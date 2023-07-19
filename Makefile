TARGET=add-nbo.cpp
CXXFLAGS=-g

all: $(TARGET)

$(TARGET): nbo-add.o
	$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f $(TARGET)
	rm -f *.o

