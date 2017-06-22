#include "NistDefinition.h"

#include <cassert>
#include <vector>
#include <istream>
#include <sstream>
#include <algorithm>
#include <iostream>

std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

std::string removeLeadingWhitespace(std::string str) {

    while(str.length()>0 && str[0] == ' ')
        str = str.substr(1);

    return str;
}

std::string removeTrailingWhitespace(std::string str) {

    while(str.length()>0 && str[str.length()-1] == ' ')
        str = str.substr(0,str.length()-1);

    return str;
}

using UnitMap = std::vector<std::pair<std::string,std::string>>;

bool hasNoPrefixCollisions(UnitMap const& map) {
    if (map.size() <= 1)
        return true;

    const auto forelast = --map.end();
    auto it = map.begin();
    for (; it != forelast; ++it)
        if (std::find_if(it + 1, map.end(), [it](std::pair<std::string, std::string> const& pair) {
                if (pair.first.find(it->first) != std::string::npos) {
                    return true;
                }
                return false;
            }) != map.end()) {
            return true;
        }

    return false;
}

std::vector<std::string> splitByWhitespace(std::string str) {

    std::istringstream iss(str);
    std::vector<std::string> r;
    do
    {
        std::string sub;
        iss >> sub;
        if (sub.length()!=0) r.push_back(sub);
    } while (iss);

    return r;
}



NistDefinition::NistDefinition(const std::string &rawLine)
{
    const int qstart = 0;
    const int vstart = 60;
    const int cstart = 85;
    const int ustart = 110;

    parseQuantity(    rawLine.substr(qstart,vstart-qstart));
    parseValue(       rawLine.substr(vstart,cstart-vstart));
    parseUncertaintiy(rawLine.substr(cstart,ustart-cstart));
    parseUnit(        rawLine.substr(ustart));
}



void NistDefinition::toCppStatement(std::ostream& s, bool uncertainty_) const
{
    s << "constexpr auto ";
    s.width(55);
    s << quantity;
    s <<  " = ";
    s.width(20);
    s << (uncertainty_ ? uncertainty : value);
    s << "_number";
    s << unitSep(uncertainty_);
    s << cppUnit(uncertainty_);
    s << ";\n";
}


bool NistDefinition::uses(const NistDefinition &other) const
{
    return unit.find(other.quantity)!=std::string::npos;
}

void NistDefinition::parseQuantity(std::string v)
{
    v = removeLeadingWhitespace(v);
    v = removeTrailingWhitespace(v);

    const std::vector<std::string> toBeReplaced {" ","{","}",".",",","(",")","-"};

    for(auto const& t:toBeReplaced)
        v = replaceAll(v,t,"_");

    v = replaceAll(v,"/","_per_");

    v = replaceAll(v,"__","_");

    assert(v.length()>1);

    if (v.back()=='_') v.pop_back();
    if (v.front()=='_') v = std::string("c") + v; //pervent '_X...' where X is a captial letter

    quantity = v;

}

void NistDefinition::parseValue(std::string v)
{
    v = removeLeadingWhitespace(v);
    v = removeTrailingWhitespace(v);

    v = replaceAll(v," ","");
    v = replaceAll(v,"...","");

    assert(v.length()>0);

    assert(isDouble(v));

    if (v.find('.')==std::string::npos && v.find('e')==std::string::npos && v.find('E')==std::string::npos ) v.append(".0");

    value = v;
}

void NistDefinition::parseUncertaintiy(std::string v)
{
    v = removeLeadingWhitespace(v);
    v = removeTrailingWhitespace(v);

    v = replaceAll(v," ","");
    v = replaceAll(v,"...","");

    if (v=="(exact)") v = "0.0";
    uncertainty = v;
}

void NistDefinition::parseUnit(std::string v)
{
    v = removeLeadingWhitespace(v);
    v = removeTrailingWhitespace(v);

    auto s = splitByWhitespace(v);

    for(auto const& u:s)
        addUnit(u);
}

const char *NistDefinition::unitSep(bool uncertainty_) const
{
    if (unit.length()<=0) return "";
    if (uncertainty_) return " * ";

    const bool hasOperator = unit.substr(0,2)==" /";

    return hasOperator ? "" : " * ";
}

std::string NistDefinition::cppUnit(bool ofUncertainty) const
{
    if (unit.length()<=0) return "";
    if (ofUncertainty) return std::string("decltype(physicalConstant::") + quantity + ")::classtype{1}";
    return unit;
}

void NistDefinition::addUnit(std::string factor)
{

    if (factor.length()==0) return;

    if (factor=="(GeV/c^2)^-2") {
        addUnit("c^4");
        addUnit("GeV^-2");
        return;
    }

    if (factor=="MeV/c") {
        addUnit("MeV");
        addUnit("c^-1");
        return;
    }

    if (factor=="C_90") { //there shouldnt be any brackets
        addUnit("C");
        addUnit("mol^-1");
        return;
    }


    auto expPos = factor.find("^");
    const std::string factorUnit = factor.substr(0,expPos); //"mol"
    const std::string factorExponent = expPos==std::string::npos?std::string() : factor.substr(expPos+1); //"^-2"

    UnitMap const& replaceMap{ //correct order will be checked later

        {"MeV","mega(electron_volt)"},
        {"GeV","giga(electron_volt)"},
        {"ohm","ohm{1}"},
        {"mol","mole{1}"},
        {"MHz","mega(hertz{1})"},
        {"E_h","hartree_electron_volt_relationship"},
        {"eV","electron_volt"},
        {"kg","kilogram{1}"},
        {"Wb","weber{1}"},
        {"fm","femto(metre{1})"},
        {"Pa","pascal{1}"},
        {"Hz","hertz{1}"},
        {"sr","steradian{1}"},
        {"u","unified_atomic_mass_unit"},
        {"J","joule{1}"},
        {"m","metre{1}"},
        {"K","kelvin{1}"},
        {"C","coulomb{1}"},
        {"s","second{1}"},
        {"A","ampere{1}"},
        {"V","volt{1}"},
        {"N","newton{1}"},
        {"T","tesla{1}"},
        {"F","farad{1}"},
        {"S","siemens{1}"},
        {"W","watt{1}"},
        {"c","speed_of_light_in_vacuum"}
    };

    assert(hasNoPrefixCollisions(replaceMap)==false);


    for(auto const& replaceRule:replaceMap)
        if (replaceRule.first==factorUnit) {
            if (unit.length() > 0 ) unit += " * ";
            unit += addExponent(replaceRule.second ,factorExponent);
            unit = replaceAll(unit, "*  /", "/");
            return;
        }

    assert(false); //unknown unit


}

std::string NistDefinition::addExponent(std::string const& u, std::string exponent)
{
   // u=="mole{1}"
   // exponent=="-3"

    if (exponent.length()<=0) return u;

    const bool inv = exponent[0]=='-';
    const std::string invPrefix = inv ? " / " : "";

    if (inv) {
        exponent = exponent.substr(1);
    }

    assert(exponent.length()==1);

    if (exponent[0]=='1') return invPrefix + u;
    if (exponent[0]=='2') return invPrefix + std::string("square( ") + u + " )";
    if (exponent[0]=='3') return invPrefix + std::string("cube( ") + u + " )";
    return invPrefix + std::string("pow<std::ratio<") + exponent + ">>( " + u + " )";

}

bool NistDefinition::isDouble(std::string v)
{
    std::istringstream s{v.c_str()};
    double d;
    s >> d;
    return s.good() || s.eof();
}
