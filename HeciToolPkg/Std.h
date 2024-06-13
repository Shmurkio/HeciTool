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

#pragma once

#ifdef __cplusplus

extern "C" {

    #endif

    /* Libraries */

    #include <Uefi.h>
    #include <Library/UefiLib.h>
    #include <Library/PrintLib.h>
    #include <Library/UefiBootServicesTableLib.h>

    /* Protocols */

    #include <Protocol/SimpleTextInEx.h>

    #ifdef __cplusplus

}

#endif

#define STD_MAX_STRING_LENGTH 1024

extern bool gHexValue;

namespace std {

    /* (1) Data types */

    /* (1.1) std::string */

    class string {

        private:
        
            CHAR16 *pData;
        
        public:

            string();
            string(const char *Data);
            string(const string& Other);

            ~string();

            string& operator=(const string& Other);

            operator const CHAR16*() const;

            size_t length() const;

            void erase (char Character);

            CHAR16 *c_str() const;

            void replace(const string& OldStr, const string& NewStr);

            bool empty() const;

            bool equal(const string& Str) const;

            int to_int() const;

            friend string toupper(const string& Str);
            friend string tolower(const string& Str);

            friend string append(const string& Str1, const string& Str2);

            friend string substr(const string& Str, size_t Pos, size_t Length);

    };

    extern string String;

    /* (1.2) std::wstring */

    class wstring {

        private:

            wchar_t *pData;
        
        public:

            wstring();
            wstring(const wchar_t *Data);
            wstring(const wstring& Other);

            ~wstring();

            wstring& operator=(const wstring& Other);

            operator const wchar_t*() const;

    };

    /* (1.3) std::endl */

    class Cout;

    class Endl {

        public:
            
            friend Cout& operator<<(Cout& lOut, const Endl& lEndl);

    };
    
    extern Endl endl;

    extern wstring Wstring;

    /* (2) Utility Functions */

    /* (2.1) std::to_string */

    string to_string(const wstring& Wstr);
    string to_string(EFI_STATUS Status);

    /* (2.2) std::to_wstring */

    wstring to_wstring(const string& Str);
    wstring to_wstring(EFI_STATUS Status);

    /* (2.3) std::toupper */

    string toupper(const string& Str);

    /* (2.4) std::tolower */

    string tolower(const string& Str);

    /* (2.5) std::append */

    string append(const string& Str1, const string& Str2);

    /* (2.6) std::substr */

    string substr(const string& Str, size_t Pos, size_t Length);

    /* (2.7) std::find */

    int find(const string& Str, const string& Target, size_t Pos);

    /* (2.8) Str.length() */

    /* (2.9) Str.erase() */

    /* (2.10) Str.c_str() */

    /* (2.11) std::replace */

    /* (2.13) Str.empty() */

    /* (2.14) Str.equal(Str) */

    /* (2.15) Str.to_int() */

    /* (2.16) std::hex */

    /* (2.17) std::dec */

    class Hex {

        public:

            Hex() {}

    };

    Cout& operator<<(Cout& lOut, const Hex& Manip);

    extern Hex hex;

    /* (2.17) std::dec */

    class Dec {

        public:

            Dec() {}
        
    };

    Cout& operator<<(Cout& lOut, const Dec& Manip);

    extern Dec dec;

    /* (3) Print Functions */

    /* (3.1) std::cout */

    class Cout {

        public:

            Cout& operator<<(const char *Str);

            Cout& operator<<(const CHAR16 *Str);

            Cout& operator<<(UINT8 Number);
            Cout& operator<<(UINT16 Number);
            Cout& operator<<(UINT32 Number);
            Cout& operator<<(UINTN Number);

            Cout& operator<<(INT8 Number);
            Cout& operator<<(INT16 Number);
            Cout& operator<<(INT32 Number);
            Cout& operator<<(INTN Number);

            Cout& operator<<(double Number);

            friend Cout& operator<<(Cout& lOut, const Endl& lEndl);
        
    };

    extern Cout cout;

    /* (3.2) std::wcout */

    class Wcout {

        public:

            Wcout& operator<<(const wchar_t *Str);

            Wcout& operator<<(const Endl& lEndl);

    };

    extern Wcout wcout;

    /* (4) Input Functions */

    /* (4.1) std::cin */

    class Cin {

        public:

            Cin& operator>>(string& Str);

            void get();

    };

    extern Cin cin;

    /* (4.2) std::cin.get() */

    /* (4.3) std::cin_s */

    class Cin_s {

        public:

            Cin_s& operator>>(string& Str);

    };

    extern Cin_s cin_s;

    /* (5) Thread Functions */

    /* (5.1) std::thread */

    typedef void (EFIAPI *EventFunc)(EFI_EVENT Event, VOID *Context);

    class thread {

        private:

            EFI_EVENT pThreadEvent;

        public:

            thread();

            ~thread();

            EFI_STATUS create(EventFunc Func);

            EFI_STATUS start();

            EFI_STATUS terminate();

    };

    extern thread Thread;

}