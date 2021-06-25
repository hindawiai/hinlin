<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Arasan Secure Digital Host Controller Interface.
 * Copyright (C) 2011 - 2012 Michal Simek <monstr@monstr.eu>
 * Copyright (c) 2012 Wind River Systems, Inc.
 * Copyright (C) 2013 Pengutronix e.K.
 * Copyright (C) 2013 Xilinx Inc.
 *
 * Based on sdhci-of-esdhc.c
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 * Copyright (c) 2009 MontaVista Software, Inc.
 *
 * Authors: Xiaobo Xie <X.Xie@मुक्तscale.com>
 *	    Anton Vorontsov <avorontsov@ru.mvista.com>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/of.h>
#समावेश <linux/firmware/xlnx-zynqmp.h>

#समावेश "cqhci.h"
#समावेश "sdhci-pltfm.h"

#घोषणा SDHCI_ARASAN_VENDOR_REGISTER	0x78

#घोषणा SDHCI_ARASAN_ITAPDLY_REGISTER	0xF0F8
#घोषणा SDHCI_ARASAN_ITAPDLY_SEL_MASK	0xFF

#घोषणा SDHCI_ARASAN_OTAPDLY_REGISTER	0xF0FC
#घोषणा SDHCI_ARASAN_OTAPDLY_SEL_MASK	0x3F

#घोषणा SDHCI_ARASAN_CQE_BASE_ADDR	0x200
#घोषणा VENDOR_ENHANCED_STROBE		BIT(0)

#घोषणा PHY_CLK_TOO_SLOW_HZ		400000

#घोषणा SDHCI_ITAPDLY_CHGWIN		0x200
#घोषणा SDHCI_ITAPDLY_ENABLE		0x100
#घोषणा SDHCI_OTAPDLY_ENABLE		0x40

/* Default settings क्रम ZynqMP Clock Phases */
#घोषणा ZYNQMP_ICLK_PHASE अणु0, 63, 63, 0, 63,  0,   0, 183, 54,  0, 0पूर्ण
#घोषणा ZYNQMP_OCLK_PHASE अणु0, 72, 60, 0, 60, 72, 135, 48, 72, 135, 0पूर्ण

#घोषणा VERSAL_ICLK_PHASE अणु0, 132, 132, 0, 132, 0, 0, 162, 90, 0, 0पूर्ण
#घोषणा VERSAL_OCLK_PHASE अणु0,  60, 48, 0, 48, 72, 90, 36, 60, 90, 0पूर्ण

/*
 * On some SoCs the syscon area has a feature where the upper 16-bits of
 * each 32-bit रेजिस्टर act as a ग_लिखो mask क्रम the lower 16-bits.  This allows
 * atomic updates of the रेजिस्टर without locking.  This macro is used on SoCs
 * that have that feature.
 */
#घोषणा HIWORD_UPDATE(val, mask, shअगरt) \
		((val) << (shअगरt) | (mask) << ((shअगरt) + 16))

/**
 * काष्ठा sdhci_arasan_soc_ctl_field - Field used in sdhci_arasan_soc_ctl_map
 *
 * @reg:	Offset within the syscon of the रेजिस्टर containing this field
 * @width:	Number of bits क्रम this field
 * @shअगरt:	Bit offset within @reg of this field (or -1 अगर not avail)
 */
काष्ठा sdhci_arasan_soc_ctl_field अणु
	u32 reg;
	u16 width;
	s16 shअगरt;
पूर्ण;

/**
 * काष्ठा sdhci_arasan_soc_ctl_map - Map in syscon to corecfg रेजिस्टरs
 *
 * @baseclkfreq:	Where to find corecfg_baseclkfreq
 * @घड़ीmultiplier:	Where to find corecfg_घड़ीmultiplier
 * @support64b:		Where to find SUPPORT64B bit
 * @hiword_update:	If true, use HIWORD_UPDATE to access the syscon
 *
 * It's up to the licensee of the Arsan IP block to make these available
 * somewhere अगर needed.  Presumably these will be scattered somewhere that's
 * accessible via the syscon API.
 */
काष्ठा sdhci_arasan_soc_ctl_map अणु
	काष्ठा sdhci_arasan_soc_ctl_field	baseclkfreq;
	काष्ठा sdhci_arasan_soc_ctl_field	घड़ीmultiplier;
	काष्ठा sdhci_arasan_soc_ctl_field	support64b;
	bool					hiword_update;
पूर्ण;

/**
 * काष्ठा sdhci_arasan_clk_ops - Clock Operations क्रम Arasan SD controller
 *
 * @sdcardclk_ops:	The output घड़ी related operations
 * @sampleclk_ops:	The sample घड़ी related operations
 */
काष्ठा sdhci_arasan_clk_ops अणु
	स्थिर काष्ठा clk_ops *sdcardclk_ops;
	स्थिर काष्ठा clk_ops *sampleclk_ops;
पूर्ण;

/**
 * काष्ठा sdhci_arasan_clk_data - Arasan Controller Clock Data.
 *
 * @sdcardclk_hw:	Struct क्रम the घड़ी we might provide to a PHY.
 * @sdcardclk:		Poपूर्णांकer to normal 'struct clock' क्रम sdcardclk_hw.
 * @sampleclk_hw:	Struct क्रम the घड़ी we might provide to a PHY.
 * @sampleclk:		Poपूर्णांकer to normal 'struct clock' क्रम sampleclk_hw.
 * @clk_phase_in:	Array of Input Clock Phase Delays क्रम all speed modes
 * @clk_phase_out:	Array of Output Clock Phase Delays क्रम all speed modes
 * @set_clk_delays:	Function poपूर्णांकer क्रम setting Clock Delays
 * @clk_of_data:	Platक्रमm specअगरic runसमय घड़ी data storage poपूर्णांकer
 */
काष्ठा sdhci_arasan_clk_data अणु
	काष्ठा clk_hw	sdcardclk_hw;
	काष्ठा clk      *sdcardclk;
	काष्ठा clk_hw	sampleclk_hw;
	काष्ठा clk      *sampleclk;
	पूर्णांक		clk_phase_in[MMC_TIMING_MMC_HS400 + 1];
	पूर्णांक		clk_phase_out[MMC_TIMING_MMC_HS400 + 1];
	व्योम		(*set_clk_delays)(काष्ठा sdhci_host *host);
	व्योम		*clk_of_data;
पूर्ण;

/**
 * काष्ठा sdhci_arasan_data - Arasan Controller Data
 *
 * @host:		Poपूर्णांकer to the मुख्य SDHCI host काष्ठाure.
 * @clk_ahb:		Poपूर्णांकer to the AHB घड़ी
 * @phy:		Poपूर्णांकer to the generic phy
 * @is_phy_on:		True अगर the PHY is on; false अगर not.
 * @has_cqe:		True अगर controller has command queuing engine.
 * @clk_data:		Struct क्रम the Arasan Controller Clock Data.
 * @clk_ops:		Struct क्रम the Arasan Controller Clock Operations.
 * @soc_ctl_base:	Poपूर्णांकer to regmap क्रम syscon क्रम soc_ctl रेजिस्टरs.
 * @soc_ctl_map:	Map to get offsets पूर्णांकo soc_ctl रेजिस्टरs.
 * @quirks:		Arasan deviations from spec.
 */
काष्ठा sdhci_arasan_data अणु
	काष्ठा sdhci_host *host;
	काष्ठा clk	*clk_ahb;
	काष्ठा phy	*phy;
	bool		is_phy_on;

	bool		has_cqe;
	काष्ठा sdhci_arasan_clk_data clk_data;
	स्थिर काष्ठा sdhci_arasan_clk_ops *clk_ops;

	काष्ठा regmap	*soc_ctl_base;
	स्थिर काष्ठा sdhci_arasan_soc_ctl_map *soc_ctl_map;
	अचिन्हित पूर्णांक	quirks;

/* Controller करोes not have CD wired and will not function normally without */
#घोषणा SDHCI_ARASAN_QUIRK_FORCE_CDTEST	BIT(0)
/* Controller immediately reports SDHCI_CLOCK_INT_STABLE after enabling the
 * पूर्णांकernal घड़ी even when the घड़ी isn't stable */
#घोषणा SDHCI_ARASAN_QUIRK_CLOCK_UNSTABLE BIT(1)
पूर्ण;

काष्ठा sdhci_arasan_of_data अणु
	स्थिर काष्ठा sdhci_arasan_soc_ctl_map *soc_ctl_map;
	स्थिर काष्ठा sdhci_pltfm_data *pdata;
	स्थिर काष्ठा sdhci_arasan_clk_ops *clk_ops;
पूर्ण;

अटल स्थिर काष्ठा sdhci_arasan_soc_ctl_map rk3399_soc_ctl_map = अणु
	.baseclkfreq = अणु .reg = 0xf000, .width = 8, .shअगरt = 8 पूर्ण,
	.घड़ीmultiplier = अणु .reg = 0xf02c, .width = 8, .shअगरt = 0पूर्ण,
	.hiword_update = true,
पूर्ण;

अटल स्थिर काष्ठा sdhci_arasan_soc_ctl_map पूर्णांकel_lgm_emmc_soc_ctl_map = अणु
	.baseclkfreq = अणु .reg = 0xa0, .width = 8, .shअगरt = 2 पूर्ण,
	.घड़ीmultiplier = अणु .reg = 0, .width = -1, .shअगरt = -1 पूर्ण,
	.hiword_update = false,
पूर्ण;

अटल स्थिर काष्ठा sdhci_arasan_soc_ctl_map पूर्णांकel_lgm_sdxc_soc_ctl_map = अणु
	.baseclkfreq = अणु .reg = 0x80, .width = 8, .shअगरt = 2 पूर्ण,
	.घड़ीmultiplier = अणु .reg = 0, .width = -1, .shअगरt = -1 पूर्ण,
	.hiword_update = false,
पूर्ण;

अटल स्थिर काष्ठा sdhci_arasan_soc_ctl_map पूर्णांकel_keembay_soc_ctl_map = अणु
	.baseclkfreq = अणु .reg = 0x0, .width = 8, .shअगरt = 14 पूर्ण,
	.घड़ीmultiplier = अणु .reg = 0x4, .width = 8, .shअगरt = 14 पूर्ण,
	.support64b = अणु .reg = 0x4, .width = 1, .shअगरt = 24 पूर्ण,
	.hiword_update = false,
पूर्ण;

/**
 * sdhci_arasan_syscon_ग_लिखो - Write to a field in soc_ctl रेजिस्टरs
 *
 * @host:	The sdhci_host
 * @fld:	The field to ग_लिखो to
 * @val:	The value to ग_लिखो
 *
 * This function allows writing to fields in sdhci_arasan_soc_ctl_map.
 * Note that अगर a field is specअगरied as not available (shअगरt < 0) then
 * this function will silently वापस an error code.  It will be noisy
 * and prपूर्णांक errors क्रम any other (unexpected) errors.
 *
 * Return: 0 on success and error value on error
 */
अटल पूर्णांक sdhci_arasan_syscon_ग_लिखो(काष्ठा sdhci_host *host,
				   स्थिर काष्ठा sdhci_arasan_soc_ctl_field *fld,
				   u32 val)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_arasan_data *sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	काष्ठा regmap *soc_ctl_base = sdhci_arasan->soc_ctl_base;
	u32 reg = fld->reg;
	u16 width = fld->width;
	s16 shअगरt = fld->shअगरt;
	पूर्णांक ret;

	/*
	 * Silently वापस errors क्रम shअगरt < 0 so caller करोesn't have
	 * to check क्रम fields which are optional.  For fields that
	 * are required then caller needs to करो something special
	 * anyway.
	 */
	अगर (shअगरt < 0)
		वापस -EINVAL;

	अगर (sdhci_arasan->soc_ctl_map->hiword_update)
		ret = regmap_ग_लिखो(soc_ctl_base, reg,
				   HIWORD_UPDATE(val, GENMASK(width, 0),
						 shअगरt));
	अन्यथा
		ret = regmap_update_bits(soc_ctl_base, reg,
					 GENMASK(shअगरt + width, shअगरt),
					 val << shअगरt);

	/* Yell about (unexpected) regmap errors */
	अगर (ret)
		pr_warn("%s: Regmap write fail: %d\n",
			 mmc_hostname(host->mmc), ret);

	वापस ret;
पूर्ण

अटल व्योम sdhci_arasan_set_घड़ी(काष्ठा sdhci_host *host, अचिन्हित पूर्णांक घड़ी)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_arasan_data *sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	काष्ठा sdhci_arasan_clk_data *clk_data = &sdhci_arasan->clk_data;
	bool ctrl_phy = false;

	अगर (!IS_ERR(sdhci_arasan->phy)) अणु
		अगर (!sdhci_arasan->is_phy_on && घड़ी <= PHY_CLK_TOO_SLOW_HZ) अणु
			/*
			 * If PHY off, set घड़ी to max speed and घातer PHY on.
			 *
			 * Although PHY करोcs apparently suggest घातer cycling
			 * when changing the घड़ी the PHY करोesn't like to be
			 * घातered on जबतक at low speeds like those used in ID
			 * mode.  Even worse is घातering the PHY on जबतक the
			 * घड़ी is off.
			 *
			 * To workaround the PHY limitations, the best we can
			 * करो is to घातer it on at a faster speed and then slam
			 * through low speeds without घातer cycling.
			 */
			sdhci_set_घड़ी(host, host->max_clk);
			phy_घातer_on(sdhci_arasan->phy);
			sdhci_arasan->is_phy_on = true;

			/*
			 * We'll now fall through to the below हाल with
			 * ctrl_phy = false (so we won't turn off/on).  The
			 * sdhci_set_घड़ी() will set the real घड़ी.
			 */
		पूर्ण अन्यथा अगर (घड़ी > PHY_CLK_TOO_SLOW_HZ) अणु
			/*
			 * At higher घड़ी speeds the PHY is fine being घातer
			 * cycled and करोcs say you _should_ घातer cycle when
			 * changing घड़ी speeds.
			 */
			ctrl_phy = true;
		पूर्ण
	पूर्ण

	अगर (ctrl_phy && sdhci_arasan->is_phy_on) अणु
		phy_घातer_off(sdhci_arasan->phy);
		sdhci_arasan->is_phy_on = false;
	पूर्ण

	/* Set the Input and Output Clock Phase Delays */
	अगर (clk_data->set_clk_delays)
		clk_data->set_clk_delays(host);

	sdhci_set_घड़ी(host, घड़ी);

	अगर (sdhci_arasan->quirks & SDHCI_ARASAN_QUIRK_CLOCK_UNSTABLE)
		/*
		 * Some controllers immediately report SDHCI_CLOCK_INT_STABLE
		 * after enabling the घड़ी even though the घड़ी is not
		 * stable. Trying to use a घड़ी without रुकोing here results
		 * in EILSEQ जबतक detecting some older/slower cards. The
		 * chosen delay is the maximum delay from sdhci_set_घड़ी.
		 */
		msleep(20);

	अगर (ctrl_phy) अणु
		phy_घातer_on(sdhci_arasan->phy);
		sdhci_arasan->is_phy_on = true;
	पूर्ण
पूर्ण

अटल व्योम sdhci_arasan_hs400_enhanced_strobe(काष्ठा mmc_host *mmc,
					काष्ठा mmc_ios *ios)
अणु
	u32 venकरोr;
	काष्ठा sdhci_host *host = mmc_priv(mmc);

	venकरोr = sdhci_पढ़ोl(host, SDHCI_ARASAN_VENDOR_REGISTER);
	अगर (ios->enhanced_strobe)
		venकरोr |= VENDOR_ENHANCED_STROBE;
	अन्यथा
		venकरोr &= ~VENDOR_ENHANCED_STROBE;

	sdhci_ग_लिखोl(host, venकरोr, SDHCI_ARASAN_VENDOR_REGISTER);
पूर्ण

अटल व्योम sdhci_arasan_reset(काष्ठा sdhci_host *host, u8 mask)
अणु
	u8 ctrl;
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_arasan_data *sdhci_arasan = sdhci_pltfm_priv(pltfm_host);

	sdhci_reset(host, mask);

	अगर (sdhci_arasan->quirks & SDHCI_ARASAN_QUIRK_FORCE_CDTEST) अणु
		ctrl = sdhci_पढ़ोb(host, SDHCI_HOST_CONTROL);
		ctrl |= SDHCI_CTRL_CDTEST_INS | SDHCI_CTRL_CDTEST_EN;
		sdhci_ग_लिखोb(host, ctrl, SDHCI_HOST_CONTROL);
	पूर्ण
पूर्ण

अटल पूर्णांक sdhci_arasan_voltage_चयन(काष्ठा mmc_host *mmc,
				       काष्ठा mmc_ios *ios)
अणु
	चयन (ios->संकेत_voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_180:
		/*
		 * Plese करोn't switch to 1V8 as arasan,5.1 doesn't
		 * actually refer to this setting to indicate the
		 * संकेत voltage and the state machine will be broken
		 * actually अगर we क्रमce to enable 1V8. That's something
		 * like broken quirk but we could work around here.
		 */
		वापस 0;
	हाल MMC_SIGNAL_VOLTAGE_330:
	हाल MMC_SIGNAL_VOLTAGE_120:
		/* We करोn't support 3V3 and 1V2 */
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा sdhci_ops sdhci_arasan_ops = अणु
	.set_घड़ी = sdhci_arasan_set_घड़ी,
	.get_max_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.get_समयout_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_arasan_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
	.set_घातer = sdhci_set_घातer_and_bus_voltage,
पूर्ण;

अटल u32 sdhci_arasan_cqhci_irq(काष्ठा sdhci_host *host, u32 पूर्णांकmask)
अणु
	पूर्णांक cmd_error = 0;
	पूर्णांक data_error = 0;

	अगर (!sdhci_cqe_irq(host, पूर्णांकmask, &cmd_error, &data_error))
		वापस पूर्णांकmask;

	cqhci_irq(host->mmc, पूर्णांकmask, cmd_error, data_error);

	वापस 0;
पूर्ण

अटल व्योम sdhci_arasan_dumpregs(काष्ठा mmc_host *mmc)
अणु
	sdhci_dumpregs(mmc_priv(mmc));
पूर्ण

अटल व्योम sdhci_arasan_cqe_enable(काष्ठा mmc_host *mmc)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	u32 reg;

	reg = sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE);
	जबतक (reg & SDHCI_DATA_AVAILABLE) अणु
		sdhci_पढ़ोl(host, SDHCI_BUFFER);
		reg = sdhci_पढ़ोl(host, SDHCI_PRESENT_STATE);
	पूर्ण

	sdhci_cqe_enable(mmc);
पूर्ण

अटल स्थिर काष्ठा cqhci_host_ops sdhci_arasan_cqhci_ops = अणु
	.enable         = sdhci_arasan_cqe_enable,
	.disable        = sdhci_cqe_disable,
	.dumpregs       = sdhci_arasan_dumpregs,
पूर्ण;

अटल स्थिर काष्ठा sdhci_ops sdhci_arasan_cqe_ops = अणु
	.set_घड़ी = sdhci_arasan_set_घड़ी,
	.get_max_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.get_समयout_घड़ी = sdhci_pltfm_clk_get_max_घड़ी,
	.set_bus_width = sdhci_set_bus_width,
	.reset = sdhci_arasan_reset,
	.set_uhs_संकेतing = sdhci_set_uhs_संकेतing,
	.set_घातer = sdhci_set_घातer_and_bus_voltage,
	.irq = sdhci_arasan_cqhci_irq,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_arasan_cqe_pdata = अणु
	.ops = &sdhci_arasan_cqe_ops,
	.quirks = SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
			SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
/**
 * sdhci_arasan_suspend - Suspend method क्रम the driver
 * @dev:	Address of the device काष्ठाure
 *
 * Put the device in a low घातer state.
 *
 * Return: 0 on success and error value on error
 */
अटल पूर्णांक sdhci_arasan_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_arasan_data *sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	अगर (host->tuning_mode != SDHCI_TUNING_MODE_3)
		mmc_retune_needed(host->mmc);

	अगर (sdhci_arasan->has_cqe) अणु
		ret = cqhci_suspend(host->mmc);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = sdhci_suspend_host(host);
	अगर (ret)
		वापस ret;

	अगर (!IS_ERR(sdhci_arasan->phy) && sdhci_arasan->is_phy_on) अणु
		ret = phy_घातer_off(sdhci_arasan->phy);
		अगर (ret) अणु
			dev_err(dev, "Cannot power off phy.\n");
			sdhci_resume_host(host);
			वापस ret;
		पूर्ण
		sdhci_arasan->is_phy_on = false;
	पूर्ण

	clk_disable(pltfm_host->clk);
	clk_disable(sdhci_arasan->clk_ahb);

	वापस 0;
पूर्ण

/**
 * sdhci_arasan_resume - Resume method क्रम the driver
 * @dev:	Address of the device काष्ठाure
 *
 * Resume operation after suspend
 *
 * Return: 0 on success and error value on error
 */
अटल पूर्णांक sdhci_arasan_resume(काष्ठा device *dev)
अणु
	काष्ठा sdhci_host *host = dev_get_drvdata(dev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_arasan_data *sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	पूर्णांक ret;

	ret = clk_enable(sdhci_arasan->clk_ahb);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable AHB clock.\n");
		वापस ret;
	पूर्ण

	ret = clk_enable(pltfm_host->clk);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable SD clock.\n");
		वापस ret;
	पूर्ण

	अगर (!IS_ERR(sdhci_arasan->phy) && host->mmc->actual_घड़ी) अणु
		ret = phy_घातer_on(sdhci_arasan->phy);
		अगर (ret) अणु
			dev_err(dev, "Cannot power on phy.\n");
			वापस ret;
		पूर्ण
		sdhci_arasan->is_phy_on = true;
	पूर्ण

	ret = sdhci_resume_host(host);
	अगर (ret) अणु
		dev_err(dev, "Cannot resume host.\n");
		वापस ret;
	पूर्ण

	अगर (sdhci_arasan->has_cqe)
		वापस cqhci_resume(host->mmc);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* ! CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(sdhci_arasan_dev_pm_ops, sdhci_arasan_suspend,
			 sdhci_arasan_resume);

/**
 * sdhci_arasan_sdcardclk_recalc_rate - Return the card घड़ी rate
 *
 * @hw:			Poपूर्णांकer to the hardware घड़ी काष्ठाure.
 * @parent_rate:		The parent rate (should be rate of clk_xin).
 *
 * Return the current actual rate of the SD card घड़ी.  This can be used
 * to communicate with out PHY.
 *
 * Return: The card घड़ी rate.
 */
अटल अचिन्हित दीर्घ sdhci_arasan_sdcardclk_recalc_rate(काष्ठा clk_hw *hw,
						      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sdhci_arasan_clk_data *clk_data =
		container_of(hw, काष्ठा sdhci_arasan_clk_data, sdcardclk_hw);
	काष्ठा sdhci_arasan_data *sdhci_arasan =
		container_of(clk_data, काष्ठा sdhci_arasan_data, clk_data);
	काष्ठा sdhci_host *host = sdhci_arasan->host;

	वापस host->mmc->actual_घड़ी;
पूर्ण

अटल स्थिर काष्ठा clk_ops arasan_sdcardclk_ops = अणु
	.recalc_rate = sdhci_arasan_sdcardclk_recalc_rate,
पूर्ण;

/**
 * sdhci_arasan_sampleclk_recalc_rate - Return the sampling घड़ी rate
 *
 * @hw:			Poपूर्णांकer to the hardware घड़ी काष्ठाure.
 * @parent_rate:		The parent rate (should be rate of clk_xin).
 *
 * Return the current actual rate of the sampling घड़ी.  This can be used
 * to communicate with out PHY.
 *
 * Return: The sample घड़ी rate.
 */
अटल अचिन्हित दीर्घ sdhci_arasan_sampleclk_recalc_rate(काष्ठा clk_hw *hw,
						      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा sdhci_arasan_clk_data *clk_data =
		container_of(hw, काष्ठा sdhci_arasan_clk_data, sampleclk_hw);
	काष्ठा sdhci_arasan_data *sdhci_arasan =
		container_of(clk_data, काष्ठा sdhci_arasan_data, clk_data);
	काष्ठा sdhci_host *host = sdhci_arasan->host;

	वापस host->mmc->actual_घड़ी;
पूर्ण

अटल स्थिर काष्ठा clk_ops arasan_sampleclk_ops = अणु
	.recalc_rate = sdhci_arasan_sampleclk_recalc_rate,
पूर्ण;

/**
 * sdhci_zynqmp_sdcardclk_set_phase - Set the SD Output Clock Tap Delays
 *
 * @hw:			Poपूर्णांकer to the hardware घड़ी काष्ठाure.
 * @degrees:		The घड़ी phase shअगरt between 0 - 359.
 *
 * Set the SD Output Clock Tap Delays क्रम Output path
 *
 * Return: 0 on success and error value on error
 */
अटल पूर्णांक sdhci_zynqmp_sdcardclk_set_phase(काष्ठा clk_hw *hw, पूर्णांक degrees)
अणु
	काष्ठा sdhci_arasan_clk_data *clk_data =
		container_of(hw, काष्ठा sdhci_arasan_clk_data, sdcardclk_hw);
	काष्ठा sdhci_arasan_data *sdhci_arasan =
		container_of(clk_data, काष्ठा sdhci_arasan_data, clk_data);
	काष्ठा sdhci_host *host = sdhci_arasan->host;
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 node_id = !म_भेद(clk_name, "clk_out_sd0") ? NODE_SD_0 : NODE_SD_1;
	u8 tap_delay, tap_max = 0;
	पूर्णांक ret;

	/* This is applicable क्रम SDHCI_SPEC_300 and above */
	अगर (host->version < SDHCI_SPEC_300)
		वापस 0;

	चयन (host->timing) अणु
	हाल MMC_TIMING_MMC_HS:
	हाल MMC_TIMING_SD_HS:
	हाल MMC_TIMING_UHS_SDR25:
	हाल MMC_TIMING_UHS_DDR50:
	हाल MMC_TIMING_MMC_DDR52:
		/* For 50MHz घड़ी, 30 Taps are available */
		tap_max = 30;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR50:
		/* For 100MHz घड़ी, 15 Taps are available */
		tap_max = 15;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_MMC_HS200:
		/* For 200MHz घड़ी, 8 Taps are available */
		tap_max = 8;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	tap_delay = (degrees * tap_max) / 360;

	/* Set the Clock Phase */
	ret = zynqmp_pm_set_sd_tapdelay(node_id, PM_TAPDELAY_OUTPUT, tap_delay);
	अगर (ret)
		pr_err("Error setting Output Tap Delay\n");

	/* Release DLL Reset */
	zynqmp_pm_sd_dll_reset(node_id, PM_DLL_RESET_RELEASE);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops zynqmp_sdcardclk_ops = अणु
	.recalc_rate = sdhci_arasan_sdcardclk_recalc_rate,
	.set_phase = sdhci_zynqmp_sdcardclk_set_phase,
पूर्ण;

/**
 * sdhci_zynqmp_sampleclk_set_phase - Set the SD Input Clock Tap Delays
 *
 * @hw:			Poपूर्णांकer to the hardware घड़ी काष्ठाure.
 * @degrees:		The घड़ी phase shअगरt between 0 - 359.
 *
 * Set the SD Input Clock Tap Delays क्रम Input path
 *
 * Return: 0 on success and error value on error
 */
अटल पूर्णांक sdhci_zynqmp_sampleclk_set_phase(काष्ठा clk_hw *hw, पूर्णांक degrees)
अणु
	काष्ठा sdhci_arasan_clk_data *clk_data =
		container_of(hw, काष्ठा sdhci_arasan_clk_data, sampleclk_hw);
	काष्ठा sdhci_arasan_data *sdhci_arasan =
		container_of(clk_data, काष्ठा sdhci_arasan_data, clk_data);
	काष्ठा sdhci_host *host = sdhci_arasan->host;
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 node_id = !म_भेद(clk_name, "clk_in_sd0") ? NODE_SD_0 : NODE_SD_1;
	u8 tap_delay, tap_max = 0;
	पूर्णांक ret;

	/* This is applicable क्रम SDHCI_SPEC_300 and above */
	अगर (host->version < SDHCI_SPEC_300)
		वापस 0;

	/* Assert DLL Reset */
	zynqmp_pm_sd_dll_reset(node_id, PM_DLL_RESET_ASSERT);

	चयन (host->timing) अणु
	हाल MMC_TIMING_MMC_HS:
	हाल MMC_TIMING_SD_HS:
	हाल MMC_TIMING_UHS_SDR25:
	हाल MMC_TIMING_UHS_DDR50:
	हाल MMC_TIMING_MMC_DDR52:
		/* For 50MHz घड़ी, 120 Taps are available */
		tap_max = 120;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR50:
		/* For 100MHz घड़ी, 60 Taps are available */
		tap_max = 60;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_MMC_HS200:
		/* For 200MHz घड़ी, 30 Taps are available */
		tap_max = 30;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	tap_delay = (degrees * tap_max) / 360;

	/* Set the Clock Phase */
	ret = zynqmp_pm_set_sd_tapdelay(node_id, PM_TAPDELAY_INPUT, tap_delay);
	अगर (ret)
		pr_err("Error setting Input Tap Delay\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops zynqmp_sampleclk_ops = अणु
	.recalc_rate = sdhci_arasan_sampleclk_recalc_rate,
	.set_phase = sdhci_zynqmp_sampleclk_set_phase,
पूर्ण;

/**
 * sdhci_versal_sdcardclk_set_phase - Set the SD Output Clock Tap Delays
 *
 * @hw:			Poपूर्णांकer to the hardware घड़ी काष्ठाure.
 * @degrees:		The घड़ी phase shअगरt between 0 - 359.
 *
 * Set the SD Output Clock Tap Delays क्रम Output path
 *
 * Return: 0 on success and error value on error
 */
अटल पूर्णांक sdhci_versal_sdcardclk_set_phase(काष्ठा clk_hw *hw, पूर्णांक degrees)
अणु
	काष्ठा sdhci_arasan_clk_data *clk_data =
		container_of(hw, काष्ठा sdhci_arasan_clk_data, sdcardclk_hw);
	काष्ठा sdhci_arasan_data *sdhci_arasan =
		container_of(clk_data, काष्ठा sdhci_arasan_data, clk_data);
	काष्ठा sdhci_host *host = sdhci_arasan->host;
	u8 tap_delay, tap_max = 0;

	/* This is applicable क्रम SDHCI_SPEC_300 and above */
	अगर (host->version < SDHCI_SPEC_300)
		वापस 0;

	चयन (host->timing) अणु
	हाल MMC_TIMING_MMC_HS:
	हाल MMC_TIMING_SD_HS:
	हाल MMC_TIMING_UHS_SDR25:
	हाल MMC_TIMING_UHS_DDR50:
	हाल MMC_TIMING_MMC_DDR52:
		/* For 50MHz घड़ी, 30 Taps are available */
		tap_max = 30;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR50:
		/* For 100MHz घड़ी, 15 Taps are available */
		tap_max = 15;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_MMC_HS200:
		/* For 200MHz घड़ी, 8 Taps are available */
		tap_max = 8;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	tap_delay = (degrees * tap_max) / 360;

	/* Set the Clock Phase */
	अगर (tap_delay) अणु
		u32 regval;

		regval = sdhci_पढ़ोl(host, SDHCI_ARASAN_OTAPDLY_REGISTER);
		regval |= SDHCI_OTAPDLY_ENABLE;
		sdhci_ग_लिखोl(host, regval, SDHCI_ARASAN_OTAPDLY_REGISTER);
		regval &= ~SDHCI_ARASAN_OTAPDLY_SEL_MASK;
		regval |= tap_delay;
		sdhci_ग_लिखोl(host, regval, SDHCI_ARASAN_OTAPDLY_REGISTER);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops versal_sdcardclk_ops = अणु
	.recalc_rate = sdhci_arasan_sdcardclk_recalc_rate,
	.set_phase = sdhci_versal_sdcardclk_set_phase,
पूर्ण;

/**
 * sdhci_versal_sampleclk_set_phase - Set the SD Input Clock Tap Delays
 *
 * @hw:			Poपूर्णांकer to the hardware घड़ी काष्ठाure.
 * @degrees:		The घड़ी phase shअगरt between 0 - 359.
 *
 * Set the SD Input Clock Tap Delays क्रम Input path
 *
 * Return: 0 on success and error value on error
 */
अटल पूर्णांक sdhci_versal_sampleclk_set_phase(काष्ठा clk_hw *hw, पूर्णांक degrees)
अणु
	काष्ठा sdhci_arasan_clk_data *clk_data =
		container_of(hw, काष्ठा sdhci_arasan_clk_data, sampleclk_hw);
	काष्ठा sdhci_arasan_data *sdhci_arasan =
		container_of(clk_data, काष्ठा sdhci_arasan_data, clk_data);
	काष्ठा sdhci_host *host = sdhci_arasan->host;
	u8 tap_delay, tap_max = 0;

	/* This is applicable क्रम SDHCI_SPEC_300 and above */
	अगर (host->version < SDHCI_SPEC_300)
		वापस 0;

	चयन (host->timing) अणु
	हाल MMC_TIMING_MMC_HS:
	हाल MMC_TIMING_SD_HS:
	हाल MMC_TIMING_UHS_SDR25:
	हाल MMC_TIMING_UHS_DDR50:
	हाल MMC_TIMING_MMC_DDR52:
		/* For 50MHz घड़ी, 120 Taps are available */
		tap_max = 120;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR50:
		/* For 100MHz घड़ी, 60 Taps are available */
		tap_max = 60;
		अवरोध;
	हाल MMC_TIMING_UHS_SDR104:
	हाल MMC_TIMING_MMC_HS200:
		/* For 200MHz घड़ी, 30 Taps are available */
		tap_max = 30;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	tap_delay = (degrees * tap_max) / 360;

	/* Set the Clock Phase */
	अगर (tap_delay) अणु
		u32 regval;

		regval = sdhci_पढ़ोl(host, SDHCI_ARASAN_ITAPDLY_REGISTER);
		regval |= SDHCI_ITAPDLY_CHGWIN;
		sdhci_ग_लिखोl(host, regval, SDHCI_ARASAN_ITAPDLY_REGISTER);
		regval |= SDHCI_ITAPDLY_ENABLE;
		sdhci_ग_लिखोl(host, regval, SDHCI_ARASAN_ITAPDLY_REGISTER);
		regval &= ~SDHCI_ARASAN_ITAPDLY_SEL_MASK;
		regval |= tap_delay;
		sdhci_ग_लिखोl(host, regval, SDHCI_ARASAN_ITAPDLY_REGISTER);
		regval &= ~SDHCI_ITAPDLY_CHGWIN;
		sdhci_ग_लिखोl(host, regval, SDHCI_ARASAN_ITAPDLY_REGISTER);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops versal_sampleclk_ops = अणु
	.recalc_rate = sdhci_arasan_sampleclk_recalc_rate,
	.set_phase = sdhci_versal_sampleclk_set_phase,
पूर्ण;

अटल व्योम arasan_zynqmp_dll_reset(काष्ठा sdhci_host *host, u32 deviceid)
अणु
	u16 clk;

	clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);
	clk &= ~(SDHCI_CLOCK_CARD_EN | SDHCI_CLOCK_INT_EN);
	sdhci_ग_लिखोw(host, clk, SDHCI_CLOCK_CONTROL);

	/* Issue DLL Reset */
	zynqmp_pm_sd_dll_reset(deviceid, PM_DLL_RESET_PULSE);

	clk = sdhci_पढ़ोw(host, SDHCI_CLOCK_CONTROL);

	sdhci_enable_clk(host, clk);
पूर्ण

अटल पूर्णांक arasan_zynqmp_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा sdhci_host *host = mmc_priv(mmc);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_arasan_data *sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	काष्ठा clk_hw *hw = &sdhci_arasan->clk_data.sdcardclk_hw;
	स्थिर अक्षर *clk_name = clk_hw_get_name(hw);
	u32 device_id = !म_भेद(clk_name, "clk_out_sd0") ? NODE_SD_0 :
							   NODE_SD_1;
	पूर्णांक err;

	arasan_zynqmp_dll_reset(host, device_id);

	err = sdhci_execute_tuning(mmc, opcode);
	अगर (err)
		वापस err;

	arasan_zynqmp_dll_reset(host, device_id);

	वापस 0;
पूर्ण

/**
 * sdhci_arasan_update_घड़ीmultiplier - Set corecfg_घड़ीmultiplier
 *
 * @host:		The sdhci_host
 * @value:		The value to ग_लिखो
 *
 * The corecfg_घड़ीmultiplier is supposed to contain घड़ी multiplier
 * value of programmable घड़ी generator.
 *
 * NOTES:
 * - Many existing devices करोn't seem to करो this and work fine.  To keep
 *   compatibility क्रम old hardware where the device tree करोesn't provide a
 *   रेजिस्टर map, this function is a noop अगर a soc_ctl_map hasn't been provided
 *   क्रम this platक्रमm.
 * - The value of corecfg_घड़ीmultiplier should sync with that of corresponding
 *   value पढ़ोing from sdhci_capability_रेजिस्टर. So this function is called
 *   once at probe समय and never called again.
 */
अटल व्योम sdhci_arasan_update_घड़ीmultiplier(काष्ठा sdhci_host *host,
						u32 value)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_arasan_data *sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	स्थिर काष्ठा sdhci_arasan_soc_ctl_map *soc_ctl_map =
		sdhci_arasan->soc_ctl_map;

	/* Having a map is optional */
	अगर (!soc_ctl_map)
		वापस;

	/* If we have a map, we expect to have a syscon */
	अगर (!sdhci_arasan->soc_ctl_base) अणु
		pr_warn("%s: Have regmap, but no soc-ctl-syscon\n",
			mmc_hostname(host->mmc));
		वापस;
	पूर्ण

	sdhci_arasan_syscon_ग_लिखो(host, &soc_ctl_map->घड़ीmultiplier, value);
पूर्ण

/**
 * sdhci_arasan_update_baseclkfreq - Set corecfg_baseclkfreq
 *
 * @host:		The sdhci_host
 *
 * The corecfg_baseclkfreq is supposed to contain the MHz of clk_xin.  This
 * function can be used to make that happen.
 *
 * NOTES:
 * - Many existing devices करोn't seem to करो this and work fine.  To keep
 *   compatibility क्रम old hardware where the device tree करोesn't provide a
 *   रेजिस्टर map, this function is a noop अगर a soc_ctl_map hasn't been provided
 *   क्रम this platक्रमm.
 * - It's assumed that clk_xin is not dynamic and that we use the SDHCI भागider
 *   to achieve lower घड़ी rates.  That means that this function is called once
 *   at probe समय and never called again.
 */
अटल व्योम sdhci_arasan_update_baseclkfreq(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_arasan_data *sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	स्थिर काष्ठा sdhci_arasan_soc_ctl_map *soc_ctl_map =
		sdhci_arasan->soc_ctl_map;
	u32 mhz = DIV_ROUND_CLOSEST(clk_get_rate(pltfm_host->clk), 1000000);

	/* Having a map is optional */
	अगर (!soc_ctl_map)
		वापस;

	/* If we have a map, we expect to have a syscon */
	अगर (!sdhci_arasan->soc_ctl_base) अणु
		pr_warn("%s: Have regmap, but no soc-ctl-syscon\n",
			mmc_hostname(host->mmc));
		वापस;
	पूर्ण

	sdhci_arasan_syscon_ग_लिखो(host, &soc_ctl_map->baseclkfreq, mhz);
पूर्ण

अटल व्योम sdhci_arasan_set_clk_delays(काष्ठा sdhci_host *host)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_arasan_data *sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	काष्ठा sdhci_arasan_clk_data *clk_data = &sdhci_arasan->clk_data;

	clk_set_phase(clk_data->sampleclk,
		      clk_data->clk_phase_in[host->timing]);
	clk_set_phase(clk_data->sdcardclk,
		      clk_data->clk_phase_out[host->timing]);
पूर्ण

अटल व्योम arasan_dt_पढ़ो_clk_phase(काष्ठा device *dev,
				     काष्ठा sdhci_arasan_clk_data *clk_data,
				     अचिन्हित पूर्णांक timing, स्थिर अक्षर *prop)
अणु
	काष्ठा device_node *np = dev->of_node;

	पूर्णांक clk_phase[2] = अणु0पूर्ण;

	/*
	 * Read Tap Delay values from DT, अगर the DT करोes not contain the
	 * Tap Values then use the pre-defined values.
	 */
	अगर (of_property_पढ़ो_variable_u32_array(np, prop, &clk_phase[0],
						2, 0)) अणु
		dev_dbg(dev, "Using predefined clock phase for %s = %d %d\n",
			prop, clk_data->clk_phase_in[timing],
			clk_data->clk_phase_out[timing]);
		वापस;
	पूर्ण

	/* The values पढ़ो are Input and Output Clock Delays in order */
	clk_data->clk_phase_in[timing] = clk_phase[0];
	clk_data->clk_phase_out[timing] = clk_phase[1];
पूर्ण

/**
 * arasan_dt_parse_clk_phases - Read Clock Delay values from DT
 *
 * @dev:		Poपूर्णांकer to our काष्ठा device.
 * @clk_data:		Poपूर्णांकer to the Clock Data काष्ठाure
 *
 * Called at initialization to parse the values of Clock Delays.
 */
अटल व्योम arasan_dt_parse_clk_phases(काष्ठा device *dev,
				       काष्ठा sdhci_arasan_clk_data *clk_data)
अणु
	u32 mio_bank = 0;
	पूर्णांक i;

	/*
	 * This has been kept as a poपूर्णांकer and is asचिन्हित a function here.
	 * So that dअगरferent controller variants can assign their own handling
	 * function.
	 */
	clk_data->set_clk_delays = sdhci_arasan_set_clk_delays;

	अगर (of_device_is_compatible(dev->of_node, "xlnx,zynqmp-8.9a")) अणु
		u32 zynqmp_iclk_phase[MMC_TIMING_MMC_HS400 + 1] =
			ZYNQMP_ICLK_PHASE;
		u32 zynqmp_oclk_phase[MMC_TIMING_MMC_HS400 + 1] =
			ZYNQMP_OCLK_PHASE;

		of_property_पढ़ो_u32(dev->of_node, "xlnx,mio-bank", &mio_bank);
		अगर (mio_bank == 2) अणु
			zynqmp_oclk_phase[MMC_TIMING_UHS_SDR104] = 90;
			zynqmp_oclk_phase[MMC_TIMING_MMC_HS200] = 90;
		पूर्ण

		क्रम (i = 0; i <= MMC_TIMING_MMC_HS400; i++) अणु
			clk_data->clk_phase_in[i] = zynqmp_iclk_phase[i];
			clk_data->clk_phase_out[i] = zynqmp_oclk_phase[i];
		पूर्ण
	पूर्ण

	अगर (of_device_is_compatible(dev->of_node, "xlnx,versal-8.9a")) अणु
		u32 versal_iclk_phase[MMC_TIMING_MMC_HS400 + 1] =
			VERSAL_ICLK_PHASE;
		u32 versal_oclk_phase[MMC_TIMING_MMC_HS400 + 1] =
			VERSAL_OCLK_PHASE;

		क्रम (i = 0; i <= MMC_TIMING_MMC_HS400; i++) अणु
			clk_data->clk_phase_in[i] = versal_iclk_phase[i];
			clk_data->clk_phase_out[i] = versal_oclk_phase[i];
		पूर्ण
	पूर्ण

	arasan_dt_पढ़ो_clk_phase(dev, clk_data, MMC_TIMING_LEGACY,
				 "clk-phase-legacy");
	arasan_dt_पढ़ो_clk_phase(dev, clk_data, MMC_TIMING_MMC_HS,
				 "clk-phase-mmc-hs");
	arasan_dt_पढ़ो_clk_phase(dev, clk_data, MMC_TIMING_SD_HS,
				 "clk-phase-sd-hs");
	arasan_dt_पढ़ो_clk_phase(dev, clk_data, MMC_TIMING_UHS_SDR12,
				 "clk-phase-uhs-sdr12");
	arasan_dt_पढ़ो_clk_phase(dev, clk_data, MMC_TIMING_UHS_SDR25,
				 "clk-phase-uhs-sdr25");
	arasan_dt_पढ़ो_clk_phase(dev, clk_data, MMC_TIMING_UHS_SDR50,
				 "clk-phase-uhs-sdr50");
	arasan_dt_पढ़ो_clk_phase(dev, clk_data, MMC_TIMING_UHS_SDR104,
				 "clk-phase-uhs-sdr104");
	arasan_dt_पढ़ो_clk_phase(dev, clk_data, MMC_TIMING_UHS_DDR50,
				 "clk-phase-uhs-ddr50");
	arasan_dt_पढ़ो_clk_phase(dev, clk_data, MMC_TIMING_MMC_DDR52,
				 "clk-phase-mmc-ddr52");
	arasan_dt_पढ़ो_clk_phase(dev, clk_data, MMC_TIMING_MMC_HS200,
				 "clk-phase-mmc-hs200");
	arasan_dt_पढ़ो_clk_phase(dev, clk_data, MMC_TIMING_MMC_HS400,
				 "clk-phase-mmc-hs400");
पूर्ण

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_arasan_pdata = अणु
	.ops = &sdhci_arasan_ops,
	.quirks = SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
			SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN |
			SDHCI_QUIRK2_STOP_WITH_TC,
पूर्ण;

अटल स्थिर काष्ठा sdhci_arasan_clk_ops arasan_clk_ops = अणु
	.sdcardclk_ops = &arasan_sdcardclk_ops,
	.sampleclk_ops = &arasan_sampleclk_ops,
पूर्ण;

अटल काष्ठा sdhci_arasan_of_data sdhci_arasan_generic_data = अणु
	.pdata = &sdhci_arasan_pdata,
	.clk_ops = &arasan_clk_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_keembay_emmc_pdata = अणु
	.ops = &sdhci_arasan_cqe_ops,
	.quirks = SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN |
		SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
		SDHCI_QUIRK_NO_LED |
		SDHCI_QUIRK_32BIT_DMA_ADDR |
		SDHCI_QUIRK_32BIT_DMA_SIZE |
		SDHCI_QUIRK_32BIT_ADMA_SIZE,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
		SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN |
		SDHCI_QUIRK2_CAPS_BIT63_FOR_HS400 |
		SDHCI_QUIRK2_STOP_WITH_TC |
		SDHCI_QUIRK2_BROKEN_64_BIT_DMA,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_keembay_sd_pdata = अणु
	.ops = &sdhci_arasan_ops,
	.quirks = SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN |
		SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
		SDHCI_QUIRK_NO_LED |
		SDHCI_QUIRK_32BIT_DMA_ADDR |
		SDHCI_QUIRK_32BIT_DMA_SIZE |
		SDHCI_QUIRK_32BIT_ADMA_SIZE,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
		SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN |
		SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON |
		SDHCI_QUIRK2_STOP_WITH_TC |
		SDHCI_QUIRK2_BROKEN_64_BIT_DMA,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_keembay_sdio_pdata = अणु
	.ops = &sdhci_arasan_ops,
	.quirks = SDHCI_QUIRK_CAP_CLOCK_BASE_BROKEN |
		SDHCI_QUIRK_NO_ENDATTR_IN_NOPDESC |
		SDHCI_QUIRK_NO_LED |
		SDHCI_QUIRK_32BIT_DMA_ADDR |
		SDHCI_QUIRK_32BIT_DMA_SIZE |
		SDHCI_QUIRK_32BIT_ADMA_SIZE,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
		SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN |
		SDHCI_QUIRK2_HOST_OFF_CARD_ON |
		SDHCI_QUIRK2_BROKEN_64_BIT_DMA,
पूर्ण;

अटल काष्ठा sdhci_arasan_of_data sdhci_arasan_rk3399_data = अणु
	.soc_ctl_map = &rk3399_soc_ctl_map,
	.pdata = &sdhci_arasan_cqe_pdata,
	.clk_ops = &arasan_clk_ops,
पूर्ण;

अटल काष्ठा sdhci_arasan_of_data पूर्णांकel_lgm_emmc_data = अणु
	.soc_ctl_map = &पूर्णांकel_lgm_emmc_soc_ctl_map,
	.pdata = &sdhci_arasan_cqe_pdata,
	.clk_ops = &arasan_clk_ops,
पूर्ण;

अटल काष्ठा sdhci_arasan_of_data पूर्णांकel_lgm_sdxc_data = अणु
	.soc_ctl_map = &पूर्णांकel_lgm_sdxc_soc_ctl_map,
	.pdata = &sdhci_arasan_cqe_pdata,
	.clk_ops = &arasan_clk_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_pltfm_data sdhci_arasan_zynqmp_pdata = अणु
	.ops = &sdhci_arasan_ops,
	.quirks2 = SDHCI_QUIRK2_PRESET_VALUE_BROKEN |
			SDHCI_QUIRK2_CLOCK_DIV_ZERO_BROKEN |
			SDHCI_QUIRK2_STOP_WITH_TC,
पूर्ण;

अटल स्थिर काष्ठा sdhci_arasan_clk_ops zynqmp_clk_ops = अणु
	.sdcardclk_ops = &zynqmp_sdcardclk_ops,
	.sampleclk_ops = &zynqmp_sampleclk_ops,
पूर्ण;

अटल काष्ठा sdhci_arasan_of_data sdhci_arasan_zynqmp_data = अणु
	.pdata = &sdhci_arasan_zynqmp_pdata,
	.clk_ops = &zynqmp_clk_ops,
पूर्ण;

अटल स्थिर काष्ठा sdhci_arasan_clk_ops versal_clk_ops = अणु
	.sdcardclk_ops = &versal_sdcardclk_ops,
	.sampleclk_ops = &versal_sampleclk_ops,
पूर्ण;

अटल काष्ठा sdhci_arasan_of_data sdhci_arasan_versal_data = अणु
	.pdata = &sdhci_arasan_zynqmp_pdata,
	.clk_ops = &versal_clk_ops,
पूर्ण;

अटल काष्ठा sdhci_arasan_of_data पूर्णांकel_keembay_emmc_data = अणु
	.soc_ctl_map = &पूर्णांकel_keembay_soc_ctl_map,
	.pdata = &sdhci_keembay_emmc_pdata,
	.clk_ops = &arasan_clk_ops,
पूर्ण;

अटल काष्ठा sdhci_arasan_of_data पूर्णांकel_keembay_sd_data = अणु
	.soc_ctl_map = &पूर्णांकel_keembay_soc_ctl_map,
	.pdata = &sdhci_keembay_sd_pdata,
	.clk_ops = &arasan_clk_ops,
पूर्ण;

अटल काष्ठा sdhci_arasan_of_data पूर्णांकel_keembay_sdio_data = अणु
	.soc_ctl_map = &पूर्णांकel_keembay_soc_ctl_map,
	.pdata = &sdhci_keembay_sdio_pdata,
	.clk_ops = &arasan_clk_ops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sdhci_arasan_of_match[] = अणु
	/* SoC-specअगरic compatible strings w/ soc_ctl_map */
	अणु
		.compatible = "rockchip,rk3399-sdhci-5.1",
		.data = &sdhci_arasan_rk3399_data,
	पूर्ण,
	अणु
		.compatible = "intel,lgm-sdhci-5.1-emmc",
		.data = &पूर्णांकel_lgm_emmc_data,
	पूर्ण,
	अणु
		.compatible = "intel,lgm-sdhci-5.1-sdxc",
		.data = &पूर्णांकel_lgm_sdxc_data,
	पूर्ण,
	अणु
		.compatible = "intel,keembay-sdhci-5.1-emmc",
		.data = &पूर्णांकel_keembay_emmc_data,
	पूर्ण,
	अणु
		.compatible = "intel,keembay-sdhci-5.1-sd",
		.data = &पूर्णांकel_keembay_sd_data,
	पूर्ण,
	अणु
		.compatible = "intel,keembay-sdhci-5.1-sdio",
		.data = &पूर्णांकel_keembay_sdio_data,
	पूर्ण,
	/* Generic compatible below here */
	अणु
		.compatible = "arasan,sdhci-8.9a",
		.data = &sdhci_arasan_generic_data,
	पूर्ण,
	अणु
		.compatible = "arasan,sdhci-5.1",
		.data = &sdhci_arasan_generic_data,
	पूर्ण,
	अणु
		.compatible = "arasan,sdhci-4.9a",
		.data = &sdhci_arasan_generic_data,
	पूर्ण,
	अणु
		.compatible = "xlnx,zynqmp-8.9a",
		.data = &sdhci_arasan_zynqmp_data,
	पूर्ण,
	अणु
		.compatible = "xlnx,versal-8.9a",
		.data = &sdhci_arasan_versal_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sdhci_arasan_of_match);

/**
 * sdhci_arasan_रेजिस्टर_sdcardclk - Register the sdcardclk क्रम a PHY to use
 *
 * @sdhci_arasan:	Our निजी data काष्ठाure.
 * @clk_xin:		Poपूर्णांकer to the functional घड़ी
 * @dev:		Poपूर्णांकer to our काष्ठा device.
 *
 * Some PHY devices need to know what the actual card घड़ी is.  In order क्रम
 * them to find out, we'll provide a घड़ी through the common घड़ी framework
 * क्रम them to query.
 *
 * Return: 0 on success and error value on error
 */
अटल पूर्णांक
sdhci_arasan_रेजिस्टर_sdcardclk(काष्ठा sdhci_arasan_data *sdhci_arasan,
				काष्ठा clk *clk_xin,
				काष्ठा device *dev)
अणु
	काष्ठा sdhci_arasan_clk_data *clk_data = &sdhci_arasan->clk_data;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा clk_init_data sdcardclk_init;
	स्थिर अक्षर *parent_clk_name;
	पूर्णांक ret;

	ret = of_property_पढ़ो_string_index(np, "clock-output-names", 0,
					    &sdcardclk_init.name);
	अगर (ret) अणु
		dev_err(dev, "DT has #clock-cells but no clock-output-names\n");
		वापस ret;
	पूर्ण

	parent_clk_name = __clk_get_name(clk_xin);
	sdcardclk_init.parent_names = &parent_clk_name;
	sdcardclk_init.num_parents = 1;
	sdcardclk_init.flags = CLK_GET_RATE_NOCACHE;
	sdcardclk_init.ops = sdhci_arasan->clk_ops->sdcardclk_ops;

	clk_data->sdcardclk_hw.init = &sdcardclk_init;
	clk_data->sdcardclk =
		devm_clk_रेजिस्टर(dev, &clk_data->sdcardclk_hw);
	अगर (IS_ERR(clk_data->sdcardclk))
		वापस PTR_ERR(clk_data->sdcardclk);
	clk_data->sdcardclk_hw.init = शून्य;

	ret = of_clk_add_provider(np, of_clk_src_simple_get,
				  clk_data->sdcardclk);
	अगर (ret)
		dev_err(dev, "Failed to add sdcard clock provider\n");

	वापस ret;
पूर्ण

/**
 * sdhci_arasan_रेजिस्टर_sampleclk - Register the sampleclk क्रम a PHY to use
 *
 * @sdhci_arasan:	Our निजी data काष्ठाure.
 * @clk_xin:		Poपूर्णांकer to the functional घड़ी
 * @dev:		Poपूर्णांकer to our काष्ठा device.
 *
 * Some PHY devices need to know what the actual card घड़ी is.  In order क्रम
 * them to find out, we'll provide a घड़ी through the common घड़ी framework
 * क्रम them to query.
 *
 * Return: 0 on success and error value on error
 */
अटल पूर्णांक
sdhci_arasan_रेजिस्टर_sampleclk(काष्ठा sdhci_arasan_data *sdhci_arasan,
				काष्ठा clk *clk_xin,
				काष्ठा device *dev)
अणु
	काष्ठा sdhci_arasan_clk_data *clk_data = &sdhci_arasan->clk_data;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा clk_init_data sampleclk_init;
	स्थिर अक्षर *parent_clk_name;
	पूर्णांक ret;

	ret = of_property_पढ़ो_string_index(np, "clock-output-names", 1,
					    &sampleclk_init.name);
	अगर (ret) अणु
		dev_err(dev, "DT has #clock-cells but no clock-output-names\n");
		वापस ret;
	पूर्ण

	parent_clk_name = __clk_get_name(clk_xin);
	sampleclk_init.parent_names = &parent_clk_name;
	sampleclk_init.num_parents = 1;
	sampleclk_init.flags = CLK_GET_RATE_NOCACHE;
	sampleclk_init.ops = sdhci_arasan->clk_ops->sampleclk_ops;

	clk_data->sampleclk_hw.init = &sampleclk_init;
	clk_data->sampleclk =
		devm_clk_रेजिस्टर(dev, &clk_data->sampleclk_hw);
	अगर (IS_ERR(clk_data->sampleclk))
		वापस PTR_ERR(clk_data->sampleclk);
	clk_data->sampleclk_hw.init = शून्य;

	ret = of_clk_add_provider(np, of_clk_src_simple_get,
				  clk_data->sampleclk);
	अगर (ret)
		dev_err(dev, "Failed to add sample clock provider\n");

	वापस ret;
पूर्ण

/**
 * sdhci_arasan_unरेजिस्टर_sdclk - Unकरोes sdhci_arasan_रेजिस्टर_sdclk()
 *
 * @dev:		Poपूर्णांकer to our काष्ठा device.
 *
 * Should be called any समय we're निकासing and sdhci_arasan_रेजिस्टर_sdclk()
 * वापसed success.
 */
अटल व्योम sdhci_arasan_unरेजिस्टर_sdclk(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;

	अगर (!of_find_property(np, "#clock-cells", शून्य))
		वापस;

	of_clk_del_provider(dev->of_node);
पूर्ण

/**
 * sdhci_arasan_update_support64b - Set SUPPORT_64B (64-bit System Bus Support)
 * @host:		The sdhci_host
 * @value:		The value to ग_लिखो
 *
 * This should be set based on the System Address Bus.
 * 0: the Core supports only 32-bit System Address Bus.
 * 1: the Core supports 64-bit System Address Bus.
 *
 * NOTE:
 * For Keem Bay, it is required to clear this bit. Its शेष value is 1'b1.
 * Keem Bay करोes not support 64-bit access.
 */
अटल व्योम sdhci_arasan_update_support64b(काष्ठा sdhci_host *host, u32 value)
अणु
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_arasan_data *sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	स्थिर काष्ठा sdhci_arasan_soc_ctl_map *soc_ctl_map;

	/* Having a map is optional */
	soc_ctl_map = sdhci_arasan->soc_ctl_map;
	अगर (!soc_ctl_map)
		वापस;

	/* If we have a map, we expect to have a syscon */
	अगर (!sdhci_arasan->soc_ctl_base) अणु
		pr_warn("%s: Have regmap, but no soc-ctl-syscon\n",
			mmc_hostname(host->mmc));
		वापस;
	पूर्ण

	sdhci_arasan_syscon_ग_लिखो(host, &soc_ctl_map->support64b, value);
पूर्ण

/**
 * sdhci_arasan_रेजिस्टर_sdclk - Register the sdcardclk क्रम a PHY to use
 *
 * @sdhci_arasan:	Our निजी data काष्ठाure.
 * @clk_xin:		Poपूर्णांकer to the functional घड़ी
 * @dev:		Poपूर्णांकer to our काष्ठा device.
 *
 * Some PHY devices need to know what the actual card घड़ी is.  In order क्रम
 * them to find out, we'll provide a घड़ी through the common घड़ी framework
 * क्रम them to query.
 *
 * Note: without seriously re-architecting SDHCI's घड़ी code and testing on
 * all platक्रमms, there's no way to create a totally beautअगरul घड़ी here
 * with all घड़ी ops implemented.  Instead, we'll just create a घड़ी that can
 * be queried and set the CLK_GET_RATE_NOCACHE attribute to tell common घड़ी
 * framework that we're करोing things behind its back.  This should be sufficient
 * to create nice clean device tree bindings and later (अगर needed) we can try
 * re-architecting SDHCI अगर we see some benefit to it.
 *
 * Return: 0 on success and error value on error
 */
अटल पूर्णांक sdhci_arasan_रेजिस्टर_sdclk(काष्ठा sdhci_arasan_data *sdhci_arasan,
				       काष्ठा clk *clk_xin,
				       काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	u32 num_clks = 0;
	पूर्णांक ret;

	/* Providing a घड़ी to the PHY is optional; no error अगर missing */
	अगर (of_property_पढ़ो_u32(np, "#clock-cells", &num_clks) < 0)
		वापस 0;

	ret = sdhci_arasan_रेजिस्टर_sdcardclk(sdhci_arasan, clk_xin, dev);
	अगर (ret)
		वापस ret;

	अगर (num_clks) अणु
		ret = sdhci_arasan_रेजिस्टर_sampleclk(sdhci_arasan, clk_xin,
						      dev);
		अगर (ret) अणु
			sdhci_arasan_unरेजिस्टर_sdclk(dev);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdhci_arasan_add_host(काष्ठा sdhci_arasan_data *sdhci_arasan)
अणु
	काष्ठा sdhci_host *host = sdhci_arasan->host;
	काष्ठा cqhci_host *cq_host;
	bool dma64;
	पूर्णांक ret;

	अगर (!sdhci_arasan->has_cqe)
		वापस sdhci_add_host(host);

	ret = sdhci_setup_host(host);
	अगर (ret)
		वापस ret;

	cq_host = devm_kzalloc(host->mmc->parent,
			       माप(*cq_host), GFP_KERNEL);
	अगर (!cq_host) अणु
		ret = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	cq_host->mmio = host->ioaddr + SDHCI_ARASAN_CQE_BASE_ADDR;
	cq_host->ops = &sdhci_arasan_cqhci_ops;

	dma64 = host->flags & SDHCI_USE_64_BIT_DMA;
	अगर (dma64)
		cq_host->caps |= CQHCI_TASK_DESC_SZ_128;

	ret = cqhci_init(cq_host, host->mmc, dma64);
	अगर (ret)
		जाओ cleanup;

	ret = __sdhci_add_host(host);
	अगर (ret)
		जाओ cleanup;

	वापस 0;

cleanup:
	sdhci_cleanup_host(host);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_arasan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा device_node *node;
	काष्ठा clk *clk_xin;
	काष्ठा sdhci_host *host;
	काष्ठा sdhci_pltfm_host *pltfm_host;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा sdhci_arasan_data *sdhci_arasan;
	स्थिर काष्ठा sdhci_arasan_of_data *data;

	data = of_device_get_match_data(dev);
	host = sdhci_pltfm_init(pdev, data->pdata, माप(*sdhci_arasan));

	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	pltfm_host = sdhci_priv(host);
	sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	sdhci_arasan->host = host;

	sdhci_arasan->soc_ctl_map = data->soc_ctl_map;
	sdhci_arasan->clk_ops = data->clk_ops;

	node = of_parse_phandle(np, "arasan,soc-ctl-syscon", 0);
	अगर (node) अणु
		sdhci_arasan->soc_ctl_base = syscon_node_to_regmap(node);
		of_node_put(node);

		अगर (IS_ERR(sdhci_arasan->soc_ctl_base)) अणु
			ret = dev_err_probe(dev,
					    PTR_ERR(sdhci_arasan->soc_ctl_base),
					    "Can't get syscon\n");
			जाओ err_pltfm_मुक्त;
		पूर्ण
	पूर्ण

	sdhci_arasan->clk_ahb = devm_clk_get(dev, "clk_ahb");
	अगर (IS_ERR(sdhci_arasan->clk_ahb)) अणु
		ret = dev_err_probe(dev, PTR_ERR(sdhci_arasan->clk_ahb),
				    "clk_ahb clock not found.\n");
		जाओ err_pltfm_मुक्त;
	पूर्ण

	clk_xin = devm_clk_get(dev, "clk_xin");
	अगर (IS_ERR(clk_xin)) अणु
		ret = dev_err_probe(dev, PTR_ERR(clk_xin), "clk_xin clock not found.\n");
		जाओ err_pltfm_मुक्त;
	पूर्ण

	ret = clk_prepare_enable(sdhci_arasan->clk_ahb);
	अगर (ret) अणु
		dev_err(dev, "Unable to enable AHB clock.\n");
		जाओ err_pltfm_मुक्त;
	पूर्ण

	ret = clk_prepare_enable(clk_xin);
	अगर (ret) अणु
		dev_err(dev, "Unable to enable SD clock.\n");
		जाओ clk_dis_ahb;
	पूर्ण

	sdhci_get_of_property(pdev);

	अगर (of_property_पढ़ो_bool(np, "xlnx,fails-without-test-cd"))
		sdhci_arasan->quirks |= SDHCI_ARASAN_QUIRK_FORCE_CDTEST;

	अगर (of_property_पढ़ो_bool(np, "xlnx,int-clock-stable-broken"))
		sdhci_arasan->quirks |= SDHCI_ARASAN_QUIRK_CLOCK_UNSTABLE;

	pltfm_host->clk = clk_xin;

	अगर (of_device_is_compatible(np, "rockchip,rk3399-sdhci-5.1"))
		sdhci_arasan_update_घड़ीmultiplier(host, 0x0);

	अगर (of_device_is_compatible(np, "intel,keembay-sdhci-5.1-emmc") ||
	    of_device_is_compatible(np, "intel,keembay-sdhci-5.1-sd") ||
	    of_device_is_compatible(np, "intel,keembay-sdhci-5.1-sdio")) अणु
		sdhci_arasan_update_घड़ीmultiplier(host, 0x0);
		sdhci_arasan_update_support64b(host, 0x0);

		host->mmc->caps |= MMC_CAP_WAIT_WHILE_BUSY;
	पूर्ण

	sdhci_arasan_update_baseclkfreq(host);

	ret = sdhci_arasan_रेजिस्टर_sdclk(sdhci_arasan, clk_xin, dev);
	अगर (ret)
		जाओ clk_disable_all;

	अगर (of_device_is_compatible(np, "xlnx,zynqmp-8.9a")) अणु
		host->mmc_host_ops.execute_tuning =
			arasan_zynqmp_execute_tuning;
	पूर्ण

	arasan_dt_parse_clk_phases(dev, &sdhci_arasan->clk_data);

	ret = mmc_of_parse(host->mmc);
	अगर (ret) अणु
		ret = dev_err_probe(dev, ret, "parsing dt failed.\n");
		जाओ unreg_clk;
	पूर्ण

	sdhci_arasan->phy = ERR_PTR(-ENODEV);
	अगर (of_device_is_compatible(np, "arasan,sdhci-5.1")) अणु
		sdhci_arasan->phy = devm_phy_get(dev, "phy_arasan");
		अगर (IS_ERR(sdhci_arasan->phy)) अणु
			ret = dev_err_probe(dev, PTR_ERR(sdhci_arasan->phy),
					    "No phy for arasan,sdhci-5.1.\n");
			जाओ unreg_clk;
		पूर्ण

		ret = phy_init(sdhci_arasan->phy);
		अगर (ret < 0) अणु
			dev_err(dev, "phy_init err.\n");
			जाओ unreg_clk;
		पूर्ण

		host->mmc_host_ops.hs400_enhanced_strobe =
					sdhci_arasan_hs400_enhanced_strobe;
		host->mmc_host_ops.start_संकेत_voltage_चयन =
					sdhci_arasan_voltage_चयन;
		sdhci_arasan->has_cqe = true;
		host->mmc->caps2 |= MMC_CAP2_CQE;

		अगर (!of_property_पढ़ो_bool(np, "disable-cqe-dcmd"))
			host->mmc->caps2 |= MMC_CAP2_CQE_DCMD;
	पूर्ण

	ret = sdhci_arasan_add_host(sdhci_arasan);
	अगर (ret)
		जाओ err_add_host;

	वापस 0;

err_add_host:
	अगर (!IS_ERR(sdhci_arasan->phy))
		phy_निकास(sdhci_arasan->phy);
unreg_clk:
	sdhci_arasan_unरेजिस्टर_sdclk(dev);
clk_disable_all:
	clk_disable_unprepare(clk_xin);
clk_dis_ahb:
	clk_disable_unprepare(sdhci_arasan->clk_ahb);
err_pltfm_मुक्त:
	sdhci_pltfm_मुक्त(pdev);
	वापस ret;
पूर्ण

अटल पूर्णांक sdhci_arasan_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा sdhci_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	काष्ठा sdhci_arasan_data *sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	काष्ठा clk *clk_ahb = sdhci_arasan->clk_ahb;

	अगर (!IS_ERR(sdhci_arasan->phy)) अणु
		अगर (sdhci_arasan->is_phy_on)
			phy_घातer_off(sdhci_arasan->phy);
		phy_निकास(sdhci_arasan->phy);
	पूर्ण

	sdhci_arasan_unरेजिस्टर_sdclk(&pdev->dev);

	ret = sdhci_pltfm_unरेजिस्टर(pdev);

	clk_disable_unprepare(clk_ahb);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver sdhci_arasan_driver = अणु
	.driver = अणु
		.name = "sdhci-arasan",
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
		.of_match_table = sdhci_arasan_of_match,
		.pm = &sdhci_arasan_dev_pm_ops,
	पूर्ण,
	.probe = sdhci_arasan_probe,
	.हटाओ = sdhci_arasan_हटाओ,
पूर्ण;

module_platक्रमm_driver(sdhci_arasan_driver);

MODULE_DESCRIPTION("Driver for the Arasan SDHCI Controller");
MODULE_AUTHOR("Soeren Brinkmann <soren.brinkmann@xilinx.com>");
MODULE_LICENSE("GPL");
