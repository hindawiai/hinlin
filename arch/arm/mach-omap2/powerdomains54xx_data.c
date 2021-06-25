<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP54XX Power करोमुख्यs framework
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 *
 * Abhijit Pagare (abhijitpagare@ti.com)
 * Benoit Cousson (b-cousson@ti.com)
 * Paul Walmsley (paul@pwsan.com)
 *
 * This file is स्वतःmatically generated from the OMAP hardware databases.
 * We respectfully ask that any modअगरications to this file be coordinated
 * with the खुला linux-omap@vger.kernel.org mailing list and the
 * authors above to ensure that the स्वतःgeneration scripts are kept
 * up-to-date with the file contents.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश "powerdomain.h"

#समावेश "prcm-common.h"
#समावेश "prcm44xx.h"
#समावेश "prm54xx.h"
#समावेश "prcm_mpu54xx.h"

/* core_54xx_pwrdm: CORE घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य core_54xx_pwrdm = अणु
	.name		  = "core_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRM_CORE_INST,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_RET_ON,
	.pwrsts_logic_ret = PWRSTS_RET,
	.banks		  = 5,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* core_nret_bank */
		[1] = PWRSTS_OFF_RET,	/* core_ocmram */
		[2] = PWRSTS_OFF_RET,	/* core_other_bank */
		[3] = PWRSTS_OFF_RET,	/* ipu_l2ram */
		[4] = PWRSTS_OFF_RET,	/* ipu_unicache */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_OFF_RET,	/* core_nret_bank */
		[1] = PWRSTS_OFF_RET,	/* core_ocmram */
		[2] = PWRSTS_OFF_RET,	/* core_other_bank */
		[3] = PWRSTS_OFF_RET,	/* ipu_l2ram */
		[4] = PWRSTS_OFF_RET,	/* ipu_unicache */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* abe_54xx_pwrdm: Audio back end घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य abe_54xx_pwrdm = अणु
	.name		  = "abe_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRM_ABE_INST,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF,
	.banks		  = 2,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* aessmem */
		[1] = PWRSTS_OFF_RET,	/* periphmem */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_OFF_RET,	/* aessmem */
		[1] = PWRSTS_OFF_RET,	/* periphmem */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* coreaon_54xx_pwrdm: Always ON logic that sits in VDD_CORE voltage करोमुख्य */
अटल काष्ठा घातerकरोमुख्य coreaon_54xx_pwrdm = अणु
	.name		  = "coreaon_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRM_COREAON_INST,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_ON,
पूर्ण;

/* dss_54xx_pwrdm: Display subप्रणाली घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य dss_54xx_pwrdm = अणु
	.name		  = "dss_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRM_DSS_INST,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* dss_mem */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_OFF_RET,	/* dss_mem */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* cpu0_54xx_pwrdm: MPU0 processor and Neon coprocessor घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य cpu0_54xx_pwrdm = अणु
	.name		  = "cpu0_pwrdm",
	.voltdm		  = अणु .name = "mpu" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRCM_MPU_PRM_C0_INST,
	.prcm_partition	  = OMAP54XX_PRCM_MPU_PARTITION,
	.pwrsts		  = PWRSTS_RET_ON,
	.pwrsts_logic_ret = PWRSTS_RET,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* cpu0_l1 */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* cpu0_l1 */
	पूर्ण,
पूर्ण;

/* cpu1_54xx_pwrdm: MPU1 processor and Neon coprocessor घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य cpu1_54xx_pwrdm = अणु
	.name		  = "cpu1_pwrdm",
	.voltdm		  = अणु .name = "mpu" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRCM_MPU_PRM_C1_INST,
	.prcm_partition	  = OMAP54XX_PRCM_MPU_PARTITION,
	.pwrsts		  = PWRSTS_RET_ON,
	.pwrsts_logic_ret = PWRSTS_RET,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* cpu1_l1 */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* cpu1_l1 */
	पूर्ण,
पूर्ण;

/* emu_54xx_pwrdm: Emulation घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य emu_54xx_pwrdm = अणु
	.name		  = "emu_pwrdm",
	.voltdm		  = अणु .name = "wkup" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRM_EMU_INST,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_ON,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* emu_bank */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_OFF_RET,	/* emu_bank */
	पूर्ण,
पूर्ण;

/* mpu_54xx_pwrdm: Modena processor and the Neon coprocessor घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य mpu_54xx_pwrdm = अणु
	.name		  = "mpu_pwrdm",
	.voltdm		  = अणु .name = "mpu" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRM_MPU_INST,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_RET_ON,
	.pwrsts_logic_ret = PWRSTS_RET,
	.banks		  = 2,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* mpu_l2 */
		[1] = PWRSTS_RET,	/* mpu_ram */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_OFF_RET,	/* mpu_l2 */
		[1] = PWRSTS_OFF_RET,	/* mpu_ram */
	पूर्ण,
पूर्ण;

/* custefuse_54xx_pwrdm: Customer efuse controller घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य custefuse_54xx_pwrdm = अणु
	.name		  = "custefuse_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRM_CUSTEFUSE_INST,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_ON,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* dsp_54xx_pwrdm: Tesla processor घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य dsp_54xx_pwrdm = अणु
	.name		  = "dsp_pwrdm",
	.voltdm		  = अणु .name = "mm" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRM_DSP_INST,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 3,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* dsp_edma */
		[1] = PWRSTS_OFF_RET,	/* dsp_l1 */
		[2] = PWRSTS_OFF_RET,	/* dsp_l2 */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_OFF_RET,	/* dsp_edma */
		[1] = PWRSTS_OFF_RET,	/* dsp_l1 */
		[2] = PWRSTS_OFF_RET,	/* dsp_l2 */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* cam_54xx_pwrdm: Camera subप्रणाली घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य cam_54xx_pwrdm = अणु
	.name		  = "cam_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRM_CAM_INST,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_ON,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* cam_mem */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_OFF_RET,	/* cam_mem */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* l3init_54xx_pwrdm: L3 initators pheripherals घातer करोमुख्य  */
अटल काष्ठा घातerकरोमुख्य l3init_54xx_pwrdm = अणु
	.name		  = "l3init_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRM_L3INIT_INST,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 2,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* l3init_bank1 */
		[1] = PWRSTS_OFF_RET,	/* l3init_bank2 */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_OFF_RET,	/* l3init_bank1 */
		[1] = PWRSTS_OFF_RET,	/* l3init_bank2 */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* gpu_54xx_pwrdm: 3D accelerator घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य gpu_54xx_pwrdm = अणु
	.name		  = "gpu_pwrdm",
	.voltdm		  = अणु .name = "mm" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRM_GPU_INST,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_ON,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* gpu_mem */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_OFF_RET,	/* gpu_mem */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* wkupaon_54xx_pwrdm: Wake-up घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य wkupaon_54xx_pwrdm = अणु
	.name		  = "wkupaon_pwrdm",
	.voltdm		  = अणु .name = "wkup" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRM_WKUPAON_INST,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_ON,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* wkup_bank */
	पूर्ण,
पूर्ण;

/* iva_54xx_pwrdm: IVA-HD घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य iva_54xx_pwrdm = अणु
	.name		  = "iva_pwrdm",
	.voltdm		  = अणु .name = "mm" पूर्ण,
	.prcm_offs	  = OMAP54XX_PRM_IVA_INST,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF,
	.banks		  = 4,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* hwa_mem */
		[1] = PWRSTS_OFF_RET,	/* sl2_mem */
		[2] = PWRSTS_OFF_RET,	/* tcm1_mem */
		[3] = PWRSTS_OFF_RET,	/* tcm2_mem */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_OFF_RET,	/* hwa_mem */
		[1] = PWRSTS_OFF_RET,	/* sl2_mem */
		[2] = PWRSTS_OFF_RET,	/* tcm1_mem */
		[3] = PWRSTS_OFF_RET,	/* tcm2_mem */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/*
 * The following घातer करोमुख्यs are not under SW control
 *
 * mpuaon
 * mmaon
 */

/* As घातerकरोमुख्यs are added or हटाओd above, this list must also be changed */
अटल काष्ठा घातerकरोमुख्य *घातerकरोमुख्यs_omap54xx[] __initdata = अणु
	&core_54xx_pwrdm,
	&abe_54xx_pwrdm,
	&coreaon_54xx_pwrdm,
	&dss_54xx_pwrdm,
	&cpu0_54xx_pwrdm,
	&cpu1_54xx_pwrdm,
	&emu_54xx_pwrdm,
	&mpu_54xx_pwrdm,
	&custefuse_54xx_pwrdm,
	&dsp_54xx_pwrdm,
	&cam_54xx_pwrdm,
	&l3init_54xx_pwrdm,
	&gpu_54xx_pwrdm,
	&wkupaon_54xx_pwrdm,
	&iva_54xx_pwrdm,
	शून्य
पूर्ण;

व्योम __init omap54xx_घातerकरोमुख्यs_init(व्योम)
अणु
	pwrdm_रेजिस्टर_platक्रमm_funcs(&omap4_pwrdm_operations);
	pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_omap54xx);
	pwrdm_complete_init();
पूर्ण
