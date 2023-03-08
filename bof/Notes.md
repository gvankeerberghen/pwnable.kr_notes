With much help from
https://www.youtube.com/watch?v=rwfKScdQybE
and ChatGPT for understanding assembly and gdb. 


Had to install big bunch of things to get gdb / gef working on the bare minimum Kali docker image.

Once I had gef working, launched it on the binary
```sh
gdb ./bof
```

In there, some useful commands were
```sh
break main # Didn't know how to find a better address
run
si # to do single steps over each operation
context # to bring back the view of the registers, stack etc
```
TODO: improve understanding of gef, namely,
- to learn how could I have seen the disassambled code of main and then func to know where to put a break point.
Answer from ChatGPT and trying:
```sh
gdb ./<binary>
start # Starts but breaks directly
# Move on from there, look at disassembled parts with, for instance
disassemble func # Can also write disas ;-)
```
- to manage si / s / continue correctly

Went on until after the program prompts for an input

Input a series of a's = `\x61`'s

Went on to the comparison between something and `0xcafebabe`:
```
0x56555654 <func+40>        cmp    DWORD PTR [ebp+0x8], 0xcafebabe
```
So the something we're comparing to sits at `$ebp+0x8`. Which I checked in gef with
```sh
x/32xw $ebp+0x8 # Prints 32 4-byte in hex with wide(?) mode
0xffffd560:	0xdeadbeef	0x00000000	0x00000000	0x00000000
0xffffd570:	0x00000000	0x00000070	0x00000000	0xf7dad295
...
```
With help from ChatGPT, the video, the code and much painful counting in hex, I finally managed to check below in memory and find my input of `0x61`'s compared to what `0xcafebabe` will be compared to (`0xdeadbeef`)
```
x/32xw $ebp-0x38
0xffffd520:	0xf7ffcff4	0x0000002c	0x00000000	0x61616161
0xffffd530:	0x61616161	0x61616161	0x61616161	0x61616161
0xffffd540:	0x61616161	0x61616161	0x61616161	0x61616161
0xffffd550:	0x61616161	0x61616161	0x61616161	0x61616161
0xffffd560:	0xdeadbe00	0x00000000	0x00000000	0x00000000
```
From there I counted that I had put 52 `0x61` to get to the 0xdeadbeef (with the null byte ending the string having just overwritten the first byte of `0xdeadbeef`).

So it only remained to use pwntools to send `0xcafebabe` in Little Endian preceeded by 52 bytes. Using pwntools as the video and its docs had shown.
