CC:=gcc
CFLAGS:=

QSORT_TARGET=qsort
QSORTDL_TARGET=qsort_doublelinkedlist
QSORT_OBJ=qsort.o
QSORTDL_OBJ=qsort_doublelinkedlist.o

.DEFAULT:all

all: qsort qsort_doublelinkedlist

$(QSORT_TARGET): $(QSORT_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(QSORTDL_TARGET): $(QSORTDL_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -f *.o
	rm -f *.out
	rm -f $(QSORT_TARGET) $(QSORTDL_TARGET)
