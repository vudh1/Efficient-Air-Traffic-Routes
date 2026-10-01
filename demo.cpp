#include <iostream>

#include "BinarySearchTreeName.h"
#include "BinarySearchTreePlate.h"
#include "CustomerData.h"
#include "Hash.h"
#include "Stack.h"

static customerData makeRecord(const char* plate,
                               const char* name,
                               const char* brand)
{
    customerData item;
    item.setPlate(plate);
    item.setName(name);
    item.setBrand(brand);
    return item;
}

static void display(customerData& item)
{
    std::cout << "  " << item << '\n';
}

int main()
{
    BinarySearchTreePlate<customerData> plateTree;
    BinarySearchTreeName<customerData> nameTree;
    HashList<customerData> hash;
    Stack<customerData> undo;

    const customerData records[] = {
        makeRecord("A100AAA", "Ada Lovelace", "Porsche"),
        makeRecord("B200BBB", "Grace Hopper", "Tesla"),
        makeRecord("C300CCC", "Alan Turing", "BMW"),
        makeRecord("D400DDD", "Katherine Johnson", "Volvo")
    };

    for (const auto& record : records)
    {
        hash.add(record, record.getPlate());
        plateTree.insert(record);
        nameTree.insert(record);
    }

    std::cout << "SMART VALET DATA STRUCTURE DEMO\n";
    std::cout << "Loaded records: " << hash.size() << "\n\n";

    std::cout << "1. Hash lookup\n";
    std::cout << "   B200BBB -> "
              << (hash.search("B200BBB") ? "FOUND" : "NOT FOUND")
              << "\n\n";

    std::cout << "2. Plate BST (in-order)\n";
    plateTree.inOrder(display);
    std::cout << '\n';

    std::cout << "3. Customer-name BST (in-order)\n";
    nameTree.inOrder(display);
    std::cout << '\n';

    customerData removed = records[1];
    hash.removeItem(removed.getPlate());
    plateTree.remove(removed);
    nameTree.remove(removed);
    undo.push(removed);

    std::cout << "4. Delete + undo\n";
    std::cout << "   After delete: "
              << (hash.search("B200BBB") ? "FOUND" : "NOT FOUND")
              << "\n";

    customerData restored;
    if (undo.pop(restored))
    {
        hash.add(restored, restored.getPlate());
        plateTree.insert(restored);
        nameTree.insert(restored);
    }

    std::cout << "   After undo:   "
              << (hash.search("B200BBB") ? "FOUND" : "NOT FOUND")
              << "\n\n";

    std::cout << "5. Index statistics\n";
    std::cout << "   Hash records: " << hash.size() << "\n";
    std::cout << "   Plate BST nodes: " << plateTree.size() << "\n";
    std::cout << "   Name BST nodes: " << nameTree.size() << "\n";
    hash.stattistic();

    return 0;
}
