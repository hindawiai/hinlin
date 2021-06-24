<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2013-2014 Freescale Semiconductor, Inc
// Copyright (c) 2017 Sysam, Angelo Dureghello  <angelo@sysam.it>

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/dma-mcf-edma.h>

#समावेश "fsl-edma-common.h"

#घोषणा EDMA_CHANNELS		64
#घोषणा EDMA_MASK_CH(x)		((x) & GENMASK(5, 0))

अटल irqवापस_t mcf_edma_tx_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fsl_edma_engine *mcf_edma = dev_id;
	काष्ठा edma_regs *regs = &mcf_edma->regs;
	अचिन्हित पूर्णांक ch;
	काष्ठा fsl_edma_chan *mcf_chan;
	u64 पूर्णांकmap;

	पूर्णांकmap = ioपढ़ो32(regs->पूर्णांकh);
	पूर्णांकmap <<= 32;
	पूर्णांकmap |= ioपढ़ो32(regs->पूर्णांकl);
	अगर (!पूर्णांकmap)
		वापस IRQ_NONE;

	क्रम (ch = 0; ch < mcf_edma->n_chans; ch++) अणु
		अगर (पूर्णांकmap & BIT(ch)) अणु
			ioग_लिखो8(EDMA_MASK_CH(ch), regs->cपूर्णांक);

			mcf_chan = &mcf_edma->chans[ch];

			spin_lock(&mcf_chan->vchan.lock);

			अगर (!mcf_chan->edesc) अणु
				/* terminate_all called beक्रमe */
				spin_unlock(&mcf_chan->vchan.lock);
				जारी;
			पूर्ण

			अगर (!mcf_chan->edesc->iscyclic) अणु
				list_del(&mcf_chan->edesc->vdesc.node);
				vchan_cookie_complete(&mcf_chan->edesc->vdesc);
				mcf_chan->edesc = शून्य;
				mcf_chan->status = DMA_COMPLETE;
				mcf_chan->idle = true;
			पूर्ण अन्यथा अणु
				vchan_cyclic_callback(&mcf_chan->edesc->vdesc);
			पूर्ण

			अगर (!mcf_chan->edesc)
				fsl_edma_xfer_desc(mcf_chan);

			spin_unlock(&mcf_chan->vchan.lock);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mcf_edma_err_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fsl_edma_engine *mcf_edma = dev_id;
	काष्ठा edma_regs *regs = &mcf_edma->regs;
	अचिन्हित पूर्णांक err, ch;

	err = ioपढ़ो32(regs->errl);
	अगर (!err)
		वापस IRQ_NONE;

	क्रम (ch = 0; ch < (EDMA_CHANNELS / 2); ch++) अणु
		अगर (err & BIT(ch)) अणु
			fsl_edma_disable_request(&mcf_edma->chans[ch]);
			ioग_लिखो8(EDMA_CERR_CERR(ch), regs->cerr);
			mcf_edma->chans[ch].status = DMA_ERROR;
			mcf_edma->chans[ch].idle = true;
		पूर्ण
	पूर्ण

	err = ioपढ़ो32(regs->errh);
	अगर (!err)
		वापस IRQ_NONE;

	क्रम (ch = (EDMA_CHANNELS / 2); ch < EDMA_CHANNELS; ch++) अणु
		अगर (err & (BIT(ch - (EDMA_CHANNELS / 2)))) अणु
			fsl_edma_disable_request(&mcf_edma->chans[ch]);
			ioग_लिखो8(EDMA_CERR_CERR(ch), regs->cerr);
			mcf_edma->chans[ch].status = DMA_ERROR;
			mcf_edma->chans[ch].idle = true;
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mcf_edma_irq_init(काष्ठा platक्रमm_device *pdev,
				काष्ठा fsl_edma_engine *mcf_edma)
अणु
	पूर्णांक ret = 0, i;
	काष्ठा resource *res;

	res = platक्रमm_get_resource_byname(pdev,
				IORESOURCE_IRQ, "edma-tx-00-15");
	अगर (!res)
		वापस -1;

	क्रम (ret = 0, i = res->start; i <= res->end; ++i)
		ret |= request_irq(i, mcf_edma_tx_handler, 0, "eDMA", mcf_edma);
	अगर (ret)
		वापस ret;

	res = platक्रमm_get_resource_byname(pdev,
			IORESOURCE_IRQ, "edma-tx-16-55");
	अगर (!res)
		वापस -1;

	क्रम (ret = 0, i = res->start; i <= res->end; ++i)
		ret |= request_irq(i, mcf_edma_tx_handler, 0, "eDMA", mcf_edma);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_get_irq_byname(pdev, "edma-tx-56-63");
	अगर (ret != -ENXIO) अणु
		ret = request_irq(ret, mcf_edma_tx_handler,
				  0, "eDMA", mcf_edma);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = platक्रमm_get_irq_byname(pdev, "edma-err");
	अगर (ret != -ENXIO) अणु
		ret = request_irq(ret, mcf_edma_err_handler,
				  0, "eDMA", mcf_edma);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mcf_edma_irq_मुक्त(काष्ठा platक्रमm_device *pdev,
				काष्ठा fsl_edma_engine *mcf_edma)
अणु
	पूर्णांक irq;
	काष्ठा resource *res;

	res = platक्रमm_get_resource_byname(pdev,
			IORESOURCE_IRQ, "edma-tx-00-15");
	अगर (res) अणु
		क्रम (irq = res->start; irq <= res->end; irq++)
			मुक्त_irq(irq, mcf_edma);
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev,
			IORESOURCE_IRQ, "edma-tx-16-55");
	अगर (res) अणु
		क्रम (irq = res->start; irq <= res->end; irq++)
			मुक्त_irq(irq, mcf_edma);
	पूर्ण

	irq = platक्रमm_get_irq_byname(pdev, "edma-tx-56-63");
	अगर (irq != -ENXIO)
		मुक्त_irq(irq, mcf_edma);

	irq = platक्रमm_get_irq_byname(pdev, "edma-err");
	अगर (irq != -ENXIO)
		मुक्त_irq(irq, mcf_edma);
पूर्ण

अटल काष्ठा fsl_edma_drvdata mcf_data = अणु
	.version = v2,
	.setup_irq = mcf_edma_irq_init,
पूर्ण;

अटल पूर्णांक mcf_edma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mcf_edma_platक्रमm_data *pdata;
	काष्ठा fsl_edma_engine *mcf_edma;
	काष्ठा fsl_edma_chan *mcf_chan;
	काष्ठा edma_regs *regs;
	काष्ठा resource *res;
	पूर्णांक ret, i, len, chans;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no platform data supplied\n");
		वापस -EINVAL;
	पूर्ण

	chans = pdata->dma_channels;
	len = माप(*mcf_edma) + माप(*mcf_chan) * chans;
	mcf_edma = devm_kzalloc(&pdev->dev, len, GFP_KERNEL);
	अगर (!mcf_edma)
		वापस -ENOMEM;

	mcf_edma->n_chans = chans;

	/* Set up drvdata क्रम ColdFire edma */
	mcf_edma->drvdata = &mcf_data;
	mcf_edma->big_endian = 1;

	अगर (!mcf_edma->n_chans) अणु
		dev_info(&pdev->dev, "setting default channel number to 64");
		mcf_edma->n_chans = 64;
	पूर्ण

	mutex_init(&mcf_edma->fsl_edma_mutex);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	mcf_edma->membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mcf_edma->membase))
		वापस PTR_ERR(mcf_edma->membase);

	fsl_edma_setup_regs(mcf_edma);
	regs = &mcf_edma->regs;

	INIT_LIST_HEAD(&mcf_edma->dma_dev.channels);
	क्रम (i = 0; i < mcf_edma->n_chans; i++) अणु
		काष्ठा fsl_edma_chan *mcf_chan = &mcf_edma->chans[i];

		mcf_chan->edma = mcf_edma;
		mcf_chan->slave_id = i;
		mcf_chan->idle = true;
		mcf_chan->dma_dir = DMA_NONE;
		mcf_chan->vchan.desc_मुक्त = fsl_edma_मुक्त_desc;
		vchan_init(&mcf_chan->vchan, &mcf_edma->dma_dev);
		ioग_लिखो32(0x0, &regs->tcd[i].csr);
	पूर्ण

	ioग_लिखो32(~0, regs->पूर्णांकh);
	ioग_लिखो32(~0, regs->पूर्णांकl);

	ret = mcf_edma->drvdata->setup_irq(pdev, mcf_edma);
	अगर (ret)
		वापस ret;

	dma_cap_set(DMA_PRIVATE, mcf_edma->dma_dev.cap_mask);
	dma_cap_set(DMA_SLAVE, mcf_edma->dma_dev.cap_mask);
	dma_cap_set(DMA_CYCLIC, mcf_edma->dma_dev.cap_mask);

	mcf_edma->dma_dev.dev = &pdev->dev;
	mcf_edma->dma_dev.device_alloc_chan_resources =
			fsl_edma_alloc_chan_resources;
	mcf_edma->dma_dev.device_मुक्त_chan_resources =
			fsl_edma_मुक्त_chan_resources;
	mcf_edma->dma_dev.device_config = fsl_edma_slave_config;
	mcf_edma->dma_dev.device_prep_dma_cyclic =
			fsl_edma_prep_dma_cyclic;
	mcf_edma->dma_dev.device_prep_slave_sg = fsl_edma_prep_slave_sg;
	mcf_edma->dma_dev.device_tx_status = fsl_edma_tx_status;
	mcf_edma->dma_dev.device_छोड़ो = fsl_edma_छोड़ो;
	mcf_edma->dma_dev.device_resume = fsl_edma_resume;
	mcf_edma->dma_dev.device_terminate_all = fsl_edma_terminate_all;
	mcf_edma->dma_dev.device_issue_pending = fsl_edma_issue_pending;

	mcf_edma->dma_dev.src_addr_widths = FSL_EDMA_BUSWIDTHS;
	mcf_edma->dma_dev.dst_addr_widths = FSL_EDMA_BUSWIDTHS;
	mcf_edma->dma_dev.directions =
			BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);

	mcf_edma->dma_dev.filter.fn = mcf_edma_filter_fn;
	mcf_edma->dma_dev.filter.map = pdata->slave_map;
	mcf_edma->dma_dev.filter.mapcnt = pdata->slavecnt;

	platक्रमm_set_drvdata(pdev, mcf_edma);

	ret = dma_async_device_रेजिस्टर(&mcf_edma->dma_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Can't register Freescale eDMA engine. (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* Enable round robin arbitration */
	ioग_लिखो32(EDMA_CR_ERGA | EDMA_CR_ERCA, regs->cr);

	वापस 0;
पूर्ण

अटल पूर्णांक mcf_edma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_edma_engine *mcf_edma = platक्रमm_get_drvdata(pdev);

	mcf_edma_irq_मुक्त(pdev, mcf_edma);
	fsl_edma_cleanup_vchan(&mcf_edma->dma_dev);
	dma_async_device_unरेजिस्टर(&mcf_edma->dma_dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mcf_edma_driver = अणु
	.driver		= अणु
		.name	= "mcf-edma",
	पूर्ण,
	.probe		= mcf_edma_probe,
	.हटाओ		= mcf_edma_हटाओ,
पूर्ण;

bool mcf_edma_filter_fn(काष्ठा dma_chan *chan, व्योम *param)
अणु
	अगर (chan->device->dev->driver == &mcf_edma_driver.driver) अणु
		काष्ठा fsl_edma_chan *mcf_chan = to_fsl_edma_chan(chan);

		वापस (mcf_chan->slave_id == (uपूर्णांकptr_t)param);
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(mcf_edma_filter_fn);

अटल पूर्णांक __init mcf_edma_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&mcf_edma_driver);
पूर्ण
subsys_initcall(mcf_edma_init);

अटल व्योम __निकास mcf_edma_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mcf_edma_driver);
पूर्ण
module_निकास(mcf_edma_निकास);

MODULE_ALIAS("platform:mcf-edma");
MODULE_DESCRIPTION("Freescale eDMA engine driver, ColdFire family");
MODULE_LICENSE("GPL v2");
