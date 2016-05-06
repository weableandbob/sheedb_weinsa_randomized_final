extern crate rand;

use rand::Rng;
use rand::distributions::{IndependentSample, Range};

fn gen_alpha_sorted_array(alpha: f64, size: u32) -> Vec<u32> {
    let mut tmp: Vec<u32> = (0..size).collect();
    let num_to_replace = ((1.0-alpha) * (size as f64)) as usize;
    let mut rng = rand::thread_rng();
    let rand_index = Range::new(0, size);
    for i in 0..num_to_replace {
        let index = rand_index.ind_sample(&mut rng) as usize;
        if index == 0 {
            tmp[index] = tmp[index+1] + 1;
        } else {
            tmp[index] = tmp[index-1] - 1;
        }
    }
    tmp
}

fn main() {
    let mut rng = rand::thread_rng();
    //let vec = gen_alpha_sorted_array(0.9, 1_000_000_000);
    let vec = gen_alpha_sorted_array(0.9, 250_000_000);
    println!("{:?}", vec);
}
