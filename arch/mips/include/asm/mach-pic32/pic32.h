<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Joshua Henderson <joshua.henderson@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#अगर_अघोषित _ASM_MACH_PIC32_H
#घोषणा _ASM_MACH_PIC32_H

#समावेश <linux/पन.स>

/*
 * PIC32 रेजिस्टर offsets क्रम SET/CLR/INV where supported.
 */
#घोषणा PIC32_CLR(_reg)		((_reg) + 0x04)
#घोषणा PIC32_SET(_reg)		((_reg) + 0x08)
#घोषणा PIC32_INV(_reg)		((_reg) + 0x0C)

/*
 * PIC32 Base Register Offsets
 */
#घोषणा PIC32_BASE_CONFIG	0x1f800000
#घोषणा PIC32_BASE_OSC		0x1f801200
#घोषणा PIC32_BASE_RESET	0x1f801240
#घोषणा PIC32_BASE_PPS		0x1f801400
#घोषणा PIC32_BASE_UART		0x1f822000
#घोषणा PIC32_BASE_PORT		0x1f860000
#घोषणा PIC32_BASE_DEVCFG2	0x1fc4ff44

/*
 * Register unlock sequence required क्रम some रेजिस्टर access.
 */
व्योम pic32_syskey_unlock_debug(स्थिर अक्षर *fn, स्थिर uदीर्घ ln);
#घोषणा pic32_syskey_unlock()	\
	pic32_syskey_unlock_debug(__func__, __LINE__)

#पूर्ण_अगर /* _ASM_MACH_PIC32_H */
