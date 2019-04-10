:- use_module(library(socket)).

%
% aplicatia server
%

create_server(Port, Workers):-
	create_socket(Port, S),
	message_queue_create(Q),
	forall(between(1, Workers,_),
	thread_create(worker(Q),_, [])),
	thread_create(acceptor(S, Q),Id, []),
	thread_join(Id,State).
	
create_socket(Port, Socket) :-
	tcp_socket(Socket),
	tcp_bind(Socket, Port),
	tcp_listen(Socket, 5).
	
acceptor(Socket, Q) :-
	tcp_accept(Socket, Client, Peer),
	thread_send_message(Q, Client),
	acceptor(Socket, Q).

worker(Q) :-
	thread_get_message(Q, Client),
	tcp_open_socket(Client, In, Out),
	format('Client conectat\n',[]),
	read(In, Command),
	format('Clientul a trimis %s\n',[Command]),
	close(In),
	process(Command, Out),
	close(Out),
	worker(Q).
	
process(Command, Out) :-
	format(Out, "Hello!\n", []).

%
% aplicatia client
%

create_client(Host, Port) :-
	format("Client creat",[]),
	tcp_socket(Socket),
	tcp_connect(Socket, Host:Port),
	tcp_open_socket(Socket, In, Out),
	format(Out, "Comanda\n", []),
	close(In),
	close(Out).
