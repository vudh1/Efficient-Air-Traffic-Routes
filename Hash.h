#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <fstream>
#include <functional>
#include <iostream>
#include <string>

template <class ItemType>
class HashList
{
private:
    static const int TABLE_SIZE = 50;

    struct Item
    {
        std::string code;
        Item* next;
        ItemType data;

        Item(const std::string& codeValue, const ItemType& dataValue)
            : code(codeValue), next(nullptr), data(dataValue)
        {
        }
    };

    int itemCount;
    Item* hashTable[TABLE_SIZE];

    void clear();
    int bucketSize(int index) const;

public:
    HashList();
    ~HashList();

    HashList(const HashList&) = delete;
    HashList& operator=(const HashList&) = delete;

    int hashAddress(const std::string& key) const;
    bool removeItem(const std::string& code);
    bool search(const std::string& code) const;
    bool add(const ItemType& data, const std::string& plateNum);
    void printTable() const;
    void printItemsInIndex(int index) const;
    bool output(const std::string& fileName = "output.txt") const;
    void stattistic() const;
    int size() const { return itemCount; }
};

template <class ItemType>
HashList<ItemType>::HashList() : itemCount(0)
{
    for (auto& bucket : hashTable)
        bucket = nullptr;
}

template <class ItemType>
HashList<ItemType>::~HashList()
{
    clear();
}

template <class ItemType>
void HashList<ItemType>::clear()
{
    for (auto& bucket : hashTable)
    {
        while (bucket != nullptr)
        {
            Item* next = bucket->next;
            delete bucket;
            bucket = next;
        }
    }
    itemCount = 0;
}

template <class ItemType>
int HashList<ItemType>::hashAddress(const std::string& key) const
{
    // Deterministic polynomial hash. A key must map to the same bucket
    // for add/search/remove to remain consistent.
    std::size_t hash = 0;
    for (unsigned char ch : key)
        hash = hash * 31u + ch;

    return static_cast<int>(hash % TABLE_SIZE);
}

template <class ItemType>
bool HashList<ItemType>::add(const ItemType& entryData,
                             const std::string& encode)
{
    if (encode.empty() || search(encode))
        return false;

    const int index = hashAddress(encode);
    Item* node = new Item(encode, entryData);

    if (hashTable[index] == nullptr)
    {
        hashTable[index] = node;
    }
    else
    {
        Item* tail = hashTable[index];
        while (tail->next != nullptr)
            tail = tail->next;
        tail->next = node;
    }

    ++itemCount;
    return true;
}

template <class ItemType>
bool HashList<ItemType>::removeItem(const std::string& encode)
{
    const int index = hashAddress(encode);
    Item* current = hashTable[index];
    Item* previous = nullptr;

    while (current != nullptr)
    {
        if (current->code == encode)
        {
            if (previous == nullptr)
                hashTable[index] = current->next;
            else
                previous->next = current->next;

            delete current;
            --itemCount;
            return true;
        }

        previous = current;
        current = current->next;
    }

    return false;
}

template <class ItemType>
bool HashList<ItemType>::search(const std::string& encode) const
{
    const int index = hashAddress(encode);
    const Item* current = hashTable[index];

    while (current != nullptr)
    {
        if (current->code == encode)
            return true;
        current = current->next;
    }

    return false;
}

template <class ItemType>
void HashList<ItemType>::printTable() const
{
    std::cout << "\nThe number of cars is: " << itemCount << '\n';
    std::cout << "Listed by plate number (primary key):\n";

    for (int i = 0; i < TABLE_SIZE; ++i)
        printItemsInIndex(i);
}

template <class ItemType>
void HashList<ItemType>::printItemsInIndex(int index) const
{
    if (index < 0 || index >= TABLE_SIZE)
        return;

    const Item* current = hashTable[index];
    if (current == nullptr)
        return;

    std::cout << "--------------------------\n";
    std::cout << "index [" << index << "] contains:\n";

    while (current != nullptr)
    {
        std::cout << current->data << '\n';
        current = current->next;
    }
}

template <class ItemType>
bool HashList<ItemType>::output(const std::string& fileName) const
{
    std::ofstream fout(fileName);
    if (!fout)
        return false;

    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        const Item* current = hashTable[i];
        while (current != nullptr)
        {
            fout << current->code << ' ' << current->data << '\n';
            current = current->next;
        }
    }

    return true;
}

template <class ItemType>
int HashList<ItemType>::bucketSize(int index) const
{
    int count = 0;
    const Item* current = hashTable[index];

    while (current != nullptr)
    {
        ++count;
        current = current->next;
    }

    return count;
}

template <class ItemType>
void HashList<ItemType>::stattistic() const
{
    int usedBuckets = 0;
    int longestChain = 0;

    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        const int size = bucketSize(i);
        if (size > 0)
            ++usedBuckets;
        if (size > longestChain)
            longestChain = size;
    }

    const double loadFactor =
        static_cast<double>(itemCount) / TABLE_SIZE;

    std::cout << "Hash table buckets: " << TABLE_SIZE << '\n';
    std::cout << "Stored records: " << itemCount << '\n';
    std::cout << "Used buckets: " << usedBuckets << '\n';
    std::cout << "Load factor: " << loadFactor << '\n';
    std::cout << "Longest chain: " << longestChain << '\n';
}

#endif
