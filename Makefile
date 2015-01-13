hom_p1: hom_p1.cpp hom_p1.o
%: %.cpp
	g++ -std=c++11 $< -o $@ -g

%: %.c
	gcc $< -o $@

clean:
	rm -f *.o $(EXECUTABLE) hom_p1.o