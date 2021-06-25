<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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

#समावेश "smumgr.h"
#समावेश "vega12_inc.h"
#समावेश "soc15_common.h"
#समावेश "smu9_smumgr.h"
#समावेश "vega12_smumgr.h"
#समावेश "vega12_ppsmc.h"
#समावेश "vega12/smu9_driver_if.h"
#समावेश "ppatomctrl.h"
#समावेश "pp_debug.h"


/*
 * Copy table from SMC पूर्णांकo driver FB
 * @param   hwmgr    the address of the HW manager
 * @param   table_id    the driver's table ID to copy from
 */
अटल पूर्णांक vega12_copy_table_from_smc(काष्ठा pp_hwmgr *hwmgr,
				      uपूर्णांक8_t *table, पूर्णांक16_t table_id)
अणु
	काष्ठा vega12_smumgr *priv =
			(काष्ठा vega12_smumgr *)(hwmgr->smu_backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	PP_ASSERT_WITH_CODE(table_id < TABLE_COUNT,
			"Invalid SMU Table ID!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].version != 0,
			"Invalid SMU Table version!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].size != 0,
			"Invalid SMU Table Length!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrHigh,
			upper_32_bits(priv->smu_tables.entry[table_id].mc_addr),
			शून्य) == 0,
			"[CopyTableFromSMC] Attempt to Set Dram Addr High Failed!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrLow,
			lower_32_bits(priv->smu_tables.entry[table_id].mc_addr),
			शून्य) == 0,
			"[CopyTableFromSMC] Attempt to Set Dram Addr Low Failed!",
			वापस -EINVAL);
	PP_ASSERT_WITH_CODE(smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_TransferTableSmu2Dram,
			table_id,
			शून्य) == 0,
			"[CopyTableFromSMC] Attempt to Transfer Table From SMU Failed!",
			वापस -EINVAL);

	amdgpu_asic_invalidate_hdp(adev, शून्य);

	स_नकल(table, priv->smu_tables.entry[table_id].table,
			priv->smu_tables.entry[table_id].size);

	वापस 0;
पूर्ण

/*
 * Copy table from Driver FB पूर्णांकo SMC
 * @param   hwmgr    the address of the HW manager
 * @param   table_id    the table to copy from
 */
अटल पूर्णांक vega12_copy_table_to_smc(काष्ठा pp_hwmgr *hwmgr,
				    uपूर्णांक8_t *table, पूर्णांक16_t table_id)
अणु
	काष्ठा vega12_smumgr *priv =
			(काष्ठा vega12_smumgr *)(hwmgr->smu_backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	PP_ASSERT_WITH_CODE(table_id < TABLE_COUNT,
			"Invalid SMU Table ID!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].version != 0,
			"Invalid SMU Table version!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].size != 0,
			"Invalid SMU Table Length!", वापस -EINVAL);

	स_नकल(priv->smu_tables.entry[table_id].table, table,
			priv->smu_tables.entry[table_id].size);

	amdgpu_asic_flush_hdp(adev, शून्य);

	PP_ASSERT_WITH_CODE(smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrHigh,
			upper_32_bits(priv->smu_tables.entry[table_id].mc_addr),
			शून्य) == 0,
			"[CopyTableToSMC] Attempt to Set Dram Addr High Failed!",
			वापस -EINVAL;);
	PP_ASSERT_WITH_CODE(smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrLow,
			lower_32_bits(priv->smu_tables.entry[table_id].mc_addr),
			शून्य) == 0,
			"[CopyTableToSMC] Attempt to Set Dram Addr Low Failed!",
			वापस -EINVAL);
	PP_ASSERT_WITH_CODE(smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_TransferTableDram2Smu,
			table_id,
			शून्य) == 0,
			"[CopyTableToSMC] Attempt to Transfer Table To SMU Failed!",
			वापस -EINVAL);

	वापस 0;
पूर्ण

पूर्णांक vega12_enable_smc_features(काष्ठा pp_hwmgr *hwmgr,
		bool enable, uपूर्णांक64_t feature_mask)
अणु
	uपूर्णांक32_t smu_features_low, smu_features_high;

	smu_features_low = (uपूर्णांक32_t)((feature_mask & SMU_FEATURES_LOW_MASK) >> SMU_FEATURES_LOW_SHIFT);
	smu_features_high = (uपूर्णांक32_t)((feature_mask & SMU_FEATURES_HIGH_MASK) >> SMU_FEATURES_HIGH_SHIFT);

	अगर (enable) अणु
		PP_ASSERT_WITH_CODE(smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_EnableSmuFeaturesLow, smu_features_low, शून्य) == 0,
				"[EnableDisableSMCFeatures] Attempt to enable SMU features Low failed!",
				वापस -EINVAL);
		PP_ASSERT_WITH_CODE(smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_EnableSmuFeaturesHigh, smu_features_high, शून्य) == 0,
				"[EnableDisableSMCFeatures] Attempt to enable SMU features High failed!",
				वापस -EINVAL);
	पूर्ण अन्यथा अणु
		PP_ASSERT_WITH_CODE(smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_DisableSmuFeaturesLow, smu_features_low, शून्य) == 0,
				"[EnableDisableSMCFeatures] Attempt to disable SMU features Low failed!",
				वापस -EINVAL);
		PP_ASSERT_WITH_CODE(smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_DisableSmuFeaturesHigh, smu_features_high, शून्य) == 0,
				"[EnableDisableSMCFeatures] Attempt to disable SMU features High failed!",
				वापस -EINVAL);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vega12_get_enabled_smc_features(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक64_t *features_enabled)
अणु
	uपूर्णांक32_t smc_features_low, smc_features_high;

	अगर (features_enabled == शून्य)
		वापस -EINVAL;

	PP_ASSERT_WITH_CODE(smum_send_msg_to_smc(hwmgr,
			PPSMC_MSG_GetEnabledSmuFeaturesLow,
			&smc_features_low) == 0,
			"[GetEnabledSMCFeatures] Attempt to get SMU features Low failed!",
			वापस -EINVAL);

	PP_ASSERT_WITH_CODE(smum_send_msg_to_smc(hwmgr,
			PPSMC_MSG_GetEnabledSmuFeaturesHigh,
			&smc_features_high) == 0,
			"[GetEnabledSMCFeatures] Attempt to get SMU features High failed!",
			वापस -EINVAL);

	*features_enabled = ((((uपूर्णांक64_t)smc_features_low << SMU_FEATURES_LOW_SHIFT) & SMU_FEATURES_LOW_MASK) |
			(((uपूर्णांक64_t)smc_features_high << SMU_FEATURES_HIGH_SHIFT) & SMU_FEATURES_HIGH_MASK));

	वापस 0;
पूर्ण

अटल bool vega12_is_dpm_running(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक64_t features_enabled = 0;

	vega12_get_enabled_smc_features(hwmgr, &features_enabled);

	अगर (features_enabled & SMC_DPM_FEATURES)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक vega12_set_tools_address(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_smumgr *priv =
			(काष्ठा vega12_smumgr *)(hwmgr->smu_backend);

	अगर (priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr) अणु
		अगर (!smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetToolsDramAddrHigh,
				upper_32_bits(priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr),
				शून्य))
			smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetToolsDramAddrLow,
					lower_32_bits(priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr),
					शून्य);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vega12_smu_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_smumgr *priv;
	अचिन्हित दीर्घ tools_size;
	काष्ठा cgs_firmware_info info = अणु0पूर्ण;
	पूर्णांक ret;

	ret = cgs_get_firmware_info(hwmgr->device, CGS_UCODE_ID_SMU,
				&info);
	अगर (ret || !info.kptr)
		वापस -EINVAL;

	priv = kzalloc(माप(काष्ठा vega12_smumgr), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	hwmgr->smu_backend = priv;

	/* allocate space क्रम pptable */
	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
			माप(PPTable_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[TABLE_PPTABLE].handle,
			&priv->smu_tables.entry[TABLE_PPTABLE].mc_addr,
			&priv->smu_tables.entry[TABLE_PPTABLE].table);
	अगर (ret)
		जाओ मुक्त_backend;

	priv->smu_tables.entry[TABLE_PPTABLE].version = 0x01;
	priv->smu_tables.entry[TABLE_PPTABLE].size = माप(PPTable_t);

	/* allocate space क्रम watermarks table */
	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
				      माप(Watermarks_t),
				      PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &priv->smu_tables.entry[TABLE_WATERMARKS].handle,
				      &priv->smu_tables.entry[TABLE_WATERMARKS].mc_addr,
				      &priv->smu_tables.entry[TABLE_WATERMARKS].table);

	अगर (ret)
		जाओ err0;

	priv->smu_tables.entry[TABLE_WATERMARKS].version = 0x01;
	priv->smu_tables.entry[TABLE_WATERMARKS].size = माप(Watermarks_t);

	tools_size = 0x19000;
	अगर (tools_size) अणु
		ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
					      tools_size,
					      PAGE_SIZE,
					      AMDGPU_GEM_DOMAIN_VRAM,
					      &priv->smu_tables.entry[TABLE_PMSTATUSLOG].handle,
					      &priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr,
					      &priv->smu_tables.entry[TABLE_PMSTATUSLOG].table);
		अगर (ret)
			जाओ err1;

		priv->smu_tables.entry[TABLE_PMSTATUSLOG].version = 0x01;
		priv->smu_tables.entry[TABLE_PMSTATUSLOG].size = tools_size;
	पूर्ण

	/* allocate space क्रम AVFS Fuse table */
	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
				      माप(AvfsFuseOverride_t),
				      PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].handle,
				      &priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].mc_addr,
				      &priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].table);

	अगर (ret)
		जाओ err2;

	priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].version = 0x01;
	priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].size = माप(AvfsFuseOverride_t);

	/* allocate space क्रम OverDrive table */
	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
				      माप(OverDriveTable_t),
				      PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &priv->smu_tables.entry[TABLE_OVERDRIVE].handle,
				      &priv->smu_tables.entry[TABLE_OVERDRIVE].mc_addr,
				      &priv->smu_tables.entry[TABLE_OVERDRIVE].table);
	अगर (ret)
		जाओ err3;

	priv->smu_tables.entry[TABLE_OVERDRIVE].version = 0x01;
	priv->smu_tables.entry[TABLE_OVERDRIVE].size = माप(OverDriveTable_t);

	/* allocate space क्रम SMU_METRICS table */
	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
				      माप(SmuMetrics_t),
				      PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &priv->smu_tables.entry[TABLE_SMU_METRICS].handle,
				      &priv->smu_tables.entry[TABLE_SMU_METRICS].mc_addr,
				      &priv->smu_tables.entry[TABLE_SMU_METRICS].table);
	अगर (ret)
		जाओ err4;

	priv->smu_tables.entry[TABLE_SMU_METRICS].version = 0x01;
	priv->smu_tables.entry[TABLE_SMU_METRICS].size = माप(SmuMetrics_t);

	वापस 0;

err4:
	amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_OVERDRIVE].handle,
				&priv->smu_tables.entry[TABLE_OVERDRIVE].mc_addr,
				&priv->smu_tables.entry[TABLE_OVERDRIVE].table);
err3:
	amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].handle,
				&priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].mc_addr,
				&priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].table);
err2:
	अगर (priv->smu_tables.entry[TABLE_PMSTATUSLOG].table)
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_PMSTATUSLOG].handle,
				&priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr,
				&priv->smu_tables.entry[TABLE_PMSTATUSLOG].table);
err1:
	amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_WATERMARKS].handle,
				&priv->smu_tables.entry[TABLE_WATERMARKS].mc_addr,
				&priv->smu_tables.entry[TABLE_WATERMARKS].table);
err0:
	amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_PPTABLE].handle,
			&priv->smu_tables.entry[TABLE_PPTABLE].mc_addr,
			&priv->smu_tables.entry[TABLE_PPTABLE].table);
मुक्त_backend:
	kमुक्त(hwmgr->smu_backend);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vega12_smu_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega12_smumgr *priv =
			(काष्ठा vega12_smumgr *)(hwmgr->smu_backend);

	अगर (priv) अणु
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_PPTABLE].handle,
				      &priv->smu_tables.entry[TABLE_PPTABLE].mc_addr,
				      &priv->smu_tables.entry[TABLE_PPTABLE].table);
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_WATERMARKS].handle,
				      &priv->smu_tables.entry[TABLE_WATERMARKS].mc_addr,
				      &priv->smu_tables.entry[TABLE_WATERMARKS].table);
		अगर (priv->smu_tables.entry[TABLE_PMSTATUSLOG].table)
			amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_PMSTATUSLOG].handle,
					      &priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr,
					      &priv->smu_tables.entry[TABLE_PMSTATUSLOG].table);
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].handle,
				      &priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].mc_addr,
				      &priv->smu_tables.entry[TABLE_AVFS_FUSE_OVERRIDE].table);
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_OVERDRIVE].handle,
				      &priv->smu_tables.entry[TABLE_OVERDRIVE].mc_addr,
				      &priv->smu_tables.entry[TABLE_OVERDRIVE].table);
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_SMU_METRICS].handle,
				      &priv->smu_tables.entry[TABLE_SMU_METRICS].mc_addr,
				      &priv->smu_tables.entry[TABLE_SMU_METRICS].table);
		kमुक्त(hwmgr->smu_backend);
		hwmgr->smu_backend = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vega12_start_smu(काष्ठा pp_hwmgr *hwmgr)
अणु
	PP_ASSERT_WITH_CODE(smu9_is_smc_ram_running(hwmgr),
			"SMC is not running!",
			वापस -EINVAL);

	vega12_set_tools_address(hwmgr);

	वापस 0;
पूर्ण

अटल पूर्णांक vega12_smc_table_manager(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t *table,
				    uपूर्णांक16_t table_id, bool rw)
अणु
	पूर्णांक ret;

	अगर (rw)
		ret = vega12_copy_table_from_smc(hwmgr, table, table_id);
	अन्यथा
		ret = vega12_copy_table_to_smc(hwmgr, table, table_id);

	वापस ret;
पूर्ण

स्थिर काष्ठा pp_smumgr_func vega12_smu_funcs = अणु
	.name = "vega12_smu",
	.smu_init = &vega12_smu_init,
	.smu_fini = &vega12_smu_fini,
	.start_smu = &vega12_start_smu,
	.request_smu_load_specअगरic_fw = शून्य,
	.send_msg_to_smc = &smu9_send_msg_to_smc,
	.send_msg_to_smc_with_parameter = &smu9_send_msg_to_smc_with_parameter,
	.करोwnload_pptable_settings = शून्य,
	.upload_pptable_settings = शून्य,
	.is_dpm_running = vega12_is_dpm_running,
	.get_argument = smu9_get_argument,
	.smc_table_manager = vega12_smc_table_manager,
पूर्ण;
