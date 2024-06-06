#include <PWServer.h>
#include <PWException.h>

#include <iostream>

/**
 * The main function of the program.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of C-style strings containing the command-line arguments.
 * @return The exit status of the program.
 */
int main(int argc, char* argv[])
{
	std::string infile,outfile;
	if (argc != 5) {
		std::cerr << "Usage: " <<argv[0]<< " /infile <filename> /outfile <filename>"<<std::endl;
		return 1;
	}
	for (int i = 1; i < argc; i += 2) {
        std::string argName = argv[i];
        if (argName == "/infile") {
            infile = argv[i + 1];
        } else if (argName == "/outfile") {
            outfile = argv[i + 1];
        } else {
            std::cerr << "Unknown argument: " << argName << std::endl;
            return 1;
        }
    }

	try
	{


		PWServer server(infile, outfile);
		server.Start();
	}
	catch (const PWException& exp)
	{
		std::cout << exp.what();
		return -1;
	}

    return 0;
}
