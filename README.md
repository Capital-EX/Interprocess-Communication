# OS Interals and Design Final Project

This project was constructed for OS Internals and Design.  It uses the follow 
interpocess communication system:

* Pipes
* Network Sockets
* Message Passing
* Shared Memory
 
I also included the essay I wrote for this project.

## Running
Each program was designed to run on Linux. pipes, network sockets, and shared memory 
where all compiled using GCC-7. Additionally, the network sockets project requires a 
working installation of [Rust](https://www.rust-lang.org/).  Each, project can be 
built and ran through make using the following commands:

|Project            | Build Command                 | Run Command                   |
|:---:              | :---:                         | :---:                         |
| Pipes             | `make build-pipes`            | `make run-pipes`              |
| Netwwork Sockets  | `make build-sockets`          | `make run-sockets`            |
| Message Passing   | `make build-message-passing`  | `make run-message-passing`    |
| Shared Memory     | `make build-shared`           | `make run-shared`             |

Finally, veriyf.py is a simple script that check the contents of each programs output
files.