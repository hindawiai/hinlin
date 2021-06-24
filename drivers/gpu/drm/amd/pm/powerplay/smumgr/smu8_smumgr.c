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

#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "cgs_common.h"
#समावेश "smu/smu_8_0_d.h"
#समावेश "smu/smu_8_0_sh_mask.h"
#समावेश "smu8.h"
#समावेश "smu8_fusion.h"
#समावेश "smu8_smumgr.h"
#समावेश "cz_ppsmc.h"
#समावेश "smu_ucode_xfer_cz.h"
#समावेश "gca/gfx_8_0_d.h"
#समावेश "gca/gfx_8_0_sh_mask.h"
#समावेश "smumgr.h"

#घोषणा SIZE_ALIGN_32(x)    (((x) + 31) / 32 * 32)

अटल स्थिर क्रमागत smu8_scratch_entry firmware_list[] = अणु
	SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA0,
	SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA1,
	SMU8_SCRATCH_ENTRY_UCODE_ID_CP_CE,
	SMU8_SCRATCH_ENTRY_UCODE_ID_CP_PFP,
	SMU8_SCRATCH_ENTRY_UCODE_ID_CP_ME,
	SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT1,
	SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT2,
	SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_G,
पूर्ण;

अटल uपूर्णांक32_t smu8_get_argument(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (hwmgr == शून्य || hwmgr->device == शून्य)
		वापस 0;

	वापस cgs_पढ़ो_रेजिस्टर(hwmgr->device,
					mmSMU_MP1_SRBM2P_ARG_0);
पूर्ण

/* Send a message to the SMC, and रुको क्रम its response.*/
अटल पूर्णांक smu8_send_msg_to_smc_with_parameter(काष्ठा pp_hwmgr *hwmgr,
					    uपूर्णांक16_t msg, uपूर्णांक32_t parameter)
अणु
	पूर्णांक result = 0;
	kसमय_प्रकार t_start;
	s64 elapsed_us;

	अगर (hwmgr == शून्य || hwmgr->device == शून्य)
		वापस -EINVAL;

	result = PHM_WAIT_FIELD_UNEQUAL(hwmgr,
					SMU_MP1_SRBM2P_RESP_0, CONTENT, 0);
	अगर (result != 0) अणु
		/* Read the last message to SMU, to report actual cause */
		uपूर्णांक32_t val = cgs_पढ़ो_रेजिस्टर(hwmgr->device,
						 mmSMU_MP1_SRBM2P_MSG_0);
		pr_err("%s(0x%04x) aborted; SMU still servicing msg (0x%04x)\n",
			__func__, msg, val);
		वापस result;
	पूर्ण
	t_start = kसमय_get();

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMU_MP1_SRBM2P_ARG_0, parameter);

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMU_MP1_SRBM2P_RESP_0, 0);
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMU_MP1_SRBM2P_MSG_0, msg);

	result = PHM_WAIT_FIELD_UNEQUAL(hwmgr,
					SMU_MP1_SRBM2P_RESP_0, CONTENT, 0);

	elapsed_us = kसमय_us_delta(kसमय_get(), t_start);

	WARN(result, "%s(0x%04x, %#x) timed out after %lld us\n",
			__func__, msg, parameter, elapsed_us);

	वापस result;
पूर्ण

अटल पूर्णांक smu8_send_msg_to_smc(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t msg)
अणु
	वापस smu8_send_msg_to_smc_with_parameter(hwmgr, msg, 0);
पूर्ण

अटल पूर्णांक smu8_set_smc_sram_address(काष्ठा pp_hwmgr *hwmgr,
				     uपूर्णांक32_t smc_address, uपूर्णांक32_t limit)
अणु
	अगर (hwmgr == शून्य || hwmgr->device == शून्य)
		वापस -EINVAL;

	अगर (0 != (3 & smc_address)) अणु
		pr_err("SMC address must be 4 byte aligned\n");
		वापस -EINVAL;
	पूर्ण

	अगर (limit <= (smc_address + 3)) अणु
		pr_err("SMC address beyond the SMC RAM area\n");
		वापस -EINVAL;
	पूर्ण

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMP0PUB_IND_INDEX_0,
				SMN_MP1_SRAM_START_ADDR + smc_address);

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_ग_लिखो_smc_sram_dword(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t smc_address, uपूर्णांक32_t value, uपूर्णांक32_t limit)
अणु
	पूर्णांक result;

	अगर (hwmgr == शून्य || hwmgr->device == शून्य)
		वापस -EINVAL;

	result = smu8_set_smc_sram_address(hwmgr, smc_address, limit);
	अगर (!result)
		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMP0PUB_IND_DATA_0, value);

	वापस result;
पूर्ण

अटल पूर्णांक smu8_check_fw_load_finish(काष्ठा pp_hwmgr *hwmgr,
				   uपूर्णांक32_t firmware)
अणु
	पूर्णांक i;
	uपूर्णांक32_t index = SMN_MP1_SRAM_START_ADDR +
			 SMU8_FIRMWARE_HEADER_LOCATION +
			 दुरत्व(काष्ठा SMU8_Firmware_Header, UcodeLoadStatus);

	अगर (hwmgr == शून्य || hwmgr->device == शून्य)
		वापस -EINVAL;

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMP0PUB_IND_INDEX, index);

	क्रम (i = 0; i < hwmgr->usec_समयout; i++) अणु
		अगर (firmware ==
			(cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMP0PUB_IND_DATA) & firmware))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= hwmgr->usec_समयout) अणु
		pr_err("SMU check loaded firmware failed.\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_load_mec_firmware(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t reg_data;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक ret = 0;
	काष्ठा cgs_firmware_info info = अणु0पूर्ण;

	अगर (hwmgr == शून्य || hwmgr->device == शून्य)
		वापस -EINVAL;

	ret = cgs_get_firmware_info(hwmgr->device,
						CGS_UCODE_ID_CP_MEC, &info);

	अगर (ret)
		वापस -EINVAL;

	/* Disable MEC parsing/prefetching */
	पंचांगp = cgs_पढ़ो_रेजिस्टर(hwmgr->device,
					mmCP_MEC_CNTL);
	पंचांगp = PHM_SET_FIELD(पंचांगp, CP_MEC_CNTL, MEC_ME1_HALT, 1);
	पंचांगp = PHM_SET_FIELD(पंचांगp, CP_MEC_CNTL, MEC_ME2_HALT, 1);
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmCP_MEC_CNTL, पंचांगp);

	पंचांगp = cgs_पढ़ो_रेजिस्टर(hwmgr->device,
					mmCP_CPC_IC_BASE_CNTL);

	पंचांगp = PHM_SET_FIELD(पंचांगp, CP_CPC_IC_BASE_CNTL, VMID, 0);
	पंचांगp = PHM_SET_FIELD(पंचांगp, CP_CPC_IC_BASE_CNTL, ATC, 0);
	पंचांगp = PHM_SET_FIELD(पंचांगp, CP_CPC_IC_BASE_CNTL, CACHE_POLICY, 0);
	पंचांगp = PHM_SET_FIELD(पंचांगp, CP_CPC_IC_BASE_CNTL, MTYPE, 1);
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmCP_CPC_IC_BASE_CNTL, पंचांगp);

	reg_data = lower_32_bits(info.mc_addr) &
			PHM_FIELD_MASK(CP_CPC_IC_BASE_LO, IC_BASE_LO);
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmCP_CPC_IC_BASE_LO, reg_data);

	reg_data = upper_32_bits(info.mc_addr) &
			PHM_FIELD_MASK(CP_CPC_IC_BASE_HI, IC_BASE_HI);
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmCP_CPC_IC_BASE_HI, reg_data);

	वापस 0;
पूर्ण

अटल uपूर्णांक8_t smu8_translate_firmware_क्रमागत_to_arg(काष्ठा pp_hwmgr *hwmgr,
			क्रमागत smu8_scratch_entry firmware_क्रमागत)
अणु
	uपूर्णांक8_t ret = 0;

	चयन (firmware_क्रमागत) अणु
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA0:
		ret = UCODE_ID_SDMA0;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA1:
		अगर (hwmgr->chip_id == CHIP_STONEY)
			ret = UCODE_ID_SDMA0;
		अन्यथा
			ret = UCODE_ID_SDMA1;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_CP_CE:
		ret = UCODE_ID_CP_CE;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_CP_PFP:
		ret = UCODE_ID_CP_PFP;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_CP_ME:
		ret = UCODE_ID_CP_ME;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT1:
		ret = UCODE_ID_CP_MEC_JT1;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT2:
		अगर (hwmgr->chip_id == CHIP_STONEY)
			ret = UCODE_ID_CP_MEC_JT1;
		अन्यथा
			ret = UCODE_ID_CP_MEC_JT2;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_GMCON_RENG:
		ret = UCODE_ID_GMCON_RENG;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_G:
		ret = UCODE_ID_RLC_G;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SCRATCH:
		ret = UCODE_ID_RLC_SCRATCH;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_ARAM:
		ret = UCODE_ID_RLC_SRM_ARAM;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_DRAM:
		ret = UCODE_ID_RLC_SRM_DRAM;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_DMCU_ERAM:
		ret = UCODE_ID_DMCU_ERAM;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_DMCU_IRAM:
		ret = UCODE_ID_DMCU_IRAM;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_UCODE_ID_POWER_PROFILING:
		ret = TASK_ARG_INIT_MM_PWR_LOG;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_DATA_ID_SDMA_HALT:
	हाल SMU8_SCRATCH_ENTRY_DATA_ID_SYS_CLOCKGATING:
	हाल SMU8_SCRATCH_ENTRY_DATA_ID_SDMA_RING_REGS:
	हाल SMU8_SCRATCH_ENTRY_DATA_ID_NONGFX_REINIT:
	हाल SMU8_SCRATCH_ENTRY_DATA_ID_SDMA_START:
	हाल SMU8_SCRATCH_ENTRY_DATA_ID_IH_REGISTERS:
		ret = TASK_ARG_REG_MMIO;
		अवरोध;
	हाल SMU8_SCRATCH_ENTRY_SMU8_FUSION_CLKTABLE:
		ret = TASK_ARG_INIT_CLK_TABLE;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत cgs_ucode_id smu8_convert_fw_type_to_cgs(uपूर्णांक32_t fw_type)
अणु
	क्रमागत cgs_ucode_id result = CGS_UCODE_ID_MAXIMUM;

	चयन (fw_type) अणु
	हाल UCODE_ID_SDMA0:
		result = CGS_UCODE_ID_SDMA0;
		अवरोध;
	हाल UCODE_ID_SDMA1:
		result = CGS_UCODE_ID_SDMA1;
		अवरोध;
	हाल UCODE_ID_CP_CE:
		result = CGS_UCODE_ID_CP_CE;
		अवरोध;
	हाल UCODE_ID_CP_PFP:
		result = CGS_UCODE_ID_CP_PFP;
		अवरोध;
	हाल UCODE_ID_CP_ME:
		result = CGS_UCODE_ID_CP_ME;
		अवरोध;
	हाल UCODE_ID_CP_MEC_JT1:
		result = CGS_UCODE_ID_CP_MEC_JT1;
		अवरोध;
	हाल UCODE_ID_CP_MEC_JT2:
		result = CGS_UCODE_ID_CP_MEC_JT2;
		अवरोध;
	हाल UCODE_ID_RLC_G:
		result = CGS_UCODE_ID_RLC_G;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक smu8_smu_populate_single_scratch_task(
			काष्ठा pp_hwmgr *hwmgr,
			क्रमागत smu8_scratch_entry fw_क्रमागत,
			uपूर्णांक8_t type, bool is_last)
अणु
	uपूर्णांक8_t i;
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	काष्ठा TOC *toc = (काष्ठा TOC *)smu8_smu->toc_buffer.kaddr;
	काष्ठा SMU_Task *task = &toc->tasks[smu8_smu->toc_entry_used_count++];

	task->type = type;
	task->arg = smu8_translate_firmware_क्रमागत_to_arg(hwmgr, fw_क्रमागत);
	task->next = is_last ? END_OF_TASK_LIST : smu8_smu->toc_entry_used_count;

	क्रम (i = 0; i < smu8_smu->scratch_buffer_length; i++)
		अगर (smu8_smu->scratch_buffer[i].firmware_ID == fw_क्रमागत)
			अवरोध;

	अगर (i >= smu8_smu->scratch_buffer_length) अणु
		pr_err("Invalid Firmware Type\n");
		वापस -EINVAL;
	पूर्ण

	task->addr.low = lower_32_bits(smu8_smu->scratch_buffer[i].mc_addr);
	task->addr.high = upper_32_bits(smu8_smu->scratch_buffer[i].mc_addr);
	task->size_bytes = smu8_smu->scratch_buffer[i].data_size;

	अगर (SMU8_SCRATCH_ENTRY_DATA_ID_IH_REGISTERS == fw_क्रमागत) अणु
		काष्ठा smu8_ih_meta_data *pIHReg_restore =
		     (काष्ठा smu8_ih_meta_data *)smu8_smu->scratch_buffer[i].kaddr;
		pIHReg_restore->command =
			METADATA_CMD_MODE0 | METADATA_PERFORM_ON_LOAD;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_smu_populate_single_ucode_load_task(
					काष्ठा pp_hwmgr *hwmgr,
					क्रमागत smu8_scratch_entry fw_क्रमागत,
					bool is_last)
अणु
	uपूर्णांक8_t i;
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	काष्ठा TOC *toc = (काष्ठा TOC *)smu8_smu->toc_buffer.kaddr;
	काष्ठा SMU_Task *task = &toc->tasks[smu8_smu->toc_entry_used_count++];

	task->type = TASK_TYPE_UCODE_LOAD;
	task->arg = smu8_translate_firmware_क्रमागत_to_arg(hwmgr, fw_क्रमागत);
	task->next = is_last ? END_OF_TASK_LIST : smu8_smu->toc_entry_used_count;

	क्रम (i = 0; i < smu8_smu->driver_buffer_length; i++)
		अगर (smu8_smu->driver_buffer[i].firmware_ID == fw_क्रमागत)
			अवरोध;

	अगर (i >= smu8_smu->driver_buffer_length) अणु
		pr_err("Invalid Firmware Type\n");
		वापस -EINVAL;
	पूर्ण

	task->addr.low = lower_32_bits(smu8_smu->driver_buffer[i].mc_addr);
	task->addr.high = upper_32_bits(smu8_smu->driver_buffer[i].mc_addr);
	task->size_bytes = smu8_smu->driver_buffer[i].data_size;

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_smu_स्थिरruct_toc_क्रम_rlc_aram_save(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;

	smu8_smu->toc_entry_aram = smu8_smu->toc_entry_used_count;
	smu8_smu_populate_single_scratch_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_ARAM,
				TASK_TYPE_UCODE_SAVE, true);

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_smu_initialize_toc_empty_job_list(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक i;
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	काष्ठा TOC *toc = (काष्ठा TOC *)smu8_smu->toc_buffer.kaddr;

	क्रम (i = 0; i < NUM_JOBLIST_ENTRIES; i++)
		toc->JobList[i] = (uपूर्णांक8_t)IGNORE_JOB;

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_smu_स्थिरruct_toc_क्रम_vddgfx_enter(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	काष्ठा TOC *toc = (काष्ठा TOC *)smu8_smu->toc_buffer.kaddr;

	toc->JobList[JOB_GFX_SAVE] = (uपूर्णांक8_t)smu8_smu->toc_entry_used_count;
	smu8_smu_populate_single_scratch_task(hwmgr,
				    SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SCRATCH,
				    TASK_TYPE_UCODE_SAVE, false);

	smu8_smu_populate_single_scratch_task(hwmgr,
				    SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_DRAM,
				    TASK_TYPE_UCODE_SAVE, true);

	वापस 0;
पूर्ण


अटल पूर्णांक smu8_smu_स्थिरruct_toc_क्रम_vddgfx_निकास(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	काष्ठा TOC *toc = (काष्ठा TOC *)smu8_smu->toc_buffer.kaddr;

	toc->JobList[JOB_GFX_RESTORE] = (uपूर्णांक8_t)smu8_smu->toc_entry_used_count;

	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_CE, false);
	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_PFP, false);
	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_ME, false);
	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT1, false);

	अगर (hwmgr->chip_id == CHIP_STONEY)
		smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT1, false);
	अन्यथा
		smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT2, false);

	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_G, false);

	/* populate scratch */
	smu8_smu_populate_single_scratch_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SCRATCH,
				TASK_TYPE_UCODE_LOAD, false);

	smu8_smu_populate_single_scratch_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_ARAM,
				TASK_TYPE_UCODE_LOAD, false);

	smu8_smu_populate_single_scratch_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_DRAM,
				TASK_TYPE_UCODE_LOAD, true);

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_smu_स्थिरruct_toc_क्रम_घातer_profiling(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;

	smu8_smu->toc_entry_घातer_profiling_index = smu8_smu->toc_entry_used_count;

	smu8_smu_populate_single_scratch_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_POWER_PROFILING,
				TASK_TYPE_INITIALIZE, true);
	वापस 0;
पूर्ण

अटल पूर्णांक smu8_smu_स्थिरruct_toc_क्रम_bootup(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;

	smu8_smu->toc_entry_initialize_index = smu8_smu->toc_entry_used_count;

	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA0, false);
	अगर (hwmgr->chip_id != CHIP_STONEY)
		smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_SDMA1, false);
	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_CE, false);
	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_PFP, false);
	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_ME, false);
	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT1, false);
	अगर (hwmgr->chip_id != CHIP_STONEY)
		smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_CP_MEC_JT2, false);
	smu8_smu_populate_single_ucode_load_task(hwmgr,
				SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_G, true);

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_smu_स्थिरruct_toc_क्रम_घड़ी_प्रकारable(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;

	smu8_smu->toc_entry_घड़ी_प्रकारable = smu8_smu->toc_entry_used_count;

	smu8_smu_populate_single_scratch_task(hwmgr,
				SMU8_SCRATCH_ENTRY_SMU8_FUSION_CLKTABLE,
				TASK_TYPE_INITIALIZE, true);

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_smu_स्थिरruct_toc(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;

	smu8_smu->toc_entry_used_count = 0;
	smu8_smu_initialize_toc_empty_job_list(hwmgr);
	smu8_smu_स्थिरruct_toc_क्रम_rlc_aram_save(hwmgr);
	smu8_smu_स्थिरruct_toc_क्रम_vddgfx_enter(hwmgr);
	smu8_smu_स्थिरruct_toc_क्रम_vddgfx_निकास(hwmgr);
	smu8_smu_स्थिरruct_toc_क्रम_घातer_profiling(hwmgr);
	smu8_smu_स्थिरruct_toc_क्रम_bootup(hwmgr);
	smu8_smu_स्थिरruct_toc_क्रम_घड़ी_प्रकारable(hwmgr);

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_smu_populate_firmware_entries(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	uपूर्णांक32_t firmware_type;
	uपूर्णांक32_t i;
	पूर्णांक ret;
	क्रमागत cgs_ucode_id ucode_id;
	काष्ठा cgs_firmware_info info = अणु0पूर्ण;

	smu8_smu->driver_buffer_length = 0;

	क्रम (i = 0; i < ARRAY_SIZE(firmware_list); i++) अणु

		firmware_type = smu8_translate_firmware_क्रमागत_to_arg(hwmgr,
					firmware_list[i]);

		ucode_id = smu8_convert_fw_type_to_cgs(firmware_type);

		ret = cgs_get_firmware_info(hwmgr->device,
							ucode_id, &info);

		अगर (ret == 0) अणु
			smu8_smu->driver_buffer[i].mc_addr = info.mc_addr;

			smu8_smu->driver_buffer[i].data_size = info.image_size;

			smu8_smu->driver_buffer[i].firmware_ID = firmware_list[i];
			smu8_smu->driver_buffer_length++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_smu_populate_single_scratch_entry(
				काष्ठा pp_hwmgr *hwmgr,
				क्रमागत smu8_scratch_entry scratch_type,
				uपूर्णांक32_t ulsize_byte,
				काष्ठा smu8_buffer_entry *entry)
अणु
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	uपूर्णांक32_t ulsize_aligned = SIZE_ALIGN_32(ulsize_byte);

	entry->data_size = ulsize_byte;
	entry->kaddr = (अक्षर *) smu8_smu->smu_buffer.kaddr +
				smu8_smu->smu_buffer_used_bytes;
	entry->mc_addr = smu8_smu->smu_buffer.mc_addr + smu8_smu->smu_buffer_used_bytes;
	entry->firmware_ID = scratch_type;

	smu8_smu->smu_buffer_used_bytes += ulsize_aligned;

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_करोwnload_pptable_settings(काष्ठा pp_hwmgr *hwmgr, व्योम **table)
अणु
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < smu8_smu->scratch_buffer_length; i++) अणु
		अगर (smu8_smu->scratch_buffer[i].firmware_ID
			== SMU8_SCRATCH_ENTRY_SMU8_FUSION_CLKTABLE)
			अवरोध;
	पूर्ण

	*table = (काष्ठा SMU8_Fusion_ClkTable *)smu8_smu->scratch_buffer[i].kaddr;

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetClkTableAddrHi,
				upper_32_bits(smu8_smu->scratch_buffer[i].mc_addr),
				शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetClkTableAddrLo,
				lower_32_bits(smu8_smu->scratch_buffer[i].mc_addr),
				शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_ExecuteJob,
				smu8_smu->toc_entry_घड़ी_प्रकारable,
				शून्य);

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ClkTableXferToDram, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_upload_pptable_settings(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < smu8_smu->scratch_buffer_length; i++) अणु
		अगर (smu8_smu->scratch_buffer[i].firmware_ID
				== SMU8_SCRATCH_ENTRY_SMU8_FUSION_CLKTABLE)
			अवरोध;
	पूर्ण

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetClkTableAddrHi,
				upper_32_bits(smu8_smu->scratch_buffer[i].mc_addr),
				शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetClkTableAddrLo,
				lower_32_bits(smu8_smu->scratch_buffer[i].mc_addr),
				शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_ExecuteJob,
				smu8_smu->toc_entry_घड़ी_प्रकारable,
				शून्य);

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_ClkTableXferToSmu, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_request_smu_load_fw(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	uपूर्णांक32_t smc_address;
	uपूर्णांक32_t fw_to_check = 0;
	पूर्णांक ret;

	amdgpu_ucode_init_bo(hwmgr->adev);

	smu8_smu_populate_firmware_entries(hwmgr);

	smu8_smu_स्थिरruct_toc(hwmgr);

	smc_address = SMU8_FIRMWARE_HEADER_LOCATION +
		दुरत्व(काष्ठा SMU8_Firmware_Header, UcodeLoadStatus);

	smu8_ग_लिखो_smc_sram_dword(hwmgr, smc_address, 0, smc_address+4);

	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DriverDramAddrHi,
					upper_32_bits(smu8_smu->toc_buffer.mc_addr),
					शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_DriverDramAddrLo,
					lower_32_bits(smu8_smu->toc_buffer.mc_addr),
					शून्य);

	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_InitJobs, शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_ExecuteJob,
					smu8_smu->toc_entry_aram,
					शून्य);
	smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_ExecuteJob,
				smu8_smu->toc_entry_घातer_profiling_index,
				शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_ExecuteJob,
					smu8_smu->toc_entry_initialize_index,
					शून्य);

	fw_to_check = UCODE_ID_RLC_G_MASK |
			UCODE_ID_SDMA0_MASK |
			UCODE_ID_SDMA1_MASK |
			UCODE_ID_CP_CE_MASK |
			UCODE_ID_CP_ME_MASK |
			UCODE_ID_CP_PFP_MASK |
			UCODE_ID_CP_MEC_JT1_MASK |
			UCODE_ID_CP_MEC_JT2_MASK;

	अगर (hwmgr->chip_id == CHIP_STONEY)
		fw_to_check &= ~(UCODE_ID_SDMA1_MASK | UCODE_ID_CP_MEC_JT2_MASK);

	ret = smu8_check_fw_load_finish(hwmgr, fw_to_check);
	अगर (ret) अणु
		pr_err("SMU firmware load failed\n");
		वापस ret;
	पूर्ण

	ret = smu8_load_mec_firmware(hwmgr);
	अगर (ret) अणु
		pr_err("Mec Firmware load failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu8_start_smu(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev;

	uपूर्णांक32_t index = SMN_MP1_SRAM_START_ADDR +
			 SMU8_FIRMWARE_HEADER_LOCATION +
			 दुरत्व(काष्ठा SMU8_Firmware_Header, Version);

	अगर (hwmgr == शून्य || hwmgr->device == शून्य)
		वापस -EINVAL;

	adev = hwmgr->adev;

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmMP0PUB_IND_INDEX, index);
	hwmgr->smu_version = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmMP0PUB_IND_DATA);
	pr_info("smu version %02d.%02d.%02d\n",
		((hwmgr->smu_version >> 16) & 0xFF),
		((hwmgr->smu_version >> 8) & 0xFF),
		(hwmgr->smu_version & 0xFF));
	adev->pm.fw_version = hwmgr->smu_version >> 8;

	वापस smu8_request_smu_load_fw(hwmgr);
पूर्ण

अटल पूर्णांक smu8_smu_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret = 0;
	काष्ठा smu8_smumgr *smu8_smu;

	smu8_smu = kzalloc(माप(काष्ठा smu8_smumgr), GFP_KERNEL);
	अगर (smu8_smu == शून्य)
		वापस -ENOMEM;

	hwmgr->smu_backend = smu8_smu;

	smu8_smu->toc_buffer.data_size = 4096;
	smu8_smu->smu_buffer.data_size =
		ALIGN(UCODE_ID_RLC_SCRATCH_SIZE_BYTE, 32) +
		ALIGN(UCODE_ID_RLC_SRM_ARAM_SIZE_BYTE, 32) +
		ALIGN(UCODE_ID_RLC_SRM_DRAM_SIZE_BYTE, 32) +
		ALIGN(माप(काष्ठा SMU8_MulसमयdiaPowerLogData), 32) +
		ALIGN(माप(काष्ठा SMU8_Fusion_ClkTable), 32);

	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
				smu8_smu->toc_buffer.data_size,
				PAGE_SIZE,
				AMDGPU_GEM_DOMAIN_VRAM,
				&smu8_smu->toc_buffer.handle,
				&smu8_smu->toc_buffer.mc_addr,
				&smu8_smu->toc_buffer.kaddr);
	अगर (ret)
		जाओ err2;

	ret = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
				smu8_smu->smu_buffer.data_size,
				PAGE_SIZE,
				AMDGPU_GEM_DOMAIN_VRAM,
				&smu8_smu->smu_buffer.handle,
				&smu8_smu->smu_buffer.mc_addr,
				&smu8_smu->smu_buffer.kaddr);
	अगर (ret)
		जाओ err1;

	अगर (0 != smu8_smu_populate_single_scratch_entry(hwmgr,
		SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SCRATCH,
		UCODE_ID_RLC_SCRATCH_SIZE_BYTE,
		&smu8_smu->scratch_buffer[smu8_smu->scratch_buffer_length++])) अणु
		pr_err("Error when Populate Firmware Entry.\n");
		जाओ err0;
	पूर्ण

	अगर (0 != smu8_smu_populate_single_scratch_entry(hwmgr,
		SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_ARAM,
		UCODE_ID_RLC_SRM_ARAM_SIZE_BYTE,
		&smu8_smu->scratch_buffer[smu8_smu->scratch_buffer_length++])) अणु
		pr_err("Error when Populate Firmware Entry.\n");
		जाओ err0;
	पूर्ण
	अगर (0 != smu8_smu_populate_single_scratch_entry(hwmgr,
		SMU8_SCRATCH_ENTRY_UCODE_ID_RLC_SRM_DRAM,
		UCODE_ID_RLC_SRM_DRAM_SIZE_BYTE,
		&smu8_smu->scratch_buffer[smu8_smu->scratch_buffer_length++])) अणु
		pr_err("Error when Populate Firmware Entry.\n");
		जाओ err0;
	पूर्ण

	अगर (0 != smu8_smu_populate_single_scratch_entry(hwmgr,
		SMU8_SCRATCH_ENTRY_UCODE_ID_POWER_PROFILING,
		माप(काष्ठा SMU8_MulसमयdiaPowerLogData),
		&smu8_smu->scratch_buffer[smu8_smu->scratch_buffer_length++])) अणु
		pr_err("Error when Populate Firmware Entry.\n");
		जाओ err0;
	पूर्ण

	अगर (0 != smu8_smu_populate_single_scratch_entry(hwmgr,
		SMU8_SCRATCH_ENTRY_SMU8_FUSION_CLKTABLE,
		माप(काष्ठा SMU8_Fusion_ClkTable),
		&smu8_smu->scratch_buffer[smu8_smu->scratch_buffer_length++])) अणु
		pr_err("Error when Populate Firmware Entry.\n");
		जाओ err0;
	पूर्ण

	वापस 0;

err0:
	amdgpu_bo_मुक्त_kernel(&smu8_smu->smu_buffer.handle,
				&smu8_smu->smu_buffer.mc_addr,
				&smu8_smu->smu_buffer.kaddr);
err1:
	amdgpu_bo_मुक्त_kernel(&smu8_smu->toc_buffer.handle,
				&smu8_smu->toc_buffer.mc_addr,
				&smu8_smu->toc_buffer.kaddr);
err2:
	kमुक्त(smu8_smu);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक smu8_smu_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu8_smumgr *smu8_smu;

	अगर (hwmgr == शून्य || hwmgr->device == शून्य)
		वापस -EINVAL;

	smu8_smu = hwmgr->smu_backend;
	अगर (smu8_smu) अणु
		amdgpu_bo_मुक्त_kernel(&smu8_smu->toc_buffer.handle,
					&smu8_smu->toc_buffer.mc_addr,
					&smu8_smu->toc_buffer.kaddr);
		amdgpu_bo_मुक्त_kernel(&smu8_smu->smu_buffer.handle,
					&smu8_smu->smu_buffer.mc_addr,
					&smu8_smu->smu_buffer.kaddr);
		kमुक्त(smu8_smu);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool smu8_dpm_check_smu_features(काष्ठा pp_hwmgr *hwmgr,
				अचिन्हित दीर्घ check_feature)
अणु
	पूर्णांक result;
	uपूर्णांक32_t features;

	result = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_GetFeatureStatus,
				0,
				&features);
	अगर (result == 0) अणु
		अगर (features & check_feature)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool smu8_is_dpm_running(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (smu8_dpm_check_smu_features(hwmgr, SMU_EnabledFeatureScoreboard_SclkDpmOn))
		वापस true;
	वापस false;
पूर्ण

स्थिर काष्ठा pp_smumgr_func smu8_smu_funcs = अणु
	.name = "smu8_smu",
	.smu_init = smu8_smu_init,
	.smu_fini = smu8_smu_fini,
	.start_smu = smu8_start_smu,
	.check_fw_load_finish = smu8_check_fw_load_finish,
	.request_smu_load_fw = शून्य,
	.request_smu_load_specअगरic_fw = शून्य,
	.get_argument = smu8_get_argument,
	.send_msg_to_smc = smu8_send_msg_to_smc,
	.send_msg_to_smc_with_parameter = smu8_send_msg_to_smc_with_parameter,
	.करोwnload_pptable_settings = smu8_करोwnload_pptable_settings,
	.upload_pptable_settings = smu8_upload_pptable_settings,
	.is_dpm_running = smu8_is_dpm_running,
पूर्ण;

