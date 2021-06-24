<शैली गुरु>
/*
 * Copyright 2010 Advanced Micro Devices, Inc.
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
#अगर_अघोषित EVERGREEND_H
#घोषणा EVERGREEND_H

#घोषणा EVERGREEN_MAX_SH_GPRS           256
#घोषणा EVERGREEN_MAX_TEMP_GPRS         16
#घोषणा EVERGREEN_MAX_SH_THREADS        256
#घोषणा EVERGREEN_MAX_SH_STACK_ENTRIES  4096
#घोषणा EVERGREEN_MAX_FRC_EOV_CNT       16384
#घोषणा EVERGREEN_MAX_BACKENDS          8
#घोषणा EVERGREEN_MAX_BACKENDS_MASK     0xFF
#घोषणा EVERGREEN_MAX_SIMDS             16
#घोषणा EVERGREEN_MAX_SIMDS_MASK        0xFFFF
#घोषणा EVERGREEN_MAX_PIPES             8
#घोषणा EVERGREEN_MAX_PIPES_MASK        0xFF
#घोषणा EVERGREEN_MAX_LDS_NUM           0xFFFF

#घोषणा CYPRESS_GB_ADDR_CONFIG_GOLDEN        0x02011003
#घोषणा BARTS_GB_ADDR_CONFIG_GOLDEN          0x02011003
#घोषणा CAYMAN_GB_ADDR_CONFIG_GOLDEN         0x02011003
#घोषणा JUNIPER_GB_ADDR_CONFIG_GOLDEN        0x02010002
#घोषणा REDWOOD_GB_ADDR_CONFIG_GOLDEN        0x02010002
#घोषणा TURKS_GB_ADDR_CONFIG_GOLDEN          0x02010002
#घोषणा CEDAR_GB_ADDR_CONFIG_GOLDEN          0x02010001
#घोषणा CAICOS_GB_ADDR_CONFIG_GOLDEN         0x02010001
#घोषणा SUMO_GB_ADDR_CONFIG_GOLDEN           0x02010002
#घोषणा SUMO2_GB_ADDR_CONFIG_GOLDEN          0x02010002

/* pm रेजिस्टरs */
#घोषणा	SMC_MSG						0x20c
#घोषणा		HOST_SMC_MSG(x)				((x) << 0)
#घोषणा		HOST_SMC_MSG_MASK			(0xff << 0)
#घोषणा		HOST_SMC_MSG_SHIFT			0
#घोषणा		HOST_SMC_RESP(x)			((x) << 8)
#घोषणा		HOST_SMC_RESP_MASK			(0xff << 8)
#घोषणा		HOST_SMC_RESP_SHIFT			8
#घोषणा		SMC_HOST_MSG(x)				((x) << 16)
#घोषणा		SMC_HOST_MSG_MASK			(0xff << 16)
#घोषणा		SMC_HOST_MSG_SHIFT			16
#घोषणा		SMC_HOST_RESP(x)			((x) << 24)
#घोषणा		SMC_HOST_RESP_MASK			(0xff << 24)
#घोषणा		SMC_HOST_RESP_SHIFT			24

#घोषणा DCCG_DISP_SLOW_SELECT_REG                       0x4fc
#घोषणा		DCCG_DISP1_SLOW_SELECT(x)		((x) << 0)
#घोषणा		DCCG_DISP1_SLOW_SELECT_MASK		(7 << 0)
#घोषणा		DCCG_DISP1_SLOW_SELECT_SHIFT		0
#घोषणा		DCCG_DISP2_SLOW_SELECT(x)		((x) << 4)
#घोषणा		DCCG_DISP2_SLOW_SELECT_MASK		(7 << 4)
#घोषणा		DCCG_DISP2_SLOW_SELECT_SHIFT		4

#घोषणा	CG_SPLL_FUNC_CNTL				0x600
#घोषणा		SPLL_RESET				(1 << 0)
#घोषणा		SPLL_SLEEP				(1 << 1)
#घोषणा		SPLL_BYPASS_EN				(1 << 3)
#घोषणा		SPLL_REF_DIV(x)				((x) << 4)
#घोषणा		SPLL_REF_DIV_MASK			(0x3f << 4)
#घोषणा		SPLL_PDIV_A(x)				((x) << 20)
#घोषणा		SPLL_PDIV_A_MASK			(0x7f << 20)
#घोषणा	CG_SPLL_FUNC_CNTL_2				0x604
#घोषणा		SCLK_MUX_SEL(x)				((x) << 0)
#घोषणा		SCLK_MUX_SEL_MASK			(0x1ff << 0)
#घोषणा		SCLK_MUX_UPDATE				(1 << 26)
#घोषणा	CG_SPLL_FUNC_CNTL_3				0x608
#घोषणा		SPLL_FB_DIV(x)				((x) << 0)
#घोषणा		SPLL_FB_DIV_MASK			(0x3ffffff << 0)
#घोषणा		SPLL_DITHEN				(1 << 28)
#घोषणा	CG_SPLL_STATUS					0x60c
#घोषणा		SPLL_CHG_STATUS				(1 << 1)

#घोषणा MPLL_CNTL_MODE                                  0x61c
#       define MPLL_MCLK_SEL                            (1 << 11)
#       define SS_SSEN                                  (1 << 24)
#       define SS_DSMODE_EN                             (1 << 25)

#घोषणा	MPLL_AD_FUNC_CNTL				0x624
#घोषणा		CLKF(x)					((x) << 0)
#घोषणा		CLKF_MASK				(0x7f << 0)
#घोषणा		CLKR(x)					((x) << 7)
#घोषणा		CLKR_MASK				(0x1f << 7)
#घोषणा		CLKFRAC(x)				((x) << 12)
#घोषणा		CLKFRAC_MASK				(0x1f << 12)
#घोषणा		YCLK_POST_DIV(x)			((x) << 17)
#घोषणा		YCLK_POST_DIV_MASK			(3 << 17)
#घोषणा		IBIAS(x)				((x) << 20)
#घोषणा		IBIAS_MASK				(0x3ff << 20)
#घोषणा		RESET					(1 << 30)
#घोषणा		PDNB					(1 << 31)
#घोषणा	MPLL_AD_FUNC_CNTL_2				0x628
#घोषणा		BYPASS					(1 << 19)
#घोषणा		BIAS_GEN_PDNB				(1 << 24)
#घोषणा		RESET_EN				(1 << 25)
#घोषणा		VCO_MODE				(1 << 29)
#घोषणा	MPLL_DQ_FUNC_CNTL				0x62c
#घोषणा	MPLL_DQ_FUNC_CNTL_2				0x630

#घोषणा GENERAL_PWRMGT                                  0x63c
#       define GLOBAL_PWRMGT_EN                         (1 << 0)
#       define STATIC_PM_EN                             (1 << 1)
#       define THERMAL_PROTECTION_DIS                   (1 << 2)
#       define THERMAL_PROTECTION_TYPE                  (1 << 3)
#       define ENABLE_GEN2PCIE                          (1 << 4)
#       define ENABLE_GEN2XSP                           (1 << 5)
#       define SW_SMIO_INDEX(x)                         ((x) << 6)
#       define SW_SMIO_INDEX_MASK                       (3 << 6)
#       define SW_SMIO_INDEX_SHIFT                      6
#       define LOW_VOLT_D2_ACPI                         (1 << 8)
#       define LOW_VOLT_D3_ACPI                         (1 << 9)
#       define VOLT_PWRMGT_EN                           (1 << 10)
#       define BACKBIAS_PAD_EN                          (1 << 18)
#       define BACKBIAS_VALUE                           (1 << 19)
#       define DYN_SPREAD_SPECTRUM_EN                   (1 << 23)
#       define AC_DC_SW                                 (1 << 24)

#घोषणा SCLK_PWRMGT_CNTL                                  0x644
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
#घोषणा	MCLK_PWRMGT_CNTL				0x648
#       define DLL_SPEED(x)				((x) << 0)
#       define DLL_SPEED_MASK				(0x1f << 0)
#       define MPLL_PWRMGT_OFF                          (1 << 5)
#       define DLL_READY                                (1 << 6)
#       define MC_INT_CNTL                              (1 << 7)
#       define MRDCKA0_PDNB                             (1 << 8)
#       define MRDCKA1_PDNB                             (1 << 9)
#       define MRDCKB0_PDNB                             (1 << 10)
#       define MRDCKB1_PDNB                             (1 << 11)
#       define MRDCKC0_PDNB                             (1 << 12)
#       define MRDCKC1_PDNB                             (1 << 13)
#       define MRDCKD0_PDNB                             (1 << 14)
#       define MRDCKD1_PDNB                             (1 << 15)
#       define MRDCKA0_RESET                            (1 << 16)
#       define MRDCKA1_RESET                            (1 << 17)
#       define MRDCKB0_RESET                            (1 << 18)
#       define MRDCKB1_RESET                            (1 << 19)
#       define MRDCKC0_RESET                            (1 << 20)
#       define MRDCKC1_RESET                            (1 << 21)
#       define MRDCKD0_RESET                            (1 << 22)
#       define MRDCKD1_RESET                            (1 << 23)
#       define DLL_READY_READ                           (1 << 24)
#       define USE_DISPLAY_GAP                          (1 << 25)
#       define USE_DISPLAY_URGENT_NORMAL                (1 << 26)
#       define MPLL_TURNOFF_D2                          (1 << 28)
#घोषणा	DLL_CNTL					0x64c
#       define MRDCKA0_BYPASS                           (1 << 24)
#       define MRDCKA1_BYPASS                           (1 << 25)
#       define MRDCKB0_BYPASS                           (1 << 26)
#       define MRDCKB1_BYPASS                           (1 << 27)
#       define MRDCKC0_BYPASS                           (1 << 28)
#       define MRDCKC1_BYPASS                           (1 << 29)
#       define MRDCKD0_BYPASS                           (1 << 30)
#       define MRDCKD1_BYPASS                           (1 << 31)

#घोषणा CG_AT                                           0x6d4
#       define CG_R(x)					((x) << 0)
#       define CG_R_MASK				(0xffff << 0)
#       define CG_L(x)					((x) << 16)
#       define CG_L_MASK				(0xffff << 16)

#घोषणा CG_DISPLAY_GAP_CNTL                               0x714
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

#घोषणा	CG_BIF_REQ_AND_RSP				0x7f4
#घोषणा		CG_CLIENT_REQ(x)			((x) << 0)
#घोषणा		CG_CLIENT_REQ_MASK			(0xff << 0)
#घोषणा		CG_CLIENT_REQ_SHIFT			0
#घोषणा		CG_CLIENT_RESP(x)			((x) << 8)
#घोषणा		CG_CLIENT_RESP_MASK			(0xff << 8)
#घोषणा		CG_CLIENT_RESP_SHIFT			8
#घोषणा		CLIENT_CG_REQ(x)			((x) << 16)
#घोषणा		CLIENT_CG_REQ_MASK			(0xff << 16)
#घोषणा		CLIENT_CG_REQ_SHIFT			16
#घोषणा		CLIENT_CG_RESP(x)			((x) << 24)
#घोषणा		CLIENT_CG_RESP_MASK			(0xff << 24)
#घोषणा		CLIENT_CG_RESP_SHIFT			24

#घोषणा	CG_SPLL_SPREAD_SPECTRUM				0x790
#घोषणा		SSEN					(1 << 0)
#घोषणा	CG_SPLL_SPREAD_SPECTRUM_2			0x794

#घोषणा	MPLL_SS1					0x85c
#घोषणा		CLKV(x)					((x) << 0)
#घोषणा		CLKV_MASK				(0x3ffffff << 0)
#घोषणा	MPLL_SS2					0x860
#घोषणा		CLKS(x)					((x) << 0)
#घोषणा		CLKS_MASK				(0xfff << 0)

#घोषणा	CG_IND_ADDR					0x8f8
#घोषणा	CG_IND_DATA					0x8fc
/* CGIND regs */
#घोषणा	CG_CGTT_LOCAL_0					0x00
#घोषणा	CG_CGTT_LOCAL_1					0x01
#घोषणा	CG_CGTT_LOCAL_2					0x02
#घोषणा	CG_CGTT_LOCAL_3					0x03
#घोषणा	CG_CGLS_TILE_0					0x20
#घोषणा	CG_CGLS_TILE_1					0x21
#घोषणा	CG_CGLS_TILE_2					0x22
#घोषणा	CG_CGLS_TILE_3					0x23
#घोषणा	CG_CGLS_TILE_4					0x24
#घोषणा	CG_CGLS_TILE_5					0x25
#घोषणा	CG_CGLS_TILE_6					0x26
#घोषणा	CG_CGLS_TILE_7					0x27
#घोषणा	CG_CGLS_TILE_8					0x28
#घोषणा	CG_CGLS_TILE_9					0x29
#घोषणा	CG_CGLS_TILE_10					0x2a
#घोषणा	CG_CGLS_TILE_11					0x2b

#घोषणा VM_L2_CG                                        0x15c0

#घोषणा MC_CONFIG                                       0x2000

#घोषणा MC_CONFIG_MCD                                   0x20a0
#घोषणा MC_CG_CONFIG_MCD                                0x20a4
#घोषणा		MC_RD_ENABLE_MCD(x)			((x) << 8)
#घोषणा		MC_RD_ENABLE_MCD_MASK			(7 << 8)

#घोषणा MC_HUB_MISC_HUB_CG                              0x20b8
#घोषणा MC_HUB_MISC_VM_CG                               0x20bc
#घोषणा MC_HUB_MISC_SIP_CG                              0x20c0

#घोषणा MC_XPB_CLK_GAT                                  0x2478

#घोषणा MC_CG_CONFIG                                    0x25bc
#घोषणा		MC_RD_ENABLE(x)				((x) << 4)
#घोषणा		MC_RD_ENABLE_MASK			(3 << 4)

#घोषणा MC_CITF_MISC_RD_CG                              0x2648
#घोषणा MC_CITF_MISC_WR_CG                              0x264c
#घोषणा MC_CITF_MISC_VM_CG                              0x2650
#       define MEM_LS_ENABLE                            (1 << 19)

#घोषणा MC_ARB_BURST_TIME                               0x2808
#घोषणा		STATE0(x)				((x) << 0)
#घोषणा		STATE0_MASK				(0x1f << 0)
#घोषणा		STATE1(x)				((x) << 5)
#घोषणा		STATE1_MASK				(0x1f << 5)
#घोषणा		STATE2(x)				((x) << 10)
#घोषणा		STATE2_MASK				(0x1f << 10)
#घोषणा		STATE3(x)				((x) << 15)
#घोषणा		STATE3_MASK				(0x1f << 15)

#घोषणा MC_SEQ_RAS_TIMING                               0x28a0
#घोषणा MC_SEQ_CAS_TIMING                               0x28a4
#घोषणा MC_SEQ_MISC_TIMING                              0x28a8
#घोषणा MC_SEQ_MISC_TIMING2                             0x28ac

#घोषणा MC_SEQ_RD_CTL_D0                                0x28b4
#घोषणा MC_SEQ_RD_CTL_D1                                0x28b8
#घोषणा MC_SEQ_WR_CTL_D0                                0x28bc
#घोषणा MC_SEQ_WR_CTL_D1                                0x28c0

#घोषणा MC_SEQ_STATUS_M                                 0x29f4
#       define PMG_PWRSTATE                             (1 << 16)

#घोषणा MC_SEQ_MISC1                                    0x2a04
#घोषणा MC_SEQ_RESERVE_M                                0x2a08
#घोषणा MC_PMG_CMD_EMRS                                 0x2a0c

#घोषणा MC_SEQ_MISC3                                    0x2a2c

#घोषणा MC_SEQ_MISC5                                    0x2a54
#घोषणा MC_SEQ_MISC6                                    0x2a58

#घोषणा MC_SEQ_MISC7                                    0x2a64

#घोषणा MC_SEQ_CG                                       0x2a68
#घोषणा		CG_SEQ_REQ(x)				((x) << 0)
#घोषणा		CG_SEQ_REQ_MASK				(0xff << 0)
#घोषणा		CG_SEQ_REQ_SHIFT			0
#घोषणा		CG_SEQ_RESP(x)				((x) << 8)
#घोषणा		CG_SEQ_RESP_MASK			(0xff << 8)
#घोषणा		CG_SEQ_RESP_SHIFT			8
#घोषणा		SEQ_CG_REQ(x)				((x) << 16)
#घोषणा		SEQ_CG_REQ_MASK				(0xff << 16)
#घोषणा		SEQ_CG_REQ_SHIFT			16
#घोषणा		SEQ_CG_RESP(x)				((x) << 24)
#घोषणा		SEQ_CG_RESP_MASK			(0xff << 24)
#घोषणा		SEQ_CG_RESP_SHIFT			24
#घोषणा MC_SEQ_RAS_TIMING_LP                            0x2a6c
#घोषणा MC_SEQ_CAS_TIMING_LP                            0x2a70
#घोषणा MC_SEQ_MISC_TIMING_LP                           0x2a74
#घोषणा MC_SEQ_MISC_TIMING2_LP                          0x2a78
#घोषणा MC_SEQ_WR_CTL_D0_LP                             0x2a7c
#घोषणा MC_SEQ_WR_CTL_D1_LP                             0x2a80
#घोषणा MC_SEQ_PMG_CMD_EMRS_LP                          0x2a84
#घोषणा MC_SEQ_PMG_CMD_MRS_LP                           0x2a88

#घोषणा MC_PMG_CMD_MRS                                  0x2aac

#घोषणा MC_SEQ_RD_CTL_D0_LP                             0x2b1c
#घोषणा MC_SEQ_RD_CTL_D1_LP                             0x2b20

#घोषणा MC_PMG_CMD_MRS1                                 0x2b44
#घोषणा MC_SEQ_PMG_CMD_MRS1_LP                          0x2b48

#घोषणा CGTS_SM_CTRL_REG                                0x9150

/* Registers */

#घोषणा RCU_IND_INDEX           			0x100
#घोषणा RCU_IND_DATA            			0x104

/* discrete uvd घड़ीs */
#घोषणा CG_UPLL_FUNC_CNTL				0x718
#	define UPLL_RESET_MASK				0x00000001
#	define UPLL_SLEEP_MASK				0x00000002
#	define UPLL_BYPASS_EN_MASK			0x00000004
#	define UPLL_CTLREQ_MASK				0x00000008
#	define UPLL_REF_DIV_MASK			0x003F0000
#	define UPLL_VCO_MODE_MASK			0x00000200
#	define UPLL_CTLACK_MASK				0x40000000
#	define UPLL_CTLACK2_MASK			0x80000000
#घोषणा CG_UPLL_FUNC_CNTL_2				0x71c
#	define UPLL_PDIV_A(x)				((x) << 0)
#	define UPLL_PDIV_A_MASK				0x0000007F
#	define UPLL_PDIV_B(x)				((x) << 8)
#	define UPLL_PDIV_B_MASK				0x00007F00
#	define VCLK_SRC_SEL(x)				((x) << 20)
#	define VCLK_SRC_SEL_MASK			0x01F00000
#	define DCLK_SRC_SEL(x)				((x) << 25)
#	define DCLK_SRC_SEL_MASK			0x3E000000
#घोषणा CG_UPLL_FUNC_CNTL_3				0x720
#	define UPLL_FB_DIV(x)				((x) << 0)
#	define UPLL_FB_DIV_MASK				0x01FFFFFF
#घोषणा CG_UPLL_FUNC_CNTL_4				0x854
#	define UPLL_SPARE_ISPARE9			0x00020000
#घोषणा CG_UPLL_SPREAD_SPECTRUM				0x79c
#	define SSEN_MASK				0x00000001

/* fusion uvd घड़ीs */
#घोषणा CG_DCLK_CNTL                                    0x610
#       define DCLK_DIVIDER_MASK                        0x7f
#       define DCLK_सूची_CNTL_EN                         (1 << 8)
#घोषणा CG_DCLK_STATUS                                  0x614
#       define DCLK_STATUS                              (1 << 0)
#घोषणा CG_VCLK_CNTL                                    0x618
#घोषणा CG_VCLK_STATUS                                  0x61c
#घोषणा	CG_SCRATCH1					0x820

#घोषणा RLC_CNTL                                        0x3f00
#       define RLC_ENABLE                               (1 << 0)
#       define GFX_POWER_GATING_ENABLE                  (1 << 7)
#       define GFX_POWER_GATING_SRC                     (1 << 8)
#       define DYN_PER_SIMD_PG_ENABLE                   (1 << 27)
#       define LB_CNT_SPIM_ACTIVE                       (1 << 30)
#       define LOAD_BALANCE_ENABLE                      (1 << 31)

#घोषणा RLC_HB_BASE                                       0x3f10
#घोषणा RLC_HB_CNTL                                       0x3f0c
#घोषणा RLC_HB_RPTR                                       0x3f20
#घोषणा RLC_HB_WPTR                                       0x3f1c
#घोषणा RLC_HB_WPTR_LSB_ADDR                              0x3f14
#घोषणा RLC_HB_WPTR_MSB_ADDR                              0x3f18
#घोषणा RLC_MC_CNTL                                       0x3f44
#घोषणा RLC_UCODE_CNTL                                    0x3f48
#घोषणा RLC_UCODE_ADDR                                    0x3f2c
#घोषणा RLC_UCODE_DATA                                    0x3f30

/* new क्रम TN */
#घोषणा TN_RLC_SAVE_AND_RESTORE_BASE                      0x3f10
#घोषणा TN_RLC_LB_CNTR_MAX                                0x3f14
#घोषणा TN_RLC_LB_CNTR_INIT                               0x3f18
#घोषणा TN_RLC_CLEAR_STATE_RESTORE_BASE                   0x3f20
#घोषणा TN_RLC_LB_INIT_SIMD_MASK                          0x3fe4
#घोषणा TN_RLC_LB_ALWAYS_ACTIVE_SIMD_MASK                 0x3fe8
#घोषणा TN_RLC_LB_PARAMS                                  0x3fec

#घोषणा GRBM_GFX_INDEX          			0x802C
#घोषणा		INSTANCE_INDEX(x)			((x) << 0)
#घोषणा		SE_INDEX(x)     			((x) << 16)
#घोषणा		INSTANCE_BROADCAST_WRITES      		(1 << 30)
#घोषणा		SE_BROADCAST_WRITES      		(1 << 31)
#घोषणा RLC_GFX_INDEX           			0x3fC4
#घोषणा CC_GC_SHADER_PIPE_CONFIG			0x8950
#घोषणा		WRITE_DIS      				(1 << 0)
#घोषणा CC_RB_BACKEND_DISABLE				0x98F4
#घोषणा		BACKEND_DISABLE(x)     			((x) << 16)
#घोषणा GB_ADDR_CONFIG  				0x98F8
#घोषणा		NUM_PIPES(x)				((x) << 0)
#घोषणा		NUM_PIPES_MASK				0x0000000f
#घोषणा		PIPE_INTERLEAVE_SIZE(x)			((x) << 4)
#घोषणा		BANK_INTERLEAVE_SIZE(x)			((x) << 8)
#घोषणा		NUM_SHADER_ENGINES(x)			((x) << 12)
#घोषणा		SHADER_ENGINE_TILE_SIZE(x)     		((x) << 16)
#घोषणा		NUM_GPUS(x)     			((x) << 20)
#घोषणा		MULTI_GPU_TILE_SIZE(x)     		((x) << 24)
#घोषणा		ROW_SIZE(x)             		((x) << 28)
#घोषणा GB_BACKEND_MAP  				0x98FC
#घोषणा DMIF_ADDR_CONFIG  				0xBD4
#घोषणा HDP_ADDR_CONFIG  				0x2F48
#घोषणा HDP_MISC_CNTL  					0x2F4C
#घोषणा		HDP_FLUSH_INVALIDATE_CACHE      	(1 << 0)

#घोषणा	CC_SYS_RB_BACKEND_DISABLE			0x3F88
#घोषणा	GC_USER_RB_BACKEND_DISABLE			0x9B7C

#घोषणा	CGTS_SYS_TCC_DISABLE				0x3F90
#घोषणा	CGTS_TCC_DISABLE				0x9148
#घोषणा	CGTS_USER_SYS_TCC_DISABLE			0x3F94
#घोषणा	CGTS_USER_TCC_DISABLE				0x914C

#घोषणा	CONFIG_MEMSIZE					0x5428

#घोषणा	BIF_FB_EN						0x5490
#घोषणा		FB_READ_EN					(1 << 0)
#घोषणा		FB_WRITE_EN					(1 << 1)

#घोषणा	CP_STRMOUT_CNTL					0x84FC

#घोषणा	CP_COHER_CNTL					0x85F0
#घोषणा	CP_COHER_SIZE					0x85F4
#घोषणा	CP_COHER_BASE					0x85F8
#घोषणा	CP_STALLED_STAT1			0x8674
#घोषणा	CP_STALLED_STAT2			0x8678
#घोषणा	CP_BUSY_STAT				0x867C
#घोषणा	CP_STAT						0x8680
#घोषणा CP_ME_CNTL					0x86D8
#घोषणा		CP_ME_HALT					(1 << 28)
#घोषणा		CP_PFP_HALT					(1 << 26)
#घोषणा	CP_ME_RAM_DATA					0xC160
#घोषणा	CP_ME_RAM_RADDR					0xC158
#घोषणा	CP_ME_RAM_WADDR					0xC15C
#घोषणा CP_MEQ_THRESHOLDS				0x8764
#घोषणा		STQ_SPLIT(x)					((x) << 0)
#घोषणा	CP_PERFMON_CNTL					0x87FC
#घोषणा	CP_PFP_UCODE_ADDR				0xC150
#घोषणा	CP_PFP_UCODE_DATA				0xC154
#घोषणा	CP_QUEUE_THRESHOLDS				0x8760
#घोषणा		ROQ_IB1_START(x)				((x) << 0)
#घोषणा		ROQ_IB2_START(x)				((x) << 8)
#घोषणा	CP_RB_BASE					0xC100
#घोषणा	CP_RB_CNTL					0xC104
#घोषणा		RB_BUFSZ(x)					((x) << 0)
#घोषणा		RB_BLKSZ(x)					((x) << 8)
#घोषणा		RB_NO_UPDATE					(1 << 27)
#घोषणा		RB_RPTR_WR_ENA					(1 << 31)
#घोषणा		BUF_SWAP_32BIT					(2 << 16)
#घोषणा	CP_RB_RPTR					0x8700
#घोषणा	CP_RB_RPTR_ADDR					0xC10C
#घोषणा		RB_RPTR_SWAP(x)					((x) << 0)
#घोषणा	CP_RB_RPTR_ADDR_HI				0xC110
#घोषणा	CP_RB_RPTR_WR					0xC108
#घोषणा	CP_RB_WPTR					0xC114
#घोषणा	CP_RB_WPTR_ADDR					0xC118
#घोषणा	CP_RB_WPTR_ADDR_HI				0xC11C
#घोषणा	CP_RB_WPTR_DELAY				0x8704
#घोषणा	CP_SEM_WAIT_TIMER				0x85BC
#घोषणा	CP_SEM_INCOMPLETE_TIMER_CNTL			0x85C8
#घोषणा	CP_DEBUG					0xC1FC

/* Audio घड़ीs */
#घोषणा DCCG_AUDIO_DTO_SOURCE             0x05ac
#       define DCCG_AUDIO_DTO0_SOURCE_SEL(x) ((x) << 0) /* crtc0 - crtc5 */
#       define DCCG_AUDIO_DTO_SEL         (1 << 4) /* 0=dto0 1=dto1 */

#घोषणा DCCG_AUDIO_DTO0_PHASE             0x05b0
#घोषणा DCCG_AUDIO_DTO0_MODULE            0x05b4
#घोषणा DCCG_AUDIO_DTO0_LOAD              0x05b8
#घोषणा DCCG_AUDIO_DTO0_CNTL              0x05bc
#       define DCCG_AUDIO_DTO_WALLCLOCK_RATIO(x) (((x) & 7) << 0)
#       define DCCG_AUDIO_DTO_WALLCLOCK_RATIO_MASK 7
#       define DCCG_AUDIO_DTO_WALLCLOCK_RATIO_SHIFT 0

#घोषणा DCCG_AUDIO_DTO1_PHASE             0x05c0
#घोषणा DCCG_AUDIO_DTO1_MODULE            0x05c4
#घोषणा DCCG_AUDIO_DTO1_LOAD              0x05c8
#घोषणा DCCG_AUDIO_DTO1_CNTL              0x05cc
#       define DCCG_AUDIO_DTO1_USE_512FBR_DTO (1 << 3)

#घोषणा DCE41_DENTIST_DISPCLK_CNTL			0x049c
#       define DENTIST_DPREFCLK_WDIVIDER(x)		(((x) & 0x7f) << 24)
#       define DENTIST_DPREFCLK_WDIVIDER_MASK		(0x7f << 24)
#       define DENTIST_DPREFCLK_WDIVIDER_SHIFT		24

/* DCE 4.0 AFMT */
#घोषणा HDMI_CONTROL                         0x7030
#       define HDMI_KEEPOUT_MODE             (1 << 0)
#       define HDMI_PACKET_GEN_VERSION       (1 << 4) /* 0 = r6xx compat */
#       define HDMI_ERROR_ACK                (1 << 8)
#       define HDMI_ERROR_MASK               (1 << 9)
#       define HDMI_DEEP_COLOR_ENABLE        (1 << 24)
#       define HDMI_DEEP_COLOR_DEPTH(x)      (((x) & 3) << 28)
#       define HDMI_24BIT_DEEP_COLOR         0
#       define HDMI_30BIT_DEEP_COLOR         1
#       define HDMI_36BIT_DEEP_COLOR         2
#       define HDMI_DEEP_COLOR_DEPTH_MASK    (3 << 28)
#घोषणा HDMI_STATUS                          0x7034
#       define HDMI_ACTIVE_AVMUTE            (1 << 0)
#       define HDMI_AUDIO_PACKET_ERROR       (1 << 16)
#       define HDMI_VBI_PACKET_ERROR         (1 << 20)
#घोषणा HDMI_AUDIO_PACKET_CONTROL            0x7038
#       define HDMI_AUDIO_DELAY_EN(x)        (((x) & 3) << 4)
#       define HDMI_AUDIO_PACKETS_PER_LINE(x)  (((x) & 0x1f) << 16)
#घोषणा HDMI_ACR_PACKET_CONTROL              0x703c
#       define HDMI_ACR_SEND                 (1 << 0)
#       define HDMI_ACR_CONT                 (1 << 1)
#       define HDMI_ACR_SELECT(x)            (((x) & 3) << 4)
#       define HDMI_ACR_HW                   0
#       define HDMI_ACR_32                   1
#       define HDMI_ACR_44                   2
#       define HDMI_ACR_48                   3
#       define HDMI_ACR_SOURCE               (1 << 8) /* 0 - hw; 1 - cts value */
#       define HDMI_ACR_AUTO_SEND            (1 << 12)
#       define HDMI_ACR_N_MULTIPLE(x)        (((x) & 7) << 16)
#       define HDMI_ACR_X1                   1
#       define HDMI_ACR_X2                   2
#       define HDMI_ACR_X4                   4
#       define HDMI_ACR_AUDIO_PRIORITY       (1 << 31)
#घोषणा HDMI_VBI_PACKET_CONTROL              0x7040
#       define HDMI_शून्य_SEND                (1 << 0)
#       define HDMI_GC_SEND                  (1 << 4)
#       define HDMI_GC_CONT                  (1 << 5) /* 0 - once; 1 - every frame */
#घोषणा HDMI_INFOFRAME_CONTROL0              0x7044
#       define HDMI_AVI_INFO_SEND            (1 << 0)
#       define HDMI_AVI_INFO_CONT            (1 << 1)
#       define HDMI_AUDIO_INFO_SEND          (1 << 4)
#       define HDMI_AUDIO_INFO_CONT          (1 << 5)
#       define HDMI_MPEG_INFO_SEND           (1 << 8)
#       define HDMI_MPEG_INFO_CONT           (1 << 9)
#घोषणा HDMI_INFOFRAME_CONTROL1              0x7048
#       define HDMI_AVI_INFO_LINE(x)         (((x) & 0x3f) << 0)
#       define HDMI_AVI_INFO_LINE_MASK       (0x3f << 0)
#       define HDMI_AUDIO_INFO_LINE(x)       (((x) & 0x3f) << 8)
#       define HDMI_MPEG_INFO_LINE(x)        (((x) & 0x3f) << 16)
#घोषणा HDMI_GENERIC_PACKET_CONTROL          0x704c
#       define HDMI_GENERIC0_SEND            (1 << 0)
#       define HDMI_GENERIC0_CONT            (1 << 1)
#       define HDMI_GENERIC1_SEND            (1 << 4)
#       define HDMI_GENERIC1_CONT            (1 << 5)
#       define HDMI_GENERIC0_LINE(x)         (((x) & 0x3f) << 16)
#       define HDMI_GENERIC1_LINE(x)         (((x) & 0x3f) << 24)
#घोषणा HDMI_GC                              0x7058
#       define HDMI_GC_AVMUTE                (1 << 0)
#       define HDMI_GC_AVMUTE_CONT           (1 << 2)
#घोषणा AFMT_AUDIO_PACKET_CONTROL2           0x705c
#       define AFMT_AUDIO_LAYOUT_OVRD        (1 << 0)
#       define AFMT_AUDIO_LAYOUT_SELECT      (1 << 1)
#       define AFMT_60958_CS_SOURCE          (1 << 4)
#       define AFMT_AUDIO_CHANNEL_ENABLE(x)  (((x) & 0xff) << 8)
#       define AFMT_DP_AUDIO_STREAM_ID(x)    (((x) & 0xff) << 16)
#घोषणा AFMT_AVI_INFO0                       0x7084
#       define AFMT_AVI_INFO_CHECKSUM(x)     (((x) & 0xff) << 0)
#       define AFMT_AVI_INFO_S(x)            (((x) & 3) << 8)
#       define AFMT_AVI_INFO_B(x)            (((x) & 3) << 10)
#       define AFMT_AVI_INFO_A(x)            (((x) & 1) << 12)
#       define AFMT_AVI_INFO_Y(x)            (((x) & 3) << 13)
#       define AFMT_AVI_INFO_Y_RGB           0
#       define AFMT_AVI_INFO_Y_YCBCR422      1
#       define AFMT_AVI_INFO_Y_YCBCR444      2
#       define AFMT_AVI_INFO_Y_A_B_S(x)      (((x) & 0xff) << 8)
#       define AFMT_AVI_INFO_R(x)            (((x) & 0xf) << 16)
#       define AFMT_AVI_INFO_M(x)            (((x) & 0x3) << 20)
#       define AFMT_AVI_INFO_C(x)            (((x) & 0x3) << 22)
#       define AFMT_AVI_INFO_C_M_R(x)        (((x) & 0xff) << 16)
#       define AFMT_AVI_INFO_SC(x)           (((x) & 0x3) << 24)
#       define AFMT_AVI_INFO_Q(x)            (((x) & 0x3) << 26)
#       define AFMT_AVI_INFO_EC(x)           (((x) & 0x3) << 28)
#       define AFMT_AVI_INFO_ITC(x)          (((x) & 0x1) << 31)
#       define AFMT_AVI_INFO_ITC_EC_Q_SC(x)  (((x) & 0xff) << 24)
#घोषणा AFMT_AVI_INFO1                       0x7088
#       define AFMT_AVI_INFO_VIC(x)          (((x) & 0x7f) << 0) /* करोn't use avi infoframe v1 */
#       define AFMT_AVI_INFO_PR(x)           (((x) & 0xf) << 8) /* करोn't use avi infoframe v1 */
#       define AFMT_AVI_INFO_CN(x)           (((x) & 0x3) << 12)
#       define AFMT_AVI_INFO_YQ(x)           (((x) & 0x3) << 14)
#       define AFMT_AVI_INFO_TOP(x)          (((x) & 0xffff) << 16)
#घोषणा AFMT_AVI_INFO2                       0x708c
#       define AFMT_AVI_INFO_BOTTOM(x)       (((x) & 0xffff) << 0)
#       define AFMT_AVI_INFO_LEFT(x)         (((x) & 0xffff) << 16)
#घोषणा AFMT_AVI_INFO3                       0x7090
#       define AFMT_AVI_INFO_RIGHT(x)        (((x) & 0xffff) << 0)
#       define AFMT_AVI_INFO_VERSION(x)      (((x) & 3) << 24)
#घोषणा AFMT_MPEG_INFO0                      0x7094
#       define AFMT_MPEG_INFO_CHECKSUM(x)    (((x) & 0xff) << 0)
#       define AFMT_MPEG_INFO_MB0(x)         (((x) & 0xff) << 8)
#       define AFMT_MPEG_INFO_MB1(x)         (((x) & 0xff) << 16)
#       define AFMT_MPEG_INFO_MB2(x)         (((x) & 0xff) << 24)
#घोषणा AFMT_MPEG_INFO1                      0x7098
#       define AFMT_MPEG_INFO_MB3(x)         (((x) & 0xff) << 0)
#       define AFMT_MPEG_INFO_MF(x)          (((x) & 3) << 8)
#       define AFMT_MPEG_INFO_FR(x)          (((x) & 1) << 12)
#घोषणा AFMT_GENERIC0_HDR                    0x709c
#घोषणा AFMT_GENERIC0_0                      0x70a0
#घोषणा AFMT_GENERIC0_1                      0x70a4
#घोषणा AFMT_GENERIC0_2                      0x70a8
#घोषणा AFMT_GENERIC0_3                      0x70ac
#घोषणा AFMT_GENERIC0_4                      0x70b0
#घोषणा AFMT_GENERIC0_5                      0x70b4
#घोषणा AFMT_GENERIC0_6                      0x70b8
#घोषणा AFMT_GENERIC1_HDR                    0x70bc
#घोषणा AFMT_GENERIC1_0                      0x70c0
#घोषणा AFMT_GENERIC1_1                      0x70c4
#घोषणा AFMT_GENERIC1_2                      0x70c8
#घोषणा AFMT_GENERIC1_3                      0x70cc
#घोषणा AFMT_GENERIC1_4                      0x70d0
#घोषणा AFMT_GENERIC1_5                      0x70d4
#घोषणा AFMT_GENERIC1_6                      0x70d8
#घोषणा HDMI_ACR_32_0                        0x70dc
#       define HDMI_ACR_CTS_32(x)            (((x) & 0xfffff) << 12)
#घोषणा HDMI_ACR_32_1                        0x70e0
#       define HDMI_ACR_N_32(x)              (((x) & 0xfffff) << 0)
#घोषणा HDMI_ACR_44_0                        0x70e4
#       define HDMI_ACR_CTS_44(x)            (((x) & 0xfffff) << 12)
#घोषणा HDMI_ACR_44_1                        0x70e8
#       define HDMI_ACR_N_44(x)              (((x) & 0xfffff) << 0)
#घोषणा HDMI_ACR_48_0                        0x70ec
#       define HDMI_ACR_CTS_48(x)            (((x) & 0xfffff) << 12)
#घोषणा HDMI_ACR_48_1                        0x70f0
#       define HDMI_ACR_N_48(x)              (((x) & 0xfffff) << 0)
#घोषणा HDMI_ACR_STATUS_0                    0x70f4
#घोषणा HDMI_ACR_STATUS_1                    0x70f8
#घोषणा AFMT_AUDIO_INFO0                     0x70fc
#       define AFMT_AUDIO_INFO_CHECKSUM(x)   (((x) & 0xff) << 0)
#       define AFMT_AUDIO_INFO_CC(x)         (((x) & 7) << 8)
#       define AFMT_AUDIO_INFO_CT(x)         (((x) & 0xf) << 11)
#       define AFMT_AUDIO_INFO_CHECKSUM_OFFSET(x)   (((x) & 0xff) << 16)
#       define AFMT_AUDIO_INFO_CXT(x)        (((x) & 0x1f) << 24)
#घोषणा AFMT_AUDIO_INFO1                     0x7100
#       define AFMT_AUDIO_INFO_CA(x)         (((x) & 0xff) << 0)
#       define AFMT_AUDIO_INFO_LSV(x)        (((x) & 0xf) << 11)
#       define AFMT_AUDIO_INFO_DM_INH(x)     (((x) & 1) << 15)
#       define AFMT_AUDIO_INFO_DM_INH_LSV(x) (((x) & 0xff) << 8)
#       define AFMT_AUDIO_INFO_LFEBPL(x)     (((x) & 3) << 16)
#घोषणा AFMT_60958_0                         0x7104
#       define AFMT_60958_CS_A(x)            (((x) & 1) << 0)
#       define AFMT_60958_CS_B(x)            (((x) & 1) << 1)
#       define AFMT_60958_CS_C(x)            (((x) & 1) << 2)
#       define AFMT_60958_CS_D(x)            (((x) & 3) << 3)
#       define AFMT_60958_CS_MODE(x)         (((x) & 3) << 6)
#       define AFMT_60958_CS_CATEGORY_CODE(x)      (((x) & 0xff) << 8)
#       define AFMT_60958_CS_SOURCE_NUMBER(x)      (((x) & 0xf) << 16)
#       define AFMT_60958_CS_CHANNEL_NUMBER_L(x)   (((x) & 0xf) << 20)
#       define AFMT_60958_CS_SAMPLING_FREQUENCY(x) (((x) & 0xf) << 24)
#       define AFMT_60958_CS_CLOCK_ACCURACY(x)     (((x) & 3) << 28)
#घोषणा AFMT_60958_1                         0x7108
#       define AFMT_60958_CS_WORD_LENGTH(x)  (((x) & 0xf) << 0)
#       define AFMT_60958_CS_ORIGINAL_SAMPLING_FREQUENCY(x)   (((x) & 0xf) << 4)
#       define AFMT_60958_CS_VALID_L(x)      (((x) & 1) << 16)
#       define AFMT_60958_CS_VALID_R(x)      (((x) & 1) << 18)
#       define AFMT_60958_CS_CHANNEL_NUMBER_R(x)   (((x) & 0xf) << 20)
#घोषणा AFMT_AUDIO_CRC_CONTROL               0x710c
#       define AFMT_AUDIO_CRC_EN             (1 << 0)
#घोषणा AFMT_RAMP_CONTROL0                   0x7110
#       define AFMT_RAMP_MAX_COUNT(x)        (((x) & 0xffffff) << 0)
#       define AFMT_RAMP_DATA_SIGN           (1 << 31)
#घोषणा AFMT_RAMP_CONTROL1                   0x7114
#       define AFMT_RAMP_MIN_COUNT(x)        (((x) & 0xffffff) << 0)
#       define AFMT_AUDIO_TEST_CH_DISABLE(x) (((x) & 0xff) << 24)
#घोषणा AFMT_RAMP_CONTROL2                   0x7118
#       define AFMT_RAMP_INC_COUNT(x)        (((x) & 0xffffff) << 0)
#घोषणा AFMT_RAMP_CONTROL3                   0x711c
#       define AFMT_RAMP_DEC_COUNT(x)        (((x) & 0xffffff) << 0)
#घोषणा AFMT_60958_2                         0x7120
#       define AFMT_60958_CS_CHANNEL_NUMBER_2(x)   (((x) & 0xf) << 0)
#       define AFMT_60958_CS_CHANNEL_NUMBER_3(x)   (((x) & 0xf) << 4)
#       define AFMT_60958_CS_CHANNEL_NUMBER_4(x)   (((x) & 0xf) << 8)
#       define AFMT_60958_CS_CHANNEL_NUMBER_5(x)   (((x) & 0xf) << 12)
#       define AFMT_60958_CS_CHANNEL_NUMBER_6(x)   (((x) & 0xf) << 16)
#       define AFMT_60958_CS_CHANNEL_NUMBER_7(x)   (((x) & 0xf) << 20)
#घोषणा AFMT_STATUS                          0x7128
#       define AFMT_AUDIO_ENABLE             (1 << 4)
#       define AFMT_AUDIO_HBR_ENABLE         (1 << 8)
#       define AFMT_AZ_FORMAT_WTRIG          (1 << 28)
#       define AFMT_AZ_FORMAT_WTRIG_INT      (1 << 29)
#       define AFMT_AZ_AUDIO_ENABLE_CHG      (1 << 30)
#घोषणा AFMT_AUDIO_PACKET_CONTROL            0x712c
#       define AFMT_AUDIO_SAMPLE_SEND        (1 << 0)
#       define AFMT_RESET_FIFO_WHEN_AUDIO_DIS (1 << 11) /* set to 1 */
#       define AFMT_AUDIO_TEST_EN            (1 << 12)
#       define AFMT_AUDIO_CHANNEL_SWAP       (1 << 24)
#       define AFMT_60958_CS_UPDATE          (1 << 26)
#       define AFMT_AZ_AUDIO_ENABLE_CHG_MASK (1 << 27)
#       define AFMT_AZ_FORMAT_WTRIG_MASK     (1 << 28)
#       define AFMT_AZ_FORMAT_WTRIG_ACK      (1 << 29)
#       define AFMT_AZ_AUDIO_ENABLE_CHG_ACK  (1 << 30)
#घोषणा AFMT_VBI_PACKET_CONTROL              0x7130
#       define AFMT_GENERIC0_UPDATE          (1 << 2)
#घोषणा AFMT_INFOFRAME_CONTROL0              0x7134
#       define AFMT_AUDIO_INFO_SOURCE        (1 << 6) /* 0 - sound block; 1 - afmt regs */
#       define AFMT_AUDIO_INFO_UPDATE        (1 << 7)
#       define AFMT_MPEG_INFO_UPDATE         (1 << 10)
#घोषणा AFMT_GENERIC0_7                      0x7138

/* DCE4/5 ELD audio पूर्णांकerface */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_CHANNEL_SPEAKER          0x5f78
#घोषणा		SPEAKER_ALLOCATION(x)			(((x) & 0x7f) << 0)
#घोषणा		SPEAKER_ALLOCATION_MASK			(0x7f << 0)
#घोषणा		SPEAKER_ALLOCATION_SHIFT		0
#घोषणा		HDMI_CONNECTION				(1 << 16)
#घोषणा		DP_CONNECTION				(1 << 17)

#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR0        0x5f84 /* LPCM */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR1        0x5f88 /* AC3 */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR2        0x5f8c /* MPEG1 */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR3        0x5f90 /* MP3 */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR4        0x5f94 /* MPEG2 */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR5        0x5f98 /* AAC */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR6        0x5f9c /* DTS */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR7        0x5fa0 /* ATRAC */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR8        0x5fa4 /* one bit audio - leave at 0 (शेष) */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR9        0x5fa8 /* Dolby Digital */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR10       0x5fac /* DTS-HD */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR11       0x5fb0 /* MAT-MLP */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR12       0x5fb4 /* DTS */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_AUDIO_DESCRIPTOR13       0x5fb8 /* WMA Pro */
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

#घोषणा AZ_CHANNEL_COUNT_CONTROL                          0x5fe4
#       define HBR_CHANNEL_COUNT(x)                       (((x) & 0x7) << 0)
#       define COMPRESSED_CHANNEL_COUNT(x)                (((x) & 0x7) << 4)
/* HBR_CHANNEL_COUNT, COMPRESSED_CHANNEL_COUNT
 * 0   = use stream header
 * 1-7 = channel count - 1
 */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_RESPONSE_LIPSYNC         0x5fe8
#       define VIDEO_LIPSYNC(x)                           (((x) & 0xff) << 0)
#       define AUDIO_LIPSYNC(x)                           (((x) & 0xff) << 8)
/* VIDEO_LIPSYNC, AUDIO_LIPSYNC
 * 0   = invalid
 * x   = legal delay value
 * 255 = sync not supported
 */
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_RESPONSE_HBR             0x5fec
#       define HBR_CAPABLE                                (1 << 0) /* enabled by शेष */

#घोषणा AZ_F0_CODEC_PIN0_CONTROL_RESPONSE_AV_ASSOCIATION0 0x5ff4
#       define DISPLAY0_TYPE(x)                           (((x) & 0x3) << 0)
#       define DISPLAY_TYPE_NONE                   0
#       define DISPLAY_TYPE_HDMI                   1
#       define DISPLAY_TYPE_DP                     2
#       define DISPLAY0_ID(x)                             (((x) & 0x3f) << 2)
#       define DISPLAY1_TYPE(x)                           (((x) & 0x3) << 8)
#       define DISPLAY1_ID(x)                             (((x) & 0x3f) << 10)
#       define DISPLAY2_TYPE(x)                           (((x) & 0x3) << 16)
#       define DISPLAY2_ID(x)                             (((x) & 0x3f) << 18)
#       define DISPLAY3_TYPE(x)                           (((x) & 0x3) << 24)
#       define DISPLAY3_ID(x)                             (((x) & 0x3f) << 26)
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_RESPONSE_AV_ASSOCIATION1 0x5ff8
#       define DISPLAY4_TYPE(x)                           (((x) & 0x3) << 0)
#       define DISPLAY4_ID(x)                             (((x) & 0x3f) << 2)
#       define DISPLAY5_TYPE(x)                           (((x) & 0x3) << 8)
#       define DISPLAY5_ID(x)                             (((x) & 0x3f) << 10)
#घोषणा AZ_F0_CODEC_PIN0_CONTROL_RESPONSE_AV_NUMBER       0x5ffc
#       define NUMBER_OF_DISPLAY_ID(x)                    (((x) & 0x7) << 0)

#घोषणा AZ_HOT_PLUG_CONTROL                               0x5e78
#       define AZ_FORCE_CODEC_WAKE                        (1 << 0)
#       define PIN0_JACK_DETECTION_ENABLE                 (1 << 4)
#       define PIN1_JACK_DETECTION_ENABLE                 (1 << 5)
#       define PIN2_JACK_DETECTION_ENABLE                 (1 << 6)
#       define PIN3_JACK_DETECTION_ENABLE                 (1 << 7)
#       define PIN0_UNSOLICITED_RESPONSE_ENABLE           (1 << 8)
#       define PIN1_UNSOLICITED_RESPONSE_ENABLE           (1 << 9)
#       define PIN2_UNSOLICITED_RESPONSE_ENABLE           (1 << 10)
#       define PIN3_UNSOLICITED_RESPONSE_ENABLE           (1 << 11)
#       define CODEC_HOT_PLUG_ENABLE                      (1 << 12)
#       define PIN0_AUDIO_ENABLED                         (1 << 24)
#       define PIN1_AUDIO_ENABLED                         (1 << 25)
#       define PIN2_AUDIO_ENABLED                         (1 << 26)
#       define PIN3_AUDIO_ENABLED                         (1 << 27)
#       define AUDIO_ENABLED                              (1 << 31)


#घोषणा	GC_USER_SHADER_PIPE_CONFIG			0x8954
#घोषणा		INACTIVE_QD_PIPES(x)				((x) << 8)
#घोषणा		INACTIVE_QD_PIPES_MASK				0x0000FF00
#घोषणा		INACTIVE_SIMDS(x)				((x) << 16)
#घोषणा		INACTIVE_SIMDS_MASK				0x00FF0000

#घोषणा	GRBM_CNTL					0x8000
#घोषणा		GRBM_READ_TIMEOUT(x)				((x) << 0)
#घोषणा	GRBM_SOFT_RESET					0x8020
#घोषणा		SOFT_RESET_CP					(1 << 0)
#घोषणा		SOFT_RESET_CB					(1 << 1)
#घोषणा		SOFT_RESET_DB					(1 << 3)
#घोषणा		SOFT_RESET_PA					(1 << 5)
#घोषणा		SOFT_RESET_SC					(1 << 6)
#घोषणा		SOFT_RESET_SPI					(1 << 8)
#घोषणा		SOFT_RESET_SH					(1 << 9)
#घोषणा		SOFT_RESET_SX					(1 << 10)
#घोषणा		SOFT_RESET_TC					(1 << 11)
#घोषणा		SOFT_RESET_TA					(1 << 12)
#घोषणा		SOFT_RESET_VC					(1 << 13)
#घोषणा		SOFT_RESET_VGT					(1 << 14)

#घोषणा	GRBM_STATUS					0x8010
#घोषणा		CMDFIFO_AVAIL_MASK				0x0000000F
#घोषणा		SRBM_RQ_PENDING					(1 << 5)
#घोषणा		CF_RQ_PENDING					(1 << 7)
#घोषणा		PF_RQ_PENDING					(1 << 8)
#घोषणा		GRBM_EE_BUSY					(1 << 10)
#घोषणा		SX_CLEAN					(1 << 11)
#घोषणा		DB_CLEAN					(1 << 12)
#घोषणा		CB_CLEAN					(1 << 13)
#घोषणा		TA_BUSY 					(1 << 14)
#घोषणा		VGT_BUSY_NO_DMA					(1 << 16)
#घोषणा		VGT_BUSY					(1 << 17)
#घोषणा		SX_BUSY 					(1 << 20)
#घोषणा		SH_BUSY 					(1 << 21)
#घोषणा		SPI_BUSY					(1 << 22)
#घोषणा		SC_BUSY 					(1 << 24)
#घोषणा		PA_BUSY 					(1 << 25)
#घोषणा		DB_BUSY 					(1 << 26)
#घोषणा		CP_COHERENCY_BUSY      				(1 << 28)
#घोषणा		CP_BUSY 					(1 << 29)
#घोषणा		CB_BUSY 					(1 << 30)
#घोषणा		GUI_ACTIVE					(1 << 31)
#घोषणा	GRBM_STATUS_SE0					0x8014
#घोषणा	GRBM_STATUS_SE1					0x8018
#घोषणा		SE_SX_CLEAN					(1 << 0)
#घोषणा		SE_DB_CLEAN					(1 << 1)
#घोषणा		SE_CB_CLEAN					(1 << 2)
#घोषणा		SE_TA_BUSY					(1 << 25)
#घोषणा		SE_SX_BUSY					(1 << 26)
#घोषणा		SE_SPI_BUSY					(1 << 27)
#घोषणा		SE_SH_BUSY					(1 << 28)
#घोषणा		SE_SC_BUSY					(1 << 29)
#घोषणा		SE_DB_BUSY					(1 << 30)
#घोषणा		SE_CB_BUSY					(1 << 31)
/* evergreen */
#घोषणा	CG_THERMAL_CTRL					0x72c
#घोषणा		TOFFSET_MASK			        0x00003FE0
#घोषणा		TOFFSET_SHIFT			        5
#घोषणा		DIG_THERM_DPM(x)			((x) << 14)
#घोषणा		DIG_THERM_DPM_MASK			0x003FC000
#घोषणा		DIG_THERM_DPM_SHIFT			14

#घोषणा	CG_THERMAL_INT					0x734
#घोषणा		DIG_THERM_INTH(x)			((x) << 8)
#घोषणा		DIG_THERM_INTH_MASK			0x0000FF00
#घोषणा		DIG_THERM_INTH_SHIFT			8
#घोषणा		DIG_THERM_INTL(x)			((x) << 16)
#घोषणा		DIG_THERM_INTL_MASK			0x00FF0000
#घोषणा		DIG_THERM_INTL_SHIFT			16
#घोषणा 	THERM_INT_MASK_HIGH			(1 << 24)
#घोषणा 	THERM_INT_MASK_LOW			(1 << 25)

#घोषणा	TN_CG_THERMAL_INT_CTRL				0x738
#घोषणा		TN_DIG_THERM_INTH(x)			((x) << 0)
#घोषणा		TN_DIG_THERM_INTH_MASK			0x000000FF
#घोषणा		TN_DIG_THERM_INTH_SHIFT			0
#घोषणा		TN_DIG_THERM_INTL(x)			((x) << 8)
#घोषणा		TN_DIG_THERM_INTL_MASK			0x0000FF00
#घोषणा		TN_DIG_THERM_INTL_SHIFT			8
#घोषणा 	TN_THERM_INT_MASK_HIGH			(1 << 24)
#घोषणा 	TN_THERM_INT_MASK_LOW			(1 << 25)

#घोषणा	CG_MULT_THERMAL_STATUS				0x740
#घोषणा		ASIC_T(x)			        ((x) << 16)
#घोषणा		ASIC_T_MASK			        0x07FF0000
#घोषणा		ASIC_T_SHIFT			        16
#घोषणा	CG_TS0_STATUS					0x760
#घोषणा		TS0_ADC_DOUT_MASK			0x000003FF
#घोषणा		TS0_ADC_DOUT_SHIFT			0

/* APU */
#घोषणा	CG_THERMAL_STATUS			        0x678

#घोषणा	HDP_HOST_PATH_CNTL				0x2C00
#घोषणा	HDP_NONSURFACE_BASE				0x2C04
#घोषणा	HDP_NONSURFACE_INFO				0x2C08
#घोषणा	HDP_NONSURFACE_SIZE				0x2C0C
#घोषणा HDP_MEM_COHERENCY_FLUSH_CNTL			0x5480
#घोषणा HDP_REG_COHERENCY_FLUSH_CNTL			0x54A0
#घोषणा	HDP_TILING_CONFIG				0x2F3C

#घोषणा MC_SHARED_CHMAP						0x2004
#घोषणा		NOOFCHAN_SHIFT					12
#घोषणा		NOOFCHAN_MASK					0x00003000
#घोषणा MC_SHARED_CHREMAP					0x2008

#घोषणा MC_SHARED_BLACKOUT_CNTL           		0x20ac
#घोषणा		BLACKOUT_MODE_MASK			0x00000007

#घोषणा	MC_ARB_RAMCFG					0x2760
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
#घोषणा		BURSTLENGTH_SHIFT				9
#घोषणा		BURSTLENGTH_MASK				0x00000200
#घोषणा		CHANSIZE_OVERRIDE				(1 << 11)
#घोषणा	FUS_MC_ARB_RAMCFG				0x2768
#घोषणा	MC_VM_AGP_TOP					0x2028
#घोषणा	MC_VM_AGP_BOT					0x202C
#घोषणा	MC_VM_AGP_BASE					0x2030
#घोषणा	MC_VM_FB_LOCATION				0x2024
#घोषणा	MC_FUS_VM_FB_OFFSET				0x2898
#घोषणा	MC_VM_MB_L1_TLB0_CNTL				0x2234
#घोषणा	MC_VM_MB_L1_TLB1_CNTL				0x2238
#घोषणा	MC_VM_MB_L1_TLB2_CNTL				0x223C
#घोषणा	MC_VM_MB_L1_TLB3_CNTL				0x2240
#घोषणा		ENABLE_L1_TLB					(1 << 0)
#घोषणा		ENABLE_L1_FRAGMENT_PROCESSING			(1 << 1)
#घोषणा		SYSTEM_ACCESS_MODE_PA_ONLY			(0 << 3)
#घोषणा		SYSTEM_ACCESS_MODE_USE_SYS_MAP			(1 << 3)
#घोषणा		SYSTEM_ACCESS_MODE_IN_SYS			(2 << 3)
#घोषणा		SYSTEM_ACCESS_MODE_NOT_IN_SYS			(3 << 3)
#घोषणा		SYSTEM_APERTURE_UNMAPPED_ACCESS_PASS_THRU	(0 << 5)
#घोषणा		EFFECTIVE_L1_TLB_SIZE(x)			((x)<<15)
#घोषणा		EFFECTIVE_L1_QUEUE_SIZE(x)			((x)<<18)
#घोषणा	MC_VM_MD_L1_TLB0_CNTL				0x2654
#घोषणा	MC_VM_MD_L1_TLB1_CNTL				0x2658
#घोषणा	MC_VM_MD_L1_TLB2_CNTL				0x265C
#घोषणा	MC_VM_MD_L1_TLB3_CNTL				0x2698

#घोषणा	FUS_MC_VM_MD_L1_TLB0_CNTL			0x265C
#घोषणा	FUS_MC_VM_MD_L1_TLB1_CNTL			0x2660
#घोषणा	FUS_MC_VM_MD_L1_TLB2_CNTL			0x2664

#घोषणा	MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR		0x203C
#घोषणा	MC_VM_SYSTEM_APERTURE_HIGH_ADDR			0x2038
#घोषणा	MC_VM_SYSTEM_APERTURE_LOW_ADDR			0x2034

#घोषणा	PA_CL_ENHANCE					0x8A14
#घोषणा		CLIP_VTX_REORDER_ENA				(1 << 0)
#घोषणा		NUM_CLIP_SEQ(x)					((x) << 1)
#घोषणा	PA_SC_ENHANCE					0x8BF0
#घोषणा PA_SC_AA_CONFIG					0x28C04
#घोषणा         MSAA_NUM_SAMPLES_SHIFT                  0
#घोषणा         MSAA_NUM_SAMPLES_MASK                   0x3
#घोषणा PA_SC_CLIPRECT_RULE				0x2820C
#घोषणा	PA_SC_EDGERULE					0x28230
#घोषणा	PA_SC_FIFO_SIZE					0x8BCC
#घोषणा		SC_PRIM_FIFO_SIZE(x)				((x) << 0)
#घोषणा		SC_HIZ_TILE_FIFO_SIZE(x)			((x) << 12)
#घोषणा		SC_EARLYZ_TILE_FIFO_SIZE(x)			((x) << 20)
#घोषणा	PA_SC_FORCE_EOV_MAX_CNTS			0x8B24
#घोषणा		FORCE_EOV_MAX_CLK_CNT(x)			((x) << 0)
#घोषणा		FORCE_EOV_MAX_REZ_CNT(x)			((x) << 16)
#घोषणा PA_SC_LINE_STIPPLE				0x28A0C
#घोषणा	PA_SU_LINE_STIPPLE_VALUE			0x8A60
#घोषणा	PA_SC_LINE_STIPPLE_STATE			0x8B10

#घोषणा	SCRATCH_REG0					0x8500
#घोषणा	SCRATCH_REG1					0x8504
#घोषणा	SCRATCH_REG2					0x8508
#घोषणा	SCRATCH_REG3					0x850C
#घोषणा	SCRATCH_REG4					0x8510
#घोषणा	SCRATCH_REG5					0x8514
#घोषणा	SCRATCH_REG6					0x8518
#घोषणा	SCRATCH_REG7					0x851C
#घोषणा	SCRATCH_UMSK					0x8540
#घोषणा	SCRATCH_ADDR					0x8544

#घोषणा	SMX_SAR_CTL0					0xA008
#घोषणा	SMX_DC_CTL0					0xA020
#घोषणा		USE_HASH_FUNCTION				(1 << 0)
#घोषणा		NUMBER_OF_SETS(x)				((x) << 1)
#घोषणा		FLUSH_ALL_ON_EVENT				(1 << 10)
#घोषणा		STALL_ON_EVENT					(1 << 11)
#घोषणा	SMX_EVENT_CTL					0xA02C
#घोषणा		ES_FLUSH_CTL(x)					((x) << 0)
#घोषणा		GS_FLUSH_CTL(x)					((x) << 3)
#घोषणा		ACK_FLUSH_CTL(x)				((x) << 6)
#घोषणा		SYNC_FLUSH_CTL					(1 << 8)

#घोषणा	SPI_CONFIG_CNTL					0x9100
#घोषणा		GPR_WRITE_PRIORITY(x)				((x) << 0)
#घोषणा	SPI_CONFIG_CNTL_1				0x913C
#घोषणा		VTX_DONE_DELAY(x)				((x) << 0)
#घोषणा		INTERP_ONE_PRIM_PER_ROW				(1 << 4)
#घोषणा	SPI_INPUT_Z					0x286D8
#घोषणा	SPI_PS_IN_CONTROL_0				0x286CC
#घोषणा		NUM_INTERP(x)					((x)<<0)
#घोषणा		POSITION_ENA					(1<<8)
#घोषणा		POSITION_CENTROID				(1<<9)
#घोषणा		POSITION_ADDR(x)				((x)<<10)
#घोषणा		PARAM_GEN(x)					((x)<<15)
#घोषणा		PARAM_GEN_ADDR(x)				((x)<<19)
#घोषणा		BARYC_SAMPLE_CNTL(x)				((x)<<26)
#घोषणा		PERSP_GRADIENT_ENA				(1<<28)
#घोषणा		LINEAR_GRADIENT_ENA				(1<<29)
#घोषणा		POSITION_SAMPLE					(1<<30)
#घोषणा		BARYC_AT_SAMPLE_ENA				(1<<31)

#घोषणा	SQ_CONFIG					0x8C00
#घोषणा		VC_ENABLE					(1 << 0)
#घोषणा		EXPORT_SRC_C					(1 << 1)
#घोषणा		CS_PRIO(x)					((x) << 18)
#घोषणा		LS_PRIO(x)					((x) << 20)
#घोषणा		HS_PRIO(x)					((x) << 22)
#घोषणा		PS_PRIO(x)					((x) << 24)
#घोषणा		VS_PRIO(x)					((x) << 26)
#घोषणा		GS_PRIO(x)					((x) << 28)
#घोषणा		ES_PRIO(x)					((x) << 30)
#घोषणा	SQ_GPR_RESOURCE_MGMT_1				0x8C04
#घोषणा		NUM_PS_GPRS(x)					((x) << 0)
#घोषणा		NUM_VS_GPRS(x)					((x) << 16)
#घोषणा		NUM_CLAUSE_TEMP_GPRS(x)				((x) << 28)
#घोषणा	SQ_GPR_RESOURCE_MGMT_2				0x8C08
#घोषणा		NUM_GS_GPRS(x)					((x) << 0)
#घोषणा		NUM_ES_GPRS(x)					((x) << 16)
#घोषणा	SQ_GPR_RESOURCE_MGMT_3				0x8C0C
#घोषणा		NUM_HS_GPRS(x)					((x) << 0)
#घोषणा		NUM_LS_GPRS(x)					((x) << 16)
#घोषणा	SQ_GLOBAL_GPR_RESOURCE_MGMT_1			0x8C10
#घोषणा	SQ_GLOBAL_GPR_RESOURCE_MGMT_2			0x8C14
#घोषणा	SQ_THREAD_RESOURCE_MGMT				0x8C18
#घोषणा		NUM_PS_THREADS(x)				((x) << 0)
#घोषणा		NUM_VS_THREADS(x)				((x) << 8)
#घोषणा		NUM_GS_THREADS(x)				((x) << 16)
#घोषणा		NUM_ES_THREADS(x)				((x) << 24)
#घोषणा	SQ_THREAD_RESOURCE_MGMT_2			0x8C1C
#घोषणा		NUM_HS_THREADS(x)				((x) << 0)
#घोषणा		NUM_LS_THREADS(x)				((x) << 8)
#घोषणा	SQ_STACK_RESOURCE_MGMT_1			0x8C20
#घोषणा		NUM_PS_STACK_ENTRIES(x)				((x) << 0)
#घोषणा		NUM_VS_STACK_ENTRIES(x)				((x) << 16)
#घोषणा	SQ_STACK_RESOURCE_MGMT_2			0x8C24
#घोषणा		NUM_GS_STACK_ENTRIES(x)				((x) << 0)
#घोषणा		NUM_ES_STACK_ENTRIES(x)				((x) << 16)
#घोषणा	SQ_STACK_RESOURCE_MGMT_3			0x8C28
#घोषणा		NUM_HS_STACK_ENTRIES(x)				((x) << 0)
#घोषणा		NUM_LS_STACK_ENTRIES(x)				((x) << 16)
#घोषणा	SQ_DYN_GPR_CNTL_PS_FLUSH_REQ    		0x8D8C
#घोषणा	SQ_DYN_GPR_SIMD_LOCK_EN    			0x8D94
#घोषणा	SQ_STATIC_THREAD_MGMT_1    			0x8E20
#घोषणा	SQ_STATIC_THREAD_MGMT_2    			0x8E24
#घोषणा	SQ_STATIC_THREAD_MGMT_3    			0x8E28
#घोषणा	SQ_LDS_RESOURCE_MGMT    			0x8E2C

#घोषणा	SQ_MS_FIFO_SIZES				0x8CF0
#घोषणा		CACHE_FIFO_SIZE(x)				((x) << 0)
#घोषणा		FETCH_FIFO_HIWATER(x)				((x) << 8)
#घोषणा		DONE_FIFO_HIWATER(x)				((x) << 16)
#घोषणा		ALU_UPDATE_FIFO_HIWATER(x)			((x) << 24)

#घोषणा	SX_DEBUG_1					0x9058
#घोषणा		ENABLE_NEW_SMX_ADDRESS				(1 << 16)
#घोषणा	SX_EXPORT_BUFFER_SIZES				0x900C
#घोषणा		COLOR_BUFFER_SIZE(x)				((x) << 0)
#घोषणा		POSITION_BUFFER_SIZE(x)				((x) << 8)
#घोषणा		SMX_BUFFER_SIZE(x)				((x) << 16)
#घोषणा	SX_MEMORY_EXPORT_BASE				0x9010
#घोषणा	SX_MISC						0x28350

#घोषणा CB_PERF_CTR0_SEL_0				0x9A20
#घोषणा CB_PERF_CTR0_SEL_1				0x9A24
#घोषणा CB_PERF_CTR1_SEL_0				0x9A28
#घोषणा CB_PERF_CTR1_SEL_1				0x9A2C
#घोषणा CB_PERF_CTR2_SEL_0				0x9A30
#घोषणा CB_PERF_CTR2_SEL_1				0x9A34
#घोषणा CB_PERF_CTR3_SEL_0				0x9A38
#घोषणा CB_PERF_CTR3_SEL_1				0x9A3C

#घोषणा	TA_CNTL_AUX					0x9508
#घोषणा		DISABLE_CUBE_WRAP				(1 << 0)
#घोषणा		DISABLE_CUBE_ANISO				(1 << 1)
#घोषणा		SYNC_GRADIENT					(1 << 24)
#घोषणा		SYNC_WALKER					(1 << 25)
#घोषणा		SYNC_ALIGNER					(1 << 26)

#घोषणा	TCP_CHAN_STEER_LO				0x960c
#घोषणा	TCP_CHAN_STEER_HI				0x9610

#घोषणा	VGT_CACHE_INVALIDATION				0x88C4
#घोषणा		CACHE_INVALIDATION(x)				((x) << 0)
#घोषणा			VC_ONLY						0
#घोषणा			TC_ONLY						1
#घोषणा			VC_AND_TC					2
#घोषणा		AUTO_INVLD_EN(x)				((x) << 6)
#घोषणा			NO_AUTO						0
#घोषणा			ES_AUTO						1
#घोषणा			GS_AUTO						2
#घोषणा			ES_AND_GS_AUTO					3
#घोषणा	VGT_GS_VERTEX_REUSE				0x88D4
#घोषणा	VGT_NUM_INSTANCES				0x8974
#घोषणा	VGT_OUT_DEALLOC_CNTL				0x28C5C
#घोषणा		DEALLOC_DIST_MASK				0x0000007F
#घोषणा	VGT_VERTEX_REUSE_BLOCK_CNTL			0x28C58
#घोषणा		VTX_REUSE_DEPTH_MASK				0x000000FF

#घोषणा VM_CONTEXT0_CNTL				0x1410
#घोषणा		ENABLE_CONTEXT					(1 << 0)
#घोषणा		PAGE_TABLE_DEPTH(x)				(((x) & 3) << 1)
#घोषणा		RANGE_PROTECTION_FAULT_ENABLE_DEFAULT		(1 << 4)
#घोषणा VM_CONTEXT1_CNTL				0x1414
#घोषणा VM_CONTEXT1_CNTL2				0x1434
#घोषणा	VM_CONTEXT0_PAGE_TABLE_BASE_ADDR		0x153C
#घोषणा	VM_CONTEXT0_PAGE_TABLE_END_ADDR			0x157C
#घोषणा	VM_CONTEXT0_PAGE_TABLE_START_ADDR		0x155C
#घोषणा VM_CONTEXT0_PROTECTION_FAULT_DEFAULT_ADDR	0x1518
#घोषणा VM_CONTEXT0_REQUEST_RESPONSE			0x1470
#घोषणा		REQUEST_TYPE(x)					(((x) & 0xf) << 0)
#घोषणा		RESPONSE_TYPE_MASK				0x000000F0
#घोषणा		RESPONSE_TYPE_SHIFT				4
#घोषणा VM_L2_CNTL					0x1400
#घोषणा		ENABLE_L2_CACHE					(1 << 0)
#घोषणा		ENABLE_L2_FRAGMENT_PROCESSING			(1 << 1)
#घोषणा		ENABLE_L2_PTE_CACHE_LRU_UPDATE_BY_WRITE		(1 << 9)
#घोषणा		EFFECTIVE_L2_QUEUE_SIZE(x)			(((x) & 7) << 14)
#घोषणा VM_L2_CNTL2					0x1404
#घोषणा		INVALIDATE_ALL_L1_TLBS				(1 << 0)
#घोषणा		INVALIDATE_L2_CACHE				(1 << 1)
#घोषणा VM_L2_CNTL3					0x1408
#घोषणा		BANK_SELECT(x)					((x) << 0)
#घोषणा		CACHE_UPDATE_MODE(x)				((x) << 6)
#घोषणा	VM_L2_STATUS					0x140C
#घोषणा		L2_BUSY						(1 << 0)
#घोषणा	VM_CONTEXT1_PROTECTION_FAULT_ADDR		0x14FC
#घोषणा	VM_CONTEXT1_PROTECTION_FAULT_STATUS		0x14DC

#घोषणा	WAIT_UNTIL					0x8040

#घोषणा	SRBM_STATUS				        0x0E50
#घोषणा		RLC_RQ_PENDING 				(1 << 3)
#घोषणा		GRBM_RQ_PENDING 			(1 << 5)
#घोषणा		VMC_BUSY 				(1 << 8)
#घोषणा		MCB_BUSY 				(1 << 9)
#घोषणा		MCB_NON_DISPLAY_BUSY 			(1 << 10)
#घोषणा		MCC_BUSY 				(1 << 11)
#घोषणा		MCD_BUSY 				(1 << 12)
#घोषणा		SEM_BUSY 				(1 << 14)
#घोषणा		RLC_BUSY 				(1 << 15)
#घोषणा		IH_BUSY 				(1 << 17)
#घोषणा	SRBM_STATUS2				        0x0EC4
#घोषणा		DMA_BUSY 				(1 << 5)
#घोषणा	SRBM_SOFT_RESET				        0x0E60
#घोषणा		SRBM_SOFT_RESET_ALL_MASK    	       	0x00FEEFA6
#घोषणा		SOFT_RESET_BIF				(1 << 1)
#घोषणा		SOFT_RESET_CG				(1 << 2)
#घोषणा		SOFT_RESET_DC				(1 << 5)
#घोषणा		SOFT_RESET_GRBM				(1 << 8)
#घोषणा		SOFT_RESET_HDP				(1 << 9)
#घोषणा		SOFT_RESET_IH				(1 << 10)
#घोषणा		SOFT_RESET_MC				(1 << 11)
#घोषणा		SOFT_RESET_RLC				(1 << 13)
#घोषणा		SOFT_RESET_ROM				(1 << 14)
#घोषणा		SOFT_RESET_SEM				(1 << 15)
#घोषणा		SOFT_RESET_VMC				(1 << 17)
#घोषणा		SOFT_RESET_DMA				(1 << 20)
#घोषणा		SOFT_RESET_TST				(1 << 21)
#घोषणा		SOFT_RESET_REGBB			(1 << 22)
#घोषणा		SOFT_RESET_ORB				(1 << 23)

#घोषणा SRBM_READ_ERROR					0xE98
#घोषणा SRBM_INT_CNTL					0xEA0
#घोषणा SRBM_INT_ACK					0xEA8

/* display watermarks */
#घोषणा	DC_LB_MEMORY_SPLIT				  0x6b0c
#घोषणा	PRIORITY_A_CNT			                  0x6b18
#घोषणा		PRIORITY_MARK_MASK			  0x7fff
#घोषणा		PRIORITY_OFF				  (1 << 16)
#घोषणा		PRIORITY_ALWAYS_ON			  (1 << 20)
#घोषणा	PRIORITY_B_CNT			                  0x6b1c
#घोषणा	PIPE0_ARBITRATION_CONTROL3			  0x0bf0
#       define LATENCY_WATERMARK_MASK(x)                  ((x) << 16)
#घोषणा	PIPE0_LATENCY_CONTROL			          0x0bf4
#       define LATENCY_LOW_WATERMARK(x)                   ((x) << 0)
#       define LATENCY_HIGH_WATERMARK(x)                  ((x) << 16)

#घोषणा	PIPE0_DMIF_BUFFER_CONTROL			  0x0ca0
#       define DMIF_BUFFERS_ALLOCATED(x)                  ((x) << 0)
#       define DMIF_BUFFERS_ALLOCATED_COMPLETED           (1 << 4)

#घोषणा IH_RB_CNTL                                        0x3e00
#       define IH_RB_ENABLE                               (1 << 0)
#       define IH_IB_SIZE(x)                              ((x) << 1) /* log2 */
#       define IH_RB_FULL_DRAIN_ENABLE                    (1 << 6)
#       define IH_WPTR_WRITEBACK_ENABLE                   (1 << 8)
#       define IH_WPTR_WRITEBACK_TIMER(x)                 ((x) << 9) /* log2 */
#       define IH_WPTR_OVERFLOW_ENABLE                    (1 << 16)
#       define IH_WPTR_OVERFLOW_CLEAR                     (1 << 31)
#घोषणा IH_RB_BASE                                        0x3e04
#घोषणा IH_RB_RPTR                                        0x3e08
#घोषणा IH_RB_WPTR                                        0x3e0c
#       define RB_OVERFLOW                                (1 << 0)
#       define WPTR_OFFSET_MASK                           0x3fffc
#घोषणा IH_RB_WPTR_ADDR_HI                                0x3e10
#घोषणा IH_RB_WPTR_ADDR_LO                                0x3e14
#घोषणा IH_CNTL                                           0x3e18
#       define ENABLE_INTR                                (1 << 0)
#       define IH_MC_SWAP(x)                              ((x) << 1)
#       define IH_MC_SWAP_NONE                            0
#       define IH_MC_SWAP_16BIT                           1
#       define IH_MC_SWAP_32BIT                           2
#       define IH_MC_SWAP_64BIT                           3
#       define RPTR_REARM                                 (1 << 4)
#       define MC_WRREQ_CREDIT(x)                         ((x) << 15)
#       define MC_WR_CLEAN_CNT(x)                         ((x) << 20)

#घोषणा CP_INT_CNTL                                     0xc124
#       define CNTX_BUSY_INT_ENABLE                     (1 << 19)
#       define CNTX_EMPTY_INT_ENABLE                    (1 << 20)
#       define SCRATCH_INT_ENABLE                       (1 << 25)
#       define TIME_STAMP_INT_ENABLE                    (1 << 26)
#       define IB2_INT_ENABLE                           (1 << 29)
#       define IB1_INT_ENABLE                           (1 << 30)
#       define RB_INT_ENABLE                            (1 << 31)
#घोषणा CP_INT_STATUS                                   0xc128
#       define SCRATCH_INT_STAT                         (1 << 25)
#       define TIME_STAMP_INT_STAT                      (1 << 26)
#       define IB2_INT_STAT                             (1 << 29)
#       define IB1_INT_STAT                             (1 << 30)
#       define RB_INT_STAT                              (1 << 31)

#घोषणा GRBM_INT_CNTL                                   0x8060
#       define RDERR_INT_ENABLE                         (1 << 0)
#       define GUI_IDLE_INT_ENABLE                      (1 << 19)

/* 0x6e98, 0x7a98, 0x10698, 0x11298, 0x11e98, 0x12a98 */
#घोषणा CRTC_STATUS_FRAME_COUNT                         0x6e98

/* 0x6bb8, 0x77b8, 0x103b8, 0x10fb8, 0x11bb8, 0x127b8 */
#घोषणा VLINE_STATUS                                    0x6bb8
#       define VLINE_OCCURRED                           (1 << 0)
#       define VLINE_ACK                                (1 << 4)
#       define VLINE_STAT                               (1 << 12)
#       define VLINE_INTERRUPT                          (1 << 16)
#       define VLINE_INTERRUPT_TYPE                     (1 << 17)
/* 0x6bbc, 0x77bc, 0x103bc, 0x10fbc, 0x11bbc, 0x127bc */
#घोषणा VBLANK_STATUS                                   0x6bbc
#       define VBLANK_OCCURRED                          (1 << 0)
#       define VBLANK_ACK                               (1 << 4)
#       define VBLANK_STAT                              (1 << 12)
#       define VBLANK_INTERRUPT                         (1 << 16)
#       define VBLANK_INTERRUPT_TYPE                    (1 << 17)

/* 0x6b40, 0x7740, 0x10340, 0x10f40, 0x11b40, 0x12740 */
#घोषणा INT_MASK                                        0x6b40
#       define VBLANK_INT_MASK                          (1 << 0)
#       define VLINE_INT_MASK                           (1 << 4)

#घोषणा DISP_INTERRUPT_STATUS                           0x60f4
#       define LB_D1_VLINE_INTERRUPT                    (1 << 2)
#       define LB_D1_VBLANK_INTERRUPT                   (1 << 3)
#       define DC_HPD1_INTERRUPT                        (1 << 17)
#       define DC_HPD1_RX_INTERRUPT                     (1 << 18)
#       define DACA_AUTODETECT_INTERRUPT                (1 << 22)
#       define DACB_AUTODETECT_INTERRUPT                (1 << 23)
#       define DC_I2C_SW_DONE_INTERRUPT                 (1 << 24)
#       define DC_I2C_HW_DONE_INTERRUPT                 (1 << 25)
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE                  0x60f8
#       define LB_D2_VLINE_INTERRUPT                    (1 << 2)
#       define LB_D2_VBLANK_INTERRUPT                   (1 << 3)
#       define DC_HPD2_INTERRUPT                        (1 << 17)
#       define DC_HPD2_RX_INTERRUPT                     (1 << 18)
#       define DISP_TIMER_INTERRUPT                     (1 << 24)
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE2                 0x60fc
#       define LB_D3_VLINE_INTERRUPT                    (1 << 2)
#       define LB_D3_VBLANK_INTERRUPT                   (1 << 3)
#       define DC_HPD3_INTERRUPT                        (1 << 17)
#       define DC_HPD3_RX_INTERRUPT                     (1 << 18)
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE3                 0x6100
#       define LB_D4_VLINE_INTERRUPT                    (1 << 2)
#       define LB_D4_VBLANK_INTERRUPT                   (1 << 3)
#       define DC_HPD4_INTERRUPT                        (1 << 17)
#       define DC_HPD4_RX_INTERRUPT                     (1 << 18)
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE4                 0x614c
#       define LB_D5_VLINE_INTERRUPT                    (1 << 2)
#       define LB_D5_VBLANK_INTERRUPT                   (1 << 3)
#       define DC_HPD5_INTERRUPT                        (1 << 17)
#       define DC_HPD5_RX_INTERRUPT                     (1 << 18)
#घोषणा DISP_INTERRUPT_STATUS_CONTINUE5                 0x6150
#       define LB_D6_VLINE_INTERRUPT                    (1 << 2)
#       define LB_D6_VBLANK_INTERRUPT                   (1 << 3)
#       define DC_HPD6_INTERRUPT                        (1 << 17)
#       define DC_HPD6_RX_INTERRUPT                     (1 << 18)

/* 0x6858, 0x7458, 0x10058, 0x10c58, 0x11858, 0x12458 */
#घोषणा GRPH_INT_STATUS                                 0x6858
#       define GRPH_PFLIP_INT_OCCURRED                  (1 << 0)
#       define GRPH_PFLIP_INT_CLEAR                     (1 << 8)
/* 0x685c, 0x745c, 0x1005c, 0x10c5c, 0x1185c, 0x1245c */
#घोषणा	GRPH_INT_CONTROL			        0x685c
#       define GRPH_PFLIP_INT_MASK                      (1 << 0)
#       define GRPH_PFLIP_INT_TYPE                      (1 << 8)

#घोषणा	DACA_AUTODETECT_INT_CONTROL			0x66c8
#घोषणा	DACB_AUTODETECT_INT_CONTROL			0x67c8

#घोषणा DC_HPD1_INT_STATUS                              0x601c
#घोषणा DC_HPD2_INT_STATUS                              0x6028
#घोषणा DC_HPD3_INT_STATUS                              0x6034
#घोषणा DC_HPD4_INT_STATUS                              0x6040
#घोषणा DC_HPD5_INT_STATUS                              0x604c
#घोषणा DC_HPD6_INT_STATUS                              0x6058
#       define DC_HPDx_INT_STATUS                       (1 << 0)
#       define DC_HPDx_SENSE                            (1 << 1)
#       define DC_HPDx_RX_INT_STATUS                    (1 << 8)

#घोषणा DC_HPD1_INT_CONTROL                             0x6020
#घोषणा DC_HPD2_INT_CONTROL                             0x602c
#घोषणा DC_HPD3_INT_CONTROL                             0x6038
#घोषणा DC_HPD4_INT_CONTROL                             0x6044
#घोषणा DC_HPD5_INT_CONTROL                             0x6050
#घोषणा DC_HPD6_INT_CONTROL                             0x605c
#       define DC_HPDx_INT_ACK                          (1 << 0)
#       define DC_HPDx_INT_POLARITY                     (1 << 8)
#       define DC_HPDx_INT_EN                           (1 << 16)
#       define DC_HPDx_RX_INT_ACK                       (1 << 20)
#       define DC_HPDx_RX_INT_EN                        (1 << 24)

#घोषणा DC_HPD1_CONTROL                                   0x6024
#घोषणा DC_HPD2_CONTROL                                   0x6030
#घोषणा DC_HPD3_CONTROL                                   0x603c
#घोषणा DC_HPD4_CONTROL                                   0x6048
#घोषणा DC_HPD5_CONTROL                                   0x6054
#घोषणा DC_HPD6_CONTROL                                   0x6060
#       define DC_HPDx_CONNECTION_TIMER(x)                ((x) << 0)
#       define DC_HPDx_RX_INT_TIMER(x)                    ((x) << 16)
#       define DC_HPDx_EN                                 (1 << 28)

/* DCE4/5/6 FMT blocks */
#घोषणा FMT_DYNAMIC_EXP_CNTL                 0x6fb4
#       define FMT_DYNAMIC_EXP_EN            (1 << 0)
#       define FMT_DYNAMIC_EXP_MODE          (1 << 4)
        /* 0 = 10bit -> 12bit, 1 = 8bit -> 12bit */
#घोषणा FMT_CONTROL                          0x6fb8
#       define FMT_PIXEL_ENCODING            (1 << 16)
        /* 0 = RGB 4:4:4 or YCbCr 4:4:4, 1 = YCbCr 4:2:2 */
#घोषणा FMT_BIT_DEPTH_CONTROL                0x6fc8
#       define FMT_TRUNCATE_EN               (1 << 0)
#       define FMT_TRUNCATE_DEPTH            (1 << 4)
#       define FMT_SPATIAL_DITHER_EN         (1 << 8)
#       define FMT_SPATIAL_DITHER_MODE(x)    ((x) << 9)
#       define FMT_SPATIAL_DITHER_DEPTH      (1 << 12)
#       define FMT_FRAME_RANDOM_ENABLE       (1 << 13)
#       define FMT_RGB_RANDOM_ENABLE         (1 << 14)
#       define FMT_HIGHPASS_RANDOM_ENABLE    (1 << 15)
#       define FMT_TEMPORAL_DITHER_EN        (1 << 16)
#       define FMT_TEMPORAL_DITHER_DEPTH     (1 << 20)
#       define FMT_TEMPORAL_DITHER_OFFSET(x) ((x) << 21)
#       define FMT_TEMPORAL_LEVEL            (1 << 24)
#       define FMT_TEMPORAL_DITHER_RESET     (1 << 25)
#       define FMT_25FRC_SEL(x)              ((x) << 26)
#       define FMT_50FRC_SEL(x)              ((x) << 28)
#       define FMT_75FRC_SEL(x)              ((x) << 30)
#घोषणा FMT_CLAMP_CONTROL                    0x6fe4
#       define FMT_CLAMP_DATA_EN             (1 << 0)
#       define FMT_CLAMP_COLOR_FORMAT(x)     ((x) << 16)
#       define FMT_CLAMP_6BPC                0
#       define FMT_CLAMP_8BPC                1
#       define FMT_CLAMP_10BPC               2

/* ASYNC DMA */
#घोषणा DMA_RB_RPTR                                       0xd008
#घोषणा DMA_RB_WPTR                                       0xd00c

#घोषणा DMA_CNTL                                          0xd02c
#       define TRAP_ENABLE                                (1 << 0)
#       define SEM_INCOMPLETE_INT_ENABLE                  (1 << 1)
#       define SEM_WAIT_INT_ENABLE                        (1 << 2)
#       define DATA_SWAP_ENABLE                           (1 << 3)
#       define FENCE_SWAP_ENABLE                          (1 << 4)
#       define CTXEMPTY_INT_ENABLE                        (1 << 28)
#घोषणा DMA_TILING_CONFIG  				  0xD0B8

#घोषणा CAYMAN_DMA1_CNTL                                  0xd82c

/* async DMA packets */
#घोषणा DMA_PACKET(cmd, sub_cmd, n) ((((cmd) & 0xF) << 28) |    \
                                    (((sub_cmd) & 0xFF) << 20) |\
                                    (((n) & 0xFFFFF) << 0))
#घोषणा GET_DMA_CMD(h) (((h) & 0xf0000000) >> 28)
#घोषणा GET_DMA_COUNT(h) ((h) & 0x000fffff)
#घोषणा GET_DMA_SUB_CMD(h) (((h) & 0x0ff00000) >> 20)

/* async DMA Packet types */
#घोषणा	DMA_PACKET_WRITE                        0x2
#घोषणा	DMA_PACKET_COPY                         0x3
#घोषणा	DMA_PACKET_INसूचीECT_BUFFER              0x4
#घोषणा	DMA_PACKET_SEMAPHORE                    0x5
#घोषणा	DMA_PACKET_FENCE                        0x6
#घोषणा	DMA_PACKET_TRAP                         0x7
#घोषणा	DMA_PACKET_SRBM_WRITE                   0x9
#घोषणा	DMA_PACKET_CONSTANT_FILL                0xd
#घोषणा	DMA_PACKET_NOP                          0xf

/* PIF PHY0 indirect regs */
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
/* PIF PHY1 indirect regs */
#घोषणा PB1_PIF_CNTL                                      0x10
#घोषणा PB1_PIF_PAIRING                                   0x11
#घोषणा PB1_PIF_PWRDOWN_0                                 0x12
#घोषणा PB1_PIF_PWRDOWN_1                                 0x13
/* PCIE PORT indirect regs */
#घोषणा PCIE_LC_CNTL                                      0xa0
#       define LC_L0S_INACTIVITY(x)                       ((x) << 8)
#       define LC_L0S_INACTIVITY_MASK                     (0xf << 8)
#       define LC_L0S_INACTIVITY_SHIFT                    8
#       define LC_L1_INACTIVITY(x)                        ((x) << 12)
#       define LC_L1_INACTIVITY_MASK                      (0xf << 12)
#       define LC_L1_INACTIVITY_SHIFT                     12
#       define LC_PMI_TO_L1_DIS                           (1 << 16)
#       define LC_ASPM_TO_L1_DIS                          (1 << 24)
#घोषणा PCIE_LC_TRAINING_CNTL                             0xa1 /* PCIE_P */
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
#घोषणा PCIE_LC_SPEED_CNTL                                0xa4 /* PCIE_P */
#       define LC_GEN2_EN_STRAP                           (1 << 0)
#       define LC_TARGET_LINK_SPEED_OVERRIDE_EN           (1 << 1)
#       define LC_FORCE_EN_HW_SPEED_CHANGE                (1 << 5)
#       define LC_FORCE_DIS_HW_SPEED_CHANGE               (1 << 6)
#       define LC_SPEED_CHANGE_ATTEMPTS_ALLOWED_MASK      (0x3 << 8)
#       define LC_SPEED_CHANGE_ATTEMPTS_ALLOWED_SHIFT     3
#       define LC_CURRENT_DATA_RATE                       (1 << 11)
#       define LC_HW_VOLTAGE_IF_CONTROL(x)                ((x) << 12)
#       define LC_HW_VOLTAGE_IF_CONTROL_MASK              (3 << 12)
#       define LC_HW_VOLTAGE_IF_CONTROL_SHIFT             12
#       define LC_VOLTAGE_TIMER_SEL_MASK                  (0xf << 14)
#       define LC_CLR_FAILED_SPD_CHANGE_CNT               (1 << 21)
#       define LC_OTHER_SIDE_EVER_SENT_GEN2               (1 << 23)
#       define LC_OTHER_SIDE_SUPPORTS_GEN2                (1 << 24)
#घोषणा MM_CFGREGS_CNTL                                   0x544c
#       define MM_WR_TO_CFG_EN                            (1 << 3)
#घोषणा LINK_CNTL2                                        0x88 /* F0 */
#       define TARGET_LINK_SPEED_MASK                     (0xf << 0)
#       define SELECTABLE_DEEMPHASIS                      (1 << 6)


/*
 * UVD
 */
#घोषणा UVD_UDEC_ADDR_CONFIG				0xef4c
#घोषणा UVD_UDEC_DB_ADDR_CONFIG				0xef50
#घोषणा UVD_UDEC_DBW_ADDR_CONFIG			0xef54
#घोषणा UVD_NO_OP					0xeffc
#घोषणा UVD_RBC_RB_RPTR					0xf690
#घोषणा UVD_RBC_RB_WPTR					0xf694
#घोषणा UVD_STATUS					0xf6bc

/*
 * PM4
 */
#घोषणा PACKET0(reg, n)	((RADEON_PACKET_TYPE0 << 30) |			\
			 (((reg) >> 2) & 0xFFFF) |			\
			 ((n) & 0x3FFF) << 16)
#घोषणा CP_PACKET2			0x80000000
#घोषणा		PACKET2_PAD_SHIFT		0
#घोषणा		PACKET2_PAD_MASK		(0x3fffffff << 0)

#घोषणा PACKET2(v)	(CP_PACKET2 | REG_SET(PACKET2_PAD, (v)))

#घोषणा PACKET3(op, n)	((RADEON_PACKET_TYPE3 << 30) |			\
			 (((op) & 0xFF) << 8) |				\
			 ((n) & 0x3FFF) << 16)

/* Packet 3 types */
#घोषणा	PACKET3_NOP					0x10
#घोषणा	PACKET3_SET_BASE				0x11
#घोषणा	PACKET3_CLEAR_STATE				0x12
#घोषणा	PACKET3_INDEX_BUFFER_SIZE			0x13
#घोषणा	PACKET3_DISPATCH_सूचीECT				0x15
#घोषणा	PACKET3_DISPATCH_INसूचीECT			0x16
#घोषणा	PACKET3_INसूचीECT_BUFFER_END			0x17
#घोषणा	PACKET3_MODE_CONTROL				0x18
#घोषणा	PACKET3_SET_PREDICATION				0x20
#घोषणा	PACKET3_REG_RMW					0x21
#घोषणा	PACKET3_COND_EXEC				0x22
#घोषणा	PACKET3_PRED_EXEC				0x23
#घोषणा	PACKET3_DRAW_INसूचीECT				0x24
#घोषणा	PACKET3_DRAW_INDEX_INसूचीECT			0x25
#घोषणा	PACKET3_INDEX_BASE				0x26
#घोषणा	PACKET3_DRAW_INDEX_2				0x27
#घोषणा	PACKET3_CONTEXT_CONTROL				0x28
#घोषणा	PACKET3_DRAW_INDEX_OFFSET			0x29
#घोषणा	PACKET3_INDEX_TYPE				0x2A
#घोषणा	PACKET3_DRAW_INDEX				0x2B
#घोषणा	PACKET3_DRAW_INDEX_AUTO				0x2D
#घोषणा	PACKET3_DRAW_INDEX_IMMD				0x2E
#घोषणा	PACKET3_NUM_INSTANCES				0x2F
#घोषणा	PACKET3_DRAW_INDEX_MULTI_AUTO			0x30
#घोषणा	PACKET3_STRMOUT_BUFFER_UPDATE			0x34
#घोषणा	PACKET3_DRAW_INDEX_OFFSET_2			0x35
#घोषणा	PACKET3_DRAW_INDEX_MULTI_ELEMENT		0x36
#घोषणा	PACKET3_MEM_SEMAPHORE				0x39
#घोषणा	PACKET3_MPEG_INDEX				0x3A
#घोषणा	PACKET3_COPY_DW					0x3B
#घोषणा	PACKET3_WAIT_REG_MEM				0x3C
#घोषणा	PACKET3_MEM_WRITE				0x3D
#घोषणा	PACKET3_INसूचीECT_BUFFER				0x32
#घोषणा	PACKET3_CP_DMA					0x41
/* 1. header
 * 2. SRC_ADDR_LO or DATA [31:0]
 * 3. CP_SYNC [31] | SRC_SEL [30:29] | ENGINE [27] | DST_SEL [21:20] |
 *    SRC_ADDR_HI [7:0]
 * 4. DST_ADDR_LO [31:0]
 * 5. DST_ADDR_HI [7:0]
 * 6. COMMAND [29:22] | BYTE_COUNT [20:0]
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
#घोषणा	PACKET3_PFP_SYNC_ME				0x42
#घोषणा	PACKET3_SURFACE_SYNC				0x43
#              define PACKET3_CB0_DEST_BASE_ENA    (1 << 6)
#              define PACKET3_CB1_DEST_BASE_ENA    (1 << 7)
#              define PACKET3_CB2_DEST_BASE_ENA    (1 << 8)
#              define PACKET3_CB3_DEST_BASE_ENA    (1 << 9)
#              define PACKET3_CB4_DEST_BASE_ENA    (1 << 10)
#              define PACKET3_CB5_DEST_BASE_ENA    (1 << 11)
#              define PACKET3_CB6_DEST_BASE_ENA    (1 << 12)
#              define PACKET3_CB7_DEST_BASE_ENA    (1 << 13)
#              define PACKET3_DB_DEST_BASE_ENA     (1 << 14)
#              define PACKET3_CB8_DEST_BASE_ENA    (1 << 15)
#              define PACKET3_CB9_DEST_BASE_ENA    (1 << 16)
#              define PACKET3_CB10_DEST_BASE_ENA   (1 << 17)
#              define PACKET3_CB11_DEST_BASE_ENA   (1 << 18)
#              define PACKET3_FULL_CACHE_ENA       (1 << 20)
#              define PACKET3_TC_ACTION_ENA        (1 << 23)
#              define PACKET3_VC_ACTION_ENA        (1 << 24)
#              define PACKET3_CB_ACTION_ENA        (1 << 25)
#              define PACKET3_DB_ACTION_ENA        (1 << 26)
#              define PACKET3_SH_ACTION_ENA        (1 << 27)
#              define PACKET3_SX_ACTION_ENA        (1 << 28)
#घोषणा	PACKET3_ME_INITIALIZE				0x44
#घोषणा		PACKET3_ME_INITIALIZE_DEVICE_ID(x) ((x) << 16)
#घोषणा	PACKET3_COND_WRITE				0x45
#घोषणा	PACKET3_EVENT_WRITE				0x46
#घोषणा	PACKET3_EVENT_WRITE_EOP				0x47
#घोषणा	PACKET3_EVENT_WRITE_EOS				0x48
#घोषणा	PACKET3_PREAMBLE_CNTL				0x4A
#              define PACKET3_PREAMBLE_BEGIN_CLEAR_STATE     (2 << 28)
#              define PACKET3_PREAMBLE_END_CLEAR_STATE       (3 << 28)
#घोषणा	PACKET3_RB_OFFSET				0x4B
#घोषणा	PACKET3_ALU_PS_CONST_BUFFER_COPY		0x4C
#घोषणा	PACKET3_ALU_VS_CONST_BUFFER_COPY		0x4D
#घोषणा	PACKET3_ALU_PS_CONST_UPDATE		        0x4E
#घोषणा	PACKET3_ALU_VS_CONST_UPDATE		        0x4F
#घोषणा	PACKET3_ONE_REG_WRITE				0x57
#घोषणा	PACKET3_SET_CONFIG_REG				0x68
#घोषणा		PACKET3_SET_CONFIG_REG_START			0x00008000
#घोषणा		PACKET3_SET_CONFIG_REG_END			0x0000ac00
#घोषणा	PACKET3_SET_CONTEXT_REG				0x69
#घोषणा		PACKET3_SET_CONTEXT_REG_START			0x00028000
#घोषणा		PACKET3_SET_CONTEXT_REG_END			0x00029000
#घोषणा	PACKET3_SET_ALU_CONST				0x6A
/* alu स्थिर buffers only; no reg file */
#घोषणा	PACKET3_SET_BOOL_CONST				0x6B
#घोषणा		PACKET3_SET_BOOL_CONST_START			0x0003a500
#घोषणा		PACKET3_SET_BOOL_CONST_END			0x0003a518
#घोषणा	PACKET3_SET_LOOP_CONST				0x6C
#घोषणा		PACKET3_SET_LOOP_CONST_START			0x0003a200
#घोषणा		PACKET3_SET_LOOP_CONST_END			0x0003a500
#घोषणा	PACKET3_SET_RESOURCE				0x6D
#घोषणा		PACKET3_SET_RESOURCE_START			0x00030000
#घोषणा		PACKET3_SET_RESOURCE_END			0x00038000
#घोषणा	PACKET3_SET_SAMPLER				0x6E
#घोषणा		PACKET3_SET_SAMPLER_START			0x0003c000
#घोषणा		PACKET3_SET_SAMPLER_END				0x0003c600
#घोषणा	PACKET3_SET_CTL_CONST				0x6F
#घोषणा		PACKET3_SET_CTL_CONST_START			0x0003cff0
#घोषणा		PACKET3_SET_CTL_CONST_END			0x0003ff0c
#घोषणा	PACKET3_SET_RESOURCE_OFFSET			0x70
#घोषणा	PACKET3_SET_ALU_CONST_VS			0x71
#घोषणा	PACKET3_SET_ALU_CONST_DI			0x72
#घोषणा	PACKET3_SET_CONTEXT_REG_INसूचीECT		0x73
#घोषणा	PACKET3_SET_RESOURCE_INसूचीECT			0x74
#घोषणा	PACKET3_SET_APPEND_CNT			        0x75
/* SET_APPEND_CNT - करोcumentation
 * 1. header
 * 2. COMMAND
 *  1:0 - SOURCE SEL
 *  15:2 - Reserved
 *  31:16 - WR_REG_OFFSET - context रेजिस्टर to ग_लिखो source data to.
 *          (one of R_02872C_GDS_APPEND_COUNT_0-11)
 * 3. CONTROL
 *  (क्रम source == mem)
 *  31:2 SRC_ADDRESS_LO
 *  0:1 SWAP
 *  (क्रम source == GDS)
 *  31:0 GDS offset
 *  (क्रम source == DATA)
 *  31:0 DATA
 *  (क्रम source == REG)
 *  31:0 REG
 * 4. SRC_ADDRESS_HI[7:0]
 * kernel driver 2.44 only supports SRC == MEM.
 */
#घोषणा PACKET3_SET_APPEND_CNT_SRC_SELECT(x) ((x) << 0)
#घोषणा G_PACKET3_SET_APPEND_CNT_SRC_SELECT(x) ((x & 0x3) >> 0)
/* source is from the data in CONTROL */
#घोषणा PACKET3_SAC_SRC_SEL_DATA 0x0
/* source is from रेजिस्टर */
#घोषणा PACKET3_SAC_SRC_SEL_REG  0x1
/* source is from GDS offset in CONTROL */
#घोषणा PACKET3_SAC_SRC_SEL_GDS  0x2
/* source is from memory address */
#घोषणा PACKET3_SAC_SRC_SEL_MEM  0x3

#घोषणा	SQ_RESOURCE_CONSTANT_WORD7_0				0x3001c
#घोषणा		S__SQ_CONSTANT_TYPE(x)			(((x) & 3) << 30)
#घोषणा		G__SQ_CONSTANT_TYPE(x)			(((x) >> 30) & 3)
#घोषणा			SQ_TEX_VTX_INVALID_TEXTURE			0x0
#घोषणा			SQ_TEX_VTX_INVALID_BUFFER			0x1
#घोषणा			SQ_TEX_VTX_VALID_TEXTURE			0x2
#घोषणा			SQ_TEX_VTX_VALID_BUFFER				0x3

#घोषणा VGT_VTX_VECT_EJECT_REG				0x88b0

#घोषणा SQ_CONST_MEM_BASE				0x8df8

#घोषणा SQ_ESGS_RING_BASE				0x8c40
#घोषणा SQ_ESGS_RING_SIZE				0x8c44
#घोषणा SQ_GSVS_RING_BASE				0x8c48
#घोषणा SQ_GSVS_RING_SIZE				0x8c4c
#घोषणा SQ_ESTMP_RING_BASE				0x8c50
#घोषणा SQ_ESTMP_RING_SIZE				0x8c54
#घोषणा SQ_GSTMP_RING_BASE				0x8c58
#घोषणा SQ_GSTMP_RING_SIZE				0x8c5c
#घोषणा SQ_VSTMP_RING_BASE				0x8c60
#घोषणा SQ_VSTMP_RING_SIZE				0x8c64
#घोषणा SQ_PSTMP_RING_BASE				0x8c68
#घोषणा SQ_PSTMP_RING_SIZE				0x8c6c
#घोषणा SQ_LSTMP_RING_BASE				0x8e10
#घोषणा SQ_LSTMP_RING_SIZE				0x8e14
#घोषणा SQ_HSTMP_RING_BASE				0x8e18
#घोषणा SQ_HSTMP_RING_SIZE				0x8e1c
#घोषणा VGT_TF_RING_SIZE				0x8988

#घोषणा SQ_ESGS_RING_ITEMSIZE				0x28900
#घोषणा SQ_GSVS_RING_ITEMSIZE				0x28904
#घोषणा SQ_ESTMP_RING_ITEMSIZE				0x28908
#घोषणा SQ_GSTMP_RING_ITEMSIZE				0x2890c
#घोषणा SQ_VSTMP_RING_ITEMSIZE				0x28910
#घोषणा SQ_PSTMP_RING_ITEMSIZE				0x28914
#घोषणा SQ_LSTMP_RING_ITEMSIZE				0x28830
#घोषणा SQ_HSTMP_RING_ITEMSIZE				0x28834

#घोषणा SQ_GS_VERT_ITEMSIZE				0x2891c
#घोषणा SQ_GS_VERT_ITEMSIZE_1				0x28920
#घोषणा SQ_GS_VERT_ITEMSIZE_2				0x28924
#घोषणा SQ_GS_VERT_ITEMSIZE_3				0x28928
#घोषणा SQ_GSVS_RING_OFFSET_1				0x2892c
#घोषणा SQ_GSVS_RING_OFFSET_2				0x28930
#घोषणा SQ_GSVS_RING_OFFSET_3				0x28934

#घोषणा SQ_ALU_CONST_BUFFER_SIZE_PS_0			0x28140
#घोषणा SQ_ALU_CONST_BUFFER_SIZE_HS_0			0x28f80

#घोषणा SQ_ALU_CONST_CACHE_PS_0				0x28940
#घोषणा SQ_ALU_CONST_CACHE_PS_1				0x28944
#घोषणा SQ_ALU_CONST_CACHE_PS_2				0x28948
#घोषणा SQ_ALU_CONST_CACHE_PS_3				0x2894c
#घोषणा SQ_ALU_CONST_CACHE_PS_4				0x28950
#घोषणा SQ_ALU_CONST_CACHE_PS_5				0x28954
#घोषणा SQ_ALU_CONST_CACHE_PS_6				0x28958
#घोषणा SQ_ALU_CONST_CACHE_PS_7				0x2895c
#घोषणा SQ_ALU_CONST_CACHE_PS_8				0x28960
#घोषणा SQ_ALU_CONST_CACHE_PS_9				0x28964
#घोषणा SQ_ALU_CONST_CACHE_PS_10			0x28968
#घोषणा SQ_ALU_CONST_CACHE_PS_11			0x2896c
#घोषणा SQ_ALU_CONST_CACHE_PS_12			0x28970
#घोषणा SQ_ALU_CONST_CACHE_PS_13			0x28974
#घोषणा SQ_ALU_CONST_CACHE_PS_14			0x28978
#घोषणा SQ_ALU_CONST_CACHE_PS_15			0x2897c
#घोषणा SQ_ALU_CONST_CACHE_VS_0				0x28980
#घोषणा SQ_ALU_CONST_CACHE_VS_1				0x28984
#घोषणा SQ_ALU_CONST_CACHE_VS_2				0x28988
#घोषणा SQ_ALU_CONST_CACHE_VS_3				0x2898c
#घोषणा SQ_ALU_CONST_CACHE_VS_4				0x28990
#घोषणा SQ_ALU_CONST_CACHE_VS_5				0x28994
#घोषणा SQ_ALU_CONST_CACHE_VS_6				0x28998
#घोषणा SQ_ALU_CONST_CACHE_VS_7				0x2899c
#घोषणा SQ_ALU_CONST_CACHE_VS_8				0x289a0
#घोषणा SQ_ALU_CONST_CACHE_VS_9				0x289a4
#घोषणा SQ_ALU_CONST_CACHE_VS_10			0x289a8
#घोषणा SQ_ALU_CONST_CACHE_VS_11			0x289ac
#घोषणा SQ_ALU_CONST_CACHE_VS_12			0x289b0
#घोषणा SQ_ALU_CONST_CACHE_VS_13			0x289b4
#घोषणा SQ_ALU_CONST_CACHE_VS_14			0x289b8
#घोषणा SQ_ALU_CONST_CACHE_VS_15			0x289bc
#घोषणा SQ_ALU_CONST_CACHE_GS_0				0x289c0
#घोषणा SQ_ALU_CONST_CACHE_GS_1				0x289c4
#घोषणा SQ_ALU_CONST_CACHE_GS_2				0x289c8
#घोषणा SQ_ALU_CONST_CACHE_GS_3				0x289cc
#घोषणा SQ_ALU_CONST_CACHE_GS_4				0x289d0
#घोषणा SQ_ALU_CONST_CACHE_GS_5				0x289d4
#घोषणा SQ_ALU_CONST_CACHE_GS_6				0x289d8
#घोषणा SQ_ALU_CONST_CACHE_GS_7				0x289dc
#घोषणा SQ_ALU_CONST_CACHE_GS_8				0x289e0
#घोषणा SQ_ALU_CONST_CACHE_GS_9				0x289e4
#घोषणा SQ_ALU_CONST_CACHE_GS_10			0x289e8
#घोषणा SQ_ALU_CONST_CACHE_GS_11			0x289ec
#घोषणा SQ_ALU_CONST_CACHE_GS_12			0x289f0
#घोषणा SQ_ALU_CONST_CACHE_GS_13			0x289f4
#घोषणा SQ_ALU_CONST_CACHE_GS_14			0x289f8
#घोषणा SQ_ALU_CONST_CACHE_GS_15			0x289fc
#घोषणा SQ_ALU_CONST_CACHE_HS_0				0x28f00
#घोषणा SQ_ALU_CONST_CACHE_HS_1				0x28f04
#घोषणा SQ_ALU_CONST_CACHE_HS_2				0x28f08
#घोषणा SQ_ALU_CONST_CACHE_HS_3				0x28f0c
#घोषणा SQ_ALU_CONST_CACHE_HS_4				0x28f10
#घोषणा SQ_ALU_CONST_CACHE_HS_5				0x28f14
#घोषणा SQ_ALU_CONST_CACHE_HS_6				0x28f18
#घोषणा SQ_ALU_CONST_CACHE_HS_7				0x28f1c
#घोषणा SQ_ALU_CONST_CACHE_HS_8				0x28f20
#घोषणा SQ_ALU_CONST_CACHE_HS_9				0x28f24
#घोषणा SQ_ALU_CONST_CACHE_HS_10			0x28f28
#घोषणा SQ_ALU_CONST_CACHE_HS_11			0x28f2c
#घोषणा SQ_ALU_CONST_CACHE_HS_12			0x28f30
#घोषणा SQ_ALU_CONST_CACHE_HS_13			0x28f34
#घोषणा SQ_ALU_CONST_CACHE_HS_14			0x28f38
#घोषणा SQ_ALU_CONST_CACHE_HS_15			0x28f3c
#घोषणा SQ_ALU_CONST_CACHE_LS_0				0x28f40
#घोषणा SQ_ALU_CONST_CACHE_LS_1				0x28f44
#घोषणा SQ_ALU_CONST_CACHE_LS_2				0x28f48
#घोषणा SQ_ALU_CONST_CACHE_LS_3				0x28f4c
#घोषणा SQ_ALU_CONST_CACHE_LS_4				0x28f50
#घोषणा SQ_ALU_CONST_CACHE_LS_5				0x28f54
#घोषणा SQ_ALU_CONST_CACHE_LS_6				0x28f58
#घोषणा SQ_ALU_CONST_CACHE_LS_7				0x28f5c
#घोषणा SQ_ALU_CONST_CACHE_LS_8				0x28f60
#घोषणा SQ_ALU_CONST_CACHE_LS_9				0x28f64
#घोषणा SQ_ALU_CONST_CACHE_LS_10			0x28f68
#घोषणा SQ_ALU_CONST_CACHE_LS_11			0x28f6c
#घोषणा SQ_ALU_CONST_CACHE_LS_12			0x28f70
#घोषणा SQ_ALU_CONST_CACHE_LS_13			0x28f74
#घोषणा SQ_ALU_CONST_CACHE_LS_14			0x28f78
#घोषणा SQ_ALU_CONST_CACHE_LS_15			0x28f7c

#घोषणा PA_SC_SCREEN_SCISSOR_TL                         0x28030
#घोषणा PA_SC_GENERIC_SCISSOR_TL                        0x28240
#घोषणा PA_SC_WINDOW_SCISSOR_TL                         0x28204

#घोषणा VGT_PRIMITIVE_TYPE                              0x8958
#घोषणा VGT_INDEX_TYPE                                  0x895C

#घोषणा VGT_NUM_INDICES                                 0x8970

#घोषणा VGT_COMPUTE_DIM_X                               0x8990
#घोषणा VGT_COMPUTE_DIM_Y                               0x8994
#घोषणा VGT_COMPUTE_DIM_Z                               0x8998
#घोषणा VGT_COMPUTE_START_X                             0x899C
#घोषणा VGT_COMPUTE_START_Y                             0x89A0
#घोषणा VGT_COMPUTE_START_Z                             0x89A4
#घोषणा VGT_COMPUTE_INDEX                               0x89A8
#घोषणा VGT_COMPUTE_THREAD_GROUP_SIZE                   0x89AC
#घोषणा VGT_HS_OFFCHIP_PARAM                            0x89B0

#घोषणा DB_DEBUG					0x9830
#घोषणा DB_DEBUG2					0x9834
#घोषणा DB_DEBUG3					0x9838
#घोषणा DB_DEBUG4					0x983C
#घोषणा DB_WATERMARKS					0x9854
#घोषणा DB_DEPTH_CONTROL				0x28800
#घोषणा R_028800_DB_DEPTH_CONTROL                    0x028800
#घोषणा   S_028800_STENCIL_ENABLE(x)                   (((x) & 0x1) << 0)
#घोषणा   G_028800_STENCIL_ENABLE(x)                   (((x) >> 0) & 0x1)
#घोषणा   C_028800_STENCIL_ENABLE                      0xFFFFFFFE
#घोषणा   S_028800_Z_ENABLE(x)                         (((x) & 0x1) << 1)
#घोषणा   G_028800_Z_ENABLE(x)                         (((x) >> 1) & 0x1)
#घोषणा   C_028800_Z_ENABLE                            0xFFFFFFFD
#घोषणा   S_028800_Z_WRITE_ENABLE(x)                   (((x) & 0x1) << 2)
#घोषणा   G_028800_Z_WRITE_ENABLE(x)                   (((x) >> 2) & 0x1)
#घोषणा   C_028800_Z_WRITE_ENABLE                      0xFFFFFFFB
#घोषणा   S_028800_ZFUNC(x)                            (((x) & 0x7) << 4)
#घोषणा   G_028800_ZFUNC(x)                            (((x) >> 4) & 0x7)
#घोषणा   C_028800_ZFUNC                               0xFFFFFF8F
#घोषणा   S_028800_BACKFACE_ENABLE(x)                  (((x) & 0x1) << 7)
#घोषणा   G_028800_BACKFACE_ENABLE(x)                  (((x) >> 7) & 0x1)
#घोषणा   C_028800_BACKFACE_ENABLE                     0xFFFFFF7F
#घोषणा   S_028800_STENCILFUNC(x)                      (((x) & 0x7) << 8)
#घोषणा   G_028800_STENCILFUNC(x)                      (((x) >> 8) & 0x7)
#घोषणा   C_028800_STENCILFUNC                         0xFFFFF8FF
#घोषणा     V_028800_STENCILFUNC_NEVER                 0x00000000
#घोषणा     V_028800_STENCILFUNC_LESS                  0x00000001
#घोषणा     V_028800_STENCILFUNC_EQUAL                 0x00000002
#घोषणा     V_028800_STENCILFUNC_LEQUAL                0x00000003
#घोषणा     V_028800_STENCILFUNC_GREATER               0x00000004
#घोषणा     V_028800_STENCILFUNC_NOTEQUAL              0x00000005
#घोषणा     V_028800_STENCILFUNC_GEQUAL                0x00000006
#घोषणा     V_028800_STENCILFUNC_ALWAYS                0x00000007
#घोषणा   S_028800_STENCILFAIL(x)                      (((x) & 0x7) << 11)
#घोषणा   G_028800_STENCILFAIL(x)                      (((x) >> 11) & 0x7)
#घोषणा   C_028800_STENCILFAIL                         0xFFFFC7FF
#घोषणा     V_028800_STENCIL_KEEP                      0x00000000
#घोषणा     V_028800_STENCIL_ZERO                      0x00000001
#घोषणा     V_028800_STENCIL_REPLACE                   0x00000002
#घोषणा     V_028800_STENCIL_INCR                      0x00000003
#घोषणा     V_028800_STENCIL_DECR                      0x00000004
#घोषणा     V_028800_STENCIL_INVERT                    0x00000005
#घोषणा     V_028800_STENCIL_INCR_WRAP                 0x00000006
#घोषणा     V_028800_STENCIL_DECR_WRAP                 0x00000007
#घोषणा   S_028800_STENCILZPASS(x)                     (((x) & 0x7) << 14)
#घोषणा   G_028800_STENCILZPASS(x)                     (((x) >> 14) & 0x7)
#घोषणा   C_028800_STENCILZPASS                        0xFFFE3FFF
#घोषणा   S_028800_STENCILZFAIL(x)                     (((x) & 0x7) << 17)
#घोषणा   G_028800_STENCILZFAIL(x)                     (((x) >> 17) & 0x7)
#घोषणा   C_028800_STENCILZFAIL                        0xFFF1FFFF
#घोषणा   S_028800_STENCILFUNC_BF(x)                   (((x) & 0x7) << 20)
#घोषणा   G_028800_STENCILFUNC_BF(x)                   (((x) >> 20) & 0x7)
#घोषणा   C_028800_STENCILFUNC_BF                      0xFF8FFFFF
#घोषणा   S_028800_STENCILFAIL_BF(x)                   (((x) & 0x7) << 23)
#घोषणा   G_028800_STENCILFAIL_BF(x)                   (((x) >> 23) & 0x7)
#घोषणा   C_028800_STENCILFAIL_BF                      0xFC7FFFFF
#घोषणा   S_028800_STENCILZPASS_BF(x)                  (((x) & 0x7) << 26)
#घोषणा   G_028800_STENCILZPASS_BF(x)                  (((x) >> 26) & 0x7)
#घोषणा   C_028800_STENCILZPASS_BF                     0xE3FFFFFF
#घोषणा   S_028800_STENCILZFAIL_BF(x)                  (((x) & 0x7) << 29)
#घोषणा   G_028800_STENCILZFAIL_BF(x)                  (((x) >> 29) & 0x7)
#घोषणा   C_028800_STENCILZFAIL_BF                     0x1FFFFFFF
#घोषणा DB_DEPTH_VIEW					0x28008
#घोषणा R_028008_DB_DEPTH_VIEW                       0x00028008
#घोषणा   S_028008_SLICE_START(x)                      (((x) & 0x7FF) << 0)
#घोषणा   G_028008_SLICE_START(x)                      (((x) >> 0) & 0x7FF)
#घोषणा   C_028008_SLICE_START                         0xFFFFF800
#घोषणा   S_028008_SLICE_MAX(x)                        (((x) & 0x7FF) << 13)
#घोषणा   G_028008_SLICE_MAX(x)                        (((x) >> 13) & 0x7FF)
#घोषणा   C_028008_SLICE_MAX                           0xFF001FFF
#घोषणा DB_HTILE_DATA_BASE				0x28014
#घोषणा DB_HTILE_SURFACE				0x28abc
#घोषणा   S_028ABC_HTILE_WIDTH(x)                      (((x) & 0x1) << 0)
#घोषणा   G_028ABC_HTILE_WIDTH(x)                      (((x) >> 0) & 0x1)
#घोषणा   C_028ABC_HTILE_WIDTH                         0xFFFFFFFE
#घोषणा   S_028ABC_HTILE_HEIGHT(x)                      (((x) & 0x1) << 1)
#घोषणा   G_028ABC_HTILE_HEIGHT(x)                      (((x) >> 1) & 0x1)
#घोषणा   C_028ABC_HTILE_HEIGHT                         0xFFFFFFFD
#घोषणा   G_028ABC_LINEAR(x)                           (((x) >> 2) & 0x1)
#घोषणा DB_Z_INFO					0x28040
#       define Z_ARRAY_MODE(x)                          ((x) << 4)
#       define DB_TILE_SPLIT(x)                         (((x) & 0x7) << 8)
#       define DB_NUM_BANKS(x)                          (((x) & 0x3) << 12)
#       define DB_BANK_WIDTH(x)                         (((x) & 0x3) << 16)
#       define DB_BANK_HEIGHT(x)                        (((x) & 0x3) << 20)
#       define DB_MACRO_TILE_ASPECT(x)                  (((x) & 0x3) << 24)
#घोषणा R_028040_DB_Z_INFO                       0x028040
#घोषणा   S_028040_FORMAT(x)                           (((x) & 0x3) << 0)
#घोषणा   G_028040_FORMAT(x)                           (((x) >> 0) & 0x3)
#घोषणा   C_028040_FORMAT                              0xFFFFFFFC
#घोषणा     V_028040_Z_INVALID                     0x00000000
#घोषणा     V_028040_Z_16                          0x00000001
#घोषणा     V_028040_Z_24                          0x00000002
#घोषणा     V_028040_Z_32_FLOAT                    0x00000003
#घोषणा   S_028040_ARRAY_MODE(x)                       (((x) & 0xF) << 4)
#घोषणा   G_028040_ARRAY_MODE(x)                       (((x) >> 4) & 0xF)
#घोषणा   C_028040_ARRAY_MODE                          0xFFFFFF0F
#घोषणा   S_028040_READ_SIZE(x)                        (((x) & 0x1) << 28)
#घोषणा   G_028040_READ_SIZE(x)                        (((x) >> 28) & 0x1)
#घोषणा   C_028040_READ_SIZE                           0xEFFFFFFF
#घोषणा   S_028040_TILE_SURFACE_ENABLE(x)              (((x) & 0x1) << 29)
#घोषणा   G_028040_TILE_SURFACE_ENABLE(x)              (((x) >> 29) & 0x1)
#घोषणा   C_028040_TILE_SURFACE_ENABLE                 0xDFFFFFFF
#घोषणा   S_028040_ZRANGE_PRECISION(x)                 (((x) & 0x1) << 31)
#घोषणा   G_028040_ZRANGE_PRECISION(x)                 (((x) >> 31) & 0x1)
#घोषणा   C_028040_ZRANGE_PRECISION                    0x7FFFFFFF
#घोषणा   S_028040_TILE_SPLIT(x)                       (((x) & 0x7) << 8)
#घोषणा   G_028040_TILE_SPLIT(x)                       (((x) >> 8) & 0x7)
#घोषणा   S_028040_NUM_BANKS(x)                        (((x) & 0x3) << 12)
#घोषणा   G_028040_NUM_BANKS(x)                        (((x) >> 12) & 0x3)
#घोषणा   S_028040_BANK_WIDTH(x)                       (((x) & 0x3) << 16)
#घोषणा   G_028040_BANK_WIDTH(x)                       (((x) >> 16) & 0x3)
#घोषणा   S_028040_BANK_HEIGHT(x)                      (((x) & 0x3) << 20)
#घोषणा   G_028040_BANK_HEIGHT(x)                      (((x) >> 20) & 0x3)
#घोषणा   S_028040_MACRO_TILE_ASPECT(x)                (((x) & 0x3) << 24)
#घोषणा   G_028040_MACRO_TILE_ASPECT(x)                (((x) >> 24) & 0x3)
#घोषणा DB_STENCIL_INFO					0x28044
#घोषणा R_028044_DB_STENCIL_INFO                     0x028044
#घोषणा   S_028044_FORMAT(x)                           (((x) & 0x1) << 0)
#घोषणा   G_028044_FORMAT(x)                           (((x) >> 0) & 0x1)
#घोषणा   C_028044_FORMAT                              0xFFFFFFFE
#घोषणा	    V_028044_STENCIL_INVALID			0
#घोषणा	    V_028044_STENCIL_8				1
#घोषणा   G_028044_TILE_SPLIT(x)                       (((x) >> 8) & 0x7)
#घोषणा DB_Z_READ_BASE					0x28048
#घोषणा DB_STENCIL_READ_BASE				0x2804c
#घोषणा DB_Z_WRITE_BASE					0x28050
#घोषणा DB_STENCIL_WRITE_BASE				0x28054
#घोषणा DB_DEPTH_SIZE					0x28058
#घोषणा R_028058_DB_DEPTH_SIZE                       0x028058
#घोषणा   S_028058_PITCH_TILE_MAX(x)                   (((x) & 0x7FF) << 0)
#घोषणा   G_028058_PITCH_TILE_MAX(x)                   (((x) >> 0) & 0x7FF)
#घोषणा   C_028058_PITCH_TILE_MAX                      0xFFFFF800
#घोषणा   S_028058_HEIGHT_TILE_MAX(x)                   (((x) & 0x7FF) << 11)
#घोषणा   G_028058_HEIGHT_TILE_MAX(x)                   (((x) >> 11) & 0x7FF)
#घोषणा   C_028058_HEIGHT_TILE_MAX                      0xFFC007FF
#घोषणा R_02805C_DB_DEPTH_SLICE                      0x02805C
#घोषणा   S_02805C_SLICE_TILE_MAX(x)                   (((x) & 0x3FFFFF) << 0)
#घोषणा   G_02805C_SLICE_TILE_MAX(x)                   (((x) >> 0) & 0x3FFFFF)
#घोषणा   C_02805C_SLICE_TILE_MAX                      0xFFC00000

#घोषणा SQ_PGM_START_PS					0x28840
#घोषणा SQ_PGM_START_VS					0x2885c
#घोषणा SQ_PGM_START_GS					0x28874
#घोषणा SQ_PGM_START_ES					0x2888c
#घोषणा SQ_PGM_START_FS					0x288a4
#घोषणा SQ_PGM_START_HS					0x288b8
#घोषणा SQ_PGM_START_LS					0x288d0

#घोषणा	VGT_STRMOUT_BUFFER_BASE_0			0x28AD8
#घोषणा	VGT_STRMOUT_BUFFER_BASE_1			0x28AE8
#घोषणा	VGT_STRMOUT_BUFFER_BASE_2			0x28AF8
#घोषणा	VGT_STRMOUT_BUFFER_BASE_3			0x28B08
#घोषणा VGT_STRMOUT_BUFFER_SIZE_0			0x28AD0
#घोषणा VGT_STRMOUT_BUFFER_SIZE_1			0x28AE0
#घोषणा VGT_STRMOUT_BUFFER_SIZE_2			0x28AF0
#घोषणा VGT_STRMOUT_BUFFER_SIZE_3			0x28B00
#घोषणा VGT_STRMOUT_CONFIG				0x28b94
#घोषणा VGT_STRMOUT_BUFFER_CONFIG			0x28b98

#घोषणा CB_TARGET_MASK					0x28238
#घोषणा CB_SHADER_MASK					0x2823c

#घोषणा GDS_ADDR_BASE					0x28720

#घोषणा GDS_APPEND_COUNT_0				0x2872C
#घोषणा GDS_APPEND_COUNT_1				0x28730
#घोषणा GDS_APPEND_COUNT_2				0x28734
#घोषणा GDS_APPEND_COUNT_3				0x28738
#घोषणा GDS_APPEND_COUNT_4				0x2873C
#घोषणा GDS_APPEND_COUNT_5				0x28740
#घोषणा GDS_APPEND_COUNT_6				0x28744
#घोषणा GDS_APPEND_COUNT_7				0x28748
#घोषणा GDS_APPEND_COUNT_8				0x2874c
#घोषणा GDS_APPEND_COUNT_9				0x28750
#घोषणा GDS_APPEND_COUNT_10				0x28754
#घोषणा GDS_APPEND_COUNT_11				0x28758

#घोषणा	CB_IMMED0_BASE					0x28b9c
#घोषणा	CB_IMMED1_BASE					0x28ba0
#घोषणा	CB_IMMED2_BASE					0x28ba4
#घोषणा	CB_IMMED3_BASE					0x28ba8
#घोषणा	CB_IMMED4_BASE					0x28bac
#घोषणा	CB_IMMED5_BASE					0x28bb0
#घोषणा	CB_IMMED6_BASE					0x28bb4
#घोषणा	CB_IMMED7_BASE					0x28bb8
#घोषणा	CB_IMMED8_BASE					0x28bbc
#घोषणा	CB_IMMED9_BASE					0x28bc0
#घोषणा	CB_IMMED10_BASE					0x28bc4
#घोषणा	CB_IMMED11_BASE					0x28bc8

/* all 12 CB blocks have these regs */
#घोषणा	CB_COLOR0_BASE					0x28c60
#घोषणा	CB_COLOR0_PITCH					0x28c64
#घोषणा	CB_COLOR0_SLICE					0x28c68
#घोषणा	CB_COLOR0_VIEW					0x28c6c
#घोषणा R_028C6C_CB_COLOR0_VIEW                      0x00028C6C
#घोषणा   S_028C6C_SLICE_START(x)                      (((x) & 0x7FF) << 0)
#घोषणा   G_028C6C_SLICE_START(x)                      (((x) >> 0) & 0x7FF)
#घोषणा   C_028C6C_SLICE_START                         0xFFFFF800
#घोषणा   S_028C6C_SLICE_MAX(x)                        (((x) & 0x7FF) << 13)
#घोषणा   G_028C6C_SLICE_MAX(x)                        (((x) >> 13) & 0x7FF)
#घोषणा   C_028C6C_SLICE_MAX                           0xFF001FFF
#घोषणा R_028C70_CB_COLOR0_INFO                      0x028C70
#घोषणा   S_028C70_ENDIAN(x)                           (((x) & 0x3) << 0)
#घोषणा   G_028C70_ENDIAN(x)                           (((x) >> 0) & 0x3)
#घोषणा   C_028C70_ENDIAN                              0xFFFFFFFC
#घोषणा   S_028C70_FORMAT(x)                           (((x) & 0x3F) << 2)
#घोषणा   G_028C70_FORMAT(x)                           (((x) >> 2) & 0x3F)
#घोषणा   C_028C70_FORMAT                              0xFFFFFF03
#घोषणा     V_028C70_COLOR_INVALID                     0x00000000
#घोषणा     V_028C70_COLOR_8                           0x00000001
#घोषणा     V_028C70_COLOR_4_4                         0x00000002
#घोषणा     V_028C70_COLOR_3_3_2                       0x00000003
#घोषणा     V_028C70_COLOR_16                          0x00000005
#घोषणा     V_028C70_COLOR_16_FLOAT                    0x00000006
#घोषणा     V_028C70_COLOR_8_8                         0x00000007
#घोषणा     V_028C70_COLOR_5_6_5                       0x00000008
#घोषणा     V_028C70_COLOR_6_5_5                       0x00000009
#घोषणा     V_028C70_COLOR_1_5_5_5                     0x0000000A
#घोषणा     V_028C70_COLOR_4_4_4_4                     0x0000000B
#घोषणा     V_028C70_COLOR_5_5_5_1                     0x0000000C
#घोषणा     V_028C70_COLOR_32                          0x0000000D
#घोषणा     V_028C70_COLOR_32_FLOAT                    0x0000000E
#घोषणा     V_028C70_COLOR_16_16                       0x0000000F
#घोषणा     V_028C70_COLOR_16_16_FLOAT                 0x00000010
#घोषणा     V_028C70_COLOR_8_24                        0x00000011
#घोषणा     V_028C70_COLOR_8_24_FLOAT                  0x00000012
#घोषणा     V_028C70_COLOR_24_8                        0x00000013
#घोषणा     V_028C70_COLOR_24_8_FLOAT                  0x00000014
#घोषणा     V_028C70_COLOR_10_11_11                    0x00000015
#घोषणा     V_028C70_COLOR_10_11_11_FLOAT              0x00000016
#घोषणा     V_028C70_COLOR_11_11_10                    0x00000017
#घोषणा     V_028C70_COLOR_11_11_10_FLOAT              0x00000018
#घोषणा     V_028C70_COLOR_2_10_10_10                  0x00000019
#घोषणा     V_028C70_COLOR_8_8_8_8                     0x0000001A
#घोषणा     V_028C70_COLOR_10_10_10_2                  0x0000001B
#घोषणा     V_028C70_COLOR_X24_8_32_FLOAT              0x0000001C
#घोषणा     V_028C70_COLOR_32_32                       0x0000001D
#घोषणा     V_028C70_COLOR_32_32_FLOAT                 0x0000001E
#घोषणा     V_028C70_COLOR_16_16_16_16                 0x0000001F
#घोषणा     V_028C70_COLOR_16_16_16_16_FLOAT           0x00000020
#घोषणा     V_028C70_COLOR_32_32_32_32                 0x00000022
#घोषणा     V_028C70_COLOR_32_32_32_32_FLOAT           0x00000023
#घोषणा     V_028C70_COLOR_32_32_32_FLOAT              0x00000030
#घोषणा   S_028C70_ARRAY_MODE(x)                       (((x) & 0xF) << 8)
#घोषणा   G_028C70_ARRAY_MODE(x)                       (((x) >> 8) & 0xF)
#घोषणा   C_028C70_ARRAY_MODE                          0xFFFFF0FF
#घोषणा     V_028C70_ARRAY_LINEAR_GENERAL              0x00000000
#घोषणा     V_028C70_ARRAY_LINEAR_ALIGNED              0x00000001
#घोषणा     V_028C70_ARRAY_1D_TILED_THIN1              0x00000002
#घोषणा     V_028C70_ARRAY_2D_TILED_THIN1              0x00000004
#घोषणा   S_028C70_NUMBER_TYPE(x)                      (((x) & 0x7) << 12)
#घोषणा   G_028C70_NUMBER_TYPE(x)                      (((x) >> 12) & 0x7)
#घोषणा   C_028C70_NUMBER_TYPE                         0xFFFF8FFF
#घोषणा     V_028C70_NUMBER_UNORM                      0x00000000
#घोषणा     V_028C70_NUMBER_SNORM                      0x00000001
#घोषणा     V_028C70_NUMBER_USCALED                    0x00000002
#घोषणा     V_028C70_NUMBER_SSCALED                    0x00000003
#घोषणा     V_028C70_NUMBER_UINT                       0x00000004
#घोषणा     V_028C70_NUMBER_SINT                       0x00000005
#घोषणा     V_028C70_NUMBER_SRGB                       0x00000006
#घोषणा     V_028C70_NUMBER_FLOAT                      0x00000007
#घोषणा   S_028C70_COMP_SWAP(x)                        (((x) & 0x3) << 15)
#घोषणा   G_028C70_COMP_SWAP(x)                        (((x) >> 15) & 0x3)
#घोषणा   C_028C70_COMP_SWAP                           0xFFFE7FFF
#घोषणा     V_028C70_SWAP_STD                          0x00000000
#घोषणा     V_028C70_SWAP_ALT                          0x00000001
#घोषणा     V_028C70_SWAP_STD_REV                      0x00000002
#घोषणा     V_028C70_SWAP_ALT_REV                      0x00000003
#घोषणा   S_028C70_FAST_CLEAR(x)                       (((x) & 0x1) << 17)
#घोषणा   G_028C70_FAST_CLEAR(x)                       (((x) >> 17) & 0x1)
#घोषणा   C_028C70_FAST_CLEAR                          0xFFFDFFFF
#घोषणा   S_028C70_COMPRESSION(x)                      (((x) & 0x3) << 18)
#घोषणा   G_028C70_COMPRESSION(x)                      (((x) >> 18) & 0x3)
#घोषणा   C_028C70_COMPRESSION                         0xFFF3FFFF
#घोषणा   S_028C70_BLEND_CLAMP(x)                      (((x) & 0x1) << 19)
#घोषणा   G_028C70_BLEND_CLAMP(x)                      (((x) >> 19) & 0x1)
#घोषणा   C_028C70_BLEND_CLAMP                         0xFFF7FFFF
#घोषणा   S_028C70_BLEND_BYPASS(x)                     (((x) & 0x1) << 20)
#घोषणा   G_028C70_BLEND_BYPASS(x)                     (((x) >> 20) & 0x1)
#घोषणा   C_028C70_BLEND_BYPASS                        0xFFEFFFFF
#घोषणा   S_028C70_SIMPLE_FLOAT(x)                     (((x) & 0x1) << 21)
#घोषणा   G_028C70_SIMPLE_FLOAT(x)                     (((x) >> 21) & 0x1)
#घोषणा   C_028C70_SIMPLE_FLOAT                        0xFFDFFFFF
#घोषणा   S_028C70_ROUND_MODE(x)                       (((x) & 0x1) << 22)
#घोषणा   G_028C70_ROUND_MODE(x)                       (((x) >> 22) & 0x1)
#घोषणा   C_028C70_ROUND_MODE                          0xFFBFFFFF
#घोषणा   S_028C70_TILE_COMPACT(x)                     (((x) & 0x1) << 23)
#घोषणा   G_028C70_TILE_COMPACT(x)                     (((x) >> 23) & 0x1)
#घोषणा   C_028C70_TILE_COMPACT                        0xFF7FFFFF
#घोषणा   S_028C70_SOURCE_FORMAT(x)                    (((x) & 0x3) << 24)
#घोषणा   G_028C70_SOURCE_FORMAT(x)                    (((x) >> 24) & 0x3)
#घोषणा   C_028C70_SOURCE_FORMAT                       0xFCFFFFFF
#घोषणा     V_028C70_EXPORT_4C_32BPC                   0x0
#घोषणा     V_028C70_EXPORT_4C_16BPC                   0x1
#घोषणा     V_028C70_EXPORT_2C_32BPC                   0x2 /* Do not use */
#घोषणा   S_028C70_RAT(x)                              (((x) & 0x1) << 26)
#घोषणा   G_028C70_RAT(x)                              (((x) >> 26) & 0x1)
#घोषणा   C_028C70_RAT                                 0xFBFFFFFF
#घोषणा   S_028C70_RESOURCE_TYPE(x)                    (((x) & 0x7) << 27)
#घोषणा   G_028C70_RESOURCE_TYPE(x)                    (((x) >> 27) & 0x7)
#घोषणा   C_028C70_RESOURCE_TYPE                       0xC7FFFFFF

#घोषणा	CB_COLOR0_INFO					0x28c70
#	define CB_FORMAT(x)				((x) << 2)
#       define CB_ARRAY_MODE(x)                         ((x) << 8)
#       define ARRAY_LINEAR_GENERAL                     0
#       define ARRAY_LINEAR_ALIGNED                     1
#       define ARRAY_1D_TILED_THIN1                     2
#       define ARRAY_2D_TILED_THIN1                     4
#	define CB_SOURCE_FORMAT(x)			((x) << 24)
#	define CB_SF_EXPORT_FULL			0
#	define CB_SF_EXPORT_NORM			1
#घोषणा R_028C74_CB_COLOR0_ATTRIB                      0x028C74
#घोषणा   S_028C74_NON_DISP_TILING_ORDER(x)            (((x) & 0x1) << 4)
#घोषणा   G_028C74_NON_DISP_TILING_ORDER(x)            (((x) >> 4) & 0x1)
#घोषणा   C_028C74_NON_DISP_TILING_ORDER               0xFFFFFFEF
#घोषणा   S_028C74_TILE_SPLIT(x)                       (((x) & 0xf) << 5)
#घोषणा   G_028C74_TILE_SPLIT(x)                       (((x) >> 5) & 0xf)
#घोषणा   S_028C74_NUM_BANKS(x)                        (((x) & 0x3) << 10)
#घोषणा   G_028C74_NUM_BANKS(x)                        (((x) >> 10) & 0x3)
#घोषणा   S_028C74_BANK_WIDTH(x)                       (((x) & 0x3) << 13)
#घोषणा   G_028C74_BANK_WIDTH(x)                       (((x) >> 13) & 0x3)
#घोषणा   S_028C74_BANK_HEIGHT(x)                      (((x) & 0x3) << 16)
#घोषणा   G_028C74_BANK_HEIGHT(x)                      (((x) >> 16) & 0x3)
#घोषणा   S_028C74_MACRO_TILE_ASPECT(x)                (((x) & 0x3) << 19)
#घोषणा   G_028C74_MACRO_TILE_ASPECT(x)                (((x) >> 19) & 0x3)
#घोषणा	CB_COLOR0_ATTRIB				0x28c74
#       define CB_TILE_SPLIT(x)                         (((x) & 0x7) << 5)
#       define ADDR_SURF_TILE_SPLIT_64B                 0
#       define ADDR_SURF_TILE_SPLIT_128B                1
#       define ADDR_SURF_TILE_SPLIT_256B                2
#       define ADDR_SURF_TILE_SPLIT_512B                3
#       define ADDR_SURF_TILE_SPLIT_1KB                 4
#       define ADDR_SURF_TILE_SPLIT_2KB                 5
#       define ADDR_SURF_TILE_SPLIT_4KB                 6
#       define CB_NUM_BANKS(x)                          (((x) & 0x3) << 10)
#       define ADDR_SURF_2_BANK                         0
#       define ADDR_SURF_4_BANK                         1
#       define ADDR_SURF_8_BANK                         2
#       define ADDR_SURF_16_BANK                        3
#       define CB_BANK_WIDTH(x)                         (((x) & 0x3) << 13)
#       define ADDR_SURF_BANK_WIDTH_1                   0
#       define ADDR_SURF_BANK_WIDTH_2                   1
#       define ADDR_SURF_BANK_WIDTH_4                   2
#       define ADDR_SURF_BANK_WIDTH_8                   3
#       define CB_BANK_HEIGHT(x)                        (((x) & 0x3) << 16)
#       define ADDR_SURF_BANK_HEIGHT_1                  0
#       define ADDR_SURF_BANK_HEIGHT_2                  1
#       define ADDR_SURF_BANK_HEIGHT_4                  2
#       define ADDR_SURF_BANK_HEIGHT_8                  3
#       define CB_MACRO_TILE_ASPECT(x)                  (((x) & 0x3) << 19)
#घोषणा	CB_COLOR0_DIM					0x28c78
/* only CB0-7 blocks have these regs */
#घोषणा	CB_COLOR0_CMASK					0x28c7c
#घोषणा	CB_COLOR0_CMASK_SLICE				0x28c80
#घोषणा	CB_COLOR0_FMASK					0x28c84
#घोषणा	CB_COLOR0_FMASK_SLICE				0x28c88
#घोषणा	CB_COLOR0_CLEAR_WORD0				0x28c8c
#घोषणा	CB_COLOR0_CLEAR_WORD1				0x28c90
#घोषणा	CB_COLOR0_CLEAR_WORD2				0x28c94
#घोषणा	CB_COLOR0_CLEAR_WORD3				0x28c98

#घोषणा	CB_COLOR1_BASE					0x28c9c
#घोषणा	CB_COLOR2_BASE					0x28cd8
#घोषणा	CB_COLOR3_BASE					0x28d14
#घोषणा	CB_COLOR4_BASE					0x28d50
#घोषणा	CB_COLOR5_BASE					0x28d8c
#घोषणा	CB_COLOR6_BASE					0x28dc8
#घोषणा	CB_COLOR7_BASE					0x28e04
#घोषणा	CB_COLOR8_BASE					0x28e40
#घोषणा	CB_COLOR9_BASE					0x28e5c
#घोषणा	CB_COLOR10_BASE					0x28e78
#घोषणा	CB_COLOR11_BASE					0x28e94

#घोषणा	CB_COLOR1_PITCH					0x28ca0
#घोषणा	CB_COLOR2_PITCH					0x28cdc
#घोषणा	CB_COLOR3_PITCH					0x28d18
#घोषणा	CB_COLOR4_PITCH					0x28d54
#घोषणा	CB_COLOR5_PITCH					0x28d90
#घोषणा	CB_COLOR6_PITCH					0x28dcc
#घोषणा	CB_COLOR7_PITCH					0x28e08
#घोषणा	CB_COLOR8_PITCH					0x28e44
#घोषणा	CB_COLOR9_PITCH					0x28e60
#घोषणा	CB_COLOR10_PITCH				0x28e7c
#घोषणा	CB_COLOR11_PITCH				0x28e98

#घोषणा	CB_COLOR1_SLICE					0x28ca4
#घोषणा	CB_COLOR2_SLICE					0x28ce0
#घोषणा	CB_COLOR3_SLICE					0x28d1c
#घोषणा	CB_COLOR4_SLICE					0x28d58
#घोषणा	CB_COLOR5_SLICE					0x28d94
#घोषणा	CB_COLOR6_SLICE					0x28dd0
#घोषणा	CB_COLOR7_SLICE					0x28e0c
#घोषणा	CB_COLOR8_SLICE					0x28e48
#घोषणा	CB_COLOR9_SLICE					0x28e64
#घोषणा	CB_COLOR10_SLICE				0x28e80
#घोषणा	CB_COLOR11_SLICE				0x28e9c

#घोषणा	CB_COLOR1_VIEW					0x28ca8
#घोषणा	CB_COLOR2_VIEW					0x28ce4
#घोषणा	CB_COLOR3_VIEW					0x28d20
#घोषणा	CB_COLOR4_VIEW					0x28d5c
#घोषणा	CB_COLOR5_VIEW					0x28d98
#घोषणा	CB_COLOR6_VIEW					0x28dd4
#घोषणा	CB_COLOR7_VIEW					0x28e10
#घोषणा	CB_COLOR8_VIEW					0x28e4c
#घोषणा	CB_COLOR9_VIEW					0x28e68
#घोषणा	CB_COLOR10_VIEW					0x28e84
#घोषणा	CB_COLOR11_VIEW					0x28ea0

#घोषणा	CB_COLOR1_INFO					0x28cac
#घोषणा	CB_COLOR2_INFO					0x28ce8
#घोषणा	CB_COLOR3_INFO					0x28d24
#घोषणा	CB_COLOR4_INFO					0x28d60
#घोषणा	CB_COLOR5_INFO					0x28d9c
#घोषणा	CB_COLOR6_INFO					0x28dd8
#घोषणा	CB_COLOR7_INFO					0x28e14
#घोषणा	CB_COLOR8_INFO					0x28e50
#घोषणा	CB_COLOR9_INFO					0x28e6c
#घोषणा	CB_COLOR10_INFO					0x28e88
#घोषणा	CB_COLOR11_INFO					0x28ea4

#घोषणा	CB_COLOR1_ATTRIB				0x28cb0
#घोषणा	CB_COLOR2_ATTRIB				0x28cec
#घोषणा	CB_COLOR3_ATTRIB				0x28d28
#घोषणा	CB_COLOR4_ATTRIB				0x28d64
#घोषणा	CB_COLOR5_ATTRIB				0x28da0
#घोषणा	CB_COLOR6_ATTRIB				0x28ddc
#घोषणा	CB_COLOR7_ATTRIB				0x28e18
#घोषणा	CB_COLOR8_ATTRIB				0x28e54
#घोषणा	CB_COLOR9_ATTRIB				0x28e70
#घोषणा	CB_COLOR10_ATTRIB				0x28e8c
#घोषणा	CB_COLOR11_ATTRIB				0x28ea8

#घोषणा	CB_COLOR1_DIM					0x28cb4
#घोषणा	CB_COLOR2_DIM					0x28cf0
#घोषणा	CB_COLOR3_DIM					0x28d2c
#घोषणा	CB_COLOR4_DIM					0x28d68
#घोषणा	CB_COLOR5_DIM					0x28da4
#घोषणा	CB_COLOR6_DIM					0x28de0
#घोषणा	CB_COLOR7_DIM					0x28e1c
#घोषणा	CB_COLOR8_DIM					0x28e58
#घोषणा	CB_COLOR9_DIM					0x28e74
#घोषणा	CB_COLOR10_DIM					0x28e90
#घोषणा	CB_COLOR11_DIM					0x28eac

#घोषणा	CB_COLOR1_CMASK					0x28cb8
#घोषणा	CB_COLOR2_CMASK					0x28cf4
#घोषणा	CB_COLOR3_CMASK					0x28d30
#घोषणा	CB_COLOR4_CMASK					0x28d6c
#घोषणा	CB_COLOR5_CMASK					0x28da8
#घोषणा	CB_COLOR6_CMASK					0x28de4
#घोषणा	CB_COLOR7_CMASK					0x28e20

#घोषणा	CB_COLOR1_CMASK_SLICE				0x28cbc
#घोषणा	CB_COLOR2_CMASK_SLICE				0x28cf8
#घोषणा	CB_COLOR3_CMASK_SLICE				0x28d34
#घोषणा	CB_COLOR4_CMASK_SLICE				0x28d70
#घोषणा	CB_COLOR5_CMASK_SLICE				0x28dac
#घोषणा	CB_COLOR6_CMASK_SLICE				0x28de8
#घोषणा	CB_COLOR7_CMASK_SLICE				0x28e24

#घोषणा	CB_COLOR1_FMASK					0x28cc0
#घोषणा	CB_COLOR2_FMASK					0x28cfc
#घोषणा	CB_COLOR3_FMASK					0x28d38
#घोषणा	CB_COLOR4_FMASK					0x28d74
#घोषणा	CB_COLOR5_FMASK					0x28db0
#घोषणा	CB_COLOR6_FMASK					0x28dec
#घोषणा	CB_COLOR7_FMASK					0x28e28

#घोषणा	CB_COLOR1_FMASK_SLICE				0x28cc4
#घोषणा	CB_COLOR2_FMASK_SLICE				0x28d00
#घोषणा	CB_COLOR3_FMASK_SLICE				0x28d3c
#घोषणा	CB_COLOR4_FMASK_SLICE				0x28d78
#घोषणा	CB_COLOR5_FMASK_SLICE				0x28db4
#घोषणा	CB_COLOR6_FMASK_SLICE				0x28df0
#घोषणा	CB_COLOR7_FMASK_SLICE				0x28e2c

#घोषणा	CB_COLOR1_CLEAR_WORD0				0x28cc8
#घोषणा	CB_COLOR2_CLEAR_WORD0				0x28d04
#घोषणा	CB_COLOR3_CLEAR_WORD0				0x28d40
#घोषणा	CB_COLOR4_CLEAR_WORD0				0x28d7c
#घोषणा	CB_COLOR5_CLEAR_WORD0				0x28db8
#घोषणा	CB_COLOR6_CLEAR_WORD0				0x28df4
#घोषणा	CB_COLOR7_CLEAR_WORD0				0x28e30

#घोषणा	CB_COLOR1_CLEAR_WORD1				0x28ccc
#घोषणा	CB_COLOR2_CLEAR_WORD1				0x28d08
#घोषणा	CB_COLOR3_CLEAR_WORD1				0x28d44
#घोषणा	CB_COLOR4_CLEAR_WORD1				0x28d80
#घोषणा	CB_COLOR5_CLEAR_WORD1				0x28dbc
#घोषणा	CB_COLOR6_CLEAR_WORD1				0x28df8
#घोषणा	CB_COLOR7_CLEAR_WORD1				0x28e34

#घोषणा	CB_COLOR1_CLEAR_WORD2				0x28cd0
#घोषणा	CB_COLOR2_CLEAR_WORD2				0x28d0c
#घोषणा	CB_COLOR3_CLEAR_WORD2				0x28d48
#घोषणा	CB_COLOR4_CLEAR_WORD2				0x28d84
#घोषणा	CB_COLOR5_CLEAR_WORD2				0x28dc0
#घोषणा	CB_COLOR6_CLEAR_WORD2				0x28dfc
#घोषणा	CB_COLOR7_CLEAR_WORD2				0x28e38

#घोषणा	CB_COLOR1_CLEAR_WORD3				0x28cd4
#घोषणा	CB_COLOR2_CLEAR_WORD3				0x28d10
#घोषणा	CB_COLOR3_CLEAR_WORD3				0x28d4c
#घोषणा	CB_COLOR4_CLEAR_WORD3				0x28d88
#घोषणा	CB_COLOR5_CLEAR_WORD3				0x28dc4
#घोषणा	CB_COLOR6_CLEAR_WORD3				0x28e00
#घोषणा	CB_COLOR7_CLEAR_WORD3				0x28e3c

#घोषणा SQ_TEX_RESOURCE_WORD0_0                         0x30000
#	define TEX_DIM(x)				((x) << 0)
#	define SQ_TEX_DIM_1D				0
#	define SQ_TEX_DIM_2D				1
#	define SQ_TEX_DIM_3D				2
#	define SQ_TEX_DIM_CUBEMAP			3
#	define SQ_TEX_DIM_1D_ARRAY			4
#	define SQ_TEX_DIM_2D_ARRAY			5
#	define SQ_TEX_DIM_2D_MSAA			6
#	define SQ_TEX_DIM_2D_ARRAY_MSAA			7
#घोषणा SQ_TEX_RESOURCE_WORD1_0                         0x30004
#       define TEX_ARRAY_MODE(x)                        ((x) << 28)
#घोषणा SQ_TEX_RESOURCE_WORD2_0                         0x30008
#घोषणा SQ_TEX_RESOURCE_WORD3_0                         0x3000C
#घोषणा SQ_TEX_RESOURCE_WORD4_0                         0x30010
#	define TEX_DST_SEL_X(x)				((x) << 16)
#	define TEX_DST_SEL_Y(x)				((x) << 19)
#	define TEX_DST_SEL_Z(x)				((x) << 22)
#	define TEX_DST_SEL_W(x)				((x) << 25)
#	define SQ_SEL_X					0
#	define SQ_SEL_Y					1
#	define SQ_SEL_Z					2
#	define SQ_SEL_W					3
#	define SQ_SEL_0					4
#	define SQ_SEL_1					5
#घोषणा SQ_TEX_RESOURCE_WORD5_0                         0x30014
#घोषणा SQ_TEX_RESOURCE_WORD6_0                         0x30018
#       define TEX_TILE_SPLIT(x)                        (((x) & 0x7) << 29)
#घोषणा SQ_TEX_RESOURCE_WORD7_0                         0x3001c
#       define MACRO_TILE_ASPECT(x)                     (((x) & 0x3) << 6)
#       define TEX_BANK_WIDTH(x)                        (((x) & 0x3) << 8)
#       define TEX_BANK_HEIGHT(x)                       (((x) & 0x3) << 10)
#       define TEX_NUM_BANKS(x)                         (((x) & 0x3) << 16)
#घोषणा R_030000_SQ_TEX_RESOURCE_WORD0_0             0x030000
#घोषणा   S_030000_DIM(x)                              (((x) & 0x7) << 0)
#घोषणा   G_030000_DIM(x)                              (((x) >> 0) & 0x7)
#घोषणा   C_030000_DIM                                 0xFFFFFFF8
#घोषणा     V_030000_SQ_TEX_DIM_1D                     0x00000000
#घोषणा     V_030000_SQ_TEX_DIM_2D                     0x00000001
#घोषणा     V_030000_SQ_TEX_DIM_3D                     0x00000002
#घोषणा     V_030000_SQ_TEX_DIM_CUBEMAP                0x00000003
#घोषणा     V_030000_SQ_TEX_DIM_1D_ARRAY               0x00000004
#घोषणा     V_030000_SQ_TEX_DIM_2D_ARRAY               0x00000005
#घोषणा     V_030000_SQ_TEX_DIM_2D_MSAA                0x00000006
#घोषणा     V_030000_SQ_TEX_DIM_2D_ARRAY_MSAA          0x00000007
#घोषणा   S_030000_NON_DISP_TILING_ORDER(x)            (((x) & 0x1) << 5)
#घोषणा   G_030000_NON_DISP_TILING_ORDER(x)            (((x) >> 5) & 0x1)
#घोषणा   C_030000_NON_DISP_TILING_ORDER               0xFFFFFFDF
#घोषणा   S_030000_PITCH(x)                            (((x) & 0xFFF) << 6)
#घोषणा   G_030000_PITCH(x)                            (((x) >> 6) & 0xFFF)
#घोषणा   C_030000_PITCH                               0xFFFC003F
#घोषणा   S_030000_TEX_WIDTH(x)                        (((x) & 0x3FFF) << 18)
#घोषणा   G_030000_TEX_WIDTH(x)                        (((x) >> 18) & 0x3FFF)
#घोषणा   C_030000_TEX_WIDTH                           0x0003FFFF
#घोषणा R_030004_SQ_TEX_RESOURCE_WORD1_0             0x030004
#घोषणा   S_030004_TEX_HEIGHT(x)                       (((x) & 0x3FFF) << 0)
#घोषणा   G_030004_TEX_HEIGHT(x)                       (((x) >> 0) & 0x3FFF)
#घोषणा   C_030004_TEX_HEIGHT                          0xFFFFC000
#घोषणा   S_030004_TEX_DEPTH(x)                        (((x) & 0x1FFF) << 14)
#घोषणा   G_030004_TEX_DEPTH(x)                        (((x) >> 14) & 0x1FFF)
#घोषणा   C_030004_TEX_DEPTH                           0xF8003FFF
#घोषणा   S_030004_ARRAY_MODE(x)                       (((x) & 0xF) << 28)
#घोषणा   G_030004_ARRAY_MODE(x)                       (((x) >> 28) & 0xF)
#घोषणा   C_030004_ARRAY_MODE                          0x0FFFFFFF
#घोषणा R_030008_SQ_TEX_RESOURCE_WORD2_0             0x030008
#घोषणा   S_030008_BASE_ADDRESS(x)                     (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_030008_BASE_ADDRESS(x)                     (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_030008_BASE_ADDRESS                        0x00000000
#घोषणा R_03000C_SQ_TEX_RESOURCE_WORD3_0             0x03000C
#घोषणा   S_03000C_MIP_ADDRESS(x)                      (((x) & 0xFFFFFFFF) << 0)
#घोषणा   G_03000C_MIP_ADDRESS(x)                      (((x) >> 0) & 0xFFFFFFFF)
#घोषणा   C_03000C_MIP_ADDRESS                         0x00000000
#घोषणा R_030010_SQ_TEX_RESOURCE_WORD4_0             0x030010
#घोषणा   S_030010_FORMAT_COMP_X(x)                    (((x) & 0x3) << 0)
#घोषणा   G_030010_FORMAT_COMP_X(x)                    (((x) >> 0) & 0x3)
#घोषणा   C_030010_FORMAT_COMP_X                       0xFFFFFFFC
#घोषणा     V_030010_SQ_FORMAT_COMP_UNSIGNED           0x00000000
#घोषणा     V_030010_SQ_FORMAT_COMP_SIGNED             0x00000001
#घोषणा     V_030010_SQ_FORMAT_COMP_UNSIGNED_BIASED    0x00000002
#घोषणा   S_030010_FORMAT_COMP_Y(x)                    (((x) & 0x3) << 2)
#घोषणा   G_030010_FORMAT_COMP_Y(x)                    (((x) >> 2) & 0x3)
#घोषणा   C_030010_FORMAT_COMP_Y                       0xFFFFFFF3
#घोषणा   S_030010_FORMAT_COMP_Z(x)                    (((x) & 0x3) << 4)
#घोषणा   G_030010_FORMAT_COMP_Z(x)                    (((x) >> 4) & 0x3)
#घोषणा   C_030010_FORMAT_COMP_Z                       0xFFFFFFCF
#घोषणा   S_030010_FORMAT_COMP_W(x)                    (((x) & 0x3) << 6)
#घोषणा   G_030010_FORMAT_COMP_W(x)                    (((x) >> 6) & 0x3)
#घोषणा   C_030010_FORMAT_COMP_W                       0xFFFFFF3F
#घोषणा   S_030010_NUM_FORMAT_ALL(x)                   (((x) & 0x3) << 8)
#घोषणा   G_030010_NUM_FORMAT_ALL(x)                   (((x) >> 8) & 0x3)
#घोषणा   C_030010_NUM_FORMAT_ALL                      0xFFFFFCFF
#घोषणा     V_030010_SQ_NUM_FORMAT_NORM                0x00000000
#घोषणा     V_030010_SQ_NUM_FORMAT_INT                 0x00000001
#घोषणा     V_030010_SQ_NUM_FORMAT_SCALED              0x00000002
#घोषणा   S_030010_SRF_MODE_ALL(x)                     (((x) & 0x1) << 10)
#घोषणा   G_030010_SRF_MODE_ALL(x)                     (((x) >> 10) & 0x1)
#घोषणा   C_030010_SRF_MODE_ALL                        0xFFFFFBFF
#घोषणा     V_030010_SRF_MODE_ZERO_CLAMP_MINUS_ONE     0x00000000
#घोषणा     V_030010_SRF_MODE_NO_ZERO                  0x00000001
#घोषणा   S_030010_FORCE_DEGAMMA(x)                    (((x) & 0x1) << 11)
#घोषणा   G_030010_FORCE_DEGAMMA(x)                    (((x) >> 11) & 0x1)
#घोषणा   C_030010_FORCE_DEGAMMA                       0xFFFFF7FF
#घोषणा   S_030010_ENDIAN_SWAP(x)                      (((x) & 0x3) << 12)
#घोषणा   G_030010_ENDIAN_SWAP(x)                      (((x) >> 12) & 0x3)
#घोषणा   C_030010_ENDIAN_SWAP                         0xFFFFCFFF
#घोषणा   S_030010_DST_SEL_X(x)                        (((x) & 0x7) << 16)
#घोषणा   G_030010_DST_SEL_X(x)                        (((x) >> 16) & 0x7)
#घोषणा   C_030010_DST_SEL_X                           0xFFF8FFFF
#घोषणा     V_030010_SQ_SEL_X                          0x00000000
#घोषणा     V_030010_SQ_SEL_Y                          0x00000001
#घोषणा     V_030010_SQ_SEL_Z                          0x00000002
#घोषणा     V_030010_SQ_SEL_W                          0x00000003
#घोषणा     V_030010_SQ_SEL_0                          0x00000004
#घोषणा     V_030010_SQ_SEL_1                          0x00000005
#घोषणा   S_030010_DST_SEL_Y(x)                        (((x) & 0x7) << 19)
#घोषणा   G_030010_DST_SEL_Y(x)                        (((x) >> 19) & 0x7)
#घोषणा   C_030010_DST_SEL_Y                           0xFFC7FFFF
#घोषणा   S_030010_DST_SEL_Z(x)                        (((x) & 0x7) << 22)
#घोषणा   G_030010_DST_SEL_Z(x)                        (((x) >> 22) & 0x7)
#घोषणा   C_030010_DST_SEL_Z                           0xFE3FFFFF
#घोषणा   S_030010_DST_SEL_W(x)                        (((x) & 0x7) << 25)
#घोषणा   G_030010_DST_SEL_W(x)                        (((x) >> 25) & 0x7)
#घोषणा   C_030010_DST_SEL_W                           0xF1FFFFFF
#घोषणा   S_030010_BASE_LEVEL(x)                       (((x) & 0xF) << 28)
#घोषणा   G_030010_BASE_LEVEL(x)                       (((x) >> 28) & 0xF)
#घोषणा   C_030010_BASE_LEVEL                          0x0FFFFFFF
#घोषणा R_030014_SQ_TEX_RESOURCE_WORD5_0             0x030014
#घोषणा   S_030014_LAST_LEVEL(x)                       (((x) & 0xF) << 0)
#घोषणा   G_030014_LAST_LEVEL(x)                       (((x) >> 0) & 0xF)
#घोषणा   C_030014_LAST_LEVEL                          0xFFFFFFF0
#घोषणा   S_030014_BASE_ARRAY(x)                       (((x) & 0x1FFF) << 4)
#घोषणा   G_030014_BASE_ARRAY(x)                       (((x) >> 4) & 0x1FFF)
#घोषणा   C_030014_BASE_ARRAY                          0xFFFE000F
#घोषणा   S_030014_LAST_ARRAY(x)                       (((x) & 0x1FFF) << 17)
#घोषणा   G_030014_LAST_ARRAY(x)                       (((x) >> 17) & 0x1FFF)
#घोषणा   C_030014_LAST_ARRAY                          0xC001FFFF
#घोषणा R_030018_SQ_TEX_RESOURCE_WORD6_0             0x030018
#घोषणा   S_030018_MAX_ANISO(x)                        (((x) & 0x7) << 0)
#घोषणा   G_030018_MAX_ANISO(x)                        (((x) >> 0) & 0x7)
#घोषणा   C_030018_MAX_ANISO                           0xFFFFFFF8
#घोषणा   S_030018_PERF_MODULATION(x)                  (((x) & 0x7) << 3)
#घोषणा   G_030018_PERF_MODULATION(x)                  (((x) >> 3) & 0x7)
#घोषणा   C_030018_PERF_MODULATION                     0xFFFFFFC7
#घोषणा   S_030018_INTERLACED(x)                       (((x) & 0x1) << 6)
#घोषणा   G_030018_INTERLACED(x)                       (((x) >> 6) & 0x1)
#घोषणा   C_030018_INTERLACED                          0xFFFFFFBF
#घोषणा   S_030018_TILE_SPLIT(x)                       (((x) & 0x7) << 29)
#घोषणा   G_030018_TILE_SPLIT(x)                       (((x) >> 29) & 0x7)
#घोषणा R_03001C_SQ_TEX_RESOURCE_WORD7_0             0x03001C
#घोषणा   S_03001C_MACRO_TILE_ASPECT(x)                (((x) & 0x3) << 6)
#घोषणा   G_03001C_MACRO_TILE_ASPECT(x)                (((x) >> 6) & 0x3)
#घोषणा   S_03001C_BANK_WIDTH(x)                       (((x) & 0x3) << 8)
#घोषणा   G_03001C_BANK_WIDTH(x)                       (((x) >> 8) & 0x3)
#घोषणा   S_03001C_BANK_HEIGHT(x)                      (((x) & 0x3) << 10)
#घोषणा   G_03001C_BANK_HEIGHT(x)                      (((x) >> 10) & 0x3)
#घोषणा   S_03001C_NUM_BANKS(x)                        (((x) & 0x3) << 16)
#घोषणा   G_03001C_NUM_BANKS(x)                        (((x) >> 16) & 0x3)
#घोषणा   S_03001C_TYPE(x)                             (((x) & 0x3) << 30)
#घोषणा   G_03001C_TYPE(x)                             (((x) >> 30) & 0x3)
#घोषणा   C_03001C_TYPE                                0x3FFFFFFF
#घोषणा     V_03001C_SQ_TEX_VTX_INVALID_TEXTURE        0x00000000
#घोषणा     V_03001C_SQ_TEX_VTX_INVALID_BUFFER         0x00000001
#घोषणा     V_03001C_SQ_TEX_VTX_VALID_TEXTURE          0x00000002
#घोषणा     V_03001C_SQ_TEX_VTX_VALID_BUFFER           0x00000003
#घोषणा   S_03001C_DATA_FORMAT(x)                      (((x) & 0x3F) << 0)
#घोषणा   G_03001C_DATA_FORMAT(x)                      (((x) >> 0) & 0x3F)
#घोषणा   C_03001C_DATA_FORMAT                         0xFFFFFFC0

#घोषणा SQ_VTX_CONSTANT_WORD0_0				0x30000
#घोषणा SQ_VTX_CONSTANT_WORD1_0				0x30004
#घोषणा SQ_VTX_CONSTANT_WORD2_0				0x30008
#	define SQ_VTXC_BASE_ADDR_HI(x)			((x) << 0)
#	define SQ_VTXC_STRIDE(x)			((x) << 8)
#	define SQ_VTXC_ENDIAN_SWAP(x)			((x) << 30)
#	define SQ_ENDIAN_NONE				0
#	define SQ_ENDIAN_8IN16				1
#	define SQ_ENDIAN_8IN32				2
#घोषणा SQ_VTX_CONSTANT_WORD3_0				0x3000C
#	define SQ_VTCX_SEL_X(x)				((x) << 3)
#	define SQ_VTCX_SEL_Y(x)				((x) << 6)
#	define SQ_VTCX_SEL_Z(x)				((x) << 9)
#	define SQ_VTCX_SEL_W(x)				((x) << 12)
#घोषणा SQ_VTX_CONSTANT_WORD4_0				0x30010
#घोषणा SQ_VTX_CONSTANT_WORD5_0                         0x30014
#घोषणा SQ_VTX_CONSTANT_WORD6_0                         0x30018
#घोषणा SQ_VTX_CONSTANT_WORD7_0                         0x3001c

#घोषणा TD_PS_BORDER_COLOR_INDEX                        0xA400
#घोषणा TD_PS_BORDER_COLOR_RED                          0xA404
#घोषणा TD_PS_BORDER_COLOR_GREEN                        0xA408
#घोषणा TD_PS_BORDER_COLOR_BLUE                         0xA40C
#घोषणा TD_PS_BORDER_COLOR_ALPHA                        0xA410
#घोषणा TD_VS_BORDER_COLOR_INDEX                        0xA414
#घोषणा TD_VS_BORDER_COLOR_RED                          0xA418
#घोषणा TD_VS_BORDER_COLOR_GREEN                        0xA41C
#घोषणा TD_VS_BORDER_COLOR_BLUE                         0xA420
#घोषणा TD_VS_BORDER_COLOR_ALPHA                        0xA424
#घोषणा TD_GS_BORDER_COLOR_INDEX                        0xA428
#घोषणा TD_GS_BORDER_COLOR_RED                          0xA42C
#घोषणा TD_GS_BORDER_COLOR_GREEN                        0xA430
#घोषणा TD_GS_BORDER_COLOR_BLUE                         0xA434
#घोषणा TD_GS_BORDER_COLOR_ALPHA                        0xA438
#घोषणा TD_HS_BORDER_COLOR_INDEX                        0xA43C
#घोषणा TD_HS_BORDER_COLOR_RED                          0xA440
#घोषणा TD_HS_BORDER_COLOR_GREEN                        0xA444
#घोषणा TD_HS_BORDER_COLOR_BLUE                         0xA448
#घोषणा TD_HS_BORDER_COLOR_ALPHA                        0xA44C
#घोषणा TD_LS_BORDER_COLOR_INDEX                        0xA450
#घोषणा TD_LS_BORDER_COLOR_RED                          0xA454
#घोषणा TD_LS_BORDER_COLOR_GREEN                        0xA458
#घोषणा TD_LS_BORDER_COLOR_BLUE                         0xA45C
#घोषणा TD_LS_BORDER_COLOR_ALPHA                        0xA460
#घोषणा TD_CS_BORDER_COLOR_INDEX                        0xA464
#घोषणा TD_CS_BORDER_COLOR_RED                          0xA468
#घोषणा TD_CS_BORDER_COLOR_GREEN                        0xA46C
#घोषणा TD_CS_BORDER_COLOR_BLUE                         0xA470
#घोषणा TD_CS_BORDER_COLOR_ALPHA                        0xA474

/* cayman 3D regs */
#घोषणा CAYMAN_VGT_OFFCHIP_LDS_BASE			0x89B4
#घोषणा CAYMAN_SQ_EX_ALLOC_TABLE_SLOTS			0x8E48
#घोषणा CAYMAN_DB_EQAA					0x28804
#घोषणा CAYMAN_DB_DEPTH_INFO				0x2803C
#घोषणा CAYMAN_PA_SC_AA_CONFIG				0x28BE0
#घोषणा         CAYMAN_MSAA_NUM_SAMPLES_SHIFT           0
#घोषणा         CAYMAN_MSAA_NUM_SAMPLES_MASK            0x7
#घोषणा CAYMAN_SX_SCATTER_EXPORT_BASE			0x28358
/* cayman packet3 addition */
#घोषणा	CAYMAN_PACKET3_DEALLOC_STATE			0x14

/* DMA regs common on r6xx/r7xx/evergreen/ni */
#घोषणा DMA_RB_CNTL                                       0xd000
#       define DMA_RB_ENABLE                              (1 << 0)
#       define DMA_RB_SIZE(x)                             ((x) << 1) /* log2 */
#       define DMA_RB_SWAP_ENABLE                         (1 << 9) /* 8IN32 */
#       define DMA_RPTR_WRITEBACK_ENABLE                  (1 << 12)
#       define DMA_RPTR_WRITEBACK_SWAP_ENABLE             (1 << 13)  /* 8IN32 */
#       define DMA_RPTR_WRITEBACK_TIMER(x)                ((x) << 16) /* log2 */
#घोषणा DMA_STATUS_REG                                    0xd034
#       define DMA_IDLE                                   (1 << 0)

#पूर्ण_अगर
