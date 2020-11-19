#include "ConsoleInputManager.h"
#include <iostream>

using namespace std;

const string ConsoleInputManager::GetPosition() const
{
	std::string in;
	cin >> in;
	return in;
}