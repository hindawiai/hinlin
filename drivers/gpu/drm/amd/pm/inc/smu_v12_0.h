<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __SMU_V12_0_H__
#घोषणा __SMU_V12_0_H__

#समावेश "amdgpu_smu.h"

/* MP Apertures */
#घोषणा MP0_Public			0x03800000
#घोषणा MP0_SRAM			0x03900000
#घोषणा MP1_Public			0x03b00000
#घोषणा MP1_SRAM			0x03c00004

#अगर defined(SWSMU_CODE_LAYER_L2) || defined(SWSMU_CODE_LAYER_L3)

पूर्णांक smu_v12_0_check_fw_status(काष्ठा smu_context *smu);

पूर्णांक smu_v12_0_check_fw_version(काष्ठा smu_context *smu);

पूर्णांक smu_v12_0_घातergate_sdma(काष्ठा smu_context *smu, bool gate);

पूर्णांक smu_v12_0_घातergate_vcn(काष्ठा smu_context *smu, bool gate);

पूर्णांक smu_v12_0_घातergate_jpeg(काष्ठा smu_context *smu, bool gate);

पूर्णांक smu_v12_0_set_gfx_cgpg(काष्ठा smu_context *smu, bool enable);

uपूर्णांक32_t smu_v12_0_get_gfxoff_status(काष्ठा smu_context *smu);

पूर्णांक smu_v12_0_gfx_off_control(काष्ठा smu_context *smu, bool enable);

पूर्णांक smu_v12_0_fini_smc_tables(काष्ठा smu_context *smu);

पूर्णांक smu_v12_0_set_शेष_dpm_tables(काष्ठा smu_context *smu);

पूर्णांक smu_v12_0_mode2_reset(काष्ठा smu_context *smu);

पूर्णांक smu_v12_0_set_soft_freq_limited_range(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type,
			    uपूर्णांक32_t min, uपूर्णांक32_t max);

पूर्णांक smu_v12_0_set_driver_table_location(काष्ठा smu_context *smu);

पूर्णांक smu_v12_0_get_vbios_bootup_values(काष्ठा smu_context *smu);

#पूर्ण_अगर
#पूर्ण_अगर
