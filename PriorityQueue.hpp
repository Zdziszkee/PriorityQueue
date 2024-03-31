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


    bool is_root(const size_t index)
    {
        return index == ROOT_INDEX;
    }

    bool is_parent_smaller(const size_t index, const PriorityQueueElement& priority_queue_element)
    {
        size_t parent_index = get_parent_index(index);
        const PriorityQueueElement& parent = priority_queue_array[parent_index];
        return parent.priority < priority_queue_element.priority;
    }


    void swap(const size_t first, const size_t second)
    {
        PriorityQueueElement first_element = priority_queue_array[first];
        priority_queue_array[first] = priority_queue_array[second];
        priority_queue_array[second] = first_element;
    }

    size_t get_parent_index(const size_t index)
    {
        return (index - 1) / 2;
    }

    size_t get_left_child_index(const size_t index)
    {
        return index * 2 + 1;
    }

    size_t get_right_child_index(const size_t index)
    {
        return index * 2 + 2;
    }


    void heapifyUp(const PriorityQueueElement& priority_queue_element)
    {
        size_t insertion_index = current_size;
        while (!is_root(insertion_index) && is_parent_smaller(insertion_index, priority_queue_element))
        {
            size_t parent_index = get_parent_index(insertion_index);
            swap(insertion_index, parent_index);
            insertion_index = get_parent_index(insertion_index);
        }
        priority_queue_array[insertion_index] = priority_queue_element;
    }

    void heapifyDown(size_t parent)
    {
        size_t left_child, right_child, largest;

        while (parent < current_capacity)
        {
            largest = parent;

            left_child = get_left_child_index(parent);
            right_child = get_right_child_index(parent);

            if (left_child < current_capacity && priority_queue_array[left_child].priority > priority_queue_array[
                largest].priority)
            {
                largest = left_child;
            }

            if (right_child < current_capacity && priority_queue_array[right_child].priority > priority_queue_array[
                largest].priority)
            {
                largest = right_child;
            }

            if (largest == parent)
            {
                return;
            }

            swap(parent, largest);

            parent = largest;
        }
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
        PriorityQueueElement priority_queue_element(priority, element);
        heapifyUp(priority_queue_element);
        ++current_size;
    }

    const PriorityQueueElement& peek()
    {
        if (current_size <= 0)
        {
            throw std::underflow_error("Heap is empty!");
        }
        return priority_queue_array[ROOT_INDEX];
    }

    const PriorityQueueElement& pop()
    {
        if (current_size <= 0)
        {
            throw std::underflow_error("Heap is empty!");
        }
        PriorityQueueElement& element = priority_queue_array[ROOT_INDEX];
        priority_queue_array[ROOT_INDEX] = priority_queue_array[current_size - 1];
        current_size--;
        heapifyDown(ROOT_INDEX);
        return element;
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
