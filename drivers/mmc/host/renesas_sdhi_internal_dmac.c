<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DMA support क्रम Internal DMAC with SDHI SD/SDIO controller
 *
 * Copyright (C) 2016-19 Renesas Electronics Corporation
 * Copyright (C) 2016-17 Horms Solutions, Simon Horman
 * Copyright (C) 2018-19 Sang Engineering, Wolfram Sang
 */

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/io-64-nonatomic-hi-lo.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/sys_soc.h>

#समावेश "renesas_sdhi.h"
#समावेश "tmio_mmc.h"

#घोषणा DM_CM_DTRAN_MODE	0x820
#घोषणा DM_CM_DTRAN_CTRL	0x828
#घोषणा DM_CM_RST		0x830
#घोषणा DM_CM_INFO1		0x840
#घोषणा DM_CM_INFO1_MASK	0x848
#घोषणा DM_CM_INFO2		0x850
#घोषणा DM_CM_INFO2_MASK	0x858
#घोषणा DM_DTRAN_ADDR		0x880

/* DM_CM_DTRAN_MODE */
#घोषणा DTRAN_MODE_CH_NUM_CH0	0	/* "downstream" = क्रम ग_लिखो commands */
#घोषणा DTRAN_MODE_CH_NUM_CH1	BIT(16)	/* "upstream" = क्रम पढ़ो commands */
#घोषणा DTRAN_MODE_BUS_WIDTH	(BIT(5) | BIT(4))
#घोषणा DTRAN_MODE_ADDR_MODE	BIT(0)	/* 1 = Increment address, 0 = Fixed */

/* DM_CM_DTRAN_CTRL */
#घोषणा DTRAN_CTRL_DM_START	BIT(0)

/* DM_CM_RST */
#घोषणा RST_DTRANRST1		BIT(9)
#घोषणा RST_DTRANRST0		BIT(8)
#घोषणा RST_RESERVED_BITS	GENMASK_ULL(31, 0)

/* DM_CM_INFO1 and DM_CM_INFO1_MASK */
#घोषणा INFO1_CLEAR		0
#घोषणा INFO1_MASK_CLEAR	GENMASK_ULL(31, 0)
#घोषणा INFO1_DTRANEND1		BIT(17)
#घोषणा INFO1_DTRANEND0		BIT(16)

/* DM_CM_INFO2 and DM_CM_INFO2_MASK */
#घोषणा INFO2_MASK_CLEAR	GENMASK_ULL(31, 0)
#घोषणा INFO2_DTRANERR1		BIT(17)
#घोषणा INFO2_DTRANERR0		BIT(16)

क्रमागत renesas_sdhi_dma_cookie अणु
	COOKIE_UNMAPPED,
	COOKIE_PRE_MAPPED,
	COOKIE_MAPPED,
पूर्ण;

/*
 * Specअगरication of this driver:
 * - host->chan_अणुrx,txपूर्ण will be used as a flag of enabling/disabling the dma
 * - Since this SDHI DMAC रेजिस्टर set has 16 but 32-bit width, we
 *   need a custom accessor.
 */

अटल अचिन्हित दीर्घ global_flags;
/*
 * Workaround क्रम aव्योमing to use RX DMAC by multiple channels.
 * On R-Car H3 ES1.* and M3-W ES1.0, when multiple SDHI channels use
 * RX DMAC simultaneously, someबार hundreds of bytes data are not
 * stored पूर्णांकo the प्रणाली memory even अगर the DMAC पूर्णांकerrupt happened.
 * So, this driver then uses one RX DMAC channel only.
 */
#घोषणा SDHI_INTERNAL_DMAC_ONE_RX_ONLY	0
#घोषणा SDHI_INTERNAL_DMAC_RX_IN_USE	1

/* RZ/A2 करोes not have the ADRR_MODE bit */
#घोषणा SDHI_INTERNAL_DMAC_ADDR_MODE_FIXED_ONLY 2

/* Definitions क्रम sampling घड़ीs */
अटल काष्ठा renesas_sdhi_scc rcar_gen3_scc_taps[] = अणु
	अणु
		.clk_rate = 0,
		.tap = 0x00000300,
		.tap_hs400_4tap = 0x00000100,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा renesas_sdhi_of_data of_rza2_compatible = अणु
	.पंचांगio_flags	= TMIO_MMC_HAS_IDLE_WAIT | TMIO_MMC_CLK_ACTUAL |
			  TMIO_MMC_HAVE_CBSY,
	.पंचांगio_ocr_mask	= MMC_VDD_32_33,
	.capabilities	= MMC_CAP_SD_HIGHSPEED | MMC_CAP_SDIO_IRQ |
			  MMC_CAP_CMD23 | MMC_CAP_WAIT_WHILE_BUSY,
	.bus_shअगरt	= 2,
	.scc_offset	= 0 - 0x1000,
	.taps		= rcar_gen3_scc_taps,
	.taps_num	= ARRAY_SIZE(rcar_gen3_scc_taps),
	/* DMAC can handle 32bit blk count but only 1 segment */
	.max_blk_count	= अच_पूर्णांक_उच्च / TMIO_MAX_BLK_SIZE,
	.max_segs	= 1,
पूर्ण;

अटल स्थिर काष्ठा renesas_sdhi_of_data of_rcar_gen3_compatible = अणु
	.पंचांगio_flags	= TMIO_MMC_HAS_IDLE_WAIT | TMIO_MMC_CLK_ACTUAL |
			  TMIO_MMC_HAVE_CBSY | TMIO_MMC_MIN_RCAR2,
	.capabilities	= MMC_CAP_SD_HIGHSPEED | MMC_CAP_SDIO_IRQ |
			  MMC_CAP_CMD23 | MMC_CAP_WAIT_WHILE_BUSY,
	.capabilities2	= MMC_CAP2_NO_WRITE_PROTECT | MMC_CAP2_MERGE_CAPABLE,
	.bus_shअगरt	= 2,
	.scc_offset	= 0x1000,
	.taps		= rcar_gen3_scc_taps,
	.taps_num	= ARRAY_SIZE(rcar_gen3_scc_taps),
	/* DMAC can handle 32bit blk count but only 1 segment */
	.max_blk_count	= अच_पूर्णांक_उच्च / TMIO_MAX_BLK_SIZE,
	.max_segs	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id renesas_sdhi_पूर्णांकernal_dmac_of_match[] = अणु
	अणु .compatible = "renesas,sdhi-r7s9210", .data = &of_rza2_compatible, पूर्ण,
	अणु .compatible = "renesas,sdhi-mmc-r8a77470", .data = &of_rcar_gen3_compatible, पूर्ण,
	अणु .compatible = "renesas,sdhi-r8a7795", .data = &of_rcar_gen3_compatible, पूर्ण,
	अणु .compatible = "renesas,sdhi-r8a7796", .data = &of_rcar_gen3_compatible, पूर्ण,
	अणु .compatible = "renesas,rcar-gen3-sdhi", .data = &of_rcar_gen3_compatible, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, renesas_sdhi_पूर्णांकernal_dmac_of_match);

अटल व्योम
renesas_sdhi_पूर्णांकernal_dmac_dm_ग_लिखो(काष्ठा पंचांगio_mmc_host *host,
				    पूर्णांक addr, u64 val)
अणु
	ग_लिखोq(val, host->ctl + addr);
पूर्ण

अटल व्योम
renesas_sdhi_पूर्णांकernal_dmac_enable_dma(काष्ठा पंचांगio_mmc_host *host, bool enable)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);

	अगर (!host->chan_tx || !host->chan_rx)
		वापस;

	अगर (!enable)
		renesas_sdhi_पूर्णांकernal_dmac_dm_ग_लिखो(host, DM_CM_INFO1,
						    INFO1_CLEAR);

	अगर (priv->dma_priv.enable)
		priv->dma_priv.enable(host, enable);
पूर्ण

अटल व्योम
renesas_sdhi_पूर्णांकernal_dmac_पात_dma(काष्ठा पंचांगio_mmc_host *host) अणु
	u64 val = RST_DTRANRST1 | RST_DTRANRST0;

	renesas_sdhi_पूर्णांकernal_dmac_enable_dma(host, false);

	renesas_sdhi_पूर्णांकernal_dmac_dm_ग_लिखो(host, DM_CM_RST,
					    RST_RESERVED_BITS & ~val);
	renesas_sdhi_पूर्णांकernal_dmac_dm_ग_लिखो(host, DM_CM_RST,
					    RST_RESERVED_BITS | val);

	clear_bit(SDHI_INTERNAL_DMAC_RX_IN_USE, &global_flags);

	renesas_sdhi_पूर्णांकernal_dmac_enable_dma(host, true);
पूर्ण

अटल व्योम
renesas_sdhi_पूर्णांकernal_dmac_dataend_dma(काष्ठा पंचांगio_mmc_host *host) अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);

	tasklet_schedule(&priv->dma_priv.dma_complete);
पूर्ण

/*
 * renesas_sdhi_पूर्णांकernal_dmac_map() will be called with two dअगरference
 * sg poपूर्णांकers in two mmc_data by .pre_req(), but पंचांगio host can have a single
 * sg_ptr only. So, renesas_sdhi_पूर्णांकernal_dmac_अणुunपूर्णmap() should use a sg
 * poपूर्णांकer in a mmc_data instead of host->sg_ptr.
 */
अटल व्योम
renesas_sdhi_पूर्णांकernal_dmac_unmap(काष्ठा पंचांगio_mmc_host *host,
				 काष्ठा mmc_data *data,
				 क्रमागत renesas_sdhi_dma_cookie cookie)
अणु
	bool unmap = cookie == COOKIE_UNMAPPED ? (data->host_cookie != cookie) :
						 (data->host_cookie == cookie);

	अगर (unmap) अणु
		dma_unmap_sg(&host->pdev->dev, data->sg, data->sg_len,
			     mmc_get_dma_dir(data));
		data->host_cookie = COOKIE_UNMAPPED;
	पूर्ण
पूर्ण

अटल bool
renesas_sdhi_पूर्णांकernal_dmac_map(काष्ठा पंचांगio_mmc_host *host,
			       काष्ठा mmc_data *data,
			       क्रमागत renesas_sdhi_dma_cookie cookie)
अणु
	अगर (data->host_cookie == COOKIE_PRE_MAPPED)
		वापस true;

	अगर (!dma_map_sg(&host->pdev->dev, data->sg, data->sg_len,
			    mmc_get_dma_dir(data)))
		वापस false;

	data->host_cookie = cookie;

	/* This DMAC cannot handle अगर buffer is not 128-bytes alignment */
	अगर (!IS_ALIGNED(sg_dma_address(data->sg), 128)) अणु
		renesas_sdhi_पूर्णांकernal_dmac_unmap(host, data, cookie);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम
renesas_sdhi_पूर्णांकernal_dmac_start_dma(काष्ठा पंचांगio_mmc_host *host,
				     काष्ठा mmc_data *data)
अणु
	काष्ठा scatterlist *sg = host->sg_ptr;
	u32 dtran_mode = DTRAN_MODE_BUS_WIDTH;

	अगर (!test_bit(SDHI_INTERNAL_DMAC_ADDR_MODE_FIXED_ONLY, &global_flags))
		dtran_mode |= DTRAN_MODE_ADDR_MODE;

	अगर (!renesas_sdhi_पूर्णांकernal_dmac_map(host, data, COOKIE_MAPPED))
		जाओ क्रमce_pio;

	अगर (data->flags & MMC_DATA_READ) अणु
		dtran_mode |= DTRAN_MODE_CH_NUM_CH1;
		अगर (test_bit(SDHI_INTERNAL_DMAC_ONE_RX_ONLY, &global_flags) &&
		    test_and_set_bit(SDHI_INTERNAL_DMAC_RX_IN_USE, &global_flags))
			जाओ क्रमce_pio_with_unmap;
	पूर्ण अन्यथा अणु
		dtran_mode |= DTRAN_MODE_CH_NUM_CH0;
	पूर्ण

	renesas_sdhi_पूर्णांकernal_dmac_enable_dma(host, true);

	/* set dma parameters */
	renesas_sdhi_पूर्णांकernal_dmac_dm_ग_लिखो(host, DM_CM_DTRAN_MODE,
					    dtran_mode);
	renesas_sdhi_पूर्णांकernal_dmac_dm_ग_लिखो(host, DM_DTRAN_ADDR,
					    sg_dma_address(sg));

	host->dma_on = true;

	वापस;

क्रमce_pio_with_unmap:
	renesas_sdhi_पूर्णांकernal_dmac_unmap(host, data, COOKIE_UNMAPPED);

क्रमce_pio:
	renesas_sdhi_पूर्णांकernal_dmac_enable_dma(host, false);
पूर्ण

अटल व्योम renesas_sdhi_पूर्णांकernal_dmac_issue_tasklet_fn(अचिन्हित दीर्घ arg)
अणु
	काष्ठा पंचांगio_mmc_host *host = (काष्ठा पंचांगio_mmc_host *)arg;

	पंचांगio_mmc_enable_mmc_irqs(host, TMIO_STAT_DATAEND);

	/* start the DMAC */
	renesas_sdhi_पूर्णांकernal_dmac_dm_ग_लिखो(host, DM_CM_DTRAN_CTRL,
					    DTRAN_CTRL_DM_START);
पूर्ण

अटल bool renesas_sdhi_पूर्णांकernal_dmac_complete(काष्ठा पंचांगio_mmc_host *host)
अणु
	क्रमागत dma_data_direction dir;

	अगर (!host->dma_on)
		वापस false;

	अगर (!host->data)
		वापस false;

	अगर (host->data->flags & MMC_DATA_READ)
		dir = DMA_FROM_DEVICE;
	अन्यथा
		dir = DMA_TO_DEVICE;

	renesas_sdhi_पूर्णांकernal_dmac_enable_dma(host, false);
	renesas_sdhi_पूर्णांकernal_dmac_unmap(host, host->data, COOKIE_MAPPED);

	अगर (dir == DMA_FROM_DEVICE)
		clear_bit(SDHI_INTERNAL_DMAC_RX_IN_USE, &global_flags);

	host->dma_on = false;

	वापस true;
पूर्ण

अटल व्योम renesas_sdhi_पूर्णांकernal_dmac_complete_tasklet_fn(अचिन्हित दीर्घ arg)
अणु
	काष्ठा पंचांगio_mmc_host *host = (काष्ठा पंचांगio_mmc_host *)arg;

	spin_lock_irq(&host->lock);
	अगर (!renesas_sdhi_पूर्णांकernal_dmac_complete(host))
		जाओ out;

	पंचांगio_mmc_करो_data_irq(host);
out:
	spin_unlock_irq(&host->lock);
पूर्ण

अटल व्योम renesas_sdhi_पूर्णांकernal_dmac_end_dma(काष्ठा पंचांगio_mmc_host *host)
अणु
	अगर (host->data)
		renesas_sdhi_पूर्णांकernal_dmac_complete(host);
पूर्ण

अटल व्योम renesas_sdhi_पूर्णांकernal_dmac_post_req(काष्ठा mmc_host *mmc,
						काष्ठा mmc_request *mrq,
						पूर्णांक err)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;

	अगर (!data)
		वापस;

	renesas_sdhi_पूर्णांकernal_dmac_unmap(host, data, COOKIE_UNMAPPED);
पूर्ण

अटल व्योम renesas_sdhi_पूर्णांकernal_dmac_pre_req(काष्ठा mmc_host *mmc,
					       काष्ठा mmc_request *mrq)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;

	अगर (!data)
		वापस;

	data->host_cookie = COOKIE_UNMAPPED;
	renesas_sdhi_पूर्णांकernal_dmac_map(host, data, COOKIE_PRE_MAPPED);
पूर्ण

अटल व्योम
renesas_sdhi_पूर्णांकernal_dmac_request_dma(काष्ठा पंचांगio_mmc_host *host,
				       काष्ठा पंचांगio_mmc_data *pdata)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);

	/* Disable DMAC पूर्णांकerrupts, we करोn't use them */
	renesas_sdhi_पूर्णांकernal_dmac_dm_ग_लिखो(host, DM_CM_INFO1_MASK,
					    INFO1_MASK_CLEAR);
	renesas_sdhi_पूर्णांकernal_dmac_dm_ग_लिखो(host, DM_CM_INFO2_MASK,
					    INFO2_MASK_CLEAR);

	/* Each value is set to non-zero to assume "enabling" each DMA */
	host->chan_rx = host->chan_tx = (व्योम *)0xdeadbeaf;

	tasklet_init(&priv->dma_priv.dma_complete,
		     renesas_sdhi_पूर्णांकernal_dmac_complete_tasklet_fn,
		     (अचिन्हित दीर्घ)host);
	tasklet_init(&host->dma_issue,
		     renesas_sdhi_पूर्णांकernal_dmac_issue_tasklet_fn,
		     (अचिन्हित दीर्घ)host);

	/* Add pre_req and post_req */
	host->ops.pre_req = renesas_sdhi_पूर्णांकernal_dmac_pre_req;
	host->ops.post_req = renesas_sdhi_पूर्णांकernal_dmac_post_req;
पूर्ण

अटल व्योम
renesas_sdhi_पूर्णांकernal_dmac_release_dma(काष्ठा पंचांगio_mmc_host *host)
अणु
	/* Each value is set to zero to assume "disabling" each DMA */
	host->chan_rx = host->chan_tx = शून्य;
पूर्ण

अटल स्थिर काष्ठा पंचांगio_mmc_dma_ops renesas_sdhi_पूर्णांकernal_dmac_dma_ops = अणु
	.start = renesas_sdhi_पूर्णांकernal_dmac_start_dma,
	.enable = renesas_sdhi_पूर्णांकernal_dmac_enable_dma,
	.request = renesas_sdhi_पूर्णांकernal_dmac_request_dma,
	.release = renesas_sdhi_पूर्णांकernal_dmac_release_dma,
	.पात = renesas_sdhi_पूर्णांकernal_dmac_पात_dma,
	.dataend = renesas_sdhi_पूर्णांकernal_dmac_dataend_dma,
	.end = renesas_sdhi_पूर्णांकernal_dmac_end_dma,
पूर्ण;

/*
 * Whitelist of specअगरic R-Car Gen3 SoC ES versions to use this DMAC
 * implementation as others may use a dअगरferent implementation.
 */
अटल स्थिर काष्ठा soc_device_attribute soc_dma_quirks[] = अणु
	अणु .soc_id = "r7s9210",
	  .data = (व्योम *)BIT(SDHI_INTERNAL_DMAC_ADDR_MODE_FIXED_ONLY) पूर्ण,
	अणु .soc_id = "r8a7795", .revision = "ES1.*",
	  .data = (व्योम *)BIT(SDHI_INTERNAL_DMAC_ONE_RX_ONLY) पूर्ण,
	अणु .soc_id = "r8a7796", .revision = "ES1.0",
	  .data = (व्योम *)BIT(SDHI_INTERNAL_DMAC_ONE_RX_ONLY) पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक renesas_sdhi_पूर्णांकernal_dmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा soc_device_attribute *soc = soc_device_match(soc_dma_quirks);
	काष्ठा device *dev = &pdev->dev;

	अगर (soc)
		global_flags |= (अचिन्हित दीर्घ)soc->data;

	/* value is max of SD_SECCNT. Confirmed by HW engineers */
	dma_set_max_seg_size(dev, 0xffffffff);

	वापस renesas_sdhi_probe(pdev, &renesas_sdhi_पूर्णांकernal_dmac_dma_ops);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops renesas_sdhi_पूर्णांकernal_dmac_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(पंचांगio_mmc_host_runसमय_suspend,
			   पंचांगio_mmc_host_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver renesas_पूर्णांकernal_dmac_sdhi_driver = अणु
	.driver		= अणु
		.name	= "renesas_sdhi_internal_dmac",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.pm	= &renesas_sdhi_पूर्णांकernal_dmac_dev_pm_ops,
		.of_match_table = renesas_sdhi_पूर्णांकernal_dmac_of_match,
	पूर्ण,
	.probe		= renesas_sdhi_पूर्णांकernal_dmac_probe,
	.हटाओ		= renesas_sdhi_हटाओ,
पूर्ण;

module_platक्रमm_driver(renesas_पूर्णांकernal_dmac_sdhi_driver);

MODULE_DESCRIPTION("Renesas SDHI driver for internal DMAC");
MODULE_AUTHOR("Yoshihiro Shimoda");
MODULE_LICENSE("GPL v2");
