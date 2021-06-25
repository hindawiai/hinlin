<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DMA Router driver क्रम LPC18xx/43xx DMA MUX
 *
 * Copyright (C) 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * Based on TI DMA Crossbar driver by:
 *   Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com
 *   Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spinlock.h>

/* CREG रेजिस्टर offset and macros क्रम mux manipulation */
#घोषणा LPC18XX_CREG_DMAMUX		0x11c
#घोषणा LPC18XX_DMAMUX_VAL(v, n)	((v) << (n * 2))
#घोषणा LPC18XX_DMAMUX_MASK(n)		(0x3 << (n * 2))
#घोषणा LPC18XX_DMAMUX_MAX_VAL		0x3

काष्ठा lpc18xx_dmamux अणु
	u32 value;
	bool busy;
पूर्ण;

काष्ठा lpc18xx_dmamux_data अणु
	काष्ठा dma_router dmarouter;
	काष्ठा lpc18xx_dmamux *muxes;
	u32 dma_master_requests;
	u32 dma_mux_requests;
	काष्ठा regmap *reg;
	spinlock_t lock;
पूर्ण;

अटल व्योम lpc18xx_dmamux_मुक्त(काष्ठा device *dev, व्योम *route_data)
अणु
	काष्ठा lpc18xx_dmamux_data *dmamux = dev_get_drvdata(dev);
	काष्ठा lpc18xx_dmamux *mux = route_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dmamux->lock, flags);
	mux->busy = false;
	spin_unlock_irqrestore(&dmamux->lock, flags);
पूर्ण

अटल व्योम *lpc18xx_dmamux_reserve(काष्ठा of_phandle_args *dma_spec,
				    काष्ठा of_dma *ofdma)
अणु
	काष्ठा platक्रमm_device *pdev = of_find_device_by_node(ofdma->of_node);
	काष्ठा lpc18xx_dmamux_data *dmamux = platक्रमm_get_drvdata(pdev);
	अचिन्हित दीर्घ flags;
	अचिन्हित mux;

	अगर (dma_spec->args_count != 3) अणु
		dev_err(&pdev->dev, "invalid number of dma mux args\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	mux = dma_spec->args[0];
	अगर (mux >= dmamux->dma_master_requests) अणु
		dev_err(&pdev->dev, "invalid mux number: %d\n",
			dma_spec->args[0]);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (dma_spec->args[1] > LPC18XX_DMAMUX_MAX_VAL) अणु
		dev_err(&pdev->dev, "invalid dma mux value: %d\n",
			dma_spec->args[1]);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* The of_node_put() will be करोne in the core क्रम the node */
	dma_spec->np = of_parse_phandle(ofdma->of_node, "dma-masters", 0);
	अगर (!dma_spec->np) अणु
		dev_err(&pdev->dev, "can't get dma master\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	spin_lock_irqsave(&dmamux->lock, flags);
	अगर (dmamux->muxes[mux].busy) अणु
		spin_unlock_irqrestore(&dmamux->lock, flags);
		dev_err(&pdev->dev, "dma request %u busy with %u.%u\n",
			mux, mux, dmamux->muxes[mux].value);
		of_node_put(dma_spec->np);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	dmamux->muxes[mux].busy = true;
	dmamux->muxes[mux].value = dma_spec->args[1];

	regmap_update_bits(dmamux->reg, LPC18XX_CREG_DMAMUX,
			   LPC18XX_DMAMUX_MASK(mux),
			   LPC18XX_DMAMUX_VAL(dmamux->muxes[mux].value, mux));
	spin_unlock_irqrestore(&dmamux->lock, flags);

	dma_spec->args[1] = dma_spec->args[2];
	dma_spec->args_count = 2;

	dev_dbg(&pdev->dev, "mapping dmamux %u.%u to dma request %u\n", mux,
		dmamux->muxes[mux].value, mux);

	वापस &dmamux->muxes[mux];
पूर्ण

अटल पूर्णांक lpc18xx_dmamux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *dma_np, *np = pdev->dev.of_node;
	काष्ठा lpc18xx_dmamux_data *dmamux;
	पूर्णांक ret;

	dmamux = devm_kzalloc(&pdev->dev, माप(*dmamux), GFP_KERNEL);
	अगर (!dmamux)
		वापस -ENOMEM;

	dmamux->reg = syscon_regmap_lookup_by_compatible("nxp,lpc1850-creg");
	अगर (IS_ERR(dmamux->reg)) अणु
		dev_err(&pdev->dev, "syscon lookup failed\n");
		वापस PTR_ERR(dmamux->reg);
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "dma-requests",
				   &dmamux->dma_mux_requests);
	अगर (ret) अणु
		dev_err(&pdev->dev, "missing dma-requests property\n");
		वापस ret;
	पूर्ण

	dma_np = of_parse_phandle(np, "dma-masters", 0);
	अगर (!dma_np) अणु
		dev_err(&pdev->dev, "can't get dma master\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_property_पढ़ो_u32(dma_np, "dma-requests",
				   &dmamux->dma_master_requests);
	of_node_put(dma_np);
	अगर (ret) अणु
		dev_err(&pdev->dev, "missing master dma-requests property\n");
		वापस ret;
	पूर्ण

	dmamux->muxes = devm_kसुस्मृति(&pdev->dev, dmamux->dma_master_requests,
				     माप(काष्ठा lpc18xx_dmamux),
				     GFP_KERNEL);
	अगर (!dmamux->muxes)
		वापस -ENOMEM;

	spin_lock_init(&dmamux->lock);
	platक्रमm_set_drvdata(pdev, dmamux);
	dmamux->dmarouter.dev = &pdev->dev;
	dmamux->dmarouter.route_मुक्त = lpc18xx_dmamux_मुक्त;

	वापस of_dma_router_रेजिस्टर(np, lpc18xx_dmamux_reserve,
				      &dmamux->dmarouter);
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc18xx_dmamux_match[] = अणु
	अणु .compatible = "nxp,lpc1850-dmamux" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver lpc18xx_dmamux_driver = अणु
	.probe	= lpc18xx_dmamux_probe,
	.driver = अणु
		.name = "lpc18xx-dmamux",
		.of_match_table = lpc18xx_dmamux_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init lpc18xx_dmamux_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&lpc18xx_dmamux_driver);
पूर्ण
arch_initcall(lpc18xx_dmamux_init);
