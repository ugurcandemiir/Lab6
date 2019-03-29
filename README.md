#### CS 240 - Spring 2019
# Lab 6 - Binary Search Tree
## Due Date: 11:59 p.m., March 27th, 2019

*All programs will be tested on the machines in the Q22 lab. If your code does not run on the system in this lab, it is considered non-functioning EVEN IF IT RUNS ON YOUR PERSONAL COMPUTER. Always check that your code runs on the lab machines before submitting.*

### Provided Files and Expected Output
* _Files_
    * lab6.cpp
* _Expected Command > Output_
    * Test Commands we will run
        * make
        * make run
        * make checkmem
        * make clean
    * Sample Output (with our test case):
```shell
    TEST #1: Create an empty tree
    ========================PASS========================
    TEST #2: Insert values into the Tree
    ========================PASS========================
    TEST #3: Cannot insert duplicate values into the Tree
    ========================PASS========================
    TEST #4: Insert 1000 Values into the Tree
    ========================PASS========================
    TEST #5: Find values in the tree
    ========================PASS========================
    TEST #6: Find doesn't segfault on empty tree
    ========================PASS========================
    TEST #7: Cannot remove node that is not in the tree
     [1]  [2]  [3]  [5]  [6]  [7]  [8]  [9]  [10]  [11]  [12]  [13]
    ========================PASS========================
    TEST #8: Remove a leaf node
     [2]  [3]  [5]  [6]  [7]  [8]  [9]  [10]  [11]  [12]  [13]
    ========================PASS========================
    TEST #9: Remove single branch using the Short Circuit algorithm
     [2]  [3]  [5]  [6]  [8]  [9]  [10]  [11]  [12]  [13]
    ========================PASS========================
    Test #10: Remove two branch node promoting a leaf node
     [2]  [3]  [5]  [6]  [8]  [9]  [11]  [12]  [13]
    ========================PASS========================
    TEST #11: Remove two branch node promoting a 1 branch node using Short Circuit
     [2]  [3]  [5]  [6]  [8]  [9]  [12]  [13]
    ========================PASS========================
    TEST #12: Remove root with two branches
     [2]  [3]  [6]  [8]  [9]  [12]  [13]
    ========================PASS========================
    TEST #13: Remove root with one branch
     [8]  [9]  [12]  [13]
    ========================PASS========================
    TEST #14: Remove root as leaf
    ========================PASS========================
    TEST #15: Deep copy for a tree of 100 random values
    ========================PASS========================
    TEST #16: Test deletion and Destructor
    ========================PASS========================
    TEST #17: Test Balancing Tree
    ========================PASS========================
    All Tests Passed.
    Don\'t forget to run with Valgrind and submit to Blackboard!
```
### Grading Rubric
**_TOTAL: 30 points_**
* **Part A: 12 points**
    * Node is an internal class (3 points)
    * Test #1 - Create an empty tree (1 point)
    * Test #2 - Insert values into the Tree (2 points)
    * Test #3 - Cannot insert duplicate values into the Tree (1 point)
    * Test #4 - Insert 1000 Values into the Tree (2 points)
    * Test #5 - Find values in the tree (2 points)
    * Test #6 - Find doesn't segfault on empty tree (1 point)
* **Part B: 18 points**
    * Test #7 - Cannot remove node that is not in the tree (1 point)
    * Test #8 - Remove a leaf node (1 point)
    * Test #9 - Remove single branch using the Short Circuit algorithm (2 points)
    * Test #10 - Remove two branch node promoting a leaf node (1 point)
    * Test #11 - Remove two branch node promoting a 1 branch node using Short Circuit (1 point)
    * Test #12 - Remove root with two branches (2 point)
    * Test #13 - Remove root with one branch (2 point)
    * Test #14 - Remove root as leaf (2 point)
    * Test #15 - Deep copy for a tree of 100 random values (2 points)
    * Test #16 - Test deletion and Destructor (4 points)
* **Part C - EXTRA CREDIT: 10 points**
    * Test #17 - Test Balancing Tree (10 points)
* **Part D:**
    * If memory error, memory leak, no 'memcheck' target [-5 points]
    * Submission includes .o files or binary [-1 point]
    * Does not follow [Style guidelines](https://drive.google.com/open?id=1a5I7XhhCDRHoS8LUfILu3y2la4wW8HHh4olO30YvMVk) [-3 points]
    * Your submission will not be accepted if:
        * Does not follow requested project structure and submission format
        * Does not compile

### Guidelines

This is an individual lab assignment. You must do the vast majority of the work on your own. It is permissible to consult with classmates to ask general questions about the assignment, to help discover and fix specific bugs, and to talk about high level approaches in general terms. It is not permissible to give or receive answers or solution details from fellow students.

You may research online for additional resources; however, you may not use code that was written specifically *to* solve the problem you have been given, and you may not have anyone else help you write the code or solve the problem. You may use code snippets found online, providing that they are appropriately and clearly cited, within your submitted code.

*By submitting this assignment, you agree that you have followed the above guidelines regarding collaboration and research.*

### Policies

#### Commits


#### Getting Help and Extensions

Please follow the debugging guidelines outline [here](https://docs.google.com/document/d/1DLPaOPd9CmbCWbnaRHkPzDQ2Qmo2gYAdqWU1xDM2joI/edit?usp=sharing). We will try to answer questions and provide help within 24 hours of your request. If you do not receive a response in 24 hours, please send the request again.

Although we will answer questions, provide clarification, and give general help where possible up until the deadline, we will not help you debug specific code within 24 hours of the deadline. We will not provide any help after the deadline.

#### Extensions
If an extension is requested more than 24 hours before the deadline, it may be granted, depending on the reason for the requested extension. No extension will be granted, regardless of the reason, within 24 hours of the deadline.

***

The goal of Lab 6 is to build a Binary Search Tree, work with templates a bit more, and develop tree based algorithms such as traversal and balancing.

In the last lab we got a list of habitable planets in our universe. The list can be pretty large, so we want to be able to find specific planets quickly. We are going to build a templated binary search tree so we can store and search for specific Planets. We'll start by testing our BST with integers to make things a bit easier.

#### (Parts A must be completed in lab)

## Part A: Creating a BST Class

Write your own simple templated Binary Search Tree (BST) C++ class that includes the insert(), find(), and remove() methods, as well as traversal and utility methods. We can start with the following public interface:
* `BSTree()`
* `bool empty()`
    * `true` if the tree is empty
    * `false` if it is not
* `bool insert(int val)`
    * Returns `true` if the value was inserted
    * `false` if the value was already in the tree
        * INSERT ALGORITHM: To insert a new node, start at the root and move down left or right, following the appropriate pointers, until you get to the appropriate place at the bottom. Then create a new BSTree<T>::Node and set the appropriate pointer to the new node.
* `bool find(int val)`
    * `true` if the value is in the tree
    * `false` if the value is not in the tree
        * FIND ALGORITHM: Find works the same as insert, except you do not create a new node. Instead you return a boolean value when you find the value or a null branch.
* Use one class for the entire BST, which contains a single pointer to a Node, which is the root of the tree.

You'll also have a nested helper C++ class, Node, which contains a templated data member to store the data item, and three pointers to other Nodes, one for the left subtree, one for the right subtree, and one for the parent.

* You are going to create the Node class as an internal class to the Tree. This MUST be the first thing in your BSTree class. You declare it just like a normal class, except it is kept as a private data member:

```c++
template <class T>
class BSTree{
      private:
            class Node{
                    public:
                            …
```

* You can only access the node class within your `BSTree` class if it is private.
    * More info about [nested classes](http://www.oopweb.com/CPP/Documents/CPPAnnotations/Volume/cplusplus16.html)
    * For the templated nested class, `Node`, you will need to qualify the type with the keyword, `typename`. This is due to the ambiguity of whether you are referring to a class or a namespace. Read the following for more [information](http://pages.cs.wisc.edu/~driscoll/typename.html).
* You must complete your templated implementations of your `insert` and `find` in lab. Make sure everything compiles before moving on.

__Show your TA your code.__

__--END OF IN LAB REQUIRED WORK--__

_You may continue to work on the remainder of the lab on your own time or in lab_

## Part B: Implementing Remove and Traversal
Now we are going to extend the templated BST with remove and traversal. Your BST must have the following public interface:
* `BSTree()`
* `BSTree(const BSTree &old_tree)`
    * Performs a deep copy of a `BSTree` object using preorder traversal
* `~BSTree()`
    * Removes all allocated memory in a `BSTree` using postorder traversal
* `bool empty()`
    * `true` if the tree is empty
    * `false` if it is not
* `bool insert(int val)`
    * Returns `true` if the value was inserted
    * `false` if the value was already in the tree
* `bool find(int val)`
    * `true` if the value is in the tree
    * `false` if the value is not in the tree
* `void sortedArray(vector<int> &list)`
    * Takes a `vector` reference, and fills the `vector` with the tree values in sorted order
* `bool remove(int num)`
    * Takes a value and removes that value from the tree if found
    * Returns `true` if the value was removed, `false` if the value is not in the tree.

You will need to implement the following algorithms. I recommend implementing them as separate private methods that you call in each of the associated public methods.

* InOrder Traversal for sortedArray
* PostOrder Traversal for tree deletion
* PreOrder Traversal for tree deep copy

## Part C - EXTRA CREDIT: Balancing Your Tree

There are many different ways to balance a binary tree. The simplest method (but not necessarily the most efficient) is to sort the tree into a sorted list, then delete all values from the tree and remake the tree by recursively dividing the array in half, and inserting the center value back into the tree. Here is the basic algorithm:
1) Get the middle of the array and make it root.
2) Recursively do same for left half and right half.
    * Get the middle of left half and make it left child of the root
          created in step 1.
    * Get the middle of right half and make it right child of the
          root created in step 1.
    * Continue logically dividing the array in half until it is empty
        * :bulb: You do not need to actually break the array into two arrays. Just keep track of the start and end with indices.

For part C you must have a method that balances your tree object. You may use another algorithm if you choose. The only requirement for your balance method is that it must have this interface:
```c++
    void balance();
```

In order to test your tree, you will need to have an additional method, height, which returns the height of your tree. Add the following method to your `BSTree` class:

```c++
    int BSTree::height(){
        return findHeight(this->root);
    }
    int BSTree::findHeight(Node* node){
       // base case tree is empty
       if(node == NULL)
           return 0;

       // If tree is not empty then height = 1 + max of left height and right heights
        lh = height(node->left);
        rh = height(node->right)
        max = (lh >= rh) ? lh : rh;
        return 1 + max;
    }
```

You may have to make some modifications to work with your tree, but you should not change the basic algorithm.

__You must add a blank file to your repo called EXTRA in order for the TA's to give you credit for the extra credit__

__Use the command `touch EXTRA` to create this file__

## Part D: Code Organization and Submission
* Required code organization:
    * lab6.cpp (driver code - You must include this file in your submission)
    * BSTree.h
    * makefile
        * executable should be called: lab6
        * You must have the following targets in your makefile:
            * `all` - only compiles your source code using separate compilation for each .cpp file
            * `clean` - removes all object files and binary executables
            * `run` - compiles if necessary and runs your executable
            * `memcheck` - compiles your source if necessary, then runs your executable with valgrind
    * EXTRA (optional)

Below is just a reminder of the commands you should use to submit your code. If you cannot remember the exact process, please review lab 1.

*These commands all presume that your current working directory is within the directory tracked by `git`.*

You will need to do the following when your submission is ready for grading.
```shell
git commit -am "final commit"
git push
```

To complete your submission, you must copy and paste the commit hash into MyCourses. Go to MyCourses, select CS240, and then assignments. Select Lab 6, and where it says text submission, paste your commit hash. You can get your latest commit hash with the following command:

```shell
git rev-parse HEAD
```

:warning: Remember, you __MUST__ make a submission on mycourses before the deadline to be considered on time.
