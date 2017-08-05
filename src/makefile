IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11

ODIR=obj
LDIR =../lib

LIBS=-lwiringPi

_DEPS = $(shell find $(IDIR) -type f)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = demo-adcread.o ABE_ADCPi.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST_BNO = test_BNO055.o Adafruit_BNO055.o 
TEST_BNO = $(patsubst %,$(ODIR)/%,$(_TEST_BNO))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

testmake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

testbno: $(TEST_BNO)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
