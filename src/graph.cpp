
/*
*  graph.h - Declaration of the CompleteGraph data structure
*  Date: March 8, 2021
*  Author: Arihant Lunawat
*/

#include <graph.h>

namespace graph
{
    CompleteGraph::CompleteGraph()
    {
        vertices_.clear();
        edges_.clear();
    }

    CompleteGraph::CompleteGraph(const CompleteGraph &other)
    {
        vertices_.clear();
        edges_.clear();
        for (auto edgeList : other.edges())
        {
            for (auto edge : edgeList.second)
                addEdge(edgeList.first, edge.first, edge.second);
        }
    }

    void CompleteGraph::print(std::string str, bool printEdges)
    {
        std::cout << str << "\n\tNodes:\t[";
        for (auto v : vertices_)
            std::cout << v << ", ";
        std::cout << "]\n";

        if (!printEdges)
            return;

        std::cout << "\tEdges:  * [v1 -> v2]: distance\n";

        for (auto edgeList : edges_)
        {
            for (auto edge : edgeList.second)
                std::cout << "\t\t* [" << edgeList.first << "  ->  " << edge.first << "]: " << edge.second << "\n";
        }
    }

    bool CompleteGraph::addVertexIfNotExists(int v)
    {
        auto existingVertex = std::find(vertices_.begin(), vertices_.end(), v);
        if (existingVertex != vertices_.end())
            return false;

        vertices_.push_back(v);
        return true;
    }

    bool CompleteGraph::addVertexWithUserInput()
    {
        int v;

        bool alreadyExists = true;
        int tries = 5;
        do
        {
            tries--;
            std::cout << "Enter an integer number to add a new node: ";
            std::cin >> v;
            std::cin.sync();
            std::cout << "Entered node number is: " << v << "\n";
            auto existingVertex = std::find(vertices_.begin(), vertices_.end(), v);
            alreadyExists = (existingVertex != vertices_.end());
            if (alreadyExists)
                std::cout << "Node " << v << " already exists. " << tries << " attempts remaining\n";
        } while (alreadyExists && (tries > 0));

        if (tries == 0)
        {
            std::cout << "All attempts are exhausted\n";
            return false;
        }

        Vertices verticesCopy = vertices();
        for (auto existingVertex : verticesCopy)
        {
            int w;
            std::cout << "Enter a positive integer for the distance between nodes " << v << " -> " << existingVertex << ": ";
            std::cin >> w;
            std::cin.sync();
            std::cout << "Adding edge: [" << v << "  ->  " << existingVertex << "]: " << w << "\n";
            addEdge(v, existingVertex, w);
        }
    }

    bool CompleteGraph::addEdge(int a, int b, int w)
    {
        addVertexIfNotExists(a);
        addVertexIfNotExists(b);

        if (edges_.find(a) == edges_.end())
            edges_[a] = std::unordered_map<int, int>{{b, w}};
        else
        {
            if (edges_.at(a).find(b) == edges_.at(a).end())
                edges_.at(a)[b] = w;
            else
                return false;
        }

        if (edges_.find(b) == edges_.end())
            edges_[b] = std::unordered_map<int, int>{{a, w}};
        else
        {
            if (edges_.at(b).find(a) == edges_.at(b).end())
                edges_.at(b)[a] = w;
            else
                return false;
        }

        return true;
    }

    bool CompleteGraph::removeEdge(int a, int b)
    {
        auto edgesFromA = edges_.find(a);
        if (edgesFromA == edges_.end())
            return false;

        auto edgeFromAtoB = edgesFromA->second.find(b);
        if (edgeFromAtoB == edgesFromA->second.end())
            return false;

        edgesFromA->second.erase(b);

        if (edgesFromA->second.empty())
            edges_.erase(a);

        auto edges_FromB = edges_.find(b);
        if (edges_FromB == edges_.end())
            return false;

        auto edgeFromBtoA = edges_FromB->second.find(a);
        if (edgeFromBtoA == edges_FromB->second.end())
            return false;

        edges_FromB->second.erase(a);

        if (edges_FromB->second.empty())
            edges_.erase(b);
    }

    bool CompleteGraph::removeVertexWithUserInput()
    {
        if (vertices_.size() <= 2)
        {
            std::cout << "Minimum 2 nodes need to be present in the graph. Cannot remove any nodes at the moment\n";
            return false;
        }

        int v;
        print(std::string("Current Graph:"), false);

        bool exists = false;
        int tries = 5;
        do
        {
            tries--;
            std::cout << "Enter node number to remove: ";
            std::cin >> v;
            std::cin.sync();
            std::cout << "Entered node number is: " << v << "\n";
            auto existingVertex = std::find(vertices_.begin(), vertices_.end(), v);
            exists = (existingVertex != vertices_.end());
            if (!exists)
                std::cout << "Node " << v << " does not exist. " << tries << " attempts remaining\n";
        } while (!exists && (tries > 0));

        if (tries == 0)
        {
            std::cout << "All attempts are exhausted\n";
            return false;
        }

        removeVertex(v);
    }

    bool CompleteGraph::removeVertex(int v)
    {
        auto existingVertex = std::find(vertices_.begin(), vertices_.end(), v);
        if (existingVertex == vertices_.end())
            return false;

        vertices_.erase(existingVertex);

        for (auto edgeFromV : edges_[v])
        {
            edges_.at(edgeFromV.first).erase(v);

            if (edges_.at(edgeFromV.first).empty())
                edges_.erase(edgeFromV.second);
        }

        edges_.erase(v);
    }

    void CompleteGraph::computeTSP()
    {
        std::cout << "Computing the fastest route...\n";
        std::string minPath;
        int minCost = INT_MAX;
        do
        {
            int cost = 0;
            std::string path = std::to_string(vertices_[0]);
            for (int i = 0; i < vertices_.size(); i++)
            {
                cost += edges_[vertices_[i % vertices_.size()]][vertices_[(i + 1) % vertices_.size()]];
                path += std::string(" -> ") + std::to_string(vertices_[(i + 1) % vertices_.size()]);
            }

            if (cost < minCost)
            {
                minCost = cost;
                minPath = path;
            }

        } while (std::next_permutation(vertices_.begin(), vertices_.end()));

        std::cout << "Fastest route: " << minPath << std::endl;
        std::cout << "Distance: " << minCost << std::endl;
    }
}