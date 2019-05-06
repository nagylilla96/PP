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

smarandache(Num) :-
	not(crypto_is_prime(Num, [])).

smarandache(Num) :-
	crypto_is_prime(Num, []),
	writeln(Num).
	
work(Q) :- 
	thread_get_message(Q, getnum(Num)),
	smarandache(Num).
	
create_workers(Q, Threads) :-
	Nr is Threads - 1,
	foreach(between(0, Nr, X), thread_create(work(Q), X, [])).
	
join_threads(Threads) :-
	Nr is Threads - 1,
	foreach(betweeen(0, Nr, X), thread_join(X)).
	
master(_, [], _, _).	

master(_, _, N, Threads) :- 
	N == Threads.
	
master([H|T], N, Threads) :-
	Id is N mod Threads,
	thread_send_message(Id, getnum(H)),
	N1 is N + 1,
	master(T, N1, Threads). 	
	
create_master(List, Threads) :-
	master(List, 0, Threads).
	
ex(Time, Threads) :- 
	A is 2,
	B is 2**100000,	
	list_primes(2, 7500, [F|L]), 
	list_numbers(A, B, F, L, C),
	statistics(walltime, _),
	message_queue_create(Q),
	create_master(C, Threads),
	create_workers(Q, Threads),
	join_threads(Threads),
	statistics(walltime, [_|[Time]]).