#include <cassert>

#include "../BinarySearchTreeName.h"
#include "../BinarySearchTreePlate.h"
#include "../CustomerData.h"
#include "../Hash.h"
#include "../Queue.h"
#include "../Stack.h"

static customerData record(const char* plate,
                           const char* name,
                           const char* brand)
{
    customerData item;
    item.setPlate(plate);
    item.setName(name);
    item.setBrand(brand);
    return item;
}

int main()
{
    customerData a = record("A100AAA", "Ada Lovelace", "Porsche");
    customerData b = record("B200BBB", "Grace Hopper", "Tesla");
    customerData c = record("C300CCC", "Alan Turing", "BMW");

    HashList<customerData> hash;
    assert(hash.add(a, a.getPlate()));
    assert(hash.add(b, b.getPlate()));
    assert(!hash.add(a, a.getPlate()));
    assert(hash.search("A100AAA"));
    assert(hash.search("B200BBB"));
    assert(hash.size() == 2);
    assert(hash.removeItem("A100AAA"));
    assert(!hash.search("A100AAA"));
    assert(hash.size() == 1);

    BinarySearchTreePlate<customerData> plateTree;
    assert(plateTree.insert(a));
    assert(plateTree.insert(b));
    assert(plateTree.insert(c));
    assert(!plateTree.insert(a));
    assert(plateTree.size() == 3);

    customerData plateKey;
    plateKey.setPlate("B200BBB");
    customerData found;
    assert(plateTree.getEntry(plateKey, found));
    assert(found.getName() == "Grace Hopper");

    BinarySearchTreePlate<customerData> copied = plateTree;
    assert(copied.size() == 3);
    assert(plateTree.remove(b));
    assert(plateTree.size() == 2);
    assert(copied.getEntry(plateKey, found));

    BinarySearchTreeName<customerData> nameTree;
    assert(nameTree.insert(a));
    assert(nameTree.insert(b));
    assert(nameTree.insert(c));

    customerData nameKey;
    nameKey.setName("Grace Hopper");
    assert(nameTree.getEntry(nameKey, found));
    assert(found.getPlate() == "B200BBB");
    assert(nameTree.remove(b));
    assert(nameTree.size() == 2);

    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);
    int value = 0;
    assert(queue.queueFront(value) && value == 10);
    assert(queue.queueRear(value) && value == 20);
    assert(queue.dequeue(value) && value == 10);
    assert(queue.dequeue(value) && value == 20);
    assert(queue.isEmpty());

    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    assert(stack.pop(value) && value == 2);
    assert(stack.pop(value) && value == 1);
    assert(stack.isEmpty());

    return 0;
}
