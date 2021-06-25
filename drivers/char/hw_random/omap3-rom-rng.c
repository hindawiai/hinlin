<शैली गुरु>
/*
 * omap3-rom-rng.c - RNG driver क्रम TI OMAP3 CPU family
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Juha Yrjola <juha.yrjola@solidboot.com>
 *
 * Copyright (C) 2013 Pali Rohथँr <pali@kernel.org>
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा RNG_RESET			0x01
#घोषणा RNG_GEN_PRNG_HW_INIT		0x02
#घोषणा RNG_GEN_HW			0x08

काष्ठा omap_rom_rng अणु
	काष्ठा clk *clk;
	काष्ठा device *dev;
	काष्ठा hwrng ops;
	u32 (*rom_rng_call)(u32 ptr, u32 count, u32 flag);
पूर्ण;

अटल पूर्णांक omap3_rom_rng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool w)
अणु
	काष्ठा omap_rom_rng *ddata;
	u32 ptr;
	पूर्णांक r;

	ddata = (काष्ठा omap_rom_rng *)rng->priv;

	r = pm_runसमय_get_sync(ddata->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_noidle(ddata->dev);

		वापस r;
	पूर्ण

	ptr = virt_to_phys(data);
	r = ddata->rom_rng_call(ptr, 4, RNG_GEN_HW);
	अगर (r != 0)
		r = -EINVAL;
	अन्यथा
		r = 4;

	pm_runसमय_mark_last_busy(ddata->dev);
	pm_runसमय_put_स्वतःsuspend(ddata->dev);

	वापस r;
पूर्ण

अटल पूर्णांक __maybe_unused omap_rom_rng_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा omap_rom_rng *ddata;
	पूर्णांक r;

	ddata = dev_get_drvdata(dev);

	r = ddata->rom_rng_call(0, 0, RNG_RESET);
	अगर (r != 0)
		dev_err(dev, "reset failed: %d\n", r);

	clk_disable_unprepare(ddata->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused omap_rom_rng_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा omap_rom_rng *ddata;
	पूर्णांक r;

	ddata = dev_get_drvdata(dev);

	r = clk_prepare_enable(ddata->clk);
	अगर (r < 0)
		वापस r;

	r = ddata->rom_rng_call(0, 0, RNG_GEN_PRNG_HW_INIT);
	अगर (r != 0) अणु
		clk_disable(ddata->clk);
		dev_err(dev, "HW init failed: %d\n", r);

		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम omap_rom_rng_finish(व्योम *data)
अणु
	काष्ठा omap_rom_rng *ddata = data;

	pm_runसमय_करोnt_use_स्वतःsuspend(ddata->dev);
	pm_runसमय_disable(ddata->dev);
पूर्ण

अटल पूर्णांक omap3_rom_rng_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_rom_rng *ddata;
	पूर्णांक ret = 0;

	ddata = devm_kzalloc(&pdev->dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	ddata->dev = &pdev->dev;
	ddata->ops.priv = (अचिन्हित दीर्घ)ddata;
	ddata->ops.name = "omap3-rom";
	ddata->ops.पढ़ो = of_device_get_match_data(&pdev->dev);
	ddata->ops.quality = 900;
	अगर (!ddata->ops.पढ़ो) अणु
		dev_err(&pdev->dev, "missing rom code handler\n");

		वापस -ENODEV;
	पूर्ण
	dev_set_drvdata(ddata->dev, ddata);

	ddata->rom_rng_call = pdev->dev.platक्रमm_data;
	अगर (!ddata->rom_rng_call) अणु
		dev_err(ddata->dev, "rom_rng_call is NULL\n");
		वापस -EINVAL;
	पूर्ण

	ddata->clk = devm_clk_get(ddata->dev, "ick");
	अगर (IS_ERR(ddata->clk)) अणु
		dev_err(ddata->dev, "unable to get RNG clock\n");
		वापस PTR_ERR(ddata->clk);
	पूर्ण

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, 500);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);

	ret = devm_add_action_or_reset(ddata->dev, omap_rom_rng_finish,
				       ddata);
	अगर (ret)
		वापस ret;

	वापस devm_hwrng_रेजिस्टर(ddata->dev, &ddata->ops);
पूर्ण

अटल स्थिर काष्ठा of_device_id omap_rom_rng_match[] = अणु
	अणु .compatible = "nokia,n900-rom-rng", .data = omap3_rom_rng_पढ़ो, पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_rom_rng_match);

अटल स्थिर काष्ठा dev_pm_ops omap_rom_rng_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(omap_rom_rng_runसमय_suspend,
				omap_rom_rng_runसमय_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver omap3_rom_rng_driver = अणु
	.driver = अणु
		.name		= "omap3-rom-rng",
		.of_match_table = omap_rom_rng_match,
		.pm = &omap_rom_rng_pm_ops,
	पूर्ण,
	.probe		= omap3_rom_rng_probe,
पूर्ण;

module_platक्रमm_driver(omap3_rom_rng_driver);

MODULE_ALIAS("platform:omap3-rom-rng");
MODULE_AUTHOR("Juha Yrjola");
MODULE_AUTHOR("Pali Rohथँr <pali@kernel.org>");
MODULE_LICENSE("GPL");
