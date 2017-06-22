#ifndef PYSDEFINITION_H
#define PYSDEFINITION_H

#include <string>
#include <ostream>

class NistDefinition
{
public:
    NistDefinition(std::string const& rawLine);

    void toCppStatement(std::ostream& s, bool uncertainty_ = false) const;
    bool uses(NistDefinition const& other) const;

private:

   void parseQuantity(std::string v);
   void parseValue(std::string v);
   void parseUncertaintiy(std::string v);
   void parseUnit(std::string v);

   const char* unitSep(bool uncertainty_)const;
   std::string cppUnit(bool uncertainty_)const;

   void addUnit(std::string v);
   static std::string addExponent(std::string const& u, std::string exponent);

   static bool isDouble(std::string v);

   std::string quantity;
   std::string value;
   std::string uncertainty;
   std::string unit;

};

#endif // PYSDEFINITION_H
