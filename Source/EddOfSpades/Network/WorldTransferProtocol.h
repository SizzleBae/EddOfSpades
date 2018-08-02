// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WorldTransferProtocol.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWorldReceived);

/**
 * 
 */
UCLASS()
class EDDOFSPADES_API UWorldTransferProtocol : public UObject, public FRunnable
{
	GENERATED_BODY()
	
private:
	class AEddOfSpadesGameState* GameState;

	class UServerTCP* ServerTCP;
	class UClientTCP* ClientTCP;

	class AEddOfSpadesPlayerController* TargetPlayer;
	class AEddOfSpadesHUD* HUD;

	bool bIsReceiving;
	bool bStopping;

	int32 ChunksHandled;

	FRunnableThread* TransferThread;

public:
	UPROPERTY(BlueprintAssignable)
	FOnWorldReceived OnWorldReceived;
	


public:
	~UWorldTransferProtocol();

	void SendWorldToClient(class UServerTCP* ServerTCP, AEddOfSpadesGameState* GameState, class AEddOfSpadesPlayerController* TargetPlayer);
	void ReceiveWorldFromServer(class UClientTCP* ClientTCP, AEddOfSpadesGameState* GameState, class AEddOfSpadesPlayerController* ClientController);

	virtual uint32 Run() override;

private:
	void StartTransfering();

	int32 ReadInteger(uint8* Data, int32 Offset);
	void WriteInteger(uint8* Data, int32 Integer, int32 Offset);

};