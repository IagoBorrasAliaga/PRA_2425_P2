bin/testTableEntry: testTableEntry.cpp TableEntry.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp

clean:
	rm -rf *.o *.gch bin

bin/testBSTreeDict: testBSTreeDict.cpp BSTreeDict.h BSTree.h BSNode.h TableEntry.h Dict.h
	mkdir -p bin
	g++ -o bin/testBSTreeDict testBSTreeDict.cpp




bin/testBSTree: testBSTree.cpp BSTree.h BSNode.h
	mkdir -p bin
	g++ -o bin/testBSTree testBSTree.cpp
