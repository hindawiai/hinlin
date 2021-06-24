<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * STM32 Low-Power Timer Encoder and Counter driver
 *
 * Copyright (C) STMicroelectronics 2017
 *
 * Author: Fabrice Gasnier <fabrice.gasnier@st.com>
 *
 * Inspired by 104-quad-8 and sपंचांग32-समयr-trigger drivers.
 *
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/counter.h>
#समावेश <linux/mfd/sपंचांग32-lpसमयr.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा sपंचांग32_lptim_cnt अणु
	काष्ठा counter_device counter;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
	u32 उच्चमानing;
	u32 polarity;
	u32 quadrature_mode;
	bool enabled;
पूर्ण;

अटल पूर्णांक sपंचांग32_lptim_is_enabled(काष्ठा sपंचांग32_lptim_cnt *priv)
अणु
	u32 val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(priv->regmap, STM32_LPTIM_CR, &val);
	अगर (ret)
		वापस ret;

	वापस FIELD_GET(STM32_LPTIM_ENABLE, val);
पूर्ण

अटल पूर्णांक sपंचांग32_lptim_set_enable_state(काष्ठा sपंचांग32_lptim_cnt *priv,
					पूर्णांक enable)
अणु
	पूर्णांक ret;
	u32 val;

	val = FIELD_PREP(STM32_LPTIM_ENABLE, enable);
	ret = regmap_ग_लिखो(priv->regmap, STM32_LPTIM_CR, val);
	अगर (ret)
		वापस ret;

	अगर (!enable) अणु
		clk_disable(priv->clk);
		priv->enabled = false;
		वापस 0;
	पूर्ण

	/* LP समयr must be enabled beक्रमe writing CMP & ARR */
	ret = regmap_ग_लिखो(priv->regmap, STM32_LPTIM_ARR, priv->उच्चमानing);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(priv->regmap, STM32_LPTIM_CMP, 0);
	अगर (ret)
		वापस ret;

	/* ensure CMP & ARR रेजिस्टरs are properly written */
	ret = regmap_पढ़ो_poll_समयout(priv->regmap, STM32_LPTIM_ISR, val,
				       (val & STM32_LPTIM_CMPOK_ARROK),
				       100, 1000);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(priv->regmap, STM32_LPTIM_ICR,
			   STM32_LPTIM_CMPOKCF_ARROKCF);
	अगर (ret)
		वापस ret;

	ret = clk_enable(priv->clk);
	अगर (ret) अणु
		regmap_ग_लिखो(priv->regmap, STM32_LPTIM_CR, 0);
		वापस ret;
	पूर्ण
	priv->enabled = true;

	/* Start LP समयr in continuous mode */
	वापस regmap_update_bits(priv->regmap, STM32_LPTIM_CR,
				  STM32_LPTIM_CNTSTRT, STM32_LPTIM_CNTSTRT);
पूर्ण

अटल पूर्णांक sपंचांग32_lptim_setup(काष्ठा sपंचांग32_lptim_cnt *priv, पूर्णांक enable)
अणु
	u32 mask = STM32_LPTIM_ENC | STM32_LPTIM_COUNTMODE |
		   STM32_LPTIM_CKPOL | STM32_LPTIM_PRESC;
	u32 val;

	/* Setup LP समयr encoder/counter and polarity, without prescaler */
	अगर (priv->quadrature_mode)
		val = enable ? STM32_LPTIM_ENC : 0;
	अन्यथा
		val = enable ? STM32_LPTIM_COUNTMODE : 0;
	val |= FIELD_PREP(STM32_LPTIM_CKPOL, enable ? priv->polarity : 0);

	वापस regmap_update_bits(priv->regmap, STM32_LPTIM_CFGR, mask, val);
पूर्ण

/**
 * क्रमागत sपंचांग32_lptim_cnt_function - क्रमागतerates LPTimer counter & encoder modes
 * @STM32_LPTIM_COUNTER_INCREASE: up count on IN1 rising, falling or both edges
 * @STM32_LPTIM_ENCODER_BOTH_EDGE: count on both edges (IN1 & IN2 quadrature)
 *
 * In non-quadrature mode, device counts up on active edge.
 * In quadrature mode, encoder counting scenarios are as follows:
 * +---------+----------+--------------------+--------------------+
 * | Active  | Level on |      IN1 संकेत    |     IN2 संकेत     |
 * | edge    | opposite +----------+---------+----------+---------+
 * |         | संकेत   |  Rising  | Falling |  Rising  | Falling |
 * +---------+----------+----------+---------+----------+---------+
 * | Rising  | High ->  |   Down   |    -    |   Up     |    -    |
 * | edge    | Low  ->  |   Up     |    -    |   Down   |    -    |
 * +---------+----------+----------+---------+----------+---------+
 * | Falling | High ->  |    -     |   Up    |    -     |   Down  |
 * | edge    | Low  ->  |    -     |   Down  |    -     |   Up    |
 * +---------+----------+----------+---------+----------+---------+
 * | Both    | High ->  |   Down   |   Up    |   Up     |   Down  |
 * | edges   | Low  ->  |   Up     |   Down  |   Down   |   Up    |
 * +---------+----------+----------+---------+----------+---------+
 */
क्रमागत sपंचांग32_lptim_cnt_function अणु
	STM32_LPTIM_COUNTER_INCREASE,
	STM32_LPTIM_ENCODER_BOTH_EDGE,
पूर्ण;

अटल क्रमागत counter_count_function sपंचांग32_lptim_cnt_functions[] = अणु
	[STM32_LPTIM_COUNTER_INCREASE] = COUNTER_COUNT_FUNCTION_INCREASE,
	[STM32_LPTIM_ENCODER_BOTH_EDGE] = COUNTER_COUNT_FUNCTION_QUADRATURE_X4,
पूर्ण;

क्रमागत sपंचांग32_lptim_synapse_action अणु
	STM32_LPTIM_SYNAPSE_ACTION_RISING_EDGE,
	STM32_LPTIM_SYNAPSE_ACTION_FALLING_EDGE,
	STM32_LPTIM_SYNAPSE_ACTION_BOTH_EDGES,
	STM32_LPTIM_SYNAPSE_ACTION_NONE,
पूर्ण;

अटल क्रमागत counter_synapse_action sपंचांग32_lptim_cnt_synapse_actions[] = अणु
	/* Index must match with sपंचांग32_lptim_cnt_polarity[] (priv->polarity) */
	[STM32_LPTIM_SYNAPSE_ACTION_RISING_EDGE] = COUNTER_SYNAPSE_ACTION_RISING_EDGE,
	[STM32_LPTIM_SYNAPSE_ACTION_FALLING_EDGE] = COUNTER_SYNAPSE_ACTION_FALLING_EDGE,
	[STM32_LPTIM_SYNAPSE_ACTION_BOTH_EDGES] = COUNTER_SYNAPSE_ACTION_BOTH_EDGES,
	[STM32_LPTIM_SYNAPSE_ACTION_NONE] = COUNTER_SYNAPSE_ACTION_NONE,
पूर्ण;

अटल पूर्णांक sपंचांग32_lptim_cnt_पढ़ो(काष्ठा counter_device *counter,
				काष्ठा counter_count *count, अचिन्हित दीर्घ *val)
अणु
	काष्ठा sपंचांग32_lptim_cnt *स्थिर priv = counter->priv;
	u32 cnt;
	पूर्णांक ret;

	ret = regmap_पढ़ो(priv->regmap, STM32_LPTIM_CNT, &cnt);
	अगर (ret)
		वापस ret;

	*val = cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_lptim_cnt_function_get(काष्ठा counter_device *counter,
					काष्ठा counter_count *count,
					माप_प्रकार *function)
अणु
	काष्ठा sपंचांग32_lptim_cnt *स्थिर priv = counter->priv;

	अगर (!priv->quadrature_mode) अणु
		*function = STM32_LPTIM_COUNTER_INCREASE;
		वापस 0;
	पूर्ण

	अगर (priv->polarity == STM32_LPTIM_SYNAPSE_ACTION_BOTH_EDGES) अणु
		*function = STM32_LPTIM_ENCODER_BOTH_EDGE;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_lptim_cnt_function_set(काष्ठा counter_device *counter,
					काष्ठा counter_count *count,
					माप_प्रकार function)
अणु
	काष्ठा sपंचांग32_lptim_cnt *स्थिर priv = counter->priv;

	अगर (sपंचांग32_lptim_is_enabled(priv))
		वापस -EBUSY;

	चयन (function) अणु
	हाल STM32_LPTIM_COUNTER_INCREASE:
		priv->quadrature_mode = 0;
		वापस 0;
	हाल STM32_LPTIM_ENCODER_BOTH_EDGE:
		priv->quadrature_mode = 1;
		priv->polarity = STM32_LPTIM_SYNAPSE_ACTION_BOTH_EDGES;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार sपंचांग32_lptim_cnt_enable_पढ़ो(काष्ठा counter_device *counter,
					   काष्ठा counter_count *count,
					   व्योम *निजी, अक्षर *buf)
अणु
	काष्ठा sपंचांग32_lptim_cnt *स्थिर priv = counter->priv;
	पूर्णांक ret;

	ret = sपंचांग32_lptim_is_enabled(priv);
	अगर (ret < 0)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", ret);
पूर्ण

अटल sमाप_प्रकार sपंचांग32_lptim_cnt_enable_ग_लिखो(काष्ठा counter_device *counter,
					    काष्ठा counter_count *count,
					    व्योम *निजी,
					    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा sपंचांग32_lptim_cnt *स्थिर priv = counter->priv;
	bool enable;
	पूर्णांक ret;

	ret = kstrtobool(buf, &enable);
	अगर (ret)
		वापस ret;

	/* Check nobody uses the समयr, or alपढ़ोy disabled/enabled */
	ret = sपंचांग32_lptim_is_enabled(priv);
	अगर ((ret < 0) || (!ret && !enable))
		वापस ret;
	अगर (enable && ret)
		वापस -EBUSY;

	ret = sपंचांग32_lptim_setup(priv, enable);
	अगर (ret)
		वापस ret;

	ret = sपंचांग32_lptim_set_enable_state(priv, enable);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार sपंचांग32_lptim_cnt_उच्चमानing_पढ़ो(काष्ठा counter_device *counter,
					    काष्ठा counter_count *count,
					    व्योम *निजी, अक्षर *buf)
अणु
	काष्ठा sपंचांग32_lptim_cnt *स्थिर priv = counter->priv;

	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", priv->उच्चमानing);
पूर्ण

अटल sमाप_प्रकार sपंचांग32_lptim_cnt_उच्चमानing_ग_लिखो(काष्ठा counter_device *counter,
					     काष्ठा counter_count *count,
					     व्योम *निजी,
					     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा sपंचांग32_lptim_cnt *स्थिर priv = counter->priv;
	अचिन्हित पूर्णांक उच्चमानing;
	पूर्णांक ret;

	अगर (sपंचांग32_lptim_is_enabled(priv))
		वापस -EBUSY;

	ret = kstrtouपूर्णांक(buf, 0, &उच्चमानing);
	अगर (ret)
		वापस ret;

	अगर (उच्चमानing > STM32_LPTIM_MAX_ARR)
		वापस -EINVAL;

	priv->उच्चमानing = उच्चमानing;

	वापस len;
पूर्ण

अटल स्थिर काष्ठा counter_count_ext sपंचांग32_lptim_cnt_ext[] = अणु
	अणु
		.name = "enable",
		.पढ़ो = sपंचांग32_lptim_cnt_enable_पढ़ो,
		.ग_लिखो = sपंचांग32_lptim_cnt_enable_ग_लिखो
	पूर्ण,
	अणु
		.name = "ceiling",
		.पढ़ो = sपंचांग32_lptim_cnt_उच्चमानing_पढ़ो,
		.ग_लिखो = sपंचांग32_lptim_cnt_उच्चमानing_ग_लिखो
	पूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांग32_lptim_cnt_action_get(काष्ठा counter_device *counter,
				      काष्ठा counter_count *count,
				      काष्ठा counter_synapse *synapse,
				      माप_प्रकार *action)
अणु
	काष्ठा sपंचांग32_lptim_cnt *स्थिर priv = counter->priv;
	माप_प्रकार function;
	पूर्णांक err;

	err = sपंचांग32_lptim_cnt_function_get(counter, count, &function);
	अगर (err)
		वापस err;

	चयन (function) अणु
	हाल STM32_LPTIM_COUNTER_INCREASE:
		/* LP Timer acts as up-counter on input 1 */
		अगर (synapse->संकेत->id == count->synapses[0].संकेत->id)
			*action = priv->polarity;
		अन्यथा
			*action = STM32_LPTIM_SYNAPSE_ACTION_NONE;
		वापस 0;
	हाल STM32_LPTIM_ENCODER_BOTH_EDGE:
		*action = priv->polarity;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_lptim_cnt_action_set(काष्ठा counter_device *counter,
				      काष्ठा counter_count *count,
				      काष्ठा counter_synapse *synapse,
				      माप_प्रकार action)
अणु
	काष्ठा sपंचांग32_lptim_cnt *स्थिर priv = counter->priv;
	माप_प्रकार function;
	पूर्णांक err;

	अगर (sपंचांग32_lptim_is_enabled(priv))
		वापस -EBUSY;

	err = sपंचांग32_lptim_cnt_function_get(counter, count, &function);
	अगर (err)
		वापस err;

	/* only set polarity when in counter mode (on input 1) */
	अगर (function == STM32_LPTIM_COUNTER_INCREASE
	    && synapse->संकेत->id == count->synapses[0].संकेत->id) अणु
		चयन (action) अणु
		हाल STM32_LPTIM_SYNAPSE_ACTION_RISING_EDGE:
		हाल STM32_LPTIM_SYNAPSE_ACTION_FALLING_EDGE:
		हाल STM32_LPTIM_SYNAPSE_ACTION_BOTH_EDGES:
			priv->polarity = action;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा counter_ops sपंचांग32_lptim_cnt_ops = अणु
	.count_पढ़ो = sपंचांग32_lptim_cnt_पढ़ो,
	.function_get = sपंचांग32_lptim_cnt_function_get,
	.function_set = sपंचांग32_lptim_cnt_function_set,
	.action_get = sपंचांग32_lptim_cnt_action_get,
	.action_set = sपंचांग32_lptim_cnt_action_set,
पूर्ण;

अटल काष्ठा counter_संकेत sपंचांग32_lptim_cnt_संकेतs[] = अणु
	अणु
		.id = 0,
		.name = "Channel 1 Quadrature A"
	पूर्ण,
	अणु
		.id = 1,
		.name = "Channel 1 Quadrature B"
	पूर्ण
पूर्ण;

अटल काष्ठा counter_synapse sपंचांग32_lptim_cnt_synapses[] = अणु
	अणु
		.actions_list = sपंचांग32_lptim_cnt_synapse_actions,
		.num_actions = ARRAY_SIZE(sपंचांग32_lptim_cnt_synapse_actions),
		.संकेत = &sपंचांग32_lptim_cnt_संकेतs[0]
	पूर्ण,
	अणु
		.actions_list = sपंचांग32_lptim_cnt_synapse_actions,
		.num_actions = ARRAY_SIZE(sपंचांग32_lptim_cnt_synapse_actions),
		.संकेत = &sपंचांग32_lptim_cnt_संकेतs[1]
	पूर्ण
पूर्ण;

/* LP समयr with encoder */
अटल काष्ठा counter_count sपंचांग32_lptim_enc_counts = अणु
	.id = 0,
	.name = "LPTimer Count",
	.functions_list = sपंचांग32_lptim_cnt_functions,
	.num_functions = ARRAY_SIZE(sपंचांग32_lptim_cnt_functions),
	.synapses = sपंचांग32_lptim_cnt_synapses,
	.num_synapses = ARRAY_SIZE(sपंचांग32_lptim_cnt_synapses),
	.ext = sपंचांग32_lptim_cnt_ext,
	.num_ext = ARRAY_SIZE(sपंचांग32_lptim_cnt_ext)
पूर्ण;

/* LP समयr without encoder (counter only) */
अटल काष्ठा counter_count sपंचांग32_lptim_in1_counts = अणु
	.id = 0,
	.name = "LPTimer Count",
	.functions_list = sपंचांग32_lptim_cnt_functions,
	.num_functions = 1,
	.synapses = sपंचांग32_lptim_cnt_synapses,
	.num_synapses = 1,
	.ext = sपंचांग32_lptim_cnt_ext,
	.num_ext = ARRAY_SIZE(sपंचांग32_lptim_cnt_ext)
पूर्ण;

अटल पूर्णांक sपंचांग32_lptim_cnt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_lpसमयr *ddata = dev_get_drvdata(pdev->dev.parent);
	काष्ठा sपंचांग32_lptim_cnt *priv;

	अगर (IS_ERR_OR_शून्य(ddata))
		वापस -EINVAL;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = &pdev->dev;
	priv->regmap = ddata->regmap;
	priv->clk = ddata->clk;
	priv->उच्चमानing = STM32_LPTIM_MAX_ARR;

	/* Initialize Counter device */
	priv->counter.name = dev_name(&pdev->dev);
	priv->counter.parent = &pdev->dev;
	priv->counter.ops = &sपंचांग32_lptim_cnt_ops;
	अगर (ddata->has_encoder) अणु
		priv->counter.counts = &sपंचांग32_lptim_enc_counts;
		priv->counter.num_संकेतs = ARRAY_SIZE(sपंचांग32_lptim_cnt_संकेतs);
	पूर्ण अन्यथा अणु
		priv->counter.counts = &sपंचांग32_lptim_in1_counts;
		priv->counter.num_संकेतs = 1;
	पूर्ण
	priv->counter.num_counts = 1;
	priv->counter.संकेतs = sपंचांग32_lptim_cnt_संकेतs;
	priv->counter.priv = priv;

	platक्रमm_set_drvdata(pdev, priv);

	वापस devm_counter_रेजिस्टर(&pdev->dev, &priv->counter);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांग32_lptim_cnt_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_lptim_cnt *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* Only take care of enabled counter: करोn't disturb other MFD child */
	अगर (priv->enabled) अणु
		ret = sपंचांग32_lptim_setup(priv, 0);
		अगर (ret)
			वापस ret;

		ret = sपंचांग32_lptim_set_enable_state(priv, 0);
		अगर (ret)
			वापस ret;

		/* Force enable state क्रम later resume */
		priv->enabled = true;
	पूर्ण

	वापस pinctrl_pm_select_sleep_state(dev);
पूर्ण

अटल पूर्णांक sपंचांग32_lptim_cnt_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_lptim_cnt *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pinctrl_pm_select_शेष_state(dev);
	अगर (ret)
		वापस ret;

	अगर (priv->enabled) अणु
		priv->enabled = false;
		ret = sपंचांग32_lptim_setup(priv, 1);
		अगर (ret)
			वापस ret;

		ret = sपंचांग32_lptim_set_enable_state(priv, 1);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(sपंचांग32_lptim_cnt_pm_ops, sपंचांग32_lptim_cnt_suspend,
			 sपंचांग32_lptim_cnt_resume);

अटल स्थिर काष्ठा of_device_id sपंचांग32_lptim_cnt_of_match[] = अणु
	अणु .compatible = "st,stm32-lptimer-counter", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_lptim_cnt_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_lptim_cnt_driver = अणु
	.probe = sपंचांग32_lptim_cnt_probe,
	.driver = अणु
		.name = "stm32-lptimer-counter",
		.of_match_table = sपंचांग32_lptim_cnt_of_match,
		.pm = &sपंचांग32_lptim_cnt_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_lptim_cnt_driver);

MODULE_AUTHOR("Fabrice Gasnier <fabrice.gasnier@st.com>");
MODULE_ALIAS("platform:stm32-lptimer-counter");
MODULE_DESCRIPTION("STMicroelectronics STM32 LPTIM counter driver");
MODULE_LICENSE("GPL v2");
