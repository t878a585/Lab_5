all: sales nfl

sales: sales.o
	gcc sales.o -o sales

nfl: nfl.o
	gcc nfl.o -o nfl

clean:
	rm *.o sales nfl

.PHONY: all
.PHONY: debug
.PHONY: clean
