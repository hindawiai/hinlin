<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AM43xx Clock करोमुख्यs framework
 *
 * Copyright (C) 2013 Texas Instruments, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>

#समावेश "clockdomain.h"
#समावेश "prcm44xx.h"
#समावेश "prcm43xx.h"

अटल काष्ठा घड़ीकरोमुख्य l4_cefuse_43xx_clkdm = अणु
	.name		  = "l4_cefuse_clkdm",
	.pwrdm		  = अणु .name = "cefuse_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_CEFUSE_INST,
	.clkdm_offs	  = AM43XX_CM_CEFUSE_CEFUSE_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य mpu_43xx_clkdm = अणु
	.name		  = "mpu_clkdm",
	.pwrdm		  = अणु .name = "mpu_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_MPU_INST,
	.clkdm_offs	  = AM43XX_CM_MPU_MPU_CDOFFS,
	.flags		  = CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4ls_43xx_clkdm = अणु
	.name		  = "l4ls_clkdm",
	.pwrdm		  = अणु .name = "per_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_PER_INST,
	.clkdm_offs	  = AM43XX_CM_PER_L4LS_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य tamper_43xx_clkdm = अणु
	.name		  = "tamper_clkdm",
	.pwrdm		  = अणु .name = "tamper_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_TAMPER_INST,
	.clkdm_offs	  = AM43XX_CM_TAMPER_TAMPER_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4_rtc_43xx_clkdm = अणु
	.name		  = "l4_rtc_clkdm",
	.pwrdm		  = अणु .name = "rtc_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_RTC_INST,
	.clkdm_offs	  = AM43XX_CM_RTC_RTC_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य pruss_ocp_43xx_clkdm = अणु
	.name		  = "pruss_ocp_clkdm",
	.pwrdm		  = अणु .name = "per_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_PER_INST,
	.clkdm_offs	  = AM43XX_CM_PER_ICSS_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य ocpwp_l3_43xx_clkdm = अणु
	.name		  = "ocpwp_l3_clkdm",
	.pwrdm		  = अणु .name = "per_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_PER_INST,
	.clkdm_offs	  = AM43XX_CM_PER_OCPWP_L3_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3s_tsc_43xx_clkdm = अणु
	.name		  = "l3s_tsc_clkdm",
	.pwrdm		  = अणु .name = "wkup_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_WKUP_INST,
	.clkdm_offs	  = AM43XX_CM_WKUP_L3S_TSC_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य lcdc_43xx_clkdm = अणु
	.name		  = "lcdc_clkdm",
	.pwrdm		  = अणु .name = "per_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_PER_INST,
	.clkdm_offs	  = AM43XX_CM_PER_LCDC_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य dss_43xx_clkdm = अणु
	.name		  = "dss_clkdm",
	.pwrdm		  = अणु .name = "per_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_PER_INST,
	.clkdm_offs	  = AM43XX_CM_PER_DSS_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3_aon_43xx_clkdm = अणु
	.name		  = "l3_aon_clkdm",
	.pwrdm		  = अणु .name = "wkup_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_WKUP_INST,
	.clkdm_offs	  = AM43XX_CM_WKUP_L3_AON_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य emअगर_43xx_clkdm = अणु
	.name		  = "emif_clkdm",
	.pwrdm		  = अणु .name = "per_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_PER_INST,
	.clkdm_offs	  = AM43XX_CM_PER_EMIF_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4_wkup_aon_43xx_clkdm = अणु
	.name		  = "l4_wkup_aon_clkdm",
	.pwrdm		  = अणु .name = "wkup_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_WKUP_INST,
	.clkdm_offs	  = AM43XX_CM_WKUP_L4_WKUP_AON_CDOFFS,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3_43xx_clkdm = अणु
	.name		  = "l3_clkdm",
	.pwrdm		  = अणु .name = "per_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_PER_INST,
	.clkdm_offs	  = AM43XX_CM_PER_L3_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4_wkup_43xx_clkdm = अणु
	.name		  = "l4_wkup_clkdm",
	.pwrdm		  = अणु .name = "wkup_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_WKUP_INST,
	.clkdm_offs	  = AM43XX_CM_WKUP_WKUP_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य cpsw_125mhz_43xx_clkdm = अणु
	.name		  = "cpsw_125mhz_clkdm",
	.pwrdm		  = अणु .name = "per_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_PER_INST,
	.clkdm_offs	  = AM43XX_CM_PER_CPSW_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य gfx_l3_43xx_clkdm = अणु
	.name		  = "gfx_l3_clkdm",
	.pwrdm		  = अणु .name = "gfx_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_GFX_INST,
	.clkdm_offs	  = AM43XX_CM_GFX_GFX_L3_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3s_43xx_clkdm = अणु
	.name		  = "l3s_clkdm",
	.pwrdm		  = अणु .name = "per_pwrdm" पूर्ण,
	.prcm_partition	  = AM43XX_CM_PARTITION,
	.cm_inst	  = AM43XX_CM_PER_INST,
	.clkdm_offs	  = AM43XX_CM_PER_L3S_CDOFFS,
	.flags		  = CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य *घड़ीकरोमुख्यs_am43xx[] __initdata = अणु
	&l4_cefuse_43xx_clkdm,
	&mpu_43xx_clkdm,
	&l4ls_43xx_clkdm,
	&tamper_43xx_clkdm,
	&l4_rtc_43xx_clkdm,
	&pruss_ocp_43xx_clkdm,
	&ocpwp_l3_43xx_clkdm,
	&l3s_tsc_43xx_clkdm,
	&lcdc_43xx_clkdm,
	&dss_43xx_clkdm,
	&l3_aon_43xx_clkdm,
	&emअगर_43xx_clkdm,
	&l4_wkup_aon_43xx_clkdm,
	&l3_43xx_clkdm,
	&l4_wkup_43xx_clkdm,
	&cpsw_125mhz_43xx_clkdm,
	&gfx_l3_43xx_clkdm,
	&l3s_43xx_clkdm,
	शून्य
पूर्ण;

व्योम __init am43xx_घड़ीकरोमुख्यs_init(व्योम)
अणु
	clkdm_रेजिस्टर_platक्रमm_funcs(&am43xx_clkdm_operations);
	clkdm_रेजिस्टर_clkdms(घड़ीकरोमुख्यs_am43xx);
	clkdm_complete_init();
पूर्ण
