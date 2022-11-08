#!/bin/bash
for (( counter=1; counter<21; counter++ ))
do
    echo "dfs test $counter"
    diff out/originals/graph_$counter\_bfs.gdf out/generated/graph_$counter\_bfs.gdf
done
printf "\n"

for (( counter=1; counter<21; counter++ ))
do 
    echo "bfs test $counter"
    diff out/originals/graph_$counter\_bfs.gdf out/generated/graph_$counter\_bfs.gdf
done
printf "\n"