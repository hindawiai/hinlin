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

#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/sched.h>
#समावेश "kfd_kernel_queue.h"
#समावेश "kfd_priv.h"
#समावेश "kfd_device_queue_manager.h"
#समावेश "kfd_pm4_headers.h"
#समावेश "kfd_pm4_opcodes.h"

#घोषणा PM4_COUNT_ZERO (((1 << 15) - 1) << 16)

/* Initialize a kernel queue, including allocations of GART memory
 * needed क्रम the queue.
 */
अटल bool kq_initialize(काष्ठा kernel_queue *kq, काष्ठा kfd_dev *dev,
		क्रमागत kfd_queue_type type, अचिन्हित पूर्णांक queue_size)
अणु
	काष्ठा queue_properties prop;
	पूर्णांक retval;
	जोड़ PM4_MES_TYPE_3_HEADER nop;

	अगर (WARN_ON(type != KFD_QUEUE_TYPE_DIQ && type != KFD_QUEUE_TYPE_HIQ))
		वापस false;

	pr_debug("Initializing queue type %d size %d\n", KFD_QUEUE_TYPE_HIQ,
			queue_size);

	स_रखो(&prop, 0, माप(prop));
	स_रखो(&nop, 0, माप(nop));

	nop.opcode = IT_NOP;
	nop.type = PM4_TYPE_3;
	nop.u32all |= PM4_COUNT_ZERO;

	kq->dev = dev;
	kq->nop_packet = nop.u32all;
	चयन (type) अणु
	हाल KFD_QUEUE_TYPE_DIQ:
		kq->mqd_mgr = dev->dqm->mqd_mgrs[KFD_MQD_TYPE_DIQ];
		अवरोध;
	हाल KFD_QUEUE_TYPE_HIQ:
		kq->mqd_mgr = dev->dqm->mqd_mgrs[KFD_MQD_TYPE_HIQ];
		अवरोध;
	शेष:
		pr_err("Invalid queue type %d\n", type);
		वापस false;
	पूर्ण

	अगर (!kq->mqd_mgr)
		वापस false;

	prop.करोorbell_ptr = kfd_get_kernel_करोorbell(dev, &prop.करोorbell_off);

	अगर (!prop.करोorbell_ptr) अणु
		pr_err("Failed to initialize doorbell");
		जाओ err_get_kernel_करोorbell;
	पूर्ण

	retval = kfd_gtt_sa_allocate(dev, queue_size, &kq->pq);
	अगर (retval != 0) अणु
		pr_err("Failed to init pq queues size %d\n", queue_size);
		जाओ err_pq_allocate_vidmem;
	पूर्ण

	kq->pq_kernel_addr = kq->pq->cpu_ptr;
	kq->pq_gpu_addr = kq->pq->gpu_addr;

	/* For CIK family asics, kq->eop_mem is not needed */
	अगर (dev->device_info->asic_family > CHIP_MULLINS) अणु
		retval = kfd_gtt_sa_allocate(dev, PAGE_SIZE, &kq->eop_mem);
		अगर (retval != 0)
			जाओ err_eop_allocate_vidmem;

		kq->eop_gpu_addr = kq->eop_mem->gpu_addr;
		kq->eop_kernel_addr = kq->eop_mem->cpu_ptr;

		स_रखो(kq->eop_kernel_addr, 0, PAGE_SIZE);
	पूर्ण

	retval = kfd_gtt_sa_allocate(dev, माप(*kq->rptr_kernel),
					&kq->rptr_mem);

	अगर (retval != 0)
		जाओ err_rptr_allocate_vidmem;

	kq->rptr_kernel = kq->rptr_mem->cpu_ptr;
	kq->rptr_gpu_addr = kq->rptr_mem->gpu_addr;

	retval = kfd_gtt_sa_allocate(dev, dev->device_info->करोorbell_size,
					&kq->wptr_mem);

	अगर (retval != 0)
		जाओ err_wptr_allocate_vidmem;

	kq->wptr_kernel = kq->wptr_mem->cpu_ptr;
	kq->wptr_gpu_addr = kq->wptr_mem->gpu_addr;

	स_रखो(kq->pq_kernel_addr, 0, queue_size);
	स_रखो(kq->rptr_kernel, 0, माप(*kq->rptr_kernel));
	स_रखो(kq->wptr_kernel, 0, माप(*kq->wptr_kernel));

	prop.queue_size = queue_size;
	prop.is_पूर्णांकerop = false;
	prop.is_gws = false;
	prop.priority = 1;
	prop.queue_percent = 100;
	prop.type = type;
	prop.vmid = 0;
	prop.queue_address = kq->pq_gpu_addr;
	prop.पढ़ो_ptr = (uपूर्णांक32_t *) kq->rptr_gpu_addr;
	prop.ग_लिखो_ptr = (uपूर्णांक32_t *) kq->wptr_gpu_addr;
	prop.eop_ring_buffer_address = kq->eop_gpu_addr;
	prop.eop_ring_buffer_size = PAGE_SIZE;
	prop.cu_mask = शून्य;

	अगर (init_queue(&kq->queue, &prop) != 0)
		जाओ err_init_queue;

	kq->queue->device = dev;
	kq->queue->process = kfd_get_process(current);

	kq->queue->mqd_mem_obj = kq->mqd_mgr->allocate_mqd(kq->mqd_mgr->dev,
					&kq->queue->properties);
	अगर (!kq->queue->mqd_mem_obj)
		जाओ err_allocate_mqd;
	kq->mqd_mgr->init_mqd(kq->mqd_mgr, &kq->queue->mqd,
					kq->queue->mqd_mem_obj,
					&kq->queue->gart_mqd_addr,
					&kq->queue->properties);
	/* assign HIQ to HQD */
	अगर (type == KFD_QUEUE_TYPE_HIQ) अणु
		pr_debug("Assigning hiq to hqd\n");
		kq->queue->pipe = KFD_CIK_HIQ_PIPE;
		kq->queue->queue = KFD_CIK_HIQ_QUEUE;
		kq->mqd_mgr->load_mqd(kq->mqd_mgr, kq->queue->mqd,
				kq->queue->pipe, kq->queue->queue,
				&kq->queue->properties, शून्य);
	पूर्ण अन्यथा अणु
		/* allocate fence क्रम DIQ */

		retval = kfd_gtt_sa_allocate(dev, माप(uपूर्णांक32_t),
						&kq->fence_mem_obj);

		अगर (retval != 0)
			जाओ err_alloc_fence;

		kq->fence_kernel_address = kq->fence_mem_obj->cpu_ptr;
		kq->fence_gpu_addr = kq->fence_mem_obj->gpu_addr;
	पूर्ण

	prपूर्णांक_queue(kq->queue);

	वापस true;
err_alloc_fence:
	kq->mqd_mgr->मुक्त_mqd(kq->mqd_mgr, kq->queue->mqd, kq->queue->mqd_mem_obj);
err_allocate_mqd:
	uninit_queue(kq->queue);
err_init_queue:
	kfd_gtt_sa_मुक्त(dev, kq->wptr_mem);
err_wptr_allocate_vidmem:
	kfd_gtt_sa_मुक्त(dev, kq->rptr_mem);
err_rptr_allocate_vidmem:
	kfd_gtt_sa_मुक्त(dev, kq->eop_mem);
err_eop_allocate_vidmem:
	kfd_gtt_sa_मुक्त(dev, kq->pq);
err_pq_allocate_vidmem:
	kfd_release_kernel_करोorbell(dev, prop.करोorbell_ptr);
err_get_kernel_करोorbell:
	वापस false;

पूर्ण

/* Uninitialize a kernel queue and मुक्त all its memory usages. */
अटल व्योम kq_uninitialize(काष्ठा kernel_queue *kq, bool hanging)
अणु
	अगर (kq->queue->properties.type == KFD_QUEUE_TYPE_HIQ && !hanging)
		kq->mqd_mgr->destroy_mqd(kq->mqd_mgr,
					kq->queue->mqd,
					KFD_PREEMPT_TYPE_WAVEFRONT_RESET,
					KFD_UNMAP_LATENCY_MS,
					kq->queue->pipe,
					kq->queue->queue);
	अन्यथा अगर (kq->queue->properties.type == KFD_QUEUE_TYPE_DIQ)
		kfd_gtt_sa_मुक्त(kq->dev, kq->fence_mem_obj);

	kq->mqd_mgr->मुक्त_mqd(kq->mqd_mgr, kq->queue->mqd,
				kq->queue->mqd_mem_obj);

	kfd_gtt_sa_मुक्त(kq->dev, kq->rptr_mem);
	kfd_gtt_sa_मुक्त(kq->dev, kq->wptr_mem);

	/* For CIK family asics, kq->eop_mem is Null, kfd_gtt_sa_मुक्त()
	 * is able to handle शून्य properly.
	 */
	kfd_gtt_sa_मुक्त(kq->dev, kq->eop_mem);

	kfd_gtt_sa_मुक्त(kq->dev, kq->pq);
	kfd_release_kernel_करोorbell(kq->dev,
					kq->queue->properties.करोorbell_ptr);
	uninit_queue(kq->queue);
पूर्ण

पूर्णांक kq_acquire_packet_buffer(काष्ठा kernel_queue *kq,
		माप_प्रकार packet_size_in_dwords, अचिन्हित पूर्णांक **buffer_ptr)
अणु
	माप_प्रकार available_size;
	माप_प्रकार queue_size_dwords;
	uपूर्णांक32_t wptr, rptr;
	uपूर्णांक64_t wptr64;
	अचिन्हित पूर्णांक *queue_address;

	/* When rptr == wptr, the buffer is empty.
	 * When rptr == wptr + 1, the buffer is full.
	 * It is always rptr that advances to the position of wptr, rather than
	 * the opposite. So we can only use up to queue_size_dwords - 1 dwords.
	 */
	rptr = *kq->rptr_kernel;
	wptr = kq->pending_wptr;
	wptr64 = kq->pending_wptr64;
	queue_address = (अचिन्हित पूर्णांक *)kq->pq_kernel_addr;
	queue_size_dwords = kq->queue->properties.queue_size / 4;

	pr_debug("rptr: %d\n", rptr);
	pr_debug("wptr: %d\n", wptr);
	pr_debug("queue_address 0x%p\n", queue_address);

	available_size = (rptr + queue_size_dwords - 1 - wptr) %
							queue_size_dwords;

	अगर (packet_size_in_dwords > available_size) अणु
		/*
		 * make sure calling functions know
		 * acquire_packet_buffer() failed
		 */
		जाओ err_no_space;
	पूर्ण

	अगर (wptr + packet_size_in_dwords >= queue_size_dwords) अणु
		/* make sure after rolling back to position 0, there is
		 * still enough space.
		 */
		अगर (packet_size_in_dwords >= rptr)
			जाओ err_no_space;

		/* fill nops, roll back and start at position 0 */
		जबतक (wptr > 0) अणु
			queue_address[wptr] = kq->nop_packet;
			wptr = (wptr + 1) % queue_size_dwords;
			wptr64++;
		पूर्ण
	पूर्ण

	*buffer_ptr = &queue_address[wptr];
	kq->pending_wptr = wptr + packet_size_in_dwords;
	kq->pending_wptr64 = wptr64 + packet_size_in_dwords;

	वापस 0;

err_no_space:
	*buffer_ptr = शून्य;
	वापस -ENOMEM;
पूर्ण

व्योम kq_submit_packet(काष्ठा kernel_queue *kq)
अणु
#अगर_घोषित DEBUG
	पूर्णांक i;

	क्रम (i = *kq->wptr_kernel; i < kq->pending_wptr; i++) अणु
		pr_debug("0x%2X ", kq->pq_kernel_addr[i]);
		अगर (i % 15 == 0)
			pr_debug("\n");
	पूर्ण
	pr_debug("\n");
#पूर्ण_अगर
	अगर (kq->dev->device_info->करोorbell_size == 8) अणु
		*kq->wptr64_kernel = kq->pending_wptr64;
		ग_लिखो_kernel_करोorbell64(kq->queue->properties.करोorbell_ptr,
					kq->pending_wptr64);
	पूर्ण अन्यथा अणु
		*kq->wptr_kernel = kq->pending_wptr;
		ग_लिखो_kernel_करोorbell(kq->queue->properties.करोorbell_ptr,
					kq->pending_wptr);
	पूर्ण
पूर्ण

व्योम kq_rollback_packet(काष्ठा kernel_queue *kq)
अणु
	अगर (kq->dev->device_info->करोorbell_size == 8) अणु
		kq->pending_wptr64 = *kq->wptr64_kernel;
		kq->pending_wptr = *kq->wptr_kernel %
			(kq->queue->properties.queue_size / 4);
	पूर्ण अन्यथा अणु
		kq->pending_wptr = *kq->wptr_kernel;
	पूर्ण
पूर्ण

काष्ठा kernel_queue *kernel_queue_init(काष्ठा kfd_dev *dev,
					क्रमागत kfd_queue_type type)
अणु
	काष्ठा kernel_queue *kq;

	kq = kzalloc(माप(*kq), GFP_KERNEL);
	अगर (!kq)
		वापस शून्य;

	अगर (kq_initialize(kq, dev, type, KFD_KERNEL_QUEUE_SIZE))
		वापस kq;

	pr_err("Failed to init kernel queue\n");

	kमुक्त(kq);
	वापस शून्य;
पूर्ण

व्योम kernel_queue_uninit(काष्ठा kernel_queue *kq, bool hanging)
अणु
	kq_uninitialize(kq, hanging);
	kमुक्त(kq);
पूर्ण

/* FIXME: Can this test be हटाओd? */
अटल __attribute__((unused)) व्योम test_kq(काष्ठा kfd_dev *dev)
अणु
	काष्ठा kernel_queue *kq;
	uपूर्णांक32_t *buffer, i;
	पूर्णांक retval;

	pr_err("Starting kernel queue test\n");

	kq = kernel_queue_init(dev, KFD_QUEUE_TYPE_HIQ);
	अगर (unlikely(!kq)) अणु
		pr_err("  Failed to initialize HIQ\n");
		pr_err("Kernel queue test failed\n");
		वापस;
	पूर्ण

	retval = kq_acquire_packet_buffer(kq, 5, &buffer);
	अगर (unlikely(retval != 0)) अणु
		pr_err("  Failed to acquire packet buffer\n");
		pr_err("Kernel queue test failed\n");
		वापस;
	पूर्ण
	क्रम (i = 0; i < 5; i++)
		buffer[i] = kq->nop_packet;
	kq_submit_packet(kq);

	pr_err("Ending kernel queue test\n");
पूर्ण


