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

#अगर_अघोषित PP_ATOMFWCTRL_H
#घोषणा PP_ATOMFWCTRL_H

#समावेश "hwmgr.h"

प्रकार क्रमागत atom_smu9_syspll0_घड़ी_id BIOS_CLKID;

#घोषणा GetIndexIntoMasterCmdTable(FieldName) \
	(((अक्षर*)(&((काष्ठा atom_master_list_of_command_functions_v2_1*)0)->FieldName)-(अक्षर*)0)/माप(uपूर्णांक16_t))
#घोषणा GetIndexIntoMasterDataTable(FieldName) \
	(((अक्षर*)(&((काष्ठा atom_master_list_of_data_tables_v2_1*)0)->FieldName)-(अक्षर*)0)/माप(uपूर्णांक16_t))

#घोषणा PP_ATOMFWCTRL_MAX_VOLTAGE_ENTRIES 32

काष्ठा pp_atomfwctrl_voltage_table_entry अणु
	uपूर्णांक16_t value;
	uपूर्णांक32_t  smio_low;
पूर्ण;

काष्ठा pp_atomfwctrl_voltage_table अणु
	uपूर्णांक32_t count;
	uपूर्णांक32_t mask_low;
	uपूर्णांक32_t phase_delay;
	uपूर्णांक8_t psi0_enable;
	uपूर्णांक8_t psi1_enable;
	uपूर्णांक8_t max_vid_step;
	uपूर्णांक8_t telemetry_offset;
	uपूर्णांक8_t telemetry_slope;
	काष्ठा pp_atomfwctrl_voltage_table_entry entries[PP_ATOMFWCTRL_MAX_VOLTAGE_ENTRIES];
पूर्ण;

काष्ठा pp_atomfwctrl_gpio_pin_assignment अणु
	uपूर्णांक16_t us_gpio_pin_aindex;
	uपूर्णांक8_t uc_gpio_pin_bit_shअगरt;
पूर्ण;

काष्ठा pp_atomfwctrl_घड़ी_भागiders_soc15 अणु
	uपूर्णांक32_t   ulClock;           /* the actual घड़ी */
	uपूर्णांक32_t   ulDid;             /* DFS भागider */
	uपूर्णांक32_t   ulPll_fb_mult;     /* Feedback Multiplier:  bit 8:0 पूर्णांक, bit 15:12 post_भाग, bit 31:16 frac */
	uपूर्णांक32_t   ulPll_ss_fbsmult;  /* Spपढ़ो FB Multiplier: bit 8:0 पूर्णांक, bit 31:16 frac */
	uपूर्णांक16_t   usPll_ss_slew_frac;
	uपूर्णांक8_t    ucPll_ss_enable;
	uपूर्णांक8_t    ucReserve;
	uपूर्णांक32_t   ulReserve[2];
पूर्ण;

काष्ठा pp_atomfwctrl_avfs_parameters अणु
	uपूर्णांक32_t   ulMaxVddc;
	uपूर्णांक32_t   ulMinVddc;

	uपूर्णांक32_t   ulMeanNsigmaAcontant0;
	uपूर्णांक32_t   ulMeanNsigmaAcontant1;
	uपूर्णांक32_t   ulMeanNsigmaAcontant2;
	uपूर्णांक16_t   usMeanNsigmaDcTolSigma;
	uपूर्णांक16_t   usMeanNsigmaPlatक्रमmMean;
	uपूर्णांक16_t   usMeanNsigmaPlatक्रमmSigma;
	uपूर्णांक32_t   ulGbVdroopTableCksoffA0;
	uपूर्णांक32_t   ulGbVdroopTableCksoffA1;
	uपूर्णांक32_t   ulGbVdroopTableCksoffA2;
	uपूर्णांक32_t   ulGbVdroopTableCksonA0;
	uपूर्णांक32_t   ulGbVdroopTableCksonA1;
	uपूर्णांक32_t   ulGbVdroopTableCksonA2;

	uपूर्णांक32_t   ulGbFuseTableCksoffM1;
	uपूर्णांक32_t   ulGbFuseTableCksoffM2;
	uपूर्णांक32_t   ulGbFuseTableCksoffB;

	uपूर्णांक32_t   ulGbFuseTableCksonM1;
	uपूर्णांक32_t   ulGbFuseTableCksonM2;
	uपूर्णांक32_t   ulGbFuseTableCksonB;

	uपूर्णांक8_t    ucEnableGbVdroopTableCkson;
	uपूर्णांक8_t    ucEnableGbFuseTableCkson;
	uपूर्णांक16_t   usPsmAgeComfactor;

	uपूर्णांक32_t   ulDispclk2GfxclkM1;
	uपूर्णांक32_t   ulDispclk2GfxclkM2;
	uपूर्णांक32_t   ulDispclk2GfxclkB;
	uपूर्णांक32_t   ulDcefclk2GfxclkM1;
	uपूर्णांक32_t   ulDcefclk2GfxclkM2;
	uपूर्णांक32_t   ulDcefclk2GfxclkB;
	uपूर्णांक32_t   ulPixelclk2GfxclkM1;
	uपूर्णांक32_t   ulPixelclk2GfxclkM2;
	uपूर्णांक32_t   ulPixelclk2GfxclkB;
	uपूर्णांक32_t   ulPhyclk2GfxclkM1;
	uपूर्णांक32_t   ulPhyclk2GfxclkM2;
	uपूर्णांक32_t   ulPhyclk2GfxclkB;
	uपूर्णांक32_t   ulAcgGbVdroopTableA0;
	uपूर्णांक32_t   ulAcgGbVdroopTableA1;
	uपूर्णांक32_t   ulAcgGbVdroopTableA2;
	uपूर्णांक32_t   ulAcgGbFuseTableM1;
	uपूर्णांक32_t   ulAcgGbFuseTableM2;
	uपूर्णांक32_t   ulAcgGbFuseTableB;
	uपूर्णांक32_t   ucAcgEnableGbVdroopTable;
	uपूर्णांक32_t   ucAcgEnableGbFuseTable;
पूर्ण;

काष्ठा pp_atomfwctrl_gpio_parameters अणु
	uपूर्णांक8_t   ucAcDcGpio;
	uपूर्णांक8_t   ucAcDcPolarity;
	uपूर्णांक8_t   ucVR0HotGpio;
	uपूर्णांक8_t   ucVR0HotPolarity;
	uपूर्णांक8_t   ucVR1HotGpio;
	uपूर्णांक8_t   ucVR1HotPolarity;
	uपूर्णांक8_t   ucFwCtfGpio;
	uपूर्णांक8_t   ucFwCtfPolarity;
पूर्ण;

काष्ठा pp_atomfwctrl_bios_boot_up_values अणु
	uपूर्णांक32_t   ulRevision;
	uपूर्णांक32_t   ulGfxClk;
	uपूर्णांक32_t   ulUClk;
	uपूर्णांक32_t   ulSocClk;
	uपूर्णांक32_t   ulDCEFClk;
	uपूर्णांक32_t   ulEClk;
	uपूर्णांक32_t   ulVClk;
	uपूर्णांक32_t   ulDClk;
	uपूर्णांक32_t   ulFClk;
	uपूर्णांक16_t   usVddc;
	uपूर्णांक16_t   usVddci;
	uपूर्णांक16_t   usMvddc;
	uपूर्णांक16_t   usVddGfx;
	uपूर्णांक8_t    ucCoolingID;
पूर्ण;

काष्ठा pp_atomfwctrl_smc_dpm_parameters
अणु
  uपूर्णांक8_t  liquid1_i2c_address;
  uपूर्णांक8_t  liquid2_i2c_address;
  uपूर्णांक8_t  vr_i2c_address;
  uपूर्णांक8_t  plx_i2c_address;
  uपूर्णांक8_t  liquid_i2c_linescl;
  uपूर्णांक8_t  liquid_i2c_linesda;
  uपूर्णांक8_t  vr_i2c_linescl;
  uपूर्णांक8_t  vr_i2c_linesda;
  uपूर्णांक8_t  plx_i2c_linescl;
  uपूर्णांक8_t  plx_i2c_linesda;
  uपूर्णांक8_t  vrsensorpresent;
  uपूर्णांक8_t  liquidsensorpresent;
  uपूर्णांक16_t maxvoltagestepgfx;
  uपूर्णांक16_t maxvoltagestepsoc;
  uपूर्णांक8_t  vddgfxvrmapping;
  uपूर्णांक8_t  vddsocvrmapping;
  uपूर्णांक8_t  vddmem0vrmapping;
  uपूर्णांक8_t  vddmem1vrmapping;
  uपूर्णांक8_t  gfxulvphasesheddingmask;
  uपूर्णांक8_t  soculvphasesheddingmask;

  uपूर्णांक16_t gfxmaxcurrent;
  uपूर्णांक8_t  gfxoffset;
  uपूर्णांक8_t  padding_telemetrygfx;
  uपूर्णांक16_t socmaxcurrent;
  uपूर्णांक8_t  socoffset;
  uपूर्णांक8_t  padding_telemetrysoc;
  uपूर्णांक16_t mem0maxcurrent;
  uपूर्णांक8_t  mem0offset;
  uपूर्णांक8_t  padding_telemetrymem0;
  uपूर्णांक16_t mem1maxcurrent;
  uपूर्णांक8_t  mem1offset;
  uपूर्णांक8_t  padding_telemetrymem1;

  uपूर्णांक8_t  acdcgpio;
  uपूर्णांक8_t  acdcpolarity;
  uपूर्णांक8_t  vr0hotgpio;
  uपूर्णांक8_t  vr0hotpolarity;
  uपूर्णांक8_t  vr1hotgpio;
  uपूर्णांक8_t  vr1hotpolarity;
  uपूर्णांक8_t  padding1;
  uपूर्णांक8_t  padding2;

  uपूर्णांक8_t  ledpin0;
  uपूर्णांक8_t  ledpin1;
  uपूर्णांक8_t  ledpin2;

	uपूर्णांक8_t  pllgfxclkspपढ़ोenabled;
	uपूर्णांक8_t  pllgfxclkspपढ़ोpercent;
	uपूर्णांक16_t pllgfxclkspपढ़ोfreq;

  uपूर्णांक8_t  uclkspपढ़ोenabled;
  uपूर्णांक8_t  uclkspपढ़ोpercent;
  uपूर्णांक16_t uclkspपढ़ोfreq;

  uपूर्णांक8_t socclkspपढ़ोenabled;
  uपूर्णांक8_t socclkspपढ़ोpercent;
  uपूर्णांक16_t socclkspपढ़ोfreq;

	uपूर्णांक8_t  acggfxclkspपढ़ोenabled;
	uपूर्णांक8_t  acggfxclkspपढ़ोpercent;
	uपूर्णांक16_t acggfxclkspपढ़ोfreq;

	uपूर्णांक8_t Vr2_I2C_address;
पूर्ण;

पूर्णांक pp_atomfwctrl_get_gpu_pll_भागiders_vega10(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t घड़ी_प्रकारype, uपूर्णांक32_t घड़ी_value,
		काष्ठा pp_atomfwctrl_घड़ी_भागiders_soc15 *भागiders);
पूर्णांक pp_atomfwctrl_enter_self_refresh(काष्ठा pp_hwmgr *hwmgr);
bool pp_atomfwctrl_get_pp_assign_pin(काष्ठा pp_hwmgr *hwmgr, स्थिर uपूर्णांक32_t pin_id,
		काष्ठा pp_atomfwctrl_gpio_pin_assignment *gpio_pin_assignment);

पूर्णांक pp_atomfwctrl_get_voltage_table_v4(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t voltage_type,
		uपूर्णांक8_t voltage_mode, काष्ठा pp_atomfwctrl_voltage_table *voltage_table);
bool pp_atomfwctrl_is_voltage_controlled_by_gpio_v4(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक8_t voltage_type, uपूर्णांक8_t voltage_mode);

पूर्णांक pp_atomfwctrl_get_avfs_inक्रमmation(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_atomfwctrl_avfs_parameters *param);
पूर्णांक pp_atomfwctrl_get_gpio_inक्रमmation(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_atomfwctrl_gpio_parameters *param);

पूर्णांक pp_atomfwctrl_get_vbios_bootup_values(काष्ठा pp_hwmgr *hwmgr,
			काष्ठा pp_atomfwctrl_bios_boot_up_values *boot_values);
पूर्णांक pp_atomfwctrl_get_smc_dpm_inक्रमmation(काष्ठा pp_hwmgr *hwmgr,
			काष्ठा pp_atomfwctrl_smc_dpm_parameters *param);
पूर्णांक pp_atomfwctrl_get_clk_inक्रमmation_by_clkid(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक8_t clk_id, uपूर्णांक8_t syspll_id,
					uपूर्णांक32_t *frequency);

#पूर्ण_अगर

