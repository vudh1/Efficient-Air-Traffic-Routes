# Smart Valet Parking Service — C++ Data Structures

> **Historical repository name:** `Efficient-Air-Traffic-Routes`. The source in this repository is a **Smart Valet Parking Service** project; it is not an air-traffic routing implementation.

![C++ CI](https://github.com/vudh1/Efficient-Air-Traffic-Routes/actions/workflows/ci.yml/badge.svg)

![Animated demo](demo.gif)

A console-based C++ application that manages parked vehicles using custom data structures. Each vehicle is indexed multiple ways so the program can demonstrate hash-table lookup, binary-search-tree ordering, deletion, undo, statistics, and file persistence.

## What the project demonstrates

- **Hash table** for license-plate lookup with separate chaining.
- **Plate-keyed BST** for primary-key ordered traversal.
- **Name-keyed BST** for secondary-key lookup and sorted traversal.
- **Stack** for last-in-first-out undo of deletions.
- **Queue** used by breadth-first tree traversal.
- **Fixed-size record array** for the active parking inventory.
- Parking-duration and charge calculation.
- Persistence through `customerInfo.txt`, `output.txt`, and `BackUp.txt`.

## Architecture

```text
                         +----------------------+
                         |   Customer Records   |
                         +----------+-----------+
                                    |
              +---------------------+---------------------+
              |                     |                     |
              v                     v                     v
       Hash<plate>            BST<plate>             BST<name>
        O(1) avg.              ordered                 ordered
              |                     |                     |
              +---------------------+---------------------+
                                    |
                                    v
                              Parking menu
                                    |
                       +------------+------------+
                       |                         |
                    Delete                    Undo
                       |                         |
                       v                         v
                  Stack<T>  <--------------- restore
```

## Demo

The repository contains a small deterministic executable in `demo.cpp`. It exercises the same repaired data structures used by the application:

1. Insert four vehicles.
2. Look up a vehicle through the hash table.
3. Traverse both BST indexes.
4. Delete a vehicle.
5. Restore it through the undo stack.
6. Print index statistics.

The animated GIF is generated from the executable's real output, so it stays synchronized with the demo as the code changes.

## Build

### CMake

Requirements:

- CMake 3.16+
- C++17 compiler

Linux/macOS:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure

./build/valet
./build/valet_demo
```

Windows:

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure

.uildReleasealet.exe
.uildReleasealet_demo.exe
```

The original project was developed with Visual Studio/MSVC. The current code also supports POSIX `localtime_r` so the automated Linux build can exercise the same source.

## Tests

`tests/data_structure_smoke.cpp` covers the core invariants:

- deterministic hash lookup and removal;
- duplicate plate rejection;
- hash record counts;
- plate BST insertion, lookup, deletion, and deep copy;
- name BST lookup and deletion;
- queue front/rear/dequeue behavior;
- stack push/pop behavior.

GitHub Actions builds the application and runs the smoke tests on every push and pull request.

## Input format

Each active record uses:

```text
<license-plate> <brand> <customer name>
```

Example:

```text
I415HKH Tesla John Plemmons
E068UHK Porsche Ada Lovelace
```

The sample file contains 25 records. The application has a maximum active capacity of 50 records.

## Data structures and complexity

| Structure | Operation | Typical complexity |
| --- | --- | --- |
| Hash table | plate search | O(1) average |
| Hash table | insert/remove | O(1) average |
| BST | search/insert/remove | O(log n) average |
| BST | search/insert/remove | O(n) worst case |
| Stack | undo push/pop | O(1) |
| Active array | delete/compact | O(n) |

The hash function is deterministic. This is important because the same license plate must resolve to the same bucket during insert, search, and removal.

## Improvements in this revision

The original academic implementation had several correctness and maintainability issues. The current version fixes them without changing the project's core data-structure design:

- deterministic hashing instead of a time-dependent bucket calculation;
- no per-lookup hash-array memory leak;
- correct hash record counts after deletion;
- duplicate license-plate protection;
- safe hash-table destruction;
- deep-copy support for the binary-tree base class;
- correct BST node counts;
- corrected queue rear return value;
- portable local-time handling for Windows and POSIX;
- robust file parsing without the classic `while (!eof())` bug;
- correct active-record removal instead of leaving deleted vehicles in the array;
- repaired search logic and removed out-of-bounds indexing;
- undo now restores all three indexes and the active record list;
- backup now reflects the current active records;
- CMake + automated smoke tests;
- reproducible animated demo generation.

## Repository guide

| File | Purpose |
| --- | --- |
| `main.cpp` | Interactive application and workflow |
| `CustomerData.h/.cpp` | Vehicle/customer model and parking-time logic |
| `Hash.h` | Separate-chaining hash table |
| `BinaryTree.h` | Shared binary-tree ownership/traversal |
| `BinarySearchTreePlate.h` | License-plate BST |
| `BinarySearchTreeName.h` | Customer-name BST |
| `Stack.h` | Undo stack |
| `Queue.h` | Breadth-first traversal queue |
| `demo.cpp` | Deterministic portfolio/demo executable |
| `tests/data_structure_smoke.cpp` | Core data-structure tests |
| `CMakeLists.txt` | Portable build/test configuration |
| `customerInfo.txt` | Sample active records |

## Historical context

This was originally a CIS 22C team academic project. The source attribution in the original files is preserved rather than rewriting the project's history.

The repository name is historical and does not describe the implementation currently stored here.
