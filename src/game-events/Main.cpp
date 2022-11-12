#include "WinSockManager.h"
#include "Client.h"
#include "Hook.h"


static constexpr const char* const k_ServerIP = "127.0.0.1";
static constexpr const int k_Port = 7777;


static WinSockManager* s_WinSockManager = nullptr;
static Client* s_Client = nullptr;
static Hook* s_ProcessGameEventsHook = nullptr;


static void __stdcall SendGameEvent(const void* gameEventData, int32_t gameEventType, uint32_t gameEventSize)
{
    static constexpr const size_t gameEventMaxSize = 0x1400;
    
    struct alignas(0x4) GameEvent
    {
        int32_t Type;
        uint32_t Size;
        uint8_t Data[gameEventMaxSize];
    };

    GameEvent gameEvent = {};
    gameEvent.Type = gameEventType;
    gameEvent.Size = gameEventSize;
    memcpy_s(gameEvent.Data, sizeof(gameEvent.Data), gameEventData, gameEventSize);

    s_Client->SendData(&gameEvent, sizeof(gameEvent));
}

__declspec(naked) static void SendGameEventThunk()
{
    __asm
    {
        pushfd
        pushad

        push dword ptr [esi - 0xC]
        push dword ptr [esi - 0x10]
        push esi
        call SendGameEvent

        popad
        popfd

        ret
    }
}

static void Initialize()
{
    s_WinSockManager = new WinSockManager();
    
    s_Client = new Client();
    s_Client->Connect(k_ServerIP, k_Port);
    
    s_ProcessGameEventsHook = new Hook(reinterpret_cast<void*>(0x00A254DD), 7);
    s_ProcessGameEventsHook->Enable(SendGameEventThunk);
}

static void Shutdown()
{
    delete s_ProcessGameEventsHook;
    delete s_Client;
    
    delete s_WinSockManager;
}

BOOL WINAPI DllMain(
    _In_ HINSTANCE hinstDLL,
    _In_ DWORD     fdwReason,
    _In_ LPVOID    lpvReserved
)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDLL);
        Initialize();
        break;
    
    case DLL_PROCESS_DETACH:
        Shutdown();
        break;
    }

    return TRUE;
}