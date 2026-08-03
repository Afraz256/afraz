#ifndef CART_H
#define CART_H

#include "Course.h"

/* What the student picked but hasn't paid for. Same heap array ownership as
   Department. */
class Cart {
private:
    Course* courses;
    int count;
    double totalCost;    // before tax

    /* Static so it belongs to the class, not to every Cart. As a plain const
       member it deleted the assignment operator below, with no error.
       fixed by L3I */
    static constexpr double TAX_RATE = 0.13;

public:
    Cart();
    ~Cart();

    // Bare pointer, so the defaults would be shallow. Same as Department.
    Cart(const Cart& other);
    Cart& operator=(const Cart& other);

    void addCourse(const Course& course);
    void listCourses() const;
    void checkout();
    bool isEmpty() const;
    void clear();

    double getSubtotal() const;
    double getTotalWithTax() const;   // added, fixed by L3I
};

#endif
