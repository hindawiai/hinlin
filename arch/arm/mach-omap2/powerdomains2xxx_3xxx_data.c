<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2/3 common घातerकरोमुख्य definitions
 *
 * Copyright (C) 2007-2008, 2011 Texas Instruments, Inc.
 * Copyright (C) 2007-2011 Nokia Corporation
 *
 * Paul Walmsley, Jouni Hथघgander
 */

/*
 * The names क्रम the DSP/IVA2 घातerकरोमुख्यs are confusing.
 *
 * Most OMAP chips have an on-board DSP.
 *
 * On the 2420, this is a 'C55 DSP called, simply, the DSP.  Its
 * घातerकरोमुख्य is called the "DSP power domain."  On the 2430, the
 * on-board DSP is a 'C64 DSP, now called (aदीर्घ with its hardware
 * accelerators) the IVA2 or IVA2.1.  Its घातerकरोमुख्य is still called
 * the "DSP power domain." On the 3430, the DSP is a 'C64 DSP like the
 * 2430, also known as the IVA2; but its घातerकरोमुख्य is now called the
 * "IVA2 power domain."
 *
 * The 2420 also has something called the IVA, which is a separate ARM
 * core, and has nothing to करो with the DSP/IVA2.
 *
 * Ideally the DSP/IVA2 could just be the same घातerकरोमुख्य, but the PRCM
 * address offset is dअगरferent between the C55 and C64 DSPs.
 */

#समावेश "powerdomain.h"

#समावेश "prcm-common.h"
#समावेश "prm.h"

/* OMAP2/3-common घातerकरोमुख्यs */

/*
 * The GFX घातerकरोमुख्य is not present on 3430ES2, but currently we करो not
 * have a macro to filter it out at compile-समय.
 */
काष्ठा घातerकरोमुख्य gfx_omap2_pwrdm = अणु
	.name		  = "gfx_pwrdm",
	.prcm_offs	  = GFX_MOD,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_RET,
	.banks		  = 1,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_RET, /* MEMRETSTATE */
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_ON,  /* MEMONSTATE */
	पूर्ण,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

काष्ठा घातerकरोमुख्य wkup_omap2_pwrdm = अणु
	.name		= "wkup_pwrdm",
	.prcm_offs	= WKUP_MOD,
	.pwrsts		= PWRSTS_ON,
	.voltdm		= अणु .name = "wakeup" पूर्ण,
पूर्ण;
