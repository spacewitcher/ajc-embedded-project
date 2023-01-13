#pragma once
#include <fstream>
#include <iterator>
#include "log.hpp"
#include "serializable.hpp"

class CSVSerializer
{
    public:
        CSVSerializer():separator(';'){};
        bool openReader(string path, bool skipHeader, char separator=';');
        bool openWriter(string path, bool append, char separator=';');
        bool writeHeader(const Serializable& s);
        bool write(const Serializable& s);
        bool read(Serializable& s);
        bool close();
    private:
        bool canWrite();
        bool canRead();
        char separator;
        fstream file;
        bool is_read;
};

void handle_carriage_return(vector<string>& row);