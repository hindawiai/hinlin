<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SuperH Timer Support - TMU
 *
 *  Copyright (C) 2009 Magnus Damm
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sh_समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#अगर_घोषित CONFIG_SUPERH
#समावेश <यंत्र/platक्रमm_early.h>
#पूर्ण_अगर

क्रमागत sh_पंचांगu_model अणु
	SH_TMU,
	SH_TMU_SH3,
पूर्ण;

काष्ठा sh_पंचांगu_device;

काष्ठा sh_पंचांगu_channel अणु
	काष्ठा sh_पंचांगu_device *पंचांगu;
	अचिन्हित पूर्णांक index;

	व्योम __iomem *base;
	पूर्णांक irq;

	अचिन्हित दीर्घ periodic;
	काष्ठा घड़ी_event_device ced;
	काष्ठा घड़ीsource cs;
	bool cs_enabled;
	अचिन्हित पूर्णांक enable_count;
पूर्ण;

काष्ठा sh_पंचांगu_device अणु
	काष्ठा platक्रमm_device *pdev;

	व्योम __iomem *mapbase;
	काष्ठा clk *clk;
	अचिन्हित दीर्घ rate;

	क्रमागत sh_पंचांगu_model model;

	raw_spinlock_t lock; /* Protect the shared start/stop रेजिस्टर */

	काष्ठा sh_पंचांगu_channel *channels;
	अचिन्हित पूर्णांक num_channels;

	bool has_घड़ीevent;
	bool has_घड़ीsource;
पूर्ण;

#घोषणा TSTR -1 /* shared रेजिस्टर */
#घोषणा TCOR  0 /* channel रेजिस्टर */
#घोषणा TCNT 1 /* channel रेजिस्टर */
#घोषणा TCR 2 /* channel रेजिस्टर */

#घोषणा TCR_UNF			(1 << 8)
#घोषणा TCR_UNIE		(1 << 5)
#घोषणा TCR_TPSC_CLK4		(0 << 0)
#घोषणा TCR_TPSC_CLK16		(1 << 0)
#घोषणा TCR_TPSC_CLK64		(2 << 0)
#घोषणा TCR_TPSC_CLK256		(3 << 0)
#घोषणा TCR_TPSC_CLK1024	(4 << 0)
#घोषणा TCR_TPSC_MASK		(7 << 0)

अटल अंतरभूत अचिन्हित दीर्घ sh_पंचांगu_पढ़ो(काष्ठा sh_पंचांगu_channel *ch, पूर्णांक reg_nr)
अणु
	अचिन्हित दीर्घ offs;

	अगर (reg_nr == TSTR) अणु
		चयन (ch->पंचांगu->model) अणु
		हाल SH_TMU_SH3:
			वापस ioपढ़ो8(ch->पंचांगu->mapbase + 2);
		हाल SH_TMU:
			वापस ioपढ़ो8(ch->पंचांगu->mapbase + 4);
		पूर्ण
	पूर्ण

	offs = reg_nr << 2;

	अगर (reg_nr == TCR)
		वापस ioपढ़ो16(ch->base + offs);
	अन्यथा
		वापस ioपढ़ो32(ch->base + offs);
पूर्ण

अटल अंतरभूत व्योम sh_पंचांगu_ग_लिखो(काष्ठा sh_पंचांगu_channel *ch, पूर्णांक reg_nr,
				अचिन्हित दीर्घ value)
अणु
	अचिन्हित दीर्घ offs;

	अगर (reg_nr == TSTR) अणु
		चयन (ch->पंचांगu->model) अणु
		हाल SH_TMU_SH3:
			वापस ioग_लिखो8(value, ch->पंचांगu->mapbase + 2);
		हाल SH_TMU:
			वापस ioग_लिखो8(value, ch->पंचांगu->mapbase + 4);
		पूर्ण
	पूर्ण

	offs = reg_nr << 2;

	अगर (reg_nr == TCR)
		ioग_लिखो16(value, ch->base + offs);
	अन्यथा
		ioग_लिखो32(value, ch->base + offs);
पूर्ण

अटल व्योम sh_पंचांगu_start_stop_ch(काष्ठा sh_पंचांगu_channel *ch, पूर्णांक start)
अणु
	अचिन्हित दीर्घ flags, value;

	/* start stop रेजिस्टर shared by multiple समयr channels */
	raw_spin_lock_irqsave(&ch->पंचांगu->lock, flags);
	value = sh_पंचांगu_पढ़ो(ch, TSTR);

	अगर (start)
		value |= 1 << ch->index;
	अन्यथा
		value &= ~(1 << ch->index);

	sh_पंचांगu_ग_लिखो(ch, TSTR, value);
	raw_spin_unlock_irqrestore(&ch->पंचांगu->lock, flags);
पूर्ण

अटल पूर्णांक __sh_पंचांगu_enable(काष्ठा sh_पंचांगu_channel *ch)
अणु
	पूर्णांक ret;

	/* enable घड़ी */
	ret = clk_enable(ch->पंचांगu->clk);
	अगर (ret) अणु
		dev_err(&ch->पंचांगu->pdev->dev, "ch%u: cannot enable clock\n",
			ch->index);
		वापस ret;
	पूर्ण

	/* make sure channel is disabled */
	sh_पंचांगu_start_stop_ch(ch, 0);

	/* maximum समयout */
	sh_पंचांगu_ग_लिखो(ch, TCOR, 0xffffffff);
	sh_पंचांगu_ग_लिखो(ch, TCNT, 0xffffffff);

	/* configure channel to parent घड़ी / 4, irq off */
	sh_पंचांगu_ग_लिखो(ch, TCR, TCR_TPSC_CLK4);

	/* enable channel */
	sh_पंचांगu_start_stop_ch(ch, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_पंचांगu_enable(काष्ठा sh_पंचांगu_channel *ch)
अणु
	अगर (ch->enable_count++ > 0)
		वापस 0;

	pm_runसमय_get_sync(&ch->पंचांगu->pdev->dev);
	dev_pm_syscore_device(&ch->पंचांगu->pdev->dev, true);

	वापस __sh_पंचांगu_enable(ch);
पूर्ण

अटल व्योम __sh_पंचांगu_disable(काष्ठा sh_पंचांगu_channel *ch)
अणु
	/* disable channel */
	sh_पंचांगu_start_stop_ch(ch, 0);

	/* disable पूर्णांकerrupts in TMU block */
	sh_पंचांगu_ग_लिखो(ch, TCR, TCR_TPSC_CLK4);

	/* stop घड़ी */
	clk_disable(ch->पंचांगu->clk);
पूर्ण

अटल व्योम sh_पंचांगu_disable(काष्ठा sh_पंचांगu_channel *ch)
अणु
	अगर (WARN_ON(ch->enable_count == 0))
		वापस;

	अगर (--ch->enable_count > 0)
		वापस;

	__sh_पंचांगu_disable(ch);

	dev_pm_syscore_device(&ch->पंचांगu->pdev->dev, false);
	pm_runसमय_put(&ch->पंचांगu->pdev->dev);
पूर्ण

अटल व्योम sh_पंचांगu_set_next(काष्ठा sh_पंचांगu_channel *ch, अचिन्हित दीर्घ delta,
			    पूर्णांक periodic)
अणु
	/* stop समयr */
	sh_पंचांगu_start_stop_ch(ch, 0);

	/* acknowledge पूर्णांकerrupt */
	sh_पंचांगu_पढ़ो(ch, TCR);

	/* enable पूर्णांकerrupt */
	sh_पंचांगu_ग_लिखो(ch, TCR, TCR_UNIE | TCR_TPSC_CLK4);

	/* reload delta value in हाल of periodic समयr */
	अगर (periodic)
		sh_पंचांगu_ग_लिखो(ch, TCOR, delta);
	अन्यथा
		sh_पंचांगu_ग_लिखो(ch, TCOR, 0xffffffff);

	sh_पंचांगu_ग_लिखो(ch, TCNT, delta);

	/* start समयr */
	sh_पंचांगu_start_stop_ch(ch, 1);
पूर्ण

अटल irqवापस_t sh_पंचांगu_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sh_पंचांगu_channel *ch = dev_id;

	/* disable or acknowledge पूर्णांकerrupt */
	अगर (घड़ीevent_state_oneshot(&ch->ced))
		sh_पंचांगu_ग_लिखो(ch, TCR, TCR_TPSC_CLK4);
	अन्यथा
		sh_पंचांगu_ग_लिखो(ch, TCR, TCR_UNIE | TCR_TPSC_CLK4);

	/* notअगरy घड़ीevent layer */
	ch->ced.event_handler(&ch->ced);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा sh_पंचांगu_channel *cs_to_sh_पंचांगu(काष्ठा घड़ीsource *cs)
अणु
	वापस container_of(cs, काष्ठा sh_पंचांगu_channel, cs);
पूर्ण

अटल u64 sh_पंचांगu_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा sh_पंचांगu_channel *ch = cs_to_sh_पंचांगu(cs);

	वापस sh_पंचांगu_पढ़ो(ch, TCNT) ^ 0xffffffff;
पूर्ण

अटल पूर्णांक sh_पंचांगu_घड़ीsource_enable(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा sh_पंचांगu_channel *ch = cs_to_sh_पंचांगu(cs);
	पूर्णांक ret;

	अगर (WARN_ON(ch->cs_enabled))
		वापस 0;

	ret = sh_पंचांगu_enable(ch);
	अगर (!ret)
		ch->cs_enabled = true;

	वापस ret;
पूर्ण

अटल व्योम sh_पंचांगu_घड़ीsource_disable(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा sh_पंचांगu_channel *ch = cs_to_sh_पंचांगu(cs);

	अगर (WARN_ON(!ch->cs_enabled))
		वापस;

	sh_पंचांगu_disable(ch);
	ch->cs_enabled = false;
पूर्ण

अटल व्योम sh_पंचांगu_घड़ीsource_suspend(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा sh_पंचांगu_channel *ch = cs_to_sh_पंचांगu(cs);

	अगर (!ch->cs_enabled)
		वापस;

	अगर (--ch->enable_count == 0) अणु
		__sh_पंचांगu_disable(ch);
		dev_pm_genpd_suspend(&ch->पंचांगu->pdev->dev);
	पूर्ण
पूर्ण

अटल व्योम sh_पंचांगu_घड़ीsource_resume(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा sh_पंचांगu_channel *ch = cs_to_sh_पंचांगu(cs);

	अगर (!ch->cs_enabled)
		वापस;

	अगर (ch->enable_count++ == 0) अणु
		dev_pm_genpd_resume(&ch->पंचांगu->pdev->dev);
		__sh_पंचांगu_enable(ch);
	पूर्ण
पूर्ण

अटल पूर्णांक sh_पंचांगu_रेजिस्टर_घड़ीsource(काष्ठा sh_पंचांगu_channel *ch,
				       स्थिर अक्षर *name)
अणु
	काष्ठा घड़ीsource *cs = &ch->cs;

	cs->name = name;
	cs->rating = 200;
	cs->पढ़ो = sh_पंचांगu_घड़ीsource_पढ़ो;
	cs->enable = sh_पंचांगu_घड़ीsource_enable;
	cs->disable = sh_पंचांगu_घड़ीsource_disable;
	cs->suspend = sh_पंचांगu_घड़ीsource_suspend;
	cs->resume = sh_पंचांगu_घड़ीsource_resume;
	cs->mask = CLOCKSOURCE_MASK(32);
	cs->flags = CLOCK_SOURCE_IS_CONTINUOUS;

	dev_info(&ch->पंचांगu->pdev->dev, "ch%u: used as clock source\n",
		 ch->index);

	घड़ीsource_रेजिस्टर_hz(cs, ch->पंचांगu->rate);
	वापस 0;
पूर्ण

अटल काष्ठा sh_पंचांगu_channel *ced_to_sh_पंचांगu(काष्ठा घड़ी_event_device *ced)
अणु
	वापस container_of(ced, काष्ठा sh_पंचांगu_channel, ced);
पूर्ण

अटल व्योम sh_पंचांगu_घड़ी_event_start(काष्ठा sh_पंचांगu_channel *ch, पूर्णांक periodic)
अणु
	sh_पंचांगu_enable(ch);

	अगर (periodic) अणु
		ch->periodic = (ch->पंचांगu->rate + HZ/2) / HZ;
		sh_पंचांगu_set_next(ch, ch->periodic, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक sh_पंचांगu_घड़ी_event_shutकरोwn(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा sh_पंचांगu_channel *ch = ced_to_sh_पंचांगu(ced);

	अगर (घड़ीevent_state_oneshot(ced) || घड़ीevent_state_periodic(ced))
		sh_पंचांगu_disable(ch);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_पंचांगu_घड़ी_event_set_state(काष्ठा घड़ी_event_device *ced,
					पूर्णांक periodic)
अणु
	काष्ठा sh_पंचांगu_channel *ch = ced_to_sh_पंचांगu(ced);

	/* deal with old setting first */
	अगर (घड़ीevent_state_oneshot(ced) || घड़ीevent_state_periodic(ced))
		sh_पंचांगu_disable(ch);

	dev_info(&ch->पंचांगu->pdev->dev, "ch%u: used for %s clock events\n",
		 ch->index, periodic ? "periodic" : "oneshot");
	sh_पंचांगu_घड़ी_event_start(ch, periodic);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_पंचांगu_घड़ी_event_set_oneshot(काष्ठा घड़ी_event_device *ced)
अणु
	वापस sh_पंचांगu_घड़ी_event_set_state(ced, 0);
पूर्ण

अटल पूर्णांक sh_पंचांगu_घड़ी_event_set_periodic(काष्ठा घड़ी_event_device *ced)
अणु
	वापस sh_पंचांगu_घड़ी_event_set_state(ced, 1);
पूर्ण

अटल पूर्णांक sh_पंचांगu_घड़ी_event_next(अचिन्हित दीर्घ delta,
				   काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा sh_पंचांगu_channel *ch = ced_to_sh_पंचांगu(ced);

	BUG_ON(!घड़ीevent_state_oneshot(ced));

	/* program new delta value */
	sh_पंचांगu_set_next(ch, delta, 0);
	वापस 0;
पूर्ण

अटल व्योम sh_पंचांगu_घड़ी_event_suspend(काष्ठा घड़ी_event_device *ced)
अणु
	dev_pm_genpd_suspend(&ced_to_sh_पंचांगu(ced)->पंचांगu->pdev->dev);
पूर्ण

अटल व्योम sh_पंचांगu_घड़ी_event_resume(काष्ठा घड़ी_event_device *ced)
अणु
	dev_pm_genpd_resume(&ced_to_sh_पंचांगu(ced)->पंचांगu->pdev->dev);
पूर्ण

अटल व्योम sh_पंचांगu_रेजिस्टर_घड़ीevent(काष्ठा sh_पंचांगu_channel *ch,
				       स्थिर अक्षर *name)
अणु
	काष्ठा घड़ी_event_device *ced = &ch->ced;
	पूर्णांक ret;

	ced->name = name;
	ced->features = CLOCK_EVT_FEAT_PERIODIC;
	ced->features |= CLOCK_EVT_FEAT_ONESHOT;
	ced->rating = 200;
	ced->cpumask = cpu_possible_mask;
	ced->set_next_event = sh_पंचांगu_घड़ी_event_next;
	ced->set_state_shutकरोwn = sh_पंचांगu_घड़ी_event_shutकरोwn;
	ced->set_state_periodic = sh_पंचांगu_घड़ी_event_set_periodic;
	ced->set_state_oneshot = sh_पंचांगu_घड़ी_event_set_oneshot;
	ced->suspend = sh_पंचांगu_घड़ी_event_suspend;
	ced->resume = sh_पंचांगu_घड़ी_event_resume;

	dev_info(&ch->पंचांगu->pdev->dev, "ch%u: used for clock events\n",
		 ch->index);

	घड़ीevents_config_and_रेजिस्टर(ced, ch->पंचांगu->rate, 0x300, 0xffffffff);

	ret = request_irq(ch->irq, sh_पंचांगu_पूर्णांकerrupt,
			  IRQF_TIMER | IRQF_IRQPOLL | IRQF_NOBALANCING,
			  dev_name(&ch->पंचांगu->pdev->dev), ch);
	अगर (ret) अणु
		dev_err(&ch->पंचांगu->pdev->dev, "ch%u: failed to request irq %d\n",
			ch->index, ch->irq);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक sh_पंचांगu_रेजिस्टर(काष्ठा sh_पंचांगu_channel *ch, स्थिर अक्षर *name,
			   bool घड़ीevent, bool घड़ीsource)
अणु
	अगर (घड़ीevent) अणु
		ch->पंचांगu->has_घड़ीevent = true;
		sh_पंचांगu_रेजिस्टर_घड़ीevent(ch, name);
	पूर्ण अन्यथा अगर (घड़ीsource) अणु
		ch->पंचांगu->has_घड़ीsource = true;
		sh_पंचांगu_रेजिस्टर_घड़ीsource(ch, name);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sh_पंचांगu_channel_setup(काष्ठा sh_पंचांगu_channel *ch, अचिन्हित पूर्णांक index,
				bool घड़ीevent, bool घड़ीsource,
				काष्ठा sh_पंचांगu_device *पंचांगu)
अणु
	/* Skip unused channels. */
	अगर (!घड़ीevent && !घड़ीsource)
		वापस 0;

	ch->पंचांगu = पंचांगu;
	ch->index = index;

	अगर (पंचांगu->model == SH_TMU_SH3)
		ch->base = पंचांगu->mapbase + 4 + ch->index * 12;
	अन्यथा
		ch->base = पंचांगu->mapbase + 8 + ch->index * 12;

	ch->irq = platक्रमm_get_irq(पंचांगu->pdev, index);
	अगर (ch->irq < 0)
		वापस ch->irq;

	ch->cs_enabled = false;
	ch->enable_count = 0;

	वापस sh_पंचांगu_रेजिस्टर(ch, dev_name(&पंचांगu->pdev->dev),
			       घड़ीevent, घड़ीsource);
पूर्ण

अटल पूर्णांक sh_पंचांगu_map_memory(काष्ठा sh_पंचांगu_device *पंचांगu)
अणु
	काष्ठा resource *res;

	res = platक्रमm_get_resource(पंचांगu->pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&पंचांगu->pdev->dev, "failed to get I/O memory\n");
		वापस -ENXIO;
	पूर्ण

	पंचांगu->mapbase = ioremap(res->start, resource_size(res));
	अगर (पंचांगu->mapbase == शून्य)
		वापस -ENXIO;

	वापस 0;
पूर्ण

अटल पूर्णांक sh_पंचांगu_parse_dt(काष्ठा sh_पंचांगu_device *पंचांगu)
अणु
	काष्ठा device_node *np = पंचांगu->pdev->dev.of_node;

	पंचांगu->model = SH_TMU;
	पंचांगu->num_channels = 3;

	of_property_पढ़ो_u32(np, "#renesas,channels", &पंचांगu->num_channels);

	अगर (पंचांगu->num_channels != 2 && पंचांगu->num_channels != 3) अणु
		dev_err(&पंचांगu->pdev->dev, "invalid number of channels %u\n",
			पंचांगu->num_channels);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sh_पंचांगu_setup(काष्ठा sh_पंचांगu_device *पंचांगu, काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	पंचांगu->pdev = pdev;

	raw_spin_lock_init(&पंचांगu->lock);

	अगर (IS_ENABLED(CONFIG_OF) && pdev->dev.of_node) अणु
		ret = sh_पंचांगu_parse_dt(पंचांगu);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (pdev->dev.platक्रमm_data) अणु
		स्थिर काष्ठा platक्रमm_device_id *id = pdev->id_entry;
		काष्ठा sh_समयr_config *cfg = pdev->dev.platक्रमm_data;

		पंचांगu->model = id->driver_data;
		पंचांगu->num_channels = hweight8(cfg->channels_mask);
	पूर्ण अन्यथा अणु
		dev_err(&पंचांगu->pdev->dev, "missing platform data\n");
		वापस -ENXIO;
	पूर्ण

	/* Get hold of घड़ी. */
	पंचांगu->clk = clk_get(&पंचांगu->pdev->dev, "fck");
	अगर (IS_ERR(पंचांगu->clk)) अणु
		dev_err(&पंचांगu->pdev->dev, "cannot get clock\n");
		वापस PTR_ERR(पंचांगu->clk);
	पूर्ण

	ret = clk_prepare(पंचांगu->clk);
	अगर (ret < 0)
		जाओ err_clk_put;

	/* Determine घड़ी rate. */
	ret = clk_enable(पंचांगu->clk);
	अगर (ret < 0)
		जाओ err_clk_unprepare;

	पंचांगu->rate = clk_get_rate(पंचांगu->clk) / 4;
	clk_disable(पंचांगu->clk);

	/* Map the memory resource. */
	ret = sh_पंचांगu_map_memory(पंचांगu);
	अगर (ret < 0) अणु
		dev_err(&पंचांगu->pdev->dev, "failed to remap I/O memory\n");
		जाओ err_clk_unprepare;
	पूर्ण

	/* Allocate and setup the channels. */
	पंचांगu->channels = kसुस्मृति(पंचांगu->num_channels, माप(*पंचांगu->channels),
				GFP_KERNEL);
	अगर (पंचांगu->channels == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_unmap;
	पूर्ण

	/*
	 * Use the first channel as a घड़ी event device and the second channel
	 * as a घड़ी source.
	 */
	क्रम (i = 0; i < पंचांगu->num_channels; ++i) अणु
		ret = sh_पंचांगu_channel_setup(&पंचांगu->channels[i], i,
					   i == 0, i == 1, पंचांगu);
		अगर (ret < 0)
			जाओ err_unmap;
	पूर्ण

	platक्रमm_set_drvdata(pdev, पंचांगu);

	वापस 0;

err_unmap:
	kमुक्त(पंचांगu->channels);
	iounmap(पंचांगu->mapbase);
err_clk_unprepare:
	clk_unprepare(पंचांगu->clk);
err_clk_put:
	clk_put(पंचांगu->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक sh_पंचांगu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_पंचांगu_device *पंचांगu = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	अगर (!is_sh_early_platक्रमm_device(pdev)) अणु
		pm_runसमय_set_active(&pdev->dev);
		pm_runसमय_enable(&pdev->dev);
	पूर्ण

	अगर (पंचांगu) अणु
		dev_info(&pdev->dev, "kept as earlytimer\n");
		जाओ out;
	पूर्ण

	पंचांगu = kzalloc(माप(*पंचांगu), GFP_KERNEL);
	अगर (पंचांगu == शून्य)
		वापस -ENOMEM;

	ret = sh_पंचांगu_setup(पंचांगu, pdev);
	अगर (ret) अणु
		kमुक्त(पंचांगu);
		pm_runसमय_idle(&pdev->dev);
		वापस ret;
	पूर्ण

	अगर (is_sh_early_platक्रमm_device(pdev))
		वापस 0;

 out:
	अगर (पंचांगu->has_घड़ीevent || पंचांगu->has_घड़ीsource)
		pm_runसमय_irq_safe(&pdev->dev);
	अन्यथा
		pm_runसमय_idle(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sh_पंचांगu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -EBUSY; /* cannot unरेजिस्टर घड़ीevent and घड़ीsource */
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id sh_पंचांगu_id_table[] = अणु
	अणु "sh-tmu", SH_TMU पूर्ण,
	अणु "sh-tmu-sh3", SH_TMU_SH3 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, sh_पंचांगu_id_table);

अटल स्थिर काष्ठा of_device_id sh_पंचांगu_of_table[] __maybe_unused = अणु
	अणु .compatible = "renesas,tmu" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sh_पंचांगu_of_table);

अटल काष्ठा platक्रमm_driver sh_पंचांगu_device_driver = अणु
	.probe		= sh_पंचांगu_probe,
	.हटाओ		= sh_पंचांगu_हटाओ,
	.driver		= अणु
		.name	= "sh_tmu",
		.of_match_table = of_match_ptr(sh_पंचांगu_of_table),
	पूर्ण,
	.id_table	= sh_पंचांगu_id_table,
पूर्ण;

अटल पूर्णांक __init sh_पंचांगu_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sh_पंचांगu_device_driver);
पूर्ण

अटल व्योम __निकास sh_पंचांगu_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sh_पंचांगu_device_driver);
पूर्ण

#अगर_घोषित CONFIG_SUPERH
sh_early_platक्रमm_init("earlytimer", &sh_पंचांगu_device_driver);
#पूर्ण_अगर

subsys_initcall(sh_पंचांगu_init);
module_निकास(sh_पंचांगu_निकास);

MODULE_AUTHOR("Magnus Damm");
MODULE_DESCRIPTION("SuperH TMU Timer Driver");
MODULE_LICENSE("GPL v2");
