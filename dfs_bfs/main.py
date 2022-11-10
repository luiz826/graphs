from graph import *

if __name__ == "__main__":
    # number of instances
    n_inst = 20
    eccentricity = []
    apv = [] # Average path lenght 
    
    
    for i in range(1, n_inst+1):
        g = Graph()
        g.read_graph(f"./in/graph_{i}")
        print(f"Starting graph {i}...")

        for j in range(1, g.n+1):
            levels_bfs = g.bfs(j)
            eccentricity.append(max(levels_bfs))
            apv.append(sum(levels_bfs))

        print("Diameter: ", max(eccentricity))
        print("Radius: ", min(eccentricity))
        print("Average path lenght: ", sum(apv) / ((g.n-1) * g.n)) # Formula
        g.dfs(1)
        generate_solution(g, f"./out/generated/graph_{i}_dfs")
        g.bfs(1)
        generate_solution(g, f"./out/generated/graph_{i}_bfs")
        eccentricity.clear()
        apv.clear()
        print(f"Graph {i} done!\n")

        