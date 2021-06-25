<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * STM32 Timer Encoder and Counter driver
 *
 * Copyright (C) STMicroelectronics 2018
 *
 * Author: Benjamin Gaignard <benjamin.gaignard@st.com>
 *
 */
#समावेश <linux/counter.h>
#समावेश <linux/mfd/sपंचांग32-समयrs.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा TIM_CCMR_CCXS	(BIT(8) | BIT(0))
#घोषणा TIM_CCMR_MASK	(TIM_CCMR_CC1S | TIM_CCMR_CC2S | \
			 TIM_CCMR_IC1F | TIM_CCMR_IC2F)
#घोषणा TIM_CCER_MASK	(TIM_CCER_CC1P | TIM_CCER_CC1NP | \
			 TIM_CCER_CC2P | TIM_CCER_CC2NP)

काष्ठा sपंचांग32_समयr_regs अणु
	u32 cr1;
	u32 cnt;
	u32 smcr;
	u32 arr;
पूर्ण;

काष्ठा sपंचांग32_समयr_cnt अणु
	काष्ठा counter_device counter;
	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
	u32 max_arr;
	bool enabled;
	काष्ठा sपंचांग32_समयr_regs bak;
पूर्ण;

/**
 * क्रमागत sपंचांग32_count_function - क्रमागतerates sपंचांग32 समयr counter encoder modes
 * @STM32_COUNT_SLAVE_MODE_DISABLED: counts on पूर्णांकernal घड़ी when CEN=1
 * @STM32_COUNT_ENCODER_MODE_1: counts TI1FP1 edges, depending on TI2FP2 level
 * @STM32_COUNT_ENCODER_MODE_2: counts TI2FP2 edges, depending on TI1FP1 level
 * @STM32_COUNT_ENCODER_MODE_3: counts on both TI1FP1 and TI2FP2 edges
 */
क्रमागत sपंचांग32_count_function अणु
	STM32_COUNT_SLAVE_MODE_DISABLED,
	STM32_COUNT_ENCODER_MODE_1,
	STM32_COUNT_ENCODER_MODE_2,
	STM32_COUNT_ENCODER_MODE_3,
पूर्ण;

अटल क्रमागत counter_count_function sपंचांग32_count_functions[] = अणु
	[STM32_COUNT_SLAVE_MODE_DISABLED] = COUNTER_COUNT_FUNCTION_INCREASE,
	[STM32_COUNT_ENCODER_MODE_1] = COUNTER_COUNT_FUNCTION_QUADRATURE_X2_A,
	[STM32_COUNT_ENCODER_MODE_2] = COUNTER_COUNT_FUNCTION_QUADRATURE_X2_B,
	[STM32_COUNT_ENCODER_MODE_3] = COUNTER_COUNT_FUNCTION_QUADRATURE_X4,
पूर्ण;

अटल पूर्णांक sपंचांग32_count_पढ़ो(काष्ठा counter_device *counter,
			    काष्ठा counter_count *count, अचिन्हित दीर्घ *val)
अणु
	काष्ठा sपंचांग32_समयr_cnt *स्थिर priv = counter->priv;
	u32 cnt;

	regmap_पढ़ो(priv->regmap, TIM_CNT, &cnt);
	*val = cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_count_ग_लिखो(काष्ठा counter_device *counter,
			     काष्ठा counter_count *count,
			     स्थिर अचिन्हित दीर्घ val)
अणु
	काष्ठा sपंचांग32_समयr_cnt *स्थिर priv = counter->priv;
	u32 उच्चमानing;

	regmap_पढ़ो(priv->regmap, TIM_ARR, &उच्चमानing);
	अगर (val > उच्चमानing)
		वापस -EINVAL;

	वापस regmap_ग_लिखो(priv->regmap, TIM_CNT, val);
पूर्ण

अटल पूर्णांक sपंचांग32_count_function_get(काष्ठा counter_device *counter,
				    काष्ठा counter_count *count,
				    माप_प्रकार *function)
अणु
	काष्ठा sपंचांग32_समयr_cnt *स्थिर priv = counter->priv;
	u32 smcr;

	regmap_पढ़ो(priv->regmap, TIM_SMCR, &smcr);

	चयन (smcr & TIM_SMCR_SMS) अणु
	हाल 0:
		*function = STM32_COUNT_SLAVE_MODE_DISABLED;
		वापस 0;
	हाल 1:
		*function = STM32_COUNT_ENCODER_MODE_1;
		वापस 0;
	हाल 2:
		*function = STM32_COUNT_ENCODER_MODE_2;
		वापस 0;
	हाल 3:
		*function = STM32_COUNT_ENCODER_MODE_3;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_count_function_set(काष्ठा counter_device *counter,
				    काष्ठा counter_count *count,
				    माप_प्रकार function)
अणु
	काष्ठा sपंचांग32_समयr_cnt *स्थिर priv = counter->priv;
	u32 cr1, sms;

	चयन (function) अणु
	हाल STM32_COUNT_SLAVE_MODE_DISABLED:
		sms = 0;
		अवरोध;
	हाल STM32_COUNT_ENCODER_MODE_1:
		sms = 1;
		अवरोध;
	हाल STM32_COUNT_ENCODER_MODE_2:
		sms = 2;
		अवरोध;
	हाल STM32_COUNT_ENCODER_MODE_3:
		sms = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Store enable status */
	regmap_पढ़ो(priv->regmap, TIM_CR1, &cr1);

	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, 0);

	regmap_update_bits(priv->regmap, TIM_SMCR, TIM_SMCR_SMS, sms);

	/* Make sure that रेजिस्टरs are updated */
	regmap_update_bits(priv->regmap, TIM_EGR, TIM_EGR_UG, TIM_EGR_UG);

	/* Restore the enable status */
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, cr1);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sपंचांग32_count_direction_पढ़ो(काष्ठा counter_device *counter,
				      काष्ठा counter_count *count,
				      व्योम *निजी, अक्षर *buf)
अणु
	काष्ठा sपंचांग32_समयr_cnt *स्थिर priv = counter->priv;
	स्थिर अक्षर *direction;
	u32 cr1;

	regmap_पढ़ो(priv->regmap, TIM_CR1, &cr1);
	direction = (cr1 & TIM_CR1_सूची) ? "backward" : "forward";

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", direction);
पूर्ण

अटल sमाप_प्रकार sपंचांग32_count_उच्चमानing_पढ़ो(काष्ठा counter_device *counter,
					काष्ठा counter_count *count,
					व्योम *निजी, अक्षर *buf)
अणु
	काष्ठा sपंचांग32_समयr_cnt *स्थिर priv = counter->priv;
	u32 arr;

	regmap_पढ़ो(priv->regmap, TIM_ARR, &arr);

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", arr);
पूर्ण

अटल sमाप_प्रकार sपंचांग32_count_उच्चमानing_ग_लिखो(काष्ठा counter_device *counter,
					 काष्ठा counter_count *count,
					 व्योम *निजी,
					 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा sपंचांग32_समयr_cnt *स्थिर priv = counter->priv;
	अचिन्हित पूर्णांक उच्चमानing;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 0, &उच्चमानing);
	अगर (ret)
		वापस ret;

	अगर (उच्चमानing > priv->max_arr)
		वापस -दुस्फल;

	/* TIMx_ARR रेजिस्टर shouldn't be buffered (ARPE=0) */
	regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_ARPE, 0);
	regmap_ग_लिखो(priv->regmap, TIM_ARR, उच्चमानing);

	वापस len;
पूर्ण

अटल sमाप_प्रकार sपंचांग32_count_enable_पढ़ो(काष्ठा counter_device *counter,
				       काष्ठा counter_count *count,
				       व्योम *निजी, अक्षर *buf)
अणु
	काष्ठा sपंचांग32_समयr_cnt *स्थिर priv = counter->priv;
	u32 cr1;

	regmap_पढ़ो(priv->regmap, TIM_CR1, &cr1);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", (bool)(cr1 & TIM_CR1_CEN));
पूर्ण

अटल sमाप_प्रकार sपंचांग32_count_enable_ग_लिखो(काष्ठा counter_device *counter,
					काष्ठा counter_count *count,
					व्योम *निजी,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा sपंचांग32_समयr_cnt *स्थिर priv = counter->priv;
	पूर्णांक err;
	u32 cr1;
	bool enable;

	err = kstrtobool(buf, &enable);
	अगर (err)
		वापस err;

	अगर (enable) अणु
		regmap_पढ़ो(priv->regmap, TIM_CR1, &cr1);
		अगर (!(cr1 & TIM_CR1_CEN))
			clk_enable(priv->clk);

		regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN,
				   TIM_CR1_CEN);
	पूर्ण अन्यथा अणु
		regmap_पढ़ो(priv->regmap, TIM_CR1, &cr1);
		regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, 0);
		अगर (cr1 & TIM_CR1_CEN)
			clk_disable(priv->clk);
	पूर्ण

	/* Keep enabled state to properly handle low घातer states */
	priv->enabled = enable;

	वापस len;
पूर्ण

अटल स्थिर काष्ठा counter_count_ext sपंचांग32_count_ext[] = अणु
	अणु
		.name = "direction",
		.पढ़ो = sपंचांग32_count_direction_पढ़ो,
	पूर्ण,
	अणु
		.name = "enable",
		.पढ़ो = sपंचांग32_count_enable_पढ़ो,
		.ग_लिखो = sपंचांग32_count_enable_ग_लिखो
	पूर्ण,
	अणु
		.name = "ceiling",
		.पढ़ो = sपंचांग32_count_उच्चमानing_पढ़ो,
		.ग_लिखो = sपंचांग32_count_उच्चमानing_ग_लिखो
	पूर्ण,
पूर्ण;

क्रमागत sपंचांग32_synapse_action अणु
	STM32_SYNAPSE_ACTION_NONE,
	STM32_SYNAPSE_ACTION_BOTH_EDGES
पूर्ण;

अटल क्रमागत counter_synapse_action sपंचांग32_synapse_actions[] = अणु
	[STM32_SYNAPSE_ACTION_NONE] = COUNTER_SYNAPSE_ACTION_NONE,
	[STM32_SYNAPSE_ACTION_BOTH_EDGES] = COUNTER_SYNAPSE_ACTION_BOTH_EDGES
पूर्ण;

अटल पूर्णांक sपंचांग32_action_get(काष्ठा counter_device *counter,
			    काष्ठा counter_count *count,
			    काष्ठा counter_synapse *synapse,
			    माप_प्रकार *action)
अणु
	माप_प्रकार function;
	पूर्णांक err;

	err = sपंचांग32_count_function_get(counter, count, &function);
	अगर (err)
		वापस err;

	चयन (function) अणु
	हाल STM32_COUNT_SLAVE_MODE_DISABLED:
		/* counts on पूर्णांकernal घड़ी when CEN=1 */
		*action = STM32_SYNAPSE_ACTION_NONE;
		वापस 0;
	हाल STM32_COUNT_ENCODER_MODE_1:
		/* counts up/करोwn on TI1FP1 edge depending on TI2FP2 level */
		अगर (synapse->संकेत->id == count->synapses[0].संकेत->id)
			*action = STM32_SYNAPSE_ACTION_BOTH_EDGES;
		अन्यथा
			*action = STM32_SYNAPSE_ACTION_NONE;
		वापस 0;
	हाल STM32_COUNT_ENCODER_MODE_2:
		/* counts up/करोwn on TI2FP2 edge depending on TI1FP1 level */
		अगर (synapse->संकेत->id == count->synapses[1].संकेत->id)
			*action = STM32_SYNAPSE_ACTION_BOTH_EDGES;
		अन्यथा
			*action = STM32_SYNAPSE_ACTION_NONE;
		वापस 0;
	हाल STM32_COUNT_ENCODER_MODE_3:
		/* counts up/करोwn on both TI1FP1 and TI2FP2 edges */
		*action = STM32_SYNAPSE_ACTION_BOTH_EDGES;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा counter_ops sपंचांग32_समयr_cnt_ops = अणु
	.count_पढ़ो = sपंचांग32_count_पढ़ो,
	.count_ग_लिखो = sपंचांग32_count_ग_लिखो,
	.function_get = sपंचांग32_count_function_get,
	.function_set = sपंचांग32_count_function_set,
	.action_get = sपंचांग32_action_get,
पूर्ण;

अटल काष्ठा counter_संकेत sपंचांग32_संकेतs[] = अणु
	अणु
		.id = 0,
		.name = "Channel 1 Quadrature A"
	पूर्ण,
	अणु
		.id = 1,
		.name = "Channel 1 Quadrature B"
	पूर्ण
पूर्ण;

अटल काष्ठा counter_synapse sपंचांग32_count_synapses[] = अणु
	अणु
		.actions_list = sपंचांग32_synapse_actions,
		.num_actions = ARRAY_SIZE(sपंचांग32_synapse_actions),
		.संकेत = &sपंचांग32_संकेतs[0]
	पूर्ण,
	अणु
		.actions_list = sपंचांग32_synapse_actions,
		.num_actions = ARRAY_SIZE(sपंचांग32_synapse_actions),
		.संकेत = &sपंचांग32_संकेतs[1]
	पूर्ण
पूर्ण;

अटल काष्ठा counter_count sपंचांग32_counts = अणु
	.id = 0,
	.name = "Channel 1 Count",
	.functions_list = sपंचांग32_count_functions,
	.num_functions = ARRAY_SIZE(sपंचांग32_count_functions),
	.synapses = sपंचांग32_count_synapses,
	.num_synapses = ARRAY_SIZE(sपंचांग32_count_synapses),
	.ext = sपंचांग32_count_ext,
	.num_ext = ARRAY_SIZE(sपंचांग32_count_ext)
पूर्ण;

अटल पूर्णांक sपंचांग32_समयr_cnt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_समयrs *ddata = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sपंचांग32_समयr_cnt *priv;

	अगर (IS_ERR_OR_शून्य(ddata))
		वापस -EINVAL;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regmap = ddata->regmap;
	priv->clk = ddata->clk;
	priv->max_arr = ddata->max_arr;

	priv->counter.name = dev_name(dev);
	priv->counter.parent = dev;
	priv->counter.ops = &sपंचांग32_समयr_cnt_ops;
	priv->counter.counts = &sपंचांग32_counts;
	priv->counter.num_counts = 1;
	priv->counter.संकेतs = sपंचांग32_संकेतs;
	priv->counter.num_संकेतs = ARRAY_SIZE(sपंचांग32_संकेतs);
	priv->counter.priv = priv;

	platक्रमm_set_drvdata(pdev, priv);

	/* Register Counter device */
	वापस devm_counter_रेजिस्टर(dev, &priv->counter);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_समयr_cnt_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_समयr_cnt *priv = dev_get_drvdata(dev);

	/* Only take care of enabled counter: करोn't disturb other MFD child */
	अगर (priv->enabled) अणु
		/* Backup रेजिस्टरs that may get lost in low घातer mode */
		regmap_पढ़ो(priv->regmap, TIM_SMCR, &priv->bak.smcr);
		regmap_पढ़ो(priv->regmap, TIM_ARR, &priv->bak.arr);
		regmap_पढ़ो(priv->regmap, TIM_CNT, &priv->bak.cnt);
		regmap_पढ़ो(priv->regmap, TIM_CR1, &priv->bak.cr1);

		/* Disable the counter */
		regmap_update_bits(priv->regmap, TIM_CR1, TIM_CR1_CEN, 0);
		clk_disable(priv->clk);
	पूर्ण

	वापस pinctrl_pm_select_sleep_state(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_समयr_cnt_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_समयr_cnt *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pinctrl_pm_select_शेष_state(dev);
	अगर (ret)
		वापस ret;

	अगर (priv->enabled) अणु
		clk_enable(priv->clk);

		/* Restore रेजिस्टरs that may have been lost */
		regmap_ग_लिखो(priv->regmap, TIM_SMCR, priv->bak.smcr);
		regmap_ग_लिखो(priv->regmap, TIM_ARR, priv->bak.arr);
		regmap_ग_लिखो(priv->regmap, TIM_CNT, priv->bak.cnt);

		/* Also re-enables the counter */
		regmap_ग_लिखो(priv->regmap, TIM_CR1, priv->bak.cr1);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sपंचांग32_समयr_cnt_pm_ops, sपंचांग32_समयr_cnt_suspend,
			 sपंचांग32_समयr_cnt_resume);

अटल स्थिर काष्ठा of_device_id sपंचांग32_समयr_cnt_of_match[] = अणु
	अणु .compatible = "st,stm32-timer-counter", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_समयr_cnt_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_समयr_cnt_driver = अणु
	.probe = sपंचांग32_समयr_cnt_probe,
	.driver = अणु
		.name = "stm32-timer-counter",
		.of_match_table = sपंचांग32_समयr_cnt_of_match,
		.pm = &sपंचांग32_समयr_cnt_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_समयr_cnt_driver);

MODULE_AUTHOR("Benjamin Gaignard <benjamin.gaignard@st.com>");
MODULE_ALIAS("platform:stm32-timer-counter");
MODULE_DESCRIPTION("STMicroelectronics STM32 TIMER counter driver");
MODULE_LICENSE("GPL v2");
