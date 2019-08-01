Yakira Quemba
Sherzod Kariev
Qi Zheng

COP3331 Spring 2019
Project 2

---> Polymorphism -> string printHeader()
* Function Definitions for Polymorphism at:
   1. User.cpp - string User::printHeader(); lines: 14-18
   2. Student.cpp - string Student:printHeader(); lines:10 - 14
   3. Advisor.cpp - string Advisor::printHeader(); lines: 10 - 14
* Calling function at Proj2.cpp - lines: 10, 47, 55


---> Overloading -> string printHeader() and string printHeader(string ID)  
1. Function Definitions at:
   1. Student.cpp - string Student::printHeader(); lines: 10 - 14
   2. Student.cpp - string Student::printHeader(string ID); lines 16 - 20
2. Calling Function at: 
   1. Student.cpp: line 36
   2. Proj2.cpp: line 10 (If user login in as student)
     
     
---> Overriding  -> string printHeader()
* Function Declaration with virtual keyword at: User.h line:27
* Function Definition at User.cpp lines: 14-18    
* Function Declarations with override keyword at: Student.h line: 31 and Advisor.h line: 30
* Function Definition at: Student.cpp lines: 10-14 and Advisor.cpp lines: 14-18 
* Calling function at Proj2.cpp - lines: 10, 47, 55
      

---> STL containers (at least two) 
1. Vector 
   1. FileIO.cpp - lines: 27, 81, 91, 141, 149, 150, 266, 478, 618, 638, 666, 
   2. Student.cpp - lines: 24, 65, 69
   3. Advisor.cpp - lines: 238, 245, 493, 526, 623, 626, 632, 706
2. Map of Vector
   1. FileIO.cpp - lines: 139, 141, 616, 618, 
   2. Student.cpp - lines: 24, 65 
   3. Advisor.cpp - lines 245, 493, 526, 623, 706
       

---> STL algorithms (at least two) 
1. Sort 
   1. Advisor.cpp - lines: 80 - 82, 94 - 96, 107 - 109
2. For_each 
   1. Advisor.cpp - lines: 85 - 88, 99 - 101, 112 - 114, 242 - 248

          
---> Function Template -> Advisor::display(T value); 
* Function Declaration at Advisor.h line 28-29;
* Function Definition at
   * Advisor.cpp - lines 8 - 12
* Calling Function at
   * Advisor.cpp: lines 40, 41, 64, 127, 172
       

---> Lambda Expression
1. Proj2.cpp - line: 10
2. Advisor.cpp - lines: 80 - 82, 85 - 88, 94 - 96, 99 - 101, 107 - 109, 112 - 114, 242-248, 724-726

            
---> Exception Handling
* Custom Exception Struct Name: struct User::InvalidNumberTypeException; 
* Custom Exception Struct Declaration at User.h - line 29
* Custom Exception Struct Definition at User.cpp - line 32 
* Exception is throw if input contain any char, in other word, the exception will throw if input 
  is not a right type i.e. integer or double depends on the need.
* Try-Throw-Catch and Custom Exception Object at
   1. User.cpp - Function Name: void User::checkDigit; lines 35 - 65
* Using function void checkDigit at
   1. Proj2.cpp - line 33
   2. Student.cpp - lines 43, 123, 196, 239
   3. Advisor.cpp - lines 45, 132, 177, 212