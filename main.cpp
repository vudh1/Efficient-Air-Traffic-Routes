#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "BinarySearchTreeName.h"
#include "BinarySearchTreePlate.h"
#include "CustomerData.h"
#include "Hash.h"
#include "Stack.h"

constexpr int MAX_SIZE = 50;
constexpr int PARKING_RATE_CENTS_PER_MINUTE = 4;

void introduction();
int buildList(const char fileName[],
              BinarySearchTreePlate<customerData>& plateTree,
              BinarySearchTreeName<customerData>& nameTree,
              HashList<customerData>& hash,
              customerData data[]);

void menu(BinarySearchTreePlate<customerData>& plateTree,
          BinarySearchTreeName<customerData>& nameTree,
          HashList<customerData>& hash,
          customerData data[],
          int& countData);

void display(customerData& item);

void saveData(const char fileName[],
              const customerData data[],
              int countData);

int main()
{
    customerData data[MAX_SIZE];
    const char fileName[] = "customerInfo.txt";

    BinarySearchTreePlate<customerData> plateTree;
    BinarySearchTreeName<customerData> nameTree;
    HashList<customerData> hash;

    introduction();

    const int loaded = buildList(
        fileName, plateTree, nameTree, hash, data);

    if (loaded < 0)
        return 1;

    int countData = loaded;
    menu(plateTree, nameTree, hash, data, countData);

    saveData("BackUp.txt", data, countData);
    return 0;
}

void introduction()
{
    std::cout
        << "============================================================\n"
        << "              Smart Valet Parking Service\n"
        << "============================================================\n"
        << "Custom hash table + primary/secondary BST indexes + undo\n"
        << "Parking charge: " << PARKING_RATE_CENTS_PER_MINUTE
        << " cents per minute.\n\n";
}

int buildList(const char fileName[],
              BinarySearchTreePlate<customerData>& plateTree,
              BinarySearchTreeName<customerData>& nameTree,
              HashList<customerData>& hash,
              customerData data[])
{
    std::ifstream fin(fileName);
    if (!fin)
    {
        std::cerr << "Unable to open " << fileName << ".\n";
        return -1;
    }

    int count = 0;
    std::string plate;
    std::string brand;
    std::string name;

    while (count < MAX_SIZE && fin >> plate >> brand)
    {
        fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (!std::getline(fin, name))
            break;

        if (name.empty())
            continue;

        customerData record;
        record.setPlate(plate);
        record.setBrand(brand);
        record.setName(name);
        record.getTimeIn();

        if (!hash.add(record, plate))
            continue;

        plateTree.insert(record);
        nameTree.insert(record);
        data[count++] = record;
    }

    return count;
}

int findIndexByPlate(const customerData data[],
                     int countData,
                     const std::string& plate)
{
    for (int i = 0; i < countData; ++i)
    {
        if (data[i].getPlate() == plate)
            return i;
    }

    return -1;
}

void menu(BinarySearchTreePlate<customerData>& plateTree,
          BinarySearchTreeName<customerData>& nameTree,
          HashList<customerData>& hash,
          customerData data[],
          int& countData)
{
    Stack<customerData> undoList;

    while (true)
    {
        std::cout
            << "\n[A]dd  [D]elete  [S]earch  [L]ist\n"
            << "[W]rite [T]statistics [U]ndo  [Q]uit\n"
            << "Choice: ";

        char choice;
        std::cin >> choice;
        choice = static_cast<char>(
            std::tolower(static_cast<unsigned char>(choice)));

        if (choice == 'q')
            break;

        if (choice == 'a')
        {
            if (countData >= MAX_SIZE)
            {
                std::cout << "Parking capacity is full.\n";
                continue;
            }

            customerData record;
            std::string plate;
            std::string name;
            std::string brand;

            std::cout << "License plate: ";
            std::cin >> plate;

            if (hash.search(plate))
            {
                std::cout << "That plate is already parked.\n";
                continue;
            }

            std::cout << "Customer name: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n');
            std::getline(std::cin, name);

            std::cout << "Vehicle brand: ";
            std::cin >> brand;

            record.setPlate(plate);
            record.setName(name);
            record.setBrand(brand);
            record.getTimeIn();

            hash.add(record, plate);
            plateTree.insert(record);
            nameTree.insert(record);
            data[countData++] = record;

            std::cout << "Vehicle added.\n";
        }
        else if (choice == 'd')
        {
            std::string plate;
            std::cout << "License plate to remove: ";
            std::cin >> plate;

            const int index = findIndexByPlate(
                data, countData, plate);

            if (index < 0)
            {
                std::cout << "No vehicle with plate "
                          << plate << " was found.\n";
                continue;
            }

            customerData removed = data[index];
            removed.getTimeOut();

            const int minutes = removed.getTimeLength();
            const int charge = minutes * PARKING_RATE_CENTS_PER_MINUTE;

            hash.removeItem(plate);
            plateTree.remove(removed);
            nameTree.remove(removed);
            undoList.push(removed);

            for (int i = index; i + 1 < countData; ++i)
                data[i] = data[i + 1];

            --countData;

            std::cout << "Vehicle removed.\n"
                      << "Parking time: " << minutes << " minutes\n"
                      << "Charge: " << charge << " cents\n";
        }
        else if (choice == 's')
        {
            std::cout
                << "1 - Search by license plate\n"
                << "2 - Search by customer name\n"
                << "Choice: ";

            int searchChoice;
            std::cin >> searchChoice;

            if (searchChoice == 1)
            {
                std::string plate;
                std::cout << "License plate: ";
                std::cin >> plate;

                customerData key;
                key.setPlate(plate);
                customerData result;

                if (plateTree.getEntry(key, result))
                    std::cout << "Found: " << result << '\n';
                else
                    std::cout << "No matching vehicle.\n";
            }
            else if (searchChoice == 2)
            {
                std::string name;
                std::cout << "Customer name: ";
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, name);

                customerData key;
                key.setName(name);
                customerData result;

                if (nameTree.getEntry(key, result))
                    std::cout << "Found: " << result << '\n';
                else
                    std::cout << "No matching customer.\n";
            }
            else
            {
                std::cout << "Invalid search option.\n";
            }
        }
        else if (choice == 'l')
        {
            std::cout << "\nUnsorted records:\n";
            for (int i = 0; i < countData; ++i)
                std::cout << "  " << data[i] << '\n';

            std::cout << "\nSorted by license plate:\n";
            plateTree.inOrder(display);

            std::cout << "\nSorted by customer name:\n";
            nameTree.inOrder(display);
        }
        else if (choice == 'w')
        {
            if (hash.output())
                std::cout << "Hash-table order written to output.txt.\n";
            else
                std::cout << "Unable to write output.txt.\n";
        }
        else if (choice == 't')
        {
            hash.stattistic();
            std::cout << "Plate BST nodes: " << plateTree.size() << '\n';
            std::cout << "Name BST nodes: " << nameTree.size() << '\n';
        }
        else if (choice == 'u')
        {
            customerData restored;

            if (!undoList.pop(restored))
            {
                std::cout << "Nothing to undo.\n";
                continue;
            }

            if (countData >= MAX_SIZE ||
                hash.search(restored.getPlate()))
            {
                std::cout << "Cannot restore this vehicle.\n";
                undoList.push(restored);
                continue;
            }

            hash.add(restored, restored.getPlate());
            plateTree.insert(restored);
            nameTree.insert(restored);
            data[countData++] = restored;

            std::cout << "Last deletion undone: "
                      << restored << '\n';
        }
        else
        {
            std::cout << "Unknown option.\n";
        }
    }
}

void display(customerData& item)
{
    std::cout << item << '\n';
}

void saveData(const char fileName[],
              const customerData data[],
              int countData)
{
    std::ofstream fout(fileName);
    if (!fout)
    {
        std::cerr << "Unable to write " << fileName << ".\n";
        return;
    }

    for (int i = 0; i < countData; ++i)
    {
        fout << data[i].getPlate() << ' '
             << data[i].getBrand() << ' '
             << data[i].getName() << '\n';
    }
}
