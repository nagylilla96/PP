:- use_module(library(clpfd)).

is_prime(2).
is_prime(X) :-
    X > 1,
    prime(X, 2).

prime(X, Y) :-
    Y > floor(sqrt(X)) -> true;
    0 is X mod Y -> false;
    Z is Y + 1,
    prime(X, Z).

list_primes(A, B, []) :- A > B, !.

list_primes(A, B, [A|L]) :-
    is_prime(A),
    !,
    A1 is A + 1,
    list_primes(A1, B, L).

list_primes(A, B, L) :-
    A1 is A + 1,
    list_primes(A1, B, L).

list_primes(A, B, L) :-
    A =< 2,
    A =< B,
    append([], [2], L).
	
smarandache(_, _, _, []).
smarandache(_, B, Num, _) :-
	Num > B.
	
smarandache(A, B, Num, [F|E]) :-
	A > Num,
	smarandache(A, B, F, E).	
	
smarandache(A, B, Num, [F|E]) :-
	not(crypto_is_prime(Num, [])),
	atom_concat(Num, F, X),
	atom_number(X, Y),
	%write('['),
	%write(Num),
	%writeln(']'),
	smarandache(A, B, Y, E).

smarandache(A, B, Num, [F|E]) :-
	crypto_is_prime(Num, []),
	writeln(Num),
	atom_concat(Num, F, X),
	atom_number(X, Y),
	smarandache(A, B, Y, E).
	
ex(T) :- 
	A is 2,
	B is 2**1000000,
	statistics(walltime, _),
	list_primes(2, 7500, [F|L]), 
	smarandache(A, B, F, L),
	statistics(walltime, [_|[T]]).