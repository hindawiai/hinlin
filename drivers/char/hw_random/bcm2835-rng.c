<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2010-2012 Broadcom. All rights reserved.
 * Copyright (c) 2013 Lubomir Rपूर्णांकel
 */

#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/clk.h>
#समावेश <linux/reset.h>

#घोषणा RNG_CTRL	0x0
#घोषणा RNG_STATUS	0x4
#घोषणा RNG_DATA	0x8
#घोषणा RNG_INT_MASK	0x10

/* enable rng */
#घोषणा RNG_RBGEN	0x1

/* the initial numbers generated are "less random" so will be discarded */
#घोषणा RNG_WARMUP_COUNT 0x40000

#घोषणा RNG_INT_OFF	0x1

काष्ठा bcm2835_rng_priv अणु
	काष्ठा hwrng rng;
	व्योम __iomem *base;
	bool mask_पूर्णांकerrupts;
	काष्ठा clk *clk;
	काष्ठा reset_control *reset;
पूर्ण;

अटल अंतरभूत काष्ठा bcm2835_rng_priv *to_rng_priv(काष्ठा hwrng *rng)
अणु
	वापस container_of(rng, काष्ठा bcm2835_rng_priv, rng);
पूर्ण

अटल अंतरभूत u32 rng_पढ़ोl(काष्ठा bcm2835_rng_priv *priv, u32 offset)
अणु
	/* MIPS chips strapped क्रम BE will स्वतःmagically configure the
	 * peripheral रेजिस्टरs क्रम CPU-native byte order.
	 */
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		वापस __raw_पढ़ोl(priv->base + offset);
	अन्यथा
		वापस पढ़ोl(priv->base + offset);
पूर्ण

अटल अंतरभूत व्योम rng_ग_लिखोl(काष्ठा bcm2835_rng_priv *priv, u32 val,
			      u32 offset)
अणु
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		__raw_ग_लिखोl(val, priv->base + offset);
	अन्यथा
		ग_लिखोl(val, priv->base + offset);
पूर्ण

अटल पूर्णांक bcm2835_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max,
			       bool रुको)
अणु
	काष्ठा bcm2835_rng_priv *priv = to_rng_priv(rng);
	u32 max_words = max / माप(u32);
	u32 num_words, count;

	जबतक ((rng_पढ़ोl(priv, RNG_STATUS) >> 24) == 0) अणु
		अगर (!रुको)
			वापस 0;
		cpu_relax();
	पूर्ण

	num_words = rng_पढ़ोl(priv, RNG_STATUS) >> 24;
	अगर (num_words > max_words)
		num_words = max_words;

	क्रम (count = 0; count < num_words; count++)
		((u32 *)buf)[count] = rng_पढ़ोl(priv, RNG_DATA);

	वापस num_words * माप(u32);
पूर्ण

अटल पूर्णांक bcm2835_rng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा bcm2835_rng_priv *priv = to_rng_priv(rng);
	पूर्णांक ret = 0;
	u32 val;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	ret = reset_control_reset(priv->reset);
	अगर (ret)
		वापस ret;

	अगर (priv->mask_पूर्णांकerrupts) अणु
		/* mask the पूर्णांकerrupt */
		val = rng_पढ़ोl(priv, RNG_INT_MASK);
		val |= RNG_INT_OFF;
		rng_ग_लिखोl(priv, val, RNG_INT_MASK);
	पूर्ण

	/* set warm-up count & enable */
	rng_ग_लिखोl(priv, RNG_WARMUP_COUNT, RNG_STATUS);
	rng_ग_लिखोl(priv, RNG_RBGEN, RNG_CTRL);

	वापस ret;
पूर्ण

अटल व्योम bcm2835_rng_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा bcm2835_rng_priv *priv = to_rng_priv(rng);

	/* disable rng hardware */
	rng_ग_लिखोl(priv, 0, RNG_CTRL);

	clk_disable_unprepare(priv->clk);
पूर्ण

काष्ठा bcm2835_rng_of_data अणु
	bool mask_पूर्णांकerrupts;
पूर्ण;

अटल स्थिर काष्ठा bcm2835_rng_of_data nsp_rng_of_data = अणु
	.mask_पूर्णांकerrupts = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm2835_rng_of_match[] = अणु
	अणु .compatible = "brcm,bcm2835-rng"पूर्ण,
	अणु .compatible = "brcm,bcm-nsp-rng", .data = &nsp_rng_of_data पूर्ण,
	अणु .compatible = "brcm,bcm5301x-rng", .data = &nsp_rng_of_data पूर्ण,
	अणु .compatible = "brcm,bcm6368-rng"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक bcm2835_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा bcm2835_rng_of_data *of_data;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *rng_id;
	काष्ठा bcm2835_rng_priv *priv;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	/* map peripheral */
	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	/* Clock is optional on most platक्रमms */
	priv->clk = devm_clk_get_optional(dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	priv->reset = devm_reset_control_get_optional_exclusive(dev, शून्य);
	अगर (IS_ERR(priv->reset))
		वापस PTR_ERR(priv->reset);

	priv->rng.name = pdev->name;
	priv->rng.init = bcm2835_rng_init;
	priv->rng.पढ़ो = bcm2835_rng_पढ़ो;
	priv->rng.cleanup = bcm2835_rng_cleanup;

	अगर (dev_of_node(dev)) अणु
		rng_id = of_match_node(bcm2835_rng_of_match, dev->of_node);
		अगर (!rng_id)
			वापस -EINVAL;

		/* Check क्रम rng init function, execute it */
		of_data = rng_id->data;
		अगर (of_data)
			priv->mask_पूर्णांकerrupts = of_data->mask_पूर्णांकerrupts;
	पूर्ण

	/* रेजिस्टर driver */
	err = devm_hwrng_रेजिस्टर(dev, &priv->rng);
	अगर (err)
		dev_err(dev, "hwrng registration failed\n");
	अन्यथा
		dev_info(dev, "hwrng registered\n");

	वापस err;
पूर्ण

MODULE_DEVICE_TABLE(of, bcm2835_rng_of_match);

अटल स्थिर काष्ठा platक्रमm_device_id bcm2835_rng_devtype[] = अणु
	अणु .name = "bcm2835-rng" पूर्ण,
	अणु .name = "bcm63xx-rng" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, bcm2835_rng_devtype);

अटल काष्ठा platक्रमm_driver bcm2835_rng_driver = अणु
	.driver = अणु
		.name = "bcm2835-rng",
		.of_match_table = bcm2835_rng_of_match,
	पूर्ण,
	.probe		= bcm2835_rng_probe,
	.id_table	= bcm2835_rng_devtype,
पूर्ण;
module_platक्रमm_driver(bcm2835_rng_driver);

MODULE_AUTHOR("Lubomir Rintel <lkundrak@v3.sk>");
MODULE_DESCRIPTION("BCM2835 Random Number Generator (RNG) driver");
MODULE_LICENSE("GPL v2");
