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

#अगर_अघोषित PP_HWMGR_PPT_H
#घोषणा PP_HWMGR_PPT_H

#समावेश "hardwaremanager.h"
#समावेश "smumgr.h"
#समावेश "atom-types.h"

काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_record अणु
	uपूर्णांक32_t clk;
	uपूर्णांक8_t  vddInd;
	uपूर्णांक8_t  vddciInd;
	uपूर्णांक8_t  mvddInd;
	uपूर्णांक16_t vdd_offset;
	uपूर्णांक16_t vddc;
	uपूर्णांक16_t vddgfx;
	uपूर्णांक16_t vddci;
	uपूर्णांक16_t mvdd;
	uपूर्णांक8_t  phases;
	uपूर्णांक8_t  cks_enable;
	uपूर्णांक8_t  cks_voffset;
	uपूर्णांक32_t sclk_offset;
पूर्ण;

प्रकार काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_record phm_ppt_v1_घड़ी_voltage_dependency_record;

काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table अणु
	uपूर्णांक32_t count;                                            /* Number of entries. */
	phm_ppt_v1_घड़ी_voltage_dependency_record entries[];	   /* Dynamically allocate count entries. */
पूर्ण;

प्रकार काष्ठा phm_ppt_v1_घड़ी_voltage_dependency_table phm_ppt_v1_घड़ी_voltage_dependency_table;


/* Mulसमयdia Clock Voltage Dependency records and table */
काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_record अणु
	uपूर्णांक32_t  dclk;                                              /* UVD D-घड़ी */
	uपूर्णांक32_t  vclk;                                              /* UVD V-घड़ी */
	uपूर्णांक32_t  eclk;                                              /* VCE घड़ी */
	uपूर्णांक32_t  aclk;                                              /* ACP घड़ी */
	uपूर्णांक32_t  samघड़ी;                                          /* SAMU घड़ी */
	uपूर्णांक8_t	vddcInd;
	uपूर्णांक16_t vddgfx_offset;
	uपूर्णांक16_t vddc;
	uपूर्णांक16_t vddgfx;
	uपूर्णांक8_t phases;
पूर्ण;
प्रकार काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_record phm_ppt_v1_mm_घड़ी_voltage_dependency_record;

काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table अणु
	uपूर्णांक32_t count;													/* Number of entries. */
	phm_ppt_v1_mm_घड़ी_voltage_dependency_record entries[];		/* Dynamically allocate count entries. */
पूर्ण;
प्रकार काष्ठा phm_ppt_v1_mm_घड़ी_voltage_dependency_table phm_ppt_v1_mm_घड़ी_voltage_dependency_table;

काष्ठा phm_ppt_v1_voltage_lookup_record अणु
	uपूर्णांक16_t us_calculated;
	uपूर्णांक16_t us_vdd;												/* Base voltage */
	uपूर्णांक16_t us_cac_low;
	uपूर्णांक16_t us_cac_mid;
	uपूर्णांक16_t us_cac_high;
पूर्ण;
प्रकार काष्ठा phm_ppt_v1_voltage_lookup_record phm_ppt_v1_voltage_lookup_record;

काष्ठा phm_ppt_v1_voltage_lookup_table अणु
	uपूर्णांक32_t count;
	phm_ppt_v1_voltage_lookup_record entries[];    /* Dynamically allocate count entries. */
पूर्ण;
प्रकार काष्ठा phm_ppt_v1_voltage_lookup_table phm_ppt_v1_voltage_lookup_table;

/* PCIE records and Table */

काष्ठा phm_ppt_v1_pcie_record अणु
	uपूर्णांक8_t gen_speed;
	uपूर्णांक8_t lane_width;
	uपूर्णांक16_t usreserved;
	uपूर्णांक16_t reserved;
	uपूर्णांक32_t pcie_sclk;
पूर्ण;
प्रकार काष्ठा phm_ppt_v1_pcie_record phm_ppt_v1_pcie_record;

काष्ठा phm_ppt_v1_pcie_table अणु
	uपूर्णांक32_t count;                                            /* Number of entries. */
	phm_ppt_v1_pcie_record entries[];			   /* Dynamically allocate count entries. */
पूर्ण;
प्रकार काष्ठा phm_ppt_v1_pcie_table phm_ppt_v1_pcie_table;

काष्ठा phm_ppt_v1_gpio_table अणु
	uपूर्णांक8_t vrhot_triggered_sclk_dpm_index;           /* SCLK DPM level index to चयन to when VRHot is triggered */
पूर्ण;
प्रकार काष्ठा phm_ppt_v1_gpio_table phm_ppt_v1_gpio_table;

#पूर्ण_अगर

