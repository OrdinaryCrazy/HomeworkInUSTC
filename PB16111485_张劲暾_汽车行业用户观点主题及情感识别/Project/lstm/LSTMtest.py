import pandas as pd
import numpy as np
import jieba
import multiprocessing

from gensim.models.word2vec import Word2Vec
from gensim.corpora.dictionary import Dictionary
from keras.preprocessing import sequence

from sklearn.model_selection import train_test_split
from keras.models import Sequential
from keras.layers.embeddings import Embedding
from keras.layers.recurrent import LSTM
from keras.layers.core import Dense, Dropout, Activation
from keras.models import model_from_yaml
from keras import utils as np_utils

np.random.seed(1337)  # For Reproducibility
import sys

sys.setrecursionlimit(1000000)
import yaml

# set parameters:
cpu_count = multiprocessing.cpu_count()  # 4
vocab_dim = 100
n_iterations = 1  # ideally more..
n_exposures = 10  # all words with freq>10
window_size = 7
n_epoch = 4
input_length = 100
maxlen = 100

batch_size = 32


def loadfile():
    neg = pd.read_csv('./neg.csv', header=None, index_col=None)
    pos = pd.read_csv('./pos.csv', header=None, index_col=None, error_bad_lines=False)
    neu = pd.read_csv('./neu.csv', header=None, index_col=None)


    combined = np.concatenate((pos[0], neu[0], neg[0]))
    y = np.concatenate((np.ones(len(pos), dtype=int), np.zeros(len(neu), dtype=int),
                        -1*np.ones(len(neg),dtype=int)))

    return combined,y


# cut words in sentence and delete the breaks for new lines
def tokenizer(text):
    ''' Simple Parser converting each document to lower-case, then
        removing the breaks for new lines and finally splitting on the
        whitespace
    '''
    text = [jieba.lcut(document.replace('\n', '')) for document in text]
    return text


def create_dictionaries(model=None,
                        combined=None):
    ''' Function does are number of Jobs:
        1- Creates a word to index mapping
        2- Creates a word to vector mapping
        3- Transforms the Training and Testing Dictionaries
    '''
    if (combined is not None) and (model is not None):
        gensim_dict = Dictionary()
        gensim_dict.doc2bow(model.wv.vocab.keys(),
                            allow_update=True)
        #  freqxiao10->0 ,so k+1
        w2indx = {v: k + 1 for k, v in gensim_dict.items()}  # all index of word with freq>10,(k->v)=>(v->k)
        w2vec = {word: model[word] for word in
                 w2indx.keys()}  # all index of word vectors with freq>10, (word->model(word))

        def parse_dataset(combined):
            ''' Words become integers
            '''
            data = []
            for sentence in combined:
                new_txt = []
                for word in sentence:
                    try:
                        new_txt.append(w2indx[word])
                    except:
                        new_txt.append(0)  # freqxiao10->0
                data.append(new_txt)
            return data  # word=>index

        combined = parse_dataset(combined)
        combined = sequence.pad_sequences(combined,
                                          maxlen=maxlen)  # index to every word in every sentence, when freq < 10, index = 0
        return w2indx, w2vec, combined
    else:
        print('No data provided...')


# create dictionary for words, and return index and word vector, and the word index of each sentence
def word2vec_train(combined):
    model = Word2Vec(size=vocab_dim,
                     min_count=n_exposures,
                     window=window_size,
                     workers=cpu_count,
                     iter=n_iterations)
    model.build_vocab(combined)  # input: list
    model.train(combined, total_examples=model.corpus_count, epochs=model.iter)
    model.save('../model/Word2vec_model0.pkl')
    index_dict, word_vectors, combined = create_dictionaries(model=model, combined=combined)
    return index_dict, word_vectors, combined

# def word2vec_train1(combined):
#     model1 = Word2Vec(size=vocab_dim,
#                      min_count=n_exposures,
#                      window=window_size,
#                      workers=cpu_count,
#                      iter=n_iterations)
#     model1.build_vocab(combined)  # input: list
#     model1.train(combined, total_examples=model1.corpus_count, epochs=model1.iter)
#     model1.save('../model/Word2vec_model1.pkl')
#     index_dict, word_vectors, combined = create_dictionaries(model=model1, combined=combined)
#     return index_dict, word_vectors, combined

def get_data(index_dict, word_vectors, combined, y):
    n_symbols = len(index_dict) + 1
    embedding_weights = np.zeros((n_symbols, vocab_dim))
    for word, index in index_dict.items():
        embedding_weights[index, :] = word_vectors[word]
    x_train, x_test, y_train, y_test = train_test_split(combined, y, test_size=0.2)
    y_train = np_utils.to_categorical(y_train, num_classes=3)
    y_test = np_utils.to_categorical(y_test, num_classes=3)
    # print x_train.shape,y_train.shape
    return n_symbols, embedding_weights, x_train, y_train, x_test, y_test
# def get_data1(index_dict, word_vectors, combined, y):
#     n_symbols1 = len(index_dict) + 1  # the number of index of all words, word with fre<10, index=0, so ++1
#     embedding_weights1 = np.zeros((n_symbols1, vocab_dim))  # initialize word with index = 0, word vector = 0
#     for word, index in index_dict.items():  # from index=1, every word index <-> word vector
#         embedding_weights1[index, :] = word_vectors[word]
#     x_train1, x_test1, y_train1, y_test1 = train_test_split(combined, y, test_size=0.5)
#     y_train1 = np_utils.to_categorical(y_train1, num_classes=3)
#     y_test1 = np_utils.to_categorical(y_test1, num_classes=3)
#     print x_train.shape,y_train.shape
    # return n_symbols1, embedding_weights1, x_train1, y_train1, x_test1, y_test1
#
# define network structure
def train_lstm(n_symbols, embedding_weights, x_train, y_train, x_test, y_test):
    print('Defining a Simple Keras Model...')
    model = Sequential()  # or Graph or whatever
    model.add(Embedding(output_dim=vocab_dim,
                        input_dim=n_symbols,
                        mask_zero=True,
                        weights=[embedding_weights],
                        input_length=input_length))  # Adding Input Length
    model.add(LSTM(output_dim=50, activation='tanh'))
    model.add(Dropout(0.5))
    model.add(Dense(3, activation='softmax'))  # Dense=>full connection layer,output demension=3
    model.add(Activation('softmax'))

    print('Compiling the Model...')
    model.compile(loss='categorical_crossentropy',
                  optimizer='adam', metrics=['accuracy'])

    print("Train...")  # batch_size=32
    model.fit(x_train, y_train, batch_size=batch_size, epochs=n_epoch, verbose=1)

    print("Evaluate...")
    score = model.evaluate(x_test, y_test,
                           batch_size=batch_size)
    # score1 = model.evaluate(x_test1, y_test1,
    #                        batch_size=batch_size)

    yaml_string = model.to_yaml()
    with open('../model/lstm0.yml', 'w') as outfile:
        outfile.write(yaml.dump(yaml_string, default_flow_style=True))
    model.save_weights('../model/lstm0.h5')
    print('Test score:', score)



# train model and then save model
print('Loading Data...')
combined, y= loadfile()
print(len(combined), len(y))
# print(len(combined1), len(y1))
print('Tokenising...')
combined = tokenizer(combined)
# combined1 = tokenizer(combined1)
print('Training a Word2vec model...')
index_dict, word_vectors, combined = word2vec_train(combined)
# index_dict1, word_vectors1, combined1 = word2vec_train1(combined1)

print('Setting up Arrays for Keras Embedding Layer...')
n_symbols, embedding_weights, x_train, y_train, x_test, y_test = get_data(index_dict, word_vectors, combined, y)
# n_symbols1, embedding_weights1, x_train1, y_train1, x_test1, y_test1 = get_data1(index_dict1, word_vectors1, combined1, y1)
print("x_train.shape and y_train.shape:")
print(x_train.shape, y_train.shape)

train_lstm(n_symbols, embedding_weights, x_train, y_train, x_test, y_test)