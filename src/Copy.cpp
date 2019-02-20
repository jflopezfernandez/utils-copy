
#include "Copy.h"

namespace Opts = boost::program_options;


bool VerboseModeEnabled = false;

void VerboseInfo(const std::string_view& str)
{
    if (VerboseModeEnabled)
        std::clog << "[DEBUG]: " << str << "\n";
}

std::string BoolToString(const bool value) noexcept { return (value) ? "True" : "False"; }

struct IStringify
{
    virtual std::string toString() const noexcept = 0;
};

struct IOption : virtual public IStringify
{
    virtual std::string toString() const noexcept = 0;
};

class Option : public IOption
{
protected:
    std::string name;

public:
    Option()
        : name{ "<Untitled Option>" }
    {
        // Default constructor
    }

    Option(const char* name)
        : name{ name }
    {
        // 
    }

    Option(const Option& option)
        : name{ option.name }
    {
        // Copy constructor
    }

    virtual std::string toString() const noexcept { return name; }
};

class BooleanOption : public Option
{
protected:
    bool value;

public:
    BooleanOption()
        : Option{ "" }, value{ false }
    {
        // Default constructor
    }

    BooleanOption(const char* name, bool initialValue)
        : Option{ name }, value{ initialValue }
    {
        // Constructor
        VerboseInfo("Boolean option constructor: " + std::string{ name } + " (" + BoolToString(initialValue) + ")");
    }

    BooleanOption(const BooleanOption& option)
        : Option{ option }, value{ option.value }
    {
        // Copy constructor
    }
    
    bool operator!  () noexcept { return (this->value != this->value); }

    virtual std::string toString() const noexcept override
    {
        return name + ": " + BoolToString(value);
    }

    std::string operator() () const noexcept { return this->toString(); }

    friend std::ostream& operator<<(std::ostream& outputStream, const BooleanOption& opt)
    {
        return outputStream << opt.toString();
    }
};

class Configuration
{
public:
    BooleanOption DebugModeEnabled;
    BooleanOption VerboseModeEnabled;

    std::vector<Option> Options;

public:
    Configuration()
        :   DebugModeEnabled{ "Debug Mode Enabled", false },
            VerboseModeEnabled{ "Verbose Mode Enabled", false }
    {
        // Default constructor
        VerboseInfo(DebugModeEnabled());
        VerboseInfo(VerboseModeEnabled());

        this->AddOptions();
    }

    Configuration& AddOption(Option& option)
    {
        VerboseInfo("1: Size of vector: " + std::to_string(Options.size()));
        Options.emplace_back(option);
        VerboseInfo("2: Size of vector: " + std::to_string(Options.size()));
        
        return *this;
    }

    void Print()
    {
        std::cout << "\n\nCurrent Configuration: \n";

        for (const auto& opt : Options)
        {
            std::cout << " \t - " << opt.toString() << "\n";
        }
    }

private:
    Configuration& AddOptions()
    {
        this->AddOption(DebugModeEnabled);
        this->AddOption(VerboseModeEnabled);

        return *this;
    }
};

int main(int argc, char* argv[])
{
    Opts::options_description OptsDescription("Available options");
    OptsDescription.add_options()
        ("help,h", "Display help menu")
        ("version,v", "Display program version")
        ("verbose", "Display copious debugging information")
        ("input", Opts::value<std::string>(), "Input file or directory name")
    ;
    
    Opts::variables_map InputMap;
    Opts::store(Opts::parse_command_line(argc, argv, OptsDescription), InputMap);
    Opts::notify(InputMap);

    if (InputMap.count("help"))
    {
        std::cout << OptsDescription << "\n";

        return EXIT_SUCCESS;
    }

    if (InputMap.count("version"))
    {
        std::cout << "\n\n";
        std::cout << "<Program Name>\n";
        std::cout << "<Program Author>\n";
        std::cout << "<Program Version>\n";
        std::cout << "\n\n";

        return EXIT_SUCCESS;
    }

    if (InputMap.count("verbose"))
    {
        VerboseModeEnabled = true;

        VerboseInfo("Verbose output mode enabled.");
    }

    if (InputMap.count("input"))
    {
        // ERROR: If input is defined but no actual file is specified, the
        // program aborts with a call to std::terminate().
        VerboseInfo("Input file specified.");
    }

    Configuration configuration;
    //std::cout << configuration.VerboseModeEnabled() << "\n";
    configuration.Print();

    return EXIT_SUCCESS;
}
