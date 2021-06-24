<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OMAP3xxx घड़ीकरोमुख्यs
 *
 * Copyright (C) 2008-2011 Texas Instruments, Inc.
 * Copyright (C) 2008-2010 Nokia Corporation
 *
 * Paul Walmsley, Jouni Hथघgander
 *
 * This file contains घड़ीकरोमुख्यs and घड़ीकरोमुख्य wakeup/sleep
 * dependencies क्रम the OMAP3xxx chips.  Some notes:
 *
 * A useful validation rule क्रम काष्ठा घड़ीकरोमुख्य: Any घड़ीकरोमुख्य
 * referenced by a wkdep_srcs or sleepdep_srcs array must have a
 * dep_bit asचिन्हित.  So wkdep_srcs/sleepdep_srcs are really just
 * software-controllable dependencies.  Non-software-controllable
 * dependencies करो exist, but they are not encoded below (yet).
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
#समावेश "cm-regbits-34xx.h"
#समावेश "prm-regbits-34xx.h"

/*
 * Clockकरोमुख्य dependencies क्रम wkdeps/sleepdeps
 *
 * XXX Hardware dependencies (e.g., dependencies that cannot be
 * changed in software) are not included here yet, but should be.
 */

/* OMAP3-specअगरic possible dependencies */

/*
 * 3430ES1 PM_WKDEP_GFX: adds IVA2, हटाओs CORE
 * 3430ES2 PM_WKDEP_SGX: adds IVA2, हटाओs CORE
 */
अटल काष्ठा clkdm_dep gfx_sgx_3xxx_wkdeps[] = अणु
	अणु .clkdm_name = "iva2_clkdm" पूर्ण,
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep gfx_sgx_am35x_wkdeps[] = अणु
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* 3430: PM_WKDEP_PER: CORE, IVA2, MPU, WKUP */
अटल काष्ठा clkdm_dep per_wkdeps[] = अणु
	अणु .clkdm_name = "core_l3_clkdm" पूर्ण,
	अणु .clkdm_name = "core_l4_clkdm" पूर्ण,
	अणु .clkdm_name = "iva2_clkdm" पूर्ण,
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep per_am35x_wkdeps[] = अणु
	अणु .clkdm_name = "core_l3_clkdm" पूर्ण,
	अणु .clkdm_name = "core_l4_clkdm" पूर्ण,
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* 3430ES2: PM_WKDEP_USBHOST: CORE, IVA2, MPU, WKUP */
अटल काष्ठा clkdm_dep usbhost_wkdeps[] = अणु
	अणु .clkdm_name = "core_l3_clkdm" पूर्ण,
	अणु .clkdm_name = "core_l4_clkdm" पूर्ण,
	अणु .clkdm_name = "iva2_clkdm" पूर्ण,
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep usbhost_am35x_wkdeps[] = अणु
	अणु .clkdm_name = "core_l3_clkdm" पूर्ण,
	अणु .clkdm_name = "core_l4_clkdm" पूर्ण,
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* 3430 PM_WKDEP_MPU: CORE, IVA2, DSS, PER */
अटल काष्ठा clkdm_dep mpu_3xxx_wkdeps[] = अणु
	अणु .clkdm_name = "core_l3_clkdm" पूर्ण,
	अणु .clkdm_name = "core_l4_clkdm" पूर्ण,
	अणु .clkdm_name = "iva2_clkdm" पूर्ण,
	अणु .clkdm_name = "dss_clkdm" पूर्ण,
	अणु .clkdm_name = "per_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep mpu_am35x_wkdeps[] = अणु
	अणु .clkdm_name = "core_l3_clkdm" पूर्ण,
	अणु .clkdm_name = "core_l4_clkdm" पूर्ण,
	अणु .clkdm_name = "dss_clkdm" पूर्ण,
	अणु .clkdm_name = "per_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* 3430 PM_WKDEP_IVA2: CORE, MPU, WKUP, DSS, PER */
अटल काष्ठा clkdm_dep iva2_wkdeps[] = अणु
	अणु .clkdm_name = "core_l3_clkdm" पूर्ण,
	अणु .clkdm_name = "core_l4_clkdm" पूर्ण,
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु .clkdm_name = "dss_clkdm" पूर्ण,
	अणु .clkdm_name = "per_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* 3430 PM_WKDEP_CAM: IVA2, MPU, WKUP */
अटल काष्ठा clkdm_dep cam_wkdeps[] = अणु
	अणु .clkdm_name = "iva2_clkdm" पूर्ण,
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* 3430 PM_WKDEP_DSS: IVA2, MPU, WKUP */
अटल काष्ठा clkdm_dep dss_wkdeps[] = अणु
	अणु .clkdm_name = "iva2_clkdm" पूर्ण,
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep dss_am35x_wkdeps[] = अणु
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* 3430: PM_WKDEP_NEON: MPU */
अटल काष्ठा clkdm_dep neon_wkdeps[] = अणु
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* Sleep dependency source arrays क्रम OMAP3-specअगरic clkdms */

/* 3430: CM_SLEEPDEP_DSS: MPU, IVA */
अटल काष्ठा clkdm_dep dss_sleepdeps[] = अणु
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "iva2_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep dss_am35x_sleepdeps[] = अणु
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* 3430: CM_SLEEPDEP_PER: MPU, IVA */
अटल काष्ठा clkdm_dep per_sleepdeps[] = अणु
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "iva2_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep per_am35x_sleepdeps[] = अणु
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* 3430ES2: CM_SLEEPDEP_USBHOST: MPU, IVA */
अटल काष्ठा clkdm_dep usbhost_sleepdeps[] = अणु
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "iva2_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep usbhost_am35x_sleepdeps[] = अणु
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* 3430: CM_SLEEPDEP_CAM: MPU */
अटल काष्ठा clkdm_dep cam_sleepdeps[] = अणु
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/*
 * 3430ES1: CM_SLEEPDEP_GFX: MPU
 * 3430ES2: CM_SLEEPDEP_SGX: MPU
 * These can share data since they will never be present simultaneously
 * on the same device.
 */
अटल काष्ठा clkdm_dep gfx_sgx_sleepdeps[] = अणु
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/*
 * OMAP3 घड़ीकरोमुख्यs
 */

अटल काष्ठा घड़ीकरोमुख्य mpu_3xxx_clkdm = अणु
	.name		= "mpu_clkdm",
	.pwrdm		= अणु .name = "mpu_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP | CLKDM_CAN_FORCE_WAKEUP,
	.dep_bit	= OMAP3430_EN_MPU_SHIFT,
	.wkdep_srcs	= mpu_3xxx_wkdeps,
	.clktrctrl_mask = OMAP3430_CLKTRCTRL_MPU_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य mpu_am35x_clkdm = अणु
	.name		= "mpu_clkdm",
	.pwrdm		= अणु .name = "mpu_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP | CLKDM_CAN_FORCE_WAKEUP,
	.dep_bit	= OMAP3430_EN_MPU_SHIFT,
	.wkdep_srcs	= mpu_am35x_wkdeps,
	.clktrctrl_mask = OMAP3430_CLKTRCTRL_MPU_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य neon_clkdm = अणु
	.name		= "neon_clkdm",
	.pwrdm		= अणु .name = "neon_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.wkdep_srcs	= neon_wkdeps,
	.clktrctrl_mask = OMAP3430_CLKTRCTRL_NEON_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य iva2_clkdm = अणु
	.name		= "iva2_clkdm",
	.pwrdm		= अणु .name = "iva2_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_SWSUP,
	.dep_bit	= OMAP3430_PM_WKDEP_MPU_EN_IVA2_SHIFT,
	.wkdep_srcs	= iva2_wkdeps,
	.clktrctrl_mask = OMAP3430_CLKTRCTRL_IVA2_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य gfx_3430es1_clkdm = अणु
	.name		= "gfx_clkdm",
	.pwrdm		= अणु .name = "gfx_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.wkdep_srcs	= gfx_sgx_3xxx_wkdeps,
	.sleepdep_srcs	= gfx_sgx_sleepdeps,
	.clktrctrl_mask = OMAP3430ES1_CLKTRCTRL_GFX_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य sgx_clkdm = अणु
	.name		= "sgx_clkdm",
	.pwrdm		= अणु .name = "sgx_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.wkdep_srcs	= gfx_sgx_3xxx_wkdeps,
	.sleepdep_srcs	= gfx_sgx_sleepdeps,
	.clktrctrl_mask = OMAP3430ES2_CLKTRCTRL_SGX_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य sgx_am35x_clkdm = अणु
	.name		= "sgx_clkdm",
	.pwrdm		= अणु .name = "sgx_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.wkdep_srcs	= gfx_sgx_am35x_wkdeps,
	.sleepdep_srcs	= gfx_sgx_sleepdeps,
	.clktrctrl_mask = OMAP3430ES2_CLKTRCTRL_SGX_MASK,
पूर्ण;

/*
 * The die-to-die घड़ीकरोमुख्य was करोcumented in the 34xx ES1 TRM, but
 * then that inक्रमmation was हटाओd from the 34xx ES2+ TRM.  It is
 * unclear whether the core is still there, but the घड़ीकरोमुख्य logic
 * is there, and must be programmed to an appropriate state अगर the
 * CORE घड़ीकरोमुख्य is to become inactive.
 */
अटल काष्ठा घड़ीकरोमुख्य d2d_clkdm = अणु
	.name		= "d2d_clkdm",
	.pwrdm		= अणु .name = "core_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.clktrctrl_mask = OMAP3430ES1_CLKTRCTRL_D2D_MASK,
पूर्ण;

/*
 * XXX add usecounting क्रम clkdm dependencies, otherwise the presence
 * of a single dep bit क्रम core_l3_3xxx_clkdm and core_l4_3xxx_clkdm
 * could cause trouble
 */
अटल काष्ठा घड़ीकरोमुख्य core_l3_3xxx_clkdm = अणु
	.name		= "core_l3_clkdm",
	.pwrdm		= अणु .name = "core_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP,
	.dep_bit	= OMAP3430_EN_CORE_SHIFT,
	.clktrctrl_mask = OMAP3430_CLKTRCTRL_L3_MASK,
पूर्ण;

/*
 * XXX add usecounting क्रम clkdm dependencies, otherwise the presence
 * of a single dep bit क्रम core_l3_3xxx_clkdm and core_l4_3xxx_clkdm
 * could cause trouble
 */
अटल काष्ठा घड़ीकरोमुख्य core_l4_3xxx_clkdm = अणु
	.name		= "core_l4_clkdm",
	.pwrdm		= अणु .name = "core_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP,
	.dep_bit	= OMAP3430_EN_CORE_SHIFT,
	.clktrctrl_mask = OMAP3430_CLKTRCTRL_L4_MASK,
पूर्ण;

/* Another हाल of bit name collisions between several रेजिस्टरs: EN_DSS */
अटल काष्ठा घड़ीकरोमुख्य dss_3xxx_clkdm = अणु
	.name		= "dss_clkdm",
	.pwrdm		= अणु .name = "dss_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP3430_PM_WKDEP_MPU_EN_DSS_SHIFT,
	.wkdep_srcs	= dss_wkdeps,
	.sleepdep_srcs	= dss_sleepdeps,
	.clktrctrl_mask = OMAP3430_CLKTRCTRL_DSS_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य dss_am35x_clkdm = अणु
	.name		= "dss_clkdm",
	.pwrdm		= अणु .name = "dss_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP3430_PM_WKDEP_MPU_EN_DSS_SHIFT,
	.wkdep_srcs	= dss_am35x_wkdeps,
	.sleepdep_srcs	= dss_am35x_sleepdeps,
	.clktrctrl_mask = OMAP3430_CLKTRCTRL_DSS_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य cam_clkdm = अणु
	.name		= "cam_clkdm",
	.pwrdm		= अणु .name = "cam_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.wkdep_srcs	= cam_wkdeps,
	.sleepdep_srcs	= cam_sleepdeps,
	.clktrctrl_mask = OMAP3430_CLKTRCTRL_CAM_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य usbhost_clkdm = अणु
	.name		= "usbhost_clkdm",
	.pwrdm		= अणु .name = "usbhost_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.wkdep_srcs	= usbhost_wkdeps,
	.sleepdep_srcs	= usbhost_sleepdeps,
	.clktrctrl_mask = OMAP3430ES2_CLKTRCTRL_USBHOST_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य usbhost_am35x_clkdm = अणु
	.name		= "usbhost_clkdm",
	.pwrdm		= अणु .name = "core_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.wkdep_srcs	= usbhost_am35x_wkdeps,
	.sleepdep_srcs	= usbhost_am35x_sleepdeps,
	.clktrctrl_mask = OMAP3430ES2_CLKTRCTRL_USBHOST_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य per_clkdm = अणु
	.name		= "per_clkdm",
	.pwrdm		= अणु .name = "per_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP3430_EN_PER_SHIFT,
	.wkdep_srcs	= per_wkdeps,
	.sleepdep_srcs	= per_sleepdeps,
	.clktrctrl_mask = OMAP3430_CLKTRCTRL_PER_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य per_am35x_clkdm = अणु
	.name		= "per_clkdm",
	.pwrdm		= अणु .name = "per_pwrdm" पूर्ण,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
	.dep_bit	= OMAP3430_EN_PER_SHIFT,
	.wkdep_srcs	= per_am35x_wkdeps,
	.sleepdep_srcs	= per_am35x_sleepdeps,
	.clktrctrl_mask = OMAP3430_CLKTRCTRL_PER_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य emu_clkdm = अणु
	.name		= "emu_clkdm",
	.pwrdm		= अणु .name = "emu_pwrdm" पूर्ण,
	.flags		= (CLKDM_CAN_ENABLE_AUTO | CLKDM_CAN_SWSUP |
			   CLKDM_MISSING_IDLE_REPORTING),
	.clktrctrl_mask = OMAP3430_CLKTRCTRL_EMU_MASK,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य dpll1_clkdm = अणु
	.name		= "dpll1_clkdm",
	.pwrdm		= अणु .name = "dpll1_pwrdm" पूर्ण,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य dpll2_clkdm = अणु
	.name		= "dpll2_clkdm",
	.pwrdm		= अणु .name = "dpll2_pwrdm" पूर्ण,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य dpll3_clkdm = अणु
	.name		= "dpll3_clkdm",
	.pwrdm		= अणु .name = "dpll3_pwrdm" पूर्ण,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य dpll4_clkdm = अणु
	.name		= "dpll4_clkdm",
	.pwrdm		= अणु .name = "dpll4_pwrdm" पूर्ण,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य dpll5_clkdm = अणु
	.name		= "dpll5_clkdm",
	.pwrdm		= अणु .name = "dpll5_pwrdm" पूर्ण,
पूर्ण;

/*
 * Clockकरोमुख्य hwsup dependencies
 */

अटल काष्ठा clkdm_स्वतःdep clkdm_स्वतःdeps[] = अणु
	अणु
		.clkdm = अणु .name = "mpu_clkdm" पूर्ण,
	पूर्ण,
	अणु
		.clkdm = अणु .name = "iva2_clkdm" पूर्ण,
	पूर्ण,
	अणु
		.clkdm = अणु .name = शून्य पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा clkdm_स्वतःdep clkdm_am35x_स्वतःdeps[] = अणु
	अणु
		.clkdm = अणु .name = "mpu_clkdm" पूर्ण,
	पूर्ण,
	अणु
		.clkdm = अणु .name = शून्य पूर्ण,
	पूर्ण
पूर्ण;

/*
 *
 */

अटल काष्ठा घड़ीकरोमुख्य *घड़ीकरोमुख्यs_common[] __initdata = अणु
	&wkup_common_clkdm,
	&neon_clkdm,
	&core_l3_3xxx_clkdm,
	&core_l4_3xxx_clkdm,
	&emu_clkdm,
	&dpll1_clkdm,
	&dpll3_clkdm,
	&dpll4_clkdm,
	शून्य
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य *घड़ीकरोमुख्यs_omap3430[] __initdata = अणु
	&mpu_3xxx_clkdm,
	&iva2_clkdm,
	&d2d_clkdm,
	&dss_3xxx_clkdm,
	&cam_clkdm,
	&per_clkdm,
	&dpll2_clkdm,
	शून्य
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य *घड़ीकरोमुख्यs_omap3430es1[] __initdata = अणु
	&gfx_3430es1_clkdm,
	शून्य,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य *घड़ीकरोमुख्यs_omap3430es2plus[] __initdata = अणु
	&sgx_clkdm,
	&dpll5_clkdm,
	&usbhost_clkdm,
	शून्य,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य *घड़ीकरोमुख्यs_am35x[] __initdata = अणु
	&mpu_am35x_clkdm,
	&sgx_am35x_clkdm,
	&dss_am35x_clkdm,
	&per_am35x_clkdm,
	&usbhost_am35x_clkdm,
	&dpll5_clkdm,
	शून्य
पूर्ण;

व्योम __init omap3xxx_घड़ीकरोमुख्यs_init(व्योम)
अणु
	काष्ठा घड़ीकरोमुख्य **sc;
	अचिन्हित पूर्णांक rev;

	अगर (!cpu_is_omap34xx())
		वापस;

	clkdm_रेजिस्टर_platक्रमm_funcs(&omap3_clkdm_operations);
	clkdm_रेजिस्टर_clkdms(घड़ीकरोमुख्यs_common);

	rev = omap_rev();

	अगर (rev == AM35XX_REV_ES1_0 || rev == AM35XX_REV_ES1_1) अणु
		clkdm_रेजिस्टर_clkdms(घड़ीकरोमुख्यs_am35x);
		clkdm_रेजिस्टर_स्वतःdeps(clkdm_am35x_स्वतःdeps);
	पूर्ण अन्यथा अणु
		clkdm_रेजिस्टर_clkdms(घड़ीकरोमुख्यs_omap3430);

		sc = (rev == OMAP3430_REV_ES1_0) ?
			घड़ीकरोमुख्यs_omap3430es1 : घड़ीकरोमुख्यs_omap3430es2plus;

		clkdm_रेजिस्टर_clkdms(sc);
		clkdm_रेजिस्टर_स्वतःdeps(clkdm_स्वतःdeps);
	पूर्ण

	clkdm_complete_init();
पूर्ण
