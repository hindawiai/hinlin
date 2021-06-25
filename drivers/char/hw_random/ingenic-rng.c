<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Ingenic Ranकरोm Number Generator driver
 * Copyright (c) 2017 PrasannaKumar Muralidharan <prasannatsmkumar@gmail.com>
 * Copyright (c) 2020 ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

/* RNG रेजिस्टर offsets */
#घोषणा RNG_REG_ERNG_OFFSET		0x0
#घोषणा RNG_REG_RNG_OFFSET		0x4

/* bits within the ERND रेजिस्टर */
#घोषणा ERNG_READY				BIT(31)
#घोषणा ERNG_ENABLE				BIT(0)

क्रमागत ingenic_rng_version अणु
	ID_JZ4780,
	ID_X1000,
पूर्ण;

/* Device associated memory */
काष्ठा ingenic_rng अणु
	क्रमागत ingenic_rng_version version;

	व्योम __iomem *base;
	काष्ठा hwrng rng;
पूर्ण;

अटल पूर्णांक ingenic_rng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा ingenic_rng *priv = container_of(rng, काष्ठा ingenic_rng, rng);

	ग_लिखोl(ERNG_ENABLE, priv->base + RNG_REG_ERNG_OFFSET);

	वापस 0;
पूर्ण

अटल व्योम ingenic_rng_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा ingenic_rng *priv = container_of(rng, काष्ठा ingenic_rng, rng);

	ग_लिखोl(0, priv->base + RNG_REG_ERNG_OFFSET);
पूर्ण

अटल पूर्णांक ingenic_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max, bool रुको)
अणु
	काष्ठा ingenic_rng *priv = container_of(rng, काष्ठा ingenic_rng, rng);
	u32 *data = buf;
	u32 status;
	पूर्णांक ret;

	अगर (priv->version >= ID_X1000) अणु
		ret = पढ़ोl_poll_समयout(priv->base + RNG_REG_ERNG_OFFSET, status,
					 status & ERNG_READY, 10, 1000);
		अगर (ret == -ETIMEDOUT) अणु
			pr_err("%s: Wait for RNG data ready timeout\n", __func__);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * A delay is required so that the current RNG data is not bit shअगरted
		 * version of previous RNG data which could happen अगर अक्रमom data is
		 * पढ़ो continuously from this device.
		 */
		udelay(20);
	पूर्ण

	*data = पढ़ोl(priv->base + RNG_REG_RNG_OFFSET);

	वापस 4;
पूर्ण

अटल पूर्णांक ingenic_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ingenic_rng *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base)) अणु
		pr_err("%s: Failed to map RNG registers\n", __func__);
		वापस PTR_ERR(priv->base);
	पूर्ण

	priv->version = (क्रमागत ingenic_rng_version)of_device_get_match_data(&pdev->dev);

	priv->rng.name = pdev->name;
	priv->rng.init = ingenic_rng_init;
	priv->rng.cleanup = ingenic_rng_cleanup;
	priv->rng.पढ़ो = ingenic_rng_पढ़ो;

	ret = hwrng_रेजिस्टर(&priv->rng);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register hwrng\n");
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	dev_info(&pdev->dev, "Ingenic RNG driver registered\n");
	वापस 0;
पूर्ण

अटल पूर्णांक ingenic_rng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ingenic_rng *priv = platक्रमm_get_drvdata(pdev);

	hwrng_unरेजिस्टर(&priv->rng);

	ग_लिखोl(0, priv->base + RNG_REG_ERNG_OFFSET);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ingenic_rng_of_match[] = अणु
	अणु .compatible = "ingenic,jz4780-rng", .data = (व्योम *) ID_JZ4780 पूर्ण,
	अणु .compatible = "ingenic,x1000-rng", .data = (व्योम *) ID_X1000 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ingenic_rng_of_match);

अटल काष्ठा platक्रमm_driver ingenic_rng_driver = अणु
	.probe		= ingenic_rng_probe,
	.हटाओ		= ingenic_rng_हटाओ,
	.driver		= अणु
		.name	= "ingenic-rng",
		.of_match_table = ingenic_rng_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ingenic_rng_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("PrasannaKumar Muralidharan <prasannatsmkumar@gmail.com>");
MODULE_AUTHOR("ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>");
MODULE_DESCRIPTION("Ingenic Random Number Generator driver");
