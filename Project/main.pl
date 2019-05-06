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
	
create_workers(_, _, _, []).

create_workers(_, 0, _, _).
	
create_workers(Q, N, Threads, [Id|L]) :-
	thread_create(work(Q), Id, []),
	N1 is N - 1,
	create_workers(Q, N1, Threads, L).
	
join_threads([]).
	
join_threads([H|T]) :-
	thread_join(H),
	join_threads(T).
	
master(_, [], _, _).	

master(_, _, N, Threads) :- 
	N == Threads.
	
master(Q, [H|T], N, Threads) :-
	thread_send_message(Q, getnum(H)),
	N1 is N + 1,
	master(Q, T, N1, Threads). 	
	
create_master(Q, List, Threads) :-
	master(Q, List, 0, Threads).
	
ex(Time, Threads) :- 
	A is 2,
	B is 2**100000,	
	list_primes(2, 7500, [F|L]), 
	list_numbers(A, B, F, L, C),
	statistics(walltime, _),
	message_queue_create(Q),
	create_master(Q, C, Threads),
	create_workers(Q, Threads, Threads, Ids),
	join_threads(Ids),
	statistics(walltime, [_|[Time]]).