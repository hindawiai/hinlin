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

#अगर_अघोषित __RV6XX_DPM_H__
#घोषणा __RV6XX_DPM_H__

#समावेश "r600_dpm.h"

/* Represents a single SCLK step. */
काष्ठा rv6xx_sclk_stepping
अणु
    u32 vco_frequency;
    u32 post_भागider;
पूर्ण;

काष्ठा rv6xx_pm_hw_state अणु
	u32 sclks[R600_PM_NUMBER_OF_ACTIVITY_LEVELS];
	u32 mclks[R600_PM_NUMBER_OF_MCLKS];
	u16 vddc[R600_PM_NUMBER_OF_VOLTAGE_LEVELS];
	bool backbias[R600_PM_NUMBER_OF_VOLTAGE_LEVELS];
	bool pcie_gen2[R600_PM_NUMBER_OF_ACTIVITY_LEVELS];
	u8 high_sclk_index;
	u8 medium_sclk_index;
	u8 low_sclk_index;
	u8 high_mclk_index;
	u8 medium_mclk_index;
	u8 low_mclk_index;
	u8 high_vddc_index;
	u8 medium_vddc_index;
	u8 low_vddc_index;
	u8 rp[R600_PM_NUMBER_OF_ACTIVITY_LEVELS];
	u8 lp[R600_PM_NUMBER_OF_ACTIVITY_LEVELS];
पूर्ण;

काष्ठा rv6xx_घातer_info अणु
	/* flags */
	bool voltage_control;
	bool sclk_ss;
	bool mclk_ss;
	bool dynamic_ss;
	bool dynamic_pcie_gen2;
	bool thermal_protection;
	bool display_gap;
	bool gfx_घड़ी_gating;
	/* clk values */
	u32 fb_भाग_scale;
	u32 spll_ref_भाग;
	u32 mpll_ref_भाग;
	u32 bsu;
	u32 bsp;
	/* */
	u32 active_स्वतः_throttle_sources;
	/* current घातer state */
	u32 restricted_levels;
	काष्ठा rv6xx_pm_hw_state hw;
पूर्ण;

काष्ठा rv6xx_pl अणु
	u32 sclk;
	u32 mclk;
	u16 vddc;
	u32 flags;
पूर्ण;

काष्ठा rv6xx_ps अणु
	काष्ठा rv6xx_pl high;
	काष्ठा rv6xx_pl medium;
	काष्ठा rv6xx_pl low;
पूर्ण;

#घोषणा RV6XX_DEFAULT_VCLK_FREQ  40000 /* 10 khz */
#घोषणा RV6XX_DEFAULT_DCLK_FREQ  30000 /* 10 khz */

#पूर्ण_अगर
