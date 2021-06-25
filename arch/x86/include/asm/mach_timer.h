<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Machine specअगरic calibrate_tsc() क्रम generic.
 *  Split out from समयr_tsc.c by Osamu Tomita <tomita@cinet.co.jp>
 */
/* ------ Calibrate the TSC ------- 
 * Return 2^32 * (1 / (TSC घड़ीs per usec)) क्रम करो_fast_समय_लोoffset().
 * Too much 64-bit arithmetic here to करो this cleanly in C, and क्रम
 * accuracy's sake we want to keep the overhead on the CTC speaker (channel 2)
 * output busy loop as low as possible. We aव्योम पढ़ोing the CTC रेजिस्टरs
 * directly because of the awkward 8-bit access mechanism of the 82C54
 * device.
 */
#अगर_अघोषित _ASM_X86_MACH_DEFAULT_MACH_TIMER_H
#घोषणा _ASM_X86_MACH_DEFAULT_MACH_TIMER_H

#घोषणा CALIBRATE_TIME_MSEC 30 /* 30 msecs */
#घोषणा CALIBRATE_LATCH	\
	((PIT_TICK_RATE * CALIBRATE_TIME_MSEC + 1000/2)/1000)

अटल अंतरभूत व्योम mach_prepare_counter(व्योम)
अणु
       /* Set the Gate high, disable speaker */
	outb((inb(0x61) & ~0x02) | 0x01, 0x61);

	/*
	 * Now let's take care of CTC channel 2
	 *
	 * Set the Gate high, program CTC channel 2 क्रम mode 0,
	 * (पूर्णांकerrupt on terminal count mode), binary count,
	 * load 5 * LATCH count, (LSB and MSB) to begin countकरोwn.
	 *
	 * Some devices need a delay here.
	 */
	outb(0xb0, 0x43);			/* binary, mode 0, LSB/MSB, Ch 2 */
	outb_p(CALIBRATE_LATCH & 0xff, 0x42);	/* LSB of count */
	outb_p(CALIBRATE_LATCH >> 8, 0x42);       /* MSB of count */
पूर्ण

अटल अंतरभूत व्योम mach_countup(अचिन्हित दीर्घ *count_p)
अणु
	अचिन्हित दीर्घ count = 0;
	करो अणु
		count++;
	पूर्ण जबतक ((inb_p(0x61) & 0x20) == 0);
	*count_p = count;
पूर्ण

#पूर्ण_अगर /* _ASM_X86_MACH_DEFAULT_MACH_TIMER_H */
