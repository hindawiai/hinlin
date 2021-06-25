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
#समावेश <linux/pci.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_atomfirmware.h"
#समावेश "gmc_v10_0.h"
#समावेश "umc_v8_7.h"

#समावेश "athub/athub_2_0_0_sh_mask.h"
#समावेश "athub/athub_2_0_0_offset.h"
#समावेश "dcn/dcn_2_0_0_offset.h"
#समावेश "dcn/dcn_2_0_0_sh_mask.h"
#समावेश "oss/osssys_5_0_0_offset.h"
#समावेश "ivsrcid/vmc/irqsrcs_vmc_1_0.h"
#समावेश "navi10_enum.h"

#समावेश "soc15.h"
#समावेश "soc15d.h"
#समावेश "soc15_common.h"

#समावेश "nbio_v2_3.h"

#समावेश "gfxhub_v2_0.h"
#समावेश "gfxhub_v2_1.h"
#समावेश "mmhub_v2_0.h"
#समावेश "mmhub_v2_3.h"
#समावेश "athub_v2_0.h"
#समावेश "athub_v2_1.h"

#अगर 0
अटल स्थिर काष्ठा soc15_reg_golden golden_settings_navi10_hdp[] =
अणु
	/* TODO add golden setting क्रम hdp */
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक gmc_v10_0_ecc_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					 काष्ठा amdgpu_irq_src *src,
					 अचिन्हित type,
					 क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
gmc_v10_0_vm_fault_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
				   काष्ठा amdgpu_irq_src *src, अचिन्हित type,
				   क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	चयन (state) अणु
	हाल AMDGPU_IRQ_STATE_DISABLE:
		/* MM HUB */
		amdgpu_gmc_set_vm_fault_masks(adev, AMDGPU_MMHUB_0, false);
		/* GFX HUB */
		amdgpu_gmc_set_vm_fault_masks(adev, AMDGPU_GFXHUB_0, false);
		अवरोध;
	हाल AMDGPU_IRQ_STATE_ENABLE:
		/* MM HUB */
		amdgpu_gmc_set_vm_fault_masks(adev, AMDGPU_MMHUB_0, true);
		/* GFX HUB */
		amdgpu_gmc_set_vm_fault_masks(adev, AMDGPU_GFXHUB_0, true);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v10_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				       काष्ठा amdgpu_irq_src *source,
				       काष्ठा amdgpu_iv_entry *entry)
अणु
	bool retry_fault = !!(entry->src_data[1] & 0x80);
	काष्ठा amdgpu_vmhub *hub = &adev->vmhub[entry->vmid_src];
	काष्ठा amdgpu_task_info task_info;
	uपूर्णांक32_t status = 0;
	u64 addr;

	addr = (u64)entry->src_data[0] << 12;
	addr |= ((u64)entry->src_data[1] & 0xf) << 44;

	अगर (retry_fault) अणु
		/* Returning 1 here also prevents sending the IV to the KFD */

		/* Process it onyl अगर it's the first fault क्रम this address */
		अगर (entry->ih != &adev->irq.ih_soft &&
		    amdgpu_gmc_filter_faults(adev, addr, entry->pasid,
					     entry->बारtamp))
			वापस 1;

		/* Delegate it to a dअगरferent ring अगर the hardware hasn't
		 * alपढ़ोy करोne it.
		 */
		अगर (entry->ih == &adev->irq.ih) अणु
			amdgpu_irq_delegate(adev, entry, 8);
			वापस 1;
		पूर्ण

		/* Try to handle the recoverable page faults by filling page
		 * tables
		 */
		अगर (amdgpu_vm_handle_fault(adev, entry->pasid, addr))
			वापस 1;
	पूर्ण

	अगर (!amdgpu_sriov_vf(adev)) अणु
		/*
		 * Issue a dummy पढ़ो to रुको क्रम the status रेजिस्टर to
		 * be updated to aव्योम पढ़ोing an incorrect value due to
		 * the new fast GRBM पूर्णांकerface.
		 */
		अगर ((entry->vmid_src == AMDGPU_GFXHUB_0) &&
		    (adev->asic_type < CHIP_SIENNA_CICHLID))
			RREG32(hub->vm_l2_pro_fault_status);

		status = RREG32(hub->vm_l2_pro_fault_status);
		WREG32_P(hub->vm_l2_pro_fault_cntl, 1, ~1);
	पूर्ण

	अगर (!prपूर्णांकk_ratelimit())
		वापस 0;

	स_रखो(&task_info, 0, माप(काष्ठा amdgpu_task_info));
	amdgpu_vm_get_task_info(adev, entry->pasid, &task_info);

	dev_err(adev->dev,
		"[%s] page fault (src_id:%u ring:%u vmid:%u pasid:%u, "
		"for process %s pid %d thread %s pid %d)\n",
		entry->vmid_src ? "mmhub" : "gfxhub",
		entry->src_id, entry->ring_id, entry->vmid,
		entry->pasid, task_info.process_name, task_info.tgid,
		task_info.task_name, task_info.pid);
	dev_err(adev->dev, "  in page starting at address 0x%016llx from client 0x%x (%s)\n",
		addr, entry->client_id,
		soc15_ih_clientid_name[entry->client_id]);

	अगर (!amdgpu_sriov_vf(adev))
		hub->vmhub_funcs->prपूर्णांक_l2_protection_fault_status(adev,
								   status);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs gmc_v10_0_irq_funcs = अणु
	.set = gmc_v10_0_vm_fault_पूर्णांकerrupt_state,
	.process = gmc_v10_0_process_पूर्णांकerrupt,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_irq_src_funcs gmc_v10_0_ecc_funcs = अणु
	.set = gmc_v10_0_ecc_पूर्णांकerrupt_state,
	.process = amdgpu_umc_process_ecc_irq,
पूर्ण;

अटल व्योम gmc_v10_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->gmc.vm_fault.num_types = 1;
	adev->gmc.vm_fault.funcs = &gmc_v10_0_irq_funcs;

	अगर (!amdgpu_sriov_vf(adev)) अणु
		adev->gmc.ecc_irq.num_types = 1;
		adev->gmc.ecc_irq.funcs = &gmc_v10_0_ecc_funcs;
	पूर्ण
पूर्ण

/**
 * gmc_v10_0_use_invalidate_semaphore - judge whether to use semaphore
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vmhub: vmhub type
 *
 */
अटल bool gmc_v10_0_use_invalidate_semaphore(काष्ठा amdgpu_device *adev,
				       uपूर्णांक32_t vmhub)
अणु
	वापस ((vmhub == AMDGPU_MMHUB_0 ||
		 vmhub == AMDGPU_MMHUB_1) &&
		(!amdgpu_sriov_vf(adev)));
पूर्ण

अटल bool gmc_v10_0_get_atc_vmid_pasid_mapping_info(
					काष्ठा amdgpu_device *adev,
					uपूर्णांक8_t vmid, uपूर्णांक16_t *p_pasid)
अणु
	uपूर्णांक32_t value;

	value = RREG32(SOC15_REG_OFFSET(ATHUB, 0, mmATC_VMID0_PASID_MAPPING)
		     + vmid);
	*p_pasid = value & ATC_VMID0_PASID_MAPPING__PASID_MASK;

	वापस !!(value & ATC_VMID0_PASID_MAPPING__VALID_MASK);
पूर्ण

/*
 * GART
 * VMID 0 is the physical GPU addresses as used by the kernel.
 * VMIDs 1-15 are used क्रम userspace clients and are handled
 * by the amdgpu vm/hsa code.
 */

अटल व्योम gmc_v10_0_flush_vm_hub(काष्ठा amdgpu_device *adev, uपूर्णांक32_t vmid,
				   अचिन्हित पूर्णांक vmhub, uपूर्णांक32_t flush_type)
अणु
	bool use_semaphore = gmc_v10_0_use_invalidate_semaphore(adev, vmhub);
	काष्ठा amdgpu_vmhub *hub = &adev->vmhub[vmhub];
	u32 inv_req = hub->vmhub_funcs->get_invalidate_req(vmid, flush_type);
	u32 पंचांगp;
	/* Use रेजिस्टर 17 क्रम GART */
	स्थिर अचिन्हित eng = 17;
	अचिन्हित पूर्णांक i;

	spin_lock(&adev->gmc.invalidate_lock);
	/*
	 * It may lose gpuvm invalidate acknowldege state across घातer-gating
	 * off cycle, add semaphore acquire beक्रमe invalidation and semaphore
	 * release after invalidation to aव्योम entering घातer gated state
	 * to WA the Issue
	 */

	/* TODO: It needs to जारी working on debugging with semaphore क्रम GFXHUB as well. */
	अगर (use_semaphore) अणु
		क्रम (i = 0; i < adev->usec_समयout; i++) अणु
			/* a पढ़ो वापस value of 1 means semaphore acuqire */
			पंचांगp = RREG32_NO_KIQ(hub->vm_inv_eng0_sem +
					    hub->eng_distance * eng);
			अगर (पंचांगp & 0x1)
				अवरोध;
			udelay(1);
		पूर्ण

		अगर (i >= adev->usec_समयout)
			DRM_ERROR("Timeout waiting for sem acquire in VM flush!\n");
	पूर्ण

	WREG32_NO_KIQ(hub->vm_inv_eng0_req + hub->eng_distance * eng, inv_req);

	/*
	 * Issue a dummy पढ़ो to रुको क्रम the ACK रेजिस्टर to be cleared
	 * to aव्योम a false ACK due to the new fast GRBM पूर्णांकerface.
	 */
	अगर ((vmhub == AMDGPU_GFXHUB_0) &&
	    (adev->asic_type < CHIP_SIENNA_CICHLID))
		RREG32_NO_KIQ(hub->vm_inv_eng0_req + hub->eng_distance * eng);

	/* Wait क्रम ACK with a delay.*/
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		पंचांगp = RREG32_NO_KIQ(hub->vm_inv_eng0_ack +
				    hub->eng_distance * eng);
		पंचांगp &= 1 << vmid;
		अगर (पंचांगp)
			अवरोध;

		udelay(1);
	पूर्ण

	/* TODO: It needs to जारी working on debugging with semaphore क्रम GFXHUB as well. */
	अगर (use_semaphore)
		/*
		 * add semaphore release after invalidation,
		 * ग_लिखो with 0 means semaphore release
		 */
		WREG32_NO_KIQ(hub->vm_inv_eng0_sem +
			      hub->eng_distance * eng, 0);

	spin_unlock(&adev->gmc.invalidate_lock);

	अगर (i < adev->usec_समयout)
		वापस;

	DRM_ERROR("Timeout waiting for VM flush ACK!\n");
पूर्ण

/**
 * gmc_v10_0_flush_gpu_tlb - gart tlb flush callback
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vmid: vm instance to flush
 * @vmhub: vmhub type
 * @flush_type: the flush type
 *
 * Flush the TLB क्रम the requested page table.
 */
अटल व्योम gmc_v10_0_flush_gpu_tlb(काष्ठा amdgpu_device *adev, uपूर्णांक32_t vmid,
					uपूर्णांक32_t vmhub, uपूर्णांक32_t flush_type)
अणु
	काष्ठा amdgpu_ring *ring = adev->mman.buffer_funcs_ring;
	काष्ठा dma_fence *fence;
	काष्ठा amdgpu_job *job;

	पूर्णांक r;

	/* flush hdp cache */
	adev->hdp.funcs->flush_hdp(adev, शून्य);

	/* For SRIOV run समय, driver shouldn't access the रेजिस्टर through MMIO
	 * Directly use kiq to करो the vm invalidation instead
	 */
	अगर (adev->gfx.kiq.ring.sched.पढ़ोy &&
	    (amdgpu_sriov_runसमय(adev) || !amdgpu_sriov_vf(adev)) &&
	    करोwn_पढ़ो_trylock(&adev->reset_sem)) अणु
		काष्ठा amdgpu_vmhub *hub = &adev->vmhub[vmhub];
		स्थिर अचिन्हित eng = 17;
		u32 inv_req = hub->vmhub_funcs->get_invalidate_req(vmid, flush_type);
		u32 req = hub->vm_inv_eng0_req + hub->eng_distance * eng;
		u32 ack = hub->vm_inv_eng0_ack + hub->eng_distance * eng;

		amdgpu_virt_kiq_reg_ग_लिखो_reg_रुको(adev, req, ack, inv_req,
				1 << vmid);

		up_पढ़ो(&adev->reset_sem);
		वापस;
	पूर्ण

	mutex_lock(&adev->mman.gtt_winकरोw_lock);

	अगर (vmhub == AMDGPU_MMHUB_0) अणु
		gmc_v10_0_flush_vm_hub(adev, vmid, AMDGPU_MMHUB_0, 0);
		mutex_unlock(&adev->mman.gtt_winकरोw_lock);
		वापस;
	पूर्ण

	BUG_ON(vmhub != AMDGPU_GFXHUB_0);

	अगर (!adev->mman.buffer_funcs_enabled ||
	    !adev->ib_pool_पढ़ोy ||
	    amdgpu_in_reset(adev) ||
	    ring->sched.पढ़ोy == false) अणु
		gmc_v10_0_flush_vm_hub(adev, vmid, AMDGPU_GFXHUB_0, 0);
		mutex_unlock(&adev->mman.gtt_winकरोw_lock);
		वापस;
	पूर्ण

	/* The SDMA on Navi has a bug which can theoretically result in memory
	 * corruption अगर an invalidation happens at the same समय as an VA
	 * translation. Aव्योम this by करोing the invalidation from the SDMA
	 * itself.
	 */
	r = amdgpu_job_alloc_with_ib(adev, 16 * 4, AMDGPU_IB_POOL_IMMEDIATE,
				     &job);
	अगर (r)
		जाओ error_alloc;

	job->vm_pd_addr = amdgpu_gmc_pd_addr(adev->gart.bo);
	job->vm_needs_flush = true;
	job->ibs->ptr[job->ibs->length_dw++] = ring->funcs->nop;
	amdgpu_ring_pad_ib(ring, &job->ibs[0]);
	r = amdgpu_job_submit(job, &adev->mman.entity,
			      AMDGPU_FENCE_OWNER_UNDEFINED, &fence);
	अगर (r)
		जाओ error_submit;

	mutex_unlock(&adev->mman.gtt_winकरोw_lock);

	dma_fence_रुको(fence, false);
	dma_fence_put(fence);

	वापस;

error_submit:
	amdgpu_job_मुक्त(job);

error_alloc:
	mutex_unlock(&adev->mman.gtt_winकरोw_lock);
	DRM_ERROR("Error flushing GPU TLB using the SDMA (%d)!\n", r);
पूर्ण

/**
 * gmc_v10_0_flush_gpu_tlb_pasid - tlb flush via pasid
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @pasid: pasid to be flush
 * @flush_type: the flush type
 * @all_hub: Used with PACKET3_INVALIDATE_TLBS_ALL_HUB()
 *
 * Flush the TLB क्रम the requested pasid.
 */
अटल पूर्णांक gmc_v10_0_flush_gpu_tlb_pasid(काष्ठा amdgpu_device *adev,
					uपूर्णांक16_t pasid, uपूर्णांक32_t flush_type,
					bool all_hub)
अणु
	पूर्णांक vmid, i;
	चिन्हित दीर्घ r;
	uपूर्णांक32_t seq;
	uपूर्णांक16_t queried_pasid;
	bool ret;
	काष्ठा amdgpu_ring *ring = &adev->gfx.kiq.ring;
	काष्ठा amdgpu_kiq *kiq = &adev->gfx.kiq;

	अगर (amdgpu_emu_mode == 0 && ring->sched.पढ़ोy) अणु
		spin_lock(&adev->gfx.kiq.ring_lock);
		/* 2 dwords flush + 8 dwords fence */
		amdgpu_ring_alloc(ring, kiq->pmf->invalidate_tlbs_size + 8);
		kiq->pmf->kiq_invalidate_tlbs(ring,
					pasid, flush_type, all_hub);
		r = amdgpu_fence_emit_polling(ring, &seq, MAX_KIQ_REG_WAIT);
		अगर (r) अणु
			amdgpu_ring_unकरो(ring);
			spin_unlock(&adev->gfx.kiq.ring_lock);
			वापस -ETIME;
		पूर्ण

		amdgpu_ring_commit(ring);
		spin_unlock(&adev->gfx.kiq.ring_lock);
		r = amdgpu_fence_रुको_polling(ring, seq, adev->usec_समयout);
		अगर (r < 1) अणु
			dev_err(adev->dev, "wait for kiq fence error: %ld.\n", r);
			वापस -ETIME;
		पूर्ण

		वापस 0;
	पूर्ण

	क्रम (vmid = 1; vmid < AMDGPU_NUM_VMID; vmid++) अणु

		ret = gmc_v10_0_get_atc_vmid_pasid_mapping_info(adev, vmid,
				&queried_pasid);
		अगर (ret	&& queried_pasid == pasid) अणु
			अगर (all_hub) अणु
				क्रम (i = 0; i < adev->num_vmhubs; i++)
					gmc_v10_0_flush_gpu_tlb(adev, vmid,
							i, flush_type);
			पूर्ण अन्यथा अणु
				gmc_v10_0_flush_gpu_tlb(adev, vmid,
						AMDGPU_GFXHUB_0, flush_type);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल uपूर्णांक64_t gmc_v10_0_emit_flush_gpu_tlb(काष्ठा amdgpu_ring *ring,
					     अचिन्हित vmid, uपूर्णांक64_t pd_addr)
अणु
	bool use_semaphore = gmc_v10_0_use_invalidate_semaphore(ring->adev, ring->funcs->vmhub);
	काष्ठा amdgpu_vmhub *hub = &ring->adev->vmhub[ring->funcs->vmhub];
	uपूर्णांक32_t req = hub->vmhub_funcs->get_invalidate_req(vmid, 0);
	अचिन्हित eng = ring->vm_inv_eng;

	/*
	 * It may lose gpuvm invalidate acknowldege state across घातer-gating
	 * off cycle, add semaphore acquire beक्रमe invalidation and semaphore
	 * release after invalidation to aव्योम entering घातer gated state
	 * to WA the Issue
	 */

	/* TODO: It needs to जारी working on debugging with semaphore क्रम GFXHUB as well. */
	अगर (use_semaphore)
		/* a पढ़ो वापस value of 1 means semaphore acuqire */
		amdgpu_ring_emit_reg_रुको(ring,
					  hub->vm_inv_eng0_sem +
					  hub->eng_distance * eng, 0x1, 0x1);

	amdgpu_ring_emit_wreg(ring, hub->ctx0_ptb_addr_lo32 +
			      (hub->ctx_addr_distance * vmid),
			      lower_32_bits(pd_addr));

	amdgpu_ring_emit_wreg(ring, hub->ctx0_ptb_addr_hi32 +
			      (hub->ctx_addr_distance * vmid),
			      upper_32_bits(pd_addr));

	amdgpu_ring_emit_reg_ग_लिखो_reg_रुको(ring, hub->vm_inv_eng0_req +
					    hub->eng_distance * eng,
					    hub->vm_inv_eng0_ack +
					    hub->eng_distance * eng,
					    req, 1 << vmid);

	/* TODO: It needs to जारी working on debugging with semaphore क्रम GFXHUB as well. */
	अगर (use_semaphore)
		/*
		 * add semaphore release after invalidation,
		 * ग_लिखो with 0 means semaphore release
		 */
		amdgpu_ring_emit_wreg(ring, hub->vm_inv_eng0_sem +
				      hub->eng_distance * eng, 0);

	वापस pd_addr;
पूर्ण

अटल व्योम gmc_v10_0_emit_pasid_mapping(काष्ठा amdgpu_ring *ring, अचिन्हित vmid,
					 अचिन्हित pasid)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t reg;

	अगर (ring->funcs->vmhub == AMDGPU_GFXHUB_0)
		reg = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_VMID_0_LUT) + vmid;
	अन्यथा
		reg = SOC15_REG_OFFSET(OSSSYS, 0, mmIH_VMID_0_LUT_MM) + vmid;

	amdgpu_ring_emit_wreg(ring, reg, pasid);
पूर्ण

/*
 * PTE क्रमmat on NAVI 10:
 * 63:59 reserved
 * 58 reserved and क्रम sienna_cichlid is used क्रम MALL noalloc
 * 57 reserved
 * 56 F
 * 55 L
 * 54 reserved
 * 53:52 SW
 * 51 T
 * 50:48 mtype
 * 47:12 4k physical page base address
 * 11:7 fragment
 * 6 ग_लिखो
 * 5 पढ़ो
 * 4 exe
 * 3 Z
 * 2 snooped
 * 1 प्रणाली
 * 0 valid
 *
 * PDE क्रमmat on NAVI 10:
 * 63:59 block fragment size
 * 58:55 reserved
 * 54 P
 * 53:48 reserved
 * 47:6 physical base address of PD or PTE
 * 5:3 reserved
 * 2 C
 * 1 प्रणाली
 * 0 valid
 */

अटल uपूर्णांक64_t gmc_v10_0_map_mtype(काष्ठा amdgpu_device *adev, uपूर्णांक32_t flags)
अणु
	चयन (flags) अणु
	हाल AMDGPU_VM_MTYPE_DEFAULT:
		वापस AMDGPU_PTE_MTYPE_NV10(MTYPE_NC);
	हाल AMDGPU_VM_MTYPE_NC:
		वापस AMDGPU_PTE_MTYPE_NV10(MTYPE_NC);
	हाल AMDGPU_VM_MTYPE_WC:
		वापस AMDGPU_PTE_MTYPE_NV10(MTYPE_WC);
	हाल AMDGPU_VM_MTYPE_CC:
		वापस AMDGPU_PTE_MTYPE_NV10(MTYPE_CC);
	हाल AMDGPU_VM_MTYPE_UC:
		वापस AMDGPU_PTE_MTYPE_NV10(MTYPE_UC);
	शेष:
		वापस AMDGPU_PTE_MTYPE_NV10(MTYPE_NC);
	पूर्ण
पूर्ण

अटल व्योम gmc_v10_0_get_vm_pde(काष्ठा amdgpu_device *adev, पूर्णांक level,
				 uपूर्णांक64_t *addr, uपूर्णांक64_t *flags)
अणु
	अगर (!(*flags & AMDGPU_PDE_PTE) && !(*flags & AMDGPU_PTE_SYSTEM))
		*addr = amdgpu_gmc_vram_mc2pa(adev, *addr);
	BUG_ON(*addr & 0xFFFF00000000003FULL);

	अगर (!adev->gmc.translate_further)
		वापस;

	अगर (level == AMDGPU_VM_PDB1) अणु
		/* Set the block fragment size */
		अगर (!(*flags & AMDGPU_PDE_PTE))
			*flags |= AMDGPU_PDE_BFS(0x9);

	पूर्ण अन्यथा अगर (level == AMDGPU_VM_PDB0) अणु
		अगर (*flags & AMDGPU_PDE_PTE)
			*flags &= ~AMDGPU_PDE_PTE;
		अन्यथा
			*flags |= AMDGPU_PTE_TF;
	पूर्ण
पूर्ण

अटल व्योम gmc_v10_0_get_vm_pte(काष्ठा amdgpu_device *adev,
				 काष्ठा amdgpu_bo_va_mapping *mapping,
				 uपूर्णांक64_t *flags)
अणु
	*flags &= ~AMDGPU_PTE_EXECUTABLE;
	*flags |= mapping->flags & AMDGPU_PTE_EXECUTABLE;

	*flags &= ~AMDGPU_PTE_MTYPE_NV10_MASK;
	*flags |= (mapping->flags & AMDGPU_PTE_MTYPE_NV10_MASK);

	अगर (mapping->flags & AMDGPU_PTE_PRT) अणु
		*flags |= AMDGPU_PTE_PRT;
		*flags |= AMDGPU_PTE_SNOOPED;
		*flags |= AMDGPU_PTE_LOG;
		*flags |= AMDGPU_PTE_SYSTEM;
		*flags &= ~AMDGPU_PTE_VALID;
	पूर्ण
पूर्ण

अटल अचिन्हित gmc_v10_0_get_vbios_fb_size(काष्ठा amdgpu_device *adev)
अणु
	u32 d1vga_control = RREG32_SOC15(DCE, 0, mmD1VGA_CONTROL);
	अचिन्हित size;

	अगर (REG_GET_FIELD(d1vga_control, D1VGA_CONTROL, D1VGA_MODE_ENABLE)) अणु
		size = AMDGPU_VBIOS_VGA_ALLOCATION;
	पूर्ण अन्यथा अणु
		u32 viewport;
		u32 pitch;

		viewport = RREG32_SOC15(DCE, 0, mmHUBP0_DCSURF_PRI_VIEWPORT_DIMENSION);
		pitch = RREG32_SOC15(DCE, 0, mmHUBPREQ0_DCSURF_SURFACE_PITCH);
		size = (REG_GET_FIELD(viewport,
					HUBP0_DCSURF_PRI_VIEWPORT_DIMENSION, PRI_VIEWPORT_HEIGHT) *
				REG_GET_FIELD(pitch, HUBPREQ0_DCSURF_SURFACE_PITCH, PITCH) *
				4);
	पूर्ण

	वापस size;
पूर्ण

अटल स्थिर काष्ठा amdgpu_gmc_funcs gmc_v10_0_gmc_funcs = अणु
	.flush_gpu_tlb = gmc_v10_0_flush_gpu_tlb,
	.flush_gpu_tlb_pasid = gmc_v10_0_flush_gpu_tlb_pasid,
	.emit_flush_gpu_tlb = gmc_v10_0_emit_flush_gpu_tlb,
	.emit_pasid_mapping = gmc_v10_0_emit_pasid_mapping,
	.map_mtype = gmc_v10_0_map_mtype,
	.get_vm_pde = gmc_v10_0_get_vm_pde,
	.get_vm_pte = gmc_v10_0_get_vm_pte,
	.get_vbios_fb_size = gmc_v10_0_get_vbios_fb_size,
पूर्ण;

अटल व्योम gmc_v10_0_set_gmc_funcs(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->gmc.gmc_funcs == शून्य)
		adev->gmc.gmc_funcs = &gmc_v10_0_gmc_funcs;
पूर्ण

अटल व्योम gmc_v10_0_set_umc_funcs(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_SIENNA_CICHLID:
		adev->umc.max_ras_err_cnt_per_query = UMC_V8_7_TOTAL_CHANNEL_NUM;
		adev->umc.channel_inst_num = UMC_V8_7_CHANNEL_INSTANCE_NUM;
		adev->umc.umc_inst_num = UMC_V8_7_UMC_INSTANCE_NUM;
		adev->umc.channel_offs = UMC_V8_7_PER_CHANNEL_OFFSET_SIENNA;
		adev->umc.channel_idx_tbl = &umc_v8_7_channel_idx_tbl[0][0];
		adev->umc.ras_funcs = &umc_v8_7_ras_funcs;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण


अटल व्योम gmc_v10_0_set_mmhub_funcs(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_VANGOGH:
		adev->mmhub.funcs = &mmhub_v2_3_funcs;
		अवरोध;
	शेष:
		adev->mmhub.funcs = &mmhub_v2_0_funcs;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम gmc_v10_0_set_gfxhub_funcs(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_VANGOGH:
	हाल CHIP_DIMGREY_CAVEFISH:
		adev->gfxhub.funcs = &gfxhub_v2_1_funcs;
		अवरोध;
	शेष:
		adev->gfxhub.funcs = &gfxhub_v2_0_funcs;
		अवरोध;
	पूर्ण
पूर्ण


अटल पूर्णांक gmc_v10_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	gmc_v10_0_set_mmhub_funcs(adev);
	gmc_v10_0_set_gfxhub_funcs(adev);
	gmc_v10_0_set_gmc_funcs(adev);
	gmc_v10_0_set_irq_funcs(adev);
	gmc_v10_0_set_umc_funcs(adev);

	adev->gmc.shared_aperture_start = 0x2000000000000000ULL;
	adev->gmc.shared_aperture_end =
		adev->gmc.shared_aperture_start + (4ULL << 30) - 1;
	adev->gmc.निजी_aperture_start = 0x1000000000000000ULL;
	adev->gmc.निजी_aperture_end =
		adev->gmc.निजी_aperture_start + (4ULL << 30) - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v10_0_late_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक r;

	r = amdgpu_gmc_allocate_vm_inv_eng(adev);
	अगर (r)
		वापस r;

	r = amdgpu_gmc_ras_late_init(adev);
	अगर (r)
		वापस r;

	वापस amdgpu_irq_get(adev, &adev->gmc.vm_fault, 0);
पूर्ण

अटल व्योम gmc_v10_0_vram_gtt_location(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_gmc *mc)
अणु
	u64 base = 0;

	base = adev->gfxhub.funcs->get_fb_location(adev);

	/* add the xgmi offset of the physical node */
	base += adev->gmc.xgmi.physical_node_id * adev->gmc.xgmi.node_segment_size;

	amdgpu_gmc_vram_location(adev, &adev->gmc, base);
	amdgpu_gmc_gart_location(adev, mc);
	amdgpu_gmc_agp_location(adev, mc);

	/* base offset of vram pages */
	adev->vm_manager.vram_base_offset = adev->gfxhub.funcs->get_mc_fb_offset(adev);

	/* add the xgmi offset of the physical node */
	adev->vm_manager.vram_base_offset +=
		adev->gmc.xgmi.physical_node_id * adev->gmc.xgmi.node_segment_size;
पूर्ण

/**
 * gmc_v10_0_mc_init - initialize the memory controller driver params
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Look up the amount of vram, vram width, and decide how to place
 * vram and gart within the GPU's physical address space.
 * Returns 0 क्रम success.
 */
अटल पूर्णांक gmc_v10_0_mc_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	/* size in MB on si */
	adev->gmc.mc_vram_size =
		adev->nbio.funcs->get_memsize(adev) * 1024ULL * 1024ULL;
	adev->gmc.real_vram_size = adev->gmc.mc_vram_size;

	अगर (!(adev->flags & AMD_IS_APU)) अणु
		r = amdgpu_device_resize_fb_bar(adev);
		अगर (r)
			वापस r;
	पूर्ण
	adev->gmc.aper_base = pci_resource_start(adev->pdev, 0);
	adev->gmc.aper_size = pci_resource_len(adev->pdev, 0);

#अगर_घोषित CONFIG_X86_64
	अगर (adev->flags & AMD_IS_APU) अणु
		adev->gmc.aper_base = adev->gfxhub.funcs->get_mc_fb_offset(adev);
		adev->gmc.aper_size = adev->gmc.real_vram_size;
	पूर्ण
#पूर्ण_अगर

	/* In हाल the PCI BAR is larger than the actual amount of vram */
	adev->gmc.visible_vram_size = adev->gmc.aper_size;
	अगर (adev->gmc.visible_vram_size > adev->gmc.real_vram_size)
		adev->gmc.visible_vram_size = adev->gmc.real_vram_size;

	/* set the gart size */
	अगर (amdgpu_gart_size == -1) अणु
		चयन (adev->asic_type) अणु
		हाल CHIP_NAVI10:
		हाल CHIP_NAVI14:
		हाल CHIP_NAVI12:
		हाल CHIP_SIENNA_CICHLID:
		हाल CHIP_NAVY_FLOUNDER:
		हाल CHIP_VANGOGH:
		हाल CHIP_DIMGREY_CAVEFISH:
		शेष:
			adev->gmc.gart_size = 512ULL << 20;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		adev->gmc.gart_size = (u64)amdgpu_gart_size << 20;

	gmc_v10_0_vram_gtt_location(adev, &adev->gmc);

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v10_0_gart_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (adev->gart.bo) अणु
		WARN(1, "NAVI10 PCIE GART already initialized\n");
		वापस 0;
	पूर्ण

	/* Initialize common gart काष्ठाure */
	r = amdgpu_gart_init(adev);
	अगर (r)
		वापस r;

	adev->gart.table_size = adev->gart.num_gpu_pages * 8;
	adev->gart.gart_pte_flags = AMDGPU_PTE_MTYPE_NV10(MTYPE_UC) |
				 AMDGPU_PTE_EXECUTABLE;

	वापस amdgpu_gart_table_vram_alloc(adev);
पूर्ण

अटल पूर्णांक gmc_v10_0_sw_init(व्योम *handle)
अणु
	पूर्णांक r, vram_width = 0, vram_type = 0, vram_venकरोr = 0;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->gfxhub.funcs->init(adev);

	adev->mmhub.funcs->init(adev);

	spin_lock_init(&adev->gmc.invalidate_lock);

	अगर ((adev->flags & AMD_IS_APU) && amdgpu_emu_mode == 1) अणु
		adev->gmc.vram_type = AMDGPU_VRAM_TYPE_DDR4;
		adev->gmc.vram_width = 64;
	पूर्ण अन्यथा अगर (amdgpu_emu_mode == 1) अणु
		adev->gmc.vram_type = AMDGPU_VRAM_TYPE_GDDR6;
		adev->gmc.vram_width = 1 * 128; /* numchan * chansize */
	पूर्ण अन्यथा अणु
		r = amdgpu_atomfirmware_get_vram_info(adev,
				&vram_width, &vram_type, &vram_venकरोr);
		adev->gmc.vram_width = vram_width;

		adev->gmc.vram_type = vram_type;
		adev->gmc.vram_venकरोr = vram_venकरोr;
	पूर्ण

	चयन (adev->asic_type) अणु
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_NAVI12:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_VANGOGH:
	हाल CHIP_DIMGREY_CAVEFISH:
		adev->num_vmhubs = 2;
		/*
		 * To fulfill 4-level page support,
		 * vm size is 256TB (48bit), maximum size of Navi10/Navi14/Navi12,
		 * block size 512 (9bit)
		 */
		amdgpu_vm_adjust_size(adev, 256 * 1024, 9, 3, 48);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* This पूर्णांकerrupt is VMC page fault.*/
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_VMC,
			      VMC_1_0__SRCID__VM_FAULT,
			      &adev->gmc.vm_fault);

	अगर (r)
		वापस r;

	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_UTCL2,
			      UTCL2_1_0__SRCID__FAULT,
			      &adev->gmc.vm_fault);
	अगर (r)
		वापस r;

	अगर (!amdgpu_sriov_vf(adev)) अणु
		/* पूर्णांकerrupt sent to DF. */
		r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_DF, 0,
				      &adev->gmc.ecc_irq);
		अगर (r)
			वापस r;
	पूर्ण

	/*
	 * Set the पूर्णांकernal MC address mask This is the max address of the GPU's
	 * पूर्णांकernal address space.
	 */
	adev->gmc.mc_mask = 0xffffffffffffULL; /* 48 bit MC */

	r = dma_set_mask_and_coherent(adev->dev, DMA_BIT_MASK(44));
	अगर (r) अणु
		prपूर्णांकk(KERN_WARNING "amdgpu: No suitable DMA available.\n");
		वापस r;
	पूर्ण

	अगर (adev->gmc.xgmi.supported) अणु
		r = adev->gfxhub.funcs->get_xgmi_info(adev);
		अगर (r)
			वापस r;
	पूर्ण

	r = gmc_v10_0_mc_init(adev);
	अगर (r)
		वापस r;

	amdgpu_gmc_get_vbios_allocations(adev);

	/* Memory manager */
	r = amdgpu_bo_init(adev);
	अगर (r)
		वापस r;

	r = gmc_v10_0_gart_init(adev);
	अगर (r)
		वापस r;

	/*
	 * number of VMs
	 * VMID 0 is reserved क्रम System
	 * amdgpu graphics/compute will use VMIDs 1-7
	 * amdkfd will use VMIDs 8-15
	 */
	adev->vm_manager.first_kfd_vmid = 8;

	amdgpu_vm_manager_init(adev);

	वापस 0;
पूर्ण

/**
 * gmc_v8_0_gart_fini - vm fini callback
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Tears करोwn the driver GART/VM setup (CIK).
 */
अटल व्योम gmc_v10_0_gart_fini(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_gart_table_vram_मुक्त(adev);
	amdgpu_gart_fini(adev);
पूर्ण

अटल पूर्णांक gmc_v10_0_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_vm_manager_fini(adev);
	gmc_v10_0_gart_fini(adev);
	amdgpu_gem_क्रमce_release(adev);
	amdgpu_bo_fini(adev);

	वापस 0;
पूर्ण

अटल व्योम gmc_v10_0_init_golden_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_NAVI12:
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_VANGOGH:
	हाल CHIP_DIMGREY_CAVEFISH:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * gmc_v10_0_gart_enable - gart enable
 *
 * @adev: amdgpu_device poपूर्णांकer
 */
अटल पूर्णांक gmc_v10_0_gart_enable(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;
	bool value;

	अगर (adev->gart.bo == शून्य) अणु
		dev_err(adev->dev, "No VRAM object for PCIE GART.\n");
		वापस -EINVAL;
	पूर्ण

	r = amdgpu_gart_table_vram_pin(adev);
	अगर (r)
		वापस r;

	r = adev->gfxhub.funcs->gart_enable(adev);
	अगर (r)
		वापस r;

	r = adev->mmhub.funcs->gart_enable(adev);
	अगर (r)
		वापस r;

	adev->hdp.funcs->init_रेजिस्टरs(adev);

	/* Flush HDP after it is initialized */
	adev->hdp.funcs->flush_hdp(adev, शून्य);

	value = (amdgpu_vm_fault_stop == AMDGPU_VM_FAULT_STOP_ALWAYS) ?
		false : true;

	adev->gfxhub.funcs->set_fault_enable_शेष(adev, value);
	adev->mmhub.funcs->set_fault_enable_शेष(adev, value);
	gmc_v10_0_flush_gpu_tlb(adev, 0, AMDGPU_MMHUB_0, 0);
	gmc_v10_0_flush_gpu_tlb(adev, 0, AMDGPU_GFXHUB_0, 0);

	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (अचिन्हित)(adev->gmc.gart_size >> 20),
		 (अचिन्हित दीर्घ दीर्घ)amdgpu_bo_gpu_offset(adev->gart.bo));

	adev->gart.पढ़ोy = true;

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v10_0_hw_init(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* The sequence of these two function calls matters.*/
	gmc_v10_0_init_golden_रेजिस्टरs(adev);

	r = gmc_v10_0_gart_enable(adev);
	अगर (r)
		वापस r;

	अगर (adev->umc.funcs && adev->umc.funcs->init_रेजिस्टरs)
		adev->umc.funcs->init_रेजिस्टरs(adev);

	वापस 0;
पूर्ण

/**
 * gmc_v10_0_gart_disable - gart disable
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * This disables all VM page table.
 */
अटल व्योम gmc_v10_0_gart_disable(काष्ठा amdgpu_device *adev)
अणु
	adev->gfxhub.funcs->gart_disable(adev);
	adev->mmhub.funcs->gart_disable(adev);
	amdgpu_gart_table_vram_unpin(adev);
पूर्ण

अटल पूर्णांक gmc_v10_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (amdgpu_sriov_vf(adev)) अणु
		/* full access mode, so करोn't touch any GMC रेजिस्टर */
		DRM_DEBUG("For SRIOV client, shouldn't do anything.\n");
		वापस 0;
	पूर्ण

	amdgpu_irq_put(adev, &adev->gmc.ecc_irq, 0);
	amdgpu_irq_put(adev, &adev->gmc.vm_fault, 0);
	gmc_v10_0_gart_disable(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v10_0_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	gmc_v10_0_hw_fini(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v10_0_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = gmc_v10_0_hw_init(adev);
	अगर (r)
		वापस r;

	amdgpu_vmid_reset_all(adev);

	वापस 0;
पूर्ण

अटल bool gmc_v10_0_is_idle(व्योम *handle)
अणु
	/* MC is always पढ़ोy in GMC v10.*/
	वापस true;
पूर्ण

अटल पूर्णांक gmc_v10_0_रुको_क्रम_idle(व्योम *handle)
अणु
	/* There is no need to रुको क्रम MC idle in GMC v10.*/
	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v10_0_soft_reset(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक gmc_v10_0_set_घड़ीgating_state(व्योम *handle,
					   क्रमागत amd_घड़ीgating_state state)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = adev->mmhub.funcs->set_घड़ीgating(adev, state);
	अगर (r)
		वापस r;

	अगर (adev->asic_type >= CHIP_SIENNA_CICHLID &&
	    adev->asic_type <= CHIP_DIMGREY_CAVEFISH)
		वापस athub_v2_1_set_घड़ीgating(adev, state);
	अन्यथा
		वापस athub_v2_0_set_घड़ीgating(adev, state);
पूर्ण

अटल व्योम gmc_v10_0_get_घड़ीgating_state(व्योम *handle, u32 *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->mmhub.funcs->get_घड़ीgating(adev, flags);

	अगर (adev->asic_type >= CHIP_SIENNA_CICHLID &&
	    adev->asic_type <= CHIP_DIMGREY_CAVEFISH)
		athub_v2_1_get_घड़ीgating(adev, flags);
	अन्यथा
		athub_v2_0_get_घड़ीgating(adev, flags);
पूर्ण

अटल पूर्णांक gmc_v10_0_set_घातergating_state(व्योम *handle,
					   क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

स्थिर काष्ठा amd_ip_funcs gmc_v10_0_ip_funcs = अणु
	.name = "gmc_v10_0",
	.early_init = gmc_v10_0_early_init,
	.late_init = gmc_v10_0_late_init,
	.sw_init = gmc_v10_0_sw_init,
	.sw_fini = gmc_v10_0_sw_fini,
	.hw_init = gmc_v10_0_hw_init,
	.hw_fini = gmc_v10_0_hw_fini,
	.suspend = gmc_v10_0_suspend,
	.resume = gmc_v10_0_resume,
	.is_idle = gmc_v10_0_is_idle,
	.रुको_क्रम_idle = gmc_v10_0_रुको_क्रम_idle,
	.soft_reset = gmc_v10_0_soft_reset,
	.set_घड़ीgating_state = gmc_v10_0_set_घड़ीgating_state,
	.set_घातergating_state = gmc_v10_0_set_घातergating_state,
	.get_घड़ीgating_state = gmc_v10_0_get_घड़ीgating_state,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version gmc_v10_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_GMC,
	.major = 10,
	.minor = 0,
	.rev = 0,
	.funcs = &gmc_v10_0_ip_funcs,
पूर्ण;
