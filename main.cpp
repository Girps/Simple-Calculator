#include<iostream>
#include<string>
#include "Tokenizer.h"
#include "Parser.h"
#include <sstream>


int main() 
{
	try 
	{
	
		std::string line;

		std::getline(std::cin, line); 
		

		Tokenizer t(line); 
		auto v = t.getVector(); 
	

		Parser syn(t.getStack()); 
		std::cout << syn.getResult(); 

	}
	catch (std::exception &e) 
	{
		std::cerr << e.what(); 
	}

	return 0; 

}