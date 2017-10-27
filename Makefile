all: test

JIMUPath=../JIMU
JIMUWarpper=$(JIMUPath)/PoolWarpper/
JIMULib=$(JIMUPath)/src
JIMUFile=$(wildcard $(JIMULib)/*.c)
JIMUHeader=$(wildcard $(JIMULib)/*.h)


CFLAG= -maes -msse2 -msse4.2 -march=corei7-avx `libgcrypt-config --cflags --libs`  -lm -O3 -I src -I $(JIMUWarpper) -I $(JIMULib)

PoolFile=PoolScheme.c
PoolHeader=aes.h block.h PRG.h PoolScheme.h JIMUPoolAPI.h

test: testG.out testE.out
	
testG.out:	$(addprefix src/, $(PoolFile)) $(addprefix src/, $(PoolHeader)) $(JIMUHeader) $(JIMUFile) $(JIMUWarpper)/PoolWarpper.h test/test.c
	gcc  $(addprefix src/, $(PoolFile)) $(JIMUFile) test/test.c -o testG.out $(CFLAG) -D ALICE

testE.out:	$(addprefix src/, $(PoolFile)) $(addprefix src/, $(PoolHeader)) $(JIMUHeader) $(JIMUFile) $(JIMUWarpper)/PoolWarpper.h test/test.c
	gcc  $(addprefix src/, $(PoolFile)) $(JIMUFile)  test/test.c -o testE.out $(CFLAG) -D BOB



clean: 
	rm -f *.out 
