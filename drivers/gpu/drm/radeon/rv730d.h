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
 */
#अगर_अघोषित RV730_H
#घोषणा RV730_H

#घोषणा	CG_SPLL_FUNC_CNTL				0x600
#घोषणा		SPLL_RESET				(1 << 0)
#घोषणा		SPLL_SLEEP				(1 << 1)
#घोषणा		SPLL_DIVEN				(1 << 2)
#घोषणा		SPLL_BYPASS_EN				(1 << 3)
#घोषणा		SPLL_REF_DIV(x)				((x) << 4)
#घोषणा		SPLL_REF_DIV_MASK			(0x3f << 4)
#घोषणा		SPLL_HILEN(x)				((x) << 12)
#घोषणा		SPLL_HILEN_MASK				(0xf << 12)
#घोषणा		SPLL_LOLEN(x)				((x) << 16)
#घोषणा		SPLL_LOLEN_MASK				(0xf << 16)
#घोषणा	CG_SPLL_FUNC_CNTL_2				0x604
#घोषणा		SCLK_MUX_SEL(x)				((x) << 0)
#घोषणा		SCLK_MUX_SEL_MASK			(0x1ff << 0)
#घोषणा	CG_SPLL_FUNC_CNTL_3				0x608
#घोषणा		SPLL_FB_DIV(x)				((x) << 0)
#घोषणा		SPLL_FB_DIV_MASK			(0x3ffffff << 0)
#घोषणा		SPLL_DITHEN				(1 << 28)

#घोषणा	CG_MPLL_FUNC_CNTL				0x624
#घोषणा		MPLL_RESET				(1 << 0)
#घोषणा		MPLL_SLEEP				(1 << 1)
#घोषणा		MPLL_DIVEN				(1 << 2)
#घोषणा		MPLL_BYPASS_EN				(1 << 3)
#घोषणा		MPLL_REF_DIV(x)				((x) << 4)
#घोषणा		MPLL_REF_DIV_MASK			(0x3f << 4)
#घोषणा		MPLL_HILEN(x)				((x) << 12)
#घोषणा		MPLL_HILEN_MASK				(0xf << 12)
#घोषणा		MPLL_LOLEN(x)				((x) << 16)
#घोषणा		MPLL_LOLEN_MASK				(0xf << 16)
#घोषणा	CG_MPLL_FUNC_CNTL_2				0x628
#घोषणा		MCLK_MUX_SEL(x)				((x) << 0)
#घोषणा		MCLK_MUX_SEL_MASK			(0x1ff << 0)
#घोषणा	CG_MPLL_FUNC_CNTL_3				0x62c
#घोषणा		MPLL_FB_DIV(x)				((x) << 0)
#घोषणा		MPLL_FB_DIV_MASK			(0x3ffffff << 0)
#घोषणा		MPLL_DITHEN				(1 << 28)

#घोषणा	CG_TCI_MPLL_SPREAD_SPECTRUM			0x634
#घोषणा	CG_TCI_MPLL_SPREAD_SPECTRUM_2			0x638
#घोषणा GENERAL_PWRMGT                                  0x63c
#       define GLOBAL_PWRMGT_EN                         (1 << 0)
#       define STATIC_PM_EN                             (1 << 1)
#       define THERMAL_PROTECTION_DIS                   (1 << 2)
#       define THERMAL_PROTECTION_TYPE                  (1 << 3)
#       define ENABLE_GEN2PCIE                          (1 << 4)
#       define ENABLE_GEN2XSP                           (1 << 5)
#       define SW_SMIO_INDEX(x)                         ((x) << 6)
#       define SW_SMIO_INDEX_MASK                       (3 << 6)
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

#घोषणा	TCI_MCLK_PWRMGT_CNTL				0x648
#       define MPLL_PWRMGT_OFF                          (1 << 5)
#       define DLL_READY                                (1 << 6)
#       define MC_INT_CNTL                              (1 << 7)
#       define MRDCKA_SLEEP                             (1 << 8)
#       define MRDCKB_SLEEP                             (1 << 9)
#       define MRDCKC_SLEEP                             (1 << 10)
#       define MRDCKD_SLEEP                             (1 << 11)
#       define MRDCKE_SLEEP                             (1 << 12)
#       define MRDCKF_SLEEP                             (1 << 13)
#       define MRDCKG_SLEEP                             (1 << 14)
#       define MRDCKH_SLEEP                             (1 << 15)
#       define MRDCKA_RESET                             (1 << 16)
#       define MRDCKB_RESET                             (1 << 17)
#       define MRDCKC_RESET                             (1 << 18)
#       define MRDCKD_RESET                             (1 << 19)
#       define MRDCKE_RESET                             (1 << 20)
#       define MRDCKF_RESET                             (1 << 21)
#       define MRDCKG_RESET                             (1 << 22)
#       define MRDCKH_RESET                             (1 << 23)
#       define DLL_READY_READ                           (1 << 24)
#       define USE_DISPLAY_GAP                          (1 << 25)
#       define USE_DISPLAY_URGENT_NORMAL                (1 << 26)
#       define MPLL_TURNOFF_D2                          (1 << 28)
#घोषणा	TCI_DLL_CNTL					0x64c

#घोषणा	CG_PG_CNTL					0x858
#       define PWRGATE_ENABLE                           (1 << 0)

#घोषणा	CG_AT				                0x6d4
#घोषणा		CG_R(x)					((x) << 0)
#घोषणा		CG_R_MASK				(0xffff << 0)
#घोषणा		CG_L(x)					((x) << 16)
#घोषणा		CG_L_MASK				(0xffff << 16)

#घोषणा	CG_SPLL_SPREAD_SPECTRUM				0x790
#घोषणा		SSEN					(1 << 0)
#घोषणा		CLK_S(x)				((x) << 4)
#घोषणा		CLK_S_MASK				(0xfff << 4)
#घोषणा	CG_SPLL_SPREAD_SPECTRUM_2			0x794
#घोषणा		CLK_V(x)				((x) << 0)
#घोषणा		CLK_V_MASK				(0x3ffffff << 0)

#घोषणा	MC_ARB_DRAM_TIMING				0x2774
#घोषणा	MC_ARB_DRAM_TIMING2				0x2778

#घोषणा	MC_ARB_RFSH_RATE				0x27b0
#घोषणा		POWERMODE0(x)				((x) << 0)
#घोषणा		POWERMODE0_MASK				(0xff << 0)
#घोषणा		POWERMODE1(x)				((x) << 8)
#घोषणा		POWERMODE1_MASK				(0xff << 8)
#घोषणा		POWERMODE2(x)				((x) << 16)
#घोषणा		POWERMODE2_MASK				(0xff << 16)
#घोषणा		POWERMODE3(x)				((x) << 24)
#घोषणा		POWERMODE3_MASK				(0xff << 24)

#घोषणा	MC_ARB_DRAM_TIMING_1				0x27f0
#घोषणा	MC_ARB_DRAM_TIMING_2				0x27f4
#घोषणा	MC_ARB_DRAM_TIMING_3				0x27f8
#घोषणा	MC_ARB_DRAM_TIMING2_1				0x27fc
#घोषणा	MC_ARB_DRAM_TIMING2_2				0x2800
#घोषणा	MC_ARB_DRAM_TIMING2_3				0x2804

#घोषणा	MC4_IO_DQ_PAD_CNTL_D0_I0			0x2978
#घोषणा	MC4_IO_DQ_PAD_CNTL_D0_I1			0x297c
#घोषणा	MC4_IO_QS_PAD_CNTL_D0_I0			0x2980
#घोषणा	MC4_IO_QS_PAD_CNTL_D0_I1			0x2984

#पूर्ण_अगर
