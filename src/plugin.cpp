#include <cstdio>
#include <cstdlib>
#include "libs.h"
#include "gdeliveryd/countrybattleman.h"

// int __cdecl GNET::CountryBattleMan::ArrangeCountry(CountryBattleMan *const this, bool has_major_str)
// gdeliveryd + 0x083517AA
// 55 89 E5 53 83 EC 24 8B 45 ? 88 45 ? C7 45

LIBDETOUR_DECL_TYPE(int, ArrangeCountry, const GNET::CountryBattleMan *, bool);
libdetour_ArrangeCountry_t g_ptrArrangeCountry;
int Hook_ArrangeCountry(const GNET::CountryBattleMan *_this, bool has_major_str);
libdetour_ctx_t g_ctxArrangeCountry;

__attribute__ ((constructor)) void init()
{
    // gdeliveryd + 0x083517AA
    g_ptrArrangeCountry = reinterpret_cast<libdetour_ArrangeCountry_t>(
        GetFuncPtr(
            "gdeliveryd",
            "55 89 E5 53 83 EC 24 8B 45 ? 88 45 ? C7 45"
        )
    );

    libdetour_init(
        &g_ctxArrangeCountry,
        reinterpret_cast<void *>(g_ptrArrangeCountry),
        reinterpret_cast<void *>(&Hook_ArrangeCountry)
    );
    libdetour_add(&g_ctxArrangeCountry);
}

__attribute__ ((destructor)) void fini()
{
    if (g_ctxArrangeCountry.detoured)
    {
        libdetour_del(&g_ctxArrangeCountry);
    }
}

/**
 * Рачитывает сторону игрока / группы на внутрисерверном БД.
 *
 * Счисление в массивах идет с 0, а результат функции (и далее) с 1.
 * Другими словами, мы должны вернуть `индекс_массива + 1`
 *
 * Стороны:
 * - 1  Вонг    Справа
 * - 2  Лун     Снизу
 * - 3  Найт    Слева
 * - 4  Утгард  Сверху
 *
 * @param _this             класс менеджера
 * @param has_major_str     имеет ли доминирующую силу (?)
 *
 * @return ID стороны (индекс массива + 1)
 */
int Hook_ArrangeCountry(const GNET::CountryBattleMan *_this, bool has_major_str)
{
    // Выберем нужные стороны (Вонг и Найт)
    constexpr int ids[2] = {1, 3};

    // Извлечем кол-во игроков онлайн на этих сторонах
    const int online[2] = {
        _this->_country_info[ids[0] - 1].online_player_cnt,
        _this->_country_info[ids[1] - 1].online_player_cnt
    };

    // Если онлайн одинаковый, то выберем рандомом
    if (online[0] == online[1])
    {
        return ids[rand() % 2];
    }

    // Иначе отправим туда, где онлайн меньше
    return online[0] < online[1] ? ids[0] : ids[1];
}