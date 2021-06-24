<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2016
 * Author: Benjamin Gaignard <benjamin.gaignard@st.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/mfd/sपंचांग32-समयrs.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/reset.h>

#घोषणा STM32_TIMERS_MAX_REGISTERS	0x3fc

/* DIER रेजिस्टर DMA enable bits */
अटल स्थिर u32 sपंचांग32_समयrs_dier_dmaen[STM32_TIMERS_MAX_DMAS] = अणु
	TIM_DIER_CC1DE,
	TIM_DIER_CC2DE,
	TIM_DIER_CC3DE,
	TIM_DIER_CC4DE,
	TIM_DIER_UIE,
	TIM_DIER_TDE,
	TIM_DIER_COMDE
पूर्ण;

अटल व्योम sपंचांग32_समयrs_dma_करोne(व्योम *p)
अणु
	काष्ठा sपंचांग32_समयrs_dma *dma = p;
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;

	status = dmaengine_tx_status(dma->chan, dma->chan->cookie, &state);
	अगर (status == DMA_COMPLETE)
		complete(&dma->completion);
पूर्ण

/**
 * sपंचांग32_समयrs_dma_burst_पढ़ो - Read from समयrs रेजिस्टरs using DMA.
 *
 * Read from STM32 समयrs रेजिस्टरs using DMA on a single event.
 * @dev: reference to sपंचांग32_समयrs MFD device
 * @buf: DMA'able destination buffer
 * @id: sपंचांग32_समयrs_dmas event identअगरier (ch[1..4], up, trig or com)
 * @reg: रेजिस्टरs start offset क्रम DMA to पढ़ो from (like CCRx क्रम capture)
 * @num_reg: number of रेजिस्टरs to पढ़ो upon each DMA request, starting @reg.
 * @bursts: number of bursts to पढ़ो (e.g. like two क्रम pwm period capture)
 * @पंचांगo_ms: समयout (milliseconds)
 */
पूर्णांक sपंचांग32_समयrs_dma_burst_पढ़ो(काष्ठा device *dev, u32 *buf,
				क्रमागत sपंचांग32_समयrs_dmas id, u32 reg,
				अचिन्हित पूर्णांक num_reg, अचिन्हित पूर्णांक bursts,
				अचिन्हित दीर्घ पंचांगo_ms)
अणु
	काष्ठा sपंचांग32_समयrs *ddata = dev_get_drvdata(dev);
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(पंचांगo_ms);
	काष्ठा regmap *regmap = ddata->regmap;
	काष्ठा sपंचांग32_समयrs_dma *dma = &ddata->dma;
	माप_प्रकार len = num_reg * bursts * माप(u32);
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_slave_config config;
	dma_cookie_t cookie;
	dma_addr_t dma_buf;
	u32 dbl, dba;
	दीर्घ err;
	पूर्णांक ret;

	/* Sanity check */
	अगर (id < STM32_TIMERS_DMA_CH1 || id >= STM32_TIMERS_MAX_DMAS)
		वापस -EINVAL;

	अगर (!num_reg || !bursts || reg > STM32_TIMERS_MAX_REGISTERS ||
	    (reg + num_reg * माप(u32)) > STM32_TIMERS_MAX_REGISTERS)
		वापस -EINVAL;

	अगर (!dma->chans[id])
		वापस -ENODEV;
	mutex_lock(&dma->lock);

	/* Select DMA channel in use */
	dma->chan = dma->chans[id];
	dma_buf = dma_map_single(dev, buf, len, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, dma_buf)) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	/* Prepare DMA पढ़ो from समयr रेजिस्टरs, using DMA burst mode */
	स_रखो(&config, 0, माप(config));
	config.src_addr = (dma_addr_t)dma->phys_base + TIM_DMAR;
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	ret = dmaengine_slave_config(dma->chan, &config);
	अगर (ret)
		जाओ unmap;

	desc = dmaengine_prep_slave_single(dma->chan, dma_buf, len,
					   DMA_DEV_TO_MEM, DMA_PREP_INTERRUPT);
	अगर (!desc) अणु
		ret = -EBUSY;
		जाओ unmap;
	पूर्ण

	desc->callback = sपंचांग32_समयrs_dma_करोne;
	desc->callback_param = dma;
	cookie = dmaengine_submit(desc);
	ret = dma_submit_error(cookie);
	अगर (ret)
		जाओ dma_term;

	reinit_completion(&dma->completion);
	dma_async_issue_pending(dma->chan);

	/* Setup and enable समयr DMA burst mode */
	dbl = FIELD_PREP(TIM_DCR_DBL, bursts - 1);
	dba = FIELD_PREP(TIM_DCR_DBA, reg >> 2);
	ret = regmap_ग_लिखो(regmap, TIM_DCR, dbl | dba);
	अगर (ret)
		जाओ dma_term;

	/* Clear pending flags beक्रमe enabling DMA request */
	ret = regmap_ग_लिखो(regmap, TIM_SR, 0);
	अगर (ret)
		जाओ dcr_clr;

	ret = regmap_update_bits(regmap, TIM_DIER, sपंचांग32_समयrs_dier_dmaen[id],
				 sपंचांग32_समयrs_dier_dmaen[id]);
	अगर (ret)
		जाओ dcr_clr;

	err = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&dma->completion,
							समयout);
	अगर (err == 0)
		ret = -ETIMEDOUT;
	अन्यथा अगर (err < 0)
		ret = err;

	regmap_update_bits(regmap, TIM_DIER, sपंचांग32_समयrs_dier_dmaen[id], 0);
	regmap_ग_लिखो(regmap, TIM_SR, 0);
dcr_clr:
	regmap_ग_लिखो(regmap, TIM_DCR, 0);
dma_term:
	dmaengine_terminate_all(dma->chan);
unmap:
	dma_unmap_single(dev, dma_buf, len, DMA_FROM_DEVICE);
unlock:
	dma->chan = शून्य;
	mutex_unlock(&dma->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sपंचांग32_समयrs_dma_burst_पढ़ो);

अटल स्थिर काष्ठा regmap_config sपंचांग32_समयrs_regmap_cfg = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = माप(u32),
	.max_रेजिस्टर = STM32_TIMERS_MAX_REGISTERS,
पूर्ण;

अटल व्योम sपंचांग32_समयrs_get_arr_size(काष्ठा sपंचांग32_समयrs *ddata)
अणु
	u32 arr;

	/* Backup ARR to restore it after getting the maximum value */
	regmap_पढ़ो(ddata->regmap, TIM_ARR, &arr);

	/*
	 * Only the available bits will be written so when पढ़ोback
	 * we get the maximum value of स्वतः reload रेजिस्टर
	 */
	regmap_ग_लिखो(ddata->regmap, TIM_ARR, ~0L);
	regmap_पढ़ो(ddata->regmap, TIM_ARR, &ddata->max_arr);
	regmap_ग_लिखो(ddata->regmap, TIM_ARR, arr);
पूर्ण

अटल पूर्णांक sपंचांग32_समयrs_dma_probe(काष्ठा device *dev,
				   काष्ठा sपंचांग32_समयrs *ddata)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	अक्षर name[4];

	init_completion(&ddata->dma.completion);
	mutex_init(&ddata->dma.lock);

	/* Optional DMA support: get valid DMA channel(s) or शून्य */
	क्रम (i = STM32_TIMERS_DMA_CH1; i <= STM32_TIMERS_DMA_CH4; i++) अणु
		snम_लिखो(name, ARRAY_SIZE(name), "ch%1d", i + 1);
		ddata->dma.chans[i] = dma_request_chan(dev, name);
	पूर्ण
	ddata->dma.chans[STM32_TIMERS_DMA_UP] = dma_request_chan(dev, "up");
	ddata->dma.chans[STM32_TIMERS_DMA_TRIG] = dma_request_chan(dev, "trig");
	ddata->dma.chans[STM32_TIMERS_DMA_COM] = dma_request_chan(dev, "com");

	क्रम (i = STM32_TIMERS_DMA_CH1; i < STM32_TIMERS_MAX_DMAS; i++) अणु
		अगर (IS_ERR(ddata->dma.chans[i])) अणु
			/* Save the first error code to वापस */
			अगर (PTR_ERR(ddata->dma.chans[i]) != -ENODEV && !ret)
				ret = PTR_ERR(ddata->dma.chans[i]);

			ddata->dma.chans[i] = शून्य;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_समयrs_dma_हटाओ(काष्ठा device *dev,
				    काष्ठा sपंचांग32_समयrs *ddata)
अणु
	पूर्णांक i;

	क्रम (i = STM32_TIMERS_DMA_CH1; i < STM32_TIMERS_MAX_DMAS; i++)
		अगर (ddata->dma.chans[i])
			dma_release_channel(ddata->dma.chans[i]);
पूर्ण

अटल पूर्णांक sपंचांग32_समयrs_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sपंचांग32_समयrs *ddata;
	काष्ठा resource *res;
	व्योम __iomem *mmio;
	पूर्णांक ret;

	ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mmio = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(mmio))
		वापस PTR_ERR(mmio);

	/* Timer physical addr क्रम DMA */
	ddata->dma.phys_base = res->start;

	ddata->regmap = devm_regmap_init_mmio_clk(dev, "int", mmio,
						  &sपंचांग32_समयrs_regmap_cfg);
	अगर (IS_ERR(ddata->regmap))
		वापस PTR_ERR(ddata->regmap);

	ddata->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ddata->clk))
		वापस PTR_ERR(ddata->clk);

	sपंचांग32_समयrs_get_arr_size(ddata);

	ret = sपंचांग32_समयrs_dma_probe(dev, ddata);
	अगर (ret) अणु
		sपंचांग32_समयrs_dma_हटाओ(dev, ddata);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ddata);

	ret = of_platक्रमm_populate(pdev->dev.of_node, शून्य, शून्य, &pdev->dev);
	अगर (ret)
		sपंचांग32_समयrs_dma_हटाओ(dev, ddata);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_समयrs_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_समयrs *ddata = platक्रमm_get_drvdata(pdev);

	/*
	 * Don't use devm_ here: enक्रमe of_platक्रमm_depopulate() happens beक्रमe
	 * DMA are released, to aव्योम race on DMA.
	 */
	of_platक्रमm_depopulate(&pdev->dev);
	sपंचांग32_समयrs_dma_हटाओ(&pdev->dev, ddata);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sपंचांग32_समयrs_of_match[] = अणु
	अणु .compatible = "st,stm32-timers", पूर्ण,
	अणु /* end node */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_समयrs_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_समयrs_driver = अणु
	.probe = sपंचांग32_समयrs_probe,
	.हटाओ = sपंचांग32_समयrs_हटाओ,
	.driver	= अणु
		.name = "stm32-timers",
		.of_match_table = sपंचांग32_समयrs_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_समयrs_driver);

MODULE_DESCRIPTION("STMicroelectronics STM32 Timers");
MODULE_LICENSE("GPL v2");
