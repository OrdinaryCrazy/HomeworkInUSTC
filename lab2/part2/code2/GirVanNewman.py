# -*- coding: utf-8 -*-
import networkx as nx
# 以Q值大于0.5表示一个连通块有很好的社区结构并作为终止条件

class GirvanNewman():
    def __init__(self,Graph,Q = 0.5):
        self.Graph = Graph
        self.Q = Q

    def get_community(self):
        return (list)( nx.connected_components(self.Graph) )

    #def compute_betweenness():

    def get_modularity(self):
        print("Computing Modularity...")
        Communities = nx.connected_components(self.Graph)
        DegreeDict = (dict)(nx.degree(self.Graph))
        Modularity = 0.0
        Nodes = list(self.Graph.nodes())
        AdjMatrix = nx.adj_matrix(self.Graph)
        NumberOfEdges = nx.number_of_edges(self.Graph)
        
        for Com in Communities:
            for node_from in Com:
                for node_to in Com:
                    Modularity += ( float(AdjMatrix[Nodes.index(node_from),Nodes.index(node_to)]) - float(DegreeDict[node_from] * DegreeDict[node_to]) / float(2 * NumberOfEdges) )

        Modularity = Modularity / ( 2 * NumberOfEdges )
        return Modularity

    def cut_bridge(self):
        OriginCommunityNum = nx.number_connected_components(self.Graph)
        NewCommunityNum = OriginCommunityNum
        print("Begin Cut ...",end ='\t')
        CutTimes = 0
        while NewCommunityNum <= OriginCommunityNum:

            # print("Computing Betweenness...",end='\t')
            EdgeBetweenness = nx.edge_betweenness_centrality(self.Graph)
            # print("Betweenness get.")
            CutTimes = CutTimes + 1
            ############################################################################################
            # 这里每次只删除一条界边数最高的边
            # EBSortedOrder = sorted(EdgeBetweenness.items(),key=lambda x:x[1],reverse=True)
            # self.Graph.remove_edge(EBSortedOrder[0][0][0],EBSortedOrder[0][0][1])
            ############################################################################################

            # 一次性删除所有界边数最高的边加快收敛速度：
            MaxEB = max(EdgeBetweenness.values())
            for edge, bet in EdgeBetweenness.items():
                if float(bet) == MaxEB:
                    self.Graph.remove_edge(edge[0],edge[1])

            NewCommunityNum = nx.number_connected_components(self.Graph)

        print("Cut: " + str(CutTimes) + " Edges.")

    def run(self):
        while True:
            ModulQ = self.get_modularity()
            print("Get Modularity:" + str(ModulQ))
            if (ModulQ > self.Q) or (self.Graph.number_of_edges() == 0):
                break
            self.cut_bridge()
            #################################################################################################
            # 每轮都去清除边缘节点，防止一些只有一两个点的社区，没有意义
            DegreeDict = (dict)(nx.degree(self.Graph))
            NodeList = list( self.Graph.nodes() )
            for node in NodeList:
                if DegreeDict[node] <= 1:
                    self.Graph.remove_node(node)
            #################################################################################################

if __name__ == '__main__':
    CoAuthGraph = nx.read_gexf("./B2SimpleCoAuthGraph.gexf")
    GNFinder = GirvanNewman(CoAuthGraph,Q=0.5)
    print("Original Community Number: " + str(nx.number_connected_components(CoAuthGraph)))
    print("Begin Finding...")
    GNFinder.run()
    #print(GNFinder.get_community())

    CommunityFile = open("../data2/GirvanNewmanCommunity.txt",'w')
    Communities = list( nx.connected_components(GNFinder.Graph) )
    for i in range(len(Communities)):
        CommunityFile.write(str(i) + ' : ' + str(Communities[i]) + '\n')
    nx.write_gexf(GNFinder.Graph,"./GNCut_CoAuthGraph.gexf")
    CommunityFile.close()