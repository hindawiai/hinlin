<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018-2019 MediaTek Inc.

/*
 * Driver क्रम MediaTek Command-Queue DMA Controller
 *
 * Author: Shun-Chih Yu <shun-chih.yu@mediatek.com>
 *
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/पूर्णांकerrupt.h>
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

#घोषणा MTK_CQDMA_USEC_POLL		10
#घोषणा MTK_CQDMA_TIMEOUT_POLL		1000
#घोषणा MTK_CQDMA_DMA_BUSWIDTHS		BIT(DMA_SLAVE_BUSWIDTH_4_BYTES)
#घोषणा MTK_CQDMA_ALIGN_SIZE		1

/* The शेष number of भव channel */
#घोषणा MTK_CQDMA_NR_VCHANS		32

/* The शेष number of physical channel */
#घोषणा MTK_CQDMA_NR_PCHANS		3

/* Registers क्रम underlying dma manipulation */
#घोषणा MTK_CQDMA_INT_FLAG		0x0
#घोषणा MTK_CQDMA_INT_EN		0x4
#घोषणा MTK_CQDMA_EN			0x8
#घोषणा MTK_CQDMA_RESET			0xc
#घोषणा MTK_CQDMA_FLUSH			0x14
#घोषणा MTK_CQDMA_SRC			0x1c
#घोषणा MTK_CQDMA_DST			0x20
#घोषणा MTK_CQDMA_LEN1			0x24
#घोषणा MTK_CQDMA_LEN2			0x28
#घोषणा MTK_CQDMA_SRC2			0x60
#घोषणा MTK_CQDMA_DST2			0x64

/* Registers setting */
#घोषणा MTK_CQDMA_EN_BIT		BIT(0)
#घोषणा MTK_CQDMA_INT_FLAG_BIT		BIT(0)
#घोषणा MTK_CQDMA_INT_EN_BIT		BIT(0)
#घोषणा MTK_CQDMA_FLUSH_BIT		BIT(0)

#घोषणा MTK_CQDMA_WARM_RST_BIT		BIT(0)
#घोषणा MTK_CQDMA_HARD_RST_BIT		BIT(1)

#घोषणा MTK_CQDMA_MAX_LEN		GENMASK(27, 0)
#घोषणा MTK_CQDMA_ADDR_LIMIT		GENMASK(31, 0)
#घोषणा MTK_CQDMA_ADDR2_SHFIT		(32)

/**
 * काष्ठा mtk_cqdma_vdesc - The काष्ठा holding info describing भव
 *                         descriptor (CVD)
 * @vd:                    An instance क्रम काष्ठा virt_dma_desc
 * @len:                   The total data size device wants to move
 * @residue:               The reमुख्यing data size device will move
 * @dest:                  The destination address device wants to move to
 * @src:                   The source address device wants to move from
 * @ch:                    The poपूर्णांकer to the corresponding dma channel
 * @node:                  The lise_head काष्ठा to build link-list क्रम VDs
 * @parent:                The poपूर्णांकer to the parent CVD
 */
काष्ठा mtk_cqdma_vdesc अणु
	काष्ठा virt_dma_desc vd;
	माप_प्रकार len;
	माप_प्रकार residue;
	dma_addr_t dest;
	dma_addr_t src;
	काष्ठा dma_chan *ch;

	काष्ठा list_head node;
	काष्ठा mtk_cqdma_vdesc *parent;
पूर्ण;

/**
 * काष्ठा mtk_cqdma_pchan - The काष्ठा holding info describing physical
 *                         channel (PC)
 * @queue:                 Queue क्रम the PDs issued to this PC
 * @base:                  The mapped रेजिस्टर I/O base of this PC
 * @irq:                   The IRQ that this PC are using
 * @refcnt:                Track how many VCs are using this PC
 * @tasklet:               Tasklet क्रम this PC
 * @lock:                  Lock protect agaisting multiple VCs access PC
 */
काष्ठा mtk_cqdma_pchan अणु
	काष्ठा list_head queue;
	व्योम __iomem *base;
	u32 irq;

	refcount_t refcnt;

	काष्ठा tasklet_काष्ठा tasklet;

	/* lock to protect PC */
	spinlock_t lock;
पूर्ण;

/**
 * काष्ठा mtk_cqdma_vchan - The काष्ठा holding info describing भव
 *                         channel (VC)
 * @vc:                    An instance क्रम काष्ठा virt_dma_chan
 * @pc:                    The poपूर्णांकer to the underlying PC
 * @issue_completion:	   The रुको क्रम all issued descriptors completited
 * @issue_synchronize:	   Bool indicating channel synchronization starts
 */
काष्ठा mtk_cqdma_vchan अणु
	काष्ठा virt_dma_chan vc;
	काष्ठा mtk_cqdma_pchan *pc;
	काष्ठा completion issue_completion;
	bool issue_synchronize;
पूर्ण;

/**
 * काष्ठा mtk_cqdma_device - The काष्ठा holding info describing CQDMA
 *                          device
 * @ddev:                   An instance क्रम काष्ठा dma_device
 * @clk:                    The घड़ी that device पूर्णांकernal is using
 * @dma_requests:           The number of VCs the device supports to
 * @dma_channels:           The number of PCs the device supports to
 * @vc:                     The poपूर्णांकer to all available VCs
 * @pc:                     The poपूर्णांकer to all the underlying PCs
 */
काष्ठा mtk_cqdma_device अणु
	काष्ठा dma_device ddev;
	काष्ठा clk *clk;

	u32 dma_requests;
	u32 dma_channels;
	काष्ठा mtk_cqdma_vchan *vc;
	काष्ठा mtk_cqdma_pchan **pc;
पूर्ण;

अटल काष्ठा mtk_cqdma_device *to_cqdma_dev(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan->device, काष्ठा mtk_cqdma_device, ddev);
पूर्ण

अटल काष्ठा mtk_cqdma_vchan *to_cqdma_vchan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा mtk_cqdma_vchan, vc.chan);
पूर्ण

अटल काष्ठा mtk_cqdma_vdesc *to_cqdma_vdesc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा mtk_cqdma_vdesc, vd);
पूर्ण

अटल काष्ठा device *cqdma2dev(काष्ठा mtk_cqdma_device *cqdma)
अणु
	वापस cqdma->ddev.dev;
पूर्ण

अटल u32 mtk_dma_पढ़ो(काष्ठा mtk_cqdma_pchan *pc, u32 reg)
अणु
	वापस पढ़ोl(pc->base + reg);
पूर्ण

अटल व्योम mtk_dma_ग_लिखो(काष्ठा mtk_cqdma_pchan *pc, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, pc->base + reg);
पूर्ण

अटल व्योम mtk_dma_rmw(काष्ठा mtk_cqdma_pchan *pc, u32 reg,
			u32 mask, u32 set)
अणु
	u32 val;

	val = mtk_dma_पढ़ो(pc, reg);
	val &= ~mask;
	val |= set;
	mtk_dma_ग_लिखो(pc, reg, val);
पूर्ण

अटल व्योम mtk_dma_set(काष्ठा mtk_cqdma_pchan *pc, u32 reg, u32 val)
अणु
	mtk_dma_rmw(pc, reg, 0, val);
पूर्ण

अटल व्योम mtk_dma_clr(काष्ठा mtk_cqdma_pchan *pc, u32 reg, u32 val)
अणु
	mtk_dma_rmw(pc, reg, val, 0);
पूर्ण

अटल व्योम mtk_cqdma_vdesc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	kमुक्त(to_cqdma_vdesc(vd));
पूर्ण

अटल पूर्णांक mtk_cqdma_poll_engine_करोne(काष्ठा mtk_cqdma_pchan *pc, bool atomic)
अणु
	u32 status = 0;

	अगर (!atomic)
		वापस पढ़ोl_poll_समयout(pc->base + MTK_CQDMA_EN,
					  status,
					  !(status & MTK_CQDMA_EN_BIT),
					  MTK_CQDMA_USEC_POLL,
					  MTK_CQDMA_TIMEOUT_POLL);

	वापस पढ़ोl_poll_समयout_atomic(pc->base + MTK_CQDMA_EN,
					 status,
					 !(status & MTK_CQDMA_EN_BIT),
					 MTK_CQDMA_USEC_POLL,
					 MTK_CQDMA_TIMEOUT_POLL);
पूर्ण

अटल पूर्णांक mtk_cqdma_hard_reset(काष्ठा mtk_cqdma_pchan *pc)
अणु
	mtk_dma_set(pc, MTK_CQDMA_RESET, MTK_CQDMA_HARD_RST_BIT);
	mtk_dma_clr(pc, MTK_CQDMA_RESET, MTK_CQDMA_HARD_RST_BIT);

	वापस mtk_cqdma_poll_engine_करोne(pc, true);
पूर्ण

अटल व्योम mtk_cqdma_start(काष्ठा mtk_cqdma_pchan *pc,
			    काष्ठा mtk_cqdma_vdesc *cvd)
अणु
	/* रुको क्रम the previous transaction करोne */
	अगर (mtk_cqdma_poll_engine_करोne(pc, true) < 0)
		dev_err(cqdma2dev(to_cqdma_dev(cvd->ch)), "cqdma wait transaction timeout\n");

	/* warm reset the dma engine क्रम the new transaction */
	mtk_dma_set(pc, MTK_CQDMA_RESET, MTK_CQDMA_WARM_RST_BIT);
	अगर (mtk_cqdma_poll_engine_करोne(pc, true) < 0)
		dev_err(cqdma2dev(to_cqdma_dev(cvd->ch)), "cqdma warm reset timeout\n");

	/* setup the source */
	mtk_dma_set(pc, MTK_CQDMA_SRC, cvd->src & MTK_CQDMA_ADDR_LIMIT);
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	mtk_dma_set(pc, MTK_CQDMA_SRC2, cvd->src >> MTK_CQDMA_ADDR2_SHFIT);
#अन्यथा
	mtk_dma_set(pc, MTK_CQDMA_SRC2, 0);
#पूर्ण_अगर

	/* setup the destination */
	mtk_dma_set(pc, MTK_CQDMA_DST, cvd->dest & MTK_CQDMA_ADDR_LIMIT);
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	mtk_dma_set(pc, MTK_CQDMA_DST2, cvd->dest >> MTK_CQDMA_ADDR2_SHFIT);
#अन्यथा
	mtk_dma_set(pc, MTK_CQDMA_DST2, 0);
#पूर्ण_अगर

	/* setup the length */
	mtk_dma_set(pc, MTK_CQDMA_LEN1, cvd->len);

	/* start dma engine */
	mtk_dma_set(pc, MTK_CQDMA_EN, MTK_CQDMA_EN_BIT);
पूर्ण

अटल व्योम mtk_cqdma_issue_vchan_pending(काष्ठा mtk_cqdma_vchan *cvc)
अणु
	काष्ठा virt_dma_desc *vd, *vd2;
	काष्ठा mtk_cqdma_pchan *pc = cvc->pc;
	काष्ठा mtk_cqdma_vdesc *cvd;
	bool trigger_engine = false;

	lockdep_निश्चित_held(&cvc->vc.lock);
	lockdep_निश्चित_held(&pc->lock);

	list_क्रम_each_entry_safe(vd, vd2, &cvc->vc.desc_issued, node) अणु
		/* need to trigger dma engine अगर PC's queue is empty */
		अगर (list_empty(&pc->queue))
			trigger_engine = true;

		cvd = to_cqdma_vdesc(vd);

		/* add VD पूर्णांकo PC's queue */
		list_add_tail(&cvd->node, &pc->queue);

		/* start the dma engine */
		अगर (trigger_engine)
			mtk_cqdma_start(pc, cvd);

		/* हटाओ VD from list desc_issued */
		list_del(&vd->node);
	पूर्ण
पूर्ण

/*
 * वापस true अगर this VC is active,
 * meaning that there are VDs under processing by the PC
 */
अटल bool mtk_cqdma_is_vchan_active(काष्ठा mtk_cqdma_vchan *cvc)
अणु
	काष्ठा mtk_cqdma_vdesc *cvd;

	list_क्रम_each_entry(cvd, &cvc->pc->queue, node)
		अगर (cvc == to_cqdma_vchan(cvd->ch))
			वापस true;

	वापस false;
पूर्ण

/*
 * वापस the poपूर्णांकer of the CVD that is just consumed by the PC
 */
अटल काष्ठा mtk_cqdma_vdesc
*mtk_cqdma_consume_work_queue(काष्ठा mtk_cqdma_pchan *pc)
अणु
	काष्ठा mtk_cqdma_vchan *cvc;
	काष्ठा mtk_cqdma_vdesc *cvd, *ret = शून्य;

	/* consume a CVD from PC's queue */
	cvd = list_first_entry_or_null(&pc->queue,
				       काष्ठा mtk_cqdma_vdesc, node);
	अगर (unlikely(!cvd || !cvd->parent))
		वापस शून्य;

	cvc = to_cqdma_vchan(cvd->ch);
	ret = cvd;

	/* update residue of the parent CVD */
	cvd->parent->residue -= cvd->len;

	/* delete CVD from PC's queue */
	list_del(&cvd->node);

	spin_lock(&cvc->vc.lock);

	/* check whether all the child CVDs completed */
	अगर (!cvd->parent->residue) अणु
		/* add the parent VD पूर्णांकo list desc_completed */
		vchan_cookie_complete(&cvd->parent->vd);

		/* setup completion अगर this VC is under synchronization */
		अगर (cvc->issue_synchronize && !mtk_cqdma_is_vchan_active(cvc)) अणु
			complete(&cvc->issue_completion);
			cvc->issue_synchronize = false;
		पूर्ण
	पूर्ण

	spin_unlock(&cvc->vc.lock);

	/* start transaction क्रम next CVD in the queue */
	cvd = list_first_entry_or_null(&pc->queue,
				       काष्ठा mtk_cqdma_vdesc, node);
	अगर (cvd)
		mtk_cqdma_start(pc, cvd);

	वापस ret;
पूर्ण

अटल व्योम mtk_cqdma_tasklet_cb(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mtk_cqdma_pchan *pc = from_tasklet(pc, t, tasklet);
	काष्ठा mtk_cqdma_vdesc *cvd = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pc->lock, flags);
	/* consume the queue */
	cvd = mtk_cqdma_consume_work_queue(pc);
	spin_unlock_irqrestore(&pc->lock, flags);

	/* submit the next CVD */
	अगर (cvd) अणु
		dma_run_dependencies(&cvd->vd.tx);

		/*
		 * मुक्त child CVD after completion.
		 * the parent CVD would be मुक्तed with desc_मुक्त by user.
		 */
		अगर (cvd->parent != cvd)
			kमुक्त(cvd);
	पूर्ण

	/* re-enable पूर्णांकerrupt beक्रमe leaving tasklet */
	enable_irq(pc->irq);
पूर्ण

अटल irqवापस_t mtk_cqdma_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा mtk_cqdma_device *cqdma = devid;
	irqवापस_t ret = IRQ_NONE;
	bool schedule_tasklet = false;
	u32 i;

	/* clear पूर्णांकerrupt flags क्रम each PC */
	क्रम (i = 0; i < cqdma->dma_channels; ++i, schedule_tasklet = false) अणु
		spin_lock(&cqdma->pc[i]->lock);
		अगर (mtk_dma_पढ़ो(cqdma->pc[i],
				 MTK_CQDMA_INT_FLAG) & MTK_CQDMA_INT_FLAG_BIT) अणु
			/* clear पूर्णांकerrupt */
			mtk_dma_clr(cqdma->pc[i], MTK_CQDMA_INT_FLAG,
				    MTK_CQDMA_INT_FLAG_BIT);

			schedule_tasklet = true;
			ret = IRQ_HANDLED;
		पूर्ण
		spin_unlock(&cqdma->pc[i]->lock);

		अगर (schedule_tasklet) अणु
			/* disable पूर्णांकerrupt */
			disable_irq_nosync(cqdma->pc[i]->irq);

			/* schedule the tasklet to handle the transactions */
			tasklet_schedule(&cqdma->pc[i]->tasklet);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा virt_dma_desc *mtk_cqdma_find_active_desc(काष्ठा dma_chan *c,
							dma_cookie_t cookie)
अणु
	काष्ठा mtk_cqdma_vchan *cvc = to_cqdma_vchan(c);
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cvc->pc->lock, flags);
	list_क्रम_each_entry(vd, &cvc->pc->queue, node)
		अगर (vd->tx.cookie == cookie) अणु
			spin_unlock_irqrestore(&cvc->pc->lock, flags);
			वापस vd;
		पूर्ण
	spin_unlock_irqrestore(&cvc->pc->lock, flags);

	list_क्रम_each_entry(vd, &cvc->vc.desc_issued, node)
		अगर (vd->tx.cookie == cookie)
			वापस vd;

	वापस शून्य;
पूर्ण

अटल क्रमागत dma_status mtk_cqdma_tx_status(काष्ठा dma_chan *c,
					   dma_cookie_t cookie,
					   काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा mtk_cqdma_vchan *cvc = to_cqdma_vchan(c);
	काष्ठा mtk_cqdma_vdesc *cvd;
	काष्ठा virt_dma_desc *vd;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;
	माप_प्रकार bytes = 0;

	ret = dma_cookie_status(c, cookie, txstate);
	अगर (ret == DMA_COMPLETE || !txstate)
		वापस ret;

	spin_lock_irqsave(&cvc->vc.lock, flags);
	vd = mtk_cqdma_find_active_desc(c, cookie);
	spin_unlock_irqrestore(&cvc->vc.lock, flags);

	अगर (vd) अणु
		cvd = to_cqdma_vdesc(vd);
		bytes = cvd->residue;
	पूर्ण

	dma_set_residue(txstate, bytes);

	वापस ret;
पूर्ण

अटल व्योम mtk_cqdma_issue_pending(काष्ठा dma_chan *c)
अणु
	काष्ठा mtk_cqdma_vchan *cvc = to_cqdma_vchan(c);
	अचिन्हित दीर्घ pc_flags;
	अचिन्हित दीर्घ vc_flags;

	/* acquire PC's lock before VS's lock क्रम lock dependency in tasklet */
	spin_lock_irqsave(&cvc->pc->lock, pc_flags);
	spin_lock_irqsave(&cvc->vc.lock, vc_flags);

	अगर (vchan_issue_pending(&cvc->vc))
		mtk_cqdma_issue_vchan_pending(cvc);

	spin_unlock_irqrestore(&cvc->vc.lock, vc_flags);
	spin_unlock_irqrestore(&cvc->pc->lock, pc_flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
mtk_cqdma_prep_dma_स_नकल(काष्ठा dma_chan *c, dma_addr_t dest,
			  dma_addr_t src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mtk_cqdma_vdesc **cvd;
	काष्ठा dma_async_tx_descriptor *tx = शून्य, *prev_tx = शून्य;
	माप_प्रकार i, tlen, nr_vd;

	/*
	 * In the हाल that trsanction length is larger than the
	 * DMA engine supports, a single स_नकल transaction needs
	 * to be separated पूर्णांकo several DMA transactions.
	 * Each DMA transaction would be described by a CVD,
	 * and the first one is referred as the parent CVD,
	 * जबतक the others are child CVDs.
	 * The parent CVD's tx descriptor is the only tx descriptor
	 * वापसed to the DMA user, and it should not be completed
	 * until all the child CVDs completed.
	 */
	nr_vd = DIV_ROUND_UP(len, MTK_CQDMA_MAX_LEN);
	cvd = kसुस्मृति(nr_vd, माप(*cvd), GFP_NOWAIT);
	अगर (!cvd)
		वापस शून्य;

	क्रम (i = 0; i < nr_vd; ++i) अणु
		cvd[i] = kzalloc(माप(*cvd[i]), GFP_NOWAIT);
		अगर (!cvd[i]) अणु
			क्रम (; i > 0; --i)
				kमुक्त(cvd[i - 1]);
			वापस शून्य;
		पूर्ण

		/* setup dma channel */
		cvd[i]->ch = c;

		/* setup sourece, destination, and length */
		tlen = (len > MTK_CQDMA_MAX_LEN) ? MTK_CQDMA_MAX_LEN : len;
		cvd[i]->len = tlen;
		cvd[i]->src = src;
		cvd[i]->dest = dest;

		/* setup tx descriptor */
		tx = vchan_tx_prep(to_virt_chan(c), &cvd[i]->vd, flags);
		tx->next = शून्य;

		अगर (!i) अणु
			cvd[0]->residue = len;
		पूर्ण अन्यथा अणु
			prev_tx->next = tx;
			cvd[i]->residue = tlen;
		पूर्ण

		cvd[i]->parent = cvd[0];

		/* update the src, dest, len, prev_tx क्रम the next CVD */
		src += tlen;
		dest += tlen;
		len -= tlen;
		prev_tx = tx;
	पूर्ण

	वापस &cvd[0]->vd.tx;
पूर्ण

अटल व्योम mtk_cqdma_मुक्त_inactive_desc(काष्ठा dma_chan *c)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(c);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	/*
	 * set desc_allocated, desc_submitted,
	 * and desc_issued as the candicates to be मुक्तd
	 */
	spin_lock_irqsave(&vc->lock, flags);
	list_splice_tail_init(&vc->desc_allocated, &head);
	list_splice_tail_init(&vc->desc_submitted, &head);
	list_splice_tail_init(&vc->desc_issued, &head);
	spin_unlock_irqrestore(&vc->lock, flags);

	/* मुक्त descriptor lists */
	vchan_dma_desc_मुक्त_list(vc, &head);
पूर्ण

अटल व्योम mtk_cqdma_मुक्त_active_desc(काष्ठा dma_chan *c)
अणु
	काष्ठा mtk_cqdma_vchan *cvc = to_cqdma_vchan(c);
	bool sync_needed = false;
	अचिन्हित दीर्घ pc_flags;
	अचिन्हित दीर्घ vc_flags;

	/* acquire PC's lock first due to lock dependency in dma ISR */
	spin_lock_irqsave(&cvc->pc->lock, pc_flags);
	spin_lock_irqsave(&cvc->vc.lock, vc_flags);

	/* synchronization is required अगर this VC is active */
	अगर (mtk_cqdma_is_vchan_active(cvc)) अणु
		cvc->issue_synchronize = true;
		sync_needed = true;
	पूर्ण

	spin_unlock_irqrestore(&cvc->vc.lock, vc_flags);
	spin_unlock_irqrestore(&cvc->pc->lock, pc_flags);

	/* रुकोing क्रम the completion of this VC */
	अगर (sync_needed)
		रुको_क्रम_completion(&cvc->issue_completion);

	/* मुक्त all descriptors in list desc_completed */
	vchan_synchronize(&cvc->vc);

	WARN_ONCE(!list_empty(&cvc->vc.desc_completed),
		  "Desc pending still in list desc_completed\n");
पूर्ण

अटल पूर्णांक mtk_cqdma_terminate_all(काष्ठा dma_chan *c)
अणु
	/* मुक्त descriptors not processed yet by hardware */
	mtk_cqdma_मुक्त_inactive_desc(c);

	/* मुक्त descriptors being processed by hardware */
	mtk_cqdma_मुक्त_active_desc(c);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_cqdma_alloc_chan_resources(काष्ठा dma_chan *c)
अणु
	काष्ठा mtk_cqdma_device *cqdma = to_cqdma_dev(c);
	काष्ठा mtk_cqdma_vchan *vc = to_cqdma_vchan(c);
	काष्ठा mtk_cqdma_pchan *pc = शून्य;
	u32 i, min_refcnt = U32_MAX, refcnt;
	अचिन्हित दीर्घ flags;

	/* allocate PC with the minimun refcount */
	क्रम (i = 0; i < cqdma->dma_channels; ++i) अणु
		refcnt = refcount_पढ़ो(&cqdma->pc[i]->refcnt);
		अगर (refcnt < min_refcnt) अणु
			pc = cqdma->pc[i];
			min_refcnt = refcnt;
		पूर्ण
	पूर्ण

	अगर (!pc)
		वापस -ENOSPC;

	spin_lock_irqsave(&pc->lock, flags);

	अगर (!refcount_पढ़ो(&pc->refcnt)) अणु
		/* allocate PC when the refcount is zero */
		mtk_cqdma_hard_reset(pc);

		/* enable पूर्णांकerrupt क्रम this PC */
		mtk_dma_set(pc, MTK_CQDMA_INT_EN, MTK_CQDMA_INT_EN_BIT);

		/*
		 * refcount_inc would complain increment on 0; use-after-मुक्त.
		 * Thus, we need to explicitly set it as 1 initially.
		 */
		refcount_set(&pc->refcnt, 1);
	पूर्ण अन्यथा अणु
		refcount_inc(&pc->refcnt);
	पूर्ण

	spin_unlock_irqrestore(&pc->lock, flags);

	vc->pc = pc;

	वापस 0;
पूर्ण

अटल व्योम mtk_cqdma_मुक्त_chan_resources(काष्ठा dma_chan *c)
अणु
	काष्ठा mtk_cqdma_vchan *cvc = to_cqdma_vchan(c);
	अचिन्हित दीर्घ flags;

	/* मुक्त all descriptors in all lists on the VC */
	mtk_cqdma_terminate_all(c);

	spin_lock_irqsave(&cvc->pc->lock, flags);

	/* PC is not मुक्तd until there is no VC mapped to it */
	अगर (refcount_dec_and_test(&cvc->pc->refcnt)) अणु
		/* start the flush operation and stop the engine */
		mtk_dma_set(cvc->pc, MTK_CQDMA_FLUSH, MTK_CQDMA_FLUSH_BIT);

		/* रुको क्रम the completion of flush operation */
		अगर (mtk_cqdma_poll_engine_करोne(cvc->pc, true) < 0)
			dev_err(cqdma2dev(to_cqdma_dev(c)), "cqdma flush timeout\n");

		/* clear the flush bit and पूर्णांकerrupt flag */
		mtk_dma_clr(cvc->pc, MTK_CQDMA_FLUSH, MTK_CQDMA_FLUSH_BIT);
		mtk_dma_clr(cvc->pc, MTK_CQDMA_INT_FLAG,
			    MTK_CQDMA_INT_FLAG_BIT);

		/* disable पूर्णांकerrupt क्रम this PC */
		mtk_dma_clr(cvc->pc, MTK_CQDMA_INT_EN, MTK_CQDMA_INT_EN_BIT);
	पूर्ण

	spin_unlock_irqrestore(&cvc->pc->lock, flags);
पूर्ण

अटल पूर्णांक mtk_cqdma_hw_init(काष्ठा mtk_cqdma_device *cqdma)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;
	u32 i;

	pm_runसमय_enable(cqdma2dev(cqdma));
	pm_runसमय_get_sync(cqdma2dev(cqdma));

	err = clk_prepare_enable(cqdma->clk);

	अगर (err) अणु
		pm_runसमय_put_sync(cqdma2dev(cqdma));
		pm_runसमय_disable(cqdma2dev(cqdma));
		वापस err;
	पूर्ण

	/* reset all PCs */
	क्रम (i = 0; i < cqdma->dma_channels; ++i) अणु
		spin_lock_irqsave(&cqdma->pc[i]->lock, flags);
		अगर (mtk_cqdma_hard_reset(cqdma->pc[i]) < 0) अणु
			dev_err(cqdma2dev(cqdma), "cqdma hard reset timeout\n");
			spin_unlock_irqrestore(&cqdma->pc[i]->lock, flags);

			clk_disable_unprepare(cqdma->clk);
			pm_runसमय_put_sync(cqdma2dev(cqdma));
			pm_runसमय_disable(cqdma2dev(cqdma));
			वापस -EINVAL;
		पूर्ण
		spin_unlock_irqrestore(&cqdma->pc[i]->lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_cqdma_hw_deinit(काष्ठा mtk_cqdma_device *cqdma)
अणु
	अचिन्हित दीर्घ flags;
	u32 i;

	/* reset all PCs */
	क्रम (i = 0; i < cqdma->dma_channels; ++i) अणु
		spin_lock_irqsave(&cqdma->pc[i]->lock, flags);
		अगर (mtk_cqdma_hard_reset(cqdma->pc[i]) < 0)
			dev_err(cqdma2dev(cqdma), "cqdma hard reset timeout\n");
		spin_unlock_irqrestore(&cqdma->pc[i]->lock, flags);
	पूर्ण

	clk_disable_unprepare(cqdma->clk);

	pm_runसमय_put_sync(cqdma2dev(cqdma));
	pm_runसमय_disable(cqdma2dev(cqdma));
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_cqdma_match[] = अणु
	अणु .compatible = "mediatek,mt6765-cqdma" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_cqdma_match);

अटल पूर्णांक mtk_cqdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_cqdma_device *cqdma;
	काष्ठा mtk_cqdma_vchan *vc;
	काष्ठा dma_device *dd;
	काष्ठा resource *res;
	पूर्णांक err;
	u32 i;

	cqdma = devm_kzalloc(&pdev->dev, माप(*cqdma), GFP_KERNEL);
	अगर (!cqdma)
		वापस -ENOMEM;

	dd = &cqdma->ddev;

	cqdma->clk = devm_clk_get(&pdev->dev, "cqdma");
	अगर (IS_ERR(cqdma->clk)) अणु
		dev_err(&pdev->dev, "No clock for %s\n",
			dev_name(&pdev->dev));
		वापस PTR_ERR(cqdma->clk);
	पूर्ण

	dma_cap_set(DMA_MEMCPY, dd->cap_mask);

	dd->copy_align = MTK_CQDMA_ALIGN_SIZE;
	dd->device_alloc_chan_resources = mtk_cqdma_alloc_chan_resources;
	dd->device_मुक्त_chan_resources = mtk_cqdma_मुक्त_chan_resources;
	dd->device_tx_status = mtk_cqdma_tx_status;
	dd->device_issue_pending = mtk_cqdma_issue_pending;
	dd->device_prep_dma_स_नकल = mtk_cqdma_prep_dma_स_नकल;
	dd->device_terminate_all = mtk_cqdma_terminate_all;
	dd->src_addr_widths = MTK_CQDMA_DMA_BUSWIDTHS;
	dd->dst_addr_widths = MTK_CQDMA_DMA_BUSWIDTHS;
	dd->directions = BIT(DMA_MEM_TO_MEM);
	dd->residue_granularity = DMA_RESIDUE_GRANULARITY_SEGMENT;
	dd->dev = &pdev->dev;
	INIT_LIST_HEAD(&dd->channels);

	अगर (pdev->dev.of_node && of_property_पढ़ो_u32(pdev->dev.of_node,
						      "dma-requests",
						      &cqdma->dma_requests)) अणु
		dev_info(&pdev->dev,
			 "Using %u as missing dma-requests property\n",
			 MTK_CQDMA_NR_VCHANS);

		cqdma->dma_requests = MTK_CQDMA_NR_VCHANS;
	पूर्ण

	अगर (pdev->dev.of_node && of_property_पढ़ो_u32(pdev->dev.of_node,
						      "dma-channels",
						      &cqdma->dma_channels)) अणु
		dev_info(&pdev->dev,
			 "Using %u as missing dma-channels property\n",
			 MTK_CQDMA_NR_PCHANS);

		cqdma->dma_channels = MTK_CQDMA_NR_PCHANS;
	पूर्ण

	cqdma->pc = devm_kसुस्मृति(&pdev->dev, cqdma->dma_channels,
				 माप(*cqdma->pc), GFP_KERNEL);
	अगर (!cqdma->pc)
		वापस -ENOMEM;

	/* initialization क्रम PCs */
	क्रम (i = 0; i < cqdma->dma_channels; ++i) अणु
		cqdma->pc[i] = devm_kसुस्मृति(&pdev->dev, 1,
					    माप(**cqdma->pc), GFP_KERNEL);
		अगर (!cqdma->pc[i])
			वापस -ENOMEM;

		INIT_LIST_HEAD(&cqdma->pc[i]->queue);
		spin_lock_init(&cqdma->pc[i]->lock);
		refcount_set(&cqdma->pc[i]->refcnt, 0);
		cqdma->pc[i]->base = devm_platक्रमm_ioremap_resource(pdev, i);
		अगर (IS_ERR(cqdma->pc[i]->base))
			वापस PTR_ERR(cqdma->pc[i]->base);

		/* allocate IRQ resource */
		res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, i);
		अगर (!res) अणु
			dev_err(&pdev->dev, "No irq resource for %s\n",
				dev_name(&pdev->dev));
			वापस -EINVAL;
		पूर्ण
		cqdma->pc[i]->irq = res->start;

		err = devm_request_irq(&pdev->dev, cqdma->pc[i]->irq,
				       mtk_cqdma_irq, 0, dev_name(&pdev->dev),
				       cqdma);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"request_irq failed with err %d\n", err);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* allocate resource क्रम VCs */
	cqdma->vc = devm_kसुस्मृति(&pdev->dev, cqdma->dma_requests,
				 माप(*cqdma->vc), GFP_KERNEL);
	अगर (!cqdma->vc)
		वापस -ENOMEM;

	क्रम (i = 0; i < cqdma->dma_requests; i++) अणु
		vc = &cqdma->vc[i];
		vc->vc.desc_मुक्त = mtk_cqdma_vdesc_मुक्त;
		vchan_init(&vc->vc, dd);
		init_completion(&vc->issue_completion);
	पूर्ण

	err = dma_async_device_रेजिस्टर(dd);
	अगर (err)
		वापस err;

	err = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
					 of_dma_xlate_by_chan_id, cqdma);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"MediaTek CQDMA OF registration failed %d\n", err);
		जाओ err_unरेजिस्टर;
	पूर्ण

	err = mtk_cqdma_hw_init(cqdma);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"MediaTek CQDMA HW initialization failed %d\n", err);
		जाओ err_unरेजिस्टर;
	पूर्ण

	platक्रमm_set_drvdata(pdev, cqdma);

	/* initialize tasklet क्रम each PC */
	क्रम (i = 0; i < cqdma->dma_channels; ++i)
		tasklet_setup(&cqdma->pc[i]->tasklet, mtk_cqdma_tasklet_cb);

	dev_info(&pdev->dev, "MediaTek CQDMA driver registered\n");

	वापस 0;

err_unरेजिस्टर:
	dma_async_device_unरेजिस्टर(dd);

	वापस err;
पूर्ण

अटल पूर्णांक mtk_cqdma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_cqdma_device *cqdma = platक्रमm_get_drvdata(pdev);
	काष्ठा mtk_cqdma_vchan *vc;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* समाप्त VC task */
	क्रम (i = 0; i < cqdma->dma_requests; i++) अणु
		vc = &cqdma->vc[i];

		list_del(&vc->vc.chan.device_node);
		tasklet_समाप्त(&vc->vc.task);
	पूर्ण

	/* disable पूर्णांकerrupt */
	क्रम (i = 0; i < cqdma->dma_channels; i++) अणु
		spin_lock_irqsave(&cqdma->pc[i]->lock, flags);
		mtk_dma_clr(cqdma->pc[i], MTK_CQDMA_INT_EN,
			    MTK_CQDMA_INT_EN_BIT);
		spin_unlock_irqrestore(&cqdma->pc[i]->lock, flags);

		/* Waits क्रम any pending IRQ handlers to complete */
		synchronize_irq(cqdma->pc[i]->irq);

		tasklet_समाप्त(&cqdma->pc[i]->tasklet);
	पूर्ण

	/* disable hardware */
	mtk_cqdma_hw_deinit(cqdma);

	dma_async_device_unरेजिस्टर(&cqdma->ddev);
	of_dma_controller_मुक्त(pdev->dev.of_node);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mtk_cqdma_driver = अणु
	.probe = mtk_cqdma_probe,
	.हटाओ = mtk_cqdma_हटाओ,
	.driver = अणु
		.name           = KBUILD_MODNAME,
		.of_match_table = mtk_cqdma_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(mtk_cqdma_driver);

MODULE_DESCRIPTION("MediaTek CQDMA Controller Driver");
MODULE_AUTHOR("Shun-Chih Yu <shun-chih.yu@mediatek.com>");
MODULE_LICENSE("GPL v2");
