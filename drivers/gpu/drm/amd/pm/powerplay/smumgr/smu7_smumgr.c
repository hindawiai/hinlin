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
#समावेश "smumgr.h"
#समावेश "smu_ucode_xfer_vi.h"
#समावेश "ppatomctrl.h"
#समावेश "cgs_common.h"
#समावेश "smu7_ppsmc.h"
#समावेश "smu7_smumgr.h"
#समावेश "smu7_common.h"

#समावेश "polaris10_pwrvirus.h"

#घोषणा SMU7_SMC_SIZE 0x20000

अटल पूर्णांक smu7_set_smc_sram_address(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t smc_addr, uपूर्णांक32_t limit)
अणु
	PP_ASSERT_WITH_CODE((0 == (3 & smc_addr)), "SMC address must be 4 byte aligned.", वापस -EINVAL);
	PP_ASSERT_WITH_CODE((limit > (smc_addr + 3)), "SMC addr is beyond the SMC RAM area.", वापस -EINVAL);

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMC_IND_INDEX_11, smc_addr);
	PHM_WRITE_FIELD(hwmgr->device, SMC_IND_ACCESS_CNTL, AUTO_INCREMENT_IND_11, 0); /* on ci, SMC_IND_ACCESS_CNTL is dअगरferent */
	वापस 0;
पूर्ण


पूर्णांक smu7_copy_bytes_from_smc(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t smc_start_address, uपूर्णांक32_t *dest, uपूर्णांक32_t byte_count, uपूर्णांक32_t limit)
अणु
	uपूर्णांक32_t data;
	uपूर्णांक32_t addr;
	uपूर्णांक8_t *dest_byte;
	uपूर्णांक8_t i, data_byte[4] = अणु0पूर्ण;
	uपूर्णांक32_t *pdata = (uपूर्णांक32_t *)&data_byte;

	PP_ASSERT_WITH_CODE((0 == (3 & smc_start_address)), "SMC address must be 4 byte aligned.", वापस -EINVAL);
	PP_ASSERT_WITH_CODE((limit > (smc_start_address + byte_count)), "SMC address is beyond the SMC RAM area.", वापस -EINVAL);

	addr = smc_start_address;

	जबतक (byte_count >= 4) अणु
		smu7_पढ़ो_smc_sram_dword(hwmgr, addr, &data, limit);

		*dest = PP_SMC_TO_HOST_UL(data);

		dest += 1;
		byte_count -= 4;
		addr += 4;
	पूर्ण

	अगर (byte_count) अणु
		smu7_पढ़ो_smc_sram_dword(hwmgr, addr, &data, limit);
		*pdata = PP_SMC_TO_HOST_UL(data);
	/* Cast dest पूर्णांकo byte type in dest_byte.  This way, we करोn't overflow अगर the allocated memory is not 4-byte aligned. */
		dest_byte = (uपूर्णांक8_t *)dest;
		क्रम (i = 0; i < byte_count; i++)
			dest_byte[i] = data_byte[i];
	पूर्ण

	वापस 0;
पूर्ण


पूर्णांक smu7_copy_bytes_to_smc(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t smc_start_address,
				स्थिर uपूर्णांक8_t *src, uपूर्णांक32_t byte_count, uपूर्णांक32_t limit)
अणु
	पूर्णांक result;
	uपूर्णांक32_t data = 0;
	uपूर्णांक32_t original_data;
	uपूर्णांक32_t addr = 0;
	uपूर्णांक32_t extra_shअगरt;

	PP_ASSERT_WITH_CODE((0 == (3 & smc_start_address)), "SMC address must be 4 byte aligned.", वापस -EINVAL);
	PP_ASSERT_WITH_CODE((limit > (smc_start_address + byte_count)), "SMC address is beyond the SMC RAM area.", वापस -EINVAL);

	addr = smc_start_address;

	जबतक (byte_count >= 4) अणु
	/* Bytes are written पूर्णांकo the SMC addres space with the MSB first. */
		data = src[0] * 0x1000000 + src[1] * 0x10000 + src[2] * 0x100 + src[3];

		result = smu7_set_smc_sram_address(hwmgr, addr, limit);

		अगर (0 != result)
			वापस result;

		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMC_IND_DATA_11, data);

		src += 4;
		byte_count -= 4;
		addr += 4;
	पूर्ण

	अगर (0 != byte_count) अणु

		data = 0;

		result = smu7_set_smc_sram_address(hwmgr, addr, limit);

		अगर (0 != result)
			वापस result;


		original_data = cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmSMC_IND_DATA_11);

		extra_shअगरt = 8 * (4 - byte_count);

		जबतक (byte_count > 0) अणु
			/* Bytes are written पूर्णांकo the SMC addres space with the MSB first. */
			data = (0x100 * data) + *src++;
			byte_count--;
		पूर्ण

		data <<= extra_shअगरt;

		data |= (original_data & ~((~0UL) << extra_shअगरt));

		result = smu7_set_smc_sram_address(hwmgr, addr, limit);

		अगर (0 != result)
			वापस result;

		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMC_IND_DATA_11, data);
	पूर्ण

	वापस 0;
पूर्ण


पूर्णांक smu7_program_jump_on_start(काष्ठा pp_hwmgr *hwmgr)
अणु
	अटल स्थिर अचिन्हित अक्षर data[4] = अणु 0xE0, 0x00, 0x80, 0x40 पूर्ण;

	smu7_copy_bytes_to_smc(hwmgr, 0x0, data, 4, माप(data)+1);

	वापस 0;
पूर्ण

bool smu7_is_smc_ram_running(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस ((0 == PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC, SMC_SYSCON_CLOCK_CNTL_0, ck_disable))
	&& (0x20100 <= cgs_पढ़ो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC, ixSMC_PC_C)));
पूर्ण

पूर्णांक smu7_send_msg_to_smc(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t msg)
अणु
	पूर्णांक ret;

	PHM_WAIT_FIELD_UNEQUAL(hwmgr, SMC_RESP_0, SMC_RESP, 0);

	ret = PHM_READ_FIELD(hwmgr->device, SMC_RESP_0, SMC_RESP);

	अगर (ret == 0xFE)
		pr_debug("last message was not supported\n");
	अन्यथा अगर (ret != 1)
		pr_info("\n last message was failed ret is %d\n", ret);

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMC_RESP_0, 0);
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMC_MESSAGE_0, msg);

	PHM_WAIT_FIELD_UNEQUAL(hwmgr, SMC_RESP_0, SMC_RESP, 0);

	ret = PHM_READ_FIELD(hwmgr->device, SMC_RESP_0, SMC_RESP);

	अगर (ret == 0xFE)
		pr_debug("message %x was not supported\n", msg);
	अन्यथा अगर (ret != 1)
		pr_info("\n failed to send message %x ret is %d \n",  msg, ret);

	वापस 0;
पूर्ण

पूर्णांक smu7_send_msg_to_smc_with_parameter(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t msg, uपूर्णांक32_t parameter)
अणु
	PHM_WAIT_FIELD_UNEQUAL(hwmgr, SMC_RESP_0, SMC_RESP, 0);

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMC_MSG_ARG_0, parameter);

	वापस smu7_send_msg_to_smc(hwmgr, msg);
पूर्ण

uपूर्णांक32_t smu7_get_argument(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmSMC_MSG_ARG_0);
पूर्ण

पूर्णांक smu7_send_msg_to_smc_offset(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_Test, 0x20000, शून्य);
पूर्ण

क्रमागत cgs_ucode_id smu7_convert_fw_type_to_cgs(uपूर्णांक32_t fw_type)
अणु
	क्रमागत cgs_ucode_id result = CGS_UCODE_ID_MAXIMUM;

	चयन (fw_type) अणु
	हाल UCODE_ID_SMU:
		result = CGS_UCODE_ID_SMU;
		अवरोध;
	हाल UCODE_ID_SMU_SK:
		result = CGS_UCODE_ID_SMU_SK;
		अवरोध;
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
	हाल UCODE_ID_CP_MEC:
		result = CGS_UCODE_ID_CP_MEC;
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
	हाल UCODE_ID_MEC_STORAGE:
		result = CGS_UCODE_ID_STORAGE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण


पूर्णांक smu7_पढ़ो_smc_sram_dword(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t smc_addr, uपूर्णांक32_t *value, uपूर्णांक32_t limit)
अणु
	पूर्णांक result;

	result = smu7_set_smc_sram_address(hwmgr, smc_addr, limit);

	*value = result ? 0 : cgs_पढ़ो_रेजिस्टर(hwmgr->device, mmSMC_IND_DATA_11);

	वापस result;
पूर्ण

पूर्णांक smu7_ग_लिखो_smc_sram_dword(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t smc_addr, uपूर्णांक32_t value, uपूर्णांक32_t limit)
अणु
	पूर्णांक result;

	result = smu7_set_smc_sram_address(hwmgr, smc_addr, limit);

	अगर (result)
		वापस result;

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMC_IND_DATA_11, value);

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_populate_single_firmware_entry(काष्ठा pp_hwmgr *hwmgr,
						uपूर्णांक32_t fw_type,
						काष्ठा SMU_Entry *entry)
अणु
	पूर्णांक result = 0;
	काष्ठा cgs_firmware_info info = अणु0पूर्ण;

	result = cgs_get_firmware_info(hwmgr->device,
				smu7_convert_fw_type_to_cgs(fw_type),
				&info);

	अगर (!result) अणु
		entry->version = info.fw_version;
		entry->id = (uपूर्णांक16_t)fw_type;
		entry->image_addr_high = upper_32_bits(info.mc_addr);
		entry->image_addr_low = lower_32_bits(info.mc_addr);
		entry->meta_data_addr_high = 0;
		entry->meta_data_addr_low = 0;

		/* digest need be excluded out */
		अगर (!hwmgr->not_vf)
			info.image_size -= 20;
		entry->data_size_byte = info.image_size;
		entry->num_रेजिस्टर_entries = 0;
	पूर्ण

	अगर ((fw_type == UCODE_ID_RLC_G)
		|| (fw_type == UCODE_ID_CP_MEC))
		entry->flags = 1;
	अन्यथा
		entry->flags = 0;

	वापस 0;
पूर्ण

पूर्णांक smu7_request_smu_load_fw(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_smumgr *smu_data = (काष्ठा smu7_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t fw_to_load;
	पूर्णांक r = 0;

	amdgpu_ucode_init_bo(hwmgr->adev);

	अगर (smu_data->soft_regs_start)
		cgs_ग_लिखो_ind_रेजिस्टर(hwmgr->device, CGS_IND_REG__SMC,
					smu_data->soft_regs_start + smum_get_दुरत्व(hwmgr,
					SMU_SoftRegisters, UcodeLoadStatus),
					0x0);

	अगर (hwmgr->chip_id > CHIP_TOPAZ) अणु /* add support क्रम Topaz */
		अगर (hwmgr->not_vf) अणु
			smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SMU_DRAM_ADDR_HI,
						upper_32_bits(smu_data->smu_buffer.mc_addr),
						शून्य);
			smum_send_msg_to_smc_with_parameter(hwmgr,
						PPSMC_MSG_SMU_DRAM_ADDR_LO,
						lower_32_bits(smu_data->smu_buffer.mc_addr),
						शून्य);
		पूर्ण
		fw_to_load = UCODE_ID_RLC_G_MASK
			   + UCODE_ID_SDMA0_MASK
			   + UCODE_ID_SDMA1_MASK
			   + UCODE_ID_CP_CE_MASK
			   + UCODE_ID_CP_ME_MASK
			   + UCODE_ID_CP_PFP_MASK
			   + UCODE_ID_CP_MEC_MASK;
	पूर्ण अन्यथा अणु
		fw_to_load = UCODE_ID_RLC_G_MASK
			   + UCODE_ID_SDMA0_MASK
			   + UCODE_ID_SDMA1_MASK
			   + UCODE_ID_CP_CE_MASK
			   + UCODE_ID_CP_ME_MASK
			   + UCODE_ID_CP_PFP_MASK
			   + UCODE_ID_CP_MEC_MASK
			   + UCODE_ID_CP_MEC_JT1_MASK
			   + UCODE_ID_CP_MEC_JT2_MASK;
	पूर्ण

	अगर (!smu_data->toc) अणु
		काष्ठा SMU_DRAMData_TOC *toc;

		smu_data->toc = kzalloc(माप(काष्ठा SMU_DRAMData_TOC), GFP_KERNEL);
		अगर (!smu_data->toc)
			वापस -ENOMEM;
		toc = smu_data->toc;
		toc->num_entries = 0;
		toc->काष्ठाure_version = 1;

		PP_ASSERT_WITH_CODE(0 == smu7_populate_single_firmware_entry(hwmgr,
				UCODE_ID_RLC_G, &toc->entry[toc->num_entries++]),
				"Failed to Get Firmware Entry.", r = -EINVAL; जाओ failed);
		PP_ASSERT_WITH_CODE(0 == smu7_populate_single_firmware_entry(hwmgr,
				UCODE_ID_CP_CE, &toc->entry[toc->num_entries++]),
				"Failed to Get Firmware Entry.", r = -EINVAL; जाओ failed);
		PP_ASSERT_WITH_CODE(0 == smu7_populate_single_firmware_entry(hwmgr,
				UCODE_ID_CP_PFP, &toc->entry[toc->num_entries++]),
				"Failed to Get Firmware Entry.", r = -EINVAL; जाओ failed);
		PP_ASSERT_WITH_CODE(0 == smu7_populate_single_firmware_entry(hwmgr,
				UCODE_ID_CP_ME, &toc->entry[toc->num_entries++]),
				"Failed to Get Firmware Entry.", r = -EINVAL; जाओ failed);
		PP_ASSERT_WITH_CODE(0 == smu7_populate_single_firmware_entry(hwmgr,
				UCODE_ID_CP_MEC, &toc->entry[toc->num_entries++]),
				"Failed to Get Firmware Entry.", r = -EINVAL; जाओ failed);
		PP_ASSERT_WITH_CODE(0 == smu7_populate_single_firmware_entry(hwmgr,
				UCODE_ID_CP_MEC_JT1, &toc->entry[toc->num_entries++]),
				"Failed to Get Firmware Entry.", r = -EINVAL; जाओ failed);
		PP_ASSERT_WITH_CODE(0 == smu7_populate_single_firmware_entry(hwmgr,
				UCODE_ID_CP_MEC_JT2, &toc->entry[toc->num_entries++]),
				"Failed to Get Firmware Entry.", r = -EINVAL; जाओ failed);
		PP_ASSERT_WITH_CODE(0 == smu7_populate_single_firmware_entry(hwmgr,
				UCODE_ID_SDMA0, &toc->entry[toc->num_entries++]),
				"Failed to Get Firmware Entry.", r = -EINVAL; जाओ failed);
		PP_ASSERT_WITH_CODE(0 == smu7_populate_single_firmware_entry(hwmgr,
				UCODE_ID_SDMA1, &toc->entry[toc->num_entries++]),
				"Failed to Get Firmware Entry.", r = -EINVAL; जाओ failed);
		अगर (!hwmgr->not_vf)
			PP_ASSERT_WITH_CODE(0 == smu7_populate_single_firmware_entry(hwmgr,
				UCODE_ID_MEC_STORAGE, &toc->entry[toc->num_entries++]),
				"Failed to Get Firmware Entry.", r = -EINVAL; जाओ failed);
	पूर्ण
	स_नकल_toio(smu_data->header_buffer.kaddr, smu_data->toc,
		    माप(काष्ठा SMU_DRAMData_TOC));
	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_DRV_DRAM_ADDR_HI,
			upper_32_bits(smu_data->header_buffer.mc_addr),
			शून्य);
	smum_send_msg_to_smc_with_parameter(hwmgr,
			PPSMC_MSG_DRV_DRAM_ADDR_LO,
			lower_32_bits(smu_data->header_buffer.mc_addr),
			शून्य);

	smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_MSG_LoadUcodes, fw_to_load, शून्य);

	r = smu7_check_fw_load_finish(hwmgr, fw_to_load);
	अगर (!r)
		वापस 0;

	pr_err("SMU load firmware failed\n");

failed:
	kमुक्त(smu_data->toc);
	smu_data->toc = शून्य;
	वापस r;
पूर्ण

/* Check अगर the FW has been loaded, SMU will not वापस अगर loading has not finished. */
पूर्णांक smu7_check_fw_load_finish(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t fw_type)
अणु
	काष्ठा smu7_smumgr *smu_data = (काष्ठा smu7_smumgr *)(hwmgr->smu_backend);
	uपूर्णांक32_t ret;

	ret = phm_रुको_on_indirect_रेजिस्टर(hwmgr, mmSMC_IND_INDEX_11,
					smu_data->soft_regs_start + smum_get_दुरत्व(hwmgr,
					SMU_SoftRegisters, UcodeLoadStatus),
					fw_type, fw_type);
	वापस ret;
पूर्ण

पूर्णांक smu7_reload_firmware(काष्ठा pp_hwmgr *hwmgr)
अणु
	वापस hwmgr->smumgr_funcs->start_smu(hwmgr);
पूर्ण

अटल पूर्णांक smu7_upload_smc_firmware_data(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t length, uपूर्णांक32_t *src, uपूर्णांक32_t limit)
अणु
	uपूर्णांक32_t byte_count = length;

	PP_ASSERT_WITH_CODE((limit >= byte_count), "SMC address is beyond the SMC RAM area.", वापस -EINVAL);

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMC_IND_INDEX_11, 0x20000);
	PHM_WRITE_FIELD(hwmgr->device, SMC_IND_ACCESS_CNTL, AUTO_INCREMENT_IND_11, 1);

	क्रम (; byte_count >= 4; byte_count -= 4)
		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmSMC_IND_DATA_11, *src++);

	PHM_WRITE_FIELD(hwmgr->device, SMC_IND_ACCESS_CNTL, AUTO_INCREMENT_IND_11, 0);

	PP_ASSERT_WITH_CODE((0 == byte_count), "SMC size must be divisible by 4.", वापस -EINVAL);

	वापस 0;
पूर्ण


पूर्णांक smu7_upload_smu_firmware_image(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = 0;
	काष्ठा smu7_smumgr *smu_data = (काष्ठा smu7_smumgr *)(hwmgr->smu_backend);

	काष्ठा cgs_firmware_info info = अणु0पूर्ण;

	अगर (smu_data->security_hard_key == 1)
		cgs_get_firmware_info(hwmgr->device,
			smu7_convert_fw_type_to_cgs(UCODE_ID_SMU), &info);
	अन्यथा
		cgs_get_firmware_info(hwmgr->device,
			smu7_convert_fw_type_to_cgs(UCODE_ID_SMU_SK), &info);

	hwmgr->is_kicker = info.is_kicker;
	hwmgr->smu_version = info.version;
	result = smu7_upload_smc_firmware_data(hwmgr, info.image_size, (uपूर्णांक32_t *)info.kptr, SMU7_SMC_SIZE);

	वापस result;
पूर्ण

अटल व्योम execute_pwr_table(काष्ठा pp_hwmgr *hwmgr, स्थिर PWR_Command_Table *pvirus, पूर्णांक size)
अणु
	पूर्णांक i;
	uपूर्णांक32_t reg, data;

	क्रम (i = 0; i < size; i++) अणु
		reg  = pvirus->reg;
		data = pvirus->data;
		अगर (reg != 0xffffffff)
			cgs_ग_लिखो_रेजिस्टर(hwmgr->device, reg, data);
		अन्यथा
			अवरोध;
		pvirus++;
	पूर्ण
पूर्ण

अटल व्योम execute_pwr_dfy_table(काष्ठा pp_hwmgr *hwmgr, स्थिर PWR_DFY_Section *section)
अणु
	पूर्णांक i;

	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmCP_DFY_CNTL, section->dfy_cntl);
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmCP_DFY_ADDR_HI, section->dfy_addr_hi);
	cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmCP_DFY_ADDR_LO, section->dfy_addr_lo);
	क्रम (i = 0; i < section->dfy_size; i++)
		cgs_ग_लिखो_रेजिस्टर(hwmgr->device, mmCP_DFY_DATA_0, section->dfy_data[i]);
पूर्ण

पूर्णांक smu7_setup_pwr_virus(काष्ठा pp_hwmgr *hwmgr)
अणु
	execute_pwr_table(hwmgr, pwr_virus_table_pre, ARRAY_SIZE(pwr_virus_table_pre));
	execute_pwr_dfy_table(hwmgr, &pwr_virus_section1);
	execute_pwr_dfy_table(hwmgr, &pwr_virus_section2);
	execute_pwr_dfy_table(hwmgr, &pwr_virus_section3);
	execute_pwr_dfy_table(hwmgr, &pwr_virus_section4);
	execute_pwr_dfy_table(hwmgr, &pwr_virus_section5);
	execute_pwr_dfy_table(hwmgr, &pwr_virus_section6);
	execute_pwr_table(hwmgr, pwr_virus_table_post, ARRAY_SIZE(pwr_virus_table_post));

	वापस 0;
पूर्ण

पूर्णांक smu7_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_smumgr *smu_data;
	पूर्णांक r;
	/* Allocate memory क्रम backend निजी data */
	smu_data = (काष्ठा smu7_smumgr *)(hwmgr->smu_backend);
	smu_data->header_buffer.data_size =
			((माप(काष्ठा SMU_DRAMData_TOC) / 4096) + 1) * 4096;

/* Allocate FW image data काष्ठाure and header buffer and
 * send the header buffer address to SMU */
	r = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
		smu_data->header_buffer.data_size,
		PAGE_SIZE,
		AMDGPU_GEM_DOMAIN_VRAM,
		&smu_data->header_buffer.handle,
		&smu_data->header_buffer.mc_addr,
		&smu_data->header_buffer.kaddr);

	अगर (r)
		वापस -EINVAL;

	अगर (!hwmgr->not_vf)
		वापस 0;

	smu_data->smu_buffer.data_size = 200*4096;
	r = amdgpu_bo_create_kernel((काष्ठा amdgpu_device *)hwmgr->adev,
		smu_data->smu_buffer.data_size,
		PAGE_SIZE,
		AMDGPU_GEM_DOMAIN_VRAM,
		&smu_data->smu_buffer.handle,
		&smu_data->smu_buffer.mc_addr,
		&smu_data->smu_buffer.kaddr);

	अगर (r) अणु
		amdgpu_bo_मुक्त_kernel(&smu_data->header_buffer.handle,
					&smu_data->header_buffer.mc_addr,
					&smu_data->header_buffer.kaddr);
		वापस -EINVAL;
	पूर्ण

	अगर (smum_is_hw_avfs_present(hwmgr) &&
	    (hwmgr->feature_mask & PP_AVFS_MASK))
		hwmgr->avfs_supported = true;

	वापस 0;
पूर्ण


पूर्णांक smu7_smu_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_smumgr *smu_data = (काष्ठा smu7_smumgr *)(hwmgr->smu_backend);

	amdgpu_bo_मुक्त_kernel(&smu_data->header_buffer.handle,
					&smu_data->header_buffer.mc_addr,
					&smu_data->header_buffer.kaddr);

	अगर (hwmgr->not_vf)
		amdgpu_bo_मुक्त_kernel(&smu_data->smu_buffer.handle,
					&smu_data->smu_buffer.mc_addr,
					&smu_data->smu_buffer.kaddr);


	kमुक्त(smu_data->toc);
	smu_data->toc = शून्य;
	kमुक्त(hwmgr->smu_backend);
	hwmgr->smu_backend = शून्य;
	वापस 0;
पूर्ण
