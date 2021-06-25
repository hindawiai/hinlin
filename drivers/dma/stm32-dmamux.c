<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) STMicroelectronics SA 2017
 * Author(s): M'boumba Cedric Madianga <cedric.madianga@gmail.com>
 *            Pierre-Yves Mordret <pierre-yves.mordret@st.com>
 *
 * DMA Router driver क्रम STM32 DMA MUX
 *
 * Based on TI DMA Crossbar driver
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#घोषणा STM32_DMAMUX_CCR(x)		(0x4 * (x))
#घोषणा STM32_DMAMUX_MAX_DMA_REQUESTS	32
#घोषणा STM32_DMAMUX_MAX_REQUESTS	255

काष्ठा sपंचांग32_dmamux अणु
	u32 master;
	u32 request;
	u32 chan_id;
पूर्ण;

काष्ठा sपंचांग32_dmamux_data अणु
	काष्ठा dma_router dmarouter;
	काष्ठा clk *clk;
	व्योम __iomem *iomem;
	u32 dma_requests; /* Number of DMA requests connected to DMAMUX */
	u32 dmamux_requests; /* Number of DMA requests routed toward DMAs */
	spinlock_t lock; /* Protects रेजिस्टर access */
	अचिन्हित दीर्घ *dma_inuse; /* Used DMA channel */
	u32 ccr[STM32_DMAMUX_MAX_DMA_REQUESTS]; /* Used to backup CCR रेजिस्टर
						 * in suspend
						 */
	u32 dma_reqs[]; /* Number of DMA Request per DMA masters.
			 *  [0] holds number of DMA Masters.
			 *  To be kept at very end end of this काष्ठाure
			 */
पूर्ण;

अटल अंतरभूत u32 sपंचांग32_dmamux_पढ़ो(व्योम __iomem *iomem, u32 reg)
अणु
	वापस पढ़ोl_relaxed(iomem + reg);
पूर्ण

अटल अंतरभूत व्योम sपंचांग32_dmamux_ग_लिखो(व्योम __iomem *iomem, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, iomem + reg);
पूर्ण

अटल व्योम sपंचांग32_dmamux_मुक्त(काष्ठा device *dev, व्योम *route_data)
अणु
	काष्ठा sपंचांग32_dmamux_data *dmamux = dev_get_drvdata(dev);
	काष्ठा sपंचांग32_dmamux *mux = route_data;
	अचिन्हित दीर्घ flags;

	/* Clear dma request */
	spin_lock_irqsave(&dmamux->lock, flags);

	sपंचांग32_dmamux_ग_लिखो(dmamux->iomem, STM32_DMAMUX_CCR(mux->chan_id), 0);
	clear_bit(mux->chan_id, dmamux->dma_inuse);

	pm_runसमय_put_sync(dev);

	spin_unlock_irqrestore(&dmamux->lock, flags);

	dev_dbg(dev, "Unmapping DMAMUX(%u) to DMA%u(%u)\n",
		mux->request, mux->master, mux->chan_id);

	kमुक्त(mux);
पूर्ण

अटल व्योम *sपंचांग32_dmamux_route_allocate(काष्ठा of_phandle_args *dma_spec,
					 काष्ठा of_dma *ofdma)
अणु
	काष्ठा platक्रमm_device *pdev = of_find_device_by_node(ofdma->of_node);
	काष्ठा sपंचांग32_dmamux_data *dmamux = platक्रमm_get_drvdata(pdev);
	काष्ठा sपंचांग32_dmamux *mux;
	u32 i, min, max;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (dma_spec->args_count != 3) अणु
		dev_err(&pdev->dev, "invalid number of dma mux args\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (dma_spec->args[0] > dmamux->dmamux_requests) अणु
		dev_err(&pdev->dev, "invalid mux request number: %d\n",
			dma_spec->args[0]);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_irqsave(&dmamux->lock, flags);
	mux->chan_id = find_first_zero_bit(dmamux->dma_inuse,
					   dmamux->dma_requests);

	अगर (mux->chan_id == dmamux->dma_requests) अणु
		spin_unlock_irqrestore(&dmamux->lock, flags);
		dev_err(&pdev->dev, "Run out of free DMA requests\n");
		ret = -ENOMEM;
		जाओ error_chan_id;
	पूर्ण
	set_bit(mux->chan_id, dmamux->dma_inuse);
	spin_unlock_irqrestore(&dmamux->lock, flags);

	/* Look क्रम DMA Master */
	क्रम (i = 1, min = 0, max = dmamux->dma_reqs[i];
	     i <= dmamux->dma_reqs[0];
	     min += dmamux->dma_reqs[i], max += dmamux->dma_reqs[++i])
		अगर (mux->chan_id < max)
			अवरोध;
	mux->master = i - 1;

	/* The of_node_put() will be करोne in of_dma_router_xlate function */
	dma_spec->np = of_parse_phandle(ofdma->of_node, "dma-masters", i - 1);
	अगर (!dma_spec->np) अणु
		dev_err(&pdev->dev, "can't get dma master\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* Set dma request */
	spin_lock_irqsave(&dmamux->lock, flags);
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		spin_unlock_irqrestore(&dmamux->lock, flags);
		जाओ error;
	पूर्ण
	spin_unlock_irqrestore(&dmamux->lock, flags);

	mux->request = dma_spec->args[0];

	/*  craft DMA spec */
	dma_spec->args[3] = dma_spec->args[2];
	dma_spec->args[2] = dma_spec->args[1];
	dma_spec->args[1] = 0;
	dma_spec->args[0] = mux->chan_id - min;
	dma_spec->args_count = 4;

	sपंचांग32_dmamux_ग_लिखो(dmamux->iomem, STM32_DMAMUX_CCR(mux->chan_id),
			   mux->request);
	dev_dbg(&pdev->dev, "Mapping DMAMUX(%u) to DMA%u(%u)\n",
		mux->request, mux->master, mux->chan_id);

	वापस mux;

error:
	clear_bit(mux->chan_id, dmamux->dma_inuse);

error_chan_id:
	kमुक्त(mux);
	वापस ERR_PTR(ret);
पूर्ण

अटल स्थिर काष्ठा of_device_id sपंचांग32_sपंचांग32dma_master_match[] __maybe_unused = अणु
	अणु .compatible = "st,stm32-dma", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांग32_dmamux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *dma_node;
	काष्ठा sपंचांग32_dmamux_data *sपंचांग32_dmamux;
	काष्ठा resource *res;
	व्योम __iomem *iomem;
	काष्ठा reset_control *rst;
	पूर्णांक i, count, ret;
	u32 dma_req;

	अगर (!node)
		वापस -ENODEV;

	count = device_property_count_u32(&pdev->dev, "dma-masters");
	अगर (count < 0) अणु
		dev_err(&pdev->dev, "Can't get DMA master(s) node\n");
		वापस -ENODEV;
	पूर्ण

	sपंचांग32_dmamux = devm_kzalloc(&pdev->dev, माप(*sपंचांग32_dmamux) +
				    माप(u32) * (count + 1), GFP_KERNEL);
	अगर (!sपंचांग32_dmamux)
		वापस -ENOMEM;

	dma_req = 0;
	क्रम (i = 1; i <= count; i++) अणु
		dma_node = of_parse_phandle(node, "dma-masters", i - 1);

		match = of_match_node(sपंचांग32_sपंचांग32dma_master_match, dma_node);
		अगर (!match) अणु
			dev_err(&pdev->dev, "DMA master is not supported\n");
			of_node_put(dma_node);
			वापस -EINVAL;
		पूर्ण

		अगर (of_property_पढ़ो_u32(dma_node, "dma-requests",
					 &sपंचांग32_dmamux->dma_reqs[i])) अणु
			dev_info(&pdev->dev,
				 "Missing MUX output information, using %u.\n",
				 STM32_DMAMUX_MAX_DMA_REQUESTS);
			sपंचांग32_dmamux->dma_reqs[i] =
				STM32_DMAMUX_MAX_DMA_REQUESTS;
		पूर्ण
		dma_req += sपंचांग32_dmamux->dma_reqs[i];
		of_node_put(dma_node);
	पूर्ण

	अगर (dma_req > STM32_DMAMUX_MAX_DMA_REQUESTS) अणु
		dev_err(&pdev->dev, "Too many DMA Master Requests to manage\n");
		वापस -ENODEV;
	पूर्ण

	sपंचांग32_dmamux->dma_requests = dma_req;
	sपंचांग32_dmamux->dma_reqs[0] = count;
	sपंचांग32_dmamux->dma_inuse = devm_kसुस्मृति(&pdev->dev,
					       BITS_TO_LONGS(dma_req),
					       माप(अचिन्हित दीर्घ),
					       GFP_KERNEL);
	अगर (!sपंचांग32_dmamux->dma_inuse)
		वापस -ENOMEM;

	अगर (device_property_पढ़ो_u32(&pdev->dev, "dma-requests",
				     &sपंचांग32_dmamux->dmamux_requests)) अणु
		sपंचांग32_dmamux->dmamux_requests = STM32_DMAMUX_MAX_REQUESTS;
		dev_warn(&pdev->dev, "DMAMUX defaulting on %u requests\n",
			 sपंचांग32_dmamux->dmamux_requests);
	पूर्ण
	pm_runसमय_get_noresume(&pdev->dev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	iomem = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(iomem))
		वापस PTR_ERR(iomem);

	spin_lock_init(&sपंचांग32_dmamux->lock);

	sपंचांग32_dmamux->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(sपंचांग32_dmamux->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(sपंचांग32_dmamux->clk),
				     "Missing clock controller\n");

	ret = clk_prepare_enable(sपंचांग32_dmamux->clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "clk_prep_enable error: %d\n", ret);
		वापस ret;
	पूर्ण

	rst = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(rst)) अणु
		ret = PTR_ERR(rst);
		अगर (ret == -EPROBE_DEFER)
			जाओ err_clk;
	पूर्ण अन्यथा अणु
		reset_control_निश्चित(rst);
		udelay(2);
		reset_control_deनिश्चित(rst);
	पूर्ण

	sपंचांग32_dmamux->iomem = iomem;
	sपंचांग32_dmamux->dmarouter.dev = &pdev->dev;
	sपंचांग32_dmamux->dmarouter.route_मुक्त = sपंचांग32_dmamux_मुक्त;

	platक्रमm_set_drvdata(pdev, sपंचांग32_dmamux);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	pm_runसमय_get_noresume(&pdev->dev);

	/* Reset the dmamux */
	क्रम (i = 0; i < sपंचांग32_dmamux->dma_requests; i++)
		sपंचांग32_dmamux_ग_लिखो(sपंचांग32_dmamux->iomem, STM32_DMAMUX_CCR(i), 0);

	pm_runसमय_put(&pdev->dev);

	ret = of_dma_router_रेजिस्टर(node, sपंचांग32_dmamux_route_allocate,
				     &sपंचांग32_dmamux->dmarouter);
	अगर (ret)
		जाओ err_clk;

	वापस 0;

err_clk:
	clk_disable_unprepare(sपंचांग32_dmamux->clk);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sपंचांग32_dmamux_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा sपंचांग32_dmamux_data *sपंचांग32_dmamux = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(sपंचांग32_dmamux->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_dmamux_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा sपंचांग32_dmamux_data *sपंचांग32_dmamux = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = clk_prepare_enable(sपंचांग32_dmamux->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to prepare_enable clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांग32_dmamux_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा sपंचांग32_dmamux_data *sपंचांग32_dmamux = platक्रमm_get_drvdata(pdev);
	पूर्णांक i, ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < sपंचांग32_dmamux->dma_requests; i++)
		sपंचांग32_dmamux->ccr[i] = sपंचांग32_dmamux_पढ़ो(sपंचांग32_dmamux->iomem,
							 STM32_DMAMUX_CCR(i));

	pm_runसमय_put_sync(dev);

	pm_runसमय_क्रमce_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_dmamux_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा sपंचांग32_dmamux_data *sपंचांग32_dmamux = platक्रमm_get_drvdata(pdev);
	पूर्णांक i, ret;

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret < 0)
		वापस ret;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < sपंचांग32_dmamux->dma_requests; i++)
		sपंचांग32_dmamux_ग_लिखो(sपंचांग32_dmamux->iomem, STM32_DMAMUX_CCR(i),
				   sपंचांग32_dmamux->ccr[i]);

	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_dmamux_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_dmamux_suspend, sपंचांग32_dmamux_resume)
	SET_RUNTIME_PM_OPS(sपंचांग32_dmamux_runसमय_suspend,
			   sपंचांग32_dmamux_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_dmamux_match[] = अणु
	अणु .compatible = "st,stm32h7-dmamux" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver sपंचांग32_dmamux_driver = अणु
	.probe	= sपंचांग32_dmamux_probe,
	.driver = अणु
		.name = "stm32-dmamux",
		.of_match_table = sपंचांग32_dmamux_match,
		.pm = &sपंचांग32_dmamux_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sपंचांग32_dmamux_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sपंचांग32_dmamux_driver);
पूर्ण
arch_initcall(sपंचांग32_dmamux_init);

MODULE_DESCRIPTION("DMA Router driver for STM32 DMA MUX");
MODULE_AUTHOR("M'boumba Cedric Madianga <cedric.madianga@gmail.com>");
MODULE_AUTHOR("Pierre-Yves Mordret <pierre-yves.mordret@st.com>");
MODULE_LICENSE("GPL v2");
