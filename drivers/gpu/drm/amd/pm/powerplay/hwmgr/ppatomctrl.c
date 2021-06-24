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
#समावेश "pp_debug.h"
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश "atom.h"
#समावेश "ppatomctrl.h"
#समावेश "atombios.h"
#समावेश "cgs_common.h"
#समावेश "ppevvmath.h"

#घोषणा MEM_ID_MASK           0xff000000
#घोषणा MEM_ID_SHIFT          24
#घोषणा CLOCK_RANGE_MASK      0x00ffffff
#घोषणा CLOCK_RANGE_SHIFT     0
#घोषणा LOW_NIBBLE_MASK       0xf
#घोषणा DATA_EQU_PREV         0
#घोषणा DATA_FROM_TABLE       4

जोड़ voltage_object_info अणु
	काष्ठा _ATOM_VOLTAGE_OBJECT_INFO v1;
	काष्ठा _ATOM_VOLTAGE_OBJECT_INFO_V2 v2;
	काष्ठा _ATOM_VOLTAGE_OBJECT_INFO_V3_1 v3;
पूर्ण;

अटल पूर्णांक atomctrl_retrieve_ac_timing(
		uपूर्णांक8_t index,
		ATOM_INIT_REG_BLOCK *reg_block,
		pp_atomctrl_mc_reg_table *table)
अणु
	uपूर्णांक32_t i, j;
	uपूर्णांक8_t पंचांगem_id;
	ATOM_MEMORY_SETTING_DATA_BLOCK *reg_data = (ATOM_MEMORY_SETTING_DATA_BLOCK *)
		((uपूर्णांक8_t *)reg_block + (2 * माप(uपूर्णांक16_t)) + le16_to_cpu(reg_block->usRegIndexTblSize));

	uपूर्णांक8_t num_ranges = 0;

	जबतक (*(uपूर्णांक32_t *)reg_data != END_OF_REG_DATA_BLOCK &&
			num_ranges < VBIOS_MAX_AC_TIMING_ENTRIES) अणु
		पंचांगem_id = (uपूर्णांक8_t)((*(uपूर्णांक32_t *)reg_data & MEM_ID_MASK) >> MEM_ID_SHIFT);

		अगर (index == पंचांगem_id) अणु
			table->mc_reg_table_entry[num_ranges].mclk_max =
				(uपूर्णांक32_t)((*(uपूर्णांक32_t *)reg_data & CLOCK_RANGE_MASK) >>
						CLOCK_RANGE_SHIFT);

			क्रम (i = 0, j = 1; i < table->last; i++) अणु
				अगर ((table->mc_reg_address[i].uc_pre_reg_data &
							LOW_NIBBLE_MASK) == DATA_FROM_TABLE) अणु
					table->mc_reg_table_entry[num_ranges].mc_data[i] =
						(uपूर्णांक32_t)*((uपूर्णांक32_t *)reg_data + j);
					j++;
				पूर्ण अन्यथा अगर ((table->mc_reg_address[i].uc_pre_reg_data &
							LOW_NIBBLE_MASK) == DATA_EQU_PREV) अणु
					table->mc_reg_table_entry[num_ranges].mc_data[i] =
						table->mc_reg_table_entry[num_ranges].mc_data[i-1];
				पूर्ण
			पूर्ण
			num_ranges++;
		पूर्ण

		reg_data = (ATOM_MEMORY_SETTING_DATA_BLOCK *)
			((uपूर्णांक8_t *)reg_data + le16_to_cpu(reg_block->usRegDataBlkSize)) ;
	पूर्ण

	PP_ASSERT_WITH_CODE((*(uपूर्णांक32_t *)reg_data == END_OF_REG_DATA_BLOCK),
			"Invalid VramInfo table.", वापस -1);
	table->num_entries = num_ranges;

	वापस 0;
पूर्ण

/**
 * atomctrl_set_mc_reg_address_table - Get memory घड़ी AC timing रेजिस्टरs index from VBIOS table
 * VBIOS set end of memory घड़ी AC timing रेजिस्टरs by ucPreRegDataLength bit6 = 1
 * @reg_block: the address ATOM_INIT_REG_BLOCK
 * @table: the address of MCRegTable
 * Return:   0
 */
अटल पूर्णांक atomctrl_set_mc_reg_address_table(
		ATOM_INIT_REG_BLOCK *reg_block,
		pp_atomctrl_mc_reg_table *table)
अणु
	uपूर्णांक8_t i = 0;
	uपूर्णांक8_t num_entries = (uपूर्णांक8_t)((le16_to_cpu(reg_block->usRegIndexTblSize))
			/ माप(ATOM_INIT_REG_INDEX_FORMAT));
	ATOM_INIT_REG_INDEX_FORMAT *क्रमmat = &reg_block->asRegIndexBuf[0];

	num_entries--;        /* subtract 1 data end mark entry */

	PP_ASSERT_WITH_CODE((num_entries <= VBIOS_MC_REGISTER_ARRAY_SIZE),
			"Invalid VramInfo table.", वापस -1);

	/* ucPreRegDataLength bit6 = 1 is the end of memory घड़ी AC timing रेजिस्टरs */
	जबतक ((!(क्रमmat->ucPreRegDataLength & ACCESS_PLACEHOLDER)) &&
			(i < num_entries)) अणु
		table->mc_reg_address[i].s1 =
			(uपूर्णांक16_t)(le16_to_cpu(क्रमmat->usRegIndex));
		table->mc_reg_address[i].uc_pre_reg_data =
			क्रमmat->ucPreRegDataLength;

		i++;
		क्रमmat = (ATOM_INIT_REG_INDEX_FORMAT *)
			((uपूर्णांक8_t *)क्रमmat + माप(ATOM_INIT_REG_INDEX_FORMAT));
	पूर्ण

	table->last = i;
	वापस 0;
पूर्ण

पूर्णांक atomctrl_initialize_mc_reg_table(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t module_index,
		pp_atomctrl_mc_reg_table *table)
अणु
	ATOM_VRAM_INFO_HEADER_V2_1 *vram_info;
	ATOM_INIT_REG_BLOCK *reg_block;
	पूर्णांक result = 0;
	u8 frev, crev;
	u16 size;

	vram_info = (ATOM_VRAM_INFO_HEADER_V2_1 *)
		smu_atom_get_data_table(hwmgr->adev,
				GetIndexIntoMasterTable(DATA, VRAM_Info), &size, &frev, &crev);

	अगर (module_index >= vram_info->ucNumOfVRAMModule) अणु
		pr_err("Invalid VramInfo table.");
		result = -1;
	पूर्ण अन्यथा अगर (vram_info->sHeader.ucTableFormatRevision < 2) अणु
		pr_err("Invalid VramInfo table.");
		result = -1;
	पूर्ण

	अगर (0 == result) अणु
		reg_block = (ATOM_INIT_REG_BLOCK *)
			((uपूर्णांक8_t *)vram_info + le16_to_cpu(vram_info->usMemClkPatchTblOffset));
		result = atomctrl_set_mc_reg_address_table(reg_block, table);
	पूर्ण

	अगर (0 == result) अणु
		result = atomctrl_retrieve_ac_timing(module_index,
					reg_block, table);
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक atomctrl_initialize_mc_reg_table_v2_2(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t module_index,
		pp_atomctrl_mc_reg_table *table)
अणु
	ATOM_VRAM_INFO_HEADER_V2_2 *vram_info;
	ATOM_INIT_REG_BLOCK *reg_block;
	पूर्णांक result = 0;
	u8 frev, crev;
	u16 size;

	vram_info = (ATOM_VRAM_INFO_HEADER_V2_2 *)
		smu_atom_get_data_table(hwmgr->adev,
				GetIndexIntoMasterTable(DATA, VRAM_Info), &size, &frev, &crev);

	अगर (module_index >= vram_info->ucNumOfVRAMModule) अणु
		pr_err("Invalid VramInfo table.");
		result = -1;
	पूर्ण अन्यथा अगर (vram_info->sHeader.ucTableFormatRevision < 2) अणु
		pr_err("Invalid VramInfo table.");
		result = -1;
	पूर्ण

	अगर (0 == result) अणु
		reg_block = (ATOM_INIT_REG_BLOCK *)
			((uपूर्णांक8_t *)vram_info + le16_to_cpu(vram_info->usMemClkPatchTblOffset));
		result = atomctrl_set_mc_reg_address_table(reg_block, table);
	पूर्ण

	अगर (0 == result) अणु
		result = atomctrl_retrieve_ac_timing(module_index,
					reg_block, table);
	पूर्ण

	वापस result;
पूर्ण

/*
 * Set DRAM timings based on engine घड़ी and memory घड़ी.
 */
पूर्णांक atomctrl_set_engine_dram_timings_rv770(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t engine_घड़ी,
		uपूर्णांक32_t memory_घड़ी)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	SET_ENGINE_CLOCK_PS_ALLOCATION engine_घड़ी_parameters;

	/* They are both in 10KHz Units. */
	engine_घड़ी_parameters.ulTargetEngineClock =
		cpu_to_le32((engine_घड़ी & SET_CLOCK_FREQ_MASK) |
			    ((COMPUTE_ENGINE_PLL_PARAM << 24)));

	/* in 10 khz units.*/
	engine_घड़ी_parameters.sReserved.ulClock =
		cpu_to_le32(memory_घड़ी & SET_CLOCK_FREQ_MASK);

	वापस amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, DynamicMemorySettings),
			(uपूर्णांक32_t *)&engine_घड़ी_parameters);
पूर्ण

/*
 * Private Function to get the PowerPlay Table Address.
 * WARNING: The tabled वापसed by this function is in
 * dynamically allocated memory.
 * The caller has to release अगर by calling kमुक्त.
 */
अटल ATOM_VOLTAGE_OBJECT_INFO *get_voltage_info_table(व्योम *device)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, VoltageObjectInfo);
	u8 frev, crev;
	u16 size;
	जोड़ voltage_object_info *voltage_info;

	voltage_info = (जोड़ voltage_object_info *)
		smu_atom_get_data_table(device, index,
			&size, &frev, &crev);

	अगर (voltage_info != शून्य)
		वापस (ATOM_VOLTAGE_OBJECT_INFO *) &(voltage_info->v3);
	अन्यथा
		वापस शून्य;
पूर्ण

अटल स्थिर ATOM_VOLTAGE_OBJECT_V3 *atomctrl_lookup_voltage_type_v3(
		स्थिर ATOM_VOLTAGE_OBJECT_INFO_V3_1 * voltage_object_info_table,
		uपूर्णांक8_t voltage_type, uपूर्णांक8_t voltage_mode)
अणु
	अचिन्हित पूर्णांक size = le16_to_cpu(voltage_object_info_table->sHeader.usStructureSize);
	अचिन्हित पूर्णांक offset = दुरत्व(ATOM_VOLTAGE_OBJECT_INFO_V3_1, asVoltageObj[0]);
	uपूर्णांक8_t *start = (uपूर्णांक8_t *)voltage_object_info_table;

	जबतक (offset < size) अणु
		स्थिर ATOM_VOLTAGE_OBJECT_V3 *voltage_object =
			(स्थिर ATOM_VOLTAGE_OBJECT_V3 *)(start + offset);

		अगर (voltage_type == voltage_object->asGpioVoltageObj.sHeader.ucVoltageType &&
			voltage_mode == voltage_object->asGpioVoltageObj.sHeader.ucVoltageMode)
			वापस voltage_object;

		offset += le16_to_cpu(voltage_object->asGpioVoltageObj.sHeader.usSize);
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * atomctrl_get_memory_pll_भागiders_si().
 *
 * @hwmgr:           input parameter: poपूर्णांकer to HwMgr
 * @घड़ी_value:     input parameter: memory घड़ी
 * @mpll_param:      output parameter: memory घड़ी parameters
 * @strobe_mode:     input parameter: 1 क्रम strobe mode,  0 क्रम perक्रमmance mode
 */
पूर्णांक atomctrl_get_memory_pll_भागiders_si(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी_value,
		pp_atomctrl_memory_घड़ी_param *mpll_param,
		bool strobe_mode)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	COMPUTE_MEMORY_CLOCK_PARAM_PARAMETERS_V2_1 mpll_parameters;
	पूर्णांक result;

	mpll_parameters.ulClock = cpu_to_le32(घड़ी_value);
	mpll_parameters.ucInputFlag = (uपूर्णांक8_t)((strobe_mode) ? 1 : 0);

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
		 GetIndexIntoMasterTable(COMMAND, ComputeMemoryClockParam),
		(uपूर्णांक32_t *)&mpll_parameters);

	अगर (0 == result) अणु
		mpll_param->mpll_fb_भागider.clk_frac =
			le16_to_cpu(mpll_parameters.ulFbDiv.usFbDivFrac);
		mpll_param->mpll_fb_भागider.cl_kf =
			le16_to_cpu(mpll_parameters.ulFbDiv.usFbDiv);
		mpll_param->mpll_post_भागider =
			(uपूर्णांक32_t)mpll_parameters.ucPostDiv;
		mpll_param->vco_mode =
			(uपूर्णांक32_t)(mpll_parameters.ucPllCntlFlag &
					MPLL_CNTL_FLAG_VCO_MODE_MASK);
		mpll_param->yclk_sel =
			(uपूर्णांक32_t)((mpll_parameters.ucPllCntlFlag &
						MPLL_CNTL_FLAG_BYPASS_DQ_PLL) ? 1 : 0);
		mpll_param->qdr =
			(uपूर्णांक32_t)((mpll_parameters.ucPllCntlFlag &
						MPLL_CNTL_FLAG_QDR_ENABLE) ? 1 : 0);
		mpll_param->half_rate =
			(uपूर्णांक32_t)((mpll_parameters.ucPllCntlFlag &
						MPLL_CNTL_FLAG_AD_HALF_RATE) ? 1 : 0);
		mpll_param->dll_speed =
			(uपूर्णांक32_t)(mpll_parameters.ucDllSpeed);
		mpll_param->bw_ctrl =
			(uपूर्णांक32_t)(mpll_parameters.ucBWCntl);
	पूर्ण

	वापस result;
पूर्ण

/**
 * atomctrl_get_memory_pll_भागiders_vi().
 *
 * @hwmgr:                 input parameter: poपूर्णांकer to HwMgr
 * @घड़ी_value:           input parameter: memory घड़ी
 * @mpll_param:            output parameter: memory घड़ी parameters
 */
पूर्णांक atomctrl_get_memory_pll_भागiders_vi(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी_value, pp_atomctrl_memory_घड़ी_param *mpll_param)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	COMPUTE_MEMORY_CLOCK_PARAM_PARAMETERS_V2_2 mpll_parameters;
	पूर्णांक result;

	mpll_parameters.ulClock.ulClock = cpu_to_le32(घड़ी_value);

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, ComputeMemoryClockParam),
			(uपूर्णांक32_t *)&mpll_parameters);

	अगर (!result)
		mpll_param->mpll_post_भागider =
				(uपूर्णांक32_t)mpll_parameters.ulClock.ucPostDiv;

	वापस result;
पूर्ण

पूर्णांक atomctrl_get_memory_pll_भागiders_ai(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक32_t घड़ी_value,
					pp_atomctrl_memory_घड़ी_param_ai *mpll_param)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	COMPUTE_MEMORY_CLOCK_PARAM_PARAMETERS_V2_3 mpll_parameters = अणुअणु0पूर्ण, 0, 0पूर्ण;
	पूर्णांक result;

	mpll_parameters.ulClock.ulClock = cpu_to_le32(घड़ी_value);

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, ComputeMemoryClockParam),
			(uपूर्णांक32_t *)&mpll_parameters);

	/* VEGAM's mpll takes someसमय to finish computing */
	udelay(10);

	अगर (!result) अणु
		mpll_param->ulMclk_fcw_पूर्णांक =
			le16_to_cpu(mpll_parameters.usMclk_fcw_पूर्णांक);
		mpll_param->ulMclk_fcw_frac =
			le16_to_cpu(mpll_parameters.usMclk_fcw_frac);
		mpll_param->ulClock =
			le32_to_cpu(mpll_parameters.ulClock.ulClock);
		mpll_param->ulPostDiv = mpll_parameters.ulClock.ucPostDiv;
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक atomctrl_get_engine_pll_भागiders_kong(काष्ठा pp_hwmgr *hwmgr,
					  uपूर्णांक32_t घड़ी_value,
					  pp_atomctrl_घड़ी_भागiders_kong *भागiders)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	COMPUTE_MEMORY_ENGINE_PLL_PARAMETERS_V4 pll_parameters;
	पूर्णांक result;

	pll_parameters.ulClock = cpu_to_le32(घड़ी_value);

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
		 GetIndexIntoMasterTable(COMMAND, ComputeMemoryEnginePLL),
		(uपूर्णांक32_t *)&pll_parameters);

	अगर (0 == result) अणु
		भागiders->pll_post_भागider = pll_parameters.ucPostDiv;
		भागiders->real_घड़ी = le32_to_cpu(pll_parameters.ulClock);
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक atomctrl_get_engine_pll_भागiders_vi(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी_value,
		pp_atomctrl_घड़ी_भागiders_vi *भागiders)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	COMPUTE_GPU_CLOCK_OUTPUT_PARAMETERS_V1_6 pll_patameters;
	पूर्णांक result;

	pll_patameters.ulClock.ulClock = cpu_to_le32(घड़ी_value);
	pll_patameters.ulClock.ucPostDiv = COMPUTE_GPUCLK_INPUT_FLAG_SCLK;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
		 GetIndexIntoMasterTable(COMMAND, ComputeMemoryEnginePLL),
		(uपूर्णांक32_t *)&pll_patameters);

	अगर (0 == result) अणु
		भागiders->pll_post_भागider =
			pll_patameters.ulClock.ucPostDiv;
		भागiders->real_घड़ी =
			le32_to_cpu(pll_patameters.ulClock.ulClock);

		भागiders->ul_fb_भाग.ul_fb_भाग_frac =
			le16_to_cpu(pll_patameters.ulFbDiv.usFbDivFrac);
		भागiders->ul_fb_भाग.ul_fb_भाग =
			le16_to_cpu(pll_patameters.ulFbDiv.usFbDiv);

		भागiders->uc_pll_ref_भाग =
			pll_patameters.ucPllRefDiv;
		भागiders->uc_pll_post_भाग =
			pll_patameters.ucPllPostDiv;
		भागiders->uc_pll_cntl_flag =
			pll_patameters.ucPllCntlFlag;
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक atomctrl_get_engine_pll_भागiders_ai(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी_value,
		pp_atomctrl_घड़ी_भागiders_ai *भागiders)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	COMPUTE_GPU_CLOCK_OUTPUT_PARAMETERS_V1_7 pll_patameters;
	पूर्णांक result;

	pll_patameters.ulClock.ulClock = cpu_to_le32(घड़ी_value);
	pll_patameters.ulClock.ucPostDiv = COMPUTE_GPUCLK_INPUT_FLAG_SCLK;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
		 GetIndexIntoMasterTable(COMMAND, ComputeMemoryEnginePLL),
		(uपूर्णांक32_t *)&pll_patameters);

	अगर (0 == result) अणु
		भागiders->usSclk_fcw_frac     = le16_to_cpu(pll_patameters.usSclk_fcw_frac);
		भागiders->usSclk_fcw_पूर्णांक      = le16_to_cpu(pll_patameters.usSclk_fcw_पूर्णांक);
		भागiders->ucSclkPostDiv       = pll_patameters.ucSclkPostDiv;
		भागiders->ucSclkVcoMode       = pll_patameters.ucSclkVcoMode;
		भागiders->ucSclkPllRange      = pll_patameters.ucSclkPllRange;
		भागiders->ucSscEnable         = pll_patameters.ucSscEnable;
		भागiders->usSsc_fcw1_frac     = le16_to_cpu(pll_patameters.usSsc_fcw1_frac);
		भागiders->usSsc_fcw1_पूर्णांक      = le16_to_cpu(pll_patameters.usSsc_fcw1_पूर्णांक);
		भागiders->usPcc_fcw_पूर्णांक       = le16_to_cpu(pll_patameters.usPcc_fcw_पूर्णांक);
		भागiders->usSsc_fcw_slew_frac = le16_to_cpu(pll_patameters.usSsc_fcw_slew_frac);
		भागiders->usPcc_fcw_slew_frac = le16_to_cpu(pll_patameters.usPcc_fcw_slew_frac);
	पूर्ण
	वापस result;
पूर्ण

पूर्णांक atomctrl_get_dfs_pll_भागiders_vi(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी_value,
		pp_atomctrl_घड़ी_भागiders_vi *भागiders)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	COMPUTE_GPU_CLOCK_OUTPUT_PARAMETERS_V1_6 pll_patameters;
	पूर्णांक result;

	pll_patameters.ulClock.ulClock = cpu_to_le32(घड़ी_value);
	pll_patameters.ulClock.ucPostDiv =
		COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
		 GetIndexIntoMasterTable(COMMAND, ComputeMemoryEnginePLL),
		(uपूर्णांक32_t *)&pll_patameters);

	अगर (0 == result) अणु
		भागiders->pll_post_भागider =
			pll_patameters.ulClock.ucPostDiv;
		भागiders->real_घड़ी =
			le32_to_cpu(pll_patameters.ulClock.ulClock);

		भागiders->ul_fb_भाग.ul_fb_भाग_frac =
			le16_to_cpu(pll_patameters.ulFbDiv.usFbDivFrac);
		भागiders->ul_fb_भाग.ul_fb_भाग =
			le16_to_cpu(pll_patameters.ulFbDiv.usFbDiv);

		भागiders->uc_pll_ref_भाग =
			pll_patameters.ucPllRefDiv;
		भागiders->uc_pll_post_भाग =
			pll_patameters.ucPllPostDiv;
		भागiders->uc_pll_cntl_flag =
			pll_patameters.ucPllCntlFlag;
	पूर्ण

	वापस result;
पूर्ण

/*
 * Get the reference घड़ी in 10KHz
 */
uपूर्णांक32_t atomctrl_get_reference_घड़ी(काष्ठा pp_hwmgr *hwmgr)
अणु
	ATOM_FIRMWARE_INFO *fw_info;
	u8 frev, crev;
	u16 size;
	uपूर्णांक32_t घड़ी;

	fw_info = (ATOM_FIRMWARE_INFO *)
		smu_atom_get_data_table(hwmgr->adev,
			GetIndexIntoMasterTable(DATA, FirmwareInfo),
			&size, &frev, &crev);

	अगर (fw_info == शून्य)
		घड़ी = 2700;
	अन्यथा
		घड़ी = (uपूर्णांक32_t)(le16_to_cpu(fw_info->usReferenceClock));

	वापस घड़ी;
पूर्ण

/*
 * Returns true अगर the given voltage type is controlled by GPIO pins.
 * voltage_type is one of SET_VOLTAGE_TYPE_ASIC_VDDC,
 * SET_VOLTAGE_TYPE_ASIC_MVDDC, SET_VOLTAGE_TYPE_ASIC_MVDDQ.
 * voltage_mode is one of ATOM_SET_VOLTAGE, ATOM_SET_VOLTAGE_PHASE
 */
bool atomctrl_is_voltage_controlled_by_gpio_v3(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t voltage_type,
		uपूर्णांक8_t voltage_mode)
अणु
	ATOM_VOLTAGE_OBJECT_INFO_V3_1 *voltage_info =
		(ATOM_VOLTAGE_OBJECT_INFO_V3_1 *)get_voltage_info_table(hwmgr->adev);
	bool ret;

	PP_ASSERT_WITH_CODE((शून्य != voltage_info),
			"Could not find Voltage Table in BIOS.", वापस false;);

	ret = (शून्य != atomctrl_lookup_voltage_type_v3
			(voltage_info, voltage_type, voltage_mode)) ? true : false;

	वापस ret;
पूर्ण

पूर्णांक atomctrl_get_voltage_table_v3(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t voltage_type,
		uपूर्णांक8_t voltage_mode,
		pp_atomctrl_voltage_table *voltage_table)
अणु
	ATOM_VOLTAGE_OBJECT_INFO_V3_1 *voltage_info =
		(ATOM_VOLTAGE_OBJECT_INFO_V3_1 *)get_voltage_info_table(hwmgr->adev);
	स्थिर ATOM_VOLTAGE_OBJECT_V3 *voltage_object;
	अचिन्हित पूर्णांक i;

	PP_ASSERT_WITH_CODE((शून्य != voltage_info),
			"Could not find Voltage Table in BIOS.", वापस -1;);

	voltage_object = atomctrl_lookup_voltage_type_v3
		(voltage_info, voltage_type, voltage_mode);

	अगर (voltage_object == शून्य)
		वापस -1;

	PP_ASSERT_WITH_CODE(
			(voltage_object->asGpioVoltageObj.ucGpioEntryNum <=
			PP_ATOMCTRL_MAX_VOLTAGE_ENTRIES),
			"Too many voltage entries!",
			वापस -1;
			);

	क्रम (i = 0; i < voltage_object->asGpioVoltageObj.ucGpioEntryNum; i++) अणु
		voltage_table->entries[i].value =
			le16_to_cpu(voltage_object->asGpioVoltageObj.asVolGpioLut[i].usVoltageValue);
		voltage_table->entries[i].smio_low =
			le32_to_cpu(voltage_object->asGpioVoltageObj.asVolGpioLut[i].ulVoltageId);
	पूर्ण

	voltage_table->mask_low    =
		le32_to_cpu(voltage_object->asGpioVoltageObj.ulGpioMaskVal);
	voltage_table->count      =
		voltage_object->asGpioVoltageObj.ucGpioEntryNum;
	voltage_table->phase_delay =
		voltage_object->asGpioVoltageObj.ucPhaseDelay;

	वापस 0;
पूर्ण

अटल bool atomctrl_lookup_gpio_pin(
		ATOM_GPIO_PIN_LUT * gpio_lookup_table,
		स्थिर uपूर्णांक32_t pinId,
		pp_atomctrl_gpio_pin_assignment *gpio_pin_assignment)
अणु
	अचिन्हित पूर्णांक size = le16_to_cpu(gpio_lookup_table->sHeader.usStructureSize);
	अचिन्हित पूर्णांक offset = दुरत्व(ATOM_GPIO_PIN_LUT, asGPIO_Pin[0]);
	uपूर्णांक8_t *start = (uपूर्णांक8_t *)gpio_lookup_table;

	जबतक (offset < size) अणु
		स्थिर ATOM_GPIO_PIN_ASSIGNMENT *pin_assignment =
			(स्थिर ATOM_GPIO_PIN_ASSIGNMENT *)(start + offset);

		अगर (pinId == pin_assignment->ucGPIO_ID) अणु
			gpio_pin_assignment->uc_gpio_pin_bit_shअगरt =
				pin_assignment->ucGpioPinBitShअगरt;
			gpio_pin_assignment->us_gpio_pin_aindex =
				le16_to_cpu(pin_assignment->usGpioPin_AIndex);
			वापस true;
		पूर्ण

		offset += दुरत्व(ATOM_GPIO_PIN_ASSIGNMENT, ucGPIO_ID) + 1;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Private Function to get the PowerPlay Table Address.
 * WARNING: The tabled वापसed by this function is in
 * dynamically allocated memory.
 * The caller has to release अगर by calling kमुक्त.
 */
अटल ATOM_GPIO_PIN_LUT *get_gpio_lookup_table(व्योम *device)
अणु
	u8 frev, crev;
	u16 size;
	व्योम *table_address;

	table_address = (ATOM_GPIO_PIN_LUT *)
		smu_atom_get_data_table(device,
				GetIndexIntoMasterTable(DATA, GPIO_Pin_LUT),
				&size, &frev, &crev);

	PP_ASSERT_WITH_CODE((शून्य != table_address),
			"Error retrieving BIOS Table Address!", वापस शून्य;);

	वापस (ATOM_GPIO_PIN_LUT *)table_address;
पूर्ण

/*
 * Returns 1 अगर the given pin id find in lookup table.
 */
bool atomctrl_get_pp_assign_pin(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर uपूर्णांक32_t pinId,
		pp_atomctrl_gpio_pin_assignment *gpio_pin_assignment)
अणु
	bool bRet = false;
	ATOM_GPIO_PIN_LUT *gpio_lookup_table =
		get_gpio_lookup_table(hwmgr->adev);

	PP_ASSERT_WITH_CODE((शून्य != gpio_lookup_table),
			"Could not find GPIO lookup Table in BIOS.", वापस false);

	bRet = atomctrl_lookup_gpio_pin(gpio_lookup_table, pinId,
		gpio_pin_assignment);

	वापस bRet;
पूर्ण

पूर्णांक atomctrl_calculate_voltage_evv_on_sclk(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t voltage_type,
		uपूर्णांक32_t sclk,
		uपूर्णांक16_t भव_voltage_Id,
		uपूर्णांक16_t *voltage,
		uपूर्णांक16_t dpm_level,
		bool debug)
अणु
	ATOM_ASIC_PROFILING_INFO_V3_4 *getASICProfilingInfo;
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	EFUSE_LINEAR_FUNC_PARAM sRO_fuse;
	EFUSE_LINEAR_FUNC_PARAM sCACm_fuse;
	EFUSE_LINEAR_FUNC_PARAM sCACb_fuse;
	EFUSE_LOGISTIC_FUNC_PARAM sKt_Beta_fuse;
	EFUSE_LOGISTIC_FUNC_PARAM sKv_m_fuse;
	EFUSE_LOGISTIC_FUNC_PARAM sKv_b_fuse;
	EFUSE_INPUT_PARAMETER sInput_FuseValues;
	READ_EFUSE_VALUE_PARAMETER sOutput_FuseValues;

	uपूर्णांक32_t ul_RO_fused, ul_CACb_fused, ul_CACm_fused, ul_Kt_Beta_fused, ul_Kv_m_fused, ul_Kv_b_fused;
	fInt fSM_A0, fSM_A1, fSM_A2, fSM_A3, fSM_A4, fSM_A5, fSM_A6, fSM_A7;
	fInt fMargin_RO_a, fMargin_RO_b, fMargin_RO_c, fMargin_fixed, fMargin_FMAX_mean, fMargin_Plat_mean, fMargin_FMAX_sigma, fMargin_Plat_sigma, fMargin_DC_sigma;
	fInt fLkg_FT, repeat;
	fInt fMicro_FMAX, fMicro_CR, fSigma_FMAX, fSigma_CR, fSigma_DC, fDC_SCLK, fSquared_Sigma_DC, fSquared_Sigma_CR, fSquared_Sigma_FMAX;
	fInt fRLL_LoadLine, fDerateTDP, fVDDC_base, fA_Term, fC_Term, fB_Term, fRO_DC_margin;
	fInt fRO_fused, fCACm_fused, fCACb_fused, fKv_m_fused, fKv_b_fused, fKt_Beta_fused, fFT_Lkg_V0NORM;
	fInt fSclk_margin, fSclk, fEVV_V;
	fInt fV_min, fV_max, fT_prod, fLKG_Factor, fT_FT, fV_FT, fV_x, fTDP_Power, fTDP_Power_right, fTDP_Power_left, fTDP_Current, fV_NL;
	uपूर्णांक32_t ul_FT_Lkg_V0NORM;
	fInt fLn_MaxDivMin, fMin, fAverage, fRange;
	fInt fRoots[2];
	fInt fStepSize = GetScaledFraction(625, 100000);

	पूर्णांक result;

	getASICProfilingInfo = (ATOM_ASIC_PROFILING_INFO_V3_4 *)
			smu_atom_get_data_table(hwmgr->adev,
					GetIndexIntoMasterTable(DATA, ASIC_ProfilingInfo),
					शून्य, शून्य, शून्य);

	अगर (!getASICProfilingInfo)
		वापस -1;

	अगर (getASICProfilingInfo->asHeader.ucTableFormatRevision < 3 ||
	    (getASICProfilingInfo->asHeader.ucTableFormatRevision == 3 &&
	     getASICProfilingInfo->asHeader.ucTableContentRevision < 4))
		वापस -1;

	/*-----------------------------------------------------------
	 *GETTING MULTI-STEP PARAMETERS RELATED TO CURRENT DPM LEVEL
	 *-----------------------------------------------------------
	 */
	fRLL_LoadLine = Divide(getASICProfilingInfo->ulLoadLineSlop, 1000);

	चयन (dpm_level) अणु
	हाल 1:
		fDerateTDP = GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulTdpDerateDPM1), 1000);
		अवरोध;
	हाल 2:
		fDerateTDP = GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulTdpDerateDPM2), 1000);
		अवरोध;
	हाल 3:
		fDerateTDP = GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulTdpDerateDPM3), 1000);
		अवरोध;
	हाल 4:
		fDerateTDP = GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulTdpDerateDPM4), 1000);
		अवरोध;
	हाल 5:
		fDerateTDP = GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulTdpDerateDPM5), 1000);
		अवरोध;
	हाल 6:
		fDerateTDP = GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulTdpDerateDPM6), 1000);
		अवरोध;
	हाल 7:
		fDerateTDP = GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulTdpDerateDPM7), 1000);
		अवरोध;
	शेष:
		pr_err("DPM Level not supported\n");
		fDerateTDP = GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulTdpDerateDPM0), 1000);
	पूर्ण

	/*-------------------------
	 * DECODING FUSE VALUES
	 * ------------------------
	 */
	/*Decode RO_Fused*/
	sRO_fuse = getASICProfilingInfo->sRoFuse;

	sInput_FuseValues.usEfuseIndex = sRO_fuse.usEfuseIndex;
	sInput_FuseValues.ucBitShअगरt = sRO_fuse.ucEfuseBitLSB;
	sInput_FuseValues.ucBitLength = sRO_fuse.ucEfuseLength;

	sOutput_FuseValues.sEfuse = sInput_FuseValues;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, ReadEfuseValue),
			(uपूर्णांक32_t *)&sOutput_FuseValues);

	अगर (result)
		वापस result;

	/* Finally, the actual fuse value */
	ul_RO_fused = le32_to_cpu(sOutput_FuseValues.ulEfuseValue);
	fMin = GetScaledFraction(le32_to_cpu(sRO_fuse.ulEfuseMin), 1);
	fRange = GetScaledFraction(le32_to_cpu(sRO_fuse.ulEfuseEncodeRange), 1);
	fRO_fused = fDecodeLinearFuse(ul_RO_fused, fMin, fRange, sRO_fuse.ucEfuseLength);

	sCACm_fuse = getASICProfilingInfo->sCACm;

	sInput_FuseValues.usEfuseIndex = sCACm_fuse.usEfuseIndex;
	sInput_FuseValues.ucBitShअगरt = sCACm_fuse.ucEfuseBitLSB;
	sInput_FuseValues.ucBitLength = sCACm_fuse.ucEfuseLength;

	sOutput_FuseValues.sEfuse = sInput_FuseValues;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, ReadEfuseValue),
			(uपूर्णांक32_t *)&sOutput_FuseValues);

	अगर (result)
		वापस result;

	ul_CACm_fused = le32_to_cpu(sOutput_FuseValues.ulEfuseValue);
	fMin = GetScaledFraction(le32_to_cpu(sCACm_fuse.ulEfuseMin), 1000);
	fRange = GetScaledFraction(le32_to_cpu(sCACm_fuse.ulEfuseEncodeRange), 1000);

	fCACm_fused = fDecodeLinearFuse(ul_CACm_fused, fMin, fRange, sCACm_fuse.ucEfuseLength);

	sCACb_fuse = getASICProfilingInfo->sCACb;

	sInput_FuseValues.usEfuseIndex = sCACb_fuse.usEfuseIndex;
	sInput_FuseValues.ucBitShअगरt = sCACb_fuse.ucEfuseBitLSB;
	sInput_FuseValues.ucBitLength = sCACb_fuse.ucEfuseLength;
	sOutput_FuseValues.sEfuse = sInput_FuseValues;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, ReadEfuseValue),
			(uपूर्णांक32_t *)&sOutput_FuseValues);

	अगर (result)
		वापस result;

	ul_CACb_fused = le32_to_cpu(sOutput_FuseValues.ulEfuseValue);
	fMin = GetScaledFraction(le32_to_cpu(sCACb_fuse.ulEfuseMin), 1000);
	fRange = GetScaledFraction(le32_to_cpu(sCACb_fuse.ulEfuseEncodeRange), 1000);

	fCACb_fused = fDecodeLinearFuse(ul_CACb_fused, fMin, fRange, sCACb_fuse.ucEfuseLength);

	sKt_Beta_fuse = getASICProfilingInfo->sKt_b;

	sInput_FuseValues.usEfuseIndex = sKt_Beta_fuse.usEfuseIndex;
	sInput_FuseValues.ucBitShअगरt = sKt_Beta_fuse.ucEfuseBitLSB;
	sInput_FuseValues.ucBitLength = sKt_Beta_fuse.ucEfuseLength;

	sOutput_FuseValues.sEfuse = sInput_FuseValues;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, ReadEfuseValue),
			(uपूर्णांक32_t *)&sOutput_FuseValues);

	अगर (result)
		वापस result;

	ul_Kt_Beta_fused = le32_to_cpu(sOutput_FuseValues.ulEfuseValue);
	fAverage = GetScaledFraction(le32_to_cpu(sKt_Beta_fuse.ulEfuseEncodeAverage), 1000);
	fRange = GetScaledFraction(le32_to_cpu(sKt_Beta_fuse.ulEfuseEncodeRange), 1000);

	fKt_Beta_fused = fDecodeLogisticFuse(ul_Kt_Beta_fused,
			fAverage, fRange, sKt_Beta_fuse.ucEfuseLength);

	sKv_m_fuse = getASICProfilingInfo->sKv_m;

	sInput_FuseValues.usEfuseIndex = sKv_m_fuse.usEfuseIndex;
	sInput_FuseValues.ucBitShअगरt = sKv_m_fuse.ucEfuseBitLSB;
	sInput_FuseValues.ucBitLength = sKv_m_fuse.ucEfuseLength;

	sOutput_FuseValues.sEfuse = sInput_FuseValues;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, ReadEfuseValue),
			(uपूर्णांक32_t *)&sOutput_FuseValues);
	अगर (result)
		वापस result;

	ul_Kv_m_fused = le32_to_cpu(sOutput_FuseValues.ulEfuseValue);
	fAverage = GetScaledFraction(le32_to_cpu(sKv_m_fuse.ulEfuseEncodeAverage), 1000);
	fRange = GetScaledFraction((le32_to_cpu(sKv_m_fuse.ulEfuseEncodeRange) & 0x7fffffff), 1000);
	fRange = fMultiply(fRange, ConvertToFraction(-1));

	fKv_m_fused = fDecodeLogisticFuse(ul_Kv_m_fused,
			fAverage, fRange, sKv_m_fuse.ucEfuseLength);

	sKv_b_fuse = getASICProfilingInfo->sKv_b;

	sInput_FuseValues.usEfuseIndex = sKv_b_fuse.usEfuseIndex;
	sInput_FuseValues.ucBitShअगरt = sKv_b_fuse.ucEfuseBitLSB;
	sInput_FuseValues.ucBitLength = sKv_b_fuse.ucEfuseLength;
	sOutput_FuseValues.sEfuse = sInput_FuseValues;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, ReadEfuseValue),
			(uपूर्णांक32_t *)&sOutput_FuseValues);

	अगर (result)
		वापस result;

	ul_Kv_b_fused = le32_to_cpu(sOutput_FuseValues.ulEfuseValue);
	fAverage = GetScaledFraction(le32_to_cpu(sKv_b_fuse.ulEfuseEncodeAverage), 1000);
	fRange = GetScaledFraction(le32_to_cpu(sKv_b_fuse.ulEfuseEncodeRange), 1000);

	fKv_b_fused = fDecodeLogisticFuse(ul_Kv_b_fused,
			fAverage, fRange, sKv_b_fuse.ucEfuseLength);

	/* Decoding the Leakage - No special काष्ठा container */
	/*
	 * usLkgEuseIndex=56
	 * ucLkgEfuseBitLSB=6
	 * ucLkgEfuseLength=10
	 * ulLkgEncodeLn_MaxDivMin=69077
	 * ulLkgEncodeMax=1000000
	 * ulLkgEncodeMin=1000
	 * ulEfuseLogisticAlpha=13
	 */

	sInput_FuseValues.usEfuseIndex = getASICProfilingInfo->usLkgEuseIndex;
	sInput_FuseValues.ucBitShअगरt = getASICProfilingInfo->ucLkgEfuseBitLSB;
	sInput_FuseValues.ucBitLength = getASICProfilingInfo->ucLkgEfuseLength;

	sOutput_FuseValues.sEfuse = sInput_FuseValues;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, ReadEfuseValue),
			(uपूर्णांक32_t *)&sOutput_FuseValues);

	अगर (result)
		वापस result;

	ul_FT_Lkg_V0NORM = le32_to_cpu(sOutput_FuseValues.ulEfuseValue);
	fLn_MaxDivMin = GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulLkgEncodeLn_MaxDivMin), 10000);
	fMin = GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulLkgEncodeMin), 10000);

	fFT_Lkg_V0NORM = fDecodeLeakageID(ul_FT_Lkg_V0NORM,
			fLn_MaxDivMin, fMin, getASICProfilingInfo->ucLkgEfuseLength);
	fLkg_FT = fFT_Lkg_V0NORM;

	/*-------------------------------------------
	 * PART 2 - Grabbing all required values
	 *-------------------------------------------
	 */
	fSM_A0 = fMultiply(GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulSM_A0), 1000000),
			ConvertToFraction(uPow(-1, getASICProfilingInfo->ucSM_A0_sign)));
	fSM_A1 = fMultiply(GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulSM_A1), 1000000),
			ConvertToFraction(uPow(-1, getASICProfilingInfo->ucSM_A1_sign)));
	fSM_A2 = fMultiply(GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulSM_A2), 100000),
			ConvertToFraction(uPow(-1, getASICProfilingInfo->ucSM_A2_sign)));
	fSM_A3 = fMultiply(GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulSM_A3), 1000000),
			ConvertToFraction(uPow(-1, getASICProfilingInfo->ucSM_A3_sign)));
	fSM_A4 = fMultiply(GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulSM_A4), 1000000),
			ConvertToFraction(uPow(-1, getASICProfilingInfo->ucSM_A4_sign)));
	fSM_A5 = fMultiply(GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulSM_A5), 1000),
			ConvertToFraction(uPow(-1, getASICProfilingInfo->ucSM_A5_sign)));
	fSM_A6 = fMultiply(GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulSM_A6), 1000),
			ConvertToFraction(uPow(-1, getASICProfilingInfo->ucSM_A6_sign)));
	fSM_A7 = fMultiply(GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulSM_A7), 1000),
			ConvertToFraction(uPow(-1, getASICProfilingInfo->ucSM_A7_sign)));

	fMargin_RO_a = ConvertToFraction(le32_to_cpu(getASICProfilingInfo->ulMargin_RO_a));
	fMargin_RO_b = ConvertToFraction(le32_to_cpu(getASICProfilingInfo->ulMargin_RO_b));
	fMargin_RO_c = ConvertToFraction(le32_to_cpu(getASICProfilingInfo->ulMargin_RO_c));

	fMargin_fixed = ConvertToFraction(le32_to_cpu(getASICProfilingInfo->ulMargin_fixed));

	fMargin_FMAX_mean = GetScaledFraction(
		le32_to_cpu(getASICProfilingInfo->ulMargin_Fmax_mean), 10000);
	fMargin_Plat_mean = GetScaledFraction(
		le32_to_cpu(getASICProfilingInfo->ulMargin_plat_mean), 10000);
	fMargin_FMAX_sigma = GetScaledFraction(
		le32_to_cpu(getASICProfilingInfo->ulMargin_Fmax_sigma), 10000);
	fMargin_Plat_sigma = GetScaledFraction(
		le32_to_cpu(getASICProfilingInfo->ulMargin_plat_sigma), 10000);

	fMargin_DC_sigma = GetScaledFraction(
		le32_to_cpu(getASICProfilingInfo->ulMargin_DC_sigma), 100);
	fMargin_DC_sigma = fDivide(fMargin_DC_sigma, ConvertToFraction(1000));

	fCACm_fused = fDivide(fCACm_fused, ConvertToFraction(100));
	fCACb_fused = fDivide(fCACb_fused, ConvertToFraction(100));
	fKt_Beta_fused = fDivide(fKt_Beta_fused, ConvertToFraction(100));
	fKv_m_fused =  fNegate(fDivide(fKv_m_fused, ConvertToFraction(100)));
	fKv_b_fused = fDivide(fKv_b_fused, ConvertToFraction(10));

	fSclk = GetScaledFraction(sclk, 100);

	fV_max = fDivide(GetScaledFraction(
				 le32_to_cpu(getASICProfilingInfo->ulMaxVddc), 1000), ConvertToFraction(4));
	fT_prod = GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulBoardCoreTemp), 10);
	fLKG_Factor = GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulEvvLkgFactor), 100);
	fT_FT = GetScaledFraction(le32_to_cpu(getASICProfilingInfo->ulLeakageTemp), 10);
	fV_FT = fDivide(GetScaledFraction(
				le32_to_cpu(getASICProfilingInfo->ulLeakageVoltage), 1000), ConvertToFraction(4));
	fV_min = fDivide(GetScaledFraction(
				 le32_to_cpu(getASICProfilingInfo->ulMinVddc), 1000), ConvertToFraction(4));

	/*-----------------------
	 * PART 3
	 *-----------------------
	 */

	fA_Term = fAdd(fMargin_RO_a, fAdd(fMultiply(fSM_A4, fSclk), fSM_A5));
	fB_Term = fAdd(fAdd(fMultiply(fSM_A2, fSclk), fSM_A6), fMargin_RO_b);
	fC_Term = fAdd(fMargin_RO_c,
			fAdd(fMultiply(fSM_A0, fLkg_FT),
			fAdd(fMultiply(fSM_A1, fMultiply(fLkg_FT, fSclk)),
			fAdd(fMultiply(fSM_A3, fSclk),
			fSubtract(fSM_A7, fRO_fused)))));

	fVDDC_base = fSubtract(fRO_fused,
			fSubtract(fMargin_RO_c,
					fSubtract(fSM_A3, fMultiply(fSM_A1, fSclk))));
	fVDDC_base = fDivide(fVDDC_base, fAdd(fMultiply(fSM_A0, fSclk), fSM_A2));

	repeat = fSubtract(fVDDC_base,
			fDivide(fMargin_DC_sigma, ConvertToFraction(1000)));

	fRO_DC_margin = fAdd(fMultiply(fMargin_RO_a,
			fGetSquare(repeat)),
			fAdd(fMultiply(fMargin_RO_b, repeat),
			fMargin_RO_c));

	fDC_SCLK = fSubtract(fRO_fused,
			fSubtract(fRO_DC_margin,
			fSubtract(fSM_A3,
			fMultiply(fSM_A2, repeat))));
	fDC_SCLK = fDivide(fDC_SCLK, fAdd(fMultiply(fSM_A0, repeat), fSM_A1));

	fSigma_DC = fSubtract(fSclk, fDC_SCLK);

	fMicro_FMAX = fMultiply(fSclk, fMargin_FMAX_mean);
	fMicro_CR = fMultiply(fSclk, fMargin_Plat_mean);
	fSigma_FMAX = fMultiply(fSclk, fMargin_FMAX_sigma);
	fSigma_CR = fMultiply(fSclk, fMargin_Plat_sigma);

	fSquared_Sigma_DC = fGetSquare(fSigma_DC);
	fSquared_Sigma_CR = fGetSquare(fSigma_CR);
	fSquared_Sigma_FMAX = fGetSquare(fSigma_FMAX);

	fSclk_margin = fAdd(fMicro_FMAX,
			fAdd(fMicro_CR,
			fAdd(fMargin_fixed,
			fSqrt(fAdd(fSquared_Sigma_FMAX,
			fAdd(fSquared_Sigma_DC, fSquared_Sigma_CR))))));
	/*
	 fA_Term = fSM_A4 * (fSclk + fSclk_margin) + fSM_A5;
	 fB_Term = fSM_A2 * (fSclk + fSclk_margin) + fSM_A6;
	 fC_Term = fRO_DC_margin + fSM_A0 * fLkg_FT + fSM_A1 * fLkg_FT * (fSclk + fSclk_margin) + fSM_A3 * (fSclk + fSclk_margin) + fSM_A7 - fRO_fused;
	 */

	fA_Term = fAdd(fMultiply(fSM_A4, fAdd(fSclk, fSclk_margin)), fSM_A5);
	fB_Term = fAdd(fMultiply(fSM_A2, fAdd(fSclk, fSclk_margin)), fSM_A6);
	fC_Term = fAdd(fRO_DC_margin,
			fAdd(fMultiply(fSM_A0, fLkg_FT),
			fAdd(fMultiply(fMultiply(fSM_A1, fLkg_FT),
			fAdd(fSclk, fSclk_margin)),
			fAdd(fMultiply(fSM_A3,
			fAdd(fSclk, fSclk_margin)),
			fSubtract(fSM_A7, fRO_fused)))));

	SolveQuadracticEqn(fA_Term, fB_Term, fC_Term, fRoots);

	अगर (GreaterThan(fRoots[0], fRoots[1]))
		fEVV_V = fRoots[1];
	अन्यथा
		fEVV_V = fRoots[0];

	अगर (GreaterThan(fV_min, fEVV_V))
		fEVV_V = fV_min;
	अन्यथा अगर (GreaterThan(fEVV_V, fV_max))
		fEVV_V = fSubtract(fV_max, fStepSize);

	fEVV_V = fRoundUpByStepSize(fEVV_V, fStepSize, 0);

	/*-----------------
	 * PART 4
	 *-----------------
	 */

	fV_x = fV_min;

	जबतक (GreaterThan(fAdd(fV_max, fStepSize), fV_x)) अणु
		fTDP_Power_left = fMultiply(fMultiply(fMultiply(fAdd(
				fMultiply(fCACm_fused, fV_x), fCACb_fused), fSclk),
				fGetSquare(fV_x)), fDerateTDP);

		fTDP_Power_right = fMultiply(fFT_Lkg_V0NORM, fMultiply(fLKG_Factor,
				fMultiply(fExponential(fMultiply(fAdd(fMultiply(fKv_m_fused,
				fT_prod), fKv_b_fused), fV_x)), fV_x)));
		fTDP_Power_right = fMultiply(fTDP_Power_right, fExponential(fMultiply(
				fKt_Beta_fused, fT_prod)));
		fTDP_Power_right = fDivide(fTDP_Power_right, fExponential(fMultiply(
				fAdd(fMultiply(fKv_m_fused, fT_prod), fKv_b_fused), fV_FT)));
		fTDP_Power_right = fDivide(fTDP_Power_right, fExponential(fMultiply(
				fKt_Beta_fused, fT_FT)));

		fTDP_Power = fAdd(fTDP_Power_left, fTDP_Power_right);

		fTDP_Current = fDivide(fTDP_Power, fV_x);

		fV_NL = fAdd(fV_x, fDivide(fMultiply(fTDP_Current, fRLL_LoadLine),
				ConvertToFraction(10)));

		fV_NL = fRoundUpByStepSize(fV_NL, fStepSize, 0);

		अगर (GreaterThan(fV_max, fV_NL) &&
			(GreaterThan(fV_NL, fEVV_V) ||
			Equal(fV_NL, fEVV_V))) अणु
			fV_NL = fMultiply(fV_NL, ConvertToFraction(1000));

			*voltage = (uपूर्णांक16_t)fV_NL.partial.real;
			अवरोध;
		पूर्ण अन्यथा
			fV_x = fAdd(fV_x, fStepSize);
	पूर्ण

	वापस result;
पूर्ण

/**
 * atomctrl_get_voltage_evv_on_sclk माला_लो voltage via call to ATOM COMMAND table.
 * @hwmgr:              input: poपूर्णांकer to hwManager
 * @voltage_type:       input: type of EVV voltage VDDC or VDDGFX
 * @sclk:               input: in 10Khz unit. DPM state SCLK frequency
 *		         which is define in PPTable SCLK/VDDC dependence
 *			 table associated with this भव_voltage_Id
 * @भव_voltage_Id: input: voltage id which match per voltage DPM state: 0xff01, 0xff02.. 0xff08
 * @voltage: 	        output: real voltage level in unit of mv
 */
पूर्णांक atomctrl_get_voltage_evv_on_sclk(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t voltage_type,
		uपूर्णांक32_t sclk, uपूर्णांक16_t भव_voltage_Id,
		uपूर्णांक16_t *voltage)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	GET_VOLTAGE_INFO_INPUT_PARAMETER_V1_2 get_voltage_info_param_space;
	पूर्णांक result;

	get_voltage_info_param_space.ucVoltageType   =
		voltage_type;
	get_voltage_info_param_space.ucVoltageMode   =
		ATOM_GET_VOLTAGE_EVV_VOLTAGE;
	get_voltage_info_param_space.usVoltageLevel  =
		cpu_to_le16(भव_voltage_Id);
	get_voltage_info_param_space.ulSCLKFreq      =
		cpu_to_le32(sclk);

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, GetVoltageInfo),
			(uपूर्णांक32_t *)&get_voltage_info_param_space);

	*voltage = result ? 0 :
			le16_to_cpu(((GET_EVV_VOLTAGE_INFO_OUTPUT_PARAMETER_V1_2 *)
				(&get_voltage_info_param_space))->usVoltageLevel);

	वापस result;
पूर्ण

/**
 * atomctrl_get_voltage_evv माला_लो voltage via call to ATOM COMMAND table.
 * @hwmgr:              input: poपूर्णांकer to hwManager
 * @भव_voltage_id: input: voltage id which match per voltage DPM state: 0xff01, 0xff02.. 0xff08
 * @voltage: 	       output: real voltage level in unit of mv
 */
पूर्णांक atomctrl_get_voltage_evv(काष्ठा pp_hwmgr *hwmgr,
			     uपूर्णांक16_t भव_voltage_id,
			     uपूर्णांक16_t *voltage)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	GET_VOLTAGE_INFO_INPUT_PARAMETER_V1_2 get_voltage_info_param_space;
	पूर्णांक result;
	पूर्णांक entry_id;

	/* search क्रम leakage voltage ID 0xff01 ~ 0xff08 and sckl */
	क्रम (entry_id = 0; entry_id < hwmgr->dyn_state.vddc_dependency_on_sclk->count; entry_id++) अणु
		अगर (hwmgr->dyn_state.vddc_dependency_on_sclk->entries[entry_id].v == भव_voltage_id) अणु
			/* found */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (entry_id >= hwmgr->dyn_state.vddc_dependency_on_sclk->count) अणु
	        pr_debug("Can't find requested voltage id in vddc_dependency_on_sclk table!\n");
	        वापस -EINVAL;
	पूर्ण

	get_voltage_info_param_space.ucVoltageType = VOLTAGE_TYPE_VDDC;
	get_voltage_info_param_space.ucVoltageMode = ATOM_GET_VOLTAGE_EVV_VOLTAGE;
	get_voltage_info_param_space.usVoltageLevel = भव_voltage_id;
	get_voltage_info_param_space.ulSCLKFreq =
		cpu_to_le32(hwmgr->dyn_state.vddc_dependency_on_sclk->entries[entry_id].clk);

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, GetVoltageInfo),
			(uपूर्णांक32_t *)&get_voltage_info_param_space);

	अगर (0 != result)
		वापस result;

	*voltage = le16_to_cpu(((GET_EVV_VOLTAGE_INFO_OUTPUT_PARAMETER_V1_2 *)
				(&get_voltage_info_param_space))->usVoltageLevel);

	वापस result;
पूर्ण

/*
 * Get the mpll reference घड़ी in 10KHz
 */
uपूर्णांक32_t atomctrl_get_mpll_reference_घड़ी(काष्ठा pp_hwmgr *hwmgr)
अणु
	ATOM_COMMON_TABLE_HEADER *fw_info;
	uपूर्णांक32_t घड़ी;
	u8 frev, crev;
	u16 size;

	fw_info = (ATOM_COMMON_TABLE_HEADER *)
		smu_atom_get_data_table(hwmgr->adev,
				GetIndexIntoMasterTable(DATA, FirmwareInfo),
				&size, &frev, &crev);

	अगर (fw_info == शून्य)
		घड़ी = 2700;
	अन्यथा अणु
		अगर ((fw_info->ucTableFormatRevision == 2) &&
			(le16_to_cpu(fw_info->usStructureSize) >= माप(ATOM_FIRMWARE_INFO_V2_1))) अणु
			ATOM_FIRMWARE_INFO_V2_1 *fwInfo_2_1 =
				(ATOM_FIRMWARE_INFO_V2_1 *)fw_info;
			घड़ी = (uपूर्णांक32_t)(le16_to_cpu(fwInfo_2_1->usMemoryReferenceClock));
		पूर्ण अन्यथा अणु
			ATOM_FIRMWARE_INFO *fwInfo_0_0 =
				(ATOM_FIRMWARE_INFO *)fw_info;
			घड़ी = (uपूर्णांक32_t)(le16_to_cpu(fwInfo_0_0->usReferenceClock));
		पूर्ण
	पूर्ण

	वापस घड़ी;
पूर्ण

/*
 * Get the asic पूर्णांकernal spपढ़ो spectrum table
 */
अटल ATOM_ASIC_INTERNAL_SS_INFO *asic_पूर्णांकernal_ss_get_ss_table(व्योम *device)
अणु
	ATOM_ASIC_INTERNAL_SS_INFO *table = शून्य;
	u8 frev, crev;
	u16 size;

	table = (ATOM_ASIC_INTERNAL_SS_INFO *)
		smu_atom_get_data_table(device,
			GetIndexIntoMasterTable(DATA, ASIC_InternalSS_Info),
			&size, &frev, &crev);

	वापस table;
पूर्ण

bool atomctrl_is_asic_पूर्णांकernal_ss_supported(काष्ठा pp_hwmgr *hwmgr)
अणु
	ATOM_ASIC_INTERNAL_SS_INFO *table =
		asic_पूर्णांकernal_ss_get_ss_table(hwmgr->adev);

	अगर (table)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/*
 * Get the asic पूर्णांकernal spपढ़ो spectrum assignment
 */
अटल पूर्णांक asic_पूर्णांकernal_ss_get_ss_asignment(काष्ठा pp_hwmgr *hwmgr,
		स्थिर uपूर्णांक8_t घड़ीSource,
		स्थिर uपूर्णांक32_t घड़ीSpeed,
		pp_atomctrl_पूर्णांकernal_ss_info *ssEntry)
अणु
	ATOM_ASIC_INTERNAL_SS_INFO *table;
	ATOM_ASIC_SS_ASSIGNMENT *ssInfo;
	पूर्णांक entry_found = 0;

	स_रखो(ssEntry, 0x00, माप(pp_atomctrl_पूर्णांकernal_ss_info));

	table = asic_पूर्णांकernal_ss_get_ss_table(hwmgr->adev);

	अगर (शून्य == table)
		वापस -1;

	ssInfo = &table->asSpपढ़ोSpectrum[0];

	जबतक (((uपूर्णांक8_t *)ssInfo - (uपूर्णांक8_t *)table) <
		le16_to_cpu(table->sHeader.usStructureSize)) अणु
		अगर ((घड़ीSource == ssInfo->ucClockIndication) &&
			((uपूर्णांक32_t)घड़ीSpeed <= le32_to_cpu(ssInfo->ulTargetClockRange))) अणु
			entry_found = 1;
			अवरोध;
		पूर्ण

		ssInfo = (ATOM_ASIC_SS_ASSIGNMENT *)((uपूर्णांक8_t *)ssInfo +
				माप(ATOM_ASIC_SS_ASSIGNMENT));
	पूर्ण

	अगर (entry_found) अणु
		ssEntry->speed_spectrum_percentage =
			le16_to_cpu(ssInfo->usSpपढ़ोSpectrumPercentage);
		ssEntry->speed_spectrum_rate = le16_to_cpu(ssInfo->usSpपढ़ोRateInKhz);

		अगर (((GET_DATA_TABLE_MAJOR_REVISION(table) == 2) &&
			(GET_DATA_TABLE_MINOR_REVISION(table) >= 2)) ||
			(GET_DATA_TABLE_MAJOR_REVISION(table) == 3)) अणु
			ssEntry->speed_spectrum_rate /= 100;
		पूर्ण

		चयन (ssInfo->ucSpपढ़ोSpectrumMode) अणु
		हाल 0:
			ssEntry->speed_spectrum_mode =
				pp_atomctrl_spपढ़ो_spectrum_mode_करोwn;
			अवरोध;
		हाल 1:
			ssEntry->speed_spectrum_mode =
				pp_atomctrl_spपढ़ो_spectrum_mode_center;
			अवरोध;
		शेष:
			ssEntry->speed_spectrum_mode =
				pp_atomctrl_spपढ़ो_spectrum_mode_करोwn;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस entry_found ? 0 : 1;
पूर्ण

/*
 * Get the memory घड़ी spपढ़ो spectrum info
 */
पूर्णांक atomctrl_get_memory_घड़ी_spपढ़ो_spectrum(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर uपूर्णांक32_t memory_घड़ी,
		pp_atomctrl_पूर्णांकernal_ss_info *ssInfo)
अणु
	वापस asic_पूर्णांकernal_ss_get_ss_asignment(hwmgr,
			ASIC_INTERNAL_MEMORY_SS, memory_घड़ी, ssInfo);
पूर्ण

/*
 * Get the engine घड़ी spपढ़ो spectrum info
 */
पूर्णांक atomctrl_get_engine_घड़ी_spपढ़ो_spectrum(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर uपूर्णांक32_t engine_घड़ी,
		pp_atomctrl_पूर्णांकernal_ss_info *ssInfo)
अणु
	वापस asic_पूर्णांकernal_ss_get_ss_asignment(hwmgr,
			ASIC_INTERNAL_ENGINE_SS, engine_घड़ी, ssInfo);
पूर्ण

पूर्णांक atomctrl_पढ़ो_efuse(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t start_index,
		uपूर्णांक16_t end_index, uपूर्णांक32_t *efuse)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t mask;
	पूर्णांक result;
	READ_EFUSE_VALUE_PARAMETER efuse_param;

	अगर ((end_index - start_index)  == 31)
		mask = 0xFFFFFFFF;
	अन्यथा
		mask = (1 << ((end_index - start_index) + 1)) - 1;

	efuse_param.sEfuse.usEfuseIndex = cpu_to_le16((start_index / 32) * 4);
	efuse_param.sEfuse.ucBitShअगरt = (uपूर्णांक8_t)
			(start_index - ((start_index / 32) * 32));
	efuse_param.sEfuse.ucBitLength  = (uपूर्णांक8_t)
			((end_index - start_index) + 1);

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, ReadEfuseValue),
			(uपूर्णांक32_t *)&efuse_param);
	*efuse = result ? 0 : le32_to_cpu(efuse_param.ulEfuseValue) & mask;

	वापस result;
पूर्ण

पूर्णांक atomctrl_set_ac_timing_ai(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t memory_घड़ी,
			      uपूर्णांक8_t level)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	DYNAMICE_MEMORY_SETTINGS_PARAMETER_V2_1 memory_घड़ी_parameters;
	पूर्णांक result;

	memory_घड़ी_parameters.asDPMMCReg.ulClock.ulClockFreq =
		memory_घड़ी & SET_CLOCK_FREQ_MASK;
	memory_घड़ी_parameters.asDPMMCReg.ulClock.ulComputeClockFlag =
		ADJUST_MC_SETTING_PARAM;
	memory_घड़ी_parameters.asDPMMCReg.ucMclkDPMState = level;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
		 GetIndexIntoMasterTable(COMMAND, DynamicMemorySettings),
		(uपूर्णांक32_t *)&memory_घड़ी_parameters);

	वापस result;
पूर्ण

पूर्णांक atomctrl_get_voltage_evv_on_sclk_ai(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t voltage_type,
				uपूर्णांक32_t sclk, uपूर्णांक16_t भव_voltage_Id, uपूर्णांक32_t *voltage)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक result;
	GET_VOLTAGE_INFO_INPUT_PARAMETER_V1_3 get_voltage_info_param_space;

	get_voltage_info_param_space.ucVoltageType = voltage_type;
	get_voltage_info_param_space.ucVoltageMode = ATOM_GET_VOLTAGE_EVV_VOLTAGE;
	get_voltage_info_param_space.usVoltageLevel = cpu_to_le16(भव_voltage_Id);
	get_voltage_info_param_space.ulSCLKFreq = cpu_to_le32(sclk);

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, GetVoltageInfo),
			(uपूर्णांक32_t *)&get_voltage_info_param_space);

	*voltage = result ? 0 :
		le32_to_cpu(((GET_EVV_VOLTAGE_INFO_OUTPUT_PARAMETER_V1_3 *)(&get_voltage_info_param_space))->ulVoltageLevel);

	वापस result;
पूर्ण

पूर्णांक atomctrl_get_smc_sclk_range_table(काष्ठा pp_hwmgr *hwmgr, काष्ठा pp_atom_ctrl_sclk_range_table *table)
अणु

	पूर्णांक i;
	u8 frev, crev;
	u16 size;

	ATOM_SMU_INFO_V2_1 *psmu_info =
		(ATOM_SMU_INFO_V2_1 *)smu_atom_get_data_table(hwmgr->adev,
			GetIndexIntoMasterTable(DATA, SMU_Info),
			&size, &frev, &crev);


	क्रम (i = 0; i < psmu_info->ucSclkEntryNum; i++) अणु
		table->entry[i].ucVco_setting = psmu_info->asSclkFcwRangeEntry[i].ucVco_setting;
		table->entry[i].ucPostभाग = psmu_info->asSclkFcwRangeEntry[i].ucPostभाग;
		table->entry[i].usFcw_pcc =
			le16_to_cpu(psmu_info->asSclkFcwRangeEntry[i].ucFcw_pcc);
		table->entry[i].usFcw_trans_upper =
			le16_to_cpu(psmu_info->asSclkFcwRangeEntry[i].ucFcw_trans_upper);
		table->entry[i].usRcw_trans_lower =
			le16_to_cpu(psmu_info->asSclkFcwRangeEntry[i].ucRcw_trans_lower);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक atomctrl_get_vddc_shared_railinfo(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t *shared_rail)
अणु
	ATOM_SMU_INFO_V2_1 *psmu_info =
		(ATOM_SMU_INFO_V2_1 *)smu_atom_get_data_table(hwmgr->adev,
			GetIndexIntoMasterTable(DATA, SMU_Info),
			शून्य, शून्य, शून्य);
	अगर (!psmu_info)
		वापस -1;

	*shared_rail = psmu_info->ucSharePowerSource;

	वापस 0;
पूर्ण

पूर्णांक atomctrl_get_avfs_inक्रमmation(काष्ठा pp_hwmgr *hwmgr,
				  काष्ठा pp_atom_ctrl__avfs_parameters *param)
अणु
	ATOM_ASIC_PROFILING_INFO_V3_6 *profile = शून्य;

	अगर (param == शून्य)
		वापस -EINVAL;

	profile = (ATOM_ASIC_PROFILING_INFO_V3_6 *)
			smu_atom_get_data_table(hwmgr->adev,
					GetIndexIntoMasterTable(DATA, ASIC_ProfilingInfo),
					शून्य, शून्य, शून्य);
	अगर (!profile)
		वापस -1;

	param->ulAVFS_meanNsigma_Acontant0 = le32_to_cpu(profile->ulAVFS_meanNsigma_Acontant0);
	param->ulAVFS_meanNsigma_Acontant1 = le32_to_cpu(profile->ulAVFS_meanNsigma_Acontant1);
	param->ulAVFS_meanNsigma_Acontant2 = le32_to_cpu(profile->ulAVFS_meanNsigma_Acontant2);
	param->usAVFS_meanNsigma_DC_tol_sigma = le16_to_cpu(profile->usAVFS_meanNsigma_DC_tol_sigma);
	param->usAVFS_meanNsigma_Platक्रमm_mean = le16_to_cpu(profile->usAVFS_meanNsigma_Platक्रमm_mean);
	param->usAVFS_meanNsigma_Platक्रमm_sigma = le16_to_cpu(profile->usAVFS_meanNsigma_Platक्रमm_sigma);
	param->ulGB_VDROOP_TABLE_CKSOFF_a0 = le32_to_cpu(profile->ulGB_VDROOP_TABLE_CKSOFF_a0);
	param->ulGB_VDROOP_TABLE_CKSOFF_a1 = le32_to_cpu(profile->ulGB_VDROOP_TABLE_CKSOFF_a1);
	param->ulGB_VDROOP_TABLE_CKSOFF_a2 = le32_to_cpu(profile->ulGB_VDROOP_TABLE_CKSOFF_a2);
	param->ulGB_VDROOP_TABLE_CKSON_a0 = le32_to_cpu(profile->ulGB_VDROOP_TABLE_CKSON_a0);
	param->ulGB_VDROOP_TABLE_CKSON_a1 = le32_to_cpu(profile->ulGB_VDROOP_TABLE_CKSON_a1);
	param->ulGB_VDROOP_TABLE_CKSON_a2 = le32_to_cpu(profile->ulGB_VDROOP_TABLE_CKSON_a2);
	param->ulAVFSGB_FUSE_TABLE_CKSOFF_m1 = le32_to_cpu(profile->ulAVFSGB_FUSE_TABLE_CKSOFF_m1);
	param->usAVFSGB_FUSE_TABLE_CKSOFF_m2 = le16_to_cpu(profile->usAVFSGB_FUSE_TABLE_CKSOFF_m2);
	param->ulAVFSGB_FUSE_TABLE_CKSOFF_b = le32_to_cpu(profile->ulAVFSGB_FUSE_TABLE_CKSOFF_b);
	param->ulAVFSGB_FUSE_TABLE_CKSON_m1 = le32_to_cpu(profile->ulAVFSGB_FUSE_TABLE_CKSON_m1);
	param->usAVFSGB_FUSE_TABLE_CKSON_m2 = le16_to_cpu(profile->usAVFSGB_FUSE_TABLE_CKSON_m2);
	param->ulAVFSGB_FUSE_TABLE_CKSON_b = le32_to_cpu(profile->ulAVFSGB_FUSE_TABLE_CKSON_b);
	param->usMaxVoltage_0_25mv = le16_to_cpu(profile->usMaxVoltage_0_25mv);
	param->ucEnableGB_VDROOP_TABLE_CKSOFF = profile->ucEnableGB_VDROOP_TABLE_CKSOFF;
	param->ucEnableGB_VDROOP_TABLE_CKSON = profile->ucEnableGB_VDROOP_TABLE_CKSON;
	param->ucEnableGB_FUSE_TABLE_CKSOFF = profile->ucEnableGB_FUSE_TABLE_CKSOFF;
	param->ucEnableGB_FUSE_TABLE_CKSON = profile->ucEnableGB_FUSE_TABLE_CKSON;
	param->usPSM_Age_ComFactor = le16_to_cpu(profile->usPSM_Age_ComFactor);
	param->ucEnableApplyAVFS_CKS_OFF_Voltage = profile->ucEnableApplyAVFS_CKS_OFF_Voltage;

	वापस 0;
पूर्ण

पूर्णांक  atomctrl_get_svi2_info(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t voltage_type,
				uपूर्णांक8_t *svd_gpio_id, uपूर्णांक8_t *svc_gpio_id,
				uपूर्णांक16_t *load_line)
अणु
	ATOM_VOLTAGE_OBJECT_INFO_V3_1 *voltage_info =
		(ATOM_VOLTAGE_OBJECT_INFO_V3_1 *)get_voltage_info_table(hwmgr->adev);

	स्थिर ATOM_VOLTAGE_OBJECT_V3 *voltage_object;

	PP_ASSERT_WITH_CODE((शून्य != voltage_info),
			"Could not find Voltage Table in BIOS.", वापस -EINVAL);

	voltage_object = atomctrl_lookup_voltage_type_v3
		(voltage_info, voltage_type,  VOLTAGE_OBJ_SVID2);

	*svd_gpio_id = voltage_object->asSVID2Obj.ucSVDGpioId;
	*svc_gpio_id = voltage_object->asSVID2Obj.ucSVCGpioId;
	*load_line = voltage_object->asSVID2Obj.usLoadLine_PSI;

	वापस 0;
पूर्ण

पूर्णांक atomctrl_get_leakage_id_from_efuse(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t *भव_voltage_id)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	SET_VOLTAGE_PS_ALLOCATION allocation;
	SET_VOLTAGE_PARAMETERS_V1_3 *voltage_parameters =
			(SET_VOLTAGE_PARAMETERS_V1_3 *)&allocation.sASICSetVoltage;
	पूर्णांक result;

	voltage_parameters->ucVoltageMode = ATOM_GET_LEAKAGE_ID;

	result = amdgpu_atom_execute_table(adev->mode_info.atom_context,
			GetIndexIntoMasterTable(COMMAND, SetVoltage),
			(uपूर्णांक32_t *)voltage_parameters);

	*भव_voltage_id = voltage_parameters->usVoltageLevel;

	वापस result;
पूर्ण

पूर्णांक atomctrl_get_leakage_vddc_base_on_leakage(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक16_t *vddc, uपूर्णांक16_t *vddci,
					uपूर्णांक16_t भव_voltage_id,
					uपूर्णांक16_t efuse_voltage_id)
अणु
	पूर्णांक i, j;
	पूर्णांक ix;
	u16 *leakage_bin, *vddc_id_buf, *vddc_buf, *vddci_id_buf, *vddci_buf;
	ATOM_ASIC_PROFILING_INFO_V2_1 *profile;

	*vddc = 0;
	*vddci = 0;

	ix = GetIndexIntoMasterTable(DATA, ASIC_ProfilingInfo);

	profile = (ATOM_ASIC_PROFILING_INFO_V2_1 *)
			smu_atom_get_data_table(hwmgr->adev,
					ix,
					शून्य, शून्य, शून्य);
	अगर (!profile)
		वापस -EINVAL;

	अगर ((profile->asHeader.ucTableFormatRevision >= 2) &&
		(profile->asHeader.ucTableContentRevision >= 1) &&
		(profile->asHeader.usStructureSize >= माप(ATOM_ASIC_PROFILING_INFO_V2_1))) अणु
		leakage_bin = (u16 *)((अक्षर *)profile + profile->usLeakageBinArrayOffset);
		vddc_id_buf = (u16 *)((अक्षर *)profile + profile->usElbVDDC_IdArrayOffset);
		vddc_buf = (u16 *)((अक्षर *)profile + profile->usElbVDDC_LevelArrayOffset);
		अगर (profile->ucElbVDDC_Num > 0) अणु
			क्रम (i = 0; i < profile->ucElbVDDC_Num; i++) अणु
				अगर (vddc_id_buf[i] == भव_voltage_id) अणु
					क्रम (j = 0; j < profile->ucLeakageBinNum; j++) अणु
						अगर (efuse_voltage_id <= leakage_bin[j]) अणु
							*vddc = vddc_buf[j * profile->ucElbVDDC_Num + i];
							अवरोध;
						पूर्ण
					पूर्ण
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		vddci_id_buf = (u16 *)((अक्षर *)profile + profile->usElbVDDCI_IdArrayOffset);
		vddci_buf   = (u16 *)((अक्षर *)profile + profile->usElbVDDCI_LevelArrayOffset);
		अगर (profile->ucElbVDDCI_Num > 0) अणु
			क्रम (i = 0; i < profile->ucElbVDDCI_Num; i++) अणु
				अगर (vddci_id_buf[i] == भव_voltage_id) अणु
					क्रम (j = 0; j < profile->ucLeakageBinNum; j++) अणु
						अगर (efuse_voltage_id <= leakage_bin[j]) अणु
							*vddci = vddci_buf[j * profile->ucElbVDDCI_Num + i];
							अवरोध;
						पूर्ण
					पूर्ण
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम atomctrl_get_voltage_range(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *max_vddc,
							uपूर्णांक32_t *min_vddc)
अणु
	व्योम *profile;

	profile = smu_atom_get_data_table(hwmgr->adev,
					GetIndexIntoMasterTable(DATA, ASIC_ProfilingInfo),
					शून्य, शून्य, शून्य);

	अगर (profile) अणु
		चयन (hwmgr->chip_id) अणु
		हाल CHIP_TONGA:
		हाल CHIP_FIJI:
			*max_vddc = le32_to_cpu(((ATOM_ASIC_PROFILING_INFO_V3_3 *)profile)->ulMaxVddc) / 4;
			*min_vddc = le32_to_cpu(((ATOM_ASIC_PROFILING_INFO_V3_3 *)profile)->ulMinVddc) / 4;
			वापस;
		हाल CHIP_POLARIS11:
		हाल CHIP_POLARIS10:
		हाल CHIP_POLARIS12:
			*max_vddc = le32_to_cpu(((ATOM_ASIC_PROFILING_INFO_V3_6 *)profile)->ulMaxVddc) / 100;
			*min_vddc = le32_to_cpu(((ATOM_ASIC_PROFILING_INFO_V3_6 *)profile)->ulMinVddc) / 100;
			वापस;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	*max_vddc = 0;
	*min_vddc = 0;
पूर्ण

पूर्णांक atomctrl_get_edc_hilo_leakage_offset_table(काष्ठा pp_hwmgr *hwmgr,
					       AtomCtrl_HiLoLeakageOffsetTable *table)
अणु
	ATOM_GFX_INFO_V2_3 *gfxinfo = smu_atom_get_data_table(hwmgr->adev,
					GetIndexIntoMasterTable(DATA, GFX_Info),
					शून्य, शून्य, शून्य);
	अगर (!gfxinfo)
		वापस -ENOENT;

	table->usHiLoLeakageThreshold = gfxinfo->usHiLoLeakageThreshold;
	table->usEdcDidtLoDpm7TableOffset = gfxinfo->usEdcDidtLoDpm7TableOffset;
	table->usEdcDidtHiDpm7TableOffset = gfxinfo->usEdcDidtHiDpm7TableOffset;

	वापस 0;
पूर्ण

अटल AtomCtrl_EDCLeakgeTable *get_edc_leakage_table(काष्ठा pp_hwmgr *hwmgr,
						      uपूर्णांक16_t offset)
अणु
	व्योम *table_address;
	अक्षर *temp;

	table_address = smu_atom_get_data_table(hwmgr->adev,
			GetIndexIntoMasterTable(DATA, GFX_Info),
			शून्य, शून्य, शून्य);
	अगर (!table_address)
		वापस शून्य;

	temp = (अक्षर *)table_address;
	table_address += offset;

	वापस (AtomCtrl_EDCLeakgeTable *)temp;
पूर्ण

पूर्णांक atomctrl_get_edc_leakage_table(काष्ठा pp_hwmgr *hwmgr,
				   AtomCtrl_EDCLeakgeTable *table,
				   uपूर्णांक16_t offset)
अणु
	uपूर्णांक32_t length, i;
	AtomCtrl_EDCLeakgeTable *leakage_table =
		get_edc_leakage_table(hwmgr, offset);

	अगर (!leakage_table)
		वापस -ENOENT;

	length = माप(leakage_table->DIDT_REG) /
		 माप(leakage_table->DIDT_REG[0]);
	क्रम (i = 0; i < length; i++)
		table->DIDT_REG[i] = leakage_table->DIDT_REG[i];

	वापस 0;
पूर्ण
