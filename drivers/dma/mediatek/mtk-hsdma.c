<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017-2018 MediaTek Inc.

/*
 * Driver क्रम MediaTek High-Speed DMA Controller
 *
 * Author: Sean Wang <sean.wang@mediatek.com>
 *
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/refcount.h>
#समावेश <linux/slab.h>

#समावेश "../virt-dma.h"

#घोषणा MTK_HSDMA_USEC_POLL		20
#घोषणा MTK_HSDMA_TIMEOUT_POLL		200000
#घोषणा MTK_HSDMA_DMA_BUSWIDTHS		BIT(DMA_SLAVE_BUSWIDTH_4_BYTES)

/* The शेष number of भव channel */
#घोषणा MTK_HSDMA_NR_VCHANS		3

/* Only one physical channel supported */
#घोषणा MTK_HSDMA_NR_MAX_PCHANS		1

/* Macro क्रम physical descriptor (PD) manipulation */
/* The number of PD which must be 2 of घातer */
#घोषणा MTK_DMA_SIZE			64
#घोषणा MTK_HSDMA_NEXT_DESP_IDX(x, y)	(((x) + 1) & ((y) - 1))
#घोषणा MTK_HSDMA_LAST_DESP_IDX(x, y)	(((x) - 1) & ((y) - 1))
#घोषणा MTK_HSDMA_MAX_LEN		0x3f80
#घोषणा MTK_HSDMA_ALIGN_SIZE		4
#घोषणा MTK_HSDMA_PLEN_MASK		0x3fff
#घोषणा MTK_HSDMA_DESC_PLEN(x)		(((x) & MTK_HSDMA_PLEN_MASK) << 16)
#घोषणा MTK_HSDMA_DESC_PLEN_GET(x)	(((x) >> 16) & MTK_HSDMA_PLEN_MASK)

/* Registers क्रम underlying ring manipulation */
#घोषणा MTK_HSDMA_TX_BASE		0x0
#घोषणा MTK_HSDMA_TX_CNT		0x4
#घोषणा MTK_HSDMA_TX_CPU		0x8
#घोषणा MTK_HSDMA_TX_DMA		0xc
#घोषणा MTK_HSDMA_RX_BASE		0x100
#घोषणा MTK_HSDMA_RX_CNT		0x104
#घोषणा MTK_HSDMA_RX_CPU		0x108
#घोषणा MTK_HSDMA_RX_DMA		0x10c

/* Registers क्रम global setup */
#घोषणा MTK_HSDMA_GLO			0x204
#घोषणा MTK_HSDMA_GLO_MULTI_DMA		BIT(10)
#घोषणा MTK_HSDMA_TX_WB_DDONE		BIT(6)
#घोषणा MTK_HSDMA_BURST_64BYTES		(0x2 << 4)
#घोषणा MTK_HSDMA_GLO_RX_BUSY		BIT(3)
#घोषणा MTK_HSDMA_GLO_RX_DMA		BIT(2)
#घोषणा MTK_HSDMA_GLO_TX_BUSY		BIT(1)
#घोषणा MTK_HSDMA_GLO_TX_DMA		BIT(0)
#घोषणा MTK_HSDMA_GLO_DMA		(MTK_HSDMA_GLO_TX_DMA |	\
					 MTK_HSDMA_GLO_RX_DMA)
#घोषणा MTK_HSDMA_GLO_BUSY		(MTK_HSDMA_GLO_RX_BUSY | \
					 MTK_HSDMA_GLO_TX_BUSY)
#घोषणा MTK_HSDMA_GLO_DEFAULT		(MTK_HSDMA_GLO_TX_DMA | \
					 MTK_HSDMA_GLO_RX_DMA | \
					 MTK_HSDMA_TX_WB_DDONE | \
					 MTK_HSDMA_BURST_64BYTES | \
					 MTK_HSDMA_GLO_MULTI_DMA)

/* Registers क्रम reset */
#घोषणा MTK_HSDMA_RESET			0x208
#घोषणा MTK_HSDMA_RST_TX		BIT(0)
#घोषणा MTK_HSDMA_RST_RX		BIT(16)

/* Registers क्रम पूर्णांकerrupt control */
#घोषणा MTK_HSDMA_DLYINT		0x20c
#घोषणा MTK_HSDMA_RXDLY_INT_EN		BIT(15)

/* Interrupt fires when the pending number's more than the specअगरied */
#घोषणा MTK_HSDMA_RXMAX_PINT(x)		(((x) & 0x7f) << 8)

/* Interrupt fires when the pending समय's more than the specअगरied in 20 us */
#घोषणा MTK_HSDMA_RXMAX_PTIME(x)	((x) & 0x7f)
#घोषणा MTK_HSDMA_DLYINT_DEFAULT	(MTK_HSDMA_RXDLY_INT_EN | \
					 MTK_HSDMA_RXMAX_PINT(20) | \
					 MTK_HSDMA_RXMAX_PTIME(20))
#घोषणा MTK_HSDMA_INT_STATUS		0x220
#घोषणा MTK_HSDMA_INT_ENABLE		0x228
#घोषणा MTK_HSDMA_INT_RXDONE		BIT(16)

क्रमागत mtk_hsdma_vdesc_flag अणु
	MTK_HSDMA_VDESC_FINISHED	= 0x01,
पूर्ण;

#घोषणा IS_MTK_HSDMA_VDESC_FINISHED(x) ((x) == MTK_HSDMA_VDESC_FINISHED)

/**
 * काष्ठा mtk_hsdma_pdesc - This is the काष्ठा holding info describing physical
 *			    descriptor (PD) and its placement must be kept at
 *			    4-bytes alignment in little endian order.
 * @desc1:		    | The control pad used to indicate hardware how to
 * @desc2:		    | deal with the descriptor such as source and
 * @desc3:		    | destination address and data length. The maximum
 * @desc4:		    | data length each pdesc can handle is 0x3f80 bytes
 */
काष्ठा mtk_hsdma_pdesc अणु
	__le32 desc1;
	__le32 desc2;
	__le32 desc3;
	__le32 desc4;
पूर्ण __packed __aligned(4);

/**
 * काष्ठा mtk_hsdma_vdesc - This is the काष्ठा holding info describing भव
 *			    descriptor (VD)
 * @vd:			    An instance क्रम काष्ठा virt_dma_desc
 * @len:		    The total data size device wants to move
 * @residue:		    The reमुख्यing data size device will move
 * @dest:		    The destination address device wants to move to
 * @src:		    The source address device wants to move from
 */
काष्ठा mtk_hsdma_vdesc अणु
	काष्ठा virt_dma_desc vd;
	माप_प्रकार len;
	माप_प्रकार residue;
	dma_addr_t dest;
	dma_addr_t src;
पूर्ण;

/**
 * काष्ठा mtk_hsdma_cb - This is the काष्ठा holding extra info required क्रम RX
 *			 ring to know what relevant VD the the PD is being
 *			 mapped to.
 * @vd:			 Poपूर्णांकer to the relevant VD.
 * @flag:		 Flag indicating what action should be taken when VD
 *			 is completed.
 */
काष्ठा mtk_hsdma_cb अणु
	काष्ठा virt_dma_desc *vd;
	क्रमागत mtk_hsdma_vdesc_flag flag;
पूर्ण;

/**
 * काष्ठा mtk_hsdma_ring - This काष्ठा holds info describing underlying ring
 *			   space
 * @txd:		   The descriptor TX ring which describes DMA source
 *			   inक्रमmation
 * @rxd:		   The descriptor RX ring which describes DMA
 *			   destination inक्रमmation
 * @cb:			   The extra inक्रमmation poपूर्णांकed at by RX ring
 * @tphys:		   The physical addr of TX ring
 * @rphys:		   The physical addr of RX ring
 * @cur_tptr:		   Poपूर्णांकer to the next मुक्त descriptor used by the host
 * @cur_rptr:		   Poपूर्णांकer to the last करोne descriptor by the device
 */
काष्ठा mtk_hsdma_ring अणु
	काष्ठा mtk_hsdma_pdesc *txd;
	काष्ठा mtk_hsdma_pdesc *rxd;
	काष्ठा mtk_hsdma_cb *cb;
	dma_addr_t tphys;
	dma_addr_t rphys;
	u16 cur_tptr;
	u16 cur_rptr;
पूर्ण;

/**
 * काष्ठा mtk_hsdma_pchan - This is the काष्ठा holding info describing physical
 *			   channel (PC)
 * @ring:		   An instance क्रम the underlying ring
 * @sz_ring:		   Total size allocated क्रम the ring
 * @nr_मुक्त:		   Total number of मुक्त rooms in the ring. It would
 *			   be accessed and updated frequently between IRQ
 *			   context and user context to reflect whether ring
 *			   can accept requests from VD.
 */
काष्ठा mtk_hsdma_pchan अणु
	काष्ठा mtk_hsdma_ring ring;
	माप_प्रकार sz_ring;
	atomic_t nr_मुक्त;
पूर्ण;

/**
 * काष्ठा mtk_hsdma_vchan - This is the काष्ठा holding info describing भव
 *			   channel (VC)
 * @vc:			   An instance क्रम काष्ठा virt_dma_chan
 * @issue_completion:	   The रुको क्रम all issued descriptors completited
 * @issue_synchronize:	   Bool indicating channel synchronization starts
 * @desc_hw_processing:	   List those descriptors the hardware is processing,
 *			   which is रक्षित by vc.lock
 */
काष्ठा mtk_hsdma_vchan अणु
	काष्ठा virt_dma_chan vc;
	काष्ठा completion issue_completion;
	bool issue_synchronize;
	काष्ठा list_head desc_hw_processing;
पूर्ण;

/**
 * काष्ठा mtk_hsdma_soc - This is the काष्ठा holding dअगरferences among SoCs
 * @dकरोne:		  Bit mask क्रम DDONE
 * @ls0:		  Bit mask क्रम LS0
 */
काष्ठा mtk_hsdma_soc अणु
	__le32 dकरोne;
	__le32 ls0;
पूर्ण;

/**
 * काष्ठा mtk_hsdma_device - This is the काष्ठा holding info describing HSDMA
 *			     device
 * @ddev:		     An instance क्रम काष्ठा dma_device
 * @base:		     The mapped रेजिस्टर I/O base
 * @clk:		     The घड़ी that device पूर्णांकernal is using
 * @irq:		     The IRQ that device are using
 * @dma_requests:	     The number of VCs the device supports to
 * @vc:			     The poपूर्णांकer to all available VCs
 * @pc:			     The poपूर्णांकer to the underlying PC
 * @pc_refcnt:		     Track how many VCs are using the PC
 * @lock:		     Lock protect agaisting multiple VCs access PC
 * @soc:		     The poपूर्णांकer to area holding dअगरferences among
 *			     vaious platक्रमm
 */
काष्ठा mtk_hsdma_device अणु
	काष्ठा dma_device ddev;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	u32 irq;

	u32 dma_requests;
	काष्ठा mtk_hsdma_vchan *vc;
	काष्ठा mtk_hsdma_pchan *pc;
	refcount_t pc_refcnt;

	/* Lock used to protect against multiple VCs access PC */
	spinlock_t lock;

	स्थिर काष्ठा mtk_hsdma_soc *soc;
पूर्ण;

अटल काष्ठा mtk_hsdma_device *to_hsdma_dev(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan->device, काष्ठा mtk_hsdma_device, ddev);
पूर्ण

अटल अंतरभूत काष्ठा mtk_hsdma_vchan *to_hsdma_vchan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा mtk_hsdma_vchan, vc.chan);
पूर्ण

अटल काष्ठा mtk_hsdma_vdesc *to_hsdma_vdesc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा mtk_hsdma_vdesc, vd);
पूर्ण

अटल काष्ठा device *hsdma2dev(काष्ठा mtk_hsdma_device *hsdma)
अणु
	वापस hsdma->ddev.dev;
पूर्ण

अटल u32 mtk_dma_पढ़ो(काष्ठा mtk_hsdma_device *hsdma, u32 reg)
अणु
	वापस पढ़ोl(hsdma->base + reg);
पूर्ण

अटल व्योम mtk_dma_ग_लिखो(काष्ठा mtk_hsdma_device *hsdma, u32 reg, u32 val)
अणु
	ग_लिखोl(val, hsdma->base + reg);
पूर्ण

अटल व्योम mtk_dma_rmw(काष्ठा mtk_hsdma_device *hsdma, u32 reg,
			u32 mask, u32 set)
अणु
	u32 val;

	val = mtk_dma_पढ़ो(hsdma, reg);
	val &= ~mask;
	val |= set;
	mtk_dma_ग_लिखो(hsdma, reg, val);
पूर्ण

अटल व्योम mtk_dma_set(काष्ठा mtk_hsdma_device *hsdma, u32 reg, u32 val)
अणु
	mtk_dma_rmw(hsdma, reg, 0, val);
पूर्ण

अटल व्योम mtk_dma_clr(काष्ठा mtk_hsdma_device *hsdma, u32 reg, u32 val)
अणु
	mtk_dma_rmw(hsdma, reg, val, 0);
पूर्ण

अटल व्योम mtk_hsdma_vdesc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	kमुक्त(container_of(vd, काष्ठा mtk_hsdma_vdesc, vd));
पूर्ण

अटल पूर्णांक mtk_hsdma_busy_रुको(काष्ठा mtk_hsdma_device *hsdma)
अणु
	u32 status = 0;

	वापस पढ़ोl_poll_समयout(hsdma->base + MTK_HSDMA_GLO, status,
				  !(status & MTK_HSDMA_GLO_BUSY),
				  MTK_HSDMA_USEC_POLL,
				  MTK_HSDMA_TIMEOUT_POLL);
पूर्ण

अटल पूर्णांक mtk_hsdma_alloc_pchan(काष्ठा mtk_hsdma_device *hsdma,
				 काष्ठा mtk_hsdma_pchan *pc)
अणु
	काष्ठा mtk_hsdma_ring *ring = &pc->ring;
	पूर्णांक err;

	स_रखो(pc, 0, माप(*pc));

	/*
	 * Allocate ring space where [0 ... MTK_DMA_SIZE - 1] is क्रम TX ring
	 * and [MTK_DMA_SIZE ... 2 * MTK_DMA_SIZE - 1] is क्रम RX ring.
	 */
	pc->sz_ring = 2 * MTK_DMA_SIZE * माप(*ring->txd);
	ring->txd = dma_alloc_coherent(hsdma2dev(hsdma), pc->sz_ring,
				       &ring->tphys, GFP_NOWAIT);
	अगर (!ring->txd)
		वापस -ENOMEM;

	ring->rxd = &ring->txd[MTK_DMA_SIZE];
	ring->rphys = ring->tphys + MTK_DMA_SIZE * माप(*ring->txd);
	ring->cur_tptr = 0;
	ring->cur_rptr = MTK_DMA_SIZE - 1;

	ring->cb = kसुस्मृति(MTK_DMA_SIZE, माप(*ring->cb), GFP_NOWAIT);
	अगर (!ring->cb) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_dma;
	पूर्ण

	atomic_set(&pc->nr_मुक्त, MTK_DMA_SIZE - 1);

	/* Disable HSDMA and रुको क्रम the completion */
	mtk_dma_clr(hsdma, MTK_HSDMA_GLO, MTK_HSDMA_GLO_DMA);
	err = mtk_hsdma_busy_रुको(hsdma);
	अगर (err)
		जाओ err_मुक्त_cb;

	/* Reset */
	mtk_dma_set(hsdma, MTK_HSDMA_RESET,
		    MTK_HSDMA_RST_TX | MTK_HSDMA_RST_RX);
	mtk_dma_clr(hsdma, MTK_HSDMA_RESET,
		    MTK_HSDMA_RST_TX | MTK_HSDMA_RST_RX);

	/* Setup HSDMA initial poपूर्णांकer in the ring */
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_TX_BASE, ring->tphys);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_TX_CNT, MTK_DMA_SIZE);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_TX_CPU, ring->cur_tptr);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_TX_DMA, 0);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_RX_BASE, ring->rphys);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_RX_CNT, MTK_DMA_SIZE);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_RX_CPU, ring->cur_rptr);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_RX_DMA, 0);

	/* Enable HSDMA */
	mtk_dma_set(hsdma, MTK_HSDMA_GLO, MTK_HSDMA_GLO_DMA);

	/* Setup delayed पूर्णांकerrupt */
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_DLYINT, MTK_HSDMA_DLYINT_DEFAULT);

	/* Enable पूर्णांकerrupt */
	mtk_dma_set(hsdma, MTK_HSDMA_INT_ENABLE, MTK_HSDMA_INT_RXDONE);

	वापस 0;

err_मुक्त_cb:
	kमुक्त(ring->cb);

err_मुक्त_dma:
	dma_मुक्त_coherent(hsdma2dev(hsdma),
			  pc->sz_ring, ring->txd, ring->tphys);
	वापस err;
पूर्ण

अटल व्योम mtk_hsdma_मुक्त_pchan(काष्ठा mtk_hsdma_device *hsdma,
				 काष्ठा mtk_hsdma_pchan *pc)
अणु
	काष्ठा mtk_hsdma_ring *ring = &pc->ring;

	/* Disable HSDMA and then रुको क्रम the completion */
	mtk_dma_clr(hsdma, MTK_HSDMA_GLO, MTK_HSDMA_GLO_DMA);
	mtk_hsdma_busy_रुको(hsdma);

	/* Reset poपूर्णांकer in the ring */
	mtk_dma_clr(hsdma, MTK_HSDMA_INT_ENABLE, MTK_HSDMA_INT_RXDONE);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_TX_BASE, 0);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_TX_CNT, 0);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_TX_CPU, 0);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_RX_BASE, 0);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_RX_CNT, 0);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_RX_CPU, MTK_DMA_SIZE - 1);

	kमुक्त(ring->cb);

	dma_मुक्त_coherent(hsdma2dev(hsdma),
			  pc->sz_ring, ring->txd, ring->tphys);
पूर्ण

अटल पूर्णांक mtk_hsdma_issue_pending_vdesc(काष्ठा mtk_hsdma_device *hsdma,
					 काष्ठा mtk_hsdma_pchan *pc,
					 काष्ठा mtk_hsdma_vdesc *hvd)
अणु
	काष्ठा mtk_hsdma_ring *ring = &pc->ring;
	काष्ठा mtk_hsdma_pdesc *txd, *rxd;
	u16 reserved, prev, tlen, num_sgs;
	अचिन्हित दीर्घ flags;

	/* Protect against PC is accessed by multiple VCs simultaneously */
	spin_lock_irqsave(&hsdma->lock, flags);

	/*
	 * Reserve rooms, where pc->nr_मुक्त is used to track how many मुक्त
	 * rooms in the ring being updated in user and IRQ context.
	 */
	num_sgs = DIV_ROUND_UP(hvd->len, MTK_HSDMA_MAX_LEN);
	reserved = min_t(u16, num_sgs, atomic_पढ़ो(&pc->nr_मुक्त));

	अगर (!reserved) अणु
		spin_unlock_irqrestore(&hsdma->lock, flags);
		वापस -ENOSPC;
	पूर्ण

	atomic_sub(reserved, &pc->nr_मुक्त);

	जबतक (reserved--) अणु
		/* Limit size by PD capability क्रम valid data moving */
		tlen = (hvd->len > MTK_HSDMA_MAX_LEN) ?
		       MTK_HSDMA_MAX_LEN : hvd->len;

		/*
		 * Setup PDs using the reमुख्यing VD info mapped on those
		 * reserved rooms. And since RXD is shared memory between the
		 * host and the device allocated by dma_alloc_coherent call,
		 * the helper macro WRITE_ONCE can ensure the data written to
		 * RAM would really happens.
		 */
		txd = &ring->txd[ring->cur_tptr];
		WRITE_ONCE(txd->desc1, hvd->src);
		WRITE_ONCE(txd->desc2,
			   hsdma->soc->ls0 | MTK_HSDMA_DESC_PLEN(tlen));

		rxd = &ring->rxd[ring->cur_tptr];
		WRITE_ONCE(rxd->desc1, hvd->dest);
		WRITE_ONCE(rxd->desc2, MTK_HSDMA_DESC_PLEN(tlen));

		/* Associate VD, the PD beदीर्घed to */
		ring->cb[ring->cur_tptr].vd = &hvd->vd;

		/* Move क्रमward the poपूर्णांकer of TX ring */
		ring->cur_tptr = MTK_HSDMA_NEXT_DESP_IDX(ring->cur_tptr,
							 MTK_DMA_SIZE);

		/* Update VD with reमुख्यing data */
		hvd->src  += tlen;
		hvd->dest += tlen;
		hvd->len  -= tlen;
	पूर्ण

	/*
	 * Tagging flag क्रम the last PD क्रम VD will be responsible क्रम
	 * completing VD.
	 */
	अगर (!hvd->len) अणु
		prev = MTK_HSDMA_LAST_DESP_IDX(ring->cur_tptr, MTK_DMA_SIZE);
		ring->cb[prev].flag = MTK_HSDMA_VDESC_FINISHED;
	पूर्ण

	/* Ensure all changes indeed करोne beक्रमe we're going on */
	wmb();

	/*
	 * Updating पूर्णांकo hardware the poपूर्णांकer of TX ring lets HSDMA to take
	 * action क्रम those pending PDs.
	 */
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_TX_CPU, ring->cur_tptr);

	spin_unlock_irqrestore(&hsdma->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम mtk_hsdma_issue_vchan_pending(काष्ठा mtk_hsdma_device *hsdma,
					  काष्ठा mtk_hsdma_vchan *hvc)
अणु
	काष्ठा virt_dma_desc *vd, *vd2;
	पूर्णांक err;

	lockdep_निश्चित_held(&hvc->vc.lock);

	list_क्रम_each_entry_safe(vd, vd2, &hvc->vc.desc_issued, node) अणु
		काष्ठा mtk_hsdma_vdesc *hvd;

		hvd = to_hsdma_vdesc(vd);

		/* Map VD पूर्णांकo PC and all VCs shares a single PC */
		err = mtk_hsdma_issue_pending_vdesc(hsdma, hsdma->pc, hvd);

		/*
		 * Move VD from desc_issued to desc_hw_processing when entire
		 * VD is fit पूर्णांकo available PDs. Otherwise, the uncompleted
		 * VDs would stay in list desc_issued and then restart the
		 * processing as soon as possible once underlying ring space
		 * got मुक्तd.
		 */
		अगर (err == -ENOSPC || hvd->len > 0)
			अवरोध;

		/*
		 * The extra list desc_hw_processing is used because
		 * hardware can't provide sufficient inक्रमmation allowing us
		 * to know what VDs are still working on the underlying ring.
		 * Through the additional list, it can help us to implement
		 * terminate_all, residue calculation and such thing needed
		 * to know detail descriptor status on the hardware.
		 */
		list_move_tail(&vd->node, &hvc->desc_hw_processing);
	पूर्ण
पूर्ण

अटल व्योम mtk_hsdma_मुक्त_rooms_in_ring(काष्ठा mtk_hsdma_device *hsdma)
अणु
	काष्ठा mtk_hsdma_vchan *hvc;
	काष्ठा mtk_hsdma_pdesc *rxd;
	काष्ठा mtk_hsdma_vdesc *hvd;
	काष्ठा mtk_hsdma_pchan *pc;
	काष्ठा mtk_hsdma_cb *cb;
	पूर्णांक i = MTK_DMA_SIZE;
	__le32 desc2;
	u32 status;
	u16 next;

	/* Read IRQ status */
	status = mtk_dma_पढ़ो(hsdma, MTK_HSDMA_INT_STATUS);
	अगर (unlikely(!(status & MTK_HSDMA_INT_RXDONE)))
		जाओ rx_करोne;

	pc = hsdma->pc;

	/*
	 * Using a fail-safe loop with iterations of up to MTK_DMA_SIZE to
	 * reclaim these finished descriptors: The most number of PDs the ISR
	 * can handle at one समय shouldn't be more than MTK_DMA_SIZE so we
	 * take it as limited count instead of just using a dangerous infinite
	 * poll.
	 */
	जबतक (i--) अणु
		next = MTK_HSDMA_NEXT_DESP_IDX(pc->ring.cur_rptr,
					       MTK_DMA_SIZE);
		rxd = &pc->ring.rxd[next];

		/*
		 * If MTK_HSDMA_DESC_DDONE is no specअगरied, that means data
		 * moving क्रम the PD is still under going.
		 */
		desc2 = READ_ONCE(rxd->desc2);
		अगर (!(desc2 & hsdma->soc->dकरोne))
			अवरोध;

		cb = &pc->ring.cb[next];
		अगर (unlikely(!cb->vd)) अणु
			dev_err(hsdma2dev(hsdma), "cb->vd cannot be null\n");
			अवरोध;
		पूर्ण

		/* Update residue of VD the associated PD beदीर्घed to */
		hvd = to_hsdma_vdesc(cb->vd);
		hvd->residue -= MTK_HSDMA_DESC_PLEN_GET(rxd->desc2);

		/* Complete VD until the relevant last PD is finished */
		अगर (IS_MTK_HSDMA_VDESC_FINISHED(cb->flag)) अणु
			hvc = to_hsdma_vchan(cb->vd->tx.chan);

			spin_lock(&hvc->vc.lock);

			/* Remove VD from list desc_hw_processing */
			list_del(&cb->vd->node);

			/* Add VD पूर्णांकo list desc_completed */
			vchan_cookie_complete(cb->vd);

			अगर (hvc->issue_synchronize &&
			    list_empty(&hvc->desc_hw_processing)) अणु
				complete(&hvc->issue_completion);
				hvc->issue_synchronize = false;
			पूर्ण
			spin_unlock(&hvc->vc.lock);

			cb->flag = 0;
		पूर्ण

		cb->vd = 0;

		/*
		 * Recycle the RXD with the helper WRITE_ONCE that can ensure
		 * data written पूर्णांकo RAM would really happens.
		 */
		WRITE_ONCE(rxd->desc1, 0);
		WRITE_ONCE(rxd->desc2, 0);
		pc->ring.cur_rptr = next;

		/* Release rooms */
		atomic_inc(&pc->nr_मुक्त);
	पूर्ण

	/* Ensure all changes indeed करोne beक्रमe we're going on */
	wmb();

	/* Update CPU poपूर्णांकer क्रम those completed PDs */
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_RX_CPU, pc->ring.cur_rptr);

	/*
	 * Acking the pending IRQ allows hardware no दीर्घer to keep the used
	 * IRQ line in certain trigger state when software has completed all
	 * the finished physical descriptors.
	 */
	अगर (atomic_पढ़ो(&pc->nr_मुक्त) >= MTK_DMA_SIZE - 1)
		mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_INT_STATUS, status);

	/* ASAP handles pending VDs in all VCs after मुक्तing some rooms */
	क्रम (i = 0; i < hsdma->dma_requests; i++) अणु
		hvc = &hsdma->vc[i];
		spin_lock(&hvc->vc.lock);
		mtk_hsdma_issue_vchan_pending(hsdma, hvc);
		spin_unlock(&hvc->vc.lock);
	पूर्ण

rx_करोne:
	/* All completed PDs are cleaned up, so enable पूर्णांकerrupt again */
	mtk_dma_set(hsdma, MTK_HSDMA_INT_ENABLE, MTK_HSDMA_INT_RXDONE);
पूर्ण

अटल irqवापस_t mtk_hsdma_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा mtk_hsdma_device *hsdma = devid;

	/*
	 * Disable पूर्णांकerrupt until all completed PDs are cleaned up in
	 * mtk_hsdma_मुक्त_rooms call.
	 */
	mtk_dma_clr(hsdma, MTK_HSDMA_INT_ENABLE, MTK_HSDMA_INT_RXDONE);

	mtk_hsdma_मुक्त_rooms_in_ring(hsdma);

	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा virt_dma_desc *mtk_hsdma_find_active_desc(काष्ठा dma_chan *c,
							dma_cookie_t cookie)
अणु
	काष्ठा mtk_hsdma_vchan *hvc = to_hsdma_vchan(c);
	काष्ठा virt_dma_desc *vd;

	list_क्रम_each_entry(vd, &hvc->desc_hw_processing, node)
		अगर (vd->tx.cookie == cookie)
			वापस vd;

	list_क्रम_each_entry(vd, &hvc->vc.desc_issued, node)
		अगर (vd->tx.cookie == cookie)
			वापस vd;

	वापस शून्य;
पूर्ण

अटल क्रमागत dma_status mtk_hsdma_tx_status(काष्ठा dma_chan *c,
					   dma_cookie_t cookie,
					   काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा mtk_hsdma_vchan *hvc = to_hsdma_vchan(c);
	काष्ठा mtk_hsdma_vdesc *hvd;
	काष्ठा virt_dma_desc *vd;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;
	माप_प्रकार bytes = 0;

	ret = dma_cookie_status(c, cookie, txstate);
	अगर (ret == DMA_COMPLETE || !txstate)
		वापस ret;

	spin_lock_irqsave(&hvc->vc.lock, flags);
	vd = mtk_hsdma_find_active_desc(c, cookie);
	spin_unlock_irqrestore(&hvc->vc.lock, flags);

	अगर (vd) अणु
		hvd = to_hsdma_vdesc(vd);
		bytes = hvd->residue;
	पूर्ण

	dma_set_residue(txstate, bytes);

	वापस ret;
पूर्ण

अटल व्योम mtk_hsdma_issue_pending(काष्ठा dma_chan *c)
अणु
	काष्ठा mtk_hsdma_device *hsdma = to_hsdma_dev(c);
	काष्ठा mtk_hsdma_vchan *hvc = to_hsdma_vchan(c);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hvc->vc.lock, flags);

	अगर (vchan_issue_pending(&hvc->vc))
		mtk_hsdma_issue_vchan_pending(hsdma, hvc);

	spin_unlock_irqrestore(&hvc->vc.lock, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
mtk_hsdma_prep_dma_स_नकल(काष्ठा dma_chan *c, dma_addr_t dest,
			  dma_addr_t src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mtk_hsdma_vdesc *hvd;

	hvd = kzalloc(माप(*hvd), GFP_NOWAIT);
	अगर (!hvd)
		वापस शून्य;

	hvd->len = len;
	hvd->residue = len;
	hvd->src = src;
	hvd->dest = dest;

	वापस vchan_tx_prep(to_virt_chan(c), &hvd->vd, flags);
पूर्ण

अटल पूर्णांक mtk_hsdma_मुक्त_inactive_desc(काष्ठा dma_chan *c)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(c);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&vc->lock, flags);
	list_splice_tail_init(&vc->desc_allocated, &head);
	list_splice_tail_init(&vc->desc_submitted, &head);
	list_splice_tail_init(&vc->desc_issued, &head);
	spin_unlock_irqrestore(&vc->lock, flags);

	/* At the poपूर्णांक, we करोn't expect users put descriptor पूर्णांकo VC again */
	vchan_dma_desc_मुक्त_list(vc, &head);

	वापस 0;
पूर्ण

अटल व्योम mtk_hsdma_मुक्त_active_desc(काष्ठा dma_chan *c)
अणु
	काष्ठा mtk_hsdma_vchan *hvc = to_hsdma_vchan(c);
	bool sync_needed = false;

	/*
	 * Once issue_synchronize is being set, which means once the hardware
	 * consumes all descriptors क्रम the channel in the ring, the
	 * synchronization must be be notअगरied immediately it is completed.
	 */
	spin_lock(&hvc->vc.lock);
	अगर (!list_empty(&hvc->desc_hw_processing)) अणु
		hvc->issue_synchronize = true;
		sync_needed = true;
	पूर्ण
	spin_unlock(&hvc->vc.lock);

	अगर (sync_needed)
		रुको_क्रम_completion(&hvc->issue_completion);
	/*
	 * At the poपूर्णांक, we expect that all reमुख्यing descriptors in the ring
	 * क्रम the channel should be all processing करोne.
	 */
	WARN_ONCE(!list_empty(&hvc->desc_hw_processing),
		  "Desc pending still in list desc_hw_processing\n");

	/* Free all descriptors in list desc_completed */
	vchan_synchronize(&hvc->vc);

	WARN_ONCE(!list_empty(&hvc->vc.desc_completed),
		  "Desc pending still in list desc_completed\n");
पूर्ण

अटल पूर्णांक mtk_hsdma_terminate_all(काष्ठा dma_chan *c)
अणु
	/*
	 * Free pending descriptors not processed yet by hardware that have
	 * previously been submitted to the channel.
	 */
	mtk_hsdma_मुक्त_inactive_desc(c);

	/*
	 * However, the DMA engine करोesn't provide any way to stop these
	 * descriptors being processed currently by hardware. The only way is
	 * to just रुकोing until these descriptors are all processed completely
	 * through mtk_hsdma_मुक्त_active_desc call.
	 */
	mtk_hsdma_मुक्त_active_desc(c);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hsdma_alloc_chan_resources(काष्ठा dma_chan *c)
अणु
	काष्ठा mtk_hsdma_device *hsdma = to_hsdma_dev(c);
	पूर्णांक err;

	/*
	 * Since HSDMA has only one PC, the resource क्रम PC is being allocated
	 * when the first VC is being created and the other VCs would run on
	 * the same PC.
	 */
	अगर (!refcount_पढ़ो(&hsdma->pc_refcnt)) अणु
		err = mtk_hsdma_alloc_pchan(hsdma, hsdma->pc);
		अगर (err)
			वापस err;
		/*
		 * refcount_inc would complain increment on 0; use-after-मुक्त.
		 * Thus, we need to explicitly set it as 1 initially.
		 */
		refcount_set(&hsdma->pc_refcnt, 1);
	पूर्ण अन्यथा अणु
		refcount_inc(&hsdma->pc_refcnt);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_hsdma_मुक्त_chan_resources(काष्ठा dma_chan *c)
अणु
	काष्ठा mtk_hsdma_device *hsdma = to_hsdma_dev(c);

	/* Free all descriptors in all lists on the VC */
	mtk_hsdma_terminate_all(c);

	/* The resource क्रम PC is not मुक्तd until all the VCs are destroyed */
	अगर (!refcount_dec_and_test(&hsdma->pc_refcnt))
		वापस;

	mtk_hsdma_मुक्त_pchan(hsdma, hsdma->pc);
पूर्ण

अटल पूर्णांक mtk_hsdma_hw_init(काष्ठा mtk_hsdma_device *hsdma)
अणु
	पूर्णांक err;

	pm_runसमय_enable(hsdma2dev(hsdma));
	pm_runसमय_get_sync(hsdma2dev(hsdma));

	err = clk_prepare_enable(hsdma->clk);
	अगर (err)
		वापस err;

	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_INT_ENABLE, 0);
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_GLO, MTK_HSDMA_GLO_DEFAULT);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hsdma_hw_deinit(काष्ठा mtk_hsdma_device *hsdma)
अणु
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_GLO, 0);

	clk_disable_unprepare(hsdma->clk);

	pm_runसमय_put_sync(hsdma2dev(hsdma));
	pm_runसमय_disable(hsdma2dev(hsdma));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_hsdma_soc mt7623_soc = अणु
	.dकरोne = BIT(31),
	.ls0 = BIT(30),
पूर्ण;

अटल स्थिर काष्ठा mtk_hsdma_soc mt7622_soc = अणु
	.dकरोne = BIT(15),
	.ls0 = BIT(14),
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_hsdma_match[] = अणु
	अणु .compatible = "mediatek,mt7623-hsdma", .data = &mt7623_socपूर्ण,
	अणु .compatible = "mediatek,mt7622-hsdma", .data = &mt7622_socपूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_hsdma_match);

अटल पूर्णांक mtk_hsdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_hsdma_device *hsdma;
	काष्ठा mtk_hsdma_vchan *vc;
	काष्ठा dma_device *dd;
	काष्ठा resource *res;
	पूर्णांक i, err;

	hsdma = devm_kzalloc(&pdev->dev, माप(*hsdma), GFP_KERNEL);
	अगर (!hsdma)
		वापस -ENOMEM;

	dd = &hsdma->ddev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	hsdma->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(hsdma->base))
		वापस PTR_ERR(hsdma->base);

	hsdma->soc = of_device_get_match_data(&pdev->dev);
	अगर (!hsdma->soc) अणु
		dev_err(&pdev->dev, "No device match found\n");
		वापस -ENODEV;
	पूर्ण

	hsdma->clk = devm_clk_get(&pdev->dev, "hsdma");
	अगर (IS_ERR(hsdma->clk)) अणु
		dev_err(&pdev->dev, "No clock for %s\n",
			dev_name(&pdev->dev));
		वापस PTR_ERR(hsdma->clk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "No irq resource for %s\n",
			dev_name(&pdev->dev));
		वापस -EINVAL;
	पूर्ण
	hsdma->irq = res->start;

	refcount_set(&hsdma->pc_refcnt, 0);
	spin_lock_init(&hsdma->lock);

	dma_cap_set(DMA_MEMCPY, dd->cap_mask);

	dd->copy_align = MTK_HSDMA_ALIGN_SIZE;
	dd->device_alloc_chan_resources = mtk_hsdma_alloc_chan_resources;
	dd->device_मुक्त_chan_resources = mtk_hsdma_मुक्त_chan_resources;
	dd->device_tx_status = mtk_hsdma_tx_status;
	dd->device_issue_pending = mtk_hsdma_issue_pending;
	dd->device_prep_dma_स_नकल = mtk_hsdma_prep_dma_स_नकल;
	dd->device_terminate_all = mtk_hsdma_terminate_all;
	dd->src_addr_widths = MTK_HSDMA_DMA_BUSWIDTHS;
	dd->dst_addr_widths = MTK_HSDMA_DMA_BUSWIDTHS;
	dd->directions = BIT(DMA_MEM_TO_MEM);
	dd->residue_granularity = DMA_RESIDUE_GRANULARITY_SEGMENT;
	dd->dev = &pdev->dev;
	INIT_LIST_HEAD(&dd->channels);

	hsdma->dma_requests = MTK_HSDMA_NR_VCHANS;
	अगर (pdev->dev.of_node && of_property_पढ़ो_u32(pdev->dev.of_node,
						      "dma-requests",
						      &hsdma->dma_requests)) अणु
		dev_info(&pdev->dev,
			 "Using %u as missing dma-requests property\n",
			 MTK_HSDMA_NR_VCHANS);
	पूर्ण

	hsdma->pc = devm_kसुस्मृति(&pdev->dev, MTK_HSDMA_NR_MAX_PCHANS,
				 माप(*hsdma->pc), GFP_KERNEL);
	अगर (!hsdma->pc)
		वापस -ENOMEM;

	hsdma->vc = devm_kसुस्मृति(&pdev->dev, hsdma->dma_requests,
				 माप(*hsdma->vc), GFP_KERNEL);
	अगर (!hsdma->vc)
		वापस -ENOMEM;

	क्रम (i = 0; i < hsdma->dma_requests; i++) अणु
		vc = &hsdma->vc[i];
		vc->vc.desc_मुक्त = mtk_hsdma_vdesc_मुक्त;
		vchan_init(&vc->vc, dd);
		init_completion(&vc->issue_completion);
		INIT_LIST_HEAD(&vc->desc_hw_processing);
	पूर्ण

	err = dma_async_device_रेजिस्टर(dd);
	अगर (err)
		वापस err;

	err = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
					 of_dma_xlate_by_chan_id, hsdma);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"MediaTek HSDMA OF registration failed %d\n", err);
		जाओ err_unरेजिस्टर;
	पूर्ण

	mtk_hsdma_hw_init(hsdma);

	err = devm_request_irq(&pdev->dev, hsdma->irq,
			       mtk_hsdma_irq, 0,
			       dev_name(&pdev->dev), hsdma);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"request_irq failed with err %d\n", err);
		जाओ err_मुक्त;
	पूर्ण

	platक्रमm_set_drvdata(pdev, hsdma);

	dev_info(&pdev->dev, "MediaTek HSDMA driver registered\n");

	वापस 0;

err_मुक्त:
	mtk_hsdma_hw_deinit(hsdma);
	of_dma_controller_मुक्त(pdev->dev.of_node);
err_unरेजिस्टर:
	dma_async_device_unरेजिस्टर(dd);

	वापस err;
पूर्ण

अटल पूर्णांक mtk_hsdma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_hsdma_device *hsdma = platक्रमm_get_drvdata(pdev);
	काष्ठा mtk_hsdma_vchan *vc;
	पूर्णांक i;

	/* Kill VC task */
	क्रम (i = 0; i < hsdma->dma_requests; i++) अणु
		vc = &hsdma->vc[i];

		list_del(&vc->vc.chan.device_node);
		tasklet_समाप्त(&vc->vc.task);
	पूर्ण

	/* Disable DMA पूर्णांकerrupt */
	mtk_dma_ग_लिखो(hsdma, MTK_HSDMA_INT_ENABLE, 0);

	/* Waits क्रम any pending IRQ handlers to complete */
	synchronize_irq(hsdma->irq);

	/* Disable hardware */
	mtk_hsdma_hw_deinit(hsdma);

	dma_async_device_unरेजिस्टर(&hsdma->ddev);
	of_dma_controller_मुक्त(pdev->dev.of_node);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mtk_hsdma_driver = अणु
	.probe		= mtk_hsdma_probe,
	.हटाओ		= mtk_hsdma_हटाओ,
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.of_match_table	= mtk_hsdma_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mtk_hsdma_driver);

MODULE_DESCRIPTION("MediaTek High-Speed DMA Controller Driver");
MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_LICENSE("GPL v2");
