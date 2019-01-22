import jieba
import csv
import numpy as np
from gensim.models.word2vec import Word2Vec
from gensim.corpora.dictionary import Dictionary
from keras.preprocessing import sequence

import yaml
from keras.models import model_from_yaml

np.random.seed(1337)  # For Reproducibility
import sys

sys.setrecursionlimit(1000000)

# define parameters
maxlen = 50


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
        #  freqxiao10->0, so k+1
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


def input_transform(string):
    words = jieba.lcut(string)
    words = np.array(words).reshape(1, -1)
    model = Word2Vec.load('../model/Word2vec_model.pkl')
    _, _, combined = create_dictionaries(model, words)
    return combined


def lstm_predict(string):
    print('loading model......')
    with open('../model/lstm.yml', 'r') as f:
        yaml_string = yaml.load(f)
    model = model_from_yaml(yaml_string)

    print('loading weights......')
    model.load_weights('../model/lstm.h5')
    model.compile(loss='categorical_crossentropy',
                  optimizer='adam', metrics=['accuracy'])
    for i in range(len(string)):
      data = input_transform(string[i])
      data.reshape(1, -1)
    # print data
      result = model.predict_classes(data)
    # print result # [[1]]
      if result[0] == 1:
        print(' positive\n')
        with open('predict0.txt', 'a', encoding="utf-8") as f:
            f.write( '1\n')
            print("写入成功")
      elif result[0] == 0:
        print(' neural\n')
        with open('predict0.txt', 'a', encoding="utf-8") as f:
            f.write( '0\n')
            print("写入成功")
      else:
        print( ' negative\n')
        with open('predict0.txt', 'a', encoding="utf-8") as f:
            f.write('-1\n')
            print("写入成功")


if __name__ == '__main__':
    # string='酒店的环境非常好，价格也便宜，值得推荐'
    # string='手机质量太差了，傻逼店家，赚黑心钱，以后再也不会买了'
    # string = "这是我看过文字写得很糟糕的书，因为买了，还是耐着性子看完了，但是总体来说不好，文字、内容、结构都不好"
    # string = "虽说是职场指导书，但是写的有点干涩，我读一半就看不下去了！"
    # string = "书的质量还好，但是内容实在没意思。本以为会侧重心理方面的分析，但实际上是婚外恋内容。"
    # string = "不是太好"
    # string = "不错不错"
    # string = "欧蓝德，价格便宜，森林人太贵啦！    "
    with open('test_public.csv', 'rt', encoding="utf-8") as csvfile:
        reader = csv.DictReader(csvfile)
        test = [row['content'] for row in reader]
    # for i in range(len(test)):
    lstm_predict(test)