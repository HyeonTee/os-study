CC = gcc
CFLAGS = -Wall -g

TARGETS = p1 p2 p3 p4 p5 p6 p7 p8

all: $(TARGETS)

run: $(FILE).c
	@$(CC) $(CFLAGS) -o $(FILE) $(FILE).c
	@./$(FILE)
	@rm -f $(FILE)

p1: p1.c
	$(CC) $(CFLAGS) -o p1 p1.c

p2: p2.c
	$(CC) $(CFLAGS) -o p2 p2.c

p3: p3.c
	$(CC) $(CFLAGS) -o p3 p3.c

p4: p4.c
	$(CC) $(CFLAGS) -o p4 p4.c

p5: p5.c
	$(CC) $(CFLAGS) -o p5 p5.c

p6: p6.c
	$(CC) $(CFLAGS) -o p6 p6.c

p7: p7.c
	$(CC) $(CFLAGS) -o p7 p7.c

p8: p8.c
	$(CC) $(CFLAGS) -o p8 p8.c

clean:
	rm -f $(TARGETS)
