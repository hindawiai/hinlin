<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP4 Clock करोमुख्यs framework
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
#समावेश <linux/पन.स>

#समावेश "clockdomain.h"
#समावेश "cm1_44xx.h"
#समावेश "cm2_44xx.h"

#समावेश "cm-regbits-44xx.h"
#समावेश "prm44xx.h"
#समावेश "prcm44xx.h"
#समावेश "prcm_mpu44xx.h"

/* Static Dependencies क्रम OMAP4 Clock Doमुख्यs */

अटल काष्ठा clkdm_dep d2d_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "abe_clkdm" पूर्ण,
	अणु .clkdm_name = "ivahd_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_2_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_emif_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_init_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_cfg_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_per_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep ducati_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "abe_clkdm" पूर्ण,
	अणु .clkdm_name = "ivahd_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_2_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_dss_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_emif_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_gfx_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_init_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_cfg_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_per_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_secure_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_wkup_clkdm" पूर्ण,
	अणु .clkdm_name = "tesla_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep iss_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "ivahd_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_emif_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep ivahd_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "l3_1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_emif_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep l3_dma_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "abe_clkdm" पूर्ण,
	अणु .clkdm_name = "ducati_clkdm" पूर्ण,
	अणु .clkdm_name = "ivahd_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_dss_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_emif_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_init_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_cfg_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_per_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_secure_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep l3_dss_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "ivahd_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_2_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_emif_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep l3_gfx_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "ivahd_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_emif_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep l3_init_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "abe_clkdm" पूर्ण,
	अणु .clkdm_name = "ivahd_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_emif_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_cfg_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_per_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_secure_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep l4_secure_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "l3_1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_emif_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_per_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep mpu_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "abe_clkdm" पूर्ण,
	अणु .clkdm_name = "ducati_clkdm" पूर्ण,
	अणु .clkdm_name = "ivahd_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_2_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_dss_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_emif_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_gfx_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_init_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_cfg_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_per_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_secure_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_wkup_clkdm" पूर्ण,
	अणु .clkdm_name = "tesla_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep tesla_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "abe_clkdm" पूर्ण,
	अणु .clkdm_name = "ivahd_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_2_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_emif_clkdm" पूर्ण,
	अणु .clkdm_name = "l3_init_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_cfg_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_per_clkdm" पूर्ण,
	अणु .clkdm_name = "l4_wkup_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4_cefuse_44xx_clkdm = अणु
	.name		  = "l4_cefuse_clkdm",
	.pwrdm		  = अणु .name = "cefuse_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_CEFUSE_INST,
	.clkdm_offs	  = OMAP4430_CM2_CEFUSE_CEFUSE_CDOFFS,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4_cfg_44xx_clkdm = अणु
	.name		  = "l4_cfg_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_CORE_INST,
	.clkdm_offs	  = OMAP4430_CM2_CORE_L4CFG_CDOFFS,
	.dep_bit	  = OMAP4430_L4CFG_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य tesla_44xx_clkdm = अणु
	.name		  = "tesla_clkdm",
	.pwrdm		  = अणु .name = "tesla_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM1_PARTITION,
	.cm_inst	  = OMAP4430_CM1_TESLA_INST,
	.clkdm_offs	  = OMAP4430_CM1_TESLA_TESLA_CDOFFS,
	.dep_bit	  = OMAP4430_TESLA_STATDEP_SHIFT,
	.wkdep_srcs	  = tesla_wkup_sleep_deps,
	.sleepdep_srcs	  = tesla_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3_gfx_44xx_clkdm = अणु
	.name		  = "l3_gfx_clkdm",
	.pwrdm		  = अणु .name = "gfx_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_GFX_INST,
	.clkdm_offs	  = OMAP4430_CM2_GFX_GFX_CDOFFS,
	.dep_bit	  = OMAP4430_GFX_STATDEP_SHIFT,
	.wkdep_srcs	  = l3_gfx_wkup_sleep_deps,
	.sleepdep_srcs	  = l3_gfx_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य ivahd_44xx_clkdm = अणु
	.name		  = "ivahd_clkdm",
	.pwrdm		  = अणु .name = "ivahd_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_IVAHD_INST,
	.clkdm_offs	  = OMAP4430_CM2_IVAHD_IVAHD_CDOFFS,
	.dep_bit	  = OMAP4430_IVAHD_STATDEP_SHIFT,
	.wkdep_srcs	  = ivahd_wkup_sleep_deps,
	.sleepdep_srcs	  = ivahd_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4_secure_44xx_clkdm = अणु
	.name		  = "l4_secure_clkdm",
	.pwrdm		  = अणु .name = "l4per_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_L4PER_INST,
	.clkdm_offs	  = OMAP4430_CM2_L4PER_L4SEC_CDOFFS,
	.dep_bit	  = OMAP4430_L4SEC_STATDEP_SHIFT,
	.wkdep_srcs	  = l4_secure_wkup_sleep_deps,
	.sleepdep_srcs	  = l4_secure_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4_per_44xx_clkdm = अणु
	.name		  = "l4_per_clkdm",
	.pwrdm		  = अणु .name = "l4per_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_L4PER_INST,
	.clkdm_offs	  = OMAP4430_CM2_L4PER_L4PER_CDOFFS,
	.dep_bit	  = OMAP4430_L4PER_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य abe_44xx_clkdm = अणु
	.name		  = "abe_clkdm",
	.pwrdm		  = अणु .name = "abe_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM1_PARTITION,
	.cm_inst	  = OMAP4430_CM1_ABE_INST,
	.clkdm_offs	  = OMAP4430_CM1_ABE_ABE_CDOFFS,
	.dep_bit	  = OMAP4430_ABE_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3_instr_44xx_clkdm = अणु
	.name		  = "l3_instr_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_CORE_INST,
	.clkdm_offs	  = OMAP4430_CM2_CORE_L3INSTR_CDOFFS,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3_init_44xx_clkdm = अणु
	.name		  = "l3_init_clkdm",
	.pwrdm		  = अणु .name = "l3init_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_L3INIT_INST,
	.clkdm_offs	  = OMAP4430_CM2_L3INIT_L3INIT_CDOFFS,
	.dep_bit	  = OMAP4430_L3INIT_STATDEP_SHIFT,
	.wkdep_srcs	  = l3_init_wkup_sleep_deps,
	.sleepdep_srcs	  = l3_init_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य d2d_44xx_clkdm = अणु
	.name		  = "d2d_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_CORE_INST,
	.clkdm_offs	  = OMAP4430_CM2_CORE_D2D_CDOFFS,
	.wkdep_srcs	  = d2d_wkup_sleep_deps,
	.sleepdep_srcs	  = d2d_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य mpu0_44xx_clkdm = अणु
	.name		  = "mpu0_clkdm",
	.pwrdm		  = अणु .name = "cpu0_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_PRCM_MPU_PARTITION,
	.cm_inst	  = OMAP4430_PRCM_MPU_CPU0_INST,
	.clkdm_offs	  = OMAP4430_PRCM_MPU_CPU0_CPU0_CDOFFS,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य mpu1_44xx_clkdm = अणु
	.name		  = "mpu1_clkdm",
	.pwrdm		  = अणु .name = "cpu1_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_PRCM_MPU_PARTITION,
	.cm_inst	  = OMAP4430_PRCM_MPU_CPU1_INST,
	.clkdm_offs	  = OMAP4430_PRCM_MPU_CPU1_CPU1_CDOFFS,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3_emअगर_44xx_clkdm = अणु
	.name		  = "l3_emif_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_CORE_INST,
	.clkdm_offs	  = OMAP4430_CM2_CORE_MEMIF_CDOFFS,
	.dep_bit	  = OMAP4430_MEMIF_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4_ao_44xx_clkdm = अणु
	.name		  = "l4_ao_clkdm",
	.pwrdm		  = अणु .name = "always_on_core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_ALWAYS_ON_INST,
	.clkdm_offs	  = OMAP4430_CM2_ALWAYS_ON_ALWON_CDOFFS,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य ducati_44xx_clkdm = अणु
	.name		  = "ducati_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_CORE_INST,
	.clkdm_offs	  = OMAP4430_CM2_CORE_DUCATI_CDOFFS,
	.dep_bit	  = OMAP4430_DUCATI_STATDEP_SHIFT,
	.wkdep_srcs	  = ducati_wkup_sleep_deps,
	.sleepdep_srcs	  = ducati_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य mpu_44xx_clkdm = अणु
	.name		  = "mpuss_clkdm",
	.pwrdm		  = अणु .name = "mpu_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM1_PARTITION,
	.cm_inst	  = OMAP4430_CM1_MPU_INST,
	.clkdm_offs	  = OMAP4430_CM1_MPU_MPU_CDOFFS,
	.wkdep_srcs	  = mpu_wkup_sleep_deps,
	.sleepdep_srcs	  = mpu_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3_2_44xx_clkdm = अणु
	.name		  = "l3_2_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_CORE_INST,
	.clkdm_offs	  = OMAP4430_CM2_CORE_L3_2_CDOFFS,
	.dep_bit	  = OMAP4430_L3_2_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3_1_44xx_clkdm = अणु
	.name		  = "l3_1_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_CORE_INST,
	.clkdm_offs	  = OMAP4430_CM2_CORE_L3_1_CDOFFS,
	.dep_bit	  = OMAP4430_L3_1_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य iss_44xx_clkdm = अणु
	.name		  = "iss_clkdm",
	.pwrdm		  = अणु .name = "cam_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_CAM_INST,
	.clkdm_offs	  = OMAP4430_CM2_CAM_CAM_CDOFFS,
	.wkdep_srcs	  = iss_wkup_sleep_deps,
	.sleepdep_srcs	  = iss_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3_dss_44xx_clkdm = अणु
	.name		  = "l3_dss_clkdm",
	.pwrdm		  = अणु .name = "dss_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_DSS_INST,
	.clkdm_offs	  = OMAP4430_CM2_DSS_DSS_CDOFFS,
	.dep_bit	  = OMAP4430_DSS_STATDEP_SHIFT,
	.wkdep_srcs	  = l3_dss_wkup_sleep_deps,
	.sleepdep_srcs	  = l3_dss_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4_wkup_44xx_clkdm = अणु
	.name		  = "l4_wkup_clkdm",
	.pwrdm		  = अणु .name = "wkup_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.cm_inst	  = OMAP4430_PRM_WKUP_CM_INST,
	.clkdm_offs	  = OMAP4430_PRM_WKUP_CM_WKUP_CDOFFS,
	.dep_bit	  = OMAP4430_L4WKUP_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_HWSUP | CLKDM_ACTIVE_WITH_MPU,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य emu_sys_44xx_clkdm = अणु
	.name		  = "emu_sys_clkdm",
	.pwrdm		  = अणु .name = "emu_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_PRM_PARTITION,
	.cm_inst	  = OMAP4430_PRM_EMU_CM_INST,
	.clkdm_offs	  = OMAP4430_PRM_EMU_CM_EMU_CDOFFS,
	.flags		  = (CLKDM_CAN_ENABLE_AUTO | CLKDM_CAN_FORCE_WAKEUP |
			     CLKDM_MISSING_IDLE_REPORTING),
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3_dma_44xx_clkdm = अणु
	.name		  = "l3_dma_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP4430_CM2_PARTITION,
	.cm_inst	  = OMAP4430_CM2_CORE_INST,
	.clkdm_offs	  = OMAP4430_CM2_CORE_SDMA_CDOFFS,
	.wkdep_srcs	  = l3_dma_wkup_sleep_deps,
	.sleepdep_srcs	  = l3_dma_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

/* As घड़ीकरोमुख्यs are added or हटाओd above, this list must also be changed */
अटल काष्ठा घड़ीकरोमुख्य *घड़ीकरोमुख्यs_omap44xx[] __initdata = अणु
	&l4_cefuse_44xx_clkdm,
	&l4_cfg_44xx_clkdm,
	&tesla_44xx_clkdm,
	&l3_gfx_44xx_clkdm,
	&ivahd_44xx_clkdm,
	&l4_secure_44xx_clkdm,
	&l4_per_44xx_clkdm,
	&abe_44xx_clkdm,
	&l3_instr_44xx_clkdm,
	&l3_init_44xx_clkdm,
	&d2d_44xx_clkdm,
	&mpu0_44xx_clkdm,
	&mpu1_44xx_clkdm,
	&l3_emअगर_44xx_clkdm,
	&l4_ao_44xx_clkdm,
	&ducati_44xx_clkdm,
	&mpu_44xx_clkdm,
	&l3_2_44xx_clkdm,
	&l3_1_44xx_clkdm,
	&iss_44xx_clkdm,
	&l3_dss_44xx_clkdm,
	&l4_wkup_44xx_clkdm,
	&emu_sys_44xx_clkdm,
	&l3_dma_44xx_clkdm,
	शून्य
पूर्ण;


व्योम __init omap44xx_घड़ीकरोमुख्यs_init(व्योम)
अणु
	clkdm_रेजिस्टर_platक्रमm_funcs(&omap4_clkdm_operations);
	clkdm_रेजिस्टर_clkdms(घड़ीकरोमुख्यs_omap44xx);
	clkdm_complete_init();
पूर्ण
