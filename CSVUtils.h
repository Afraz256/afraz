#ifndef CSVUTILS_H
#define CSVUTILS_H

#include "Department.h"

/* All CSV work lives here so nothing else has to know the file format.
   Both return false when the read or write did not happen.

   File layout:
     <department count>
     <department name>, <course count>
     <course number>, <course name>, <schedule>, <price> */
bool loadFromCSV(const char* filename);
bool saveToCSV(const char* filename);

#endif
