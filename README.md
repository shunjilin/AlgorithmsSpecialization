##### Coursera: Algorithms Specialization [Stanford]

##### Shunji Lin  

Another attempt at the programming problems from [Algorithms Specialization](https://www.coursera.org/specializations/algorithms).  

*C++ implementations, CMake and unit tests using Google Test/ Google Mock*

## Cloning the repository
```
git clone https://github.com/shunjilin/AlgorithmsSpecialization --recurse-submodules
```

## Usage
In root folder, make directory ./build

In ./build, run:
```
cmake ..
```
followed by:
```
make
```
To run all (unit) tests:
```
ctest --verbose
```

## Problems

* 01.Karatsuba - O(n^(log2(3)) multiplication algorithm
* 02.Inversions - Merge sort + counting inversions
* 03.QuickSort - QuickSort + counting comparisons
* 04.MinimumCut - Kargers minimum cut algorithm with Union-Find data structure
* 05.StronglyConnectedComponents - Kosaraju's algorithm
* 06.ShortestPath - Dijkstra's algorithm for single source shortest paths
* 07.MedianMaintenance - Running median using min and max heaps
* 08.TwoSum - 2-SUM algorithm using binary search and a hash table
* 09.MinimumWeightedSumOfCompletionTimes - Greedy scheduling
* 10.MinimumSpanningTree - Prim's algorithm
* 11.Clustering - k Clustering using Union-Find data structure
* 12.ClusteringBig - k Clustering of bitstrings by hamming distances
* 13.HuffmanCoding - Huffman coding for binary coding compression
* 14.MaxWeightIndependentSet - MWIS using dynamic programming
* 15.Knapsack - Optimal knapsack value using dynamic programming
* 16.KnapsackBig - Optimal knapsack value using recursion with memoization
* 17.AllPairsShortestPaths - all pairs shortest path with Johnson's algorithm
* 18.TravelingSalesmanProblem - exact TSP using dynamic programming
* 19.ApproximateTravelingSalesmanProblem - approximate TSP using nearest neighbor heuristic