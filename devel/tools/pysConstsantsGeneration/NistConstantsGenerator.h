#ifndef PHYCONSTANTSGENERATOR_H
#define PHYCONSTANTSGENERATOR_H

#include "NistDefinition.h"

#include <string>
#include <vector>
#include <list>
#include <functional>


class NistConstantsGenerator
{
public:
    NistConstantsGenerator();

private:


    using RawLines = std::vector<std::string>;

    static RawLines readTxt(std::string const& file);
    static RawLines removeHeader(RawLines const& linesWithHeader, std::string& httpSource);

    using PysDefinitions = std::vector<NistDefinition>;
    static PysDefinitions toDefintions(RawLines const& rawDefinitions);

    static void writeCpp(std::string const& constantsHdr, std::string const& httpSource, PysDefinitions const& defintions);

    static void toCppCode(std::ostream& s, std::string const& httpSource, PysDefinitions const& defintions);

    static void toCppCodeConstantsPrefix(std::ostream& s, std::string const& httpSource);
    static void toCppCodeConstantsSuffix(std::ostream& s);
    static void toCppCodeUncertaintiesPrefix(std::ostream& s);
    static void toCppCodeUncertaintiesSuffix(std::ostream& s);

    static void forEachUnused(std::list<NistDefinition> defintions, std::function<void(NistDefinition const&)> f);

    static std::list<NistDefinition>::const_iterator findUnused(std::list<NistDefinition> const&  defintions);

};

#endif // PHYCONSTANTSGENERATOR_H
