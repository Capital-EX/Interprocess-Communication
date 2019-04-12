extern crate rand;
use std::net::TcpStream;
use std::fs::File;
use std::io::prelude::*;
use rand::prelude::*;

fn main() {
    let mut results = File::create("../producer.txt").unwrap();
    let mut rng = rand::thread_rng();
    for _ in 0..100 {
        let mut stream = TcpStream::connect("127.0.0.1:8888").unwrap();
        let x: i64 = rng.gen();
        write!(stream, "{}", x).unwrap();
        write!(results, "{}\n", x).unwrap();
    }
    let mut stream = TcpStream::connect("127.0.0.1:8888").unwrap();
    write!(stream, "finished");
}
