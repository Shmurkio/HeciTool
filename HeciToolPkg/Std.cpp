/*
*
*   Std Wrapper for EDK2 1.4 by Shmurkio
*
*   Include in .inf:
*    [Sources] Std.h & Std.cpp
*   [Protocols] gEfiSimpleTextInputExProtocolGuid
*
*   https://github.com/Shmurkio
*
*/

#include "Std.h"

bool gHexValue = FALSE;

extern "C" int _fltused = 1;

void *operator new[](size_t Size) {
    
    void *Pointer = nullptr;

    gBS->AllocatePool(EfiBootServicesData, Size, &Pointer);

    return Pointer;

}

void operator delete[](void *Pointer) noexcept {
    
    if (Pointer != nullptr) {

        gBS->FreePool(Pointer);

    }

}

int atexit(void (*Function)()) {

    return 0;
    
}

size_t Wcslen(const wchar_t *String) {

    const wchar_t *Pointer = String;

    while (*Pointer != L'\0') {

        Pointer++;

    }

    return Pointer - String;

}

wchar_t* Wcscpy(wchar_t* Destination, const wchar_t* Source) {

    wchar_t* Start = Destination;

    while (*Source != L'\0') {

        *Start++ = *Source++;

    }

    *Start = L'\0';

    return Start;

}

void DoubleToString(double Number, CHAR16 *Buffer, UINTN BufferSize) {
    
    int IntPart = static_cast<int>(Number);

    int FracPart = static_cast<int>((Number - IntPart) * 100);

    UnicodeSPrint(Buffer, BufferSize, reinterpret_cast<CHAR16 *>(L"%d.%d"), IntPart, FracPart);

}

EFI_STATUS EFIAPI GetString(OUT CHAR16 *String) {

    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *ConInEx;

    EFI_STATUS Status = gST->BootServices->HandleProtocol(gST->ConsoleInHandle, &gEfiSimpleTextInputExProtocolGuid, reinterpret_cast<VOID **>(&ConInEx));

    if (EFI_ERROR(Status)) {

        return Status;

    }

    EFI_INPUT_KEY Key;

    EFI_KEY_DATA KeyData;

    UINTN Index = 0;

    while(Index < STD_MAX_STRING_LENGTH - 1) {

        Status = ConInEx->ReadKeyStrokeEx(ConInEx, &KeyData);

        if (Status == EFI_SUCCESS) {

            Key = KeyData.Key;

            if (Key.UnicodeChar == CHAR_CARRIAGE_RETURN) {

                break;

            }
            else if (Key.UnicodeChar == CHAR_BACKSPACE && Index > 0) {

                Print(reinterpret_cast<CHAR16 *>(L"\b \b"));

                Index--;

            }
            else if (Key.UnicodeChar >= L' ' && Key.UnicodeChar <= L'~') {

                Print(reinterpret_cast<CHAR16 *>(L"%c"), Key.UnicodeChar);

                String[Index] = Key.UnicodeChar;

                Index++;

            }

        }

    }

    String[Index] = L'\0';

    return Status;

}

EFI_STATUS EFIAPI GetStringS(OUT CHAR16 *String) {

    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *ConInEx;

    EFI_STATUS Status = gST->BootServices->HandleProtocol(gST->ConsoleInHandle, &gEfiSimpleTextInputExProtocolGuid, reinterpret_cast<VOID **>(&ConInEx));

    if (EFI_ERROR(Status)) {

        return Status;

    }

    EFI_INPUT_KEY Key;

    EFI_KEY_DATA KeyData;

    UINTN Index = 0;

    while(Index < STD_MAX_STRING_LENGTH - 1) {

        Status = ConInEx->ReadKeyStrokeEx(ConInEx, &KeyData);

        if (Status == EFI_SUCCESS) {

            Key = KeyData.Key;

            if (Key.UnicodeChar == CHAR_CARRIAGE_RETURN) {

                break;

            }
            else if (Key.UnicodeChar == CHAR_BACKSPACE && Index > 0) {

                Print(reinterpret_cast<CHAR16 *>(L"\b \b"));

                Index--;

            }
            else if (Key.UnicodeChar >= L' ' && Key.UnicodeChar <= L'~') {

                Print(reinterpret_cast<CHAR16 *>(L"*"));

                String[Index] = Key.UnicodeChar;

                Index++;

            }

        }

    }

    String[Index] = L'\0';

    return Status;

}

EFI_STATUS EFIAPI Pause() {

    EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL *ConInEx;

    EFI_STATUS Status = gST->BootServices->HandleProtocol(gST->ConsoleInHandle, &gEfiSimpleTextInputExProtocolGuid, (VOID **)&ConInEx);

    if (EFI_ERROR(Status)) {

        return Status;

    }

    EFI_KEY_DATA KeyData;

    while(TRUE) {

        Status = ConInEx->ReadKeyStrokeEx(ConInEx, &KeyData);

        if (Status == EFI_SUCCESS) {

            return Status;

        }

    }

}

namespace std {

    /* (1) Data types */

    /* (1.1) std::string */

    string String;

    string::string() : pData(nullptr) {};

    string::string(const string& Other) {

        size_t Length = StrLen(Other.pData);

        pData = new CHAR16[Length + 1];

        StrCpyS(pData, Length + 1, Other.pData);

    }

    string::string(const char *Data) : pData(nullptr) {

        size_t Length = AsciiStrLen(Data);

        pData = new CHAR16[Length + 1];

        for (size_t Index = 0; Index < Length; ++Index) {

            pData[Index] = static_cast<CHAR16>(Data[Index]);

        }

        pData[Length] = L'\0';

    }

    string& string::operator=(const string& Other) {

        if (this != &Other) {

            delete[] pData;

            size_t Length = StrLen(Other.pData);

            pData = new CHAR16[Length + 1];

            StrCpyS(pData, Length + 1, Other.pData);

        }

        return *this;

    }

    string::operator const CHAR16*() const {

        return pData;

    }

    string::~string() {

        delete[] pData;

    }

    /* (1.2) std::wstring */

    wstring Wstring;

    wstring::wstring() : pData(nullptr) {}

    wstring::wstring(const wstring& Other) {

        size_t Length = Wcslen(Other.pData);

        pData = new wchar_t[Length + 1];

        Wcscpy(pData, Other.pData);

    }

    wstring::wstring(const wchar_t *Data) : pData(nullptr) {

        size_t Length = Wcslen(Data);

        pData = new wchar_t[Length + 1];

        Wcscpy(pData, Data);

    }

    wstring& wstring::operator=(const wstring& Other) {

        if (this != &Other) {

            delete[] pData;

            size_t Length = Wcslen(Other.pData);

            pData = new wchar_t[Length + 1];

            Wcscpy(pData, Other.pData);

        }

        return *this;

    }

    wstring::operator const wchar_t*() const {

        return pData;

    }

    wstring::~wstring() {

        delete[] pData;

    }

    /* (1.3) std::endl */

    Endl endl;

    /* (2) Utility Functions */

    /* (2.1) std::to_string */

    string to_string(const wstring& Wstr) {

        size_t Length = Wcslen(Wstr);

        char* Data = new char[Length + 1];

        for (size_t Index = 0; Index < Length; Index++) {

            Data[Index] = static_cast<char>(Wstr[Index]);

        }

        Data[Length] = '\0';

        string Result(Data);

        delete[] Data;

        return Result;

    }

    string to_string(EFI_STATUS Status) {

        switch (Status) {

            case RETURN_SUCCESS:
                return "EFI_SUCCESS";
            case RETURN_LOAD_ERROR:
                return "EFI_LOAD_ERROR";
            case RETURN_INVALID_PARAMETER:
                return "EFI_INVALID_PARAMETER";
            case RETURN_UNSUPPORTED:
                return "EFI_UNSUPPORTED";
            case RETURN_BAD_BUFFER_SIZE:
                return "EFI_BAD_BUFFER_SIZE";
            case RETURN_BUFFER_TOO_SMALL:
                return "EFI_BUFFER_TOO_SMALL";
            case RETURN_NOT_READY:
                return "EFI_NOT_READY";
            case RETURN_DEVICE_ERROR:
                return "EFI_DEVICE_ERROR";
            case RETURN_WRITE_PROTECTED:
                return "EFI_WRITE_PROTECTED";
            case RETURN_OUT_OF_RESOURCES:
                return "EFI_OUT_OF_RESOURCES";
            case RETURN_VOLUME_CORRUPTED:
                return "EFI_VOLUME_CORRUPTED";
            case RETURN_VOLUME_FULL:
                return "EFI_VOLUME_FULL";
            case RETURN_NO_MEDIA:
                return "EFI_NO_MEDIA";
            case RETURN_MEDIA_CHANGED:
                return "EFI_MEDIA_CHANGED";
            case RETURN_NOT_FOUND:
                return "EFI_NOT_FOUND";
            case RETURN_ACCESS_DENIED:
                return "EFI_ACCESS_DENIED";
            case RETURN_NO_RESPONSE:
                return "EFI_NO_RESPONSE";
            case RETURN_NO_MAPPING:
                return "EFI_NO_MAPPING";
            case RETURN_TIMEOUT:
                return "EFI_TIMEOUT";
            case RETURN_NOT_STARTED:
                return "EFI_NOT_STARTED";
            case RETURN_ALREADY_STARTED:
                return "EFI_ALREADY_STARTED";
            case RETURN_ABORTED:
                return "EFI_ABORTED";
            case RETURN_ICMP_ERROR:
                return "EFI_ICMP_ERROR";
            case RETURN_TFTP_ERROR:
                return "EFI_TFTP_ERROR";
            case RETURN_PROTOCOL_ERROR:
                return "EFI_PROTOCOL_ERROR";
            case RETURN_INCOMPATIBLE_VERSION:
                return "EFI_INCOMPATIBLE_VERSION";
            case RETURN_SECURITY_VIOLATION:
                return "EFI_SECURITY_VIOLATION";
            case RETURN_CRC_ERROR:
                return "EFI_CRC_ERROR";
            case RETURN_END_OF_MEDIA:
                return "EFI_END_OF_MEDIA";
            case RETURN_END_OF_FILE:
                return "EFI_END_OF_FILE";
            case RETURN_INVALID_LANGUAGE:
                return "EFI_INVALID_LANGUAGE";
            case RETURN_COMPROMISED_DATA:
                return "EFI_COMPROMISED_DATA";
            case RETURN_IP_ADDRESS_CONFLICT:
                return "EFI_IP_ADDRESS_CONFLICT";
            case RETURN_HTTP_ERROR:
                return "EFI_HTTP_ERROR";
            case RETURN_WARN_UNKNOWN_GLYPH:
                return "EFI_WARN_UNKNOWN_GLYPH";
            case RETURN_WARN_DELETE_FAILURE:
                return "EFI_WARN_DELETE_FAILURE";
            case RETURN_WARN_WRITE_FAILURE:
                return "EFI_WARN_WRITE_FAILURE";
            case RETURN_WARN_BUFFER_TOO_SMALL:
                return "EFI_WARN_BUFFER_TOO_SMALL";
            case RETURN_WARN_STALE_DATA:
                return "EFI_WARN_STALE_DATA";
            case RETURN_WARN_FILE_SYSTEM:
                return "EFI_WARN_FILE_SYSTEM";
            case RETURN_WARN_RESET_REQUIRED:
                return "EFI_WARN_RESET_REQUIRED";
            default:
                return "EFI_UNKNOWN_STATUS";

        }

    }
    
    /* (2.2) std::to_wstring */

    wstring to_wstring(const string& Str) {

        size_t Length = StrLen(Str);

        wchar_t* Data = new wchar_t[Length + 1];

        for (size_t Index = 0; Index < Length; Index++) {

            Data[Index] = static_cast<wchar_t>(Str[Index]);

        }

        Data[Length] = L'\0';

        wstring Result(Data);

        delete[] Data;

        return Result;

    }

    wstring to_wstring(EFI_STATUS Status) {

        switch (Status) {

            case RETURN_SUCCESS:
                return L"EFI_SUCCESS";
            case RETURN_LOAD_ERROR:
                return L"EFI_LOAD_ERROR";
            case RETURN_INVALID_PARAMETER:
                return L"EFI_INVALID_PARAMETER";
            case RETURN_UNSUPPORTED:
                return L"EFI_UNSUPPORTED";
            case RETURN_BAD_BUFFER_SIZE:
                return L"EFI_BAD_BUFFER_SIZE";
            case RETURN_BUFFER_TOO_SMALL:
                return L"EFI_BUFFER_TOO_SMALL";
            case RETURN_NOT_READY:
                return L"EFI_NOT_READY";
            case RETURN_DEVICE_ERROR:
                return L"EFI_DEVICE_ERROR";
            case RETURN_WRITE_PROTECTED:
                return L"EFI_WRITE_PROTECTED";
            case RETURN_OUT_OF_RESOURCES:
                return L"EFI_OUT_OF_RESOURCES";
            case RETURN_VOLUME_CORRUPTED:
                return L"EFI_VOLUME_CORRUPTED";
            case RETURN_VOLUME_FULL:
                return L"EFI_VOLUME_FULL";
            case RETURN_NO_MEDIA:
                return L"EFI_NO_MEDIA";
            case RETURN_MEDIA_CHANGED:
                return L"EFI_MEDIA_CHANGED";
            case RETURN_NOT_FOUND:
                return L"EFI_NOT_FOUND";
            case RETURN_ACCESS_DENIED:
                return L"EFI_ACCESS_DENIED";
            case RETURN_NO_RESPONSE:
                return L"EFI_NO_RESPONSE";
            case RETURN_NO_MAPPING:
                return L"EFI_NO_MAPPING";
            case RETURN_TIMEOUT:
                return L"EFI_TIMEOUT";
            case RETURN_NOT_STARTED:
                return L"EFI_NOT_STARTED";
            case RETURN_ALREADY_STARTED:
                return L"EFI_ALREADY_STARTED";
            case RETURN_ABORTED:
                return L"EFI_ABORTED";
            case RETURN_ICMP_ERROR:
                return L"EFI_ICMP_ERROR";
            case RETURN_TFTP_ERROR:
                return L"EFI_TFTP_ERROR";
            case RETURN_PROTOCOL_ERROR:
                return L"EFI_PROTOCOL_ERROR";
            case RETURN_INCOMPATIBLE_VERSION:
                return L"EFI_INCOMPATIBLE_VERSION";
            case RETURN_SECURITY_VIOLATION:
                return L"EFI_SECURITY_VIOLATION";
            case RETURN_CRC_ERROR:
                return L"EFI_CRC_ERROR";
            case RETURN_END_OF_MEDIA:
                return L"EFI_END_OF_MEDIA";
            case RETURN_END_OF_FILE:
                return L"EFI_END_OF_FILE";
            case RETURN_INVALID_LANGUAGE:
                return L"EFI_INVALID_LANGUAGE";
            case RETURN_COMPROMISED_DATA:
                return L"EFI_COMPROMISED_DATA";
            case RETURN_IP_ADDRESS_CONFLICT:
                return L"EFI_IP_ADDRESS_CONFLICT";
            case RETURN_HTTP_ERROR:
                return L"EFI_HTTP_ERROR";
            case RETURN_WARN_UNKNOWN_GLYPH:
                return L"EFI_WARN_UNKNOWN_GLYPH";
            case RETURN_WARN_DELETE_FAILURE:
                return L"EFI_WARN_DELETE_FAILURE";
            case RETURN_WARN_WRITE_FAILURE:
                return L"EFI_WARN_WRITE_FAILURE";
            case RETURN_WARN_BUFFER_TOO_SMALL:
                return L"EFI_WARN_BUFFER_TOO_SMALL";
            case RETURN_WARN_STALE_DATA:
                return L"EFI_WARN_STALE_DATA";
            case RETURN_WARN_FILE_SYSTEM:
                return L"EFI_WARN_FILE_SYSTEM";
            case RETURN_WARN_RESET_REQUIRED:
                return L"EFI_WARN_RESET_REQUIRED";
            default:
                return L"EFI_UNKNOWN_STATUS";

        }

    }

    /* (2.4) std::toupper */

    string toupper(const string& Str) {

        size_t Length = StrLen(Str);

        CHAR16* Data = new CHAR16[Length + 1];

        for (size_t Index = 0; Index < Length; Index++) {

            CHAR16 Character = Str[Index];

            if (Character >= L'a' && Character <= L'z') {

                Data[Index] = Character - L'a' + L'A';

            }
            else {

                Data[Index] = Character;

            }

        }

        Data[Length] = L'\0';

        string Result;

        Result.pData = Data;

        return Result;
        
    }

    /* (2.4) std::tolower */

    string tolower(const string& Str) {

        size_t Length = StrLen(Str);

        CHAR16* Data = new CHAR16[Length + 1];

        for (size_t Index = 0; Index < Length; Index++) {

            CHAR16 Character = Str[Index];

            if (Character >= L'A' && Character <= L'Z') {

                Data[Index] = Character - L'A' + L'a';

            }
            else {

                Data[Index] = Character;

            }

        }

        Data[Length] = L'\0';

        string Result;

        Result.pData = Data;

        return Result;
        
    }

    /* (2.5) std::append */

    string append(const string& Str1, const string& Str2) {

        size_t Length1 = StrLen(Str1);
        size_t Length2 = StrLen(Str2);

        CHAR16 *Combined = new CHAR16[Length1 + Length2 + 1];

        for (size_t Index = 0; Index < Length1; Index++) {

            Combined[Index] = Str1[Index];

        }

        for (size_t Index = 0; Index < Length2; Index++) {

            Combined[Length1 + Index] = Str2[Index];
            
        }

        Combined[Length1 + Length2] = L'\0';

        string Result;

        Result.pData = Combined;

        return Result;

    }

    /* (2.6) std::substr */

    string substr(const string& Str, size_t Pos, size_t Length) {

        size_t StrLength = StrLen(Str);

        if (Pos >= StrLength) {
            
            return string();

        }

        size_t SubLen = (Length == -1 || Pos + Length > StrLength) ? StrLength - Pos : Length;

        CHAR16* SubData = new CHAR16[SubLen + 1];

        for (size_t Index = 0; Index < SubLen; Index++) {

            SubData[Index] = Str[Index + Pos];

        }

        SubData[SubLen] = L'\0';

        string Result;
        
        Result.pData = SubData;

        return Result;

    }

    /* (2.7) std::find */

    int find(const string& Str, const string& Target, size_t Pos) {

        size_t StrLength = StrLen(Str);
        size_t TargetLen = StrLen(Target);

        if (TargetLen > StrLength || Pos >= StrLength) {

            return -1;

        }

        for (size_t Index = Pos; Index <= StrLength - TargetLen; Index++) {

            bool Found = TRUE;

            for (size_t Index2 = 0; Index2 < TargetLen; Index2++) {

                if (Str[Index + Index2] != Target[Index2]) {

                    Found = FALSE;

                    break;

                }

            }

            if (Found) {

                return static_cast<int>(Index);

            }

        }

        return -1;

    }

    /* (2.8) Str.length() */

    size_t string::length() const {

        size_t Length = 0;

        if (pData != nullptr) {

            while (pData[Length] != L'\0') {

                Length++;

            }

            return Length;
        }

        return 0;

    }

    /* (2.9) Str.erase() */

    void std::string::erase(char Character) {
        
        CHAR16* Temp = new CHAR16[length() + 1];

        size_t TempIndex = 0;

        for (size_t Index = 0; Index < length(); Index++) {

            if (pData[Index] != Character) {

                Temp[TempIndex++] = pData[Index];

            }

        }

        Temp[TempIndex] = L'\0';

        delete[] pData;

        pData = Temp;

    }

    /* (2.10) Str.c_str() */

    CHAR16* string::c_str() const {

        return pData;

    }

    /* (2.11) std::replace */

    void string::replace(const string& OldStr, const string& NewStr) {

        if (OldStr.length() == 0) {

            return;

        }

        size_t OldStrLength = OldStr.length();

        size_t NewStrLength = NewStr.length();

        size_t Pos = 0;

        while ((Pos = find(*this, OldStr, Pos)) != -1) {

            size_t StrLength = length();

            size_t ResultLen = StrLength - OldStrLength + NewStrLength;

            CHAR16* Result = new CHAR16[ResultLen + 1];

            StrnCpyS(Result, ResultLen + 1, pData, Pos);

            StrCatS(Result, ResultLen + 1, NewStr.c_str());

            StrCatS(Result, ResultLen + 1, pData + Pos + OldStrLength);

            delete[] pData;

            pData = Result;

            Pos += NewStrLength;

        }

    }

    /* (2.13) Str.empty() */

    bool string::empty() const {

        return length() == 0;

    }

    /* (2.14) Str.equal(Str) */

    bool string::equal(const string& Str) const {

        return StrCmp(pData, Str.pData) == 0;

    }

    /* (2.15) Str.to_int() */

    int string::to_int() const {

        int Result = 0;
        
        bool IsNegative = false;

        const char16_t* Pointer = reinterpret_cast<const char16_t*>(pData);
        
        if (*Pointer == '-') {

            IsNegative = true;

            Pointer++;

        }

        while (*Pointer >= '0' && *Pointer <= '9') {

            Result = Result * 10 + (*Pointer - '0');

            Pointer++;

        }

        if (IsNegative) {

            Result = -Result;

        }


        return Result;

    }

    /* (2.16) std::hex */

    Cout& operator<<(Cout& lOut, const Hex& Manip) {

        gHexValue = TRUE;

        return lOut;

    }

    Hex hex;

    /* (2.17) std::dec */

    Cout& operator<<(Cout& lOut, const Dec& Manip) {

        gHexValue = FALSE;

        return lOut;

    }

    Dec dec;

    /* (3) Print Functions */

    /* (3.1) std::cout */

    Cout &Cout::operator<<(const char *lString) {

        while (*lString) {

            CHAR16 Buffer[2];

            Buffer[0] = static_cast<CHAR16>(*lString++);

            Buffer[1] = '\0';

            Print(Buffer);

        }

        return *this;

    }

    Cout& Cout::operator<<(const CHAR16 *lString) {

        Print(lString);

        return *this;
        
    }

    Cout& Cout::operator<<(UINT8 Number) {

        CHAR16 Buffer[STD_MAX_STRING_LENGTH];

        if (gHexValue) {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%x"), Number);

        }
        else {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%u"), Number);

        }

        Print(Buffer);

        return *this;

    }

    Cout& Cout::operator<<(UINT16 Number) {

        CHAR16 Buffer[STD_MAX_STRING_LENGTH];

        if (gHexValue) {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%x"), Number);

        }
        else {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%u"), Number);

        }

        Print(Buffer);

        return *this;

    }

    Cout& Cout::operator<<(UINT32 Number) {

        CHAR16 Buffer[STD_MAX_STRING_LENGTH];

        if (gHexValue) {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%x"), Number);

        }
        else {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%u"), Number);
            
        }

        Print(Buffer);

        return *this;

    }

    Cout& Cout::operator<<(UINTN Number) {

        CHAR16 Buffer[STD_MAX_STRING_LENGTH];

        if (gHexValue) {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%lx"), Number);

        }
        else {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%lu"), Number);

        }

        Print(Buffer);

        return *this;
        
    }

    Cout& Cout::operator<<(INT8 Number) {
        
        CHAR16 Buffer[STD_MAX_STRING_LENGTH];

        if (gHexValue) {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%x"), Number);

        }
        else {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%d"), Number);

        }

        Print(Buffer);

        return *this;

    }

    Cout& Cout::operator<<(INT16 Number) {

        CHAR16 Buffer[STD_MAX_STRING_LENGTH];

        if (gHexValue) {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%x"), Number);
        }
        else {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%d"), Number);
            
        }

        Print(Buffer);
        
        return *this;

    }

    Cout& Cout::operator<<(INT32 Number) {

        CHAR16 Buffer[STD_MAX_STRING_LENGTH];

        if (gHexValue) {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%x"), Number);

        }
        else {
            
            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%d"), Number);
            
        }

        Print(Buffer);

        return *this;

    }

    Cout& Cout::operator<<(INTN Number) {

        CHAR16 Buffer[STD_MAX_STRING_LENGTH];

        if (gHexValue) {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%lx"), Number);

        }
        else {

            UnicodeSPrint(Buffer, sizeof(Buffer), reinterpret_cast<CHAR16 *>(L"%ld"), Number);
            
        }

        Print(Buffer);

        return *this;
        
    }

    Cout& Cout::operator<<(double Number) {
        
        CHAR16 Buffer[STD_MAX_STRING_LENGTH];

        DoubleToString(Number, Buffer, sizeof(Buffer));

        Print(Buffer);

        return *this;

    }

    Cout& operator<<(Cout& lOut, const Endl& lEndl) {
        
        Print(reinterpret_cast<CHAR16 *>(L"\n"));

        return lOut;

    }

    Cout cout;

    /* (3.1) std::wcout */

    Wcout& Wcout::operator<<(const wchar_t *lString) {

        Print(reinterpret_cast<CHAR16 *>(L"%s"), lString);

        return *this;

    }

    Wcout& Wcout::operator<<(const Endl& lEndl) {

        Print(reinterpret_cast<CHAR16 *>(L"\n"));

        return *this;

    }

    Wcout wcout;

    /* (4) Input Functions */

    /* (4.1) std::cin */

    Cin& Cin::operator>>(string& Str) {

        CHAR16 Buffer[STD_MAX_STRING_LENGTH];

        EFI_STATUS Status = GetString(Buffer);

        if (!EFI_ERROR(Status)) {

            char CharBuffer[STD_MAX_STRING_LENGTH];

            UnicodeStrToAsciiStrS(Buffer, CharBuffer, sizeof(CharBuffer));
            
            Str = CharBuffer;

        }

        return *this;

    }

    Cin cin;

    /* (4.2) std::cin.get() */

    void Cin::get() {

        Pause();

    }

    /* (4.3) std::cin_s */

    Cin_s& Cin_s::operator>>(string& Str) {

        CHAR16 Buffer[STD_MAX_STRING_LENGTH];

        EFI_STATUS Status = GetStringS(Buffer);

        if (!EFI_ERROR(Status)) {

            char CharBuffer[STD_MAX_STRING_LENGTH];

            UnicodeStrToAsciiStrS(Buffer, CharBuffer, sizeof(CharBuffer));
            
            Str = CharBuffer;

        }

        return *this;
        
    }

    Cin_s cin_s;

    /* (5) Thread Functions */

    /* (5.1) std::thread */

    thread::thread() :pThreadEvent(nullptr) {}

    thread::~thread() {

        if (pThreadEvent) {

            gBS->CloseEvent(pThreadEvent);

        }

    }

    EFI_STATUS thread::create(EventFunc func) {

        if (!func) {

            return EFI_INVALID_PARAMETER;

        }

        EFI_STATUS Status = gBS->CreateEvent(EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_CALLBACK, func, nullptr, &pThreadEvent);

        return Status;

    }

    EFI_STATUS thread::start() {

        if (!pThreadEvent) {

            return EFI_NOT_READY;

        }

        EFI_STATUS Status = gBS->SetTimer(pThreadEvent, TimerPeriodic, 0);

        return Status;

    }

    EFI_STATUS thread::terminate() {

        if (!pThreadEvent) {

            return EFI_NOT_FOUND;

        }

        EFI_STATUS Status = gBS->CloseEvent(pThreadEvent);

        pThreadEvent = nullptr;

        return Status;

    }

    thread Thread;

}