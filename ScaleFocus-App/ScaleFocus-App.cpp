#include <nanodbc.h>
#include <iostream>
#include <exception>
#include <string>

int main() try
{
    auto const connstr = NANODBC_TEXT("Driver={ODBC Driver 17 for SQL Server};Server=(localdb)\\MSSQLLocalDB;Database=master;Trusted_Connection=yes;");
    nanodbc::connection conn(connstr);
    //nanodbc::execute(conn, NANODBC_TEXT("create table t (i int)"));
    //nanodbc::execute(conn, NANODBC_TEXT("insert into t (1)"));

    auto result = nanodbc::execute(conn, NANODBC_TEXT("SELECT 1 as One, N'Hello!'"));
    while (result.next())
    {
        auto i = result.get<int>("One", -1);
        auto s = result.get<nanodbc::string>(1, "");
        std::cout << i << ", " << s << std::endl;
    }
    return EXIT_SUCCESS;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}