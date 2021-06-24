<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas SDHI
 *
 * Copyright (C) 2015-19 Renesas Electronics Corporation
 * Copyright (C) 2016-19 Sang Engineering, Wolfram Sang
 * Copyright (C) 2016-17 Horms Solutions, Simon Horman
 * Copyright (C) 2009 Magnus Damm
 *
 * Based on "Compaq ASIC3 support":
 *
 * Copyright 2001 Compaq Computer Corporation.
 * Copyright 2004-2005 Phil Blundell
 * Copyright 2007-2008 OpenedHand Ltd.
 *
 * Authors: Phil Blundell <pb@handhelds.org>,
 *	    Samuel Ortiz <sameo@खोलोedhand.com>
 *
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pinctrl/pinctrl-state.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/sh_dma.h>
#समावेश <linux/slab.h>
#समावेश <linux/sys_soc.h>

#समावेश "renesas_sdhi.h"
#समावेश "tmio_mmc.h"

#घोषणा CTL_HOST_MODE	0xe4
#घोषणा HOST_MODE_GEN2_SDR50_WMODE	BIT(0)
#घोषणा HOST_MODE_GEN2_SDR104_WMODE	BIT(0)
#घोषणा HOST_MODE_GEN3_WMODE		BIT(0)
#घोषणा HOST_MODE_GEN3_BUSWIDTH		BIT(8)

#घोषणा HOST_MODE_GEN3_16BIT	HOST_MODE_GEN3_WMODE
#घोषणा HOST_MODE_GEN3_32BIT	(HOST_MODE_GEN3_WMODE | HOST_MODE_GEN3_BUSWIDTH)
#घोषणा HOST_MODE_GEN3_64BIT	0

#घोषणा CTL_SDIF_MODE	0xe6
#घोषणा SDIF_MODE_HS400		BIT(0)

#घोषणा SDHI_VER_GEN2_SDR50	0x490c
#घोषणा SDHI_VER_RZ_A1		0x820b
/* very old datasheets said 0x490c क्रम SDR104, too. They are wrong! */
#घोषणा SDHI_VER_GEN2_SDR104	0xcb0d
#घोषणा SDHI_VER_GEN3_SD	0xcc10
#घोषणा SDHI_VER_GEN3_SDMMC	0xcd10

#घोषणा SDHI_GEN3_MMC0_ADDR	0xee140000

अटल व्योम renesas_sdhi_sdbuf_width(काष्ठा पंचांगio_mmc_host *host, पूर्णांक width)
अणु
	u32 val;

	/*
	 * see also
	 *	renesas_sdhi_of_data :: dma_buswidth
	 */
	चयन (sd_ctrl_पढ़ो16(host, CTL_VERSION)) अणु
	हाल SDHI_VER_GEN2_SDR50:
		val = (width == 32) ? HOST_MODE_GEN2_SDR50_WMODE : 0;
		अवरोध;
	हाल SDHI_VER_GEN2_SDR104:
		val = (width == 32) ? 0 : HOST_MODE_GEN2_SDR104_WMODE;
		अवरोध;
	हाल SDHI_VER_GEN3_SD:
	हाल SDHI_VER_GEN3_SDMMC:
		अगर (width == 64)
			val = HOST_MODE_GEN3_64BIT;
		अन्यथा अगर (width == 32)
			val = HOST_MODE_GEN3_32BIT;
		अन्यथा
			val = HOST_MODE_GEN3_16BIT;
		अवरोध;
	शेष:
		/* nothing to करो */
		वापस;
	पूर्ण

	sd_ctrl_ग_लिखो16(host, CTL_HOST_MODE, val);
पूर्ण

अटल पूर्णांक renesas_sdhi_clk_enable(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा mmc_host *mmc = host->mmc;
	काष्ठा renesas_sdhi *priv = host_to_priv(host);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->clk_cd);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The घड़ी driver may not know what maximum frequency
	 * actually works, so it should be set with the max-frequency
	 * property which will alपढ़ोy have been पढ़ो to f_max.  If it
	 * was missing, assume the current frequency is the maximum.
	 */
	अगर (!mmc->f_max)
		mmc->f_max = clk_get_rate(priv->clk);

	/*
	 * Minimum frequency is the minimum input घड़ी frequency
	 * भागided by our maximum भागider.
	 */
	mmc->f_min = max(clk_round_rate(priv->clk, 1) / 512, 1L);

	/* enable 16bit data access on SDBUF as शेष */
	renesas_sdhi_sdbuf_width(host, 16);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक renesas_sdhi_clk_update(काष्ठा पंचांगio_mmc_host *host,
					    अचिन्हित पूर्णांक new_घड़ी)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);
	अचिन्हित पूर्णांक freq, dअगरf, best_freq = 0, dअगरf_min = ~0;
	पूर्णांक i;

	/*
	 * We simply वापस the current rate अगर a) we are not on a R-Car Gen2+
	 * SoC (may work क्रम others, but untested) or b) अगर the SCC needs its
	 * घड़ी during tuning, so we करोn't change the बाह्यal घड़ी setup.
	 */
	अगर (!(host->pdata->flags & TMIO_MMC_MIN_RCAR2) || mmc_करोing_tune(host->mmc))
		वापस clk_get_rate(priv->clk);

	/*
	 * We want the bus घड़ी to be as बंद as possible to, but no
	 * greater than, new_घड़ी.  As we can भागide by 1 << i क्रम
	 * any i in [0, 9] we want the input घड़ी to be as बंद as
	 * possible, but no greater than, new_घड़ी << i.
	 */
	क्रम (i = min(9, ilog2(अच_पूर्णांक_उच्च / new_घड़ी)); i >= 0; i--) अणु
		freq = clk_round_rate(priv->clk, new_घड़ी << i);
		अगर (freq > (new_घड़ी << i)) अणु
			/* Too fast; look क्रम a slightly slower option */
			freq = clk_round_rate(priv->clk,
					      (new_घड़ी << i) / 4 * 3);
			अगर (freq > (new_घड़ी << i))
				जारी;
		पूर्ण

		dअगरf = new_घड़ी - (freq >> i);
		अगर (dअगरf <= dअगरf_min) अणु
			best_freq = freq;
			dअगरf_min = dअगरf;
		पूर्ण
	पूर्ण

	clk_set_rate(priv->clk, best_freq);

	वापस clk_get_rate(priv->clk);
पूर्ण

अटल व्योम renesas_sdhi_set_घड़ी(काष्ठा पंचांगio_mmc_host *host,
				   अचिन्हित पूर्णांक new_घड़ी)
अणु
	u32 clk = 0, घड़ी;

	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, ~CLK_CTL_SCLKEN &
		sd_ctrl_पढ़ो16(host, CTL_SD_CARD_CLK_CTL));

	अगर (new_घड़ी == 0) अणु
		host->mmc->actual_घड़ी = 0;
		जाओ out;
	पूर्ण

	host->mmc->actual_घड़ी = renesas_sdhi_clk_update(host, new_घड़ी);
	घड़ी = host->mmc->actual_घड़ी / 512;

	क्रम (clk = 0x80000080; new_घड़ी >= (घड़ी << 1); clk >>= 1)
		घड़ी <<= 1;

	/* 1/1 घड़ी is option */
	अगर ((host->pdata->flags & TMIO_MMC_CLK_ACTUAL) && ((clk >> 22) & 0x1)) अणु
		अगर (!(host->mmc->ios.timing == MMC_TIMING_MMC_HS400))
			clk |= 0xff;
		अन्यथा
			clk &= ~0xff;
	पूर्ण

	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, clk & CLK_CTL_DIV_MASK);
	अगर (!(host->pdata->flags & TMIO_MMC_MIN_RCAR2))
		usleep_range(10000, 11000);

	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, CLK_CTL_SCLKEN |
		sd_ctrl_पढ़ो16(host, CTL_SD_CARD_CLK_CTL));

out:
	/* HW engineers overrode करोcs: no sleep needed on R-Car2+ */
	अगर (!(host->pdata->flags & TMIO_MMC_MIN_RCAR2))
		usleep_range(10000, 11000);
पूर्ण

अटल व्योम renesas_sdhi_clk_disable(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);

	clk_disable_unprepare(priv->clk_cd);
पूर्ण

अटल पूर्णांक renesas_sdhi_card_busy(काष्ठा mmc_host *mmc)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);

	वापस !(sd_ctrl_पढ़ो16_and_16_as_32(host, CTL_STATUS) &
		 TMIO_STAT_DAT0);
पूर्ण

अटल पूर्णांक renesas_sdhi_start_संकेत_voltage_चयन(काष्ठा mmc_host *mmc,
						    काष्ठा mmc_ios *ios)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);
	काष्ठा renesas_sdhi *priv = host_to_priv(host);
	काष्ठा pinctrl_state *pin_state;
	पूर्णांक ret;

	चयन (ios->संकेत_voltage) अणु
	हाल MMC_SIGNAL_VOLTAGE_330:
		pin_state = priv->pins_शेष;
		अवरोध;
	हाल MMC_SIGNAL_VOLTAGE_180:
		pin_state = priv->pins_uhs;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * If anything is missing, assume संकेत voltage is fixed at
	 * 3.3V and succeed/fail accordingly.
	 */
	अगर (IS_ERR(priv->pinctrl) || IS_ERR(pin_state))
		वापस ios->संकेत_voltage ==
			MMC_SIGNAL_VOLTAGE_330 ? 0 : -EINVAL;

	ret = mmc_regulator_set_vqmmc(host->mmc, ios);
	अगर (ret < 0)
		वापस ret;

	वापस pinctrl_select_state(priv->pinctrl, pin_state);
पूर्ण

/* SCC रेजिस्टरs */
#घोषणा SH_MOBILE_SDHI_SCC_DTCNTL	0x000
#घोषणा SH_MOBILE_SDHI_SCC_TAPSET	0x002
#घोषणा SH_MOBILE_SDHI_SCC_DT2FF	0x004
#घोषणा SH_MOBILE_SDHI_SCC_CKSEL	0x006
#घोषणा SH_MOBILE_SDHI_SCC_RVSCNTL	0x008
#घोषणा SH_MOBILE_SDHI_SCC_RVSREQ	0x00A
#घोषणा SH_MOBILE_SDHI_SCC_SMPCMP       0x00C
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT2	0x00E
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT3	0x014
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT4	0x016
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT5	0x018
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT6	0x01A
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT7	0x01C

#घोषणा SH_MOBILE_SDHI_SCC_DTCNTL_TAPEN		BIT(0)
#घोषणा SH_MOBILE_SDHI_SCC_DTCNTL_TAPNUM_SHIFT	16
#घोषणा SH_MOBILE_SDHI_SCC_DTCNTL_TAPNUM_MASK	0xff

#घोषणा SH_MOBILE_SDHI_SCC_CKSEL_DTSEL		BIT(0)

#घोषणा SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN	BIT(0)

#घोषणा SH_MOBILE_SDHI_SCC_RVSREQ_REQTAPDOWN	BIT(0)
#घोषणा SH_MOBILE_SDHI_SCC_RVSREQ_REQTAPUP	BIT(1)
#घोषणा SH_MOBILE_SDHI_SCC_RVSREQ_RVSERR	BIT(2)

#घोषणा SH_MOBILE_SDHI_SCC_SMPCMP_CMD_REQDOWN	BIT(8)
#घोषणा SH_MOBILE_SDHI_SCC_SMPCMP_CMD_REQUP	BIT(24)
#घोषणा SH_MOBILE_SDHI_SCC_SMPCMP_CMD_ERR	(BIT(8) | BIT(24))

#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT2_HS400OSEL	BIT(4)
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT2_HS400EN	BIT(31)

/* Definitions क्रम values the SH_MOBILE_SDHI_SCC_TMPPORT4 रेजिस्टर */
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT4_DLL_ACC_START	BIT(0)

/* Definitions क्रम values the SH_MOBILE_SDHI_SCC_TMPPORT5 रेजिस्टर */
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT5_DLL_RW_SEL_R	BIT(8)
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT5_DLL_RW_SEL_W	(0 << 8)
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT5_DLL_ADR_MASK	0x3F

/* Definitions क्रम values the SH_MOBILE_SDHI_SCC रेजिस्टर */
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT_DISABLE_WP_CODE	0xa5000000
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT_CALIB_CODE_MASK	0x1f
#घोषणा SH_MOBILE_SDHI_SCC_TMPPORT_MANUAL_MODE		BIT(7)

अटल स्थिर u8 r8a7796_es13_calib_table[2][SDHI_CALIB_TABLE_MAX] = अणु
	अणु 3,  3,  3,  3,  3,  3,  3,  4,  4,  5,  6,  7,  8,  9, 10, 15,
	 16, 16, 16, 16, 16, 16, 17, 18, 18, 19, 20, 21, 22, 23, 24, 25 पूर्ण,
	अणु 5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  6,  7,  8, 11,
	 12, 17, 18, 18, 18, 18, 18, 18, 18, 19, 20, 21, 22, 23, 25, 25 पूर्ण
पूर्ण;

अटल स्थिर u8 r8a77965_calib_table[2][SDHI_CALIB_TABLE_MAX] = अणु
	अणु 1,  2,  6,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 15, 15, 16,
	 17, 18, 19, 20, 21, 22, 23, 24, 25, 25, 26, 27, 28, 29, 30, 31 पूर्ण,
	अणु 2,  3,  4,  4,  5,  6,  7,  9, 10, 11, 12, 13, 14, 15, 16, 17,
	 17, 17, 20, 21, 22, 23, 24, 25, 27, 28, 29, 30, 31, 31, 31, 31 पूर्ण
पूर्ण;

अटल स्थिर u8 r8a77990_calib_table[2][SDHI_CALIB_TABLE_MAX] = अणु
	अणु 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 पूर्ण,
	अणु 0,  0,  0,  1,  2,  3,  3,  4,  4,  4,  5,  5,  6,  8,  9, 10,
	 11, 12, 13, 15, 16, 17, 17, 18, 18, 19, 20, 22, 24, 25, 26, 26 पूर्ण
पूर्ण;

अटल अंतरभूत u32 sd_scc_पढ़ो32(काष्ठा पंचांगio_mmc_host *host,
				काष्ठा renesas_sdhi *priv, पूर्णांक addr)
अणु
	वापस पढ़ोl(priv->scc_ctl + (addr << host->bus_shअगरt));
पूर्ण

अटल अंतरभूत व्योम sd_scc_ग_लिखो32(काष्ठा पंचांगio_mmc_host *host,
				  काष्ठा renesas_sdhi *priv,
				  पूर्णांक addr, u32 val)
अणु
	ग_लिखोl(val, priv->scc_ctl + (addr << host->bus_shअगरt));
पूर्ण

अटल अचिन्हित पूर्णांक renesas_sdhi_init_tuning(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा renesas_sdhi *priv;

	priv = host_to_priv(host);

	/* Initialize SCC */
	sd_ctrl_ग_लिखो32_as_16_and_16(host, CTL_STATUS, 0x0);

	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, ~CLK_CTL_SCLKEN &
			sd_ctrl_पढ़ो16(host, CTL_SD_CARD_CLK_CTL));

	/* set sampling घड़ी selection range */
	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_DTCNTL,
		       SH_MOBILE_SDHI_SCC_DTCNTL_TAPEN |
		       0x8 << SH_MOBILE_SDHI_SCC_DTCNTL_TAPNUM_SHIFT);

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_CKSEL,
		       SH_MOBILE_SDHI_SCC_CKSEL_DTSEL |
		       sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_CKSEL));

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL,
		       ~SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN &
		       sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL));

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_DT2FF, priv->scc_tappos);

	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, CLK_CTL_SCLKEN |
			sd_ctrl_पढ़ो16(host, CTL_SD_CARD_CLK_CTL));

	/* Read TAPNUM */
	वापस (sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_DTCNTL) >>
		SH_MOBILE_SDHI_SCC_DTCNTL_TAPNUM_SHIFT) &
		SH_MOBILE_SDHI_SCC_DTCNTL_TAPNUM_MASK;
पूर्ण

अटल व्योम renesas_sdhi_hs400_complete(काष्ठा mmc_host *mmc)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);
	काष्ठा renesas_sdhi *priv = host_to_priv(host);
	u32 bad_taps = priv->quirks ? priv->quirks->hs400_bad_taps : 0;
	bool use_4tap = priv->quirks && priv->quirks->hs400_4taps;

	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, ~CLK_CTL_SCLKEN &
		sd_ctrl_पढ़ो16(host, CTL_SD_CARD_CLK_CTL));

	/* Set HS400 mode */
	sd_ctrl_ग_लिखो16(host, CTL_SDIF_MODE, SDIF_MODE_HS400 |
			sd_ctrl_पढ़ो16(host, CTL_SDIF_MODE));

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_DT2FF,
		       priv->scc_tappos_hs400);

	/* Gen3 can't करो स्वतःmatic tap correction with HS400, so disable it */
	अगर (sd_ctrl_पढ़ो16(host, CTL_VERSION) == SDHI_VER_GEN3_SDMMC)
		sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL,
			       ~SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN &
			       sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL));

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT2,
		       (SH_MOBILE_SDHI_SCC_TMPPORT2_HS400EN |
			SH_MOBILE_SDHI_SCC_TMPPORT2_HS400OSEL) |
			sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT2));

	/* Set the sampling घड़ी selection range of HS400 mode */
	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_DTCNTL,
		       SH_MOBILE_SDHI_SCC_DTCNTL_TAPEN |
		       0x4 << SH_MOBILE_SDHI_SCC_DTCNTL_TAPNUM_SHIFT);

	/* Aव्योम bad TAP */
	अगर (bad_taps & BIT(priv->tap_set)) अणु
		u32 new_tap = (priv->tap_set + 1) % priv->tap_num;

		अगर (bad_taps & BIT(new_tap))
			new_tap = (priv->tap_set - 1) % priv->tap_num;

		अगर (bad_taps & BIT(new_tap)) अणु
			new_tap = priv->tap_set;
			dev_dbg(&host->pdev->dev, "Can't handle three bad tap in a row\n");
		पूर्ण

		priv->tap_set = new_tap;
	पूर्ण

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TAPSET,
		       priv->tap_set / (use_4tap ? 2 : 1));

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_CKSEL,
		       SH_MOBILE_SDHI_SCC_CKSEL_DTSEL |
		       sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_CKSEL));

	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, CLK_CTL_SCLKEN |
			sd_ctrl_पढ़ो16(host, CTL_SD_CARD_CLK_CTL));

	अगर (priv->adjust_hs400_calib_table)
		priv->needs_adjust_hs400 = true;
पूर्ण

अटल व्योम renesas_sdhi_disable_scc(काष्ठा mmc_host *mmc)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);
	काष्ठा renesas_sdhi *priv = host_to_priv(host);

	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, ~CLK_CTL_SCLKEN &
			sd_ctrl_पढ़ो16(host, CTL_SD_CARD_CLK_CTL));

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_CKSEL,
		       ~SH_MOBILE_SDHI_SCC_CKSEL_DTSEL &
		       sd_scc_पढ़ो32(host, priv,
				     SH_MOBILE_SDHI_SCC_CKSEL));

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_DTCNTL,
		       ~SH_MOBILE_SDHI_SCC_DTCNTL_TAPEN &
		       sd_scc_पढ़ो32(host, priv,
				     SH_MOBILE_SDHI_SCC_DTCNTL));

	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, CLK_CTL_SCLKEN |
			sd_ctrl_पढ़ो16(host, CTL_SD_CARD_CLK_CTL));
पूर्ण

अटल u32 sd_scc_पंचांगpport_पढ़ो32(काष्ठा पंचांगio_mmc_host *host,
				 काष्ठा renesas_sdhi *priv, u32 addr)
अणु
	/* पढ़ो mode */
	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT5,
		       SH_MOBILE_SDHI_SCC_TMPPORT5_DLL_RW_SEL_R |
		       (SH_MOBILE_SDHI_SCC_TMPPORT5_DLL_ADR_MASK & addr));

	/* access start and stop */
	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT4,
		       SH_MOBILE_SDHI_SCC_TMPPORT4_DLL_ACC_START);
	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT4, 0);

	वापस sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT7);
पूर्ण

अटल व्योम sd_scc_पंचांगpport_ग_लिखो32(काष्ठा पंचांगio_mmc_host *host,
				   काष्ठा renesas_sdhi *priv, u32 addr, u32 val)
अणु
	/* ग_लिखो mode */
	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT5,
		       SH_MOBILE_SDHI_SCC_TMPPORT5_DLL_RW_SEL_W |
		       (SH_MOBILE_SDHI_SCC_TMPPORT5_DLL_ADR_MASK & addr));

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT6, val);

	/* access start and stop */
	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT4,
		       SH_MOBILE_SDHI_SCC_TMPPORT4_DLL_ACC_START);
	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT4, 0);
पूर्ण

अटल व्योम renesas_sdhi_adjust_hs400_mode_enable(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);
	u32 calib_code;

	/* disable ग_लिखो protect */
	sd_scc_पंचांगpport_ग_लिखो32(host, priv, 0x00,
			       SH_MOBILE_SDHI_SCC_TMPPORT_DISABLE_WP_CODE);
	/* पढ़ो calibration code and adjust */
	calib_code = sd_scc_पंचांगpport_पढ़ो32(host, priv, 0x26);
	calib_code &= SH_MOBILE_SDHI_SCC_TMPPORT_CALIB_CODE_MASK;

	sd_scc_पंचांगpport_ग_लिखो32(host, priv, 0x22,
			       SH_MOBILE_SDHI_SCC_TMPPORT_MANUAL_MODE |
			       priv->adjust_hs400_calib_table[calib_code]);

	/* set offset value to TMPPORT3, hardcoded to OFFSET0 (= 0x3) क्रम now */
	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT3, 0x3);

	/* adjusपंचांगent करोne, clear flag */
	priv->needs_adjust_hs400 = false;
पूर्ण

अटल व्योम renesas_sdhi_adjust_hs400_mode_disable(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);

	/* disable ग_लिखो protect */
	sd_scc_पंचांगpport_ग_लिखो32(host, priv, 0x00,
			       SH_MOBILE_SDHI_SCC_TMPPORT_DISABLE_WP_CODE);
	/* disable manual calibration */
	sd_scc_पंचांगpport_ग_लिखो32(host, priv, 0x22, 0);
	/* clear offset value of TMPPORT3 */
	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT3, 0);
पूर्ण

अटल व्योम renesas_sdhi_reset_hs400_mode(काष्ठा पंचांगio_mmc_host *host,
					  काष्ठा renesas_sdhi *priv)
अणु
	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, ~CLK_CTL_SCLKEN &
			sd_ctrl_पढ़ो16(host, CTL_SD_CARD_CLK_CTL));

	/* Reset HS400 mode */
	sd_ctrl_ग_लिखो16(host, CTL_SDIF_MODE, ~SDIF_MODE_HS400 &
			sd_ctrl_पढ़ो16(host, CTL_SDIF_MODE));

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_DT2FF, priv->scc_tappos);

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT2,
		       ~(SH_MOBILE_SDHI_SCC_TMPPORT2_HS400EN |
			 SH_MOBILE_SDHI_SCC_TMPPORT2_HS400OSEL) &
			sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_TMPPORT2));

	अगर (priv->adjust_hs400_calib_table)
		renesas_sdhi_adjust_hs400_mode_disable(host);

	sd_ctrl_ग_लिखो16(host, CTL_SD_CARD_CLK_CTL, CLK_CTL_SCLKEN |
			sd_ctrl_पढ़ो16(host, CTL_SD_CARD_CLK_CTL));
पूर्ण

अटल पूर्णांक renesas_sdhi_prepare_hs400_tuning(काष्ठा mmc_host *mmc, काष्ठा mmc_ios *ios)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);

	renesas_sdhi_reset_hs400_mode(host, host_to_priv(host));
	वापस 0;
पूर्ण

अटल व्योम renesas_sdhi_scc_reset(काष्ठा पंचांगio_mmc_host *host, काष्ठा renesas_sdhi *priv)
अणु
	renesas_sdhi_disable_scc(host->mmc);
	renesas_sdhi_reset_hs400_mode(host, priv);
	priv->needs_adjust_hs400 = false;

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL,
		       ~SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN &
		       sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL));
पूर्ण

/* only populated क्रम TMIO_MMC_MIN_RCAR2 */
अटल व्योम renesas_sdhi_reset(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);
	पूर्णांक ret;
	u16 val;

	अगर (priv->rstc) अणु
		reset_control_reset(priv->rstc);
		/* Unknown why but without polling reset status, it will hang */
		पढ़ो_poll_समयout(reset_control_status, ret, ret == 0, 1, 100,
				  false, priv->rstc);
		priv->needs_adjust_hs400 = false;
		renesas_sdhi_set_घड़ी(host, host->clk_cache);
	पूर्ण अन्यथा अगर (priv->scc_ctl) अणु
		renesas_sdhi_scc_reset(host, priv);
	पूर्ण

	अगर (sd_ctrl_पढ़ो16(host, CTL_VERSION) >= SDHI_VER_GEN3_SD) अणु
		val = sd_ctrl_पढ़ो16(host, CTL_SD_MEM_CARD_OPT);
		val |= CARD_OPT_EXTOP;
		sd_ctrl_ग_लिखो16(host, CTL_SD_MEM_CARD_OPT, val);
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक renesas_sdhi_gen3_get_cycles(काष्ठा पंचांगio_mmc_host *host)
अणु
	u16 num, val = sd_ctrl_पढ़ो16(host, CTL_SD_MEM_CARD_OPT);

	num = (val & CARD_OPT_TOP_MASK) >> CARD_OPT_TOP_SHIFT;
	वापस 1 << ((val & CARD_OPT_EXTOP ? 14 : 13) + num);

पूर्ण

#घोषणा SH_MOBILE_SDHI_MIN_TAP_ROW 3

अटल पूर्णांक renesas_sdhi_select_tuning(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);
	अचिन्हित पूर्णांक tap_start = 0, tap_end = 0, tap_cnt = 0, rs, re, i;
	अचिन्हित पूर्णांक taps_size = priv->tap_num * 2, min_tap_row;
	अचिन्हित दीर्घ *biपंचांगap;

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_RVSREQ, 0);

	/*
	 * When tuning CMD19 is issued twice क्रम each tap, merge the
	 * result requiring the tap to be good in both runs beक्रमe
	 * considering it क्रम tuning selection.
	 */
	क्रम (i = 0; i < taps_size; i++) अणु
		पूर्णांक offset = priv->tap_num * (i < priv->tap_num ? 1 : -1);

		अगर (!test_bit(i, priv->taps))
			clear_bit(i + offset, priv->taps);

		अगर (!test_bit(i, priv->smpcmp))
			clear_bit(i + offset, priv->smpcmp);
	पूर्ण

	/*
	 * If all TAP are OK, the sampling घड़ी position is selected by
	 * identअगरying the change poपूर्णांक of data.
	 */
	अगर (biपंचांगap_full(priv->taps, taps_size)) अणु
		biपंचांगap = priv->smpcmp;
		min_tap_row = 1;
	पूर्ण अन्यथा अणु
		biपंचांगap = priv->taps;
		min_tap_row = SH_MOBILE_SDHI_MIN_TAP_ROW;
	पूर्ण

	/*
	 * Find the दीर्घest consecutive run of successful probes. If that
	 * is at least SH_MOBILE_SDHI_MIN_TAP_ROW probes दीर्घ then use the
	 * center index as the tap, otherwise bail out.
	 */
	biपंचांगap_क्रम_each_set_region(biपंचांगap, rs, re, 0, taps_size) अणु
		अगर (re - rs > tap_cnt) अणु
			tap_end = re;
			tap_start = rs;
			tap_cnt = tap_end - tap_start;
		पूर्ण
	पूर्ण

	अगर (tap_cnt >= min_tap_row)
		priv->tap_set = (tap_start + tap_end) / 2 % priv->tap_num;
	अन्यथा
		वापस -EIO;

	/* Set SCC */
	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TAPSET, priv->tap_set);

	/* Enable स्वतः re-tuning */
	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL,
		       SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN |
		       sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL));

	वापस 0;
पूर्ण

अटल पूर्णांक renesas_sdhi_execute_tuning(काष्ठा mmc_host *mmc, u32 opcode)
अणु
	काष्ठा पंचांगio_mmc_host *host = mmc_priv(mmc);
	काष्ठा renesas_sdhi *priv = host_to_priv(host);
	पूर्णांक i, ret;

	priv->tap_num = renesas_sdhi_init_tuning(host);
	अगर (!priv->tap_num)
		वापस 0; /* Tuning is not supported */

	अगर (priv->tap_num * 2 >= माप(priv->taps) * BITS_PER_BYTE) अणु
		dev_err(&host->pdev->dev,
			"Too many taps, please update 'taps' in tmio_mmc_host!\n");
		वापस -EINVAL;
	पूर्ण

	biपंचांगap_zero(priv->taps, priv->tap_num * 2);
	biपंचांगap_zero(priv->smpcmp, priv->tap_num * 2);

	/* Issue CMD19 twice क्रम each tap */
	क्रम (i = 0; i < 2 * priv->tap_num; i++) अणु
		पूर्णांक cmd_error;

		/* Set sampling घड़ी position */
		sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TAPSET, i % priv->tap_num);

		अगर (mmc_send_tuning(mmc, opcode, &cmd_error) == 0)
			set_bit(i, priv->taps);

		अगर (sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_SMPCMP) == 0)
			set_bit(i, priv->smpcmp);

		अगर (cmd_error)
			mmc_पात_tuning(mmc, opcode);
	पूर्ण

	ret = renesas_sdhi_select_tuning(host);
	अगर (ret < 0)
		renesas_sdhi_scc_reset(host, priv);
	वापस ret;
पूर्ण

अटल bool renesas_sdhi_manual_correction(काष्ठा पंचांगio_mmc_host *host, bool use_4tap)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);
	अचिन्हित पूर्णांक new_tap = priv->tap_set, error_tap = priv->tap_set;
	u32 val;

	val = sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_RVSREQ);
	अगर (!val)
		वापस false;

	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_RVSREQ, 0);

	/* Change TAP position according to correction status */
	अगर (sd_ctrl_पढ़ो16(host, CTL_VERSION) == SDHI_VER_GEN3_SDMMC &&
	    host->mmc->ios.timing == MMC_TIMING_MMC_HS400) अणु
		u32 bad_taps = priv->quirks ? priv->quirks->hs400_bad_taps : 0;
		/*
		 * With HS400, the DAT संकेत is based on DS, not CLK.
		 * Thereक्रमe, use only CMD status.
		 */
		u32 smpcmp = sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_SMPCMP) &
					   SH_MOBILE_SDHI_SCC_SMPCMP_CMD_ERR;
		अगर (!smpcmp) अणु
			वापस false;	/* no error in CMD संकेत */
		पूर्ण अन्यथा अगर (smpcmp == SH_MOBILE_SDHI_SCC_SMPCMP_CMD_REQUP) अणु
			new_tap++;
			error_tap--;
		पूर्ण अन्यथा अगर (smpcmp == SH_MOBILE_SDHI_SCC_SMPCMP_CMD_REQDOWN) अणु
			new_tap--;
			error_tap++;
		पूर्ण अन्यथा अणु
			वापस true;	/* need retune */
		पूर्ण

		/*
		 * When new_tap is a bad tap, we cannot change. Then, we compare
		 * with the HS200 tuning result. When smpcmp[error_tap] is OK,
		 * we can at least retune.
		 */
		अगर (bad_taps & BIT(new_tap % priv->tap_num))
			वापस test_bit(error_tap % priv->tap_num, priv->smpcmp);
	पूर्ण अन्यथा अणु
		अगर (val & SH_MOBILE_SDHI_SCC_RVSREQ_RVSERR)
			वापस true;    /* need retune */
		अन्यथा अगर (val & SH_MOBILE_SDHI_SCC_RVSREQ_REQTAPUP)
			new_tap++;
		अन्यथा अगर (val & SH_MOBILE_SDHI_SCC_RVSREQ_REQTAPDOWN)
			new_tap--;
		अन्यथा
			वापस false;
	पूर्ण

	priv->tap_set = (new_tap % priv->tap_num);
	sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_TAPSET,
		       priv->tap_set / (use_4tap ? 2 : 1));

	वापस false;
पूर्ण

अटल bool renesas_sdhi_स्वतः_correction(काष्ठा पंचांगio_mmc_host *host)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);

	/* Check SCC error */
	अगर (sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_RVSREQ) &
	    SH_MOBILE_SDHI_SCC_RVSREQ_RVSERR) अणु
		sd_scc_ग_लिखो32(host, priv, SH_MOBILE_SDHI_SCC_RVSREQ, 0);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool renesas_sdhi_check_scc_error(काष्ठा पंचांगio_mmc_host *host,
					 काष्ठा mmc_request *mrq)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);
	bool use_4tap = priv->quirks && priv->quirks->hs400_4taps;
	bool ret = false;

	/*
	 * Skip checking SCC errors when running on 4 taps in HS400 mode as
	 * any retuning would still result in the same 4 taps being used.
	 */
	अगर (!(host->mmc->ios.timing == MMC_TIMING_UHS_SDR104) &&
	    !(host->mmc->ios.timing == MMC_TIMING_MMC_HS200) &&
	    !(host->mmc->ios.timing == MMC_TIMING_MMC_HS400 && !use_4tap))
		वापस false;

	अगर (mmc_करोing_tune(host->mmc))
		वापस false;

	अगर (((mrq->cmd->error == -ETIMEDOUT) ||
	     (mrq->data && mrq->data->error == -ETIMEDOUT)) &&
	    ((host->mmc->caps & MMC_CAP_NONREMOVABLE) ||
	     (host->ops.get_cd && host->ops.get_cd(host->mmc))))
		ret |= true;

	अगर (sd_scc_पढ़ो32(host, priv, SH_MOBILE_SDHI_SCC_RVSCNTL) &
	    SH_MOBILE_SDHI_SCC_RVSCNTL_RVSEN)
		ret |= renesas_sdhi_स्वतः_correction(host);
	अन्यथा
		ret |= renesas_sdhi_manual_correction(host, use_4tap);

	वापस ret;
पूर्ण

अटल पूर्णांक renesas_sdhi_रुको_idle(काष्ठा पंचांगio_mmc_host *host, u32 bit)
अणु
	पूर्णांक समयout = 1000;
	/* CBSY is set when busy, SCLKDIVEN is cleared when busy */
	u32 रुको_state = (bit == TMIO_STAT_CMD_BUSY ? TMIO_STAT_CMD_BUSY : 0);

	जबतक (--समयout && (sd_ctrl_पढ़ो16_and_16_as_32(host, CTL_STATUS)
			      & bit) == रुको_state)
		udelay(1);

	अगर (!समयout) अणु
		dev_warn(&host->pdev->dev, "timeout waiting for SD bus idle\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक renesas_sdhi_ग_लिखो16_hook(काष्ठा पंचांगio_mmc_host *host, पूर्णांक addr)
अणु
	u32 bit = TMIO_STAT_SCLKDIVEN;

	चयन (addr) अणु
	हाल CTL_SD_CMD:
	हाल CTL_STOP_INTERNAL_ACTION:
	हाल CTL_XFER_BLK_COUNT:
	हाल CTL_SD_XFER_LEN:
	हाल CTL_SD_MEM_CARD_OPT:
	हाल CTL_TRANSACTION_CTL:
	हाल CTL_DMA_ENABLE:
	हाल CTL_HOST_MODE:
		अगर (host->pdata->flags & TMIO_MMC_HAVE_CBSY)
			bit = TMIO_STAT_CMD_BUSY;
		fallthrough;
	हाल CTL_SD_CARD_CLK_CTL:
		वापस renesas_sdhi_रुको_idle(host, bit);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक renesas_sdhi_multi_io_quirk(काष्ठा mmc_card *card,
				       अचिन्हित पूर्णांक direction, पूर्णांक blk_size)
अणु
	/*
	 * In Renesas controllers, when perक्रमming a
	 * multiple block पढ़ो of one or two blocks,
	 * depending on the timing with which the
	 * response रेजिस्टर is पढ़ो, the response
	 * value may not be पढ़ो properly.
	 * Use single block पढ़ो क्रम this HW bug
	 */
	अगर ((direction == MMC_DATA_READ) &&
	    blk_size == 2)
		वापस 1;

	वापस blk_size;
पूर्ण

अटल व्योम renesas_sdhi_fixup_request(काष्ठा पंचांगio_mmc_host *host, काष्ठा mmc_request *mrq)
अणु
	काष्ठा renesas_sdhi *priv = host_to_priv(host);

	अगर (priv->needs_adjust_hs400 && mrq->cmd->opcode == MMC_SEND_STATUS)
		renesas_sdhi_adjust_hs400_mode_enable(host);
पूर्ण
अटल व्योम renesas_sdhi_enable_dma(काष्ठा पंचांगio_mmc_host *host, bool enable)
अणु
	/* Iff regs are 8 byte apart, sdbuf is 64 bit. Otherwise always 32. */
	पूर्णांक width = (host->bus_shअगरt == 2) ? 64 : 32;

	sd_ctrl_ग_लिखो16(host, CTL_DMA_ENABLE, enable ? DMA_ENABLE_DMASDRW : 0);
	renesas_sdhi_sdbuf_width(host, enable ? width : 16);
पूर्ण

अटल स्थिर काष्ठा renesas_sdhi_quirks sdhi_quirks_4tap_nohs400 = अणु
	.hs400_disabled = true,
	.hs400_4taps = true,
पूर्ण;

अटल स्थिर काष्ठा renesas_sdhi_quirks sdhi_quirks_4tap = अणु
	.hs400_4taps = true,
	.hs400_bad_taps = BIT(2) | BIT(3) | BIT(6) | BIT(7),
पूर्ण;

अटल स्थिर काष्ठा renesas_sdhi_quirks sdhi_quirks_nohs400 = अणु
	.hs400_disabled = true,
पूर्ण;

अटल स्थिर काष्ठा renesas_sdhi_quirks sdhi_quirks_bad_taps1357 = अणु
	.hs400_bad_taps = BIT(1) | BIT(3) | BIT(5) | BIT(7),
पूर्ण;

अटल स्थिर काष्ठा renesas_sdhi_quirks sdhi_quirks_bad_taps2367 = अणु
	.hs400_bad_taps = BIT(2) | BIT(3) | BIT(6) | BIT(7),
पूर्ण;

अटल स्थिर काष्ठा renesas_sdhi_quirks sdhi_quirks_r8a7796_es13 = अणु
	.hs400_4taps = true,
	.hs400_bad_taps = BIT(2) | BIT(3) | BIT(6) | BIT(7),
	.hs400_calib_table = r8a7796_es13_calib_table,
पूर्ण;

अटल स्थिर काष्ठा renesas_sdhi_quirks sdhi_quirks_r8a77965 = अणु
	.hs400_bad_taps = BIT(2) | BIT(3) | BIT(6) | BIT(7),
	.hs400_calib_table = r8a77965_calib_table,
पूर्ण;

अटल स्थिर काष्ठा renesas_sdhi_quirks sdhi_quirks_r8a77990 = अणु
	.hs400_calib_table = r8a77990_calib_table,
पूर्ण;

/*
 * Note क्रम r8a7796 / r8a774a1: we can't distinguish ES1.1 and 1.2 as of now.
 * So, we want to treat them equally and only have a match क्रम ES1.2 to enक्रमce
 * this अगर there ever will be a way to distinguish ES1.2.
 */
अटल स्थिर काष्ठा soc_device_attribute sdhi_quirks_match[]  = अणु
	अणु .soc_id = "r8a774a1", .revision = "ES1.[012]", .data = &sdhi_quirks_4tap_nohs400 पूर्ण,
	अणु .soc_id = "r8a7795", .revision = "ES1.*", .data = &sdhi_quirks_4tap_nohs400 पूर्ण,
	अणु .soc_id = "r8a7795", .revision = "ES2.0", .data = &sdhi_quirks_4tap पूर्ण,
	अणु .soc_id = "r8a7795", .revision = "ES3.*", .data = &sdhi_quirks_bad_taps2367 पूर्ण,
	अणु .soc_id = "r8a7796", .revision = "ES1.[012]", .data = &sdhi_quirks_4tap_nohs400 पूर्ण,
	अणु .soc_id = "r8a7796", .revision = "ES1.*", .data = &sdhi_quirks_r8a7796_es13 पूर्ण,
	अणु .soc_id = "r8a77961", .data = &sdhi_quirks_bad_taps1357 पूर्ण,
	अणु .soc_id = "r8a77965", .data = &sdhi_quirks_r8a77965 पूर्ण,
	अणु .soc_id = "r8a77980", .data = &sdhi_quirks_nohs400 पूर्ण,
	अणु .soc_id = "r8a77990", .data = &sdhi_quirks_r8a77990 पूर्ण,
	अणु /* Sentinel. */ पूर्ण,
पूर्ण;

पूर्णांक renesas_sdhi_probe(काष्ठा platक्रमm_device *pdev,
		       स्थिर काष्ठा पंचांगio_mmc_dma_ops *dma_ops)
अणु
	काष्ठा पंचांगio_mmc_data *mmd = pdev->dev.platक्रमm_data;
	स्थिर काष्ठा renesas_sdhi_quirks *quirks = शून्य;
	स्थिर काष्ठा renesas_sdhi_of_data *of_data;
	स्थिर काष्ठा soc_device_attribute *attr;
	काष्ठा पंचांगio_mmc_data *mmc_data;
	काष्ठा पंचांगio_mmc_dma *dma_priv;
	काष्ठा पंचांगio_mmc_host *host;
	काष्ठा renesas_sdhi *priv;
	पूर्णांक num_irqs, irq, ret, i;
	काष्ठा resource *res;
	u16 ver;

	of_data = of_device_get_match_data(&pdev->dev);

	attr = soc_device_match(sdhi_quirks_match);
	अगर (attr)
		quirks = attr->data;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा renesas_sdhi),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->quirks = quirks;
	mmc_data = &priv->mmc_data;
	dma_priv = &priv->dma_priv;

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		ret = PTR_ERR(priv->clk);
		dev_err(&pdev->dev, "cannot get clock: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Some controllers provide a 2nd घड़ी just to run the पूर्णांकernal card
	 * detection logic. Unक्रमtunately, the existing driver architecture करोes
	 * not support a separation of घड़ीs क्रम runसमय PM usage. When
	 * native hotplug is used, the पंचांगio driver assumes that the core
	 * must जारी to run क्रम card detect to stay active, so we cannot
	 * disable it.
	 * Additionally, it is prohibited to supply a घड़ी to the core but not
	 * to the card detect circuit. That leaves us with अगर separate घड़ीs
	 * are presented, we must treat them both as भवly 1 घड़ी.
	 */
	priv->clk_cd = devm_clk_get(&pdev->dev, "cd");
	अगर (IS_ERR(priv->clk_cd))
		priv->clk_cd = शून्य;

	priv->pinctrl = devm_pinctrl_get(&pdev->dev);
	अगर (!IS_ERR(priv->pinctrl)) अणु
		priv->pins_शेष = pinctrl_lookup_state(priv->pinctrl,
						PINCTRL_STATE_DEFAULT);
		priv->pins_uhs = pinctrl_lookup_state(priv->pinctrl,
						"state_uhs");
	पूर्ण

	host = पंचांगio_mmc_host_alloc(pdev, mmc_data);
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	अगर (of_data) अणु
		mmc_data->flags |= of_data->पंचांगio_flags;
		mmc_data->ocr_mask = of_data->पंचांगio_ocr_mask;
		mmc_data->capabilities |= of_data->capabilities;
		mmc_data->capabilities2 |= of_data->capabilities2;
		mmc_data->dma_rx_offset = of_data->dma_rx_offset;
		mmc_data->max_blk_count = of_data->max_blk_count;
		mmc_data->max_segs = of_data->max_segs;
		dma_priv->dma_buswidth = of_data->dma_buswidth;
		host->bus_shअगरt = of_data->bus_shअगरt;
	पूर्ण

	host->ग_लिखो16_hook	= renesas_sdhi_ग_लिखो16_hook;
	host->clk_enable	= renesas_sdhi_clk_enable;
	host->clk_disable	= renesas_sdhi_clk_disable;
	host->set_घड़ी		= renesas_sdhi_set_घड़ी;
	host->multi_io_quirk	= renesas_sdhi_multi_io_quirk;
	host->dma_ops		= dma_ops;

	अगर (quirks && quirks->hs400_disabled)
		host->mmc->caps2 &= ~(MMC_CAP2_HS400 | MMC_CAP2_HS400_ES);

	/* For some SoC, we disable पूर्णांकernal WP. GPIO may override this */
	अगर (mmc_can_gpio_ro(host->mmc))
		mmc_data->capabilities2 &= ~MMC_CAP2_NO_WRITE_PROTECT;

	/* SDR speeds are only available on Gen2+ */
	अगर (mmc_data->flags & TMIO_MMC_MIN_RCAR2) अणु
		/* card_busy caused issues on r8a73a4 (pre-Gen2) CD-less SDHI */
		host->ops.card_busy = renesas_sdhi_card_busy;
		host->ops.start_संकेत_voltage_चयन =
			renesas_sdhi_start_संकेत_voltage_चयन;
		host->sdcard_irq_setbit_mask = TMIO_STAT_ALWAYS_SET_27;
		host->sdcard_irq_mask_all = TMIO_MASK_ALL_RCAR2;
		host->reset = renesas_sdhi_reset;
	पूर्ण

	/* Orginally रेजिस्टरs were 16 bit apart, could be 32 or 64 nowadays */
	अगर (!host->bus_shअगरt && resource_size(res) > 0x100) /* old way to determine the shअगरt */
		host->bus_shअगरt = 1;

	अगर (mmd)
		*mmc_data = *mmd;

	dma_priv->filter = shdma_chan_filter;
	dma_priv->enable = renesas_sdhi_enable_dma;

	mmc_data->alignment_shअगरt = 1; /* 2-byte alignment */
	mmc_data->capabilities |= MMC_CAP_MMC_HIGHSPEED;

	/*
	 * All SDHI blocks support 2-byte and larger block sizes in 4-bit
	 * bus width mode.
	 */
	mmc_data->flags |= TMIO_MMC_BLKSZ_2BYTES;

	/*
	 * All SDHI blocks support SDIO IRQ संकेतling.
	 */
	mmc_data->flags |= TMIO_MMC_SDIO_IRQ;

	/* All SDHI have CMD12 control bit */
	mmc_data->flags |= TMIO_MMC_HAVE_CMD12_CTRL;

	/* All SDHI have SDIO status bits which must be 1 */
	mmc_data->flags |= TMIO_MMC_SDIO_STATUS_SETBITS;

	/* All SDHI support HW busy detection */
	mmc_data->flags |= TMIO_MMC_USE_BUSY_TIMEOUT;

	dev_pm_करोमुख्य_start(&pdev->dev);

	ret = renesas_sdhi_clk_enable(host);
	अगर (ret)
		जाओ eमुक्त;

	priv->rstc = devm_reset_control_get_optional_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->rstc))
		वापस PTR_ERR(priv->rstc);

	ver = sd_ctrl_पढ़ो16(host, CTL_VERSION);
	/* GEN2_SDR104 is first known SDHI to use 32bit block count */
	अगर (ver < SDHI_VER_GEN2_SDR104 && mmc_data->max_blk_count > U16_MAX)
		mmc_data->max_blk_count = U16_MAX;

	/* One Gen2 SDHI incarnation करोes NOT have a CBSY bit */
	अगर (ver == SDHI_VER_GEN2_SDR50)
		mmc_data->flags &= ~TMIO_MMC_HAVE_CBSY;

	अगर (ver == SDHI_VER_GEN3_SDMMC && quirks && quirks->hs400_calib_table) अणु
		host->fixup_request = renesas_sdhi_fixup_request;
		priv->adjust_hs400_calib_table = *(
			res->start == SDHI_GEN3_MMC0_ADDR ?
			quirks->hs400_calib_table :
			quirks->hs400_calib_table + 1);
	पूर्ण

	/* these have an EXTOP bit */
	अगर (ver >= SDHI_VER_GEN3_SD)
		host->get_समयout_cycles = renesas_sdhi_gen3_get_cycles;

	/* Enable tuning अगरf we have an SCC and a supported mode */
	अगर (of_data && of_data->scc_offset &&
	    (host->mmc->caps & MMC_CAP_UHS_SDR104 ||
	     host->mmc->caps2 & (MMC_CAP2_HS200_1_8V_SDR |
				 MMC_CAP2_HS400_1_8V))) अणु
		स्थिर काष्ठा renesas_sdhi_scc *taps = of_data->taps;
		bool use_4tap = priv->quirks && priv->quirks->hs400_4taps;
		bool hit = false;

		क्रम (i = 0; i < of_data->taps_num; i++) अणु
			अगर (taps[i].clk_rate == 0 ||
			    taps[i].clk_rate == host->mmc->f_max) अणु
				priv->scc_tappos = taps->tap;
				priv->scc_tappos_hs400 = use_4tap ?
							 taps->tap_hs400_4tap :
							 taps->tap;
				hit = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!hit)
			dev_warn(&host->pdev->dev, "Unknown clock rate for tuning\n");

		priv->scc_ctl = host->ctl + of_data->scc_offset;
		host->check_retune = renesas_sdhi_check_scc_error;
		host->ops.execute_tuning = renesas_sdhi_execute_tuning;
		host->ops.prepare_hs400_tuning = renesas_sdhi_prepare_hs400_tuning;
		host->ops.hs400_करोwngrade = renesas_sdhi_disable_scc;
		host->ops.hs400_complete = renesas_sdhi_hs400_complete;
	पूर्ण

	ret = पंचांगio_mmc_host_probe(host);
	अगर (ret < 0)
		जाओ edisclk;

	num_irqs = platक्रमm_irq_count(pdev);
	अगर (num_irqs < 0) अणु
		ret = num_irqs;
		जाओ eirq;
	पूर्ण

	/* There must be at least one IRQ source */
	अगर (!num_irqs) अणु
		ret = -ENXIO;
		जाओ eirq;
	पूर्ण

	क्रम (i = 0; i < num_irqs; i++) अणु
		irq = platक्रमm_get_irq(pdev, i);
		अगर (irq < 0) अणु
			ret = irq;
			जाओ eirq;
		पूर्ण

		ret = devm_request_irq(&pdev->dev, irq, पंचांगio_mmc_irq, 0,
				       dev_name(&pdev->dev), host);
		अगर (ret)
			जाओ eirq;
	पूर्ण

	dev_info(&pdev->dev, "%s base at %pa, max clock rate %u MHz\n",
		 mmc_hostname(host->mmc), &res->start, host->mmc->f_max / 1000000);

	वापस ret;

eirq:
	पंचांगio_mmc_host_हटाओ(host);
edisclk:
	renesas_sdhi_clk_disable(host);
eमुक्त:
	पंचांगio_mmc_host_मुक्त(host);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(renesas_sdhi_probe);

पूर्णांक renesas_sdhi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पंचांगio_mmc_host *host = platक्रमm_get_drvdata(pdev);

	पंचांगio_mmc_host_हटाओ(host);
	renesas_sdhi_clk_disable(host);
	पंचांगio_mmc_host_मुक्त(host);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(renesas_sdhi_हटाओ);

MODULE_LICENSE("GPL v2");
