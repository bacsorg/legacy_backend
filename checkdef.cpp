#include <stdexcept>
#include <iostream>
#include <fstream>

enum error_code
{
	OK=0,
	WA=2,
	PE=4,
	UN=100
};

error_code check_LN(std::ifstream &in)
{
	char c;
	while (in.get(c))
	{
		if (c!='\n')
			return WA;
	}
	return OK;
}

int main(int argc, char **argv)
{
	try
	{
		if (argc!=3+1)
			throw std::invalid_argument("wrong argument count");
		//std::ifstream in(argv[1]);
		std::ifstream out(argv[2]);
		std::ifstream cout(argv[3]);
		if (!out.good())
			throw std::runtime_error("bad file: \""+std::string(argv[2])+"\"");
		if (!cout.good())
			throw std::runtime_error("bad file: \""+std::string(argv[3])+"\"");
		char o, c;
		while (out.get(o) && cout.get(c))
			if (o!=c)
				return WA;
		if (out.eof() && cout.eof())
			return OK;
		else
		{
			if (out.eof())
				return check_LN(cout);
			else
				return check_LN(out);
		}
	}
	catch (std::exception &e)
	{
		std::cerr<<"Error: "<<e.what()<<std::endl;
		std::cerr<<"Usage: checkdef <input file> <output file generated by solution> <correct output file>"<<std::endl<<std::endl;
		std::cerr<<"Return codes:"<<std::endl;
		std::cerr<<"\t"<<OK<<" - OK"<<std::endl
			<<"\t"<<WA<<" - Wrong Answer"<<std::endl
			<<"\t"<<PE<<" - Presentation Error"<<std::endl
			<<"\t"<<UN<<" - Invalid parameters or check error"<<std::endl;
		return UN;
	}
}

