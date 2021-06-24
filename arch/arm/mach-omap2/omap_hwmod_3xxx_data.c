<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap_hwmod_3xxx_data.c - hardware modules present on the OMAP3xxx chips
 *
 * Copyright (C) 2009-2011 Nokia Corporation
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Paul Walmsley
 *
 * The data in this file should be completely स्वतःgeneratable from
 * the TI hardware database or other technical करोcumentation.
 *
 * XXX these should be marked initdata क्रम multi-OMAP kernels
 */

#समावेश <linux/platक्रमm_data/i2c-omap.h>
#समावेश <linux/घातer/smartreflex.h>
#समावेश <linux/platक्रमm_data/hsmmc-omap.h>

#समावेश "l3_3xxx.h"
#समावेश "l4_3xxx.h"

#समावेश "soc.h"
#समावेश "omap_hwmod.h"
#समावेश "omap_hwmod_common_data.h"
#समावेश "prm-regbits-34xx.h"
#समावेश "cm-regbits-34xx.h"

#समावेश "i2c.h"
#समावेश "wd_timer.h"
#समावेश "serial.h"

/*
 * OMAP3xxx hardware module पूर्णांकegration data
 *
 * All of the data in this section should be स्वतःgeneratable from the
 * TI hardware database or other technical करोcumentation.  Data that
 * is driver-specअगरic or driver-kernel पूर्णांकegration-specअगरic beदीर्घs
 * अन्यथाwhere.
 */

#घोषणा AM35XX_IPSS_USBOTGSS_BASE      0x5C040000

/*
 * IP blocks
 */

/* L3 */

अटल काष्ठा omap_hwmod omap3xxx_l3_मुख्य_hwmod = अणु
	.name		= "l3_main",
	.class		= &l3_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* L4 CORE */
अटल काष्ठा omap_hwmod omap3xxx_l4_core_hwmod = अणु
	.name		= "l4_core",
	.class		= &l4_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* L4 PER */
अटल काष्ठा omap_hwmod omap3xxx_l4_per_hwmod = अणु
	.name		= "l4_per",
	.class		= &l4_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* L4 WKUP */
अटल काष्ठा omap_hwmod omap3xxx_l4_wkup_hwmod = अणु
	.name		= "l4_wkup",
	.class		= &l4_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* L4 SEC */
अटल काष्ठा omap_hwmod omap3xxx_l4_sec_hwmod = अणु
	.name		= "l4_sec",
	.class		= &l4_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* MPU */

अटल काष्ठा omap_hwmod omap3xxx_mpu_hwmod = अणु
	.name		= "mpu",
	.class		= &mpu_hwmod_class,
	.मुख्य_clk	= "arm_fck",
पूर्ण;

/* IVA2 (IVA2) */
अटल काष्ठा omap_hwmod_rst_info omap3xxx_iva_resets[] = अणु
	अणु .name = "logic", .rst_shअगरt = 0, .st_shअगरt = 8 पूर्ण,
	अणु .name = "seq0", .rst_shअगरt = 1, .st_shअगरt = 9 पूर्ण,
	अणु .name = "seq1", .rst_shअगरt = 2, .st_shअगरt = 10 पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_iva_hwmod = अणु
	.name		= "iva",
	.class		= &iva_hwmod_class,
	.clkdm_name	= "iva2_clkdm",
	.rst_lines	= omap3xxx_iva_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap3xxx_iva_resets),
	.मुख्य_clk	= "iva2_ck",
	.prcm = अणु
		.omap2 = अणु
			.module_offs = OMAP3430_IVA2_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_IVA2_SHIFT,
		पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * 'debugss' class
 * debug and emulation sub प्रणाली
 */

अटल काष्ठा omap_hwmod_class omap3xxx_debugss_hwmod_class = अणु
	.name	= "debugss",
पूर्ण;

/* debugss */
अटल काष्ठा omap_hwmod omap3xxx_debugss_hwmod = अणु
	.name		= "debugss",
	.class		= &omap3xxx_debugss_hwmod_class,
	.clkdm_name	= "emu_clkdm",
	.मुख्य_clk	= "emu_src_ck",
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* समयr class */
अटल काष्ठा omap_hwmod_class_sysconfig omap3xxx_समयr_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_SIDLEMODE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_EMUFREE | SYSC_HAS_AUTOIDLE |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_समयr_hwmod_class = अणु
	.name = "timer",
	.sysc = &omap3xxx_समयr_sysc,
पूर्ण;

/* समयr3 */
अटल काष्ठा omap_hwmod omap3xxx_समयr3_hwmod = अणु
	.name		= "timer3",
	.मुख्य_clk	= "gpt3_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPT3_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_समयr_hwmod_class,
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr4 */
अटल काष्ठा omap_hwmod omap3xxx_समयr4_hwmod = अणु
	.name		= "timer4",
	.मुख्य_clk	= "gpt4_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPT4_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_समयr_hwmod_class,
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr5 */
अटल काष्ठा omap_hwmod omap3xxx_समयr5_hwmod = अणु
	.name		= "timer5",
	.मुख्य_clk	= "gpt5_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPT5_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_समयr_hwmod_class,
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr6 */
अटल काष्ठा omap_hwmod omap3xxx_समयr6_hwmod = अणु
	.name		= "timer6",
	.मुख्य_clk	= "gpt6_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPT6_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_समयr_hwmod_class,
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr7 */
अटल काष्ठा omap_hwmod omap3xxx_समयr7_hwmod = अणु
	.name		= "timer7",
	.मुख्य_clk	= "gpt7_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPT7_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_समयr_hwmod_class,
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr8 */
अटल काष्ठा omap_hwmod omap3xxx_समयr8_hwmod = अणु
	.name		= "timer8",
	.मुख्य_clk	= "gpt8_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPT8_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_समयr_hwmod_class,
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr9 */
अटल काष्ठा omap_hwmod omap3xxx_समयr9_hwmod = अणु
	.name		= "timer9",
	.मुख्य_clk	= "gpt9_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPT9_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_समयr_hwmod_class,
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr10 */
अटल काष्ठा omap_hwmod omap3xxx_समयr10_hwmod = अणु
	.name		= "timer10",
	.मुख्य_clk	= "gpt10_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPT10_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_समयr_hwmod_class,
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr11 */
अटल काष्ठा omap_hwmod omap3xxx_समयr11_hwmod = अणु
	.name		= "timer11",
	.मुख्य_clk	= "gpt11_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPT11_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_समयr_hwmod_class,
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/*
 * 'wd_timer' class
 * 32-bit watchकरोg upward counter that generates a pulse on the reset pin on
 * overflow condition
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap3xxx_wd_समयr_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_SIDLEMODE | SYSC_HAS_EMUFREE |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields    = &omap_hwmod_sysc_type1,
पूर्ण;

/* I2C common */
अटल काष्ठा omap_hwmod_class_sysconfig i2c_sysc = अणु
	.rev_offs	= 0x00,
	.sysc_offs	= 0x20,
	.syss_offs	= 0x10,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields    = &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_wd_समयr_hwmod_class = अणु
	.name		= "wd_timer",
	.sysc		= &omap3xxx_wd_समयr_sysc,
	.pre_shutकरोwn	= &omap2_wd_समयr_disable,
	.reset		= &omap2_wd_समयr_reset,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_wd_समयr2_hwmod = अणु
	.name		= "wd_timer2",
	.class		= &omap3xxx_wd_समयr_hwmod_class,
	.मुख्य_clk	= "wdt2_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = WKUP_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_WDT2_SHIFT,
		पूर्ण,
	पूर्ण,
	/*
	 * XXX: Use software supervised mode, HW supervised smartidle seems to
	 * block CORE घातer करोमुख्य idle transitions. Maybe a HW bug in wdt2?
	 */
	.flags		= HWMOD_SWSUP_SIDLE,
पूर्ण;

/* UART1 */
अटल काष्ठा omap_hwmod omap3xxx_uart1_hwmod = अणु
	.name		= "uart1",
	.मुख्य_clk	= "uart1_fck",
	.flags		= DEBUG_TI81XXUART1_FLAGS | HWMOD_SWSUP_SIDLE,
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_EN_UART1_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2_uart_class,
पूर्ण;

/* UART2 */
अटल काष्ठा omap_hwmod omap3xxx_uart2_hwmod = अणु
	.name		= "uart2",
	.मुख्य_clk	= "uart2_fck",
	.flags		= DEBUG_TI81XXUART2_FLAGS | HWMOD_SWSUP_SIDLE,
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_EN_UART2_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2_uart_class,
पूर्ण;

/* UART3 */
अटल काष्ठा omap_hwmod omap3xxx_uart3_hwmod = अणु
	.name		= "uart3",
	.मुख्य_clk	= "uart3_fck",
	.flags		= DEBUG_OMAP3UART3_FLAGS | DEBUG_TI81XXUART3_FLAGS |
				HWMOD_SWSUP_SIDLE,
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_EN_UART3_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2_uart_class,
पूर्ण;

/* UART4 */


अटल काष्ठा omap_hwmod omap36xx_uart4_hwmod = अणु
	.name		= "uart4",
	.मुख्य_clk	= "uart4_fck",
	.flags		= DEBUG_OMAP3UART4_FLAGS | HWMOD_SWSUP_SIDLE,
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3630_EN_UART4_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2_uart_class,
पूर्ण;



/*
 * XXX AM35xx UART4 cannot complete its softreset without uart1_fck or
 * uart2_fck being enabled.  So we add uart1_fck as an optional घड़ी,
 * below, and set the HWMOD_CONTROL_OPT_CLKS_IN_RESET.  This really
 * should not be needed.  The functional घड़ी काष्ठाure of the AM35xx
 * UART4 is extremely unclear and opaque; it is unclear what the role
 * of uart1/2_fck is क्रम the UART4.  Any clarअगरication from either
 * empirical testing or the AM3505/3517 hardware designers would be
 * most welcome.
 */
अटल काष्ठा omap_hwmod_opt_clk am35xx_uart4_opt_clks[] = अणु
	अणु .role = "softreset_uart1_fck", .clk = "uart1_fck" पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod am35xx_uart4_hwmod = अणु
	.name		= "uart4",
	.मुख्य_clk	= "uart4_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = AM35XX_ST_UART4_SHIFT,
		पूर्ण,
	पूर्ण,
	.opt_clks	= am35xx_uart4_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(am35xx_uart4_opt_clks),
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.class		= &omap2_uart_class,
पूर्ण;

अटल काष्ठा omap_hwmod_class i2c_class = अणु
	.name	= "i2c",
	.sysc	= &i2c_sysc,
	.reset	= &omap_i2c_reset,
पूर्ण;

/* dss */
अटल काष्ठा omap_hwmod_opt_clk dss_opt_clks[] = अणु
	/*
	 * The DSS HW needs all DSS घड़ीs enabled during reset. The dss_core
	 * driver करोes not use these घड़ीs.
	 */
	अणु .role = "sys_clk", .clk = "dss2_alwon_fck" पूर्ण,
	अणु .role = "tv_clk", .clk = "dss_tv_fck" पूर्ण,
	/* required only on OMAP3430 */
	अणु .role = "tv_dac_clk", .clk = "dss_96m_fck" पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap3430es1_dss_core_hwmod = अणु
	.name		= "dss_core",
	.class		= &omap2_dss_hwmod_class,
	.मुख्य_clk	= "dss1_alwon_fck", /* instead of dss_fck */
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_DSS_MOD,
			.idlest_reg_id = 1,
		पूर्ण,
	पूर्ण,
	.opt_clks	= dss_opt_clks,
	.opt_clks_cnt = ARRAY_SIZE(dss_opt_clks),
	.flags		= HWMOD_NO_IDLEST | HWMOD_CONTROL_OPT_CLKS_IN_RESET,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_dss_core_hwmod = अणु
	.name		= "dss_core",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.class		= &omap2_dss_hwmod_class,
	.मुख्य_clk	= "dss1_alwon_fck", /* instead of dss_fck */
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_DSS_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430ES2_ST_DSS_IDLE_SHIFT,
		पूर्ण,
	पूर्ण,
	.opt_clks	= dss_opt_clks,
	.opt_clks_cnt = ARRAY_SIZE(dss_opt_clks),
पूर्ण;

/*
 * 'dispc' class
 * display controller
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap3_dispc_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_SIDLEMODE | SYSC_HAS_MIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE |
			   SYSC_HAS_ENAWAKEUP),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   MSTANDBY_FORCE | MSTANDBY_NO | MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3_dispc_hwmod_class = अणु
	.name	= "dispc",
	.sysc	= &omap3_dispc_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_dss_dispc_hwmod = अणु
	.name		= "dss_dispc",
	.class		= &omap3_dispc_hwmod_class,
	.मुख्य_clk	= "dss1_alwon_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_DSS_MOD,
		पूर्ण,
	पूर्ण,
	.flags		= HWMOD_NO_IDLEST,
	.dev_attr	= &omap2_3_dss_dispc_dev_attr,
पूर्ण;

/*
 * 'dsi' class
 * display serial पूर्णांकerface controller
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap3xxx_dsi_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_dsi_hwmod_class = अणु
	.name = "dsi",
	.sysc	= &omap3xxx_dsi_sysc,
पूर्ण;

/* dss_dsi1 */
अटल काष्ठा omap_hwmod_opt_clk dss_dsi1_opt_clks[] = अणु
	अणु .role = "sys_clk", .clk = "dss2_alwon_fck" पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_dss_dsi1_hwmod = अणु
	.name		= "dss_dsi1",
	.class		= &omap3xxx_dsi_hwmod_class,
	.मुख्य_clk	= "dss1_alwon_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_DSS_MOD,
		पूर्ण,
	पूर्ण,
	.opt_clks	= dss_dsi1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_dsi1_opt_clks),
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

अटल काष्ठा omap_hwmod_opt_clk dss_rfbi_opt_clks[] = अणु
	अणु .role = "ick", .clk = "dss_ick" पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_dss_rfbi_hwmod = अणु
	.name		= "dss_rfbi",
	.class		= &omap2_rfbi_hwmod_class,
	.मुख्य_clk	= "dss1_alwon_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_DSS_MOD,
		पूर्ण,
	पूर्ण,
	.opt_clks	= dss_rfbi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_rfbi_opt_clks),
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

अटल काष्ठा omap_hwmod_opt_clk dss_venc_opt_clks[] = अणु
	/* required only on OMAP3430 */
	अणु .role = "tv_dac_clk", .clk = "dss_96m_fck" पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_dss_venc_hwmod = अणु
	.name		= "dss_venc",
	.class		= &omap2_venc_hwmod_class,
	.मुख्य_clk	= "dss_tv_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_DSS_MOD,
		पूर्ण,
	पूर्ण,
	.opt_clks	= dss_venc_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_venc_opt_clks),
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* I2C1 */
अटल काष्ठा omap_hwmod omap3xxx_i2c1_hwmod = अणु
	.name		= "i2c1",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.मुख्य_clk	= "i2c1_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_I2C1_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &i2c_class,
पूर्ण;

/* I2C2 */
अटल काष्ठा omap_hwmod omap3xxx_i2c2_hwmod = अणु
	.name		= "i2c2",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.मुख्य_clk	= "i2c2_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_I2C2_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &i2c_class,
पूर्ण;

/* I2C3 */
अटल काष्ठा omap_hwmod omap3xxx_i2c3_hwmod = अणु
	.name		= "i2c3",
	.flags		= HWMOD_16BIT_REG | HWMOD_SET_DEFAULT_CLOCKACT,
	.मुख्य_clk	= "i2c3_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_I2C3_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &i2c_class,
पूर्ण;

/*
 * 'gpio' class
 * general purpose io module
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap3xxx_gpio_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields    = &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_gpio_hwmod_class = अणु
	.name = "gpio",
	.sysc = &omap3xxx_gpio_sysc,
पूर्ण;

/* gpio1 */
अटल काष्ठा omap_hwmod_opt_clk gpio1_opt_clks[] = अणु
	अणु .role = "dbclk", .clk = "gpio1_dbck", पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_gpio1_hwmod = अणु
	.name		= "gpio1",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.मुख्य_clk	= "gpio1_ick",
	.opt_clks	= gpio1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio1_opt_clks),
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = WKUP_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPIO1_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_gpio_hwmod_class,
पूर्ण;

/* gpio2 */
अटल काष्ठा omap_hwmod_opt_clk gpio2_opt_clks[] = अणु
	अणु .role = "dbclk", .clk = "gpio2_dbck", पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_gpio2_hwmod = अणु
	.name		= "gpio2",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.मुख्य_clk	= "gpio2_ick",
	.opt_clks	= gpio2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio2_opt_clks),
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPIO2_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_gpio_hwmod_class,
पूर्ण;

/* gpio3 */
अटल काष्ठा omap_hwmod_opt_clk gpio3_opt_clks[] = अणु
	अणु .role = "dbclk", .clk = "gpio3_dbck", पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_gpio3_hwmod = अणु
	.name		= "gpio3",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.मुख्य_clk	= "gpio3_ick",
	.opt_clks	= gpio3_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio3_opt_clks),
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPIO3_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_gpio_hwmod_class,
पूर्ण;

/* gpio4 */
अटल काष्ठा omap_hwmod_opt_clk gpio4_opt_clks[] = अणु
	अणु .role = "dbclk", .clk = "gpio4_dbck", पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_gpio4_hwmod = अणु
	.name		= "gpio4",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.मुख्य_clk	= "gpio4_ick",
	.opt_clks	= gpio4_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio4_opt_clks),
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPIO4_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_gpio_hwmod_class,
पूर्ण;

/* gpio5 */

अटल काष्ठा omap_hwmod_opt_clk gpio5_opt_clks[] = अणु
	अणु .role = "dbclk", .clk = "gpio5_dbck", पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_gpio5_hwmod = अणु
	.name		= "gpio5",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.मुख्य_clk	= "gpio5_ick",
	.opt_clks	= gpio5_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio5_opt_clks),
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPIO5_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_gpio_hwmod_class,
पूर्ण;

/* gpio6 */

अटल काष्ठा omap_hwmod_opt_clk gpio6_opt_clks[] = अणु
	अणु .role = "dbclk", .clk = "gpio6_dbck", पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_gpio6_hwmod = अणु
	.name		= "gpio6",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.मुख्य_clk	= "gpio6_ick",
	.opt_clks	= gpio6_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio6_opt_clks),
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_GPIO6_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_gpio_hwmod_class,
पूर्ण;

/*
 * 'mcbsp' class
 * multi channel buffered serial port controller
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap3xxx_mcbsp_sysc = अणु
	.rev_offs	= -ENODEV,
	.sysc_offs	= 0x008c,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_mcbsp_hwmod_class = अणु
	.name = "mcbsp",
	.sysc = &omap3xxx_mcbsp_sysc,
पूर्ण;

/* McBSP functional घड़ी mapping */
अटल काष्ठा omap_hwmod_opt_clk mcbsp15_opt_clks[] = अणु
	अणु .role = "pad_fck", .clk = "mcbsp_clks" पूर्ण,
	अणु .role = "prcm_fck", .clk = "core_96m_fck" पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod_opt_clk mcbsp234_opt_clks[] = अणु
	अणु .role = "pad_fck", .clk = "mcbsp_clks" पूर्ण,
	अणु .role = "prcm_fck", .clk = "per_96m_fck" पूर्ण,
पूर्ण;

/* mcbsp1 */
अटल काष्ठा omap_hwmod omap3xxx_mcbsp1_hwmod = अणु
	.name		= "mcbsp1",
	.class		= &omap3xxx_mcbsp_hwmod_class,
	.मुख्य_clk	= "mcbsp1_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MCBSP1_SHIFT,
		पूर्ण,
	पूर्ण,
	.opt_clks	= mcbsp15_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp15_opt_clks),
पूर्ण;

/* mcbsp2 */
अटल काष्ठा omap_hwmod omap3xxx_mcbsp2_hwmod = अणु
	.name		= "mcbsp2",
	.class		= &omap3xxx_mcbsp_hwmod_class,
	.मुख्य_clk	= "mcbsp2_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MCBSP2_SHIFT,
		पूर्ण,
	पूर्ण,
	.opt_clks	= mcbsp234_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp234_opt_clks),
पूर्ण;

/* mcbsp3 */
अटल काष्ठा omap_hwmod omap3xxx_mcbsp3_hwmod = अणु
	.name		= "mcbsp3",
	.class		= &omap3xxx_mcbsp_hwmod_class,
	.मुख्य_clk	= "mcbsp3_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MCBSP3_SHIFT,
		पूर्ण,
	पूर्ण,
	.opt_clks	= mcbsp234_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp234_opt_clks),
पूर्ण;

/* mcbsp4 */
अटल काष्ठा omap_hwmod omap3xxx_mcbsp4_hwmod = अणु
	.name		= "mcbsp4",
	.class		= &omap3xxx_mcbsp_hwmod_class,
	.मुख्य_clk	= "mcbsp4_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = OMAP3430_PER_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MCBSP4_SHIFT,
		पूर्ण,
	पूर्ण,
	.opt_clks	= mcbsp234_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp234_opt_clks),
पूर्ण;

/* mcbsp5 */
अटल काष्ठा omap_hwmod omap3xxx_mcbsp5_hwmod = अणु
	.name		= "mcbsp5",
	.class		= &omap3xxx_mcbsp_hwmod_class,
	.मुख्य_clk	= "mcbsp5_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MCBSP5_SHIFT,
		पूर्ण,
	पूर्ण,
	.opt_clks	= mcbsp15_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(mcbsp15_opt_clks),
पूर्ण;

/* 'mcbsp sidetone' class */
अटल काष्ठा omap_hwmod_class_sysconfig omap3xxx_mcbsp_sidetone_sysc = अणु
	.rev_offs	= -ENODEV,
	.sysc_offs	= 0x0010,
	.sysc_flags	= SYSC_HAS_AUTOIDLE,
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_mcbsp_sidetone_hwmod_class = अणु
	.name = "mcbsp_sidetone",
	.sysc = &omap3xxx_mcbsp_sidetone_sysc,
पूर्ण;

/* mcbsp2_sidetone */
अटल काष्ठा omap_hwmod omap3xxx_mcbsp2_sidetone_hwmod = अणु
	.name		= "mcbsp2_sidetone",
	.class		= &omap3xxx_mcbsp_sidetone_hwmod_class,
	.मुख्य_clk	= "mcbsp2_ick",
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* mcbsp3_sidetone */
अटल काष्ठा omap_hwmod omap3xxx_mcbsp3_sidetone_hwmod = अणु
	.name		= "mcbsp3_sidetone",
	.class		= &omap3xxx_mcbsp_sidetone_hwmod_class,
	.मुख्य_clk	= "mcbsp3_ick",
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* SR common */
अटल काष्ठा omap_hwmod_class_sysconfig omap34xx_sr_sysc = अणु
	.rev_offs	= -ENODEV,
	.sysc_offs	= 0x24,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_NO_CACHE),
	.sysc_fields	= &omap34xx_sr_sysc_fields,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap34xx_smartreflex_hwmod_class = अणु
	.name = "smartreflex",
	.sysc = &omap34xx_sr_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod_class_sysconfig omap36xx_sr_sysc = अणु
	.rev_offs	= -ENODEV,
	.sysc_offs	= 0x38,
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_flags	= (SYSC_HAS_SIDLEMODE | SYSC_HAS_ENAWAKEUP |
			SYSC_NO_CACHE),
	.sysc_fields	= &omap36xx_sr_sysc_fields,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap36xx_smartreflex_hwmod_class = अणु
	.name = "smartreflex",
	.sysc = &omap36xx_sr_sysc,
पूर्ण;

/* SR1 */
अटल काष्ठा omap_smartreflex_dev_attr sr1_dev_attr = अणु
	.sensor_voltdm_name   = "mpu_iva",
पूर्ण;


अटल काष्ठा omap_hwmod omap34xx_sr1_hwmod = अणु
	.name		= "smartreflex_mpu_iva",
	.class		= &omap34xx_smartreflex_hwmod_class,
	.मुख्य_clk	= "sr1_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = WKUP_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_EN_SR1_SHIFT,
		पूर्ण,
	पूर्ण,
	.dev_attr	= &sr1_dev_attr,
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

अटल काष्ठा omap_hwmod omap36xx_sr1_hwmod = अणु
	.name		= "smartreflex_mpu_iva",
	.class		= &omap36xx_smartreflex_hwmod_class,
	.मुख्य_clk	= "sr1_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = WKUP_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_EN_SR1_SHIFT,
		पूर्ण,
	पूर्ण,
	.dev_attr	= &sr1_dev_attr,
पूर्ण;

/* SR2 */
अटल काष्ठा omap_smartreflex_dev_attr sr2_dev_attr = अणु
	.sensor_voltdm_name	= "core",
पूर्ण;


अटल काष्ठा omap_hwmod omap34xx_sr2_hwmod = अणु
	.name		= "smartreflex_core",
	.class		= &omap34xx_smartreflex_hwmod_class,
	.मुख्य_clk	= "sr2_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = WKUP_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_EN_SR2_SHIFT,
		पूर्ण,
	पूर्ण,
	.dev_attr	= &sr2_dev_attr,
	.flags		= HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

अटल काष्ठा omap_hwmod omap36xx_sr2_hwmod = अणु
	.name		= "smartreflex_core",
	.class		= &omap36xx_smartreflex_hwmod_class,
	.मुख्य_clk	= "sr2_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = WKUP_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_EN_SR2_SHIFT,
		पूर्ण,
	पूर्ण,
	.dev_attr	= &sr2_dev_attr,
पूर्ण;

/*
 * 'mailbox' class
 * mailbox module allowing communication between the on-chip processors
 * using a queued mailbox-पूर्णांकerrupt mechanism.
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap3xxx_mailbox_sysc = अणु
	.rev_offs	= 0x000,
	.sysc_offs	= 0x010,
	.syss_offs	= 0x014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
				SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_mailbox_hwmod_class = अणु
	.name = "mailbox",
	.sysc = &omap3xxx_mailbox_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_mailbox_hwmod = अणु
	.name		= "mailbox",
	.class		= &omap3xxx_mailbox_hwmod_class,
	.मुख्य_clk	= "mailboxes_ick",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MAILBOXES_SHIFT,
		पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * 'mcspi' class
 * multichannel serial port पूर्णांकerface (mcspi) / master/slave synchronous serial
 * bus
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap34xx_mcspi_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
				SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
				SYSC_HAS_AUTOIDLE | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields    = &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap34xx_mcspi_class = अणु
	.name = "mcspi",
	.sysc = &omap34xx_mcspi_sysc,
पूर्ण;

/* mcspi1 */
अटल काष्ठा omap_hwmod omap34xx_mcspi1 = अणु
	.name		= "mcspi1",
	.मुख्य_clk	= "mcspi1_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MCSPI1_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap34xx_mcspi_class,
पूर्ण;

/* mcspi2 */
अटल काष्ठा omap_hwmod omap34xx_mcspi2 = अणु
	.name		= "mcspi2",
	.मुख्य_clk	= "mcspi2_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MCSPI2_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap34xx_mcspi_class,
पूर्ण;

/* mcspi3 */
अटल काष्ठा omap_hwmod omap34xx_mcspi3 = अणु
	.name		= "mcspi3",
	.मुख्य_clk	= "mcspi3_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MCSPI3_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap34xx_mcspi_class,
पूर्ण;

/* mcspi4 */
अटल काष्ठा omap_hwmod omap34xx_mcspi4 = अणु
	.name		= "mcspi4",
	.मुख्य_clk	= "mcspi4_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MCSPI4_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap34xx_mcspi_class,
पूर्ण;

/* usbhsotg */
अटल काष्ठा omap_hwmod_class_sysconfig omap3xxx_usbhsotg_sysc = अणु
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
	.sysc = &omap3xxx_usbhsotg_sysc,
पूर्ण;

/* usb_otg_hs */

अटल काष्ठा omap_hwmod omap3xxx_usbhsotg_hwmod = अणु
	.name		= "usb_otg_hs",
	.मुख्य_clk	= "hsotgusb_ick",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430ES2_ST_HSOTGUSB_IDLE_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &usbotg_class,

	/*
	 * Erratum ID: i479  idle_req / idle_ack mechanism potentially
	 * broken when स्वतःidle is enabled
	 * workaround is to disable the स्वतःidle bit at module level.
	 *
	 * Enabling the device in any other MIDLEMODE setting but क्रमce-idle
	 * causes core_pwrdm not enter idle states at least on OMAP3630.
	 * Note that musb has OTG_FORCESTDBY रेजिस्टर that controls MSTANDBY
	 * संकेत when MIDLEMODE is set to क्रमce-idle.
	 */
	.flags		= HWMOD_NO_OCP_AUTOIDLE | HWMOD_SWSUP_SIDLE |
			  HWMOD_FORCE_MSTANDBY | HWMOD_RECONFIG_IO_CHAIN,
पूर्ण;

/* usb_otg_hs */

अटल काष्ठा omap_hwmod_class am35xx_usbotg_class = अणु
	.name = "am35xx_usbotg",
पूर्ण;

अटल काष्ठा omap_hwmod am35xx_usbhsotg_hwmod = अणु
	.name		= "am35x_otg_hs",
	.मुख्य_clk	= "hsotgusb_fck",
	.class		= &am35xx_usbotg_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* MMC/SD/SDIO common */
अटल काष्ठा omap_hwmod_class_sysconfig omap34xx_mmc_sysc = अणु
	.rev_offs	= 0x1fc,
	.sysc_offs	= 0x10,
	.syss_offs	= 0x14,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields    = &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap34xx_mmc_class = अणु
	.name = "mmc",
	.sysc = &omap34xx_mmc_sysc,
पूर्ण;

/* MMC/SD/SDIO1 */



अटल काष्ठा omap_hwmod_opt_clk omap34xx_mmc1_opt_clks[] = अणु
	अणु .role = "dbck", .clk = "omap_32k_fck", पूर्ण,
पूर्ण;

अटल काष्ठा omap_hsmmc_dev_attr mmc1_dev_attr = अणु
	.flags = OMAP_HSMMC_SUPPORTS_DUAL_VOLT,
पूर्ण;

/* See 35xx errata 2.1.1.128 in SPRZ278F */
अटल काष्ठा omap_hsmmc_dev_attr mmc1_pre_es3_dev_attr = अणु
	.flags = (OMAP_HSMMC_SUPPORTS_DUAL_VOLT |
		  OMAP_HSMMC_BROKEN_MULTIBLOCK_READ),
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_pre_es3_mmc1_hwmod = अणु
	.name		= "mmc1",
	.opt_clks	= omap34xx_mmc1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(omap34xx_mmc1_opt_clks),
	.मुख्य_clk	= "mmchs1_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MMC1_SHIFT,
		पूर्ण,
	पूर्ण,
	.dev_attr	= &mmc1_pre_es3_dev_attr,
	.class		= &omap34xx_mmc_class,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_es3plus_mmc1_hwmod = अणु
	.name		= "mmc1",
	.opt_clks	= omap34xx_mmc1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(omap34xx_mmc1_opt_clks),
	.मुख्य_clk	= "mmchs1_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MMC1_SHIFT,
		पूर्ण,
	पूर्ण,
	.dev_attr	= &mmc1_dev_attr,
	.class		= &omap34xx_mmc_class,
पूर्ण;

/* MMC/SD/SDIO2 */



अटल काष्ठा omap_hwmod_opt_clk omap34xx_mmc2_opt_clks[] = अणु
	अणु .role = "dbck", .clk = "omap_32k_fck", पूर्ण,
पूर्ण;

/* See 35xx errata 2.1.1.128 in SPRZ278F */
अटल काष्ठा omap_hsmmc_dev_attr mmc2_pre_es3_dev_attr = अणु
	.flags = OMAP_HSMMC_BROKEN_MULTIBLOCK_READ,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_pre_es3_mmc2_hwmod = अणु
	.name		= "mmc2",
	.opt_clks	= omap34xx_mmc2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(omap34xx_mmc2_opt_clks),
	.मुख्य_clk	= "mmchs2_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MMC2_SHIFT,
		पूर्ण,
	पूर्ण,
	.dev_attr	= &mmc2_pre_es3_dev_attr,
	.class		= &omap34xx_mmc_class,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_es3plus_mmc2_hwmod = अणु
	.name		= "mmc2",
	.opt_clks	= omap34xx_mmc2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(omap34xx_mmc2_opt_clks),
	.मुख्य_clk	= "mmchs2_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MMC2_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap34xx_mmc_class,
पूर्ण;

/* MMC/SD/SDIO3 */



अटल काष्ठा omap_hwmod_opt_clk omap34xx_mmc3_opt_clks[] = अणु
	अणु .role = "dbck", .clk = "omap_32k_fck", पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_mmc3_hwmod = अणु
	.name		= "mmc3",
	.opt_clks	= omap34xx_mmc3_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(omap34xx_mmc3_opt_clks),
	.मुख्य_clk	= "mmchs3_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_MMC3_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap34xx_mmc_class,
पूर्ण;

/*
 * 'usb_host_hs' class
 * high-speed multi-port usb host controller
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap3xxx_usb_host_hs_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_MIDLEMODE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_ENAWAKEUP |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   MSTANDBY_FORCE | MSTANDBY_NO | MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_usb_host_hs_hwmod_class = अणु
	.name = "usb_host_hs",
	.sysc = &omap3xxx_usb_host_hs_sysc,
पूर्ण;


अटल काष्ठा omap_hwmod omap3xxx_usb_host_hs_hwmod = अणु
	.name		= "usb_host_hs",
	.class		= &omap3xxx_usb_host_hs_hwmod_class,
	.clkdm_name	= "usbhost_clkdm",
	.मुख्य_clk	= "usbhost_48m_fck",
	.prcm = अणु
		.omap2 = अणु
			.module_offs = OMAP3430ES2_USBHOST_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430ES2_ST_USBHOST_IDLE_SHIFT,
		पूर्ण,
	पूर्ण,

	/*
	 * Errata: USBHOST Configured In Smart-Idle Can Lead To a Deadlock
	 * id: i660
	 *
	 * Description:
	 * In the following configuration :
	 * - USBHOST module is set to smart-idle mode
	 * - PRCM निश्चितs idle_req to the USBHOST module ( This typically
	 *   happens when the प्रणाली is going to a low घातer mode : all ports
	 *   have been suspended, the master part of the USBHOST module has
	 *   entered the standby state, and SW has cut the functional घड़ीs)
	 * - an USBHOST पूर्णांकerrupt occurs beक्रमe the module is able to answer
	 *   idle_ack, typically a remote wakeup IRQ.
	 * Then the USB HOST module will enter a deadlock situation where it
	 * is no more accessible nor functional.
	 *
	 * Workaround:
	 * Don't use smart idle; use only क्रमce idle, hence HWMOD_SWSUP_SIDLE
	 */

	/*
	 * Errata: USB host EHCI may stall when entering smart-standby mode
	 * Id: i571
	 *
	 * Description:
	 * When the USBHOST module is set to smart-standby mode, and when it is
	 * पढ़ोy to enter the standby state (i.e. all ports are suspended and
	 * all attached devices are in suspend mode), then it can wrongly निश्चित
	 * the Mstandby संकेत too early जबतक there are still some residual OCP
	 * transactions ongoing. If this condition occurs, the पूर्णांकernal state
	 * machine may go to an undefined state and the USB link may be stuck
	 * upon the next resume.
	 *
	 * Workaround:
	 * Don't use smart standby; use only क्रमce standby,
	 * hence HWMOD_SWSUP_MSTANDBY
	 */

	.flags		= HWMOD_SWSUP_SIDLE | HWMOD_SWSUP_MSTANDBY,
पूर्ण;

/*
 * 'usb_tll_hs' class
 * usb_tll_hs module is the adapter on the usb_host_hs ports
 */
अटल काष्ठा omap_hwmod_class_sysconfig omap3xxx_usb_tll_hs_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_usb_tll_hs_hwmod_class = अणु
	.name = "usb_tll_hs",
	.sysc = &omap3xxx_usb_tll_hs_sysc,
पूर्ण;


अटल काष्ठा omap_hwmod omap3xxx_usb_tll_hs_hwmod = अणु
	.name		= "usb_tll_hs",
	.class		= &omap3xxx_usb_tll_hs_hwmod_class,
	.clkdm_name	= "core_l4_clkdm",
	.मुख्य_clk	= "usbtll_fck",
	.prcm = अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 3,
			.idlest_idle_bit = OMAP3430ES2_ST_USBTLL_SHIFT,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_hdq1w_hwmod = अणु
	.name		= "hdq1w",
	.मुख्य_clk	= "hdq_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_HDQ_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2_hdq1w_class,
पूर्ण;

/* SAD2D */
अटल काष्ठा omap_hwmod_rst_info omap3xxx_sad2d_resets[] = अणु
	अणु .name = "rst_modem_pwron_sw", .rst_shअगरt = 0 पूर्ण,
	अणु .name = "rst_modem_sw", .rst_shअगरt = 1 पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_sad2d_class = अणु
	.name			= "sad2d",
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_sad2d_hwmod = अणु
	.name		= "sad2d",
	.rst_lines	= omap3xxx_sad2d_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap3xxx_sad2d_resets),
	.मुख्य_clk	= "sad2d_ick",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_SAD2D_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_sad2d_class,
पूर्ण;

/*
 * 'gpmc' class
 * general purpose memory controller
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap3xxx_gpmc_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_gpmc_hwmod_class = अणु
	.name	= "gpmc",
	.sysc	= &omap3xxx_gpmc_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_gpmc_hwmod = अणु
	.name		= "gpmc",
	.class		= &omap3xxx_gpmc_hwmod_class,
	.clkdm_name	= "core_l3_clkdm",
	.मुख्य_clk	= "gpmc_fck",
	/* Skip reset क्रम CONFIG_OMAP_GPMC_DEBUG क्रम bootloader timings */
	.flags		= HWMOD_NO_IDLEST | DEBUG_OMAP_GPMC_HWMOD_FLAGS,
पूर्ण;

/*
 * पूर्णांकerfaces
 */

/* L3 -> L4_CORE पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l3_मुख्य__l4_core = अणु
	.master	= &omap3xxx_l3_मुख्य_hwmod,
	.slave	= &omap3xxx_l4_core_hwmod,
	.user	= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L3 -> L4_PER पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l3_मुख्य__l4_per = अणु
	.master = &omap3xxx_l3_मुख्य_hwmod,
	.slave	= &omap3xxx_l4_per_hwmod,
	.user	= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;


/* MPU -> L3 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_mpu__l3_मुख्य = अणु
	.master   = &omap3xxx_mpu_hwmod,
	.slave    = &omap3xxx_l3_मुख्य_hwmod,
	.user	= OCP_USER_MPU,
पूर्ण;


/* l3 -> debugss */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l3_मुख्य__l4_debugss = अणु
	.master		= &omap3xxx_l3_मुख्य_hwmod,
	.slave		= &omap3xxx_debugss_hwmod,
	.user		= OCP_USER_MPU,
पूर्ण;

/* DSS -> l3 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3430es1_dss__l3 = अणु
	.master		= &omap3430es1_dss_core_hwmod,
	.slave		= &omap3xxx_l3_मुख्य_hwmod,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_dss__l3 = अणु
	.master		= &omap3xxx_dss_core_hwmod,
	.slave		= &omap3xxx_l3_मुख्य_hwmod,
	.fw = अणु
		.omap2 = अणु
			.l3_perm_bit  = OMAP3_L3_CORE_FW_INIT_ID_DSS,
			.flags	= OMAP_FIREWALL_L3,
		पूर्ण,
	पूर्ण,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l3_core -> usbhsotg पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_usbhsotg__l3 = अणु
	.master		= &omap3xxx_usbhsotg_hwmod,
	.slave		= &omap3xxx_l3_मुख्य_hwmod,
	.clk		= "core_l3_ick",
	.user		= OCP_USER_MPU,
पूर्ण;

/* l3_core -> am35xx_usbhsotg पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर am35xx_usbhsotg__l3 = अणु
	.master		= &am35xx_usbhsotg_hwmod,
	.slave		= &omap3xxx_l3_मुख्य_hwmod,
	.clk		= "hsotgusb_ick",
	.user		= OCP_USER_MPU,
पूर्ण;

/* l3_core -> sad2d पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_sad2d__l3 = अणु
	.master		= &omap3xxx_sad2d_hwmod,
	.slave		= &omap3xxx_l3_मुख्य_hwmod,
	.clk		= "core_l3_ick",
	.user		= OCP_USER_MPU,
पूर्ण;

/* L4_CORE -> L4_WKUP पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__l4_wkup = अणु
	.master	= &omap3xxx_l4_core_hwmod,
	.slave	= &omap3xxx_l4_wkup_hwmod,
	.user	= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 CORE -> MMC1 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__pre_es3_mmc1 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_pre_es3_mmc1_hwmod,
	.clk		= "mmchs1_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
	.flags		= OMAP_FIREWALL_L4,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__es3plus_mmc1 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_es3plus_mmc1_hwmod,
	.clk		= "mmchs1_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
	.flags		= OMAP_FIREWALL_L4,
पूर्ण;

/* L4 CORE -> MMC2 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__pre_es3_mmc2 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_pre_es3_mmc2_hwmod,
	.clk		= "mmchs2_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
	.flags		= OMAP_FIREWALL_L4,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__es3plus_mmc2 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_es3plus_mmc2_hwmod,
	.clk		= "mmchs2_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
	.flags		= OMAP_FIREWALL_L4,
पूर्ण;

/* L4 CORE -> MMC3 पूर्णांकerface */

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__mmc3 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_mmc3_hwmod,
	.clk		= "mmchs3_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
	.flags		= OMAP_FIREWALL_L4,
पूर्ण;

/* L4 CORE -> UART1 पूर्णांकerface */

अटल काष्ठा omap_hwmod_ocp_अगर omap3_l4_core__uart1 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_uart1_hwmod,
	.clk		= "uart1_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 CORE -> UART2 पूर्णांकerface */

अटल काष्ठा omap_hwmod_ocp_अगर omap3_l4_core__uart2 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_uart2_hwmod,
	.clk		= "uart2_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 PER -> UART3 पूर्णांकerface */

अटल काष्ठा omap_hwmod_ocp_अगर omap3_l4_per__uart3 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_uart3_hwmod,
	.clk		= "uart3_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 PER -> UART4 पूर्णांकerface */

अटल काष्ठा omap_hwmod_ocp_अगर omap36xx_l4_per__uart4 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap36xx_uart4_hwmod,
	.clk		= "uart4_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* AM35xx: L4 CORE -> UART4 पूर्णांकerface */

अटल काष्ठा omap_hwmod_ocp_अगर am35xx_l4_core__uart4 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &am35xx_uart4_hwmod,
	.clk		= "uart4_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 CORE -> I2C1 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap3_l4_core__i2c1 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_i2c1_hwmod,
	.clk		= "i2c1_ick",
	.fw = अणु
		.omap2 = अणु
			.l4_fw_region  = OMAP3_L4_CORE_FW_I2C1_REGION,
			.l4_prot_group = 7,
			.flags	= OMAP_FIREWALL_L4,
		पूर्ण,
	पूर्ण,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 CORE -> I2C2 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap3_l4_core__i2c2 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_i2c2_hwmod,
	.clk		= "i2c2_ick",
	.fw = अणु
		.omap2 = अणु
			.l4_fw_region  = OMAP3_L4_CORE_FW_I2C2_REGION,
			.l4_prot_group = 7,
			.flags = OMAP_FIREWALL_L4,
		पूर्ण,
	पूर्ण,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 CORE -> I2C3 पूर्णांकerface */

अटल काष्ठा omap_hwmod_ocp_अगर omap3_l4_core__i2c3 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_i2c3_hwmod,
	.clk		= "i2c3_ick",
	.fw = अणु
		.omap2 = अणु
			.l4_fw_region  = OMAP3_L4_CORE_FW_I2C3_REGION,
			.l4_prot_group = 7,
			.flags = OMAP_FIREWALL_L4,
		पूर्ण,
	पूर्ण,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* L4 CORE -> SR1 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap34xx_l4_core__sr1 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap34xx_sr1_hwmod,
	.clk		= "sr_l4_ick",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर omap36xx_l4_core__sr1 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap36xx_sr1_hwmod,
	.clk		= "sr_l4_ick",
	.user		= OCP_USER_MPU,
पूर्ण;

/* L4 CORE -> SR2 पूर्णांकerface */

अटल काष्ठा omap_hwmod_ocp_अगर omap34xx_l4_core__sr2 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap34xx_sr2_hwmod,
	.clk		= "sr_l4_ick",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर omap36xx_l4_core__sr2 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap36xx_sr2_hwmod,
	.clk		= "sr_l4_ick",
	.user		= OCP_USER_MPU,
पूर्ण;


/* l4_core -> usbhsotg  */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__usbhsotg = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_usbhsotg_hwmod,
	.clk		= "l4_ick",
	.user		= OCP_USER_MPU,
पूर्ण;


/* l4_core -> usbhsotg  */
अटल काष्ठा omap_hwmod_ocp_अगर am35xx_l4_core__usbhsotg = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &am35xx_usbhsotg_hwmod,
	.clk		= "hsotgusb_ick",
	.user		= OCP_USER_MPU,
पूर्ण;

/* L4_WKUP -> L4_SEC पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_wkup__l4_sec = अणु
	.master = &omap3xxx_l4_wkup_hwmod,
	.slave	= &omap3xxx_l4_sec_hwmod,
	.user	= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* IVA2 <- L3 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l3__iva = अणु
	.master		= &omap3xxx_l3_मुख्य_hwmod,
	.slave		= &omap3xxx_iva_hwmod,
	.clk		= "core_l3_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_per -> समयr3 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__समयr3 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_समयr3_hwmod,
	.clk		= "gpt3_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;


/* l4_per -> समयr4 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__समयr4 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_समयr4_hwmod,
	.clk		= "gpt4_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;


/* l4_per -> समयr5 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__समयr5 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_समयr5_hwmod,
	.clk		= "gpt5_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;


/* l4_per -> समयr6 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__समयr6 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_समयr6_hwmod,
	.clk		= "gpt6_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;


/* l4_per -> समयr7 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__समयr7 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_समयr7_hwmod,
	.clk		= "gpt7_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;


/* l4_per -> समयr8 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__समयr8 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_समयr8_hwmod,
	.clk		= "gpt8_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;


/* l4_per -> समयr9 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__समयr9 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_समयr9_hwmod,
	.clk		= "gpt9_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> समयr10 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__समयr10 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_समयr10_hwmod,
	.clk		= "gpt10_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> समयr11 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__समयr11 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_समयr11_hwmod,
	.clk		= "gpt11_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_wkup -> wd_समयr2 */

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_wkup__wd_समयr2 = अणु
	.master		= &omap3xxx_l4_wkup_hwmod,
	.slave		= &omap3xxx_wd_समयr2_hwmod,
	.clk		= "wdt2_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> dss */
अटल काष्ठा omap_hwmod_ocp_अगर omap3430es1_l4_core__dss = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3430es1_dss_core_hwmod,
	.clk		= "dss_ick",
	.fw = अणु
		.omap2 = अणु
			.l4_fw_region  = OMAP3ES1_L4_CORE_FW_DSS_CORE_REGION,
			.l4_prot_group = OMAP3_L4_CORE_FW_DSS_PROT_GROUP,
			.flags	= OMAP_FIREWALL_L4,
		पूर्ण,
	पूर्ण,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__dss = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_dss_core_hwmod,
	.clk		= "dss_ick",
	.fw = अणु
		.omap2 = अणु
			.l4_fw_region  = OMAP3_L4_CORE_FW_DSS_CORE_REGION,
			.l4_prot_group = OMAP3_L4_CORE_FW_DSS_PROT_GROUP,
			.flags	= OMAP_FIREWALL_L4,
		पूर्ण,
	पूर्ण,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> dss_dispc */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__dss_dispc = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_dss_dispc_hwmod,
	.clk		= "dss_ick",
	.fw = अणु
		.omap2 = अणु
			.l4_fw_region  = OMAP3_L4_CORE_FW_DSS_DISPC_REGION,
			.l4_prot_group = OMAP3_L4_CORE_FW_DSS_PROT_GROUP,
			.flags	= OMAP_FIREWALL_L4,
		पूर्ण,
	पूर्ण,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> dss_dsi1 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__dss_dsi1 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_dss_dsi1_hwmod,
	.clk		= "dss_ick",
	.fw = अणु
		.omap2 = अणु
			.l4_fw_region  = OMAP3_L4_CORE_FW_DSS_DSI_REGION,
			.l4_prot_group = OMAP3_L4_CORE_FW_DSS_PROT_GROUP,
			.flags	= OMAP_FIREWALL_L4,
		पूर्ण,
	पूर्ण,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> dss_rfbi */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__dss_rfbi = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_dss_rfbi_hwmod,
	.clk		= "dss_ick",
	.fw = अणु
		.omap2 = अणु
			.l4_fw_region  = OMAP3_L4_CORE_FW_DSS_RFBI_REGION,
			.l4_prot_group = OMAP3_L4_CORE_FW_DSS_PROT_GROUP ,
			.flags	= OMAP_FIREWALL_L4,
		पूर्ण,
	पूर्ण,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> dss_venc */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__dss_venc = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_dss_venc_hwmod,
	.clk		= "dss_ick",
	.fw = अणु
		.omap2 = अणु
			.l4_fw_region  = OMAP3_L4_CORE_FW_DSS_VENC_REGION,
			.l4_prot_group = OMAP3_L4_CORE_FW_DSS_PROT_GROUP,
			.flags	= OMAP_FIREWALL_L4,
		पूर्ण,
	पूर्ण,
	.flags		= OCPIF_SWSUP_IDLE,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_wkup -> gpio1 */

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_wkup__gpio1 = अणु
	.master		= &omap3xxx_l4_wkup_hwmod,
	.slave		= &omap3xxx_gpio1_hwmod,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_per -> gpio2 */

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__gpio2 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_gpio2_hwmod,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_per -> gpio3 */

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__gpio3 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_gpio3_hwmod,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/*
 * 'mmu' class
 * The memory management unit perक्रमms भव to physical address translation
 * क्रम its requestors.
 */

अटल काष्ठा omap_hwmod_class_sysconfig mmu_sysc = अणु
	.rev_offs	= 0x000,
	.sysc_offs	= 0x010,
	.syss_offs	= 0x014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_mmu_hwmod_class = अणु
	.name = "mmu",
	.sysc = &mmu_sysc,
पूर्ण;

/* mmu isp */
अटल काष्ठा omap_hwmod omap3xxx_mmu_isp_hwmod;

/* l4_core -> mmu isp */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__mmu_isp = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_mmu_isp_hwmod,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_mmu_isp_hwmod = अणु
	.name		= "mmu_isp",
	.class		= &omap3xxx_mmu_hwmod_class,
	.मुख्य_clk	= "cam_ick",
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* mmu iva */

अटल काष्ठा omap_hwmod omap3xxx_mmu_iva_hwmod;

अटल काष्ठा omap_hwmod_rst_info omap3xxx_mmu_iva_resets[] = अणु
	अणु .name = "mmu", .rst_shअगरt = 1, .st_shअगरt = 9 पूर्ण,
पूर्ण;

/* l3_मुख्य -> iva mmu */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l3_मुख्य__mmu_iva = अणु
	.master		= &omap3xxx_l3_मुख्य_hwmod,
	.slave		= &omap3xxx_mmu_iva_hwmod,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_mmu_iva_hwmod = अणु
	.name		= "mmu_iva",
	.class		= &omap3xxx_mmu_hwmod_class,
	.clkdm_name	= "iva2_clkdm",
	.rst_lines	= omap3xxx_mmu_iva_resets,
	.rst_lines_cnt	= ARRAY_SIZE(omap3xxx_mmu_iva_resets),
	.मुख्य_clk	= "iva2_ck",
	.prcm = अणु
		.omap2 = अणु
			.module_offs = OMAP3430_IVA2_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_IVA2_SHIFT,
		पूर्ण,
	पूर्ण,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* l4_per -> gpio4 */

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__gpio4 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_gpio4_hwmod,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_per -> gpio5 */

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__gpio5 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_gpio5_hwmod,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_per -> gpio6 */

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__gpio6 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_gpio6_hwmod,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> mcbsp1 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__mcbsp1 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_mcbsp1_hwmod,
	.clk		= "mcbsp1_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;


/* l4_per -> mcbsp2 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__mcbsp2 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_mcbsp2_hwmod,
	.clk		= "mcbsp2_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;


/* l4_per -> mcbsp3 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__mcbsp3 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_mcbsp3_hwmod,
	.clk		= "mcbsp3_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;


/* l4_per -> mcbsp4 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__mcbsp4 = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_mcbsp4_hwmod,
	.clk		= "mcbsp4_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;


/* l4_core -> mcbsp5 */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__mcbsp5 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_mcbsp5_hwmod,
	.clk		= "mcbsp5_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;


/* l4_per -> mcbsp2_sidetone */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__mcbsp2_sidetone = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_mcbsp2_sidetone_hwmod,
	.clk		= "mcbsp2_ick",
	.user		= OCP_USER_MPU,
पूर्ण;


/* l4_per -> mcbsp3_sidetone */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_per__mcbsp3_sidetone = अणु
	.master		= &omap3xxx_l4_per_hwmod,
	.slave		= &omap3xxx_mcbsp3_sidetone_hwmod,
	.clk		= "mcbsp3_ick",
	.user		= OCP_USER_MPU,
पूर्ण;

/* l4_core -> mailbox */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__mailbox = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_mailbox_hwmod,
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4 core -> mcspi1 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap34xx_l4_core__mcspi1 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap34xx_mcspi1,
	.clk		= "mcspi1_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4 core -> mcspi2 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap34xx_l4_core__mcspi2 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap34xx_mcspi2,
	.clk		= "mcspi2_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4 core -> mcspi3 पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap34xx_l4_core__mcspi3 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap34xx_mcspi3,
	.clk		= "mcspi3_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4 core -> mcspi4 पूर्णांकerface */

अटल काष्ठा omap_hwmod_ocp_अगर omap34xx_l4_core__mcspi4 = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap34xx_mcspi4,
	.clk		= "mcspi4_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_usb_host_hs__l3_मुख्य_2 = अणु
	.master		= &omap3xxx_usb_host_hs_hwmod,
	.slave		= &omap3xxx_l3_मुख्य_hwmod,
	.clk		= "core_l3_ick",
	.user		= OCP_USER_MPU,
पूर्ण;


अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__usb_host_hs = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_usb_host_hs_hwmod,
	.clk		= "usbhost_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;


अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__usb_tll_hs = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_usb_tll_hs_hwmod,
	.clk		= "usbtll_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> hdq1w पूर्णांकerface */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__hdq1w = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_hdq1w_hwmod,
	.clk		= "hdq_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
	.flags		= OMAP_FIREWALL_L4 | OCPIF_SWSUP_IDLE,
पूर्ण;

/* am35xx has Davinci MDIO & EMAC */
अटल काष्ठा omap_hwmod_class am35xx_mdio_class = अणु
	.name = "davinci_mdio",
पूर्ण;

अटल काष्ठा omap_hwmod am35xx_mdio_hwmod = अणु
	.name		= "davinci_mdio",
	.class		= &am35xx_mdio_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/*
 * XXX Should be connected to an IPSS hwmod, not the L3 directly;
 * but this will probably require some additional hwmod core support,
 * so is left as a future to-करो item.
 */
अटल काष्ठा omap_hwmod_ocp_अगर am35xx_mdio__l3 = अणु
	.master		= &am35xx_mdio_hwmod,
	.slave		= &omap3xxx_l3_मुख्य_hwmod,
	.clk		= "emac_fck",
	.user		= OCP_USER_MPU,
पूर्ण;

/* l4_core -> davinci mdio  */
/*
 * XXX Should be connected to an IPSS hwmod, not the L4_CORE directly;
 * but this will probably require some additional hwmod core support,
 * so is left as a future to-करो item.
 */
अटल काष्ठा omap_hwmod_ocp_अगर am35xx_l4_core__mdio = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &am35xx_mdio_hwmod,
	.clk		= "emac_fck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_class am35xx_emac_class = अणु
	.name = "davinci_emac",
पूर्ण;

अटल काष्ठा omap_hwmod am35xx_emac_hwmod = अणु
	.name		= "davinci_emac",
	.class		= &am35xx_emac_class,
	/*
	 * According to Mark Greer, the MPU will not वापस from WFI
	 * when the EMAC संकेतs an पूर्णांकerrupt.
	 * http://www.spinics.net/lists/arm-kernel/msg174734.hपंचांगl
	 */
	.flags		= (HWMOD_NO_IDLEST | HWMOD_BLOCK_WFI),
पूर्ण;

/* l3_core -> davinci emac पूर्णांकerface */
/*
 * XXX Should be connected to an IPSS hwmod, not the L3 directly;
 * but this will probably require some additional hwmod core support,
 * so is left as a future to-करो item.
 */
अटल काष्ठा omap_hwmod_ocp_अगर am35xx_emac__l3 = अणु
	.master		= &am35xx_emac_hwmod,
	.slave		= &omap3xxx_l3_मुख्य_hwmod,
	.clk		= "emac_ick",
	.user		= OCP_USER_MPU,
पूर्ण;

/* l4_core -> davinci emac  */
/*
 * XXX Should be connected to an IPSS hwmod, not the L4_CORE directly;
 * but this will probably require some additional hwmod core support,
 * so is left as a future to-करो item.
 */
अटल काष्ठा omap_hwmod_ocp_अगर am35xx_l4_core__emac = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &am35xx_emac_hwmod,
	.clk		= "emac_ick",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l3_मुख्य__gpmc = अणु
	.master		= &omap3xxx_l3_मुख्य_hwmod,
	.slave		= &omap3xxx_gpmc_hwmod,
	.clk		= "core_l3_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/* l4_core -> SHAM2 (SHA1/MD5) (similar to omap24xx) */
अटल काष्ठा omap_hwmod_class_sysconfig omap3_sham_sysc = अणु
	.rev_offs	= 0x5c,
	.sysc_offs	= 0x60,
	.syss_offs	= 0x64,
	.sysc_flags	= (SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE | SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap3_sham_sysc_fields,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_sham_class = अणु
	.name	= "sham",
	.sysc	= &omap3_sham_sysc,
पूर्ण;



अटल काष्ठा omap_hwmod omap3xxx_sham_hwmod = अणु
	.name		= "sham",
	.मुख्य_clk	= "sha12_ick",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP3430_ST_SHA12_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap3xxx_sham_class,
पूर्ण;


अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__sham = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_sham_hwmod,
	.clk		= "sha12_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

/*
 * 'ssi' class
 * synchronous serial पूर्णांकerface (multichannel and full-duplex serial अगर)
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap34xx_ssi_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_MIDLEMODE |
			   SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap3xxx_ssi_hwmod_class = अणु
	.name	= "ssi",
	.sysc	= &omap34xx_ssi_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod omap3xxx_ssi_hwmod = अणु
	.name		= "ssi",
	.class		= &omap3xxx_ssi_hwmod_class,
	.clkdm_name	= "core_l4_clkdm",
	.मुख्य_clk	= "ssi_ssr_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs		= CORE_MOD,
			.idlest_reg_id		= 1,
			.idlest_idle_bit	= OMAP3430ES2_ST_SSI_IDLE_SHIFT,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* L4 CORE -> SSI */
अटल काष्ठा omap_hwmod_ocp_अगर omap3xxx_l4_core__ssi = अणु
	.master		= &omap3xxx_l4_core_hwmod,
	.slave		= &omap3xxx_ssi_hwmod,
	.clk		= "ssi_ick",
	.user		= OCP_USER_MPU | OCP_USER_SDMA,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर *omap3xxx_hwmod_ocp_अगरs[] __initdata = अणु
	&omap3xxx_l3_मुख्य__l4_core,
	&omap3xxx_l3_मुख्य__l4_per,
	&omap3xxx_mpu__l3_मुख्य,
	&omap3xxx_l3_मुख्य__l4_debugss,
	&omap3xxx_l4_core__l4_wkup,
	&omap3xxx_l4_core__mmc3,
	&omap3_l4_core__uart1,
	&omap3_l4_core__uart2,
	&omap3_l4_per__uart3,
	&omap3_l4_core__i2c1,
	&omap3_l4_core__i2c2,
	&omap3_l4_core__i2c3,
	&omap3xxx_l4_wkup__l4_sec,
	&omap3xxx_l4_per__समयr3,
	&omap3xxx_l4_per__समयr4,
	&omap3xxx_l4_per__समयr5,
	&omap3xxx_l4_per__समयr6,
	&omap3xxx_l4_per__समयr7,
	&omap3xxx_l4_per__समयr8,
	&omap3xxx_l4_per__समयr9,
	&omap3xxx_l4_core__समयr10,
	&omap3xxx_l4_core__समयr11,
	&omap3xxx_l4_wkup__wd_समयr2,
	&omap3xxx_l4_wkup__gpio1,
	&omap3xxx_l4_per__gpio2,
	&omap3xxx_l4_per__gpio3,
	&omap3xxx_l4_per__gpio4,
	&omap3xxx_l4_per__gpio5,
	&omap3xxx_l4_per__gpio6,
	&omap3xxx_l4_core__mcbsp1,
	&omap3xxx_l4_per__mcbsp2,
	&omap3xxx_l4_per__mcbsp3,
	&omap3xxx_l4_per__mcbsp4,
	&omap3xxx_l4_core__mcbsp5,
	&omap3xxx_l4_per__mcbsp2_sidetone,
	&omap3xxx_l4_per__mcbsp3_sidetone,
	&omap34xx_l4_core__mcspi1,
	&omap34xx_l4_core__mcspi2,
	&omap34xx_l4_core__mcspi3,
	&omap34xx_l4_core__mcspi4,
	&omap3xxx_l3_मुख्य__gpmc,
	शून्य,
पूर्ण;

/* crypto hwmod links */
अटल काष्ठा omap_hwmod_ocp_अगर *omap34xx_sham_hwmod_ocp_अगरs[] __initdata = अणु
	&omap3xxx_l4_core__sham,
	शून्य,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर *omap36xx_sham_hwmod_ocp_अगरs[] __initdata = अणु
	&omap3xxx_l4_core__sham,
	शून्य
पूर्ण;


/*
 * Apparently the SHA/MD5 and AES accelerator IP blocks are
 * only present on some AM35xx chips, and no one knows which
 * ones.  See
 * http://www.spinics.net/lists/arm-kernel/msg215466.hपंचांगl So
 * अगर you need these IP blocks on an AM35xx, try uncommenting
 * the following lines.
 */
अटल काष्ठा omap_hwmod_ocp_अगर *am35xx_sham_hwmod_ocp_अगरs[] __initdata = अणु
	/* &omap3xxx_l4_core__sham, */
	शून्य
पूर्ण;

/* 3430ES1-only hwmod links */
अटल काष्ठा omap_hwmod_ocp_अगर *omap3430es1_hwmod_ocp_अगरs[] __initdata = अणु
	&omap3430es1_dss__l3,
	&omap3430es1_l4_core__dss,
	शून्य,
पूर्ण;

/* 3430ES2+-only hwmod links */
अटल काष्ठा omap_hwmod_ocp_अगर *omap3430es2plus_hwmod_ocp_अगरs[] __initdata = अणु
	&omap3xxx_dss__l3,
	&omap3xxx_l4_core__dss,
	&omap3xxx_usbhsotg__l3,
	&omap3xxx_l4_core__usbhsotg,
	&omap3xxx_usb_host_hs__l3_मुख्य_2,
	&omap3xxx_l4_core__usb_host_hs,
	&omap3xxx_l4_core__usb_tll_hs,
	शून्य,
पूर्ण;

/* <= 3430ES3-only hwmod links */
अटल काष्ठा omap_hwmod_ocp_अगर *omap3430_pre_es3_hwmod_ocp_अगरs[] __initdata = अणु
	&omap3xxx_l4_core__pre_es3_mmc1,
	&omap3xxx_l4_core__pre_es3_mmc2,
	शून्य,
पूर्ण;

/* 3430ES3+-only hwmod links */
अटल काष्ठा omap_hwmod_ocp_अगर *omap3430_es3plus_hwmod_ocp_अगरs[] __initdata = अणु
	&omap3xxx_l4_core__es3plus_mmc1,
	&omap3xxx_l4_core__es3plus_mmc2,
	शून्य,
पूर्ण;

/* 34xx-only hwmod links (all ES revisions) */
अटल काष्ठा omap_hwmod_ocp_अगर *omap34xx_hwmod_ocp_अगरs[] __initdata = अणु
	&omap3xxx_l3__iva,
	&omap34xx_l4_core__sr1,
	&omap34xx_l4_core__sr2,
	&omap3xxx_l4_core__mailbox,
	&omap3xxx_l4_core__hdq1w,
	&omap3xxx_sad2d__l3,
	&omap3xxx_l4_core__mmu_isp,
	&omap3xxx_l3_मुख्य__mmu_iva,
	&omap3xxx_l4_core__ssi,
	शून्य,
पूर्ण;

/* 36xx-only hwmod links (all ES revisions) */
अटल काष्ठा omap_hwmod_ocp_अगर *omap36xx_hwmod_ocp_अगरs[] __initdata = अणु
	&omap3xxx_l3__iva,
	&omap36xx_l4_per__uart4,
	&omap3xxx_dss__l3,
	&omap3xxx_l4_core__dss,
	&omap36xx_l4_core__sr1,
	&omap36xx_l4_core__sr2,
	&omap3xxx_usbhsotg__l3,
	&omap3xxx_l4_core__usbhsotg,
	&omap3xxx_l4_core__mailbox,
	&omap3xxx_usb_host_hs__l3_मुख्य_2,
	&omap3xxx_l4_core__usb_host_hs,
	&omap3xxx_l4_core__usb_tll_hs,
	&omap3xxx_l4_core__es3plus_mmc1,
	&omap3xxx_l4_core__es3plus_mmc2,
	&omap3xxx_l4_core__hdq1w,
	&omap3xxx_sad2d__l3,
	&omap3xxx_l4_core__mmu_isp,
	&omap3xxx_l3_मुख्य__mmu_iva,
	&omap3xxx_l4_core__ssi,
	शून्य,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर *am35xx_hwmod_ocp_अगरs[] __initdata = अणु
	&omap3xxx_dss__l3,
	&omap3xxx_l4_core__dss,
	&am35xx_usbhsotg__l3,
	&am35xx_l4_core__usbhsotg,
	&am35xx_l4_core__uart4,
	&omap3xxx_usb_host_hs__l3_मुख्य_2,
	&omap3xxx_l4_core__usb_host_hs,
	&omap3xxx_l4_core__usb_tll_hs,
	&omap3xxx_l4_core__es3plus_mmc1,
	&omap3xxx_l4_core__es3plus_mmc2,
	&omap3xxx_l4_core__hdq1w,
	&am35xx_mdio__l3,
	&am35xx_l4_core__mdio,
	&am35xx_emac__l3,
	&am35xx_l4_core__emac,
	शून्य,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर *omap3xxx_dss_hwmod_ocp_अगरs[] __initdata = अणु
	&omap3xxx_l4_core__dss_dispc,
	&omap3xxx_l4_core__dss_dsi1,
	&omap3xxx_l4_core__dss_rfbi,
	&omap3xxx_l4_core__dss_venc,
	शून्य,
पूर्ण;

/**
 * omap3xxx_hwmod_is_hs_ip_block_usable - is a security IP block accessible?
 * @bus: काष्ठा device_node * क्रम the top-level OMAP DT data
 * @dev_name: device name used in the DT file
 *
 * Determine whether a "secure" IP block @dev_name is usable by Linux.
 * There करोesn't appear to be a 100% reliable way to determine this,
 * so we rely on heuristics.  If @bus is null, meaning there's no DT
 * data, then we only assume the IP block is accessible अगर the OMAP is
 * fused as a 'general-purpose' SoC.  If however DT data is present,
 * test to see अगर the IP block is described in the DT data and set to
 * 'status = "okay"'.  If so then we assume the ODM has configured the
 * OMAP firewalls to allow access to the IP block.
 *
 * Return: 0 अगर device named @dev_name is not likely to be accessible,
 * or 1 अगर it is likely to be accessible.
 */
अटल bool __init omap3xxx_hwmod_is_hs_ip_block_usable(काष्ठा device_node *bus,
							स्थिर अक्षर *dev_name)
अणु
	काष्ठा device_node *node;
	bool available;

	अगर (!bus)
		वापस omap_type() == OMAP2_DEVICE_TYPE_GP;

	node = of_get_child_by_name(bus, dev_name);
	available = of_device_is_available(node);
	of_node_put(node);

	वापस available;
पूर्ण

पूर्णांक __init omap3xxx_hwmod_init(व्योम)
अणु
	पूर्णांक r;
	काष्ठा omap_hwmod_ocp_अगर **h = शून्य, **h_sham = शून्य;
	काष्ठा device_node *bus;
	अचिन्हित पूर्णांक rev;

	omap_hwmod_init();

	/* Register hwmod links common to all OMAP3 */
	r = omap_hwmod_रेजिस्टर_links(omap3xxx_hwmod_ocp_अगरs);
	अगर (r < 0)
		वापस r;

	rev = omap_rev();

	/*
	 * Register hwmod links common to inभागidual OMAP3 families, all
	 * silicon revisions (e.g., 34xx, or AM3505/3517, or 36xx)
	 * All possible revisions should be included in this conditional.
	 */
	अगर (rev == OMAP3430_REV_ES1_0 || rev == OMAP3430_REV_ES2_0 ||
	    rev == OMAP3430_REV_ES2_1 || rev == OMAP3430_REV_ES3_0 ||
	    rev == OMAP3430_REV_ES3_1 || rev == OMAP3430_REV_ES3_1_2) अणु
		h = omap34xx_hwmod_ocp_अगरs;
		h_sham = omap34xx_sham_hwmod_ocp_अगरs;
	पूर्ण अन्यथा अगर (rev == AM35XX_REV_ES1_0 || rev == AM35XX_REV_ES1_1) अणु
		h = am35xx_hwmod_ocp_अगरs;
		h_sham = am35xx_sham_hwmod_ocp_अगरs;
	पूर्ण अन्यथा अगर (rev == OMAP3630_REV_ES1_0 || rev == OMAP3630_REV_ES1_1 ||
		   rev == OMAP3630_REV_ES1_2) अणु
		h = omap36xx_hwmod_ocp_अगरs;
		h_sham = omap36xx_sham_hwmod_ocp_अगरs;
	पूर्ण अन्यथा अणु
		WARN(1, "OMAP3 hwmod family init: unknown chip type\n");
		वापस -EINVAL;
	पूर्ण

	r = omap_hwmod_रेजिस्टर_links(h);
	अगर (r < 0)
		वापस r;

	/*
	 * Register crypto hwmod links only अगर they are not disabled in DT.
	 * If DT inक्रमmation is missing, enable them only क्रम GP devices.
	 */

	bus = of_find_node_by_name(शून्य, "ocp");

	अगर (h_sham && omap3xxx_hwmod_is_hs_ip_block_usable(bus, "sham")) अणु
		r = omap_hwmod_रेजिस्टर_links(h_sham);
		अगर (r < 0)
			जाओ put_node;
	पूर्ण

	of_node_put(bus);

	/*
	 * Register hwmod links specअगरic to certain ES levels of a
	 * particular family of silicon (e.g., 34xx ES1.0)
	 */
	h = शून्य;
	अगर (rev == OMAP3430_REV_ES1_0) अणु
		h = omap3430es1_hwmod_ocp_अगरs;
	पूर्ण अन्यथा अगर (rev == OMAP3430_REV_ES2_0 || rev == OMAP3430_REV_ES2_1 ||
		   rev == OMAP3430_REV_ES3_0 || rev == OMAP3430_REV_ES3_1 ||
		   rev == OMAP3430_REV_ES3_1_2) अणु
		h = omap3430es2plus_hwmod_ocp_अगरs;
	पूर्ण

	अगर (h) अणु
		r = omap_hwmod_रेजिस्टर_links(h);
		अगर (r < 0)
			वापस r;
	पूर्ण

	h = शून्य;
	अगर (rev == OMAP3430_REV_ES1_0 || rev == OMAP3430_REV_ES2_0 ||
	    rev == OMAP3430_REV_ES2_1) अणु
		h = omap3430_pre_es3_hwmod_ocp_अगरs;
	पूर्ण अन्यथा अगर (rev == OMAP3430_REV_ES3_0 || rev == OMAP3430_REV_ES3_1 ||
		   rev == OMAP3430_REV_ES3_1_2) अणु
		h = omap3430_es3plus_hwmod_ocp_अगरs;
	पूर्ण

	अगर (h)
		r = omap_hwmod_रेजिस्टर_links(h);
	अगर (r < 0)
		वापस r;

	/*
	 * DSS code presumes that dss_core hwmod is handled first,
	 * _beक्रमe_ any other DSS related hwmods so रेजिस्टर common
	 * DSS hwmod links last to ensure that dss_core is alपढ़ोy
	 * रेजिस्टरed.  Otherwise some change things may happen, क्रम
	 * ex. अगर dispc is handled beक्रमe dss_core and DSS is enabled
	 * in bootloader DISPC will be reset with outमाला_दो enabled
	 * which someबार leads to unrecoverable L3 error.  XXX The
	 * दीर्घ-term fix to this is to ensure hwmods are set up in
	 * dependency order in the hwmod core code.
	 */
	r = omap_hwmod_रेजिस्टर_links(omap3xxx_dss_hwmod_ocp_अगरs);

	वापस r;

put_node:
	of_node_put(bus);
	वापस r;
पूर्ण
