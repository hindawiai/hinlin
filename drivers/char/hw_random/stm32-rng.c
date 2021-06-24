<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2015, Daniel Thompson
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>

#घोषणा RNG_CR 0x00
#घोषणा RNG_CR_RNGEN BIT(2)
#घोषणा RNG_CR_CED BIT(5)

#घोषणा RNG_SR 0x04
#घोषणा RNG_SR_SEIS BIT(6)
#घोषणा RNG_SR_CEIS BIT(5)
#घोषणा RNG_SR_DRDY BIT(0)

#घोषणा RNG_DR 0x08

काष्ठा sपंचांग32_rng_निजी अणु
	काष्ठा hwrng rng;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा reset_control *rst;
	bool ced;
पूर्ण;

अटल पूर्णांक sपंचांग32_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको)
अणु
	काष्ठा sपंचांग32_rng_निजी *priv =
	    container_of(rng, काष्ठा sपंचांग32_rng_निजी, rng);
	u32 sr;
	पूर्णांक retval = 0;

	pm_runसमय_get_sync((काष्ठा device *) priv->rng.priv);

	जबतक (max > माप(u32)) अणु
		sr = पढ़ोl_relaxed(priv->base + RNG_SR);
		/* Manage समयout which is based on समयr and take */
		/* care of initial delay समय when enabling rng	*/
		अगर (!sr && रुको) अणु
			retval = पढ़ोl_relaxed_poll_समयout_atomic(priv->base
								   + RNG_SR,
								   sr, sr,
								   10, 50000);
			अगर (retval)
				dev_err((काष्ठा device *)priv->rng.priv,
					"%s: timeout %x!\n", __func__, sr);
		पूर्ण

		/* If error detected or data not पढ़ोy... */
		अगर (sr != RNG_SR_DRDY) अणु
			अगर (WARN_ONCE(sr & (RNG_SR_SEIS | RNG_SR_CEIS),
					"bad RNG status - %x\n", sr))
				ग_लिखोl_relaxed(0, priv->base + RNG_SR);
			अवरोध;
		पूर्ण

		*(u32 *)data = पढ़ोl_relaxed(priv->base + RNG_DR);

		retval += माप(u32);
		data += माप(u32);
		max -= माप(u32);
	पूर्ण

	pm_runसमय_mark_last_busy((काष्ठा device *) priv->rng.priv);
	pm_runसमय_put_sync_स्वतःsuspend((काष्ठा device *) priv->rng.priv);

	वापस retval || !रुको ? retval : -EIO;
पूर्ण

अटल पूर्णांक sपंचांग32_rng_init(काष्ठा hwrng *rng)
अणु
	काष्ठा sपंचांग32_rng_निजी *priv =
	    container_of(rng, काष्ठा sपंचांग32_rng_निजी, rng);
	पूर्णांक err;

	err = clk_prepare_enable(priv->clk);
	अगर (err)
		वापस err;

	अगर (priv->ced)
		ग_लिखोl_relaxed(RNG_CR_RNGEN, priv->base + RNG_CR);
	अन्यथा
		ग_लिखोl_relaxed(RNG_CR_RNGEN | RNG_CR_CED,
			       priv->base + RNG_CR);

	/* clear error indicators */
	ग_लिखोl_relaxed(0, priv->base + RNG_SR);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_rng_cleanup(काष्ठा hwrng *rng)
अणु
	काष्ठा sपंचांग32_rng_निजी *priv =
	    container_of(rng, काष्ठा sपंचांग32_rng_निजी, rng);

	ग_लिखोl_relaxed(0, priv->base + RNG_CR);
	clk_disable_unprepare(priv->clk);
पूर्ण

अटल पूर्णांक sपंचांग32_rng_probe(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा device *dev = &ofdev->dev;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा sपंचांग32_rng_निजी *priv;
	काष्ठा resource res;
	पूर्णांक err;

	priv = devm_kzalloc(dev, माप(काष्ठा sपंचांग32_rng_निजी), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	err = of_address_to_resource(np, 0, &res);
	अगर (err)
		वापस err;

	priv->base = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->clk = devm_clk_get(&ofdev->dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	priv->rst = devm_reset_control_get(&ofdev->dev, शून्य);
	अगर (!IS_ERR(priv->rst)) अणु
		reset_control_निश्चित(priv->rst);
		udelay(2);
		reset_control_deनिश्चित(priv->rst);
	पूर्ण

	priv->ced = of_property_पढ़ो_bool(np, "clock-error-detect");

	dev_set_drvdata(dev, priv);

	priv->rng.name = dev_driver_string(dev);
#अगर_अघोषित CONFIG_PM
	priv->rng.init = sपंचांग32_rng_init;
	priv->rng.cleanup = sपंचांग32_rng_cleanup;
#पूर्ण_अगर
	priv->rng.पढ़ो = sपंचांग32_rng_पढ़ो;
	priv->rng.priv = (अचिन्हित दीर्घ) dev;
	priv->rng.quality = 900;

	pm_runसमय_set_स्वतःsuspend_delay(dev, 100);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_enable(dev);

	वापस devm_hwrng_रेजिस्टर(dev, &priv->rng);
पूर्ण

अटल पूर्णांक sपंचांग32_rng_हटाओ(काष्ठा platक्रमm_device *ofdev)
अणु
	pm_runसमय_disable(&ofdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sपंचांग32_rng_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_rng_निजी *priv = dev_get_drvdata(dev);

	sपंचांग32_rng_cleanup(&priv->rng);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_rng_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_rng_निजी *priv = dev_get_drvdata(dev);

	वापस sपंचांग32_rng_init(&priv->rng);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_rng_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sपंचांग32_rng_runसमय_suspend,
			   sपंचांग32_rng_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;


अटल स्थिर काष्ठा of_device_id sपंचांग32_rng_match[] = अणु
	अणु
		.compatible = "st,stm32-rng",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_rng_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_rng_driver = अणु
	.driver = अणु
		.name = "stm32-rng",
		.pm = &sपंचांग32_rng_pm_ops,
		.of_match_table = sपंचांग32_rng_match,
	पूर्ण,
	.probe = sपंचांग32_rng_probe,
	.हटाओ = sपंचांग32_rng_हटाओ,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_rng_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Daniel Thompson <daniel.thompson@linaro.org>");
MODULE_DESCRIPTION("STMicroelectronics STM32 RNG device driver");
