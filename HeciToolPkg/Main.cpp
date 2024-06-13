#include "HeciTool.h"

HECI_PROTOCOL *gHeci = NULL;

EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable) {
    
    EFI_STATUS Status = gBS->LocateProtocol(&gHeciProtocolGuid, NULL, reinterpret_cast<VOID **>(&gHeci));

    if (EFI_ERROR(Status)) {

        SetColor(EFI_RED, EFI_BACKGROUND_BLACK);

        std::cout << "Failed to retrieve the HECI_PROTOCOL from the memory. Status: " << std::to_string(Status) << std::endl;

        SetColor(EFI_WHITE, EFI_BACKGROUND_BLACK);

        return Status;
    }

    Status = PrintMenu();

    if (EFI_ERROR(Status) && Status != EFI_ABORTED) {

        SetColor(EFI_RED, EFI_BACKGROUND_BLACK);

        std::cout << "Failed to process the command. Status: " << std::to_string(Status) << std::endl;

        SetColor(EFI_WHITE, EFI_BACKGROUND_BLACK); 

    }

    if (Status == EFI_ABORTED) {

        ClearScreen();

    }

    return Status;

}