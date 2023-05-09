#include "Tokenizer.h"


Tokenizer::Tokenizer(std::vector<std::string> str_List)
	:raw_String{str_List}
{
	// Call function to convert strings to tokens 
	Lexical_Analysis();	
}

/* Initliaze our tokens initalize arg to 0 assuming token is not a literal number */
Token::Token(Types t, double arg = 0)
	:value{ arg }, kind{t}
{
}

/*	Tokenize each string on the stack holding raw strings */
void Tokenizer::Lexical_Analysis() 
{
	std::stringstream buf; 
	this->Tokens_List.push_back(Token(ENDOFFILE,0));
	this->Tokens_Stack.push(Token(ENDOFFILE,0)); 
	// iterate through out raw vector of strigns and tokenize each element 
	for(auto it = raw_String.rbegin(); it != raw_String.rend(); ++it)
	{	
		char ch = it->at(0);
		// Check first character of each string 
		switch (ch) 
		{
			// Check for operators 
		case('('):	// plus
			this->Tokens_Stack.push(Token(LEFTPAREN));
			this->Tokens_List.push_back(Token(LEFTPAREN));
			break;
		case(')'):	// plus
			this->Tokens_Stack.push(Token(RIGHTPAREN));
			this->Tokens_List.push_back(Token(RIGHTPAREN));
			break;
			// Check for operators 
		case('+'):	// plus
			this->Tokens_Stack.push(Token(PLUS)); 
			this->Tokens_List.push_back(Token(PLUS)); 
			break; 
		case('-'):	// minus
			this->Tokens_Stack.push(Token(MINUS));
			this->Tokens_List.push_back(Token(MINUS)); 
			break;
		case('/'):	// divide
			this->Tokens_Stack.push(Token(DIVIDE));
			this->Tokens_List.push_back(Token(DIVIDE));
			break; 
		case('*'):	// mulitply
			this->Tokens_Stack.push(Token(MULIIPLY));
			this->Tokens_List.push_back(Token(MULIIPLY)); 
			break;
		case('%'):	// divisor
			this->Tokens_Stack.push(Token(DIVSOR));
			this->Tokens_List.push_back(Token(DIVSOR)); 
			break; 
			// All these cases its a token holding a numerical value 
		case('.'):
		case ('0'): 
		case ('1'):
		case('2'): 
		case('3'): 
		case('4'):
		case('5'):
		case('6'):
		case('7'): 
		case('8'):
		case('9'): 
			{
				unsigned int i = 0; 
				double v = std::stod(*it, &i);	// check how many chars processed 
				if (i < it->size())	// not all processed throw 
				{
					throw std::runtime_error("Tokenizer error");
				}
				// Check if it conforms 
				Token temp(DOUBLE, v);
				this->Tokens_Stack.push(temp);
				this->Tokens_List.push_back(temp); 
			}
			break; 
		default: 
			throw std::runtime_error("Tokenizer error");
			break; 
		}
	}
}




// Return of a vector of tokens 
std::vector<Token>  Tokenizer::getVector() 
{
	return this->Tokens_List; 
}

// Return a stack of tokens 
std::stack<Token> Tokenizer::getStack() 
{
	return this->Tokens_Stack; 
}