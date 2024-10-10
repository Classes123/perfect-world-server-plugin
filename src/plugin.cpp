#include "libs.h"                   // обертка вокруг libsigcan и libdetour
#include "sdk/cnet/gamed/gsp_if.h"  // содержит только перечисление CHAT каналов

////////////////
// Объявления //
////////////////

/**
 *  Вызов функции
 */
typedef bool (*SystemChatMsg_t)(const void *msg, size_t size, char channel, const void *data, size_t dsize);    // 1. Прототип функции
SystemChatMsg_t g_ptrSystemChatMsg;                                                                             // 2. Указатель на оригинальную функцию
bool SystemChatMsg(const void *msg, size_t size, char channel, const void *data = nullptr, size_t dsize = 0);   // 3. Обертка для удобства (можно и без нее)

/**
 *  Хук функции
 */
LIBDETOUR_DECL_TYPE(void, DeliverItem, void *, unsigned int, const void *, unsigned int);                       // 1. Прототип функции (макрос уже реализован в libdetour для удобства)
libdetour_DeliverItem_t g_ptrDeliverItem;                                                                       // 2. Указатель на оригинальную функцию
void Hook_DeliverItem(void *pTask, unsigned int ulTask, const void *wi, unsigned int ulMulti);                  // 3. "каллбэк"
libdetour_ctx_t g_ctxDeliverItem;                                                                               // 4. Контекст хука

/////////////////////////
// Управление плагином //
/////////////////////////

/**
 *  Точка входа плагина / Старт плагина
 */
__attribute__ ((constructor)) void init()
{
    // Получим указатель на функцию отправки сообщения в системный чат
    // GMSV::SystemChatMsg (gs + 0x84BFBCE)
    g_ptrSystemChatMsg = reinterpret_cast<SystemChatMsg_t>(
        GetFuncPtr(
            "gs",                                                               // Модуль 
            "55 89 E5 53 83 EC 54 8B 45 ? 88 45 ? 83 EC 0C 8D 45"               // Сигнатура
        )
    );

    // Получим указатель на функцию доставки предмета для дальнейшего хука
    // _DeliverItem (libtask.so + 0x26A16)
    g_ptrDeliverItem = reinterpret_cast<libdetour_DeliverItem_t>(
        GetFuncPtr(
            "libtask.so",                                                       // Модуль
            "55 89 E5 53 81 EC 24 04 00 00 E8 ? ? ? ? 5B 81 C3 2B 72 03 00"     // Сигнатура
        )
    );

    // Инициализируем хук
    libdetour_init(
        &g_ctxDeliverItem,                                                      // Контекст хука
        reinterpret_cast<void *>(g_ptrDeliverItem),                             // Указатель на оригинальную функцию
        reinterpret_cast<void *>(&Hook_DeliverItem)                             // Указатель на нашу функцию (каллбэк)
    );
    
    // Активируем хук
    libdetour_add(&g_ctxDeliverItem);
}

/**
 *  Точка выхода плагина
 */
__attribute__ ((destructor)) void fini()
{
    // Если хук активен
    if (g_ctxDeliverItem.detoured)
    {
        // Отключим хук
        libdetour_del(&g_ctxDeliverItem);
    }
}

////////////
// "Тело" //
////////////

/**
 *  Обертка над функцией отправки сообщения в системный чат
 */
bool SystemChatMsg(const void *msg, size_t size, char channel, const void *data, size_t dsize)
{
    // Просто вызываем по указателю, передавая все аргументы и получая результат.
    return g_ptrSystemChatMsg(msg, size, channel, data, dsize);
}

/**
 *  Хук функции доставки предмета
 */
void Hook_DeliverItem(void *pTask, unsigned int ulTask, const void *wi, unsigned int ulMulti)
{
    // Вызовем сначала оригинал, он должен быть в приоретете если у нас что-то пойдет не так
    LIBDETOUR_ORIG_CALL(&g_ctxDeliverItem, DeliverItem, pTask, ulTask, wi, ulMulti);

    // Сундук вызывает квест с ID == 43562
    if (ulTask == 43562)
    {
        // Отправляем сообщение в системный чат
        char16_t msg[] = u"^FFFF00Кто-то открыл cундук!";
        SystemChatMsg(msg, sizeof(msg), GMSV::CHAT_CHANNEL_BROADCAST);
    }
}
