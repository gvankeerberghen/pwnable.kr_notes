So we only get a binary.

Try gbd start on it returns a fail. Weird.

Running `strings` on it gives some gibberish, but one line popped out.
Saying this was packed with UPX and a link getting to: https://upx.github.io/

Reading that page makes it clear that a packer will compress the actual code and pack it.

From there, googling unpack upx brings many posts on how to unpack such code. They seem involved and require different tools. I mainly saw Windows tools so... I decided to see
what my friend at https://www.youtube.com/watch?v=l7dPPmVeRDw used and to stick to that.

Turns out he does unpack it but is clever about finding the flag. Let's try to re-do that
from memory.

Started by using `strace`, which logs system calls during the execution. Had to install it on Kali, easy with `apt install strace`.

```sh
$ strace ./flag
xecve("./flag", ["./flag"], 0x7ffece2b2800 /* 17 vars */) = 0
mmap(0x800000, 2959710, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, 0, 0) = 0x800000
readlink("/proc/self/exe", "/home/pwnable/flag/flag", 4096) = 23
mmap(0x400000, 2912256, PROT_NONE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x400000
mmap(0x400000, 790878, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x400000
mprotect(0x400000, 790878, PROT_READ|PROT_EXEC) = 0
mmap(0x6c1000, 9968, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0xc1000) = 0x6c1000
mprotect(0x6c1000, 9968, PROT_READ|PROT_WRITE) = 0
mmap(0x6c4000, 8920, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x6c4000
munmap(0x801000, 2955614)               = 0
uname({sysname="Linux", nodename="2506f4bf3f7c", ...}) = 0
brk(NULL)                               = 0xc7d000
brk(0xc7e1c0)                           = 0xc7e1c0
arch_prctl(ARCH_SET_FS, 0xc7d880)       = 0
brk(0xc9f1c0)                           = 0xc9f1c0
brk(0xca0000)                           = 0xca0000
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f420d6eb000
write(1, "I will malloc() and strcpy the f"..., 52I will malloc() and strcpy the flag there. take it.
) = 52
exit_group(0)                           = ?
+++ exited with 0 +++
```

So from there, and from previously running the program, we see syscalls to write and to exit_group at the end. Presumably when the flag it in memory.

Cool thing is that there's a way in gdb to stop on specific syscalls. Google it.
```
catch syscall <name>
```
Easy, start gdb, do `catch syscal exit_group` and run.
Bingo, gdb stopped there and if we're lucky the flag is somewhere in memory.

Ok so how do we look at the whole memory for strings?

There's a dump memory but it asks for adresses, dunno what to give.
I can print from the current stack, but nothing pops up.
Ok in the video he used something like core dump no? Googling brings more to generate core file, done that.

Then
```sh
strings <generated core file> | less
```
and searching for `:)` brings the flag. Ok yeah I knew it contained `:)`. Another way could have been to use the `-n` arg of strings to go faster. Or just scroll.

Bottom line, some nice shortcuts to get to a flag. In a "real" case one would have to manage unpacking the UPX. Google is there for that.


