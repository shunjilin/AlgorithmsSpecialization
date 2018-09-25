#ifndef APPROXIMATE_TRAVELING_SALESMAN_PROBLEM_HPP
#define APPROXIMATE_TRAVELING_SALESMAN_PROBLEM_HPP

#include <cmath>
#include <vector>
#include <limits>
#include <iostream>

struct Vertex {
    double x;
    double y;
    Vertex(double x, double y) : x(x), y(y) {}
};

double euclideanDistance(Vertex const & v1, Vertex const & v2) {
    return sqrt(pow((v1.x - v2.x), 2) + pow((v1.y - v2.y), 2));
}

double getApproximateTSPValue(std::vector<Vertex> const & vertices) {
    std::vector<bool> visited(vertices.size(), false);

    size_t current_vertex_index = 0;
    visited[current_vertex_index] = true;

    double tour_distance = 0.0;

    while (true) {
        
        size_t shortest_distance_vertex = std::numeric_limits<size_t>::max();
        auto shortest_distance = std::numeric_limits<double>::max();

        // pick nearest neighbor
        for (size_t vertex_index = 0; vertex_index < vertices.size();
             ++vertex_index) {
            if (!visited[vertex_index]) {
                auto distance_to_vertex =
                    euclideanDistance(vertices[current_vertex_index],
                                      vertices[vertex_index]);
                if (distance_to_vertex < shortest_distance) {
                    shortest_distance = distance_to_vertex;
                    shortest_distance_vertex = vertex_index;
                }
            }
        }

        // add nearest neighbor distance and go to that vertex
        if (shortest_distance_vertex != std::numeric_limits<size_t>::max()) {
            tour_distance += shortest_distance;
            visited[shortest_distance_vertex] = true;
            current_vertex_index = shortest_distance_vertex;
        } else {
            break;
        }
    }
    // last hop to complete tour
    tour_distance += euclideanDistance(vertices[current_vertex_index],
                                       vertices[0]);
    
    return tour_distance;
}


#endif
