<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Mediatek Hardware Ranकरोm Number Generator
 *
 * Copyright (C) 2017 Sean Wang <sean.wang@mediatek.com>
 */
#घोषणा MTK_RNG_DEV KBUILD_MODNAME

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

/* Runसमय PM स्वतःsuspend समयout: */
#घोषणा RNG_AUTOSUSPEND_TIMEOUT		100

#घोषणा USEC_POLL			2
#घोषणा TIMEOUT_POLL			20

#घोषणा RNG_CTRL			0x00
#घोषणा RNG_EN				BIT(0)
#घोषणा RNG_READY			BIT(31)

#घोषणा RNG_DATA			0x08

#घोषणा to_mtk_rng(p)	container_of(p, काष्ठा mtk_rng, rng)

काष्ठा mtk_rng अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा hwrng rng;
पूर्ण;

अटल पूर्णांक mtk_rng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा mtk_rng *priv = to_mtk_rng(rng);
	u32 val;
	पूर्णांक err;

	err = clk_prepare_enable(priv->clk);
	अगर (err)
		वापस err;

	val = पढ़ोl(priv->base + RNG_CTRL);
	val |= RNG_EN;
	ग_लिखोl(val, priv->base + RNG_CTRL);

	वापस 0;
पूर्ण

अटल व्योम mtk_rng_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा mtk_rng *priv = to_mtk_rng(rng);
	u32 val;

	val = पढ़ोl(priv->base + RNG_CTRL);
	val &= ~RNG_EN;
	ग_लिखोl(val, priv->base + RNG_CTRL);

	clk_disable_unprepare(priv->clk);
पूर्ण

अटल bool mtk_rng_रुको_पढ़ोy(काष्ठा hwrng *rng, bool रुको)
अणु
	काष्ठा mtk_rng *priv = to_mtk_rng(rng);
	पूर्णांक पढ़ोy;

	पढ़ोy = पढ़ोl(priv->base + RNG_CTRL) & RNG_READY;
	अगर (!पढ़ोy && रुको)
		पढ़ोl_poll_समयout_atomic(priv->base + RNG_CTRL, पढ़ोy,
					  पढ़ोy & RNG_READY, USEC_POLL,
					  TIMEOUT_POLL);
	वापस !!पढ़ोy;
पूर्ण

अटल पूर्णांक mtk_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max, bool रुको)
अणु
	काष्ठा mtk_rng *priv = to_mtk_rng(rng);
	पूर्णांक retval = 0;

	pm_runसमय_get_sync((काष्ठा device *)priv->rng.priv);

	जबतक (max >= माप(u32)) अणु
		अगर (!mtk_rng_रुको_पढ़ोy(rng, रुको))
			अवरोध;

		*(u32 *)buf = पढ़ोl(priv->base + RNG_DATA);
		retval += माप(u32);
		buf += माप(u32);
		max -= माप(u32);
	पूर्ण

	pm_runसमय_mark_last_busy((काष्ठा device *)priv->rng.priv);
	pm_runसमय_put_sync_स्वतःsuspend((काष्ठा device *)priv->rng.priv);

	वापस retval || !रुको ? retval : -EIO;
पूर्ण

अटल पूर्णांक mtk_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा mtk_rng *priv;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->rng.name = pdev->name;
#अगर_अघोषित CONFIG_PM
	priv->rng.init = mtk_rng_init;
	priv->rng.cleanup = mtk_rng_cleanup;
#पूर्ण_अगर
	priv->rng.पढ़ो = mtk_rng_पढ़ो;
	priv->rng.priv = (अचिन्हित दीर्घ)&pdev->dev;
	priv->rng.quality = 900;

	priv->clk = devm_clk_get(&pdev->dev, "rng");
	अगर (IS_ERR(priv->clk)) अणु
		ret = PTR_ERR(priv->clk);
		dev_err(&pdev->dev, "no clock for device: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	ret = devm_hwrng_रेजिस्टर(&pdev->dev, &priv->rng);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register rng device: %d\n",
			ret);
		वापस ret;
	पूर्ण

	dev_set_drvdata(&pdev->dev, priv);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, RNG_AUTOSUSPEND_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	dev_info(&pdev->dev, "registered RNG driver\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mtk_rng_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_rng *priv = dev_get_drvdata(dev);

	mtk_rng_cleanup(&priv->rng);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_rng_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_rng *priv = dev_get_drvdata(dev);

	वापस mtk_rng_init(&priv->rng);
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(mtk_rng_pm_ops, mtk_rng_runसमय_suspend,
			    mtk_rng_runसमय_resume, शून्य);
#घोषणा MTK_RNG_PM_OPS (&mtk_rng_pm_ops)
#अन्यथा	/* CONFIG_PM */
#घोषणा MTK_RNG_PM_OPS शून्य
#पूर्ण_अगर	/* CONFIG_PM */

अटल स्थिर काष्ठा of_device_id mtk_rng_match[] = अणु
	अणु .compatible = "mediatek,mt7623-rng" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_rng_match);

अटल काष्ठा platक्रमm_driver mtk_rng_driver = अणु
	.probe          = mtk_rng_probe,
	.driver = अणु
		.name = MTK_RNG_DEV,
		.pm = MTK_RNG_PM_OPS,
		.of_match_table = mtk_rng_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_rng_driver);

MODULE_DESCRIPTION("Mediatek Random Number Generator Driver");
MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_LICENSE("GPL");
