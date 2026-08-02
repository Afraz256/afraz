#include "Cart.h"
#include <iostream>
#include <iomanip>

Cart::Cart() : courses(nullptr), count(0), totalCost(0.0) {}

Cart::~Cart() {
    clear();
}

// Deep copy, same as Department's.
Cart::Cart(const Cart& other) {
    count = other.count;
    totalCost = other.totalCost;

    if (count > 0) {
        courses = new Course[count];
        for (int i = 0; i < count; ++i) {
            courses[i] = other.courses[i];
        }
    } else {
        courses = nullptr;
    }
}

Cart& Cart::operator=(const Cart& other) {
    // Guards c = c. Without it we free our array then read from it.
    if (this != &other) {
        delete[] courses;

        count = other.count;
        totalCost = other.totalCost;

        if (count > 0) {
            courses = new Course[count];
            for (int i = 0; i < count; ++i) {
                courses[i] = other.courses[i];
            }
        } else {
            courses = nullptr;
        }
    }
    return *this;
}

void Cart::clear() {
    delete[] courses;
    // checkout() empties the cart but the object lives on, so don't leave a
    // stale pointer here.
    courses = nullptr;
    count = 0;
    totalCost = 0.0;
}

bool Cart::isEmpty() const {
    return count == 0;
}

// Grow by one, same as Department::addCourse. Running subtotal so we don't
// walk the array every time.
void Cart::addCourse(const Course& course) {
    Course* temp = new Course[count + 1];

    for (int i = 0; i < count; ++i) {
        temp[i] = courses[i];
    }

    temp[count] = course;

    delete[] courses;
    courses = temp;

    count++;
    totalCost += course.getPrice();
}

void Cart::listCourses() const {
    if (isEmpty()) {
        std::cout << "\nCart is empty." << std::endl;
        return;
    }

    std::cout << "\n--- Shopping Cart ---" << std::endl;
    for (int i = 0; i < count; ++i) {
        std::cout << i + 1 << ". " << courses[i].getCourseNumber()
                  << " - " << courses[i].getCourseName()
                  << " | Schedule: " << courses[i].getSchedule()
                  << " | Price: $" << std::fixed << std::setprecision(2) << courses[i].getPrice() << std::endl;
    }
    std::cout << "--------------------" << std::endl;
    std::cout << "Subtotal: $" << getSubtotal() << std::endl;
    std::cout << "Tax (13%): $" << getSubtotal() * TAX_RATE << std::endl;
    std::cout << "Total Cost: $" << getTotalWithTax() << std::endl;
}

double Cart::getSubtotal() const {
    return totalCost;
}

double Cart::getTotalWithTax() const {
    return totalCost + (totalCost * TAX_RATE);
}

void Cart::checkout() {
    if (isEmpty()) {
        std::cout << "\nNo courses in the cart" << std::endl;
    } else {
        std::cout << "\nThank you for your purchase!" << std::endl;
        clear();
    }
}
