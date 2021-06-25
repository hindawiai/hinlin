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
#अगर_अघोषित __BTC_DPM_H__
#घोषणा __BTC_DPM_H__

#समावेश "radeon.h"
#समावेश "rv770_dpm.h"

#घोषणा BTC_RLP_UVD_DFLT                              20
#घोषणा BTC_RMP_UVD_DFLT                              50
#घोषणा BTC_LHP_UVD_DFLT                              50
#घोषणा BTC_LMP_UVD_DFLT                              20
#घोषणा BARTS_MGCGCGTSSMCTRL_DFLT                     0x81944000
#घोषणा TURKS_MGCGCGTSSMCTRL_DFLT                     0x6e944000
#घोषणा CAICOS_MGCGCGTSSMCTRL_DFLT                    0x46944040
#घोषणा BTC_CGULVPARAMETER_DFLT                       0x00040035
#घोषणा BTC_CGULVCONTROL_DFLT                         0x00001450

बाह्य u32 btc_valid_sclk[40];

व्योम btc_पढ़ो_arb_रेजिस्टरs(काष्ठा radeon_device *rdev);
व्योम btc_program_mgcg_hw_sequence(काष्ठा radeon_device *rdev,
				  स्थिर u32 *sequence, u32 count);
व्योम btc_skip_blacklist_घड़ीs(काष्ठा radeon_device *rdev,
			       स्थिर u32 max_sclk, स्थिर u32 max_mclk,
			       u32 *sclk, u32 *mclk);
व्योम btc_adjust_घड़ी_combinations(काष्ठा radeon_device *rdev,
				   स्थिर काष्ठा radeon_घड़ी_and_voltage_limits *max_limits,
				   काष्ठा rv7xx_pl *pl);
व्योम btc_apply_voltage_dependency_rules(काष्ठा radeon_घड़ी_voltage_dependency_table *table,
					u32 घड़ी, u16 max_voltage, u16 *voltage);
व्योम btc_get_max_घड़ी_from_voltage_dependency_table(काष्ठा radeon_घड़ी_voltage_dependency_table *table,
						     u32 *max_घड़ी);
व्योम btc_apply_voltage_delta_rules(काष्ठा radeon_device *rdev,
				   u16 max_vddc, u16 max_vddci,
				   u16 *vddc, u16 *vddci);
bool btc_dpm_enabled(काष्ठा radeon_device *rdev);
पूर्णांक btc_reset_to_शेष(काष्ठा radeon_device *rdev);
व्योम btc_notअगरy_uvd_to_smc(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ps *radeon_new_state);

#पूर्ण_अगर
