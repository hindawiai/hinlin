<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/dma/fsl-edma.c
 *
 * Copyright 2013-2014 Freescale Semiconductor, Inc.
 *
 * Driver क्रम the Freescale eDMA engine with flexible channel multiplexing
 * capability क्रम DMA request sources. The eDMA block can be found on some
 * Vybrid and Layerscape SoCs.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_dma.h>

#समावेश "fsl-edma-common.h"

अटल व्योम fsl_edma_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);

	vchan_synchronize(&fsl_chan->vchan);
पूर्ण

अटल irqवापस_t fsl_edma_tx_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fsl_edma_engine *fsl_edma = dev_id;
	अचिन्हित पूर्णांक पूर्णांकr, ch;
	काष्ठा edma_regs *regs = &fsl_edma->regs;
	काष्ठा fsl_edma_chan *fsl_chan;

	पूर्णांकr = edma_पढ़ोl(fsl_edma, regs->पूर्णांकl);
	अगर (!पूर्णांकr)
		वापस IRQ_NONE;

	क्रम (ch = 0; ch < fsl_edma->n_chans; ch++) अणु
		अगर (पूर्णांकr & (0x1 << ch)) अणु
			edma_ग_लिखोb(fsl_edma, EDMA_CINT_CINT(ch), regs->cपूर्णांक);

			fsl_chan = &fsl_edma->chans[ch];

			spin_lock(&fsl_chan->vchan.lock);

			अगर (!fsl_chan->edesc) अणु
				/* terminate_all called beक्रमe */
				spin_unlock(&fsl_chan->vchan.lock);
				जारी;
			पूर्ण

			अगर (!fsl_chan->edesc->iscyclic) अणु
				list_del(&fsl_chan->edesc->vdesc.node);
				vchan_cookie_complete(&fsl_chan->edesc->vdesc);
				fsl_chan->edesc = शून्य;
				fsl_chan->status = DMA_COMPLETE;
				fsl_chan->idle = true;
			पूर्ण अन्यथा अणु
				vchan_cyclic_callback(&fsl_chan->edesc->vdesc);
			पूर्ण

			अगर (!fsl_chan->edesc)
				fsl_edma_xfer_desc(fsl_chan);

			spin_unlock(&fsl_chan->vchan.lock);
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t fsl_edma_err_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fsl_edma_engine *fsl_edma = dev_id;
	अचिन्हित पूर्णांक err, ch;
	काष्ठा edma_regs *regs = &fsl_edma->regs;

	err = edma_पढ़ोl(fsl_edma, regs->errl);
	अगर (!err)
		वापस IRQ_NONE;

	क्रम (ch = 0; ch < fsl_edma->n_chans; ch++) अणु
		अगर (err & (0x1 << ch)) अणु
			fsl_edma_disable_request(&fsl_edma->chans[ch]);
			edma_ग_लिखोb(fsl_edma, EDMA_CERR_CERR(ch), regs->cerr);
			fsl_edma->chans[ch].status = DMA_ERROR;
			fsl_edma->chans[ch].idle = true;
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t fsl_edma_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	अगर (fsl_edma_tx_handler(irq, dev_id) == IRQ_HANDLED)
		वापस IRQ_HANDLED;

	वापस fsl_edma_err_handler(irq, dev_id);
पूर्ण

अटल काष्ठा dma_chan *fsl_edma_xlate(काष्ठा of_phandle_args *dma_spec,
		काष्ठा of_dma *ofdma)
अणु
	काष्ठा fsl_edma_engine *fsl_edma = ofdma->of_dma_data;
	काष्ठा dma_chan *chan, *_chan;
	काष्ठा fsl_edma_chan *fsl_chan;
	u32 dmamux_nr = fsl_edma->drvdata->dmamuxs;
	अचिन्हित दीर्घ chans_per_mux = fsl_edma->n_chans / dmamux_nr;

	अगर (dma_spec->args_count != 2)
		वापस शून्य;

	mutex_lock(&fsl_edma->fsl_edma_mutex);
	list_क्रम_each_entry_safe(chan, _chan, &fsl_edma->dma_dev.channels, device_node) अणु
		अगर (chan->client_count)
			जारी;
		अगर ((chan->chan_id / chans_per_mux) == dma_spec->args[0]) अणु
			chan = dma_get_slave_channel(chan);
			अगर (chan) अणु
				chan->device->निजीcnt++;
				fsl_chan = to_fsl_edma_chan(chan);
				fsl_chan->slave_id = dma_spec->args[1];
				fsl_edma_chan_mux(fsl_chan, fsl_chan->slave_id,
						true);
				mutex_unlock(&fsl_edma->fsl_edma_mutex);
				वापस chan;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&fsl_edma->fsl_edma_mutex);
	वापस शून्य;
पूर्ण

अटल पूर्णांक
fsl_edma_irq_init(काष्ठा platक्रमm_device *pdev, काष्ठा fsl_edma_engine *fsl_edma)
अणु
	पूर्णांक ret;

	fsl_edma->txirq = platक्रमm_get_irq_byname(pdev, "edma-tx");
	अगर (fsl_edma->txirq < 0)
		वापस fsl_edma->txirq;

	fsl_edma->errirq = platक्रमm_get_irq_byname(pdev, "edma-err");
	अगर (fsl_edma->errirq < 0)
		वापस fsl_edma->errirq;

	अगर (fsl_edma->txirq == fsl_edma->errirq) अणु
		ret = devm_request_irq(&pdev->dev, fsl_edma->txirq,
				fsl_edma_irq_handler, 0, "eDMA", fsl_edma);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Can't register eDMA IRQ.\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = devm_request_irq(&pdev->dev, fsl_edma->txirq,
				fsl_edma_tx_handler, 0, "eDMA tx", fsl_edma);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Can't register eDMA tx IRQ.\n");
			वापस ret;
		पूर्ण

		ret = devm_request_irq(&pdev->dev, fsl_edma->errirq,
				fsl_edma_err_handler, 0, "eDMA err", fsl_edma);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Can't register eDMA err IRQ.\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fsl_edma2_irq_init(काष्ठा platक्रमm_device *pdev,
		   काष्ठा fsl_edma_engine *fsl_edma)
अणु
	पूर्णांक i, ret, irq;
	पूर्णांक count;

	count = platक्रमm_irq_count(pdev);
	dev_dbg(&pdev->dev, "%s Found %d interrupts\r\n", __func__, count);
	अगर (count <= 2) अणु
		dev_err(&pdev->dev, "Interrupts in DTS not correct.\n");
		वापस -EINVAL;
	पूर्ण
	/*
	 * 16 channel independent पूर्णांकerrupts + 1 error पूर्णांकerrupt on i.mx7ulp.
	 * 2 channel share one पूर्णांकerrupt, क्रम example, ch0/ch16, ch1/ch17...
	 * For now, just simply request irq without IRQF_SHARED flag, since 16
	 * channels are enough on i.mx7ulp whose M4 करोमुख्य own some peripherals.
	 */
	क्रम (i = 0; i < count; i++) अणु
		irq = platक्रमm_get_irq(pdev, i);
		अगर (irq < 0)
			वापस -ENXIO;

		प्र_लिखो(fsl_edma->chans[i].chan_name, "eDMA2-CH%02d", i);

		/* The last IRQ is क्रम eDMA err */
		अगर (i == count - 1)
			ret = devm_request_irq(&pdev->dev, irq,
						fsl_edma_err_handler,
						0, "eDMA2-ERR", fsl_edma);
		अन्यथा
			ret = devm_request_irq(&pdev->dev, irq,
						fsl_edma_tx_handler, 0,
						fsl_edma->chans[i].chan_name,
						fsl_edma);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fsl_edma_irq_निकास(
		काष्ठा platक्रमm_device *pdev, काष्ठा fsl_edma_engine *fsl_edma)
अणु
	अगर (fsl_edma->txirq == fsl_edma->errirq) अणु
		devm_मुक्त_irq(&pdev->dev, fsl_edma->txirq, fsl_edma);
	पूर्ण अन्यथा अणु
		devm_मुक्त_irq(&pdev->dev, fsl_edma->txirq, fsl_edma);
		devm_मुक्त_irq(&pdev->dev, fsl_edma->errirq, fsl_edma);
	पूर्ण
पूर्ण

अटल व्योम fsl_disable_घड़ीs(काष्ठा fsl_edma_engine *fsl_edma, पूर्णांक nr_घड़ीs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_घड़ीs; i++)
		clk_disable_unprepare(fsl_edma->muxclk[i]);
पूर्ण

अटल काष्ठा fsl_edma_drvdata vf610_data = अणु
	.version = v1,
	.dmamuxs = DMAMUX_NR,
	.setup_irq = fsl_edma_irq_init,
पूर्ण;

अटल काष्ठा fsl_edma_drvdata ls1028a_data = अणु
	.version = v1,
	.dmamuxs = DMAMUX_NR,
	.mux_swap = true,
	.setup_irq = fsl_edma_irq_init,
पूर्ण;

अटल काष्ठा fsl_edma_drvdata imx7ulp_data = अणु
	.version = v3,
	.dmamuxs = 1,
	.has_dmaclk = true,
	.setup_irq = fsl_edma2_irq_init,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_edma_dt_ids[] = अणु
	अणु .compatible = "fsl,vf610-edma", .data = &vf610_dataपूर्ण,
	अणु .compatible = "fsl,ls1028a-edma", .data = &ls1028a_dataपूर्ण,
	अणु .compatible = "fsl,imx7ulp-edma", .data = &imx7ulp_dataपूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_edma_dt_ids);

अटल पूर्णांक fsl_edma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *of_id =
			of_match_device(fsl_edma_dt_ids, &pdev->dev);
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा fsl_edma_engine *fsl_edma;
	स्थिर काष्ठा fsl_edma_drvdata *drvdata = शून्य;
	काष्ठा fsl_edma_chan *fsl_chan;
	काष्ठा edma_regs *regs;
	काष्ठा resource *res;
	पूर्णांक len, chans;
	पूर्णांक ret, i;

	अगर (of_id)
		drvdata = of_id->data;
	अगर (!drvdata) अणु
		dev_err(&pdev->dev, "unable to find driver data\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "dma-channels", &chans);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't get dma-channels.\n");
		वापस ret;
	पूर्ण

	len = माप(*fsl_edma) + माप(*fsl_chan) * chans;
	fsl_edma = devm_kzalloc(&pdev->dev, len, GFP_KERNEL);
	अगर (!fsl_edma)
		वापस -ENOMEM;

	fsl_edma->drvdata = drvdata;
	fsl_edma->n_chans = chans;
	mutex_init(&fsl_edma->fsl_edma_mutex);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	fsl_edma->membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(fsl_edma->membase))
		वापस PTR_ERR(fsl_edma->membase);

	fsl_edma_setup_regs(fsl_edma);
	regs = &fsl_edma->regs;

	अगर (drvdata->has_dmaclk) अणु
		fsl_edma->dmaclk = devm_clk_get(&pdev->dev, "dma");
		अगर (IS_ERR(fsl_edma->dmaclk)) अणु
			dev_err(&pdev->dev, "Missing DMA block clock.\n");
			वापस PTR_ERR(fsl_edma->dmaclk);
		पूर्ण

		ret = clk_prepare_enable(fsl_edma->dmaclk);
		अगर (ret) अणु
			dev_err(&pdev->dev, "DMA clk block failed.\n");
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < fsl_edma->drvdata->dmamuxs; i++) अणु
		अक्षर clkname[32];

		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1 + i);
		fsl_edma->muxbase[i] = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(fsl_edma->muxbase[i])) अणु
			/* on error: disable all previously enabled clks */
			fsl_disable_घड़ीs(fsl_edma, i);
			वापस PTR_ERR(fsl_edma->muxbase[i]);
		पूर्ण

		प्र_लिखो(clkname, "dmamux%d", i);
		fsl_edma->muxclk[i] = devm_clk_get(&pdev->dev, clkname);
		अगर (IS_ERR(fsl_edma->muxclk[i])) अणु
			dev_err(&pdev->dev, "Missing DMAMUX block clock.\n");
			/* on error: disable all previously enabled clks */
			fsl_disable_घड़ीs(fsl_edma, i);
			वापस PTR_ERR(fsl_edma->muxclk[i]);
		पूर्ण

		ret = clk_prepare_enable(fsl_edma->muxclk[i]);
		अगर (ret)
			/* on error: disable all previously enabled clks */
			fsl_disable_घड़ीs(fsl_edma, i);

	पूर्ण

	fsl_edma->big_endian = of_property_पढ़ो_bool(np, "big-endian");

	INIT_LIST_HEAD(&fsl_edma->dma_dev.channels);
	क्रम (i = 0; i < fsl_edma->n_chans; i++) अणु
		काष्ठा fsl_edma_chan *fsl_chan = &fsl_edma->chans[i];

		fsl_chan->edma = fsl_edma;
		fsl_chan->pm_state = RUNNING;
		fsl_chan->slave_id = 0;
		fsl_chan->idle = true;
		fsl_chan->dma_dir = DMA_NONE;
		fsl_chan->vchan.desc_मुक्त = fsl_edma_मुक्त_desc;
		vchan_init(&fsl_chan->vchan, &fsl_edma->dma_dev);

		edma_ग_लिखोw(fsl_edma, 0x0, &regs->tcd[i].csr);
		fsl_edma_chan_mux(fsl_chan, 0, false);
	पूर्ण

	edma_ग_लिखोl(fsl_edma, ~0, regs->पूर्णांकl);
	ret = fsl_edma->drvdata->setup_irq(pdev, fsl_edma);
	अगर (ret)
		वापस ret;

	dma_cap_set(DMA_PRIVATE, fsl_edma->dma_dev.cap_mask);
	dma_cap_set(DMA_SLAVE, fsl_edma->dma_dev.cap_mask);
	dma_cap_set(DMA_CYCLIC, fsl_edma->dma_dev.cap_mask);

	fsl_edma->dma_dev.dev = &pdev->dev;
	fsl_edma->dma_dev.device_alloc_chan_resources
		= fsl_edma_alloc_chan_resources;
	fsl_edma->dma_dev.device_मुक्त_chan_resources
		= fsl_edma_मुक्त_chan_resources;
	fsl_edma->dma_dev.device_tx_status = fsl_edma_tx_status;
	fsl_edma->dma_dev.device_prep_slave_sg = fsl_edma_prep_slave_sg;
	fsl_edma->dma_dev.device_prep_dma_cyclic = fsl_edma_prep_dma_cyclic;
	fsl_edma->dma_dev.device_config = fsl_edma_slave_config;
	fsl_edma->dma_dev.device_छोड़ो = fsl_edma_छोड़ो;
	fsl_edma->dma_dev.device_resume = fsl_edma_resume;
	fsl_edma->dma_dev.device_terminate_all = fsl_edma_terminate_all;
	fsl_edma->dma_dev.device_synchronize = fsl_edma_synchronize;
	fsl_edma->dma_dev.device_issue_pending = fsl_edma_issue_pending;

	fsl_edma->dma_dev.src_addr_widths = FSL_EDMA_BUSWIDTHS;
	fsl_edma->dma_dev.dst_addr_widths = FSL_EDMA_BUSWIDTHS;
	fsl_edma->dma_dev.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);

	platक्रमm_set_drvdata(pdev, fsl_edma);

	ret = dma_async_device_रेजिस्टर(&fsl_edma->dma_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Can't register Freescale eDMA engine. (%d)\n", ret);
		fsl_disable_घड़ीs(fsl_edma, fsl_edma->drvdata->dmamuxs);
		वापस ret;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(np, fsl_edma_xlate, fsl_edma);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Can't register Freescale eDMA of_dma. (%d)\n", ret);
		dma_async_device_unरेजिस्टर(&fsl_edma->dma_dev);
		fsl_disable_घड़ीs(fsl_edma, fsl_edma->drvdata->dmamuxs);
		वापस ret;
	पूर्ण

	/* enable round robin arbitration */
	edma_ग_लिखोl(fsl_edma, EDMA_CR_ERGA | EDMA_CR_ERCA, regs->cr);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_edma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा fsl_edma_engine *fsl_edma = platक्रमm_get_drvdata(pdev);

	fsl_edma_irq_निकास(pdev, fsl_edma);
	fsl_edma_cleanup_vchan(&fsl_edma->dma_dev);
	of_dma_controller_मुक्त(np);
	dma_async_device_unरेजिस्टर(&fsl_edma->dma_dev);
	fsl_disable_घड़ीs(fsl_edma, fsl_edma->drvdata->dmamuxs);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_edma_suspend_late(काष्ठा device *dev)
अणु
	काष्ठा fsl_edma_engine *fsl_edma = dev_get_drvdata(dev);
	काष्ठा fsl_edma_chan *fsl_chan;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	क्रम (i = 0; i < fsl_edma->n_chans; i++) अणु
		fsl_chan = &fsl_edma->chans[i];
		spin_lock_irqsave(&fsl_chan->vchan.lock, flags);
		/* Make sure chan is idle or will क्रमce disable. */
		अगर (unlikely(!fsl_chan->idle)) अणु
			dev_warn(dev, "WARN: There is non-idle channel.");
			fsl_edma_disable_request(fsl_chan);
			fsl_edma_chan_mux(fsl_chan, 0, false);
		पूर्ण

		fsl_chan->pm_state = SUSPENDED;
		spin_unlock_irqrestore(&fsl_chan->vchan.lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_edma_resume_early(काष्ठा device *dev)
अणु
	काष्ठा fsl_edma_engine *fsl_edma = dev_get_drvdata(dev);
	काष्ठा fsl_edma_chan *fsl_chan;
	काष्ठा edma_regs *regs = &fsl_edma->regs;
	पूर्णांक i;

	क्रम (i = 0; i < fsl_edma->n_chans; i++) अणु
		fsl_chan = &fsl_edma->chans[i];
		fsl_chan->pm_state = RUNNING;
		edma_ग_लिखोw(fsl_edma, 0x0, &regs->tcd[i].csr);
		अगर (fsl_chan->slave_id != 0)
			fsl_edma_chan_mux(fsl_chan, fsl_chan->slave_id, true);
	पूर्ण

	edma_ग_लिखोl(fsl_edma, EDMA_CR_ERGA | EDMA_CR_ERCA, regs->cr);

	वापस 0;
पूर्ण

/*
 * eDMA provides the service to others, so it should be suspend late
 * and resume early. When eDMA suspend, all of the clients should stop
 * the DMA data transmission and let the channel idle.
 */
अटल स्थिर काष्ठा dev_pm_ops fsl_edma_pm_ops = अणु
	.suspend_late   = fsl_edma_suspend_late,
	.resume_early   = fsl_edma_resume_early,
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_edma_driver = अणु
	.driver		= अणु
		.name	= "fsl-edma",
		.of_match_table = fsl_edma_dt_ids,
		.pm     = &fsl_edma_pm_ops,
	पूर्ण,
	.probe          = fsl_edma_probe,
	.हटाओ		= fsl_edma_हटाओ,
पूर्ण;

अटल पूर्णांक __init fsl_edma_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&fsl_edma_driver);
पूर्ण
subsys_initcall(fsl_edma_init);

अटल व्योम __निकास fsl_edma_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&fsl_edma_driver);
पूर्ण
module_निकास(fsl_edma_निकास);

MODULE_ALIAS("platform:fsl-edma");
MODULE_DESCRIPTION("Freescale eDMA engine driver");
MODULE_LICENSE("GPL v2");
