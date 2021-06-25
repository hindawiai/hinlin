<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <drm/amdgpu_drm.h>
#समावेश "smumgr.h"

MODULE_FIRMWARE("amdgpu/bonaire_smc.bin");
MODULE_FIRMWARE("amdgpu/bonaire_k_smc.bin");
MODULE_FIRMWARE("amdgpu/hawaii_smc.bin");
MODULE_FIRMWARE("amdgpu/hawaii_k_smc.bin");
MODULE_FIRMWARE("amdgpu/topaz_smc.bin");
MODULE_FIRMWARE("amdgpu/topaz_k_smc.bin");
MODULE_FIRMWARE("amdgpu/tonga_smc.bin");
MODULE_FIRMWARE("amdgpu/tonga_k_smc.bin");
MODULE_FIRMWARE("amdgpu/fiji_smc.bin");
MODULE_FIRMWARE("amdgpu/polaris10_smc.bin");
MODULE_FIRMWARE("amdgpu/polaris10_smc_sk.bin");
MODULE_FIRMWARE("amdgpu/polaris10_k_smc.bin");
MODULE_FIRMWARE("amdgpu/polaris10_k2_smc.bin");
MODULE_FIRMWARE("amdgpu/polaris11_smc.bin");
MODULE_FIRMWARE("amdgpu/polaris11_smc_sk.bin");
MODULE_FIRMWARE("amdgpu/polaris11_k_smc.bin");
MODULE_FIRMWARE("amdgpu/polaris11_k2_smc.bin");
MODULE_FIRMWARE("amdgpu/polaris12_smc.bin");
MODULE_FIRMWARE("amdgpu/polaris12_k_smc.bin");
MODULE_FIRMWARE("amdgpu/vegam_smc.bin");
MODULE_FIRMWARE("amdgpu/vega10_smc.bin");
MODULE_FIRMWARE("amdgpu/vega10_acg_smc.bin");
MODULE_FIRMWARE("amdgpu/vega12_smc.bin");
MODULE_FIRMWARE("amdgpu/vega20_smc.bin");

पूर्णांक smum_thermal_avfs_enable(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (शून्य != hwmgr->smumgr_funcs->thermal_avfs_enable)
		वापस hwmgr->smumgr_funcs->thermal_avfs_enable(hwmgr);

	वापस 0;
पूर्ण

पूर्णांक smum_thermal_setup_fan_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (शून्य != hwmgr->smumgr_funcs->thermal_setup_fan_table)
		वापस hwmgr->smumgr_funcs->thermal_setup_fan_table(hwmgr);

	वापस 0;
पूर्ण

पूर्णांक smum_update_sclk_threshold(काष्ठा pp_hwmgr *hwmgr)
अणु

	अगर (शून्य != hwmgr->smumgr_funcs->update_sclk_threshold)
		वापस hwmgr->smumgr_funcs->update_sclk_threshold(hwmgr);

	वापस 0;
पूर्ण

पूर्णांक smum_update_smc_table(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t type)
अणु

	अगर (शून्य != hwmgr->smumgr_funcs->update_smc_table)
		वापस hwmgr->smumgr_funcs->update_smc_table(hwmgr, type);

	वापस 0;
पूर्ण

uपूर्णांक32_t smum_get_दुरत्व(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t type, uपूर्णांक32_t member)
अणु
	अगर (शून्य != hwmgr->smumgr_funcs->get_दुरत्व)
		वापस hwmgr->smumgr_funcs->get_दुरत्व(type, member);

	वापस 0;
पूर्ण

पूर्णांक smum_process_firmware_header(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (शून्य != hwmgr->smumgr_funcs->process_firmware_header)
		वापस hwmgr->smumgr_funcs->process_firmware_header(hwmgr);
	वापस 0;
पूर्ण

uपूर्णांक32_t smum_get_mac_definition(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t value)
अणु
	अगर (शून्य != hwmgr->smumgr_funcs->get_mac_definition)
		वापस hwmgr->smumgr_funcs->get_mac_definition(value);

	वापस 0;
पूर्ण

पूर्णांक smum_करोwnload_घातerplay_table(काष्ठा pp_hwmgr *hwmgr, व्योम **table)
अणु
	अगर (शून्य != hwmgr->smumgr_funcs->करोwnload_pptable_settings)
		वापस hwmgr->smumgr_funcs->करोwnload_pptable_settings(hwmgr,
									table);
	वापस 0;
पूर्ण

पूर्णांक smum_upload_घातerplay_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (शून्य != hwmgr->smumgr_funcs->upload_pptable_settings)
		वापस hwmgr->smumgr_funcs->upload_pptable_settings(hwmgr);

	वापस 0;
पूर्ण

पूर्णांक smum_send_msg_to_smc(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t msg, uपूर्णांक32_t *resp)
अणु
	पूर्णांक ret = 0;

	अगर (hwmgr == शून्य ||
	    hwmgr->smumgr_funcs->send_msg_to_smc == शून्य ||
	    (resp && !hwmgr->smumgr_funcs->get_argument))
		वापस -EINVAL;

	mutex_lock(&hwmgr->msg_lock);

	ret = hwmgr->smumgr_funcs->send_msg_to_smc(hwmgr, msg);
	अगर (ret) अणु
		mutex_unlock(&hwmgr->msg_lock);
		वापस ret;
	पूर्ण

	अगर (resp)
		*resp = hwmgr->smumgr_funcs->get_argument(hwmgr);

	mutex_unlock(&hwmgr->msg_lock);

	वापस ret;
पूर्ण

पूर्णांक smum_send_msg_to_smc_with_parameter(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक16_t msg,
					uपूर्णांक32_t parameter,
					uपूर्णांक32_t *resp)
अणु
	पूर्णांक ret = 0;

	अगर (hwmgr == शून्य ||
	    hwmgr->smumgr_funcs->send_msg_to_smc_with_parameter == शून्य ||
	    (resp && !hwmgr->smumgr_funcs->get_argument))
		वापस -EINVAL;

	mutex_lock(&hwmgr->msg_lock);

	ret = hwmgr->smumgr_funcs->send_msg_to_smc_with_parameter(
						hwmgr, msg, parameter);
	अगर (ret) अणु
		mutex_unlock(&hwmgr->msg_lock);
		वापस ret;
	पूर्ण

	अगर (resp)
		*resp = hwmgr->smumgr_funcs->get_argument(hwmgr);

	mutex_unlock(&hwmgr->msg_lock);

	वापस ret;
पूर्ण

पूर्णांक smum_init_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (शून्य != hwmgr->smumgr_funcs->init_smc_table)
		वापस hwmgr->smumgr_funcs->init_smc_table(hwmgr);

	वापस 0;
पूर्ण

पूर्णांक smum_populate_all_graphic_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (शून्य != hwmgr->smumgr_funcs->populate_all_graphic_levels)
		वापस hwmgr->smumgr_funcs->populate_all_graphic_levels(hwmgr);

	वापस 0;
पूर्ण

पूर्णांक smum_populate_all_memory_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (शून्य != hwmgr->smumgr_funcs->populate_all_memory_levels)
		वापस hwmgr->smumgr_funcs->populate_all_memory_levels(hwmgr);

	वापस 0;
पूर्ण

/*this पूर्णांकerface is needed by island ci/vi */
पूर्णांक smum_initialize_mc_reg_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (शून्य != hwmgr->smumgr_funcs->initialize_mc_reg_table)
		वापस hwmgr->smumgr_funcs->initialize_mc_reg_table(hwmgr);

	वापस 0;
पूर्ण

bool smum_is_dpm_running(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (शून्य != hwmgr->smumgr_funcs->is_dpm_running)
		वापस hwmgr->smumgr_funcs->is_dpm_running(hwmgr);

	वापस true;
पूर्ण

bool smum_is_hw_avfs_present(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (hwmgr->smumgr_funcs->is_hw_avfs_present)
		वापस hwmgr->smumgr_funcs->is_hw_avfs_present(hwmgr);

	वापस false;
पूर्ण

पूर्णांक smum_update_dpm_settings(काष्ठा pp_hwmgr *hwmgr, व्योम *profile_setting)
अणु
	अगर (hwmgr->smumgr_funcs->update_dpm_settings)
		वापस hwmgr->smumgr_funcs->update_dpm_settings(hwmgr, profile_setting);

	वापस -EINVAL;
पूर्ण

पूर्णांक smum_smc_table_manager(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t *table, uपूर्णांक16_t table_id, bool rw)
अणु
	अगर (hwmgr->smumgr_funcs->smc_table_manager)
		वापस hwmgr->smumgr_funcs->smc_table_manager(hwmgr, table, table_id, rw);

	वापस -EINVAL;
पूर्ण

पूर्णांक smum_stop_smc(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (hwmgr->smumgr_funcs->stop_smc)
		वापस hwmgr->smumgr_funcs->stop_smc(hwmgr);

	वापस 0;
पूर्ण
