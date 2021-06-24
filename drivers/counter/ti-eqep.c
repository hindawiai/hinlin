<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2019 David Lechner <david@lechnology.com>
 *
 * Counter driver क्रम Texas Instruments Enhanced Quadrature Encoder Pulse (eQEP)
 */

#समावेश <linux/bitops.h>
#समावेश <linux/counter.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

/* 32-bit रेजिस्टरs */
#घोषणा QPOSCNT		0x0
#घोषणा QPOSINIT	0x4
#घोषणा QPOSMAX		0x8
#घोषणा QPOSCMP		0xc
#घोषणा QPOSILAT	0x10
#घोषणा QPOSSLAT	0x14
#घोषणा QPOSLAT		0x18
#घोषणा QUTMR		0x1c
#घोषणा QUPRD		0x20

/* 16-bit रेजिस्टरs */
#घोषणा QWDTMR		0x0	/* 0x24 */
#घोषणा QWDPRD		0x2	/* 0x26 */
#घोषणा QDECCTL		0x4	/* 0x28 */
#घोषणा QEPCTL		0x6	/* 0x2a */
#घोषणा QCAPCTL		0x8	/* 0x2c */
#घोषणा QPOSCTL		0xa	/* 0x2e */
#घोषणा QEINT		0xc	/* 0x30 */
#घोषणा QFLG		0xe	/* 0x32 */
#घोषणा QCLR		0x10	/* 0x34 */
#घोषणा QFRC		0x12	/* 0x36 */
#घोषणा QEPSTS		0x14	/* 0x38 */
#घोषणा QCTMR		0x16	/* 0x3a */
#घोषणा QCPRD		0x18	/* 0x3c */
#घोषणा QCTMRLAT	0x1a	/* 0x3e */
#घोषणा QCPRDLAT	0x1c	/* 0x40 */

#घोषणा QDECCTL_QSRC_SHIFT	14
#घोषणा QDECCTL_QSRC		GENMASK(15, 14)
#घोषणा QDECCTL_SOEN		BIT(13)
#घोषणा QDECCTL_SPSEL		BIT(12)
#घोषणा QDECCTL_XCR		BIT(11)
#घोषणा QDECCTL_SWAP		BIT(10)
#घोषणा QDECCTL_IGATE		BIT(9)
#घोषणा QDECCTL_QAP		BIT(8)
#घोषणा QDECCTL_QBP		BIT(7)
#घोषणा QDECCTL_QIP		BIT(6)
#घोषणा QDECCTL_QSP		BIT(5)

#घोषणा QEPCTL_FREE_SOFT	GENMASK(15, 14)
#घोषणा QEPCTL_PCRM		GENMASK(13, 12)
#घोषणा QEPCTL_SEI		GENMASK(11, 10)
#घोषणा QEPCTL_IEI		GENMASK(9, 8)
#घोषणा QEPCTL_SWI		BIT(7)
#घोषणा QEPCTL_SEL		BIT(6)
#घोषणा QEPCTL_IEL		GENMASK(5, 4)
#घोषणा QEPCTL_PHEN		BIT(3)
#घोषणा QEPCTL_QCLM		BIT(2)
#घोषणा QEPCTL_UTE		BIT(1)
#घोषणा QEPCTL_WDE		BIT(0)

/* EQEP Inमाला_दो */
क्रमागत अणु
	TI_EQEP_SIGNAL_QEPA,	/* QEPA/XCLK */
	TI_EQEP_SIGNAL_QEPB,	/* QEPB/Xसूची */
पूर्ण;

/* Position Counter Input Modes */
क्रमागत अणु
	TI_EQEP_COUNT_FUNC_QUAD_COUNT,
	TI_EQEP_COUNT_FUNC_सूची_COUNT,
	TI_EQEP_COUNT_FUNC_UP_COUNT,
	TI_EQEP_COUNT_FUNC_DOWN_COUNT,
पूर्ण;

क्रमागत अणु
	TI_EQEP_SYNAPSE_ACTION_BOTH_EDGES,
	TI_EQEP_SYNAPSE_ACTION_RISING_EDGE,
	TI_EQEP_SYNAPSE_ACTION_NONE,
पूर्ण;

काष्ठा ti_eqep_cnt अणु
	काष्ठा counter_device counter;
	काष्ठा regmap *regmap32;
	काष्ठा regmap *regmap16;
पूर्ण;

अटल पूर्णांक ti_eqep_count_पढ़ो(काष्ठा counter_device *counter,
			      काष्ठा counter_count *count, अचिन्हित दीर्घ *val)
अणु
	काष्ठा ti_eqep_cnt *priv = counter->priv;
	u32 cnt;

	regmap_पढ़ो(priv->regmap32, QPOSCNT, &cnt);
	*val = cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक ti_eqep_count_ग_लिखो(काष्ठा counter_device *counter,
			       काष्ठा counter_count *count, अचिन्हित दीर्घ val)
अणु
	काष्ठा ti_eqep_cnt *priv = counter->priv;
	u32 max;

	regmap_पढ़ो(priv->regmap32, QPOSMAX, &max);
	अगर (val > max)
		वापस -EINVAL;

	वापस regmap_ग_लिखो(priv->regmap32, QPOSCNT, val);
पूर्ण

अटल पूर्णांक ti_eqep_function_get(काष्ठा counter_device *counter,
				काष्ठा counter_count *count, माप_प्रकार *function)
अणु
	काष्ठा ti_eqep_cnt *priv = counter->priv;
	u32 qdecctl;

	regmap_पढ़ो(priv->regmap16, QDECCTL, &qdecctl);
	*function = (qdecctl & QDECCTL_QSRC) >> QDECCTL_QSRC_SHIFT;

	वापस 0;
पूर्ण

अटल पूर्णांक ti_eqep_function_set(काष्ठा counter_device *counter,
				काष्ठा counter_count *count, माप_प्रकार function)
अणु
	काष्ठा ti_eqep_cnt *priv = counter->priv;

	वापस regmap_ग_लिखो_bits(priv->regmap16, QDECCTL, QDECCTL_QSRC,
				 function << QDECCTL_QSRC_SHIFT);
पूर्ण

अटल पूर्णांक ti_eqep_action_get(काष्ठा counter_device *counter,
			      काष्ठा counter_count *count,
			      काष्ठा counter_synapse *synapse, माप_प्रकार *action)
अणु
	काष्ठा ti_eqep_cnt *priv = counter->priv;
	माप_प्रकार function;
	u32 qdecctl;
	पूर्णांक err;

	err = ti_eqep_function_get(counter, count, &function);
	अगर (err)
		वापस err;

	चयन (function) अणु
	हाल TI_EQEP_COUNT_FUNC_QUAD_COUNT:
		/* In quadrature mode, the rising and falling edge of both
		 * QEPA and QEPB trigger QCLK.
		 */
		*action = TI_EQEP_SYNAPSE_ACTION_BOTH_EDGES;
		अवरोध;
	हाल TI_EQEP_COUNT_FUNC_सूची_COUNT:
		/* In direction-count mode only rising edge of QEPA is counted
		 * and QEPB gives direction.
		 */
		चयन (synapse->संकेत->id) अणु
		हाल TI_EQEP_SIGNAL_QEPA:
			*action = TI_EQEP_SYNAPSE_ACTION_RISING_EDGE;
			अवरोध;
		शेष:
			*action = TI_EQEP_SYNAPSE_ACTION_NONE;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल TI_EQEP_COUNT_FUNC_UP_COUNT:
	हाल TI_EQEP_COUNT_FUNC_DOWN_COUNT:
		/* In up/करोwn-count modes only QEPA is counted and QEPB is not
		 * used.
		 */
		चयन (synapse->संकेत->id) अणु
		हाल TI_EQEP_SIGNAL_QEPA:
			err = regmap_पढ़ो(priv->regmap16, QDECCTL, &qdecctl);
			अगर (err)
				वापस err;

			अगर (qdecctl & QDECCTL_XCR)
				*action = TI_EQEP_SYNAPSE_ACTION_BOTH_EDGES;
			अन्यथा
				*action = TI_EQEP_SYNAPSE_ACTION_RISING_EDGE;
			अवरोध;
		शेष:
			*action = TI_EQEP_SYNAPSE_ACTION_NONE;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा counter_ops ti_eqep_counter_ops = अणु
	.count_पढ़ो	= ti_eqep_count_पढ़ो,
	.count_ग_लिखो	= ti_eqep_count_ग_लिखो,
	.function_get	= ti_eqep_function_get,
	.function_set	= ti_eqep_function_set,
	.action_get	= ti_eqep_action_get,
पूर्ण;

अटल sमाप_प्रकार ti_eqep_position_उच्चमानing_पढ़ो(काष्ठा counter_device *counter,
					     काष्ठा counter_count *count,
					     व्योम *ext_priv, अक्षर *buf)
अणु
	काष्ठा ti_eqep_cnt *priv = counter->priv;
	u32 qposmax;

	regmap_पढ़ो(priv->regmap32, QPOSMAX, &qposmax);

	वापस प्र_लिखो(buf, "%u\n", qposmax);
पूर्ण

अटल sमाप_प्रकार ti_eqep_position_उच्चमानing_ग_लिखो(काष्ठा counter_device *counter,
					      काष्ठा counter_count *count,
					      व्योम *ext_priv, स्थिर अक्षर *buf,
					      माप_प्रकार len)
अणु
	काष्ठा ti_eqep_cnt *priv = counter->priv;
	पूर्णांक err;
	u32 res;

	err = kstrtouपूर्णांक(buf, 0, &res);
	अगर (err < 0)
		वापस err;

	regmap_ग_लिखो(priv->regmap32, QPOSMAX, res);

	वापस len;
पूर्ण

अटल sमाप_प्रकार ti_eqep_position_enable_पढ़ो(काष्ठा counter_device *counter,
					    काष्ठा counter_count *count,
					    व्योम *ext_priv, अक्षर *buf)
अणु
	काष्ठा ti_eqep_cnt *priv = counter->priv;
	u32 qepctl;

	regmap_पढ़ो(priv->regmap16, QEPCTL, &qepctl);

	वापस प्र_लिखो(buf, "%u\n", !!(qepctl & QEPCTL_PHEN));
पूर्ण

अटल sमाप_प्रकार ti_eqep_position_enable_ग_लिखो(काष्ठा counter_device *counter,
					     काष्ठा counter_count *count,
					     व्योम *ext_priv, स्थिर अक्षर *buf,
					     माप_प्रकार len)
अणु
	काष्ठा ti_eqep_cnt *priv = counter->priv;
	पूर्णांक err;
	bool res;

	err = kstrtobool(buf, &res);
	अगर (err < 0)
		वापस err;

	regmap_ग_लिखो_bits(priv->regmap16, QEPCTL, QEPCTL_PHEN, res ? -1 : 0);

	वापस len;
पूर्ण

अटल काष्ठा counter_count_ext ti_eqep_position_ext[] = अणु
	अणु
		.name	= "ceiling",
		.पढ़ो	= ti_eqep_position_उच्चमानing_पढ़ो,
		.ग_लिखो	= ti_eqep_position_उच्चमानing_ग_लिखो,
	पूर्ण,
	अणु
		.name	= "enable",
		.पढ़ो	= ti_eqep_position_enable_पढ़ो,
		.ग_लिखो	= ti_eqep_position_enable_ग_लिखो,
	पूर्ण,
पूर्ण;

अटल काष्ठा counter_संकेत ti_eqep_संकेतs[] = अणु
	[TI_EQEP_SIGNAL_QEPA] = अणु
		.id = TI_EQEP_SIGNAL_QEPA,
		.name = "QEPA"
	पूर्ण,
	[TI_EQEP_SIGNAL_QEPB] = अणु
		.id = TI_EQEP_SIGNAL_QEPB,
		.name = "QEPB"
	पूर्ण,
पूर्ण;

अटल स्थिर क्रमागत counter_count_function ti_eqep_position_functions[] = अणु
	[TI_EQEP_COUNT_FUNC_QUAD_COUNT]	= COUNTER_COUNT_FUNCTION_QUADRATURE_X4,
	[TI_EQEP_COUNT_FUNC_सूची_COUNT]	= COUNTER_COUNT_FUNCTION_PULSE_सूचीECTION,
	[TI_EQEP_COUNT_FUNC_UP_COUNT]	= COUNTER_COUNT_FUNCTION_INCREASE,
	[TI_EQEP_COUNT_FUNC_DOWN_COUNT]	= COUNTER_COUNT_FUNCTION_DECREASE,
पूर्ण;

अटल स्थिर क्रमागत counter_synapse_action ti_eqep_position_synapse_actions[] = अणु
	[TI_EQEP_SYNAPSE_ACTION_BOTH_EDGES]	= COUNTER_SYNAPSE_ACTION_BOTH_EDGES,
	[TI_EQEP_SYNAPSE_ACTION_RISING_EDGE]	= COUNTER_SYNAPSE_ACTION_RISING_EDGE,
	[TI_EQEP_SYNAPSE_ACTION_NONE]		= COUNTER_SYNAPSE_ACTION_NONE,
पूर्ण;

अटल काष्ठा counter_synapse ti_eqep_position_synapses[] = अणु
	अणु
		.actions_list	= ti_eqep_position_synapse_actions,
		.num_actions	= ARRAY_SIZE(ti_eqep_position_synapse_actions),
		.संकेत		= &ti_eqep_संकेतs[TI_EQEP_SIGNAL_QEPA],
	पूर्ण,
	अणु
		.actions_list	= ti_eqep_position_synapse_actions,
		.num_actions	= ARRAY_SIZE(ti_eqep_position_synapse_actions),
		.संकेत		= &ti_eqep_संकेतs[TI_EQEP_SIGNAL_QEPB],
	पूर्ण,
पूर्ण;

अटल काष्ठा counter_count ti_eqep_counts[] = अणु
	अणु
		.id		= 0,
		.name		= "QPOSCNT",
		.functions_list	= ti_eqep_position_functions,
		.num_functions	= ARRAY_SIZE(ti_eqep_position_functions),
		.synapses	= ti_eqep_position_synapses,
		.num_synapses	= ARRAY_SIZE(ti_eqep_position_synapses),
		.ext		= ti_eqep_position_ext,
		.num_ext	= ARRAY_SIZE(ti_eqep_position_ext),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ti_eqep_regmap32_config = अणु
	.name = "32-bit",
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = QUPRD,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ti_eqep_regmap16_config = अणु
	.name = "16-bit",
	.reg_bits = 16,
	.val_bits = 16,
	.reg_stride = 2,
	.max_रेजिस्टर = QCPRDLAT,
पूर्ण;

अटल पूर्णांक ti_eqep_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ti_eqep_cnt *priv;
	व्योम __iomem *base;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->regmap32 = devm_regmap_init_mmio(dev, base,
					       &ti_eqep_regmap32_config);
	अगर (IS_ERR(priv->regmap32))
		वापस PTR_ERR(priv->regmap32);

	priv->regmap16 = devm_regmap_init_mmio(dev, base + 0x24,
					       &ti_eqep_regmap16_config);
	अगर (IS_ERR(priv->regmap16))
		वापस PTR_ERR(priv->regmap16);

	priv->counter.name = dev_name(dev);
	priv->counter.parent = dev;
	priv->counter.ops = &ti_eqep_counter_ops;
	priv->counter.counts = ti_eqep_counts;
	priv->counter.num_counts = ARRAY_SIZE(ti_eqep_counts);
	priv->counter.संकेतs = ti_eqep_संकेतs;
	priv->counter.num_संकेतs = ARRAY_SIZE(ti_eqep_संकेतs);
	priv->counter.priv = priv;

	platक्रमm_set_drvdata(pdev, priv);

	/*
	 * Need to make sure घातer is turned on. On AM33xx, this comes from the
	 * parent PWMSS bus driver. On AM17xx, this comes from the PSC घातer
	 * करोमुख्य.
	 */
	pm_runसमय_enable(dev);
	pm_runसमय_get_sync(dev);

	err = counter_रेजिस्टर(&priv->counter);
	अगर (err < 0) अणु
		pm_runसमय_put_sync(dev);
		pm_runसमय_disable(dev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ti_eqep_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_eqep_cnt *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;

	counter_unरेजिस्टर(&priv->counter);
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_eqep_of_match[] = अणु
	अणु .compatible = "ti,am3352-eqep", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_eqep_of_match);

अटल काष्ठा platक्रमm_driver ti_eqep_driver = अणु
	.probe = ti_eqep_probe,
	.हटाओ = ti_eqep_हटाओ,
	.driver = अणु
		.name = "ti-eqep-cnt",
		.of_match_table = ti_eqep_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ti_eqep_driver);

MODULE_AUTHOR("David Lechner <david@lechnology.com>");
MODULE_DESCRIPTION("TI eQEP counter driver");
MODULE_LICENSE("GPL v2");
