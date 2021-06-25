<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic PXA PATA driver
 *
 * Copyright (C) 2010 Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/ata.h>
#समावेश <linux/libata.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>

#समावेश <scsi/scsi_host.h>

#समावेश <linux/platक्रमm_data/ata-pxa.h>

#घोषणा DRV_NAME	"pata_pxa"
#घोषणा DRV_VERSION	"0.1"

काष्ठा pata_pxa_data अणु
	काष्ठा dma_chan		*dma_chan;
	dma_cookie_t		dma_cookie;
	काष्ठा completion	dma_करोne;
पूर्ण;

/*
 * DMA पूर्णांकerrupt handler.
 */
अटल व्योम pxa_ata_dma_irq(व्योम *d)
अणु
	काष्ठा pata_pxa_data *pd = d;
	क्रमागत dma_status status;

	status = dmaengine_tx_status(pd->dma_chan, pd->dma_cookie, शून्य);
	अगर (status == DMA_ERROR || status == DMA_COMPLETE)
		complete(&pd->dma_करोne);
पूर्ण

/*
 * Prepare taskfile क्रम submission.
 */
अटल क्रमागत ata_completion_errors pxa_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा pata_pxa_data *pd = qc->ap->निजी_data;
	काष्ठा dma_async_tx_descriptor *tx;
	क्रमागत dma_transfer_direction dir;

	अगर (!(qc->flags & ATA_QCFLAG_DMAMAP))
		वापस AC_ERR_OK;

	dir = (qc->dma_dir == DMA_TO_DEVICE ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM);
	tx = dmaengine_prep_slave_sg(pd->dma_chan, qc->sg, qc->n_elem, dir,
				     DMA_PREP_INTERRUPT);
	अगर (!tx) अणु
		ata_dev_err(qc->dev, "prep_slave_sg() failed\n");
		वापस AC_ERR_OK;
	पूर्ण
	tx->callback = pxa_ata_dma_irq;
	tx->callback_param = pd;
	pd->dma_cookie = dmaengine_submit(tx);

	वापस AC_ERR_OK;
पूर्ण

/*
 * Configure the DMA controller, load the DMA descriptors, but करोn't start the
 * DMA controller yet. Only issue the ATA command.
 */
अटल व्योम pxa_bmdma_setup(काष्ठा ata_queued_cmd *qc)
अणु
	qc->ap->ops->sff_exec_command(qc->ap, &qc->tf);
पूर्ण

/*
 * Execute the DMA transfer.
 */
अटल व्योम pxa_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा pata_pxa_data *pd = qc->ap->निजी_data;
	init_completion(&pd->dma_करोne);
	dma_async_issue_pending(pd->dma_chan);
पूर्ण

/*
 * Wait until the DMA transfer completes, then stop the DMA controller.
 */
अटल व्योम pxa_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा pata_pxa_data *pd = qc->ap->निजी_data;
	क्रमागत dma_status status;

	status = dmaengine_tx_status(pd->dma_chan, pd->dma_cookie, शून्य);
	अगर (status != DMA_ERROR && status != DMA_COMPLETE &&
	    रुको_क्रम_completion_समयout(&pd->dma_करोne, HZ))
		ata_dev_err(qc->dev, "Timeout waiting for DMA completion!");

	dmaengine_terminate_all(pd->dma_chan);
पूर्ण

/*
 * Read DMA status. The bmdma_stop() will take care of properly finishing the
 * DMA transfer so we always have DMA-complete पूर्णांकerrupt here.
 */
अटल अचिन्हित अक्षर pxa_bmdma_status(काष्ठा ata_port *ap)
अणु
	काष्ठा pata_pxa_data *pd = ap->निजी_data;
	अचिन्हित अक्षर ret = ATA_DMA_INTR;
	काष्ठा dma_tx_state state;
	क्रमागत dma_status status;

	status = dmaengine_tx_status(pd->dma_chan, pd->dma_cookie, &state);
	अगर (status != DMA_COMPLETE)
		ret |= ATA_DMA_ERR;

	वापस ret;
पूर्ण

/*
 * No IRQ रेजिस्टर present so we करो nothing.
 */
अटल व्योम pxa_irq_clear(काष्ठा ata_port *ap)
अणु
पूर्ण

/*
 * Check क्रम ATAPI DMA. ATAPI DMA is unsupported by this driver. It's still
 * unclear why ATAPI has DMA issues.
 */
अटल पूर्णांक pxa_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा pxa_ata_sht = अणु
	ATA_BMDMA_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations pxa_ata_port_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	.cable_detect		= ata_cable_40wire,

	.bmdma_setup		= pxa_bmdma_setup,
	.bmdma_start		= pxa_bmdma_start,
	.bmdma_stop		= pxa_bmdma_stop,
	.bmdma_status		= pxa_bmdma_status,

	.check_atapi_dma	= pxa_check_atapi_dma,

	.sff_irq_clear		= pxa_irq_clear,

	.qc_prep		= pxa_qc_prep,
पूर्ण;

अटल पूर्णांक pxa_ata_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	काष्ठा pata_pxa_data *data;
	काष्ठा resource *cmd_res;
	काष्ठा resource *ctl_res;
	काष्ठा resource *dma_res;
	काष्ठा resource *irq_res;
	काष्ठा pata_pxa_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा dma_slave_config	config;
	पूर्णांक ret = 0;

	/*
	 * Resource validation, three resources are needed:
	 *  - CMD port base address
	 *  - CTL port base address
	 *  - DMA port base address
	 *  - IRQ pin
	 */
	अगर (pdev->num_resources != 4) अणु
		dev_err(&pdev->dev, "invalid number of resources\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * CMD port base address
	 */
	cmd_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (unlikely(cmd_res == शून्य))
		वापस -EINVAL;

	/*
	 * CTL port base address
	 */
	ctl_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (unlikely(ctl_res == शून्य))
		वापस -EINVAL;

	/*
	 * DMA port base address
	 */
	dma_res = platक्रमm_get_resource(pdev, IORESOURCE_DMA, 0);
	अगर (unlikely(dma_res == शून्य))
		वापस -EINVAL;

	/*
	 * IRQ pin
	 */
	irq_res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (unlikely(irq_res == शून्य))
		वापस -EINVAL;

	/*
	 * Allocate the host
	 */
	host = ata_host_alloc(&pdev->dev, 1);
	अगर (!host)
		वापस -ENOMEM;

	ap		= host->ports[0];
	ap->ops		= &pxa_ata_port_ops;
	ap->pio_mask	= ATA_PIO4;
	ap->mwdma_mask	= ATA_MWDMA2;

	ap->ioaddr.cmd_addr	= devm_ioremap(&pdev->dev, cmd_res->start,
						resource_size(cmd_res));
	ap->ioaddr.ctl_addr	= devm_ioremap(&pdev->dev, ctl_res->start,
						resource_size(ctl_res));
	ap->ioaddr.bmdma_addr	= devm_ioremap(&pdev->dev, dma_res->start,
						resource_size(dma_res));

	/*
	 * Adjust रेजिस्टर offsets
	 */
	ap->ioaddr.altstatus_addr = ap->ioaddr.ctl_addr;
	ap->ioaddr.data_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_DATA << pdata->reg_shअगरt);
	ap->ioaddr.error_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_ERR << pdata->reg_shअगरt);
	ap->ioaddr.feature_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_FEATURE << pdata->reg_shअगरt);
	ap->ioaddr.nsect_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_NSECT << pdata->reg_shअगरt);
	ap->ioaddr.lbal_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_LBAL << pdata->reg_shअगरt);
	ap->ioaddr.lbam_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_LBAM << pdata->reg_shअगरt);
	ap->ioaddr.lbah_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_LBAH << pdata->reg_shअगरt);
	ap->ioaddr.device_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_DEVICE << pdata->reg_shअगरt);
	ap->ioaddr.status_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_STATUS << pdata->reg_shअगरt);
	ap->ioaddr.command_addr	= ap->ioaddr.cmd_addr +
					(ATA_REG_CMD << pdata->reg_shअगरt);

	/*
	 * Allocate and load driver's पूर्णांकernal data काष्ठाure
	 */
	data = devm_kzalloc(&pdev->dev, माप(काष्ठा pata_pxa_data),
								GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	ap->निजी_data = data;

	स_रखो(&config, 0, माप(config));
	config.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	config.dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	config.src_addr = dma_res->start;
	config.dst_addr = dma_res->start;
	config.src_maxburst = 32;
	config.dst_maxburst = 32;

	/*
	 * Request the DMA channel
	 */
	data->dma_chan =
		dma_request_slave_channel(&pdev->dev, "data");
	अगर (!data->dma_chan)
		वापस -EBUSY;
	ret = dmaengine_slave_config(data->dma_chan, &config);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "dma configuration failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Activate the ATA host
	 */
	ret = ata_host_activate(host, irq_res->start, ata_sff_पूर्णांकerrupt,
				pdata->irq_flags, &pxa_ata_sht);
	अगर (ret)
		dma_release_channel(data->dma_chan);

	वापस ret;
पूर्ण

अटल पूर्णांक pxa_ata_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा pata_pxa_data *data = host->ports[0]->निजी_data;

	dma_release_channel(data->dma_chan);

	ata_host_detach(host);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pxa_ata_driver = अणु
	.probe		= pxa_ata_probe,
	.हटाओ		= pxa_ata_हटाओ,
	.driver		= अणु
		.name		= DRV_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pxa_ata_driver);

MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("DMA-capable driver for PATA on PXA CPU");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);
MODULE_ALIAS("platform:" DRV_NAME);
