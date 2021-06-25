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
#समावेश "vnic_wq.h"
#समावेश "enic.h"

अटल पूर्णांक vnic_wq_alloc_bufs(काष्ठा vnic_wq *wq)
अणु
	काष्ठा vnic_wq_buf *buf;
	अचिन्हित पूर्णांक i, j, count = wq->ring.desc_count;
	अचिन्हित पूर्णांक blks = VNIC_WQ_BUF_BLKS_NEEDED(count);

	क्रम (i = 0; i < blks; i++) अणु
		wq->bufs[i] = kzalloc(VNIC_WQ_BUF_BLK_SZ(count), GFP_KERNEL);
		अगर (!wq->bufs[i])
			वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < blks; i++) अणु
		buf = wq->bufs[i];
		क्रम (j = 0; j < VNIC_WQ_BUF_BLK_ENTRIES(count); j++) अणु
			buf->index = i * VNIC_WQ_BUF_BLK_ENTRIES(count) + j;
			buf->desc = (u8 *)wq->ring.descs +
				wq->ring.desc_size * buf->index;
			अगर (buf->index + 1 == count) अणु
				buf->next = wq->bufs[0];
				buf->next->prev = buf;
				अवरोध;
			पूर्ण अन्यथा अगर (j + 1 == VNIC_WQ_BUF_BLK_ENTRIES(count)) अणु
				buf->next = wq->bufs[i + 1];
				buf->next->prev = buf;
			पूर्ण अन्यथा अणु
				buf->next = buf + 1;
				buf->next->prev = buf;
				buf++;
			पूर्ण
		पूर्ण
	पूर्ण

	wq->to_use = wq->to_clean = wq->bufs[0];

	वापस 0;
पूर्ण

व्योम vnic_wq_मुक्त(काष्ठा vnic_wq *wq)
अणु
	काष्ठा vnic_dev *vdev;
	अचिन्हित पूर्णांक i;

	vdev = wq->vdev;

	vnic_dev_मुक्त_desc_ring(vdev, &wq->ring);

	क्रम (i = 0; i < VNIC_WQ_BUF_BLKS_MAX; i++) अणु
		अगर (wq->bufs[i]) अणु
			kमुक्त(wq->bufs[i]);
			wq->bufs[i] = शून्य;
		पूर्ण
	पूर्ण

	wq->ctrl = शून्य;
पूर्ण

पूर्णांक vnic_wq_alloc(काष्ठा vnic_dev *vdev, काष्ठा vnic_wq *wq, अचिन्हित पूर्णांक index,
	अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size)
अणु
	पूर्णांक err;

	wq->index = index;
	wq->vdev = vdev;

	wq->ctrl = vnic_dev_get_res(vdev, RES_TYPE_WQ, index);
	अगर (!wq->ctrl) अणु
		vdev_err(vdev, "Failed to hook WQ[%d] resource\n", index);
		वापस -EINVAL;
	पूर्ण

	vnic_wq_disable(wq);

	err = vnic_dev_alloc_desc_ring(vdev, &wq->ring, desc_count, desc_size);
	अगर (err)
		वापस err;

	err = vnic_wq_alloc_bufs(wq);
	अगर (err) अणु
		vnic_wq_मुक्त(wq);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक enic_wq_devcmd2_alloc(काष्ठा vnic_dev *vdev, काष्ठा vnic_wq *wq,
			  अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size)
अणु
	पूर्णांक err;

	wq->index = 0;
	wq->vdev = vdev;

	wq->ctrl = vnic_dev_get_res(vdev, RES_TYPE_DEVCMD2, 0);
	अगर (!wq->ctrl)
		वापस -EINVAL;
	vnic_wq_disable(wq);
	err = vnic_dev_alloc_desc_ring(vdev, &wq->ring, desc_count, desc_size);

	वापस err;
पूर्ण

व्योम enic_wq_init_start(काष्ठा vnic_wq *wq, अचिन्हित पूर्णांक cq_index,
			अचिन्हित पूर्णांक fetch_index, अचिन्हित पूर्णांक posted_index,
			अचिन्हित पूर्णांक error_पूर्णांकerrupt_enable,
			अचिन्हित पूर्णांक error_पूर्णांकerrupt_offset)
अणु
	u64 paddr;
	अचिन्हित पूर्णांक count = wq->ring.desc_count;

	paddr = (u64)wq->ring.base_addr | VNIC_PADDR_TARGET;
	ग_लिखोq(paddr, &wq->ctrl->ring_base);
	ioग_लिखो32(count, &wq->ctrl->ring_size);
	ioग_लिखो32(fetch_index, &wq->ctrl->fetch_index);
	ioग_लिखो32(posted_index, &wq->ctrl->posted_index);
	ioग_लिखो32(cq_index, &wq->ctrl->cq_index);
	ioग_लिखो32(error_पूर्णांकerrupt_enable, &wq->ctrl->error_पूर्णांकerrupt_enable);
	ioग_लिखो32(error_पूर्णांकerrupt_offset, &wq->ctrl->error_पूर्णांकerrupt_offset);
	ioग_लिखो32(0, &wq->ctrl->error_status);

	wq->to_use = wq->to_clean =
		&wq->bufs[fetch_index / VNIC_WQ_BUF_BLK_ENTRIES(count)]
			[fetch_index % VNIC_WQ_BUF_BLK_ENTRIES(count)];
पूर्ण

व्योम vnic_wq_init(काष्ठा vnic_wq *wq, अचिन्हित पूर्णांक cq_index,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_enable,
	अचिन्हित पूर्णांक error_पूर्णांकerrupt_offset)
अणु
	enic_wq_init_start(wq, cq_index, 0, 0,
		error_पूर्णांकerrupt_enable,
		error_पूर्णांकerrupt_offset);
पूर्ण

अचिन्हित पूर्णांक vnic_wq_error_status(काष्ठा vnic_wq *wq)
अणु
	वापस ioपढ़ो32(&wq->ctrl->error_status);
पूर्ण

व्योम vnic_wq_enable(काष्ठा vnic_wq *wq)
अणु
	ioग_लिखो32(1, &wq->ctrl->enable);
पूर्ण

पूर्णांक vnic_wq_disable(काष्ठा vnic_wq *wq)
अणु
	अचिन्हित पूर्णांक रुको;
	काष्ठा vnic_dev *vdev = wq->vdev;

	ioग_लिखो32(0, &wq->ctrl->enable);

	/* Wait क्रम HW to ACK disable request */
	क्रम (रुको = 0; रुको < 1000; रुको++) अणु
		अगर (!(ioपढ़ो32(&wq->ctrl->running)))
			वापस 0;
		udelay(10);
	पूर्ण

	vdev_neterr(vdev, "Failed to disable WQ[%d]\n", wq->index);

	वापस -ETIMEDOUT;
पूर्ण

व्योम vnic_wq_clean(काष्ठा vnic_wq *wq,
	व्योम (*buf_clean)(काष्ठा vnic_wq *wq, काष्ठा vnic_wq_buf *buf))
अणु
	काष्ठा vnic_wq_buf *buf;

	buf = wq->to_clean;

	जबतक (vnic_wq_desc_used(wq) > 0) अणु

		(*buf_clean)(wq, buf);

		buf = wq->to_clean = buf->next;
		wq->ring.desc_avail++;
	पूर्ण

	wq->to_use = wq->to_clean = wq->bufs[0];

	ioग_लिखो32(0, &wq->ctrl->fetch_index);
	ioग_लिखो32(0, &wq->ctrl->posted_index);
	ioग_लिखो32(0, &wq->ctrl->error_status);

	vnic_dev_clear_desc_ring(&wq->ring);
पूर्ण
