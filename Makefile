CXX := g++
CXXFLAGS := -std=c++17 -fsanitize=address -fsanitize=leak -fsanitize=undefined -Wall -Wextra -Werror -pedantic -pedantic-errors -march=native -mtune=native -fdata-sections -ffunction-sections -O2
LDFLAGS := -Wl,--gc-sections

schiffeversenken: $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o schiffeversenken

.o: $*.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $<

clean:
	find . -iname '*.o' -delete
	find . -iname '*.out' -delete
	rm -f schiffeversenken
