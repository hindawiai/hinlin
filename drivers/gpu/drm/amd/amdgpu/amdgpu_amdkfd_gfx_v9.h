<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
 */



व्योम kgd_gfx_v9_program_sh_mem_settings(काष्ठा kgd_dev *kgd, uपूर्णांक32_t vmid,
		uपूर्णांक32_t sh_mem_config,
		uपूर्णांक32_t sh_mem_ape1_base, uपूर्णांक32_t sh_mem_ape1_limit,
		uपूर्णांक32_t sh_mem_bases);
पूर्णांक kgd_gfx_v9_set_pasid_vmid_mapping(काष्ठा kgd_dev *kgd, u32 pasid,
		अचिन्हित पूर्णांक vmid);
पूर्णांक kgd_gfx_v9_init_पूर्णांकerrupts(काष्ठा kgd_dev *kgd, uपूर्णांक32_t pipe_id);
पूर्णांक kgd_gfx_v9_hqd_load(काष्ठा kgd_dev *kgd, व्योम *mqd, uपूर्णांक32_t pipe_id,
			uपूर्णांक32_t queue_id, uपूर्णांक32_t __user *wptr,
			uपूर्णांक32_t wptr_shअगरt, uपूर्णांक32_t wptr_mask,
			काष्ठा mm_काष्ठा *mm);
पूर्णांक kgd_gfx_v9_hiq_mqd_load(काष्ठा kgd_dev *kgd, व्योम *mqd,
			    uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id,
			    uपूर्णांक32_t करोorbell_off);
पूर्णांक kgd_gfx_v9_hqd_dump(काष्ठा kgd_dev *kgd,
			uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id,
			uपूर्णांक32_t (**dump)[2], uपूर्णांक32_t *n_regs);
bool kgd_gfx_v9_hqd_is_occupied(काष्ठा kgd_dev *kgd, uपूर्णांक64_t queue_address,
		uपूर्णांक32_t pipe_id, uपूर्णांक32_t queue_id);
पूर्णांक kgd_gfx_v9_hqd_destroy(काष्ठा kgd_dev *kgd, व्योम *mqd,
				क्रमागत kfd_preempt_type reset_type,
				अचिन्हित पूर्णांक uसमयout, uपूर्णांक32_t pipe_id,
				uपूर्णांक32_t queue_id);
पूर्णांक kgd_gfx_v9_address_watch_disable(काष्ठा kgd_dev *kgd);
पूर्णांक kgd_gfx_v9_address_watch_execute(काष्ठा kgd_dev *kgd,
					अचिन्हित पूर्णांक watch_poपूर्णांक_id,
					uपूर्णांक32_t cntl_val,
					uपूर्णांक32_t addr_hi,
					uपूर्णांक32_t addr_lo);
पूर्णांक kgd_gfx_v9_wave_control_execute(काष्ठा kgd_dev *kgd,
					uपूर्णांक32_t gfx_index_val,
					uपूर्णांक32_t sq_cmd);
uपूर्णांक32_t kgd_gfx_v9_address_watch_get_offset(काष्ठा kgd_dev *kgd,
					अचिन्हित पूर्णांक watch_poपूर्णांक_id,
					अचिन्हित पूर्णांक reg_offset);

bool kgd_gfx_v9_get_atc_vmid_pasid_mapping_info(काष्ठा kgd_dev *kgd,
					uपूर्णांक8_t vmid, uपूर्णांक16_t *p_pasid);

व्योम kgd_gfx_v9_set_vm_context_page_table_base(काष्ठा kgd_dev *kgd,
			uपूर्णांक32_t vmid, uपूर्णांक64_t page_table_base);
व्योम kgd_gfx_v9_get_cu_occupancy(काष्ठा kgd_dev *kgd, पूर्णांक pasid,
		पूर्णांक *pasid_wave_cnt, पूर्णांक *max_waves_per_cu);
