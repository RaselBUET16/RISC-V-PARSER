all:
	g++ main.cpp Tokenizer.cpp Instruction.cpp InstructionSet.cpp -o output
clean:
	rm -rf *.o output