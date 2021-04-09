# Self Reflective Tacit Interpreter

This project is the framework for a Lisp-like interpreter, written in C, which accepts a lisp-like, point-free language with the added reflexive capability of internal function reference.

In standard lambda calculus, there is no reference to a function within itself. To get around such issues special combinators like the Y-combinator were invented. To essentially pass the function to itself in a way digestible by the syntax rules of untyped lambda calculus.

This interpreter makes a pointer available to an open function which points to the use of said function. With a natural atom for recursion, recursive proofs and programs are much shorter to construct, a necessry fact for [OOPS](http://www.idsia.ch/~juergen/oops.html) solvers.

This source code is pre-setup to run the factorial function on the input. Execute the program with:
`./interp [x]` where `[x]` is the number to perfom a factorial on.

sample output:
```
./interp 4

VALID OUTPUT
 RESULT:  24
 PROGRAM: (OUT (LAMBDA (X) (IF (VALUE0) (ONE) (MULT (VALUE0) (RECUR0 (DEC (VALUE0)))))))
 ENERGY:  33
```


When profiled with valgrind, it can be proven that no leaks exist.
`valgrind ./interp [x]`

output from valgrind:
```
==4653== HEAP SUMMARY:
==4653==     in use at exit: 0 bytes in 0 blocks
==4653==   total heap usage: 176 allocs, 176 frees, 4,616 bytes allocated
==4653==
==4653== All heap blocks were freed -- no leaks are possible
==4653==
==4653== For lists of detected and suppressed errors, rerun with: -s
==4653== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
