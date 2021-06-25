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

#समावेश "smumgr.h"
#समावेश "vega20_inc.h"
#समावेश "soc15_common.h"
#समावेश "vega20_smumgr.h"
#समावेश "vega20_ppsmc.h"
#समावेश "smu11_driver_if.h"
#समावेश "ppatomctrl.h"
#समावेश "pp_debug.h"
#समावेश "smu_ucode_xfer_vi.h"
#समावेश "smu7_smumgr.h"
#समावेश "vega20_hwmgr.h"

#समावेश "smu_v11_0_i2c.h"

/* MP Apertures */
#घोषणा MP0_Public			0x03800000
#घोषणा MP0_SRAM			0x03900000
#घोषणा MP1_Public			0x03b00000
#घोषणा MP1_SRAM			0x03c00004

/* address block */
#घोषणा smnMP1_FIRMWARE_FLAGS		0x3010024
#घोषणा smnMP0_FW_INTF			0x30101c0
#घोषणा smnMP1_PUB_CTRL			0x3010b14

bool vega20_is_smc_ram_running(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t mp1_fw_flags;

	mp1_fw_flags = RREG32_PCIE(MP1_Public |
				   (smnMP1_FIRMWARE_FLAGS & 0xffffffff));

	अगर ((mp1_fw_flags & MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED_MASK) >>
	    MP1_FIRMWARE_FLAGS__INTERRUPTS_ENABLED__SHIFT)
		वापस true;

	वापस false;
पूर्ण

/*
 * Check अगर SMC has responded to previous message.
 *
 * @param    smumgr  the address of the घातerplay hardware manager.
 * @वापस   TRUE    SMC has responded, FALSE otherwise.
 */
अटल uपूर्णांक32_t vega20_रुको_क्रम_response(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t reg;

	reg = SOC15_REG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_90);

	phm_रुको_क्रम_रेजिस्टर_unequal(hwmgr, reg,
			0, MP1_C2PMSG_90__CONTENT_MASK);

	वापस RREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90);
पूर्ण

/*
 * Send a message to the SMC, and करो not रुको क्रम its response.
 * @param    smumgr  the address of the घातerplay hardware manager.
 * @param    msg the message to send.
 * @वापस   Always वापस 0.
 */
अटल पूर्णांक vega20_send_msg_to_smc_without_रुकोing(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक16_t msg)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_66, msg);

	वापस 0;
पूर्ण

/*
 * Send a message to the SMC, and रुको क्रम its response.
 * @param    hwmgr  the address of the घातerplay hardware manager.
 * @param    msg the message to send.
 * @वापस   Always वापस 0.
 */
अटल पूर्णांक vega20_send_msg_to_smc(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t msg)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक ret = 0;

	vega20_रुको_क्रम_response(hwmgr);

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	vega20_send_msg_to_smc_without_रुकोing(hwmgr, msg);

	ret = vega20_रुको_क्रम_response(hwmgr);
	अगर (ret != PPSMC_Result_OK)
		pr_err("Failed to send message 0x%x, response 0x%x\n", msg, ret);

	वापस (ret == PPSMC_Result_OK) ? 0 : -EIO;
पूर्ण

/*
 * Send a message to the SMC with parameter
 * @param    hwmgr:  the address of the घातerplay hardware manager.
 * @param    msg: the message to send.
 * @param    parameter: the parameter to send
 * @वापस   Always वापस 0.
 */
अटल पूर्णांक vega20_send_msg_to_smc_with_parameter(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक16_t msg, uपूर्णांक32_t parameter)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक ret = 0;

	vega20_रुको_क्रम_response(hwmgr);

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82, parameter);

	vega20_send_msg_to_smc_without_रुकोing(hwmgr, msg);

	ret = vega20_रुको_क्रम_response(hwmgr);
	अगर (ret != PPSMC_Result_OK)
		pr_err("Failed to send message 0x%x, response 0x%x\n", msg, ret);

	वापस (ret == PPSMC_Result_OK) ? 0 : -EIO;
पूर्ण

अटल uपूर्णांक32_t vega20_get_argument(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	वापस RREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82);
पूर्ण

/*
 * Copy table from SMC पूर्णांकo driver FB
 * @param   hwmgr    the address of the HW manager
 * @param   table_id    the driver's table ID to copy from
 */
अटल पूर्णांक vega20_copy_table_from_smc(काष्ठा pp_hwmgr *hwmgr,
				      uपूर्णांक8_t *table, पूर्णांक16_t table_id)
अणु
	काष्ठा vega20_smumgr *priv =
			(काष्ठा vega20_smumgr *)(hwmgr->smu_backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक ret = 0;

	PP_ASSERT_WITH_CODE(table_id < TABLE_COUNT,
			"Invalid SMU Table ID!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].version != 0,
			"Invalid SMU Table version!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].size != 0,
			"Invalid SMU Table Length!", वापस -EINVAL);

	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrHigh,
			upper_32_bits(priv->smu_tables.entry[table_id].mc_addr),
			शून्य)) == 0,
			"[CopyTableFromSMC] Attempt to Set Dram Addr High Failed!",
			वापस ret);
	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrLow,
			lower_32_bits(priv->smu_tables.entry[table_id].mc_addr),
			शून्य)) == 0,
			"[CopyTableFromSMC] Attempt to Set Dram Addr Low Failed!",
			वापस ret);
	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_TransferTableSmu2Dram, table_id, शून्य)) == 0,
			"[CopyTableFromSMC] Attempt to Transfer Table From SMU Failed!",
			वापस ret);

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
अटल पूर्णांक vega20_copy_table_to_smc(काष्ठा pp_hwmgr *hwmgr,
				    uपूर्णांक8_t *table, पूर्णांक16_t table_id)
अणु
	काष्ठा vega20_smumgr *priv =
			(काष्ठा vega20_smumgr *)(hwmgr->smu_backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक ret = 0;

	PP_ASSERT_WITH_CODE(table_id < TABLE_COUNT,
			"Invalid SMU Table ID!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].version != 0,
			"Invalid SMU Table version!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].size != 0,
			"Invalid SMU Table Length!", वापस -EINVAL);

	स_नकल(priv->smu_tables.entry[table_id].table, table,
			priv->smu_tables.entry[table_id].size);

	amdgpu_asic_flush_hdp(adev, शून्य);

	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrHigh,
			upper_32_bits(priv->smu_tables.entry[table_id].mc_addr),
			शून्य)) == 0,
			"[CopyTableToSMC] Attempt to Set Dram Addr High Failed!",
			वापस ret);
	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrLow,
			lower_32_bits(priv->smu_tables.entry[table_id].mc_addr),
			शून्य)) == 0,
			"[CopyTableToSMC] Attempt to Set Dram Addr Low Failed!",
			वापस ret);
	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_TransferTableDram2Smu, table_id, शून्य)) == 0,
			"[CopyTableToSMC] Attempt to Transfer Table To SMU Failed!",
			वापस ret);

	वापस 0;
पूर्ण

पूर्णांक vega20_set_activity_monitor_coeff(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t *table, uपूर्णांक16_t workload_type)
अणु
	काष्ठा vega20_smumgr *priv =
			(काष्ठा vega20_smumgr *)(hwmgr->smu_backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक ret = 0;

	स_नकल(priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].table, table,
			priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].size);

	amdgpu_asic_flush_hdp(adev, शून्य);

	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrHigh,
			upper_32_bits(priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].mc_addr),
			शून्य)) == 0,
			"[SetActivityMonitor] Attempt to Set Dram Addr High Failed!",
			वापस ret);
	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrLow,
			lower_32_bits(priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].mc_addr),
			शून्य)) == 0,
			"[SetActivityMonitor] Attempt to Set Dram Addr Low Failed!",
			वापस ret);
	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_TransferTableDram2Smu,
			TABLE_ACTIVITY_MONITOR_COEFF | (workload_type << 16),
			शून्य)) == 0,
			"[SetActivityMonitor] Attempt to Transfer Table To SMU Failed!",
			वापस ret);

	वापस 0;
पूर्ण

पूर्णांक vega20_get_activity_monitor_coeff(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t *table, uपूर्णांक16_t workload_type)
अणु
	काष्ठा vega20_smumgr *priv =
			(काष्ठा vega20_smumgr *)(hwmgr->smu_backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक ret = 0;

	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrHigh,
			upper_32_bits(priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].mc_addr),
			शून्य)) == 0,
			"[GetActivityMonitor] Attempt to Set Dram Addr High Failed!",
			वापस ret);
	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrLow,
			lower_32_bits(priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].mc_addr),
			शून्य)) == 0,
			"[GetActivityMonitor] Attempt to Set Dram Addr Low Failed!",
			वापस ret);
	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_TransferTableSmu2Dram,
			TABLE_ACTIVITY_MONITOR_COEFF | (workload_type << 16), शून्य)) == 0,
			"[GetActivityMonitor] Attempt to Transfer Table From SMU Failed!",
			वापस ret);

	amdgpu_asic_invalidate_hdp(adev, शून्य);

	स_नकल(table, priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].table,
			priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].size);

	वापस 0;
पूर्ण

पूर्णांक vega20_enable_smc_features(काष्ठा pp_hwmgr *hwmgr,
		bool enable, uपूर्णांक64_t feature_mask)
अणु
	uपूर्णांक32_t smu_features_low, smu_features_high;
	पूर्णांक ret = 0;

	smu_features_low = (uपूर्णांक32_t)((feature_mask & SMU_FEATURES_LOW_MASK) >> SMU_FEATURES_LOW_SHIFT);
	smu_features_high = (uपूर्णांक32_t)((feature_mask & SMU_FEATURES_HIGH_MASK) >> SMU_FEATURES_HIGH_SHIFT);

	अगर (enable) अणु
		PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_EnableSmuFeaturesLow, smu_features_low, शून्य)) == 0,
				"[EnableDisableSMCFeatures] Attempt to enable SMU features Low failed!",
				वापस ret);
		PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_EnableSmuFeaturesHigh, smu_features_high, शून्य)) == 0,
				"[EnableDisableSMCFeatures] Attempt to enable SMU features High failed!",
				वापस ret);
	पूर्ण अन्यथा अणु
		PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_DisableSmuFeaturesLow, smu_features_low, शून्य)) == 0,
				"[EnableDisableSMCFeatures] Attempt to disable SMU features Low failed!",
				वापस ret);
		PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_DisableSmuFeaturesHigh, smu_features_high, शून्य)) == 0,
				"[EnableDisableSMCFeatures] Attempt to disable SMU features High failed!",
				वापस ret);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vega20_get_enabled_smc_features(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक64_t *features_enabled)
अणु
	uपूर्णांक32_t smc_features_low, smc_features_high;
	पूर्णांक ret = 0;

	अगर (features_enabled == शून्य)
		वापस -EINVAL;

	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc(hwmgr,
			PPSMC_MSG_GetEnabledSmuFeaturesLow,
			&smc_features_low)) == 0,
			"[GetEnabledSMCFeatures] Attempt to get SMU features Low failed!",
			वापस ret);
	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc(hwmgr,
			PPSMC_MSG_GetEnabledSmuFeaturesHigh,
			&smc_features_high)) == 0,
			"[GetEnabledSMCFeatures] Attempt to get SMU features High failed!",
			वापस ret);

	*features_enabled = ((((uपूर्णांक64_t)smc_features_low << SMU_FEATURES_LOW_SHIFT) & SMU_FEATURES_LOW_MASK) |
			(((uपूर्णांक64_t)smc_features_high << SMU_FEATURES_HIGH_SHIFT) & SMU_FEATURES_HIGH_MASK));

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_set_tools_address(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_smumgr *priv =
			(काष्ठा vega20_smumgr *)(hwmgr->smu_backend);
	पूर्णांक ret = 0;

	अगर (priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr) अणु
		ret = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetToolsDramAddrHigh,
				upper_32_bits(priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr),
				शून्य);
		अगर (!ret)
			ret = smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_SetToolsDramAddrLow,
					lower_32_bits(priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr),
					शून्य);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक vega20_set_pptable_driver_address(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_smumgr *priv =
			(काष्ठा vega20_smumgr *)(hwmgr->smu_backend);
	पूर्णांक ret = 0;

	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrHigh,
			upper_32_bits(priv->smu_tables.entry[TABLE_PPTABLE].mc_addr),
			शून्य)) == 0,
			"[SetPPtabeDriverAddress] Attempt to Set Dram Addr High Failed!",
			वापस ret);
	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_SetDriverDramAddrLow,
			lower_32_bits(priv->smu_tables.entry[TABLE_PPTABLE].mc_addr),
			शून्य)) == 0,
			"[SetPPtabeDriverAddress] Attempt to Set Dram Addr Low Failed!",
			वापस ret);

	वापस ret;
पूर्ण

अटल पूर्णांक vega20_smu_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_smumgr *priv;
	अचिन्हित दीर्घ tools_size = 0x19000;
	पूर्णांक ret = 0;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	काष्ठा cgs_firmware_info info = अणु0पूर्ण;

	ret = cgs_get_firmware_info(hwmgr->device,
				smu7_convert_fw_type_to_cgs(UCODE_ID_SMU),
				&info);
	अगर (ret || !info.kptr)
		वापस -EINVAL;

	priv = kzalloc(माप(काष्ठा vega20_smumgr), GFP_KERNEL);
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

	/* allocate space क्रम pmstatuslog table */
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

	/* allocate space क्रम OverDrive table */
	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
			माप(OverDriveTable_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[TABLE_OVERDRIVE].handle,
			&priv->smu_tables.entry[TABLE_OVERDRIVE].mc_addr,
			&priv->smu_tables.entry[TABLE_OVERDRIVE].table);
	अगर (ret)
		जाओ err2;

	priv->smu_tables.entry[TABLE_OVERDRIVE].version = 0x01;
	priv->smu_tables.entry[TABLE_OVERDRIVE].size = माप(OverDriveTable_t);

	/* allocate space क्रम SmuMetrics table */
	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
			माप(SmuMetrics_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[TABLE_SMU_METRICS].handle,
			&priv->smu_tables.entry[TABLE_SMU_METRICS].mc_addr,
			&priv->smu_tables.entry[TABLE_SMU_METRICS].table);
	अगर (ret)
		जाओ err3;

	priv->smu_tables.entry[TABLE_SMU_METRICS].version = 0x01;
	priv->smu_tables.entry[TABLE_SMU_METRICS].size = माप(SmuMetrics_t);

	/* allocate space क्रम ActivityMonitor table */
	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
			माप(DpmActivityMonitorCoeffInt_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].handle,
			&priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].mc_addr,
			&priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].table);
	अगर (ret)
		जाओ err4;

	priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].version = 0x01;
	priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].size = माप(DpmActivityMonitorCoeffInt_t);

	ret = smu_v11_0_i2c_control_init(&adev->pm.smu_i2c);
	अगर (ret)
		जाओ err4;

	वापस 0;

err4:
	amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_SMU_METRICS].handle,
			&priv->smu_tables.entry[TABLE_SMU_METRICS].mc_addr,
			&priv->smu_tables.entry[TABLE_SMU_METRICS].table);
err3:
	amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_OVERDRIVE].handle,
			&priv->smu_tables.entry[TABLE_OVERDRIVE].mc_addr,
			&priv->smu_tables.entry[TABLE_OVERDRIVE].table);
err2:
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

अटल पूर्णांक vega20_smu_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_smumgr *priv =
			(काष्ठा vega20_smumgr *)(hwmgr->smu_backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	smu_v11_0_i2c_control_fini(&adev->pm.smu_i2c);

	अगर (priv) अणु
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_PPTABLE].handle,
				&priv->smu_tables.entry[TABLE_PPTABLE].mc_addr,
				&priv->smu_tables.entry[TABLE_PPTABLE].table);
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_WATERMARKS].handle,
				&priv->smu_tables.entry[TABLE_WATERMARKS].mc_addr,
				&priv->smu_tables.entry[TABLE_WATERMARKS].table);
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_PMSTATUSLOG].handle,
				&priv->smu_tables.entry[TABLE_PMSTATUSLOG].mc_addr,
				&priv->smu_tables.entry[TABLE_PMSTATUSLOG].table);
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_OVERDRIVE].handle,
				&priv->smu_tables.entry[TABLE_OVERDRIVE].mc_addr,
				&priv->smu_tables.entry[TABLE_OVERDRIVE].table);
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_SMU_METRICS].handle,
				&priv->smu_tables.entry[TABLE_SMU_METRICS].mc_addr,
				&priv->smu_tables.entry[TABLE_SMU_METRICS].table);
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].handle,
				&priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].mc_addr,
				&priv->smu_tables.entry[TABLE_ACTIVITY_MONITOR_COEFF].table);
		kमुक्त(hwmgr->smu_backend);
		hwmgr->smu_backend = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_start_smu(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret;

	ret = vega20_is_smc_ram_running(hwmgr);
	PP_ASSERT_WITH_CODE(ret,
			"[Vega20StartSmu] SMC is not running!",
			वापस -EINVAL);

	ret = vega20_set_tools_address(hwmgr);
	PP_ASSERT_WITH_CODE(!ret,
			"[Vega20StartSmu] Failed to set tools address!",
			वापस ret);

	वापस 0;
पूर्ण

अटल bool vega20_is_dpm_running(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक64_t features_enabled = 0;

	vega20_get_enabled_smc_features(hwmgr, &features_enabled);

	अगर (features_enabled & SMC_DPM_FEATURES)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक vega20_smc_table_manager(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t *table,
				    uपूर्णांक16_t table_id, bool rw)
अणु
	पूर्णांक ret;

	अगर (rw)
		ret = vega20_copy_table_from_smc(hwmgr, table, table_id);
	अन्यथा
		ret = vega20_copy_table_to_smc(hwmgr, table, table_id);

	वापस ret;
पूर्ण

स्थिर काष्ठा pp_smumgr_func vega20_smu_funcs = अणु
	.name = "vega20_smu",
	.smu_init = &vega20_smu_init,
	.smu_fini = &vega20_smu_fini,
	.start_smu = &vega20_start_smu,
	.request_smu_load_specअगरic_fw = शून्य,
	.send_msg_to_smc = &vega20_send_msg_to_smc,
	.send_msg_to_smc_with_parameter = &vega20_send_msg_to_smc_with_parameter,
	.करोwnload_pptable_settings = शून्य,
	.upload_pptable_settings = शून्य,
	.is_dpm_running = vega20_is_dpm_running,
	.get_argument = vega20_get_argument,
	.smc_table_manager = vega20_smc_table_manager,
पूर्ण;
