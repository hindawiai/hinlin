<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2013 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_TIMEX_H
#घोषणा _XTENSA_TIMEX_H

#समावेश <यंत्र/processor.h>

#अगर XCHAL_NUM_TIMERS > 0 && \
	XTENSA_INT_LEVEL(XCHAL_TIMER0_INTERRUPT) <= XCHAL_EXCM_LEVEL
# define LINUX_TIMER     0
# define LINUX_TIMER_INT XCHAL_TIMER0_INTERRUPT
#या_अगर XCHAL_NUM_TIMERS > 1 && \
	XTENSA_INT_LEVEL(XCHAL_TIMER1_INTERRUPT) <= XCHAL_EXCM_LEVEL
# define LINUX_TIMER     1
# define LINUX_TIMER_INT XCHAL_TIMER1_INTERRUPT
#या_अगर XCHAL_NUM_TIMERS > 2 && \
	XTENSA_INT_LEVEL(XCHAL_TIMER2_INTERRUPT) <= XCHAL_EXCM_LEVEL
# define LINUX_TIMER     2
# define LINUX_TIMER_INT XCHAL_TIMER2_INTERRUPT
#अन्यथा
# error "Bad timer number for Linux configurations!"
#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ ccount_freq;

प्रकार अचिन्हित दीर्घ दीर्घ cycles_t;

#घोषणा get_cycles()	(0)

व्योम local_समयr_setup(अचिन्हित cpu);

/*
 * Register access.
 */

अटल अंतरभूत अचिन्हित दीर्घ get_ccount (व्योम)
अणु
	वापस xtensa_get_sr(ccount);
पूर्ण

अटल अंतरभूत व्योम set_ccount (अचिन्हित दीर्घ ccount)
अणु
	xtensa_set_sr(ccount, ccount);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_linux_समयr (व्योम)
अणु
	वापस xtensa_get_sr(SREG_CCOMPARE + LINUX_TIMER);
पूर्ण

अटल अंतरभूत व्योम set_linux_समयr (अचिन्हित दीर्घ ccompare)
अणु
	xtensa_set_sr(ccompare, SREG_CCOMPARE + LINUX_TIMER);
पूर्ण

#पूर्ण_अगर	/* _XTENSA_TIMEX_H */
