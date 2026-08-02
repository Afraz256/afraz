#ifndef CART_H
#define CART_H

#include "Course.h"

class Cart {
private:
    Course* courses;
    int count;
    double totalCost;

    // Static so it belongs to the class, not to every Cart object. As a plain
    // const member it also silently deleted the assignment operator below,
    // because you can't assign to a const.
    static constexpr double TAX_RATE = 0.13;

public:
    Cart();
    ~Cart();

    // Cart owns raw memory, so the compiler's default copies would be shallow
    // and two Carts would end up deleting the same array. Rule of Three.
    Cart(const Cart& other);
    Cart& operator=(const Cart& other);

    void addCourse(const Course& course);
    void listCourses() const;
    void checkout();
    bool isEmpty() const;
    void clear();

    double getSubtotal() const;
    double getTotalWithTax() const;
};

#endif
