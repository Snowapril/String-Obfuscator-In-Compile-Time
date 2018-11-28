# String Obfuscator in Compile Time
##### C++ String Obfuscator using Metaprogramming.
Wrapping string literals using	 OBFUSCATE macro prevents string literals appearing in object files as it is. Actually, it is not impossible to figure obfuscated codes out, but obfuscating makes reverse-engineering difficult and time-consuming. 

## How to use

1. just include source codes in directory "include".
2. Wrap your raw string literal with "OBFUSCATE" macro.

``` c++
#include <iostream>
#include "obfuscator.hpp"

int main(void) { 
	std::cout << OBFUSCATE("Private Key") << std::endl;
	return 0;
}
```

## Features

##### Before Obfuacating (Compile options : -O3 -march=native -fPIC -g)

``` c++
#include <iostream>
int main(void) {
    std::cout << "snowapril" << std::endl;
    return 0;
}
```
``` assembly
Dump of assembler code for function main():
   0x00403b90 <+0>:     push   %ebp
   0x00403b91 <+1>:     mov    %esp,%ebp
   0x00403b93 <+3>:     and    $0xfffffff0,%esp
   0x00403b96 <+6>:     sub    $0x10,%esp
   0x00403b99 <+9>:     call   0x4019c0 <__main>
   0x00403b9e <+14>:    movl   $0x9,0x8(%esp)
   0x00403ba6 <+22>:    movl   $0x405064,0x4(%esp)
   0x00403bae <+30>:    movl   $0x40825c,(%esp)
   0x00403bb5 <+4>:     call   0x401478 <_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_i>
   0x00403bba <+9>:     movl   $0x40825c,(%esp)
   0x00403bc1 <+4>:     call   0x401470 <_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_>
   0x00403bc6 <+9>:     xor    %eax,%eax
   0x00403bc8 <+11>:    leave
   0x00403bc9 <+12>:    ret
End of assembler dump.

(gdb) x /s 0x405064
>> 0x405064 <_Jv_RegisterClasses+4214884>: "snowapril"
```

##### After Obfuscating (Compile options : -O3 -march=native -fPIC -g)

``` c++
#include <iostream>
#include "obfuscator.hpp"
int main(void) {
    std::cout << OBFUSCATE("snowapril") << std::endl;
    return 0;
}
```
``` assembly
Dump of assembler code for function main():
   0x00403b90 <+0>:     push   %ebp
   0x00403b91 <+1>:     mov    %esp,%ebp
   0x00403b93 <+3>:     and    $0xfffffff0,%esp
   0x00403b96 <+6>:     sub    $0x40,%esp
   0x00403b99 <+9>:     call   0x4019c0 <__main>
   0x00403b9e <+14>:    lea    0x10(%esp),%eax
   0x00403ba2 <+18>:    movl   $0x408258,(%esp)
   0x00403ba9 <+4>:     movl   $0x4,0x1c(%esp)
   0x00403bb1 <+12>:    movl   $0x10,0x20(%esp)
   0x00403bb9 <+20>:    movl   $0x27,0x24(%esp)
   0x00403bc1 <+28>:    mov    %eax,0x4(%esp)
   0x00403bc5 <+32>:    movl   $0x60,0x28(%esp)
   0x00403bcd <+40>:    movl   $0x62,0x2c(%esp)
   0x00403bd5 <+48>:    movl   $0x3e,0x30(%esp)
   0x00403bdd <+56>:    movl   $0x6c,0x34(%esp)
   0x00403be5 <+64>:    movl   $0x1c,0x38(%esp)
   0x00403bed <+72>:    movl   $0x61,0x3c(%esp)
   0x00403bf5 <+80>:    movb   $0x73,0x10(%esp)
   0x00403bfa <+85>:    movb   $0x6e,0x11(%esp)
   0x00403bff <+90>:    movb   $0x6f,0x12(%esp)
   0x00403c04 <+95>:    movb   $0x77,0x13(%esp)
   0x00403c09 <+100>:   movb   $0x61,0x14(%esp)
   0x00403c0e <+105>:   movb   $0x70,0x15(%esp)
   0x00403c13 <+110>:   movb   $0x72,0x16(%esp)
   0x00403c18 <+115>:   movb   $0x69,0x17(%esp)
   0x00403c1d <+120>:   movb   $0x6c,0x18(%esp)
   0x00403c22 <+125>:   movb   $0x0,0x19(%esp)
   0x00403c27 <+130>:   call   0x401470 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc>
   0x00403c2c <+135>:   mov    %eax,(%esp)
   0x00403c2f <+138>:   call   0x401478 <_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_>
   0x00403c34 <+143>:   xor    %eax,%eax
   0x00403c36 <+145>:   leave
   0x00403c37 <+146>:   ret
End of assembler dump.
```

## Reference
largely referenced on https://github.com/andrivet/ADVobfuscator
