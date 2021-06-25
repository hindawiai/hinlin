<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Timer support क्रम Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_TIMER_REGS_H
#घोषणा _ASM_TIMER_REGS_H

/*  This stuff should go पूर्णांकo a platक्रमm specअगरic file  */
#घोषणा TCX0_CLK_RATE		19200
#घोषणा TIMER_ENABLE		0
#घोषणा TIMER_CLR_ON_MATCH	1

/*
 * 8x50 HDD Specs 5-8.  Simulator co-sim not fixed until
 * release 1.1, and then it's "adjustable" and probably not शेषed.
 */
#घोषणा RTOS_TIMER_INT		3
#अगर_घोषित CONFIG_HEXAGON_COMET
#घोषणा RTOS_TIMER_REGS_ADDR	0xAB000000UL
#पूर्ण_अगर
#घोषणा SLEEP_CLK_RATE		32000

#पूर्ण_अगर
