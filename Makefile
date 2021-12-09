CC = g++
LINKERFLAG = -lm


%: %/main.exe phony
	

phony:
	

%/main.exe: %/main.o
	@${CC} ${LINKERFLAG} $< -o $@
	@./$@
	@rm -rf $< $@

%/main.o: %/main.cpp
	@${CC} -c $< -o $@