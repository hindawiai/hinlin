<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Ranकरोm Number Generator driver क्रम the Keystone SOC
 *
 * Copyright (C) 2016 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors:	Sandeep Nair
 *		Vitaly Andrianov
 */

#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/err.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयkeeping.h>

#घोषणा SA_CMD_STATUS_OFS			0x8

/* TRNG enable control in SA System module*/
#घोषणा SA_CMD_STATUS_REG_TRNG_ENABLE		BIT(3)

/* TRNG start control in TRNG module */
#घोषणा TRNG_CNTL_REG_TRNG_ENABLE		BIT(10)

/* Data पढ़ोy indicator in STATUS रेजिस्टर */
#घोषणा TRNG_STATUS_REG_READY			BIT(0)

/* Data पढ़ोy clear control in INTACK रेजिस्टर */
#घोषणा TRNG_INTACK_REG_READY			BIT(0)

/*
 * Number of samples taken to gather entropy during startup.
 * If value is 0, the number of samples is 2^24 अन्यथा
 * equals value बार 2^8.
 */
#घोषणा TRNG_DEF_STARTUP_CYCLES			0
#घोषणा TRNG_CNTL_REG_STARTUP_CYCLES_SHIFT	16

/*
 * Minimum number of samples taken to regenerate entropy
 * If value is 0, the number of samples is 2^24 अन्यथा
 * equals value बार 2^6.
 */
#घोषणा TRNG_DEF_MIN_REFILL_CYCLES		1
#घोषणा TRNG_CFG_REG_MIN_REFILL_CYCLES_SHIFT	0

/*
 * Maximum number of samples taken to regenerate entropy
 * If value is 0, the number of samples is 2^24 अन्यथा
 * equals value बार 2^8.
 */
#घोषणा TRNG_DEF_MAX_REFILL_CYCLES		0
#घोषणा TRNG_CFG_REG_MAX_REFILL_CYCLES_SHIFT	16

/* Number of CLK input cycles between samples */
#घोषणा TRNG_DEF_CLK_DIV_CYCLES			0
#घोषणा TRNG_CFG_REG_SAMPLE_DIV_SHIFT		8

/* Maximum retries to get rng data */
#घोषणा SA_MAX_RNG_DATA_RETRIES			5
/* Delay between retries (in usecs) */
#घोषणा SA_RNG_DATA_RETRY_DELAY			5

काष्ठा trng_regs अणु
	u32	output_l;
	u32	output_h;
	u32	status;
	u32	पूर्णांकmask;
	u32	पूर्णांकack;
	u32	control;
	u32	config;
पूर्ण;

काष्ठा ks_sa_rng अणु
	काष्ठा device	*dev;
	काष्ठा hwrng	rng;
	काष्ठा clk	*clk;
	काष्ठा regmap	*regmap_cfg;
	काष्ठा trng_regs __iomem *reg_rng;
	u64 पढ़ोy_ts;
	अचिन्हित पूर्णांक refill_delay_ns;
पूर्ण;

अटल अचिन्हित पूर्णांक cycles_to_ns(अचिन्हित दीर्घ clk_rate, अचिन्हित पूर्णांक cycles)
अणु
	वापस DIV_ROUND_UP_ULL((TRNG_DEF_CLK_DIV_CYCLES + 1) * 1000000000ull *
				cycles, clk_rate);
पूर्ण

अटल अचिन्हित पूर्णांक startup_delay_ns(अचिन्हित दीर्घ clk_rate)
अणु
	अगर (!TRNG_DEF_STARTUP_CYCLES)
		वापस cycles_to_ns(clk_rate, BIT(24));
	वापस cycles_to_ns(clk_rate, 256 * TRNG_DEF_STARTUP_CYCLES);
पूर्ण

अटल अचिन्हित पूर्णांक refill_delay_ns(अचिन्हित दीर्घ clk_rate)
अणु
	अगर (!TRNG_DEF_MAX_REFILL_CYCLES)
		वापस cycles_to_ns(clk_rate, BIT(24));
	वापस cycles_to_ns(clk_rate, 256 * TRNG_DEF_MAX_REFILL_CYCLES);
पूर्ण

अटल पूर्णांक ks_sa_rng_init(काष्ठा hwrng *rng)
अणु
	u32 value;
	काष्ठा device *dev = (काष्ठा device *)rng->priv;
	काष्ठा ks_sa_rng *ks_sa_rng = dev_get_drvdata(dev);
	अचिन्हित दीर्घ clk_rate = clk_get_rate(ks_sa_rng->clk);

	/* Enable RNG module */
	regmap_ग_लिखो_bits(ks_sa_rng->regmap_cfg, SA_CMD_STATUS_OFS,
			  SA_CMD_STATUS_REG_TRNG_ENABLE,
			  SA_CMD_STATUS_REG_TRNG_ENABLE);

	/* Configure RNG module */
	ग_लिखोl(0, &ks_sa_rng->reg_rng->control);
	value = TRNG_DEF_STARTUP_CYCLES << TRNG_CNTL_REG_STARTUP_CYCLES_SHIFT;
	ग_लिखोl(value, &ks_sa_rng->reg_rng->control);

	value =	(TRNG_DEF_MIN_REFILL_CYCLES <<
		 TRNG_CFG_REG_MIN_REFILL_CYCLES_SHIFT) |
		(TRNG_DEF_MAX_REFILL_CYCLES <<
		 TRNG_CFG_REG_MAX_REFILL_CYCLES_SHIFT) |
		(TRNG_DEF_CLK_DIV_CYCLES <<
		 TRNG_CFG_REG_SAMPLE_DIV_SHIFT);

	ग_लिखोl(value, &ks_sa_rng->reg_rng->config);

	/* Disable all पूर्णांकerrupts from TRNG */
	ग_लिखोl(0, &ks_sa_rng->reg_rng->पूर्णांकmask);

	/* Enable RNG */
	value = पढ़ोl(&ks_sa_rng->reg_rng->control);
	value |= TRNG_CNTL_REG_TRNG_ENABLE;
	ग_लिखोl(value, &ks_sa_rng->reg_rng->control);

	ks_sa_rng->refill_delay_ns = refill_delay_ns(clk_rate);
	ks_sa_rng->पढ़ोy_ts = kसमय_get_ns() +
			      startup_delay_ns(clk_rate);

	वापस 0;
पूर्ण

अटल व्योम ks_sa_rng_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा device *dev = (काष्ठा device *)rng->priv;
	काष्ठा ks_sa_rng *ks_sa_rng = dev_get_drvdata(dev);

	/* Disable RNG */
	ग_लिखोl(0, &ks_sa_rng->reg_rng->control);
	regmap_ग_लिखो_bits(ks_sa_rng->regmap_cfg, SA_CMD_STATUS_OFS,
			  SA_CMD_STATUS_REG_TRNG_ENABLE, 0);
पूर्ण

अटल पूर्णांक ks_sa_rng_data_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	काष्ठा device *dev = (काष्ठा device *)rng->priv;
	काष्ठा ks_sa_rng *ks_sa_rng = dev_get_drvdata(dev);

	/* Read अक्रमom data */
	data[0] = पढ़ोl(&ks_sa_rng->reg_rng->output_l);
	data[1] = पढ़ोl(&ks_sa_rng->reg_rng->output_h);

	ग_लिखोl(TRNG_INTACK_REG_READY, &ks_sa_rng->reg_rng->पूर्णांकack);
	ks_sa_rng->पढ़ोy_ts = kसमय_get_ns() + ks_sa_rng->refill_delay_ns;

	वापस माप(u32) * 2;
पूर्ण

अटल पूर्णांक ks_sa_rng_data_present(काष्ठा hwrng *rng, पूर्णांक रुको)
अणु
	काष्ठा device *dev = (काष्ठा device *)rng->priv;
	काष्ठा ks_sa_rng *ks_sa_rng = dev_get_drvdata(dev);
	u64 now = kसमय_get_ns();

	u32	पढ़ोy;
	पूर्णांक	j;

	अगर (रुको && now < ks_sa_rng->पढ़ोy_ts) अणु
		/* Max delay expected here is 81920000 ns */
		अचिन्हित दीर्घ min_delay =
			DIV_ROUND_UP((u32)(ks_sa_rng->पढ़ोy_ts - now), 1000);

		usleep_range(min_delay, min_delay + SA_RNG_DATA_RETRY_DELAY);
	पूर्ण

	क्रम (j = 0; j < SA_MAX_RNG_DATA_RETRIES; j++) अणु
		पढ़ोy = पढ़ोl(&ks_sa_rng->reg_rng->status);
		पढ़ोy &= TRNG_STATUS_REG_READY;

		अगर (पढ़ोy || !रुको)
			अवरोध;

		udelay(SA_RNG_DATA_RETRY_DELAY);
	पूर्ण

	वापस पढ़ोy;
पूर्ण

अटल पूर्णांक ks_sa_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ks_sa_rng	*ks_sa_rng;
	काष्ठा device		*dev = &pdev->dev;
	पूर्णांक			ret;

	ks_sa_rng = devm_kzalloc(dev, माप(*ks_sa_rng), GFP_KERNEL);
	अगर (!ks_sa_rng)
		वापस -ENOMEM;

	ks_sa_rng->dev = dev;
	ks_sa_rng->rng = (काष्ठा hwrng) अणु
		.name = "ks_sa_hwrng",
		.init = ks_sa_rng_init,
		.data_पढ़ो = ks_sa_rng_data_पढ़ो,
		.data_present = ks_sa_rng_data_present,
		.cleanup = ks_sa_rng_cleanup,
	पूर्ण;
	ks_sa_rng->rng.priv = (अचिन्हित दीर्घ)dev;

	ks_sa_rng->reg_rng = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ks_sa_rng->reg_rng))
		वापस PTR_ERR(ks_sa_rng->reg_rng);

	ks_sa_rng->regmap_cfg =
		syscon_regmap_lookup_by_phandle(dev->of_node,
						"ti,syscon-sa-cfg");

	अगर (IS_ERR(ks_sa_rng->regmap_cfg)) अणु
		dev_err(dev, "syscon_node_to_regmap failed\n");
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_enable(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable SA power-domain\n");
		pm_runसमय_put_noidle(dev);
		pm_runसमय_disable(dev);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ks_sa_rng);

	वापस devm_hwrng_रेजिस्टर(&pdev->dev, &ks_sa_rng->rng);
पूर्ण

अटल पूर्णांक ks_sa_rng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ks_sa_rng_dt_match[] = अणु
	अणु
		.compatible = "ti,keystone-rng",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ks_sa_rng_dt_match);

अटल काष्ठा platक्रमm_driver ks_sa_rng_driver = अणु
	.driver		= अणु
		.name	= "ks-sa-rng",
		.of_match_table = ks_sa_rng_dt_match,
	पूर्ण,
	.probe		= ks_sa_rng_probe,
	.हटाओ		= ks_sa_rng_हटाओ,
पूर्ण;

module_platक्रमm_driver(ks_sa_rng_driver);

MODULE_DESCRIPTION("Keystone NETCP SA H/W Random Number Generator driver");
MODULE_AUTHOR("Vitaly Andrianov <vitalya@ti.com>");
MODULE_LICENSE("GPL");
