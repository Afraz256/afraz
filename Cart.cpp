#include "Cart.h"
#include <iostream>
#include <iomanip>

Cart::Cart() : courses(nullptr), count(0), totalCost(0.0) {}

Cart::~Cart() {
    clear();
}

void Cart::clear() {
    delete[] courses;
    courses = nullptr;
    count = 0;
    totalCost = 0.0;
}

bool Cart::isEmpty() const {
    return count == 0;
}

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
    double tax = totalCost * TAX_RATE;
    double finalCost = totalCost + tax;
    std::cout << "--------------------" << std::endl;
    std::cout << "Subtotal: $" << totalCost << std::endl;
    std::cout << "Tax (13%): $" << tax << std::endl;
    std::cout << "Total Cost: $" << finalCost << std::endl;
}

void Cart::checkout() {
    if (isEmpty()) {
        std::cout << "\nNo courses in the cart" << std::endl;
    } else {
        std::cout << "\nThank you for your purchase!" << std::endl;
        clear();
    }
}