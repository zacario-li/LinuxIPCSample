all:send receive ipc_daemon shm_client shm_server
flag = -g

send:send.c
	gcc -o $@ send.c $(flag)
receive:receive.c
	gcc -o $@ receive.c $(flag)
ipc_daemon:ipc_daemon.c
	gcc -o $@ ipc_daemon.c $(flag)
shm_client:shm_client.c
	gcc -o $@ shm_client.c $(flag)
shm_server:shm_server.c
	gcc -o $@ shm_server.c $(flag)

.PHONY: clean	
clean:
	rm send receive ipc_daemon shm_server shm_client
