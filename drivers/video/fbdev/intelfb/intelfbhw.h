<शैली गुरु>
#अगर_अघोषित _INTELFBHW_H
#घोषणा _INTELFBHW_H

/* $DHD: पूर्णांकelfb/पूर्णांकelfbhw.h,v 1.5 2003/06/27 15:06:25 dawes Exp $ */


/*** HW-specअगरic data ***/

/* Inक्रमmation about the 852GM/855GM variants */
#घोषणा INTEL_85X_CAPID		0x44
#घोषणा INTEL_85X_VARIANT_MASK		0x7
#घोषणा INTEL_85X_VARIANT_SHIFT		5
#घोषणा INTEL_VAR_855GME		0x0
#घोषणा INTEL_VAR_855GM			0x4
#घोषणा INTEL_VAR_852GME		0x2
#घोषणा INTEL_VAR_852GM			0x5

/* Inक्रमmation about DVO/LVDS Ports */
#घोषणा DVOA_PORT  0x1
#घोषणा DVOB_PORT  0x2
#घोषणा DVOC_PORT  0x4
#घोषणा LVDS_PORT  0x8

/*
 * The Bridge device's PCI config space has inक्रमmation about the
 * fb aperture size and the amount of pre-reserved memory.
 */
#घोषणा INTEL_GMCH_CTRL		0x52
#घोषणा INTEL_GMCH_ENABLED		0x4
#घोषणा INTEL_GMCH_MEM_MASK		0x1
#घोषणा INTEL_GMCH_MEM_64M		0x1
#घोषणा INTEL_GMCH_MEM_128M		0

#घोषणा INTEL_830_GMCH_GMS_MASK		(0x7 << 4)
#घोषणा INTEL_830_GMCH_GMS_DISABLED	(0x0 << 4)
#घोषणा INTEL_830_GMCH_GMS_LOCAL	(0x1 << 4)
#घोषणा INTEL_830_GMCH_GMS_STOLEN_512	(0x2 << 4)
#घोषणा INTEL_830_GMCH_GMS_STOLEN_1024	(0x3 << 4)
#घोषणा INTEL_830_GMCH_GMS_STOLEN_8192	(0x4 << 4)

#घोषणा INTEL_855_GMCH_GMS_MASK		(0x7 << 4)
#घोषणा INTEL_855_GMCH_GMS_DISABLED	(0x0 << 4)
#घोषणा INTEL_855_GMCH_GMS_STOLEN_1M	(0x1 << 4)
#घोषणा INTEL_855_GMCH_GMS_STOLEN_4M	(0x2 << 4)
#घोषणा INTEL_855_GMCH_GMS_STOLEN_8M	(0x3 << 4)
#घोषणा INTEL_855_GMCH_GMS_STOLEN_16M	(0x4 << 4)
#घोषणा INTEL_855_GMCH_GMS_STOLEN_32M	(0x5 << 4)

#घोषणा INTEL_915G_GMCH_GMS_STOLEN_48M	(0x6 << 4)
#घोषणा INTEL_915G_GMCH_GMS_STOLEN_64M	(0x7 << 4)

/* HW रेजिस्टरs */

/* Fence रेजिस्टरs */
#घोषणा FENCE			0x2000
#घोषणा FENCE_NUM			8

/* Primary ring buffer */
#घोषणा PRI_RING_TAIL		0x2030
#घोषणा RING_TAIL_MASK			0x001ffff8
#घोषणा RING_INUSE			0x1

#घोषणा PRI_RING_HEAD		0x2034
#घोषणा RING_HEAD_WRAP_MASK		0x7ff
#घोषणा RING_HEAD_WRAP_SHIFT		21
#घोषणा RING_HEAD_MASK			0x001ffffc

#घोषणा PRI_RING_START		0x2038
#घोषणा RING_START_MASK			0xfffff000

#घोषणा PRI_RING_LENGTH		0x203c
#घोषणा RING_LENGTH_MASK		0x001ff000
#घोषणा RING_REPORT_MASK		(0x3 << 1)
#घोषणा RING_NO_REPORT			(0x0 << 1)
#घोषणा RING_REPORT_64K			(0x1 << 1)
#घोषणा RING_REPORT_4K			(0x2 << 1)
#घोषणा RING_REPORT_128K		(0x3 << 1)
#घोषणा RING_ENABLE			0x1

/*
 * Tail can't wrap to any बंदr than RING_MIN_FREE bytes of the head,
 * and the last RING_MIN_FREE bytes need to be padded with MI_NOOP
 */
#घोषणा RING_MIN_FREE			64

#घोषणा IPEHR			0x2088

#घोषणा INSTDONE		0x2090
#घोषणा PRI_RING_EMPTY			1

#घोषणा HWSTAM			0x2098
#घोषणा IER			0x20A0
#घोषणा IIR			0x20A4
#घोषणा IMR			0x20A8
#घोषणा VSYNC_PIPE_A_INTERRUPT		(1 << 7)
#घोषणा PIPE_A_EVENT_INTERRUPT		(1 << 6)
#घोषणा VSYNC_PIPE_B_INTERRUPT		(1 << 5)
#घोषणा PIPE_B_EVENT_INTERRUPT		(1 << 4)
#घोषणा HOST_PORT_EVENT_INTERRUPT	(1 << 3)
#घोषणा CAPTURE_EVENT_INTERRUPT		(1 << 2)
#घोषणा USER_DEFINED_INTERRUPT		(1 << 1)
#घोषणा BREAKPOINT_INTERRUPT		1

#घोषणा INSTPM			0x20c0
#घोषणा SYNC_FLUSH_ENABLE		(1 << 5)

#घोषणा INSTPS			0x20c4

#घोषणा MEM_MODE		0x20cc

#घोषणा MASK_SHIFT			16

#घोषणा FW_BLC_0		0x20d8
#घोषणा FW_DISPA_WM_SHIFT		0
#घोषणा FW_DISPA_WM_MASK		0x3f
#घोषणा FW_DISPA_BL_SHIFT		8
#घोषणा FW_DISPA_BL_MASK		0xf
#घोषणा FW_DISPB_WM_SHIFT		16
#घोषणा FW_DISPB_WM_MASK		0x1f
#घोषणा FW_DISPB_BL_SHIFT		24
#घोषणा FW_DISPB_BL_MASK		0x7

#घोषणा FW_BLC_1		0x20dc
#घोषणा FW_DISPC_WM_SHIFT		0
#घोषणा FW_DISPC_WM_MASK		0x1f
#घोषणा FW_DISPC_BL_SHIFT		8
#घोषणा FW_DISPC_BL_MASK		0x7

#घोषणा GPIOA             0x5010
#घोषणा GPIOB             0x5014
#घोषणा GPIOC             0x5018 /* this may be बाह्यal DDC on i830 */
#घोषणा GPIOD             0x501C /* this is DVO DDC */
#घोषणा GPIOE             0x5020 /* this is DVO i2C */
#घोषणा GPIOF             0x5024

/* PLL रेजिस्टरs */
#घोषणा VGA0_DIVISOR		0x06000
#घोषणा VGA1_DIVISOR		0x06004
#घोषणा VGAPD			0x06010
#घोषणा VGAPD_0_P1_SHIFT		0
#घोषणा VGAPD_0_P1_FORCE_DIV2		(1 << 5)
#घोषणा VGAPD_0_P2_SHIFT		7
#घोषणा VGAPD_1_P1_SHIFT		8
#घोषणा VGAPD_1_P1_FORCE_DIV2		(1 << 13)
#घोषणा VGAPD_1_P2_SHIFT		15

#घोषणा DPLL_A			0x06014
#घोषणा DPLL_B			0x06018
#घोषणा DPLL_VCO_ENABLE			(1 << 31)
#घोषणा DPLL_2X_CLOCK_ENABLE		(1 << 30)
#घोषणा DPLL_SYNCLOCK_ENABLE		(1 << 29)
#घोषणा DPLL_VGA_MODE_DISABLE		(1 << 28)
#घोषणा DPLL_P2_MASK			1
#घोषणा DPLL_P2_SHIFT			23
#घोषणा DPLL_I9XX_P2_SHIFT              24
#घोषणा DPLL_P1_FORCE_DIV2		(1 << 21)
#घोषणा DPLL_P1_MASK			0x1f
#घोषणा DPLL_P1_SHIFT			16
#घोषणा DPLL_REFERENCE_SELECT_MASK	(0x3 << 13)
#घोषणा DPLL_REFERENCE_DEFAULT		(0x0 << 13)
#घोषणा DPLL_REFERENCE_TVCLK		(0x2 << 13)
#घोषणा DPLL_RATE_SELECT_MASK		(1 << 8)
#घोषणा DPLL_RATE_SELECT_FP0		(0 << 8)
#घोषणा DPLL_RATE_SELECT_FP1		(1 << 8)

#घोषणा FPA0			0x06040
#घोषणा FPA1			0x06044
#घोषणा FPB0			0x06048
#घोषणा FPB1			0x0604c
#घोषणा FP_DIVISOR_MASK			0x3f
#घोषणा FP_N_DIVISOR_SHIFT		16
#घोषणा FP_M1_DIVISOR_SHIFT		8
#घोषणा FP_M2_DIVISOR_SHIFT		0

/* PLL parameters (these are क्रम 852GM/855GM/865G, check earlier chips). */
/* Clock values are in units of kHz */
#घोषणा PLL_REFCLK		48000
#घोषणा MIN_CLOCK		25000
#घोषणा MAX_CLOCK		350000

/* Two pipes */
#घोषणा PIPE_A			0
#घोषणा PIPE_B			1
#घोषणा PIPE_MASK		1

/* palette रेजिस्टरs */
#घोषणा PALETTE_A		0x0a000
#घोषणा PALETTE_B		0x0a800
#अगर_अघोषित PALETTE_8_ENTRIES
#घोषणा PALETTE_8_ENTRIES		256
#पूर्ण_अगर
#घोषणा PALETTE_8_SIZE			(PALETTE_8_ENTRIES * 4)
#घोषणा PALETTE_10_ENTRIES		128
#घोषणा PALETTE_10_SIZE			(PALETTE_10_ENTRIES * 8)
#घोषणा PALETTE_8_MASK			0xff
#घोषणा PALETTE_8_RED_SHIFT		16
#घोषणा PALETTE_8_GREEN_SHIFT		8
#घोषणा PALETTE_8_BLUE_SHIFT		0

/* CRTC रेजिस्टरs */
#घोषणा HTOTAL_A		0x60000
#घोषणा HBLANK_A		0x60004
#घोषणा HSYNC_A			0x60008
#घोषणा VTOTAL_A		0x6000c
#घोषणा VBLANK_A		0x60010
#घोषणा VSYNC_A			0x60014
#घोषणा SRC_SIZE_A		0x6001c
#घोषणा BCLRPAT_A		0x60020

#घोषणा HTOTAL_B		0x61000
#घोषणा HBLANK_B		0x61004
#घोषणा HSYNC_B			0x61008
#घोषणा VTOTAL_B		0x6100c
#घोषणा VBLANK_B		0x61010
#घोषणा VSYNC_B			0x61014
#घोषणा SRC_SIZE_B		0x6101c
#घोषणा BCLRPAT_B		0x61020

#घोषणा HTOTAL_MASK			0xfff
#घोषणा HTOTAL_SHIFT			16
#घोषणा HACTIVE_MASK			0x7ff
#घोषणा HACTIVE_SHIFT			0
#घोषणा HBLANKEND_MASK			0xfff
#घोषणा HBLANKEND_SHIFT			16
#घोषणा HBLANKSTART_MASK		0xfff
#घोषणा HBLANKSTART_SHIFT		0
#घोषणा HSYNCEND_MASK			0xfff
#घोषणा HSYNCEND_SHIFT			16
#घोषणा HSYNCSTART_MASK			0xfff
#घोषणा HSYNCSTART_SHIFT		0
#घोषणा VTOTAL_MASK			0xfff
#घोषणा VTOTAL_SHIFT			16
#घोषणा VACTIVE_MASK			0x7ff
#घोषणा VACTIVE_SHIFT			0
#घोषणा VBLANKEND_MASK			0xfff
#घोषणा VBLANKEND_SHIFT			16
#घोषणा VBLANKSTART_MASK		0xfff
#घोषणा VBLANKSTART_SHIFT		0
#घोषणा VSYNCEND_MASK			0xfff
#घोषणा VSYNCEND_SHIFT			16
#घोषणा VSYNCSTART_MASK			0xfff
#घोषणा VSYNCSTART_SHIFT		0
#घोषणा SRC_SIZE_HORIZ_MASK		0x7ff
#घोषणा SRC_SIZE_HORIZ_SHIFT		16
#घोषणा SRC_SIZE_VERT_MASK		0x7ff
#घोषणा SRC_SIZE_VERT_SHIFT		0

#घोषणा ADPA			0x61100
#घोषणा ADPA_DAC_ENABLE			(1 << 31)
#घोषणा ADPA_DAC_DISABLE		0
#घोषणा ADPA_PIPE_SELECT_SHIFT		30
#घोषणा ADPA_USE_VGA_HVPOLARITY		(1 << 15)
#घोषणा ADPA_SETS_HVPOLARITY		0
#घोषणा ADPA_DPMS_CONTROL_MASK		(0x3 << 10)
#घोषणा ADPA_DPMS_D0			(0x0 << 10)
#घोषणा ADPA_DPMS_D2			(0x1 << 10)
#घोषणा ADPA_DPMS_D1			(0x2 << 10)
#घोषणा ADPA_DPMS_D3			(0x3 << 10)
#घोषणा ADPA_VSYNC_ACTIVE_SHIFT		4
#घोषणा ADPA_HSYNC_ACTIVE_SHIFT		3
#घोषणा ADPA_SYNC_ACTIVE_MASK		1
#घोषणा ADPA_SYNC_ACTIVE_HIGH		1
#घोषणा ADPA_SYNC_ACTIVE_LOW		0

#घोषणा DVOA			0x61120
#घोषणा DVOB			0x61140
#घोषणा DVOC			0x61160
#घोषणा LVDS			0x61180
#घोषणा PORT_ENABLE		        (1 << 31)
#घोषणा PORT_PIPE_SELECT_SHIFT	        30
#घोषणा PORT_TV_FLAGS_MASK              0xFF
#घोषणा PORT_TV_FLAGS                   0xC4	/* ripped from my BIOS
						   to understand and correct */

#घोषणा DVOA_SRCDIM		0x61124
#घोषणा DVOB_SRCDIM		0x61144
#घोषणा DVOC_SRCDIM		0x61164

#घोषणा PIPEA_DSL		0x70000
#घोषणा PIPEB_DSL		0x71000
#घोषणा PIPEACONF		0x70008
#घोषणा PIPEBCONF		0x71008
#घोषणा PIPEASTAT		0x70024 /* bits 0-15 are "write 1 to clear" */
#घोषणा PIPEBSTAT		0x71024

#घोषणा PIPECONF_ENABLE			(1 << 31)
#घोषणा PIPECONF_DISABLE		0
#घोषणा PIPECONF_DOUBLE_WIDE		(1 << 30)
#घोषणा PIPECONF_SINGLE_WIDE		0
#घोषणा PIPECONF_LOCKED			(1 << 25)
#घोषणा PIPECONF_UNLOCKED		0
#घोषणा PIPECONF_GAMMA			(1 << 24)
#घोषणा PIPECONF_PALETTE		0
#घोषणा PIPECONF_PROGRESSIVE			(0 << 21)
#घोषणा PIPECONF_INTERLACE_W_FIELD_INDICATION	(6 << 21)
#घोषणा PIPECONF_INTERLACE_FIELD_0_ONLY		(7 << 21)
#घोषणा PIPECONF_INTERLACE_MASK			(7 << 21)

/* enable bits, ग_लिखो 1 to enable */
#घोषणा PIPESTAT_FIFO_UNDERRUN		(1 << 31)
#घोषणा PIPESTAT_CRC_ERROR_EN		(1 << 29)
#घोषणा PIPESTAT_CRC_DONE_EN		(1 << 28)
#घोषणा PIPESTAT_HOTPLUG_EN		(1 << 26)
#घोषणा PIPESTAT_VERTICAL_SYNC_EN	(1 << 25)
#घोषणा PIPESTAT_DISPLINE_COMP_EN	(1 << 24)
#घोषणा PIPESTAT_FLD_EVT_ODD_EN		(1 << 21)
#घोषणा PIPESTAT_FLD_EVT_EVEN_EN	(1 << 20)
#घोषणा PIPESTAT_TV_HOTPLUG_EN		(1 << 18)
#घोषणा PIPESTAT_VBLANK_EN		(1 << 17)
#घोषणा PIPESTAT_OVL_UPDATE_EN		(1 << 16)
/* status bits, ग_लिखो 1 to clear */
#घोषणा PIPESTAT_HOTPLUG_STATE		(1 << 15)
#घोषणा PIPESTAT_CRC_ERROR		(1 << 13)
#घोषणा PIPESTAT_CRC_DONE		(1 << 12)
#घोषणा PIPESTAT_HOTPLUG		(1 << 10)
#घोषणा PIPESTAT_VSYNC			(1 << 9)
#घोषणा PIPESTAT_DISPLINE_COMP		(1 << 8)
#घोषणा PIPESTAT_FLD_EVT_ODD		(1 << 5)
#घोषणा PIPESTAT_FLD_EVT_EVEN		(1 << 4)
#घोषणा PIPESTAT_TV_HOTPLUG		(1 << 2)
#घोषणा PIPESTAT_VBLANK			(1 << 1)
#घोषणा PIPESTAT_OVL_UPDATE		(1 << 0)

#घोषणा DISPARB			0x70030
#घोषणा DISPARB_AEND_MASK		0x1ff
#घोषणा DISPARB_AEND_SHIFT		0
#घोषणा DISPARB_BEND_MASK		0x3ff
#घोषणा DISPARB_BEND_SHIFT		9

/* Desktop HW cursor */
#घोषणा CURSOR_CONTROL		0x70080
#घोषणा CURSOR_ENABLE			(1 << 31)
#घोषणा CURSOR_GAMMA_ENABLE		(1 << 30)
#घोषणा CURSOR_STRIDE_MASK		(0x3 << 28)
#घोषणा CURSOR_STRIDE_256		(0x0 << 28)
#घोषणा CURSOR_STRIDE_512		(0x1 << 28)
#घोषणा CURSOR_STRIDE_1K		(0x2 << 28)
#घोषणा CURSOR_STRIDE_2K		(0x3 << 28)
#घोषणा CURSOR_FORMAT_MASK		(0x7 << 24)
#घोषणा CURSOR_FORMAT_2C		(0x0 << 24)
#घोषणा CURSOR_FORMAT_3C		(0x1 << 24)
#घोषणा CURSOR_FORMAT_4C		(0x2 << 24)
#घोषणा CURSOR_FORMAT_ARGB		(0x4 << 24)
#घोषणा CURSOR_FORMAT_XRGB		(0x5 << 24)

/* Mobile HW cursor (and i810) */
#घोषणा CURSOR_A_CONTROL	CURSOR_CONTROL
#घोषणा CURSOR_B_CONTROL	0x700c0
#घोषणा CURSOR_MODE_MASK		0x27
#घोषणा CURSOR_MODE_DISABLE		0
#घोषणा CURSOR_MODE_64_3C		0x04
#घोषणा CURSOR_MODE_64_4C_AX		0x05
#घोषणा CURSOR_MODE_64_4C		0x06
#घोषणा CURSOR_MODE_64_32B_AX		0x07
#घोषणा CURSOR_MODE_64_ARGB_AX		0x27
#घोषणा CURSOR_PIPE_SELECT_SHIFT	28
#घोषणा CURSOR_MOBILE_GAMMA_ENABLE	(1 << 26)
#घोषणा CURSOR_MEM_TYPE_LOCAL		(1 << 25)

/* All platक्रमms (desktop has no pipe B) */
#घोषणा CURSOR_A_BASEADDR	0x70084
#घोषणा CURSOR_B_BASEADDR	0x700c4
#घोषणा CURSOR_BASE_MASK		0xffffff00

#घोषणा CURSOR_A_POSITION	0x70088
#घोषणा CURSOR_B_POSITION	0x700c8
#घोषणा CURSOR_POS_SIGN			(1 << 15)
#घोषणा CURSOR_POS_MASK			0x7ff
#घोषणा CURSOR_X_SHIFT			0
#घोषणा CURSOR_Y_SHIFT			16

#घोषणा CURSOR_A_PALETTE0	0x70090
#घोषणा CURSOR_A_PALETTE1	0x70094
#घोषणा CURSOR_A_PALETTE2	0x70098
#घोषणा CURSOR_A_PALETTE3	0x7009c
#घोषणा CURSOR_B_PALETTE0	0x700d0
#घोषणा CURSOR_B_PALETTE1	0x700d4
#घोषणा CURSOR_B_PALETTE2	0x700d8
#घोषणा CURSOR_B_PALETTE3	0x700dc
#घोषणा CURSOR_COLOR_MASK			0xff
#घोषणा CURSOR_RED_SHIFT			16
#घोषणा CURSOR_GREEN_SHIFT			8
#घोषणा CURSOR_BLUE_SHIFT			0
#घोषणा CURSOR_PALETTE_MASK			0xffffff

/* Desktop only */
#घोषणा CURSOR_SIZE		0x700a0
#घोषणा CURSOR_SIZE_MASK		0x3ff
#घोषणा CURSOR_SIZE_H_SHIFT		0
#घोषणा CURSOR_SIZE_V_SHIFT		12

#घोषणा DSPACNTR		0x70180
#घोषणा DSPBCNTR		0x71180
#घोषणा DISPPLANE_PLANE_ENABLE		(1 << 31)
#घोषणा DISPPLANE_PLANE_DISABLE		0
#घोषणा DISPPLANE_GAMMA_ENABLE		(1<<30)
#घोषणा DISPPLANE_GAMMA_DISABLE		0
#घोषणा DISPPLANE_PIXFORMAT_MASK	(0xf<<26)
#घोषणा DISPPLANE_8BPP			(0x2<<26)
#घोषणा DISPPLANE_15_16BPP		(0x4<<26)
#घोषणा DISPPLANE_16BPP			(0x5<<26)
#घोषणा DISPPLANE_32BPP_NO_ALPHA	(0x6<<26)
#घोषणा DISPPLANE_32BPP			(0x7<<26)
#घोषणा DISPPLANE_STEREO_ENABLE		(1<<25)
#घोषणा DISPPLANE_STEREO_DISABLE	0
#घोषणा DISPPLANE_SEL_PIPE_SHIFT	24
#घोषणा DISPPLANE_SRC_KEY_ENABLE	(1<<22)
#घोषणा DISPPLANE_SRC_KEY_DISABLE	0
#घोषणा DISPPLANE_LINE_DOUBLE		(1<<20)
#घोषणा DISPPLANE_NO_LINE_DOUBLE	0
#घोषणा DISPPLANE_STEREO_POLARITY_FIRST	0
#घोषणा DISPPLANE_STEREO_POLARITY_SECOND (1<<18)
/* plane B only */
#घोषणा DISPPLANE_ALPHA_TRANS_ENABLE	(1<<15)
#घोषणा DISPPLANE_ALPHA_TRANS_DISABLE	0
#घोषणा DISPPLANE_SPRITE_ABOVE_DISPLAYA	0
#घोषणा DISPPLANE_SPRITE_ABOVE_OVERLAY	1

#घोषणा DSPABASE		0x70184
#घोषणा DSPASTRIDE		0x70188

#घोषणा DSPBBASE		0x71184
#घोषणा DSPBSTRIDE		0x71188

#घोषणा VGACNTRL		0x71400
#घोषणा VGA_DISABLE			(1 << 31)
#घोषणा VGA_ENABLE			0
#घोषणा VGA_PIPE_SELECT_SHIFT		29
#घोषणा VGA_PALETTE_READ_SELECT		23
#घोषणा VGA_PALETTE_A_WRITE_DISABLE	(1 << 22)
#घोषणा VGA_PALETTE_B_WRITE_DISABLE	(1 << 21)
#घोषणा VGA_LEGACY_PALETTE		(1 << 20)
#घोषणा VGA_6BIT_DAC			0
#घोषणा VGA_8BIT_DAC			(1 << 20)

#घोषणा ADD_ID			0x71408
#घोषणा ADD_ID_MASK			0xff

/* BIOS scratch area रेजिस्टरs (830M and 845G). */
#घोषणा SWF0			0x71410
#घोषणा SWF1			0x71414
#घोषणा SWF2			0x71418
#घोषणा SWF3			0x7141c
#घोषणा SWF4			0x71420
#घोषणा SWF5			0x71424
#घोषणा SWF6			0x71428

/* BIOS scratch area रेजिस्टरs (852GM, 855GM, 865G). */
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

/* Memory Commands */
#घोषणा MI_NOOP			(0x00 << 23)
#घोषणा MI_NOOP_WRITE_ID		(1 << 22)
#घोषणा MI_NOOP_ID_MASK			((1 << 22) - 1)

#घोषणा MI_FLUSH		(0x04 << 23)
#घोषणा MI_WRITE_सूचीTY_STATE		(1 << 4)
#घोषणा MI_END_SCENE			(1 << 3)
#घोषणा MI_INHIBIT_RENDER_CACHE_FLUSH	(1 << 2)
#घोषणा MI_INVALIDATE_MAP_CACHE		(1 << 0)

#घोषणा MI_STORE_DWORD_IMM	((0x20 << 23) | 1)

/* 2D Commands */
#घोषणा COLOR_BLT_CMD		((2 << 29) | (0x40 << 22) | 3)
#घोषणा XY_COLOR_BLT_CMD	((2 << 29) | (0x50 << 22) | 4)
#घोषणा XY_SETUP_CLIP_BLT_CMD	((2 << 29) | (0x03 << 22) | 1)
#घोषणा XY_SRC_COPY_BLT_CMD	((2 << 29) | (0x53 << 22) | 6)
#घोषणा SRC_COPY_BLT_CMD	((2 << 29) | (0x43 << 22) | 4)
#घोषणा XY_MONO_PAT_BLT_CMD	((2 << 29) | (0x52 << 22) | 7)
#घोषणा XY_MONO_SRC_BLT_CMD	((2 << 29) | (0x54 << 22) | 6)
#घोषणा XY_MONO_SRC_IMM_BLT_CMD	((2 << 29) | (0x71 << 22) | 5)
#घोषणा TXT_IMM_BLT_CMD	        ((2 << 29) | (0x30 << 22) | 2)
#घोषणा SETUP_BLT_CMD	        ((2 << 29) | (0x00 << 22) | 6)

#घोषणा DW_LENGTH_MASK			0xff

#घोषणा WRITE_ALPHA			(1 << 21)
#घोषणा WRITE_RGB			(1 << 20)
#घोषणा VERT_SEED			(3 << 8)
#घोषणा HORIZ_SEED			(3 << 12)

#घोषणा COLOR_DEPTH_8			(0 << 24)
#घोषणा COLOR_DEPTH_16			(1 << 24)
#घोषणा COLOR_DEPTH_32			(3 << 24)

#घोषणा SRC_ROP_GXCOPY			0xcc
#घोषणा SRC_ROP_GXXOR			0x66

#घोषणा PAT_ROP_GXCOPY                  0xf0
#घोषणा PAT_ROP_GXXOR                   0x5a

#घोषणा PITCH_SHIFT			0
#घोषणा ROP_SHIFT			16
#घोषणा WIDTH_SHIFT			0
#घोषणा HEIGHT_SHIFT			16

/* in bytes */
#घोषणा MAX_MONO_IMM_SIZE		128


/*** Macros ***/

/* I/O macros */
#घोषणा INREG8(addr)	      पढ़ोb((u8 __iomem *)(dinfo->mmio_base + (addr)))
#घोषणा INREG16(addr)	      पढ़ोw((u16 __iomem *)(dinfo->mmio_base + (addr)))
#घोषणा INREG(addr)	      पढ़ोl((u32 __iomem *)(dinfo->mmio_base + (addr)))
#घोषणा OUTREG8(addr, val)    ग_लिखोb((val),(u8 __iomem *)(dinfo->mmio_base + \
							   (addr)))
#घोषणा OUTREG16(addr, val)    ग_लिखोw((val),(u16 __iomem *)(dinfo->mmio_base + \
							   (addr)))
#घोषणा OUTREG(addr, val)     ग_लिखोl((val),(u32 __iomem *)(dinfo->mmio_base + \
                                     (addr)))

/* Ring buffer macros */
#घोषणा OUT_RING(n)	करो अणु						\
	ग_लिखोl((n), (u32 __iomem *)(dinfo->ring.भव + dinfo->ring_tail));\
	dinfo->ring_tail += 4;						\
	dinfo->ring_tail &= dinfo->ring_tail_mask;			\
पूर्ण जबतक (0)

#घोषणा START_RING(n)	करो अणु						\
	अगर (dinfo->ring_space < (n) * 4)				\
		रुको_ring(dinfo,(n) * 4);				\
	dinfo->ring_space -= (n) * 4;					\
पूर्ण जबतक (0)

#घोषणा ADVANCE_RING()	करो अणु						\
	OUTREG(PRI_RING_TAIL, dinfo->ring_tail);                        \
पूर्ण जबतक (0)

#घोषणा DO_RING_IDLE()	करो अणु						\
	u32 head, tail;							\
	करो अणु								\
		head = INREG(PRI_RING_HEAD) & RING_HEAD_MASK;		\
		tail = INREG(PRI_RING_TAIL) & RING_TAIL_MASK;		\
		udelay(10);						\
	पूर्ण जबतक (head != tail);						\
पूर्ण जबतक (0)


/* function protoypes */
बाह्य पूर्णांक पूर्णांकelfbhw_get_chipset(काष्ठा pci_dev *pdev, काष्ठा पूर्णांकelfb_info *dinfo);
बाह्य पूर्णांक पूर्णांकelfbhw_get_memory(काष्ठा pci_dev *pdev, पूर्णांक *aperture_size,
				पूर्णांक *stolen_size);
बाह्य पूर्णांक पूर्णांकelfbhw_check_non_crt(काष्ठा पूर्णांकelfb_info *dinfo);
बाह्य स्थिर अक्षर *पूर्णांकelfbhw_dvo_to_string(पूर्णांक dvo);
बाह्य पूर्णांक पूर्णांकelfbhw_validate_mode(काष्ठा पूर्णांकelfb_info *dinfo,
				   काष्ठा fb_var_screeninfo *var);
बाह्य पूर्णांक पूर्णांकelfbhw_pan_display(काष्ठा fb_var_screeninfo *var,
				 काष्ठा fb_info *info);
बाह्य व्योम पूर्णांकelfbhw_करो_blank(पूर्णांक blank, काष्ठा fb_info *info);
बाह्य व्योम पूर्णांकelfbhw_setcolreg(काष्ठा पूर्णांकelfb_info *dinfo, अचिन्हित regno,
				अचिन्हित red, अचिन्हित green, अचिन्हित blue,
				अचिन्हित transp);
बाह्य पूर्णांक पूर्णांकelfbhw_पढ़ो_hw_state(काष्ठा पूर्णांकelfb_info *dinfo,
				   काष्ठा पूर्णांकelfb_hwstate *hw, पूर्णांक flag);
बाह्य व्योम पूर्णांकelfbhw_prपूर्णांक_hw_state(काष्ठा पूर्णांकelfb_info *dinfo,
				     काष्ठा पूर्णांकelfb_hwstate *hw);
बाह्य पूर्णांक पूर्णांकelfbhw_mode_to_hw(काष्ठा पूर्णांकelfb_info *dinfo,
				काष्ठा पूर्णांकelfb_hwstate *hw,
				काष्ठा fb_var_screeninfo *var);
बाह्य पूर्णांक पूर्णांकelfbhw_program_mode(काष्ठा पूर्णांकelfb_info *dinfo,
				  स्थिर काष्ठा पूर्णांकelfb_hwstate *hw, पूर्णांक blank);
बाह्य व्योम पूर्णांकelfbhw_करो_sync(काष्ठा पूर्णांकelfb_info *dinfo);
बाह्य व्योम पूर्णांकelfbhw_2d_stop(काष्ठा पूर्णांकelfb_info *dinfo);
बाह्य व्योम पूर्णांकelfbhw_2d_start(काष्ठा पूर्णांकelfb_info *dinfo);
बाह्य व्योम पूर्णांकelfbhw_करो_fillrect(काष्ठा पूर्णांकelfb_info *dinfo, u32 x, u32 y,
				  u32 w, u32 h, u32 color, u32 pitch, u32 bpp,
				  u32 rop);
बाह्य व्योम पूर्णांकelfbhw_करो_bitblt(काष्ठा पूर्णांकelfb_info *dinfo, u32 curx, u32 cury,
				u32 dstx, u32 dsty, u32 w, u32 h, u32 pitch,
				u32 bpp);
बाह्य पूर्णांक पूर्णांकelfbhw_करो_drawglyph(काष्ठा पूर्णांकelfb_info *dinfo, u32 fg, u32 bg,
				  u32 w, u32 h, स्थिर u8* cdat, u32 x, u32 y,
				  u32 pitch, u32 bpp);
बाह्य व्योम पूर्णांकelfbhw_cursor_init(काष्ठा पूर्णांकelfb_info *dinfo);
बाह्य व्योम पूर्णांकelfbhw_cursor_hide(काष्ठा पूर्णांकelfb_info *dinfo);
बाह्य व्योम पूर्णांकelfbhw_cursor_show(काष्ठा पूर्णांकelfb_info *dinfo);
बाह्य व्योम पूर्णांकelfbhw_cursor_setpos(काष्ठा पूर्णांकelfb_info *dinfo, पूर्णांक x, पूर्णांक y);
बाह्य व्योम पूर्णांकelfbhw_cursor_setcolor(काष्ठा पूर्णांकelfb_info *dinfo, u32 bg,
				      u32 fg);
बाह्य व्योम पूर्णांकelfbhw_cursor_load(काष्ठा पूर्णांकelfb_info *dinfo, पूर्णांक width,
				  पूर्णांक height, u8 *data);
बाह्य व्योम पूर्णांकelfbhw_cursor_reset(काष्ठा पूर्णांकelfb_info *dinfo);
बाह्य पूर्णांक पूर्णांकelfbhw_enable_irq(काष्ठा पूर्णांकelfb_info *dinfo);
बाह्य व्योम पूर्णांकelfbhw_disable_irq(काष्ठा पूर्णांकelfb_info *dinfo);
बाह्य पूर्णांक पूर्णांकelfbhw_रुको_क्रम_vsync(काष्ठा पूर्णांकelfb_info *dinfo, u32 pipe);
बाह्य पूर्णांक पूर्णांकelfbhw_active_pipe(स्थिर काष्ठा पूर्णांकelfb_hwstate *hw);

#पूर्ण_अगर /* _INTELFBHW_H */
