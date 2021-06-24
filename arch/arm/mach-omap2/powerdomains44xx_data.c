<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP4 Power करोमुख्यs framework
 *
 * Copyright (C) 2009-2011 Texas Instruments, Inc.
 * Copyright (C) 2009-2011 Nokia Corporation
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
#समावेश "prm-regbits-44xx.h"
#समावेश "prm44xx.h"
#समावेश "prcm_mpu44xx.h"

/* core_44xx_pwrdm: CORE घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य core_44xx_pwrdm = अणु
	.name		  = "core_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_CORE_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 5,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF,	/* core_nret_bank */
		[1] = PWRSTS_RET,	/* core_ocmram */
		[2] = PWRSTS_RET,	/* core_other_bank */
		[3] = PWRSTS_OFF_RET,	/* ducati_l2ram */
		[4] = PWRSTS_OFF_RET,	/* ducati_unicache */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* core_nret_bank */
		[1] = PWRSTS_ON,	/* core_ocmram */
		[2] = PWRSTS_ON,	/* core_other_bank */
		[3] = PWRSTS_ON,	/* ducati_l2ram */
		[4] = PWRSTS_ON,	/* ducati_unicache */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* gfx_44xx_pwrdm: 3D accelerator घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य gfx_44xx_pwrdm = अणु
	.name		  = "gfx_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_GFX_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_ON,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF,	/* gfx_mem */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* gfx_mem */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* abe_44xx_pwrdm: Audio back end घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य abe_44xx_pwrdm = अणु
	.name		  = "abe_pwrdm",
	.voltdm		  = अणु .name = "iva" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_ABE_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF,
	.banks		  = 2,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_RET,	/* aessmem */
		[1] = PWRSTS_OFF,	/* periphmem */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* aessmem */
		[1] = PWRSTS_ON,	/* periphmem */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* dss_44xx_pwrdm: Display subप्रणाली घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य dss_44xx_pwrdm = अणु
	.name		  = "dss_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_DSS_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF,	/* dss_mem */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* dss_mem */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* tesla_44xx_pwrdm: Tesla processor घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य tesla_44xx_pwrdm = अणु
	.name		  = "tesla_pwrdm",
	.voltdm		  = अणु .name = "iva" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_TESLA_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 3,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_RET,	/* tesla_edma */
		[1] = PWRSTS_OFF_RET,	/* tesla_l1 */
		[2] = PWRSTS_OFF_RET,	/* tesla_l2 */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* tesla_edma */
		[1] = PWRSTS_ON,	/* tesla_l1 */
		[2] = PWRSTS_ON,	/* tesla_l2 */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* wkup_44xx_pwrdm: Wake-up घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य wkup_44xx_pwrdm = अणु
	.name		  = "wkup_pwrdm",
	.voltdm		  = अणु .name = "wakeup" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_WKUP_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_ON,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF,	/* wkup_bank */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* wkup_bank */
	पूर्ण,
पूर्ण;

/* cpu0_44xx_pwrdm: MPU0 processor and Neon coprocessor घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य cpu0_44xx_pwrdm = अणु
	.name		  = "cpu0_pwrdm",
	.voltdm		  = अणु .name = "mpu" पूर्ण,
	.prcm_offs	  = OMAP4430_PRCM_MPU_CPU0_INST,
	.prcm_partition	  = OMAP4430_PRCM_MPU_PARTITION,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* cpu0_l1 */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* cpu0_l1 */
	पूर्ण,
पूर्ण;

/* cpu1_44xx_pwrdm: MPU1 processor and Neon coprocessor घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य cpu1_44xx_pwrdm = अणु
	.name		  = "cpu1_pwrdm",
	.voltdm		  = अणु .name = "mpu" पूर्ण,
	.prcm_offs	  = OMAP4430_PRCM_MPU_CPU1_INST,
	.prcm_partition	  = OMAP4430_PRCM_MPU_PARTITION,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* cpu1_l1 */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* cpu1_l1 */
	पूर्ण,
पूर्ण;

/* emu_44xx_pwrdm: Emulation घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य emu_44xx_pwrdm = अणु
	.name		  = "emu_pwrdm",
	.voltdm		  = अणु .name = "wakeup" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_EMU_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_ON,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF,	/* emu_bank */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* emu_bank */
	पूर्ण,
पूर्ण;

/* mpu_44xx_pwrdm: Modena processor and the Neon coprocessor घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य mpu_44xx_pwrdm = अणु
	.name		  = "mpu_pwrdm",
	.voltdm		  = अणु .name = "mpu" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_MPU_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 3,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF_RET,	/* mpu_l1 */
		[1] = PWRSTS_OFF_RET,	/* mpu_l2 */
		[2] = PWRSTS_RET,	/* mpu_ram */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* mpu_l1 */
		[1] = PWRSTS_ON,	/* mpu_l2 */
		[2] = PWRSTS_ON,	/* mpu_ram */
	पूर्ण,
पूर्ण;

/* ivahd_44xx_pwrdm: IVA-HD घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य ivahd_44xx_pwrdm = अणु
	.name		  = "ivahd_pwrdm",
	.voltdm		  = अणु .name = "iva" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_IVAHD_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF,
	.banks		  = 4,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF,	/* hwa_mem */
		[1] = PWRSTS_OFF_RET,	/* sl2_mem */
		[2] = PWRSTS_OFF_RET,	/* tcm1_mem */
		[3] = PWRSTS_OFF_RET,	/* tcm2_mem */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* hwa_mem */
		[1] = PWRSTS_ON,	/* sl2_mem */
		[2] = PWRSTS_ON,	/* tcm1_mem */
		[3] = PWRSTS_ON,	/* tcm2_mem */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* cam_44xx_pwrdm: Camera subप्रणाली घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य cam_44xx_pwrdm = अणु
	.name		  = "cam_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_CAM_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_ON,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF,	/* cam_mem */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* cam_mem */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* l3init_44xx_pwrdm: L3 initators pheripherals घातer करोमुख्य  */
अटल काष्ठा घातerकरोमुख्य l3init_44xx_pwrdm = अणु
	.name		  = "l3init_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_L3INIT_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 1,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF,	/* l3init_bank1 */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* l3init_bank1 */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/* l4per_44xx_pwrdm: Target peripherals घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य l4per_44xx_pwrdm = अणु
	.name		  = "l4per_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_L4PER_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_RET_ON,
	.pwrsts_logic_ret = PWRSTS_OFF_RET,
	.banks		  = 2,
	.pwrsts_mem_ret	= अणु
		[0] = PWRSTS_OFF,	/* nonretained_bank */
		[1] = PWRSTS_RET,	/* retained_bank */
	पूर्ण,
	.pwrsts_mem_on	= अणु
		[0] = PWRSTS_ON,	/* nonretained_bank */
		[1] = PWRSTS_ON,	/* retained_bank */
	पूर्ण,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/*
 * always_on_core_44xx_pwrdm: Always ON logic that sits in VDD_CORE voltage
 * करोमुख्य
 */
अटल काष्ठा घातerकरोमुख्य always_on_core_44xx_pwrdm = अणु
	.name		  = "always_on_core_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_ALWAYS_ON_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_ON,
पूर्ण;

/* cefuse_44xx_pwrdm: Customer efuse controller घातer करोमुख्य */
अटल काष्ठा घातerकरोमुख्य cefuse_44xx_pwrdm = अणु
	.name		  = "cefuse_pwrdm",
	.voltdm		  = अणु .name = "core" पूर्ण,
	.prcm_offs	  = OMAP4430_PRM_CEFUSE_INST,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.pwrsts		  = PWRSTS_OFF_ON,
	.flags		  = PWRDM_HAS_LOWPOWERSTATECHANGE,
पूर्ण;

/*
 * The following घातer करोमुख्यs are not under SW control
 *
 * always_on_iva
 * always_on_mpu
 * stdefuse
 */

/* As घातerकरोमुख्यs are added or हटाओd above, this list must also be changed */
अटल काष्ठा घातerकरोमुख्य *घातerकरोमुख्यs_omap44xx[] __initdata = अणु
	&core_44xx_pwrdm,
	&gfx_44xx_pwrdm,
	&abe_44xx_pwrdm,
	&dss_44xx_pwrdm,
	&tesla_44xx_pwrdm,
	&wkup_44xx_pwrdm,
	&cpu0_44xx_pwrdm,
	&cpu1_44xx_pwrdm,
	&emu_44xx_pwrdm,
	&mpu_44xx_pwrdm,
	&ivahd_44xx_pwrdm,
	&cam_44xx_pwrdm,
	&l3init_44xx_pwrdm,
	&l4per_44xx_pwrdm,
	&always_on_core_44xx_pwrdm,
	&cefuse_44xx_pwrdm,
	शून्य
पूर्ण;

व्योम __init omap44xx_घातerकरोमुख्यs_init(व्योम)
अणु
	pwrdm_रेजिस्टर_platक्रमm_funcs(&omap4_pwrdm_operations);
	pwrdm_रेजिस्टर_pwrdms(घातerकरोमुख्यs_omap44xx);
	pwrdm_complete_init();
पूर्ण
