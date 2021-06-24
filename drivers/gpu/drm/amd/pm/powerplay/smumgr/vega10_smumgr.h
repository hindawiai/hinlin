<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
#अगर_अघोषित _VEGA10_SMUMANAGER_H_
#घोषणा _VEGA10_SMUMANAGER_H_

#घोषणा MAX_SMU_TABLE 5

काष्ठा smu_table_entry अणु
	uपूर्णांक32_t version;
	uपूर्णांक32_t size;
	uपूर्णांक32_t table_id;
	uपूर्णांक64_t mc_addr;
	व्योम *table;
	काष्ठा amdgpu_bo *handle;
पूर्ण;

काष्ठा smu_table_array अणु
	काष्ठा smu_table_entry entry[MAX_SMU_TABLE];
पूर्ण;

काष्ठा vega10_smumgr अणु
	काष्ठा smu_table_array            smu_tables;
पूर्ण;

पूर्णांक vega10_enable_smc_features(काष्ठा pp_hwmgr *hwmgr,
			       bool enable, uपूर्णांक32_t feature_mask);
पूर्णांक vega10_get_enabled_smc_features(काष्ठा pp_hwmgr *hwmgr,
				    uपूर्णांक64_t *features_enabled);

#पूर्ण_अगर

