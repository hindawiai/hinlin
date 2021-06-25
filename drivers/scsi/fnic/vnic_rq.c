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
#समावेश <linux/slab.h>
#समावेश "vnic_dev.h"
#समावेश "vnic_rq.h"

अटल पूर्णांक vnic_rq_alloc_bufs(काष्ठा vnic_rq *rq)
अणु
	काष्ठा vnic_rq_buf *buf;
	अचिन्हित पूर्णांक i, j, count = rq->ring.desc_count;
	अचिन्हित पूर्णांक blks = VNIC_RQ_BUF_BLKS_NEEDED(count);

	क्रम (i = 0; i < blks; i++) अणु
		rq->bufs[i] = kzalloc(VNIC_RQ_BUF_BLK_SZ, GFP_ATOMIC);
		अगर (!rq->bufs[i]) अणु
			prपूर्णांकk(KERN_ERR "Failed to alloc rq_bufs\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < blks; i++) अणु
		buf = rq->bufs[i];
		क्रम (j = 0; j < VNIC_RQ_BUF_BLK_ENTRIES; j++) अणु
			buf->index = i * VNIC_RQ_BUF_BLK_ENTRIES + j;
			buf->desc = (u8 *)rq->ring.descs +
				rq->ring.desc_size * buf->index;
			अगर (buf->index + 1 == count) अणु
				buf->next = rq->bufs[0];
				अवरोध;
			पूर्ण अन्यथा अगर (j + 1 == VNIC_RQ_BUF_BLK_ENTRIES) अणु
				buf->next = rq->bufs[i + 1];
			पूर्ण अन्यथा अणु
				buf->next = buf + 1;
				buf++;
			पूर्ण
		पूर्ण
	पूर्ण

	rq->to_use = rq->to_clean = rq->bufs[0];
	rq->buf_index = 0;

	वापस 0;
पूर्ण

व्योम vnic_rq_मुक्त(काष्ठा vnic_rq *rq)
अणु
	काष्ठा vnic_dev *vdev;
	अचिन्हित पूर्णांक i;

	vdev = rq->vdev;

	vnic_dev_मुक्त_desc_ring(vdev, &rq->ring);

	क्रम (i = 0; i < VNIC_RQ_BUF_BLKS_MAX; i++) अणु
		kमुक्त(rq->bufs[i]);
		rq->bufs[i] = शून्य;
	पूर्ण

	rq->ctrl = शून्य;
पूर्ण

पूर्णांक vnic_rq_alloc(काष्ठा vnic_dev *vdev, काष्ठा vnic_rq *rq, अचिन्हित पूर्णांक index,
	अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size)
अणु
	पूर्णांक err;

	rq->index = index;
	rq->vdev = vdev;

	rq->ctrl = vnic_dev_get_res(vdev, RES_TYPE_RQ, index);
	अगर (!rq->ctrl) अणु
		prपूर्णांकk(KERN_ERR "Failed to hook RQ[%d] resource\n", index);
		वापस -EINVAL;
	पूर्ण

	vnic_rq_disable(rq);

	err = vnic_dev_alloc_desc_ring(vdev, &rq->ring, desc_count, desc_size);
	अगर (err)
		वापस err;

	err = vnic_rq_alloc_bufs(rq);
	अगर (err) अणु
		vnic_rq_मुक्त(rq);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम vnic_rq_init(काष्ठा vnic_rq *rq, अचिन्हित पूर्णांक cq_index,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_enable,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_offset)
अणु
	u64 paddr;
	u32 fetch_index;

	paddr = (u64)rq->ring.base_addr | VNIC_PADDR_TARGET;
	ग_लिखोq(paddr, &rq->ctrl->ring_base);
	ioग_लिखो32(rq->ring.desc_count, &rq->ctrl->ring_size);
	ioग_लिखो32(cq_index, &rq->ctrl->cq_index);
	ioग_लिखो32(error_पूर्णांकerrupt_enable, &rq->ctrl->error_पूर्णांकerrupt_enable);
	ioग_लिखो32(error_पूर्णांकerrupt_offset, &rq->ctrl->error_पूर्णांकerrupt_offset);
	ioग_लिखो32(0, &rq->ctrl->dropped_packet_count);
	ioग_लिखो32(0, &rq->ctrl->error_status);

	/* Use current fetch_index as the ring starting poपूर्णांक */
	fetch_index = ioपढ़ो32(&rq->ctrl->fetch_index);
	rq->to_use = rq->to_clean =
		&rq->bufs[fetch_index / VNIC_RQ_BUF_BLK_ENTRIES]
			[fetch_index % VNIC_RQ_BUF_BLK_ENTRIES];
	ioग_लिखो32(fetch_index, &rq->ctrl->posted_index);

	rq->buf_index = 0;
पूर्ण

अचिन्हित पूर्णांक vnic_rq_error_status(काष्ठा vnic_rq *rq)
अणु
	वापस ioपढ़ो32(&rq->ctrl->error_status);
पूर्ण

व्योम vnic_rq_enable(काष्ठा vnic_rq *rq)
अणु
	ioग_लिखो32(1, &rq->ctrl->enable);
पूर्ण

पूर्णांक vnic_rq_disable(काष्ठा vnic_rq *rq)
अणु
	अचिन्हित पूर्णांक रुको;

	ioग_लिखो32(0, &rq->ctrl->enable);

	/* Wait क्रम HW to ACK disable request */
	क्रम (रुको = 0; रुको < 100; रुको++) अणु
		अगर (!(ioपढ़ो32(&rq->ctrl->running)))
			वापस 0;
		udelay(1);
	पूर्ण

	prपूर्णांकk(KERN_ERR "Failed to disable RQ[%d]\n", rq->index);

	वापस -ETIMEDOUT;
पूर्ण

व्योम vnic_rq_clean(काष्ठा vnic_rq *rq,
	व्योम (*buf_clean)(काष्ठा vnic_rq *rq, काष्ठा vnic_rq_buf *buf))
अणु
	काष्ठा vnic_rq_buf *buf;
	u32 fetch_index;

	WARN_ON(ioपढ़ो32(&rq->ctrl->enable));

	buf = rq->to_clean;

	जबतक (vnic_rq_desc_used(rq) > 0) अणु

		(*buf_clean)(rq, buf);

		buf = rq->to_clean = buf->next;
		rq->ring.desc_avail++;
	पूर्ण

	/* Use current fetch_index as the ring starting poपूर्णांक */
	fetch_index = ioपढ़ो32(&rq->ctrl->fetch_index);
	rq->to_use = rq->to_clean =
		&rq->bufs[fetch_index / VNIC_RQ_BUF_BLK_ENTRIES]
			[fetch_index % VNIC_RQ_BUF_BLK_ENTRIES];
	ioग_लिखो32(fetch_index, &rq->ctrl->posted_index);

	rq->buf_index = 0;

	vnic_dev_clear_desc_ring(&rq->ring);
पूर्ण

