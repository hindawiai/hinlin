<शैली गुरु>
/*
 * Copyright 2014 Cisco Systems, Inc.  All rights reserved.
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

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/slab.h>
#समावेश "vnic_resource.h"
#समावेश "vnic_devcmd.h"
#समावेश "vnic_dev.h"
#समावेश "vnic_stats.h"
#समावेश "vnic_wq.h"

#घोषणा VNIC_DVCMD_TMO	10000	/* Devcmd Timeout value */
#घोषणा VNIC_NOTIFY_INTR_MASK 0x0000ffff00000000ULL

काष्ठा devcmd2_controller अणु
	काष्ठा vnic_wq_ctrl __iomem *wq_ctrl;
	काष्ठा vnic_dev_ring results_ring;
	काष्ठा vnic_wq wq;
	काष्ठा vnic_devcmd2 *cmd_ring;
	काष्ठा devcmd2_result *result;
	u16 next_result;
	u16 result_size;
	पूर्णांक color;
पूर्ण;

काष्ठा vnic_res अणु
	व्योम __iomem *vaddr;
	अचिन्हित पूर्णांक count;
पूर्ण;

काष्ठा vnic_dev अणु
	व्योम *priv;
	काष्ठा pci_dev *pdev;
	काष्ठा vnic_res res[RES_TYPE_MAX];
	क्रमागत vnic_dev_पूर्णांकr_mode पूर्णांकr_mode;
	काष्ठा vnic_devcmd __iomem *devcmd;
	काष्ठा vnic_devcmd_notअगरy *notअगरy;
	काष्ठा vnic_devcmd_notअगरy notअगरy_copy;
	dma_addr_t notअगरy_pa;
	u32 *linkstatus;
	dma_addr_t linkstatus_pa;
	काष्ठा vnic_stats *stats;
	dma_addr_t stats_pa;
	काष्ठा vnic_devcmd_fw_info *fw_info;
	dma_addr_t fw_info_pa;
	u64 args[VNIC_DEVCMD_NARGS];
	काष्ठा devcmd2_controller *devcmd2;

	पूर्णांक (*devcmd_rtn)(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
			  पूर्णांक रुको);
पूर्ण;

#घोषणा VNIC_MAX_RES_HDR_SIZE \
	(माप(काष्ठा vnic_resource_header) + \
	माप(काष्ठा vnic_resource) * RES_TYPE_MAX)
#घोषणा VNIC_RES_STRIDE	128

व्योम *svnic_dev_priv(काष्ठा vnic_dev *vdev)
अणु
	वापस vdev->priv;
पूर्ण

अटल पूर्णांक vnic_dev_discover_res(काष्ठा vnic_dev *vdev,
	काष्ठा vnic_dev_bar *bar, अचिन्हित पूर्णांक num_bars)
अणु
	काष्ठा vnic_resource_header __iomem *rh;
	काष्ठा vnic_resource __iomem *r;
	u8 type;

	अगर (num_bars == 0)
		वापस -EINVAL;

	अगर (bar->len < VNIC_MAX_RES_HDR_SIZE) अणु
		pr_err("vNIC BAR0 res hdr length error\n");

		वापस -EINVAL;
	पूर्ण

	rh = bar->vaddr;
	अगर (!rh) अणु
		pr_err("vNIC BAR0 res hdr not mem-mapped\n");

		वापस -EINVAL;
	पूर्ण

	अगर (ioपढ़ो32(&rh->magic) != VNIC_RES_MAGIC ||
	    ioपढ़ो32(&rh->version) != VNIC_RES_VERSION) अणु
		pr_err("vNIC BAR0 res magic/version error exp (%lx/%lx) curr (%x/%x)\n",
			VNIC_RES_MAGIC, VNIC_RES_VERSION,
			ioपढ़ो32(&rh->magic), ioपढ़ो32(&rh->version));

		वापस -EINVAL;
	पूर्ण

	r = (काष्ठा vnic_resource __iomem *)(rh + 1);

	जबतक ((type = ioपढ़ो8(&r->type)) != RES_TYPE_EOL) अणु

		u8 bar_num = ioपढ़ो8(&r->bar);
		u32 bar_offset = ioपढ़ो32(&r->bar_offset);
		u32 count = ioपढ़ो32(&r->count);
		u32 len;

		r++;

		अगर (bar_num >= num_bars)
			जारी;

		अगर (!bar[bar_num].len || !bar[bar_num].vaddr)
			जारी;

		चयन (type) अणु
		हाल RES_TYPE_WQ:
		हाल RES_TYPE_RQ:
		हाल RES_TYPE_CQ:
		हाल RES_TYPE_INTR_CTRL:
			/* each count is stride bytes दीर्घ */
			len = count * VNIC_RES_STRIDE;
			अगर (len + bar_offset > bar->len) अणु
				pr_err("vNIC BAR0 resource %d out-of-bounds, offset 0x%x + size 0x%x > bar len 0x%lx\n",
					type, bar_offset,
					len,
					bar->len);

				वापस -EINVAL;
			पूर्ण
			अवरोध;

		हाल RES_TYPE_INTR_PBA_LEGACY:
		हाल RES_TYPE_DEVCMD:
		हाल RES_TYPE_DEVCMD2:
			len = count;
			अवरोध;

		शेष:
			जारी;
		पूर्ण

		vdev->res[type].count = count;
		vdev->res[type].vaddr = (अक्षर __iomem *)bar->vaddr + bar_offset;
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक svnic_dev_get_res_count(काष्ठा vnic_dev *vdev,
	क्रमागत vnic_res_type type)
अणु
	वापस vdev->res[type].count;
पूर्ण

व्योम __iomem *svnic_dev_get_res(काष्ठा vnic_dev *vdev, क्रमागत vnic_res_type type,
	अचिन्हित पूर्णांक index)
अणु
	अगर (!vdev->res[type].vaddr)
		वापस शून्य;

	चयन (type) अणु
	हाल RES_TYPE_WQ:
	हाल RES_TYPE_RQ:
	हाल RES_TYPE_CQ:
	हाल RES_TYPE_INTR_CTRL:
		वापस (अक्षर __iomem *)vdev->res[type].vaddr +
					index * VNIC_RES_STRIDE;

	शेष:
		वापस (अक्षर __iomem *)vdev->res[type].vaddr;
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक svnic_dev_desc_ring_size(काष्ठा vnic_dev_ring *ring,
				      अचिन्हित पूर्णांक desc_count,
				      अचिन्हित पूर्णांक desc_size)
अणु
	/* The base address of the desc rings must be 512 byte aligned.
	 * Descriptor count is aligned to groups of 32 descriptors.  A
	 * count of 0 means the maximum 4096 descriptors.  Descriptor
	 * size is aligned to 16 bytes.
	 */

	अचिन्हित पूर्णांक count_align = 32;
	अचिन्हित पूर्णांक desc_align = 16;

	ring->base_align = 512;

	अगर (desc_count == 0)
		desc_count = 4096;

	ring->desc_count = ALIGN(desc_count, count_align);

	ring->desc_size = ALIGN(desc_size, desc_align);

	ring->size = ring->desc_count * ring->desc_size;
	ring->size_unaligned = ring->size + ring->base_align;

	वापस ring->size_unaligned;
पूर्ण

व्योम svnic_dev_clear_desc_ring(काष्ठा vnic_dev_ring *ring)
अणु
	स_रखो(ring->descs, 0, ring->size);
पूर्ण

पूर्णांक svnic_dev_alloc_desc_ring(काष्ठा vnic_dev *vdev, काष्ठा vnic_dev_ring *ring,
	अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size)
अणु
	svnic_dev_desc_ring_size(ring, desc_count, desc_size);

	ring->descs_unaligned = dma_alloc_coherent(&vdev->pdev->dev,
			ring->size_unaligned, &ring->base_addr_unaligned,
			GFP_KERNEL);
	अगर (!ring->descs_unaligned) अणु
		pr_err("Failed to allocate ring (size=%d), aborting\n",
			(पूर्णांक)ring->size);

		वापस -ENOMEM;
	पूर्ण

	ring->base_addr = ALIGN(ring->base_addr_unaligned,
		ring->base_align);
	ring->descs = (u8 *)ring->descs_unaligned +
		(ring->base_addr - ring->base_addr_unaligned);

	svnic_dev_clear_desc_ring(ring);

	ring->desc_avail = ring->desc_count - 1;

	वापस 0;
पूर्ण

व्योम svnic_dev_मुक्त_desc_ring(काष्ठा vnic_dev *vdev, काष्ठा vnic_dev_ring *ring)
अणु
	अगर (ring->descs) अणु
		dma_मुक्त_coherent(&vdev->pdev->dev,
			ring->size_unaligned,
			ring->descs_unaligned,
			ring->base_addr_unaligned);
		ring->descs = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक _svnic_dev_cmd2(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
	पूर्णांक रुको)
अणु
	काष्ठा devcmd2_controller *dc2c = vdev->devcmd2;
	काष्ठा devcmd2_result *result = शून्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक delay;
	पूर्णांक err;
	u32 posted;
	u32 fetch_idx;
	u32 new_posted;
	u8 color;

	fetch_idx = ioपढ़ो32(&dc2c->wq_ctrl->fetch_index);
	अगर (fetch_idx == 0xFFFFFFFF) अणु /* check क्रम hardware gone  */
		/* Hardware surprise removal: वापस error */
		वापस -ENODEV;
	पूर्ण

	posted = ioपढ़ो32(&dc2c->wq_ctrl->posted_index);

	अगर (posted == 0xFFFFFFFF) अणु /* check क्रम hardware gone  */
		/* Hardware surprise removal: वापस error */
		वापस -ENODEV;
	पूर्ण

	new_posted = (posted + 1) % DEVCMD2_RING_SIZE;
	अगर (new_posted == fetch_idx) अणु
		pr_err("%s: wq is full while issuing devcmd2 command %d, fetch index: %u, posted index: %u\n",
			pci_name(vdev->pdev), _CMD_N(cmd), fetch_idx, posted);

		वापस -EBUSY;
	पूर्ण

	dc2c->cmd_ring[posted].cmd = cmd;
	dc2c->cmd_ring[posted].flags = 0;

	अगर ((_CMD_FLAGS(cmd) & _CMD_FLAGS_NOWAIT))
		dc2c->cmd_ring[posted].flags |= DEVCMD2_FNORESULT;

	अगर (_CMD_सूची(cmd) & _CMD_सूची_WRITE) अणु
		क्रम (i = 0; i < VNIC_DEVCMD_NARGS; i++)
			dc2c->cmd_ring[posted].args[i] = vdev->args[i];
	पूर्ण
	/* Adding ग_लिखो memory barrier prevents compiler and/or CPU
	 * reordering, thus aव्योमing descriptor posting beक्रमe
	 * descriptor is initialized. Otherwise, hardware can पढ़ो
	 * stale descriptor fields.
	 */
	wmb();
	ioग_लिखो32(new_posted, &dc2c->wq_ctrl->posted_index);

	अगर (dc2c->cmd_ring[posted].flags & DEVCMD2_FNORESULT)
		वापस 0;

	result = dc2c->result + dc2c->next_result;
	color = dc2c->color;

	/*
	 * Increment next_result, after posting the devcmd, irrespective of
	 * devcmd result, and it should be करोne only once.
	 */
	dc2c->next_result++;
	अगर (dc2c->next_result == dc2c->result_size) अणु
		dc2c->next_result = 0;
		dc2c->color = dc2c->color ? 0 : 1;
	पूर्ण

	क्रम (delay = 0; delay < रुको; delay++) अणु
		udelay(100);
		अगर (result->color == color) अणु
			अगर (result->error) अणु
				err = (पूर्णांक) result->error;
				अगर (err != ERR_ECMDUNKNOWN ||
				    cmd != CMD_CAPABILITY)
					pr_err("Error %d devcmd %d\n",
						err, _CMD_N(cmd));

				वापस err;
			पूर्ण
			अगर (_CMD_सूची(cmd) & _CMD_सूची_READ) अणु
				क्रम (i = 0; i < VNIC_DEVCMD_NARGS; i++)
					vdev->args[i] = result->results[i];
			पूर्ण

			वापस 0;
		पूर्ण
	पूर्ण

	pr_err("Timed out devcmd %d\n", _CMD_N(cmd));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक svnic_dev_init_devcmd2(काष्ठा vnic_dev *vdev)
अणु
	काष्ठा devcmd2_controller *dc2c = शून्य;
	अचिन्हित पूर्णांक fetch_idx;
	पूर्णांक ret;
	व्योम __iomem *p;

	अगर (vdev->devcmd2)
		वापस 0;

	p = svnic_dev_get_res(vdev, RES_TYPE_DEVCMD2, 0);
	अगर (!p)
		वापस -ENODEV;

	dc2c = kzalloc(माप(*dc2c), GFP_ATOMIC);
	अगर (!dc2c)
		वापस -ENOMEM;

	vdev->devcmd2 = dc2c;

	dc2c->color = 1;
	dc2c->result_size = DEVCMD2_RING_SIZE;

	ret  = vnic_wq_devcmd2_alloc(vdev,
				     &dc2c->wq,
				     DEVCMD2_RING_SIZE,
				     DEVCMD2_DESC_SIZE);
	अगर (ret)
		जाओ err_मुक्त_devcmd2;

	fetch_idx = ioपढ़ो32(&dc2c->wq.ctrl->fetch_index);
	अगर (fetch_idx == 0xFFFFFFFF) अणु /* check क्रम hardware gone  */
		/* Hardware surprise removal: reset fetch_index */
		fetch_idx = 0;
	पूर्ण

	/*
	 * Don't change fetch_index ever and
	 * set posted_index same as fetch_index
	 * when setting up the WQ क्रम devcmd2.
	 */
	vnic_wq_init_start(&dc2c->wq, 0, fetch_idx, fetch_idx, 0, 0);
	svnic_wq_enable(&dc2c->wq);
	ret = svnic_dev_alloc_desc_ring(vdev,
					&dc2c->results_ring,
					DEVCMD2_RING_SIZE,
					DEVCMD2_DESC_SIZE);
	अगर (ret)
		जाओ err_मुक्त_wq;

	dc2c->result = (काष्ठा devcmd2_result *) dc2c->results_ring.descs;
	dc2c->cmd_ring = (काष्ठा vnic_devcmd2 *) dc2c->wq.ring.descs;
	dc2c->wq_ctrl = dc2c->wq.ctrl;
	vdev->args[0] = (u64) dc2c->results_ring.base_addr | VNIC_PADDR_TARGET;
	vdev->args[1] = DEVCMD2_RING_SIZE;

	ret = _svnic_dev_cmd2(vdev, CMD_INITIALIZE_DEVCMD2, VNIC_DVCMD_TMO);
	अगर (ret < 0)
		जाओ err_मुक्त_desc_ring;

	vdev->devcmd_rtn = &_svnic_dev_cmd2;
	pr_info("DEVCMD2 Initialized.\n");

	वापस ret;

err_मुक्त_desc_ring:
	svnic_dev_मुक्त_desc_ring(vdev, &dc2c->results_ring);

err_मुक्त_wq:
	svnic_wq_disable(&dc2c->wq);
	svnic_wq_मुक्त(&dc2c->wq);

err_मुक्त_devcmd2:
	kमुक्त(dc2c);
	vdev->devcmd2 = शून्य;

	वापस ret;
पूर्ण /* end of svnic_dev_init_devcmd2 */

अटल व्योम vnic_dev_deinit_devcmd2(काष्ठा vnic_dev *vdev)
अणु
	काष्ठा devcmd2_controller *dc2c = vdev->devcmd2;

	vdev->devcmd2 = शून्य;
	vdev->devcmd_rtn = शून्य;

	svnic_dev_मुक्त_desc_ring(vdev, &dc2c->results_ring);
	svnic_wq_disable(&dc2c->wq);
	svnic_wq_मुक्त(&dc2c->wq);
	kमुक्त(dc2c);
पूर्ण

पूर्णांक svnic_dev_cmd(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
	u64 *a0, u64 *a1, पूर्णांक रुको)
अणु
	पूर्णांक err;

	स_रखो(vdev->args, 0, माप(vdev->args));
	vdev->args[0] = *a0;
	vdev->args[1] = *a1;

	err = (*vdev->devcmd_rtn)(vdev, cmd, रुको);

	*a0 = vdev->args[0];
	*a1 = vdev->args[1];

	वापस  err;
पूर्ण

पूर्णांक svnic_dev_fw_info(काष्ठा vnic_dev *vdev,
	काष्ठा vnic_devcmd_fw_info **fw_info)
अणु
	u64 a0, a1 = 0;
	पूर्णांक रुको = VNIC_DVCMD_TMO;
	पूर्णांक err = 0;

	अगर (!vdev->fw_info) अणु
		vdev->fw_info = dma_alloc_coherent(&vdev->pdev->dev,
			माप(काष्ठा vnic_devcmd_fw_info),
			&vdev->fw_info_pa, GFP_KERNEL);
		अगर (!vdev->fw_info)
			वापस -ENOMEM;

		a0 = vdev->fw_info_pa;

		/* only get fw_info once and cache it */
		err = svnic_dev_cmd(vdev, CMD_MCPU_FW_INFO, &a0, &a1, रुको);
	पूर्ण

	*fw_info = vdev->fw_info;

	वापस err;
पूर्ण

पूर्णांक svnic_dev_spec(काष्ठा vnic_dev *vdev, अचिन्हित पूर्णांक offset,
	अचिन्हित पूर्णांक size, व्योम *value)
अणु
	u64 a0, a1;
	पूर्णांक रुको = VNIC_DVCMD_TMO;
	पूर्णांक err;

	a0 = offset;
	a1 = size;

	err = svnic_dev_cmd(vdev, CMD_DEV_SPEC, &a0, &a1, रुको);

	चयन (size) अणु
	हाल 1:
		*(u8 *)value = (u8)a0;
		अवरोध;
	हाल 2:
		*(u16 *)value = (u16)a0;
		अवरोध;
	हाल 4:
		*(u32 *)value = (u32)a0;
		अवरोध;
	हाल 8:
		*(u64 *)value = a0;
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक svnic_dev_stats_clear(काष्ठा vnic_dev *vdev)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = VNIC_DVCMD_TMO;

	वापस svnic_dev_cmd(vdev, CMD_STATS_CLEAR, &a0, &a1, रुको);
पूर्ण

पूर्णांक svnic_dev_stats_dump(काष्ठा vnic_dev *vdev, काष्ठा vnic_stats **stats)
अणु
	u64 a0, a1;
	पूर्णांक रुको = VNIC_DVCMD_TMO;

	अगर (!vdev->stats) अणु
		vdev->stats = dma_alloc_coherent(&vdev->pdev->dev,
			माप(काष्ठा vnic_stats), &vdev->stats_pa, GFP_KERNEL);
		अगर (!vdev->stats)
			वापस -ENOMEM;
	पूर्ण

	*stats = vdev->stats;
	a0 = vdev->stats_pa;
	a1 = माप(काष्ठा vnic_stats);

	वापस svnic_dev_cmd(vdev, CMD_STATS_DUMP, &a0, &a1, रुको);
पूर्ण

पूर्णांक svnic_dev_बंद(काष्ठा vnic_dev *vdev)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = VNIC_DVCMD_TMO;

	वापस svnic_dev_cmd(vdev, CMD_CLOSE, &a0, &a1, रुको);
पूर्ण

पूर्णांक svnic_dev_enable_रुको(काष्ठा vnic_dev *vdev)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = VNIC_DVCMD_TMO;
	पूर्णांक err = 0;

	err = svnic_dev_cmd(vdev, CMD_ENABLE_WAIT, &a0, &a1, रुको);
	अगर (err == ERR_ECMDUNKNOWN)
		वापस svnic_dev_cmd(vdev, CMD_ENABLE, &a0, &a1, रुको);

	वापस err;
पूर्ण

पूर्णांक svnic_dev_disable(काष्ठा vnic_dev *vdev)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = VNIC_DVCMD_TMO;

	वापस svnic_dev_cmd(vdev, CMD_DISABLE, &a0, &a1, रुको);
पूर्ण

पूर्णांक svnic_dev_खोलो(काष्ठा vnic_dev *vdev, पूर्णांक arg)
अणु
	u64 a0 = (u32)arg, a1 = 0;
	पूर्णांक रुको = VNIC_DVCMD_TMO;

	वापस svnic_dev_cmd(vdev, CMD_OPEN, &a0, &a1, रुको);
पूर्ण

पूर्णांक svnic_dev_खोलो_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *करोne)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = VNIC_DVCMD_TMO;
	पूर्णांक err;

	*करोne = 0;

	err = svnic_dev_cmd(vdev, CMD_OPEN_STATUS, &a0, &a1, रुको);
	अगर (err)
		वापस err;

	*करोne = (a0 == 0);

	वापस 0;
पूर्ण

पूर्णांक svnic_dev_notअगरy_set(काष्ठा vnic_dev *vdev, u16 पूर्णांकr)
अणु
	u64 a0, a1;
	पूर्णांक रुको = VNIC_DVCMD_TMO;

	अगर (!vdev->notअगरy) अणु
		vdev->notअगरy = dma_alloc_coherent(&vdev->pdev->dev,
			माप(काष्ठा vnic_devcmd_notअगरy),
			&vdev->notअगरy_pa, GFP_KERNEL);
		अगर (!vdev->notअगरy)
			वापस -ENOMEM;
	पूर्ण

	a0 = vdev->notअगरy_pa;
	a1 = ((u64)पूर्णांकr << 32) & VNIC_NOTIFY_INTR_MASK;
	a1 += माप(काष्ठा vnic_devcmd_notअगरy);

	वापस svnic_dev_cmd(vdev, CMD_NOTIFY, &a0, &a1, रुको);
पूर्ण

व्योम svnic_dev_notअगरy_unset(काष्ठा vnic_dev *vdev)
अणु
	u64 a0, a1;
	पूर्णांक रुको = VNIC_DVCMD_TMO;

	a0 = 0;  /* paddr = 0 to unset notअगरy buffer */
	a1 = VNIC_NOTIFY_INTR_MASK; /* पूर्णांकr num = -1 to unreg क्रम पूर्णांकr */
	a1 += माप(काष्ठा vnic_devcmd_notअगरy);

	svnic_dev_cmd(vdev, CMD_NOTIFY, &a0, &a1, रुको);
पूर्ण

अटल पूर्णांक vnic_dev_notअगरy_पढ़ोy(काष्ठा vnic_dev *vdev)
अणु
	u32 *words;
	अचिन्हित पूर्णांक nwords = माप(काष्ठा vnic_devcmd_notअगरy) / 4;
	अचिन्हित पूर्णांक i;
	u32 csum;

	अगर (!vdev->notअगरy)
		वापस 0;

	करो अणु
		csum = 0;
		स_नकल(&vdev->notअगरy_copy, vdev->notअगरy,
			माप(काष्ठा vnic_devcmd_notअगरy));
		words = (u32 *)&vdev->notअगरy_copy;
		क्रम (i = 1; i < nwords; i++)
			csum += words[i];
	पूर्ण जबतक (csum != words[0]);

	वापस 1;
पूर्ण

पूर्णांक svnic_dev_init(काष्ठा vnic_dev *vdev, पूर्णांक arg)
अणु
	u64 a0 = (u32)arg, a1 = 0;
	पूर्णांक रुको = VNIC_DVCMD_TMO;

	वापस svnic_dev_cmd(vdev, CMD_INIT, &a0, &a1, रुको);
पूर्ण

पूर्णांक svnic_dev_link_status(काष्ठा vnic_dev *vdev)
अणु
	अगर (vdev->linkstatus)
		वापस *vdev->linkstatus;

	अगर (!vnic_dev_notअगरy_पढ़ोy(vdev))
		वापस 0;

	वापस vdev->notअगरy_copy.link_state;
पूर्ण

u32 svnic_dev_link_करोwn_cnt(काष्ठा vnic_dev *vdev)
अणु
	अगर (!vnic_dev_notअगरy_पढ़ोy(vdev))
		वापस 0;

	वापस vdev->notअगरy_copy.link_करोwn_cnt;
पूर्ण

व्योम svnic_dev_set_पूर्णांकr_mode(काष्ठा vnic_dev *vdev,
	क्रमागत vnic_dev_पूर्णांकr_mode पूर्णांकr_mode)
अणु
	vdev->पूर्णांकr_mode = पूर्णांकr_mode;
पूर्ण

क्रमागत vnic_dev_पूर्णांकr_mode svnic_dev_get_पूर्णांकr_mode(काष्ठा vnic_dev *vdev)
अणु
	वापस vdev->पूर्णांकr_mode;
पूर्ण

व्योम svnic_dev_unरेजिस्टर(काष्ठा vnic_dev *vdev)
अणु
	अगर (vdev) अणु
		अगर (vdev->notअगरy)
			dma_मुक्त_coherent(&vdev->pdev->dev,
				माप(काष्ठा vnic_devcmd_notअगरy),
				vdev->notअगरy,
				vdev->notअगरy_pa);
		अगर (vdev->linkstatus)
			dma_मुक्त_coherent(&vdev->pdev->dev,
				माप(u32),
				vdev->linkstatus,
				vdev->linkstatus_pa);
		अगर (vdev->stats)
			dma_मुक्त_coherent(&vdev->pdev->dev,
				माप(काष्ठा vnic_stats),
				vdev->stats, vdev->stats_pa);
		अगर (vdev->fw_info)
			dma_मुक्त_coherent(&vdev->pdev->dev,
				माप(काष्ठा vnic_devcmd_fw_info),
				vdev->fw_info, vdev->fw_info_pa);
		अगर (vdev->devcmd2)
			vnic_dev_deinit_devcmd2(vdev);
		kमुक्त(vdev);
	पूर्ण
पूर्ण

काष्ठा vnic_dev *svnic_dev_alloc_discover(काष्ठा vnic_dev *vdev,
					  व्योम *priv,
					  काष्ठा pci_dev *pdev,
					  काष्ठा vnic_dev_bar *bar,
					  अचिन्हित पूर्णांक num_bars)
अणु
	अगर (!vdev) अणु
		vdev = kzalloc(माप(काष्ठा vnic_dev), GFP_ATOMIC);
		अगर (!vdev)
			वापस शून्य;
	पूर्ण

	vdev->priv = priv;
	vdev->pdev = pdev;

	अगर (vnic_dev_discover_res(vdev, bar, num_bars))
		जाओ err_out;

	वापस vdev;

err_out:
	svnic_dev_unरेजिस्टर(vdev);

	वापस शून्य;
पूर्ण /* end of svnic_dev_alloc_discover */

/*
 * fallback option is left to keep the पूर्णांकerface common क्रम other vnics.
 */
पूर्णांक svnic_dev_cmd_init(काष्ठा vnic_dev *vdev, पूर्णांक fallback)
अणु
	पूर्णांक err = -ENODEV;
	व्योम __iomem *p;

	p = svnic_dev_get_res(vdev, RES_TYPE_DEVCMD2, 0);
	अगर (p)
		err = svnic_dev_init_devcmd2(vdev);
	अन्यथा
		pr_err("DEVCMD2 resource not found.\n");

	वापस err;
पूर्ण /* end of svnic_dev_cmd_init */
