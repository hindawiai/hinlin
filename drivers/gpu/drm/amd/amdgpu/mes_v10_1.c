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
 *
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश "amdgpu.h"
#समावेश "soc15_common.h"
#समावेश "nv.h"
#समावेश "gc/gc_10_1_0_offset.h"
#समावेश "gc/gc_10_1_0_sh_mask.h"
#समावेश "v10_structs.h"
#समावेश "mes_api_def.h"

#घोषणा mmCP_MES_IC_OP_CNTL_Sienna_Cichlid               0x2820
#घोषणा mmCP_MES_IC_OP_CNTL_Sienna_Cichlid_BASE_IDX      1

MODULE_FIRMWARE("amdgpu/navi10_mes.bin");
MODULE_FIRMWARE("amdgpu/sienna_cichlid_mes.bin");

अटल पूर्णांक mes_v10_1_hw_fini(व्योम *handle);

#घोषणा MES_EOP_SIZE   2048

अटल व्योम mes_v10_1_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell) अणु
		atomic64_set((atomic64_t *)&adev->wb.wb[ring->wptr_offs],
			     ring->wptr);
		WDOORBELL64(ring->करोorbell_index, ring->wptr);
	पूर्ण अन्यथा अणु
		BUG();
	पूर्ण
पूर्ण

अटल u64 mes_v10_1_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	वापस ring->adev->wb.wb[ring->rptr_offs];
पूर्ण

अटल u64 mes_v10_1_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	u64 wptr;

	अगर (ring->use_करोorbell)
		wptr = atomic64_पढ़ो((atomic64_t *)
				     &ring->adev->wb.wb[ring->wptr_offs]);
	अन्यथा
		BUG();
	वापस wptr;
पूर्ण

अटल स्थिर काष्ठा amdgpu_ring_funcs mes_v10_1_ring_funcs = अणु
	.type = AMDGPU_RING_TYPE_MES,
	.align_mask = 1,
	.nop = 0,
	.support_64bit_ptrs = true,
	.get_rptr = mes_v10_1_ring_get_rptr,
	.get_wptr = mes_v10_1_ring_get_wptr,
	.set_wptr = mes_v10_1_ring_set_wptr,
	.insert_nop = amdgpu_ring_insert_nop,
पूर्ण;

अटल पूर्णांक mes_v10_1_submit_pkt_and_poll_completion(काष्ठा amdgpu_mes *mes,
						    व्योम *pkt, पूर्णांक size)
अणु
	पूर्णांक ndw = size / 4;
	चिन्हित दीर्घ r;
	जोड़ MESAPI__ADD_QUEUE *x_pkt = pkt;
	काष्ठा amdgpu_device *adev = mes->adev;
	काष्ठा amdgpu_ring *ring = &mes->ring;

	BUG_ON(size % 4 != 0);

	अगर (amdgpu_ring_alloc(ring, ndw))
		वापस -ENOMEM;

	amdgpu_ring_ग_लिखो_multiple(ring, pkt, ndw);
	amdgpu_ring_commit(ring);

	DRM_DEBUG("MES msg=%d was emitted\n", x_pkt->header.opcode);

	r = amdgpu_fence_रुको_polling(ring, ring->fence_drv.sync_seq,
				      adev->usec_समयout);
	अगर (r < 1) अणु
		DRM_ERROR("MES failed to response msg=%d\n",
			  x_pkt->header.opcode);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक convert_to_mes_queue_type(पूर्णांक queue_type)
अणु
	अगर (queue_type == AMDGPU_RING_TYPE_GFX)
		वापस MES_QUEUE_TYPE_GFX;
	अन्यथा अगर (queue_type == AMDGPU_RING_TYPE_COMPUTE)
		वापस MES_QUEUE_TYPE_COMPUTE;
	अन्यथा अगर (queue_type == AMDGPU_RING_TYPE_SDMA)
		वापस MES_QUEUE_TYPE_SDMA;
	अन्यथा
		BUG();
	वापस -1;
पूर्ण

अटल पूर्णांक mes_v10_1_add_hw_queue(काष्ठा amdgpu_mes *mes,
				  काष्ठा mes_add_queue_input *input)
अणु
	काष्ठा amdgpu_device *adev = mes->adev;
	जोड़ MESAPI__ADD_QUEUE mes_add_queue_pkt;

	स_रखो(&mes_add_queue_pkt, 0, माप(mes_add_queue_pkt));

	mes_add_queue_pkt.header.type = MES_API_TYPE_SCHEDULER;
	mes_add_queue_pkt.header.opcode = MES_SCH_API_ADD_QUEUE;
	mes_add_queue_pkt.header.dwsize = API_FRAME_SIZE_IN_DWORDS;

	mes_add_queue_pkt.process_id = input->process_id;
	mes_add_queue_pkt.page_table_base_addr =
		input->page_table_base_addr - adev->gmc.vram_start;
	mes_add_queue_pkt.process_बहु_शुरू = input->process_बहु_शुरू;
	mes_add_queue_pkt.process_बहु_पूर्ण = input->process_बहु_पूर्ण;
	mes_add_queue_pkt.process_quantum = input->process_quantum;
	mes_add_queue_pkt.process_context_addr = input->process_context_addr;
	mes_add_queue_pkt.gang_quantum = input->gang_quantum;
	mes_add_queue_pkt.gang_context_addr = input->gang_context_addr;
	mes_add_queue_pkt.inprocess_gang_priority =
		input->inprocess_gang_priority;
	mes_add_queue_pkt.gang_global_priority_level =
		input->gang_global_priority_level;
	mes_add_queue_pkt.करोorbell_offset = input->करोorbell_offset;
	mes_add_queue_pkt.mqd_addr = input->mqd_addr;
	mes_add_queue_pkt.wptr_addr = input->wptr_addr;
	mes_add_queue_pkt.queue_type =
		convert_to_mes_queue_type(input->queue_type);
	mes_add_queue_pkt.paging = input->paging;

	mes_add_queue_pkt.api_status.api_completion_fence_addr =
		mes->ring.fence_drv.gpu_addr;
	mes_add_queue_pkt.api_status.api_completion_fence_value =
		++mes->ring.fence_drv.sync_seq;

	वापस mes_v10_1_submit_pkt_and_poll_completion(mes,
			&mes_add_queue_pkt, माप(mes_add_queue_pkt));
पूर्ण

अटल पूर्णांक mes_v10_1_हटाओ_hw_queue(काष्ठा amdgpu_mes *mes,
				     काष्ठा mes_हटाओ_queue_input *input)
अणु
	जोड़ MESAPI__REMOVE_QUEUE mes_हटाओ_queue_pkt;

	स_रखो(&mes_हटाओ_queue_pkt, 0, माप(mes_हटाओ_queue_pkt));

	mes_हटाओ_queue_pkt.header.type = MES_API_TYPE_SCHEDULER;
	mes_हटाओ_queue_pkt.header.opcode = MES_SCH_API_REMOVE_QUEUE;
	mes_हटाओ_queue_pkt.header.dwsize = API_FRAME_SIZE_IN_DWORDS;

	mes_हटाओ_queue_pkt.करोorbell_offset = input->करोorbell_offset;
	mes_हटाओ_queue_pkt.gang_context_addr = input->gang_context_addr;

	mes_हटाओ_queue_pkt.api_status.api_completion_fence_addr =
		mes->ring.fence_drv.gpu_addr;
	mes_हटाओ_queue_pkt.api_status.api_completion_fence_value =
		++mes->ring.fence_drv.sync_seq;

	वापस mes_v10_1_submit_pkt_and_poll_completion(mes,
			&mes_हटाओ_queue_pkt, माप(mes_हटाओ_queue_pkt));
पूर्ण

अटल पूर्णांक mes_v10_1_suspend_gang(काष्ठा amdgpu_mes *mes,
				  काष्ठा mes_suspend_gang_input *input)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mes_v10_1_resume_gang(काष्ठा amdgpu_mes *mes,
				 काष्ठा mes_resume_gang_input *input)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mes_v10_1_query_sched_status(काष्ठा amdgpu_mes *mes)
अणु
	जोड़ MESAPI__QUERY_MES_STATUS mes_status_pkt;

	स_रखो(&mes_status_pkt, 0, माप(mes_status_pkt));

	mes_status_pkt.header.type = MES_API_TYPE_SCHEDULER;
	mes_status_pkt.header.opcode = MES_SCH_API_QUERY_SCHEDULER_STATUS;
	mes_status_pkt.header.dwsize = API_FRAME_SIZE_IN_DWORDS;

	mes_status_pkt.api_status.api_completion_fence_addr =
		mes->ring.fence_drv.gpu_addr;
	mes_status_pkt.api_status.api_completion_fence_value =
		++mes->ring.fence_drv.sync_seq;

	वापस mes_v10_1_submit_pkt_and_poll_completion(mes,
			&mes_status_pkt, माप(mes_status_pkt));
पूर्ण

अटल पूर्णांक mes_v10_1_set_hw_resources(काष्ठा amdgpu_mes *mes)
अणु
	पूर्णांक i;
	काष्ठा amdgpu_device *adev = mes->adev;
	जोड़ MESAPI_SET_HW_RESOURCES mes_set_hw_res_pkt;

	स_रखो(&mes_set_hw_res_pkt, 0, माप(mes_set_hw_res_pkt));

	mes_set_hw_res_pkt.header.type = MES_API_TYPE_SCHEDULER;
	mes_set_hw_res_pkt.header.opcode = MES_SCH_API_SET_HW_RSRC;
	mes_set_hw_res_pkt.header.dwsize = API_FRAME_SIZE_IN_DWORDS;

	mes_set_hw_res_pkt.vmid_mask_mmhub = mes->vmid_mask_mmhub;
	mes_set_hw_res_pkt.vmid_mask_gfxhub = mes->vmid_mask_gfxhub;
	mes_set_hw_res_pkt.gds_size = adev->gds.gds_size;
	mes_set_hw_res_pkt.paging_vmid = 0;
	mes_set_hw_res_pkt.g_sch_ctx_gpu_mc_ptr = mes->sch_ctx_gpu_addr;
	mes_set_hw_res_pkt.query_status_fence_gpu_mc_ptr =
		mes->query_status_fence_gpu_addr;

	क्रम (i = 0; i < MAX_COMPUTE_PIPES; i++)
		mes_set_hw_res_pkt.compute_hqd_mask[i] =
			mes->compute_hqd_mask[i];

	क्रम (i = 0; i < MAX_GFX_PIPES; i++)
		mes_set_hw_res_pkt.gfx_hqd_mask[i] = mes->gfx_hqd_mask[i];

	क्रम (i = 0; i < MAX_SDMA_PIPES; i++)
		mes_set_hw_res_pkt.sdma_hqd_mask[i] = mes->sdma_hqd_mask[i];

	क्रम (i = 0; i < AMD_PRIORITY_NUM_LEVELS; i++)
		mes_set_hw_res_pkt.agreegated_करोorbells[i] =
			mes->agreegated_करोorbells[i];

	mes_set_hw_res_pkt.api_status.api_completion_fence_addr =
		mes->ring.fence_drv.gpu_addr;
	mes_set_hw_res_pkt.api_status.api_completion_fence_value =
		++mes->ring.fence_drv.sync_seq;

	वापस mes_v10_1_submit_pkt_and_poll_completion(mes,
			&mes_set_hw_res_pkt, माप(mes_set_hw_res_pkt));
पूर्ण

अटल स्थिर काष्ठा amdgpu_mes_funcs mes_v10_1_funcs = अणु
	.add_hw_queue = mes_v10_1_add_hw_queue,
	.हटाओ_hw_queue = mes_v10_1_हटाओ_hw_queue,
	.suspend_gang = mes_v10_1_suspend_gang,
	.resume_gang = mes_v10_1_resume_gang,
पूर्ण;

अटल पूर्णांक mes_v10_1_init_microcode(काष्ठा amdgpu_device *adev)
अणु
	स्थिर अक्षर *chip_name;
	अक्षर fw_name[30];
	पूर्णांक err;
	स्थिर काष्ठा mes_firmware_header_v1_0 *mes_hdr;
	काष्ठा amdgpu_firmware_info *info;

	चयन (adev->asic_type) अणु
	हाल CHIP_NAVI10:
		chip_name = "navi10";
		अवरोध;
	हाल CHIP_SIENNA_CICHLID:
		chip_name = "sienna_cichlid";
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	snम_लिखो(fw_name, माप(fw_name), "amdgpu/%s_mes.bin", chip_name);
	err = request_firmware(&adev->mes.fw, fw_name, adev->dev);
	अगर (err)
		वापस err;

	err = amdgpu_ucode_validate(adev->mes.fw);
	अगर (err) अणु
		release_firmware(adev->mes.fw);
		adev->mes.fw = शून्य;
		वापस err;
	पूर्ण

	mes_hdr = (स्थिर काष्ठा mes_firmware_header_v1_0 *)adev->mes.fw->data;
	adev->mes.ucode_fw_version = le32_to_cpu(mes_hdr->mes_ucode_version);
	adev->mes.ucode_fw_version =
		le32_to_cpu(mes_hdr->mes_ucode_data_version);
	adev->mes.uc_start_addr =
		le32_to_cpu(mes_hdr->mes_uc_start_addr_lo) |
		((uपूर्णांक64_t)(le32_to_cpu(mes_hdr->mes_uc_start_addr_hi)) << 32);
	adev->mes.data_start_addr =
		le32_to_cpu(mes_hdr->mes_data_start_addr_lo) |
		((uपूर्णांक64_t)(le32_to_cpu(mes_hdr->mes_data_start_addr_hi)) << 32);

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_MES];
		info->ucode_id = AMDGPU_UCODE_ID_CP_MES;
		info->fw = adev->mes.fw;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(mes_hdr->mes_ucode_size_bytes),
			      PAGE_SIZE);

		info = &adev->firmware.ucode[AMDGPU_UCODE_ID_CP_MES_DATA];
		info->ucode_id = AMDGPU_UCODE_ID_CP_MES_DATA;
		info->fw = adev->mes.fw;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(mes_hdr->mes_ucode_data_size_bytes),
			      PAGE_SIZE);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mes_v10_1_मुक्त_microcode(काष्ठा amdgpu_device *adev)
अणु
	release_firmware(adev->mes.fw);
	adev->mes.fw = शून्य;
पूर्ण

अटल पूर्णांक mes_v10_1_allocate_ucode_buffer(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;
	स्थिर काष्ठा mes_firmware_header_v1_0 *mes_hdr;
	स्थिर __le32 *fw_data;
	अचिन्हित fw_size;

	mes_hdr = (स्थिर काष्ठा mes_firmware_header_v1_0 *)
		adev->mes.fw->data;

	fw_data = (स्थिर __le32 *)(adev->mes.fw->data +
		   le32_to_cpu(mes_hdr->mes_ucode_offset_bytes));
	fw_size = le32_to_cpu(mes_hdr->mes_ucode_size_bytes);

	r = amdgpu_bo_create_reserved(adev, fw_size,
				      PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
				      &adev->mes.ucode_fw_obj,
				      &adev->mes.ucode_fw_gpu_addr,
				      (व्योम **)&adev->mes.ucode_fw_ptr);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) failed to create mes fw bo\n", r);
		वापस r;
	पूर्ण

	स_नकल(adev->mes.ucode_fw_ptr, fw_data, fw_size);

	amdgpu_bo_kunmap(adev->mes.ucode_fw_obj);
	amdgpu_bo_unreserve(adev->mes.ucode_fw_obj);

	वापस 0;
पूर्ण

अटल पूर्णांक mes_v10_1_allocate_ucode_data_buffer(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;
	स्थिर काष्ठा mes_firmware_header_v1_0 *mes_hdr;
	स्थिर __le32 *fw_data;
	अचिन्हित fw_size;

	mes_hdr = (स्थिर काष्ठा mes_firmware_header_v1_0 *)
		adev->mes.fw->data;

	fw_data = (स्थिर __le32 *)(adev->mes.fw->data +
		   le32_to_cpu(mes_hdr->mes_ucode_data_offset_bytes));
	fw_size = le32_to_cpu(mes_hdr->mes_ucode_data_size_bytes);

	r = amdgpu_bo_create_reserved(adev, fw_size,
				      64 * 1024, AMDGPU_GEM_DOMAIN_GTT,
				      &adev->mes.data_fw_obj,
				      &adev->mes.data_fw_gpu_addr,
				      (व्योम **)&adev->mes.data_fw_ptr);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) failed to create mes data fw bo\n", r);
		वापस r;
	पूर्ण

	स_नकल(adev->mes.data_fw_ptr, fw_data, fw_size);

	amdgpu_bo_kunmap(adev->mes.data_fw_obj);
	amdgpu_bo_unreserve(adev->mes.data_fw_obj);

	वापस 0;
पूर्ण

अटल व्योम mes_v10_1_मुक्त_ucode_buffers(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_bo_मुक्त_kernel(&adev->mes.data_fw_obj,
			      &adev->mes.data_fw_gpu_addr,
			      (व्योम **)&adev->mes.data_fw_ptr);

	amdgpu_bo_मुक्त_kernel(&adev->mes.ucode_fw_obj,
			      &adev->mes.ucode_fw_gpu_addr,
			      (व्योम **)&adev->mes.ucode_fw_ptr);
पूर्ण

अटल व्योम mes_v10_1_enable(काष्ठा amdgpu_device *adev, bool enable)
अणु
	uपूर्णांक32_t data = 0;

	अगर (enable) अणु
		data = RREG32_SOC15(GC, 0, mmCP_MES_CNTL);
		data = REG_SET_FIELD(data, CP_MES_CNTL, MES_PIPE0_RESET, 1);
		WREG32_SOC15(GC, 0, mmCP_MES_CNTL, data);

		/* set ucode start address */
		WREG32_SOC15(GC, 0, mmCP_MES_PRGRM_CNTR_START,
			     (uपूर्णांक32_t)(adev->mes.uc_start_addr) >> 2);

		/* clear BYPASS_UNCACHED to aव्योम hangs after पूर्णांकerrupt. */
		data = RREG32_SOC15(GC, 0, mmCP_MES_DC_OP_CNTL);
		data = REG_SET_FIELD(data, CP_MES_DC_OP_CNTL,
				     BYPASS_UNCACHED, 0);
		WREG32_SOC15(GC, 0, mmCP_MES_DC_OP_CNTL, data);

		/* unhalt MES and activate pipe0 */
		data = REG_SET_FIELD(0, CP_MES_CNTL, MES_PIPE0_ACTIVE, 1);
		WREG32_SOC15(GC, 0, mmCP_MES_CNTL, data);
	पूर्ण अन्यथा अणु
		data = RREG32_SOC15(GC, 0, mmCP_MES_CNTL);
		data = REG_SET_FIELD(data, CP_MES_CNTL, MES_PIPE0_ACTIVE, 0);
		data = REG_SET_FIELD(data, CP_MES_CNTL,
				     MES_INVALIDATE_ICACHE, 1);
		data = REG_SET_FIELD(data, CP_MES_CNTL, MES_PIPE0_RESET, 1);
		data = REG_SET_FIELD(data, CP_MES_CNTL, MES_HALT, 1);
		WREG32_SOC15(GC, 0, mmCP_MES_CNTL, data);
	पूर्ण
पूर्ण

/* This function is क्रम backकरोor MES firmware */
अटल पूर्णांक mes_v10_1_load_microcode(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;
	uपूर्णांक32_t data;

	अगर (!adev->mes.fw)
		वापस -EINVAL;

	r = mes_v10_1_allocate_ucode_buffer(adev);
	अगर (r)
		वापस r;

	r = mes_v10_1_allocate_ucode_data_buffer(adev);
	अगर (r) अणु
		mes_v10_1_मुक्त_ucode_buffers(adev);
		वापस r;
	पूर्ण

	mes_v10_1_enable(adev, false);

	WREG32_SOC15(GC, 0, mmCP_MES_IC_BASE_CNTL, 0);

	mutex_lock(&adev->srbm_mutex);
	/* me=3, pipe=0, queue=0 */
	nv_grbm_select(adev, 3, 0, 0, 0);

	/* set ucode start address */
	WREG32_SOC15(GC, 0, mmCP_MES_PRGRM_CNTR_START,
		     (uपूर्णांक32_t)(adev->mes.uc_start_addr) >> 2);

	/* set ucode fimrware address */
	WREG32_SOC15(GC, 0, mmCP_MES_IC_BASE_LO,
		     lower_32_bits(adev->mes.ucode_fw_gpu_addr));
	WREG32_SOC15(GC, 0, mmCP_MES_IC_BASE_HI,
		     upper_32_bits(adev->mes.ucode_fw_gpu_addr));

	/* set ucode inकाष्ठाion cache boundary to 2M-1 */
	WREG32_SOC15(GC, 0, mmCP_MES_MIBOUND_LO, 0x1FFFFF);

	/* set ucode data firmware address */
	WREG32_SOC15(GC, 0, mmCP_MES_MDBASE_LO,
		     lower_32_bits(adev->mes.data_fw_gpu_addr));
	WREG32_SOC15(GC, 0, mmCP_MES_MDBASE_HI,
		     upper_32_bits(adev->mes.data_fw_gpu_addr));

	/* Set 0x3FFFF (256K-1) to CP_MES_MDBOUND_LO */
	WREG32_SOC15(GC, 0, mmCP_MES_MDBOUND_LO, 0x3FFFF);

	/* invalidate ICACHE */
	चयन (adev->asic_type) अणु
	हाल CHIP_SIENNA_CICHLID:
		data = RREG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTL_Sienna_Cichlid);
		अवरोध;
	शेष:
		data = RREG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTL);
		अवरोध;
	पूर्ण
	data = REG_SET_FIELD(data, CP_MES_IC_OP_CNTL, PRIME_ICACHE, 0);
	data = REG_SET_FIELD(data, CP_MES_IC_OP_CNTL, INVALIDATE_CACHE, 1);
	चयन (adev->asic_type) अणु
	हाल CHIP_SIENNA_CICHLID:
		WREG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTL_Sienna_Cichlid, data);
		अवरोध;
	शेष:
		WREG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTL, data);
		अवरोध;
	पूर्ण

	/* prime the ICACHE. */
	चयन (adev->asic_type) अणु
	हाल CHIP_SIENNA_CICHLID:
		data = RREG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTL_Sienna_Cichlid);
		अवरोध;
	शेष:
		data = RREG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTL);
		अवरोध;
	पूर्ण
	data = REG_SET_FIELD(data, CP_MES_IC_OP_CNTL, PRIME_ICACHE, 1);
	चयन (adev->asic_type) अणु
	हाल CHIP_SIENNA_CICHLID:
		WREG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTL_Sienna_Cichlid, data);
		अवरोध;
	शेष:
		WREG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTL, data);
		अवरोध;
	पूर्ण

	nv_grbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक mes_v10_1_allocate_eop_buf(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;
	u32 *eop;

	r = amdgpu_bo_create_reserved(adev, MES_EOP_SIZE, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_GTT,
				      &adev->mes.eop_gpu_obj,
				      &adev->mes.eop_gpu_addr,
				      (व्योम **)&eop);
	अगर (r) अणु
		dev_warn(adev->dev, "(%d) create EOP bo failed\n", r);
		वापस r;
	पूर्ण

	स_रखो(eop, 0, adev->mes.eop_gpu_obj->tbo.base.size);

	amdgpu_bo_kunmap(adev->mes.eop_gpu_obj);
	amdgpu_bo_unreserve(adev->mes.eop_gpu_obj);

	वापस 0;
पूर्ण

अटल पूर्णांक mes_v10_1_allocate_mem_slots(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	r = amdgpu_device_wb_get(adev, &adev->mes.sch_ctx_offs);
	अगर (r) अणु
		dev_err(adev->dev,
			"(%d) mes sch_ctx_offs wb alloc failed\n", r);
		वापस r;
	पूर्ण
	adev->mes.sch_ctx_gpu_addr =
		adev->wb.gpu_addr + (adev->mes.sch_ctx_offs * 4);
	adev->mes.sch_ctx_ptr =
		(uपूर्णांक64_t *)&adev->wb.wb[adev->mes.sch_ctx_offs];

	r = amdgpu_device_wb_get(adev, &adev->mes.query_status_fence_offs);
	अगर (r) अणु
		dev_err(adev->dev,
			"(%d) query_status_fence_offs wb alloc failed\n", r);
		वापस r;
	पूर्ण
	adev->mes.query_status_fence_gpu_addr =
		adev->wb.gpu_addr + (adev->mes.query_status_fence_offs * 4);
	adev->mes.query_status_fence_ptr =
		(uपूर्णांक64_t *)&adev->wb.wb[adev->mes.query_status_fence_offs];

	वापस 0;
पूर्ण

अटल पूर्णांक mes_v10_1_mqd_init(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा v10_compute_mqd *mqd = ring->mqd_ptr;
	uपूर्णांक64_t hqd_gpu_addr, wb_gpu_addr, eop_base_addr;
	uपूर्णांक32_t पंचांगp;

	mqd->header = 0xC0310800;
	mqd->compute_pipelinestat_enable = 0x00000001;
	mqd->compute_अटल_thपढ़ो_mgmt_se0 = 0xffffffff;
	mqd->compute_अटल_thपढ़ो_mgmt_se1 = 0xffffffff;
	mqd->compute_अटल_thपढ़ो_mgmt_se2 = 0xffffffff;
	mqd->compute_अटल_thपढ़ो_mgmt_se3 = 0xffffffff;
	mqd->compute_misc_reserved = 0x00000003;

	eop_base_addr = ring->eop_gpu_addr >> 8;
	mqd->cp_hqd_eop_base_addr_lo = eop_base_addr;
	mqd->cp_hqd_eop_base_addr_hi = upper_32_bits(eop_base_addr);

	/* set the EOP size, रेजिस्टर value is 2^(EOP_SIZE+1) dwords */
	पंचांगp = RREG32_SOC15(GC, 0, mmCP_HQD_EOP_CONTROL);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_EOP_CONTROL, EOP_SIZE,
			(order_base_2(MES_EOP_SIZE / 4) - 1));

	mqd->cp_hqd_eop_control = पंचांगp;

	/* enable करोorbell? */
	पंचांगp = RREG32_SOC15(GC, 0, mmCP_HQD_PQ_DOORBELL_CONTROL);

	अगर (ring->use_करोorbell) अणु
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_DOORBELL_CONTROL,
				    DOORBELL_OFFSET, ring->करोorbell_index);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_DOORBELL_CONTROL,
				    DOORBELL_EN, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_DOORBELL_CONTROL,
				    DOORBELL_SOURCE, 0);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_DOORBELL_CONTROL,
				    DOORBELL_HIT, 0);
	पूर्ण
	अन्यथा
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_DOORBELL_CONTROL,
				    DOORBELL_EN, 0);

	mqd->cp_hqd_pq_करोorbell_control = पंचांगp;

	/* disable the queue अगर it's active */
	ring->wptr = 0;
	mqd->cp_hqd_dequeue_request = 0;
	mqd->cp_hqd_pq_rptr = 0;
	mqd->cp_hqd_pq_wptr_lo = 0;
	mqd->cp_hqd_pq_wptr_hi = 0;

	/* set the poपूर्णांकer to the MQD */
	mqd->cp_mqd_base_addr_lo = ring->mqd_gpu_addr & 0xfffffffc;
	mqd->cp_mqd_base_addr_hi = upper_32_bits(ring->mqd_gpu_addr);

	/* set MQD vmid to 0 */
	पंचांगp = RREG32_SOC15(GC, 0, mmCP_MQD_CONTROL);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_MQD_CONTROL, VMID, 0);
	mqd->cp_mqd_control = पंचांगp;

	/* set the poपूर्णांकer to the HQD, this is similar CP_RB0_BASE/_HI */
	hqd_gpu_addr = ring->gpu_addr >> 8;
	mqd->cp_hqd_pq_base_lo = hqd_gpu_addr;
	mqd->cp_hqd_pq_base_hi = upper_32_bits(hqd_gpu_addr);

	/* set up the HQD, this is similar to CP_RB0_CNTL */
	पंचांगp = RREG32_SOC15(GC, 0, mmCP_HQD_PQ_CONTROL);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, QUEUE_SIZE,
			    (order_base_2(ring->ring_size / 4) - 1));
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, RPTR_BLOCK_SIZE,
			    ((order_base_2(AMDGPU_GPU_PAGE_SIZE / 4) - 1) << 8));
#अगर_घोषित __BIG_ENDIAN
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, ENDIAN_SWAP, 1);
#पूर्ण_अगर
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, UNORD_DISPATCH, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, TUNNEL_DISPATCH, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, PRIV_STATE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_CONTROL, KMD_QUEUE, 1);
	mqd->cp_hqd_pq_control = पंचांगp;

	/* set the wb address whether it's enabled or not */
	wb_gpu_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);
	mqd->cp_hqd_pq_rptr_report_addr_lo = wb_gpu_addr & 0xfffffffc;
	mqd->cp_hqd_pq_rptr_report_addr_hi =
		upper_32_bits(wb_gpu_addr) & 0xffff;

	/* only used अगर CP_PQ_WPTR_POLL_CNTL.CP_PQ_WPTR_POLL_CNTL__EN_MASK=1 */
	wb_gpu_addr = adev->wb.gpu_addr + (ring->wptr_offs * 4);
	mqd->cp_hqd_pq_wptr_poll_addr_lo = wb_gpu_addr & 0xfffffff8;
	mqd->cp_hqd_pq_wptr_poll_addr_hi = upper_32_bits(wb_gpu_addr) & 0xffff;

	पंचांगp = 0;
	/* enable the करोorbell अगर requested */
	अगर (ring->use_करोorbell) अणु
		पंचांगp = RREG32_SOC15(GC, 0, mmCP_HQD_PQ_DOORBELL_CONTROL);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_DOORBELL_CONTROL,
				DOORBELL_OFFSET, ring->करोorbell_index);

		पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_DOORBELL_CONTROL,
				    DOORBELL_EN, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_DOORBELL_CONTROL,
				    DOORBELL_SOURCE, 0);
		पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PQ_DOORBELL_CONTROL,
				    DOORBELL_HIT, 0);
	पूर्ण

	mqd->cp_hqd_pq_करोorbell_control = पंचांगp;

	/* reset पढ़ो and ग_लिखो poपूर्णांकers, similar to CP_RB0_WPTR/_RPTR */
	ring->wptr = 0;
	mqd->cp_hqd_pq_rptr = RREG32_SOC15(GC, 0, mmCP_HQD_PQ_RPTR);

	/* set the vmid क्रम the queue */
	mqd->cp_hqd_vmid = 0;

	पंचांगp = RREG32_SOC15(GC, 0, mmCP_HQD_PERSISTENT_STATE);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_PERSISTENT_STATE, PRELOAD_SIZE, 0x53);
	mqd->cp_hqd_persistent_state = पंचांगp;

	/* set MIN_IB_AVAIL_SIZE */
	पंचांगp = RREG32_SOC15(GC, 0, mmCP_HQD_IB_CONTROL);
	पंचांगp = REG_SET_FIELD(पंचांगp, CP_HQD_IB_CONTROL, MIN_IB_AVAIL_SIZE, 3);
	mqd->cp_hqd_ib_control = पंचांगp;

	/* activate the queue */
	mqd->cp_hqd_active = 1;
	वापस 0;
पूर्ण

अटल व्योम mes_v10_1_queue_init_रेजिस्टर(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा v10_compute_mqd *mqd = ring->mqd_ptr;
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t data = 0;

	mutex_lock(&adev->srbm_mutex);
	nv_grbm_select(adev, 3, 0, 0, 0);

	/* set CP_HQD_VMID.VMID = 0. */
	data = RREG32_SOC15(GC, 0, mmCP_HQD_VMID);
	data = REG_SET_FIELD(data, CP_HQD_VMID, VMID, 0);
	WREG32_SOC15(GC, 0, mmCP_HQD_VMID, data);

	/* set CP_HQD_PQ_DOORBELL_CONTROL.DOORBELL_EN=0 */
	data = RREG32_SOC15(GC, 0, mmCP_HQD_PQ_DOORBELL_CONTROL);
	data = REG_SET_FIELD(data, CP_HQD_PQ_DOORBELL_CONTROL,
			     DOORBELL_EN, 0);
	WREG32_SOC15(GC, 0, mmCP_HQD_PQ_DOORBELL_CONTROL, data);

	/* set CP_MQD_BASE_ADDR/HI with the MQD base address */
	WREG32_SOC15(GC, 0, mmCP_MQD_BASE_ADDR, mqd->cp_mqd_base_addr_lo);
	WREG32_SOC15(GC, 0, mmCP_MQD_BASE_ADDR_HI, mqd->cp_mqd_base_addr_hi);

	/* set CP_MQD_CONTROL.VMID=0 */
	data = RREG32_SOC15(GC, 0, mmCP_MQD_CONTROL);
	data = REG_SET_FIELD(data, CP_MQD_CONTROL, VMID, 0);
	WREG32_SOC15(GC, 0, mmCP_MQD_CONTROL, 0);

	/* set CP_HQD_PQ_BASE/HI with the ring buffer base address */
	WREG32_SOC15(GC, 0, mmCP_HQD_PQ_BASE, mqd->cp_hqd_pq_base_lo);
	WREG32_SOC15(GC, 0, mmCP_HQD_PQ_BASE_HI, mqd->cp_hqd_pq_base_hi);

	/* set CP_HQD_PQ_RPTR_REPORT_ADDR/HI */
	WREG32_SOC15(GC, 0, mmCP_HQD_PQ_RPTR_REPORT_ADDR,
		     mqd->cp_hqd_pq_rptr_report_addr_lo);
	WREG32_SOC15(GC, 0, mmCP_HQD_PQ_RPTR_REPORT_ADDR_HI,
		     mqd->cp_hqd_pq_rptr_report_addr_hi);

	/* set CP_HQD_PQ_CONTROL */
	WREG32_SOC15(GC, 0, mmCP_HQD_PQ_CONTROL, mqd->cp_hqd_pq_control);

	/* set CP_HQD_PQ_WPTR_POLL_ADDR/HI */
	WREG32_SOC15(GC, 0, mmCP_HQD_PQ_WPTR_POLL_ADDR,
		     mqd->cp_hqd_pq_wptr_poll_addr_lo);
	WREG32_SOC15(GC, 0, mmCP_HQD_PQ_WPTR_POLL_ADDR_HI,
		     mqd->cp_hqd_pq_wptr_poll_addr_hi);

	/* set CP_HQD_PQ_DOORBELL_CONTROL */
	WREG32_SOC15(GC, 0, mmCP_HQD_PQ_DOORBELL_CONTROL,
		     mqd->cp_hqd_pq_करोorbell_control);

	/* set CP_HQD_PERSISTENT_STATE.PRELOAD_SIZE=0x53 */
	WREG32_SOC15(GC, 0, mmCP_HQD_PERSISTENT_STATE, mqd->cp_hqd_persistent_state);

	/* set CP_HQD_ACTIVE.ACTIVE=1 */
	WREG32_SOC15(GC, 0, mmCP_HQD_ACTIVE, mqd->cp_hqd_active);

	nv_grbm_select(adev, 0, 0, 0, 0);
	mutex_unlock(&adev->srbm_mutex);
पूर्ण

#अगर 0
अटल पूर्णांक mes_v10_1_kiq_enable_queue(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_kiq *kiq = &adev->gfx.kiq;
	काष्ठा amdgpu_ring *kiq_ring = &adev->gfx.kiq.ring;
	पूर्णांक r;

	अगर (!kiq->pmf || !kiq->pmf->kiq_map_queues)
		वापस -EINVAL;

	r = amdgpu_ring_alloc(kiq_ring, kiq->pmf->map_queues_size);
	अगर (r) अणु
		DRM_ERROR("Failed to lock KIQ (%d).\n", r);
		वापस r;
	पूर्ण

	kiq->pmf->kiq_map_queues(kiq_ring, &adev->mes.ring);

	r = amdgpu_ring_test_ring(kiq_ring);
	अगर (r) अणु
		DRM_ERROR("kfq enable failed\n");
		kiq_ring->sched.पढ़ोy = false;
	पूर्ण
	वापस r;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mes_v10_1_queue_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	r = mes_v10_1_mqd_init(&adev->mes.ring);
	अगर (r)
		वापस r;

#अगर 0
	r = mes_v10_1_kiq_enable_queue(adev);
	अगर (r)
		वापस r;
#अन्यथा
	mes_v10_1_queue_init_रेजिस्टर(&adev->mes.ring);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक mes_v10_1_ring_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;

	ring = &adev->mes.ring;

	ring->funcs = &mes_v10_1_ring_funcs;

	ring->me = 3;
	ring->pipe = 0;
	ring->queue = 0;

	ring->ring_obj = शून्य;
	ring->use_करोorbell = true;
	ring->करोorbell_index = adev->करोorbell_index.mes_ring << 1;
	ring->eop_gpu_addr = adev->mes.eop_gpu_addr;
	ring->no_scheduler = true;
	प्र_लिखो(ring->name, "mes_%d.%d.%d", ring->me, ring->pipe, ring->queue);

	वापस amdgpu_ring_init(adev, ring, 1024, शून्य, 0,
				AMDGPU_RING_PRIO_DEFAULT, शून्य);
पूर्ण

अटल पूर्णांक mes_v10_1_mqd_sw_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r, mqd_size = माप(काष्ठा v10_compute_mqd);
	काष्ठा amdgpu_ring *ring = &adev->mes.ring;

	अगर (ring->mqd_obj)
		वापस 0;

	r = amdgpu_bo_create_kernel(adev, mqd_size, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_GTT, &ring->mqd_obj,
				    &ring->mqd_gpu_addr, &ring->mqd_ptr);
	अगर (r) अणु
		dev_warn(adev->dev, "failed to create ring mqd bo (%d)", r);
		वापस r;
	पूर्ण

	/* prepare MQD backup */
	adev->mes.mqd_backup = kदो_स्मृति(mqd_size, GFP_KERNEL);
	अगर (!adev->mes.mqd_backup)
		dev_warn(adev->dev,
			 "no memory to create MQD backup for ring %s\n",
			 ring->name);

	वापस 0;
पूर्ण

अटल पूर्णांक mes_v10_1_sw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->mes.adev = adev;
	adev->mes.funcs = &mes_v10_1_funcs;

	r = mes_v10_1_init_microcode(adev);
	अगर (r)
		वापस r;

	r = mes_v10_1_allocate_eop_buf(adev);
	अगर (r)
		वापस r;

	r = mes_v10_1_mqd_sw_init(adev);
	अगर (r)
		वापस r;

	r = mes_v10_1_ring_init(adev);
	अगर (r)
		वापस r;

	r = mes_v10_1_allocate_mem_slots(adev);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक mes_v10_1_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_device_wb_मुक्त(adev, adev->mes.sch_ctx_offs);
	amdgpu_device_wb_मुक्त(adev, adev->mes.query_status_fence_offs);

	kमुक्त(adev->mes.mqd_backup);

	amdgpu_bo_मुक्त_kernel(&adev->mes.ring.mqd_obj,
			      &adev->mes.ring.mqd_gpu_addr,
			      &adev->mes.ring.mqd_ptr);

	amdgpu_bo_मुक्त_kernel(&adev->mes.eop_gpu_obj,
			      &adev->mes.eop_gpu_addr,
			      शून्य);

	mes_v10_1_मुक्त_microcode(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक mes_v10_1_hw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_सूचीECT) अणु
		r = mes_v10_1_load_microcode(adev);
		अगर (r) अणु
			DRM_ERROR("failed to MES fw, r=%d\n", r);
			वापस r;
		पूर्ण
	पूर्ण

	mes_v10_1_enable(adev, true);

	r = mes_v10_1_queue_init(adev);
	अगर (r)
		जाओ failure;

	r = mes_v10_1_set_hw_resources(&adev->mes);
	अगर (r)
		जाओ failure;

	r = mes_v10_1_query_sched_status(&adev->mes);
	अगर (r) अणु
		DRM_ERROR("MES is busy\n");
		जाओ failure;
	पूर्ण

	वापस 0;

failure:
	mes_v10_1_hw_fini(adev);
	वापस r;
पूर्ण

अटल पूर्णांक mes_v10_1_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	mes_v10_1_enable(adev, false);

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_सूचीECT)
		mes_v10_1_मुक्त_ucode_buffers(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक mes_v10_1_suspend(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक mes_v10_1_resume(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs mes_v10_1_ip_funcs = अणु
	.name = "mes_v10_1",
	.sw_init = mes_v10_1_sw_init,
	.sw_fini = mes_v10_1_sw_fini,
	.hw_init = mes_v10_1_hw_init,
	.hw_fini = mes_v10_1_hw_fini,
	.suspend = mes_v10_1_suspend,
	.resume = mes_v10_1_resume,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version mes_v10_1_ip_block = अणु
	.type = AMD_IP_BLOCK_TYPE_MES,
	.major = 10,
	.minor = 1,
	.rev = 0,
	.funcs = &mes_v10_1_ip_funcs,
पूर्ण;
