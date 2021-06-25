<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/यंत्र-m68k/समयx.h
 *
 * m68k architecture समयx specअगरications
 */
#अगर_अघोषित _ASMm68K_TIMEX_H
#घोषणा _ASMm68K_TIMEX_H

#अगर_घोषित CONFIG_COLDFIRE
/*
 * CLOCK_TICK_RATE should give the underlying frequency of the tick समयr
 * to make ntp work best.  For Coldfires, that's the मुख्य घड़ी.
 */
#समावेश <यंत्र/coldfire.h>
#घोषणा CLOCK_TICK_RATE	MCF_CLK
#अन्यथा
/*
 * This शेष CLOCK_TICK_RATE is probably wrong क्रम many 68k boards
 * Users of those boards will need to check and modअगरy accordingly
 */
#घोषणा CLOCK_TICK_RATE	1193180 /* Underlying HZ */
#पूर्ण_अगर

प्रकार अचिन्हित दीर्घ cycles_t;

अटल अंतरभूत cycles_t get_cycles(व्योम)
अणु
	वापस 0;
पूर्ण

बाह्य अचिन्हित दीर्घ (*mach_अक्रमom_get_entropy)(व्योम);

अटल अंतरभूत अचिन्हित दीर्घ अक्रमom_get_entropy(व्योम)
अणु
	अगर (mach_अक्रमom_get_entropy)
		वापस mach_अक्रमom_get_entropy();
	वापस 0;
पूर्ण
#घोषणा अक्रमom_get_entropy	अक्रमom_get_entropy

#पूर्ण_अगर
