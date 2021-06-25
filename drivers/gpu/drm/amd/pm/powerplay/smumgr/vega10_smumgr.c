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

#समावेश <linux/pci.h>

#समावेश "smumgr.h"
#समावेश "vega10_inc.h"
#समावेश "soc15_common.h"
#समावेश "vega10_smumgr.h"
#समावेश "vega10_hwmgr.h"
#समावेश "vega10_ppsmc.h"
#समावेश "smu9_driver_if.h"
#समावेश "smu9_smumgr.h"
#समावेश "ppatomctrl.h"
#समावेश "pp_debug.h"


अटल पूर्णांक vega10_copy_table_from_smc(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t *table, पूर्णांक16_t table_id)
अणु
	काष्ठा vega10_smumgr *priv = hwmgr->smu_backend;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	PP_ASSERT_WITH_CODE(table_id < MAX_SMU_TABLE,
			"Invalid SMU Table ID!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].version != 0,
			"Invalid SMU Table version!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].size != 0,
			"Invalid SMU Table Length!", वापस -EINVAL);
	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrHigh,
			upper_32_bits(priv->smu_tables.entry[table_id].mc_addr),
			शून्य);
	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrLow,
			lower_32_bits(priv->smu_tables.entry[table_id].mc_addr),
			शून्य);
	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_TransferTableSmu2Dram,
			priv->smu_tables.entry[table_id].table_id,
			शून्य);

	amdgpu_asic_invalidate_hdp(adev, शून्य);

	स_नकल(table, priv->smu_tables.entry[table_id].table,
			priv->smu_tables.entry[table_id].size);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_copy_table_to_smc(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t *table, पूर्णांक16_t table_id)
अणु
	काष्ठा vega10_smumgr *priv = hwmgr->smu_backend;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	/* under sriov, vbios or hypervisor driver
	 * has alपढ़ोy copy table to smc so here only skip it
	 */
	अगर (!hwmgr->not_vf)
		वापस 0;

	PP_ASSERT_WITH_CODE(table_id < MAX_SMU_TABLE,
			"Invalid SMU Table ID!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].version != 0,
			"Invalid SMU Table version!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].size != 0,
			"Invalid SMU Table Length!", वापस -EINVAL);

	स_नकल(priv->smu_tables.entry[table_id].table, table,
			priv->smu_tables.entry[table_id].size);

	amdgpu_asic_flush_hdp(adev, शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrHigh,
			upper_32_bits(priv->smu_tables.entry[table_id].mc_addr),
			शून्य);
	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrLow,
			lower_32_bits(priv->smu_tables.entry[table_id].mc_addr),
			शून्य);
	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_TransferTableDram2Smu,
			priv->smu_tables.entry[table_id].table_id,
			शून्य);

	वापस 0;
पूर्ण

पूर्णांक vega10_enable_smc_features(काष्ठा pp_hwmgr *hwmgr,
			       bool enable, uपूर्णांक32_t feature_mask)
अणु
	पूर्णांक msg = enable ? PPSMC_MSG_EnableSmuFeatures :
			PPSMC_MSG_DisableSmuFeatures;

	/* VF has no permission to change smu feature due
	 * to security concern even under pp one vf mode
	 * it still can't करो it. For vega10, the smu in
	 * vbios will enable the appropriate features.
	 * */
	अगर (!hwmgr->not_vf)
		वापस 0;

	वापस smum_send_msg_to_smc_with_parameter(hwmgr,
			msg, feature_mask, शून्य);
पूर्ण

पूर्णांक vega10_get_enabled_smc_features(काष्ठा pp_hwmgr *hwmgr,
			    uपूर्णांक64_t *features_enabled)
अणु
	uपूर्णांक32_t enabled_features;

	अगर (features_enabled == शून्य)
		वापस -EINVAL;

	smum_send_msg_to_smc(hwmgr,
			PPSMC_MSG_GetEnabledSmuFeatures,
			&enabled_features);
	*features_enabled = enabled_features;

	वापस 0;
पूर्ण

अटल bool vega10_is_dpm_running(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक64_t features_enabled = 0;

	vega10_get_enabled_smc_features(hwmgr, &features_enabled);

	अगर (features_enabled & SMC_DPM_FEATURES)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक vega10_set_tools_address(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_smumgr *priv = hwmgr->smu_backend;

	अगर (priv->smu_tables.entry[TOOLSTABLE].mc_addr) अणु
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetToolsDramAddrHigh,
				upper_32_bits(priv->smu_tables.entry[TOOLSTABLE].mc_addr),
				शून्य);
		smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetToolsDramAddrLow,
				lower_32_bits(priv->smu_tables.entry[TOOLSTABLE].mc_addr),
				शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vega10_verअगरy_smc_पूर्णांकerface(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t smc_driver_अगर_version;
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t dev_id;
	uपूर्णांक32_t rev_id;

	PP_ASSERT_WITH_CODE(!smum_send_msg_to_smc(hwmgr,
			PPSMC_MSG_GetDriverIfVersion,
			&smc_driver_अगर_version),
			"Attempt to get SMC IF Version Number Failed!",
			वापस -EINVAL);

	dev_id = adev->pdev->device;
	rev_id = adev->pdev->revision;

	अगर (!((dev_id == 0x687f) &&
		((rev_id == 0xc0) ||
		(rev_id == 0xc1) ||
		(rev_id == 0xc3)))) अणु
		अगर (smc_driver_अगर_version != SMU9_DRIVER_IF_VERSION) अणु
			pr_err("Your firmware(0x%x) doesn't match SMU9_DRIVER_IF_VERSION(0x%x). Please update your firmware!\n",
			       smc_driver_अगर_version, SMU9_DRIVER_IF_VERSION);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_smu_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_smumgr *priv;
	अचिन्हित दीर्घ tools_size;
	पूर्णांक ret;
	काष्ठा cgs_firmware_info info = अणु0पूर्ण;

	ret = cgs_get_firmware_info(hwmgr->device,
					CGS_UCODE_ID_SMU,
					&info);
	अगर (ret || !info.kptr)
		वापस -EINVAL;

	priv = kzalloc(माप(काष्ठा vega10_smumgr), GFP_KERNEL);

	अगर (!priv)
		वापस -ENOMEM;

	hwmgr->smu_backend = priv;

	/* allocate space क्रम pptable */
	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
			माप(PPTable_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[PPTABLE].handle,
			&priv->smu_tables.entry[PPTABLE].mc_addr,
			&priv->smu_tables.entry[PPTABLE].table);
	अगर (ret)
		जाओ मुक्त_backend;

	priv->smu_tables.entry[PPTABLE].version = 0x01;
	priv->smu_tables.entry[PPTABLE].size = माप(PPTable_t);
	priv->smu_tables.entry[PPTABLE].table_id = TABLE_PPTABLE;

	/* allocate space क्रम watermarks table */
	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
			माप(Watermarks_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[WMTABLE].handle,
			&priv->smu_tables.entry[WMTABLE].mc_addr,
			&priv->smu_tables.entry[WMTABLE].table);

	अगर (ret)
		जाओ err0;

	priv->smu_tables.entry[WMTABLE].version = 0x01;
	priv->smu_tables.entry[WMTABLE].size = माप(Watermarks_t);
	priv->smu_tables.entry[WMTABLE].table_id = TABLE_WATERMARKS;

	/* allocate space क्रम AVFS table */
	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
			माप(AvfsTable_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[AVFSTABLE].handle,
			&priv->smu_tables.entry[AVFSTABLE].mc_addr,
			&priv->smu_tables.entry[AVFSTABLE].table);

	अगर (ret)
		जाओ err1;

	priv->smu_tables.entry[AVFSTABLE].version = 0x01;
	priv->smu_tables.entry[AVFSTABLE].size = माप(AvfsTable_t);
	priv->smu_tables.entry[AVFSTABLE].table_id = TABLE_AVFS;

	tools_size = 0x19000;
	अगर (tools_size) अणु
		ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
				tools_size,
				PAGE_SIZE,
				AMDGPU_GEM_DOMAIN_VRAM,
				&priv->smu_tables.entry[TOOLSTABLE].handle,
				&priv->smu_tables.entry[TOOLSTABLE].mc_addr,
				&priv->smu_tables.entry[TOOLSTABLE].table);
		अगर (ret)
			जाओ err2;
		priv->smu_tables.entry[TOOLSTABLE].version = 0x01;
		priv->smu_tables.entry[TOOLSTABLE].size = tools_size;
		priv->smu_tables.entry[TOOLSTABLE].table_id = TABLE_PMSTATUSLOG;
	पूर्ण

	/* allocate space क्रम AVFS Fuse table */
	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
			माप(AvfsFuseOverride_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[AVFSFUSETABLE].handle,
			&priv->smu_tables.entry[AVFSFUSETABLE].mc_addr,
			&priv->smu_tables.entry[AVFSFUSETABLE].table);
	अगर (ret)
		जाओ err3;

	priv->smu_tables.entry[AVFSFUSETABLE].version = 0x01;
	priv->smu_tables.entry[AVFSFUSETABLE].size = माप(AvfsFuseOverride_t);
	priv->smu_tables.entry[AVFSFUSETABLE].table_id = TABLE_AVFS_FUSE_OVERRIDE;


	वापस 0;

err3:
	अगर (priv->smu_tables.entry[TOOLSTABLE].table)
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TOOLSTABLE].handle,
				&priv->smu_tables.entry[TOOLSTABLE].mc_addr,
				&priv->smu_tables.entry[TOOLSTABLE].table);
err2:
	amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[AVFSTABLE].handle,
				&priv->smu_tables.entry[AVFSTABLE].mc_addr,
				&priv->smu_tables.entry[AVFSTABLE].table);
err1:
	amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[WMTABLE].handle,
				&priv->smu_tables.entry[WMTABLE].mc_addr,
				&priv->smu_tables.entry[WMTABLE].table);
err0:
	amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[PPTABLE].handle,
			&priv->smu_tables.entry[PPTABLE].mc_addr,
			&priv->smu_tables.entry[PPTABLE].table);
मुक्त_backend:
	kमुक्त(hwmgr->smu_backend);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vega10_smu_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_smumgr *priv = hwmgr->smu_backend;

	अगर (priv) अणु
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[PPTABLE].handle,
				&priv->smu_tables.entry[PPTABLE].mc_addr,
				&priv->smu_tables.entry[PPTABLE].table);
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[WMTABLE].handle,
					&priv->smu_tables.entry[WMTABLE].mc_addr,
					&priv->smu_tables.entry[WMTABLE].table);
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[AVFSTABLE].handle,
					&priv->smu_tables.entry[AVFSTABLE].mc_addr,
					&priv->smu_tables.entry[AVFSTABLE].table);
		अगर (priv->smu_tables.entry[TOOLSTABLE].table)
			amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TOOLSTABLE].handle,
					&priv->smu_tables.entry[TOOLSTABLE].mc_addr,
					&priv->smu_tables.entry[TOOLSTABLE].table);
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[AVFSFUSETABLE].handle,
					&priv->smu_tables.entry[AVFSFUSETABLE].mc_addr,
					&priv->smu_tables.entry[AVFSFUSETABLE].table);
		kमुक्त(hwmgr->smu_backend);
		hwmgr->smu_backend = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vega10_start_smu(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (!smu9_is_smc_ram_running(hwmgr))
		वापस -EINVAL;

	PP_ASSERT_WITH_CODE(!vega10_verअगरy_smc_पूर्णांकerface(hwmgr),
			"Failed to verify SMC interface!",
			वापस -EINVAL);

	vega10_set_tools_address(hwmgr);

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_smc_table_manager(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t *table,
				    uपूर्णांक16_t table_id, bool rw)
अणु
	पूर्णांक ret;

	अगर (rw)
		ret = vega10_copy_table_from_smc(hwmgr, table, table_id);
	अन्यथा
		ret = vega10_copy_table_to_smc(hwmgr, table, table_id);

	वापस ret;
पूर्ण

स्थिर काष्ठा pp_smumgr_func vega10_smu_funcs = अणु
	.name = "vega10_smu",
	.smu_init = &vega10_smu_init,
	.smu_fini = &vega10_smu_fini,
	.start_smu = &vega10_start_smu,
	.request_smu_load_specअगरic_fw = शून्य,
	.send_msg_to_smc = &smu9_send_msg_to_smc,
	.send_msg_to_smc_with_parameter = &smu9_send_msg_to_smc_with_parameter,
	.करोwnload_pptable_settings = शून्य,
	.upload_pptable_settings = शून्य,
	.is_dpm_running = vega10_is_dpm_running,
	.get_argument = smu9_get_argument,
	.smc_table_manager = vega10_smc_table_manager,
पूर्ण;
