<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mmc/host/mmci.c - ARM PrimeCell MMCI PL180/1 driver
 *
 *  Copyright (C) 2003 Deep Blue Solutions, Ltd, All Rights Reserved.
 *  Copyright (C) 2010 ST-Ericsson SA
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/log2.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/pm.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/sd.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/amba/bus.h>
#समावेश <linux/clk.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/amba/mmci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/types.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/पन.स>

#समावेश "mmci.h"

#घोषणा DRIVER_NAME "mmci-pl18x"

अटल व्योम mmci_variant_init(काष्ठा mmci_host *host);
अटल व्योम ux500_variant_init(काष्ठा mmci_host *host);
अटल व्योम ux500v2_variant_init(काष्ठा mmci_host *host);

अटल अचिन्हित पूर्णांक fmax = 515633;

अटल काष्ठा variant_data variant_arm = अणु
	.fअगरosize		= 16 * 4,
	.fअगरohalfsize		= 8 * 4,
	.cmdreg_cpsm_enable	= MCI_CPSM_ENABLE,
	.cmdreg_lrsp_crc	= MCI_CPSM_RESPONSE | MCI_CPSM_LONGRSP,
	.cmdreg_srsp_crc	= MCI_CPSM_RESPONSE,
	.cmdreg_srsp		= MCI_CPSM_RESPONSE,
	.datalength_bits	= 16,
	.datactrl_blocksz	= 11,
	.pwrreg_घातerup		= MCI_PWR_UP,
	.f_max			= 100000000,
	.reversed_irq_handling	= true,
	.mmcimask1		= true,
	.irq_pio_mask		= MCI_IRQ_PIO_MASK,
	.start_err		= MCI_STARTBITERR,
	.खोलोdrain		= MCI_ROD,
	.init			= mmci_variant_init,
पूर्ण;

अटल काष्ठा variant_data variant_arm_extended_fअगरo = अणु
	.fअगरosize		= 128 * 4,
	.fअगरohalfsize		= 64 * 4,
	.cmdreg_cpsm_enable	= MCI_CPSM_ENABLE,
	.cmdreg_lrsp_crc	= MCI_CPSM_RESPONSE | MCI_CPSM_LONGRSP,
	.cmdreg_srsp_crc	= MCI_CPSM_RESPONSE,
	.cmdreg_srsp		= MCI_CPSM_RESPONSE,
	.datalength_bits	= 16,
	.datactrl_blocksz	= 11,
	.pwrreg_घातerup		= MCI_PWR_UP,
	.f_max			= 100000000,
	.mmcimask1		= true,
	.irq_pio_mask		= MCI_IRQ_PIO_MASK,
	.start_err		= MCI_STARTBITERR,
	.खोलोdrain		= MCI_ROD,
	.init			= mmci_variant_init,
पूर्ण;

अटल काष्ठा variant_data variant_arm_extended_fअगरo_hwfc = अणु
	.fअगरosize		= 128 * 4,
	.fअगरohalfsize		= 64 * 4,
	.clkreg_enable		= MCI_ARM_HWFCEN,
	.cmdreg_cpsm_enable	= MCI_CPSM_ENABLE,
	.cmdreg_lrsp_crc	= MCI_CPSM_RESPONSE | MCI_CPSM_LONGRSP,
	.cmdreg_srsp_crc	= MCI_CPSM_RESPONSE,
	.cmdreg_srsp		= MCI_CPSM_RESPONSE,
	.datalength_bits	= 16,
	.datactrl_blocksz	= 11,
	.pwrreg_घातerup		= MCI_PWR_UP,
	.f_max			= 100000000,
	.mmcimask1		= true,
	.irq_pio_mask		= MCI_IRQ_PIO_MASK,
	.start_err		= MCI_STARTBITERR,
	.खोलोdrain		= MCI_ROD,
	.init			= mmci_variant_init,
पूर्ण;

अटल काष्ठा variant_data variant_u300 = अणु
	.fअगरosize		= 16 * 4,
	.fअगरohalfsize		= 8 * 4,
	.clkreg_enable		= MCI_ST_U300_HWFCEN,
	.clkreg_8bit_bus_enable = MCI_ST_8BIT_BUS,
	.cmdreg_cpsm_enable	= MCI_CPSM_ENABLE,
	.cmdreg_lrsp_crc	= MCI_CPSM_RESPONSE | MCI_CPSM_LONGRSP,
	.cmdreg_srsp_crc	= MCI_CPSM_RESPONSE,
	.cmdreg_srsp		= MCI_CPSM_RESPONSE,
	.datalength_bits	= 16,
	.datactrl_blocksz	= 11,
	.datactrl_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.st_sdio			= true,
	.pwrreg_घातerup		= MCI_PWR_ON,
	.f_max			= 100000000,
	.संकेत_direction	= true,
	.pwrreg_clkgate		= true,
	.pwrreg_noघातer		= true,
	.mmcimask1		= true,
	.irq_pio_mask		= MCI_IRQ_PIO_MASK,
	.start_err		= MCI_STARTBITERR,
	.खोलोdrain		= MCI_OD,
	.init			= mmci_variant_init,
पूर्ण;

अटल काष्ठा variant_data variant_nomadik = अणु
	.fअगरosize		= 16 * 4,
	.fअगरohalfsize		= 8 * 4,
	.clkreg			= MCI_CLK_ENABLE,
	.clkreg_8bit_bus_enable = MCI_ST_8BIT_BUS,
	.cmdreg_cpsm_enable	= MCI_CPSM_ENABLE,
	.cmdreg_lrsp_crc	= MCI_CPSM_RESPONSE | MCI_CPSM_LONGRSP,
	.cmdreg_srsp_crc	= MCI_CPSM_RESPONSE,
	.cmdreg_srsp		= MCI_CPSM_RESPONSE,
	.datalength_bits	= 24,
	.datactrl_blocksz	= 11,
	.datactrl_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.st_sdio		= true,
	.st_clkभाग		= true,
	.pwrreg_घातerup		= MCI_PWR_ON,
	.f_max			= 100000000,
	.संकेत_direction	= true,
	.pwrreg_clkgate		= true,
	.pwrreg_noघातer		= true,
	.mmcimask1		= true,
	.irq_pio_mask		= MCI_IRQ_PIO_MASK,
	.start_err		= MCI_STARTBITERR,
	.खोलोdrain		= MCI_OD,
	.init			= mmci_variant_init,
पूर्ण;

अटल काष्ठा variant_data variant_ux500 = अणु
	.fअगरosize		= 30 * 4,
	.fअगरohalfsize		= 8 * 4,
	.clkreg			= MCI_CLK_ENABLE,
	.clkreg_enable		= MCI_ST_UX500_HWFCEN,
	.clkreg_8bit_bus_enable = MCI_ST_8BIT_BUS,
	.clkreg_neg_edge_enable	= MCI_ST_UX500_NEG_EDGE,
	.cmdreg_cpsm_enable	= MCI_CPSM_ENABLE,
	.cmdreg_lrsp_crc	= MCI_CPSM_RESPONSE | MCI_CPSM_LONGRSP,
	.cmdreg_srsp_crc	= MCI_CPSM_RESPONSE,
	.cmdreg_srsp		= MCI_CPSM_RESPONSE,
	.datalength_bits	= 24,
	.datactrl_blocksz	= 11,
	.datactrl_any_blocksz	= true,
	.dma_घातer_of_2		= true,
	.datactrl_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.st_sdio		= true,
	.st_clkभाग		= true,
	.pwrreg_घातerup		= MCI_PWR_ON,
	.f_max			= 100000000,
	.संकेत_direction	= true,
	.pwrreg_clkgate		= true,
	.busy_detect		= true,
	.busy_dpsm_flag		= MCI_DPSM_ST_BUSYMODE,
	.busy_detect_flag	= MCI_ST_CARDBUSY,
	.busy_detect_mask	= MCI_ST_BUSYENDMASK,
	.pwrreg_noघातer		= true,
	.mmcimask1		= true,
	.irq_pio_mask		= MCI_IRQ_PIO_MASK,
	.start_err		= MCI_STARTBITERR,
	.खोलोdrain		= MCI_OD,
	.init			= ux500_variant_init,
पूर्ण;

अटल काष्ठा variant_data variant_ux500v2 = अणु
	.fअगरosize		= 30 * 4,
	.fअगरohalfsize		= 8 * 4,
	.clkreg			= MCI_CLK_ENABLE,
	.clkreg_enable		= MCI_ST_UX500_HWFCEN,
	.clkreg_8bit_bus_enable = MCI_ST_8BIT_BUS,
	.clkreg_neg_edge_enable	= MCI_ST_UX500_NEG_EDGE,
	.cmdreg_cpsm_enable	= MCI_CPSM_ENABLE,
	.cmdreg_lrsp_crc	= MCI_CPSM_RESPONSE | MCI_CPSM_LONGRSP,
	.cmdreg_srsp_crc	= MCI_CPSM_RESPONSE,
	.cmdreg_srsp		= MCI_CPSM_RESPONSE,
	.datactrl_mask_ddrmode	= MCI_DPSM_ST_DDRMODE,
	.datalength_bits	= 24,
	.datactrl_blocksz	= 11,
	.datactrl_any_blocksz	= true,
	.dma_घातer_of_2		= true,
	.datactrl_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.st_sdio		= true,
	.st_clkभाग		= true,
	.pwrreg_घातerup		= MCI_PWR_ON,
	.f_max			= 100000000,
	.संकेत_direction	= true,
	.pwrreg_clkgate		= true,
	.busy_detect		= true,
	.busy_dpsm_flag		= MCI_DPSM_ST_BUSYMODE,
	.busy_detect_flag	= MCI_ST_CARDBUSY,
	.busy_detect_mask	= MCI_ST_BUSYENDMASK,
	.pwrreg_noघातer		= true,
	.mmcimask1		= true,
	.irq_pio_mask		= MCI_IRQ_PIO_MASK,
	.start_err		= MCI_STARTBITERR,
	.खोलोdrain		= MCI_OD,
	.init			= ux500v2_variant_init,
पूर्ण;

अटल काष्ठा variant_data variant_sपंचांग32 = अणु
	.fअगरosize		= 32 * 4,
	.fअगरohalfsize		= 8 * 4,
	.clkreg			= MCI_CLK_ENABLE,
	.clkreg_enable		= MCI_ST_UX500_HWFCEN,
	.clkreg_8bit_bus_enable = MCI_ST_8BIT_BUS,
	.clkreg_neg_edge_enable	= MCI_ST_UX500_NEG_EDGE,
	.cmdreg_cpsm_enable	= MCI_CPSM_ENABLE,
	.cmdreg_lrsp_crc	= MCI_CPSM_RESPONSE | MCI_CPSM_LONGRSP,
	.cmdreg_srsp_crc	= MCI_CPSM_RESPONSE,
	.cmdreg_srsp		= MCI_CPSM_RESPONSE,
	.irq_pio_mask		= MCI_IRQ_PIO_MASK,
	.datalength_bits	= 24,
	.datactrl_blocksz	= 11,
	.datactrl_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.st_sdio		= true,
	.st_clkभाग		= true,
	.pwrreg_घातerup		= MCI_PWR_ON,
	.f_max			= 48000000,
	.pwrreg_clkgate		= true,
	.pwrreg_noघातer		= true,
	.init			= mmci_variant_init,
पूर्ण;

अटल काष्ठा variant_data variant_sपंचांग32_sdmmc = अणु
	.fअगरosize		= 16 * 4,
	.fअगरohalfsize		= 8 * 4,
	.f_max			= 208000000,
	.sपंचांग32_clkभाग		= true,
	.cmdreg_cpsm_enable	= MCI_CPSM_STM32_ENABLE,
	.cmdreg_lrsp_crc	= MCI_CPSM_STM32_LRSP_CRC,
	.cmdreg_srsp_crc	= MCI_CPSM_STM32_SRSP_CRC,
	.cmdreg_srsp		= MCI_CPSM_STM32_SRSP,
	.cmdreg_stop		= MCI_CPSM_STM32_CMDSTOP,
	.data_cmd_enable	= MCI_CPSM_STM32_CMDTRANS,
	.irq_pio_mask		= MCI_IRQ_PIO_STM32_MASK,
	.datactrl_first		= true,
	.datacnt_useless	= true,
	.datalength_bits	= 25,
	.datactrl_blocksz	= 14,
	.datactrl_any_blocksz	= true,
	.datactrl_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.sपंचांग32_idmअसलize_mask	= GENMASK(12, 5),
	.busy_समयout		= true,
	.busy_detect		= true,
	.busy_detect_flag	= MCI_STM32_BUSYD0,
	.busy_detect_mask	= MCI_STM32_BUSYD0ENDMASK,
	.init			= sdmmc_variant_init,
पूर्ण;

अटल काष्ठा variant_data variant_sपंचांग32_sdmmcv2 = अणु
	.fअगरosize		= 16 * 4,
	.fअगरohalfsize		= 8 * 4,
	.f_max			= 208000000,
	.sपंचांग32_clkभाग		= true,
	.cmdreg_cpsm_enable	= MCI_CPSM_STM32_ENABLE,
	.cmdreg_lrsp_crc	= MCI_CPSM_STM32_LRSP_CRC,
	.cmdreg_srsp_crc	= MCI_CPSM_STM32_SRSP_CRC,
	.cmdreg_srsp		= MCI_CPSM_STM32_SRSP,
	.cmdreg_stop		= MCI_CPSM_STM32_CMDSTOP,
	.data_cmd_enable	= MCI_CPSM_STM32_CMDTRANS,
	.irq_pio_mask		= MCI_IRQ_PIO_STM32_MASK,
	.datactrl_first		= true,
	.datacnt_useless	= true,
	.datalength_bits	= 25,
	.datactrl_blocksz	= 14,
	.datactrl_any_blocksz	= true,
	.datactrl_mask_sdio	= MCI_DPSM_ST_SDIOEN,
	.sपंचांग32_idmअसलize_mask	= GENMASK(16, 5),
	.dma_lli		= true,
	.busy_समयout		= true,
	.busy_detect		= true,
	.busy_detect_flag	= MCI_STM32_BUSYD0,
	.busy_detect_mask	= MCI_STM32_BUSYD0ENDMASK,
	.init			= sdmmc_variant_init,
पूर्ण;

अटल काष्ठा variant_data variant_qcom = अणु
	.fअगरosize		= 16 * 4,
	.fअगरohalfsize		= 8 * 4,
	.clkreg			= MCI_CLK_ENABLE,
	.clkreg_enable		= MCI_QCOM_CLK_FLOWENA |
				  MCI_QCOM_CLK_SELECT_IN_FBCLK,
	.clkreg_8bit_bus_enable = MCI_QCOM_CLK_WIDEBUS_8,
	.datactrl_mask_ddrmode	= MCI_QCOM_CLK_SELECT_IN_DDR_MODE,
	.cmdreg_cpsm_enable	= MCI_CPSM_ENABLE,
	.cmdreg_lrsp_crc	= MCI_CPSM_RESPONSE | MCI_CPSM_LONGRSP,
	.cmdreg_srsp_crc	= MCI_CPSM_RESPONSE,
	.cmdreg_srsp		= MCI_CPSM_RESPONSE,
	.data_cmd_enable	= MCI_CPSM_QCOM_DATCMD,
	.datalength_bits	= 24,
	.datactrl_blocksz	= 11,
	.datactrl_any_blocksz	= true,
	.pwrreg_घातerup		= MCI_PWR_UP,
	.f_max			= 208000000,
	.explicit_mclk_control	= true,
	.qcom_fअगरo		= true,
	.qcom_dml		= true,
	.mmcimask1		= true,
	.irq_pio_mask		= MCI_IRQ_PIO_MASK,
	.start_err		= MCI_STARTBITERR,
	.खोलोdrain		= MCI_ROD,
	.init			= qcom_variant_init,
पूर्ण;

/* Busy detection क्रम the ST Micro variant */
अटल पूर्णांक mmci_card_busy(काष्ठा mmc_host *mmc)
अणु
	काष्ठा mmci_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;
	पूर्णांक busy = 0;

	spin_lock_irqsave(&host->lock, flags);
	अगर (पढ़ोl(host->base + MMCISTATUS) & host->variant->busy_detect_flag)
		busy = 1;
	spin_unlock_irqrestore(&host->lock, flags);

	वापस busy;
पूर्ण

अटल व्योम mmci_reg_delay(काष्ठा mmci_host *host)
अणु
	/*
	 * According to the spec, at least three feedback घड़ी cycles
	 * of max 52 MHz must pass between two ग_लिखोs to the MMCICLOCK reg.
	 * Three MCLK घड़ी cycles must pass between two MMCIPOWER reg ग_लिखोs.
	 * Worst delay समय during card init is at 100 kHz => 30 us.
	 * Worst delay समय when up and running is at 25 MHz => 120 ns.
	 */
	अगर (host->cclk < 25000000)
		udelay(30);
	अन्यथा
		ndelay(120);
पूर्ण

/*
 * This must be called with host->lock held
 */
व्योम mmci_ग_लिखो_clkreg(काष्ठा mmci_host *host, u32 clk)
अणु
	अगर (host->clk_reg != clk) अणु
		host->clk_reg = clk;
		ग_लिखोl(clk, host->base + MMCICLOCK);
	पूर्ण
पूर्ण

/*
 * This must be called with host->lock held
 */
व्योम mmci_ग_लिखो_pwrreg(काष्ठा mmci_host *host, u32 pwr)
अणु
	अगर (host->pwr_reg != pwr) अणु
		host->pwr_reg = pwr;
		ग_लिखोl(pwr, host->base + MMCIPOWER);
	पूर्ण
पूर्ण

/*
 * This must be called with host->lock held
 */
अटल व्योम mmci_ग_लिखो_datactrlreg(काष्ठा mmci_host *host, u32 datactrl)
अणु
	/* Keep busy mode in DPSM अगर enabled */
	datactrl |= host->datactrl_reg & host->variant->busy_dpsm_flag;

	अगर (host->datactrl_reg != datactrl) अणु
		host->datactrl_reg = datactrl;
		ग_लिखोl(datactrl, host->base + MMCIDATACTRL);
	पूर्ण
पूर्ण

/*
 * This must be called with host->lock held
 */
अटल व्योम mmci_set_clkreg(काष्ठा mmci_host *host, अचिन्हित पूर्णांक desired)
अणु
	काष्ठा variant_data *variant = host->variant;
	u32 clk = variant->clkreg;

	/* Make sure cclk reflects the current calculated घड़ी */
	host->cclk = 0;

	अगर (desired) अणु
		अगर (variant->explicit_mclk_control) अणु
			host->cclk = host->mclk;
		पूर्ण अन्यथा अगर (desired >= host->mclk) अणु
			clk = MCI_CLK_BYPASS;
			अगर (variant->st_clkभाग)
				clk |= MCI_ST_UX500_NEG_EDGE;
			host->cclk = host->mclk;
		पूर्ण अन्यथा अगर (variant->st_clkभाग) अणु
			/*
			 * DB8500 TRM says f = mclk / (clkभाग + 2)
			 * => clkभाग = (mclk / f) - 2
			 * Round the भागider up so we करोn't exceed the max
			 * frequency
			 */
			clk = DIV_ROUND_UP(host->mclk, desired) - 2;
			अगर (clk >= 256)
				clk = 255;
			host->cclk = host->mclk / (clk + 2);
		पूर्ण अन्यथा अणु
			/*
			 * PL180 TRM says f = mclk / (2 * (clkभाग + 1))
			 * => clkभाग = mclk / (2 * f) - 1
			 */
			clk = host->mclk / (2 * desired) - 1;
			अगर (clk >= 256)
				clk = 255;
			host->cclk = host->mclk / (2 * (clk + 1));
		पूर्ण

		clk |= variant->clkreg_enable;
		clk |= MCI_CLK_ENABLE;
		/* This hasn't proven to be worthजबतक */
		/* clk |= MCI_CLK_PWRSAVE; */
	पूर्ण

	/* Set actual घड़ी क्रम debug */
	host->mmc->actual_घड़ी = host->cclk;

	अगर (host->mmc->ios.bus_width == MMC_BUS_WIDTH_4)
		clk |= MCI_4BIT_BUS;
	अगर (host->mmc->ios.bus_width == MMC_BUS_WIDTH_8)
		clk |= variant->clkreg_8bit_bus_enable;

	अगर (host->mmc->ios.timing == MMC_TIMING_UHS_DDR50 ||
	    host->mmc->ios.timing == MMC_TIMING_MMC_DDR52)
		clk |= variant->clkreg_neg_edge_enable;

	mmci_ग_लिखो_clkreg(host, clk);
पूर्ण

अटल व्योम mmci_dma_release(काष्ठा mmci_host *host)
अणु
	अगर (host->ops && host->ops->dma_release)
		host->ops->dma_release(host);

	host->use_dma = false;
पूर्ण

अटल व्योम mmci_dma_setup(काष्ठा mmci_host *host)
अणु
	अगर (!host->ops || !host->ops->dma_setup)
		वापस;

	अगर (host->ops->dma_setup(host))
		वापस;

	/* initialize pre request cookie */
	host->next_cookie = 1;

	host->use_dma = true;
पूर्ण

/*
 * Validate mmc prerequisites
 */
अटल पूर्णांक mmci_validate_data(काष्ठा mmci_host *host,
			      काष्ठा mmc_data *data)
अणु
	काष्ठा variant_data *variant = host->variant;

	अगर (!data)
		वापस 0;
	अगर (!is_घातer_of_2(data->blksz) && !variant->datactrl_any_blocksz) अणु
		dev_err(mmc_dev(host->mmc),
			"unsupported block size (%d bytes)\n", data->blksz);
		वापस -EINVAL;
	पूर्ण

	अगर (host->ops && host->ops->validate_data)
		वापस host->ops->validate_data(host, data);

	वापस 0;
पूर्ण

अटल पूर्णांक mmci_prep_data(काष्ठा mmci_host *host, काष्ठा mmc_data *data, bool next)
अणु
	पूर्णांक err;

	अगर (!host->ops || !host->ops->prep_data)
		वापस 0;

	err = host->ops->prep_data(host, data, next);

	अगर (next && !err)
		data->host_cookie = ++host->next_cookie < 0 ?
			1 : host->next_cookie;

	वापस err;
पूर्ण

अटल व्योम mmci_unprep_data(काष्ठा mmci_host *host, काष्ठा mmc_data *data,
		      पूर्णांक err)
अणु
	अगर (host->ops && host->ops->unprep_data)
		host->ops->unprep_data(host, data, err);

	data->host_cookie = 0;
पूर्ण

अटल व्योम mmci_get_next_data(काष्ठा mmci_host *host, काष्ठा mmc_data *data)
अणु
	WARN_ON(data->host_cookie && data->host_cookie != host->next_cookie);

	अगर (host->ops && host->ops->get_next_data)
		host->ops->get_next_data(host, data);
पूर्ण

अटल पूर्णांक mmci_dma_start(काष्ठा mmci_host *host, अचिन्हित पूर्णांक datactrl)
अणु
	काष्ठा mmc_data *data = host->data;
	पूर्णांक ret;

	अगर (!host->use_dma)
		वापस -EINVAL;

	ret = mmci_prep_data(host, data, false);
	अगर (ret)
		वापस ret;

	अगर (!host->ops || !host->ops->dma_start)
		वापस -EINVAL;

	/* Okay, go क्रम it. */
	dev_vdbg(mmc_dev(host->mmc),
		 "Submit MMCI DMA job, sglen %d blksz %04x blks %04x flags %08x\n",
		 data->sg_len, data->blksz, data->blocks, data->flags);

	ret = host->ops->dma_start(host, &datactrl);
	अगर (ret)
		वापस ret;

	/* Trigger the DMA transfer */
	mmci_ग_लिखो_datactrlreg(host, datactrl);

	/*
	 * Let the MMCI say when the data is ended and it's समय
	 * to fire next DMA request. When that happens, MMCI will
	 * call mmci_data_end()
	 */
	ग_लिखोl(पढ़ोl(host->base + MMCIMASK0) | MCI_DATAENDMASK,
	       host->base + MMCIMASK0);
	वापस 0;
पूर्ण

अटल व्योम mmci_dma_finalize(काष्ठा mmci_host *host, काष्ठा mmc_data *data)
अणु
	अगर (!host->use_dma)
		वापस;

	अगर (host->ops && host->ops->dma_finalize)
		host->ops->dma_finalize(host, data);
पूर्ण

अटल व्योम mmci_dma_error(काष्ठा mmci_host *host)
अणु
	अगर (!host->use_dma)
		वापस;

	अगर (host->ops && host->ops->dma_error)
		host->ops->dma_error(host);
पूर्ण

अटल व्योम
mmci_request_end(काष्ठा mmci_host *host, काष्ठा mmc_request *mrq)
अणु
	ग_लिखोl(0, host->base + MMCICOMMAND);

	BUG_ON(host->data);

	host->mrq = शून्य;
	host->cmd = शून्य;

	mmc_request_करोne(host->mmc, mrq);
पूर्ण

अटल व्योम mmci_set_mask1(काष्ठा mmci_host *host, अचिन्हित पूर्णांक mask)
अणु
	व्योम __iomem *base = host->base;
	काष्ठा variant_data *variant = host->variant;

	अगर (host->singleirq) अणु
		अचिन्हित पूर्णांक mask0 = पढ़ोl(base + MMCIMASK0);

		mask0 &= ~variant->irq_pio_mask;
		mask0 |= mask;

		ग_लिखोl(mask0, base + MMCIMASK0);
	पूर्ण

	अगर (variant->mmcimask1)
		ग_लिखोl(mask, base + MMCIMASK1);

	host->mask1_reg = mask;
पूर्ण

अटल व्योम mmci_stop_data(काष्ठा mmci_host *host)
अणु
	mmci_ग_लिखो_datactrlreg(host, 0);
	mmci_set_mask1(host, 0);
	host->data = शून्य;
पूर्ण

अटल व्योम mmci_init_sg(काष्ठा mmci_host *host, काष्ठा mmc_data *data)
अणु
	अचिन्हित पूर्णांक flags = SG_MITER_ATOMIC;

	अगर (data->flags & MMC_DATA_READ)
		flags |= SG_MITER_TO_SG;
	अन्यथा
		flags |= SG_MITER_FROM_SG;

	sg_miter_start(&host->sg_miter, data->sg, data->sg_len, flags);
पूर्ण

अटल u32 mmci_get_dctrl_cfg(काष्ठा mmci_host *host)
अणु
	वापस MCI_DPSM_ENABLE | mmci_dctrl_blksz(host);
पूर्ण

अटल u32 ux500v2_get_dctrl_cfg(काष्ठा mmci_host *host)
अणु
	वापस MCI_DPSM_ENABLE | (host->data->blksz << 16);
पूर्ण

अटल bool ux500_busy_complete(काष्ठा mmci_host *host, u32 status, u32 err_msk)
अणु
	व्योम __iomem *base = host->base;

	/*
	 * Beक्रमe unmasking क्रम the busy end IRQ, confirm that the
	 * command was sent successfully. To keep track of having a
	 * command in-progress, रुकोing क्रम busy संकेतing to end,
	 * store the status in host->busy_status.
	 *
	 * Note that, the card may need a couple of घड़ी cycles beक्रमe
	 * it starts संकेतing busy on DAT0, hence re-पढ़ो the
	 * MMCISTATUS रेजिस्टर here, to allow the busy bit to be set.
	 * Potentially we may even need to poll the रेजिस्टर क्रम a
	 * जबतक, to allow it to be set, but tests indicates that it
	 * isn't needed.
	 */
	अगर (!host->busy_status && !(status & err_msk) &&
	    (पढ़ोl(base + MMCISTATUS) & host->variant->busy_detect_flag)) अणु
		ग_लिखोl(पढ़ोl(base + MMCIMASK0) |
		       host->variant->busy_detect_mask,
		       base + MMCIMASK0);

		host->busy_status = status & (MCI_CMDSENT | MCI_CMDRESPEND);
		वापस false;
	पूर्ण

	/*
	 * If there is a command in-progress that has been successfully
	 * sent, then bail out अगर busy status is set and रुको क्रम the
	 * busy end IRQ.
	 *
	 * Note that, the HW triggers an IRQ on both edges जबतक
	 * monitoring DAT0 क्रम busy completion, but there is only one
	 * status bit in MMCISTATUS क्रम the busy state. Thereक्रमe
	 * both the start and the end पूर्णांकerrupts needs to be cleared,
	 * one after the other. So, clear the busy start IRQ here.
	 */
	अगर (host->busy_status &&
	    (status & host->variant->busy_detect_flag)) अणु
		ग_लिखोl(host->variant->busy_detect_mask, base + MMCICLEAR);
		वापस false;
	पूर्ण

	/*
	 * If there is a command in-progress that has been successfully
	 * sent and the busy bit isn't set, it means we have received
	 * the busy end IRQ. Clear and mask the IRQ, then जारी to
	 * process the command.
	 */
	अगर (host->busy_status) अणु
		ग_लिखोl(host->variant->busy_detect_mask, base + MMCICLEAR);

		ग_लिखोl(पढ़ोl(base + MMCIMASK0) &
		       ~host->variant->busy_detect_mask, base + MMCIMASK0);
		host->busy_status = 0;
	पूर्ण

	वापस true;
पूर्ण

/*
 * All the DMA operation mode stuff goes inside this अगरdef.
 * This assumes that you have a generic DMA device पूर्णांकerface,
 * no custom DMA पूर्णांकerfaces are supported.
 */
#अगर_घोषित CONFIG_DMA_ENGINE
काष्ठा mmci_dmae_next अणु
	काष्ठा dma_async_tx_descriptor *desc;
	काष्ठा dma_chan	*chan;
पूर्ण;

काष्ठा mmci_dmae_priv अणु
	काष्ठा dma_chan	*cur;
	काष्ठा dma_chan	*rx_channel;
	काष्ठा dma_chan	*tx_channel;
	काष्ठा dma_async_tx_descriptor	*desc_current;
	काष्ठा mmci_dmae_next next_data;
पूर्ण;

पूर्णांक mmci_dmae_setup(काष्ठा mmci_host *host)
अणु
	स्थिर अक्षर *rxname, *txname;
	काष्ठा mmci_dmae_priv *dmae;

	dmae = devm_kzalloc(mmc_dev(host->mmc), माप(*dmae), GFP_KERNEL);
	अगर (!dmae)
		वापस -ENOMEM;

	host->dma_priv = dmae;

	dmae->rx_channel = dma_request_chan(mmc_dev(host->mmc), "rx");
	अगर (IS_ERR(dmae->rx_channel)) अणु
		पूर्णांक ret = PTR_ERR(dmae->rx_channel);
		dmae->rx_channel = शून्य;
		वापस ret;
	पूर्ण

	dmae->tx_channel = dma_request_chan(mmc_dev(host->mmc), "tx");
	अगर (IS_ERR(dmae->tx_channel)) अणु
		अगर (PTR_ERR(dmae->tx_channel) == -EPROBE_DEFER)
			dev_warn(mmc_dev(host->mmc),
				 "Deferred probe for TX channel ignored\n");
		dmae->tx_channel = शून्य;
	पूर्ण

	/*
	 * If only an RX channel is specअगरied, the driver will
	 * attempt to use it bidirectionally, however अगर it is
	 * is specअगरied but cannot be located, DMA will be disabled.
	 */
	अगर (dmae->rx_channel && !dmae->tx_channel)
		dmae->tx_channel = dmae->rx_channel;

	अगर (dmae->rx_channel)
		rxname = dma_chan_name(dmae->rx_channel);
	अन्यथा
		rxname = "none";

	अगर (dmae->tx_channel)
		txname = dma_chan_name(dmae->tx_channel);
	अन्यथा
		txname = "none";

	dev_info(mmc_dev(host->mmc), "DMA channels RX %s, TX %s\n",
		 rxname, txname);

	/*
	 * Limit the maximum segment size in any SG entry according to
	 * the parameters of the DMA engine device.
	 */
	अगर (dmae->tx_channel) अणु
		काष्ठा device *dev = dmae->tx_channel->device->dev;
		अचिन्हित पूर्णांक max_seg_size = dma_get_max_seg_size(dev);

		अगर (max_seg_size < host->mmc->max_seg_size)
			host->mmc->max_seg_size = max_seg_size;
	पूर्ण
	अगर (dmae->rx_channel) अणु
		काष्ठा device *dev = dmae->rx_channel->device->dev;
		अचिन्हित पूर्णांक max_seg_size = dma_get_max_seg_size(dev);

		अगर (max_seg_size < host->mmc->max_seg_size)
			host->mmc->max_seg_size = max_seg_size;
	पूर्ण

	अगर (!dmae->tx_channel || !dmae->rx_channel) अणु
		mmci_dmae_release(host);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This is used in or so अंतरभूत it
 * so it can be discarded.
 */
व्योम mmci_dmae_release(काष्ठा mmci_host *host)
अणु
	काष्ठा mmci_dmae_priv *dmae = host->dma_priv;

	अगर (dmae->rx_channel)
		dma_release_channel(dmae->rx_channel);
	अगर (dmae->tx_channel)
		dma_release_channel(dmae->tx_channel);
	dmae->rx_channel = dmae->tx_channel = शून्य;
पूर्ण

अटल व्योम mmci_dma_unmap(काष्ठा mmci_host *host, काष्ठा mmc_data *data)
अणु
	काष्ठा mmci_dmae_priv *dmae = host->dma_priv;
	काष्ठा dma_chan *chan;

	अगर (data->flags & MMC_DATA_READ)
		chan = dmae->rx_channel;
	अन्यथा
		chan = dmae->tx_channel;

	dma_unmap_sg(chan->device->dev, data->sg, data->sg_len,
		     mmc_get_dma_dir(data));
पूर्ण

व्योम mmci_dmae_error(काष्ठा mmci_host *host)
अणु
	काष्ठा mmci_dmae_priv *dmae = host->dma_priv;

	अगर (!dma_inprogress(host))
		वापस;

	dev_err(mmc_dev(host->mmc), "error during DMA transfer!\n");
	dmaengine_terminate_all(dmae->cur);
	host->dma_in_progress = false;
	dmae->cur = शून्य;
	dmae->desc_current = शून्य;
	host->data->host_cookie = 0;

	mmci_dma_unmap(host, host->data);
पूर्ण

व्योम mmci_dmae_finalize(काष्ठा mmci_host *host, काष्ठा mmc_data *data)
अणु
	काष्ठा mmci_dmae_priv *dmae = host->dma_priv;
	u32 status;
	पूर्णांक i;

	अगर (!dma_inprogress(host))
		वापस;

	/* Wait up to 1ms क्रम the DMA to complete */
	क्रम (i = 0; ; i++) अणु
		status = पढ़ोl(host->base + MMCISTATUS);
		अगर (!(status & MCI_RXDATAAVLBLMASK) || i >= 100)
			अवरोध;
		udelay(10);
	पूर्ण

	/*
	 * Check to see whether we still have some data left in the FIFO -
	 * this catches DMA controllers which are unable to monitor the
	 * DMALBREQ and DMALSREQ संकेतs जबतक allowing us to DMA to non-
	 * contiguous buffers.  On TX, we'll get a FIFO underrun error.
	 */
	अगर (status & MCI_RXDATAAVLBLMASK) अणु
		mmci_dma_error(host);
		अगर (!data->error)
			data->error = -EIO;
	पूर्ण अन्यथा अगर (!data->host_cookie) अणु
		mmci_dma_unmap(host, data);
	पूर्ण

	/*
	 * Use of DMA with scatter-gather is impossible.
	 * Give up with DMA and चयन back to PIO mode.
	 */
	अगर (status & MCI_RXDATAAVLBLMASK) अणु
		dev_err(mmc_dev(host->mmc), "buggy DMA detected. Taking evasive action.\n");
		mmci_dma_release(host);
	पूर्ण

	host->dma_in_progress = false;
	dmae->cur = शून्य;
	dmae->desc_current = शून्य;
पूर्ण

/* prepares DMA channel and DMA descriptor, वापसs non-zero on failure */
अटल पूर्णांक _mmci_dmae_prep_data(काष्ठा mmci_host *host, काष्ठा mmc_data *data,
				काष्ठा dma_chan **dma_chan,
				काष्ठा dma_async_tx_descriptor **dma_desc)
अणु
	काष्ठा mmci_dmae_priv *dmae = host->dma_priv;
	काष्ठा variant_data *variant = host->variant;
	काष्ठा dma_slave_config conf = अणु
		.src_addr = host->phybase + MMCIFIFO,
		.dst_addr = host->phybase + MMCIFIFO,
		.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
		.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES,
		.src_maxburst = variant->fअगरohalfsize >> 2, /* # of words */
		.dst_maxburst = variant->fअगरohalfsize >> 2, /* # of words */
		.device_fc = false,
	पूर्ण;
	काष्ठा dma_chan *chan;
	काष्ठा dma_device *device;
	काष्ठा dma_async_tx_descriptor *desc;
	पूर्णांक nr_sg;
	अचिन्हित दीर्घ flags = DMA_CTRL_ACK;

	अगर (data->flags & MMC_DATA_READ) अणु
		conf.direction = DMA_DEV_TO_MEM;
		chan = dmae->rx_channel;
	पूर्ण अन्यथा अणु
		conf.direction = DMA_MEM_TO_DEV;
		chan = dmae->tx_channel;
	पूर्ण

	/* If there's no DMA channel, fall back to PIO */
	अगर (!chan)
		वापस -EINVAL;

	/* If less than or equal to the fअगरo size, करोn't bother with DMA */
	अगर (data->blksz * data->blocks <= variant->fअगरosize)
		वापस -EINVAL;

	/*
	 * This is necessary to get SDIO working on the Ux500. We करो not yet
	 * know अगर this is a bug in:
	 * - The Ux500 DMA controller (DMA40)
	 * - The MMCI DMA पूर्णांकerface on the Ux500
	 * some घातer of two blocks (such as 64 bytes) are sent regularly
	 * during SDIO traffic and those work fine so क्रम these we enable DMA
	 * transfers.
	 */
	अगर (host->variant->dma_घातer_of_2 && !is_घातer_of_2(data->blksz))
		वापस -EINVAL;

	device = chan->device;
	nr_sg = dma_map_sg(device->dev, data->sg, data->sg_len,
			   mmc_get_dma_dir(data));
	अगर (nr_sg == 0)
		वापस -EINVAL;

	अगर (host->variant->qcom_dml)
		flags |= DMA_PREP_INTERRUPT;

	dmaengine_slave_config(chan, &conf);
	desc = dmaengine_prep_slave_sg(chan, data->sg, nr_sg,
					    conf.direction, flags);
	अगर (!desc)
		जाओ unmap_निकास;

	*dma_chan = chan;
	*dma_desc = desc;

	वापस 0;

 unmap_निकास:
	dma_unmap_sg(device->dev, data->sg, data->sg_len,
		     mmc_get_dma_dir(data));
	वापस -ENOMEM;
पूर्ण

पूर्णांक mmci_dmae_prep_data(काष्ठा mmci_host *host,
			काष्ठा mmc_data *data,
			bool next)
अणु
	काष्ठा mmci_dmae_priv *dmae = host->dma_priv;
	काष्ठा mmci_dmae_next *nd = &dmae->next_data;

	अगर (!host->use_dma)
		वापस -EINVAL;

	अगर (next)
		वापस _mmci_dmae_prep_data(host, data, &nd->chan, &nd->desc);
	/* Check अगर next job is alपढ़ोy prepared. */
	अगर (dmae->cur && dmae->desc_current)
		वापस 0;

	/* No job were prepared thus करो it now. */
	वापस _mmci_dmae_prep_data(host, data, &dmae->cur,
				    &dmae->desc_current);
पूर्ण

पूर्णांक mmci_dmae_start(काष्ठा mmci_host *host, अचिन्हित पूर्णांक *datactrl)
अणु
	काष्ठा mmci_dmae_priv *dmae = host->dma_priv;
	पूर्णांक ret;

	host->dma_in_progress = true;
	ret = dma_submit_error(dmaengine_submit(dmae->desc_current));
	अगर (ret < 0) अणु
		host->dma_in_progress = false;
		वापस ret;
	पूर्ण
	dma_async_issue_pending(dmae->cur);

	*datactrl |= MCI_DPSM_DMAENABLE;

	वापस 0;
पूर्ण

व्योम mmci_dmae_get_next_data(काष्ठा mmci_host *host, काष्ठा mmc_data *data)
अणु
	काष्ठा mmci_dmae_priv *dmae = host->dma_priv;
	काष्ठा mmci_dmae_next *next = &dmae->next_data;

	अगर (!host->use_dma)
		वापस;

	WARN_ON(!data->host_cookie && (next->desc || next->chan));

	dmae->desc_current = next->desc;
	dmae->cur = next->chan;
	next->desc = शून्य;
	next->chan = शून्य;
पूर्ण

व्योम mmci_dmae_unprep_data(काष्ठा mmci_host *host,
			   काष्ठा mmc_data *data, पूर्णांक err)

अणु
	काष्ठा mmci_dmae_priv *dmae = host->dma_priv;

	अगर (!host->use_dma)
		वापस;

	mmci_dma_unmap(host, data);

	अगर (err) अणु
		काष्ठा mmci_dmae_next *next = &dmae->next_data;
		काष्ठा dma_chan *chan;
		अगर (data->flags & MMC_DATA_READ)
			chan = dmae->rx_channel;
		अन्यथा
			chan = dmae->tx_channel;
		dmaengine_terminate_all(chan);

		अगर (dmae->desc_current == next->desc)
			dmae->desc_current = शून्य;

		अगर (dmae->cur == next->chan) अणु
			host->dma_in_progress = false;
			dmae->cur = शून्य;
		पूर्ण

		next->desc = शून्य;
		next->chan = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा mmci_host_ops mmci_variant_ops = अणु
	.prep_data = mmci_dmae_prep_data,
	.unprep_data = mmci_dmae_unprep_data,
	.get_datactrl_cfg = mmci_get_dctrl_cfg,
	.get_next_data = mmci_dmae_get_next_data,
	.dma_setup = mmci_dmae_setup,
	.dma_release = mmci_dmae_release,
	.dma_start = mmci_dmae_start,
	.dma_finalize = mmci_dmae_finalize,
	.dma_error = mmci_dmae_error,
पूर्ण;
#अन्यथा
अटल काष्ठा mmci_host_ops mmci_variant_ops = अणु
	.get_datactrl_cfg = mmci_get_dctrl_cfg,
पूर्ण;
#पूर्ण_अगर

अटल व्योम mmci_variant_init(काष्ठा mmci_host *host)
अणु
	host->ops = &mmci_variant_ops;
पूर्ण

अटल व्योम ux500_variant_init(काष्ठा mmci_host *host)
अणु
	host->ops = &mmci_variant_ops;
	host->ops->busy_complete = ux500_busy_complete;
पूर्ण

अटल व्योम ux500v2_variant_init(काष्ठा mmci_host *host)
अणु
	host->ops = &mmci_variant_ops;
	host->ops->busy_complete = ux500_busy_complete;
	host->ops->get_datactrl_cfg = ux500v2_get_dctrl_cfg;
पूर्ण

अटल व्योम mmci_pre_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmci_host *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;

	अगर (!data)
		वापस;

	WARN_ON(data->host_cookie);

	अगर (mmci_validate_data(host, data))
		वापस;

	mmci_prep_data(host, data, true);
पूर्ण

अटल व्योम mmci_post_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq,
			      पूर्णांक err)
अणु
	काष्ठा mmci_host *host = mmc_priv(mmc);
	काष्ठा mmc_data *data = mrq->data;

	अगर (!data || !data->host_cookie)
		वापस;

	mmci_unprep_data(host, data, err);
पूर्ण

अटल व्योम mmci_start_data(काष्ठा mmci_host *host, काष्ठा mmc_data *data)
अणु
	काष्ठा variant_data *variant = host->variant;
	अचिन्हित पूर्णांक datactrl, समयout, irqmask;
	अचिन्हित दीर्घ दीर्घ clks;
	व्योम __iomem *base;

	dev_dbg(mmc_dev(host->mmc), "blksz %04x blks %04x flags %08x\n",
		data->blksz, data->blocks, data->flags);

	host->data = data;
	host->size = data->blksz * data->blocks;
	data->bytes_xfered = 0;

	clks = (अचिन्हित दीर्घ दीर्घ)data->समयout_ns * host->cclk;
	करो_भाग(clks, NSEC_PER_SEC);

	समयout = data->समयout_clks + (अचिन्हित पूर्णांक)clks;

	base = host->base;
	ग_लिखोl(समयout, base + MMCIDATATIMER);
	ग_लिखोl(host->size, base + MMCIDATALENGTH);

	datactrl = host->ops->get_datactrl_cfg(host);
	datactrl |= host->data->flags & MMC_DATA_READ ? MCI_DPSM_सूचीECTION : 0;

	अगर (host->mmc->card && mmc_card_sdio(host->mmc->card)) अणु
		u32 clk;

		datactrl |= variant->datactrl_mask_sdio;

		/*
		 * The ST Micro variant क्रम SDIO small ग_लिखो transfers
		 * needs to have घड़ी H/W flow control disabled,
		 * otherwise the transfer will not start. The threshold
		 * depends on the rate of MCLK.
		 */
		अगर (variant->st_sdio && data->flags & MMC_DATA_WRITE &&
		    (host->size < 8 ||
		     (host->size <= 8 && host->mclk > 50000000)))
			clk = host->clk_reg & ~variant->clkreg_enable;
		अन्यथा
			clk = host->clk_reg | variant->clkreg_enable;

		mmci_ग_लिखो_clkreg(host, clk);
	पूर्ण

	अगर (host->mmc->ios.timing == MMC_TIMING_UHS_DDR50 ||
	    host->mmc->ios.timing == MMC_TIMING_MMC_DDR52)
		datactrl |= variant->datactrl_mask_ddrmode;

	/*
	 * Attempt to use DMA operation mode, अगर this
	 * should fail, fall back to PIO mode
	 */
	अगर (!mmci_dma_start(host, datactrl))
		वापस;

	/* IRQ mode, map the SG list क्रम CPU पढ़ोing/writing */
	mmci_init_sg(host, data);

	अगर (data->flags & MMC_DATA_READ) अणु
		irqmask = MCI_RXFIFOHALFFULLMASK;

		/*
		 * If we have less than the fअगरo 'half-full' threshold to
		 * transfer, trigger a PIO पूर्णांकerrupt as soon as any data
		 * is available.
		 */
		अगर (host->size < variant->fअगरohalfsize)
			irqmask |= MCI_RXDATAAVLBLMASK;
	पूर्ण अन्यथा अणु
		/*
		 * We करोn't actually need to include "FIFO empty" here
		 * since its implicit in "FIFO half empty".
		 */
		irqmask = MCI_TXFIFOHALFEMPTYMASK;
	पूर्ण

	mmci_ग_लिखो_datactrlreg(host, datactrl);
	ग_लिखोl(पढ़ोl(base + MMCIMASK0) & ~MCI_DATAENDMASK, base + MMCIMASK0);
	mmci_set_mask1(host, irqmask);
पूर्ण

अटल व्योम
mmci_start_command(काष्ठा mmci_host *host, काष्ठा mmc_command *cmd, u32 c)
अणु
	व्योम __iomem *base = host->base;
	अचिन्हित दीर्घ दीर्घ clks;

	dev_dbg(mmc_dev(host->mmc), "op %02x arg %08x flags %08x\n",
	    cmd->opcode, cmd->arg, cmd->flags);

	अगर (पढ़ोl(base + MMCICOMMAND) & host->variant->cmdreg_cpsm_enable) अणु
		ग_लिखोl(0, base + MMCICOMMAND);
		mmci_reg_delay(host);
	पूर्ण

	अगर (host->variant->cmdreg_stop &&
	    cmd->opcode == MMC_STOP_TRANSMISSION)
		c |= host->variant->cmdreg_stop;

	c |= cmd->opcode | host->variant->cmdreg_cpsm_enable;
	अगर (cmd->flags & MMC_RSP_PRESENT) अणु
		अगर (cmd->flags & MMC_RSP_136)
			c |= host->variant->cmdreg_lrsp_crc;
		अन्यथा अगर (cmd->flags & MMC_RSP_CRC)
			c |= host->variant->cmdreg_srsp_crc;
		अन्यथा
			c |= host->variant->cmdreg_srsp;
	पूर्ण

	अगर (host->variant->busy_समयout && cmd->flags & MMC_RSP_BUSY) अणु
		अगर (!cmd->busy_समयout)
			cmd->busy_समयout = 10 * MSEC_PER_SEC;

		अगर (cmd->busy_समयout > host->mmc->max_busy_समयout)
			clks = (अचिन्हित दीर्घ दीर्घ)host->mmc->max_busy_समयout * host->cclk;
		अन्यथा
			clks = (अचिन्हित दीर्घ दीर्घ)cmd->busy_समयout * host->cclk;

		करो_भाग(clks, MSEC_PER_SEC);
		ग_लिखोl_relaxed(clks, host->base + MMCIDATATIMER);
	पूर्ण

	अगर (host->ops->pre_sig_volt_चयन && cmd->opcode == SD_SWITCH_VOLTAGE)
		host->ops->pre_sig_volt_चयन(host);

	अगर (/*पूर्णांकerrupt*/0)
		c |= MCI_CPSM_INTERRUPT;

	अगर (mmc_cmd_type(cmd) == MMC_CMD_ADTC)
		c |= host->variant->data_cmd_enable;

	host->cmd = cmd;

	ग_लिखोl(cmd->arg, base + MMCIARGUMENT);
	ग_लिखोl(c, base + MMCICOMMAND);
पूर्ण

अटल व्योम mmci_stop_command(काष्ठा mmci_host *host)
अणु
	host->stop_पात.error = 0;
	mmci_start_command(host, &host->stop_पात, 0);
पूर्ण

अटल व्योम
mmci_data_irq(काष्ठा mmci_host *host, काष्ठा mmc_data *data,
	      अचिन्हित पूर्णांक status)
अणु
	अचिन्हित पूर्णांक status_err;

	/* Make sure we have data to handle */
	अगर (!data)
		वापस;

	/* First check क्रम errors */
	status_err = status & (host->variant->start_err |
			       MCI_DATACRCFAIL | MCI_DATATIMEOUT |
			       MCI_TXUNDERRUN | MCI_RXOVERRUN);

	अगर (status_err) अणु
		u32 reमुख्य, success;

		/* Terminate the DMA transfer */
		mmci_dma_error(host);

		/*
		 * Calculate how far we are पूर्णांकo the transfer.  Note that
		 * the data counter gives the number of bytes transferred
		 * on the MMC bus, not on the host side.  On पढ़ोs, this
		 * can be as much as a FIFO-worth of data ahead.  This
		 * matters क्रम FIFO overruns only.
		 */
		अगर (!host->variant->datacnt_useless) अणु
			reमुख्य = पढ़ोl(host->base + MMCIDATACNT);
			success = data->blksz * data->blocks - reमुख्य;
		पूर्ण अन्यथा अणु
			success = 0;
		पूर्ण

		dev_dbg(mmc_dev(host->mmc), "MCI ERROR IRQ, status 0x%08x at 0x%08x\n",
			status_err, success);
		अगर (status_err & MCI_DATACRCFAIL) अणु
			/* Last block was not successful */
			success -= 1;
			data->error = -EILSEQ;
		पूर्ण अन्यथा अगर (status_err & MCI_DATATIMEOUT) अणु
			data->error = -ETIMEDOUT;
		पूर्ण अन्यथा अगर (status_err & MCI_STARTBITERR) अणु
			data->error = -ECOMM;
		पूर्ण अन्यथा अगर (status_err & MCI_TXUNDERRUN) अणु
			data->error = -EIO;
		पूर्ण अन्यथा अगर (status_err & MCI_RXOVERRUN) अणु
			अगर (success > host->variant->fअगरosize)
				success -= host->variant->fअगरosize;
			अन्यथा
				success = 0;
			data->error = -EIO;
		पूर्ण
		data->bytes_xfered = round_करोwn(success, data->blksz);
	पूर्ण

	अगर (status & MCI_DATABLOCKEND)
		dev_err(mmc_dev(host->mmc), "stray MCI_DATABLOCKEND interrupt\n");

	अगर (status & MCI_DATAEND || data->error) अणु
		mmci_dma_finalize(host, data);

		mmci_stop_data(host);

		अगर (!data->error)
			/* The error clause is handled above, success! */
			data->bytes_xfered = data->blksz * data->blocks;

		अगर (!data->stop) अणु
			अगर (host->variant->cmdreg_stop && data->error)
				mmci_stop_command(host);
			अन्यथा
				mmci_request_end(host, data->mrq);
		पूर्ण अन्यथा अगर (host->mrq->sbc && !data->error) अणु
			mmci_request_end(host, data->mrq);
		पूर्ण अन्यथा अणु
			mmci_start_command(host, data->stop, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
mmci_cmd_irq(काष्ठा mmci_host *host, काष्ठा mmc_command *cmd,
	     अचिन्हित पूर्णांक status)
अणु
	u32 err_msk = MCI_CMDCRCFAIL | MCI_CMDTIMEOUT;
	व्योम __iomem *base = host->base;
	bool sbc, busy_resp;

	अगर (!cmd)
		वापस;

	sbc = (cmd == host->mrq->sbc);
	busy_resp = !!(cmd->flags & MMC_RSP_BUSY);

	/*
	 * We need to be one of these पूर्णांकerrupts to be considered worth
	 * handling. Note that we tag on any latent IRQs postponed
	 * due to रुकोing क्रम busy status.
	 */
	अगर (host->variant->busy_समयout && busy_resp)
		err_msk |= MCI_DATATIMEOUT;

	अगर (!((status | host->busy_status) &
	      (err_msk | MCI_CMDSENT | MCI_CMDRESPEND)))
		वापस;

	/* Handle busy detection on DAT0 अगर the variant supports it. */
	अगर (busy_resp && host->variant->busy_detect)
		अगर (!host->ops->busy_complete(host, status, err_msk))
			वापस;

	host->cmd = शून्य;

	अगर (status & MCI_CMDTIMEOUT) अणु
		cmd->error = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (status & MCI_CMDCRCFAIL && cmd->flags & MMC_RSP_CRC) अणु
		cmd->error = -EILSEQ;
	पूर्ण अन्यथा अगर (host->variant->busy_समयout && busy_resp &&
		   status & MCI_DATATIMEOUT) अणु
		cmd->error = -ETIMEDOUT;
		host->irq_action = IRQ_WAKE_THREAD;
	पूर्ण अन्यथा अणु
		cmd->resp[0] = पढ़ोl(base + MMCIRESPONSE0);
		cmd->resp[1] = पढ़ोl(base + MMCIRESPONSE1);
		cmd->resp[2] = पढ़ोl(base + MMCIRESPONSE2);
		cmd->resp[3] = पढ़ोl(base + MMCIRESPONSE3);
	पूर्ण

	अगर ((!sbc && !cmd->data) || cmd->error) अणु
		अगर (host->data) अणु
			/* Terminate the DMA transfer */
			mmci_dma_error(host);

			mmci_stop_data(host);
			अगर (host->variant->cmdreg_stop && cmd->error) अणु
				mmci_stop_command(host);
				वापस;
			पूर्ण
		पूर्ण

		अगर (host->irq_action != IRQ_WAKE_THREAD)
			mmci_request_end(host, host->mrq);

	पूर्ण अन्यथा अगर (sbc) अणु
		mmci_start_command(host, host->mrq->cmd, 0);
	पूर्ण अन्यथा अगर (!host->variant->datactrl_first &&
		   !(cmd->data->flags & MMC_DATA_READ)) अणु
		mmci_start_data(host, cmd->data);
	पूर्ण
पूर्ण

अटल पूर्णांक mmci_get_rx_fअगरocnt(काष्ठा mmci_host *host, u32 status, पूर्णांक reमुख्य)
अणु
	वापस reमुख्य - (पढ़ोl(host->base + MMCIFIFOCNT) << 2);
पूर्ण

अटल पूर्णांक mmci_qcom_get_rx_fअगरocnt(काष्ठा mmci_host *host, u32 status, पूर्णांक r)
अणु
	/*
	 * on qcom SDCC4 only 8 words are used in each burst so only 8 addresses
	 * from the fअगरo range should be used
	 */
	अगर (status & MCI_RXFIFOHALFFULL)
		वापस host->variant->fअगरohalfsize;
	अन्यथा अगर (status & MCI_RXDATAAVLBL)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक mmci_pio_पढ़ो(काष्ठा mmci_host *host, अक्षर *buffer, अचिन्हित पूर्णांक reमुख्य)
अणु
	व्योम __iomem *base = host->base;
	अक्षर *ptr = buffer;
	u32 status = पढ़ोl(host->base + MMCISTATUS);
	पूर्णांक host_reमुख्य = host->size;

	करो अणु
		पूर्णांक count = host->get_rx_fअगरocnt(host, status, host_reमुख्य);

		अगर (count > reमुख्य)
			count = reमुख्य;

		अगर (count <= 0)
			अवरोध;

		/*
		 * SDIO especially may want to send something that is
		 * not भागisible by 4 (as opposed to card sectors
		 * etc). Thereक्रमe make sure to always पढ़ो the last bytes
		 * जबतक only करोing full 32-bit पढ़ोs towards the FIFO.
		 */
		अगर (unlikely(count & 0x3)) अणु
			अगर (count < 4) अणु
				अचिन्हित अक्षर buf[4];
				ioपढ़ो32_rep(base + MMCIFIFO, buf, 1);
				स_नकल(ptr, buf, count);
			पूर्ण अन्यथा अणु
				ioपढ़ो32_rep(base + MMCIFIFO, ptr, count >> 2);
				count &= ~0x3;
			पूर्ण
		पूर्ण अन्यथा अणु
			ioपढ़ो32_rep(base + MMCIFIFO, ptr, count >> 2);
		पूर्ण

		ptr += count;
		reमुख्य -= count;
		host_reमुख्य -= count;

		अगर (reमुख्य == 0)
			अवरोध;

		status = पढ़ोl(base + MMCISTATUS);
	पूर्ण जबतक (status & MCI_RXDATAAVLBL);

	वापस ptr - buffer;
पूर्ण

अटल पूर्णांक mmci_pio_ग_लिखो(काष्ठा mmci_host *host, अक्षर *buffer, अचिन्हित पूर्णांक reमुख्य, u32 status)
अणु
	काष्ठा variant_data *variant = host->variant;
	व्योम __iomem *base = host->base;
	अक्षर *ptr = buffer;

	करो अणु
		अचिन्हित पूर्णांक count, maxcnt;

		maxcnt = status & MCI_TXFIFOEMPTY ?
			 variant->fअगरosize : variant->fअगरohalfsize;
		count = min(reमुख्य, maxcnt);

		/*
		 * SDIO especially may want to send something that is
		 * not भागisible by 4 (as opposed to card sectors
		 * etc), and the FIFO only accept full 32-bit ग_लिखोs.
		 * So compensate by adding +3 on the count, a single
		 * byte become a 32bit ग_लिखो, 7 bytes will be two
		 * 32bit ग_लिखोs etc.
		 */
		ioग_लिखो32_rep(base + MMCIFIFO, ptr, (count + 3) >> 2);

		ptr += count;
		reमुख्य -= count;

		अगर (reमुख्य == 0)
			अवरोध;

		status = पढ़ोl(base + MMCISTATUS);
	पूर्ण जबतक (status & MCI_TXFIFOHALFEMPTY);

	वापस ptr - buffer;
पूर्ण

/*
 * PIO data transfer IRQ handler.
 */
अटल irqवापस_t mmci_pio_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mmci_host *host = dev_id;
	काष्ठा sg_mapping_iter *sg_miter = &host->sg_miter;
	काष्ठा variant_data *variant = host->variant;
	व्योम __iomem *base = host->base;
	u32 status;

	status = पढ़ोl(base + MMCISTATUS);

	dev_dbg(mmc_dev(host->mmc), "irq1 (pio) %08x\n", status);

	करो अणु
		अचिन्हित पूर्णांक reमुख्य, len;
		अक्षर *buffer;

		/*
		 * For ग_लिखो, we only need to test the half-empty flag
		 * here - अगर the FIFO is completely empty, then by
		 * definition it is more than half empty.
		 *
		 * For पढ़ो, check क्रम data available.
		 */
		अगर (!(status & (MCI_TXFIFOHALFEMPTY|MCI_RXDATAAVLBL)))
			अवरोध;

		अगर (!sg_miter_next(sg_miter))
			अवरोध;

		buffer = sg_miter->addr;
		reमुख्य = sg_miter->length;

		len = 0;
		अगर (status & MCI_RXACTIVE)
			len = mmci_pio_पढ़ो(host, buffer, reमुख्य);
		अगर (status & MCI_TXACTIVE)
			len = mmci_pio_ग_लिखो(host, buffer, reमुख्य, status);

		sg_miter->consumed = len;

		host->size -= len;
		reमुख्य -= len;

		अगर (reमुख्य)
			अवरोध;

		status = पढ़ोl(base + MMCISTATUS);
	पूर्ण जबतक (1);

	sg_miter_stop(sg_miter);

	/*
	 * If we have less than the fअगरo 'half-full' threshold to transfer,
	 * trigger a PIO पूर्णांकerrupt as soon as any data is available.
	 */
	अगर (status & MCI_RXACTIVE && host->size < variant->fअगरohalfsize)
		mmci_set_mask1(host, MCI_RXDATAAVLBLMASK);

	/*
	 * If we run out of data, disable the data IRQs; this
	 * prevents a race where the FIFO becomes empty beक्रमe
	 * the chip itself has disabled the data path, and
	 * stops us racing with our data end IRQ.
	 */
	अगर (host->size == 0) अणु
		mmci_set_mask1(host, 0);
		ग_लिखोl(पढ़ोl(base + MMCIMASK0) | MCI_DATAENDMASK, base + MMCIMASK0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Handle completion of command and data transfers.
 */
अटल irqवापस_t mmci_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mmci_host *host = dev_id;
	u32 status;

	spin_lock(&host->lock);
	host->irq_action = IRQ_HANDLED;

	करो अणु
		status = पढ़ोl(host->base + MMCISTATUS);

		अगर (host->singleirq) अणु
			अगर (status & host->mask1_reg)
				mmci_pio_irq(irq, dev_id);

			status &= ~host->variant->irq_pio_mask;
		पूर्ण

		/*
		 * Busy detection is managed by mmci_cmd_irq(), including to
		 * clear the corresponding IRQ.
		 */
		status &= पढ़ोl(host->base + MMCIMASK0);
		अगर (host->variant->busy_detect)
			ग_लिखोl(status & ~host->variant->busy_detect_mask,
			       host->base + MMCICLEAR);
		अन्यथा
			ग_लिखोl(status, host->base + MMCICLEAR);

		dev_dbg(mmc_dev(host->mmc), "irq0 (data+cmd) %08x\n", status);

		अगर (host->variant->reversed_irq_handling) अणु
			mmci_data_irq(host, host->data, status);
			mmci_cmd_irq(host, host->cmd, status);
		पूर्ण अन्यथा अणु
			mmci_cmd_irq(host, host->cmd, status);
			mmci_data_irq(host, host->data, status);
		पूर्ण

		/*
		 * Busy detection has been handled by mmci_cmd_irq() above.
		 * Clear the status bit to prevent polling in IRQ context.
		 */
		अगर (host->variant->busy_detect_flag)
			status &= ~host->variant->busy_detect_flag;

	पूर्ण जबतक (status);

	spin_unlock(&host->lock);

	वापस host->irq_action;
पूर्ण

/*
 * mmci_irq_thपढ़ो() - A thपढ़ोed IRQ handler that manages a reset of the HW.
 *
 * A reset is needed क्रम some variants, where a dataसमयout क्रम a R1B request
 * causes the DPSM to stay busy (non-functional).
 */
अटल irqवापस_t mmci_irq_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mmci_host *host = dev_id;
	अचिन्हित दीर्घ flags;

	अगर (host->rst) अणु
		reset_control_निश्चित(host->rst);
		udelay(2);
		reset_control_deनिश्चित(host->rst);
	पूर्ण

	spin_lock_irqsave(&host->lock, flags);
	ग_लिखोl(host->clk_reg, host->base + MMCICLOCK);
	ग_लिखोl(host->pwr_reg, host->base + MMCIPOWER);
	ग_लिखोl(MCI_IRQENABLE | host->variant->start_err,
	       host->base + MMCIMASK0);

	host->irq_action = IRQ_HANDLED;
	mmci_request_end(host, host->mrq);
	spin_unlock_irqrestore(&host->lock, flags);

	वापस host->irq_action;
पूर्ण

अटल व्योम mmci_request(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq)
अणु
	काष्ठा mmci_host *host = mmc_priv(mmc);
	अचिन्हित दीर्घ flags;

	WARN_ON(host->mrq != शून्य);

	mrq->cmd->error = mmci_validate_data(host, mrq->data);
	अगर (mrq->cmd->error) अणु
		mmc_request_करोne(mmc, mrq);
		वापस;
	पूर्ण

	spin_lock_irqsave(&host->lock, flags);

	host->mrq = mrq;

	अगर (mrq->data)
		mmci_get_next_data(host, mrq->data);

	अगर (mrq->data &&
	    (host->variant->datactrl_first || mrq->data->flags & MMC_DATA_READ))
		mmci_start_data(host, mrq->data);

	अगर (mrq->sbc)
		mmci_start_command(host, mrq->sbc, 0);
	अन्यथा
		mmci_start_command(host, mrq->cmd, 0);

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम mmci_set_max_busy_समयout(काष्ठा mmc_host *mmc)
अणु
	काष्ठा mmci_host *host = mmc_priv(mmc);
	u32 max_busy_समयout = 0;

	अगर (!host->variant->busy_detect)
		वापस;

	अगर (host->variant->busy_समयout && mmc->actual_घड़ी)
		max_busy_समयout = ~0UL / (mmc->actual_घड़ी / MSEC_PER_SEC);

	mmc->max_busy_समयout = max_busy_समयout;
पूर्ण

अटल व्योम mmci_set_ios(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा mmci_host *host = mmc_priv(mmc);
	काष्ठा variant_data *variant = host->variant;
	u32 pwr = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (host->plat->ios_handler &&
		host->plat->ios_handler(mmc_dev(mmc), ios))
			dev_err(mmc_dev(mmc), "platform ios_handler failed\n");

	चयन (ios->घातer_mode) अणु
	हाल MMC_POWER_OFF:
		अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);

		अगर (!IS_ERR(mmc->supply.vqmmc) && host->vqmmc_enabled) अणु
			regulator_disable(mmc->supply.vqmmc);
			host->vqmmc_enabled = false;
		पूर्ण

		अवरोध;
	हाल MMC_POWER_UP:
		अगर (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, ios->vdd);

		/*
		 * The ST Micro variant करोesn't have the PL180s MCI_PWR_UP
		 * and instead uses MCI_PWR_ON so apply whatever value is
		 * configured in the variant data.
		 */
		pwr |= variant->pwrreg_घातerup;

		अवरोध;
	हाल MMC_POWER_ON:
		अगर (!IS_ERR(mmc->supply.vqmmc) && !host->vqmmc_enabled) अणु
			ret = regulator_enable(mmc->supply.vqmmc);
			अगर (ret < 0)
				dev_err(mmc_dev(mmc),
					"failed to enable vqmmc regulator\n");
			अन्यथा
				host->vqmmc_enabled = true;
		पूर्ण

		pwr |= MCI_PWR_ON;
		अवरोध;
	पूर्ण

	अगर (variant->संकेत_direction && ios->घातer_mode != MMC_POWER_OFF) अणु
		/*
		 * The ST Micro variant has some additional bits
		 * indicating संकेत direction क्रम the संकेतs in
		 * the SD/MMC bus and feedback-घड़ी usage.
		 */
		pwr |= host->pwr_reg_add;

		अगर (ios->bus_width == MMC_BUS_WIDTH_4)
			pwr &= ~MCI_ST_DATA74सूचीEN;
		अन्यथा अगर (ios->bus_width == MMC_BUS_WIDTH_1)
			pwr &= (~MCI_ST_DATA74सूचीEN &
				~MCI_ST_DATA31सूचीEN &
				~MCI_ST_DATA2सूचीEN);
	पूर्ण

	अगर (variant->खोलोdrain) अणु
		अगर (ios->bus_mode == MMC_BUSMODE_OPENDRAIN)
			pwr |= variant->खोलोdrain;
	पूर्ण अन्यथा अणु
		/*
		 * If the variant cannot configure the pads by its own, then we
		 * expect the pinctrl to be able to करो that क्रम us
		 */
		अगर (ios->bus_mode == MMC_BUSMODE_OPENDRAIN)
			pinctrl_select_state(host->pinctrl, host->pins_खोलोdrain);
		अन्यथा
			pinctrl_select_शेष_state(mmc_dev(mmc));
	पूर्ण

	/*
	 * If घड़ी = 0 and the variant requires the MMCIPOWER to be used क्रम
	 * gating the घड़ी, the MCI_PWR_ON bit is cleared.
	 */
	अगर (!ios->घड़ी && variant->pwrreg_clkgate)
		pwr &= ~MCI_PWR_ON;

	अगर (host->variant->explicit_mclk_control &&
	    ios->घड़ी != host->घड़ी_cache) अणु
		ret = clk_set_rate(host->clk, ios->घड़ी);
		अगर (ret < 0)
			dev_err(mmc_dev(host->mmc),
				"Error setting clock rate (%d)\n", ret);
		अन्यथा
			host->mclk = clk_get_rate(host->clk);
	पूर्ण
	host->घड़ी_cache = ios->घड़ी;

	spin_lock_irqsave(&host->lock, flags);

	अगर (host->ops && host->ops->set_clkreg)
		host->ops->set_clkreg(host, ios->घड़ी);
	अन्यथा
		mmci_set_clkreg(host, ios->घड़ी);

	mmci_set_max_busy_समयout(mmc);

	अगर (host->ops && host->ops->set_pwrreg)
		host->ops->set_pwrreg(host, pwr);
	अन्यथा
		mmci_ग_लिखो_pwrreg(host, pwr);

	mmci_reg_delay(host);

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल पूर्णांक mmci_get_cd(काष्ठा mmc_host *mmc)
अणु
	काष्ठा mmci_host *host = mmc_priv(mmc);
	काष्ठा mmci_platक्रमm_data *plat = host->plat;
	अचिन्हित पूर्णांक status = mmc_gpio_get_cd(mmc);

	अगर (status == -ENOSYS) अणु
		अगर (!plat->status)
			वापस 1; /* Assume always present */

		status = plat->status(mmc_dev(host->mmc));
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक mmci_sig_volt_चयन(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा mmci_host *host = mmc_priv(mmc);
	पूर्णांक ret;

	ret = mmc_regulator_set_vqmmc(mmc, ios);

	अगर (!ret && host->ops && host->ops->post_sig_volt_चयन)
		ret = host->ops->post_sig_volt_चयन(host, ios);
	अन्यथा अगर (ret)
		ret = 0;

	अगर (ret < 0)
		dev_warn(mmc_dev(mmc), "Voltage switch failed\n");

	वापस ret;
पूर्ण

अटल काष्ठा mmc_host_ops mmci_ops = अणु
	.request	= mmci_request,
	.pre_req	= mmci_pre_request,
	.post_req	= mmci_post_request,
	.set_ios	= mmci_set_ios,
	.get_ro		= mmc_gpio_get_ro,
	.get_cd		= mmci_get_cd,
	.start_संकेत_voltage_चयन = mmci_sig_volt_चयन,
पूर्ण;

अटल व्योम mmci_probe_level_translator(काष्ठा mmc_host *mmc)
अणु
	काष्ठा device *dev = mmc_dev(mmc);
	काष्ठा mmci_host *host = mmc_priv(mmc);
	काष्ठा gpio_desc *cmd_gpio;
	काष्ठा gpio_desc *ck_gpio;
	काष्ठा gpio_desc *ckin_gpio;
	पूर्णांक clk_hi, clk_lo;

	/*
	 * Assume the level translator is present अगर st,use-ckin is set.
	 * This is to cater क्रम DTs which करो not implement this test.
	 */
	host->clk_reg_add |= MCI_STM32_CLK_SELCKIN;

	cmd_gpio = gpiod_get(dev, "st,cmd", GPIOD_OUT_HIGH);
	अगर (IS_ERR(cmd_gpio))
		जाओ निकास_cmd;

	ck_gpio = gpiod_get(dev, "st,ck", GPIOD_OUT_HIGH);
	अगर (IS_ERR(ck_gpio))
		जाओ निकास_ck;

	ckin_gpio = gpiod_get(dev, "st,ckin", GPIOD_IN);
	अगर (IS_ERR(ckin_gpio))
		जाओ निकास_ckin;

	/* All GPIOs are valid, test whether level translator works */

	/* Sample CKIN */
	clk_hi = !!gpiod_get_value(ckin_gpio);

	/* Set CK low */
	gpiod_set_value(ck_gpio, 0);

	/* Sample CKIN */
	clk_lo = !!gpiod_get_value(ckin_gpio);

	/* Tristate all */
	gpiod_direction_input(cmd_gpio);
	gpiod_direction_input(ck_gpio);

	/* Level translator is present अगर CK संकेत is propagated to CKIN */
	अगर (!clk_hi || clk_lo) अणु
		host->clk_reg_add &= ~MCI_STM32_CLK_SELCKIN;
		dev_warn(dev,
			 "Level translator inoperable, CK signal not detected on CKIN, disabling.\n");
	पूर्ण

	gpiod_put(ckin_gpio);

निकास_ckin:
	gpiod_put(ck_gpio);
निकास_ck:
	gpiod_put(cmd_gpio);
निकास_cmd:
	pinctrl_select_शेष_state(dev);
पूर्ण

अटल पूर्णांक mmci_of_parse(काष्ठा device_node *np, काष्ठा mmc_host *mmc)
अणु
	काष्ठा mmci_host *host = mmc_priv(mmc);
	पूर्णांक ret = mmc_of_parse(mmc);

	अगर (ret)
		वापस ret;

	अगर (of_get_property(np, "st,sig-dir-dat0", शून्य))
		host->pwr_reg_add |= MCI_ST_DATA0सूचीEN;
	अगर (of_get_property(np, "st,sig-dir-dat2", शून्य))
		host->pwr_reg_add |= MCI_ST_DATA2सूचीEN;
	अगर (of_get_property(np, "st,sig-dir-dat31", शून्य))
		host->pwr_reg_add |= MCI_ST_DATA31सूचीEN;
	अगर (of_get_property(np, "st,sig-dir-dat74", शून्य))
		host->pwr_reg_add |= MCI_ST_DATA74सूचीEN;
	अगर (of_get_property(np, "st,sig-dir-cmd", शून्य))
		host->pwr_reg_add |= MCI_ST_CMDसूचीEN;
	अगर (of_get_property(np, "st,sig-pin-fbclk", शून्य))
		host->pwr_reg_add |= MCI_ST_FBCLKEN;
	अगर (of_get_property(np, "st,sig-dir", शून्य))
		host->pwr_reg_add |= MCI_STM32_सूचीPOL;
	अगर (of_get_property(np, "st,neg-edge", शून्य))
		host->clk_reg_add |= MCI_STM32_CLK_NEGEDGE;
	अगर (of_get_property(np, "st,use-ckin", शून्य))
		mmci_probe_level_translator(mmc);

	अगर (of_get_property(np, "mmc-cap-mmc-highspeed", शून्य))
		mmc->caps |= MMC_CAP_MMC_HIGHSPEED;
	अगर (of_get_property(np, "mmc-cap-sd-highspeed", शून्य))
		mmc->caps |= MMC_CAP_SD_HIGHSPEED;

	वापस 0;
पूर्ण

अटल पूर्णांक mmci_probe(काष्ठा amba_device *dev,
	स्थिर काष्ठा amba_id *id)
अणु
	काष्ठा mmci_platक्रमm_data *plat = dev->dev.platक्रमm_data;
	काष्ठा device_node *np = dev->dev.of_node;
	काष्ठा variant_data *variant = id->data;
	काष्ठा mmci_host *host;
	काष्ठा mmc_host *mmc;
	पूर्णांक ret;

	/* Must have platक्रमm data or Device Tree. */
	अगर (!plat && !np) अणु
		dev_err(&dev->dev, "No plat data or DT found\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!plat) अणु
		plat = devm_kzalloc(&dev->dev, माप(*plat), GFP_KERNEL);
		अगर (!plat)
			वापस -ENOMEM;
	पूर्ण

	mmc = mmc_alloc_host(माप(काष्ठा mmci_host), &dev->dev);
	अगर (!mmc)
		वापस -ENOMEM;

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->mmc_ops = &mmci_ops;
	mmc->ops = &mmci_ops;

	ret = mmci_of_parse(np, mmc);
	अगर (ret)
		जाओ host_मुक्त;

	/*
	 * Some variant (STM32) करोesn't have खोलोdrain bit, nevertheless
	 * pins can be set accordingly using pinctrl
	 */
	अगर (!variant->खोलोdrain) अणु
		host->pinctrl = devm_pinctrl_get(&dev->dev);
		अगर (IS_ERR(host->pinctrl)) अणु
			dev_err(&dev->dev, "failed to get pinctrl");
			ret = PTR_ERR(host->pinctrl);
			जाओ host_मुक्त;
		पूर्ण

		host->pins_खोलोdrain = pinctrl_lookup_state(host->pinctrl,
							    MMCI_PINCTRL_STATE_OPENDRAIN);
		अगर (IS_ERR(host->pins_खोलोdrain)) अणु
			dev_err(mmc_dev(mmc), "Can't select opendrain pins\n");
			ret = PTR_ERR(host->pins_खोलोdrain);
			जाओ host_मुक्त;
		पूर्ण
	पूर्ण

	host->hw_designer = amba_manf(dev);
	host->hw_revision = amba_rev(dev);
	dev_dbg(mmc_dev(mmc), "designer ID = 0x%02x\n", host->hw_designer);
	dev_dbg(mmc_dev(mmc), "revision = 0x%01x\n", host->hw_revision);

	host->clk = devm_clk_get(&dev->dev, शून्य);
	अगर (IS_ERR(host->clk)) अणु
		ret = PTR_ERR(host->clk);
		जाओ host_मुक्त;
	पूर्ण

	ret = clk_prepare_enable(host->clk);
	अगर (ret)
		जाओ host_मुक्त;

	अगर (variant->qcom_fअगरo)
		host->get_rx_fअगरocnt = mmci_qcom_get_rx_fअगरocnt;
	अन्यथा
		host->get_rx_fअगरocnt = mmci_get_rx_fअगरocnt;

	host->plat = plat;
	host->variant = variant;
	host->mclk = clk_get_rate(host->clk);
	/*
	 * According to the spec, mclk is max 100 MHz,
	 * so we try to adjust the घड़ी करोwn to this,
	 * (अगर possible).
	 */
	अगर (host->mclk > variant->f_max) अणु
		ret = clk_set_rate(host->clk, variant->f_max);
		अगर (ret < 0)
			जाओ clk_disable;
		host->mclk = clk_get_rate(host->clk);
		dev_dbg(mmc_dev(mmc), "eventual mclk rate: %u Hz\n",
			host->mclk);
	पूर्ण

	host->phybase = dev->res.start;
	host->base = devm_ioremap_resource(&dev->dev, &dev->res);
	अगर (IS_ERR(host->base)) अणु
		ret = PTR_ERR(host->base);
		जाओ clk_disable;
	पूर्ण

	अगर (variant->init)
		variant->init(host);

	/*
	 * The ARM and ST versions of the block have slightly dअगरferent
	 * घड़ी भागider equations which means that the minimum भागider
	 * dअगरfers too.
	 * on Qualcomm like controllers get the nearest minimum घड़ी to 100Khz
	 */
	अगर (variant->st_clkभाग)
		mmc->f_min = DIV_ROUND_UP(host->mclk, 257);
	अन्यथा अगर (variant->sपंचांग32_clkभाग)
		mmc->f_min = DIV_ROUND_UP(host->mclk, 2046);
	अन्यथा अगर (variant->explicit_mclk_control)
		mmc->f_min = clk_round_rate(host->clk, 100000);
	अन्यथा
		mmc->f_min = DIV_ROUND_UP(host->mclk, 512);
	/*
	 * If no maximum operating frequency is supplied, fall back to use
	 * the module parameter, which has a (low) शेष value in हाल it
	 * is not specअगरied. Either value must not exceed the घड़ी rate पूर्णांकo
	 * the block, of course.
	 */
	अगर (mmc->f_max)
		mmc->f_max = variant->explicit_mclk_control ?
				min(variant->f_max, mmc->f_max) :
				min(host->mclk, mmc->f_max);
	अन्यथा
		mmc->f_max = variant->explicit_mclk_control ?
				fmax : min(host->mclk, fmax);


	dev_dbg(mmc_dev(mmc), "clocking block at %u Hz\n", mmc->f_max);

	host->rst = devm_reset_control_get_optional_exclusive(&dev->dev, शून्य);
	अगर (IS_ERR(host->rst)) अणु
		ret = PTR_ERR(host->rst);
		जाओ clk_disable;
	पूर्ण

	/* Get regulators and the supported OCR mask */
	ret = mmc_regulator_get_supply(mmc);
	अगर (ret)
		जाओ clk_disable;

	अगर (!mmc->ocr_avail)
		mmc->ocr_avail = plat->ocr_mask;
	अन्यथा अगर (plat->ocr_mask)
		dev_warn(mmc_dev(mmc), "Platform OCR mask is ignored\n");

	/* We support these capabilities. */
	mmc->caps |= MMC_CAP_CMD23;

	/*
	 * Enable busy detection.
	 */
	अगर (variant->busy_detect) अणु
		mmci_ops.card_busy = mmci_card_busy;
		/*
		 * Not all variants have a flag to enable busy detection
		 * in the DPSM, but अगर they करो, set it here.
		 */
		अगर (variant->busy_dpsm_flag)
			mmci_ग_लिखो_datactrlreg(host,
					       host->variant->busy_dpsm_flag);
		mmc->caps |= MMC_CAP_WAIT_WHILE_BUSY;
	पूर्ण

	/* Variants with mandatory busy समयout in HW needs R1B responses. */
	अगर (variant->busy_समयout)
		mmc->caps |= MMC_CAP_NEED_RSP_BUSY;

	/* Prepare a CMD12 - needed to clear the DPSM on some variants. */
	host->stop_पात.opcode = MMC_STOP_TRANSMISSION;
	host->stop_पात.arg = 0;
	host->stop_पात.flags = MMC_RSP_R1B | MMC_CMD_AC;

	/* We support these PM capabilities. */
	mmc->pm_caps |= MMC_PM_KEEP_POWER;

	/*
	 * We can करो SGIO
	 */
	mmc->max_segs = NR_SG;

	/*
	 * Since only a certain number of bits are valid in the data length
	 * रेजिस्टर, we must ensure that we करोn't exceed 2^num-1 bytes in a
	 * single request.
	 */
	mmc->max_req_size = (1 << variant->datalength_bits) - 1;

	/*
	 * Set the maximum segment size.  Since we aren't करोing DMA
	 * (yet) we are only limited by the data length रेजिस्टर.
	 */
	mmc->max_seg_size = mmc->max_req_size;

	/*
	 * Block size can be up to 2048 bytes, but must be a घातer of two.
	 */
	mmc->max_blk_size = 1 << variant->datactrl_blocksz;

	/*
	 * Limit the number of blocks transferred so that we करोn't overflow
	 * the maximum request size.
	 */
	mmc->max_blk_count = mmc->max_req_size >> variant->datactrl_blocksz;

	spin_lock_init(&host->lock);

	ग_लिखोl(0, host->base + MMCIMASK0);

	अगर (variant->mmcimask1)
		ग_लिखोl(0, host->base + MMCIMASK1);

	ग_लिखोl(0xfff, host->base + MMCICLEAR);

	/*
	 * If:
	 * - not using DT but using a descriptor table, or
	 * - using a table of descriptors ALONGSIDE DT, or
	 * look up these descriptors named "cd" and "wp" right here, fail
	 * silently of these करो not exist
	 */
	अगर (!np) अणु
		ret = mmc_gpiod_request_cd(mmc, "cd", 0, false, 0);
		अगर (ret == -EPROBE_DEFER)
			जाओ clk_disable;

		ret = mmc_gpiod_request_ro(mmc, "wp", 0, 0);
		अगर (ret == -EPROBE_DEFER)
			जाओ clk_disable;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&dev->dev, dev->irq[0], mmci_irq,
					mmci_irq_thपढ़ो, IRQF_SHARED,
					DRIVER_NAME " (cmd)", host);
	अगर (ret)
		जाओ clk_disable;

	अगर (!dev->irq[1])
		host->singleirq = true;
	अन्यथा अणु
		ret = devm_request_irq(&dev->dev, dev->irq[1], mmci_pio_irq,
				IRQF_SHARED, DRIVER_NAME " (pio)", host);
		अगर (ret)
			जाओ clk_disable;
	पूर्ण

	ग_लिखोl(MCI_IRQENABLE | variant->start_err, host->base + MMCIMASK0);

	amba_set_drvdata(dev, mmc);

	dev_info(&dev->dev, "%s: PL%03x manf %x rev%u at 0x%08llx irq %d,%d (pio)\n",
		 mmc_hostname(mmc), amba_part(dev), amba_manf(dev),
		 amba_rev(dev), (अचिन्हित दीर्घ दीर्घ)dev->res.start,
		 dev->irq[0], dev->irq[1]);

	mmci_dma_setup(host);

	pm_runसमय_set_स्वतःsuspend_delay(&dev->dev, 50);
	pm_runसमय_use_स्वतःsuspend(&dev->dev);

	mmc_add_host(mmc);

	pm_runसमय_put(&dev->dev);
	वापस 0;

 clk_disable:
	clk_disable_unprepare(host->clk);
 host_मुक्त:
	mmc_मुक्त_host(mmc);
	वापस ret;
पूर्ण

अटल व्योम mmci_हटाओ(काष्ठा amba_device *dev)
अणु
	काष्ठा mmc_host *mmc = amba_get_drvdata(dev);

	अगर (mmc) अणु
		काष्ठा mmci_host *host = mmc_priv(mmc);
		काष्ठा variant_data *variant = host->variant;

		/*
		 * Unकरो pm_runसमय_put() in probe.  We use the _sync
		 * version here so that we can access the primecell.
		 */
		pm_runसमय_get_sync(&dev->dev);

		mmc_हटाओ_host(mmc);

		ग_लिखोl(0, host->base + MMCIMASK0);

		अगर (variant->mmcimask1)
			ग_लिखोl(0, host->base + MMCIMASK1);

		ग_लिखोl(0, host->base + MMCICOMMAND);
		ग_लिखोl(0, host->base + MMCIDATACTRL);

		mmci_dma_release(host);
		clk_disable_unprepare(host->clk);
		mmc_मुक्त_host(mmc);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम mmci_save(काष्ठा mmci_host *host)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);

	ग_लिखोl(0, host->base + MMCIMASK0);
	अगर (host->variant->pwrreg_noघातer) अणु
		ग_लिखोl(0, host->base + MMCIDATACTRL);
		ग_लिखोl(0, host->base + MMCIPOWER);
		ग_लिखोl(0, host->base + MMCICLOCK);
	पूर्ण
	mmci_reg_delay(host);

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल व्योम mmci_restore(काष्ठा mmci_host *host)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&host->lock, flags);

	अगर (host->variant->pwrreg_noघातer) अणु
		ग_लिखोl(host->clk_reg, host->base + MMCICLOCK);
		ग_लिखोl(host->datactrl_reg, host->base + MMCIDATACTRL);
		ग_लिखोl(host->pwr_reg, host->base + MMCIPOWER);
	पूर्ण
	ग_लिखोl(MCI_IRQENABLE | host->variant->start_err,
	       host->base + MMCIMASK0);
	mmci_reg_delay(host);

	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

अटल पूर्णांक mmci_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा amba_device *adev = to_amba_device(dev);
	काष्ठा mmc_host *mmc = amba_get_drvdata(adev);

	अगर (mmc) अणु
		काष्ठा mmci_host *host = mmc_priv(mmc);
		pinctrl_pm_select_sleep_state(dev);
		mmci_save(host);
		clk_disable_unprepare(host->clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmci_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा amba_device *adev = to_amba_device(dev);
	काष्ठा mmc_host *mmc = amba_get_drvdata(adev);

	अगर (mmc) अणु
		काष्ठा mmci_host *host = mmc_priv(mmc);
		clk_prepare_enable(host->clk);
		mmci_restore(host);
		pinctrl_select_शेष_state(dev);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops mmci_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(mmci_runसमय_suspend, mmci_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा amba_id mmci_ids[] = अणु
	अणु
		.id	= 0x00041180,
		.mask	= 0xff0fffff,
		.data	= &variant_arm,
	पूर्ण,
	अणु
		.id	= 0x01041180,
		.mask	= 0xff0fffff,
		.data	= &variant_arm_extended_fअगरo,
	पूर्ण,
	अणु
		.id	= 0x02041180,
		.mask	= 0xff0fffff,
		.data	= &variant_arm_extended_fअगरo_hwfc,
	पूर्ण,
	अणु
		.id	= 0x00041181,
		.mask	= 0x000fffff,
		.data	= &variant_arm,
	पूर्ण,
	/* ST Micro variants */
	अणु
		.id     = 0x00180180,
		.mask   = 0x00ffffff,
		.data	= &variant_u300,
	पूर्ण,
	अणु
		.id     = 0x10180180,
		.mask   = 0xf0ffffff,
		.data	= &variant_nomadik,
	पूर्ण,
	अणु
		.id     = 0x00280180,
		.mask   = 0x00ffffff,
		.data	= &variant_nomadik,
	पूर्ण,
	अणु
		.id     = 0x00480180,
		.mask   = 0xf0ffffff,
		.data	= &variant_ux500,
	पूर्ण,
	अणु
		.id     = 0x10480180,
		.mask   = 0xf0ffffff,
		.data	= &variant_ux500v2,
	पूर्ण,
	अणु
		.id     = 0x00880180,
		.mask   = 0x00ffffff,
		.data	= &variant_sपंचांग32,
	पूर्ण,
	अणु
		.id     = 0x10153180,
		.mask	= 0xf0ffffff,
		.data	= &variant_sपंचांग32_sdmmc,
	पूर्ण,
	अणु
		.id     = 0x00253180,
		.mask	= 0xf0ffffff,
		.data	= &variant_sपंचांग32_sdmmcv2,
	पूर्ण,
	/* Qualcomm variants */
	अणु
		.id     = 0x00051180,
		.mask	= 0x000fffff,
		.data	= &variant_qcom,
	पूर्ण,
	अणु 0, 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, mmci_ids);

अटल काष्ठा amba_driver mmci_driver = अणु
	.drv		= अणु
		.name	= DRIVER_NAME,
		.pm	= &mmci_dev_pm_ops,
	पूर्ण,
	.probe		= mmci_probe,
	.हटाओ		= mmci_हटाओ,
	.id_table	= mmci_ids,
पूर्ण;

module_amba_driver(mmci_driver);

module_param(fmax, uपूर्णांक, 0444);

MODULE_DESCRIPTION("ARM PrimeCell PL180/181 Multimedia Card Interface driver");
MODULE_LICENSE("GPL");
