<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2009, Intel Corporation.
 */
#अगर_अघोषित __PSB_INTEL_REG_H__
#घोषणा __PSB_INTEL_REG_H__

/*
 * GPIO regs
 */
#घोषणा GPIOA			0x5010
#घोषणा GPIOB			0x5014
#घोषणा GPIOC			0x5018
#घोषणा GPIOD			0x501c
#घोषणा GPIOE			0x5020
#घोषणा GPIOF			0x5024
#घोषणा GPIOG			0x5028
#घोषणा GPIOH			0x502c
# define GPIO_CLOCK_सूची_MASK		(1 << 0)
# define GPIO_CLOCK_सूची_IN		(0 << 1)
# define GPIO_CLOCK_सूची_OUT		(1 << 1)
# define GPIO_CLOCK_VAL_MASK		(1 << 2)
# define GPIO_CLOCK_VAL_OUT		(1 << 3)
# define GPIO_CLOCK_VAL_IN		(1 << 4)
# define GPIO_CLOCK_PULLUP_DISABLE	(1 << 5)
# define GPIO_DATA_सूची_MASK		(1 << 8)
# define GPIO_DATA_सूची_IN		(0 << 9)
# define GPIO_DATA_सूची_OUT		(1 << 9)
# define GPIO_DATA_VAL_MASK		(1 << 10)
# define GPIO_DATA_VAL_OUT		(1 << 11)
# define GPIO_DATA_VAL_IN		(1 << 12)
# define GPIO_DATA_PULLUP_DISABLE	(1 << 13)

#घोषणा GMBUS0			0x5100 /* घड़ी/port select */
#घोषणा   GMBUS_RATE_100KHZ	(0<<8)
#घोषणा   GMBUS_RATE_50KHZ	(1<<8)
#घोषणा   GMBUS_RATE_400KHZ	(2<<8) /* reserved on Pineview */
#घोषणा   GMBUS_RATE_1MHZ	(3<<8) /* reserved on Pineview */
#घोषणा   GMBUS_HOLD_EXT	(1<<7) /* 300ns hold समय, rsvd on Pineview */
#घोषणा   GMBUS_PORT_DISABLED	0
#घोषणा   GMBUS_PORT_SSC	1
#घोषणा   GMBUS_PORT_VGADDC	2
#घोषणा   GMBUS_PORT_PANEL	3
#घोषणा   GMBUS_PORT_DPC	4 /* HDMIC */
#घोषणा   GMBUS_PORT_DPB	5 /* SDVO, HDMIB */
				  /* 6 reserved */
#घोषणा   GMBUS_PORT_DPD	7 /* HDMID */
#घोषणा   GMBUS_NUM_PORTS       8
#घोषणा GMBUS1			0x5104 /* command/status */
#घोषणा   GMBUS_SW_CLR_INT	(1<<31)
#घोषणा   GMBUS_SW_RDY		(1<<30)
#घोषणा   GMBUS_ENT		(1<<29) /* enable समयout */
#घोषणा   GMBUS_CYCLE_NONE	(0<<25)
#घोषणा   GMBUS_CYCLE_WAIT	(1<<25)
#घोषणा   GMBUS_CYCLE_INDEX	(2<<25)
#घोषणा   GMBUS_CYCLE_STOP	(4<<25)
#घोषणा   GMBUS_BYTE_COUNT_SHIFT 16
#घोषणा   GMBUS_SLAVE_INDEX_SHIFT 8
#घोषणा   GMBUS_SLAVE_ADDR_SHIFT 1
#घोषणा   GMBUS_SLAVE_READ	(1<<0)
#घोषणा   GMBUS_SLAVE_WRITE	(0<<0)
#घोषणा GMBUS2			0x5108 /* status */
#घोषणा   GMBUS_INUSE		(1<<15)
#घोषणा   GMBUS_HW_WAIT_PHASE	(1<<14)
#घोषणा   GMBUS_STALL_TIMEOUT	(1<<13)
#घोषणा   GMBUS_INT		(1<<12)
#घोषणा   GMBUS_HW_RDY		(1<<11)
#घोषणा   GMBUS_SATOER		(1<<10)
#घोषणा   GMBUS_ACTIVE		(1<<9)
#घोषणा GMBUS3			0x510c /* data buffer bytes 3-0 */
#घोषणा GMBUS4			0x5110 /* पूर्णांकerrupt mask (Pineview+) */
#घोषणा   GMBUS_SLAVE_TIMEOUT_EN (1<<4)
#घोषणा   GMBUS_NAK_EN		(1<<3)
#घोषणा   GMBUS_IDLE_EN		(1<<2)
#घोषणा   GMBUS_HW_WAIT_EN	(1<<1)
#घोषणा   GMBUS_HW_RDY_EN	(1<<0)
#घोषणा GMBUS5			0x5120 /* byte index */
#घोषणा   GMBUS_2BYTE_INDEX_EN	(1<<31)

#घोषणा BLC_PWM_CTL		0x61254
#घोषणा BLC_PWM_CTL2		0x61250
#घोषणा  PWM_ENABLE		(1 << 31)
#घोषणा  PWM_LEGACY_MODE	(1 << 30)
#घोषणा  PWM_PIPE_B		(1 << 29)
#घोषणा BLC_PWM_CTL_C		0x62254
#घोषणा BLC_PWM_CTL2_C		0x62250
#घोषणा BACKLIGHT_MODULATION_FREQ_SHIFT		(17)
/*
 * This is the most signअगरicant 15 bits of the number of backlight cycles in a
 * complete cycle of the modulated backlight control.
 *
 * The actual value is this field multiplied by two.
 */
#घोषणा BACKLIGHT_MODULATION_FREQ_MASK	(0x7fff << 17)
#घोषणा BLM_LEGACY_MODE			(1 << 16)
/*
 * This is the number of cycles out of the backlight modulation cycle क्रम which
 * the backlight is on.
 *
 * This field must be no greater than the number of cycles in the complete
 * backlight modulation cycle.
 */
#घोषणा BACKLIGHT_DUTY_CYCLE_SHIFT	(0)
#घोषणा BACKLIGHT_DUTY_CYCLE_MASK	(0xffff)

#घोषणा I915_GCFGC			0xf0
#घोषणा I915_LOW_FREQUENCY_ENABLE	(1 << 7)
#घोषणा I915_DISPLAY_CLOCK_190_200_MHZ	(0 << 4)
#घोषणा I915_DISPLAY_CLOCK_333_MHZ	(4 << 4)
#घोषणा I915_DISPLAY_CLOCK_MASK		(7 << 4)

#घोषणा I855_HPLLCC			0xc0
#घोषणा I855_CLOCK_CONTROL_MASK		(3 << 0)
#घोषणा I855_CLOCK_133_200		(0 << 0)
#घोषणा I855_CLOCK_100_200		(1 << 0)
#घोषणा I855_CLOCK_100_133		(2 << 0)
#घोषणा I855_CLOCK_166_250		(3 << 0)

/* I830 CRTC रेजिस्टरs */
#घोषणा HTOTAL_A		0x60000
#घोषणा HBLANK_A		0x60004
#घोषणा HSYNC_A			0x60008
#घोषणा VTOTAL_A		0x6000c
#घोषणा VBLANK_A		0x60010
#घोषणा VSYNC_A			0x60014
#घोषणा PIPEASRC		0x6001c
#घोषणा BCLRPAT_A		0x60020
#घोषणा VSYNCSHIFT_A		0x60028

#घोषणा HTOTAL_B		0x61000
#घोषणा HBLANK_B		0x61004
#घोषणा HSYNC_B			0x61008
#घोषणा VTOTAL_B		0x6100c
#घोषणा VBLANK_B		0x61010
#घोषणा VSYNC_B			0x61014
#घोषणा PIPEBSRC		0x6101c
#घोषणा BCLRPAT_B		0x61020
#घोषणा VSYNCSHIFT_B		0x61028

#घोषणा HTOTAL_C		0x62000
#घोषणा HBLANK_C		0x62004
#घोषणा HSYNC_C			0x62008
#घोषणा VTOTAL_C		0x6200c
#घोषणा VBLANK_C		0x62010
#घोषणा VSYNC_C			0x62014
#घोषणा PIPECSRC		0x6201c
#घोषणा BCLRPAT_C		0x62020
#घोषणा VSYNCSHIFT_C		0x62028

#घोषणा PP_STATUS		0x61200
# define PP_ON				(1 << 31)
/*
 * Indicates that all dependencies of the panel are on:
 *
 * - PLL enabled
 * - pipe enabled
 * - LVDS/DVOB/DVOC on
 */
#घोषणा PP_READY			(1 << 30)
#घोषणा PP_SEQUENCE_NONE		(0 << 28)
#घोषणा PP_SEQUENCE_ON			(1 << 28)
#घोषणा PP_SEQUENCE_OFF			(2 << 28)
#घोषणा PP_SEQUENCE_MASK		0x30000000
#घोषणा	PP_CYCLE_DELAY_ACTIVE		(1 << 27)
#घोषणा	PP_SEQUENCE_STATE_ON_IDLE	(1 << 3)
#घोषणा	PP_SEQUENCE_STATE_MASK		0x0000000f

#घोषणा PP_CONTROL		0x61204
#घोषणा POWER_TARGET_ON			(1 << 0)
#घोषणा	PANEL_UNLOCK_REGS		(0xabcd << 16)
#घोषणा	PANEL_UNLOCK_MASK		(0xffff << 16)
#घोषणा	EDP_FORCE_VDD			(1 << 3)
#घोषणा	EDP_BLC_ENABLE			(1 << 2)
#घोषणा	PANEL_POWER_RESET		(1 << 1)
#घोषणा	PANEL_POWER_OFF			(0 << 0)
#घोषणा	PANEL_POWER_ON			(1 << 0)

/* Poulsbo/Oaktrail */
#घोषणा LVDSPP_ON		0x61208
#घोषणा LVDSPP_OFF		0x6120c
#घोषणा PP_CYCLE		0x61210

/* Cedartrail */
#घोषणा PP_ON_DELAYS		0x61208		/* Cedartrail */
#घोषणा PANEL_PORT_SELECT_MASK 		(3 << 30)
#घोषणा PANEL_PORT_SELECT_LVDS 		(0 << 30)
#घोषणा PANEL_PORT_SELECT_EDP		(1 << 30)
#घोषणा PANEL_POWER_UP_DELAY_MASK	(0x1fff0000)
#घोषणा PANEL_POWER_UP_DELAY_SHIFT	16
#घोषणा PANEL_LIGHT_ON_DELAY_MASK	(0x1fff)
#घोषणा PANEL_LIGHT_ON_DELAY_SHIFT	0

#घोषणा PP_OFF_DELAYS		0x6120c		/* Cedartrail */
#घोषणा PANEL_POWER_DOWN_DELAY_MASK	(0x1fff0000)
#घोषणा PANEL_POWER_DOWN_DELAY_SHIFT	16
#घोषणा PANEL_LIGHT_OFF_DELAY_MASK	(0x1fff)
#घोषणा PANEL_LIGHT_OFF_DELAY_SHIFT	0

#घोषणा PP_DIVISOR		0x61210		/* Cedartrail */
#घोषणा  PP_REFERENCE_DIVIDER_MASK	(0xffffff00)
#घोषणा  PP_REFERENCE_DIVIDER_SHIFT	8
#घोषणा  PANEL_POWER_CYCLE_DELAY_MASK	(0x1f)
#घोषणा  PANEL_POWER_CYCLE_DELAY_SHIFT	0

#घोषणा PFIT_CONTROL		0x61230
#घोषणा PFIT_ENABLE			(1 << 31)
#घोषणा PFIT_PIPE_MASK			(3 << 29)
#घोषणा PFIT_PIPE_SHIFT			29
#घोषणा PFIT_SCALING_MODE_PILLARBOX	(1 << 27)
#घोषणा PFIT_SCALING_MODE_LETTERBOX	(3 << 26)
#घोषणा VERT_INTERP_DISABLE		(0 << 10)
#घोषणा VERT_INTERP_BILINEAR		(1 << 10)
#घोषणा VERT_INTERP_MASK		(3 << 10)
#घोषणा VERT_AUTO_SCALE			(1 << 9)
#घोषणा HORIZ_INTERP_DISABLE		(0 << 6)
#घोषणा HORIZ_INTERP_BILINEAR		(1 << 6)
#घोषणा HORIZ_INTERP_MASK		(3 << 6)
#घोषणा HORIZ_AUTO_SCALE		(1 << 5)
#घोषणा PANEL_8TO6_DITHER_ENABLE	(1 << 3)

#घोषणा PFIT_PGM_RATIOS		0x61234
#घोषणा PFIT_VERT_SCALE_MASK			0xfff00000
#घोषणा PFIT_HORIZ_SCALE_MASK			0x0000fff0

#घोषणा PFIT_AUTO_RATIOS	0x61238

#घोषणा DPLL_A			0x06014
#घोषणा DPLL_B			0x06018
#घोषणा DPLL_VCO_ENABLE			(1 << 31)
#घोषणा DPLL_DVO_HIGH_SPEED		(1 << 30)
#घोषणा DPLL_SYNCLOCK_ENABLE		(1 << 29)
#घोषणा DPLL_VGA_MODE_DIS		(1 << 28)
#घोषणा DPLLB_MODE_DAC_SERIAL		(1 << 26)	/* i915 */
#घोषणा DPLLB_MODE_LVDS			(2 << 26)	/* i915 */
#घोषणा DPLL_MODE_MASK			(3 << 26)
#घोषणा DPLL_DAC_SERIAL_P2_CLOCK_DIV_10	(0 << 24)	/* i915 */
#घोषणा DPLL_DAC_SERIAL_P2_CLOCK_DIV_5	(1 << 24)	/* i915 */
#घोषणा DPLLB_LVDS_P2_CLOCK_DIV_14	(0 << 24)	/* i915 */
#घोषणा DPLLB_LVDS_P2_CLOCK_DIV_7	(1 << 24)	/* i915 */
#घोषणा DPLL_P2_CLOCK_DIV_MASK		0x03000000	/* i915 */
#घोषणा DPLL_FPA0h1_P1_POST_DIV_MASK	0x00ff0000	/* i915 */
#घोषणा DPLL_LOCK			(1 << 15)	/* CDV */

/*
 *  The i830 generation, in DAC/serial mode, defines p1 as two plus this
 * bitfield, or just 2 अगर PLL_P1_DIVIDE_BY_TWO is set.
 */
# define DPLL_FPA01_P1_POST_DIV_MASK_I830	0x001f0000
/*
 * The i830 generation, in LVDS mode, defines P1 as the bit number set within
 * this field (only one bit may be set).
 */
#घोषणा DPLL_FPA01_P1_POST_DIV_MASK_I830_LVDS	0x003f0000
#घोषणा DPLL_FPA01_P1_POST_DIV_SHIFT	16
#घोषणा PLL_P2_DIVIDE_BY_4		(1 << 23)	/* i830, required
							 * in DVO non-gang */
# define PLL_P1_DIVIDE_BY_TWO		(1 << 21)	/* i830 */
#घोषणा PLL_REF_INPUT_DREFCLK		(0 << 13)
#घोषणा PLL_REF_INPUT_TVCLKINA		(1 << 13)	/* i830 */
#घोषणा PLL_REF_INPUT_TVCLKINBC		(2 << 13)	/* SDVO
								 * TVCLKIN */
#घोषणा PLLB_REF_INPUT_SPREADSPECTRUMIN	(3 << 13)
#घोषणा PLL_REF_INPUT_MASK		(3 << 13)
#घोषणा PLL_LOAD_PULSE_PHASE_SHIFT	9
/*
 * Parallel to Serial Load Pulse phase selection.
 * Selects the phase क्रम the 10X DPLL घड़ी क्रम the PCIe
 * digital display port. The range is 4 to 13; 10 or more
 * is just a flip delay. The शेष is 6
 */
#घोषणा PLL_LOAD_PULSE_PHASE_MASK	(0xf << PLL_LOAD_PULSE_PHASE_SHIFT)
#घोषणा DISPLAY_RATE_SELECT_FPA1	(1 << 8)

/*
 * SDVO multiplier क्रम 945G/GM. Not used on 965.
 *
 * DPLL_MD_UDI_MULTIPLIER_MASK
 */
#घोषणा SDVO_MULTIPLIER_MASK		0x000000ff
#घोषणा SDVO_MULTIPLIER_SHIFT_HIRES	4
#घोषणा SDVO_MULTIPLIER_SHIFT_VGA	0

/*
 * PLL_MD
 */
/* Pipe A SDVO/UDI घड़ी multiplier/भागider रेजिस्टर क्रम G965. */
#घोषणा DPLL_A_MD		0x0601c
/* Pipe B SDVO/UDI घड़ी multiplier/भागider रेजिस्टर क्रम G965. */
#घोषणा DPLL_B_MD		0x06020
/*
 * UDI pixel भागider, controlling how many pixels are stuffed पूर्णांकo a packet.
 *
 * Value is pixels minus 1.  Must be set to 1 pixel क्रम SDVO.
 */
#घोषणा DPLL_MD_UDI_DIVIDER_MASK	0x3f000000
#घोषणा DPLL_MD_UDI_DIVIDER_SHIFT	24
/* UDI pixel भागider क्रम VGA, same as DPLL_MD_UDI_DIVIDER_MASK. */
#घोषणा DPLL_MD_VGA_UDI_DIVIDER_MASK	0x003f0000
#घोषणा DPLL_MD_VGA_UDI_DIVIDER_SHIFT	16
/*
 * SDVO/UDI pixel multiplier.
 *
 * SDVO requires that the bus घड़ी rate be between 1 and 2 Ghz, and the bus
 * घड़ी rate is 10 बार the DPLL घड़ी.  At low resolution/refresh rate
 * modes, the bus rate would be below the limits, so SDVO allows क्रम stuffing
 * dummy bytes in the datastream at an increased घड़ी rate, with both sides of
 * the link knowing how many bytes are fill.
 *
 * So, क्रम a mode with a करोtघड़ी of 65Mhz, we would want to द्विगुन the घड़ी
 * rate to 130Mhz to get a bus rate of 1.30Ghz.  The DPLL घड़ी rate would be
 * set to 130Mhz, and the SDVO multiplier set to 2x in this रेजिस्टर and
 * through an SDVO command.
 *
 * This रेजिस्टर field has values of multiplication factor minus 1, with
 * a maximum multiplier of 5 क्रम SDVO.
 */
#घोषणा DPLL_MD_UDI_MULTIPLIER_MASK	0x00003f00
#घोषणा DPLL_MD_UDI_MULTIPLIER_SHIFT	8
/*
 * SDVO/UDI pixel multiplier क्रम VGA, same as DPLL_MD_UDI_MULTIPLIER_MASK.
 * This best be set to the शेष value (3) or the CRT won't work. No,
 * I करोn't entirely understand what this करोes...
 */
#घोषणा DPLL_MD_VGA_UDI_MULTIPLIER_MASK	0x0000003f
#घोषणा DPLL_MD_VGA_UDI_MULTIPLIER_SHIFT 0

#घोषणा DPLL_TEST		0x606c
#घोषणा DPLLB_TEST_SDVO_DIV_1		(0 << 22)
#घोषणा DPLLB_TEST_SDVO_DIV_2		(1 << 22)
#घोषणा DPLLB_TEST_SDVO_DIV_4		(2 << 22)
#घोषणा DPLLB_TEST_SDVO_DIV_MASK	(3 << 22)
#घोषणा DPLLB_TEST_N_BYPASS		(1 << 19)
#घोषणा DPLLB_TEST_M_BYPASS		(1 << 18)
#घोषणा DPLLB_INPUT_BUFFER_ENABLE	(1 << 16)
#घोषणा DPLLA_TEST_N_BYPASS		(1 << 3)
#घोषणा DPLLA_TEST_M_BYPASS		(1 << 2)
#घोषणा DPLLA_INPUT_BUFFER_ENABLE	(1 << 0)

#घोषणा ADPA			0x61100
#घोषणा ADPA_DAC_ENABLE			(1 << 31)
#घोषणा ADPA_DAC_DISABLE		0
#घोषणा ADPA_PIPE_SELECT_MASK		(1 << 30)
#घोषणा ADPA_PIPE_A_SELECT		0
#घोषणा ADPA_PIPE_B_SELECT		(1 << 30)
#घोषणा ADPA_USE_VGA_HVPOLARITY		(1 << 15)
#घोषणा ADPA_SETS_HVPOLARITY		0
#घोषणा ADPA_VSYNC_CNTL_DISABLE		(1 << 11)
#घोषणा ADPA_VSYNC_CNTL_ENABLE		0
#घोषणा ADPA_HSYNC_CNTL_DISABLE		(1 << 10)
#घोषणा ADPA_HSYNC_CNTL_ENABLE		0
#घोषणा ADPA_VSYNC_ACTIVE_HIGH		(1 << 4)
#घोषणा ADPA_VSYNC_ACTIVE_LOW		0
#घोषणा ADPA_HSYNC_ACTIVE_HIGH		(1 << 3)
#घोषणा ADPA_HSYNC_ACTIVE_LOW		0

#घोषणा FPA0			0x06040
#घोषणा FPA1			0x06044
#घोषणा FPB0			0x06048
#घोषणा FPB1			0x0604c
#घोषणा FP_N_DIV_MASK			0x003f0000
#घोषणा FP_N_DIV_SHIFT			16
#घोषणा FP_M1_DIV_MASK			0x00003f00
#घोषणा FP_M1_DIV_SHIFT			8
#घोषणा FP_M2_DIV_MASK			0x0000003f
#घोषणा FP_M2_DIV_SHIFT			0

#घोषणा PORT_HOTPLUG_EN		0x61110
#घोषणा HDMIB_HOTPLUG_INT_EN		(1 << 29)
#घोषणा HDMIC_HOTPLUG_INT_EN		(1 << 28)
#घोषणा HDMID_HOTPLUG_INT_EN		(1 << 27)
#घोषणा SDVOB_HOTPLUG_INT_EN		(1 << 26)
#घोषणा SDVOC_HOTPLUG_INT_EN		(1 << 25)
#घोषणा TV_HOTPLUG_INT_EN		(1 << 18)
#घोषणा CRT_HOTPLUG_INT_EN		(1 << 9)
#घोषणा CRT_HOTPLUG_FORCE_DETECT	(1 << 3)
/* CDV.. */
#घोषणा CRT_HOTPLUG_ACTIVATION_PERIOD_64	(1 << 8)
#घोषणा CRT_HOTPLUG_DAC_ON_TIME_2M		(0 << 7)
#घोषणा CRT_HOTPLUG_DAC_ON_TIME_4M		(1 << 7)
#घोषणा CRT_HOTPLUG_VOLTAGE_COMPARE_40		(0 << 5)
#घोषणा CRT_HOTPLUG_VOLTAGE_COMPARE_50		(1 << 5)
#घोषणा CRT_HOTPLUG_VOLTAGE_COMPARE_60		(2 << 5)
#घोषणा CRT_HOTPLUG_VOLTAGE_COMPARE_70		(3 << 5)
#घोषणा CRT_HOTPLUG_VOLTAGE_COMPARE_MASK	(3 << 5)
#घोषणा CRT_HOTPLUG_DETECT_DELAY_1G		(0 << 4)
#घोषणा CRT_HOTPLUG_DETECT_DELAY_2G		(1 << 4)
#घोषणा CRT_HOTPLUG_DETECT_VOLTAGE_325MV	(0 << 2)
#घोषणा CRT_HOTPLUG_DETECT_VOLTAGE_475MV	(1 << 2)
#घोषणा CRT_HOTPLUG_DETECT_MASK			0x000000F8

#घोषणा PORT_HOTPLUG_STAT	0x61114
#घोषणा CRT_HOTPLUG_INT_STATUS		(1 << 11)
#घोषणा TV_HOTPLUG_INT_STATUS		(1 << 10)
#घोषणा CRT_HOTPLUG_MONITOR_MASK	(3 << 8)
#घोषणा CRT_HOTPLUG_MONITOR_COLOR	(3 << 8)
#घोषणा CRT_HOTPLUG_MONITOR_MONO	(2 << 8)
#घोषणा CRT_HOTPLUG_MONITOR_NONE	(0 << 8)
#घोषणा SDVOC_HOTPLUG_INT_STATUS	(1 << 7)
#घोषणा SDVOB_HOTPLUG_INT_STATUS	(1 << 6)

#घोषणा SDVOB			0x61140
#घोषणा SDVOC			0x61160
#घोषणा SDVO_ENABLE			(1 << 31)
#घोषणा SDVO_PIPE_B_SELECT		(1 << 30)
#घोषणा SDVO_STALL_SELECT		(1 << 29)
#घोषणा SDVO_INTERRUPT_ENABLE		(1 << 26)
#घोषणा SDVO_COLOR_RANGE_16_235		(1 << 8)
#घोषणा SDVO_AUDIO_ENABLE		(1 << 6)

/**
 * 915G/GM SDVO pixel multiplier.
 *
 * Programmed value is multiplier - 1, up to 5x.
 *
 * DPLL_MD_UDI_MULTIPLIER_MASK
 */
#घोषणा SDVO_PORT_MULTIPLY_MASK		(7 << 23)
#घोषणा SDVO_PORT_MULTIPLY_SHIFT	23
#घोषणा SDVO_PHASE_SELECT_MASK		(15 << 19)
#घोषणा SDVO_PHASE_SELECT_DEFAULT	(6 << 19)
#घोषणा SDVO_CLOCK_OUTPUT_INVERT	(1 << 18)
#घोषणा SDVOC_GANG_MODE			(1 << 16)
#घोषणा SDVO_BORDER_ENABLE		(1 << 7)
#घोषणा SDVOB_PCIE_CONCURRENCY		(1 << 3)
#घोषणा SDVO_DETECTED			(1 << 2)
/* Bits to be preserved when writing */
#घोषणा SDVOB_PRESERVE_MASK		((1 << 17) | (1 << 16) | (1 << 14))
#घोषणा SDVOC_PRESERVE_MASK		(1 << 17)

/*
 * This रेजिस्टर controls the LVDS output enable, pipe selection, and data
 * क्रमmat selection.
 *
 * All of the घड़ी/data pairs are क्रमce घातered करोwn by घातer sequencing.
 */
#घोषणा LVDS			0x61180
/*
 * Enables the LVDS port.  This bit must be set beक्रमe DPLLs are enabled, as
 * the DPLL semantics change when the LVDS is asचिन्हित to that pipe.
 */
#घोषणा LVDS_PORT_EN			(1 << 31)
/* Selects pipe B क्रम LVDS data.  Must be set on pre-965. */
#घोषणा LVDS_PIPEB_SELECT		(1 << 30)

/* Turns on border drawing to allow centered display. */
#घोषणा LVDS_BORDER_EN			(1 << 15)

/*
 * Enables the A0-A2 data pairs and CLKA, containing 18 bits of color data per
 * pixel.
 */
#घोषणा LVDS_A0A2_CLKA_POWER_MASK	(3 << 8)
#घोषणा LVDS_A0A2_CLKA_POWER_DOWN	(0 << 8)
#घोषणा LVDS_A0A2_CLKA_POWER_UP		(3 << 8)
/*
 * Controls the A3 data pair, which contains the additional LSBs क्रम 24 bit
 * mode.  Only enabled अगर LVDS_A0A2_CLKA_POWER_UP also indicates it should be
 * on.
 */
#घोषणा LVDS_A3_POWER_MASK		(3 << 6)
#घोषणा LVDS_A3_POWER_DOWN		(0 << 6)
#घोषणा LVDS_A3_POWER_UP		(3 << 6)
/*
 * Controls the CLKB pair.  This should only be set when LVDS_B0B3_POWER_UP
 * is set.
 */
#घोषणा LVDS_CLKB_POWER_MASK		(3 << 4)
#घोषणा LVDS_CLKB_POWER_DOWN		(0 << 4)
#घोषणा LVDS_CLKB_POWER_UP		(3 << 4)
/*
 * Controls the B0-B3 data pairs.  This must be set to match the DPLL p2
 * setting क्रम whether we are in dual-channel mode.  The B3 pair will
 * additionally only be घातered up when LVDS_A3_POWER_UP is set.
 */
#घोषणा LVDS_B0B3_POWER_MASK		(3 << 2)
#घोषणा LVDS_B0B3_POWER_DOWN		(0 << 2)
#घोषणा LVDS_B0B3_POWER_UP		(3 << 2)

#घोषणा PIPEACONF		0x70008
#घोषणा PIPEACONF_ENABLE		(1 << 31)
#घोषणा PIPEACONF_DISABLE		0
#घोषणा PIPEACONF_DOUBLE_WIDE		(1 << 30)
#घोषणा PIPECONF_ACTIVE			(1 << 30)
#घोषणा PIPECONF_DSIPLL_LOCK		(1 << 29)
#घोषणा PIPEACONF_SINGLE_WIDE		0
#घोषणा PIPEACONF_PIPE_UNLOCKED		0
#घोषणा PIPEACONF_DSR			(1 << 26)
#घोषणा PIPEACONF_PIPE_LOCKED		(1 << 25)
#घोषणा PIPEACONF_PALETTE		0
#घोषणा PIPECONF_FORCE_BORDER		(1 << 25)
#घोषणा PIPEACONF_GAMMA			(1 << 24)
#घोषणा PIPECONF_PROGRESSIVE		(0 << 21)
#घोषणा PIPECONF_INTERLACE_W_FIELD_INDICATION	(6 << 21)
#घोषणा PIPECONF_INTERLACE_FIELD_0_ONLY		(7 << 21)
#घोषणा PIPECONF_PLANE_OFF		(1 << 19)
#घोषणा PIPECONF_CURSOR_OFF		(1 << 18)

#घोषणा PIPEBCONF		0x71008
#घोषणा PIPEBCONF_ENABLE		(1 << 31)
#घोषणा PIPEBCONF_DISABLE		0
#घोषणा PIPEBCONF_DOUBLE_WIDE		(1 << 30)
#घोषणा PIPEBCONF_DISABLE		0
#घोषणा PIPEBCONF_GAMMA			(1 << 24)
#घोषणा PIPEBCONF_PALETTE		0

#घोषणा PIPECCONF		0x72008

#घोषणा PIPEBGCMAXRED		0x71010
#घोषणा PIPEBGCMAXGREEN		0x71014
#घोषणा PIPEBGCMAXBLUE		0x71018

#घोषणा PIPEASTAT		0x70024
#घोषणा PIPEBSTAT		0x71024
#घोषणा PIPECSTAT		0x72024
#घोषणा PIPE_VBLANK_INTERRUPT_STATUS		(1UL << 1)
#घोषणा PIPE_START_VBLANK_INTERRUPT_STATUS	(1UL << 2)
#घोषणा PIPE_VBLANK_CLEAR			(1 << 1)
#घोषणा PIPE_VBLANK_STATUS			(1 << 1)
#घोषणा PIPE_TE_STATUS				(1UL << 6)
#घोषणा PIPE_DPST_EVENT_STATUS			(1UL << 7)
#घोषणा PIPE_VSYNC_CLEAR			(1UL << 9)
#घोषणा PIPE_VSYNC_STATUS			(1UL << 9)
#घोषणा PIPE_HDMI_AUDIO_UNDERRUN_STATUS		(1UL << 10)
#घोषणा PIPE_HDMI_AUDIO_BUFFER_DONE_STATUS	(1UL << 11)
#घोषणा PIPE_VBLANK_INTERRUPT_ENABLE		(1UL << 17)
#घोषणा PIPE_START_VBLANK_INTERRUPT_ENABLE	(1UL << 18)
#घोषणा PIPE_TE_ENABLE				(1UL << 22)
#घोषणा PIPE_LEGACY_BLC_EVENT_ENABLE		(1UL << 22)
#घोषणा PIPE_DPST_EVENT_ENABLE			(1UL << 23)
#घोषणा PIPE_VSYNC_ENABL			(1UL << 25)
#घोषणा PIPE_HDMI_AUDIO_UNDERRUN		(1UL << 26)
#घोषणा PIPE_HDMI_AUDIO_BUFFER_DONE		(1UL << 27)
#घोषणा PIPE_FIFO_UNDERRUN			(1UL << 31)
#घोषणा PIPE_HDMI_AUDIO_INT_MASK		(PIPE_HDMI_AUDIO_UNDERRUN | \
						PIPE_HDMI_AUDIO_BUFFER_DONE)
#घोषणा PIPE_EVENT_MASK ((1 << 29)|(1 << 28)|(1 << 27)|(1 << 26)|(1 << 24)|(1 << 23)|(1 << 22)|(1 << 21)|(1 << 20)|(1 << 16))
#घोषणा PIPE_VBLANK_MASK ((1 << 25)|(1 << 24)|(1 << 18)|(1 << 17))
#घोषणा HISTOGRAM_INT_CONTROL		0x61268
#घोषणा HISTOGRAM_BIN_DATA		0X61264
#घोषणा HISTOGRAM_LOGIC_CONTROL		0x61260
#घोषणा PWM_CONTROL_LOGIC		0x61250
#घोषणा PIPE_HOTPLUG_INTERRUPT_STATUS		(1UL << 10)
#घोषणा HISTOGRAM_INTERRUPT_ENABLE		(1UL << 31)
#घोषणा HISTOGRAM_LOGIC_ENABLE			(1UL << 31)
#घोषणा PWM_LOGIC_ENABLE			(1UL << 31)
#घोषणा PWM_PHASEIN_ENABLE			(1UL << 25)
#घोषणा PWM_PHASEIN_INT_ENABLE			(1UL << 24)
#घोषणा PWM_PHASEIN_VB_COUNT			0x00001f00
#घोषणा PWM_PHASEIN_INC				0x0000001f
#घोषणा HISTOGRAM_INT_CTRL_CLEAR		(1UL << 30)
#घोषणा DPST_YUV_LUMA_MODE			0

#घोषणा PIPEAFRAMEHIGH		0x70040
#घोषणा PIPEAFRAMEPIXEL		0x70044
#घोषणा PIPEBFRAMEHIGH		0x71040
#घोषणा PIPEBFRAMEPIXEL		0x71044
#घोषणा PIPECFRAMEHIGH		0x72040
#घोषणा PIPECFRAMEPIXEL		0x72044
#घोषणा PIPE_FRAME_HIGH_MASK	0x0000ffff
#घोषणा PIPE_FRAME_HIGH_SHIFT	0
#घोषणा PIPE_FRAME_LOW_MASK	0xff000000
#घोषणा PIPE_FRAME_LOW_SHIFT	24
#घोषणा PIPE_PIXEL_MASK		0x00ffffff
#घोषणा PIPE_PIXEL_SHIFT	0

#घोषणा FW_BLC_SELF		0x20e0
#घोषणा FW_BLC_SELF_EN          (1<<15)

#घोषणा DSPARB			0x70030
#घोषणा DSPFW1			0x70034
#घोषणा DSP_FIFO_SR_WM_MASK		0xFF800000
#घोषणा DSP_FIFO_SR_WM_SHIFT		23
#घोषणा CURSOR_B_FIFO_WM_MASK		0x003F0000
#घोषणा CURSOR_B_FIFO_WM_SHIFT		16
#घोषणा DSPFW2			0x70038
#घोषणा CURSOR_A_FIFO_WM_MASK		0x3F00
#घोषणा CURSOR_A_FIFO_WM_SHIFT		8
#घोषणा DSP_PLANE_C_FIFO_WM_MASK	0x7F
#घोषणा DSP_PLANE_C_FIFO_WM_SHIFT	0
#घोषणा DSPFW3			0x7003c
#घोषणा DSPFW4			0x70050
#घोषणा DSPFW5			0x70054
#घोषणा DSP_PLANE_B_FIFO_WM1_SHIFT	24
#घोषणा DSP_PLANE_A_FIFO_WM1_SHIFT	16
#घोषणा CURSOR_B_FIFO_WM1_SHIFT		8
#घोषणा CURSOR_FIFO_SR_WM1_SHIFT	0
#घोषणा DSPFW6			0x70058
#घोषणा DSPCHICKENBIT		0x70400
#घोषणा DSPACNTR		0x70180
#घोषणा DSPBCNTR		0x71180
#घोषणा DSPCCNTR		0x72180
#घोषणा DISPLAY_PLANE_ENABLE			(1 << 31)
#घोषणा DISPLAY_PLANE_DISABLE			0
#घोषणा DISPPLANE_GAMMA_ENABLE			(1 << 30)
#घोषणा DISPPLANE_GAMMA_DISABLE			0
#घोषणा DISPPLANE_PIXFORMAT_MASK		(0xf << 26)
#घोषणा DISPPLANE_8BPP				(0x2 << 26)
#घोषणा DISPPLANE_15_16BPP			(0x4 << 26)
#घोषणा DISPPLANE_16BPP				(0x5 << 26)
#घोषणा DISPPLANE_32BPP_NO_ALPHA		(0x6 << 26)
#घोषणा DISPPLANE_32BPP				(0x7 << 26)
#घोषणा DISPPLANE_STEREO_ENABLE			(1 << 25)
#घोषणा DISPPLANE_STEREO_DISABLE		0
#घोषणा DISPPLANE_SEL_PIPE_MASK			(1 << 24)
#घोषणा DISPPLANE_SEL_PIPE_POS			24
#घोषणा DISPPLANE_SEL_PIPE_A			0
#घोषणा DISPPLANE_SEL_PIPE_B			(1 << 24)
#घोषणा DISPPLANE_SRC_KEY_ENABLE		(1 << 22)
#घोषणा DISPPLANE_SRC_KEY_DISABLE		0
#घोषणा DISPPLANE_LINE_DOUBLE			(1 << 20)
#घोषणा DISPPLANE_NO_LINE_DOUBLE		0
#घोषणा DISPPLANE_STEREO_POLARITY_FIRST		0
#घोषणा DISPPLANE_STEREO_POLARITY_SECOND	(1 << 18)
/* plane B only */
#घोषणा DISPPLANE_ALPHA_TRANS_ENABLE		(1 << 15)
#घोषणा DISPPLANE_ALPHA_TRANS_DISABLE		0
#घोषणा DISPPLANE_SPRITE_ABOVE_DISPLAYA		0
#घोषणा DISPPLANE_SPRITE_ABOVE_OVERLAY		(1)
#घोषणा DISPPLANE_BOTTOM			(4)

#घोषणा DSPABASE		0x70184
#घोषणा DSPALINOFF		0x70184
#घोषणा DSPASTRIDE		0x70188

#घोषणा DSPBBASE		0x71184
#घोषणा DSPBLINOFF		0X71184
#घोषणा DSPBADDR		DSPBBASE
#घोषणा DSPBSTRIDE		0x71188

#घोषणा DSPCBASE		0x72184
#घोषणा DSPCLINOFF		0x72184
#घोषणा DSPCSTRIDE		0x72188

#घोषणा DSPAKEYVAL		0x70194
#घोषणा DSPAKEYMASK		0x70198

#घोषणा DSPAPOS			0x7018C	/* reserved */
#घोषणा DSPASIZE		0x70190
#घोषणा DSPBPOS			0x7118C
#घोषणा DSPBSIZE		0x71190
#घोषणा DSPCPOS			0x7218C
#घोषणा DSPCSIZE		0x72190

#घोषणा DSPASURF		0x7019C
#घोषणा DSPATILखातापूर्णF		0x701A4

#घोषणा DSPBSURF		0x7119C
#घोषणा DSPBTILखातापूर्णF		0x711A4

#घोषणा DSPCSURF		0x7219C
#घोषणा DSPCTILखातापूर्णF		0x721A4
#घोषणा DSPCKEYMAXVAL		0x721A0
#घोषणा DSPCKEYMINVAL		0x72194
#घोषणा DSPCKEYMSK		0x72198

#घोषणा VGACNTRL		0x71400
#घोषणा VGA_DISP_DISABLE		(1 << 31)
#घोषणा VGA_2X_MODE			(1 << 30)
#घोषणा VGA_PIPE_B_SELECT		(1 << 29)

/*
 * Overlay रेजिस्टरs
 */
#घोषणा OV_C_OFFSET		0x08000
#घोषणा OV_OVADD		0x30000
#घोषणा OV_DOVASTA		0x30008
# define OV_PIPE_SELECT			((1 << 6)|(1 << 7))
# define OV_PIPE_SELECT_POS		6
# define OV_PIPE_A			0
# define OV_PIPE_C			1
#घोषणा OV_OGAMC5		0x30010
#घोषणा OV_OGAMC4		0x30014
#घोषणा OV_OGAMC3		0x30018
#घोषणा OV_OGAMC2		0x3001C
#घोषणा OV_OGAMC1		0x30020
#घोषणा OV_OGAMC0		0x30024
#घोषणा OVC_OVADD		0x38000
#घोषणा OVC_DOVCSTA		0x38008
#घोषणा OVC_OGAMC5		0x38010
#घोषणा OVC_OGAMC4		0x38014
#घोषणा OVC_OGAMC3		0x38018
#घोषणा OVC_OGAMC2		0x3801C
#घोषणा OVC_OGAMC1		0x38020
#घोषणा OVC_OGAMC0		0x38024

/*
 * Some BIOS scratch area रेजिस्टरs.  The 845 (and 830?) store the amount
 * of video memory available to the BIOS in SWF1.
 */
#घोषणा SWF0			0x71410
#घोषणा SWF1			0x71414
#घोषणा SWF2			0x71418
#घोषणा SWF3			0x7141c
#घोषणा SWF4			0x71420
#घोषणा SWF5			0x71424
#घोषणा SWF6			0x71428

/*
 * 855 scratch रेजिस्टरs.
 */
#घोषणा SWF00			0x70410
#घोषणा SWF01			0x70414
#घोषणा SWF02			0x70418
#घोषणा SWF03			0x7041c
#घोषणा SWF04			0x70420
#घोषणा SWF05			0x70424
#घोषणा SWF06			0x70428

#घोषणा SWF10			SWF0
#घोषणा SWF11			SWF1
#घोषणा SWF12			SWF2
#घोषणा SWF13			SWF3
#घोषणा SWF14			SWF4
#घोषणा SWF15			SWF5
#घोषणा SWF16			SWF6

#घोषणा SWF30			0x72414
#घोषणा SWF31			0x72418
#घोषणा SWF32			0x7241c


/*
 * Palette रेजिस्टरs
 */
#घोषणा PALETTE_A		0x0a000
#घोषणा PALETTE_B		0x0a800
#घोषणा PALETTE_C		0x0ac00

/* Cursor A & B regs */
#घोषणा CURACNTR		0x70080
#घोषणा CURSOR_MODE_DISABLE		0x00
#घोषणा CURSOR_MODE_64_32B_AX		0x07
#घोषणा CURSOR_MODE_64_ARGB_AX		((1 << 5) | CURSOR_MODE_64_32B_AX)
#घोषणा MCURSOR_GAMMA_ENABLE		(1 << 26)
#घोषणा CURABASE		0x70084
#घोषणा CURAPOS			0x70088
#घोषणा CURSOR_POS_MASK			0x007FF
#घोषणा CURSOR_POS_SIGN			0x8000
#घोषणा CURSOR_X_SHIFT			0
#घोषणा CURSOR_Y_SHIFT			16
#घोषणा CURBCNTR		0x700c0
#घोषणा CURBBASE		0x700c4
#घोषणा CURBPOS			0x700c8
#घोषणा CURCCNTR		0x700e0
#घोषणा CURCBASE		0x700e4
#घोषणा CURCPOS			0x700e8

/*
 * Interrupt Registers
 */
#घोषणा IER			0x020a0
#घोषणा IIR			0x020a4
#घोषणा IMR			0x020a8
#घोषणा ISR			0x020ac

/*
 * MOORESTOWN delta रेजिस्टरs
 */
#घोषणा MRST_DPLL_A		0x0f014
#घोषणा DPLLA_MODE_LVDS			(2 << 26)	/* mrst */
#घोषणा MRST_FPA0		0x0f040
#घोषणा MRST_FPA1		0x0f044
#घोषणा MRST_PERF_MODE		0x020f4

/*
 * MEDFIELD HDMI रेजिस्टरs
 */
#घोषणा HDMIPHYMISCCTL		0x61134
#घोषणा HDMI_PHY_POWER_DOWN		0x7f
#घोषणा HDMIB_CONTROL		0x61140
#घोषणा HDMIB_PORT_EN			(1 << 31)
#घोषणा HDMIB_PIPE_B_SELECT		(1 << 30)
#घोषणा HDMIB_शून्य_PACKET		(1 << 9)
#घोषणा HDMIB_HDCP_PORT			(1 << 5)

/* #घोषणा LVDS			0x61180 */
#घोषणा MRST_PANEL_8TO6_DITHER_ENABLE	(1 << 25)
#घोषणा MRST_PANEL_24_DOT_1_FORMAT	(1 << 24)
#घोषणा LVDS_A3_POWER_UP_0_OUTPUT	(1 << 6)

#घोषणा MIPI			0x61190
#घोषणा MIPI_C			0x62190
#घोषणा MIPI_PORT_EN			(1 << 31)
/* Turns on border drawing to allow centered display. */
#घोषणा SEL_FLOPPED_HSTX		(1 << 23)
#घोषणा PASS_FROM_SPHY_TO_AFE		(1 << 16)
#घोषणा MIPI_BORDER_EN			(1 << 15)
#घोषणा MIPIA_3LANE_MIPIC_1LANE		0x1
#घोषणा MIPIA_2LANE_MIPIC_2LANE		0x2
#घोषणा TE_TRIGGER_DSI_PROTOCOL		(1 << 2)
#घोषणा TE_TRIGGER_GPIO_PIN		(1 << 3)
#घोषणा MIPI_TE_COUNT		0x61194

/* #घोषणा PP_CONTROL	0x61204 */
#घोषणा POWER_DOWN_ON_RESET		(1 << 1)

/* #घोषणा PFIT_CONTROL	0x61230 */
#घोषणा PFIT_PIPE_SELECT		(3 << 29)
#घोषणा PFIT_PIPE_SELECT_SHIFT		(29)

/* #घोषणा BLC_PWM_CTL		0x61254 */
#घोषणा MRST_BACKLIGHT_MODULATION_FREQ_SHIFT	(16)
#घोषणा MRST_BACKLIGHT_MODULATION_FREQ_MASK	(0xffff << 16)

/* #घोषणा PIPEACONF 0x70008 */
#घोषणा PIPEACONF_PIPE_STATE		(1 << 30)
/* #घोषणा DSPACNTR		0x70180 */

#घोषणा MRST_DSPABASE		0x7019c
#घोषणा MRST_DSPBBASE		0x7119c

/*
 * Moorestown रेजिस्टरs.
 */

/*
 *	MIPI IP रेजिस्टरs
 */
#घोषणा MIPIC_REG_OFFSET		0x800

#घोषणा DEVICE_READY_REG		0xb000
#घोषणा LP_OUTPUT_HOLD				(1 << 16)
#घोषणा EXIT_ULPS_DEV_READY			0x3
#घोषणा LP_OUTPUT_HOLD_RELEASE			0x810000
# define ENTERING_ULPS				(2 << 1)
# define EXITING_ULPS				(1 << 1)
# define ULPS_MASK				(3 << 1)
# define BUS_POSSESSION				(1 << 3)
#घोषणा INTR_STAT_REG			0xb004
#घोषणा RX_SOT_ERROR				(1 << 0)
#घोषणा RX_SOT_SYNC_ERROR			(1 << 1)
#घोषणा RX_ESCAPE_MODE_ENTRY_ERROR		(1 << 3)
#घोषणा RX_LP_TX_SYNC_ERROR			(1 << 4)
#घोषणा RX_HS_RECEIVE_TIMEOUT_ERROR		(1 << 5)
#घोषणा RX_FALSE_CONTROL_ERROR			(1 << 6)
#घोषणा RX_ECC_SINGLE_BIT_ERROR			(1 << 7)
#घोषणा RX_ECC_MULTI_BIT_ERROR			(1 << 8)
#घोषणा RX_CHECKSUM_ERROR			(1 << 9)
#घोषणा RX_DSI_DATA_TYPE_NOT_RECOGNIZED		(1 << 10)
#घोषणा RX_DSI_VC_ID_INVALID			(1 << 11)
#घोषणा TX_FALSE_CONTROL_ERROR			(1 << 12)
#घोषणा TX_ECC_SINGLE_BIT_ERROR			(1 << 13)
#घोषणा TX_ECC_MULTI_BIT_ERROR			(1 << 14)
#घोषणा TX_CHECKSUM_ERROR			(1 << 15)
#घोषणा TX_DSI_DATA_TYPE_NOT_RECOGNIZED		(1 << 16)
#घोषणा TX_DSI_VC_ID_INVALID			(1 << 17)
#घोषणा HIGH_CONTENTION				(1 << 18)
#घोषणा LOW_CONTENTION				(1 << 19)
#घोषणा DPI_FIFO_UNDER_RUN			(1 << 20)
#घोषणा HS_TX_TIMEOUT				(1 << 21)
#घोषणा LP_RX_TIMEOUT				(1 << 22)
#घोषणा TURN_AROUND_ACK_TIMEOUT			(1 << 23)
#घोषणा ACK_WITH_NO_ERROR			(1 << 24)
#घोषणा HS_GENERIC_WR_FIFO_FULL			(1 << 27)
#घोषणा LP_GENERIC_WR_FIFO_FULL			(1 << 28)
#घोषणा SPL_PKT_SENT				(1 << 30)
#घोषणा INTR_EN_REG			0xb008
#घोषणा DSI_FUNC_PRG_REG		0xb00c
#घोषणा DPI_CHANNEL_NUMBER_POS			0x03
#घोषणा DBI_CHANNEL_NUMBER_POS			0x05
#घोषणा FMT_DPI_POS				0x07
#घोषणा FMT_DBI_POS				0x0A
#घोषणा DBI_DATA_WIDTH_POS			0x0D

/* DPI PIXEL FORMATS */
#घोषणा RGB_565_FMT				0x01	/* RGB 565 FORMAT */
#घोषणा RGB_666_FMT				0x02	/* RGB 666 FORMAT */
#घोषणा LRGB_666_FMT				0x03	/* RGB LOOSELY PACKED
							 * 666 FORMAT
							 */
#घोषणा RGB_888_FMT				0x04	/* RGB 888 FORMAT */
#घोषणा VIRTUAL_CHANNEL_NUMBER_0		0x00	/* Virtual channel 0 */
#घोषणा VIRTUAL_CHANNEL_NUMBER_1		0x01	/* Virtual channel 1 */
#घोषणा VIRTUAL_CHANNEL_NUMBER_2		0x02	/* Virtual channel 2 */
#घोषणा VIRTUAL_CHANNEL_NUMBER_3		0x03	/* Virtual channel 3 */

#घोषणा DBI_NOT_SUPPORTED			0x00	/* command mode
							 * is not supported
							 */
#घोषणा DBI_DATA_WIDTH_16BIT			0x01	/* 16 bit data */
#घोषणा DBI_DATA_WIDTH_9BIT			0x02	/* 9 bit data */
#घोषणा DBI_DATA_WIDTH_8BIT			0x03	/* 8 bit data */
#घोषणा DBI_DATA_WIDTH_OPT1			0x04	/* option 1 */
#घोषणा DBI_DATA_WIDTH_OPT2			0x05	/* option 2 */

#घोषणा HS_TX_TIMEOUT_REG		0xb010
#घोषणा LP_RX_TIMEOUT_REG		0xb014
#घोषणा TURN_AROUND_TIMEOUT_REG		0xb018
#घोषणा DEVICE_RESET_REG		0xb01C
#घोषणा DPI_RESOLUTION_REG		0xb020
#घोषणा RES_V_POS				0x10
#घोषणा HORIZ_SYNC_PAD_COUNT_REG	0xb028
#घोषणा HORIZ_BACK_PORCH_COUNT_REG	0xb02C
#घोषणा HORIZ_FRONT_PORCH_COUNT_REG	0xb030
#घोषणा HORIZ_ACTIVE_AREA_COUNT_REG	0xb034
#घोषणा VERT_SYNC_PAD_COUNT_REG		0xb038
#घोषणा VERT_BACK_PORCH_COUNT_REG	0xb03c
#घोषणा VERT_FRONT_PORCH_COUNT_REG	0xb040
#घोषणा HIGH_LOW_SWITCH_COUNT_REG	0xb044
#घोषणा DPI_CONTROL_REG			0xb048
#घोषणा DPI_SHUT_DOWN				(1 << 0)
#घोषणा DPI_TURN_ON				(1 << 1)
#घोषणा DPI_COLOR_MODE_ON			(1 << 2)
#घोषणा DPI_COLOR_MODE_OFF			(1 << 3)
#घोषणा DPI_BACK_LIGHT_ON			(1 << 4)
#घोषणा DPI_BACK_LIGHT_OFF			(1 << 5)
#घोषणा DPI_LP					(1 << 6)
#घोषणा DPI_DATA_REG			0xb04c
#घोषणा DPI_BACK_LIGHT_ON_DATA			0x07
#घोषणा DPI_BACK_LIGHT_OFF_DATA			0x17
#घोषणा INIT_COUNT_REG			0xb050
#घोषणा MAX_RET_PAK_REG			0xb054
#घोषणा VIDEO_FMT_REG			0xb058
#घोषणा COMPLETE_LAST_PCKT			(1 << 2)
#घोषणा EOT_DISABLE_REG			0xb05c
#घोषणा ENABLE_CLOCK_STOPPING			(1 << 1)
#घोषणा LP_BYTECLK_REG			0xb060
#घोषणा LP_GEN_DATA_REG			0xb064
#घोषणा HS_GEN_DATA_REG			0xb068
#घोषणा LP_GEN_CTRL_REG			0xb06C
#घोषणा HS_GEN_CTRL_REG			0xb070
#घोषणा DCS_CHANNEL_NUMBER_POS		0x6
#घोषणा MCS_COMMANDS_POS		0x8
#घोषणा WORD_COUNTS_POS			0x8
#घोषणा MCS_PARAMETER_POS			0x10
#घोषणा GEN_FIFO_STAT_REG		0xb074
#घोषणा HS_DATA_FIFO_FULL			(1 << 0)
#घोषणा HS_DATA_FIFO_HALF_EMPTY			(1 << 1)
#घोषणा HS_DATA_FIFO_EMPTY			(1 << 2)
#घोषणा LP_DATA_FIFO_FULL			(1 << 8)
#घोषणा LP_DATA_FIFO_HALF_EMPTY			(1 << 9)
#घोषणा LP_DATA_FIFO_EMPTY			(1 << 10)
#घोषणा HS_CTRL_FIFO_FULL			(1 << 16)
#घोषणा HS_CTRL_FIFO_HALF_EMPTY			(1 << 17)
#घोषणा HS_CTRL_FIFO_EMPTY			(1 << 18)
#घोषणा LP_CTRL_FIFO_FULL			(1 << 24)
#घोषणा LP_CTRL_FIFO_HALF_EMPTY			(1 << 25)
#घोषणा LP_CTRL_FIFO_EMPTY			(1 << 26)
#घोषणा DBI_FIFO_EMPTY				(1 << 27)
#घोषणा DPI_FIFO_EMPTY				(1 << 28)
#घोषणा HS_LS_DBI_ENABLE_REG		0xb078
#घोषणा TXCLKESC_REG			0xb07c
#घोषणा DPHY_PARAM_REG			0xb080
#घोषणा DBI_BW_CTRL_REG			0xb084
#घोषणा CLK_LANE_SWT_REG		0xb088

/*
 * MIPI Adapter रेजिस्टरs
 */
#घोषणा MIPI_CONTROL_REG		0xb104
#घोषणा MIPI_2X_CLOCK_BITS			((1 << 0) | (1 << 1))
#घोषणा MIPI_DATA_ADDRESS_REG		0xb108
#घोषणा MIPI_DATA_LENGTH_REG		0xb10C
#घोषणा MIPI_COMMAND_ADDRESS_REG	0xb110
#घोषणा MIPI_COMMAND_LENGTH_REG		0xb114
#घोषणा MIPI_READ_DATA_RETURN_REG0	0xb118
#घोषणा MIPI_READ_DATA_RETURN_REG1	0xb11C
#घोषणा MIPI_READ_DATA_RETURN_REG2	0xb120
#घोषणा MIPI_READ_DATA_RETURN_REG3	0xb124
#घोषणा MIPI_READ_DATA_RETURN_REG4	0xb128
#घोषणा MIPI_READ_DATA_RETURN_REG5	0xb12C
#घोषणा MIPI_READ_DATA_RETURN_REG6	0xb130
#घोषणा MIPI_READ_DATA_RETURN_REG7	0xb134
#घोषणा MIPI_READ_DATA_VALID_REG	0xb138

/* DBI COMMANDS */
#घोषणा soft_reset			0x01
/*
 *	The display module perक्रमms a software reset.
 *	Registers are written with their SW Reset शेष values.
 */
#घोषणा get_घातer_mode			0x0a
/*
 *	The display module वापसs the current घातer mode
 */
#घोषणा get_address_mode		0x0b
/*
 *	The display module वापसs the current status.
 */
#घोषणा get_pixel_क्रमmat		0x0c
/*
 *	This command माला_लो the pixel क्रमmat क्रम the RGB image data
 *	used by the पूर्णांकerface.
 */
#घोषणा get_display_mode		0x0d
/*
 *	The display module वापसs the Display Image Mode status.
 */
#घोषणा get_संकेत_mode			0x0e
/*
 *	The display module वापसs the Display Signal Mode.
 */
#घोषणा get_diagnostic_result		0x0f
/*
 *	The display module वापसs the self-diagnostic results following
 *	a Sleep Out command.
 */
#घोषणा enter_sleep_mode		0x10
/*
 *	This command causes the display module to enter the Sleep mode.
 *	In this mode, all unnecessary blocks inside the display module are
 *	disabled except पूर्णांकerface communication. This is the lowest घातer
 *	mode the display module supports.
 */
#घोषणा निकास_sleep_mode			0x11
/*
 *	This command causes the display module to निकास Sleep mode.
 *	All blocks inside the display module are enabled.
 */
#घोषणा enter_partial_mode		0x12
/*
 *	This command causes the display module to enter the Partial Display
 *	Mode. The Partial Display Mode winकरोw is described by the
 *	set_partial_area command.
 */
#घोषणा enter_normal_mode		0x13
/*
 *	This command causes the display module to enter the Normal mode.
 *	Normal Mode is defined as Partial Display mode and Scroll mode are off
 */
#घोषणा निकास_invert_mode		0x20
/*
 *	This command causes the display module to stop inverting the image
 *	data on the display device. The frame memory contents reमुख्य unchanged.
 *	No status bits are changed.
 */
#घोषणा enter_invert_mode		0x21
/*
 *	This command causes the display module to invert the image data only on
 *	the display device. The frame memory contents reमुख्य unchanged.
 *	No status bits are changed.
 */
#घोषणा set_gamma_curve			0x26
/*
 *	This command selects the desired gamma curve क्रम the display device.
 *	Four fixed gamma curves are defined in section DCS spec.
 */
#घोषणा set_display_off			0x28
/* ************************************************************************* *\
This command causes the display module to stop displaying the image data
on the display device. The frame memory contents reमुख्य unchanged.
No status bits are changed.
\* ************************************************************************* */
#घोषणा set_display_on			0x29
/* ************************************************************************* *\
This command causes the display module to start displaying the image data
on the display device. The frame memory contents reमुख्य unchanged.
No status bits are changed.
\* ************************************************************************* */
#घोषणा set_column_address		0x2a
/*
 *	This command defines the column extent of the frame memory accessed by
 *	the hostprocessor with the पढ़ो_memory_जारी and
 *	ग_लिखो_memory_जारी commands.
 *	No status bits are changed.
 */
#घोषणा set_page_addr			0x2b
/*
 *	This command defines the page extent of the frame memory accessed by
 *	the host processor with the ग_लिखो_memory_जारी and
 *	पढ़ो_memory_जारी command.
 *	No status bits are changed.
 */
#घोषणा ग_लिखो_mem_start			0x2c
/*
 *	This command transfers image data from the host processor to the
 *	display modules frame memory starting at the pixel location specअगरied
 *	by preceding set_column_address and set_page_address commands.
 */
#घोषणा set_partial_area		0x30
/*
 *	This command defines the Partial Display mode s display area.
 *	There are two parameters associated with this command, the first
 *	defines the Start Row (SR) and the second the End Row (ER). SR and ER
 *	refer to the Frame Memory Line Poपूर्णांकer.
 */
#घोषणा set_scroll_area			0x33
/*
 *	This command defines the display modules Vertical Scrolling Area.
 */
#घोषणा set_tear_off			0x34
/*
 *	This command turns off the display modules Tearing Effect output
 *	संकेत on the TE संकेत line.
 */
#घोषणा set_tear_on			0x35
/*
 *	This command turns on the display modules Tearing Effect output संकेत
 *	on the TE संकेत line.
 */
#घोषणा set_address_mode		0x36
/*
 *	This command sets the data order क्रम transfers from the host processor
 *	to display modules frame memory,bits B[7:5] and B3, and from the
 *	display modules frame memory to the display device, bits B[2:0] and B4.
 */
#घोषणा set_scroll_start		0x37
/*
 *	This command sets the start of the vertical scrolling area in the frame
 *	memory. The vertical scrolling area is fully defined when this command
 *	is used with the set_scroll_area command The set_scroll_start command
 *	has one parameter, the Vertical Scroll Poपूर्णांकer. The VSP defines the
 *	line in the frame memory that is written to the display device as the
 *	first line of the vertical scroll area.
 */
#घोषणा निकास_idle_mode			0x38
/*
 *	This command causes the display module to निकास Idle mode.
 */
#घोषणा enter_idle_mode			0x39
/*
 *	This command causes the display module to enter Idle Mode.
 *	In Idle Mode, color expression is reduced. Colors are shown on the
 *	display device using the MSB of each of the R, G and B color
 *	components in the frame memory
 */
#घोषणा set_pixel_क्रमmat		0x3a
/*
 *	This command sets the pixel क्रमmat क्रम the RGB image data used by the
 *	पूर्णांकerface.
 *	Bits D[6:4]  DPI Pixel Format Definition
 *	Bits D[2:0]  DBI Pixel Format Definition
 *	Bits D7 and D3 are not used.
 */
#घोषणा DCS_PIXEL_FORMAT_3bpp		0x1
#घोषणा DCS_PIXEL_FORMAT_8bpp		0x2
#घोषणा DCS_PIXEL_FORMAT_12bpp		0x3
#घोषणा DCS_PIXEL_FORMAT_16bpp		0x5
#घोषणा DCS_PIXEL_FORMAT_18bpp		0x6
#घोषणा DCS_PIXEL_FORMAT_24bpp		0x7

#घोषणा ग_लिखो_mem_cont			0x3c

/*
 *	This command transfers image data from the host processor to the
 *	display module's frame memory continuing from the pixel location
 *	following the previous ग_लिखो_memory_जारी or ग_लिखो_memory_start
 *	command.
 */
#घोषणा set_tear_scanline		0x44
/*
 *	This command turns on the display modules Tearing Effect output संकेत
 *	on the TE संकेत line when the display module reaches line N.
 */
#घोषणा get_scanline			0x45
/*
 *	The display module वापसs the current scanline, N, used to update the
 *	 display device. The total number of scanlines on a display device is
 *	defined as VSYNC + VBP + VACT + VFP.The first scanline is defined as
 *	the first line of V Sync and is denoted as Line 0.
 *	When in Sleep Mode, the value वापसed by get_scanline is undefined.
 */

/* MCS or Generic COMMANDS */
/* MCS/generic data type */
#घोषणा GEN_SHORT_WRITE_0	0x03  /* generic लघु ग_लिखो, no parameters */
#घोषणा GEN_SHORT_WRITE_1	0x13  /* generic लघु ग_लिखो, 1 parameters */
#घोषणा GEN_SHORT_WRITE_2	0x23  /* generic लघु ग_लिखो, 2 parameters */
#घोषणा GEN_READ_0		0x04  /* generic पढ़ो, no parameters */
#घोषणा GEN_READ_1		0x14  /* generic पढ़ो, 1 parameters */
#घोषणा GEN_READ_2		0x24  /* generic पढ़ो, 2 parameters */
#घोषणा GEN_LONG_WRITE		0x29  /* generic दीर्घ ग_लिखो */
#घोषणा MCS_SHORT_WRITE_0	0x05  /* MCS लघु ग_लिखो, no parameters */
#घोषणा MCS_SHORT_WRITE_1	0x15  /* MCS लघु ग_लिखो, 1 parameters */
#घोषणा MCS_READ		0x06  /* MCS पढ़ो, no parameters */
#घोषणा MCS_LONG_WRITE		0x39  /* MCS दीर्घ ग_लिखो */
/* MCS/generic commands */
/* TPO MCS */
#घोषणा ग_लिखो_display_profile		0x50
#घोषणा ग_लिखो_display_brightness	0x51
#घोषणा ग_लिखो_ctrl_display		0x53
#घोषणा ग_लिखो_ctrl_cabc			0x55
  #घोषणा UI_IMAGE		0x01
  #घोषणा STILL_IMAGE		0x02
  #घोषणा MOVING_IMAGE		0x03
#घोषणा ग_लिखो_hysteresis		0x57
#घोषणा ग_लिखो_gamma_setting		0x58
#घोषणा ग_लिखो_cabc_min_bright		0x5e
#घोषणा ग_लिखो_kbbc_profile		0x60
/* TMD MCS */
#घोषणा पंचांगd_ग_लिखो_display_brightness 0x8c

/*
 *	This command is used to control ambient light, panel backlight
 *	brightness and gamma settings.
 */
#घोषणा BRIGHT_CNTL_BLOCK_ON	(1 << 5)
#घोषणा AMBIENT_LIGHT_SENSE_ON	(1 << 4)
#घोषणा DISPLAY_DIMMING_ON	(1 << 3)
#घोषणा BACKLIGHT_ON		(1 << 2)
#घोषणा DISPLAY_BRIGHTNESS_AUTO	(1 << 1)
#घोषणा GAMMA_AUTO		(1 << 0)

/* DCS Interface Pixel Formats */
#घोषणा DCS_PIXEL_FORMAT_3BPP	0x1
#घोषणा DCS_PIXEL_FORMAT_8BPP	0x2
#घोषणा DCS_PIXEL_FORMAT_12BPP	0x3
#घोषणा DCS_PIXEL_FORMAT_16BPP	0x5
#घोषणा DCS_PIXEL_FORMAT_18BPP	0x6
#घोषणा DCS_PIXEL_FORMAT_24BPP	0x7
/* ONE PARAMETER READ DATA */
#घोषणा addr_mode_data		0xfc
#घोषणा diag_res_data		0x00
#घोषणा disp_mode_data		0x23
#घोषणा pxl_fmt_data		0x77
#घोषणा pwr_mode_data		0x74
#घोषणा sig_mode_data		0x00
/* TWO PARAMETERS READ DATA */
#घोषणा scanline_data1		0xff
#घोषणा scanline_data2		0xff
#घोषणा NON_BURST_MODE_SYNC_PULSE	0x01	/* Non Burst Mode
						 * with Sync Pulse
						 */
#घोषणा NON_BURST_MODE_SYNC_EVENTS	0x02	/* Non Burst Mode
						 * with Sync events
						 */
#घोषणा BURST_MODE			0x03	/* Burst Mode */
#घोषणा DBI_COMMAND_BUFFER_SIZE		0x240   /* 0x32 */    /* 0x120 */
						/* Allocate at least
						 * 0x100 Byte with 32
						 * byte alignment
						 */
#घोषणा DBI_DATA_BUFFER_SIZE		0x120	/* Allocate at least
						 * 0x100 Byte with 32
						 * byte alignment
						 */
#घोषणा DBI_CB_TIME_OUT			0xFFFF

#घोषणा GEN_FB_TIME_OUT			2000

#घोषणा SKU_83				0x01
#घोषणा SKU_100				0x02
#घोषणा SKU_100L			0x04
#घोषणा SKU_BYPASS			0x08

/* Some handy macros क्रम playing with bitfields. */
#घोषणा PSB_MASK(high, low) (((1<<((high)-(low)+1))-1)<<(low))
#घोषणा SET_FIELD(value, field) (((value) << field ## _SHIFT) & field ## _MASK)
#घोषणा GET_FIELD(word, field) (((word)  & field ## _MASK) >> field ## _SHIFT)

#घोषणा _PIPE(pipe, a, b) ((a) + (pipe)*((b)-(a)))

/* PCI config space */

#घोषणा SB_PCKT         0x02100 /* cedarview */
# define SB_OPCODE_MASK                         PSB_MASK(31, 16)
# define SB_OPCODE_SHIFT                        16
# define SB_OPCODE_READ                         0
# define SB_OPCODE_WRITE                        1
# define SB_DEST_MASK                           PSB_MASK(15, 8)
# define SB_DEST_SHIFT                          8
# define SB_DEST_DPLL                           0x88
# define SB_BYTE_ENABLE_MASK                    PSB_MASK(7, 4)
# define SB_BYTE_ENABLE_SHIFT                   4
# define SB_BUSY                                (1 << 0)

#घोषणा DSPCLK_GATE_D		0x6200
# define VRHUNIT_CLOCK_GATE_DISABLE		(1 << 28) /* Fixed value on CDV */
# define DPOUNIT_CLOCK_GATE_DISABLE		(1 << 11)
# define DPIOUNIT_CLOCK_GATE_DISABLE		(1 << 6)
# define DPUNIT_PIPEB_GATE_DISABLE		(1 << 30)
# define DPUNIT_PIPEA_GATE_DISABLE		(1 << 25)
# define DPCUNIT_CLOCK_GATE_DISABLE		(1 << 24)
# define DPLSUNIT_CLOCK_GATE_DISABLE		(1 << 13)

#घोषणा RAMCLK_GATE_D		0x6210

/* 32-bit value पढ़ो/written from the DPIO reg. */
#घोषणा SB_DATA		0x02104 /* cedarview */
/* 32-bit address of the DPIO reg to be पढ़ो/written. */
#घोषणा SB_ADDR		0x02108 /* cedarview */
#घोषणा DPIO_CFG	0x02110 /* cedarview */
# define DPIO_MODE_SELECT_1			(1 << 3)
# define DPIO_MODE_SELECT_0			(1 << 2)
# define DPIO_SFR_BYPASS			(1 << 1)
/* reset is active low */
# define DPIO_CMN_RESET_N			(1 << 0)

/* Cedarview sideband रेजिस्टरs */
#घोषणा _SB_M_A			0x8008
#घोषणा _SB_M_B			0x8028
#घोषणा SB_M(pipe) _PIPE(pipe, _SB_M_A, _SB_M_B)
# define SB_M_DIVIDER_MASK			(0xFF << 24)
# define SB_M_DIVIDER_SHIFT			24

#घोषणा _SB_N_VCO_A		0x8014
#घोषणा _SB_N_VCO_B		0x8034
#घोषणा SB_N_VCO(pipe) _PIPE(pipe, _SB_N_VCO_A, _SB_N_VCO_B)
#घोषणा SB_N_VCO_SEL_MASK			PSB_MASK(31, 30)
#घोषणा SB_N_VCO_SEL_SHIFT			30
#घोषणा SB_N_DIVIDER_MASK			PSB_MASK(29, 26)
#घोषणा SB_N_DIVIDER_SHIFT			26
#घोषणा SB_N_CB_TUNE_MASK			PSB_MASK(25, 24)
#घोषणा SB_N_CB_TUNE_SHIFT			24

/* the bit 14:13 is used to select between the dअगरferent reference घड़ी क्रम Pipe A/B */
#घोषणा SB_REF_DPLLA		0x8010
#घोषणा SB_REF_DPLLB		0x8030
#घोषणा	REF_CLK_MASK		(0x3 << 13)
#घोषणा REF_CLK_CORE		(0 << 13)
#घोषणा REF_CLK_DPLL		(1 << 13)
#घोषणा REF_CLK_DPLLA		(2 << 13)
/* For the DPLL B, it will use the reference clk from DPLL A when using (2 << 13) */

#घोषणा _SB_REF_A		0x8018
#घोषणा _SB_REF_B		0x8038
#घोषणा SB_REF_SFR(pipe)	_PIPE(pipe, _SB_REF_A, _SB_REF_B)

#घोषणा _SB_P_A			0x801c
#घोषणा _SB_P_B			0x803c
#घोषणा SB_P(pipe) _PIPE(pipe, _SB_P_A, _SB_P_B)
#घोषणा SB_P2_DIVIDER_MASK			PSB_MASK(31, 30)
#घोषणा SB_P2_DIVIDER_SHIFT			30
#घोषणा SB_P2_10				0 /* HDMI, DP, DAC */
#घोषणा SB_P2_5				1 /* DAC */
#घोषणा SB_P2_14				2 /* LVDS single */
#घोषणा SB_P2_7				3 /* LVDS द्विगुन */
#घोषणा SB_P1_DIVIDER_MASK			PSB_MASK(15, 12)
#घोषणा SB_P1_DIVIDER_SHIFT			12

#घोषणा PSB_LANE0		0x120
#घोषणा PSB_LANE1		0x220
#घोषणा PSB_LANE2		0x2320
#घोषणा PSB_LANE3		0x2420

#घोषणा LANE_PLL_MASK		(0x7 << 20)
#घोषणा LANE_PLL_ENABLE		(0x3 << 20)
#घोषणा LANE_PLL_PIPE(p)	(((p) == 0) ? (1 << 21) : (0 << 21))

#घोषणा DP_B				0x64100
#घोषणा DP_C				0x64200

#घोषणा   DP_PORT_EN			(1 << 31)
#घोषणा   DP_PIPEB_SELECT		(1 << 30)
#घोषणा   DP_PIPE_MASK			(1 << 30)

/* Link training mode - select a suitable mode क्रम each stage */
#घोषणा   DP_LINK_TRAIN_PAT_1		(0 << 28)
#घोषणा   DP_LINK_TRAIN_PAT_2		(1 << 28)
#घोषणा   DP_LINK_TRAIN_PAT_IDLE	(2 << 28)
#घोषणा   DP_LINK_TRAIN_OFF		(3 << 28)
#घोषणा   DP_LINK_TRAIN_MASK		(3 << 28)
#घोषणा   DP_LINK_TRAIN_SHIFT		28

/* Signal voltages. These are mostly controlled by the other end */
#घोषणा   DP_VOLTAGE_0_4		(0 << 25)
#घोषणा   DP_VOLTAGE_0_6		(1 << 25)
#घोषणा   DP_VOLTAGE_0_8		(2 << 25)
#घोषणा   DP_VOLTAGE_1_2		(3 << 25)
#घोषणा   DP_VOLTAGE_MASK		(7 << 25)
#घोषणा   DP_VOLTAGE_SHIFT		25

/* Signal pre-emphasis levels, like voltages, the other end tells us what
 * they want
 */
#घोषणा   DP_PRE_EMPHASIS_0		(0 << 22)
#घोषणा   DP_PRE_EMPHASIS_3_5		(1 << 22)
#घोषणा   DP_PRE_EMPHASIS_6		(2 << 22)
#घोषणा   DP_PRE_EMPHASIS_9_5		(3 << 22)
#घोषणा   DP_PRE_EMPHASIS_MASK		(7 << 22)
#घोषणा   DP_PRE_EMPHASIS_SHIFT		22

/* How many wires to use. I guess 3 was too hard */
#घोषणा   DP_PORT_WIDTH_1		(0 << 19)
#घोषणा   DP_PORT_WIDTH_2		(1 << 19)
#घोषणा   DP_PORT_WIDTH_4		(3 << 19)
#घोषणा   DP_PORT_WIDTH_MASK		(7 << 19)

/* Mystic DPCD version 1.1 special mode */
#घोषणा   DP_ENHANCED_FRAMING		(1 << 18)

/** locked once port is enabled */
#घोषणा   DP_PORT_REVERSAL		(1 << 15)

/** sends the घड़ी on lane 15 of the PEG क्रम debug */
#घोषणा   DP_CLOCK_OUTPUT_ENABLE	(1 << 13)

#घोषणा   DP_SCRAMBLING_DISABLE		(1 << 12)
#घोषणा   DP_SCRAMBLING_DISABLE_IRONLAKE	(1 << 7)

/** limit RGB values to aव्योम confusing TVs */
#घोषणा   DP_COLOR_RANGE_16_235		(1 << 8)

/** Turn on the audio link */
#घोषणा   DP_AUDIO_OUTPUT_ENABLE	(1 << 6)

/** vs and hs sync polarity */
#घोषणा   DP_SYNC_VS_HIGH		(1 << 4)
#घोषणा   DP_SYNC_HS_HIGH		(1 << 3)

/** A fantasy */
#घोषणा   DP_DETECTED			(1 << 2)

/** The aux channel provides a way to talk to the
 * संकेत sink क्रम DDC etc. Max packet size supported
 * is 20 bytes in each direction, hence the 5 fixed
 * data रेजिस्टरs
 */
#घोषणा DPB_AUX_CH_CTL			0x64110
#घोषणा DPB_AUX_CH_DATA1		0x64114
#घोषणा DPB_AUX_CH_DATA2		0x64118
#घोषणा DPB_AUX_CH_DATA3		0x6411c
#घोषणा DPB_AUX_CH_DATA4		0x64120
#घोषणा DPB_AUX_CH_DATA5		0x64124

#घोषणा DPC_AUX_CH_CTL			0x64210
#घोषणा DPC_AUX_CH_DATA1		0x64214
#घोषणा DPC_AUX_CH_DATA2		0x64218
#घोषणा DPC_AUX_CH_DATA3		0x6421c
#घोषणा DPC_AUX_CH_DATA4		0x64220
#घोषणा DPC_AUX_CH_DATA5		0x64224

#घोषणा   DP_AUX_CH_CTL_SEND_BUSY	    (1 << 31)
#घोषणा   DP_AUX_CH_CTL_DONE		    (1 << 30)
#घोषणा   DP_AUX_CH_CTL_INTERRUPT	    (1 << 29)
#घोषणा   DP_AUX_CH_CTL_TIME_OUT_ERROR	    (1 << 28)
#घोषणा   DP_AUX_CH_CTL_TIME_OUT_400us	    (0 << 26)
#घोषणा   DP_AUX_CH_CTL_TIME_OUT_600us	    (1 << 26)
#घोषणा   DP_AUX_CH_CTL_TIME_OUT_800us	    (2 << 26)
#घोषणा   DP_AUX_CH_CTL_TIME_OUT_1600us	    (3 << 26)
#घोषणा   DP_AUX_CH_CTL_TIME_OUT_MASK	    (3 << 26)
#घोषणा   DP_AUX_CH_CTL_RECEIVE_ERROR	    (1 << 25)
#घोषणा   DP_AUX_CH_CTL_MESSAGE_SIZE_MASK    (0x1f << 20)
#घोषणा   DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT   20
#घोषणा   DP_AUX_CH_CTL_PRECHARGE_2US_MASK   (0xf << 16)
#घोषणा   DP_AUX_CH_CTL_PRECHARGE_2US_SHIFT  16
#घोषणा   DP_AUX_CH_CTL_AUX_AKSV_SELECT	    (1 << 15)
#घोषणा   DP_AUX_CH_CTL_MANCHESTER_TEST	    (1 << 14)
#घोषणा   DP_AUX_CH_CTL_SYNC_TEST	    (1 << 13)
#घोषणा   DP_AUX_CH_CTL_DEGLITCH_TEST	    (1 << 12)
#घोषणा   DP_AUX_CH_CTL_PRECHARGE_TEST	    (1 << 11)
#घोषणा   DP_AUX_CH_CTL_BIT_CLOCK_2X_MASK    (0x7ff)
#घोषणा   DP_AUX_CH_CTL_BIT_CLOCK_2X_SHIFT   0

/*
 * Computing GMCH M and N values क्रम the Display Port link
 *
 * GMCH M/N = करोt घड़ी * bytes per pixel / ls_clk * # of lanes
 *
 * ls_clk (we assume) is the DP link घड़ी (1.62 or 2.7 GHz)
 *
 * The GMCH value is used पूर्णांकernally
 *
 * bytes_per_pixel is the number of bytes coming out of the plane,
 * which is after the LUTs, so we want the bytes क्रम our color क्रमmat.
 * For our current usage, this is always 3, one byte क्रम R, G and B.
 */

#घोषणा _PIPEA_GMCH_DATA_M			0x70050
#घोषणा _PIPEB_GMCH_DATA_M			0x71050

/* Transfer unit size क्रम display port - 1, शेष is 0x3f (क्रम TU size 64) */
#घोषणा   PIPE_GMCH_DATA_M_TU_SIZE_MASK		(0x3f << 25)
#घोषणा   PIPE_GMCH_DATA_M_TU_SIZE_SHIFT	25

#घोषणा   PIPE_GMCH_DATA_M_MASK			(0xffffff)

#घोषणा _PIPEA_GMCH_DATA_N			0x70054
#घोषणा _PIPEB_GMCH_DATA_N			0x71054
#घोषणा   PIPE_GMCH_DATA_N_MASK			(0xffffff)

/*
 * Computing Link M and N values क्रम the Display Port link
 *
 * Link M / N = pixel_घड़ी / ls_clk
 *
 * (the DP spec calls pixel_घड़ी the 'strm_clk')
 *
 * The Link value is transmitted in the Main Stream
 * Attributes and VB-ID.
 */

#घोषणा _PIPEA_DP_LINK_M				0x70060
#घोषणा _PIPEB_DP_LINK_M				0x71060
#घोषणा   PIPEA_DP_LINK_M_MASK			(0xffffff)

#घोषणा _PIPEA_DP_LINK_N				0x70064
#घोषणा _PIPEB_DP_LINK_N				0x71064
#घोषणा   PIPEA_DP_LINK_N_MASK			(0xffffff)

#घोषणा PIPE_GMCH_DATA_M(pipe) _PIPE(pipe, _PIPEA_GMCH_DATA_M, _PIPEB_GMCH_DATA_M)
#घोषणा PIPE_GMCH_DATA_N(pipe) _PIPE(pipe, _PIPEA_GMCH_DATA_N, _PIPEB_GMCH_DATA_N)
#घोषणा PIPE_DP_LINK_M(pipe) _PIPE(pipe, _PIPEA_DP_LINK_M, _PIPEB_DP_LINK_M)
#घोषणा PIPE_DP_LINK_N(pipe) _PIPE(pipe, _PIPEA_DP_LINK_N, _PIPEB_DP_LINK_N)

#घोषणा   PIPE_BPC_MASK				(7 << 5)
#घोषणा   PIPE_8BPC				(0 << 5)
#घोषणा   PIPE_10BPC				(1 << 5)
#घोषणा   PIPE_6BPC				(2 << 5)

#पूर्ण_अगर
