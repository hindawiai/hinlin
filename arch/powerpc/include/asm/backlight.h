<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Routines क्रम handling backlight control on PowerBooks
 *
 * For now, implementation resides in
 * arch/घातerpc/platक्रमms/घातermac/backlight.c
 *
 */
#अगर_अघोषित __ASM_POWERPC_BACKLIGHT_H
#घोषणा __ASM_POWERPC_BACKLIGHT_H
#अगर_घोषित __KERNEL__

#समावेश <linux/fb.h>
#समावेश <linux/mutex.h>

/* For locking inकाष्ठाions, see the implementation file */
बाह्य काष्ठा backlight_device *pmac_backlight;
बाह्य काष्ठा mutex pmac_backlight_mutex;

बाह्य पूर्णांक pmac_backlight_curve_lookup(काष्ठा fb_info *info, पूर्णांक value);

बाह्य पूर्णांक pmac_has_backlight_type(स्थिर अक्षर *type);

बाह्य व्योम pmac_backlight_key(पूर्णांक direction);
अटल अंतरभूत व्योम pmac_backlight_key_up(व्योम)
अणु
	pmac_backlight_key(0);
पूर्ण
अटल अंतरभूत व्योम pmac_backlight_key_करोwn(व्योम)
अणु
	pmac_backlight_key(1);
पूर्ण

बाह्य व्योम pmac_backlight_set_legacy_brightness_pmu(पूर्णांक brightness);
बाह्य पूर्णांक pmac_backlight_set_legacy_brightness(पूर्णांक brightness);
बाह्य पूर्णांक pmac_backlight_get_legacy_brightness(व्योम);

बाह्य व्योम pmac_backlight_enable(व्योम);
बाह्य व्योम pmac_backlight_disable(व्योम);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर
