<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#अगर_अघोषित __ASM_OPENRISC_TIMEX_H
#घोषणा __ASM_OPENRISC_TIMEX_H

#घोषणा get_cycles get_cycles

#समावेश <यंत्र-generic/समयx.h>
#समावेश <यंत्र/spr.h>
#समावेश <यंत्र/spr_defs.h>

अटल अंतरभूत cycles_t get_cycles(व्योम)
अणु
	वापस mfspr(SPR_TTCR);
पूर्ण

/* This isn't really used any more */
#घोषणा CLOCK_TICK_RATE 1000

#घोषणा ARCH_HAS_READ_CURRENT_TIMER

#पूर्ण_अगर
