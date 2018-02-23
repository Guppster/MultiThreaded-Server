# MultiThreaded-Server
A multi threaded server made using pthreads libary 

## Description:
A multithreaded server that creates a thread pool with N threads.
When a new client request arrives, the server should add it to a queue of connections.
The threads should remove one connection from the queue and handle the request. If the
connection queue does not have a connection available, the thread should “sleep” until a
connection is ready. The connection queue is shared among all threads and thus requires
synchronization to protect access to the connection queue.
The processing to be done on behalf of the client is to take a number sent from the client,
multiply it by 10 and return the result back to the client.
Program should not use busy waiting.

## Purpose:
1. Learn how to use the pthreads library to manage threads 
2. Understand how to create a multi-threaded server 
3. Understand how and where to use basic thread synchronization 
4. Gain practice with client software that can issue multiple requests over a socket.

## Usage:
*Server Command Line Input:* Port number that will be used to listen on, number of
threads, size of connection array

*Client Command Line Input:* Server’s host name, port number and the number to be
multiplied


