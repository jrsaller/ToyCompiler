CXXFLAGS := -std=c++11

main: Main.o Token.o StateMachine.o Scanner.o Symbol.o
	g++ $(CXXFLAGS) -o $@ $^

Main.o: Main.cpp Token.h
	g++ $(CXXFLAGS) -c $<

Token.o: Token.cpp Token.h
	g++ $(CXXFLAGS) -c $<

Scanner.o: Scanner.cpp Scanner.h Token.h StateMachine.h
	g++ $(CXXFLAGS) -c $<

StateMachine.o: StateMachine.cpp StateMachine.h
	g++ $(CXXFLAGS) -c $<

Symbol.o: Symbol.cpp Symbol.h
	g++ $(CXXFLAGS) -c $<


clean:
	rm *.o main



