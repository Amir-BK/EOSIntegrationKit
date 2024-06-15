﻿// Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSubsystemEIK/SdkFunctions/EIK_SharedFunctionFile.h"
THIRD_PARTY_INCLUDES_START
#include "eos_auth.h"
THIRD_PARTY_INCLUDES_END
#include "Subsystems/GameInstanceSubsystem.h"
#include "EIK_AuthSubsystem.generated.h"

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FEIK_Auth_OnLoginStatusChangedCallback, FEIK_EpicAccountId, LocalUserId, const TEnumAsByte<EIK_ELoginStatus>&, PrevStatus, const TEnumAsByte<EIK_ELoginStatus>&, CurrentStatus);
UCLASS(meta=(DisplayName="Auth Interface"), Category="EOS Integration Kit", DisplayName="Auth Interface")
class ONLINESUBSYSTEMEIK_API UEIK_AuthSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	FEIK_Auth_OnLoginStatusChangedCallback OnLoginStatusChanged;
	/*
	 Register to receive login status updates.
	 *
	 If the returned NotificationId is valid, you must call EOS_Auth_RemoveNotifyLoginStatusChanged when you no longer wish to have your NotificationHandler called.
	 */
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Auth Interface", DisplayName="EOS_Auth_AddNotifyLoginStatusChanged")
	FEIK_NotificationId EIK_Auth_AddNotifyLoginStatusChanged(const FEIK_Auth_OnLoginStatusChangedCallback& Callback);

	//Fetch an ID token for an Epic Account ID. ID tokens are used to securely verify user identities with online services. The most common use case is using an ID token to authenticate the local user by their selected account ID, which is the account ID that should be used to access any game-scoped data for the current application. An ID token for the selected account ID of a locally authenticated user will always be readily available. To retrieve it for the selected account ID, you can use EOS_Auth_CopyIdToken directly after a successful user login.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Auth Interface", DisplayName="EOS_Auth_CopyIdToken")
	TEnumAsByte<EEIK_Result> EIK_Auth_CopyIdToken(const FEIK_EpicAccountId& AccountId, FEIK_Auth_IdToken& OutToken);

	//Fetch a user auth token for an Epic Account ID. A user authentication token allows any code with possession (backend/client) to perform certain actions on behalf of the user. Because of this, for the purposes of user identity verification, the EOS_Auth_CopyIdToken API should be used instead.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Auth Interface", DisplayName="EOS_Auth_CopyUserAuthToken")
	TEnumAsByte<EEIK_Result> EIK_Auth_CopyUserAuthToken(const FEIK_EpicAccountId& LocalUserId, FEIK_Auth_Token& OutToken);

	//Fetch an Epic Account ID that is logged in.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Auth Interface", DisplayName="EOS_Auth_GetLoggedInAccountByIndex")
	FEIK_EpicAccountId EIK_Auth_GetLoggedInAccountByIndex(int32 Index);

	//Fetch the number of accounts that are logged in.
	UFUNCTION(BlueprintCallable, Category = "EOS Integration Kit | SDK Functions | Auth Interface", DisplayName="EOS_Auth_GetLoggedInAccountsCount")
	int32 EIK_Auth_GetLoggedInAccountsCount();

	
};
