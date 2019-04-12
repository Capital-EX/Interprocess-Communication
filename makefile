build-pipes:
	cd pipes; make build; 

run-pipes: build-pipes
	cd pipes; make run;

build-message-passing:
	cd message-passing; make build

run-message-passing: build-message-passing
	cd message-passing; make run

build-sockets:
	cd sockets; cargo build

run-sockets: build-sockets
	cd sockets; cargo run

build-shared:
	cd shared; make build

run-shared:
	cd shared; make run