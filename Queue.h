#ifndef DYNAMICQUEUE_H
#define DYNAMICQUEUE_H

#include <iostream>

template <class T>
class Queue
{
private:
    struct QueueNode
    {
        T value;
        QueueNode* next;
    };

    QueueNode* front;
    QueueNode* rear;
    int count;

public:
    Queue() : front(nullptr), rear(nullptr), count(0) {}
    ~Queue();

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    bool enqueue(const T& item);
    bool dequeue(T& item);
    bool isEmpty() const;
    int getCount() const;
    bool queueFront(T& item) const;
    bool queueRear(T& item) const;
    void print() const;
};

template <class T>
Queue<T>::~Queue()
{
    while (front != nullptr)
    {
        QueueNode* next = front->next;
        delete front;
        front = next;
    }
    rear = nullptr;
    count = 0;
}

template <class T>
int Queue<T>::getCount() const
{
    return count;
}

template <class T>
bool Queue<T>::isEmpty() const
{
    return count == 0;
}

template <class T>
bool Queue<T>::enqueue(const T& item)
{
    QueueNode* node = new QueueNode{item, nullptr};

    if (rear == nullptr)
        front = rear = node;
    else
    {
        rear->next = node;
        rear = node;
    }

    ++count;
    return true;
}

template <class T>
bool Queue<T>::dequeue(T& item)
{
    if (front == nullptr)
        return false;

    QueueNode* oldFront = front;
    item = oldFront->value;
    front = oldFront->next;

    if (front == nullptr)
        rear = nullptr;

    delete oldFront;
    --count;
    return true;
}

template <class T>
bool Queue<T>::queueFront(T& item) const
{
    if (front == nullptr)
        return false;

    item = front->value;
    return true;
}

template <class T>
bool Queue<T>::queueRear(T& item) const
{
    if (rear == nullptr)
        return false;

    item = rear->value;
    return true;
}

template <class T>
void Queue<T>::print() const
{
    QueueNode* current = front;
    while (current != nullptr)
    {
        std::cout << current->value << '
';
        current = current->next;
    }
}

#endif
