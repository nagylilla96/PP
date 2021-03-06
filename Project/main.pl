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
	Num == 0, !.
	%writeln("Got finish message")
	
work(Q) :- 
	thread_get_message(Q, getnum(Num)),
	smarandache(Num),
	%write("["), write(Num), writeln("]"),
	work(Q).

create_workers(_, 0, []) :- !.
	
create_workers(Q, N, [Id|L]) :-
	%writeln("Creating workers"),
	thread_create(work(Q), Id, []),
	N1 is N - 1,
	create_workers(Q, N1, L).
	
join_threads([]).
	
join_threads([H|T]) :-
	thread_join(H),
	join_threads(T).
	
master(Q, [], 0) :- thread_send_message(Q, getnum(0)), !.
	
master(Q, [], Threads) :- 
	%writeln("Sending finish message"),
	thread_send_message(Q, getnum(0)),
	T1 is Threads - 1,
	master(Q, [], T1).
	
master(Q, [H|T], Threads) :-
	thread_send_message(Q, getnum(H)),
	master(Q, T, Threads). 	
	
create_master(Q, List, Threads) :-
	master(Q, List, Threads).
	
project(Time, Threads) :- 
	A is 2,
	B is 2**1000000,	
	list_primes(2, 10000, [F|L]), 
	list_numbers(A, B, F, L, C),
	statistics(walltime, _),
	message_queue_create(Q),
	create_master(Q, C, Threads),
	%write("Threads = "), writeln(Threads),
	create_workers(Q, Threads, Ids),
	join_threads(Ids),
	statistics(walltime, [_|[Time]]).