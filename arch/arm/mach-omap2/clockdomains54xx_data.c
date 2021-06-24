<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP54XX Clock करोमुख्यs framework
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
#समावेश <linux/पन.स>

#समावेश "clockdomain.h"
#समावेश "cm1_54xx.h"
#समावेश "cm2_54xx.h"

#समावेश "cm-regbits-54xx.h"
#समावेश "prm54xx.h"
#समावेश "prcm44xx.h"
#समावेश "prcm_mpu54xx.h"

/* Static Dependencies क्रम OMAP4 Clock Doमुख्यs */

अटल काष्ठा clkdm_dep c2c_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "abe_clkdm" पूर्ण,
	अणु .clkdm_name = "emif_clkdm" पूर्ण,
	अणु .clkdm_name = "iva_clkdm" पूर्ण,
	अणु .clkdm_name = "l3init_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main2_clkdm" पूर्ण,
	अणु .clkdm_name = "l4cfg_clkdm" पूर्ण,
	अणु .clkdm_name = "l4per_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep cam_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "emif_clkdm" पूर्ण,
	अणु .clkdm_name = "iva_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main1_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep dma_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "abe_clkdm" पूर्ण,
	अणु .clkdm_name = "dss_clkdm" पूर्ण,
	अणु .clkdm_name = "emif_clkdm" पूर्ण,
	अणु .clkdm_name = "ipu_clkdm" पूर्ण,
	अणु .clkdm_name = "iva_clkdm" पूर्ण,
	अणु .clkdm_name = "l3init_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main1_clkdm" पूर्ण,
	अणु .clkdm_name = "l4cfg_clkdm" पूर्ण,
	अणु .clkdm_name = "l4per_clkdm" पूर्ण,
	अणु .clkdm_name = "l4sec_clkdm" पूर्ण,
	अणु .clkdm_name = "wkupaon_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep dsp_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "abe_clkdm" पूर्ण,
	अणु .clkdm_name = "emif_clkdm" पूर्ण,
	अणु .clkdm_name = "iva_clkdm" पूर्ण,
	अणु .clkdm_name = "l3init_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main2_clkdm" पूर्ण,
	अणु .clkdm_name = "l4cfg_clkdm" पूर्ण,
	अणु .clkdm_name = "l4per_clkdm" पूर्ण,
	अणु .clkdm_name = "wkupaon_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep dss_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "emif_clkdm" पूर्ण,
	अणु .clkdm_name = "iva_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main2_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep gpu_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "emif_clkdm" पूर्ण,
	अणु .clkdm_name = "iva_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main1_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep ipu_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "abe_clkdm" पूर्ण,
	अणु .clkdm_name = "dsp_clkdm" पूर्ण,
	अणु .clkdm_name = "dss_clkdm" पूर्ण,
	अणु .clkdm_name = "emif_clkdm" पूर्ण,
	अणु .clkdm_name = "gpu_clkdm" पूर्ण,
	अणु .clkdm_name = "iva_clkdm" पूर्ण,
	अणु .clkdm_name = "l3init_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main2_clkdm" पूर्ण,
	अणु .clkdm_name = "l4cfg_clkdm" पूर्ण,
	अणु .clkdm_name = "l4per_clkdm" पूर्ण,
	अणु .clkdm_name = "l4sec_clkdm" पूर्ण,
	अणु .clkdm_name = "wkupaon_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep iva_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "emif_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main1_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep l3init_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "abe_clkdm" पूर्ण,
	अणु .clkdm_name = "emif_clkdm" पूर्ण,
	अणु .clkdm_name = "iva_clkdm" पूर्ण,
	अणु .clkdm_name = "l4cfg_clkdm" पूर्ण,
	अणु .clkdm_name = "l4per_clkdm" पूर्ण,
	अणु .clkdm_name = "l4sec_clkdm" पूर्ण,
	अणु .clkdm_name = "wkupaon_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep l4sec_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "emif_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main1_clkdm" पूर्ण,
	अणु .clkdm_name = "l4per_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep mipiext_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "abe_clkdm" पूर्ण,
	अणु .clkdm_name = "emif_clkdm" पूर्ण,
	अणु .clkdm_name = "iva_clkdm" पूर्ण,
	अणु .clkdm_name = "l3init_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main2_clkdm" पूर्ण,
	अणु .clkdm_name = "l4cfg_clkdm" पूर्ण,
	अणु .clkdm_name = "l4per_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा clkdm_dep mpu_wkup_sleep_deps[] = अणु
	अणु .clkdm_name = "abe_clkdm" पूर्ण,
	अणु .clkdm_name = "dsp_clkdm" पूर्ण,
	अणु .clkdm_name = "dss_clkdm" पूर्ण,
	अणु .clkdm_name = "emif_clkdm" पूर्ण,
	अणु .clkdm_name = "gpu_clkdm" पूर्ण,
	अणु .clkdm_name = "ipu_clkdm" पूर्ण,
	अणु .clkdm_name = "iva_clkdm" पूर्ण,
	अणु .clkdm_name = "l3init_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main1_clkdm" पूर्ण,
	अणु .clkdm_name = "l3main2_clkdm" पूर्ण,
	अणु .clkdm_name = "l4cfg_clkdm" पूर्ण,
	अणु .clkdm_name = "l4per_clkdm" पूर्ण,
	अणु .clkdm_name = "l4sec_clkdm" पूर्ण,
	अणु .clkdm_name = "wkupaon_clkdm" पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4sec_54xx_clkdm = अणु
	.name		  = "l4sec_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_CORE_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_CORE_L4SEC_CDOFFS,
	.dep_bit	  = OMAP54XX_L4SEC_STATDEP_SHIFT,
	.wkdep_srcs	  = l4sec_wkup_sleep_deps,
	.sleepdep_srcs	  = l4sec_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य iva_54xx_clkdm = अणु
	.name		  = "iva_clkdm",
	.pwrdm		  = अणु .name = "iva_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_IVA_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_IVA_IVA_CDOFFS,
	.dep_bit	  = OMAP54XX_IVA_STATDEP_SHIFT,
	.wkdep_srcs	  = iva_wkup_sleep_deps,
	.sleepdep_srcs	  = iva_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य mipiext_54xx_clkdm = अणु
	.name		  = "mipiext_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_CORE_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_CORE_MIPIEXT_CDOFFS,
	.wkdep_srcs	  = mipiext_wkup_sleep_deps,
	.sleepdep_srcs	  = mipiext_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3मुख्य2_54xx_clkdm = अणु
	.name		  = "l3main2_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_CORE_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_CORE_L3MAIN2_CDOFFS,
	.dep_bit	  = OMAP54XX_L3MAIN2_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3मुख्य1_54xx_clkdm = अणु
	.name		  = "l3main1_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_CORE_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_CORE_L3MAIN1_CDOFFS,
	.dep_bit	  = OMAP54XX_L3MAIN1_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य custefuse_54xx_clkdm = अणु
	.name		  = "custefuse_clkdm",
	.pwrdm		  = अणु .name = "custefuse_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_CUSTEFUSE_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_CUSTEFUSE_CUSTEFUSE_CDOFFS,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य ipu_54xx_clkdm = अणु
	.name		  = "ipu_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_CORE_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_CORE_IPU_CDOFFS,
	.dep_bit	  = OMAP54XX_IPU_STATDEP_SHIFT,
	.wkdep_srcs	  = ipu_wkup_sleep_deps,
	.sleepdep_srcs	  = ipu_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4cfg_54xx_clkdm = अणु
	.name		  = "l4cfg_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_CORE_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_CORE_L4CFG_CDOFFS,
	.dep_bit	  = OMAP54XX_L4CFG_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य abe_54xx_clkdm = अणु
	.name		  = "abe_clkdm",
	.pwrdm		  = अणु .name = "abe_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_AON_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_AON_ABE_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_AON_ABE_ABE_CDOFFS,
	.dep_bit	  = OMAP54XX_ABE_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य dss_54xx_clkdm = अणु
	.name		  = "dss_clkdm",
	.pwrdm		  = अणु .name = "dss_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_DSS_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_DSS_DSS_CDOFFS,
	.dep_bit	  = OMAP54XX_DSS_STATDEP_SHIFT,
	.wkdep_srcs	  = dss_wkup_sleep_deps,
	.sleepdep_srcs	  = dss_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य dsp_54xx_clkdm = अणु
	.name		  = "dsp_clkdm",
	.pwrdm		  = अणु .name = "dsp_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_AON_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_AON_DSP_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_AON_DSP_DSP_CDOFFS,
	.dep_bit	  = OMAP54XX_DSP_STATDEP_SHIFT,
	.wkdep_srcs	  = dsp_wkup_sleep_deps,
	.sleepdep_srcs	  = dsp_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य c2c_54xx_clkdm = अणु
	.name		  = "c2c_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_CORE_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_CORE_C2C_CDOFFS,
	.wkdep_srcs	  = c2c_wkup_sleep_deps,
	.sleepdep_srcs	  = c2c_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4per_54xx_clkdm = अणु
	.name		  = "l4per_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_CORE_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_CORE_L4PER_CDOFFS,
	.dep_bit	  = OMAP54XX_L4PER_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य gpu_54xx_clkdm = अणु
	.name		  = "gpu_clkdm",
	.pwrdm		  = अणु .name = "gpu_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_GPU_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_GPU_GPU_CDOFFS,
	.dep_bit	  = OMAP54XX_GPU_STATDEP_SHIFT,
	.wkdep_srcs	  = gpu_wkup_sleep_deps,
	.sleepdep_srcs	  = gpu_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य wkupaon_54xx_clkdm = अणु
	.name		  = "wkupaon_clkdm",
	.pwrdm		  = अणु .name = "wkupaon_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.cm_inst	  = OMAP54XX_PRM_WKUPAON_CM_INST,
	.clkdm_offs	  = OMAP54XX_PRM_WKUPAON_CM_WKUPAON_CDOFFS,
	.dep_bit	  = OMAP54XX_WKUPAON_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य mpu0_54xx_clkdm = अणु
	.name		  = "mpu0_clkdm",
	.pwrdm		  = अणु .name = "cpu0_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_PRCM_MPU_PARTITION,
	.cm_inst	  = OMAP54XX_PRCM_MPU_CM_C0_INST,
	.clkdm_offs	  = OMAP54XX_PRCM_MPU_CM_C0_CPU0_CDOFFS,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य mpu1_54xx_clkdm = अणु
	.name		  = "mpu1_clkdm",
	.pwrdm		  = अणु .name = "cpu1_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_PRCM_MPU_PARTITION,
	.cm_inst	  = OMAP54XX_PRCM_MPU_CM_C1_INST,
	.clkdm_offs	  = OMAP54XX_PRCM_MPU_CM_C1_CPU1_CDOFFS,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य coreaon_54xx_clkdm = अणु
	.name		  = "coreaon_clkdm",
	.pwrdm		  = अणु .name = "coreaon_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_COREAON_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_COREAON_COREAON_CDOFFS,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य mpu_54xx_clkdm = अणु
	.name		  = "mpu_clkdm",
	.pwrdm		  = अणु .name = "mpu_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_AON_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_AON_MPU_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_AON_MPU_MPU_CDOFFS,
	.wkdep_srcs	  = mpu_wkup_sleep_deps,
	.sleepdep_srcs	  = mpu_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3init_54xx_clkdm = अणु
	.name		  = "l3init_clkdm",
	.pwrdm		  = अणु .name = "l3init_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_L3INIT_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_L3INIT_L3INIT_CDOFFS,
	.dep_bit	  = OMAP54XX_L3INIT_STATDEP_SHIFT,
	.wkdep_srcs	  = l3init_wkup_sleep_deps,
	.sleepdep_srcs	  = l3init_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य dma_54xx_clkdm = अणु
	.name		  = "dma_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_CORE_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_CORE_DMA_CDOFFS,
	.wkdep_srcs	  = dma_wkup_sleep_deps,
	.sleepdep_srcs	  = dma_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3instr_54xx_clkdm = अणु
	.name		  = "l3instr_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_CORE_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_CORE_L3INSTR_CDOFFS,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य emअगर_54xx_clkdm = अणु
	.name		  = "emif_clkdm",
	.pwrdm		  = अणु .name = "core_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_CORE_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_CORE_EMIF_CDOFFS,
	.dep_bit	  = OMAP54XX_EMIF_STATDEP_SHIFT,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य emu_54xx_clkdm = अणु
	.name		  = "emu_clkdm",
	.pwrdm		  = अणु .name = "emu_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_PRM_PARTITION,
	.cm_inst	  = OMAP54XX_PRM_EMU_CM_INST,
	.clkdm_offs	  = OMAP54XX_PRM_EMU_CM_EMU_CDOFFS,
	.flags		  = CLKDM_CAN_FORCE_WAKEUP | CLKDM_CAN_HWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य cam_54xx_clkdm = अणु
	.name		  = "cam_clkdm",
	.pwrdm		  = अणु .name = "cam_pwrdm" पूर्ण,
	.prcm_partition	  = OMAP54XX_CM_CORE_PARTITION,
	.cm_inst	  = OMAP54XX_CM_CORE_CAM_INST,
	.clkdm_offs	  = OMAP54XX_CM_CORE_CAM_CAM_CDOFFS,
	.wkdep_srcs	  = cam_wkup_sleep_deps,
	.sleepdep_srcs	  = cam_wkup_sleep_deps,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

/* As घड़ीकरोमुख्यs are added or हटाओd above, this list must also be changed */
अटल काष्ठा घड़ीकरोमुख्य *घड़ीकरोमुख्यs_omap54xx[] __initdata = अणु
	&l4sec_54xx_clkdm,
	&iva_54xx_clkdm,
	&mipiext_54xx_clkdm,
	&l3मुख्य2_54xx_clkdm,
	&l3मुख्य1_54xx_clkdm,
	&custefuse_54xx_clkdm,
	&ipu_54xx_clkdm,
	&l4cfg_54xx_clkdm,
	&abe_54xx_clkdm,
	&dss_54xx_clkdm,
	&dsp_54xx_clkdm,
	&c2c_54xx_clkdm,
	&l4per_54xx_clkdm,
	&gpu_54xx_clkdm,
	&wkupaon_54xx_clkdm,
	&mpu0_54xx_clkdm,
	&mpu1_54xx_clkdm,
	&coreaon_54xx_clkdm,
	&mpu_54xx_clkdm,
	&l3init_54xx_clkdm,
	&dma_54xx_clkdm,
	&l3instr_54xx_clkdm,
	&emअगर_54xx_clkdm,
	&emu_54xx_clkdm,
	&cam_54xx_clkdm,
	शून्य
पूर्ण;

व्योम __init omap54xx_घड़ीकरोमुख्यs_init(व्योम)
अणु
	clkdm_रेजिस्टर_platक्रमm_funcs(&omap4_clkdm_operations);
	clkdm_रेजिस्टर_clkdms(घड़ीकरोमुख्यs_omap54xx);
	clkdm_complete_init();
पूर्ण
