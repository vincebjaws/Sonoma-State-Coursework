// Vince Bjazevic
// Project 1
// Due 10/7/19
//solutions.cpp

#include "reclists.hpp"
#include "solutions.hpp"

list append( list p, list q )
{
  if(is_null(p)) return q;  // Base case
  if(is_null(q)) return p;
  return cons(car(p), append(cdr(p),q)); // Recursion call
}

list reverse( list p )
{
  if(is_null(p)) return p; // Base case
  if(is_atom(p)) return p; // Base case
  return append(reverse(cdr(p)), cons(car(p), null())) ; // Recursion call
}

bool is_lat( list p)
{ // is_lat takes a non-atomic list and returns true if the list is a list (potentially empty) of atoms
  if(is_null(p))        return false; // Base case
  if(is_atom(car(p)))   return true; // Base case
  return is_lat(cdr(p)); // Recursion call
}

bool member(list p, list q)
{ // p is an atom and q is an non-atomic list. member returns true if p appears anywhere in q.
  if(is_null(q))      return false; // Base case
  if(is_atom(car(q))) {
    if(eq(p, car(q))) return true;
  }
  return member(p, cdr(q)); // recusion call
}

list last(list p)
{ // last returns the last element, ln, of a non-atomic, non-empty list.
  if(is_null(cdr(p)))   return car(p); // Base case
  return last(cdr(p)); // recusion call
}

list list_pair(list p, list q)
{   // returns a list that consists of lists of two atoms each, which
    // are the corresponding atoms paired up.
  if(is_null(cdr(p))) return cons(append(p,q), null());
  return  cons(cons(car(p),cons(car(q),null())),list_pair(cdr(p),cdr(q)));
}

list firsts(list p)
{ // returns a list which contains the first element from each of the lists
    if(is_null(p))   return null();
    return cons(car(car(p)),firsts(cdr(p)));
}

list flat(list p)
{ //returns a list which is the original list with the parenthesis removed
   if(is_null(p))        return p;
   if(is_atom(car(p)))   return cons(car(p),flat(cdr(p)));
   if(!is_atom(car(p)))  return append(flat(car(p)),flat(cdr(p)));
   return flat(cdr(p));
}

bool two_the_same(list p, list q)
{ // returns true if p and q contain at least one atom in common
    if( is_null(p))          return false;
    if( is_null(q))          return false;
    if(member(car(p), q))    return true;
    return two_the_same(cdr(p), q);
}

bool equal(list p, list q)
{   // takes two arbitrary recursive lists and determines if they are identical, that is the
    // parentheses are all in the same place and the atoms agree as to place and name.
    if(is_null(p))         return false;
    if(eq(car(p),car(q)))  return true;
    return equal(cdr(p), cdr(q));
}

list total_reverse(list p)
{   //It is the extension of reverse that reverses the
    // list and each sub-list, recursively, unto the nth generation.
    if(is_null(p))  return p;
    if(!is_atom(car(p)))  return reverse(cons(total_reverse(car(p)),total_reverse(cdr(p)))); 
    return append(total_reverse(cdr(p)),cons(car(p), null()));
}

list shape(list p)
{  // returns a recursive list that consists of only the parentheses in the original.
    if(is_null(p))       return p;
    if(is_atom(car(p)))  return shape(cdr(p));
    return cons(shape(car(p)), shape(cdr(p)));
}

list intersection(list p, list q)
{  // p and q are lists of atoms with no atom appearing twice in p and no atom appearing twice
   // in q. p and q represent sets. intersection forms their intersection.
    if(is_null(p)) return null();
    if(is_null(q)) return null();
    if(member(car(p),q))  return append (cons(car(p), null()), intersection(cdr(p),q));
    return intersection(cdr(p), q);
}

list list_union(list p, list q)
{ // list_union forms the set which is their union—remember if p and q have an atom in
   // common then this atom should only appear once in the union.

    if(is_null(q)) return p;
    if(is_null(p)) return q;
    if(member(car(p), q)) return append(list_union(cdr(p), q), null());
    return append(cons(car(p), null()), list_union(cdr(p), q));
}

list permute(list p){
    if(is_null(p)) return p;
    //return (permute(cons(cdr(p),null())));
    return cons((cdr(p)),cons(p, null()));
}
