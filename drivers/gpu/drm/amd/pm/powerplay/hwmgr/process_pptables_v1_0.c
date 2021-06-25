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

#समावेश "process_pptables_v1_0.h"
#समावेश "ppatomctrl.h"
#समावेश "atombios.h"
#समावेश "hwmgr.h"
#समावेश "cgs_common.h"
#समावेश "pptable_v1_0.h"

/**
 * set_hw_cap - Private Function used during initialization.
 * @hwmgr: Poपूर्णांकer to the hardware manager.
 * @setIt: A flag indication अगर the capability should be set (TRUE) or reset (FALSE).
 * @cap: Which capability to set/reset.
 */
अटल व्योम set_hw_cap(काष्ठा pp_hwmgr *hwmgr, bool setIt, क्रमागत phm_platक्रमm_caps cap)
अणु
	अगर (setIt)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, cap);
	अन्यथा
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps, cap);
पूर्ण


/**
 * set_platक्रमm_caps - Private Function used during initialization.
 * @hwmgr: Poपूर्णांकer to the hardware manager.
 * @घातerplay_caps: the bit array (from BIOS) of capability bits.
 * Exception:  the current implementation always वापसs 1.
 */
अटल पूर्णांक set_platक्रमm_caps(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t घातerplay_caps)
अणु
	PP_ASSERT_WITH_CODE((~घातerplay_caps & ____RETIRE16____),
		"ATOM_PP_PLATFORM_CAP_ASPM_L1 is not supported!", जारी);
	PP_ASSERT_WITH_CODE((~घातerplay_caps & ____RETIRE64____),
		"ATOM_PP_PLATFORM_CAP_GEMINIPRIMARY is not supported!", जारी);
	PP_ASSERT_WITH_CODE((~घातerplay_caps & ____RETIRE512____),
		"ATOM_PP_PLATFORM_CAP_SIDEPORTCONTROL is not supported!", जारी);
	PP_ASSERT_WITH_CODE((~घातerplay_caps & ____RETIRE1024____),
		"ATOM_PP_PLATFORM_CAP_TURNOFFPLL_ASPML1 is not supported!", जारी);
	PP_ASSERT_WITH_CODE((~घातerplay_caps & ____RETIRE2048____),
		"ATOM_PP_PLATFORM_CAP_HTLINKCONTROL is not supported!", जारी);

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_TONGA_PP_PLATFORM_CAP_POWERPLAY),
			PHM_Platक्रमmCaps_PowerPlaySupport
		  );

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_TONGA_PP_PLATFORM_CAP_SBIOSPOWERSOURCE),
			PHM_Platक्रमmCaps_BiosPowerSourceControl
		  );

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_TONGA_PP_PLATFORM_CAP_HARDWAREDC),
			PHM_Platक्रमmCaps_AutomaticDCTransition
		  );

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_TONGA_PP_PLATFORM_CAP_MVDD_CONTROL),
			PHM_Platक्रमmCaps_EnableMVDDControl
		  );

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_TONGA_PP_PLATFORM_CAP_VDDCI_CONTROL),
			PHM_Platक्रमmCaps_ControlVDDCI
		  );

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_TONGA_PP_PLATFORM_CAP_VDDGFX_CONTROL),
			PHM_Platक्रमmCaps_ControlVDDGFX
		  );

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_TONGA_PP_PLATFORM_CAP_BACO),
			PHM_Platक्रमmCaps_BACO
		  );

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_TONGA_PP_PLATFORM_CAP_DISABLE_VOLTAGE_ISLAND),
			PHM_Platक्रमmCaps_DisableVoltageIsland
		  );

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_TONGA_PP_PLATFORM_COMBINE_PCC_WITH_THERMAL_SIGNAL),
			PHM_Platक्रमmCaps_CombinePCCWithThermalSignal
		  );

	set_hw_cap(
			hwmgr,
			0 != (घातerplay_caps & ATOM_TONGA_PLATFORM_LOAD_POST_PRODUCTION_FIRMWARE),
			PHM_Platक्रमmCaps_LoadPostProductionFirmware
		  );

	वापस 0;
पूर्ण

/*
 * Private Function to get the PowerPlay Table Address.
 */
अटल स्थिर व्योम *get_घातerplay_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक index = GetIndexIntoMasterTable(DATA, PowerPlayInfo);

	u16 size;
	u8 frev, crev;
	व्योम *table_address = (व्योम *)hwmgr->soft_pp_table;

	अगर (!table_address) अणु
		table_address = (ATOM_Tonga_POWERPLAYTABLE *)
				smu_atom_get_data_table(hwmgr->adev,
						index, &size, &frev, &crev);
		hwmgr->soft_pp_table = table_address;	/*Cache the result in RAM.*/
		hwmgr->soft_pp_table_size = size;
	पूर्ण

	वापस table_address;
पूर्ण

अटल पूर्णांक get_vddc_lookup_table(
		काष्ठा pp_hwmgr	*hwmgr,
		phm_ppt_v1_voltage_lookup_table	**lookup_table,
		स्थिर ATOM_Tonga_Voltage_Lookup_Table *vddc_lookup_pp_tables,
		uपूर्णांक32_t max_levels
		)
अणु
	uपूर्णांक32_t i;
	phm_ppt_v1_voltage_lookup_table *table;
	phm_ppt_v1_voltage_lookup_record *record;
	ATOM_Tonga_Voltage_Lookup_Record *atom_record;

	PP_ASSERT_WITH_CODE((0 != vddc_lookup_pp_tables->ucNumEntries),
		"Invalid CAC Leakage PowerPlay Table!", वापस 1);

	table = kzalloc(काष्ठा_size(table, entries, max_levels), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	table->count = vddc_lookup_pp_tables->ucNumEntries;

	क्रम (i = 0; i < vddc_lookup_pp_tables->ucNumEntries; i++) अणु
		record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
					phm_ppt_v1_voltage_lookup_record,
					entries, table, i);
		atom_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
					ATOM_Tonga_Voltage_Lookup_Record,
					entries, vddc_lookup_pp_tables, i);
		record->us_calculated = 0;
		record->us_vdd = le16_to_cpu(atom_record->usVdd);
		record->us_cac_low = le16_to_cpu(atom_record->usCACLow);
		record->us_cac_mid = le16_to_cpu(atom_record->usCACMid);
		record->us_cac_high = le16_to_cpu(atom_record->usCACHigh);
	पूर्ण

	*lookup_table = table;

	वापस 0;
पूर्ण

/**
 * get_platक्रमm_घातer_management_table - Private Function used during initialization.
 * Initialize Platक्रमm Power Management Parameter table
 * @hwmgr: Poपूर्णांकer to the hardware manager.
 * @atom_ppm_table: Poपूर्णांकer to PPM table in VBIOS
 */
अटल पूर्णांक get_platक्रमm_घातer_management_table(
		काष्ठा pp_hwmgr *hwmgr,
		ATOM_Tonga_PPM_Table *atom_ppm_table)
अणु
	काष्ठा phm_ppm_table *ptr = kzalloc(माप(ATOM_Tonga_PPM_Table), GFP_KERNEL);
	काष्ठा phm_ppt_v1_inक्रमmation *pp_table_inक्रमmation =
		(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	अगर (शून्य == ptr)
		वापस -ENOMEM;

	ptr->ppm_design
		= atom_ppm_table->ucPpmDesign;
	ptr->cpu_core_number
		= le16_to_cpu(atom_ppm_table->usCpuCoreNumber);
	ptr->platक्रमm_tdp
		= le32_to_cpu(atom_ppm_table->ulPlatक्रमmTDP);
	ptr->small_ac_platक्रमm_tdp
		= le32_to_cpu(atom_ppm_table->ulSmallACPlatक्रमmTDP);
	ptr->platक्रमm_tdc
		= le32_to_cpu(atom_ppm_table->ulPlatक्रमmTDC);
	ptr->small_ac_platक्रमm_tdc
		= le32_to_cpu(atom_ppm_table->ulSmallACPlatक्रमmTDC);
	ptr->apu_tdp
		= le32_to_cpu(atom_ppm_table->ulApuTDP);
	ptr->dgpu_tdp
		= le32_to_cpu(atom_ppm_table->ulDGpuTDP);
	ptr->dgpu_ulv_घातer
		= le32_to_cpu(atom_ppm_table->ulDGpuUlvPower);
	ptr->tj_max
		= le32_to_cpu(atom_ppm_table->ulTjmax);

	pp_table_inक्रमmation->ppm_parameter_table = ptr;

	वापस 0;
पूर्ण

/**
 * init_dpm_2_parameters - Private Function used during initialization.
 * Initialize TDP limits क्रम DPM2
 * @hwmgr: Poपूर्णांकer to the hardware manager.
 * @घातerplay_table: Poपूर्णांकer to the PowerPlay Table.
 */
अटल पूर्णांक init_dpm_2_parameters(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर ATOM_Tonga_POWERPLAYTABLE *घातerplay_table
		)
अणु
	पूर्णांक result = 0;
	काष्ठा phm_ppt_v1_inक्रमmation *pp_table_inक्रमmation = (काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	ATOM_Tonga_PPM_Table *atom_ppm_table;
	uपूर्णांक32_t disable_ppm = 0;
	uपूर्णांक32_t disable_घातer_control = 0;

	pp_table_inक्रमmation->us_ulv_voltage_offset =
		le16_to_cpu(घातerplay_table->usUlvVoltageOffset);

	pp_table_inक्रमmation->ppm_parameter_table = शून्य;
	pp_table_inक्रमmation->vddc_lookup_table = शून्य;
	pp_table_inक्रमmation->vddgfx_lookup_table = शून्य;
	/* TDP limits */
	hwmgr->platक्रमm_descriptor.TDPODLimit =
		le16_to_cpu(घातerplay_table->usPowerControlLimit);
	hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगent = 0;
	hwmgr->platक्रमm_descriptor.VidAdjusपंचांगent = 0;
	hwmgr->platक्रमm_descriptor.VidAdjusपंचांगentPolarity = 0;
	hwmgr->platक्रमm_descriptor.VidMinLimit = 0;
	hwmgr->platक्रमm_descriptor.VidMaxLimit = 1500000;
	hwmgr->platक्रमm_descriptor.VidStep = 6250;

	disable_घातer_control = 0;
	अगर (0 == disable_घातer_control) अणु
		/* enable TDP overdrive (PowerControl) feature as well अगर supported */
		अगर (hwmgr->platक्रमm_descriptor.TDPODLimit != 0)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_PowerControl);
	पूर्ण

	अगर (0 != घातerplay_table->usVddcLookupTableOffset) अणु
		स्थिर ATOM_Tonga_Voltage_Lookup_Table *pVddcCACTable =
			(ATOM_Tonga_Voltage_Lookup_Table *)(((अचिन्हित दीर्घ)घातerplay_table) +
			le16_to_cpu(घातerplay_table->usVddcLookupTableOffset));

		result = get_vddc_lookup_table(hwmgr,
			&pp_table_inक्रमmation->vddc_lookup_table, pVddcCACTable, 16);
	पूर्ण

	अगर (0 != घातerplay_table->usVddgfxLookupTableOffset) अणु
		स्थिर ATOM_Tonga_Voltage_Lookup_Table *pVddgfxCACTable =
			(ATOM_Tonga_Voltage_Lookup_Table *)(((अचिन्हित दीर्घ)घातerplay_table) +
			le16_to_cpu(घातerplay_table->usVddgfxLookupTableOffset));

		result = get_vddc_lookup_table(hwmgr,
			&pp_table_inक्रमmation->vddgfx_lookup_table, pVddgfxCACTable, 16);
	पूर्ण

	disable_ppm = 0;
	अगर (0 == disable_ppm) अणु
		atom_ppm_table = (ATOM_Tonga_PPM_Table *)
			(((अचिन्हित दीर्घ)घातerplay_table) + le16_to_cpu(घातerplay_table->usPPMTableOffset));

		अगर (0 != घातerplay_table->usPPMTableOffset) अणु
			अगर (get_platक्रमm_घातer_management_table(hwmgr, atom_ppm_table) == 0) अणु
				phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_EnablePlatक्रमmPowerManagement);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक get_valid_clk(
		काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_घड़ी_array **clk_table,
		phm_ppt_v1_घड़ी_voltage_dependency_table स्थिर *clk_volt_pp_table
		)
अणु
	uपूर्णांक32_t i;
	काष्ठा phm_घड़ी_array *table;
	phm_ppt_v1_घड़ी_voltage_dependency_record *dep_record;

	PP_ASSERT_WITH_CODE((0 != clk_volt_pp_table->count),
		"Invalid PowerPlay Table!", वापस -1);

	table = kzalloc(काष्ठा_size(table, values, clk_volt_pp_table->count),
			GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	table->count = (uपूर्णांक32_t)clk_volt_pp_table->count;

	क्रम (i = 0; i < table->count; i++) अणु
		dep_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
				phm_ppt_v1_घड़ी_voltage_dependency_record,
				entries, clk_volt_pp_table, i);
		table->values[i] = (uपूर्णांक32_t)dep_record->clk;
	पूर्ण
	*clk_table = table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_hard_limits(
		काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_घड़ी_and_voltage_limits *limits,
		ATOM_Tonga_Hard_Limit_Table स्थिर *limitable
		)
अणु
	PP_ASSERT_WITH_CODE((0 != limitable->ucNumEntries), "Invalid PowerPlay Table!", वापस -1);

	/* currently we always take entries[0] parameters */
	limits->sclk = le32_to_cpu(limitable->entries[0].ulSCLKLimit);
	limits->mclk = le32_to_cpu(limitable->entries[0].ulMCLKLimit);
	limits->vddc = le16_to_cpu(limitable->entries[0].usVddcLimit);
	limits->vddci = le16_to_cpu(limitable->entries[0].usVddciLimit);
	limits->vddgfx = le16_to_cpu(limitable->entries[0].usVddgfxLimit);

	वापस 0;
पूर्ण

अटल पूर्णांक get_mclk_voltage_dependency_table(
		काष्ठा pp_hwmgr *hwmgr,
		phm_ppt_v1_घड़ी_voltage_dependency_table **pp_tonga_mclk_dep_table,
		ATOM_Tonga_MCLK_Dependency_Table स्थिर *mclk_dep_table
		)
अणु
	uपूर्णांक32_t i;
	phm_ppt_v1_घड़ी_voltage_dependency_table *mclk_table;
	phm_ppt_v1_घड़ी_voltage_dependency_record *mclk_table_record;
	ATOM_Tonga_MCLK_Dependency_Record *mclk_dep_record;

	PP_ASSERT_WITH_CODE((0 != mclk_dep_table->ucNumEntries),
		"Invalid PowerPlay Table!", वापस -1);

	mclk_table = kzalloc(काष्ठा_size(mclk_table, entries, mclk_dep_table->ucNumEntries),
			     GFP_KERNEL);
	अगर (!mclk_table)
		वापस -ENOMEM;

	mclk_table->count = (uपूर्णांक32_t)mclk_dep_table->ucNumEntries;

	क्रम (i = 0; i < mclk_dep_table->ucNumEntries; i++) अणु
		mclk_table_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
					phm_ppt_v1_घड़ी_voltage_dependency_record,
						entries, mclk_table, i);
		mclk_dep_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
					ATOM_Tonga_MCLK_Dependency_Record,
						entries, mclk_dep_table, i);
		mclk_table_record->vddInd = mclk_dep_record->ucVddcInd;
		mclk_table_record->vdd_offset = le16_to_cpu(mclk_dep_record->usVddgfxOffset);
		mclk_table_record->vddci = le16_to_cpu(mclk_dep_record->usVddci);
		mclk_table_record->mvdd = le16_to_cpu(mclk_dep_record->usMvdd);
		mclk_table_record->clk = le32_to_cpu(mclk_dep_record->ulMclk);
	पूर्ण

	*pp_tonga_mclk_dep_table = mclk_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_sclk_voltage_dependency_table(
		काष्ठा pp_hwmgr *hwmgr,
		phm_ppt_v1_घड़ी_voltage_dependency_table **pp_tonga_sclk_dep_table,
		PPTable_Generic_SubTable_Header स्थिर  *sclk_dep_table
		)
अणु
	uपूर्णांक32_t i;
	phm_ppt_v1_घड़ी_voltage_dependency_table *sclk_table;
	phm_ppt_v1_घड़ी_voltage_dependency_record *sclk_table_record;

	अगर (sclk_dep_table->ucRevId < 1) अणु
		स्थिर ATOM_Tonga_SCLK_Dependency_Table *tonga_table =
			    (ATOM_Tonga_SCLK_Dependency_Table *)sclk_dep_table;
		ATOM_Tonga_SCLK_Dependency_Record *sclk_dep_record;

		PP_ASSERT_WITH_CODE((0 != tonga_table->ucNumEntries),
			"Invalid PowerPlay Table!", वापस -1);

		sclk_table = kzalloc(काष्ठा_size(sclk_table, entries, tonga_table->ucNumEntries),
				     GFP_KERNEL);
		अगर (!sclk_table)
			वापस -ENOMEM;

		sclk_table->count = (uपूर्णांक32_t)tonga_table->ucNumEntries;

		क्रम (i = 0; i < tonga_table->ucNumEntries; i++) अणु
			sclk_dep_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
						ATOM_Tonga_SCLK_Dependency_Record,
						entries, tonga_table, i);
			sclk_table_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
						phm_ppt_v1_घड़ी_voltage_dependency_record,
						entries, sclk_table, i);
			sclk_table_record->vddInd = sclk_dep_record->ucVddInd;
			sclk_table_record->vdd_offset = le16_to_cpu(sclk_dep_record->usVddcOffset);
			sclk_table_record->clk = le32_to_cpu(sclk_dep_record->ulSclk);
			sclk_table_record->cks_enable =
				(((sclk_dep_record->ucCKSVOffsetandDisable & 0x80) >> 7) == 0) ? 1 : 0;
			sclk_table_record->cks_voffset = (sclk_dep_record->ucCKSVOffsetandDisable & 0x7F);
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर ATOM_Polaris_SCLK_Dependency_Table *polaris_table =
			    (ATOM_Polaris_SCLK_Dependency_Table *)sclk_dep_table;
		ATOM_Polaris_SCLK_Dependency_Record *sclk_dep_record;

		PP_ASSERT_WITH_CODE((0 != polaris_table->ucNumEntries),
			"Invalid PowerPlay Table!", वापस -1);

		sclk_table = kzalloc(काष्ठा_size(sclk_table, entries, polaris_table->ucNumEntries),
				     GFP_KERNEL);
		अगर (!sclk_table)
			वापस -ENOMEM;

		sclk_table->count = (uपूर्णांक32_t)polaris_table->ucNumEntries;

		क्रम (i = 0; i < polaris_table->ucNumEntries; i++) अणु
			sclk_dep_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
						ATOM_Polaris_SCLK_Dependency_Record,
						entries, polaris_table, i);
			sclk_table_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
						phm_ppt_v1_घड़ी_voltage_dependency_record,
						entries, sclk_table, i);
			sclk_table_record->vddInd = sclk_dep_record->ucVddInd;
			sclk_table_record->vdd_offset = le16_to_cpu(sclk_dep_record->usVddcOffset);
			sclk_table_record->clk = le32_to_cpu(sclk_dep_record->ulSclk);
			sclk_table_record->cks_enable =
				(((sclk_dep_record->ucCKSVOffsetandDisable & 0x80) >> 7) == 0) ? 1 : 0;
			sclk_table_record->cks_voffset = (sclk_dep_record->ucCKSVOffsetandDisable & 0x7F);
			sclk_table_record->sclk_offset = le32_to_cpu(sclk_dep_record->ulSclkOffset);
		पूर्ण
	पूर्ण
	*pp_tonga_sclk_dep_table = sclk_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_pcie_table(
		काष्ठा pp_hwmgr *hwmgr,
		phm_ppt_v1_pcie_table **pp_tonga_pcie_table,
		PPTable_Generic_SubTable_Header स्थिर *ptable
		)
अणु
	uपूर्णांक32_t i, pcie_count;
	phm_ppt_v1_pcie_table *pcie_table;
	काष्ठा phm_ppt_v1_inक्रमmation *pp_table_inक्रमmation =
		(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);
	phm_ppt_v1_pcie_record *pcie_record;

	अगर (ptable->ucRevId < 1) अणु
		स्थिर ATOM_Tonga_PCIE_Table *atom_pcie_table = (ATOM_Tonga_PCIE_Table *)ptable;
		ATOM_Tonga_PCIE_Record *atom_pcie_record;

		PP_ASSERT_WITH_CODE((atom_pcie_table->ucNumEntries != 0),
			"Invalid PowerPlay Table!", वापस -1);

		pcie_table = kzalloc(काष्ठा_size(pcie_table, entries,
						 atom_pcie_table->ucNumEntries),
				     GFP_KERNEL);
		अगर (!pcie_table)
			वापस -ENOMEM;

		/*
		* Make sure the number of pcie entries are less than or equal to sclk dpm levels.
		* Since first PCIE entry is क्रम ULV, #pcie has to be <= SclkLevel + 1.
		*/
		pcie_count = (pp_table_inक्रमmation->vdd_dep_on_sclk->count) + 1;
		अगर ((uपूर्णांक32_t)atom_pcie_table->ucNumEntries <= pcie_count)
			pcie_count = (uपूर्णांक32_t)atom_pcie_table->ucNumEntries;
		अन्यथा
			pr_err("Number of Pcie Entries exceed the number of SCLK Dpm Levels! Disregarding the excess entries...\n");

		pcie_table->count = pcie_count;
		क्रम (i = 0; i < pcie_count; i++) अणु
			pcie_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
						phm_ppt_v1_pcie_record,
						entries, pcie_table, i);
			atom_pcie_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
						ATOM_Tonga_PCIE_Record,
						entries, atom_pcie_table, i);
			pcie_record->gen_speed = atom_pcie_record->ucPCIEGenSpeed;
			pcie_record->lane_width = le16_to_cpu(atom_pcie_record->usPCIELaneWidth);
		पूर्ण

		*pp_tonga_pcie_table = pcie_table;
	पूर्ण अन्यथा अणु
		/* Polaris10/Polaris11 and newer. */
		स्थिर ATOM_Polaris10_PCIE_Table *atom_pcie_table = (ATOM_Polaris10_PCIE_Table *)ptable;
		ATOM_Polaris10_PCIE_Record *atom_pcie_record;

		PP_ASSERT_WITH_CODE((atom_pcie_table->ucNumEntries != 0),
			"Invalid PowerPlay Table!", वापस -1);

		pcie_table = kzalloc(काष्ठा_size(pcie_table, entries,
						 atom_pcie_table->ucNumEntries),
				     GFP_KERNEL);
		अगर (!pcie_table)
			वापस -ENOMEM;

		/*
		* Make sure the number of pcie entries are less than or equal to sclk dpm levels.
		* Since first PCIE entry is क्रम ULV, #pcie has to be <= SclkLevel + 1.
		*/
		pcie_count = (pp_table_inक्रमmation->vdd_dep_on_sclk->count) + 1;
		अगर ((uपूर्णांक32_t)atom_pcie_table->ucNumEntries <= pcie_count)
			pcie_count = (uपूर्णांक32_t)atom_pcie_table->ucNumEntries;
		अन्यथा
			pr_err("Number of Pcie Entries exceed the number of SCLK Dpm Levels! Disregarding the excess entries...\n");

		pcie_table->count = pcie_count;

		क्रम (i = 0; i < pcie_count; i++) अणु
			pcie_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
						phm_ppt_v1_pcie_record,
						entries, pcie_table, i);
			atom_pcie_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
						ATOM_Polaris10_PCIE_Record,
						entries, atom_pcie_table, i);
			pcie_record->gen_speed = atom_pcie_record->ucPCIEGenSpeed;
			pcie_record->lane_width = le16_to_cpu(atom_pcie_record->usPCIELaneWidth);
			pcie_record->pcie_sclk = le32_to_cpu(atom_pcie_record->ulPCIE_Sclk);
		पूर्ण

		*pp_tonga_pcie_table = pcie_table;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_cac_tdp_table(
		काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_cac_tdp_table **cac_tdp_table,
		स्थिर PPTable_Generic_SubTable_Header * table
		)
अणु
	uपूर्णांक32_t table_size;
	काष्ठा phm_cac_tdp_table *tdp_table;

	table_size = माप(uपूर्णांक32_t) + माप(काष्ठा phm_cac_tdp_table);
	tdp_table = kzalloc(table_size, GFP_KERNEL);

	अगर (शून्य == tdp_table)
		वापस -ENOMEM;

	hwmgr->dyn_state.cac_dtp_table = kzalloc(table_size, GFP_KERNEL);

	अगर (शून्य == hwmgr->dyn_state.cac_dtp_table) अणु
		kमुक्त(tdp_table);
		वापस -ENOMEM;
	पूर्ण

	अगर (table->ucRevId < 3) अणु
		स्थिर ATOM_Tonga_PowerTune_Table *tonga_table =
			(ATOM_Tonga_PowerTune_Table *)table;
		tdp_table->usTDP = le16_to_cpu(tonga_table->usTDP);
		tdp_table->usConfigurableTDP =
			le16_to_cpu(tonga_table->usConfigurableTDP);
		tdp_table->usTDC = le16_to_cpu(tonga_table->usTDC);
		tdp_table->usBatteryPowerLimit =
			le16_to_cpu(tonga_table->usBatteryPowerLimit);
		tdp_table->usSmallPowerLimit =
			le16_to_cpu(tonga_table->usSmallPowerLimit);
		tdp_table->usLowCACLeakage =
			le16_to_cpu(tonga_table->usLowCACLeakage);
		tdp_table->usHighCACLeakage =
			le16_to_cpu(tonga_table->usHighCACLeakage);
		tdp_table->usMaximumPowerDeliveryLimit =
			le16_to_cpu(tonga_table->usMaximumPowerDeliveryLimit);
		tdp_table->usDefaultTargetOperatingTemp =
			le16_to_cpu(tonga_table->usTjMax);
		tdp_table->usTargetOperatingTemp =
			le16_to_cpu(tonga_table->usTjMax); /*Set the initial temp to the same as शेष */
		tdp_table->usPowerTuneDataSetID =
			le16_to_cpu(tonga_table->usPowerTuneDataSetID);
		tdp_table->usSoftwareShutकरोwnTemp =
			le16_to_cpu(tonga_table->usSoftwareShutकरोwnTemp);
		tdp_table->usClockStretchAmount =
			le16_to_cpu(tonga_table->usClockStretchAmount);
	पूर्ण अन्यथा अगर (table->ucRevId < 4) अणु   /* Fiji and newer */
		स्थिर ATOM_Fiji_PowerTune_Table *fijitable =
			(ATOM_Fiji_PowerTune_Table *)table;
		tdp_table->usTDP = le16_to_cpu(fijitable->usTDP);
		tdp_table->usConfigurableTDP = le16_to_cpu(fijitable->usConfigurableTDP);
		tdp_table->usTDC = le16_to_cpu(fijitable->usTDC);
		tdp_table->usBatteryPowerLimit = le16_to_cpu(fijitable->usBatteryPowerLimit);
		tdp_table->usSmallPowerLimit = le16_to_cpu(fijitable->usSmallPowerLimit);
		tdp_table->usLowCACLeakage = le16_to_cpu(fijitable->usLowCACLeakage);
		tdp_table->usHighCACLeakage = le16_to_cpu(fijitable->usHighCACLeakage);
		tdp_table->usMaximumPowerDeliveryLimit =
			le16_to_cpu(fijitable->usMaximumPowerDeliveryLimit);
		tdp_table->usDefaultTargetOperatingTemp =
			le16_to_cpu(fijitable->usTjMax);
		tdp_table->usTargetOperatingTemp =
			le16_to_cpu(fijitable->usTjMax); /*Set the initial temp to the same as शेष */
		tdp_table->usPowerTuneDataSetID =
			le16_to_cpu(fijitable->usPowerTuneDataSetID);
		tdp_table->usSoftwareShutकरोwnTemp =
			le16_to_cpu(fijitable->usSoftwareShutकरोwnTemp);
		tdp_table->usClockStretchAmount =
			le16_to_cpu(fijitable->usClockStretchAmount);
		tdp_table->usTemperatureLimitHotspot =
			le16_to_cpu(fijitable->usTemperatureLimitHotspot);
		tdp_table->usTemperatureLimitLiquid1 =
			le16_to_cpu(fijitable->usTemperatureLimitLiquid1);
		tdp_table->usTemperatureLimitLiquid2 =
			le16_to_cpu(fijitable->usTemperatureLimitLiquid2);
		tdp_table->usTemperatureLimitVrVddc =
			le16_to_cpu(fijitable->usTemperatureLimitVrVddc);
		tdp_table->usTemperatureLimitVrMvdd =
			le16_to_cpu(fijitable->usTemperatureLimitVrMvdd);
		tdp_table->usTemperatureLimitPlx =
			le16_to_cpu(fijitable->usTemperatureLimitPlx);
		tdp_table->ucLiquid1_I2C_address =
			fijitable->ucLiquid1_I2C_address;
		tdp_table->ucLiquid2_I2C_address =
			fijitable->ucLiquid2_I2C_address;
		tdp_table->ucLiquid_I2C_Line =
			fijitable->ucLiquid_I2C_Line;
		tdp_table->ucVr_I2C_address = fijitable->ucVr_I2C_address;
		tdp_table->ucVr_I2C_Line = fijitable->ucVr_I2C_Line;
		tdp_table->ucPlx_I2C_address = fijitable->ucPlx_I2C_address;
		tdp_table->ucPlx_I2C_Line = fijitable->ucPlx_I2C_Line;
	पूर्ण अन्यथा अणु
		स्थिर ATOM_Polaris_PowerTune_Table *polaristable =
			(ATOM_Polaris_PowerTune_Table *)table;
		tdp_table->usTDP = le16_to_cpu(polaristable->usTDP);
		tdp_table->usConfigurableTDP = le16_to_cpu(polaristable->usConfigurableTDP);
		tdp_table->usTDC = le16_to_cpu(polaristable->usTDC);
		tdp_table->usBatteryPowerLimit = le16_to_cpu(polaristable->usBatteryPowerLimit);
		tdp_table->usSmallPowerLimit = le16_to_cpu(polaristable->usSmallPowerLimit);
		tdp_table->usLowCACLeakage = le16_to_cpu(polaristable->usLowCACLeakage);
		tdp_table->usHighCACLeakage = le16_to_cpu(polaristable->usHighCACLeakage);
		tdp_table->usMaximumPowerDeliveryLimit =
			le16_to_cpu(polaristable->usMaximumPowerDeliveryLimit);
		tdp_table->usDefaultTargetOperatingTemp =
			le16_to_cpu(polaristable->usTjMax);
		tdp_table->usTargetOperatingTemp =
			le16_to_cpu(polaristable->usTjMax); /*Set the initial temp to the same as शेष */
		tdp_table->usPowerTuneDataSetID =
			le16_to_cpu(polaristable->usPowerTuneDataSetID);
		tdp_table->usSoftwareShutकरोwnTemp =
			le16_to_cpu(polaristable->usSoftwareShutकरोwnTemp);
		tdp_table->usClockStretchAmount =
			le16_to_cpu(polaristable->usClockStretchAmount);
		tdp_table->usTemperatureLimitHotspot =
			le16_to_cpu(polaristable->usTemperatureLimitHotspot);
		tdp_table->usTemperatureLimitLiquid1 =
			le16_to_cpu(polaristable->usTemperatureLimitLiquid1);
		tdp_table->usTemperatureLimitLiquid2 =
			le16_to_cpu(polaristable->usTemperatureLimitLiquid2);
		tdp_table->usTemperatureLimitVrVddc =
			le16_to_cpu(polaristable->usTemperatureLimitVrVddc);
		tdp_table->usTemperatureLimitVrMvdd =
			le16_to_cpu(polaristable->usTemperatureLimitVrMvdd);
		tdp_table->usTemperatureLimitPlx =
			le16_to_cpu(polaristable->usTemperatureLimitPlx);
		tdp_table->ucLiquid1_I2C_address =
			polaristable->ucLiquid1_I2C_address;
		tdp_table->ucLiquid2_I2C_address =
			polaristable->ucLiquid2_I2C_address;
		tdp_table->ucLiquid_I2C_Line =
			polaristable->ucLiquid_I2C_Line;
		tdp_table->ucVr_I2C_address = polaristable->ucVr_I2C_address;
		tdp_table->ucVr_I2C_Line = polaristable->ucVr_I2C_Line;
		tdp_table->ucPlx_I2C_address = polaristable->ucPlx_I2C_address;
		tdp_table->ucPlx_I2C_Line = polaristable->ucPlx_I2C_Line;
		tdp_table->usBoostPowerLimit = polaristable->usBoostPowerLimit;
		tdp_table->ucCKS_LDO_REFSEL = polaristable->ucCKS_LDO_REFSEL;
		tdp_table->ucHotSpotOnly = polaristable->ucHotSpotOnly;
	पूर्ण

	*cac_tdp_table = tdp_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_mm_घड़ी_voltage_table(
		काष्ठा pp_hwmgr *hwmgr,
		phm_ppt_v1_mm_घड़ी_voltage_dependency_table **tonga_mm_table,
		स्थिर ATOM_Tonga_MM_Dependency_Table * mm_dependency_table
		)
अणु
	uपूर्णांक32_t i;
	स्थिर ATOM_Tonga_MM_Dependency_Record *mm_dependency_record;
	phm_ppt_v1_mm_घड़ी_voltage_dependency_table *mm_table;
	phm_ppt_v1_mm_घड़ी_voltage_dependency_record *mm_table_record;

	PP_ASSERT_WITH_CODE((0 != mm_dependency_table->ucNumEntries),
		"Invalid PowerPlay Table!", वापस -1);
	mm_table = kzalloc(काष्ठा_size(mm_table, entries, mm_dependency_table->ucNumEntries),
			   GFP_KERNEL);
	अगर (!mm_table)
		वापस -ENOMEM;

	mm_table->count = mm_dependency_table->ucNumEntries;

	क्रम (i = 0; i < mm_dependency_table->ucNumEntries; i++) अणु
		mm_dependency_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
						ATOM_Tonga_MM_Dependency_Record,
						entries, mm_dependency_table, i);
		mm_table_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
					phm_ppt_v1_mm_घड़ी_voltage_dependency_record,
					entries, mm_table, i);
		mm_table_record->vddcInd = mm_dependency_record->ucVddcInd;
		mm_table_record->vddgfx_offset = le16_to_cpu(mm_dependency_record->usVddgfxOffset);
		mm_table_record->aclk = le32_to_cpu(mm_dependency_record->ulAClk);
		mm_table_record->samघड़ी = le32_to_cpu(mm_dependency_record->ulSAMUClk);
		mm_table_record->eclk = le32_to_cpu(mm_dependency_record->ulEClk);
		mm_table_record->vclk = le32_to_cpu(mm_dependency_record->ulVClk);
		mm_table_record->dclk = le32_to_cpu(mm_dependency_record->ulDClk);
	पूर्ण

	*tonga_mm_table = mm_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_gpio_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_ppt_v1_gpio_table **pp_tonga_gpio_table,
		स्थिर ATOM_Tonga_GPIO_Table *atom_gpio_table)
अणु
	uपूर्णांक32_t table_size;
	काष्ठा phm_ppt_v1_gpio_table *pp_gpio_table;
	काष्ठा phm_ppt_v1_inक्रमmation *pp_table_inक्रमmation =
			(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	table_size = माप(काष्ठा phm_ppt_v1_gpio_table);
	pp_gpio_table = kzalloc(table_size, GFP_KERNEL);
	अगर (!pp_gpio_table)
		वापस -ENOMEM;

	अगर (pp_table_inक्रमmation->vdd_dep_on_sclk->count <
			atom_gpio_table->ucVRHotTriggeredSclkDpmIndex)
		PP_ASSERT_WITH_CODE(false,
				"SCLK DPM index for VRHot cannot exceed the total sclk level count!",);
	अन्यथा
		pp_gpio_table->vrhot_triggered_sclk_dpm_index =
				atom_gpio_table->ucVRHotTriggeredSclkDpmIndex;

	*pp_tonga_gpio_table = pp_gpio_table;

	वापस 0;
पूर्ण
/**
 * init_घड़ी_voltage_dependency - Private Function used during initialization.
 * Initialize घड़ी voltage dependency
 * @hwmgr: Poपूर्णांकer to the hardware manager.
 * @घातerplay_table: Poपूर्णांकer to the PowerPlay Table.
 */
अटल पूर्णांक init_घड़ी_voltage_dependency(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर ATOM_Tonga_POWERPLAYTABLE *घातerplay_table
		)
अणु
	पूर्णांक result = 0;
	काष्ठा phm_ppt_v1_inक्रमmation *pp_table_inक्रमmation =
		(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	स्थिर ATOM_Tonga_MM_Dependency_Table *mm_dependency_table =
		(स्थिर ATOM_Tonga_MM_Dependency_Table *)(((अचिन्हित दीर्घ) घातerplay_table) +
		le16_to_cpu(घातerplay_table->usMMDependencyTableOffset));
	स्थिर PPTable_Generic_SubTable_Header *pPowerTuneTable =
		(स्थिर PPTable_Generic_SubTable_Header *)(((अचिन्हित दीर्घ) घातerplay_table) +
		le16_to_cpu(घातerplay_table->usPowerTuneTableOffset));
	स्थिर ATOM_Tonga_MCLK_Dependency_Table *mclk_dep_table =
		(स्थिर ATOM_Tonga_MCLK_Dependency_Table *)(((अचिन्हित दीर्घ) घातerplay_table) +
		le16_to_cpu(घातerplay_table->usMclkDependencyTableOffset));
	स्थिर PPTable_Generic_SubTable_Header *sclk_dep_table =
		(स्थिर PPTable_Generic_SubTable_Header *)(((अचिन्हित दीर्घ) घातerplay_table) +
		le16_to_cpu(घातerplay_table->usSclkDependencyTableOffset));
	स्थिर ATOM_Tonga_Hard_Limit_Table *pHardLimits =
		(स्थिर ATOM_Tonga_Hard_Limit_Table *)(((अचिन्हित दीर्घ) घातerplay_table) +
		le16_to_cpu(घातerplay_table->usHardLimitTableOffset));
	स्थिर PPTable_Generic_SubTable_Header *pcie_table =
		(स्थिर PPTable_Generic_SubTable_Header *)(((अचिन्हित दीर्घ) घातerplay_table) +
		le16_to_cpu(घातerplay_table->usPCIETableOffset));
	स्थिर ATOM_Tonga_GPIO_Table *gpio_table =
		(स्थिर ATOM_Tonga_GPIO_Table *)(((अचिन्हित दीर्घ) घातerplay_table) +
		le16_to_cpu(घातerplay_table->usGPIOTableOffset));

	pp_table_inक्रमmation->vdd_dep_on_sclk = शून्य;
	pp_table_inक्रमmation->vdd_dep_on_mclk = शून्य;
	pp_table_inक्रमmation->mm_dep_table = शून्य;
	pp_table_inक्रमmation->pcie_table = शून्य;
	pp_table_inक्रमmation->gpio_table = शून्य;

	अगर (घातerplay_table->usMMDependencyTableOffset != 0)
		result = get_mm_घड़ी_voltage_table(hwmgr,
		&pp_table_inक्रमmation->mm_dep_table, mm_dependency_table);

	अगर (result == 0 && घातerplay_table->usPowerTuneTableOffset != 0)
		result = get_cac_tdp_table(hwmgr,
		&pp_table_inक्रमmation->cac_dtp_table, pPowerTuneTable);

	अगर (result == 0 && घातerplay_table->usSclkDependencyTableOffset != 0)
		result = get_sclk_voltage_dependency_table(hwmgr,
		&pp_table_inक्रमmation->vdd_dep_on_sclk, sclk_dep_table);

	अगर (result == 0 && घातerplay_table->usMclkDependencyTableOffset != 0)
		result = get_mclk_voltage_dependency_table(hwmgr,
		&pp_table_inक्रमmation->vdd_dep_on_mclk, mclk_dep_table);

	अगर (result == 0 && घातerplay_table->usPCIETableOffset != 0)
		result = get_pcie_table(hwmgr,
		&pp_table_inक्रमmation->pcie_table, pcie_table);

	अगर (result == 0 && घातerplay_table->usHardLimitTableOffset != 0)
		result = get_hard_limits(hwmgr,
		&pp_table_inक्रमmation->max_घड़ी_voltage_on_dc, pHardLimits);

	hwmgr->dyn_state.max_घड़ी_voltage_on_dc.sclk =
		pp_table_inक्रमmation->max_घड़ी_voltage_on_dc.sclk;
	hwmgr->dyn_state.max_घड़ी_voltage_on_dc.mclk =
		pp_table_inक्रमmation->max_घड़ी_voltage_on_dc.mclk;
	hwmgr->dyn_state.max_घड़ी_voltage_on_dc.vddc =
		pp_table_inक्रमmation->max_घड़ी_voltage_on_dc.vddc;
	hwmgr->dyn_state.max_घड़ी_voltage_on_dc.vddci =
		pp_table_inक्रमmation->max_घड़ी_voltage_on_dc.vddci;

	अगर (result == 0 && (शून्य != pp_table_inक्रमmation->vdd_dep_on_mclk)
		&& (0 != pp_table_inक्रमmation->vdd_dep_on_mclk->count))
		result = get_valid_clk(hwmgr, &pp_table_inक्रमmation->valid_mclk_values,
		pp_table_inक्रमmation->vdd_dep_on_mclk);

	अगर (result == 0 && (शून्य != pp_table_inक्रमmation->vdd_dep_on_sclk)
		&& (0 != pp_table_inक्रमmation->vdd_dep_on_sclk->count))
		result = get_valid_clk(hwmgr, &pp_table_inक्रमmation->valid_sclk_values,
		pp_table_inक्रमmation->vdd_dep_on_sclk);

	अगर (!result && gpio_table)
		result = get_gpio_table(hwmgr, &pp_table_inक्रमmation->gpio_table,
				gpio_table);

	वापस result;
पूर्ण

/**
 * init_over_drive_limits - Retrieves the (चिन्हित) Overdrive limits from VBIOS.
 * The max engine घड़ी, memory घड़ी and max temperature come from the firmware info table.
 *
 * The inक्रमmation is placed पूर्णांकo the platक्रमm descriptor.
 *
 * @hwmgr: source of the VBIOS table and owner of the platक्रमm descriptor to be updated.
 * @घातerplay_table: the address of the PowerPlay table.
 *
 * Return: 1 as दीर्घ as the firmware info table was present and of a supported version.
 */
अटल पूर्णांक init_over_drive_limits(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर ATOM_Tonga_POWERPLAYTABLE *घातerplay_table)
अणु
	hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock =
		le32_to_cpu(घातerplay_table->ulMaxODEngineClock);
	hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock =
		le32_to_cpu(घातerplay_table->ulMaxODMemoryClock);

	hwmgr->platक्रमm_descriptor.minOverdriveVDDC = 0;
	hwmgr->platक्रमm_descriptor.maxOverdriveVDDC = 0;
	hwmgr->platक्रमm_descriptor.overdriveVDDCStep = 0;

	वापस 0;
पूर्ण

/**
 * init_thermal_controller - Private Function used during initialization.
 * Inspect the PowerPlay table क्रम obvious signs of corruption.
 * @hwmgr: Poपूर्णांकer to the hardware manager.
 * @घातerplay_table: Poपूर्णांकer to the PowerPlay Table.
 * Exception:  This implementation always वापसs 1.
 */
अटल पूर्णांक init_thermal_controller(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर ATOM_Tonga_POWERPLAYTABLE *घातerplay_table
		)
अणु
	स्थिर PPTable_Generic_SubTable_Header *fan_table;
	ATOM_Tonga_Thermal_Controller *thermal_controller;

	thermal_controller = (ATOM_Tonga_Thermal_Controller *)
		(((अचिन्हित दीर्घ)घातerplay_table) +
		le16_to_cpu(घातerplay_table->usThermalControllerOffset));
	PP_ASSERT_WITH_CODE((0 != घातerplay_table->usThermalControllerOffset),
		"Thermal controller table not set!", वापस -1);

	hwmgr->thermal_controller.ucType = thermal_controller->ucType;
	hwmgr->thermal_controller.ucI2cLine = thermal_controller->ucI2cLine;
	hwmgr->thermal_controller.ucI2cAddress = thermal_controller->ucI2cAddress;

	hwmgr->thermal_controller.fanInfo.bNoFan =
		(0 != (thermal_controller->ucFanParameters & ATOM_TONGA_PP_FANPARAMETERS_NOFAN));

	hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution =
		thermal_controller->ucFanParameters &
		ATOM_TONGA_PP_FANPARAMETERS_TACHOMETER_PULSES_PER_REVOLUTION_MASK;

	hwmgr->thermal_controller.fanInfo.ulMinRPM
		= thermal_controller->ucFanMinRPM * 100UL;
	hwmgr->thermal_controller.fanInfo.ulMaxRPM
		= thermal_controller->ucFanMaxRPM * 100UL;

	set_hw_cap(
			hwmgr,
			ATOM_TONGA_PP_THERMALCONTROLLER_NONE != hwmgr->thermal_controller.ucType,
			PHM_Platक्रमmCaps_ThermalController
		  );

	अगर (0 == घातerplay_table->usFanTableOffset) अणु
		hwmgr->thermal_controller.use_hw_fan_control = 1;
		वापस 0;
	पूर्ण

	fan_table = (स्थिर PPTable_Generic_SubTable_Header *)
		(((अचिन्हित दीर्घ)घातerplay_table) +
		le16_to_cpu(घातerplay_table->usFanTableOffset));

	PP_ASSERT_WITH_CODE((0 != घातerplay_table->usFanTableOffset),
		"Fan table not set!", वापस -1);
	PP_ASSERT_WITH_CODE((0 < fan_table->ucRevId),
		"Unsupported fan table format!", वापस -1);

	hwmgr->thermal_controller.advanceFanControlParameters.ulCycleDelay
		= 100000;
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
		PHM_Platक्रमmCaps_MicrocodeFanControl);

	अगर (fan_table->ucRevId < 8) अणु
		स्थिर ATOM_Tonga_Fan_Table *tonga_fan_table =
			(ATOM_Tonga_Fan_Table *)fan_table;
		hwmgr->thermal_controller.advanceFanControlParameters.ucTHyst
			= tonga_fan_table->ucTHyst;
		hwmgr->thermal_controller.advanceFanControlParameters.usTMin
			= le16_to_cpu(tonga_fan_table->usTMin);
		hwmgr->thermal_controller.advanceFanControlParameters.usTMed
			= le16_to_cpu(tonga_fan_table->usTMed);
		hwmgr->thermal_controller.advanceFanControlParameters.usTHigh
			= le16_to_cpu(tonga_fan_table->usTHigh);
		hwmgr->thermal_controller.advanceFanControlParameters.usPWMMin
			= le16_to_cpu(tonga_fan_table->usPWMMin);
		hwmgr->thermal_controller.advanceFanControlParameters.usPWMMed
			= le16_to_cpu(tonga_fan_table->usPWMMed);
		hwmgr->thermal_controller.advanceFanControlParameters.usPWMHigh
			= le16_to_cpu(tonga_fan_table->usPWMHigh);
		hwmgr->thermal_controller.advanceFanControlParameters.usTMax
			= 10900;                  /* hard coded */
		hwmgr->thermal_controller.advanceFanControlParameters.usTMax
			= le16_to_cpu(tonga_fan_table->usTMax);
		hwmgr->thermal_controller.advanceFanControlParameters.ucFanControlMode
			= tonga_fan_table->ucFanControlMode;
		hwmgr->thermal_controller.advanceFanControlParameters.usDefaultMaxFanPWM
			= le16_to_cpu(tonga_fan_table->usFanPWMMax);
		hwmgr->thermal_controller.advanceFanControlParameters.usDefaultFanOutputSensitivity
			= 4836;
		hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity
			= le16_to_cpu(tonga_fan_table->usFanOutputSensitivity);
		hwmgr->thermal_controller.advanceFanControlParameters.usDefaultMaxFanRPM
			= le16_to_cpu(tonga_fan_table->usFanRPMMax);
		hwmgr->thermal_controller.advanceFanControlParameters.ulMinFanSCLKAcousticLimit
			= (le32_to_cpu(tonga_fan_table->ulMinFanSCLKAcousticLimit) / 100); /* PPTable stores it in 10Khz unit क्रम 2 decimal places.  SMC wants MHz. */
		hwmgr->thermal_controller.advanceFanControlParameters.ucTargetTemperature
			= tonga_fan_table->ucTargetTemperature;
		hwmgr->thermal_controller.advanceFanControlParameters.ucMinimumPWMLimit
			= tonga_fan_table->ucMinimumPWMLimit;
	पूर्ण अन्यथा अगर (fan_table->ucRevId == 8) अणु
		स्थिर ATOM_Fiji_Fan_Table *fiji_fan_table =
			(ATOM_Fiji_Fan_Table *)fan_table;
		hwmgr->thermal_controller.advanceFanControlParameters.ucTHyst
			= fiji_fan_table->ucTHyst;
		hwmgr->thermal_controller.advanceFanControlParameters.usTMin
			= le16_to_cpu(fiji_fan_table->usTMin);
		hwmgr->thermal_controller.advanceFanControlParameters.usTMed
			= le16_to_cpu(fiji_fan_table->usTMed);
		hwmgr->thermal_controller.advanceFanControlParameters.usTHigh
			= le16_to_cpu(fiji_fan_table->usTHigh);
		hwmgr->thermal_controller.advanceFanControlParameters.usPWMMin
			= le16_to_cpu(fiji_fan_table->usPWMMin);
		hwmgr->thermal_controller.advanceFanControlParameters.usPWMMed
			= le16_to_cpu(fiji_fan_table->usPWMMed);
		hwmgr->thermal_controller.advanceFanControlParameters.usPWMHigh
			= le16_to_cpu(fiji_fan_table->usPWMHigh);
		hwmgr->thermal_controller.advanceFanControlParameters.usTMax
			= le16_to_cpu(fiji_fan_table->usTMax);
		hwmgr->thermal_controller.advanceFanControlParameters.ucFanControlMode
			= fiji_fan_table->ucFanControlMode;
		hwmgr->thermal_controller.advanceFanControlParameters.usDefaultMaxFanPWM
			= le16_to_cpu(fiji_fan_table->usFanPWMMax);
		hwmgr->thermal_controller.advanceFanControlParameters.usDefaultFanOutputSensitivity
			= 4836;
		hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity
			= le16_to_cpu(fiji_fan_table->usFanOutputSensitivity);
		hwmgr->thermal_controller.advanceFanControlParameters.usDefaultMaxFanRPM
			= le16_to_cpu(fiji_fan_table->usFanRPMMax);
		hwmgr->thermal_controller.advanceFanControlParameters.ulMinFanSCLKAcousticLimit
			= (le32_to_cpu(fiji_fan_table->ulMinFanSCLKAcousticLimit) / 100); /* PPTable stores it in 10Khz unit क्रम 2 decimal places.  SMC wants MHz. */
		hwmgr->thermal_controller.advanceFanControlParameters.ucTargetTemperature
			= fiji_fan_table->ucTargetTemperature;
		hwmgr->thermal_controller.advanceFanControlParameters.ucMinimumPWMLimit
			= fiji_fan_table->ucMinimumPWMLimit;

		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainEdge
			= le16_to_cpu(fiji_fan_table->usFanGainEdge);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainHotspot
			= le16_to_cpu(fiji_fan_table->usFanGainHotspot);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainLiquid
			= le16_to_cpu(fiji_fan_table->usFanGainLiquid);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainVrVddc
			= le16_to_cpu(fiji_fan_table->usFanGainVrVddc);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainVrMvdd
			= le16_to_cpu(fiji_fan_table->usFanGainVrMvdd);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainPlx
			= le16_to_cpu(fiji_fan_table->usFanGainPlx);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainHbm
			= le16_to_cpu(fiji_fan_table->usFanGainHbm);
	पूर्ण अन्यथा अगर (fan_table->ucRevId >= 9) अणु
		स्थिर ATOM_Polaris_Fan_Table *polaris_fan_table =
			(ATOM_Polaris_Fan_Table *)fan_table;
		hwmgr->thermal_controller.advanceFanControlParameters.ucTHyst
			= polaris_fan_table->ucTHyst;
		hwmgr->thermal_controller.advanceFanControlParameters.usTMin
			= le16_to_cpu(polaris_fan_table->usTMin);
		hwmgr->thermal_controller.advanceFanControlParameters.usTMed
			= le16_to_cpu(polaris_fan_table->usTMed);
		hwmgr->thermal_controller.advanceFanControlParameters.usTHigh
			= le16_to_cpu(polaris_fan_table->usTHigh);
		hwmgr->thermal_controller.advanceFanControlParameters.usPWMMin
			= le16_to_cpu(polaris_fan_table->usPWMMin);
		hwmgr->thermal_controller.advanceFanControlParameters.usPWMMed
			= le16_to_cpu(polaris_fan_table->usPWMMed);
		hwmgr->thermal_controller.advanceFanControlParameters.usPWMHigh
			= le16_to_cpu(polaris_fan_table->usPWMHigh);
		hwmgr->thermal_controller.advanceFanControlParameters.usTMax
			= le16_to_cpu(polaris_fan_table->usTMax);
		hwmgr->thermal_controller.advanceFanControlParameters.ucFanControlMode
			= polaris_fan_table->ucFanControlMode;
		hwmgr->thermal_controller.advanceFanControlParameters.usDefaultMaxFanPWM
			= le16_to_cpu(polaris_fan_table->usFanPWMMax);
		hwmgr->thermal_controller.advanceFanControlParameters.usDefaultFanOutputSensitivity
			= 4836;
		hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity
			= le16_to_cpu(polaris_fan_table->usFanOutputSensitivity);
		hwmgr->thermal_controller.advanceFanControlParameters.usDefaultMaxFanRPM
			= le16_to_cpu(polaris_fan_table->usFanRPMMax);
		hwmgr->thermal_controller.advanceFanControlParameters.ulMinFanSCLKAcousticLimit
			= (le32_to_cpu(polaris_fan_table->ulMinFanSCLKAcousticLimit) / 100); /* PPTable stores it in 10Khz unit क्रम 2 decimal places.  SMC wants MHz. */
		hwmgr->thermal_controller.advanceFanControlParameters.ucTargetTemperature
			= polaris_fan_table->ucTargetTemperature;
		hwmgr->thermal_controller.advanceFanControlParameters.ucMinimumPWMLimit
			= polaris_fan_table->ucMinimumPWMLimit;

		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainEdge
			= le16_to_cpu(polaris_fan_table->usFanGainEdge);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainHotspot
			= le16_to_cpu(polaris_fan_table->usFanGainHotspot);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainLiquid
			= le16_to_cpu(polaris_fan_table->usFanGainLiquid);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainVrVddc
			= le16_to_cpu(polaris_fan_table->usFanGainVrVddc);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainVrMvdd
			= le16_to_cpu(polaris_fan_table->usFanGainVrMvdd);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainPlx
			= le16_to_cpu(polaris_fan_table->usFanGainPlx);
		hwmgr->thermal_controller.advanceFanControlParameters.usFanGainHbm
			= le16_to_cpu(polaris_fan_table->usFanGainHbm);
		hwmgr->thermal_controller.advanceFanControlParameters.ucEnableZeroRPM
			= le16_to_cpu(polaris_fan_table->ucEnableZeroRPM);
		hwmgr->thermal_controller.advanceFanControlParameters.ucFanStopTemperature
			= le16_to_cpu(polaris_fan_table->ucFanStopTemperature);
		hwmgr->thermal_controller.advanceFanControlParameters.ucFanStartTemperature
			= le16_to_cpu(polaris_fan_table->ucFanStartTemperature);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * check_घातerplay_tables - Private Function used during initialization.
 * Inspect the PowerPlay table क्रम obvious signs of corruption.
 * @hwmgr: Poपूर्णांकer to the hardware manager.
 * @घातerplay_table: Poपूर्णांकer to the PowerPlay Table.
 * Exception:  2 अगर the घातerplay table is incorrect.
 */
अटल पूर्णांक check_घातerplay_tables(
		काष्ठा pp_hwmgr *hwmgr,
		स्थिर ATOM_Tonga_POWERPLAYTABLE *घातerplay_table
		)
अणु
	स्थिर ATOM_Tonga_State_Array *state_arrays;

	state_arrays = (ATOM_Tonga_State_Array *)(((अचिन्हित दीर्घ)घातerplay_table) +
		le16_to_cpu(घातerplay_table->usStateArrayOffset));

	PP_ASSERT_WITH_CODE((ATOM_Tonga_TABLE_REVISION_TONGA <=
		घातerplay_table->sHeader.ucTableFormatRevision),
		"Unsupported PPTable format!", वापस -1);
	PP_ASSERT_WITH_CODE((0 != घातerplay_table->usStateArrayOffset),
		"State table is not set!", वापस -1);
	PP_ASSERT_WITH_CODE((0 < घातerplay_table->sHeader.usStructureSize),
		"Invalid PowerPlay Table!", वापस -1);
	PP_ASSERT_WITH_CODE((0 < state_arrays->ucNumEntries),
		"Invalid PowerPlay Table!", वापस -1);

	वापस 0;
पूर्ण

अटल पूर्णांक pp_tables_v1_0_initialize(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	स्थिर ATOM_Tonga_POWERPLAYTABLE *घातerplay_table;

	hwmgr->pptable = kzalloc(माप(काष्ठा phm_ppt_v1_inक्रमmation), GFP_KERNEL);

	PP_ASSERT_WITH_CODE((शून्य != hwmgr->pptable),
			    "Failed to allocate hwmgr->pptable!", वापस -ENOMEM);

	घातerplay_table = get_घातerplay_table(hwmgr);

	PP_ASSERT_WITH_CODE((शून्य != घातerplay_table),
		"Missing PowerPlay Table!", वापस -1);

	result = check_घातerplay_tables(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "check_powerplay_tables failed", वापस result);

	result = set_platक्रमm_caps(hwmgr,
				   le32_to_cpu(घातerplay_table->ulPlatक्रमmCaps));

	PP_ASSERT_WITH_CODE((result == 0),
			    "set_platform_caps failed", वापस result);

	result = init_thermal_controller(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_thermal_controller failed", वापस result);

	result = init_over_drive_limits(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_over_drive_limits failed", वापस result);

	result = init_घड़ी_voltage_dependency(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_clock_voltage_dependency failed", वापस result);

	result = init_dpm_2_parameters(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_dpm_2_parameters failed", वापस result);

	वापस result;
पूर्ण

अटल पूर्णांक pp_tables_v1_0_uninitialize(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा phm_ppt_v1_inक्रमmation *pp_table_inक्रमmation =
		(काष्ठा phm_ppt_v1_inक्रमmation *)(hwmgr->pptable);

	kमुक्त(pp_table_inक्रमmation->vdd_dep_on_sclk);
	pp_table_inक्रमmation->vdd_dep_on_sclk = शून्य;

	kमुक्त(pp_table_inक्रमmation->vdd_dep_on_mclk);
	pp_table_inक्रमmation->vdd_dep_on_mclk = शून्य;

	kमुक्त(pp_table_inक्रमmation->valid_mclk_values);
	pp_table_inक्रमmation->valid_mclk_values = शून्य;

	kमुक्त(pp_table_inक्रमmation->valid_sclk_values);
	pp_table_inक्रमmation->valid_sclk_values = शून्य;

	kमुक्त(pp_table_inक्रमmation->vddc_lookup_table);
	pp_table_inक्रमmation->vddc_lookup_table = शून्य;

	kमुक्त(pp_table_inक्रमmation->vddgfx_lookup_table);
	pp_table_inक्रमmation->vddgfx_lookup_table = शून्य;

	kमुक्त(pp_table_inक्रमmation->mm_dep_table);
	pp_table_inक्रमmation->mm_dep_table = शून्य;

	kमुक्त(pp_table_inक्रमmation->cac_dtp_table);
	pp_table_inक्रमmation->cac_dtp_table = शून्य;

	kमुक्त(hwmgr->dyn_state.cac_dtp_table);
	hwmgr->dyn_state.cac_dtp_table = शून्य;

	kमुक्त(pp_table_inक्रमmation->ppm_parameter_table);
	pp_table_inक्रमmation->ppm_parameter_table = शून्य;

	kमुक्त(pp_table_inक्रमmation->pcie_table);
	pp_table_inक्रमmation->pcie_table = शून्य;

	kमुक्त(pp_table_inक्रमmation->gpio_table);
	pp_table_inक्रमmation->gpio_table = शून्य;

	kमुक्त(hwmgr->pptable);
	hwmgr->pptable = शून्य;

	वापस 0;
पूर्ण

स्थिर काष्ठा pp_table_func pptable_v1_0_funcs = अणु
	.pptable_init = pp_tables_v1_0_initialize,
	.pptable_fini = pp_tables_v1_0_uninitialize,
पूर्ण;

पूर्णांक get_number_of_घातerplay_table_entries_v1_0(काष्ठा pp_hwmgr *hwmgr)
अणु
	ATOM_Tonga_State_Array स्थिर *state_arrays;
	स्थिर ATOM_Tonga_POWERPLAYTABLE *pp_table = get_घातerplay_table(hwmgr);

	PP_ASSERT_WITH_CODE((शून्य != pp_table),
			"Missing PowerPlay Table!", वापस -1);
	PP_ASSERT_WITH_CODE((pp_table->sHeader.ucTableFormatRevision >=
			ATOM_Tonga_TABLE_REVISION_TONGA),
			"Incorrect PowerPlay table revision!", वापस -1);

	state_arrays = (ATOM_Tonga_State_Array *)(((अचिन्हित दीर्घ)pp_table) +
			le16_to_cpu(pp_table->usStateArrayOffset));

	वापस (uपूर्णांक32_t)(state_arrays->ucNumEntries);
पूर्ण

/*
 * Private function to convert flags stored in the BIOS to software flags in PowerPlay.
 */
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

अटल पूर्णांक ppt_get_num_of_vce_state_table_entries_v1_0(काष्ठा pp_hwmgr *hwmgr)
अणु
	स्थिर ATOM_Tonga_POWERPLAYTABLE *pp_table = get_घातerplay_table(hwmgr);
	स्थिर ATOM_Tonga_VCE_State_Table *vce_state_table;


	अगर (pp_table == शून्य)
		वापस 0;

	vce_state_table = (व्योम *)pp_table +
			le16_to_cpu(pp_table->usVCEStateTableOffset);

	वापस vce_state_table->ucNumEntries;
पूर्ण

अटल पूर्णांक ppt_get_vce_state_table_entry_v1_0(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t i,
		काष्ठा amd_vce_state *vce_state, व्योम **घड़ी_info, uपूर्णांक32_t *flag)
अणु
	स्थिर ATOM_Tonga_VCE_State_Record *vce_state_record;
	ATOM_Tonga_SCLK_Dependency_Record *sclk_dep_record;
	ATOM_Tonga_MCLK_Dependency_Record *mclk_dep_record;
	ATOM_Tonga_MM_Dependency_Record *mm_dep_record;
	स्थिर ATOM_Tonga_POWERPLAYTABLE *pptable = get_घातerplay_table(hwmgr);
	स्थिर ATOM_Tonga_VCE_State_Table *vce_state_table = (ATOM_Tonga_VCE_State_Table *)(((अचिन्हित दीर्घ)pptable)
							  + le16_to_cpu(pptable->usVCEStateTableOffset));
	स्थिर ATOM_Tonga_SCLK_Dependency_Table *sclk_dep_table = (ATOM_Tonga_SCLK_Dependency_Table *)(((अचिन्हित दीर्घ)pptable)
							  + le16_to_cpu(pptable->usSclkDependencyTableOffset));
	स्थिर ATOM_Tonga_MCLK_Dependency_Table *mclk_dep_table = (ATOM_Tonga_MCLK_Dependency_Table *)(((अचिन्हित दीर्घ)pptable)
							  + le16_to_cpu(pptable->usMclkDependencyTableOffset));
	स्थिर ATOM_Tonga_MM_Dependency_Table *mm_dep_table = (ATOM_Tonga_MM_Dependency_Table *)(((अचिन्हित दीर्घ)pptable)
							  + le16_to_cpu(pptable->usMMDependencyTableOffset));

	PP_ASSERT_WITH_CODE((i < vce_state_table->ucNumEntries),
			 "Requested state entry ID is out of range!",
			 वापस -EINVAL);

	vce_state_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
					ATOM_Tonga_VCE_State_Record,
					entries, vce_state_table, i);
	sclk_dep_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
					ATOM_Tonga_SCLK_Dependency_Record,
					entries, sclk_dep_table,
					vce_state_record->ucSCLKIndex);
	mm_dep_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
					ATOM_Tonga_MM_Dependency_Record,
					entries, mm_dep_table,
					vce_state_record->ucVCEClockIndex);
	*flag = vce_state_record->ucFlag;

	vce_state->evclk = le32_to_cpu(mm_dep_record->ulEClk);
	vce_state->ecclk = le32_to_cpu(mm_dep_record->ulEClk);
	vce_state->sclk = le32_to_cpu(sclk_dep_record->ulSclk);

	अगर (vce_state_record->ucMCLKIndex >= mclk_dep_table->ucNumEntries)
		mclk_dep_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
					ATOM_Tonga_MCLK_Dependency_Record,
					entries, mclk_dep_table,
					mclk_dep_table->ucNumEntries - 1);
	अन्यथा
		mclk_dep_record = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
					ATOM_Tonga_MCLK_Dependency_Record,
					entries, mclk_dep_table,
					vce_state_record->ucMCLKIndex);

	vce_state->mclk = le32_to_cpu(mclk_dep_record->ulMclk);
	वापस 0;
पूर्ण

/**
 * get_घातerplay_table_entry_v1_0 - Create a Power State out of an entry in the PowerPlay table.
 * This function is called by the hardware back-end.
 * @hwmgr: Poपूर्णांकer to the hardware manager.
 * @entry_index: The index of the entry to be extracted from the table.
 * @घातer_state: The address of the PowerState instance being created.
 * @call_back_func: The function to call पूर्णांकo to fill घातer state
 * Return: -1 अगर the entry cannot be retrieved.
 */
पूर्णांक get_घातerplay_table_entry_v1_0(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t entry_index, काष्ठा pp_घातer_state *घातer_state,
		पूर्णांक (*call_back_func)(काष्ठा pp_hwmgr *, व्योम *,
				काष्ठा pp_घातer_state *, व्योम *, uपूर्णांक32_t))
अणु
	पूर्णांक result = 0;
	स्थिर ATOM_Tonga_State_Array *state_arrays;
	स्थिर ATOM_Tonga_State *state_entry;
	स्थिर ATOM_Tonga_POWERPLAYTABLE *pp_table = get_घातerplay_table(hwmgr);
	पूर्णांक i, j;
	uपूर्णांक32_t flags = 0;

	PP_ASSERT_WITH_CODE((शून्य != pp_table), "Missing PowerPlay Table!", वापस -1;);
	घातer_state->classअगरication.bios_index = entry_index;

	अगर (pp_table->sHeader.ucTableFormatRevision >=
			ATOM_Tonga_TABLE_REVISION_TONGA) अणु
		state_arrays = (ATOM_Tonga_State_Array *)(((अचिन्हित दीर्घ)pp_table) +
				le16_to_cpu(pp_table->usStateArrayOffset));

		PP_ASSERT_WITH_CODE((0 < pp_table->usStateArrayOffset),
				"Invalid PowerPlay Table State Array Offset.", वापस -1);
		PP_ASSERT_WITH_CODE((0 < state_arrays->ucNumEntries),
				"Invalid PowerPlay Table State Array.", वापस -1);
		PP_ASSERT_WITH_CODE((entry_index <= state_arrays->ucNumEntries),
				"Invalid PowerPlay Table State Array Entry.", वापस -1);

		state_entry = GET_FLEXIBLE_ARRAY_MEMBER_ADDR(
						ATOM_Tonga_State, entries,
						state_arrays, entry_index);

		result = call_back_func(hwmgr, (व्योम *)state_entry, घातer_state,
				(व्योम *)pp_table,
				make_classअगरication_flags(hwmgr,
					le16_to_cpu(state_entry->usClassअगरication),
					le16_to_cpu(state_entry->usClassअगरication2)));
	पूर्ण

	अगर (!result && (घातer_state->classअगरication.flags &
			PP_StateClassअगरicationFlag_Boot))
		result = hwmgr->hwmgr_func->patch_boot_state(hwmgr, &(घातer_state->hardware));

	hwmgr->num_vce_state_tables = i = ppt_get_num_of_vce_state_table_entries_v1_0(hwmgr);

	अगर ((i != 0) && (i <= AMD_MAX_VCE_LEVELS)) अणु
		क्रम (j = 0; j < i; j++)
			ppt_get_vce_state_table_entry_v1_0(hwmgr, j, &(hwmgr->vce_states[j]), शून्य, &flags);
	पूर्ण

	वापस result;
पूर्ण

