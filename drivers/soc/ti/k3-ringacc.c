<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * TI K3 NAVSS Ring Accelerator subप्रणाली driver
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/dma/ti-cppi5.h>
#समावेश <linux/soc/ti/k3-ringacc.h>
#समावेश <linux/soc/ti/ti_sci_protocol.h>
#समावेश <linux/soc/ti/ti_sci_पूर्णांकa_msi.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqकरोमुख्य.h>

अटल LIST_HEAD(k3_ringacc_list);
अटल DEFINE_MUTEX(k3_ringacc_list_lock);

#घोषणा K3_RINGACC_CFG_RING_SIZE_ELCNT_MASK		GENMASK(19, 0)
#घोषणा K3_DMARING_CFG_RING_SIZE_ELCNT_MASK		GENMASK(15, 0)

/**
 * काष्ठा k3_ring_rt_regs - The RA realसमय Control/Status Registers region
 *
 * @resv_16: Reserved
 * @db: Ring Doorbell Register
 * @resv_4: Reserved
 * @occ: Ring Occupancy Register
 * @indx: Ring Current Index Register
 * @hwocc: Ring Hardware Occupancy Register
 * @hwindx: Ring Hardware Current Index Register
 */
काष्ठा k3_ring_rt_regs अणु
	u32	resv_16[4];
	u32	db;
	u32	resv_4[1];
	u32	occ;
	u32	indx;
	u32	hwocc;
	u32	hwindx;
पूर्ण;

#घोषणा K3_RINGACC_RT_REGS_STEP			0x1000
#घोषणा K3_DMARING_RT_REGS_STEP			0x2000
#घोषणा K3_DMARING_RT_REGS_REVERSE_OFS		0x1000
#घोषणा K3_RINGACC_RT_OCC_MASK			GENMASK(20, 0)
#घोषणा K3_DMARING_RT_OCC_TDOWN_COMPLETE	BIT(31)
#घोषणा K3_DMARING_RT_DB_ENTRY_MASK		GENMASK(7, 0)
#घोषणा K3_DMARING_RT_DB_TDOWN_ACK		BIT(31)

/**
 * काष्ठा k3_ring_fअगरo_regs - The Ring Accelerator Queues Registers region
 *
 * @head_data: Ring Head Entry Data Registers
 * @tail_data: Ring Tail Entry Data Registers
 * @peek_head_data: Ring Peek Head Entry Data Regs
 * @peek_tail_data: Ring Peek Tail Entry Data Regs
 */
काष्ठा k3_ring_fअगरo_regs अणु
	u32	head_data[128];
	u32	tail_data[128];
	u32	peek_head_data[128];
	u32	peek_tail_data[128];
पूर्ण;

/**
 * काष्ठा k3_ringacc_proxy_gcfg_regs - RA Proxy Global Config MMIO Region
 *
 * @revision: Revision Register
 * @config: Config Register
 */
काष्ठा k3_ringacc_proxy_gcfg_regs अणु
	u32	revision;
	u32	config;
पूर्ण;

#घोषणा K3_RINGACC_PROXY_CFG_THREADS_MASK		GENMASK(15, 0)

/**
 * काष्ठा k3_ringacc_proxy_target_regs - Proxy Datapath MMIO Region
 *
 * @control: Proxy Control Register
 * @status: Proxy Status Register
 * @resv_512: Reserved
 * @data: Proxy Data Register
 */
काष्ठा k3_ringacc_proxy_target_regs अणु
	u32	control;
	u32	status;
	u8	resv_512[504];
	u32	data[128];
पूर्ण;

#घोषणा K3_RINGACC_PROXY_TARGET_STEP	0x1000
#घोषणा K3_RINGACC_PROXY_NOT_USED	(-1)

क्रमागत k3_ringacc_proxy_access_mode अणु
	PROXY_ACCESS_MODE_HEAD = 0,
	PROXY_ACCESS_MODE_TAIL = 1,
	PROXY_ACCESS_MODE_PEEK_HEAD = 2,
	PROXY_ACCESS_MODE_PEEK_TAIL = 3,
पूर्ण;

#घोषणा K3_RINGACC_FIFO_WINDOW_SIZE_BYTES  (512U)
#घोषणा K3_RINGACC_FIFO_REGS_STEP	0x1000
#घोषणा K3_RINGACC_MAX_DB_RING_CNT    (127U)

काष्ठा k3_ring_ops अणु
	पूर्णांक (*push_tail)(काष्ठा k3_ring *ring, व्योम *elm);
	पूर्णांक (*push_head)(काष्ठा k3_ring *ring, व्योम *elm);
	पूर्णांक (*pop_tail)(काष्ठा k3_ring *ring, व्योम *elm);
	पूर्णांक (*pop_head)(काष्ठा k3_ring *ring, व्योम *elm);
पूर्ण;

/**
 * काष्ठा k3_ring_state - Internal state tracking काष्ठाure
 *
 * @मुक्त: Number of मुक्त entries
 * @occ: Occupancy
 * @windex: Write index
 * @rindex: Read index
 */
काष्ठा k3_ring_state अणु
	u32 मुक्त;
	u32 occ;
	u32 windex;
	u32 rindex;
	u32 tकरोwn_complete:1;
पूर्ण;

/**
 * काष्ठा k3_ring - RA Ring descriptor
 *
 * @rt: Ring control/status रेजिस्टरs
 * @fअगरos: Ring queues रेजिस्टरs
 * @proxy: Ring Proxy Datapath रेजिस्टरs
 * @ring_mem_dma: Ring buffer dma address
 * @ring_mem_virt: Ring buffer virt address
 * @ops: Ring operations
 * @size: Ring size in elements
 * @elm_size: Size of the ring element
 * @mode: Ring mode
 * @flags: flags
 * @state: Ring state
 * @ring_id: Ring Id
 * @parent: Poपूर्णांकer on काष्ठा @k3_ringacc
 * @use_count: Use count क्रम shared rings
 * @proxy_id: RA Ring Proxy Id (only अगर @K3_RINGACC_RING_USE_PROXY)
 * @dma_dev: device to be used क्रम DMA API (allocation, mapping)
 * @asel: Address Space Select value क्रम physical addresses
 */
काष्ठा k3_ring अणु
	काष्ठा k3_ring_rt_regs __iomem *rt;
	काष्ठा k3_ring_fअगरo_regs __iomem *fअगरos;
	काष्ठा k3_ringacc_proxy_target_regs  __iomem *proxy;
	dma_addr_t	ring_mem_dma;
	व्योम		*ring_mem_virt;
	काष्ठा k3_ring_ops *ops;
	u32		size;
	क्रमागत k3_ring_size elm_size;
	क्रमागत k3_ring_mode mode;
	u32		flags;
#घोषणा K3_RING_FLAG_BUSY	BIT(1)
#घोषणा K3_RING_FLAG_SHARED	BIT(2)
#घोषणा K3_RING_FLAG_REVERSE	BIT(3)
	काष्ठा k3_ring_state state;
	u32		ring_id;
	काष्ठा k3_ringacc	*parent;
	u32		use_count;
	पूर्णांक		proxy_id;
	काष्ठा device	*dma_dev;
	u32		asel;
#घोषणा K3_ADDRESS_ASEL_SHIFT	48
पूर्ण;

काष्ठा k3_ringacc_ops अणु
	पूर्णांक (*init)(काष्ठा platक्रमm_device *pdev, काष्ठा k3_ringacc *ringacc);
पूर्ण;

/**
 * काष्ठा k3_ringacc - Rings accelerator descriptor
 *
 * @dev: poपूर्णांकer on RA device
 * @proxy_gcfg: RA proxy global config रेजिस्टरs
 * @proxy_target_base: RA proxy datapath region
 * @num_rings: number of ring in RA
 * @rings_inuse: bitfield क्रम ring usage tracking
 * @rm_gp_range: general purpose rings range from tisci
 * @dma_ring_reset_quirk: DMA reset w/a enable
 * @num_proxies: number of RA proxies
 * @proxy_inuse: bitfield क्रम proxy usage tracking
 * @rings: array of rings descriptors (काष्ठा @k3_ring)
 * @list: list of RAs in the प्रणाली
 * @req_lock: protect rings allocation
 * @tisci: poपूर्णांकer ti-sci handle
 * @tisci_ring_ops: ti-sci rings ops
 * @tisci_dev_id: ti-sci device id
 * @ops: SoC specअगरic ringacc operation
 * @dma_rings: indicate DMA ring (dual ring within BCDMA/PKTDMA)
 */
काष्ठा k3_ringacc अणु
	काष्ठा device *dev;
	काष्ठा k3_ringacc_proxy_gcfg_regs __iomem *proxy_gcfg;
	व्योम __iomem *proxy_target_base;
	u32 num_rings; /* number of rings in Ringacc module */
	अचिन्हित दीर्घ *rings_inuse;
	काष्ठा ti_sci_resource *rm_gp_range;

	bool dma_ring_reset_quirk;
	u32 num_proxies;
	अचिन्हित दीर्घ *proxy_inuse;

	काष्ठा k3_ring *rings;
	काष्ठा list_head list;
	काष्ठा mutex req_lock; /* protect rings allocation */

	स्थिर काष्ठा ti_sci_handle *tisci;
	स्थिर काष्ठा ti_sci_rm_ringacc_ops *tisci_ring_ops;
	u32 tisci_dev_id;

	स्थिर काष्ठा k3_ringacc_ops *ops;
	bool dma_rings;
पूर्ण;

/**
 * काष्ठा k3_ringacc - Rings accelerator SoC data
 *
 * @dma_ring_reset_quirk:  DMA reset w/a enable
 */
काष्ठा k3_ringacc_soc_data अणु
	अचिन्हित dma_ring_reset_quirk:1;
पूर्ण;

अटल पूर्णांक k3_ringacc_ring_पढ़ो_occ(काष्ठा k3_ring *ring)
अणु
	वापस पढ़ोl(&ring->rt->occ) & K3_RINGACC_RT_OCC_MASK;
पूर्ण

अटल व्योम k3_ringacc_ring_update_occ(काष्ठा k3_ring *ring)
अणु
	u32 val;

	val = पढ़ोl(&ring->rt->occ);

	ring->state.occ = val & K3_RINGACC_RT_OCC_MASK;
	ring->state.tकरोwn_complete = !!(val & K3_DMARING_RT_OCC_TDOWN_COMPLETE);
पूर्ण

अटल दीर्घ k3_ringacc_ring_get_fअगरo_pos(काष्ठा k3_ring *ring)
अणु
	वापस K3_RINGACC_FIFO_WINDOW_SIZE_BYTES -
	       (4 << ring->elm_size);
पूर्ण

अटल व्योम *k3_ringacc_get_elm_addr(काष्ठा k3_ring *ring, u32 idx)
अणु
	वापस (ring->ring_mem_virt + idx * (4 << ring->elm_size));
पूर्ण

अटल पूर्णांक k3_ringacc_ring_push_mem(काष्ठा k3_ring *ring, व्योम *elem);
अटल पूर्णांक k3_ringacc_ring_pop_mem(काष्ठा k3_ring *ring, व्योम *elem);
अटल पूर्णांक k3_dmaring_fwd_pop(काष्ठा k3_ring *ring, व्योम *elem);
अटल पूर्णांक k3_dmaring_reverse_pop(काष्ठा k3_ring *ring, व्योम *elem);

अटल काष्ठा k3_ring_ops k3_ring_mode_ring_ops = अणु
		.push_tail = k3_ringacc_ring_push_mem,
		.pop_head = k3_ringacc_ring_pop_mem,
पूर्ण;

अटल काष्ठा k3_ring_ops k3_dmaring_fwd_ops = अणु
		.push_tail = k3_ringacc_ring_push_mem,
		.pop_head = k3_dmaring_fwd_pop,
पूर्ण;

अटल काष्ठा k3_ring_ops k3_dmaring_reverse_ops = अणु
		/* Reverse side of the DMA ring can only be popped by SW */
		.pop_head = k3_dmaring_reverse_pop,
पूर्ण;

अटल पूर्णांक k3_ringacc_ring_push_io(काष्ठा k3_ring *ring, व्योम *elem);
अटल पूर्णांक k3_ringacc_ring_pop_io(काष्ठा k3_ring *ring, व्योम *elem);
अटल पूर्णांक k3_ringacc_ring_push_head_io(काष्ठा k3_ring *ring, व्योम *elem);
अटल पूर्णांक k3_ringacc_ring_pop_tail_io(काष्ठा k3_ring *ring, व्योम *elem);

अटल काष्ठा k3_ring_ops k3_ring_mode_msg_ops = अणु
		.push_tail = k3_ringacc_ring_push_io,
		.push_head = k3_ringacc_ring_push_head_io,
		.pop_tail = k3_ringacc_ring_pop_tail_io,
		.pop_head = k3_ringacc_ring_pop_io,
पूर्ण;

अटल पूर्णांक k3_ringacc_ring_push_head_proxy(काष्ठा k3_ring *ring, व्योम *elem);
अटल पूर्णांक k3_ringacc_ring_push_tail_proxy(काष्ठा k3_ring *ring, व्योम *elem);
अटल पूर्णांक k3_ringacc_ring_pop_head_proxy(काष्ठा k3_ring *ring, व्योम *elem);
अटल पूर्णांक k3_ringacc_ring_pop_tail_proxy(काष्ठा k3_ring *ring, व्योम *elem);

अटल काष्ठा k3_ring_ops k3_ring_mode_proxy_ops = अणु
		.push_tail = k3_ringacc_ring_push_tail_proxy,
		.push_head = k3_ringacc_ring_push_head_proxy,
		.pop_tail = k3_ringacc_ring_pop_tail_proxy,
		.pop_head = k3_ringacc_ring_pop_head_proxy,
पूर्ण;

अटल व्योम k3_ringacc_ring_dump(काष्ठा k3_ring *ring)
अणु
	काष्ठा device *dev = ring->parent->dev;

	dev_dbg(dev, "dump ring: %d\n", ring->ring_id);
	dev_dbg(dev, "dump mem virt %p, dma %pad\n", ring->ring_mem_virt,
		&ring->ring_mem_dma);
	dev_dbg(dev, "dump elmsize %d, size %d, mode %d, proxy_id %d\n",
		ring->elm_size, ring->size, ring->mode, ring->proxy_id);
	dev_dbg(dev, "dump flags %08X\n", ring->flags);

	dev_dbg(dev, "dump ring_rt_regs: db%08x\n", पढ़ोl(&ring->rt->db));
	dev_dbg(dev, "dump occ%08x\n", पढ़ोl(&ring->rt->occ));
	dev_dbg(dev, "dump indx%08x\n", पढ़ोl(&ring->rt->indx));
	dev_dbg(dev, "dump hwocc%08x\n", पढ़ोl(&ring->rt->hwocc));
	dev_dbg(dev, "dump hwindx%08x\n", पढ़ोl(&ring->rt->hwindx));

	अगर (ring->ring_mem_virt)
		prपूर्णांक_hex_dump_debug("dump ring_mem_virt ", DUMP_PREFIX_NONE,
				     16, 1, ring->ring_mem_virt, 16 * 8, false);
पूर्ण

काष्ठा k3_ring *k3_ringacc_request_ring(काष्ठा k3_ringacc *ringacc,
					पूर्णांक id, u32 flags)
अणु
	पूर्णांक proxy_id = K3_RINGACC_PROXY_NOT_USED;

	mutex_lock(&ringacc->req_lock);

	अगर (id == K3_RINGACC_RING_ID_ANY) अणु
		/* Request क्रम any general purpose ring */
		काष्ठा ti_sci_resource_desc *gp_rings =
						&ringacc->rm_gp_range->desc[0];
		अचिन्हित दीर्घ size;

		size = gp_rings->start + gp_rings->num;
		id = find_next_zero_bit(ringacc->rings_inuse, size,
					gp_rings->start);
		अगर (id == size)
			जाओ error;
	पूर्ण अन्यथा अगर (id < 0) अणु
		जाओ error;
	पूर्ण

	अगर (test_bit(id, ringacc->rings_inuse) &&
	    !(ringacc->rings[id].flags & K3_RING_FLAG_SHARED))
		जाओ error;
	अन्यथा अगर (ringacc->rings[id].flags & K3_RING_FLAG_SHARED)
		जाओ out;

	अगर (flags & K3_RINGACC_RING_USE_PROXY) अणु
		proxy_id = find_next_zero_bit(ringacc->proxy_inuse,
					      ringacc->num_proxies, 0);
		अगर (proxy_id == ringacc->num_proxies)
			जाओ error;
	पूर्ण

	अगर (proxy_id != K3_RINGACC_PROXY_NOT_USED) अणु
		set_bit(proxy_id, ringacc->proxy_inuse);
		ringacc->rings[id].proxy_id = proxy_id;
		dev_dbg(ringacc->dev, "Giving ring#%d proxy#%d\n", id,
			proxy_id);
	पूर्ण अन्यथा अणु
		dev_dbg(ringacc->dev, "Giving ring#%d\n", id);
	पूर्ण

	set_bit(id, ringacc->rings_inuse);
out:
	ringacc->rings[id].use_count++;
	mutex_unlock(&ringacc->req_lock);
	वापस &ringacc->rings[id];

error:
	mutex_unlock(&ringacc->req_lock);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_request_ring);

अटल पूर्णांक k3_dmaring_request_dual_ring(काष्ठा k3_ringacc *ringacc, पूर्णांक fwd_id,
					काष्ठा k3_ring **fwd_ring,
					काष्ठा k3_ring **compl_ring)
अणु
	पूर्णांक ret = 0;

	/*
	 * DMA rings must be requested by ID, completion ring is the reverse
	 * side of the क्रमward ring
	 */
	अगर (fwd_id < 0)
		वापस -EINVAL;

	mutex_lock(&ringacc->req_lock);

	अगर (test_bit(fwd_id, ringacc->rings_inuse)) अणु
		ret = -EBUSY;
		जाओ error;
	पूर्ण

	*fwd_ring = &ringacc->rings[fwd_id];
	*compl_ring = &ringacc->rings[fwd_id + ringacc->num_rings];
	set_bit(fwd_id, ringacc->rings_inuse);
	ringacc->rings[fwd_id].use_count++;
	dev_dbg(ringacc->dev, "Giving ring#%d\n", fwd_id);

	mutex_unlock(&ringacc->req_lock);
	वापस 0;

error:
	mutex_unlock(&ringacc->req_lock);
	वापस ret;
पूर्ण

पूर्णांक k3_ringacc_request_rings_pair(काष्ठा k3_ringacc *ringacc,
				  पूर्णांक fwd_id, पूर्णांक compl_id,
				  काष्ठा k3_ring **fwd_ring,
				  काष्ठा k3_ring **compl_ring)
अणु
	पूर्णांक ret = 0;

	अगर (!fwd_ring || !compl_ring)
		वापस -EINVAL;

	अगर (ringacc->dma_rings)
		वापस k3_dmaring_request_dual_ring(ringacc, fwd_id,
						    fwd_ring, compl_ring);

	*fwd_ring = k3_ringacc_request_ring(ringacc, fwd_id, 0);
	अगर (!(*fwd_ring))
		वापस -ENODEV;

	*compl_ring = k3_ringacc_request_ring(ringacc, compl_id, 0);
	अगर (!(*compl_ring)) अणु
		k3_ringacc_ring_मुक्त(*fwd_ring);
		ret = -ENODEV;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_request_rings_pair);

अटल व्योम k3_ringacc_ring_reset_sci(काष्ठा k3_ring *ring)
अणु
	काष्ठा ti_sci_msg_rm_ring_cfg ring_cfg = अणु 0 पूर्ण;
	काष्ठा k3_ringacc *ringacc = ring->parent;
	पूर्णांक ret;

	ring_cfg.nav_id = ringacc->tisci_dev_id;
	ring_cfg.index = ring->ring_id;
	ring_cfg.valid_params = TI_SCI_MSG_VALUE_RM_RING_COUNT_VALID;
	ring_cfg.count = ring->size;

	ret = ringacc->tisci_ring_ops->set_cfg(ringacc->tisci, &ring_cfg);
	अगर (ret)
		dev_err(ringacc->dev, "TISCI reset ring fail (%d) ring_idx %d\n",
			ret, ring->ring_id);
पूर्ण

व्योम k3_ringacc_ring_reset(काष्ठा k3_ring *ring)
अणु
	अगर (!ring || !(ring->flags & K3_RING_FLAG_BUSY))
		वापस;

	स_रखो(&ring->state, 0, माप(ring->state));

	k3_ringacc_ring_reset_sci(ring);
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_ring_reset);

अटल व्योम k3_ringacc_ring_reconfig_qmode_sci(काष्ठा k3_ring *ring,
					       क्रमागत k3_ring_mode mode)
अणु
	काष्ठा ti_sci_msg_rm_ring_cfg ring_cfg = अणु 0 पूर्ण;
	काष्ठा k3_ringacc *ringacc = ring->parent;
	पूर्णांक ret;

	ring_cfg.nav_id = ringacc->tisci_dev_id;
	ring_cfg.index = ring->ring_id;
	ring_cfg.valid_params = TI_SCI_MSG_VALUE_RM_RING_MODE_VALID;
	ring_cfg.mode = mode;

	ret = ringacc->tisci_ring_ops->set_cfg(ringacc->tisci, &ring_cfg);
	अगर (ret)
		dev_err(ringacc->dev, "TISCI reconf qmode fail (%d) ring_idx %d\n",
			ret, ring->ring_id);
पूर्ण

व्योम k3_ringacc_ring_reset_dma(काष्ठा k3_ring *ring, u32 occ)
अणु
	अगर (!ring || !(ring->flags & K3_RING_FLAG_BUSY))
		वापस;

	अगर (!ring->parent->dma_ring_reset_quirk)
		जाओ reset;

	अगर (!occ)
		occ = k3_ringacc_ring_पढ़ो_occ(ring);

	अगर (occ) अणु
		u32 db_ring_cnt, db_ring_cnt_cur;

		dev_dbg(ring->parent->dev, "%s %u occ: %u\n", __func__,
			ring->ring_id, occ);
		/* TI-SCI ring reset */
		k3_ringacc_ring_reset_sci(ring);

		/*
		 * Setup the ring in ring/करोorbell mode (अगर not alपढ़ोy in this
		 * mode)
		 */
		अगर (ring->mode != K3_RINGACC_RING_MODE_RING)
			k3_ringacc_ring_reconfig_qmode_sci(
					ring, K3_RINGACC_RING_MODE_RING);
		/*
		 * Ring the करोorbell 2**22 ै  ringOcc बार.
		 * This will wrap the पूर्णांकernal UDMAP ring state occupancy
		 * counter (which is 21-bits wide) to 0.
		 */
		db_ring_cnt = (1U << 22) - occ;

		जबतक (db_ring_cnt != 0) अणु
			/*
			 * Ring the करोorbell with the maximum count each
			 * iteration अगर possible to minimize the total
			 * of ग_लिखोs
			 */
			अगर (db_ring_cnt > K3_RINGACC_MAX_DB_RING_CNT)
				db_ring_cnt_cur = K3_RINGACC_MAX_DB_RING_CNT;
			अन्यथा
				db_ring_cnt_cur = db_ring_cnt;

			ग_लिखोl(db_ring_cnt_cur, &ring->rt->db);
			db_ring_cnt -= db_ring_cnt_cur;
		पूर्ण

		/* Restore the original ring mode (अगर not ring mode) */
		अगर (ring->mode != K3_RINGACC_RING_MODE_RING)
			k3_ringacc_ring_reconfig_qmode_sci(ring, ring->mode);
	पूर्ण

reset:
	/* Reset the ring */
	k3_ringacc_ring_reset(ring);
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_ring_reset_dma);

अटल व्योम k3_ringacc_ring_मुक्त_sci(काष्ठा k3_ring *ring)
अणु
	काष्ठा ti_sci_msg_rm_ring_cfg ring_cfg = अणु 0 पूर्ण;
	काष्ठा k3_ringacc *ringacc = ring->parent;
	पूर्णांक ret;

	ring_cfg.nav_id = ringacc->tisci_dev_id;
	ring_cfg.index = ring->ring_id;
	ring_cfg.valid_params = TI_SCI_MSG_VALUE_RM_ALL_NO_ORDER;

	ret = ringacc->tisci_ring_ops->set_cfg(ringacc->tisci, &ring_cfg);
	अगर (ret)
		dev_err(ringacc->dev, "TISCI ring free fail (%d) ring_idx %d\n",
			ret, ring->ring_id);
पूर्ण

पूर्णांक k3_ringacc_ring_मुक्त(काष्ठा k3_ring *ring)
अणु
	काष्ठा k3_ringacc *ringacc;

	अगर (!ring)
		वापस -EINVAL;

	ringacc = ring->parent;

	/*
	 * DMA rings: rings shared memory and configuration, only क्रमward ring
	 * is configured and reverse ring considered as slave.
	 */
	अगर (ringacc->dma_rings && (ring->flags & K3_RING_FLAG_REVERSE))
		वापस 0;

	dev_dbg(ring->parent->dev, "flags: 0x%08x\n", ring->flags);

	अगर (!test_bit(ring->ring_id, ringacc->rings_inuse))
		वापस -EINVAL;

	mutex_lock(&ringacc->req_lock);

	अगर (--ring->use_count)
		जाओ out;

	अगर (!(ring->flags & K3_RING_FLAG_BUSY))
		जाओ no_init;

	k3_ringacc_ring_मुक्त_sci(ring);

	dma_मुक्त_coherent(ring->dma_dev,
			  ring->size * (4 << ring->elm_size),
			  ring->ring_mem_virt, ring->ring_mem_dma);
	ring->flags = 0;
	ring->ops = शून्य;
	ring->dma_dev = शून्य;
	ring->asel = 0;

	अगर (ring->proxy_id != K3_RINGACC_PROXY_NOT_USED) अणु
		clear_bit(ring->proxy_id, ringacc->proxy_inuse);
		ring->proxy = शून्य;
		ring->proxy_id = K3_RINGACC_PROXY_NOT_USED;
	पूर्ण

no_init:
	clear_bit(ring->ring_id, ringacc->rings_inuse);

out:
	mutex_unlock(&ringacc->req_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_ring_मुक्त);

u32 k3_ringacc_get_ring_id(काष्ठा k3_ring *ring)
अणु
	अगर (!ring)
		वापस -EINVAL;

	वापस ring->ring_id;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_get_ring_id);

u32 k3_ringacc_get_tisci_dev_id(काष्ठा k3_ring *ring)
अणु
	अगर (!ring)
		वापस -EINVAL;

	वापस ring->parent->tisci_dev_id;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_get_tisci_dev_id);

पूर्णांक k3_ringacc_get_ring_irq_num(काष्ठा k3_ring *ring)
अणु
	पूर्णांक irq_num;

	अगर (!ring)
		वापस -EINVAL;

	irq_num = ti_sci_पूर्णांकa_msi_get_virq(ring->parent->dev, ring->ring_id);
	अगर (irq_num <= 0)
		irq_num = -EINVAL;
	वापस irq_num;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_get_ring_irq_num);

अटल पूर्णांक k3_ringacc_ring_cfg_sci(काष्ठा k3_ring *ring)
अणु
	काष्ठा ti_sci_msg_rm_ring_cfg ring_cfg = अणु 0 पूर्ण;
	काष्ठा k3_ringacc *ringacc = ring->parent;
	पूर्णांक ret;

	अगर (!ringacc->tisci)
		वापस -EINVAL;

	ring_cfg.nav_id = ringacc->tisci_dev_id;
	ring_cfg.index = ring->ring_id;
	ring_cfg.valid_params = TI_SCI_MSG_VALUE_RM_ALL_NO_ORDER;
	ring_cfg.addr_lo = lower_32_bits(ring->ring_mem_dma);
	ring_cfg.addr_hi = upper_32_bits(ring->ring_mem_dma);
	ring_cfg.count = ring->size;
	ring_cfg.mode = ring->mode;
	ring_cfg.size = ring->elm_size;
	ring_cfg.asel = ring->asel;

	ret = ringacc->tisci_ring_ops->set_cfg(ringacc->tisci, &ring_cfg);
	अगर (ret)
		dev_err(ringacc->dev, "TISCI config ring fail (%d) ring_idx %d\n",
			ret, ring->ring_id);

	वापस ret;
पूर्ण

अटल पूर्णांक k3_dmaring_cfg(काष्ठा k3_ring *ring, काष्ठा k3_ring_cfg *cfg)
अणु
	काष्ठा k3_ringacc *ringacc;
	काष्ठा k3_ring *reverse_ring;
	पूर्णांक ret = 0;

	अगर (cfg->elm_size != K3_RINGACC_RING_ELSIZE_8 ||
	    cfg->mode != K3_RINGACC_RING_MODE_RING ||
	    cfg->size & ~K3_DMARING_CFG_RING_SIZE_ELCNT_MASK)
		वापस -EINVAL;

	ringacc = ring->parent;

	/*
	 * DMA rings: rings shared memory and configuration, only क्रमward ring
	 * is configured and reverse ring considered as slave.
	 */
	अगर (ringacc->dma_rings && (ring->flags & K3_RING_FLAG_REVERSE))
		वापस 0;

	अगर (!test_bit(ring->ring_id, ringacc->rings_inuse))
		वापस -EINVAL;

	ring->size = cfg->size;
	ring->elm_size = cfg->elm_size;
	ring->mode = cfg->mode;
	ring->asel = cfg->asel;
	ring->dma_dev = cfg->dma_dev;
	अगर (!ring->dma_dev) अणु
		dev_warn(ringacc->dev, "dma_dev is not provided for ring%d\n",
			 ring->ring_id);
		ring->dma_dev = ringacc->dev;
	पूर्ण

	स_रखो(&ring->state, 0, माप(ring->state));

	ring->ops = &k3_dmaring_fwd_ops;

	ring->ring_mem_virt = dma_alloc_coherent(ring->dma_dev,
						 ring->size * (4 << ring->elm_size),
						 &ring->ring_mem_dma, GFP_KERNEL);
	अगर (!ring->ring_mem_virt) अणु
		dev_err(ringacc->dev, "Failed to alloc ring mem\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_ops;
	पूर्ण

	ret = k3_ringacc_ring_cfg_sci(ring);
	अगर (ret)
		जाओ err_मुक्त_mem;

	ring->flags |= K3_RING_FLAG_BUSY;

	k3_ringacc_ring_dump(ring);

	/* DMA rings: configure reverse ring */
	reverse_ring = &ringacc->rings[ring->ring_id + ringacc->num_rings];
	reverse_ring->size = cfg->size;
	reverse_ring->elm_size = cfg->elm_size;
	reverse_ring->mode = cfg->mode;
	reverse_ring->asel = cfg->asel;
	स_रखो(&reverse_ring->state, 0, माप(reverse_ring->state));
	reverse_ring->ops = &k3_dmaring_reverse_ops;

	reverse_ring->ring_mem_virt = ring->ring_mem_virt;
	reverse_ring->ring_mem_dma = ring->ring_mem_dma;
	reverse_ring->flags |= K3_RING_FLAG_BUSY;
	k3_ringacc_ring_dump(reverse_ring);

	वापस 0;

err_मुक्त_mem:
	dma_मुक्त_coherent(ring->dma_dev,
			  ring->size * (4 << ring->elm_size),
			  ring->ring_mem_virt,
			  ring->ring_mem_dma);
err_मुक्त_ops:
	ring->ops = शून्य;
	ring->proxy = शून्य;
	ring->dma_dev = शून्य;
	ring->asel = 0;
	वापस ret;
पूर्ण

पूर्णांक k3_ringacc_ring_cfg(काष्ठा k3_ring *ring, काष्ठा k3_ring_cfg *cfg)
अणु
	काष्ठा k3_ringacc *ringacc;
	पूर्णांक ret = 0;

	अगर (!ring || !cfg)
		वापस -EINVAL;

	ringacc = ring->parent;

	अगर (ringacc->dma_rings)
		वापस k3_dmaring_cfg(ring, cfg);

	अगर (cfg->elm_size > K3_RINGACC_RING_ELSIZE_256 ||
	    cfg->mode >= K3_RINGACC_RING_MODE_INVALID ||
	    cfg->size & ~K3_RINGACC_CFG_RING_SIZE_ELCNT_MASK ||
	    !test_bit(ring->ring_id, ringacc->rings_inuse))
		वापस -EINVAL;

	अगर (cfg->mode == K3_RINGACC_RING_MODE_MESSAGE &&
	    ring->proxy_id == K3_RINGACC_PROXY_NOT_USED &&
	    cfg->elm_size > K3_RINGACC_RING_ELSIZE_8) अणु
		dev_err(ringacc->dev,
			"Message mode must use proxy for %u element size\n",
			4 << ring->elm_size);
		वापस -EINVAL;
	पूर्ण

	/*
	 * In हाल of shared ring only the first user (master user) can
	 * configure the ring. The sequence should be by the client:
	 * ring = k3_ringacc_request_ring(ringacc, ring_id, 0); # master user
	 * k3_ringacc_ring_cfg(ring, cfg); # master configuration
	 * k3_ringacc_request_ring(ringacc, ring_id, K3_RING_FLAG_SHARED);
	 * k3_ringacc_request_ring(ringacc, ring_id, K3_RING_FLAG_SHARED);
	 */
	अगर (ring->use_count != 1)
		वापस 0;

	ring->size = cfg->size;
	ring->elm_size = cfg->elm_size;
	ring->mode = cfg->mode;
	स_रखो(&ring->state, 0, माप(ring->state));

	अगर (ring->proxy_id != K3_RINGACC_PROXY_NOT_USED)
		ring->proxy = ringacc->proxy_target_base +
			      ring->proxy_id * K3_RINGACC_PROXY_TARGET_STEP;

	चयन (ring->mode) अणु
	हाल K3_RINGACC_RING_MODE_RING:
		ring->ops = &k3_ring_mode_ring_ops;
		ring->dma_dev = cfg->dma_dev;
		अगर (!ring->dma_dev)
			ring->dma_dev = ringacc->dev;
		अवरोध;
	हाल K3_RINGACC_RING_MODE_MESSAGE:
		ring->dma_dev = ringacc->dev;
		अगर (ring->proxy)
			ring->ops = &k3_ring_mode_proxy_ops;
		अन्यथा
			ring->ops = &k3_ring_mode_msg_ops;
		अवरोध;
	शेष:
		ring->ops = शून्य;
		ret = -EINVAL;
		जाओ err_मुक्त_proxy;
	पूर्ण

	ring->ring_mem_virt = dma_alloc_coherent(ring->dma_dev,
						 ring->size * (4 << ring->elm_size),
						 &ring->ring_mem_dma, GFP_KERNEL);
	अगर (!ring->ring_mem_virt) अणु
		dev_err(ringacc->dev, "Failed to alloc ring mem\n");
		ret = -ENOMEM;
		जाओ err_मुक्त_ops;
	पूर्ण

	ret = k3_ringacc_ring_cfg_sci(ring);

	अगर (ret)
		जाओ err_मुक्त_mem;

	ring->flags |= K3_RING_FLAG_BUSY;
	ring->flags |= (cfg->flags & K3_RINGACC_RING_SHARED) ?
			K3_RING_FLAG_SHARED : 0;

	k3_ringacc_ring_dump(ring);

	वापस 0;

err_मुक्त_mem:
	dma_मुक्त_coherent(ring->dma_dev,
			  ring->size * (4 << ring->elm_size),
			  ring->ring_mem_virt,
			  ring->ring_mem_dma);
err_मुक्त_ops:
	ring->ops = शून्य;
	ring->dma_dev = शून्य;
err_मुक्त_proxy:
	ring->proxy = शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_ring_cfg);

u32 k3_ringacc_ring_get_size(काष्ठा k3_ring *ring)
अणु
	अगर (!ring || !(ring->flags & K3_RING_FLAG_BUSY))
		वापस -EINVAL;

	वापस ring->size;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_ring_get_size);

u32 k3_ringacc_ring_get_मुक्त(काष्ठा k3_ring *ring)
अणु
	अगर (!ring || !(ring->flags & K3_RING_FLAG_BUSY))
		वापस -EINVAL;

	अगर (!ring->state.मुक्त)
		ring->state.मुक्त = ring->size - k3_ringacc_ring_पढ़ो_occ(ring);

	वापस ring->state.मुक्त;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_ring_get_मुक्त);

u32 k3_ringacc_ring_get_occ(काष्ठा k3_ring *ring)
अणु
	अगर (!ring || !(ring->flags & K3_RING_FLAG_BUSY))
		वापस -EINVAL;

	वापस k3_ringacc_ring_पढ़ो_occ(ring);
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_ring_get_occ);

u32 k3_ringacc_ring_is_full(काष्ठा k3_ring *ring)
अणु
	वापस !k3_ringacc_ring_get_मुक्त(ring);
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_ring_is_full);

क्रमागत k3_ringacc_access_mode अणु
	K3_RINGACC_ACCESS_MODE_PUSH_HEAD,
	K3_RINGACC_ACCESS_MODE_POP_HEAD,
	K3_RINGACC_ACCESS_MODE_PUSH_TAIL,
	K3_RINGACC_ACCESS_MODE_POP_TAIL,
	K3_RINGACC_ACCESS_MODE_PEEK_HEAD,
	K3_RINGACC_ACCESS_MODE_PEEK_TAIL,
पूर्ण;

#घोषणा K3_RINGACC_PROXY_MODE(x)	(((x) & 0x3) << 16)
#घोषणा K3_RINGACC_PROXY_ELSIZE(x)	(((x) & 0x7) << 24)
अटल पूर्णांक k3_ringacc_ring_cfg_proxy(काष्ठा k3_ring *ring,
				     क्रमागत k3_ringacc_proxy_access_mode mode)
अणु
	u32 val;

	val = ring->ring_id;
	val |= K3_RINGACC_PROXY_MODE(mode);
	val |= K3_RINGACC_PROXY_ELSIZE(ring->elm_size);
	ग_लिखोl(val, &ring->proxy->control);
	वापस 0;
पूर्ण

अटल पूर्णांक k3_ringacc_ring_access_proxy(काष्ठा k3_ring *ring, व्योम *elem,
					क्रमागत k3_ringacc_access_mode access_mode)
अणु
	व्योम __iomem *ptr;

	ptr = (व्योम __iomem *)&ring->proxy->data;

	चयन (access_mode) अणु
	हाल K3_RINGACC_ACCESS_MODE_PUSH_HEAD:
	हाल K3_RINGACC_ACCESS_MODE_POP_HEAD:
		k3_ringacc_ring_cfg_proxy(ring, PROXY_ACCESS_MODE_HEAD);
		अवरोध;
	हाल K3_RINGACC_ACCESS_MODE_PUSH_TAIL:
	हाल K3_RINGACC_ACCESS_MODE_POP_TAIL:
		k3_ringacc_ring_cfg_proxy(ring, PROXY_ACCESS_MODE_TAIL);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ptr += k3_ringacc_ring_get_fअगरo_pos(ring);

	चयन (access_mode) अणु
	हाल K3_RINGACC_ACCESS_MODE_POP_HEAD:
	हाल K3_RINGACC_ACCESS_MODE_POP_TAIL:
		dev_dbg(ring->parent->dev,
			"proxy:memcpy_fromio(x): --> ptr(%p), mode:%d\n", ptr,
			access_mode);
		स_नकल_fromio(elem, ptr, (4 << ring->elm_size));
		ring->state.occ--;
		अवरोध;
	हाल K3_RINGACC_ACCESS_MODE_PUSH_TAIL:
	हाल K3_RINGACC_ACCESS_MODE_PUSH_HEAD:
		dev_dbg(ring->parent->dev,
			"proxy:memcpy_toio(x): --> ptr(%p), mode:%d\n", ptr,
			access_mode);
		स_नकल_toio(ptr, elem, (4 << ring->elm_size));
		ring->state.मुक्त--;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(ring->parent->dev, "proxy: free%d occ%d\n", ring->state.मुक्त,
		ring->state.occ);
	वापस 0;
पूर्ण

अटल पूर्णांक k3_ringacc_ring_push_head_proxy(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	वापस k3_ringacc_ring_access_proxy(ring, elem,
					    K3_RINGACC_ACCESS_MODE_PUSH_HEAD);
पूर्ण

अटल पूर्णांक k3_ringacc_ring_push_tail_proxy(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	वापस k3_ringacc_ring_access_proxy(ring, elem,
					    K3_RINGACC_ACCESS_MODE_PUSH_TAIL);
पूर्ण

अटल पूर्णांक k3_ringacc_ring_pop_head_proxy(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	वापस k3_ringacc_ring_access_proxy(ring, elem,
					    K3_RINGACC_ACCESS_MODE_POP_HEAD);
पूर्ण

अटल पूर्णांक k3_ringacc_ring_pop_tail_proxy(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	वापस k3_ringacc_ring_access_proxy(ring, elem,
					    K3_RINGACC_ACCESS_MODE_POP_HEAD);
पूर्ण

अटल पूर्णांक k3_ringacc_ring_access_io(काष्ठा k3_ring *ring, व्योम *elem,
				     क्रमागत k3_ringacc_access_mode access_mode)
अणु
	व्योम __iomem *ptr;

	चयन (access_mode) अणु
	हाल K3_RINGACC_ACCESS_MODE_PUSH_HEAD:
	हाल K3_RINGACC_ACCESS_MODE_POP_HEAD:
		ptr = (व्योम __iomem *)&ring->fअगरos->head_data;
		अवरोध;
	हाल K3_RINGACC_ACCESS_MODE_PUSH_TAIL:
	हाल K3_RINGACC_ACCESS_MODE_POP_TAIL:
		ptr = (व्योम __iomem *)&ring->fअगरos->tail_data;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ptr += k3_ringacc_ring_get_fअगरo_pos(ring);

	चयन (access_mode) अणु
	हाल K3_RINGACC_ACCESS_MODE_POP_HEAD:
	हाल K3_RINGACC_ACCESS_MODE_POP_TAIL:
		dev_dbg(ring->parent->dev,
			"memcpy_fromio(x): --> ptr(%p), mode:%d\n", ptr,
			access_mode);
		स_नकल_fromio(elem, ptr, (4 << ring->elm_size));
		ring->state.occ--;
		अवरोध;
	हाल K3_RINGACC_ACCESS_MODE_PUSH_TAIL:
	हाल K3_RINGACC_ACCESS_MODE_PUSH_HEAD:
		dev_dbg(ring->parent->dev,
			"memcpy_toio(x): --> ptr(%p), mode:%d\n", ptr,
			access_mode);
		स_नकल_toio(ptr, elem, (4 << ring->elm_size));
		ring->state.मुक्त--;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(ring->parent->dev, "free%d index%d occ%d index%d\n",
		ring->state.मुक्त, ring->state.windex, ring->state.occ,
		ring->state.rindex);
	वापस 0;
पूर्ण

अटल पूर्णांक k3_ringacc_ring_push_head_io(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	वापस k3_ringacc_ring_access_io(ring, elem,
					 K3_RINGACC_ACCESS_MODE_PUSH_HEAD);
पूर्ण

अटल पूर्णांक k3_ringacc_ring_push_io(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	वापस k3_ringacc_ring_access_io(ring, elem,
					 K3_RINGACC_ACCESS_MODE_PUSH_TAIL);
पूर्ण

अटल पूर्णांक k3_ringacc_ring_pop_io(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	वापस k3_ringacc_ring_access_io(ring, elem,
					 K3_RINGACC_ACCESS_MODE_POP_HEAD);
पूर्ण

अटल पूर्णांक k3_ringacc_ring_pop_tail_io(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	वापस k3_ringacc_ring_access_io(ring, elem,
					 K3_RINGACC_ACCESS_MODE_POP_HEAD);
पूर्ण

/*
 * The element is 48 bits of address + ASEL bits in the ring.
 * ASEL is used by the DMAs and should be हटाओd क्रम the kernel as it is not
 * part of the physical memory address.
 */
अटल व्योम k3_dmaring_हटाओ_asel_from_elem(u64 *elem)
अणु
	*elem &= GENMASK_ULL(K3_ADDRESS_ASEL_SHIFT - 1, 0);
पूर्ण

अटल पूर्णांक k3_dmaring_fwd_pop(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	व्योम *elem_ptr;
	u32 elem_idx;

	/*
	 * DMA rings: क्रमward ring is always tied DMA channel and HW करोes not
	 * मुख्यtain any state data required क्रम POP operation and its unknown
	 * how much elements were consumed by HW. So, to actually
	 * करो POP, the पढ़ो poपूर्णांकer has to be recalculated every समय.
	 */
	ring->state.occ = k3_ringacc_ring_पढ़ो_occ(ring);
	अगर (ring->state.windex >= ring->state.occ)
		elem_idx = ring->state.windex - ring->state.occ;
	अन्यथा
		elem_idx = ring->size - (ring->state.occ - ring->state.windex);

	elem_ptr = k3_ringacc_get_elm_addr(ring, elem_idx);
	स_नकल(elem, elem_ptr, (4 << ring->elm_size));
	k3_dmaring_हटाओ_asel_from_elem(elem);

	ring->state.occ--;
	ग_लिखोl(-1, &ring->rt->db);

	dev_dbg(ring->parent->dev, "%s: occ%d Windex%d Rindex%d pos_ptr%px\n",
		__func__, ring->state.occ, ring->state.windex, elem_idx,
		elem_ptr);
	वापस 0;
पूर्ण

अटल पूर्णांक k3_dmaring_reverse_pop(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	व्योम *elem_ptr;

	elem_ptr = k3_ringacc_get_elm_addr(ring, ring->state.rindex);

	अगर (ring->state.occ) अणु
		स_नकल(elem, elem_ptr, (4 << ring->elm_size));
		k3_dmaring_हटाओ_asel_from_elem(elem);

		ring->state.rindex = (ring->state.rindex + 1) % ring->size;
		ring->state.occ--;
		ग_लिखोl(-1 & K3_DMARING_RT_DB_ENTRY_MASK, &ring->rt->db);
	पूर्ण अन्यथा अगर (ring->state.tकरोwn_complete) अणु
		dma_addr_t *value = elem;

		*value = CPPI5_TDCM_MARKER;
		ग_लिखोl(K3_DMARING_RT_DB_TDOWN_ACK, &ring->rt->db);
		ring->state.tकरोwn_complete = false;
	पूर्ण

	dev_dbg(ring->parent->dev, "%s: occ%d index%d pos_ptr%px\n",
		__func__, ring->state.occ, ring->state.rindex, elem_ptr);
	वापस 0;
पूर्ण

अटल पूर्णांक k3_ringacc_ring_push_mem(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	व्योम *elem_ptr;

	elem_ptr = k3_ringacc_get_elm_addr(ring, ring->state.windex);

	स_नकल(elem_ptr, elem, (4 << ring->elm_size));
	अगर (ring->parent->dma_rings) अणु
		u64 *addr = elem_ptr;

		*addr |= ((u64)ring->asel << K3_ADDRESS_ASEL_SHIFT);
	पूर्ण

	ring->state.windex = (ring->state.windex + 1) % ring->size;
	ring->state.मुक्त--;
	ग_लिखोl(1, &ring->rt->db);

	dev_dbg(ring->parent->dev, "ring_push_mem: free%d index%d\n",
		ring->state.मुक्त, ring->state.windex);

	वापस 0;
पूर्ण

अटल पूर्णांक k3_ringacc_ring_pop_mem(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	व्योम *elem_ptr;

	elem_ptr = k3_ringacc_get_elm_addr(ring, ring->state.rindex);

	स_नकल(elem, elem_ptr, (4 << ring->elm_size));

	ring->state.rindex = (ring->state.rindex + 1) % ring->size;
	ring->state.occ--;
	ग_लिखोl(-1, &ring->rt->db);

	dev_dbg(ring->parent->dev, "ring_pop_mem: occ%d index%d pos_ptr%p\n",
		ring->state.occ, ring->state.rindex, elem_ptr);
	वापस 0;
पूर्ण

पूर्णांक k3_ringacc_ring_push(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (!ring || !(ring->flags & K3_RING_FLAG_BUSY))
		वापस -EINVAL;

	dev_dbg(ring->parent->dev, "ring_push: free%d index%d\n",
		ring->state.मुक्त, ring->state.windex);

	अगर (k3_ringacc_ring_is_full(ring))
		वापस -ENOMEM;

	अगर (ring->ops && ring->ops->push_tail)
		ret = ring->ops->push_tail(ring, elem);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_ring_push);

पूर्णांक k3_ringacc_ring_push_head(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (!ring || !(ring->flags & K3_RING_FLAG_BUSY))
		वापस -EINVAL;

	dev_dbg(ring->parent->dev, "ring_push_head: free%d index%d\n",
		ring->state.मुक्त, ring->state.windex);

	अगर (k3_ringacc_ring_is_full(ring))
		वापस -ENOMEM;

	अगर (ring->ops && ring->ops->push_head)
		ret = ring->ops->push_head(ring, elem);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_ring_push_head);

पूर्णांक k3_ringacc_ring_pop(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (!ring || !(ring->flags & K3_RING_FLAG_BUSY))
		वापस -EINVAL;

	अगर (!ring->state.occ)
		k3_ringacc_ring_update_occ(ring);

	dev_dbg(ring->parent->dev, "ring_pop: occ%d index%d\n", ring->state.occ,
		ring->state.rindex);

	अगर (!ring->state.occ && !ring->state.tकरोwn_complete)
		वापस -ENODATA;

	अगर (ring->ops && ring->ops->pop_head)
		ret = ring->ops->pop_head(ring, elem);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_ring_pop);

पूर्णांक k3_ringacc_ring_pop_tail(काष्ठा k3_ring *ring, व्योम *elem)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (!ring || !(ring->flags & K3_RING_FLAG_BUSY))
		वापस -EINVAL;

	अगर (!ring->state.occ)
		k3_ringacc_ring_update_occ(ring);

	dev_dbg(ring->parent->dev, "ring_pop_tail: occ%d index%d\n",
		ring->state.occ, ring->state.rindex);

	अगर (!ring->state.occ)
		वापस -ENODATA;

	अगर (ring->ops && ring->ops->pop_tail)
		ret = ring->ops->pop_tail(ring, elem);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_ring_pop_tail);

काष्ठा k3_ringacc *of_k3_ringacc_get_by_phandle(काष्ठा device_node *np,
						स्थिर अक्षर *property)
अणु
	काष्ठा device_node *ringacc_np;
	काष्ठा k3_ringacc *ringacc = ERR_PTR(-EPROBE_DEFER);
	काष्ठा k3_ringacc *entry;

	ringacc_np = of_parse_phandle(np, property, 0);
	अगर (!ringacc_np)
		वापस ERR_PTR(-ENODEV);

	mutex_lock(&k3_ringacc_list_lock);
	list_क्रम_each_entry(entry, &k3_ringacc_list, list)
		अगर (entry->dev->of_node == ringacc_np) अणु
			ringacc = entry;
			अवरोध;
		पूर्ण
	mutex_unlock(&k3_ringacc_list_lock);
	of_node_put(ringacc_np);

	वापस ringacc;
पूर्ण
EXPORT_SYMBOL_GPL(of_k3_ringacc_get_by_phandle);

अटल पूर्णांक k3_ringacc_probe_dt(काष्ठा k3_ringacc *ringacc)
अणु
	काष्ठा device_node *node = ringacc->dev->of_node;
	काष्ठा device *dev = ringacc->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक ret;

	अगर (!node) अणु
		dev_err(dev, "device tree info unavailable\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "ti,num-rings", &ringacc->num_rings);
	अगर (ret) अणु
		dev_err(dev, "ti,num-rings read failure %d\n", ret);
		वापस ret;
	पूर्ण

	ringacc->tisci = ti_sci_get_by_phandle(node, "ti,sci");
	अगर (IS_ERR(ringacc->tisci)) अणु
		ret = PTR_ERR(ringacc->tisci);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "ti,sci read fail %d\n", ret);
		ringacc->tisci = शून्य;
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(node, "ti,sci-dev-id",
				   &ringacc->tisci_dev_id);
	अगर (ret) अणु
		dev_err(dev, "ti,sci-dev-id read fail %d\n", ret);
		वापस ret;
	पूर्ण

	pdev->id = ringacc->tisci_dev_id;

	ringacc->rm_gp_range = devm_ti_sci_get_of_resource(ringacc->tisci, dev,
						ringacc->tisci_dev_id,
						"ti,sci-rm-range-gp-rings");
	अगर (IS_ERR(ringacc->rm_gp_range)) अणु
		dev_err(dev, "Failed to allocate MSI interrupts\n");
		वापस PTR_ERR(ringacc->rm_gp_range);
	पूर्ण

	वापस ti_sci_पूर्णांकa_msi_करोमुख्य_alloc_irqs(ringacc->dev,
						 ringacc->rm_gp_range);
पूर्ण

अटल स्थिर काष्ठा k3_ringacc_soc_data k3_ringacc_soc_data_sr1 = अणु
	.dma_ring_reset_quirk = 1,
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute k3_ringacc_socinfo[] = अणु
	अणु .family = "AM65X",
	  .revision = "SR1.0",
	  .data = &k3_ringacc_soc_data_sr1
	पूर्ण,
	अणु/* sentinel */पूर्ण
पूर्ण;

अटल पूर्णांक k3_ringacc_init(काष्ठा platक्रमm_device *pdev,
			   काष्ठा k3_ringacc *ringacc)
अणु
	स्थिर काष्ठा soc_device_attribute *soc;
	व्योम __iomem *base_fअगरo, *base_rt;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	पूर्णांक ret, i;

	dev->msi_करोमुख्य = of_msi_get_करोमुख्य(dev, dev->of_node,
					    DOMAIN_BUS_TI_SCI_INTA_MSI);
	अगर (!dev->msi_करोमुख्य) अणु
		dev_err(dev, "Failed to get MSI domain\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	ret = k3_ringacc_probe_dt(ringacc);
	अगर (ret)
		वापस ret;

	soc = soc_device_match(k3_ringacc_socinfo);
	अगर (soc && soc->data) अणु
		स्थिर काष्ठा k3_ringacc_soc_data *soc_data = soc->data;

		ringacc->dma_ring_reset_quirk = soc_data->dma_ring_reset_quirk;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "rt");
	base_rt = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base_rt))
		वापस PTR_ERR(base_rt);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "fifos");
	base_fअगरo = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base_fअगरo))
		वापस PTR_ERR(base_fअगरo);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "proxy_gcfg");
	ringacc->proxy_gcfg = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ringacc->proxy_gcfg))
		वापस PTR_ERR(ringacc->proxy_gcfg);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   "proxy_target");
	ringacc->proxy_target_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ringacc->proxy_target_base))
		वापस PTR_ERR(ringacc->proxy_target_base);

	ringacc->num_proxies = पढ़ोl(&ringacc->proxy_gcfg->config) &
				     K3_RINGACC_PROXY_CFG_THREADS_MASK;

	ringacc->rings = devm_kzalloc(dev,
				      माप(*ringacc->rings) *
				      ringacc->num_rings,
				      GFP_KERNEL);
	ringacc->rings_inuse = devm_kसुस्मृति(dev,
					    BITS_TO_LONGS(ringacc->num_rings),
					    माप(अचिन्हित दीर्घ), GFP_KERNEL);
	ringacc->proxy_inuse = devm_kसुस्मृति(dev,
					    BITS_TO_LONGS(ringacc->num_proxies),
					    माप(अचिन्हित दीर्घ), GFP_KERNEL);

	अगर (!ringacc->rings || !ringacc->rings_inuse || !ringacc->proxy_inuse)
		वापस -ENOMEM;

	क्रम (i = 0; i < ringacc->num_rings; i++) अणु
		ringacc->rings[i].rt = base_rt +
				       K3_RINGACC_RT_REGS_STEP * i;
		ringacc->rings[i].fअगरos = base_fअगरo +
					  K3_RINGACC_FIFO_REGS_STEP * i;
		ringacc->rings[i].parent = ringacc;
		ringacc->rings[i].ring_id = i;
		ringacc->rings[i].proxy_id = K3_RINGACC_PROXY_NOT_USED;
	पूर्ण

	ringacc->tisci_ring_ops = &ringacc->tisci->ops.rm_ring_ops;

	dev_info(dev, "Ring Accelerator probed rings:%u, gp-rings[%u,%u] sci-dev-id:%u\n",
		 ringacc->num_rings,
		 ringacc->rm_gp_range->desc[0].start,
		 ringacc->rm_gp_range->desc[0].num,
		 ringacc->tisci_dev_id);
	dev_info(dev, "dma-ring-reset-quirk: %s\n",
		 ringacc->dma_ring_reset_quirk ? "enabled" : "disabled");
	dev_info(dev, "RA Proxy rev. %08x, num_proxies:%u\n",
		 पढ़ोl(&ringacc->proxy_gcfg->revision), ringacc->num_proxies);

	वापस 0;
पूर्ण

काष्ठा ringacc_match_data अणु
	काष्ठा k3_ringacc_ops ops;
पूर्ण;

अटल काष्ठा ringacc_match_data k3_ringacc_data = अणु
	.ops = अणु
		.init = k3_ringacc_init,
	पूर्ण,
पूर्ण;

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id k3_ringacc_of_match[] = अणु
	अणु .compatible = "ti,am654-navss-ringacc", .data = &k3_ringacc_data, पूर्ण,
	अणुपूर्ण,
पूर्ण;

काष्ठा k3_ringacc *k3_ringacc_dmarings_init(काष्ठा platक्रमm_device *pdev,
					    काष्ठा k3_ringacc_init_data *data)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा k3_ringacc *ringacc;
	व्योम __iomem *base_rt;
	काष्ठा resource *res;
	पूर्णांक i;

	ringacc = devm_kzalloc(dev, माप(*ringacc), GFP_KERNEL);
	अगर (!ringacc)
		वापस ERR_PTR(-ENOMEM);

	ringacc->dev = dev;
	ringacc->dma_rings = true;
	ringacc->num_rings = data->num_rings;
	ringacc->tisci = data->tisci;
	ringacc->tisci_dev_id = data->tisci_dev_id;

	mutex_init(&ringacc->req_lock);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "ringrt");
	base_rt = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base_rt))
		वापस ERR_CAST(base_rt);

	ringacc->rings = devm_kzalloc(dev,
				      माप(*ringacc->rings) *
				      ringacc->num_rings * 2,
				      GFP_KERNEL);
	ringacc->rings_inuse = devm_kसुस्मृति(dev,
					    BITS_TO_LONGS(ringacc->num_rings),
					    माप(अचिन्हित दीर्घ), GFP_KERNEL);

	अगर (!ringacc->rings || !ringacc->rings_inuse)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < ringacc->num_rings; i++) अणु
		काष्ठा k3_ring *ring = &ringacc->rings[i];

		ring->rt = base_rt + K3_DMARING_RT_REGS_STEP * i;
		ring->parent = ringacc;
		ring->ring_id = i;
		ring->proxy_id = K3_RINGACC_PROXY_NOT_USED;

		ring = &ringacc->rings[ringacc->num_rings + i];
		ring->rt = base_rt + K3_DMARING_RT_REGS_STEP * i +
			   K3_DMARING_RT_REGS_REVERSE_OFS;
		ring->parent = ringacc;
		ring->ring_id = i;
		ring->proxy_id = K3_RINGACC_PROXY_NOT_USED;
		ring->flags = K3_RING_FLAG_REVERSE;
	पूर्ण

	ringacc->tisci_ring_ops = &ringacc->tisci->ops.rm_ring_ops;

	dev_info(dev, "Number of rings: %u\n", ringacc->num_rings);

	वापस ringacc;
पूर्ण
EXPORT_SYMBOL_GPL(k3_ringacc_dmarings_init);

अटल पूर्णांक k3_ringacc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा ringacc_match_data *match_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा k3_ringacc *ringacc;
	पूर्णांक ret;

	match_data = of_device_get_match_data(&pdev->dev);
	अगर (!match_data)
		वापस -ENODEV;

	ringacc = devm_kzalloc(dev, माप(*ringacc), GFP_KERNEL);
	अगर (!ringacc)
		वापस -ENOMEM;

	ringacc->dev = dev;
	mutex_init(&ringacc->req_lock);
	ringacc->ops = &match_data->ops;

	ret = ringacc->ops->init(pdev, ringacc);
	अगर (ret)
		वापस ret;

	dev_set_drvdata(dev, ringacc);

	mutex_lock(&k3_ringacc_list_lock);
	list_add_tail(&ringacc->list, &k3_ringacc_list);
	mutex_unlock(&k3_ringacc_list_lock);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver k3_ringacc_driver = अणु
	.probe		= k3_ringacc_probe,
	.driver		= अणु
		.name	= "k3-ringacc",
		.of_match_table = k3_ringacc_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(k3_ringacc_driver);
