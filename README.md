# Smart Valet Parking Service — C++ Data Structures

> **Repository-name note:** the repository name is historical. The code currently stored here is a **Smart Valet Parking Service** data-structures project, not an air-traffic routing implementation. This README describes the source code that is actually present.

A console-based C++ application for managing vehicles in a valet parking service. The project uses several custom data structures to support fast lookup, sorted views, deletion/undo, and persistent customer records.

## Features

- load customer/vehicle records from a text file;
- add newly parked vehicles;
- remove vehicles when they leave;
- search by license plate or customer name;
- display records in multiple sorted/unsorted views;
- maintain separate binary-search-tree indexes;
- use a hash table for plate-based lookup;
- keep an undo stack for deleted records;
- calculate a parking charge from elapsed time;
- write/backup customer data.

## Data structures

| Structure | Role |
| --- | --- |
| Hash table | Primary lookup by license plate |
| Binary search tree | Sorted/indexed lookup by plate |
| Binary search tree | Secondary ordering by customer name |
| Stack | Undo history for deleted vehicles |
| Array | In-memory customer record storage |

The repository includes custom implementations in files such as `Hash.h`, `BinaryTree.h`, `BinarySearchTreePlate.h`, `BinarySearchTreeName.h`, and `Stack.h`.

## Build

The code was written for Visual Studio/MSVC and uses `localtime_s`.

From a Visual Studio Developer Command Prompt:

```bat
cl /EHsc main.cpp CustomerData.cpp
```

Then run:

```bat
main.exe
```

The program reads its initial records from `customerInfo.txt`.

## Input format

Each record follows this shape:

```text
<plate> <brand> <customer name>
```

For example:

```text
I415HKH Tesla John Plemmons
E068UHK Porsche Ada Lovelace
```

## Repository guide

| File | Purpose |
| --- | --- |
| `main.cpp` | Application menu and orchestration |
| `CustomerData.h/.cpp` | Customer/vehicle model and time calculations |
| `Hash.h` | Hash-table implementation |
| `BinaryTree.h` | Base binary-tree implementation |
| `BinarySearchTreePlate.h` | Plate-keyed BST |
| `BinarySearchTreeName.h` | Name-keyed BST |
| `Stack.h` | Undo stack |
| `customerInfo.txt` | Sample input records |
| `BackUp.txt` | Historical backup/output data |

## Project context

This was a team academic project. The original source header credits **Tung Lin Lee** as the primary programmer and **Hoang Duong Vu** with function development, with additional team members contributing stability/testing work. Those original attributions are preserved here so the portfolio description matches the source history.

## What this project demonstrates

The project is primarily a data-structures exercise: the same domain records are indexed in different ways so the program can support **fast key lookup, sorted traversal, secondary-key access, and reversible deletion** without relying on standard-library containers for every operation.
