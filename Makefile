pa18: pa18.o List.hpp Stack.hpp
	$(CXX) $(CXXFLAGS) pa18.o -o pa18

pa18.o: pa18.cpp
	$(CXX) $(CXXFLAGS) pa18.cpp -c

clean:
	rm -f pa18.o pa18

turnin:
	turnin -c cs202 -p pa18 -v List.hpp Stack.hpp pa18.cpp Makefile
