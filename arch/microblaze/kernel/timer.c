<शैली गुरु>
/*
 * Copyright (C) 2007-2013 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2012-2013 Xilinx, Inc.
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched_घड़ी.h>
#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/समयcounter.h>
#समावेश <यंत्र/cpuinfo.h>

अटल व्योम __iomem *समयr_baseaddr;

अटल अचिन्हित पूर्णांक freq_भाग_hz;
अटल अचिन्हित पूर्णांक समयr_घड़ी_freq;

#घोषणा TCSR0	(0x00)
#घोषणा TLR0	(0x04)
#घोषणा TCR0	(0x08)
#घोषणा TCSR1	(0x10)
#घोषणा TLR1	(0x14)
#घोषणा TCR1	(0x18)

#घोषणा TCSR_MDT	(1<<0)
#घोषणा TCSR_UDT	(1<<1)
#घोषणा TCSR_GENT	(1<<2)
#घोषणा TCSR_CAPT	(1<<3)
#घोषणा TCSR_ARHT	(1<<4)
#घोषणा TCSR_LOAD	(1<<5)
#घोषणा TCSR_ENIT	(1<<6)
#घोषणा TCSR_ENT	(1<<7)
#घोषणा TCSR_TINT	(1<<8)
#घोषणा TCSR_PWMA	(1<<9)
#घोषणा TCSR_ENALL	(1<<10)

अटल अचिन्हित पूर्णांक (*पढ़ो_fn)(व्योम __iomem *);
अटल व्योम (*ग_लिखो_fn)(u32, व्योम __iomem *);

अटल व्योम समयr_ग_लिखो32(u32 val, व्योम __iomem *addr)
अणु
	ioग_लिखो32(val, addr);
पूर्ण

अटल अचिन्हित पूर्णांक समयr_पढ़ो32(व्योम __iomem *addr)
अणु
	वापस ioपढ़ो32(addr);
पूर्ण

अटल व्योम समयr_ग_लिखो32_be(u32 val, व्योम __iomem *addr)
अणु
	ioग_लिखो32be(val, addr);
पूर्ण

अटल अचिन्हित पूर्णांक समयr_पढ़ो32_be(व्योम __iomem *addr)
अणु
	वापस ioपढ़ो32be(addr);
पूर्ण

अटल अंतरभूत व्योम xilinx_समयr0_stop(व्योम)
अणु
	ग_लिखो_fn(पढ़ो_fn(समयr_baseaddr + TCSR0) & ~TCSR_ENT,
		 समयr_baseaddr + TCSR0);
पूर्ण

अटल अंतरभूत व्योम xilinx_समयr0_start_periodic(अचिन्हित दीर्घ load_val)
अणु
	अगर (!load_val)
		load_val = 1;
	/* loading value to समयr reg */
	ग_लिखो_fn(load_val, समयr_baseaddr + TLR0);

	/* load the initial value */
	ग_लिखो_fn(TCSR_LOAD, समयr_baseaddr + TCSR0);

	/* see समयr data sheet क्रम detail
	 * !ENALL - करोn't enable 'em all
	 * !PWMA - disable pwm
	 * TINT - clear पूर्णांकerrupt status
	 * ENT- enable समयr itself
	 * ENIT - enable पूर्णांकerrupt
	 * !LOAD - clear the bit to let go
	 * ARHT - स्वतः reload
	 * !CAPT - no बाह्यal trigger
	 * !GENT - no बाह्यal संकेत
	 * UDT - set the समयr as करोwn counter
	 * !MDT0 - generate mode
	 */
	ग_लिखो_fn(TCSR_TINT|TCSR_ENIT|TCSR_ENT|TCSR_ARHT|TCSR_UDT,
		 समयr_baseaddr + TCSR0);
पूर्ण

अटल अंतरभूत व्योम xilinx_समयr0_start_oneshot(अचिन्हित दीर्घ load_val)
अणु
	अगर (!load_val)
		load_val = 1;
	/* loading value to समयr reg */
	ग_लिखो_fn(load_val, समयr_baseaddr + TLR0);

	/* load the initial value */
	ग_लिखो_fn(TCSR_LOAD, समयr_baseaddr + TCSR0);

	ग_लिखो_fn(TCSR_TINT|TCSR_ENIT|TCSR_ENT|TCSR_ARHT|TCSR_UDT,
		 समयr_baseaddr + TCSR0);
पूर्ण

अटल पूर्णांक xilinx_समयr_set_next_event(अचिन्हित दीर्घ delta,
					काष्ठा घड़ी_event_device *dev)
अणु
	pr_debug("%s: next event, delta %x\n", __func__, (u32)delta);
	xilinx_समयr0_start_oneshot(delta);
	वापस 0;
पूर्ण

अटल पूर्णांक xilinx_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	pr_info("%s\n", __func__);
	xilinx_समयr0_stop();
	वापस 0;
पूर्ण

अटल पूर्णांक xilinx_समयr_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	pr_info("%s\n", __func__);
	xilinx_समयr0_start_periodic(freq_भाग_hz);
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device घड़ीevent_xilinx_समयr = अणु
	.name			= "xilinx_clockevent",
	.features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_PERIODIC,
	.shअगरt			= 8,
	.rating			= 300,
	.set_next_event		= xilinx_समयr_set_next_event,
	.set_state_shutकरोwn	= xilinx_समयr_shutकरोwn,
	.set_state_periodic	= xilinx_समयr_set_periodic,
पूर्ण;

अटल अंतरभूत व्योम समयr_ack(व्योम)
अणु
	ग_लिखो_fn(पढ़ो_fn(समयr_baseaddr + TCSR0), समयr_baseaddr + TCSR0);
पूर्ण

अटल irqवापस_t समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = &घड़ीevent_xilinx_समयr;
	समयr_ack();
	evt->event_handler(evt);
	वापस IRQ_HANDLED;
पूर्ण

अटल __init पूर्णांक xilinx_घड़ीevent_init(व्योम)
अणु
	घड़ीevent_xilinx_समयr.mult =
		भाग_sc(समयr_घड़ी_freq, NSEC_PER_SEC,
				घड़ीevent_xilinx_समयr.shअगरt);
	घड़ीevent_xilinx_समयr.max_delta_ns =
		घड़ीevent_delta2ns((u32)~0, &घड़ीevent_xilinx_समयr);
	घड़ीevent_xilinx_समयr.max_delta_ticks = (u32)~0;
	घड़ीevent_xilinx_समयr.min_delta_ns =
		घड़ीevent_delta2ns(1, &घड़ीevent_xilinx_समयr);
	घड़ीevent_xilinx_समयr.min_delta_ticks = 1;
	घड़ीevent_xilinx_समयr.cpumask = cpumask_of(0);
	घड़ीevents_रेजिस्टर_device(&घड़ीevent_xilinx_समयr);

	वापस 0;
पूर्ण

अटल u64 xilinx_घड़ी_पढ़ो(व्योम)
अणु
	वापस पढ़ो_fn(समयr_baseaddr + TCR1);
पूर्ण

अटल u64 xilinx_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	/* पढ़ोing actual value of समयr 1 */
	वापस (u64)xilinx_घड़ी_पढ़ो();
पूर्ण

अटल काष्ठा समयcounter xilinx_tc = अणु
	.cc = शून्य,
पूर्ण;

अटल u64 xilinx_cc_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	वापस xilinx_पढ़ो(शून्य);
पूर्ण

अटल काष्ठा cyclecounter xilinx_cc = अणु
	.पढ़ो = xilinx_cc_पढ़ो,
	.mask = CLOCKSOURCE_MASK(32),
	.shअगरt = 8,
पूर्ण;

अटल पूर्णांक __init init_xilinx_समयcounter(व्योम)
अणु
	xilinx_cc.mult = भाग_sc(समयr_घड़ी_freq, NSEC_PER_SEC,
				xilinx_cc.shअगरt);

	समयcounter_init(&xilinx_tc, &xilinx_cc, sched_घड़ी());

	वापस 0;
पूर्ण

अटल काष्ठा घड़ीsource घड़ीsource_microblaze = अणु
	.name		= "xilinx_clocksource",
	.rating		= 300,
	.पढ़ो		= xilinx_पढ़ो,
	.mask		= CLOCKSOURCE_MASK(32),
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल पूर्णांक __init xilinx_घड़ीsource_init(व्योम)
अणु
	पूर्णांक ret;

	ret = घड़ीsource_रेजिस्टर_hz(&घड़ीsource_microblaze,
				      समयr_घड़ी_freq);
	अगर (ret) अणु
		pr_err("failed to register clocksource");
		वापस ret;
	पूर्ण

	/* stop समयr1 */
	ग_लिखो_fn(पढ़ो_fn(समयr_baseaddr + TCSR1) & ~TCSR_ENT,
		 समयr_baseaddr + TCSR1);
	/* start समयr1 - up counting without पूर्णांकerrupt */
	ग_लिखो_fn(TCSR_TINT|TCSR_ENT|TCSR_ARHT, समयr_baseaddr + TCSR1);

	/* रेजिस्टर समयcounter - क्रम ftrace support */
	वापस init_xilinx_समयcounter();
पूर्ण

अटल पूर्णांक __init xilinx_समयr_init(काष्ठा device_node *समयr)
अणु
	काष्ठा clk *clk;
	अटल पूर्णांक initialized;
	u32 irq;
	u32 समयr_num = 1;
	पूर्णांक ret;

	अगर (initialized)
		वापस -EINVAL;

	initialized = 1;

	समयr_baseaddr = of_iomap(समयr, 0);
	अगर (!समयr_baseaddr) अणु
		pr_err("ERROR: invalid timer base address\n");
		वापस -ENXIO;
	पूर्ण

	ग_लिखो_fn = समयr_ग_लिखो32;
	पढ़ो_fn = समयr_पढ़ो32;

	ग_लिखो_fn(TCSR_MDT, समयr_baseaddr + TCSR0);
	अगर (!(पढ़ो_fn(समयr_baseaddr + TCSR0) & TCSR_MDT)) अणु
		ग_लिखो_fn = समयr_ग_लिखो32_be;
		पढ़ो_fn = समयr_पढ़ो32_be;
	पूर्ण

	irq = irq_of_parse_and_map(समयr, 0);
	अगर (irq <= 0) अणु
		pr_err("Failed to parse and map irq");
		वापस -EINVAL;
	पूर्ण

	of_property_पढ़ो_u32(समयr, "xlnx,one-timer-only", &समयr_num);
	अगर (समयr_num) अणु
		pr_err("Please enable two timers in HW\n");
		वापस -EINVAL;
	पूर्ण

	pr_info("%pOF: irq=%d\n", समयr, irq);

	clk = of_clk_get(समयr, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("ERROR: timer CCF input clock not found\n");
		/* If there is घड़ी-frequency property than use it */
		of_property_पढ़ो_u32(समयr, "clock-frequency",
				    &समयr_घड़ी_freq);
	पूर्ण अन्यथा अणु
		समयr_घड़ी_freq = clk_get_rate(clk);
	पूर्ण

	अगर (!समयr_घड़ी_freq) अणु
		pr_err("ERROR: Using CPU clock frequency\n");
		समयr_घड़ी_freq = cpuinfo.cpu_घड़ी_freq;
	पूर्ण

	freq_भाग_hz = समयr_घड़ी_freq / HZ;

	ret = request_irq(irq, समयr_पूर्णांकerrupt, IRQF_TIMER, "timer",
			  &घड़ीevent_xilinx_समयr);
	अगर (ret) अणु
		pr_err("Failed to setup IRQ");
		वापस ret;
	पूर्ण

	ret = xilinx_घड़ीsource_init();
	अगर (ret)
		वापस ret;

	ret = xilinx_घड़ीevent_init();
	अगर (ret)
		वापस ret;

	sched_घड़ी_रेजिस्टर(xilinx_घड़ी_पढ़ो, 32, समयr_घड़ी_freq);

	वापस 0;
पूर्ण

TIMER_OF_DECLARE(xilinx_समयr, "xlnx,xps-timer-1.00.a",
		       xilinx_समयr_init);
