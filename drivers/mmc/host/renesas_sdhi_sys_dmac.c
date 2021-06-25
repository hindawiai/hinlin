<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DMA support use of SYS DMAC with SDHI SD/SDIO controller
 *
 * Copyright (C) 2016-19 Renesas Electronics Corporation
 * Copyright (C) 2016-19 Sang Engineering, Wolfram Sang
 * Copyright (C) 2017 Horms Solutions, Simon Horman
 * Copyright (C) 2010-2011 Guennadi Liakhovetski
 */

#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sys_soc.h>

#समावेश "renesas_sdhi.h"
#समावेश "tmio_mmc.h"

#घोषणा TMIO_MMC_MIN_DMA_LEN 8

अटल स्थिर काष्ठा renesas_sdhi_of_data of_शेष_cfg = अणु
	.पंचांगio_flags = TMIO_MMC_HAS_IDLE_WAIT,
पूर्ण;

अटल स्थिर काष्ठा renesas_sdhi_of_data of_rz_compatible = अणु
	.पंचांगio_flags	= TMIO_MMC_HAS_IDLE_WAIT | TMIO_MMC_32BIT_DATA_PORT |
			  TMIO_MMC_HAVE_CBSY,
	.पंचांगio_ocr_mask	= MMC_VDD_32_33,
	.capabilities	= MMC_CAP_SD_HIGHSPEED | MMC_CAP_SDIO_IRQ |
			  MMC_CAP_WAIT_WHILE_BUSY,
पूर्ण;

अटल स्थिर काष्ठा renesas_sdhi_of_data of_rcar_gen1_compatible = अणु
	.पंचांगio_flags	= TMIO_MMC_HAS_IDLE_WAIT | TMIO_MMC_CLK_ACTUAL,
	.capabilities	= MMC_CAP_SD_HIGHSPEED | MMC_CAP_SDIO_IRQ |
			  MMC_CAP_WAIT_WHILE_BUSY,
	.capabilities2	= MMC_CAP2_NO_WRITE_PROTECT,
पूर्ण;

/* Definitions क्रम sampling घड़ीs */
अटल काष्ठा renesas_sdhi_scc rcar_gen2_scc_taps[] = अणु
	अणु
		.clk_rate = 156000000,
		.tap = 0x00000703,
	पूर्ण,
	अणु
		.clk_rate = 0,
		.tap = 0x00000300,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा renesas_sdhi_of_data of_rcar_gen2_compatible = अणु
	.पंचांगio_flags	= TMIO_MMC_HAS_IDLE_WAIT | TMIO_MMC_CLK_ACTUAL |
			  TMIO_MMC_HAVE_CBSY | TMIO_MMC_MIN_RCAR2,
	.capabilities	= MMC_CAP_SD_HIGHSPEED | MMC_CAP_SDIO_IRQ |
			  MMC_CAP_CMD23 | MMC_CAP_WAIT_WHILE_BUSY,
	.capabilities2	= MMC_CAP2_NO_WRITE_PROTECT,
	.dma_buswidth	= DMA_SLAVE_BUSWIDTH_4_BYTES,
	.dma_rx_offset	= 0x2000,
	.scc_offset	= 0x0300,
	.taps		= rcar_gen2_scc_taps,
	.taps_num	= ARRAY_SIZE(rcar_gen2_scc_taps),
	.max_blk_count	= अच_पूर्णांक_उच्च / TMIO_MAX_BLK_SIZE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id renesas_sdhi_sys_dmac_of_match[] = अणु
	अणु .compatible = "renesas,sdhi-sh73a0", .data = &of_शेष_cfg, पूर्ण,
	अणु .compatible = "renesas,sdhi-r8a73a4", .data = &of_शेष_cfg, पूर्ण,
	अणु .compatible = "renesas,sdhi-r8a7740", .data = &of_शेष_cfg, पूर्ण,
	अणु .compatible = "renesas,sdhi-r7s72100", .data = &of_rz_compatible, पूर्ण,
	अणु .compatible = "renesas,sdhi-r8a7778", .data = &of_rcar_gen1_compatible, पूर्ण,
	अणु .compatible = "renesas,sdhi-r8a7779", .data = &of_rcar_gen1_compatible, पूर्ण,
	अणु .compatible = "renesas,sdhi-r8a7743", .data = &of_rcar_gen2_compatible, पूर्ण,
	अणु .compatible = "renesas,sdhi-r8a7745", .data = &of_rcar_gen2_compatible, पूर्ण,
	अणु .compatible = "renesas,sdhi-r8a7790", .data = &of_rcar_gen2_compatible, पूर्ण,
	अणु .compatible = "renesas,sdhi-r8a7791", .data = &of_rcar_gen2_compatible, पूर्ण,
	अणु .compatible = "renesas,sdhi-r8a7792", .data = &of_rcar_gen2_compatible, पूर्ण,
	अणु .compatible = "renesas,sdhi-r8a7793", .data = &of_rcar_gen2_compatible, पूर्ण,
	अणु .compatible = "renesas,sdhi-r8a7794", .data = &of_rcar_gen2_compatible, पूर्ण,
	अणु .compatible = "renesas,rcar-gen1-sdhi", .data = &of_rcar_gen1_compatible, पूर्ण,
	अणु .compatible = "renesas,rcar-gen2-sdhi", .data = &of_rcar_gen2_compatible, पूर्ण,
	अणु .compatible = "renesas,sdhi-shmobile" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, renesas_sdhi_sys_dmac_of_match);

अटल व्योम renesas_sdhi_sys_dmac_enable_dma(काष्ठा पंचांगio_mmc_host *host,
					     bool enable)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);

	अगर (!host->chan_tx || !host->chan_rx)
		वापस;

	अगर (priv->dma_priv.enable)
		priv->dma_priv.enable(host, enable);
पूर्ण

अटल व्योम renesas_sdhi_sys_dmac_पात_dma(काष्ठा पंचांगio_mmc_host *host)
अणु
	renesas_sdhi_sys_dmac_enable_dma(host, false);

	अगर (host->chan_rx)
		dmaengine_terminate_all(host->chan_rx);
	अगर (host->chan_tx)
		dmaengine_terminate_all(host->chan_tx);

	renesas_sdhi_sys_dmac_enable_dma(host, true);
पूर्ण

अटल व्योम renesas_sdhi_sys_dmac_dataend_dma(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);

	complete(&priv->dma_priv.dma_dataend);
पूर्ण

अटल व्योम renesas_sdhi_sys_dmac_dma_callback(व्योम *arg)
अणु
	काष्ठा पंचांगio_mmc_host *host = arg;
	काष्ठा renesas_sdhi *priv = host_to_priv(host);

	spin_lock_irq(&host->lock);

	अगर (!host->data)
		जाओ out;

	अगर (host->data->flags & MMC_DATA_READ)
		dma_unmap_sg(host->chan_rx->device->dev,
			     host->sg_ptr, host->sg_len,
			     DMA_FROM_DEVICE);
	अन्यथा
		dma_unmap_sg(host->chan_tx->device->dev,
			     host->sg_ptr, host->sg_len,
			     DMA_TO_DEVICE);

	spin_unlock_irq(&host->lock);

	रुको_क्रम_completion(&priv->dma_priv.dma_dataend);

	spin_lock_irq(&host->lock);
	पंचांगio_mmc_करो_data_irq(host);
out:
	spin_unlock_irq(&host->lock);
पूर्ण

अटल व्योम renesas_sdhi_sys_dmac_start_dma_rx(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);
	काष्ठा scatterlist *sg = host->sg_ptr, *sg_पंचांगp;
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	काष्ठा dma_chan *chan = host->chan_rx;
	dma_cookie_t cookie;
	पूर्णांक ret, i;
	bool aligned = true, multiple = true;
	अचिन्हित पूर्णांक align = (1 << host->pdata->alignment_shअगरt) - 1;

	क्रम_each_sg(sg, sg_पंचांगp, host->sg_len, i) अणु
		अगर (sg_पंचांगp->offset & align)
			aligned = false;
		अगर (sg_पंचांगp->length & align) अणु
			multiple = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((!aligned && (host->sg_len > 1 || sg->length > PAGE_SIZE ||
			  (align & PAGE_MASK))) || !multiple) अणु
		ret = -EINVAL;
		जाओ pio;
	पूर्ण

	अगर (sg->length < TMIO_MMC_MIN_DMA_LEN)
		वापस;

	/* The only sg element can be unaligned, use our bounce buffer then */
	अगर (!aligned) अणु
		sg_init_one(&host->bounce_sg, host->bounce_buf, sg->length);
		host->sg_ptr = &host->bounce_sg;
		sg = host->sg_ptr;
	पूर्ण

	ret = dma_map_sg(chan->device->dev, sg, host->sg_len, DMA_FROM_DEVICE);
	अगर (ret > 0)
		desc = dmaengine_prep_slave_sg(chan, sg, ret, DMA_DEV_TO_MEM,
					       DMA_CTRL_ACK);

	अगर (desc) अणु
		reinit_completion(&priv->dma_priv.dma_dataend);
		desc->callback = renesas_sdhi_sys_dmac_dma_callback;
		desc->callback_param = host;

		cookie = dmaengine_submit(desc);
		अगर (cookie < 0) अणु
			desc = शून्य;
			ret = cookie;
		पूर्ण
		host->dma_on = true;
	पूर्ण
pio:
	अगर (!desc) अणु
		/* DMA failed, fall back to PIO */
		renesas_sdhi_sys_dmac_enable_dma(host, false);
		अगर (ret >= 0)
			ret = -EIO;
		host->chan_rx = शून्य;
		dma_release_channel(chan);
		/* Free the Tx channel too */
		chan = host->chan_tx;
		अगर (chan) अणु
			host->chan_tx = शून्य;
			dma_release_channel(chan);
		पूर्ण
		dev_warn(&host->pdev->dev,
			 "DMA failed: %d, falling back to PIO\n", ret);
	पूर्ण
पूर्ण

अटल व्योम renesas_sdhi_sys_dmac_start_dma_tx(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);
	काष्ठा scatterlist *sg = host->sg_ptr, *sg_पंचांगp;
	काष्ठा dma_async_tx_descriptor *desc = शून्य;
	काष्ठा dma_chan *chan = host->chan_tx;
	dma_cookie_t cookie;
	पूर्णांक ret, i;
	bool aligned = true, multiple = true;
	अचिन्हित पूर्णांक align = (1 << host->pdata->alignment_shअगरt) - 1;

	क्रम_each_sg(sg, sg_पंचांगp, host->sg_len, i) अणु
		अगर (sg_पंचांगp->offset & align)
			aligned = false;
		अगर (sg_पंचांगp->length & align) अणु
			multiple = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((!aligned && (host->sg_len > 1 || sg->length > PAGE_SIZE ||
			  (align & PAGE_MASK))) || !multiple) अणु
		ret = -EINVAL;
		जाओ pio;
	पूर्ण

	अगर (sg->length < TMIO_MMC_MIN_DMA_LEN)
		वापस;

	/* The only sg element can be unaligned, use our bounce buffer then */
	अगर (!aligned) अणु
		अचिन्हित दीर्घ flags;
		व्योम *sg_vaddr = पंचांगio_mmc_kmap_atomic(sg, &flags);

		sg_init_one(&host->bounce_sg, host->bounce_buf, sg->length);
		स_नकल(host->bounce_buf, sg_vaddr, host->bounce_sg.length);
		पंचांगio_mmc_kunmap_atomic(sg, &flags, sg_vaddr);
		host->sg_ptr = &host->bounce_sg;
		sg = host->sg_ptr;
	पूर्ण

	ret = dma_map_sg(chan->device->dev, sg, host->sg_len, DMA_TO_DEVICE);
	अगर (ret > 0)
		desc = dmaengine_prep_slave_sg(chan, sg, ret, DMA_MEM_TO_DEV,
					       DMA_CTRL_ACK);

	अगर (desc) अणु
		reinit_completion(&priv->dma_priv.dma_dataend);
		desc->callback = renesas_sdhi_sys_dmac_dma_callback;
		desc->callback_param = host;

		cookie = dmaengine_submit(desc);
		अगर (cookie < 0) अणु
			desc = शून्य;
			ret = cookie;
		पूर्ण
		host->dma_on = true;
	पूर्ण
pio:
	अगर (!desc) अणु
		/* DMA failed, fall back to PIO */
		renesas_sdhi_sys_dmac_enable_dma(host, false);
		अगर (ret >= 0)
			ret = -EIO;
		host->chan_tx = शून्य;
		dma_release_channel(chan);
		/* Free the Rx channel too */
		chan = host->chan_rx;
		अगर (chan) अणु
			host->chan_rx = शून्य;
			dma_release_channel(chan);
		पूर्ण
		dev_warn(&host->pdev->dev,
			 "DMA failed: %d, falling back to PIO\n", ret);
	पूर्ण
पूर्ण

अटल व्योम renesas_sdhi_sys_dmac_start_dma(काष्ठा पंचांगio_mmc_host *host,
					    काष्ठा mmc_data *data)
अणु
	अगर (data->flags & MMC_DATA_READ) अणु
		अगर (host->chan_rx)
			renesas_sdhi_sys_dmac_start_dma_rx(host);
	पूर्ण अन्यथा अणु
		अगर (host->chan_tx)
			renesas_sdhi_sys_dmac_start_dma_tx(host);
	पूर्ण
पूर्ण

अटल व्योम renesas_sdhi_sys_dmac_issue_tasklet_fn(अचिन्हित दीर्घ priv)
अणु
	काष्ठा पंचांगio_mmc_host *host = (काष्ठा पंचांगio_mmc_host *)priv;
	काष्ठा dma_chan *chan = शून्य;

	spin_lock_irq(&host->lock);

	अगर (host->data) अणु
		अगर (host->data->flags & MMC_DATA_READ)
			chan = host->chan_rx;
		अन्यथा
			chan = host->chan_tx;
	पूर्ण

	spin_unlock_irq(&host->lock);

	पंचांगio_mmc_enable_mmc_irqs(host, TMIO_STAT_DATAEND);

	अगर (chan)
		dma_async_issue_pending(chan);
पूर्ण

अटल व्योम renesas_sdhi_sys_dmac_request_dma(काष्ठा पंचांगio_mmc_host *host,
					      काष्ठा पंचांगio_mmc_data *pdata)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);

	/* We can only either use DMA क्रम both Tx and Rx or not use it at all */
	अगर (!host->pdev->dev.of_node &&
	    (!pdata->chan_priv_tx || !pdata->chan_priv_rx))
		वापस;

	अगर (!host->chan_tx && !host->chan_rx) अणु
		काष्ठा resource *res = platक्रमm_get_resource(host->pdev,
							     IORESOURCE_MEM, 0);
		काष्ठा dma_slave_config cfg = अणुपूर्ण;
		dma_cap_mask_t mask;
		पूर्णांक ret;

		अगर (!res)
			वापस;

		dma_cap_zero(mask);
		dma_cap_set(DMA_SLAVE, mask);

		host->chan_tx = dma_request_slave_channel_compat(mask,
					priv->dma_priv.filter, pdata->chan_priv_tx,
					&host->pdev->dev, "tx");
		dev_dbg(&host->pdev->dev, "%s: TX: got channel %p\n", __func__,
			host->chan_tx);

		अगर (!host->chan_tx)
			वापस;

		cfg.direction = DMA_MEM_TO_DEV;
		cfg.dst_addr = res->start +
			(CTL_SD_DATA_PORT << host->bus_shअगरt);
		cfg.dst_addr_width = priv->dma_priv.dma_buswidth;
		अगर (!cfg.dst_addr_width)
			cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		cfg.src_addr = 0;
		ret = dmaengine_slave_config(host->chan_tx, &cfg);
		अगर (ret < 0)
			जाओ ecfgtx;

		host->chan_rx = dma_request_slave_channel_compat(mask,
					priv->dma_priv.filter, pdata->chan_priv_rx,
					&host->pdev->dev, "rx");
		dev_dbg(&host->pdev->dev, "%s: RX: got channel %p\n", __func__,
			host->chan_rx);

		अगर (!host->chan_rx)
			जाओ ereqrx;

		cfg.direction = DMA_DEV_TO_MEM;
		cfg.src_addr = cfg.dst_addr + host->pdata->dma_rx_offset;
		cfg.src_addr_width = priv->dma_priv.dma_buswidth;
		अगर (!cfg.src_addr_width)
			cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		cfg.dst_addr = 0;
		ret = dmaengine_slave_config(host->chan_rx, &cfg);
		अगर (ret < 0)
			जाओ ecfgrx;

		host->bounce_buf = (u8 *)__get_मुक्त_page(GFP_KERNEL | GFP_DMA);
		अगर (!host->bounce_buf)
			जाओ ebouncebuf;

		init_completion(&priv->dma_priv.dma_dataend);
		tasklet_init(&host->dma_issue,
			     renesas_sdhi_sys_dmac_issue_tasklet_fn,
			     (अचिन्हित दीर्घ)host);
	पूर्ण

	renesas_sdhi_sys_dmac_enable_dma(host, true);

	वापस;

ebouncebuf:
ecfgrx:
	dma_release_channel(host->chan_rx);
	host->chan_rx = शून्य;
ereqrx:
ecfgtx:
	dma_release_channel(host->chan_tx);
	host->chan_tx = शून्य;
पूर्ण

अटल व्योम renesas_sdhi_sys_dmac_release_dma(काष्ठा पंचांगio_mmc_host *host)
अणु
	अगर (host->chan_tx) अणु
		काष्ठा dma_chan *chan = host->chan_tx;

		host->chan_tx = शून्य;
		dma_release_channel(chan);
	पूर्ण
	अगर (host->chan_rx) अणु
		काष्ठा dma_chan *chan = host->chan_rx;

		host->chan_rx = शून्य;
		dma_release_channel(chan);
	पूर्ण
	अगर (host->bounce_buf) अणु
		मुक्त_pages((अचिन्हित दीर्घ)host->bounce_buf, 0);
		host->bounce_buf = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा पंचांगio_mmc_dma_ops renesas_sdhi_sys_dmac_dma_ops = अणु
	.start = renesas_sdhi_sys_dmac_start_dma,
	.enable = renesas_sdhi_sys_dmac_enable_dma,
	.request = renesas_sdhi_sys_dmac_request_dma,
	.release = renesas_sdhi_sys_dmac_release_dma,
	.पात = renesas_sdhi_sys_dmac_पात_dma,
	.dataend = renesas_sdhi_sys_dmac_dataend_dma,
पूर्ण;

अटल पूर्णांक renesas_sdhi_sys_dmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस renesas_sdhi_probe(pdev, &renesas_sdhi_sys_dmac_dma_ops);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops renesas_sdhi_sys_dmac_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(पंचांगio_mmc_host_runसमय_suspend,
			   पंचांगio_mmc_host_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver renesas_sys_dmac_sdhi_driver = अणु
	.driver		= अणु
		.name	= "sh_mobile_sdhi",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm	= &renesas_sdhi_sys_dmac_dev_pm_ops,
		.of_match_table = renesas_sdhi_sys_dmac_of_match,
	पूर्ण,
	.probe		= renesas_sdhi_sys_dmac_probe,
	.हटाओ		= renesas_sdhi_हटाओ,
पूर्ण;

module_platक्रमm_driver(renesas_sys_dmac_sdhi_driver);

MODULE_DESCRIPTION("Renesas SDHI driver");
MODULE_AUTHOR("Magnus Damm");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sh_mobile_sdhi");
