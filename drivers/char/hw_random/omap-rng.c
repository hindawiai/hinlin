<शैली गुरु>
/*
 * omap-rng.c - RNG driver क्रम TI OMAP CPU family
 *
 * Author: Deepak Saxena <dsaxena@plनिकासy.net>
 *
 * Copyright 2005 (c) MontaVista Software, Inc.
 *
 * Mostly based on original driver:
 *
 * Copyright (C) 2005 Nokia Corporation
 * Author: Juha Yrjथघlथअ <juha.yrjola@nokia.com>
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>

#घोषणा RNG_REG_STATUS_RDY			(1 << 0)

#घोषणा RNG_REG_INTACK_RDY_MASK			(1 << 0)
#घोषणा RNG_REG_INTACK_SHUTDOWN_OFLO_MASK	(1 << 1)
#घोषणा RNG_SHUTDOWN_OFLO_MASK			(1 << 1)

#घोषणा RNG_CONTROL_STARTUP_CYCLES_SHIFT	16
#घोषणा RNG_CONTROL_STARTUP_CYCLES_MASK		(0xffff << 16)
#घोषणा RNG_CONTROL_ENABLE_TRNG_SHIFT		10
#घोषणा RNG_CONTROL_ENABLE_TRNG_MASK		(1 << 10)

#घोषणा RNG_CONFIG_MAX_REFIL_CYCLES_SHIFT	16
#घोषणा RNG_CONFIG_MAX_REFIL_CYCLES_MASK	(0xffff << 16)
#घोषणा RNG_CONFIG_MIN_REFIL_CYCLES_SHIFT	0
#घोषणा RNG_CONFIG_MIN_REFIL_CYCLES_MASK	(0xff << 0)

#घोषणा RNG_CONTROL_STARTUP_CYCLES		0xff
#घोषणा RNG_CONFIG_MIN_REFIL_CYCLES		0x21
#घोषणा RNG_CONFIG_MAX_REFIL_CYCLES		0x22

#घोषणा RNG_ALARMCNT_ALARM_TH_SHIFT		0x0
#घोषणा RNG_ALARMCNT_ALARM_TH_MASK		(0xff << 0)
#घोषणा RNG_ALARMCNT_SHUTDOWN_TH_SHIFT		16
#घोषणा RNG_ALARMCNT_SHUTDOWN_TH_MASK		(0x1f << 16)
#घोषणा RNG_ALARM_THRESHOLD			0xff
#घोषणा RNG_SHUTDOWN_THRESHOLD			0x4

#घोषणा RNG_REG_FROENABLE_MASK			0xffffff
#घोषणा RNG_REG_FRODETUNE_MASK			0xffffff

#घोषणा OMAP2_RNG_OUTPUT_SIZE			0x4
#घोषणा OMAP4_RNG_OUTPUT_SIZE			0x8
#घोषणा EIP76_RNG_OUTPUT_SIZE			0x10

/*
 * EIP76 RNG takes approx. 700us to produce 16 bytes of output data
 * as per testing results. And to account क्रम the lack of udelay()'s
 * reliability, we keep the समयout as 1000us.
 */
#घोषणा RNG_DATA_FILL_TIMEOUT			100

क्रमागत अणु
	RNG_OUTPUT_0_REG = 0,
	RNG_OUTPUT_1_REG,
	RNG_OUTPUT_2_REG,
	RNG_OUTPUT_3_REG,
	RNG_STATUS_REG,
	RNG_INTMASK_REG,
	RNG_INTACK_REG,
	RNG_CONTROL_REG,
	RNG_CONFIG_REG,
	RNG_ALARMCNT_REG,
	RNG_FROENABLE_REG,
	RNG_FRODETUNE_REG,
	RNG_ALARMMASK_REG,
	RNG_ALARMSTOP_REG,
	RNG_REV_REG,
	RNG_SYSCONFIG_REG,
पूर्ण;

अटल स्थिर u16 reg_map_omap2[] = अणु
	[RNG_OUTPUT_0_REG]	= 0x0,
	[RNG_STATUS_REG]	= 0x4,
	[RNG_CONFIG_REG]	= 0x28,
	[RNG_REV_REG]		= 0x3c,
	[RNG_SYSCONFIG_REG]	= 0x40,
पूर्ण;

अटल स्थिर u16 reg_map_omap4[] = अणु
	[RNG_OUTPUT_0_REG]	= 0x0,
	[RNG_OUTPUT_1_REG]	= 0x4,
	[RNG_STATUS_REG]	= 0x8,
	[RNG_INTMASK_REG]	= 0xc,
	[RNG_INTACK_REG]	= 0x10,
	[RNG_CONTROL_REG]	= 0x14,
	[RNG_CONFIG_REG]	= 0x18,
	[RNG_ALARMCNT_REG]	= 0x1c,
	[RNG_FROENABLE_REG]	= 0x20,
	[RNG_FRODETUNE_REG]	= 0x24,
	[RNG_ALARMMASK_REG]	= 0x28,
	[RNG_ALARMSTOP_REG]	= 0x2c,
	[RNG_REV_REG]		= 0x1FE0,
	[RNG_SYSCONFIG_REG]	= 0x1FE4,
पूर्ण;

अटल स्थिर u16 reg_map_eip76[] = अणु
	[RNG_OUTPUT_0_REG]	= 0x0,
	[RNG_OUTPUT_1_REG]	= 0x4,
	[RNG_OUTPUT_2_REG]	= 0x8,
	[RNG_OUTPUT_3_REG]	= 0xc,
	[RNG_STATUS_REG]	= 0x10,
	[RNG_INTACK_REG]	= 0x10,
	[RNG_CONTROL_REG]	= 0x14,
	[RNG_CONFIG_REG]	= 0x18,
	[RNG_ALARMCNT_REG]	= 0x1c,
	[RNG_FROENABLE_REG]	= 0x20,
	[RNG_FRODETUNE_REG]	= 0x24,
	[RNG_ALARMMASK_REG]	= 0x28,
	[RNG_ALARMSTOP_REG]	= 0x2c,
	[RNG_REV_REG]		= 0x7c,
पूर्ण;

काष्ठा omap_rng_dev;
/**
 * काष्ठा omap_rng_pdata - RNG IP block-specअगरic data
 * @regs: Poपूर्णांकer to the रेजिस्टर offsets काष्ठाure.
 * @data_size: No. of bytes in RNG output.
 * @data_present: Callback to determine अगर data is available.
 * @init: Callback क्रम IP specअगरic initialization sequence.
 * @cleanup: Callback क्रम IP specअगरic cleanup sequence.
 */
काष्ठा omap_rng_pdata अणु
	u16	*regs;
	u32	data_size;
	u32	(*data_present)(काष्ठा omap_rng_dev *priv);
	पूर्णांक	(*init)(काष्ठा omap_rng_dev *priv);
	व्योम	(*cleanup)(काष्ठा omap_rng_dev *priv);
पूर्ण;

काष्ठा omap_rng_dev अणु
	व्योम __iomem			*base;
	काष्ठा device			*dev;
	स्थिर काष्ठा omap_rng_pdata	*pdata;
	काष्ठा hwrng rng;
	काष्ठा clk 			*clk;
	काष्ठा clk			*clk_reg;
पूर्ण;

अटल अंतरभूत u32 omap_rng_पढ़ो(काष्ठा omap_rng_dev *priv, u16 reg)
अणु
	वापस __raw_पढ़ोl(priv->base + priv->pdata->regs[reg]);
पूर्ण

अटल अंतरभूत व्योम omap_rng_ग_लिखो(काष्ठा omap_rng_dev *priv, u16 reg,
				      u32 val)
अणु
	__raw_ग_लिखोl(val, priv->base + priv->pdata->regs[reg]);
पूर्ण


अटल पूर्णांक omap_rng_करो_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max,
			    bool रुको)
अणु
	काष्ठा omap_rng_dev *priv;
	पूर्णांक i, present;

	priv = (काष्ठा omap_rng_dev *)rng->priv;

	अगर (max < priv->pdata->data_size)
		वापस 0;

	क्रम (i = 0; i < RNG_DATA_FILL_TIMEOUT; i++) अणु
		present = priv->pdata->data_present(priv);
		अगर (present || !रुको)
			अवरोध;

		udelay(10);
	पूर्ण
	अगर (!present)
		वापस 0;

	स_नकल_fromio(data, priv->base + priv->pdata->regs[RNG_OUTPUT_0_REG],
		      priv->pdata->data_size);

	अगर (priv->pdata->regs[RNG_INTACK_REG])
		omap_rng_ग_लिखो(priv, RNG_INTACK_REG, RNG_REG_INTACK_RDY_MASK);

	वापस priv->pdata->data_size;
पूर्ण

अटल पूर्णांक omap_rng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा omap_rng_dev *priv;

	priv = (काष्ठा omap_rng_dev *)rng->priv;
	वापस priv->pdata->init(priv);
पूर्ण

अटल व्योम omap_rng_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा omap_rng_dev *priv;

	priv = (काष्ठा omap_rng_dev *)rng->priv;
	priv->pdata->cleanup(priv);
पूर्ण


अटल अंतरभूत u32 omap2_rng_data_present(काष्ठा omap_rng_dev *priv)
अणु
	वापस omap_rng_पढ़ो(priv, RNG_STATUS_REG) ? 0 : 1;
पूर्ण

अटल पूर्णांक omap2_rng_init(काष्ठा omap_rng_dev *priv)
अणु
	omap_rng_ग_लिखो(priv, RNG_SYSCONFIG_REG, 0x1);
	वापस 0;
पूर्ण

अटल व्योम omap2_rng_cleanup(काष्ठा omap_rng_dev *priv)
अणु
	omap_rng_ग_लिखो(priv, RNG_SYSCONFIG_REG, 0x0);
पूर्ण

अटल काष्ठा omap_rng_pdata omap2_rng_pdata = अणु
	.regs		= (u16 *)reg_map_omap2,
	.data_size	= OMAP2_RNG_OUTPUT_SIZE,
	.data_present	= omap2_rng_data_present,
	.init		= omap2_rng_init,
	.cleanup	= omap2_rng_cleanup,
पूर्ण;

अटल अंतरभूत u32 omap4_rng_data_present(काष्ठा omap_rng_dev *priv)
अणु
	वापस omap_rng_पढ़ो(priv, RNG_STATUS_REG) & RNG_REG_STATUS_RDY;
पूर्ण

अटल पूर्णांक eip76_rng_init(काष्ठा omap_rng_dev *priv)
अणु
	u32 val;

	/* Return अगर RNG is alपढ़ोy running. */
	अगर (omap_rng_पढ़ो(priv, RNG_CONTROL_REG) & RNG_CONTROL_ENABLE_TRNG_MASK)
		वापस 0;

	/*  Number of 512 bit blocks of raw Noise Source output data that must
	 *  be processed by either the Conditioning Function or the
	 *  SP 800-90 DRBG ै BC_DFै  functionality to yield a ै full entropyै 
	 *  output value.
	 */
	val = 0x5 << RNG_CONFIG_MIN_REFIL_CYCLES_SHIFT;

	/* Number of FRO samples that are XOR-ed together पूर्णांकo one bit to be
	 * shअगरted पूर्णांकo the मुख्य shअगरt रेजिस्टर
	 */
	val |= RNG_CONFIG_MAX_REFIL_CYCLES << RNG_CONFIG_MAX_REFIL_CYCLES_SHIFT;
	omap_rng_ग_लिखो(priv, RNG_CONFIG_REG, val);

	/* Enable all available FROs */
	omap_rng_ग_लिखो(priv, RNG_FRODETUNE_REG, 0x0);
	omap_rng_ग_लिखो(priv, RNG_FROENABLE_REG, RNG_REG_FROENABLE_MASK);

	/* Enable TRNG */
	val = RNG_CONTROL_ENABLE_TRNG_MASK;
	omap_rng_ग_लिखो(priv, RNG_CONTROL_REG, val);

	वापस 0;
पूर्ण

अटल पूर्णांक omap4_rng_init(काष्ठा omap_rng_dev *priv)
अणु
	u32 val;

	/* Return अगर RNG is alपढ़ोy running. */
	अगर (omap_rng_पढ़ो(priv, RNG_CONTROL_REG) & RNG_CONTROL_ENABLE_TRNG_MASK)
		वापस 0;

	val = RNG_CONFIG_MIN_REFIL_CYCLES << RNG_CONFIG_MIN_REFIL_CYCLES_SHIFT;
	val |= RNG_CONFIG_MAX_REFIL_CYCLES << RNG_CONFIG_MAX_REFIL_CYCLES_SHIFT;
	omap_rng_ग_लिखो(priv, RNG_CONFIG_REG, val);

	omap_rng_ग_लिखो(priv, RNG_FRODETUNE_REG, 0x0);
	omap_rng_ग_लिखो(priv, RNG_FROENABLE_REG, RNG_REG_FROENABLE_MASK);
	val = RNG_ALARM_THRESHOLD << RNG_ALARMCNT_ALARM_TH_SHIFT;
	val |= RNG_SHUTDOWN_THRESHOLD << RNG_ALARMCNT_SHUTDOWN_TH_SHIFT;
	omap_rng_ग_लिखो(priv, RNG_ALARMCNT_REG, val);

	val = RNG_CONTROL_STARTUP_CYCLES << RNG_CONTROL_STARTUP_CYCLES_SHIFT;
	val |= RNG_CONTROL_ENABLE_TRNG_MASK;
	omap_rng_ग_लिखो(priv, RNG_CONTROL_REG, val);

	वापस 0;
पूर्ण

अटल व्योम omap4_rng_cleanup(काष्ठा omap_rng_dev *priv)
अणु
	पूर्णांक val;

	val = omap_rng_पढ़ो(priv, RNG_CONTROL_REG);
	val &= ~RNG_CONTROL_ENABLE_TRNG_MASK;
	omap_rng_ग_लिखो(priv, RNG_CONTROL_REG, val);
पूर्ण

अटल irqवापस_t omap4_rng_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा omap_rng_dev *priv = dev_id;
	u32 fro_detune, fro_enable;

	/*
	 * Interrupt उठाओd by a fro shutकरोwn threshold, करो the following:
	 * 1. Clear the alarm events.
	 * 2. De tune the FROs which are shutकरोwn.
	 * 3. Re enable the shutकरोwn FROs.
	 */
	omap_rng_ग_लिखो(priv, RNG_ALARMMASK_REG, 0x0);
	omap_rng_ग_लिखो(priv, RNG_ALARMSTOP_REG, 0x0);

	fro_enable = omap_rng_पढ़ो(priv, RNG_FROENABLE_REG);
	fro_detune = ~fro_enable & RNG_REG_FRODETUNE_MASK;
	fro_detune = fro_detune | omap_rng_पढ़ो(priv, RNG_FRODETUNE_REG);
	fro_enable = RNG_REG_FROENABLE_MASK;

	omap_rng_ग_लिखो(priv, RNG_FRODETUNE_REG, fro_detune);
	omap_rng_ग_लिखो(priv, RNG_FROENABLE_REG, fro_enable);

	omap_rng_ग_लिखो(priv, RNG_INTACK_REG, RNG_REG_INTACK_SHUTDOWN_OFLO_MASK);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा omap_rng_pdata omap4_rng_pdata = अणु
	.regs		= (u16 *)reg_map_omap4,
	.data_size	= OMAP4_RNG_OUTPUT_SIZE,
	.data_present	= omap4_rng_data_present,
	.init		= omap4_rng_init,
	.cleanup	= omap4_rng_cleanup,
पूर्ण;

अटल काष्ठा omap_rng_pdata eip76_rng_pdata = अणु
	.regs		= (u16 *)reg_map_eip76,
	.data_size	= EIP76_RNG_OUTPUT_SIZE,
	.data_present	= omap4_rng_data_present,
	.init		= eip76_rng_init,
	.cleanup	= omap4_rng_cleanup,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_rng_of_match[] __maybe_unused = अणु
		अणु
			.compatible	= "ti,omap2-rng",
			.data		= &omap2_rng_pdata,
		पूर्ण,
		अणु
			.compatible	= "ti,omap4-rng",
			.data		= &omap4_rng_pdata,
		पूर्ण,
		अणु
			.compatible	= "inside-secure,safexcel-eip76",
			.data		= &eip76_rng_pdata,
		पूर्ण,
		अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_rng_of_match);

अटल पूर्णांक of_get_omap_rng_device_details(काष्ठा omap_rng_dev *priv,
					  काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक irq, err;

	priv->pdata = of_device_get_match_data(dev);
	अगर (!priv->pdata)
		वापस -ENODEV;


	अगर (of_device_is_compatible(dev->of_node, "ti,omap4-rng") ||
	    of_device_is_compatible(dev->of_node, "inside-secure,safexcel-eip76")) अणु
		irq = platक्रमm_get_irq(pdev, 0);
		अगर (irq < 0)
			वापस irq;

		err = devm_request_irq(dev, irq, omap4_rng_irq,
				       IRQF_TRIGGER_NONE, dev_name(dev), priv);
		अगर (err) अणु
			dev_err(dev, "unable to request irq %d, err = %d\n",
				irq, err);
			वापस err;
		पूर्ण

		/*
		 * On OMAP4, enabling the shutकरोwn_oflo पूर्णांकerrupt is
		 * करोne in the पूर्णांकerrupt mask रेजिस्टर. There is no
		 * such रेजिस्टर on EIP76, and it's enabled by the
		 * same bit in the control रेजिस्टर
		 */
		अगर (priv->pdata->regs[RNG_INTMASK_REG])
			omap_rng_ग_लिखो(priv, RNG_INTMASK_REG,
				       RNG_SHUTDOWN_OFLO_MASK);
		अन्यथा
			omap_rng_ग_लिखो(priv, RNG_CONTROL_REG,
				       RNG_SHUTDOWN_OFLO_MASK);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक get_omap_rng_device_details(काष्ठा omap_rng_dev *omap_rng)
अणु
	/* Only OMAP2/3 can be non-DT */
	omap_rng->pdata = &omap2_rng_pdata;
	वापस 0;
पूर्ण

अटल पूर्णांक omap_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_rng_dev *priv;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(काष्ठा omap_rng_dev), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->rng.पढ़ो = omap_rng_करो_पढ़ो;
	priv->rng.init = omap_rng_init;
	priv->rng.cleanup = omap_rng_cleanup;
	priv->rng.quality = 900;

	priv->rng.priv = (अचिन्हित दीर्घ)priv;
	platक्रमm_set_drvdata(pdev, priv);
	priv->dev = dev;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base)) अणु
		ret = PTR_ERR(priv->base);
		जाओ err_ioremap;
	पूर्ण

	priv->rng.name = devm_kstrdup(dev, dev_name(dev), GFP_KERNEL);
	अगर (!priv->rng.name) अणु
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to runtime_get device: %d\n", ret);
		pm_runसमय_put_noidle(&pdev->dev);
		जाओ err_ioremap;
	पूर्ण

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (PTR_ERR(priv->clk) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (!IS_ERR(priv->clk)) अणु
		ret = clk_prepare_enable(priv->clk);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Unable to enable the clk: %d\n", ret);
			जाओ err_रेजिस्टर;
		पूर्ण
	पूर्ण

	priv->clk_reg = devm_clk_get(&pdev->dev, "reg");
	अगर (PTR_ERR(priv->clk_reg) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;
	अगर (!IS_ERR(priv->clk_reg)) अणु
		ret = clk_prepare_enable(priv->clk_reg);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Unable to enable the register clk: %d\n",
				ret);
			जाओ err_रेजिस्टर;
		पूर्ण
	पूर्ण

	ret = (dev->of_node) ? of_get_omap_rng_device_details(priv, pdev) :
				get_omap_rng_device_details(priv);
	अगर (ret)
		जाओ err_रेजिस्टर;

	ret = devm_hwrng_रेजिस्टर(&pdev->dev, &priv->rng);
	अगर (ret)
		जाओ err_रेजिस्टर;

	dev_info(&pdev->dev, "Random Number Generator ver. %02x\n",
		 omap_rng_पढ़ो(priv, RNG_REV_REG));

	वापस 0;

err_रेजिस्टर:
	priv->base = शून्य;
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	clk_disable_unprepare(priv->clk_reg);
	clk_disable_unprepare(priv->clk);
err_ioremap:
	dev_err(dev, "initialization failed.\n");
	वापस ret;
पूर्ण

अटल पूर्णांक omap_rng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_rng_dev *priv = platक्रमm_get_drvdata(pdev);


	priv->pdata->cleanup(priv);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	clk_disable_unprepare(priv->clk);
	clk_disable_unprepare(priv->clk_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_rng_suspend(काष्ठा device *dev)
अणु
	काष्ठा omap_rng_dev *priv = dev_get_drvdata(dev);

	priv->pdata->cleanup(priv);
	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_rng_resume(काष्ठा device *dev)
अणु
	काष्ठा omap_rng_dev *priv = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to runtime_get device: %d\n", ret);
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	priv->pdata->init(priv);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(omap_rng_pm, omap_rng_suspend, omap_rng_resume);

अटल काष्ठा platक्रमm_driver omap_rng_driver = अणु
	.driver = अणु
		.name		= "omap_rng",
		.pm		= &omap_rng_pm,
		.of_match_table = of_match_ptr(omap_rng_of_match),
	पूर्ण,
	.probe		= omap_rng_probe,
	.हटाओ		= omap_rng_हटाओ,
पूर्ण;

module_platक्रमm_driver(omap_rng_driver);
MODULE_ALIAS("platform:omap_rng");
MODULE_AUTHOR("Deepak Saxena (and others)");
MODULE_LICENSE("GPL");
