CC := g++ -std=c++11
CXXFLAGS += -O0 -Wall

SELECT := selection
BST := BST

ASTYLE := astyle --style=kr --indent=spaces=4 --suffix=none
ASTYLEFLAGS := --style=kr --indent=spaces=4 --suffix=none
CPPCHECK := cppcheck -I. --error-exitcode=1 .

$(PRE):
	$(CPPCHECK)
	astyle $(ASTYLEFLAGS) $(SELECT).cpp
	astyle $(ASTYLEFLAGS) $(BST).cpp

all: 
	$(PRE)
	$(CC) -o $(SELECT) $(CXXFLAGS) $(SELECT).cpp
	$(CC) -o $(BST) $(CXXFLAGS) $(BST).cpp

debug:
	$(PRE)
	$(CC) -o $(SELECT) $(CXXFLAGS) -g $(SELECT).cpp
	$(CC) -o $(BST) $(CXXFLAGS) -g $(BST).cpp

debugEXE:
	$(PRE)
	$(CC) -o $(SELECT).exe $(CXXFLAGS) -g $(SELECT).cpp
	$(CC) -o $(BST).exe $(CXXFLAGS) -g $(BST).cpp

style: $(SOURCES:.cpp=.astyle-check-stamp)
	$(PRE)

.PHONY: clean

clean:
	rm -rf $(SELECT) $(BST) $(SELECT).exe $(BST).exe