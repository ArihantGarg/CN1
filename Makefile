compile:
	gcc server.c -o ./Executables/server
	gcc client.c -o ./Executables/client

server:
	./Executables/server

c1:
	./Executables/client 5000 cat

c2:
	./Executables/client 5001 carac

c3:
	./Executables/client 5002 banab

c4:
	./Executables/client 5003 nope

c5:
	./Executables/client 5004 i