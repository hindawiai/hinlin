<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-omap2/घड़ी.c
 *
 *  Copyright (C) 2005-2008 Texas Instruments, Inc.
 *  Copyright (C) 2004-2010 Nokia Corporation
 *
 *  Contacts:
 *  Riअक्षरd Woodruff <r-woodruff2@ti.com>
 *  Paul Walmsley
 */
#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/bitops.h>
#समावेश <linux/of_address.h>
#समावेश <यंत्र/cpu.h>

#समावेश <trace/events/घातer.h>

#समावेश "soc.h"
#समावेश "clockdomain.h"
#समावेश "clock.h"
#समावेश "cm.h"
#समावेश "cm2xxx.h"
#समावेश "cm3xxx.h"
#समावेश "cm-regbits-24xx.h"
#समावेश "cm-regbits-34xx.h"
#समावेश "common.h"

u16 cpu_mask;

/* DPLL valid Fपूर्णांक frequency band limits - from 34xx TRM Section 4.7.6.2 */
#घोषणा OMAP3430_DPLL_FINT_BAND1_MIN	750000
#घोषणा OMAP3430_DPLL_FINT_BAND1_MAX	2100000
#घोषणा OMAP3430_DPLL_FINT_BAND2_MIN	7500000
#घोषणा OMAP3430_DPLL_FINT_BAND2_MAX	21000000

/*
 * DPLL valid Fपूर्णांक frequency range क्रम OMAP36xx and OMAP4xxx.
 * From device data manual section 4.3 "DPLL and DLL Specifications".
 */
#घोषणा OMAP3PLUS_DPLL_Fपूर्णांक_न्यून		32000
#घोषणा OMAP3PLUS_DPLL_Fपूर्णांक_उच्च		52000000

काष्ठा ti_clk_ll_ops omap_clk_ll_ops = अणु
	.clkdm_clk_enable = clkdm_clk_enable,
	.clkdm_clk_disable = clkdm_clk_disable,
	.clkdm_lookup = clkdm_lookup,
	.cm_रुको_module_पढ़ोy = omap_cm_रुको_module_पढ़ोy,
	.cm_split_idlest_reg = cm_split_idlest_reg,
पूर्ण;

/**
 * omap2_clk_setup_ll_ops - setup घड़ी driver low-level ops
 *
 * Sets up घड़ी driver low-level platक्रमm ops. These are needed
 * क्रम रेजिस्टर accesses and various other misc platक्रमm operations.
 * Returns 0 on success, -EBUSY अगर low level ops have been रेजिस्टरed
 * alपढ़ोy.
 */
पूर्णांक __init omap2_clk_setup_ll_ops(व्योम)
अणु
	वापस ti_clk_setup_ll_ops(&omap_clk_ll_ops);
पूर्ण

/*
 * OMAP2+ specअगरic घड़ी functions
 */

/**
 * ti_clk_init_features - init घड़ी features काष्ठा क्रम the SoC
 *
 * Initializes the घड़ी features काष्ठा based on the SoC type.
 */
व्योम __init ti_clk_init_features(व्योम)
अणु
	काष्ठा ti_clk_features features = अणु 0 पूर्ण;
	/* Fपूर्णांक setup क्रम DPLLs */
	अगर (cpu_is_omap3430()) अणु
		features.fपूर्णांक_min = OMAP3430_DPLL_FINT_BAND1_MIN;
		features.fपूर्णांक_max = OMAP3430_DPLL_FINT_BAND2_MAX;
		features.fपूर्णांक_band1_max = OMAP3430_DPLL_FINT_BAND1_MAX;
		features.fपूर्णांक_band2_min = OMAP3430_DPLL_FINT_BAND2_MIN;
	पूर्ण अन्यथा अणु
		features.fपूर्णांक_min = OMAP3PLUS_DPLL_Fपूर्णांक_न्यून;
		features.fपूर्णांक_max = OMAP3PLUS_DPLL_Fपूर्णांक_उच्च;
	पूर्ण

	/* Bypass value setup क्रम DPLLs */
	अगर (cpu_is_omap24xx()) अणु
		features.dpll_bypass_vals |=
			(1 << OMAP2XXX_EN_DPLL_LPBYPASS) |
			(1 << OMAP2XXX_EN_DPLL_FRBYPASS);
	पूर्ण अन्यथा अगर (cpu_is_omap34xx()) अणु
		features.dpll_bypass_vals |=
			(1 << OMAP3XXX_EN_DPLL_LPBYPASS) |
			(1 << OMAP3XXX_EN_DPLL_FRBYPASS);
	पूर्ण अन्यथा अगर (soc_is_am33xx() || cpu_is_omap44xx() || soc_is_am43xx() ||
		   soc_is_omap54xx() || soc_is_dra7xx()) अणु
		features.dpll_bypass_vals |=
			(1 << OMAP4XXX_EN_DPLL_LPBYPASS) |
			(1 << OMAP4XXX_EN_DPLL_FRBYPASS) |
			(1 << OMAP4XXX_EN_DPLL_MNBYPASS);
	पूर्ण

	/* Jitter correction only available on OMAP343X */
	अगर (cpu_is_omap343x())
		features.flags |= TI_CLK_DPLL_HAS_FREQSEL;

	अगर (omap_type() == OMAP2_DEVICE_TYPE_GP)
		features.flags |= TI_CLK_DEVICE_TYPE_GP;

	/* Idlest value क्रम पूर्णांकerface घड़ीs.
	 * 24xx uses 0 to indicate not पढ़ोy, and 1 to indicate पढ़ोy.
	 * 34xx reverses this, just to keep us on our toes
	 * AM35xx uses both, depending on the module.
	 */
	अगर (cpu_is_omap24xx())
		features.cm_idlest_val = OMAP24XX_CM_IDLEST_VAL;
	अन्यथा अगर (cpu_is_omap34xx())
		features.cm_idlest_val = OMAP34XX_CM_IDLEST_VAL;

	/* On OMAP3430 ES1.0, DPLL4 can't be re-programmed */
	अगर (omap_rev() == OMAP3430_REV_ES1_0)
		features.flags |= TI_CLK_DPLL4_DENY_REPROGRAM;

	/* Errata I810 क्रम omap5 / dra7 */
	अगर (soc_is_omap54xx() || soc_is_dra7xx())
		features.flags |= TI_CLK_ERRATA_I810;

	ti_clk_setup_features(&features);
पूर्ण
