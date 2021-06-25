<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_address.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "../dmaengine.h"

#घोषणा DESC_TYPE	27
#घोषणा DESC_TYPE_HOST	0x10
#घोषणा DESC_TYPE_TEARD	0x13

#घोषणा TD_DESC_IS_RX	(1 << 16)
#घोषणा TD_DESC_DMA_NUM	10

#घोषणा DESC_LENGTH_BITS_NUM	21

#घोषणा DESC_TYPE_USB	(5 << 26)
#घोषणा DESC_PD_COMPLETE	(1 << 31)

/* DMA engine */
#घोषणा DMA_TDFDQ	4
#घोषणा DMA_TXGCR(x)	(0x800 + (x) * 0x20)
#घोषणा DMA_RXGCR(x)	(0x808 + (x) * 0x20)
#घोषणा RXHPCRA0		4

#घोषणा GCR_CHAN_ENABLE		(1 << 31)
#घोषणा GCR_TEARDOWN		(1 << 30)
#घोषणा GCR_STARV_RETRY		(1 << 24)
#घोषणा GCR_DESC_TYPE_HOST	(1 << 14)

/* DMA scheduler */
#घोषणा DMA_SCHED_CTRL		0
#घोषणा DMA_SCHED_CTRL_EN	(1 << 31)
#घोषणा DMA_SCHED_WORD(x)	((x) * 4 + 0x800)

#घोषणा SCHED_ENTRY0_CHAN(x)	((x) << 0)
#घोषणा SCHED_ENTRY0_IS_RX	(1 << 7)

#घोषणा SCHED_ENTRY1_CHAN(x)	((x) << 8)
#घोषणा SCHED_ENTRY1_IS_RX	(1 << 15)

#घोषणा SCHED_ENTRY2_CHAN(x)	((x) << 16)
#घोषणा SCHED_ENTRY2_IS_RX	(1 << 23)

#घोषणा SCHED_ENTRY3_CHAN(x)	((x) << 24)
#घोषणा SCHED_ENTRY3_IS_RX	(1 << 31)

/* Queue manager */
/* 4 KiB of memory क्रम descriptors, 2 क्रम each endpoपूर्णांक */
#घोषणा ALLOC_DECS_NUM		128
#घोषणा DESCS_AREAS		1
#घोषणा TOTAL_DESCS_NUM		(ALLOC_DECS_NUM * DESCS_AREAS)
#घोषणा QMGR_SCRATCH_SIZE	(TOTAL_DESCS_NUM * 4)

#घोषणा QMGR_LRAM0_BASE		0x80
#घोषणा QMGR_LRAM_SIZE		0x84
#घोषणा QMGR_LRAM1_BASE		0x88
#घोषणा QMGR_MEMBASE(x)		(0x1000 + (x) * 0x10)
#घोषणा QMGR_MEMCTRL(x)		(0x1004 + (x) * 0x10)
#घोषणा QMGR_MEMCTRL_IDX_SH	16
#घोषणा QMGR_MEMCTRL_DESC_SH	8

#घोषणा QMGR_PEND(x)	(0x90 + (x) * 4)

#घोषणा QMGR_PENDING_SLOT_Q(x)	(x / 32)
#घोषणा QMGR_PENDING_BIT_Q(x)	(x % 32)

#घोषणा QMGR_QUEUE_A(n)	(0x2000 + (n) * 0x10)
#घोषणा QMGR_QUEUE_B(n)	(0x2004 + (n) * 0x10)
#घोषणा QMGR_QUEUE_C(n)	(0x2008 + (n) * 0x10)
#घोषणा QMGR_QUEUE_D(n)	(0x200c + (n) * 0x10)

/* Packet Descriptor */
#घोषणा PD2_ZERO_LENGTH		(1 << 19)

काष्ठा cppi41_channel अणु
	काष्ठा dma_chan chan;
	काष्ठा dma_async_tx_descriptor txd;
	काष्ठा cppi41_dd *cdd;
	काष्ठा cppi41_desc *desc;
	dma_addr_t desc_phys;
	व्योम __iomem *gcr_reg;
	पूर्णांक is_tx;
	u32 residue;

	अचिन्हित पूर्णांक q_num;
	अचिन्हित पूर्णांक q_comp_num;
	अचिन्हित पूर्णांक port_num;

	अचिन्हित td_retry;
	अचिन्हित td_queued:1;
	अचिन्हित td_seen:1;
	अचिन्हित td_desc_seen:1;

	काष्ठा list_head node;		/* Node क्रम pending list */
पूर्ण;

काष्ठा cppi41_desc अणु
	u32 pd0;
	u32 pd1;
	u32 pd2;
	u32 pd3;
	u32 pd4;
	u32 pd5;
	u32 pd6;
	u32 pd7;
पूर्ण __aligned(32);

काष्ठा chan_queues अणु
	u16 submit;
	u16 complete;
पूर्ण;

काष्ठा cppi41_dd अणु
	काष्ठा dma_device ddev;

	व्योम *qmgr_scratch;
	dma_addr_t scratch_phys;

	काष्ठा cppi41_desc *cd;
	dma_addr_t descs_phys;
	u32 first_td_desc;
	काष्ठा cppi41_channel *chan_busy[ALLOC_DECS_NUM];

	व्योम __iomem *ctrl_mem;
	व्योम __iomem *sched_mem;
	व्योम __iomem *qmgr_mem;
	अचिन्हित पूर्णांक irq;
	स्थिर काष्ठा chan_queues *queues_rx;
	स्थिर काष्ठा chan_queues *queues_tx;
	काष्ठा chan_queues td_queue;
	u16 first_completion_queue;
	u16 qmgr_num_pend;
	u32 n_chans;
	u8 platक्रमm;

	काष्ठा list_head pending;	/* Pending queued transfers */
	spinlock_t lock;		/* Lock क्रम pending list */

	/* context क्रम suspend/resume */
	अचिन्हित पूर्णांक dma_tdfdq;

	bool is_suspended;
पूर्ण;

अटल काष्ठा chan_queues am335x_usb_queues_tx[] = अणु
	/* USB0 ENDP 1 */
	[ 0] = अणु .submit = 32, .complete =  93पूर्ण,
	[ 1] = अणु .submit = 34, .complete =  94पूर्ण,
	[ 2] = अणु .submit = 36, .complete =  95पूर्ण,
	[ 3] = अणु .submit = 38, .complete =  96पूर्ण,
	[ 4] = अणु .submit = 40, .complete =  97पूर्ण,
	[ 5] = अणु .submit = 42, .complete =  98पूर्ण,
	[ 6] = अणु .submit = 44, .complete =  99पूर्ण,
	[ 7] = अणु .submit = 46, .complete = 100पूर्ण,
	[ 8] = अणु .submit = 48, .complete = 101पूर्ण,
	[ 9] = अणु .submit = 50, .complete = 102पूर्ण,
	[10] = अणु .submit = 52, .complete = 103पूर्ण,
	[11] = अणु .submit = 54, .complete = 104पूर्ण,
	[12] = अणु .submit = 56, .complete = 105पूर्ण,
	[13] = अणु .submit = 58, .complete = 106पूर्ण,
	[14] = अणु .submit = 60, .complete = 107पूर्ण,

	/* USB1 ENDP1 */
	[15] = अणु .submit = 62, .complete = 125पूर्ण,
	[16] = अणु .submit = 64, .complete = 126पूर्ण,
	[17] = अणु .submit = 66, .complete = 127पूर्ण,
	[18] = अणु .submit = 68, .complete = 128पूर्ण,
	[19] = अणु .submit = 70, .complete = 129पूर्ण,
	[20] = अणु .submit = 72, .complete = 130पूर्ण,
	[21] = अणु .submit = 74, .complete = 131पूर्ण,
	[22] = अणु .submit = 76, .complete = 132पूर्ण,
	[23] = अणु .submit = 78, .complete = 133पूर्ण,
	[24] = अणु .submit = 80, .complete = 134पूर्ण,
	[25] = अणु .submit = 82, .complete = 135पूर्ण,
	[26] = अणु .submit = 84, .complete = 136पूर्ण,
	[27] = अणु .submit = 86, .complete = 137पूर्ण,
	[28] = अणु .submit = 88, .complete = 138पूर्ण,
	[29] = अणु .submit = 90, .complete = 139पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा chan_queues am335x_usb_queues_rx[] = अणु
	/* USB0 ENDP 1 */
	[ 0] = अणु .submit =  1, .complete = 109पूर्ण,
	[ 1] = अणु .submit =  2, .complete = 110पूर्ण,
	[ 2] = अणु .submit =  3, .complete = 111पूर्ण,
	[ 3] = अणु .submit =  4, .complete = 112पूर्ण,
	[ 4] = अणु .submit =  5, .complete = 113पूर्ण,
	[ 5] = अणु .submit =  6, .complete = 114पूर्ण,
	[ 6] = अणु .submit =  7, .complete = 115पूर्ण,
	[ 7] = अणु .submit =  8, .complete = 116पूर्ण,
	[ 8] = अणु .submit =  9, .complete = 117पूर्ण,
	[ 9] = अणु .submit = 10, .complete = 118पूर्ण,
	[10] = अणु .submit = 11, .complete = 119पूर्ण,
	[11] = अणु .submit = 12, .complete = 120पूर्ण,
	[12] = अणु .submit = 13, .complete = 121पूर्ण,
	[13] = अणु .submit = 14, .complete = 122पूर्ण,
	[14] = अणु .submit = 15, .complete = 123पूर्ण,

	/* USB1 ENDP 1 */
	[15] = अणु .submit = 16, .complete = 141पूर्ण,
	[16] = अणु .submit = 17, .complete = 142पूर्ण,
	[17] = अणु .submit = 18, .complete = 143पूर्ण,
	[18] = अणु .submit = 19, .complete = 144पूर्ण,
	[19] = अणु .submit = 20, .complete = 145पूर्ण,
	[20] = अणु .submit = 21, .complete = 146पूर्ण,
	[21] = अणु .submit = 22, .complete = 147पूर्ण,
	[22] = अणु .submit = 23, .complete = 148पूर्ण,
	[23] = अणु .submit = 24, .complete = 149पूर्ण,
	[24] = अणु .submit = 25, .complete = 150पूर्ण,
	[25] = अणु .submit = 26, .complete = 151पूर्ण,
	[26] = अणु .submit = 27, .complete = 152पूर्ण,
	[27] = अणु .submit = 28, .complete = 153पूर्ण,
	[28] = अणु .submit = 29, .complete = 154पूर्ण,
	[29] = अणु .submit = 30, .complete = 155पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा chan_queues da8xx_usb_queues_tx[] = अणु
	[0] = अणु .submit =  16, .complete = 24पूर्ण,
	[1] = अणु .submit =  18, .complete = 24पूर्ण,
	[2] = अणु .submit =  20, .complete = 24पूर्ण,
	[3] = अणु .submit =  22, .complete = 24पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा chan_queues da8xx_usb_queues_rx[] = अणु
	[0] = अणु .submit =  1, .complete = 26पूर्ण,
	[1] = अणु .submit =  3, .complete = 26पूर्ण,
	[2] = अणु .submit =  5, .complete = 26पूर्ण,
	[3] = अणु .submit =  7, .complete = 26पूर्ण,
पूर्ण;

काष्ठा cppi_glue_infos अणु
	स्थिर काष्ठा chan_queues *queues_rx;
	स्थिर काष्ठा chan_queues *queues_tx;
	काष्ठा chan_queues td_queue;
	u16 first_completion_queue;
	u16 qmgr_num_pend;
पूर्ण;

अटल काष्ठा cppi41_channel *to_cpp41_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा cppi41_channel, chan);
पूर्ण

अटल काष्ठा cppi41_channel *desc_to_chan(काष्ठा cppi41_dd *cdd, u32 desc)
अणु
	काष्ठा cppi41_channel *c;
	u32 descs_size;
	u32 desc_num;

	descs_size = माप(काष्ठा cppi41_desc) * ALLOC_DECS_NUM;

	अगर (!((desc >= cdd->descs_phys) &&
			(desc < (cdd->descs_phys + descs_size)))) अणु
		वापस शून्य;
	पूर्ण

	desc_num = (desc - cdd->descs_phys) / माप(काष्ठा cppi41_desc);
	BUG_ON(desc_num >= ALLOC_DECS_NUM);
	c = cdd->chan_busy[desc_num];
	cdd->chan_busy[desc_num] = शून्य;

	/* Usecount क्रम chan_busy[], paired with push_desc_queue() */
	pm_runसमय_put(cdd->ddev.dev);

	वापस c;
पूर्ण

अटल व्योम cppi_ग_लिखोl(u32 val, व्योम *__iomem *mem)
अणु
	__raw_ग_लिखोl(val, mem);
पूर्ण

अटल u32 cppi_पढ़ोl(व्योम *__iomem *mem)
अणु
	वापस __raw_पढ़ोl(mem);
पूर्ण

अटल u32 pd_trans_len(u32 val)
अणु
	वापस val & ((1 << (DESC_LENGTH_BITS_NUM + 1)) - 1);
पूर्ण

अटल u32 cppi41_pop_desc(काष्ठा cppi41_dd *cdd, अचिन्हित queue_num)
अणु
	u32 desc;

	desc = cppi_पढ़ोl(cdd->qmgr_mem + QMGR_QUEUE_D(queue_num));
	desc &= ~0x1f;
	वापस desc;
पूर्ण

अटल irqवापस_t cppi41_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cppi41_dd *cdd = data;
	u16 first_completion_queue = cdd->first_completion_queue;
	u16 qmgr_num_pend = cdd->qmgr_num_pend;
	काष्ठा cppi41_channel *c;
	पूर्णांक i;

	क्रम (i = QMGR_PENDING_SLOT_Q(first_completion_queue); i < qmgr_num_pend;
			i++) अणु
		u32 val;
		u32 q_num;

		val = cppi_पढ़ोl(cdd->qmgr_mem + QMGR_PEND(i));
		अगर (i == QMGR_PENDING_SLOT_Q(first_completion_queue) && val) अणु
			u32 mask;
			/* set corresponding bit क्रम completetion Q 93 */
			mask = 1 << QMGR_PENDING_BIT_Q(first_completion_queue);
			/* not set all bits क्रम queues less than Q 93 */
			mask--;
			/* now invert and keep only Q 93+ set */
			val &= ~mask;
		पूर्ण

		अगर (val)
			__iormb();

		जबतक (val) अणु
			u32 desc, len;

			/*
			 * This should never trigger, see the comments in
			 * push_desc_queue()
			 */
			WARN_ON(cdd->is_suspended);

			q_num = __fls(val);
			val &= ~(1 << q_num);
			q_num += 32 * i;
			desc = cppi41_pop_desc(cdd, q_num);
			c = desc_to_chan(cdd, desc);
			अगर (WARN_ON(!c)) अणु
				pr_err("%s() q %d desc %08x\n", __func__,
						q_num, desc);
				जारी;
			पूर्ण

			अगर (c->desc->pd2 & PD2_ZERO_LENGTH)
				len = 0;
			अन्यथा
				len = pd_trans_len(c->desc->pd0);

			c->residue = pd_trans_len(c->desc->pd6) - len;
			dma_cookie_complete(&c->txd);
			dmaengine_desc_get_callback_invoke(&c->txd, शून्य);
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल dma_cookie_t cppi41_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	dma_cookie_t cookie;

	cookie = dma_cookie_assign(tx);

	वापस cookie;
पूर्ण

अटल पूर्णांक cppi41_dma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा cppi41_channel *c = to_cpp41_chan(chan);
	काष्ठा cppi41_dd *cdd = c->cdd;
	पूर्णांक error;

	error = pm_runसमय_get_sync(cdd->ddev.dev);
	अगर (error < 0) अणु
		dev_err(cdd->ddev.dev, "%s pm runtime get: %i\n",
			__func__, error);
		pm_runसमय_put_noidle(cdd->ddev.dev);

		वापस error;
	पूर्ण

	dma_cookie_init(chan);
	dma_async_tx_descriptor_init(&c->txd, chan);
	c->txd.tx_submit = cppi41_tx_submit;

	अगर (!c->is_tx)
		cppi_ग_लिखोl(c->q_num, c->gcr_reg + RXHPCRA0);

	pm_runसमय_mark_last_busy(cdd->ddev.dev);
	pm_runसमय_put_स्वतःsuspend(cdd->ddev.dev);

	वापस 0;
पूर्ण

अटल व्योम cppi41_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा cppi41_channel *c = to_cpp41_chan(chan);
	काष्ठा cppi41_dd *cdd = c->cdd;
	पूर्णांक error;

	error = pm_runसमय_get_sync(cdd->ddev.dev);
	अगर (error < 0) अणु
		pm_runसमय_put_noidle(cdd->ddev.dev);

		वापस;
	पूर्ण

	WARN_ON(!list_empty(&cdd->pending));

	pm_runसमय_mark_last_busy(cdd->ddev.dev);
	pm_runसमय_put_स्वतःsuspend(cdd->ddev.dev);
पूर्ण

अटल क्रमागत dma_status cppi41_dma_tx_status(काष्ठा dma_chan *chan,
	dma_cookie_t cookie, काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा cppi41_channel *c = to_cpp41_chan(chan);
	क्रमागत dma_status ret;

	ret = dma_cookie_status(chan, cookie, txstate);

	dma_set_residue(txstate, c->residue);

	वापस ret;
पूर्ण

अटल व्योम push_desc_queue(काष्ठा cppi41_channel *c)
अणु
	काष्ठा cppi41_dd *cdd = c->cdd;
	u32 desc_num;
	u32 desc_phys;
	u32 reg;

	c->residue = 0;

	reg = GCR_CHAN_ENABLE;
	अगर (!c->is_tx) अणु
		reg |= GCR_STARV_RETRY;
		reg |= GCR_DESC_TYPE_HOST;
		reg |= c->q_comp_num;
	पूर्ण

	cppi_ग_लिखोl(reg, c->gcr_reg);

	/*
	 * We करोn't use ग_लिखोl() but __raw_ग_लिखोl() so we have to make sure
	 * that the DMA descriptor in coherent memory made to the मुख्य memory
	 * beक्रमe starting the dma engine.
	 */
	__iowmb();

	/*
	 * DMA transfers can take at least 200ms to complete with USB mass
	 * storage connected. To prevent स्वतःsuspend समयouts, we must use
	 * pm_runसमय_get/put() when chan_busy[] is modअगरied. This will get
	 * cleared in desc_to_chan() or cppi41_stop_chan() depending on the
	 * outcome of the transfer.
	 */
	pm_runसमय_get(cdd->ddev.dev);

	desc_phys = lower_32_bits(c->desc_phys);
	desc_num = (desc_phys - cdd->descs_phys) / माप(काष्ठा cppi41_desc);
	WARN_ON(cdd->chan_busy[desc_num]);
	cdd->chan_busy[desc_num] = c;

	reg = (माप(काष्ठा cppi41_desc) - 24) / 4;
	reg |= desc_phys;
	cppi_ग_लिखोl(reg, cdd->qmgr_mem + QMGR_QUEUE_D(c->q_num));
पूर्ण

/*
 * Caller must hold cdd->lock to prevent push_desc_queue()
 * getting called out of order. We have both cppi41_dma_issue_pending()
 * and cppi41_runसमय_resume() call this function.
 */
अटल व्योम cppi41_run_queue(काष्ठा cppi41_dd *cdd)
अणु
	काष्ठा cppi41_channel *c, *_c;

	list_क्रम_each_entry_safe(c, _c, &cdd->pending, node) अणु
		push_desc_queue(c);
		list_del(&c->node);
	पूर्ण
पूर्ण

अटल व्योम cppi41_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा cppi41_channel *c = to_cpp41_chan(chan);
	काष्ठा cppi41_dd *cdd = c->cdd;
	अचिन्हित दीर्घ flags;
	पूर्णांक error;

	error = pm_runसमय_get(cdd->ddev.dev);
	अगर ((error != -EINPROGRESS) && error < 0) अणु
		pm_runसमय_put_noidle(cdd->ddev.dev);
		dev_err(cdd->ddev.dev, "Failed to pm_runtime_get: %i\n",
			error);

		वापस;
	पूर्ण

	spin_lock_irqsave(&cdd->lock, flags);
	list_add_tail(&c->node, &cdd->pending);
	अगर (!cdd->is_suspended)
		cppi41_run_queue(cdd);
	spin_unlock_irqrestore(&cdd->lock, flags);

	pm_runसमय_mark_last_busy(cdd->ddev.dev);
	pm_runसमय_put_स्वतःsuspend(cdd->ddev.dev);
पूर्ण

अटल u32 get_host_pd0(u32 length)
अणु
	u32 reg;

	reg = DESC_TYPE_HOST << DESC_TYPE;
	reg |= length;

	वापस reg;
पूर्ण

अटल u32 get_host_pd1(काष्ठा cppi41_channel *c)
अणु
	u32 reg;

	reg = 0;

	वापस reg;
पूर्ण

अटल u32 get_host_pd2(काष्ठा cppi41_channel *c)
अणु
	u32 reg;

	reg = DESC_TYPE_USB;
	reg |= c->q_comp_num;

	वापस reg;
पूर्ण

अटल u32 get_host_pd3(u32 length)
अणु
	u32 reg;

	/* PD3 = packet size */
	reg = length;

	वापस reg;
पूर्ण

अटल u32 get_host_pd6(u32 length)
अणु
	u32 reg;

	/* PD6 buffer size */
	reg = DESC_PD_COMPLETE;
	reg |= length;

	वापस reg;
पूर्ण

अटल u32 get_host_pd4_or_7(u32 addr)
अणु
	u32 reg;

	reg = addr;

	वापस reg;
पूर्ण

अटल u32 get_host_pd5(व्योम)
अणु
	u32 reg;

	reg = 0;

	वापस reg;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *cppi41_dma_prep_slave_sg(
	काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl, अचिन्हित sg_len,
	क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ tx_flags, व्योम *context)
अणु
	काष्ठा cppi41_channel *c = to_cpp41_chan(chan);
	काष्ठा dma_async_tx_descriptor *txd = शून्य;
	काष्ठा cppi41_dd *cdd = c->cdd;
	काष्ठा cppi41_desc *d;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;
	पूर्णांक error;

	error = pm_runसमय_get(cdd->ddev.dev);
	अगर (error < 0) अणु
		pm_runसमय_put_noidle(cdd->ddev.dev);

		वापस शून्य;
	पूर्ण

	अगर (cdd->is_suspended)
		जाओ err_out_not_पढ़ोy;

	d = c->desc;
	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		u32 addr;
		u32 len;

		/* We need to use more than one desc once musb supports sg */
		addr = lower_32_bits(sg_dma_address(sg));
		len = sg_dma_len(sg);

		d->pd0 = get_host_pd0(len);
		d->pd1 = get_host_pd1(c);
		d->pd2 = get_host_pd2(c);
		d->pd3 = get_host_pd3(len);
		d->pd4 = get_host_pd4_or_7(addr);
		d->pd5 = get_host_pd5();
		d->pd6 = get_host_pd6(len);
		d->pd7 = get_host_pd4_or_7(addr);

		d++;
	पूर्ण

	txd = &c->txd;

err_out_not_पढ़ोy:
	pm_runसमय_mark_last_busy(cdd->ddev.dev);
	pm_runसमय_put_स्वतःsuspend(cdd->ddev.dev);

	वापस txd;
पूर्ण

अटल व्योम cppi41_compute_td_desc(काष्ठा cppi41_desc *d)
अणु
	d->pd0 = DESC_TYPE_TEARD << DESC_TYPE;
पूर्ण

अटल पूर्णांक cppi41_tear_करोwn_chan(काष्ठा cppi41_channel *c)
अणु
	काष्ठा dmaengine_result पात_result;
	काष्ठा cppi41_dd *cdd = c->cdd;
	काष्ठा cppi41_desc *td;
	u32 reg;
	u32 desc_phys;
	u32 td_desc_phys;

	td = cdd->cd;
	td += cdd->first_td_desc;

	td_desc_phys = cdd->descs_phys;
	td_desc_phys += cdd->first_td_desc * माप(काष्ठा cppi41_desc);

	अगर (!c->td_queued) अणु
		cppi41_compute_td_desc(td);
		__iowmb();

		reg = (माप(काष्ठा cppi41_desc) - 24) / 4;
		reg |= td_desc_phys;
		cppi_ग_लिखोl(reg, cdd->qmgr_mem +
				QMGR_QUEUE_D(cdd->td_queue.submit));

		reg = GCR_CHAN_ENABLE;
		अगर (!c->is_tx) अणु
			reg |= GCR_STARV_RETRY;
			reg |= GCR_DESC_TYPE_HOST;
			reg |= cdd->td_queue.complete;
		पूर्ण
		reg |= GCR_TEARDOWN;
		cppi_ग_लिखोl(reg, c->gcr_reg);
		c->td_queued = 1;
		c->td_retry = 500;
	पूर्ण

	अगर (!c->td_seen || !c->td_desc_seen) अणु

		desc_phys = cppi41_pop_desc(cdd, cdd->td_queue.complete);
		अगर (!desc_phys && c->is_tx)
			desc_phys = cppi41_pop_desc(cdd, c->q_comp_num);

		अगर (desc_phys == c->desc_phys) अणु
			c->td_desc_seen = 1;

		पूर्ण अन्यथा अगर (desc_phys == td_desc_phys) अणु
			u32 pd0;

			__iormb();
			pd0 = td->pd0;
			WARN_ON((pd0 >> DESC_TYPE) != DESC_TYPE_TEARD);
			WARN_ON(!c->is_tx && !(pd0 & TD_DESC_IS_RX));
			WARN_ON((pd0 & 0x1f) != c->port_num);
			c->td_seen = 1;
		पूर्ण अन्यथा अगर (desc_phys) अणु
			WARN_ON_ONCE(1);
		पूर्ण
	पूर्ण
	c->td_retry--;
	/*
	 * If the TX descriptor / channel is in use, the caller needs to poke
	 * his TD bit multiple बार. After that he hardware releases the
	 * transfer descriptor followed by TD descriptor. Waiting seems not to
	 * cause any dअगरference.
	 * RX seems to be thrown out right away. However once the TearDown
	 * descriptor माला_लो through we are करोne. If we have seens the transfer
	 * descriptor beक्रमe the TD we fetch it from enqueue, it has to be
	 * there रुकोing क्रम us.
	 */
	अगर (!c->td_seen && c->td_retry) अणु
		udelay(1);
		वापस -EAGAIN;
	पूर्ण
	WARN_ON(!c->td_retry);

	अगर (!c->td_desc_seen) अणु
		desc_phys = cppi41_pop_desc(cdd, c->q_num);
		अगर (!desc_phys)
			desc_phys = cppi41_pop_desc(cdd, c->q_comp_num);
		WARN_ON(!desc_phys);
	पूर्ण

	c->td_queued = 0;
	c->td_seen = 0;
	c->td_desc_seen = 0;
	cppi_ग_लिखोl(0, c->gcr_reg);

	/* Invoke the callback to करो the necessary clean-up */
	पात_result.result = DMA_TRANS_ABORTED;
	dma_cookie_complete(&c->txd);
	dmaengine_desc_get_callback_invoke(&c->txd, &पात_result);

	वापस 0;
पूर्ण

अटल पूर्णांक cppi41_stop_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा cppi41_channel *c = to_cpp41_chan(chan);
	काष्ठा cppi41_dd *cdd = c->cdd;
	u32 desc_num;
	u32 desc_phys;
	पूर्णांक ret;

	desc_phys = lower_32_bits(c->desc_phys);
	desc_num = (desc_phys - cdd->descs_phys) / माप(काष्ठा cppi41_desc);
	अगर (!cdd->chan_busy[desc_num]) अणु
		काष्ठा cppi41_channel *cc, *_ct;

		/*
		 * channels might still be in the pendling list अगर
		 * cppi41_dma_issue_pending() is called after
		 * cppi41_runसमय_suspend() is called
		 */
		list_क्रम_each_entry_safe(cc, _ct, &cdd->pending, node) अणु
			अगर (cc != c)
				जारी;
			list_del(&cc->node);
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण

	ret = cppi41_tear_करोwn_chan(c);
	अगर (ret)
		वापस ret;

	WARN_ON(!cdd->chan_busy[desc_num]);
	cdd->chan_busy[desc_num] = शून्य;

	/* Usecount क्रम chan_busy[], paired with push_desc_queue() */
	pm_runसमय_put(cdd->ddev.dev);

	वापस 0;
पूर्ण

अटल पूर्णांक cppi41_add_chans(काष्ठा device *dev, काष्ठा cppi41_dd *cdd)
अणु
	काष्ठा cppi41_channel *cchan, *chans;
	पूर्णांक i;
	u32 n_chans = cdd->n_chans;

	/*
	 * The channels can only be used as TX or as RX. So we add twice
	 * that much dma channels because USB can only करो RX or TX.
	 */
	n_chans *= 2;

	chans = devm_kसुस्मृति(dev, n_chans, माप(*chans), GFP_KERNEL);
	अगर (!chans)
		वापस -ENOMEM;

	क्रम (i = 0; i < n_chans; i++) अणु
		cchan = &chans[i];

		cchan->cdd = cdd;
		अगर (i & 1) अणु
			cchan->gcr_reg = cdd->ctrl_mem + DMA_TXGCR(i >> 1);
			cchan->is_tx = 1;
		पूर्ण अन्यथा अणु
			cchan->gcr_reg = cdd->ctrl_mem + DMA_RXGCR(i >> 1);
			cchan->is_tx = 0;
		पूर्ण
		cchan->port_num = i >> 1;
		cchan->desc = &cdd->cd[i];
		cchan->desc_phys = cdd->descs_phys;
		cchan->desc_phys += i * माप(काष्ठा cppi41_desc);
		cchan->chan.device = &cdd->ddev;
		list_add_tail(&cchan->chan.device_node, &cdd->ddev.channels);
	पूर्ण
	cdd->first_td_desc = n_chans;

	वापस 0;
पूर्ण

अटल व्योम purge_descs(काष्ठा device *dev, काष्ठा cppi41_dd *cdd)
अणु
	अचिन्हित पूर्णांक mem_decs;
	पूर्णांक i;

	mem_decs = ALLOC_DECS_NUM * माप(काष्ठा cppi41_desc);

	क्रम (i = 0; i < DESCS_AREAS; i++) अणु

		cppi_ग_लिखोl(0, cdd->qmgr_mem + QMGR_MEMBASE(i));
		cppi_ग_लिखोl(0, cdd->qmgr_mem + QMGR_MEMCTRL(i));

		dma_मुक्त_coherent(dev, mem_decs, cdd->cd,
				cdd->descs_phys);
	पूर्ण
पूर्ण

अटल व्योम disable_sched(काष्ठा cppi41_dd *cdd)
अणु
	cppi_ग_लिखोl(0, cdd->sched_mem + DMA_SCHED_CTRL);
पूर्ण

अटल व्योम deinit_cppi41(काष्ठा device *dev, काष्ठा cppi41_dd *cdd)
अणु
	disable_sched(cdd);

	purge_descs(dev, cdd);

	cppi_ग_लिखोl(0, cdd->qmgr_mem + QMGR_LRAM0_BASE);
	cppi_ग_लिखोl(0, cdd->qmgr_mem + QMGR_LRAM0_BASE);
	dma_मुक्त_coherent(dev, QMGR_SCRATCH_SIZE, cdd->qmgr_scratch,
			cdd->scratch_phys);
पूर्ण

अटल पूर्णांक init_descs(काष्ठा device *dev, काष्ठा cppi41_dd *cdd)
अणु
	अचिन्हित पूर्णांक desc_size;
	अचिन्हित पूर्णांक mem_decs;
	पूर्णांक i;
	u32 reg;
	u32 idx;

	BUILD_BUG_ON(माप(काष्ठा cppi41_desc) &
			(माप(काष्ठा cppi41_desc) - 1));
	BUILD_BUG_ON(माप(काष्ठा cppi41_desc) < 32);
	BUILD_BUG_ON(ALLOC_DECS_NUM < 32);

	desc_size = माप(काष्ठा cppi41_desc);
	mem_decs = ALLOC_DECS_NUM * desc_size;

	idx = 0;
	क्रम (i = 0; i < DESCS_AREAS; i++) अणु

		reg = idx << QMGR_MEMCTRL_IDX_SH;
		reg |= (ilog2(desc_size) - 5) << QMGR_MEMCTRL_DESC_SH;
		reg |= ilog2(ALLOC_DECS_NUM) - 5;

		BUILD_BUG_ON(DESCS_AREAS != 1);
		cdd->cd = dma_alloc_coherent(dev, mem_decs,
				&cdd->descs_phys, GFP_KERNEL);
		अगर (!cdd->cd)
			वापस -ENOMEM;

		cppi_ग_लिखोl(cdd->descs_phys, cdd->qmgr_mem + QMGR_MEMBASE(i));
		cppi_ग_लिखोl(reg, cdd->qmgr_mem + QMGR_MEMCTRL(i));

		idx += ALLOC_DECS_NUM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम init_sched(काष्ठा cppi41_dd *cdd)
अणु
	अचिन्हित ch;
	अचिन्हित word;
	u32 reg;

	word = 0;
	cppi_ग_लिखोl(0, cdd->sched_mem + DMA_SCHED_CTRL);
	क्रम (ch = 0; ch < cdd->n_chans; ch += 2) अणु

		reg = SCHED_ENTRY0_CHAN(ch);
		reg |= SCHED_ENTRY1_CHAN(ch) | SCHED_ENTRY1_IS_RX;

		reg |= SCHED_ENTRY2_CHAN(ch + 1);
		reg |= SCHED_ENTRY3_CHAN(ch + 1) | SCHED_ENTRY3_IS_RX;
		cppi_ग_लिखोl(reg, cdd->sched_mem + DMA_SCHED_WORD(word));
		word++;
	पूर्ण
	reg = cdd->n_chans * 2 - 1;
	reg |= DMA_SCHED_CTRL_EN;
	cppi_ग_लिखोl(reg, cdd->sched_mem + DMA_SCHED_CTRL);
पूर्ण

अटल पूर्णांक init_cppi41(काष्ठा device *dev, काष्ठा cppi41_dd *cdd)
अणु
	पूर्णांक ret;

	BUILD_BUG_ON(QMGR_SCRATCH_SIZE > ((1 << 14) - 1));
	cdd->qmgr_scratch = dma_alloc_coherent(dev, QMGR_SCRATCH_SIZE,
			&cdd->scratch_phys, GFP_KERNEL);
	अगर (!cdd->qmgr_scratch)
		वापस -ENOMEM;

	cppi_ग_लिखोl(cdd->scratch_phys, cdd->qmgr_mem + QMGR_LRAM0_BASE);
	cppi_ग_लिखोl(TOTAL_DESCS_NUM, cdd->qmgr_mem + QMGR_LRAM_SIZE);
	cppi_ग_लिखोl(0, cdd->qmgr_mem + QMGR_LRAM1_BASE);

	ret = init_descs(dev, cdd);
	अगर (ret)
		जाओ err_td;

	cppi_ग_लिखोl(cdd->td_queue.submit, cdd->ctrl_mem + DMA_TDFDQ);
	init_sched(cdd);

	वापस 0;
err_td:
	deinit_cppi41(dev, cdd);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver cpp41_dma_driver;
/*
 * The param क्रमmat is:
 * X Y
 * X: Port
 * Y: 0 = RX अन्यथा TX
 */
#घोषणा INFO_PORT	0
#घोषणा INFO_IS_TX	1

अटल bool cpp41_dma_filter_fn(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा cppi41_channel *cchan;
	काष्ठा cppi41_dd *cdd;
	स्थिर काष्ठा chan_queues *queues;
	u32 *num = param;

	अगर (chan->device->dev->driver != &cpp41_dma_driver.driver)
		वापस false;

	cchan = to_cpp41_chan(chan);

	अगर (cchan->port_num != num[INFO_PORT])
		वापस false;

	अगर (cchan->is_tx && !num[INFO_IS_TX])
		वापस false;
	cdd = cchan->cdd;
	अगर (cchan->is_tx)
		queues = cdd->queues_tx;
	अन्यथा
		queues = cdd->queues_rx;

	BUILD_BUG_ON(ARRAY_SIZE(am335x_usb_queues_rx) !=
		     ARRAY_SIZE(am335x_usb_queues_tx));
	अगर (WARN_ON(cchan->port_num >= ARRAY_SIZE(am335x_usb_queues_rx)))
		वापस false;

	cchan->q_num = queues[cchan->port_num].submit;
	cchan->q_comp_num = queues[cchan->port_num].complete;
	वापस true;
पूर्ण

अटल काष्ठा of_dma_filter_info cpp41_dma_info = अणु
	.filter_fn = cpp41_dma_filter_fn,
पूर्ण;

अटल काष्ठा dma_chan *cppi41_dma_xlate(काष्ठा of_phandle_args *dma_spec,
		काष्ठा of_dma *ofdma)
अणु
	पूर्णांक count = dma_spec->args_count;
	काष्ठा of_dma_filter_info *info = ofdma->of_dma_data;

	अगर (!info || !info->filter_fn)
		वापस शून्य;

	अगर (count != 2)
		वापस शून्य;

	वापस dma_request_channel(info->dma_cap, info->filter_fn,
			&dma_spec->args[0]);
पूर्ण

अटल स्थिर काष्ठा cppi_glue_infos am335x_usb_infos = अणु
	.queues_rx = am335x_usb_queues_rx,
	.queues_tx = am335x_usb_queues_tx,
	.td_queue = अणु .submit = 31, .complete = 0 पूर्ण,
	.first_completion_queue = 93,
	.qmgr_num_pend = 5,
पूर्ण;

अटल स्थिर काष्ठा cppi_glue_infos da8xx_usb_infos = अणु
	.queues_rx = da8xx_usb_queues_rx,
	.queues_tx = da8xx_usb_queues_tx,
	.td_queue = अणु .submit = 31, .complete = 0 पूर्ण,
	.first_completion_queue = 24,
	.qmgr_num_pend = 2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cppi41_dma_ids[] = अणु
	अणु .compatible = "ti,am3359-cppi41", .data = &am335x_usb_infosपूर्ण,
	अणु .compatible = "ti,da830-cppi41", .data = &da8xx_usb_infosपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cppi41_dma_ids);

अटल स्थिर काष्ठा cppi_glue_infos *get_glue_info(काष्ठा device *dev)
अणु
	स्थिर काष्ठा of_device_id *of_id;

	of_id = of_match_node(cppi41_dma_ids, dev->of_node);
	अगर (!of_id)
		वापस शून्य;
	वापस of_id->data;
पूर्ण

#घोषणा CPPI41_DMA_BUSWIDTHS	(BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
				BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
				BIT(DMA_SLAVE_BUSWIDTH_3_BYTES) | \
				BIT(DMA_SLAVE_BUSWIDTH_4_BYTES))

अटल पूर्णांक cppi41_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cppi41_dd *cdd;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा cppi_glue_infos *glue_info;
	काष्ठा resource *mem;
	पूर्णांक index;
	पूर्णांक irq;
	पूर्णांक ret;

	glue_info = get_glue_info(dev);
	अगर (!glue_info)
		वापस -EINVAL;

	cdd = devm_kzalloc(&pdev->dev, माप(*cdd), GFP_KERNEL);
	अगर (!cdd)
		वापस -ENOMEM;

	dma_cap_set(DMA_SLAVE, cdd->ddev.cap_mask);
	cdd->ddev.device_alloc_chan_resources = cppi41_dma_alloc_chan_resources;
	cdd->ddev.device_मुक्त_chan_resources = cppi41_dma_मुक्त_chan_resources;
	cdd->ddev.device_tx_status = cppi41_dma_tx_status;
	cdd->ddev.device_issue_pending = cppi41_dma_issue_pending;
	cdd->ddev.device_prep_slave_sg = cppi41_dma_prep_slave_sg;
	cdd->ddev.device_terminate_all = cppi41_stop_chan;
	cdd->ddev.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	cdd->ddev.src_addr_widths = CPPI41_DMA_BUSWIDTHS;
	cdd->ddev.dst_addr_widths = CPPI41_DMA_BUSWIDTHS;
	cdd->ddev.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	cdd->ddev.dev = dev;
	INIT_LIST_HEAD(&cdd->ddev.channels);
	cpp41_dma_info.dma_cap = cdd->ddev.cap_mask;

	index = of_property_match_string(dev->of_node,
					 "reg-names", "controller");
	अगर (index < 0)
		वापस index;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, index);
	cdd->ctrl_mem = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(cdd->ctrl_mem))
		वापस PTR_ERR(cdd->ctrl_mem);

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, index + 1);
	cdd->sched_mem = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(cdd->sched_mem))
		वापस PTR_ERR(cdd->sched_mem);

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, index + 2);
	cdd->qmgr_mem = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(cdd->qmgr_mem))
		वापस PTR_ERR(cdd->qmgr_mem);

	spin_lock_init(&cdd->lock);
	INIT_LIST_HEAD(&cdd->pending);

	platक्रमm_set_drvdata(pdev, cdd);

	pm_runसमय_enable(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, 100);
	pm_runसमय_use_स्वतःsuspend(dev);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		जाओ err_get_sync;

	cdd->queues_rx = glue_info->queues_rx;
	cdd->queues_tx = glue_info->queues_tx;
	cdd->td_queue = glue_info->td_queue;
	cdd->qmgr_num_pend = glue_info->qmgr_num_pend;
	cdd->first_completion_queue = glue_info->first_completion_queue;

	ret = of_property_पढ़ो_u32(dev->of_node,
				   "#dma-channels", &cdd->n_chans);
	अगर (ret)
		जाओ err_get_n_chans;

	ret = init_cppi41(dev, cdd);
	अगर (ret)
		जाओ err_init_cppi;

	ret = cppi41_add_chans(dev, cdd);
	अगर (ret)
		जाओ err_chans;

	irq = irq_of_parse_and_map(dev->of_node, 0);
	अगर (!irq) अणु
		ret = -EINVAL;
		जाओ err_chans;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, cppi41_irq, IRQF_SHARED,
			dev_name(dev), cdd);
	अगर (ret)
		जाओ err_chans;
	cdd->irq = irq;

	ret = dma_async_device_रेजिस्टर(&cdd->ddev);
	अगर (ret)
		जाओ err_chans;

	ret = of_dma_controller_रेजिस्टर(dev->of_node,
			cppi41_dma_xlate, &cpp41_dma_info);
	अगर (ret)
		जाओ err_of;

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;
err_of:
	dma_async_device_unरेजिस्टर(&cdd->ddev);
err_chans:
	deinit_cppi41(dev, cdd);
err_init_cppi:
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);
err_get_n_chans:
err_get_sync:
	pm_runसमय_put_sync(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक cppi41_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cppi41_dd *cdd = platक्रमm_get_drvdata(pdev);
	पूर्णांक error;

	error = pm_runसमय_get_sync(&pdev->dev);
	अगर (error < 0)
		dev_err(&pdev->dev, "%s could not pm_runtime_get: %i\n",
			__func__, error);
	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&cdd->ddev);

	devm_मुक्त_irq(&pdev->dev, cdd->irq, cdd);
	deinit_cppi41(&pdev->dev, cdd);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cppi41_suspend(काष्ठा device *dev)
अणु
	काष्ठा cppi41_dd *cdd = dev_get_drvdata(dev);

	cdd->dma_tdfdq = cppi_पढ़ोl(cdd->ctrl_mem + DMA_TDFDQ);
	disable_sched(cdd);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cppi41_resume(काष्ठा device *dev)
अणु
	काष्ठा cppi41_dd *cdd = dev_get_drvdata(dev);
	काष्ठा cppi41_channel *c;
	पूर्णांक i;

	क्रम (i = 0; i < DESCS_AREAS; i++)
		cppi_ग_लिखोl(cdd->descs_phys, cdd->qmgr_mem + QMGR_MEMBASE(i));

	list_क्रम_each_entry(c, &cdd->ddev.channels, chan.device_node)
		अगर (!c->is_tx)
			cppi_ग_लिखोl(c->q_num, c->gcr_reg + RXHPCRA0);

	init_sched(cdd);

	cppi_ग_लिखोl(cdd->dma_tdfdq, cdd->ctrl_mem + DMA_TDFDQ);
	cppi_ग_लिखोl(cdd->scratch_phys, cdd->qmgr_mem + QMGR_LRAM0_BASE);
	cppi_ग_लिखोl(QMGR_SCRATCH_SIZE, cdd->qmgr_mem + QMGR_LRAM_SIZE);
	cppi_ग_लिखोl(0, cdd->qmgr_mem + QMGR_LRAM1_BASE);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cppi41_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा cppi41_dd *cdd = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cdd->lock, flags);
	cdd->is_suspended = true;
	WARN_ON(!list_empty(&cdd->pending));
	spin_unlock_irqrestore(&cdd->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cppi41_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cppi41_dd *cdd = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cdd->lock, flags);
	cdd->is_suspended = false;
	cppi41_run_queue(cdd);
	spin_unlock_irqrestore(&cdd->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cppi41_pm_ops = अणु
	SET_LATE_SYSTEM_SLEEP_PM_OPS(cppi41_suspend, cppi41_resume)
	SET_RUNTIME_PM_OPS(cppi41_runसमय_suspend,
			   cppi41_runसमय_resume,
			   शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver cpp41_dma_driver = अणु
	.probe  = cppi41_dma_probe,
	.हटाओ = cppi41_dma_हटाओ,
	.driver = अणु
		.name = "cppi41-dma-engine",
		.pm = &cppi41_pm_ops,
		.of_match_table = of_match_ptr(cppi41_dma_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cpp41_dma_driver);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sebastian Andrzej Siewior <bigeasy@linutronix.de>");
