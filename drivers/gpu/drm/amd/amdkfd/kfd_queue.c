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

#समावेश <linux/slab.h>
#समावेश "kfd_priv.h"

व्योम prपूर्णांक_queue_properties(काष्ठा queue_properties *q)
अणु
	अगर (!q)
		वापस;

	pr_debug("Printing queue properties:\n");
	pr_debug("Queue Type: %u\n", q->type);
	pr_debug("Queue Size: %llu\n", q->queue_size);
	pr_debug("Queue percent: %u\n", q->queue_percent);
	pr_debug("Queue Address: 0x%llX\n", q->queue_address);
	pr_debug("Queue Id: %u\n", q->queue_id);
	pr_debug("Queue Process Vmid: %u\n", q->vmid);
	pr_debug("Queue Read Pointer: 0x%px\n", q->पढ़ो_ptr);
	pr_debug("Queue Write Pointer: 0x%px\n", q->ग_लिखो_ptr);
	pr_debug("Queue Doorbell Pointer: 0x%p\n", q->करोorbell_ptr);
	pr_debug("Queue Doorbell Offset: %u\n", q->करोorbell_off);
पूर्ण

व्योम prपूर्णांक_queue(काष्ठा queue *q)
अणु
	अगर (!q)
		वापस;
	pr_debug("Printing queue:\n");
	pr_debug("Queue Type: %u\n", q->properties.type);
	pr_debug("Queue Size: %llu\n", q->properties.queue_size);
	pr_debug("Queue percent: %u\n", q->properties.queue_percent);
	pr_debug("Queue Address: 0x%llX\n", q->properties.queue_address);
	pr_debug("Queue Id: %u\n", q->properties.queue_id);
	pr_debug("Queue Process Vmid: %u\n", q->properties.vmid);
	pr_debug("Queue Read Pointer: 0x%px\n", q->properties.पढ़ो_ptr);
	pr_debug("Queue Write Pointer: 0x%px\n", q->properties.ग_लिखो_ptr);
	pr_debug("Queue Doorbell Pointer: 0x%p\n", q->properties.करोorbell_ptr);
	pr_debug("Queue Doorbell Offset: %u\n", q->properties.करोorbell_off);
	pr_debug("Queue MQD Address: 0x%p\n", q->mqd);
	pr_debug("Queue MQD Gart: 0x%llX\n", q->gart_mqd_addr);
	pr_debug("Queue Process Address: 0x%p\n", q->process);
	pr_debug("Queue Device Address: 0x%p\n", q->device);
पूर्ण

पूर्णांक init_queue(काष्ठा queue **q, स्थिर काष्ठा queue_properties *properties)
अणु
	काष्ठा queue *पंचांगp_q;

	पंचांगp_q = kzalloc(माप(*पंचांगp_q), GFP_KERNEL);
	अगर (!पंचांगp_q)
		वापस -ENOMEM;

	स_नकल(&पंचांगp_q->properties, properties, माप(*properties));

	*q = पंचांगp_q;
	वापस 0;
पूर्ण

व्योम uninit_queue(काष्ठा queue *q)
अणु
	kमुक्त(q);
पूर्ण
