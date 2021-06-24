<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Functions निजी to घातer supply class
 *
 *  Copyright तऊ 2007  Anton Vorontsov <cbou@mail.ru>
 *  Copyright तऊ 2004  Szabolcs Gyurko
 *  Copyright तऊ 2003  Ian Molton <spyro@f2s.com>
 *
 *  Modअगरied: 2004, Oct     Szabolcs Gyurko
 */

काष्ठा device;
काष्ठा device_type;
काष्ठा घातer_supply;

#अगर_घोषित CONFIG_SYSFS

बाह्य व्योम घातer_supply_init_attrs(काष्ठा device_type *dev_type);
बाह्य पूर्णांक घातer_supply_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env);

#अन्यथा

अटल अंतरभूत व्योम घातer_supply_init_attrs(काष्ठा device_type *dev_type) अणुपूर्ण
#घोषणा घातer_supply_uevent शून्य

#पूर्ण_अगर /* CONFIG_SYSFS */

#अगर_घोषित CONFIG_LEDS_TRIGGERS

बाह्य व्योम घातer_supply_update_leds(काष्ठा घातer_supply *psy);
बाह्य पूर्णांक घातer_supply_create_triggers(काष्ठा घातer_supply *psy);
बाह्य व्योम घातer_supply_हटाओ_triggers(काष्ठा घातer_supply *psy);

#अन्यथा

अटल अंतरभूत व्योम घातer_supply_update_leds(काष्ठा घातer_supply *psy) अणुपूर्ण
अटल अंतरभूत पूर्णांक घातer_supply_create_triggers(काष्ठा घातer_supply *psy)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम घातer_supply_हटाओ_triggers(काष्ठा घातer_supply *psy) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_LEDS_TRIGGERS */
