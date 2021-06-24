<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2019 - All Rights Reserved
 * Authors: Benjamin Gaignard <benjamin.gaignard@st.com> क्रम STMicroelectronics.
 *	    Pascal Paillet <p.paillet@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/sपंचांग32-lpसमयr.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_wakeirq.h>

#घोषणा CFGR_PSC_OFFSET		9
#घोषणा STM32_LP_RATING		1000
#घोषणा STM32_TARGET_CLKRATE	(32000 * HZ)
#घोषणा STM32_LP_MAX_PSC	7

काष्ठा sपंचांग32_lp_निजी अणु
	काष्ठा regmap *reg;
	काष्ठा घड़ी_event_device clkevt;
	अचिन्हित दीर्घ period;
	काष्ठा device *dev;
पूर्ण;

अटल काष्ठा sपंचांग32_lp_निजी*
to_priv(काष्ठा घड़ी_event_device *clkevt)
अणु
	वापस container_of(clkevt, काष्ठा sपंचांग32_lp_निजी, clkevt);
पूर्ण

अटल पूर्णांक sपंचांग32_clkevent_lp_shutकरोwn(काष्ठा घड़ी_event_device *clkevt)
अणु
	काष्ठा sपंचांग32_lp_निजी *priv = to_priv(clkevt);

	regmap_ग_लिखो(priv->reg, STM32_LPTIM_CR, 0);
	regmap_ग_लिखो(priv->reg, STM32_LPTIM_IER, 0);
	/* clear pending flags */
	regmap_ग_लिखो(priv->reg, STM32_LPTIM_ICR, STM32_LPTIM_ARRMCF);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_clkevent_lp_set_समयr(अचिन्हित दीर्घ evt,
				       काष्ठा घड़ी_event_device *clkevt,
				       पूर्णांक is_periodic)
अणु
	काष्ठा sपंचांग32_lp_निजी *priv = to_priv(clkevt);

	/* disable LPTIMER to be able to ग_लिखो पूर्णांकo IER रेजिस्टर*/
	regmap_ग_लिखो(priv->reg, STM32_LPTIM_CR, 0);
	/* enable ARR पूर्णांकerrupt */
	regmap_ग_लिखो(priv->reg, STM32_LPTIM_IER, STM32_LPTIM_ARRMIE);
	/* enable LPTIMER to be able to ग_लिखो पूर्णांकo ARR रेजिस्टर */
	regmap_ग_लिखो(priv->reg, STM32_LPTIM_CR, STM32_LPTIM_ENABLE);
	/* set next event counter */
	regmap_ग_लिखो(priv->reg, STM32_LPTIM_ARR, evt);

	/* start counter */
	अगर (is_periodic)
		regmap_ग_लिखो(priv->reg, STM32_LPTIM_CR,
			     STM32_LPTIM_CNTSTRT | STM32_LPTIM_ENABLE);
	अन्यथा
		regmap_ग_लिखो(priv->reg, STM32_LPTIM_CR,
			     STM32_LPTIM_SNGSTRT | STM32_LPTIM_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_clkevent_lp_set_next_event(अचिन्हित दीर्घ evt,
					    काष्ठा घड़ी_event_device *clkevt)
अणु
	वापस sपंचांग32_clkevent_lp_set_समयr(evt, clkevt,
					   घड़ीevent_state_periodic(clkevt));
पूर्ण

अटल पूर्णांक sपंचांग32_clkevent_lp_set_periodic(काष्ठा घड़ी_event_device *clkevt)
अणु
	काष्ठा sपंचांग32_lp_निजी *priv = to_priv(clkevt);

	वापस sपंचांग32_clkevent_lp_set_समयr(priv->period, clkevt, true);
पूर्ण

अटल पूर्णांक sपंचांग32_clkevent_lp_set_oneshot(काष्ठा घड़ी_event_device *clkevt)
अणु
	काष्ठा sपंचांग32_lp_निजी *priv = to_priv(clkevt);

	वापस sपंचांग32_clkevent_lp_set_समयr(priv->period, clkevt, false);
पूर्ण

अटल irqवापस_t sपंचांग32_clkevent_lp_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा घड़ी_event_device *clkevt = (काष्ठा घड़ी_event_device *)dev_id;
	काष्ठा sपंचांग32_lp_निजी *priv = to_priv(clkevt);

	regmap_ग_लिखो(priv->reg, STM32_LPTIM_ICR, STM32_LPTIM_ARRMCF);

	अगर (clkevt->event_handler)
		clkevt->event_handler(clkevt);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sपंचांग32_clkevent_lp_set_prescaler(काष्ठा sपंचांग32_lp_निजी *priv,
					    अचिन्हित दीर्घ *rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= STM32_LP_MAX_PSC; i++) अणु
		अगर (DIV_ROUND_CLOSEST(*rate, 1 << i) < STM32_TARGET_CLKRATE)
			अवरोध;
	पूर्ण

	regmap_ग_लिखो(priv->reg, STM32_LPTIM_CFGR, i << CFGR_PSC_OFFSET);

	/* Adjust rate and period given the prescaler value */
	*rate = DIV_ROUND_CLOSEST(*rate, (1 << i));
	priv->period = DIV_ROUND_UP(*rate, HZ);
पूर्ण

अटल व्योम sपंचांग32_clkevent_lp_init(काष्ठा sपंचांग32_lp_निजी *priv,
				  काष्ठा device_node *np, अचिन्हित दीर्घ rate)
अणु
	priv->clkevt.name = np->full_name;
	priv->clkevt.cpumask = cpu_possible_mask;
	priv->clkevt.features = CLOCK_EVT_FEAT_PERIODIC |
				CLOCK_EVT_FEAT_ONESHOT;
	priv->clkevt.set_state_shutकरोwn = sपंचांग32_clkevent_lp_shutकरोwn;
	priv->clkevt.set_state_periodic = sपंचांग32_clkevent_lp_set_periodic;
	priv->clkevt.set_state_oneshot = sपंचांग32_clkevent_lp_set_oneshot;
	priv->clkevt.set_next_event = sपंचांग32_clkevent_lp_set_next_event;
	priv->clkevt.rating = STM32_LP_RATING;

	घड़ीevents_config_and_रेजिस्टर(&priv->clkevt, rate, 0x1,
					STM32_LPTIM_MAX_ARR);
पूर्ण

अटल पूर्णांक sपंचांग32_clkevent_lp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_lpसमयr *ddata = dev_get_drvdata(pdev->dev.parent);
	काष्ठा sपंचांग32_lp_निजी *priv;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret, irq;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->reg = ddata->regmap;
	ret = clk_prepare_enable(ddata->clk);
	अगर (ret)
		वापस -EINVAL;

	rate = clk_get_rate(ddata->clk);
	अगर (!rate) अणु
		ret = -EINVAL;
		जाओ out_clk_disable;
	पूर्ण

	irq = platक्रमm_get_irq(to_platक्रमm_device(pdev->dev.parent), 0);
	अगर (irq <= 0) अणु
		ret = irq;
		जाओ out_clk_disable;
	पूर्ण

	अगर (of_property_पढ़ो_bool(pdev->dev.parent->of_node, "wakeup-source")) अणु
		ret = device_init_wakeup(&pdev->dev, true);
		अगर (ret)
			जाओ out_clk_disable;

		ret = dev_pm_set_wake_irq(&pdev->dev, irq);
		अगर (ret)
			जाओ out_clk_disable;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, sपंचांग32_clkevent_lp_irq_handler,
			       IRQF_TIMER, pdev->name, &priv->clkevt);
	अगर (ret)
		जाओ out_clk_disable;

	sपंचांग32_clkevent_lp_set_prescaler(priv, &rate);

	sपंचांग32_clkevent_lp_init(priv, pdev->dev.parent->of_node, rate);

	priv->dev = &pdev->dev;

	वापस 0;

out_clk_disable:
	clk_disable_unprepare(ddata->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_clkevent_lp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -EBUSY; /* cannot unरेजिस्टर घड़ीevent */
पूर्ण

अटल स्थिर काष्ठा of_device_id sपंचांग32_clkevent_lp_of_match[] = अणु
	अणु .compatible = "st,stm32-lptimer-timer", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_clkevent_lp_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_clkevent_lp_driver = अणु
	.probe	= sपंचांग32_clkevent_lp_probe,
	.हटाओ = sपंचांग32_clkevent_lp_हटाओ,
	.driver	= अणु
		.name = "stm32-lptimer-timer",
		.of_match_table = of_match_ptr(sपंचांग32_clkevent_lp_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_clkevent_lp_driver);

MODULE_ALIAS("platform:stm32-lptimer-timer");
MODULE_DESCRIPTION("STMicroelectronics STM32 clockevent low power driver");
MODULE_LICENSE("GPL v2");
