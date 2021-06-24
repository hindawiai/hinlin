<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Ralink RT2880 समयr
 * Author: John Crispin
 *
 * Copyright (C) 2013 John Crispin <john@phrozen.org>
*/

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयr.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/clk.h>

#समावेश <यंत्र/mach-ralink/ralink_regs.h>

#घोषणा TIMER_REG_TMRSTAT		0x00
#घोषणा TIMER_REG_TMR0LOAD		0x10
#घोषणा TIMER_REG_TMR0CTL		0x18

#घोषणा TMRSTAT_TMR0INT			BIT(0)

#घोषणा TMR0CTL_ENABLE			BIT(7)
#घोषणा TMR0CTL_MODE_PERIODIC		BIT(4)
#घोषणा TMR0CTL_PRESCALER		1
#घोषणा TMR0CTL_PRESCALE_VAL		(0xf - TMR0CTL_PRESCALER)
#घोषणा TMR0CTL_PRESCALE_DIV		(65536 / BIT(TMR0CTL_PRESCALER))

काष्ठा rt_समयr अणु
	काष्ठा device	*dev;
	व्योम __iomem	*membase;
	पूर्णांक		irq;
	अचिन्हित दीर्घ	समयr_freq;
	अचिन्हित दीर्घ	समयr_भाग;
पूर्ण;

अटल अंतरभूत व्योम rt_समयr_w32(काष्ठा rt_समयr *rt, u8 reg, u32 val)
अणु
	__raw_ग_लिखोl(val, rt->membase + reg);
पूर्ण

अटल अंतरभूत u32 rt_समयr_r32(काष्ठा rt_समयr *rt, u8 reg)
अणु
	वापस __raw_पढ़ोl(rt->membase + reg);
पूर्ण

अटल irqवापस_t rt_समयr_irq(पूर्णांक irq, व्योम *_rt)
अणु
	काष्ठा rt_समयr *rt =  (काष्ठा rt_समयr *) _rt;

	rt_समयr_w32(rt, TIMER_REG_TMR0LOAD, rt->समयr_freq / rt->समयr_भाग);
	rt_समयr_w32(rt, TIMER_REG_TMRSTAT, TMRSTAT_TMR0INT);

	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक rt_समयr_request(काष्ठा rt_समयr *rt)
अणु
	पूर्णांक err = request_irq(rt->irq, rt_समयr_irq, 0,
						dev_name(rt->dev), rt);
	अगर (err) अणु
		dev_err(rt->dev, "failed to request irq\n");
	पूर्ण अन्यथा अणु
		u32 t = TMR0CTL_MODE_PERIODIC | TMR0CTL_PRESCALE_VAL;
		rt_समयr_w32(rt, TIMER_REG_TMR0CTL, t);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक rt_समयr_config(काष्ठा rt_समयr *rt, अचिन्हित दीर्घ भागisor)
अणु
	अगर (rt->समयr_freq < भागisor)
		rt->समयr_भाग = rt->समयr_freq;
	अन्यथा
		rt->समयr_भाग = भागisor;

	rt_समयr_w32(rt, TIMER_REG_TMR0LOAD, rt->समयr_freq / rt->समयr_भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक rt_समयr_enable(काष्ठा rt_समयr *rt)
अणु
	u32 t;

	rt_समयr_w32(rt, TIMER_REG_TMR0LOAD, rt->समयr_freq / rt->समयr_भाग);

	t = rt_समयr_r32(rt, TIMER_REG_TMR0CTL);
	t |= TMR0CTL_ENABLE;
	rt_समयr_w32(rt, TIMER_REG_TMR0CTL, t);

	वापस 0;
पूर्ण

अटल पूर्णांक rt_समयr_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	काष्ठा rt_समयr *rt;
	काष्ठा clk *clk;

	rt = devm_kzalloc(&pdev->dev, माप(*rt), GFP_KERNEL);
	अगर (!rt) अणु
		dev_err(&pdev->dev, "failed to allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	rt->irq = platक्रमm_get_irq(pdev, 0);
	अगर (rt->irq < 0)
		वापस rt->irq;

	rt->membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(rt->membase))
		वापस PTR_ERR(rt->membase);

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "failed get clock rate\n");
		वापस PTR_ERR(clk);
	पूर्ण

	rt->समयr_freq = clk_get_rate(clk) / TMR0CTL_PRESCALE_DIV;
	अगर (!rt->समयr_freq)
		वापस -EINVAL;

	rt->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, rt);

	rt_समयr_request(rt);
	rt_समयr_config(rt, 2);
	rt_समयr_enable(rt);

	dev_info(&pdev->dev, "maximum frequency is %luHz\n", rt->समयr_freq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rt_समयr_match[] = अणु
	अणु .compatible = "ralink,rt2880-timer" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver rt_समयr_driver = अणु
	.probe = rt_समयr_probe,
	.driver = अणु
		.name			= "rt-timer",
		.of_match_table		= rt_समयr_match,
		.suppress_bind_attrs	= true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(rt_समयr_driver);
