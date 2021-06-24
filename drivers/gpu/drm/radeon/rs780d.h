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
#अगर_अघोषित __RS780D_H__
#घोषणा __RS780D_H__

#घोषणा CG_SPLL_FUNC_CNTL                                 0x600
#       define SPLL_RESET                                (1 << 0)
#       define SPLL_SLEEP                                (1 << 1)
#       define SPLL_REF_DIV(x)                           ((x) << 2)
#       define SPLL_REF_DIV_MASK                         (7 << 2)
#       define SPLL_REF_DIV_SHIFT                        2
#       define SPLL_FB_DIV(x)                            ((x) << 5)
#       define SPLL_FB_DIV_MASK                          (0xff << 2)
#       define SPLL_FB_DIV_SHIFT                         2
#       define SPLL_PULSEEN                              (1 << 13)
#       define SPLL_PULSENUM(x)                          ((x) << 14)
#       define SPLL_PULSENUM_MASK                        (3 << 14)
#       define SPLL_SW_HILEN(x)                          ((x) << 16)
#       define SPLL_SW_HILEN_MASK                        (0xf << 16)
#       define SPLL_SW_HILEN_SHIFT                       16
#       define SPLL_SW_LOLEN(x)                          ((x) << 20)
#       define SPLL_SW_LOLEN_MASK                        (0xf << 20)
#       define SPLL_SW_LOLEN_SHIFT                       20
#       define SPLL_DIVEN                                (1 << 24)
#       define SPLL_BYPASS_EN                            (1 << 25)
#       define SPLL_CHG_STATUS                           (1 << 29)
#       define SPLL_CTLREQ                               (1 << 30)
#       define SPLL_CTLACK                               (1 << 31)

/* RS780/RS880 PM */
#घोषणा	FVTHROT_CNTRL_REG				0x3000
#घोषणा		DONT_WAIT_FOR_FBDIV_WRAP		(1 << 0)
#घोषणा		MINIMUM_CIP(x)				((x) << 1)
#घोषणा		MINIMUM_CIP_SHIFT			1
#घोषणा		MINIMUM_CIP_MASK			0x1fffffe
#घोषणा		REFRESH_RATE_DIVISOR(x)			((x) << 25)
#घोषणा		REFRESH_RATE_DIVISOR_SHIFT		25
#घोषणा		REFRESH_RATE_DIVISOR_MASK		(0x3 << 25)
#घोषणा		ENABLE_FV_THROT				(1 << 27)
#घोषणा		ENABLE_FV_UPDATE			(1 << 28)
#घोषणा		TREND_SEL_MODE				(1 << 29)
#घोषणा		FORCE_TREND_SEL				(1 << 30)
#घोषणा		ENABLE_FV_THROT_IO			(1 << 31)
#घोषणा	FVTHROT_TARGET_REG				0x3004
#घोषणा		TARGET_IDLE_COUNT(x)			((x) << 0)
#घोषणा		TARGET_IDLE_COUNT_MASK			0xffffff
#घोषणा		TARGET_IDLE_COUNT_SHIFT			0
#घोषणा	FVTHROT_CB1					0x3008
#घोषणा	FVTHROT_CB2					0x300c
#घोषणा	FVTHROT_CB3					0x3010
#घोषणा	FVTHROT_CB4					0x3014
#घोषणा	FVTHROT_UTC0					0x3018
#घोषणा	FVTHROT_UTC1					0x301c
#घोषणा	FVTHROT_UTC2					0x3020
#घोषणा	FVTHROT_UTC3					0x3024
#घोषणा	FVTHROT_UTC4					0x3028
#घोषणा	FVTHROT_DTC0					0x302c
#घोषणा	FVTHROT_DTC1					0x3030
#घोषणा	FVTHROT_DTC2					0x3034
#घोषणा	FVTHROT_DTC3					0x3038
#घोषणा	FVTHROT_DTC4					0x303c
#घोषणा	FVTHROT_FBDIV_REG0				0x3040
#घोषणा		MIN_FEEDBACK_DIV(x)			((x) << 0)
#घोषणा		MIN_FEEDBACK_DIV_MASK			0xfff
#घोषणा		MIN_FEEDBACK_DIV_SHIFT			0
#घोषणा		MAX_FEEDBACK_DIV(x)			((x) << 12)
#घोषणा		MAX_FEEDBACK_DIV_MASK			(0xfff << 12)
#घोषणा		MAX_FEEDBACK_DIV_SHIFT			12
#घोषणा	FVTHROT_FBDIV_REG1				0x3044
#घोषणा		MAX_FEEDBACK_STEP(x)			((x) << 0)
#घोषणा		MAX_FEEDBACK_STEP_MASK			0xfff
#घोषणा		MAX_FEEDBACK_STEP_SHIFT			0
#घोषणा		STARTING_FEEDBACK_DIV(x)		((x) << 12)
#घोषणा		STARTING_FEEDBACK_DIV_MASK		(0xfff << 12)
#घोषणा		STARTING_FEEDBACK_DIV_SHIFT		12
#घोषणा		FORCE_FEEDBACK_DIV			(1 << 24)
#घोषणा	FVTHROT_FBDIV_REG2				0x3048
#घोषणा		FORCED_FEEDBACK_DIV(x)			((x) << 0)
#घोषणा		FORCED_FEEDBACK_DIV_MASK		0xfff
#घोषणा		FORCED_FEEDBACK_DIV_SHIFT		0
#घोषणा		FB_DIV_TIMER_VAL(x)			((x) << 12)
#घोषणा		FB_DIV_TIMER_VAL_MASK			(0xffff << 12)
#घोषणा		FB_DIV_TIMER_VAL_SHIFT			12
#घोषणा	FVTHROT_FB_US_REG0				0x304c
#घोषणा	FVTHROT_FB_US_REG1				0x3050
#घोषणा	FVTHROT_FB_DS_REG0				0x3054
#घोषणा	FVTHROT_FB_DS_REG1				0x3058
#घोषणा	FVTHROT_PWM_CTRL_REG0				0x305c
#घोषणा		STARTING_PWM_HIGHTIME(x)		((x) << 0)
#घोषणा		STARTING_PWM_HIGHTIME_MASK		0xfff
#घोषणा		STARTING_PWM_HIGHTIME_SHIFT		0
#घोषणा		NUMBER_OF_CYCLES_IN_PERIOD(x)		((x) << 12)
#घोषणा		NUMBER_OF_CYCLES_IN_PERIOD_MASK		(0xfff << 12)
#घोषणा		NUMBER_OF_CYCLES_IN_PERIOD_SHIFT	12
#घोषणा		FORCE_STARTING_PWM_HIGHTIME		(1 << 24)
#घोषणा		INVERT_PWM_WAVEFORM			(1 << 25)
#घोषणा	FVTHROT_PWM_CTRL_REG1				0x3060
#घोषणा		MIN_PWM_HIGHTIME(x)			((x) << 0)
#घोषणा		MIN_PWM_HIGHTIME_MASK			0xfff
#घोषणा		MIN_PWM_HIGHTIME_SHIFT			0
#घोषणा		MAX_PWM_HIGHTIME(x)			((x) << 12)
#घोषणा		MAX_PWM_HIGHTIME_MASK			(0xfff << 12)
#घोषणा		MAX_PWM_HIGHTIME_SHIFT			12
#घोषणा	FVTHROT_PWM_US_REG0				0x3064
#घोषणा	FVTHROT_PWM_US_REG1				0x3068
#घोषणा	FVTHROT_PWM_DS_REG0				0x306c
#घोषणा	FVTHROT_PWM_DS_REG1				0x3070
#घोषणा	FVTHROT_STATUS_REG0				0x3074
#घोषणा		CURRENT_FEEDBACK_DIV_MASK		0xfff
#घोषणा		CURRENT_FEEDBACK_DIV_SHIFT		0
#घोषणा	FVTHROT_STATUS_REG1				0x3078
#घोषणा	FVTHROT_STATUS_REG2				0x307c
#घोषणा	CG_INTGFX_MISC					0x3080
#घोषणा		FVTHROT_VBLANK_SEL			(1 << 9)
#घोषणा	FVTHROT_PWM_FEEDBACK_DIV_REG1			0x308c
#घोषणा		RANGE0_PWM_FEEDBACK_DIV(x)		((x) << 0)
#घोषणा		RANGE0_PWM_FEEDBACK_DIV_MASK		0xfff
#घोषणा		RANGE0_PWM_FEEDBACK_DIV_SHIFT		0
#घोषणा		RANGE_PWM_FEEDBACK_DIV_EN		(1 << 12)
#घोषणा	FVTHROT_PWM_FEEDBACK_DIV_REG2			0x3090
#घोषणा		RANGE1_PWM_FEEDBACK_DIV(x)		((x) << 0)
#घोषणा		RANGE1_PWM_FEEDBACK_DIV_MASK		0xfff
#घोषणा		RANGE1_PWM_FEEDBACK_DIV_SHIFT		0
#घोषणा		RANGE2_PWM_FEEDBACK_DIV(x)		((x) << 12)
#घोषणा		RANGE2_PWM_FEEDBACK_DIV_MASK		(0xfff << 12)
#घोषणा		RANGE2_PWM_FEEDBACK_DIV_SHIFT		12
#घोषणा	FVTHROT_PWM_FEEDBACK_DIV_REG3			0x3094
#घोषणा		RANGE0_PWM(x)				((x) << 0)
#घोषणा		RANGE0_PWM_MASK				0xfff
#घोषणा		RANGE0_PWM_SHIFT			0
#घोषणा		RANGE1_PWM(x)				((x) << 12)
#घोषणा		RANGE1_PWM_MASK				(0xfff << 12)
#घोषणा		RANGE1_PWM_SHIFT			12
#घोषणा	FVTHROT_PWM_FEEDBACK_DIV_REG4			0x3098
#घोषणा		RANGE2_PWM(x)				((x) << 0)
#घोषणा		RANGE2_PWM_MASK				0xfff
#घोषणा		RANGE2_PWM_SHIFT			0
#घोषणा		RANGE3_PWM(x)				((x) << 12)
#घोषणा		RANGE3_PWM_MASK				(0xfff << 12)
#घोषणा		RANGE3_PWM_SHIFT			12
#घोषणा	FVTHROT_SLOW_CLK_FEEDBACK_DIV_REG1		0x30ac
#घोषणा		RANGE0_SLOW_CLK_FEEDBACK_DIV(x)		((x) << 0)
#घोषणा		RANGE0_SLOW_CLK_FEEDBACK_DIV_MASK	0xfff
#घोषणा		RANGE0_SLOW_CLK_FEEDBACK_DIV_SHIFT	0
#घोषणा		RANGE_SLOW_CLK_FEEDBACK_DIV_EN		(1 << 12)

#घोषणा	GFX_MACRO_BYPASS_CNTL				0x30c0
#घोषणा		SPLL_BYPASS_CNTL			(1 << 0)
#घोषणा		UPLL_BYPASS_CNTL			(1 << 1)

#पूर्ण_अगर
