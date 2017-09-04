IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11

ODIR=obj
LDIR =../lib

LIBS=-lwiringPi

_DEPS = $(shell find $(IDIR) -type f)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = ABE_ADCPi.o SensorManager.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST_FILES = ABE_ADCPi.o test.o
TEST_FILES = $(patsubst %,$(ODIR)/%,$(_TEST_FILES))

_TEST_BNO = test_BNO055.o Adafruit_BNO055.o 
TEST_BNO = $(patsubst %,$(ODIR)/%,$(_TEST_BNO))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

firm: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

testmake: $(TEST_FILES)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

testbno: $(TEST_BNO)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
