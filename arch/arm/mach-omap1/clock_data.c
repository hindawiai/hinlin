<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-omap1/घड़ी_data.c
 *
 *  Copyright (C) 2004 - 2005, 2009-2010 Nokia Corporation
 *  Written by Tuukka Tikkanen <tuukka.tikkanen@elektrobit.com>
 *  Based on घड़ीs.h by Tony Lindgren, Gorकरोn McNutt and RidgeRun, Inc
 *
 * To करो:
 * - Clocks that are only available on some chips should be marked with the
 *   chips that they are present on.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/mach-types.h>  /* क्रम machine_is_* */

#समावेश "soc.h"

#समावेश <mach/hardware.h>
#समावेश <mach/usb.h>   /* क्रम OTG_BASE */

#समावेश "iomap.h"
#समावेश "clock.h"
#समावेश "sram.h"

/* Some ARM_IDLECT1 bit shअगरts - used in काष्ठा arm_idlect1_clk */
#घोषणा IDL_CLKOUT_ARM_SHIFT			12
#घोषणा IDLTIM_ARM_SHIFT			9
#घोषणा IDLAPI_ARM_SHIFT			8
#घोषणा IDLIF_ARM_SHIFT				6
#घोषणा IDLLB_ARM_SHIFT				4	/* unकरोcumented? */
#घोषणा OMAP1510_IDLLCD_ARM_SHIFT		3	/* unकरोcumented? */
#घोषणा IDLPER_ARM_SHIFT			2
#घोषणा IDLXORP_ARM_SHIFT			1
#घोषणा IDLWDT_ARM_SHIFT			0

/* Some MOD_CONF_CTRL_0 bit shअगरts - used in काष्ठा clk.enable_bit */
#घोषणा CONF_MOD_UART3_CLK_MODE_R		31
#घोषणा CONF_MOD_UART2_CLK_MODE_R		30
#घोषणा CONF_MOD_UART1_CLK_MODE_R		29
#घोषणा CONF_MOD_MMC_SD_CLK_REQ_R		23
#घोषणा CONF_MOD_MCBSP3_AUXON			20

/* Some MOD_CONF_CTRL_1 bit shअगरts - used in काष्ठा clk.enable_bit */
#घोषणा CONF_MOD_SOSSI_CLK_EN_R			16

/* Some OTG_SYSCON_2-specअगरic bit fields */
#घोषणा OTG_SYSCON_2_UHOST_EN_SHIFT		8

/* Some SOFT_REQ_REG bit fields - used in काष्ठा clk.enable_bit */
#घोषणा SOFT_MMC2_DPLL_REQ_SHIFT	13
#घोषणा SOFT_MMC_DPLL_REQ_SHIFT		12
#घोषणा SOFT_UART3_DPLL_REQ_SHIFT	11
#घोषणा SOFT_UART2_DPLL_REQ_SHIFT	10
#घोषणा SOFT_UART1_DPLL_REQ_SHIFT	9
#घोषणा SOFT_USB_OTG_DPLL_REQ_SHIFT	8
#घोषणा SOFT_CAM_DPLL_REQ_SHIFT		7
#घोषणा SOFT_COM_MCKO_REQ_SHIFT		6
#घोषणा SOFT_PERIPH_REQ_SHIFT		5	/* sys_ck gate क्रम UART2 ? */
#घोषणा USB_REQ_EN_SHIFT		4
#घोषणा SOFT_USB_REQ_SHIFT		3	/* sys_ck gate क्रम USB host? */
#घोषणा SOFT_SDW_REQ_SHIFT		2	/* sys_ck gate क्रम Bluetooth? */
#घोषणा SOFT_COM_REQ_SHIFT		1	/* sys_ck gate क्रम com proc? */
#घोषणा SOFT_DPLL_REQ_SHIFT		0

/*
 * Omap1 घड़ीs
 */

अटल काष्ठा clk ck_ref = अणु
	.name		= "ck_ref",
	.ops		= &clkops_null,
	.rate		= 12000000,
पूर्ण;

अटल काष्ठा clk ck_dpll1 = अणु
	.name		= "ck_dpll1",
	.ops		= &clkops_null,
	.parent		= &ck_ref,
पूर्ण;

/*
 * FIXME: This घड़ी seems to be necessary but no-one has asked क्रम its
 * activation.  [ FIX: SoSSI, SSR ]
 */
अटल काष्ठा arm_idlect1_clk ck_dpll1out = अणु
	.clk = अणु
		.name		= "ck_dpll1out",
		.ops		= &clkops_generic,
		.parent		= &ck_dpll1,
		.flags		= CLOCK_IDLE_CONTROL | ENABLE_REG_32BIT |
				  ENABLE_ON_INIT,
		.enable_reg	= OMAP1_IO_ADDRESS(ARM_IDLECT2),
		.enable_bit	= EN_CKOUT_ARM,
		.recalc		= &followparent_recalc,
	पूर्ण,
	.idlect_shअगरt	= IDL_CLKOUT_ARM_SHIFT,
पूर्ण;

अटल काष्ठा clk sossi_ck = अणु
	.name		= "ck_sossi",
	.ops		= &clkops_generic,
	.parent		= &ck_dpll1out.clk,
	.flags		= CLOCK_NO_IDLE_PARENT | ENABLE_REG_32BIT,
	.enable_reg	= OMAP1_IO_ADDRESS(MOD_CONF_CTRL_1),
	.enable_bit	= CONF_MOD_SOSSI_CLK_EN_R,
	.recalc		= &omap1_sossi_recalc,
	.set_rate	= &omap1_set_sossi_rate,
पूर्ण;

अटल काष्ठा clk arm_ck = अणु
	.name		= "arm_ck",
	.ops		= &clkops_null,
	.parent		= &ck_dpll1,
	.rate_offset	= CKCTL_ARMDIV_OFFSET,
	.recalc		= &omap1_ckctl_recalc,
	.round_rate	= omap1_clk_round_rate_ckctl_arm,
	.set_rate	= omap1_clk_set_rate_ckctl_arm,
पूर्ण;

अटल काष्ठा arm_idlect1_clk armper_ck = अणु
	.clk = अणु
		.name		= "armper_ck",
		.ops		= &clkops_generic,
		.parent		= &ck_dpll1,
		.flags		= CLOCK_IDLE_CONTROL,
		.enable_reg	= OMAP1_IO_ADDRESS(ARM_IDLECT2),
		.enable_bit	= EN_PERCK,
		.rate_offset	= CKCTL_PERDIV_OFFSET,
		.recalc		= &omap1_ckctl_recalc,
		.round_rate	= omap1_clk_round_rate_ckctl_arm,
		.set_rate	= omap1_clk_set_rate_ckctl_arm,
	पूर्ण,
	.idlect_shअगरt	= IDLPER_ARM_SHIFT,
पूर्ण;

/*
 * FIXME: This घड़ी seems to be necessary but no-one has asked क्रम its
 * activation.  [ GPIO code क्रम 1510 ]
 */
अटल काष्ठा clk arm_gpio_ck = अणु
	.name		= "ick",
	.ops		= &clkops_generic,
	.parent		= &ck_dpll1,
	.flags		= ENABLE_ON_INIT,
	.enable_reg	= OMAP1_IO_ADDRESS(ARM_IDLECT2),
	.enable_bit	= EN_GPIOCK,
	.recalc		= &followparent_recalc,
पूर्ण;

अटल काष्ठा arm_idlect1_clk armxor_ck = अणु
	.clk = अणु
		.name		= "armxor_ck",
		.ops		= &clkops_generic,
		.parent		= &ck_ref,
		.flags		= CLOCK_IDLE_CONTROL,
		.enable_reg	= OMAP1_IO_ADDRESS(ARM_IDLECT2),
		.enable_bit	= EN_XORPCK,
		.recalc		= &followparent_recalc,
	पूर्ण,
	.idlect_shअगरt	= IDLXORP_ARM_SHIFT,
पूर्ण;

अटल काष्ठा arm_idlect1_clk armtim_ck = अणु
	.clk = अणु
		.name		= "armtim_ck",
		.ops		= &clkops_generic,
		.parent		= &ck_ref,
		.flags		= CLOCK_IDLE_CONTROL,
		.enable_reg	= OMAP1_IO_ADDRESS(ARM_IDLECT2),
		.enable_bit	= EN_TIMCK,
		.recalc		= &followparent_recalc,
	पूर्ण,
	.idlect_shअगरt	= IDLTIM_ARM_SHIFT,
पूर्ण;

अटल काष्ठा arm_idlect1_clk armwdt_ck = अणु
	.clk = अणु
		.name		= "armwdt_ck",
		.ops		= &clkops_generic,
		.parent		= &ck_ref,
		.flags		= CLOCK_IDLE_CONTROL,
		.enable_reg	= OMAP1_IO_ADDRESS(ARM_IDLECT2),
		.enable_bit	= EN_WDTCK,
		.fixed_भाग	= 14,
		.recalc		= &omap_fixed_भागisor_recalc,
	पूर्ण,
	.idlect_shअगरt	= IDLWDT_ARM_SHIFT,
पूर्ण;

अटल काष्ठा clk armपूर्णांकh_ck16xx = अणु
	.name		= "arminth_ck",
	.ops		= &clkops_null,
	.parent		= &arm_ck,
	.recalc		= &followparent_recalc,
	/* Note: On 16xx the frequency can be भागided by 2 by programming
	 * ARM_CKCTL:ARM_INTHCK_SEL(14) to 1
	 *
	 * 1510 version is in TC घड़ीs.
	 */
पूर्ण;

अटल काष्ठा clk dsp_ck = अणु
	.name		= "dsp_ck",
	.ops		= &clkops_generic,
	.parent		= &ck_dpll1,
	.enable_reg	= OMAP1_IO_ADDRESS(ARM_CKCTL),
	.enable_bit	= EN_DSPCK,
	.rate_offset	= CKCTL_DSPDIV_OFFSET,
	.recalc		= &omap1_ckctl_recalc,
	.round_rate	= omap1_clk_round_rate_ckctl_arm,
	.set_rate	= omap1_clk_set_rate_ckctl_arm,
पूर्ण;

अटल काष्ठा clk dspmmu_ck = अणु
	.name		= "dspmmu_ck",
	.ops		= &clkops_null,
	.parent		= &ck_dpll1,
	.rate_offset	= CKCTL_DSPMMUDIV_OFFSET,
	.recalc		= &omap1_ckctl_recalc,
	.round_rate	= omap1_clk_round_rate_ckctl_arm,
	.set_rate	= omap1_clk_set_rate_ckctl_arm,
पूर्ण;

अटल काष्ठा clk dspper_ck = अणु
	.name		= "dspper_ck",
	.ops		= &clkops_dspck,
	.parent		= &ck_dpll1,
	.enable_reg	= DSP_IDLECT2,
	.enable_bit	= EN_PERCK,
	.rate_offset	= CKCTL_PERDIV_OFFSET,
	.recalc		= &omap1_ckctl_recalc_dsp_करोमुख्य,
	.round_rate	= omap1_clk_round_rate_ckctl_arm,
	.set_rate	= &omap1_clk_set_rate_dsp_करोमुख्य,
पूर्ण;

अटल काष्ठा clk dspxor_ck = अणु
	.name		= "dspxor_ck",
	.ops		= &clkops_dspck,
	.parent		= &ck_ref,
	.enable_reg	= DSP_IDLECT2,
	.enable_bit	= EN_XORPCK,
	.recalc		= &followparent_recalc,
पूर्ण;

अटल काष्ठा clk dsptim_ck = अणु
	.name		= "dsptim_ck",
	.ops		= &clkops_dspck,
	.parent		= &ck_ref,
	.enable_reg	= DSP_IDLECT2,
	.enable_bit	= EN_DSPTIMCK,
	.recalc		= &followparent_recalc,
पूर्ण;

अटल काष्ठा arm_idlect1_clk tc_ck = अणु
	.clk = अणु
		.name		= "tc_ck",
		.ops		= &clkops_null,
		.parent		= &ck_dpll1,
		.flags		= CLOCK_IDLE_CONTROL,
		.rate_offset	= CKCTL_TCDIV_OFFSET,
		.recalc		= &omap1_ckctl_recalc,
		.round_rate	= omap1_clk_round_rate_ckctl_arm,
		.set_rate	= omap1_clk_set_rate_ckctl_arm,
	पूर्ण,
	.idlect_shअगरt	= IDLIF_ARM_SHIFT,
पूर्ण;

अटल काष्ठा clk armपूर्णांकh_ck1510 = अणु
	.name		= "arminth_ck",
	.ops		= &clkops_null,
	.parent		= &tc_ck.clk,
	.recalc		= &followparent_recalc,
	/* Note: On 1510 the frequency follows TC_CK
	 *
	 * 16xx version is in MPU घड़ीs.
	 */
पूर्ण;

अटल काष्ठा clk tipb_ck = अणु
	/* No-idle controlled by "tc_ck" */
	.name		= "tipb_ck",
	.ops		= &clkops_null,
	.parent		= &tc_ck.clk,
	.recalc		= &followparent_recalc,
पूर्ण;

अटल काष्ठा clk l3_ocpi_ck = अणु
	/* No-idle controlled by "tc_ck" */
	.name		= "l3_ocpi_ck",
	.ops		= &clkops_generic,
	.parent		= &tc_ck.clk,
	.enable_reg	= OMAP1_IO_ADDRESS(ARM_IDLECT3),
	.enable_bit	= EN_OCPI_CK,
	.recalc		= &followparent_recalc,
पूर्ण;

अटल काष्ठा clk tc1_ck = अणु
	.name		= "tc1_ck",
	.ops		= &clkops_generic,
	.parent		= &tc_ck.clk,
	.enable_reg	= OMAP1_IO_ADDRESS(ARM_IDLECT3),
	.enable_bit	= EN_TC1_CK,
	.recalc		= &followparent_recalc,
पूर्ण;

/*
 * FIXME: This घड़ी seems to be necessary but no-one has asked क्रम its
 * activation.  [ pm.c (SRAM), CCP, Camera ]
 */
अटल काष्ठा clk tc2_ck = अणु
	.name		= "tc2_ck",
	.ops		= &clkops_generic,
	.parent		= &tc_ck.clk,
	.flags		= ENABLE_ON_INIT,
	.enable_reg	= OMAP1_IO_ADDRESS(ARM_IDLECT3),
	.enable_bit	= EN_TC2_CK,
	.recalc		= &followparent_recalc,
पूर्ण;

अटल काष्ठा clk dma_ck = अणु
	/* No-idle controlled by "tc_ck" */
	.name		= "dma_ck",
	.ops		= &clkops_null,
	.parent		= &tc_ck.clk,
	.recalc		= &followparent_recalc,
पूर्ण;

अटल काष्ठा clk dma_lcdमुक्त_ck = अणु
	.name		= "dma_lcdfree_ck",
	.ops		= &clkops_null,
	.parent		= &tc_ck.clk,
	.recalc		= &followparent_recalc,
पूर्ण;

अटल काष्ठा arm_idlect1_clk api_ck = अणु
	.clk = अणु
		.name		= "api_ck",
		.ops		= &clkops_generic,
		.parent		= &tc_ck.clk,
		.flags		= CLOCK_IDLE_CONTROL,
		.enable_reg	= OMAP1_IO_ADDRESS(ARM_IDLECT2),
		.enable_bit	= EN_APICK,
		.recalc		= &followparent_recalc,
	पूर्ण,
	.idlect_shअगरt	= IDLAPI_ARM_SHIFT,
पूर्ण;

अटल काष्ठा arm_idlect1_clk lb_ck = अणु
	.clk = अणु
		.name		= "lb_ck",
		.ops		= &clkops_generic,
		.parent		= &tc_ck.clk,
		.flags		= CLOCK_IDLE_CONTROL,
		.enable_reg	= OMAP1_IO_ADDRESS(ARM_IDLECT2),
		.enable_bit	= EN_LBCK,
		.recalc		= &followparent_recalc,
	पूर्ण,
	.idlect_shअगरt	= IDLLB_ARM_SHIFT,
पूर्ण;

अटल काष्ठा clk rhea1_ck = अणु
	.name		= "rhea1_ck",
	.ops		= &clkops_null,
	.parent		= &tc_ck.clk,
	.recalc		= &followparent_recalc,
पूर्ण;

अटल काष्ठा clk rhea2_ck = अणु
	.name		= "rhea2_ck",
	.ops		= &clkops_null,
	.parent		= &tc_ck.clk,
	.recalc		= &followparent_recalc,
पूर्ण;

अटल काष्ठा clk lcd_ck_16xx = अणु
	.name		= "lcd_ck",
	.ops		= &clkops_generic,
	.parent		= &ck_dpll1,
	.enable_reg	= OMAP1_IO_ADDRESS(ARM_IDLECT2),
	.enable_bit	= EN_LCDCK,
	.rate_offset	= CKCTL_LCDDIV_OFFSET,
	.recalc		= &omap1_ckctl_recalc,
	.round_rate	= omap1_clk_round_rate_ckctl_arm,
	.set_rate	= omap1_clk_set_rate_ckctl_arm,
पूर्ण;

अटल काष्ठा arm_idlect1_clk lcd_ck_1510 = अणु
	.clk = अणु
		.name		= "lcd_ck",
		.ops		= &clkops_generic,
		.parent		= &ck_dpll1,
		.flags		= CLOCK_IDLE_CONTROL,
		.enable_reg	= OMAP1_IO_ADDRESS(ARM_IDLECT2),
		.enable_bit	= EN_LCDCK,
		.rate_offset	= CKCTL_LCDDIV_OFFSET,
		.recalc		= &omap1_ckctl_recalc,
		.round_rate	= omap1_clk_round_rate_ckctl_arm,
		.set_rate	= omap1_clk_set_rate_ckctl_arm,
	पूर्ण,
	.idlect_shअगरt	= OMAP1510_IDLLCD_ARM_SHIFT,
पूर्ण;

/*
 * XXX The enable_bit here is misused - it simply चयनes between 12MHz
 * and 48MHz.  Reimplement with clksel.
 *
 * XXX करोes this need SYSC रेजिस्टर handling?
 */
अटल काष्ठा clk uart1_1510 = अणु
	.name		= "uart1_ck",
	.ops		= &clkops_null,
	/* Direct from ULPD, no real parent */
	.parent		= &armper_ck.clk,
	.rate		= 12000000,
	.flags		= ENABLE_REG_32BIT | CLOCK_NO_IDLE_PARENT,
	.enable_reg	= OMAP1_IO_ADDRESS(MOD_CONF_CTRL_0),
	.enable_bit	= CONF_MOD_UART1_CLK_MODE_R,
	.set_rate	= &omap1_set_uart_rate,
	.recalc		= &omap1_uart_recalc,
पूर्ण;

/*
 * XXX The enable_bit here is misused - it simply चयनes between 12MHz
 * and 48MHz.  Reimplement with clksel.
 *
 * XXX SYSC रेजिस्टर handling करोes not beदीर्घ in the घड़ी framework
 */
अटल काष्ठा uart_clk uart1_16xx = अणु
	.clk	= अणु
		.name		= "uart1_ck",
		.ops		= &clkops_uart_16xx,
		/* Direct from ULPD, no real parent */
		.parent		= &armper_ck.clk,
		.rate		= 48000000,
		.flags		= ENABLE_REG_32BIT | CLOCK_NO_IDLE_PARENT,
		.enable_reg	= OMAP1_IO_ADDRESS(MOD_CONF_CTRL_0),
		.enable_bit	= CONF_MOD_UART1_CLK_MODE_R,
	पूर्ण,
	.sysc_addr	= 0xfffb0054,
पूर्ण;

/*
 * XXX The enable_bit here is misused - it simply चयनes between 12MHz
 * and 48MHz.  Reimplement with clksel.
 *
 * XXX करोes this need SYSC रेजिस्टर handling?
 */
अटल काष्ठा clk uart2_ck = अणु
	.name		= "uart2_ck",
	.ops		= &clkops_null,
	/* Direct from ULPD, no real parent */
	.parent		= &armper_ck.clk,
	.rate		= 12000000,
	.flags		= ENABLE_REG_32BIT | CLOCK_NO_IDLE_PARENT,
	.enable_reg	= OMAP1_IO_ADDRESS(MOD_CONF_CTRL_0),
	.enable_bit	= CONF_MOD_UART2_CLK_MODE_R,
	.set_rate	= &omap1_set_uart_rate,
	.recalc		= &omap1_uart_recalc,
पूर्ण;

/*
 * XXX The enable_bit here is misused - it simply चयनes between 12MHz
 * and 48MHz.  Reimplement with clksel.
 *
 * XXX करोes this need SYSC रेजिस्टर handling?
 */
अटल काष्ठा clk uart3_1510 = अणु
	.name		= "uart3_ck",
	.ops		= &clkops_null,
	/* Direct from ULPD, no real parent */
	.parent		= &armper_ck.clk,
	.rate		= 12000000,
	.flags		= ENABLE_REG_32BIT | CLOCK_NO_IDLE_PARENT,
	.enable_reg	= OMAP1_IO_ADDRESS(MOD_CONF_CTRL_0),
	.enable_bit	= CONF_MOD_UART3_CLK_MODE_R,
	.set_rate	= &omap1_set_uart_rate,
	.recalc		= &omap1_uart_recalc,
पूर्ण;

/*
 * XXX The enable_bit here is misused - it simply चयनes between 12MHz
 * and 48MHz.  Reimplement with clksel.
 *
 * XXX SYSC रेजिस्टर handling करोes not beदीर्घ in the घड़ी framework
 */
अटल काष्ठा uart_clk uart3_16xx = अणु
	.clk	= अणु
		.name		= "uart3_ck",
		.ops		= &clkops_uart_16xx,
		/* Direct from ULPD, no real parent */
		.parent		= &armper_ck.clk,
		.rate		= 48000000,
		.flags		= ENABLE_REG_32BIT | CLOCK_NO_IDLE_PARENT,
		.enable_reg	= OMAP1_IO_ADDRESS(MOD_CONF_CTRL_0),
		.enable_bit	= CONF_MOD_UART3_CLK_MODE_R,
	पूर्ण,
	.sysc_addr	= 0xfffb9854,
पूर्ण;

अटल काष्ठा clk usb_clko = अणु	/* 6 MHz output on W4_USB_CLKO */
	.name		= "usb_clko",
	.ops		= &clkops_generic,
	/* Direct from ULPD, no parent */
	.rate		= 6000000,
	.flags		= ENABLE_REG_32BIT,
	.enable_reg	= OMAP1_IO_ADDRESS(ULPD_CLOCK_CTRL),
	.enable_bit	= USB_MCLK_EN_BIT,
पूर्ण;

अटल काष्ठा clk usb_hhc_ck1510 = अणु
	.name		= "usb_hhc_ck",
	.ops		= &clkops_generic,
	/* Direct from ULPD, no parent */
	.rate		= 48000000, /* Actually 2 घड़ीs, 12MHz and 48MHz */
	.flags		= ENABLE_REG_32BIT,
	.enable_reg	= OMAP1_IO_ADDRESS(MOD_CONF_CTRL_0),
	.enable_bit	= USB_HOST_HHC_UHOST_EN,
पूर्ण;

अटल काष्ठा clk usb_hhc_ck16xx = अणु
	.name		= "usb_hhc_ck",
	.ops		= &clkops_generic,
	/* Direct from ULPD, no parent */
	.rate		= 48000000,
	/* OTG_SYSCON_2.OTG_PADEN == 0 (not 1510-compatible) */
	.flags		= ENABLE_REG_32BIT,
	.enable_reg	= OMAP1_IO_ADDRESS(OTG_BASE + 0x08), /* OTG_SYSCON_2 */
	.enable_bit	= OTG_SYSCON_2_UHOST_EN_SHIFT
पूर्ण;

अटल काष्ठा clk usb_dc_ck = अणु
	.name		= "usb_dc_ck",
	.ops		= &clkops_generic,
	/* Direct from ULPD, no parent */
	.rate		= 48000000,
	.enable_reg	= OMAP1_IO_ADDRESS(SOFT_REQ_REG),
	.enable_bit	= SOFT_USB_OTG_DPLL_REQ_SHIFT,
पूर्ण;

अटल काष्ठा clk uart1_7xx = अणु
	.name		= "uart1_ck",
	.ops		= &clkops_generic,
	/* Direct from ULPD, no parent */
	.rate		= 12000000,
	.enable_reg	= OMAP1_IO_ADDRESS(SOFT_REQ_REG),
	.enable_bit	= 9,
पूर्ण;

अटल काष्ठा clk uart2_7xx = अणु
	.name		= "uart2_ck",
	.ops		= &clkops_generic,
	/* Direct from ULPD, no parent */
	.rate		= 12000000,
	.enable_reg	= OMAP1_IO_ADDRESS(SOFT_REQ_REG),
	.enable_bit	= 11,
पूर्ण;

अटल काष्ठा clk mclk_1510 = अणु
	.name		= "mclk",
	.ops		= &clkops_generic,
	/* Direct from ULPD, no parent. May be enabled by ext hardware. */
	.rate		= 12000000,
	.enable_reg	= OMAP1_IO_ADDRESS(SOFT_REQ_REG),
	.enable_bit	= SOFT_COM_MCKO_REQ_SHIFT,
पूर्ण;

अटल काष्ठा clk mclk_16xx = अणु
	.name		= "mclk",
	.ops		= &clkops_generic,
	/* Direct from ULPD, no parent. May be enabled by ext hardware. */
	.enable_reg	= OMAP1_IO_ADDRESS(COM_CLK_DIV_CTRL_SEL),
	.enable_bit	= COM_ULPD_PLL_CLK_REQ,
	.set_rate	= &omap1_set_ext_clk_rate,
	.round_rate	= &omap1_round_ext_clk_rate,
	.init		= &omap1_init_ext_clk,
पूर्ण;

अटल काष्ठा clk bclk_1510 = अणु
	.name		= "bclk",
	.ops		= &clkops_generic,
	/* Direct from ULPD, no parent. May be enabled by ext hardware. */
	.rate		= 12000000,
पूर्ण;

अटल काष्ठा clk bclk_16xx = अणु
	.name		= "bclk",
	.ops		= &clkops_generic,
	/* Direct from ULPD, no parent. May be enabled by ext hardware. */
	.enable_reg	= OMAP1_IO_ADDRESS(SWD_CLK_DIV_CTRL_SEL),
	.enable_bit	= SWD_ULPD_PLL_CLK_REQ,
	.set_rate	= &omap1_set_ext_clk_rate,
	.round_rate	= &omap1_round_ext_clk_rate,
	.init		= &omap1_init_ext_clk,
पूर्ण;

अटल काष्ठा clk mmc1_ck = अणु
	.name		= "mmc1_ck",
	.ops		= &clkops_generic,
	/* Functional घड़ी is direct from ULPD, पूर्णांकerface घड़ी is ARMPER */
	.parent		= &armper_ck.clk,
	.rate		= 48000000,
	.flags		= ENABLE_REG_32BIT | CLOCK_NO_IDLE_PARENT,
	.enable_reg	= OMAP1_IO_ADDRESS(MOD_CONF_CTRL_0),
	.enable_bit	= CONF_MOD_MMC_SD_CLK_REQ_R,
पूर्ण;

/*
 * XXX MOD_CONF_CTRL_0 bit 20 is defined in the 1510 TRM as
 * CONF_MOD_MCBSP3_AUXON ??
 */
अटल काष्ठा clk mmc2_ck = अणु
	.name		= "mmc2_ck",
	.ops		= &clkops_generic,
	/* Functional घड़ी is direct from ULPD, पूर्णांकerface घड़ी is ARMPER */
	.parent		= &armper_ck.clk,
	.rate		= 48000000,
	.flags		= ENABLE_REG_32BIT | CLOCK_NO_IDLE_PARENT,
	.enable_reg	= OMAP1_IO_ADDRESS(MOD_CONF_CTRL_0),
	.enable_bit	= 20,
पूर्ण;

अटल काष्ठा clk mmc3_ck = अणु
	.name		= "mmc3_ck",
	.ops		= &clkops_generic,
	/* Functional घड़ी is direct from ULPD, पूर्णांकerface घड़ी is ARMPER */
	.parent		= &armper_ck.clk,
	.rate		= 48000000,
	.flags		= ENABLE_REG_32BIT | CLOCK_NO_IDLE_PARENT,
	.enable_reg	= OMAP1_IO_ADDRESS(SOFT_REQ_REG),
	.enable_bit	= SOFT_MMC_DPLL_REQ_SHIFT,
पूर्ण;

अटल काष्ठा clk भव_ck_mpu = अणु
	.name		= "mpu",
	.ops		= &clkops_null,
	.parent		= &arm_ck, /* Is smarter alias क्रम */
	.recalc		= &followparent_recalc,
	.set_rate	= &omap1_select_table_rate,
	.round_rate	= &omap1_round_to_table_rate,
पूर्ण;

/* भव functional घड़ी करोमुख्य क्रम I2C. Just क्रम making sure that ARMXOR_CK
reमुख्यs active during MPU idle whenever this is enabled */
अटल काष्ठा clk i2c_fck = अणु
	.name		= "i2c_fck",
	.ops		= &clkops_null,
	.flags		= CLOCK_NO_IDLE_PARENT,
	.parent		= &armxor_ck.clk,
	.recalc		= &followparent_recalc,
पूर्ण;

अटल काष्ठा clk i2c_ick = अणु
	.name		= "i2c_ick",
	.ops		= &clkops_null,
	.flags		= CLOCK_NO_IDLE_PARENT,
	.parent		= &armper_ck.clk,
	.recalc		= &followparent_recalc,
पूर्ण;

/*
 * clkdev पूर्णांकegration
 */

अटल काष्ठा omap_clk omap_clks[] = अणु
	/* non-ULPD घड़ीs */
	CLK(शून्य,	"ck_ref",	&ck_ref,	CK_16XX | CK_1510 | CK_310 | CK_7XX),
	CLK(शून्य,	"ck_dpll1",	&ck_dpll1,	CK_16XX | CK_1510 | CK_310 | CK_7XX),
	/* CK_GEN1 घड़ीs */
	CLK(शून्य,	"ck_dpll1out",	&ck_dpll1out.clk, CK_16XX),
	CLK(शून्य,	"ck_sossi",	&sossi_ck,	CK_16XX),
	CLK(शून्य,	"arm_ck",	&arm_ck,	CK_16XX | CK_1510 | CK_310),
	CLK(शून्य,	"armper_ck",	&armper_ck.clk,	CK_16XX | CK_1510 | CK_310),
	CLK("omap_gpio.0", "ick",	&arm_gpio_ck,	CK_1510 | CK_310),
	CLK(शून्य,	"armxor_ck",	&armxor_ck.clk,	CK_16XX | CK_1510 | CK_310 | CK_7XX),
	CLK(शून्य,	"armtim_ck",	&armtim_ck.clk,	CK_16XX | CK_1510 | CK_310),
	CLK("omap_wdt",	"fck",		&armwdt_ck.clk,	CK_16XX | CK_1510 | CK_310),
	CLK("omap_wdt",	"ick",		&armper_ck.clk,	CK_16XX),
	CLK("omap_wdt", "ick",		&dummy_ck,	CK_1510 | CK_310),
	CLK(शून्य,	"arminth_ck",	&armपूर्णांकh_ck1510, CK_1510 | CK_310),
	CLK(शून्य,	"arminth_ck",	&armपूर्णांकh_ck16xx, CK_16XX),
	/* CK_GEN2 घड़ीs */
	CLK(शून्य,	"dsp_ck",	&dsp_ck,	CK_16XX | CK_1510 | CK_310),
	CLK(शून्य,	"dspmmu_ck",	&dspmmu_ck,	CK_16XX | CK_1510 | CK_310),
	CLK(शून्य,	"dspper_ck",	&dspper_ck,	CK_16XX | CK_1510 | CK_310),
	CLK(शून्य,	"dspxor_ck",	&dspxor_ck,	CK_16XX | CK_1510 | CK_310),
	CLK(शून्य,	"dsptim_ck",	&dsptim_ck,	CK_16XX | CK_1510 | CK_310),
	/* CK_GEN3 घड़ीs */
	CLK(शून्य,	"tc_ck",	&tc_ck.clk,	CK_16XX | CK_1510 | CK_310 | CK_7XX),
	CLK(शून्य,	"tipb_ck",	&tipb_ck,	CK_1510 | CK_310),
	CLK(शून्य,	"l3_ocpi_ck",	&l3_ocpi_ck,	CK_16XX | CK_7XX),
	CLK(शून्य,	"tc1_ck",	&tc1_ck,	CK_16XX),
	CLK(शून्य,	"tc2_ck",	&tc2_ck,	CK_16XX),
	CLK(शून्य,	"dma_ck",	&dma_ck,	CK_16XX | CK_1510 | CK_310),
	CLK(शून्य,	"dma_lcdfree_ck", &dma_lcdमुक्त_ck, CK_16XX),
	CLK(शून्य,	"api_ck",	&api_ck.clk,	CK_16XX | CK_1510 | CK_310 | CK_7XX),
	CLK(शून्य,	"lb_ck",	&lb_ck.clk,	CK_1510 | CK_310),
	CLK(शून्य,	"rhea1_ck",	&rhea1_ck,	CK_16XX),
	CLK(शून्य,	"rhea2_ck",	&rhea2_ck,	CK_16XX),
	CLK(शून्य,	"lcd_ck",	&lcd_ck_16xx,	CK_16XX | CK_7XX),
	CLK(शून्य,	"lcd_ck",	&lcd_ck_1510.clk, CK_1510 | CK_310),
	/* ULPD घड़ीs */
	CLK(शून्य,	"uart1_ck",	&uart1_1510,	CK_1510 | CK_310),
	CLK(शून्य,	"uart1_ck",	&uart1_16xx.clk, CK_16XX),
	CLK(शून्य,	"uart1_ck",	&uart1_7xx,	CK_7XX),
	CLK(शून्य,	"uart2_ck",	&uart2_ck,	CK_16XX | CK_1510 | CK_310),
	CLK(शून्य,	"uart2_ck",	&uart2_7xx,	CK_7XX),
	CLK(शून्य,	"uart3_ck",	&uart3_1510,	CK_1510 | CK_310),
	CLK(शून्य,	"uart3_ck",	&uart3_16xx.clk, CK_16XX),
	CLK(शून्य,	"usb_clko",	&usb_clko,	CK_16XX | CK_1510 | CK_310),
	CLK(शून्य,	"usb_hhc_ck",	&usb_hhc_ck1510, CK_1510 | CK_310),
	CLK(शून्य,	"usb_hhc_ck",	&usb_hhc_ck16xx, CK_16XX),
	CLK(शून्य,	"usb_dc_ck",	&usb_dc_ck,	CK_16XX | CK_7XX),
	CLK(शून्य,	"mclk",		&mclk_1510,	CK_1510 | CK_310),
	CLK(शून्य,	"mclk",		&mclk_16xx,	CK_16XX),
	CLK(शून्य,	"bclk",		&bclk_1510,	CK_1510 | CK_310),
	CLK(शून्य,	"bclk",		&bclk_16xx,	CK_16XX),
	CLK("mmci-omap.0", "fck",	&mmc1_ck,	CK_16XX | CK_1510 | CK_310),
	CLK("mmci-omap.0", "fck",	&mmc3_ck,	CK_7XX),
	CLK("mmci-omap.0", "ick",	&armper_ck.clk,	CK_16XX | CK_1510 | CK_310 | CK_7XX),
	CLK("mmci-omap.1", "fck",	&mmc2_ck,	CK_16XX),
	CLK("mmci-omap.1", "ick",	&armper_ck.clk,	CK_16XX),
	/* Virtual घड़ीs */
	CLK(शून्य,	"mpu",		&भव_ck_mpu, CK_16XX | CK_1510 | CK_310),
	CLK("omap_i2c.1", "fck",	&i2c_fck,	CK_16XX | CK_1510 | CK_310 | CK_7XX),
	CLK("omap_i2c.1", "ick",	&i2c_ick,	CK_16XX),
	CLK("omap_i2c.1", "ick",	&dummy_ck,	CK_1510 | CK_310 | CK_7XX),
	CLK("omap1_spi100k.1", "fck",	&dummy_ck,	CK_7XX),
	CLK("omap1_spi100k.1", "ick",	&dummy_ck,	CK_7XX),
	CLK("omap1_spi100k.2", "fck",	&dummy_ck,	CK_7XX),
	CLK("omap1_spi100k.2", "ick",	&dummy_ck,	CK_7XX),
	CLK("omap_uwire", "fck",	&armxor_ck.clk,	CK_16XX | CK_1510 | CK_310),
	CLK("omap-mcbsp.1", "ick",	&dspper_ck,	CK_16XX),
	CLK("omap-mcbsp.1", "ick",	&dummy_ck,	CK_1510 | CK_310),
	CLK("omap-mcbsp.2", "ick",	&armper_ck.clk,	CK_16XX),
	CLK("omap-mcbsp.2", "ick",	&dummy_ck,	CK_1510 | CK_310),
	CLK("omap-mcbsp.3", "ick",	&dspper_ck,	CK_16XX),
	CLK("omap-mcbsp.3", "ick",	&dummy_ck,	CK_1510 | CK_310),
	CLK("omap-mcbsp.1", "fck",	&dspxor_ck,	CK_16XX | CK_1510 | CK_310),
	CLK("omap-mcbsp.2", "fck",	&armper_ck.clk,	CK_16XX | CK_1510 | CK_310),
	CLK("omap-mcbsp.3", "fck",	&dspxor_ck,	CK_16XX | CK_1510 | CK_310),
पूर्ण;

/*
 * init
 */

अटल व्योम __init omap1_show_rates(व्योम)
अणु
	pr_notice("Clocking rate (xtal/DPLL1/MPU): %ld.%01ld/%ld.%01ld/%ld.%01ld MHz\n",
		  ck_ref.rate / 1000000, (ck_ref.rate / 100000) % 10,
		  ck_dpll1.rate / 1000000, (ck_dpll1.rate / 100000) % 10,
		  arm_ck.rate / 1000000, (arm_ck.rate / 100000) % 10);
पूर्ण

u32 cpu_mask;

पूर्णांक __init omap1_clk_init(व्योम)
अणु
	काष्ठा omap_clk *c;
	पूर्णांक crystal_type = 0; /* Default 12 MHz */
	u32 reg;

#अगर_घोषित CONFIG_DEBUG_LL
	/*
	 * Resets some घड़ीs that may be left on from bootloader,
	 * but leaves serial घड़ीs on.
	 */
	omap_ग_लिखोl(0x3 << 29, MOD_CONF_CTRL_0);
#पूर्ण_अगर

	/* USB_REQ_EN will be disabled later अगर necessary (usb_dc_ck) */
	reg = omap_पढ़ोw(SOFT_REQ_REG) & (1 << 4);
	omap_ग_लिखोw(reg, SOFT_REQ_REG);
	अगर (!cpu_is_omap15xx())
		omap_ग_लिखोw(0, SOFT_REQ_REG2);

	/* By शेष all idlect1 घड़ीs are allowed to idle */
	arm_idlect1_mask = ~0;

	क्रम (c = omap_clks; c < omap_clks + ARRAY_SIZE(omap_clks); c++)
		clk_preinit(c->lk.clk);

	cpu_mask = 0;
	अगर (cpu_is_omap1710())
		cpu_mask |= CK_1710;
	अगर (cpu_is_omap16xx())
		cpu_mask |= CK_16XX;
	अगर (cpu_is_omap1510())
		cpu_mask |= CK_1510;
	अगर (cpu_is_omap7xx())
		cpu_mask |= CK_7XX;
	अगर (cpu_is_omap310())
		cpu_mask |= CK_310;

	क्रम (c = omap_clks; c < omap_clks + ARRAY_SIZE(omap_clks); c++)
		अगर (c->cpu & cpu_mask) अणु
			clkdev_add(&c->lk);
			clk_रेजिस्टर(c->lk.clk);
		पूर्ण

	/* Poपूर्णांकers to these घड़ीs are needed by code in घड़ी.c */
	api_ck_p = clk_get(शून्य, "api_ck");
	ck_dpll1_p = clk_get(शून्य, "ck_dpll1");
	ck_ref_p = clk_get(शून्य, "ck_ref");

	अगर (cpu_is_omap7xx())
		ck_ref.rate = 13000000;
	अगर (cpu_is_omap16xx() && crystal_type == 2)
		ck_ref.rate = 19200000;

	pr_info("Clocks: ARM_SYSST: 0x%04x DPLL_CTL: 0x%04x ARM_CKCTL: 0x%04x\n",
		omap_पढ़ोw(ARM_SYSST), omap_पढ़ोw(DPLL_CTL),
		omap_पढ़ोw(ARM_CKCTL));

	/* We want to be in syncronous scalable mode */
	omap_ग_लिखोw(0x1000, ARM_SYSST);


	/*
	 * Initially use the values set by bootloader. Determine PLL rate and
	 * recalculate dependent घड़ीs as अगर kernel had changed PLL or
	 * भागisors. See also omap1_clk_late_init() that can reprogram dpll1
	 * after the SRAM is initialized.
	 */
	अणु
		अचिन्हित pll_ctl_val = omap_पढ़ोw(DPLL_CTL);

		ck_dpll1.rate = ck_ref.rate; /* Base xtal rate */
		अगर (pll_ctl_val & 0x10) अणु
			/* PLL enabled, apply multiplier and भागisor */
			अगर (pll_ctl_val & 0xf80)
				ck_dpll1.rate *= (pll_ctl_val & 0xf80) >> 7;
			ck_dpll1.rate /= ((pll_ctl_val & 0x60) >> 5) + 1;
		पूर्ण अन्यथा अणु
			/* PLL disabled, apply bypass भागisor */
			चयन (pll_ctl_val & 0xc) अणु
			हाल 0:
				अवरोध;
			हाल 0x4:
				ck_dpll1.rate /= 2;
				अवरोध;
			शेष:
				ck_dpll1.rate /= 4;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	propagate_rate(&ck_dpll1);
	/* Cache rates क्रम घड़ीs connected to ck_ref (not dpll1) */
	propagate_rate(&ck_ref);
	omap1_show_rates();
	अगर (machine_is_omap_perseus2() || machine_is_omap_fsample()) अणु
		/* Select slicer output as OMAP input घड़ी */
		omap_ग_लिखोw(omap_पढ़ोw(OMAP7XX_PCC_UPLD_CTRL) & ~0x1,
				OMAP7XX_PCC_UPLD_CTRL);
	पूर्ण

	/* Amstrad Delta wants BCLK high when inactive */
	अगर (machine_is_ams_delta())
		omap_ग_लिखोl(omap_पढ़ोl(ULPD_CLOCK_CTRL) |
				(1 << SDW_MCLK_INV_BIT),
				ULPD_CLOCK_CTRL);

	/* Turn off DSP and ARM_TIMXO. Make sure ARM_INTHCK is not भागided */
	/* (on 730, bit 13 must not be cleared) */
	अगर (cpu_is_omap7xx())
		omap_ग_लिखोw(omap_पढ़ोw(ARM_CKCTL) & 0x2fff, ARM_CKCTL);
	अन्यथा
		omap_ग_लिखोw(omap_पढ़ोw(ARM_CKCTL) & 0x0fff, ARM_CKCTL);

	/* Put DSP/MPUI पूर्णांकo reset until needed */
	omap_ग_लिखोw(0, ARM_RSTCT1);
	omap_ग_लिखोw(1, ARM_RSTCT2);
	omap_ग_लिखोw(0x400, ARM_IDLECT1);

	/*
	 * According to OMAP5910 Erratum SYS_DMA_1, bit DMACK_REQ (bit 8)
	 * of the ARM_IDLECT2 रेजिस्टर must be set to zero. The घातer-on
	 * शेष value of this bit is one.
	 */
	omap_ग_लिखोw(0x0000, ARM_IDLECT2);	/* Turn LCD घड़ी off also */

	/*
	 * Only enable those घड़ीs we will need, let the drivers
	 * enable other घड़ीs as necessary
	 */
	clk_enable(&armper_ck.clk);
	clk_enable(&armxor_ck.clk);
	clk_enable(&armtim_ck.clk); /* This should be करोne by समयr code */

	अगर (cpu_is_omap15xx())
		clk_enable(&arm_gpio_ck);

	वापस 0;
पूर्ण

#घोषणा OMAP1_DPLL1_SANE_VALUE	60000000

व्योम __init omap1_clk_late_init(व्योम)
अणु
	अचिन्हित दीर्घ rate = ck_dpll1.rate;

	/* Find the highest supported frequency and enable it */
	अगर (omap1_select_table_rate(&भव_ck_mpu, ~0)) अणु
		pr_err("System frequencies not set, using default. Check your config.\n");
		/*
		 * Reprogramming the DPLL is tricky, it must be करोne from SRAM.
		 */
		omap_sram_reprogram_घड़ी(0x2290, 0x0005);
		ck_dpll1.rate = OMAP1_DPLL1_SANE_VALUE;
	पूर्ण
	propagate_rate(&ck_dpll1);
	omap1_show_rates();
	loops_per_jअगरfy = cpufreq_scale(loops_per_jअगरfy, rate, ck_dpll1.rate);
पूर्ण
