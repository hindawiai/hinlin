<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_DELAY_H
#घोषणा _ASM_POWERPC_DELAY_H
#अगर_घोषित __KERNEL__

#समावेश <linux/processor.h>
#समावेश <यंत्र/समय.स>

/*
 * Copyright 1996, Paul Mackerras.
 * Copyright (C) 2009 Freescale Semiconductor, Inc. All rights reserved.
 *
 * PPC64 Support added by Dave Engebretsen, Todd Inglett, Mike Corrigan,
 * Anton Blanअक्षरd.
 */

बाह्य व्योम __delay(अचिन्हित दीर्घ loops);
बाह्य व्योम udelay(अचिन्हित दीर्घ usecs);

/*
 * On shared processor machines the generic implementation of mdelay can
 * result in large errors. While each iteration of the loop inside mdelay
 * is supposed to take 1ms, the hypervisor could sleep our partition क्रम
 * दीर्घer (eg 10ms). With the right timing these errors can add up.
 *
 * Since there is no 32bit overflow issue on 64bit kernels, just call
 * udelay directly.
 */
#अगर_घोषित CONFIG_PPC64
#घोषणा mdelay(n)	udelay((n) * 1000)
#पूर्ण_अगर

/**
 * spin_event_समयout - spin until a condition माला_लो true or a समयout elapses
 * @condition: a C expression to evalate
 * @समयout: समयout, in microseconds
 * @delay: the number of microseconds to delay between each evaluation of
 *         @condition
 *
 * The process spins until the condition evaluates to true (non-zero) or the
 * समयout elapses.  The वापस value of this macro is the value of
 * @condition when the loop terminates. This allows you to determine the cause
 * of the loop terminates.  If the वापस value is zero, then you know a
 * समयout has occurred.
 *
 * This primary purpose of this macro is to poll on a hardware रेजिस्टर
 * until a status bit changes.  The समयout ensures that the loop still
 * terminates even अगर the bit never changes.  The delay is क्रम devices that
 * need a delay in between successive पढ़ोs.
 *
 * gcc will optimize out the अगर-statement अगर @delay is a स्थिरant.
 */
#घोषणा spin_event_समयout(condition, समयout, delay)                          \
(अणु                                                                             \
	typeof(condition) __ret;                                               \
	अचिन्हित दीर्घ __loops = tb_ticks_per_usec * समयout;                   \
	अचिन्हित दीर्घ __start = mftb();                                     \
                                                                               \
	अगर (delay) अणु                                                           \
		जबतक (!(__ret = (condition)) &&                               \
				(tb_ticks_since(__start) <= __loops))          \
			udelay(delay);                                         \
	पूर्ण अन्यथा अणु                                                               \
		spin_begin();                                                  \
		जबतक (!(__ret = (condition)) &&                               \
				(tb_ticks_since(__start) <= __loops))          \
			spin_cpu_relax();                                      \
		spin_end();                                                    \
	पूर्ण                                                                      \
	अगर (!__ret)                                                            \
		__ret = (condition);                                           \
	__ret;		                                                       \
पूर्ण)

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_DELAY_H */
