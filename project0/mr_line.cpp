#ifndef _MR_LINE_CPP_
#define _MR_LINE_CPP_

#include "mr_line.h"
#include <random>
using namespace std;

// this prevents cpp file from being read multiple times, if it is then you get multiple definition errors
// our varible was called the_line and it was an int *
// if you do use default arguments you can't use them for both the .h and .cpp because it doesn't like it.

MrLine::MrLine(int size)
  : m_size(size), the_line(nullptr)
{
  // how do we create a single "line" or really a dynamically allocated array?
  if (m_size > 0)
  {
    // sometimes if you put a zero into the argument here... it can explode
    the_line = new int[m_size];
    // what does this do?
    // what it does is it asks the OS to allocate m_size integers for you.
    // the memory space is called "the heap", "the stack"
    for (int i = 0; i < m_size; i++)
    {
      the_line[i] = rand() % 100;
    }		    
  }
}

MrLine::MrLine(const MrLine & other_line)
{
  // the line is a pointer, set to junk data, but C++ doesn't know that.
  the_line = nullptr;
  // the copy constructor just uses this function, doesn't need to do anything else
  copy_line(other_line);
}

MrLine & MrLine::operator = (const MrLine & other_line)
{
  // one extra thing to do for the assignment operator.
  // MrLine a(5);
  // MrLine * ptr_a = &a, *ptr_b = &a;
  // *ptr_a = *ptr_b;
  // this is the most dangerous place where it probably does happen.
  // this is the self assignment check, use this or something similar.
  if (this != &other_line)
  {
    // remember that this is a POINTER to the current class that we're in
    // reference operator gets the address (a pointer to) other_line.
    // they are NOT the same.
    copy_line(other_line);
  }
  // return this so that c = b = a; work.
  return *this;
}

void MrLine::copy_line(const MrLine & other_line)
{
  // how do you copy a piece of memory?
  // why did we run clear first?
  // because we might have something in there already.
  clear();
  m_size = other_line.m_size;
  if (m_size > 0)
  {
      
    the_line = new int[m_size];
    // what have we done so far?
    // copied the new size into our class
    // we've made a new "line" array
    // what haven't we done yet?  we haven't copied the old values from the other_line into our class
    for (int i = 0; i < m_size; i++)
      {
	the_line[i] = other_line.the_line[i];
      }
  }
}

void MrLine::clear()
{
  // if you delete something that you allocated with new type [brackets] then you need to use delete []
  delete [] the_line;
  // otherwise you get a mismatched delete /delete [] error when you valgrind.
  // remember that the_line was a pointer, it still remembers the value which it had before!!!
  // it doesn't forget just because the memory gets returned to the heap.
  the_line = nullptr;
  m_size = 0;
  // if the only time you run clear is your destructor then who cares, but ... it won't be... so care.
}

MrLine::~MrLine()
{
  clear();
}


#endif
