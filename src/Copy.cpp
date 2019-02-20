
#include "Copy.h"

// TODO: Install dot
// TODO: Install graphviz

namespace Opts = boost::program_options;


int main(int argc, char* argv[])
{
    Opts::options_description OptsDescription("Available options");
    OptsDescription.add_options()
        ("help", "Display help menu")
    ;
    
    Opts::variables_map InputMap;
    Opts::store(Opts::parse_command_line(argc, argv, OptsDescription), InputMap);
    Opts::notify(InputMap);

    if (InputMap.count("help"))
    {
        std::cout << OptsDescription << "\n";

        return EXIT_SUCCESS;
    }

    std::cout << "<Testing...>\n";

    return EXIT_SUCCESS;
}
