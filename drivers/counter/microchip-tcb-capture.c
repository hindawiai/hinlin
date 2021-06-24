<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * Copyright (C) 2020 Microchip
 *
 * Author: Kamel Bouhara <kamel.bouhara@bootlin.com>
 */
#समावेश <linux/clk.h>
#समावेश <linux/counter.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <soc/at91/aपंचांगel_tcb.h>

#घोषणा ATMEL_TC_CMR_MASK	(ATMEL_TC_LDRA_RISING | ATMEL_TC_LDRB_FALLING | \
				 ATMEL_TC_ETRGEDG_RISING | ATMEL_TC_LDBDIS | \
				 ATMEL_TC_LDBSTOP)

#घोषणा ATMEL_TC_QDEN			BIT(8)
#घोषणा ATMEL_TC_POSEN			BIT(9)

काष्ठा mchp_tc_data अणु
	स्थिर काष्ठा aपंचांगel_tcb_config *tc_cfg;
	काष्ठा counter_device counter;
	काष्ठा regmap *regmap;
	पूर्णांक qdec_mode;
	पूर्णांक num_channels;
	पूर्णांक channel[2];
	bool trig_inverted;
पूर्ण;

क्रमागत mchp_tc_count_function अणु
	MCHP_TC_FUNCTION_INCREASE,
	MCHP_TC_FUNCTION_QUADRATURE,
पूर्ण;

अटल क्रमागत counter_count_function mchp_tc_count_functions[] = अणु
	[MCHP_TC_FUNCTION_INCREASE] = COUNTER_COUNT_FUNCTION_INCREASE,
	[MCHP_TC_FUNCTION_QUADRATURE] = COUNTER_COUNT_FUNCTION_QUADRATURE_X4,
पूर्ण;

क्रमागत mchp_tc_synapse_action अणु
	MCHP_TC_SYNAPSE_ACTION_NONE = 0,
	MCHP_TC_SYNAPSE_ACTION_RISING_EDGE,
	MCHP_TC_SYNAPSE_ACTION_FALLING_EDGE,
	MCHP_TC_SYNAPSE_ACTION_BOTH_EDGE
पूर्ण;

अटल क्रमागत counter_synapse_action mchp_tc_synapse_actions[] = अणु
	[MCHP_TC_SYNAPSE_ACTION_NONE] = COUNTER_SYNAPSE_ACTION_NONE,
	[MCHP_TC_SYNAPSE_ACTION_RISING_EDGE] = COUNTER_SYNAPSE_ACTION_RISING_EDGE,
	[MCHP_TC_SYNAPSE_ACTION_FALLING_EDGE] = COUNTER_SYNAPSE_ACTION_FALLING_EDGE,
	[MCHP_TC_SYNAPSE_ACTION_BOTH_EDGE] = COUNTER_SYNAPSE_ACTION_BOTH_EDGES,
पूर्ण;

अटल काष्ठा counter_संकेत mchp_tc_count_संकेतs[] = अणु
	अणु
		.id = 0,
		.name = "Channel A",
	पूर्ण,
	अणु
		.id = 1,
		.name = "Channel B",
	पूर्ण
पूर्ण;

अटल काष्ठा counter_synapse mchp_tc_count_synapses[] = अणु
	अणु
		.actions_list = mchp_tc_synapse_actions,
		.num_actions = ARRAY_SIZE(mchp_tc_synapse_actions),
		.संकेत = &mchp_tc_count_संकेतs[0]
	पूर्ण,
	अणु
		.actions_list = mchp_tc_synapse_actions,
		.num_actions = ARRAY_SIZE(mchp_tc_synapse_actions),
		.संकेत = &mchp_tc_count_संकेतs[1]
	पूर्ण
पूर्ण;

अटल पूर्णांक mchp_tc_count_function_get(काष्ठा counter_device *counter,
				      काष्ठा counter_count *count,
				      माप_प्रकार *function)
अणु
	काष्ठा mchp_tc_data *स्थिर priv = counter->priv;

	अगर (priv->qdec_mode)
		*function = MCHP_TC_FUNCTION_QUADRATURE;
	अन्यथा
		*function = MCHP_TC_FUNCTION_INCREASE;

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_tc_count_function_set(काष्ठा counter_device *counter,
				      काष्ठा counter_count *count,
				      माप_प्रकार function)
अणु
	काष्ठा mchp_tc_data *स्थिर priv = counter->priv;
	u32 bmr, cmr;

	regmap_पढ़ो(priv->regmap, ATMEL_TC_BMR, &bmr);
	regmap_पढ़ो(priv->regmap, ATMEL_TC_REG(priv->channel[0], CMR), &cmr);

	/* Set capture mode */
	cmr &= ~ATMEL_TC_WAVE;

	चयन (function) अणु
	हाल MCHP_TC_FUNCTION_INCREASE:
		priv->qdec_mode = 0;
		/* Set highest rate based on whether soc has gclk or not */
		bmr &= ~(ATMEL_TC_QDEN | ATMEL_TC_POSEN);
		अगर (priv->tc_cfg->has_gclk)
			cmr |= ATMEL_TC_TIMER_CLOCK2;
		अन्यथा
			cmr |= ATMEL_TC_TIMER_CLOCK1;
		/* Setup the period capture mode */
		cmr |=  ATMEL_TC_CMR_MASK;
		cmr &= ~(ATMEL_TC_ABETRG | ATMEL_TC_XC0);
		अवरोध;
	हाल MCHP_TC_FUNCTION_QUADRATURE:
		अगर (!priv->tc_cfg->has_qdec)
			वापस -EINVAL;
		/* In QDEC mode settings both channels 0 and 1 are required */
		अगर (priv->num_channels < 2 || priv->channel[0] != 0 ||
		    priv->channel[1] != 1) अणु
			pr_err("Invalid channels number or id for quadrature mode\n");
			वापस -EINVAL;
		पूर्ण
		priv->qdec_mode = 1;
		bmr |= ATMEL_TC_QDEN | ATMEL_TC_POSEN;
		cmr |= ATMEL_TC_ETRGEDG_RISING | ATMEL_TC_ABETRG | ATMEL_TC_XC0;
		अवरोध;
	पूर्ण

	regmap_ग_लिखो(priv->regmap, ATMEL_TC_BMR, bmr);
	regmap_ग_लिखो(priv->regmap, ATMEL_TC_REG(priv->channel[0], CMR), cmr);

	/* Enable घड़ी and trigger counter */
	regmap_ग_लिखो(priv->regmap, ATMEL_TC_REG(priv->channel[0], CCR),
		     ATMEL_TC_CLKEN | ATMEL_TC_SWTRG);

	अगर (priv->qdec_mode) अणु
		regmap_ग_लिखो(priv->regmap,
			     ATMEL_TC_REG(priv->channel[1], CMR), cmr);
		regmap_ग_लिखो(priv->regmap,
			     ATMEL_TC_REG(priv->channel[1], CCR),
			     ATMEL_TC_CLKEN | ATMEL_TC_SWTRG);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_tc_count_संकेत_पढ़ो(काष्ठा counter_device *counter,
				     काष्ठा counter_संकेत *संकेत,
				     क्रमागत counter_संकेत_value *val)
अणु
	काष्ठा mchp_tc_data *स्थिर priv = counter->priv;
	bool sigstatus;
	u32 sr;

	regmap_पढ़ो(priv->regmap, ATMEL_TC_REG(priv->channel[0], SR), &sr);

	अगर (priv->trig_inverted)
		sigstatus = (sr & ATMEL_TC_MTIOB);
	अन्यथा
		sigstatus = (sr & ATMEL_TC_MTIOA);

	*val = sigstatus ? COUNTER_SIGNAL_HIGH : COUNTER_SIGNAL_LOW;

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_tc_count_action_get(काष्ठा counter_device *counter,
				    काष्ठा counter_count *count,
				    काष्ठा counter_synapse *synapse,
				    माप_प्रकार *action)
अणु
	काष्ठा mchp_tc_data *स्थिर priv = counter->priv;
	u32 cmr;

	regmap_पढ़ो(priv->regmap, ATMEL_TC_REG(priv->channel[0], CMR), &cmr);

	चयन (cmr & ATMEL_TC_ETRGEDG) अणु
	शेष:
		*action = MCHP_TC_SYNAPSE_ACTION_NONE;
		अवरोध;
	हाल ATMEL_TC_ETRGEDG_RISING:
		*action = MCHP_TC_SYNAPSE_ACTION_RISING_EDGE;
		अवरोध;
	हाल ATMEL_TC_ETRGEDG_FALLING:
		*action = MCHP_TC_SYNAPSE_ACTION_FALLING_EDGE;
		अवरोध;
	हाल ATMEL_TC_ETRGEDG_BOTH:
		*action = MCHP_TC_SYNAPSE_ACTION_BOTH_EDGE;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_tc_count_action_set(काष्ठा counter_device *counter,
				    काष्ठा counter_count *count,
				    काष्ठा counter_synapse *synapse,
				    माप_प्रकार action)
अणु
	काष्ठा mchp_tc_data *स्थिर priv = counter->priv;
	u32 edge = ATMEL_TC_ETRGEDG_NONE;

	/* QDEC mode is rising edge only */
	अगर (priv->qdec_mode)
		वापस -EINVAL;

	चयन (action) अणु
	हाल MCHP_TC_SYNAPSE_ACTION_NONE:
		edge = ATMEL_TC_ETRGEDG_NONE;
		अवरोध;
	हाल MCHP_TC_SYNAPSE_ACTION_RISING_EDGE:
		edge = ATMEL_TC_ETRGEDG_RISING;
		अवरोध;
	हाल MCHP_TC_SYNAPSE_ACTION_FALLING_EDGE:
		edge = ATMEL_TC_ETRGEDG_FALLING;
		अवरोध;
	हाल MCHP_TC_SYNAPSE_ACTION_BOTH_EDGE:
		edge = ATMEL_TC_ETRGEDG_BOTH;
		अवरोध;
	पूर्ण

	वापस regmap_ग_लिखो_bits(priv->regmap,
				ATMEL_TC_REG(priv->channel[0], CMR),
				ATMEL_TC_ETRGEDG, edge);
पूर्ण

अटल पूर्णांक mchp_tc_count_पढ़ो(काष्ठा counter_device *counter,
			      काष्ठा counter_count *count,
			      अचिन्हित दीर्घ *val)
अणु
	काष्ठा mchp_tc_data *स्थिर priv = counter->priv;
	u32 cnt;

	regmap_पढ़ो(priv->regmap, ATMEL_TC_REG(priv->channel[0], CV), &cnt);
	*val = cnt;

	वापस 0;
पूर्ण

अटल काष्ठा counter_count mchp_tc_counts[] = अणु
	अणु
		.id = 0,
		.name = "Timer Counter",
		.functions_list = mchp_tc_count_functions,
		.num_functions = ARRAY_SIZE(mchp_tc_count_functions),
		.synapses = mchp_tc_count_synapses,
		.num_synapses = ARRAY_SIZE(mchp_tc_count_synapses),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा counter_ops mchp_tc_ops = अणु
	.संकेत_पढ़ो  = mchp_tc_count_संकेत_पढ़ो,
	.count_पढ़ो   = mchp_tc_count_पढ़ो,
	.function_get = mchp_tc_count_function_get,
	.function_set = mchp_tc_count_function_set,
	.action_get   = mchp_tc_count_action_get,
	.action_set   = mchp_tc_count_action_set
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_tcb_config tcb_rm9200_config = अणु
		.counter_width = 16,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_tcb_config tcb_sam9x5_config = अणु
		.counter_width = 32,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_tcb_config tcb_sama5d2_config = अणु
		.counter_width = 32,
		.has_gclk = true,
		.has_qdec = true,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_tcb_config tcb_sama5d3_config = अणु
		.counter_width = 32,
		.has_qdec = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_tc_of_match[] = अणु
	अणु .compatible = "atmel,at91rm9200-tcb", .data = &tcb_rm9200_config, पूर्ण,
	अणु .compatible = "atmel,at91sam9x5-tcb", .data = &tcb_sam9x5_config, पूर्ण,
	अणु .compatible = "atmel,sama5d2-tcb", .data = &tcb_sama5d2_config, पूर्ण,
	अणु .compatible = "atmel,sama5d3-tcb", .data = &tcb_sama5d3_config, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल व्योम mchp_tc_clk_हटाओ(व्योम *ptr)
अणु
	clk_disable_unprepare((काष्ठा clk *)ptr);
पूर्ण

अटल पूर्णांक mchp_tc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा aपंचांगel_tcb_config *tcb_config;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा mchp_tc_data *priv;
	अक्षर clk_name[7];
	काष्ठा regmap *regmap;
	काष्ठा clk *clk[3];
	पूर्णांक channel;
	पूर्णांक ret, i;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	match = of_match_node(aपंचांगel_tc_of_match, np->parent);
	tcb_config = match->data;
	अगर (!tcb_config) अणु
		dev_err(&pdev->dev, "No matching parent node found\n");
		वापस -ENODEV;
	पूर्ण

	regmap = syscon_node_to_regmap(np->parent);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* max. channels number is 2 when in QDEC mode */
	priv->num_channels = of_property_count_u32_elems(np, "reg");
	अगर (priv->num_channels < 0) अणु
		dev_err(&pdev->dev, "Invalid or missing channel\n");
		वापस -EINVAL;
	पूर्ण

	/* Register channels and initialize घड़ीs */
	क्रम (i = 0; i < priv->num_channels; i++) अणु
		ret = of_property_पढ़ो_u32_index(np, "reg", i, &channel);
		अगर (ret < 0 || channel > 2)
			वापस -ENODEV;

		priv->channel[i] = channel;

		snम_लिखो(clk_name, माप(clk_name), "t%d_clk", channel);

		clk[i] = of_clk_get_by_name(np->parent, clk_name);
		अगर (IS_ERR(clk[i])) अणु
			/* Fallback to t0_clk */
			clk[i] = of_clk_get_by_name(np->parent, "t0_clk");
			अगर (IS_ERR(clk[i]))
				वापस PTR_ERR(clk[i]);
		पूर्ण

		ret = clk_prepare_enable(clk[i]);
		अगर (ret)
			वापस ret;

		ret = devm_add_action_or_reset(&pdev->dev,
					       mchp_tc_clk_हटाओ,
					       clk[i]);
		अगर (ret)
			वापस ret;

		dev_dbg(&pdev->dev,
			"Initialized capture mode on channel %d\n",
			channel);
	पूर्ण

	priv->tc_cfg = tcb_config;
	priv->regmap = regmap;
	priv->counter.name = dev_name(&pdev->dev);
	priv->counter.parent = &pdev->dev;
	priv->counter.ops = &mchp_tc_ops;
	priv->counter.num_counts = ARRAY_SIZE(mchp_tc_counts);
	priv->counter.counts = mchp_tc_counts;
	priv->counter.num_संकेतs = ARRAY_SIZE(mchp_tc_count_संकेतs);
	priv->counter.संकेतs = mchp_tc_count_संकेतs;
	priv->counter.priv = priv;

	वापस devm_counter_रेजिस्टर(&pdev->dev, &priv->counter);
पूर्ण

अटल स्थिर काष्ठा of_device_id mchp_tc_dt_ids[] = अणु
	अणु .compatible = "microchip,tcb-capture", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mchp_tc_dt_ids);

अटल काष्ठा platक्रमm_driver mchp_tc_driver = अणु
	.probe = mchp_tc_probe,
	.driver = अणु
		.name = "microchip-tcb-capture",
		.of_match_table = mchp_tc_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mchp_tc_driver);

MODULE_AUTHOR("Kamel Bouhara <kamel.bouhara@bootlin.com>");
MODULE_DESCRIPTION("Microchip TCB Capture driver");
MODULE_LICENSE("GPL v2");
