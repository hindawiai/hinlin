<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_LOADAVG_H
#घोषणा _LINUX_SCHED_LOADAVG_H

/*
 * These are the स्थिरant used to fake the fixed-poपूर्णांक load-average
 * counting. Some notes:
 *  - 11 bit fractions expand to 22 bits by the multiplies: this gives
 *    a load-average precision of 10 bits पूर्णांकeger + 11 bits fractional
 *  - अगर you want to count load-averages more often, you need more
 *    precision, or rounding will get you. With 2-second counting freq,
 *    the EXP_n values would be 1981, 2034 and 2043 अगर still using only
 *    11 bit fractions.
 */
बाह्य अचिन्हित दीर्घ avenrun[];		/* Load averages */
बाह्य व्योम get_avenrun(अचिन्हित दीर्घ *loads, अचिन्हित दीर्घ offset, पूर्णांक shअगरt);

#घोषणा FSHIFT		11		/* nr of bits of precision */
#घोषणा FIXED_1		(1<<FSHIFT)	/* 1.0 as fixed-poपूर्णांक */
#घोषणा LOAD_FREQ	(5*HZ+1)	/* 5 sec पूर्णांकervals */
#घोषणा EXP_1		1884		/* 1/exp(5sec/1min) as fixed-poपूर्णांक */
#घोषणा EXP_5		2014		/* 1/exp(5sec/5min) */
#घोषणा EXP_15		2037		/* 1/exp(5sec/15min) */

/*
 * a1 = a0 * e + a * (1 - e)
 */
अटल अंतरभूत अचिन्हित दीर्घ
calc_load(अचिन्हित दीर्घ load, अचिन्हित दीर्घ exp, अचिन्हित दीर्घ active)
अणु
	अचिन्हित दीर्घ newload;

	newload = load * exp + active * (FIXED_1 - exp);
	अगर (active >= load)
		newload += FIXED_1-1;

	वापस newload / FIXED_1;
पूर्ण

बाह्य अचिन्हित दीर्घ calc_load_n(अचिन्हित दीर्घ load, अचिन्हित दीर्घ exp,
				 अचिन्हित दीर्घ active, अचिन्हित पूर्णांक n);

#घोषणा LOAD_INT(x) ((x) >> FSHIFT)
#घोषणा LOAD_FRAC(x) LOAD_INT(((x) & (FIXED_1-1)) * 100)

बाह्य व्योम calc_global_load(व्योम);

#पूर्ण_अगर /* _LINUX_SCHED_LOADAVG_H */
