all:
	@tput setaf 2;
	@echo [COMPILING PRIMES.HPP]
	@tput setaf 7;
	clang++ primes.hpp -std=c++11
	@tput setaf 2;
	@echo [LINKING PRIMES.HPP INTO MAIN.CPP]
	@echo [COMPILING MAIN.HPP]
	@tput setaf 7;
	clang++ main.cpp -std=c++11 -o main
	@tput setaf 2;
	@echo [COMPILATION WAS SUCCESSFUL]
clean:
	@clear;
	@tput setaf 1;
	@echo [MAIN WAS REMOVED SUCCESSFUL]
	@tput setaf 7;
	rm main primes.hpp.gch
