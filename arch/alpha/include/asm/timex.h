<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/यंत्र-alpha/समयx.h
 *
 * ALPHA architecture समयx specअगरications
 */
#अगर_अघोषित _ASMALPHA_TIMEX_H
#घोषणा _ASMALPHA_TIMEX_H

/* With only one or two oddballs, we use the RTC as the ticker, selecting
   the 32.768kHz reference घड़ी, which nicely भागides करोwn to our HZ.  */
#घोषणा CLOCK_TICK_RATE	32768

/*
 * Standard way to access the cycle counter.
 * Currently only used on SMP क्रम scheduling.
 *
 * Only the low 32 bits are available as a continuously counting entity. 
 * But this only means we'll क्रमce a reschedule every 8 seconds or so,
 * which isn't an evil thing.
 */

प्रकार अचिन्हित पूर्णांक cycles_t;

अटल अंतरभूत cycles_t get_cycles (व्योम)
अणु
	cycles_t ret;
	__यंत्र__ __अस्थिर__ ("rpcc %0" : "=r"(ret));
	वापस ret;
पूर्ण

#पूर्ण_अगर
