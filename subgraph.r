library(igraph)

dataFile = "net.txt"
outputFile = "data/network-medium.txt"

graph = read.graph(dataFile)
sub = induced_subgraph(graph, c(1:5000))
graphComponents = components(sub)
largestComponent = which.max(graphComponents$csize)
largestSubgraphMembers = groups(graphComponents)[largestComponent]
largestSubgraph = induced_subgraph(sub, unlist(largestSubgraphMembers))

subgraph = as_edgelist(largestSubgraph)
weightedSubgraph = cbind(subgraph, runif(dim(subgraph)[1]))

write.table(weightedSubgraph, outputFile, quote=FALSE, row.names=FALSE, col.names=FALSE)
