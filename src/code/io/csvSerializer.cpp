#include "csvSerializer.hpp"

bool CSVSerializer::openReader(string path, bool skipHeader, char separator)
{
    if(this->file.is_open())
    {
        this->file.close();
    }
    this->file.open(path, ios_base::in);
    bool result = this->file.is_open();
    if(result && skipHeader)
    {
        string line;
        getline(this->file, line);
    }
    this->separator = separator;
    this->is_read = true;
    return result;
}

bool CSVSerializer::openWriter(string path, bool append, char separator)
{
    if(this->file.is_open())
    {
        this->file.close();
    }
    this->file.open(path, append? (ios_base::out | ios_base::app): ios_base::out);
    bool result = this->file.is_open();
    this->separator = separator;
    this->is_read = false;
    return result;
}

bool CSVSerializer::canWrite()
{
    if(this->is_read || !this->file.good())
    {
        PLOGD << "Écriture impossible due à l'état du fichier";
        return false;
    }
    return true;
}

bool CSVSerializer::canRead()
{
    if(!this->is_read || !this->file.good())
    {
        PLOGD << "Lecture impossible due à l'état du fichier";
        return false;
    }
    return true;
}

bool CSVSerializer::writeHeader(const Serializable& s)
{
    if(this->canWrite())
    {
        vector<string> properties= s.getProperties();
        int i=0;
        int last = properties.size()-1;
        for(string p: properties)
        {
            this->file << p;
            if(i++<last)
            {
                this->file << this->separator;
            }
        }
        this->file << endl;
        return true;
    }
    return false;
}

bool CSVSerializer::write(const Serializable& s)
{
     if(this->canWrite())
    {
        ExchangeItem e = s.to_exchangeItem();
        vector<string> values = e.getValues();
        int i=0;
        int last = values.size()-1;
        for(string p: values)
        {
            this->file << p;
            if(i++<last)
            {
                this->file << this->separator;
            }
        }
        this->file << endl;
        return true;
    }
    return false;
}

bool CSVSerializer::read(Serializable& s)
{
    bool result = false;
    if(canRead())
    {
        vector<string> row;
        string line;
        string word;
        vector<string> properties = s.getProperties();
        ExchangeItem e = s.to_exchangeItem();
        while(getline(this->file, line))
        {
            row.clear();
            stringstream str(line);
            while(getline(str, word, this->separator))
            {
                row.push_back(word);
            }
            if(row.size()!=properties.size())
            {
                continue;;
            }
            handle_carriage_return(row);
            int i=0;
            for(string p: properties)
            {
                e[p] = row[i++];
            }
            s.from_exchangeItem(e);
            result = true;
        }
        if(!result)
        {
            this->file.close();
        }
    }
    return result;
}

bool CSVSerializer::close()
{
    this->file.close();
    return !this->file.is_open();
}

void handle_carriage_return(vector<string>& row)
{
    string last_w = row[row.size()-1];
    if (!last_w.empty() && last_w[last_w.size() - 1] == '\r')
    {
       row[row.size()-1] = last_w.erase(last_w.size() - 1);
    }
}