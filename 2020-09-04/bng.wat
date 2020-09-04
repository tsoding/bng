(module
 (memory (import "js" "mem") 1)
 (func $print (import "js" "print") (param i32))
 (func (export "bng_size")
       (result i32)
       (i32.mul
        (i32.mul
         (i32.load (i32.const 4))
         (i32.load (i32.const 8)))
        (i32.const 4)))
 (func (export "bng_width")
       (result i32)
       (i32.load (i32.const 4)))
  (func (export "bng_height")
       (result i32)
       (i32.load (i32.const 8))))
