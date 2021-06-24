<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2000, 2001 Broadcom Corporation
 */
#अगर_अघोषित __ASM_SIBYTE_SENTOSA_H
#घोषणा __ASM_SIBYTE_SENTOSA_H

#समावेश <यंत्र/sibyte/sb1250.h>
#समावेश <यंत्र/sibyte/sb1250_पूर्णांक.h>

#अगर_घोषित CONFIG_SIBYTE_SENTOSA
#घोषणा SIBYTE_BOARD_NAME "BCM91250E (Sentosa)"
#पूर्ण_अगर
#अगर_घोषित CONFIG_SIBYTE_RHONE
#घोषणा SIBYTE_BOARD_NAME "BCM91125E (Rhone)"
#पूर्ण_अगर

/* Generic bus chip selects */
#अगर_घोषित CONFIG_SIBYTE_RHONE
#घोषणा LEDS_CS		6
#घोषणा LEDS_PHYS	0x1d0a0000
#पूर्ण_अगर

/* GPIOs */
#घोषणा K_GPIO_DBG_LED	0

#पूर्ण_अगर /* __ASM_SIBYTE_SENTOSA_H */
