<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RNG driver क्रम Exynos TRNGs
 *
 * Author: धukasz Stelmach <l.stelmach@samsung.com>
 *
 * Copyright 2017 (c) Samsung Electronics Software, Inc.
 *
 * Based on the Exynos PRNG driver drivers/crypto/exynos-rng by
 * Krzysztof Kozधowski <krzk@kernel.org>
 */

#समावेश <linux/clk.h>
#समावेश <linux/crypto.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा EXYNOS_TRNG_CLKDIV         (0x0)

#घोषणा EXYNOS_TRNG_CTRL           (0x20)
#घोषणा EXYNOS_TRNG_CTRL_RNGEN     BIT(31)

#घोषणा EXYNOS_TRNG_POST_CTRL      (0x30)
#घोषणा EXYNOS_TRNG_ONLINE_CTRL    (0x40)
#घोषणा EXYNOS_TRNG_ONLINE_STAT    (0x44)
#घोषणा EXYNOS_TRNG_ONLINE_MAXCHI2 (0x48)
#घोषणा EXYNOS_TRNG_FIFO_CTRL      (0x50)
#घोषणा EXYNOS_TRNG_FIFO_0         (0x80)
#घोषणा EXYNOS_TRNG_FIFO_1         (0x84)
#घोषणा EXYNOS_TRNG_FIFO_2         (0x88)
#घोषणा EXYNOS_TRNG_FIFO_3         (0x8c)
#घोषणा EXYNOS_TRNG_FIFO_4         (0x90)
#घोषणा EXYNOS_TRNG_FIFO_5         (0x94)
#घोषणा EXYNOS_TRNG_FIFO_6         (0x98)
#घोषणा EXYNOS_TRNG_FIFO_7         (0x9c)
#घोषणा EXYNOS_TRNG_FIFO_LEN       (8)
#घोषणा EXYNOS_TRNG_CLOCK_RATE     (500000)


काष्ठा exynos_trng_dev अणु
	काष्ठा device    *dev;
	व्योम __iomem     *mem;
	काष्ठा clk       *clk;
	काष्ठा hwrng rng;
पूर्ण;

अटल पूर्णांक exynos_trng_करो_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max,
			       bool रुको)
अणु
	काष्ठा exynos_trng_dev *trng;
	पूर्णांक val;

	max = min_t(माप_प्रकार, max, (EXYNOS_TRNG_FIFO_LEN * 4));

	trng = (काष्ठा exynos_trng_dev *)rng->priv;

	ग_लिखोl_relaxed(max * 8, trng->mem + EXYNOS_TRNG_FIFO_CTRL);
	val = पढ़ोl_poll_समयout(trng->mem + EXYNOS_TRNG_FIFO_CTRL, val,
				 val == 0, 200, 1000000);
	अगर (val < 0)
		वापस val;

	स_नकल_fromio(data, trng->mem + EXYNOS_TRNG_FIFO_0, max);

	वापस max;
पूर्ण

अटल पूर्णांक exynos_trng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा exynos_trng_dev *trng = (काष्ठा exynos_trng_dev *)rng->priv;
	अचिन्हित दीर्घ sss_rate;
	u32 val;

	sss_rate = clk_get_rate(trng->clk);

	/*
	 * For most TRNG circuits the घड़ी frequency of under 500 kHz
	 * is safe.
	 */
	val = sss_rate / (EXYNOS_TRNG_CLOCK_RATE * 2);
	अगर (val > 0x7fff) अणु
		dev_err(trng->dev, "clock divider too large: %d", val);
		वापस -दुस्फल;
	पूर्ण
	val = val << 1;
	ग_लिखोl_relaxed(val, trng->mem + EXYNOS_TRNG_CLKDIV);

	/* Enable the generator. */
	val = EXYNOS_TRNG_CTRL_RNGEN;
	ग_लिखोl_relaxed(val, trng->mem + EXYNOS_TRNG_CTRL);

	/*
	 * Disable post-processing. /dev/hwrng is supposed to deliver
	 * unprocessed data.
	 */
	ग_लिखोl_relaxed(0, trng->mem + EXYNOS_TRNG_POST_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_trng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_trng_dev *trng;
	पूर्णांक ret = -ENOMEM;

	trng = devm_kzalloc(&pdev->dev, माप(*trng), GFP_KERNEL);
	अगर (!trng)
		वापस ret;

	trng->rng.name = devm_kstrdup(&pdev->dev, dev_name(&pdev->dev),
				      GFP_KERNEL);
	अगर (!trng->rng.name)
		वापस ret;

	trng->rng.init = exynos_trng_init;
	trng->rng.पढ़ो = exynos_trng_करो_पढ़ो;
	trng->rng.priv = (अचिन्हित दीर्घ) trng;

	platक्रमm_set_drvdata(pdev, trng);
	trng->dev = &pdev->dev;

	trng->mem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(trng->mem))
		वापस PTR_ERR(trng->mem);

	pm_runसमय_enable(&pdev->dev);
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not get runtime PM.\n");
		जाओ err_pm_get;
	पूर्ण

	trng->clk = devm_clk_get(&pdev->dev, "secss");
	अगर (IS_ERR(trng->clk)) अणु
		ret = PTR_ERR(trng->clk);
		dev_err(&pdev->dev, "Could not get clock.\n");
		जाओ err_घड़ी;
	पूर्ण

	ret = clk_prepare_enable(trng->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not enable the clk.\n");
		जाओ err_घड़ी;
	पूर्ण

	ret = devm_hwrng_रेजिस्टर(&pdev->dev, &trng->rng);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register hwrng device.\n");
		जाओ err_रेजिस्टर;
	पूर्ण

	dev_info(&pdev->dev, "Exynos True Random Number Generator.\n");

	वापस 0;

err_रेजिस्टर:
	clk_disable_unprepare(trng->clk);

err_घड़ी:
	pm_runसमय_put_sync(&pdev->dev);

err_pm_get:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_trng_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_trng_dev *trng =  platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(trng->clk);

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_trng_suspend(काष्ठा device *dev)
अणु
	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_trng_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Could not get runtime PM.\n");
		pm_runसमय_put_noidle(dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(exynos_trng_pm_ops, exynos_trng_suspend,
			 exynos_trng_resume);

अटल स्थिर काष्ठा of_device_id exynos_trng_dt_match[] = अणु
	अणु
		.compatible = "samsung,exynos5250-trng",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_trng_dt_match);

अटल काष्ठा platक्रमm_driver exynos_trng_driver = अणु
	.driver = अणु
		.name = "exynos-trng",
		.pm = &exynos_trng_pm_ops,
		.of_match_table = exynos_trng_dt_match,
	पूर्ण,
	.probe = exynos_trng_probe,
	.हटाओ = exynos_trng_हटाओ,
पूर्ण;

module_platक्रमm_driver(exynos_trng_driver);
MODULE_AUTHOR("धukasz Stelmach");
MODULE_DESCRIPTION("H/W TRNG driver for Exynos chips");
MODULE_LICENSE("GPL v2");
