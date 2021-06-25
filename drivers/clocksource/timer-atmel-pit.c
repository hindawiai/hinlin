<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * at91sam926x_समय.c - Periodic Interval Timer (PIT) क्रम at91sam926x
 *
 * Copyright (C) 2005-2006 M. Amine SAYA, ATMEL Rousset, France
 * Revision	 2005 M. Nicolas Diremdjian, ATMEL Rousset, France
 * Converted to ClockSource/ClockEvents by David Brownell.
 */

#घोषणा pr_fmt(fmt)	"AT91: PIT: " fmt

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/slab.h>

#घोषणा AT91_PIT_MR		0x00			/* Mode Register */
#घोषणा AT91_PIT_PITIEN			BIT(25)			/* Timer Interrupt Enable */
#घोषणा AT91_PIT_PITEN			BIT(24)			/* Timer Enabled */
#घोषणा AT91_PIT_PIV			GENMASK(19, 0)		/* Periodic Interval Value */

#घोषणा AT91_PIT_SR		0x04			/* Status Register */
#घोषणा AT91_PIT_PITS			BIT(0)			/* Timer Status */

#घोषणा AT91_PIT_PIVR		0x08			/* Periodic Interval Value Register */
#घोषणा AT91_PIT_PIIR		0x0c			/* Periodic Interval Image Register */
#घोषणा AT91_PIT_PICNT			GENMASK(31, 20)		/* Interval Counter */
#घोषणा AT91_PIT_CPIV			GENMASK(19, 0)		/* Inverval Value */

#घोषणा PIT_CPIV(x)	((x) & AT91_PIT_CPIV)
#घोषणा PIT_PICNT(x)	(((x) & AT91_PIT_PICNT) >> 20)

काष्ठा pit_data अणु
	काष्ठा घड़ी_event_device	clkevt;
	काष्ठा घड़ीsource		clksrc;

	व्योम __iomem	*base;
	u32		cycle;
	u32		cnt;
	अचिन्हित पूर्णांक	irq;
	काष्ठा clk	*mck;
पूर्ण;

अटल अंतरभूत काष्ठा pit_data *clksrc_to_pit_data(काष्ठा घड़ीsource *clksrc)
अणु
	वापस container_of(clksrc, काष्ठा pit_data, clksrc);
पूर्ण

अटल अंतरभूत काष्ठा pit_data *clkevt_to_pit_data(काष्ठा घड़ी_event_device *clkevt)
अणु
	वापस container_of(clkevt, काष्ठा pit_data, clkevt);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक pit_पढ़ो(व्योम __iomem *base, अचिन्हित पूर्णांक reg_offset)
अणु
	वापस पढ़ोl_relaxed(base + reg_offset);
पूर्ण

अटल अंतरभूत व्योम pit_ग_लिखो(व्योम __iomem *base, अचिन्हित पूर्णांक reg_offset, अचिन्हित दीर्घ value)
अणु
	ग_लिखोl_relaxed(value, base + reg_offset);
पूर्ण

/*
 * Clocksource:  just a monotonic counter of MCK/16 cycles.
 * We करोn't care whether or not PIT irqs are enabled.
 */
अटल u64 पढ़ो_pit_clk(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा pit_data *data = clksrc_to_pit_data(cs);
	अचिन्हित दीर्घ flags;
	u32 elapsed;
	u32 t;

	raw_local_irq_save(flags);
	elapsed = data->cnt;
	t = pit_पढ़ो(data->base, AT91_PIT_PIIR);
	raw_local_irq_restore(flags);

	elapsed += PIT_PICNT(t) * data->cycle;
	elapsed += PIT_CPIV(t);
	वापस elapsed;
पूर्ण

अटल पूर्णांक pit_clkevt_shutकरोwn(काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा pit_data *data = clkevt_to_pit_data(dev);

	/* disable irq, leaving the घड़ीsource active */
	pit_ग_लिखो(data->base, AT91_PIT_MR, (data->cycle - 1) | AT91_PIT_PITEN);
	वापस 0;
पूर्ण

/*
 * Clockevent device:  पूर्णांकerrupts every 1/HZ (== pit_cycles * MCK/16)
 */
अटल पूर्णांक pit_clkevt_set_periodic(काष्ठा घड़ी_event_device *dev)
अणु
	काष्ठा pit_data *data = clkevt_to_pit_data(dev);

	/* update घड़ीsource counter */
	data->cnt += data->cycle * PIT_PICNT(pit_पढ़ो(data->base, AT91_PIT_PIVR));
	pit_ग_लिखो(data->base, AT91_PIT_MR,
		  (data->cycle - 1) | AT91_PIT_PITEN | AT91_PIT_PITIEN);
	वापस 0;
पूर्ण

अटल व्योम at91sam926x_pit_suspend(काष्ठा घड़ी_event_device *cedev)
अणु
	काष्ठा pit_data *data = clkevt_to_pit_data(cedev);

	/* Disable समयr */
	pit_ग_लिखो(data->base, AT91_PIT_MR, 0);
पूर्ण

अटल व्योम at91sam926x_pit_reset(काष्ठा pit_data *data)
अणु
	/* Disable समयr and irqs */
	pit_ग_लिखो(data->base, AT91_PIT_MR, 0);

	/* Clear any pending पूर्णांकerrupts, रुको क्रम PIT to stop counting */
	जबतक (PIT_CPIV(pit_पढ़ो(data->base, AT91_PIT_PIVR)) != 0)
		cpu_relax();

	/* Start PIT but करोn't enable IRQ */
	pit_ग_लिखो(data->base, AT91_PIT_MR,
		  (data->cycle - 1) | AT91_PIT_PITEN);
पूर्ण

अटल व्योम at91sam926x_pit_resume(काष्ठा घड़ी_event_device *cedev)
अणु
	काष्ठा pit_data *data = clkevt_to_pit_data(cedev);

	at91sam926x_pit_reset(data);
पूर्ण

/*
 * IRQ handler क्रम the समयr.
 */
अटल irqवापस_t at91sam926x_pit_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pit_data *data = dev_id;

	/* The PIT पूर्णांकerrupt may be disabled, and is shared */
	अगर (घड़ीevent_state_periodic(&data->clkevt) &&
	    (pit_पढ़ो(data->base, AT91_PIT_SR) & AT91_PIT_PITS)) अणु
		/* Get number of ticks perक्रमmed beक्रमe irq, and ack it */
		data->cnt += data->cycle * PIT_PICNT(pit_पढ़ो(data->base,
							      AT91_PIT_PIVR));
		data->clkevt.event_handler(&data->clkevt);

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

/*
 * Set up both घड़ीsource and घड़ीevent support.
 */
अटल पूर्णांक __init at91sam926x_pit_dt_init(काष्ठा device_node *node)
अणु
	अचिन्हित दीर्घ   pit_rate;
	अचिन्हित        bits;
	पूर्णांक             ret;
	काष्ठा pit_data *data;

	data = kzalloc(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->base = of_iomap(node, 0);
	अगर (!data->base) अणु
		pr_err("Could not map PIT address\n");
		ret = -ENXIO;
		जाओ निकास;
	पूर्ण

	data->mck = of_clk_get(node, 0);
	अगर (IS_ERR(data->mck)) अणु
		pr_err("Unable to get mck clk\n");
		ret = PTR_ERR(data->mck);
		जाओ निकास;
	पूर्ण

	ret = clk_prepare_enable(data->mck);
	अगर (ret) अणु
		pr_err("Unable to enable mck\n");
		जाओ निकास;
	पूर्ण

	/* Get the पूर्णांकerrupts property */
	data->irq = irq_of_parse_and_map(node, 0);
	अगर (!data->irq) अणु
		pr_err("Unable to get IRQ from DT\n");
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	/*
	 * Use our actual MCK to figure out how many MCK/16 ticks per
	 * 1/HZ period (instead of a compile-समय स्थिरant LATCH).
	 */
	pit_rate = clk_get_rate(data->mck) / 16;
	data->cycle = DIV_ROUND_CLOSEST(pit_rate, HZ);
	WARN_ON(((data->cycle - 1) & ~AT91_PIT_PIV) != 0);

	/* Initialize and enable the समयr */
	at91sam926x_pit_reset(data);

	/*
	 * Register घड़ीsource.  The high order bits of PIV are unused,
	 * so this isn't a 32-bit counter unless we get घड़ीevent irqs.
	 */
	bits = 12 /* PICNT */ + ilog2(data->cycle) /* PIV */;
	data->clksrc.mask = CLOCKSOURCE_MASK(bits);
	data->clksrc.name = "pit";
	data->clksrc.rating = 175;
	data->clksrc.पढ़ो = पढ़ो_pit_clk;
	data->clksrc.flags = CLOCK_SOURCE_IS_CONTINUOUS;
	
	ret = घड़ीsource_रेजिस्टर_hz(&data->clksrc, pit_rate);
	अगर (ret) अणु
		pr_err("Failed to register clocksource\n");
		जाओ निकास;
	पूर्ण

	/* Set up irq handler */
	ret = request_irq(data->irq, at91sam926x_pit_पूर्णांकerrupt,
			  IRQF_SHARED | IRQF_TIMER | IRQF_IRQPOLL,
			  "at91_tick", data);
	अगर (ret) अणु
		pr_err("Unable to setup IRQ\n");
		घड़ीsource_unरेजिस्टर(&data->clksrc);
		जाओ निकास;
	पूर्ण

	/* Set up and रेजिस्टर घड़ीevents */
	data->clkevt.name = "pit";
	data->clkevt.features = CLOCK_EVT_FEAT_PERIODIC;
	data->clkevt.shअगरt = 32;
	data->clkevt.mult = भाग_sc(pit_rate, NSEC_PER_SEC, data->clkevt.shअगरt);
	data->clkevt.rating = 100;
	data->clkevt.cpumask = cpumask_of(0);

	data->clkevt.set_state_shutकरोwn = pit_clkevt_shutकरोwn;
	data->clkevt.set_state_periodic = pit_clkevt_set_periodic;
	data->clkevt.resume = at91sam926x_pit_resume;
	data->clkevt.suspend = at91sam926x_pit_suspend;
	घड़ीevents_रेजिस्टर_device(&data->clkevt);

	वापस 0;

निकास:
	kमुक्त(data);
	वापस ret;
पूर्ण
TIMER_OF_DECLARE(at91sam926x_pit, "atmel,at91sam9260-pit",
		       at91sam926x_pit_dt_init);
