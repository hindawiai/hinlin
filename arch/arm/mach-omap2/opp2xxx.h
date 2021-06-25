<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * opp2xxx.h - macros क्रम old-style OMAP2xxx "OPP" definitions
 *
 * Copyright (C) 2005-2009 Texas Instruments, Inc.
 * Copyright (C) 2004-2009 Nokia Corporation
 *
 * Riअक्षरd Woodruff <r-woodruff2@ti.com>
 *
 * The OMAP2 processor can be run at several discrete 'PRCM configurations'.
 * These configurations are अक्षरacterized by voltage and speed क्रम घड़ीs.
 * The device is only validated क्रम certain combinations. One way to express
 * these combinations is via the 'ratio's' which the घड़ीs operate with
 * respect to each other. These ratio sets are क्रम a given voltage/DPLL
 * setting. All configurations can be described by a DPLL setting and a ratio
 * There are 3 ratio sets क्रम the 2430 and X ratio sets क्रम 2420.
 *
 * 2430 dअगरfers from 2420 in that there are no more phase synchronizers used.
 * They both have a slightly dअगरferent घड़ी करोमुख्य setup. 2420(iva1,dsp) vs
 * 2430 (iva2.1, NOdsp, mdm)
 *
 * XXX Missing voltage data.
 *
 * THe क्रमmat described in this file is deprecated.  Once a reasonable
 * OPP API exists, the data in this file should be converted to use it.
 *
 * This is technically part of the OMAP2xxx घड़ी code.
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_OPP2XXX_H
#घोषणा __ARCH_ARM_MACH_OMAP2_OPP2XXX_H

/**
 * काष्ठा prcm_config - define घड़ी rates on a per-OPP basis (24xx)
 *
 * Key भागiders which make up a PRCM set. Ratio's क्रम a PRCM are mandated.
 * xtal_speed, dpll_speed, mpu_speed, CM_CLKSEL_MPU,CM_CLKSEL_DSP
 * CM_CLKSEL_GFX, CM_CLKSEL1_CORE, CM_CLKSEL1_PLL CM_CLKSEL2_PLL, CM_CLKSEL_MDM
 *
 * This is deprecated.  As soon as we have a decent OPP API, we should
 * move all this stuff to it.
 */
काष्ठा prcm_config अणु
	अचिन्हित दीर्घ xtal_speed;	/* crystal rate */
	अचिन्हित दीर्घ dpll_speed;	/* dpll: out*xtal*M/(N-1)table_recalc */
	अचिन्हित दीर्घ mpu_speed;	/* speed of MPU */
	अचिन्हित दीर्घ cm_clksel_mpu;	/* mpu भागider */
	अचिन्हित दीर्घ cm_clksel_dsp;	/* dsp+iva1 भाग(2420), iva2.1(2430) */
	अचिन्हित दीर्घ cm_clksel_gfx;	/* gfx भागiders */
	अचिन्हित दीर्घ cm_clksel1_core;	/* major subप्रणाली भागiders */
	अचिन्हित दीर्घ cm_clksel1_pll;	/* m,n */
	अचिन्हित दीर्घ cm_clksel2_pll;	/* dpllx1 or x2 out */
	अचिन्हित दीर्घ cm_clksel_mdm;	/* modem भागiders 2430 only */
	अचिन्हित दीर्घ base_sdrc_rfr;	/* base refresh timing क्रम a set */
	अचिन्हित लघु flags;
पूर्ण;


/* Core fields क्रम cm_clksel, not ratio governed */
#घोषणा RX_CLKSEL_DSS1			(0x10 << 8)
#घोषणा RX_CLKSEL_DSS2			(0x0 << 13)
#घोषणा RX_CLKSEL_SSI			(0x5 << 20)

/*-------------------------------------------------------------------------
 * Voltage/DPLL ratios
 *-------------------------------------------------------------------------*/

/* 2430 Ratio's, 2430-Ratio Config 1 */
#घोषणा R1_CLKSEL_L3			(4 << 0)
#घोषणा R1_CLKSEL_L4			(2 << 5)
#घोषणा R1_CLKSEL_USB			(4 << 25)
#घोषणा R1_CM_CLKSEL1_CORE_VAL		(R1_CLKSEL_USB | RX_CLKSEL_SSI | \
					 RX_CLKSEL_DSS2 | RX_CLKSEL_DSS1 | \
					 R1_CLKSEL_L4 | R1_CLKSEL_L3)
#घोषणा R1_CLKSEL_MPU			(2 << 0)
#घोषणा R1_CM_CLKSEL_MPU_VAL		R1_CLKSEL_MPU
#घोषणा R1_CLKSEL_DSP			(2 << 0)
#घोषणा R1_CLKSEL_DSP_IF		(2 << 5)
#घोषणा R1_CM_CLKSEL_DSP_VAL		(R1_CLKSEL_DSP | R1_CLKSEL_DSP_IF)
#घोषणा R1_CLKSEL_GFX			(2 << 0)
#घोषणा R1_CM_CLKSEL_GFX_VAL		R1_CLKSEL_GFX
#घोषणा R1_CLKSEL_MDM			(4 << 0)
#घोषणा R1_CM_CLKSEL_MDM_VAL		R1_CLKSEL_MDM

/* 2430-Ratio Config 2 */
#घोषणा R2_CLKSEL_L3			(6 << 0)
#घोषणा R2_CLKSEL_L4			(2 << 5)
#घोषणा R2_CLKSEL_USB			(2 << 25)
#घोषणा R2_CM_CLKSEL1_CORE_VAL		(R2_CLKSEL_USB | RX_CLKSEL_SSI | \
					 RX_CLKSEL_DSS2 | RX_CLKSEL_DSS1 | \
					 R2_CLKSEL_L4 | R2_CLKSEL_L3)
#घोषणा R2_CLKSEL_MPU			(2 << 0)
#घोषणा R2_CM_CLKSEL_MPU_VAL		R2_CLKSEL_MPU
#घोषणा R2_CLKSEL_DSP			(2 << 0)
#घोषणा R2_CLKSEL_DSP_IF		(3 << 5)
#घोषणा R2_CM_CLKSEL_DSP_VAL		(R2_CLKSEL_DSP | R2_CLKSEL_DSP_IF)
#घोषणा R2_CLKSEL_GFX			(2 << 0)
#घोषणा R2_CM_CLKSEL_GFX_VAL		R2_CLKSEL_GFX
#घोषणा R2_CLKSEL_MDM			(6 << 0)
#घोषणा R2_CM_CLKSEL_MDM_VAL		R2_CLKSEL_MDM

/* 2430-Ratio Booपंचांग (BYPASS) */
#घोषणा RB_CLKSEL_L3			(1 << 0)
#घोषणा RB_CLKSEL_L4			(1 << 5)
#घोषणा RB_CLKSEL_USB			(1 << 25)
#घोषणा RB_CM_CLKSEL1_CORE_VAL		(RB_CLKSEL_USB | RX_CLKSEL_SSI | \
					 RX_CLKSEL_DSS2 | RX_CLKSEL_DSS1 | \
					 RB_CLKSEL_L4 | RB_CLKSEL_L3)
#घोषणा RB_CLKSEL_MPU			(1 << 0)
#घोषणा RB_CM_CLKSEL_MPU_VAL		RB_CLKSEL_MPU
#घोषणा RB_CLKSEL_DSP			(1 << 0)
#घोषणा RB_CLKSEL_DSP_IF		(1 << 5)
#घोषणा RB_CM_CLKSEL_DSP_VAL		(RB_CLKSEL_DSP | RB_CLKSEL_DSP_IF)
#घोषणा RB_CLKSEL_GFX			(1 << 0)
#घोषणा RB_CM_CLKSEL_GFX_VAL		RB_CLKSEL_GFX
#घोषणा RB_CLKSEL_MDM			(1 << 0)
#घोषणा RB_CM_CLKSEL_MDM_VAL		RB_CLKSEL_MDM

/* 2420 Ratio Equivalents */
#घोषणा RXX_CLKSEL_VLYNQ		(0x12 << 15)
#घोषणा RXX_CLKSEL_SSI			(0x8 << 20)

/* 2420-PRCM III 532MHz core */
#घोषणा RIII_CLKSEL_L3			(4 << 0)	/* 133MHz */
#घोषणा RIII_CLKSEL_L4			(2 << 5)	/* 66.5MHz */
#घोषणा RIII_CLKSEL_USB			(4 << 25)	/* 33.25MHz */
#घोषणा RIII_CM_CLKSEL1_CORE_VAL	(RIII_CLKSEL_USB | RXX_CLKSEL_SSI | \
					 RXX_CLKSEL_VLYNQ | RX_CLKSEL_DSS2 | \
					 RX_CLKSEL_DSS1 | RIII_CLKSEL_L4 | \
					 RIII_CLKSEL_L3)
#घोषणा RIII_CLKSEL_MPU			(2 << 0)	/* 266MHz */
#घोषणा RIII_CM_CLKSEL_MPU_VAL		RIII_CLKSEL_MPU
#घोषणा RIII_CLKSEL_DSP			(3 << 0)	/* c5x - 177.3MHz */
#घोषणा RIII_CLKSEL_DSP_IF		(2 << 5)	/* c5x - 88.67MHz */
#घोषणा RIII_SYNC_DSP			(1 << 7)	/* Enable sync */
#घोषणा RIII_CLKSEL_IVA			(6 << 8)	/* iva1 - 88.67MHz */
#घोषणा RIII_SYNC_IVA			(1 << 13)	/* Enable sync */
#घोषणा RIII_CM_CLKSEL_DSP_VAL		(RIII_SYNC_IVA | RIII_CLKSEL_IVA | \
					 RIII_SYNC_DSP | RIII_CLKSEL_DSP_IF | \
					 RIII_CLKSEL_DSP)
#घोषणा RIII_CLKSEL_GFX			(2 << 0)	/* 66.5MHz */
#घोषणा RIII_CM_CLKSEL_GFX_VAL		RIII_CLKSEL_GFX

/* 2420-PRCM II 600MHz core */
#घोषणा RII_CLKSEL_L3			(6 << 0)	/* 100MHz */
#घोषणा RII_CLKSEL_L4			(2 << 5)	/* 50MHz */
#घोषणा RII_CLKSEL_USB			(2 << 25)	/* 50MHz */
#घोषणा RII_CM_CLKSEL1_CORE_VAL		(RII_CLKSEL_USB | RXX_CLKSEL_SSI | \
					 RXX_CLKSEL_VLYNQ | RX_CLKSEL_DSS2 | \
					 RX_CLKSEL_DSS1 | RII_CLKSEL_L4 | \
					 RII_CLKSEL_L3)
#घोषणा RII_CLKSEL_MPU			(2 << 0)	/* 300MHz */
#घोषणा RII_CM_CLKSEL_MPU_VAL		RII_CLKSEL_MPU
#घोषणा RII_CLKSEL_DSP			(3 << 0)	/* c5x - 200MHz */
#घोषणा RII_CLKSEL_DSP_IF		(2 << 5)	/* c5x - 100MHz */
#घोषणा RII_SYNC_DSP			(0 << 7)	/* Bypass sync */
#घोषणा RII_CLKSEL_IVA			(3 << 8)	/* iva1 - 200MHz */
#घोषणा RII_SYNC_IVA			(0 << 13)	/* Bypass sync */
#घोषणा RII_CM_CLKSEL_DSP_VAL		(RII_SYNC_IVA | RII_CLKSEL_IVA | \
					 RII_SYNC_DSP | RII_CLKSEL_DSP_IF | \
					 RII_CLKSEL_DSP)
#घोषणा RII_CLKSEL_GFX			(2 << 0)	/* 50MHz */
#घोषणा RII_CM_CLKSEL_GFX_VAL		RII_CLKSEL_GFX

/* 2420-PRCM I 660MHz core */
#घोषणा RI_CLKSEL_L3			(4 << 0)	/* 165MHz */
#घोषणा RI_CLKSEL_L4			(2 << 5)	/* 82.5MHz */
#घोषणा RI_CLKSEL_USB			(4 << 25)	/* 41.25MHz */
#घोषणा RI_CM_CLKSEL1_CORE_VAL		(RI_CLKSEL_USB |		\
					 RXX_CLKSEL_SSI | RXX_CLKSEL_VLYNQ | \
					 RX_CLKSEL_DSS2 | RX_CLKSEL_DSS1 | \
					 RI_CLKSEL_L4 | RI_CLKSEL_L3)
#घोषणा RI_CLKSEL_MPU			(2 << 0)	/* 330MHz */
#घोषणा RI_CM_CLKSEL_MPU_VAL		RI_CLKSEL_MPU
#घोषणा RI_CLKSEL_DSP			(3 << 0)	/* c5x - 220MHz */
#घोषणा RI_CLKSEL_DSP_IF		(2 << 5)	/* c5x - 110MHz */
#घोषणा RI_SYNC_DSP			(1 << 7)	/* Activate sync */
#घोषणा RI_CLKSEL_IVA			(4 << 8)	/* iva1 - 165MHz */
#घोषणा RI_SYNC_IVA			(0 << 13)	/* Bypass sync */
#घोषणा RI_CM_CLKSEL_DSP_VAL		(RI_SYNC_IVA | RI_CLKSEL_IVA |	\
					 RI_SYNC_DSP | RI_CLKSEL_DSP_IF | \
					 RI_CLKSEL_DSP)
#घोषणा RI_CLKSEL_GFX			(1 << 0)	/* 165MHz */
#घोषणा RI_CM_CLKSEL_GFX_VAL		RI_CLKSEL_GFX

/* 2420-PRCM VII (boot) */
#घोषणा RVII_CLKSEL_L3			(1 << 0)
#घोषणा RVII_CLKSEL_L4			(1 << 5)
#घोषणा RVII_CLKSEL_DSS1		(1 << 8)
#घोषणा RVII_CLKSEL_DSS2		(0 << 13)
#घोषणा RVII_CLKSEL_VLYNQ		(1 << 15)
#घोषणा RVII_CLKSEL_SSI			(1 << 20)
#घोषणा RVII_CLKSEL_USB			(1 << 25)

#घोषणा RVII_CM_CLKSEL1_CORE_VAL	(RVII_CLKSEL_USB | RVII_CLKSEL_SSI | \
					 RVII_CLKSEL_VLYNQ | \
					 RVII_CLKSEL_DSS2 | RVII_CLKSEL_DSS1 | \
					 RVII_CLKSEL_L4 | RVII_CLKSEL_L3)

#घोषणा RVII_CLKSEL_MPU			(1 << 0) /* all भागide by 1 */
#घोषणा RVII_CM_CLKSEL_MPU_VAL		RVII_CLKSEL_MPU

#घोषणा RVII_CLKSEL_DSP			(1 << 0)
#घोषणा RVII_CLKSEL_DSP_IF		(1 << 5)
#घोषणा RVII_SYNC_DSP			(0 << 7)
#घोषणा RVII_CLKSEL_IVA			(1 << 8)
#घोषणा RVII_SYNC_IVA			(0 << 13)
#घोषणा RVII_CM_CLKSEL_DSP_VAL		(RVII_SYNC_IVA | RVII_CLKSEL_IVA | \
					 RVII_SYNC_DSP | RVII_CLKSEL_DSP_IF | \
					 RVII_CLKSEL_DSP)

#घोषणा RVII_CLKSEL_GFX			(1 << 0)
#घोषणा RVII_CM_CLKSEL_GFX_VAL		RVII_CLKSEL_GFX

/*-------------------------------------------------------------------------
 * 2430 Target modes: Aदीर्घ with each configuration the CPU has several
 * modes which goes aदीर्घ with them. Modes मुख्यly are the addition of
 * describe DPLL combinations to go aदीर्घ with a ratio.
 *-------------------------------------------------------------------------*/

/* Hardware governed */
#घोषणा MX_48M_SRC			(0 << 3)
#घोषणा MX_54M_SRC			(0 << 5)
#घोषणा MX_APLLS_CLIKIN_12		(3 << 23)
#घोषणा MX_APLLS_CLIKIN_13		(2 << 23)
#घोषणा MX_APLLS_CLIKIN_19_2		(0 << 23)

/*
 * 2430 - standalone, 2*ref*M/(n+1), M/N is क्रम exactness not relock speed
 * #5a	(ratio1) baseport-target, target DPLL = 266*2 = 532MHz
 */
#घोषणा M5A_DPLL_MULT_12		(133 << 12)
#घोषणा M5A_DPLL_DIV_12			(5 << 8)
#घोषणा M5A_CM_CLKSEL1_PLL_12_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M5A_DPLL_DIV_12 | M5A_DPLL_MULT_12 | \
					 MX_APLLS_CLIKIN_12)
#घोषणा M5A_DPLL_MULT_13		(61 << 12)
#घोषणा M5A_DPLL_DIV_13			(2 << 8)
#घोषणा M5A_CM_CLKSEL1_PLL_13_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M5A_DPLL_DIV_13 | M5A_DPLL_MULT_13 | \
					 MX_APLLS_CLIKIN_13)
#घोषणा M5A_DPLL_MULT_19		(55 << 12)
#घोषणा M5A_DPLL_DIV_19			(3 << 8)
#घोषणा M5A_CM_CLKSEL1_PLL_19_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M5A_DPLL_DIV_19 | M5A_DPLL_MULT_19 | \
					 MX_APLLS_CLIKIN_19_2)
/* #5b	(ratio1) target DPLL = 200*2 = 400MHz */
#घोषणा M5B_DPLL_MULT_12		(50 << 12)
#घोषणा M5B_DPLL_DIV_12			(2 << 8)
#घोषणा M5B_CM_CLKSEL1_PLL_12_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M5B_DPLL_DIV_12 | M5B_DPLL_MULT_12 | \
					 MX_APLLS_CLIKIN_12)
#घोषणा M5B_DPLL_MULT_13		(200 << 12)
#घोषणा M5B_DPLL_DIV_13			(12 << 8)

#घोषणा M5B_CM_CLKSEL1_PLL_13_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M5B_DPLL_DIV_13 | M5B_DPLL_MULT_13 | \
					 MX_APLLS_CLIKIN_13)
#घोषणा M5B_DPLL_MULT_19		(125 << 12)
#घोषणा M5B_DPLL_DIV_19			(31 << 8)
#घोषणा M5B_CM_CLKSEL1_PLL_19_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M5B_DPLL_DIV_19 | M5B_DPLL_MULT_19 | \
					 MX_APLLS_CLIKIN_19_2)
/*
 * #4	(ratio2), DPLL = 399*2 = 798MHz, L3=133MHz
 */
#घोषणा M4_DPLL_MULT_12			(133 << 12)
#घोषणा M4_DPLL_DIV_12			(3 << 8)
#घोषणा M4_CM_CLKSEL1_PLL_12_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M4_DPLL_DIV_12 | M4_DPLL_MULT_12 | \
					 MX_APLLS_CLIKIN_12)

#घोषणा M4_DPLL_MULT_13			(399 << 12)
#घोषणा M4_DPLL_DIV_13			(12 << 8)
#घोषणा M4_CM_CLKSEL1_PLL_13_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M4_DPLL_DIV_13 | M4_DPLL_MULT_13 | \
					 MX_APLLS_CLIKIN_13)

#घोषणा M4_DPLL_MULT_19			(145 << 12)
#घोषणा M4_DPLL_DIV_19			(6 << 8)
#घोषणा M4_CM_CLKSEL1_PLL_19_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M4_DPLL_DIV_19 | M4_DPLL_MULT_19 | \
					 MX_APLLS_CLIKIN_19_2)

/*
 * #3	(ratio2) baseport-target, target DPLL = 330*2 = 660MHz
 */
#घोषणा M3_DPLL_MULT_12			(55 << 12)
#घोषणा M3_DPLL_DIV_12			(1 << 8)
#घोषणा M3_CM_CLKSEL1_PLL_12_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M3_DPLL_DIV_12 | M3_DPLL_MULT_12 | \
					 MX_APLLS_CLIKIN_12)
#घोषणा M3_DPLL_MULT_13			(76 << 12)
#घोषणा M3_DPLL_DIV_13			(2 << 8)
#घोषणा M3_CM_CLKSEL1_PLL_13_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M3_DPLL_DIV_13 | M3_DPLL_MULT_13 | \
					 MX_APLLS_CLIKIN_13)
#घोषणा M3_DPLL_MULT_19			(17 << 12)
#घोषणा M3_DPLL_DIV_19			(0 << 8)
#घोषणा M3_CM_CLKSEL1_PLL_19_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M3_DPLL_DIV_19 | M3_DPLL_MULT_19 | \
					 MX_APLLS_CLIKIN_19_2)

/*
 * #2   (ratio1) DPLL = 330*2 = 660MHz, L3=165MHz
 */
#घोषणा M2_DPLL_MULT_12		        (55 << 12)
#घोषणा M2_DPLL_DIV_12		        (1 << 8)
#घोषणा M2_CM_CLKSEL1_PLL_12_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M2_DPLL_DIV_12 | M2_DPLL_MULT_12 | \
					 MX_APLLS_CLIKIN_12)

/* Speed changes - Used 658.7MHz instead of 660MHz क्रम LP-Refresh M=76 N=2,
 * relock समय issue */
/* Core frequency changed from 330/165 to 329/164 MHz*/
#घोषणा M2_DPLL_MULT_13		        (76 << 12)
#घोषणा M2_DPLL_DIV_13		        (2 << 8)
#घोषणा M2_CM_CLKSEL1_PLL_13_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M2_DPLL_DIV_13 | M2_DPLL_MULT_13 | \
					 MX_APLLS_CLIKIN_13)

#घोषणा M2_DPLL_MULT_19		        (17 << 12)
#घोषणा M2_DPLL_DIV_19		        (0 << 8)
#घोषणा M2_CM_CLKSEL1_PLL_19_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 M2_DPLL_DIV_19 | M2_DPLL_MULT_19 | \
					 MX_APLLS_CLIKIN_19_2)

/* boot (boot) */
#घोषणा MB_DPLL_MULT			(1 << 12)
#घोषणा MB_DPLL_DIV			(0 << 8)
#घोषणा MB_CM_CLKSEL1_PLL_12_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 MB_DPLL_DIV | MB_DPLL_MULT | \
					 MX_APLLS_CLIKIN_12)

#घोषणा MB_CM_CLKSEL1_PLL_13_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 MB_DPLL_DIV | MB_DPLL_MULT | \
					 MX_APLLS_CLIKIN_13)

#घोषणा MB_CM_CLKSEL1_PLL_19_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 MB_DPLL_DIV | MB_DPLL_MULT | \
					 MX_APLLS_CLIKIN_19)

/*
 * 2430 - chassis (sedna)
 * 165 (ratio1) same as above #2
 * 150 (ratio1)
 * 133 (ratio2) same as above #4
 * 110 (ratio2) same as above #3
 * 104 (ratio2)
 * boot (boot)
 */

/* PRCM I target DPLL = 2*330MHz = 660MHz */
#घोषणा MI_DPLL_MULT_12			(55 << 12)
#घोषणा MI_DPLL_DIV_12			(1 << 8)
#घोषणा MI_CM_CLKSEL1_PLL_12_VAL	(MX_48M_SRC | MX_54M_SRC | \
					 MI_DPLL_DIV_12 | MI_DPLL_MULT_12 | \
					 MX_APLLS_CLIKIN_12)

/*
 * 2420 Equivalent - mode रेजिस्टरs
 * PRCM II , target DPLL = 2*300MHz = 600MHz
 */
#घोषणा MII_DPLL_MULT_12		(50 << 12)
#घोषणा MII_DPLL_DIV_12			(1 << 8)
#घोषणा MII_CM_CLKSEL1_PLL_12_VAL	(MX_48M_SRC | MX_54M_SRC |	\
					 MII_DPLL_DIV_12 | MII_DPLL_MULT_12 | \
					 MX_APLLS_CLIKIN_12)
#घोषणा MII_DPLL_MULT_13		(300 << 12)
#घोषणा MII_DPLL_DIV_13			(12 << 8)
#घोषणा MII_CM_CLKSEL1_PLL_13_VAL	(MX_48M_SRC | MX_54M_SRC |	\
					 MII_DPLL_DIV_13 | MII_DPLL_MULT_13 | \
					 MX_APLLS_CLIKIN_13)

/* PRCM III target DPLL = 2*266 = 532MHz*/
#घोषणा MIII_DPLL_MULT_12		(133 << 12)
#घोषणा MIII_DPLL_DIV_12		(5 << 8)
#घोषणा MIII_CM_CLKSEL1_PLL_12_VAL	(MX_48M_SRC | MX_54M_SRC |	\
					 MIII_DPLL_DIV_12 | \
					 MIII_DPLL_MULT_12 | MX_APLLS_CLIKIN_12)
#घोषणा MIII_DPLL_MULT_13		(266 << 12)
#घोषणा MIII_DPLL_DIV_13		(12 << 8)
#घोषणा MIII_CM_CLKSEL1_PLL_13_VAL	(MX_48M_SRC | MX_54M_SRC |	\
					 MIII_DPLL_DIV_13 | \
					 MIII_DPLL_MULT_13 | MX_APLLS_CLIKIN_13)

/* PRCM VII (boot bypass) */
#घोषणा MVII_CM_CLKSEL1_PLL_12_VAL	MB_CM_CLKSEL1_PLL_12_VAL
#घोषणा MVII_CM_CLKSEL1_PLL_13_VAL	MB_CM_CLKSEL1_PLL_13_VAL

/* High and low operation value */
#घोषणा MX_CLKSEL2_PLL_2x_VAL		(2 << 0)
#घोषणा MX_CLKSEL2_PLL_1x_VAL		(1 << 0)

/* MPU speed defines */
#घोषणा S12M	12000000
#घोषणा S13M	13000000
#घोषणा S19M	19200000
#घोषणा S26M	26000000
#घोषणा S100M	100000000
#घोषणा S133M	133000000
#घोषणा S150M	150000000
#घोषणा S164M	164000000
#घोषणा S165M	165000000
#घोषणा S199M	199000000
#घोषणा S200M	200000000
#घोषणा S266M	266000000
#घोषणा S300M	300000000
#घोषणा S329M	329000000
#घोषणा S330M	330000000
#घोषणा S399M	399000000
#घोषणा S400M	400000000
#घोषणा S532M	532000000
#घोषणा S600M	600000000
#घोषणा S658M	658000000
#घोषणा S660M	660000000
#घोषणा S798M	798000000


बाह्य स्थिर काष्ठा prcm_config omap2420_rate_table[];

#अगर_घोषित CONFIG_SOC_OMAP2430
बाह्य स्थिर काष्ठा prcm_config omap2430_rate_table[];
#अन्यथा
#घोषणा omap2430_rate_table	शून्य
#पूर्ण_अगर
बाह्य स्थिर काष्ठा prcm_config *rate_table;
बाह्य स्थिर काष्ठा prcm_config *curr_prcm_set;

#पूर्ण_अगर
