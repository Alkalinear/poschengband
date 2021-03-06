#include "angband.h"

static void _calc_bonuses(void)
{
    if (p_ptr->lev >= 40)
        res_add(RES_FEAR);
}

static void _get_flags(u32b flgs[OF_ARRAY_SIZE])
{
    if (p_ptr->lev >= 40)
        add_flag(flgs, OF_RES_FEAR);
}

static int _get_powers(spell_info* spells, int max)
{
    int ct = 0;
    spell_info* spell = &spells[ct++];

    if (is_good_realm(p_ptr->realm1))
    {
        spell->level = 30;
        spell->cost = 30;
        spell->fail = calculate_fail_rate(spell->level, 70, p_ptr->stat_ind[A_WIS]);
        spell->fn = holy_lance_spell;
    }
    else
    {
        spell->level = 30;
        spell->cost = 30;
        spell->fail = calculate_fail_rate(spell->level, 70, p_ptr->stat_ind[A_WIS]);
        spell->fn = hell_lance_spell;
    }

    return ct;
}

static caster_info * _caster_info(void)
{
    static caster_info me = {0};
    static bool init = FALSE;
    if (!init)
    {
        me.magic_desc = "prayer";
        me.which_stat = A_WIS;
        me.weight = 450;
        me.min_fail = 5;
        init = TRUE;
    }
    return &me;
}

class_t *paladin_get_class(void)
{
    static class_t me = {0};
    static bool init = FALSE;

    if (!init)
    {           /* dis, dev, sav, stl, srh, fos, thn, thb */
    skills_t bs = { 20,  24,  34,   1,  12,   2,  68,  40};
    skills_t xs = {  7,  10,  11,   0,   0,   0,  21,  18};

        me.name = "Paladin";
        me.desc = "A Paladin is a combination of a warrior and a priest. Paladins "
                    "are very good fighters, but not very good at missile weapons. A "
                    "paladin lacks much in the way of abilities. He is poor at "
                    "stealth, perception, searching, and magical devices but has a "
                    "decent saving throw due to his divine alliance. Wisdom determines "
                    "a Paladin's success at praying to his deity.\n \n"
                    "Paladins can select a realm from Life, Crusade, Daemon and Death. "
                    "Like priests, they cannot select which prayers to learn, but are "
                    "rewarded with new prayers by their deities. They can learn all spells, "
                    "but not as fast as priests. They detest paganism so strongly that they "
                    "will even gain experience for destroying high-level pagan spellbooks: "
                    "'pagan' means Life or Crusade spellbooks for a Death/Daemon "
                    "Paladin and all spellbooks other than Life or Crusade for a "
                    "Life/Crusade Paladin. Depending on their realm, they have a class "
                    "power - 'Holy Lance' or 'Hell Lance'.";

        me.stats[A_STR] =  3;
        me.stats[A_INT] = -3;
        me.stats[A_WIS] =  1;
        me.stats[A_DEX] =  0;
        me.stats[A_CON] =  2;
        me.stats[A_CHR] =  2;
        me.base_skills = bs;
        me.extra_skills = xs;
        me.life = 111;
        me.base_hp = 12;
        me.exp = 135;
        me.pets = 40;
        
        me.calc_bonuses = _calc_bonuses;
        me.caster_info = _caster_info;
        /* TODO: This class uses spell books, so we are SOL
        me.get_spells = _get_spells;*/
        me.get_powers = _get_powers;
        me.character_dump = spellbook_character_dump;
        me.get_flags = _get_flags;
        init = TRUE;
    }

    return &me;
}
