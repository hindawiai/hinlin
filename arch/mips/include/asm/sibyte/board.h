<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2000,2001,2002,2003,2004 Broadcom Corporation
 */

#अगर_अघोषित _SIBYTE_BOARD_H
#घोषणा _SIBYTE_BOARD_H

#अगर defined(CONFIG_SIBYTE_SWARM) || defined(CONFIG_SIBYTE_CRHONE) || \
    defined(CONFIG_SIBYTE_CRHINE) || defined(CONFIG_SIBYTE_LITTLESUR)
#समावेश <यंत्र/sibyte/swarm.h>
#पूर्ण_अगर

#अगर defined(CONFIG_SIBYTE_SENTOSA) || defined(CONFIG_SIBYTE_RHONE)
#समावेश <यंत्र/sibyte/sentosa.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_SIBYTE_CARMEL
#समावेश <यंत्र/sibyte/carmel.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_SIBYTE_BIGSUR
#समावेश <यंत्र/sibyte/bigsur.h>
#पूर्ण_अगर

#अगर_घोषित __ASSEMBLY__

#अगर_घोषित LEDS_PHYS
#घोषणा setleds(t0, t1, c0, c1, c2, c3) \
	li	t0, (LEDS_PHYS|0xa0000000); \
	li	t1, c0; \
	sb	t1, 0x18(t0); \
	li	t1, c1; \
	sb	t1, 0x10(t0); \
	li	t1, c2; \
	sb	t1, 0x08(t0); \
	li	t1, c3; \
	sb	t1, 0x00(t0)
#अन्यथा
#घोषणा setleds(t0, t1, c0, c1, c2, c3)
#पूर्ण_अगर /* LEDS_PHYS */

#अन्यथा

व्योम swarm_setup(व्योम);

#अगर_घोषित LEDS_PHYS
बाह्य व्योम setleds(अक्षर *str);
#अन्यथा
#घोषणा setleds(s) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* LEDS_PHYS */

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _SIBYTE_BOARD_H */
