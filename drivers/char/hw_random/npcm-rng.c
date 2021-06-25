<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Nuvoton Technology corporation.

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/init.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा NPCM_RNGCS_REG		0x00	/* Control and status रेजिस्टर */
#घोषणा NPCM_RNGD_REG		0x04	/* Data रेजिस्टर */
#घोषणा NPCM_RNGMODE_REG	0x08	/* Mode रेजिस्टर */

#घोषणा NPCM_RNG_CLK_SET_25MHZ	GENMASK(4, 3) /* 20-25 MHz */
#घोषणा NPCM_RNG_DATA_VALID	BIT(1)
#घोषणा NPCM_RNG_ENABLE		BIT(0)
#घोषणा NPCM_RNG_M1ROSEL	BIT(1)

#घोषणा NPCM_RNG_TIMEOUT_USEC	20000
#घोषणा NPCM_RNG_POLL_USEC	1000

#घोषणा to_npcm_rng(p)	container_of(p, काष्ठा npcm_rng, rng)

काष्ठा npcm_rng अणु
	व्योम __iomem *base;
	काष्ठा hwrng rng;
पूर्ण;

अटल पूर्णांक npcm_rng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा npcm_rng *priv = to_npcm_rng(rng);

	ग_लिखोl(NPCM_RNG_CLK_SET_25MHZ | NPCM_RNG_ENABLE,
	       priv->base + NPCM_RNGCS_REG);

	वापस 0;
पूर्ण

अटल व्योम npcm_rng_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा npcm_rng *priv = to_npcm_rng(rng);

	ग_लिखोl(NPCM_RNG_CLK_SET_25MHZ, priv->base + NPCM_RNGCS_REG);
पूर्ण

अटल पूर्णांक npcm_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *buf, माप_प्रकार max, bool रुको)
अणु
	काष्ठा npcm_rng *priv = to_npcm_rng(rng);
	पूर्णांक retval = 0;
	पूर्णांक पढ़ोy;

	pm_runसमय_get_sync((काष्ठा device *)priv->rng.priv);

	जबतक (max) अणु
		अगर (रुको) अणु
			अगर (पढ़ोb_poll_समयout(priv->base + NPCM_RNGCS_REG,
					       पढ़ोy,
					       पढ़ोy & NPCM_RNG_DATA_VALID,
					       NPCM_RNG_POLL_USEC,
					       NPCM_RNG_TIMEOUT_USEC))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर ((पढ़ोb(priv->base + NPCM_RNGCS_REG) &
			    NPCM_RNG_DATA_VALID) == 0)
				अवरोध;
		पूर्ण

		*(u8 *)buf = पढ़ोb(priv->base + NPCM_RNGD_REG);
		retval++;
		buf++;
		max--;
	पूर्ण

	pm_runसमय_mark_last_busy((काष्ठा device *)priv->rng.priv);
	pm_runसमय_put_sync_स्वतःsuspend((काष्ठा device *)priv->rng.priv);

	वापस retval || !रुको ? retval : -EIO;
पूर्ण

अटल पूर्णांक npcm_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा npcm_rng *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	dev_set_drvdata(&pdev->dev, priv);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 100);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

#अगर_अघोषित CONFIG_PM
	priv->rng.init = npcm_rng_init;
	priv->rng.cleanup = npcm_rng_cleanup;
#पूर्ण_अगर
	priv->rng.name = pdev->name;
	priv->rng.पढ़ो = npcm_rng_पढ़ो;
	priv->rng.priv = (अचिन्हित दीर्घ)&pdev->dev;
	priv->rng.quality = 1000;

	ग_लिखोl(NPCM_RNG_M1ROSEL, priv->base + NPCM_RNGMODE_REG);

	ret = devm_hwrng_रेजिस्टर(&pdev->dev, &priv->rng);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register rng device: %d\n",
			ret);
		pm_runसमय_disable(&pdev->dev);
		pm_runसमय_set_suspended(&pdev->dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक npcm_rng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा npcm_rng *priv = platक्रमm_get_drvdata(pdev);

	devm_hwrng_unरेजिस्टर(&pdev->dev, &priv->rng);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक npcm_rng_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा npcm_rng *priv = dev_get_drvdata(dev);

	npcm_rng_cleanup(&priv->rng);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm_rng_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा npcm_rng *priv = dev_get_drvdata(dev);

	वापस npcm_rng_init(&priv->rng);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops npcm_rng_pm_ops = अणु
	SET_RUNTIME_PM_OPS(npcm_rng_runसमय_suspend,
			   npcm_rng_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id rng_dt_id[] __maybe_unused = अणु
	अणु .compatible = "nuvoton,npcm750-rng",  पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rng_dt_id);

अटल काष्ठा platक्रमm_driver npcm_rng_driver = अणु
	.driver = अणु
		.name		= "npcm-rng",
		.pm		= &npcm_rng_pm_ops,
		.of_match_table = of_match_ptr(rng_dt_id),
	पूर्ण,
	.probe		= npcm_rng_probe,
	.हटाओ		= npcm_rng_हटाओ,
पूर्ण;

module_platक्रमm_driver(npcm_rng_driver);

MODULE_DESCRIPTION("Nuvoton NPCM Random Number Generator Driver");
MODULE_AUTHOR("Tomer Maimon <tomer.maimon@nuvoton.com>");
MODULE_LICENSE("GPL v2");
