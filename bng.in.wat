#define WIDTH_OFFSET 4
#define HEIGHT_OFFSET 8
#define PIXEL_FORMAT_OFFSET 12
#define DATA_OFFSET 16

(module
 (memory (import "js" "mem") 1)
 (func $print (import "js" "print") (param i32))
 (func $byte_offset
       (param $index i32)
       (result i32)
       (i32.mul 
        (i32.sub 
         (i32.sub (i32.const 4) (get_local $index))
         (i32.const 1))
        (i32.const 8)))
 (func $get_byte
       (param $pixel i32)
       (param $index i32)
       (result i32)
       (i32.shr_u 
        (i32.and 
         (get_local $pixel)
         (i32.shl (i32.const 255) (call $byte_offset (get_local $index))))
        (call $byte_offset (get_local $index))))
 (func $set_byte
       (param $pixel i32)
       (param $index i32)
       (param $byte i32)
       (result i32)
       (i32.or
        (get_local $pixel)
        (i32.shl (get_local $byte) (call $byte_offset (get_local $index)))))
 (func $convert_pixel
       (param $pixel i32)
       (result i32)
       (local $result i32)
       (set_local $result (i32.const 0))
       (set_local $result
                  (call $set_byte (get_local $result)
                        (i32.const 0)
                        (call $get_byte (get_local $pixel)
                              (i32.load8_u (i32.const PIXEL_FORMAT_OFFSET)))))
       (set_local $result
                  (call $set_byte (get_local $result)
                        (i32.const 1)
                        (call $get_byte (get_local $pixel)
                              (i32.load8_u (i32.add (i32.const PIXEL_FORMAT_OFFSET)
                                                    (i32.const 1))))))
       (set_local $result
                  (call $set_byte (get_local $result)
                        (i32.const 2)
                        (call $get_byte (get_local $pixel)
                              (i32.load8_u (i32.add (i32.const PIXEL_FORMAT_OFFSET)
                                                    (i32.const 2))))))
       (set_local $result
                  (call $set_byte (get_local $result)
                        (i32.const 3)
                        (call $get_byte (get_local $pixel)
                              (i32.load8_u (i32.add (i32.const PIXEL_FORMAT_OFFSET)
                                                    (i32.const 3))))))
       (get_local $result))
 (func (export "bng_process")
       (local $index i32)
       (local $count i32)
       (local $address i32)
       (set_local $count (i32.mul (call $bng_width) (call $bng_height)))
       (block
        $exit
        (loop
         $repeat
         (br_if $exit (i32.ge_s
                       (get_local $index)
                       (get_local $count)))
         (set_local $address
                    (i32.add
                     (i32.const DATA_OFFSET)
                     (i32.mul
                      (get_local $index)
                      (i32.const 4))))
         (i32.store (get_local $address) (call $convert_pixel (i32.load (get_local $address))))
         (set_local $index (i32.add (get_local $index) (i32.const 1)))
         (br $repeat))))
 (func (export "bng_offset")
       (result i32)
       (i32.const DATA_OFFSET))
 (func $bng_width (export "bng_width")
       (result i32)
       (i32.load (i32.const WIDTH_OFFSET)))
 (func $bng_height (export "bng_height")
       (result i32)
       (i32.load (i32.const HEIGHT_OFFSET)))
 (func (export "bng_size")
       (result i32)
       (i32.mul
        (i32.mul
         (call $bng_width)
         (call $bng_height))
        (i32.const 4))))
