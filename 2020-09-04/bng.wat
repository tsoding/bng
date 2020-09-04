(module
 (memory (import "js" "mem") 1)
 (func $print (import "js" "print") (param i32))
 (func (export "bng")
       (call $print (i32.load (i32.const 0)))
       (call $print (i32.load (i32.const 4)))
       (call $print (i32.load (i32.const 8)))))
