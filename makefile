all:send receive ipc_daemon

send:send.c
	gcc -o $@ send.c
receive:receive.c
	gcc -o $@ receive.c
ipc_daemon:ipc_daemon.c
	gcc -o $@ ipc_daemon.c
	
clean:
	rm send receive ipc_daemon