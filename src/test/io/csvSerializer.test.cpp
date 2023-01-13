#include "csvSerializer.test.hpp"

UP_SUITE_BEGIN(csvSerializer);

UP_TEST(connect)
{
    remove(test_csv_file_path.c_str());
    UP_ASSERT(!serializer.openReader(test_csv_file_path, false));
    UP_ASSERT(!serializer.openReader(test_csv_file_path, true));
    UP_ASSERT(serializer.openWriter(test_csv_file_path, false));
    UP_ASSERT(serializer.openWriter(test_csv_file_path, true));
    UP_ASSERT(serializer.openReader(test_csv_file_path, false));
    UP_ASSERT(serializer.openReader(test_csv_file_path, true));
    UP_ASSERT(serializer.close());
    remove(test_csv_file_path.c_str());
}

UP_TEST(writeHeader)
{
    UP_ASSERT(serializer.openWriter(test_csv_file_path, false));
    UP_ASSERT(serializer.writeHeader(MockSerializable()));
    UP_ASSERT(serializer.close());
    ifstream file(test_csv_file_path);
    string line;
    getline(file, line);
    UP_ASSERT_EQUAL(line, "Nom;Prenom");
}

UP_TEST(writeValues)
{
    UP_ASSERT(serializer.openWriter(test_csv_file_path, false));
    UP_ASSERT(serializer.write(MockSerializable("Tiberghien", "Mathias")));
    UP_ASSERT(serializer.close());
    ifstream file(test_csv_file_path);
    string line;
    getline(file, line);
    UP_ASSERT_EQUAL(line, "Tiberghien;Mathias");
    remove(test_csv_file_path.c_str());
}

UP_TEST(readValues)
{
    UP_ASSERT(serializer.openWriter(test_csv_file_path, false));
    UP_ASSERT(serializer.write(MockSerializable("Tiberghien", "Mathias")));
    UP_ASSERT(serializer.close());
    MockSerializable s;
    UP_ASSERT(serializer.openReader(test_csv_file_path, false));
    UP_ASSERT(serializer.read(s));
    UP_ASSERT_EQUAL(s.getNom(), "Tiberghien");
    UP_ASSERT_EQUAL(s.getPrenom(), "Mathias");
}

UP_SUITE_END();

