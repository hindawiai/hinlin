<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
#अगर_अघोषित _VEGA20_SMUMANAGER_H_
#घोषणा _VEGA20_SMUMANAGER_H_

#समावेश "hwmgr.h"
#समावेश "smu11_driver_if.h"

काष्ठा smu_table_entry अणु
	uपूर्णांक32_t version;
	uपूर्णांक32_t size;
	uपूर्णांक64_t mc_addr;
	व्योम *table;
	काष्ठा amdgpu_bo *handle;
पूर्ण;

काष्ठा smu_table_array अणु
	काष्ठा smu_table_entry entry[TABLE_COUNT];
पूर्ण;

काष्ठा vega20_smumgr अणु
	काष्ठा smu_table_array            smu_tables;
पूर्ण;

#घोषणा SMU_FEATURES_LOW_MASK        0x00000000FFFFFFFF
#घोषणा SMU_FEATURES_LOW_SHIFT       0
#घोषणा SMU_FEATURES_HIGH_MASK       0xFFFFFFFF00000000
#घोषणा SMU_FEATURES_HIGH_SHIFT      32

पूर्णांक vega20_enable_smc_features(काष्ठा pp_hwmgr *hwmgr,
		bool enable, uपूर्णांक64_t feature_mask);
पूर्णांक vega20_get_enabled_smc_features(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक64_t *features_enabled);
पूर्णांक vega20_set_activity_monitor_coeff(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t *table, uपूर्णांक16_t workload_type);
पूर्णांक vega20_get_activity_monitor_coeff(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t *table, uपूर्णांक16_t workload_type);
पूर्णांक vega20_set_pptable_driver_address(काष्ठा pp_hwmgr *hwmgr);

bool vega20_is_smc_ram_running(काष्ठा pp_hwmgr *hwmgr);

#पूर्ण_अगर

