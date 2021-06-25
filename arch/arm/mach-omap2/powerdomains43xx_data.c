<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AM43xx Power करोमुख्यs framework
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश "powerdomain.h"

#समावेश "prcm-common.h"
#समावेश "prcm44xx.h"
#समावेश "prcm43xx.h"

अटल काष्ठा घातerकरोमुख्य gfx_43xx_pwrdm = अणु
	.name		  = "gfx_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = AM43XX_PRM_GFX_INST,
	.prcm_partition	  = AM43XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_ON,
	.banks		  = 1,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* gfx_mem */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य mpu_43xx_pwrdm = अणु
	.name		  = "mpu_pwrdm",
	.voltdm		  = अणु .name = "mpu" पूर्ण,
	.prcm_offs	  = AM43XX_PRM_MPU_INST,
	.prcm_partition	  = AM43XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 3,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* mpu_l1 */
		[1] = PWRSTS_OFF_RET,	/* mpu_l2 */
		[2] = PWRSTS_OFF_RET,	/* mpu_ram */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* mpu_l1 */
		[1] = PWRSTS_ON,	/* mpu_l2 */
		[2] = PWRSTS_ON,	/* mpu_ram */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य rtc_43xx_pwrdm = अणु
	.name		  = "rtc_pwrdm",
	.voltdm		  = अणु .name = "rtc" पूर्ण,
	.prcm_offs	  = AM43XX_PRM_RTC_INST,
	.prcm_partition	  = AM43XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_ON,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य wkup_43xx_pwrdm = अणु
	.name		  = "wkup_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = AM43XX_PRM_WKUP_INST,
	.prcm_partition	  = AM43XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_ON,
	.banks		  = 1,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* debugss_mem */
	पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य tamper_43xx_pwrdm = अणु
	.name		  = "tamper_pwrdm",
	.voltdm		  = अणु .name = "tamper" पूर्ण,
	.prcm_offs	  = AM43XX_PRM_TAMPER_INST,
	.prcm_partition	  = AM43XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_ON,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य cefuse_43xx_pwrdm = अणु
	.name		  = "cefuse_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = AM43XX_PRM_CEFUSE_INST,
	.prcm_partition	  = AM43XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_ON,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य per_43xx_pwrdm = अणु
	.name		  = "per_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = AM43XX_PRM_PER_INST,
	.prcm_partition	  = AM43XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 4,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* icss_mem */
		[1] = PWRSTS_OFF_RET,	/* per_mem */
		[2] = PWRSTS_OFF_RET,	/* ram1_mem */
		[3] = PWRSTS_OFF_RET,	/* ram2_mem */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* icss_mem */
		[1] = PWRSTS_ON,	/* per_mem */
		[2] = PWRSTS_ON,	/* ram1_mem */
		[3] = PWRSTS_ON,	/* ram2_mem */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य *घातerकरोमुख्यs_am43xx[] __initdata = अणु
	&gfx_43xx_pwrdm,
	&mpu_43xx_pwrdm,
	&rtc_43xx_pwrdm,
	&wkup_43xx_pwrdm,
	&tamper_43xx_pwrdm,
	&cefuse_43xx_pwrdm,
	&per_43xx_pwrdm,
	शून्य
पूर्ण;

अटल पूर्णांक am43xx_check_vcvp(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम __init am43xx_घातerकरोमुख्यs_init(व्योम)
अणु
	omap4_pwrdm_operations.pwrdm_has_voltdm = am43xx_check_vcvp;
	pwrdm_रेजिस्टर_platक्रमm_funcs(&omap4_pwrdm_operations);
	pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_am43xx);
	pwrdm_complete_init();
पूर्ण
