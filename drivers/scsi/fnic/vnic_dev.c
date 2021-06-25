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

काष्ठा devcmd2_controller अणु
	काष्ठा vnic_wq_ctrl *wq_ctrl;
	काष्ठा vnic_dev_ring results_ring;
	काष्ठा vnic_wq wq;
	काष्ठा vnic_devcmd2 *cmd_ring;
	काष्ठा devcmd2_result *result;
	u16 next_result;
	u16 result_size;
	पूर्णांक color;
पूर्ण;

क्रमागत vnic_proxy_type अणु
	PROXY_NONE,
	PROXY_BY_BDF,
	PROXY_BY_INDEX,
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
	क्रमागत vnic_proxy_type proxy;
	u32 proxy_index;
	u64 args[VNIC_DEVCMD_NARGS];
	काष्ठा devcmd2_controller *devcmd2;
	पूर्णांक (*devcmd_rtn)(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
			पूर्णांक रुको);
पूर्ण;

#घोषणा VNIC_MAX_RES_HDR_SIZE \
	(माप(काष्ठा vnic_resource_header) + \
	माप(काष्ठा vnic_resource) * RES_TYPE_MAX)
#घोषणा VNIC_RES_STRIDE	128

व्योम *vnic_dev_priv(काष्ठा vnic_dev *vdev)
अणु
	वापस vdev->priv;
पूर्ण

अटल पूर्णांक vnic_dev_discover_res(काष्ठा vnic_dev *vdev,
	काष्ठा vnic_dev_bar *bar)
अणु
	काष्ठा vnic_resource_header __iomem *rh;
	काष्ठा vnic_resource __iomem *r;
	u8 type;

	अगर (bar->len < VNIC_MAX_RES_HDR_SIZE) अणु
		prपूर्णांकk(KERN_ERR "vNIC BAR0 res hdr length error\n");
		वापस -EINVAL;
	पूर्ण

	rh = bar->vaddr;
	अगर (!rh) अणु
		prपूर्णांकk(KERN_ERR "vNIC BAR0 res hdr not mem-mapped\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ioपढ़ो32(&rh->magic) != VNIC_RES_MAGIC ||
	    ioपढ़ो32(&rh->version) != VNIC_RES_VERSION) अणु
		prपूर्णांकk(KERN_ERR "vNIC BAR0 res magic/version error "
			"exp (%lx/%lx) curr (%x/%x)\n",
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

		अगर (bar_num != 0)  /* only mapping in BAR0 resources */
			जारी;

		चयन (type) अणु
		हाल RES_TYPE_WQ:
		हाल RES_TYPE_RQ:
		हाल RES_TYPE_CQ:
		हाल RES_TYPE_INTR_CTRL:
			/* each count is stride bytes दीर्घ */
			len = count * VNIC_RES_STRIDE;
			अगर (len + bar_offset > bar->len) अणु
				prपूर्णांकk(KERN_ERR "vNIC BAR0 resource %d "
					"out-of-bounds, offset 0x%x + "
					"size 0x%x > bar len 0x%lx\n",
					type, bar_offset,
					len,
					bar->len);
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल RES_TYPE_INTR_PBA_LEGACY:
		हाल RES_TYPE_DEVCMD2:
		हाल RES_TYPE_DEVCMD:
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

अचिन्हित पूर्णांक vnic_dev_get_res_count(काष्ठा vnic_dev *vdev,
	क्रमागत vnic_res_type type)
अणु
	वापस vdev->res[type].count;
पूर्ण

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

अचिन्हित पूर्णांक vnic_dev_desc_ring_size(काष्ठा vnic_dev_ring *ring,
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
		&ring->base_addr_unaligned, GFP_KERNEL);

	अगर (!ring->descs_unaligned) अणु
		prपूर्णांकk(KERN_ERR
		  "Failed to allocate ring (size=%d), aborting\n",
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
		dma_मुक्त_coherent(&vdev->pdev->dev,
			ring->size_unaligned,
			ring->descs_unaligned,
			ring->base_addr_unaligned);
		ring->descs = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक vnic_dev_cmd1(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd, पूर्णांक रुको)
अणु
	काष्ठा vnic_devcmd __iomem *devcmd = vdev->devcmd;
	पूर्णांक delay;
	u32 status;
	अटल स्थिर पूर्णांक dev_cmd_err[] = अणु
		/* convert from fw's version of error.h to host's version */
		0,	/* ERR_SUCCESS */
		EINVAL,	/* ERR_EINVAL */
		EFAULT,	/* ERR_EFAULT */
		EPERM,	/* ERR_EPERM */
		EBUSY,  /* ERR_EBUSY */
	पूर्ण;
	पूर्णांक err;
	u64 *a0 = &vdev->args[0];
	u64 *a1 = &vdev->args[1];

	status = ioपढ़ो32(&devcmd->status);
	अगर (status & STAT_BUSY) अणु
		prपूर्णांकk(KERN_ERR "Busy devcmd %d\n", _CMD_N(cmd));
		वापस -EBUSY;
	पूर्ण

	अगर (_CMD_सूची(cmd) & _CMD_सूची_WRITE) अणु
		ग_लिखोq(*a0, &devcmd->args[0]);
		ग_लिखोq(*a1, &devcmd->args[1]);
		wmb();
	पूर्ण

	ioग_लिखो32(cmd, &devcmd->cmd);

	अगर ((_CMD_FLAGS(cmd) & _CMD_FLAGS_NOWAIT))
			वापस 0;

	क्रम (delay = 0; delay < रुको; delay++) अणु

		udelay(100);

		status = ioपढ़ो32(&devcmd->status);
		अगर (!(status & STAT_BUSY)) अणु

			अगर (status & STAT_ERROR) अणु
				err = dev_cmd_err[(पूर्णांक)पढ़ोq(&devcmd->args[0])];
				prपूर्णांकk(KERN_ERR "Error %d devcmd %d\n",
					err, _CMD_N(cmd));
				वापस -err;
			पूर्ण

			अगर (_CMD_सूची(cmd) & _CMD_सूची_READ) अणु
				rmb();
				*a0 = पढ़ोq(&devcmd->args[0]);
				*a1 = पढ़ोq(&devcmd->args[1]);
			पूर्ण

			वापस 0;
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_ERR "Timedout devcmd %d\n", _CMD_N(cmd));
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक vnic_dev_cmd2(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
		पूर्णांक रुको)
अणु
	काष्ठा devcmd2_controller *dc2c = vdev->devcmd2;
	काष्ठा devcmd2_result *result;
	u8 color;
	अचिन्हित पूर्णांक i;
	पूर्णांक delay;
	पूर्णांक err;
	u32 fetch_index;
	u32 posted;
	u32 new_posted;

	posted = ioपढ़ो32(&dc2c->wq_ctrl->posted_index);
	fetch_index = ioपढ़ो32(&dc2c->wq_ctrl->fetch_index);

	अगर (posted == 0xFFFFFFFF || fetch_index == 0xFFFFFFFF) अणु
		/* Hardware surprise removal: वापस error */
		pr_err("%s: devcmd2 invalid posted or fetch index on cmd %d\n",
				pci_name(vdev->pdev), _CMD_N(cmd));
		pr_err("%s: fetch index: %u, posted index: %u\n",
				pci_name(vdev->pdev), fetch_index, posted);

		वापस -ENODEV;

	पूर्ण

	new_posted = (posted + 1) % DEVCMD2_RING_SIZE;

	अगर (new_posted == fetch_index) अणु
		pr_err("%s: devcmd2 wq full while issuing cmd %d\n",
				pci_name(vdev->pdev), _CMD_N(cmd));
		pr_err("%s: fetch index: %u, posted index: %u\n",
				pci_name(vdev->pdev), fetch_index, posted);
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

	dc2c->next_result++;
	अगर (dc2c->next_result == dc2c->result_size) अणु
		dc2c->next_result = 0;
		dc2c->color = dc2c->color ? 0 : 1;
	पूर्ण

	क्रम (delay = 0; delay < रुको; delay++) अणु
		udelay(100);
		अगर (result->color == color) अणु
			अगर (result->error) अणु
				err = -(पूर्णांक) result->error;
				अगर (err != ERR_ECMDUNKNOWN ||
						cmd != CMD_CAPABILITY)
					pr_err("%s:Error %d devcmd %d\n",
						pci_name(vdev->pdev),
						err, _CMD_N(cmd));
				वापस err;
			पूर्ण
			अगर (_CMD_सूची(cmd) & _CMD_सूची_READ) अणु
				rmb(); /*prevent reorder जबतक reding result*/
				क्रम (i = 0; i < VNIC_DEVCMD_NARGS; i++)
					vdev->args[i] = result->results[i];
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण

	pr_err("%s:Timed out devcmd %d\n", pci_name(vdev->pdev), _CMD_N(cmd));

	वापस -ETIMEDOUT;
पूर्ण


अटल पूर्णांक vnic_dev_init_devcmd1(काष्ठा vnic_dev *vdev)
अणु
	vdev->devcmd = vnic_dev_get_res(vdev, RES_TYPE_DEVCMD, 0);
	अगर (!vdev->devcmd)
		वापस -ENODEV;

	vdev->devcmd_rtn = &vnic_dev_cmd1;
	वापस 0;
पूर्ण


अटल पूर्णांक vnic_dev_init_devcmd2(काष्ठा vnic_dev *vdev)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक fetch_index;

	अगर (vdev->devcmd2)
		वापस 0;

	vdev->devcmd2 = kzalloc(माप(*vdev->devcmd2), GFP_ATOMIC);
	अगर (!vdev->devcmd2)
		वापस -ENOMEM;

	vdev->devcmd2->color = 1;
	vdev->devcmd2->result_size = DEVCMD2_RING_SIZE;
	err = vnic_wq_devcmd2_alloc(vdev, &vdev->devcmd2->wq,
				DEVCMD2_RING_SIZE, DEVCMD2_DESC_SIZE);
	अगर (err)
		जाओ err_मुक्त_devcmd2;

	fetch_index = ioपढ़ो32(&vdev->devcmd2->wq.ctrl->fetch_index);
	अगर (fetch_index == 0xFFFFFFFF) अणु /* check क्रम hardware gone  */
		pr_err("error in devcmd2 init");
		err = -ENODEV;
		जाओ err_मुक्त_wq;
	पूर्ण

	/*
	 * Don't change fetch_index ever and
	 * set posted_index same as fetch_index
	 * when setting up the WQ क्रम devcmd2.
	 */
	vnic_wq_init_start(&vdev->devcmd2->wq, 0, fetch_index,
			fetch_index, 0, 0);

	vnic_wq_enable(&vdev->devcmd2->wq);

	err = vnic_dev_alloc_desc_ring(vdev, &vdev->devcmd2->results_ring,
			DEVCMD2_RING_SIZE, DEVCMD2_DESC_SIZE);
	अगर (err)
		जाओ err_disable_wq;

	vdev->devcmd2->result =
		(काष्ठा devcmd2_result *) vdev->devcmd2->results_ring.descs;
	vdev->devcmd2->cmd_ring =
		(काष्ठा vnic_devcmd2 *) vdev->devcmd2->wq.ring.descs;
	vdev->devcmd2->wq_ctrl = vdev->devcmd2->wq.ctrl;
	vdev->args[0] = (u64) vdev->devcmd2->results_ring.base_addr |
				VNIC_PADDR_TARGET;
	vdev->args[1] = DEVCMD2_RING_SIZE;

	err = vnic_dev_cmd2(vdev, CMD_INITIALIZE_DEVCMD2, 1000);
	अगर (err)
		जाओ err_मुक्त_desc_ring;

	vdev->devcmd_rtn = &vnic_dev_cmd2;

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
	vdev->devcmd2 = शून्य;
	vdev->devcmd_rtn = &vnic_dev_cmd1;
पूर्ण


अटल पूर्णांक vnic_dev_cmd_no_proxy(काष्ठा vnic_dev *vdev,
	क्रमागत vnic_devcmd_cmd cmd, u64 *a0, u64 *a1, पूर्णांक रुको)
अणु
	पूर्णांक err;

	vdev->args[0] = *a0;
	vdev->args[1] = *a1;

	err = (*vdev->devcmd_rtn)(vdev, cmd, रुको);

	*a0 = vdev->args[0];
	*a1 = vdev->args[1];

	वापस err;
पूर्ण


पूर्णांक vnic_dev_cmd(काष्ठा vnic_dev *vdev, क्रमागत vnic_devcmd_cmd cmd,
	u64 *a0, u64 *a1, पूर्णांक रुको)
अणु
	स_रखो(vdev->args, 0, माप(vdev->args));

	चयन (vdev->proxy) अणु
	हाल PROXY_NONE:
	शेष:
		वापस vnic_dev_cmd_no_proxy(vdev, cmd, a0, a1, रुको);
	पूर्ण
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
			&vdev->fw_info_pa, GFP_KERNEL);
		अगर (!vdev->fw_info)
			वापस -ENOMEM;

		a0 = vdev->fw_info_pa;

		/* only get fw_info once and cache it */
		err = vnic_dev_cmd(vdev, CMD_MCPU_FW_INFO, &a0, &a1, रुको);
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

पूर्णांक vnic_dev_stats_clear(काष्ठा vnic_dev *vdev)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = 1000;
	वापस vnic_dev_cmd(vdev, CMD_STATS_CLEAR, &a0, &a1, रुको);
पूर्ण

पूर्णांक vnic_dev_stats_dump(काष्ठा vnic_dev *vdev, काष्ठा vnic_stats **stats)
अणु
	u64 a0, a1;
	पूर्णांक रुको = 1000;

	अगर (!vdev->stats) अणु
		vdev->stats = dma_alloc_coherent(&vdev->pdev->dev,
			माप(काष्ठा vnic_stats), &vdev->stats_pa, GFP_KERNEL);
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

पूर्णांक vnic_dev_enable(काष्ठा vnic_dev *vdev)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = 1000;
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

पूर्णांक vnic_dev_hang_notअगरy(काष्ठा vnic_dev *vdev)
अणु
	u64 a0 = 0, a1 = 0;
	पूर्णांक रुको = 1000;
	वापस vnic_dev_cmd(vdev, CMD_HANG_NOTIFY, &a0, &a1, रुको);
पूर्ण

पूर्णांक vnic_dev_mac_addr(काष्ठा vnic_dev *vdev, u8 *mac_addr)
अणु
	u64 a[2] = अणुपूर्ण;
	पूर्णांक रुको = 1000;
	पूर्णांक err, i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		mac_addr[i] = 0;

	err = vnic_dev_cmd(vdev, CMD_MAC_ADDR, &a[0], &a[1], रुको);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < ETH_ALEN; i++)
		mac_addr[i] = ((u8 *)&a)[i];

	वापस 0;
पूर्ण

व्योम vnic_dev_packet_filter(काष्ठा vnic_dev *vdev, पूर्णांक directed, पूर्णांक multicast,
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
		prपूर्णांकk(KERN_ERR "Can't set packet filter\n");
पूर्ण

व्योम vnic_dev_add_addr(काष्ठा vnic_dev *vdev, u8 *addr)
अणु
	u64 a[2] = अणुपूर्ण;
	पूर्णांक रुको = 1000;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		((u8 *)&a)[i] = addr[i];

	err = vnic_dev_cmd(vdev, CMD_ADDR_ADD, &a[0], &a[1], रुको);
	अगर (err)
		pr_err("Can't add addr [%pM], %d\n", addr, err);
पूर्ण

व्योम vnic_dev_del_addr(काष्ठा vnic_dev *vdev, u8 *addr)
अणु
	u64 a[2] = अणुपूर्ण;
	पूर्णांक रुको = 1000;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < ETH_ALEN; i++)
		((u8 *)&a)[i] = addr[i];

	err = vnic_dev_cmd(vdev, CMD_ADDR_DEL, &a[0], &a[1], रुको);
	अगर (err)
		pr_err("Can't del addr [%pM], %d\n", addr, err);
पूर्ण

पूर्णांक vnic_dev_notअगरy_set(काष्ठा vnic_dev *vdev, u16 पूर्णांकr)
अणु
	u64 a0, a1;
	पूर्णांक रुको = 1000;

	अगर (!vdev->notअगरy) अणु
		vdev->notअगरy = dma_alloc_coherent(&vdev->pdev->dev,
			माप(काष्ठा vnic_devcmd_notअगरy),
			&vdev->notअगरy_pa, GFP_KERNEL);
		अगर (!vdev->notअगरy)
			वापस -ENOMEM;
	पूर्ण

	a0 = vdev->notअगरy_pa;
	a1 = ((u64)पूर्णांकr << 32) & 0x0000ffff00000000ULL;
	a1 += माप(काष्ठा vnic_devcmd_notअगरy);

	वापस vnic_dev_cmd(vdev, CMD_NOTIFY, &a0, &a1, रुको);
पूर्ण

व्योम vnic_dev_notअगरy_unset(काष्ठा vnic_dev *vdev)
अणु
	u64 a0, a1;
	पूर्णांक रुको = 1000;

	a0 = 0;  /* paddr = 0 to unset notअगरy buffer */
	a1 = 0x0000ffff00000000ULL; /* पूर्णांकr num = -1 to unreg क्रम पूर्णांकr */
	a1 += माप(काष्ठा vnic_devcmd_notअगरy);

	vnic_dev_cmd(vdev, CMD_NOTIFY, &a0, &a1, रुको);
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

पूर्णांक vnic_dev_init(काष्ठा vnic_dev *vdev, पूर्णांक arg)
अणु
	u64 a0 = (u32)arg, a1 = 0;
	पूर्णांक रुको = 1000;
	वापस vnic_dev_cmd(vdev, CMD_INIT, &a0, &a1, रुको);
पूर्ण

u16 vnic_dev_set_शेष_vlan(काष्ठा vnic_dev *vdev, u16 new_शेष_vlan)
अणु
	u64 a0 = new_शेष_vlan, a1 = 0;
	पूर्णांक रुको = 1000;
	पूर्णांक old_vlan = 0;

	old_vlan = vnic_dev_cmd(vdev, CMD_SET_DEFAULT_VLAN, &a0, &a1, रुको);
	वापस (u16)old_vlan;
पूर्ण

पूर्णांक vnic_dev_link_status(काष्ठा vnic_dev *vdev)
अणु
	अगर (vdev->linkstatus)
		वापस *vdev->linkstatus;

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

u32 vnic_dev_link_करोwn_cnt(काष्ठा vnic_dev *vdev)
अणु
	अगर (!vnic_dev_notअगरy_पढ़ोy(vdev))
		वापस 0;

	वापस vdev->notअगरy_copy.link_करोwn_cnt;
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

व्योम vnic_dev_unरेजिस्टर(काष्ठा vnic_dev *vdev)
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

काष्ठा vnic_dev *vnic_dev_रेजिस्टर(काष्ठा vnic_dev *vdev,
	व्योम *priv, काष्ठा pci_dev *pdev, काष्ठा vnic_dev_bar *bar)
अणु
	अगर (!vdev) अणु
		vdev = kzalloc(माप(काष्ठा vnic_dev), GFP_KERNEL);
		अगर (!vdev)
			वापस शून्य;
	पूर्ण

	vdev->priv = priv;
	vdev->pdev = pdev;

	अगर (vnic_dev_discover_res(vdev, bar))
		जाओ err_out;

	वापस vdev;

err_out:
	vnic_dev_unरेजिस्टर(vdev);
	वापस शून्य;
पूर्ण

पूर्णांक vnic_dev_cmd_init(काष्ठा vnic_dev *vdev)
अणु
	पूर्णांक err;
	व्योम *p;

	p = vnic_dev_get_res(vdev, RES_TYPE_DEVCMD2, 0);
	अगर (p) अणु
		pr_err("fnic: DEVCMD2 resource found!\n");
		err = vnic_dev_init_devcmd2(vdev);
	पूर्ण अन्यथा अणु
		pr_err("fnic: DEVCMD2 not found, fall back to Devcmd\n");
		err = vnic_dev_init_devcmd1(vdev);
	पूर्ण

	वापस err;
पूर्ण
