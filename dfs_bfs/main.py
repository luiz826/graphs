from graph import *

if __name__ == "__main__":
    # number of instances
    n_inst = 20
    
    
    for i in range(1, n_inst+1):
        g = Graph()
        g.read_graph(f"./in/graph_{i}")
        g.dfs(1)
        generate_solution(g, f"./out/generated/graph_{i}_dfs")
        g.bfs(1)
        generate_solution(g, f"./out/generated/graph_{i}_bfs")
        print(f"Graph {i} done!")
        