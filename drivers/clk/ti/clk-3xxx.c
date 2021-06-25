<शैली गुरु>
/*
 * OMAP3 Clock init
 *
 * Copyright (C) 2013 Texas Instruments, Inc
 *     Tero Kristo (t-kristo@ti.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/ti.h>

#समावेश "clock.h"

#घोषणा OMAP3430ES2_ST_DSS_IDLE_SHIFT			1
#घोषणा OMAP3430ES2_ST_HSOTGUSB_IDLE_SHIFT		5
#घोषणा OMAP3430ES2_ST_SSI_IDLE_SHIFT			8

#घोषणा OMAP34XX_CM_IDLEST_VAL				1

/*
 * In AM35xx IPSS, the अणुICK,FCKपूर्ण enable bits क्रम modules are exported
 * in the same रेजिस्टर at a bit offset of 0x8. The EN_ACK क्रम ICK is
 * at an offset of 4 from ICK enable bit.
 */
#घोषणा AM35XX_IPSS_ICK_MASK			0xF
#घोषणा AM35XX_IPSS_ICK_EN_ACK_OFFSET		0x4
#घोषणा AM35XX_IPSS_ICK_FCK_OFFSET		0x8
#घोषणा AM35XX_IPSS_CLK_IDLEST_VAL		0

#घोषणा AM35XX_ST_IPSS_SHIFT			5

/**
 * omap3430es2_clk_ssi_find_idlest - वापस CM_IDLEST info क्रम SSI
 * @clk: काष्ठा clk * being enabled
 * @idlest_reg: व्योम __iomem ** to store CM_IDLEST reg address पूर्णांकo
 * @idlest_bit: poपूर्णांकer to a u8 to store the CM_IDLEST bit shअगरt पूर्णांकo
 * @idlest_val: poपूर्णांकer to a u8 to store the CM_IDLEST indicator
 *
 * The OMAP3430ES2 SSI target CM_IDLEST bit is at a dअगरferent shअगरt
 * from the CM_अणुI,Fपूर्णCLKEN bit.  Pass back the correct info via
 * @idlest_reg and @idlest_bit.  No वापस value.
 */
अटल व्योम omap3430es2_clk_ssi_find_idlest(काष्ठा clk_hw_omap *clk,
					    काष्ठा clk_omap_reg *idlest_reg,
					    u8 *idlest_bit,
					    u8 *idlest_val)
अणु
	स_नकल(idlest_reg, &clk->enable_reg, माप(*idlest_reg));
	idlest_reg->offset &= ~0xf0;
	idlest_reg->offset |= 0x20;
	*idlest_bit = OMAP3430ES2_ST_SSI_IDLE_SHIFT;
	*idlest_val = OMAP34XX_CM_IDLEST_VAL;
पूर्ण

स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap3430es2_iclk_ssi_रुको = अणु
	.allow_idle	= omap2_clkt_iclk_allow_idle,
	.deny_idle	= omap2_clkt_iclk_deny_idle,
	.find_idlest	= omap3430es2_clk_ssi_find_idlest,
	.find_companion	= omap2_clk_dflt_find_companion,
पूर्ण;

/**
 * omap3430es2_clk_dss_usbhost_find_idlest - CM_IDLEST info क्रम DSS, USBHOST
 * @clk: काष्ठा clk * being enabled
 * @idlest_reg: व्योम __iomem ** to store CM_IDLEST reg address पूर्णांकo
 * @idlest_bit: poपूर्णांकer to a u8 to store the CM_IDLEST bit shअगरt पूर्णांकo
 * @idlest_val: poपूर्णांकer to a u8 to store the CM_IDLEST indicator
 *
 * Some OMAP modules on OMAP3 ES2+ chips have both initiator and
 * target IDLEST bits.  For our purposes, we are concerned with the
 * target IDLEST bits, which exist at a dअगरferent bit position than
 * the *CLKEN bit position क्रम these modules (DSS and USBHOST) (The
 * शेष find_idlest code assumes that they are at the same
 * position.)  No वापस value.
 */
अटल व्योम
omap3430es2_clk_dss_usbhost_find_idlest(काष्ठा clk_hw_omap *clk,
					काष्ठा clk_omap_reg *idlest_reg,
					u8 *idlest_bit, u8 *idlest_val)
अणु
	स_नकल(idlest_reg, &clk->enable_reg, माप(*idlest_reg));

	idlest_reg->offset &= ~0xf0;
	idlest_reg->offset |= 0x20;
	/* USBHOST_IDLE has same shअगरt */
	*idlest_bit = OMAP3430ES2_ST_DSS_IDLE_SHIFT;
	*idlest_val = OMAP34XX_CM_IDLEST_VAL;
पूर्ण

स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap3430es2_dss_usbhost_रुको = अणु
	.find_idlest	= omap3430es2_clk_dss_usbhost_find_idlest,
	.find_companion	= omap2_clk_dflt_find_companion,
पूर्ण;

स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap3430es2_iclk_dss_usbhost_रुको = अणु
	.allow_idle	= omap2_clkt_iclk_allow_idle,
	.deny_idle	= omap2_clkt_iclk_deny_idle,
	.find_idlest	= omap3430es2_clk_dss_usbhost_find_idlest,
	.find_companion	= omap2_clk_dflt_find_companion,
पूर्ण;

/**
 * omap3430es2_clk_hsotgusb_find_idlest - वापस CM_IDLEST info क्रम HSOTGUSB
 * @clk: काष्ठा clk * being enabled
 * @idlest_reg: व्योम __iomem ** to store CM_IDLEST reg address पूर्णांकo
 * @idlest_bit: poपूर्णांकer to a u8 to store the CM_IDLEST bit shअगरt पूर्णांकo
 * @idlest_val: poपूर्णांकer to a u8 to store the CM_IDLEST indicator
 *
 * The OMAP3430ES2 HSOTGUSB target CM_IDLEST bit is at a dअगरferent
 * shअगरt from the CM_अणुI,Fपूर्णCLKEN bit.  Pass back the correct info via
 * @idlest_reg and @idlest_bit.  No वापस value.
 */
अटल व्योम
omap3430es2_clk_hsotgusb_find_idlest(काष्ठा clk_hw_omap *clk,
				     काष्ठा clk_omap_reg *idlest_reg,
				     u8 *idlest_bit,
				     u8 *idlest_val)
अणु
	स_नकल(idlest_reg, &clk->enable_reg, माप(*idlest_reg));
	idlest_reg->offset &= ~0xf0;
	idlest_reg->offset |= 0x20;
	*idlest_bit = OMAP3430ES2_ST_HSOTGUSB_IDLE_SHIFT;
	*idlest_val = OMAP34XX_CM_IDLEST_VAL;
पूर्ण

स्थिर काष्ठा clk_hw_omap_ops clkhwops_omap3430es2_iclk_hsotgusb_रुको = अणु
	.allow_idle	= omap2_clkt_iclk_allow_idle,
	.deny_idle	= omap2_clkt_iclk_deny_idle,
	.find_idlest	= omap3430es2_clk_hsotgusb_find_idlest,
	.find_companion	= omap2_clk_dflt_find_companion,
पूर्ण;

/**
 * am35xx_clk_find_idlest - वापस घड़ी ACK info क्रम AM35XX IPSS
 * @clk: काष्ठा clk * being enabled
 * @idlest_reg: व्योम __iomem ** to store CM_IDLEST reg address पूर्णांकo
 * @idlest_bit: poपूर्णांकer to a u8 to store the CM_IDLEST bit shअगरt पूर्णांकo
 * @idlest_val: poपूर्णांकer to a u8 to store the CM_IDLEST indicator
 *
 * The पूर्णांकerface घड़ीs on AM35xx IPSS reflects the घड़ी idle status
 * in the enable रेजिस्टर itsel at a bit offset of 4 from the enable
 * bit. A value of 1 indicates that घड़ी is enabled.
 */
अटल व्योम am35xx_clk_find_idlest(काष्ठा clk_hw_omap *clk,
				   काष्ठा clk_omap_reg *idlest_reg,
				   u8 *idlest_bit,
				   u8 *idlest_val)
अणु
	स_नकल(idlest_reg, &clk->enable_reg, माप(*idlest_reg));
	*idlest_bit = clk->enable_bit + AM35XX_IPSS_ICK_EN_ACK_OFFSET;
	*idlest_val = AM35XX_IPSS_CLK_IDLEST_VAL;
पूर्ण

/**
 * am35xx_clk_find_companion - find companion घड़ी to @clk
 * @clk: काष्ठा clk * to find the companion घड़ी of
 * @other_reg: व्योम __iomem ** to वापस the companion घड़ी CM_*CLKEN va in
 * @other_bit: u8 ** to वापस the companion घड़ी bit shअगरt in
 *
 * Some घड़ीs करोn't have companion घड़ीs.  For example, modules with
 * only an पूर्णांकerface घड़ी (such as HECC) करोn't have a companion
 * घड़ी.  Right now, this code relies on the hardware exporting a bit
 * in the correct companion रेजिस्टर that indicates that the
 * nonexistent 'companion clock' is active.  Future patches will
 * associate this type of code with per-module data काष्ठाures to
 * aव्योम this issue, and हटाओ the casts.  No वापस value.
 */
अटल व्योम am35xx_clk_find_companion(काष्ठा clk_hw_omap *clk,
				      काष्ठा clk_omap_reg *other_reg,
				      u8 *other_bit)
अणु
	स_नकल(other_reg, &clk->enable_reg, माप(*other_reg));
	अगर (clk->enable_bit & AM35XX_IPSS_ICK_MASK)
		*other_bit = clk->enable_bit + AM35XX_IPSS_ICK_FCK_OFFSET;
	अन्यथा
	*other_bit = clk->enable_bit - AM35XX_IPSS_ICK_FCK_OFFSET;
पूर्ण

स्थिर काष्ठा clk_hw_omap_ops clkhwops_am35xx_ipss_module_रुको = अणु
	.find_idlest	= am35xx_clk_find_idlest,
	.find_companion	= am35xx_clk_find_companion,
पूर्ण;

/**
 * am35xx_clk_ipss_find_idlest - वापस CM_IDLEST info क्रम IPSS
 * @clk: काष्ठा clk * being enabled
 * @idlest_reg: व्योम __iomem ** to store CM_IDLEST reg address पूर्णांकo
 * @idlest_bit: poपूर्णांकer to a u8 to store the CM_IDLEST bit shअगरt पूर्णांकo
 * @idlest_val: poपूर्णांकer to a u8 to store the CM_IDLEST indicator
 *
 * The IPSS target CM_IDLEST bit is at a dअगरferent shअगरt from the
 * CM_अणुI,Fपूर्णCLKEN bit.  Pass back the correct info via @idlest_reg
 * and @idlest_bit.  No वापस value.
 */
अटल व्योम am35xx_clk_ipss_find_idlest(काष्ठा clk_hw_omap *clk,
					काष्ठा clk_omap_reg *idlest_reg,
					u8 *idlest_bit,
					u8 *idlest_val)
अणु
	स_नकल(idlest_reg, &clk->enable_reg, माप(*idlest_reg));

	idlest_reg->offset &= ~0xf0;
	idlest_reg->offset |= 0x20;
	*idlest_bit = AM35XX_ST_IPSS_SHIFT;
	*idlest_val = OMAP34XX_CM_IDLEST_VAL;
पूर्ण

स्थिर काष्ठा clk_hw_omap_ops clkhwops_am35xx_ipss_रुको = अणु
	.allow_idle	= omap2_clkt_iclk_allow_idle,
	.deny_idle	= omap2_clkt_iclk_deny_idle,
	.find_idlest	= am35xx_clk_ipss_find_idlest,
	.find_companion	= omap2_clk_dflt_find_companion,
पूर्ण;

अटल काष्ठा ti_dt_clk omap3xxx_clks[] = अणु
	DT_CLK(शून्य, "timer_32k_ck", "omap_32k_fck"),
	DT_CLK(शून्य, "timer_sys_ck", "sys_ck"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

अटल काष्ठा ti_dt_clk omap36xx_omap3430es2plus_clks[] = अणु
	DT_CLK(शून्य, "ssi_ssr_fck", "ssi_ssr_fck_3430es2"),
	DT_CLK(शून्य, "ssi_sst_fck", "ssi_sst_fck_3430es2"),
	DT_CLK(शून्य, "hsotgusb_ick", "hsotgusb_ick_3430es2"),
	DT_CLK(शून्य, "ssi_ick", "ssi_ick_3430es2"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

अटल काष्ठा ti_dt_clk omap3430es1_clks[] = अणु
	DT_CLK(शून्य, "ssi_ssr_fck", "ssi_ssr_fck_3430es1"),
	DT_CLK(शून्य, "ssi_sst_fck", "ssi_sst_fck_3430es1"),
	DT_CLK(शून्य, "hsotgusb_ick", "hsotgusb_ick_3430es1"),
	DT_CLK(शून्य, "ssi_ick", "ssi_ick_3430es1"),
	DT_CLK(शून्य, "dss1_alwon_fck", "dss1_alwon_fck_3430es1"),
	DT_CLK(शून्य, "dss_ick", "dss_ick_3430es1"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

अटल काष्ठा ti_dt_clk omap36xx_am35xx_omap3430es2plus_clks[] = अणु
	DT_CLK(शून्य, "dss1_alwon_fck", "dss1_alwon_fck_3430es2"),
	DT_CLK(शून्य, "dss_ick", "dss_ick_3430es2"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

अटल काष्ठा ti_dt_clk am35xx_clks[] = अणु
	DT_CLK(शून्य, "hsotgusb_ick", "hsotgusb_ick_am35xx"),
	DT_CLK(शून्य, "hsotgusb_fck", "hsotgusb_fck_am35xx"),
	DT_CLK(शून्य, "uart4_ick", "uart4_ick_am35xx"),
	DT_CLK(शून्य, "uart4_fck", "uart4_fck_am35xx"),
	अणु .node_name = शून्य पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *enable_init_clks[] = अणु
	"sdrc_ick",
	"gpmc_fck",
	"omapctrl_ick",
पूर्ण;

क्रमागत अणु
	OMAP3_SOC_AM35XX,
	OMAP3_SOC_OMAP3430_ES1,
	OMAP3_SOC_OMAP3430_ES2_PLUS,
	OMAP3_SOC_OMAP3630,
पूर्ण;

/**
 * omap3_clk_lock_dpll5 - locks DPLL5
 *
 * Locks DPLL5 to a pre-defined frequency. This is required क्रम proper
 * operation of USB.
 */
व्योम __init omap3_clk_lock_dpll5(व्योम)
अणु
	काष्ठा clk *dpll5_clk;
	काष्ठा clk *dpll5_m2_clk;

	/*
	 * Errata sprz319f advisory 2.1 करोcuments a USB host घड़ी drअगरt issue
	 * that can be worked around using specially crafted dpll5 settings
	 * with a dpll5_m2 भागider set to 8. Set the dpll5 rate to 8x the USB
	 * host घड़ी rate, its .set_rate handler() will detect that frequency
	 * and use the errata settings.
	 */
	dpll5_clk = clk_get(शून्य, "dpll5_ck");
	clk_set_rate(dpll5_clk, OMAP3_DPLL5_FREQ_FOR_USBHOST * 8);
	clk_prepare_enable(dpll5_clk);

	/* Program dpll5_m2_clk भागider */
	dpll5_m2_clk = clk_get(शून्य, "dpll5_m2_ck");
	clk_prepare_enable(dpll5_m2_clk);
	clk_set_rate(dpll5_m2_clk, OMAP3_DPLL5_FREQ_FOR_USBHOST);

	clk_disable_unprepare(dpll5_m2_clk);
	clk_disable_unprepare(dpll5_clk);
पूर्ण

अटल पूर्णांक __init omap3xxx_dt_clk_init(पूर्णांक soc_type)
अणु
	अगर (soc_type == OMAP3_SOC_AM35XX || soc_type == OMAP3_SOC_OMAP3630 ||
	    soc_type == OMAP3_SOC_OMAP3430_ES1 ||
	    soc_type == OMAP3_SOC_OMAP3430_ES2_PLUS)
		ti_dt_घड़ीs_रेजिस्टर(omap3xxx_clks);

	अगर (soc_type == OMAP3_SOC_AM35XX)
		ti_dt_घड़ीs_रेजिस्टर(am35xx_clks);

	अगर (soc_type == OMAP3_SOC_OMAP3630 || soc_type == OMAP3_SOC_AM35XX ||
	    soc_type == OMAP3_SOC_OMAP3430_ES2_PLUS)
		ti_dt_घड़ीs_रेजिस्टर(omap36xx_am35xx_omap3430es2plus_clks);

	अगर (soc_type == OMAP3_SOC_OMAP3430_ES1)
		ti_dt_घड़ीs_रेजिस्टर(omap3430es1_clks);

	अगर (soc_type == OMAP3_SOC_OMAP3430_ES2_PLUS ||
	    soc_type == OMAP3_SOC_OMAP3630)
		ti_dt_घड़ीs_रेजिस्टर(omap36xx_omap3430es2plus_clks);

	omap2_clk_disable_स्वतःidle_all();

	ti_clk_add_aliases();

	omap2_clk_enable_init_घड़ीs(enable_init_clks,
				     ARRAY_SIZE(enable_init_clks));

	pr_info("Clocking rate (Crystal/Core/MPU): %ld.%01ld/%ld/%ld MHz\n",
		(clk_get_rate(clk_get_sys(शून्य, "osc_sys_ck")) / 1000000),
		(clk_get_rate(clk_get_sys(शून्य, "osc_sys_ck")) / 100000) % 10,
		(clk_get_rate(clk_get_sys(शून्य, "core_ck")) / 1000000),
		(clk_get_rate(clk_get_sys(शून्य, "arm_fck")) / 1000000));

	अगर (soc_type != OMAP3_SOC_OMAP3430_ES1)
		omap3_clk_lock_dpll5();

	वापस 0;
पूर्ण

पूर्णांक __init omap3430_dt_clk_init(व्योम)
अणु
	वापस omap3xxx_dt_clk_init(OMAP3_SOC_OMAP3430_ES2_PLUS);
पूर्ण

पूर्णांक __init omap3630_dt_clk_init(व्योम)
अणु
	वापस omap3xxx_dt_clk_init(OMAP3_SOC_OMAP3630);
पूर्ण

पूर्णांक __init am35xx_dt_clk_init(व्योम)
अणु
	वापस omap3xxx_dt_clk_init(OMAP3_SOC_AM35XX);
पूर्ण
