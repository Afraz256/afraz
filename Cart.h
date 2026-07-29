#ifndef CART_H
#define CART_H

#include "Course.h"

class Cart {
private:
    Course* courses;
    int count;
    double totalCost;
    const double TAX_RATE = 0.13;

public:
    Cart();
    ~Cart();
    Cart(const Cart& other);
    Cart& operator=(const Cart& other);

    void addCourse(const Course& course);
    void listCourses() const;
    void checkout();
    bool isEmpty() const;
    void clear();
};

#endif