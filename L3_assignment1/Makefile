compiler = g++

all: main.cpp 
	@echo all
	$(compiler) main.cpp workshop.cpp customer.cpp workorder.cpp services.cpp -I. -o main

clean: 
	@echo Cleaning...
	rm -rf *.o *.so *.a *.out

# This also removes the makefile unfortunately...	
#	ls | grep -v "\." | xargs rm 


