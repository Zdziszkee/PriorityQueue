#include <iostream>
#include <string>
#include <sstream>
#include "PriorityQueue.hpp"

int main()
{
    PriorityQueue<std::string> priority_queue(64);
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        std::string operation, id;

        iss >> operation;
        if (operation == "ADD")
        {
            int priority;
            iss >> id >> priority;
            priority_queue.insert(id, priority);
        }
        else if (operation == "REMOVE")
        {
            if (priority_queue.size() == 0)
            {
                std::cout << "EMPTY" << std::endl;
            }
            else
            {
                std::cout << priority_queue.pop().element << std::endl; // Access the ID
            }
        }
        else if (operation == "PEEK")
        {
            if (priority_queue.size() == 0)
            {
                std::cout << "EMPTY" << std::endl;
            }
            else
            {
                std::cout << priority_queue.peek().element << std::endl; // Access the ID
            }
        }
    }

    return 0;
}
