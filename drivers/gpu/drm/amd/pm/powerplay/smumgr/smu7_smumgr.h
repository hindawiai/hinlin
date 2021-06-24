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

#अगर_अघोषित _SMU7_SMUMANAGER_H
#घोषणा _SMU7_SMUMANAGER_H


#समावेश <pp_endian.h>

#घोषणा SMC_RAM_END 0x40000

काष्ठा smu7_buffer_entry अणु
	uपूर्णांक32_t data_size;
	uपूर्णांक64_t mc_addr;
	व्योम *kaddr;
	काष्ठा amdgpu_bo *handle;
पूर्ण;

काष्ठा smu7_smumgr अणु
	काष्ठा smu7_buffer_entry smu_buffer;
	काष्ठा smu7_buffer_entry header_buffer;
	काष्ठा SMU_DRAMData_TOC *toc;

	uपूर्णांक32_t                             soft_regs_start;
	uपूर्णांक32_t                             dpm_table_start;
	uपूर्णांक32_t                             mc_reg_table_start;
	uपूर्णांक32_t                             fan_table_start;
	uपूर्णांक32_t                             arb_table_start;
	uपूर्णांक32_t                             ulv_setting_starts;
	uपूर्णांक8_t                              security_hard_key;
	uपूर्णांक32_t                             acpi_optimization;
	uपूर्णांक32_t                             avfs_btc_param;
पूर्ण;


पूर्णांक smu7_copy_bytes_from_smc(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t smc_start_address,
				uपूर्णांक32_t *dest, uपूर्णांक32_t byte_count, uपूर्णांक32_t limit);
पूर्णांक smu7_copy_bytes_to_smc(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t smc_start_address,
			स्थिर uपूर्णांक8_t *src, uपूर्णांक32_t byte_count, uपूर्णांक32_t limit);
पूर्णांक smu7_program_jump_on_start(काष्ठा pp_hwmgr *hwmgr);
bool smu7_is_smc_ram_running(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_send_msg_to_smc(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t msg);
पूर्णांक smu7_send_msg_to_smc_with_parameter(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t msg,
						uपूर्णांक32_t parameter);
uपूर्णांक32_t smu7_get_argument(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_send_msg_to_smc_offset(काष्ठा pp_hwmgr *hwmgr);

क्रमागत cgs_ucode_id smu7_convert_fw_type_to_cgs(uपूर्णांक32_t fw_type);
पूर्णांक smu7_पढ़ो_smc_sram_dword(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t smc_addr,
						uपूर्णांक32_t *value, uपूर्णांक32_t limit);
पूर्णांक smu7_ग_लिखो_smc_sram_dword(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t smc_addr,
						uपूर्णांक32_t value, uपूर्णांक32_t limit);

पूर्णांक smu7_request_smu_load_fw(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_check_fw_load_finish(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t fw_type);
पूर्णांक smu7_reload_firmware(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_upload_smu_firmware_image(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_init(काष्ठा pp_hwmgr *hwmgr);
पूर्णांक smu7_smu_fini(काष्ठा pp_hwmgr *hwmgr);

पूर्णांक smu7_setup_pwr_virus(काष्ठा pp_hwmgr *hwmgr);

#पूर्ण_अगर
