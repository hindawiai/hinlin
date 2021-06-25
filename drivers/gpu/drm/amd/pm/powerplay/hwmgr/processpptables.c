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
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>

#समावेश <drm/amdgpu_drm.h>
#समावेश "processpptables.h"
#समावेश <atom-types.h>
#समावेश <atomमूलप्रण.स>
#समावेश "pptable.h"
#समावेश "power_state.h"
#समावेश "hwmgr.h"
#समावेश "hardwaremanager.h"


#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V2 12
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V3 14
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V4 16
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V5 18
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V6 20
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V7 22
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V8 24
#घोषणा SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V9 26

#घोषणा NUM_BITS_CLOCK_INFO_ARRAY_INDEX 6

अटल uपूर्णांक16_t get_vce_table_offset(काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t vce_table_offset = 0;

	अगर (le16_to_cpu(घातerplay_table->usTableSize) >=
	   माप(ATOM_PPLIB_POWERPLAYTABLE3)) अणु
		स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *घातerplay_table3 =
			(स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *)घातerplay_table;

		अगर (घातerplay_table3->usExtendendedHeaderOffset > 0) अणु
			स्थिर ATOM_PPLIB_EXTENDEDHEADER  *extended_header =
						(स्थिर ATOM_PPLIB_EXTENDEDHEADER *)
						(((अचिन्हित दीर्घ)घातerplay_table3) +
						le16_to_cpu(घातerplay_table3->usExtendendedHeaderOffset));
			अगर (le16_to_cpu(extended_header->usSize) >=
			   SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V2)
				vce_table_offset = le16_to_cpu(extended_header->usVCETableOffset);
		पूर्ण
	पूर्ण

	वापस vce_table_offset;
पूर्ण

अटल uपूर्णांक16_t get_vce_घड़ी_info_array_offset(काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t table_offset = get_vce_table_offset(hwmgr,
						घातerplay_table);

	अगर (table_offset > 0)
		वापस table_offset + 1;

	वापस 0;
पूर्ण

अटल uपूर्णांक16_t get_vce_घड़ी_info_array_size(काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t table_offset = get_vce_घड़ी_info_array_offset(hwmgr,
							घातerplay_table);
	uपूर्णांक16_t table_size = 0;

	अगर (table_offset > 0) अणु
		स्थिर VCEClockInfoArray *p = (स्थिर VCEClockInfoArray *)
			(((अचिन्हित दीर्घ) घातerplay_table) + table_offset);
		table_size = माप(uपूर्णांक8_t) + p->ucNumEntries * माप(VCEClockInfo);
	पूर्ण

	वापस table_size;
पूर्ण

अटल uपूर्णांक16_t get_vce_घड़ी_voltage_limit_table_offset(काष्ठा pp_hwmgr *hwmgr,
				स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t table_offset = get_vce_घड़ी_info_array_offset(hwmgr,
							घातerplay_table);

	अगर (table_offset > 0)
		वापस table_offset + get_vce_घड़ी_info_array_size(hwmgr,
							घातerplay_table);

	वापस 0;
पूर्ण

अटल uपूर्णांक16_t get_vce_घड़ी_voltage_limit_table_size(काष्ठा pp_hwmgr *hwmgr,
							स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t table_offset = get_vce_घड़ी_voltage_limit_table_offset(hwmgr, घातerplay_table);
	uपूर्णांक16_t table_size = 0;

	अगर (table_offset > 0) अणु
		स्थिर ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *ptable =
			(स्थिर ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *)(((अचिन्हित दीर्घ) घातerplay_table) + table_offset);

		table_size = माप(uपूर्णांक8_t) + ptable->numEntries * माप(ATOM_PPLIB_VCE_Clock_Voltage_Limit_Record);
	पूर्ण
	वापस table_size;
पूर्ण

अटल uपूर्णांक16_t get_vce_state_table_offset(काष्ठा pp_hwmgr *hwmgr, स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t table_offset = get_vce_घड़ी_voltage_limit_table_offset(hwmgr, घातerplay_table);

	अगर (table_offset > 0)
		वापस table_offset + get_vce_घड़ी_voltage_limit_table_size(hwmgr, घातerplay_table);

	वापस 0;
पूर्ण

अटल स्थिर ATOM_PPLIB_VCE_State_Table *get_vce_state_table(
						काष्ठा pp_hwmgr *hwmgr,
						स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t table_offset = get_vce_state_table_offset(hwmgr, घातerplay_table);

	अगर (table_offset > 0)
		वापस (स्थिर ATOM_PPLIB_VCE_State_Table *)(((अचिन्हित दीर्घ) घातerplay_table) + table_offset);

	वापस शून्य;
पूर्ण

अटल uपूर्णांक16_t get_uvd_table_offset(काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t uvd_table_offset = 0;

	अगर (le16_to_cpu(घातerplay_table->usTableSize) >=
	    माप(ATOM_PPLIB_POWERPLAYTABLE3)) अणु
		स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *घातerplay_table3 =
			(स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *)घातerplay_table;
		अगर (घातerplay_table3->usExtendendedHeaderOffset > 0) अणु
			स्थिर ATOM_PPLIB_EXTENDEDHEADER  *extended_header =
					(स्थिर ATOM_PPLIB_EXTENDEDHEADER *)
					(((अचिन्हित दीर्घ)घातerplay_table3) +
				le16_to_cpu(घातerplay_table3->usExtendendedHeaderOffset));
			अगर (le16_to_cpu(extended_header->usSize) >=
			    SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V3)
				uvd_table_offset = le16_to_cpu(extended_header->usUVDTableOffset);
		पूर्ण
	पूर्ण
	वापस uvd_table_offset;
पूर्ण

अटल uपूर्णांक16_t get_uvd_घड़ी_info_array_offset(काष्ठा pp_hwmgr *hwmgr,
			 स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t table_offset = get_uvd_table_offset(hwmgr,
						    घातerplay_table);

	अगर (table_offset > 0)
		वापस table_offset + 1;
	वापस 0;
पूर्ण

अटल uपूर्णांक16_t get_uvd_घड़ी_info_array_size(काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t table_offset = get_uvd_घड़ी_info_array_offset(hwmgr,
						    घातerplay_table);
	uपूर्णांक16_t table_size = 0;

	अगर (table_offset > 0) अणु
		स्थिर UVDClockInfoArray *p = (स्थिर UVDClockInfoArray *)
					(((अचिन्हित दीर्घ) घातerplay_table)
					+ table_offset);
		table_size = माप(UCHAR) +
			     p->ucNumEntries * माप(UVDClockInfo);
	पूर्ण

	वापस table_size;
पूर्ण

अटल uपूर्णांक16_t get_uvd_घड़ी_voltage_limit_table_offset(
			काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t table_offset = get_uvd_घड़ी_info_array_offset(hwmgr,
						     घातerplay_table);

	अगर (table_offset > 0)
		वापस table_offset +
			get_uvd_घड़ी_info_array_size(hwmgr, घातerplay_table);

	वापस 0;
पूर्ण

अटल uपूर्णांक16_t get_samu_table_offset(काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t samu_table_offset = 0;

	अगर (le16_to_cpu(घातerplay_table->usTableSize) >=
	    माप(ATOM_PPLIB_POWERPLAYTABLE3)) अणु
		स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *घातerplay_table3 =
			(स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *)घातerplay_table;
		अगर (घातerplay_table3->usExtendendedHeaderOffset > 0) अणु
			स्थिर ATOM_PPLIB_EXTENDEDHEADER  *extended_header =
				(स्थिर ATOM_PPLIB_EXTENDEDHEADER *)
				(((अचिन्हित दीर्घ)घातerplay_table3) +
				le16_to_cpu(घातerplay_table3->usExtendendedHeaderOffset));
			अगर (le16_to_cpu(extended_header->usSize) >=
			    SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V4)
				samu_table_offset = le16_to_cpu(extended_header->usSAMUTableOffset);
		पूर्ण
	पूर्ण

	वापस samu_table_offset;
पूर्ण

अटल uपूर्णांक16_t get_samu_घड़ी_voltage_limit_table_offset(
			काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t table_offset = get_samu_table_offset(hwmgr,
					    घातerplay_table);

	अगर (table_offset > 0)
		वापस table_offset + 1;

	वापस 0;
पूर्ण

अटल uपूर्णांक16_t get_acp_table_offset(काष्ठा pp_hwmgr *hwmgr,
				स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t acp_table_offset = 0;

	अगर (le16_to_cpu(घातerplay_table->usTableSize) >=
	    माप(ATOM_PPLIB_POWERPLAYTABLE3)) अणु
		स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *घातerplay_table3 =
			(स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *)घातerplay_table;
		अगर (घातerplay_table3->usExtendendedHeaderOffset > 0) अणु
			स्थिर ATOM_PPLIB_EXTENDEDHEADER  *pExtendedHeader =
				(स्थिर ATOM_PPLIB_EXTENDEDHEADER *)
				(((अचिन्हित दीर्घ)घातerplay_table3) +
				le16_to_cpu(घातerplay_table3->usExtendendedHeaderOffset));
			अगर (le16_to_cpu(pExtendedHeader->usSize) >=
			    SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V6)
				acp_table_offset = le16_to_cpu(pExtendedHeader->usACPTableOffset);
		पूर्ण
	पूर्ण

	वापस acp_table_offset;
पूर्ण

अटल uपूर्णांक16_t get_acp_घड़ी_voltage_limit_table_offset(
				काष्ठा pp_hwmgr *hwmgr,
				स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t tableOffset = get_acp_table_offset(hwmgr, घातerplay_table);

	अगर (tableOffset > 0)
		वापस tableOffset + 1;

	वापस 0;
पूर्ण

अटल uपूर्णांक16_t get_cacp_tdp_table_offset(
				काष्ठा pp_hwmgr *hwmgr,
				स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t cacTdpTableOffset = 0;

	अगर (le16_to_cpu(घातerplay_table->usTableSize) >=
	    माप(ATOM_PPLIB_POWERPLAYTABLE3)) अणु
		स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *घातerplay_table3 =
				(स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *)घातerplay_table;
		अगर (घातerplay_table3->usExtendendedHeaderOffset > 0) अणु
			स्थिर ATOM_PPLIB_EXTENDEDHEADER  *pExtendedHeader =
					(स्थिर ATOM_PPLIB_EXTENDEDHEADER *)
					(((अचिन्हित दीर्घ)घातerplay_table3) +
				le16_to_cpu(घातerplay_table3->usExtendendedHeaderOffset));
			अगर (le16_to_cpu(pExtendedHeader->usSize) >=
			    SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V7)
				cacTdpTableOffset = le16_to_cpu(pExtendedHeader->usPowerTuneTableOffset);
		पूर्ण
	पूर्ण

	वापस cacTdpTableOffset;
पूर्ण

अटल पूर्णांक get_cac_tdp_table(काष्ठा pp_hwmgr *hwmgr,
				काष्ठा phm_cac_tdp_table **ptable,
				स्थिर ATOM_PowerTune_Table *table,
				uपूर्णांक16_t us_maximum_घातer_delivery_limit)
अणु
	अचिन्हित दीर्घ table_size;
	काष्ठा phm_cac_tdp_table *tdp_table;

	table_size = माप(अचिन्हित दीर्घ) + माप(काष्ठा phm_cac_tdp_table);

	tdp_table = kzalloc(table_size, GFP_KERNEL);
	अगर (शून्य == tdp_table)
		वापस -ENOMEM;

	tdp_table->usTDP = le16_to_cpu(table->usTDP);
	tdp_table->usConfigurableTDP = le16_to_cpu(table->usConfigurableTDP);
	tdp_table->usTDC = le16_to_cpu(table->usTDC);
	tdp_table->usBatteryPowerLimit = le16_to_cpu(table->usBatteryPowerLimit);
	tdp_table->usSmallPowerLimit = le16_to_cpu(table->usSmallPowerLimit);
	tdp_table->usLowCACLeakage = le16_to_cpu(table->usLowCACLeakage);
	tdp_table->usHighCACLeakage = le16_to_cpu(table->usHighCACLeakage);
	tdp_table->usMaximumPowerDeliveryLimit = us_maximum_घातer_delivery_limit;

	*ptable = tdp_table;

	वापस 0;
पूर्ण

अटल uपूर्णांक16_t get_sclk_vdd_gfx_table_offset(काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t sclk_vdd_gfx_table_offset = 0;

	अगर (le16_to_cpu(घातerplay_table->usTableSize) >=
	    माप(ATOM_PPLIB_POWERPLAYTABLE3)) अणु
		स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *घातerplay_table3 =
				(स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *)घातerplay_table;
		अगर (घातerplay_table3->usExtendendedHeaderOffset > 0) अणु
			स्थिर ATOM_PPLIB_EXTENDEDHEADER  *pExtendedHeader =
				(स्थिर ATOM_PPLIB_EXTENDEDHEADER *)
				(((अचिन्हित दीर्घ)घातerplay_table3) +
				le16_to_cpu(घातerplay_table3->usExtendendedHeaderOffset));
			अगर (le16_to_cpu(pExtendedHeader->usSize) >=
			    SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V8)
				sclk_vdd_gfx_table_offset =
					le16_to_cpu(pExtendedHeader->usSclkVddgfxTableOffset);
		पूर्ण
	पूर्ण

	वापस sclk_vdd_gfx_table_offset;
पूर्ण

अटल uपूर्णांक16_t get_sclk_vdd_gfx_घड़ी_voltage_dependency_table_offset(
			काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	uपूर्णांक16_t tableOffset = get_sclk_vdd_gfx_table_offset(hwmgr, घातerplay_table);

	अगर (tableOffset > 0)
		वापस tableOffset;

	वापस 0;
पूर्ण


अटल पूर्णांक get_घड़ी_voltage_dependency_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_घड़ी_voltage_dependency_table **ptable,
		स्थिर ATOM_PPLIB_Clock_Voltage_Dependency_Table *table)
अणु

	अचिन्हित दीर्घ i;
	काष्ठा phm_घड़ी_voltage_dependency_table *dep_table;

	dep_table = kzalloc(काष्ठा_size(dep_table, entries, table->ucNumEntries),
			    GFP_KERNEL);
	अगर (शून्य == dep_table)
		वापस -ENOMEM;

	dep_table->count = (अचिन्हित दीर्घ)table->ucNumEntries;

	क्रम (i = 0; i < dep_table->count; i++) अणु
		dep_table->entries[i].clk =
			((अचिन्हित दीर्घ)table->entries[i].ucClockHigh << 16) |
			le16_to_cpu(table->entries[i].usClockLow);
		dep_table->entries[i].v =
			(अचिन्हित दीर्घ)le16_to_cpu(table->entries[i].usVoltage);
	पूर्ण

	*ptable = dep_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_valid_clk(काष्ठा pp_hwmgr *hwmgr,
			काष्ठा phm_घड़ी_array **ptable,
			स्थिर काष्ठा phm_घड़ी_voltage_dependency_table *table)
अणु
	अचिन्हित दीर्घ i;
	काष्ठा phm_घड़ी_array *घड़ी_प्रकारable;

	घड़ी_प्रकारable = kzalloc(काष्ठा_size(घड़ी_प्रकारable, values, table->count), GFP_KERNEL);
	अगर (!घड़ी_प्रकारable)
		वापस -ENOMEM;

	घड़ी_प्रकारable->count = (अचिन्हित दीर्घ)table->count;

	क्रम (i = 0; i < घड़ी_प्रकारable->count; i++)
		घड़ी_प्रकारable->values[i] = (अचिन्हित दीर्घ)table->entries[i].clk;

	*ptable = घड़ी_प्रकारable;

	वापस 0;
पूर्ण

अटल पूर्णांक get_घड़ी_voltage_limit(काष्ठा pp_hwmgr *hwmgr,
			काष्ठा phm_घड़ी_and_voltage_limits *limits,
			स्थिर ATOM_PPLIB_Clock_Voltage_Limit_Table *table)
अणु
	limits->sclk = ((अचिन्हित दीर्घ)table->entries[0].ucSclkHigh << 16) |
			le16_to_cpu(table->entries[0].usSclkLow);
	limits->mclk = ((अचिन्हित दीर्घ)table->entries[0].ucMclkHigh << 16) |
			le16_to_cpu(table->entries[0].usMclkLow);
	limits->vddc = (अचिन्हित दीर्घ)le16_to_cpu(table->entries[0].usVddc);
	limits->vddci = (अचिन्हित दीर्घ)le16_to_cpu(table->entries[0].usVddci);

	वापस 0;
पूर्ण


अटल व्योम set_hw_cap(काष्ठा pp_hwmgr *hwmgr, bool enable,
		       क्रमागत phm_platक्रमm_caps cap)
अणु
	अगर (enable)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, cap);
	अन्यथा
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps, cap);
पूर्ण

अटल पूर्णांक set_platक्रमm_caps(काष्ठा pp_hwmgr *hwmgr,
			अचिन्हित दीर्घ घातerplay_caps)
अणु
	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_POWERPLAY),
		PHM_Platक्रमmCaps_PowerPlaySupport
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_SBIOSPOWERSOURCE),
		PHM_Platक्रमmCaps_BiosPowerSourceControl
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_ASPM_L0s),
		PHM_Platक्रमmCaps_EnableASPML0s
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_ASPM_L1),
		PHM_Platक्रमmCaps_EnableASPML1
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_BACKBIAS),
		PHM_Platक्रमmCaps_EnableBackbias
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_HARDWAREDC),
		PHM_Platक्रमmCaps_AutomaticDCTransition
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_GEMINIPRIMARY),
		PHM_Platक्रमmCaps_GeminiPrimary
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_STEPVDDC),
		PHM_Platक्रमmCaps_StepVddc
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_VOLTAGECONTROL),
		PHM_Platक्रमmCaps_EnableVoltageControl
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_SIDEPORTCONTROL),
		PHM_Platक्रमmCaps_EnableSideportControl
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_TURNOFFPLL_ASPML1),
		PHM_Platक्रमmCaps_TurnOffPll_ASPML1
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_HTLINKCONTROL),
		PHM_Platक्रमmCaps_EnableHTLinkControl
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_MVDDCONTROL),
		PHM_Platक्रमmCaps_EnableMVDDControl
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_VDDCI_CONTROL),
		PHM_Platक्रमmCaps_ControlVDDCI
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_REGULATOR_HOT),
		PHM_Platक्रमmCaps_RegulatorHot
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_GOTO_BOOT_ON_ALERT),
		PHM_Platक्रमmCaps_BootStateOnAlert
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_DONT_WAIT_FOR_VBLANK_ON_ALERT),
		PHM_Platक्रमmCaps_DontWaitForVBlankOnAlert
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_BACO),
		PHM_Platक्रमmCaps_BACO
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_NEW_CAC_VOLTAGE),
		PHM_Platक्रमmCaps_NewCACVoltage
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_REVERT_GPIO5_POLARITY),
		PHM_Platक्रमmCaps_RevertGPIO5Polarity
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_OUTPUT_THERMAL2GPIO17),
		PHM_Platक्रमmCaps_Thermal2GPIO17
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_VRHOT_GPIO_CONFIGURABLE),
		PHM_Platक्रमmCaps_VRHotGPIOConfigurable
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_TEMP_INVERSION),
		PHM_Platक्रमmCaps_TempInversion
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_EVV),
		PHM_Platक्रमmCaps_EVV
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_COMBINE_PCC_WITH_THERMAL_SIGNAL),
		PHM_Platक्रमmCaps_CombinePCCWithThermalSignal
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_LOAD_POST_PRODUCTION_FIRMWARE),
		PHM_Platक्रमmCaps_LoadPostProductionFirmware
	);

	set_hw_cap(
		hwmgr,
		0 != (घातerplay_caps & ATOM_PP_PLATFORM_CAP_DISABLE_USING_ACTUAL_TEMPERATURE_FOR_POWER_CALC),
		PHM_Platक्रमmCaps_DisableUsingActualTemperatureForPowerCalc
	);

	वापस 0;
पूर्ण

अटल PP_StateClassअगरicationFlags make_classअगरication_flags(
						   काष्ठा pp_hwmgr *hwmgr,
						    USHORT classअगरication,
						   USHORT classअगरication2)
अणु
	PP_StateClassअगरicationFlags result = 0;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_BOOT)
		result |= PP_StateClassअगरicationFlag_Boot;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_THERMAL)
		result |= PP_StateClassअगरicationFlag_Thermal;

	अगर (classअगरication &
			ATOM_PPLIB_CLASSIFICATION_LIMITEDPOWERSOURCE)
		result |= PP_StateClassअगरicationFlag_LimitedPowerSource;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_REST)
		result |= PP_StateClassअगरicationFlag_Rest;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_FORCED)
		result |= PP_StateClassअगरicationFlag_Forced;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_3DPERFORMANCE)
		result |= PP_StateClassअगरicationFlag_3DPerक्रमmance;


	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_OVERDRIVETEMPLATE)
		result |= PP_StateClassअगरicationFlag_ACOverdriveTemplate;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_UVDSTATE)
		result |= PP_StateClassअगरicationFlag_Uvd;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_HDSTATE)
		result |= PP_StateClassअगरicationFlag_UvdHD;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_SDSTATE)
		result |= PP_StateClassअगरicationFlag_UvdSD;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_HD2STATE)
		result |= PP_StateClassअगरicationFlag_HD2;

	अगर (classअगरication & ATOM_PPLIB_CLASSIFICATION_ACPI)
		result |= PP_StateClassअगरicationFlag_ACPI;

	अगर (classअगरication2 & ATOM_PPLIB_CLASSIFICATION2_LIMITEDPOWERSOURCE_2)
		result |= PP_StateClassअगरicationFlag_LimitedPowerSource_2;


	अगर (classअगरication2 & ATOM_PPLIB_CLASSIFICATION2_ULV)
		result |= PP_StateClassअगरicationFlag_ULV;

	अगर (classअगरication2 & ATOM_PPLIB_CLASSIFICATION2_MVC)
		result |= PP_StateClassअगरicationFlag_UvdMVC;

	वापस result;
पूर्ण

अटल पूर्णांक init_non_घड़ी_fields(काष्ठा pp_hwmgr *hwmgr,
						काष्ठा pp_घातer_state *ps,
							    uपूर्णांक8_t version,
			 स्थिर ATOM_PPLIB_NONCLOCK_INFO *pnon_घड़ी_info) अणु
	अचिन्हित दीर्घ rrr_index;
	अचिन्हित दीर्घ पंचांगp;

	ps->classअगरication.ui_label = (le16_to_cpu(pnon_घड़ी_info->usClassअगरication) &
					ATOM_PPLIB_CLASSIFICATION_UI_MASK) >> ATOM_PPLIB_CLASSIFICATION_UI_SHIFT;
	ps->classअगरication.flags = make_classअगरication_flags(hwmgr,
				le16_to_cpu(pnon_घड़ी_info->usClassअगरication),
				le16_to_cpu(pnon_घड़ी_info->usClassअगरication2));

	ps->classअगरication.temporary_state = false;
	ps->classअगरication.to_be_deleted = false;
	पंचांगp = le32_to_cpu(pnon_घड़ी_info->ulCapsAndSettings) &
		ATOM_PPLIB_SINGLE_DISPLAY_ONLY;

	ps->validation.singleDisplayOnly = (0 != पंचांगp);

	पंचांगp = le32_to_cpu(pnon_घड़ी_info->ulCapsAndSettings) &
		ATOM_PPLIB_DISALLOW_ON_DC;

	ps->validation.disallowOnDC = (0 != पंचांगp);

	ps->pcie.lanes = ((le32_to_cpu(pnon_घड़ी_info->ulCapsAndSettings) &
				ATOM_PPLIB_PCIE_LINK_WIDTH_MASK) >>
				ATOM_PPLIB_PCIE_LINK_WIDTH_SHIFT) + 1;

	ps->pcie.lanes = 0;

	ps->display.disableFrameModulation = false;

	rrr_index = (le32_to_cpu(pnon_घड़ी_info->ulCapsAndSettings) &
			ATOM_PPLIB_LIMITED_REFRESHRATE_VALUE_MASK) >>
			ATOM_PPLIB_LIMITED_REFRESHRATE_VALUE_SHIFT;

	अगर (rrr_index != ATOM_PPLIB_LIMITED_REFRESHRATE_UNLIMITED) अणु
		अटल स्थिर uपूर्णांक8_t look_up[(ATOM_PPLIB_LIMITED_REFRESHRATE_VALUE_MASK >> ATOM_PPLIB_LIMITED_REFRESHRATE_VALUE_SHIFT) + 1] = \
								अणु 0, 50, 0 पूर्ण;

		ps->display.refreshrateSource = PP_RefreshrateSource_Explicit;
		ps->display.explicitRefreshrate = look_up[rrr_index];
		ps->display.limitRefreshrate = true;

		अगर (ps->display.explicitRefreshrate == 0)
			ps->display.limitRefreshrate = false;
	पूर्ण अन्यथा
		ps->display.limitRefreshrate = false;

	पंचांगp = le32_to_cpu(pnon_घड़ी_info->ulCapsAndSettings) &
		ATOM_PPLIB_ENABLE_VARIBRIGHT;

	ps->display.enableVariBright = (0 != पंचांगp);

	पंचांगp = le32_to_cpu(pnon_घड़ी_info->ulCapsAndSettings) &
		ATOM_PPLIB_SWSTATE_MEMORY_DLL_OFF;

	ps->memory.dllOff = (0 != पंचांगp);

	ps->memory.m3arb = (le32_to_cpu(pnon_घड़ी_info->ulCapsAndSettings) &
			    ATOM_PPLIB_M3ARB_MASK) >> ATOM_PPLIB_M3ARB_SHIFT;

	ps->temperatures.min = PP_TEMPERATURE_UNITS_PER_CENTIGRADES *
				     pnon_घड़ी_info->ucMinTemperature;

	ps->temperatures.max = PP_TEMPERATURE_UNITS_PER_CENTIGRADES *
				     pnon_घड़ी_info->ucMaxTemperature;

	पंचांगp = le32_to_cpu(pnon_घड़ी_info->ulCapsAndSettings) &
		ATOM_PPLIB_SOFTWARE_DISABLE_LOADBALANCING;

	ps->software.disableLoadBalancing = पंचांगp;

	पंचांगp = le32_to_cpu(pnon_घड़ी_info->ulCapsAndSettings) &
		ATOM_PPLIB_SOFTWARE_ENABLE_SLEEP_FOR_TIMESTAMPS;

	ps->software.enableSleepForTimestamps = (0 != पंचांगp);

	ps->validation.supportedPowerLevels = pnon_घड़ी_info->ucRequiredPower;

	अगर (ATOM_PPLIB_NONCLOCKINFO_VER1 < version) अणु
		ps->uvd_घड़ीs.VCLK = le32_to_cpu(pnon_घड़ी_info->ulVCLK);
		ps->uvd_घड़ीs.DCLK = le32_to_cpu(pnon_घड़ी_info->ulDCLK);
	पूर्ण अन्यथा अणु
		ps->uvd_घड़ीs.VCLK = 0;
		ps->uvd_घड़ीs.DCLK = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल ULONG size_of_entry_v2(ULONG num_dpm_levels)
अणु
	वापस (माप(UCHAR) + माप(UCHAR) +
			(num_dpm_levels * माप(UCHAR)));
पूर्ण

अटल स्थिर ATOM_PPLIB_STATE_V2 *get_state_entry_v2(
					स्थिर StateArray * pstate_arrays,
							 ULONG entry_index)
अणु
	ULONG i;
	स्थिर ATOM_PPLIB_STATE_V2 *pstate;

	pstate = pstate_arrays->states;
	अगर (entry_index <= pstate_arrays->ucNumEntries) अणु
		क्रम (i = 0; i < entry_index; i++)
			pstate = (ATOM_PPLIB_STATE_V2 *)(
						  (अचिन्हित दीर्घ)pstate +
			     size_of_entry_v2(pstate->ucNumDPMLevels));
	पूर्ण
	वापस pstate;
पूर्ण

अटल स्थिर अचिन्हित अक्षर soft_dummy_pp_table[] = अणु
	0xe1, 0x01, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x4a, 0x00, 0x6c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x42, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x4e, 0x00, 0x88, 0x00, 0x00, 0x9e, 0x00, 0x17, 0x00, 0x00, 0x00, 0x9e, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00,
	0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x18, 0x05, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe1, 0x00, 0x43, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x8e, 0x01, 0x00, 0x00, 0xb8, 0x01, 0x00, 0x00, 0x08, 0x30, 0x75, 0x00, 0x80, 0x00, 0xa0, 0x8c,
	0x00, 0x7e, 0x00, 0x71, 0xa5, 0x00, 0x7c, 0x00, 0xe5, 0xc8, 0x00, 0x70, 0x00, 0x91, 0xf4, 0x00,
	0x64, 0x00, 0x40, 0x19, 0x01, 0x5a, 0x00, 0x0e, 0x28, 0x01, 0x52, 0x00, 0x80, 0x38, 0x01, 0x4a,
	0x00, 0x00, 0x09, 0x30, 0x75, 0x00, 0x30, 0x75, 0x00, 0x40, 0x9c, 0x00, 0x40, 0x9c, 0x00, 0x59,
	0xd8, 0x00, 0x59, 0xd8, 0x00, 0x91, 0xf4, 0x00, 0x91, 0xf4, 0x00, 0x0e, 0x28, 0x01, 0x0e, 0x28,
	0x01, 0x90, 0x5f, 0x01, 0x90, 0x5f, 0x01, 0x00, 0x77, 0x01, 0x00, 0x77, 0x01, 0xca, 0x91, 0x01,
	0xca, 0x91, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x80, 0x00, 0x00, 0x7e, 0x00, 0x01,
	0x7c, 0x00, 0x02, 0x70, 0x00, 0x03, 0x64, 0x00, 0x04, 0x5a, 0x00, 0x05, 0x52, 0x00, 0x06, 0x4a,
	0x00, 0x07, 0x08, 0x08, 0x00, 0x08, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x02, 0x02, 0x02, 0x03,
	0x02, 0x04, 0x02, 0x00, 0x08, 0x40, 0x9c, 0x00, 0x30, 0x75, 0x00, 0x74, 0xb5, 0x00, 0xa0, 0x8c,
	0x00, 0x60, 0xea, 0x00, 0x74, 0xb5, 0x00, 0x0e, 0x28, 0x01, 0x60, 0xea, 0x00, 0x90, 0x5f, 0x01,
	0x40, 0x19, 0x01, 0xb2, 0xb0, 0x01, 0x90, 0x5f, 0x01, 0xc0, 0xd4, 0x01, 0x00, 0x77, 0x01, 0x5e,
	0xff, 0x01, 0xca, 0x91, 0x01, 0x08, 0x80, 0x00, 0x00, 0x7e, 0x00, 0x01, 0x7c, 0x00, 0x02, 0x70,
	0x00, 0x03, 0x64, 0x00, 0x04, 0x5a, 0x00, 0x05, 0x52, 0x00, 0x06, 0x4a, 0x00, 0x07, 0x00, 0x08,
	0x80, 0x00, 0x30, 0x75, 0x00, 0x7e, 0x00, 0x40, 0x9c, 0x00, 0x7c, 0x00, 0x59, 0xd8, 0x00, 0x70,
	0x00, 0xdc, 0x0b, 0x01, 0x64, 0x00, 0x80, 0x38, 0x01, 0x5a, 0x00, 0x80, 0x38, 0x01, 0x52, 0x00,
	0x80, 0x38, 0x01, 0x4a, 0x00, 0x80, 0x38, 0x01, 0x08, 0x30, 0x75, 0x00, 0x80, 0x00, 0xa0, 0x8c,
	0x00, 0x7e, 0x00, 0x71, 0xa5, 0x00, 0x7c, 0x00, 0xe5, 0xc8, 0x00, 0x74, 0x00, 0x91, 0xf4, 0x00,
	0x66, 0x00, 0x40, 0x19, 0x01, 0x58, 0x00, 0x0e, 0x28, 0x01, 0x52, 0x00, 0x80, 0x38, 0x01, 0x4a,
	0x00
पूर्ण;

अटल स्थिर ATOM_PPLIB_POWERPLAYTABLE *get_घातerplay_table(
				     काष्ठा pp_hwmgr *hwmgr)
अणु
	स्थिर व्योम *table_addr = hwmgr->soft_pp_table;
	uपूर्णांक8_t frev, crev;
	uपूर्णांक16_t size;

	अगर (!table_addr) अणु
		अगर (hwmgr->chip_id == CHIP_RAVEN) अणु
			table_addr = &soft_dummy_pp_table[0];
			hwmgr->soft_pp_table = &soft_dummy_pp_table[0];
			hwmgr->soft_pp_table_size = माप(soft_dummy_pp_table);
		पूर्ण अन्यथा अणु
			table_addr = smu_atom_get_data_table(hwmgr->adev,
					GetIndexIntoMasterTable(DATA, PowerPlayInfo),
					&size, &frev, &crev);
			hwmgr->soft_pp_table = table_addr;
			hwmgr->soft_pp_table_size = size;
		पूर्ण
	पूर्ण

	वापस (स्थिर ATOM_PPLIB_POWERPLAYTABLE *)table_addr;
पूर्ण

पूर्णांक pp_tables_get_response_बार(काष्ठा pp_hwmgr *hwmgr,
				uपूर्णांक32_t *vol_rep_समय, uपूर्णांक32_t *bb_rep_समय)
अणु
	स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_tab = get_घातerplay_table(hwmgr);

	PP_ASSERT_WITH_CODE(शून्य != घातerplay_tab,
			    "Missing PowerPlay Table!", वापस -EINVAL);

	*vol_rep_समय = (uपूर्णांक32_t)le16_to_cpu(घातerplay_tab->usVoltageTime);
	*bb_rep_समय = (uपूर्णांक32_t)le16_to_cpu(घातerplay_tab->usBackbiasTime);

	वापस 0;
पूर्ण

पूर्णांक pp_tables_get_num_of_entries(काष्ठा pp_hwmgr *hwmgr,
				     अचिन्हित दीर्घ *num_of_entries)
अणु
	स्थिर StateArray *pstate_arrays;
	स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table = get_घातerplay_table(hwmgr);

	अगर (घातerplay_table == शून्य)
		वापस -1;

	अगर (घातerplay_table->sHeader.ucTableFormatRevision >= 6) अणु
		pstate_arrays = (StateArray *)(((अचिन्हित दीर्घ)घातerplay_table) +
					le16_to_cpu(घातerplay_table->usStateArrayOffset));

		*num_of_entries = (अचिन्हित दीर्घ)(pstate_arrays->ucNumEntries);
	पूर्ण अन्यथा
		*num_of_entries = (अचिन्हित दीर्घ)(घातerplay_table->ucNumStates);

	वापस 0;
पूर्ण

पूर्णांक pp_tables_get_entry(काष्ठा pp_hwmgr *hwmgr,
				अचिन्हित दीर्घ entry_index,
				काष्ठा pp_घातer_state *ps,
			 pp_tables_hw_घड़ी_info_callback func)
अणु
	पूर्णांक i;
	स्थिर StateArray *pstate_arrays;
	स्थिर ATOM_PPLIB_STATE_V2 *pstate_entry_v2;
	स्थिर ATOM_PPLIB_NONCLOCK_INFO *pnon_घड़ी_info;
	स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table = get_घातerplay_table(hwmgr);
	पूर्णांक result = 0;
	पूर्णांक res = 0;

	स्थिर ClockInfoArray *pघड़ी_arrays;

	स्थिर NonClockInfoArray *pnon_घड़ी_arrays;

	स्थिर ATOM_PPLIB_STATE *pstate_entry;

	अगर (घातerplay_table == शून्य)
		वापस -1;

	ps->classअगरication.bios_index = entry_index;

	अगर (घातerplay_table->sHeader.ucTableFormatRevision >= 6) अणु
		pstate_arrays = (StateArray *)(((अचिन्हित दीर्घ)घातerplay_table) +
					le16_to_cpu(घातerplay_table->usStateArrayOffset));

		अगर (entry_index > pstate_arrays->ucNumEntries)
			वापस -1;

		pstate_entry_v2 = get_state_entry_v2(pstate_arrays, entry_index);
		pघड़ी_arrays = (ClockInfoArray *)(((अचिन्हित दीर्घ)घातerplay_table) +
					le16_to_cpu(घातerplay_table->usClockInfoArrayOffset));

		pnon_घड़ी_arrays = (NonClockInfoArray *)(((अचिन्हित दीर्घ)घातerplay_table) +
						le16_to_cpu(घातerplay_table->usNonClockInfoArrayOffset));

		pnon_घड़ी_info = (ATOM_PPLIB_NONCLOCK_INFO *)((अचिन्हित दीर्घ)(pnon_घड़ी_arrays->nonClockInfo) +
					(pstate_entry_v2->nonClockInfoIndex * pnon_घड़ी_arrays->ucEntrySize));

		result = init_non_घड़ी_fields(hwmgr, ps, pnon_घड़ी_arrays->ucEntrySize, pnon_घड़ी_info);

		क्रम (i = 0; i < pstate_entry_v2->ucNumDPMLevels; i++) अणु
			स्थिर व्योम *pघड़ी_info = (स्थिर व्योम *)(
							(अचिन्हित दीर्घ)(pघड़ी_arrays->घड़ीInfo) +
							(pstate_entry_v2->घड़ीInfoIndex[i] * pघड़ी_arrays->ucEntrySize));
			res = func(hwmgr, &ps->hardware, i, pघड़ी_info);
			अगर ((0 == result) && (0 != res))
				result = res;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (entry_index > घातerplay_table->ucNumStates)
			वापस -1;

		pstate_entry = (ATOM_PPLIB_STATE *)((अचिन्हित दीर्घ)घातerplay_table +
						    le16_to_cpu(घातerplay_table->usStateArrayOffset) +
						    entry_index * घातerplay_table->ucStateEntrySize);

		pnon_घड़ी_info = (ATOM_PPLIB_NONCLOCK_INFO *)((अचिन्हित दीर्घ)घातerplay_table +
						le16_to_cpu(घातerplay_table->usNonClockInfoArrayOffset) +
						pstate_entry->ucNonClockStateIndex *
						घातerplay_table->ucNonClockSize);

		result = init_non_घड़ी_fields(hwmgr, ps,
							घातerplay_table->ucNonClockSize,
							pnon_घड़ी_info);

		क्रम (i = 0; i < घातerplay_table->ucStateEntrySize-1; i++) अणु
			स्थिर व्योम *pघड़ी_info = (स्थिर व्योम *)((अचिन्हित दीर्घ)घातerplay_table +
						le16_to_cpu(घातerplay_table->usClockInfoArrayOffset) +
						pstate_entry->ucClockStateIndices[i] *
						घातerplay_table->ucClockInfoSize);

			पूर्णांक res = func(hwmgr, &ps->hardware, i, pघड़ी_info);

			अगर ((0 == result) && (0 != res))
					result = res;
		पूर्ण
	पूर्ण

	अगर ((0 == result) && (0 != (ps->classअगरication.flags & PP_StateClassअगरicationFlag_Boot))) अणु
		अगर (hwmgr->chip_family < AMDGPU_FAMILY_RV)
			result = hwmgr->hwmgr_func->patch_boot_state(hwmgr, &(ps->hardware));
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक init_घातerplay_tables(
			काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table
)
अणु
	वापस 0;
पूर्ण


अटल पूर्णांक init_thermal_controller(
			काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	hwmgr->thermal_controller.ucType =
			घातerplay_table->sThermalController.ucType;
	hwmgr->thermal_controller.ucI2cLine =
			घातerplay_table->sThermalController.ucI2cLine;
	hwmgr->thermal_controller.ucI2cAddress =
			घातerplay_table->sThermalController.ucI2cAddress;

	hwmgr->thermal_controller.fanInfo.bNoFan =
		(0 != (घातerplay_table->sThermalController.ucFanParameters &
			ATOM_PP_FANPARAMETERS_NOFAN));

	hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution =
		घातerplay_table->sThermalController.ucFanParameters &
		ATOM_PP_FANPARAMETERS_TACHOMETER_PULSES_PER_REVOLUTION_MASK;

	hwmgr->thermal_controller.fanInfo.ulMinRPM
		= घातerplay_table->sThermalController.ucFanMinRPM * 100UL;
	hwmgr->thermal_controller.fanInfo.ulMaxRPM
		= घातerplay_table->sThermalController.ucFanMaxRPM * 100UL;

	set_hw_cap(hwmgr,
		   ATOM_PP_THERMALCONTROLLER_NONE != hwmgr->thermal_controller.ucType,
		   PHM_Platक्रमmCaps_ThermalController);

        अगर (घातerplay_table->usTableSize >= माप(ATOM_PPLIB_POWERPLAYTABLE3)) अणु
		स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *घातerplay_table3 =
			(स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *)घातerplay_table;

		अगर (0 == le16_to_cpu(घातerplay_table3->usFanTableOffset)) अणु
			hwmgr->thermal_controller.use_hw_fan_control = 1;
			वापस 0;
		पूर्ण अन्यथा अणु
			स्थिर ATOM_PPLIB_FANTABLE *fan_table =
				(स्थिर ATOM_PPLIB_FANTABLE *)(((अचिन्हित दीर्घ)घातerplay_table) +
							      le16_to_cpu(घातerplay_table3->usFanTableOffset));

			अगर (1 <= fan_table->ucFanTableFormat) अणु
				hwmgr->thermal_controller.advanceFanControlParameters.ucTHyst =
					fan_table->ucTHyst;
				hwmgr->thermal_controller.advanceFanControlParameters.usTMin =
					le16_to_cpu(fan_table->usTMin);
				hwmgr->thermal_controller.advanceFanControlParameters.usTMed =
					le16_to_cpu(fan_table->usTMed);
				hwmgr->thermal_controller.advanceFanControlParameters.usTHigh =
					le16_to_cpu(fan_table->usTHigh);
				hwmgr->thermal_controller.advanceFanControlParameters.usPWMMin =
					le16_to_cpu(fan_table->usPWMMin);
				hwmgr->thermal_controller.advanceFanControlParameters.usPWMMed =
					le16_to_cpu(fan_table->usPWMMed);
				hwmgr->thermal_controller.advanceFanControlParameters.usPWMHigh =
					le16_to_cpu(fan_table->usPWMHigh);
				hwmgr->thermal_controller.advanceFanControlParameters.usTMax = 10900;
				hwmgr->thermal_controller.advanceFanControlParameters.ulCycleDelay = 100000;

				phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					    PHM_Platक्रमmCaps_MicrocodeFanControl);
			पूर्ण

			अगर (2 <= fan_table->ucFanTableFormat) अणु
				स्थिर ATOM_PPLIB_FANTABLE2 *fan_table2 =
					(स्थिर ATOM_PPLIB_FANTABLE2 *)(((अचिन्हित दीर्घ)घातerplay_table) +
								       le16_to_cpu(घातerplay_table3->usFanTableOffset));
				hwmgr->thermal_controller.advanceFanControlParameters.usTMax =
					le16_to_cpu(fan_table2->usTMax);
			पूर्ण

			अगर (3 <= fan_table->ucFanTableFormat) अणु
				स्थिर ATOM_PPLIB_FANTABLE3 *fan_table3 =
					(स्थिर ATOM_PPLIB_FANTABLE3 *) (((अचिन्हित दीर्घ)घातerplay_table) +
									le16_to_cpu(घातerplay_table3->usFanTableOffset));

				hwmgr->thermal_controller.advanceFanControlParameters.ucFanControlMode =
					fan_table3->ucFanControlMode;

				अगर ((3 == fan_table->ucFanTableFormat) &&
				    (0x67B1 == adev->pdev->device))
					hwmgr->thermal_controller.advanceFanControlParameters.usDefaultMaxFanPWM =
						47;
				अन्यथा
					hwmgr->thermal_controller.advanceFanControlParameters.usDefaultMaxFanPWM =
						le16_to_cpu(fan_table3->usFanPWMMax);

				hwmgr->thermal_controller.advanceFanControlParameters.usDefaultFanOutputSensitivity =
					4836;
				hwmgr->thermal_controller.advanceFanControlParameters.usFanOutputSensitivity =
					le16_to_cpu(fan_table3->usFanOutputSensitivity);
			पूर्ण

			अगर (6 <= fan_table->ucFanTableFormat) अणु
				स्थिर ATOM_PPLIB_FANTABLE4 *fan_table4 =
					(स्थिर ATOM_PPLIB_FANTABLE4 *)(((अचिन्हित दीर्घ)घातerplay_table) +
								       le16_to_cpu(घातerplay_table3->usFanTableOffset));

				phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					    PHM_Platक्रमmCaps_FanSpeedInTableIsRPM);

				hwmgr->thermal_controller.advanceFanControlParameters.usDefaultMaxFanRPM =
					le16_to_cpu(fan_table4->usFanRPMMax);
			पूर्ण

			अगर (7 <= fan_table->ucFanTableFormat) अणु
				स्थिर ATOM_PPLIB_FANTABLE5 *fan_table5 =
					(स्थिर ATOM_PPLIB_FANTABLE5 *)(((अचिन्हित दीर्घ)घातerplay_table) +
								       le16_to_cpu(घातerplay_table3->usFanTableOffset));

				अगर (0x67A2 == adev->pdev->device ||
				    0x67A9 == adev->pdev->device ||
				    0x67B9 == adev->pdev->device) अणु
					phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
						    PHM_Platक्रमmCaps_GeminiRegulatorFanControlSupport);
					hwmgr->thermal_controller.advanceFanControlParameters.usFanCurrentLow =
						le16_to_cpu(fan_table5->usFanCurrentLow);
					hwmgr->thermal_controller.advanceFanControlParameters.usFanCurrentHigh =
						le16_to_cpu(fan_table5->usFanCurrentHigh);
					hwmgr->thermal_controller.advanceFanControlParameters.usFanRPMLow =
						le16_to_cpu(fan_table5->usFanRPMLow);
					hwmgr->thermal_controller.advanceFanControlParameters.usFanRPMHigh =
						le16_to_cpu(fan_table5->usFanRPMHigh);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_overdrive_limits_V1_4(काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table,
			स्थिर ATOM_FIRMWARE_INFO_V1_4 *fw_info)
अणु
	hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock =
				le32_to_cpu(fw_info->ulASICMaxEngineClock);

	hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock =
				le32_to_cpu(fw_info->ulASICMaxMemoryClock);

	hwmgr->platक्रमm_descriptor.maxOverdriveVDDC =
		le32_to_cpu(fw_info->ul3DAccelerationEngineClock) & 0x7FF;

	hwmgr->platक्रमm_descriptor.minOverdriveVDDC =
			   le16_to_cpu(fw_info->usBootUpVDDCVoltage);

	hwmgr->platक्रमm_descriptor.maxOverdriveVDDC =
			   le16_to_cpu(fw_info->usBootUpVDDCVoltage);

	hwmgr->platक्रमm_descriptor.overdriveVDDCStep = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक init_overdrive_limits_V2_1(काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table,
			स्थिर ATOM_FIRMWARE_INFO_V2_1 *fw_info)
अणु
	स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *घातerplay_table3;
	स्थिर ATOM_PPLIB_EXTENDEDHEADER *header;

	अगर (le16_to_cpu(घातerplay_table->usTableSize) <
	    माप(ATOM_PPLIB_POWERPLAYTABLE3))
		वापस 0;

	घातerplay_table3 = (स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *)घातerplay_table;

	अगर (0 == घातerplay_table3->usExtendendedHeaderOffset)
		वापस 0;

	header = (ATOM_PPLIB_EXTENDEDHEADER *)(((अचिन्हित दीर्घ) घातerplay_table) +
			le16_to_cpu(घातerplay_table3->usExtendendedHeaderOffset));

	hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock = le32_to_cpu(header->ulMaxEngineClock);
	hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock = le32_to_cpu(header->ulMaxMemoryClock);


	hwmgr->platक्रमm_descriptor.minOverdriveVDDC = 0;
	hwmgr->platक्रमm_descriptor.maxOverdriveVDDC = 0;
	hwmgr->platक्रमm_descriptor.overdriveVDDCStep = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक init_overdrive_limits(काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	पूर्णांक result = 0;
	uपूर्णांक8_t frev, crev;
	uपूर्णांक16_t size;

	स्थिर ATOM_COMMON_TABLE_HEADER *fw_info = शून्य;

	hwmgr->platक्रमm_descriptor.overdriveLimit.engineClock = 0;
	hwmgr->platक्रमm_descriptor.overdriveLimit.memoryClock = 0;
	hwmgr->platक्रमm_descriptor.minOverdriveVDDC = 0;
	hwmgr->platक्रमm_descriptor.maxOverdriveVDDC = 0;
	hwmgr->platक्रमm_descriptor.overdriveVDDCStep = 0;

	अगर (hwmgr->chip_id == CHIP_RAVEN)
		वापस 0;

	/* We assume here that fw_info is unchanged अगर this call fails.*/
	fw_info = smu_atom_get_data_table(hwmgr->adev,
			 GetIndexIntoMasterTable(DATA, FirmwareInfo),
			 &size, &frev, &crev);

	अगर ((fw_info->ucTableFormatRevision == 1)
	    && (le16_to_cpu(fw_info->usStructureSize) >= माप(ATOM_FIRMWARE_INFO_V1_4)))
		result = init_overdrive_limits_V1_4(hwmgr,
				घातerplay_table,
				(स्थिर ATOM_FIRMWARE_INFO_V1_4 *)fw_info);

	अन्यथा अगर ((fw_info->ucTableFormatRevision == 2)
		 && (le16_to_cpu(fw_info->usStructureSize) >= माप(ATOM_FIRMWARE_INFO_V2_1)))
		result = init_overdrive_limits_V2_1(hwmgr,
				घातerplay_table,
				(स्थिर ATOM_FIRMWARE_INFO_V2_1 *)fw_info);

	वापस result;
पूर्ण

अटल पूर्णांक get_uvd_घड़ी_voltage_limit_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_uvd_घड़ी_voltage_dependency_table **ptable,
		स्थिर ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table *table,
		स्थिर UVDClockInfoArray *array)
अणु
	अचिन्हित दीर्घ i;
	काष्ठा phm_uvd_घड़ी_voltage_dependency_table *uvd_table;

	uvd_table = kzalloc(काष्ठा_size(uvd_table, entries, table->numEntries),
			    GFP_KERNEL);
	अगर (!uvd_table)
		वापस -ENOMEM;

	uvd_table->count = table->numEntries;

	क्रम (i = 0; i < table->numEntries; i++) अणु
		स्थिर UVDClockInfo *entry =
			&array->entries[table->entries[i].ucUVDClockInfoIndex];
		uvd_table->entries[i].v = (अचिन्हित दीर्घ)le16_to_cpu(table->entries[i].usVoltage);
		uvd_table->entries[i].vclk = ((अचिन्हित दीर्घ)entry->ucVClkHigh << 16)
					 | le16_to_cpu(entry->usVClkLow);
		uvd_table->entries[i].dclk = ((अचिन्हित दीर्घ)entry->ucDClkHigh << 16)
					 | le16_to_cpu(entry->usDClkLow);
	पूर्ण

	*ptable = uvd_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_vce_घड़ी_voltage_limit_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_vce_घड़ी_voltage_dependency_table **ptable,
		स्थिर ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *table,
		स्थिर VCEClockInfoArray    *array)
अणु
	अचिन्हित दीर्घ i;
	काष्ठा phm_vce_घड़ी_voltage_dependency_table *vce_table = शून्य;

	vce_table = kzalloc(काष्ठा_size(vce_table, entries, table->numEntries),
			    GFP_KERNEL);
	अगर (!vce_table)
		वापस -ENOMEM;

	vce_table->count = table->numEntries;
	क्रम (i = 0; i < table->numEntries; i++) अणु
		स्थिर VCEClockInfo *entry = &array->entries[table->entries[i].ucVCEClockInfoIndex];

		vce_table->entries[i].v = (अचिन्हित दीर्घ)le16_to_cpu(table->entries[i].usVoltage);
		vce_table->entries[i].evclk = ((अचिन्हित दीर्घ)entry->ucEVClkHigh << 16)
					| le16_to_cpu(entry->usEVClkLow);
		vce_table->entries[i].ecclk = ((अचिन्हित दीर्घ)entry->ucECClkHigh << 16)
					| le16_to_cpu(entry->usECClkLow);
	पूर्ण

	*ptable = vce_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_samu_घड़ी_voltage_limit_table(काष्ठा pp_hwmgr *hwmgr,
		 काष्ठा phm_samu_घड़ी_voltage_dependency_table **ptable,
		 स्थिर ATOM_PPLIB_SAMClk_Voltage_Limit_Table *table)
अणु
	अचिन्हित दीर्घ i;
	काष्ठा phm_samu_घड़ी_voltage_dependency_table *samu_table;

	samu_table = kzalloc(काष्ठा_size(samu_table, entries, table->numEntries),
			     GFP_KERNEL);
	अगर (!samu_table)
		वापस -ENOMEM;

	samu_table->count = table->numEntries;

	क्रम (i = 0; i < table->numEntries; i++) अणु
		samu_table->entries[i].v = (अचिन्हित दीर्घ)le16_to_cpu(table->entries[i].usVoltage);
		samu_table->entries[i].samclk = ((अचिन्हित दीर्घ)table->entries[i].ucSAMClockHigh << 16)
					 | le16_to_cpu(table->entries[i].usSAMClockLow);
	पूर्ण

	*ptable = samu_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_acp_घड़ी_voltage_limit_table(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_acp_घड़ी_voltage_dependency_table **ptable,
		स्थिर ATOM_PPLIB_ACPClk_Voltage_Limit_Table *table)
अणु
	अचिन्हित दीर्घ i;
	काष्ठा phm_acp_घड़ी_voltage_dependency_table *acp_table;

	acp_table = kzalloc(काष्ठा_size(acp_table, entries, table->numEntries),
			    GFP_KERNEL);
	अगर (!acp_table)
		वापस -ENOMEM;

	acp_table->count = (अचिन्हित दीर्घ)table->numEntries;

	क्रम (i = 0; i < table->numEntries; i++) अणु
		acp_table->entries[i].v = (अचिन्हित दीर्घ)le16_to_cpu(table->entries[i].usVoltage);
		acp_table->entries[i].acpclk = ((अचिन्हित दीर्घ)table->entries[i].ucACPClockHigh << 16)
					 | le16_to_cpu(table->entries[i].usACPClockLow);
	पूर्ण

	*ptable = acp_table;

	वापस 0;
पूर्ण

अटल पूर्णांक init_घड़ी_voltage_dependency(काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	ATOM_PPLIB_Clock_Voltage_Dependency_Table *table;
	ATOM_PPLIB_Clock_Voltage_Limit_Table *limit_table;
	पूर्णांक result = 0;

	uपूर्णांक16_t vce_घड़ी_info_array_offset;
	uपूर्णांक16_t uvd_घड़ी_info_array_offset;
	uपूर्णांक16_t table_offset;

	hwmgr->dyn_state.vddc_dependency_on_sclk = शून्य;
	hwmgr->dyn_state.vddci_dependency_on_mclk = शून्य;
	hwmgr->dyn_state.vddc_dependency_on_mclk = शून्य;
	hwmgr->dyn_state.vddc_dep_on_dal_pwrl = शून्य;
	hwmgr->dyn_state.mvdd_dependency_on_mclk = शून्य;
	hwmgr->dyn_state.vce_घड़ी_voltage_dependency_table = शून्य;
	hwmgr->dyn_state.uvd_घड़ी_voltage_dependency_table = शून्य;
	hwmgr->dyn_state.samu_घड़ी_voltage_dependency_table = शून्य;
	hwmgr->dyn_state.acp_घड़ी_voltage_dependency_table = शून्य;
	hwmgr->dyn_state.ppm_parameter_table = शून्य;
	hwmgr->dyn_state.vdd_gfx_dependency_on_sclk = शून्य;

	vce_घड़ी_info_array_offset = get_vce_घड़ी_info_array_offset(
						hwmgr, घातerplay_table);
	table_offset = get_vce_घड़ी_voltage_limit_table_offset(hwmgr,
						घातerplay_table);
	अगर (vce_घड़ी_info_array_offset > 0 && table_offset > 0) अणु
		स्थिर VCEClockInfoArray *array = (स्थिर VCEClockInfoArray *)
				(((अचिन्हित दीर्घ) घातerplay_table) +
				vce_घड़ी_info_array_offset);
		स्थिर ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *table =
				(स्थिर ATOM_PPLIB_VCE_Clock_Voltage_Limit_Table *)
				(((अचिन्हित दीर्घ) घातerplay_table) + table_offset);
		result = get_vce_घड़ी_voltage_limit_table(hwmgr,
				&hwmgr->dyn_state.vce_घड़ी_voltage_dependency_table,
				table, array);
	पूर्ण

	uvd_घड़ी_info_array_offset = get_uvd_घड़ी_info_array_offset(hwmgr, घातerplay_table);
	table_offset = get_uvd_घड़ी_voltage_limit_table_offset(hwmgr, घातerplay_table);

	अगर (uvd_घड़ी_info_array_offset > 0 && table_offset > 0) अणु
		स्थिर UVDClockInfoArray *array = (स्थिर UVDClockInfoArray *)
				(((अचिन्हित दीर्घ) घातerplay_table) +
				uvd_घड़ी_info_array_offset);
		स्थिर ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table *ptable =
				(स्थिर ATOM_PPLIB_UVD_Clock_Voltage_Limit_Table *)
				(((अचिन्हित दीर्घ) घातerplay_table) + table_offset);
		result = get_uvd_घड़ी_voltage_limit_table(hwmgr,
				&hwmgr->dyn_state.uvd_घड़ी_voltage_dependency_table, ptable, array);
	पूर्ण

	table_offset = get_samu_घड़ी_voltage_limit_table_offset(hwmgr,
							    घातerplay_table);

	अगर (table_offset > 0) अणु
		स्थिर ATOM_PPLIB_SAMClk_Voltage_Limit_Table *ptable =
				(स्थिर ATOM_PPLIB_SAMClk_Voltage_Limit_Table *)
				(((अचिन्हित दीर्घ) घातerplay_table) + table_offset);
		result = get_samu_घड़ी_voltage_limit_table(hwmgr,
				&hwmgr->dyn_state.samu_घड़ी_voltage_dependency_table, ptable);
	पूर्ण

	table_offset = get_acp_घड़ी_voltage_limit_table_offset(hwmgr,
							     घातerplay_table);

	अगर (table_offset > 0) अणु
		स्थिर ATOM_PPLIB_ACPClk_Voltage_Limit_Table *ptable =
				(स्थिर ATOM_PPLIB_ACPClk_Voltage_Limit_Table *)
				(((अचिन्हित दीर्घ) घातerplay_table) + table_offset);
		result = get_acp_घड़ी_voltage_limit_table(hwmgr,
				&hwmgr->dyn_state.acp_घड़ी_voltage_dependency_table, ptable);
	पूर्ण

	table_offset = get_cacp_tdp_table_offset(hwmgr, घातerplay_table);
	अगर (table_offset > 0) अणु
		UCHAR rev_id = *(UCHAR *)(((अचिन्हित दीर्घ)घातerplay_table) + table_offset);

		अगर (rev_id > 0) अणु
			स्थिर ATOM_PPLIB_POWERTUNE_Table_V1 *tune_table =
				(स्थिर ATOM_PPLIB_POWERTUNE_Table_V1 *)
				(((अचिन्हित दीर्घ) घातerplay_table) + table_offset);
			result = get_cac_tdp_table(hwmgr, &hwmgr->dyn_state.cac_dtp_table,
				&tune_table->घातer_tune_table,
				le16_to_cpu(tune_table->usMaximumPowerDeliveryLimit));
			hwmgr->dyn_state.cac_dtp_table->usDefaultTargetOperatingTemp =
				le16_to_cpu(tune_table->usTjMax);
		पूर्ण अन्यथा अणु
			स्थिर ATOM_PPLIB_POWERTUNE_Table *tune_table =
				(स्थिर ATOM_PPLIB_POWERTUNE_Table *)
				(((अचिन्हित दीर्घ) घातerplay_table) + table_offset);
			result = get_cac_tdp_table(hwmgr,
				&hwmgr->dyn_state.cac_dtp_table,
				&tune_table->घातer_tune_table, 255);
		पूर्ण
	पूर्ण

	अगर (le16_to_cpu(घातerplay_table->usTableSize) >=
		माप(ATOM_PPLIB_POWERPLAYTABLE4)) अणु
		स्थिर ATOM_PPLIB_POWERPLAYTABLE4 *घातerplay_table4 =
				(स्थिर ATOM_PPLIB_POWERPLAYTABLE4 *)घातerplay_table;
		अगर (0 != घातerplay_table4->usVddcDependencyOnSCLKOffset) अणु
			table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(((अचिन्हित दीर्घ) घातerplay_table4) +
				 le16_to_cpu(घातerplay_table4->usVddcDependencyOnSCLKOffset));
			result = get_घड़ी_voltage_dependency_table(hwmgr,
				&hwmgr->dyn_state.vddc_dependency_on_sclk, table);
		पूर्ण

		अगर (result == 0 && (0 != घातerplay_table4->usVddciDependencyOnMCLKOffset)) अणु
			table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(((अचिन्हित दीर्घ) घातerplay_table4) +
				 le16_to_cpu(घातerplay_table4->usVddciDependencyOnMCLKOffset));
			result = get_घड़ी_voltage_dependency_table(hwmgr,
				&hwmgr->dyn_state.vddci_dependency_on_mclk, table);
		पूर्ण

		अगर (result == 0 && (0 != घातerplay_table4->usVddcDependencyOnMCLKOffset)) अणु
			table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(((अचिन्हित दीर्घ) घातerplay_table4) +
				 le16_to_cpu(घातerplay_table4->usVddcDependencyOnMCLKOffset));
			result = get_घड़ी_voltage_dependency_table(hwmgr,
				&hwmgr->dyn_state.vddc_dependency_on_mclk, table);
		पूर्ण

		अगर (result == 0 && (0 != घातerplay_table4->usMaxClockVoltageOnDCOffset)) अणु
			limit_table = (ATOM_PPLIB_Clock_Voltage_Limit_Table *)
				(((अचिन्हित दीर्घ) घातerplay_table4) +
				 le16_to_cpu(घातerplay_table4->usMaxClockVoltageOnDCOffset));
			result = get_घड़ी_voltage_limit(hwmgr,
				&hwmgr->dyn_state.max_घड़ी_voltage_on_dc, limit_table);
		पूर्ण

		अगर (result == 0 && (शून्य != hwmgr->dyn_state.vddc_dependency_on_mclk) &&
			(0 != hwmgr->dyn_state.vddc_dependency_on_mclk->count))
			result = get_valid_clk(hwmgr, &hwmgr->dyn_state.valid_mclk_values,
					hwmgr->dyn_state.vddc_dependency_on_mclk);

		अगर(result == 0 && (शून्य != hwmgr->dyn_state.vddc_dependency_on_sclk) &&
			(0 != hwmgr->dyn_state.vddc_dependency_on_sclk->count))
			result = get_valid_clk(hwmgr,
				&hwmgr->dyn_state.valid_sclk_values,
				hwmgr->dyn_state.vddc_dependency_on_sclk);

		अगर (result == 0 && (0 != घातerplay_table4->usMvddDependencyOnMCLKOffset)) अणु
			table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
				(((अचिन्हित दीर्घ) घातerplay_table4) +
				 le16_to_cpu(घातerplay_table4->usMvddDependencyOnMCLKOffset));
			result = get_घड़ी_voltage_dependency_table(hwmgr,
				&hwmgr->dyn_state.mvdd_dependency_on_mclk, table);
		पूर्ण
	पूर्ण

	table_offset = get_sclk_vdd_gfx_घड़ी_voltage_dependency_table_offset(hwmgr,
								घातerplay_table);

	अगर (table_offset > 0) अणु
		table = (ATOM_PPLIB_Clock_Voltage_Dependency_Table *)
			(((अचिन्हित दीर्घ) घातerplay_table) + table_offset);
		result = get_घड़ी_voltage_dependency_table(hwmgr,
			&hwmgr->dyn_state.vdd_gfx_dependency_on_sclk, table);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक get_cac_leakage_table(काष्ठा pp_hwmgr *hwmgr,
				 काष्ठा phm_cac_leakage_table **ptable,
				स्थिर ATOM_PPLIB_CAC_Leakage_Table *table)
अणु
	काष्ठा phm_cac_leakage_table  *cac_leakage_table;
	अचिन्हित दीर्घ i;

	अगर (!hwmgr || !table || !ptable)
		वापस -EINVAL;

	cac_leakage_table = kzalloc(काष्ठा_size(cac_leakage_table, entries, table->ucNumEntries),
				    GFP_KERNEL);
	अगर (!cac_leakage_table)
		वापस -ENOMEM;

	cac_leakage_table->count = (ULONG)table->ucNumEntries;

	क्रम (i = 0; i < cac_leakage_table->count; i++) अणु
		अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_EVV)) अणु
			cac_leakage_table->entries[i].Vddc1 = le16_to_cpu(table->entries[i].usVddc1);
			cac_leakage_table->entries[i].Vddc2 = le16_to_cpu(table->entries[i].usVddc2);
			cac_leakage_table->entries[i].Vddc3 = le16_to_cpu(table->entries[i].usVddc3);
		पूर्ण अन्यथा अणु
			cac_leakage_table->entries[i].Vddc    = le16_to_cpu(table->entries[i].usVddc);
			cac_leakage_table->entries[i].Leakage = le32_to_cpu(table->entries[i].ulLeakageValue);
		पूर्ण
	पूर्ण

	*ptable = cac_leakage_table;

	वापस 0;
पूर्ण

अटल पूर्णांक get_platक्रमm_घातer_management_table(काष्ठा pp_hwmgr *hwmgr,
			ATOM_PPLIB_PPM_Table *atom_ppm_table)
अणु
	काष्ठा phm_ppm_table *ptr = kzalloc(माप(काष्ठा phm_ppm_table), GFP_KERNEL);

	अगर (शून्य == ptr)
		वापस -ENOMEM;

	ptr->ppm_design            = atom_ppm_table->ucPpmDesign;
	ptr->cpu_core_number        = le16_to_cpu(atom_ppm_table->usCpuCoreNumber);
	ptr->platक्रमm_tdp          = le32_to_cpu(atom_ppm_table->ulPlatक्रमmTDP);
	ptr->small_ac_platक्रमm_tdp   = le32_to_cpu(atom_ppm_table->ulSmallACPlatक्रमmTDP);
	ptr->platक्रमm_tdc          = le32_to_cpu(atom_ppm_table->ulPlatक्रमmTDC);
	ptr->small_ac_platक्रमm_tdc   = le32_to_cpu(atom_ppm_table->ulSmallACPlatक्रमmTDC);
	ptr->apu_tdp               = le32_to_cpu(atom_ppm_table->ulApuTDP);
	ptr->dgpu_tdp              = le32_to_cpu(atom_ppm_table->ulDGpuTDP);
	ptr->dgpu_ulv_घातer         = le32_to_cpu(atom_ppm_table->ulDGpuUlvPower);
	ptr->tj_max                = le32_to_cpu(atom_ppm_table->ulTjmax);
	hwmgr->dyn_state.ppm_parameter_table = ptr;

	वापस 0;
पूर्ण

अटल पूर्णांक init_dpm2_parameters(काष्ठा pp_hwmgr *hwmgr,
			स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	पूर्णांक result = 0;

	अगर (le16_to_cpu(घातerplay_table->usTableSize) >=
	    माप(ATOM_PPLIB_POWERPLAYTABLE5)) अणु
		स्थिर  ATOM_PPLIB_POWERPLAYTABLE5 *ptable5 =
				(स्थिर ATOM_PPLIB_POWERPLAYTABLE5 *)घातerplay_table;
		स्थिर  ATOM_PPLIB_POWERPLAYTABLE4 *ptable4 =
				(स्थिर ATOM_PPLIB_POWERPLAYTABLE4 *)
				(&ptable5->basicTable4);
		स्थिर  ATOM_PPLIB_POWERPLAYTABLE3 *ptable3 =
				(स्थिर ATOM_PPLIB_POWERPLAYTABLE3 *)
				(&ptable4->basicTable3);
		स्थिर  ATOM_PPLIB_EXTENDEDHEADER  *extended_header;
		uपूर्णांक16_t table_offset;
		ATOM_PPLIB_PPM_Table *atom_ppm_table;

		hwmgr->platक्रमm_descriptor.TDPLimit     = le32_to_cpu(ptable5->ulTDPLimit);
		hwmgr->platक्रमm_descriptor.nearTDPLimit = le32_to_cpu(ptable5->ulNearTDPLimit);

		hwmgr->platक्रमm_descriptor.TDPODLimit   = le16_to_cpu(ptable5->usTDPODLimit);
		hwmgr->platक्रमm_descriptor.TDPAdjusपंचांगent = 0;

		hwmgr->platक्रमm_descriptor.VidAdjusपंचांगent = 0;
		hwmgr->platक्रमm_descriptor.VidAdjusपंचांगentPolarity = 0;
		hwmgr->platक्रमm_descriptor.VidMinLimit     = 0;
		hwmgr->platक्रमm_descriptor.VidMaxLimit     = 1500000;
		hwmgr->platक्रमm_descriptor.VidStep         = 6250;

		hwmgr->platक्रमm_descriptor.nearTDPLimitAdjusted = le32_to_cpu(ptable5->ulNearTDPLimit);

		अगर (hwmgr->platक्रमm_descriptor.TDPODLimit != 0)
			phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_PowerControl);

		hwmgr->platक्रमm_descriptor.SQRampingThreshold = le32_to_cpu(ptable5->ulSQRampingThreshold);

		hwmgr->platक्रमm_descriptor.CACLeakage = le32_to_cpu(ptable5->ulCACLeakage);

		hwmgr->dyn_state.cac_leakage_table = शून्य;

		अगर (0 != ptable5->usCACLeakageTableOffset) अणु
			स्थिर ATOM_PPLIB_CAC_Leakage_Table *pCAC_leakage_table =
				(ATOM_PPLIB_CAC_Leakage_Table *)(((अचिन्हित दीर्घ)ptable5) +
				le16_to_cpu(ptable5->usCACLeakageTableOffset));
			result = get_cac_leakage_table(hwmgr,
				&hwmgr->dyn_state.cac_leakage_table, pCAC_leakage_table);
		पूर्ण

		hwmgr->platक्रमm_descriptor.LoadLineSlope = le16_to_cpu(ptable5->usLoadLineSlope);

		hwmgr->dyn_state.ppm_parameter_table = शून्य;

		अगर (0 != ptable3->usExtendendedHeaderOffset) अणु
			extended_header = (स्थिर ATOM_PPLIB_EXTENDEDHEADER *)
					(((अचिन्हित दीर्घ)घातerplay_table) +
					le16_to_cpu(ptable3->usExtendendedHeaderOffset));
			अगर ((extended_header->usPPMTableOffset > 0) &&
				le16_to_cpu(extended_header->usSize) >=
				    SIZE_OF_ATOM_PPLIB_EXTENDEDHEADER_V5) अणु
				table_offset = le16_to_cpu(extended_header->usPPMTableOffset);
				atom_ppm_table = (ATOM_PPLIB_PPM_Table *)
					(((अचिन्हित दीर्घ)घातerplay_table) + table_offset);
				अगर (0 == get_platक्रमm_घातer_management_table(hwmgr, atom_ppm_table))
					phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
						PHM_Platक्रमmCaps_EnablePlatक्रमmPowerManagement);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक init_phase_shedding_table(काष्ठा pp_hwmgr *hwmgr,
		स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table)
अणु
	अगर (le16_to_cpu(घातerplay_table->usTableSize) >=
	    माप(ATOM_PPLIB_POWERPLAYTABLE4)) अणु
		स्थिर ATOM_PPLIB_POWERPLAYTABLE4 *घातerplay_table4 =
				(स्थिर ATOM_PPLIB_POWERPLAYTABLE4 *)घातerplay_table;

		अगर (0 != घातerplay_table4->usVddcPhaseShedLimitsTableOffset) अणु
			स्थिर ATOM_PPLIB_PhaseSheddingLimits_Table *ptable =
				(ATOM_PPLIB_PhaseSheddingLimits_Table *)
				(((अचिन्हित दीर्घ)घातerplay_table4) +
				le16_to_cpu(घातerplay_table4->usVddcPhaseShedLimitsTableOffset));
			काष्ठा phm_phase_shedding_limits_table *table;
			अचिन्हित दीर्घ i;


			table = kzalloc(काष्ठा_size(table, entries, ptable->ucNumEntries),
					GFP_KERNEL);
			अगर (!table)
				वापस -ENOMEM;

			table->count = (अचिन्हित दीर्घ)ptable->ucNumEntries;

			क्रम (i = 0; i < table->count; i++) अणु
				table->entries[i].Voltage = (अचिन्हित दीर्घ)le16_to_cpu(ptable->entries[i].usVoltage);
				table->entries[i].Sclk    = ((अचिन्हित दीर्घ)ptable->entries[i].ucSclkHigh << 16)
							| le16_to_cpu(ptable->entries[i].usSclkLow);
				table->entries[i].Mclk    = ((अचिन्हित दीर्घ)ptable->entries[i].ucMclkHigh << 16)
							| le16_to_cpu(ptable->entries[i].usMclkLow);
			पूर्ण
			hwmgr->dyn_state.vddc_phase_shed_limits_table = table;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_number_of_vce_state_table_entries(
						  काष्ठा pp_hwmgr *hwmgr)
अणु
	स्थिर ATOM_PPLIB_POWERPLAYTABLE *table =
					     get_घातerplay_table(hwmgr);
	स्थिर ATOM_PPLIB_VCE_State_Table *vce_table =
				    get_vce_state_table(hwmgr, table);

	अगर (vce_table)
		वापस vce_table->numEntries;

	वापस 0;
पूर्ण

अटल पूर्णांक get_vce_state_table_entry(काष्ठा pp_hwmgr *hwmgr,
							अचिन्हित दीर्घ i,
							काष्ठा amd_vce_state *vce_state,
							व्योम **घड़ी_info,
							अचिन्हित दीर्घ *flag)
अणु
	स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table = get_घातerplay_table(hwmgr);

	स्थिर ATOM_PPLIB_VCE_State_Table *vce_state_table = get_vce_state_table(hwmgr, घातerplay_table);

	अचिन्हित लघु vce_घड़ी_info_array_offset = get_vce_घड़ी_info_array_offset(hwmgr, घातerplay_table);

	स्थिर VCEClockInfoArray *vce_घड़ी_info_array = (स्थिर VCEClockInfoArray *)(((अचिन्हित दीर्घ) घातerplay_table) + vce_घड़ी_info_array_offset);

	स्थिर ClockInfoArray *घड़ी_arrays = (ClockInfoArray *)(((अचिन्हित दीर्घ)घातerplay_table) +
								le16_to_cpu(घातerplay_table->usClockInfoArrayOffset));

	स्थिर ATOM_PPLIB_VCE_State_Record *record = &vce_state_table->entries[i];

	स्थिर VCEClockInfo *vce_घड़ी_info = &vce_घड़ी_info_array->entries[record->ucVCEClockInfoIndex];

	अचिन्हित दीर्घ घड़ीInfoIndex = record->ucClockInfoIndex & 0x3F;

	*flag = (record->ucClockInfoIndex >> NUM_BITS_CLOCK_INFO_ARRAY_INDEX);

	vce_state->evclk = ((uपूर्णांक32_t)vce_घड़ी_info->ucEVClkHigh << 16) | le16_to_cpu(vce_घड़ी_info->usEVClkLow);
	vce_state->ecclk = ((uपूर्णांक32_t)vce_घड़ी_info->ucECClkHigh << 16) | le16_to_cpu(vce_घड़ी_info->usECClkLow);

	*घड़ी_info = (व्योम *)((अचिन्हित दीर्घ)(घड़ी_arrays->घड़ीInfo) + (घड़ीInfoIndex * घड़ी_arrays->ucEntrySize));

	वापस 0;
पूर्ण


अटल पूर्णांक pp_tables_initialize(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	स्थिर ATOM_PPLIB_POWERPLAYTABLE *घातerplay_table;

	अगर (hwmgr->chip_id == CHIP_RAVEN)
		वापस 0;

	hwmgr->need_pp_table_upload = true;

	घातerplay_table = get_घातerplay_table(hwmgr);

	result = init_घातerplay_tables(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_powerplay_tables failed", वापस result);

	result = set_platक्रमm_caps(hwmgr,
				le32_to_cpu(घातerplay_table->ulPlatक्रमmCaps));

	PP_ASSERT_WITH_CODE((result == 0),
			    "set_platform_caps failed", वापस result);

	result = init_thermal_controller(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_thermal_controller failed", वापस result);

	result = init_overdrive_limits(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_overdrive_limits failed", वापस result);

	result = init_घड़ी_voltage_dependency(hwmgr,
					       घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_clock_voltage_dependency failed", वापस result);

	result = init_dpm2_parameters(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_dpm2_parameters failed", वापस result);

	result = init_phase_shedding_table(hwmgr, घातerplay_table);

	PP_ASSERT_WITH_CODE((result == 0),
			    "init_phase_shedding_table failed", वापस result);

	वापस result;
पूर्ण

अटल पूर्णांक pp_tables_uninitialize(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (hwmgr->chip_id == CHIP_RAVEN)
		वापस 0;

	kमुक्त(hwmgr->dyn_state.vddc_dependency_on_sclk);
	hwmgr->dyn_state.vddc_dependency_on_sclk = शून्य;

	kमुक्त(hwmgr->dyn_state.vddci_dependency_on_mclk);
	hwmgr->dyn_state.vddci_dependency_on_mclk = शून्य;

	kमुक्त(hwmgr->dyn_state.vddc_dependency_on_mclk);
	hwmgr->dyn_state.vddc_dependency_on_mclk = शून्य;

	kमुक्त(hwmgr->dyn_state.mvdd_dependency_on_mclk);
	hwmgr->dyn_state.mvdd_dependency_on_mclk = शून्य;

	kमुक्त(hwmgr->dyn_state.valid_mclk_values);
	hwmgr->dyn_state.valid_mclk_values = शून्य;

	kमुक्त(hwmgr->dyn_state.valid_sclk_values);
	hwmgr->dyn_state.valid_sclk_values = शून्य;

	kमुक्त(hwmgr->dyn_state.cac_leakage_table);
	hwmgr->dyn_state.cac_leakage_table = शून्य;

	kमुक्त(hwmgr->dyn_state.vddc_phase_shed_limits_table);
	hwmgr->dyn_state.vddc_phase_shed_limits_table = शून्य;

	kमुक्त(hwmgr->dyn_state.vce_घड़ी_voltage_dependency_table);
	hwmgr->dyn_state.vce_घड़ी_voltage_dependency_table = शून्य;

	kमुक्त(hwmgr->dyn_state.uvd_घड़ी_voltage_dependency_table);
	hwmgr->dyn_state.uvd_घड़ी_voltage_dependency_table = शून्य;

	kमुक्त(hwmgr->dyn_state.samu_घड़ी_voltage_dependency_table);
	hwmgr->dyn_state.samu_घड़ी_voltage_dependency_table = शून्य;

	kमुक्त(hwmgr->dyn_state.acp_घड़ी_voltage_dependency_table);
	hwmgr->dyn_state.acp_घड़ी_voltage_dependency_table = शून्य;

	kमुक्त(hwmgr->dyn_state.cac_dtp_table);
	hwmgr->dyn_state.cac_dtp_table = शून्य;

	kमुक्त(hwmgr->dyn_state.ppm_parameter_table);
	hwmgr->dyn_state.ppm_parameter_table = शून्य;

	kमुक्त(hwmgr->dyn_state.vdd_gfx_dependency_on_sclk);
	hwmgr->dyn_state.vdd_gfx_dependency_on_sclk = शून्य;

	वापस 0;
पूर्ण

स्थिर काष्ठा pp_table_func pptable_funcs = अणु
	.pptable_init = pp_tables_initialize,
	.pptable_fini = pp_tables_uninitialize,
	.pptable_get_number_of_vce_state_table_entries =
				get_number_of_vce_state_table_entries,
	.pptable_get_vce_state_table_entry =
						get_vce_state_table_entry,
पूर्ण;

