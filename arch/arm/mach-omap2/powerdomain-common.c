<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common घातerकरोमुख्य framework functions
 *
 * Copyright (C) 2010-2011 Texas Instruments, Inc.
 * Copyright (C) 2010 Nokia Corporation
 *
 * Derived from mach-omap2/घातerकरोमुख्य.c written by Paul Walmsley
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>
#समावेश "pm.h"
#समावेश "cm.h"
#समावेश "cm-regbits-34xx.h"
#समावेश "prm-regbits-34xx.h"
#समावेश "prm-regbits-44xx.h"

/*
 * OMAP3 and OMAP4 specअगरic रेजिस्टर bit initialisations
 * Notice that the names here are not according to each घातer
 * करोमुख्य but the bit mapping used applies to all of them
 */
/* OMAP3 and OMAP4 Memory Onstate Masks (common across all घातer करोमुख्यs) */
#घोषणा OMAP_MEM0_ONSTATE_MASK OMAP3430_SHAREDL1CACHEFLATONSTATE_MASK
#घोषणा OMAP_MEM1_ONSTATE_MASK OMAP3430_L1FLATMEMONSTATE_MASK
#घोषणा OMAP_MEM2_ONSTATE_MASK OMAP3430_SHAREDL2CACHEFLATONSTATE_MASK
#घोषणा OMAP_MEM3_ONSTATE_MASK OMAP3430_L2FLATMEMONSTATE_MASK
#घोषणा OMAP_MEM4_ONSTATE_MASK OMAP4430_OCP_NRET_BANK_ONSTATE_MASK

/* OMAP3 and OMAP4 Memory Retstate Masks (common across all घातer करोमुख्यs) */
#घोषणा OMAP_MEM0_RETSTATE_MASK OMAP3430_SHAREDL1CACHEFLATRETSTATE_MASK
#घोषणा OMAP_MEM1_RETSTATE_MASK OMAP3430_L1FLATMEMRETSTATE_MASK
#घोषणा OMAP_MEM2_RETSTATE_MASK OMAP3430_SHAREDL2CACHEFLATRETSTATE_MASK
#घोषणा OMAP_MEM3_RETSTATE_MASK OMAP3430_L2FLATMEMRETSTATE_MASK
#घोषणा OMAP_MEM4_RETSTATE_MASK OMAP4430_OCP_NRET_BANK_RETSTATE_MASK

/* OMAP3 and OMAP4 Memory Status bits */
#घोषणा OMAP_MEM0_STATEST_MASK OMAP3430_SHAREDL1CACHEFLATSTATEST_MASK
#घोषणा OMAP_MEM1_STATEST_MASK OMAP3430_L1FLATMEMSTATEST_MASK
#घोषणा OMAP_MEM2_STATEST_MASK OMAP3430_SHAREDL2CACHEFLATSTATEST_MASK
#घोषणा OMAP_MEM3_STATEST_MASK OMAP3430_L2FLATMEMSTATEST_MASK
#घोषणा OMAP_MEM4_STATEST_MASK OMAP4430_OCP_NRET_BANK_STATEST_MASK

/* Common Internal functions used across OMAP rev's*/
u32 omap2_pwrdm_get_mem_bank_onstate_mask(u8 bank)
अणु
	चयन (bank) अणु
	हाल 0:
		वापस OMAP_MEM0_ONSTATE_MASK;
	हाल 1:
		वापस OMAP_MEM1_ONSTATE_MASK;
	हाल 2:
		वापस OMAP_MEM2_ONSTATE_MASK;
	हाल 3:
		वापस OMAP_MEM3_ONSTATE_MASK;
	हाल 4:
		वापस OMAP_MEM4_ONSTATE_MASK;
	शेष:
		WARN_ON(1); /* should never happen */
		वापस -EEXIST;
	पूर्ण
	वापस 0;
पूर्ण

u32 omap2_pwrdm_get_mem_bank_retst_mask(u8 bank)
अणु
	चयन (bank) अणु
	हाल 0:
		वापस OMAP_MEM0_RETSTATE_MASK;
	हाल 1:
		वापस OMAP_MEM1_RETSTATE_MASK;
	हाल 2:
		वापस OMAP_MEM2_RETSTATE_MASK;
	हाल 3:
		वापस OMAP_MEM3_RETSTATE_MASK;
	हाल 4:
		वापस OMAP_MEM4_RETSTATE_MASK;
	शेष:
		WARN_ON(1); /* should never happen */
		वापस -EEXIST;
	पूर्ण
	वापस 0;
पूर्ण

u32 omap2_pwrdm_get_mem_bank_stst_mask(u8 bank)
अणु
	चयन (bank) अणु
	हाल 0:
		वापस OMAP_MEM0_STATEST_MASK;
	हाल 1:
		वापस OMAP_MEM1_STATEST_MASK;
	हाल 2:
		वापस OMAP_MEM2_STATEST_MASK;
	हाल 3:
		वापस OMAP_MEM3_STATEST_MASK;
	हाल 4:
		वापस OMAP_MEM4_STATEST_MASK;
	शेष:
		WARN_ON(1); /* should never happen */
		वापस -EEXIST;
	पूर्ण
	वापस 0;
पूर्ण

