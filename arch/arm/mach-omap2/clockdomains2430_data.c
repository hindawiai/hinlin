<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OMAP2xxx घड़ीकरोमुख्यs
 *
 * Copyright (C) 2008-2009 Texas Instruments, Inc.
 * Copyright (C) 2008-2010 Nokia Corporation
 *
 * Paul Walmsley, Jouni Hथघgander
 *
 * This file contains घड़ीकरोमुख्यs and घड़ीकरोमुख्य wakeup dependencies
 * क्रम OMAP2xxx chips.  Some notes:
 *
 * A useful validation rule क्रम काष्ठा घड़ीकरोमुख्य: Any घड़ीकरोमुख्य
 * referenced by a wkdep_srcs must have a dep_bit asचिन्हित.  So
 * wkdep_srcs are really just software-controllable dependencies.
 * Non-software-controllable dependencies करो exist, but they are not
 * encoded below (yet).
 *
 * 24xx करोes not support programmable sleep dependencies (SLEEPDEP)
 *
 * The overly-specअगरic dep_bit names are due to a bit name collision
 * with CM_FCLKEN_अणुDSP,IVA2पूर्ण.  The DSP/IVA2 PM_WKDEP and CM_SLEEPDEP shअगरt
 * value are the same क्रम all घातerकरोमुख्यs: 2
 *
 * XXX should dep_bit be a mask, so we can test to see अगर it is 0 as a
 * sanity check?
 * XXX encode hardware fixed wakeup dependencies -- esp. क्रम 3430 CORE
 */

/*
 * To-Do List
 * -> Port the Sleep/Wakeup dependencies क्रम the करोमुख्यs
 *    from the Power करोमुख्य framework
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>

#समावेश "soc.h"
#समावेश "clockdomain.h"
#समावेश "prm2xxx_3xxx.h"
#समावेश "cm2xxx_3xxx.h"
#समावेश "cm-regbits-24xx.h"
#समावेश "prm-regbits-24xx.h"

/*
 * Clockकरोमुख्य dependencies क्रम wkdeps
 *
 * XXX Hardware dependencies (e.g., dependencies that cannot be
 * changed in software) are not included here yet, but should be.
 */

/* Wakeup dependency source arrays */

/* 2430-specअगरic possible wakeup dependencies */

/* 2430 PM_WKDEP_CORE: DSP, GFX, MPU, WKUP, MDM */
अटल काष्ठा clkdm_dep core_2430_wkdeps[] = अणु
	अणु .clkdm_name = "dsp_clkdm" पूर्ण,
	अणु .clkdm_name = "gfx_clkdm" पूर्ण,
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु .clkdm_name = "mdm_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* 2430 PM_WKDEP_MPU: CORE, DSP, WKUP, MDM */
अटल काष्ठा clkdm_dep mpu_2430_wkdeps[] = अणु
	अणु .clkdm_name = "core_l3_clkdm" पूर्ण,
	अणु .clkdm_name = "core_l4_clkdm" पूर्ण,
	अणु .clkdm_name = "dsp_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु .clkdm_name = "mdm_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* 2430 PM_WKDEP_MDM: CORE, MPU, WKUP */
अटल काष्ठा clkdm_dep mdm_2430_wkdeps[] = अणु
	अणु .clkdm_name = "core_l3_clkdm" पूर्ण,
	अणु .clkdm_name = "core_l4_clkdm" पूर्ण,
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/*
 * 2430-only घड़ीकरोमुख्यs
 */

अटल काष्ठा घड़ीकरोमुख्य mpu_2430_clkdm = अणु
	.name		= "mpu_clkdm",
	.pwrdm		= अणु .name = "mpu_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.wkdep_srcs	= mpu_2430_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_MPU_MASK,
पूर्ण;

/* Another हाल of bit name collisions between several रेजिस्टरs: EN_MDM */
अटल काष्ठा घड़ीकरोमुख्य mdm_clkdm = अणु
	.name		= "mdm_clkdm",
	.pwrdm		= अणु .name = "mdm_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP2430_PM_WKDEP_MPU_EN_MDM_SHIFT,
	.wkdep_srcs	= mdm_2430_wkdeps,
	.clktrctrl_mask = OMAP2430_AUTOSTATE_MDM_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य dsp_2430_clkdm = अणु
	.name		= "dsp_clkdm",
	.pwrdm		= अणु .name = "dsp_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP24XX_PM_WKDEP_MPU_EN_DSP_SHIFT,
	.wkdep_srcs	= dsp_24xx_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_DSP_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य gfx_2430_clkdm = अणु
	.name		= "gfx_clkdm",
	.pwrdm		= अणु .name = "gfx_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.wkdep_srcs	= gfx_24xx_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_GFX_MASK,
पूर्ण;

/*
 * XXX add usecounting क्रम clkdm dependencies, otherwise the presence
 * of a single dep bit क्रम core_l3_24xx_clkdm and core_l4_24xx_clkdm
 * could cause trouble
 */
अटल काष्ठा घड़ीकरोमुख्य core_l3_2430_clkdm = अणु
	.name		= "core_l3_clkdm",
	.pwrdm		= अणु .name = "core_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP,
	.dep_bit	= OMAP24XX_EN_CORE_SHIFT,
	.wkdep_srcs	= core_2430_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_L3_MASK,
पूर्ण;

/*
 * XXX add usecounting क्रम clkdm dependencies, otherwise the presence
 * of a single dep bit क्रम core_l3_24xx_clkdm and core_l4_24xx_clkdm
 * could cause trouble
 */
अटल काष्ठा घड़ीकरोमुख्य core_l4_2430_clkdm = अणु
	.name		= "core_l4_clkdm",
	.pwrdm		= अणु .name = "core_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP,
	.dep_bit	= OMAP24XX_EN_CORE_SHIFT,
	.wkdep_srcs	= core_2430_wkdeps,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_L4_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य dss_2430_clkdm = अणु
	.name		= "dss_clkdm",
	.pwrdm		= अणु .name = "core_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP,
	.clktrctrl_mask = OMAP24XX_AUTOSTATE_DSS_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य *घड़ीकरोमुख्यs_omap243x[] __initdata = अणु
	&wkup_common_clkdm,
	&mpu_2430_clkdm,
	&mdm_clkdm,
	&dsp_2430_clkdm,
	&gfx_2430_clkdm,
	&core_l3_2430_clkdm,
	&core_l4_2430_clkdm,
	&dss_2430_clkdm,
	शून्य,
पूर्ण;

व्योम __init omap243x_घड़ीकरोमुख्यs_init(व्योम)
अणु
	अगर (!cpu_is_omap243x())
		वापस;

	clkdm_रेजिस्टर_platक्रमm_funcs(&omap2_clkdm_operations);
	clkdm_रेजिस्टर_clkdms(घड़ीकरोमुख्यs_omap243x);
	clkdm_complete_init();
पूर्ण

