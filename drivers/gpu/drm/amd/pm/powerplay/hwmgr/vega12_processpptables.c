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
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>

#समावेश "vega12/smu9_driver_if.h"
#समावेश "vega12_processpptables.h"
#समावेश "ppatomfwctrl.h"
#समावेश "atomfirmware.h"
#समावेश "pp_debug.h"
#समावेश "cgs_common.h"
#समावेश "vega12_pptable.h"

अटल व्योम set_hw_cap(काष्ठा pp_hwmgr *hwmgr, bool enable,
		क्रमागत phm_platक्रमm_caps cap)
अणु
	अगर (enable)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, cap);
	अन्यथा
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps, cap);
पूर्ण

अटल स्थिर व्योम *get_घातerplay_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक index = GetIndexIntoMasterDataTable(घातerplayinfo);

	u16 size;
	u8 frev, crev;
	स्थिर व्योम *table_address = hwmgr->soft_pp_table;

	अगर (!table_address) अणु
		table_address = (ATOM_Vega12_POWERPLAYTABLE *)
				smu_atom_get_data_table(hwmgr->adev, index,
						&size, &frev, &crev);

		hwmgr->soft_pp_table = table_address;	/*Cache the result in RAM.*/
		hwmgr->soft_pp_table_size = size;
	पूर्ण

	वापस table_address;
पूर्ण

अटल पूर्णांक check_घातerplay_tables(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर ATOM_Vega12_POWERPLAYTABLE *घातerplay_table)
अणु
	PP_ASSERT_WITH_CODE((घातerplay_table->sHeader.क्रमmat_revision >=
		ATOM_VEGA12_TABLE_REVISION_VEGA12),
		"Unsupported PPTable format!", वापस -1);
	PP_ASSERT_WITH_CODE(घातerplay_table->sHeader.काष्ठाuresize > 0,
		"Invalid PowerPlay Table!", वापस -1);

	वापस 0;
पूर्ण

अटल पूर्णांक set_platक्रमm_caps(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घातerplay_caps)
अणु
	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_VEGA12_PP_PLATFORM_CAP_POWERPLAY),
			PHM_Platक्रमmCaps_PowerPlaySupport);

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_VEGA12_PP_PLATFORM_CAP_SBIOSPOWERSOURCE),
			PHM_Platक्रमmCaps_BiosPowerSourceControl);

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_VEGA12_PP_PLATFORM_CAP_BACO),
			PHM_Platक्रमmCaps_BACO);

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_VEGA12_PP_PLATFORM_CAP_BAMACO),
			 PHM_Platक्रमmCaps_BAMACO);

	वापस 0;
पूर्ण

अटल पूर्णांक append_vbios_pptable(काष्ठा pp_hwmgr *hwmgr, PPTable_t *ppsmc_pptable)
अणु
	काष्ठा pp_atomfwctrl_smc_dpm_parameters smc_dpm_table;

	PP_ASSERT_WITH_CODE(
		pp_atomfwctrl_get_smc_dpm_inक्रमmation(hwmgr, &smc_dpm_table) == 0,
		"[appendVbiosPPTable] Failed to retrieve Smc Dpm Table from VBIOS!",
		वापस -1);

	ppsmc_pptable->Liquid1_I2C_address = smc_dpm_table.liquid1_i2c_address;
	ppsmc_pptable->Liquid2_I2C_address = smc_dpm_table.liquid2_i2c_address;
	ppsmc_pptable->Vr_I2C_address = smc_dpm_table.vr_i2c_address;
	ppsmc_pptable->Plx_I2C_address = smc_dpm_table.plx_i2c_address;

	ppsmc_pptable->Liquid_I2C_LineSCL = smc_dpm_table.liquid_i2c_linescl;
	ppsmc_pptable->Liquid_I2C_LineSDA = smc_dpm_table.liquid_i2c_linesda;
	ppsmc_pptable->Vr_I2C_LineSCL = smc_dpm_table.vr_i2c_linescl;
	ppsmc_pptable->Vr_I2C_LineSDA = smc_dpm_table.vr_i2c_linesda;

	ppsmc_pptable->Plx_I2C_LineSCL = smc_dpm_table.plx_i2c_linescl;
	ppsmc_pptable->Plx_I2C_LineSDA = smc_dpm_table.plx_i2c_linesda;
	ppsmc_pptable->VrSensorPresent = smc_dpm_table.vrsensorpresent;
	ppsmc_pptable->LiquidSensorPresent = smc_dpm_table.liquidsensorpresent;

	ppsmc_pptable->MaxVoltageStepGfx = smc_dpm_table.maxvoltagestepgfx;
	ppsmc_pptable->MaxVoltageStepSoc = smc_dpm_table.maxvoltagestepsoc;

	ppsmc_pptable->VddGfxVrMapping = smc_dpm_table.vddgfxvrmapping;
	ppsmc_pptable->VddSocVrMapping = smc_dpm_table.vddsocvrmapping;
	ppsmc_pptable->VddMem0VrMapping = smc_dpm_table.vddmem0vrmapping;
	ppsmc_pptable->VddMem1VrMapping = smc_dpm_table.vddmem1vrmapping;

	ppsmc_pptable->GfxUlvPhaseSheddingMask = smc_dpm_table.gfxulvphasesheddingmask;
	ppsmc_pptable->SocUlvPhaseSheddingMask = smc_dpm_table.soculvphasesheddingmask;

	ppsmc_pptable->GfxMaxCurrent = smc_dpm_table.gfxmaxcurrent;
	ppsmc_pptable->GfxOffset = smc_dpm_table.gfxoffset;
	ppsmc_pptable->Padding_TelemetryGfx = smc_dpm_table.padding_telemetrygfx;

	ppsmc_pptable->SocMaxCurrent = smc_dpm_table.socmaxcurrent;
	ppsmc_pptable->SocOffset = smc_dpm_table.socoffset;
	ppsmc_pptable->Padding_TelemetrySoc = smc_dpm_table.padding_telemetrysoc;

	ppsmc_pptable->Mem0MaxCurrent = smc_dpm_table.mem0maxcurrent;
	ppsmc_pptable->Mem0Offset = smc_dpm_table.mem0offset;
	ppsmc_pptable->Padding_TelemetryMem0 = smc_dpm_table.padding_telemetrymem0;

	ppsmc_pptable->Mem1MaxCurrent = smc_dpm_table.mem1maxcurrent;
	ppsmc_pptable->Mem1Offset = smc_dpm_table.mem1offset;
	ppsmc_pptable->Padding_TelemetryMem1 = smc_dpm_table.padding_telemetrymem1;

	ppsmc_pptable->AcDcGpio = smc_dpm_table.acdcgpio;
	ppsmc_pptable->AcDcPolarity = smc_dpm_table.acdcpolarity;
	ppsmc_pptable->VR0HotGpio = smc_dpm_table.vr0hotgpio;
	ppsmc_pptable->VR0HotPolarity = smc_dpm_table.vr0hotpolarity;

	ppsmc_pptable->VR1HotGpio = smc_dpm_table.vr1hotgpio;
	ppsmc_pptable->VR1HotPolarity = smc_dpm_table.vr1hotpolarity;
	ppsmc_pptable->Padding1 = smc_dpm_table.padding1;
	ppsmc_pptable->Padding2 = smc_dpm_table.padding2;

	ppsmc_pptable->LedPin0 = smc_dpm_table.ledpin0;
	ppsmc_pptable->LedPin1 = smc_dpm_table.ledpin1;
	ppsmc_pptable->LedPin2 = smc_dpm_table.ledpin2;

	ppsmc_pptable->PllGfxclkSpपढ़ोEnabled = smc_dpm_table.pllgfxclkspपढ़ोenabled;
	ppsmc_pptable->PllGfxclkSpपढ़ोPercent = smc_dpm_table.pllgfxclkspपढ़ोpercent;
	ppsmc_pptable->PllGfxclkSpपढ़ोFreq = smc_dpm_table.pllgfxclkspपढ़ोfreq;

	ppsmc_pptable->UclkSpपढ़ोEnabled = 0;
	ppsmc_pptable->UclkSpपढ़ोPercent = smc_dpm_table.uclkspपढ़ोpercent;
	ppsmc_pptable->UclkSpपढ़ोFreq = smc_dpm_table.uclkspपढ़ोfreq;

	ppsmc_pptable->SocclkSpपढ़ोEnabled = 0;
	ppsmc_pptable->SocclkSpपढ़ोPercent = smc_dpm_table.socclkspपढ़ोpercent;
	ppsmc_pptable->SocclkSpपढ़ोFreq = smc_dpm_table.socclkspपढ़ोfreq;

	ppsmc_pptable->AcgGfxclkSpपढ़ोEnabled = smc_dpm_table.acggfxclkspपढ़ोenabled;
	ppsmc_pptable->AcgGfxclkSpपढ़ोPercent = smc_dpm_table.acggfxclkspपढ़ोpercent;
	ppsmc_pptable->AcgGfxclkSpपढ़ोFreq = smc_dpm_table.acggfxclkspपढ़ोfreq;

	ppsmc_pptable->Vr2_I2C_address = smc_dpm_table.Vr2_I2C_address;

	ppsmc_pptable->Vr2_I2C_address = smc_dpm_table.Vr2_I2C_address;

	वापस 0;
पूर्ण

#घोषणा VEGA12_ENGINECLOCK_HARDMAX 198000
अटल पूर्णांक init_घातerplay_table_inक्रमmation(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर ATOM_Vega12_POWERPLAYTABLE *घातerplay_table)
अणु
	काष्ठा phm_ppt_v3_inक्रमmation *pptable_inक्रमmation =
		(काष्ठा phm_ppt_v3_inक्रमmation *)hwmgr->pptable;
	uपूर्णांक32_t disable_घातer_control = 0;
	पूर्णांक result;

	hwmgr->thermal_controller.ucType = घातerplay_table->ucThermalControllerType;
	pptable_inक्रमmation->uc_thermal_controller_type = घातerplay_table->ucThermalControllerType;

	set_hw_cap(hwmgr,
		ATOM_VEGA12_PP_THERMALCONTROLLER_NONE != hwmgr->thermal_controller.ucType,
		PHM_Platक्रमmCaps_ThermalController);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_MicrocodeFanControl);

	अगर (le32_to_cpu(घातerplay_table->ODSettingsMax[ATOM_VEGA12_ODSETTING_GFXCLKFMAX]) > VEGA12_ENGINECLOCK_HARDMAX)
		hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock = VEGA12_ENGINECLOCK_HARDMAX;
	अन्यथा
		hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock =
			le32_to_cpu(घातerplay_table->ODSettingsMax[ATOM_VEGA12_ODSETTING_GFXCLKFMAX]);
	hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock =
		le32_to_cpu(घातerplay_table->ODSettingsMax[ATOM_VEGA12_ODSETTING_UCLKFMAX]);

	phm_copy_overdrive_settings_limits_array(hwmgr,
						 &pptable_inक्रमmation->od_settings_max,
						 घातerplay_table->ODSettingsMax,
						 ATOM_VEGA12_ODSETTING_COUNT);
	phm_copy_overdrive_settings_limits_array(hwmgr,
						 &pptable_inक्रमmation->od_settings_min,
						 घातerplay_table->ODSettingsMin,
						 ATOM_VEGA12_ODSETTING_COUNT);

	/* hwmgr->platक्रमmDescriptor.minOverdriveVDDC = 0;
	hwmgr->platक्रमmDescriptor.maxOverdriveVDDC = 0;
	hwmgr->platक्रमmDescriptor.overdriveVDDCStep = 0; */

	अगर (hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock > 0
		&& hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock > 0)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_ACOverdriveSupport);

	pptable_inक्रमmation->us_small_घातer_limit1 = le16_to_cpu(घातerplay_table->usSmallPowerLimit1);
	pptable_inक्रमmation->us_small_घातer_limit2 = le16_to_cpu(घातerplay_table->usSmallPowerLimit2);
	pptable_inक्रमmation->us_boost_घातer_limit = le16_to_cpu(घातerplay_table->usBoostPowerLimit);
	pptable_inक्रमmation->us_od_turbo_घातer_limit = le16_to_cpu(घातerplay_table->usODTurboPowerLimit);
	pptable_inक्रमmation->us_od_घातersave_घातer_limit = le16_to_cpu(घातerplay_table->usODPowerSavePowerLimit);

	pptable_inक्रमmation->us_software_shutकरोwn_temp = le16_to_cpu(घातerplay_table->usSoftwareShutकरोwnTemp);

	hwmgr->platक्रमm_descriptor.TDPODLimit = le32_to_cpu(घातerplay_table->ODSettingsMax[ATOM_VEGA12_ODSETTING_POWERPERCENTAGE]);

	disable_घातer_control = 0;
	अगर (!disable_घातer_control) अणु
		/* enable TDP overdrive (PowerControl) feature as well अगर supported */
		अगर (hwmgr->platक्रमm_descriptor.TDPODLimit)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_PowerControl);
	पूर्ण

	phm_copy_घड़ी_limits_array(hwmgr, &pptable_inक्रमmation->घातer_saving_घड़ी_max, घातerplay_table->PowerSavingClockMax, ATOM_VEGA12_PPCLOCK_COUNT);
	phm_copy_घड़ी_limits_array(hwmgr, &pptable_inक्रमmation->घातer_saving_घड़ी_min, घातerplay_table->PowerSavingClockMin, ATOM_VEGA12_PPCLOCK_COUNT);

	pptable_inक्रमmation->smc_pptable = kmemdup(&(घातerplay_table->smcPPTable),
						   माप(PPTable_t), GFP_KERNEL);
	अगर (pptable_inक्रमmation->smc_pptable == शून्य)
		वापस -ENOMEM;

	result = append_vbios_pptable(hwmgr, (pptable_inक्रमmation->smc_pptable));

	वापस result;
पूर्ण

अटल पूर्णांक vega12_pp_tables_initialize(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	स्थिर ATOM_Vega12_POWERPLAYTABLE *घातerplay_table;

	hwmgr->pptable = kzalloc(माप(काष्ठा phm_ppt_v3_inक्रमmation), GFP_KERNEL);
	PP_ASSERT_WITH_CODE((hwmgr->pptable != शून्य),
		"Failed to allocate hwmgr->pptable!", वापस -ENOMEM);

	घातerplay_table = get_घातerplay_table(hwmgr);
	PP_ASSERT_WITH_CODE((घातerplay_table != शून्य),
		"Missing PowerPlay Table!", वापस -1);

	result = check_घातerplay_tables(hwmgr, घातerplay_table);
	PP_ASSERT_WITH_CODE((result == 0),
		"check_powerplay_tables failed", वापस result);

	result = set_platक्रमm_caps(hwmgr,
			le32_to_cpu(घातerplay_table->ulPlatक्रमmCaps));
	PP_ASSERT_WITH_CODE((result == 0),
		"set_platform_caps failed", वापस result);

	result = init_घातerplay_table_inक्रमmation(hwmgr, घातerplay_table);
	PP_ASSERT_WITH_CODE((result == 0),
		"init_powerplay_table_information failed", वापस result);

	वापस result;
पूर्ण

अटल पूर्णांक vega12_pp_tables_uninitialize(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा phm_ppt_v3_inक्रमmation *pp_table_info =
			(काष्ठा phm_ppt_v3_inक्रमmation *)(hwmgr->pptable);

	kमुक्त(pp_table_info->घातer_saving_घड़ी_max);
	pp_table_info->घातer_saving_घड़ी_max = शून्य;

	kमुक्त(pp_table_info->घातer_saving_घड़ी_min);
	pp_table_info->घातer_saving_घड़ी_min = शून्य;

	kमुक्त(pp_table_info->od_settings_max);
	pp_table_info->od_settings_max = शून्य;

	kमुक्त(pp_table_info->od_settings_min);
	pp_table_info->od_settings_min = शून्य;

	kमुक्त(pp_table_info->smc_pptable);
	pp_table_info->smc_pptable = शून्य;

	kमुक्त(hwmgr->pptable);
	hwmgr->pptable = शून्य;

	वापस 0;
पूर्ण

स्थिर काष्ठा pp_table_func vega12_pptable_funcs = अणु
	.pptable_init = vega12_pp_tables_initialize,
	.pptable_fini = vega12_pp_tables_uninitialize,
पूर्ण;

#अगर 0
अटल uपूर्णांक32_t make_classअगरication_flags(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक16_t classअगरication, uपूर्णांक16_t classअगरication2)
अणु
	uपूर्णांक32_t result = 0;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_BOOT)
		result |= PP_StateClassअगरicationFlag_Boot;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_THERMAL)
		result |= PP_StateClassअगरicationFlag_Thermal;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_LIMITEDPOWERSOURCE)
		result |= PP_StateClassअगरicationFlag_LimitedPowerSource;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_REST)
		result |= PP_StateClassअगरicationFlag_Rest;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_FORCED)
		result |= PP_StateClassअगरicationFlag_Forced;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_ACPI)
		result |= PP_StateClassअगरicationFlag_ACPI;

	अगर (classअगरication2 & ATOM_PPLIB_CLASSIFICATION2_LIMITEDPOWERSOURCE_2)
		result |= PP_StateClassअगरicationFlag_LimitedPowerSource_2;

	वापस result;
पूर्ण

पूर्णांक vega12_get_घातerplay_table_entry(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t entry_index, काष्ठा pp_घातer_state *घातer_state,
		पूर्णांक (*call_back_func)(काष्ठा pp_hwmgr *, व्योम *,
				काष्ठा pp_घातer_state *, व्योम *, uपूर्णांक32_t))
अणु
	पूर्णांक result = 0;
	स्थिर ATOM_Vega12_State_Array *state_arrays;
	स्थिर ATOM_Vega12_State *state_entry;
	स्थिर ATOM_Vega12_POWERPLAYTABLE *pp_table =
			get_घातerplay_table(hwmgr);

	PP_ASSERT_WITH_CODE(pp_table, "Missing PowerPlay Table!",
			वापस -1;);
	घातer_state->classअगरication.bios_index = entry_index;

	अगर (pp_table->sHeader.क्रमmat_revision >=
			ATOM_Vega12_TABLE_REVISION_VEGA12) अणु
		state_arrays = (ATOM_Vega12_State_Array *)
				(((अचिन्हित दीर्घ)pp_table) +
				le16_to_cpu(pp_table->usStateArrayOffset));

		PP_ASSERT_WITH_CODE(pp_table->usStateArrayOffset > 0,
				"Invalid PowerPlay Table State Array Offset.",
				वापस -1);
		PP_ASSERT_WITH_CODE(state_arrays->ucNumEntries > 0,
				"Invalid PowerPlay Table State Array.",
				वापस -1);
		PP_ASSERT_WITH_CODE((entry_index <= state_arrays->ucNumEntries),
				"Invalid PowerPlay Table State Array Entry.",
				वापस -1);

		state_entry = &(state_arrays->states[entry_index]);

		result = call_back_func(hwmgr, (व्योम *)state_entry, घातer_state,
				(व्योम *)pp_table,
				make_classअगरication_flags(hwmgr,
					le16_to_cpu(state_entry->usClassअगरication),
					le16_to_cpu(state_entry->usClassअगरication2)));
	पूर्ण

	अगर (!result && (घातer_state->classअगरication.flags &
			PP_StateClassअगरicationFlag_Boot))
		result = hwmgr->hwmgr_func->patch_boot_state(hwmgr, &(घातer_state->hardware));

	वापस result;
पूर्ण
#पूर्ण_अगर
