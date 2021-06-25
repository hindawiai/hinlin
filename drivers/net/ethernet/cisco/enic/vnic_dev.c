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
#समावेश <linux/अगर_ether.h>

#समावेश "vnic_resource.h"
#समावेश "vnic_devcmd.h"
#समावेश "vnic_dev.h"
#समावेश "vnic_wq.h"
#समावेश "vnic_stats.h"
#समावेश "enic.h"

#घोषणा VNIC_MAX_RES_HDR_SIZE \
	(माप(काष्ठा vnic_resource_header) + \
	माप(काष्ठा vnic_resource) * RES_TYPE_MAX)
#घोषणा VNIC_RES_STRIDE	128

व्योम *vnic_dev_priv(काष्ठा vnic_dev *vdev)
अणु
	वापस vdev->priv;
पूर्ण

अटल पूर्णांक vnic_dev_discover_res(काष्ठा vnic_dev *vdev,
	काष्ठा vnic_dev_bar *bar, अचिन्हित पूर्णांक num_bars)
अणु
	काष्ठा vnic_resource_header __iomem *rh;
	काष्ठा mgmt_barmap_hdr __iomem *mrh;
	काष्ठा vnic_resource __iomem *r;
	u8 type;

	अगर (num_bars == 0)
		वापस -EINVAL;

	अगर (bar->len < VNIC_MAX_RES_HDR_SIZE) अणु
		vdev_err(vdev, "vNIC BAR0 res hdr length error\n");
		वापस -EINVAL;
	पूर्ण

	rh  = bar->vaddr;
	mrh = bar->vaddr;
	अगर (!rh) अणु
		vdev_err(vdev, "vNIC BAR0 res hdr not mem-mapped\n");
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम mgmt vnic in addition to normal vnic */
	अगर ((ioपढ़ो32(&rh->magic) != VNIC_RES_MAGIC) ||
		(ioपढ़ो32(&rh->version) != VNIC_RES_VERSION)) अणु
		अगर ((ioपढ़ो32(&mrh->magic) != MGMTVNIC_MAGIC) ||
			(ioपढ़ो32(&mrh->version) != MGMTVNIC_VERSION)) अणु
			vdev_err(vdev, "vNIC BAR0 res magic/version error exp (%lx/%lx) or (%lx/%lx), curr (%x/%x)\n",
				 VNIC_RES_MAGIC, VNIC_RES_VERSION,
				 MGMTVNIC_MAGIC, MGMTVNIC_VERSION,
				 ioपढ़ो32(&rh->magic), ioपढ़ो32(&rh->version));
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (ioपढ़ो32(&mrh->magic) == MGMTVNIC_MAGIC)
		r = (काष्ठा vnic_resource __iomem *)(mrh + 1);
	अन्यथा
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
			अगर (len + bar_offset > bar[bar_num].len) अणु
				vdev_err(vdev, "vNIC BAR0 resource %d out-of-bounds, offset 0x%x + size 0x%x > bar len 0x%lx\n",
					 type, bar_offset, len,
					 bar[bar_num].len);
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
		vdev->res[type].vaddr = (अक्षर __iomem *)bar[bar_num].vaddr +
			bar_offset;
		vdev->res[type].bus_addr = bar[bar_num].bus_addr + bar_offset;
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक vnic_dev_get_res_count(काष्ठा vnic_dev *vdev,
	क्रमागत vnic_res_type type)
अणु
	वापस vdev->res[type].count;
पूर्ण
EXPORT_SYMBOL(vnic_dev_get_res_count);

व्योम __iomem *vnic_dev_get_res(काष्ठा vnic_dev *vdev, क्रमागत vnic_res_type type,
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
EXPORT_SYMBOL(vnic_dev_get_res);

अटल अचिन्हित पूर्णांक vnic_dev_desc_ring_size(काष्ठा vnic_dev_ring *ring,
	अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size)
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

व्योम vnic_dev_clear_desc_ring(काष्ठा vnic_dev_ring *ring)
अणु
	स_रखो(ring->descs, 0, ring->size);
पूर्ण

पूर्णांक vnic_dev_alloc_desc_ring(काष्ठा vnic_dev *vdev, काष्ठा vnic_dev_ring *ring,
	अचिन्हित पूर्णांक desc_count, अचिन्हित पूर्णांक desc_size)
अणु
	vnic_dev_desc_ring_size(ring, desc_count, desc_size);

	ring->descs_unaligned = dma_alloc_coherent(&vdev->pdev->dev,
						   ring->size_unaligned,
						   &ring->base_addr_unaligned,
						   GFP_KERNEL);

	अगर (!ring->descs_unaligned) अणु
		vdev_err(vdev, "Failed to allocate ring (size=%d), aborting\n",
			 (पूर्णांक)ring->size);
		वापस -ENOMEM;
	पूर्ण

	ring->base_addr = ALIGN(ring->base_addr_unaligned,
		ring->base_align);
	ring->descs = (u8 *)ring->descs_unaligned +
		(ring->base_addr - ring->base_addr_unaligned);

	vnic_dev_clear_desc_ring(ring);

	ring->desc_avail = ring->desc_count - 1;

	वापस 0;
पूर्ण

व्योम vnic_dev_मुक्त_desc_ring(काष्ठा vnic_dev *vdev, काष्ठा vnic_dev_ring *ring)
अणु
	अगर (ring->descs) अणु
		dma_मुक्त_coherent(&vdev->pdev->dev, ring->size_unaligned,
				  ring->descs_unaligned,
				  ring->base_addr_unaligned);
		ring->descs = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक _vnic_dev_cmd(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
	पूर्णांक रुको)
अणु
	काष्ठा vnic_devcmd __iomem *devcmd = vdev->devcmd;
	अचिन्हित पूर्णांक i;
	पूर्णांक delay;
	u32 status;
	पूर्णांक err;

	status = ioपढ़ो32(&devcmd->status);
	अगर (status == 0xFFFFFFFF) अणु
		/* PCI-e target device is gone */
		वापस -ENODEV;
	पूर्ण
	अगर (status & STAT_BUSY) अणु
		vdev_neterr(vdev, "Busy devcmd %d\n", _CMD_N(cmd));
		वापस -EBUSY;
	पूर्ण

	अगर (_CMD_सूची(cmd) & _CMD_सूची_WRITE) अणु
		क्रम (i = 0; i < VNIC_DEVCMD_NARGS; i++)
			ग_लिखोq(vdev->args[i], &devcmd->args[i]);
		wmb();
	पूर्ण

	ioग_लिखो32(cmd, &devcmd->cmd);

	अगर ((_CMD_FLAGS(cmd) & _CMD_FLAGS_NOWAIT))
		वापस 0;

	क्रम (delay = 0; delay < रुको; delay++) अणु

		udelay(100);

		status = ioपढ़ो32(&devcmd->status);
		अगर (status == 0xFFFFFFFF) अणु
			/* PCI-e target device is gone */
			वापस -ENODEV;
		पूर्ण

		अगर (!(status & STAT_BUSY)) अणु

			अगर (status & STAT_ERROR) अणु
				err = (पूर्णांक)पढ़ोq(&devcmd->args[0]);
				अगर (err == ERR_EINVAL &&
				    cmd == CMD_CAPABILITY)
					वापस -err;
				अगर (err != ERR_ECMDUNKNOWN ||
				    cmd != CMD_CAPABILITY)
					vdev_neterr(vdev, "Error %d devcmd %d\n",
						    err, _CMD_N(cmd));
				वापस -err;
			पूर्ण

			अगर (_CMD_सूची(cmd) & _CMD_सूची_READ) अणु
				rmb();
				क्रम (i = 0; i < VNIC_DEVCMD_NARGS; i++)
					vdev->args[i] = पढ़ोq(&devcmd->args[i]);
			पूर्ण

			वापस 0;
		पूर्ण
	पूर्ण

	vdev_neterr(vdev, "Timedout devcmd %d\n", _CMD_N(cmd));
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक _vnic_dev_cmd2(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
			  पूर्णांक रुको)
अणु
	काष्ठा devcmd2_controller *dc2c = vdev->devcmd2;
	काष्ठा devcmd2_result *result;
	u8 color;
	अचिन्हित पूर्णांक i;
	पूर्णांक delay, err;
	u32 fetch_index, new_posted;
	u32 posted = dc2c->posted;

	fetch_index = ioपढ़ो32(&dc2c->wq_ctrl->fetch_index);

	अगर (fetch_index == 0xFFFFFFFF)
		वापस -ENODEV;

	new_posted = (posted + 1) % DEVCMD2_RING_SIZE;

	अगर (new_posted == fetch_index) अणु
		vdev_neterr(vdev, "devcmd2 %d: wq is full. fetch index: %u, posted index: %u\n",
			    _CMD_N(cmd), fetch_index, posted);
		वापस -EBUSY;
	पूर्ण
	dc2c->cmd_ring[posted].cmd = cmd;
	dc2c->cmd_ring[posted].flags = 0;

	अगर ((_CMD_FLAGS(cmd) & _CMD_FLAGS_NOWAIT))
		dc2c->cmd_ring[posted].flags |= DEVCMD2_FNORESULT;
	अगर (_CMD_सूची(cmd) & _CMD_सूची_WRITE)
		क्रम (i = 0; i < VNIC_DEVCMD_NARGS; i++)
			dc2c->cmd_ring[posted].args[i] = vdev->args[i];

	/* Adding ग_लिखो memory barrier prevents compiler and/or CPU reordering,
	 * thus aव्योमing descriptor posting beक्रमe descriptor is initialized.
	 * Otherwise, hardware can पढ़ो stale descriptor fields.
	 */
	wmb();
	ioग_लिखो32(new_posted, &dc2c->wq_ctrl->posted_index);
	dc2c->posted = new_posted;

	अगर (dc2c->cmd_ring[posted].flags & DEVCMD2_FNORESULT)
		वापस 0;

	result = dc2c->result + dc2c->next_result;
	color = dc2c->color;

	dc2c->next_result++;
	अगर (dc2c->next_result == dc2c->result_size) अणु
		dc2c->next_result = 0;
		dc2c->color = dc2c->color ? 0 : 1;
	पूर्ण

	क्रम (delay = 0; delay < रुको; delay++) अणु
		अगर (result->color == color) अणु
			अगर (result->error) अणु
				err = result->error;
				अगर (err != ERR_ECMDUNKNOWN ||
				    cmd != CMD_CAPABILITY)
					vdev_neterr(vdev, "Error %d devcmd %d\n",
						    err, _CMD_N(cmd));
				वापस -err;
			पूर्ण
			अगर (_CMD_सूची(cmd) & _CMD_सूची_READ)
				क्रम (i = 0; i < VNIC_DEVCMD2_NARGS; i++)
					vdev->args[i] = result->results[i];

			वापस 0;
		पूर्ण
		udelay(100);
	पूर्ण

	vdev_neterr(vdev, "devcmd %d timed out\n", _CMD_N(cmd));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक vnic_dev_init_devcmd1(काष्ठा vnic_dev *vdev)
अणु
	vdev->devcmd = vnic_dev_get_res(vdev, RES_TYPE_DEVCMD, 0);
	अगर (!vdev->devcmd)
		वापस -ENODEV;
	vdev->devcmd_rtn = _vnic_dev_cmd;

	वापस 0;
पूर्ण

अटल पूर्णांक vnic_dev_init_devcmd2(काष्ठा vnic_dev *vdev)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक fetch_index;

	अगर (vdev->devcmd2)
		वापस 0;

	vdev->devcmd2 = kzalloc(माप(*vdev->devcmd2), GFP_KERNEL);
	अगर (!vdev->devcmd2)
		वापस -ENOMEM;

	vdev->devcmd2->color = 1;
	vdev->devcmd2->result_size = DEVCMD2_RING_SIZE;
	err = enic_wq_devcmd2_alloc(vdev, &vdev->devcmd2->wq, DEVCMD2_RING_SIZE,
				    DEVCMD2_DESC_SIZE);
	अगर (err)
		जाओ err_मुक्त_devcmd2;

	fetch_index = ioपढ़ो32(&vdev->devcmd2->wq.ctrl->fetch_index);
	अगर (fetch_index == 0xFFFFFFFF) अणु /* check क्रम hardware gone  */
		vdev_err(vdev, "Fatal error in devcmd2 init - hardware surprise removal\n");
		err = -ENODEV;
		जाओ err_मुक्त_wq;
	पूर्ण

	enic_wq_init_start(&vdev->devcmd2->wq, 0, fetch_index, fetch_index, 0,
			   0);
	vdev->devcmd2->posted = fetch_index;
	vnic_wq_enable(&vdev->devcmd2->wq);

	err = vnic_dev_alloc_desc_ring(vdev, &vdev->devcmd2->results_ring,
				       DEVCMD2_RING_SIZE, DEVCMD2_DESC_SIZE);
	अगर (err)
		जाओ err_disable_wq;

	vdev->devcmd2->result = vdev->devcmd2->results_ring.descs;
	vdev->devcmd2->cmd_ring = vdev->devcmd2->wq.ring.descs;
	vdev->devcmd2->wq_ctrl = vdev->devcmd2->wq.ctrl;
	vdev->args[0] = (u64)vdev->devcmd2->results_ring.base_addr |
			VNIC_PADDR_TARGET;
	vdev->args[1] = DEVCMD2_RING_SIZE;

	err = _vnic_dev_cmd2(vdev, CMD_INITIALIZE_DEVCMD2, 1000);
	अगर (err)
		जाओ err_मुक्त_desc_ring;

	vdev->devcmd_rtn = _vnic_dev_cmd2;

	वापस 0;

err_मुक्त_desc_ring:
	vnic_dev_मुक्त_desc_ring(vdev, &vdev->devcmd2->results_ring);
err_disable_wq:
	vnic_wq_disable(&vdev->devcmd2->wq);
err_मुक्त_wq:
	vnic_wq_मुक्त(&vdev->devcmd2->wq);
err_मुक्त_devcmd2:
	kमुक्त(vdev->devcmd2);
	vdev->devcmd2 = शून्य;

	वापस err;
पूर्ण

अटल व्योम vnic_dev_deinit_devcmd2(काष्ठा vnic_dev *vdev)
अणु
	vnic_dev_मुक्त_desc_ring(vdev, &vdev->devcmd2->results_ring);
	vnic_wq_disable(&vdev->devcmd2->wq);
	vnic_wq_मुक्त(&vdev->devcmd2->wq);
	kमुक्त(vdev->devcmd2);
पूर्ण

अटल पूर्णांक vnic_dev_cmd_proxy(काष्ठा vnic_dev *vdev,
	क्रमागत vnic_devcmd_cmd proxy_cmd, क्रमागत vnic_devcmd_cmd cmd,
	u64 *a0, u64 *a1, पूर्णांक रुको)
अणु
	u32 status;
	पूर्णांक err;

	स_रखो(vdev->args, 0, माप(vdev->args));

	vdev->args[0] = vdev->proxy_index;
	vdev->args[1] = cmd;
	vdev->args[2] = *a0;
	vdev->args[3] = *a1;

	err = vdev->devcmd_rtn(vdev, proxy_cmd, रुको);
	अगर (err)
		वापस err;

	status = (u32)vdev->args[0];
	अगर (status & STAT_ERROR) अणु
		err = (पूर्णांक)vdev->args[1];
		अगर (err != ERR_ECMDUNKNOWN ||
		    cmd != CMD_CAPABILITY)
			vdev_neterr(vdev, "Error %d proxy devcmd %d\n",
				    err, _CMD_N(cmd));
		वापस err;
	पूर्ण

	*a0 = vdev->args[1];
	*a1 = vdev->args[2];

	वापस 0;
पूर्ण

अटल पूर्णांक vnic_dev_cmd_no_proxy(काष्ठा vnic_dev *vdev,
	क्रमागत vnic_devcmd_cmd cmd, u64 *a0, u64 *a1, पूर्णांक रुको)
अणु
	पूर्णांक err;

	vdev->args[0] = *a0;
	vdev->args[1] = *a1;

	err = vdev->devcmd_rtn(vdev, cmd, रुको);

	*a0 = vdev->args[0];
	*a1 = vdev->args[1];

	वापस err;
पूर्ण

व्योम vnic_dev_cmd_proxy_by_index_start(काष्ठा vnic_dev *vdev, u16 index)
अणु
	vdev->proxy = PROXY_BY_INDEX;
	vdev->proxy_index = index;
पूर्ण

व्योम vnic_dev_cmd_proxy_end(काष्ठा vnic_dev *vdev)
अणु
	vdev->proxy = PROXY_NONE;
	vdev->proxy_index = 0;
पूर्ण

पूर्णांक vnic_dev_cmd(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
	u64 *a0, u64 *a1, पूर्णांक रुको)
अणु
	स_रखो(vdev->args, 0, माप(vdev->args));

	चयन (vdev->proxy) अणु
	हाल PROXY_BY_INDEX:
		वापस vnic_dev_cmd_proxy(vdev, CMD_PROXY_BY_INDEX, cmd,
				a0, a1, रुको);
	हाल PROXY_BY_BDF:
		वापस vnic_dev_cmd_proxy(vdev, CMD_PROXY_BY_BDF, cmd,
				a0, a1, रुको);
	हाल PROXY_NONE:
	शेष:
		वापस vnic_dev_cmd_no_proxy(vdev, cmd, a0, a1, रुको);
	पूर्ण
पूर्ण

अटल पूर्णांक vnic_dev_capable(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd)
अणु
	u64 a0 = (u32)cmd, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक err;

	err = vnic_dev_cmd(vdev, CMD_CAPABILITY, &a0, &a1, रुको);

	वापस !(err || a0);
पूर्ण

पूर्णांक vnic_dev_fw_info(काष्ठा vnic_dev *vdev,
	काष्ठा vnic_devcmd_fw_info **fw_info)
अणु
	u64 a0, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक err = 0;

	अगर (!vdev->fw_info) अणु
		vdev->fw_info = dma_alloc_coherent(&vdev->pdev->dev,
						   माप(काष्ठा vnic_devcmd_fw_info),
						   &vdev->fw_info_pa, GFP_ATOMIC);
		अगर (!vdev->fw_info)
			वापस -ENOMEM;

		a0 = vdev->fw_info_pa;
		a1 = माप(काष्ठा vnic_devcmd_fw_info);

		/* only get fw_info once and cache it */
		अगर (vnic_dev_capable(vdev, CMD_MCPU_FW_INFO))
			err = vnic_dev_cmd(vdev, CMD_MCPU_FW_INFO,
				&a0, &a1, रुको);
		अन्यथा
			err = vnic_dev_cmd(vdev, CMD_MCPU_FW_INFO_OLD,
				&a0, &a1, रुको);
	पूर्ण

	*fw_info = vdev->fw_info;

	वापस err;
पूर्ण

पूर्णांक vnic_dev_spec(काष्ठा vnic_dev *vdev, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक size,
	व्योम *value)
अणु
	u64 a0, a1;
	पूर्णांक रुको = 1000;
	पूर्णांक err;

	a0 = offset;
	a1 = size;

	err = vnic_dev_cmd(vdev, CMD_DEV_SPEC, &a0, &a1, रुको);

	चयन (size) अणु
	हाल 1: *(u8 *)value = (u8)a0; अवरोध;
	हाल 2: *(u16 *)value = (u16)a0; अवरोध;
	हाल 4: *(u32 *)value = (u32)a0; अवरोध;
	हाल 8: *(u64 *)value = a0; अवरोध;
	शेष: BUG(); अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक vnic_dev_stats_dump(काष्ठा vnic_dev *vdev, काष्ठा vnic_stats **stats)
अणु
	u64 a0, a1;
	पूर्णांक रुको = 1000;

	अगर (!vdev->stats) अणु
		vdev->stats = dma_alloc_coherent(&vdev->pdev->dev,
						 माप(काष्ठा vnic_stats),
						 &vdev->stats_pa, GFP_ATOMIC);
		अगर (!vdev->stats)
			वापस -ENOMEM;
	पूर्ण

	*stats = vdev->stats;
	a0 = vdev->stats_pa;
	a1 = माप(काष्ठा vnic_stats);

	वापस vnic_dev_cmd(vdev, CMD_STATS_DUMP, &a0, &a1, रुको);
पूर्ण

पूर्णांक vnic_dev_बंद(काष्ठा vnic_dev *vdev)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = 1000;
	वापस vnic_dev_cmd(vdev, CMD_CLOSE, &a0, &a1, रुको);
पूर्ण

पूर्णांक vnic_dev_enable_रुको(काष्ठा vnic_dev *vdev)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = 1000;

	अगर (vnic_dev_capable(vdev, CMD_ENABLE_WAIT))
		वापस vnic_dev_cmd(vdev, CMD_ENABLE_WAIT, &a0, &a1, रुको);
	अन्यथा
		वापस vnic_dev_cmd(vdev, CMD_ENABLE, &a0, &a1, रुको);
पूर्ण

पूर्णांक vnic_dev_disable(काष्ठा vnic_dev *vdev)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = 1000;
	वापस vnic_dev_cmd(vdev, CMD_DISABLE, &a0, &a1, रुको);
पूर्ण

पूर्णांक vnic_dev_खोलो(काष्ठा vnic_dev *vdev, पूर्णांक arg)
अणु
	u64 a0 = (u32)arg, a1 = 0;
	पूर्णांक रुको = 1000;
	वापस vnic_dev_cmd(vdev, CMD_OPEN, &a0, &a1, रुको);
पूर्ण

पूर्णांक vnic_dev_खोलो_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *करोne)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक err;

	*करोne = 0;

	err = vnic_dev_cmd(vdev, CMD_OPEN_STATUS, &a0, &a1, रुको);
	अगर (err)
		वापस err;

	*करोne = (a0 == 0);

	वापस 0;
पूर्ण

पूर्णांक vnic_dev_soft_reset(काष्ठा vnic_dev *vdev, पूर्णांक arg)
अणु
	u64 a0 = (u32)arg, a1 = 0;
	पूर्णांक रुको = 1000;
	वापस vnic_dev_cmd(vdev, CMD_SOFT_RESET, &a0, &a1, रुको);
पूर्ण

पूर्णांक vnic_dev_soft_reset_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *करोne)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक err;

	*करोne = 0;

	err = vnic_dev_cmd(vdev, CMD_SOFT_RESET_STATUS, &a0, &a1, रुको);
	अगर (err)
		वापस err;

	*करोne = (a0 == 0);

	वापस 0;
पूर्ण

पूर्णांक vnic_dev_hang_reset(काष्ठा vnic_dev *vdev, पूर्णांक arg)
अणु
	u64 a0 = (u32)arg, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक err;

	अगर (vnic_dev_capable(vdev, CMD_HANG_RESET)) अणु
		वापस vnic_dev_cmd(vdev, CMD_HANG_RESET,
				&a0, &a1, रुको);
	पूर्ण अन्यथा अणु
		err = vnic_dev_soft_reset(vdev, arg);
		अगर (err)
			वापस err;
		वापस vnic_dev_init(vdev, 0);
	पूर्ण
पूर्ण

पूर्णांक vnic_dev_hang_reset_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *करोne)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक err;

	*करोne = 0;

	अगर (vnic_dev_capable(vdev, CMD_HANG_RESET_STATUS)) अणु
		err = vnic_dev_cmd(vdev, CMD_HANG_RESET_STATUS,
				&a0, &a1, रुको);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		वापस vnic_dev_soft_reset_करोne(vdev, करोne);
	पूर्ण

	*करोne = (a0 == 0);

	वापस 0;
पूर्ण

पूर्णांक vnic_dev_hang_notअगरy(काष्ठा vnic_dev *vdev)
अणु
	u64 a0, a1;
	पूर्णांक रुको = 1000;
	वापस vnic_dev_cmd(vdev, CMD_HANG_NOTIFY, &a0, &a1, रुको);
पूर्ण

पूर्णांक vnic_dev_get_mac_addr(काष्ठा vnic_dev *vdev, u8 *mac_addr)
अणु
	u64 a0, a1;
	पूर्णांक रुको = 1000;
	पूर्णांक err, i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		mac_addr[i] = 0;

	err = vnic_dev_cmd(vdev, CMD_GET_MAC_ADDR, &a0, &a1, रुको);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < ETH_ALEN; i++)
		mac_addr[i] = ((u8 *)&a0)[i];

	वापस 0;
पूर्ण

पूर्णांक vnic_dev_packet_filter(काष्ठा vnic_dev *vdev, पूर्णांक directed, पूर्णांक multicast,
	पूर्णांक broadcast, पूर्णांक promisc, पूर्णांक allmulti)
अणु
	u64 a0, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक err;

	a0 = (directed ? CMD_PFILTER_सूचीECTED : 0) |
	     (multicast ? CMD_PFILTER_MULTICAST : 0) |
	     (broadcast ? CMD_PFILTER_BROADCAST : 0) |
	     (promisc ? CMD_PFILTER_PROMISCUOUS : 0) |
	     (allmulti ? CMD_PFILTER_ALL_MULTICAST : 0);

	err = vnic_dev_cmd(vdev, CMD_PACKET_FILTER, &a0, &a1, रुको);
	अगर (err)
		vdev_neterr(vdev, "Can't set packet filter\n");

	वापस err;
पूर्ण

पूर्णांक vnic_dev_add_addr(काष्ठा vnic_dev *vdev, स्थिर u8 *addr)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		((u8 *)&a0)[i] = addr[i];

	err = vnic_dev_cmd(vdev, CMD_ADDR_ADD, &a0, &a1, रुको);
	अगर (err)
		vdev_neterr(vdev, "Can't add addr [%pM], %d\n", addr, err);

	वापस err;
पूर्ण

पूर्णांक vnic_dev_del_addr(काष्ठा vnic_dev *vdev, स्थिर u8 *addr)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		((u8 *)&a0)[i] = addr[i];

	err = vnic_dev_cmd(vdev, CMD_ADDR_DEL, &a0, &a1, रुको);
	अगर (err)
		vdev_neterr(vdev, "Can't del addr [%pM], %d\n", addr, err);

	वापस err;
पूर्ण

पूर्णांक vnic_dev_set_ig_vlan_reग_लिखो_mode(काष्ठा vnic_dev *vdev,
	u8 ig_vlan_reग_लिखो_mode)
अणु
	u64 a0 = ig_vlan_reग_लिखो_mode, a1 = 0;
	पूर्णांक रुको = 1000;

	अगर (vnic_dev_capable(vdev, CMD_IG_VLAN_REWRITE_MODE))
		वापस vnic_dev_cmd(vdev, CMD_IG_VLAN_REWRITE_MODE,
				&a0, &a1, रुको);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक vnic_dev_notअगरy_setcmd(काष्ठा vnic_dev *vdev,
	व्योम *notअगरy_addr, dma_addr_t notअगरy_pa, u16 पूर्णांकr)
अणु
	u64 a0, a1;
	पूर्णांक रुको = 1000;
	पूर्णांक r;

	स_रखो(notअगरy_addr, 0, माप(काष्ठा vnic_devcmd_notअगरy));
	vdev->notअगरy = notअगरy_addr;
	vdev->notअगरy_pa = notअगरy_pa;

	a0 = (u64)notअगरy_pa;
	a1 = ((u64)पूर्णांकr << 32) & 0x0000ffff00000000ULL;
	a1 += माप(काष्ठा vnic_devcmd_notअगरy);

	r = vnic_dev_cmd(vdev, CMD_NOTIFY, &a0, &a1, रुको);
	vdev->notअगरy_sz = (r == 0) ? (u32)a1 : 0;
	वापस r;
पूर्ण

पूर्णांक vnic_dev_notअगरy_set(काष्ठा vnic_dev *vdev, u16 पूर्णांकr)
अणु
	व्योम *notअगरy_addr;
	dma_addr_t notअगरy_pa;

	अगर (vdev->notअगरy || vdev->notअगरy_pa) अणु
		vdev_neterr(vdev, "notify block %p still allocated\n",
			    vdev->notअगरy);
		वापस -EINVAL;
	पूर्ण

	notअगरy_addr = dma_alloc_coherent(&vdev->pdev->dev,
					 माप(काष्ठा vnic_devcmd_notअगरy),
					 &notअगरy_pa, GFP_ATOMIC);
	अगर (!notअगरy_addr)
		वापस -ENOMEM;

	वापस vnic_dev_notअगरy_setcmd(vdev, notअगरy_addr, notअगरy_pa, पूर्णांकr);
पूर्ण

अटल पूर्णांक vnic_dev_notअगरy_unsetcmd(काष्ठा vnic_dev *vdev)
अणु
	u64 a0, a1;
	पूर्णांक रुको = 1000;
	पूर्णांक err;

	a0 = 0;  /* paddr = 0 to unset notअगरy buffer */
	a1 = 0x0000ffff00000000ULL; /* पूर्णांकr num = -1 to unreg क्रम पूर्णांकr */
	a1 += माप(काष्ठा vnic_devcmd_notअगरy);

	err = vnic_dev_cmd(vdev, CMD_NOTIFY, &a0, &a1, रुको);
	vdev->notअगरy = शून्य;
	vdev->notअगरy_pa = 0;
	vdev->notअगरy_sz = 0;

	वापस err;
पूर्ण

पूर्णांक vnic_dev_notअगरy_unset(काष्ठा vnic_dev *vdev)
अणु
	अगर (vdev->notअगरy) अणु
		dma_मुक्त_coherent(&vdev->pdev->dev,
				  माप(काष्ठा vnic_devcmd_notअगरy),
				  vdev->notअगरy, vdev->notअगरy_pa);
	पूर्ण

	वापस vnic_dev_notअगरy_unsetcmd(vdev);
पूर्ण

अटल पूर्णांक vnic_dev_notअगरy_पढ़ोy(काष्ठा vnic_dev *vdev)
अणु
	u32 *words;
	अचिन्हित पूर्णांक nwords = vdev->notअगरy_sz / 4;
	अचिन्हित पूर्णांक i;
	u32 csum;

	अगर (!vdev->notअगरy || !vdev->notअगरy_sz)
		वापस 0;

	करो अणु
		csum = 0;
		स_नकल(&vdev->notअगरy_copy, vdev->notअगरy, vdev->notअगरy_sz);
		words = (u32 *)&vdev->notअगरy_copy;
		क्रम (i = 1; i < nwords; i++)
			csum += words[i];
	पूर्ण जबतक (csum != words[0]);

	वापस 1;
पूर्ण

पूर्णांक vnic_dev_init(काष्ठा vnic_dev *vdev, पूर्णांक arg)
अणु
	u64 a0 = (u32)arg, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक r = 0;

	अगर (vnic_dev_capable(vdev, CMD_INIT))
		r = vnic_dev_cmd(vdev, CMD_INIT, &a0, &a1, रुको);
	अन्यथा अणु
		vnic_dev_cmd(vdev, CMD_INIT_v1, &a0, &a1, रुको);
		अगर (a0 & CMD_INITF_DEFAULT_MAC) अणु
			/* Emulate these क्रम old CMD_INIT_v1 which
			 * didn't pass a0 so no CMD_INITF_*.
			 */
			vnic_dev_cmd(vdev, CMD_GET_MAC_ADDR, &a0, &a1, रुको);
			vnic_dev_cmd(vdev, CMD_ADDR_ADD, &a0, &a1, रुको);
		पूर्ण
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक vnic_dev_deinit(काष्ठा vnic_dev *vdev)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = 1000;

	वापस vnic_dev_cmd(vdev, CMD_DEINIT, &a0, &a1, रुको);
पूर्ण

व्योम vnic_dev_पूर्णांकr_coal_समयr_info_शेष(काष्ठा vnic_dev *vdev)
अणु
	/* Default: hardware पूर्णांकr coal समयr is in units of 1.5 usecs */
	vdev->पूर्णांकr_coal_समयr_info.mul = 2;
	vdev->पूर्णांकr_coal_समयr_info.भाग = 3;
	vdev->पूर्णांकr_coal_समयr_info.max_usec =
		vnic_dev_पूर्णांकr_coal_समयr_hw_to_usec(vdev, 0xffff);
पूर्ण

पूर्णांक vnic_dev_पूर्णांकr_coal_समयr_info(काष्ठा vnic_dev *vdev)
अणु
	पूर्णांक रुको = 1000;
	पूर्णांक err;

	स_रखो(vdev->args, 0, माप(vdev->args));

	अगर (vnic_dev_capable(vdev, CMD_INTR_COAL_CONVERT))
		err = vdev->devcmd_rtn(vdev, CMD_INTR_COAL_CONVERT, रुको);
	अन्यथा
		err = ERR_ECMDUNKNOWN;

	/* Use शेषs when firmware करोesn't support the devcmd at all or
	 * supports it क्रम only specअगरic hardware
	 */
	अगर ((err == ERR_ECMDUNKNOWN) ||
		(!err && !(vdev->args[0] && vdev->args[1] && vdev->args[2]))) अणु
		vdev_netwarn(vdev, "Using default conversion factor for interrupt coalesce timer\n");
		vnic_dev_पूर्णांकr_coal_समयr_info_शेष(vdev);
		वापस 0;
	पूर्ण

	अगर (!err) अणु
		vdev->पूर्णांकr_coal_समयr_info.mul = (u32) vdev->args[0];
		vdev->पूर्णांकr_coal_समयr_info.भाग = (u32) vdev->args[1];
		vdev->पूर्णांकr_coal_समयr_info.max_usec = (u32) vdev->args[2];
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक vnic_dev_link_status(काष्ठा vnic_dev *vdev)
अणु
	अगर (!vnic_dev_notअगरy_पढ़ोy(vdev))
		वापस 0;

	वापस vdev->notअगरy_copy.link_state;
पूर्ण

u32 vnic_dev_port_speed(काष्ठा vnic_dev *vdev)
अणु
	अगर (!vnic_dev_notअगरy_पढ़ोy(vdev))
		वापस 0;

	वापस vdev->notअगरy_copy.port_speed;
पूर्ण

u32 vnic_dev_msg_lvl(काष्ठा vnic_dev *vdev)
अणु
	अगर (!vnic_dev_notअगरy_पढ़ोy(vdev))
		वापस 0;

	वापस vdev->notअगरy_copy.msglvl;
पूर्ण

u32 vnic_dev_mtu(काष्ठा vnic_dev *vdev)
अणु
	अगर (!vnic_dev_notअगरy_पढ़ोy(vdev))
		वापस 0;

	वापस vdev->notअगरy_copy.mtu;
पूर्ण

व्योम vnic_dev_set_पूर्णांकr_mode(काष्ठा vnic_dev *vdev,
	क्रमागत vnic_dev_पूर्णांकr_mode पूर्णांकr_mode)
अणु
	vdev->पूर्णांकr_mode = पूर्णांकr_mode;
पूर्ण

क्रमागत vnic_dev_पूर्णांकr_mode vnic_dev_get_पूर्णांकr_mode(
	काष्ठा vnic_dev *vdev)
अणु
	वापस vdev->पूर्णांकr_mode;
पूर्ण

u32 vnic_dev_पूर्णांकr_coal_समयr_usec_to_hw(काष्ठा vnic_dev *vdev, u32 usec)
अणु
	वापस (usec * vdev->पूर्णांकr_coal_समयr_info.mul) /
		vdev->पूर्णांकr_coal_समयr_info.भाग;
पूर्ण

u32 vnic_dev_पूर्णांकr_coal_समयr_hw_to_usec(काष्ठा vnic_dev *vdev, u32 hw_cycles)
अणु
	वापस (hw_cycles * vdev->पूर्णांकr_coal_समयr_info.भाग) /
		vdev->पूर्णांकr_coal_समयr_info.mul;
पूर्ण

u32 vnic_dev_get_पूर्णांकr_coal_समयr_max(काष्ठा vnic_dev *vdev)
अणु
	वापस vdev->पूर्णांकr_coal_समयr_info.max_usec;
पूर्ण

व्योम vnic_dev_unरेजिस्टर(काष्ठा vnic_dev *vdev)
अणु
	अगर (vdev) अणु
		अगर (vdev->notअगरy)
			dma_मुक्त_coherent(&vdev->pdev->dev,
					  माप(काष्ठा vnic_devcmd_notअगरy),
					  vdev->notअगरy, vdev->notअगरy_pa);
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
EXPORT_SYMBOL(vnic_dev_unरेजिस्टर);

काष्ठा vnic_dev *vnic_dev_रेजिस्टर(काष्ठा vnic_dev *vdev,
	व्योम *priv, काष्ठा pci_dev *pdev, काष्ठा vnic_dev_bar *bar,
	अचिन्हित पूर्णांक num_bars)
अणु
	अगर (!vdev) अणु
		vdev = kzalloc(माप(काष्ठा vnic_dev), GFP_KERNEL);
		अगर (!vdev)
			वापस शून्य;
	पूर्ण

	vdev->priv = priv;
	vdev->pdev = pdev;

	अगर (vnic_dev_discover_res(vdev, bar, num_bars))
		जाओ err_out;

	वापस vdev;

err_out:
	vnic_dev_unरेजिस्टर(vdev);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(vnic_dev_रेजिस्टर);

काष्ठा pci_dev *vnic_dev_get_pdev(काष्ठा vnic_dev *vdev)
अणु
	वापस vdev->pdev;
पूर्ण
EXPORT_SYMBOL(vnic_dev_get_pdev);

पूर्णांक vnic_devcmd_init(काष्ठा vnic_dev *vdev)
अणु
	व्योम __iomem *res;
	पूर्णांक err;

	res = vnic_dev_get_res(vdev, RES_TYPE_DEVCMD2, 0);
	अगर (res) अणु
		err = vnic_dev_init_devcmd2(vdev);
		अगर (err)
			vdev_warn(vdev, "DEVCMD2 init failed: %d, Using DEVCMD1\n",
				  err);
		अन्यथा
			वापस 0;
	पूर्ण अन्यथा अणु
		vdev_warn(vdev, "DEVCMD2 resource not found (old firmware?) Using DEVCMD1\n");
	पूर्ण
	err = vnic_dev_init_devcmd1(vdev);
	अगर (err)
		vdev_err(vdev, "DEVCMD1 initialization failed: %d\n", err);

	वापस err;
पूर्ण

पूर्णांक vnic_dev_init_prov2(काष्ठा vnic_dev *vdev, u8 *buf, u32 len)
अणु
	u64 a0, a1 = len;
	पूर्णांक रुको = 1000;
	dma_addr_t prov_pa;
	व्योम *prov_buf;
	पूर्णांक ret;

	prov_buf = dma_alloc_coherent(&vdev->pdev->dev, len, &prov_pa, GFP_ATOMIC);
	अगर (!prov_buf)
		वापस -ENOMEM;

	स_नकल(prov_buf, buf, len);

	a0 = prov_pa;

	ret = vnic_dev_cmd(vdev, CMD_INIT_PROV_INFO2, &a0, &a1, रुको);

	dma_मुक्त_coherent(&vdev->pdev->dev, len, prov_buf, prov_pa);

	वापस ret;
पूर्ण

पूर्णांक vnic_dev_enable2(काष्ठा vnic_dev *vdev, पूर्णांक active)
अणु
	u64 a0, a1 = 0;
	पूर्णांक रुको = 1000;

	a0 = (active ? CMD_ENABLE2_ACTIVE : 0);

	वापस vnic_dev_cmd(vdev, CMD_ENABLE2, &a0, &a1, रुको);
पूर्ण

अटल पूर्णांक vnic_dev_cmd_status(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
	पूर्णांक *status)
अणु
	u64 a0 = cmd, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक ret;

	ret = vnic_dev_cmd(vdev, CMD_STATUS, &a0, &a1, रुको);
	अगर (!ret)
		*status = (पूर्णांक)a0;

	वापस ret;
पूर्ण

पूर्णांक vnic_dev_enable2_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *status)
अणु
	वापस vnic_dev_cmd_status(vdev, CMD_ENABLE2, status);
पूर्ण

पूर्णांक vnic_dev_deinit_करोne(काष्ठा vnic_dev *vdev, पूर्णांक *status)
अणु
	वापस vnic_dev_cmd_status(vdev, CMD_DEINIT, status);
पूर्ण

पूर्णांक vnic_dev_set_mac_addr(काष्ठा vnic_dev *vdev, u8 *mac_addr)
अणु
	u64 a0, a1;
	पूर्णांक रुको = 1000;
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		((u8 *)&a0)[i] = mac_addr[i];

	वापस vnic_dev_cmd(vdev, CMD_SET_MAC_ADDR, &a0, &a1, रुको);
पूर्ण

/* vnic_dev_classअगरier: Add/Delete classअगरier entries
 * @vdev: vdev of the device
 * @cmd: CLSF_ADD क्रम Add filter
 *	 CLSF_DEL क्रम Delete filter
 * @entry: In हाल of ADD filter, the caller passes the RQ number in this
 *	   variable.
 *
 *	   This function stores the filter_id वापसed by the firmware in the
 *	   same variable beक्रमe वापस;
 *
 *	   In हाल of DEL filter, the caller passes the RQ number. Return
 *	   value is irrelevant.
 * @data: filter data
 */
पूर्णांक vnic_dev_classअगरier(काष्ठा vnic_dev *vdev, u8 cmd, u16 *entry,
			काष्ठा filter *data)
अणु
	u64 a0, a1;
	पूर्णांक रुको = 1000;
	dma_addr_t tlv_pa;
	पूर्णांक ret = -EINVAL;
	काष्ठा filter_tlv *tlv, *tlv_va;
	काष्ठा filter_action *action;
	u64 tlv_size;

	अगर (cmd == CLSF_ADD) अणु
		tlv_size = माप(काष्ठा filter) +
			   माप(काष्ठा filter_action) +
			   2 * माप(काष्ठा filter_tlv);
		tlv_va = dma_alloc_coherent(&vdev->pdev->dev, tlv_size,
					    &tlv_pa, GFP_ATOMIC);
		अगर (!tlv_va)
			वापस -ENOMEM;
		tlv = tlv_va;
		a0 = tlv_pa;
		a1 = tlv_size;
		स_रखो(tlv, 0, tlv_size);
		tlv->type = CLSF_TLV_FILTER;
		tlv->length = माप(काष्ठा filter);
		*(काष्ठा filter *)&tlv->val = *data;

		tlv = (काष्ठा filter_tlv *)((अक्षर *)tlv +
					    माप(काष्ठा filter_tlv) +
					    माप(काष्ठा filter));

		tlv->type = CLSF_TLV_ACTION;
		tlv->length = माप(काष्ठा filter_action);
		action = (काष्ठा filter_action *)&tlv->val;
		action->type = FILTER_ACTION_RQ_STEERING;
		action->u.rq_idx = *entry;

		ret = vnic_dev_cmd(vdev, CMD_ADD_FILTER, &a0, &a1, रुको);
		*entry = (u16)a0;
		dma_मुक्त_coherent(&vdev->pdev->dev, tlv_size, tlv_va, tlv_pa);
	पूर्ण अन्यथा अगर (cmd == CLSF_DEL) अणु
		a0 = *entry;
		ret = vnic_dev_cmd(vdev, CMD_DEL_FILTER, &a0, &a1, रुको);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक vnic_dev_overlay_offload_ctrl(काष्ठा vnic_dev *vdev, u8 overlay, u8 config)
अणु
	u64 a0 = overlay;
	u64 a1 = config;
	पूर्णांक रुको = 1000;

	वापस vnic_dev_cmd(vdev, CMD_OVERLAY_OFFLOAD_CTRL, &a0, &a1, रुको);
पूर्ण

पूर्णांक vnic_dev_overlay_offload_cfg(काष्ठा vnic_dev *vdev, u8 overlay,
				 u16 vxlan_udp_port_number)
अणु
	u64 a1 = vxlan_udp_port_number;
	u64 a0 = overlay;
	पूर्णांक रुको = 1000;

	वापस vnic_dev_cmd(vdev, CMD_OVERLAY_OFFLOAD_CFG, &a0, &a1, रुको);
पूर्ण

पूर्णांक vnic_dev_get_supported_feature_ver(काष्ठा vnic_dev *vdev, u8 feature,
				       u64 *supported_versions, u64 *a1)
अणु
	u64 a0 = feature;
	पूर्णांक रुको = 1000;
	पूर्णांक ret;

	ret = vnic_dev_cmd(vdev, CMD_GET_SUPP_FEATURE_VER, &a0, a1, रुको);
	अगर (!ret)
		*supported_versions = a0;

	वापस ret;
पूर्ण

पूर्णांक vnic_dev_capable_rss_hash_type(काष्ठा vnic_dev *vdev, u8 *rss_hash_type)
अणु
	u64 a0 = CMD_NIC_CFG, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक err;

	err = vnic_dev_cmd(vdev, CMD_CAPABILITY, &a0, &a1, रुको);
	/* rss_hash_type is valid only when a0 is 1. Adapter which करोes not
	 * support CMD_CAPABILITY क्रम rss_hash_type has a0 = 0
	 */
	अगर (err || (a0 != 1))
		वापस -EOPNOTSUPP;

	a1 = (a1 >> NIC_CFG_RSS_HASH_TYPE_SHIFT) &
	     NIC_CFG_RSS_HASH_TYPE_MASK_FIELD;

	*rss_hash_type = (u8)a1;

	वापस 0;
पूर्ण
