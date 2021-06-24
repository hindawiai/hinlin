<शैली गुरु>
/*
 * TI81XX Clock Doमुख्य data.
 *
 * Copyright (C) 2010 Texas Instruments, Inc. - https://www.ti.com/
 * Copyright (C) 2013 SKTB SKiT, http://www.skitlab.ru/
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

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_CLOCKDOMAINS_81XX_H
#घोषणा __ARCH_ARM_MACH_OMAP2_CLOCKDOMAINS_81XX_H

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>

#समावेश "clockdomain.h"
#समावेश "cm81xx.h"

/*
 * Note that 814x seems to have HWSUP_SWSUP क्रम many घड़ीकरोमुख्यs
 * जबतक 816x करोes not. According to the TRM, 816x only has HWSUP
 * क्रम ALWON_L3_FAST. Also note that the TI tree घड़ीकरोमुख्यs81xx.h
 * seems to have the related अगरdef the wrong way around claiming
 * 816x supports HWSUP जबतक 814x करोes not. For now, we only set
 * HWSUP क्रम ALWON_L3_FAST as that seems to be supported क्रम both
 * dm814x and dm816x.
 */

/* Common क्रम 81xx */

अटल काष्ठा घड़ीकरोमुख्य alwon_l3_slow_81xx_clkdm = अणु
	.name		= "alwon_l3s_clkdm",
	.pwrdm		= अणु .name = "alwon_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_ALWON_MOD,
	.clkdm_offs	= TI81XX_CM_ALWON_L3_SLOW_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य alwon_l3_med_81xx_clkdm = अणु
	.name		= "alwon_l3_med_clkdm",
	.pwrdm		= अणु .name = "alwon_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_ALWON_MOD,
	.clkdm_offs	= TI81XX_CM_ALWON_L3_MED_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य alwon_l3_fast_81xx_clkdm = अणु
	.name		= "alwon_l3_fast_clkdm",
	.pwrdm		= अणु .name = "alwon_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_ALWON_MOD,
	.clkdm_offs	= TI81XX_CM_ALWON_L3_FAST_CLKDM,
	.flags		= CLKDM_CAN_HWSUP_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य alwon_ethernet_81xx_clkdm = अणु
	.name		= "alwon_ethernet_clkdm",
	.pwrdm		= अणु .name = "alwon_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_ALWON_MOD,
	.clkdm_offs	= TI81XX_CM_ETHERNET_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य mmu_81xx_clkdm = अणु
	.name		= "mmu_clkdm",
	.pwrdm		= अणु .name = "alwon_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_ALWON_MOD,
	.clkdm_offs	= TI81XX_CM_MMU_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य mmu_cfg_81xx_clkdm = अणु
	.name		= "mmu_cfg_clkdm",
	.pwrdm		= अणु .name = "alwon_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_ALWON_MOD,
	.clkdm_offs	= TI81XX_CM_MMUCFG_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य शेष_l3_slow_81xx_clkdm = अणु
	.name		= "default_l3_slow_clkdm",
	.pwrdm		= अणु .name = "default_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_DEFAULT_MOD,
	.clkdm_offs	= TI816X_CM_DEFAULT_L3_SLOW_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य शेष_sata_81xx_clkdm = अणु
	.name		= "default_clkdm",
	.pwrdm		= अणु .name = "default_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_DEFAULT_MOD,
	.clkdm_offs	= TI816X_CM_DEFAULT_SATA_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

/* 816x only */

अटल काष्ठा घड़ीकरोमुख्य alwon_mpu_816x_clkdm = अणु
	.name		= "alwon_mpu_clkdm",
	.pwrdm		= अणु .name = "alwon_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_ALWON_MOD,
	.clkdm_offs	= TI81XX_CM_ALWON_MPU_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य active_gem_816x_clkdm = अणु
	.name		= "active_gem_clkdm",
	.pwrdm		= अणु .name = "active_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_ACTIVE_MOD,
	.clkdm_offs	= TI816X_CM_ACTIVE_GEM_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य ivahd0_816x_clkdm = अणु
	.name		= "ivahd0_clkdm",
	.pwrdm		= अणु .name = "ivahd0_pwrdm" पूर्ण,
	.cm_inst	= TI816X_CM_IVAHD0_MOD,
	.clkdm_offs	= TI816X_CM_IVAHD0_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य ivahd1_816x_clkdm = अणु
	.name		= "ivahd1_clkdm",
	.pwrdm		= अणु .name = "ivahd1_pwrdm" पूर्ण,
	.cm_inst	= TI816X_CM_IVAHD1_MOD,
	.clkdm_offs	= TI816X_CM_IVAHD1_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य ivahd2_816x_clkdm = अणु
	.name		= "ivahd2_clkdm",
	.pwrdm		= अणु .name = "ivahd2_pwrdm" पूर्ण,
	.cm_inst	= TI816X_CM_IVAHD2_MOD,
	.clkdm_offs	= TI816X_CM_IVAHD2_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य sgx_816x_clkdm = अणु
	.name		= "sgx_clkdm",
	.pwrdm		= अणु .name = "sgx_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_SGX_MOD,
	.clkdm_offs	= TI816X_CM_SGX_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य शेष_l3_med_816x_clkdm = अणु
	.name		= "default_l3_med_clkdm",
	.pwrdm		= अणु .name = "default_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_DEFAULT_MOD,
	.clkdm_offs	= TI816X_CM_DEFAULT_L3_MED_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य शेष_ducati_816x_clkdm = अणु
	.name		= "default_ducati_clkdm",
	.pwrdm		= अणु .name = "default_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_DEFAULT_MOD,
	.clkdm_offs	= TI816X_CM_DEFAULT_DUCATI_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य शेष_pci_816x_clkdm = अणु
	.name		= "default_pci_clkdm",
	.pwrdm		= अणु .name = "default_pwrdm" पूर्ण,
	.cm_inst	= TI81XX_CM_DEFAULT_MOD,
	.clkdm_offs	= TI816X_CM_DEFAULT_PCI_CLKDM,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य *घड़ीकरोमुख्यs_ti814x[] __initdata = अणु
	&alwon_l3_slow_81xx_clkdm,
	&alwon_l3_med_81xx_clkdm,
	&alwon_l3_fast_81xx_clkdm,
	&alwon_ethernet_81xx_clkdm,
	&mmu_81xx_clkdm,
	&mmu_cfg_81xx_clkdm,
	&शेष_l3_slow_81xx_clkdm,
	&शेष_sata_81xx_clkdm,
	शून्य,
पूर्ण;

व्योम __init ti814x_घड़ीकरोमुख्यs_init(व्योम)
अणु
	clkdm_रेजिस्टर_platक्रमm_funcs(&am33xx_clkdm_operations);
	clkdm_रेजिस्टर_clkdms(घड़ीकरोमुख्यs_ti814x);
	clkdm_complete_init();
पूर्ण

अटल काष्ठा घड़ीकरोमुख्य *घड़ीकरोमुख्यs_ti816x[] __initdata = अणु
	&alwon_mpu_816x_clkdm,
	&alwon_l3_slow_81xx_clkdm,
	&alwon_l3_med_81xx_clkdm,
	&alwon_l3_fast_81xx_clkdm,
	&alwon_ethernet_81xx_clkdm,
	&mmu_81xx_clkdm,
	&mmu_cfg_81xx_clkdm,
	&active_gem_816x_clkdm,
	&ivahd0_816x_clkdm,
	&ivahd1_816x_clkdm,
	&ivahd2_816x_clkdm,
	&sgx_816x_clkdm,
	&शेष_l3_med_816x_clkdm,
	&शेष_ducati_816x_clkdm,
	&शेष_pci_816x_clkdm,
	&शेष_l3_slow_81xx_clkdm,
	&शेष_sata_81xx_clkdm,
	शून्य,
पूर्ण;

व्योम __init ti816x_घड़ीकरोमुख्यs_init(व्योम)
अणु
	clkdm_रेजिस्टर_platक्रमm_funcs(&am33xx_clkdm_operations);
	clkdm_रेजिस्टर_clkdms(घड़ीकरोमुख्यs_ti816x);
	clkdm_complete_init();
पूर्ण
#पूर्ण_अगर
