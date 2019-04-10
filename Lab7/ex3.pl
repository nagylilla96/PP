%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% calculul lui PI prin metoda monte carlo 		   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Creaza un pool cu N muncitori.
create_workers(QId, N) :-
	forall(between(1, N, _),
	thread_create(do_work(QId), _, [])).
	
% fiecare muncitor executa sarcini primite de la master
% muncitorii si masterul comunica printr-o coada de mesaje
% (coada are id-ul QId)
do_work(QId) :-
	thread_get_message(QId, munceste(Iteratii)),
	process(Iteratii,NC),
	thread_send_message(QId, rezultat(Iteratii,NC)),
	do_work(QId).
	
% process - genereaza I puncte aleatoare
% returneaza NC: numarul de puncte generate in cercul de raza 1
process(0,0).
process(I,NC) :-
	I1 is I-1,
	process(I1,N1),
	random(X),
	random(Y),
	in_cerc(X,Y,Increment),
	NC is N1 + Increment.
	
% in_cerc - returneaza 1 daca un punct dat e in cercul de raza 1,
% 0 in caz contrar
in_cerc(X,Y,1) :-
	X2 is X*X,
	Y2 is Y*Y,
	D is X2+Y2,
	D=<1.
in_cerc(_,_,0).

% masterul trimite o sarcina spre a fi executata
send_task(QId,Operatii) :-
	thread_send_message(QId, munceste(Operatii)).
	
% masterul asteapta dupa un rezultat din coada
get_result(QId) :-
	thread_get_message(QId, rezultat(N,NC)),
	retract(nrc(X)),
	retract(nr(Y)),
	X1 is X+NC,
	Y1 is Y+N,
	assert(nrc(X1)),
	assert(nr(Y1)).
	
% Masterul - coordoneaza muncitorii
% Primeste ca parametrii N: numarul de puncte ce trebuie generate si
% Operatii: numarul de operatii executate de un muncitor o data
% Colecteaza rezultatele primite de la muncitori si le salveaza
% in baza de date
master(QId,N, Operatii) :-
	Tasks is N / Operatii,
	forall(between(1, Tasks, _), send_task(QId,Operatii)),
	OperatiiRamase is N mod Operatii,
	send_task(QId,OperatiiRamase),
	forall(between(1, Tasks, _), get_result(QId)),
	get_result(QId).
	
% creaza thread-ul atasat producatorului
create_master(QId,N,Operatii,PId) :-
	thread_create(master(QId,N, Operatii), PId, []).
	
% Scopul principal - primeste ca parametrii N: numarul de iteratii si 
% NW: numarul de muncitori folositi
% Returneaza valoarea calculata pentru PI
calculate_pi(N,NW,PI) :-
	retractall(nrc(X)),
	retractall(nr(X)),
	assert(nrc(0)),
	assert(nr(0)),
	message_queue_create(QId),
	create_master(QId,N,100,PId),
	create_workers(QId,NW),
	thread_join(PId, S),
	retract(nr(X)),
	retract(nrc(Y)),
	format('Puncte totale: ~d Puncte in cerc: ~d\n',[X,Y]),
	PIpe4 is Y/X,
	PI is PIpe4*4.