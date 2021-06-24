<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * opp2420_data.c - old-style "OPP" table क्रम OMAP2420
 *
 * Copyright (C) 2005-2009 Texas Instruments, Inc.
 * Copyright (C) 2004-2009 Nokia Corporation
 *
 * Riअक्षरd Woodruff <r-woodruff2@ti.com>
 *
 * The OMAP2 processor can be run at several discrete 'PRCM configurations'.
 * These configurations are अक्षरacterized by voltage and speed क्रम घड़ीs.
 * The device is only validated क्रम certain combinations. One way to express
 * these combinations is via the 'ratios' which the घड़ीs operate with
 * respect to each other. These ratio sets are क्रम a given voltage/DPLL
 * setting. All configurations can be described by a DPLL setting and a ratio.
 *
 * XXX Missing voltage data.
 * XXX Missing 19.2MHz sys_clk rate sets (needed क्रम N800/N810)
 *
 * THe क्रमmat described in this file is deprecated.  Once a reasonable
 * OPP API exists, the data in this file should be converted to use it.
 *
 * This is technically part of the OMAP2xxx घड़ी code.
 *
 * Considerable work is still needed to fully support dynamic frequency
 * changes on OMAP2xxx-series chips.  Readers पूर्णांकerested in such a
 * project are encouraged to review the Maemo Diablo RX-34 and RX-44
 * kernel source at:
 *     http://repository.maemo.org/pool/diablo/मुक्त/k/kernel-source-diablo/
 */

#समावेश <linux/kernel.h>

#समावेश "opp2xxx.h"
#समावेश "sdrc.h"
#समावेश "clock.h"

/*
 * Key भागiders which make up a PRCM set. Ratios क्रम a PRCM are mandated.
 * xtal_speed, dpll_speed, mpu_speed, CM_CLKSEL_MPU,
 * CM_CLKSEL_DSP, CM_CLKSEL_GFX, CM_CLKSEL1_CORE, CM_CLKSEL1_PLL,
 * CM_CLKSEL2_PLL, CM_CLKSEL_MDM
 *
 * Filling in table based on H4 boards available.  There are quite a
 * few more rate combinations which could be defined.
 *
 * When multiple values are defined the start up will try and choose
 * the fastest one. If a 'fast' value is defined, then स्वतःmatically,
 * the /2 one should be included as it can be used.  Generally having
 * more than one fast set करोes not make sense, as अटल timings need
 * to be changed to change the set.  The exception is the bypass
 * setting which is available क्रम low घातer bypass.
 *
 * Note: This table needs to be sorted, fastest to slowest.
 **/
स्थिर काष्ठा prcm_config omap2420_rate_table[] = अणु
	/* PRCM I - FAST */
	अणुS12M, S660M, S330M, RI_CM_CLKSEL_MPU_VAL,		/* 330MHz ARM */
		RI_CM_CLKSEL_DSP_VAL, RI_CM_CLKSEL_GFX_VAL,
		RI_CM_CLKSEL1_CORE_VAL, MI_CM_CLKSEL1_PLL_12_VAL,
		MX_CLKSEL2_PLL_2x_VAL, 0, SDRC_RFR_CTRL_165MHz,
		RATE_IN_242Xपूर्ण,

	/* PRCM II - FAST */
	अणुS12M, S600M, S300M, RII_CM_CLKSEL_MPU_VAL,		/* 300MHz ARM */
		RII_CM_CLKSEL_DSP_VAL, RII_CM_CLKSEL_GFX_VAL,
		RII_CM_CLKSEL1_CORE_VAL, MII_CM_CLKSEL1_PLL_12_VAL,
		MX_CLKSEL2_PLL_2x_VAL, 0, SDRC_RFR_CTRL_100MHz,
		RATE_IN_242Xपूर्ण,

	अणुS13M, S600M, S300M, RII_CM_CLKSEL_MPU_VAL,		/* 300MHz ARM */
		RII_CM_CLKSEL_DSP_VAL, RII_CM_CLKSEL_GFX_VAL,
		RII_CM_CLKSEL1_CORE_VAL, MII_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_2x_VAL, 0, SDRC_RFR_CTRL_100MHz,
		RATE_IN_242Xपूर्ण,

	/* PRCM III - FAST */
	अणुS12M, S532M, S266M, RIII_CM_CLKSEL_MPU_VAL,		/* 266MHz ARM */
		RIII_CM_CLKSEL_DSP_VAL, RIII_CM_CLKSEL_GFX_VAL,
		RIII_CM_CLKSEL1_CORE_VAL, MIII_CM_CLKSEL1_PLL_12_VAL,
		MX_CLKSEL2_PLL_2x_VAL, 0, SDRC_RFR_CTRL_133MHz,
		RATE_IN_242Xपूर्ण,

	अणुS13M, S532M, S266M, RIII_CM_CLKSEL_MPU_VAL,		/* 266MHz ARM */
		RIII_CM_CLKSEL_DSP_VAL, RIII_CM_CLKSEL_GFX_VAL,
		RIII_CM_CLKSEL1_CORE_VAL, MIII_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_2x_VAL, 0, SDRC_RFR_CTRL_133MHz,
		RATE_IN_242Xपूर्ण,

	/* PRCM II - SLOW */
	अणुS12M, S300M, S150M, RII_CM_CLKSEL_MPU_VAL,		/* 150MHz ARM */
		RII_CM_CLKSEL_DSP_VAL, RII_CM_CLKSEL_GFX_VAL,
		RII_CM_CLKSEL1_CORE_VAL, MII_CM_CLKSEL1_PLL_12_VAL,
		MX_CLKSEL2_PLL_2x_VAL, 0, SDRC_RFR_CTRL_100MHz,
		RATE_IN_242Xपूर्ण,

	अणुS13M, S300M, S150M, RII_CM_CLKSEL_MPU_VAL,		/* 150MHz ARM */
		RII_CM_CLKSEL_DSP_VAL, RII_CM_CLKSEL_GFX_VAL,
		RII_CM_CLKSEL1_CORE_VAL, MII_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_2x_VAL, 0, SDRC_RFR_CTRL_100MHz,
		RATE_IN_242Xपूर्ण,

	/* PRCM III - SLOW */
	अणुS12M, S266M, S133M, RIII_CM_CLKSEL_MPU_VAL,		/* 133MHz ARM */
		RIII_CM_CLKSEL_DSP_VAL, RIII_CM_CLKSEL_GFX_VAL,
		RIII_CM_CLKSEL1_CORE_VAL, MIII_CM_CLKSEL1_PLL_12_VAL,
		MX_CLKSEL2_PLL_2x_VAL, 0, SDRC_RFR_CTRL_133MHz,
		RATE_IN_242Xपूर्ण,

	अणुS13M, S266M, S133M, RIII_CM_CLKSEL_MPU_VAL,		/* 133MHz ARM */
		RIII_CM_CLKSEL_DSP_VAL, RIII_CM_CLKSEL_GFX_VAL,
		RIII_CM_CLKSEL1_CORE_VAL, MIII_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_2x_VAL, 0, SDRC_RFR_CTRL_133MHz,
		RATE_IN_242Xपूर्ण,

	/* PRCM-VII (boot-bypass) */
	अणुS12M, S12M, S12M, RVII_CM_CLKSEL_MPU_VAL,		/* 12MHz ARM*/
		RVII_CM_CLKSEL_DSP_VAL, RVII_CM_CLKSEL_GFX_VAL,
		RVII_CM_CLKSEL1_CORE_VAL, MVII_CM_CLKSEL1_PLL_12_VAL,
		MX_CLKSEL2_PLL_2x_VAL, 0, SDRC_RFR_CTRL_BYPASS,
		RATE_IN_242Xपूर्ण,

	/* PRCM-VII (boot-bypass) */
	अणुS13M, S13M, S13M, RVII_CM_CLKSEL_MPU_VAL,		/* 13MHz ARM */
		RVII_CM_CLKSEL_DSP_VAL, RVII_CM_CLKSEL_GFX_VAL,
		RVII_CM_CLKSEL1_CORE_VAL, MVII_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_2x_VAL, 0, SDRC_RFR_CTRL_BYPASS,
		RATE_IN_242Xपूर्ण,

	अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
पूर्ण;
