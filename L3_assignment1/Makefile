compiler = g++

all: main.cpp 
	@echo all
	$(compiler) main.cpp customer.cpp services.cpp workshop.cpp -I. -o main
#	$(compiler) miniproject_main.cpp miniproject_cell.cpp miniproject_grid.cpp miniproject_BF.cpp mini_def.h -I. -o miniproject 


clean: 
	@echo Cleaning...
	rm -rf *.o *.so *.a *.out

# This also removes the makefile.	
#	ls | grep -v "\." | xargs rm 


