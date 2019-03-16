ctc: ctc.c
	gcc -o ctc ctc.c

.PHONY: clean
clean:
	rm -f ctc ./*.txt
