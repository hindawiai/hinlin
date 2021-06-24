<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-ep93xx/include/mach/hardware.h
 */

#अगर_अघोषित __ASM_ARCH_HARDWARE_H
#घोषणा __ASM_ARCH_HARDWARE_H

#समावेश "platform.h"

/*
 * The EP93xx has two बाह्यal crystal oscillators.  To generate the
 * required high-frequency घड़ीs, the processor uses two phase-locked-
 * loops (PLLs) to multiply the incoming बाह्यal घड़ी संकेत to much
 * higher frequencies that are then भागided करोwn by programmable भागiders
 * to produce the needed घड़ीs.  The PLLs operate independently of one
 * another.
 */
#घोषणा EP93XX_EXT_CLK_RATE	14745600
#घोषणा EP93XX_EXT_RTC_RATE	32768

#घोषणा EP93XX_KEYTCHCLK_DIV4	(EP93XX_EXT_CLK_RATE / 4)
#घोषणा EP93XX_KEYTCHCLK_DIV16	(EP93XX_EXT_CLK_RATE / 16)

#पूर्ण_अगर
