/*counter.h*/

//
// <<Jay V Patel>>
//
// The Counter container is a set with no duplicates.  However, it keeps
// a count of how many times an element was inserted, hence the name
// "Counter".  Users of the Counter container can test for set membership,
// as well as obtain an element's count.
// 
// Example:  suppose C is a Counter, and you insert the elements 3, 11, 
// 5, 11, 3, and 11.  Then C contains the elements {3, 5, 11}, where 3's 
// count is 2, 5's count is 1, and 11's count is 3.
//
// Given N elements, search operations are O(lgN), and insert is O(N); these
// are average-time complexities.  In terms of space, the container will 
// consume at most 4N space.
// 

//MY IMPLEMENTATION TECHNIQUE:
// I have used BST data stucture for counter to contain the values into.
//Then, I made the helper functions for the data stucture and wrote test cases to,
//check the functions..
//For the iterator class i have created an dynamic array to stoare the values of BST,
//by doing the inorder treversal of the BST i stored it into the dynamic array,
//then, i assined the begin() of iterator to the array[0] and end() at array[size+1],
//at last i wrote test case for that and BOOM..it worked.

#pragma once

#include <iostream>
#include <iterator>

using std::cout;  // for debug printing:
using std::endl;


template<typename T>

class Counter
{
private:
	struct bst_node {
		T      val;
		bst_node *left;
		bst_node *right;
		int countOf = 0;
		int leftNodeCount = 0;
		int rightNodeCount = 0;

		bst_node(const T & _val = T{}, bst_node * l = nullptr, bst_node *r = nullptr, int c = 0)
			: val{ _val }, left{ l }, right{ r }, countOf{ c }
		{ }
	};
	bst_node *root;


public:
	//
	// constructor:
	//
	Counter()
	{
		root = nullptr;
	}


	//
	// copy constructor:
	//
	Counter(const Counter& other)
	{
		root = helpcopy(other.root);
	}

	bst_node* helpcopy(const bst_node *cc)
	{
		if (cc == NULL)
		{
			return NULL;
		}
		bst_node *copyNode = new bst_node;
		copyNode->val = cc->val;
		copyNode->left = helpcopy(cc->left);
		copyNode->right = helpcopy(cc->right);
		copyNode->countOf = cc->countOf;
		return copyNode;
	}



	//
	// destructor:
	// 
	~Counter()
	{
		delete_nodes(root);
		root = nullptr;
	}


	//
	// size()
	// 
	// Returns the # of elements in the set.
	// 
	// Time complexity: O(1).
	// 

public:
	// recursive helper function to compute size of
	//   tree rooted at r
	static int helpsize(bst_node *r) {
		if (r == nullptr)
		{
			return 0;
		}
		else
		{
			return helpsize(r->left) + helpsize(r->right) + 1;
		}
	}

public:
	int size() const
	{
		return helpsize(root);
	}



	//
	// empty()
	//
	// Returns true if the set is empty, false if not.
	// 
	// Time complexity: O(1).
	// 
	bool empty() const
	{
		int s = 0;
		s = size();
		if (s == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	//
	// clear()
	//
	// Empties the set, deleting all elements and counts.
	//
	void clear()
	{
		delete_nodes(root);
		root = nullptr;
	}


	//
	// [e]
	//
	// Returns true if set contains e, false if not.
	//
	// NOTE: since the type of e is unknown, elements are compared using <. 
	// This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
	// 
	// Time complexity: average-case O(lgN).
	//
	bool operator[](const T& e)
	{
		bst_node *p = root;

		while (p != nullptr)
		{
			if ((!(p->val< e)) && (!(e<p->val)))
			{
				return true;
			}
			if (e < p->val)
			{
				p = p->left;
			}
			else
			{
				p = p->right;
			}
		}
		return false;
	}


	//
	// (e)
	// 
	// Returns a count of how many times e has been inserted into the set;
	// the count will be 0 if e has never been inserted.
	// 
	// NOTE: since the type of e is unknown, elements are compared using <. 
	// This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
	// 
	// Time complexity: average-case O(lgN).
	// 
	int operator()(const T& e) const
	{
		bst_node *p = root;

		while (p != nullptr)
		{
			if ((!(p->val< e)) && (!(e<p->val)))
			{
				return p->countOf;
			}
			if (e < p->val)
			{
				p = p->left;
			}
			else
			{
				p = p->right;
			}
		}
		return 0;
	}
	static void delete_nodes(bst_node *r) 
	{
		if (r == nullptr) return;
		delete_nodes(r->left);
		delete_nodes(r->right);
		delete r;
	}


	//
	// insert(e)
	// 
	// If e is not a member of the set, e is inserted and e's count set to 0.
	// If e is already in the set, it is *not* inserted again; instead, e's
	// count is increased by 1.  Sets are unbounded in size, and elements are
	// inserted in order as defined by T's < operator; this enables in-order 
	// iteration.
	// 
	// NOTE: since the type of e is unknown, elements are compared using <. 
	// This implies 2 elements x and y are equal if (!(x<y)) && (!(y<x)).
	// 
	// Time complexity: worst-case O(N).
	// Space complexity: 4N.
	//
	bst_node* helpinsert(bst_node *r, const T& e, bool &success)
	{
		if (r == nullptr)
		{
			success = true;
			bst_node* t = new bst_node(e, nullptr, nullptr, 0);
			t->countOf++;
			return t;
		}

		if ((!(r->val< e)) && (!(e<r->val)))
		{
			r->countOf++;
			success = false;
			return r;
		}
		if (e < r->val)
		{

			r->left = helpinsert(r->left, e, success);
			if (success)
			{
				r->leftNodeCount++;
			}

			return r;
		}
		else
		{
			r->right = helpinsert(r->right, e, success);
			if (success)
			{
				r->rightNodeCount++;
			}
			return r;
		}
	}

	void insert(const T& e)
	{
		bool success;
		root = helpinsert(root, e, success);
	}


	// 
	// += e
	//
	// Inserts e into the set; see insert.
	//
	// Time complexity: worst-case O(N).
	// Space complexity: 4N.
	// 
	Counter& operator+=(const T& e)
	{
		//
		// insert e into "this" set:
		//
		this->insert(e);

		// return "this" updated set:
		return *this;
	}


	//
	// lhs = rhs;
	//
	// Makes a deep copy of rhs (right-hand-side) and assigns into
	// lhs (left-hand-side).  Any existing elements in the lhs
	// are destroyed *before* the deep copy is made.
	// 
	// NOTE: the lhs is "this" object.
	//
	Counter& operator=(const Counter& rhs)
	{
		//
		// NOTE: where is the lhs in the function call?  The lhs operand is 
		// hidden --- it's "this" object.  So think this->operator=(rhs).  
		//

		// check for self-assignment:
		//if (this == &rhs)  // S = S;
		if ((!(this< &rhs)) && (!(&rhs<this)))
			return *this;
		else
		{
			this->clear();
			this->root = helpcopy(rhs.root);
			return *this;
		}
	}
	
	class iterator
	{
	public:
		T* array;
		int index = 0;

		//for begin() 
		iterator(bst_node* r, int const n)
		{
			array = new T[n];
			treeTraversal(r);
			index = 0;
		}

		//for end() constructor
		iterator(bst_node* t,int const k,double x)
		{
			array = new T[k+1];
			treeTraversal(t);
			index = k + 1;
		}

		void treeTraversal(bst_node *node)
		{
			if (node == NULL)
				return;

			treeTraversal(node->left);
			array[index] = node->val;
			index++;
			treeTraversal(node->right);
		}
		
		iterator& operator++()
		{
			index++;
			return *this;
		}
		const T& operator*()
		{
			return array[index];

		}
		bool operator!=(const iterator& rhs)
		{
			if (!(this->array[index] < rhs.array[index]) && (!(rhs.array[index] > this->array[index])))
			{
				return false;
			}
			else
			{
				return true;
			}
		}

	};//end of iterator class...

	//
	// begin()
	// 
	// Returns an iterator denoting the first element of the set.  If the 
	// set is empty, begin() == end().  The iterator will advance through
	// the elements in order, as defined by T's < operator.
	//
	iterator begin()
	{
		int bst_size = this->size();
		bst_size = bst_size + 1;
		int const num = bst_size;
		iterator front(this->root, num);
		return front;
	}


	//
	// end()
	// 
	// Returns an iterator denoting the end of the iteration space --- i.e.
	// one past the last element of the set.  If the set is empty, then
	// begin() == end().
	// 
	iterator end()
	{
		int const bst_size1 = this->size();
		iterator back(this->root,bst_size1,0.0);
		return back;
	}
};

//Student class to check wether all the data types are working or not...(proffesor posted it on piazza)
class Student
{
private:
int UIN, Mid, Fnl;

public:
Student()
: UIN(-1), Mid(-1), Fnl(-1)
{ }

Student(int uin, int mid, int fnl)
: UIN(uin), Mid(mid), Fnl(fnl)
{ }

int getUIN() const
{
return UIN;
}

double getExamAvg() const
{
return (Mid + Fnl) / 2.0;
}

//
// lhs < rhs
//
// returns true if lhs < rhs, false otherwise.
//
bool operator<(const Student& other) const
{
//
// NOTE: lhs is "this" object.
//
if (this->UIN < other.UIN)
return true;
else
return false;
}
};
