<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * opp2430_data.c - old-style "OPP" table क्रम OMAP2430
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
 * 2430 dअगरfers from 2420 in that there are no more phase synchronizers used.
 * They both have a slightly dअगरferent घड़ी करोमुख्य setup. 2420(iva1,dsp) vs
 * 2430 (iva2.1, NOdsp, mdm)
 *
 * XXX Missing voltage data.
 * XXX Missing 19.2MHz sys_clk rate sets.
 *
 * THe क्रमmat described in this file is deprecated.  Once a reasonable
 * OPP API exists, the data in this file should be converted to use it.
 *
 * This is technically part of the OMAP2xxx घड़ी code.
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
 * Filling in table based on 2430-SDPs variants available.  There are
 * quite a few more rate combinations which could be defined.
 *
 * When multiple values are defined the start up will try and choose
 * the fastest one. If a 'fast' value is defined, then स्वतःmatically,
 * the /2 one should be included as it can be used.  Generally having
 * more than one fast set करोes not make sense, as अटल timings need
 * to be changed to change the set.  The exception is the bypass
 * setting which is available क्रम low घातer bypass.
 *
 * Note: This table needs to be sorted, fastest to slowest.
 */
स्थिर काष्ठा prcm_config omap2430_rate_table[] = अणु
	/* PRCM #4 - ratio2 (ES2.1) - FAST */
	अणुS13M, S798M, S399M, R2_CM_CLKSEL_MPU_VAL,		/* 399MHz ARM */
		R2_CM_CLKSEL_DSP_VAL, R2_CM_CLKSEL_GFX_VAL,
		R2_CM_CLKSEL1_CORE_VAL, M4_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_2x_VAL, R2_CM_CLKSEL_MDM_VAL,
		SDRC_RFR_CTRL_133MHz,
		RATE_IN_243Xपूर्ण,

	/* PRCM #2 - ratio1 (ES2) - FAST */
	अणुS13M, S658M, S329M, R1_CM_CLKSEL_MPU_VAL,		/* 330MHz ARM */
		R1_CM_CLKSEL_DSP_VAL, R1_CM_CLKSEL_GFX_VAL,
		R1_CM_CLKSEL1_CORE_VAL, M2_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_2x_VAL, R1_CM_CLKSEL_MDM_VAL,
		SDRC_RFR_CTRL_165MHz,
		RATE_IN_243Xपूर्ण,

	/* PRCM #5a - ratio1 - FAST */
	अणुS13M, S532M, S266M, R1_CM_CLKSEL_MPU_VAL,		/* 266MHz ARM */
		R1_CM_CLKSEL_DSP_VAL, R1_CM_CLKSEL_GFX_VAL,
		R1_CM_CLKSEL1_CORE_VAL, M5A_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_2x_VAL, R1_CM_CLKSEL_MDM_VAL,
		SDRC_RFR_CTRL_133MHz,
		RATE_IN_243Xपूर्ण,

	/* PRCM #5b - ratio1 - FAST */
	अणुS13M, S400M, S200M, R1_CM_CLKSEL_MPU_VAL,		/* 200MHz ARM */
		R1_CM_CLKSEL_DSP_VAL, R1_CM_CLKSEL_GFX_VAL,
		R1_CM_CLKSEL1_CORE_VAL, M5B_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_2x_VAL, R1_CM_CLKSEL_MDM_VAL,
		SDRC_RFR_CTRL_100MHz,
		RATE_IN_243Xपूर्ण,

	/* PRCM #4 - ratio1 (ES2.1) - SLOW */
	अणुS13M, S399M, S199M, R2_CM_CLKSEL_MPU_VAL,		/* 200MHz ARM */
		R2_CM_CLKSEL_DSP_VAL, R2_CM_CLKSEL_GFX_VAL,
		R2_CM_CLKSEL1_CORE_VAL, M4_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_1x_VAL, R2_CM_CLKSEL_MDM_VAL,
		SDRC_RFR_CTRL_133MHz,
		RATE_IN_243Xपूर्ण,

	/* PRCM #2 - ratio1 (ES2) - SLOW */
	अणुS13M, S329M, S164M, R1_CM_CLKSEL_MPU_VAL,		/* 165MHz ARM */
		R1_CM_CLKSEL_DSP_VAL, R1_CM_CLKSEL_GFX_VAL,
		R1_CM_CLKSEL1_CORE_VAL, M2_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_1x_VAL, R1_CM_CLKSEL_MDM_VAL,
		SDRC_RFR_CTRL_165MHz,
		RATE_IN_243Xपूर्ण,

	/* PRCM #5a - ratio1 - SLOW */
	अणुS13M, S266M, S133M, R1_CM_CLKSEL_MPU_VAL,		/* 133MHz ARM */
		R1_CM_CLKSEL_DSP_VAL, R1_CM_CLKSEL_GFX_VAL,
		R1_CM_CLKSEL1_CORE_VAL, M5A_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_1x_VAL, R1_CM_CLKSEL_MDM_VAL,
		SDRC_RFR_CTRL_133MHz,
		RATE_IN_243Xपूर्ण,

	/* PRCM #5b - ratio1 - SLOW*/
	अणुS13M, S200M, S100M, R1_CM_CLKSEL_MPU_VAL,		/* 100MHz ARM */
		R1_CM_CLKSEL_DSP_VAL, R1_CM_CLKSEL_GFX_VAL,
		R1_CM_CLKSEL1_CORE_VAL, M5B_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_1x_VAL, R1_CM_CLKSEL_MDM_VAL,
		SDRC_RFR_CTRL_100MHz,
		RATE_IN_243Xपूर्ण,

	/* PRCM-boot/bypass */
	अणुS13M, S13M, S13M, RB_CM_CLKSEL_MPU_VAL,		/* 13MHz */
		RB_CM_CLKSEL_DSP_VAL, RB_CM_CLKSEL_GFX_VAL,
		RB_CM_CLKSEL1_CORE_VAL, MB_CM_CLKSEL1_PLL_13_VAL,
		MX_CLKSEL2_PLL_2x_VAL, RB_CM_CLKSEL_MDM_VAL,
		SDRC_RFR_CTRL_BYPASS,
		RATE_IN_243Xपूर्ण,

	/* PRCM-boot/bypass */
	अणुS12M, S12M, S12M, RB_CM_CLKSEL_MPU_VAL,		/* 12MHz */
		RB_CM_CLKSEL_DSP_VAL, RB_CM_CLKSEL_GFX_VAL,
		RB_CM_CLKSEL1_CORE_VAL, MB_CM_CLKSEL1_PLL_12_VAL,
		MX_CLKSEL2_PLL_2x_VAL, RB_CM_CLKSEL_MDM_VAL,
		SDRC_RFR_CTRL_BYPASS,
		RATE_IN_243Xपूर्ण,

	अणु 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
पूर्ण;
