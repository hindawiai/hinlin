<शैली गुरु>
/*
 * include/यंत्र-xtensa/delay.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 *
 */

#अगर_अघोषित _XTENSA_DELAY_H
#घोषणा _XTENSA_DELAY_H

#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/param.h>

बाह्य अचिन्हित दीर्घ loops_per_jअगरfy;

अटल अंतरभूत व्योम __delay(अचिन्हित दीर्घ loops)
अणु
	अगर (__builtin_स्थिरant_p(loops) && loops < 2)
		__यंत्र__ __अस्थिर__ ("nop");
	अन्यथा अगर (loops >= 2)
		/* 2 cycles per loop. */
		__यंत्र__ __अस्थिर__ ("1: addi %0, %0, -2; bgeui %0, 2, 1b"
				: "+r" (loops));
पूर्ण

/* Undefined function to get compile-समय error */
व्योम __bad_udelay(व्योम);
व्योम __bad_ndelay(व्योम);

#घोषणा __MAX_UDELAY 30000
#घोषणा __MAX_NDELAY 30000

अटल अंतरभूत व्योम __udelay(अचिन्हित दीर्घ usecs)
अणु
	अचिन्हित दीर्घ start = get_ccount();
	अचिन्हित दीर्घ cycles = (usecs * (ccount_freq >> 15)) >> 5;

	/* Note: all variables are अचिन्हित (can wrap around)! */
	जबतक (((अचिन्हित दीर्घ)get_ccount()) - start < cycles)
		cpu_relax();
पूर्ण

अटल अंतरभूत व्योम udelay(अचिन्हित दीर्घ usec)
अणु
	अगर (__builtin_स्थिरant_p(usec) && usec >= __MAX_UDELAY)
		__bad_udelay();
	अन्यथा
		__udelay(usec);
पूर्ण

अटल अंतरभूत व्योम __ndelay(अचिन्हित दीर्घ nsec)
अणु
	/*
	 * Inner shअगरt makes sure multiplication करोesn't overflow
	 * क्रम legitimate nsec values
	 */
	अचिन्हित दीर्घ cycles = (nsec * (ccount_freq >> 15)) >> 15;
	__delay(cycles);
पूर्ण

#घोषणा ndelay(n) ndelay(n)

अटल अंतरभूत व्योम ndelay(अचिन्हित दीर्घ nsec)
अणु
	अगर (__builtin_स्थिरant_p(nsec) && nsec >= __MAX_NDELAY)
		__bad_ndelay();
	अन्यथा
		__ndelay(nsec);
पूर्ण

#पूर्ण_अगर
