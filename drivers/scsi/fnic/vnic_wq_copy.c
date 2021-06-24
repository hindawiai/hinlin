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
#समावेश <linux/delay.h>
#समावेश "vnic_wq_copy.h"

व्योम vnic_wq_copy_enable(काष्ठा vnic_wq_copy *wq)
अणु
	ioग_लिखो32(1, &wq->ctrl->enable);
पूर्ण

पूर्णांक vnic_wq_copy_disable(काष्ठा vnic_wq_copy *wq)
अणु
	अचिन्हित पूर्णांक रुको;

	ioग_लिखो32(0, &wq->ctrl->enable);

	/* Wait क्रम HW to ACK disable request */
	क्रम (रुको = 0; रुको < 100; रुको++) अणु
		अगर (!(ioपढ़ो32(&wq->ctrl->running)))
			वापस 0;
		udelay(1);
	पूर्ण

	prपूर्णांकk(KERN_ERR "Failed to disable Copy WQ[%d],"
	       " fetch index=%d, posted_index=%d\n",
	       wq->index, ioपढ़ो32(&wq->ctrl->fetch_index),
	       ioपढ़ो32(&wq->ctrl->posted_index));

	वापस -ENODEV;
पूर्ण

व्योम vnic_wq_copy_clean(काष्ठा vnic_wq_copy *wq,
	व्योम (*q_clean)(काष्ठा vnic_wq_copy *wq,
	काष्ठा fcpio_host_req *wq_desc))
अणु
	BUG_ON(ioपढ़ो32(&wq->ctrl->enable));

	अगर (vnic_wq_copy_desc_in_use(wq))
		vnic_wq_copy_service(wq, -1, q_clean);

	wq->to_use_index = wq->to_clean_index = 0;

	ioग_लिखो32(0, &wq->ctrl->fetch_index);
	ioग_लिखो32(0, &wq->ctrl->posted_index);
	ioग_लिखो32(0, &wq->ctrl->error_status);

	vnic_dev_clear_desc_ring(&wq->ring);
पूर्ण

व्योम vnic_wq_copy_मुक्त(काष्ठा vnic_wq_copy *wq)
अणु
	काष्ठा vnic_dev *vdev;

	vdev = wq->vdev;
	vnic_dev_मुक्त_desc_ring(vdev, &wq->ring);
	wq->ctrl = शून्य;
पूर्ण

पूर्णांक vnic_wq_copy_alloc(काष्ठा vnic_dev *vdev, काष्ठा vnic_wq_copy *wq,
		       अचिन्हित पूर्णांक index, अचिन्हित पूर्णांक desc_count,
		       अचिन्हित पूर्णांक desc_size)
अणु
	wq->index = index;
	wq->vdev = vdev;
	wq->to_use_index = wq->to_clean_index = 0;
	wq->ctrl = vnic_dev_get_res(vdev, RES_TYPE_WQ, index);
	अगर (!wq->ctrl) अणु
		prपूर्णांकk(KERN_ERR "Failed to hook COPY WQ[%d] resource\n", index);
		वापस -EINVAL;
	पूर्ण

	vnic_wq_copy_disable(wq);

	वापस vnic_dev_alloc_desc_ring(vdev, &wq->ring, desc_count, desc_size);
पूर्ण

व्योम vnic_wq_copy_init(काष्ठा vnic_wq_copy *wq, अचिन्हित पूर्णांक cq_index,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_enable,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_offset)
अणु
	u64 paddr;

	paddr = (u64)wq->ring.base_addr | VNIC_PADDR_TARGET;
	ग_लिखोq(paddr, &wq->ctrl->ring_base);
	ioग_लिखो32(wq->ring.desc_count, &wq->ctrl->ring_size);
	ioग_लिखो32(0, &wq->ctrl->fetch_index);
	ioग_लिखो32(0, &wq->ctrl->posted_index);
	ioग_लिखो32(cq_index, &wq->ctrl->cq_index);
	ioग_लिखो32(error_पूर्णांकerrupt_enable, &wq->ctrl->error_पूर्णांकerrupt_enable);
	ioग_लिखो32(error_पूर्णांकerrupt_offset, &wq->ctrl->error_पूर्णांकerrupt_offset);
पूर्ण

