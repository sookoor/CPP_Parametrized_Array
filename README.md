Compilation instructions using g++:

1. Open a command line prompt that accepts the g++ command.
2. Change the directory to the folder containing the source code and Makefile.
3. Type 'make'
4. When the compilation is complete and focus is returned to the user type './main' to run the program. 
5. Follow the instructions on the prompt.

Updates made:

1. Comment: "This is inefficient, please say

            return &this->array_ == &rhs.array_ && this->pos_ ==
            rhs.pos_;

            so it doesn't do a complete comparison of each element in the array!"

   Changes: Changed "return (array_ == rhs.array_ && pos_ ==
            rhs.pos_);" to "return &this->array_ == &rhs.array_ &&
            this->pos_ = rhs.pos_;"

2. Comment: "This code below does not have strong exception safety
             guarantees, so please fix that."

   Changes: Used scoped array.

3. Comment: "Please don't use resize() here since it causes
             unnecessary memory copies."

   Changes: Deleted the array explicitly. 

4. Comment: "This code below does not have strong exception safety
             guarantees, so please fix that."

   change:  Used scoped array.
