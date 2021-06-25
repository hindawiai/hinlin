<शैली गुरु>
/*
 * AM33XX Power करोमुख्य data
 *
 * Copyright (C) 2011-2012 Texas Instruments Incorporated - https://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश "powerdomain.h"
#समावेश "prcm-common.h"
#समावेश "prm-regbits-33xx.h"
#समावेश "prm33xx.h"

अटल काष्ठा घातerकरोमुख्य gfx_33xx_pwrdm = अणु
	.name			= "gfx_pwrdm",
	.voltdm			= अणु .name = "core" पूर्ण,
	.prcm_offs		= AM33XX_PRM_GFX_MOD,
	.pwrstctrl_offs		= AM33XX_PM_GFX_PWRSTCTRL_OFFSET,
	.pwrstst_offs		= AM33XX_PM_GFX_PWRSTST_OFFSET,
	.pwrsts			= PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret	= PWRSTS_OFF_RET,
	.flags			= PWRDM_HAS_LOWPOWERSTATECHANGE,
	.banks			= 1,
	.logicretstate_mask	= AM33XX_LOGICRETSTATE_MASK,
	.mem_on_mask		= अणु
		[0]		= AM33XX_GFX_MEM_ONSTATE_MASK,	/* gfx_mem */
	पूर्ण,
	.mem_ret_mask		= अणु
		[0]		= AM33XX_GFX_MEM_RETSTATE_MASK,	/* gfx_mem */
	पूर्ण,
	.mem_pwrst_mask		= अणु
		[0]		= AM33XX_GFX_MEM_STATEST_MASK,	/* gfx_mem */
	पूर्ण,
	.mem_retst_mask		= अणु
		[0]		= AM33XX_GFX_MEM_RETSTATE_MASK,	/* gfx_mem */
	पूर्ण,
	.pwrsts_mem_ret		= अणु
		[0]		= PWRSTS_OFF_RET,	/* gfx_mem */
	पूर्ण,
	.pwrsts_mem_on		= अणु
		[0]		= PWRSTS_ON,		/* gfx_mem */
	पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य rtc_33xx_pwrdm = अणु
	.name			= "rtc_pwrdm",
	.voltdm			= अणु .name = "rtc" पूर्ण,
	.prcm_offs		= AM33XX_PRM_RTC_MOD,
	.pwrstctrl_offs		= AM33XX_PM_RTC_PWRSTCTRL_OFFSET,
	.pwrstst_offs		= AM33XX_PM_RTC_PWRSTST_OFFSET,
	.pwrsts			= PWRSTS_ON,
	.logicretstate_mask	= AM33XX_LOGICRETSTATE_MASK,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य wkup_33xx_pwrdm = अणु
	.name			= "wkup_pwrdm",
	.voltdm			= अणु .name = "core" पूर्ण,
	.prcm_offs		= AM33XX_PRM_WKUP_MOD,
	.pwrstctrl_offs		= AM33XX_PM_WKUP_PWRSTCTRL_OFFSET,
	.pwrstst_offs		= AM33XX_PM_WKUP_PWRSTST_OFFSET,
	.pwrsts			= PWRSTS_ON,
	.logicretstate_mask	= AM33XX_LOGICRETSTATE_3_3_MASK,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य per_33xx_pwrdm = अणु
	.name			= "per_pwrdm",
	.voltdm			= अणु .name = "core" पूर्ण,
	.prcm_offs		= AM33XX_PRM_PER_MOD,
	.pwrstctrl_offs		= AM33XX_PM_PER_PWRSTCTRL_OFFSET,
	.pwrstst_offs		= AM33XX_PM_PER_PWRSTST_OFFSET,
	.pwrsts			= PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret	= PWRSTS_OFF_RET,
	.flags			= PWRDM_HAS_LOWPOWERSTATECHANGE,
	.banks			= 3,
	.logicretstate_mask	= AM33XX_LOGICRETSTATE_3_3_MASK,
	.mem_on_mask		= अणु
		[0]		= AM33XX_PRUSS_MEM_ONSTATE_MASK, /* pruss_mem */
		[1]		= AM33XX_PER_MEM_ONSTATE_MASK,	/* per_mem */
		[2]		= AM33XX_RAM_MEM_ONSTATE_MASK,	/* ram_mem */
	पूर्ण,
	.mem_ret_mask		= अणु
		[0]		= AM33XX_PRUSS_MEM_RETSTATE_MASK, /* pruss_mem */
		[1]		= AM33XX_PER_MEM_RETSTATE_MASK,	/* per_mem */
		[2]		= AM33XX_RAM_MEM_RETSTATE_MASK,	/* ram_mem */
	पूर्ण,
	.mem_pwrst_mask		= अणु
		[0]		= AM33XX_PRUSS_MEM_STATEST_MASK, /* pruss_mem */
		[1]		= AM33XX_PER_MEM_STATEST_MASK,	/* per_mem */
		[2]		= AM33XX_RAM_MEM_STATEST_MASK,	/* ram_mem */
	पूर्ण,
	.mem_retst_mask		= अणु
		[0]		= AM33XX_PRUSS_MEM_RETSTATE_MASK, /* pruss_mem */
		[1]		= AM33XX_PER_MEM_RETSTATE_MASK,	/* per_mem */
		[2]		= AM33XX_RAM_MEM_RETSTATE_MASK,	/* ram_mem */
	पूर्ण,
	.pwrsts_mem_ret		= अणु
		[0]		= PWRSTS_OFF_RET,	/* pruss_mem */
		[1]		= PWRSTS_OFF_RET,	/* per_mem */
		[2]		= PWRSTS_OFF_RET,	/* ram_mem */
	पूर्ण,
	.pwrsts_mem_on		= अणु
		[0]		= PWRSTS_ON,		/* pruss_mem */
		[1]		= PWRSTS_ON,		/* per_mem */
		[2]		= PWRSTS_ON,		/* ram_mem */
	पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य mpu_33xx_pwrdm = अणु
	.name			= "mpu_pwrdm",
	.voltdm			= अणु .name = "mpu" पूर्ण,
	.prcm_offs		= AM33XX_PRM_MPU_MOD,
	.pwrstctrl_offs		= AM33XX_PM_MPU_PWRSTCTRL_OFFSET,
	.pwrstst_offs		= AM33XX_PM_MPU_PWRSTST_OFFSET,
	.pwrsts			= PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret	= PWRSTS_OFF_RET,
	.flags			= PWRDM_HAS_LOWPOWERSTATECHANGE,
	.banks			= 3,
	.logicretstate_mask	= AM33XX_LOGICRETSTATE_MASK,
	.mem_on_mask		= अणु
		[0]		= AM33XX_MPU_L1_ONSTATE_MASK,	/* mpu_l1 */
		[1]		= AM33XX_MPU_L2_ONSTATE_MASK,	/* mpu_l2 */
		[2]		= AM33XX_MPU_RAM_ONSTATE_MASK,	/* mpu_ram */
	पूर्ण,
	.mem_ret_mask		= अणु
		[0]		= AM33XX_MPU_L1_RETSTATE_MASK,	/* mpu_l1 */
		[1]		= AM33XX_MPU_L2_RETSTATE_MASK,	/* mpu_l2 */
		[2]		= AM33XX_MPU_RAM_RETSTATE_MASK,	/* mpu_ram */
	पूर्ण,
	.mem_pwrst_mask		= अणु
		[0]		= AM33XX_MPU_L1_STATEST_MASK,	/* mpu_l1 */
		[1]		= AM33XX_MPU_L2_STATEST_MASK,	/* mpu_l2 */
		[2]		= AM33XX_MPU_RAM_STATEST_MASK,	/* mpu_ram */
	पूर्ण,
	.mem_retst_mask		= अणु
		[0]		= AM33XX_MPU_L1_RETSTATE_MASK,	/* mpu_l1 */
		[1]		= AM33XX_MPU_L2_RETSTATE_MASK,	/* mpu_l2 */
		[2]		= AM33XX_MPU_RAM_RETSTATE_MASK,	/* mpu_ram */
	पूर्ण,
	.pwrsts_mem_ret		= अणु
		[0]		= PWRSTS_OFF_RET,	/* mpu_l1 */
		[1]		= PWRSTS_OFF_RET,	/* mpu_l2 */
		[2]		= PWRSTS_OFF_RET,	/* mpu_ram */
	पूर्ण,
	.pwrsts_mem_on		= अणु
		[0]		= PWRSTS_ON,		/* mpu_l1 */
		[1]		= PWRSTS_ON,		/* mpu_l2 */
		[2]		= PWRSTS_ON,		/* mpu_ram */
	पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य cefuse_33xx_pwrdm = अणु
	.name		= "cefuse_pwrdm",
	.voltdm		= अणु .name = "core" पूर्ण,
	.prcm_offs	= AM33XX_PRM_CEFUSE_MOD,
	.pwrstctrl_offs	= AM33XX_PM_CEFUSE_PWRSTCTRL_OFFSET,
	.pwrstst_offs	= AM33XX_PM_CEFUSE_PWRSTST_OFFSET,
	.pwrsts		= PWRSTS_OFF_ON,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य *घातerकरोमुख्यs_am33xx[] __initdata = अणु
	&gfx_33xx_pwrdm,
	&rtc_33xx_pwrdm,
	&wkup_33xx_pwrdm,
	&per_33xx_pwrdm,
	&mpu_33xx_pwrdm,
	&cefuse_33xx_pwrdm,
	शून्य,
पूर्ण;

व्योम __init am33xx_घातerकरोमुख्यs_init(व्योम)
अणु
	pwrdm_रेजिस्टर_platक्रमm_funcs(&am33xx_pwrdm_operations);
	pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_am33xx);
	pwrdm_complete_init();
पूर्ण
