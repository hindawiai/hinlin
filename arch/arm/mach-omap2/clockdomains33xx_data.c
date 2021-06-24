<शैली गुरु>
/*
 * AM33XX Clock Doमुख्य data.
 *
 * Copyright (C) 2011-2012 Texas Instruments Incorporated - https://www.ti.com/
 * Vaibhav Hiremath <hvaibhav@ti.com>
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
#समावेश <linux/पन.स>

#समावेश "clockdomain.h"
#समावेश "cm.h"
#समावेश "cm33xx.h"
#समावेश "cm-regbits-33xx.h"

अटल काष्ठा घड़ीकरोमुख्य l4ls_am33xx_clkdm = अणु
	.name		= "l4ls_clkdm",
	.pwrdm		= अणु .name = "per_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_PER_MOD,
	.clkdm_offs	= AM33XX_CM_PER_L4LS_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3s_am33xx_clkdm = अणु
	.name		= "l3s_clkdm",
	.pwrdm		= अणु .name = "per_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_PER_MOD,
	.clkdm_offs	= AM33XX_CM_PER_L3S_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4fw_am33xx_clkdm = अणु
	.name		= "l4fw_clkdm",
	.pwrdm		= अणु .name = "per_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_PER_MOD,
	.clkdm_offs	= AM33XX_CM_PER_L4FW_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3_am33xx_clkdm = अणु
	.name		= "l3_clkdm",
	.pwrdm		= अणु .name = "per_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_PER_MOD,
	.clkdm_offs	= AM33XX_CM_PER_L3_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4hs_am33xx_clkdm = अणु
	.name		= "l4hs_clkdm",
	.pwrdm		= अणु .name = "per_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_PER_MOD,
	.clkdm_offs	= AM33XX_CM_PER_L4HS_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य ocpwp_l3_am33xx_clkdm = अणु
	.name		= "ocpwp_l3_clkdm",
	.pwrdm		= अणु .name = "per_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_PER_MOD,
	.clkdm_offs	= AM33XX_CM_PER_OCPWP_L3_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य pruss_ocp_am33xx_clkdm = अणु
	.name		= "pruss_ocp_clkdm",
	.pwrdm		= अणु .name = "per_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_PER_MOD,
	.clkdm_offs	= AM33XX_CM_PER_PRUSS_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य cpsw_125mhz_am33xx_clkdm = अणु
	.name		= "cpsw_125mhz_clkdm",
	.pwrdm		= अणु .name = "per_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_PER_MOD,
	.clkdm_offs	= AM33XX_CM_PER_CPSW_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य lcdc_am33xx_clkdm = अणु
	.name		= "lcdc_clkdm",
	.pwrdm		= अणु .name = "per_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_PER_MOD,
	.clkdm_offs	= AM33XX_CM_PER_LCDC_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य clk_24mhz_am33xx_clkdm = अणु
	.name		= "clk_24mhz_clkdm",
	.pwrdm		= अणु .name = "per_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_PER_MOD,
	.clkdm_offs	= AM33XX_CM_PER_CLK_24MHZ_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4_wkup_am33xx_clkdm = अणु
	.name		= "l4_wkup_clkdm",
	.pwrdm		= अणु .name = "wkup_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_WKUP_MOD,
	.clkdm_offs	= AM33XX_CM_WKUP_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l3_aon_am33xx_clkdm = अणु
	.name		= "l3_aon_clkdm",
	.pwrdm		= अणु .name = "wkup_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_WKUP_MOD,
	.clkdm_offs	= AM33XX_CM_L3_AON_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4_wkup_aon_am33xx_clkdm = अणु
	.name		= "l4_wkup_aon_clkdm",
	.pwrdm		= अणु .name = "wkup_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_WKUP_MOD,
	.clkdm_offs	= AM33XX_CM_L4_WKUP_AON_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य mpu_am33xx_clkdm = अणु
	.name		= "mpu_clkdm",
	.pwrdm		= अणु .name = "mpu_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_MPU_MOD,
	.clkdm_offs	= AM33XX_CM_MPU_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4_rtc_am33xx_clkdm = अणु
	.name		= "l4_rtc_clkdm",
	.pwrdm		= अणु .name = "rtc_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_RTC_MOD,
	.clkdm_offs	= AM33XX_CM_RTC_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य gfx_l3_am33xx_clkdm = अणु
	.name		= "gfx_l3_clkdm",
	.pwrdm		= अणु .name = "gfx_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_GFX_MOD,
	.clkdm_offs	= AM33XX_CM_GFX_L3_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य gfx_l4ls_gfx_am33xx_clkdm = अणु
	.name		= "gfx_l4ls_gfx_clkdm",
	.pwrdm		= अणु .name = "gfx_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_GFX_MOD,
	.clkdm_offs	= AM33XX_CM_GFX_L4LS_GFX_CLKSTCTRL__1_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य l4_cefuse_am33xx_clkdm = अणु
	.name		= "l4_cefuse_clkdm",
	.pwrdm		= अणु .name = "cefuse_pwrdm" पूर्ण,
	.cm_inst	= AM33XX_CM_CEFUSE_MOD,
	.clkdm_offs	= AM33XX_CM_CEFUSE_CLKSTCTRL_OFFSET,
	.flags		= CLKDM_CAN_SWSUP,
पूर्ण;

अटल काष्ठा घड़ीकरोमुख्य *घड़ीकरोमुख्यs_am33xx[] __initdata = अणु
	&l4ls_am33xx_clkdm,
	&l3s_am33xx_clkdm,
	&l4fw_am33xx_clkdm,
	&l3_am33xx_clkdm,
	&l4hs_am33xx_clkdm,
	&ocpwp_l3_am33xx_clkdm,
	&pruss_ocp_am33xx_clkdm,
	&cpsw_125mhz_am33xx_clkdm,
	&lcdc_am33xx_clkdm,
	&clk_24mhz_am33xx_clkdm,
	&l4_wkup_am33xx_clkdm,
	&l3_aon_am33xx_clkdm,
	&l4_wkup_aon_am33xx_clkdm,
	&mpu_am33xx_clkdm,
	&l4_rtc_am33xx_clkdm,
	&gfx_l3_am33xx_clkdm,
	&gfx_l4ls_gfx_am33xx_clkdm,
	&l4_cefuse_am33xx_clkdm,
	शून्य,
पूर्ण;

व्योम __init am33xx_घड़ीकरोमुख्यs_init(व्योम)
अणु
	clkdm_रेजिस्टर_platक्रमm_funcs(&am33xx_clkdm_operations);
	clkdm_रेजिस्टर_clkdms(घड़ीकरोमुख्यs_am33xx);
	clkdm_complete_init();
पूर्ण
