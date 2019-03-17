default: ctc grid

ctc: ctc.c
	gcc -o ctc ctc.c

grid: grid.c
	gcc -o grid grid.c

.PHONY: clean
clean:
	rm -f ctc grid ./*.txt
