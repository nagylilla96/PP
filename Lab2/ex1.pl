is_prime(2).
is_prime(X) :-
    X > 1,
    prime(X, 2).

prime(X, Y) :-
    Y >= X -> true;
    0 is X mod Y -> false;
    Z is Y + 1,
    prime(X, Z).
