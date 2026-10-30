#pragma once
// Source - https://stackoverflow.com/a/36851059
// Posted by MatrixManAtYrService
// Retrieved 2026-10-30, License - CC BY-SA 3.0
#include <iostream>
class NotImplemented : public std::logic_error
{
public:
    NotImplemented() : std::logic_error("Function not yet implemented") {};
};
