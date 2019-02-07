/*main.cpp*/

//
// <<JAY V PATEL>>
// 
// Test cases for Counter container, which acts like a set but keeps a count
// of how many times each element was inserted.  
//
// References:
//   Unit testing based on Catch framework: https://github.com/catchorg/Catch2
//   Catch tutorial: https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top
//   install:     sudo apt-get install catch
//   compilation: g++ -std=c++11 -Wall -o main.exe main.cpp
//   execution:   ./main.exe
//

// let Catch provide main():
#define CATCH_CONFIG_MAIN

// gain access to Catch framework:
#include "catch.hpp"

// our Counter class:
#include "counter.h"

// *****************************************************************
//
// Test cases:
// 
// *****************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



TEST_CASE("empty Counter<int>", "[Counter]")
{
	Counter<int> C;

	REQUIRE(C.empty() == true);
	REQUIRE(C.size() == 0);

}//test


TEST_CASE("Counter<int> with 1 element", "[Counter]")
{
	Counter<int> C;

	REQUIRE(C.size() == 0);
	REQUIRE(C.empty() == true);

	SECTION("inserting element")
	{
		C.insert(123);

		REQUIRE(C.size() == 1);
		REQUIRE(!C.empty());

		SECTION("element contains")
		{
			REQUIRE(C[123] == true);

		}

		SECTION("element count")
		{
			REQUIRE(C(123) == 1);
		}

		SECTION("unknown elements not contained")
		{
			REQUIRE(!C[0]);
			REQUIRE(!C[122]);
			REQUIRE(!C[124]);

		}

		SECTION("unknown element counts")
		{
			REQUIRE(C(0) == 0);
			REQUIRE(C(122) == 0);
			REQUIRE(C(124) == 0);

		}

	}
}//test


TEST_CASE("Counter<string> with 4 elements", "[Counter]")
{
	Counter<string> C;

	REQUIRE(C.size() == 0);
	REQUIRE(C.empty() == true);

	SECTION("inserting 1st element")
	{
		C.insert("apple");

		REQUIRE(C.size() == 1);
		REQUIRE(!C.empty());

		REQUIRE(C["apple"] == true);
		REQUIRE(C("apple") == 1);

		SECTION("inserting 3 more elements")
		{
			C += "banana";
			C.insert("pear");
			C += "pizza";

			REQUIRE(C.size() == 4);
			REQUIRE(!C.empty());

			REQUIRE(C["apple"] == true);
			REQUIRE(C["banana"] == true);
			REQUIRE(C["pear"] == true);
			REQUIRE(C["pizza"] == true);

			SECTION("checking element counts")
			{
				REQUIRE(C("apple") == 1);
				REQUIRE(C("banana") == 1);
				REQUIRE(C("pear") == 1);
				REQUIRE(C("pizza") == 1);

			}

			SECTION("checking non-elements")
			{
				REQUIRE(!C["appl"]);
				REQUIRE(!C["applee"]);
				REQUIRE(!C["Pear"]);
				REQUIRE(!C["piazza"]);
				REQUIRE(!C["zizza"]);

			}

			SECTION("checking non-element counts")
			{
				REQUIRE(C("appl") == 0);
				REQUIRE(C("applee") == 0);
				REQUIRE(C("Pear") == 0);
				REQUIRE(C("piazza") == 0);
				REQUIRE(C("zizza") == 0);

			}

		}

	}
}//test


//From this point beyond next four test cases are my original creation to check the COntainer Counter.
//Test no.1
TEST_CASE("Copy Constructor Test", "[Counter]")
{
	Counter<int> C1;
	REQUIRE(C1.size() == 0);
	REQUIRE(C1.empty() == true);

	SECTION("Copy Constructor test")
	{
		C1.insert(590);
		C1.insert(1200);
		C1.insert(1200);
		C1.insert(2000);

		REQUIRE(C1.size() == 3);
		REQUIRE(C1.empty() == false);

		Counter<int> C2(C1);
		REQUIRE(C2.size() == 3);
		REQUIRE(C2.empty() == false);
		REQUIRE(C2(50) == 0);//
		REQUIRE(C2(590) == 1);
		REQUIRE(C2(1200) == 2);
		REQUIRE(C2(2000) == 1);
		REQUIRE(C2(50) == 0);
		REQUIRE(C2(590) == 1);
		REQUIRE(C2(1200) == 2);
		REQUIRE(C2(1000) == 0);

		//iterator test case...
		auto i = C1.begin();
		while (i != C1.end())
		{
			++i;
		}

	}

	Counter<int> C3;
	REQUIRE(C3.size() == 0);
	REQUIRE(C3.empty() == true);

	SECTION("= operator Constructor test")
	{
		C3.insert(590);
		C3.insert(1200);
		C3.insert(1200);
		C3.insert(2000);

		REQUIRE(C3.size() == 3);
		REQUIRE(C3.empty() == false);

		Counter<int> C4;
		C4 = C3;
		REQUIRE(C4.size() == 3);
		REQUIRE(C4.empty() == false);
		REQUIRE(C4(50) == 0);
		REQUIRE(C4(590) == 1);
		REQUIRE(C4(1200) == 2);
		REQUIRE(C4(2000) == 1);
		REQUIRE(C4(50) == 0);
		REQUIRE(C4(590) == 1);
		REQUIRE(C4(1200) == 2);
		REQUIRE(C4(1000) == 0);
	}

}//end of test 1

//Test no.2 
TEST_CASE("Clear function with copy and = operator Test", "[Counter]")
{
	Counter<int> C1;
	REQUIRE(C1.size() == 0);
	REQUIRE(C1.empty() == true);

	SECTION("Copy Constructor test")
	{
		C1.insert(590);
		C1.insert(1200);
		C1.insert(1200);
		C1.insert(2000);

		REQUIRE(C1.size() == 3);
		REQUIRE(C1.empty() == false);

		Counter<int> C2(C1);
		C1.clear();
		REQUIRE(C2.size() == 3);
		REQUIRE(C2.empty() == false);
		REQUIRE(C2(50) == 0);//
		REQUIRE(C2(590) == 1);
		REQUIRE(C2(1200) == 2);
		REQUIRE(C2(2000) == 1);
		REQUIRE(C2(50) == 0);
		REQUIRE(C2(590) == 1);
		REQUIRE(C2(1200) == 2);
		REQUIRE(C2(1000) == 0);
	}

	Counter<int> C3;
	REQUIRE(C3.size() == 0);
	REQUIRE(C3.empty() == true);

	SECTION("= operator Constructor test")
	{
		C3.insert(590);
		C3.insert(1200);
		C3.insert(1200);
		C3.insert(2000);

		REQUIRE(C3.size() == 3);
		REQUIRE(C3.empty() == false);

		Counter<int> C4;
		C4 = C3;

		C3.clear();

		REQUIRE(C4.size() == 3);
		REQUIRE(C4.empty() == false);
		REQUIRE(C4(50) == 0);
		REQUIRE(C4(590) == 1);
		REQUIRE(C4(1200) == 2);
		REQUIRE(C4(2000) == 1);
		REQUIRE(C4(50) == 0);
		REQUIRE(C4(590) == 1);
		REQUIRE(C4(1200) == 2);
		REQUIRE(C4(1000) == 0);
	}

}//end of test2


//Test no.3
TEST_CASE("Iterator Cheking for the iterator class.""[Counter]")
{
	Counter<int> C5;
	int number = 1000;
	for (int i = 0; i < number; i++)
	{
		C5.insert(i);
	}
	for (auto i : C5)
	{
		REQUIRE(C5[i] == 1);
	}

	Counter<int> C6;
	int number1 = 1000;
	for (int i = 1000; i >0; i--)
	{
		C6.insert(i);
	}
	for (auto i : C6)
	{
		REQUIRE(C6[i] == 1);
	}

	Counter<int> C7;
	C7 = C6;
	for (auto i : C7)
	{
		REQUIRE(C6[i] == 1);
	}
}//end of test 3



//Test case no.4
TEST_CASE("Counter container stress clear function", "[Counter]") 
 {
	 Counter<int> C7;
	 
	 int count = 1000;
	 for (int i = 0; i < count; i++) 
	 {
		C7.insert((rand() % 10000) + i);
	 }
	 //transfer the numbers from set to contained;
	 for ( auto val : C7) 
	 {
		 REQUIRE(C7[val] != false);
	 }
	 //clearing 1000 elements..
	 C7.clear();
 }//end of test case 4.

//------------------------------------------------------------------------------------------------------------
//From here the test cases  are adapted from the piazza posts with little changes.
TEST_CASE("Duplicates", "[Counter]") {
	Counter<int> C;
	SECTION("Insert in 1 loop") {
		for (int i = 0; i < 10; i++) {
			C.insert(i);
			REQUIRE(C[i] == true);
			REQUIRE(C(i) == 1);
			C.insert(i);
			REQUIRE(C[i] == true);
			REQUIRE(C(i) == 2);
		}
	}
	SECTION("Insert in 1 loop, check in another") {
		for (int i = 0; i < 10; i++) {
			C.insert(i);
			REQUIRE(C[i] == true);
			REQUIRE(C(i) == 1);
			C.insert(i);
		}
		for (int i = 0; i < 10; i++) {
			REQUIRE(C[i] == true);
			REQUIRE(C(i) == 2);
		}
	}
	SECTION("Insert in 2 loop, check after second insert") {
		for (int i = 0; i < 10; i++) {
			C.insert(i);
			REQUIRE(C[i] == true);
			REQUIRE(C(i) == 1);
		}
		for (int i = 0; i < 10; i++) {
			C.insert(i);
			REQUIRE(C[i] == true);
			REQUIRE(C(i) == 2);
		}
	}
	SECTION("Insert in 2 loop, check in another loop after second insert") {
		for (int i = 0; i < 10; i++) {
			C.insert(i);
			REQUIRE(C[i] == true);
			REQUIRE(C(i) == 1);
		}
		for (int i = 0; i < 10; i++) {
			C.insert(i);
		}
		for (int i = 0; i < 10; i++) {
			REQUIRE(C[i] == true);
			REQUIRE(C(i) == 2);
		}
	}

}

TEST_CASE("Copy Constructor Strings", "[Counter]")
{
	Counter<string> C;
	REQUIRE(C.size() == 0);
	REQUIRE(C.empty() == true);
	SECTION("Copy Constructor Test- strings")
	{
		C.insert("Tiger");
		C.insert("Lion");
		C.insert("Tiger");
		C.insert("Frog");
		REQUIRE(C.size() == 3);
		REQUIRE(C.empty() == false);
		//C.printArray();
		Counter<string> C2(C);
		REQUIRE(C2.size() == 3);
		REQUIRE(C2.empty() == false);
		REQUIRE(C("apple") == 0);
		REQUIRE(C("Tiger") == 2);
		REQUIRE(C("Lion") == 1);
		REQUIRE(C("Frog") == 1);
		REQUIRE(C2("Tiger") == 2);
		REQUIRE(C2("Lion") == 1);
		REQUIRE(C2("Frog") == 1);
		//C2.printArray();
	}
}

TEST_CASE("lhs=rhs deep copy Strings", "[Counter]")
{
	Counter<string> C1;
	REQUIRE(C1.size() == 0);
	REQUIRE(C1.empty() == true);
	SECTION("lsh=rhs deep copy Test- strings")
	{
		C1.insert("one");
		C1.insert("two");
		C1.insert("three");
		C1.insert("four");
		C1.insert("five");
		C1.insert("one");
		REQUIRE(C1.size() == 5);
		REQUIRE(C1.empty() == false);
		//C1.printArray();

		Counter<string> C2;
		C2 = C1;

		REQUIRE(C2("one") == 2);
		REQUIRE(C2("two") == 1);
		REQUIRE(C2("three") == 1);
		REQUIRE(C2("four") == 1);
		REQUIRE(C2("five") == 1);
		REQUIRE(C2.size() == 5);
		REQUIRE(C2.empty() == false);
		//C2.printArray();
	}
	SECTION("another deep copy test for int")
	{
		Counter<int> C3;
		REQUIRE(C3.size() == 0);
		REQUIRE(C3.empty() == true);
		C3.insert(1);
		C3.insert(2);
		C3.insert(3);
		C3.insert(4);
		C3.insert(5);
		C3.insert(1);
		REQUIRE(C3.size() == 5);
		REQUIRE(C3.empty() == false);
		//C3.printArray();
		Counter<int> C4;
		C4 = C3;

		REQUIRE(C4(1) == 2);
		REQUIRE(C4(2) == 1);
		REQUIRE(C4(3) == 1);
		REQUIRE(C4(4) == 1);
		REQUIRE(C4(5) == 1);
		REQUIRE(C4.size() == 5);
		REQUIRE(C4.empty() == false);
		//C4.printArray();
	}
}


TEST_CASE("Counter<int> clear", "[Counter]") {
	Counter<int> counter;
	set<int> randomNums;
	int count = 100;
	for (int i = 0; i < count; i++) {
		randomNums.insert((rand() % 1000000) + 1);
	}
	//transfer the numbers from set to contained; 
	for (const auto& val : randomNums) {
		counter.insert(val);
	}
	REQUIRE(counter.size() == randomNums.size());

	SECTION("Clearing 100 elements") {
		counter.clear();
		REQUIRE(counter.size() == 0);
		for (const auto& val : randomNums) {
			REQUIRE(counter[val] == false);
		}
	}
}

TEST_CASE("Counter<int> insert stress test", "[Counter]") {
	Counter<int> counter;
	set<int> randomNums;
	int count;

	SECTION("using 10^3 elements") {
		count = 1000;
		for (int i = 0; i < count; i++) {
			randomNums.insert((rand() % 1000000) + 1);
		}
		//transfer the numbers from set to contained; 
		for (const auto& val : randomNums) {
			counter.insert(val);
		}
		REQUIRE(counter.size() == randomNums.size());
	}
}

TEST_CASE("Copy constructor test", "[Counter]") {
	SECTION("With ints") {
		Counter<int> counter;
		set<int> randomNums;
		int count = 100;
		for (int i = 0; i < count; i++) {
			randomNums.insert((rand() % 1000000) + 1);
		}
		//transfer the numbers from set to contained; 
		for (const auto& val : randomNums) {
			counter.insert(val);
		}
		Counter<int> copyCounter(counter);
		REQUIRE(counter.size() == copyCounter.size());
		//clear the original one 
		counter.clear();
		REQUIRE(copyCounter.size() > counter.size());

		//make sure that a deep copy was made
		for (const auto& val : randomNums) {
			REQUIRE(copyCounter[val] == true);
		}
	}
}

TEST_CASE("Counter<int> copy constructor", "[Counter]")
{
	Counter<int> C1;
	// Insert 3 values into C1
	C1 += 5; C1 += 5;          // 2 copies
	C1 += 4;
	C1 += 6; C1 += 6; C1 += 6; // 3 copies
							   // Test the copy constructor
	SECTION("copy construct C2 from C1")
	{	// Copy construct C2 from C1
		Counter<int> C2(C1);
		// Test that the sizes are correct
		REQUIRE(C1.size() == 3);
		REQUIRE(C2.size() == C1.size());
		// Test that C1 still has the correct values
		REQUIRE((C1[5] == true && C1(5) == 2));
		REQUIRE((C1[4] == true && C1(4) == 1));
		REQUIRE((C1[6] == true && C1(6) == 3));
		// Test that C2 copied the values from C1
		SECTION("check that C2 copied the values from C1")
		{
			REQUIRE(C2[5] == true);
			REQUIRE(C2[4] == true);
			REQUIRE(C2[6] == true);
		}
		// Test that C2 copied the counts from C1
		SECTION("check that C2 copied the counts from C1")
		{
			REQUIRE(C2(5) == C1(5));
			REQUIRE(C2(4) == C1(4));
			REQUIRE(C2(6) == C1(6));
		}
		// Test that C1 and C2 are independent (in memory)
		SECTION("check that C1 and C2 are independent")
		{	// Insert 1 new value into C1
			C1 += 7;
			// Insert 2 new values into C2
			C2 += 3;
			C2 += 2;
			// Test that C1 size has been updated
			// and new value was inserted
			REQUIRE(C1.size() == 4);
			REQUIRE((C1[7] == true && C1(7) == 1));
			// Test that C2 size has been updated
			// and new values were inserted
			REQUIRE(C2.size() == 5);
			REQUIRE((C2[3] == true && C2(3) == 1));
			REQUIRE((C2[2] == true && C2(2) == 1));
			// Test that C1 does not have values from C2
			SECTION("check that C1 does not have values from C2")
			{
				REQUIRE((C1[3] == false && C1(3) == 0));
				REQUIRE((C1[2] == false && C1(2) == 0));
			}
			// Test that C2 does not have values from C1
			SECTION("check that C2 does not have values from C1")
			{
				REQUIRE((C2[7] == false && C2(7) == 0));
			}
			// Test that C1 has correct order (unaffected by C2)
			SECTION("check that C1 ordering is correct")
			{
			// Correct order: 4, 5, 6, 7
			auto iter = C1.begin();
			// Test order
			REQUIRE(*iter == 4);
			REQUIRE(*++iter == 5);
			REQUIRE(*++iter == 6);
			REQUIRE(*++iter == 7);
			// Test for end of sequence
			REQUIRE(!(++iter != C1.end()));
			}
			// Test that C2 has correct order (unaffected by C1)
			SECTION("check that C2 ordering is correct")
			{
			// Correct order: 2, 3, 4, 5, 6
			auto iter = C2.begin();
			// Test order
			REQUIRE(*iter == 2);
			REQUIRE(*++iter == 3);
			REQUIRE(*++iter == 4);
			REQUIRE(*++iter == 5);
			REQUIRE(*++iter == 6);
			// Test for end of sequence
			REQUIRE(!(++iter != C2.end()));
			}

		}
	}

}// test

 TEST_CASE("Counter<Student> with 1 element", "[Counter]")
 {
 Counter<Student> C;

 REQUIRE(C.size() == 0);
 REQUIRE(C.empty() == true);

 SECTION("inserting 1 studnet")
 {
 Student S(123456, 100, 88);

 C.insert(S);

 REQUIRE(C.size() == 1);
 REQUIRE(!C.empty());

 SECTION("element contains")
 {
 Student S2(123456, 0, 0);  // create a student with matching UIN:

 REQUIRE(C[S2] == true);
 }

 SECTION("element count")
 {
 Student S2(123456, 0, 0);  // create a student with matching UIN:

 REQUIRE(C(S2) == 1);
 }

 SECTION("unknown elements not contained")
 {
 Student S3(010100, 0, 0);  // student #1 that doesn't match:
 Student S4(999999, 0, 0);  // student #2
 Student S5(1234567, 0, 0);  // student #3

 REQUIRE(!C[S3]);
 REQUIRE(!C[S4]);
 REQUIRE(!C[S5]);
 }

 SECTION("unknown element counts")
 {
 Student S3(010100, 0, 0);  // student #1 that doesn't match:
 Student S4(999999, 0, 0);  // student #2
 Student S5(1234567, 0, 0);  // student #3

 REQUIRE(C(S3) == 0);
 REQUIRE(C(S4) == 0);
 REQUIRE(C(S5) == 0);
 }
 }
 }//test

 
TEST_CASE("Volume", "[Counter]")
{
	Counter<int> C;

	SECTION("Lots of numbers test")
	{
		for (int i = 999; i >0; i--) //insert 1000 numbers in reverse order
			C.insert(i);
		for (int i = 1; i < 1000; i++)
		{
			REQUIRE(C(i) == 1);
			REQUIRE(C[i] == true);
		}
		for (int i = 1; i <1000; i++)
			C.insert(i);
		for (int i = 1; i < 1000; i++)
		{
			REQUIRE(C(i) == 2);
			REQUIRE(C[i] == true);
		}
		//reset the array and do again
		C.clear();
		for (int i = 0; i < 1000; i++)
		{//make sure everything is clear
			REQUIRE(C(i) == 0);
			REQUIRE(C[i] == false);
		}
		REQUIRE(C.size() == 0);
		REQUIRE(C.empty() == true);
		for (int i = 999; i >= 0; i--)
			C.insert(i);

		for (int i = 1; i < 1000; i++)
		{
			REQUIRE(C(i) == 1);
			REQUIRE(C[i] == true);
		}
		for (int i = 0; i <1000; i++)
			C.insert(i);
		for (int i = 0; i < 1000; i++)
		{
			REQUIRE(C(i) == 2);
			REQUIRE(C[i] == true);
		}
		for (int i = 0; i <1000; i++)
			C += i; //try out += operator
		for (int i = 0; i < 1000; i++)
		{
			REQUIRE(C(i) == 3);
			REQUIRE(C[i] == true);
		}

		Counter <int> C2;
		C2 = C;
		REQUIRE(C.size() == 1000);
		REQUIRE(C2.size() == 1000);
		for (int i = 1; i < 1000; i++)
		{//checks if values were copied correctly and 100 was not added
			REQUIRE(C2(i) == 3);
			REQUIRE(C2[i] == true);
		}

	}
}

TEST_CASE("iterator tests")
{
	SECTION("empty list")
	{
		Counter<int> C;
		for (auto e : C)
		{
			//this shouldn't run
			REQUIRE(false);
		}
	}

	SECTION("one element")
	{
		Counter<int> C;
		C += 1;
		for (auto e : C)
		{
			REQUIRE(C[e]);
			REQUIRE(C(e) == 1);
		}
	}

	SECTION("3 elements ordering check")
	{
		Counter<int> C;
		C.insert(123);
		C.insert(454);
		C.insert(11);
		// Tree
		//			123
		//		11		 454
		auto iter = C.begin();			// start at 11
		string t = typeid(iter).name();
		REQUIRE(*iter == 11);
		++iter;
		REQUIRE(*iter == 123);
		++iter;
		REQUIRE(*iter == 454);
		++iter;
		auto iter2 = C.end();
		REQUIRE(!(iter != iter2));
	}

	SECTION("2 elements ordering check with for each")
	{
		// Tree
		//			454
		//		11
		//
		Counter<int> C;
		C.insert(454);
		C.insert(11);
		for (auto e : C)
		{
			REQUIRE(C[e]);
			REQUIRE(C(e) > 0);
		}
		auto iter = C.begin();
		REQUIRE(*iter == 11);
		REQUIRE(*++iter == 454);
	}

	SECTION("2 elements ordering check with for each")
	{
		// Tree
		//	   11
		//		   454
		//
		Counter<int> C;
		C.insert(11);
		C.insert(454);
		for (auto e : C)
		{
			REQUIRE(C[e]);
			REQUIRE(C(e) == 1);
		}
		auto iter = C.begin();
		REQUIRE(*iter == 11);
		REQUIRE(*++iter == 454);
	}

	SECTION("3 elements ordering check with for each")
	{
		Counter<int> C;
		C.insert(123);
		C.insert(454);
		C.insert(11);
		for (auto e : C)
		{
			REQUIRE(C[e]);
			REQUIRE(C(e) > 0);
		}
	}

	SECTION("degenerate Tree with for each")
	{
		Counter<int> C;
		for (int i = 0; i < 100; i++)
		{
			C.insert(i);
		}

		for (auto e : C)
		{
			REQUIRE(C[e]);
		}

		auto iter = C.begin();
		auto end = C.end();
		while (iter != end)
		{
			REQUIRE(C[*iter]);
			++iter;
		}
		//check what happens when you go past end, watch out for exceptions
		++iter;
		++iter;
		++iter;

		// insert everything again
		for (int i = 0; i < 100; i++)
		{
			C.insert(i);
		}
		Counter<int> C2 = C;
		REQUIRE(C2.size() == 100);
		REQUIRE(C.size() == 100);

		// check elements again
		for (auto e : C)
		{
			REQUIRE(C[e]);
			REQUIRE(C(e)); // all counts should be 2
		}
		for (auto e : C2)
		{
			REQUIRE(C2[e]);
			REQUIRE(C2(e) == 2); // all counts should be 2
		}
	}

	SECTION("Full Tree, iterator test")
	{
		Counter<int> C;
		int arr[] = { 5,3,7,4,1,2,6,8,10,9 };
		//Tree
		//				5
		//			3		7
		//	     1    4   6    8
		//		  2	            10	
		//                     9
		for (int i = 0; i < 10; i++)
		{
			C.insert(arr[i]);
		}

		for (auto e : C)
		{
			REQUIRE(C[e]);
			REQUIRE(C(e) == 1); // all counts should be 1
		}
		int arr2[] = { 1,2,3,4,5,6,7,8,9,10 };
		int i = 0;
		for (auto& e : C)
		{
			REQUIRE(e == arr2[i]);
			i++;
		}
	}
}//end of all test cases........
