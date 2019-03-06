% ex1

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


all_primes(A, B, L, T) :-
    list_primes(A, B, L),
    statistics(runtime, [T|_]).

% ex2

ones([], 0).

ones([H|T], R) :-
    R1 is popcount(H),
    ones(T, R2),
    R is R1 + R2.

gen(0, []) :- !.
gen(N, [H|T]) :- 
    H is random(256),
    N1 is N - 1,
    gen(N1, T).

entropy(N, R, Time) :-
    gen(N, L), 
    ones(L, O),
    T is N * 8,
    Z is T - O,
    R is -(O / T) * log(O / T) / log(2) - (Z / T) * log(Z / T) / log(2),
    statistics(runtime, [Time|_]).