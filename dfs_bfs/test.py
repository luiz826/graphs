from collections import defaultdict


class Graph:
    def __init__(self):
        self.adj_list = []
        self.distances = {}
        self.parent = {}
        self.n = 0
        
    def read_graph(self, file):
        
        with open(file, "r") as f:
            for i, obj in enumerate(f.readlines()):
                if i == 0:
                    self.n  = int(obj)
                else:            
                    vertices = list(map(int, obj.split()))
            
                    self.adj_list.append([j+1 for j, edge in enumerate(vertices) if edge == 1])

    
        return self.adj_list

    
    def bfs(self, start): # Largura
        visited = set()  
        queue = [start]
        result = []
        
        levels = [0]*self.n
        
        while queue:
            
            node = queue.pop(0)
            if node not in visited:
                visited.add(node)
                for i in self.adj_list[node-1]:   
                    if i not in queue and i not in visited:
                        queue.append(i)
                        if node < i:
                            result.append(f"{node},{i},false,'0,0,255'\n")
                        else:
                            result.append(f"{i},{node},false,'0,0,255'\n")
 
                        levels[i-1] = levels[node-1] + 1
                        self.parent[i-1] = node-1 
                    elif levels[i-1] == levels[node-1] and i in queue:
                        if self.parent[i-1] == self.parent[node-1]: 
                            result.append(f"{node},{i},false,'255,0,0'\n ")
                        else: 
                            result.append(f"{node},{i},false,'255,255,0'\n")
                    elif levels[i-1] == levels[node-1] + 1:
                        result.append(f"{node},{i},false,'0,255,0'\n")
      
      
        return visited, result
    
    def dfs(self, start): # Profundidade
        visited = set()
        stack = [start]
    
    
        result = []

        
        while stack:
            print("Stack: ", stack)
            node = stack.pop()
            print("No da vez: ", node)
            
            if node not in visited:
                visited.add(node)
                for i in self.adj_list[node-1]:
                    print("adj: ", i)
                    if  i not in stack and i not in visited:
                        stack.append(i)
                        if node < i:
                            result.append(f"{node},{i},false,'0,0,255'\n")
                            # result.append([node,i,"false"],["'0,0,255'"]])
                        else:
                            result.append(f"{i},{node},false,'0,0,255'\n")
                            # result.append([[i],[node],["false"],["'0,0,255'"]])
 
                        # levels[i-1] = levels[node-1] + 1
                        self.parent[i-1] = node - 1 
                    # elif i in stack:
                    #     result.append(f"{node},{i},false,'255,0,0'\n")
                        
                    
        print(self.parent)     

        
        return visited, result
    

    
g =  Graph()

g.read_graph("graph_1")

b = g.dfs(1)
print(g.adj_list)
s1 = sorted(b[-1], key=lambda x: int(x[0] + x[2]))
print(s1)