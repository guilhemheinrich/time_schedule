#pragma once

#include <vector>
#include <string>

using ul = unsigned long;

inline std::vector<ul> findAll(std::string in_sInputString, std::string in_sSplitter)
{
	std::vector<ul> out_vVectorIndexOfMatches;
	size_t stPositionOfMatch = in_sInputString.find(in_sSplitter, 0);;

	while (stPositionOfMatch != std::string::npos)
	{
		out_vVectorIndexOfMatches.push_back((ul)stPositionOfMatch);
		stPositionOfMatch = in_sInputString.find(in_sSplitter, stPositionOfMatch + in_sSplitter.size());
	}

	return out_vVectorIndexOfMatches;
}

inline std::vector<std::string> splitOver(std::string in_sInputString, std::string in_sSplitter)
{
	std::vector<std::string> out_vVectorOfSplittedContent;
	std::vector<ul> vIndexOfMatches = findAll(in_sInputString, in_sSplitter);


	if (vIndexOfMatches.size() == 0)
	{
		out_vVectorOfSplittedContent.push_back(in_sInputString);
		return out_vVectorOfSplittedContent;
	}
	out_vVectorOfSplittedContent.push_back(in_sInputString.substr(0, vIndexOfMatches[0]));

	for (ul indexOfMatch = 0; indexOfMatch < vIndexOfMatches.size() - 1 && vIndexOfMatches.size() > 1; indexOfMatch++)
	{
		out_vVectorOfSplittedContent.push_back(in_sInputString.substr(vIndexOfMatches[indexOfMatch] + 1, vIndexOfMatches[indexOfMatch + 1] - vIndexOfMatches[indexOfMatch] - 1));
	}
	out_vVectorOfSplittedContent.push_back(in_sInputString.substr(vIndexOfMatches[vIndexOfMatches.size() - 1] + 1));

	return out_vVectorOfSplittedContent;
}
