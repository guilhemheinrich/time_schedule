#pragma once
#include <string>
#include <map>
using ul = unsigned long;

enum class Subject
{
	EMPTY,
	MATH,
	FRENCH,
	ENGLISH,
	HISTORY,
	GEOGRAPHY,
	PHYSIC,
	NATURAL_SCIENCE,
	SPORT
};

enum class SessionID
{
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURDAY,
	FRIDAY,
	SATURDAY, 
	SUNDAY
};

inline std::string toString(Subject in_Subject)
{
	std::map<Subject, std::string> subjectDictionary;
	subjectDictionary[Subject::EMPTY] = "empty";
	subjectDictionary[Subject::MATH] = "math";
	subjectDictionary[Subject::FRENCH] = "french";
	subjectDictionary[Subject::ENGLISH] = "english";
	subjectDictionary[Subject::HISTORY] = "history";
	subjectDictionary[Subject::GEOGRAPHY] = "geography";
	subjectDictionary[Subject::PHYSIC] = "physic";
	subjectDictionary[Subject::NATURAL_SCIENCE] = "naturalScience";
	subjectDictionary[Subject::SPORT] = "sport";
	return subjectDictionary[in_Subject];
}

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