<शैली गुरु>
/*
 * Copyright (C) 2013-2014 Altera Corporation
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#घोषणा ALTR_TIMER_COMPATIBLE		"altr,timer-1.0"

#घोषणा ALTERA_TIMER_STATUS_REG	0
#घोषणा ALTERA_TIMER_CONTROL_REG	4
#घोषणा ALTERA_TIMER_PERIODL_REG	8
#घोषणा ALTERA_TIMER_PERIODH_REG	12
#घोषणा ALTERA_TIMER_SNAPL_REG		16
#घोषणा ALTERA_TIMER_SNAPH_REG		20

#घोषणा ALTERA_TIMER_CONTROL_ITO_MSK	(0x1)
#घोषणा ALTERA_TIMER_CONTROL_CONT_MSK	(0x2)
#घोषणा ALTERA_TIMER_CONTROL_START_MSK	(0x4)
#घोषणा ALTERA_TIMER_CONTROL_STOP_MSK	(0x8)

काष्ठा nios2_समयr अणु
	व्योम __iomem *base;
	अचिन्हित दीर्घ freq;
पूर्ण;

काष्ठा nios2_घड़ीevent_dev अणु
	काष्ठा nios2_समयr समयr;
	काष्ठा घड़ी_event_device ced;
पूर्ण;

काष्ठा nios2_घड़ीsource अणु
	काष्ठा nios2_समयr समयr;
	काष्ठा घड़ीsource cs;
पूर्ण;

अटल अंतरभूत काष्ठा nios2_घड़ीevent_dev *
	to_nios2_clkevent(काष्ठा घड़ी_event_device *evt)
अणु
	वापस container_of(evt, काष्ठा nios2_घड़ीevent_dev, ced);
पूर्ण

अटल अंतरभूत काष्ठा nios2_घड़ीsource *
	to_nios2_clksource(काष्ठा घड़ीsource *cs)
अणु
	वापस container_of(cs, काष्ठा nios2_घड़ीsource, cs);
पूर्ण

अटल u16 समयr_पढ़ोw(काष्ठा nios2_समयr *समयr, u32 offs)
अणु
	वापस पढ़ोw(समयr->base + offs);
पूर्ण

अटल व्योम समयr_ग_लिखोw(काष्ठा nios2_समयr *समयr, u16 val, u32 offs)
अणु
	ग_लिखोw(val, समयr->base + offs);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ पढ़ो_समयrsnapshot(काष्ठा nios2_समयr *समयr)
अणु
	अचिन्हित दीर्घ count;

	समयr_ग_लिखोw(समयr, 0, ALTERA_TIMER_SNAPL_REG);
	count = समयr_पढ़ोw(समयr, ALTERA_TIMER_SNAPH_REG) << 16 |
		समयr_पढ़ोw(समयr, ALTERA_TIMER_SNAPL_REG);

	वापस count;
पूर्ण

अटल u64 nios2_समयr_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा nios2_घड़ीsource *nios2_cs = to_nios2_clksource(cs);
	अचिन्हित दीर्घ flags;
	u32 count;

	local_irq_save(flags);
	count = पढ़ो_समयrsnapshot(&nios2_cs->समयr);
	local_irq_restore(flags);

	/* Counter is counting करोwn */
	वापस ~count;
पूर्ण

अटल काष्ठा nios2_घड़ीsource nios2_cs = अणु
	.cs = अणु
		.name	= "nios2-clksrc",
		.rating	= 250,
		.पढ़ो	= nios2_समयr_पढ़ो,
		.mask	= CLOCKSOURCE_MASK(32),
		.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
	पूर्ण,
पूर्ण;

cycles_t get_cycles(व्योम)
अणु
	/* Only पढ़ो समयr अगर it has been initialized */
	अगर (nios2_cs.समयr.base)
		वापस nios2_समयr_पढ़ो(&nios2_cs.cs);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(get_cycles);

अटल व्योम nios2_समयr_start(काष्ठा nios2_समयr *समयr)
अणु
	u16 ctrl;

	ctrl = समयr_पढ़ोw(समयr, ALTERA_TIMER_CONTROL_REG);
	ctrl |= ALTERA_TIMER_CONTROL_START_MSK;
	समयr_ग_लिखोw(समयr, ctrl, ALTERA_TIMER_CONTROL_REG);
पूर्ण

अटल व्योम nios2_समयr_stop(काष्ठा nios2_समयr *समयr)
अणु
	u16 ctrl;

	ctrl = समयr_पढ़ोw(समयr, ALTERA_TIMER_CONTROL_REG);
	ctrl |= ALTERA_TIMER_CONTROL_STOP_MSK;
	समयr_ग_लिखोw(समयr, ctrl, ALTERA_TIMER_CONTROL_REG);
पूर्ण

अटल व्योम nios2_समयr_config(काष्ठा nios2_समयr *समयr, अचिन्हित दीर्घ period,
			       bool periodic)
अणु
	u16 ctrl;

	/* The समयr's actual period is one cycle greater than the value
	 * stored in the period रेजिस्टर. */
	 period--;

	ctrl = समयr_पढ़ोw(समयr, ALTERA_TIMER_CONTROL_REG);
	/* stop counter */
	समयr_ग_लिखोw(समयr, ctrl | ALTERA_TIMER_CONTROL_STOP_MSK,
		ALTERA_TIMER_CONTROL_REG);

	/* ग_लिखो new count */
	समयr_ग_लिखोw(समयr, period, ALTERA_TIMER_PERIODL_REG);
	समयr_ग_लिखोw(समयr, period >> 16, ALTERA_TIMER_PERIODH_REG);

	ctrl |= ALTERA_TIMER_CONTROL_START_MSK | ALTERA_TIMER_CONTROL_ITO_MSK;
	अगर (periodic)
		ctrl |= ALTERA_TIMER_CONTROL_CONT_MSK;
	अन्यथा
		ctrl &= ~ALTERA_TIMER_CONTROL_CONT_MSK;
	समयr_ग_लिखोw(समयr, ctrl, ALTERA_TIMER_CONTROL_REG);
पूर्ण

अटल पूर्णांक nios2_समयr_set_next_event(अचिन्हित दीर्घ delta,
	काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा nios2_घड़ीevent_dev *nios2_ced = to_nios2_clkevent(evt);

	nios2_समयr_config(&nios2_ced->समयr, delta, false);

	वापस 0;
पूर्ण

अटल पूर्णांक nios2_समयr_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा nios2_घड़ीevent_dev *nios2_ced = to_nios2_clkevent(evt);
	काष्ठा nios2_समयr *समयr = &nios2_ced->समयr;

	nios2_समयr_stop(समयr);
	वापस 0;
पूर्ण

अटल पूर्णांक nios2_समयr_set_periodic(काष्ठा घड़ी_event_device *evt)
अणु
	अचिन्हित दीर्घ period;
	काष्ठा nios2_घड़ीevent_dev *nios2_ced = to_nios2_clkevent(evt);
	काष्ठा nios2_समयr *समयr = &nios2_ced->समयr;

	period = DIV_ROUND_UP(समयr->freq, HZ);
	nios2_समयr_config(समयr, period, true);
	वापस 0;
पूर्ण

अटल पूर्णांक nios2_समयr_resume(काष्ठा घड़ी_event_device *evt)
अणु
	काष्ठा nios2_घड़ीevent_dev *nios2_ced = to_nios2_clkevent(evt);
	काष्ठा nios2_समयr *समयr = &nios2_ced->समयr;

	nios2_समयr_start(समयr);
	वापस 0;
पूर्ण

irqवापस_t समयr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *evt = (काष्ठा घड़ी_event_device *) dev_id;
	काष्ठा nios2_घड़ीevent_dev *nios2_ced = to_nios2_clkevent(evt);

	/* Clear the पूर्णांकerrupt condition */
	समयr_ग_लिखोw(&nios2_ced->समयr, 0, ALTERA_TIMER_STATUS_REG);
	evt->event_handler(evt);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init nios2_समयr_get_base_and_freq(काष्ठा device_node *np,
				व्योम __iomem **base, u32 *freq)
अणु
	*base = of_iomap(np, 0);
	अगर (!*base) अणु
		pr_crit("Unable to map reg for %pOFn\n", np);
		वापस -ENXIO;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "clock-frequency", freq)) अणु
		pr_crit("Unable to get %pOFn clock frequency\n", np);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा nios2_घड़ीevent_dev nios2_ce = अणु
	.ced = अणु
		.name = "nios2-clkevent",
		.features = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
		.rating = 250,
		.shअगरt = 32,
		.set_next_event = nios2_समयr_set_next_event,
		.set_state_shutकरोwn = nios2_समयr_shutकरोwn,
		.set_state_periodic = nios2_समयr_set_periodic,
		.set_state_oneshot = nios2_समयr_shutकरोwn,
		.tick_resume = nios2_समयr_resume,
	पूर्ण,
पूर्ण;

अटल __init पूर्णांक nios2_घड़ीevent_init(काष्ठा device_node *समयr)
अणु
	व्योम __iomem *iobase;
	u32 freq;
	पूर्णांक irq, ret;

	ret = nios2_समयr_get_base_and_freq(समयr, &iobase, &freq);
	अगर (ret)
		वापस ret;

	irq = irq_of_parse_and_map(समयr, 0);
	अगर (!irq) अणु
		pr_crit("Unable to parse timer irq\n");
		वापस -EINVAL;
	पूर्ण

	nios2_ce.समयr.base = iobase;
	nios2_ce.समयr.freq = freq;

	nios2_ce.ced.cpumask = cpumask_of(0);
	nios2_ce.ced.irq = irq;

	nios2_समयr_stop(&nios2_ce.समयr);
	/* clear pending पूर्णांकerrupt */
	समयr_ग_लिखोw(&nios2_ce.समयr, 0, ALTERA_TIMER_STATUS_REG);

	ret = request_irq(irq, समयr_पूर्णांकerrupt, IRQF_TIMER, समयr->name,
			  &nios2_ce.ced);
	अगर (ret) अणु
		pr_crit("Unable to setup timer irq\n");
		वापस ret;
	पूर्ण

	घड़ीevents_config_and_रेजिस्टर(&nios2_ce.ced, freq, 1, अच_दीर्घ_उच्च);

	वापस 0;
पूर्ण

अटल __init पूर्णांक nios2_घड़ीsource_init(काष्ठा device_node *समयr)
अणु
	अचिन्हित पूर्णांक ctrl;
	व्योम __iomem *iobase;
	u32 freq;
	पूर्णांक ret;

	ret = nios2_समयr_get_base_and_freq(समयr, &iobase, &freq);
	अगर (ret)
		वापस ret;

	nios2_cs.समयr.base = iobase;
	nios2_cs.समयr.freq = freq;

	ret = घड़ीsource_रेजिस्टर_hz(&nios2_cs.cs, freq);
	अगर (ret)
		वापस ret;

	समयr_ग_लिखोw(&nios2_cs.समयr, अच_लघु_उच्च, ALTERA_TIMER_PERIODL_REG);
	समयr_ग_लिखोw(&nios2_cs.समयr, अच_लघु_उच्च, ALTERA_TIMER_PERIODH_REG);

	/* पूर्णांकerrupt disable + continuous + start */
	ctrl = ALTERA_TIMER_CONTROL_CONT_MSK | ALTERA_TIMER_CONTROL_START_MSK;
	समयr_ग_लिखोw(&nios2_cs.समयr, ctrl, ALTERA_TIMER_CONTROL_REG);

	/* Calibrate the delay loop directly */
	lpj_fine = freq / HZ;

	वापस 0;
पूर्ण

/*
 * The first समयr instance will use as a घड़ीevent. If there are two or
 * more instances, the second one माला_लो used as घड़ीsource and all
 * others are unused.
*/
अटल पूर्णांक __init nios2_समय_init(काष्ठा device_node *समयr)
अणु
	अटल पूर्णांक num_called;
	पूर्णांक ret;

	चयन (num_called) अणु
	हाल 0:
		ret = nios2_घड़ीevent_init(समयr);
		अवरोध;
	हाल 1:
		ret = nios2_घड़ीsource_init(समयr);
		अवरोध;
	शेष:
		ret = 0;
		अवरोध;
	पूर्ण

	num_called++;

	वापस ret;
पूर्ण

व्योम पढ़ो_persistent_घड़ी64(काष्ठा बारpec64 *ts)
अणु
	ts->tv_sec = स_गढ़ो64(2007, 1, 1, 0, 0, 0);
	ts->tv_nsec = 0;
पूर्ण

व्योम __init समय_init(व्योम)
अणु
	काष्ठा device_node *np;
	पूर्णांक count = 0;

	क्रम_each_compatible_node(np, शून्य,  ALTR_TIMER_COMPATIBLE)
		count++;

	अगर (count < 2)
		panic("%d timer is found, it needs 2 timers in system\n", count);

	समयr_probe();
पूर्ण

TIMER_OF_DECLARE(nios2_समयr, ALTR_TIMER_COMPATIBLE, nios2_समय_init);
