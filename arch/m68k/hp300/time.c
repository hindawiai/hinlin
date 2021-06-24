<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/m68k/hp300/समय.c
 *
 *  Copyright (C) 1998 Philip Blundell <philb@gnu.org>
 *
 *  This file contains the HP300-specअगरic समय handling code.
 */

#समावेश <यंत्र/ptrace.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/blinken.h>

अटल u64 hp300_पढ़ो_clk(काष्ठा घड़ीsource *cs);

अटल काष्ठा घड़ीsource hp300_clk = अणु
	.name   = "timer",
	.rating = 250,
	.पढ़ो   = hp300_पढ़ो_clk,
	.mask   = CLOCKSOURCE_MASK(32),
	.flags  = CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल u32 clk_total, clk_offset;

/* Clock hardware definitions */

#घोषणा CLOCKBASE	0xf05f8000

#घोषणा	CLKCR1		0x1
#घोषणा	CLKCR2		0x3
#घोषणा	CLKCR3		CLKCR1
#घोषणा	CLKSR		CLKCR2
#घोषणा	CLKMSB1		0x5
#घोषणा	CLKLSB1		0x7
#घोषणा	CLKMSB2		0x9
#घोषणा	CLKMSB3		0xD

#घोषणा	CLKSR_INT1	BIT(0)

/* This is क्रम machines which generate the exact घड़ी. */

#घोषणा HP300_TIMER_CLOCK_FREQ 250000
#घोषणा HP300_TIMER_CYCLES     (HP300_TIMER_CLOCK_FREQ / HZ)
#घोषणा INTVAL                 (HP300_TIMER_CYCLES - 1)

अटल irqवापस_t hp300_tick(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ पंचांगp;

	local_irq_save(flags);
	in_8(CLOCKBASE + CLKSR);
	यंत्र अस्थिर ("movpw %1@(5),%0" : "=d" (पंचांगp) : "a" (CLOCKBASE));
	clk_total += INTVAL;
	clk_offset = 0;
	legacy_समयr_tick(1);
	समयr_heartbeat();
	local_irq_restore(flags);

	/* Turn off the network and SCSI leds */
	blinken_leds(0, 0xe0);
	वापस IRQ_HANDLED;
पूर्ण

अटल u64 hp300_पढ़ो_clk(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर lsb, msb, msb_new;
	u32 ticks;

	local_irq_save(flags);
	/* Read current समयr 1 value */
	msb = in_8(CLOCKBASE + CLKMSB1);
again:
	अगर ((in_8(CLOCKBASE + CLKSR) & CLKSR_INT1) && msb > 0)
		clk_offset = INTVAL;
	lsb = in_8(CLOCKBASE + CLKLSB1);
	msb_new = in_8(CLOCKBASE + CLKMSB1);
	अगर (msb_new != msb) अणु
		msb = msb_new;
		जाओ again;
	पूर्ण

	ticks = INTVAL - ((msb << 8) | lsb);
	ticks += clk_offset + clk_total;
	local_irq_restore(flags);

	वापस ticks;
पूर्ण

व्योम __init hp300_sched_init(व्योम)
अणु
  out_8(CLOCKBASE + CLKCR2, 0x1);		/* select CR1 */
  out_8(CLOCKBASE + CLKCR1, 0x1);		/* reset */

  यंत्र अस्थिर(" movpw %0,%1@(5)" : : "d" (INTVAL), "a" (CLOCKBASE));

  अगर (request_irq(IRQ_AUTO_6, hp300_tick, IRQF_TIMER, "timer tick", शून्य))
    pr_err("Couldn't register timer interrupt\n");

  out_8(CLOCKBASE + CLKCR2, 0x1);		/* select CR1 */
  out_8(CLOCKBASE + CLKCR1, 0x40);		/* enable irq */

  घड़ीsource_रेजिस्टर_hz(&hp300_clk, HP300_TIMER_CLOCK_FREQ);
पूर्ण
