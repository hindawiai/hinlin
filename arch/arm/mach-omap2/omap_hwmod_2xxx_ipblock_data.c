<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap_hwmod_2xxx_ipblock_data.c - common IP block data क्रम OMAP2xxx
 *
 * Copyright (C) 2011 Nokia Corporation
 * Paul Walmsley
 */

#समावेश <linux/types.h>

#समावेश "omap_hwmod.h"
#समावेश "omap_hwmod_common_data.h"
#समावेश "cm-regbits-24xx.h"
#समावेश "prm-regbits-24xx.h"
#समावेश "wd_timer.h"

/*
 * 'dispc' class
 * display controller
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap2_dispc_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_SIDLEMODE | SYSC_HAS_MIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
			   MSTANDBY_FORCE | MSTANDBY_NO | MSTANDBY_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

काष्ठा omap_hwmod_class omap2_dispc_hwmod_class = अणु
	.name	= "dispc",
	.sysc	= &omap2_dispc_sysc,
पूर्ण;

/* OMAP2xxx Timer Common */
अटल काष्ठा omap_hwmod_class_sysconfig omap2xxx_समयr_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_SIDLEMODE | SYSC_HAS_CLOCKACTIVITY |
			   SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

काष्ठा omap_hwmod_class omap2xxx_समयr_hwmod_class = अणु
	.name	= "timer",
	.sysc	= &omap2xxx_समयr_sysc,
पूर्ण;

/*
 * 'wd_timer' class
 * 32-bit watchकरोg upward counter that generates a pulse on the reset pin on
 * overflow condition
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap2xxx_wd_समयr_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_EMUFREE | SYSC_HAS_SOFTRESET |
			   SYSC_HAS_AUTOIDLE | SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

काष्ठा omap_hwmod_class omap2xxx_wd_समयr_hwmod_class = अणु
	.name		= "wd_timer",
	.sysc		= &omap2xxx_wd_समयr_sysc,
	.pre_shutकरोwn	= &omap2_wd_समयr_disable,
	.reset		= &omap2_wd_समयr_reset,
पूर्ण;

/*
 * 'gpio' class
 * general purpose io module
 */
अटल काष्ठा omap_hwmod_class_sysconfig omap2xxx_gpio_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE |
			   SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

काष्ठा omap_hwmod_class omap2xxx_gpio_hwmod_class = अणु
	.name = "gpio",
	.sysc = &omap2xxx_gpio_sysc,
पूर्ण;

/*
 * 'mailbox' class
 * mailbox module allowing communication between the on-chip processors
 * using a queued mailbox-पूर्णांकerrupt mechanism.
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap2xxx_mailbox_sysc = अणु
	.rev_offs	= 0x000,
	.sysc_offs	= 0x010,
	.syss_offs	= 0x014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

काष्ठा omap_hwmod_class omap2xxx_mailbox_hwmod_class = अणु
	.name	= "mailbox",
	.sysc	= &omap2xxx_mailbox_sysc,
पूर्ण;

/*
 * 'mcspi' class
 * multichannel serial port पूर्णांकerface (mcspi) / master/slave synchronous serial
 * bus
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap2xxx_mcspi_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
				SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
				SYSC_HAS_AUTOIDLE | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

काष्ठा omap_hwmod_class omap2xxx_mcspi_class = अणु
	.name	= "mcspi",
	.sysc	= &omap2xxx_mcspi_sysc,
पूर्ण;

/*
 * 'gpmc' class
 * general purpose memory controller
 */

अटल काष्ठा omap_hwmod_class_sysconfig omap2xxx_gpmc_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= (SYSC_HAS_AUTOIDLE | SYSC_HAS_SIDLEMODE |
			   SYSC_HAS_SOFTRESET | SYSS_HAS_RESET_STATUS),
	.idlemodes	= (SIDLE_FORCE | SIDLE_NO | SIDLE_SMART),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap2xxx_gpmc_hwmod_class = अणु
	.name	= "gpmc",
	.sysc	= &omap2xxx_gpmc_sysc,
पूर्ण;

/*
 * IP blocks
 */

/* L3 */
काष्ठा omap_hwmod omap2xxx_l3_मुख्य_hwmod = अणु
	.name		= "l3_main",
	.class		= &l3_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* L4 CORE */
काष्ठा omap_hwmod omap2xxx_l4_core_hwmod = अणु
	.name		= "l4_core",
	.class		= &l4_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* L4 WKUP */
काष्ठा omap_hwmod omap2xxx_l4_wkup_hwmod = अणु
	.name		= "l4_wkup",
	.class		= &l4_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* MPU */
काष्ठा omap_hwmod omap2xxx_mpu_hwmod = अणु
	.name		= "mpu",
	.class		= &mpu_hwmod_class,
	.मुख्य_clk	= "mpu_ck",
पूर्ण;

/* IVA2 */
काष्ठा omap_hwmod omap2xxx_iva_hwmod = अणु
	.name		= "iva",
	.class		= &iva_hwmod_class,
पूर्ण;

/* समयr3 */
काष्ठा omap_hwmod omap2xxx_समयr3_hwmod = अणु
	.name		= "timer3",
	.मुख्य_clk	= "gpt3_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPT3_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_समयr_hwmod_class,
	.flags          = HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr4 */
काष्ठा omap_hwmod omap2xxx_समयr4_hwmod = अणु
	.name		= "timer4",
	.मुख्य_clk	= "gpt4_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPT4_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_समयr_hwmod_class,
	.flags          = HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr5 */
काष्ठा omap_hwmod omap2xxx_समयr5_hwmod = अणु
	.name		= "timer5",
	.मुख्य_clk	= "gpt5_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPT5_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_समयr_hwmod_class,
	.flags          = HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr6 */
काष्ठा omap_hwmod omap2xxx_समयr6_hwmod = अणु
	.name		= "timer6",
	.मुख्य_clk	= "gpt6_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPT6_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_समयr_hwmod_class,
	.flags          = HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr7 */
काष्ठा omap_hwmod omap2xxx_समयr7_hwmod = अणु
	.name		= "timer7",
	.मुख्य_clk	= "gpt7_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPT7_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_समयr_hwmod_class,
	.flags          = HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr8 */
काष्ठा omap_hwmod omap2xxx_समयr8_hwmod = अणु
	.name		= "timer8",
	.मुख्य_clk	= "gpt8_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPT8_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_समयr_hwmod_class,
	.flags          = HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr9 */
काष्ठा omap_hwmod omap2xxx_समयr9_hwmod = अणु
	.name		= "timer9",
	.मुख्य_clk	= "gpt9_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPT9_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_समयr_hwmod_class,
	.flags          = HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr10 */
काष्ठा omap_hwmod omap2xxx_समयr10_hwmod = अणु
	.name		= "timer10",
	.मुख्य_clk	= "gpt10_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPT10_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_समयr_hwmod_class,
	.flags          = HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr11 */
काष्ठा omap_hwmod omap2xxx_समयr11_hwmod = अणु
	.name		= "timer11",
	.मुख्य_clk	= "gpt11_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPT11_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_समयr_hwmod_class,
	.flags          = HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* समयr12 */
काष्ठा omap_hwmod omap2xxx_समयr12_hwmod = अणु
	.name		= "timer12",
	.मुख्य_clk	= "gpt12_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPT12_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_समयr_hwmod_class,
	.flags          = HWMOD_SET_DEFAULT_CLOCKACT,
पूर्ण;

/* wd_समयr2 */
काष्ठा omap_hwmod omap2xxx_wd_समयr2_hwmod = अणु
	.name		= "wd_timer2",
	.class		= &omap2xxx_wd_समयr_hwmod_class,
	.मुख्य_clk	= "mpu_wdt_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = WKUP_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_MPU_WDT_SHIFT,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* UART1 */

काष्ठा omap_hwmod omap2xxx_uart1_hwmod = अणु
	.name		= "uart1",
	.मुख्य_clk	= "uart1_fck",
	.flags		= DEBUG_OMAP2UART1_FLAGS | HWMOD_SWSUP_SIDLE_ACT,
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_EN_UART1_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2_uart_class,
पूर्ण;

/* UART2 */

काष्ठा omap_hwmod omap2xxx_uart2_hwmod = अणु
	.name		= "uart2",
	.मुख्य_clk	= "uart2_fck",
	.flags		= DEBUG_OMAP2UART2_FLAGS | HWMOD_SWSUP_SIDLE_ACT,
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_EN_UART2_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2_uart_class,
पूर्ण;

/* UART3 */

काष्ठा omap_hwmod omap2xxx_uart3_hwmod = अणु
	.name		= "uart3",
	.मुख्य_clk	= "uart3_fck",
	.flags		= DEBUG_OMAP2UART3_FLAGS | HWMOD_SWSUP_SIDLE_ACT,
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 2,
			.idlest_idle_bit = OMAP24XX_EN_UART3_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2_uart_class,
पूर्ण;

/* dss */

अटल काष्ठा omap_hwmod_opt_clk dss_opt_clks[] = अणु
	/*
	 * The DSS HW needs all DSS घड़ीs enabled during reset. The dss_core
	 * driver करोes not use these घड़ीs.
	 */
	अणु .role = "tv_clk", .clk = "dss_54m_fck" पूर्ण,
	अणु .role = "sys_clk", .clk = "dss2_fck" पूर्ण,
पूर्ण;

काष्ठा omap_hwmod omap2xxx_dss_core_hwmod = अणु
	.name		= "dss_core",
	.class		= &omap2_dss_hwmod_class,
	.मुख्य_clk	= "dss1_fck", /* instead of dss_fck */
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
		पूर्ण,
	पूर्ण,
	.opt_clks	= dss_opt_clks,
	.opt_clks_cnt = ARRAY_SIZE(dss_opt_clks),
	.flags		= HWMOD_NO_IDLEST | HWMOD_CONTROL_OPT_CLKS_IN_RESET,
पूर्ण;

काष्ठा omap_hwmod omap2xxx_dss_dispc_hwmod = अणु
	.name		= "dss_dispc",
	.class		= &omap2_dispc_hwmod_class,
	.मुख्य_clk	= "dss1_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
		पूर्ण,
	पूर्ण,
	.flags		= HWMOD_NO_IDLEST,
	.dev_attr	= &omap2_3_dss_dispc_dev_attr,
पूर्ण;

अटल काष्ठा omap_hwmod_opt_clk dss_rfbi_opt_clks[] = अणु
	अणु .role = "ick", .clk = "dss_ick" पूर्ण,
पूर्ण;

काष्ठा omap_hwmod omap2xxx_dss_rfbi_hwmod = अणु
	.name		= "dss_rfbi",
	.class		= &omap2_rfbi_hwmod_class,
	.मुख्य_clk	= "dss1_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
		पूर्ण,
	पूर्ण,
	.opt_clks	= dss_rfbi_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dss_rfbi_opt_clks),
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

काष्ठा omap_hwmod omap2xxx_dss_venc_hwmod = अणु
	.name		= "dss_venc",
	.class		= &omap2_venc_hwmod_class,
	.मुख्य_clk	= "dss_54m_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
		पूर्ण,
	पूर्ण,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* gpio1 */
काष्ठा omap_hwmod omap2xxx_gpio1_hwmod = अणु
	.name		= "gpio1",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.मुख्य_clk	= "gpios_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = WKUP_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPIOS_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_gpio_hwmod_class,
पूर्ण;

/* gpio2 */
काष्ठा omap_hwmod omap2xxx_gpio2_hwmod = अणु
	.name		= "gpio2",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.मुख्य_clk	= "gpios_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = WKUP_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPIOS_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_gpio_hwmod_class,
पूर्ण;

/* gpio3 */
काष्ठा omap_hwmod omap2xxx_gpio3_hwmod = अणु
	.name		= "gpio3",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.मुख्य_clk	= "gpios_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = WKUP_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPIOS_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_gpio_hwmod_class,
पूर्ण;

/* gpio4 */
काष्ठा omap_hwmod omap2xxx_gpio4_hwmod = अणु
	.name		= "gpio4",
	.flags		= HWMOD_CONTROL_OPT_CLKS_IN_RESET,
	.मुख्य_clk	= "gpios_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = WKUP_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_GPIOS_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_gpio_hwmod_class,
पूर्ण;

/* mcspi1 */
काष्ठा omap_hwmod omap2xxx_mcspi1_hwmod = अणु
	.name		= "mcspi1",
	.मुख्य_clk	= "mcspi1_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_MCSPI1_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_mcspi_class,
पूर्ण;

/* mcspi2 */
काष्ठा omap_hwmod omap2xxx_mcspi2_hwmod = अणु
	.name		= "mcspi2",
	.मुख्य_clk	= "mcspi2_fck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 1,
			.idlest_idle_bit = OMAP24XX_ST_MCSPI2_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_mcspi_class,
पूर्ण;

/* gpmc */
काष्ठा omap_hwmod omap2xxx_gpmc_hwmod = अणु
	.name		= "gpmc",
	.class		= &omap2xxx_gpmc_hwmod_class,
	.मुख्य_clk	= "gpmc_fck",
	/* Skip reset क्रम CONFIG_OMAP_GPMC_DEBUG क्रम bootloader timings */
	.flags		= HWMOD_NO_IDLEST | DEBUG_OMAP_GPMC_HWMOD_FLAGS,
	.prcm		= अणु
		.omap2	= अणु
			.module_offs = CORE_MOD,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* RNG */

अटल काष्ठा omap_hwmod_class_sysconfig omap2_rng_sysc = अणु
	.rev_offs	= 0x3c,
	.sysc_offs	= 0x40,
	.syss_offs	= 0x44,
	.sysc_flags	= (SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE |
			   SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap2_rng_hwmod_class = अणु
	.name		= "rng",
	.sysc		= &omap2_rng_sysc,
पूर्ण;

काष्ठा omap_hwmod omap2xxx_rng_hwmod = अणु
	.name		= "rng",
	.मुख्य_clk	= "l4_ck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 4,
			.idlest_idle_bit = OMAP24XX_ST_RNG_SHIFT,
		पूर्ण,
	पूर्ण,
	/*
	 * XXX The first पढ़ो from the SYSSTATUS रेजिस्टर of the RNG
	 * after the SYSCONFIG SOFTRESET bit is set triggers an
	 * imprecise बाह्यal पात.  It's unclear why this happens.
	 * Until this is analyzed, skip the IP block reset.
	 */
	.flags		= HWMOD_INIT_NO_RESET,
	.class		= &omap2_rng_hwmod_class,
पूर्ण;

/* SHAM */

अटल काष्ठा omap_hwmod_class_sysconfig omap2_sham_sysc = अणु
	.rev_offs	= 0x5c,
	.sysc_offs	= 0x60,
	.syss_offs	= 0x64,
	.sysc_flags	= (SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE |
			   SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap2xxx_sham_class = अणु
	.name	= "sham",
	.sysc	= &omap2_sham_sysc,
पूर्ण;

काष्ठा omap_hwmod omap2xxx_sham_hwmod = अणु
	.name		= "sham",
	.मुख्य_clk	= "l4_ck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 4,
			.idlest_idle_bit = OMAP24XX_ST_SHA_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_sham_class,
पूर्ण;

/* AES */

अटल काष्ठा omap_hwmod_class_sysconfig omap2_aes_sysc = अणु
	.rev_offs	= 0x44,
	.sysc_offs	= 0x48,
	.syss_offs	= 0x4c,
	.sysc_flags	= (SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE |
			   SYSS_HAS_RESET_STATUS),
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class omap2xxx_aes_class = अणु
	.name	= "aes",
	.sysc	= &omap2_aes_sysc,
पूर्ण;

काष्ठा omap_hwmod omap2xxx_aes_hwmod = अणु
	.name		= "aes",
	.मुख्य_clk	= "l4_ck",
	.prcm		= अणु
		.omap2 = अणु
			.module_offs = CORE_MOD,
			.idlest_reg_id = 4,
			.idlest_idle_bit = OMAP24XX_ST_AES_SHIFT,
		पूर्ण,
	पूर्ण,
	.class		= &omap2xxx_aes_class,
पूर्ण;
