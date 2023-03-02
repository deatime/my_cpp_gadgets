obj = curry expansion_for existential permute

all: ${obj}

curry: test_curry.cpp curry.hpp
	g++ -std=gnu++23 -o curry test_curry.cpp

expansion_for: test_expansion_for.cpp expansion_for.hpp
	g++ -std=gnu++23 -o expansion_for test_expansion_for.cpp

existential: test_existential.cpp existential.hpp
	g++ -std=gnu++23 -o existential test_existential.cpp

permute: test_permute.cpp permute.hpp
	g++ -std=gnu++23 -o permute test_permute.cpp

.PHONY: clean
clean:
	rm -f ${obj}
