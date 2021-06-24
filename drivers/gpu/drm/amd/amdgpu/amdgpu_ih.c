<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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

#समावेश <linux/dma-mapping.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_ih.h"

/**
 * amdgpu_ih_ring_init - initialize the IH state
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: ih ring to initialize
 * @ring_size: ring size to allocate
 * @use_bus_addr: true when we can use dma_alloc_coherent
 *
 * Initializes the IH state and allocates a buffer
 * क्रम the IH ring buffer.
 * Returns 0 क्रम success, errors क्रम failure.
 */
पूर्णांक amdgpu_ih_ring_init(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ih_ring *ih,
			अचिन्हित ring_size, bool use_bus_addr)
अणु
	u32 rb_bufsz;
	पूर्णांक r;

	/* Align ring size */
	rb_bufsz = order_base_2(ring_size / 4);
	ring_size = (1 << rb_bufsz) * 4;
	ih->ring_size = ring_size;
	ih->ptr_mask = ih->ring_size - 1;
	ih->rptr = 0;
	ih->use_bus_addr = use_bus_addr;

	अगर (use_bus_addr) अणु
		dma_addr_t dma_addr;

		अगर (ih->ring)
			वापस 0;

		/* add 8 bytes क्रम the rptr/wptr shaकरोws and
		 * add them to the end of the ring allocation.
		 */
		ih->ring = dma_alloc_coherent(adev->dev, ih->ring_size + 8,
					      &dma_addr, GFP_KERNEL);
		अगर (ih->ring == शून्य)
			वापस -ENOMEM;

		ih->gpu_addr = dma_addr;
		ih->wptr_addr = dma_addr + ih->ring_size;
		ih->wptr_cpu = &ih->ring[ih->ring_size / 4];
		ih->rptr_addr = dma_addr + ih->ring_size + 4;
		ih->rptr_cpu = &ih->ring[(ih->ring_size / 4) + 1];
	पूर्ण अन्यथा अणु
		अचिन्हित wptr_offs, rptr_offs;

		r = amdgpu_device_wb_get(adev, &wptr_offs);
		अगर (r)
			वापस r;

		r = amdgpu_device_wb_get(adev, &rptr_offs);
		अगर (r) अणु
			amdgpu_device_wb_मुक्त(adev, wptr_offs);
			वापस r;
		पूर्ण

		r = amdgpu_bo_create_kernel(adev, ih->ring_size, PAGE_SIZE,
					    AMDGPU_GEM_DOMAIN_GTT,
					    &ih->ring_obj, &ih->gpu_addr,
					    (व्योम **)&ih->ring);
		अगर (r) अणु
			amdgpu_device_wb_मुक्त(adev, rptr_offs);
			amdgpu_device_wb_मुक्त(adev, wptr_offs);
			वापस r;
		पूर्ण

		ih->wptr_addr = adev->wb.gpu_addr + wptr_offs * 4;
		ih->wptr_cpu = &adev->wb.wb[wptr_offs];
		ih->rptr_addr = adev->wb.gpu_addr + rptr_offs * 4;
		ih->rptr_cpu = &adev->wb.wb[rptr_offs];
	पूर्ण

	init_रुकोqueue_head(&ih->रुको_process);
	वापस 0;
पूर्ण

/**
 * amdgpu_ih_ring_fini - tear करोwn the IH state
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: ih ring to tear करोwn
 *
 * Tears करोwn the IH state and मुक्तs buffer
 * used क्रम the IH ring buffer.
 */
व्योम amdgpu_ih_ring_fini(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ih_ring *ih)
अणु
	अगर (ih->use_bus_addr) अणु
		अगर (!ih->ring)
			वापस;

		/* add 8 bytes क्रम the rptr/wptr shaकरोws and
		 * add them to the end of the ring allocation.
		 */
		dma_मुक्त_coherent(adev->dev, ih->ring_size + 8,
				  (व्योम *)ih->ring, ih->gpu_addr);
		ih->ring = शून्य;
	पूर्ण अन्यथा अणु
		amdgpu_bo_मुक्त_kernel(&ih->ring_obj, &ih->gpu_addr,
				      (व्योम **)&ih->ring);
		amdgpu_device_wb_मुक्त(adev, (ih->wptr_addr - ih->gpu_addr) / 4);
		amdgpu_device_wb_मुक्त(adev, (ih->rptr_addr - ih->gpu_addr) / 4);
	पूर्ण
पूर्ण

/**
 * amdgpu_ih_ring_ग_लिखो - ग_लिखो IV to the ring buffer
 *
 * @ih: ih ring to ग_लिखो to
 * @iv: the iv to ग_लिखो
 * @num_dw: size of the iv in dw
 *
 * Writes an IV to the ring buffer using the CPU and increment the wptr.
 * Used क्रम testing and delegating IVs to a software ring.
 */
व्योम amdgpu_ih_ring_ग_लिखो(काष्ठा amdgpu_ih_ring *ih, स्थिर uपूर्णांक32_t *iv,
			  अचिन्हित पूर्णांक num_dw)
अणु
	uपूर्णांक32_t wptr = le32_to_cpu(*ih->wptr_cpu) >> 2;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_dw; ++i)
	        ih->ring[wptr++] = cpu_to_le32(iv[i]);

	wptr <<= 2;
	wptr &= ih->ptr_mask;

	/* Only commit the new wptr अगर we करोn't overflow */
	अगर (wptr != READ_ONCE(ih->rptr)) अणु
		wmb();
		WRITE_ONCE(*ih->wptr_cpu, cpu_to_le32(wptr));
	पूर्ण
पूर्ण

/* Waiter helper that checks current rptr matches or passes checkpoपूर्णांक wptr */
अटल bool amdgpu_ih_has_checkpoपूर्णांक_processed(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_ih_ring *ih,
					uपूर्णांक32_t checkpoपूर्णांक_wptr,
					uपूर्णांक32_t *prev_rptr)
अणु
	uपूर्णांक32_t cur_rptr = ih->rptr | (*prev_rptr & ~ih->ptr_mask);

	/* rptr has wrapped. */
	अगर (cur_rptr < *prev_rptr)
		cur_rptr += ih->ptr_mask + 1;
	*prev_rptr = cur_rptr;

	वापस cur_rptr >= checkpoपूर्णांक_wptr;
पूर्ण

/**
 * amdgpu_ih_रुको_on_checkpoपूर्णांक_process - रुको to process IVs up to checkpoपूर्णांक
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: ih ring to process
 *
 * Used to ensure ring has processed IVs up to the checkpoपूर्णांक ग_लिखो poपूर्णांकer.
 */
पूर्णांक amdgpu_ih_रुको_on_checkpoपूर्णांक_process(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_ih_ring *ih)
अणु
	uपूर्णांक32_t checkpoपूर्णांक_wptr, rptr;

	अगर (!ih->enabled || adev->shutकरोwn)
		वापस -ENODEV;

	checkpoपूर्णांक_wptr = amdgpu_ih_get_wptr(adev, ih);
	/* Order wptr with rptr. */
	rmb();
	rptr = READ_ONCE(ih->rptr);

	/* wptr has wrapped. */
	अगर (rptr > checkpoपूर्णांक_wptr)
		checkpoपूर्णांक_wptr += ih->ptr_mask + 1;

	वापस रुको_event_पूर्णांकerruptible(ih->रुको_process,
				amdgpu_ih_has_checkpoपूर्णांक_processed(adev, ih,
						checkpoपूर्णांक_wptr, &rptr));
पूर्ण

/**
 * amdgpu_ih_process - पूर्णांकerrupt handler
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: ih ring to process
 *
 * Interrupt hander (VI), walk the IH ring.
 * Returns irq process वापस code.
 */
पूर्णांक amdgpu_ih_process(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_ih_ring *ih)
अणु
	अचिन्हित पूर्णांक count = AMDGPU_IH_MAX_NUM_IVS;
	u32 wptr;

	अगर (!ih->enabled || adev->shutकरोwn)
		वापस IRQ_NONE;

	wptr = amdgpu_ih_get_wptr(adev, ih);

restart_ih:
	DRM_DEBUG("%s: rptr %d, wptr %d\n", __func__, ih->rptr, wptr);

	/* Order पढ़ोing of wptr vs. पढ़ोing of IH ring data */
	rmb();

	जबतक (ih->rptr != wptr && --count) अणु
		amdgpu_irq_dispatch(adev, ih);
		ih->rptr &= ih->ptr_mask;
	पूर्ण

	amdgpu_ih_set_rptr(adev, ih);
	wake_up_all(&ih->रुको_process);

	/* make sure wptr hasn't changed जबतक processing */
	wptr = amdgpu_ih_get_wptr(adev, ih);
	अगर (wptr != ih->rptr)
		जाओ restart_ih;

	वापस IRQ_HANDLED;
पूर्ण

/**
 * amdgpu_ih_decode_iv_helper - decode an पूर्णांकerrupt vector
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @ih: ih ring to process
 * @entry: IV entry
 *
 * Decodes the पूर्णांकerrupt vector at the current rptr
 * position and also advance the position क्रम क्रम Vega10
 * and later GPUs.
 */
व्योम amdgpu_ih_decode_iv_helper(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_ih_ring *ih,
				काष्ठा amdgpu_iv_entry *entry)
अणु
	/* wptr/rptr are in bytes! */
	u32 ring_index = ih->rptr >> 2;
	uपूर्णांक32_t dw[8];

	dw[0] = le32_to_cpu(ih->ring[ring_index + 0]);
	dw[1] = le32_to_cpu(ih->ring[ring_index + 1]);
	dw[2] = le32_to_cpu(ih->ring[ring_index + 2]);
	dw[3] = le32_to_cpu(ih->ring[ring_index + 3]);
	dw[4] = le32_to_cpu(ih->ring[ring_index + 4]);
	dw[5] = le32_to_cpu(ih->ring[ring_index + 5]);
	dw[6] = le32_to_cpu(ih->ring[ring_index + 6]);
	dw[7] = le32_to_cpu(ih->ring[ring_index + 7]);

	entry->client_id = dw[0] & 0xff;
	entry->src_id = (dw[0] >> 8) & 0xff;
	entry->ring_id = (dw[0] >> 16) & 0xff;
	entry->vmid = (dw[0] >> 24) & 0xf;
	entry->vmid_src = (dw[0] >> 31);
	entry->बारtamp = dw[1] | ((u64)(dw[2] & 0xffff) << 32);
	entry->बारtamp_src = dw[2] >> 31;
	entry->pasid = dw[3] & 0xffff;
	entry->pasid_src = dw[3] >> 31;
	entry->src_data[0] = dw[4];
	entry->src_data[1] = dw[5];
	entry->src_data[2] = dw[6];
	entry->src_data[3] = dw[7];

	/* wptr/rptr are in bytes! */
	ih->rptr += 32;
पूर्ण
