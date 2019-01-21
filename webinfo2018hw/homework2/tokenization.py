import jieba
file = open('./poems')
file_cut = open('./poems_cut','w')
for line in file:
    file_cut.write(str(list(jieba.cut(line.replace(' ','').replace('，','').replace('。','').replace('；','') \
    .replace('？','').replace('！','').replace('》','').replace('《','').replace('、','').replace('\n','')))))
    file_cut.write('\n')