<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Actions Semi Owl SoCs DMA driver
//
// Copyright (c) 2014 Actions Semi Inc.
// Author: David Liu <liuwei@actions-semi.com>
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/slab.h>
#समावेश "virt-dma.h"

#घोषणा OWL_DMA_FRAME_MAX_LENGTH		0xfffff

/* Global DMA Controller Registers */
#घोषणा OWL_DMA_IRQ_PD0				0x00
#घोषणा OWL_DMA_IRQ_PD1				0x04
#घोषणा OWL_DMA_IRQ_PD2				0x08
#घोषणा OWL_DMA_IRQ_PD3				0x0C
#घोषणा OWL_DMA_IRQ_EN0				0x10
#घोषणा OWL_DMA_IRQ_EN1				0x14
#घोषणा OWL_DMA_IRQ_EN2				0x18
#घोषणा OWL_DMA_IRQ_EN3				0x1C
#घोषणा OWL_DMA_SECURE_ACCESS_CTL		0x20
#घोषणा OWL_DMA_NIC_QOS				0x24
#घोषणा OWL_DMA_DBGSEL				0x28
#घोषणा OWL_DMA_IDLE_STAT			0x2C

/* Channel Registers */
#घोषणा OWL_DMA_CHAN_BASE(i)			(0x100 + (i) * 0x100)
#घोषणा OWL_DMAX_MODE				0x00
#घोषणा OWL_DMAX_SOURCE				0x04
#घोषणा OWL_DMAX_DESTINATION			0x08
#घोषणा OWL_DMAX_FRAME_LEN			0x0C
#घोषणा OWL_DMAX_FRAME_CNT			0x10
#घोषणा OWL_DMAX_REMAIN_FRAME_CNT		0x14
#घोषणा OWL_DMAX_REMAIN_CNT			0x18
#घोषणा OWL_DMAX_SOURCE_STRIDE			0x1C
#घोषणा OWL_DMAX_DESTINATION_STRIDE		0x20
#घोषणा OWL_DMAX_START				0x24
#घोषणा OWL_DMAX_PAUSE				0x28
#घोषणा OWL_DMAX_CHAINED_CTL			0x2C
#घोषणा OWL_DMAX_CONSTANT			0x30
#घोषणा OWL_DMAX_LINKLIST_CTL			0x34
#घोषणा OWL_DMAX_NEXT_DESCRIPTOR		0x38
#घोषणा OWL_DMAX_CURRENT_DESCRIPTOR_NUM		0x3C
#घोषणा OWL_DMAX_INT_CTL			0x40
#घोषणा OWL_DMAX_INT_STATUS			0x44
#घोषणा OWL_DMAX_CURRENT_SOURCE_POINTER		0x48
#घोषणा OWL_DMAX_CURRENT_DESTINATION_POINTER	0x4C

/* OWL_DMAX_MODE Bits */
#घोषणा OWL_DMA_MODE_TS(x)			(((x) & GENMASK(5, 0)) << 0)
#घोषणा OWL_DMA_MODE_ST(x)			(((x) & GENMASK(1, 0)) << 8)
#घोषणा	OWL_DMA_MODE_ST_DEV			OWL_DMA_MODE_ST(0)
#घोषणा	OWL_DMA_MODE_ST_DCU			OWL_DMA_MODE_ST(2)
#घोषणा	OWL_DMA_MODE_ST_SRAM			OWL_DMA_MODE_ST(3)
#घोषणा OWL_DMA_MODE_DT(x)			(((x) & GENMASK(1, 0)) << 10)
#घोषणा	OWL_DMA_MODE_DT_DEV			OWL_DMA_MODE_DT(0)
#घोषणा	OWL_DMA_MODE_DT_DCU			OWL_DMA_MODE_DT(2)
#घोषणा	OWL_DMA_MODE_DT_SRAM			OWL_DMA_MODE_DT(3)
#घोषणा OWL_DMA_MODE_SAM(x)			(((x) & GENMASK(1, 0)) << 16)
#घोषणा	OWL_DMA_MODE_SAM_CONST			OWL_DMA_MODE_SAM(0)
#घोषणा	OWL_DMA_MODE_SAM_INC			OWL_DMA_MODE_SAM(1)
#घोषणा	OWL_DMA_MODE_SAM_STRIDE			OWL_DMA_MODE_SAM(2)
#घोषणा OWL_DMA_MODE_DAM(x)			(((x) & GENMASK(1, 0)) << 18)
#घोषणा	OWL_DMA_MODE_DAM_CONST			OWL_DMA_MODE_DAM(0)
#घोषणा	OWL_DMA_MODE_DAM_INC			OWL_DMA_MODE_DAM(1)
#घोषणा	OWL_DMA_MODE_DAM_STRIDE			OWL_DMA_MODE_DAM(2)
#घोषणा OWL_DMA_MODE_PW(x)			(((x) & GENMASK(2, 0)) << 20)
#घोषणा OWL_DMA_MODE_CB				BIT(23)
#घोषणा OWL_DMA_MODE_NDDBW(x)			(((x) & 0x1) << 28)
#घोषणा	OWL_DMA_MODE_NDDBW_32BIT		OWL_DMA_MODE_NDDBW(0)
#घोषणा	OWL_DMA_MODE_NDDBW_8BIT			OWL_DMA_MODE_NDDBW(1)
#घोषणा OWL_DMA_MODE_CFE			BIT(29)
#घोषणा OWL_DMA_MODE_LME			BIT(30)
#घोषणा OWL_DMA_MODE_CME			BIT(31)

/* OWL_DMAX_LINKLIST_CTL Bits */
#घोषणा OWL_DMA_LLC_SAV(x)			(((x) & GENMASK(1, 0)) << 8)
#घोषणा	OWL_DMA_LLC_SAV_INC			OWL_DMA_LLC_SAV(0)
#घोषणा	OWL_DMA_LLC_SAV_LOAD_NEXT		OWL_DMA_LLC_SAV(1)
#घोषणा	OWL_DMA_LLC_SAV_LOAD_PREV		OWL_DMA_LLC_SAV(2)
#घोषणा OWL_DMA_LLC_DAV(x)			(((x) & GENMASK(1, 0)) << 10)
#घोषणा	OWL_DMA_LLC_DAV_INC			OWL_DMA_LLC_DAV(0)
#घोषणा	OWL_DMA_LLC_DAV_LOAD_NEXT		OWL_DMA_LLC_DAV(1)
#घोषणा	OWL_DMA_LLC_DAV_LOAD_PREV		OWL_DMA_LLC_DAV(2)
#घोषणा OWL_DMA_LLC_SUSPEND			BIT(16)

/* OWL_DMAX_INT_CTL Bits */
#घोषणा OWL_DMA_INTCTL_BLOCK			BIT(0)
#घोषणा OWL_DMA_INTCTL_SUPER_BLOCK		BIT(1)
#घोषणा OWL_DMA_INTCTL_FRAME			BIT(2)
#घोषणा OWL_DMA_INTCTL_HALF_FRAME		BIT(3)
#घोषणा OWL_DMA_INTCTL_LAST_FRAME		BIT(4)

/* OWL_DMAX_INT_STATUS Bits */
#घोषणा OWL_DMA_INTSTAT_BLOCK			BIT(0)
#घोषणा OWL_DMA_INTSTAT_SUPER_BLOCK		BIT(1)
#घोषणा OWL_DMA_INTSTAT_FRAME			BIT(2)
#घोषणा OWL_DMA_INTSTAT_HALF_FRAME		BIT(3)
#घोषणा OWL_DMA_INTSTAT_LAST_FRAME		BIT(4)

/* Pack shअगरt and newshअगरt in a single word */
#घोषणा BIT_FIELD(val, width, shअगरt, newshअगरt)	\
		((((val) >> (shअगरt)) & ((BIT(width)) - 1)) << (newshअगरt))

/* Frame count value is fixed as 1 */
#घोषणा FCNT_VAL				0x1

/**
 * क्रमागत owl_dmadesc_offsets - Describe DMA descriptor, hardware link
 * list क्रम dma transfer
 * @OWL_DMADESC_NEXT_LLI: physical address of the next link list
 * @OWL_DMADESC_SADDR: source physical address
 * @OWL_DMADESC_DADDR: destination physical address
 * @OWL_DMADESC_FLEN: frame length
 * @OWL_DMADESC_SRC_STRIDE: source stride
 * @OWL_DMADESC_DST_STRIDE: destination stride
 * @OWL_DMADESC_CTRLA: dma_mode and linklist ctrl config
 * @OWL_DMADESC_CTRLB: पूर्णांकerrupt config
 * @OWL_DMADESC_CONST_NUM: data क्रम स्थिरant fill
 * @OWL_DMADESC_SIZE: max size of this क्रमागत
 */
क्रमागत owl_dmadesc_offsets अणु
	OWL_DMADESC_NEXT_LLI = 0,
	OWL_DMADESC_SADDR,
	OWL_DMADESC_DADDR,
	OWL_DMADESC_FLEN,
	OWL_DMADESC_SRC_STRIDE,
	OWL_DMADESC_DST_STRIDE,
	OWL_DMADESC_CTRLA,
	OWL_DMADESC_CTRLB,
	OWL_DMADESC_CONST_NUM,
	OWL_DMADESC_SIZE
पूर्ण;

क्रमागत owl_dma_id अणु
	S900_DMA,
	S700_DMA,
पूर्ण;

/**
 * काष्ठा owl_dma_lli - Link list क्रम dma transfer
 * @hw: hardware link list
 * @phys: physical address of hardware link list
 * @node: node क्रम txd's lli_list
 */
काष्ठा owl_dma_lli अणु
	u32			hw[OWL_DMADESC_SIZE];
	dma_addr_t		phys;
	काष्ठा list_head	node;
पूर्ण;

/**
 * काष्ठा owl_dma_txd - Wrapper क्रम काष्ठा dma_async_tx_descriptor
 * @vd: भव DMA descriptor
 * @lli_list: link list of lli nodes
 * @cyclic: flag to indicate cyclic transfers
 */
काष्ठा owl_dma_txd अणु
	काष्ठा virt_dma_desc	vd;
	काष्ठा list_head	lli_list;
	bool			cyclic;
पूर्ण;

/**
 * काष्ठा owl_dma_pchan - Holder क्रम the physical channels
 * @id: physical index to this channel
 * @base: भव memory base क्रम the dma channel
 * @vchan: the भव channel currently being served by this physical channel
 */
काष्ठा owl_dma_pchan अणु
	u32			id;
	व्योम __iomem		*base;
	काष्ठा owl_dma_vchan	*vchan;
पूर्ण;

/**
 * काष्ठा owl_dma_pchan - Wrapper क्रम DMA ENGINE channel
 * @vc: wrappped भव channel
 * @pchan: the physical channel utilized by this channel
 * @txd: active transaction on this channel
 * @cfg: slave configuration क्रम this channel
 * @drq: physical DMA request ID क्रम this channel
 */
काष्ठा owl_dma_vchan अणु
	काष्ठा virt_dma_chan	vc;
	काष्ठा owl_dma_pchan	*pchan;
	काष्ठा owl_dma_txd	*txd;
	काष्ठा dma_slave_config cfg;
	u8			drq;
पूर्ण;

/**
 * काष्ठा owl_dma - Holder क्रम the Owl DMA controller
 * @dma: dma engine क्रम this instance
 * @base: भव memory base क्रम the DMA controller
 * @clk: घड़ी क्रम the DMA controller
 * @lock: a lock to use when change DMA controller global रेजिस्टर
 * @lli_pool: a pool क्रम the LLI descriptors
 * @irq: पूर्णांकerrupt ID क्रम the DMA controller
 * @nr_pchans: the number of physical channels
 * @pchans: array of data क्रम the physical channels
 * @nr_vchans: the number of physical channels
 * @vchans: array of data क्रम the physical channels
 * @devid: device id based on OWL SoC
 */
काष्ठा owl_dma अणु
	काष्ठा dma_device	dma;
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	spinlock_t		lock;
	काष्ठा dma_pool		*lli_pool;
	पूर्णांक			irq;

	अचिन्हित पूर्णांक		nr_pchans;
	काष्ठा owl_dma_pchan	*pchans;

	अचिन्हित पूर्णांक		nr_vchans;
	काष्ठा owl_dma_vchan	*vchans;
	क्रमागत owl_dma_id		devid;
पूर्ण;

अटल व्योम pchan_update(काष्ठा owl_dma_pchan *pchan, u32 reg,
			 u32 val, bool state)
अणु
	u32 regval;

	regval = पढ़ोl(pchan->base + reg);

	अगर (state)
		regval |= val;
	अन्यथा
		regval &= ~val;

	ग_लिखोl(val, pchan->base + reg);
पूर्ण

अटल व्योम pchan_ग_लिखोl(काष्ठा owl_dma_pchan *pchan, u32 reg, u32 data)
अणु
	ग_लिखोl(data, pchan->base + reg);
पूर्ण

अटल u32 pchan_पढ़ोl(काष्ठा owl_dma_pchan *pchan, u32 reg)
अणु
	वापस पढ़ोl(pchan->base + reg);
पूर्ण

अटल व्योम dma_update(काष्ठा owl_dma *od, u32 reg, u32 val, bool state)
अणु
	u32 regval;

	regval = पढ़ोl(od->base + reg);

	अगर (state)
		regval |= val;
	अन्यथा
		regval &= ~val;

	ग_लिखोl(val, od->base + reg);
पूर्ण

अटल व्योम dma_ग_लिखोl(काष्ठा owl_dma *od, u32 reg, u32 data)
अणु
	ग_लिखोl(data, od->base + reg);
पूर्ण

अटल u32 dma_पढ़ोl(काष्ठा owl_dma *od, u32 reg)
अणु
	वापस पढ़ोl(od->base + reg);
पूर्ण

अटल अंतरभूत काष्ठा owl_dma *to_owl_dma(काष्ठा dma_device *dd)
अणु
	वापस container_of(dd, काष्ठा owl_dma, dma);
पूर्ण

अटल काष्ठा device *chan2dev(काष्ठा dma_chan *chan)
अणु
	वापस &chan->dev->device;
पूर्ण

अटल अंतरभूत काष्ठा owl_dma_vchan *to_owl_vchan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा owl_dma_vchan, vc.chan);
पूर्ण

अटल अंतरभूत काष्ठा owl_dma_txd *to_owl_txd(काष्ठा dma_async_tx_descriptor *tx)
अणु
	वापस container_of(tx, काष्ठा owl_dma_txd, vd.tx);
पूर्ण

अटल अंतरभूत u32 llc_hw_ctrla(u32 mode, u32 llc_ctl)
अणु
	u32 ctl;

	ctl = BIT_FIELD(mode, 4, 28, 28) |
	      BIT_FIELD(mode, 8, 16, 20) |
	      BIT_FIELD(mode, 4, 8, 16) |
	      BIT_FIELD(mode, 6, 0, 10) |
	      BIT_FIELD(llc_ctl, 2, 10, 8) |
	      BIT_FIELD(llc_ctl, 2, 8, 6);

	वापस ctl;
पूर्ण

अटल अंतरभूत u32 llc_hw_ctrlb(u32 पूर्णांक_ctl)
अणु
	u32 ctl;

	/*
	 * Irrespective of the SoC, ctrlb value starts filling from
	 * bit 18.
	 */
	ctl = BIT_FIELD(पूर्णांक_ctl, 7, 0, 18);

	वापस ctl;
पूर्ण

अटल u32 llc_hw_flen(काष्ठा owl_dma_lli *lli)
अणु
	वापस lli->hw[OWL_DMADESC_FLEN] & GENMASK(19, 0);
पूर्ण

अटल व्योम owl_dma_मुक्त_lli(काष्ठा owl_dma *od,
			     काष्ठा owl_dma_lli *lli)
अणु
	list_del(&lli->node);
	dma_pool_मुक्त(od->lli_pool, lli, lli->phys);
पूर्ण

अटल काष्ठा owl_dma_lli *owl_dma_alloc_lli(काष्ठा owl_dma *od)
अणु
	काष्ठा owl_dma_lli *lli;
	dma_addr_t phys;

	lli = dma_pool_alloc(od->lli_pool, GFP_NOWAIT, &phys);
	अगर (!lli)
		वापस शून्य;

	INIT_LIST_HEAD(&lli->node);
	lli->phys = phys;

	वापस lli;
पूर्ण

अटल काष्ठा owl_dma_lli *owl_dma_add_lli(काष्ठा owl_dma_txd *txd,
					   काष्ठा owl_dma_lli *prev,
					   काष्ठा owl_dma_lli *next,
					   bool is_cyclic)
अणु
	अगर (!is_cyclic)
		list_add_tail(&next->node, &txd->lli_list);

	अगर (prev) अणु
		prev->hw[OWL_DMADESC_NEXT_LLI] = next->phys;
		prev->hw[OWL_DMADESC_CTRLA] |=
					llc_hw_ctrla(OWL_DMA_MODE_LME, 0);
	पूर्ण

	वापस next;
पूर्ण

अटल अंतरभूत पूर्णांक owl_dma_cfg_lli(काष्ठा owl_dma_vchan *vchan,
				  काष्ठा owl_dma_lli *lli,
				  dma_addr_t src, dma_addr_t dst,
				  u32 len, क्रमागत dma_transfer_direction dir,
				  काष्ठा dma_slave_config *sconfig,
				  bool is_cyclic)
अणु
	काष्ठा owl_dma *od = to_owl_dma(vchan->vc.chan.device);
	u32 mode, ctrlb;

	mode = OWL_DMA_MODE_PW(0);

	चयन (dir) अणु
	हाल DMA_MEM_TO_MEM:
		mode |= OWL_DMA_MODE_TS(0) | OWL_DMA_MODE_ST_DCU |
			OWL_DMA_MODE_DT_DCU | OWL_DMA_MODE_SAM_INC |
			OWL_DMA_MODE_DAM_INC;

		अवरोध;
	हाल DMA_MEM_TO_DEV:
		mode |= OWL_DMA_MODE_TS(vchan->drq)
			| OWL_DMA_MODE_ST_DCU | OWL_DMA_MODE_DT_DEV
			| OWL_DMA_MODE_SAM_INC | OWL_DMA_MODE_DAM_CONST;

		/*
		 * Hardware only supports 32bit and 8bit buswidth. Since the
		 * शेष is 32bit, select 8bit only when requested.
		 */
		अगर (sconfig->dst_addr_width == DMA_SLAVE_BUSWIDTH_1_BYTE)
			mode |= OWL_DMA_MODE_NDDBW_8BIT;

		अवरोध;
	हाल DMA_DEV_TO_MEM:
		 mode |= OWL_DMA_MODE_TS(vchan->drq)
			| OWL_DMA_MODE_ST_DEV | OWL_DMA_MODE_DT_DCU
			| OWL_DMA_MODE_SAM_CONST | OWL_DMA_MODE_DAM_INC;

		/*
		 * Hardware only supports 32bit and 8bit buswidth. Since the
		 * शेष is 32bit, select 8bit only when requested.
		 */
		अगर (sconfig->src_addr_width == DMA_SLAVE_BUSWIDTH_1_BYTE)
			mode |= OWL_DMA_MODE_NDDBW_8BIT;

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	lli->hw[OWL_DMADESC_CTRLA] = llc_hw_ctrla(mode,
						  OWL_DMA_LLC_SAV_LOAD_NEXT |
						  OWL_DMA_LLC_DAV_LOAD_NEXT);

	अगर (is_cyclic)
		ctrlb = llc_hw_ctrlb(OWL_DMA_INTCTL_BLOCK);
	अन्यथा
		ctrlb = llc_hw_ctrlb(OWL_DMA_INTCTL_SUPER_BLOCK);

	lli->hw[OWL_DMADESC_NEXT_LLI] = 0; /* One link list by शेष */
	lli->hw[OWL_DMADESC_SADDR] = src;
	lli->hw[OWL_DMADESC_DADDR] = dst;
	lli->hw[OWL_DMADESC_SRC_STRIDE] = 0;
	lli->hw[OWL_DMADESC_DST_STRIDE] = 0;

	अगर (od->devid == S700_DMA) अणु
		/* Max frame length is 1MB */
		lli->hw[OWL_DMADESC_FLEN] = len;
		/*
		 * On S700, word starts from offset 0x1C is shared between
		 * frame count and ctrlb, where first 12 bits are क्रम frame
		 * count and rest of 20 bits are क्रम ctrlb.
		 */
		lli->hw[OWL_DMADESC_CTRLB] = FCNT_VAL | ctrlb;
	पूर्ण अन्यथा अणु
		/*
		 * On S900, word starts from offset 0xC is shared between
		 * frame length (max frame length is 1MB) and frame count,
		 * where first 20 bits are क्रम frame length and rest of
		 * 12 bits are क्रम frame count.
		 */
		lli->hw[OWL_DMADESC_FLEN] = len | FCNT_VAL << 20;
		lli->hw[OWL_DMADESC_CTRLB] = ctrlb;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा owl_dma_pchan *owl_dma_get_pchan(काष्ठा owl_dma *od,
					       काष्ठा owl_dma_vchan *vchan)
अणु
	काष्ठा owl_dma_pchan *pchan = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	क्रम (i = 0; i < od->nr_pchans; i++) अणु
		pchan = &od->pchans[i];

		spin_lock_irqsave(&od->lock, flags);
		अगर (!pchan->vchan) अणु
			pchan->vchan = vchan;
			spin_unlock_irqrestore(&od->lock, flags);
			अवरोध;
		पूर्ण

		spin_unlock_irqrestore(&od->lock, flags);
	पूर्ण

	वापस pchan;
पूर्ण

अटल पूर्णांक owl_dma_pchan_busy(काष्ठा owl_dma *od, काष्ठा owl_dma_pchan *pchan)
अणु
	अचिन्हित पूर्णांक val;

	val = dma_पढ़ोl(od, OWL_DMA_IDLE_STAT);

	वापस !(val & (1 << pchan->id));
पूर्ण

अटल व्योम owl_dma_terminate_pchan(काष्ठा owl_dma *od,
				    काष्ठा owl_dma_pchan *pchan)
अणु
	अचिन्हित दीर्घ flags;
	u32 irq_pd;

	pchan_ग_लिखोl(pchan, OWL_DMAX_START, 0);
	pchan_update(pchan, OWL_DMAX_INT_STATUS, 0xff, false);

	spin_lock_irqsave(&od->lock, flags);
	dma_update(od, OWL_DMA_IRQ_EN0, (1 << pchan->id), false);

	irq_pd = dma_पढ़ोl(od, OWL_DMA_IRQ_PD0);
	अगर (irq_pd & (1 << pchan->id)) अणु
		dev_warn(od->dma.dev,
			 "terminating pchan %d that still has pending irq\n",
			 pchan->id);
		dma_ग_लिखोl(od, OWL_DMA_IRQ_PD0, (1 << pchan->id));
	पूर्ण

	pchan->vchan = शून्य;

	spin_unlock_irqrestore(&od->lock, flags);
पूर्ण

अटल व्योम owl_dma_छोड़ो_pchan(काष्ठा owl_dma_pchan *pchan)
अणु
	pchan_ग_लिखोl(pchan, 1, OWL_DMAX_PAUSE);
पूर्ण

अटल व्योम owl_dma_resume_pchan(काष्ठा owl_dma_pchan *pchan)
अणु
	pchan_ग_लिखोl(pchan, 0, OWL_DMAX_PAUSE);
पूर्ण

अटल पूर्णांक owl_dma_start_next_txd(काष्ठा owl_dma_vchan *vchan)
अणु
	काष्ठा owl_dma *od = to_owl_dma(vchan->vc.chan.device);
	काष्ठा virt_dma_desc *vd = vchan_next_desc(&vchan->vc);
	काष्ठा owl_dma_pchan *pchan = vchan->pchan;
	काष्ठा owl_dma_txd *txd = to_owl_txd(&vd->tx);
	काष्ठा owl_dma_lli *lli;
	अचिन्हित दीर्घ flags;
	u32 पूर्णांक_ctl;

	list_del(&vd->node);

	vchan->txd = txd;

	/* Wait क्रम channel inactive */
	जबतक (owl_dma_pchan_busy(od, pchan))
		cpu_relax();

	lli = list_first_entry(&txd->lli_list,
			       काष्ठा owl_dma_lli, node);

	अगर (txd->cyclic)
		पूर्णांक_ctl = OWL_DMA_INTCTL_BLOCK;
	अन्यथा
		पूर्णांक_ctl = OWL_DMA_INTCTL_SUPER_BLOCK;

	pchan_ग_लिखोl(pchan, OWL_DMAX_MODE, OWL_DMA_MODE_LME);
	pchan_ग_लिखोl(pchan, OWL_DMAX_LINKLIST_CTL,
		     OWL_DMA_LLC_SAV_LOAD_NEXT | OWL_DMA_LLC_DAV_LOAD_NEXT);
	pchan_ग_लिखोl(pchan, OWL_DMAX_NEXT_DESCRIPTOR, lli->phys);
	pchan_ग_लिखोl(pchan, OWL_DMAX_INT_CTL, पूर्णांक_ctl);

	/* Clear IRQ status क्रम this pchan */
	pchan_update(pchan, OWL_DMAX_INT_STATUS, 0xff, false);

	spin_lock_irqsave(&od->lock, flags);

	dma_update(od, OWL_DMA_IRQ_EN0, (1 << pchan->id), true);

	spin_unlock_irqrestore(&od->lock, flags);

	dev_dbg(chan2dev(&vchan->vc.chan), "starting pchan %d\n", pchan->id);

	/* Start DMA transfer क्रम this pchan */
	pchan_ग_लिखोl(pchan, OWL_DMAX_START, 0x1);

	वापस 0;
पूर्ण

अटल व्योम owl_dma_phy_मुक्त(काष्ठा owl_dma *od, काष्ठा owl_dma_vchan *vchan)
अणु
	/* Ensure that the physical channel is stopped */
	owl_dma_terminate_pchan(od, vchan->pchan);

	vchan->pchan = शून्य;
पूर्ण

अटल irqवापस_t owl_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा owl_dma *od = dev_id;
	काष्ठा owl_dma_vchan *vchan;
	काष्ठा owl_dma_pchan *pchan;
	अचिन्हित दीर्घ pending;
	पूर्णांक i;
	अचिन्हित पूर्णांक global_irq_pending, chan_irq_pending;

	spin_lock(&od->lock);

	pending = dma_पढ़ोl(od, OWL_DMA_IRQ_PD0);

	/* Clear IRQ status क्रम each pchan */
	क्रम_each_set_bit(i, &pending, od->nr_pchans) अणु
		pchan = &od->pchans[i];
		pchan_update(pchan, OWL_DMAX_INT_STATUS, 0xff, false);
	पूर्ण

	/* Clear pending IRQ */
	dma_ग_लिखोl(od, OWL_DMA_IRQ_PD0, pending);

	/* Check missed pending IRQ */
	क्रम (i = 0; i < od->nr_pchans; i++) अणु
		pchan = &od->pchans[i];
		chan_irq_pending = pchan_पढ़ोl(pchan, OWL_DMAX_INT_CTL) &
				   pchan_पढ़ोl(pchan, OWL_DMAX_INT_STATUS);

		/* Dummy पढ़ो to ensure OWL_DMA_IRQ_PD0 value is updated */
		dma_पढ़ोl(od, OWL_DMA_IRQ_PD0);

		global_irq_pending = dma_पढ़ोl(od, OWL_DMA_IRQ_PD0);

		अगर (chan_irq_pending && !(global_irq_pending & BIT(i))) अणु
			dev_dbg(od->dma.dev,
				"global and channel IRQ pending match err\n");

			/* Clear IRQ status क्रम this pchan */
			pchan_update(pchan, OWL_DMAX_INT_STATUS,
				     0xff, false);

			/* Update global IRQ pending */
			pending |= BIT(i);
		पूर्ण
	पूर्ण

	spin_unlock(&od->lock);

	क्रम_each_set_bit(i, &pending, od->nr_pchans) अणु
		काष्ठा owl_dma_txd *txd;

		pchan = &od->pchans[i];

		vchan = pchan->vchan;
		अगर (!vchan) अणु
			dev_warn(od->dma.dev, "no vchan attached on pchan %d\n",
				 pchan->id);
			जारी;
		पूर्ण

		spin_lock(&vchan->vc.lock);

		txd = vchan->txd;
		अगर (txd) अणु
			vchan->txd = शून्य;

			vchan_cookie_complete(&txd->vd);

			/*
			 * Start the next descriptor (अगर any),
			 * otherwise मुक्त this channel.
			 */
			अगर (vchan_next_desc(&vchan->vc))
				owl_dma_start_next_txd(vchan);
			अन्यथा
				owl_dma_phy_मुक्त(od, vchan);
		पूर्ण

		spin_unlock(&vchan->vc.lock);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम owl_dma_मुक्त_txd(काष्ठा owl_dma *od, काष्ठा owl_dma_txd *txd)
अणु
	काष्ठा owl_dma_lli *lli, *_lli;

	अगर (unlikely(!txd))
		वापस;

	list_क्रम_each_entry_safe(lli, _lli, &txd->lli_list, node)
		owl_dma_मुक्त_lli(od, lli);

	kमुक्त(txd);
पूर्ण

अटल व्योम owl_dma_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा owl_dma *od = to_owl_dma(vd->tx.chan->device);
	काष्ठा owl_dma_txd *txd = to_owl_txd(&vd->tx);

	owl_dma_मुक्त_txd(od, txd);
पूर्ण

अटल पूर्णांक owl_dma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा owl_dma *od = to_owl_dma(chan->device);
	काष्ठा owl_dma_vchan *vchan = to_owl_vchan(chan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&vchan->vc.lock, flags);

	अगर (vchan->pchan)
		owl_dma_phy_मुक्त(od, vchan);

	अगर (vchan->txd) अणु
		owl_dma_desc_मुक्त(&vchan->txd->vd);
		vchan->txd = शून्य;
	पूर्ण

	vchan_get_all_descriptors(&vchan->vc, &head);

	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	vchan_dma_desc_मुक्त_list(&vchan->vc, &head);

	वापस 0;
पूर्ण

अटल पूर्णांक owl_dma_config(काष्ठा dma_chan *chan,
			  काष्ठा dma_slave_config *config)
अणु
	काष्ठा owl_dma_vchan *vchan = to_owl_vchan(chan);

	/* Reject definitely invalid configurations */
	अगर (config->src_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES ||
	    config->dst_addr_width == DMA_SLAVE_BUSWIDTH_8_BYTES)
		वापस -EINVAL;

	स_नकल(&vchan->cfg, config, माप(काष्ठा dma_slave_config));

	वापस 0;
पूर्ण

अटल पूर्णांक owl_dma_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा owl_dma_vchan *vchan = to_owl_vchan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vchan->vc.lock, flags);

	owl_dma_छोड़ो_pchan(vchan->pchan);

	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक owl_dma_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा owl_dma_vchan *vchan = to_owl_vchan(chan);
	अचिन्हित दीर्घ flags;

	अगर (!vchan->pchan && !vchan->txd)
		वापस 0;

	dev_dbg(chan2dev(chan), "vchan %p: resume\n", &vchan->vc);

	spin_lock_irqsave(&vchan->vc.lock, flags);

	owl_dma_resume_pchan(vchan->pchan);

	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	वापस 0;
पूर्ण

अटल u32 owl_dma_getbytes_chan(काष्ठा owl_dma_vchan *vchan)
अणु
	काष्ठा owl_dma_pchan *pchan;
	काष्ठा owl_dma_txd *txd;
	काष्ठा owl_dma_lli *lli;
	अचिन्हित पूर्णांक next_lli_phy;
	माप_प्रकार bytes;

	pchan = vchan->pchan;
	txd = vchan->txd;

	अगर (!pchan || !txd)
		वापस 0;

	/* Get reमुख्य count of current node in link list */
	bytes = pchan_पढ़ोl(pchan, OWL_DMAX_REMAIN_CNT);

	/* Loop through the preceding nodes to get total reमुख्यing bytes */
	अगर (pchan_पढ़ोl(pchan, OWL_DMAX_MODE) & OWL_DMA_MODE_LME) अणु
		next_lli_phy = pchan_पढ़ोl(pchan, OWL_DMAX_NEXT_DESCRIPTOR);
		list_क्रम_each_entry(lli, &txd->lli_list, node) अणु
			/* Start from the next active node */
			अगर (lli->phys == next_lli_phy) अणु
				list_क्रम_each_entry(lli, &txd->lli_list, node)
					bytes += llc_hw_flen(lli);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस bytes;
पूर्ण

अटल क्रमागत dma_status owl_dma_tx_status(काष्ठा dma_chan *chan,
					 dma_cookie_t cookie,
					 काष्ठा dma_tx_state *state)
अणु
	काष्ठा owl_dma_vchan *vchan = to_owl_vchan(chan);
	काष्ठा owl_dma_lli *lli;
	काष्ठा virt_dma_desc *vd;
	काष्ठा owl_dma_txd *txd;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;
	माप_प्रकार bytes = 0;

	ret = dma_cookie_status(chan, cookie, state);
	अगर (ret == DMA_COMPLETE || !state)
		वापस ret;

	spin_lock_irqsave(&vchan->vc.lock, flags);

	vd = vchan_find_desc(&vchan->vc, cookie);
	अगर (vd) अणु
		txd = to_owl_txd(&vd->tx);
		list_क्रम_each_entry(lli, &txd->lli_list, node)
			bytes += llc_hw_flen(lli);
	पूर्ण अन्यथा अणु
		bytes = owl_dma_getbytes_chan(vchan);
	पूर्ण

	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	dma_set_residue(state, bytes);

	वापस ret;
पूर्ण

अटल व्योम owl_dma_phy_alloc_and_start(काष्ठा owl_dma_vchan *vchan)
अणु
	काष्ठा owl_dma *od = to_owl_dma(vchan->vc.chan.device);
	काष्ठा owl_dma_pchan *pchan;

	pchan = owl_dma_get_pchan(od, vchan);
	अगर (!pchan)
		वापस;

	dev_dbg(od->dma.dev, "allocated pchan %d\n", pchan->id);

	vchan->pchan = pchan;
	owl_dma_start_next_txd(vchan);
पूर्ण

अटल व्योम owl_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा owl_dma_vchan *vchan = to_owl_vchan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vchan->vc.lock, flags);
	अगर (vchan_issue_pending(&vchan->vc)) अणु
		अगर (!vchan->pchan)
			owl_dma_phy_alloc_and_start(vchan);
	पूर्ण
	spin_unlock_irqrestore(&vchan->vc.lock, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor
		*owl_dma_prep_स_नकल(काष्ठा dma_chan *chan,
				     dma_addr_t dst, dma_addr_t src,
				     माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा owl_dma *od = to_owl_dma(chan->device);
	काष्ठा owl_dma_vchan *vchan = to_owl_vchan(chan);
	काष्ठा owl_dma_txd *txd;
	काष्ठा owl_dma_lli *lli, *prev = शून्य;
	माप_प्रकार offset, bytes;
	पूर्णांक ret;

	अगर (!len)
		वापस शून्य;

	txd = kzalloc(माप(*txd), GFP_NOWAIT);
	अगर (!txd)
		वापस शून्य;

	INIT_LIST_HEAD(&txd->lli_list);

	/* Process the transfer as frame by frame */
	क्रम (offset = 0; offset < len; offset += bytes) अणु
		lli = owl_dma_alloc_lli(od);
		अगर (!lli) अणु
			dev_warn(chan2dev(chan), "failed to allocate lli\n");
			जाओ err_txd_मुक्त;
		पूर्ण

		bytes = min_t(माप_प्रकार, (len - offset), OWL_DMA_FRAME_MAX_LENGTH);

		ret = owl_dma_cfg_lli(vchan, lli, src + offset, dst + offset,
				      bytes, DMA_MEM_TO_MEM,
				      &vchan->cfg, txd->cyclic);
		अगर (ret) अणु
			dev_warn(chan2dev(chan), "failed to config lli\n");
			जाओ err_txd_मुक्त;
		पूर्ण

		prev = owl_dma_add_lli(txd, prev, lli, false);
	पूर्ण

	वापस vchan_tx_prep(&vchan->vc, &txd->vd, flags);

err_txd_मुक्त:
	owl_dma_मुक्त_txd(od, txd);
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor
		*owl_dma_prep_slave_sg(काष्ठा dma_chan *chan,
				       काष्ठा scatterlist *sgl,
				       अचिन्हित पूर्णांक sg_len,
				       क्रमागत dma_transfer_direction dir,
				       अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा owl_dma *od = to_owl_dma(chan->device);
	काष्ठा owl_dma_vchan *vchan = to_owl_vchan(chan);
	काष्ठा dma_slave_config *sconfig = &vchan->cfg;
	काष्ठा owl_dma_txd *txd;
	काष्ठा owl_dma_lli *lli, *prev = शून्य;
	काष्ठा scatterlist *sg;
	dma_addr_t addr, src = 0, dst = 0;
	माप_प्रकार len;
	पूर्णांक ret, i;

	txd = kzalloc(माप(*txd), GFP_NOWAIT);
	अगर (!txd)
		वापस शून्य;

	INIT_LIST_HEAD(&txd->lli_list);

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		addr = sg_dma_address(sg);
		len = sg_dma_len(sg);

		अगर (len > OWL_DMA_FRAME_MAX_LENGTH) अणु
			dev_err(od->dma.dev,
				"frame length exceeds max supported length");
			जाओ err_txd_मुक्त;
		पूर्ण

		lli = owl_dma_alloc_lli(od);
		अगर (!lli) अणु
			dev_err(chan2dev(chan), "failed to allocate lli");
			जाओ err_txd_मुक्त;
		पूर्ण

		अगर (dir == DMA_MEM_TO_DEV) अणु
			src = addr;
			dst = sconfig->dst_addr;
		पूर्ण अन्यथा अणु
			src = sconfig->src_addr;
			dst = addr;
		पूर्ण

		ret = owl_dma_cfg_lli(vchan, lli, src, dst, len, dir, sconfig,
				      txd->cyclic);
		अगर (ret) अणु
			dev_warn(chan2dev(chan), "failed to config lli");
			जाओ err_txd_मुक्त;
		पूर्ण

		prev = owl_dma_add_lli(txd, prev, lli, false);
	पूर्ण

	वापस vchan_tx_prep(&vchan->vc, &txd->vd, flags);

err_txd_मुक्त:
	owl_dma_मुक्त_txd(od, txd);

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor
		*owl_prep_dma_cyclic(काष्ठा dma_chan *chan,
				     dma_addr_t buf_addr, माप_प्रकार buf_len,
				     माप_प्रकार period_len,
				     क्रमागत dma_transfer_direction dir,
				     अचिन्हित दीर्घ flags)
अणु
	काष्ठा owl_dma *od = to_owl_dma(chan->device);
	काष्ठा owl_dma_vchan *vchan = to_owl_vchan(chan);
	काष्ठा dma_slave_config *sconfig = &vchan->cfg;
	काष्ठा owl_dma_txd *txd;
	काष्ठा owl_dma_lli *lli, *prev = शून्य, *first = शून्य;
	dma_addr_t src = 0, dst = 0;
	अचिन्हित पूर्णांक periods = buf_len / period_len;
	पूर्णांक ret, i;

	txd = kzalloc(माप(*txd), GFP_NOWAIT);
	अगर (!txd)
		वापस शून्य;

	INIT_LIST_HEAD(&txd->lli_list);
	txd->cyclic = true;

	क्रम (i = 0; i < periods; i++) अणु
		lli = owl_dma_alloc_lli(od);
		अगर (!lli) अणु
			dev_warn(chan2dev(chan), "failed to allocate lli");
			जाओ err_txd_मुक्त;
		पूर्ण

		अगर (dir == DMA_MEM_TO_DEV) अणु
			src = buf_addr + (period_len * i);
			dst = sconfig->dst_addr;
		पूर्ण अन्यथा अगर (dir == DMA_DEV_TO_MEM) अणु
			src = sconfig->src_addr;
			dst = buf_addr + (period_len * i);
		पूर्ण

		ret = owl_dma_cfg_lli(vchan, lli, src, dst, period_len,
				      dir, sconfig, txd->cyclic);
		अगर (ret) अणु
			dev_warn(chan2dev(chan), "failed to config lli");
			जाओ err_txd_मुक्त;
		पूर्ण

		अगर (!first)
			first = lli;

		prev = owl_dma_add_lli(txd, prev, lli, false);
	पूर्ण

	/* बंद the cyclic list */
	owl_dma_add_lli(txd, prev, first, true);

	वापस vchan_tx_prep(&vchan->vc, &txd->vd, flags);

err_txd_मुक्त:
	owl_dma_मुक्त_txd(od, txd);

	वापस शून्य;
पूर्ण

अटल व्योम owl_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा owl_dma_vchan *vchan = to_owl_vchan(chan);

	/* Ensure all queued descriptors are मुक्तd */
	vchan_मुक्त_chan_resources(&vchan->vc);
पूर्ण

अटल अंतरभूत व्योम owl_dma_मुक्त(काष्ठा owl_dma *od)
अणु
	काष्ठा owl_dma_vchan *vchan = शून्य;
	काष्ठा owl_dma_vchan *next;

	list_क्रम_each_entry_safe(vchan,
				 next, &od->dma.channels, vc.chan.device_node) अणु
		list_del(&vchan->vc.chan.device_node);
		tasklet_समाप्त(&vchan->vc.task);
	पूर्ण
पूर्ण

अटल काष्ठा dma_chan *owl_dma_of_xlate(काष्ठा of_phandle_args *dma_spec,
					 काष्ठा of_dma *ofdma)
अणु
	काष्ठा owl_dma *od = ofdma->of_dma_data;
	काष्ठा owl_dma_vchan *vchan;
	काष्ठा dma_chan *chan;
	u8 drq = dma_spec->args[0];

	अगर (drq > od->nr_vchans)
		वापस शून्य;

	chan = dma_get_any_slave_channel(&od->dma);
	अगर (!chan)
		वापस शून्य;

	vchan = to_owl_vchan(chan);
	vchan->drq = drq;

	वापस chan;
पूर्ण

अटल स्थिर काष्ठा of_device_id owl_dma_match[] = अणु
	अणु .compatible = "actions,s500-dma", .data = (व्योम *)S900_DMA,पूर्ण,
	अणु .compatible = "actions,s700-dma", .data = (व्योम *)S700_DMA,पूर्ण,
	अणु .compatible = "actions,s900-dma", .data = (व्योम *)S900_DMA,पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, owl_dma_match);

अटल पूर्णांक owl_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा owl_dma *od;
	पूर्णांक ret, i, nr_channels, nr_requests;

	od = devm_kzalloc(&pdev->dev, माप(*od), GFP_KERNEL);
	अगर (!od)
		वापस -ENOMEM;

	od->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(od->base))
		वापस PTR_ERR(od->base);

	ret = of_property_पढ़ो_u32(np, "dma-channels", &nr_channels);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't get dma-channels\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "dma-requests", &nr_requests);
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't get dma-requests\n");
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "dma-channels %d, dma-requests %d\n",
		 nr_channels, nr_requests);

	od->devid = (क्रमागत owl_dma_id)of_device_get_match_data(&pdev->dev);

	od->nr_pchans = nr_channels;
	od->nr_vchans = nr_requests;

	pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);

	platक्रमm_set_drvdata(pdev, od);
	spin_lock_init(&od->lock);

	dma_cap_set(DMA_MEMCPY, od->dma.cap_mask);
	dma_cap_set(DMA_SLAVE, od->dma.cap_mask);
	dma_cap_set(DMA_CYCLIC, od->dma.cap_mask);

	od->dma.dev = &pdev->dev;
	od->dma.device_मुक्त_chan_resources = owl_dma_मुक्त_chan_resources;
	od->dma.device_tx_status = owl_dma_tx_status;
	od->dma.device_issue_pending = owl_dma_issue_pending;
	od->dma.device_prep_dma_स_नकल = owl_dma_prep_स_नकल;
	od->dma.device_prep_slave_sg = owl_dma_prep_slave_sg;
	od->dma.device_prep_dma_cyclic = owl_prep_dma_cyclic;
	od->dma.device_config = owl_dma_config;
	od->dma.device_छोड़ो = owl_dma_छोड़ो;
	od->dma.device_resume = owl_dma_resume;
	od->dma.device_terminate_all = owl_dma_terminate_all;
	od->dma.src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	od->dma.dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	od->dma.directions = BIT(DMA_MEM_TO_MEM);
	od->dma.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

	INIT_LIST_HEAD(&od->dma.channels);

	od->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(od->clk)) अणु
		dev_err(&pdev->dev, "unable to get clock\n");
		वापस PTR_ERR(od->clk);
	पूर्ण

	/*
	 * Eventhough the DMA controller is capable of generating 4
	 * IRQ's क्रम DMA priority feature, we only use 1 IRQ क्रम
	 * simplअगरication.
	 */
	od->irq = platक्रमm_get_irq(pdev, 0);
	ret = devm_request_irq(&pdev->dev, od->irq, owl_dma_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), od);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to request IRQ\n");
		वापस ret;
	पूर्ण

	/* Init physical channel */
	od->pchans = devm_kसुस्मृति(&pdev->dev, od->nr_pchans,
				  माप(काष्ठा owl_dma_pchan), GFP_KERNEL);
	अगर (!od->pchans)
		वापस -ENOMEM;

	क्रम (i = 0; i < od->nr_pchans; i++) अणु
		काष्ठा owl_dma_pchan *pchan = &od->pchans[i];

		pchan->id = i;
		pchan->base = od->base + OWL_DMA_CHAN_BASE(i);
	पूर्ण

	/* Init भव channel */
	od->vchans = devm_kसुस्मृति(&pdev->dev, od->nr_vchans,
				  माप(काष्ठा owl_dma_vchan), GFP_KERNEL);
	अगर (!od->vchans)
		वापस -ENOMEM;

	क्रम (i = 0; i < od->nr_vchans; i++) अणु
		काष्ठा owl_dma_vchan *vchan = &od->vchans[i];

		vchan->vc.desc_मुक्त = owl_dma_desc_मुक्त;
		vchan_init(&vchan->vc, &od->dma);
	पूर्ण

	/* Create a pool of consistent memory blocks क्रम hardware descriptors */
	od->lli_pool = dma_pool_create(dev_name(od->dma.dev), od->dma.dev,
				       माप(काष्ठा owl_dma_lli),
				       __alignof__(काष्ठा owl_dma_lli),
				       0);
	अगर (!od->lli_pool) अणु
		dev_err(&pdev->dev, "unable to allocate DMA descriptor pool\n");
		वापस -ENOMEM;
	पूर्ण

	clk_prepare_enable(od->clk);

	ret = dma_async_device_रेजिस्टर(&od->dma);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register DMA engine device\n");
		जाओ err_pool_मुक्त;
	पूर्ण

	/* Device-tree DMA controller registration */
	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
					 owl_dma_of_xlate, od);
	अगर (ret) अणु
		dev_err(&pdev->dev, "of_dma_controller_register failed\n");
		जाओ err_dma_unरेजिस्टर;
	पूर्ण

	वापस 0;

err_dma_unरेजिस्टर:
	dma_async_device_unरेजिस्टर(&od->dma);
err_pool_मुक्त:
	clk_disable_unprepare(od->clk);
	dma_pool_destroy(od->lli_pool);

	वापस ret;
पूर्ण

अटल पूर्णांक owl_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा owl_dma *od = platक्रमm_get_drvdata(pdev);

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&od->dma);

	/* Mask all पूर्णांकerrupts क्रम this execution environment */
	dma_ग_लिखोl(od, OWL_DMA_IRQ_EN0, 0x0);

	/* Make sure we won't have any further पूर्णांकerrupts */
	devm_मुक्त_irq(od->dma.dev, od->irq, od);

	owl_dma_मुक्त(od);

	clk_disable_unprepare(od->clk);
	dma_pool_destroy(od->lli_pool);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver owl_dma_driver = अणु
	.probe	= owl_dma_probe,
	.हटाओ	= owl_dma_हटाओ,
	.driver = अणु
		.name = "dma-owl",
		.of_match_table = of_match_ptr(owl_dma_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक owl_dma_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&owl_dma_driver);
पूर्ण
subsys_initcall(owl_dma_init);

अटल व्योम __निकास owl_dma_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&owl_dma_driver);
पूर्ण
module_निकास(owl_dma_निकास);

MODULE_AUTHOR("David Liu <liuwei@actions-semi.com>");
MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_DESCRIPTION("Actions Semi Owl SoCs DMA driver");
MODULE_LICENSE("GPL");
