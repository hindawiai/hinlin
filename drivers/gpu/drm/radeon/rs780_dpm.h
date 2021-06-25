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
#अगर_अघोषित __RS780_DPM_H__
#घोषणा __RS780_DPM_H__

क्रमागत rs780_vddc_level अणु
	RS780_VDDC_LEVEL_UNKNOWN = 0,
	RS780_VDDC_LEVEL_LOW = 1,
	RS780_VDDC_LEVEL_HIGH = 2,
पूर्ण;

काष्ठा igp_घातer_info अणु
	/* flags */
	bool invert_pwm_required;
	bool pwm_voltage_control;
	bool voltage_control;
	bool gfx_घड़ी_gating;
	/* stored values */
	u32 प्रणाली_config;
	u32 bootup_uma_clk;
	u16 max_voltage;
	u16 min_voltage;
	u16 boot_voltage;
	u16 पूर्णांकer_voltage_low;
	u16 पूर्णांकer_voltage_high;
	u16 num_of_cycles_in_period;
	/* variable */
	पूर्णांक crtc_id;
	पूर्णांक refresh_rate;
पूर्ण;

काष्ठा igp_ps अणु
	क्रमागत rs780_vddc_level min_voltage;
	क्रमागत rs780_vddc_level max_voltage;
	u32 sclk_low;
	u32 sclk_high;
	u32 flags;
पूर्ण;

#घोषणा RS780_CGFTV_DFLT                 0x0303000f
#घोषणा RS780_FBDIVTIMERVAL_DFLT         0x2710

#घोषणा RS780_FVTHROTUTC0_DFLT   0x04010040
#घोषणा RS780_FVTHROTUTC1_DFLT   0x04010040
#घोषणा RS780_FVTHROTUTC2_DFLT   0x04010040
#घोषणा RS780_FVTHROTUTC3_DFLT   0x04010040
#घोषणा RS780_FVTHROTUTC4_DFLT   0x04010040

#घोषणा RS780_FVTHROTDTC0_DFLT 0x04010040
#घोषणा RS780_FVTHROTDTC1_DFLT 0x04010040
#घोषणा RS780_FVTHROTDTC2_DFLT 0x04010040
#घोषणा RS780_FVTHROTDTC3_DFLT 0x04010040
#घोषणा RS780_FVTHROTDTC4_DFLT 0x04010040

#घोषणा RS780_FVTHROTFBUSREG0_DFLT       0x00001001
#घोषणा RS780_FVTHROTFBUSREG1_DFLT       0x00002002
#घोषणा RS780_FVTHROTFBDSREG0_DFLT       0x00004001
#घोषणा RS780_FVTHROTFBDSREG1_DFLT       0x00020010

#घोषणा RS780_FVTHROTPWMUSREG0_DFLT      0x00002001
#घोषणा RS780_FVTHROTPWMUSREG1_DFLT      0x00004003
#घोषणा RS780_FVTHROTPWMDSREG0_DFLT      0x00002001
#घोषणा RS780_FVTHROTPWMDSREG1_DFLT      0x00004003

#घोषणा RS780_FVTHROTPWMFBDIVRANGEREG0_DFLT  0x37
#घोषणा RS780_FVTHROTPWMFBDIVRANGEREG1_DFLT  0x4b
#घोषणा RS780_FVTHROTPWMFBDIVRANGEREG2_DFLT  0x8b

#घोषणा RS780D_FVTHROTPWMFBDIVRANGEREG0_DFLT  0x8b
#घोषणा RS780D_FVTHROTPWMFBDIVRANGEREG1_DFLT  0x8c
#घोषणा RS780D_FVTHROTPWMFBDIVRANGEREG2_DFLT  0xb5

#घोषणा RS880D_FVTHROTPWMFBDIVRANGEREG0_DFLT  0x8d
#घोषणा RS880D_FVTHROTPWMFBDIVRANGEREG1_DFLT  0x8e
#घोषणा RS880D_FVTHROTPWMFBDIVRANGEREG2_DFLT  0xBa

#घोषणा RS780_FVTHROTPWMRANGE0_GPIO_DFLT  0x1a
#घोषणा RS780_FVTHROTPWMRANGE1_GPIO_DFLT  0x1a
#घोषणा RS780_FVTHROTPWMRANGE2_GPIO_DFLT  0x0
#घोषणा RS780_FVTHROTPWMRANGE3_GPIO_DFLT  0x0

#घोषणा RS780_SLOWCLKFEEDBACKDIV_DFLT 110

#घोषणा RS780_CGCLKGATING_DFLT           0x0000E204

#घोषणा RS780_DEFAULT_VCLK_FREQ  53300 /* 10 khz */
#घोषणा RS780_DEFAULT_DCLK_FREQ  40000 /* 10 khz */

#पूर्ण_अगर
