<शैली गुरु>
/*
 * Copyright 2008 Cisco Systems, Inc.  All rights reserved.
 * Copyright 2007 Nuova Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश "vnic_dev.h"
#समावेश "vnic_cq.h"

व्योम vnic_cq_मुक्त(काष्ठा vnic_cq *cq)
अणु
	vnic_dev_मुक्त_desc_ring(cq->vdev, &cq->ring);

	cq->ctrl = शून्य;
पूर्ण

पूर्णांक vnic_cq_alloc(काष्ठा vnic_dev *vdev, काष्ठा vnic_cq *cq, अचिन्हित पूर्णांक index,
	अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size)
अणु
	पूर्णांक err;

	cq->index = index;
	cq->vdev = vdev;

	cq->ctrl = vnic_dev_get_res(vdev, RES_TYPE_CQ, index);
	अगर (!cq->ctrl) अणु
		prपूर्णांकk(KERN_ERR "Failed to hook CQ[%d] resource\n", index);
		वापस -EINVAL;
	पूर्ण

	err = vnic_dev_alloc_desc_ring(vdev, &cq->ring, desc_count, desc_size);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

व्योम vnic_cq_init(काष्ठा vnic_cq *cq, अचिन्हित पूर्णांक flow_control_enable,
	अचिन्हित पूर्णांक color_enable, अचिन्हित पूर्णांक cq_head, अचिन्हित पूर्णांक cq_tail,
	अचिन्हित पूर्णांक cq_tail_color, अचिन्हित पूर्णांक पूर्णांकerrupt_enable,
	अचिन्हित पूर्णांक cq_entry_enable, अचिन्हित पूर्णांक cq_message_enable,
	अचिन्हित पूर्णांक पूर्णांकerrupt_offset, u64 cq_message_addr)
अणु
	u64 paddr;

	paddr = (u64)cq->ring.base_addr | VNIC_PADDR_TARGET;
	ग_लिखोq(paddr, &cq->ctrl->ring_base);
	ioग_लिखो32(cq->ring.desc_count, &cq->ctrl->ring_size);
	ioग_लिखो32(flow_control_enable, &cq->ctrl->flow_control_enable);
	ioग_लिखो32(color_enable, &cq->ctrl->color_enable);
	ioग_लिखो32(cq_head, &cq->ctrl->cq_head);
	ioग_लिखो32(cq_tail, &cq->ctrl->cq_tail);
	ioग_लिखो32(cq_tail_color, &cq->ctrl->cq_tail_color);
	ioग_लिखो32(पूर्णांकerrupt_enable, &cq->ctrl->पूर्णांकerrupt_enable);
	ioग_लिखो32(cq_entry_enable, &cq->ctrl->cq_entry_enable);
	ioग_लिखो32(cq_message_enable, &cq->ctrl->cq_message_enable);
	ioग_लिखो32(पूर्णांकerrupt_offset, &cq->ctrl->पूर्णांकerrupt_offset);
	ग_लिखोq(cq_message_addr, &cq->ctrl->cq_message_addr);
पूर्ण

व्योम vnic_cq_clean(काष्ठा vnic_cq *cq)
अणु
	cq->to_clean = 0;
	cq->last_color = 0;

	ioग_लिखो32(0, &cq->ctrl->cq_head);
	ioग_लिखो32(0, &cq->ctrl->cq_tail);
	ioग_लिखो32(1, &cq->ctrl->cq_tail_color);

	vnic_dev_clear_desc_ring(&cq->ring);
पूर्ण
