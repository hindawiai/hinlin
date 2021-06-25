<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com
 *  Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/completion.h>
#समावेश <linux/soc/ti/k3-ringacc.h>
#समावेश <linux/soc/ti/ti_sci_protocol.h>
#समावेश <linux/soc/ti/ti_sci_पूर्णांकa_msi.h>
#समावेश <linux/dma/k3-event-router.h>
#समावेश <linux/dma/ti-cppi5.h>

#समावेश "../virt-dma.h"
#समावेश "k3-udma.h"
#समावेश "k3-psil-priv.h"

काष्ठा udma_अटल_tr अणु
	u8 elsize; /* RPSTR0 */
	u16 elcnt; /* RPSTR0 */
	u16 bstcnt; /* RPSTR1 */
पूर्ण;

#घोषणा K3_UDMA_MAX_RFLOWS		1024
#घोषणा K3_UDMA_DEFAULT_RING_SIZE	16

/* How SRC/DST tag should be updated by UDMA in the descriptor's Word 3 */
#घोषणा UDMA_RFLOW_SRCTAG_NONE		0
#घोषणा UDMA_RFLOW_SRCTAG_CFG_TAG	1
#घोषणा UDMA_RFLOW_SRCTAG_FLOW_ID	2
#घोषणा UDMA_RFLOW_SRCTAG_SRC_TAG	4

#घोषणा UDMA_RFLOW_DSTTAG_NONE		0
#घोषणा UDMA_RFLOW_DSTTAG_CFG_TAG	1
#घोषणा UDMA_RFLOW_DSTTAG_FLOW_ID	2
#घोषणा UDMA_RFLOW_DSTTAG_DST_TAG_LO	4
#घोषणा UDMA_RFLOW_DSTTAG_DST_TAG_HI	5

काष्ठा udma_chan;

क्रमागत k3_dma_type अणु
	DMA_TYPE_UDMA = 0,
	DMA_TYPE_BCDMA,
	DMA_TYPE_PKTDMA,
पूर्ण;

क्रमागत udma_mmr अणु
	MMR_GCFG = 0,
	MMR_BCHANRT,
	MMR_RCHANRT,
	MMR_TCHANRT,
	MMR_LAST,
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmr_names[] = अणु
	[MMR_GCFG] = "gcfg",
	[MMR_BCHANRT] = "bchanrt",
	[MMR_RCHANRT] = "rchanrt",
	[MMR_TCHANRT] = "tchanrt",
पूर्ण;

काष्ठा udma_tchan अणु
	व्योम __iomem *reg_rt;

	पूर्णांक id;
	काष्ठा k3_ring *t_ring; /* Transmit ring */
	काष्ठा k3_ring *tc_ring; /* Transmit Completion ring */
	पूर्णांक tflow_id; /* applicable only क्रम PKTDMA */

पूर्ण;

#घोषणा udma_bchan udma_tchan

काष्ठा udma_rflow अणु
	पूर्णांक id;
	काष्ठा k3_ring *fd_ring; /* Free Descriptor ring */
	काष्ठा k3_ring *r_ring; /* Receive ring */
पूर्ण;

काष्ठा udma_rchan अणु
	व्योम __iomem *reg_rt;

	पूर्णांक id;
पूर्ण;

काष्ठा udma_oes_offsets अणु
	/* K3 UDMA Output Event Offset */
	u32 udma_rchan;

	/* BCDMA Output Event Offsets */
	u32 bcdma_bchan_data;
	u32 bcdma_bchan_ring;
	u32 bcdma_tchan_data;
	u32 bcdma_tchan_ring;
	u32 bcdma_rchan_data;
	u32 bcdma_rchan_ring;

	/* PKTDMA Output Event Offsets */
	u32 pktdma_tchan_flow;
	u32 pktdma_rchan_flow;
पूर्ण;

#घोषणा UDMA_FLAG_PDMA_ACC32		BIT(0)
#घोषणा UDMA_FLAG_PDMA_BURST		BIT(1)
#घोषणा UDMA_FLAG_TDTYPE		BIT(2)
#घोषणा UDMA_FLAG_BURST_SIZE		BIT(3)
#घोषणा UDMA_FLAGS_J7_CLASS		(UDMA_FLAG_PDMA_ACC32 | \
					 UDMA_FLAG_PDMA_BURST | \
					 UDMA_FLAG_TDTYPE | \
					 UDMA_FLAG_BURST_SIZE)

काष्ठा udma_match_data अणु
	क्रमागत k3_dma_type type;
	u32 psil_base;
	bool enable_स_नकल_support;
	u32 flags;
	u32 अटलtr_z_mask;
	u8 burst_size[3];
पूर्ण;

काष्ठा udma_soc_data अणु
	काष्ठा udma_oes_offsets oes;
	u32 bcdma_trigger_event_offset;
पूर्ण;

काष्ठा udma_hwdesc अणु
	माप_प्रकार cppi5_desc_size;
	व्योम *cppi5_desc_vaddr;
	dma_addr_t cppi5_desc_paddr;

	/* TR descriptor पूर्णांकernal poपूर्णांकers */
	व्योम *tr_req_base;
	काष्ठा cppi5_tr_resp_t *tr_resp_base;
पूर्ण;

काष्ठा udma_rx_flush अणु
	काष्ठा udma_hwdesc hwdescs[2];

	माप_प्रकार buffer_size;
	व्योम *buffer_vaddr;
	dma_addr_t buffer_paddr;
पूर्ण;

काष्ठा udma_tpl अणु
	u8 levels;
	u32 start_idx[3];
पूर्ण;

काष्ठा udma_dev अणु
	काष्ठा dma_device ddev;
	काष्ठा device *dev;
	व्योम __iomem *mmrs[MMR_LAST];
	स्थिर काष्ठा udma_match_data *match_data;
	स्थिर काष्ठा udma_soc_data *soc_data;

	काष्ठा udma_tpl bchan_tpl;
	काष्ठा udma_tpl tchan_tpl;
	काष्ठा udma_tpl rchan_tpl;

	माप_प्रकार desc_align; /* alignment to use क्रम descriptors */

	काष्ठा udma_tisci_rm tisci_rm;

	काष्ठा k3_ringacc *ringacc;

	काष्ठा work_काष्ठा purge_work;
	काष्ठा list_head desc_to_purge;
	spinlock_t lock;

	काष्ठा udma_rx_flush rx_flush;

	पूर्णांक bchan_cnt;
	पूर्णांक tchan_cnt;
	पूर्णांक echan_cnt;
	पूर्णांक rchan_cnt;
	पूर्णांक rflow_cnt;
	पूर्णांक tflow_cnt;
	अचिन्हित दीर्घ *bchan_map;
	अचिन्हित दीर्घ *tchan_map;
	अचिन्हित दीर्घ *rchan_map;
	अचिन्हित दीर्घ *rflow_gp_map;
	अचिन्हित दीर्घ *rflow_gp_map_allocated;
	अचिन्हित दीर्घ *rflow_in_use;
	अचिन्हित दीर्घ *tflow_map;

	काष्ठा udma_bchan *bchans;
	काष्ठा udma_tchan *tchans;
	काष्ठा udma_rchan *rchans;
	काष्ठा udma_rflow *rflows;

	काष्ठा udma_chan *channels;
	u32 psil_base;
	u32 atype;
	u32 asel;
पूर्ण;

काष्ठा udma_desc अणु
	काष्ठा virt_dma_desc vd;

	bool terminated;

	क्रमागत dma_transfer_direction dir;

	काष्ठा udma_अटल_tr अटल_tr;
	u32 residue;

	अचिन्हित पूर्णांक sglen;
	अचिन्हित पूर्णांक desc_idx; /* Only used क्रम cyclic in packet mode */
	अचिन्हित पूर्णांक tr_idx;

	u32 metadata_size;
	व्योम *metadata; /* poपूर्णांकer to provided metadata buffer (EPIP, PSdata) */

	अचिन्हित पूर्णांक hwdesc_count;
	काष्ठा udma_hwdesc hwdesc[];
पूर्ण;

क्रमागत udma_chan_state अणु
	UDMA_CHAN_IS_IDLE = 0, /* not active, no tearकरोwn is in progress */
	UDMA_CHAN_IS_ACTIVE, /* Normal operation */
	UDMA_CHAN_IS_TERMINATING, /* channel is being terminated */
पूर्ण;

काष्ठा udma_tx_drain अणु
	काष्ठा delayed_work work;
	kसमय_प्रकार tstamp;
	u32 residue;
पूर्ण;

काष्ठा udma_chan_config अणु
	bool pkt_mode; /* TR or packet */
	bool needs_epib; /* EPIB is needed क्रम the communication or not */
	u32 psd_size; /* size of Protocol Specअगरic Data */
	u32 metadata_size; /* (needs_epib ? 16:0) + psd_size */
	u32 hdesc_size; /* Size of a packet descriptor in packet mode */
	bool notdpkt; /* Suppress sending TDC packet */
	पूर्णांक remote_thपढ़ो_id;
	u32 atype;
	u32 asel;
	u32 src_thपढ़ो;
	u32 dst_thपढ़ो;
	क्रमागत psil_endpoपूर्णांक_type ep_type;
	bool enable_acc32;
	bool enable_burst;
	क्रमागत udma_tp_level channel_tpl; /* Channel Throughput Level */

	u32 tr_trigger_type;

	/* PKDMA mapped channel */
	पूर्णांक mapped_channel_id;
	/* PKTDMA शेष tflow or rflow क्रम mapped channel */
	पूर्णांक शेष_flow_id;

	क्रमागत dma_transfer_direction dir;
पूर्ण;

काष्ठा udma_chan अणु
	काष्ठा virt_dma_chan vc;
	काष्ठा dma_slave_config	cfg;
	काष्ठा udma_dev *ud;
	काष्ठा device *dma_dev;
	काष्ठा udma_desc *desc;
	काष्ठा udma_desc *terminated_desc;
	काष्ठा udma_अटल_tr अटल_tr;
	अक्षर *name;

	काष्ठा udma_bchan *bchan;
	काष्ठा udma_tchan *tchan;
	काष्ठा udma_rchan *rchan;
	काष्ठा udma_rflow *rflow;

	bool psil_paired;

	पूर्णांक irq_num_ring;
	पूर्णांक irq_num_udma;

	bool cyclic;
	bool छोड़ोd;

	क्रमागत udma_chan_state state;
	काष्ठा completion tearकरोwn_completed;

	काष्ठा udma_tx_drain tx_drain;

	u32 bcnt; /* number of bytes completed since the start of the channel */

	/* Channel configuration parameters */
	काष्ठा udma_chan_config config;

	/* dmapool क्रम packet mode descriptors */
	bool use_dma_pool;
	काष्ठा dma_pool *hdesc_pool;

	u32 id;
पूर्ण;

अटल अंतरभूत काष्ठा udma_dev *to_udma_dev(काष्ठा dma_device *d)
अणु
	वापस container_of(d, काष्ठा udma_dev, ddev);
पूर्ण

अटल अंतरभूत काष्ठा udma_chan *to_udma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा udma_chan, vc.chan);
पूर्ण

अटल अंतरभूत काष्ठा udma_desc *to_udma_desc(काष्ठा dma_async_tx_descriptor *t)
अणु
	वापस container_of(t, काष्ठा udma_desc, vd.tx);
पूर्ण

/* Generic रेजिस्टर access functions */
अटल अंतरभूत u32 udma_पढ़ो(व्योम __iomem *base, पूर्णांक reg)
अणु
	वापस पढ़ोl(base + reg);
पूर्ण

अटल अंतरभूत व्योम udma_ग_लिखो(व्योम __iomem *base, पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, base + reg);
पूर्ण

अटल अंतरभूत व्योम udma_update_bits(व्योम __iomem *base, पूर्णांक reg,
				    u32 mask, u32 val)
अणु
	u32 पंचांगp, orig;

	orig = पढ़ोl(base + reg);
	पंचांगp = orig & ~mask;
	पंचांगp |= (val & mask);

	अगर (पंचांगp != orig)
		ग_लिखोl(पंचांगp, base + reg);
पूर्ण

/* TCHANRT */
अटल अंतरभूत u32 udma_tchanrt_पढ़ो(काष्ठा udma_chan *uc, पूर्णांक reg)
अणु
	अगर (!uc->tchan)
		वापस 0;
	वापस udma_पढ़ो(uc->tchan->reg_rt, reg);
पूर्ण

अटल अंतरभूत व्योम udma_tchanrt_ग_लिखो(काष्ठा udma_chan *uc, पूर्णांक reg, u32 val)
अणु
	अगर (!uc->tchan)
		वापस;
	udma_ग_लिखो(uc->tchan->reg_rt, reg, val);
पूर्ण

अटल अंतरभूत व्योम udma_tchanrt_update_bits(काष्ठा udma_chan *uc, पूर्णांक reg,
					    u32 mask, u32 val)
अणु
	अगर (!uc->tchan)
		वापस;
	udma_update_bits(uc->tchan->reg_rt, reg, mask, val);
पूर्ण

/* RCHANRT */
अटल अंतरभूत u32 udma_rchanrt_पढ़ो(काष्ठा udma_chan *uc, पूर्णांक reg)
अणु
	अगर (!uc->rchan)
		वापस 0;
	वापस udma_पढ़ो(uc->rchan->reg_rt, reg);
पूर्ण

अटल अंतरभूत व्योम udma_rchanrt_ग_लिखो(काष्ठा udma_chan *uc, पूर्णांक reg, u32 val)
अणु
	अगर (!uc->rchan)
		वापस;
	udma_ग_लिखो(uc->rchan->reg_rt, reg, val);
पूर्ण

अटल अंतरभूत व्योम udma_rchanrt_update_bits(काष्ठा udma_chan *uc, पूर्णांक reg,
					    u32 mask, u32 val)
अणु
	अगर (!uc->rchan)
		वापस;
	udma_update_bits(uc->rchan->reg_rt, reg, mask, val);
पूर्ण

अटल पूर्णांक navss_psil_pair(काष्ठा udma_dev *ud, u32 src_thपढ़ो, u32 dst_thपढ़ो)
अणु
	काष्ठा udma_tisci_rm *tisci_rm = &ud->tisci_rm;

	dst_thपढ़ो |= K3_PSIL_DST_THREAD_ID_OFFSET;
	वापस tisci_rm->tisci_psil_ops->pair(tisci_rm->tisci,
					      tisci_rm->tisci_navss_dev_id,
					      src_thपढ़ो, dst_thपढ़ो);
पूर्ण

अटल पूर्णांक navss_psil_unpair(काष्ठा udma_dev *ud, u32 src_thपढ़ो,
			     u32 dst_thपढ़ो)
अणु
	काष्ठा udma_tisci_rm *tisci_rm = &ud->tisci_rm;

	dst_thपढ़ो |= K3_PSIL_DST_THREAD_ID_OFFSET;
	वापस tisci_rm->tisci_psil_ops->unpair(tisci_rm->tisci,
						tisci_rm->tisci_navss_dev_id,
						src_thपढ़ो, dst_thपढ़ो);
पूर्ण

अटल व्योम k3_configure_chan_coherency(काष्ठा dma_chan *chan, u32 asel)
अणु
	काष्ठा device *chan_dev = &chan->dev->device;

	अगर (asel == 0) अणु
		/* No special handling क्रम the channel */
		chan->dev->chan_dma_dev = false;

		chan_dev->dma_coherent = false;
		chan_dev->dma_parms = शून्य;
	पूर्ण अन्यथा अगर (asel == 14 || asel == 15) अणु
		chan->dev->chan_dma_dev = true;

		chan_dev->dma_coherent = true;
		dma_coerce_mask_and_coherent(chan_dev, DMA_BIT_MASK(48));
		chan_dev->dma_parms = chan_dev->parent->dma_parms;
	पूर्ण अन्यथा अणु
		dev_warn(chan->device->dev, "Invalid ASEL value: %u\n", asel);

		chan_dev->dma_coherent = false;
		chan_dev->dma_parms = शून्य;
	पूर्ण
पूर्ण

अटल u8 udma_get_chan_tpl_index(काष्ठा udma_tpl *tpl_map, पूर्णांक chan_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tpl_map->levels; i++) अणु
		अगर (chan_id >= tpl_map->start_idx[i])
			वापस i;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम udma_reset_uchan(काष्ठा udma_chan *uc)
अणु
	स_रखो(&uc->config, 0, माप(uc->config));
	uc->config.remote_thपढ़ो_id = -1;
	uc->config.mapped_channel_id = -1;
	uc->config.शेष_flow_id = -1;
	uc->state = UDMA_CHAN_IS_IDLE;
पूर्ण

अटल व्योम udma_dump_chan_stdata(काष्ठा udma_chan *uc)
अणु
	काष्ठा device *dev = uc->ud->dev;
	u32 offset;
	पूर्णांक i;

	अगर (uc->config.dir == DMA_MEM_TO_DEV || uc->config.dir == DMA_MEM_TO_MEM) अणु
		dev_dbg(dev, "TCHAN State data:\n");
		क्रम (i = 0; i < 32; i++) अणु
			offset = UDMA_CHAN_RT_STDATA_REG + i * 4;
			dev_dbg(dev, "TRT_STDATA[%02d]: 0x%08x\n", i,
				udma_tchanrt_पढ़ो(uc, offset));
		पूर्ण
	पूर्ण

	अगर (uc->config.dir == DMA_DEV_TO_MEM || uc->config.dir == DMA_MEM_TO_MEM) अणु
		dev_dbg(dev, "RCHAN State data:\n");
		क्रम (i = 0; i < 32; i++) अणु
			offset = UDMA_CHAN_RT_STDATA_REG + i * 4;
			dev_dbg(dev, "RRT_STDATA[%02d]: 0x%08x\n", i,
				udma_rchanrt_पढ़ो(uc, offset));
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत dma_addr_t udma_curr_cppi5_desc_paddr(काष्ठा udma_desc *d,
						    पूर्णांक idx)
अणु
	वापस d->hwdesc[idx].cppi5_desc_paddr;
पूर्ण

अटल अंतरभूत व्योम *udma_curr_cppi5_desc_vaddr(काष्ठा udma_desc *d, पूर्णांक idx)
अणु
	वापस d->hwdesc[idx].cppi5_desc_vaddr;
पूर्ण

अटल काष्ठा udma_desc *udma_udma_desc_from_paddr(काष्ठा udma_chan *uc,
						   dma_addr_t paddr)
अणु
	काष्ठा udma_desc *d = uc->terminated_desc;

	अगर (d) अणु
		dma_addr_t desc_paddr = udma_curr_cppi5_desc_paddr(d,
								   d->desc_idx);

		अगर (desc_paddr != paddr)
			d = शून्य;
	पूर्ण

	अगर (!d) अणु
		d = uc->desc;
		अगर (d) अणु
			dma_addr_t desc_paddr = udma_curr_cppi5_desc_paddr(d,
								d->desc_idx);

			अगर (desc_paddr != paddr)
				d = शून्य;
		पूर्ण
	पूर्ण

	वापस d;
पूर्ण

अटल व्योम udma_मुक्त_hwdesc(काष्ठा udma_chan *uc, काष्ठा udma_desc *d)
अणु
	अगर (uc->use_dma_pool) अणु
		पूर्णांक i;

		क्रम (i = 0; i < d->hwdesc_count; i++) अणु
			अगर (!d->hwdesc[i].cppi5_desc_vaddr)
				जारी;

			dma_pool_मुक्त(uc->hdesc_pool,
				      d->hwdesc[i].cppi5_desc_vaddr,
				      d->hwdesc[i].cppi5_desc_paddr);

			d->hwdesc[i].cppi5_desc_vaddr = शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (d->hwdesc[0].cppi5_desc_vaddr) अणु
		dma_मुक्त_coherent(uc->dma_dev, d->hwdesc[0].cppi5_desc_size,
				  d->hwdesc[0].cppi5_desc_vaddr,
				  d->hwdesc[0].cppi5_desc_paddr);

		d->hwdesc[0].cppi5_desc_vaddr = शून्य;
	पूर्ण
पूर्ण

अटल व्योम udma_purge_desc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा udma_dev *ud = container_of(work, typeof(*ud), purge_work);
	काष्ठा virt_dma_desc *vd, *_vd;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&ud->lock, flags);
	list_splice_tail_init(&ud->desc_to_purge, &head);
	spin_unlock_irqrestore(&ud->lock, flags);

	list_क्रम_each_entry_safe(vd, _vd, &head, node) अणु
		काष्ठा udma_chan *uc = to_udma_chan(vd->tx.chan);
		काष्ठा udma_desc *d = to_udma_desc(&vd->tx);

		udma_मुक्त_hwdesc(uc, d);
		list_del(&vd->node);
		kमुक्त(d);
	पूर्ण

	/* If more to purge, schedule the work again */
	अगर (!list_empty(&ud->desc_to_purge))
		schedule_work(&ud->purge_work);
पूर्ण

अटल व्योम udma_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा udma_dev *ud = to_udma_dev(vd->tx.chan->device);
	काष्ठा udma_chan *uc = to_udma_chan(vd->tx.chan);
	काष्ठा udma_desc *d = to_udma_desc(&vd->tx);
	अचिन्हित दीर्घ flags;

	अगर (uc->terminated_desc == d)
		uc->terminated_desc = शून्य;

	अगर (uc->use_dma_pool) अणु
		udma_मुक्त_hwdesc(uc, d);
		kमुक्त(d);
		वापस;
	पूर्ण

	spin_lock_irqsave(&ud->lock, flags);
	list_add_tail(&vd->node, &ud->desc_to_purge);
	spin_unlock_irqrestore(&ud->lock, flags);

	schedule_work(&ud->purge_work);
पूर्ण

अटल bool udma_is_chan_running(काष्ठा udma_chan *uc)
अणु
	u32 trt_ctl = 0;
	u32 rrt_ctl = 0;

	अगर (uc->tchan)
		trt_ctl = udma_tchanrt_पढ़ो(uc, UDMA_CHAN_RT_CTL_REG);
	अगर (uc->rchan)
		rrt_ctl = udma_rchanrt_पढ़ो(uc, UDMA_CHAN_RT_CTL_REG);

	अगर (trt_ctl & UDMA_CHAN_RT_CTL_EN || rrt_ctl & UDMA_CHAN_RT_CTL_EN)
		वापस true;

	वापस false;
पूर्ण

अटल bool udma_is_chan_छोड़ोd(काष्ठा udma_chan *uc)
अणु
	u32 val, छोड़ो_mask;

	चयन (uc->config.dir) अणु
	हाल DMA_DEV_TO_MEM:
		val = udma_rchanrt_पढ़ो(uc, UDMA_CHAN_RT_PEER_RT_EN_REG);
		छोड़ो_mask = UDMA_PEER_RT_EN_PAUSE;
		अवरोध;
	हाल DMA_MEM_TO_DEV:
		val = udma_tchanrt_पढ़ो(uc, UDMA_CHAN_RT_PEER_RT_EN_REG);
		छोड़ो_mask = UDMA_PEER_RT_EN_PAUSE;
		अवरोध;
	हाल DMA_MEM_TO_MEM:
		val = udma_tchanrt_पढ़ो(uc, UDMA_CHAN_RT_CTL_REG);
		छोड़ो_mask = UDMA_CHAN_RT_CTL_PAUSE;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	अगर (val & छोड़ो_mask)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत dma_addr_t udma_get_rx_flush_hwdesc_paddr(काष्ठा udma_chan *uc)
अणु
	वापस uc->ud->rx_flush.hwdescs[uc->config.pkt_mode].cppi5_desc_paddr;
पूर्ण

अटल पूर्णांक udma_push_to_ring(काष्ठा udma_chan *uc, पूर्णांक idx)
अणु
	काष्ठा udma_desc *d = uc->desc;
	काष्ठा k3_ring *ring = शून्य;
	dma_addr_t paddr;

	चयन (uc->config.dir) अणु
	हाल DMA_DEV_TO_MEM:
		ring = uc->rflow->fd_ring;
		अवरोध;
	हाल DMA_MEM_TO_DEV:
	हाल DMA_MEM_TO_MEM:
		ring = uc->tchan->t_ring;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* RX flush packet: idx == -1 is only passed in हाल of DEV_TO_MEM */
	अगर (idx == -1) अणु
		paddr = udma_get_rx_flush_hwdesc_paddr(uc);
	पूर्ण अन्यथा अणु
		paddr = udma_curr_cppi5_desc_paddr(d, idx);

		wmb(); /* Ensure that ग_लिखोs are not moved over this poपूर्णांक */
	पूर्ण

	वापस k3_ringacc_ring_push(ring, &paddr);
पूर्ण

अटल bool udma_desc_is_rx_flush(काष्ठा udma_chan *uc, dma_addr_t addr)
अणु
	अगर (uc->config.dir != DMA_DEV_TO_MEM)
		वापस false;

	अगर (addr == udma_get_rx_flush_hwdesc_paddr(uc))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक udma_pop_from_ring(काष्ठा udma_chan *uc, dma_addr_t *addr)
अणु
	काष्ठा k3_ring *ring = शून्य;
	पूर्णांक ret;

	चयन (uc->config.dir) अणु
	हाल DMA_DEV_TO_MEM:
		ring = uc->rflow->r_ring;
		अवरोध;
	हाल DMA_MEM_TO_DEV:
	हाल DMA_MEM_TO_MEM:
		ring = uc->tchan->tc_ring;
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	ret = k3_ringacc_ring_pop(ring, addr);
	अगर (ret)
		वापस ret;

	rmb(); /* Ensure that पढ़ोs are not moved beक्रमe this poपूर्णांक */

	/* Tearकरोwn completion */
	अगर (cppi5_desc_is_tdcm(*addr))
		वापस 0;

	/* Check क्रम flush descriptor */
	अगर (udma_desc_is_rx_flush(uc, *addr))
		वापस -ENOENT;

	वापस 0;
पूर्ण

अटल व्योम udma_reset_rings(काष्ठा udma_chan *uc)
अणु
	काष्ठा k3_ring *ring1 = शून्य;
	काष्ठा k3_ring *ring2 = शून्य;

	चयन (uc->config.dir) अणु
	हाल DMA_DEV_TO_MEM:
		अगर (uc->rchan) अणु
			ring1 = uc->rflow->fd_ring;
			ring2 = uc->rflow->r_ring;
		पूर्ण
		अवरोध;
	हाल DMA_MEM_TO_DEV:
	हाल DMA_MEM_TO_MEM:
		अगर (uc->tchan) अणु
			ring1 = uc->tchan->t_ring;
			ring2 = uc->tchan->tc_ring;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ring1)
		k3_ringacc_ring_reset_dma(ring1,
					  k3_ringacc_ring_get_occ(ring1));
	अगर (ring2)
		k3_ringacc_ring_reset(ring2);

	/* make sure we are not leaking memory by stalled descriptor */
	अगर (uc->terminated_desc) अणु
		udma_desc_मुक्त(&uc->terminated_desc->vd);
		uc->terminated_desc = शून्य;
	पूर्ण
पूर्ण

अटल व्योम udma_reset_counters(काष्ठा udma_chan *uc)
अणु
	u32 val;

	अगर (uc->tchan) अणु
		val = udma_tchanrt_पढ़ो(uc, UDMA_CHAN_RT_BCNT_REG);
		udma_tchanrt_ग_लिखो(uc, UDMA_CHAN_RT_BCNT_REG, val);

		val = udma_tchanrt_पढ़ो(uc, UDMA_CHAN_RT_SBCNT_REG);
		udma_tchanrt_ग_लिखो(uc, UDMA_CHAN_RT_SBCNT_REG, val);

		val = udma_tchanrt_पढ़ो(uc, UDMA_CHAN_RT_PCNT_REG);
		udma_tchanrt_ग_लिखो(uc, UDMA_CHAN_RT_PCNT_REG, val);

		अगर (!uc->bchan) अणु
			val = udma_tchanrt_पढ़ो(uc, UDMA_CHAN_RT_PEER_BCNT_REG);
			udma_tchanrt_ग_लिखो(uc, UDMA_CHAN_RT_PEER_BCNT_REG, val);
		पूर्ण
	पूर्ण

	अगर (uc->rchan) अणु
		val = udma_rchanrt_पढ़ो(uc, UDMA_CHAN_RT_BCNT_REG);
		udma_rchanrt_ग_लिखो(uc, UDMA_CHAN_RT_BCNT_REG, val);

		val = udma_rchanrt_पढ़ो(uc, UDMA_CHAN_RT_SBCNT_REG);
		udma_rchanrt_ग_लिखो(uc, UDMA_CHAN_RT_SBCNT_REG, val);

		val = udma_rchanrt_पढ़ो(uc, UDMA_CHAN_RT_PCNT_REG);
		udma_rchanrt_ग_लिखो(uc, UDMA_CHAN_RT_PCNT_REG, val);

		val = udma_rchanrt_पढ़ो(uc, UDMA_CHAN_RT_PEER_BCNT_REG);
		udma_rchanrt_ग_लिखो(uc, UDMA_CHAN_RT_PEER_BCNT_REG, val);
	पूर्ण

	uc->bcnt = 0;
पूर्ण

अटल पूर्णांक udma_reset_chan(काष्ठा udma_chan *uc, bool hard)
अणु
	चयन (uc->config.dir) अणु
	हाल DMA_DEV_TO_MEM:
		udma_rchanrt_ग_लिखो(uc, UDMA_CHAN_RT_PEER_RT_EN_REG, 0);
		udma_rchanrt_ग_लिखो(uc, UDMA_CHAN_RT_CTL_REG, 0);
		अवरोध;
	हाल DMA_MEM_TO_DEV:
		udma_tchanrt_ग_लिखो(uc, UDMA_CHAN_RT_CTL_REG, 0);
		udma_tchanrt_ग_लिखो(uc, UDMA_CHAN_RT_PEER_RT_EN_REG, 0);
		अवरोध;
	हाल DMA_MEM_TO_MEM:
		udma_rchanrt_ग_लिखो(uc, UDMA_CHAN_RT_CTL_REG, 0);
		udma_tchanrt_ग_लिखो(uc, UDMA_CHAN_RT_CTL_REG, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Reset all counters */
	udma_reset_counters(uc);

	/* Hard reset: re-initialize the channel to reset */
	अगर (hard) अणु
		काष्ठा udma_chan_config ucc_backup;
		पूर्णांक ret;

		स_नकल(&ucc_backup, &uc->config, माप(uc->config));
		uc->ud->ddev.device_मुक्त_chan_resources(&uc->vc.chan);

		/* restore the channel configuration */
		स_नकल(&uc->config, &ucc_backup, माप(uc->config));
		ret = uc->ud->ddev.device_alloc_chan_resources(&uc->vc.chan);
		अगर (ret)
			वापस ret;

		/*
		 * Setting क्रमced tearकरोwn after क्रमced reset helps recovering
		 * the rchan.
		 */
		अगर (uc->config.dir == DMA_DEV_TO_MEM)
			udma_rchanrt_ग_लिखो(uc, UDMA_CHAN_RT_CTL_REG,
					   UDMA_CHAN_RT_CTL_EN |
					   UDMA_CHAN_RT_CTL_TDOWN |
					   UDMA_CHAN_RT_CTL_FTDOWN);
	पूर्ण
	uc->state = UDMA_CHAN_IS_IDLE;

	वापस 0;
पूर्ण

अटल व्योम udma_start_desc(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_chan_config *ucc = &uc->config;

	अगर (uc->ud->match_data->type == DMA_TYPE_UDMA && ucc->pkt_mode &&
	    (uc->cyclic || ucc->dir == DMA_DEV_TO_MEM)) अणु
		पूर्णांक i;

		/*
		 * UDMA only: Push all descriptors to ring क्रम packet mode
		 * cyclic or RX
		 * PKTDMA supports pre-linked descriptor and cyclic is not
		 * supported
		 */
		क्रम (i = 0; i < uc->desc->sglen; i++)
			udma_push_to_ring(uc, i);
	पूर्ण अन्यथा अणु
		udma_push_to_ring(uc, 0);
	पूर्ण
पूर्ण

अटल bool udma_chan_needs_reconfiguration(काष्ठा udma_chan *uc)
अणु
	/* Only PDMAs have अटलTR */
	अगर (uc->config.ep_type == PSIL_EP_NATIVE)
		वापस false;

	/* Check अगर the अटलTR configuration has changed क्रम TX */
	अगर (स_भेद(&uc->अटल_tr, &uc->desc->अटल_tr, माप(uc->अटल_tr)))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक udma_start(काष्ठा udma_chan *uc)
अणु
	काष्ठा virt_dma_desc *vd = vchan_next_desc(&uc->vc);

	अगर (!vd) अणु
		uc->desc = शून्य;
		वापस -ENOENT;
	पूर्ण

	list_del(&vd->node);

	uc->desc = to_udma_desc(&vd->tx);

	/* Channel is alपढ़ोy running and करोes not need reconfiguration */
	अगर (udma_is_chan_running(uc) && !udma_chan_needs_reconfiguration(uc)) अणु
		udma_start_desc(uc);
		जाओ out;
	पूर्ण

	/* Make sure that we clear the tearकरोwn bit, अगर it is set */
	udma_reset_chan(uc, false);

	/* Push descriptors beक्रमe we start the channel */
	udma_start_desc(uc);

	चयन (uc->desc->dir) अणु
	हाल DMA_DEV_TO_MEM:
		/* Config remote TR */
		अगर (uc->config.ep_type == PSIL_EP_PDMA_XY) अणु
			u32 val = PDMA_STATIC_TR_Y(uc->desc->अटल_tr.elcnt) |
				  PDMA_STATIC_TR_X(uc->desc->अटल_tr.elsize);
			स्थिर काष्ठा udma_match_data *match_data =
							uc->ud->match_data;

			अगर (uc->config.enable_acc32)
				val |= PDMA_STATIC_TR_XY_ACC32;
			अगर (uc->config.enable_burst)
				val |= PDMA_STATIC_TR_XY_BURST;

			udma_rchanrt_ग_लिखो(uc,
					   UDMA_CHAN_RT_PEER_STATIC_TR_XY_REG,
					   val);

			udma_rchanrt_ग_लिखो(uc,
				UDMA_CHAN_RT_PEER_STATIC_TR_Z_REG,
				PDMA_STATIC_TR_Z(uc->desc->अटल_tr.bstcnt,
						 match_data->अटलtr_z_mask));

			/* save the current अटलTR configuration */
			स_नकल(&uc->अटल_tr, &uc->desc->अटल_tr,
			       माप(uc->अटल_tr));
		पूर्ण

		udma_rchanrt_ग_लिखो(uc, UDMA_CHAN_RT_CTL_REG,
				   UDMA_CHAN_RT_CTL_EN);

		/* Enable remote */
		udma_rchanrt_ग_लिखो(uc, UDMA_CHAN_RT_PEER_RT_EN_REG,
				   UDMA_PEER_RT_EN_ENABLE);

		अवरोध;
	हाल DMA_MEM_TO_DEV:
		/* Config remote TR */
		अगर (uc->config.ep_type == PSIL_EP_PDMA_XY) अणु
			u32 val = PDMA_STATIC_TR_Y(uc->desc->अटल_tr.elcnt) |
				  PDMA_STATIC_TR_X(uc->desc->अटल_tr.elsize);

			अगर (uc->config.enable_acc32)
				val |= PDMA_STATIC_TR_XY_ACC32;
			अगर (uc->config.enable_burst)
				val |= PDMA_STATIC_TR_XY_BURST;

			udma_tchanrt_ग_लिखो(uc,
					   UDMA_CHAN_RT_PEER_STATIC_TR_XY_REG,
					   val);

			/* save the current अटलTR configuration */
			स_नकल(&uc->अटल_tr, &uc->desc->अटल_tr,
			       माप(uc->अटल_tr));
		पूर्ण

		/* Enable remote */
		udma_tchanrt_ग_लिखो(uc, UDMA_CHAN_RT_PEER_RT_EN_REG,
				   UDMA_PEER_RT_EN_ENABLE);

		udma_tchanrt_ग_लिखो(uc, UDMA_CHAN_RT_CTL_REG,
				   UDMA_CHAN_RT_CTL_EN);

		अवरोध;
	हाल DMA_MEM_TO_MEM:
		udma_rchanrt_ग_लिखो(uc, UDMA_CHAN_RT_CTL_REG,
				   UDMA_CHAN_RT_CTL_EN);
		udma_tchanrt_ग_लिखो(uc, UDMA_CHAN_RT_CTL_REG,
				   UDMA_CHAN_RT_CTL_EN);

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	uc->state = UDMA_CHAN_IS_ACTIVE;
out:

	वापस 0;
पूर्ण

अटल पूर्णांक udma_stop(काष्ठा udma_chan *uc)
अणु
	क्रमागत udma_chan_state old_state = uc->state;

	uc->state = UDMA_CHAN_IS_TERMINATING;
	reinit_completion(&uc->tearकरोwn_completed);

	चयन (uc->config.dir) अणु
	हाल DMA_DEV_TO_MEM:
		अगर (!uc->cyclic && !uc->desc)
			udma_push_to_ring(uc, -1);

		udma_rchanrt_ग_लिखो(uc, UDMA_CHAN_RT_PEER_RT_EN_REG,
				   UDMA_PEER_RT_EN_ENABLE |
				   UDMA_PEER_RT_EN_TEARDOWN);
		अवरोध;
	हाल DMA_MEM_TO_DEV:
		udma_tchanrt_ग_लिखो(uc, UDMA_CHAN_RT_PEER_RT_EN_REG,
				   UDMA_PEER_RT_EN_ENABLE |
				   UDMA_PEER_RT_EN_FLUSH);
		udma_tchanrt_ग_लिखो(uc, UDMA_CHAN_RT_CTL_REG,
				   UDMA_CHAN_RT_CTL_EN |
				   UDMA_CHAN_RT_CTL_TDOWN);
		अवरोध;
	हाल DMA_MEM_TO_MEM:
		udma_tchanrt_ग_लिखो(uc, UDMA_CHAN_RT_CTL_REG,
				   UDMA_CHAN_RT_CTL_EN |
				   UDMA_CHAN_RT_CTL_TDOWN);
		अवरोध;
	शेष:
		uc->state = old_state;
		complete_all(&uc->tearकरोwn_completed);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम udma_cyclic_packet_elapsed(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_desc *d = uc->desc;
	काष्ठा cppi5_host_desc_t *h_desc;

	h_desc = d->hwdesc[d->desc_idx].cppi5_desc_vaddr;
	cppi5_hdesc_reset_to_original(h_desc);
	udma_push_to_ring(uc, d->desc_idx);
	d->desc_idx = (d->desc_idx + 1) % d->sglen;
पूर्ण

अटल अंतरभूत व्योम udma_fetch_epib(काष्ठा udma_chan *uc, काष्ठा udma_desc *d)
अणु
	काष्ठा cppi5_host_desc_t *h_desc = d->hwdesc[0].cppi5_desc_vaddr;

	स_नकल(d->metadata, h_desc->epib, d->metadata_size);
पूर्ण

अटल bool udma_is_desc_really_करोne(काष्ठा udma_chan *uc, काष्ठा udma_desc *d)
अणु
	u32 peer_bcnt, bcnt;

	/* Only TX towards PDMA is affected */
	अगर (uc->config.ep_type == PSIL_EP_NATIVE ||
	    uc->config.dir != DMA_MEM_TO_DEV)
		वापस true;

	peer_bcnt = udma_tchanrt_पढ़ो(uc, UDMA_CHAN_RT_PEER_BCNT_REG);
	bcnt = udma_tchanrt_पढ़ो(uc, UDMA_CHAN_RT_BCNT_REG);

	/* Transfer is incomplete, store current residue and समय stamp */
	अगर (peer_bcnt < bcnt) अणु
		uc->tx_drain.residue = bcnt - peer_bcnt;
		uc->tx_drain.tstamp = kसमय_get();
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम udma_check_tx_completion(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा udma_chan *uc = container_of(work, typeof(*uc),
					    tx_drain.work.work);
	bool desc_करोne = true;
	u32 residue_dअगरf;
	kसमय_प्रकार समय_dअगरf;
	अचिन्हित दीर्घ delay;

	जबतक (1) अणु
		अगर (uc->desc) अणु
			/* Get previous residue and समय stamp */
			residue_dअगरf = uc->tx_drain.residue;
			समय_dअगरf = uc->tx_drain.tstamp;
			/*
			 * Get current residue and समय stamp or see अगर
			 * transfer is complete
			 */
			desc_करोne = udma_is_desc_really_करोne(uc, uc->desc);
		पूर्ण

		अगर (!desc_करोne) अणु
			/*
			 * Find the समय delta and residue delta w.r.t
			 * previous poll
			 */
			समय_dअगरf = kसमय_sub(uc->tx_drain.tstamp,
					      समय_dअगरf) + 1;
			residue_dअगरf -= uc->tx_drain.residue;
			अगर (residue_dअगरf) अणु
				/*
				 * Try to guess when we should check
				 * next समय by calculating rate at
				 * which data is being drained at the
				 * peer device
				 */
				delay = (समय_dअगरf / residue_dअगरf) *
					uc->tx_drain.residue;
			पूर्ण अन्यथा अणु
				/* No progress, check again in 1 second  */
				schedule_delayed_work(&uc->tx_drain.work, HZ);
				अवरोध;
			पूर्ण

			usleep_range(kसमय_प्रकारo_us(delay),
				     kसमय_प्रकारo_us(delay) + 10);
			जारी;
		पूर्ण

		अगर (uc->desc) अणु
			काष्ठा udma_desc *d = uc->desc;

			uc->bcnt += d->residue;
			udma_start(uc);
			vchan_cookie_complete(&d->vd);
			अवरोध;
		पूर्ण

		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t udma_ring_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा udma_chan *uc = data;
	काष्ठा udma_desc *d;
	dma_addr_t paddr = 0;

	अगर (udma_pop_from_ring(uc, &paddr) || !paddr)
		वापस IRQ_HANDLED;

	spin_lock(&uc->vc.lock);

	/* Tearकरोwn completion message */
	अगर (cppi5_desc_is_tdcm(paddr)) अणु
		complete_all(&uc->tearकरोwn_completed);

		अगर (uc->terminated_desc) अणु
			udma_desc_मुक्त(&uc->terminated_desc->vd);
			uc->terminated_desc = शून्य;
		पूर्ण

		अगर (!uc->desc)
			udma_start(uc);

		जाओ out;
	पूर्ण

	d = udma_udma_desc_from_paddr(uc, paddr);

	अगर (d) अणु
		dma_addr_t desc_paddr = udma_curr_cppi5_desc_paddr(d,
								   d->desc_idx);
		अगर (desc_paddr != paddr) अणु
			dev_err(uc->ud->dev, "not matching descriptors!\n");
			जाओ out;
		पूर्ण

		अगर (d == uc->desc) अणु
			/* active descriptor */
			अगर (uc->cyclic) अणु
				udma_cyclic_packet_elapsed(uc);
				vchan_cyclic_callback(&d->vd);
			पूर्ण अन्यथा अणु
				अगर (udma_is_desc_really_करोne(uc, d)) अणु
					uc->bcnt += d->residue;
					udma_start(uc);
					vchan_cookie_complete(&d->vd);
				पूर्ण अन्यथा अणु
					schedule_delayed_work(&uc->tx_drain.work,
							      0);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * terminated descriptor, mark the descriptor as
			 * completed to update the channel's cookie marker
			 */
			dma_cookie_complete(&d->vd.tx);
		पूर्ण
	पूर्ण
out:
	spin_unlock(&uc->vc.lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t udma_udma_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा udma_chan *uc = data;
	काष्ठा udma_desc *d;

	spin_lock(&uc->vc.lock);
	d = uc->desc;
	अगर (d) अणु
		d->tr_idx = (d->tr_idx + 1) % d->sglen;

		अगर (uc->cyclic) अणु
			vchan_cyclic_callback(&d->vd);
		पूर्ण अन्यथा अणु
			/* TODO: figure out the real amount of data */
			uc->bcnt += d->residue;
			udma_start(uc);
			vchan_cookie_complete(&d->vd);
		पूर्ण
	पूर्ण

	spin_unlock(&uc->vc.lock);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * __udma_alloc_gp_rflow_range - alloc range of GP RX flows
 * @ud: UDMA device
 * @from: Start the search from this flow id number
 * @cnt: Number of consecutive flow ids to allocate
 *
 * Allocate range of RX flow ids क्रम future use, those flows can be requested
 * only using explicit flow id number. अगर @from is set to -1 it will try to find
 * first मुक्त range. अगर @from is positive value it will क्रमce allocation only
 * of the specअगरied range of flows.
 *
 * Returns -ENOMEM अगर can't find मुक्त range.
 * -EEXIST अगर requested range is busy.
 * -EINVAL अगर wrong input values passed.
 * Returns flow id on success.
 */
अटल पूर्णांक __udma_alloc_gp_rflow_range(काष्ठा udma_dev *ud, पूर्णांक from, पूर्णांक cnt)
अणु
	पूर्णांक start, पंचांगp_from;
	DECLARE_BITMAP(पंचांगp, K3_UDMA_MAX_RFLOWS);

	पंचांगp_from = from;
	अगर (पंचांगp_from < 0)
		पंचांगp_from = ud->rchan_cnt;
	/* शेष flows can't be allocated and accessible only by id */
	अगर (पंचांगp_from < ud->rchan_cnt)
		वापस -EINVAL;

	अगर (पंचांगp_from + cnt > ud->rflow_cnt)
		वापस -EINVAL;

	biपंचांगap_or(पंचांगp, ud->rflow_gp_map, ud->rflow_gp_map_allocated,
		  ud->rflow_cnt);

	start = biपंचांगap_find_next_zero_area(पंचांगp,
					   ud->rflow_cnt,
					   पंचांगp_from, cnt, 0);
	अगर (start >= ud->rflow_cnt)
		वापस -ENOMEM;

	अगर (from >= 0 && start != from)
		वापस -EEXIST;

	biपंचांगap_set(ud->rflow_gp_map_allocated, start, cnt);
	वापस start;
पूर्ण

अटल पूर्णांक __udma_मुक्त_gp_rflow_range(काष्ठा udma_dev *ud, पूर्णांक from, पूर्णांक cnt)
अणु
	अगर (from < ud->rchan_cnt)
		वापस -EINVAL;
	अगर (from + cnt > ud->rflow_cnt)
		वापस -EINVAL;

	biपंचांगap_clear(ud->rflow_gp_map_allocated, from, cnt);
	वापस 0;
पूर्ण

अटल काष्ठा udma_rflow *__udma_get_rflow(काष्ठा udma_dev *ud, पूर्णांक id)
अणु
	/*
	 * Attempt to request rflow by ID can be made क्रम any rflow
	 * अगर not in use with assumption that caller knows what's करोing.
	 * TI-SCI FW will perक्रमm additional permission check ant way, it's
	 * safe
	 */

	अगर (id < 0 || id >= ud->rflow_cnt)
		वापस ERR_PTR(-ENOENT);

	अगर (test_bit(id, ud->rflow_in_use))
		वापस ERR_PTR(-ENOENT);

	अगर (ud->rflow_gp_map) अणु
		/* GP rflow has to be allocated first */
		अगर (!test_bit(id, ud->rflow_gp_map) &&
		    !test_bit(id, ud->rflow_gp_map_allocated))
			वापस ERR_PTR(-EINVAL);
	पूर्ण

	dev_dbg(ud->dev, "get rflow%d\n", id);
	set_bit(id, ud->rflow_in_use);
	वापस &ud->rflows[id];
पूर्ण

अटल व्योम __udma_put_rflow(काष्ठा udma_dev *ud, काष्ठा udma_rflow *rflow)
अणु
	अगर (!test_bit(rflow->id, ud->rflow_in_use)) अणु
		dev_err(ud->dev, "attempt to put unused rflow%d\n", rflow->id);
		वापस;
	पूर्ण

	dev_dbg(ud->dev, "put rflow%d\n", rflow->id);
	clear_bit(rflow->id, ud->rflow_in_use);
पूर्ण

#घोषणा UDMA_RESERVE_RESOURCE(res)					\
अटल काष्ठा udma_##res *__udma_reserve_##res(काष्ठा udma_dev *ud,	\
					       क्रमागत udma_tp_level tpl,	\
					       पूर्णांक id)			\
अणु									\
	अगर (id >= 0) अणु							\
		अगर (test_bit(id, ud->res##_map)) अणु			\
			dev_err(ud->dev, "res##%d is in use\n", id);	\
			वापस ERR_PTR(-ENOENT);			\
		पूर्ण							\
	पूर्ण अन्यथा अणु							\
		पूर्णांक start;						\
									\
		अगर (tpl >= ud->res##_tpl.levels)			\
			tpl = ud->res##_tpl.levels - 1;			\
									\
		start = ud->res##_tpl.start_idx[tpl];			\
									\
		id = find_next_zero_bit(ud->res##_map, ud->res##_cnt,	\
					start);				\
		अगर (id == ud->res##_cnt) अणु				\
			वापस ERR_PTR(-ENOENT);			\
		पूर्ण							\
	पूर्ण								\
									\
	set_bit(id, ud->res##_map);					\
	वापस &ud->res##s[id];						\
पूर्ण

UDMA_RESERVE_RESOURCE(bchan);
UDMA_RESERVE_RESOURCE(tchan);
UDMA_RESERVE_RESOURCE(rchan);

अटल पूर्णांक bcdma_get_bchan(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;
	क्रमागत udma_tp_level tpl;

	अगर (uc->bchan) अणु
		dev_dbg(ud->dev, "chan%d: already have bchan%d allocated\n",
			uc->id, uc->bchan->id);
		वापस 0;
	पूर्ण

	/*
	 * Use normal channels क्रम peripherals, and highest TPL channel क्रम
	 * mem2mem
	 */
	अगर (uc->config.tr_trigger_type)
		tpl = 0;
	अन्यथा
		tpl = ud->bchan_tpl.levels - 1;

	uc->bchan = __udma_reserve_bchan(ud, tpl, -1);
	अगर (IS_ERR(uc->bchan))
		वापस PTR_ERR(uc->bchan);

	uc->tchan = uc->bchan;

	वापस 0;
पूर्ण

अटल पूर्णांक udma_get_tchan(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;

	अगर (uc->tchan) अणु
		dev_dbg(ud->dev, "chan%d: already have tchan%d allocated\n",
			uc->id, uc->tchan->id);
		वापस 0;
	पूर्ण

	/*
	 * mapped_channel_id is -1 क्रम UDMA, BCDMA and PKTDMA unmapped channels.
	 * For PKTDMA mapped channels it is configured to a channel which must
	 * be used to service the peripheral.
	 */
	uc->tchan = __udma_reserve_tchan(ud, uc->config.channel_tpl,
					 uc->config.mapped_channel_id);
	अगर (IS_ERR(uc->tchan))
		वापस PTR_ERR(uc->tchan);

	अगर (ud->tflow_cnt) अणु
		पूर्णांक tflow_id;

		/* Only PKTDMA have support क्रम tx flows */
		अगर (uc->config.शेष_flow_id >= 0)
			tflow_id = uc->config.शेष_flow_id;
		अन्यथा
			tflow_id = uc->tchan->id;

		अगर (test_bit(tflow_id, ud->tflow_map)) अणु
			dev_err(ud->dev, "tflow%d is in use\n", tflow_id);
			clear_bit(uc->tchan->id, ud->tchan_map);
			uc->tchan = शून्य;
			वापस -ENOENT;
		पूर्ण

		uc->tchan->tflow_id = tflow_id;
		set_bit(tflow_id, ud->tflow_map);
	पूर्ण अन्यथा अणु
		uc->tchan->tflow_id = -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक udma_get_rchan(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;

	अगर (uc->rchan) अणु
		dev_dbg(ud->dev, "chan%d: already have rchan%d allocated\n",
			uc->id, uc->rchan->id);
		वापस 0;
	पूर्ण

	/*
	 * mapped_channel_id is -1 क्रम UDMA, BCDMA and PKTDMA unmapped channels.
	 * For PKTDMA mapped channels it is configured to a channel which must
	 * be used to service the peripheral.
	 */
	uc->rchan = __udma_reserve_rchan(ud, uc->config.channel_tpl,
					 uc->config.mapped_channel_id);

	वापस PTR_ERR_OR_ZERO(uc->rchan);
पूर्ण

अटल पूर्णांक udma_get_chan_pair(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;
	पूर्णांक chan_id, end;

	अगर ((uc->tchan && uc->rchan) && uc->tchan->id == uc->rchan->id) अणु
		dev_info(ud->dev, "chan%d: already have %d pair allocated\n",
			 uc->id, uc->tchan->id);
		वापस 0;
	पूर्ण

	अगर (uc->tchan) अणु
		dev_err(ud->dev, "chan%d: already have tchan%d allocated\n",
			uc->id, uc->tchan->id);
		वापस -EBUSY;
	पूर्ण अन्यथा अगर (uc->rchan) अणु
		dev_err(ud->dev, "chan%d: already have rchan%d allocated\n",
			uc->id, uc->rchan->id);
		वापस -EBUSY;
	पूर्ण

	/* Can be optimized, but let's have it like this क्रम now */
	end = min(ud->tchan_cnt, ud->rchan_cnt);
	/*
	 * Try to use the highest TPL channel pair क्रम MEM_TO_MEM channels
	 * Note: in UDMAP the channel TPL is symmetric between tchan and rchan
	 */
	chan_id = ud->tchan_tpl.start_idx[ud->tchan_tpl.levels - 1];
	क्रम (; chan_id < end; chan_id++) अणु
		अगर (!test_bit(chan_id, ud->tchan_map) &&
		    !test_bit(chan_id, ud->rchan_map))
			अवरोध;
	पूर्ण

	अगर (chan_id == end)
		वापस -ENOENT;

	set_bit(chan_id, ud->tchan_map);
	set_bit(chan_id, ud->rchan_map);
	uc->tchan = &ud->tchans[chan_id];
	uc->rchan = &ud->rchans[chan_id];

	/* UDMA करोes not use tx flows */
	uc->tchan->tflow_id = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक udma_get_rflow(काष्ठा udma_chan *uc, पूर्णांक flow_id)
अणु
	काष्ठा udma_dev *ud = uc->ud;

	अगर (!uc->rchan) अणु
		dev_err(ud->dev, "chan%d: does not have rchan??\n", uc->id);
		वापस -EINVAL;
	पूर्ण

	अगर (uc->rflow) अणु
		dev_dbg(ud->dev, "chan%d: already have rflow%d allocated\n",
			uc->id, uc->rflow->id);
		वापस 0;
	पूर्ण

	uc->rflow = __udma_get_rflow(ud, flow_id);

	वापस PTR_ERR_OR_ZERO(uc->rflow);
पूर्ण

अटल व्योम bcdma_put_bchan(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;

	अगर (uc->bchan) अणु
		dev_dbg(ud->dev, "chan%d: put bchan%d\n", uc->id,
			uc->bchan->id);
		clear_bit(uc->bchan->id, ud->bchan_map);
		uc->bchan = शून्य;
		uc->tchan = शून्य;
	पूर्ण
पूर्ण

अटल व्योम udma_put_rchan(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;

	अगर (uc->rchan) अणु
		dev_dbg(ud->dev, "chan%d: put rchan%d\n", uc->id,
			uc->rchan->id);
		clear_bit(uc->rchan->id, ud->rchan_map);
		uc->rchan = शून्य;
	पूर्ण
पूर्ण

अटल व्योम udma_put_tchan(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;

	अगर (uc->tchan) अणु
		dev_dbg(ud->dev, "chan%d: put tchan%d\n", uc->id,
			uc->tchan->id);
		clear_bit(uc->tchan->id, ud->tchan_map);

		अगर (uc->tchan->tflow_id >= 0)
			clear_bit(uc->tchan->tflow_id, ud->tflow_map);

		uc->tchan = शून्य;
	पूर्ण
पूर्ण

अटल व्योम udma_put_rflow(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;

	अगर (uc->rflow) अणु
		dev_dbg(ud->dev, "chan%d: put rflow%d\n", uc->id,
			uc->rflow->id);
		__udma_put_rflow(ud, uc->rflow);
		uc->rflow = शून्य;
	पूर्ण
पूर्ण

अटल व्योम bcdma_मुक्त_bchan_resources(काष्ठा udma_chan *uc)
अणु
	अगर (!uc->bchan)
		वापस;

	k3_ringacc_ring_मुक्त(uc->bchan->tc_ring);
	k3_ringacc_ring_मुक्त(uc->bchan->t_ring);
	uc->bchan->tc_ring = शून्य;
	uc->bchan->t_ring = शून्य;
	k3_configure_chan_coherency(&uc->vc.chan, 0);

	bcdma_put_bchan(uc);
पूर्ण

अटल पूर्णांक bcdma_alloc_bchan_resources(काष्ठा udma_chan *uc)
अणु
	काष्ठा k3_ring_cfg ring_cfg;
	काष्ठा udma_dev *ud = uc->ud;
	पूर्णांक ret;

	ret = bcdma_get_bchan(uc);
	अगर (ret)
		वापस ret;

	ret = k3_ringacc_request_rings_pair(ud->ringacc, uc->bchan->id, -1,
					    &uc->bchan->t_ring,
					    &uc->bchan->tc_ring);
	अगर (ret) अणु
		ret = -EBUSY;
		जाओ err_ring;
	पूर्ण

	स_रखो(&ring_cfg, 0, माप(ring_cfg));
	ring_cfg.size = K3_UDMA_DEFAULT_RING_SIZE;
	ring_cfg.elm_size = K3_RINGACC_RING_ELSIZE_8;
	ring_cfg.mode = K3_RINGACC_RING_MODE_RING;

	k3_configure_chan_coherency(&uc->vc.chan, ud->asel);
	ring_cfg.asel = ud->asel;
	ring_cfg.dma_dev = dmaengine_get_dma_device(&uc->vc.chan);

	ret = k3_ringacc_ring_cfg(uc->bchan->t_ring, &ring_cfg);
	अगर (ret)
		जाओ err_ringcfg;

	वापस 0;

err_ringcfg:
	k3_ringacc_ring_मुक्त(uc->bchan->tc_ring);
	uc->bchan->tc_ring = शून्य;
	k3_ringacc_ring_मुक्त(uc->bchan->t_ring);
	uc->bchan->t_ring = शून्य;
	k3_configure_chan_coherency(&uc->vc.chan, 0);
err_ring:
	bcdma_put_bchan(uc);

	वापस ret;
पूर्ण

अटल व्योम udma_मुक्त_tx_resources(काष्ठा udma_chan *uc)
अणु
	अगर (!uc->tchan)
		वापस;

	k3_ringacc_ring_मुक्त(uc->tchan->t_ring);
	k3_ringacc_ring_मुक्त(uc->tchan->tc_ring);
	uc->tchan->t_ring = शून्य;
	uc->tchan->tc_ring = शून्य;

	udma_put_tchan(uc);
पूर्ण

अटल पूर्णांक udma_alloc_tx_resources(काष्ठा udma_chan *uc)
अणु
	काष्ठा k3_ring_cfg ring_cfg;
	काष्ठा udma_dev *ud = uc->ud;
	काष्ठा udma_tchan *tchan;
	पूर्णांक ring_idx, ret;

	ret = udma_get_tchan(uc);
	अगर (ret)
		वापस ret;

	tchan = uc->tchan;
	अगर (tchan->tflow_id >= 0)
		ring_idx = tchan->tflow_id;
	अन्यथा
		ring_idx = ud->bchan_cnt + tchan->id;

	ret = k3_ringacc_request_rings_pair(ud->ringacc, ring_idx, -1,
					    &tchan->t_ring,
					    &tchan->tc_ring);
	अगर (ret) अणु
		ret = -EBUSY;
		जाओ err_ring;
	पूर्ण

	स_रखो(&ring_cfg, 0, माप(ring_cfg));
	ring_cfg.size = K3_UDMA_DEFAULT_RING_SIZE;
	ring_cfg.elm_size = K3_RINGACC_RING_ELSIZE_8;
	अगर (ud->match_data->type == DMA_TYPE_UDMA) अणु
		ring_cfg.mode = K3_RINGACC_RING_MODE_MESSAGE;
	पूर्ण अन्यथा अणु
		ring_cfg.mode = K3_RINGACC_RING_MODE_RING;

		k3_configure_chan_coherency(&uc->vc.chan, uc->config.asel);
		ring_cfg.asel = uc->config.asel;
		ring_cfg.dma_dev = dmaengine_get_dma_device(&uc->vc.chan);
	पूर्ण

	ret = k3_ringacc_ring_cfg(tchan->t_ring, &ring_cfg);
	ret |= k3_ringacc_ring_cfg(tchan->tc_ring, &ring_cfg);

	अगर (ret)
		जाओ err_ringcfg;

	वापस 0;

err_ringcfg:
	k3_ringacc_ring_मुक्त(uc->tchan->tc_ring);
	uc->tchan->tc_ring = शून्य;
	k3_ringacc_ring_मुक्त(uc->tchan->t_ring);
	uc->tchan->t_ring = शून्य;
err_ring:
	udma_put_tchan(uc);

	वापस ret;
पूर्ण

अटल व्योम udma_मुक्त_rx_resources(काष्ठा udma_chan *uc)
अणु
	अगर (!uc->rchan)
		वापस;

	अगर (uc->rflow) अणु
		काष्ठा udma_rflow *rflow = uc->rflow;

		k3_ringacc_ring_मुक्त(rflow->fd_ring);
		k3_ringacc_ring_मुक्त(rflow->r_ring);
		rflow->fd_ring = शून्य;
		rflow->r_ring = शून्य;

		udma_put_rflow(uc);
	पूर्ण

	udma_put_rchan(uc);
पूर्ण

अटल पूर्णांक udma_alloc_rx_resources(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;
	काष्ठा k3_ring_cfg ring_cfg;
	काष्ठा udma_rflow *rflow;
	पूर्णांक fd_ring_id;
	पूर्णांक ret;

	ret = udma_get_rchan(uc);
	अगर (ret)
		वापस ret;

	/* For MEM_TO_MEM we करोn't need rflow or rings */
	अगर (uc->config.dir == DMA_MEM_TO_MEM)
		वापस 0;

	अगर (uc->config.शेष_flow_id >= 0)
		ret = udma_get_rflow(uc, uc->config.शेष_flow_id);
	अन्यथा
		ret = udma_get_rflow(uc, uc->rchan->id);

	अगर (ret) अणु
		ret = -EBUSY;
		जाओ err_rflow;
	पूर्ण

	rflow = uc->rflow;
	अगर (ud->tflow_cnt)
		fd_ring_id = ud->tflow_cnt + rflow->id;
	अन्यथा
		fd_ring_id = ud->bchan_cnt + ud->tchan_cnt + ud->echan_cnt +
			     uc->rchan->id;

	ret = k3_ringacc_request_rings_pair(ud->ringacc, fd_ring_id, -1,
					    &rflow->fd_ring, &rflow->r_ring);
	अगर (ret) अणु
		ret = -EBUSY;
		जाओ err_ring;
	पूर्ण

	स_रखो(&ring_cfg, 0, माप(ring_cfg));

	ring_cfg.elm_size = K3_RINGACC_RING_ELSIZE_8;
	अगर (ud->match_data->type == DMA_TYPE_UDMA) अणु
		अगर (uc->config.pkt_mode)
			ring_cfg.size = SG_MAX_SEGMENTS;
		अन्यथा
			ring_cfg.size = K3_UDMA_DEFAULT_RING_SIZE;

		ring_cfg.mode = K3_RINGACC_RING_MODE_MESSAGE;
	पूर्ण अन्यथा अणु
		ring_cfg.size = K3_UDMA_DEFAULT_RING_SIZE;
		ring_cfg.mode = K3_RINGACC_RING_MODE_RING;

		k3_configure_chan_coherency(&uc->vc.chan, uc->config.asel);
		ring_cfg.asel = uc->config.asel;
		ring_cfg.dma_dev = dmaengine_get_dma_device(&uc->vc.chan);
	पूर्ण

	ret = k3_ringacc_ring_cfg(rflow->fd_ring, &ring_cfg);

	ring_cfg.size = K3_UDMA_DEFAULT_RING_SIZE;
	ret |= k3_ringacc_ring_cfg(rflow->r_ring, &ring_cfg);

	अगर (ret)
		जाओ err_ringcfg;

	वापस 0;

err_ringcfg:
	k3_ringacc_ring_मुक्त(rflow->r_ring);
	rflow->r_ring = शून्य;
	k3_ringacc_ring_मुक्त(rflow->fd_ring);
	rflow->fd_ring = शून्य;
err_ring:
	udma_put_rflow(uc);
err_rflow:
	udma_put_rchan(uc);

	वापस ret;
पूर्ण

#घोषणा TISCI_BCDMA_BCHAN_VALID_PARAMS (			\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERR_VALID |	\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_EXTENDED_CH_TYPE_VALID)

#घोषणा TISCI_BCDMA_TCHAN_VALID_PARAMS (			\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERR_VALID |	\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_SUPR_TDPKT_VALID)

#घोषणा TISCI_BCDMA_RCHAN_VALID_PARAMS (			\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERR_VALID)

#घोषणा TISCI_UDMA_TCHAN_VALID_PARAMS (				\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERR_VALID |	\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_FILT_EINFO_VALID |	\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_FILT_PSWORDS_VALID |	\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_CHAN_TYPE_VALID |		\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_SUPR_TDPKT_VALID |	\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_FETCH_SIZE_VALID |		\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_CQ_QNUM_VALID |		\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_VALID)

#घोषणा TISCI_UDMA_RCHAN_VALID_PARAMS (				\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_PAUSE_ON_ERR_VALID |	\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_FETCH_SIZE_VALID |		\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_CQ_QNUM_VALID |		\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_CHAN_TYPE_VALID |		\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_RX_IGNORE_SHORT_VALID |	\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_RX_IGNORE_LONG_VALID |	\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_RX_FLOWID_START_VALID |	\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_RX_FLOWID_CNT_VALID |	\
	TI_SCI_MSG_VALUE_RM_UDMAP_CH_ATYPE_VALID)

अटल पूर्णांक udma_tisci_m2m_channel_config(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;
	काष्ठा udma_tisci_rm *tisci_rm = &ud->tisci_rm;
	स्थिर काष्ठा ti_sci_rm_udmap_ops *tisci_ops = tisci_rm->tisci_udmap_ops;
	काष्ठा udma_tchan *tchan = uc->tchan;
	काष्ठा udma_rchan *rchan = uc->rchan;
	u8 burst_size = 0;
	पूर्णांक ret;
	u8 tpl;

	/* Non synchronized - mem to mem type of transfer */
	पूर्णांक tc_ring = k3_ringacc_get_ring_id(tchan->tc_ring);
	काष्ठा ti_sci_msg_rm_udmap_tx_ch_cfg req_tx = अणु 0 पूर्ण;
	काष्ठा ti_sci_msg_rm_udmap_rx_ch_cfg req_rx = अणु 0 पूर्ण;

	अगर (ud->match_data->flags & UDMA_FLAG_BURST_SIZE) अणु
		tpl = udma_get_chan_tpl_index(&ud->tchan_tpl, tchan->id);

		burst_size = ud->match_data->burst_size[tpl];
	पूर्ण

	req_tx.valid_params = TISCI_UDMA_TCHAN_VALID_PARAMS;
	req_tx.nav_id = tisci_rm->tisci_dev_id;
	req_tx.index = tchan->id;
	req_tx.tx_chan_type = TI_SCI_RM_UDMAP_CHAN_TYPE_3RDP_BCOPY_PBRR;
	req_tx.tx_fetch_size = माप(काष्ठा cppi5_desc_hdr_t) >> 2;
	req_tx.txcq_qnum = tc_ring;
	req_tx.tx_atype = ud->atype;
	अगर (burst_size) अणु
		req_tx.valid_params |= TI_SCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_VALID;
		req_tx.tx_burst_size = burst_size;
	पूर्ण

	ret = tisci_ops->tx_ch_cfg(tisci_rm->tisci, &req_tx);
	अगर (ret) अणु
		dev_err(ud->dev, "tchan%d cfg failed %d\n", tchan->id, ret);
		वापस ret;
	पूर्ण

	req_rx.valid_params = TISCI_UDMA_RCHAN_VALID_PARAMS;
	req_rx.nav_id = tisci_rm->tisci_dev_id;
	req_rx.index = rchan->id;
	req_rx.rx_fetch_size = माप(काष्ठा cppi5_desc_hdr_t) >> 2;
	req_rx.rxcq_qnum = tc_ring;
	req_rx.rx_chan_type = TI_SCI_RM_UDMAP_CHAN_TYPE_3RDP_BCOPY_PBRR;
	req_rx.rx_atype = ud->atype;
	अगर (burst_size) अणु
		req_rx.valid_params |= TI_SCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_VALID;
		req_rx.rx_burst_size = burst_size;
	पूर्ण

	ret = tisci_ops->rx_ch_cfg(tisci_rm->tisci, &req_rx);
	अगर (ret)
		dev_err(ud->dev, "rchan%d alloc failed %d\n", rchan->id, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक bcdma_tisci_m2m_channel_config(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;
	काष्ठा udma_tisci_rm *tisci_rm = &ud->tisci_rm;
	स्थिर काष्ठा ti_sci_rm_udmap_ops *tisci_ops = tisci_rm->tisci_udmap_ops;
	काष्ठा ti_sci_msg_rm_udmap_tx_ch_cfg req_tx = अणु 0 पूर्ण;
	काष्ठा udma_bchan *bchan = uc->bchan;
	u8 burst_size = 0;
	पूर्णांक ret;
	u8 tpl;

	अगर (ud->match_data->flags & UDMA_FLAG_BURST_SIZE) अणु
		tpl = udma_get_chan_tpl_index(&ud->bchan_tpl, bchan->id);

		burst_size = ud->match_data->burst_size[tpl];
	पूर्ण

	req_tx.valid_params = TISCI_BCDMA_BCHAN_VALID_PARAMS;
	req_tx.nav_id = tisci_rm->tisci_dev_id;
	req_tx.extended_ch_type = TI_SCI_RM_BCDMA_EXTENDED_CH_TYPE_BCHAN;
	req_tx.index = bchan->id;
	अगर (burst_size) अणु
		req_tx.valid_params |= TI_SCI_MSG_VALUE_RM_UDMAP_CH_BURST_SIZE_VALID;
		req_tx.tx_burst_size = burst_size;
	पूर्ण

	ret = tisci_ops->tx_ch_cfg(tisci_rm->tisci, &req_tx);
	अगर (ret)
		dev_err(ud->dev, "bchan%d cfg failed %d\n", bchan->id, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक udma_tisci_tx_channel_config(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;
	काष्ठा udma_tisci_rm *tisci_rm = &ud->tisci_rm;
	स्थिर काष्ठा ti_sci_rm_udmap_ops *tisci_ops = tisci_rm->tisci_udmap_ops;
	काष्ठा udma_tchan *tchan = uc->tchan;
	पूर्णांक tc_ring = k3_ringacc_get_ring_id(tchan->tc_ring);
	काष्ठा ti_sci_msg_rm_udmap_tx_ch_cfg req_tx = अणु 0 पूर्ण;
	u32 mode, fetch_size;
	पूर्णांक ret;

	अगर (uc->config.pkt_mode) अणु
		mode = TI_SCI_RM_UDMAP_CHAN_TYPE_PKT_PBRR;
		fetch_size = cppi5_hdesc_calc_size(uc->config.needs_epib,
						   uc->config.psd_size, 0);
	पूर्ण अन्यथा अणु
		mode = TI_SCI_RM_UDMAP_CHAN_TYPE_3RDP_PBRR;
		fetch_size = माप(काष्ठा cppi5_desc_hdr_t);
	पूर्ण

	req_tx.valid_params = TISCI_UDMA_TCHAN_VALID_PARAMS;
	req_tx.nav_id = tisci_rm->tisci_dev_id;
	req_tx.index = tchan->id;
	req_tx.tx_chan_type = mode;
	req_tx.tx_supr_tdpkt = uc->config.notdpkt;
	req_tx.tx_fetch_size = fetch_size >> 2;
	req_tx.txcq_qnum = tc_ring;
	req_tx.tx_atype = uc->config.atype;
	अगर (uc->config.ep_type == PSIL_EP_PDMA_XY &&
	    ud->match_data->flags & UDMA_FLAG_TDTYPE) अणु
		/* रुको क्रम peer to complete the tearकरोwn क्रम PDMAs */
		req_tx.valid_params |=
				TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_TDTYPE_VALID;
		req_tx.tx_tdtype = 1;
	पूर्ण

	ret = tisci_ops->tx_ch_cfg(tisci_rm->tisci, &req_tx);
	अगर (ret)
		dev_err(ud->dev, "tchan%d cfg failed %d\n", tchan->id, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक bcdma_tisci_tx_channel_config(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;
	काष्ठा udma_tisci_rm *tisci_rm = &ud->tisci_rm;
	स्थिर काष्ठा ti_sci_rm_udmap_ops *tisci_ops = tisci_rm->tisci_udmap_ops;
	काष्ठा udma_tchan *tchan = uc->tchan;
	काष्ठा ti_sci_msg_rm_udmap_tx_ch_cfg req_tx = अणु 0 पूर्ण;
	पूर्णांक ret;

	req_tx.valid_params = TISCI_BCDMA_TCHAN_VALID_PARAMS;
	req_tx.nav_id = tisci_rm->tisci_dev_id;
	req_tx.index = tchan->id;
	req_tx.tx_supr_tdpkt = uc->config.notdpkt;
	अगर (ud->match_data->flags & UDMA_FLAG_TDTYPE) अणु
		/* रुको क्रम peer to complete the tearकरोwn क्रम PDMAs */
		req_tx.valid_params |=
				TI_SCI_MSG_VALUE_RM_UDMAP_CH_TX_TDTYPE_VALID;
		req_tx.tx_tdtype = 1;
	पूर्ण

	ret = tisci_ops->tx_ch_cfg(tisci_rm->tisci, &req_tx);
	अगर (ret)
		dev_err(ud->dev, "tchan%d cfg failed %d\n", tchan->id, ret);

	वापस ret;
पूर्ण

#घोषणा pktdma_tisci_tx_channel_config bcdma_tisci_tx_channel_config

अटल पूर्णांक udma_tisci_rx_channel_config(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;
	काष्ठा udma_tisci_rm *tisci_rm = &ud->tisci_rm;
	स्थिर काष्ठा ti_sci_rm_udmap_ops *tisci_ops = tisci_rm->tisci_udmap_ops;
	काष्ठा udma_rchan *rchan = uc->rchan;
	पूर्णांक fd_ring = k3_ringacc_get_ring_id(uc->rflow->fd_ring);
	पूर्णांक rx_ring = k3_ringacc_get_ring_id(uc->rflow->r_ring);
	काष्ठा ti_sci_msg_rm_udmap_rx_ch_cfg req_rx = अणु 0 पूर्ण;
	काष्ठा ti_sci_msg_rm_udmap_flow_cfg flow_req = अणु 0 पूर्ण;
	u32 mode, fetch_size;
	पूर्णांक ret;

	अगर (uc->config.pkt_mode) अणु
		mode = TI_SCI_RM_UDMAP_CHAN_TYPE_PKT_PBRR;
		fetch_size = cppi5_hdesc_calc_size(uc->config.needs_epib,
						   uc->config.psd_size, 0);
	पूर्ण अन्यथा अणु
		mode = TI_SCI_RM_UDMAP_CHAN_TYPE_3RDP_PBRR;
		fetch_size = माप(काष्ठा cppi5_desc_hdr_t);
	पूर्ण

	req_rx.valid_params = TISCI_UDMA_RCHAN_VALID_PARAMS;
	req_rx.nav_id = tisci_rm->tisci_dev_id;
	req_rx.index = rchan->id;
	req_rx.rx_fetch_size =  fetch_size >> 2;
	req_rx.rxcq_qnum = rx_ring;
	req_rx.rx_chan_type = mode;
	req_rx.rx_atype = uc->config.atype;

	ret = tisci_ops->rx_ch_cfg(tisci_rm->tisci, &req_rx);
	अगर (ret) अणु
		dev_err(ud->dev, "rchan%d cfg failed %d\n", rchan->id, ret);
		वापस ret;
	पूर्ण

	flow_req.valid_params =
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_EINFO_PRESENT_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_PSINFO_PRESENT_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_ERROR_HANDLING_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DESC_TYPE_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_QNUM_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_HI_SEL_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_SRC_TAG_LO_SEL_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_HI_SEL_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_DEST_TAG_LO_SEL_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ0_SZ0_QNUM_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ1_QNUM_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ2_QNUM_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_FDQ3_QNUM_VALID;

	flow_req.nav_id = tisci_rm->tisci_dev_id;
	flow_req.flow_index = rchan->id;

	अगर (uc->config.needs_epib)
		flow_req.rx_einfo_present = 1;
	अन्यथा
		flow_req.rx_einfo_present = 0;
	अगर (uc->config.psd_size)
		flow_req.rx_psinfo_present = 1;
	अन्यथा
		flow_req.rx_psinfo_present = 0;
	flow_req.rx_error_handling = 1;
	flow_req.rx_dest_qnum = rx_ring;
	flow_req.rx_src_tag_hi_sel = UDMA_RFLOW_SRCTAG_NONE;
	flow_req.rx_src_tag_lo_sel = UDMA_RFLOW_SRCTAG_SRC_TAG;
	flow_req.rx_dest_tag_hi_sel = UDMA_RFLOW_DSTTAG_DST_TAG_HI;
	flow_req.rx_dest_tag_lo_sel = UDMA_RFLOW_DSTTAG_DST_TAG_LO;
	flow_req.rx_fdq0_sz0_qnum = fd_ring;
	flow_req.rx_fdq1_qnum = fd_ring;
	flow_req.rx_fdq2_qnum = fd_ring;
	flow_req.rx_fdq3_qnum = fd_ring;

	ret = tisci_ops->rx_flow_cfg(tisci_rm->tisci, &flow_req);

	अगर (ret)
		dev_err(ud->dev, "flow%d config failed: %d\n", rchan->id, ret);

	वापस 0;
पूर्ण

अटल पूर्णांक bcdma_tisci_rx_channel_config(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;
	काष्ठा udma_tisci_rm *tisci_rm = &ud->tisci_rm;
	स्थिर काष्ठा ti_sci_rm_udmap_ops *tisci_ops = tisci_rm->tisci_udmap_ops;
	काष्ठा udma_rchan *rchan = uc->rchan;
	काष्ठा ti_sci_msg_rm_udmap_rx_ch_cfg req_rx = अणु 0 पूर्ण;
	पूर्णांक ret;

	req_rx.valid_params = TISCI_BCDMA_RCHAN_VALID_PARAMS;
	req_rx.nav_id = tisci_rm->tisci_dev_id;
	req_rx.index = rchan->id;

	ret = tisci_ops->rx_ch_cfg(tisci_rm->tisci, &req_rx);
	अगर (ret)
		dev_err(ud->dev, "rchan%d cfg failed %d\n", rchan->id, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक pktdma_tisci_rx_channel_config(काष्ठा udma_chan *uc)
अणु
	काष्ठा udma_dev *ud = uc->ud;
	काष्ठा udma_tisci_rm *tisci_rm = &ud->tisci_rm;
	स्थिर काष्ठा ti_sci_rm_udmap_ops *tisci_ops = tisci_rm->tisci_udmap_ops;
	काष्ठा ti_sci_msg_rm_udmap_rx_ch_cfg req_rx = अणु 0 पूर्ण;
	काष्ठा ti_sci_msg_rm_udmap_flow_cfg flow_req = अणु 0 पूर्ण;
	पूर्णांक ret;

	req_rx.valid_params = TISCI_BCDMA_RCHAN_VALID_PARAMS;
	req_rx.nav_id = tisci_rm->tisci_dev_id;
	req_rx.index = uc->rchan->id;

	ret = tisci_ops->rx_ch_cfg(tisci_rm->tisci, &req_rx);
	अगर (ret) अणु
		dev_err(ud->dev, "rchan%d cfg failed %d\n", uc->rchan->id, ret);
		वापस ret;
	पूर्ण

	flow_req.valid_params =
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_EINFO_PRESENT_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_PSINFO_PRESENT_VALID |
		TI_SCI_MSG_VALUE_RM_UDMAP_FLOW_ERROR_HANDLING_VALID;

	flow_req.nav_id = tisci_rm->tisci_dev_id;
	flow_req.flow_index = uc->rflow->id;

	अगर (uc->config.needs_epib)
		flow_req.rx_einfo_present = 1;
	अन्यथा
		flow_req.rx_einfo_present = 0;
	अगर (uc->config.psd_size)
		flow_req.rx_psinfo_present = 1;
	अन्यथा
		flow_req.rx_psinfo_present = 0;
	flow_req.rx_error_handling = 1;

	ret = tisci_ops->rx_flow_cfg(tisci_rm->tisci, &flow_req);

	अगर (ret)
		dev_err(ud->dev, "flow%d config failed: %d\n", uc->rflow->id,
			ret);

	वापस ret;
पूर्ण

अटल पूर्णांक udma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);
	काष्ठा udma_dev *ud = to_udma_dev(chan->device);
	स्थिर काष्ठा udma_soc_data *soc_data = ud->soc_data;
	काष्ठा k3_ring *irq_ring;
	u32 irq_udma_idx;
	पूर्णांक ret;

	uc->dma_dev = ud->dev;

	अगर (uc->config.pkt_mode || uc->config.dir == DMA_MEM_TO_MEM) अणु
		uc->use_dma_pool = true;
		/* in हाल of MEM_TO_MEM we have maximum of two TRs */
		अगर (uc->config.dir == DMA_MEM_TO_MEM) अणु
			uc->config.hdesc_size = cppi5_trdesc_calc_size(
					माप(काष्ठा cppi5_tr_type15_t), 2);
			uc->config.pkt_mode = false;
		पूर्ण
	पूर्ण

	अगर (uc->use_dma_pool) अणु
		uc->hdesc_pool = dma_pool_create(uc->name, ud->ddev.dev,
						 uc->config.hdesc_size,
						 ud->desc_align,
						 0);
		अगर (!uc->hdesc_pool) अणु
			dev_err(ud->ddev.dev,
				"Descriptor pool allocation failed\n");
			uc->use_dma_pool = false;
			ret = -ENOMEM;
			जाओ err_cleanup;
		पूर्ण
	पूर्ण

	/*
	 * Make sure that the completion is in a known state:
	 * No tearकरोwn, the channel is idle
	 */
	reinit_completion(&uc->tearकरोwn_completed);
	complete_all(&uc->tearकरोwn_completed);
	uc->state = UDMA_CHAN_IS_IDLE;

	चयन (uc->config.dir) अणु
	हाल DMA_MEM_TO_MEM:
		/* Non synchronized - mem to mem type of transfer */
		dev_dbg(uc->ud->dev, "%s: chan%d as MEM-to-MEM\n", __func__,
			uc->id);

		ret = udma_get_chan_pair(uc);
		अगर (ret)
			जाओ err_cleanup;

		ret = udma_alloc_tx_resources(uc);
		अगर (ret) अणु
			udma_put_rchan(uc);
			जाओ err_cleanup;
		पूर्ण

		ret = udma_alloc_rx_resources(uc);
		अगर (ret) अणु
			udma_मुक्त_tx_resources(uc);
			जाओ err_cleanup;
		पूर्ण

		uc->config.src_thपढ़ो = ud->psil_base + uc->tchan->id;
		uc->config.dst_thपढ़ो = (ud->psil_base + uc->rchan->id) |
					K3_PSIL_DST_THREAD_ID_OFFSET;

		irq_ring = uc->tchan->tc_ring;
		irq_udma_idx = uc->tchan->id;

		ret = udma_tisci_m2m_channel_config(uc);
		अवरोध;
	हाल DMA_MEM_TO_DEV:
		/* Slave transfer synchronized - mem to dev (TX) trasnfer */
		dev_dbg(uc->ud->dev, "%s: chan%d as MEM-to-DEV\n", __func__,
			uc->id);

		ret = udma_alloc_tx_resources(uc);
		अगर (ret)
			जाओ err_cleanup;

		uc->config.src_thपढ़ो = ud->psil_base + uc->tchan->id;
		uc->config.dst_thपढ़ो = uc->config.remote_thपढ़ो_id;
		uc->config.dst_thपढ़ो |= K3_PSIL_DST_THREAD_ID_OFFSET;

		irq_ring = uc->tchan->tc_ring;
		irq_udma_idx = uc->tchan->id;

		ret = udma_tisci_tx_channel_config(uc);
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		/* Slave transfer synchronized - dev to mem (RX) trasnfer */
		dev_dbg(uc->ud->dev, "%s: chan%d as DEV-to-MEM\n", __func__,
			uc->id);

		ret = udma_alloc_rx_resources(uc);
		अगर (ret)
			जाओ err_cleanup;

		uc->config.src_thपढ़ो = uc->config.remote_thपढ़ो_id;
		uc->config.dst_thपढ़ो = (ud->psil_base + uc->rchan->id) |
					K3_PSIL_DST_THREAD_ID_OFFSET;

		irq_ring = uc->rflow->r_ring;
		irq_udma_idx = soc_data->oes.udma_rchan + uc->rchan->id;

		ret = udma_tisci_rx_channel_config(uc);
		अवरोध;
	शेष:
		/* Can not happen */
		dev_err(uc->ud->dev, "%s: chan%d invalid direction (%u)\n",
			__func__, uc->id, uc->config.dir);
		ret = -EINVAL;
		जाओ err_cleanup;

	पूर्ण

	/* check अगर the channel configuration was successful */
	अगर (ret)
		जाओ err_res_मुक्त;

	अगर (udma_is_chan_running(uc)) अणु
		dev_warn(ud->dev, "chan%d: is running!\n", uc->id);
		udma_reset_chan(uc, false);
		अगर (udma_is_chan_running(uc)) अणु
			dev_err(ud->dev, "chan%d: won't stop!\n", uc->id);
			ret = -EBUSY;
			जाओ err_res_मुक्त;
		पूर्ण
	पूर्ण

	/* PSI-L pairing */
	ret = navss_psil_pair(ud, uc->config.src_thपढ़ो, uc->config.dst_thपढ़ो);
	अगर (ret) अणु
		dev_err(ud->dev, "PSI-L pairing failed: 0x%04x -> 0x%04x\n",
			uc->config.src_thपढ़ो, uc->config.dst_thपढ़ो);
		जाओ err_res_मुक्त;
	पूर्ण

	uc->psil_paired = true;

	uc->irq_num_ring = k3_ringacc_get_ring_irq_num(irq_ring);
	अगर (uc->irq_num_ring <= 0) अणु
		dev_err(ud->dev, "Failed to get ring irq (index: %u)\n",
			k3_ringacc_get_ring_id(irq_ring));
		ret = -EINVAL;
		जाओ err_psi_मुक्त;
	पूर्ण

	ret = request_irq(uc->irq_num_ring, udma_ring_irq_handler,
			  IRQF_TRIGGER_HIGH, uc->name, uc);
	अगर (ret) अणु
		dev_err(ud->dev, "chan%d: ring irq request failed\n", uc->id);
		जाओ err_irq_मुक्त;
	पूर्ण

	/* Event from UDMA (TR events) only needed क्रम slave TR mode channels */
	अगर (is_slave_direction(uc->config.dir) && !uc->config.pkt_mode) अणु
		uc->irq_num_udma = ti_sci_पूर्णांकa_msi_get_virq(ud->dev,
							    irq_udma_idx);
		अगर (uc->irq_num_udma <= 0) अणु
			dev_err(ud->dev, "Failed to get udma irq (index: %u)\n",
				irq_udma_idx);
			मुक्त_irq(uc->irq_num_ring, uc);
			ret = -EINVAL;
			जाओ err_irq_मुक्त;
		पूर्ण

		ret = request_irq(uc->irq_num_udma, udma_udma_irq_handler, 0,
				  uc->name, uc);
		अगर (ret) अणु
			dev_err(ud->dev, "chan%d: UDMA irq request failed\n",
				uc->id);
			मुक्त_irq(uc->irq_num_ring, uc);
			जाओ err_irq_मुक्त;
		पूर्ण
	पूर्ण अन्यथा अणु
		uc->irq_num_udma = 0;
	पूर्ण

	udma_reset_rings(uc);

	वापस 0;

err_irq_मुक्त:
	uc->irq_num_ring = 0;
	uc->irq_num_udma = 0;
err_psi_मुक्त:
	navss_psil_unpair(ud, uc->config.src_thपढ़ो, uc->config.dst_thपढ़ो);
	uc->psil_paired = false;
err_res_मुक्त:
	udma_मुक्त_tx_resources(uc);
	udma_मुक्त_rx_resources(uc);
err_cleanup:
	udma_reset_uchan(uc);

	अगर (uc->use_dma_pool) अणु
		dma_pool_destroy(uc->hdesc_pool);
		uc->use_dma_pool = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bcdma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);
	काष्ठा udma_dev *ud = to_udma_dev(chan->device);
	स्थिर काष्ठा udma_oes_offsets *oes = &ud->soc_data->oes;
	u32 irq_udma_idx, irq_ring_idx;
	पूर्णांक ret;

	/* Only TR mode is supported */
	uc->config.pkt_mode = false;

	/*
	 * Make sure that the completion is in a known state:
	 * No tearकरोwn, the channel is idle
	 */
	reinit_completion(&uc->tearकरोwn_completed);
	complete_all(&uc->tearकरोwn_completed);
	uc->state = UDMA_CHAN_IS_IDLE;

	चयन (uc->config.dir) अणु
	हाल DMA_MEM_TO_MEM:
		/* Non synchronized - mem to mem type of transfer */
		dev_dbg(uc->ud->dev, "%s: chan%d as MEM-to-MEM\n", __func__,
			uc->id);

		ret = bcdma_alloc_bchan_resources(uc);
		अगर (ret)
			वापस ret;

		irq_ring_idx = uc->bchan->id + oes->bcdma_bchan_ring;
		irq_udma_idx = uc->bchan->id + oes->bcdma_bchan_data;

		ret = bcdma_tisci_m2m_channel_config(uc);
		अवरोध;
	हाल DMA_MEM_TO_DEV:
		/* Slave transfer synchronized - mem to dev (TX) trasnfer */
		dev_dbg(uc->ud->dev, "%s: chan%d as MEM-to-DEV\n", __func__,
			uc->id);

		ret = udma_alloc_tx_resources(uc);
		अगर (ret) अणु
			uc->config.remote_thपढ़ो_id = -1;
			वापस ret;
		पूर्ण

		uc->config.src_thपढ़ो = ud->psil_base + uc->tchan->id;
		uc->config.dst_thपढ़ो = uc->config.remote_thपढ़ो_id;
		uc->config.dst_thपढ़ो |= K3_PSIL_DST_THREAD_ID_OFFSET;

		irq_ring_idx = uc->tchan->id + oes->bcdma_tchan_ring;
		irq_udma_idx = uc->tchan->id + oes->bcdma_tchan_data;

		ret = bcdma_tisci_tx_channel_config(uc);
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		/* Slave transfer synchronized - dev to mem (RX) trasnfer */
		dev_dbg(uc->ud->dev, "%s: chan%d as DEV-to-MEM\n", __func__,
			uc->id);

		ret = udma_alloc_rx_resources(uc);
		अगर (ret) अणु
			uc->config.remote_thपढ़ो_id = -1;
			वापस ret;
		पूर्ण

		uc->config.src_thपढ़ो = uc->config.remote_thपढ़ो_id;
		uc->config.dst_thपढ़ो = (ud->psil_base + uc->rchan->id) |
					K3_PSIL_DST_THREAD_ID_OFFSET;

		irq_ring_idx = uc->rchan->id + oes->bcdma_rchan_ring;
		irq_udma_idx = uc->rchan->id + oes->bcdma_rchan_data;

		ret = bcdma_tisci_rx_channel_config(uc);
		अवरोध;
	शेष:
		/* Can not happen */
		dev_err(uc->ud->dev, "%s: chan%d invalid direction (%u)\n",
			__func__, uc->id, uc->config.dir);
		वापस -EINVAL;
	पूर्ण

	/* check अगर the channel configuration was successful */
	अगर (ret)
		जाओ err_res_मुक्त;

	अगर (udma_is_chan_running(uc)) अणु
		dev_warn(ud->dev, "chan%d: is running!\n", uc->id);
		udma_reset_chan(uc, false);
		अगर (udma_is_chan_running(uc)) अणु
			dev_err(ud->dev, "chan%d: won't stop!\n", uc->id);
			ret = -EBUSY;
			जाओ err_res_मुक्त;
		पूर्ण
	पूर्ण

	uc->dma_dev = dmaengine_get_dma_device(chan);
	अगर (uc->config.dir == DMA_MEM_TO_MEM  && !uc->config.tr_trigger_type) अणु
		uc->config.hdesc_size = cppi5_trdesc_calc_size(
					माप(काष्ठा cppi5_tr_type15_t), 2);

		uc->hdesc_pool = dma_pool_create(uc->name, ud->ddev.dev,
						 uc->config.hdesc_size,
						 ud->desc_align,
						 0);
		अगर (!uc->hdesc_pool) अणु
			dev_err(ud->ddev.dev,
				"Descriptor pool allocation failed\n");
			uc->use_dma_pool = false;
			ret = -ENOMEM;
			जाओ err_res_मुक्त;
		पूर्ण

		uc->use_dma_pool = true;
	पूर्ण अन्यथा अगर (uc->config.dir != DMA_MEM_TO_MEM) अणु
		/* PSI-L pairing */
		ret = navss_psil_pair(ud, uc->config.src_thपढ़ो,
				      uc->config.dst_thपढ़ो);
		अगर (ret) अणु
			dev_err(ud->dev,
				"PSI-L pairing failed: 0x%04x -> 0x%04x\n",
				uc->config.src_thपढ़ो, uc->config.dst_thपढ़ो);
			जाओ err_res_मुक्त;
		पूर्ण

		uc->psil_paired = true;
	पूर्ण

	uc->irq_num_ring = ti_sci_पूर्णांकa_msi_get_virq(ud->dev, irq_ring_idx);
	अगर (uc->irq_num_ring <= 0) अणु
		dev_err(ud->dev, "Failed to get ring irq (index: %u)\n",
			irq_ring_idx);
		ret = -EINVAL;
		जाओ err_psi_मुक्त;
	पूर्ण

	ret = request_irq(uc->irq_num_ring, udma_ring_irq_handler,
			  IRQF_TRIGGER_HIGH, uc->name, uc);
	अगर (ret) अणु
		dev_err(ud->dev, "chan%d: ring irq request failed\n", uc->id);
		जाओ err_irq_मुक्त;
	पूर्ण

	/* Event from BCDMA (TR events) only needed क्रम slave channels */
	अगर (is_slave_direction(uc->config.dir)) अणु
		uc->irq_num_udma = ti_sci_पूर्णांकa_msi_get_virq(ud->dev,
							    irq_udma_idx);
		अगर (uc->irq_num_udma <= 0) अणु
			dev_err(ud->dev, "Failed to get bcdma irq (index: %u)\n",
				irq_udma_idx);
			मुक्त_irq(uc->irq_num_ring, uc);
			ret = -EINVAL;
			जाओ err_irq_मुक्त;
		पूर्ण

		ret = request_irq(uc->irq_num_udma, udma_udma_irq_handler, 0,
				  uc->name, uc);
		अगर (ret) अणु
			dev_err(ud->dev, "chan%d: BCDMA irq request failed\n",
				uc->id);
			मुक्त_irq(uc->irq_num_ring, uc);
			जाओ err_irq_मुक्त;
		पूर्ण
	पूर्ण अन्यथा अणु
		uc->irq_num_udma = 0;
	पूर्ण

	udma_reset_rings(uc);

	INIT_DELAYED_WORK_ONSTACK(&uc->tx_drain.work,
				  udma_check_tx_completion);
	वापस 0;

err_irq_मुक्त:
	uc->irq_num_ring = 0;
	uc->irq_num_udma = 0;
err_psi_मुक्त:
	अगर (uc->psil_paired)
		navss_psil_unpair(ud, uc->config.src_thपढ़ो,
				  uc->config.dst_thपढ़ो);
	uc->psil_paired = false;
err_res_मुक्त:
	bcdma_मुक्त_bchan_resources(uc);
	udma_मुक्त_tx_resources(uc);
	udma_मुक्त_rx_resources(uc);

	udma_reset_uchan(uc);

	अगर (uc->use_dma_pool) अणु
		dma_pool_destroy(uc->hdesc_pool);
		uc->use_dma_pool = false;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bcdma_router_config(काष्ठा dma_chan *chan)
अणु
	काष्ठा k3_event_route_data *router_data = chan->route_data;
	काष्ठा udma_chan *uc = to_udma_chan(chan);
	u32 trigger_event;

	अगर (!uc->bchan)
		वापस -EINVAL;

	अगर (uc->config.tr_trigger_type != 1 && uc->config.tr_trigger_type != 2)
		वापस -EINVAL;

	trigger_event = uc->ud->soc_data->bcdma_trigger_event_offset;
	trigger_event += (uc->bchan->id * 2) + uc->config.tr_trigger_type - 1;

	वापस router_data->set_event(router_data->priv, trigger_event);
पूर्ण

अटल पूर्णांक pktdma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);
	काष्ठा udma_dev *ud = to_udma_dev(chan->device);
	स्थिर काष्ठा udma_oes_offsets *oes = &ud->soc_data->oes;
	u32 irq_ring_idx;
	पूर्णांक ret;

	/*
	 * Make sure that the completion is in a known state:
	 * No tearकरोwn, the channel is idle
	 */
	reinit_completion(&uc->tearकरोwn_completed);
	complete_all(&uc->tearकरोwn_completed);
	uc->state = UDMA_CHAN_IS_IDLE;

	चयन (uc->config.dir) अणु
	हाल DMA_MEM_TO_DEV:
		/* Slave transfer synchronized - mem to dev (TX) trasnfer */
		dev_dbg(uc->ud->dev, "%s: chan%d as MEM-to-DEV\n", __func__,
			uc->id);

		ret = udma_alloc_tx_resources(uc);
		अगर (ret) अणु
			uc->config.remote_thपढ़ो_id = -1;
			वापस ret;
		पूर्ण

		uc->config.src_thपढ़ो = ud->psil_base + uc->tchan->id;
		uc->config.dst_thपढ़ो = uc->config.remote_thपढ़ो_id;
		uc->config.dst_thपढ़ो |= K3_PSIL_DST_THREAD_ID_OFFSET;

		irq_ring_idx = uc->tchan->tflow_id + oes->pktdma_tchan_flow;

		ret = pktdma_tisci_tx_channel_config(uc);
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		/* Slave transfer synchronized - dev to mem (RX) trasnfer */
		dev_dbg(uc->ud->dev, "%s: chan%d as DEV-to-MEM\n", __func__,
			uc->id);

		ret = udma_alloc_rx_resources(uc);
		अगर (ret) अणु
			uc->config.remote_thपढ़ो_id = -1;
			वापस ret;
		पूर्ण

		uc->config.src_thपढ़ो = uc->config.remote_thपढ़ो_id;
		uc->config.dst_thपढ़ो = (ud->psil_base + uc->rchan->id) |
					K3_PSIL_DST_THREAD_ID_OFFSET;

		irq_ring_idx = uc->rflow->id + oes->pktdma_rchan_flow;

		ret = pktdma_tisci_rx_channel_config(uc);
		अवरोध;
	शेष:
		/* Can not happen */
		dev_err(uc->ud->dev, "%s: chan%d invalid direction (%u)\n",
			__func__, uc->id, uc->config.dir);
		वापस -EINVAL;
	पूर्ण

	/* check अगर the channel configuration was successful */
	अगर (ret)
		जाओ err_res_मुक्त;

	अगर (udma_is_chan_running(uc)) अणु
		dev_warn(ud->dev, "chan%d: is running!\n", uc->id);
		udma_reset_chan(uc, false);
		अगर (udma_is_chan_running(uc)) अणु
			dev_err(ud->dev, "chan%d: won't stop!\n", uc->id);
			ret = -EBUSY;
			जाओ err_res_मुक्त;
		पूर्ण
	पूर्ण

	uc->dma_dev = dmaengine_get_dma_device(chan);
	uc->hdesc_pool = dma_pool_create(uc->name, uc->dma_dev,
					 uc->config.hdesc_size, ud->desc_align,
					 0);
	अगर (!uc->hdesc_pool) अणु
		dev_err(ud->ddev.dev,
			"Descriptor pool allocation failed\n");
		uc->use_dma_pool = false;
		ret = -ENOMEM;
		जाओ err_res_मुक्त;
	पूर्ण

	uc->use_dma_pool = true;

	/* PSI-L pairing */
	ret = navss_psil_pair(ud, uc->config.src_thपढ़ो, uc->config.dst_thपढ़ो);
	अगर (ret) अणु
		dev_err(ud->dev, "PSI-L pairing failed: 0x%04x -> 0x%04x\n",
			uc->config.src_thपढ़ो, uc->config.dst_thपढ़ो);
		जाओ err_res_मुक्त;
	पूर्ण

	uc->psil_paired = true;

	uc->irq_num_ring = ti_sci_पूर्णांकa_msi_get_virq(ud->dev, irq_ring_idx);
	अगर (uc->irq_num_ring <= 0) अणु
		dev_err(ud->dev, "Failed to get ring irq (index: %u)\n",
			irq_ring_idx);
		ret = -EINVAL;
		जाओ err_psi_मुक्त;
	पूर्ण

	ret = request_irq(uc->irq_num_ring, udma_ring_irq_handler,
			  IRQF_TRIGGER_HIGH, uc->name, uc);
	अगर (ret) अणु
		dev_err(ud->dev, "chan%d: ring irq request failed\n", uc->id);
		जाओ err_irq_मुक्त;
	पूर्ण

	uc->irq_num_udma = 0;

	udma_reset_rings(uc);

	INIT_DELAYED_WORK_ONSTACK(&uc->tx_drain.work,
				  udma_check_tx_completion);

	अगर (uc->tchan)
		dev_dbg(ud->dev,
			"chan%d: tchan%d, tflow%d, Remote thread: 0x%04x\n",
			uc->id, uc->tchan->id, uc->tchan->tflow_id,
			uc->config.remote_thपढ़ो_id);
	अन्यथा अगर (uc->rchan)
		dev_dbg(ud->dev,
			"chan%d: rchan%d, rflow%d, Remote thread: 0x%04x\n",
			uc->id, uc->rchan->id, uc->rflow->id,
			uc->config.remote_thपढ़ो_id);
	वापस 0;

err_irq_मुक्त:
	uc->irq_num_ring = 0;
err_psi_मुक्त:
	navss_psil_unpair(ud, uc->config.src_thपढ़ो, uc->config.dst_thपढ़ो);
	uc->psil_paired = false;
err_res_मुक्त:
	udma_मुक्त_tx_resources(uc);
	udma_मुक्त_rx_resources(uc);

	udma_reset_uchan(uc);

	dma_pool_destroy(uc->hdesc_pool);
	uc->use_dma_pool = false;

	वापस ret;
पूर्ण

अटल पूर्णांक udma_slave_config(काष्ठा dma_chan *chan,
			     काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);

	स_नकल(&uc->cfg, cfg, माप(uc->cfg));

	वापस 0;
पूर्ण

अटल काष्ठा udma_desc *udma_alloc_tr_desc(काष्ठा udma_chan *uc,
					    माप_प्रकार tr_size, पूर्णांक tr_count,
					    क्रमागत dma_transfer_direction dir)
अणु
	काष्ठा udma_hwdesc *hwdesc;
	काष्ठा cppi5_desc_hdr_t *tr_desc;
	काष्ठा udma_desc *d;
	u32 reload_count = 0;
	u32 ring_id;

	चयन (tr_size) अणु
	हाल 16:
	हाल 32:
	हाल 64:
	हाल 128:
		अवरोध;
	शेष:
		dev_err(uc->ud->dev, "Unsupported TR size of %zu\n", tr_size);
		वापस शून्य;
	पूर्ण

	/* We have only one descriptor containing multiple TRs */
	d = kzalloc(माप(*d) + माप(d->hwdesc[0]), GFP_NOWAIT);
	अगर (!d)
		वापस शून्य;

	d->sglen = tr_count;

	d->hwdesc_count = 1;
	hwdesc = &d->hwdesc[0];

	/* Allocate memory क्रम DMA ring descriptor */
	अगर (uc->use_dma_pool) अणु
		hwdesc->cppi5_desc_size = uc->config.hdesc_size;
		hwdesc->cppi5_desc_vaddr = dma_pool_zalloc(uc->hdesc_pool,
						GFP_NOWAIT,
						&hwdesc->cppi5_desc_paddr);
	पूर्ण अन्यथा अणु
		hwdesc->cppi5_desc_size = cppi5_trdesc_calc_size(tr_size,
								 tr_count);
		hwdesc->cppi5_desc_size = ALIGN(hwdesc->cppi5_desc_size,
						uc->ud->desc_align);
		hwdesc->cppi5_desc_vaddr = dma_alloc_coherent(uc->ud->dev,
						hwdesc->cppi5_desc_size,
						&hwdesc->cppi5_desc_paddr,
						GFP_NOWAIT);
	पूर्ण

	अगर (!hwdesc->cppi5_desc_vaddr) अणु
		kमुक्त(d);
		वापस शून्य;
	पूर्ण

	/* Start of the TR req records */
	hwdesc->tr_req_base = hwdesc->cppi5_desc_vaddr + tr_size;
	/* Start address of the TR response array */
	hwdesc->tr_resp_base = hwdesc->tr_req_base + tr_size * tr_count;

	tr_desc = hwdesc->cppi5_desc_vaddr;

	अगर (uc->cyclic)
		reload_count = CPPI5_INFO0_TRDESC_RLDCNT_INFINITE;

	अगर (dir == DMA_DEV_TO_MEM)
		ring_id = k3_ringacc_get_ring_id(uc->rflow->r_ring);
	अन्यथा
		ring_id = k3_ringacc_get_ring_id(uc->tchan->tc_ring);

	cppi5_trdesc_init(tr_desc, tr_count, tr_size, 0, reload_count);
	cppi5_desc_set_pktids(tr_desc, uc->id,
			      CPPI5_INFO1_DESC_FLOWID_DEFAULT);
	cppi5_desc_set_retpolicy(tr_desc, 0, ring_id);

	वापस d;
पूर्ण

/**
 * udma_get_tr_counters - calculate TR counters क्रम a given length
 * @len: Length of the trasnfer
 * @align_to: Preferred alignment
 * @tr0_cnt0: First TR icnt0
 * @tr0_cnt1: First TR icnt1
 * @tr1_cnt0: Second (अगर used) TR icnt0
 *
 * For len < SZ_64K only one TR is enough, tr1_cnt0 is not updated
 * For len >= SZ_64K two TRs are used in a simple way:
 * First TR: SZ_64K-alignment blocks (tr0_cnt0, tr0_cnt1)
 * Second TR: the reमुख्यing length (tr1_cnt0)
 *
 * Returns the number of TRs the length needs (1 or 2)
 * -EINVAL अगर the length can not be supported
 */
अटल पूर्णांक udma_get_tr_counters(माप_प्रकार len, अचिन्हित दीर्घ align_to,
				u16 *tr0_cnt0, u16 *tr0_cnt1, u16 *tr1_cnt0)
अणु
	अगर (len < SZ_64K) अणु
		*tr0_cnt0 = len;
		*tr0_cnt1 = 1;

		वापस 1;
	पूर्ण

	अगर (align_to > 3)
		align_to = 3;

realign:
	*tr0_cnt0 = SZ_64K - BIT(align_to);
	अगर (len / *tr0_cnt0 >= SZ_64K) अणु
		अगर (align_to) अणु
			align_to--;
			जाओ realign;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	*tr0_cnt1 = len / *tr0_cnt0;
	*tr1_cnt0 = len % *tr0_cnt0;

	वापस 2;
पूर्ण

अटल काष्ठा udma_desc *
udma_prep_slave_sg_tr(काष्ठा udma_chan *uc, काष्ठा scatterlist *sgl,
		      अचिन्हित पूर्णांक sglen, क्रमागत dma_transfer_direction dir,
		      अचिन्हित दीर्घ tx_flags, व्योम *context)
अणु
	काष्ठा scatterlist *sgent;
	काष्ठा udma_desc *d;
	काष्ठा cppi5_tr_type1_t *tr_req = शून्य;
	u16 tr0_cnt0, tr0_cnt1, tr1_cnt0;
	अचिन्हित पूर्णांक i;
	माप_प्रकार tr_size;
	पूर्णांक num_tr = 0;
	पूर्णांक tr_idx = 0;
	u64 asel;

	/* estimate the number of TRs we will need */
	क्रम_each_sg(sgl, sgent, sglen, i) अणु
		अगर (sg_dma_len(sgent) < SZ_64K)
			num_tr++;
		अन्यथा
			num_tr += 2;
	पूर्ण

	/* Now allocate and setup the descriptor. */
	tr_size = माप(काष्ठा cppi5_tr_type1_t);
	d = udma_alloc_tr_desc(uc, tr_size, num_tr, dir);
	अगर (!d)
		वापस शून्य;

	d->sglen = sglen;

	अगर (uc->ud->match_data->type == DMA_TYPE_UDMA)
		asel = 0;
	अन्यथा
		asel = (u64)uc->config.asel << K3_ADDRESS_ASEL_SHIFT;

	tr_req = d->hwdesc[0].tr_req_base;
	क्रम_each_sg(sgl, sgent, sglen, i) अणु
		dma_addr_t sg_addr = sg_dma_address(sgent);

		num_tr = udma_get_tr_counters(sg_dma_len(sgent), __ffs(sg_addr),
					      &tr0_cnt0, &tr0_cnt1, &tr1_cnt0);
		अगर (num_tr < 0) अणु
			dev_err(uc->ud->dev, "size %u is not supported\n",
				sg_dma_len(sgent));
			udma_मुक्त_hwdesc(uc, d);
			kमुक्त(d);
			वापस शून्य;
		पूर्ण

		cppi5_tr_init(&tr_req[tr_idx].flags, CPPI5_TR_TYPE1, false,
			      false, CPPI5_TR_EVENT_SIZE_COMPLETION, 0);
		cppi5_tr_csf_set(&tr_req[tr_idx].flags, CPPI5_TR_CSF_SUPR_EVT);

		sg_addr |= asel;
		tr_req[tr_idx].addr = sg_addr;
		tr_req[tr_idx].icnt0 = tr0_cnt0;
		tr_req[tr_idx].icnt1 = tr0_cnt1;
		tr_req[tr_idx].dim1 = tr0_cnt0;
		tr_idx++;

		अगर (num_tr == 2) अणु
			cppi5_tr_init(&tr_req[tr_idx].flags, CPPI5_TR_TYPE1,
				      false, false,
				      CPPI5_TR_EVENT_SIZE_COMPLETION, 0);
			cppi5_tr_csf_set(&tr_req[tr_idx].flags,
					 CPPI5_TR_CSF_SUPR_EVT);

			tr_req[tr_idx].addr = sg_addr + tr0_cnt1 * tr0_cnt0;
			tr_req[tr_idx].icnt0 = tr1_cnt0;
			tr_req[tr_idx].icnt1 = 1;
			tr_req[tr_idx].dim1 = tr1_cnt0;
			tr_idx++;
		पूर्ण

		d->residue += sg_dma_len(sgent);
	पूर्ण

	cppi5_tr_csf_set(&tr_req[tr_idx - 1].flags,
			 CPPI5_TR_CSF_SUPR_EVT | CPPI5_TR_CSF_EOP);

	वापस d;
पूर्ण

अटल काष्ठा udma_desc *
udma_prep_slave_sg_triggered_tr(काष्ठा udma_chan *uc, काष्ठा scatterlist *sgl,
				अचिन्हित पूर्णांक sglen,
				क्रमागत dma_transfer_direction dir,
				अचिन्हित दीर्घ tx_flags, व्योम *context)
अणु
	काष्ठा scatterlist *sgent;
	काष्ठा cppi5_tr_type15_t *tr_req = शून्य;
	क्रमागत dma_slave_buswidth dev_width;
	u16 tr_cnt0, tr_cnt1;
	dma_addr_t dev_addr;
	काष्ठा udma_desc *d;
	अचिन्हित पूर्णांक i;
	माप_प्रकार tr_size, sg_len;
	पूर्णांक num_tr = 0;
	पूर्णांक tr_idx = 0;
	u32 burst, trigger_size, port_winकरोw;
	u64 asel;

	अगर (dir == DMA_DEV_TO_MEM) अणु
		dev_addr = uc->cfg.src_addr;
		dev_width = uc->cfg.src_addr_width;
		burst = uc->cfg.src_maxburst;
		port_winकरोw = uc->cfg.src_port_winकरोw_size;
	पूर्ण अन्यथा अगर (dir == DMA_MEM_TO_DEV) अणु
		dev_addr = uc->cfg.dst_addr;
		dev_width = uc->cfg.dst_addr_width;
		burst = uc->cfg.dst_maxburst;
		port_winकरोw = uc->cfg.dst_port_winकरोw_size;
	पूर्ण अन्यथा अणु
		dev_err(uc->ud->dev, "%s: bad direction?\n", __func__);
		वापस शून्य;
	पूर्ण

	अगर (!burst)
		burst = 1;

	अगर (port_winकरोw) अणु
		अगर (port_winकरोw != burst) अणु
			dev_err(uc->ud->dev,
				"The burst must be equal to port_window\n");
			वापस शून्य;
		पूर्ण

		tr_cnt0 = dev_width * port_winकरोw;
		tr_cnt1 = 1;
	पूर्ण अन्यथा अणु
		tr_cnt0 = dev_width;
		tr_cnt1 = burst;
	पूर्ण
	trigger_size = tr_cnt0 * tr_cnt1;

	/* estimate the number of TRs we will need */
	क्रम_each_sg(sgl, sgent, sglen, i) अणु
		sg_len = sg_dma_len(sgent);

		अगर (sg_len % trigger_size) अणु
			dev_err(uc->ud->dev,
				"Not aligned SG entry (%zu for %u)\n", sg_len,
				trigger_size);
			वापस शून्य;
		पूर्ण

		अगर (sg_len / trigger_size < SZ_64K)
			num_tr++;
		अन्यथा
			num_tr += 2;
	पूर्ण

	/* Now allocate and setup the descriptor. */
	tr_size = माप(काष्ठा cppi5_tr_type15_t);
	d = udma_alloc_tr_desc(uc, tr_size, num_tr, dir);
	अगर (!d)
		वापस शून्य;

	d->sglen = sglen;

	अगर (uc->ud->match_data->type == DMA_TYPE_UDMA) अणु
		asel = 0;
	पूर्ण अन्यथा अणु
		asel = (u64)uc->config.asel << K3_ADDRESS_ASEL_SHIFT;
		dev_addr |= asel;
	पूर्ण

	tr_req = d->hwdesc[0].tr_req_base;
	क्रम_each_sg(sgl, sgent, sglen, i) अणु
		u16 tr0_cnt2, tr0_cnt3, tr1_cnt2;
		dma_addr_t sg_addr = sg_dma_address(sgent);

		sg_len = sg_dma_len(sgent);
		num_tr = udma_get_tr_counters(sg_len / trigger_size, 0,
					      &tr0_cnt2, &tr0_cnt3, &tr1_cnt2);
		अगर (num_tr < 0) अणु
			dev_err(uc->ud->dev, "size %zu is not supported\n",
				sg_len);
			udma_मुक्त_hwdesc(uc, d);
			kमुक्त(d);
			वापस शून्य;
		पूर्ण

		cppi5_tr_init(&tr_req[tr_idx].flags, CPPI5_TR_TYPE15, false,
			      true, CPPI5_TR_EVENT_SIZE_COMPLETION, 0);
		cppi5_tr_csf_set(&tr_req[tr_idx].flags, CPPI5_TR_CSF_SUPR_EVT);
		cppi5_tr_set_trigger(&tr_req[tr_idx].flags,
				     uc->config.tr_trigger_type,
				     CPPI5_TR_TRIGGER_TYPE_ICNT2_DEC, 0, 0);

		sg_addr |= asel;
		अगर (dir == DMA_DEV_TO_MEM) अणु
			tr_req[tr_idx].addr = dev_addr;
			tr_req[tr_idx].icnt0 = tr_cnt0;
			tr_req[tr_idx].icnt1 = tr_cnt1;
			tr_req[tr_idx].icnt2 = tr0_cnt2;
			tr_req[tr_idx].icnt3 = tr0_cnt3;
			tr_req[tr_idx].dim1 = (-1) * tr_cnt0;

			tr_req[tr_idx].daddr = sg_addr;
			tr_req[tr_idx].dicnt0 = tr_cnt0;
			tr_req[tr_idx].dicnt1 = tr_cnt1;
			tr_req[tr_idx].dicnt2 = tr0_cnt2;
			tr_req[tr_idx].dicnt3 = tr0_cnt3;
			tr_req[tr_idx].ddim1 = tr_cnt0;
			tr_req[tr_idx].ddim2 = trigger_size;
			tr_req[tr_idx].ddim3 = trigger_size * tr0_cnt2;
		पूर्ण अन्यथा अणु
			tr_req[tr_idx].addr = sg_addr;
			tr_req[tr_idx].icnt0 = tr_cnt0;
			tr_req[tr_idx].icnt1 = tr_cnt1;
			tr_req[tr_idx].icnt2 = tr0_cnt2;
			tr_req[tr_idx].icnt3 = tr0_cnt3;
			tr_req[tr_idx].dim1 = tr_cnt0;
			tr_req[tr_idx].dim2 = trigger_size;
			tr_req[tr_idx].dim3 = trigger_size * tr0_cnt2;

			tr_req[tr_idx].daddr = dev_addr;
			tr_req[tr_idx].dicnt0 = tr_cnt0;
			tr_req[tr_idx].dicnt1 = tr_cnt1;
			tr_req[tr_idx].dicnt2 = tr0_cnt2;
			tr_req[tr_idx].dicnt3 = tr0_cnt3;
			tr_req[tr_idx].ddim1 = (-1) * tr_cnt0;
		पूर्ण

		tr_idx++;

		अगर (num_tr == 2) अणु
			cppi5_tr_init(&tr_req[tr_idx].flags, CPPI5_TR_TYPE15,
				      false, true,
				      CPPI5_TR_EVENT_SIZE_COMPLETION, 0);
			cppi5_tr_csf_set(&tr_req[tr_idx].flags,
					 CPPI5_TR_CSF_SUPR_EVT);
			cppi5_tr_set_trigger(&tr_req[tr_idx].flags,
					     uc->config.tr_trigger_type,
					     CPPI5_TR_TRIGGER_TYPE_ICNT2_DEC,
					     0, 0);

			sg_addr += trigger_size * tr0_cnt2 * tr0_cnt3;
			अगर (dir == DMA_DEV_TO_MEM) अणु
				tr_req[tr_idx].addr = dev_addr;
				tr_req[tr_idx].icnt0 = tr_cnt0;
				tr_req[tr_idx].icnt1 = tr_cnt1;
				tr_req[tr_idx].icnt2 = tr1_cnt2;
				tr_req[tr_idx].icnt3 = 1;
				tr_req[tr_idx].dim1 = (-1) * tr_cnt0;

				tr_req[tr_idx].daddr = sg_addr;
				tr_req[tr_idx].dicnt0 = tr_cnt0;
				tr_req[tr_idx].dicnt1 = tr_cnt1;
				tr_req[tr_idx].dicnt2 = tr1_cnt2;
				tr_req[tr_idx].dicnt3 = 1;
				tr_req[tr_idx].ddim1 = tr_cnt0;
				tr_req[tr_idx].ddim2 = trigger_size;
			पूर्ण अन्यथा अणु
				tr_req[tr_idx].addr = sg_addr;
				tr_req[tr_idx].icnt0 = tr_cnt0;
				tr_req[tr_idx].icnt1 = tr_cnt1;
				tr_req[tr_idx].icnt2 = tr1_cnt2;
				tr_req[tr_idx].icnt3 = 1;
				tr_req[tr_idx].dim1 = tr_cnt0;
				tr_req[tr_idx].dim2 = trigger_size;

				tr_req[tr_idx].daddr = dev_addr;
				tr_req[tr_idx].dicnt0 = tr_cnt0;
				tr_req[tr_idx].dicnt1 = tr_cnt1;
				tr_req[tr_idx].dicnt2 = tr1_cnt2;
				tr_req[tr_idx].dicnt3 = 1;
				tr_req[tr_idx].ddim1 = (-1) * tr_cnt0;
			पूर्ण
			tr_idx++;
		पूर्ण

		d->residue += sg_len;
	पूर्ण

	cppi5_tr_csf_set(&tr_req[tr_idx - 1].flags,
			 CPPI5_TR_CSF_SUPR_EVT | CPPI5_TR_CSF_EOP);

	वापस d;
पूर्ण

अटल पूर्णांक udma_configure_अटलtr(काष्ठा udma_chan *uc, काष्ठा udma_desc *d,
				   क्रमागत dma_slave_buswidth dev_width,
				   u16 elcnt)
अणु
	अगर (uc->config.ep_type != PSIL_EP_PDMA_XY)
		वापस 0;

	/* Bus width translates to the element size (ES) */
	चयन (dev_width) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
		d->अटल_tr.elsize = 0;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		d->अटल_tr.elsize = 1;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_3_BYTES:
		d->अटल_tr.elsize = 2;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		d->अटल_tr.elsize = 3;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_8_BYTES:
		d->अटल_tr.elsize = 4;
		अवरोध;
	शेष: /* not reached */
		वापस -EINVAL;
	पूर्ण

	d->अटल_tr.elcnt = elcnt;

	/*
	 * PDMA must to बंद the packet when the channel is in packet mode.
	 * For TR mode when the channel is not cyclic we also need PDMA to बंद
	 * the packet otherwise the transfer will stall because PDMA holds on
	 * the data it has received from the peripheral.
	 */
	अगर (uc->config.pkt_mode || !uc->cyclic) अणु
		अचिन्हित पूर्णांक भाग = dev_width * elcnt;

		अगर (uc->cyclic)
			d->अटल_tr.bstcnt = d->residue / d->sglen / भाग;
		अन्यथा
			d->अटल_tr.bstcnt = d->residue / भाग;

		अगर (uc->config.dir == DMA_DEV_TO_MEM &&
		    d->अटल_tr.bstcnt > uc->ud->match_data->अटलtr_z_mask)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		d->अटल_tr.bstcnt = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा udma_desc *
udma_prep_slave_sg_pkt(काष्ठा udma_chan *uc, काष्ठा scatterlist *sgl,
		       अचिन्हित पूर्णांक sglen, क्रमागत dma_transfer_direction dir,
		       अचिन्हित दीर्घ tx_flags, व्योम *context)
अणु
	काष्ठा scatterlist *sgent;
	काष्ठा cppi5_host_desc_t *h_desc = शून्य;
	काष्ठा udma_desc *d;
	u32 ring_id;
	अचिन्हित पूर्णांक i;
	u64 asel;

	d = kzalloc(काष्ठा_size(d, hwdesc, sglen), GFP_NOWAIT);
	अगर (!d)
		वापस शून्य;

	d->sglen = sglen;
	d->hwdesc_count = sglen;

	अगर (dir == DMA_DEV_TO_MEM)
		ring_id = k3_ringacc_get_ring_id(uc->rflow->r_ring);
	अन्यथा
		ring_id = k3_ringacc_get_ring_id(uc->tchan->tc_ring);

	अगर (uc->ud->match_data->type == DMA_TYPE_UDMA)
		asel = 0;
	अन्यथा
		asel = (u64)uc->config.asel << K3_ADDRESS_ASEL_SHIFT;

	क्रम_each_sg(sgl, sgent, sglen, i) अणु
		काष्ठा udma_hwdesc *hwdesc = &d->hwdesc[i];
		dma_addr_t sg_addr = sg_dma_address(sgent);
		काष्ठा cppi5_host_desc_t *desc;
		माप_प्रकार sg_len = sg_dma_len(sgent);

		hwdesc->cppi5_desc_vaddr = dma_pool_zalloc(uc->hdesc_pool,
						GFP_NOWAIT,
						&hwdesc->cppi5_desc_paddr);
		अगर (!hwdesc->cppi5_desc_vaddr) अणु
			dev_err(uc->ud->dev,
				"descriptor%d allocation failed\n", i);

			udma_मुक्त_hwdesc(uc, d);
			kमुक्त(d);
			वापस शून्य;
		पूर्ण

		d->residue += sg_len;
		hwdesc->cppi5_desc_size = uc->config.hdesc_size;
		desc = hwdesc->cppi5_desc_vaddr;

		अगर (i == 0) अणु
			cppi5_hdesc_init(desc, 0, 0);
			/* Flow and Packed ID */
			cppi5_desc_set_pktids(&desc->hdr, uc->id,
					      CPPI5_INFO1_DESC_FLOWID_DEFAULT);
			cppi5_desc_set_retpolicy(&desc->hdr, 0, ring_id);
		पूर्ण अन्यथा अणु
			cppi5_hdesc_reset_hbdesc(desc);
			cppi5_desc_set_retpolicy(&desc->hdr, 0, 0xffff);
		पूर्ण

		/* attach the sg buffer to the descriptor */
		sg_addr |= asel;
		cppi5_hdesc_attach_buf(desc, sg_addr, sg_len, sg_addr, sg_len);

		/* Attach link as host buffer descriptor */
		अगर (h_desc)
			cppi5_hdesc_link_hbdesc(h_desc,
						hwdesc->cppi5_desc_paddr | asel);

		अगर (uc->ud->match_data->type == DMA_TYPE_PKTDMA ||
		    dir == DMA_MEM_TO_DEV)
			h_desc = desc;
	पूर्ण

	अगर (d->residue >= SZ_4M) अणु
		dev_err(uc->ud->dev,
			"%s: Transfer size %u is over the supported 4M range\n",
			__func__, d->residue);
		udma_मुक्त_hwdesc(uc, d);
		kमुक्त(d);
		वापस शून्य;
	पूर्ण

	h_desc = d->hwdesc[0].cppi5_desc_vaddr;
	cppi5_hdesc_set_pktlen(h_desc, d->residue);

	वापस d;
पूर्ण

अटल पूर्णांक udma_attach_metadata(काष्ठा dma_async_tx_descriptor *desc,
				व्योम *data, माप_प्रकार len)
अणु
	काष्ठा udma_desc *d = to_udma_desc(desc);
	काष्ठा udma_chan *uc = to_udma_chan(desc->chan);
	काष्ठा cppi5_host_desc_t *h_desc;
	u32 psd_size = len;
	u32 flags = 0;

	अगर (!uc->config.pkt_mode || !uc->config.metadata_size)
		वापस -ENOTSUPP;

	अगर (!data || len > uc->config.metadata_size)
		वापस -EINVAL;

	अगर (uc->config.needs_epib && len < CPPI5_INFO0_HDESC_EPIB_SIZE)
		वापस -EINVAL;

	h_desc = d->hwdesc[0].cppi5_desc_vaddr;
	अगर (d->dir == DMA_MEM_TO_DEV)
		स_नकल(h_desc->epib, data, len);

	अगर (uc->config.needs_epib)
		psd_size -= CPPI5_INFO0_HDESC_EPIB_SIZE;

	d->metadata = data;
	d->metadata_size = len;
	अगर (uc->config.needs_epib)
		flags |= CPPI5_INFO0_HDESC_EPIB_PRESENT;

	cppi5_hdesc_update_flags(h_desc, flags);
	cppi5_hdesc_update_psdata_size(h_desc, psd_size);

	वापस 0;
पूर्ण

अटल व्योम *udma_get_metadata_ptr(काष्ठा dma_async_tx_descriptor *desc,
				   माप_प्रकार *payload_len, माप_प्रकार *max_len)
अणु
	काष्ठा udma_desc *d = to_udma_desc(desc);
	काष्ठा udma_chan *uc = to_udma_chan(desc->chan);
	काष्ठा cppi5_host_desc_t *h_desc;

	अगर (!uc->config.pkt_mode || !uc->config.metadata_size)
		वापस ERR_PTR(-ENOTSUPP);

	h_desc = d->hwdesc[0].cppi5_desc_vaddr;

	*max_len = uc->config.metadata_size;

	*payload_len = cppi5_hdesc_epib_present(&h_desc->hdr) ?
		       CPPI5_INFO0_HDESC_EPIB_SIZE : 0;
	*payload_len += cppi5_hdesc_get_psdata_size(h_desc);

	वापस h_desc->epib;
पूर्ण

अटल पूर्णांक udma_set_metadata_len(काष्ठा dma_async_tx_descriptor *desc,
				 माप_प्रकार payload_len)
अणु
	काष्ठा udma_desc *d = to_udma_desc(desc);
	काष्ठा udma_chan *uc = to_udma_chan(desc->chan);
	काष्ठा cppi5_host_desc_t *h_desc;
	u32 psd_size = payload_len;
	u32 flags = 0;

	अगर (!uc->config.pkt_mode || !uc->config.metadata_size)
		वापस -ENOTSUPP;

	अगर (payload_len > uc->config.metadata_size)
		वापस -EINVAL;

	अगर (uc->config.needs_epib && payload_len < CPPI5_INFO0_HDESC_EPIB_SIZE)
		वापस -EINVAL;

	h_desc = d->hwdesc[0].cppi5_desc_vaddr;

	अगर (uc->config.needs_epib) अणु
		psd_size -= CPPI5_INFO0_HDESC_EPIB_SIZE;
		flags |= CPPI5_INFO0_HDESC_EPIB_PRESENT;
	पूर्ण

	cppi5_hdesc_update_flags(h_desc, flags);
	cppi5_hdesc_update_psdata_size(h_desc, psd_size);

	वापस 0;
पूर्ण

अटल काष्ठा dma_descriptor_metadata_ops metadata_ops = अणु
	.attach = udma_attach_metadata,
	.get_ptr = udma_get_metadata_ptr,
	.set_len = udma_set_metadata_len,
पूर्ण;

अटल काष्ठा dma_async_tx_descriptor *
udma_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		   अचिन्हित पूर्णांक sglen, क्रमागत dma_transfer_direction dir,
		   अचिन्हित दीर्घ tx_flags, व्योम *context)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);
	क्रमागत dma_slave_buswidth dev_width;
	काष्ठा udma_desc *d;
	u32 burst;

	अगर (dir != uc->config.dir &&
	    (uc->config.dir == DMA_MEM_TO_MEM && !uc->config.tr_trigger_type)) अणु
		dev_err(chan->device->dev,
			"%s: chan%d is for %s, not supporting %s\n",
			__func__, uc->id,
			dmaengine_get_direction_text(uc->config.dir),
			dmaengine_get_direction_text(dir));
		वापस शून्य;
	पूर्ण

	अगर (dir == DMA_DEV_TO_MEM) अणु
		dev_width = uc->cfg.src_addr_width;
		burst = uc->cfg.src_maxburst;
	पूर्ण अन्यथा अगर (dir == DMA_MEM_TO_DEV) अणु
		dev_width = uc->cfg.dst_addr_width;
		burst = uc->cfg.dst_maxburst;
	पूर्ण अन्यथा अणु
		dev_err(chan->device->dev, "%s: bad direction?\n", __func__);
		वापस शून्य;
	पूर्ण

	अगर (!burst)
		burst = 1;

	अगर (uc->config.pkt_mode)
		d = udma_prep_slave_sg_pkt(uc, sgl, sglen, dir, tx_flags,
					   context);
	अन्यथा अगर (is_slave_direction(uc->config.dir))
		d = udma_prep_slave_sg_tr(uc, sgl, sglen, dir, tx_flags,
					  context);
	अन्यथा
		d = udma_prep_slave_sg_triggered_tr(uc, sgl, sglen, dir,
						    tx_flags, context);

	अगर (!d)
		वापस शून्य;

	d->dir = dir;
	d->desc_idx = 0;
	d->tr_idx = 0;

	/* अटल TR क्रम remote PDMA */
	अगर (udma_configure_अटलtr(uc, d, dev_width, burst)) अणु
		dev_err(uc->ud->dev,
			"%s: StaticTR Z is limited to maximum 4095 (%u)\n",
			__func__, d->अटल_tr.bstcnt);

		udma_मुक्त_hwdesc(uc, d);
		kमुक्त(d);
		वापस शून्य;
	पूर्ण

	अगर (uc->config.metadata_size)
		d->vd.tx.metadata_ops = &metadata_ops;

	वापस vchan_tx_prep(&uc->vc, &d->vd, tx_flags);
पूर्ण

अटल काष्ठा udma_desc *
udma_prep_dma_cyclic_tr(काष्ठा udma_chan *uc, dma_addr_t buf_addr,
			माप_प्रकार buf_len, माप_प्रकार period_len,
			क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags)
अणु
	काष्ठा udma_desc *d;
	माप_प्रकार tr_size, period_addr;
	काष्ठा cppi5_tr_type1_t *tr_req;
	अचिन्हित पूर्णांक periods = buf_len / period_len;
	u16 tr0_cnt0, tr0_cnt1, tr1_cnt0;
	अचिन्हित पूर्णांक i;
	पूर्णांक num_tr;

	num_tr = udma_get_tr_counters(period_len, __ffs(buf_addr), &tr0_cnt0,
				      &tr0_cnt1, &tr1_cnt0);
	अगर (num_tr < 0) अणु
		dev_err(uc->ud->dev, "size %zu is not supported\n",
			period_len);
		वापस शून्य;
	पूर्ण

	/* Now allocate and setup the descriptor. */
	tr_size = माप(काष्ठा cppi5_tr_type1_t);
	d = udma_alloc_tr_desc(uc, tr_size, periods * num_tr, dir);
	अगर (!d)
		वापस शून्य;

	tr_req = d->hwdesc[0].tr_req_base;
	अगर (uc->ud->match_data->type == DMA_TYPE_UDMA)
		period_addr = buf_addr;
	अन्यथा
		period_addr = buf_addr |
			((u64)uc->config.asel << K3_ADDRESS_ASEL_SHIFT);

	क्रम (i = 0; i < periods; i++) अणु
		पूर्णांक tr_idx = i * num_tr;

		cppi5_tr_init(&tr_req[tr_idx].flags, CPPI5_TR_TYPE1, false,
			      false, CPPI5_TR_EVENT_SIZE_COMPLETION, 0);

		tr_req[tr_idx].addr = period_addr;
		tr_req[tr_idx].icnt0 = tr0_cnt0;
		tr_req[tr_idx].icnt1 = tr0_cnt1;
		tr_req[tr_idx].dim1 = tr0_cnt0;

		अगर (num_tr == 2) अणु
			cppi5_tr_csf_set(&tr_req[tr_idx].flags,
					 CPPI5_TR_CSF_SUPR_EVT);
			tr_idx++;

			cppi5_tr_init(&tr_req[tr_idx].flags, CPPI5_TR_TYPE1,
				      false, false,
				      CPPI5_TR_EVENT_SIZE_COMPLETION, 0);

			tr_req[tr_idx].addr = period_addr + tr0_cnt1 * tr0_cnt0;
			tr_req[tr_idx].icnt0 = tr1_cnt0;
			tr_req[tr_idx].icnt1 = 1;
			tr_req[tr_idx].dim1 = tr1_cnt0;
		पूर्ण

		अगर (!(flags & DMA_PREP_INTERRUPT))
			cppi5_tr_csf_set(&tr_req[tr_idx].flags,
					 CPPI5_TR_CSF_SUPR_EVT);

		period_addr += period_len;
	पूर्ण

	वापस d;
पूर्ण

अटल काष्ठा udma_desc *
udma_prep_dma_cyclic_pkt(काष्ठा udma_chan *uc, dma_addr_t buf_addr,
			 माप_प्रकार buf_len, माप_प्रकार period_len,
			 क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags)
अणु
	काष्ठा udma_desc *d;
	u32 ring_id;
	पूर्णांक i;
	पूर्णांक periods = buf_len / period_len;

	अगर (periods > (K3_UDMA_DEFAULT_RING_SIZE - 1))
		वापस शून्य;

	अगर (period_len >= SZ_4M)
		वापस शून्य;

	d = kzalloc(काष्ठा_size(d, hwdesc, periods), GFP_NOWAIT);
	अगर (!d)
		वापस शून्य;

	d->hwdesc_count = periods;

	/* TODO: re-check this... */
	अगर (dir == DMA_DEV_TO_MEM)
		ring_id = k3_ringacc_get_ring_id(uc->rflow->r_ring);
	अन्यथा
		ring_id = k3_ringacc_get_ring_id(uc->tchan->tc_ring);

	अगर (uc->ud->match_data->type != DMA_TYPE_UDMA)
		buf_addr |= (u64)uc->config.asel << K3_ADDRESS_ASEL_SHIFT;

	क्रम (i = 0; i < periods; i++) अणु
		काष्ठा udma_hwdesc *hwdesc = &d->hwdesc[i];
		dma_addr_t period_addr = buf_addr + (period_len * i);
		काष्ठा cppi5_host_desc_t *h_desc;

		hwdesc->cppi5_desc_vaddr = dma_pool_zalloc(uc->hdesc_pool,
						GFP_NOWAIT,
						&hwdesc->cppi5_desc_paddr);
		अगर (!hwdesc->cppi5_desc_vaddr) अणु
			dev_err(uc->ud->dev,
				"descriptor%d allocation failed\n", i);

			udma_मुक्त_hwdesc(uc, d);
			kमुक्त(d);
			वापस शून्य;
		पूर्ण

		hwdesc->cppi5_desc_size = uc->config.hdesc_size;
		h_desc = hwdesc->cppi5_desc_vaddr;

		cppi5_hdesc_init(h_desc, 0, 0);
		cppi5_hdesc_set_pktlen(h_desc, period_len);

		/* Flow and Packed ID */
		cppi5_desc_set_pktids(&h_desc->hdr, uc->id,
				      CPPI5_INFO1_DESC_FLOWID_DEFAULT);
		cppi5_desc_set_retpolicy(&h_desc->hdr, 0, ring_id);

		/* attach each period to a new descriptor */
		cppi5_hdesc_attach_buf(h_desc,
				       period_addr, period_len,
				       period_addr, period_len);
	पूर्ण

	वापस d;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
udma_prep_dma_cyclic(काष्ठा dma_chan *chan, dma_addr_t buf_addr, माप_प्रकार buf_len,
		     माप_प्रकार period_len, क्रमागत dma_transfer_direction dir,
		     अचिन्हित दीर्घ flags)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);
	क्रमागत dma_slave_buswidth dev_width;
	काष्ठा udma_desc *d;
	u32 burst;

	अगर (dir != uc->config.dir) अणु
		dev_err(chan->device->dev,
			"%s: chan%d is for %s, not supporting %s\n",
			__func__, uc->id,
			dmaengine_get_direction_text(uc->config.dir),
			dmaengine_get_direction_text(dir));
		वापस शून्य;
	पूर्ण

	uc->cyclic = true;

	अगर (dir == DMA_DEV_TO_MEM) अणु
		dev_width = uc->cfg.src_addr_width;
		burst = uc->cfg.src_maxburst;
	पूर्ण अन्यथा अगर (dir == DMA_MEM_TO_DEV) अणु
		dev_width = uc->cfg.dst_addr_width;
		burst = uc->cfg.dst_maxburst;
	पूर्ण अन्यथा अणु
		dev_err(uc->ud->dev, "%s: bad direction?\n", __func__);
		वापस शून्य;
	पूर्ण

	अगर (!burst)
		burst = 1;

	अगर (uc->config.pkt_mode)
		d = udma_prep_dma_cyclic_pkt(uc, buf_addr, buf_len, period_len,
					     dir, flags);
	अन्यथा
		d = udma_prep_dma_cyclic_tr(uc, buf_addr, buf_len, period_len,
					    dir, flags);

	अगर (!d)
		वापस शून्य;

	d->sglen = buf_len / period_len;

	d->dir = dir;
	d->residue = buf_len;

	/* अटल TR क्रम remote PDMA */
	अगर (udma_configure_अटलtr(uc, d, dev_width, burst)) अणु
		dev_err(uc->ud->dev,
			"%s: StaticTR Z is limited to maximum 4095 (%u)\n",
			__func__, d->अटल_tr.bstcnt);

		udma_मुक्त_hwdesc(uc, d);
		kमुक्त(d);
		वापस शून्य;
	पूर्ण

	अगर (uc->config.metadata_size)
		d->vd.tx.metadata_ops = &metadata_ops;

	वापस vchan_tx_prep(&uc->vc, &d->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
udma_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
		     माप_प्रकार len, अचिन्हित दीर्घ tx_flags)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);
	काष्ठा udma_desc *d;
	काष्ठा cppi5_tr_type15_t *tr_req;
	पूर्णांक num_tr;
	माप_प्रकार tr_size = माप(काष्ठा cppi5_tr_type15_t);
	u16 tr0_cnt0, tr0_cnt1, tr1_cnt0;

	अगर (uc->config.dir != DMA_MEM_TO_MEM) अणु
		dev_err(chan->device->dev,
			"%s: chan%d is for %s, not supporting %s\n",
			__func__, uc->id,
			dmaengine_get_direction_text(uc->config.dir),
			dmaengine_get_direction_text(DMA_MEM_TO_MEM));
		वापस शून्य;
	पूर्ण

	num_tr = udma_get_tr_counters(len, __ffs(src | dest), &tr0_cnt0,
				      &tr0_cnt1, &tr1_cnt0);
	अगर (num_tr < 0) अणु
		dev_err(uc->ud->dev, "size %zu is not supported\n",
			len);
		वापस शून्य;
	पूर्ण

	d = udma_alloc_tr_desc(uc, tr_size, num_tr, DMA_MEM_TO_MEM);
	अगर (!d)
		वापस शून्य;

	d->dir = DMA_MEM_TO_MEM;
	d->desc_idx = 0;
	d->tr_idx = 0;
	d->residue = len;

	अगर (uc->ud->match_data->type != DMA_TYPE_UDMA) अणु
		src |= (u64)uc->ud->asel << K3_ADDRESS_ASEL_SHIFT;
		dest |= (u64)uc->ud->asel << K3_ADDRESS_ASEL_SHIFT;
	पूर्ण

	tr_req = d->hwdesc[0].tr_req_base;

	cppi5_tr_init(&tr_req[0].flags, CPPI5_TR_TYPE15, false, true,
		      CPPI5_TR_EVENT_SIZE_COMPLETION, 0);
	cppi5_tr_csf_set(&tr_req[0].flags, CPPI5_TR_CSF_SUPR_EVT);

	tr_req[0].addr = src;
	tr_req[0].icnt0 = tr0_cnt0;
	tr_req[0].icnt1 = tr0_cnt1;
	tr_req[0].icnt2 = 1;
	tr_req[0].icnt3 = 1;
	tr_req[0].dim1 = tr0_cnt0;

	tr_req[0].daddr = dest;
	tr_req[0].dicnt0 = tr0_cnt0;
	tr_req[0].dicnt1 = tr0_cnt1;
	tr_req[0].dicnt2 = 1;
	tr_req[0].dicnt3 = 1;
	tr_req[0].ddim1 = tr0_cnt0;

	अगर (num_tr == 2) अणु
		cppi5_tr_init(&tr_req[1].flags, CPPI5_TR_TYPE15, false, true,
			      CPPI5_TR_EVENT_SIZE_COMPLETION, 0);
		cppi5_tr_csf_set(&tr_req[1].flags, CPPI5_TR_CSF_SUPR_EVT);

		tr_req[1].addr = src + tr0_cnt1 * tr0_cnt0;
		tr_req[1].icnt0 = tr1_cnt0;
		tr_req[1].icnt1 = 1;
		tr_req[1].icnt2 = 1;
		tr_req[1].icnt3 = 1;

		tr_req[1].daddr = dest + tr0_cnt1 * tr0_cnt0;
		tr_req[1].dicnt0 = tr1_cnt0;
		tr_req[1].dicnt1 = 1;
		tr_req[1].dicnt2 = 1;
		tr_req[1].dicnt3 = 1;
	पूर्ण

	cppi5_tr_csf_set(&tr_req[num_tr - 1].flags,
			 CPPI5_TR_CSF_SUPR_EVT | CPPI5_TR_CSF_EOP);

	अगर (uc->config.metadata_size)
		d->vd.tx.metadata_ops = &metadata_ops;

	वापस vchan_tx_prep(&uc->vc, &d->vd, tx_flags);
पूर्ण

अटल व्योम udma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&uc->vc.lock, flags);

	/* If we have something pending and no active descriptor, then */
	अगर (vchan_issue_pending(&uc->vc) && !uc->desc) अणु
		/*
		 * start a descriptor अगर the channel is NOT [marked as
		 * terminating _and_ it is still running (tearकरोwn has not
		 * completed yet)].
		 */
		अगर (!(uc->state == UDMA_CHAN_IS_TERMINATING &&
		      udma_is_chan_running(uc)))
			udma_start(uc);
	पूर्ण

	spin_unlock_irqrestore(&uc->vc.lock, flags);
पूर्ण

अटल क्रमागत dma_status udma_tx_status(काष्ठा dma_chan *chan,
				      dma_cookie_t cookie,
				      काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&uc->vc.lock, flags);

	ret = dma_cookie_status(chan, cookie, txstate);

	अगर (!udma_is_chan_running(uc))
		ret = DMA_COMPLETE;

	अगर (ret == DMA_IN_PROGRESS && udma_is_chan_छोड़ोd(uc))
		ret = DMA_PAUSED;

	अगर (ret == DMA_COMPLETE || !txstate)
		जाओ out;

	अगर (uc->desc && uc->desc->vd.tx.cookie == cookie) अणु
		u32 peer_bcnt = 0;
		u32 bcnt = 0;
		u32 residue = uc->desc->residue;
		u32 delay = 0;

		अगर (uc->desc->dir == DMA_MEM_TO_DEV) अणु
			bcnt = udma_tchanrt_पढ़ो(uc, UDMA_CHAN_RT_SBCNT_REG);

			अगर (uc->config.ep_type != PSIL_EP_NATIVE) अणु
				peer_bcnt = udma_tchanrt_पढ़ो(uc,
						UDMA_CHAN_RT_PEER_BCNT_REG);

				अगर (bcnt > peer_bcnt)
					delay = bcnt - peer_bcnt;
			पूर्ण
		पूर्ण अन्यथा अगर (uc->desc->dir == DMA_DEV_TO_MEM) अणु
			bcnt = udma_rchanrt_पढ़ो(uc, UDMA_CHAN_RT_BCNT_REG);

			अगर (uc->config.ep_type != PSIL_EP_NATIVE) अणु
				peer_bcnt = udma_rchanrt_पढ़ो(uc,
						UDMA_CHAN_RT_PEER_BCNT_REG);

				अगर (peer_bcnt > bcnt)
					delay = peer_bcnt - bcnt;
			पूर्ण
		पूर्ण अन्यथा अणु
			bcnt = udma_tchanrt_पढ़ो(uc, UDMA_CHAN_RT_BCNT_REG);
		पूर्ण

		bcnt -= uc->bcnt;
		अगर (bcnt && !(bcnt % uc->desc->residue))
			residue = 0;
		अन्यथा
			residue -= bcnt % uc->desc->residue;

		अगर (!residue && (uc->config.dir == DMA_DEV_TO_MEM || !delay)) अणु
			ret = DMA_COMPLETE;
			delay = 0;
		पूर्ण

		dma_set_residue(txstate, residue);
		dma_set_in_flight_bytes(txstate, delay);

	पूर्ण अन्यथा अणु
		ret = DMA_COMPLETE;
	पूर्ण

out:
	spin_unlock_irqrestore(&uc->vc.lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक udma_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);

	/* छोड़ो the channel */
	चयन (uc->config.dir) अणु
	हाल DMA_DEV_TO_MEM:
		udma_rchanrt_update_bits(uc, UDMA_CHAN_RT_PEER_RT_EN_REG,
					 UDMA_PEER_RT_EN_PAUSE,
					 UDMA_PEER_RT_EN_PAUSE);
		अवरोध;
	हाल DMA_MEM_TO_DEV:
		udma_tchanrt_update_bits(uc, UDMA_CHAN_RT_PEER_RT_EN_REG,
					 UDMA_PEER_RT_EN_PAUSE,
					 UDMA_PEER_RT_EN_PAUSE);
		अवरोध;
	हाल DMA_MEM_TO_MEM:
		udma_tchanrt_update_bits(uc, UDMA_CHAN_RT_CTL_REG,
					 UDMA_CHAN_RT_CTL_PAUSE,
					 UDMA_CHAN_RT_CTL_PAUSE);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक udma_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);

	/* resume the channel */
	चयन (uc->config.dir) अणु
	हाल DMA_DEV_TO_MEM:
		udma_rchanrt_update_bits(uc, UDMA_CHAN_RT_PEER_RT_EN_REG,
					 UDMA_PEER_RT_EN_PAUSE, 0);

		अवरोध;
	हाल DMA_MEM_TO_DEV:
		udma_tchanrt_update_bits(uc, UDMA_CHAN_RT_PEER_RT_EN_REG,
					 UDMA_PEER_RT_EN_PAUSE, 0);
		अवरोध;
	हाल DMA_MEM_TO_MEM:
		udma_tchanrt_update_bits(uc, UDMA_CHAN_RT_CTL_REG,
					 UDMA_CHAN_RT_CTL_PAUSE, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक udma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&uc->vc.lock, flags);

	अगर (udma_is_chan_running(uc))
		udma_stop(uc);

	अगर (uc->desc) अणु
		uc->terminated_desc = uc->desc;
		uc->desc = शून्य;
		uc->terminated_desc->terminated = true;
		cancel_delayed_work(&uc->tx_drain.work);
	पूर्ण

	uc->छोड़ोd = false;

	vchan_get_all_descriptors(&uc->vc, &head);
	spin_unlock_irqrestore(&uc->vc.lock, flags);
	vchan_dma_desc_मुक्त_list(&uc->vc, &head);

	वापस 0;
पूर्ण

अटल व्योम udma_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(1000);

	vchan_synchronize(&uc->vc);

	अगर (uc->state == UDMA_CHAN_IS_TERMINATING) अणु
		समयout = रुको_क्रम_completion_समयout(&uc->tearकरोwn_completed,
						      समयout);
		अगर (!समयout) अणु
			dev_warn(uc->ud->dev, "chan%d teardown timeout!\n",
				 uc->id);
			udma_dump_chan_stdata(uc);
			udma_reset_chan(uc, true);
		पूर्ण
	पूर्ण

	udma_reset_chan(uc, false);
	अगर (udma_is_chan_running(uc))
		dev_warn(uc->ud->dev, "chan%d refused to stop!\n", uc->id);

	cancel_delayed_work_sync(&uc->tx_drain.work);
	udma_reset_rings(uc);
पूर्ण

अटल व्योम udma_desc_pre_callback(काष्ठा virt_dma_chan *vc,
				   काष्ठा virt_dma_desc *vd,
				   काष्ठा dmaengine_result *result)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(&vc->chan);
	काष्ठा udma_desc *d;

	अगर (!vd)
		वापस;

	d = to_udma_desc(&vd->tx);

	अगर (d->metadata_size)
		udma_fetch_epib(uc, d);

	/* Provide residue inक्रमmation क्रम the client */
	अगर (result) अणु
		व्योम *desc_vaddr = udma_curr_cppi5_desc_vaddr(d, d->desc_idx);

		अगर (cppi5_desc_get_type(desc_vaddr) ==
		    CPPI5_INFO0_DESC_TYPE_VAL_HOST) अणु
			result->residue = d->residue -
					  cppi5_hdesc_get_pktlen(desc_vaddr);
			अगर (result->residue)
				result->result = DMA_TRANS_ABORTED;
			अन्यथा
				result->result = DMA_TRANS_NOERROR;
		पूर्ण अन्यथा अणु
			result->residue = 0;
			result->result = DMA_TRANS_NOERROR;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This tasklet handles the completion of a DMA descriptor by
 * calling its callback and मुक्तing it.
 */
अटल व्योम udma_vchan_complete(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा virt_dma_chan *vc = from_tasklet(vc, t, task);
	काष्ठा virt_dma_desc *vd, *_vd;
	काष्ठा dmaengine_desc_callback cb;
	LIST_HEAD(head);

	spin_lock_irq(&vc->lock);
	list_splice_tail_init(&vc->desc_completed, &head);
	vd = vc->cyclic;
	अगर (vd) अणु
		vc->cyclic = शून्य;
		dmaengine_desc_get_callback(&vd->tx, &cb);
	पूर्ण अन्यथा अणु
		स_रखो(&cb, 0, माप(cb));
	पूर्ण
	spin_unlock_irq(&vc->lock);

	udma_desc_pre_callback(vc, vd, शून्य);
	dmaengine_desc_callback_invoke(&cb, शून्य);

	list_क्रम_each_entry_safe(vd, _vd, &head, node) अणु
		काष्ठा dmaengine_result result;

		dmaengine_desc_get_callback(&vd->tx, &cb);

		list_del(&vd->node);

		udma_desc_pre_callback(vc, vd, &result);
		dmaengine_desc_callback_invoke(&cb, &result);

		vchan_vdesc_fini(vd);
	पूर्ण
पूर्ण

अटल व्योम udma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);
	काष्ठा udma_dev *ud = to_udma_dev(chan->device);

	udma_terminate_all(chan);
	अगर (uc->terminated_desc) अणु
		udma_reset_chan(uc, false);
		udma_reset_rings(uc);
	पूर्ण

	cancel_delayed_work_sync(&uc->tx_drain.work);

	अगर (uc->irq_num_ring > 0) अणु
		मुक्त_irq(uc->irq_num_ring, uc);

		uc->irq_num_ring = 0;
	पूर्ण
	अगर (uc->irq_num_udma > 0) अणु
		मुक्त_irq(uc->irq_num_udma, uc);

		uc->irq_num_udma = 0;
	पूर्ण

	/* Release PSI-L pairing */
	अगर (uc->psil_paired) अणु
		navss_psil_unpair(ud, uc->config.src_thपढ़ो,
				  uc->config.dst_thपढ़ो);
		uc->psil_paired = false;
	पूर्ण

	vchan_मुक्त_chan_resources(&uc->vc);
	tasklet_समाप्त(&uc->vc.task);

	bcdma_मुक्त_bchan_resources(uc);
	udma_मुक्त_tx_resources(uc);
	udma_मुक्त_rx_resources(uc);
	udma_reset_uchan(uc);

	अगर (uc->use_dma_pool) अणु
		dma_pool_destroy(uc->hdesc_pool);
		uc->use_dma_pool = false;
	पूर्ण
पूर्ण

अटल काष्ठा platक्रमm_driver udma_driver;
अटल काष्ठा platक्रमm_driver bcdma_driver;
अटल काष्ठा platक्रमm_driver pktdma_driver;

काष्ठा udma_filter_param अणु
	पूर्णांक remote_thपढ़ो_id;
	u32 atype;
	u32 asel;
	u32 tr_trigger_type;
पूर्ण;

अटल bool udma_dma_filter_fn(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा udma_chan_config *ucc;
	काष्ठा psil_endpoपूर्णांक_config *ep_config;
	काष्ठा udma_filter_param *filter_param;
	काष्ठा udma_chan *uc;
	काष्ठा udma_dev *ud;

	अगर (chan->device->dev->driver != &udma_driver.driver &&
	    chan->device->dev->driver != &bcdma_driver.driver &&
	    chan->device->dev->driver != &pktdma_driver.driver)
		वापस false;

	uc = to_udma_chan(chan);
	ucc = &uc->config;
	ud = uc->ud;
	filter_param = param;

	अगर (filter_param->atype > 2) अणु
		dev_err(ud->dev, "Invalid channel atype: %u\n",
			filter_param->atype);
		वापस false;
	पूर्ण

	अगर (filter_param->asel > 15) अणु
		dev_err(ud->dev, "Invalid channel asel: %u\n",
			filter_param->asel);
		वापस false;
	पूर्ण

	ucc->remote_thपढ़ो_id = filter_param->remote_thपढ़ो_id;
	ucc->atype = filter_param->atype;
	ucc->asel = filter_param->asel;
	ucc->tr_trigger_type = filter_param->tr_trigger_type;

	अगर (ucc->tr_trigger_type) अणु
		ucc->dir = DMA_MEM_TO_MEM;
		जाओ triggered_bchan;
	पूर्ण अन्यथा अगर (ucc->remote_thपढ़ो_id & K3_PSIL_DST_THREAD_ID_OFFSET) अणु
		ucc->dir = DMA_MEM_TO_DEV;
	पूर्ण अन्यथा अणु
		ucc->dir = DMA_DEV_TO_MEM;
	पूर्ण

	ep_config = psil_get_ep_config(ucc->remote_thपढ़ो_id);
	अगर (IS_ERR(ep_config)) अणु
		dev_err(ud->dev, "No configuration for psi-l thread 0x%04x\n",
			ucc->remote_thपढ़ो_id);
		ucc->dir = DMA_MEM_TO_MEM;
		ucc->remote_thपढ़ो_id = -1;
		ucc->atype = 0;
		ucc->asel = 0;
		वापस false;
	पूर्ण

	अगर (ud->match_data->type == DMA_TYPE_BCDMA &&
	    ep_config->pkt_mode) अणु
		dev_err(ud->dev,
			"Only TR mode is supported (psi-l thread 0x%04x)\n",
			ucc->remote_thपढ़ो_id);
		ucc->dir = DMA_MEM_TO_MEM;
		ucc->remote_thपढ़ो_id = -1;
		ucc->atype = 0;
		ucc->asel = 0;
		वापस false;
	पूर्ण

	ucc->pkt_mode = ep_config->pkt_mode;
	ucc->channel_tpl = ep_config->channel_tpl;
	ucc->notdpkt = ep_config->notdpkt;
	ucc->ep_type = ep_config->ep_type;

	अगर (ud->match_data->type == DMA_TYPE_PKTDMA &&
	    ep_config->mapped_channel_id >= 0) अणु
		ucc->mapped_channel_id = ep_config->mapped_channel_id;
		ucc->शेष_flow_id = ep_config->शेष_flow_id;
	पूर्ण अन्यथा अणु
		ucc->mapped_channel_id = -1;
		ucc->शेष_flow_id = -1;
	पूर्ण

	अगर (ucc->ep_type != PSIL_EP_NATIVE) अणु
		स्थिर काष्ठा udma_match_data *match_data = ud->match_data;

		अगर (match_data->flags & UDMA_FLAG_PDMA_ACC32)
			ucc->enable_acc32 = ep_config->pdma_acc32;
		अगर (match_data->flags & UDMA_FLAG_PDMA_BURST)
			ucc->enable_burst = ep_config->pdma_burst;
	पूर्ण

	ucc->needs_epib = ep_config->needs_epib;
	ucc->psd_size = ep_config->psd_size;
	ucc->metadata_size =
			(ucc->needs_epib ? CPPI5_INFO0_HDESC_EPIB_SIZE : 0) +
			ucc->psd_size;

	अगर (ucc->pkt_mode)
		ucc->hdesc_size = ALIGN(माप(काष्ठा cppi5_host_desc_t) +
				 ucc->metadata_size, ud->desc_align);

	dev_dbg(ud->dev, "chan%d: Remote thread: 0x%04x (%s)\n", uc->id,
		ucc->remote_thपढ़ो_id, dmaengine_get_direction_text(ucc->dir));

	वापस true;

triggered_bchan:
	dev_dbg(ud->dev, "chan%d: triggered channel (type: %u)\n", uc->id,
		ucc->tr_trigger_type);

	वापस true;

पूर्ण

अटल काष्ठा dma_chan *udma_of_xlate(काष्ठा of_phandle_args *dma_spec,
				      काष्ठा of_dma *ofdma)
अणु
	काष्ठा udma_dev *ud = ofdma->of_dma_data;
	dma_cap_mask_t mask = ud->ddev.cap_mask;
	काष्ठा udma_filter_param filter_param;
	काष्ठा dma_chan *chan;

	अगर (ud->match_data->type == DMA_TYPE_BCDMA) अणु
		अगर (dma_spec->args_count != 3)
			वापस शून्य;

		filter_param.tr_trigger_type = dma_spec->args[0];
		filter_param.remote_thपढ़ो_id = dma_spec->args[1];
		filter_param.asel = dma_spec->args[2];
		filter_param.atype = 0;
	पूर्ण अन्यथा अणु
		अगर (dma_spec->args_count != 1 && dma_spec->args_count != 2)
			वापस शून्य;

		filter_param.remote_thपढ़ो_id = dma_spec->args[0];
		filter_param.tr_trigger_type = 0;
		अगर (dma_spec->args_count == 2) अणु
			अगर (ud->match_data->type == DMA_TYPE_UDMA) अणु
				filter_param.atype = dma_spec->args[1];
				filter_param.asel = 0;
			पूर्ण अन्यथा अणु
				filter_param.atype = 0;
				filter_param.asel = dma_spec->args[1];
			पूर्ण
		पूर्ण अन्यथा अणु
			filter_param.atype = 0;
			filter_param.asel = 0;
		पूर्ण
	पूर्ण

	chan = __dma_request_channel(&mask, udma_dma_filter_fn, &filter_param,
				     ofdma->of_node);
	अगर (!chan) अणु
		dev_err(ud->dev, "get channel fail in %s.\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस chan;
पूर्ण

अटल काष्ठा udma_match_data am654_मुख्य_data = अणु
	.type = DMA_TYPE_UDMA,
	.psil_base = 0x1000,
	.enable_स_नकल_support = true,
	.अटलtr_z_mask = GENMASK(11, 0),
	.burst_size = अणु
		TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_64_BYTES, /* Normal Channels */
		TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_64_BYTES, /* H Channels */
		0, /* No UH Channels */
	पूर्ण,
पूर्ण;

अटल काष्ठा udma_match_data am654_mcu_data = अणु
	.type = DMA_TYPE_UDMA,
	.psil_base = 0x6000,
	.enable_स_नकल_support = false,
	.अटलtr_z_mask = GENMASK(11, 0),
	.burst_size = अणु
		TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_64_BYTES, /* Normal Channels */
		TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_64_BYTES, /* H Channels */
		0, /* No UH Channels */
	पूर्ण,
पूर्ण;

अटल काष्ठा udma_match_data j721e_मुख्य_data = अणु
	.type = DMA_TYPE_UDMA,
	.psil_base = 0x1000,
	.enable_स_नकल_support = true,
	.flags = UDMA_FLAGS_J7_CLASS,
	.अटलtr_z_mask = GENMASK(23, 0),
	.burst_size = अणु
		TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_64_BYTES, /* Normal Channels */
		TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_256_BYTES, /* H Channels */
		TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_256_BYTES, /* UH Channels */
	पूर्ण,
पूर्ण;

अटल काष्ठा udma_match_data j721e_mcu_data = अणु
	.type = DMA_TYPE_UDMA,
	.psil_base = 0x6000,
	.enable_स_नकल_support = false, /* MEM_TO_MEM is slow via MCU UDMA */
	.flags = UDMA_FLAGS_J7_CLASS,
	.अटलtr_z_mask = GENMASK(23, 0),
	.burst_size = अणु
		TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_64_BYTES, /* Normal Channels */
		TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_128_BYTES, /* H Channels */
		0, /* No UH Channels */
	पूर्ण,
पूर्ण;

अटल काष्ठा udma_match_data am64_bcdma_data = अणु
	.type = DMA_TYPE_BCDMA,
	.psil_base = 0x2000, /* क्रम tchan and rchan, not applicable to bchan */
	.enable_स_नकल_support = true, /* Supported via bchan */
	.flags = UDMA_FLAGS_J7_CLASS,
	.अटलtr_z_mask = GENMASK(23, 0),
	.burst_size = अणु
		TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_64_BYTES, /* Normal Channels */
		0, /* No H Channels */
		0, /* No UH Channels */
	पूर्ण,
पूर्ण;

अटल काष्ठा udma_match_data am64_pktdma_data = अणु
	.type = DMA_TYPE_PKTDMA,
	.psil_base = 0x1000,
	.enable_स_नकल_support = false, /* PKTDMA करोes not support MEM_TO_MEM */
	.flags = UDMA_FLAGS_J7_CLASS,
	.अटलtr_z_mask = GENMASK(23, 0),
	.burst_size = अणु
		TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_64_BYTES, /* Normal Channels */
		0, /* No H Channels */
		0, /* No UH Channels */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id udma_of_match[] = अणु
	अणु
		.compatible = "ti,am654-navss-main-udmap",
		.data = &am654_मुख्य_data,
	पूर्ण,
	अणु
		.compatible = "ti,am654-navss-mcu-udmap",
		.data = &am654_mcu_data,
	पूर्ण, अणु
		.compatible = "ti,j721e-navss-main-udmap",
		.data = &j721e_मुख्य_data,
	पूर्ण, अणु
		.compatible = "ti,j721e-navss-mcu-udmap",
		.data = &j721e_mcu_data,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcdma_of_match[] = अणु
	अणु
		.compatible = "ti,am64-dmss-bcdma",
		.data = &am64_bcdma_data,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pktdma_of_match[] = अणु
	अणु
		.compatible = "ti,am64-dmss-pktdma",
		.data = &am64_pktdma_data,
	पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा udma_soc_data am654_soc_data = अणु
	.oes = अणु
		.udma_rchan = 0x200,
	पूर्ण,
पूर्ण;

अटल काष्ठा udma_soc_data j721e_soc_data = अणु
	.oes = अणु
		.udma_rchan = 0x400,
	पूर्ण,
पूर्ण;

अटल काष्ठा udma_soc_data j7200_soc_data = अणु
	.oes = अणु
		.udma_rchan = 0x80,
	पूर्ण,
पूर्ण;

अटल काष्ठा udma_soc_data am64_soc_data = अणु
	.oes = अणु
		.bcdma_bchan_data = 0x2200,
		.bcdma_bchan_ring = 0x2400,
		.bcdma_tchan_data = 0x2800,
		.bcdma_tchan_ring = 0x2a00,
		.bcdma_rchan_data = 0x2e00,
		.bcdma_rchan_ring = 0x3000,
		.pktdma_tchan_flow = 0x1200,
		.pktdma_rchan_flow = 0x1600,
	पूर्ण,
	.bcdma_trigger_event_offset = 0xc400,
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute k3_soc_devices[] = अणु
	अणु .family = "AM65X", .data = &am654_soc_data पूर्ण,
	अणु .family = "J721E", .data = &j721e_soc_data पूर्ण,
	अणु .family = "J7200", .data = &j7200_soc_data पूर्ण,
	अणु .family = "AM64X", .data = &am64_soc_data पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक udma_get_mmrs(काष्ठा platक्रमm_device *pdev, काष्ठा udma_dev *ud)
अणु
	u32 cap2, cap3, cap4;
	पूर्णांक i;

	ud->mmrs[MMR_GCFG] = devm_platक्रमm_ioremap_resource_byname(pdev, mmr_names[MMR_GCFG]);
	अगर (IS_ERR(ud->mmrs[MMR_GCFG]))
		वापस PTR_ERR(ud->mmrs[MMR_GCFG]);

	cap2 = udma_पढ़ो(ud->mmrs[MMR_GCFG], 0x28);
	cap3 = udma_पढ़ो(ud->mmrs[MMR_GCFG], 0x2c);

	चयन (ud->match_data->type) अणु
	हाल DMA_TYPE_UDMA:
		ud->rflow_cnt = UDMA_CAP3_RFLOW_CNT(cap3);
		ud->tchan_cnt = UDMA_CAP2_TCHAN_CNT(cap2);
		ud->echan_cnt = UDMA_CAP2_ECHAN_CNT(cap2);
		ud->rchan_cnt = UDMA_CAP2_RCHAN_CNT(cap2);
		अवरोध;
	हाल DMA_TYPE_BCDMA:
		ud->bchan_cnt = BCDMA_CAP2_BCHAN_CNT(cap2);
		ud->tchan_cnt = BCDMA_CAP2_TCHAN_CNT(cap2);
		ud->rchan_cnt = BCDMA_CAP2_RCHAN_CNT(cap2);
		ud->rflow_cnt = ud->rchan_cnt;
		अवरोध;
	हाल DMA_TYPE_PKTDMA:
		cap4 = udma_पढ़ो(ud->mmrs[MMR_GCFG], 0x30);
		ud->tchan_cnt = UDMA_CAP2_TCHAN_CNT(cap2);
		ud->rchan_cnt = UDMA_CAP2_RCHAN_CNT(cap2);
		ud->rflow_cnt = UDMA_CAP3_RFLOW_CNT(cap3);
		ud->tflow_cnt = PKTDMA_CAP4_TFLOW_CNT(cap4);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 1; i < MMR_LAST; i++) अणु
		अगर (i == MMR_BCHANRT && ud->bchan_cnt == 0)
			जारी;
		अगर (i == MMR_TCHANRT && ud->tchan_cnt == 0)
			जारी;
		अगर (i == MMR_RCHANRT && ud->rchan_cnt == 0)
			जारी;

		ud->mmrs[i] = devm_platक्रमm_ioremap_resource_byname(pdev, mmr_names[i]);
		अगर (IS_ERR(ud->mmrs[i]))
			वापस PTR_ERR(ud->mmrs[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम udma_mark_resource_ranges(काष्ठा udma_dev *ud, अचिन्हित दीर्घ *map,
				      काष्ठा ti_sci_resource_desc *rm_desc,
				      अक्षर *name)
अणु
	biपंचांगap_clear(map, rm_desc->start, rm_desc->num);
	biपंचांगap_clear(map, rm_desc->start_sec, rm_desc->num_sec);
	dev_dbg(ud->dev, "ti_sci resource range for %s: %d:%d | %d:%d\n", name,
		rm_desc->start, rm_desc->num, rm_desc->start_sec,
		rm_desc->num_sec);
पूर्ण

अटल स्थिर अक्षर * स्थिर range_names[] = अणु
	[RM_RANGE_BCHAN] = "ti,sci-rm-range-bchan",
	[RM_RANGE_TCHAN] = "ti,sci-rm-range-tchan",
	[RM_RANGE_RCHAN] = "ti,sci-rm-range-rchan",
	[RM_RANGE_RFLOW] = "ti,sci-rm-range-rflow",
	[RM_RANGE_TFLOW] = "ti,sci-rm-range-tflow",
पूर्ण;

अटल पूर्णांक udma_setup_resources(काष्ठा udma_dev *ud)
अणु
	पूर्णांक ret, i, j;
	काष्ठा device *dev = ud->dev;
	काष्ठा ti_sci_resource *rm_res, irq_res;
	काष्ठा udma_tisci_rm *tisci_rm = &ud->tisci_rm;
	u32 cap3;

	/* Set up the throughput level start indexes */
	cap3 = udma_पढ़ो(ud->mmrs[MMR_GCFG], 0x2c);
	अगर (of_device_is_compatible(dev->of_node,
				    "ti,am654-navss-main-udmap")) अणु
		ud->tchan_tpl.levels = 2;
		ud->tchan_tpl.start_idx[0] = 8;
	पूर्ण अन्यथा अगर (of_device_is_compatible(dev->of_node,
					   "ti,am654-navss-mcu-udmap")) अणु
		ud->tchan_tpl.levels = 2;
		ud->tchan_tpl.start_idx[0] = 2;
	पूर्ण अन्यथा अगर (UDMA_CAP3_UCHAN_CNT(cap3)) अणु
		ud->tchan_tpl.levels = 3;
		ud->tchan_tpl.start_idx[1] = UDMA_CAP3_UCHAN_CNT(cap3);
		ud->tchan_tpl.start_idx[0] = UDMA_CAP3_HCHAN_CNT(cap3);
	पूर्ण अन्यथा अगर (UDMA_CAP3_HCHAN_CNT(cap3)) अणु
		ud->tchan_tpl.levels = 2;
		ud->tchan_tpl.start_idx[0] = UDMA_CAP3_HCHAN_CNT(cap3);
	पूर्ण अन्यथा अणु
		ud->tchan_tpl.levels = 1;
	पूर्ण

	ud->rchan_tpl.levels = ud->tchan_tpl.levels;
	ud->rchan_tpl.start_idx[0] = ud->tchan_tpl.start_idx[0];
	ud->rchan_tpl.start_idx[1] = ud->tchan_tpl.start_idx[1];

	ud->tchan_map = devm_kदो_स्मृति_array(dev, BITS_TO_LONGS(ud->tchan_cnt),
					   माप(अचिन्हित दीर्घ), GFP_KERNEL);
	ud->tchans = devm_kसुस्मृति(dev, ud->tchan_cnt, माप(*ud->tchans),
				  GFP_KERNEL);
	ud->rchan_map = devm_kदो_स्मृति_array(dev, BITS_TO_LONGS(ud->rchan_cnt),
					   माप(अचिन्हित दीर्घ), GFP_KERNEL);
	ud->rchans = devm_kसुस्मृति(dev, ud->rchan_cnt, माप(*ud->rchans),
				  GFP_KERNEL);
	ud->rflow_gp_map = devm_kदो_स्मृति_array(dev, BITS_TO_LONGS(ud->rflow_cnt),
					      माप(अचिन्हित दीर्घ),
					      GFP_KERNEL);
	ud->rflow_gp_map_allocated = devm_kसुस्मृति(dev,
						  BITS_TO_LONGS(ud->rflow_cnt),
						  माप(अचिन्हित दीर्घ),
						  GFP_KERNEL);
	ud->rflow_in_use = devm_kसुस्मृति(dev, BITS_TO_LONGS(ud->rflow_cnt),
					माप(अचिन्हित दीर्घ),
					GFP_KERNEL);
	ud->rflows = devm_kसुस्मृति(dev, ud->rflow_cnt, माप(*ud->rflows),
				  GFP_KERNEL);

	अगर (!ud->tchan_map || !ud->rchan_map || !ud->rflow_gp_map ||
	    !ud->rflow_gp_map_allocated || !ud->tchans || !ud->rchans ||
	    !ud->rflows || !ud->rflow_in_use)
		वापस -ENOMEM;

	/*
	 * RX flows with the same Ids as RX channels are reserved to be used
	 * as शेष flows अगर remote HW can't generate flow_ids. Those
	 * RX flows can be requested only explicitly by id.
	 */
	biपंचांगap_set(ud->rflow_gp_map_allocated, 0, ud->rchan_cnt);

	/* by शेष no GP rflows are asचिन्हित to Linux */
	biपंचांगap_set(ud->rflow_gp_map, 0, ud->rflow_cnt);

	/* Get resource ranges from tisci */
	क्रम (i = 0; i < RM_RANGE_LAST; i++) अणु
		अगर (i == RM_RANGE_BCHAN || i == RM_RANGE_TFLOW)
			जारी;

		tisci_rm->rm_ranges[i] =
			devm_ti_sci_get_of_resource(tisci_rm->tisci, dev,
						    tisci_rm->tisci_dev_id,
						    (अक्षर *)range_names[i]);
	पूर्ण

	/* tchan ranges */
	rm_res = tisci_rm->rm_ranges[RM_RANGE_TCHAN];
	अगर (IS_ERR(rm_res)) अणु
		biपंचांगap_zero(ud->tchan_map, ud->tchan_cnt);
	पूर्ण अन्यथा अणु
		biपंचांगap_fill(ud->tchan_map, ud->tchan_cnt);
		क्रम (i = 0; i < rm_res->sets; i++)
			udma_mark_resource_ranges(ud, ud->tchan_map,
						  &rm_res->desc[i], "tchan");
	पूर्ण
	irq_res.sets = rm_res->sets;

	/* rchan and matching शेष flow ranges */
	rm_res = tisci_rm->rm_ranges[RM_RANGE_RCHAN];
	अगर (IS_ERR(rm_res)) अणु
		biपंचांगap_zero(ud->rchan_map, ud->rchan_cnt);
	पूर्ण अन्यथा अणु
		biपंचांगap_fill(ud->rchan_map, ud->rchan_cnt);
		क्रम (i = 0; i < rm_res->sets; i++)
			udma_mark_resource_ranges(ud, ud->rchan_map,
						  &rm_res->desc[i], "rchan");
	पूर्ण

	irq_res.sets += rm_res->sets;
	irq_res.desc = kसुस्मृति(irq_res.sets, माप(*irq_res.desc), GFP_KERNEL);
	rm_res = tisci_rm->rm_ranges[RM_RANGE_TCHAN];
	क्रम (i = 0; i < rm_res->sets; i++) अणु
		irq_res.desc[i].start = rm_res->desc[i].start;
		irq_res.desc[i].num = rm_res->desc[i].num;
		irq_res.desc[i].start_sec = rm_res->desc[i].start_sec;
		irq_res.desc[i].num_sec = rm_res->desc[i].num_sec;
	पूर्ण
	rm_res = tisci_rm->rm_ranges[RM_RANGE_RCHAN];
	क्रम (j = 0; j < rm_res->sets; j++, i++) अणु
		अगर (rm_res->desc[j].num) अणु
			irq_res.desc[i].start = rm_res->desc[j].start +
					ud->soc_data->oes.udma_rchan;
			irq_res.desc[i].num = rm_res->desc[j].num;
		पूर्ण
		अगर (rm_res->desc[j].num_sec) अणु
			irq_res.desc[i].start_sec = rm_res->desc[j].start_sec +
					ud->soc_data->oes.udma_rchan;
			irq_res.desc[i].num_sec = rm_res->desc[j].num_sec;
		पूर्ण
	पूर्ण
	ret = ti_sci_पूर्णांकa_msi_करोमुख्य_alloc_irqs(ud->dev, &irq_res);
	kमुक्त(irq_res.desc);
	अगर (ret) अणु
		dev_err(ud->dev, "Failed to allocate MSI interrupts\n");
		वापस ret;
	पूर्ण

	/* GP rflow ranges */
	rm_res = tisci_rm->rm_ranges[RM_RANGE_RFLOW];
	अगर (IS_ERR(rm_res)) अणु
		/* all gp flows are asचिन्हित exclusively to Linux */
		biपंचांगap_clear(ud->rflow_gp_map, ud->rchan_cnt,
			     ud->rflow_cnt - ud->rchan_cnt);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < rm_res->sets; i++)
			udma_mark_resource_ranges(ud, ud->rflow_gp_map,
						  &rm_res->desc[i], "gp-rflow");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcdma_setup_resources(काष्ठा udma_dev *ud)
अणु
	पूर्णांक ret, i, j;
	काष्ठा device *dev = ud->dev;
	काष्ठा ti_sci_resource *rm_res, irq_res;
	काष्ठा udma_tisci_rm *tisci_rm = &ud->tisci_rm;
	स्थिर काष्ठा udma_oes_offsets *oes = &ud->soc_data->oes;
	u32 cap;

	/* Set up the throughput level start indexes */
	cap = udma_पढ़ो(ud->mmrs[MMR_GCFG], 0x2c);
	अगर (BCDMA_CAP3_UBCHAN_CNT(cap)) अणु
		ud->bchan_tpl.levels = 3;
		ud->bchan_tpl.start_idx[1] = BCDMA_CAP3_UBCHAN_CNT(cap);
		ud->bchan_tpl.start_idx[0] = BCDMA_CAP3_HBCHAN_CNT(cap);
	पूर्ण अन्यथा अगर (BCDMA_CAP3_HBCHAN_CNT(cap)) अणु
		ud->bchan_tpl.levels = 2;
		ud->bchan_tpl.start_idx[0] = BCDMA_CAP3_HBCHAN_CNT(cap);
	पूर्ण अन्यथा अणु
		ud->bchan_tpl.levels = 1;
	पूर्ण

	cap = udma_पढ़ो(ud->mmrs[MMR_GCFG], 0x30);
	अगर (BCDMA_CAP4_URCHAN_CNT(cap)) अणु
		ud->rchan_tpl.levels = 3;
		ud->rchan_tpl.start_idx[1] = BCDMA_CAP4_URCHAN_CNT(cap);
		ud->rchan_tpl.start_idx[0] = BCDMA_CAP4_HRCHAN_CNT(cap);
	पूर्ण अन्यथा अगर (BCDMA_CAP4_HRCHAN_CNT(cap)) अणु
		ud->rchan_tpl.levels = 2;
		ud->rchan_tpl.start_idx[0] = BCDMA_CAP4_HRCHAN_CNT(cap);
	पूर्ण अन्यथा अणु
		ud->rchan_tpl.levels = 1;
	पूर्ण

	अगर (BCDMA_CAP4_UTCHAN_CNT(cap)) अणु
		ud->tchan_tpl.levels = 3;
		ud->tchan_tpl.start_idx[1] = BCDMA_CAP4_UTCHAN_CNT(cap);
		ud->tchan_tpl.start_idx[0] = BCDMA_CAP4_HTCHAN_CNT(cap);
	पूर्ण अन्यथा अगर (BCDMA_CAP4_HTCHAN_CNT(cap)) अणु
		ud->tchan_tpl.levels = 2;
		ud->tchan_tpl.start_idx[0] = BCDMA_CAP4_HTCHAN_CNT(cap);
	पूर्ण अन्यथा अणु
		ud->tchan_tpl.levels = 1;
	पूर्ण

	ud->bchan_map = devm_kदो_स्मृति_array(dev, BITS_TO_LONGS(ud->bchan_cnt),
					   माप(अचिन्हित दीर्घ), GFP_KERNEL);
	ud->bchans = devm_kसुस्मृति(dev, ud->bchan_cnt, माप(*ud->bchans),
				  GFP_KERNEL);
	ud->tchan_map = devm_kदो_स्मृति_array(dev, BITS_TO_LONGS(ud->tchan_cnt),
					   माप(अचिन्हित दीर्घ), GFP_KERNEL);
	ud->tchans = devm_kसुस्मृति(dev, ud->tchan_cnt, माप(*ud->tchans),
				  GFP_KERNEL);
	ud->rchan_map = devm_kदो_स्मृति_array(dev, BITS_TO_LONGS(ud->rchan_cnt),
					   माप(अचिन्हित दीर्घ), GFP_KERNEL);
	ud->rchans = devm_kसुस्मृति(dev, ud->rchan_cnt, माप(*ud->rchans),
				  GFP_KERNEL);
	/* BCDMA करो not really have flows, but the driver expect it */
	ud->rflow_in_use = devm_kसुस्मृति(dev, BITS_TO_LONGS(ud->rchan_cnt),
					माप(अचिन्हित दीर्घ),
					GFP_KERNEL);
	ud->rflows = devm_kसुस्मृति(dev, ud->rchan_cnt, माप(*ud->rflows),
				  GFP_KERNEL);

	अगर (!ud->bchan_map || !ud->tchan_map || !ud->rchan_map ||
	    !ud->rflow_in_use || !ud->bchans || !ud->tchans || !ud->rchans ||
	    !ud->rflows)
		वापस -ENOMEM;

	/* Get resource ranges from tisci */
	क्रम (i = 0; i < RM_RANGE_LAST; i++) अणु
		अगर (i == RM_RANGE_RFLOW || i == RM_RANGE_TFLOW)
			जारी;
		अगर (i == RM_RANGE_BCHAN && ud->bchan_cnt == 0)
			जारी;
		अगर (i == RM_RANGE_TCHAN && ud->tchan_cnt == 0)
			जारी;
		अगर (i == RM_RANGE_RCHAN && ud->rchan_cnt == 0)
			जारी;

		tisci_rm->rm_ranges[i] =
			devm_ti_sci_get_of_resource(tisci_rm->tisci, dev,
						    tisci_rm->tisci_dev_id,
						    (अक्षर *)range_names[i]);
	पूर्ण

	irq_res.sets = 0;

	/* bchan ranges */
	अगर (ud->bchan_cnt) अणु
		rm_res = tisci_rm->rm_ranges[RM_RANGE_BCHAN];
		अगर (IS_ERR(rm_res)) अणु
			biपंचांगap_zero(ud->bchan_map, ud->bchan_cnt);
		पूर्ण अन्यथा अणु
			biपंचांगap_fill(ud->bchan_map, ud->bchan_cnt);
			क्रम (i = 0; i < rm_res->sets; i++)
				udma_mark_resource_ranges(ud, ud->bchan_map,
							  &rm_res->desc[i],
							  "bchan");
		पूर्ण
		irq_res.sets += rm_res->sets;
	पूर्ण

	/* tchan ranges */
	अगर (ud->tchan_cnt) अणु
		rm_res = tisci_rm->rm_ranges[RM_RANGE_TCHAN];
		अगर (IS_ERR(rm_res)) अणु
			biपंचांगap_zero(ud->tchan_map, ud->tchan_cnt);
		पूर्ण अन्यथा अणु
			biपंचांगap_fill(ud->tchan_map, ud->tchan_cnt);
			क्रम (i = 0; i < rm_res->sets; i++)
				udma_mark_resource_ranges(ud, ud->tchan_map,
							  &rm_res->desc[i],
							  "tchan");
		पूर्ण
		irq_res.sets += rm_res->sets * 2;
	पूर्ण

	/* rchan ranges */
	अगर (ud->rchan_cnt) अणु
		rm_res = tisci_rm->rm_ranges[RM_RANGE_RCHAN];
		अगर (IS_ERR(rm_res)) अणु
			biपंचांगap_zero(ud->rchan_map, ud->rchan_cnt);
		पूर्ण अन्यथा अणु
			biपंचांगap_fill(ud->rchan_map, ud->rchan_cnt);
			क्रम (i = 0; i < rm_res->sets; i++)
				udma_mark_resource_ranges(ud, ud->rchan_map,
							  &rm_res->desc[i],
							  "rchan");
		पूर्ण
		irq_res.sets += rm_res->sets * 2;
	पूर्ण

	irq_res.desc = kसुस्मृति(irq_res.sets, माप(*irq_res.desc), GFP_KERNEL);
	अगर (ud->bchan_cnt) अणु
		rm_res = tisci_rm->rm_ranges[RM_RANGE_BCHAN];
		क्रम (i = 0; i < rm_res->sets; i++) अणु
			irq_res.desc[i].start = rm_res->desc[i].start +
						oes->bcdma_bchan_ring;
			irq_res.desc[i].num = rm_res->desc[i].num;
		पूर्ण
	पूर्ण
	अगर (ud->tchan_cnt) अणु
		rm_res = tisci_rm->rm_ranges[RM_RANGE_TCHAN];
		क्रम (j = 0; j < rm_res->sets; j++, i += 2) अणु
			irq_res.desc[i].start = rm_res->desc[j].start +
						oes->bcdma_tchan_data;
			irq_res.desc[i].num = rm_res->desc[j].num;

			irq_res.desc[i + 1].start = rm_res->desc[j].start +
						oes->bcdma_tchan_ring;
			irq_res.desc[i + 1].num = rm_res->desc[j].num;
		पूर्ण
	पूर्ण
	अगर (ud->rchan_cnt) अणु
		rm_res = tisci_rm->rm_ranges[RM_RANGE_RCHAN];
		क्रम (j = 0; j < rm_res->sets; j++, i += 2) अणु
			irq_res.desc[i].start = rm_res->desc[j].start +
						oes->bcdma_rchan_data;
			irq_res.desc[i].num = rm_res->desc[j].num;

			irq_res.desc[i + 1].start = rm_res->desc[j].start +
						oes->bcdma_rchan_ring;
			irq_res.desc[i + 1].num = rm_res->desc[j].num;
		पूर्ण
	पूर्ण

	ret = ti_sci_पूर्णांकa_msi_करोमुख्य_alloc_irqs(ud->dev, &irq_res);
	kमुक्त(irq_res.desc);
	अगर (ret) अणु
		dev_err(ud->dev, "Failed to allocate MSI interrupts\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pktdma_setup_resources(काष्ठा udma_dev *ud)
अणु
	पूर्णांक ret, i, j;
	काष्ठा device *dev = ud->dev;
	काष्ठा ti_sci_resource *rm_res, irq_res;
	काष्ठा udma_tisci_rm *tisci_rm = &ud->tisci_rm;
	स्थिर काष्ठा udma_oes_offsets *oes = &ud->soc_data->oes;
	u32 cap3;

	/* Set up the throughput level start indexes */
	cap3 = udma_पढ़ो(ud->mmrs[MMR_GCFG], 0x2c);
	अगर (UDMA_CAP3_UCHAN_CNT(cap3)) अणु
		ud->tchan_tpl.levels = 3;
		ud->tchan_tpl.start_idx[1] = UDMA_CAP3_UCHAN_CNT(cap3);
		ud->tchan_tpl.start_idx[0] = UDMA_CAP3_HCHAN_CNT(cap3);
	पूर्ण अन्यथा अगर (UDMA_CAP3_HCHAN_CNT(cap3)) अणु
		ud->tchan_tpl.levels = 2;
		ud->tchan_tpl.start_idx[0] = UDMA_CAP3_HCHAN_CNT(cap3);
	पूर्ण अन्यथा अणु
		ud->tchan_tpl.levels = 1;
	पूर्ण

	ud->rchan_tpl.levels = ud->tchan_tpl.levels;
	ud->rchan_tpl.start_idx[0] = ud->tchan_tpl.start_idx[0];
	ud->rchan_tpl.start_idx[1] = ud->tchan_tpl.start_idx[1];

	ud->tchan_map = devm_kदो_स्मृति_array(dev, BITS_TO_LONGS(ud->tchan_cnt),
					   माप(अचिन्हित दीर्घ), GFP_KERNEL);
	ud->tchans = devm_kसुस्मृति(dev, ud->tchan_cnt, माप(*ud->tchans),
				  GFP_KERNEL);
	ud->rchan_map = devm_kदो_स्मृति_array(dev, BITS_TO_LONGS(ud->rchan_cnt),
					   माप(अचिन्हित दीर्घ), GFP_KERNEL);
	ud->rchans = devm_kसुस्मृति(dev, ud->rchan_cnt, माप(*ud->rchans),
				  GFP_KERNEL);
	ud->rflow_in_use = devm_kसुस्मृति(dev, BITS_TO_LONGS(ud->rflow_cnt),
					माप(अचिन्हित दीर्घ),
					GFP_KERNEL);
	ud->rflows = devm_kसुस्मृति(dev, ud->rflow_cnt, माप(*ud->rflows),
				  GFP_KERNEL);
	ud->tflow_map = devm_kदो_स्मृति_array(dev, BITS_TO_LONGS(ud->tflow_cnt),
					   माप(अचिन्हित दीर्घ), GFP_KERNEL);

	अगर (!ud->tchan_map || !ud->rchan_map || !ud->tflow_map || !ud->tchans ||
	    !ud->rchans || !ud->rflows || !ud->rflow_in_use)
		वापस -ENOMEM;

	/* Get resource ranges from tisci */
	क्रम (i = 0; i < RM_RANGE_LAST; i++) अणु
		अगर (i == RM_RANGE_BCHAN)
			जारी;

		tisci_rm->rm_ranges[i] =
			devm_ti_sci_get_of_resource(tisci_rm->tisci, dev,
						    tisci_rm->tisci_dev_id,
						    (अक्षर *)range_names[i]);
	पूर्ण

	/* tchan ranges */
	rm_res = tisci_rm->rm_ranges[RM_RANGE_TCHAN];
	अगर (IS_ERR(rm_res)) अणु
		biपंचांगap_zero(ud->tchan_map, ud->tchan_cnt);
	पूर्ण अन्यथा अणु
		biपंचांगap_fill(ud->tchan_map, ud->tchan_cnt);
		क्रम (i = 0; i < rm_res->sets; i++)
			udma_mark_resource_ranges(ud, ud->tchan_map,
						  &rm_res->desc[i], "tchan");
	पूर्ण

	/* rchan ranges */
	rm_res = tisci_rm->rm_ranges[RM_RANGE_RCHAN];
	अगर (IS_ERR(rm_res)) अणु
		biपंचांगap_zero(ud->rchan_map, ud->rchan_cnt);
	पूर्ण अन्यथा अणु
		biपंचांगap_fill(ud->rchan_map, ud->rchan_cnt);
		क्रम (i = 0; i < rm_res->sets; i++)
			udma_mark_resource_ranges(ud, ud->rchan_map,
						  &rm_res->desc[i], "rchan");
	पूर्ण

	/* rflow ranges */
	rm_res = tisci_rm->rm_ranges[RM_RANGE_RFLOW];
	अगर (IS_ERR(rm_res)) अणु
		/* all rflows are asचिन्हित exclusively to Linux */
		biपंचांगap_zero(ud->rflow_in_use, ud->rflow_cnt);
	पूर्ण अन्यथा अणु
		biपंचांगap_fill(ud->rflow_in_use, ud->rflow_cnt);
		क्रम (i = 0; i < rm_res->sets; i++)
			udma_mark_resource_ranges(ud, ud->rflow_in_use,
						  &rm_res->desc[i], "rflow");
	पूर्ण
	irq_res.sets = rm_res->sets;

	/* tflow ranges */
	rm_res = tisci_rm->rm_ranges[RM_RANGE_TFLOW];
	अगर (IS_ERR(rm_res)) अणु
		/* all tflows are asचिन्हित exclusively to Linux */
		biपंचांगap_zero(ud->tflow_map, ud->tflow_cnt);
	पूर्ण अन्यथा अणु
		biपंचांगap_fill(ud->tflow_map, ud->tflow_cnt);
		क्रम (i = 0; i < rm_res->sets; i++)
			udma_mark_resource_ranges(ud, ud->tflow_map,
						  &rm_res->desc[i], "tflow");
	पूर्ण
	irq_res.sets += rm_res->sets;

	irq_res.desc = kसुस्मृति(irq_res.sets, माप(*irq_res.desc), GFP_KERNEL);
	rm_res = tisci_rm->rm_ranges[RM_RANGE_TFLOW];
	क्रम (i = 0; i < rm_res->sets; i++) अणु
		irq_res.desc[i].start = rm_res->desc[i].start +
					oes->pktdma_tchan_flow;
		irq_res.desc[i].num = rm_res->desc[i].num;
	पूर्ण
	rm_res = tisci_rm->rm_ranges[RM_RANGE_RFLOW];
	क्रम (j = 0; j < rm_res->sets; j++, i++) अणु
		irq_res.desc[i].start = rm_res->desc[j].start +
					oes->pktdma_rchan_flow;
		irq_res.desc[i].num = rm_res->desc[j].num;
	पूर्ण
	ret = ti_sci_पूर्णांकa_msi_करोमुख्य_alloc_irqs(ud->dev, &irq_res);
	kमुक्त(irq_res.desc);
	अगर (ret) अणु
		dev_err(ud->dev, "Failed to allocate MSI interrupts\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक setup_resources(काष्ठा udma_dev *ud)
अणु
	काष्ठा device *dev = ud->dev;
	पूर्णांक ch_count, ret;

	चयन (ud->match_data->type) अणु
	हाल DMA_TYPE_UDMA:
		ret = udma_setup_resources(ud);
		अवरोध;
	हाल DMA_TYPE_BCDMA:
		ret = bcdma_setup_resources(ud);
		अवरोध;
	हाल DMA_TYPE_PKTDMA:
		ret = pktdma_setup_resources(ud);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ret)
		वापस ret;

	ch_count  = ud->bchan_cnt + ud->tchan_cnt + ud->rchan_cnt;
	अगर (ud->bchan_cnt)
		ch_count -= biपंचांगap_weight(ud->bchan_map, ud->bchan_cnt);
	ch_count -= biपंचांगap_weight(ud->tchan_map, ud->tchan_cnt);
	ch_count -= biपंचांगap_weight(ud->rchan_map, ud->rchan_cnt);
	अगर (!ch_count)
		वापस -ENODEV;

	ud->channels = devm_kसुस्मृति(dev, ch_count, माप(*ud->channels),
				    GFP_KERNEL);
	अगर (!ud->channels)
		वापस -ENOMEM;

	चयन (ud->match_data->type) अणु
	हाल DMA_TYPE_UDMA:
		dev_info(dev,
			 "Channels: %d (tchan: %u, rchan: %u, gp-rflow: %u)\n",
			 ch_count,
			 ud->tchan_cnt - biपंचांगap_weight(ud->tchan_map,
						       ud->tchan_cnt),
			 ud->rchan_cnt - biपंचांगap_weight(ud->rchan_map,
						       ud->rchan_cnt),
			 ud->rflow_cnt - biपंचांगap_weight(ud->rflow_gp_map,
						       ud->rflow_cnt));
		अवरोध;
	हाल DMA_TYPE_BCDMA:
		dev_info(dev,
			 "Channels: %d (bchan: %u, tchan: %u, rchan: %u)\n",
			 ch_count,
			 ud->bchan_cnt - biपंचांगap_weight(ud->bchan_map,
						       ud->bchan_cnt),
			 ud->tchan_cnt - biपंचांगap_weight(ud->tchan_map,
						       ud->tchan_cnt),
			 ud->rchan_cnt - biपंचांगap_weight(ud->rchan_map,
						       ud->rchan_cnt));
		अवरोध;
	हाल DMA_TYPE_PKTDMA:
		dev_info(dev,
			 "Channels: %d (tchan: %u, rchan: %u)\n",
			 ch_count,
			 ud->tchan_cnt - biपंचांगap_weight(ud->tchan_map,
						       ud->tchan_cnt),
			 ud->rchan_cnt - biपंचांगap_weight(ud->rchan_map,
						       ud->rchan_cnt));
	शेष:
		अवरोध;
	पूर्ण

	वापस ch_count;
पूर्ण

अटल पूर्णांक udma_setup_rx_flush(काष्ठा udma_dev *ud)
अणु
	काष्ठा udma_rx_flush *rx_flush = &ud->rx_flush;
	काष्ठा cppi5_desc_hdr_t *tr_desc;
	काष्ठा cppi5_tr_type1_t *tr_req;
	काष्ठा cppi5_host_desc_t *desc;
	काष्ठा device *dev = ud->dev;
	काष्ठा udma_hwdesc *hwdesc;
	माप_प्रकार tr_size;

	/* Allocate 1K buffer क्रम discarded data on RX channel tearकरोwn */
	rx_flush->buffer_size = SZ_1K;
	rx_flush->buffer_vaddr = devm_kzalloc(dev, rx_flush->buffer_size,
					      GFP_KERNEL);
	अगर (!rx_flush->buffer_vaddr)
		वापस -ENOMEM;

	rx_flush->buffer_paddr = dma_map_single(dev, rx_flush->buffer_vaddr,
						rx_flush->buffer_size,
						DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, rx_flush->buffer_paddr))
		वापस -ENOMEM;

	/* Set up descriptor to be used क्रम TR mode */
	hwdesc = &rx_flush->hwdescs[0];
	tr_size = माप(काष्ठा cppi5_tr_type1_t);
	hwdesc->cppi5_desc_size = cppi5_trdesc_calc_size(tr_size, 1);
	hwdesc->cppi5_desc_size = ALIGN(hwdesc->cppi5_desc_size,
					ud->desc_align);

	hwdesc->cppi5_desc_vaddr = devm_kzalloc(dev, hwdesc->cppi5_desc_size,
						GFP_KERNEL);
	अगर (!hwdesc->cppi5_desc_vaddr)
		वापस -ENOMEM;

	hwdesc->cppi5_desc_paddr = dma_map_single(dev, hwdesc->cppi5_desc_vaddr,
						  hwdesc->cppi5_desc_size,
						  DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, hwdesc->cppi5_desc_paddr))
		वापस -ENOMEM;

	/* Start of the TR req records */
	hwdesc->tr_req_base = hwdesc->cppi5_desc_vaddr + tr_size;
	/* Start address of the TR response array */
	hwdesc->tr_resp_base = hwdesc->tr_req_base + tr_size;

	tr_desc = hwdesc->cppi5_desc_vaddr;
	cppi5_trdesc_init(tr_desc, 1, tr_size, 0, 0);
	cppi5_desc_set_pktids(tr_desc, 0, CPPI5_INFO1_DESC_FLOWID_DEFAULT);
	cppi5_desc_set_retpolicy(tr_desc, 0, 0);

	tr_req = hwdesc->tr_req_base;
	cppi5_tr_init(&tr_req->flags, CPPI5_TR_TYPE1, false, false,
		      CPPI5_TR_EVENT_SIZE_COMPLETION, 0);
	cppi5_tr_csf_set(&tr_req->flags, CPPI5_TR_CSF_SUPR_EVT);

	tr_req->addr = rx_flush->buffer_paddr;
	tr_req->icnt0 = rx_flush->buffer_size;
	tr_req->icnt1 = 1;

	dma_sync_single_क्रम_device(dev, hwdesc->cppi5_desc_paddr,
				   hwdesc->cppi5_desc_size, DMA_TO_DEVICE);

	/* Set up descriptor to be used क्रम packet mode */
	hwdesc = &rx_flush->hwdescs[1];
	hwdesc->cppi5_desc_size = ALIGN(माप(काष्ठा cppi5_host_desc_t) +
					CPPI5_INFO0_HDESC_EPIB_SIZE +
					CPPI5_INFO0_HDESC_PSDATA_MAX_SIZE,
					ud->desc_align);

	hwdesc->cppi5_desc_vaddr = devm_kzalloc(dev, hwdesc->cppi5_desc_size,
						GFP_KERNEL);
	अगर (!hwdesc->cppi5_desc_vaddr)
		वापस -ENOMEM;

	hwdesc->cppi5_desc_paddr = dma_map_single(dev, hwdesc->cppi5_desc_vaddr,
						  hwdesc->cppi5_desc_size,
						  DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, hwdesc->cppi5_desc_paddr))
		वापस -ENOMEM;

	desc = hwdesc->cppi5_desc_vaddr;
	cppi5_hdesc_init(desc, 0, 0);
	cppi5_desc_set_pktids(&desc->hdr, 0, CPPI5_INFO1_DESC_FLOWID_DEFAULT);
	cppi5_desc_set_retpolicy(&desc->hdr, 0, 0);

	cppi5_hdesc_attach_buf(desc,
			       rx_flush->buffer_paddr, rx_flush->buffer_size,
			       rx_flush->buffer_paddr, rx_flush->buffer_size);

	dma_sync_single_क्रम_device(dev, hwdesc->cppi5_desc_paddr,
				   hwdesc->cppi5_desc_size, DMA_TO_DEVICE);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम udma_dbg_summary_show_chan(काष्ठा seq_file *s,
				       काष्ठा dma_chan *chan)
अणु
	काष्ठा udma_chan *uc = to_udma_chan(chan);
	काष्ठा udma_chan_config *ucc = &uc->config;

	seq_म_लिखो(s, " %-13s| %s", dma_chan_name(chan),
		   chan->dbg_client_name ?: "in-use");
	अगर (ucc->tr_trigger_type)
		seq_माला_दो(s, " (triggered, ");
	अन्यथा
		seq_म_लिखो(s, " (%s, ",
			   dmaengine_get_direction_text(uc->config.dir));

	चयन (uc->config.dir) अणु
	हाल DMA_MEM_TO_MEM:
		अगर (uc->ud->match_data->type == DMA_TYPE_BCDMA) अणु
			seq_म_लिखो(s, "bchan%d)\n", uc->bchan->id);
			वापस;
		पूर्ण

		seq_म_लिखो(s, "chan%d pair [0x%04x -> 0x%04x], ", uc->tchan->id,
			   ucc->src_thपढ़ो, ucc->dst_thपढ़ो);
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		seq_म_लिखो(s, "rchan%d [0x%04x -> 0x%04x], ", uc->rchan->id,
			   ucc->src_thपढ़ो, ucc->dst_thपढ़ो);
		अगर (uc->ud->match_data->type == DMA_TYPE_PKTDMA)
			seq_म_लिखो(s, "rflow%d, ", uc->rflow->id);
		अवरोध;
	हाल DMA_MEM_TO_DEV:
		seq_म_लिखो(s, "tchan%d [0x%04x -> 0x%04x], ", uc->tchan->id,
			   ucc->src_thपढ़ो, ucc->dst_thपढ़ो);
		अगर (uc->ud->match_data->type == DMA_TYPE_PKTDMA)
			seq_म_लिखो(s, "tflow%d, ", uc->tchan->tflow_id);
		अवरोध;
	शेष:
		seq_म_लिखो(s, ")\n");
		वापस;
	पूर्ण

	अगर (ucc->ep_type == PSIL_EP_NATIVE) अणु
		seq_म_लिखो(s, "PSI-L Native");
		अगर (ucc->metadata_size) अणु
			seq_म_लिखो(s, "[%s", ucc->needs_epib ? " EPIB" : "");
			अगर (ucc->psd_size)
				seq_म_लिखो(s, " PSDsize:%u", ucc->psd_size);
			seq_म_लिखो(s, " ]");
		पूर्ण
	पूर्ण अन्यथा अणु
		seq_म_लिखो(s, "PDMA");
		अगर (ucc->enable_acc32 || ucc->enable_burst)
			seq_म_लिखो(s, "[%s%s ]",
				   ucc->enable_acc32 ? " ACC32" : "",
				   ucc->enable_burst ? " BURST" : "");
	पूर्ण

	seq_म_लिखो(s, ", %s)\n", ucc->pkt_mode ? "Packet mode" : "TR mode");
पूर्ण

अटल व्योम udma_dbg_summary_show(काष्ठा seq_file *s,
				  काष्ठा dma_device *dma_dev)
अणु
	काष्ठा dma_chan *chan;

	list_क्रम_each_entry(chan, &dma_dev->channels, device_node) अणु
		अगर (chan->client_count)
			udma_dbg_summary_show_chan(s, chan);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

अटल क्रमागत dmaengine_alignment udma_get_copy_align(काष्ठा udma_dev *ud)
अणु
	स्थिर काष्ठा udma_match_data *match_data = ud->match_data;
	u8 tpl;

	अगर (!match_data->enable_स_नकल_support)
		वापस DMAENGINE_ALIGN_8_BYTES;

	/* Get the highest TPL level the device supports क्रम स_नकल */
	अगर (ud->bchan_cnt)
		tpl = udma_get_chan_tpl_index(&ud->bchan_tpl, 0);
	अन्यथा अगर (ud->tchan_cnt)
		tpl = udma_get_chan_tpl_index(&ud->tchan_tpl, 0);
	अन्यथा
		वापस DMAENGINE_ALIGN_8_BYTES;

	चयन (match_data->burst_size[tpl]) अणु
	हाल TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_256_BYTES:
		वापस DMAENGINE_ALIGN_256_BYTES;
	हाल TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_128_BYTES:
		वापस DMAENGINE_ALIGN_128_BYTES;
	हाल TI_SCI_RM_UDMAP_CHAN_BURST_SIZE_64_BYTES:
	fallthrough;
	शेष:
		वापस DMAENGINE_ALIGN_64_BYTES;
	पूर्ण
पूर्ण

#घोषणा TI_UDMAC_BUSWIDTHS	(BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
				 BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_3_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_8_BYTES))

अटल पूर्णांक udma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *navss_node = pdev->dev.parent->of_node;
	स्थिर काष्ठा soc_device_attribute *soc;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा udma_dev *ud;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक i, ret;
	पूर्णांक ch_count;

	ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(48));
	अगर (ret)
		dev_err(dev, "failed to set dma mask stuff\n");

	ud = devm_kzalloc(dev, माप(*ud), GFP_KERNEL);
	अगर (!ud)
		वापस -ENOMEM;

	match = of_match_node(udma_of_match, dev->of_node);
	अगर (!match)
		match = of_match_node(bcdma_of_match, dev->of_node);
	अगर (!match) अणु
		match = of_match_node(pktdma_of_match, dev->of_node);
		अगर (!match) अणु
			dev_err(dev, "No compatible match found\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	ud->match_data = match->data;

	soc = soc_device_match(k3_soc_devices);
	अगर (!soc) अणु
		dev_err(dev, "No compatible SoC found\n");
		वापस -ENODEV;
	पूर्ण
	ud->soc_data = soc->data;

	ret = udma_get_mmrs(pdev, ud);
	अगर (ret)
		वापस ret;

	ud->tisci_rm.tisci = ti_sci_get_by_phandle(dev->of_node, "ti,sci");
	अगर (IS_ERR(ud->tisci_rm.tisci))
		वापस PTR_ERR(ud->tisci_rm.tisci);

	ret = of_property_पढ़ो_u32(dev->of_node, "ti,sci-dev-id",
				   &ud->tisci_rm.tisci_dev_id);
	अगर (ret) अणु
		dev_err(dev, "ti,sci-dev-id read failure %d\n", ret);
		वापस ret;
	पूर्ण
	pdev->id = ud->tisci_rm.tisci_dev_id;

	ret = of_property_पढ़ो_u32(navss_node, "ti,sci-dev-id",
				   &ud->tisci_rm.tisci_navss_dev_id);
	अगर (ret) अणु
		dev_err(dev, "NAVSS ti,sci-dev-id read failure %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ud->match_data->type == DMA_TYPE_UDMA) अणु
		ret = of_property_पढ़ो_u32(dev->of_node, "ti,udma-atype",
					   &ud->atype);
		अगर (!ret && ud->atype > 2) अणु
			dev_err(dev, "Invalid atype: %u\n", ud->atype);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = of_property_पढ़ो_u32(dev->of_node, "ti,asel",
					   &ud->asel);
		अगर (!ret && ud->asel > 15) अणु
			dev_err(dev, "Invalid asel: %u\n", ud->asel);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ud->tisci_rm.tisci_udmap_ops = &ud->tisci_rm.tisci->ops.rm_udmap_ops;
	ud->tisci_rm.tisci_psil_ops = &ud->tisci_rm.tisci->ops.rm_psil_ops;

	अगर (ud->match_data->type == DMA_TYPE_UDMA) अणु
		ud->ringacc = of_k3_ringacc_get_by_phandle(dev->of_node, "ti,ringacc");
	पूर्ण अन्यथा अणु
		काष्ठा k3_ringacc_init_data ring_init_data;

		ring_init_data.tisci = ud->tisci_rm.tisci;
		ring_init_data.tisci_dev_id = ud->tisci_rm.tisci_dev_id;
		अगर (ud->match_data->type == DMA_TYPE_BCDMA) अणु
			ring_init_data.num_rings = ud->bchan_cnt +
						   ud->tchan_cnt +
						   ud->rchan_cnt;
		पूर्ण अन्यथा अणु
			ring_init_data.num_rings = ud->rflow_cnt +
						   ud->tflow_cnt;
		पूर्ण

		ud->ringacc = k3_ringacc_dmarings_init(pdev, &ring_init_data);
	पूर्ण

	अगर (IS_ERR(ud->ringacc))
		वापस PTR_ERR(ud->ringacc);

	dev->msi_करोमुख्य = of_msi_get_करोमुख्य(dev, dev->of_node,
					    DOMAIN_BUS_TI_SCI_INTA_MSI);
	अगर (!dev->msi_करोमुख्य) अणु
		dev_err(dev, "Failed to get MSI domain\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	dma_cap_set(DMA_SLAVE, ud->ddev.cap_mask);
	/* cyclic operation is not supported via PKTDMA */
	अगर (ud->match_data->type != DMA_TYPE_PKTDMA) अणु
		dma_cap_set(DMA_CYCLIC, ud->ddev.cap_mask);
		ud->ddev.device_prep_dma_cyclic = udma_prep_dma_cyclic;
	पूर्ण

	ud->ddev.device_config = udma_slave_config;
	ud->ddev.device_prep_slave_sg = udma_prep_slave_sg;
	ud->ddev.device_issue_pending = udma_issue_pending;
	ud->ddev.device_tx_status = udma_tx_status;
	ud->ddev.device_छोड़ो = udma_छोड़ो;
	ud->ddev.device_resume = udma_resume;
	ud->ddev.device_terminate_all = udma_terminate_all;
	ud->ddev.device_synchronize = udma_synchronize;
#अगर_घोषित CONFIG_DEBUG_FS
	ud->ddev.dbg_summary_show = udma_dbg_summary_show;
#पूर्ण_अगर

	चयन (ud->match_data->type) अणु
	हाल DMA_TYPE_UDMA:
		ud->ddev.device_alloc_chan_resources =
					udma_alloc_chan_resources;
		अवरोध;
	हाल DMA_TYPE_BCDMA:
		ud->ddev.device_alloc_chan_resources =
					bcdma_alloc_chan_resources;
		ud->ddev.device_router_config = bcdma_router_config;
		अवरोध;
	हाल DMA_TYPE_PKTDMA:
		ud->ddev.device_alloc_chan_resources =
					pktdma_alloc_chan_resources;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ud->ddev.device_मुक्त_chan_resources = udma_मुक्त_chan_resources;

	ud->ddev.src_addr_widths = TI_UDMAC_BUSWIDTHS;
	ud->ddev.dst_addr_widths = TI_UDMAC_BUSWIDTHS;
	ud->ddev.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	ud->ddev.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	ud->ddev.desc_metadata_modes = DESC_METADATA_CLIENT |
				       DESC_METADATA_ENGINE;
	अगर (ud->match_data->enable_स_नकल_support &&
	    !(ud->match_data->type == DMA_TYPE_BCDMA && ud->bchan_cnt == 0)) अणु
		dma_cap_set(DMA_MEMCPY, ud->ddev.cap_mask);
		ud->ddev.device_prep_dma_स_नकल = udma_prep_dma_स_नकल;
		ud->ddev.directions |= BIT(DMA_MEM_TO_MEM);
	पूर्ण

	ud->ddev.dev = dev;
	ud->dev = dev;
	ud->psil_base = ud->match_data->psil_base;

	INIT_LIST_HEAD(&ud->ddev.channels);
	INIT_LIST_HEAD(&ud->desc_to_purge);

	ch_count = setup_resources(ud);
	अगर (ch_count <= 0)
		वापस ch_count;

	spin_lock_init(&ud->lock);
	INIT_WORK(&ud->purge_work, udma_purge_desc_work);

	ud->desc_align = 64;
	अगर (ud->desc_align < dma_get_cache_alignment())
		ud->desc_align = dma_get_cache_alignment();

	ret = udma_setup_rx_flush(ud);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ud->bchan_cnt; i++) अणु
		काष्ठा udma_bchan *bchan = &ud->bchans[i];

		bchan->id = i;
		bchan->reg_rt = ud->mmrs[MMR_BCHANRT] + i * 0x1000;
	पूर्ण

	क्रम (i = 0; i < ud->tchan_cnt; i++) अणु
		काष्ठा udma_tchan *tchan = &ud->tchans[i];

		tchan->id = i;
		tchan->reg_rt = ud->mmrs[MMR_TCHANRT] + i * 0x1000;
	पूर्ण

	क्रम (i = 0; i < ud->rchan_cnt; i++) अणु
		काष्ठा udma_rchan *rchan = &ud->rchans[i];

		rchan->id = i;
		rchan->reg_rt = ud->mmrs[MMR_RCHANRT] + i * 0x1000;
	पूर्ण

	क्रम (i = 0; i < ud->rflow_cnt; i++) अणु
		काष्ठा udma_rflow *rflow = &ud->rflows[i];

		rflow->id = i;
	पूर्ण

	क्रम (i = 0; i < ch_count; i++) अणु
		काष्ठा udma_chan *uc = &ud->channels[i];

		uc->ud = ud;
		uc->vc.desc_मुक्त = udma_desc_मुक्त;
		uc->id = i;
		uc->bchan = शून्य;
		uc->tchan = शून्य;
		uc->rchan = शून्य;
		uc->config.remote_thपढ़ो_id = -1;
		uc->config.mapped_channel_id = -1;
		uc->config.शेष_flow_id = -1;
		uc->config.dir = DMA_MEM_TO_MEM;
		uc->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s chan%d",
					  dev_name(dev), i);

		vchan_init(&uc->vc, &ud->ddev);
		/* Use custom vchan completion handling */
		tasklet_setup(&uc->vc.task, udma_vchan_complete);
		init_completion(&uc->tearकरोwn_completed);
		INIT_DELAYED_WORK(&uc->tx_drain.work, udma_check_tx_completion);
	पूर्ण

	/* Configure the copy_align to the maximum burst size the device supports */
	ud->ddev.copy_align = udma_get_copy_align(ud);

	ret = dma_async_device_रेजिस्टर(&ud->ddev);
	अगर (ret) अणु
		dev_err(dev, "failed to register slave DMA engine: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ud);

	ret = of_dma_controller_रेजिस्टर(dev->of_node, udma_of_xlate, ud);
	अगर (ret) अणु
		dev_err(dev, "failed to register of_dma controller\n");
		dma_async_device_unरेजिस्टर(&ud->ddev);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver udma_driver = अणु
	.driver = अणु
		.name	= "ti-udma",
		.of_match_table = udma_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= udma_probe,
पूर्ण;
builtin_platक्रमm_driver(udma_driver);

अटल काष्ठा platक्रमm_driver bcdma_driver = अणु
	.driver = अणु
		.name	= "ti-bcdma",
		.of_match_table = bcdma_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= udma_probe,
पूर्ण;
builtin_platक्रमm_driver(bcdma_driver);

अटल काष्ठा platक्रमm_driver pktdma_driver = अणु
	.driver = अणु
		.name	= "ti-pktdma",
		.of_match_table = pktdma_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= udma_probe,
पूर्ण;
builtin_platक्रमm_driver(pktdma_driver);

/* Private पूर्णांकerfaces to UDMA */
#समावेश "k3-udma-private.c"
