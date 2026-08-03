# Course Management System

A console program for running a college course catalogue. One binary, two roles. Students
browse departments and add courses to a cart. Admins create departments and courses, then
save everything to a CSV file.

Written for PRG210. Departments and courses are kept in dynamically allocated arrays that
the code resizes by hand, not in STL containers.

## Build and run

```bash
make
./cms
```

`make clean` deletes the binary. The Makefile pins `-std=c++11`, so the build behaves the
same on every machine. Without make:

```bash
g++ -std=c++11 -o cms *.cpp
```

## File structure

```
PRG210-Project/
├── main.cpp                  Globals, role menu, polymorphic call
├── Interface.h/.cpp          Abstract base, shared input checking
├── AdminInterface.h/.cpp     Admin menus
├── StudentInterface.h/.cpp   Student menus
├── Course.h/.cpp             One course
├── Department.h/.cpp         A department name and its courses
├── Cart.h/.cpp               Chosen courses and the tax total
├── CSVUtils.h/.cpp           Reads and writes data.csv
├── data.csv                  Seed data, 3 departments and 9 courses
├── Makefile
└── .gitignore
```

**main.cpp** declares the three globals the program shares: `StoreDepartments`,
`TotalDepartments` and `csvFile`. Every other file reaches them with `extern`. It loads the
CSV, then runs the role menu. Choosing a role builds the matching interface and calls
`run()` through an `Interface*`, which is where the polymorphism happens.

**Interface.h/.cpp** is abstract. `run()` is pure virtual, so the class cannot be created on
its own. The input checking both roles need sits here: menu numbers, non-empty text, and
positive prices. The destructor is virtual because `main` deletes through a base pointer.

**AdminInterface.h/.cpp** inherits from `Interface`. Lists departments, adds a department,
adds a course to an existing department, and triggers a save.

**StudentInterface.h/.cpp** inherits from `Interface` and owns a `Cart`. Browses
departments, lists their courses, adds courses to the cart, and checks out.

**Course.h/.cpp** stores a course number, name, schedule and price. Every member is a
`std::string` or a `double`, so nothing sits on the heap and no destructor is needed.

**Department.h/.cpp** stores a name in a character array plus a dynamically allocated array
of courses. It owns that memory, so it defines a destructor, a copy constructor and an
assignment operator. `addCourse` allocates a larger array, copies the old courses across,
and frees the old one.

**Cart.h/.cpp** stores the courses a student picked, keeps a running subtotal, and adds 13%
tax. Same memory ownership as `Department`.

**CSVUtils.h/.cpp** is the only file that touches `data.csv`. If the file is missing it
creates one, so a fresh clone still runs.

## Using it

The program opens on a role menu.

```
1. Student
2. Admin
3. Exit
```

**As a student**, browse departments to see what each one offers, pick a course number to
put it in your cart, then open the cart to list what you picked or check out. The cart
prints a subtotal, 13% tax, and a total. Checking out empties it.

**As an admin**, list the current departments, add a new one, or add a course to a
department that already exists. A course needs a number, a name, a schedule of `M/W`, `T/R`
or `W/F`, and a positive price. Nothing reaches the file until you choose Save Changes to
CSV.

Every prompt rejects bad input and asks again. Departments cannot be added twice under the
same name, and a name that is only spaces is refused.

## CSV format

```
<department count>
<department name>, <course count>
<course number>, <course name>, <schedule>, <price>
```

For example:

```
3
Computer Programming, 4
PRG110, Introduction to Programming, M/W, 425.00
```

## A note on data.csv

`data.csv` is tracked in git. Saving during a demo rewrites it, so `git status` will show it
as modified afterwards. That is expected. Just avoid committing a throwaway demo save over
the seed data.
