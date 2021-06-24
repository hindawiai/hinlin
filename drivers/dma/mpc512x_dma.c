<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) Freescale Semicondutor, Inc. 2007, 2008.
 * Copyright (C) Semihalf 2009
 * Copyright (C) Ilya Yanok, Emcraft Systems 2010
 * Copyright (C) Alexander Popov, Promcontroller 2014
 * Copyright (C) Mario Six, Guntermann & Drunck GmbH, 2016
 *
 * Written by Piotr Ziecik <kosmo@semihalf.com>. Hardware description
 * (defines, काष्ठाures and comments) was taken from MPC5121 DMA driver
 * written by Hongjun Chen <hong-jun.chen@मुक्तscale.com>.
 *
 * Approved as OSADL project by a majority of OSADL members and funded
 * by OSADL membership fees in 2009;  क्रम details see www.osadl.org.
 */

/*
 * MPC512x and MPC8308 DMA driver. It supports memory to memory data transfers
 * (tested using dmatest module) and data transfers between memory and
 * peripheral I/O memory by means of slave scatter/gather with these
 * limitations:
 *  - chunked transfers (described by s/g lists with more than one item) are
 *     refused as दीर्घ as proper support क्रम scatter/gather is missing
 *  - transfers on MPC8308 always start from software as this SoC करोes not have
 *     बाह्यal request lines क्रम peripheral flow control
 *  - memory <-> I/O memory transfer chunks of sizes of 1, 2, 4, 16 (क्रम
 *     MPC512x), and 32 bytes are supported, and, consequently, source
 *     addresses and destination addresses must be aligned accordingly;
 *     furthermore, क्रम MPC512x SoCs, the transfer size must be aligned on
 *     (chunk size * maxburst)
 */

#समावेश <linux/module.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <linux/अक्रमom.h>

#समावेश "dmaengine.h"

/* Number of DMA Transfer descriptors allocated per channel */
#घोषणा MPC_DMA_DESCRIPTORS	64

/* Macro definitions */
#घोषणा MPC_DMA_TCD_OFFSET	0x1000

/*
 * Maximum channel counts क्रम inभागidual hardware variants
 * and the maximum channel count over all supported controllers,
 * used क्रम data काष्ठाure size
 */
#घोषणा MPC8308_DMACHAN_MAX	16
#घोषणा MPC512x_DMACHAN_MAX	64
#घोषणा MPC_DMA_CHANNELS	64

/* Arbitration mode of group and channel */
#घोषणा MPC_DMA_DMACR_EDCG	(1 << 31)
#घोषणा MPC_DMA_DMACR_ERGA	(1 << 3)
#घोषणा MPC_DMA_DMACR_ERCA	(1 << 2)

/* Error codes */
#घोषणा MPC_DMA_DMAES_VLD	(1 << 31)
#घोषणा MPC_DMA_DMAES_GPE	(1 << 15)
#घोषणा MPC_DMA_DMAES_CPE	(1 << 14)
#घोषणा MPC_DMA_DMAES_ERRCHN(err) \
				(((err) >> 8) & 0x3f)
#घोषणा MPC_DMA_DMAES_SAE	(1 << 7)
#घोषणा MPC_DMA_DMAES_SOE	(1 << 6)
#घोषणा MPC_DMA_DMAES_DAE	(1 << 5)
#घोषणा MPC_DMA_DMAES_DOE	(1 << 4)
#घोषणा MPC_DMA_DMAES_NCE	(1 << 3)
#घोषणा MPC_DMA_DMAES_SGE	(1 << 2)
#घोषणा MPC_DMA_DMAES_SBE	(1 << 1)
#घोषणा MPC_DMA_DMAES_DBE	(1 << 0)

#घोषणा MPC_DMA_DMAGPOR_SNOOP_ENABLE	(1 << 6)

#घोषणा MPC_DMA_TSIZE_1		0x00
#घोषणा MPC_DMA_TSIZE_2		0x01
#घोषणा MPC_DMA_TSIZE_4		0x02
#घोषणा MPC_DMA_TSIZE_16	0x04
#घोषणा MPC_DMA_TSIZE_32	0x05

/* MPC5121 DMA engine रेजिस्टरs */
काष्ठा __attribute__ ((__packed__)) mpc_dma_regs अणु
	/* 0x00 */
	u32 dmacr;		/* DMA control रेजिस्टर */
	u32 dmaes;		/* DMA error status */
	/* 0x08 */
	u32 dmaerqh;		/* DMA enable request high(channels 63~32) */
	u32 dmaerql;		/* DMA enable request low(channels 31~0) */
	u32 dmaeeih;		/* DMA enable error पूर्णांकerrupt high(ch63~32) */
	u32 dmaeeil;		/* DMA enable error पूर्णांकerrupt low(ch31~0) */
	/* 0x18 */
	u8 dmaserq;		/* DMA set enable request */
	u8 dmacerq;		/* DMA clear enable request */
	u8 dmaseei;		/* DMA set enable error पूर्णांकerrupt */
	u8 dmaceei;		/* DMA clear enable error पूर्णांकerrupt */
	/* 0x1c */
	u8 dmacपूर्णांक;		/* DMA clear पूर्णांकerrupt request */
	u8 dmacerr;		/* DMA clear error */
	u8 dmassrt;		/* DMA set start bit */
	u8 dmacdne;		/* DMA clear DONE status bit */
	/* 0x20 */
	u32 dमुख्यth;		/* DMA पूर्णांकerrupt request high(ch63~32) */
	u32 dमुख्यtl;		/* DMA पूर्णांकerrupt request low(ch31~0) */
	u32 dmaerrh;		/* DMA error high(ch63~32) */
	u32 dmaerrl;		/* DMA error low(ch31~0) */
	/* 0x30 */
	u32 dmahrsh;		/* DMA hw request status high(ch63~32) */
	u32 dmahrsl;		/* DMA hardware request status low(ch31~0) */
	जोड़ अणु
		u32 dmaihsa;	/* DMA पूर्णांकerrupt high select AXE(ch63~32) */
		u32 dmagpor;	/* (General purpose रेजिस्टर on MPC8308) */
	पूर्ण;
	u32 dmailsa;		/* DMA पूर्णांकerrupt low select AXE(ch31~0) */
	/* 0x40 ~ 0xff */
	u32 reserve0[48];	/* Reserved */
	/* 0x100 */
	u8 dchpri[MPC_DMA_CHANNELS];
	/* DMA channels(0~63) priority */
पूर्ण;

काष्ठा __attribute__ ((__packed__)) mpc_dma_tcd अणु
	/* 0x00 */
	u32 saddr;		/* Source address */

	u32 smod:5;		/* Source address modulo */
	u32 ssize:3;		/* Source data transfer size */
	u32 dmod:5;		/* Destination address modulo */
	u32 dsize:3;		/* Destination data transfer size */
	u32 soff:16;		/* Signed source address offset */

	/* 0x08 */
	u32 nbytes;		/* Inner "minor" byte count */
	u32 slast;		/* Last source address adjusपंचांगent */
	u32 daddr;		/* Destination address */

	/* 0x14 */
	u32 citer_elink:1;	/* Enable channel-to-channel linking on
				 * minor loop complete
				 */
	u32 citer_linkch:6;	/* Link channel क्रम minor loop complete */
	u32 citer:9;		/* Current "major" iteration count */
	u32 करोff:16;		/* Signed destination address offset */

	/* 0x18 */
	u32 dlast_sga;		/* Last Destination address adjusपंचांगent/scatter
				 * gather address
				 */

	/* 0x1c */
	u32 biter_elink:1;	/* Enable channel-to-channel linking on major
				 * loop complete
				 */
	u32 biter_linkch:6;
	u32 biter:9;		/* Beginning "major" iteration count */
	u32 bwc:2;		/* Bandwidth control */
	u32 major_linkch:6;	/* Link channel number */
	u32 करोne:1;		/* Channel करोne */
	u32 active:1;		/* Channel active */
	u32 major_elink:1;	/* Enable channel-to-channel linking on major
				 * loop complete
				 */
	u32 e_sg:1;		/* Enable scatter/gather processing */
	u32 d_req:1;		/* Disable request */
	u32 पूर्णांक_half:1;		/* Enable an पूर्णांकerrupt when major counter is
				 * half complete
				 */
	u32 पूर्णांक_maj:1;		/* Enable an पूर्णांकerrupt when major iteration
				 * count completes
				 */
	u32 start:1;		/* Channel start */
पूर्ण;

काष्ठा mpc_dma_desc अणु
	काष्ठा dma_async_tx_descriptor	desc;
	काष्ठा mpc_dma_tcd		*tcd;
	dma_addr_t			tcd_paddr;
	पूर्णांक				error;
	काष्ठा list_head		node;
	पूर्णांक				will_access_peripheral;
पूर्ण;

काष्ठा mpc_dma_chan अणु
	काष्ठा dma_chan			chan;
	काष्ठा list_head		मुक्त;
	काष्ठा list_head		prepared;
	काष्ठा list_head		queued;
	काष्ठा list_head		active;
	काष्ठा list_head		completed;
	काष्ठा mpc_dma_tcd		*tcd;
	dma_addr_t			tcd_paddr;

	/* Settings क्रम access to peripheral FIFO */
	dma_addr_t			src_per_paddr;
	u32				src_tcd_nunits;
	u8				swidth;
	dma_addr_t			dst_per_paddr;
	u32				dst_tcd_nunits;
	u8				dwidth;

	/* Lock क्रम this काष्ठाure */
	spinlock_t			lock;
पूर्ण;

काष्ठा mpc_dma अणु
	काष्ठा dma_device		dma;
	काष्ठा tasklet_काष्ठा		tasklet;
	काष्ठा mpc_dma_chan		channels[MPC_DMA_CHANNELS];
	काष्ठा mpc_dma_regs __iomem	*regs;
	काष्ठा mpc_dma_tcd __iomem	*tcd;
	पूर्णांक				irq;
	पूर्णांक				irq2;
	uपूर्णांक				error_status;
	पूर्णांक				is_mpc8308;

	/* Lock क्रम error_status field in this काष्ठाure */
	spinlock_t			error_status_lock;
पूर्ण;

#घोषणा DRV_NAME	"mpc512x_dma"

/* Convert काष्ठा dma_chan to काष्ठा mpc_dma_chan */
अटल अंतरभूत काष्ठा mpc_dma_chan *dma_chan_to_mpc_dma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा mpc_dma_chan, chan);
पूर्ण

/* Convert काष्ठा dma_chan to काष्ठा mpc_dma */
अटल अंतरभूत काष्ठा mpc_dma *dma_chan_to_mpc_dma(काष्ठा dma_chan *c)
अणु
	काष्ठा mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(c);

	वापस container_of(mchan, काष्ठा mpc_dma, channels[c->chan_id]);
पूर्ण

/*
 * Execute all queued DMA descriptors.
 *
 * Following requirements must be met जबतक calling mpc_dma_execute():
 *	a) mchan->lock is acquired,
 *	b) mchan->active list is empty,
 *	c) mchan->queued list contains at least one entry.
 */
अटल व्योम mpc_dma_execute(काष्ठा mpc_dma_chan *mchan)
अणु
	काष्ठा mpc_dma *mdma = dma_chan_to_mpc_dma(&mchan->chan);
	काष्ठा mpc_dma_desc *first = शून्य;
	काष्ठा mpc_dma_desc *prev = शून्य;
	काष्ठा mpc_dma_desc *mdesc;
	पूर्णांक cid = mchan->chan.chan_id;

	जबतक (!list_empty(&mchan->queued)) अणु
		mdesc = list_first_entry(&mchan->queued,
						काष्ठा mpc_dma_desc, node);
		/*
		 * Grab either several mem-to-mem transfer descriptors
		 * or one peripheral transfer descriptor,
		 * करोn't mix mem-to-mem and peripheral transfer descriptors
		 * within the same 'active' list.
		 */
		अगर (mdesc->will_access_peripheral) अणु
			अगर (list_empty(&mchan->active))
				list_move_tail(&mdesc->node, &mchan->active);
			अवरोध;
		पूर्ण अन्यथा अणु
			list_move_tail(&mdesc->node, &mchan->active);
		पूर्ण
	पूर्ण

	/* Chain descriptors पूर्णांकo one transaction */
	list_क्रम_each_entry(mdesc, &mchan->active, node) अणु
		अगर (!first)
			first = mdesc;

		अगर (!prev) अणु
			prev = mdesc;
			जारी;
		पूर्ण

		prev->tcd->dlast_sga = mdesc->tcd_paddr;
		prev->tcd->e_sg = 1;
		mdesc->tcd->start = 1;

		prev = mdesc;
	पूर्ण

	prev->tcd->पूर्णांक_maj = 1;

	/* Send first descriptor in chain पूर्णांकo hardware */
	स_नकल_toio(&mdma->tcd[cid], first->tcd, माप(काष्ठा mpc_dma_tcd));

	अगर (first != prev)
		mdma->tcd[cid].e_sg = 1;

	अगर (mdma->is_mpc8308) अणु
		/* MPC8308, no request lines, software initiated start */
		out_8(&mdma->regs->dmassrt, cid);
	पूर्ण अन्यथा अगर (first->will_access_peripheral) अणु
		/* Peripherals involved, start by बाह्यal request संकेत */
		out_8(&mdma->regs->dmaserq, cid);
	पूर्ण अन्यथा अणु
		/* Memory to memory transfer, software initiated start */
		out_8(&mdma->regs->dmassrt, cid);
	पूर्ण
पूर्ण

/* Handle पूर्णांकerrupt on one half of DMA controller (32 channels) */
अटल व्योम mpc_dma_irq_process(काष्ठा mpc_dma *mdma, u32 is, u32 es, पूर्णांक off)
अणु
	काष्ठा mpc_dma_chan *mchan;
	काष्ठा mpc_dma_desc *mdesc;
	u32 status = is | es;
	पूर्णांक ch;

	जबतक ((ch = fls(status) - 1) >= 0) अणु
		status &= ~(1 << ch);
		mchan = &mdma->channels[ch + off];

		spin_lock(&mchan->lock);

		out_8(&mdma->regs->dmacपूर्णांक, ch + off);
		out_8(&mdma->regs->dmacerr, ch + off);

		/* Check error status */
		अगर (es & (1 << ch))
			list_क्रम_each_entry(mdesc, &mchan->active, node)
				mdesc->error = -EIO;

		/* Execute queued descriptors */
		list_splice_tail_init(&mchan->active, &mchan->completed);
		अगर (!list_empty(&mchan->queued))
			mpc_dma_execute(mchan);

		spin_unlock(&mchan->lock);
	पूर्ण
पूर्ण

/* Interrupt handler */
अटल irqवापस_t mpc_dma_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mpc_dma *mdma = data;
	uपूर्णांक es;

	/* Save error status रेजिस्टर */
	es = in_be32(&mdma->regs->dmaes);
	spin_lock(&mdma->error_status_lock);
	अगर ((es & MPC_DMA_DMAES_VLD) && mdma->error_status == 0)
		mdma->error_status = es;
	spin_unlock(&mdma->error_status_lock);

	/* Handle पूर्णांकerrupt on each channel */
	अगर (mdma->dma.chancnt > 32) अणु
		mpc_dma_irq_process(mdma, in_be32(&mdma->regs->dमुख्यth),
					in_be32(&mdma->regs->dmaerrh), 32);
	पूर्ण
	mpc_dma_irq_process(mdma, in_be32(&mdma->regs->dमुख्यtl),
					in_be32(&mdma->regs->dmaerrl), 0);

	/* Schedule tasklet */
	tasklet_schedule(&mdma->tasklet);

	वापस IRQ_HANDLED;
पूर्ण

/* process completed descriptors */
अटल व्योम mpc_dma_process_completed(काष्ठा mpc_dma *mdma)
अणु
	dma_cookie_t last_cookie = 0;
	काष्ठा mpc_dma_chan *mchan;
	काष्ठा mpc_dma_desc *mdesc;
	काष्ठा dma_async_tx_descriptor *desc;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(list);
	पूर्णांक i;

	क्रम (i = 0; i < mdma->dma.chancnt; i++) अणु
		mchan = &mdma->channels[i];

		/* Get all completed descriptors */
		spin_lock_irqsave(&mchan->lock, flags);
		अगर (!list_empty(&mchan->completed))
			list_splice_tail_init(&mchan->completed, &list);
		spin_unlock_irqrestore(&mchan->lock, flags);

		अगर (list_empty(&list))
			जारी;

		/* Execute callbacks and run dependencies */
		list_क्रम_each_entry(mdesc, &list, node) अणु
			desc = &mdesc->desc;

			dmaengine_desc_get_callback_invoke(desc, शून्य);

			last_cookie = desc->cookie;
			dma_run_dependencies(desc);
		पूर्ण

		/* Free descriptors */
		spin_lock_irqsave(&mchan->lock, flags);
		list_splice_tail_init(&list, &mchan->मुक्त);
		mchan->chan.completed_cookie = last_cookie;
		spin_unlock_irqrestore(&mchan->lock, flags);
	पूर्ण
पूर्ण

/* DMA Tasklet */
अटल व्योम mpc_dma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mpc_dma *mdma = from_tasklet(mdma, t, tasklet);
	अचिन्हित दीर्घ flags;
	uपूर्णांक es;

	spin_lock_irqsave(&mdma->error_status_lock, flags);
	es = mdma->error_status;
	mdma->error_status = 0;
	spin_unlock_irqrestore(&mdma->error_status_lock, flags);

	/* Prपूर्णांक nice error report */
	अगर (es) अणु
		dev_err(mdma->dma.dev,
			"Hardware reported following error(s) on channel %u:\n",
						      MPC_DMA_DMAES_ERRCHN(es));

		अगर (es & MPC_DMA_DMAES_GPE)
			dev_err(mdma->dma.dev, "- Group Priority Error\n");
		अगर (es & MPC_DMA_DMAES_CPE)
			dev_err(mdma->dma.dev, "- Channel Priority Error\n");
		अगर (es & MPC_DMA_DMAES_SAE)
			dev_err(mdma->dma.dev, "- Source Address Error\n");
		अगर (es & MPC_DMA_DMAES_SOE)
			dev_err(mdma->dma.dev, "- Source Offset Configuration Error\n");
		अगर (es & MPC_DMA_DMAES_DAE)
			dev_err(mdma->dma.dev, "- Destination Address Error\n");
		अगर (es & MPC_DMA_DMAES_DOE)
			dev_err(mdma->dma.dev, "- Destination Offset Configuration Error\n");
		अगर (es & MPC_DMA_DMAES_NCE)
			dev_err(mdma->dma.dev, "- NBytes/Citter Configuration Error\n");
		अगर (es & MPC_DMA_DMAES_SGE)
			dev_err(mdma->dma.dev, "- Scatter/Gather Configuration Error\n");
		अगर (es & MPC_DMA_DMAES_SBE)
			dev_err(mdma->dma.dev, "- Source Bus Error\n");
		अगर (es & MPC_DMA_DMAES_DBE)
			dev_err(mdma->dma.dev, "- Destination Bus Error\n");
	पूर्ण

	mpc_dma_process_completed(mdma);
पूर्ण

/* Submit descriptor to hardware */
अटल dma_cookie_t mpc_dma_tx_submit(काष्ठा dma_async_tx_descriptor *txd)
अणु
	काष्ठा mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(txd->chan);
	काष्ठा mpc_dma_desc *mdesc;
	अचिन्हित दीर्घ flags;
	dma_cookie_t cookie;

	mdesc = container_of(txd, काष्ठा mpc_dma_desc, desc);

	spin_lock_irqsave(&mchan->lock, flags);

	/* Move descriptor to queue */
	list_move_tail(&mdesc->node, &mchan->queued);

	/* If channel is idle, execute all queued descriptors */
	अगर (list_empty(&mchan->active))
		mpc_dma_execute(mchan);

	/* Update cookie */
	cookie = dma_cookie_assign(txd);
	spin_unlock_irqrestore(&mchan->lock, flags);

	वापस cookie;
पूर्ण

/* Alloc channel resources */
अटल पूर्णांक mpc_dma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा mpc_dma *mdma = dma_chan_to_mpc_dma(chan);
	काष्ठा mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	काष्ठा mpc_dma_desc *mdesc;
	काष्ठा mpc_dma_tcd *tcd;
	dma_addr_t tcd_paddr;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(descs);
	पूर्णांक i;

	/* Alloc DMA memory क्रम Transfer Control Descriptors */
	tcd = dma_alloc_coherent(mdma->dma.dev,
			MPC_DMA_DESCRIPTORS * माप(काष्ठा mpc_dma_tcd),
							&tcd_paddr, GFP_KERNEL);
	अगर (!tcd)
		वापस -ENOMEM;

	/* Alloc descriptors क्रम this channel */
	क्रम (i = 0; i < MPC_DMA_DESCRIPTORS; i++) अणु
		mdesc = kzalloc(माप(काष्ठा mpc_dma_desc), GFP_KERNEL);
		अगर (!mdesc) अणु
			dev_notice(mdma->dma.dev,
				"Memory allocation error. Allocated only %u descriptors\n", i);
			अवरोध;
		पूर्ण

		dma_async_tx_descriptor_init(&mdesc->desc, chan);
		mdesc->desc.flags = DMA_CTRL_ACK;
		mdesc->desc.tx_submit = mpc_dma_tx_submit;

		mdesc->tcd = &tcd[i];
		mdesc->tcd_paddr = tcd_paddr + (i * माप(काष्ठा mpc_dma_tcd));

		list_add_tail(&mdesc->node, &descs);
	पूर्ण

	/* Return error only अगर no descriptors were allocated */
	अगर (i == 0) अणु
		dma_मुक्त_coherent(mdma->dma.dev,
			MPC_DMA_DESCRIPTORS * माप(काष्ठा mpc_dma_tcd),
								tcd, tcd_paddr);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&mchan->lock, flags);
	mchan->tcd = tcd;
	mchan->tcd_paddr = tcd_paddr;
	list_splice_tail_init(&descs, &mchan->मुक्त);
	spin_unlock_irqrestore(&mchan->lock, flags);

	/* Enable Error Interrupt */
	out_8(&mdma->regs->dmaseei, chan->chan_id);

	वापस 0;
पूर्ण

/* Free channel resources */
अटल व्योम mpc_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा mpc_dma *mdma = dma_chan_to_mpc_dma(chan);
	काष्ठा mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	काष्ठा mpc_dma_desc *mdesc, *पंचांगp;
	काष्ठा mpc_dma_tcd *tcd;
	dma_addr_t tcd_paddr;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(descs);

	spin_lock_irqsave(&mchan->lock, flags);

	/* Channel must be idle */
	BUG_ON(!list_empty(&mchan->prepared));
	BUG_ON(!list_empty(&mchan->queued));
	BUG_ON(!list_empty(&mchan->active));
	BUG_ON(!list_empty(&mchan->completed));

	/* Move data */
	list_splice_tail_init(&mchan->मुक्त, &descs);
	tcd = mchan->tcd;
	tcd_paddr = mchan->tcd_paddr;

	spin_unlock_irqrestore(&mchan->lock, flags);

	/* Free DMA memory used by descriptors */
	dma_मुक्त_coherent(mdma->dma.dev,
			MPC_DMA_DESCRIPTORS * माप(काष्ठा mpc_dma_tcd),
								tcd, tcd_paddr);

	/* Free descriptors */
	list_क्रम_each_entry_safe(mdesc, पंचांगp, &descs, node)
		kमुक्त(mdesc);

	/* Disable Error Interrupt */
	out_8(&mdma->regs->dmaceei, chan->chan_id);
पूर्ण

/* Send all pending descriptor to hardware */
अटल व्योम mpc_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	/*
	 * We are posting descriptors to the hardware as soon as
	 * they are पढ़ोy, so this function करोes nothing.
	 */
पूर्ण

/* Check request completion status */
अटल क्रमागत dma_status
mpc_dma_tx_status(काष्ठा dma_chan *chan, dma_cookie_t cookie,
	       काष्ठा dma_tx_state *txstate)
अणु
	वापस dma_cookie_status(chan, cookie, txstate);
पूर्ण

/* Prepare descriptor क्रम memory to memory copy */
अटल काष्ठा dma_async_tx_descriptor *
mpc_dma_prep_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dst, dma_addr_t src,
					माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mpc_dma *mdma = dma_chan_to_mpc_dma(chan);
	काष्ठा mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	काष्ठा mpc_dma_desc *mdesc = शून्य;
	काष्ठा mpc_dma_tcd *tcd;
	अचिन्हित दीर्घ अगरlags;

	/* Get मुक्त descriptor */
	spin_lock_irqsave(&mchan->lock, अगरlags);
	अगर (!list_empty(&mchan->मुक्त)) अणु
		mdesc = list_first_entry(&mchan->मुक्त, काष्ठा mpc_dma_desc,
									node);
		list_del(&mdesc->node);
	पूर्ण
	spin_unlock_irqrestore(&mchan->lock, अगरlags);

	अगर (!mdesc) अणु
		/* try to मुक्त completed descriptors */
		mpc_dma_process_completed(mdma);
		वापस शून्य;
	पूर्ण

	mdesc->error = 0;
	mdesc->will_access_peripheral = 0;
	tcd = mdesc->tcd;

	/* Prepare Transfer Control Descriptor क्रम this transaction */
	स_रखो(tcd, 0, माप(काष्ठा mpc_dma_tcd));

	अगर (IS_ALIGNED(src | dst | len, 32)) अणु
		tcd->ssize = MPC_DMA_TSIZE_32;
		tcd->dsize = MPC_DMA_TSIZE_32;
		tcd->soff = 32;
		tcd->करोff = 32;
	पूर्ण अन्यथा अगर (!mdma->is_mpc8308 && IS_ALIGNED(src | dst | len, 16)) अणु
		/* MPC8308 करोesn't support 16 byte transfers */
		tcd->ssize = MPC_DMA_TSIZE_16;
		tcd->dsize = MPC_DMA_TSIZE_16;
		tcd->soff = 16;
		tcd->करोff = 16;
	पूर्ण अन्यथा अगर (IS_ALIGNED(src | dst | len, 4)) अणु
		tcd->ssize = MPC_DMA_TSIZE_4;
		tcd->dsize = MPC_DMA_TSIZE_4;
		tcd->soff = 4;
		tcd->करोff = 4;
	पूर्ण अन्यथा अगर (IS_ALIGNED(src | dst | len, 2)) अणु
		tcd->ssize = MPC_DMA_TSIZE_2;
		tcd->dsize = MPC_DMA_TSIZE_2;
		tcd->soff = 2;
		tcd->करोff = 2;
	पूर्ण अन्यथा अणु
		tcd->ssize = MPC_DMA_TSIZE_1;
		tcd->dsize = MPC_DMA_TSIZE_1;
		tcd->soff = 1;
		tcd->करोff = 1;
	पूर्ण

	tcd->saddr = src;
	tcd->daddr = dst;
	tcd->nbytes = len;
	tcd->biter = 1;
	tcd->citer = 1;

	/* Place descriptor in prepared list */
	spin_lock_irqsave(&mchan->lock, अगरlags);
	list_add_tail(&mdesc->node, &mchan->prepared);
	spin_unlock_irqrestore(&mchan->lock, अगरlags);

	वापस &mdesc->desc;
पूर्ण

अंतरभूत u8 buswidth_to_dmatsize(u8 buswidth)
अणु
	u8 res;

	क्रम (res = 0; buswidth > 1; buswidth /= 2)
		res++;
	वापस res;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
mpc_dma_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा mpc_dma *mdma = dma_chan_to_mpc_dma(chan);
	काष्ठा mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	काष्ठा mpc_dma_desc *mdesc = शून्य;
	dma_addr_t per_paddr;
	u32 tcd_nunits;
	काष्ठा mpc_dma_tcd *tcd;
	अचिन्हित दीर्घ अगरlags;
	काष्ठा scatterlist *sg;
	माप_प्रकार len;
	पूर्णांक iter, i;

	/* Currently there is no proper support क्रम scatter/gather */
	अगर (sg_len != 1)
		वापस शून्य;

	अगर (!is_slave_direction(direction))
		वापस शून्य;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		spin_lock_irqsave(&mchan->lock, अगरlags);

		mdesc = list_first_entry(&mchan->मुक्त,
						काष्ठा mpc_dma_desc, node);
		अगर (!mdesc) अणु
			spin_unlock_irqrestore(&mchan->lock, अगरlags);
			/* Try to मुक्त completed descriptors */
			mpc_dma_process_completed(mdma);
			वापस शून्य;
		पूर्ण

		list_del(&mdesc->node);

		अगर (direction == DMA_DEV_TO_MEM) अणु
			per_paddr = mchan->src_per_paddr;
			tcd_nunits = mchan->src_tcd_nunits;
		पूर्ण अन्यथा अणु
			per_paddr = mchan->dst_per_paddr;
			tcd_nunits = mchan->dst_tcd_nunits;
		पूर्ण

		spin_unlock_irqrestore(&mchan->lock, अगरlags);

		अगर (per_paddr == 0 || tcd_nunits == 0)
			जाओ err_prep;

		mdesc->error = 0;
		mdesc->will_access_peripheral = 1;

		/* Prepare Transfer Control Descriptor क्रम this transaction */
		tcd = mdesc->tcd;

		स_रखो(tcd, 0, माप(काष्ठा mpc_dma_tcd));

		अगर (direction == DMA_DEV_TO_MEM) अणु
			tcd->saddr = per_paddr;
			tcd->daddr = sg_dma_address(sg);

			अगर (!IS_ALIGNED(sg_dma_address(sg), mchan->dwidth))
				जाओ err_prep;

			tcd->soff = 0;
			tcd->करोff = mchan->dwidth;
		पूर्ण अन्यथा अणु
			tcd->saddr = sg_dma_address(sg);
			tcd->daddr = per_paddr;

			अगर (!IS_ALIGNED(sg_dma_address(sg), mchan->swidth))
				जाओ err_prep;

			tcd->soff = mchan->swidth;
			tcd->करोff = 0;
		पूर्ण

		tcd->ssize = buswidth_to_dmatsize(mchan->swidth);
		tcd->dsize = buswidth_to_dmatsize(mchan->dwidth);

		अगर (mdma->is_mpc8308) अणु
			tcd->nbytes = sg_dma_len(sg);
			अगर (!IS_ALIGNED(tcd->nbytes, mchan->swidth))
				जाओ err_prep;

			/* No major loops क्रम MPC8303 */
			tcd->biter = 1;
			tcd->citer = 1;
		पूर्ण अन्यथा अणु
			len = sg_dma_len(sg);
			tcd->nbytes = tcd_nunits * tcd->ssize;
			अगर (!IS_ALIGNED(len, tcd->nbytes))
				जाओ err_prep;

			iter = len / tcd->nbytes;
			अगर (iter >= 1 << 15) अणु
				/* len is too big */
				जाओ err_prep;
			पूर्ण
			/* citer_linkch contains the high bits of iter */
			tcd->biter = iter & 0x1ff;
			tcd->biter_linkch = iter >> 9;
			tcd->citer = tcd->biter;
			tcd->citer_linkch = tcd->biter_linkch;
		पूर्ण

		tcd->e_sg = 0;
		tcd->d_req = 1;

		/* Place descriptor in prepared list */
		spin_lock_irqsave(&mchan->lock, अगरlags);
		list_add_tail(&mdesc->node, &mchan->prepared);
		spin_unlock_irqrestore(&mchan->lock, अगरlags);
	पूर्ण

	वापस &mdesc->desc;

err_prep:
	/* Put the descriptor back */
	spin_lock_irqsave(&mchan->lock, अगरlags);
	list_add_tail(&mdesc->node, &mchan->मुक्त);
	spin_unlock_irqrestore(&mchan->lock, अगरlags);

	वापस शून्य;
पूर्ण

अंतरभूत bool is_buswidth_valid(u8 buswidth, bool is_mpc8308)
अणु
	चयन (buswidth) अणु
	हाल 16:
		अगर (is_mpc8308)
			वापस false;
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 32:
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक mpc_dma_device_config(काष्ठा dma_chan *chan,
				 काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	काष्ठा mpc_dma *mdma = dma_chan_to_mpc_dma(&mchan->chan);
	अचिन्हित दीर्घ flags;

	/*
	 * Software स्थिरraपूर्णांकs:
	 *  - only transfers between a peripheral device and memory are
	 *     supported
	 *  - transfer chunk sizes of 1, 2, 4, 16 (क्रम MPC512x), and 32 bytes
	 *     are supported, and, consequently, source addresses and
	 *     destination addresses; must be aligned accordingly; furthermore,
	 *     क्रम MPC512x SoCs, the transfer size must be aligned on (chunk
	 *     size * maxburst)
	 *  - during the transfer, the RAM address is incremented by the size
	 *     of transfer chunk
	 *  - the peripheral port's address is स्थिरant during the transfer.
	 */

	अगर (!IS_ALIGNED(cfg->src_addr, cfg->src_addr_width) ||
	    !IS_ALIGNED(cfg->dst_addr, cfg->dst_addr_width)) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (!is_buswidth_valid(cfg->src_addr_width, mdma->is_mpc8308) ||
	    !is_buswidth_valid(cfg->dst_addr_width, mdma->is_mpc8308))
		वापस -EINVAL;

	spin_lock_irqsave(&mchan->lock, flags);

	mchan->src_per_paddr = cfg->src_addr;
	mchan->src_tcd_nunits = cfg->src_maxburst;
	mchan->swidth = cfg->src_addr_width;
	mchan->dst_per_paddr = cfg->dst_addr;
	mchan->dst_tcd_nunits = cfg->dst_maxburst;
	mchan->dwidth = cfg->dst_addr_width;

	/* Apply शेषs */
	अगर (mchan->src_tcd_nunits == 0)
		mchan->src_tcd_nunits = 1;
	अगर (mchan->dst_tcd_nunits == 0)
		mchan->dst_tcd_nunits = 1;

	spin_unlock_irqrestore(&mchan->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc_dma_device_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा mpc_dma_chan *mchan = dma_chan_to_mpc_dma_chan(chan);
	काष्ठा mpc_dma *mdma = dma_chan_to_mpc_dma(chan);
	अचिन्हित दीर्घ flags;

	/* Disable channel requests */
	spin_lock_irqsave(&mchan->lock, flags);

	out_8(&mdma->regs->dmacerq, chan->chan_id);
	list_splice_tail_init(&mchan->prepared, &mchan->मुक्त);
	list_splice_tail_init(&mchan->queued, &mchan->मुक्त);
	list_splice_tail_init(&mchan->active, &mchan->मुक्त);

	spin_unlock_irqrestore(&mchan->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mpc_dma_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dn = op->dev.of_node;
	काष्ठा device *dev = &op->dev;
	काष्ठा dma_device *dma;
	काष्ठा mpc_dma *mdma;
	काष्ठा mpc_dma_chan *mchan;
	काष्ठा resource res;
	uदीर्घ regs_start, regs_size;
	पूर्णांक retval, i;
	u8 chancnt;

	mdma = devm_kzalloc(dev, माप(काष्ठा mpc_dma), GFP_KERNEL);
	अगर (!mdma) अणु
		retval = -ENOMEM;
		जाओ err;
	पूर्ण

	mdma->irq = irq_of_parse_and_map(dn, 0);
	अगर (!mdma->irq) अणु
		dev_err(dev, "Error mapping IRQ!\n");
		retval = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (of_device_is_compatible(dn, "fsl,mpc8308-dma")) अणु
		mdma->is_mpc8308 = 1;
		mdma->irq2 = irq_of_parse_and_map(dn, 1);
		अगर (!mdma->irq2) अणु
			dev_err(dev, "Error mapping IRQ!\n");
			retval = -EINVAL;
			जाओ err_dispose1;
		पूर्ण
	पूर्ण

	retval = of_address_to_resource(dn, 0, &res);
	अगर (retval) अणु
		dev_err(dev, "Error parsing memory region!\n");
		जाओ err_dispose2;
	पूर्ण

	regs_start = res.start;
	regs_size = resource_size(&res);

	अगर (!devm_request_mem_region(dev, regs_start, regs_size, DRV_NAME)) अणु
		dev_err(dev, "Error requesting memory region!\n");
		retval = -EBUSY;
		जाओ err_dispose2;
	पूर्ण

	mdma->regs = devm_ioremap(dev, regs_start, regs_size);
	अगर (!mdma->regs) अणु
		dev_err(dev, "Error mapping memory region!\n");
		retval = -ENOMEM;
		जाओ err_dispose2;
	पूर्ण

	mdma->tcd = (काष्ठा mpc_dma_tcd *)((u8 *)(mdma->regs)
							+ MPC_DMA_TCD_OFFSET);

	retval = request_irq(mdma->irq, &mpc_dma_irq, 0, DRV_NAME, mdma);
	अगर (retval) अणु
		dev_err(dev, "Error requesting IRQ!\n");
		retval = -EINVAL;
		जाओ err_dispose2;
	पूर्ण

	अगर (mdma->is_mpc8308) अणु
		retval = request_irq(mdma->irq2, &mpc_dma_irq, 0,
							DRV_NAME, mdma);
		अगर (retval) अणु
			dev_err(dev, "Error requesting IRQ2!\n");
			retval = -EINVAL;
			जाओ err_मुक्त1;
		पूर्ण
	पूर्ण

	spin_lock_init(&mdma->error_status_lock);

	dma = &mdma->dma;
	dma->dev = dev;
	dma->device_alloc_chan_resources = mpc_dma_alloc_chan_resources;
	dma->device_मुक्त_chan_resources = mpc_dma_मुक्त_chan_resources;
	dma->device_issue_pending = mpc_dma_issue_pending;
	dma->device_tx_status = mpc_dma_tx_status;
	dma->device_prep_dma_स_नकल = mpc_dma_prep_स_नकल;
	dma->device_prep_slave_sg = mpc_dma_prep_slave_sg;
	dma->device_config = mpc_dma_device_config;
	dma->device_terminate_all = mpc_dma_device_terminate_all;

	INIT_LIST_HEAD(&dma->channels);
	dma_cap_set(DMA_MEMCPY, dma->cap_mask);
	dma_cap_set(DMA_SLAVE, dma->cap_mask);

	अगर (mdma->is_mpc8308)
		chancnt = MPC8308_DMACHAN_MAX;
	अन्यथा
		chancnt = MPC512x_DMACHAN_MAX;

	क्रम (i = 0; i < chancnt; i++) अणु
		mchan = &mdma->channels[i];

		mchan->chan.device = dma;
		dma_cookie_init(&mchan->chan);

		INIT_LIST_HEAD(&mchan->मुक्त);
		INIT_LIST_HEAD(&mchan->prepared);
		INIT_LIST_HEAD(&mchan->queued);
		INIT_LIST_HEAD(&mchan->active);
		INIT_LIST_HEAD(&mchan->completed);

		spin_lock_init(&mchan->lock);
		list_add_tail(&mchan->chan.device_node, &dma->channels);
	पूर्ण

	tasklet_setup(&mdma->tasklet, mpc_dma_tasklet);

	/*
	 * Configure DMA Engine:
	 * - Dynamic घड़ी,
	 * - Round-robin group arbitration,
	 * - Round-robin channel arbitration.
	 */
	अगर (mdma->is_mpc8308) अणु
		/* MPC8308 has 16 channels and lacks some रेजिस्टरs */
		out_be32(&mdma->regs->dmacr, MPC_DMA_DMACR_ERCA);

		/* enable snooping */
		out_be32(&mdma->regs->dmagpor, MPC_DMA_DMAGPOR_SNOOP_ENABLE);
		/* Disable error पूर्णांकerrupts */
		out_be32(&mdma->regs->dmaeeil, 0);

		/* Clear पूर्णांकerrupts status */
		out_be32(&mdma->regs->dमुख्यtl, 0xFFFF);
		out_be32(&mdma->regs->dmaerrl, 0xFFFF);
	पूर्ण अन्यथा अणु
		out_be32(&mdma->regs->dmacr, MPC_DMA_DMACR_EDCG |
						MPC_DMA_DMACR_ERGA |
						MPC_DMA_DMACR_ERCA);

		/* Disable hardware DMA requests */
		out_be32(&mdma->regs->dmaerqh, 0);
		out_be32(&mdma->regs->dmaerql, 0);

		/* Disable error पूर्णांकerrupts */
		out_be32(&mdma->regs->dmaeeih, 0);
		out_be32(&mdma->regs->dmaeeil, 0);

		/* Clear पूर्णांकerrupts status */
		out_be32(&mdma->regs->dमुख्यth, 0xFFFFFFFF);
		out_be32(&mdma->regs->dमुख्यtl, 0xFFFFFFFF);
		out_be32(&mdma->regs->dmaerrh, 0xFFFFFFFF);
		out_be32(&mdma->regs->dmaerrl, 0xFFFFFFFF);

		/* Route पूर्णांकerrupts to IPIC */
		out_be32(&mdma->regs->dmaihsa, 0);
		out_be32(&mdma->regs->dmailsa, 0);
	पूर्ण

	/* Register DMA engine */
	dev_set_drvdata(dev, mdma);
	retval = dma_async_device_रेजिस्टर(dma);
	अगर (retval)
		जाओ err_मुक्त2;

	/* Register with OF helpers क्रम DMA lookups (nonfatal) */
	अगर (dev->of_node) अणु
		retval = of_dma_controller_रेजिस्टर(dev->of_node,
						of_dma_xlate_by_chan_id, mdma);
		अगर (retval)
			dev_warn(dev, "Could not register for OF lookup\n");
	पूर्ण

	वापस 0;

err_मुक्त2:
	अगर (mdma->is_mpc8308)
		मुक्त_irq(mdma->irq2, mdma);
err_मुक्त1:
	मुक्त_irq(mdma->irq, mdma);
err_dispose2:
	अगर (mdma->is_mpc8308)
		irq_dispose_mapping(mdma->irq2);
err_dispose1:
	irq_dispose_mapping(mdma->irq);
err:
	वापस retval;
पूर्ण

अटल पूर्णांक mpc_dma_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device *dev = &op->dev;
	काष्ठा mpc_dma *mdma = dev_get_drvdata(dev);

	अगर (dev->of_node)
		of_dma_controller_मुक्त(dev->of_node);
	dma_async_device_unरेजिस्टर(&mdma->dma);
	अगर (mdma->is_mpc8308) अणु
		मुक्त_irq(mdma->irq2, mdma);
		irq_dispose_mapping(mdma->irq2);
	पूर्ण
	मुक्त_irq(mdma->irq, mdma);
	irq_dispose_mapping(mdma->irq);
	tasklet_समाप्त(&mdma->tasklet);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mpc_dma_match[] = अणु
	अणु .compatible = "fsl,mpc5121-dma", पूर्ण,
	अणु .compatible = "fsl,mpc8308-dma", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpc_dma_match);

अटल काष्ठा platक्रमm_driver mpc_dma_driver = अणु
	.probe		= mpc_dma_probe,
	.हटाओ		= mpc_dma_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table	= mpc_dma_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mpc_dma_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Piotr Ziecik <kosmo@semihalf.com>");
