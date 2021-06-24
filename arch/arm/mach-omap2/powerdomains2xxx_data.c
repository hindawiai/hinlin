<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP2XXX घातerकरोमुख्य definitions
 *
 * Copyright (C) 2007-2008, 2011 Texas Instruments, Inc.
 * Copyright (C) 2007-2011 Nokia Corporation
 *
 * Paul Walmsley, Jouni Hथघgander
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश "soc.h"
#समावेश "powerdomain.h"
#समावेश "powerdomains2xxx_3xxx_data.h"

#समावेश "prcm-common.h"
#समावेश "prm2xxx_3xxx.h"
#समावेश "prm-regbits-24xx.h"

/* 24XX घातerकरोमुख्यs and dependencies */

/* Powerकरोमुख्यs */

अटल काष्ठा घातerकरोमुख्य dsp_pwrdm = अणु
	.name		  = "dsp_pwrdm",
	.prcm_offs	  = OMAP24XX_DSP_MOD,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_RET,
	.banks		  = 1,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_RET,
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_ON,
	पूर्ण,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य mpu_24xx_pwrdm = अणु
	.name		  = "mpu_pwrdm",
	.prcm_offs	  = MPU_MOD,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 1,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_RET,
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_ON,
	पूर्ण,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य core_24xx_pwrdm = अणु
	.name		  = "core_pwrdm",
	.prcm_offs	  = CORE_MOD,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_RET,
	.banks		  = 3,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_OFF_RET,	 /* MEM1RETSTATE */
		[1] = PWRSTS_OFF_RET,	 /* MEM2RETSTATE */
		[2] = PWRSTS_OFF_RET,	 /* MEM3RETSTATE */
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_OFF_RET_ON, /* MEM1ONSTATE */
		[1] = PWRSTS_OFF_RET_ON, /* MEM2ONSTATE */
		[2] = PWRSTS_OFF_RET_ON, /* MEM3ONSTATE */
	पूर्ण,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;


/*
 * 2430-specअगरic घातerकरोमुख्यs
 */

/* XXX 2430 KILLDOMAINWKUP bit?  No current users apparently */

अटल काष्ठा घातerकरोमुख्य mdm_pwrdm = अणु
	.name		  = "mdm_pwrdm",
	.prcm_offs	  = OMAP2430_MDM_MOD,
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

/*
 *
 */

अटल काष्ठा घातerकरोमुख्य *घातerकरोमुख्यs_omap24xx[] __initdata = अणु
	&wkup_omap2_pwrdm,
	&gfx_omap2_pwrdm,
	&dsp_pwrdm,
	&mpu_24xx_pwrdm,
	&core_24xx_pwrdm,
	शून्य
पूर्ण;

अटल काष्ठा घातerकरोमुख्य *घातerकरोमुख्यs_omap2430[] __initdata = अणु
	&mdm_pwrdm,
	शून्य
पूर्ण;

व्योम __init omap242x_घातerकरोमुख्यs_init(व्योम)
अणु
	अगर (!cpu_is_omap2420())
		वापस;

	pwrdm_रेजिस्टर_platक्रमm_funcs(&omap2_pwrdm_operations);
	pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_omap24xx);
	pwrdm_complete_init();
पूर्ण

व्योम __init omap243x_घातerकरोमुख्यs_init(व्योम)
अणु
	अगर (!cpu_is_omap2430())
		वापस;

	pwrdm_रेजिस्टर_platक्रमm_funcs(&omap2_pwrdm_operations);
	pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_omap24xx);
	pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_omap2430);
	pwrdm_complete_init();
पूर्ण
