#pragma once

#ifdef __cplusplus

extern "C" {

    #endif

    /* Libraries */

    #include <Uefi.h>
    #include <Library/IoLib.h>
    #include <Library/UefiLib.h>
    #include <Library/UefiDriverEntryPoint.h>
    #include <Library/UefiBootServicesTableLib.h>

    #ifdef __cplusplus

}

#endif

/* Std port */

#include "Std.h"

/* Reverse engineered HECI_PROTOCOL_GUID */

#define HECI_PROTOCOL_GUID {0x3c7bc880, 0x41f8, 0x4869, {0xae, 0xfc, 0x87, 0x0a, 0x3e, 0xd2, 0x82, 0x99}} // FPT.efi locates the HECI_PROTOCOL in memory

EFI_GUID gHeciProtocolGuid = HECI_PROTOCOL_GUID;

/* Stuff from the HECI source code (thanks to SweetKitten <3) */

/* ME mode */

#define ME_MODE_NORMAL 0x00
#define ME_MODE_DEBUG 0x02
#define ME_MODE_TEMP_DISABLED 0x03
#define ME_MODE_RECOVER 0x04
#define ME_MODE_FAILED 0x06

/* ME status */

#define ME_READY 0x00
#define ME_INITIALIZING 0x01
#define ME_IN_RECOVERY_MODE 0x02
#define ME_DISABLE_WAIT 0x06
#define ME_TRANSITION 0x07
#define ME_NOT_READY 0x0F
#define ME_FW_INIT_COMPLETE 0x80
#define ME_FW_BOOT_OPTIONS_PRESENT 0x100
#define ME_FW_UPDATES_IN_PROGRESS 0x200

/* HECI_PROTOCOL specifications from the leaked source code */

typedef struct _HECI_PROTOCOL HECI_PROTOCOL;

typedef EFI_STATUS (EFIAPI *HECI_SENDWACK) (IN OUT UINT32 *Message, IN OUT UINT32 Length, IN OUT UINT32 *RecLength, IN UINT8 HostAddress, IN UINT8 MEAddress);
typedef EFI_STATUS (EFIAPI *HECI_READ_MESSAGE) (IN UINT32 Blocking, IN UINT32 *MessageBody, IN OUT UINT32 *Length);
typedef EFI_STATUS (EFIAPI *HECI_SEND_MESSAGE) (IN UINT32 *Message, IN UINT32 Length, IN UINT8 HostAddress, IN UINT8 MEAddress);
typedef EFI_STATUS (EFIAPI *HECI_RESET) (VOID);
typedef EFI_STATUS (EFIAPI *HECI_INIT) (VOID);
typedef EFI_STATUS (EFIAPI *HECI_REINIT) (VOID);
typedef EFI_STATUS (EFIAPI *HECI_RESET_WAIT) (IN UINT32 Delay);
typedef EFI_STATUS (EFIAPI *HECI_GET_ME_STATUS) (OUT UINT32 *Status);
typedef EFI_STATUS (EFIAPI *HECI_GET_ME_MODE) (OUT UINT32 *Mode);

struct _HECI_PROTOCOL {

    HECI_SENDWACK SendwACK;
    HECI_READ_MESSAGE ReadMsg;
    HECI_SEND_MESSAGE SendMsg;
    HECI_RESET ResetHeci;
    HECI_INIT InitHeci;
    HECI_RESET_WAIT MeResetWait;
    HECI_REINIT ReInitHeci;
    HECI_GET_ME_STATUS GetMeStatus;
    HECI_GET_ME_MODE GetMeMode;

};

/* Stuff for my own code */

double gVersion = 1.0;

extern HECI_PROTOCOL *gHeci;

EFI_STATUS EFIAPI SetColor(IN UINTN Foreground, IN UINTN Background);

EFI_STATUS EFIAPI PrintMenu();

EFI_STATUS EFIAPI ClearScreen();