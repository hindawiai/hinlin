<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap_hwmod_2430_data.c - hardware modules present on the OMAP2430 chips
 *
 * Copyright (C) 2009-2011 Nokia Corporation
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Paul Walmsley
 *
 * XXX handle crossbar/shared link dअगरference क्रम L3?
 * XXX these should be marked initdata क्रम multi-OMAP kernels
 */

#समावेश <linux/platक्रमm_data/i2c-omap.h>
#समावेश <linux/platक्रमm_data/hsmmc-omap.h>

#समावेश "omap_hwmod.h"
#समावेश "l3_2xxx.h"

#समावेश "soc.h"
#समावेश "omap_hwmod_common_data.h"
#समावेश "prm-regbits-24xx.h"
#समावेश "cm-regbits-24xx.h"
#समावेश "i2c.h"
#समावेश "wd_timer.h"

/*
 * OMAP2430 hardware module पूर्णांकegration data
 *
 * All of the data in this section should be स्वतःgeneratable from the
 * TI hardware database or other technical करोcumentation.  Data that
 * is driver-specअगरic or driver-kernel पूर्णांकegration-specअगरic beदीर्घs
 * अन्यथाwhere.
 */

/*
 * IP blocks
 */

/* IVA2 (IVA2) */
अटल काष्ठा omap_hwmod_rst_info omap2430_iva_resets[] = अणु
	अणु .name = "logic", .rst_shअगरt = 0 पूर्ण,
	अणु .name = "mmu", .rst_shअगरt = 1 पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap2430_iva_hwmod = अणु
	.name		= "iva",
	.class		= &iva_hwmod_class,
	.clkdm_name	= "dsp_clkdm",
	.rst_lines	= omap2430_iva_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap2430_iva_resets),
	.मुख्य_clk	= "dsp_fck",
पूर्ण;

/* I2C common */
अटल काष्ठा omap_hwmod_class_sysconfig i2c_sysc = अणु
	.rev_offs	= 0x00,
	.sysc_offs	= 0x20,
	.syss_offs	= 0x10,
	.sysc_flags	= (SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE |
			   SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class i2c_class = अणु
	.name		= "i2c",
	.sysc		= &i2c_sysc,
	.reset		= &omap_i2c_reset,
पूर्ण;

/* I2C1 */
अटल काष्ठा omap_hwmod omap2430_i2c1_hwmod = अणु
	.name		= "i2c1",
	.flags		= HWMOD_16BIT_REG,
	.मुख्य_clk	= "i2chs1_fck",
	.prcm		= अणु
		.omap2 = अणु
			/*
			 * NOTE: The CM_FCLKEN* and CM_ICLKEN* क्रम
			 * I2CHS IP's करो not follow the usual pattern.
			 * prcm_reg_id alone cannot be used to program
			 * the iclk and fclk. Needs to be handled using
			 * additional flags when clk handling is moved
			 * to hwmod framework.
			 */
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP2430_ST_I2CHS1_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &i2c_class,
पूर्ण;

/* I2C2 */
अटल काष्ठा omap_hwmod omap2430_i2c2_hwmod = अणु
	.name		= "i2c2",
	.flags		= HWMOD_16BIT_REG,
	.मुख्य_clk	= "i2chs2_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP2430_ST_I2CHS2_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &i2c_class,
पूर्ण;

/* gpio5 */
अटल काष्ठा omap_hwmod omap2430_gpio5_hwmod = अणु
	.name		= "gpio5",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.मुख्य_clk	= "gpio5_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 2,
			.idlest_idle_bit = OMAP2430_ST_GPIO5_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_gpio_hwmod_class,
पूर्ण;

/* mailbox */
अटल काष्ठा omap_hwmod omap2430_mailbox_hwmod = अणु
	.name		= "mailbox",
	.class		= &omap2xxx_mailbox_hwmod_class,
	.मुख्य_clk	= "mailboxes_ick",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_MAILBOXES_SHIFT,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* mcspi3 */
अटल काष्ठा omap_hwmod omap2430_mcspi3_hwmod = अणु
	.name		= "mcspi3",
	.मुख्य_clk	= "mcspi3_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 2,
			.idlest_idle_bit = OMAP2430_ST_MCSPI3_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_mcspi_class,
पूर्ण;

/* usbhsotg */
अटल काष्ठा omap_hwmod_class_sysconfig omap2430_usbhsotg_sysc = अणु
	.rev_offs	= 0x0400,
	.sysc_offs	= 0x0404,
	.syss_offs	= 0x0408,
	.sysc_flags	= (SYSC_HAS_SIDLEMODE | SYSC_HAS_MIDLEMODE|
			  SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			  SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			  MSTANDBY_FORCE | MSTANDBY_NO | MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class usbotg_class = अणु
	.name = "usbotg",
	.sysc = &omap2430_usbhsotg_sysc,
पूर्ण;

/* usb_otg_hs */
अटल काष्ठा omap_hwmod omap2430_usbhsotg_hwmod = अणु
	.name		= "usb_otg_hs",
	.मुख्य_clk	= "usbhs_ick",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP2430_ST_USBHS_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &usbotg_class,
	/*
	 * Erratum ID: i479  idle_req / idle_ack mechanism potentially
	 * broken when स्वतःidle is enabled
	 * workaround is to disable the स्वतःidle bit at module level.
	 */
	.flags		= HWMOD_NO_OCP_AUTOIDLE | HWMOD_SWSUP_SIDLE
				| HWMOD_SWSUP_MSTANDBY,
पूर्ण;

/*
 * 'mcbsp' class
 * multi channel buffered serial port controller
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap2430_mcbsp_sysc = अणु
	.rev_offs	= 0x007C,
	.sysc_offs	= 0x008C,
	.sysc_flags	= (SYSC_HAS_SOFTRESET),
	.sysc_fields    = &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap2430_mcbsp_hwmod_class = अणु
	.name = "mcbsp",
	.sysc = &omap2430_mcbsp_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod_opt_clk mcbsp_opt_clks[] = अणु
	अणु .role = "pad_fck", .clk = "mcbsp_clks" पूर्ण,
	अणु .role = "prcm_fck", .clk = "func_96m_ck" पूर्ण,
पूर्ण;

/* mcbsp1 */
अटल काष्ठा omap_hwmod omap2430_mcbsp1_hwmod = अणु
	.name		= "mcbsp1",
	.class		= &omap2430_mcbsp_hwmod_class,
	.मुख्य_clk	= "mcbsp1_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_MCBSP1_SHIFT,
		पूर्ण,
	पूर्ण,
	.opt_clks	= mcbsp_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp_opt_clks),
पूर्ण;

/* mcbsp2 */
अटल काष्ठा omap_hwmod omap2430_mcbsp2_hwmod = अणु
	.name		= "mcbsp2",
	.class		= &omap2430_mcbsp_hwmod_class,
	.मुख्य_clk	= "mcbsp2_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_MCBSP2_SHIFT,
		पूर्ण,
	पूर्ण,
	.opt_clks	= mcbsp_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp_opt_clks),
पूर्ण;

/* mcbsp3 */
अटल काष्ठा omap_hwmod omap2430_mcbsp3_hwmod = अणु
	.name		= "mcbsp3",
	.class		= &omap2430_mcbsp_hwmod_class,
	.मुख्य_clk	= "mcbsp3_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 2,
			.idlest_idle_bit = OMAP2430_ST_MCBSP3_SHIFT,
		पूर्ण,
	पूर्ण,
	.opt_clks	= mcbsp_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp_opt_clks),
पूर्ण;

/* mcbsp4 */
अटल काष्ठा omap_hwmod omap2430_mcbsp4_hwmod = अणु
	.name		= "mcbsp4",
	.class		= &omap2430_mcbsp_hwmod_class,
	.मुख्य_clk	= "mcbsp4_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 2,
			.idlest_idle_bit = OMAP2430_ST_MCBSP4_SHIFT,
		पूर्ण,
	पूर्ण,
	.opt_clks	= mcbsp_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp_opt_clks),
पूर्ण;

/* mcbsp5 */
अटल काष्ठा omap_hwmod omap2430_mcbsp5_hwmod = अणु
	.name		= "mcbsp5",
	.class		= &omap2430_mcbsp_hwmod_class,
	.मुख्य_clk	= "mcbsp5_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 2,
			.idlest_idle_bit = OMAP2430_ST_MCBSP5_SHIFT,
		पूर्ण,
	पूर्ण,
	.opt_clks	= mcbsp_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp_opt_clks),
पूर्ण;

/* MMC/SD/SDIO common */
अटल काष्ठा omap_hwmod_class_sysconfig omap2430_mmc_sysc = अणु
	.rev_offs	= 0x1fc,
	.sysc_offs	= 0x10,
	.syss_offs	= 0x14,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields    = &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap2430_mmc_class = अणु
	.name = "mmc",
	.sysc = &omap2430_mmc_sysc,
पूर्ण;

/* MMC/SD/SDIO1 */
अटल काष्ठा omap_hwmod_opt_clk omap2430_mmc1_opt_clks[] = अणु
	अणु .role = "dbck", .clk = "mmchsdb1_fck" पूर्ण,
पूर्ण;

अटल काष्ठा omap_hsmmc_dev_attr mmc1_dev_attr = अणु
	.flags = OMAP_HSMMC_SUPPORTS_DUAL_VOLT,
पूर्ण;

अटल काष्ठा omap_hwmod omap2430_mmc1_hwmod = अणु
	.name		= "mmc1",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.opt_clks	= omap2430_mmc1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(omap2430_mmc1_opt_clks),
	.मुख्य_clk	= "mmchs1_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 2,
			.idlest_idle_bit = OMAP2430_ST_MMCHS1_SHIFT,
		पूर्ण,
	पूर्ण,
	.dev_attr	= &mmc1_dev_attr,
	.class		= &omap2430_mmc_class,
पूर्ण;

/* MMC/SD/SDIO2 */
अटल काष्ठा omap_hwmod_opt_clk omap2430_mmc2_opt_clks[] = अणु
	अणु .role = "dbck", .clk = "mmchsdb2_fck" पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap2430_mmc2_hwmod = अणु
	.name		= "mmc2",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.opt_clks	= omap2430_mmc2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(omap2430_mmc2_opt_clks),
	.मुख्य_clk	= "mmchs2_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 2,
			.idlest_idle_bit = OMAP2430_ST_MMCHS2_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2430_mmc_class,
पूर्ण;

/* HDQ1W/1-wire */
अटल काष्ठा omap_hwmod omap2430_hdq1w_hwmod = अणु
	.name		= "hdq1w",
	.मुख्य_clk	= "hdq_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_HDQ_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2_hdq1w_class,
पूर्ण;

/*
 * पूर्णांकerfaces
 */

/* L3 -> L4_CORE पूर्णांकerface */
/* l3_core -> usbhsotg  पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_usbhsotg__l3 = अणु
	.master		= &omap2430_usbhsotg_hwmod,
	.slave		= &omap2xxx_l3_मुख्य_hwmod,
	.clk		= "core_l3_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

/* L4 CORE -> I2C1 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__i2c1 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_i2c1_hwmod,
	.clk		= "i2c1_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 CORE -> I2C2 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__i2c2 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_i2c2_hwmod,
	.clk		= "i2c2_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/*  l4_core ->usbhsotg  पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__usbhsotg = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_usbhsotg_hwmod,
	.clk		= "usb_l4_ick",
	.user		= OCP_USER_MPU,
पूर्ण;

/* L4 CORE -> MMC1 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__mmc1 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_mmc1_hwmod,
	.clk		= "mmchs1_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 CORE -> MMC2 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__mmc2 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_mmc2_hwmod,
	.clk		= "mmchs2_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4 core -> mcspi3 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__mcspi3 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_mcspi3_hwmod,
	.clk		= "mcspi3_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* IVA2 <- L3 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l3__iva = अणु
	.master		= &omap2xxx_l3_मुख्य_hwmod,
	.slave		= &omap2430_iva_hwmod,
	.clk		= "core_l3_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_wkup -> wd_समयr2 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_wkup__wd_समयr2 = अणु
	.master		= &omap2xxx_l4_wkup_hwmod,
	.slave		= &omap2xxx_wd_समयr2_hwmod,
	.clk		= "mpu_wdt_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_wkup -> gpio1 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_wkup__gpio1 = अणु
	.master		= &omap2xxx_l4_wkup_hwmod,
	.slave		= &omap2xxx_gpio1_hwmod,
	.clk		= "gpios_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_wkup -> gpio2 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_wkup__gpio2 = अणु
	.master		= &omap2xxx_l4_wkup_hwmod,
	.slave		= &omap2xxx_gpio2_hwmod,
	.clk		= "gpios_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_wkup -> gpio3 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_wkup__gpio3 = अणु
	.master		= &omap2xxx_l4_wkup_hwmod,
	.slave		= &omap2xxx_gpio3_hwmod,
	.clk		= "gpios_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_wkup -> gpio4 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_wkup__gpio4 = अणु
	.master		= &omap2xxx_l4_wkup_hwmod,
	.slave		= &omap2xxx_gpio4_hwmod,
	.clk		= "gpios_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> gpio5 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__gpio5 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_gpio5_hwmod,
	.clk		= "gpio5_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> mailbox */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__mailbox = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_mailbox_hwmod,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> mcbsp1 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__mcbsp1 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_mcbsp1_hwmod,
	.clk		= "mcbsp1_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> mcbsp2 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__mcbsp2 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_mcbsp2_hwmod,
	.clk		= "mcbsp2_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> mcbsp3 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__mcbsp3 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_mcbsp3_hwmod,
	.clk		= "mcbsp3_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> mcbsp4 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__mcbsp4 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_mcbsp4_hwmod,
	.clk		= "mcbsp4_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> mcbsp5 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__mcbsp5 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_mcbsp5_hwmod,
	.clk		= "mcbsp5_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> hdq1w */
अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l4_core__hdq1w = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2430_hdq1w_hwmod,
	.clk		= "hdq_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
	.flags		= OMAP_FIREWALL_L4 | OCPIF_SWSUP_IDLE,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर omap2430_l3__gpmc = अणु
	.master		= &omap2xxx_l3_मुख्य_hwmod,
	.slave		= &omap2xxx_gpmc_hwmod,
	.clk		= "core_l3_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर *omap2430_hwmod_ocp_अगरs[] __initdata = अणु
	&omap2xxx_l3_मुख्य__l4_core,
	&omap2xxx_mpu__l3_मुख्य,
	&omap2xxx_dss__l3,
	&omap2430_usbhsotg__l3,
	&omap2430_l4_core__i2c1,
	&omap2430_l4_core__i2c2,
	&omap2xxx_l4_core__l4_wkup,
	&omap2_l4_core__uart1,
	&omap2_l4_core__uart2,
	&omap2_l4_core__uart3,
	&omap2430_l4_core__usbhsotg,
	&omap2430_l4_core__mmc1,
	&omap2430_l4_core__mmc2,
	&omap2xxx_l4_core__mcspi1,
	&omap2xxx_l4_core__mcspi2,
	&omap2430_l4_core__mcspi3,
	&omap2430_l3__iva,
	&omap2xxx_l4_core__समयr3,
	&omap2xxx_l4_core__समयr4,
	&omap2xxx_l4_core__समयr5,
	&omap2xxx_l4_core__समयr6,
	&omap2xxx_l4_core__समयr7,
	&omap2xxx_l4_core__समयr8,
	&omap2xxx_l4_core__समयr9,
	&omap2xxx_l4_core__समयr10,
	&omap2xxx_l4_core__समयr11,
	&omap2xxx_l4_core__समयr12,
	&omap2430_l4_wkup__wd_समयr2,
	&omap2xxx_l4_core__dss,
	&omap2xxx_l4_core__dss_dispc,
	&omap2xxx_l4_core__dss_rfbi,
	&omap2xxx_l4_core__dss_venc,
	&omap2430_l4_wkup__gpio1,
	&omap2430_l4_wkup__gpio2,
	&omap2430_l4_wkup__gpio3,
	&omap2430_l4_wkup__gpio4,
	&omap2430_l4_core__gpio5,
	&omap2430_l4_core__mailbox,
	&omap2430_l4_core__mcbsp1,
	&omap2430_l4_core__mcbsp2,
	&omap2430_l4_core__mcbsp3,
	&omap2430_l4_core__mcbsp4,
	&omap2430_l4_core__mcbsp5,
	&omap2430_l4_core__hdq1w,
	&omap2xxx_l4_core__rng,
	&omap2xxx_l4_core__sham,
	&omap2xxx_l4_core__aes,
	&omap2430_l3__gpmc,
	शून्य,
पूर्ण;

पूर्णांक __init omap2430_hwmod_init(व्योम)
अणु
	omap_hwmod_init();
	वापस omap_hwmod_रेजिस्टर_links(omap2430_hwmod_ocp_अगरs);
पूर्ण
