library(igraph)

dataFile = "net.txt"
outputFile = "network.txt"

graph = read.graph(dataFile)
sub = induced_subgraph(graph, c(1:5000))
graphComponents = components(sub)
largestComponent = which.max(graphComponents$csize)
largestSubgraphMembers = groups(graphComponents)[largestComponent]
largestSubgraph = induced_subgraph(sub, unlist(largestSubgraphMembers))

write_graph(largestSubgraph, outputFile)
