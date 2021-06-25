<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DaVinci Voice Codec Core Interface क्रम TI platक्रमms
 *
 * Copyright (C) 2010 Texas Instruments, Inc
 *
 * Author: Miguel Aguilar <miguel.aguilar@ridgerun.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/regmap.h>

#समावेश <sound/pcm.h>

#समावेश <linux/mfd/davinci_voicecodec.h>

अटल स्थिर काष्ठा regmap_config davinci_vc_regmap = अणु
	.reg_bits = 32,
	.val_bits = 32,
पूर्ण;

अटल पूर्णांक __init davinci_vc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_vc *davinci_vc;
	काष्ठा resource *res;
	काष्ठा mfd_cell *cell = शून्य;
	dma_addr_t fअगरo_base;
	पूर्णांक ret;

	davinci_vc = devm_kzalloc(&pdev->dev,
				  माप(काष्ठा davinci_vc), GFP_KERNEL);
	अगर (!davinci_vc)
		वापस -ENOMEM;

	davinci_vc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(davinci_vc->clk)) अणु
		dev_dbg(&pdev->dev,
			    "could not get the clock for voice codec\n");
		वापस -ENODEV;
	पूर्ण
	clk_enable(davinci_vc->clk);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	fअगरo_base = (dma_addr_t)res->start;
	davinci_vc->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(davinci_vc->base)) अणु
		ret = PTR_ERR(davinci_vc->base);
		जाओ fail;
	पूर्ण

	davinci_vc->regmap = devm_regmap_init_mmio(&pdev->dev,
						   davinci_vc->base,
						   &davinci_vc_regmap);
	अगर (IS_ERR(davinci_vc->regmap)) अणु
		ret = PTR_ERR(davinci_vc->regmap);
		जाओ fail;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_DMA, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "no DMA resource\n");
		ret = -ENXIO;
		जाओ fail;
	पूर्ण

	davinci_vc->davinci_vcअगर.dma_tx_channel = res->start;
	davinci_vc->davinci_vcअगर.dma_tx_addr = fअगरo_base + DAVINCI_VC_WFIFO;

	res = platक्रमm_get_resource(pdev, IORESOURCE_DMA, 1);
	अगर (!res) अणु
		dev_err(&pdev->dev, "no DMA resource\n");
		ret = -ENXIO;
		जाओ fail;
	पूर्ण

	davinci_vc->davinci_vcअगर.dma_rx_channel = res->start;
	davinci_vc->davinci_vcअगर.dma_rx_addr = fअगरo_base + DAVINCI_VC_RFIFO;

	davinci_vc->dev = &pdev->dev;
	davinci_vc->pdev = pdev;

	/* Voice codec पूर्णांकerface client */
	cell = &davinci_vc->cells[DAVINCI_VC_VCIF_CELL];
	cell->name = "davinci-vcif";
	cell->platक्रमm_data = davinci_vc;
	cell->pdata_size = माप(*davinci_vc);

	/* Voice codec CQ93VC client */
	cell = &davinci_vc->cells[DAVINCI_VC_CQ93VC_CELL];
	cell->name = "cq93vc-codec";
	cell->platक्रमm_data = davinci_vc;
	cell->pdata_size = माप(*davinci_vc);

	ret = mfd_add_devices(&pdev->dev, pdev->id, davinci_vc->cells,
			      DAVINCI_VC_CELLS, शून्य, 0, शून्य);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "fail to register client devices\n");
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	clk_disable(davinci_vc->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक davinci_vc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_vc *davinci_vc = platक्रमm_get_drvdata(pdev);

	mfd_हटाओ_devices(&pdev->dev);

	clk_disable(davinci_vc->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver davinci_vc_driver = अणु
	.driver	= अणु
		.name = "davinci_voicecodec",
	पूर्ण,
	.हटाओ	= davinci_vc_हटाओ,
पूर्ण;

module_platक्रमm_driver_probe(davinci_vc_driver, davinci_vc_probe);

MODULE_AUTHOR("Miguel Aguilar");
MODULE_DESCRIPTION("Texas Instruments DaVinci Voice Codec Core Interface");
MODULE_LICENSE("GPL");
