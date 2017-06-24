#include "NistConstantsGenerator.h"
#include "nistConstantsCout.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <cstdio>

NistConstantsGenerator::NistConstantsGenerator()
{
    //unit::physicalConstant::printAllNistConstants();

    const std::string cdir = "../devel/tools/pysConstsantsGeneration";
    const std::string inFile = cdir + "/allascii.txt";
    const std::string outFile = cdir + "/generated/physicalConstants.h";

    std::cout<<"generating physical constants from " << inFile << "\n";

    auto raw_lines = readTxt(inFile);

    std::string httpSource;
    auto raw_lines_no_hdr = removeHeader(raw_lines,httpSource);

    auto defintions = toDefintions(raw_lines_no_hdr);

    writeCpp(outFile, httpSource, defintions);
}

NistConstantsGenerator::RawLines NistConstantsGenerator::readTxt(const std::string &file)
{
    RawLines lines;
    std::string line;

    std::ifstream myfile(file);
    if (myfile.is_open() == false)
        assert(false);

    while (std::getline(myfile, line)) lines.push_back(line);

    myfile.close();

    return lines;
}

NistConstantsGenerator::RawLines NistConstantsGenerator::removeHeader(const NistConstantsGenerator::RawLines &linesWithHeader, std::string& httpSource)
{
    const std::string headerSep("-----------------");

    std::string headline;

    auto it = linesWithHeader.begin();

    for(;it!=linesWithHeader.end();++it) {
        if (it->find("http://")!=std::string::npos) httpSource = it->substr(it->find("http://"));
        if (it->find("Constants")!=std::string::npos) headline = it->substr(it->find("Fundamental"));
        if (it->find(headerSep)!=std::string::npos) break;
    }

    assert(headline=="Fundamental Physical Constants --- Complete Listing");
    assert(httpSource.length()>0);

    assert(it!=linesWithHeader.end());

    ++it; //advance to the line after the separator

    return RawLines{it,linesWithHeader.end()};
}

NistConstantsGenerator::PysDefinitions NistConstantsGenerator::toDefintions(const NistConstantsGenerator::RawLines &rawDefinitions)
{
    PysDefinitions d;
    for(auto const & s:rawDefinitions)
        d.push_back(NistDefinition{s});
    return d;
}

void NistConstantsGenerator::writeCpp(std::string const& outfile, std::string const& httpSource, const NistConstantsGenerator::PysDefinitions &defintions)
{
    std::ofstream myfile(outfile);
    if (myfile.is_open() == false)
        assert(false);

    toCppCode(myfile,httpSource, defintions);
    //toCppCode(std::cout,httpSource, defintions);
}

void NistConstantsGenerator::toCppCode(std::ostream &s, std::string const& httpSource, const NistConstantsGenerator::PysDefinitions &defintions)
{
    const bool uncertainty = true;

    toCppCodeConstantsPrefix(s, httpSource);
    forEachUnused(std::list<NistDefinition>{defintions.begin(),defintions.end()}, [&s](NistDefinition const& d){ d.toCppStatement(s,!uncertainty);});

    toCppCodeUncertaintiesPrefix(s);
    forEachUnused(std::list<NistDefinition>{defintions.begin(),defintions.end()}, [&s](NistDefinition const& d){ d.toCppStatement(s,uncertainty);});
    toCppCodeUncertaintiesSuffix(s);

    toCppCodeConstantsSuffix(s);
}


void NistConstantsGenerator::toCppCodeConstantsPrefix(std::ostream &s, std::string const& httpSource)
{
    s<<"#pragma once\n";
    s<<"\n";
    s<<"/**********************generated from " << httpSource << "**********************/\n";
    s<<"\n";
    s<<"#include <src/quantity/quantityDefinitionsSI.h>\n";
    s<<"//#include \"units.h\"\n";
    s<<"\n";
    s<<"\n";
    s<<"namespace unit {\n";
    s<<"namespace physicalConstant{\n";
    s<<"\n";
    s<<"using namespace literals;\n";
    s << "\n";
}


void NistConstantsGenerator::toCppCodeConstantsSuffix(std::ostream &s)
{
    s << "\n";
    s << "\n";
    s<<"}// namespace physicalConstant\n";
    s<<"}// namespace unit\n";
    s << "\n";
}

void NistConstantsGenerator::toCppCodeUncertaintiesPrefix(std::ostream &s)
{
    s << "\n";
    s << "\n";
    s<<"namespace uncertaintiy{\n";
    s << "\n";
}


void NistConstantsGenerator::toCppCodeUncertaintiesSuffix(std::ostream &s)
{
    s << "\n";
    s << "\n";
    s << "}// namespace uncertaintiy\n";
}

std::list<NistDefinition>::const_iterator NistConstantsGenerator::findUnused(const std::list<NistDefinition> &defintions)
{
    for(auto candiate = defintions.begin(); candiate!=defintions.end(); ++candiate)
    {
        const bool candidateUsesOthers =
            std::find_if(defintions.begin(), defintions.end(),
                         [candiate](NistDefinition const& other) { return candiate->uses(other); }) != defintions.end();

        if (candidateUsesOthers==false) return candiate;
    }
    return defintions.end();
}


void NistConstantsGenerator::forEachUnused(std::list<NistDefinition> defintions, std::function<void(NistDefinition const&)> f)
{
    while(defintions.empty()==false){
        auto unused = findUnused(defintions);
        assert(unused!=defintions.end());
        f(*unused);
        defintions.erase(unused);
    }
}


