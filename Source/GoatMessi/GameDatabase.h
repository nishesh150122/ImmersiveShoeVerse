#pragma once

#include "CoreMinimal.h"
#include "SQLiteCore/Public/IncludeSQLite.h"
#include "GameDatabase.generated.h"

UCLASS()
class UGameDatabase : public UObject
{
	GENERATED_BODY()

public:
	// Create a new user account with the given username, password and email
	UFUNCTION(BlueprintCallable, Category = "Database")
	static bool CreateUserAccount(const FString& Username, const FString& Password, const FString& Email, const FString& ConfirmPassword);

	UFUNCTION(BlueprintCallable, Category = "Database")
	static bool TestUserLogin(const FString& Username, const FString& Password);

	UFUNCTION(BlueprintCallable, Category = "Database")
	static bool AddProduct(const FString& ProductName, const int32 ProductPrice, const FString& Model);

private:
	static sqlite3* Database;
};
