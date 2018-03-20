TARGET=c4bot

CC=g++
CFLAGS=-c -Wall -std=c++17 -O2 -static
LDFLAGS=

DEPS=$(wildcard *.h)
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:%.cpp=%.o)

all: $(TARGET)
	
$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean zip

zip:
	zip $(TARGET).zip *.h *.cpp 

clean:
	rm -rf $(OBJECTS) $(TARGET) $(TARGET).zip

