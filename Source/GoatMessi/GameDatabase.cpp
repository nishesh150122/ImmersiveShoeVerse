#include "GameDatabase.h"
#include <string>
#include "SQLitePreparedStatement.h"

sqlite3* UGameDatabase::Database = nullptr;

bool UGameDatabase::CreateUserAccount(const FString& Username, const FString& Password, const FString& Email, const FString& ConfirmPassword)
{
    // Check if any input field is null
    if (Username.IsEmpty() || Password.IsEmpty() || Email.IsEmpty() || ConfirmPassword.IsEmpty())
    {
        UE_LOG(LogTemp, Error, TEXT("Input fields cannot be null"));
        return false;
    }
    const FRegexPattern EmailRegexPattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    const FString EmailStr = Email.TrimStartAndEnd();
    FRegexMatcher EmailRegexMatcher(EmailRegexPattern, EmailStr);
    if (!EmailRegexMatcher.FindNext())
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid email format"));
        return false;
    }
    // Check if passwords match
    if (Password != ConfirmPassword)
    {
        UE_LOG(LogTemp, Error, TEXT("Passwords do not match"));
        return false;
    }
    else
    {
        // Open the database
        if (!Database)
        {
            int Result = sqlite3_open_v2(TCHAR_TO_UTF8(TEXT("C:/Users/Acer/Desktop/First_project/GoatMessi/Content/Database/Goat.db")), &Database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
            if (Result != SQLITE_OK)
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to open database: %s"), UTF8_TO_TCHAR(sqlite3_errmsg(Database)));
                return false;
            }

            // Create the User table if it does not exist
            const char* CreateTableSql = "CREATE TABLE IF NOT EXISTS User (UserId INTEGER PRIMARY KEY, UserName TEXT NOT NULL UNIQUE, Password TEXT NOT NULL, Email TEXT NOT NULL UNIQUE);";
            Result = sqlite3_exec(Database, CreateTableSql, nullptr, nullptr, nullptr);
            if (Result != SQLITE_OK)
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to create User table: %s"), UTF8_TO_TCHAR(sqlite3_errmsg(Database)));
                return false;
            }
        }

        // Insert the new user account into the User table
        const char* InsertSql = sqlite3_mprintf("INSERT INTO User (UserName, Password, Email) VALUES (%Q, %Q, %Q);", TCHAR_TO_UTF8(*Username), TCHAR_TO_UTF8(*Password), TCHAR_TO_UTF8(*Email));
        int Result = sqlite3_exec(Database, InsertSql, nullptr, nullptr, nullptr);
        if (Result != SQLITE_OK)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to insert new user account: %s"), UTF8_TO_TCHAR(sqlite3_errmsg(Database)));
            return false;
        }

        return true;
    }
}
bool UGameDatabase::TestUserLogin(const FString& Username, const FString& Password)
{
    // Open the database
    if (!Database)
    {
        UE_LOG(LogTemp, Warning, TEXT("Opening database..."));
        int Result = sqlite3_open_v2(TCHAR_TO_UTF8(TEXT("C:/Users/Acer/Desktop/First_project/GoatMessi/Content/Database/Goat.db")), &Database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
        if (Result != SQLITE_OK)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to open database: %s"), UTF8_TO_TCHAR(sqlite3_errmsg(Database)));
            return false;
        }

        // Create the User table if it does not exist
        UE_LOG(LogTemp, Warning, TEXT("Creating User table..."));
        const char* CreateTableSql = "CREATE TABLE IF NOT EXISTS User (UserId INTEGER PRIMARY KEY, UserName TEXT NOT NULL UNIQUE, Password TEXT NOT NULL, Email TEXT NOT NULL UNIQUE);";
        Result = sqlite3_exec(Database, CreateTableSql, nullptr, nullptr, nullptr);
        if (Result != SQLITE_OK)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to create User table: %s"), UTF8_TO_TCHAR(sqlite3_errmsg(Database)));
            return false;
        }
    }
    // Check if the user with the given username and password exists
    const char* SelectSql = sqlite3_mprintf("SELECT UserName FROM User WHERE UserName = %Q AND Password = %Q;", TCHAR_TO_UTF8(*Username), TCHAR_TO_UTF8(*Password));
    int Result = sqlite3_exec(Database, SelectSql, nullptr, nullptr, nullptr);
    if (Result != SQLITE_OK)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to select user account: %s"), UTF8_TO_TCHAR(sqlite3_errmsg(Database)));
        return false;
    }

    // Get the number of rows returned by the SELECT statement
    int NumRows = sqlite3_changes(Database);

    // If a row was returned, the user exists and the login is successful
    if (NumRows > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Login successful for user %s"), *Username);
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid username or password."));
        return false;
    }
}
bool UGameDatabase::AddProduct(const FString& ProductName, const int32 ProductPrice, const FString& Model)
{
        // Open the database
        if (!Database)
        {
            int Result = sqlite3_open_v2(TCHAR_TO_UTF8(TEXT("C:/Users/Acer/Desktop/First_project/GoatMessi/Content/Database/Goat.db")), &Database, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
            if (Result != SQLITE_OK)
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to open database: %s"), UTF8_TO_TCHAR(sqlite3_errmsg(Database)));
                return false;
            }

            // Create the User table if it does not exist
            const char* CreateTableSql = "CREATE TABLE IF NOT EXISTS User (ProductId INTEGER PRIMARY KEY NOTNULL, ProductName TEXT NOT NULL UNIQUE, ProductPrice INTEGER NOT NULL, ProductModel TEXT NOT NULL UNIQUE);";
            Result = sqlite3_exec(Database, CreateTableSql, nullptr, nullptr, nullptr);
            if (Result != SQLITE_OK)
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to create User table: %s"), UTF8_TO_TCHAR(sqlite3_errmsg(Database)));
                return false;
            }
        }

        // Insert the new user account into the User table
        const char* InsertSql = sqlite3_mprintf("INSERT INTO Product (ProductName, ProductPrice, ProductModel) VALUES (%Q, %d, %Q);", TCHAR_TO_UTF8(*ProductName), ProductPrice, TCHAR_TO_UTF8(*Model));
        int Result = sqlite3_exec(Database, InsertSql, nullptr, nullptr, nullptr);
        if (Result != SQLITE_OK)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to insert new product: %s"), UTF8_TO_TCHAR(sqlite3_errmsg(Database)));
            return false;
        }

        return true;
}