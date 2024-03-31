//
// Created by Kacper Kuchta on 3/28/24.
//

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <stdexcept>
#include <limits>
constexpr size_t MAX_CAPACITY = std::numeric_limits<size_t>::max();
constexpr size_t ROOT_INDEX = 0;

template <class T>
class PriorityQueue
{
public:
    class PriorityQueueElement
    {
    public:
        int priority{};
        T element{};

        PriorityQueueElement()
        = default;

        PriorityQueueElement(const int priority, const T& element)
            : priority(priority),
              element(element)
        {
        }
    };

    size_t current_size{};
    size_t current_capacity{};
    PriorityQueueElement* priority_queue_array;

    static size_t get_parent_index(const size_t index)
    {
        return (index - 1) / 2;
    }

    static size_t get_left_child_index(const size_t index)
    {
        return index * 2 + 1;
    }

    static size_t get_right_child_index(const size_t index)
    {
        return index * 2 + 2;
    }

    void grow()
    {
        if (current_capacity == MAX_CAPACITY)
        {
            throw std::overflow_error("Max size reached");
        }
        size_t new_capacity;
        if (current_capacity >= MAX_CAPACITY / 2)
        {
            new_capacity = MAX_CAPACITY;
        }
        else
        {
            new_capacity = current_capacity * 2;
        }

        auto* new_array = new PriorityQueueElement[new_capacity]{};
        for (int i = 0; i < current_size; ++i)
        {
            new_array[i] = priority_queue_array[i];
        }
        delete[] priority_queue_array;
        priority_queue_array = new_array;
    }

    explicit PriorityQueue(
        const size_t initial_capacity
    )
        :
        current_capacity(initial_capacity), priority_queue_array(new PriorityQueueElement[initial_capacity])
    {
        if (initial_capacity < 1)
        {
            throw std::invalid_argument("Capacity must be 1 or higher");
        }
    }

    void insert(const T& element, const int priority)
    {
        if (current_size >= current_capacity)
        {
            grow();
        }
        size_t insertion_index = current_size;
        ++current_size;

        while (insertion_index > 0)
        {
            size_t parent_index = get_parent_index(insertion_index);

            // Compare with parent and swap if necessary
            if (priority > priority_queue_array[parent_index].priority)
            {
                std::swap(priority_queue_array[insertion_index], priority_queue_array[parent_index]);
            }
            else
            {
                break; // Heap property restored
            }

            insertion_index = parent_index;
        }
        priority_queue_array[insertion_index] = PriorityQueueElement(priority, element);
    }

    const PriorityQueueElement& peek()
    {
        if (current_size <= 0)
        {
            throw std::underflow_error("Heap is empty!");
        }
        return priority_queue_array[ROOT_INDEX];
    }

    const PriorityQueueElement pop()
    {
        if (current_size <= 0)
        {
            throw std::underflow_error("Heap is empty!");
        }
        PriorityQueueElement element = priority_queue_array[ROOT_INDEX];
        priority_queue_array[ROOT_INDEX] = priority_queue_array[current_size - 1];

        size_t parent_index = ROOT_INDEX;
        size_t left_child_index, right_child_index, largest_element_index;

        while (parent_index < current_capacity)
        {
            largest_element_index = parent_index;

            left_child_index = get_left_child_index(parent_index);
            right_child_index = get_right_child_index(parent_index);

            if (left_child_index < current_capacity && priority_queue_array[left_child_index].priority >
                priority_queue_array[
                    largest_element_index].priority)
            {
                largest_element_index = left_child_index;
            }

            if (right_child_index < current_capacity && priority_queue_array[right_child_index].priority >
                priority_queue_array[
                    largest_element_index].priority)
            {
                largest_element_index = right_child_index;
            }

            if (largest_element_index == parent_index)
            {
                break;
            }

            std::swap(priority_queue_array[parent_index], priority_queue_array[largest_element_index]);

            parent_index = largest_element_index;
        }

        current_size--;
        return element;
    }

    size_t size()
    {
        return current_size;
    }

    void print()
    {
        for (int i = 0; i < current_size; ++i)
        {
            std::cout << priority_queue_array[i].priority << " ";
        }
        std::cout << std::endl;
    }
};
#endif //PRIORITYQUEUE_H
