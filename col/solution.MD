From the code, understand what values one needs to insert in order to get to the right sum.

0x00 doesn't work well because it's understood as the end of an argument, so use 0x01. But then one needs to subtract the sum of these from the total to get and use the last bytes to get to that total.

Feeding bytes, instead of ASCII to the program can be done with python.

# Locally with python3
```sh
./col `python3 -c "import sys;sys.stdout.buffer.write(b'\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\xe8\x05\xd9\x1d')"`
```

# Remotely with Python 2
```sh
/col `python -c "print('\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\xe8\x05\xd9\x1d')"`
```
