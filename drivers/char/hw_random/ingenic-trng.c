<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ingenic True Ranकरोm Number Generator driver
 * Copyright (c) 2019 ौञ़छौ/ (Qi Pengzhen) <aric.pzqi@ingenic.com>
 * Copyright (c) 2020 ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/* DTRNG रेजिस्टर offsets */
#घोषणा TRNG_REG_CFG_OFFSET			0x00
#घोषणा TRNG_REG_RANDOMNUM_OFFSET	0x04
#घोषणा TRNG_REG_STATUS_OFFSET		0x08

/* bits within the CFG रेजिस्टर */
#घोषणा CFG_RDY_CLR					BIT(12)
#घोषणा CFG_INT_MASK				BIT(11)
#घोषणा CFG_GEN_EN					BIT(0)

/* bits within the STATUS रेजिस्टर */
#घोषणा STATUS_RANDOM_RDY			BIT(0)

काष्ठा ingenic_trng अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा hwrng rng;
पूर्ण;

अटल पूर्णांक ingenic_trng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा ingenic_trng *trng = container_of(rng, काष्ठा ingenic_trng, rng);
	अचिन्हित पूर्णांक ctrl;

	ctrl = पढ़ोl(trng->base + TRNG_REG_CFG_OFFSET);
	ctrl |= CFG_GEN_EN;
	ग_लिखोl(ctrl, trng->base + TRNG_REG_CFG_OFFSET);

	वापस 0;
पूर्ण

अटल व्योम ingenic_trng_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा ingenic_trng *trng = container_of(rng, काष्ठा ingenic_trng, rng);
	अचिन्हित पूर्णांक ctrl;

	ctrl = पढ़ोl(trng->base + TRNG_REG_CFG_OFFSET);
	ctrl &= ~CFG_GEN_EN;
	ग_लिखोl(ctrl, trng->base + TRNG_REG_CFG_OFFSET);
पूर्ण

अटल पूर्णांक ingenic_trng_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max, bool रुको)
अणु
	काष्ठा ingenic_trng *trng = container_of(rng, काष्ठा ingenic_trng, rng);
	u32 *data = buf;
	u32 status;
	पूर्णांक ret;

	ret = पढ़ोl_poll_समयout(trng->base + TRNG_REG_STATUS_OFFSET, status,
				 status & STATUS_RANDOM_RDY, 10, 1000);
	अगर (ret == -ETIMEDOUT) अणु
		pr_err("%s: Wait for DTRNG data ready timeout\n", __func__);
		वापस ret;
	पूर्ण

	*data = पढ़ोl(trng->base + TRNG_REG_RANDOMNUM_OFFSET);

	वापस 4;
पूर्ण

अटल पूर्णांक ingenic_trng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ingenic_trng *trng;
	पूर्णांक ret;

	trng = devm_kzalloc(&pdev->dev, माप(*trng), GFP_KERNEL);
	अगर (!trng)
		वापस -ENOMEM;

	trng->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(trng->base)) अणु
		pr_err("%s: Failed to map DTRNG registers\n", __func__);
		ret = PTR_ERR(trng->base);
		वापस PTR_ERR(trng->base);
	पूर्ण

	trng->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(trng->clk)) अणु
		ret = PTR_ERR(trng->clk);
		pr_crit("%s: Cannot get DTRNG clock\n", __func__);
		वापस PTR_ERR(trng->clk);
	पूर्ण

	ret = clk_prepare_enable(trng->clk);
	अगर (ret) अणु
		pr_crit("%s: Unable to enable DTRNG clock\n", __func__);
		वापस ret;
	पूर्ण

	trng->rng.name = pdev->name;
	trng->rng.init = ingenic_trng_init;
	trng->rng.cleanup = ingenic_trng_cleanup;
	trng->rng.पढ़ो = ingenic_trng_पढ़ो;

	ret = hwrng_रेजिस्टर(&trng->rng);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register hwrng\n");
		जाओ err_unprepare_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, trng);

	dev_info(&pdev->dev, "Ingenic DTRNG driver registered\n");
	वापस 0;

err_unprepare_clk:
	clk_disable_unprepare(trng->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक ingenic_trng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ingenic_trng *trng = platक्रमm_get_drvdata(pdev);
	अचिन्हित पूर्णांक ctrl;

	hwrng_unरेजिस्टर(&trng->rng);

	ctrl = पढ़ोl(trng->base + TRNG_REG_CFG_OFFSET);
	ctrl &= ~CFG_GEN_EN;
	ग_लिखोl(ctrl, trng->base + TRNG_REG_CFG_OFFSET);

	clk_disable_unprepare(trng->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ingenic_trng_of_match[] = अणु
	अणु .compatible = "ingenic,x1830-dtrng" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ingenic_trng_of_match);

अटल काष्ठा platक्रमm_driver ingenic_trng_driver = अणु
	.probe		= ingenic_trng_probe,
	.हटाओ		= ingenic_trng_हटाओ,
	.driver		= अणु
		.name	= "ingenic-trng",
		.of_match_table = ingenic_trng_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ingenic_trng_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ौञ़छौ/ (Qi Pengzhen) <aric.pzqi@ingenic.com>");
MODULE_AUTHOR("ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>");
MODULE_DESCRIPTION("Ingenic True Random Number Generator driver");
