#include "HeciTool.h"

EFI_STATUS EFIAPI SetColor(IN UINTN Foreground, IN UINTN Background) {

    return gST->ConOut->SetAttribute(gST->ConOut, Foreground | Background);

}

EFI_STATUS EFIAPI ClearScreen() {

    return gST->ConOut->Reset(gST->ConOut, TRUE);

}

EFI_STATUS EFIAPI MeStatus() {

    ClearScreen();

    std::cout << "HECI Tool " << gVersion << " by Shmurkio" << std::endl << std::endl;

    UINT32 MeStatus = 0;
    
    EFI_STATUS Status = gHeci->GetMeStatus(&MeStatus);

    if (EFI_ERROR(Status)) {

        return Status;

    }

    std::cout << "ME Status: ";

    switch (MeStatus) {

        case ME_READY:
            std::cout << "ME_READY (0x";
            break;
        
        case ME_INITIALIZING:
            std::cout << "ME_INITIALIZING (0x";
            break;

        case ME_IN_RECOVERY_MODE:
            std::cout << "ME_IN_RECOVERY_MODE (0x";
            break;

        case ME_DISABLE_WAIT:
            std::cout << "ME_DISABLE_WAIT (0x";
            break;
        
        case ME_TRANSITION:
            std::cout << "ME_TRANSITION (0x";
            break;
        
        case ME_NOT_READY:
            std::cout << "ME_NOT_READY (0x";
            break;
        
        case ME_FW_INIT_COMPLETE:
            std::cout << "ME_FW_INIT_COMPLETE (0x";
            break;

        case ME_FW_BOOT_OPTIONS_PRESENT:
            std::cout << "ME_FW_BOOT_OPTIONS_PRESENT (0x";
            break;
        
        case ME_FW_UPDATES_IN_PROGRESS:
            std::cout << "ME_FW_UPDATES_IN_PROGRESS (0x";
            break;
        
        default:
            std::cout << "ME_STATUS_UNKNOWN (0x";
            break;

    }

    std::cout << std::hex << MeStatus << std::dec << ")" << std::endl;

    return Status;

}

EFI_STATUS EFIAPI MeMode() {

    ClearScreen();

    std::cout << "HECI Tool " << gVersion << " by Shmurkio" << std::endl << std::endl;

    UINT32 MeMode = 0;

    EFI_STATUS Status = gHeci->GetMeMode(&MeMode);

    if (EFI_ERROR(Status)) {

        return Status;

    }

    std::cout << "ME Mode: ";

    switch (MeMode) {

        case ME_MODE_NORMAL:
            std::cout << "ME_MODE_NORMAL (0x";
            break;
        
        case ME_MODE_DEBUG:
            std::cout << "ME_MODE_DEBUG (0x";
            break;

        case ME_MODE_TEMP_DISABLED:
            std::cout << "ME_MODE_TEMP_DISABLED (0x";
            break;

        case ME_MODE_RECOVER:
            std::cout << "ME_MODE_RECOVER (0x";
            break;
        
        case ME_MODE_FAILED:
            std::cout << "ME_MODE_FAILED (0x";
            break;
        
        default:
            std::cout << "ME_MODE_UNKNOWN (0x";
            break;

    }

    std::cout << std::hex << MeMode << std::dec << ")" << std::endl;

    return Status;

}

EFI_STATUS EFIAPI ResetHeci() {

    ClearScreen();

    std::cout << "HECI Tool " << gVersion << " by Shmurkio" << std::endl << std::endl;

    EFI_STATUS Status = gHeci->ResetHeci();

    if (EFI_ERROR(Status)) {

        return Status;

    }

    std::cout << "Reset HECI: " << std::to_string(Status) << std::endl;

    return Status;

}

EFI_STATUS EFIAPI InitiateHeci() {

    ClearScreen();

    std::cout << "HECI Tool " << gVersion << " by Shmurkio" << std::endl << std::endl;

    EFI_STATUS Status = gHeci->InitHeci();

    if (EFI_ERROR(Status)) {

        return Status;

    }

    std::cout << "Initiate HECI: " << std::to_string(Status) << std::endl;

    return Status;

}

EFI_STATUS EFIAPI ReinitiateHeci() {

    ClearScreen();

    std::cout << "HECI Tool " << gVersion << " by Shmurkio" << std::endl << std::endl;

    EFI_STATUS Status = gHeci->ReInitHeci();

    if (EFI_ERROR(Status)) {

        return Status;

    }

    std::cout << "Reinitiate HECI: " << std::to_string(Status) << std::endl;

    return Status;

}

EFI_STATUS EFIAPI PrintMenu() {

    ClearScreen();

    std::cout << "HECI Tool " << gVersion << " by Shmurkio" << std::endl << std::endl
        << "(1) ME Status" << std::endl
        << "(2) ME Mode" << std::endl
        << "(3) Reset HECI" << std::endl
        << "(4) Initiate HECI" << std::endl
        << "(5) Reinitiate HECI" << std::endl
        << "(6) Exit" << std::endl << std::endl
        << "Enter option: ";
    
    std::string Option;
    std::cin >> Option;

    if (Option.length() != 1) {

        PrintMenu();

    }

    switch (Option.to_int()) {

        case 1:
            return MeStatus();
            break;
        
        case 2:
            return MeMode();
            break;
        
        case 3:
            return ResetHeci();
            break;
        
        case 4:
            return InitiateHeci();
            break;
        
        case 5:
            return ReinitiateHeci();
            break;
        
        case 6:
            return EFI_ABORTED;
            break;
        
        default:
            PrintMenu();
            break;

    }

    return EFI_SUCCESS;

}