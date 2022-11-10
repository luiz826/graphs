t = 0

class Graph:
    def __init__(self) -> None:
        self.adj_list = []
        self.distances = {}
        self.parent = {}
        self.enter_depth = []
        self.exit_depth = []
        self.n = 0
        self.result = []
        
        
    def read_graph(self, file: str) -> None:
        
        with open(file, "r") as f:
            for i, obj in enumerate(f.readlines()):
                if i == 0:
                    self.n  = int(obj)
                else:            
                    vertices = list(map(int, obj.split()))
            
                    self.adj_list.append([j+1 for j, edge in enumerate(vertices) if edge == 1])

        self.enter_depth = [0]*self.n
        self.exit_depth = [0]*self.n
    
    
    def bfs(self, start: int) -> None: 
        t = 0
        bfs_index = [0]*self.n 
        levels = [0]*self.n
        parent = [None]*self.n

        queue = [start]
        
        while queue:
            node = queue.pop(0)
            t += 1
            bfs_index[node-1] = t
            
            for i in self.adj_list[node-1]:
                if bfs_index[i-1] == 0:
                    parent[i-1] = node-1
                    levels[i-1] = levels[node-1] + 1
                    t += 1
                    bfs_index[i-1] = t
                    queue.append(i)
                    if node < i:
                        self.result.append(f"{node},{i},false,'0,0,255'\n")
                    else:
                        self.result.append(f"{i},{node},false,'0,0,255'\n")
                elif levels[i-1] == levels[node-1] and i in queue:
                    if parent[i-1] == parent[node-1]: 
                        if node < i:
                            self.result.append(f"{node},{i},false,'255,0,0'\n")
                        else:
                            self.result.append(f"{i},{node},false,'255,0,0'\n")
                    else: 
                        if node < i:
                            self.result.append(f"{node},{i},false,'255,255,0'\n")
                        else:
                            self.result.append(f"{i},{node},false,'255,255,0'\n")
                elif levels[i-1] == levels[node-1] + 1:
                    if node < i:
                        self.result.append(f"{node},{i},false,'0,255,0'\n")
                    else:
                        self.result.append(f"{i},{node},false,'0,255,0'\n")
    
        return levels
        

    def dfs(self, start: int) -> None:
        global t
        t += 1
        self.enter_depth[start-1] = t 
        for i in self.adj_list[start-1]:
            if self.enter_depth[i-1] == 0:
                if start < i:
                    self.result.append(f"{start},{i},false,'0,0,255'\n")
                else:
                    self.result.append(f"{i},{start},false,'0,0,255'\n")
                self.parent[i-1] = start-1
                self.dfs(i)
            elif self.exit_depth[i-1] == 0 and i-1 != self.parent[start-1]:
                if start < i:
                    self.result.append(f"{start},{i},false,'255,0,0'\n")
                else:
                    self.result.append(f"{i},{start},false,'255,0,0'\n")
        t += 1
        self.exit_depth[start-1] = t
    

def generate_solution(g: Graph, file_name: str) -> None:
    global t
    g.result = sorted(g.result, key = lambda x: (int(x.split(",")[0]), int(x.split(",")[1])))

    with open(f"{file_name}.gdf", "w") as f:
        f.write("nodedef>name VARCHAR,label VARCHAR\n")
        for i in range(1, g.n+1):
            f.write(f"{i},{i}\n")
        f.write("edgedef>node1 VARCHAR,node2 VARCHAR,directed BOOLEAN,color VARCHAR\n")
        
        for i in g.result:
            f.write(i)

    g.result = []
    t = 0
        
