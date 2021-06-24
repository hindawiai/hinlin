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
#अगर_अघोषित RV740_H
#घोषणा RV740_H

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
#घोषणा	CG_SPLL_FUNC_CNTL_3				0x608
#घोषणा		SPLL_FB_DIV(x)				((x) << 0)
#घोषणा		SPLL_FB_DIV_MASK			(0x3ffffff << 0)
#घोषणा		SPLL_DITHEN				(1 << 28)

#घोषणा	MPLL_CNTL_MODE					0x61c
#घोषणा		SS_SSEN					(1 << 24)

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

#घोषणा	MCLK_PWRMGT_CNTL				0x648
#घोषणा		DLL_SPEED(x)				((x) << 0)
#घोषणा		DLL_SPEED_MASK				(0x1f << 0)
#       define MPLL_PWRMGT_OFF                          (1 << 5)
#       define DLL_READY                                (1 << 6)
#       define MC_INT_CNTL                              (1 << 7)
#       define MRDCKA0_SLEEP                            (1 << 8)
#       define MRDCKA1_SLEEP                            (1 << 9)
#       define MRDCKB0_SLEEP                            (1 << 10)
#       define MRDCKB1_SLEEP                            (1 << 11)
#       define MRDCKC0_SLEEP                            (1 << 12)
#       define MRDCKC1_SLEEP                            (1 << 13)
#       define MRDCKD0_SLEEP                            (1 << 14)
#       define MRDCKD1_SLEEP                            (1 << 15)
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

#घोषणा	CG_SPLL_SPREAD_SPECTRUM				0x790
#घोषणा		SSEN					(1 << 0)
#घोषणा		CLK_S(x)				((x) << 4)
#घोषणा		CLK_S_MASK				(0xfff << 4)
#घोषणा	CG_SPLL_SPREAD_SPECTRUM_2			0x794
#घोषणा		CLK_V(x)				((x) << 0)
#घोषणा		CLK_V_MASK				(0x3ffffff << 0)

#घोषणा	MPLL_SS1					0x85c
#घोषणा		CLKV(x)					((x) << 0)
#घोषणा		CLKV_MASK				(0x3ffffff << 0)
#घोषणा	MPLL_SS2					0x860
#घोषणा		CLKS(x)					((x) << 0)
#घोषणा		CLKS_MASK				(0xfff << 0)

#पूर्ण_अगर
