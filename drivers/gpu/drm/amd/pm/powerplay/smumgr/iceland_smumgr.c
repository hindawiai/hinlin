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
 * Author: Huang Rui <ray.huang@amd.com>
 *
 */
#समावेश "pp_debug.h"
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/gfp.h>

#समावेश "smumgr.h"
#समावेश "iceland_smumgr.h"

#समावेश "ppsmc.h"

#समावेश "cgs_common.h"

#समावेश "smu7_dyn_defaults.h"
#समावेश "smu7_hwmgr.h"
#समावेश "hardwaremanager.h"
#समावेश "ppatomctrl.h"
#समावेश "atombios.h"
#समावेश "pppcielanes.h"
#समावेश "pp_endian.h"
#समावेश "processpptables.h"


#समावेश "smu/smu_7_1_1_d.h"
#समावेश "smu/smu_7_1_1_sh_mask.h"
#समावेश "smu71_discrete.h"

#समावेश "smu_ucode_xfer_vi.h"
#समावेश "gmc/gmc_8_1_d.h"
#समावेश "gmc/gmc_8_1_sh_mask.h"
#समावेश "bif/bif_5_0_d.h"
#समावेश "bif/bif_5_0_sh_mask.h"
#समावेश "dce/dce_10_0_d.h"
#समावेश "dce/dce_10_0_sh_mask.h"


#घोषणा ICELAND_SMC_SIZE               0x20000

#घोषणा POWERTUNE_DEFAULT_SET_MAX    1
#घोषणा MC_CG_ARB_FREQ_F1           0x0b
#घोषणा VDDC_VDDCI_DELTA            200

#घोषणा DEVICE_ID_VI_ICELAND_M_6900	0x6900
#घोषणा DEVICE_ID_VI_ICELAND_M_6901	0x6901
#घोषणा DEVICE_ID_VI_ICELAND_M_6902	0x6902
#घोषणा DEVICE_ID_VI_ICELAND_M_6903	0x6903

अटल स्थिर काष्ठा iceland_pt_शेषs शेषs_iceland = अणु
	/*
	 * sviLoadLIneEn, SviLoadLineVddC, TDC_VDDC_ThrottleReleaseLimitPerc,
	 * TDC_MAWt, TdcWaterfallCtl, DTEAmbientTempBase, DisplayCac, BAPM_TEMP_GRADIENT
	 */
	1, 0xF, 0xFD, 0x19, 5, 45, 0, 0xB0000,
	अणु 0x79,  0x253, 0x25D, 0xAE,  0x72,  0x80,  0x83,  0x86,  0x6F,  0xC8,  0xC9,  0xC9,  0x2F,  0x4D,  0x61  पूर्ण,
	अणु 0x17C, 0x172, 0x180, 0x1BC, 0x1B3, 0x1BD, 0x206, 0x200, 0x203, 0x25D, 0x25A, 0x255, 0x2C3, 0x2C5, 0x2B4 पूर्ण
पूर्ण;

/* 35W - XT, XTL */
अटल स्थिर काष्ठा iceland_pt_शेषs शेषs_icelandxt = अणु
	/*
	 * sviLoadLIneEn, SviLoadLineVddC,
	 * TDC_VDDC_ThrottleReleaseLimitPerc, TDC_MAWt,
	 * TdcWaterfallCtl, DTEAmbientTempBase, DisplayCac,
	 * BAPM_TEMP_GRADIENT
	 */
	1, 0xF, 0xFD, 0x19, 5, 45, 0, 0x0,
	अणु 0xA7,  0x0, 0x0, 0xB5,  0x0, 0x0, 0x9F,  0x0, 0x0, 0xD6,  0x0, 0x0, 0xD7,  0x0, 0x0पूर्ण,
	अणु 0x1EA, 0x0, 0x0, 0x224, 0x0, 0x0, 0x25E, 0x0, 0x0, 0x28E, 0x0, 0x0, 0x2AB, 0x0, 0x0पूर्ण
पूर्ण;

/* 25W - PRO, LE */
अटल स्थिर काष्ठा iceland_pt_शेषs शेषs_icelandpro = अणु
	/*
	 * sviLoadLIneEn, SviLoadLineVddC,
	 * TDC_VDDC_ThrottleReleaseLimitPerc, TDC_MAWt,
	 * TdcWaterfallCtl, DTEAmbientTempBase, DisplayCac,
	 * BAPM_TEMP_GRADIENT
	 */
	1, 0xF, 0xFD, 0x19, 5, 45, 0, 0x0,
	अणु 0xB7,  0x0, 0x0, 0xC3,  0x0, 0x0, 0xB5,  0x0, 0x0, 0xEA,  0x0, 0x0, 0xE6,  0x0, 0x0पूर्ण,
	अणु 0x1EA, 0x0, 0x0, 0x224, 0x0, 0x0, 0x25E, 0x0, 0x0, 0x28E, 0x0, 0x0, 0x2AB, 0x0, 0x0पूर्ण
पूर्ण;

अटल पूर्णांक iceland_start_smc(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				  SMC_SYSCON_RESET_CNTL, rst_reg, 0);

	वापस 0;
पूर्ण

अटल व्योम iceland_reset_smc(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				  SMC_SYSCON_RESET_CNTL,
				  rst_reg, 1);
पूर्ण


अटल व्योम iceland_stop_smc_घड़ी(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				  SMC_SYSCON_CLOCK_CNTL_0,
				  ck_disable, 1);
पूर्ण

अटल व्योम iceland_start_smc_घड़ी(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_WRITE_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				  SMC_SYSCON_CLOCK_CNTL_0,
				  ck_disable, 0);
पूर्ण

अटल पूर्णांक iceland_smu_start_smc(काष्ठा pp_hwmgr *hwmgr)
अणु
	/* set smc inकाष्ठा start poपूर्णांक at 0x0 */
	smu7_program_jump_on_start(hwmgr);

	/* enable smc घड़ी */
	iceland_start_smc_घड़ी(hwmgr);

	/* de-निश्चित reset */
	iceland_start_smc(hwmgr);

	PHM_WAIT_INसूचीECT_FIELD(hwmgr, SMC_IND, FIRMWARE_FLAGS,
				 INTERRUPTS_ENABLED, 1);

	वापस 0;
पूर्ण


अटल पूर्णांक iceland_upload_smc_firmware_data(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक32_t length, स्थिर uपूर्णांक8_t *src,
					uपूर्णांक32_t limit, uपूर्णांक32_t start_addr)
अणु
	uपूर्णांक32_t byte_count = length;
	uपूर्णांक32_t data;

	PP_ASSERT_WITH_CODE((limit >= byte_count), "SMC address is beyond the SMC RAM area.", वापस -EINVAL);

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMC_IND_INDEX_0, start_addr);
	PHM_WRITE_FIELD(hwmgr->device, SMC_IND_ACCESS_CNTL, AUTO_INCREMENT_IND_0, 1);

	जबतक (byte_count >= 4) अणु
		data = src[0] * 0x1000000 + src[1] * 0x10000 + src[2] * 0x100 + src[3];
		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMC_IND_DATA_0, data);
		src += 4;
		byte_count -= 4;
	पूर्ण

	PHM_WRITE_FIELD(hwmgr->device, SMC_IND_ACCESS_CNTL, AUTO_INCREMENT_IND_0, 0);

	PP_ASSERT_WITH_CODE((0 == byte_count), "SMC size must be divisible by 4.", वापस -EINVAL);

	वापस 0;
पूर्ण


अटल पूर्णांक iceland_smu_upload_firmware_image(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t val;
	काष्ठा cgs_firmware_info info = अणु0पूर्ण;

	अगर (hwmgr == शून्य || hwmgr->device == शून्य)
		वापस -EINVAL;

	/* load SMC firmware */
	cgs_get_firmware_info(hwmgr->device,
		smu7_convert_fw_type_to_cgs(UCODE_ID_SMU), &info);

	अगर (info.image_size & 3) अणु
		pr_err("[ powerplay ] SMC ucode is not 4 bytes aligned\n");
		वापस -EINVAL;
	पूर्ण

	अगर (info.image_size > ICELAND_SMC_SIZE) अणु
		pr_err("[ powerplay ] SMC address is beyond the SMC RAM area\n");
		वापस -EINVAL;
	पूर्ण
	hwmgr->smu_version = info.version;
	/* रुको क्रम smc boot up */
	PHM_WAIT_INसूचीECT_FIELD_UNEQUAL(hwmgr, SMC_IND,
					 RCU_UC_EVENTS, boot_seq_करोne, 0);

	/* clear firmware पूर्णांकerrupt enable flag */
	val = cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
				    ixSMC_SYSCON_MISC_CNTL);
	cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			       ixSMC_SYSCON_MISC_CNTL, val | 1);

	/* stop smc घड़ी */
	iceland_stop_smc_घड़ी(hwmgr);

	/* reset smc */
	iceland_reset_smc(hwmgr);
	iceland_upload_smc_firmware_data(hwmgr, info.image_size,
				(uपूर्णांक8_t *)info.kptr, ICELAND_SMC_SIZE,
				info.ucode_start_address);

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_request_smu_load_specअगरic_fw(काष्ठा pp_hwmgr *hwmgr,
						uपूर्णांक32_t firmwareType)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक iceland_start_smu(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा iceland_smumgr *priv = hwmgr->smu_backend;
	पूर्णांक result;

	अगर (!smu7_is_smc_ram_running(hwmgr)) अणु
		result = iceland_smu_upload_firmware_image(hwmgr);
		अगर (result)
			वापस result;

		iceland_smu_start_smc(hwmgr);
	पूर्ण

	/* Setup SoftRegsStart here to visit the रेजिस्टर UcodeLoadStatus
	 * to check fw loading state
	 */
	smu7_पढ़ो_smc_sram_dword(hwmgr,
			SMU71_FIRMWARE_HEADER_LOCATION +
			दुरत्व(SMU71_Firmware_Header, SoftRegisters),
			&(priv->smu7_data.soft_regs_start), 0x40000);

	result = smu7_request_smu_load_fw(hwmgr);

	वापस result;
पूर्ण

अटल पूर्णांक iceland_smu_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा iceland_smumgr *iceland_priv = शून्य;

	iceland_priv = kzalloc(माप(काष्ठा iceland_smumgr), GFP_KERNEL);

	अगर (iceland_priv == शून्य)
		वापस -ENOMEM;

	hwmgr->smu_backend = iceland_priv;

	अगर (smu7_init(hwmgr)) अणु
		kमुक्त(iceland_priv);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम iceland_initialize_घातer_tune_शेषs(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t dev_id;

	dev_id = adev->pdev->device;

	चयन (dev_id) अणु
	हाल DEVICE_ID_VI_ICELAND_M_6900:
	हाल DEVICE_ID_VI_ICELAND_M_6903:
		smu_data->घातer_tune_शेषs = &शेषs_icelandxt;
		अवरोध;

	हाल DEVICE_ID_VI_ICELAND_M_6901:
	हाल DEVICE_ID_VI_ICELAND_M_6902:
		smu_data->घातer_tune_शेषs = &शेषs_icelandpro;
		अवरोध;
	शेष:
		smu_data->घातer_tune_शेषs = &शेषs_iceland;
		pr_warn("Unknown V.I. Device ID.\n");
		अवरोध;
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक iceland_populate_svi_load_line(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा iceland_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;

	smu_data->घातer_tune_table.SviLoadLineEn = शेषs->svi_load_line_en;
	smu_data->घातer_tune_table.SviLoadLineVddC = शेषs->svi_load_line_vddc;
	smu_data->घातer_tune_table.SviLoadLineTrimVddC = 3;
	smu_data->घातer_tune_table.SviLoadLineOffsetVddC = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_tdc_limit(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक16_t tdc_limit;
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा iceland_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;

	tdc_limit = (uपूर्णांक16_t)(hwmgr->dyn_state.cac_dtp_table->usTDC * 256);
	smu_data->घातer_tune_table.TDC_VDDC_PkgLimit =
			CONVERT_FROM_HOST_TO_SMC_US(tdc_limit);
	smu_data->घातer_tune_table.TDC_VDDC_ThrottleReleaseLimitPerc =
			शेषs->tdc_vddc_throttle_release_limit_perc;
	smu_data->घातer_tune_table.TDC_MAWt = शेषs->tdc_mawt;

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_dw8(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t fuse_table_offset)
अणु
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा iceland_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;
	uपूर्णांक32_t temp;

	अगर (smu7_पढ़ो_smc_sram_dword(hwmgr,
			fuse_table_offset +
			दुरत्व(SMU71_Discrete_PmFuses, TdcWaterfallCtl),
			(uपूर्णांक32_t *)&temp, SMC_RAM_END))
		PP_ASSERT_WITH_CODE(false,
				"Attempt to read PmFuses.DW6 (SviLoadLineEn) from SMC Failed!",
				वापस -EINVAL);
	अन्यथा
		smu_data->घातer_tune_table.TdcWaterfallCtl = शेषs->tdc_waterfall_ctl;

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_temperature_scaler(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_gnb_lpml(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक i;
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);

	/* Currently not used. Set all to zero. */
	क्रम (i = 0; i < 8; i++)
		smu_data->घातer_tune_table.GnbLPML[i] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_bapm_vddc_base_leakage_sidd(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक16_t HiSidd = smu_data->घातer_tune_table.BapmVddCBaseLeakageHiSidd;
	uपूर्णांक16_t LoSidd = smu_data->घातer_tune_table.BapmVddCBaseLeakageLoSidd;
	काष्ठा phm_cac_tdp_table *cac_table = hwmgr->dyn_state.cac_dtp_table;

	HiSidd = (uपूर्णांक16_t)(cac_table->usHighCACLeakage / 100 * 256);
	LoSidd = (uपूर्णांक16_t)(cac_table->usLowCACLeakage / 100 * 256);

	smu_data->घातer_tune_table.BapmVddCBaseLeakageHiSidd =
			CONVERT_FROM_HOST_TO_SMC_US(HiSidd);
	smu_data->घातer_tune_table.BapmVddCBaseLeakageLoSidd =
			CONVERT_FROM_HOST_TO_SMC_US(LoSidd);

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_bapm_vddc_vid_sidd(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक i;
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक8_t *hi_vid = smu_data->घातer_tune_table.BapmVddCVidHiSidd;
	uपूर्णांक8_t *lo_vid = smu_data->घातer_tune_table.BapmVddCVidLoSidd;

	PP_ASSERT_WITH_CODE(शून्य != hwmgr->dyn_state.cac_leakage_table,
			    "The CAC Leakage table does not exist!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(hwmgr->dyn_state.cac_leakage_table->count <= 8,
			    "There should never be more than 8 entries for BapmVddcVid!!!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE(hwmgr->dyn_state.cac_leakage_table->count == hwmgr->dyn_state.vddc_dependency_on_sclk->count,
			    "CACLeakageTable->count and VddcDependencyOnSCLk->count not equal", वापस -EINVAL);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_EVV)) अणु
		क्रम (i = 0; (uपूर्णांक32_t) i < hwmgr->dyn_state.cac_leakage_table->count; i++) अणु
			lo_vid[i] = convert_to_vid(hwmgr->dyn_state.cac_leakage_table->entries[i].Vddc1);
			hi_vid[i] = convert_to_vid(hwmgr->dyn_state.cac_leakage_table->entries[i].Vddc2);
		पूर्ण
	पूर्ण अन्यथा अणु
		PP_ASSERT_WITH_CODE(false, "Iceland should always support EVV", वापस -EINVAL);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_vddc_vid(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक i;
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक8_t *vid = smu_data->घातer_tune_table.VddCVid;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	PP_ASSERT_WITH_CODE(data->vddc_voltage_table.count <= 8,
		"There should never be more than 8 entries for VddcVid!!!",
		वापस -EINVAL);

	क्रम (i = 0; i < (पूर्णांक)data->vddc_voltage_table.count; i++) अणु
		vid[i] = convert_to_vid(data->vddc_voltage_table.entries[i].value);
	पूर्ण

	वापस 0;
पूर्ण



अटल पूर्णांक iceland_populate_pm_fuses(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t pm_fuse_table_offset;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_PowerContainment)) अणु
		अगर (smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU71_Firmware_Header, PmFuseTable),
				&pm_fuse_table_offset, SMC_RAM_END))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to get pm_fuse_table_offset Failed!",
					वापस -EINVAL);

		/* DW0 - DW3 */
		अगर (iceland_populate_bapm_vddc_vid_sidd(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate bapm vddc vid Failed!",
					वापस -EINVAL);

		/* DW4 - DW5 */
		अगर (iceland_populate_vddc_vid(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate vddc vid Failed!",
					वापस -EINVAL);

		/* DW6 */
		अगर (iceland_populate_svi_load_line(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate SviLoadLine Failed!",
					वापस -EINVAL);
		/* DW7 */
		अगर (iceland_populate_tdc_limit(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate TDCLimit Failed!", वापस -EINVAL);
		/* DW8 */
		अगर (iceland_populate_dw8(hwmgr, pm_fuse_table_offset))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate TdcWaterfallCtl, "
					"LPMLTemperature Min and Max Failed!",
					वापस -EINVAL);

		/* DW9-DW12 */
		अगर (0 != iceland_populate_temperature_scaler(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate LPMLTemperatureScaler Failed!",
					वापस -EINVAL);

		/* DW13-DW16 */
		अगर (iceland_populate_gnb_lpml(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate GnbLPML Failed!",
					वापस -EINVAL);

		/* DW18 */
		अगर (iceland_populate_bapm_vddc_base_leakage_sidd(hwmgr))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to populate BapmVddCBaseLeakage Hi and Lo Sidd Failed!",
					वापस -EINVAL);

		अगर (smu7_copy_bytes_to_smc(hwmgr, pm_fuse_table_offset,
				(uपूर्णांक8_t *)&smu_data->घातer_tune_table,
				माप(काष्ठा SMU71_Discrete_PmFuses), SMC_RAM_END))
			PP_ASSERT_WITH_CODE(false,
					"Attempt to download PmFuseTable Failed!",
					वापस -EINVAL);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक iceland_get_dependency_volt_by_clk(काष्ठा pp_hwmgr *hwmgr,
	काष्ठा phm_घड़ी_voltage_dependency_table *allowed_घड़ी_voltage_table,
	uपूर्णांक32_t घड़ी, uपूर्णांक32_t *vol)
अणु
	uपूर्णांक32_t i = 0;

	/* घड़ी - voltage dependency table is empty table */
	अगर (allowed_घड़ी_voltage_table->count == 0)
		वापस -EINVAL;

	क्रम (i = 0; i < allowed_घड़ी_voltage_table->count; i++) अणु
		/* find first sclk bigger than request */
		अगर (allowed_घड़ी_voltage_table->entries[i].clk >= घड़ी) अणु
			*vol = allowed_घड़ी_voltage_table->entries[i].v;
			वापस 0;
		पूर्ण
	पूर्ण

	/* sclk is bigger than max sclk in the dependence table */
	*vol = allowed_घड़ी_voltage_table->entries[i - 1].v;

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_get_std_voltage_value_sidd(काष्ठा pp_hwmgr *hwmgr,
		pp_atomctrl_voltage_table_entry *tab, uपूर्णांक16_t *hi,
		uपूर्णांक16_t *lo)
अणु
	uपूर्णांक16_t v_index;
	bool vol_found = false;
	*hi = tab->value * VOLTAGE_SCALE;
	*lo = tab->value * VOLTAGE_SCALE;

	/* SCLK/VDDC Dependency Table has to exist. */
	PP_ASSERT_WITH_CODE(शून्य != hwmgr->dyn_state.vddc_dependency_on_sclk,
			"The SCLK/VDDC Dependency Table does not exist.",
			वापस -EINVAL);

	अगर (शून्य == hwmgr->dyn_state.cac_leakage_table) अणु
		pr_warn("CAC Leakage Table does not exist, using vddc.\n");
		वापस 0;
	पूर्ण

	/*
	 * Since voltage in the sclk/vddc dependency table is not
	 * necessarily in ascending order because of ELB voltage
	 * patching, loop through entire list to find exact voltage.
	 */
	क्रम (v_index = 0; (uपूर्णांक32_t)v_index < hwmgr->dyn_state.vddc_dependency_on_sclk->count; v_index++) अणु
		अगर (tab->value == hwmgr->dyn_state.vddc_dependency_on_sclk->entries[v_index].v) अणु
			vol_found = true;
			अगर ((uपूर्णांक32_t)v_index < hwmgr->dyn_state.cac_leakage_table->count) अणु
				*lo = hwmgr->dyn_state.cac_leakage_table->entries[v_index].Vddc * VOLTAGE_SCALE;
				*hi = (uपूर्णांक16_t)(hwmgr->dyn_state.cac_leakage_table->entries[v_index].Leakage * VOLTAGE_SCALE);
			पूर्ण अन्यथा अणु
				pr_warn("Index from SCLK/VDDC Dependency Table exceeds the CAC Leakage Table index, using maximum index from CAC table.\n");
				*lo = hwmgr->dyn_state.cac_leakage_table->entries[hwmgr->dyn_state.cac_leakage_table->count - 1].Vddc * VOLTAGE_SCALE;
				*hi = (uपूर्णांक16_t)(hwmgr->dyn_state.cac_leakage_table->entries[hwmgr->dyn_state.cac_leakage_table->count - 1].Leakage * VOLTAGE_SCALE);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * If voltage is not found in the first pass, loop again to
	 * find the best match, equal or higher value.
	 */
	अगर (!vol_found) अणु
		क्रम (v_index = 0; (uपूर्णांक32_t)v_index < hwmgr->dyn_state.vddc_dependency_on_sclk->count; v_index++) अणु
			अगर (tab->value <= hwmgr->dyn_state.vddc_dependency_on_sclk->entries[v_index].v) अणु
				vol_found = true;
				अगर ((uपूर्णांक32_t)v_index < hwmgr->dyn_state.cac_leakage_table->count) अणु
					*lo = hwmgr->dyn_state.cac_leakage_table->entries[v_index].Vddc * VOLTAGE_SCALE;
					*hi = (uपूर्णांक16_t)(hwmgr->dyn_state.cac_leakage_table->entries[v_index].Leakage) * VOLTAGE_SCALE;
				पूर्ण अन्यथा अणु
					pr_warn("Index from SCLK/VDDC Dependency Table exceeds the CAC Leakage Table index in second look up, using maximum index from CAC table.");
					*lo = hwmgr->dyn_state.cac_leakage_table->entries[hwmgr->dyn_state.cac_leakage_table->count - 1].Vddc * VOLTAGE_SCALE;
					*hi = (uपूर्णांक16_t)(hwmgr->dyn_state.cac_leakage_table->entries[hwmgr->dyn_state.cac_leakage_table->count - 1].Leakage * VOLTAGE_SCALE);
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!vol_found)
			pr_warn("Unable to get std_vddc from SCLK/VDDC Dependency Table, using vddc.\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_smc_voltage_table(काष्ठा pp_hwmgr *hwmgr,
		pp_atomctrl_voltage_table_entry *tab,
		SMU71_Discrete_VoltageLevel *smc_voltage_tab)
अणु
	पूर्णांक result;

	result = iceland_get_std_voltage_value_sidd(hwmgr, tab,
			&smc_voltage_tab->StdVoltageHiSidd,
			&smc_voltage_tab->StdVoltageLoSidd);
	अगर (0 != result) अणु
		smc_voltage_tab->StdVoltageHiSidd = tab->value * VOLTAGE_SCALE;
		smc_voltage_tab->StdVoltageLoSidd = tab->value * VOLTAGE_SCALE;
	पूर्ण

	smc_voltage_tab->Voltage = PP_HOST_TO_SMC_US(tab->value * VOLTAGE_SCALE);
	CONVERT_FROM_HOST_TO_SMC_US(smc_voltage_tab->StdVoltageHiSidd);
	CONVERT_FROM_HOST_TO_SMC_US(smc_voltage_tab->StdVoltageHiSidd);

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_smc_vddc_table(काष्ठा pp_hwmgr *hwmgr,
			SMU71_Discrete_DpmTable *table)
अणु
	अचिन्हित पूर्णांक count;
	पूर्णांक result;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	table->VddcLevelCount = data->vddc_voltage_table.count;
	क्रम (count = 0; count < table->VddcLevelCount; count++) अणु
		result = iceland_populate_smc_voltage_table(hwmgr,
				&(data->vddc_voltage_table.entries[count]),
				&(table->VddcLevel[count]));
		PP_ASSERT_WITH_CODE(0 == result, "do not populate SMC VDDC voltage table", वापस -EINVAL);

		/* GPIO voltage control */
		अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->voltage_control)
			table->VddcLevel[count].Smio |= data->vddc_voltage_table.entries[count].smio_low;
		अन्यथा अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->voltage_control)
			table->VddcLevel[count].Smio = 0;
	पूर्ण

	CONVERT_FROM_HOST_TO_SMC_UL(table->VddcLevelCount);

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_smc_vdd_ci_table(काष्ठा pp_hwmgr *hwmgr,
			SMU71_Discrete_DpmTable *table)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t count;
	पूर्णांक result;

	table->VddciLevelCount = data->vddci_voltage_table.count;

	क्रम (count = 0; count < table->VddciLevelCount; count++) अणु
		result = iceland_populate_smc_voltage_table(hwmgr,
				&(data->vddci_voltage_table.entries[count]),
				&(table->VddciLevel[count]));
		PP_ASSERT_WITH_CODE(result == 0, "do not populate SMC VDDCI voltage table", वापस -EINVAL);
		अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->vddci_control)
			table->VddciLevel[count].Smio |= data->vddci_voltage_table.entries[count].smio_low;
		अन्यथा
			table->VddciLevel[count].Smio |= 0;
	पूर्ण

	CONVERT_FROM_HOST_TO_SMC_UL(table->VddciLevelCount);

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_smc_mvdd_table(काष्ठा pp_hwmgr *hwmgr,
			SMU71_Discrete_DpmTable *table)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t count;
	पूर्णांक result;

	table->MvddLevelCount = data->mvdd_voltage_table.count;

	क्रम (count = 0; count < table->VddciLevelCount; count++) अणु
		result = iceland_populate_smc_voltage_table(hwmgr,
				&(data->mvdd_voltage_table.entries[count]),
				&table->MvddLevel[count]);
		PP_ASSERT_WITH_CODE(result == 0, "do not populate SMC mvdd voltage table", वापस -EINVAL);
		अगर (SMU7_VOLTAGE_CONTROL_BY_GPIO == data->mvdd_control)
			table->MvddLevel[count].Smio |= data->mvdd_voltage_table.entries[count].smio_low;
		अन्यथा
			table->MvddLevel[count].Smio |= 0;
	पूर्ण

	CONVERT_FROM_HOST_TO_SMC_UL(table->MvddLevelCount);

	वापस 0;
पूर्ण


अटल पूर्णांक iceland_populate_smc_voltage_tables(काष्ठा pp_hwmgr *hwmgr,
	SMU71_Discrete_DpmTable *table)
अणु
	पूर्णांक result;

	result = iceland_populate_smc_vddc_table(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
			"can not populate VDDC voltage table to SMC", वापस -EINVAL);

	result = iceland_populate_smc_vdd_ci_table(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
			"can not populate VDDCI voltage table to SMC", वापस -EINVAL);

	result = iceland_populate_smc_mvdd_table(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
			"can not populate MVDD voltage table to SMC", वापस -EINVAL);

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_ulv_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा SMU71_Discrete_Ulv *state)
अणु
	uपूर्णांक32_t voltage_response_समय, ulv_voltage;
	पूर्णांक result;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	state->CcPwrDynRm = 0;
	state->CcPwrDynRm1 = 0;

	result = pp_tables_get_response_बार(hwmgr, &voltage_response_समय, &ulv_voltage);
	PP_ASSERT_WITH_CODE((0 == result), "can not get ULV voltage value", वापस result;);

	अगर (ulv_voltage == 0) अणु
		data->ulv_supported = false;
		वापस 0;
	पूर्ण

	अगर (data->voltage_control != SMU7_VOLTAGE_CONTROL_BY_SVID2) अणु
		/* use minimum voltage अगर ulv voltage in pptable is bigger than minimum voltage */
		अगर (ulv_voltage > hwmgr->dyn_state.vddc_dependency_on_sclk->entries[0].v)
			state->VddcOffset = 0;
		अन्यथा
			/* used in SMIO Mode. not implemented क्रम now. this is backup only क्रम CI. */
			state->VddcOffset = (uपूर्णांक16_t)(hwmgr->dyn_state.vddc_dependency_on_sclk->entries[0].v - ulv_voltage);
	पूर्ण अन्यथा अणु
		/* use minimum voltage अगर ulv voltage in pptable is bigger than minimum voltage */
		अगर (ulv_voltage > hwmgr->dyn_state.vddc_dependency_on_sclk->entries[0].v)
			state->VddcOffsetVid = 0;
		अन्यथा  /* used in SVI2 Mode */
			state->VddcOffsetVid = (uपूर्णांक8_t)(
					(hwmgr->dyn_state.vddc_dependency_on_sclk->entries[0].v - ulv_voltage)
						* VOLTAGE_VID_OFFSET_SCALE2
						/ VOLTAGE_VID_OFFSET_SCALE1);
	पूर्ण
	state->VddcPhase = 1;

	CONVERT_FROM_HOST_TO_SMC_UL(state->CcPwrDynRm);
	CONVERT_FROM_HOST_TO_SMC_UL(state->CcPwrDynRm1);
	CONVERT_FROM_HOST_TO_SMC_US(state->VddcOffset);

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_ulv_state(काष्ठा pp_hwmgr *hwmgr,
		 SMU71_Discrete_Ulv *ulv_level)
अणु
	वापस iceland_populate_ulv_level(hwmgr, ulv_level);
पूर्ण

अटल पूर्णांक iceland_populate_smc_link_level(काष्ठा pp_hwmgr *hwmgr, SMU71_Discrete_DpmTable *table)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_dpm_table *dpm_table = &data->dpm_table;
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t i;

	/* Index (dpm_table->pcie_speed_table.count) is reserved क्रम PCIE boot level. */
	क्रम (i = 0; i <= dpm_table->pcie_speed_table.count; i++) अणु
		table->LinkLevel[i].PcieGenSpeed  =
			(uपूर्णांक8_t)dpm_table->pcie_speed_table.dpm_levels[i].value;
		table->LinkLevel[i].PcieLaneCount =
			(uपूर्णांक8_t)encode_pcie_lane_width(dpm_table->pcie_speed_table.dpm_levels[i].param1);
		table->LinkLevel[i].EnabledForActivity =
			1;
		table->LinkLevel[i].SPC =
			(uपूर्णांक8_t)(data->pcie_spc_cap & 0xff);
		table->LinkLevel[i].DownThreshold =
			PP_HOST_TO_SMC_UL(5);
		table->LinkLevel[i].UpThreshold =
			PP_HOST_TO_SMC_UL(30);
	पूर्ण

	smu_data->smc_state_table.LinkLevelCount =
		(uपूर्णांक8_t)dpm_table->pcie_speed_table.count;
	data->dpm_level_enable_mask.pcie_dpm_enable_mask =
		phm_get_dpm_level_enable_mask_value(&dpm_table->pcie_speed_table);

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_calculate_sclk_params(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t engine_घड़ी, SMU71_Discrete_GraphicsLevel *sclk)
अणु
	स्थिर काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	pp_atomctrl_घड़ी_भागiders_vi भागiders;
	uपूर्णांक32_t spll_func_cntl            = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL;
	uपूर्णांक32_t spll_func_cntl_3          = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_3;
	uपूर्णांक32_t spll_func_cntl_4          = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_4;
	uपूर्णांक32_t cg_spll_spपढ़ो_spectrum   = data->घड़ी_रेजिस्टरs.vCG_SPLL_SPREAD_SPECTRUM;
	uपूर्णांक32_t cg_spll_spपढ़ो_spectrum_2 = data->घड़ी_रेजिस्टरs.vCG_SPLL_SPREAD_SPECTRUM_2;
	uपूर्णांक32_t    reference_घड़ी;
	uपूर्णांक32_t reference_भागider;
	uपूर्णांक32_t fbभाग;
	पूर्णांक result;

	/* get the engine घड़ी भागiders क्रम this घड़ी value*/
	result = atomctrl_get_engine_pll_भागiders_vi(hwmgr, engine_घड़ी,  &भागiders);

	PP_ASSERT_WITH_CODE(result == 0,
		"Error retrieving Engine Clock dividers from VBIOS.", वापस result);

	/* To get FBDIV we need to multiply this by 16384 and भागide it by Fref.*/
	reference_घड़ी = atomctrl_get_reference_घड़ी(hwmgr);

	reference_भागider = 1 + भागiders.uc_pll_ref_भाग;

	/* low 14 bits is fraction and high 12 bits is भागider*/
	fbभाग = भागiders.ul_fb_भाग.ul_fb_भागider & 0x3FFFFFF;

	/* SPLL_FUNC_CNTL setup*/
	spll_func_cntl = PHM_SET_FIELD(spll_func_cntl,
		CG_SPLL_FUNC_CNTL, SPLL_REF_DIV, भागiders.uc_pll_ref_भाग);
	spll_func_cntl = PHM_SET_FIELD(spll_func_cntl,
		CG_SPLL_FUNC_CNTL, SPLL_PDIV_A,  भागiders.uc_pll_post_भाग);

	/* SPLL_FUNC_CNTL_3 setup*/
	spll_func_cntl_3 = PHM_SET_FIELD(spll_func_cntl_3,
		CG_SPLL_FUNC_CNTL_3, SPLL_FB_DIV, fbभाग);

	/* set to use fractional accumulation*/
	spll_func_cntl_3 = PHM_SET_FIELD(spll_func_cntl_3,
		CG_SPLL_FUNC_CNTL_3, SPLL_DITHEN, 1);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_EngineSpपढ़ोSpectrumSupport)) अणु
		pp_atomctrl_पूर्णांकernal_ss_info ss_info;

		uपूर्णांक32_t vcoFreq = engine_घड़ी * भागiders.uc_pll_post_भाग;
		अगर (0 == atomctrl_get_engine_घड़ी_spपढ़ो_spectrum(hwmgr, vcoFreq, &ss_info)) अणु
			/*
			* ss_info.speed_spectrum_percentage -- in unit of 0.01%
			* ss_info.speed_spectrum_rate -- in unit of khz
			*/
			/* clks = reference_घड़ी * 10 / (REFDIV + 1) / speed_spectrum_rate / 2 */
			uपूर्णांक32_t clkS = reference_घड़ी * 5 / (reference_भागider * ss_info.speed_spectrum_rate);

			/* clkv = 2 * D * fbभाग / NS */
			uपूर्णांक32_t clkV = 4 * ss_info.speed_spectrum_percentage * fbभाग / (clkS * 10000);

			cg_spll_spपढ़ो_spectrum =
				PHM_SET_FIELD(cg_spll_spपढ़ो_spectrum, CG_SPLL_SPREAD_SPECTRUM, CLKS, clkS);
			cg_spll_spपढ़ो_spectrum =
				PHM_SET_FIELD(cg_spll_spपढ़ो_spectrum, CG_SPLL_SPREAD_SPECTRUM, SSEN, 1);
			cg_spll_spपढ़ो_spectrum_2 =
				PHM_SET_FIELD(cg_spll_spपढ़ो_spectrum_2, CG_SPLL_SPREAD_SPECTRUM_2, CLKV, clkV);
		पूर्ण
	पूर्ण

	sclk->SclkFrequency        = engine_घड़ी;
	sclk->CgSpllFuncCntl3      = spll_func_cntl_3;
	sclk->CgSpllFuncCntl4      = spll_func_cntl_4;
	sclk->SpllSpपढ़ोSpectrum   = cg_spll_spपढ़ो_spectrum;
	sclk->SpllSpपढ़ोSpectrum2  = cg_spll_spपढ़ो_spectrum_2;
	sclk->SclkDid              = (uपूर्णांक8_t)भागiders.pll_post_भागider;

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_phase_value_based_on_sclk(काष्ठा pp_hwmgr *hwmgr,
				स्थिर काष्ठा phm_phase_shedding_limits_table *pl,
					uपूर्णांक32_t sclk, uपूर्णांक32_t *p_shed)
अणु
	अचिन्हित पूर्णांक i;

	/* use the minimum phase shedding */
	*p_shed = 1;

	क्रम (i = 0; i < pl->count; i++) अणु
		अगर (sclk < pl->entries[i].Sclk) अणु
			*p_shed = i;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_single_graphic_level(काष्ठा pp_hwmgr *hwmgr,
						uपूर्णांक32_t engine_घड़ी,
				SMU71_Discrete_GraphicsLevel *graphic_level)
अणु
	पूर्णांक result;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	result = iceland_calculate_sclk_params(hwmgr, engine_घड़ी, graphic_level);

	/* populate graphics levels*/
	result = iceland_get_dependency_volt_by_clk(hwmgr,
		hwmgr->dyn_state.vddc_dependency_on_sclk, engine_घड़ी,
		&graphic_level->MinVddc);
	PP_ASSERT_WITH_CODE((0 == result),
		"can not find VDDC voltage value for VDDC engine clock dependency table", वापस result);

	/* SCLK frequency in units of 10KHz*/
	graphic_level->SclkFrequency = engine_घड़ी;
	graphic_level->MinVddcPhases = 1;

	अगर (data->vddc_phase_shed_control)
		iceland_populate_phase_value_based_on_sclk(hwmgr,
				hwmgr->dyn_state.vddc_phase_shed_limits_table,
				engine_घड़ी,
				&graphic_level->MinVddcPhases);

	/* Indicates maximum activity level क्रम this perक्रमmance level. 50% क्रम now*/
	graphic_level->ActivityLevel = data->current_profile_setting.sclk_activity;

	graphic_level->CcPwrDynRm = 0;
	graphic_level->CcPwrDynRm1 = 0;
	/* this level can be used अगर activity is high enough.*/
	graphic_level->EnabledForActivity = 0;
	/* this level can be used क्रम throttling.*/
	graphic_level->EnabledForThrottle = 1;
	graphic_level->UpHyst = data->current_profile_setting.sclk_up_hyst;
	graphic_level->DownHyst = data->current_profile_setting.sclk_करोwn_hyst;
	graphic_level->VoltageDownHyst = 0;
	graphic_level->PowerThrottle = 0;

	data->display_timing.min_घड़ी_in_sr =
			hwmgr->display_config->min_core_set_घड़ी_in_sr;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SclkDeepSleep))
		graphic_level->DeepSleepDivId =
				smu7_get_sleep_भागider_id_from_घड़ी(engine_घड़ी,
						data->display_timing.min_घड़ी_in_sr);

	/* Default to slow, highest DPM level will be set to PPSMC_DISPLAY_WATERMARK_LOW later.*/
	graphic_level->DisplayWatermark = PPSMC_DISPLAY_WATERMARK_LOW;

	अगर (0 == result) अणु
		graphic_level->MinVddc = PP_HOST_TO_SMC_UL(graphic_level->MinVddc * VOLTAGE_SCALE);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->MinVddcPhases);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->SclkFrequency);
		CONVERT_FROM_HOST_TO_SMC_US(graphic_level->ActivityLevel);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->CgSpllFuncCntl3);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->CgSpllFuncCntl4);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->SpllSpपढ़ोSpectrum);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->SpllSpपढ़ोSpectrum2);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->CcPwrDynRm);
		CONVERT_FROM_HOST_TO_SMC_UL(graphic_level->CcPwrDynRm1);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक iceland_populate_all_graphic_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	काष्ठा smu7_dpm_table *dpm_table = &data->dpm_table;
	uपूर्णांक32_t level_array_adress = smu_data->smu7_data.dpm_table_start +
				दुरत्व(SMU71_Discrete_DpmTable, GraphicsLevel);

	uपूर्णांक32_t level_array_size = माप(SMU71_Discrete_GraphicsLevel) *
						SMU71_MAX_LEVELS_GRAPHICS;

	SMU71_Discrete_GraphicsLevel *levels = smu_data->smc_state_table.GraphicsLevel;

	uपूर्णांक32_t i;
	uपूर्णांक8_t highest_pcie_level_enabled = 0;
	uपूर्णांक8_t lowest_pcie_level_enabled = 0, mid_pcie_level_enabled = 0;
	uपूर्णांक8_t count = 0;
	पूर्णांक result = 0;

	स_रखो(levels, 0x00, level_array_size);

	क्रम (i = 0; i < dpm_table->sclk_table.count; i++) अणु
		result = iceland_populate_single_graphic_level(hwmgr,
					dpm_table->sclk_table.dpm_levels[i].value,
					&(smu_data->smc_state_table.GraphicsLevel[i]));
		अगर (result != 0)
			वापस result;

		/* Making sure only DPM level 0-1 have Deep Sleep Div ID populated. */
		अगर (i > 1)
			smu_data->smc_state_table.GraphicsLevel[i].DeepSleepDivId = 0;
	पूर्ण

	/* Only enable level 0 क्रम now. */
	smu_data->smc_state_table.GraphicsLevel[0].EnabledForActivity = 1;

	/* set highest level watermark to high */
	अगर (dpm_table->sclk_table.count > 1)
		smu_data->smc_state_table.GraphicsLevel[dpm_table->sclk_table.count-1].DisplayWatermark =
			PPSMC_DISPLAY_WATERMARK_HIGH;

	smu_data->smc_state_table.GraphicsDpmLevelCount =
		(uपूर्णांक8_t)dpm_table->sclk_table.count;
	data->dpm_level_enable_mask.sclk_dpm_enable_mask =
		phm_get_dpm_level_enable_mask_value(&dpm_table->sclk_table);

	जबतक ((data->dpm_level_enable_mask.pcie_dpm_enable_mask &
				(1 << (highest_pcie_level_enabled + 1))) != 0) अणु
		highest_pcie_level_enabled++;
	पूर्ण

	जबतक ((data->dpm_level_enable_mask.pcie_dpm_enable_mask &
		(1 << lowest_pcie_level_enabled)) == 0) अणु
		lowest_pcie_level_enabled++;
	पूर्ण

	जबतक ((count < highest_pcie_level_enabled) &&
			((data->dpm_level_enable_mask.pcie_dpm_enable_mask &
				(1 << (lowest_pcie_level_enabled + 1 + count))) == 0)) अणु
		count++;
	पूर्ण

	mid_pcie_level_enabled = (lowest_pcie_level_enabled+1+count) < highest_pcie_level_enabled ?
		(lowest_pcie_level_enabled+1+count) : highest_pcie_level_enabled;


	/* set pcieDpmLevel to highest_pcie_level_enabled*/
	क्रम (i = 2; i < dpm_table->sclk_table.count; i++) अणु
		smu_data->smc_state_table.GraphicsLevel[i].pcieDpmLevel = highest_pcie_level_enabled;
	पूर्ण

	/* set pcieDpmLevel to lowest_pcie_level_enabled*/
	smu_data->smc_state_table.GraphicsLevel[0].pcieDpmLevel = lowest_pcie_level_enabled;

	/* set pcieDpmLevel to mid_pcie_level_enabled*/
	smu_data->smc_state_table.GraphicsLevel[1].pcieDpmLevel = mid_pcie_level_enabled;

	/* level count will send to smc once at init smc table and never change*/
	result = smu7_copy_bytes_to_smc(hwmgr, level_array_adress,
				(uपूर्णांक8_t *)levels, (uपूर्णांक32_t)level_array_size,
								SMC_RAM_END);

	वापस result;
पूर्ण

अटल पूर्णांक iceland_calculate_mclk_params(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t memory_घड़ी,
		SMU71_Discrete_MemoryLevel *mclk,
		bool strobe_mode,
		bool dllStateOn
		)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	uपूर्णांक32_t  dll_cntl = data->घड़ी_रेजिस्टरs.vDLL_CNTL;
	uपूर्णांक32_t  mclk_pwrmgt_cntl = data->घड़ी_रेजिस्टरs.vMCLK_PWRMGT_CNTL;
	uपूर्णांक32_t  mpll_ad_func_cntl = data->घड़ी_रेजिस्टरs.vMPLL_AD_FUNC_CNTL;
	uपूर्णांक32_t  mpll_dq_func_cntl = data->घड़ी_रेजिस्टरs.vMPLL_DQ_FUNC_CNTL;
	uपूर्णांक32_t  mpll_func_cntl = data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL;
	uपूर्णांक32_t  mpll_func_cntl_1 = data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL_1;
	uपूर्णांक32_t  mpll_func_cntl_2 = data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL_2;
	uपूर्णांक32_t  mpll_ss1 = data->घड़ी_रेजिस्टरs.vMPLL_SS1;
	uपूर्णांक32_t  mpll_ss2 = data->घड़ी_रेजिस्टरs.vMPLL_SS2;

	pp_atomctrl_memory_घड़ी_param mpll_param;
	पूर्णांक result;

	result = atomctrl_get_memory_pll_भागiders_si(hwmgr,
				memory_घड़ी, &mpll_param, strobe_mode);
	PP_ASSERT_WITH_CODE(0 == result,
		"Error retrieving Memory Clock Parameters from VBIOS.", वापस result);

	/* MPLL_FUNC_CNTL setup*/
	mpll_func_cntl = PHM_SET_FIELD(mpll_func_cntl, MPLL_FUNC_CNTL, BWCTRL, mpll_param.bw_ctrl);

	/* MPLL_FUNC_CNTL_1 setup*/
	mpll_func_cntl_1  = PHM_SET_FIELD(mpll_func_cntl_1,
							MPLL_FUNC_CNTL_1, CLKF, mpll_param.mpll_fb_भागider.cl_kf);
	mpll_func_cntl_1  = PHM_SET_FIELD(mpll_func_cntl_1,
							MPLL_FUNC_CNTL_1, CLKFRAC, mpll_param.mpll_fb_भागider.clk_frac);
	mpll_func_cntl_1  = PHM_SET_FIELD(mpll_func_cntl_1,
							MPLL_FUNC_CNTL_1, VCO_MODE, mpll_param.vco_mode);

	/* MPLL_AD_FUNC_CNTL setup*/
	mpll_ad_func_cntl = PHM_SET_FIELD(mpll_ad_func_cntl,
							MPLL_AD_FUNC_CNTL, YCLK_POST_DIV, mpll_param.mpll_post_भागider);

	अगर (data->is_memory_gddr5) अणु
		/* MPLL_DQ_FUNC_CNTL setup*/
		mpll_dq_func_cntl  = PHM_SET_FIELD(mpll_dq_func_cntl,
								MPLL_DQ_FUNC_CNTL, YCLK_SEL, mpll_param.yclk_sel);
		mpll_dq_func_cntl  = PHM_SET_FIELD(mpll_dq_func_cntl,
								MPLL_DQ_FUNC_CNTL, YCLK_POST_DIV, mpll_param.mpll_post_भागider);
	पूर्ण

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_MemorySpपढ़ोSpectrumSupport)) अणु
		/*
		 ************************************
		 Fref = Reference Frequency
		 NF = Feedback भागider ratio
		 NR = Reference भागider ratio
		 Fnom = Nominal VCO output frequency = Fref * NF / NR
		 Fs = Spपढ़ोing Rate
		 D = Percentage करोwn-spपढ़ो / 2
		 Fपूर्णांक = Reference input frequency to PFD = Fref / NR
		 NS = Spपढ़ोing rate भागider ratio = पूर्णांक(Fपूर्णांक / (2 * Fs))
		 CLKS = NS - 1 = ISS_STEP_NUM[11:0]
		 NV = D * Fs / Fnom * 4 * ((Fnom/Fref * NR) ^ 2)
		 CLKV = 65536 * NV = ISS_STEP_SIZE[25:0]
		 *************************************
		 */
		pp_atomctrl_पूर्णांकernal_ss_info ss_info;
		uपूर्णांक32_t freq_nom;
		uपूर्णांक32_t पंचांगp;
		uपूर्णांक32_t reference_घड़ी = atomctrl_get_mpll_reference_घड़ी(hwmgr);

		/* क्रम GDDR5 क्रम all modes and DDR3 */
		अगर (1 == mpll_param.qdr)
			freq_nom = memory_घड़ी * 4 * (1 << mpll_param.mpll_post_भागider);
		अन्यथा
			freq_nom = memory_घड़ी * 2 * (1 << mpll_param.mpll_post_भागider);

		/* पंचांगp = (freq_nom / reference_घड़ी * reference_भागider) ^ 2  Note: S.I. reference_भागider = 1*/
		पंचांगp = (freq_nom / reference_घड़ी);
		पंचांगp = पंचांगp * पंचांगp;

		अगर (0 == atomctrl_get_memory_घड़ी_spपढ़ो_spectrum(hwmgr, freq_nom, &ss_info)) अणु
			/* ss_info.speed_spectrum_percentage -- in unit of 0.01% */
			/* ss.Info.speed_spectrum_rate -- in unit of khz */
			/* CLKS = reference_घड़ी / (2 * speed_spectrum_rate * reference_भागider) * 10 */
			/*     = reference_घड़ी * 5 / speed_spectrum_rate */
			uपूर्णांक32_t clks = reference_घड़ी * 5 / ss_info.speed_spectrum_rate;

			/* CLKV = 65536 * speed_spectrum_percentage / 2 * spपढ़ोSpecrumRate / freq_nom * 4 / 100000 * ((freq_nom / reference_घड़ी) ^ 2) */
			/*     = 131 * speed_spectrum_percentage * speed_spectrum_rate / 100 * ((freq_nom / reference_घड़ी) ^ 2) / freq_nom */
			uपूर्णांक32_t clkv =
				(uपूर्णांक32_t)((((131 * ss_info.speed_spectrum_percentage *
							ss_info.speed_spectrum_rate) / 100) * पंचांगp) / freq_nom);

			mpll_ss1 = PHM_SET_FIELD(mpll_ss1, MPLL_SS1, CLKV, clkv);
			mpll_ss2 = PHM_SET_FIELD(mpll_ss2, MPLL_SS2, CLKS, clks);
		पूर्ण
	पूर्ण

	/* MCLK_PWRMGT_CNTL setup */
	mclk_pwrmgt_cntl = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, DLL_SPEED, mpll_param.dll_speed);
	mclk_pwrmgt_cntl = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, MRDCK0_PDNB, dllStateOn);
	mclk_pwrmgt_cntl = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, MRDCK1_PDNB, dllStateOn);


	/* Save the result data to outpupt memory level काष्ठाure */
	mclk->MclkFrequency   = memory_घड़ी;
	mclk->MpllFuncCntl    = mpll_func_cntl;
	mclk->MpllFuncCntl_1  = mpll_func_cntl_1;
	mclk->MpllFuncCntl_2  = mpll_func_cntl_2;
	mclk->MpllAdFuncCntl  = mpll_ad_func_cntl;
	mclk->MpllDqFuncCntl  = mpll_dq_func_cntl;
	mclk->MclkPwrmgtCntl  = mclk_pwrmgt_cntl;
	mclk->DllCntl         = dll_cntl;
	mclk->MpllSs1         = mpll_ss1;
	mclk->MpllSs2         = mpll_ss2;

	वापस 0;
पूर्ण

अटल uपूर्णांक8_t iceland_get_mclk_frequency_ratio(uपूर्णांक32_t memory_घड़ी,
		bool strobe_mode)
अणु
	uपूर्णांक8_t mc_para_index;

	अगर (strobe_mode) अणु
		अगर (memory_घड़ी < 12500) अणु
			mc_para_index = 0x00;
		पूर्ण अन्यथा अगर (memory_घड़ी > 47500) अणु
			mc_para_index = 0x0f;
		पूर्ण अन्यथा अणु
			mc_para_index = (uपूर्णांक8_t)((memory_घड़ी - 10000) / 2500);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (memory_घड़ी < 65000) अणु
			mc_para_index = 0x00;
		पूर्ण अन्यथा अगर (memory_घड़ी > 135000) अणु
			mc_para_index = 0x0f;
		पूर्ण अन्यथा अणु
			mc_para_index = (uपूर्णांक8_t)((memory_घड़ी - 60000) / 5000);
		पूर्ण
	पूर्ण

	वापस mc_para_index;
पूर्ण

अटल uपूर्णांक8_t iceland_get_ddr3_mclk_frequency_ratio(uपूर्णांक32_t memory_घड़ी)
अणु
	uपूर्णांक8_t mc_para_index;

	अगर (memory_घड़ी < 10000) अणु
		mc_para_index = 0;
	पूर्ण अन्यथा अगर (memory_घड़ी >= 80000) अणु
		mc_para_index = 0x0f;
	पूर्ण अन्यथा अणु
		mc_para_index = (uपूर्णांक8_t)((memory_घड़ी - 10000) / 5000 + 1);
	पूर्ण

	वापस mc_para_index;
पूर्ण

अटल पूर्णांक iceland_populate_phase_value_based_on_mclk(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा phm_phase_shedding_limits_table *pl,
					uपूर्णांक32_t memory_घड़ी, uपूर्णांक32_t *p_shed)
अणु
	अचिन्हित पूर्णांक i;

	*p_shed = 1;

	क्रम (i = 0; i < pl->count; i++) अणु
		अगर (memory_घड़ी < pl->entries[i].Mclk) अणु
			*p_shed = i;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_single_memory_level(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t memory_घड़ी,
		SMU71_Discrete_MemoryLevel *memory_level
		)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	पूर्णांक result = 0;
	bool dll_state_on;
	uपूर्णांक32_t mclk_edc_wr_enable_threshold = 40000;
	uपूर्णांक32_t mclk_edc_enable_threshold = 40000;
	uपूर्णांक32_t mclk_strobe_mode_threshold = 40000;

	अगर (hwmgr->dyn_state.vddc_dependency_on_mclk != शून्य) अणु
		result = iceland_get_dependency_volt_by_clk(hwmgr,
			hwmgr->dyn_state.vddc_dependency_on_mclk, memory_घड़ी, &memory_level->MinVddc);
		PP_ASSERT_WITH_CODE((0 == result),
			"can not find MinVddc voltage value from memory VDDC voltage dependency table", वापस result);
	पूर्ण

	अगर (data->vddci_control == SMU7_VOLTAGE_CONTROL_NONE) अणु
		memory_level->MinVddci = memory_level->MinVddc;
	पूर्ण अन्यथा अगर (शून्य != hwmgr->dyn_state.vddci_dependency_on_mclk) अणु
		result = iceland_get_dependency_volt_by_clk(hwmgr,
				hwmgr->dyn_state.vddci_dependency_on_mclk,
				memory_घड़ी,
				&memory_level->MinVddci);
		PP_ASSERT_WITH_CODE((0 == result),
			"can not find MinVddci voltage value from memory VDDCI voltage dependency table", वापस result);
	पूर्ण

	memory_level->MinVddcPhases = 1;

	अगर (data->vddc_phase_shed_control) अणु
		iceland_populate_phase_value_based_on_mclk(hwmgr, hwmgr->dyn_state.vddc_phase_shed_limits_table,
				memory_घड़ी, &memory_level->MinVddcPhases);
	पूर्ण

	memory_level->EnabledForThrottle = 1;
	memory_level->EnabledForActivity = 0;
	memory_level->UpHyst = data->current_profile_setting.mclk_up_hyst;
	memory_level->DownHyst = data->current_profile_setting.mclk_करोwn_hyst;
	memory_level->VoltageDownHyst = 0;

	/* Indicates maximum activity level क्रम this perक्रमmance level.*/
	memory_level->ActivityLevel = data->current_profile_setting.mclk_activity;
	memory_level->StutterEnable = 0;
	memory_level->StrobeEnable = 0;
	memory_level->EdcReadEnable = 0;
	memory_level->EdcWriteEnable = 0;
	memory_level->RttEnable = 0;

	/* शेष set to low watermark. Highest level will be set to high later.*/
	memory_level->DisplayWatermark = PPSMC_DISPLAY_WATERMARK_LOW;

	data->display_timing.num_existing_displays = hwmgr->display_config->num_display;
	data->display_timing.vrefresh = hwmgr->display_config->vrefresh;

	/* stutter mode not support on iceland */

	/* decide strobe mode*/
	memory_level->StrobeEnable = (mclk_strobe_mode_threshold != 0) &&
		(memory_घड़ी <= mclk_strobe_mode_threshold);

	/* decide EDC mode and memory घड़ी ratio*/
	अगर (data->is_memory_gddr5) अणु
		memory_level->StrobeRatio = iceland_get_mclk_frequency_ratio(memory_घड़ी,
					memory_level->StrobeEnable);

		अगर ((mclk_edc_enable_threshold != 0) &&
				(memory_घड़ी > mclk_edc_enable_threshold)) अणु
			memory_level->EdcReadEnable = 1;
		पूर्ण

		अगर ((mclk_edc_wr_enable_threshold != 0) &&
				(memory_घड़ी > mclk_edc_wr_enable_threshold)) अणु
			memory_level->EdcWriteEnable = 1;
		पूर्ण

		अगर (memory_level->StrobeEnable) अणु
			अगर (iceland_get_mclk_frequency_ratio(memory_घड़ी, 1) >=
					((cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC7) >> 16) & 0xf))
				dll_state_on = ((cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC5) >> 1) & 0x1) ? 1 : 0;
			अन्यथा
				dll_state_on = ((cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC6) >> 1) & 0x1) ? 1 : 0;
		पूर्ण अन्यथा
			dll_state_on = data->dll_शेष_on;
	पूर्ण अन्यथा अणु
		memory_level->StrobeRatio =
			iceland_get_ddr3_mclk_frequency_ratio(memory_घड़ी);
		dll_state_on = ((cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC5) >> 1) & 0x1) ? 1 : 0;
	पूर्ण

	result = iceland_calculate_mclk_params(hwmgr,
		memory_घड़ी, memory_level, memory_level->StrobeEnable, dll_state_on);

	अगर (0 == result) अणु
		memory_level->MinVddc = PP_HOST_TO_SMC_UL(memory_level->MinVddc * VOLTAGE_SCALE);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MinVddcPhases);
		memory_level->MinVddci = PP_HOST_TO_SMC_UL(memory_level->MinVddci * VOLTAGE_SCALE);
		memory_level->MinMvdd = PP_HOST_TO_SMC_UL(memory_level->MinMvdd * VOLTAGE_SCALE);
		/* MCLK frequency in units of 10KHz*/
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MclkFrequency);
		/* Indicates maximum activity level क्रम this perक्रमmance level.*/
		CONVERT_FROM_HOST_TO_SMC_US(memory_level->ActivityLevel);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllFuncCntl);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllFuncCntl_1);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllFuncCntl_2);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllAdFuncCntl);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllDqFuncCntl);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MclkPwrmgtCntl);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->DllCntl);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllSs1);
		CONVERT_FROM_HOST_TO_SMC_UL(memory_level->MpllSs2);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक iceland_populate_all_memory_levels(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	काष्ठा smu7_dpm_table *dpm_table = &data->dpm_table;
	पूर्णांक result;

	/* populate MCLK dpm table to SMU7 */
	uपूर्णांक32_t level_array_adress = smu_data->smu7_data.dpm_table_start + दुरत्व(SMU71_Discrete_DpmTable, MemoryLevel);
	uपूर्णांक32_t level_array_size = माप(SMU71_Discrete_MemoryLevel) * SMU71_MAX_LEVELS_MEMORY;
	SMU71_Discrete_MemoryLevel *levels = smu_data->smc_state_table.MemoryLevel;
	uपूर्णांक32_t i;

	स_रखो(levels, 0x00, level_array_size);

	क्रम (i = 0; i < dpm_table->mclk_table.count; i++) अणु
		PP_ASSERT_WITH_CODE((0 != dpm_table->mclk_table.dpm_levels[i].value),
			"can not populate memory level as memory clock is zero", वापस -EINVAL);
		result = iceland_populate_single_memory_level(hwmgr, dpm_table->mclk_table.dpm_levels[i].value,
			&(smu_data->smc_state_table.MemoryLevel[i]));
		अगर (0 != result) अणु
			वापस result;
		पूर्ण
	पूर्ण

	/* Only enable level 0 क्रम now.*/
	smu_data->smc_state_table.MemoryLevel[0].EnabledForActivity = 1;

	/*
	* in order to prevent MC activity from stutter mode to push DPM up.
	* the UVD change complements this by putting the MCLK in a higher state
	* by शेष such that we are not effected by up threshold or and MCLK DPM latency.
	*/
	smu_data->smc_state_table.MemoryLevel[0].ActivityLevel = 0x1F;
	CONVERT_FROM_HOST_TO_SMC_US(smu_data->smc_state_table.MemoryLevel[0].ActivityLevel);

	smu_data->smc_state_table.MemoryDpmLevelCount = (uपूर्णांक8_t)dpm_table->mclk_table.count;
	data->dpm_level_enable_mask.mclk_dpm_enable_mask = phm_get_dpm_level_enable_mask_value(&dpm_table->mclk_table);
	/* set highest level watermark to high*/
	smu_data->smc_state_table.MemoryLevel[dpm_table->mclk_table.count-1].DisplayWatermark = PPSMC_DISPLAY_WATERMARK_HIGH;

	/* level count will send to smc once at init smc table and never change*/
	result = smu7_copy_bytes_to_smc(hwmgr,
		level_array_adress, (uपूर्णांक8_t *)levels, (uपूर्णांक32_t)level_array_size,
		SMC_RAM_END);

	वापस result;
पूर्ण

अटल पूर्णांक iceland_populate_mvdd_value(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t mclk,
					SMU71_Discrete_VoltageLevel *voltage)
अणु
	स्थिर काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	uपूर्णांक32_t i = 0;

	अगर (SMU7_VOLTAGE_CONTROL_NONE != data->mvdd_control) अणु
		/* find mvdd value which घड़ी is more than request */
		क्रम (i = 0; i < hwmgr->dyn_state.mvdd_dependency_on_mclk->count; i++) अणु
			अगर (mclk <= hwmgr->dyn_state.mvdd_dependency_on_mclk->entries[i].clk) अणु
				/* Always round to higher voltage. */
				voltage->Voltage = data->mvdd_voltage_table.entries[i].value;
				अवरोध;
			पूर्ण
		पूर्ण

		PP_ASSERT_WITH_CODE(i < hwmgr->dyn_state.mvdd_dependency_on_mclk->count,
			"MVDD Voltage is outside the supported range.", वापस -EINVAL);

	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_smc_acpi_level(काष्ठा pp_hwmgr *hwmgr,
	SMU71_Discrete_DpmTable *table)
अणु
	पूर्णांक result = 0;
	स्थिर काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा pp_atomctrl_घड़ी_भागiders_vi भागiders;
	uपूर्णांक32_t vddc_phase_shed_control = 0;

	SMU71_Discrete_VoltageLevel voltage_level;
	uपूर्णांक32_t spll_func_cntl    = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL;
	uपूर्णांक32_t spll_func_cntl_2  = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_2;
	uपूर्णांक32_t dll_cntl          = data->घड़ी_रेजिस्टरs.vDLL_CNTL;
	uपूर्णांक32_t mclk_pwrmgt_cntl  = data->घड़ी_रेजिस्टरs.vMCLK_PWRMGT_CNTL;


	/* The ACPI state should not करो DPM on DC (or ever).*/
	table->ACPILevel.Flags &= ~PPSMC_SWSTATE_FLAG_DC;

	अगर (data->acpi_vddc)
		table->ACPILevel.MinVddc = PP_HOST_TO_SMC_UL(data->acpi_vddc * VOLTAGE_SCALE);
	अन्यथा
		table->ACPILevel.MinVddc = PP_HOST_TO_SMC_UL(data->min_vddc_in_pptable * VOLTAGE_SCALE);

	table->ACPILevel.MinVddcPhases = vddc_phase_shed_control ? 0 : 1;
	/* assign zero क्रम now*/
	table->ACPILevel.SclkFrequency = atomctrl_get_reference_घड़ी(hwmgr);

	/* get the engine घड़ी भागiders क्रम this घड़ी value*/
	result = atomctrl_get_engine_pll_भागiders_vi(hwmgr,
		table->ACPILevel.SclkFrequency,  &भागiders);

	PP_ASSERT_WITH_CODE(result == 0,
		"Error retrieving Engine Clock dividers from VBIOS.", वापस result);

	/* भागider ID क्रम required SCLK*/
	table->ACPILevel.SclkDid = (uपूर्णांक8_t)भागiders.pll_post_भागider;
	table->ACPILevel.DisplayWatermark = PPSMC_DISPLAY_WATERMARK_LOW;
	table->ACPILevel.DeepSleepDivId = 0;

	spll_func_cntl      = PHM_SET_FIELD(spll_func_cntl,
							CG_SPLL_FUNC_CNTL,   SPLL_PWRON,     0);
	spll_func_cntl      = PHM_SET_FIELD(spll_func_cntl,
							CG_SPLL_FUNC_CNTL,   SPLL_RESET,     1);
	spll_func_cntl_2    = PHM_SET_FIELD(spll_func_cntl_2,
							CG_SPLL_FUNC_CNTL_2, SCLK_MUX_SEL,   4);

	table->ACPILevel.CgSpllFuncCntl = spll_func_cntl;
	table->ACPILevel.CgSpllFuncCntl2 = spll_func_cntl_2;
	table->ACPILevel.CgSpllFuncCntl3 = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_3;
	table->ACPILevel.CgSpllFuncCntl4 = data->घड़ी_रेजिस्टरs.vCG_SPLL_FUNC_CNTL_4;
	table->ACPILevel.SpllSpपढ़ोSpectrum = data->घड़ी_रेजिस्टरs.vCG_SPLL_SPREAD_SPECTRUM;
	table->ACPILevel.SpllSpपढ़ोSpectrum2 = data->घड़ी_रेजिस्टरs.vCG_SPLL_SPREAD_SPECTRUM_2;
	table->ACPILevel.CcPwrDynRm = 0;
	table->ACPILevel.CcPwrDynRm1 = 0;


	/* For various features to be enabled/disabled जबतक this level is active.*/
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.Flags);
	/* SCLK frequency in units of 10KHz*/
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.SclkFrequency);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CgSpllFuncCntl);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CgSpllFuncCntl2);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CgSpllFuncCntl3);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CgSpllFuncCntl4);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.SpllSpपढ़ोSpectrum);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.SpllSpपढ़ोSpectrum2);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CcPwrDynRm);
	CONVERT_FROM_HOST_TO_SMC_UL(table->ACPILevel.CcPwrDynRm1);

	/* table->MemoryACPILevel.MinVddcPhases = table->ACPILevel.MinVddcPhases;*/
	table->MemoryACPILevel.MinVddc = table->ACPILevel.MinVddc;
	table->MemoryACPILevel.MinVddcPhases = table->ACPILevel.MinVddcPhases;

	अगर (SMU7_VOLTAGE_CONTROL_NONE == data->vddci_control)
		table->MemoryACPILevel.MinVddci = table->MemoryACPILevel.MinVddc;
	अन्यथा अणु
		अगर (data->acpi_vddci != 0)
			table->MemoryACPILevel.MinVddci = PP_HOST_TO_SMC_UL(data->acpi_vddci * VOLTAGE_SCALE);
		अन्यथा
			table->MemoryACPILevel.MinVddci = PP_HOST_TO_SMC_UL(data->min_vddci_in_pptable * VOLTAGE_SCALE);
	पूर्ण

	अगर (0 == iceland_populate_mvdd_value(hwmgr, 0, &voltage_level))
		table->MemoryACPILevel.MinMvdd =
			PP_HOST_TO_SMC_UL(voltage_level.Voltage * VOLTAGE_SCALE);
	अन्यथा
		table->MemoryACPILevel.MinMvdd = 0;

	/* Force reset on DLL*/
	mclk_pwrmgt_cntl    = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, MRDCK0_RESET, 0x1);
	mclk_pwrmgt_cntl    = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, MRDCK1_RESET, 0x1);

	/* Disable DLL in ACPIState*/
	mclk_pwrmgt_cntl    = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, MRDCK0_PDNB, 0);
	mclk_pwrmgt_cntl    = PHM_SET_FIELD(mclk_pwrmgt_cntl,
		MCLK_PWRMGT_CNTL, MRDCK1_PDNB, 0);

	/* Enable DLL bypass संकेत*/
	dll_cntl            = PHM_SET_FIELD(dll_cntl,
		DLL_CNTL, MRDCK0_BYPASS, 0);
	dll_cntl            = PHM_SET_FIELD(dll_cntl,
		DLL_CNTL, MRDCK1_BYPASS, 0);

	table->MemoryACPILevel.DllCntl            =
		PP_HOST_TO_SMC_UL(dll_cntl);
	table->MemoryACPILevel.MclkPwrmgtCntl     =
		PP_HOST_TO_SMC_UL(mclk_pwrmgt_cntl);
	table->MemoryACPILevel.MpllAdFuncCntl     =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_AD_FUNC_CNTL);
	table->MemoryACPILevel.MpllDqFuncCntl     =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_DQ_FUNC_CNTL);
	table->MemoryACPILevel.MpllFuncCntl       =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL);
	table->MemoryACPILevel.MpllFuncCntl_1     =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL_1);
	table->MemoryACPILevel.MpllFuncCntl_2     =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_FUNC_CNTL_2);
	table->MemoryACPILevel.MpllSs1            =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_SS1);
	table->MemoryACPILevel.MpllSs2            =
		PP_HOST_TO_SMC_UL(data->घड़ी_रेजिस्टरs.vMPLL_SS2);

	table->MemoryACPILevel.EnabledForThrottle = 0;
	table->MemoryACPILevel.EnabledForActivity = 0;
	table->MemoryACPILevel.UpHyst = 0;
	table->MemoryACPILevel.DownHyst = 100;
	table->MemoryACPILevel.VoltageDownHyst = 0;
	/* Indicates maximum activity level क्रम this perक्रमmance level.*/
	table->MemoryACPILevel.ActivityLevel = PP_HOST_TO_SMC_US(data->current_profile_setting.mclk_activity);

	table->MemoryACPILevel.StutterEnable = 0;
	table->MemoryACPILevel.StrobeEnable = 0;
	table->MemoryACPILevel.EdcReadEnable = 0;
	table->MemoryACPILevel.EdcWriteEnable = 0;
	table->MemoryACPILevel.RttEnable = 0;

	वापस result;
पूर्ण

अटल पूर्णांक iceland_populate_smc_uvd_level(काष्ठा pp_hwmgr *hwmgr,
					SMU71_Discrete_DpmTable *table)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_smc_vce_level(काष्ठा pp_hwmgr *hwmgr,
		SMU71_Discrete_DpmTable *table)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_smc_acp_level(काष्ठा pp_hwmgr *hwmgr,
		SMU71_Discrete_DpmTable *table)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_memory_timing_parameters(
		काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t engine_घड़ी,
		uपूर्णांक32_t memory_घड़ी,
		काष्ठा SMU71_Discrete_MCArbDramTimingTableEntry *arb_regs
		)
अणु
	uपूर्णांक32_t dramTiming;
	uपूर्णांक32_t dramTiming2;
	uपूर्णांक32_t burstTime;
	पूर्णांक result;

	result = atomctrl_set_engine_dram_timings_rv770(hwmgr,
				engine_घड़ी, memory_घड़ी);

	PP_ASSERT_WITH_CODE(result == 0,
		"Error calling VBIOS to set DRAM_TIMING.", वापस result);

	dramTiming  = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING);
	dramTiming2 = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_ARB_DRAM_TIMING2);
	burstTime = PHM_READ_FIELD(hwmgr->device, MC_ARB_BURST_TIME, STATE0);

	arb_regs->McArbDramTiming  = PP_HOST_TO_SMC_UL(dramTiming);
	arb_regs->McArbDramTiming2 = PP_HOST_TO_SMC_UL(dramTiming2);
	arb_regs->McArbBurstTime = (uपूर्णांक8_t)burstTime;

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_program_memory_timing_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	पूर्णांक result = 0;
	SMU71_Discrete_MCArbDramTimingTable  arb_regs;
	uपूर्णांक32_t i, j;

	स_रखो(&arb_regs, 0x00, माप(SMU71_Discrete_MCArbDramTimingTable));

	क्रम (i = 0; i < data->dpm_table.sclk_table.count; i++) अणु
		क्रम (j = 0; j < data->dpm_table.mclk_table.count; j++) अणु
			result = iceland_populate_memory_timing_parameters
				(hwmgr, data->dpm_table.sclk_table.dpm_levels[i].value,
				 data->dpm_table.mclk_table.dpm_levels[j].value,
				 &arb_regs.entries[i][j]);

			अगर (0 != result) अणु
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (0 == result) अणु
		result = smu7_copy_bytes_to_smc(
				hwmgr,
				smu_data->smu7_data.arb_table_start,
				(uपूर्णांक8_t *)&arb_regs,
				माप(SMU71_Discrete_MCArbDramTimingTable),
				SMC_RAM_END
				);
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक iceland_populate_smc_boot_level(काष्ठा pp_hwmgr *hwmgr,
			SMU71_Discrete_DpmTable *table)
अणु
	पूर्णांक result = 0;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	table->GraphicsBootLevel = 0;
	table->MemoryBootLevel = 0;

	/* find boot level from dpm table*/
	result = phm_find_boot_level(&(data->dpm_table.sclk_table),
			data->vbios_boot_state.sclk_bootup_value,
			(uपूर्णांक32_t *)&(smu_data->smc_state_table.GraphicsBootLevel));

	अगर (0 != result) अणु
		smu_data->smc_state_table.GraphicsBootLevel = 0;
		pr_err("VBIOS did not find boot engine clock value in dependency table. Using Graphics DPM level 0!\n");
		result = 0;
	पूर्ण

	result = phm_find_boot_level(&(data->dpm_table.mclk_table),
		data->vbios_boot_state.mclk_bootup_value,
		(uपूर्णांक32_t *)&(smu_data->smc_state_table.MemoryBootLevel));

	अगर (0 != result) अणु
		smu_data->smc_state_table.MemoryBootLevel = 0;
		pr_err("VBIOS did not find boot engine clock value in dependency table. Using Memory DPM level 0!\n");
		result = 0;
	पूर्ण

	table->BootVddc = data->vbios_boot_state.vddc_bootup_value;
	अगर (SMU7_VOLTAGE_CONTROL_NONE == data->vddci_control)
		table->BootVddci = table->BootVddc;
	अन्यथा
		table->BootVddci = data->vbios_boot_state.vddci_bootup_value;

	table->BootMVdd = data->vbios_boot_state.mvdd_bootup_value;

	वापस result;
पूर्ण

अटल पूर्णांक iceland_populate_mc_reg_address(काष्ठा pp_hwmgr *hwmgr,
				 SMU71_Discrete_MCRegisters *mc_reg_table)
अणु
	स्थिर काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)hwmgr->smu_backend;

	uपूर्णांक32_t i, j;

	क्रम (i = 0, j = 0; j < smu_data->mc_reg_table.last; j++) अणु
		अगर (smu_data->mc_reg_table.validflag & 1<<j) अणु
			PP_ASSERT_WITH_CODE(i < SMU71_DISCRETE_MC_REGISTER_ARRAY_SIZE,
				"Index of mc_reg_table->address[] array out of boundary", वापस -EINVAL);
			mc_reg_table->address[i].s0 =
				PP_HOST_TO_SMC_US(smu_data->mc_reg_table.mc_reg_address[j].s0);
			mc_reg_table->address[i].s1 =
				PP_HOST_TO_SMC_US(smu_data->mc_reg_table.mc_reg_address[j].s1);
			i++;
		पूर्ण
	पूर्ण

	mc_reg_table->last = (uपूर्णांक8_t)i;

	वापस 0;
पूर्ण

/*convert रेजिस्टर values from driver to SMC क्रमmat */
अटल व्योम iceland_convert_mc_रेजिस्टरs(
	स्थिर काष्ठा iceland_mc_reg_entry *entry,
	SMU71_Discrete_MCRegisterSet *data,
	uपूर्णांक32_t num_entries, uपूर्णांक32_t valid_flag)
अणु
	uपूर्णांक32_t i, j;

	क्रम (i = 0, j = 0; j < num_entries; j++) अणु
		अगर (valid_flag & 1<<j) अणु
			data->value[i] = PP_HOST_TO_SMC_UL(entry->mc_data[j]);
			i++;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक iceland_convert_mc_reg_table_entry_to_smc(काष्ठा pp_hwmgr *hwmgr,
		स्थिर uपूर्णांक32_t memory_घड़ी,
		SMU71_Discrete_MCRegisterSet *mc_reg_table_data
		)
अणु
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t i = 0;

	क्रम (i = 0; i < smu_data->mc_reg_table.num_entries; i++) अणु
		अगर (memory_घड़ी <=
			smu_data->mc_reg_table.mc_reg_table_entry[i].mclk_max) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((i == smu_data->mc_reg_table.num_entries) && (i > 0))
		--i;

	iceland_convert_mc_रेजिस्टरs(&smu_data->mc_reg_table.mc_reg_table_entry[i],
				mc_reg_table_data, smu_data->mc_reg_table.last,
				smu_data->mc_reg_table.validflag);

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_convert_mc_reg_table_to_smc(काष्ठा pp_hwmgr *hwmgr,
		SMU71_Discrete_MCRegisters *mc_regs)
अणु
	पूर्णांक result = 0;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	पूर्णांक res;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < data->dpm_table.mclk_table.count; i++) अणु
		res = iceland_convert_mc_reg_table_entry_to_smc(
				hwmgr,
				data->dpm_table.mclk_table.dpm_levels[i].value,
				&mc_regs->data[i]
				);

		अगर (0 != res)
			result = res;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक iceland_update_and_upload_mc_reg_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	uपूर्णांक32_t address;
	पूर्णांक32_t result;

	अगर (0 == (data->need_update_smu7_dpm_table & DPMTABLE_OD_UPDATE_MCLK))
		वापस 0;


	स_रखो(&smu_data->mc_regs, 0, माप(SMU71_Discrete_MCRegisters));

	result = iceland_convert_mc_reg_table_to_smc(hwmgr, &(smu_data->mc_regs));

	अगर (result != 0)
		वापस result;


	address = smu_data->smu7_data.mc_reg_table_start + (uपूर्णांक32_t)दुरत्व(SMU71_Discrete_MCRegisters, data[0]);

	वापस  smu7_copy_bytes_to_smc(hwmgr, address,
				 (uपूर्णांक8_t *)&smu_data->mc_regs.data[0],
				माप(SMU71_Discrete_MCRegisterSet) * data->dpm_table.mclk_table.count,
				SMC_RAM_END);
पूर्ण

अटल पूर्णांक iceland_populate_initial_mc_reg_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);

	स_रखो(&smu_data->mc_regs, 0x00, माप(SMU71_Discrete_MCRegisters));
	result = iceland_populate_mc_reg_address(hwmgr, &(smu_data->mc_regs));
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to initialize MCRegTable for the MC register addresses!", वापस result;);

	result = iceland_convert_mc_reg_table_to_smc(hwmgr, &smu_data->mc_regs);
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to initialize MCRegTable for driver state!", वापस result;);

	वापस smu7_copy_bytes_to_smc(hwmgr, smu_data->smu7_data.mc_reg_table_start,
			(uपूर्णांक8_t *)&smu_data->mc_regs, माप(SMU71_Discrete_MCRegisters), SMC_RAM_END);
पूर्ण

अटल पूर्णांक iceland_populate_smc_initial_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक8_t count, level;

	count = (uपूर्णांक8_t)(hwmgr->dyn_state.vddc_dependency_on_sclk->count);

	क्रम (level = 0; level < count; level++) अणु
		अगर (hwmgr->dyn_state.vddc_dependency_on_sclk->entries[level].clk
			 >= data->vbios_boot_state.sclk_bootup_value) अणु
			smu_data->smc_state_table.GraphicsBootLevel = level;
			अवरोध;
		पूर्ण
	पूर्ण

	count = (uपूर्णांक8_t)(hwmgr->dyn_state.vddc_dependency_on_mclk->count);

	क्रम (level = 0; level < count; level++) अणु
		अगर (hwmgr->dyn_state.vddc_dependency_on_mclk->entries[level].clk
			>= data->vbios_boot_state.mclk_bootup_value) अणु
			smu_data->smc_state_table.MemoryBootLevel = level;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_bapm_parameters_in_dpm_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	स्थिर काष्ठा iceland_pt_शेषs *शेषs = smu_data->घातer_tune_शेषs;
	SMU71_Discrete_DpmTable  *dpm_table = &(smu_data->smc_state_table);
	काष्ठा phm_cac_tdp_table *cac_dtp_table = hwmgr->dyn_state.cac_dtp_table;
	काष्ठा phm_ppm_table *ppm = hwmgr->dyn_state.ppm_parameter_table;
	स्थिर uपूर्णांक16_t *def1, *def2;
	पूर्णांक i, j, k;


	/*
	 * TDP number of fraction bits are changed from 8 to 7 क्रम Iceland
	 * as requested by SMC team
	 */

	dpm_table->DefaultTdp = PP_HOST_TO_SMC_US((uपूर्णांक16_t)(cac_dtp_table->usTDP * 256));
	dpm_table->TargetTdp = PP_HOST_TO_SMC_US((uपूर्णांक16_t)(cac_dtp_table->usConfigurableTDP * 256));


	dpm_table->DTETjOffset = 0;

	dpm_table->GpuTjMax = (uपूर्णांक8_t)(data->thermal_temp_setting.temperature_high / PP_TEMPERATURE_UNITS_PER_CENTIGRADES);
	dpm_table->GpuTjHyst = 8;

	dpm_table->DTEAmbientTempBase = शेषs->dte_ambient_temp_base;

	/* The following are क्रम new Iceland Multi-input fan/thermal control */
	अगर (शून्य != ppm) अणु
		dpm_table->PPM_PkgPwrLimit = (uपूर्णांक16_t)ppm->dgpu_tdp * 256 / 1000;
		dpm_table->PPM_TemperatureLimit = (uपूर्णांक16_t)ppm->tj_max * 256;
	पूर्ण अन्यथा अणु
		dpm_table->PPM_PkgPwrLimit = 0;
		dpm_table->PPM_TemperatureLimit = 0;
	पूर्ण

	CONVERT_FROM_HOST_TO_SMC_US(dpm_table->PPM_PkgPwrLimit);
	CONVERT_FROM_HOST_TO_SMC_US(dpm_table->PPM_TemperatureLimit);

	dpm_table->BAPM_TEMP_GRADIENT = PP_HOST_TO_SMC_UL(शेषs->bapm_temp_gradient);
	def1 = शेषs->bapmti_r;
	def2 = शेषs->bapmti_rc;

	क्रम (i = 0; i < SMU71_DTE_ITERATIONS; i++) अणु
		क्रम (j = 0; j < SMU71_DTE_SOURCES; j++) अणु
			क्रम (k = 0; k < SMU71_DTE_SINKS; k++) अणु
				dpm_table->BAPMTI_R[i][j][k] = PP_HOST_TO_SMC_US(*def1);
				dpm_table->BAPMTI_RC[i][j][k] = PP_HOST_TO_SMC_US(*def2);
				def1++;
				def2++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_populate_smc_svi2_config(काष्ठा pp_hwmgr *hwmgr,
					    SMU71_Discrete_DpmTable *tab)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->voltage_control)
		tab->SVI2Enable |= VDDC_ON_SVI2;

	अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->vddci_control)
		tab->SVI2Enable |= VDDCI_ON_SVI2;
	अन्यथा
		tab->MergedVddci = 1;

	अगर (SMU7_VOLTAGE_CONTROL_BY_SVID2 == data->mvdd_control)
		tab->SVI2Enable |= MVDD_ON_SVI2;

	PP_ASSERT_WITH_CODE(tab->SVI2Enable != (VDDC_ON_SVI2 | VDDCI_ON_SVI2 | MVDD_ON_SVI2) &&
		(tab->SVI2Enable & VDDC_ON_SVI2), "SVI2 domain configuration is incorrect!", वापस -EINVAL);

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_init_smc_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	SMU71_Discrete_DpmTable  *table = &(smu_data->smc_state_table);


	iceland_initialize_घातer_tune_शेषs(hwmgr);
	स_रखो(&(smu_data->smc_state_table), 0x00, माप(smu_data->smc_state_table));

	अगर (SMU7_VOLTAGE_CONTROL_NONE != data->voltage_control) अणु
		iceland_populate_smc_voltage_tables(hwmgr, table);
	पूर्ण

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_AutomaticDCTransition))
		table->SystemFlags |= PPSMC_SYSTEMFLAG_GPIO_DC;


	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_StepVddc))
		table->SystemFlags |= PPSMC_SYSTEMFLAG_STEPVDDC;

	अगर (data->is_memory_gddr5)
		table->SystemFlags |= PPSMC_SYSTEMFLAG_GDDR5;


	अगर (data->ulv_supported) अणु
		result = iceland_populate_ulv_state(hwmgr, &(smu_data->ulv_setting));
		PP_ASSERT_WITH_CODE(0 == result,
			"Failed to initialize ULV state!", वापस result;);

		cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
			ixCG_ULV_PARAMETER, 0x40035);
	पूर्ण

	result = iceland_populate_smc_link_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to initialize Link Level!", वापस result;);

	result = iceland_populate_all_graphic_levels(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to initialize Graphics Level!", वापस result;);

	result = iceland_populate_all_memory_levels(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to initialize Memory Level!", वापस result;);

	result = iceland_populate_smc_acpi_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to initialize ACPI Level!", वापस result;);

	result = iceland_populate_smc_vce_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to initialize VCE Level!", वापस result;);

	result = iceland_populate_smc_acp_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to initialize ACP Level!", वापस result;);

	/* Since only the initial state is completely set up at this poपूर्णांक (the other states are just copies of the boot state) we only */
	/* need to populate the  ARB settings क्रम the initial state. */
	result = iceland_program_memory_timing_parameters(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to Write ARB settings for the initial state.", वापस result;);

	result = iceland_populate_smc_uvd_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to initialize UVD Level!", वापस result;);

	table->GraphicsBootLevel = 0;
	table->MemoryBootLevel = 0;

	result = iceland_populate_smc_boot_level(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to initialize Boot Level!", वापस result;);

	result = iceland_populate_smc_initial_state(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result, "Failed to initialize Boot State!", वापस result);

	result = iceland_populate_bapm_parameters_in_dpm_table(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result, "Failed to populate BAPM Parameters!", वापस result);

	table->GraphicsVoltageChangeEnable  = 1;
	table->GraphicsThermThrottleEnable  = 1;
	table->GraphicsInterval = 1;
	table->VoltageInterval  = 1;
	table->ThermalInterval  = 1;

	table->TemperatureLimitHigh =
		(data->thermal_temp_setting.temperature_high *
		 SMU7_Q88_FORMAT_CONVERSION_UNIT) / PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	table->TemperatureLimitLow =
		(data->thermal_temp_setting.temperature_low *
		SMU7_Q88_FORMAT_CONVERSION_UNIT) / PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	table->MemoryVoltageChangeEnable  = 1;
	table->MemoryInterval  = 1;
	table->VoltageResponseTime  = 0;
	table->PhaseResponseTime  = 0;
	table->MemoryThermThrottleEnable  = 1;
	table->PCIeBootLinkLevel = 0;
	table->PCIeGenInterval = 1;

	result = iceland_populate_smc_svi2_config(hwmgr, table);
	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to populate SVI2 setting!", वापस result);

	table->ThermGpio  = 17;
	table->SclkStepSize = 0x4000;

	CONVERT_FROM_HOST_TO_SMC_UL(table->SystemFlags);
	CONVERT_FROM_HOST_TO_SMC_UL(table->SmioMaskVddcVid);
	CONVERT_FROM_HOST_TO_SMC_UL(table->SmioMaskVddcPhase);
	CONVERT_FROM_HOST_TO_SMC_UL(table->SmioMaskVddciVid);
	CONVERT_FROM_HOST_TO_SMC_UL(table->SmioMaskMvddVid);
	CONVERT_FROM_HOST_TO_SMC_UL(table->SclkStepSize);
	CONVERT_FROM_HOST_TO_SMC_US(table->TemperatureLimitHigh);
	CONVERT_FROM_HOST_TO_SMC_US(table->TemperatureLimitLow);
	CONVERT_FROM_HOST_TO_SMC_US(table->VoltageResponseTime);
	CONVERT_FROM_HOST_TO_SMC_US(table->PhaseResponseTime);

	table->BootVddc = PP_HOST_TO_SMC_US(table->BootVddc * VOLTAGE_SCALE);
	table->BootVddci = PP_HOST_TO_SMC_US(table->BootVddci * VOLTAGE_SCALE);
	table->BootMVdd = PP_HOST_TO_SMC_US(table->BootMVdd * VOLTAGE_SCALE);

	/* Upload all dpm data to SMC memory.(dpm level, dpm level count etc) */
	result = smu7_copy_bytes_to_smc(hwmgr, smu_data->smu7_data.dpm_table_start +
										दुरत्व(SMU71_Discrete_DpmTable, SystemFlags),
										(uपूर्णांक8_t *)&(table->SystemFlags),
										माप(SMU71_Discrete_DpmTable)-3 * माप(SMU71_PIDController),
										SMC_RAM_END);

	PP_ASSERT_WITH_CODE(0 == result,
		"Failed to upload dpm data to SMC memory!", वापस result;);

	/* Upload all ulv setting to SMC memory.(dpm level, dpm level count etc) */
	result = smu7_copy_bytes_to_smc(hwmgr,
			smu_data->smu7_data.ulv_setting_starts,
			(uपूर्णांक8_t *)&(smu_data->ulv_setting),
			माप(SMU71_Discrete_Ulv),
			SMC_RAM_END);


	result = iceland_populate_initial_mc_reg_table(hwmgr);
	PP_ASSERT_WITH_CODE((0 == result),
		"Failed to populate initialize MC Reg table!", वापस result);

	result = iceland_populate_pm_fuses(hwmgr);
	PP_ASSERT_WITH_CODE(0 == result,
			"Failed to  populate PM fuses to SMC memory!", वापस result);

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_thermal_setup_fan_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_smumgr *smu7_data = (काष्ठा smu7_smumgr *)(hwmgr->smu_backend);
	SMU71_Discrete_FanTable fan_table = अणु FDO_MODE_HARDWARE पूर्ण;
	uपूर्णांक32_t duty100;
	uपूर्णांक32_t t_dअगरf1, t_dअगरf2, pwm_dअगरf1, pwm_dअगरf2;
	uपूर्णांक16_t fकरो_min, slope1, slope2;
	uपूर्णांक32_t reference_घड़ी;
	पूर्णांक res;
	uपूर्णांक64_t पंचांगp64;

	अगर (!phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_MicrocodeFanControl))
		वापस 0;

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_MicrocodeFanControl);
		वापस 0;
	पूर्ण

	अगर (0 == smu7_data->fan_table_start) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_MicrocodeFanControl);
		वापस 0;
	पूर्ण

	duty100 = PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, CG_FDO_CTRL1, FMAX_DUTY100);

	अगर (0 == duty100) अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_MicrocodeFanControl);
		वापस 0;
	पूर्ण

	पंचांगp64 = hwmgr->thermal_controller.advanceFanControlParameters.usPWMMin * duty100;
	करो_भाग(पंचांगp64, 10000);
	fकरो_min = (uपूर्णांक16_t)पंचांगp64;

	t_dअगरf1 = hwmgr->thermal_controller.advanceFanControlParameters.usTMed - hwmgr->thermal_controller.advanceFanControlParameters.usTMin;
	t_dअगरf2 = hwmgr->thermal_controller.advanceFanControlParameters.usTHigh - hwmgr->thermal_controller.advanceFanControlParameters.usTMed;

	pwm_dअगरf1 = hwmgr->thermal_controller.advanceFanControlParameters.usPWMMed - hwmgr->thermal_controller.advanceFanControlParameters.usPWMMin;
	pwm_dअगरf2 = hwmgr->thermal_controller.advanceFanControlParameters.usPWMHigh - hwmgr->thermal_controller.advanceFanControlParameters.usPWMMed;

	slope1 = (uपूर्णांक16_t)((50 + ((16 * duty100 * pwm_dअगरf1) / t_dअगरf1)) / 100);
	slope2 = (uपूर्णांक16_t)((50 + ((16 * duty100 * pwm_dअगरf2) / t_dअगरf2)) / 100);

	fan_table.TempMin = cpu_to_be16((50 + hwmgr->thermal_controller.advanceFanControlParameters.usTMin) / 100);
	fan_table.TempMed = cpu_to_be16((50 + hwmgr->thermal_controller.advanceFanControlParameters.usTMed) / 100);
	fan_table.TempMax = cpu_to_be16((50 + hwmgr->thermal_controller.advanceFanControlParameters.usTMax) / 100);

	fan_table.Slope1 = cpu_to_be16(slope1);
	fan_table.Slope2 = cpu_to_be16(slope2);

	fan_table.FकरोMin = cpu_to_be16(fकरो_min);

	fan_table.HystDown = cpu_to_be16(hwmgr->thermal_controller.advanceFanControlParameters.ucTHyst);

	fan_table.HystUp = cpu_to_be16(1);

	fan_table.HystSlope = cpu_to_be16(1);

	fan_table.TempRespLim = cpu_to_be16(5);

	reference_घड़ी = amdgpu_asic_get_xclk((काष्ठा amdgpu_device *)hwmgr->adev);

	fan_table.RefreshPeriod = cpu_to_be32((hwmgr->thermal_controller.advanceFanControlParameters.ulCycleDelay * reference_घड़ी) / 1600);

	fan_table.FकरोMax = cpu_to_be16((uपूर्णांक16_t)duty100);

	fan_table.TempSrc = (uपूर्णांक8_t)PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, CG_MULT_THERMAL_CTRL, TEMP_SEL);

	/* fan_table.FanControl_GL_Flag = 1; */

	res = smu7_copy_bytes_to_smc(hwmgr, smu7_data->fan_table_start, (uपूर्णांक8_t *)&fan_table, (uपूर्णांक32_t)माप(fan_table), SMC_RAM_END);

	वापस res;
पूर्ण


अटल पूर्णांक iceland_program_mem_timing_parameters(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	अगर (data->need_update_smu7_dpm_table &
		(DPMTABLE_OD_UPDATE_SCLK + DPMTABLE_OD_UPDATE_MCLK))
		वापस iceland_program_memory_timing_parameters(hwmgr);

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_update_sclk_threshold(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);

	पूर्णांक result = 0;
	uपूर्णांक32_t low_sclk_पूर्णांकerrupt_threshold = 0;

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SclkThrottleLowNotअगरication)
		&& (data->low_sclk_पूर्णांकerrupt_threshold != 0)) अणु
		low_sclk_पूर्णांकerrupt_threshold =
				data->low_sclk_पूर्णांकerrupt_threshold;

		CONVERT_FROM_HOST_TO_SMC_UL(low_sclk_पूर्णांकerrupt_threshold);

		result = smu7_copy_bytes_to_smc(
				hwmgr,
				smu_data->smu7_data.dpm_table_start +
				दुरत्व(SMU71_Discrete_DpmTable,
					LowSclkInterruptThreshold),
				(uपूर्णांक8_t *)&low_sclk_पूर्णांकerrupt_threshold,
				माप(uपूर्णांक32_t),
				SMC_RAM_END);
	पूर्ण

	result = iceland_update_and_upload_mc_reg_table(hwmgr);

	PP_ASSERT_WITH_CODE((0 == result), "Failed to upload MC reg table!", वापस result);

	result = iceland_program_mem_timing_parameters(hwmgr);
	PP_ASSERT_WITH_CODE((result == 0),
			"Failed to program memory timing parameters!",
			);

	वापस result;
पूर्ण

अटल uपूर्णांक32_t iceland_get_दुरत्व(uपूर्णांक32_t type, uपूर्णांक32_t member)
अणु
	चयन (type) अणु
	हाल SMU_SoftRegisters:
		चयन (member) अणु
		हाल HandshakeDisables:
			वापस दुरत्व(SMU71_SoftRegisters, HandshakeDisables);
		हाल VoltageChangeTimeout:
			वापस दुरत्व(SMU71_SoftRegisters, VoltageChangeTimeout);
		हाल AverageGraphicsActivity:
			वापस दुरत्व(SMU71_SoftRegisters, AverageGraphicsActivity);
		हाल AverageMemoryActivity:
			वापस दुरत्व(SMU71_SoftRegisters, AverageMemoryActivity);
		हाल PreVBlankGap:
			वापस दुरत्व(SMU71_SoftRegisters, PreVBlankGap);
		हाल VBlankTimeout:
			वापस दुरत्व(SMU71_SoftRegisters, VBlankTimeout);
		हाल UcodeLoadStatus:
			वापस दुरत्व(SMU71_SoftRegisters, UcodeLoadStatus);
		हाल DRAM_LOG_ADDR_H:
			वापस दुरत्व(SMU71_SoftRegisters, DRAM_LOG_ADDR_H);
		हाल DRAM_LOG_ADDR_L:
			वापस दुरत्व(SMU71_SoftRegisters, DRAM_LOG_ADDR_L);
		हाल DRAM_LOG_PHY_ADDR_H:
			वापस दुरत्व(SMU71_SoftRegisters, DRAM_LOG_PHY_ADDR_H);
		हाल DRAM_LOG_PHY_ADDR_L:
			वापस दुरत्व(SMU71_SoftRegisters, DRAM_LOG_PHY_ADDR_L);
		हाल DRAM_LOG_BUFF_SIZE:
			वापस दुरत्व(SMU71_SoftRegisters, DRAM_LOG_BUFF_SIZE);
		पूर्ण
		अवरोध;
	हाल SMU_Discrete_DpmTable:
		चयन (member) अणु
		हाल LowSclkInterruptThreshold:
			वापस दुरत्व(SMU71_Discrete_DpmTable, LowSclkInterruptThreshold);
		पूर्ण
		अवरोध;
	पूर्ण
	pr_warn("can't get the offset of type %x member %x\n", type, member);
	वापस 0;
पूर्ण

अटल uपूर्णांक32_t iceland_get_mac_definition(uपूर्णांक32_t value)
अणु
	चयन (value) अणु
	हाल SMU_MAX_LEVELS_GRAPHICS:
		वापस SMU71_MAX_LEVELS_GRAPHICS;
	हाल SMU_MAX_LEVELS_MEMORY:
		वापस SMU71_MAX_LEVELS_MEMORY;
	हाल SMU_MAX_LEVELS_LINK:
		वापस SMU71_MAX_LEVELS_LINK;
	हाल SMU_MAX_ENTRIES_SMIO:
		वापस SMU71_MAX_ENTRIES_SMIO;
	हाल SMU_MAX_LEVELS_VDDC:
		वापस SMU71_MAX_LEVELS_VDDC;
	हाल SMU_MAX_LEVELS_VDDCI:
		वापस SMU71_MAX_LEVELS_VDDCI;
	हाल SMU_MAX_LEVELS_MVDD:
		वापस SMU71_MAX_LEVELS_MVDD;
	पूर्ण

	pr_warn("can't get the mac of %x\n", value);
	वापस 0;
पूर्ण

अटल पूर्णांक iceland_process_firmware_header(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);
	काष्ठा smu7_smumgr *smu7_data = (काष्ठा smu7_smumgr *)(hwmgr->smu_backend);

	uपूर्णांक32_t पंचांगp;
	पूर्णांक result;
	bool error = false;

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU71_Firmware_Header, DpmTable),
				&पंचांगp, SMC_RAM_END);

	अगर (0 == result) अणु
		smu7_data->dpm_table_start = पंचांगp;
	पूर्ण

	error |= (0 != result);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU71_Firmware_Header, SoftRegisters),
				&पंचांगp, SMC_RAM_END);

	अगर (0 == result) अणु
		data->soft_regs_start = पंचांगp;
		smu7_data->soft_regs_start = पंचांगp;
	पूर्ण

	error |= (0 != result);


	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU71_Firmware_Header, mcRegisterTable),
				&पंचांगp, SMC_RAM_END);

	अगर (0 == result) अणु
		smu7_data->mc_reg_table_start = पंचांगp;
	पूर्ण

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU71_Firmware_Header, FanTable),
				&पंचांगp, SMC_RAM_END);

	अगर (0 == result) अणु
		smu7_data->fan_table_start = पंचांगp;
	पूर्ण

	error |= (0 != result);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU71_Firmware_Header, mcArbDramTimingTable),
				&पंचांगp, SMC_RAM_END);

	अगर (0 == result) अणु
		smu7_data->arb_table_start = पंचांगp;
	पूर्ण

	error |= (0 != result);


	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU71_Firmware_Header, Version),
				&पंचांगp, SMC_RAM_END);

	अगर (0 == result) अणु
		hwmgr->microcode_version_info.SMC = पंचांगp;
	पूर्ण

	error |= (0 != result);

	result = smu7_पढ़ो_smc_sram_dword(hwmgr,
				SMU71_FIRMWARE_HEADER_LOCATION +
				दुरत्व(SMU71_Firmware_Header, UlvSettings),
				&पंचांगp, SMC_RAM_END);

	अगर (0 == result) अणु
		smu7_data->ulv_setting_starts = पंचांगp;
	पूर्ण

	error |= (0 != result);

	वापस error ? 1 : 0;
पूर्ण

/*---------------------------MC----------------------------*/

अटल uपूर्णांक8_t iceland_get_memory_modile_index(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस (uपूर्णांक8_t) (0xFF & (cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmBIOS_SCRATCH_4) >> 16));
पूर्ण

अटल bool iceland_check_s0_mc_reg_index(uपूर्णांक16_t in_reg, uपूर्णांक16_t *out_reg)
अणु
	bool result = true;

	चयन (in_reg) अणु
	हाल  mmMC_SEQ_RAS_TIMING:
		*out_reg = mmMC_SEQ_RAS_TIMING_LP;
		अवरोध;

	हाल  mmMC_SEQ_DLL_STBY:
		*out_reg = mmMC_SEQ_DLL_STBY_LP;
		अवरोध;

	हाल  mmMC_SEQ_G5PDX_CMD0:
		*out_reg = mmMC_SEQ_G5PDX_CMD0_LP;
		अवरोध;

	हाल  mmMC_SEQ_G5PDX_CMD1:
		*out_reg = mmMC_SEQ_G5PDX_CMD1_LP;
		अवरोध;

	हाल  mmMC_SEQ_G5PDX_CTRL:
		*out_reg = mmMC_SEQ_G5PDX_CTRL_LP;
		अवरोध;

	हाल mmMC_SEQ_CAS_TIMING:
		*out_reg = mmMC_SEQ_CAS_TIMING_LP;
		अवरोध;

	हाल mmMC_SEQ_MISC_TIMING:
		*out_reg = mmMC_SEQ_MISC_TIMING_LP;
		अवरोध;

	हाल mmMC_SEQ_MISC_TIMING2:
		*out_reg = mmMC_SEQ_MISC_TIMING2_LP;
		अवरोध;

	हाल mmMC_SEQ_PMG_DVS_CMD:
		*out_reg = mmMC_SEQ_PMG_DVS_CMD_LP;
		अवरोध;

	हाल mmMC_SEQ_PMG_DVS_CTL:
		*out_reg = mmMC_SEQ_PMG_DVS_CTL_LP;
		अवरोध;

	हाल mmMC_SEQ_RD_CTL_D0:
		*out_reg = mmMC_SEQ_RD_CTL_D0_LP;
		अवरोध;

	हाल mmMC_SEQ_RD_CTL_D1:
		*out_reg = mmMC_SEQ_RD_CTL_D1_LP;
		अवरोध;

	हाल mmMC_SEQ_WR_CTL_D0:
		*out_reg = mmMC_SEQ_WR_CTL_D0_LP;
		अवरोध;

	हाल mmMC_SEQ_WR_CTL_D1:
		*out_reg = mmMC_SEQ_WR_CTL_D1_LP;
		अवरोध;

	हाल mmMC_PMG_CMD_EMRS:
		*out_reg = mmMC_SEQ_PMG_CMD_EMRS_LP;
		अवरोध;

	हाल mmMC_PMG_CMD_MRS:
		*out_reg = mmMC_SEQ_PMG_CMD_MRS_LP;
		अवरोध;

	हाल mmMC_PMG_CMD_MRS1:
		*out_reg = mmMC_SEQ_PMG_CMD_MRS1_LP;
		अवरोध;

	हाल mmMC_SEQ_PMG_TIMING:
		*out_reg = mmMC_SEQ_PMG_TIMING_LP;
		अवरोध;

	हाल mmMC_PMG_CMD_MRS2:
		*out_reg = mmMC_SEQ_PMG_CMD_MRS2_LP;
		अवरोध;

	हाल mmMC_SEQ_WR_CTL_2:
		*out_reg = mmMC_SEQ_WR_CTL_2_LP;
		अवरोध;

	शेष:
		result = false;
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक iceland_set_s0_mc_reg_index(काष्ठा iceland_mc_reg_table *table)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक16_t address;

	क्रम (i = 0; i < table->last; i++) अणु
		table->mc_reg_address[i].s0 =
			iceland_check_s0_mc_reg_index(table->mc_reg_address[i].s1, &address)
			? address : table->mc_reg_address[i].s1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक iceland_copy_vbios_smc_reg_table(स्थिर pp_atomctrl_mc_reg_table *table,
					काष्ठा iceland_mc_reg_table *ni_table)
अणु
	uपूर्णांक8_t i, j;

	PP_ASSERT_WITH_CODE((table->last <= SMU71_DISCRETE_MC_REGISTER_ARRAY_SIZE),
		"Invalid VramInfo table.", वापस -EINVAL);
	PP_ASSERT_WITH_CODE((table->num_entries <= MAX_AC_TIMING_ENTRIES),
		"Invalid VramInfo table.", वापस -EINVAL);

	क्रम (i = 0; i < table->last; i++) अणु
		ni_table->mc_reg_address[i].s1 = table->mc_reg_address[i].s1;
	पूर्ण
	ni_table->last = table->last;

	क्रम (i = 0; i < table->num_entries; i++) अणु
		ni_table->mc_reg_table_entry[i].mclk_max =
			table->mc_reg_table_entry[i].mclk_max;
		क्रम (j = 0; j < table->last; j++) अणु
			ni_table->mc_reg_table_entry[i].mc_data[j] =
				table->mc_reg_table_entry[i].mc_data[j];
		पूर्ण
	पूर्ण

	ni_table->num_entries = table->num_entries;

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_set_mc_special_रेजिस्टरs(काष्ठा pp_hwmgr *hwmgr,
					काष्ठा iceland_mc_reg_table *table)
अणु
	uपूर्णांक8_t i, j, k;
	uपूर्णांक32_t temp_reg;
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	क्रम (i = 0, j = table->last; i < table->last; i++) अणु
		PP_ASSERT_WITH_CODE((j < SMU71_DISCRETE_MC_REGISTER_ARRAY_SIZE),
			"Invalid VramInfo table.", वापस -EINVAL);

		चयन (table->mc_reg_address[i].s1) अणु

		हाल mmMC_SEQ_MISC1:
			temp_reg = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_PMG_CMD_EMRS);
			table->mc_reg_address[j].s1 = mmMC_PMG_CMD_EMRS;
			table->mc_reg_address[j].s0 = mmMC_SEQ_PMG_CMD_EMRS_LP;
			क्रम (k = 0; k < table->num_entries; k++) अणु
				table->mc_reg_table_entry[k].mc_data[j] =
					((temp_reg & 0xffff0000)) |
					((table->mc_reg_table_entry[k].mc_data[i] & 0xffff0000) >> 16);
			पूर्ण
			j++;

			PP_ASSERT_WITH_CODE((j < SMU71_DISCRETE_MC_REGISTER_ARRAY_SIZE),
				"Invalid VramInfo table.", वापस -EINVAL);
			temp_reg = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_PMG_CMD_MRS);
			table->mc_reg_address[j].s1 = mmMC_PMG_CMD_MRS;
			table->mc_reg_address[j].s0 = mmMC_SEQ_PMG_CMD_MRS_LP;
			क्रम (k = 0; k < table->num_entries; k++) अणु
				table->mc_reg_table_entry[k].mc_data[j] =
					(temp_reg & 0xffff0000) |
					(table->mc_reg_table_entry[k].mc_data[i] & 0x0000ffff);

				अगर (!data->is_memory_gddr5) अणु
					table->mc_reg_table_entry[k].mc_data[j] |= 0x100;
				पूर्ण
			पूर्ण
			j++;

			अगर (!data->is_memory_gddr5) अणु
				PP_ASSERT_WITH_CODE((j < SMU71_DISCRETE_MC_REGISTER_ARRAY_SIZE),
					"Invalid VramInfo table.", वापस -EINVAL);
				table->mc_reg_address[j].s1 = mmMC_PMG_AUTO_CMD;
				table->mc_reg_address[j].s0 = mmMC_PMG_AUTO_CMD;
				क्रम (k = 0; k < table->num_entries; k++) अणु
					table->mc_reg_table_entry[k].mc_data[j] =
						(table->mc_reg_table_entry[k].mc_data[i] & 0xffff0000) >> 16;
				पूर्ण
				j++;
			पूर्ण

			अवरोध;

		हाल mmMC_SEQ_RESERVE_M:
			temp_reg = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_PMG_CMD_MRS1);
			table->mc_reg_address[j].s1 = mmMC_PMG_CMD_MRS1;
			table->mc_reg_address[j].s0 = mmMC_SEQ_PMG_CMD_MRS1_LP;
			क्रम (k = 0; k < table->num_entries; k++) अणु
				table->mc_reg_table_entry[k].mc_data[j] =
					(temp_reg & 0xffff0000) |
					(table->mc_reg_table_entry[k].mc_data[i] & 0x0000ffff);
			पूर्ण
			j++;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

	पूर्ण

	table->last = j;

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_set_valid_flag(काष्ठा iceland_mc_reg_table *table)
अणु
	uपूर्णांक8_t i, j;
	क्रम (i = 0; i < table->last; i++) अणु
		क्रम (j = 1; j < table->num_entries; j++) अणु
			अगर (table->mc_reg_table_entry[j-1].mc_data[i] !=
				table->mc_reg_table_entry[j].mc_data[i]) अणु
				table->validflag |= (1<<i);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक iceland_initialize_mc_reg_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	काष्ठा iceland_smumgr *smu_data = (काष्ठा iceland_smumgr *)(hwmgr->smu_backend);
	pp_atomctrl_mc_reg_table *table;
	काष्ठा iceland_mc_reg_table *ni_table = &smu_data->mc_reg_table;
	uपूर्णांक8_t module_index = iceland_get_memory_modile_index(hwmgr);

	table = kzalloc(माप(pp_atomctrl_mc_reg_table), GFP_KERNEL);

	अगर (शून्य == table)
		वापस -ENOMEM;

	/* Program additional LP रेजिस्टरs that are no दीर्घer programmed by VBIOS */
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RAS_TIMING_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RAS_TIMING));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_CAS_TIMING_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_CAS_TIMING));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_DLL_STBY_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_DLL_STBY));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_G5PDX_CMD0_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_G5PDX_CMD0));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_G5PDX_CMD1_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_G5PDX_CMD1));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_G5PDX_CTRL_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_G5PDX_CTRL));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_DVS_CMD_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_DVS_CMD));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_DVS_CTL_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_DVS_CTL));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC_TIMING_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC_TIMING));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC_TIMING2_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_MISC_TIMING2));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_CMD_EMRS_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_PMG_CMD_EMRS));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_CMD_MRS_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_PMG_CMD_MRS));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_CMD_MRS1_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_PMG_CMD_MRS1));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_D0_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_D0));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_D1_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_D1));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RD_CTL_D0_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RD_CTL_D0));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RD_CTL_D1_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_RD_CTL_D1));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_TIMING_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_TIMING));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_PMG_CMD_MRS2_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_PMG_CMD_MRS2));
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_2_LP, cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMC_SEQ_WR_CTL_2));

	result = atomctrl_initialize_mc_reg_table(hwmgr, module_index, table);

	अगर (0 == result)
		result = iceland_copy_vbios_smc_reg_table(table, ni_table);

	अगर (0 == result) अणु
		iceland_set_s0_mc_reg_index(ni_table);
		result = iceland_set_mc_special_रेजिस्टरs(hwmgr, ni_table);
	पूर्ण

	अगर (0 == result)
		iceland_set_valid_flag(ni_table);

	kमुक्त(table);

	वापस result;
पूर्ण

अटल bool iceland_is_dpm_running(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस (1 == PHM_READ_INसूचीECT_FIELD(hwmgr->device,
			CGS_IND_REG__SMC, FEATURE_STATUS, VOLTAGE_CONTROLLER_ON))
			? true : false;
पूर्ण

स्थिर काष्ठा pp_smumgr_func iceland_smu_funcs = अणु
	.name = "iceland_smu",
	.smu_init = &iceland_smu_init,
	.smu_fini = &smu7_smu_fini,
	.start_smu = &iceland_start_smu,
	.check_fw_load_finish = &smu7_check_fw_load_finish,
	.request_smu_load_fw = &smu7_request_smu_load_fw,
	.request_smu_load_specअगरic_fw = &iceland_request_smu_load_specअगरic_fw,
	.send_msg_to_smc = &smu7_send_msg_to_smc,
	.send_msg_to_smc_with_parameter = &smu7_send_msg_to_smc_with_parameter,
	.get_argument = smu7_get_argument,
	.करोwnload_pptable_settings = शून्य,
	.upload_pptable_settings = शून्य,
	.get_दुरत्व = iceland_get_दुरत्व,
	.process_firmware_header = iceland_process_firmware_header,
	.init_smc_table = iceland_init_smc_table,
	.update_sclk_threshold = iceland_update_sclk_threshold,
	.thermal_setup_fan_table = iceland_thermal_setup_fan_table,
	.populate_all_graphic_levels = iceland_populate_all_graphic_levels,
	.populate_all_memory_levels = iceland_populate_all_memory_levels,
	.get_mac_definition = iceland_get_mac_definition,
	.initialize_mc_reg_table = iceland_initialize_mc_reg_table,
	.is_dpm_running = iceland_is_dpm_running,
पूर्ण;

