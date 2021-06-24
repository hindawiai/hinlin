<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/common/समय-acorn.c
 *
 *  Copyright (c) 1996-2000 Russell King.
 *
 *  Changelog:
 *   24-Sep-1996	RMK	Created
 *   10-Oct-1996	RMK	Brought up to date with arch-sa110eval
 *   04-Dec-1997	RMK	Updated क्रम new arch/arm/समय.c
 *   13=Jun-2004	DS	Moved to arch/arm/common b/c shared w/CLPS7500
 */
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/hardware/ioc.h>

#समावेश <यंत्र/mach/समय.स>

#घोषणा RPC_CLOCK_FREQ 2000000
#घोषणा RPC_LATCH DIV_ROUND_CLOSEST(RPC_CLOCK_FREQ, HZ)

अटल u32 ioc_समय;

अटल u64 ioc_समयr_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	अचिन्हित पूर्णांक count1, count2, status;
	अचिन्हित दीर्घ flags;
	u32 ticks;

	local_irq_save(flags);
	ioc_ग_लिखोb (0, IOC_T0LATCH);
	barrier ();
	count1 = ioc_पढ़ोb(IOC_T0CNTL) | (ioc_पढ़ोb(IOC_T0CNTH) << 8);
	barrier ();
	status = ioc_पढ़ोb(IOC_IRQREQA);
	barrier ();
	ioc_ग_लिखोb (0, IOC_T0LATCH);
	barrier ();
	count2 = ioc_पढ़ोb(IOC_T0CNTL) | (ioc_पढ़ोb(IOC_T0CNTH) << 8);
	ticks = ioc_समय + RPC_LATCH - count2;
	local_irq_restore(flags);

	अगर (count2 < count1) अणु
		/*
		 * The समयr has not reloaded between पढ़ोing count1 and
		 * count2, check whether an पूर्णांकerrupt was actually pending.
		 */
		अगर (status & (1 << 5))
			ticks += RPC_LATCH;
	पूर्ण अन्यथा अगर (count2 > count1) अणु
		/*
		 * The समयr has reloaded, so count2 indicates the new
		 * count since the wrap.  The पूर्णांकerrupt would not have
		 * been processed, so add the missed ticks.
		 */
		ticks += RPC_LATCH;
	पूर्ण

	वापस ticks;
पूर्ण

अटल काष्ठा घड़ीsource ioस_समय_घड़ीsource = अणु
	.पढ़ो = ioc_समयr_पढ़ो,
	.mask = CLOCKSOURCE_MASK(32),
	.rating = 100,
पूर्ण;

व्योम __init ioस_समय_init(व्योम)
अणु
	ioc_ग_लिखोb(RPC_LATCH & 255, IOC_T0LTCHL);
	ioc_ग_लिखोb(RPC_LATCH >> 8, IOC_T0LTCHH);
	ioc_ग_लिखोb(0, IOC_T0GO);
पूर्ण

अटल irqवापस_t
ioc_समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	ioc_समय += RPC_LATCH;
	legacy_समयr_tick(1);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Set up समयr पूर्णांकerrupt.
 */
व्योम __init ioc_समयr_init(व्योम)
अणु
	WARN_ON(घड़ीsource_रेजिस्टर_hz(&ioस_समय_घड़ीsource, RPC_CLOCK_FREQ));
	ioस_समय_init();
	अगर (request_irq(IRQ_TIMER0, ioc_समयr_पूर्णांकerrupt, 0, "timer", शून्य))
		pr_err("Failed to request irq %d (timer)\n", IRQ_TIMER0);
पूर्ण
