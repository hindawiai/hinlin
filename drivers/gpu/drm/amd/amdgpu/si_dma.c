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
 * Authors: Alex Deucher
 */

#समावेश "amdgpu.h"
#समावेश "amdgpu_trace.h"
#समावेश "si.h"
#समावेश "sid.h"

स्थिर u32 sdma_offsets[SDMA_MAX_INSTANCE] =
अणु
	DMA0_REGISTER_OFFSET,
	DMA1_REGISTER_OFFSET
पूर्ण;

अटल व्योम si_dma_set_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम si_dma_set_buffer_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम si_dma_set_vm_pte_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम si_dma_set_irq_funcs(काष्ठा amdgpu_device *adev);

अटल uपूर्णांक64_t si_dma_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	वापस ring->adev->wb.wb[ring->rptr_offs>>2];
पूर्ण

अटल uपूर्णांक64_t si_dma_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	u32 me = (ring == &adev->sdma.instance[0].ring) ? 0 : 1;

	वापस (RREG32(DMA_RB_WPTR + sdma_offsets[me]) & 0x3fffc) >> 2;
पूर्ण

अटल व्योम si_dma_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	u32 me = (ring == &adev->sdma.instance[0].ring) ? 0 : 1;

	WREG32(DMA_RB_WPTR + sdma_offsets[me],
	       (lower_32_bits(ring->wptr) << 2) & 0x3fffc);
पूर्ण

अटल व्योम si_dma_ring_emit_ib(काष्ठा amdgpu_ring *ring,
				काष्ठा amdgpu_job *job,
				काष्ठा amdgpu_ib *ib,
				uपूर्णांक32_t flags)
अणु
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);
	/* The indirect buffer packet must end on an 8 DW boundary in the DMA ring.
	 * Pad as necessary with NOPs.
	 */
	जबतक ((lower_32_bits(ring->wptr) & 7) != 5)
		amdgpu_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0, 0));
	amdgpu_ring_ग_लिखो(ring, DMA_IB_PACKET(DMA_PACKET_INसूचीECT_BUFFER, vmid, 0));
	amdgpu_ring_ग_लिखो(ring, (ib->gpu_addr & 0xFFFFFFE0));
	amdgpu_ring_ग_लिखो(ring, (ib->length_dw << 12) | (upper_32_bits(ib->gpu_addr) & 0xFF));

पूर्ण

/**
 * si_dma_ring_emit_fence - emit a fence on the DMA ring
 *
 * @ring: amdgpu ring poपूर्णांकer
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Add a DMA fence packet to the ring to ग_लिखो
 * the fence seq number and DMA trap packet to generate
 * an पूर्णांकerrupt अगर needed (VI).
 */
अटल व्योम si_dma_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr, u64 seq,
				      अचिन्हित flags)
अणु

	bool ग_लिखो64bit = flags & AMDGPU_FENCE_FLAG_64BIT;
	/* ग_लिखो the fence */
	amdgpu_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_FENCE, 0, 0, 0, 0));
	amdgpu_ring_ग_लिखो(ring, addr & 0xfffffffc);
	amdgpu_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xff));
	amdgpu_ring_ग_लिखो(ring, seq);
	/* optionally ग_लिखो high bits as well */
	अगर (ग_लिखो64bit) अणु
		addr += 4;
		amdgpu_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_FENCE, 0, 0, 0, 0));
		amdgpu_ring_ग_लिखो(ring, addr & 0xfffffffc);
		amdgpu_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xff));
		amdgpu_ring_ग_लिखो(ring, upper_32_bits(seq));
	पूर्ण
	/* generate an पूर्णांकerrupt */
	amdgpu_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_TRAP, 0, 0, 0, 0));
पूर्ण

अटल व्योम si_dma_stop(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	u32 rb_cntl;
	अचिन्हित i;

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		ring = &adev->sdma.instance[i].ring;
		/* dma0 */
		rb_cntl = RREG32(DMA_RB_CNTL + sdma_offsets[i]);
		rb_cntl &= ~DMA_RB_ENABLE;
		WREG32(DMA_RB_CNTL + sdma_offsets[i], rb_cntl);

		अगर (adev->mman.buffer_funcs_ring == ring)
			amdgpu_tपंचांग_set_buffer_funcs_status(adev, false);
	पूर्ण
पूर्ण

अटल पूर्णांक si_dma_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	u32 rb_cntl, dma_cntl, ib_cntl, rb_bufsz;
	पूर्णांक i, r;
	uपूर्णांक64_t rptr_addr;

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		ring = &adev->sdma.instance[i].ring;

		WREG32(DMA_SEM_INCOMPLETE_TIMER_CNTL + sdma_offsets[i], 0);
		WREG32(DMA_SEM_WAIT_FAIL_TIMER_CNTL + sdma_offsets[i], 0);

		/* Set ring buffer size in dwords */
		rb_bufsz = order_base_2(ring->ring_size / 4);
		rb_cntl = rb_bufsz << 1;
#अगर_घोषित __BIG_ENDIAN
		rb_cntl |= DMA_RB_SWAP_ENABLE | DMA_RPTR_WRITEBACK_SWAP_ENABLE;
#पूर्ण_अगर
		WREG32(DMA_RB_CNTL + sdma_offsets[i], rb_cntl);

		/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
		WREG32(DMA_RB_RPTR + sdma_offsets[i], 0);
		WREG32(DMA_RB_WPTR + sdma_offsets[i], 0);

		rptr_addr = adev->wb.gpu_addr + (ring->rptr_offs * 4);

		WREG32(DMA_RB_RPTR_ADDR_LO + sdma_offsets[i], lower_32_bits(rptr_addr));
		WREG32(DMA_RB_RPTR_ADDR_HI + sdma_offsets[i], upper_32_bits(rptr_addr) & 0xFF);

		rb_cntl |= DMA_RPTR_WRITEBACK_ENABLE;

		WREG32(DMA_RB_BASE + sdma_offsets[i], ring->gpu_addr >> 8);

		/* enable DMA IBs */
		ib_cntl = DMA_IB_ENABLE | CMD_VMID_FORCE;
#अगर_घोषित __BIG_ENDIAN
		ib_cntl |= DMA_IB_SWAP_ENABLE;
#पूर्ण_अगर
		WREG32(DMA_IB_CNTL + sdma_offsets[i], ib_cntl);

		dma_cntl = RREG32(DMA_CNTL + sdma_offsets[i]);
		dma_cntl &= ~CTXEMPTY_INT_ENABLE;
		WREG32(DMA_CNTL + sdma_offsets[i], dma_cntl);

		ring->wptr = 0;
		WREG32(DMA_RB_WPTR + sdma_offsets[i], lower_32_bits(ring->wptr) << 2);
		WREG32(DMA_RB_CNTL + sdma_offsets[i], rb_cntl | DMA_RB_ENABLE);

		ring->sched.पढ़ोy = true;

		r = amdgpu_ring_test_helper(ring);
		अगर (r)
			वापस r;

		अगर (adev->mman.buffer_funcs_ring == ring)
			amdgpu_tपंचांग_set_buffer_funcs_status(adev, true);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * si_dma_ring_test_ring - simple async dma engine test
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 *
 * Test the DMA engine by writing using it to ग_लिखो an
 * value to memory. (VI).
 * Returns 0 क्रम success, error क्रम failure.
 */
अटल पूर्णांक si_dma_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	अचिन्हित i;
	अचिन्हित index;
	पूर्णांक r;
	u32 पंचांगp;
	u64 gpu_addr;

	r = amdgpu_device_wb_get(adev, &index);
	अगर (r)
		वापस r;

	gpu_addr = adev->wb.gpu_addr + (index * 4);
	पंचांगp = 0xCAFEDEAD;
	adev->wb.wb[index] = cpu_to_le32(पंचांगp);

	r = amdgpu_ring_alloc(ring, 4);
	अगर (r)
		जाओ error_मुक्त_wb;

	amdgpu_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_WRITE, 0, 0, 0, 1));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(gpu_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(gpu_addr) & 0xff);
	amdgpu_ring_ग_लिखो(ring, 0xDEADBEEF);
	amdgpu_ring_commit(ring);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		पंचांगp = le32_to_cpu(adev->wb.wb[index]);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= adev->usec_समयout)
		r = -ETIMEDOUT;

error_मुक्त_wb:
	amdgpu_device_wb_मुक्त(adev, index);
	वापस r;
पूर्ण

/**
 * si_dma_ring_test_ib - test an IB on the DMA engine
 *
 * @ring: amdgpu_ring काष्ठाure holding ring inक्रमmation
 * @समयout: समयout value in jअगरfies, or MAX_SCHEDULE_TIMEOUT
 *
 * Test a simple IB in the DMA ring (VI).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक si_dma_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा amdgpu_ib ib;
	काष्ठा dma_fence *f = शून्य;
	अचिन्हित index;
	u32 पंचांगp = 0;
	u64 gpu_addr;
	दीर्घ r;

	r = amdgpu_device_wb_get(adev, &index);
	अगर (r)
		वापस r;

	gpu_addr = adev->wb.gpu_addr + (index * 4);
	पंचांगp = 0xCAFEDEAD;
	adev->wb.wb[index] = cpu_to_le32(पंचांगp);
	स_रखो(&ib, 0, माप(ib));
	r = amdgpu_ib_get(adev, शून्य, 256,
					AMDGPU_IB_POOL_सूचीECT, &ib);
	अगर (r)
		जाओ err0;

	ib.ptr[0] = DMA_PACKET(DMA_PACKET_WRITE, 0, 0, 0, 1);
	ib.ptr[1] = lower_32_bits(gpu_addr);
	ib.ptr[2] = upper_32_bits(gpu_addr) & 0xff;
	ib.ptr[3] = 0xDEADBEEF;
	ib.length_dw = 4;
	r = amdgpu_ib_schedule(ring, 1, &ib, शून्य, &f);
	अगर (r)
		जाओ err1;

	r = dma_fence_रुको_समयout(f, false, समयout);
	अगर (r == 0) अणु
		r = -ETIMEDOUT;
		जाओ err1;
	पूर्ण अन्यथा अगर (r < 0) अणु
		जाओ err1;
	पूर्ण
	पंचांगp = le32_to_cpu(adev->wb.wb[index]);
	अगर (पंचांगp == 0xDEADBEEF)
		r = 0;
	अन्यथा
		r = -EINVAL;

err1:
	amdgpu_ib_मुक्त(adev, &ib, शून्य);
	dma_fence_put(f);
err0:
	amdgpu_device_wb_मुक्त(adev, index);
	वापस r;
पूर्ण

/**
 * cik_dma_vm_copy_pte - update PTEs by copying them from the GART
 *
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @src: src addr to copy from
 * @count: number of page entries to update
 *
 * Update PTEs by copying them from the GART using DMA (SI).
 */
अटल व्योम si_dma_vm_copy_pte(काष्ठा amdgpu_ib *ib,
			       uपूर्णांक64_t pe, uपूर्णांक64_t src,
			       अचिन्हित count)
अणु
	अचिन्हित bytes = count * 8;

	ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_COPY,
					      1, 0, 0, bytes);
	ib->ptr[ib->length_dw++] = lower_32_bits(pe);
	ib->ptr[ib->length_dw++] = lower_32_bits(src);
	ib->ptr[ib->length_dw++] = upper_32_bits(pe) & 0xff;
	ib->ptr[ib->length_dw++] = upper_32_bits(src) & 0xff;
पूर्ण

/**
 * si_dma_vm_ग_लिखो_pte - update PTEs by writing them manually
 *
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @value: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 *
 * Update PTEs by writing them manually using DMA (SI).
 */
अटल व्योम si_dma_vm_ग_लिखो_pte(काष्ठा amdgpu_ib *ib, uपूर्णांक64_t pe,
				uपूर्णांक64_t value, अचिन्हित count,
				uपूर्णांक32_t incr)
अणु
	अचिन्हित ndw = count * 2;

	ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_WRITE, 0, 0, 0, ndw);
	ib->ptr[ib->length_dw++] = lower_32_bits(pe);
	ib->ptr[ib->length_dw++] = upper_32_bits(pe);
	क्रम (; ndw > 0; ndw -= 2) अणु
		ib->ptr[ib->length_dw++] = lower_32_bits(value);
		ib->ptr[ib->length_dw++] = upper_32_bits(value);
		value += incr;
	पूर्ण
पूर्ण

/**
 * si_dma_vm_set_pte_pde - update the page tables using sDMA
 *
 * @ib: indirect buffer to fill with commands
 * @pe: addr of the page entry
 * @addr: dst addr to ग_लिखो पूर्णांकo pe
 * @count: number of page entries to update
 * @incr: increase next addr by incr bytes
 * @flags: access flags
 *
 * Update the page tables using sDMA (CIK).
 */
अटल व्योम si_dma_vm_set_pte_pde(काष्ठा amdgpu_ib *ib,
				     uपूर्णांक64_t pe,
				     uपूर्णांक64_t addr, अचिन्हित count,
				     uपूर्णांक32_t incr, uपूर्णांक64_t flags)
अणु
	uपूर्णांक64_t value;
	अचिन्हित ndw;

	जबतक (count) अणु
		ndw = count * 2;
		अगर (ndw > 0xFFFFE)
			ndw = 0xFFFFE;

		अगर (flags & AMDGPU_PTE_VALID)
			value = addr;
		अन्यथा
			value = 0;

		/* क्रम physically contiguous pages (vram) */
		ib->ptr[ib->length_dw++] = DMA_PTE_PDE_PACKET(ndw);
		ib->ptr[ib->length_dw++] = pe; /* dst addr */
		ib->ptr[ib->length_dw++] = upper_32_bits(pe) & 0xff;
		ib->ptr[ib->length_dw++] = lower_32_bits(flags); /* mask */
		ib->ptr[ib->length_dw++] = upper_32_bits(flags);
		ib->ptr[ib->length_dw++] = value; /* value */
		ib->ptr[ib->length_dw++] = upper_32_bits(value);
		ib->ptr[ib->length_dw++] = incr; /* increment size */
		ib->ptr[ib->length_dw++] = 0;
		pe += ndw * 4;
		addr += (ndw / 2) * incr;
		count -= ndw / 2;
	पूर्ण
पूर्ण

/**
 * si_dma_pad_ib - pad the IB to the required number of dw
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @ib: indirect buffer to fill with padding
 *
 */
अटल व्योम si_dma_ring_pad_ib(काष्ठा amdgpu_ring *ring, काष्ठा amdgpu_ib *ib)
अणु
	जबतक (ib->length_dw & 0x7)
		ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0, 0);
पूर्ण

/**
 * cik_sdma_ring_emit_pipeline_sync - sync the pipeline
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Make sure all previous operations are completed (CIK).
 */
अटल व्योम si_dma_ring_emit_pipeline_sync(काष्ठा amdgpu_ring *ring)
अणु
	uपूर्णांक32_t seq = ring->fence_drv.sync_seq;
	uपूर्णांक64_t addr = ring->fence_drv.gpu_addr;

	/* रुको क्रम idle */
	amdgpu_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_POLL_REG_MEM, 0, 0, 0, 0) |
			  (1 << 27)); /* Poll memory */
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, (0xff << 16) | upper_32_bits(addr)); /* retry, addr_hi */
	amdgpu_ring_ग_लिखो(ring, 0xffffffff); /* mask */
	amdgpu_ring_ग_लिखो(ring, seq); /* value */
	amdgpu_ring_ग_लिखो(ring, (3 << 28) | 0x20); /* func(equal) | poll पूर्णांकerval */
पूर्ण

/**
 * si_dma_ring_emit_vm_flush - cik vm flush using sDMA
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @vmid: vmid number to use
 * @pd_addr: address
 *
 * Update the page table base and flush the VM TLB
 * using sDMA (VI).
 */
अटल व्योम si_dma_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
				      अचिन्हित vmid, uपूर्णांक64_t pd_addr)
अणु
	amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	/* रुको क्रम invalidate to complete */
	amdgpu_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_POLL_REG_MEM, 0, 0, 0, 0));
	amdgpu_ring_ग_लिखो(ring, VM_INVALIDATE_REQUEST);
	amdgpu_ring_ग_लिखो(ring, 0xff << 16); /* retry */
	amdgpu_ring_ग_लिखो(ring, 1 << vmid); /* mask */
	amdgpu_ring_ग_लिखो(ring, 0); /* value */
	amdgpu_ring_ग_लिखो(ring, (0 << 28) | 0x20); /* func(always) | poll पूर्णांकerval */
पूर्ण

अटल व्योम si_dma_ring_emit_wreg(काष्ठा amdgpu_ring *ring,
				  uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	amdgpu_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_SRBM_WRITE, 0, 0, 0, 0));
	amdgpu_ring_ग_लिखो(ring, (0xf << 16) | reg);
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

अटल पूर्णांक si_dma_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->sdma.num_instances = 2;

	si_dma_set_ring_funcs(adev);
	si_dma_set_buffer_funcs(adev);
	si_dma_set_vm_pte_funcs(adev);
	si_dma_set_irq_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक si_dma_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक r, i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* DMA0 trap event */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 224,
			      &adev->sdma.trap_irq);
	अगर (r)
		वापस r;

	/* DMA1 trap event */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 244,
			      &adev->sdma.trap_irq);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		ring = &adev->sdma.instance[i].ring;
		ring->ring_obj = शून्य;
		ring->use_करोorbell = false;
		प्र_लिखो(ring->name, "sdma%d", i);
		r = amdgpu_ring_init(adev, ring, 1024,
				     &adev->sdma.trap_irq,
				     (i == 0) ? AMDGPU_SDMA_IRQ_INSTANCE0 :
				     AMDGPU_SDMA_IRQ_INSTANCE1,
				     AMDGPU_RING_PRIO_DEFAULT, शून्य);
		अगर (r)
			वापस r;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक si_dma_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक i;

	क्रम (i = 0; i < adev->sdma.num_instances; i++)
		amdgpu_ring_fini(&adev->sdma.instance[i].ring);

	वापस 0;
पूर्ण

अटल पूर्णांक si_dma_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस si_dma_start(adev);
पूर्ण

अटल पूर्णांक si_dma_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	si_dma_stop(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक si_dma_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस si_dma_hw_fini(adev);
पूर्ण

अटल पूर्णांक si_dma_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस si_dma_hw_init(adev);
पूर्ण

अटल bool si_dma_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 पंचांगp = RREG32(SRBM_STATUS2);

	अगर (पंचांगp & (DMA_BUSY_MASK | DMA1_BUSY_MASK))
	    वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक si_dma_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (si_dma_is_idle(handle))
			वापस 0;
		udelay(1);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक si_dma_soft_reset(व्योम *handle)
अणु
	DRM_INFO("si_dma_soft_reset --- not implemented !!!!!!!\n");
	वापस 0;
पूर्ण

अटल पूर्णांक si_dma_set_trap_irq_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *src,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	u32 sdma_cntl;

	चयन (type) अणु
	हाल AMDGPU_SDMA_IRQ_INSTANCE0:
		चयन (state) अणु
		हाल AMDGPU_IRQ_STATE_DISABLE:
			sdma_cntl = RREG32(DMA_CNTL + DMA0_REGISTER_OFFSET);
			sdma_cntl &= ~TRAP_ENABLE;
			WREG32(DMA_CNTL + DMA0_REGISTER_OFFSET, sdma_cntl);
			अवरोध;
		हाल AMDGPU_IRQ_STATE_ENABLE:
			sdma_cntl = RREG32(DMA_CNTL + DMA0_REGISTER_OFFSET);
			sdma_cntl |= TRAP_ENABLE;
			WREG32(DMA_CNTL + DMA0_REGISTER_OFFSET, sdma_cntl);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल AMDGPU_SDMA_IRQ_INSTANCE1:
		चयन (state) अणु
		हाल AMDGPU_IRQ_STATE_DISABLE:
			sdma_cntl = RREG32(DMA_CNTL + DMA1_REGISTER_OFFSET);
			sdma_cntl &= ~TRAP_ENABLE;
			WREG32(DMA_CNTL + DMA1_REGISTER_OFFSET, sdma_cntl);
			अवरोध;
		हाल AMDGPU_IRQ_STATE_ENABLE:
			sdma_cntl = RREG32(DMA_CNTL + DMA1_REGISTER_OFFSET);
			sdma_cntl |= TRAP_ENABLE;
			WREG32(DMA_CNTL + DMA1_REGISTER_OFFSET, sdma_cntl);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si_dma_process_trap_irq(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	अगर (entry->src_id == 224)
		amdgpu_fence_process(&adev->sdma.instance[0].ring);
	अन्यथा
		amdgpu_fence_process(&adev->sdma.instance[1].ring);
	वापस 0;
पूर्ण

अटल पूर्णांक si_dma_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	u32 orig, data, offset;
	पूर्णांक i;
	bool enable;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	enable = (state == AMD_CG_STATE_GATE);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_SDMA_MGCG)) अणु
		क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
			अगर (i == 0)
				offset = DMA0_REGISTER_OFFSET;
			अन्यथा
				offset = DMA1_REGISTER_OFFSET;
			orig = data = RREG32(DMA_POWER_CNTL + offset);
			data &= ~MEM_POWER_OVERRIDE;
			अगर (data != orig)
				WREG32(DMA_POWER_CNTL + offset, data);
			WREG32(DMA_CLK_CTRL + offset, 0x00000100);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
			अगर (i == 0)
				offset = DMA0_REGISTER_OFFSET;
			अन्यथा
				offset = DMA1_REGISTER_OFFSET;
			orig = data = RREG32(DMA_POWER_CNTL + offset);
			data |= MEM_POWER_OVERRIDE;
			अगर (data != orig)
				WREG32(DMA_POWER_CNTL + offset, data);

			orig = data = RREG32(DMA_CLK_CTRL + offset);
			data = 0xff000000;
			अगर (data != orig)
				WREG32(DMA_CLK_CTRL + offset, data);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si_dma_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	u32 पंचांगp;

	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	WREG32(DMA_PGFSM_WRITE,  0x00002000);
	WREG32(DMA_PGFSM_CONFIG, 0x100010ff);

	क्रम (पंचांगp = 0; पंचांगp < 5; पंचांगp++)
		WREG32(DMA_PGFSM_WRITE, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs si_dma_ip_funcs = अणु
	.name = "si_dma",
	.early_init = si_dma_early_init,
	.late_init = शून्य,
	.sw_init = si_dma_sw_init,
	.sw_fini = si_dma_sw_fini,
	.hw_init = si_dma_hw_init,
	.hw_fini = si_dma_hw_fini,
	.suspend = si_dma_suspend,
	.resume = si_dma_resume,
	.is_idle = si_dma_is_idle,
	.रुको_क्रम_idle = si_dma_रुको_क्रम_idle,
	.soft_reset = si_dma_soft_reset,
	.set_घड़ीgating_state = si_dma_set_घड़ीgating_state,
	.set_घातergating_state = si_dma_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs si_dma_ring_funcs = अणु
	.type = AMDGPU_RING_TYPE_SDMA,
	.align_mask = 0xf,
	.nop = DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0, 0),
	.support_64bit_ptrs = false,
	.get_rptr = si_dma_ring_get_rptr,
	.get_wptr = si_dma_ring_get_wptr,
	.set_wptr = si_dma_ring_set_wptr,
	.emit_frame_size =
		3 + 3 + /* hdp flush / invalidate */
		6 + /* si_dma_ring_emit_pipeline_sync */
		SI_FLUSH_GPU_TLB_NUM_WREG * 3 + 6 + /* si_dma_ring_emit_vm_flush */
		9 + 9 + 9, /* si_dma_ring_emit_fence x3 क्रम user fence, vm fence */
	.emit_ib_size = 7 + 3, /* si_dma_ring_emit_ib */
	.emit_ib = si_dma_ring_emit_ib,
	.emit_fence = si_dma_ring_emit_fence,
	.emit_pipeline_sync = si_dma_ring_emit_pipeline_sync,
	.emit_vm_flush = si_dma_ring_emit_vm_flush,
	.test_ring = si_dma_ring_test_ring,
	.test_ib = si_dma_ring_test_ib,
	.insert_nop = amdgpu_ring_insert_nop,
	.pad_ib = si_dma_ring_pad_ib,
	.emit_wreg = si_dma_ring_emit_wreg,
पूर्ण;

अटल व्योम si_dma_set_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->sdma.num_instances; i++)
		adev->sdma.instance[i].ring.funcs = &si_dma_ring_funcs;
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs si_dma_trap_irq_funcs = अणु
	.set = si_dma_set_trap_irq_state,
	.process = si_dma_process_trap_irq,
पूर्ण;

अटल व्योम si_dma_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->sdma.trap_irq.num_types = AMDGPU_SDMA_IRQ_LAST;
	adev->sdma.trap_irq.funcs = &si_dma_trap_irq_funcs;
पूर्ण

/**
 * si_dma_emit_copy_buffer - copy buffer using the sDMA engine
 *
 * @ib: indirect buffer to copy to
 * @src_offset: src GPU address
 * @dst_offset: dst GPU address
 * @byte_count: number of bytes to xfer
 * @पंचांगz: is this a secure operation
 *
 * Copy GPU buffers using the DMA engine (VI).
 * Used by the amdgpu tपंचांग implementation to move pages अगर
 * रेजिस्टरed as the asic copy callback.
 */
अटल व्योम si_dma_emit_copy_buffer(काष्ठा amdgpu_ib *ib,
				       uपूर्णांक64_t src_offset,
				       uपूर्णांक64_t dst_offset,
				       uपूर्णांक32_t byte_count,
				       bool पंचांगz)
अणु
	ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_COPY,
					      1, 0, 0, byte_count);
	ib->ptr[ib->length_dw++] = lower_32_bits(dst_offset);
	ib->ptr[ib->length_dw++] = lower_32_bits(src_offset);
	ib->ptr[ib->length_dw++] = upper_32_bits(dst_offset) & 0xff;
	ib->ptr[ib->length_dw++] = upper_32_bits(src_offset) & 0xff;
पूर्ण

/**
 * si_dma_emit_fill_buffer - fill buffer using the sDMA engine
 *
 * @ib: indirect buffer to copy to
 * @src_data: value to ग_लिखो to buffer
 * @dst_offset: dst GPU address
 * @byte_count: number of bytes to xfer
 *
 * Fill GPU buffers using the DMA engine (VI).
 */
अटल व्योम si_dma_emit_fill_buffer(काष्ठा amdgpu_ib *ib,
				       uपूर्णांक32_t src_data,
				       uपूर्णांक64_t dst_offset,
				       uपूर्णांक32_t byte_count)
अणु
	ib->ptr[ib->length_dw++] = DMA_PACKET(DMA_PACKET_CONSTANT_FILL,
					      0, 0, 0, byte_count / 4);
	ib->ptr[ib->length_dw++] = lower_32_bits(dst_offset);
	ib->ptr[ib->length_dw++] = src_data;
	ib->ptr[ib->length_dw++] = upper_32_bits(dst_offset) << 16;
पूर्ण


अटल स्थिर काष्ठा amdgpu_buffer_funcs si_dma_buffer_funcs = अणु
	.copy_max_bytes = 0xffff8,
	.copy_num_dw = 5,
	.emit_copy_buffer = si_dma_emit_copy_buffer,

	.fill_max_bytes = 0xffff8,
	.fill_num_dw = 4,
	.emit_fill_buffer = si_dma_emit_fill_buffer,
पूर्ण;

अटल व्योम si_dma_set_buffer_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->mman.buffer_funcs = &si_dma_buffer_funcs;
	adev->mman.buffer_funcs_ring = &adev->sdma.instance[0].ring;
पूर्ण

अटल स्थिर काष्ठा amdgpu_vm_pte_funcs si_dma_vm_pte_funcs = अणु
	.copy_pte_num_dw = 5,
	.copy_pte = si_dma_vm_copy_pte,

	.ग_लिखो_pte = si_dma_vm_ग_लिखो_pte,
	.set_pte_pde = si_dma_vm_set_pte_pde,
पूर्ण;

अटल व्योम si_dma_set_vm_pte_funcs(काष्ठा amdgpu_device *adev)
अणु
	अचिन्हित i;

	adev->vm_manager.vm_pte_funcs = &si_dma_vm_pte_funcs;
	क्रम (i = 0; i < adev->sdma.num_instances; i++) अणु
		adev->vm_manager.vm_pte_scheds[i] =
			&adev->sdma.instance[i].ring.sched;
	पूर्ण
	adev->vm_manager.vm_pte_num_scheds = adev->sdma.num_instances;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version si_dma_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_SDMA,
	.major = 1,
	.minor = 0,
	.rev = 0,
	.funcs = &si_dma_ip_funcs,
पूर्ण;
