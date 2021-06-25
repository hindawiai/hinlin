<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OMAP2/3 घड़ीकरोमुख्य common data
 *
 * Copyright (C) 2008-2011 Texas Instruments, Inc.
 * Copyright (C) 2008-2010 Nokia Corporation
 *
 * Paul Walmsley, Jouni Hथघgander
 *
 * This file contains घड़ीकरोमुख्यs and घड़ीकरोमुख्य wakeup/sleep
 * dependencies क्रम the OMAP2/3 chips.  Some notes:
 *
 * A useful validation rule क्रम काष्ठा घड़ीकरोमुख्य: Any घड़ीकरोमुख्य
 * referenced by a wkdep_srcs or sleepdep_srcs array must have a
 * dep_bit asचिन्हित.  So wkdep_srcs/sleepdep_srcs are really just
 * software-controllable dependencies.  Non-software-controllable
 * dependencies करो exist, but they are not encoded below (yet).
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

#समावेश "clockdomain.h"
#समावेश "prm2xxx_3xxx.h"
#समावेश "cm2xxx_3xxx.h"
#समावेश "cm-regbits-24xx.h"
#समावेश "cm-regbits-34xx.h"
#समावेश "cm-regbits-44xx.h"
#समावेश "prm-regbits-24xx.h"
#समावेश "prm-regbits-34xx.h"

/*
 * Clockकरोमुख्य dependencies क्रम wkdeps/sleepdeps
 *
 * XXX Hardware dependencies (e.g., dependencies that cannot be
 * changed in software) are not included here yet, but should be.
 */

/* Wakeup dependency source arrays */

/* 2xxx-specअगरic possible dependencies */

/* 2xxx PM_WKDEP_GFX: CORE, MPU, WKUP */
काष्ठा clkdm_dep gfx_24xx_wkdeps[] = अणु
	अणु .clkdm_name = "core_l3_clkdm" पूर्ण,
	अणु .clkdm_name = "core_l4_clkdm" पूर्ण,
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

/* 2xxx PM_WKDEP_DSP: CORE, MPU, WKUP */
काष्ठा clkdm_dep dsp_24xx_wkdeps[] = अणु
	अणु .clkdm_name = "core_l3_clkdm" पूर्ण,
	अणु .clkdm_name = "core_l4_clkdm" पूर्ण,
	अणु .clkdm_name = "mpu_clkdm" पूर्ण,
	अणु .clkdm_name = "wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;


/*
 * OMAP2/3-common घड़ीकरोमुख्यs
 *
 * Even though the 2420 has a single PRCM module from the
 * पूर्णांकerconnect's perspective, पूर्णांकernally it करोes appear to have
 * separate PRM and CM घड़ीकरोमुख्यs.  The usual test हाल is
 * sys_clkout/sys_clkout2.
 */

/* This is an implicit घड़ीकरोमुख्य - it is never defined as such in TRM */
काष्ठा घड़ीकरोमुख्य wkup_common_clkdm = अणु
	.name		= "wkup_clkdm",
	.pwrdm		= अणु .name = "wkup_pwrdm" पूर्ण,
	.dep_bit	= OMAP_EN_WKUP_SHIFT,
	.flags		= CLKDM_ACTIVE_WITH_MPU,
पूर्ण;
