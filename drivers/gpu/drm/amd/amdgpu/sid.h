<शैली गुरु>
/*
 * Copyright 2011 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Alex Deucher
 */
#अगर_अघोषित SI_H
#घोषणा SI_H

#घोषणा TAHITI_RB_BITMAP_WIDTH_PER_SH  2

#घोषणा TAHITI_GB_ADDR_CONFIG_GOLDEN        0x12011003
#घोषणा VERDE_GB_ADDR_CONFIG_GOLDEN         0x12010002
#घोषणा HAIन_अंक_GB_ADDR_CONFIG_GOLDEN        0x02010001

#घोषणा SI_MAX_SH_GPRS		 	256
#घोषणा SI_MAX_TEMP_GPRS         	16
#घोषणा SI_MAX_SH_THREADS        	256
#घोषणा SI_MAX_SH_STACK_ENTRIES  	4096
#घोषणा SI_MAX_FRC_EOV_CNT       	16384
#घोषणा SI_MAX_BACKENDS          	8
#घोषणा SI_MAX_BACKENDS_MASK     	0xFF
#घोषणा SI_MAX_BACKENDS_PER_SE_MASK     0x0F
#घोषणा SI_MAX_SIMDS             	12
#घोषणा SI_MAX_SIMDS_MASK        	0x0FFF
#घोषणा SI_MAX_SIMDS_PER_SE_MASK        0x00FF
#घोषणा SI_MAX_PIPES            	8
#घोषणा SI_MAX_PIPES_MASK        	0xFF
#घोषणा SI_MAX_PIPES_PER_SIMD_MASK      0x3F
#घोषणा SI_MAX_LDS_NUM           	0xFFFF
#घोषणा SI_MAX_TCC               	16
#घोषणा SI_MAX_TCC_MASK          	0xFFFF
#घोषणा SI_MAX_CTLACKS_ASSERTION_WAIT   100

/* SMC IND accessor regs */
#घोषणा SMC_IND_INDEX_0                              0x80
#घोषणा SMC_IND_DATA_0                               0x81

#घोषणा SMC_IND_ACCESS_CNTL                          0x8A
#       define AUTO_INCREMENT_IND_0                  (1 << 0)
#घोषणा SMC_MESSAGE_0                                0x8B
#घोषणा SMC_RESP_0                                   0x8C

/* CG IND रेजिस्टरs are accessed via SMC indirect space + SMC_CG_IND_START */
#घोषणा SMC_CG_IND_START                    0xc0030000
#घोषणा SMC_CG_IND_END                      0xc0040000

#घोषणा	CG_CGTT_LOCAL_0				0x400
#घोषणा	CG_CGTT_LOCAL_1				0x401

/* SMC IND रेजिस्टरs */
#घोषणा	SMC_SYSCON_RESET_CNTL				0x80000000
#       define RST_REG                                  (1 << 0)
#घोषणा	SMC_SYSCON_CLOCK_CNTL_0				0x80000004
#       define CK_DISABLE                               (1 << 0)
#       define CKEN                                     (1 << 24)

#घोषणा VGA_HDP_CONTROL  				0xCA
#घोषणा		VGA_MEMORY_DISABLE				(1 << 4)

#घोषणा DCCG_DISP_SLOW_SELECT_REG                       0x13F
#घोषणा		DCCG_DISP1_SLOW_SELECT(x)		((x) << 0)
#घोषणा		DCCG_DISP1_SLOW_SELECT_MASK		(7 << 0)
#घोषणा		DCCG_DISP1_SLOW_SELECT_SHIFT		0
#घोषणा		DCCG_DISP2_SLOW_SELECT(x)		((x) << 4)
#घोषणा		DCCG_DISP2_SLOW_SELECT_MASK		(7 << 4)
#घोषणा		DCCG_DISP2_SLOW_SELECT_SHIFT		4

#घोषणा	CG_SPLL_FUNC_CNTL				0x180
#घोषणा		SPLL_RESET				(1 << 0)
#घोषणा		SPLL_SLEEP				(1 << 1)
#घोषणा		SPLL_BYPASS_EN				(1 << 3)
#घोषणा		SPLL_REF_DIV(x)				((x) << 4)
#घोषणा		SPLL_REF_DIV_MASK			(0x3f << 4)
#घोषणा		SPLL_PDIV_A(x)				((x) << 20)
#घोषणा		SPLL_PDIV_A_MASK			(0x7f << 20)
#घोषणा		SPLL_PDIV_A_SHIFT			20
#घोषणा	CG_SPLL_FUNC_CNTL_2				0x181
#घोषणा		SCLK_MUX_SEL(x)				((x) << 0)
#घोषणा		SCLK_MUX_SEL_MASK			(0x1ff << 0)
#घोषणा		SPLL_CTLREQ_CHG				(1 << 23)
#घोषणा		SCLK_MUX_UPDATE				(1 << 26)
#घोषणा	CG_SPLL_FUNC_CNTL_3				0x182
#घोषणा		SPLL_FB_DIV(x)				((x) << 0)
#घोषणा		SPLL_FB_DIV_MASK			(0x3ffffff << 0)
#घोषणा		SPLL_FB_DIV_SHIFT			0
#घोषणा		SPLL_DITHEN				(1 << 28)
#घोषणा	CG_SPLL_FUNC_CNTL_4				0x183

#घोषणा	SPLL_STATUS					0x185
#घोषणा		SPLL_CHG_STATUS				(1 << 1)
#घोषणा	SPLL_CNTL_MODE					0x186
#घोषणा		SPLL_SW_सूची_CONTROL			(1 << 0)
#	define SPLL_REFCLK_SEL(x)			((x) << 26)
#	define SPLL_REFCLK_SEL_MASK			(3 << 26)

#घोषणा	CG_SPLL_SPREAD_SPECTRUM				0x188
#घोषणा		SSEN					(1 << 0)
#घोषणा		CLK_S(x)				((x) << 4)
#घोषणा		CLK_S_MASK				(0xfff << 4)
#घोषणा		CLK_S_SHIFT				4
#घोषणा	CG_SPLL_SPREAD_SPECTRUM_2			0x189
#घोषणा		CLK_V(x)				((x) << 0)
#घोषणा		CLK_V_MASK				(0x3ffffff << 0)
#घोषणा		CLK_V_SHIFT				0

#घोषणा	CG_SPLL_AUTOSCALE_CNTL				0x18b
#       define AUTOSCALE_ON_SS_CLEAR                    (1 << 9)

/* discrete uvd घड़ीs */
#घोषणा	CG_UPLL_FUNC_CNTL				0x18d
#	define UPLL_RESET_MASK				0x00000001
#	define UPLL_SLEEP_MASK				0x00000002
#	define UPLL_BYPASS_EN_MASK			0x00000004
#	define UPLL_CTLREQ_MASK				0x00000008
#	define UPLL_VCO_MODE_MASK			0x00000600
#	define UPLL_REF_DIV_MASK			0x003F0000
#	define UPLL_CTLACK_MASK				0x40000000
#	define UPLL_CTLACK2_MASK			0x80000000
#घोषणा	CG_UPLL_FUNC_CNTL_2				0x18e
#	define UPLL_PDIV_A(x)				((x) << 0)
#	define UPLL_PDIV_A_MASK				0x0000007F
#	define UPLL_PDIV_B(x)				((x) << 8)
#	define UPLL_PDIV_B_MASK				0x00007F00
#	define VCLK_SRC_SEL(x)				((x) << 20)
#	define VCLK_SRC_SEL_MASK			0x01F00000
#	define DCLK_SRC_SEL(x)				((x) << 25)
#	define DCLK_SRC_SEL_MASK			0x3E000000
#घोषणा	CG_UPLL_FUNC_CNTL_3				0x18f
#	define UPLL_FB_DIV(x)				((x) << 0)
#	define UPLL_FB_DIV_MASK				0x01FFFFFF
#घोषणा	CG_UPLL_FUNC_CNTL_4                             0x191
#	define UPLL_SPARE_ISPARE9			0x00020000
#घोषणा	CG_UPLL_FUNC_CNTL_5				0x192
#	define RESET_ANTI_MUX_MASK			0x00000200
#घोषणा	CG_UPLL_SPREAD_SPECTRUM				0x194
#	define SSEN_MASK				0x00000001

#घोषणा	MPLL_BYPASSCLK_SEL				0x197
#	define MPLL_CLKOUT_SEL(x)			((x) << 8)
#	define MPLL_CLKOUT_SEL_MASK			0xFF00

#घोषणा CG_CLKPIN_CNTL                                    0x198
#       define XTALIN_DIVIDE                              (1 << 1)
#       define BCLK_AS_XCLK                               (1 << 2)
#घोषणा CG_CLKPIN_CNTL_2                                  0x199
#       define FORCE_BIF_REFCLK_EN                        (1 << 3)
#       define MUX_TCLK_TO_XCLK                           (1 << 8)

#घोषणा	THM_CLK_CNTL					0x19b
#	define CMON_CLK_SEL(x)				((x) << 0)
#	define CMON_CLK_SEL_MASK			0xFF
#	define TMON_CLK_SEL(x)				((x) << 8)
#	define TMON_CLK_SEL_MASK			0xFF00
#घोषणा	MISC_CLK_CNTL					0x19c
#	define DEEP_SLEEP_CLK_SEL(x)			((x) << 0)
#	define DEEP_SLEEP_CLK_SEL_MASK			0xFF
#	define ZCLK_SEL(x)				((x) << 8)
#	define ZCLK_SEL_MASK				0xFF00

#घोषणा	CG_THERMAL_CTRL					0x1c0
#घोषणा 	DPM_EVENT_SRC(x)			((x) << 0)
#घोषणा 	DPM_EVENT_SRC_MASK			(7 << 0)
#घोषणा		DIG_THERM_DPM(x)			((x) << 14)
#घोषणा		DIG_THERM_DPM_MASK			0x003FC000
#घोषणा		DIG_THERM_DPM_SHIFT			14
#घोषणा	CG_THERMAL_STATUS				0x1c1
#घोषणा		FDO_PWM_DUTY(x)				((x) << 9)
#घोषणा		FDO_PWM_DUTY_MASK			(0xff << 9)
#घोषणा		FDO_PWM_DUTY_SHIFT			9
#घोषणा	CG_THERMAL_INT					0x1c2
#घोषणा		DIG_THERM_INTH(x)			((x) << 8)
#घोषणा		DIG_THERM_INTH_MASK			0x0000FF00
#घोषणा		DIG_THERM_INTH_SHIFT			8
#घोषणा		DIG_THERM_INTL(x)			((x) << 16)
#घोषणा		DIG_THERM_INTL_MASK			0x00FF0000
#घोषणा		DIG_THERM_INTL_SHIFT			16
#घोषणा 	THERM_INT_MASK_HIGH			(1 << 24)
#घोषणा 	THERM_INT_MASK_LOW			(1 << 25)

#घोषणा	CG_MULT_THERMAL_CTRL					0x1c4
#घोषणा		TEMP_SEL(x)					((x) << 20)
#घोषणा		TEMP_SEL_MASK					(0xff << 20)
#घोषणा		TEMP_SEL_SHIFT					20
#घोषणा	CG_MULT_THERMAL_STATUS					0x1c5
#घोषणा		ASIC_MAX_TEMP(x)				((x) << 0)
#घोषणा		ASIC_MAX_TEMP_MASK				0x000001ff
#घोषणा		ASIC_MAX_TEMP_SHIFT				0
#घोषणा		CTF_TEMP(x)					((x) << 9)
#घोषणा		CTF_TEMP_MASK					0x0003fe00
#घोषणा		CTF_TEMP_SHIFT					9

#घोषणा	CG_FDO_CTRL0					0x1d5
#घोषणा		FDO_STATIC_DUTY(x)			((x) << 0)
#घोषणा		FDO_STATIC_DUTY_MASK			0x000000FF
#घोषणा		FDO_STATIC_DUTY_SHIFT			0
#घोषणा	CG_FDO_CTRL1					0x1d6
#घोषणा		FMAX_DUTY100(x)				((x) << 0)
#घोषणा		FMAX_DUTY100_MASK			0x000000FF
#घोषणा		FMAX_DUTY100_SHIFT			0
#घोषणा	CG_FDO_CTRL2					0x1d7
#घोषणा		TMIN(x)					((x) << 0)
#घोषणा		TMIN_MASK				0x000000FF
#घोषणा		TMIN_SHIFT				0
#घोषणा		FDO_PWM_MODE(x)				((x) << 11)
#घोषणा		FDO_PWM_MODE_MASK			(7 << 11)
#घोषणा		FDO_PWM_MODE_SHIFT			11
#घोषणा		TACH_PWM_RESP_RATE(x)			((x) << 25)
#घोषणा		TACH_PWM_RESP_RATE_MASK			(0x7f << 25)
#घोषणा		TACH_PWM_RESP_RATE_SHIFT		25

#घोषणा CG_TACH_CTRL                                    0x1dc
#       define EDGE_PER_REV(x)                          ((x) << 0)
#       define EDGE_PER_REV_MASK                        (0x7 << 0)
#       define EDGE_PER_REV_SHIFT                       0
#       define TARGET_PERIOD(x)                         ((x) << 3)
#       define TARGET_PERIOD_MASK                       0xfffffff8
#       define TARGET_PERIOD_SHIFT                      3
#घोषणा CG_TACH_STATUS                                  0x1dd
#       define TACH_PERIOD(x)                           ((x) << 0)
#       define TACH_PERIOD_MASK                         0xffffffff
#       define TACH_PERIOD_SHIFT                        0

#घोषणा GENERAL_PWRMGT                                  0x1e0
#       define GLOBAL_PWRMGT_EN                         (1 << 0)
#       define STATIC_PM_EN                             (1 << 1)
#       define THERMAL_PROTECTION_DIS                   (1 << 2)
#       define THERMAL_PROTECTION_TYPE                  (1 << 3)
#       define SW_SMIO_INDEX(x)                         ((x) << 6)
#       define SW_SMIO_INDEX_MASK                       (1 << 6)
#       define SW_SMIO_INDEX_SHIFT                      6
#       define VOLT_PWRMGT_EN                           (1 << 10)
#       define DYN_SPREAD_SPECTRUM_EN                   (1 << 23)
#घोषणा CG_TPC                                            0x1e1
#घोषणा SCLK_PWRMGT_CNTL                                  0x1e2
#       define SCLK_PWRMGT_OFF                            (1 << 0)
#       define SCLK_LOW_D1                                (1 << 1)
#       define FIR_RESET                                  (1 << 4)
#       define FIR_FORCE_TREND_SEL                        (1 << 5)
#       define FIR_TREND_MODE                             (1 << 6)
#       define DYN_GFX_CLK_OFF_EN                         (1 << 7)
#       define GFX_CLK_FORCE_ON                           (1 << 8)
#       define GFX_CLK_REQUEST_OFF                        (1 << 9)
#       define GFX_CLK_FORCE_OFF                          (1 << 10)
#       define GFX_CLK_OFF_ACPI_D1                        (1 << 11)
#       define GFX_CLK_OFF_ACPI_D2                        (1 << 12)
#       define GFX_CLK_OFF_ACPI_D3                        (1 << 13)
#       define DYN_LIGHT_SLEEP_EN                         (1 << 14)

#घोषणा TARGET_AND_CURRENT_PROखाता_INDEX                  0x1e6
#       define CURRENT_STATE_INDEX_MASK                   (0xf << 4)
#       define CURRENT_STATE_INDEX_SHIFT                  4

#घोषणा CG_FTV                                            0x1ef

#घोषणा CG_FFCT_0                                         0x1f0
#       define UTC_0(x)                                   ((x) << 0)
#       define UTC_0_MASK                                 (0x3ff << 0)
#       define DTC_0(x)                                   ((x) << 10)
#       define DTC_0_MASK                                 (0x3ff << 10)

#घोषणा CG_BSP                                          0x1ff
#       define BSP(x)					((x) << 0)
#       define BSP_MASK					(0xffff << 0)
#       define BSU(x)					((x) << 16)
#       define BSU_MASK					(0xf << 16)
#घोषणा CG_AT                                           0x200
#       define CG_R(x)					((x) << 0)
#       define CG_R_MASK				(0xffff << 0)
#       define CG_L(x)					((x) << 16)
#       define CG_L_MASK				(0xffff << 16)

#घोषणा CG_GIT                                          0x201
#       define CG_GICST(x)                              ((x) << 0)
#       define CG_GICST_MASK                            (0xffff << 0)
#       define CG_GIPOT(x)                              ((x) << 16)
#       define CG_GIPOT_MASK                            (0xffff << 16)

#घोषणा CG_SSP                                            0x203
#       define SST(x)                                     ((x) << 0)
#       define SST_MASK                                   (0xffff << 0)
#       define SSTU(x)                                    ((x) << 16)
#       define SSTU_MASK                                  (0xf << 16)

#घोषणा CG_DISPLAY_GAP_CNTL                               0x20a
#       define DISP1_GAP(x)                               ((x) << 0)
#       define DISP1_GAP_MASK                             (3 << 0)
#       define DISP2_GAP(x)                               ((x) << 2)
#       define DISP2_GAP_MASK                             (3 << 2)
#       define VBI_TIMER_COUNT(x)                         ((x) << 4)
#       define VBI_TIMER_COUNT_MASK                       (0x3fff << 4)
#       define VBI_TIMER_UNIT(x)                          ((x) << 20)
#       define VBI_TIMER_UNIT_MASK                        (7 << 20)
#       define DISP1_GAP_MCHG(x)                          ((x) << 24)
#       define DISP1_GAP_MCHG_MASK                        (3 << 24)
#       define DISP2_GAP_MCHG(x)                          ((x) << 26)
#       define DISP2_GAP_MCHG_MASK                        (3 << 26)

#घोषणा	CG_ULV_CONTROL					0x21e
#घोषणा	CG_ULV_PARAMETER				0x21f

#घोषणा	SMC_SCRATCH0					0x221

#घोषणा	CG_CAC_CTRL					0x22e
#	define CAC_WINDOW(x)				((x) << 0)
#	define CAC_WINDOW_MASK				0x00ffffff

#घोषणा DMIF_ADDR_CONFIG  				0x2F5

#घोषणा DMIF_ADDR_CALC  				0x300

#घोषणा	PIPE0_DMIF_BUFFER_CONTROL			  0x0328
#       define DMIF_BUFFERS_ALLOCATED(x)                  ((x) << 0)
#       define DMIF_BUFFERS_ALLOCATED_COMPLETED           (1 << 4)

#घोषणा	SRBM_STATUS				        0x394
#घोषणा		GRBM_RQ_PENDING 			(1 << 5)
#घोषणा		VMC_BUSY 				(1 << 8)
#घोषणा		MCB_BUSY 				(1 << 9)
#घोषणा		MCB_NON_DISPLAY_BUSY 			(1 << 10)
#घोषणा		MCC_BUSY 				(1 << 11)
#घोषणा		MCD_BUSY 				(1 << 12)
#घोषणा		SEM_BUSY 				(1 << 14)
#घोषणा		IH_BUSY 				(1 << 17)

#घोषणा	SRBM_SOFT_RESET				        0x398
#घोषणा		SOFT_RESET_BIF				(1 << 1)
#घोषणा		SOFT_RESET_DC				(1 << 5)
#घोषणा		SOFT_RESET_DMA1				(1 << 6)
#घोषणा		SOFT_RESET_GRBM				(1 << 8)
#घोषणा		SOFT_RESET_HDP				(1 << 9)
#घोषणा		SOFT_RESET_IH				(1 << 10)
#घोषणा		SOFT_RESET_MC				(1 << 11)
#घोषणा		SOFT_RESET_ROM				(1 << 14)
#घोषणा		SOFT_RESET_SEM				(1 << 15)
#घोषणा		SOFT_RESET_VMC				(1 << 17)
#घोषणा		SOFT_RESET_DMA				(1 << 20)
#घोषणा		SOFT_RESET_TST				(1 << 21)
#घोषणा		SOFT_RESET_REGBB			(1 << 22)
#घोषणा		SOFT_RESET_ORB				(1 << 23)

#घोषणा	CC_SYS_RB_BACKEND_DISABLE			0x3A0
#घोषणा	GC_USER_SYS_RB_BACKEND_DISABLE			0x3A1

#घोषणा SRBM_READ_ERROR					0x3A6
#घोषणा SRBM_INT_CNTL					0x3A8
#घोषणा SRBM_INT_ACK					0x3AA

#घोषणा	SRBM_STATUS2				        0x3B1
#घोषणा		DMA_BUSY 				(1 << 5)
#घोषणा		DMA1_BUSY 				(1 << 6)

#घोषणा VM_L2_CNTL					0x500
#घोषणा		ENABLE_L2_CACHE					(1 << 0)
#घोषणा		ENABLE_L2_FRAGMENT_PROCESSING			(1 << 1)
#घोषणा		L2_CACHE_PTE_ENDIAN_SWAP_MODE(x)		((x) << 2)
#घोषणा		L2_CACHE_PDE_ENDIAN_SWAP_MODE(x)		((x) << 4)
#घोषणा		ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE		(1 << 9)
#घोषणा		ENABLE_L2_PDE0_CACHE_LRU_UPDATE_BY_WRITE	(1 << 10)
#घोषणा		EFFECTIVE_L2_QUEUE_SIZE(x)			(((x) & 7) << 15)
#घोषणा		CONTEXT1_IDENTITY_ACCESS_MODE(x)		(((x) & 3) << 19)
#घोषणा VM_L2_CNTL2					0x501
#घोषणा		INVALIDATE_ALL_L1_TLBS				(1 << 0)
#घोषणा		INVALIDATE_L2_CACHE				(1 << 1)
#घोषणा		INVALIDATE_CACHE_MODE(x)			((x) << 26)
#घोषणा			INVALIDATE_PTE_AND_PDE_CACHES		0
#घोषणा			INVALIDATE_ONLY_PTE_CACHES		1
#घोषणा			INVALIDATE_ONLY_PDE_CACHES		2
#घोषणा VM_L2_CNTL3					0x502
#घोषणा		BANK_SELECT(x)					((x) << 0)
#घोषणा		L2_CACHE_UPDATE_MODE(x)				((x) << 6)
#घोषणा		L2_CACHE_BIGK_FRAGMENT_SIZE(x)			((x) << 15)
#घोषणा		L2_CACHE_BIGK_ASSOCIATIVITY			(1 << 20)
#घोषणा	VM_L2_STATUS					0x503
#घोषणा		L2_BUSY						(1 << 0)
#घोषणा VM_CONTEXT0_CNTL				0x504
#घोषणा		ENABLE_CONTEXT					(1 << 0)
#घोषणा		PAGE_TABLE_DEPTH(x)				(((x) & 3) << 1)
#घोषणा		RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT		(1 << 3)
#घोषणा		RANGE_PROTECTION_FAULT_ENABLE_DEFAULT		(1 << 4)
#घोषणा		DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT	(1 << 6)
#घोषणा		DUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT	(1 << 7)
#घोषणा		PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT		(1 << 9)
#घोषणा		PDE0_PROTECTION_FAULT_ENABLE_DEFAULT		(1 << 10)
#घोषणा		VALID_PROTECTION_FAULT_ENABLE_INTERRUPT		(1 << 12)
#घोषणा		VALID_PROTECTION_FAULT_ENABLE_DEFAULT		(1 << 13)
#घोषणा		READ_PROTECTION_FAULT_ENABLE_INTERRUPT		(1 << 15)
#घोषणा		READ_PROTECTION_FAULT_ENABLE_DEFAULT		(1 << 16)
#घोषणा		WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT		(1 << 18)
#घोषणा		WRITE_PROTECTION_FAULT_ENABLE_DEFAULT		(1 << 19)
#घोषणा		PAGE_TABLE_BLOCK_SIZE(x)			(((x) & 0xF) << 24)
#घोषणा VM_CONTEXT1_CNTL				0x505
#घोषणा VM_CONTEXT0_CNTL2				0x50C
#घोषणा VM_CONTEXT1_CNTL2				0x50D
#घोषणा	VM_CONTEXT8_PAGE_TABLE_BASE_ADDR		0x50E
#घोषणा	VM_CONTEXT9_PAGE_TABLE_BASE_ADDR		0x50F
#घोषणा	VM_CONTEXT10_PAGE_TABLE_BASE_ADDR		0x510
#घोषणा	VM_CONTEXT11_PAGE_TABLE_BASE_ADDR		0x511
#घोषणा	VM_CONTEXT12_PAGE_TABLE_BASE_ADDR		0x512
#घोषणा	VM_CONTEXT13_PAGE_TABLE_BASE_ADDR		0x513
#घोषणा	VM_CONTEXT14_PAGE_TABLE_BASE_ADDR		0x514
#घोषणा	VM_CONTEXT15_PAGE_TABLE_BASE_ADDR		0x515

#घोषणा	VM_CONTEXT1_PROTECTION_FAULT_ADDR		0x53f
#घोषणा	VM_CONTEXT1_PROTECTION_FAULT_STATUS		0x537
#घोषणा		PROTECTIONS_MASK			(0xf << 0)
#घोषणा		PROTECTIONS_SHIFT			0
		/* bit 0: range
		 * bit 1: pde0
		 * bit 2: valid
		 * bit 3: पढ़ो
		 * bit 4: ग_लिखो
		 */
#घोषणा		MEMORY_CLIENT_ID_MASK			(0xff << 12)
#घोषणा		MEMORY_CLIENT_ID_SHIFT			12
#घोषणा		MEMORY_CLIENT_RW_MASK			(1 << 24)
#घोषणा		MEMORY_CLIENT_RW_SHIFT			24
#घोषणा		FAULT_VMID_MASK				(0xf << 25)
#घोषणा		FAULT_VMID_SHIFT			25

#घोषणा VM_INVALIDATE_REQUEST				0x51E
#घोषणा VM_INVALIDATE_RESPONSE				0x51F

#घोषणा VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR	0x546
#घोषणा VM_CONTEXT1_PROTECTION_FAULT_DEFAULT_ADDR	0x547

#घोषणा	VM_CONTEXT0_PAGE_TABLE_BASE_ADDR		0x54F
#घोषणा	VM_CONTEXT1_PAGE_TABLE_BASE_ADDR		0x550
#घोषणा	VM_CONTEXT2_PAGE_TABLE_BASE_ADDR		0x551
#घोषणा	VM_CONTEXT3_PAGE_TABLE_BASE_ADDR		0x552
#घोषणा	VM_CONTEXT4_PAGE_TABLE_BASE_ADDR		0x553
#घोषणा	VM_CONTEXT5_PAGE_TABLE_BASE_ADDR		0x554
#घोषणा	VM_CONTEXT6_PAGE_TABLE_BASE_ADDR		0x555
#घोषणा	VM_CONTEXT7_PAGE_TABLE_BASE_ADDR		0x556
#घोषणा	VM_CONTEXT0_PAGE_TABLE_START_ADDR		0x557
#घोषणा	VM_CONTEXT1_PAGE_TABLE_START_ADDR		0x558

#घोषणा	VM_CONTEXT0_PAGE_TABLE_END_ADDR			0x55F
#घोषणा	VM_CONTEXT1_PAGE_TABLE_END_ADDR			0x560

#घोषणा VM_L2_CG           				0x570
#घोषणा		MC_CG_ENABLE				(1 << 18)
#घोषणा		MC_LS_ENABLE				(1 << 19)

#घोषणा MC_SHARED_CHMAP						0x801
#घोषणा		NOOFCHAN_SHIFT					12
#घोषणा		NOOFCHAN_MASK					0x0000f000
#घोषणा MC_SHARED_CHREMAP					0x802

#घोषणा	MC_VM_FB_LOCATION				0x809
#घोषणा	MC_VM_AGP_TOP					0x80A
#घोषणा	MC_VM_AGP_BOT					0x80B
#घोषणा	MC_VM_AGP_BASE					0x80C
#घोषणा	MC_VM_SYSTEM_APERTURE_LOW_ADDR			0x80D
#घोषणा	MC_VM_SYSTEM_APERTURE_HIGH_ADDR			0x80E
#घोषणा	MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR		0x80F

#घोषणा	MC_VM_MX_L1_TLB_CNTL				0x819
#घोषणा		ENABLE_L1_TLB					(1 << 0)
#घोषणा		ENABLE_L1_FRAGMENT_PROCESSING			(1 << 1)
#घोषणा		SYSTEM_ACCESS_MODE_PA_ONLY			(0 << 3)
#घोषणा		SYSTEM_ACCESS_MODE_USE_SYS_MAP			(1 << 3)
#घोषणा		SYSTEM_ACCESS_MODE_IN_SYS			(2 << 3)
#घोषणा		SYSTEM_ACCESS_MODE_NOT_IN_SYS			(3 << 3)
#घोषणा		SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU	(0 << 5)
#घोषणा		ENABLE_ADVANCED_DRIVER_MODEL			(1 << 6)

#घोषणा MC_SHARED_BLACKOUT_CNTL           		0x82B

#घोषणा MC_HUB_MISC_HUB_CG           			0x82E
#घोषणा MC_HUB_MISC_VM_CG           			0x82F

#घोषणा MC_HUB_MISC_SIP_CG           			0x830

#घोषणा MC_XPB_CLK_GAT           			0x91E

#घोषणा MC_CITF_MISC_RD_CG           			0x992
#घोषणा MC_CITF_MISC_WR_CG           			0x993
#घोषणा MC_CITF_MISC_VM_CG           			0x994

#घोषणा	MC_ARB_RAMCFG					0x9D8
#घोषणा		NOOFBANK_SHIFT					0
#घोषणा		NOOFBANK_MASK					0x00000003
#घोषणा		NOOFRANK_SHIFT					2
#घोषणा		NOOFRANK_MASK					0x00000004
#घोषणा		NOOFROWS_SHIFT					3
#घोषणा		NOOFROWS_MASK					0x00000038
#घोषणा		NOOFCOLS_SHIFT					6
#घोषणा		NOOFCOLS_MASK					0x000000C0
#घोषणा		CHANSIZE_SHIFT					8
#घोषणा		CHANSIZE_MASK					0x00000100
#घोषणा		CHANSIZE_OVERRIDE				(1 << 11)
#घोषणा		NOOFGROUPS_SHIFT				12
#घोषणा		NOOFGROUPS_MASK					0x00001000

#घोषणा	MC_ARB_DRAM_TIMING				0x9DD
#घोषणा	MC_ARB_DRAM_TIMING2				0x9DE

#घोषणा MC_ARB_BURST_TIME                               0xA02
#घोषणा		STATE0(x)				((x) << 0)
#घोषणा		STATE0_MASK				(0x1f << 0)
#घोषणा		STATE0_SHIFT				0
#घोषणा		STATE1(x)				((x) << 5)
#घोषणा		STATE1_MASK				(0x1f << 5)
#घोषणा		STATE1_SHIFT				5
#घोषणा		STATE2(x)				((x) << 10)
#घोषणा		STATE2_MASK				(0x1f << 10)
#घोषणा		STATE2_SHIFT				10
#घोषणा		STATE3(x)				((x) << 15)
#घोषणा		STATE3_MASK				(0x1f << 15)
#घोषणा		STATE3_SHIFT				15

#घोषणा	MC_SEQ_TRAIN_WAKEUP_CNTL			0xA3A
#घोषणा		TRAIN_DONE_D0      			(1 << 30)
#घोषणा		TRAIN_DONE_D1      			(1 << 31)

#घोषणा MC_SEQ_SUP_CNTL           			0xA32
#घोषणा		RUN_MASK      				(1 << 0)
#घोषणा MC_SEQ_SUP_PGM           			0xA33
#घोषणा MC_PMG_AUTO_CMD           			0xA34

#घोषणा MC_IO_PAD_CNTL_D0           			0xA74
#घोषणा		MEM_FALL_OUT_CMD      			(1 << 8)

#घोषणा MC_SEQ_RAS_TIMING                               0xA28
#घोषणा MC_SEQ_CAS_TIMING                               0xA29
#घोषणा MC_SEQ_MISC_TIMING                              0xA2A
#घोषणा MC_SEQ_MISC_TIMING2                             0xA2B
#घोषणा MC_SEQ_PMG_TIMING                               0xA2C
#घोषणा MC_SEQ_RD_CTL_D0                                0xA2D
#घोषणा MC_SEQ_RD_CTL_D1                                0xA2E
#घोषणा MC_SEQ_WR_CTL_D0                                0xA2F
#घोषणा MC_SEQ_WR_CTL_D1                                0xA30

#घोषणा MC_SEQ_MISC0           				0xA80
#घोषणा 	MC_SEQ_MISC0_VEN_ID_SHIFT               8
#घोषणा 	MC_SEQ_MISC0_VEN_ID_MASK                0x00000f00
#घोषणा 	MC_SEQ_MISC0_VEN_ID_VALUE               3
#घोषणा 	MC_SEQ_MISC0_REV_ID_SHIFT               12
#घोषणा 	MC_SEQ_MISC0_REV_ID_MASK                0x0000f000
#घोषणा 	MC_SEQ_MISC0_REV_ID_VALUE               1
#घोषणा 	MC_SEQ_MISC0_GDDR5_SHIFT                28
#घोषणा 	MC_SEQ_MISC0_GDDR5_MASK                 0xf0000000
#घोषणा 	MC_SEQ_MISC0_GDDR5_VALUE                5
#घोषणा MC_SEQ_MISC1                                    0xA81
#घोषणा MC_SEQ_RESERVE_M                                0xA82
#घोषणा MC_PMG_CMD_EMRS                                 0xA83

#घोषणा MC_SEQ_IO_DEBUG_INDEX           		0xA91
#घोषणा MC_SEQ_IO_DEBUG_DATA           			0xA92

#घोषणा MC_SEQ_MISC5                                    0xA95
#घोषणा MC_SEQ_MISC6                                    0xA96

#घोषणा MC_SEQ_MISC7                                    0xA99

#घोषणा MC_SEQ_RAS_TIMING_LP                            0xA9B
#घोषणा MC_SEQ_CAS_TIMING_LP                            0xA9C
#घोषणा MC_SEQ_MISC_TIMING_LP                           0xA9D
#घोषणा MC_SEQ_MISC_TIMING2_LP                          0xA9E
#घोषणा MC_SEQ_WR_CTL_D0_LP                             0xA9F
#घोषणा MC_SEQ_WR_CTL_D1_LP                             0xAA0
#घोषणा MC_SEQ_PMG_CMD_EMRS_LP                          0xAA1
#घोषणा MC_SEQ_PMG_CMD_MRS_LP                           0xAA2

#घोषणा MC_PMG_CMD_MRS                                  0xAAB

#घोषणा MC_SEQ_RD_CTL_D0_LP                             0xAC7
#घोषणा MC_SEQ_RD_CTL_D1_LP                             0xAC8

#घोषणा MC_PMG_CMD_MRS1                                 0xAD1
#घोषणा MC_SEQ_PMG_CMD_MRS1_LP                          0xAD2
#घोषणा MC_SEQ_PMG_TIMING_LP                            0xAD3

#घोषणा MC_SEQ_WR_CTL_2                                 0xAD5
#घोषणा MC_SEQ_WR_CTL_2_LP                              0xAD6
#घोषणा MC_PMG_CMD_MRS2                                 0xAD7
#घोषणा MC_SEQ_PMG_CMD_MRS2_LP                          0xAD8

#घोषणा	MCLK_PWRMGT_CNTL				0xAE8
#       define DLL_SPEED(x)				((x) << 0)
#       define DLL_SPEED_MASK				(0x1f << 0)
#       define DLL_READY                                (1 << 6)
#       define MC_INT_CNTL                              (1 << 7)
#       define MRDCK0_PDNB                              (1 << 8)
#       define MRDCK1_PDNB                              (1 << 9)
#       define MRDCK0_RESET                             (1 << 16)
#       define MRDCK1_RESET                             (1 << 17)
#       define DLL_READY_READ                           (1 << 24)
#घोषणा	DLL_CNTL					0xAE9
#       define MRDCK0_BYPASS                            (1 << 24)
#       define MRDCK1_BYPASS                            (1 << 25)

#घोषणा	MPLL_CNTL_MODE					0xAEC
#       define MPLL_MCLK_SEL                            (1 << 11)
#घोषणा	MPLL_FUNC_CNTL					0xAED
#घोषणा		BWCTRL(x)				((x) << 20)
#घोषणा		BWCTRL_MASK				(0xff << 20)
#घोषणा	MPLL_FUNC_CNTL_1				0xAEE
#घोषणा		VCO_MODE(x)				((x) << 0)
#घोषणा		VCO_MODE_MASK				(3 << 0)
#घोषणा		CLKFRAC(x)				((x) << 4)
#घोषणा		CLKFRAC_MASK				(0xfff << 4)
#घोषणा		CLKF(x)					((x) << 16)
#घोषणा		CLKF_MASK				(0xfff << 16)
#घोषणा	MPLL_FUNC_CNTL_2				0xAEF
#घोषणा	MPLL_AD_FUNC_CNTL				0xAF0
#घोषणा		YCLK_POST_DIV(x)			((x) << 0)
#घोषणा		YCLK_POST_DIV_MASK			(7 << 0)
#घोषणा	MPLL_DQ_FUNC_CNTL				0xAF1
#घोषणा		YCLK_SEL(x)				((x) << 4)
#घोषणा		YCLK_SEL_MASK				(1 << 4)

#घोषणा	MPLL_SS1					0xAF3
#घोषणा		CLKV(x)					((x) << 0)
#घोषणा		CLKV_MASK				(0x3ffffff << 0)
#घोषणा	MPLL_SS2					0xAF4
#घोषणा		CLKS(x)					((x) << 0)
#घोषणा		CLKS_MASK				(0xfff << 0)

#घोषणा	HDP_HOST_PATH_CNTL				0xB00
#घोषणा 	CLOCK_GATING_DIS			(1 << 23)
#घोषणा	HDP_NONSURFACE_BASE				0xB01
#घोषणा	HDP_NONSURFACE_INFO				0xB02
#घोषणा	HDP_NONSURFACE_SIZE				0xB03

#घोषणा HDP_DEBUG0  					0xBCC

#घोषणा HDP_ADDR_CONFIG  				0xBD2
#घोषणा HDP_MISC_CNTL					0xBD3
#घोषणा 	HDP_FLUSH_INVALIDATE_CACHE			(1 << 0)
#घोषणा HDP_MEM_POWER_LS				0xBD4
#घोषणा 	HDP_LS_ENABLE				(1 << 0)

#घोषणा ATC_MISC_CG           				0xCD4

#घोषणा IH_RB_CNTL                                        0xF80
#       define IH_RB_ENABLE                               (1 << 0)
#       define IH_IB_SIZE(x)                              ((x) << 1) /* log2 */
#       define IH_RB_FULL_DRAIN_ENABLE                    (1 << 6)
#       define IH_WPTR_WRITEBACK_ENABLE                   (1 << 8)
#       define IH_WPTR_WRITEBACK_TIMER(x)                 ((x) << 9) /* log2 */
#       define IH_WPTR_OVERFLOW_ENABLE                    (1 << 16)
#       define IH_WPTR_OVERFLOW_CLEAR                     (1 << 31)
#घोषणा IH_RB_BASE                                        0xF81
#घोषणा IH_RB_RPTR                                        0xF82
#घोषणा IH_RB_WPTR                                        0xF83
#       define RB_OVERFLOW                                (1 << 0)
#       define WPTR_OFFSET_MASK                           0x3fffc
#घोषणा IH_RB_WPTR_ADDR_HI                                0xF84
#घोषणा IH_RB_WPTR_ADDR_LO                                0xF85
#घोषणा IH_CNTL                                           0xF86
#       define ENABLE_INTR                                (1 << 0)
#       define IH_MC_SWAP(x)                              ((x) << 1)
#       define IH_MC_SWAP_NONE                            0
#       define IH_MC_SWAP_16BIT                           1
#       define IH_MC_SWAP_32BIT                           2
#       define IH_MC_SWAP_64BIT                           3
#       define RPTR_REARM                                 (1 << 4)
#       define MC_WRREQ_CREDIT(x)                         ((x) << 15)
#       define MC_WR_CLEAN_CNT(x)                         ((x) << 20)
#       define MC_VMID(x)                                 ((x) << 25)

#घोषणा	CONFIG_MEMSIZE					0x150A

#घोषणा INTERRUPT_CNTL                                    0x151A
#       define IH_DUMMY_RD_OVERRIDE                       (1 << 0)
#       define IH_DUMMY_RD_EN                             (1 << 1)
#       define IH_REQ_NONSNOOP_EN                         (1 << 3)
#       define GEN_IH_INT_EN                              (1 << 8)
#घोषणा INTERRUPT_CNTL2                                   0x151B

#घोषणा HDP_MEM_COHERENCY_FLUSH_CNTL			0x1520

#घोषणा	BIF_FB_EN						0x1524
#घोषणा		FB_READ_EN					(1 << 0)
#घोषणा		FB_WRITE_EN					(1 << 1)

#घोषणा HDP_REG_COHERENCY_FLUSH_CNTL			0x1528

/* DCE6 ELD audio पूर्णांकerface */
#घोषणा AZ_F0_CODEC_ENDPOINT_INDEX                       0x1780
#       define AZ_ENDPOINT_REG_INDEX(x)                  (((x) & 0xff) << 0)
#       define AZ_ENDPOINT_REG_WRITE_EN                  (1 << 8)
#घोषणा AZ_F0_CODEC_ENDPOINT_DATA                        0x1781

#घोषणा AZ_F0_CODEC_PIN_CONTROL_CHANNEL_SPEAKER          0x25
#घोषणा		SPEAKER_ALLOCATION(x)			(((x) & 0x7f) << 0)
#घोषणा		SPEAKER_ALLOCATION_MASK			(0x7f << 0)
#घोषणा		SPEAKER_ALLOCATION_SHIFT		0
#घोषणा		HDMI_CONNECTION				(1 << 16)
#घोषणा		DP_CONNECTION				(1 << 17)

#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR0        0x28 /* LPCM */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR1        0x29 /* AC3 */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR2        0x2A /* MPEG1 */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR3        0x2B /* MP3 */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR4        0x2C /* MPEG2 */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR5        0x2D /* AAC */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR6        0x2E /* DTS */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR7        0x2F /* ATRAC */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR8        0x30 /* one bit audio - leave at 0 (शेष) */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR9        0x31 /* Dolby Digital */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR10       0x32 /* DTS-HD */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR11       0x33 /* MAT-MLP */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR12       0x34 /* DTS */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_AUDIO_DESCRIPTOR13       0x35 /* WMA Pro */
#       define MAX_CHANNELS(x)                            (((x) & 0x7) << 0)
/* max channels minus one.  7 = 8 channels */
#       define SUPPORTED_FREQUENCIES(x)                   (((x) & 0xff) << 8)
#       define DESCRIPTOR_BYTE_2(x)                       (((x) & 0xff) << 16)
#       define SUPPORTED_FREQUENCIES_STEREO(x)            (((x) & 0xff) << 24) /* LPCM only */
/* SUPPORTED_FREQUENCIES, SUPPORTED_FREQUENCIES_STEREO
 * bit0 = 32 kHz
 * bit1 = 44.1 kHz
 * bit2 = 48 kHz
 * bit3 = 88.2 kHz
 * bit4 = 96 kHz
 * bit5 = 176.4 kHz
 * bit6 = 192 kHz
 */

#घोषणा AZ_F0_CODEC_PIN_CONTROL_RESPONSE_LIPSYNC         0x37
#       define VIDEO_LIPSYNC(x)                           (((x) & 0xff) << 0)
#       define AUDIO_LIPSYNC(x)                           (((x) & 0xff) << 8)
/* VIDEO_LIPSYNC, AUDIO_LIPSYNC
 * 0   = invalid
 * x   = legal delay value
 * 255 = sync not supported
 */
#घोषणा AZ_F0_CODEC_PIN_CONTROL_RESPONSE_HBR             0x38
#       define HBR_CAPABLE                                (1 << 0) /* enabled by शेष */

#घोषणा AZ_F0_CODEC_PIN_CONTROL_SINK_INFO0               0x3a
#       define MANUFACTURER_ID(x)                        (((x) & 0xffff) << 0)
#       define PRODUCT_ID(x)                             (((x) & 0xffff) << 16)
#घोषणा AZ_F0_CODEC_PIN_CONTROL_SINK_INFO1               0x3b
#       define SINK_DESCRIPTION_LEN(x)                   (((x) & 0xff) << 0)
#घोषणा AZ_F0_CODEC_PIN_CONTROL_SINK_INFO2               0x3c
#       define PORT_ID0(x)                               (((x) & 0xffffffff) << 0)
#घोषणा AZ_F0_CODEC_PIN_CONTROL_SINK_INFO3               0x3d
#       define PORT_ID1(x)                               (((x) & 0xffffffff) << 0)
#घोषणा AZ_F0_CODEC_PIN_CONTROL_SINK_INFO4               0x3e
#       define DESCRIPTION0(x)                           (((x) & 0xff) << 0)
#       define DESCRIPTION1(x)                           (((x) & 0xff) << 8)
#       define DESCRIPTION2(x)                           (((x) & 0xff) << 16)
#       define DESCRIPTION3(x)                           (((x) & 0xff) << 24)
#घोषणा AZ_F0_CODEC_PIN_CONTROL_SINK_INFO5               0x3f
#       define DESCRIPTION4(x)                           (((x) & 0xff) << 0)
#       define DESCRIPTION5(x)                           (((x) & 0xff) << 8)
#       define DESCRIPTION6(x)                           (((x) & 0xff) << 16)
#       define DESCRIPTION7(x)                           (((x) & 0xff) << 24)
#घोषणा AZ_F0_CODEC_PIN_CONTROL_SINK_INFO6               0x40
#       define DESCRIPTION8(x)                           (((x) & 0xff) << 0)
#       define DESCRIPTION9(x)                           (((x) & 0xff) << 8)
#       define DESCRIPTION10(x)                          (((x) & 0xff) << 16)
#       define DESCRIPTION11(x)                          (((x) & 0xff) << 24)
#घोषणा AZ_F0_CODEC_PIN_CONTROL_SINK_INFO7               0x41
#       define DESCRIPTION12(x)                          (((x) & 0xff) << 0)
#       define DESCRIPTION13(x)                          (((x) & 0xff) << 8)
#       define DESCRIPTION14(x)                          (((x) & 0xff) << 16)
#       define DESCRIPTION15(x)                          (((x) & 0xff) << 24)
#घोषणा AZ_F0_CODEC_PIN_CONTROL_SINK_INFO8               0x42
#       define DESCRIPTION16(x)                          (((x) & 0xff) << 0)
#       define DESCRIPTION17(x)                          (((x) & 0xff) << 8)

#घोषणा AZ_F0_CODEC_PIN_CONTROL_HOT_PLUG_CONTROL         0x54
#       define AUDIO_ENABLED                             (1 << 31)

#घोषणा AZ_F0_CODEC_PIN_CONTROL_RESPONSE_CONFIGURATION_DEFAULT  0x56
#घोषणा		PORT_CONNECTIVITY_MASK				(3 << 30)
#घोषणा		PORT_CONNECTIVITY_SHIFT				30

#घोषणा	DC_LB_MEMORY_SPLIT					0x1AC3
#घोषणा		DC_LB_MEMORY_CONFIG(x)				((x) << 20)

#घोषणा	PRIORITY_A_CNT						0x1AC6
#घोषणा		PRIORITY_MARK_MASK				0x7fff
#घोषणा		PRIORITY_OFF					(1 << 16)
#घोषणा		PRIORITY_ALWAYS_ON				(1 << 20)
#घोषणा	PRIORITY_B_CNT						0x1AC7

#घोषणा	DPG_PIPE_ARBITRATION_CONTROL3				0x1B32
#       define LATENCY_WATERMARK_MASK(x)			((x) << 16)
#घोषणा	DPG_PIPE_LATENCY_CONTROL				0x1B33
#       define LATENCY_LOW_WATERMARK(x)				((x) << 0)
#       define LATENCY_HIGH_WATERMARK(x)			((x) << 16)

/* 0x6bb8, 0x77b8, 0x103b8, 0x10fb8, 0x11bb8, 0x127b8 */
#घोषणा VLINE_STATUS                                    0x1AEE
#       define VLINE_OCCURRED                           (1 << 0)
#       define VLINE_ACK                                (1 << 4)
#       define VLINE_STAT                               (1 << 12)
#       define VLINE_INTERRUPT                          (1 << 16)
#       define VLINE_INTERRUPT_TYPE                     (1 << 17)
/* 0x6bbc, 0x77bc, 0x103bc, 0x10fbc, 0x11bbc, 0x127bc */
#घोषणा VBLANK_STATUS                                   0x1AEF
#       define VBLANK_OCCURRED                          (1 << 0)
#       define VBLANK_ACK                               (1 << 4)
#       define VBLANK_STAT                              (1 << 12)
#       define VBLANK_INTERRUPT                         (1 << 16)
#       define VBLANK_INTERRUPT_TYPE                    (1 << 17)

/* 0x6b40, 0x7740, 0x10340, 0x10f40, 0x11b40, 0x12740 */
#घोषणा INT_MASK                                        0x1AD0
#       define VBLANK_INT_MASK                          (1 << 0)
#       define VLINE_INT_MASK                           (1 << 4)

#घोषणा DISP_INTERRUPT_STATUS                           0x183D
#       define LB_D1_VLINE_INTERRUPT                    (1 << 2)
#       define LB_D1_VBLANK_INTERRUPT                   (1 << 3)
#       define DC_HPD1_INTERRUPT                        (1 << 17)
#       define DC_HPD1_RX_INTERRUPT                     (1 << 18)
#       define DACA_AUTODETECT_INTERRUPT                (1 << 22)
#       define DACB_AUTODETECT_INTERRUPT                (1 << 23)
#       define DC_I2C_SW_DONE_INTERRUPT                 (1 << 24)
#       define DC_I2C_HW_DONE_INTERRUPT                 (1 << 25)
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE                  0x183E
#       define LB_D2_VLINE_INTERRUPT                    (1 << 2)
#       define LB_D2_VBLANK_INTERRUPT                   (1 << 3)
#       define DC_HPD2_INTERRUPT                        (1 << 17)
#       define DC_HPD2_RX_INTERRUPT                     (1 << 18)
#       define DISP_TIMER_INTERRUPT                     (1 << 24)
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE2                 0x183F
#       define LB_D3_VLINE_INTERRUPT                    (1 << 2)
#       define LB_D3_VBLANK_INTERRUPT                   (1 << 3)
#       define DC_HPD3_INTERRUPT                        (1 << 17)
#       define DC_HPD3_RX_INTERRUPT                     (1 << 18)
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE3                 0x1840
#       define LB_D4_VLINE_INTERRUPT                    (1 << 2)
#       define LB_D4_VBLANK_INTERRUPT                   (1 << 3)
#       define DC_HPD4_INTERRUPT                        (1 << 17)
#       define DC_HPD4_RX_INTERRUPT                     (1 << 18)
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE4                 0x1853
#       define LB_D5_VLINE_INTERRUPT                    (1 << 2)
#       define LB_D5_VBLANK_INTERRUPT                   (1 << 3)
#       define DC_HPD5_INTERRUPT                        (1 << 17)
#       define DC_HPD5_RX_INTERRUPT                     (1 << 18)
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE5                 0x1854
#       define LB_D6_VLINE_INTERRUPT                    (1 << 2)
#       define LB_D6_VBLANK_INTERRUPT                   (1 << 3)
#       define DC_HPD6_INTERRUPT                        (1 << 17)
#       define DC_HPD6_RX_INTERRUPT                     (1 << 18)

/* 0x6858, 0x7458, 0x10058, 0x10c58, 0x11858, 0x12458 */
#घोषणा GRPH_INT_STATUS                                 0x1A16
#       define GRPH_PFLIP_INT_OCCURRED                  (1 << 0)
#       define GRPH_PFLIP_INT_CLEAR                     (1 << 8)
/* 0x685c, 0x745c, 0x1005c, 0x10c5c, 0x1185c, 0x1245c */
#घोषणा	GRPH_INT_CONTROL			        0x1A17
#       define GRPH_PFLIP_INT_MASK                      (1 << 0)
#       define GRPH_PFLIP_INT_TYPE                      (1 << 8)

#घोषणा	DAC_AUTODETECT_INT_CONTROL			0x19F2

#घोषणा DC_HPD1_INT_STATUS                              0x1807
#घोषणा DC_HPD2_INT_STATUS                              0x180A
#घोषणा DC_HPD3_INT_STATUS                              0x180D
#घोषणा DC_HPD4_INT_STATUS                              0x1810
#घोषणा DC_HPD5_INT_STATUS                              0x1813
#घोषणा DC_HPD6_INT_STATUS                              0x1816
#       define DC_HPDx_INT_STATUS                       (1 << 0)
#       define DC_HPDx_SENSE                            (1 << 1)
#       define DC_HPDx_RX_INT_STATUS                    (1 << 8)

#घोषणा DC_HPD1_INT_CONTROL                             0x1808
#घोषणा DC_HPD2_INT_CONTROL                             0x180B
#घोषणा DC_HPD3_INT_CONTROL                             0x180E
#घोषणा DC_HPD4_INT_CONTROL                             0x1811
#घोषणा DC_HPD5_INT_CONTROL                             0x1814
#घोषणा DC_HPD6_INT_CONTROL                             0x1817
#       define DC_HPDx_INT_ACK                          (1 << 0)
#       define DC_HPDx_INT_POLARITY                     (1 << 8)
#       define DC_HPDx_INT_EN                           (1 << 16)
#       define DC_HPDx_RX_INT_ACK                       (1 << 20)
#       define DC_HPDx_RX_INT_EN                        (1 << 24)

#घोषणा DC_HPD1_CONTROL                                   0x1809
#घोषणा DC_HPD2_CONTROL                                   0x180C
#घोषणा DC_HPD3_CONTROL                                   0x180F
#घोषणा DC_HPD4_CONTROL                                   0x1812
#घोषणा DC_HPD5_CONTROL                                   0x1815
#घोषणा DC_HPD6_CONTROL                                   0x1818
#       define DC_HPDx_CONNECTION_TIMER(x)                ((x) << 0)
#       define DC_HPDx_RX_INT_TIMER(x)                    ((x) << 16)
#       define DC_HPDx_EN                                 (1 << 28)

#घोषणा DPG_PIPE_STUTTER_CONTROL                          0x1B35
#       define STUTTER_ENABLE                             (1 << 0)

/* 0x6e98, 0x7a98, 0x10698, 0x11298, 0x11e98, 0x12a98 */
#घोषणा CRTC_STATUS_FRAME_COUNT                         0x1BA6

/* Audio घड़ीs */
#घोषणा DCCG_AUDIO_DTO_SOURCE                           0x05ac
#       define DCCG_AUDIO_DTO0_SOURCE_SEL(x) ((x) << 0) /* crtc0 - crtc5 */
#       define DCCG_AUDIO_DTO_SEL            (1 << 4)   /* 0=dto0 1=dto1 */

#घोषणा DCCG_AUDIO_DTO0_PHASE                           0x05b0
#घोषणा DCCG_AUDIO_DTO0_MODULE                          0x05b4
#घोषणा DCCG_AUDIO_DTO1_PHASE                           0x05c0
#घोषणा DCCG_AUDIO_DTO1_MODULE                          0x05c4

#घोषणा AFMT_AUDIO_SRC_CONTROL                          0x1c4f
#घोषणा		AFMT_AUDIO_SRC_SELECT(x)		(((x) & 7) << 0)
/* AFMT_AUDIO_SRC_SELECT
 * 0 = stream0
 * 1 = stream1
 * 2 = stream2
 * 3 = stream3
 * 4 = stream4
 * 5 = stream5
 */

#घोषणा	GRBM_CNTL					0x2000
#घोषणा		GRBM_READ_TIMEOUT(x)				((x) << 0)

#घोषणा	GRBM_STATUS2					0x2002
#घोषणा		RLC_RQ_PENDING 					(1 << 0)
#घोषणा		RLC_BUSY 					(1 << 8)
#घोषणा		TC_BUSY 					(1 << 9)

#घोषणा	GRBM_STATUS					0x2004
#घोषणा		CMDFIFO_AVAIL_MASK				0x0000000F
#घोषणा		RING2_RQ_PENDING				(1 << 4)
#घोषणा		SRBM_RQ_PENDING					(1 << 5)
#घोषणा		RING1_RQ_PENDING				(1 << 6)
#घोषणा		CF_RQ_PENDING					(1 << 7)
#घोषणा		PF_RQ_PENDING					(1 << 8)
#घोषणा		GDS_DMA_RQ_PENDING				(1 << 9)
#घोषणा		GRBM_EE_BUSY					(1 << 10)
#घोषणा		DB_CLEAN					(1 << 12)
#घोषणा		CB_CLEAN					(1 << 13)
#घोषणा		TA_BUSY 					(1 << 14)
#घोषणा		GDS_BUSY 					(1 << 15)
#घोषणा		VGT_BUSY					(1 << 17)
#घोषणा		IA_BUSY_NO_DMA					(1 << 18)
#घोषणा		IA_BUSY						(1 << 19)
#घोषणा		SX_BUSY 					(1 << 20)
#घोषणा		SPI_BUSY					(1 << 22)
#घोषणा		BCI_BUSY					(1 << 23)
#घोषणा		SC_BUSY 					(1 << 24)
#घोषणा		PA_BUSY 					(1 << 25)
#घोषणा		DB_BUSY 					(1 << 26)
#घोषणा		CP_COHERENCY_BUSY      				(1 << 28)
#घोषणा		CP_BUSY 					(1 << 29)
#घोषणा		CB_BUSY 					(1 << 30)
#घोषणा		GUI_ACTIVE					(1 << 31)
#घोषणा	GRBM_STATUS_SE0					0x2005
#घोषणा	GRBM_STATUS_SE1					0x2006
#घोषणा		SE_DB_CLEAN					(1 << 1)
#घोषणा		SE_CB_CLEAN					(1 << 2)
#घोषणा		SE_BCI_BUSY					(1 << 22)
#घोषणा		SE_VGT_BUSY					(1 << 23)
#घोषणा		SE_PA_BUSY					(1 << 24)
#घोषणा		SE_TA_BUSY					(1 << 25)
#घोषणा		SE_SX_BUSY					(1 << 26)
#घोषणा		SE_SPI_BUSY					(1 << 27)
#घोषणा		SE_SC_BUSY					(1 << 29)
#घोषणा		SE_DB_BUSY					(1 << 30)
#घोषणा		SE_CB_BUSY					(1 << 31)

#घोषणा	GRBM_SOFT_RESET					0x2008
#घोषणा		SOFT_RESET_CP					(1 << 0)
#घोषणा		SOFT_RESET_CB					(1 << 1)
#घोषणा		SOFT_RESET_RLC					(1 << 2)
#घोषणा		SOFT_RESET_DB					(1 << 3)
#घोषणा		SOFT_RESET_GDS					(1 << 4)
#घोषणा		SOFT_RESET_PA					(1 << 5)
#घोषणा		SOFT_RESET_SC					(1 << 6)
#घोषणा		SOFT_RESET_BCI					(1 << 7)
#घोषणा		SOFT_RESET_SPI					(1 << 8)
#घोषणा		SOFT_RESET_SX					(1 << 10)
#घोषणा		SOFT_RESET_TC					(1 << 11)
#घोषणा		SOFT_RESET_TA					(1 << 12)
#घोषणा		SOFT_RESET_VGT					(1 << 14)
#घोषणा		SOFT_RESET_IA					(1 << 15)

#घोषणा GRBM_GFX_INDEX          			0x200B
#घोषणा		INSTANCE_INDEX(x)			((x) << 0)
#घोषणा		SH_INDEX(x)     			((x) << 8)
#घोषणा		SE_INDEX(x)     			((x) << 16)
#घोषणा		SH_BROADCAST_WRITES      		(1 << 29)
#घोषणा		INSTANCE_BROADCAST_WRITES      		(1 << 30)
#घोषणा		SE_BROADCAST_WRITES      		(1 << 31)

#घोषणा GRBM_INT_CNTL                                   0x2018
#       define RDERR_INT_ENABLE                         (1 << 0)
#       define GUI_IDLE_INT_ENABLE                      (1 << 19)

#घोषणा	CP_STRMOUT_CNTL					0x213F
#घोषणा	SCRATCH_REG0					0x2140
#घोषणा	SCRATCH_REG1					0x2141
#घोषणा	SCRATCH_REG2					0x2142
#घोषणा	SCRATCH_REG3					0x2143
#घोषणा	SCRATCH_REG4					0x2144
#घोषणा	SCRATCH_REG5					0x2145
#घोषणा	SCRATCH_REG6					0x2146
#घोषणा	SCRATCH_REG7					0x2147

#घोषणा	SCRATCH_UMSK					0x2150
#घोषणा	SCRATCH_ADDR					0x2151

#घोषणा	CP_SEM_WAIT_TIMER				0x216F

#घोषणा	CP_SEM_INCOMPLETE_TIMER_CNTL			0x2172

#घोषणा CP_ME_CNTL					0x21B6
#घोषणा		CP_CE_HALT					(1 << 24)
#घोषणा		CP_PFP_HALT					(1 << 26)
#घोषणा		CP_ME_HALT					(1 << 28)

#घोषणा	CP_COHER_CNTL2					0x217A

#घोषणा	CP_RB2_RPTR					0x21BE
#घोषणा	CP_RB1_RPTR					0x21BF
#घोषणा	CP_RB0_RPTR					0x21C0
#घोषणा	CP_RB_WPTR_DELAY				0x21C1

#घोषणा	CP_QUEUE_THRESHOLDS				0x21D8
#घोषणा		ROQ_IB1_START(x)				((x) << 0)
#घोषणा		ROQ_IB2_START(x)				((x) << 8)
#घोषणा CP_MEQ_THRESHOLDS				0x21D9
#घोषणा		MEQ1_START(x)				((x) << 0)
#घोषणा		MEQ2_START(x)				((x) << 8)

#घोषणा	CP_PERFMON_CNTL					0x21FF

#घोषणा	VGT_VTX_VECT_EJECT_REG				0x222C

#घोषणा	VGT_CACHE_INVALIDATION				0x2231
#घोषणा		CACHE_INVALIDATION(x)				((x) << 0)
#घोषणा			VC_ONLY						0
#घोषणा			TC_ONLY						1
#घोषणा			VC_AND_TC					2
#घोषणा		AUTO_INVLD_EN(x)				((x) << 6)
#घोषणा			NO_AUTO						0
#घोषणा			ES_AUTO						1
#घोषणा			GS_AUTO						2
#घोषणा			ES_AND_GS_AUTO					3
#घोषणा	VGT_ESGS_RING_SIZE				0x2232
#घोषणा	VGT_GSVS_RING_SIZE				0x2233

#घोषणा	VGT_GS_VERTEX_REUSE				0x2235

#घोषणा	VGT_PRIMITIVE_TYPE				0x2256
#घोषणा	VGT_INDEX_TYPE					0x2257

#घोषणा	VGT_NUM_INDICES					0x225C
#घोषणा	VGT_NUM_INSTANCES				0x225D

#घोषणा	VGT_TF_RING_SIZE				0x2262

#घोषणा	VGT_HS_OFFCHIP_PARAM				0x226C

#घोषणा	VGT_TF_MEMORY_BASE				0x226E

#घोषणा CC_GC_SHADER_ARRAY_CONFIG			0x226F
#घोषणा		INACTIVE_CUS_MASK			0xFFFF0000
#घोषणा		INACTIVE_CUS_SHIFT			16
#घोषणा GC_USER_SHADER_ARRAY_CONFIG			0x2270

#घोषणा	PA_CL_ENHANCE					0x2285
#घोषणा		CLIP_VTX_REORDER_ENA				(1 << 0)
#घोषणा		NUM_CLIP_SEQ(x)					((x) << 1)

#घोषणा	PA_SU_LINE_STIPPLE_VALUE			0x2298

#घोषणा	PA_SC_LINE_STIPPLE_STATE			0x22C4

#घोषणा	PA_SC_FORCE_EOV_MAX_CNTS			0x22C9
#घोषणा		FORCE_EOV_MAX_CLK_CNT(x)			((x) << 0)
#घोषणा		FORCE_EOV_MAX_REZ_CNT(x)			((x) << 16)

#घोषणा	PA_SC_FIFO_SIZE					0x22F3
#घोषणा		SC_FRONTEND_PRIM_FIFO_SIZE(x)			((x) << 0)
#घोषणा		SC_BACKEND_PRIM_FIFO_SIZE(x)			((x) << 6)
#घोषणा		SC_HIZ_TILE_FIFO_SIZE(x)			((x) << 15)
#घोषणा		SC_EARLYZ_TILE_FIFO_SIZE(x)			((x) << 23)

#घोषणा	PA_SC_ENHANCE					0x22FC

#घोषणा	SQ_CONFIG					0x2300

#घोषणा	SQC_CACHES					0x2302

#घोषणा SQ_POWER_THROTTLE                               0x2396
#घोषणा		MIN_POWER(x)				((x) << 0)
#घोषणा		MIN_POWER_MASK				(0x3fff << 0)
#घोषणा		MIN_POWER_SHIFT				0
#घोषणा		MAX_POWER(x)				((x) << 16)
#घोषणा		MAX_POWER_MASK				(0x3fff << 16)
#घोषणा		MAX_POWER_SHIFT				0
#घोषणा SQ_POWER_THROTTLE2                              0x2397
#घोषणा		MAX_POWER_DELTA(x)			((x) << 0)
#घोषणा		MAX_POWER_DELTA_MASK			(0x3fff << 0)
#घोषणा		MAX_POWER_DELTA_SHIFT			0
#घोषणा		STI_SIZE(x)				((x) << 16)
#घोषणा		STI_SIZE_MASK				(0x3ff << 16)
#घोषणा		STI_SIZE_SHIFT				16
#घोषणा		LTI_RATIO(x)				((x) << 27)
#घोषणा		LTI_RATIO_MASK				(0xf << 27)
#घोषणा		LTI_RATIO_SHIFT				27

#घोषणा	SX_DEBUG_1					0x2418

#घोषणा	SPI_STATIC_THREAD_MGMT_1			0x2438
#घोषणा	SPI_STATIC_THREAD_MGMT_2			0x2439
#घोषणा	SPI_STATIC_THREAD_MGMT_3			0x243A
#घोषणा	SPI_PS_MAX_WAVE_ID				0x243B

#घोषणा	SPI_CONFIG_CNTL					0x2440

#घोषणा	SPI_CONFIG_CNTL_1				0x244F
#घोषणा		VTX_DONE_DELAY(x)				((x) << 0)
#घोषणा		INTERP_ONE_PRIM_PER_ROW				(1 << 4)

#घोषणा	CGTS_TCC_DISABLE				0x2452
#घोषणा	CGTS_USER_TCC_DISABLE				0x2453
#घोषणा		TCC_DISABLE_MASK				0xFFFF0000
#घोषणा		TCC_DISABLE_SHIFT				16
#घोषणा	CGTS_SM_CTRL_REG				0x2454
#घोषणा		OVERRIDE				(1 << 21)
#घोषणा		LS_OVERRIDE				(1 << 22)

#घोषणा	SPI_LB_CU_MASK					0x24D5

#घोषणा	TA_CNTL_AUX					0x2542

#घोषणा CC_RB_BACKEND_DISABLE				0x263D
#घोषणा		BACKEND_DISABLE(x)     			((x) << 16)
#घोषणा GB_ADDR_CONFIG  				0x263E
#घोषणा		NUM_PIPES(x)				((x) << 0)
#घोषणा		NUM_PIPES_MASK				0x00000007
#घोषणा		NUM_PIPES_SHIFT				0
#घोषणा		PIPE_INTERLEAVE_SIZE(x)			((x) << 4)
#घोषणा		PIPE_INTERLEAVE_SIZE_MASK		0x00000070
#घोषणा		PIPE_INTERLEAVE_SIZE_SHIFT		4
#घोषणा		NUM_SHADER_ENGINES(x)			((x) << 12)
#घोषणा		NUM_SHADER_ENGINES_MASK			0x00003000
#घोषणा		NUM_SHADER_ENGINES_SHIFT		12
#घोषणा		SHADER_ENGINE_TILE_SIZE(x)     		((x) << 16)
#घोषणा		SHADER_ENGINE_TILE_SIZE_MASK		0x00070000
#घोषणा		SHADER_ENGINE_TILE_SIZE_SHIFT		16
#घोषणा		NUM_GPUS(x)     			((x) << 20)
#घोषणा		NUM_GPUS_MASK				0x00700000
#घोषणा		NUM_GPUS_SHIFT				20
#घोषणा		MULTI_GPU_TILE_SIZE(x)     		((x) << 24)
#घोषणा		MULTI_GPU_TILE_SIZE_MASK		0x03000000
#घोषणा		MULTI_GPU_TILE_SIZE_SHIFT		24
#घोषणा		ROW_SIZE(x)             		((x) << 28)
#घोषणा		ROW_SIZE_MASK				0x30000000
#घोषणा		ROW_SIZE_SHIFT				28

#घोषणा	GB_TILE_MODE0					0x2644
#       define MICRO_TILE_MODE(x)				((x) << 0)
#              define	ADDR_SURF_DISPLAY_MICRO_TILING		0
#              define	ADDR_SURF_THIN_MICRO_TILING		1
#              define	ADDR_SURF_DEPTH_MICRO_TILING		2
#       define ARRAY_MODE(x)					((x) << 2)
#              define	ARRAY_LINEAR_GENERAL			0
#              define	ARRAY_LINEAR_ALIGNED			1
#              define	ARRAY_1D_TILED_THIN1			2
#              define	ARRAY_2D_TILED_THIN1			4
#       define PIPE_CONFIG(x)					((x) << 6)
#              define	ADDR_SURF_P2				0
#              define	ADDR_SURF_P4_8x16			4
#              define	ADDR_SURF_P4_16x16			5
#              define	ADDR_SURF_P4_16x32			6
#              define	ADDR_SURF_P4_32x32			7
#              define	ADDR_SURF_P8_16x16_8x16			8
#              define	ADDR_SURF_P8_16x32_8x16			9
#              define	ADDR_SURF_P8_32x32_8x16			10
#              define	ADDR_SURF_P8_16x32_16x16		11
#              define	ADDR_SURF_P8_32x32_16x16		12
#              define	ADDR_SURF_P8_32x32_16x32		13
#              define	ADDR_SURF_P8_32x64_32x32		14
#       define TILE_SPLIT(x)					((x) << 11)
#              define	ADDR_SURF_TILE_SPLIT_64B		0
#              define	ADDR_SURF_TILE_SPLIT_128B		1
#              define	ADDR_SURF_TILE_SPLIT_256B		2
#              define	ADDR_SURF_TILE_SPLIT_512B		3
#              define	ADDR_SURF_TILE_SPLIT_1KB		4
#              define	ADDR_SURF_TILE_SPLIT_2KB		5
#              define	ADDR_SURF_TILE_SPLIT_4KB		6
#       define BANK_WIDTH(x)					((x) << 14)
#              define	ADDR_SURF_BANK_WIDTH_1			0
#              define	ADDR_SURF_BANK_WIDTH_2			1
#              define	ADDR_SURF_BANK_WIDTH_4			2
#              define	ADDR_SURF_BANK_WIDTH_8			3
#       define BANK_HEIGHT(x)					((x) << 16)
#              define	ADDR_SURF_BANK_HEIGHT_1			0
#              define	ADDR_SURF_BANK_HEIGHT_2			1
#              define	ADDR_SURF_BANK_HEIGHT_4			2
#              define	ADDR_SURF_BANK_HEIGHT_8			3
#       define MACRO_TILE_ASPECT(x)				((x) << 18)
#              define	ADDR_SURF_MACRO_ASPECT_1		0
#              define	ADDR_SURF_MACRO_ASPECT_2		1
#              define	ADDR_SURF_MACRO_ASPECT_4		2
#              define	ADDR_SURF_MACRO_ASPECT_8		3
#       define NUM_BANKS(x)					((x) << 20)
#              define	ADDR_SURF_2_BANK			0
#              define	ADDR_SURF_4_BANK			1
#              define	ADDR_SURF_8_BANK			2
#              define	ADDR_SURF_16_BANK			3
#घोषणा	GB_TILE_MODE1					0x2645
#घोषणा	GB_TILE_MODE2					0x2646
#घोषणा	GB_TILE_MODE3					0x2647
#घोषणा	GB_TILE_MODE4					0x2648
#घोषणा	GB_TILE_MODE5					0x2649
#घोषणा	GB_TILE_MODE6					0x264a
#घोषणा	GB_TILE_MODE7					0x264b
#घोषणा	GB_TILE_MODE8					0x264c
#घोषणा	GB_TILE_MODE9					0x264d
#घोषणा	GB_TILE_MODE10					0x264e
#घोषणा	GB_TILE_MODE11					0x264f
#घोषणा	GB_TILE_MODE12					0x2650
#घोषणा	GB_TILE_MODE13					0x2651
#घोषणा	GB_TILE_MODE14					0x2652
#घोषणा	GB_TILE_MODE15					0x2653
#घोषणा	GB_TILE_MODE16					0x2654
#घोषणा	GB_TILE_MODE17					0x2655
#घोषणा	GB_TILE_MODE18					0x2656
#घोषणा	GB_TILE_MODE19					0x2657
#घोषणा	GB_TILE_MODE20					0x2658
#घोषणा	GB_TILE_MODE21					0x2659
#घोषणा	GB_TILE_MODE22					0x265a
#घोषणा	GB_TILE_MODE23					0x265b
#घोषणा	GB_TILE_MODE24					0x265c
#घोषणा	GB_TILE_MODE25					0x265d
#घोषणा	GB_TILE_MODE26					0x265e
#घोषणा	GB_TILE_MODE27					0x265f
#घोषणा	GB_TILE_MODE28					0x2660
#घोषणा	GB_TILE_MODE29					0x2661
#घोषणा	GB_TILE_MODE30					0x2662
#घोषणा	GB_TILE_MODE31					0x2663

#घोषणा	CB_PERFCOUNTER0_SELECT0				0x2688
#घोषणा	CB_PERFCOUNTER0_SELECT1				0x2689
#घोषणा	CB_PERFCOUNTER1_SELECT0				0x268A
#घोषणा	CB_PERFCOUNTER1_SELECT1				0x268B
#घोषणा	CB_PERFCOUNTER2_SELECT0				0x268C
#घोषणा	CB_PERFCOUNTER2_SELECT1				0x268D
#घोषणा	CB_PERFCOUNTER3_SELECT0				0x268E
#घोषणा	CB_PERFCOUNTER3_SELECT1				0x268F

#घोषणा	CB_CGTT_SCLK_CTRL				0x2698

#घोषणा	GC_USER_RB_BACKEND_DISABLE			0x26DF
#घोषणा		BACKEND_DISABLE_MASK			0x00FF0000
#घोषणा		BACKEND_DISABLE_SHIFT			16

#घोषणा	TCP_CHAN_STEER_LO				0x2B03
#घोषणा	TCP_CHAN_STEER_HI				0x2B94

#घोषणा	CP_RB0_BASE					0x3040
#घोषणा	CP_RB0_CNTL					0x3041
#घोषणा		RB_BUFSZ(x)					((x) << 0)
#घोषणा		RB_BLKSZ(x)					((x) << 8)
#घोषणा		BUF_SWAP_32BIT					(2 << 16)
#घोषणा		RB_NO_UPDATE					(1 << 27)
#घोषणा		RB_RPTR_WR_ENA					(1 << 31)

#घोषणा	CP_RB0_RPTR_ADDR				0x3043
#घोषणा	CP_RB0_RPTR_ADDR_HI				0x3044
#घोषणा	CP_RB0_WPTR					0x3045

#घोषणा	CP_PFP_UCODE_ADDR				0x3054
#घोषणा	CP_PFP_UCODE_DATA				0x3055
#घोषणा	CP_ME_RAM_RADDR					0x3056
#घोषणा	CP_ME_RAM_WADDR					0x3057
#घोषणा	CP_ME_RAM_DATA					0x3058

#घोषणा	CP_CE_UCODE_ADDR				0x305A
#घोषणा	CP_CE_UCODE_DATA				0x305B

#घोषणा	CP_RB1_BASE					0x3060
#घोषणा	CP_RB1_CNTL					0x3061
#घोषणा	CP_RB1_RPTR_ADDR				0x3062
#घोषणा	CP_RB1_RPTR_ADDR_HI				0x3063
#घोषणा	CP_RB1_WPTR					0x3064
#घोषणा	CP_RB2_BASE					0x3065
#घोषणा	CP_RB2_CNTL					0x3066
#घोषणा	CP_RB2_RPTR_ADDR				0x3067
#घोषणा	CP_RB2_RPTR_ADDR_HI				0x3068
#घोषणा	CP_RB2_WPTR					0x3069
#घोषणा CP_INT_CNTL_RING0                               0x306A
#घोषणा CP_INT_CNTL_RING1                               0x306B
#घोषणा CP_INT_CNTL_RING2                               0x306C
#       define CNTX_BUSY_INT_ENABLE                     (1 << 19)
#       define CNTX_EMPTY_INT_ENABLE                    (1 << 20)
#       define WAIT_MEM_SEM_INT_ENABLE                  (1 << 21)
#       define TIME_STAMP_INT_ENABLE                    (1 << 26)
#       define CP_RINGID2_INT_ENABLE                    (1 << 29)
#       define CP_RINGID1_INT_ENABLE                    (1 << 30)
#       define CP_RINGID0_INT_ENABLE                    (1 << 31)
#घोषणा CP_INT_STATUS_RING0                             0x306D
#घोषणा CP_INT_STATUS_RING1                             0x306E
#घोषणा CP_INT_STATUS_RING2                             0x306F
#       define WAIT_MEM_SEM_INT_STAT                    (1 << 21)
#       define TIME_STAMP_INT_STAT                      (1 << 26)
#       define CP_RINGID2_INT_STAT                      (1 << 29)
#       define CP_RINGID1_INT_STAT                      (1 << 30)
#       define CP_RINGID0_INT_STAT                      (1 << 31)

#घोषणा	CP_MEM_SLP_CNTL					0x3079
#       define CP_MEM_LS_EN                             (1 << 0)

#घोषणा	CP_DEBUG					0x307F

#घोषणा RLC_CNTL                                          0x30C0
#       define RLC_ENABLE                                 (1 << 0)
#घोषणा RLC_RL_BASE                                       0x30C1
#घोषणा RLC_RL_SIZE                                       0x30C2
#घोषणा RLC_LB_CNTL                                       0x30C3
#       define LOAD_BALANCE_ENABLE                        (1 << 0)
#घोषणा RLC_SAVE_AND_RESTORE_BASE                         0x30C4
#घोषणा RLC_LB_CNTR_MAX                                   0x30C5
#घोषणा RLC_LB_CNTR_INIT                                  0x30C6

#घोषणा RLC_CLEAR_STATE_RESTORE_BASE                      0x30C8

#घोषणा RLC_UCODE_ADDR                                    0x30CB
#घोषणा RLC_UCODE_DATA                                    0x30CC

#घोषणा RLC_GPU_CLOCK_COUNT_LSB                           0x30CE
#घोषणा RLC_GPU_CLOCK_COUNT_MSB                           0x30CF
#घोषणा RLC_CAPTURE_GPU_CLOCK_COUNT                       0x30D0
#घोषणा RLC_MC_CNTL                                       0x30D1
#घोषणा RLC_UCODE_CNTL                                    0x30D2
#घोषणा RLC_STAT                                          0x30D3
#       define RLC_BUSY_STATUS                            (1 << 0)
#       define GFX_POWER_STATUS                           (1 << 1)
#       define GFX_CLOCK_STATUS                           (1 << 2)
#       define GFX_LS_STATUS                              (1 << 3)

#घोषणा	RLC_PG_CNTL					0x30D7
#	define GFX_PG_ENABLE				(1 << 0)
#	define GFX_PG_SRC				(1 << 1)

#घोषणा	RLC_CGTT_MGCG_OVERRIDE				0x3100
#घोषणा	RLC_CGCG_CGLS_CTRL				0x3101
#	define CGCG_EN					(1 << 0)
#	define CGLS_EN					(1 << 1)

#घोषणा	RLC_TTOP_D					0x3105
#	define RLC_PUD(x)				((x) << 0)
#	define RLC_PUD_MASK				(0xff << 0)
#	define RLC_PDD(x)				((x) << 8)
#	define RLC_PDD_MASK				(0xff << 8)
#	define RLC_TTPD(x)				((x) << 16)
#	define RLC_TTPD_MASK				(0xff << 16)
#	define RLC_MSD(x)				((x) << 24)
#	define RLC_MSD_MASK				(0xff << 24)

#घोषणा RLC_LB_INIT_CU_MASK                               0x3107

#घोषणा	RLC_PG_AO_CU_MASK				0x310B
#घोषणा	RLC_MAX_PG_CU					0x310C
#	define MAX_PU_CU(x)				((x) << 0)
#	define MAX_PU_CU_MASK				(0xff << 0)
#घोषणा	RLC_AUTO_PG_CTRL				0x310C
#	define AUTO_PG_EN				(1 << 0)
#	define GRBM_REG_SGIT(x)				((x) << 3)
#	define GRBM_REG_SGIT_MASK			(0xffff << 3)
#	define PG_AFTER_GRBM_REG_ST(x)			((x) << 19)
#	define PG_AFTER_GRBM_REG_ST_MASK		(0x1fff << 19)

#घोषणा RLC_SERDES_WR_MASTER_MASK_0                       0x3115
#घोषणा RLC_SERDES_WR_MASTER_MASK_1                       0x3116
#घोषणा RLC_SERDES_WR_CTRL                                0x3117

#घोषणा RLC_SERDES_MASTER_BUSY_0                          0x3119
#घोषणा RLC_SERDES_MASTER_BUSY_1                          0x311A

#घोषणा RLC_GCPM_GENERAL_3                                0x311E

#घोषणा	DB_RENDER_CONTROL				0xA000

#घोषणा DB_DEPTH_INFO                                   0xA00F

#घोषणा PA_SC_RASTER_CONFIG                             0xA0D4
#	define RB_MAP_PKR0(x)				((x) << 0)
#	define RB_MAP_PKR0_MASK				(0x3 << 0)
#	define RB_MAP_PKR1(x)				((x) << 2)
#	define RB_MAP_PKR1_MASK				(0x3 << 2)
#       define RASTER_CONFIG_RB_MAP_0                   0
#       define RASTER_CONFIG_RB_MAP_1                   1
#       define RASTER_CONFIG_RB_MAP_2                   2
#       define RASTER_CONFIG_RB_MAP_3                   3
#	define RB_XSEL2(x)				((x) << 4)
#	define RB_XSEL2_MASK				(0x3 << 4)
#	define RB_XSEL					(1 << 6)
#	define RB_YSEL					(1 << 7)
#	define PKR_MAP(x)				((x) << 8)
#	define PKR_MAP_MASK				(0x3 << 8)
#       define RASTER_CONFIG_PKR_MAP_0			0
#       define RASTER_CONFIG_PKR_MAP_1			1
#       define RASTER_CONFIG_PKR_MAP_2			2
#       define RASTER_CONFIG_PKR_MAP_3			3
#	define PKR_XSEL(x)				((x) << 10)
#	define PKR_XSEL_MASK				(0x3 << 10)
#	define PKR_YSEL(x)				((x) << 12)
#	define PKR_YSEL_MASK				(0x3 << 12)
#	define SC_MAP(x)				((x) << 16)
#	define SC_MAP_MASK				(0x3 << 16)
#	define SC_XSEL(x)				((x) << 18)
#	define SC_XSEL_MASK				(0x3 << 18)
#	define SC_YSEL(x)				((x) << 20)
#	define SC_YSEL_MASK				(0x3 << 20)
#	define SE_MAP(x)				((x) << 24)
#	define SE_MAP_MASK				(0x3 << 24)
#       define RASTER_CONFIG_SE_MAP_0			0
#       define RASTER_CONFIG_SE_MAP_1			1
#       define RASTER_CONFIG_SE_MAP_2			2
#       define RASTER_CONFIG_SE_MAP_3			3
#	define SE_XSEL(x)				((x) << 26)
#	define SE_XSEL_MASK				(0x3 << 26)
#	define SE_YSEL(x)				((x) << 28)
#	define SE_YSEL_MASK				(0x3 << 28)


#घोषणा VGT_EVENT_INITIATOR                             0xA2A4
#       define SAMPLE_STREAMOUTSTATS1                   (1 << 0)
#       define SAMPLE_STREAMOUTSTATS2                   (2 << 0)
#       define SAMPLE_STREAMOUTSTATS3                   (3 << 0)
#       define CACHE_FLUSH_TS                           (4 << 0)
#       define CACHE_FLUSH                              (6 << 0)
#       define CS_PARTIAL_FLUSH                         (7 << 0)
#       define VGT_STREAMOUT_RESET                      (10 << 0)
#       define END_OF_PIPE_INCR_DE                      (11 << 0)
#       define END_OF_PIPE_IB_END                       (12 << 0)
#       define RST_PIX_CNT                              (13 << 0)
#       define VS_PARTIAL_FLUSH                         (15 << 0)
#       define PS_PARTIAL_FLUSH                         (16 << 0)
#       define CACHE_FLUSH_AND_INV_TS_EVENT             (20 << 0)
#       define ZPASS_DONE                               (21 << 0)
#       define CACHE_FLUSH_AND_INV_EVENT                (22 << 0)
#       define PERFCOUNTER_START                        (23 << 0)
#       define PERFCOUNTER_STOP                         (24 << 0)
#       define PIPELINESTAT_START                       (25 << 0)
#       define PIPELINESTAT_STOP                        (26 << 0)
#       define PERFCOUNTER_SAMPLE                       (27 << 0)
#       define SAMPLE_PIPELINESTAT                      (30 << 0)
#       define SAMPLE_STREAMOUTSTATS                    (32 << 0)
#       define RESET_VTX_CNT                            (33 << 0)
#       define VGT_FLUSH                                (36 << 0)
#       define BOTTOM_OF_PIPE_TS                        (40 << 0)
#       define DB_CACHE_FLUSH_AND_INV                   (42 << 0)
#       define FLUSH_AND_INV_DB_DATA_TS                 (43 << 0)
#       define FLUSH_AND_INV_DB_META                    (44 << 0)
#       define FLUSH_AND_INV_CB_DATA_TS                 (45 << 0)
#       define FLUSH_AND_INV_CB_META                    (46 << 0)
#       define CS_DONE                                  (47 << 0)
#       define PS_DONE                                  (48 << 0)
#       define FLUSH_AND_INV_CB_PIXEL_DATA              (49 << 0)
#       define THREAD_TRACE_START                       (51 << 0)
#       define THREAD_TRACE_STOP                        (52 << 0)
#       define THREAD_TRACE_FLUSH                       (54 << 0)
#       define THREAD_TRACE_FINISH                      (55 << 0)

/* PIF PHY0 रेजिस्टरs idx/data 0x8/0xc */
#घोषणा PB0_PIF_CNTL                                      0x10
#       define LS2_EXIT_TIME(x)                           ((x) << 17)
#       define LS2_EXIT_TIME_MASK                         (0x7 << 17)
#       define LS2_EXIT_TIME_SHIFT                        17
#घोषणा PB0_PIF_PAIRING                                   0x11
#       define MULTI_PIF                                  (1 << 25)
#घोषणा PB0_PIF_PWRDOWN_0                                 0x12
#       define PLL_POWER_STATE_IN_TXS2_0(x)               ((x) << 7)
#       define PLL_POWER_STATE_IN_TXS2_0_MASK             (0x7 << 7)
#       define PLL_POWER_STATE_IN_TXS2_0_SHIFT            7
#       define PLL_POWER_STATE_IN_OFF_0(x)                ((x) << 10)
#       define PLL_POWER_STATE_IN_OFF_0_MASK              (0x7 << 10)
#       define PLL_POWER_STATE_IN_OFF_0_SHIFT             10
#       define PLL_RAMP_UP_TIME_0(x)                      ((x) << 24)
#       define PLL_RAMP_UP_TIME_0_MASK                    (0x7 << 24)
#       define PLL_RAMP_UP_TIME_0_SHIFT                   24
#घोषणा PB0_PIF_PWRDOWN_1                                 0x13
#       define PLL_POWER_STATE_IN_TXS2_1(x)               ((x) << 7)
#       define PLL_POWER_STATE_IN_TXS2_1_MASK             (0x7 << 7)
#       define PLL_POWER_STATE_IN_TXS2_1_SHIFT            7
#       define PLL_POWER_STATE_IN_OFF_1(x)                ((x) << 10)
#       define PLL_POWER_STATE_IN_OFF_1_MASK              (0x7 << 10)
#       define PLL_POWER_STATE_IN_OFF_1_SHIFT             10
#       define PLL_RAMP_UP_TIME_1(x)                      ((x) << 24)
#       define PLL_RAMP_UP_TIME_1_MASK                    (0x7 << 24)
#       define PLL_RAMP_UP_TIME_1_SHIFT                   24

#घोषणा PB0_PIF_PWRDOWN_2                                 0x17
#       define PLL_POWER_STATE_IN_TXS2_2(x)               ((x) << 7)
#       define PLL_POWER_STATE_IN_TXS2_2_MASK             (0x7 << 7)
#       define PLL_POWER_STATE_IN_TXS2_2_SHIFT            7
#       define PLL_POWER_STATE_IN_OFF_2(x)                ((x) << 10)
#       define PLL_POWER_STATE_IN_OFF_2_MASK              (0x7 << 10)
#       define PLL_POWER_STATE_IN_OFF_2_SHIFT             10
#       define PLL_RAMP_UP_TIME_2(x)                      ((x) << 24)
#       define PLL_RAMP_UP_TIME_2_MASK                    (0x7 << 24)
#       define PLL_RAMP_UP_TIME_2_SHIFT                   24
#घोषणा PB0_PIF_PWRDOWN_3                                 0x18
#       define PLL_POWER_STATE_IN_TXS2_3(x)               ((x) << 7)
#       define PLL_POWER_STATE_IN_TXS2_3_MASK             (0x7 << 7)
#       define PLL_POWER_STATE_IN_TXS2_3_SHIFT            7
#       define PLL_POWER_STATE_IN_OFF_3(x)                ((x) << 10)
#       define PLL_POWER_STATE_IN_OFF_3_MASK              (0x7 << 10)
#       define PLL_POWER_STATE_IN_OFF_3_SHIFT             10
#       define PLL_RAMP_UP_TIME_3(x)                      ((x) << 24)
#       define PLL_RAMP_UP_TIME_3_MASK                    (0x7 << 24)
#       define PLL_RAMP_UP_TIME_3_SHIFT                   24
/* PIF PHY1 रेजिस्टरs idx/data 0x10/0x14 */
#घोषणा PB1_PIF_CNTL                                      0x10
#घोषणा PB1_PIF_PAIRING                                   0x11
#घोषणा PB1_PIF_PWRDOWN_0                                 0x12
#घोषणा PB1_PIF_PWRDOWN_1                                 0x13

#घोषणा PB1_PIF_PWRDOWN_2                                 0x17
#घोषणा PB1_PIF_PWRDOWN_3                                 0x18
/* PCIE रेजिस्टरs idx/data 0x30/0x34 */
#घोषणा PCIE_CNTL2                                        0x1c /* PCIE */
#       define SLV_MEM_LS_EN                              (1 << 16)
#       define SLV_MEM_AGGRESSIVE_LS_EN                   (1 << 17)
#       define MST_MEM_LS_EN                              (1 << 18)
#       define REPLAY_MEM_LS_EN                           (1 << 19)
#घोषणा PCIE_LC_STATUS1                                   0x28 /* PCIE */
#       define LC_REVERSE_RCVR                            (1 << 0)
#       define LC_REVERSE_XMIT                            (1 << 1)
#       define LC_OPERATING_LINK_WIDTH_MASK               (0x7 << 2)
#       define LC_OPERATING_LINK_WIDTH_SHIFT              2
#       define LC_DETECTED_LINK_WIDTH_MASK                (0x7 << 5)
#       define LC_DETECTED_LINK_WIDTH_SHIFT               5

#घोषणा PCIE_P_CNTL                                       0x40 /* PCIE */
#       define P_IGNORE_EDB_ERR                           (1 << 6)

/* PCIE PORT रेजिस्टरs idx/data 0x38/0x3c */
#घोषणा PCIE_LC_CNTL                                      0xa0
#       define LC_L0S_INACTIVITY(x)                       ((x) << 8)
#       define LC_L0S_INACTIVITY_MASK                     (0xf << 8)
#       define LC_L0S_INACTIVITY_SHIFT                    8
#       define LC_L1_INACTIVITY(x)                        ((x) << 12)
#       define LC_L1_INACTIVITY_MASK                      (0xf << 12)
#       define LC_L1_INACTIVITY_SHIFT                     12
#       define LC_PMI_TO_L1_DIS                           (1 << 16)
#       define LC_ASPM_TO_L1_DIS                          (1 << 24)
#घोषणा PCIE_LC_LINK_WIDTH_CNTL                           0xa2 /* PCIE_P */
#       define LC_LINK_WIDTH_SHIFT                        0
#       define LC_LINK_WIDTH_MASK                         0x7
#       define LC_LINK_WIDTH_X0                           0
#       define LC_LINK_WIDTH_X1                           1
#       define LC_LINK_WIDTH_X2                           2
#       define LC_LINK_WIDTH_X4                           3
#       define LC_LINK_WIDTH_X8                           4
#       define LC_LINK_WIDTH_X16                          6
#       define LC_LINK_WIDTH_RD_SHIFT                     4
#       define LC_LINK_WIDTH_RD_MASK                      0x70
#       define LC_RECONFIG_ARC_MISSING_ESCAPE             (1 << 7)
#       define LC_RECONFIG_NOW                            (1 << 8)
#       define LC_RENEGOTIATION_SUPPORT                   (1 << 9)
#       define LC_RENEGOTIATE_EN                          (1 << 10)
#       define LC_SHORT_RECONFIG_EN                       (1 << 11)
#       define LC_UPCONFIGURE_SUPPORT                     (1 << 12)
#       define LC_UPCONFIGURE_DIS                         (1 << 13)
#       define LC_DYN_LANES_PWR_STATE(x)                  ((x) << 21)
#       define LC_DYN_LANES_PWR_STATE_MASK                (0x3 << 21)
#       define LC_DYN_LANES_PWR_STATE_SHIFT               21
#घोषणा PCIE_LC_N_FTS_CNTL                                0xa3 /* PCIE_P */
#       define LC_XMIT_N_FTS(x)                           ((x) << 0)
#       define LC_XMIT_N_FTS_MASK                         (0xff << 0)
#       define LC_XMIT_N_FTS_SHIFT                        0
#       define LC_XMIT_N_FTS_OVERRIDE_EN                  (1 << 8)
#       define LC_N_FTS_MASK                              (0xff << 24)
#घोषणा PCIE_LC_SPEED_CNTL                                0xa4 /* PCIE_P */
#       define LC_GEN2_EN_STRAP                           (1 << 0)
#       define LC_GEN3_EN_STRAP                           (1 << 1)
#       define LC_TARGET_LINK_SPEED_OVERRIDE_EN           (1 << 2)
#       define LC_TARGET_LINK_SPEED_OVERRIDE_MASK         (0x3 << 3)
#       define LC_TARGET_LINK_SPEED_OVERRIDE_SHIFT        3
#       define LC_FORCE_EN_SW_SPEED_CHANGE                (1 << 5)
#       define LC_FORCE_DIS_SW_SPEED_CHANGE               (1 << 6)
#       define LC_FORCE_EN_HW_SPEED_CHANGE                (1 << 7)
#       define LC_FORCE_DIS_HW_SPEED_CHANGE               (1 << 8)
#       define LC_INITIATE_LINK_SPEED_CHANGE              (1 << 9)
#       define LC_SPEED_CHANGE_ATTEMPTS_ALLOWED_MASK      (0x3 << 10)
#       define LC_SPEED_CHANGE_ATTEMPTS_ALLOWED_SHIFT     10
#       define LC_CURRENT_DATA_RATE_MASK                  (0x3 << 13) /* 0/1/2 = gen1/2/3 */
#       define LC_CURRENT_DATA_RATE_SHIFT                 13
#       define LC_CLR_FAILED_SPD_CHANGE_CNT               (1 << 16)
#       define LC_OTHER_SIDE_EVER_SENT_GEN2               (1 << 18)
#       define LC_OTHER_SIDE_SUPPORTS_GEN2                (1 << 19)
#       define LC_OTHER_SIDE_EVER_SENT_GEN3               (1 << 20)
#       define LC_OTHER_SIDE_SUPPORTS_GEN3                (1 << 21)

#घोषणा PCIE_LC_CNTL2                                     0xb1
#       define LC_ALLOW_PDWN_IN_L1                        (1 << 17)
#       define LC_ALLOW_PDWN_IN_L23                       (1 << 18)

#घोषणा PCIE_LC_CNTL3                                     0xb5 /* PCIE_P */
#       define LC_GO_TO_RECOVERY                          (1 << 30)
#घोषणा PCIE_LC_CNTL4                                     0xb6 /* PCIE_P */
#       define LC_REDO_EQ                                 (1 << 5)
#       define LC_SET_QUIESCE                             (1 << 13)

/*
 * UVD
 */
#घोषणा UVD_UDEC_ADDR_CONFIG				0x3bd3
#घोषणा UVD_UDEC_DB_ADDR_CONFIG				0x3bd4
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG			0x3bd5
#घोषणा UVD_RBC_RB_RPTR					0x3da4
#घोषणा UVD_RBC_RB_WPTR					0x3da5
#घोषणा UVD_STATUS					0x3daf

#घोषणा	UVD_CGC_CTRL					0x3dc2
#	define DCM					(1 << 0)
#	define CG_DT(x)					((x) << 2)
#	define CG_DT_MASK				(0xf << 2)
#	define CLK_OD(x)				((x) << 6)
#	define CLK_OD_MASK				(0x1f << 6)

 /* UVD CTX indirect */
#घोषणा	UVD_CGC_MEM_CTRL				0xC0
#घोषणा	UVD_CGC_CTRL2					0xC1
#	define DYN_OR_EN				(1 << 0)
#	define DYN_RR_EN				(1 << 1)
#	define G_DIV_ID(x)				((x) << 2)
#	define G_DIV_ID_MASK				(0x7 << 2)

/*
 * PM4
 */
#घोषणा PACKET_TYPE0    0
#घोषणा PACKET0(reg, n) ((PACKET_TYPE0 << 30) |				\
                         ((reg) & 0xFFFF) |				\
                         ((n) & 0x3FFF) << 16)
#घोषणा CP_PACKET2			0x80000000
#घोषणा		PACKET2_PAD_SHIFT		0
#घोषणा		PACKET2_PAD_MASK		(0x3fffffff << 0)

#घोषणा PACKET2(v)	(CP_PACKET2 | REG_SET(PACKET2_PAD, (v)))
#घोषणा RADEON_PACKET_TYPE3 3
#घोषणा PACKET3(op, n)	((RADEON_PACKET_TYPE3 << 30) |			\
			 (((op) & 0xFF) << 8) |				\
			 ((n) & 0x3FFF) << 16)

#घोषणा PACKET3_COMPUTE(op, n) (PACKET3(op, n) | 1 << 1)

/* Packet 3 types */
#घोषणा	PACKET3_NOP					0x10
#घोषणा	PACKET3_SET_BASE				0x11
#घोषणा		PACKET3_BASE_INDEX(x)                  ((x) << 0)
#घोषणा			GDS_PARTITION_BASE		2
#घोषणा			CE_PARTITION_BASE		3
#घोषणा	PACKET3_CLEAR_STATE				0x12
#घोषणा	PACKET3_INDEX_BUFFER_SIZE			0x13
#घोषणा	PACKET3_DISPATCH_सूचीECT				0x15
#घोषणा	PACKET3_DISPATCH_INसूचीECT			0x16
#घोषणा	PACKET3_ALLOC_GDS				0x1B
#घोषणा	PACKET3_WRITE_GDS_RAM				0x1C
#घोषणा	PACKET3_ATOMIC_GDS				0x1D
#घोषणा	PACKET3_ATOMIC					0x1E
#घोषणा	PACKET3_OCCLUSION_QUERY				0x1F
#घोषणा	PACKET3_SET_PREDICATION				0x20
#घोषणा	PACKET3_REG_RMW					0x21
#घोषणा	PACKET3_COND_EXEC				0x22
#घोषणा	PACKET3_PRED_EXEC				0x23
#घोषणा	PACKET3_DRAW_INसूचीECT				0x24
#घोषणा	PACKET3_DRAW_INDEX_INसूचीECT			0x25
#घोषणा	PACKET3_INDEX_BASE				0x26
#घोषणा	PACKET3_DRAW_INDEX_2				0x27
#घोषणा	PACKET3_CONTEXT_CONTROL				0x28
#घोषणा	PACKET3_INDEX_TYPE				0x2A
#घोषणा	PACKET3_DRAW_INसूचीECT_MULTI			0x2C
#घोषणा	PACKET3_DRAW_INDEX_AUTO				0x2D
#घोषणा	PACKET3_DRAW_INDEX_IMMD				0x2E
#घोषणा	PACKET3_NUM_INSTANCES				0x2F
#घोषणा	PACKET3_DRAW_INDEX_MULTI_AUTO			0x30
#घोषणा	PACKET3_INसूचीECT_BUFFER_CONST			0x31
#घोषणा	PACKET3_INसूचीECT_BUFFER				0x3F
#घोषणा	PACKET3_STRMOUT_BUFFER_UPDATE			0x34
#घोषणा	PACKET3_DRAW_INDEX_OFFSET_2			0x35
#घोषणा	PACKET3_DRAW_INDEX_MULTI_ELEMENT		0x36
#घोषणा	PACKET3_WRITE_DATA				0x37
#घोषणा		WRITE_DATA_DST_SEL(x)                   ((x) << 8)
                /* 0 - रेजिस्टर
		 * 1 - memory (sync - via GRBM)
		 * 2 - tc/l2
		 * 3 - gds
		 * 4 - reserved
		 * 5 - memory (async - direct)
		 */
#घोषणा		WR_ONE_ADDR                             (1 << 16)
#घोषणा		WR_CONFIRM                              (1 << 20)
#घोषणा		WRITE_DATA_ENGINE_SEL(x)                ((x) << 30)
                /* 0 - me
		 * 1 - pfp
		 * 2 - ce
		 */
#घोषणा	PACKET3_DRAW_INDEX_INसूचीECT_MULTI		0x38
#घोषणा	PACKET3_MEM_SEMAPHORE				0x39
#घोषणा	PACKET3_MPEG_INDEX				0x3A
#घोषणा	PACKET3_COPY_DW					0x3B
#घोषणा	PACKET3_WAIT_REG_MEM				0x3C
#घोषणा		WAIT_REG_MEM_FUNCTION(x)                ((x) << 0)
                /* 0 - always
		 * 1 - <
		 * 2 - <=
		 * 3 - ==
		 * 4 - !=
		 * 5 - >=
		 * 6 - >
		 */
#घोषणा		WAIT_REG_MEM_MEM_SPACE(x)               ((x) << 4)
                /* 0 - reg
		 * 1 - mem
		 */
#घोषणा		WAIT_REG_MEM_ENGINE(x)                  ((x) << 8)
                /* 0 - me
		 * 1 - pfp
		 */
#घोषणा	PACKET3_MEM_WRITE				0x3D
#घोषणा	PACKET3_COPY_DATA				0x40
#घोषणा	PACKET3_CP_DMA					0x41
/* 1. header
 * 2. SRC_ADDR_LO or DATA [31:0]
 * 3. CP_SYNC [31] | SRC_SEL [30:29] | ENGINE [27] | DST_SEL [21:20] |
 *    SRC_ADDR_HI [7:0]
 * 4. DST_ADDR_LO [31:0]
 * 5. DST_ADDR_HI [7:0]
 * 6. COMMAND [30:21] | BYTE_COUNT [20:0]
 */
#              define PACKET3_CP_DMA_DST_SEL(x)    ((x) << 20)
                /* 0 - DST_ADDR
		 * 1 - GDS
		 */
#              define PACKET3_CP_DMA_ENGINE(x)     ((x) << 27)
                /* 0 - ME
		 * 1 - PFP
		 */
#              define PACKET3_CP_DMA_SRC_SEL(x)    ((x) << 29)
                /* 0 - SRC_ADDR
		 * 1 - GDS
		 * 2 - DATA
		 */
#              define PACKET3_CP_DMA_CP_SYNC       (1 << 31)
/* COMMAND */
#              define PACKET3_CP_DMA_DIS_WC        (1 << 21)
#              define PACKET3_CP_DMA_CMD_SRC_SWAP(x) ((x) << 22)
                /* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
#              define PACKET3_CP_DMA_CMD_DST_SWAP(x) ((x) << 24)
                /* 0 - none
		 * 1 - 8 in 16
		 * 2 - 8 in 32
		 * 3 - 8 in 64
		 */
#              define PACKET3_CP_DMA_CMD_SAS       (1 << 26)
                /* 0 - memory
		 * 1 - रेजिस्टर
		 */
#              define PACKET3_CP_DMA_CMD_DAS       (1 << 27)
                /* 0 - memory
		 * 1 - रेजिस्टर
		 */
#              define PACKET3_CP_DMA_CMD_SAIC      (1 << 28)
#              define PACKET3_CP_DMA_CMD_DAIC      (1 << 29)
#              define PACKET3_CP_DMA_CMD_RAW_WAIT  (1 << 30)
#घोषणा	PACKET3_PFP_SYNC_ME				0x42
#घोषणा	PACKET3_SURFACE_SYNC				0x43
#              define PACKET3_DEST_BASE_0_ENA      (1 << 0)
#              define PACKET3_DEST_BASE_1_ENA      (1 << 1)
#              define PACKET3_CB0_DEST_BASE_ENA    (1 << 6)
#              define PACKET3_CB1_DEST_BASE_ENA    (1 << 7)
#              define PACKET3_CB2_DEST_BASE_ENA    (1 << 8)
#              define PACKET3_CB3_DEST_BASE_ENA    (1 << 9)
#              define PACKET3_CB4_DEST_BASE_ENA    (1 << 10)
#              define PACKET3_CB5_DEST_BASE_ENA    (1 << 11)
#              define PACKET3_CB6_DEST_BASE_ENA    (1 << 12)
#              define PACKET3_CB7_DEST_BASE_ENA    (1 << 13)
#              define PACKET3_DB_DEST_BASE_ENA     (1 << 14)
#              define PACKET3_DEST_BASE_2_ENA      (1 << 19)
#              define PACKET3_DEST_BASE_3_ENA      (1 << 21)
#              define PACKET3_TCL1_ACTION_ENA      (1 << 22)
#              define PACKET3_TC_ACTION_ENA        (1 << 23)
#              define PACKET3_CB_ACTION_ENA        (1 << 25)
#              define PACKET3_DB_ACTION_ENA        (1 << 26)
#              define PACKET3_SH_KCACHE_ACTION_ENA (1 << 27)
#              define PACKET3_SH_ICACHE_ACTION_ENA (1 << 29)
#घोषणा	PACKET3_ME_INITIALIZE				0x44
#घोषणा		PACKET3_ME_INITIALIZE_DEVICE_ID(x) ((x) << 16)
#घोषणा	PACKET3_COND_WRITE				0x45
#घोषणा	PACKET3_EVENT_WRITE				0x46
#घोषणा		EVENT_TYPE(x)                           ((x) << 0)
#घोषणा		EVENT_INDEX(x)                          ((x) << 8)
                /* 0 - any non-TS event
		 * 1 - ZPASS_DONE
		 * 2 - SAMPLE_PIPELINESTAT
		 * 3 - SAMPLE_STREAMOUTSTAT*
		 * 4 - *S_PARTIAL_FLUSH
		 * 5 - EOP events
		 * 6 - EOS events
		 * 7 - CACHE_FLUSH, CACHE_FLUSH_AND_INV_EVENT
		 */
#घोषणा		INV_L2                                  (1 << 20)
                /* INV TC L2 cache when EVENT_INDEX = 7 */
#घोषणा	PACKET3_EVENT_WRITE_EOP				0x47
#घोषणा		DATA_SEL(x)                             ((x) << 29)
                /* 0 - discard
		 * 1 - send low 32bit data
		 * 2 - send 64bit data
		 * 3 - send 64bit counter value
		 */
#घोषणा		INT_SEL(x)                              ((x) << 24)
                /* 0 - none
		 * 1 - पूर्णांकerrupt only (DATA_SEL = 0)
		 * 2 - पूर्णांकerrupt when data ग_लिखो is confirmed
		 */
#घोषणा	PACKET3_EVENT_WRITE_EOS				0x48
#घोषणा	PACKET3_PREAMBLE_CNTL				0x4A
#              define PACKET3_PREAMBLE_BEGIN_CLEAR_STATE     (2 << 28)
#              define PACKET3_PREAMBLE_END_CLEAR_STATE       (3 << 28)
#घोषणा	PACKET3_ONE_REG_WRITE				0x57
#घोषणा	PACKET3_LOAD_CONFIG_REG				0x5F
#घोषणा	PACKET3_LOAD_CONTEXT_REG			0x60
#घोषणा	PACKET3_LOAD_SH_REG				0x61
#घोषणा	PACKET3_SET_CONFIG_REG				0x68
#घोषणा		PACKET3_SET_CONFIG_REG_START			0x00002000
#घोषणा		PACKET3_SET_CONFIG_REG_END			0x00002c00
#घोषणा	PACKET3_SET_CONTEXT_REG				0x69
#घोषणा		PACKET3_SET_CONTEXT_REG_START			0x000a000
#घोषणा		PACKET3_SET_CONTEXT_REG_END			0x000a400
#घोषणा	PACKET3_SET_CONTEXT_REG_INसूचीECT		0x73
#घोषणा	PACKET3_SET_RESOURCE_INसूचीECT			0x74
#घोषणा	PACKET3_SET_SH_REG				0x76
#घोषणा		PACKET3_SET_SH_REG_START			0x00002c00
#घोषणा		PACKET3_SET_SH_REG_END				0x00003000
#घोषणा	PACKET3_SET_SH_REG_OFFSET			0x77
#घोषणा	PACKET3_ME_WRITE				0x7A
#घोषणा	PACKET3_SCRATCH_RAM_WRITE			0x7D
#घोषणा	PACKET3_SCRATCH_RAM_READ			0x7E
#घोषणा	PACKET3_CE_WRITE				0x7F
#घोषणा	PACKET3_LOAD_CONST_RAM				0x80
#घोषणा	PACKET3_WRITE_CONST_RAM				0x81
#घोषणा	PACKET3_WRITE_CONST_RAM_OFFSET			0x82
#घोषणा	PACKET3_DUMP_CONST_RAM				0x83
#घोषणा	PACKET3_INCREMENT_CE_COUNTER			0x84
#घोषणा	PACKET3_INCREMENT_DE_COUNTER			0x85
#घोषणा	PACKET3_WAIT_ON_CE_COUNTER			0x86
#घोषणा	PACKET3_WAIT_ON_DE_COUNTER			0x87
#घोषणा	PACKET3_WAIT_ON_DE_COUNTER_DIFF			0x88
#घोषणा	PACKET3_SET_CE_DE_COUNTERS			0x89
#घोषणा	PACKET3_WAIT_ON_AVAIL_BUFFER			0x8A
#घोषणा	PACKET3_SWITCH_BUFFER				0x8B

/* ASYNC DMA - first instance at 0xd000, second at 0xd800 */
#घोषणा DMA0_REGISTER_OFFSET                              0x0 /* not a रेजिस्टर */
#घोषणा DMA1_REGISTER_OFFSET                              0x200 /* not a रेजिस्टर */

#घोषणा DMA_RB_CNTL                                       0x3400
#       define DMA_RB_ENABLE                              (1 << 0)
#       define DMA_RB_SIZE(x)                             ((x) << 1) /* log2 */
#       define DMA_RB_SWAP_ENABLE                         (1 << 9) /* 8IN32 */
#       define DMA_RPTR_WRITEBACK_ENABLE                  (1 << 12)
#       define DMA_RPTR_WRITEBACK_SWAP_ENABLE             (1 << 13)  /* 8IN32 */
#       define DMA_RPTR_WRITEBACK_TIMER(x)                ((x) << 16) /* log2 */
#घोषणा DMA_RB_BASE                                       0x3401
#घोषणा DMA_RB_RPTR                                       0x3402
#घोषणा DMA_RB_WPTR                                       0x3403

#घोषणा DMA_RB_RPTR_ADDR_HI                               0x3407
#घोषणा DMA_RB_RPTR_ADDR_LO                               0x3408

#घोषणा DMA_IB_CNTL                                       0x3409
#       define DMA_IB_ENABLE                              (1 << 0)
#       define DMA_IB_SWAP_ENABLE                         (1 << 4)
#       define CMD_VMID_FORCE                             (1 << 31)
#घोषणा DMA_IB_RPTR                                       0x340a
#घोषणा DMA_CNTL                                          0x340b
#       define TRAP_ENABLE                                (1 << 0)
#       define SEM_INCOMPLETE_INT_ENABLE                  (1 << 1)
#       define SEM_WAIT_INT_ENABLE                        (1 << 2)
#       define DATA_SWAP_ENABLE                           (1 << 3)
#       define FENCE_SWAP_ENABLE                          (1 << 4)
#       define CTXEMPTY_INT_ENABLE                        (1 << 28)
#घोषणा DMA_STATUS_REG                                    0x340d
#       define DMA_IDLE                                   (1 << 0)
#घोषणा DMA_TILING_CONFIG  				  0x342e

#घोषणा	DMA_POWER_CNTL					0x342f
#       define MEM_POWER_OVERRIDE                       (1 << 8)
#घोषणा	DMA_CLK_CTRL					0x3430

#घोषणा	DMA_PG						0x3435
#	define PG_CNTL_ENABLE				(1 << 0)
#घोषणा	DMA_PGFSM_CONFIG				0x3436
#घोषणा	DMA_PGFSM_WRITE					0x3437

#घोषणा DMA_PACKET(cmd, b, t, s, n)	((((cmd) & 0xF) << 28) |	\
					 (((b) & 0x1) << 26) |		\
					 (((t) & 0x1) << 23) |		\
					 (((s) & 0x1) << 22) |		\
					 (((n) & 0xFFFFF) << 0))

#घोषणा DMA_IB_PACKET(cmd, vmid, n)	((((cmd) & 0xF) << 28) |	\
					 (((vmid) & 0xF) << 20) |	\
					 (((n) & 0xFFFFF) << 0))

#घोषणा DMA_PTE_PDE_PACKET(n)		((2 << 28) |			\
					 (1 << 26) |			\
					 (1 << 21) |			\
					 (((n) & 0xFFFFF) << 0))

/* async DMA Packet types */
#घोषणा	DMA_PACKET_WRITE				  0x2
#घोषणा	DMA_PACKET_COPY					  0x3
#घोषणा	DMA_PACKET_INसूचीECT_BUFFER			  0x4
#घोषणा	DMA_PACKET_SEMAPHORE				  0x5
#घोषणा	DMA_PACKET_FENCE				  0x6
#घोषणा	DMA_PACKET_TRAP					  0x7
#घोषणा	DMA_PACKET_SRBM_WRITE				  0x9
#घोषणा	DMA_PACKET_CONSTANT_FILL			  0xd
#घोषणा	DMA_PACKET_POLL_REG_MEM				  0xe
#घोषणा	DMA_PACKET_NOP					  0xf

#घोषणा VCE_STATUS					0x20004
#घोषणा VCE_VCPU_CNTL					0x20014
#घोषणा		VCE_CLK_EN				(1 << 0)
#घोषणा VCE_VCPU_CACHE_OFFSET0				0x20024
#घोषणा VCE_VCPU_CACHE_SIZE0				0x20028
#घोषणा VCE_VCPU_CACHE_OFFSET1				0x2002c
#घोषणा VCE_VCPU_CACHE_SIZE1				0x20030
#घोषणा VCE_VCPU_CACHE_OFFSET2				0x20034
#घोषणा VCE_VCPU_CACHE_SIZE2				0x20038
#घोषणा VCE_SOFT_RESET					0x20120
#घोषणा 	VCE_ECPU_SOFT_RESET			(1 << 0)
#घोषणा 	VCE_FME_SOFT_RESET			(1 << 2)
#घोषणा VCE_RB_BASE_LO2					0x2016c
#घोषणा VCE_RB_BASE_HI2					0x20170
#घोषणा VCE_RB_SIZE2					0x20174
#घोषणा VCE_RB_RPTR2					0x20178
#घोषणा VCE_RB_WPTR2					0x2017c
#घोषणा VCE_RB_BASE_LO					0x20180
#घोषणा VCE_RB_BASE_HI					0x20184
#घोषणा VCE_RB_SIZE					0x20188
#घोषणा VCE_RB_RPTR					0x2018c
#घोषणा VCE_RB_WPTR					0x20190
#घोषणा VCE_CLOCK_GATING_A				0x202f8
#घोषणा VCE_CLOCK_GATING_B				0x202fc
#घोषणा VCE_UENC_CLOCK_GATING				0x205bc
#घोषणा VCE_UENC_REG_CLOCK_GATING			0x205c0
#घोषणा VCE_FW_REG_STATUS				0x20e10
#	define VCE_FW_REG_STATUS_BUSY			(1 << 0)
#	define VCE_FW_REG_STATUS_PASS			(1 << 3)
#	define VCE_FW_REG_STATUS_DONE			(1 << 11)
#घोषणा VCE_LMI_FW_START_KEYSEL				0x20e18
#घोषणा VCE_LMI_FW_PERIODIC_CTRL			0x20e20
#घोषणा VCE_LMI_CTRL2					0x20e74
#घोषणा VCE_LMI_CTRL					0x20e98
#घोषणा VCE_LMI_VM_CTRL					0x20ea0
#घोषणा VCE_LMI_SWAP_CNTL				0x20eb4
#घोषणा VCE_LMI_SWAP_CNTL1				0x20eb8
#घोषणा VCE_LMI_CACHE_CTRL				0x20ef4

#घोषणा VCE_CMD_NO_OP					0x00000000
#घोषणा VCE_CMD_END					0x00000001
#घोषणा VCE_CMD_IB					0x00000002
#घोषणा VCE_CMD_FENCE					0x00000003
#घोषणा VCE_CMD_TRAP					0x00000004
#घोषणा VCE_CMD_IB_AUTO					0x00000005
#घोषणा VCE_CMD_SEMAPHORE				0x00000006


//#dce stupp
/* display controller offsets used क्रम crtc/cur/lut/grph/viewport/etc. */
#घोषणा SI_CRTC0_REGISTER_OFFSET                0 //(0x6df0 - 0x6df0)/4
#घोषणा SI_CRTC1_REGISTER_OFFSET                0x300 //(0x79f0 - 0x6df0)/4
#घोषणा SI_CRTC2_REGISTER_OFFSET                0x2600 //(0x105f0 - 0x6df0)/4
#घोषणा SI_CRTC3_REGISTER_OFFSET                0x2900 //(0x111f0 - 0x6df0)/4
#घोषणा SI_CRTC4_REGISTER_OFFSET                0x2c00 //(0x11df0 - 0x6df0)/4
#घोषणा SI_CRTC5_REGISTER_OFFSET                0x2f00 //(0x129f0 - 0x6df0)/4

#घोषणा CURSOR_WIDTH 64
#घोषणा CURSOR_HEIGHT 64
#घोषणा AMDGPU_MM_INDEX		        0x0000
#घोषणा AMDGPU_MM_DATA		        0x0001

#घोषणा VERDE_NUM_CRTC 6
#घोषणा	BLACKOUT_MODE_MASK			0x00000007
#घोषणा	VGA_RENDER_CONTROL			0xC0
#घोषणा R_000300_VGA_RENDER_CONTROL             0xC0
#घोषणा C_000300_VGA_VSTATUS_CNTL               0xFFFCFFFF
#घोषणा EVERGREEN_CRTC_STATUS                   0x1BA3
#घोषणा EVERGREEN_CRTC_V_BLANK                  (1 << 0)
#घोषणा EVERGREEN_CRTC_STATUS_POSITION          0x1BA4
/* CRTC blocks at 0x6df0, 0x79f0, 0x105f0, 0x111f0, 0x11df0, 0x129f0 */
#घोषणा EVERGREEN_CRTC_V_BLANK_START_END                0x1b8d
#घोषणा EVERGREEN_CRTC_CONTROL                          0x1b9c
#घोषणा EVERGREEN_CRTC_MASTER_EN                 (1 << 0)
#घोषणा EVERGREEN_CRTC_DISP_READ_REQUEST_DISABLE (1 << 24)
#घोषणा EVERGREEN_CRTC_BLANK_CONTROL                    0x1b9d
#घोषणा EVERGREEN_CRTC_BLANK_DATA_EN             (1 << 8)
#घोषणा EVERGREEN_CRTC_V_BLANK                   (1 << 0)
#घोषणा EVERGREEN_CRTC_STATUS_HV_COUNT                  0x1ba8
#घोषणा EVERGREEN_CRTC_UPDATE_LOCK                      0x1bb5
#घोषणा EVERGREEN_MASTER_UPDATE_LOCK                    0x1bbd
#घोषणा EVERGREEN_MASTER_UPDATE_MODE                    0x1bbe
#घोषणा EVERGREEN_GRPH_UPDATE_LOCK               (1 << 16)
#घोषणा EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH     0x1a07
#घोषणा EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS_HIGH   0x1a08
#घोषणा EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS          0x1a04
#घोषणा EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS        0x1a05
#घोषणा EVERGREEN_GRPH_UPDATE                           0x1a11
#घोषणा EVERGREEN_VGA_MEMORY_BASE_ADDRESS               0xc4
#घोषणा EVERGREEN_VGA_MEMORY_BASE_ADDRESS_HIGH          0xc9
#घोषणा EVERGREEN_GRPH_SURFACE_UPDATE_PENDING    (1 << 2)

#घोषणा EVERGREEN_DATA_FORMAT                           0x1ac0
#       define EVERGREEN_INTERLEAVE_EN                  (1 << 0)

#घोषणा MC_SHARED_CHMAP__NOOFCHAN_MASK 0xf000
#घोषणा MC_SHARED_CHMAP__NOOFCHAN__SHIFT 0xc

#घोषणा R600_D1GRPH_ARRAY_MODE_LINEAR_GENERAL            (0 << 20)
#घोषणा R600_D1GRPH_ARRAY_MODE_LINEAR_ALIGNED            (1 << 20)
#घोषणा R600_D1GRPH_ARRAY_MODE_1D_TILED_THIN1            (2 << 20)
#घोषणा R600_D1GRPH_ARRAY_MODE_2D_TILED_THIN1            (4 << 20)

#घोषणा R700_D1GRPH_PRIMARY_SURFACE_ADDRESS_HIGH                0x1a45
#घोषणा R700_D2GRPH_PRIMARY_SURFACE_ADDRESS_HIGH                0x1845

#घोषणा R700_D2GRPH_SECONDARY_SURFACE_ADDRESS_HIGH              0x1847
#घोषणा R700_D1GRPH_SECONDARY_SURFACE_ADDRESS_HIGH              0x1a47

#घोषणा DISP_INTERRUPT_STATUS__LB_D1_VBLANK_INTERRUPT_MASK 0x8
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE__LB_D2_VBLANK_INTERRUPT_MASK 0x8
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE2__LB_D3_VBLANK_INTERRUPT_MASK 0x8
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE3__LB_D4_VBLANK_INTERRUPT_MASK 0x8
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE4__LB_D5_VBLANK_INTERRUPT_MASK 0x8
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE5__LB_D6_VBLANK_INTERRUPT_MASK 0x8

#घोषणा DISP_INTERRUPT_STATUS__LB_D1_VLINE_INTERRUPT_MASK 0x4
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE__LB_D2_VLINE_INTERRUPT_MASK 0x4
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE2__LB_D3_VLINE_INTERRUPT_MASK 0x4
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE3__LB_D4_VLINE_INTERRUPT_MASK 0x4
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE4__LB_D5_VLINE_INTERRUPT_MASK 0x4
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE5__LB_D6_VLINE_INTERRUPT_MASK 0x4

#घोषणा DISP_INTERRUPT_STATUS__DC_HPD1_INTERRUPT_MASK 0x20000
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE__DC_HPD2_INTERRUPT_MASK 0x20000
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE2__DC_HPD3_INTERRUPT_MASK 0x20000
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE3__DC_HPD4_INTERRUPT_MASK 0x20000
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE4__DC_HPD5_INTERRUPT_MASK 0x20000
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE5__DC_HPD6_INTERRUPT_MASK 0x20000

#घोषणा GRPH_INTERRUPT_STATUS__GRPH_PFLIP_INT_OCCURRED_MASK 0x1
#घोषणा GRPH_INTERRUPT_STATUS__GRPH_PFLIP_INT_CLEAR_MASK 0x100

#घोषणा DC_HPD1_INT_CONTROL__DC_HPD1_INT_ACK_MASK 0x1

#घोषणा R600_D1GRPH_SWAP_CONTROL                               0x1843
#घोषणा R600_D1GRPH_SWAP_ENDIAN_NONE                    (0 << 0)
#घोषणा R600_D1GRPH_SWAP_ENDIAN_16BIT                   (1 << 0)
#घोषणा R600_D1GRPH_SWAP_ENDIAN_32BIT                   (2 << 0)
#घोषणा R600_D1GRPH_SWAP_ENDIAN_64BIT                   (3 << 0)

#घोषणा AVIVO_D1VGA_CONTROL					0x00cc
#       define AVIVO_DVGA_CONTROL_MODE_ENABLE            (1 << 0)
#       define AVIVO_DVGA_CONTROL_TIMING_SELECT          (1 << 8)
#       define AVIVO_DVGA_CONTROL_SYNC_POLARITY_SELECT   (1 << 9)
#       define AVIVO_DVGA_CONTROL_OVERSCAN_TIMING_SELECT (1 << 10)
#       define AVIVO_DVGA_CONTROL_OVERSCAN_COLOR_EN      (1 << 16)
#       define AVIVO_DVGA_CONTROL_ROTATE                 (1 << 24)
#घोषणा AVIVO_D2VGA_CONTROL					0x00ce

#घोषणा R600_BUS_CNTL                                           0x1508
#       define R600_BIOS_ROM_DIS                                (1 << 1)

#घोषणा R600_ROM_CNTL                              0x580
#       define R600_SCK_OVERWRITE                  (1 << 1)
#       define R600_SCK_PRESCALE_CRYSTAL_CLK_SHIFT 28
#       define R600_SCK_PRESCALE_CRYSTAL_CLK_MASK  (0xf << 28)

#घोषणा GRPH_INTERRUPT_CONTROL__GRPH_PFLIP_INT_MASK_MASK 0x1

#घोषणा FMT_BIT_DEPTH_CONTROL                0x1bf2
#घोषणा FMT_TRUNCATE_EN               (1 << 0)
#घोषणा FMT_TRUNCATE_DEPTH            (1 << 4)
#घोषणा FMT_SPATIAL_DITHER_EN         (1 << 8)
#घोषणा FMT_SPATIAL_DITHER_MODE(x)    ((x) << 9)
#घोषणा FMT_SPATIAL_DITHER_DEPTH      (1 << 12)
#घोषणा FMT_FRAME_RANDOM_ENABLE       (1 << 13)
#घोषणा FMT_RGB_RANDOM_ENABLE         (1 << 14)
#घोषणा FMT_HIGHPASS_RANDOM_ENABLE    (1 << 15)
#घोषणा FMT_TEMPORAL_DITHER_EN        (1 << 16)
#घोषणा FMT_TEMPORAL_DITHER_DEPTH     (1 << 20)
#घोषणा FMT_TEMPORAL_DITHER_OFFSET(x) ((x) << 21)
#घोषणा FMT_TEMPORAL_LEVEL            (1 << 24)
#घोषणा FMT_TEMPORAL_DITHER_RESET     (1 << 25)
#घोषणा FMT_25FRC_SEL(x)              ((x) << 26)
#घोषणा FMT_50FRC_SEL(x)              ((x) << 28)
#घोषणा FMT_75FRC_SEL(x)              ((x) << 30)

#घोषणा EVERGREEN_DC_LUT_CONTROL                        0x1a80
#घोषणा EVERGREEN_DC_LUT_BLACK_OFFSET_BLUE              0x1a81
#घोषणा EVERGREEN_DC_LUT_BLACK_OFFSET_GREEN             0x1a82
#घोषणा EVERGREEN_DC_LUT_BLACK_OFFSET_RED               0x1a83
#घोषणा EVERGREEN_DC_LUT_WHITE_OFFSET_BLUE              0x1a84
#घोषणा EVERGREEN_DC_LUT_WHITE_OFFSET_GREEN             0x1a85
#घोषणा EVERGREEN_DC_LUT_WHITE_OFFSET_RED               0x1a86
#घोषणा EVERGREEN_DC_LUT_30_COLOR                       0x1a7c
#घोषणा EVERGREEN_DC_LUT_RW_INDEX                       0x1a79
#घोषणा EVERGREEN_DC_LUT_WRITE_EN_MASK                  0x1a7e
#घोषणा EVERGREEN_DC_LUT_RW_MODE                        0x1a78

#घोषणा EVERGREEN_GRPH_ENABLE                           0x1a00
#घोषणा EVERGREEN_GRPH_CONTROL                          0x1a01
#घोषणा EVERGREEN_GRPH_DEPTH(x)                  (((x) & 0x3) << 0)
#घोषणा EVERGREEN_GRPH_DEPTH_8BPP                0
#घोषणा EVERGREEN_GRPH_DEPTH_16BPP               1
#घोषणा EVERGREEN_GRPH_DEPTH_32BPP               2
#घोषणा EVERGREEN_GRPH_NUM_BANKS(x)              (((x) & 0x3) << 2)
#घोषणा EVERGREEN_ADDR_SURF_2_BANK               0
#घोषणा EVERGREEN_ADDR_SURF_4_BANK               1
#घोषणा EVERGREEN_ADDR_SURF_8_BANK               2
#घोषणा EVERGREEN_ADDR_SURF_16_BANK              3
#घोषणा EVERGREEN_GRPH_Z(x)                      (((x) & 0x3) << 4)
#घोषणा EVERGREEN_GRPH_BANK_WIDTH(x)             (((x) & 0x3) << 6)
#घोषणा EVERGREEN_ADDR_SURF_BANK_WIDTH_1         0
#घोषणा EVERGREEN_ADDR_SURF_BANK_WIDTH_2         1
#घोषणा EVERGREEN_ADDR_SURF_BANK_WIDTH_4         2
#घोषणा EVERGREEN_ADDR_SURF_BANK_WIDTH_8         3
#घोषणा EVERGREEN_GRPH_FORMAT(x)                 (((x) & 0x7) << 8)

#घोषणा EVERGREEN_GRPH_FORMAT_INDEXED            0
#घोषणा EVERGREEN_GRPH_FORMAT_ARGB1555           0
#घोषणा EVERGREEN_GRPH_FORMAT_ARGB565            1
#घोषणा EVERGREEN_GRPH_FORMAT_ARGB4444           2
#घोषणा EVERGREEN_GRPH_FORMAT_AI88               3
#घोषणा EVERGREEN_GRPH_FORMAT_MONO16             4
#घोषणा EVERGREEN_GRPH_FORMAT_BGRA5551           5

/* 32 BPP */
#घोषणा EVERGREEN_GRPH_FORMAT_ARGB8888           0
#घोषणा EVERGREEN_GRPH_FORMAT_ARGB2101010        1
#घोषणा EVERGREEN_GRPH_FORMAT_32BPP_DIG          2
#घोषणा EVERGREEN_GRPH_FORMAT_8B_ARGB2101010     3
#घोषणा EVERGREEN_GRPH_FORMAT_BGRA1010102        4
#घोषणा EVERGREEN_GRPH_FORMAT_8B_BGRA1010102     5
#घोषणा EVERGREEN_GRPH_FORMAT_RGB111110          6
#घोषणा EVERGREEN_GRPH_FORMAT_BGR101111          7
#घोषणा EVERGREEN_GRPH_BANK_HEIGHT(x)            (((x) & 0x3) << 11)
#घोषणा EVERGREEN_ADDR_SURF_BANK_HEIGHT_1        0
#घोषणा EVERGREEN_ADDR_SURF_BANK_HEIGHT_2        1
#घोषणा EVERGREEN_ADDR_SURF_BANK_HEIGHT_4        2
#घोषणा EVERGREEN_ADDR_SURF_BANK_HEIGHT_8        3
#घोषणा EVERGREEN_GRPH_TILE_SPLIT(x)             (((x) & 0x7) << 13)
#घोषणा EVERGREEN_ADDR_SURF_TILE_SPLIT_64B       0
#घोषणा EVERGREEN_ADDR_SURF_TILE_SPLIT_128B      1
#घोषणा EVERGREEN_ADDR_SURF_TILE_SPLIT_256B      2
#घोषणा EVERGREEN_ADDR_SURF_TILE_SPLIT_512B      3
#घोषणा EVERGREEN_ADDR_SURF_TILE_SPLIT_1KB       4
#घोषणा EVERGREEN_ADDR_SURF_TILE_SPLIT_2KB       5
#घोषणा EVERGREEN_ADDR_SURF_TILE_SPLIT_4KB       6
#घोषणा EVERGREEN_GRPH_MACRO_TILE_ASPECT(x)      (((x) & 0x3) << 18)
#घोषणा EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_1  0
#घोषणा EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_2  1
#घोषणा EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_4  2
#घोषणा EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_8  3
#घोषणा EVERGREEN_GRPH_ARRAY_MODE(x)             (((x) & 0x7) << 20)
#घोषणा EVERGREEN_GRPH_ARRAY_LINEAR_GENERAL      0
#घोषणा EVERGREEN_GRPH_ARRAY_LINEAR_ALIGNED      1
#घोषणा EVERGREEN_GRPH_ARRAY_1D_TILED_THIN1      2
#घोषणा EVERGREEN_GRPH_ARRAY_2D_TILED_THIN1      4
#घोषणा EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_1  0
#घोषणा EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_2  1
#घोषणा EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_4  2
#घोषणा EVERGREEN_ADDR_SURF_MACRO_TILE_ASPECT_8  3

#घोषणा EVERGREEN_GRPH_SWAP_CONTROL                     0x1a03
#घोषणा EVERGREEN_GRPH_ENDIAN_SWAP(x)            (((x) & 0x3) << 0)
#       define EVERGREEN_GRPH_ENDIAN_NONE               0
#       define EVERGREEN_GRPH_ENDIAN_8IN16              1
#       define EVERGREEN_GRPH_ENDIAN_8IN32              2
#       define EVERGREEN_GRPH_ENDIAN_8IN64              3
#घोषणा EVERGREEN_GRPH_RED_CROSSBAR(x)           (((x) & 0x3) << 4)
#       define EVERGREEN_GRPH_RED_SEL_R                 0
#       define EVERGREEN_GRPH_RED_SEL_G                 1
#       define EVERGREEN_GRPH_RED_SEL_B                 2
#       define EVERGREEN_GRPH_RED_SEL_A                 3
#घोषणा EVERGREEN_GRPH_GREEN_CROSSBAR(x)         (((x) & 0x3) << 6)
#       define EVERGREEN_GRPH_GREEN_SEL_G               0
#       define EVERGREEN_GRPH_GREEN_SEL_B               1
#       define EVERGREEN_GRPH_GREEN_SEL_A               2
#       define EVERGREEN_GRPH_GREEN_SEL_R               3
#घोषणा EVERGREEN_GRPH_BLUE_CROSSBAR(x)          (((x) & 0x3) << 8)
#       define EVERGREEN_GRPH_BLUE_SEL_B                0
#       define EVERGREEN_GRPH_BLUE_SEL_A                1
#       define EVERGREEN_GRPH_BLUE_SEL_R                2
#       define EVERGREEN_GRPH_BLUE_SEL_G                3
#घोषणा EVERGREEN_GRPH_ALPHA_CROSSBAR(x)         (((x) & 0x3) << 10)
#       define EVERGREEN_GRPH_ALPHA_SEL_A               0
#       define EVERGREEN_GRPH_ALPHA_SEL_R               1
#       define EVERGREEN_GRPH_ALPHA_SEL_G               2
#       define EVERGREEN_GRPH_ALPHA_SEL_B               3

#घोषणा EVERGREEN_D3VGA_CONTROL                         0xf8
#घोषणा EVERGREEN_D4VGA_CONTROL                         0xf9
#घोषणा EVERGREEN_D5VGA_CONTROL                         0xfa
#घोषणा EVERGREEN_D6VGA_CONTROL                         0xfb

#घोषणा EVERGREEN_GRPH_SURFACE_ADDRESS_MASK      0xffffff00

#घोषणा EVERGREEN_GRPH_LUT_10BIT_BYPASS_CONTROL         0x1a02
#घोषणा EVERGREEN_LUT_10BIT_BYPASS_EN            (1 << 8)

#घोषणा EVERGREEN_GRPH_PITCH                            0x1a06
#घोषणा EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH     0x1a07
#घोषणा EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS_HIGH   0x1a08
#घोषणा EVERGREEN_GRPH_SURFACE_OFFSET_X                 0x1a09
#घोषणा EVERGREEN_GRPH_SURFACE_OFFSET_Y                 0x1a0a
#घोषणा EVERGREEN_GRPH_X_START                          0x1a0b
#घोषणा EVERGREEN_GRPH_Y_START                          0x1a0c
#घोषणा EVERGREEN_GRPH_X_END                            0x1a0d
#घोषणा EVERGREEN_GRPH_Y_END                            0x1a0e
#घोषणा EVERGREEN_GRPH_UPDATE                           0x1a11
#घोषणा EVERGREEN_GRPH_SURFACE_UPDATE_PENDING    (1 << 2)
#घोषणा EVERGREEN_GRPH_UPDATE_LOCK               (1 << 16)
#घोषणा EVERGREEN_GRPH_FLIP_CONTROL                     0x1a12
#घोषणा EVERGREEN_GRPH_SURFACE_UPDATE_H_RETRACE_EN (1 << 0)

#घोषणा EVERGREEN_VIEWPORT_START                        0x1b5c
#घोषणा EVERGREEN_VIEWPORT_SIZE                         0x1b5d
#घोषणा EVERGREEN_DESKTOP_HEIGHT                        0x1ac1

/* CUR blocks at 0x6998, 0x7598, 0x10198, 0x10d98, 0x11998, 0x12598 */
#घोषणा EVERGREEN_CUR_CONTROL                           0x1a66
#       define EVERGREEN_CURSOR_EN                      (1 << 0)
#       define EVERGREEN_CURSOR_MODE(x)                 (((x) & 0x3) << 8)
#       define EVERGREEN_CURSOR_MONO                    0
#       define EVERGREEN_CURSOR_24_1                    1
#       define EVERGREEN_CURSOR_24_8_PRE_MULT           2
#       define EVERGREEN_CURSOR_24_8_UNPRE_MULT         3
#       define EVERGREEN_CURSOR_2X_MAGNIFY              (1 << 16)
#       define EVERGREEN_CURSOR_FORCE_MC_ON             (1 << 20)
#       define EVERGREEN_CURSOR_URGENT_CONTROL(x)       (((x) & 0x7) << 24)
#       define EVERGREEN_CURSOR_URGENT_ALWAYS           0
#       define EVERGREEN_CURSOR_URGENT_1_8              1
#       define EVERGREEN_CURSOR_URGENT_1_4              2
#       define EVERGREEN_CURSOR_URGENT_3_8              3
#       define EVERGREEN_CURSOR_URGENT_1_2              4
#घोषणा EVERGREEN_CUR_SURFACE_ADDRESS                   0x1a67
#       define EVERGREEN_CUR_SURFACE_ADDRESS_MASK       0xfffff000
#घोषणा EVERGREEN_CUR_SIZE                              0x1a68
#घोषणा EVERGREEN_CUR_SURFACE_ADDRESS_HIGH              0x1a69
#घोषणा EVERGREEN_CUR_POSITION                          0x1a6a
#घोषणा EVERGREEN_CUR_HOT_SPOT                          0x1a6b
#घोषणा EVERGREEN_CUR_COLOR1                            0x1a6c
#घोषणा EVERGREEN_CUR_COLOR2                            0x1a6d
#घोषणा EVERGREEN_CUR_UPDATE                            0x1a6e
#       define EVERGREEN_CURSOR_UPDATE_PENDING          (1 << 0)
#       define EVERGREEN_CURSOR_UPDATE_TAKEN            (1 << 1)
#       define EVERGREEN_CURSOR_UPDATE_LOCK             (1 << 16)
#       define EVERGREEN_CURSOR_DISABLE_MULTIPLE_UPDATE (1 << 24)


#घोषणा NI_INPUT_CSC_CONTROL                           0x1a35
#       define NI_INPUT_CSC_GRPH_MODE(x)               (((x) & 0x3) << 0)
#       define NI_INPUT_CSC_BYPASS                     0
#       define NI_INPUT_CSC_PROG_COEFF                 1
#       define NI_INPUT_CSC_PROG_SHARED_MATRIXA        2
#       define NI_INPUT_CSC_OVL_MODE(x)                (((x) & 0x3) << 4)

#घोषणा NI_OUTPUT_CSC_CONTROL                          0x1a3c
#       define NI_OUTPUT_CSC_GRPH_MODE(x)              (((x) & 0x7) << 0)
#       define NI_OUTPUT_CSC_BYPASS                    0
#       define NI_OUTPUT_CSC_TV_RGB                    1
#       define NI_OUTPUT_CSC_YCBCR_601                 2
#       define NI_OUTPUT_CSC_YCBCR_709                 3
#       define NI_OUTPUT_CSC_PROG_COEFF                4
#       define NI_OUTPUT_CSC_PROG_SHARED_MATRIXB       5
#       define NI_OUTPUT_CSC_OVL_MODE(x)               (((x) & 0x7) << 4)

#घोषणा NI_DEGAMMA_CONTROL                             0x1a58
#       define NI_GRPH_DEGAMMA_MODE(x)                 (((x) & 0x3) << 0)
#       define NI_DEGAMMA_BYPASS                       0
#       define NI_DEGAMMA_SRGB_24                      1
#       define NI_DEGAMMA_XVYCC_222                    2
#       define NI_OVL_DEGAMMA_MODE(x)                  (((x) & 0x3) << 4)
#       define NI_ICON_DEGAMMA_MODE(x)                 (((x) & 0x3) << 8)
#       define NI_CURSOR_DEGAMMA_MODE(x)               (((x) & 0x3) << 12)

#घोषणा NI_GAMUT_REMAP_CONTROL                         0x1a59
#       define NI_GRPH_GAMUT_REMAP_MODE(x)             (((x) & 0x3) << 0)
#       define NI_GAMUT_REMAP_BYPASS                   0
#       define NI_GAMUT_REMAP_PROG_COEFF               1
#       define NI_GAMUT_REMAP_PROG_SHARED_MATRIXA      2
#       define NI_GAMUT_REMAP_PROG_SHARED_MATRIXB      3
#       define NI_OVL_GAMUT_REMAP_MODE(x)              (((x) & 0x3) << 4)

#घोषणा NI_REGAMMA_CONTROL                             0x1aa0
#       define NI_GRPH_REGAMMA_MODE(x)                 (((x) & 0x7) << 0)
#       define NI_REGAMMA_BYPASS                       0
#       define NI_REGAMMA_SRGB_24                      1
#       define NI_REGAMMA_XVYCC_222                    2
#       define NI_REGAMMA_PROG_A                       3
#       define NI_REGAMMA_PROG_B                       4
#       define NI_OVL_REGAMMA_MODE(x)                  (((x) & 0x7) << 4)


#घोषणा NI_PRESCALE_GRPH_CONTROL                       0x1a2d
#       define NI_GRPH_PRESCALE_BYPASS                 (1 << 4)

#घोषणा NI_PRESCALE_OVL_CONTROL                        0x1a31
#       define NI_OVL_PRESCALE_BYPASS                  (1 << 4)

#घोषणा NI_INPUT_GAMMA_CONTROL                         0x1a10
#       define NI_GRPH_INPUT_GAMMA_MODE(x)             (((x) & 0x3) << 0)
#       define NI_INPUT_GAMMA_USE_LUT                  0
#       define NI_INPUT_GAMMA_BYPASS                   1
#       define NI_INPUT_GAMMA_SRGB_24                  2
#       define NI_INPUT_GAMMA_XVYCC_222                3
#       define NI_OVL_INPUT_GAMMA_MODE(x)              (((x) & 0x3) << 4)

#घोषणा	BLACKOUT_MODE_MASK			0x00000007
#घोषणा	VGA_RENDER_CONTROL			0xC0
#घोषणा R_000300_VGA_RENDER_CONTROL             0xC0
#घोषणा C_000300_VGA_VSTATUS_CNTL               0xFFFCFFFF
#घोषणा EVERGREEN_CRTC_STATUS                   0x1BA3
#घोषणा EVERGREEN_CRTC_V_BLANK                  (1 << 0)
#घोषणा EVERGREEN_CRTC_STATUS_POSITION          0x1BA4
/* CRTC blocks at 0x6df0, 0x79f0, 0x105f0, 0x111f0, 0x11df0, 0x129f0 */
#घोषणा EVERGREEN_CRTC_V_BLANK_START_END                0x1b8d
#घोषणा EVERGREEN_CRTC_CONTROL                          0x1b9c
#       define EVERGREEN_CRTC_MASTER_EN                 (1 << 0)
#       define EVERGREEN_CRTC_DISP_READ_REQUEST_DISABLE (1 << 24)
#घोषणा EVERGREEN_CRTC_BLANK_CONTROL                    0x1b9d
#       define EVERGREEN_CRTC_BLANK_DATA_EN             (1 << 8)
#       define EVERGREEN_CRTC_V_BLANK                   (1 << 0)
#घोषणा EVERGREEN_CRTC_STATUS_HV_COUNT                  0x1ba8
#घोषणा EVERGREEN_CRTC_UPDATE_LOCK                      0x1bb5
#घोषणा EVERGREEN_MASTER_UPDATE_LOCK                    0x1bbd
#घोषणा EVERGREEN_MASTER_UPDATE_MODE                    0x1bbe
#घोषणा EVERGREEN_GRPH_UPDATE_LOCK               (1 << 16)
#घोषणा EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH     0x1a07
#घोषणा EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS_HIGH   0x1a08
#घोषणा EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS          0x1a04
#घोषणा EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS        0x1a05
#घोषणा EVERGREEN_GRPH_UPDATE                           0x1a11
#घोषणा EVERGREEN_VGA_MEMORY_BASE_ADDRESS               0xc4
#घोषणा EVERGREEN_VGA_MEMORY_BASE_ADDRESS_HIGH          0xc9
#घोषणा EVERGREEN_GRPH_SURFACE_UPDATE_PENDING    (1 << 2)

#घोषणा mmVM_CONTEXT1_CNTL__xxRANGE_PROTECTION_FAULT_ENABLE_DEFAULT_MASK 0x10
#घोषणा mmVM_CONTEXT1_CNTL__xxRANGE_PROTECTION_FAULT_ENABLE_DEFAULT__SHIFT 0x4
#घोषणा mmVM_CONTEXT1_CNTL__xxDUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT_MASK 0x80
#घोषणा mmVM_CONTEXT1_CNTL__xxDUMMY_PAGE_PROTECTION_FAULT_ENABLE_DEFAULT__SHIFT 0x7
#घोषणा mmVM_CONTEXT1_CNTL__xxPDE0_PROTECTION_FAULT_ENABLE_DEFAULT_MASK 0x400
#घोषणा mmVM_CONTEXT1_CNTL__xxPDE0_PROTECTION_FAULT_ENABLE_DEFAULT__SHIFT 0xa
#घोषणा mmVM_CONTEXT1_CNTL__xxVALID_PROTECTION_FAULT_ENABLE_DEFAULT_MASK 0x2000
#घोषणा mmVM_CONTEXT1_CNTL__xxVALID_PROTECTION_FAULT_ENABLE_DEFAULT__SHIFT 0xd
#घोषणा mmVM_CONTEXT1_CNTL__xxREAD_PROTECTION_FAULT_ENABLE_DEFAULT_MASK 0x10000
#घोषणा mmVM_CONTEXT1_CNTL__xxREAD_PROTECTION_FAULT_ENABLE_DEFAULT__SHIFT 0x10
#घोषणा mmVM_CONTEXT1_CNTL__xxWRITE_PROTECTION_FAULT_ENABLE_DEFAULT_MASK 0x80000
#घोषणा mmVM_CONTEXT1_CNTL__xxWRITE_PROTECTION_FAULT_ENABLE_DEFAULT__SHIFT 0x13

#घोषणा mmVM_CONTEXT1_PROTECTION_FAULT_STATUS__xxVMID_MASK 0x1e000000
#घोषणा mmVM_CONTEXT1_PROTECTION_FAULT_STATUS__xxVMID__SHIFT 0x19
#घोषणा mmVM_CONTEXT1_PROTECTION_FAULT_STATUS__xxPROTECTIONS_MASK 0xff
#घोषणा mmVM_CONTEXT1_PROTECTION_FAULT_STATUS__xxPROTECTIONS__SHIFT 0x0
#घोषणा mmVM_CONTEXT1_PROTECTION_FAULT_STATUS__xxMEMORY_CLIENT_ID_MASK 0xff000
#घोषणा mmVM_CONTEXT1_PROTECTION_FAULT_STATUS__xxMEMORY_CLIENT_ID__SHIFT 0xc
#घोषणा mmVM_CONTEXT1_PROTECTION_FAULT_STATUS__xxMEMORY_CLIENT_RW_MASK 0x1000000
#घोषणा mmVM_CONTEXT1_PROTECTION_FAULT_STATUS__xxMEMORY_CLIENT_RW__SHIFT 0x18

#घोषणा mmMC_SHARED_BLACKOUT_CNTL__xxBLACKOUT_MODE_MASK 0x7
#घोषणा mmMC_SHARED_BLACKOUT_CNTL__xxBLACKOUT_MODE__SHIFT 0x0

#घोषणा mmBIF_FB_EN__xxFB_READ_EN_MASK 0x1
#घोषणा mmBIF_FB_EN__xxFB_READ_EN__SHIFT 0x0
#घोषणा mmBIF_FB_EN__xxFB_WRITE_EN_MASK 0x2
#घोषणा mmBIF_FB_EN__xxFB_WRITE_EN__SHIFT 0x1

#घोषणा mmSRBM_SOFT_RESET__xxSOFT_RESET_VMC_MASK 0x20000
#घोषणा mmSRBM_SOFT_RESET__xxSOFT_RESET_VMC__SHIFT 0x11
#घोषणा mmSRBM_SOFT_RESET__xxSOFT_RESET_MC_MASK 0x800
#घोषणा mmSRBM_SOFT_RESET__xxSOFT_RESET_MC__SHIFT 0xb

#घोषणा VM_CONTEXT1_CNTL__RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK 0x8
#घोषणा VM_CONTEXT1_CNTL__RANGE_PROTECTION_FAULT_ENABLE_INTERRUPT__SHIFT 0x3
#घोषणा VM_CONTEXT1_CNTL__DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK 0x40
#घोषणा VM_CONTEXT1_CNTL__DUMMY_PAGE_PROTECTION_FAULT_ENABLE_INTERRUPT__SHIFT 0x6
#घोषणा VM_CONTEXT1_CNTL__PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK 0x200
#घोषणा VM_CONTEXT1_CNTL__PDE0_PROTECTION_FAULT_ENABLE_INTERRUPT__SHIFT 0x9
#घोषणा VM_CONTEXT1_CNTL__VALID_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK 0x1000
#घोषणा VM_CONTEXT1_CNTL__VALID_PROTECTION_FAULT_ENABLE_INTERRUPT__SHIFT 0xc
#घोषणा VM_CONTEXT1_CNTL__READ_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK 0x8000
#घोषणा VM_CONTEXT1_CNTL__READ_PROTECTION_FAULT_ENABLE_INTERRUPT__SHIFT 0xf
#घोषणा VM_CONTEXT1_CNTL__WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT_MASK 0x40000
#घोषणा VM_CONTEXT1_CNTL__WRITE_PROTECTION_FAULT_ENABLE_INTERRUPT__SHIFT 0x12

#घोषणा MC_SEQ_MISC0__MT__MASK	0xf0000000
#घोषणा MC_SEQ_MISC0__MT__GDDR1  0x10000000
#घोषणा MC_SEQ_MISC0__MT__DDR2   0x20000000
#घोषणा MC_SEQ_MISC0__MT__GDDR3  0x30000000
#घोषणा MC_SEQ_MISC0__MT__GDDR4  0x40000000
#घोषणा MC_SEQ_MISC0__MT__GDDR5  0x50000000
#घोषणा MC_SEQ_MISC0__MT__HBM    0x60000000
#घोषणा MC_SEQ_MISC0__MT__DDR3   0xB0000000

#घोषणा GRBM_STATUS__GUI_ACTIVE_MASK 0x80000000
#घोषणा CP_INT_CNTL_RING__TIME_STAMP_INT_ENABLE_MASK 0x4000000
#घोषणा CP_INT_CNTL_RING0__PRIV_REG_INT_ENABLE_MASK 0x800000
#घोषणा CP_INT_CNTL_RING0__PRIV_INSTR_INT_ENABLE_MASK 0x400000
#घोषणा PACKET3_SEM_WAIT_ON_SIGNAL    (0x1 << 12)
#घोषणा PACKET3_SEM_SEL_SIGNAL	    (0x6 << 29)
#घोषणा PACKET3_SEM_SEL_WAIT	    (0x7 << 29)

#घोषणा CONFIG_CNTL	0x1509
#घोषणा CC_DRM_ID_STRAPS	0X1559
#घोषणा AMDGPU_PCIE_INDEX	0xc
#घोषणा AMDGPU_PCIE_DATA	0xd

#घोषणा DMA_SEM_INCOMPLETE_TIMER_CNTL                     0x3411
#घोषणा DMA_SEM_WAIT_FAIL_TIMER_CNTL                      0x3412
#घोषणा DMA_MODE                                          0x342f
#घोषणा DMA_RB_RPTR_ADDR_HI                               0x3407
#घोषणा DMA_RB_RPTR_ADDR_LO                               0x3408
#घोषणा DMA_BUSY_MASK 0x20
#घोषणा DMA1_BUSY_MASK 0X40
#घोषणा SDMA_MAX_INSTANCE 2

#घोषणा PCIE_BUS_CLK    10000
#घोषणा TCLK            (PCIE_BUS_CLK / 10)
#घोषणा	PCIE_PORT_INDEX					0xe
#घोषणा	PCIE_PORT_DATA					0xf
#घोषणा EVERGREEN_PIF_PHY0_INDEX                        0x8
#घोषणा EVERGREEN_PIF_PHY0_DATA                         0xc
#घोषणा EVERGREEN_PIF_PHY1_INDEX                        0x10
#घोषणा EVERGREEN_PIF_PHY1_DATA				0x14

#घोषणा	MC_VM_FB_OFFSET					0x81a

/* Discrete VCE घड़ीs */
#घोषणा CG_VCEPLL_FUNC_CNTL                             0xc0030600
#घोषणा    VCEPLL_RESET_MASK                            0x00000001
#घोषणा    VCEPLL_SLEEP_MASK                            0x00000002
#घोषणा    VCEPLL_BYPASS_EN_MASK                        0x00000004
#घोषणा    VCEPLL_CTLREQ_MASK                           0x00000008
#घोषणा    VCEPLL_VCO_MODE_MASK                         0x00000600
#घोषणा    VCEPLL_REF_DIV_MASK                          0x003F0000
#घोषणा    VCEPLL_CTLACK_MASK                           0x40000000
#घोषणा    VCEPLL_CTLACK2_MASK                          0x80000000

#घोषणा CG_VCEPLL_FUNC_CNTL_2                           0xc0030601
#घोषणा    VCEPLL_PDIV_A(x)                             ((x) << 0)
#घोषणा    VCEPLL_PDIV_A_MASK                           0x0000007F
#घोषणा    VCEPLL_PDIV_B(x)                             ((x) << 8)
#घोषणा    VCEPLL_PDIV_B_MASK                           0x00007F00
#घोषणा    EVCLK_SRC_SEL(x)                             ((x) << 20)
#घोषणा    EVCLK_SRC_SEL_MASK                           0x01F00000
#घोषणा    ECCLK_SRC_SEL(x)                             ((x) << 25)
#घोषणा    ECCLK_SRC_SEL_MASK                           0x3E000000

#घोषणा CG_VCEPLL_FUNC_CNTL_3                           0xc0030602
#घोषणा    VCEPLL_FB_DIV(x)                             ((x) << 0)
#घोषणा    VCEPLL_FB_DIV_MASK                           0x01FFFFFF

#घोषणा CG_VCEPLL_FUNC_CNTL_4                           0xc0030603

#घोषणा CG_VCEPLL_FUNC_CNTL_5                           0xc0030604
#घोषणा CG_VCEPLL_SPREAD_SPECTRUM                       0xc0030606
#घोषणा    VCEPLL_SSEN_MASK                             0x00000001


#पूर्ण_अगर
