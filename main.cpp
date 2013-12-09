// Uses a Array to reverse a name and test various properties of class
// Array<>.

#include <assert.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include "Array.h"

static const int INITIAL_NAME_LEN = 1;

typedef Array<char> ARRAY;

main (int argc, char *argv[]) 
{
  try
    {
      std::string name;
      const ARRAY::TYPE DEFAULT_VALUE = 'D';

      ARRAY a1 (INITIAL_NAME_LEN, DEFAULT_VALUE);
      size_t i;
      assert (a1.size () == INITIAL_NAME_LEN);

      std::cout << "please enter your name..: ";
      std::getline (std::cin, name);

      assert (a1.size () == 1);
      std::cout << "size is " << a1.size () << std::endl 
                << "read in: " << name.length () << std::endl;

      for (i = 0; i < name.length (); i++)
        // Note that this call should trigger a resize() initially.
        a1.set (name[i], i);

      // Test to make sure that a1.size () is assigned properly after
      // the series of set() calls. 
      assert (a1.size () == name.length ());

      std::cout << "size is " << a1.size () << std::endl << "your name is..: ";

      for (i = 0; i < a1.size (); i++)
        std::cout << a1[i];

      std::cout << std::endl << "your name is..: ";

      for (ARRAY::iterator iterator (a1.begin ());
           iterator != a1.end ();
           iterator++)
        std::cout << *iterator;

      std::cout << std::endl;

      // Test initialization with the copy constructor.
      ARRAY a2 (a1);
      ARRAY a3 (a1.size () + a2.size (), -1);

      // Test the assignment operator.
      a1 = a2;
      assert (a1.size () == a2.size ());
      assert (a1 == a2);
      assert (!(a1 != a2));

      a2 = a3;
      assert (a1.size () != a2.size ());
      assert (a1 != a2);

      // Test for self assignment.
      a3 = a3;

      // Checking for error in assignment/equality operator when
      // copying cur_size - 1 chars instead of cur_size.
      ARRAY a4 (name.length ());

      for (i = 0; i < name.length (); i++)
        a4.set (name[i], i);

      ARRAY a5 (INITIAL_NAME_LEN, DEFAULT_VALUE);
      a5 = a4;

      assert (a4 == a5);

      a4 [name.length () - 1] = 'x';
      assert (! (a4 == a5));

      std::cout << "your name backwards is..: ";

      // Note that we're "off by one here" so we'll get a range error.
      for (int j = name.length (); j >= 0; j--)
        {
          ARRAY::TYPE c;

          a1.get (c, j - 1);
          std::cout << c;
        }

      std::cout << "\n";
    }
  catch (std::out_of_range &e)
    {
      std::cout.flush(); 
      std::cerr << std::endl << "index " << e.what () << " out of range" << std::endl;
    }
  catch (std::bad_alloc &)
    {
      std::cout.flush(); 
      std::cerr << "new failed" << std::endl;
    }

  return 0;     
}

#if defined (__GNUC__) || defined (_MSC_VER)
template class Array<char>;
#endif /* __GNUC__ || _MSC_VER */
