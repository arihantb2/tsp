/*
*  graph.h - Declaration of the CompleteGraph data structure
*  Date: March 8, 2021
*  Author: Arihant Lunawat
*/

#pragma once

#include <bits/stdc++.h>

namespace graph
{
    class CompleteGraph
    {
    public:
        typedef std::vector<int> Vertices;
        typedef std::unordered_map<int, std::unordered_map<int, int>> Edges;

        CompleteGraph();
        CompleteGraph(const CompleteGraph &);

        ~CompleteGraph() {}

        Vertices vertices() { return vertices_; }
        Vertices vertices() const { return vertices_; }

        Edges edges() { return edges_; }
        Edges edges() const { return edges_; }

        void print(std::string str = std::string("Graph:"), bool printEdges = true);

        bool addVertexWithUserInput();
        bool addVertexIfNotExists(int);
        bool addEdge(int, int, int);

        bool removeVertexWithUserInput();
        bool removeVertex(int);
        bool removeEdge(int, int);

        void computeTSP();

    private:
        Vertices vertices_;
        Edges edges_;
    };
}