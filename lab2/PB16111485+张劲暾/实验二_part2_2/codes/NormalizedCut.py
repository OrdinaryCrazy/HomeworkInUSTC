import networkx as nx
import numpy as np
from collections import defaultdict

class NormalizedCutCommunityFinding():
    def __init__(self, Graph, expected_community_number):
        self.Graph = Graph
        self.expected_community_number = expected_community_number

    def get_community(self, K_means):
        Communities = defaultdict(set)
        Nodes = list(self.Graph.nodes())
        NodeIndex = 0
        for ass, data in K_means:
            Communities[ass].add(Nodes[NodeIndex])
            NodeIndex = NodeIndex + 1

        CommunitiesList = list(Communities.values())
        ######################################################################################################################
        # 这里为了得到一个方便展示的结果，对不在划分结果内的边进行删除，并删除一些非常小的社区
        for Com in CommunitiesList:
            for Number in Com:
                Neighbors = list( nx.classes.function.all_neighbors(self.Graph, Number) )
                for Neighbor in Neighbors:
                    if Neighbor not in Com:
                        self.Graph.remove_edge(Number, Neighbor)
        CCList = list( nx.connected_components(CoAuthGraph) )
        for CC in CCList:
            if len(CC) < 15:
                for point in CC:
                    self.Graph.remove_node(point)
        ######################################################################################################################
        return CommunitiesList

    def k_means(self, DataSet):
        CentersNum = np.random.choice(self.D.shape[0],self.expected_community_number)
        Centers = []
        for i in range(len(CentersNum)):
            Centers.append(DataSet[ CentersNum[i] ])
        Centers = np.array(Centers)
        # print(Centers)
        Assign = self.assign_points(DataSet, Centers)
        tmpA = list(Assign)
        print([ tmpA.count(x) for x in range(self.expected_community_number)])
        LastAssign = []
        while list(Assign) != list(LastAssign):
            NewCenters = self.update_center(DataSet, Assign)
            # print(NewCenters)
            LastAssign = Assign
            Assign = self.assign_points(DataSet,NewCenters)
            tmpA = list(Assign)
            print([ tmpA.count(x) for x in range(self.expected_community_number)])
        return zip(Assign, DataSet)

    def assign_points(self, DataSet, Centers):
        print("Assigning Points ...")
        Assign = []
        for Point in DataSet:
            ShortestDistance = float("inf")
            NearestCenter = 0
            for cen in range(len(Centers)):
                dis = ( ( Point - Centers[cen] ) ** 2 ).sum() ** 0.5
                if dis < ShortestDistance:
                    ShortestDistance = dis
                    NearestCenter = cen
            Assign.append(NearestCenter)
        return np.array(Assign)

    def point_avg(self, points):
        Sum = np.zeros(self.expected_community_number)
        for point in points:
            Sum = Sum + np.array(point)
        return list( ( Sum / len(points) ) )

    def update_center(self, DataSet, Assign):
        print("Updating centers ...")
        NewAssign = defaultdict(list)
        Centers = []
        for ass, point in zip(Assign, DataSet):
            NewAssign[ass].append(point)
        for points in NewAssign.values():
            Centers.append(self.point_avg(points))
        return np.array(Centers)

    def spectral_cut(self):
        '''
            Compute eigenvectors for Laplacian matrix of the graph
        '''
        DegreeDict = (dict)(nx.degree(self.Graph))
        self.D = np.diag(list(DegreeDict.values())).astype(float)
        self.D_05 = np.diag(list(DegreeDict.values())).astype(float)

        for i in range(self.D_05.shape[0]):
            if self.D_05[i][i] != 0:
                self.D_05[i][i] = self.D_05[i][i] ** (-0.5)
        self.M = nx.adjacency_matrix(self.Graph).todense()
        self.M.astype(float)
        LaplacianMatrix = np.dot( np.dot( self.D_05, ( self.D - self.M ) ), self.D_05 )
        print("Getting eigenvectors...")
        EigenValues, EigenVectors = np.linalg.eig(LaplacianMatrix)
        print("Eigenvectors get.")
        return np.array( EigenVectors[:self.expected_community_number] )

    def run(self):
        EigenVectorForCut = self.spectral_cut()
        Clusters = self.k_means(EigenVectorForCut.T)
        Communities = self.get_community(Clusters)
        print(len(Communities))
        return Communities


if __name__ == '__main__':
    CoAuthGraph = nx.read_gexf("./B1SimpleCoAuthGraph.gexf")
    # 根据GirvanNewman算法的结果将
    NCFinder = NormalizedCutCommunityFinding(CoAuthGraph,12)
    print("Original Community Number: " + str(nx.number_connected_components(CoAuthGraph)))
    print("Begin Finding...")
    Communities = NCFinder.run()

    CommunityFile = open("../data2/NormalizedCutCommunity.txt",'w')
    for i in range(len(Communities)):
        CommunityFile.write(str(i) + ' : ' + str(Communities[i]) + '\n')
    nx.write_gexf(NCFinder.Graph,"./NCCut_CoAuthGraph.gexf")
    CommunityFile.close()
    