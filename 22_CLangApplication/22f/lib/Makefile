TARGET  = test
SRC     = $(TARGET).c
OBJ     = $(TARGET).o
LIB     = my_clib
LIB_SRC = $(LIB).c
LIB_OBJ = $(LIB).o
GCC     = gcc

all: $(TARGET)

$(OBJ): $(SRC)
	$(GCC) -o $@ -c $<

$(LIB_OBJ): $(LIB_SRC)
	$(GCC) -o $@ -c $<

$(TARGET): $(OBJ) $(LIB_OBJ)
	$(GCC) -o $@ $^ && ./$(TARGET)

clean:
	rm $(TARGET) $(OBJ) $(LIB_OBJ)
