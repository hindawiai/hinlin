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

#अगर_अघोषित KFD_KERNEL_QUEUE_H_
#घोषणा KFD_KERNEL_QUEUE_H_

#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश "kfd_priv.h"

/**
 * kq_acquire_packet_buffer: Returns a poपूर्णांकer to the location in the kernel
 * queue ring buffer where the calling function can ग_लिखो its packet. It is
 * Guaranteed that there is enough space क्रम that packet. It also updates the
 * pending ग_लिखो poपूर्णांकer to that location so subsequent calls to
 * acquire_packet_buffer will get a correct ग_लिखो poपूर्णांकer
 *
 * kq_submit_packet: Update the ग_लिखो poपूर्णांकer and करोorbell of a kernel queue.
 *
 * kq_rollback_packet: This routine is called अगर we failed to build an acquired
 * packet क्रम some reason. It just overग_लिखोs the pending wptr with the current
 * one
 *
 */

पूर्णांक kq_acquire_packet_buffer(काष्ठा kernel_queue *kq,
				माप_प्रकार packet_size_in_dwords,
				अचिन्हित पूर्णांक **buffer_ptr);
व्योम kq_submit_packet(काष्ठा kernel_queue *kq);
व्योम kq_rollback_packet(काष्ठा kernel_queue *kq);


काष्ठा kernel_queue अणु
	/* data */
	काष्ठा kfd_dev		*dev;
	काष्ठा mqd_manager	*mqd_mgr;
	काष्ठा queue		*queue;
	uपूर्णांक64_t		pending_wptr64;
	uपूर्णांक32_t		pending_wptr;
	अचिन्हित पूर्णांक		nop_packet;

	काष्ठा kfd_mem_obj	*rptr_mem;
	uपूर्णांक32_t		*rptr_kernel;
	uपूर्णांक64_t		rptr_gpu_addr;
	काष्ठा kfd_mem_obj	*wptr_mem;
	जोड़ अणु
		uपूर्णांक64_t	*wptr64_kernel;
		uपूर्णांक32_t	*wptr_kernel;
	पूर्ण;
	uपूर्णांक64_t		wptr_gpu_addr;
	काष्ठा kfd_mem_obj	*pq;
	uपूर्णांक64_t		pq_gpu_addr;
	uपूर्णांक32_t		*pq_kernel_addr;
	काष्ठा kfd_mem_obj	*eop_mem;
	uपूर्णांक64_t		eop_gpu_addr;
	uपूर्णांक32_t		*eop_kernel_addr;

	काष्ठा kfd_mem_obj	*fence_mem_obj;
	uपूर्णांक64_t		fence_gpu_addr;
	व्योम			*fence_kernel_address;

	काष्ठा list_head	list;
पूर्ण;

#पूर्ण_अगर /* KFD_KERNEL_QUEUE_H_ */
