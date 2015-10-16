# Serial Over TCP

This application includes two programs: Server and Client. The Client Connects to Server and Send a Message then The server forwards it to Serial Port.The Serial Port sends Response to Server and The server Forwards it to Client.
The Components are as follows:
  - TCP Server
  - Client
  - Serial Port

For Testing this system we make a virtual serial port by "socat" which are back to back ports.Then Test it by Sending a Message.

 
### Version
1.0.0

### Installation
The Virtual Serial Port:

```sh
# socat -d -d pty,raw,echo=0 pty,raw,echo=0
```
Reading The Serial Port in New Terminal:

```sh
# cat < /dev/pts/5
```

The Server:

```sh
# cd Server
# ./server PortNumber
```

The Client:

```sh
# cd Client
# ./client HostName PortNumber
```
Then Type The Message in Client Program, It will show up in Server then in Serial Port Terminal.
Then The Serial Port Response will go to Server Then to Client.



