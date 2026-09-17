class Graph:

    def __init__(self, vertices):
        self.vertices = vertices
        self.adjList = [[] for _ in range(self.vertices)]

    def addEdge(self, src, dst, weight):
        self.adjList[src].append((dst, weight))

    def kruskal(self):

        tmpList = []
        for src, neigh in enumerate(self.adjList):
            tmpList += [(src, dst, weight) for (dst, weight) in neigh]

        tmpList.sort(key = lambda x : x[2])
        
        dsu = Dsu(self.vertices)
        result = []
        
        for src, dst, weight in tmpList:
            if len(result) == self.vertices - 1:
                break
            if not dsu.find(src, dst):
                result.append((src, dst, weight))
                dsu.union(src, dst)

        return result


class Dsu:

    def __init__(self, n):
        self.size = [1 for _ in range(n)]
        self.rep = [i for i in range(n)]

    def representative(self, a):
        x = a if self.rep[a] == a else self.representative(self.rep[a])
        self.rep[a] = x
        return x

    def union(self, a, b):

        repA = self.representative(a)
        repB = self.representative(b)

        if repA == repB:
            return

        repA, repB = (repA, repB) if self.size[repA] > self.size[repB] else (repB, repA)
        self.size[repA] += self.size[repB]
        self.rep[repB] = repA


    def find(self, a, b):
        return self.representative(a) == self.representative(b)


if __name__ == "__main__":

    g = Graph(4)
    g.addEdge(0, 1, 4)
    g.addEdge(1, 2, 3)
    g.addEdge(2, 0, 7)
    g.addEdge(2, 3, 8)
    result = g.kruskal()

    for src, dst, weight in result:
        print(f"Source: {src}, Destination: {dst}, Weight: {weight}")




