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
#समावेश "vnic_wq.h"


अटल पूर्णांक vnic_wq_get_ctrl(काष्ठा vnic_dev *vdev, काष्ठा vnic_wq *wq,
		अचिन्हित पूर्णांक index, क्रमागत vnic_res_type res_type)
अणु
	wq->ctrl = vnic_dev_get_res(vdev, res_type, index);

	अगर (!wq->ctrl)
		वापस -EINVAL;

	वापस 0;
पूर्ण


अटल पूर्णांक vnic_wq_alloc_ring(काष्ठा vnic_dev *vdev, काष्ठा vnic_wq *wq,
		अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size)
अणु
	वापस vnic_dev_alloc_desc_ring(vdev, &wq->ring, desc_count, desc_size);
पूर्ण


अटल पूर्णांक vnic_wq_alloc_bufs(काष्ठा vnic_wq *wq)
अणु
	काष्ठा vnic_wq_buf *buf;
	अचिन्हित पूर्णांक i, j, count = wq->ring.desc_count;
	अचिन्हित पूर्णांक blks = VNIC_WQ_BUF_BLKS_NEEDED(count);

	क्रम (i = 0; i < blks; i++) अणु
		wq->bufs[i] = kzalloc(VNIC_WQ_BUF_BLK_SZ, GFP_ATOMIC);
		अगर (!wq->bufs[i]) अणु
			prपूर्णांकk(KERN_ERR "Failed to alloc wq_bufs\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < blks; i++) अणु
		buf = wq->bufs[i];
		क्रम (j = 0; j < VNIC_WQ_BUF_BLK_ENTRIES; j++) अणु
			buf->index = i * VNIC_WQ_BUF_BLK_ENTRIES + j;
			buf->desc = (u8 *)wq->ring.descs +
				wq->ring.desc_size * buf->index;
			अगर (buf->index + 1 == count) अणु
				buf->next = wq->bufs[0];
				अवरोध;
			पूर्ण अन्यथा अगर (j + 1 == VNIC_WQ_BUF_BLK_ENTRIES) अणु
				buf->next = wq->bufs[i + 1];
			पूर्ण अन्यथा अणु
				buf->next = buf + 1;
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
		kमुक्त(wq->bufs[i]);
		wq->bufs[i] = शून्य;
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
		prपूर्णांकk(KERN_ERR "Failed to hook WQ[%d] resource\n", index);
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


पूर्णांक vnic_wq_devcmd2_alloc(काष्ठा vnic_dev *vdev, काष्ठा vnic_wq *wq,
		अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size)
अणु
	पूर्णांक err;

	wq->index = 0;
	wq->vdev = vdev;

	err = vnic_wq_get_ctrl(vdev, wq, 0, RES_TYPE_DEVCMD2);
	अगर (err) अणु
		pr_err("Failed to get devcmd2 resource\n");
		वापस err;
	पूर्ण
	vnic_wq_disable(wq);

	err = vnic_wq_alloc_ring(vdev, wq, desc_count, desc_size);
	अगर (err)
		वापस err;
	वापस 0;
पूर्ण

व्योम vnic_wq_init_start(काष्ठा vnic_wq *wq, अचिन्हित पूर्णांक cq_index,
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
		&wq->bufs[fetch_index / VNIC_WQ_BUF_BLK_ENTRIES]
		[fetch_index % VNIC_WQ_BUF_BLK_ENTRIES];
पूर्ण


व्योम vnic_wq_init(काष्ठा vnic_wq *wq, अचिन्हित पूर्णांक cq_index,
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
	ioग_लिखो32(0, &wq->ctrl->error_status);
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

	ioग_लिखो32(0, &wq->ctrl->enable);

	/* Wait क्रम HW to ACK disable request */
	क्रम (रुको = 0; रुको < 100; रुको++) अणु
		अगर (!(ioपढ़ो32(&wq->ctrl->running)))
			वापस 0;
		udelay(1);
	पूर्ण

	prपूर्णांकk(KERN_ERR "Failed to disable WQ[%d]\n", wq->index);

	वापस -ETIMEDOUT;
पूर्ण

व्योम vnic_wq_clean(काष्ठा vnic_wq *wq,
	व्योम (*buf_clean)(काष्ठा vnic_wq *wq, काष्ठा vnic_wq_buf *buf))
अणु
	काष्ठा vnic_wq_buf *buf;

	BUG_ON(ioपढ़ो32(&wq->ctrl->enable));

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
