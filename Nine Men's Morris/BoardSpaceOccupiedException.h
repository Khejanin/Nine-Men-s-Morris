#pragma once

#include <exception>

class BoardSpaceOccupiedException : public std::exception {
public:

	BoardSpaceOccupiedException(char const* const msg = "This BoardSpace is already occupied by a Piece! Please choose one that's empty (marked with an 'X')!") : exception(msg) {

	}

};