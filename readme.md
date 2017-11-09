# PoolFramework

Pool is a programming support for active-secure two-party computation. See details [here](http://homes.soic.indiana.edu/yh33/mypub/pool.pdf).
Documentation is available [here](https://jimu-pool.github.io/PoolFramework/)

# Pre-required packages: 
gcc, make, libgcrypt-dev.

# Underlying Protocol 
Clone the underlying protocol repository[here](https://github.com/jimu-pool/JIMU) and this one  under the same dictionary, for example:

Pool/JIMU

Pool/PoolFrameWork

# How to run the code:
1. Go to Pool/JIMU/src/client, and change "localhost" in line 19 to the address to the IP address of the garbler. (Skip this step if tested on localhost).

2. Go to Pool/PoolFrameWork/, and run:

```sh
$ make
```

to compile

3. run
```sh
./testG.out 12345
```

and 

```sh
./testE.out 12345
```
on separated windows to execute the test code. (12345 is the port number)







