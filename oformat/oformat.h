/*********************************************************************
The format to out put numbers
 *********************************************************************/

#ifndef FORMATE1
#define FORMATE1 "%.5e\n"
#endif

#ifndef FORMATE2
#define FORMATE2 "%.5e %.5e\n"
#endif

#ifndef FORMATE3
#define FORMATE3 "%.5e %.5e %.5e\n"
#endif

#ifndef FORMATE4
#define FORMATE4 "%.5e %.5e %.5e %.5e\n"
#endif

#ifndef PRINT_Dividing_line
#include <iostream>
#include <iomanip> 
#define PRINT_Dividing_line(flag)\
  std::cout<<std::setfill(flag)\
           <<std::setw(79)\
           <<flag\
           <<std::endl
#endif
