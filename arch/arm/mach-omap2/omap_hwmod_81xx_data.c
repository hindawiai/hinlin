<शैली गुरु>
/*
 * DM81xx hwmod data.
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
 *
 */

#समावेश <linux/types.h>

#समावेश <linux/platक्रमm_data/hsmmc-omap.h>

#समावेश "omap_hwmod_common_data.h"
#समावेश "cm81xx.h"
#समावेश "ti81xx.h"
#समावेश "wd_timer.h"

/*
 * DM816X hardware modules पूर्णांकegration data
 *
 * Note: This is incomplete and at present, not generated from h/w database.
 */

/*
 * Common alwon .clkctrl_offs from dm814x TRM "Table 2-278. CM_ALWON REGISTERS"
 * also dm816x TRM 18.7.17 CM_ALWON device रेजिस्टर values minus 0x1400.
 */
#घोषणा DM81XX_CM_ALWON_MCASP0_CLKCTRL		0x140
#घोषणा DM81XX_CM_ALWON_MCASP1_CLKCTRL		0x144
#घोषणा DM81XX_CM_ALWON_MCASP2_CLKCTRL		0x148
#घोषणा DM81XX_CM_ALWON_MCBSP_CLKCTRL		0x14c
#घोषणा DM81XX_CM_ALWON_UART_0_CLKCTRL		0x150
#घोषणा DM81XX_CM_ALWON_UART_1_CLKCTRL		0x154
#घोषणा DM81XX_CM_ALWON_UART_2_CLKCTRL		0x158
#घोषणा DM81XX_CM_ALWON_GPIO_0_CLKCTRL		0x15c
#घोषणा DM81XX_CM_ALWON_GPIO_1_CLKCTRL		0x160
#घोषणा DM81XX_CM_ALWON_I2C_0_CLKCTRL		0x164
#घोषणा DM81XX_CM_ALWON_I2C_1_CLKCTRL		0x168
#घोषणा DM81XX_CM_ALWON_WDTIMER_CLKCTRL		0x18c
#घोषणा DM81XX_CM_ALWON_SPI_CLKCTRL		0x190
#घोषणा DM81XX_CM_ALWON_MAILBOX_CLKCTRL		0x194
#घोषणा DM81XX_CM_ALWON_SPINBOX_CLKCTRL		0x198
#घोषणा DM81XX_CM_ALWON_MMUDATA_CLKCTRL		0x19c
#घोषणा DM81XX_CM_ALWON_MMUCFG_CLKCTRL		0x1a8
#घोषणा DM81XX_CM_ALWON_CONTROL_CLKCTRL		0x1c4
#घोषणा DM81XX_CM_ALWON_GPMC_CLKCTRL		0x1d0
#घोषणा DM81XX_CM_ALWON_ETHERNET_0_CLKCTRL	0x1d4
#घोषणा DM81XX_CM_ALWON_L3_CLKCTRL		0x1e4
#घोषणा DM81XX_CM_ALWON_L4HS_CLKCTRL		0x1e8
#घोषणा DM81XX_CM_ALWON_L4LS_CLKCTRL		0x1ec
#घोषणा DM81XX_CM_ALWON_RTC_CLKCTRL		0x1f0
#घोषणा DM81XX_CM_ALWON_TPCC_CLKCTRL		0x1f4
#घोषणा DM81XX_CM_ALWON_TPTC0_CLKCTRL		0x1f8
#घोषणा DM81XX_CM_ALWON_TPTC1_CLKCTRL		0x1fc
#घोषणा DM81XX_CM_ALWON_TPTC2_CLKCTRL		0x200
#घोषणा DM81XX_CM_ALWON_TPTC3_CLKCTRL		0x204

/* Registers specअगरic to dm814x */
#घोषणा DM814X_CM_ALWON_MCASP_3_4_5_CLKCTRL	0x16c
#घोषणा DM814X_CM_ALWON_ATL_CLKCTRL		0x170
#घोषणा DM814X_CM_ALWON_MLB_CLKCTRL		0x174
#घोषणा DM814X_CM_ALWON_PATA_CLKCTRL		0x178
#घोषणा DM814X_CM_ALWON_UART_3_CLKCTRL		0x180
#घोषणा DM814X_CM_ALWON_UART_4_CLKCTRL		0x184
#घोषणा DM814X_CM_ALWON_UART_5_CLKCTRL		0x188
#घोषणा DM814X_CM_ALWON_OCM_0_CLKCTRL		0x1b4
#घोषणा DM814X_CM_ALWON_VCP_CLKCTRL		0x1b8
#घोषणा DM814X_CM_ALWON_MPU_CLKCTRL		0x1dc
#घोषणा DM814X_CM_ALWON_DEBUGSS_CLKCTRL		0x1e0
#घोषणा DM814X_CM_ALWON_DCAN_0_1_CLKCTRL	0x218
#घोषणा DM814X_CM_ALWON_MMCHS_0_CLKCTRL		0x21c
#घोषणा DM814X_CM_ALWON_MMCHS_1_CLKCTRL		0x220
#घोषणा DM814X_CM_ALWON_MMCHS_2_CLKCTRL		0x224
#घोषणा DM814X_CM_ALWON_CUST_EFUSE_CLKCTRL	0x228

/* Registers specअगरic to dm816x */
#घोषणा DM816X_DM_ALWON_BASE		0x1400
#घोषणा DM816X_CM_ALWON_TIMER_1_CLKCTRL	(0x1570 - DM816X_DM_ALWON_BASE)
#घोषणा DM816X_CM_ALWON_TIMER_2_CLKCTRL	(0x1574 - DM816X_DM_ALWON_BASE)
#घोषणा DM816X_CM_ALWON_TIMER_3_CLKCTRL	(0x1578 - DM816X_DM_ALWON_BASE)
#घोषणा DM816X_CM_ALWON_TIMER_4_CLKCTRL	(0x157c - DM816X_DM_ALWON_BASE)
#घोषणा DM816X_CM_ALWON_TIMER_5_CLKCTRL	(0x1580 - DM816X_DM_ALWON_BASE)
#घोषणा DM816X_CM_ALWON_TIMER_6_CLKCTRL	(0x1584 - DM816X_DM_ALWON_BASE)
#घोषणा DM816X_CM_ALWON_TIMER_7_CLKCTRL	(0x1588 - DM816X_DM_ALWON_BASE)
#घोषणा DM816X_CM_ALWON_SDIO_CLKCTRL	(0x15b0 - DM816X_DM_ALWON_BASE)
#घोषणा DM816X_CM_ALWON_OCMC_0_CLKCTRL	(0x15b4 - DM816X_DM_ALWON_BASE)
#घोषणा DM816X_CM_ALWON_OCMC_1_CLKCTRL	(0x15b8 - DM816X_DM_ALWON_BASE)
#घोषणा DM816X_CM_ALWON_ETHERNET_1_CLKCTRL (0x15d8 - DM816X_DM_ALWON_BASE)
#घोषणा DM816X_CM_ALWON_MPU_CLKCTRL	(0x15dc - DM816X_DM_ALWON_BASE)
#घोषणा DM816X_CM_ALWON_SR_0_CLKCTRL	(0x1608 - DM816X_DM_ALWON_BASE)
#घोषणा DM816X_CM_ALWON_SR_1_CLKCTRL	(0x160c - DM816X_DM_ALWON_BASE)

/*
 * The शेष .clkctrl_offs field is offset from CM_DEFAULT, that's
 * TRM 18.7.6 CM_DEFAULT device रेजिस्टर values minus 0x500
 */
#घोषणा DM81XX_CM_DEFAULT_OFFSET	0x500
#घोषणा DM81XX_CM_DEFAULT_USB_CLKCTRL	(0x558 - DM81XX_CM_DEFAULT_OFFSET)
#घोषणा DM81XX_CM_DEFAULT_SATA_CLKCTRL	(0x560 - DM81XX_CM_DEFAULT_OFFSET)

/* L3 Interconnect entries घड़ीed at 125, 250 and 500MHz */
अटल काष्ठा omap_hwmod dm81xx_alwon_l3_slow_hwmod = अणु
	.name		= "alwon_l3_slow",
	.clkdm_name	= "alwon_l3s_clkdm",
	.class		= &l3_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_शेष_l3_slow_hwmod = अणु
	.name		= "default_l3_slow",
	.clkdm_name	= "default_l3_slow_clkdm",
	.class		= &l3_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_alwon_l3_med_hwmod = अणु
	.name		= "l3_med",
	.clkdm_name	= "alwon_l3_med_clkdm",
	.class		= &l3_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/*
 * L4 standard peripherals, see TRM table 1-12 क्रम devices using this.
 * See TRM table 1-73 क्रम devices using the 125MHz SYSCLK6 घड़ी.
 */
अटल काष्ठा omap_hwmod dm81xx_l4_ls_hwmod = अणु
	.name		= "l4_ls",
	.clkdm_name	= "alwon_l3s_clkdm",
	.class		= &l4_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/*
 * L4 high-speed peripherals. For devices using this, please see the TRM
 * table 1-13. On dm816x, only EMAC, MDIO and SATA use this. See also TRM
 * table 1-73 क्रम devices using 250MHz SYSCLK5 घड़ी.
 */
अटल काष्ठा omap_hwmod dm81xx_l4_hs_hwmod = अणु
	.name		= "l4_hs",
	.clkdm_name	= "alwon_l3_med_clkdm",
	.class		= &l4_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

/* L3 slow -> L4 ls peripheral पूर्णांकerface running at 125MHz */
अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_alwon_l3_slow__l4_ls = अणु
	.master	= &dm81xx_alwon_l3_slow_hwmod,
	.slave	= &dm81xx_l4_ls_hwmod,
	.user	= OCP_USER_MPU,
पूर्ण;

/* L3 med -> L4 fast peripheral पूर्णांकerface running at 250MHz */
अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_alwon_l3_slow__l4_hs = अणु
	.master	= &dm81xx_alwon_l3_med_hwmod,
	.slave	= &dm81xx_l4_hs_hwmod,
	.user	= OCP_USER_MPU,
पूर्ण;

/* MPU */
अटल काष्ठा omap_hwmod dm814x_mpu_hwmod = अणु
	.name		= "mpu",
	.clkdm_name	= "alwon_l3s_clkdm",
	.class		= &mpu_hwmod_class,
	.flags		= HWMOD_INIT_NO_IDLE,
	.मुख्य_clk	= "mpu_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM814X_CM_ALWON_MPU_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm814x_mpu__alwon_l3_slow = अणु
	.master		= &dm814x_mpu_hwmod,
	.slave		= &dm81xx_alwon_l3_slow_hwmod,
	.user		= OCP_USER_MPU,
पूर्ण;

/* L3 med peripheral पूर्णांकerface running at 200MHz */
अटल काष्ठा omap_hwmod_ocp_अगर dm814x_mpu__alwon_l3_med = अणु
	.master	= &dm814x_mpu_hwmod,
	.slave	= &dm81xx_alwon_l3_med_hwmod,
	.user	= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod dm816x_mpu_hwmod = अणु
	.name		= "mpu",
	.clkdm_name	= "alwon_mpu_clkdm",
	.class		= &mpu_hwmod_class,
	.flags		= HWMOD_INIT_NO_IDLE,
	.मुख्य_clk	= "mpu_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM816X_CM_ALWON_MPU_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm816x_mpu__alwon_l3_slow = अणु
	.master		= &dm816x_mpu_hwmod,
	.slave		= &dm81xx_alwon_l3_slow_hwmod,
	.user		= OCP_USER_MPU,
पूर्ण;

/* L3 med peripheral पूर्णांकerface running at 250MHz */
अटल काष्ठा omap_hwmod_ocp_अगर dm816x_mpu__alwon_l3_med = अणु
	.master	= &dm816x_mpu_hwmod,
	.slave	= &dm81xx_alwon_l3_med_hwmod,
	.user	= OCP_USER_MPU,
पूर्ण;

/* RTC */
अटल काष्ठा omap_hwmod_class_sysconfig ti81xx_rtc_sysc = अणु
	.rev_offs	= 0x74,
	.sysc_offs	= 0x78,
	.sysc_flags	= SYSC_HAS_SIDLEMODE,
	.idlemodes	= SIDLE_FORCE | SIDLE_NO |
			  SIDLE_SMART | SIDLE_SMART_WKUP,
	.sysc_fields	= &omap_hwmod_sysc_type3,
पूर्ण;

अटल काष्ठा omap_hwmod_class ti81xx_rtc_hwmod_class = अणु
	.name		= "rtc",
	.sysc		= &ti81xx_rtc_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod ti81xx_rtc_hwmod = अणु
	.name		= "rtc",
	.class		= &ti81xx_rtc_hwmod_class,
	.clkdm_name	= "alwon_l3s_clkdm",
	.flags		= HWMOD_NO_IDLEST,
	.मुख्य_clk	= "sysclk18_ck",
	.prcm		= अणु
		.omap4	= अणु
			.clkctrl_offs = DM81XX_CM_ALWON_RTC_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर ti81xx_l4_ls__rtc = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &ti81xx_rtc_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

/* UART common */
अटल काष्ठा omap_hwmod_class_sysconfig uart_sysc = अणु
	.rev_offs	= 0x50,
	.sysc_offs	= 0x54,
	.syss_offs	= 0x58,
	.sysc_flags	= SYSC_HAS_ENAWAKEUP | SYSC_HAS_SIDLEMODE |
				SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE |
				SYSS_HAS_RESET_STATUS,
	.idlemodes	= SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
				MSTANDBY_SMART_WKUP,
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class uart_class = अणु
	.name = "uart",
	.sysc = &uart_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_uart1_hwmod = अणु
	.name		= "uart1",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "sysclk10_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_UART_0_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &uart_class,
	.flags		= DEBUG_TI81XXUART1_FLAGS,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__uart1 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_uart1_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_uart2_hwmod = अणु
	.name		= "uart2",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "sysclk10_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_UART_1_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &uart_class,
	.flags		= DEBUG_TI81XXUART2_FLAGS,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__uart2 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_uart2_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_uart3_hwmod = अणु
	.name		= "uart3",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "sysclk10_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_UART_2_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &uart_class,
	.flags		= DEBUG_TI81XXUART3_FLAGS,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__uart3 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_uart3_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_class_sysconfig wd_समयr_sysc = अणु
	.rev_offs	= 0x0,
	.sysc_offs	= 0x10,
	.syss_offs	= 0x14,
	.sysc_flags	= SYSC_HAS_EMUFREE | SYSC_HAS_SOFTRESET |
				SYSS_HAS_RESET_STATUS,
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class wd_समयr_class = अणु
	.name		= "wd_timer",
	.sysc		= &wd_समयr_sysc,
	.pre_shutकरोwn	= &omap2_wd_समयr_disable,
	.reset		= &omap2_wd_समयr_reset,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_wd_समयr_hwmod = अणु
	.name		= "wd_timer",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "sysclk18_ck",
	.flags		= HWMOD_NO_IDLEST,
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_WDTIMER_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &wd_समयr_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__wd_समयr1 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_wd_समयr_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

/* I2C common */
अटल काष्ठा omap_hwmod_class_sysconfig i2c_sysc = अणु
	.rev_offs	= 0x0,
	.sysc_offs	= 0x10,
	.syss_offs	= 0x90,
	.sysc_flags	= SYSC_HAS_SIDLEMODE |
				SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
				SYSC_HAS_AUTOIDLE,
	.idlemodes	= SIDLE_FORCE | SIDLE_NO | SIDLE_SMART,
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class i2c_class = अणु
	.name = "i2c",
	.sysc = &i2c_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_i2c1_hwmod = अणु
	.name		= "i2c1",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "sysclk10_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_I2C_0_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &i2c_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__i2c1 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_i2c1_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_i2c2_hwmod = अणु
	.name		= "i2c2",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "sysclk10_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_I2C_1_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &i2c_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__i2c2 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_i2c2_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_class_sysconfig dm81xx_elm_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
				SYSC_HAS_SOFTRESET |
				SYSS_HAS_RESET_STATUS,
	.idlemodes	= SIDLE_FORCE | SIDLE_NO | SIDLE_SMART,
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class dm81xx_elm_hwmod_class = अणु
	.name = "elm",
	.sysc = &dm81xx_elm_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_elm_hwmod = अणु
	.name		= "elm",
	.clkdm_name	= "alwon_l3s_clkdm",
	.class		= &dm81xx_elm_hwmod_class,
	.मुख्य_clk	= "sysclk6_ck",
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__elm = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_elm_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_class_sysconfig dm81xx_gpio_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0114,
	.sysc_flags	= SYSC_HAS_AUTOIDLE | SYSC_HAS_ENAWAKEUP |
				SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
				SYSS_HAS_RESET_STATUS,
	.idlemodes	= SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
				SIDLE_SMART_WKUP,
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class dm81xx_gpio_hwmod_class = अणु
	.name	= "gpio",
	.sysc	= &dm81xx_gpio_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod_opt_clk gpio1_opt_clks[] = अणु
	अणु .role = "dbclk", .clk = "sysclk18_ck" पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_gpio1_hwmod = अणु
	.name		= "gpio1",
	.clkdm_name	= "alwon_l3s_clkdm",
	.class		= &dm81xx_gpio_hwmod_class,
	.मुख्य_clk	= "sysclk6_ck",
	.prcm = अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_GPIO_0_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.opt_clks	= gpio1_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio1_opt_clks),
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__gpio1 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_gpio1_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_opt_clk gpio2_opt_clks[] = अणु
	अणु .role = "dbclk", .clk = "sysclk18_ck" पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_gpio2_hwmod = अणु
	.name		= "gpio2",
	.clkdm_name	= "alwon_l3s_clkdm",
	.class		= &dm81xx_gpio_hwmod_class,
	.मुख्य_clk	= "sysclk6_ck",
	.prcm = अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_GPIO_1_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.opt_clks	= gpio2_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio2_opt_clks),
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__gpio2 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_gpio2_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_opt_clk gpio3_opt_clks[] = अणु
	अणु .role = "dbclk", .clk = "sysclk18_ck" पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_gpio3_hwmod = अणु
	.name		= "gpio3",
	.clkdm_name	= "alwon_l3s_clkdm",
	.class		= &dm81xx_gpio_hwmod_class,
	.मुख्य_clk	= "sysclk6_ck",
	.prcm = अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_GPIO_1_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.opt_clks	= gpio3_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio3_opt_clks),
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__gpio3 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_gpio3_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_opt_clk gpio4_opt_clks[] = अणु
	अणु .role = "dbclk", .clk = "sysclk18_ck" पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_gpio4_hwmod = अणु
	.name		= "gpio4",
	.clkdm_name	= "alwon_l3s_clkdm",
	.class		= &dm81xx_gpio_hwmod_class,
	.मुख्य_clk	= "sysclk6_ck",
	.prcm = अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_GPIO_1_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.opt_clks	= gpio4_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(gpio4_opt_clks),
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__gpio4 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_gpio4_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_class_sysconfig dm81xx_gpmc_sysc = अणु
	.rev_offs	= 0x0,
	.sysc_offs	= 0x10,
	.syss_offs	= 0x14,
	.sysc_flags	= SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET |
				SYSC_HAS_AUTOIDLE | SYSS_HAS_RESET_STATUS,
	.idlemodes	= SIDLE_FORCE | SIDLE_NO | SIDLE_SMART,
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class dm81xx_gpmc_hwmod_class = अणु
	.name	= "gpmc",
	.sysc	= &dm81xx_gpmc_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_gpmc_hwmod = अणु
	.name		= "gpmc",
	.clkdm_name	= "alwon_l3s_clkdm",
	.class		= &dm81xx_gpmc_hwmod_class,
	.मुख्य_clk	= "sysclk6_ck",
	/* Skip reset क्रम CONFIG_OMAP_GPMC_DEBUG क्रम bootloader timings */
	.flags		= DEBUG_OMAP_GPMC_HWMOD_FLAGS,
	.prcm = अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_GPMC_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_alwon_l3_slow__gpmc = अणु
	.master		= &dm81xx_alwon_l3_slow_hwmod,
	.slave		= &dm81xx_gpmc_hwmod,
	.user		= OCP_USER_MPU,
पूर्ण;

/* USB needs udelay 1 after reset at least on hp t410, use 2 क्रम margin */
अटल काष्ठा omap_hwmod_class_sysconfig dm81xx_usbhsotg_sysc = अणु
	.rev_offs	= 0x0,
	.sysc_offs	= 0x10,
	.srst_udelay	= 2,
	.sysc_flags	= SYSC_HAS_SIDLEMODE | SYSC_HAS_MIDLEMODE |
				SYSC_HAS_SOFTRESET,
	.idlemodes	= SIDLE_SMART | MSTANDBY_FORCE | MSTANDBY_SMART,
	.sysc_fields	= &omap_hwmod_sysc_type2,
पूर्ण;

अटल काष्ठा omap_hwmod_class dm81xx_usbotg_class = अणु
	.name = "usbotg",
	.sysc = &dm81xx_usbhsotg_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod dm814x_usbss_hwmod = अणु
	.name		= "usb_otg_hs",
	.clkdm_name	= "default_l3_slow_clkdm",
	.मुख्य_clk	= "pll260dcoclkldo",	/* 481c5260.adpll.dcoclklकरो */
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_DEFAULT_USB_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &dm81xx_usbotg_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm814x_शेष_l3_slow__usbss = अणु
	.master		= &dm81xx_शेष_l3_slow_hwmod,
	.slave		= &dm814x_usbss_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod dm816x_usbss_hwmod = अणु
	.name		= "usb_otg_hs",
	.clkdm_name	= "default_l3_slow_clkdm",
	.मुख्य_clk	= "sysclk6_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_DEFAULT_USB_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &dm81xx_usbotg_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm816x_शेष_l3_slow__usbss = अणु
	.master		= &dm81xx_शेष_l3_slow_hwmod,
	.slave		= &dm816x_usbss_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_class_sysconfig dm816x_समयr_sysc = अणु
	.rev_offs	= 0x0000,
	.sysc_offs	= 0x0010,
	.syss_offs	= 0x0014,
	.sysc_flags	= SYSC_HAS_SIDLEMODE | SYSC_HAS_SOFTRESET,
	.idlemodes	= SIDLE_FORCE | SIDLE_NO | SIDLE_SMART |
				SIDLE_SMART_WKUP,
	.sysc_fields	= &omap_hwmod_sysc_type2,
पूर्ण;

अटल काष्ठा omap_hwmod_class dm816x_समयr_hwmod_class = अणु
	.name = "timer",
	.sysc = &dm816x_समयr_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod dm816x_समयr3_hwmod = अणु
	.name		= "timer3",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "timer3_fck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM816X_CM_ALWON_TIMER_3_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &dm816x_समयr_hwmod_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm816x_l4_ls__समयr3 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm816x_समयr3_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod dm816x_समयr4_hwmod = अणु
	.name		= "timer4",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "timer4_fck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM816X_CM_ALWON_TIMER_4_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &dm816x_समयr_hwmod_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm816x_l4_ls__समयr4 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm816x_समयr4_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod dm816x_समयr5_hwmod = अणु
	.name		= "timer5",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "timer5_fck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM816X_CM_ALWON_TIMER_5_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &dm816x_समयr_hwmod_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm816x_l4_ls__समयr5 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm816x_समयr5_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod dm816x_समयr6_hwmod = अणु
	.name		= "timer6",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "timer6_fck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM816X_CM_ALWON_TIMER_6_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &dm816x_समयr_hwmod_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm816x_l4_ls__समयr6 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm816x_समयr6_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod dm816x_समयr7_hwmod = अणु
	.name		= "timer7",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "timer7_fck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM816X_CM_ALWON_TIMER_7_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &dm816x_समयr_hwmod_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm816x_l4_ls__समयr7 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm816x_समयr7_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

/* EMAC Ethernet */
अटल काष्ठा omap_hwmod_class_sysconfig dm816x_emac_sysc = अणु
	.rev_offs	= 0x0,
	.sysc_offs	= 0x4,
	.sysc_flags	= SYSC_HAS_SOFTRESET,
	.sysc_fields	= &omap_hwmod_sysc_type2,
पूर्ण;

अटल काष्ठा omap_hwmod_class dm816x_emac_hwmod_class = अणु
	.name		= "emac",
	.sysc		= &dm816x_emac_sysc,
पूर्ण;

/*
 * On dm816x the MDIO is within EMAC0. As the MDIO driver is a separate
 * driver probed beक्रमe EMAC0, we let MDIO करो the घड़ी idling.
 */
अटल काष्ठा omap_hwmod dm816x_emac0_hwmod = अणु
	.name		= "emac0",
	.clkdm_name	= "alwon_ethernet_clkdm",
	.class		= &dm816x_emac_hwmod_class,
	.flags		= HWMOD_NO_IDLEST,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_hs__emac0 = अणु
	.master		= &dm81xx_l4_hs_hwmod,
	.slave		= &dm816x_emac0_hwmod,
	.clk		= "sysclk5_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_class dm81xx_mdio_hwmod_class = अणु
	.name		= "davinci_mdio",
	.sysc		= &dm816x_emac_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_emac0_mdio_hwmod = अणु
	.name		= "davinci_mdio",
	.class		= &dm81xx_mdio_hwmod_class,
	.clkdm_name	= "alwon_ethernet_clkdm",
	.मुख्य_clk	= "sysclk24_ck",
	.flags		= HWMOD_NO_IDLEST,
	/*
	 * REVISIT: This should be moved to the emac0_hwmod
	 * once we have a better way to handle device slaves.
	 */
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_ETHERNET_0_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_emac0__mdio = अणु
	.master		= &dm81xx_l4_hs_hwmod,
	.slave		= &dm81xx_emac0_mdio_hwmod,
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod dm816x_emac1_hwmod = अणु
	.name		= "emac1",
	.clkdm_name	= "alwon_ethernet_clkdm",
	.मुख्य_clk	= "sysclk24_ck",
	.flags		= HWMOD_NO_IDLEST,
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM816X_CM_ALWON_ETHERNET_1_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &dm816x_emac_hwmod_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm816x_l4_hs__emac1 = अणु
	.master		= &dm81xx_l4_hs_hwmod,
	.slave		= &dm816x_emac1_hwmod,
	.clk		= "sysclk5_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_class_sysconfig dm81xx_sata_sysc = अणु
	.rev_offs	= 0x00fc,
	.sysc_offs	= 0x1100,
	.sysc_flags	= SYSC_HAS_SIDLEMODE,
	.idlemodes	= SIDLE_FORCE,
	.sysc_fields	= &omap_hwmod_sysc_type3,
पूर्ण;

अटल काष्ठा omap_hwmod_class dm81xx_sata_hwmod_class = अणु
	.name	= "sata",
	.sysc	= &dm81xx_sata_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_sata_hwmod = अणु
	.name		= "sata",
	.clkdm_name	= "default_clkdm",
	.flags		= HWMOD_NO_IDLEST,
	.prcm = अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_DEFAULT_SATA_CLKCTRL,
			.modulemode   = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &dm81xx_sata_hwmod_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_hs__sata = अणु
	.master		= &dm81xx_l4_hs_hwmod,
	.slave		= &dm81xx_sata_hwmod,
	.clk		= "sysclk5_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_class_sysconfig dm81xx_mmc_sysc = अणु
	.rev_offs	= 0x0,
	.sysc_offs	= 0x110,
	.syss_offs	= 0x114,
	.sysc_flags	= SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
				SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
				SYSC_HAS_AUTOIDLE | SYSS_HAS_RESET_STATUS,
	.idlemodes	= SIDLE_FORCE | SIDLE_NO | SIDLE_SMART,
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class dm81xx_mmc_class = अणु
	.name = "mmc",
	.sysc = &dm81xx_mmc_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod_opt_clk dm81xx_mmc_opt_clks[] = अणु
	अणु .role = "dbck", .clk = "sysclk18_ck", पूर्ण,
पूर्ण;

अटल काष्ठा omap_hsmmc_dev_attr mmc_dev_attr = अणु
पूर्ण;

अटल काष्ठा omap_hwmod dm814x_mmc1_hwmod = अणु
	.name		= "mmc1",
	.clkdm_name	= "alwon_l3s_clkdm",
	.opt_clks	= dm81xx_mmc_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dm81xx_mmc_opt_clks),
	.मुख्य_clk	= "sysclk8_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM814X_CM_ALWON_MMCHS_0_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.dev_attr	= &mmc_dev_attr,
	.class		= &dm81xx_mmc_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm814x_l4_ls__mmc1 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm814x_mmc1_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
	.flags		= OMAP_FIREWALL_L4
पूर्ण;

अटल काष्ठा omap_hwmod dm814x_mmc2_hwmod = अणु
	.name		= "mmc2",
	.clkdm_name	= "alwon_l3s_clkdm",
	.opt_clks	= dm81xx_mmc_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dm81xx_mmc_opt_clks),
	.मुख्य_clk	= "sysclk8_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM814X_CM_ALWON_MMCHS_1_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.dev_attr	= &mmc_dev_attr,
	.class		= &dm81xx_mmc_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm814x_l4_ls__mmc2 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm814x_mmc2_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
	.flags		= OMAP_FIREWALL_L4
पूर्ण;

अटल काष्ठा omap_hwmod dm814x_mmc3_hwmod = अणु
	.name		= "mmc3",
	.clkdm_name	= "alwon_l3_med_clkdm",
	.opt_clks	= dm81xx_mmc_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dm81xx_mmc_opt_clks),
	.मुख्य_clk	= "sysclk8_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM814X_CM_ALWON_MMCHS_2_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.dev_attr	= &mmc_dev_attr,
	.class		= &dm81xx_mmc_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm814x_alwon_l3_med__mmc3 = अणु
	.master		= &dm81xx_alwon_l3_med_hwmod,
	.slave		= &dm814x_mmc3_hwmod,
	.clk		= "sysclk4_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod dm816x_mmc1_hwmod = अणु
	.name		= "mmc1",
	.clkdm_name	= "alwon_l3s_clkdm",
	.opt_clks	= dm81xx_mmc_opt_clks,
	.opt_clks_cnt	= ARRAY_SIZE(dm81xx_mmc_opt_clks),
	.मुख्य_clk	= "sysclk10_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM816X_CM_ALWON_SDIO_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.dev_attr	= &mmc_dev_attr,
	.class		= &dm81xx_mmc_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm816x_l4_ls__mmc1 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm816x_mmc1_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
	.flags		= OMAP_FIREWALL_L4
पूर्ण;

अटल काष्ठा omap_hwmod_class_sysconfig dm816x_mcspi_sysc = अणु
	.rev_offs	= 0x0,
	.sysc_offs	= 0x110,
	.syss_offs	= 0x114,
	.sysc_flags	= SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
				SYSC_HAS_ENAWAKEUP | SYSC_HAS_SOFTRESET |
				SYSC_HAS_AUTOIDLE | SYSS_HAS_RESET_STATUS,
	.idlemodes	= SIDLE_FORCE | SIDLE_NO | SIDLE_SMART,
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class dm816x_mcspi_class = अणु
	.name = "mcspi",
	.sysc = &dm816x_mcspi_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_mcspi1_hwmod = अणु
	.name		= "mcspi1",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "sysclk10_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_SPI_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &dm816x_mcspi_class,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_mcspi2_hwmod = अणु
	.name		= "mcspi2",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "sysclk10_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_SPI_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &dm816x_mcspi_class,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_mcspi3_hwmod = अणु
	.name		= "mcspi3",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "sysclk10_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_SPI_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &dm816x_mcspi_class,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_mcspi4_hwmod = अणु
	.name		= "mcspi4",
	.clkdm_name	= "alwon_l3s_clkdm",
	.मुख्य_clk	= "sysclk10_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_SPI_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
	.class		= &dm816x_mcspi_class,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__mcspi1 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_mcspi1_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__mcspi2 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_mcspi2_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__mcspi3 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_mcspi3_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__mcspi4 = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_mcspi4_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_class_sysconfig dm81xx_mailbox_sysc = अणु
	.rev_offs	= 0x000,
	.sysc_offs	= 0x010,
	.syss_offs	= 0x014,
	.sysc_flags	= SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
				SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE,
	.idlemodes	= SIDLE_FORCE | SIDLE_NO | SIDLE_SMART,
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class dm81xx_mailbox_hwmod_class = अणु
	.name = "mailbox",
	.sysc = &dm81xx_mailbox_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_mailbox_hwmod = अणु
	.name		= "mailbox",
	.clkdm_name	= "alwon_l3s_clkdm",
	.class		= &dm81xx_mailbox_hwmod_class,
	.मुख्य_clk	= "sysclk6_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_MAILBOX_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__mailbox = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_mailbox_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

अटल काष्ठा omap_hwmod_class_sysconfig dm81xx_spinbox_sysc = अणु
	.rev_offs	= 0x000,
	.sysc_offs	= 0x010,
	.syss_offs	= 0x014,
	.sysc_flags	= SYSC_HAS_CLOCKACTIVITY | SYSC_HAS_SIDLEMODE |
				SYSC_HAS_SOFTRESET | SYSC_HAS_AUTOIDLE,
	.idlemodes	= SIDLE_FORCE | SIDLE_NO | SIDLE_SMART,
	.sysc_fields	= &omap_hwmod_sysc_type1,
पूर्ण;

अटल काष्ठा omap_hwmod_class dm81xx_spinbox_hwmod_class = अणु
	.name = "spinbox",
	.sysc = &dm81xx_spinbox_sysc,
पूर्ण;

अटल काष्ठा omap_hwmod dm81xx_spinbox_hwmod = अणु
	.name		= "spinbox",
	.clkdm_name	= "alwon_l3s_clkdm",
	.class		= &dm81xx_spinbox_hwmod_class,
	.मुख्य_clk	= "sysclk6_ck",
	.prcm		= अणु
		.omap4 = अणु
			.clkctrl_offs = DM81XX_CM_ALWON_SPINBOX_CLKCTRL,
			.modulemode = MODULEMODE_SWCTRL,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_hwmod_ocp_अगर dm81xx_l4_ls__spinbox = अणु
	.master		= &dm81xx_l4_ls_hwmod,
	.slave		= &dm81xx_spinbox_hwmod,
	.clk		= "sysclk6_ck",
	.user		= OCP_USER_MPU,
पूर्ण;

/*
 * REVISIT: Test and enable the following once घड़ीs work:
 * dm81xx_l4_ls__mailbox
 *
 * Also note that some devices share a single clkctrl_offs..
 * For example, i2c1 and 3 share one, and i2c2 and 4 share one.
 */
अटल काष्ठा omap_hwmod_ocp_अगर *dm814x_hwmod_ocp_अगरs[] __initdata = अणु
	&dm814x_mpu__alwon_l3_slow,
	&dm814x_mpu__alwon_l3_med,
	&dm81xx_alwon_l3_slow__l4_ls,
	&dm81xx_alwon_l3_slow__l4_hs,
	&dm81xx_l4_ls__uart1,
	&dm81xx_l4_ls__uart2,
	&dm81xx_l4_ls__uart3,
	&dm81xx_l4_ls__wd_समयr1,
	&dm81xx_l4_ls__i2c1,
	&dm81xx_l4_ls__i2c2,
	&dm81xx_l4_ls__gpio1,
	&dm81xx_l4_ls__gpio2,
	&dm81xx_l4_ls__gpio3,
	&dm81xx_l4_ls__gpio4,
	&dm81xx_l4_ls__elm,
	&dm81xx_l4_ls__mcspi1,
	&dm81xx_l4_ls__mcspi2,
	&dm81xx_l4_ls__mcspi3,
	&dm81xx_l4_ls__mcspi4,
	&dm814x_l4_ls__mmc1,
	&dm814x_l4_ls__mmc2,
	&ti81xx_l4_ls__rtc,
	&dm81xx_alwon_l3_slow__gpmc,
	&dm814x_शेष_l3_slow__usbss,
	&dm814x_alwon_l3_med__mmc3,
	शून्य,
पूर्ण;

पूर्णांक __init dm814x_hwmod_init(व्योम)
अणु
	omap_hwmod_init();
	वापस omap_hwmod_रेजिस्टर_links(dm814x_hwmod_ocp_अगरs);
पूर्ण

अटल काष्ठा omap_hwmod_ocp_अगर *dm816x_hwmod_ocp_अगरs[] __initdata = अणु
	&dm816x_mpu__alwon_l3_slow,
	&dm816x_mpu__alwon_l3_med,
	&dm81xx_alwon_l3_slow__l4_ls,
	&dm81xx_alwon_l3_slow__l4_hs,
	&dm81xx_l4_ls__uart1,
	&dm81xx_l4_ls__uart2,
	&dm81xx_l4_ls__uart3,
	&dm81xx_l4_ls__wd_समयr1,
	&dm81xx_l4_ls__i2c1,
	&dm81xx_l4_ls__i2c2,
	&dm81xx_l4_ls__gpio1,
	&dm81xx_l4_ls__gpio2,
	&dm81xx_l4_ls__elm,
	&ti81xx_l4_ls__rtc,
	&dm816x_l4_ls__mmc1,
	&dm816x_l4_ls__समयr3,
	&dm816x_l4_ls__समयr4,
	&dm816x_l4_ls__समयr5,
	&dm816x_l4_ls__समयr6,
	&dm816x_l4_ls__समयr7,
	&dm81xx_l4_ls__mcspi1,
	&dm81xx_l4_ls__mailbox,
	&dm81xx_l4_ls__spinbox,
	&dm81xx_l4_hs__emac0,
	&dm81xx_emac0__mdio,
	&dm816x_l4_hs__emac1,
	&dm81xx_l4_hs__sata,
	&dm81xx_alwon_l3_slow__gpmc,
	&dm816x_शेष_l3_slow__usbss,
	शून्य,
पूर्ण;

पूर्णांक __init dm816x_hwmod_init(व्योम)
अणु
	omap_hwmod_init();
	वापस omap_hwmod_रेजिस्टर_links(dm816x_hwmod_ocp_अगरs);
पूर्ण
