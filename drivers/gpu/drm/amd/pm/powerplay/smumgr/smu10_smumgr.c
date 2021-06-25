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
#समावेश "smu10_inc.h"
#समावेश "soc15_common.h"
#समावेश "smu10_smumgr.h"
#समावेश "ppatomctrl.h"
#समावेश "rv_ppsmc.h"
#समावेश "smu10_driver_if.h"
#समावेश "smu10.h"
#समावेश "pp_debug.h"


#घोषणा BUFFER_SIZE                 80000
#घोषणा MAX_STRING_SIZE             15
#घोषणा BUFFER_SIZETWO              131072

#घोषणा MP0_Public                  0x03800000
#घोषणा MP0_SRAM                    0x03900000
#घोषणा MP1_Public                  0x03b00000
#घोषणा MP1_SRAM                    0x03c00004

#घोषणा smnMP1_FIRMWARE_FLAGS       0x3010028


अटल uपूर्णांक32_t smu10_रुको_क्रम_response(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t reg;

	reg = SOC15_REG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_90);

	phm_रुको_क्रम_रेजिस्टर_unequal(hwmgr, reg,
			0, MP1_C2PMSG_90__CONTENT_MASK);

	वापस RREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90);
पूर्ण

अटल पूर्णांक smu10_send_msg_to_smc_without_रुकोing(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक16_t msg)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_66, msg);

	वापस 0;
पूर्ण

अटल uपूर्णांक32_t smu10_पढ़ो_arg_from_smc(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	वापस RREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82);
पूर्ण

अटल पूर्णांक smu10_send_msg_to_smc(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t msg)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	smu10_रुको_क्रम_response(hwmgr);

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	smu10_send_msg_to_smc_without_रुकोing(hwmgr, msg);

	अगर (smu10_रुको_क्रम_response(hwmgr) == 0)
		prपूर्णांकk("Failed to send Message %x.\n", msg);

	वापस 0;
पूर्ण


अटल पूर्णांक smu10_send_msg_to_smc_with_parameter(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक16_t msg, uपूर्णांक32_t parameter)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	smu10_रुको_क्रम_response(hwmgr);

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_90, 0);

	WREG32_SOC15(MP1, 0, mmMP1_SMN_C2PMSG_82, parameter);

	smu10_send_msg_to_smc_without_रुकोing(hwmgr, msg);


	अगर (smu10_रुको_क्रम_response(hwmgr) == 0)
		prपूर्णांकk("Failed to send Message %x.\n", msg);

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_copy_table_from_smc(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t *table, पूर्णांक16_t table_id)
अणु
	काष्ठा smu10_smumgr *priv =
			(काष्ठा smu10_smumgr *)(hwmgr->smu_backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	PP_ASSERT_WITH_CODE(table_id < MAX_SMU_TABLE,
			"Invalid SMU Table ID!", वापस -EINVAL;);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].version != 0,
			"Invalid SMU Table version!", वापस -EINVAL;);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].size != 0,
			"Invalid SMU Table Length!", वापस -EINVAL;);
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

	स_नकल(table, (uपूर्णांक8_t *)priv->smu_tables.entry[table_id].table,
			priv->smu_tables.entry[table_id].size);

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_copy_table_to_smc(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t *table, पूर्णांक16_t table_id)
अणु
	काष्ठा smu10_smumgr *priv =
			(काष्ठा smu10_smumgr *)(hwmgr->smu_backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	PP_ASSERT_WITH_CODE(table_id < MAX_SMU_TABLE,
			"Invalid SMU Table ID!", वापस -EINVAL;);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].version != 0,
			"Invalid SMU Table version!", वापस -EINVAL;);
	PP_ASSERT_WITH_CODE(priv->smu_tables.entry[table_id].size != 0,
			"Invalid SMU Table Length!", वापस -EINVAL;);

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

अटल पूर्णांक smu10_verअगरy_smc_पूर्णांकerface(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t smc_driver_अगर_version;

	smum_send_msg_to_smc(hwmgr,
			PPSMC_MSG_GetDriverIfVersion,
			&smc_driver_अगर_version);

	अगर ((smc_driver_अगर_version != SMU10_DRIVER_IF_VERSION) &&
	    (smc_driver_अगर_version != SMU10_DRIVER_IF_VERSION + 1)) अणु
		pr_err("Attempt to read SMC IF Version Number Failed!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_smu_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu10_smumgr *priv =
			(काष्ठा smu10_smumgr *)(hwmgr->smu_backend);

	अगर (priv) अणु
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[SMU10_WMTABLE].handle,
					&priv->smu_tables.entry[SMU10_WMTABLE].mc_addr,
					&priv->smu_tables.entry[SMU10_WMTABLE].table);
		amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[SMU10_CLOCKTABLE].handle,
					&priv->smu_tables.entry[SMU10_CLOCKTABLE].mc_addr,
					&priv->smu_tables.entry[SMU10_CLOCKTABLE].table);
		kमुक्त(hwmgr->smu_backend);
		hwmgr->smu_backend = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_start_smu(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetSmuVersion, &hwmgr->smu_version);
	adev->pm.fw_version = hwmgr->smu_version >> 8;

	अगर (!(adev->apu_flags & AMD_APU_IS_RAVEN2) &&
	    (adev->apu_flags & AMD_APU_IS_RAVEN) &&
	    adev->pm.fw_version < 0x1e45)
		adev->pm.pp_feature &= ~PP_GFXOFF_MASK;

	अगर (smu10_verअगरy_smc_पूर्णांकerface(hwmgr))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक smu10_smu_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu10_smumgr *priv;
	पूर्णांक r;

	priv = kzalloc(माप(काष्ठा smu10_smumgr), GFP_KERNEL);

	अगर (!priv)
		वापस -ENOMEM;

	hwmgr->smu_backend = priv;

	/* allocate space क्रम watermarks table */
	r = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
			माप(Watermarks_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[SMU10_WMTABLE].handle,
			&priv->smu_tables.entry[SMU10_WMTABLE].mc_addr,
			&priv->smu_tables.entry[SMU10_WMTABLE].table);

	अगर (r)
		जाओ err0;

	priv->smu_tables.entry[SMU10_WMTABLE].version = 0x01;
	priv->smu_tables.entry[SMU10_WMTABLE].size = माप(Watermarks_t);
	priv->smu_tables.entry[SMU10_WMTABLE].table_id = TABLE_WATERMARKS;

	/* allocate space क्रम watermarks table */
	r = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
			माप(DpmClocks_t),
			PAGE_SIZE,
			AMDGPU_GEM_DOMAIN_VRAM,
			&priv->smu_tables.entry[SMU10_CLOCKTABLE].handle,
			&priv->smu_tables.entry[SMU10_CLOCKTABLE].mc_addr,
			&priv->smu_tables.entry[SMU10_CLOCKTABLE].table);

	अगर (r)
		जाओ err1;

	priv->smu_tables.entry[SMU10_CLOCKTABLE].version = 0x01;
	priv->smu_tables.entry[SMU10_CLOCKTABLE].size = माप(DpmClocks_t);
	priv->smu_tables.entry[SMU10_CLOCKTABLE].table_id = TABLE_DPMCLOCKS;

	वापस 0;

err1:
	amdgpu_bo_मुक्त_kernel(&priv->smu_tables.entry[SMU10_WMTABLE].handle,
				&priv->smu_tables.entry[SMU10_WMTABLE].mc_addr,
				&priv->smu_tables.entry[SMU10_WMTABLE].table);
err0:
	kमुक्त(priv);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक smu10_smc_table_manager(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t *table, uपूर्णांक16_t table_id, bool rw)
अणु
	पूर्णांक ret;

	अगर (rw)
		ret = smu10_copy_table_from_smc(hwmgr, table, table_id);
	अन्यथा
		ret = smu10_copy_table_to_smc(hwmgr, table, table_id);

	वापस ret;
पूर्ण


स्थिर काष्ठा pp_smumgr_func smu10_smu_funcs = अणु
	.name = "smu10_smu",
	.smu_init = &smu10_smu_init,
	.smu_fini = &smu10_smu_fini,
	.start_smu = &smu10_start_smu,
	.request_smu_load_specअगरic_fw = शून्य,
	.send_msg_to_smc = &smu10_send_msg_to_smc,
	.send_msg_to_smc_with_parameter = &smu10_send_msg_to_smc_with_parameter,
	.करोwnload_pptable_settings = शून्य,
	.upload_pptable_settings = शून्य,
	.get_argument = smu10_पढ़ो_arg_from_smc,
	.smc_table_manager = smu10_smc_table_manager,
पूर्ण;


