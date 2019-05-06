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
	
list_numbers(_, _, _, [], _).

list_numbers(_, B, Num, _, []) :-
	Num > B.
	
list_numbers(A, B, Num, [F|E], L) :-
	A > Num,
	list_numbers(A, B, F, E, L).		
	
list_numbers(A, B, Num, [F|E], [Num|L]) :-
	atom_concat(Num, F, X),
	atom_number(X, Y),
	%writeln(Y),
	list_numbers(A, B, Y, E, L).
	
smarandache([]).

smarandache([F|E]) :-
	not(crypto_is_prime(F, [])),
	smarandache(E).

smarandache([F|E]) :-
	crypto_is_prime(F, []),
	writeln(F),
	smarandache(E).
	
worker(L
	
create_threads(0, _).
	
create_threads(Threads, L) :-
	Id is Threads - 1,
	thread_create(worker(L), Id, []),
	create_threads(Id, L).
	
create_workers(Id, List, Threads) :-
	forall(between(1, Threads, _),
	thread_create(do_work(Id, List), _, [])).
	
join_threads(0).
	
join_threads(Threads) :-
	Id is Threads - 1,
	thread_join(Id, S),
	join_threads(Id).
	
master(Threads, L) :-
	create_threads(Threads, L),
	join_threads(Threads).

	
ex(Time, Threads) :- 
	A is 2,
	B is 2**100000,	
	list_primes(2, 7500, [F|L]), 
	list_numbers(A, B, F, L, C),
	statistics(walltime, _),
	master(Threads, C),
	smarandache(C),
	statistics(walltime, [_|[Time]]).