<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Precise Delay Loops क्रम S390
 *
 *    Copyright IBM Corp. 1999, 2008
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Heiko Carstens <heiko.carstens@de.ibm.com>,
 */

#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयx.h>
#समावेश <linux/export.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/vसमयr.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/idle.h>

व्योम __delay(अचिन्हित दीर्घ loops)
अणु
        /*
         * To end the bloody studid and useless discussion about the
         * BogoMips number I took the liberty to define the __delay
         * function in a way that that resulting BogoMips number will
         * yield the megahertz number of the cpu. The important function
         * is udelay and that is करोne using the tod घड़ी. -- martin.
         */
	यंत्र अस्थिर("0: brct %0,0b" : : "d" ((loops/2) + 1));
पूर्ण
EXPORT_SYMBOL(__delay);

अटल व्योम delay_loop(अचिन्हित दीर्घ delta)
अणु
	अचिन्हित दीर्घ end;

	end = get_tod_घड़ी_monotonic() + delta;
	जबतक (!tod_after(get_tod_घड़ी_monotonic(), end))
		cpu_relax();
पूर्ण

व्योम __udelay(अचिन्हित दीर्घ usecs)
अणु
	delay_loop(usecs << 12);
पूर्ण
EXPORT_SYMBOL(__udelay);

व्योम __ndelay(अचिन्हित दीर्घ nsecs)
अणु
	nsecs <<= 9;
	करो_भाग(nsecs, 125);
	delay_loop(nsecs);
पूर्ण
EXPORT_SYMBOL(__ndelay);
