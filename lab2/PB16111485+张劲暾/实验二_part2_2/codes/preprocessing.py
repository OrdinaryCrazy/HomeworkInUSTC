# -*- coding: utf-8 -*-
import networkx as nx

#####################################################################################
# node = ['A','B','C','A']
# edge = [['A','B'],['B','C']]
# G = nx.Graph()
# G.add_nodes_from(node)
# G.add_edges_from(edge)
# nx.write_gexf(G,"./graph.gexf")
#####################################################################################

InputFile = open("../data2/Erdos1.txt")
node = []
edge = []
for i in range(511):
    CoAuth = InputFile.readline()
    CoAuth = CoAuth.replace(' ','').replace('\n','').replace('1','').replace('2','').replace('3','').replace('4','').replace('5','').replace('6','').replace('7','').replace('8','').replace('9','').replace('0','').replace('\t','').replace(':','').replace('*','')
    node.append(CoAuth)
    CoCoAuth = InputFile.readline()
    while(CoCoAuth != '\n'):
        CoCoAuth = CoCoAuth.replace(' ','').replace('\n','').replace('1','').replace('2','').replace('3','').replace('4','').replace('5','').replace('6','').replace('7','').replace('8','').replace('9','').replace('0','').replace('\t','').replace(':','').replace('*','')
        node.append(CoCoAuth)
        edge.append([CoAuth,CoCoAuth])
        CoCoAuth = InputFile.readline()
    print(str(i) + ':' + CoAuth)

CoAuthGraph = nx.Graph()
CoAuthGraph.add_nodes_from(node)
CoAuthGraph.add_edges_from(edge)

#############################################################################################
# 因为这个图实在是太大了，在上面计算 betweenness 和 modularity 计算量太大，所以删除度数为1的边缘节点以便计算
DegreeDict = (dict)(nx.degree(CoAuthGraph))
NodeList = list( CoAuthGraph.nodes() )
for node in NodeList:
    # if DegreeDict[node] <= 1:
    # 删除度数为2的节点，基本上就能看到结果了：
    if DegreeDict[node] <= 2:
        CoAuthGraph.remove_node(node)
#############################################################################################

# nx.write_gexf(CoAuthGraph,"./CoAuthGraph.gexf")
# nx.write_gexf(CoAuthGraph,"./SimpleCoAuthGraph.gexf")

nx.write_gexf(CoAuthGraph,"./B1SimpleCoAuthGraph.gexf")

# pos = nx.spring_layout(CoAuthGraph)
# nx.draw_networkx(CoAuthGraph, pos, node_size=de2, with_labels = False, node_color='#A52A2A', linewidths=None, width=1.0, edge_color ='#858585')