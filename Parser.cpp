#include "Parser.h"

/*
	Parse constructor passes argStack to initalize memeber stack
*/
Parser::Parser(const std::stack<Token> &argStack)
	:Tokens{ argStack }, result{0}
{
	// push last token to end of the stack 
	syntax_Analysis(); 
}


/*
	Returns the result of the calculation 
*/
double Parser::getResult()  
{
	return this->result; 
}

/*
	Void function parses the tokens on the stack and checks if 
	it is a valid parsing tree 
*/
void Parser::syntax_Analysis()
{
	
	// starts here 
	result = parse_Expression();	// start the expression 
	// check end of file 
	check_EOF(); 
}

/*
	Void function parses each token asscoiated with rule Expression 
		
	Expression -> Term PLUS Expression 
	Expression -> Term MINUS Expression 

*/
double Parser::parse_Expression()

{
	
	double left = parse_Term(); 
	
	Token t2 = getToken(); 


	while (true)
	{
		if (t2.kind == PLUS)
		{

			left += parse_Term();
			t2 = getToken();
		}
		else if (t2.kind == MINUS)
		{
			left -= parse_Term();
			t2 = getToken();
		}
		else
		{
			ungetToken(t2); 
			return left; 
		}
	}

}


/*
	Returns a double while consumes tokens from the stack 
	calls corresponding rules

	
	Term -> Primary Term Mulitply Primary 
	Term -> Primary Term Divide Primary
	Term -> Primary Term Divisor Primary 
*/
double Parser::parse_Term() 
{
	double left{ 0 }; 

	left = parse_Primary(); 
	
	// getToken again 
	 Token t2 = getToken(); 


	while (true) 
	{
		if (t2.kind == MULIIPLY) 
		{
			// Consume * 
			left *= parse_Primary(); 
			t2 = getToken(); 
		}
		else if (t2.kind == DIVIDE)
		{
			double temp = parse_Primary();
			if (temp == 0) 
			{
				throw std::runtime_error("Can not divide by 0");
			}
			// Consume  
			left /= temp; 
			t2 = getToken(); 
		}
		else
		{
			// just return the value of left since next token is another rule
			ungetToken(t2); 
			return left;  
		}
	}

	return left; 
}

/*
	Primary -> Number 
	Primary -> LeftParen Expression RightParen 
*/
double Parser::parse_Primary() 
{
	Token t = getToken(); 
	double left{ 0 }; 
	if (t.kind == LEFTPAREN) 
	{
		// consume token (
		left = parse_Expression();

		// Consume token ) 
		t = getToken(); 

		if (t.kind != RIGHTPAREN) 
		{
			syntax_Error(); 
		}
		
	}
	else if (t.kind == DOUBLE) 
	{
		// let number hajdle it
		ungetToken(t);
		left = parse_Number(); 
	}
	else 
	{
		syntax_Error(); 
		return 0; 
	}

	return left; 
	
}

double Parser::parse_Number()  
{
	Token t = getToken(); 
	double left = t.value; 
	if (t.kind == DOUBLE) 
	{
		// just consume the token
		return left; 
	}
	else 
	{
		syntax_Error(); 
		return 0; 
	}
}


/*
	Void function checks if last token is EOF if not then error 
*/
void Parser::check_EOF()
{
	// Get and consume the token 
	Token t = getToken(); 
	if (t.kind != ENDOFFILE)
	{
		syntax_Error(); 
	}
}


/*
	Void function throws a syntax error 
*/
void Parser::syntax_Error()
{
	throw std::runtime_error("Syntax Error");
}



/*
	Pops token from the stack and returns it to the caller 
*/
Token Parser::getToken() 
{
	Token t = this->Tokens.top(); 
	this->Tokens.pop(); 
	return t; 
}


/*	
	Adds token back to the stack
*/
void Parser::ungetToken(Token t) 
{
	this->Tokens.push(t); 
}

