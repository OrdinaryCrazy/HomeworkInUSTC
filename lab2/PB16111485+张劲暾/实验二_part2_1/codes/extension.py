import numpy as np
import math

time = np.zeros([6041, 3953], dtype=int)

def get_data(filename):
    x = np.zeros([6041, 3953], dtype=int)
    test = []
    i=0
    with open(filename,'r') as f:
        for line in f.readlines():
            line = line.strip("\n").split("::")
            time[int(line[0])][int(line[1])] = int(line[3])
            if(i%20!=0):
                x[int(line[0])][int(line[1])] = int(line[2])
            else:
                test.append([int(line[0]),int(line[1]),int(line[2])])
            i+=1
    movies = {}
    with open("movies.dat", "r", encoding='ISO-8859-1') as f:
        for line in f.readlines():
            line = line.strip("\n").split("::")
            value = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
            ref = line[2].split("|")
            if "Action" in ref:
                value[0] = 1
            if "Adventure" in ref:
                value[1] = 1
            if "Animation" in ref:
                value[2] = 1
            if "Children's" in ref:
                value[3] = 1
            if "Comedy" in ref:
                value[4] = 1
            if "Crime" in ref:
                value[5] = 1
            if "Documentary" in ref:
                value[6] = 1
            if "Drama" in ref:
                value[7] = 1
            if "Fantasy" in ref:
                value[8] = 1
            if "Film-Noir" in ref:
                value[9] = 1
            if "Horror" in ref:
                value[10] = 1
            if "Musical" in ref:
                value[11] = 1
            if "Mystery" in ref:
                value[12] = 1
            if "Romance" in ref:
                value[13] = 1
            if "Sci-Fi" in ref:
                value[14] = 1
            if "Thriller" in ref:
                value[15] = 1
            if "War" in ref:
                value[16] = 1
            if "Western" in ref:
                value[17] = 1
            movies[int(line[0])] = value
    return x,test,movies

def ItemSimilarity(train, alpha):
    C = dict()
    N = dict()
    for u, items in train.items():
        for i,tui in items.items():
            N[i] += 1
            for j,tuj in items.items():
                if i == j:
                    continue
                C[i][j] += 1 / (1 + alpha * abs(tui - tuj))
    W = dict()
    for i,related_items in C.items():
        for j, cij in related_items.items():
            W[u] = cij / math.sqrt(N[i] * N[j])
    return W

def get_sim(i,j,data,movies):
    items = data[:, [i, j]]
    del_inds = np.where(items == 0)[0]
    items = np.delete(items, del_inds, axis=0)
    x = items[:,0]
    y = items[:,1]
    s = time[:,[i,j]]
    dele = np.where(s == 0)[0]
    s = np.delete(s,dele,axis=0)
    tx = s[:,0]
    ty = s[:,1]
    if s.size == 0:
        sim = 0
    if items.size == 0:
        sim = 0
    else:
        sim = ((x @ y)/(np.linalg.norm(x,2) * np.linalg.norm(y,2)))
        sim = sim * (tx @ ty)/(np.linalg.norm(tx,2) * np.linalg.norm(ty,2))
    if i in movies:
        x = np.array(movies[i])
    else:
        sim = 0
        return sim
    if j in movies:
        y = np.array(movies[j])
    else:
        sim = 0
        return sim
    sim = sim * (x @ y)/(np.linalg.norm(x,2) * np.linalg.norm(y,2))
    return sim

def get_sim_matri(data,movies):
    sim_matri = np.zeros((3953,3953))
    v=0
    print("getting simi mat!")
    for i in range(1,3953):
        for j in range(i+1,3953):
            sim_matri[i,j] = get_sim(i,j,data,movies)
            sim_matri[j,i] = sim_matri[i,j]
            v+=1
            if(v==1953276):
                print("25%")
            if(v==3906552):
                print("50%")
    print("done!")
    print("file writing!")
    with open("sim_matrix.dat","w") as w:
        for i in range(3953):
            for j in range(3953):
                w.write(str(sim_matri[i,j])+",")
            w.write("\n")
    print("writing done!")
    return sim_matri

def get_sim_matri2(data,movies):
    sim_matri = np.zeros((3953,3953))
    i = 0
    j = 0
    with open("sim_matrix.dat", "r") as w:
        for line in w.readlines():
            line = line.strip("\n").split(",")
            for j in range(3953):
                sim_matri[i, j] = float(line[j])
            i += 1
    return sim_matri


def fullfill_matri(data,simi_matri):
    print("fullfilling!")
    for i in range(1,6041):
        usr = data[i]
        un_fill = np.where(usr == 0)[0]
        filled = np.where(usr > 0)[0]
        stars = usr[filled]
        for j in un_fill[1:]:
            sim = simi_matri[j][filled]
            if(np.sum(sim)==0):
                data[i,j] = round(np.sum(stars)) / np.linalg.norm(stars,1)
            else:
                data[i,j] = round(np.sum(stars * sim) / np.linalg.norm(sim,1))
        if(i == 2000):
            print("30%")
        if(i == 4000):
            print("60%")
    print("done!")
    return data

def evaluate(test,data):
    #ItemSimilarity
    num = len(test)
    res1 = 0
    res2 = 0
    res3 = 0
    res4 = 0
    for x in test:
        res1+=abs(data[x[0],x[1]]-x[2])
        res3+=(data[x[0],x[1]]-x[2])*(data[x[0],x[1]]-x[2])
        if(data[x[0],x[1]]==x[2]):
            res2+=1

    res1 = res1 / num
    res2 = res2 / num
    res4 = res3 / num
    res3 = math.sqrt(res3 / (num-1))
    return res1,res2,res3,res4

data, test, movies = get_data("ratings.dat");
sim_matri = get_sim_matri(data,movies)
data = fullfill_matri(data,sim_matri)
r1,r2,r3,r4 = evaluate(test,data)
print("MAE:         ",r1)
print("precision:   ",r2)
print("RMSE:        ",r3)
print("VAR:         ",r4)


