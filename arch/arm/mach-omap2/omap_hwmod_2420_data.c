<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap_hwmod_2420_data.c - hardware modules present on the OMAP2420 chips
 *
 * Copyright (C) 2009-2011 Nokia Corporation
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Paul Walmsley
 *
 * XXX handle crossbar/shared link dअगरference क्रम L3?
 * XXX these should be marked initdata क्रम multi-OMAP kernels
 */

#समावेश <linux/platक्रमm_data/i2c-omap.h>

#समावेश "omap_hwmod.h"
#समावेश "l3_2xxx.h"
#समावेश "l4_2xxx.h"

#समावेश "omap_hwmod_common_data.h"

#समावेश "cm-regbits-24xx.h"
#समावेश "prm-regbits-24xx.h"
#समावेश "i2c.h"
#समावेश "mmc.h"
#समावेश "serial.h"
#समावेश "wd_timer.h"

/*
 * OMAP2420 hardware module पूर्णांकegration data
 *
 * All of the data in this section should be स्वतःgeneratable from the
 * TI hardware database or other technical करोcumentation.  Data that
 * is driver-specअगरic or driver-kernel पूर्णांकegration-specअगरic beदीर्घs
 * अन्यथाwhere.
 */

/*
 * IP blocks
 */

/* IVA1 (IVA1) */
अटल काष्ठा omap_hwmod_class iva1_hwmod_class = अणु
	.name		= "iva1",
पूर्ण;

अटल काष्ठा omap_hwmod_rst_info omap2420_iva_resets[] = अणु
	अणु .name = "iva", .rst_shअगरt = 8 पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap2420_iva_hwmod = अणु
	.name		= "iva",
	.class		= &iva1_hwmod_class,
	.clkdm_name	= "iva1_clkdm",
	.rst_lines	= omap2420_iva_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap2420_iva_resets),
	.मुख्य_clk	= "iva1_ifck",
पूर्ण;

/* DSP */
अटल काष्ठा omap_hwmod_class dsp_hwmod_class = अणु
	.name		= "dsp",
पूर्ण;

अटल काष्ठा omap_hwmod_rst_info omap2420_dsp_resets[] = अणु
	अणु .name = "logic", .rst_shअगरt = 0 पूर्ण,
	अणु .name = "mmu", .rst_shअगरt = 1 पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap2420_dsp_hwmod = अणु
	.name		= "dsp",
	.class		= &dsp_hwmod_class,
	.clkdm_name	= "dsp_clkdm",
	.rst_lines	= omap2420_dsp_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap2420_dsp_resets),
	.मुख्य_clk	= "dsp_fck",
पूर्ण;

/* I2C common */
अटल काष्ठा omap_hwmod_class_sysconfig i2c_sysc = अणु
	.rev_offs	= 0x00,
	.sysc_offs	= 0x20,
	.syss_offs	= 0x10,
	.sysc_flags	= (SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class i2c_class = अणु
	.name		= "i2c",
	.sysc		= &i2c_sysc,
	.reset		= &omap_i2c_reset,
पूर्ण;

/* I2C1 */
अटल काष्ठा omap_hwmod omap2420_i2c1_hwmod = अणु
	.name		= "i2c1",
	.मुख्य_clk	= "i2c1_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP2420_ST_I2C1_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &i2c_class,
	/*
	 * From mach-omap2/pm24xx.c: "Putting MPU पूर्णांकo the WFI state
	 * जबतक a transfer is active seems to cause the I2C block to
	 * समयout. Why? Good question."
	 */
	.flags		= (HWMOD_16BIT_REG | HWMOD_BLOCK_WFI),
पूर्ण;

/* I2C2 */
अटल काष्ठा omap_hwmod omap2420_i2c2_hwmod = अणु
	.name		= "i2c2",
	.मुख्य_clk	= "i2c2_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP2420_ST_I2C2_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &i2c_class,
	.flags		= HWMOD_16BIT_REG,
पूर्ण;

/* mailbox */
अटल काष्ठा omap_hwmod omap2420_mailbox_hwmod = अणु
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

/*
 * 'mcbsp' class
 * multi channel buffered serial port controller
 */

अटल काष्ठा omap_hwmod_class omap2420_mcbsp_hwmod_class = अणु
	.name = "mcbsp",
पूर्ण;

अटल काष्ठा omap_hwmod_opt_clk mcbsp_opt_clks[] = अणु
	अणु .role = "pad_fck", .clk = "mcbsp_clks" पूर्ण,
	अणु .role = "prcm_fck", .clk = "func_96m_ck" पूर्ण,
पूर्ण;

/* mcbsp1 */
अटल काष्ठा omap_hwmod omap2420_mcbsp1_hwmod = अणु
	.name		= "mcbsp1",
	.class		= &omap2420_mcbsp_hwmod_class,
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
अटल काष्ठा omap_hwmod omap2420_mcbsp2_hwmod = अणु
	.name		= "mcbsp2",
	.class		= &omap2420_mcbsp_hwmod_class,
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

अटल काष्ठा omap_hwmod_class_sysconfig omap2420_msdi_sysc = अणु
	.rev_offs	= 0x3c,
	.sysc_offs	= 0x64,
	.syss_offs	= 0x68,
	.sysc_flags	= (SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap2420_msdi_hwmod_class = अणु
	.name	= "msdi",
	.sysc	= &omap2420_msdi_sysc,
	.reset	= &omap_msdi_reset,
पूर्ण;

/* msdi1 */
अटल काष्ठा omap_hwmod omap2420_msdi1_hwmod = अणु
	.name		= "msdi1",
	.class		= &omap2420_msdi_hwmod_class,
	.मुख्य_clk	= "mmc_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP2420_ST_MMC_SHIFT,
		पूर्ण,
	पूर्ण,
	.flags		= HWMOD_16BIT_REG,
पूर्ण;

/* HDQ1W/1-wire */
अटल काष्ठा omap_hwmod omap2420_hdq1w_hwmod = अणु
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

/* L4 CORE -> I2C1 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l4_core__i2c1 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2420_i2c1_hwmod,
	.clk		= "i2c1_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 CORE -> I2C2 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l4_core__i2c2 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2420_i2c2_hwmod,
	.clk		= "i2c2_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* IVA <- L3 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l3__iva = अणु
	.master		= &omap2xxx_l3_मुख्य_hwmod,
	.slave		= &omap2420_iva_hwmod,
	.clk		= "core_l3_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* DSP <- L3 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l3__dsp = अणु
	.master		= &omap2xxx_l3_मुख्य_hwmod,
	.slave		= &omap2420_dsp_hwmod,
	.clk		= "dsp_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_wkup -> wd_समयr2 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l4_wkup__wd_समयr2 = अणु
	.master		= &omap2xxx_l4_wkup_hwmod,
	.slave		= &omap2xxx_wd_समयr2_hwmod,
	.clk		= "mpu_wdt_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_wkup -> gpio1 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l4_wkup__gpio1 = अणु
	.master		= &omap2xxx_l4_wkup_hwmod,
	.slave		= &omap2xxx_gpio1_hwmod,
	.clk		= "gpios_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_wkup -> gpio2 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l4_wkup__gpio2 = अणु
	.master		= &omap2xxx_l4_wkup_hwmod,
	.slave		= &omap2xxx_gpio2_hwmod,
	.clk		= "gpios_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_wkup -> gpio3 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l4_wkup__gpio3 = अणु
	.master		= &omap2xxx_l4_wkup_hwmod,
	.slave		= &omap2xxx_gpio3_hwmod,
	.clk		= "gpios_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_wkup -> gpio4 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l4_wkup__gpio4 = अणु
	.master		= &omap2xxx_l4_wkup_hwmod,
	.slave		= &omap2xxx_gpio4_hwmod,
	.clk		= "gpios_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> mailbox */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l4_core__mailbox = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2420_mailbox_hwmod,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> mcbsp1 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l4_core__mcbsp1 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2420_mcbsp1_hwmod,
	.clk		= "mcbsp1_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> mcbsp2 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l4_core__mcbsp2 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2420_mcbsp2_hwmod,
	.clk		= "mcbsp2_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> msdi1 */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l4_core__msdi1 = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2420_msdi1_hwmod,
	.clk		= "mmc_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> hdq1w पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l4_core__hdq1w = अणु
	.master		= &omap2xxx_l4_core_hwmod,
	.slave		= &omap2420_hdq1w_hwmod,
	.clk		= "hdq_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
	.flags		= OMAP_FIREWALL_L4 | OCPIF_SWSUP_IDLE,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर omap2420_l3__gpmc = अणु
	.master		= &omap2xxx_l3_मुख्य_hwmod,
	.slave		= &omap2xxx_gpmc_hwmod,
	.clk		= "core_l3_ck",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर *omap2420_hwmod_ocp_अगरs[] __initdata = अणु
	&omap2xxx_l3_मुख्य__l4_core,
	&omap2xxx_mpu__l3_मुख्य,
	&omap2xxx_dss__l3,
	&omap2xxx_l4_core__mcspi1,
	&omap2xxx_l4_core__mcspi2,
	&omap2xxx_l4_core__l4_wkup,
	&omap2_l4_core__uart1,
	&omap2_l4_core__uart2,
	&omap2_l4_core__uart3,
	&omap2420_l4_core__i2c1,
	&omap2420_l4_core__i2c2,
	&omap2420_l3__iva,
	&omap2420_l3__dsp,
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
	&omap2420_l4_wkup__wd_समयr2,
	&omap2xxx_l4_core__dss,
	&omap2xxx_l4_core__dss_dispc,
	&omap2xxx_l4_core__dss_rfbi,
	&omap2xxx_l4_core__dss_venc,
	&omap2420_l4_wkup__gpio1,
	&omap2420_l4_wkup__gpio2,
	&omap2420_l4_wkup__gpio3,
	&omap2420_l4_wkup__gpio4,
	&omap2420_l4_core__mailbox,
	&omap2420_l4_core__mcbsp1,
	&omap2420_l4_core__mcbsp2,
	&omap2420_l4_core__msdi1,
	&omap2xxx_l4_core__rng,
	&omap2xxx_l4_core__sham,
	&omap2xxx_l4_core__aes,
	&omap2420_l4_core__hdq1w,
	&omap2420_l3__gpmc,
	शून्य,
पूर्ण;

पूर्णांक __init omap2420_hwmod_init(व्योम)
अणु
	omap_hwmod_init();
	वापस omap_hwmod_रेजिस्टर_links(omap2420_hwmod_ocp_अगरs);
पूर्ण
