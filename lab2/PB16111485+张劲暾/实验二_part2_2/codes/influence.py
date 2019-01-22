import networkx as nx

CoAuthGraph = nx.read_gexf("./CoAuthGraph.gexf")

# Degree Centrality Influence Analyse
CoAuthGraphDict = nx.convert.to_dict_of_lists(CoAuthGraph)
DegreeDict = {}
for node in CoAuthGraph.nodes:
    DegreeDict[node] = len(CoAuthGraphDict[node])

SortedDegree = sorted(DegreeDict.items(),key = lambda x:x[1],reverse = True)
InfluentialAnalyseData = open("../data2/InfluentialAnalyseData.txt",'w')
print("Top 50 of the most influential node under Degree Centrality: \n",end = '')
InfluentialAnalyseData.write("Top 50 of the most influential node under Degree Centrality: \n")
for i in range(50):
    print( str(i + 1) + ' : ' + str(SortedDegree[i]) + '\n',end = '')
    InfluentialAnalyseData.write( str(i + 1) + ' : ' + str(SortedDegree[i]) + '\n')

# Closeness Centrality Influence Analyse
NumberOfNodes = len((list)(CoAuthGraph.nodes))
ClosenessDict = {}
for node_form in CoAuthGraph.nodes:
    SumDistanse = 0
    for node_to in CoAuthGraph.nodes:
        try:
            SumDistanse += nx.shortest_path_length(CoAuthGraph,node_form,node_to)
        except nx.exception.NetworkXNoPath:
            SumDistanse += NumberOfNodes * 10
    #print(node_form + str(( NumberOfNodes - 1 ) / SumDistanse))
    ClosenessDict[node_form] = ( NumberOfNodes - 1 ) / SumDistanse
SortedCloseness = sorted(ClosenessDict.items(),key = lambda x:x[1],reverse = True)

print("Top 50 of the most influential node under Closeness Centrality: \n",end = '')
InfluentialAnalyseData.write("Top 50 of the most influential node under Closeness Centrality: \n")
for i in range(50):
    print( str(i + 1) + ' : ' + str(SortedCloseness[i]) + '\n',end = '')
    InfluentialAnalyseData.write( str(i + 1) + ' : ' + str(SortedCloseness[i]) + '\n')

InfluentialAnalyseData.close()