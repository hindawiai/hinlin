<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_DELAY_H
#घोषणा _LINUX_DELAY_H

/*
 * Copyright (C) 1993 Linus Torvalds
 *
 * Delay routines, using a pre-computed "loops_per_jiffy" value.
 *
 * Please note that ndelay(), udelay() and mdelay() may वापस early क्रम
 * several reasons:
 *  1. computed loops_per_jअगरfy too low (due to the समय taken to
 *     execute the समयr पूर्णांकerrupt.)
 *  2. cache behaviour affecting the समय it takes to execute the
 *     loop function.
 *  3. CPU घड़ी rate changes.
 *
 * Please see this thपढ़ो:
 *   https://lists.खोलोwall.net/linux-kernel/2011/01/09/56
 */

#समावेश <linux/kernel.h>

बाह्य अचिन्हित दीर्घ loops_per_jअगरfy;

#समावेश <यंत्र/delay.h>

/*
 * Using udelay() क्रम पूर्णांकervals greater than a few milliseconds can
 * risk overflow क्रम high loops_per_jअगरfy (high bogomips) machines. The
 * mdelay() provides a wrapper to prevent this.  For delays greater
 * than MAX_UDELAY_MS milliseconds, the wrapper is used.  Architecture
 * specअगरic values can be defined in यंत्र-???/delay.h as an override.
 * The 2nd mdelay() definition ensures GCC will optimize away the 
 * जबतक loop क्रम the common हालs where n <= MAX_UDELAY_MS  --  Paul G.
 */

#अगर_अघोषित MAX_UDELAY_MS
#घोषणा MAX_UDELAY_MS	5
#पूर्ण_अगर

#अगर_अघोषित mdelay
#घोषणा mdelay(n) (\
	(__builtin_स्थिरant_p(n) && (n)<=MAX_UDELAY_MS) ? udelay((n)*1000) : \
	(अणुअचिन्हित दीर्घ __ms=(n); जबतक (__ms--) udelay(1000);पूर्ण))
#पूर्ण_अगर

#अगर_अघोषित ndelay
अटल अंतरभूत व्योम ndelay(अचिन्हित दीर्घ x)
अणु
	udelay(DIV_ROUND_UP(x, 1000));
पूर्ण
#घोषणा ndelay(x) ndelay(x)
#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ lpj_fine;
व्योम calibrate_delay(व्योम);
व्योम __attribute__((weak)) calibration_delay_करोne(व्योम);
व्योम msleep(अचिन्हित पूर्णांक msecs);
अचिन्हित दीर्घ msleep_पूर्णांकerruptible(अचिन्हित पूर्णांक msecs);
व्योम usleep_range(अचिन्हित दीर्घ min, अचिन्हित दीर्घ max);

अटल अंतरभूत व्योम ssleep(अचिन्हित पूर्णांक seconds)
अणु
	msleep(seconds * 1000);
पूर्ण

/* see Documentation/समयrs/समयrs-howto.rst क्रम the thresholds */
अटल अंतरभूत व्योम fsleep(अचिन्हित दीर्घ usecs)
अणु
	अगर (usecs <= 10)
		udelay(usecs);
	अन्यथा अगर (usecs <= 20000)
		usleep_range(usecs, 2 * usecs);
	अन्यथा
		msleep(DIV_ROUND_UP(usecs, 1000));
पूर्ण

#पूर्ण_अगर /* defined(_LINUX_DELAY_H) */
