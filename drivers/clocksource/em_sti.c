<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Emma Mobile Timer Support - STI
 *
 *  Copyright (C) 2012 Magnus Damm
 */

#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/irq.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

क्रमागत अणु USER_CLOCKSOURCE, USER_CLOCKEVENT, USER_NR पूर्ण;

काष्ठा em_sti_priv अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा platक्रमm_device *pdev;
	अचिन्हित पूर्णांक active[USER_NR];
	अचिन्हित दीर्घ rate;
	raw_spinlock_t lock;
	काष्ठा घड़ी_event_device ced;
	काष्ठा घड़ीsource cs;
पूर्ण;

#घोषणा STI_CONTROL 0x00
#घोषणा STI_COMPA_H 0x10
#घोषणा STI_COMPA_L 0x14
#घोषणा STI_COMPB_H 0x18
#घोषणा STI_COMPB_L 0x1c
#घोषणा STI_COUNT_H 0x20
#घोषणा STI_COUNT_L 0x24
#घोषणा STI_COUNT_RAW_H 0x28
#घोषणा STI_COUNT_RAW_L 0x2c
#घोषणा STI_SET_H 0x30
#घोषणा STI_SET_L 0x34
#घोषणा STI_INTSTATUS 0x40
#घोषणा STI_INTRAWSTATUS 0x44
#घोषणा STI_INTENSET 0x48
#घोषणा STI_INTENCLR 0x4c
#घोषणा STI_INTFFCLR 0x50

अटल अंतरभूत अचिन्हित दीर्घ em_sti_पढ़ो(काष्ठा em_sti_priv *p, पूर्णांक offs)
अणु
	वापस ioपढ़ो32(p->base + offs);
पूर्ण

अटल अंतरभूत व्योम em_sti_ग_लिखो(काष्ठा em_sti_priv *p, पूर्णांक offs,
				अचिन्हित दीर्घ value)
अणु
	ioग_लिखो32(value, p->base + offs);
पूर्ण

अटल पूर्णांक em_sti_enable(काष्ठा em_sti_priv *p)
अणु
	पूर्णांक ret;

	/* enable घड़ी */
	ret = clk_enable(p->clk);
	अगर (ret) अणु
		dev_err(&p->pdev->dev, "cannot enable clock\n");
		वापस ret;
	पूर्ण

	/* reset the counter */
	em_sti_ग_लिखो(p, STI_SET_H, 0x40000000);
	em_sti_ग_लिखो(p, STI_SET_L, 0x00000000);

	/* mask and clear pending पूर्णांकerrupts */
	em_sti_ग_लिखो(p, STI_INTENCLR, 3);
	em_sti_ग_लिखो(p, STI_INTFFCLR, 3);

	/* enable updates of counter रेजिस्टरs */
	em_sti_ग_लिखो(p, STI_CONTROL, 1);

	वापस 0;
पूर्ण

अटल व्योम em_sti_disable(काष्ठा em_sti_priv *p)
अणु
	/* mask पूर्णांकerrupts */
	em_sti_ग_लिखो(p, STI_INTENCLR, 3);

	/* stop घड़ी */
	clk_disable(p->clk);
पूर्ण

अटल u64 em_sti_count(काष्ठा em_sti_priv *p)
अणु
	u64 ticks;
	अचिन्हित दीर्घ flags;

	/* the STI hardware buffers the 48-bit count, but to
	 * अवरोध it out पूर्णांकo two 32-bit access the रेजिस्टरs
	 * must be accessed in a certain order.
	 * Always पढ़ो STI_COUNT_H beक्रमe STI_COUNT_L.
	 */
	raw_spin_lock_irqsave(&p->lock, flags);
	ticks = (u64)(em_sti_पढ़ो(p, STI_COUNT_H) & 0xffff) << 32;
	ticks |= em_sti_पढ़ो(p, STI_COUNT_L);
	raw_spin_unlock_irqrestore(&p->lock, flags);

	वापस ticks;
पूर्ण

अटल u64 em_sti_set_next(काष्ठा em_sti_priv *p, u64 next)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&p->lock, flags);

	/* mask compare A पूर्णांकerrupt */
	em_sti_ग_लिखो(p, STI_INTENCLR, 1);

	/* update compare A value */
	em_sti_ग_लिखो(p, STI_COMPA_H, next >> 32);
	em_sti_ग_लिखो(p, STI_COMPA_L, next & 0xffffffff);

	/* clear compare A पूर्णांकerrupt source */
	em_sti_ग_लिखो(p, STI_INTFFCLR, 1);

	/* unmask compare A पूर्णांकerrupt */
	em_sti_ग_लिखो(p, STI_INTENSET, 1);

	raw_spin_unlock_irqrestore(&p->lock, flags);

	वापस next;
पूर्ण

अटल irqवापस_t em_sti_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा em_sti_priv *p = dev_id;

	p->ced.event_handler(&p->ced);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक em_sti_start(काष्ठा em_sti_priv *p, अचिन्हित पूर्णांक user)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक used_beक्रमe;
	पूर्णांक ret = 0;

	raw_spin_lock_irqsave(&p->lock, flags);
	used_beक्रमe = p->active[USER_CLOCKSOURCE] | p->active[USER_CLOCKEVENT];
	अगर (!used_beक्रमe)
		ret = em_sti_enable(p);

	अगर (!ret)
		p->active[user] = 1;
	raw_spin_unlock_irqrestore(&p->lock, flags);

	वापस ret;
पूर्ण

अटल व्योम em_sti_stop(काष्ठा em_sti_priv *p, अचिन्हित पूर्णांक user)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक used_beक्रमe, used_after;

	raw_spin_lock_irqsave(&p->lock, flags);
	used_beक्रमe = p->active[USER_CLOCKSOURCE] | p->active[USER_CLOCKEVENT];
	p->active[user] = 0;
	used_after = p->active[USER_CLOCKSOURCE] | p->active[USER_CLOCKEVENT];

	अगर (used_beक्रमe && !used_after)
		em_sti_disable(p);
	raw_spin_unlock_irqrestore(&p->lock, flags);
पूर्ण

अटल काष्ठा em_sti_priv *cs_to_em_sti(काष्ठा घड़ीsource *cs)
अणु
	वापस container_of(cs, काष्ठा em_sti_priv, cs);
पूर्ण

अटल u64 em_sti_घड़ीsource_पढ़ो(काष्ठा घड़ीsource *cs)
अणु
	वापस em_sti_count(cs_to_em_sti(cs));
पूर्ण

अटल पूर्णांक em_sti_घड़ीsource_enable(काष्ठा घड़ीsource *cs)
अणु
	काष्ठा em_sti_priv *p = cs_to_em_sti(cs);

	वापस em_sti_start(p, USER_CLOCKSOURCE);
पूर्ण

अटल व्योम em_sti_घड़ीsource_disable(काष्ठा घड़ीsource *cs)
अणु
	em_sti_stop(cs_to_em_sti(cs), USER_CLOCKSOURCE);
पूर्ण

अटल व्योम em_sti_घड़ीsource_resume(काष्ठा घड़ीsource *cs)
अणु
	em_sti_घड़ीsource_enable(cs);
पूर्ण

अटल पूर्णांक em_sti_रेजिस्टर_घड़ीsource(काष्ठा em_sti_priv *p)
अणु
	काष्ठा घड़ीsource *cs = &p->cs;

	cs->name = dev_name(&p->pdev->dev);
	cs->rating = 200;
	cs->पढ़ो = em_sti_घड़ीsource_पढ़ो;
	cs->enable = em_sti_घड़ीsource_enable;
	cs->disable = em_sti_घड़ीsource_disable;
	cs->suspend = em_sti_घड़ीsource_disable;
	cs->resume = em_sti_घड़ीsource_resume;
	cs->mask = CLOCKSOURCE_MASK(48);
	cs->flags = CLOCK_SOURCE_IS_CONTINUOUS;

	dev_info(&p->pdev->dev, "used as clock source\n");

	घड़ीsource_रेजिस्टर_hz(cs, p->rate);
	वापस 0;
पूर्ण

अटल काष्ठा em_sti_priv *ced_to_em_sti(काष्ठा घड़ी_event_device *ced)
अणु
	वापस container_of(ced, काष्ठा em_sti_priv, ced);
पूर्ण

अटल पूर्णांक em_sti_घड़ी_event_shutकरोwn(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा em_sti_priv *p = ced_to_em_sti(ced);
	em_sti_stop(p, USER_CLOCKEVENT);
	वापस 0;
पूर्ण

अटल पूर्णांक em_sti_घड़ी_event_set_oneshot(काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा em_sti_priv *p = ced_to_em_sti(ced);

	dev_info(&p->pdev->dev, "used for oneshot clock events\n");
	em_sti_start(p, USER_CLOCKEVENT);
	वापस 0;
पूर्ण

अटल पूर्णांक em_sti_घड़ी_event_next(अचिन्हित दीर्घ delta,
				   काष्ठा घड़ी_event_device *ced)
अणु
	काष्ठा em_sti_priv *p = ced_to_em_sti(ced);
	u64 next;
	पूर्णांक safe;

	next = em_sti_set_next(p, em_sti_count(p) + delta);
	safe = em_sti_count(p) < (next - 1);

	वापस !safe;
पूर्ण

अटल व्योम em_sti_रेजिस्टर_घड़ीevent(काष्ठा em_sti_priv *p)
अणु
	काष्ठा घड़ी_event_device *ced = &p->ced;

	ced->name = dev_name(&p->pdev->dev);
	ced->features = CLOCK_EVT_FEAT_ONESHOT;
	ced->rating = 200;
	ced->cpumask = cpu_possible_mask;
	ced->set_next_event = em_sti_घड़ी_event_next;
	ced->set_state_shutकरोwn = em_sti_घड़ी_event_shutकरोwn;
	ced->set_state_oneshot = em_sti_घड़ी_event_set_oneshot;

	dev_info(&p->pdev->dev, "used for clock events\n");

	घड़ीevents_config_and_रेजिस्टर(ced, p->rate, 2, 0xffffffff);
पूर्ण

अटल पूर्णांक em_sti_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा em_sti_priv *p;
	पूर्णांक irq, ret;

	p = devm_kzalloc(&pdev->dev, माप(*p), GFP_KERNEL);
	अगर (p == शून्य)
		वापस -ENOMEM;

	p->pdev = pdev;
	platक्रमm_set_drvdata(pdev, p);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	/* map memory, let base poपूर्णांक to the STI instance */
	p->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(p->base))
		वापस PTR_ERR(p->base);

	ret = devm_request_irq(&pdev->dev, irq, em_sti_पूर्णांकerrupt,
			       IRQF_TIMER | IRQF_IRQPOLL | IRQF_NOBALANCING,
			       dev_name(&pdev->dev), p);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to request low IRQ\n");
		वापस ret;
	पूर्ण

	/* get hold of घड़ी */
	p->clk = devm_clk_get(&pdev->dev, "sclk");
	अगर (IS_ERR(p->clk)) अणु
		dev_err(&pdev->dev, "cannot get clock\n");
		वापस PTR_ERR(p->clk);
	पूर्ण

	ret = clk_prepare(p->clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "cannot prepare clock\n");
		वापस ret;
	पूर्ण

	ret = clk_enable(p->clk);
	अगर (ret < 0) अणु
		dev_err(&p->pdev->dev, "cannot enable clock\n");
		clk_unprepare(p->clk);
		वापस ret;
	पूर्ण
	p->rate = clk_get_rate(p->clk);
	clk_disable(p->clk);

	raw_spin_lock_init(&p->lock);
	em_sti_रेजिस्टर_घड़ीevent(p);
	em_sti_रेजिस्टर_घड़ीsource(p);
	वापस 0;
पूर्ण

अटल पूर्णांक em_sti_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -EBUSY; /* cannot unरेजिस्टर घड़ीevent and घड़ीsource */
पूर्ण

अटल स्थिर काष्ठा of_device_id em_sti_dt_ids[] = अणु
	अणु .compatible = "renesas,em-sti", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, em_sti_dt_ids);

अटल काष्ठा platक्रमm_driver em_sti_device_driver = अणु
	.probe		= em_sti_probe,
	.हटाओ		= em_sti_हटाओ,
	.driver		= अणु
		.name	= "em_sti",
		.of_match_table = em_sti_dt_ids,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init em_sti_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&em_sti_device_driver);
पूर्ण

अटल व्योम __निकास em_sti_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&em_sti_device_driver);
पूर्ण

subsys_initcall(em_sti_init);
module_निकास(em_sti_निकास);

MODULE_AUTHOR("Magnus Damm");
MODULE_DESCRIPTION("Renesas Emma Mobile STI Timer Driver");
MODULE_LICENSE("GPL v2");
