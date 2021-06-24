<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale eSDHC controller driver.
 *
 * Copyright (c) 2007, 2010, 2012 Freescale Semiconductor, Inc.
 * Copyright (c) 2009 MontaVista Software, Inc.
 * Copyright 2020 NXP
 *
 * Authors: Xiaobo Xie <X.Xie@मुक्तscale.com>
 *	    Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/clk.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश "sdhci-pltfm.h"
#समावेश "sdhci-esdhc.h"

#घोषणा VENDOR_V_22	0x12
#घोषणा VENDOR_V_23	0x13

#घोषणा MMC_TIMING_NUM (MMC_TIMING_MMC_HS400 + 1)

काष्ठा esdhc_clk_fixup अणु
	स्थिर अचिन्हित पूर्णांक sd_dflt_max_clk;
	स्थिर अचिन्हित पूर्णांक max_clk[MMC_TIMING_NUM];
पूर्ण;

अटल स्थिर काष्ठा esdhc_clk_fixup ls1021a_esdhc_clk = अणु
	.sd_dflt_max_clk = 25000000,
	.max_clk[MMC_TIMING_MMC_HS] = 46500000,
	.max_clk[MMC_TIMING_SD_HS] = 46500000,
पूर्ण;

अटल स्थिर काष्ठा esdhc_clk_fixup ls1046a_esdhc_clk = अणु
	.sd_dflt_max_clk = 25000000,
	.max_clk[MMC_TIMING_UHS_SDR104] = 167000000,
	.max_clk[MMC_TIMING_MMC_HS200] = 167000000,
पूर्ण;

अटल स्थिर काष्ठा esdhc_clk_fixup ls1012a_esdhc_clk = अणु
	.sd_dflt_max_clk = 25000000,
	.max_clk[MMC_TIMING_UHS_SDR104] = 125000000,
	.max_clk[MMC_TIMING_MMC_HS200] = 125000000,
पूर्ण;

अटल स्थिर काष्ठा esdhc_clk_fixup p1010_esdhc_clk = अणु
	.sd_dflt_max_clk = 20000000,
	.max_clk[MMC_TIMING_LEGACY] = 20000000,
	.max_clk[MMC_TIMING_MMC_HS] = 42000000,
	.max_clk[MMC_TIMING_SD_HS] = 40000000,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sdhci_esdhc_of_match[] = अणु
	अणु .compatible = "fsl,ls1021a-esdhc", .data = &ls1021a_esdhc_clkपूर्ण,
	अणु .compatible = "fsl,ls1046a-esdhc", .data = &ls1046a_esdhc_clkपूर्ण,
	अणु .compatible = "fsl,ls1012a-esdhc", .data = &ls1012a_esdhc_clkपूर्ण,
	अणु .compatible = "fsl,p1010-esdhc",   .data = &p1010_esdhc_clkपूर्ण,
	अणु .compatible = "fsl,mpc8379-esdhc" पूर्ण,
	अणु .compatible = "fsl,mpc8536-esdhc" पूर्ण,
	अणु .compatible = "fsl,esdhc" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_esdhc_of_match);

काष्ठा sdhci_esdhc अणु
	u8 venकरोr_ver;
	u8 spec_ver;
	bool quirk_incorrect_hostver;
	bool quirk_limited_clk_भागision;
	bool quirk_unreliable_pulse_detection;
	bool quirk_tuning_erratum_type1;
	bool quirk_tuning_erratum_type2;
	bool quirk_ignore_data_inhibit;
	bool quirk_delay_beक्रमe_data_reset;
	bool quirk_trans_complete_erratum;
	bool in_sw_tuning;
	अचिन्हित पूर्णांक peripheral_घड़ी;
	स्थिर काष्ठा esdhc_clk_fixup *clk_fixup;
	u32 भाग_ratio;
पूर्ण;

/**
 * esdhc_पढ़ो*_fixup - Fixup the value पढ़ो from incompatible eSDHC रेजिस्टर
 *		       to make it compatible with SD spec.
 *
 * @host: poपूर्णांकer to sdhci_host
 * @spec_reg: SD spec रेजिस्टर address
 * @value: 32bit eSDHC रेजिस्टर value on spec_reg address
 *
 * In SD spec, there are 8/16/32/64 bits रेजिस्टरs, जबतक all of eSDHC
 * रेजिस्टरs are 32 bits. There are dअगरferences in रेजिस्टर size, रेजिस्टर
 * address, रेजिस्टर function, bit position and function between eSDHC spec
 * and SD spec.
 *
 * Return a fixed up रेजिस्टर value
 */
अटल u32 esdhc_पढ़ोl_fixup(काष्ठा sdhci_host *host,
				     पूर्णांक spec_reg, u32 value)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	u32 ret;

	/*
	 * The bit of ADMA flag in eSDHC is not compatible with standard
	 * SDHC रेजिस्टर, so set fake flag SDHCI_CAN_DO_ADMA2 when ADMA is
	 * supported by eSDHC.
	 * And क्रम many FSL eSDHC controller, the reset value of field
	 * SDHCI_CAN_DO_ADMA1 is 1, but some of them can't support ADMA,
	 * only these venकरोr version is greater than 2.2/0x12 support ADMA.
	 */
	अगर ((spec_reg == SDHCI_CAPABILITIES) && (value & SDHCI_CAN_DO_ADMA1)) अणु
		अगर (esdhc->venकरोr_ver > VENDOR_V_22) अणु
			ret = value | SDHCI_CAN_DO_ADMA2;
			वापस ret;
		पूर्ण
	पूर्ण
	/*
	 * The DAT[3:0] line संकेत levels and the CMD line संकेत level are
	 * not compatible with standard SDHC रेजिस्टर. The line संकेत levels
	 * DAT[7:0] are at bits 31:24 and the command line संकेत level is at
	 * bit 23. All other bits are the same as in the standard SDHC
	 * रेजिस्टर.
	 */
	अगर (spec_reg == SDHCI_PRESENT_STATE) अणु
		ret = value & 0x000fffff;
		ret |= (value >> 4) & SDHCI_DATA_LVL_MASK;
		ret |= (value << 1) & SDHCI_CMD_LVL;
		वापस ret;
	पूर्ण

	/*
	 * DTS properties of mmc host are used to enable each speed mode
	 * according to soc and board capability. So clean up
	 * SDR50/SDR104/DDR50 support bits here.
	 */
	अगर (spec_reg == SDHCI_CAPABILITIES_1) अणु
		ret = value & ~(SDHCI_SUPPORT_SDR50 | SDHCI_SUPPORT_SDR104 |
				SDHCI_SUPPORT_DDR50);
		वापस ret;
	पूर्ण

	/*
	 * Some controllers have unreliable Data Line Active
	 * bit क्रम commands with busy संकेत. This affects
	 * Command Inhibit (data) bit. Just ignore it since
	 * MMC core driver has alपढ़ोy polled card status
	 * with CMD13 after any command with busy siganl.
	 */
	अगर ((spec_reg == SDHCI_PRESENT_STATE) &&
	(esdhc->quirk_ignore_data_inhibit == true)) अणु
		ret = value & ~SDHCI_DATA_INHIBIT;
		वापस ret;
	पूर्ण

	ret = value;
	वापस ret;
पूर्ण

अटल u16 esdhc_पढ़ोw_fixup(काष्ठा sdhci_host *host,
				     पूर्णांक spec_reg, u32 value)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	u16 ret;
	पूर्णांक shअगरt = (spec_reg & 0x2) * 8;

	अगर (spec_reg == SDHCI_TRANSFER_MODE)
		वापस pltfm_host->xfer_mode_shaकरोw;

	अगर (spec_reg == SDHCI_HOST_VERSION)
		ret = value & 0xffff;
	अन्यथा
		ret = (value >> shअगरt) & 0xffff;
	/* Workaround क्रम T4240-R1.0-R2.0 eSDHC which has incorrect
	 * venकरोr version and spec version inक्रमmation.
	 */
	अगर ((spec_reg == SDHCI_HOST_VERSION) &&
	    (esdhc->quirk_incorrect_hostver))
		ret = (VENDOR_V_23 << SDHCI_VENDOR_VER_SHIFT) | SDHCI_SPEC_200;
	वापस ret;
पूर्ण

अटल u8 esdhc_पढ़ोb_fixup(काष्ठा sdhci_host *host,
				     पूर्णांक spec_reg, u32 value)
अणु
	u8 ret;
	u8 dma_bits;
	पूर्णांक shअगरt = (spec_reg & 0x3) * 8;

	ret = (value >> shअगरt) & 0xff;

	/*
	 * "DMA select" locates at offset 0x28 in SD specअगरication, but on
	 * P5020 or P3041, it locates at 0x29.
	 */
	अगर (spec_reg == SDHCI_HOST_CONTROL) अणु
		/* DMA select is 22,23 bits in Protocol Control Register */
		dma_bits = (value >> 5) & SDHCI_CTRL_DMA_MASK;
		/* fixup the result */
		ret &= ~SDHCI_CTRL_DMA_MASK;
		ret |= dma_bits;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * esdhc_ग_लिखो*_fixup - Fixup the SD spec रेजिस्टर value so that it could be
 *			written पूर्णांकo eSDHC रेजिस्टर.
 *
 * @host: poपूर्णांकer to sdhci_host
 * @spec_reg: SD spec रेजिस्टर address
 * @value: 8/16/32bit SD spec रेजिस्टर value that would be written
 * @old_value: 32bit eSDHC रेजिस्टर value on spec_reg address
 *
 * In SD spec, there are 8/16/32/64 bits रेजिस्टरs, जबतक all of eSDHC
 * रेजिस्टरs are 32 bits. There are dअगरferences in रेजिस्टर size, रेजिस्टर
 * address, रेजिस्टर function, bit position and function between eSDHC spec
 * and SD spec.
 *
 * Return a fixed up रेजिस्टर value
 */
अटल u32 esdhc_ग_लिखोl_fixup(काष्ठा sdhci_host *host,
				     पूर्णांक spec_reg, u32 value, u32 old_value)
अणु
	u32 ret;

	/*
	 * Enabling IRQSTATEN[BGESEN] is just to set IRQSTAT[BGE]
	 * when SYSCTL[RSTD] is set क्रम some special operations.
	 * No any impact on other operation.
	 */
	अगर (spec_reg == SDHCI_INT_ENABLE)
		ret = value | SDHCI_INT_BLK_GAP;
	अन्यथा
		ret = value;

	वापस ret;
पूर्ण

अटल u32 esdhc_ग_लिखोw_fixup(काष्ठा sdhci_host *host,
				     पूर्णांक spec_reg, u16 value, u32 old_value)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	पूर्णांक shअगरt = (spec_reg & 0x2) * 8;
	u32 ret;

	चयन (spec_reg) अणु
	हाल SDHCI_TRANSFER_MODE:
		/*
		 * Postpone this ग_लिखो, we must करो it together with a
		 * command ग_लिखो that is करोwn below. Return old value.
		 */
		pltfm_host->xfer_mode_shaकरोw = value;
		वापस old_value;
	हाल SDHCI_COMMAND:
		ret = (value << 16) | pltfm_host->xfer_mode_shaकरोw;
		वापस ret;
	पूर्ण

	ret = old_value & (~(0xffff << shअगरt));
	ret |= (value << shअगरt);

	अगर (spec_reg == SDHCI_BLOCK_SIZE) अणु
		/*
		 * Two last DMA bits are reserved, and first one is used क्रम
		 * non-standard blksz of 4096 bytes that we करोn't support
		 * yet. So clear the DMA boundary bits.
		 */
		ret &= (~SDHCI_MAKE_BLKSZ(0x7, 0));
	पूर्ण
	वापस ret;
पूर्ण

अटल u32 esdhc_ग_लिखोb_fixup(काष्ठा sdhci_host *host,
				     पूर्णांक spec_reg, u8 value, u32 old_value)
अणु
	u32 ret;
	u32 dma_bits;
	u8 पंचांगp;
	पूर्णांक shअगरt = (spec_reg & 0x3) * 8;

	/*
	 * eSDHC करोesn't have a standard घातer control रेजिस्टर, so we करो
	 * nothing here to aव्योम incorrect operation.
	 */
	अगर (spec_reg == SDHCI_POWER_CONTROL)
		वापस old_value;
	/*
	 * "DMA select" location is offset 0x28 in SD specअगरication, but on
	 * P5020 or P3041, it's located at 0x29.
	 */
	अगर (spec_reg == SDHCI_HOST_CONTROL) अणु
		/*
		 * If host control रेजिस्टर is not standard, निकास
		 * this function
		 */
		अगर (host->quirks2 & SDHCI_QUIRK2_BROKEN_HOST_CONTROL)
			वापस old_value;

		/* DMA select is 22,23 bits in Protocol Control Register */
		dma_bits = (value & SDHCI_CTRL_DMA_MASK) << 5;
		ret = (old_value & (~(SDHCI_CTRL_DMA_MASK << 5))) | dma_bits;
		पंचांगp = (value & (~SDHCI_CTRL_DMA_MASK)) |
		      (old_value & SDHCI_CTRL_DMA_MASK);
		ret = (ret & (~0xff)) | पंचांगp;

		/* Prevent SDHCI core from writing reserved bits (e.g. HISPD) */
		ret &= ~ESDHC_HOST_CONTROL_RES;
		वापस ret;
	पूर्ण

	ret = (old_value & (~(0xff << shअगरt))) | (value << shअगरt);
	वापस ret;
पूर्ण

अटल u32 esdhc_be_पढ़ोl(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u32 ret;
	u32 value;

	अगर (reg == SDHCI_CAPABILITIES_1)
		value = ioपढ़ो32be(host->ioaddr + ESDHC_CAPABILITIES_1);
	अन्यथा
		value = ioपढ़ो32be(host->ioaddr + reg);

	ret = esdhc_पढ़ोl_fixup(host, reg, value);

	वापस ret;
पूर्ण

अटल u32 esdhc_le_पढ़ोl(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u32 ret;
	u32 value;

	अगर (reg == SDHCI_CAPABILITIES_1)
		value = ioपढ़ो32(host->ioaddr + ESDHC_CAPABILITIES_1);
	अन्यथा
		value = ioपढ़ो32(host->ioaddr + reg);

	ret = esdhc_पढ़ोl_fixup(host, reg, value);

	वापस ret;
पूर्ण

अटल u16 esdhc_be_पढ़ोw(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u16 ret;
	u32 value;
	पूर्णांक base = reg & ~0x3;

	value = ioपढ़ो32be(host->ioaddr + base);
	ret = esdhc_पढ़ोw_fixup(host, reg, value);
	वापस ret;
पूर्ण

अटल u16 esdhc_le_पढ़ोw(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u16 ret;
	u32 value;
	पूर्णांक base = reg & ~0x3;

	value = ioपढ़ो32(host->ioaddr + base);
	ret = esdhc_पढ़ोw_fixup(host, reg, value);
	वापस ret;
पूर्ण

अटल u8 esdhc_be_पढ़ोb(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u8 ret;
	u32 value;
	पूर्णांक base = reg & ~0x3;

	value = ioपढ़ो32be(host->ioaddr + base);
	ret = esdhc_पढ़ोb_fixup(host, reg, value);
	वापस ret;
पूर्ण

अटल u8 esdhc_le_पढ़ोb(काष्ठा sdhci_host *host, पूर्णांक reg)
अणु
	u8 ret;
	u32 value;
	पूर्णांक base = reg & ~0x3;

	value = ioपढ़ो32(host->ioaddr + base);
	ret = esdhc_पढ़ोb_fixup(host, reg, value);
	वापस ret;
पूर्ण

अटल व्योम esdhc_be_ग_लिखोl(काष्ठा sdhci_host *host, u32 val, पूर्णांक reg)
अणु
	u32 value;

	value = esdhc_ग_लिखोl_fixup(host, reg, val, 0);
	ioग_लिखो32be(value, host->ioaddr + reg);
पूर्ण

अटल व्योम esdhc_le_ग_लिखोl(काष्ठा sdhci_host *host, u32 val, पूर्णांक reg)
अणु
	u32 value;

	value = esdhc_ग_लिखोl_fixup(host, reg, val, 0);
	ioग_लिखो32(value, host->ioaddr + reg);
पूर्ण

अटल व्योम esdhc_be_ग_लिखोw(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक base = reg & ~0x3;
	u32 value;
	u32 ret;

	value = ioपढ़ो32be(host->ioaddr + base);
	ret = esdhc_ग_लिखोw_fixup(host, reg, val, value);
	अगर (reg != SDHCI_TRANSFER_MODE)
		ioग_लिखो32be(ret, host->ioaddr + base);

	/* Starting SW tuning requires ESDHC_SMPCLKSEL to be set
	 * 1us later after ESDHC_EXTN is set.
	 */
	अगर (base == ESDHC_SYSTEM_CONTROL_2) अणु
		अगर (!(value & ESDHC_EXTN) && (ret & ESDHC_EXTN) &&
		    esdhc->in_sw_tuning) अणु
			udelay(1);
			ret |= ESDHC_SMPCLKSEL;
			ioग_लिखो32be(ret, host->ioaddr + base);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम esdhc_le_ग_लिखोw(काष्ठा sdhci_host *host, u16 val, पूर्णांक reg)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक base = reg & ~0x3;
	u32 value;
	u32 ret;

	value = ioपढ़ो32(host->ioaddr + base);
	ret = esdhc_ग_लिखोw_fixup(host, reg, val, value);
	अगर (reg != SDHCI_TRANSFER_MODE)
		ioग_लिखो32(ret, host->ioaddr + base);

	/* Starting SW tuning requires ESDHC_SMPCLKSEL to be set
	 * 1us later after ESDHC_EXTN is set.
	 */
	अगर (base == ESDHC_SYSTEM_CONTROL_2) अणु
		अगर (!(value & ESDHC_EXTN) && (ret & ESDHC_EXTN) &&
		    esdhc->in_sw_tuning) अणु
			udelay(1);
			ret |= ESDHC_SMPCLKSEL;
			ioग_लिखो32(ret, host->ioaddr + base);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम esdhc_be_ग_लिखोb(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg)
अणु
	पूर्णांक base = reg & ~0x3;
	u32 value;
	u32 ret;

	value = ioपढ़ो32be(host->ioaddr + base);
	ret = esdhc_ग_लिखोb_fixup(host, reg, val, value);
	ioग_लिखो32be(ret, host->ioaddr + base);
पूर्ण

अटल व्योम esdhc_le_ग_लिखोb(काष्ठा sdhci_host *host, u8 val, पूर्णांक reg)
अणु
	पूर्णांक base = reg & ~0x3;
	u32 value;
	u32 ret;

	value = ioपढ़ो32(host->ioaddr + base);
	ret = esdhc_ग_लिखोb_fixup(host, reg, val, value);
	ioग_लिखो32(ret, host->ioaddr + base);
पूर्ण

/*
 * For Abort or Suspend after Stop at Block Gap, ignore the ADMA
 * error(IRQSTAT[ADMAE]) अगर both Transfer Complete(IRQSTAT[TC])
 * and Block Gap Event(IRQSTAT[BGE]) are also set.
 * For Continue, apply soft reset क्रम data(SYSCTL[RSTD]);
 * and re-issue the entire पढ़ो transaction from beginning.
 */
अटल व्योम esdhc_of_adma_workaround(काष्ठा sdhci_host *host, u32 पूर्णांकmask)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	bool applicable;
	dma_addr_t dmastart;
	dma_addr_t dmanow;

	applicable = (पूर्णांकmask & SDHCI_INT_DATA_END) &&
		     (पूर्णांकmask & SDHCI_INT_BLK_GAP) &&
		     (esdhc->venकरोr_ver == VENDOR_V_23);
	अगर (!applicable)
		वापस;

	host->data->error = 0;
	dmastart = sg_dma_address(host->data->sg);
	dmanow = dmastart + host->data->bytes_xfered;
	/*
	 * Force update to the next DMA block boundary.
	 */
	dmanow = (dmanow & ~(SDHCI_DEFAULT_BOUNDARY_SIZE - 1)) +
		SDHCI_DEFAULT_BOUNDARY_SIZE;
	host->data->bytes_xfered = dmanow - dmastart;
	sdhci_ग_लिखोl(host, dmanow, SDHCI_DMA_ADDRESS);
पूर्ण

अटल पूर्णांक esdhc_of_enable_dma(काष्ठा sdhci_host *host)
अणु
	u32 value;
	काष्ठा device *dev = mmc_dev(host->mmc);

	अगर (of_device_is_compatible(dev->of_node, "fsl,ls1043a-esdhc") ||
	    of_device_is_compatible(dev->of_node, "fsl,ls1046a-esdhc"))
		dma_set_mask_and_coherent(dev, DMA_BIT_MASK(40));

	value = sdhci_पढ़ोl(host, ESDHC_DMA_SYSCTL);

	अगर (of_dma_is_coherent(dev->of_node))
		value |= ESDHC_DMA_SNOOP;
	अन्यथा
		value &= ~ESDHC_DMA_SNOOP;

	sdhci_ग_लिखोl(host, value, ESDHC_DMA_SYSCTL);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक esdhc_of_get_max_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);

	अगर (esdhc->peripheral_घड़ी)
		वापस esdhc->peripheral_घड़ी;
	अन्यथा
		वापस pltfm_host->घड़ी;
पूर्ण

अटल अचिन्हित पूर्णांक esdhc_of_get_min_घड़ी(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	अचिन्हित पूर्णांक घड़ी;

	अगर (esdhc->peripheral_घड़ी)
		घड़ी = esdhc->peripheral_घड़ी;
	अन्यथा
		घड़ी = pltfm_host->घड़ी;
	वापस घड़ी / 256 / 16;
पूर्ण

अटल व्योम esdhc_घड़ी_enable(काष्ठा sdhci_host *host, bool enable)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	kसमय_प्रकार समयout;
	u32 val, clk_en;

	clk_en = ESDHC_CLOCK_SDCLKEN;

	/*
	 * IPGEN/HCKEN/PEREN bits exist on eSDHC whose venकरोr version
	 * is 2.2 or lower.
	 */
	अगर (esdhc->venकरोr_ver <= VENDOR_V_22)
		clk_en |= (ESDHC_CLOCK_IPGEN | ESDHC_CLOCK_HCKEN |
			   ESDHC_CLOCK_PEREN);

	val = sdhci_पढ़ोl(host, ESDHC_SYSTEM_CONTROL);

	अगर (enable)
		val |= clk_en;
	अन्यथा
		val &= ~clk_en;

	sdhci_ग_लिखोl(host, val, ESDHC_SYSTEM_CONTROL);

	/*
	 * Wait max 20 ms. If venकरोr version is 2.2 or lower, करो not
	 * रुको घड़ी stable bit which करोes not exist.
	 */
	समयout = kसमय_add_ms(kसमय_get(), 20);
	जबतक (esdhc->venकरोr_ver > VENDOR_V_22) अणु
		bool समयकरोut = kसमय_after(kसमय_get(), समयout);

		अगर (sdhci_पढ़ोl(host, ESDHC_PRSSTAT) & ESDHC_CLOCK_STABLE)
			अवरोध;
		अगर (समयकरोut) अणु
			pr_err("%s: Internal clock never stabilised.\n",
				mmc_hostname(host->mmc));
			अवरोध;
		पूर्ण
		usleep_range(10, 20);
	पूर्ण
पूर्ण

अटल व्योम esdhc_flush_async_fअगरo(काष्ठा sdhci_host *host)
अणु
	kसमय_प्रकार समयout;
	u32 val;

	val = sdhci_पढ़ोl(host, ESDHC_DMA_SYSCTL);
	val |= ESDHC_FLUSH_ASYNC_FIFO;
	sdhci_ग_लिखोl(host, val, ESDHC_DMA_SYSCTL);

	/* Wait max 20 ms */
	समयout = kसमय_add_ms(kसमय_get(), 20);
	जबतक (1) अणु
		bool समयकरोut = kसमय_after(kसमय_get(), समयout);

		अगर (!(sdhci_पढ़ोl(host, ESDHC_DMA_SYSCTL) &
		      ESDHC_FLUSH_ASYNC_FIFO))
			अवरोध;
		अगर (समयकरोut) अणु
			pr_err("%s: flushing asynchronous FIFO timeout.\n",
				mmc_hostname(host->mmc));
			अवरोध;
		पूर्ण
		usleep_range(10, 20);
	पूर्ण
पूर्ण

अटल व्योम esdhc_of_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	अचिन्हित पूर्णांक pre_भाग = 1, भाग = 1;
	अचिन्हित पूर्णांक घड़ी_fixup = 0;
	kसमय_प्रकार समयout;
	u32 temp;

	अगर (घड़ी == 0) अणु
		host->mmc->actual_घड़ी = 0;
		esdhc_घड़ी_enable(host, false);
		वापस;
	पूर्ण

	/* Start pre_भाग at 2 क्रम venकरोr version < 2.3. */
	अगर (esdhc->venकरोr_ver < VENDOR_V_23)
		pre_भाग = 2;

	/* Fix घड़ी value. */
	अगर (host->mmc->card && mmc_card_sd(host->mmc->card) &&
	    esdhc->clk_fixup && host->mmc->ios.timing == MMC_TIMING_LEGACY)
		घड़ी_fixup = esdhc->clk_fixup->sd_dflt_max_clk;
	अन्यथा अगर (esdhc->clk_fixup)
		घड़ी_fixup = esdhc->clk_fixup->max_clk[host->mmc->ios.timing];

	अगर (घड़ी_fixup == 0 || घड़ी < घड़ी_fixup)
		घड़ी_fixup = घड़ी;

	/* Calculate pre_भाग and भाग. */
	जबतक (host->max_clk / pre_भाग / 16 > घड़ी_fixup && pre_भाग < 256)
		pre_भाग *= 2;

	जबतक (host->max_clk / pre_भाग / भाग > घड़ी_fixup && भाग < 16)
		भाग++;

	esdhc->भाग_ratio = pre_भाग * भाग;

	/* Limit घड़ी भागision क्रम HS400 200MHz घड़ी क्रम quirk. */
	अगर (esdhc->quirk_limited_clk_भागision &&
	    घड़ी == MMC_HS200_MAX_DTR &&
	    (host->mmc->ios.timing == MMC_TIMING_MMC_HS400 ||
	     host->flags & SDHCI_HS400_TUNING)) अणु
		अगर (esdhc->भाग_ratio <= 4) अणु
			pre_भाग = 4;
			भाग = 1;
		पूर्ण अन्यथा अगर (esdhc->भाग_ratio <= 8) अणु
			pre_भाग = 4;
			भाग = 2;
		पूर्ण अन्यथा अगर (esdhc->भाग_ratio <= 12) अणु
			pre_भाग = 4;
			भाग = 3;
		पूर्ण अन्यथा अणु
			pr_warn("%s: using unsupported clock division.\n",
				mmc_hostname(host->mmc));
		पूर्ण
		esdhc->भाग_ratio = pre_भाग * भाग;
	पूर्ण

	host->mmc->actual_घड़ी = host->max_clk / esdhc->भाग_ratio;

	dev_dbg(mmc_dev(host->mmc), "desired SD clock: %d, actual: %d\n",
		घड़ी, host->mmc->actual_घड़ी);

	/* Set घड़ी भागision पूर्णांकo रेजिस्टर. */
	pre_भाग >>= 1;
	भाग--;

	esdhc_घड़ी_enable(host, false);

	temp = sdhci_पढ़ोl(host, ESDHC_SYSTEM_CONTROL);
	temp &= ~ESDHC_CLOCK_MASK;
	temp |= ((भाग << ESDHC_DIVIDER_SHIFT) |
		(pre_भाग << ESDHC_PREDIV_SHIFT));
	sdhci_ग_लिखोl(host, temp, ESDHC_SYSTEM_CONTROL);

	/*
	 * Wait max 20 ms. If venकरोr version is 2.2 or lower, करो not
	 * रुको घड़ी stable bit which करोes not exist.
	 */
	समयout = kसमय_add_ms(kसमय_get(), 20);
	जबतक (esdhc->venकरोr_ver > VENDOR_V_22) अणु
		bool समयकरोut = kसमय_after(kसमय_get(), समयout);

		अगर (sdhci_पढ़ोl(host, ESDHC_PRSSTAT) & ESDHC_CLOCK_STABLE)
			अवरोध;
		अगर (समयकरोut) अणु
			pr_err("%s: Internal clock never stabilised.\n",
				mmc_hostname(host->mmc));
			अवरोध;
		पूर्ण
		usleep_range(10, 20);
	पूर्ण

	/* Additional setting क्रम HS400. */
	अगर (host->mmc->ios.timing == MMC_TIMING_MMC_HS400 &&
	    घड़ी == MMC_HS200_MAX_DTR) अणु
		temp = sdhci_पढ़ोl(host, ESDHC_TBCTL);
		sdhci_ग_लिखोl(host, temp | ESDHC_HS400_MODE, ESDHC_TBCTL);
		temp = sdhci_पढ़ोl(host, ESDHC_SDCLKCTL);
		sdhci_ग_लिखोl(host, temp | ESDHC_CMD_CLK_CTL, ESDHC_SDCLKCTL);
		esdhc_घड़ी_enable(host, true);

		temp = sdhci_पढ़ोl(host, ESDHC_DLLCFG0);
		temp |= ESDHC_DLL_ENABLE;
		अगर (host->mmc->actual_घड़ी == MMC_HS200_MAX_DTR)
			temp |= ESDHC_DLL_FREQ_SEL;
		sdhci_ग_लिखोl(host, temp, ESDHC_DLLCFG0);

		temp |= ESDHC_DLL_RESET;
		sdhci_ग_लिखोl(host, temp, ESDHC_DLLCFG0);
		udelay(1);
		temp &= ~ESDHC_DLL_RESET;
		sdhci_ग_लिखोl(host, temp, ESDHC_DLLCFG0);

		/* Wait max 20 ms */
		अगर (पढ़ो_poll_समयout(sdhci_पढ़ोl, temp,
				      temp & ESDHC_DLL_STS_SLV_LOCK,
				      10, 20000, false,
				      host, ESDHC_DLLSTAT0))
			pr_err("%s: timeout for delay chain lock.\n",
			       mmc_hostname(host->mmc));

		temp = sdhci_पढ़ोl(host, ESDHC_TBCTL);
		sdhci_ग_लिखोl(host, temp | ESDHC_HS400_WNDW_ADJUST, ESDHC_TBCTL);

		esdhc_घड़ी_enable(host, false);
		esdhc_flush_async_fअगरo(host);
	पूर्ण
	esdhc_घड़ी_enable(host, true);
पूर्ण

अटल व्योम esdhc_pltfm_set_bus_width(काष्ठा sdhci_host *host, पूर्णांक width)
अणु
	u32 ctrl;

	ctrl = sdhci_पढ़ोl(host, ESDHC_PROCTL);
	ctrl &= (~ESDHC_CTRL_BUSWIDTH_MASK);
	चयन (width) अणु
	हाल MMC_BUS_WIDTH_8:
		ctrl |= ESDHC_CTRL_8BITBUS;
		अवरोध;

	हाल MMC_BUS_WIDTH_4:
		ctrl |= ESDHC_CTRL_4BITBUS;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	sdhci_ग_लिखोl(host, ctrl, ESDHC_PROCTL);
पूर्ण

अटल व्योम esdhc_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	u32 val, bus_width = 0;

	/*
	 * Add delay to make sure all the DMA transfers are finished
	 * क्रम quirk.
	 */
	अगर (esdhc->quirk_delay_beक्रमe_data_reset &&
	    (mask & SDHCI_RESET_DATA) &&
	    (host->flags & SDHCI_REQ_USE_DMA))
		mdelay(5);

	/*
	 * Save bus-width क्रम eSDHC whose venकरोr version is 2.2
	 * or lower क्रम data reset.
	 */
	अगर ((mask & SDHCI_RESET_DATA) &&
	    (esdhc->venकरोr_ver <= VENDOR_V_22)) अणु
		val = sdhci_पढ़ोl(host, ESDHC_PROCTL);
		bus_width = val & ESDHC_CTRL_BUSWIDTH_MASK;
	पूर्ण

	sdhci_reset(host, mask);

	/*
	 * Restore bus-width setting and पूर्णांकerrupt रेजिस्टरs क्रम eSDHC
	 * whose venकरोr version is 2.2 or lower क्रम data reset.
	 */
	अगर ((mask & SDHCI_RESET_DATA) &&
	    (esdhc->venकरोr_ver <= VENDOR_V_22)) अणु
		val = sdhci_पढ़ोl(host, ESDHC_PROCTL);
		val &= ~ESDHC_CTRL_BUSWIDTH_MASK;
		val |= bus_width;
		sdhci_ग_लिखोl(host, val, ESDHC_PROCTL);

		sdhci_ग_लिखोl(host, host->ier, SDHCI_INT_ENABLE);
		sdhci_ग_लिखोl(host, host->ier, SDHCI_SIGNAL_ENABLE);
	पूर्ण

	/*
	 * Some bits have to be cleaned manually क्रम eSDHC whose spec
	 * version is higher than 3.0 क्रम all reset.
	 */
	अगर ((mask & SDHCI_RESET_ALL) &&
	    (esdhc->spec_ver >= SDHCI_SPEC_300)) अणु
		val = sdhci_पढ़ोl(host, ESDHC_TBCTL);
		val &= ~ESDHC_TB_EN;
		sdhci_ग_लिखोl(host, val, ESDHC_TBCTL);

		/*
		 * Initialize eSDHC_DLLCFG1[DLL_PD_PULSE_STRETCH_SEL] to
		 * 0 क्रम quirk.
		 */
		अगर (esdhc->quirk_unreliable_pulse_detection) अणु
			val = sdhci_पढ़ोl(host, ESDHC_DLLCFG1);
			val &= ~ESDHC_DLL_PD_PULSE_STRETCH_SEL;
			sdhci_ग_लिखोl(host, val, ESDHC_DLLCFG1);
		पूर्ण
	पूर्ण
पूर्ण

/* The SCFG, Supplemental Configuration Unit, provides SoC specअगरic
 * configuration and status रेजिस्टरs क्रम the device. There is a
 * SDHC IO VSEL control रेजिस्टर on SCFG क्रम some platक्रमms. It's
 * used to support SDHC IO voltage चयनing.
 */
अटल स्थिर काष्ठा of_device_id scfg_device_ids[] = अणु
	अणु .compatible = "fsl,t1040-scfg", पूर्ण,
	अणु .compatible = "fsl,ls1012a-scfg", पूर्ण,
	अणु .compatible = "fsl,ls1046a-scfg", पूर्ण,
	अणुपूर्ण
पूर्ण;

/* SDHC IO VSEL control रेजिस्टर definition */
#घोषणा SCFG_SDHCIOVSELCR	0x408
#घोषणा SDHCIOVSELCR_TGLEN	0x80000000
#घोषणा SDHCIOVSELCR_VSELVAL	0x60000000
#घोषणा SDHCIOVSELCR_SDHC_VS	0x00000001

अटल पूर्णांक esdhc_संकेत_voltage_चयन(काष्ठा mmc_host *mmc,
				       काष्ठा mmc_ios *ios)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा device_node *scfg_node;
	व्योम __iomem *scfg_base = शून्य;
	u32 sdhciovselcr;
	u32 val;

	/*
	 * Signal Voltage Switching is only applicable क्रम Host Controllers
	 * v3.00 and above.
	 */
	अगर (host->version < SDHCI_SPEC_300)
		वापस 0;

	val = sdhci_पढ़ोl(host, ESDHC_PROCTL);

	चयन (ios->संकेत_voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_330:
		val &= ~ESDHC_VOLT_SEL;
		sdhci_ग_लिखोl(host, val, ESDHC_PROCTL);
		वापस 0;
	हाल MMC_SIGNAL_VOLTAGE_180:
		scfg_node = of_find_matching_node(शून्य, scfg_device_ids);
		अगर (scfg_node)
			scfg_base = of_iomap(scfg_node, 0);
		अगर (scfg_base) अणु
			sdhciovselcr = SDHCIOVSELCR_TGLEN |
				       SDHCIOVSELCR_VSELVAL;
			ioग_लिखो32be(sdhciovselcr,
				scfg_base + SCFG_SDHCIOVSELCR);

			val |= ESDHC_VOLT_SEL;
			sdhci_ग_लिखोl(host, val, ESDHC_PROCTL);
			mdelay(5);

			sdhciovselcr = SDHCIOVSELCR_TGLEN |
				       SDHCIOVSELCR_SDHC_VS;
			ioग_लिखो32be(sdhciovselcr,
				scfg_base + SCFG_SDHCIOVSELCR);
			iounmap(scfg_base);
		पूर्ण अन्यथा अणु
			val |= ESDHC_VOLT_SEL;
			sdhci_ग_लिखोl(host, val, ESDHC_PROCTL);
		पूर्ण
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा soc_device_attribute soc_tuning_erratum_type1[] = अणु
	अणु .family = "QorIQ T1023", पूर्ण,
	अणु .family = "QorIQ T1040", पूर्ण,
	अणु .family = "QorIQ T2080", पूर्ण,
	अणु .family = "QorIQ LS1021A", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा soc_device_attribute soc_tuning_erratum_type2[] = अणु
	अणु .family = "QorIQ LS1012A", पूर्ण,
	अणु .family = "QorIQ LS1043A", पूर्ण,
	अणु .family = "QorIQ LS1046A", पूर्ण,
	अणु .family = "QorIQ LS1080A", पूर्ण,
	अणु .family = "QorIQ LS2080A", पूर्ण,
	अणु .family = "QorIQ LA1575A", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम esdhc_tuning_block_enable(काष्ठा sdhci_host *host, bool enable)
अणु
	u32 val;

	esdhc_घड़ी_enable(host, false);
	esdhc_flush_async_fअगरo(host);

	val = sdhci_पढ़ोl(host, ESDHC_TBCTL);
	अगर (enable)
		val |= ESDHC_TB_EN;
	अन्यथा
		val &= ~ESDHC_TB_EN;
	sdhci_ग_लिखोl(host, val, ESDHC_TBCTL);

	esdhc_घड़ी_enable(host, true);
पूर्ण

अटल व्योम esdhc_tuning_winकरोw_ptr(काष्ठा sdhci_host *host, u8 *winकरोw_start,
				    u8 *winकरोw_end)
अणु
	u32 val;

	/* Write TBCTL[11:8]=4'h8 */
	val = sdhci_पढ़ोl(host, ESDHC_TBCTL);
	val &= ~(0xf << 8);
	val |= 8 << 8;
	sdhci_ग_लिखोl(host, val, ESDHC_TBCTL);

	mdelay(1);

	/* Read TBCTL[31:0] रेजिस्टर and reग_लिखो again */
	val = sdhci_पढ़ोl(host, ESDHC_TBCTL);
	sdhci_ग_लिखोl(host, val, ESDHC_TBCTL);

	mdelay(1);

	/* Read the TBSTAT[31:0] रेजिस्टर twice */
	val = sdhci_पढ़ोl(host, ESDHC_TBSTAT);
	val = sdhci_पढ़ोl(host, ESDHC_TBSTAT);

	*winकरोw_end = val & 0xff;
	*winकरोw_start = (val >> 8) & 0xff;
पूर्ण

अटल व्योम esdhc_prepare_sw_tuning(काष्ठा sdhci_host *host, u8 *winकरोw_start,
				    u8 *winकरोw_end)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	u8 start_ptr, end_ptr;

	अगर (esdhc->quirk_tuning_erratum_type1) अणु
		*winकरोw_start = 5 * esdhc->भाग_ratio;
		*winकरोw_end = 3 * esdhc->भाग_ratio;
		वापस;
	पूर्ण

	esdhc_tuning_winकरोw_ptr(host, &start_ptr, &end_ptr);

	/* Reset data lines by setting ESDHCCTL[RSTD] */
	sdhci_reset(host, SDHCI_RESET_DATA);
	/* Write 32'hFFFF_FFFF to IRQSTAT रेजिस्टर */
	sdhci_ग_लिखोl(host, 0xFFFFFFFF, SDHCI_INT_STATUS);

	/* If TBSTAT[15:8]-TBSTAT[7:0] > (4 * भाग_ratio) + 2
	 * or TBSTAT[7:0]-TBSTAT[15:8] > (4 * भाग_ratio) + 2,
	 * then program TBPTR[TB_WNDW_END_PTR] = 4 * भाग_ratio
	 * and program TBPTR[TB_WNDW_START_PTR] = 8 * भाग_ratio.
	 */

	अगर (असल(start_ptr - end_ptr) > (4 * esdhc->भाग_ratio + 2)) अणु
		*winकरोw_start = 8 * esdhc->भाग_ratio;
		*winकरोw_end = 4 * esdhc->भाग_ratio;
	पूर्ण अन्यथा अणु
		*winकरोw_start = 5 * esdhc->भाग_ratio;
		*winकरोw_end = 3 * esdhc->भाग_ratio;
	पूर्ण
पूर्ण

अटल पूर्णांक esdhc_execute_sw_tuning(काष्ठा mmc_host *mmc, u32 opcode,
				   u8 winकरोw_start, u8 winकरोw_end)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	u32 val;
	पूर्णांक ret;

	/* Program TBPTR[TB_WNDW_END_PTR] and TBPTR[TB_WNDW_START_PTR] */
	val = ((u32)winकरोw_start << ESDHC_WNDW_STRT_PTR_SHIFT) &
	      ESDHC_WNDW_STRT_PTR_MASK;
	val |= winकरोw_end & ESDHC_WNDW_END_PTR_MASK;
	sdhci_ग_लिखोl(host, val, ESDHC_TBPTR);

	/* Program the software tuning mode by setting TBCTL[TB_MODE]=2'h3 */
	val = sdhci_पढ़ोl(host, ESDHC_TBCTL);
	val &= ~ESDHC_TB_MODE_MASK;
	val |= ESDHC_TB_MODE_SW;
	sdhci_ग_लिखोl(host, val, ESDHC_TBCTL);

	esdhc->in_sw_tuning = true;
	ret = sdhci_execute_tuning(mmc, opcode);
	esdhc->in_sw_tuning = false;
	वापस ret;
पूर्ण

अटल पूर्णांक esdhc_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	u8 winकरोw_start, winकरोw_end;
	पूर्णांक ret, retries = 1;
	bool hs400_tuning;
	अचिन्हित पूर्णांक clk;
	u32 val;

	/* For tuning mode, the sd घड़ी भागisor value
	 * must be larger than 3 according to reference manual.
	 */
	clk = esdhc->peripheral_घड़ी / 3;
	अगर (host->घड़ी > clk)
		esdhc_of_set_घड़ी(host, clk);

	esdhc_tuning_block_enable(host, true);

	/*
	 * The eSDHC controller takes the data समयout value पूर्णांकo account
	 * during tuning. If the SD card is too slow sending the response, the
	 * समयr will expire and a "Buffer Read Ready" पूर्णांकerrupt without data
	 * is triggered. This leads to tuning errors.
	 *
	 * Just set the समयout to the maximum value because the core will
	 * alपढ़ोy take care of it in sdhci_send_tuning().
	 */
	sdhci_ग_लिखोb(host, 0xe, SDHCI_TIMEOUT_CONTROL);

	hs400_tuning = host->flags & SDHCI_HS400_TUNING;

	करो अणु
		अगर (esdhc->quirk_limited_clk_भागision &&
		    hs400_tuning)
			esdhc_of_set_घड़ी(host, host->घड़ी);

		/* Do HW tuning */
		val = sdhci_पढ़ोl(host, ESDHC_TBCTL);
		val &= ~ESDHC_TB_MODE_MASK;
		val |= ESDHC_TB_MODE_3;
		sdhci_ग_लिखोl(host, val, ESDHC_TBCTL);

		ret = sdhci_execute_tuning(mmc, opcode);
		अगर (ret)
			अवरोध;

		/* For type2 affected platक्रमms of the tuning erratum,
		 * tuning may succeed although eSDHC might not have
		 * tuned properly. Need to check tuning winकरोw.
		 */
		अगर (esdhc->quirk_tuning_erratum_type2 &&
		    !host->tuning_err) अणु
			esdhc_tuning_winकरोw_ptr(host, &winकरोw_start,
						&winकरोw_end);
			अगर (असल(winकरोw_start - winकरोw_end) >
			    (4 * esdhc->भाग_ratio + 2))
				host->tuning_err = -EAGAIN;
		पूर्ण

		/* If HW tuning fails and triggers erratum,
		 * try workaround.
		 */
		ret = host->tuning_err;
		अगर (ret == -EAGAIN &&
		    (esdhc->quirk_tuning_erratum_type1 ||
		     esdhc->quirk_tuning_erratum_type2)) अणु
			/* Recover HS400 tuning flag */
			अगर (hs400_tuning)
				host->flags |= SDHCI_HS400_TUNING;
			pr_info("%s: Hold on to use fixed sampling clock. Try SW tuning!\n",
				mmc_hostname(mmc));
			/* Do SW tuning */
			esdhc_prepare_sw_tuning(host, &winकरोw_start,
						&winकरोw_end);
			ret = esdhc_execute_sw_tuning(mmc, opcode,
						      winकरोw_start,
						      winकरोw_end);
			अगर (ret)
				अवरोध;

			/* Retry both HW/SW tuning with reduced घड़ी. */
			ret = host->tuning_err;
			अगर (ret == -EAGAIN && retries) अणु
				/* Recover HS400 tuning flag */
				अगर (hs400_tuning)
					host->flags |= SDHCI_HS400_TUNING;

				clk = host->max_clk / (esdhc->भाग_ratio + 1);
				esdhc_of_set_घड़ी(host, clk);
				pr_info("%s: Hold on to use fixed sampling clock. Try tuning with reduced clock!\n",
					mmc_hostname(mmc));
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण जबतक (retries--);

	अगर (ret) अणु
		esdhc_tuning_block_enable(host, false);
	पूर्ण अन्यथा अगर (hs400_tuning) अणु
		val = sdhci_पढ़ोl(host, ESDHC_SDTIMNGCTL);
		val |= ESDHC_FLW_CTL_BG;
		sdhci_ग_लिखोl(host, val, ESDHC_SDTIMNGCTL);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम esdhc_set_uhs_संकेतing(काष्ठा sdhci_host *host,
				   अचिन्हित पूर्णांक timing)
अणु
	u32 val;

	/*
	 * There are specअगरic रेजिस्टरs setting क्रम HS400 mode.
	 * Clean all of them अगर controller is in HS400 mode to
	 * निकास HS400 mode beक्रमe re-setting any speed mode.
	 */
	val = sdhci_पढ़ोl(host, ESDHC_TBCTL);
	अगर (val & ESDHC_HS400_MODE) अणु
		val = sdhci_पढ़ोl(host, ESDHC_SDTIMNGCTL);
		val &= ~ESDHC_FLW_CTL_BG;
		sdhci_ग_लिखोl(host, val, ESDHC_SDTIMNGCTL);

		val = sdhci_पढ़ोl(host, ESDHC_SDCLKCTL);
		val &= ~ESDHC_CMD_CLK_CTL;
		sdhci_ग_लिखोl(host, val, ESDHC_SDCLKCTL);

		esdhc_घड़ी_enable(host, false);
		val = sdhci_पढ़ोl(host, ESDHC_TBCTL);
		val &= ~ESDHC_HS400_MODE;
		sdhci_ग_लिखोl(host, val, ESDHC_TBCTL);
		esdhc_घड़ी_enable(host, true);

		val = sdhci_पढ़ोl(host, ESDHC_DLLCFG0);
		val &= ~(ESDHC_DLL_ENABLE | ESDHC_DLL_FREQ_SEL);
		sdhci_ग_लिखोl(host, val, ESDHC_DLLCFG0);

		val = sdhci_पढ़ोl(host, ESDHC_TBCTL);
		val &= ~ESDHC_HS400_WNDW_ADJUST;
		sdhci_ग_लिखोl(host, val, ESDHC_TBCTL);

		esdhc_tuning_block_enable(host, false);
	पूर्ण

	अगर (timing == MMC_TIMING_MMC_HS400)
		esdhc_tuning_block_enable(host, true);
	अन्यथा
		sdhci_set_uhs_संकेतing(host, timing);
पूर्ण

अटल u32 esdhc_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_esdhc *esdhc = sdhci_pltfm_priv(pltfm_host);
	u32 command;

	अगर (esdhc->quirk_trans_complete_erratum) अणु
		command = SDHCI_GET_CMD(sdhci_पढ़ोw(host,
					SDHCI_COMMAND));
		अगर (command == MMC_WRITE_MULTIPLE_BLOCK &&
				sdhci_पढ़ोw(host, SDHCI_BLOCK_COUNT) &&
				पूर्णांकmask & SDHCI_INT_DATA_END) अणु
			पूर्णांकmask &= ~SDHCI_INT_DATA_END;
			sdhci_ग_लिखोl(host, SDHCI_INT_DATA_END,
					SDHCI_INT_STATUS);
		पूर्ण
	पूर्ण
	वापस पूर्णांकmask;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल u32 esdhc_proctl;
अटल पूर्णांक esdhc_of_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);

	esdhc_proctl = sdhci_पढ़ोl(host, SDHCI_HOST_CONTROL);

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	वापस sdhci_suspend_host(host);
पूर्ण

अटल पूर्णांक esdhc_of_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	पूर्णांक ret = sdhci_resume_host(host);

	अगर (ret == 0) अणु
		/* Isn't this alपढ़ोy करोne by sdhci_resume_host() ? --rmk */
		esdhc_of_enable_dma(host);
		sdhci_ग_लिखोl(host, esdhc_proctl, SDHCI_HOST_CONTROL);
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(esdhc_of_dev_pm_ops,
			esdhc_of_suspend,
			esdhc_of_resume);

अटल स्थिर काष्ठा sdhci_ops sdhci_esdhc_be_ops = अणु
	.पढ़ो_l = esdhc_be_पढ़ोl,
	.पढ़ो_w = esdhc_be_पढ़ोw,
	.पढ़ो_b = esdhc_be_पढ़ोb,
	.ग_लिखो_l = esdhc_be_ग_लिखोl,
	.ग_लिखो_w = esdhc_be_ग_लिखोw,
	.ग_लिखो_b = esdhc_be_ग_लिखोb,
	.set_घड़ी = esdhc_of_set_घड़ी,
	.enable_dma = esdhc_of_enable_dma,
	.get_max_घड़ी = esdhc_of_get_max_घड़ी,
	.get_min_घड़ी = esdhc_of_get_min_घड़ी,
	.adma_workaround = esdhc_of_adma_workaround,
	.set_bus_width = esdhc_pltfm_set_bus_width,
	.reset = esdhc_reset,
	.set_uhs_संकेतing = esdhc_set_uhs_संकेतing,
	.irq = esdhc_irq,
पूर्ण;

अटल स्थिर काष्ठा sdhci_ops sdhci_esdhc_le_ops = अणु
	.पढ़ो_l = esdhc_le_पढ़ोl,
	.पढ़ो_w = esdhc_le_पढ़ोw,
	.पढ़ो_b = esdhc_le_पढ़ोb,
	.ग_लिखो_l = esdhc_le_ग_लिखोl,
	.ग_लिखो_w = esdhc_le_ग_लिखोw,
	.ग_लिखो_b = esdhc_le_ग_लिखोb,
	.set_घड़ी = esdhc_of_set_घड़ी,
	.enable_dma = esdhc_of_enable_dma,
	.get_max_घड़ी = esdhc_of_get_max_घड़ी,
	.get_min_घड़ी = esdhc_of_get_min_घड़ी,
	.adma_workaround = esdhc_of_adma_workaround,
	.set_bus_width = esdhc_pltfm_set_bus_width,
	.reset = esdhc_reset,
	.set_uhs_संकेतing = esdhc_set_uhs_संकेतing,
	.irq = esdhc_irq,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_esdhc_be_pdata = अणु
	.quirks = ESDHC_DEFAULT_QUIRKS |
#अगर_घोषित CONFIG_PPC
		  SDHCI_QUIRK_BROKEN_CARD_DETECTION |
#पूर्ण_अगर
		  SDHCI_QUIRK_NO_CARD_NO_RESET |
		  SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC,
	.ops = &sdhci_esdhc_be_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_esdhc_le_pdata = अणु
	.quirks = ESDHC_DEFAULT_QUIRKS |
		  SDHCI_QUIRK_NO_CARD_NO_RESET |
		  SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC,
	.ops = &sdhci_esdhc_le_ops,
पूर्ण;

अटल काष्ठा soc_device_attribute soc_incorrect_hostver[] = अणु
	अणु .family = "QorIQ T4240", .revision = "1.0", पूर्ण,
	अणु .family = "QorIQ T4240", .revision = "2.0", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा soc_device_attribute soc_fixup_sdhc_clkभागs[] = अणु
	अणु .family = "QorIQ LX2160A", .revision = "1.0", पूर्ण,
	अणु .family = "QorIQ LX2160A", .revision = "2.0", पूर्ण,
	अणु .family = "QorIQ LS1028A", .revision = "1.0", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा soc_device_attribute soc_unreliable_pulse_detection[] = अणु
	अणु .family = "QorIQ LX2160A", .revision = "1.0", पूर्ण,
	अणु .family = "QorIQ LX2160A", .revision = "2.0", पूर्ण,
	अणु .family = "QorIQ LS1028A", .revision = "1.0", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम esdhc_init(काष्ठा platक्रमm_device *pdev, काष्ठा sdhci_host *host)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_esdhc *esdhc;
	काष्ठा device_node *np;
	काष्ठा clk *clk;
	u32 val;
	u16 host_ver;

	pltfm_host = sdhci_priv(host);
	esdhc = sdhci_pltfm_priv(pltfm_host);

	host_ver = sdhci_पढ़ोw(host, SDHCI_HOST_VERSION);
	esdhc->venकरोr_ver = (host_ver & SDHCI_VENDOR_VER_MASK) >>
			     SDHCI_VENDOR_VER_SHIFT;
	esdhc->spec_ver = host_ver & SDHCI_SPEC_VER_MASK;
	अगर (soc_device_match(soc_incorrect_hostver))
		esdhc->quirk_incorrect_hostver = true;
	अन्यथा
		esdhc->quirk_incorrect_hostver = false;

	अगर (soc_device_match(soc_fixup_sdhc_clkभागs))
		esdhc->quirk_limited_clk_भागision = true;
	अन्यथा
		esdhc->quirk_limited_clk_भागision = false;

	अगर (soc_device_match(soc_unreliable_pulse_detection))
		esdhc->quirk_unreliable_pulse_detection = true;
	अन्यथा
		esdhc->quirk_unreliable_pulse_detection = false;

	match = of_match_node(sdhci_esdhc_of_match, pdev->dev.of_node);
	अगर (match)
		esdhc->clk_fixup = match->data;
	np = pdev->dev.of_node;

	अगर (of_device_is_compatible(np, "fsl,p2020-esdhc")) अणु
		esdhc->quirk_delay_beक्रमe_data_reset = true;
		esdhc->quirk_trans_complete_erratum = true;
	पूर्ण

	clk = of_clk_get(np, 0);
	अगर (!IS_ERR(clk)) अणु
		/*
		 * esdhc->peripheral_घड़ी would be asचिन्हित with a value
		 * which is eSDHC base घड़ी when use periperal घड़ी.
		 * For some platक्रमms, the घड़ी value got by common clk
		 * API is peripheral घड़ी जबतक the eSDHC base घड़ी is
		 * 1/2 peripheral घड़ी.
		 */
		अगर (of_device_is_compatible(np, "fsl,ls1046a-esdhc") ||
		    of_device_is_compatible(np, "fsl,ls1028a-esdhc") ||
		    of_device_is_compatible(np, "fsl,ls1088a-esdhc"))
			esdhc->peripheral_घड़ी = clk_get_rate(clk) / 2;
		अन्यथा
			esdhc->peripheral_घड़ी = clk_get_rate(clk);

		clk_put(clk);
	पूर्ण

	esdhc_घड़ी_enable(host, false);
	val = sdhci_पढ़ोl(host, ESDHC_DMA_SYSCTL);
	/*
	 * This bit is not able to be reset by SDHCI_RESET_ALL. Need to
	 * initialize it as 1 or 0 once, to override the dअगरferent value
	 * which may be configured in bootloader.
	 */
	अगर (esdhc->peripheral_घड़ी)
		val |= ESDHC_PERIPHERAL_CLK_SEL;
	अन्यथा
		val &= ~ESDHC_PERIPHERAL_CLK_SEL;
	sdhci_ग_लिखोl(host, val, ESDHC_DMA_SYSCTL);
	esdhc_घड़ी_enable(host, true);
पूर्ण

अटल पूर्णांक esdhc_hs400_prepare_ddr(काष्ठा mmc_host *mmc)
अणु
	esdhc_tuning_block_enable(mmc_priv(mmc), false);
	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_esdhc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sdhci_host *host;
	काष्ठा device_node *np;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा sdhci_esdhc *esdhc;
	पूर्णांक ret;

	np = pdev->dev.of_node;

	अगर (of_property_पढ़ो_bool(np, "little-endian"))
		host = sdhci_pltfm_init(pdev, &sdhci_esdhc_le_pdata,
					माप(काष्ठा sdhci_esdhc));
	अन्यथा
		host = sdhci_pltfm_init(pdev, &sdhci_esdhc_be_pdata,
					माप(काष्ठा sdhci_esdhc));

	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	host->mmc_host_ops.start_संकेत_voltage_चयन =
		esdhc_संकेत_voltage_चयन;
	host->mmc_host_ops.execute_tuning = esdhc_execute_tuning;
	host->mmc_host_ops.hs400_prepare_ddr = esdhc_hs400_prepare_ddr;
	host->tuning_delay = 1;

	esdhc_init(pdev, host);

	sdhci_get_of_property(pdev);

	pltfm_host = sdhci_priv(host);
	esdhc = sdhci_pltfm_priv(pltfm_host);
	अगर (soc_device_match(soc_tuning_erratum_type1))
		esdhc->quirk_tuning_erratum_type1 = true;
	अन्यथा
		esdhc->quirk_tuning_erratum_type1 = false;

	अगर (soc_device_match(soc_tuning_erratum_type2))
		esdhc->quirk_tuning_erratum_type2 = true;
	अन्यथा
		esdhc->quirk_tuning_erratum_type2 = false;

	अगर (esdhc->venकरोr_ver == VENDOR_V_22)
		host->quirks2 |= SDHCI_QUIRK2_HOST_NO_CMD23;

	अगर (esdhc->venकरोr_ver > VENDOR_V_22)
		host->quirks &= ~SDHCI_QUIRK_NO_BUSY_IRQ;

	अगर (of_find_compatible_node(शून्य, शून्य, "fsl,p2020-esdhc")) अणु
		host->quirks |= SDHCI_QUIRK_RESET_AFTER_REQUEST;
		host->quirks |= SDHCI_QUIRK_BROKEN_TIMEOUT_VAL;
	पूर्ण

	अगर (of_device_is_compatible(np, "fsl,p5040-esdhc") ||
	    of_device_is_compatible(np, "fsl,p5020-esdhc") ||
	    of_device_is_compatible(np, "fsl,p4080-esdhc") ||
	    of_device_is_compatible(np, "fsl,p1020-esdhc") ||
	    of_device_is_compatible(np, "fsl,t1040-esdhc"))
		host->quirks &= ~SDHCI_QUIRK_BROKEN_CARD_DETECTION;

	अगर (of_device_is_compatible(np, "fsl,ls1021a-esdhc"))
		host->quirks |= SDHCI_QUIRK_BROKEN_TIMEOUT_VAL;

	esdhc->quirk_ignore_data_inhibit = false;
	अगर (of_device_is_compatible(np, "fsl,p2020-esdhc")) अणु
		/*
		 * Freescale messed up with P2020 as it has a non-standard
		 * host control रेजिस्टर
		 */
		host->quirks2 |= SDHCI_QUIRK2_BROKEN_HOST_CONTROL;
		esdhc->quirk_ignore_data_inhibit = true;
	पूर्ण

	/* call to generic mmc_of_parse to support additional capabilities */
	ret = mmc_of_parse(host->mmc);
	अगर (ret)
		जाओ err;

	mmc_of_parse_voltage(host->mmc, &host->ocr_mask);

	ret = sdhci_add_host(host);
	अगर (ret)
		जाओ err;

	वापस 0;
 err:
	sdhci_pltfm_मुक्त(pdev);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver sdhci_esdhc_driver = अणु
	.driver = अणु
		.name = "sdhci-esdhc",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = sdhci_esdhc_of_match,
		.pm = &esdhc_of_dev_pm_ops,
	पूर्ण,
	.probe = sdhci_esdhc_probe,
	.हटाओ = sdhci_pltfm_unरेजिस्टर,
पूर्ण;

module_platक्रमm_driver(sdhci_esdhc_driver);

MODULE_DESCRIPTION("SDHCI OF driver for Freescale MPC eSDHC");
MODULE_AUTHOR("Xiaobo Xie <X.Xie@freescale.com>, "
	      "Anton Vorontsov <avorontsov@ru.mvista.com>");
MODULE_LICENSE("GPL v2");
