<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2+ DMA driver
 *
 * Copyright (C) 2003 - 2008 Nokia Corporation
 * Author: Juha Yrjथघlथअ <juha.yrjola@nokia.com>
 * DMA channel linking क्रम 1610 by Samuel Ortiz <samuel.ortiz@nokia.com>
 * Graphics DMA and LCD DMA graphics tranक्रमmations
 * by Imre Deak <imre.deak@nokia.com>
 * OMAP2/3 support Copyright (C) 2004-2007 Texas Instruments, Inc.
 * Some functions based on earlier dma-omap.c Copyright (C) 2001 RidgeRun, Inc.
 *
 * Copyright (C) 2009 Texas Instruments
 * Added OMAP4 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - https://www.ti.com/
 * Converted DMA library पूर्णांकo platक्रमm driver
 *	- G, Manjunath Kondaiah <manjugk@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/of.h>
#समावेश <linux/omap-dma.h>

#समावेश "soc.h"

अटल स्थिर काष्ठा omap_dma_reg reg_map[] = अणु
	[REVISION]	= अणु 0x0000, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[GCR]		= अणु 0x0078, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[IRQSTATUS_L0]	= अणु 0x0008, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[IRQSTATUS_L1]	= अणु 0x000c, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[IRQSTATUS_L2]	= अणु 0x0010, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[IRQSTATUS_L3]	= अणु 0x0014, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[IRQENABLE_L0]	= अणु 0x0018, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[IRQENABLE_L1]	= अणु 0x001c, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[IRQENABLE_L2]	= अणु 0x0020, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[IRQENABLE_L3]	= अणु 0x0024, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[SYSSTATUS]	= अणु 0x0028, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[OCP_SYSCONFIG]	= अणु 0x002c, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[CAPS_0]	= अणु 0x0064, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[CAPS_2]	= अणु 0x006c, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[CAPS_3]	= अणु 0x0070, 0x00, OMAP_DMA_REG_32BIT पूर्ण,
	[CAPS_4]	= अणु 0x0074, 0x00, OMAP_DMA_REG_32BIT पूर्ण,

	/* Common रेजिस्टर offsets */
	[CCR]		= अणु 0x0080, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CLNK_CTRL]	= अणु 0x0084, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CICR]		= अणु 0x0088, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CSR]		= अणु 0x008c, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CSDP]		= अणु 0x0090, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CEN]		= अणु 0x0094, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CFN]		= अणु 0x0098, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CSEI]		= अणु 0x00a4, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CSFI]		= अणु 0x00a8, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CDEI]		= अणु 0x00ac, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CDFI]		= अणु 0x00b0, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CSAC]		= अणु 0x00b4, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CDAC]		= अणु 0x00b8, 0x60, OMAP_DMA_REG_32BIT पूर्ण,

	/* Channel specअगरic रेजिस्टर offsets */
	[CSSA]		= अणु 0x009c, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CDSA]		= अणु 0x00a0, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CCEN]		= अणु 0x00bc, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CCFN]		= अणु 0x00c0, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[COLOR]		= अणु 0x00c4, 0x60, OMAP_DMA_REG_32BIT पूर्ण,

	/* OMAP4 specअगरic रेजिस्टरs */
	[CDP]		= अणु 0x00d0, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CNDP]		= अणु 0x00d4, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
	[CCDN]		= अणु 0x00d8, 0x60, OMAP_DMA_REG_32BIT पूर्ण,
पूर्ण;

अटल अचिन्हित configure_dma_errata(व्योम)
अणु
	अचिन्हित errata = 0;

	/*
	 * Errata applicable क्रम OMAP2430ES1.0 and all omap2420
	 *
	 * I.
	 * Erratum ID: Not Available
	 * Inter Frame DMA buffering issue DMA will wrongly
	 * buffer elements अगर packing and bursting is enabled. This might
	 * result in data माला_लो stalled in FIFO at the end of the block.
	 * Workaround: DMA channels must have BUFFERING_DISABLED bit set to
	 * guarantee no data will stay in the DMA FIFO in हाल पूर्णांकer frame
	 * buffering occurs
	 *
	 * II.
	 * Erratum ID: Not Available
	 * DMA may hang when several channels are used in parallel
	 * In the following configuration, DMA channel hanging can occur:
	 * a. Channel i, hardware synchronized, is enabled
	 * b. Another channel (Channel x), software synchronized, is enabled.
	 * c. Channel i is disabled beक्रमe end of transfer
	 * d. Channel i is reenabled.
	 * e. Steps 1 to 4 are repeated a certain number of बार.
	 * f. A third channel (Channel y), software synchronized, is enabled.
	 * Channel x and Channel y may hang immediately after step 'f'.
	 * Workaround:
	 * For any channel used - make sure NextLCH_ID is set to the value j.
	 */
	अगर (cpu_is_omap2420() || (cpu_is_omap2430() &&
				(omap_type() == OMAP2430_REV_ES1_0))) अणु

		SET_DMA_ERRATA(DMA_ERRATA_IFRAME_BUFFERING);
		SET_DMA_ERRATA(DMA_ERRATA_PARALLEL_CHANNELS);
	पूर्ण

	/*
	 * Erratum ID: i378: OMAP2+: sDMA Channel is not disabled
	 * after a transaction error.
	 * Workaround: SW should explicitely disable the channel.
	 */
	अगर (cpu_class_is_omap2())
		SET_DMA_ERRATA(DMA_ERRATA_i378);

	/*
	 * Erratum ID: i541: sDMA FIFO draining करोes not finish
	 * If sDMA channel is disabled on the fly, sDMA enters standby even
	 * through FIFO Drain is still in progress
	 * Workaround: Put sDMA in NoStandby more beक्रमe a logical channel is
	 * disabled, then put it back to SmartStandby right after the channel
	 * finishes FIFO draining.
	 */
	अगर (cpu_is_omap34xx())
		SET_DMA_ERRATA(DMA_ERRATA_i541);

	/*
	 * Erratum ID: i88 : Special programming model needed to disable DMA
	 * beक्रमe end of block.
	 * Workaround: software must ensure that the DMA is configured in No
	 * Standby mode(DMAx_OCP_SYSCONFIG.MIDLEMODE = "01")
	 */
	अगर (omap_type() == OMAP3430_REV_ES1_0)
		SET_DMA_ERRATA(DMA_ERRATA_i88);

	/*
	 * Erratum 3.2/3.3: someबार 0 is वापसed अगर CSAC/CDAC is
	 * पढ़ो beक्रमe the DMA controller finished disabling the channel.
	 */
	SET_DMA_ERRATA(DMA_ERRATA_3_3);

	/*
	 * Erratum ID: Not Available
	 * A bug in ROM code leaves IRQ status क्रम channels 0 and 1 uncleared
	 * after secure sram context save and restore.
	 * Work around: Hence we need to manually clear those IRQs to aव्योम
	 * spurious पूर्णांकerrupts. This affects only secure devices.
	 */
	अगर (cpu_is_omap34xx() && (omap_type() != OMAP2_DEVICE_TYPE_GP))
		SET_DMA_ERRATA(DMA_ROMCODE_BUG);

	वापस errata;
पूर्ण

अटल स्थिर काष्ठा dma_slave_map omap24xx_sdma_dt_map[] = अणु
	/* बाह्यal DMA requests when tusb6010 is used */
	अणु "musb-hdrc.1.auto", "dmareq0", SDMA_FILTER_PARAM(2) पूर्ण,
	अणु "musb-hdrc.1.auto", "dmareq1", SDMA_FILTER_PARAM(3) पूर्ण,
	अणु "musb-hdrc.1.auto", "dmareq2", SDMA_FILTER_PARAM(14) पूर्ण, /* OMAP2420 only */
	अणु "musb-hdrc.1.auto", "dmareq3", SDMA_FILTER_PARAM(15) पूर्ण, /* OMAP2420 only */
	अणु "musb-hdrc.1.auto", "dmareq4", SDMA_FILTER_PARAM(16) पूर्ण, /* OMAP2420 only */
	अणु "musb-hdrc.1.auto", "dmareq5", SDMA_FILTER_PARAM(64) पूर्ण, /* OMAP2420 only */
पूर्ण;

अटल काष्ठा omap_dma_dev_attr dma_attr = अणु
	.dev_caps = RESERVE_CHANNEL | DMA_LINKED_LCH | GLOBAL_PRIORITY |
		    IS_CSSA_32 | IS_CDSA_32,
	.lch_count = 32,
पूर्ण;

काष्ठा omap_प्रणाली_dma_plat_info dma_plat_info = अणु
	.reg_map	= reg_map,
	.channel_stride	= 0x60,
	.dma_attr	= &dma_attr,
पूर्ण;

/* One समय initializations */
अटल पूर्णांक __init omap2_प्रणाली_dma_init(व्योम)
अणु
	dma_plat_info.errata = configure_dma_errata();

	अगर (soc_is_omap24xx()) अणु
		/* DMA slave map क्रम drivers not yet converted to DT */
		dma_plat_info.slave_map = omap24xx_sdma_dt_map;
		dma_plat_info.slavecnt = ARRAY_SIZE(omap24xx_sdma_dt_map);
	पूर्ण

	अगर (!soc_is_omap242x())
		dma_attr.dev_caps |= IS_RW_PRIORITY;

	अगर (soc_is_omap34xx() && (omap_type() != OMAP2_DEVICE_TYPE_GP))
		dma_attr.dev_caps |= HS_CHANNELS_RESERVED;

	वापस 0;
पूर्ण
omap_arch_initcall(omap2_प्रणाली_dma_init);
