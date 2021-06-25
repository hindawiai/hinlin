<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Time operations क्रम IP22 machines. Original code may come from
 * Ralf Baechle or David S. Miller (sorry guys, i'm really not sure)
 *
 * Copyright (C) 2001 by Ladislav Michl
 * Copyright (C) 2003, 06 Ralf Baechle (ralf@linux-mips.org)
 */
#समावेश <linux/bcd.h>
#समावेश <linux/i8253.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/समय.स>
#समावेश <linux/ftrace.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/sgialib.h>
#समावेश <यंत्र/sgi/ioc.h>
#समावेश <यंत्र/sgi/hpc3.h>
#समावेश <यंत्र/sgi/ip22.h>

अटल अचिन्हित दीर्घ करोsample(व्योम)
अणु
	u32 ct0, ct1;
	u8 msb;

	/* Start the counter. */
	sgपूर्णांक->tcword = (SGINT_TCWORD_CNT2 | SGINT_TCWORD_CALL |
			 SGINT_TCWORD_MRGEN);
	sgपूर्णांक->tcnt2 = SGINT_TCSAMP_COUNTER & 0xff;
	sgपूर्णांक->tcnt2 = SGINT_TCSAMP_COUNTER >> 8;

	/* Get initial counter invariant */
	ct0 = पढ़ो_c0_count();

	/* Latch and spin until top byte of counter2 is zero */
	करो अणु
		ग_लिखोb(SGINT_TCWORD_CNT2 | SGINT_TCWORD_CLAT, &sgपूर्णांक->tcword);
		(व्योम) पढ़ोb(&sgपूर्णांक->tcnt2);
		msb = पढ़ोb(&sgपूर्णांक->tcnt2);
		ct1 = पढ़ो_c0_count();
	पूर्ण जबतक (msb);

	/* Stop the counter. */
	ग_लिखोb(SGINT_TCWORD_CNT2 | SGINT_TCWORD_CALL | SGINT_TCWORD_MSWST,
	       &sgपूर्णांक->tcword);
	/*
	 * Return the dअगरference, this is how far the r4k counter increments
	 * क्रम every 1/HZ seconds. We round off the nearest 1 MHz of master
	 * घड़ी (= 1000000 / HZ / 2).
	 */

	वापस (ct1 - ct0) / (500000/HZ) * (500000/HZ);
पूर्ण

/*
 * Here we need to calibrate the cycle counter to at least be बंद.
 */
__init व्योम plat_समय_init(व्योम)
अणु
	अचिन्हित दीर्घ r4k_ticks[3];
	अचिन्हित दीर्घ r4k_tick;

	/*
	 * Figure out the r4k offset, the algorithm is very simple and works in
	 * _all_ हालs as दीर्घ as the 8254 counter रेजिस्टर itself works ok (as
	 * an पूर्णांकerrupt driving समयr it करोes not because of bug, this is why
	 * we are using the onchip r4k counter/compare रेजिस्टर to serve this
	 * purpose, but क्रम r4k_offset calculation it will work ok क्रम us).
	 * There are other very complicated ways of perक्रमming this calculation
	 * but this one works just fine so I am not going to futz around. ;-)
	 */
	prपूर्णांकk(KERN_INFO "Calibrating system timer... ");
	करोsample();	/* Prime cache. */
	करोsample();	/* Prime cache. */
	/* Zero is NOT an option. */
	करो अणु
		r4k_ticks[0] = करोsample();
	पूर्ण जबतक (!r4k_ticks[0]);
	करो अणु
		r4k_ticks[1] = करोsample();
	पूर्ण जबतक (!r4k_ticks[1]);

	अगर (r4k_ticks[0] != r4k_ticks[1]) अणु
		prपूर्णांकk("warning: timer counts differ, retrying... ");
		r4k_ticks[2] = करोsample();
		अगर (r4k_ticks[2] == r4k_ticks[0]
		    || r4k_ticks[2] == r4k_ticks[1])
			r4k_tick = r4k_ticks[2];
		अन्यथा अणु
			prपूर्णांकk("disagreement, using average... ");
			r4k_tick = (r4k_ticks[0] + r4k_ticks[1]
				   + r4k_ticks[2]) / 3;
		पूर्ण
	पूर्ण अन्यथा
		r4k_tick = r4k_ticks[0];

	prपूर्णांकk("%d [%d.%04d MHz CPU]\n", (पूर्णांक) r4k_tick,
		(पूर्णांक) (r4k_tick / (500000 / HZ)),
		(पूर्णांक) (r4k_tick % (500000 / HZ)));

	mips_hpt_frequency = r4k_tick * HZ;

	अगर (ip22_is_fullhouse())
		setup_pit_समयr();
पूर्ण

/* Generic SGI handler क्रम (spurious) 8254 पूर्णांकerrupts */
व्योम __irq_entry indy_8254समयr_irq(व्योम)
अणु
	पूर्णांक irq = SGI_8254_0_IRQ;
	ULONG cnt;
	अक्षर c;

	irq_enter();
	kstat_incr_irq_this_cpu(irq);
	prपूर्णांकk(KERN_ALERT "Oops, got 8254 interrupt.\n");
	ArcRead(0, &c, 1, &cnt);
	ArcEnterInteractiveMode();
	irq_निकास();
पूर्ण
