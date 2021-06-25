<शैली गुरु>
/*
 * Copyright 2008-2010 Cisco Systems, Inc.  All rights reserved.
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
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश "vnic_dev.h"
#समावेश "vnic_rq.h"
#समावेश "enic.h"

अटल पूर्णांक vnic_rq_alloc_bufs(काष्ठा vnic_rq *rq)
अणु
	काष्ठा vnic_rq_buf *buf;
	अचिन्हित पूर्णांक i, j, count = rq->ring.desc_count;
	अचिन्हित पूर्णांक blks = VNIC_RQ_BUF_BLKS_NEEDED(count);

	क्रम (i = 0; i < blks; i++) अणु
		rq->bufs[i] = kzalloc(VNIC_RQ_BUF_BLK_SZ(count), GFP_KERNEL);
		अगर (!rq->bufs[i])
			वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < blks; i++) अणु
		buf = rq->bufs[i];
		क्रम (j = 0; j < VNIC_RQ_BUF_BLK_ENTRIES(count); j++) अणु
			buf->index = i * VNIC_RQ_BUF_BLK_ENTRIES(count) + j;
			buf->desc = (u8 *)rq->ring.descs +
				rq->ring.desc_size * buf->index;
			अगर (buf->index + 1 == count) अणु
				buf->next = rq->bufs[0];
				अवरोध;
			पूर्ण अन्यथा अगर (j + 1 == VNIC_RQ_BUF_BLK_ENTRIES(count)) अणु
				buf->next = rq->bufs[i + 1];
			पूर्ण अन्यथा अणु
				buf->next = buf + 1;
				buf++;
			पूर्ण
		पूर्ण
	पूर्ण

	rq->to_use = rq->to_clean = rq->bufs[0];

	वापस 0;
पूर्ण

व्योम vnic_rq_मुक्त(काष्ठा vnic_rq *rq)
अणु
	काष्ठा vnic_dev *vdev;
	अचिन्हित पूर्णांक i;

	vdev = rq->vdev;

	vnic_dev_मुक्त_desc_ring(vdev, &rq->ring);

	क्रम (i = 0; i < VNIC_RQ_BUF_BLKS_MAX; i++) अणु
		अगर (rq->bufs[i]) अणु
			kमुक्त(rq->bufs[i]);
			rq->bufs[i] = शून्य;
		पूर्ण
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
		vdev_err(vdev, "Failed to hook RQ[%d] resource\n", index);
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

अटल व्योम vnic_rq_init_start(काष्ठा vnic_rq *rq, अचिन्हित पूर्णांक cq_index,
	अचिन्हित पूर्णांक fetch_index, अचिन्हित पूर्णांक posted_index,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_enable,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_offset)
अणु
	u64 paddr;
	अचिन्हित पूर्णांक count = rq->ring.desc_count;

	paddr = (u64)rq->ring.base_addr | VNIC_PADDR_TARGET;
	ग_लिखोq(paddr, &rq->ctrl->ring_base);
	ioग_लिखो32(count, &rq->ctrl->ring_size);
	ioग_लिखो32(cq_index, &rq->ctrl->cq_index);
	ioग_लिखो32(error_पूर्णांकerrupt_enable, &rq->ctrl->error_पूर्णांकerrupt_enable);
	ioग_लिखो32(error_पूर्णांकerrupt_offset, &rq->ctrl->error_पूर्णांकerrupt_offset);
	ioग_लिखो32(0, &rq->ctrl->dropped_packet_count);
	ioग_लिखो32(0, &rq->ctrl->error_status);
	ioग_लिखो32(fetch_index, &rq->ctrl->fetch_index);
	ioग_लिखो32(posted_index, &rq->ctrl->posted_index);

	rq->to_use = rq->to_clean =
		&rq->bufs[fetch_index / VNIC_RQ_BUF_BLK_ENTRIES(count)]
			[fetch_index % VNIC_RQ_BUF_BLK_ENTRIES(count)];
पूर्ण

व्योम vnic_rq_init(काष्ठा vnic_rq *rq, अचिन्हित पूर्णांक cq_index,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_enable,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_offset)
अणु
	vnic_rq_init_start(rq, cq_index, 0, 0, error_पूर्णांकerrupt_enable,
			   error_पूर्णांकerrupt_offset);
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
	काष्ठा vnic_dev *vdev = rq->vdev;
	पूर्णांक i;

	/* Due to a race condition with clearing RQ "mini-cache" in hw, we need
	 * to disable the RQ twice to guarantee that stale descriptors are not
	 * used when this RQ is re-enabled.
	 */
	क्रम (i = 0; i < 2; i++) अणु
		ioग_लिखो32(0, &rq->ctrl->enable);

		/* Wait क्रम HW to ACK disable request */
		क्रम (रुको = 20000; रुको > 0; रुको--)
			अगर (!ioपढ़ो32(&rq->ctrl->running))
				अवरोध;
		अगर (!रुको) अणु
			vdev_neterr(vdev, "Failed to disable RQ[%d]\n",
				    rq->index);

			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम vnic_rq_clean(काष्ठा vnic_rq *rq,
	व्योम (*buf_clean)(काष्ठा vnic_rq *rq, काष्ठा vnic_rq_buf *buf))
अणु
	काष्ठा vnic_rq_buf *buf;
	u32 fetch_index;
	अचिन्हित पूर्णांक count = rq->ring.desc_count;
	पूर्णांक i;

	buf = rq->to_clean;

	क्रम (i = 0; i < rq->ring.desc_count; i++) अणु
		(*buf_clean)(rq, buf);
		buf = buf->next;
	पूर्ण
	rq->ring.desc_avail = rq->ring.desc_count - 1;

	/* Use current fetch_index as the ring starting poपूर्णांक */
	fetch_index = ioपढ़ो32(&rq->ctrl->fetch_index);

	अगर (fetch_index == 0xFFFFFFFF) अणु /* check क्रम hardware gone  */
		/* Hardware surprise removal: reset fetch_index */
		fetch_index = 0;
	पूर्ण
	rq->to_use = rq->to_clean =
		&rq->bufs[fetch_index / VNIC_RQ_BUF_BLK_ENTRIES(count)]
			[fetch_index % VNIC_RQ_BUF_BLK_ENTRIES(count)];
	ioग_लिखो32(fetch_index, &rq->ctrl->posted_index);

	/* Anyसमय we ग_लिखो fetch_index, we need to re-ग_लिखो 0 to rq->enable
	 * to re-sync पूर्णांकernal VIC state.
	 */
	ioग_लिखो32(0, &rq->ctrl->enable);

	vnic_dev_clear_desc_ring(&rq->ring);
पूर्ण

