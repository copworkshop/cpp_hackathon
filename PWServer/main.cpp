#include <iostream>

#include <PWServer.h>
#include <PWException.h>

int main(int argc, char* argv[])
{
	std::string infile,dbfile,outfile;
	if (argc != 5) {
		std::cerr << "Usage: " <<argv[0]<< " /infile <filename> /outfile <filename>"<<std::endl;
		std::cerr << "		 " <<argv[0]<< " /db <filename> /outfile <filename>"<<std::endl;
		return 1;
	}
	for (int i = 1; i < argc; i += 2) {
        std::string argName = argv[i];
        if (argName == "/infile") {
            infile = argv[i + 1];
        } else if (argName == "/outfile") {
            outfile = argv[i + 1];
        }else if (argName == "/db") {
            dbfile = argv[i + 1];
        } else {
            std::cerr << "Unknown argument: " << argName << std::endl;
            return 1;
        }
    }
	if(!infile.empty() && !dbfile.empty()){
		std::cerr << "Cannot use JSON and DB at the same time"<<std::endl;
		std::cerr << "Usage: " <<argv[0]<< " /infile <filename> /outfile <filename>"<<std::endl;
		std::cerr << "		 " <<argv[0]<< " /db <filename> /outfile <filename>"<<std::endl;
		return 1;
	}

	try
	{

		if(!dbfile.empty()){
			PWServer server(dbfile, outfile,true);
			server.Start();
		
		}
		else {
			PWServer server(infile, outfile);
			server.Start();
		}
	}
	catch (const PWException& exp)
	{
		std::cout << exp.what();
		return -1;
	}

    return 0;
}
