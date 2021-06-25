<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2000, 2001, 2002, 2003 Broadcom Corporation
 */
#अगर_अघोषित __ASM_SIBYTE_SWARM_H
#घोषणा __ASM_SIBYTE_SWARM_H

#समावेश <यंत्र/sibyte/sb1250.h>
#समावेश <यंत्र/sibyte/sb1250_पूर्णांक.h>

#अगर_घोषित CONFIG_SIBYTE_SWARM
#घोषणा SIBYTE_BOARD_NAME "BCM91250A (SWARM)"
#घोषणा SIBYTE_HAVE_PCMCIA 1
#घोषणा SIBYTE_HAVE_IDE	   1
#पूर्ण_अगर
#अगर_घोषित CONFIG_SIBYTE_LITTLESUR
#घोषणा SIBYTE_BOARD_NAME "BCM91250C2 (LittleSur)"
#घोषणा SIBYTE_HAVE_PCMCIA 0
#घोषणा SIBYTE_HAVE_IDE	   1
#घोषणा SIBYTE_DEFAULT_CONSOLE "cfe0"
#पूर्ण_अगर
#अगर_घोषित CONFIG_SIBYTE_CRHONE
#घोषणा SIBYTE_BOARD_NAME "BCM91125C (CRhone)"
#घोषणा SIBYTE_HAVE_PCMCIA 0
#घोषणा SIBYTE_HAVE_IDE	   0
#पूर्ण_अगर
#अगर_घोषित CONFIG_SIBYTE_CRHINE
#घोषणा SIBYTE_BOARD_NAME "BCM91120C (CRhine)"
#घोषणा SIBYTE_HAVE_PCMCIA 0
#घोषणा SIBYTE_HAVE_IDE	   0
#पूर्ण_अगर

/* Generic bus chip selects */
#घोषणा LEDS_CS		3
#घोषणा LEDS_PHYS	0x100a0000

#अगर_घोषित SIBYTE_HAVE_IDE
#घोषणा IDE_CS		4
#घोषणा IDE_PHYS	0x100b0000
#घोषणा K_GPIO_GB_IDE	4
#घोषणा K_INT_GB_IDE	(K_INT_GPIO_0 + K_GPIO_GB_IDE)
#पूर्ण_अगर

#अगर_घोषित SIBYTE_HAVE_PCMCIA
#घोषणा PCMCIA_CS	6
#घोषणा PCMCIA_PHYS	0x11000000
#घोषणा K_GPIO_PC_READY 9
#घोषणा K_INT_PC_READY	(K_INT_GPIO_0 + K_GPIO_PC_READY)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SIBYTE_SWARM_H */
