#include <graph.h>

int main(int argc, char const *argv[])
{
    graph::CompleteGraph graph;

    // Example graph
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 15);
    graph.addEdge(1, 4, 20);
    graph.addEdge(2, 3, 35);
    graph.addEdge(2, 4, 25);
    graph.addEdge(3, 4, 30);

    char menuStream[1024];
    sprintf(menuStream, "The following options are available for interacting with this program:\n'h': Print this help message\n'p': Print current graph\n'c': Compute fastest route\n'a': Add new node\n'r': Remove existing node\n'q': Exit program");
    char requestStream[1024];
    sprintf(requestStream, "Enter command here: ");
    char invalidStream[1024];
    sprintf(invalidStream, "Input command is invalid");

    std::cout << std::endl;
    std::cout << std::string(menuStream) << std::endl;

    char command = 'h';
    do
    {
        std::cout << std::endl;
        std::cout << requestStream;
        std::cin >> command;
        std::cin.sync();
        std::cout << "Entered command is: " << command << std::endl
                  << std::endl;
        switch (command)
        {
        case 'p':
            graph.print();
            break;

        case 'c':
            graph.computeTSP();
            break;

        case 'a':
            if (graph.addVertexWithUserInput())
                graph.print("Updated Graph:");
            break;

        case 'r':
            if (graph.removeVertexWithUserInput())
                graph.print("Updated Graph:");
            break;

        case 'q':
            std::cout << "Exiting now...\n";
            break;

        case 'h':
            std::cout << std::endl;
            std::cout << std::string(menuStream) << std::endl;
            break;

        default:
            std::cout << invalidStream << std::endl
                      << std::endl;
            std::cout << menuStream << std::endl;
            break;
        }
    } while (command != 'q');

    return 0;
}
