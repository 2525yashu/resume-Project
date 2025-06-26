# resume-Project
#Route Cost & Distance Calculator using Dijkstra's Algorithm

This C++ project calculates the shortest distance and associated travel cost between multiple user-defined locations using Dijkstra's algorithm. The graph is built dynamically, and the user inputs their desired journey step by step.

#Features:
Calculates shortest path by distance while also tracking cumulative cost.
Supports multiple stops and displays path between each consecutive pair.

#Automatically handles:
Invalid or unknown addresses.
Same start and end point.
Unreachable destinations.
User-friendly command-line interface with case-insensitive input.

#Core Concepts:
Graph representation using unordered_map and adjacency list.
Dijkstra's algorithm with priority queue (min-heap) for shortest path.
Uses tuple, vector, and STL for path reconstruction.
Clean, modular, and scalable design.
