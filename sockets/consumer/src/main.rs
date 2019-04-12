use std::net::TcpListener;
use std::fs::File;
use std::io::prelude::*;

fn main() {
    println!("Consumer process listening on 127.0.0.1:8888");
    let listener = TcpListener::bind("127.0.0.1:8888").unwrap();
    let mut results = File::create("../consumer.txt").unwrap();
    let mut string = String::new();
    loop {
        let (mut socket, _) = listener.accept().unwrap();
        string.clear();
        socket.read_to_string(&mut string).unwrap();
        if string == "finished" {
            break;
        } else {
            write!(results, "{}\n", string).unwrap();
        }
    }
}