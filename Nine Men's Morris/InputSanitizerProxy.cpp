#include "InputSanitizerProxy.h"

const string InputSanitizerProxy::SanitizeInput(const string in) const
{
	string res;
	for (size_t i = 0; i < in.length(); i++)
	{
		char c = in[i];
		if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			res += c;
		}
	}
	return res;
}

InputSanitizerProxy::InputSanitizerProxy(const ConsoleInputManager & iManager) : iMgr(iManager)
{
}

const string InputSanitizerProxy::GetSanitizedBoardInput() const
{
	const string input = iMgr.GetPosition();
	return SanitizeInput(input);
}

const string InputSanitizerProxy::GetPosition() const
{
	return GetSanitizedBoardInput();
}


