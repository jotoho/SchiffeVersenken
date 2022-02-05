VERSION=\"$(shell git describe --tags --always --dirty)\"
CXX := x86_64-w64-mingw32-g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -pedantic -pedantic-errors -march=native -mtune=native -fdata-sections -ffunction-sections -O2 -DSCHIFFEVERSENKEN_VERSION=$(VERSION)
LDFLAGS := -Wl,--gc-sections

schiffeversenken: $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o schiffeversenken -pthread

schiffeversenken-sanitizing: $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
	$(CXX) $(CXXFLAGS) -fsanitize=address -fsanitize=leak -fsanitize=undefined $^ $(LDFLAGS) -o schiffeversenken

.o: $*.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $<

clean:
	find . -iname '*.o' -delete
	find . -iname '*.out' -delete
	rm -f schiffeversenken
