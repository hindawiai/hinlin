<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP3 घातerकरोमुख्य definitions
 *
 * Copyright (C) 2007-2008, 2011 Texas Instruments, Inc.
 * Copyright (C) 2007-2011 Nokia Corporation
 *
 * Paul Walmsley, Jouni Hथघgander
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/bug.h>

#समावेश "soc.h"
#समावेश "powerdomain.h"
#समावेश "powerdomains2xxx_3xxx_data.h"
#समावेश "prcm-common.h"
#समावेश "prm2xxx_3xxx.h"
#समावेश "prm-regbits-34xx.h"
#समावेश "cm2xxx_3xxx.h"
#समावेश "cm-regbits-34xx.h"

/*
 * 34XX-specअगरic घातerकरोमुख्यs, dependencies
 */

/*
 * Powerकरोमुख्यs
 */

अटल काष्ठा घातerकरोमुख्य iva2_pwrdm = अणु
	.name		  = "iva2_pwrdm",
	.prcm_offs	  = OMAP3430_IVA2_MOD,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 4,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_OFF_RET,
		[1] = PWRSTS_OFF_RET,
		[2] = PWRSTS_OFF_RET,
		[3] = PWRSTS_OFF_RET,
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_ON,
		[1] = PWRSTS_ON,
		[2] = PWRSTS_OFF_ON,
		[3] = PWRSTS_ON,
	पूर्ण,
	.voltdm		  = अणु .name = "mpu_iva" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य mpu_3xxx_pwrdm = अणु
	.name		  = "mpu_pwrdm",
	.prcm_offs	  = MPU_MOD,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.flags		  = PWRDM_HAS_MPU_QUIRK,
	.banks		  = 1,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_OFF_RET,
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_OFF_ON,
	पूर्ण,
	.voltdm		  = अणु .name = "mpu_iva" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य mpu_am35x_pwrdm = अणु
	.name		  = "mpu_pwrdm",
	.prcm_offs	  = MPU_MOD,
	.pwrsts		  = PWRSTS_ON,
	.pwrsts_logic_ret = PWRSTS_ON,
	.flags		  = PWRDM_HAS_MPU_QUIRK,
	.banks		  = 1,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_ON,
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_ON,
	पूर्ण,
	.voltdm		  = अणु .name = "mpu_iva" पूर्ण,
पूर्ण;

/*
 * The USBTLL Save-and-Restore mechanism is broken on
 * 3430s up to ES3.0 and 3630ES1.0. Hence this feature
 * needs to be disabled on these chips.
 * Refer: 3430 errata ID i459 and 3630 errata ID i579
 *
 * Note: setting the SAR flag could help क्रम errata ID i478
 *  which applies to 3430 <= ES3.1, but since the SAR feature
 *  is broken, करो not use it.
 */
अटल काष्ठा घातerकरोमुख्य core_3xxx_pre_es3_1_pwrdm = अणु
	.name		  = "core_pwrdm",
	.prcm_offs	  = CORE_MOD,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 2,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_OFF_RET,	 /* MEM1RETSTATE */
		[1] = PWRSTS_OFF_RET,	 /* MEM2RETSTATE */
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_OFF_RET_ON, /* MEM1ONSTATE */
		[1] = PWRSTS_OFF_RET_ON, /* MEM2ONSTATE */
	पूर्ण,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य core_3xxx_es3_1_pwrdm = अणु
	.name		  = "core_pwrdm",
	.prcm_offs	  = CORE_MOD,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	/*
	 * Setting the SAR flag क्रम errata ID i478 which applies
	 *  to 3430 <= ES3.1
	 */
	.flags		  = PWRDM_HAS_HDWR_SAR, /* क्रम USBTLL only */
	.banks		  = 2,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_OFF_RET,	 /* MEM1RETSTATE */
		[1] = PWRSTS_OFF_RET,	 /* MEM2RETSTATE */
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_OFF_RET_ON, /* MEM1ONSTATE */
		[1] = PWRSTS_OFF_RET_ON, /* MEM2ONSTATE */
	पूर्ण,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य core_am35x_pwrdm = अणु
	.name		  = "core_pwrdm",
	.prcm_offs	  = CORE_MOD,
	.pwrsts		  = PWRSTS_ON,
	.pwrsts_logic_ret = PWRSTS_ON,
	.banks		  = 2,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_ON,	 /* MEM1RETSTATE */
		[1] = PWRSTS_ON,	 /* MEM2RETSTATE */
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_ON, /* MEM1ONSTATE */
		[1] = PWRSTS_ON, /* MEM2ONSTATE */
	पूर्ण,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य dss_pwrdm = अणु
	.name		  = "dss_pwrdm",
	.prcm_offs	  = OMAP3430_DSS_MOD,
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

अटल काष्ठा घातerकरोमुख्य dss_am35x_pwrdm = अणु
	.name		  = "dss_pwrdm",
	.prcm_offs	  = OMAP3430_DSS_MOD,
	.pwrsts		  = PWRSTS_ON,
	.pwrsts_logic_ret = PWRSTS_ON,
	.banks		  = 1,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_ON, /* MEMRETSTATE */
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_ON,  /* MEMONSTATE */
	पूर्ण,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

/*
 * Although the 34XX TRM Rev K Table 4-371 notes that retention is a
 * possible SGX घातerstate, the SGX device itself करोes not support
 * retention.
 */
अटल काष्ठा घातerकरोमुख्य sgx_pwrdm = अणु
	.name		  = "sgx_pwrdm",
	.prcm_offs	  = OMAP3430ES2_SGX_MOD,
	/* XXX This is accurate क्रम 3430 SGX, but what about GFX? */
	.pwrsts		  = PWRSTS_OFF_ON,
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

अटल काष्ठा घातerकरोमुख्य sgx_am35x_pwrdm = अणु
	.name		  = "sgx_pwrdm",
	.prcm_offs	  = OMAP3430ES2_SGX_MOD,
	.pwrsts		  = PWRSTS_ON,
	.pwrsts_logic_ret = PWRSTS_ON,
	.banks		  = 1,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_ON, /* MEMRETSTATE */
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_ON,  /* MEMONSTATE */
	पूर्ण,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य cam_pwrdm = अणु
	.name		  = "cam_pwrdm",
	.prcm_offs	  = OMAP3430_CAM_MOD,
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

अटल काष्ठा घातerकरोमुख्य per_pwrdm = अणु
	.name		  = "per_pwrdm",
	.prcm_offs	  = OMAP3430_PER_MOD,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 1,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_RET, /* MEMRETSTATE */
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_ON,  /* MEMONSTATE */
	पूर्ण,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य per_am35x_pwrdm = अणु
	.name		  = "per_pwrdm",
	.prcm_offs	  = OMAP3430_PER_MOD,
	.pwrsts		  = PWRSTS_ON,
	.pwrsts_logic_ret = PWRSTS_ON,
	.banks		  = 1,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_ON, /* MEMRETSTATE */
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_ON,  /* MEMONSTATE */
	पूर्ण,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य emu_pwrdm = अणु
	.name		= "emu_pwrdm",
	.prcm_offs	= OMAP3430_EMU_MOD,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य neon_pwrdm = अणु
	.name		  = "neon_pwrdm",
	.prcm_offs	  = OMAP3430_NEON_MOD,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_RET,
	.voltdm		  = अणु .name = "mpu_iva" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य neon_am35x_pwrdm = अणु
	.name		  = "neon_pwrdm",
	.prcm_offs	  = OMAP3430_NEON_MOD,
	.pwrsts		  = PWRSTS_ON,
	.pwrsts_logic_ret = PWRSTS_ON,
	.voltdm		  = अणु .name = "mpu_iva" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य usbhost_pwrdm = अणु
	.name		  = "usbhost_pwrdm",
	.prcm_offs	  = OMAP3430ES2_USBHOST_MOD,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_RET,
	/*
	 * REVISIT: Enabling usb host save and restore mechanism seems to
	 * leave the usb host करोमुख्य permanently in ACTIVE mode after
	 * changing the usb host घातer करोमुख्य state from OFF to active once.
	 * Disabling क्रम now.
	 */
	/*.flags	  = PWRDM_HAS_HDWR_SAR,*/ /* क्रम USBHOST ctrlr only */
	.banks		  = 1,
	.pwrsts_mem_ret	  = अणु
		[0] = PWRSTS_RET, /* MEMRETSTATE */
	पूर्ण,
	.pwrsts_mem_on	  = अणु
		[0] = PWRSTS_ON,  /* MEMONSTATE */
	पूर्ण,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य dpll1_pwrdm = अणु
	.name		= "dpll1_pwrdm",
	.prcm_offs	= MPU_MOD,
	.voltdm		  = अणु .name = "mpu_iva" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य dpll2_pwrdm = अणु
	.name		= "dpll2_pwrdm",
	.prcm_offs	= OMAP3430_IVA2_MOD,
	.voltdm		  = अणु .name = "mpu_iva" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य dpll3_pwrdm = अणु
	.name		= "dpll3_pwrdm",
	.prcm_offs	= PLL_MOD,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य dpll4_pwrdm = अणु
	.name		= "dpll4_pwrdm",
	.prcm_offs	= PLL_MOD,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य dpll5_pwrdm = अणु
	.name		= "dpll5_pwrdm",
	.prcm_offs	= PLL_MOD,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य alwon_81xx_pwrdm = अणु
	.name		  = "alwon_pwrdm",
	.prcm_offs	  = TI81XX_PRM_ALWON_MOD,
	.pwrsts		  = PWRSTS_OFF_ON,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य device_81xx_pwrdm = अणु
	.name		  = "device_pwrdm",
	.prcm_offs	  = TI81XX_PRM_DEVICE_MOD,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य gem_814x_pwrdm = अणु
	.name		= "gem_pwrdm",
	.prcm_offs	= TI814X_PRM_DSP_MOD,
	.pwrsts		= PWRSTS_OFF_ON,
	.voltdm		= अणु .name = "dsp" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य ivahd_814x_pwrdm = अणु
	.name		= "ivahd_pwrdm",
	.prcm_offs	= TI814X_PRM_HDVICP_MOD,
	.pwrsts		= PWRSTS_OFF_ON,
	.voltdm		= अणु .name = "iva" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य hdvpss_814x_pwrdm = अणु
	.name		= "hdvpss_pwrdm",
	.prcm_offs	= TI814X_PRM_HDVPSS_MOD,
	.pwrsts		= PWRSTS_OFF_ON,
	.voltdm		= अणु .name = "dsp" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य sgx_814x_pwrdm = अणु
	.name		= "sgx_pwrdm",
	.prcm_offs	= TI814X_PRM_GFX_MOD,
	.pwrsts		= PWRSTS_OFF_ON,
	.voltdm		= अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य isp_814x_pwrdm = अणु
	.name		= "isp_pwrdm",
	.prcm_offs	= TI814X_PRM_ISP_MOD,
	.pwrsts		= PWRSTS_OFF_ON,
	.voltdm		= अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य active_81xx_pwrdm = अणु
	.name		  = "active_pwrdm",
	.prcm_offs	  = TI816X_PRM_ACTIVE_MOD,
	.pwrsts		  = PWRSTS_OFF_ON,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य शेष_81xx_pwrdm = अणु
	.name		  = "default_pwrdm",
	.prcm_offs	  = TI81XX_PRM_DEFAULT_MOD,
	.pwrsts		  = PWRSTS_OFF_ON,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य ivahd0_816x_pwrdm = अणु
	.name		  = "ivahd0_pwrdm",
	.prcm_offs	  = TI816X_PRM_IVAHD0_MOD,
	.pwrsts		  = PWRSTS_OFF_ON,
	.voltdm		  = अणु .name = "mpu_iva" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य ivahd1_816x_pwrdm = अणु
	.name		  = "ivahd1_pwrdm",
	.prcm_offs	  = TI816X_PRM_IVAHD1_MOD,
	.pwrsts		  = PWRSTS_OFF_ON,
	.voltdm		  = अणु .name = "mpu_iva" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य ivahd2_816x_pwrdm = अणु
	.name		  = "ivahd2_pwrdm",
	.prcm_offs	  = TI816X_PRM_IVAHD2_MOD,
	.pwrsts		  = PWRSTS_OFF_ON,
	.voltdm		  = अणु .name = "mpu_iva" पूर्ण,
पूर्ण;

अटल काष्ठा घातerकरोमुख्य sgx_816x_pwrdm = अणु
	.name		  = "sgx_pwrdm",
	.prcm_offs	  = TI816X_PRM_SGX_MOD,
	.pwrsts		  = PWRSTS_OFF_ON,
	.voltdm		  = अणु .name = "core" पूर्ण,
पूर्ण;

/* As घातerकरोमुख्यs are added or हटाओd above, this list must also be changed */
अटल काष्ठा घातerकरोमुख्य *घातerकरोमुख्यs_omap3430_common[] __initdata = अणु
	&wkup_omap2_pwrdm,
	&iva2_pwrdm,
	&mpu_3xxx_pwrdm,
	&neon_pwrdm,
	&cam_pwrdm,
	&dss_pwrdm,
	&per_pwrdm,
	&emu_pwrdm,
	&dpll1_pwrdm,
	&dpll2_pwrdm,
	&dpll3_pwrdm,
	&dpll4_pwrdm,
	शून्य
पूर्ण;

अटल काष्ठा घातerकरोमुख्य *घातerकरोमुख्यs_omap3430es1[] __initdata = अणु
	&gfx_omap2_pwrdm,
	&core_3xxx_pre_es3_1_pwrdm,
	शून्य
पूर्ण;

/* also includes 3630ES1.0 */
अटल काष्ठा घातerकरोमुख्य *घातerकरोमुख्यs_omap3430es2_es3_0[] __initdata = अणु
	&core_3xxx_pre_es3_1_pwrdm,
	&sgx_pwrdm,
	&usbhost_pwrdm,
	&dpll5_pwrdm,
	शून्य
पूर्ण;

/* also includes 3630ES1.1+ */
अटल काष्ठा घातerकरोमुख्य *घातerकरोमुख्यs_omap3430es3_1plus[] __initdata = अणु
	&core_3xxx_es3_1_pwrdm,
	&sgx_pwrdm,
	&usbhost_pwrdm,
	&dpll5_pwrdm,
	शून्य
पूर्ण;

अटल काष्ठा घातerकरोमुख्य *घातerकरोमुख्यs_am35x[] __initdata = अणु
	&wkup_omap2_pwrdm,
	&mpu_am35x_pwrdm,
	&neon_am35x_pwrdm,
	&core_am35x_pwrdm,
	&sgx_am35x_pwrdm,
	&dss_am35x_pwrdm,
	&per_am35x_pwrdm,
	&emu_pwrdm,
	&dpll1_pwrdm,
	&dpll3_pwrdm,
	&dpll4_pwrdm,
	&dpll5_pwrdm,
	शून्य
पूर्ण;

अटल काष्ठा घातerकरोमुख्य *घातerकरोमुख्यs_ti814x[] __initdata = अणु
	&alwon_81xx_pwrdm,
	&device_81xx_pwrdm,
	&active_81xx_pwrdm,
	&शेष_81xx_pwrdm,
	&gem_814x_pwrdm,
	&ivahd_814x_pwrdm,
	&hdvpss_814x_pwrdm,
	&sgx_814x_pwrdm,
	&isp_814x_pwrdm,
	शून्य
पूर्ण;

अटल काष्ठा घातerकरोमुख्य *घातerकरोमुख्यs_ti816x[] __initdata = अणु
	&alwon_81xx_pwrdm,
	&device_81xx_pwrdm,
	&active_81xx_pwrdm,
	&शेष_81xx_pwrdm,
	&ivahd0_816x_pwrdm,
	&ivahd1_816x_pwrdm,
	&ivahd2_816x_pwrdm,
	&sgx_816x_pwrdm,
	शून्य
पूर्ण;

/* TI81XX specअगरic ops */
#घोषणा TI81XX_PM_PWSTCTRL				0x0000
#घोषणा TI81XX_RM_RSTCTRL				0x0010
#घोषणा TI81XX_PM_PWSTST				0x0004

अटल पूर्णांक ti81xx_pwrdm_set_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm, u8 pwrst)
अणु
	omap2_prm_rmw_mod_reg_bits(OMAP_POWERSTATE_MASK,
				   (pwrst << OMAP_POWERSTATE_SHIFT),
				   pwrdm->prcm_offs, TI81XX_PM_PWSTCTRL);
	वापस 0;
पूर्ण

अटल पूर्णांक ti81xx_pwrdm_पढ़ो_next_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs,
					     TI81XX_PM_PWSTCTRL,
					     OMAP_POWERSTATE_MASK);
पूर्ण

अटल पूर्णांक ti81xx_pwrdm_पढ़ो_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs,
		(pwrdm->prcm_offs == TI814X_PRM_GFX_MOD) ? TI81XX_RM_RSTCTRL :
					     TI81XX_PM_PWSTST,
					     OMAP_POWERSTATEST_MASK);
पूर्ण

अटल पूर्णांक ti81xx_pwrdm_पढ़ो_logic_pwrst(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	वापस omap2_prm_पढ़ो_mod_bits_shअगरt(pwrdm->prcm_offs,
		(pwrdm->prcm_offs == TI814X_PRM_GFX_MOD) ? TI81XX_RM_RSTCTRL :
					     TI81XX_PM_PWSTST,
					     OMAP3430_LOGICSTATEST_MASK);
पूर्ण

अटल पूर्णांक ti81xx_pwrdm_रुको_transition(काष्ठा घातerकरोमुख्य *pwrdm)
अणु
	u32 c = 0;

	जबतक ((omap2_prm_पढ़ो_mod_reg(pwrdm->prcm_offs,
		(pwrdm->prcm_offs == TI814X_PRM_GFX_MOD) ? TI81XX_RM_RSTCTRL :
				       TI81XX_PM_PWSTST) &
		OMAP_INTRANSITION_MASK) &&
		(c++ < PWRDM_TRANSITION_BAILOUT))
			udelay(1);

	अगर (c > PWRDM_TRANSITION_BAILOUT) अणु
		pr_err("powerdomain: %s timeout waiting for transition\n",
		       pwrdm->name);
		वापस -EAGAIN;
	पूर्ण

	pr_debug("powerdomain: completed transition in %d loops\n", c);

	वापस 0;
पूर्ण

/* For dm814x we need to fix up fix GFX pwstst and rstctrl reg offsets */
अटल काष्ठा pwrdm_ops ti81xx_pwrdm_operations = अणु
	.pwrdm_set_next_pwrst	= ti81xx_pwrdm_set_next_pwrst,
	.pwrdm_पढ़ो_next_pwrst	= ti81xx_pwrdm_पढ़ो_next_pwrst,
	.pwrdm_पढ़ो_pwrst	= ti81xx_pwrdm_पढ़ो_pwrst,
	.pwrdm_पढ़ो_logic_pwrst	= ti81xx_pwrdm_पढ़ो_logic_pwrst,
	.pwrdm_रुको_transition	= ti81xx_pwrdm_रुको_transition,
पूर्ण;

व्योम __init omap3xxx_घातerकरोमुख्यs_init(व्योम)
अणु
	अचिन्हित पूर्णांक rev;

	अगर (!cpu_is_omap34xx() && !cpu_is_ti81xx())
		वापस;

	/* Only 81xx needs custom pwrdm_operations */
	अगर (!cpu_is_ti81xx())
		pwrdm_रेजिस्टर_platक्रमm_funcs(&omap3_pwrdm_operations);

	rev = omap_rev();

	अगर (rev == AM35XX_REV_ES1_0 || rev == AM35XX_REV_ES1_1) अणु
		pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_am35x);
	पूर्ण अन्यथा अगर (rev == TI8148_REV_ES1_0 || rev == TI8148_REV_ES2_0 ||
		   rev == TI8148_REV_ES2_1) अणु
		pwrdm_रेजिस्टर_platक्रमm_funcs(&ti81xx_pwrdm_operations);
		pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_ti814x);
	पूर्ण अन्यथा अगर (rev == TI8168_REV_ES1_0 || rev == TI8168_REV_ES1_1
			|| rev == TI8168_REV_ES2_0 || rev == TI8168_REV_ES2_1) अणु
		pwrdm_रेजिस्टर_platक्रमm_funcs(&ti81xx_pwrdm_operations);
		pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_ti816x);
	पूर्ण अन्यथा अणु
		pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_omap3430_common);

		चयन (rev) अणु
		हाल OMAP3430_REV_ES1_0:
			pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_omap3430es1);
			अवरोध;
		हाल OMAP3430_REV_ES2_0:
		हाल OMAP3430_REV_ES2_1:
		हाल OMAP3430_REV_ES3_0:
		हाल OMAP3630_REV_ES1_0:
			pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_omap3430es2_es3_0);
			अवरोध;
		हाल OMAP3430_REV_ES3_1:
		हाल OMAP3430_REV_ES3_1_2:
		हाल OMAP3630_REV_ES1_1:
		हाल OMAP3630_REV_ES1_2:
			pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_omap3430es3_1plus);
			अवरोध;
		शेष:
			WARN(1, "OMAP3 powerdomain init: unknown chip type\n");
		पूर्ण
	पूर्ण

	pwrdm_complete_init();
पूर्ण
