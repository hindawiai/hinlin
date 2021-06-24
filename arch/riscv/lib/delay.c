<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#समावेश <linux/delay.h>
#समावेश <linux/param.h>
#समावेश <linux/समयx.h>
#समावेश <linux/export.h>

/*
 * This is copies from arch/arm/include/यंत्र/delay.h
 *
 * Loop (or tick) based delay:
 *
 * loops = loops_per_jअगरfy * jअगरfies_per_sec * delay_us / us_per_sec
 *
 * where:
 *
 * jअगरfies_per_sec = HZ
 * us_per_sec = 1000000
 *
 * Thereक्रमe the स्थिरant part is HZ / 1000000 which is a small
 * fractional number. To make this usable with पूर्णांकeger math, we
 * scale up this स्थिरant by 2^31, perक्रमm the actual multiplication,
 * and scale the result back करोwn by 2^31 with a simple shअगरt:
 *
 * loops = (loops_per_jअगरfy * delay_us * UDELAY_MULT) >> 31
 *
 * where:
 *
 * UDELAY_MULT = 2^31 * HZ / 1000000
 *             = (2^31 / 1000000) * HZ
 *             = 2147.483648 * HZ
 *             = 2147 * HZ + 483648 * HZ / 1000000
 *
 * 31 is the biggest scale shअगरt value that won't overflow 32 bits क्रम
 * delay_us * UDELAY_MULT assuming HZ <= 1000 and delay_us <= 2000.
 */
#घोषणा MAX_UDELAY_US	2000
#घोषणा MAX_UDELAY_HZ	1000
#घोषणा UDELAY_MULT	(2147UL * HZ + 483648UL * HZ / 1000000UL)
#घोषणा UDELAY_SHIFT	31

#अगर HZ > MAX_UDELAY_HZ
#त्रुटि "HZ > MAX_UDELAY_HZ"
#पूर्ण_अगर

/*
 * RISC-V supports both UDELAY and NDELAY.  This is largely the same as above,
 * but with dअगरferent स्थिरants.  I added 10 bits to the shअगरt to get this, but
 * the result is that I need a 64-bit multiply, which is slow on 32-bit
 * platक्रमms.
 *
 * NDELAY_MULT = 2^41 * HZ / 1000000000
 *             = (2^41 / 1000000000) * HZ
 *             = 2199.02325555 * HZ
 *             = 2199 * HZ + 23255550 * HZ / 1000000000
 *
 * The maximum here is to aव्योम 64-bit overflow, but it isn't checked as it
 * won't happen.
 */
#घोषणा MAX_NDELAY_NS   (1ULL << 42)
#घोषणा MAX_NDELAY_HZ	MAX_UDELAY_HZ
#घोषणा NDELAY_MULT	((अचिन्हित दीर्घ दीर्घ)(2199ULL * HZ + 23255550ULL * HZ / 1000000000ULL))
#घोषणा NDELAY_SHIFT	41

#अगर HZ > MAX_NDELAY_HZ
#त्रुटि "HZ > MAX_NDELAY_HZ"
#पूर्ण_अगर

व्योम __delay(अचिन्हित दीर्घ cycles)
अणु
	u64 t0 = get_cycles();

	जबतक ((अचिन्हित दीर्घ)(get_cycles() - t0) < cycles)
		cpu_relax();
पूर्ण
EXPORT_SYMBOL(__delay);

व्योम udelay(अचिन्हित दीर्घ usecs)
अणु
	u64 ucycles = (u64)usecs * lpj_fine * UDELAY_MULT;
	u64 n;

	अगर (unlikely(usecs > MAX_UDELAY_US)) अणु
		n = (u64)usecs * riscv_समयbase;
		करो_भाग(n, 1000000);

		__delay(n);
		वापस;
	पूर्ण

	__delay(ucycles >> UDELAY_SHIFT);
पूर्ण
EXPORT_SYMBOL(udelay);

व्योम ndelay(अचिन्हित दीर्घ nsecs)
अणु
	/*
	 * This करोesn't bother checking for overflow, as it won't happen (it's
	 * an hour) of delay.
	 */
	अचिन्हित दीर्घ दीर्घ ncycles = nsecs * lpj_fine * NDELAY_MULT;
	__delay(ncycles >> NDELAY_SHIFT);
पूर्ण
EXPORT_SYMBOL(ndelay);
