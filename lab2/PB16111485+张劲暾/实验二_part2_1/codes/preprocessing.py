import os
import random
import pandas as pd
import numpy as np
import math

def initRatingMatrix():
    dataMatrix = np.zeros((3953, 6041), dtype=np.int8)  # 横坐标为电影ID，纵坐标为用户ID
    return dataMatrix


genres = {
    "Action": 2 ** 0,
    "Adventure": 2 ** 1,
    "Animation": 2 ** 2,
    "Children's": 2 ** 3,
    "Comedy": 2 ** 4,
    "Crime": 2 ** 5,
    "Documentary": 2 ** 6,
    "Drama": 2 ** 7,
    "Fantasy": 2 ** 8,
    "Film-Noir": 2 ** 9,
    "Horror": 2 ** 10,
    "Musical": 2 ** 11,
    "Mystery": 2 ** 12,
    "Romance": 2 ** 13,
    "Sci-Fi": 2 ** 14,
    "Thriller": 2 ** 15,
    "War": 2 ** 16,
    "Western": 2 ** 17
}


class contentBased:
    def __init__(self):
        self.ratingMatrix = np.zeros((3953, 6041), dtype=np.int8)  # 横坐标为电影ID，纵坐标为用户ID
        self.genresMatrix = np.zeros((3953, 2), dtype=np.int64)  # 横坐标为电影ID
        self.userGenresTimesMatrix = np.zeros((6041, 19), dtype=np.int16)  # 横坐标为用户ID
        self.userGenresRateMatrix = np.zeros((6041, 19), dtype=np.float_)  # 横坐标为用户ID
        self.movieJaccard = np.zeros((3953, 3953), dtype=np.float_)  # 用jaccard计算电影相似度
        self.userRated = []
        for i in range(0, 6041):
            self.userRated.append([])
        print(self.userRated)
        self.testData = []

    def setMovie(self, movieID, genreStr):
        p = genreStr.split('|')
        q = 0
        for i in p:
            self.genresMatrix[movieID][0] |= genres[i]
            q |= genres[i]

    def setUserGenresMatrix(self, userID, movieID, rating):
        p = 1
        item = self.genresMatrix[movieID][0]
        for i in range(1, 18):
            if (p & item):
                self.userGenresTimesMatrix[userID][i] += 1  # 是否需要根据一个电影的标签数量设置权重
                self.userGenresRateMatrix[userID][i] += rating
                self.userRated[userID].append(movieID)
            p = p << 1

    def preprocess(self):  # ratingPath, moviePath):
        ratingPath = "D:/learning/webinfo/movie database/ml-1m/ratings.dat"
        moviePath = "D:/learning/webinfo/movie database/ml-1m/movies.dat"
        with open(moviePath, 'r', encoding='ISO-8859-1') as f:  # set genresMatrix for each movie
            line = f.readline()
            while (line != ''):
                line = line.strip("\n")
                p = line.split('::')
                self.setMovie(int(p[0]), p[2])
                print(p)
                line = f.readline()
        for i in range(0, 3593):
            for j in range(0, 3593):
                totalGenres = 0
                sameGenres = 0
                t = 1
                for p in range(1, 18):
                    if ((t | self.genresMatrix[i][0]) or (t | self.genresMatrix[j][0])):
                        totalGenres += 1
                        if ((t | self.genresMatrix[i][0]) and (t | self.genresMatrix[j][0])):
                            sameGenres += 1
                self.movieJaccard[i][j] = sameGenres / totalGenres
        with open(ratingPath, 'r') as f:
            line = f.readline()
            while (line != ''):
                p = line.split('::')
                # print(p)
                if (random.random() > 0.01):
                    self.ratingMatrix[int(p[1])][int(p[0])] = int(p[2])
                    self.setUserGenresMatrix(int(p[0]), int(p[1]), int(p[2]))
                else:
                    self.testData.append(p)
                line = f.readline()
            f.close()
        for i in range(0, 6041):
            for j in range(0, 18):
                if (self.userGenresRateMatrix[i][j] != 0):
                    self.userGenresRateMatrix[i][j] /= self.userGenresTimesMatrix[i][j]
        for i in self.userGenresRateMatrix:
            print(i)
        for i in range(0, 3953):
            times = 0
            temp = 0
            for j in range(0, 6041):
                if (self.ratingMatrix[i][j] > 0):
                    times += 1
                    temp += self.ratingMatrix[i][j]
            if times != 0:
                self.genresMatrix[i][1] = temp / times
            else:
                self.genresMatrix[i][1] = 0
        print("preprocess finished")
p = contentBased()
p.preprocess()