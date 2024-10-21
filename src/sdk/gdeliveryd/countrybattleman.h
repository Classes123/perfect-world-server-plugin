#ifndef GDELIVERYD_COUNTRYBATTLEMAN_H
#define GDELIVERYD_COUNTRYBATTLEMAN_H

namespace GNET
{
    /**
     * Класс ЧАСТИЧНО восстановлен!
     */
    class CountryBattleMan
    {
        typedef char byte_t; // псевдоним для char, чтобы не было путаницы

        struct CountryInfo
        {
            float major_strength;
            int minor_strength;
            int online_player_cnt;
            int domains_cnt;
            int country_scores;
            float player_total_scores;
            byte_t king_info[0x42C - 0x18];             // CountryKing king_info;
            byte_t communication_map[0x438 - 0x42C];    // COUNTRY_COMMUNICATION_MAP communication_map;
        };

    public:
        byte_t _observer[8];                            // Сдвиг от наследования IntervalTimer::Observer
        int _group_index;
        int _arrange_country_type;
        int _status;
        int _capital_worldtag;
        int _calc_domains_timer;
        int _country_id_ctrl;
        int _adjust_time;
        unsigned int _db_send_bonus_per_sec;
        byte_t _bonus_limit[0x40 - 0x28];               // BonusLimit _bonus_limit;
        byte_t _servers[0x4C - 0x40];                   // SERVER_LIST _servers;
        byte_t _domain_map[0x58 - 0x4C];                // DOMAIN_MAP _domain_map;
        byte_t _player_map[0x64 - 0x58];                // PLAYER_ENTRY_MAP _player_map;
        byte_t _player_score_map[0x70 - 0x64];          // PLAYER_SCORE_MAP _player_score_map;
        byte_t _move_info[0x7C - 0x70];                 // MOVE_LIST _move_info;
        byte_t _players_wait_fight[0x88 - 0x7C];        // PLAYER_WAIT_FIGHT_LIST _players_wait_fight;
        byte_t _occupation_fac_list[0x94 - 0x88];       // OCCUPATION_FAC_LIST _occupation_fac_list;
        byte_t _player_bonus_list[0xA0 - 0x94];         // PLAYER_BONUS_LIST _player_bonus_list;
        byte_t _capital_info[0x170 - 0xA0];             // CapitalInfo _capital_info[COUNTRY_MAX_CNT];
        CountryInfo _country_info[4];                   // CountryInfo _country_info[COUNTRY_MAX_CNT];
        unsigned char _open_days[7];                    // unsigned char _open_days[WEEK_DAY_CNT];
        char _zone_country_map[0x1264 - 0x1258];        // ZONE_COUNTRY_MAP _zone_country_map;
    };
}

#endif // GDELIVERYD_COUNTRYBATTLEMAN_H