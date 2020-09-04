(module
 (memory (export "primes") 700 700)
 (func $is_prime
       (param $x i32)
       (result i32)
       (local $prime i32)
       (local $i i32)
       (local $result i32)
       (set_local $i (i32.const 0))
       (block
        $exit
        (loop
         $top
         (set_local $prime (i32.load (i32.mul (get_local $i) (i32.const 4))))
         (set_local $result (i32.const 1))
         (br_if $exit (i32.gt_s (i32.mul (get_local $prime) (get_local $prime)) (get_local $x)))
         (set_local $result (i32.const 0))
         (br_if $exit (i32.eq (i32.rem_s (get_local $x) (get_local $prime)) (i32.const 0)))
         (set_local $i (i32.add (get_local $i) (i32.const 1)))
         (br $top)))
       (get_local $result))
 (func (export "prime")
       (param $n i32)
       (result i32)
       (local $primes_count i32)
       (local $x i32)
       (i32.store (i32.const 0) (i32.const 2))
       (set_local $primes_count (i32.const 1))
       (set_local $x (i32.const 2))
       (block
        $exit
        (loop
         $top
         (set_local $x (i32.add (get_local $x) (i32.const 1)))
         (br_if $exit (i32.ge_s (get_local $primes_count) (get_local $n)))
         (br_if $top (i32.eqz (call $is_prime (get_local $x))))
         (i32.store (i32.mul (get_local $primes_count) (i32.const 4)) (get_local $x))
         (set_local $primes_count (i32.add (get_local $primes_count) (i32.const 1)))
         (br $top)))
       (i32.load (i32.mul (i32.sub (get_local $primes_count) (i32.const 1)) (i32.const 4)))))
