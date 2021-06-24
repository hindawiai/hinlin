<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PIC32 RNG driver
 *
 * Joshua Henderson <joshua.henderson@microchip.com>
 * Copyright (C) 2016 Microchip Technology Inc.  All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/err.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#घोषणा RNGCON		0x04
#घोषणा  TRNGEN		BIT(8)
#घोषणा  PRNGEN		BIT(9)
#घोषणा  PRNGCONT	BIT(10)
#घोषणा  TRNGMOD	BIT(11)
#घोषणा  SEEDLOAD	BIT(12)
#घोषणा RNGPOLY1	0x08
#घोषणा RNGPOLY2	0x0C
#घोषणा RNGNUMGEN1	0x10
#घोषणा RNGNUMGEN2	0x14
#घोषणा RNGSEED1	0x18
#घोषणा RNGSEED2	0x1C
#घोषणा RNGRCNT		0x20
#घोषणा  RCNT_MASK	0x7F

काष्ठा pic32_rng अणु
	व्योम __iomem	*base;
	काष्ठा hwrng	rng;
	काष्ठा clk	*clk;
पूर्ण;

/*
 * The TRNG can generate up to 24Mbps. This is a समयout that should be safe
 * enough given the inकाष्ठाions in the loop and that the TRNG may not always
 * be at maximum rate.
 */
#घोषणा RNG_TIMEOUT 500

अटल पूर्णांक pic32_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max,
			  bool रुको)
अणु
	काष्ठा pic32_rng *priv = container_of(rng, काष्ठा pic32_rng, rng);
	u64 *data = buf;
	u32 t;
	अचिन्हित पूर्णांक समयout = RNG_TIMEOUT;

	करो अणु
		t = पढ़ोl(priv->base + RNGRCNT) & RCNT_MASK;
		अगर (t == 64) अणु
			/* TRNG value comes through the seed रेजिस्टरs */
			*data = ((u64)पढ़ोl(priv->base + RNGSEED2) << 32) +
				पढ़ोl(priv->base + RNGSEED1);
			वापस 8;
		पूर्ण
	पूर्ण जबतक (रुको && --समयout);

	वापस -EIO;
पूर्ण

अटल पूर्णांक pic32_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pic32_rng *priv;
	u32 v;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	/* enable TRNG in enhanced mode */
	v = TRNGEN | TRNGMOD;
	ग_लिखोl(v, priv->base + RNGCON);

	priv->rng.name = pdev->name;
	priv->rng.पढ़ो = pic32_rng_पढ़ो;

	ret = devm_hwrng_रेजिस्टर(&pdev->dev, &priv->rng);
	अगर (ret)
		जाओ err_रेजिस्टर;

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;

err_रेजिस्टर:
	clk_disable_unprepare(priv->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक pic32_rng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pic32_rng *rng = platक्रमm_get_drvdata(pdev);

	ग_लिखोl(0, rng->base + RNGCON);
	clk_disable_unprepare(rng->clk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id pic32_rng_of_match[] __maybe_unused = अणु
	अणु .compatible	= "microchip,pic32mzda-rng", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pic32_rng_of_match);

अटल काष्ठा platक्रमm_driver pic32_rng_driver = अणु
	.probe		= pic32_rng_probe,
	.हटाओ		= pic32_rng_हटाओ,
	.driver		= अणु
		.name	= "pic32-rng",
		.of_match_table = of_match_ptr(pic32_rng_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pic32_rng_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joshua Henderson <joshua.henderson@microchip.com>");
MODULE_DESCRIPTION("Microchip PIC32 RNG Driver");
