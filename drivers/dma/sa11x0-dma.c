<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SA11x0 DMAengine support
 *
 * Copyright (C) 2012 Russell King
 *   Derived in part from arch/arm/mach-sa1100/dma.c,
 *   Copyright (C) 2000, 2001 by Nicolas Pitre
 */
#समावेश <linux/sched.h>
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "virt-dma.h"

#घोषणा NR_PHY_CHAN	6
#घोषणा DMA_ALIGN	3
#घोषणा DMA_MAX_SIZE	0x1fff
#घोषणा DMA_CHUNK_SIZE	0x1000

#घोषणा DMA_DDAR	0x00
#घोषणा DMA_DCSR_S	0x04
#घोषणा DMA_DCSR_C	0x08
#घोषणा DMA_DCSR_R	0x0c
#घोषणा DMA_DBSA	0x10
#घोषणा DMA_DBTA	0x14
#घोषणा DMA_DBSB	0x18
#घोषणा DMA_DBTB	0x1c
#घोषणा DMA_SIZE	0x20

#घोषणा DCSR_RUN	(1 << 0)
#घोषणा DCSR_IE		(1 << 1)
#घोषणा DCSR_ERROR	(1 << 2)
#घोषणा DCSR_DONEA	(1 << 3)
#घोषणा DCSR_STRTA	(1 << 4)
#घोषणा DCSR_DONEB	(1 << 5)
#घोषणा DCSR_STRTB	(1 << 6)
#घोषणा DCSR_BIU	(1 << 7)

#घोषणा DDAR_RW		(1 << 0)	/* 0 = W, 1 = R */
#घोषणा DDAR_E		(1 << 1)	/* 0 = LE, 1 = BE */
#घोषणा DDAR_BS		(1 << 2)	/* 0 = BS4, 1 = BS8 */
#घोषणा DDAR_DW		(1 << 3)	/* 0 = 8b, 1 = 16b */
#घोषणा DDAR_Ser0UDCTr	(0x0 << 4)
#घोषणा DDAR_Ser0UDCRc	(0x1 << 4)
#घोषणा DDAR_Ser1SDLCTr	(0x2 << 4)
#घोषणा DDAR_Ser1SDLCRc	(0x3 << 4)
#घोषणा DDAR_Ser1UARTTr	(0x4 << 4)
#घोषणा DDAR_Ser1UARTRc	(0x5 << 4)
#घोषणा DDAR_Ser2ICPTr	(0x6 << 4)
#घोषणा DDAR_Ser2ICPRc	(0x7 << 4)
#घोषणा DDAR_Ser3UARTTr	(0x8 << 4)
#घोषणा DDAR_Ser3UARTRc	(0x9 << 4)
#घोषणा DDAR_Ser4MCP0Tr	(0xa << 4)
#घोषणा DDAR_Ser4MCP0Rc	(0xb << 4)
#घोषणा DDAR_Ser4MCP1Tr	(0xc << 4)
#घोषणा DDAR_Ser4MCP1Rc	(0xd << 4)
#घोषणा DDAR_Ser4SSPTr	(0xe << 4)
#घोषणा DDAR_Ser4SSPRc	(0xf << 4)

काष्ठा sa11x0_dma_sg अणु
	u32			addr;
	u32			len;
पूर्ण;

काष्ठा sa11x0_dma_desc अणु
	काष्ठा virt_dma_desc	vd;

	u32			ddar;
	माप_प्रकार			size;
	अचिन्हित		period;
	bool			cyclic;

	अचिन्हित		sglen;
	काष्ठा sa11x0_dma_sg	sg[];
पूर्ण;

काष्ठा sa11x0_dma_phy;

काष्ठा sa11x0_dma_chan अणु
	काष्ठा virt_dma_chan	vc;

	/* रक्षित by c->vc.lock */
	काष्ठा sa11x0_dma_phy	*phy;
	क्रमागत dma_status		status;

	/* रक्षित by d->lock */
	काष्ठा list_head	node;

	u32			ddar;
	स्थिर अक्षर		*name;
पूर्ण;

काष्ठा sa11x0_dma_phy अणु
	व्योम __iomem		*base;
	काष्ठा sa11x0_dma_dev	*dev;
	अचिन्हित		num;

	काष्ठा sa11x0_dma_chan	*vchan;

	/* Protected by c->vc.lock */
	अचिन्हित		sg_load;
	काष्ठा sa11x0_dma_desc	*txd_load;
	अचिन्हित		sg_करोne;
	काष्ठा sa11x0_dma_desc	*txd_करोne;
	u32			dbs[2];
	u32			dbt[2];
	u32			dcsr;
पूर्ण;

काष्ठा sa11x0_dma_dev अणु
	काष्ठा dma_device	slave;
	व्योम __iomem		*base;
	spinlock_t		lock;
	काष्ठा tasklet_काष्ठा	task;
	काष्ठा list_head	chan_pending;
	काष्ठा sa11x0_dma_phy	phy[NR_PHY_CHAN];
पूर्ण;

अटल काष्ठा sa11x0_dma_chan *to_sa11x0_dma_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा sa11x0_dma_chan, vc.chan);
पूर्ण

अटल काष्ठा sa11x0_dma_dev *to_sa11x0_dma(काष्ठा dma_device *dmadev)
अणु
	वापस container_of(dmadev, काष्ठा sa11x0_dma_dev, slave);
पूर्ण

अटल काष्ठा sa11x0_dma_desc *sa11x0_dma_next_desc(काष्ठा sa11x0_dma_chan *c)
अणु
	काष्ठा virt_dma_desc *vd = vchan_next_desc(&c->vc);

	वापस vd ? container_of(vd, काष्ठा sa11x0_dma_desc, vd) : शून्य;
पूर्ण

अटल व्योम sa11x0_dma_मुक्त_desc(काष्ठा virt_dma_desc *vd)
अणु
	kमुक्त(container_of(vd, काष्ठा sa11x0_dma_desc, vd));
पूर्ण

अटल व्योम sa11x0_dma_start_desc(काष्ठा sa11x0_dma_phy *p, काष्ठा sa11x0_dma_desc *txd)
अणु
	list_del(&txd->vd.node);
	p->txd_load = txd;
	p->sg_load = 0;

	dev_vdbg(p->dev->slave.dev, "pchan %u: txd %p[%x]: starting: DDAR:%x\n",
		p->num, &txd->vd, txd->vd.tx.cookie, txd->ddar);
पूर्ण

अटल व्योम noअंतरभूत sa11x0_dma_start_sg(काष्ठा sa11x0_dma_phy *p,
	काष्ठा sa11x0_dma_chan *c)
अणु
	काष्ठा sa11x0_dma_desc *txd = p->txd_load;
	काष्ठा sa11x0_dma_sg *sg;
	व्योम __iomem *base = p->base;
	अचिन्हित dbsx, dbtx;
	u32 dcsr;

	अगर (!txd)
		वापस;

	dcsr = पढ़ोl_relaxed(base + DMA_DCSR_R);

	/* Don't try to load the next transfer अगर both buffers are started */
	अगर ((dcsr & (DCSR_STRTA | DCSR_STRTB)) == (DCSR_STRTA | DCSR_STRTB))
		वापस;

	अगर (p->sg_load == txd->sglen) अणु
		अगर (!txd->cyclic) अणु
			काष्ठा sa11x0_dma_desc *txn = sa11x0_dma_next_desc(c);

			/*
			 * We have reached the end of the current descriptor.
			 * Peek at the next descriptor, and अगर compatible with
			 * the current, start processing it.
			 */
			अगर (txn && txn->ddar == txd->ddar) अणु
				txd = txn;
				sa11x0_dma_start_desc(p, txn);
			पूर्ण अन्यथा अणु
				p->txd_load = शून्य;
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Cyclic: reset back to beginning */
			p->sg_load = 0;
		पूर्ण
	पूर्ण

	sg = &txd->sg[p->sg_load++];

	/* Select buffer to load according to channel status */
	अगर (((dcsr & (DCSR_BIU | DCSR_STRTB)) == (DCSR_BIU | DCSR_STRTB)) ||
	    ((dcsr & (DCSR_BIU | DCSR_STRTA)) == 0)) अणु
		dbsx = DMA_DBSA;
		dbtx = DMA_DBTA;
		dcsr = DCSR_STRTA | DCSR_IE | DCSR_RUN;
	पूर्ण अन्यथा अणु
		dbsx = DMA_DBSB;
		dbtx = DMA_DBTB;
		dcsr = DCSR_STRTB | DCSR_IE | DCSR_RUN;
	पूर्ण

	ग_लिखोl_relaxed(sg->addr, base + dbsx);
	ग_लिखोl_relaxed(sg->len, base + dbtx);
	ग_लिखोl(dcsr, base + DMA_DCSR_S);

	dev_dbg(p->dev->slave.dev, "pchan %u: load: DCSR:%02x DBS%c:%08x DBT%c:%08x\n",
		p->num, dcsr,
		'A' + (dbsx == DMA_DBSB), sg->addr,
		'A' + (dbtx == DMA_DBTB), sg->len);
पूर्ण

अटल व्योम noअंतरभूत sa11x0_dma_complete(काष्ठा sa11x0_dma_phy *p,
	काष्ठा sa11x0_dma_chan *c)
अणु
	काष्ठा sa11x0_dma_desc *txd = p->txd_करोne;

	अगर (++p->sg_करोne == txd->sglen) अणु
		अगर (!txd->cyclic) अणु
			vchan_cookie_complete(&txd->vd);

			p->sg_करोne = 0;
			p->txd_करोne = p->txd_load;

			अगर (!p->txd_करोne)
				tasklet_schedule(&p->dev->task);
		पूर्ण अन्यथा अणु
			अगर ((p->sg_करोne % txd->period) == 0)
				vchan_cyclic_callback(&txd->vd);

			/* Cyclic: reset back to beginning */
			p->sg_करोne = 0;
		पूर्ण
	पूर्ण

	sa11x0_dma_start_sg(p, c);
पूर्ण

अटल irqवापस_t sa11x0_dma_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sa11x0_dma_phy *p = dev_id;
	काष्ठा sa11x0_dma_dev *d = p->dev;
	काष्ठा sa11x0_dma_chan *c;
	u32 dcsr;

	dcsr = पढ़ोl_relaxed(p->base + DMA_DCSR_R);
	अगर (!(dcsr & (DCSR_ERROR | DCSR_DONEA | DCSR_DONEB)))
		वापस IRQ_NONE;

	/* Clear reported status bits */
	ग_लिखोl_relaxed(dcsr & (DCSR_ERROR | DCSR_DONEA | DCSR_DONEB),
		p->base + DMA_DCSR_C);

	dev_dbg(d->slave.dev, "pchan %u: irq: DCSR:%02x\n", p->num, dcsr);

	अगर (dcsr & DCSR_ERROR) अणु
		dev_err(d->slave.dev, "pchan %u: error. DCSR:%02x DDAR:%08x DBSA:%08x DBTA:%08x DBSB:%08x DBTB:%08x\n",
			p->num, dcsr,
			पढ़ोl_relaxed(p->base + DMA_DDAR),
			पढ़ोl_relaxed(p->base + DMA_DBSA),
			पढ़ोl_relaxed(p->base + DMA_DBTA),
			पढ़ोl_relaxed(p->base + DMA_DBSB),
			पढ़ोl_relaxed(p->base + DMA_DBTB));
	पूर्ण

	c = p->vchan;
	अगर (c) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&c->vc.lock, flags);
		/*
		 * Now that we're holding the lock, check that the vchan
		 * really is associated with this pchan beक्रमe touching the
		 * hardware.  This should always succeed, because we won't
		 * change p->vchan or c->phy जबतक the channel is actively
		 * transferring.
		 */
		अगर (c->phy == p) अणु
			अगर (dcsr & DCSR_DONEA)
				sa11x0_dma_complete(p, c);
			अगर (dcsr & DCSR_DONEB)
				sa11x0_dma_complete(p, c);
		पूर्ण
		spin_unlock_irqrestore(&c->vc.lock, flags);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sa11x0_dma_start_txd(काष्ठा sa11x0_dma_chan *c)
अणु
	काष्ठा sa11x0_dma_desc *txd = sa11x0_dma_next_desc(c);

	/* If the issued list is empty, we have no further txds to process */
	अगर (txd) अणु
		काष्ठा sa11x0_dma_phy *p = c->phy;

		sa11x0_dma_start_desc(p, txd);
		p->txd_करोne = txd;
		p->sg_करोne = 0;

		/* The channel should not have any transfers started */
		WARN_ON(पढ़ोl_relaxed(p->base + DMA_DCSR_R) &
				      (DCSR_STRTA | DCSR_STRTB));

		/* Clear the run and start bits beक्रमe changing DDAR */
		ग_लिखोl_relaxed(DCSR_RUN | DCSR_STRTA | DCSR_STRTB,
			       p->base + DMA_DCSR_C);
		ग_लिखोl_relaxed(txd->ddar, p->base + DMA_DDAR);

		/* Try to start both buffers */
		sa11x0_dma_start_sg(p, c);
		sa11x0_dma_start_sg(p, c);
	पूर्ण
पूर्ण

अटल व्योम sa11x0_dma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा sa11x0_dma_dev *d = from_tasklet(d, t, task);
	काष्ठा sa11x0_dma_phy *p;
	काष्ठा sa11x0_dma_chan *c;
	अचिन्हित pch, pch_alloc = 0;

	dev_dbg(d->slave.dev, "tasklet enter\n");

	list_क्रम_each_entry(c, &d->slave.channels, vc.chan.device_node) अणु
		spin_lock_irq(&c->vc.lock);
		p = c->phy;
		अगर (p && !p->txd_करोne) अणु
			sa11x0_dma_start_txd(c);
			अगर (!p->txd_करोne) अणु
				/* No current txd associated with this channel */
				dev_dbg(d->slave.dev, "pchan %u: free\n", p->num);

				/* Mark this channel मुक्त */
				c->phy = शून्य;
				p->vchan = शून्य;
			पूर्ण
		पूर्ण
		spin_unlock_irq(&c->vc.lock);
	पूर्ण

	spin_lock_irq(&d->lock);
	क्रम (pch = 0; pch < NR_PHY_CHAN; pch++) अणु
		p = &d->phy[pch];

		अगर (p->vchan == शून्य && !list_empty(&d->chan_pending)) अणु
			c = list_first_entry(&d->chan_pending,
				काष्ठा sa11x0_dma_chan, node);
			list_del_init(&c->node);

			pch_alloc |= 1 << pch;

			/* Mark this channel allocated */
			p->vchan = c;

			dev_dbg(d->slave.dev, "pchan %u: alloc vchan %p\n", pch, &c->vc);
		पूर्ण
	पूर्ण
	spin_unlock_irq(&d->lock);

	क्रम (pch = 0; pch < NR_PHY_CHAN; pch++) अणु
		अगर (pch_alloc & (1 << pch)) अणु
			p = &d->phy[pch];
			c = p->vchan;

			spin_lock_irq(&c->vc.lock);
			c->phy = p;

			sa11x0_dma_start_txd(c);
			spin_unlock_irq(&c->vc.lock);
		पूर्ण
	पूर्ण

	dev_dbg(d->slave.dev, "tasklet exit\n");
पूर्ण


अटल व्योम sa11x0_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	काष्ठा sa11x0_dma_dev *d = to_sa11x0_dma(chan->device);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&d->lock, flags);
	list_del_init(&c->node);
	spin_unlock_irqrestore(&d->lock, flags);

	vchan_मुक्त_chan_resources(&c->vc);
पूर्ण

अटल dma_addr_t sa11x0_dma_pos(काष्ठा sa11x0_dma_phy *p)
अणु
	अचिन्हित reg;
	u32 dcsr;

	dcsr = पढ़ोl_relaxed(p->base + DMA_DCSR_R);

	अगर ((dcsr & (DCSR_BIU | DCSR_STRTA)) == DCSR_STRTA ||
	    (dcsr & (DCSR_BIU | DCSR_STRTB)) == DCSR_BIU)
		reg = DMA_DBSA;
	अन्यथा
		reg = DMA_DBSB;

	वापस पढ़ोl_relaxed(p->base + reg);
पूर्ण

अटल क्रमागत dma_status sa11x0_dma_tx_status(काष्ठा dma_chan *chan,
	dma_cookie_t cookie, काष्ठा dma_tx_state *state)
अणु
	काष्ठा sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	काष्ठा sa11x0_dma_dev *d = to_sa11x0_dma(chan->device);
	काष्ठा sa11x0_dma_phy *p;
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;
	क्रमागत dma_status ret;

	ret = dma_cookie_status(&c->vc.chan, cookie, state);
	अगर (ret == DMA_COMPLETE)
		वापस ret;

	अगर (!state)
		वापस c->status;

	spin_lock_irqsave(&c->vc.lock, flags);
	p = c->phy;

	/*
	 * If the cookie is on our issue queue, then the residue is
	 * its total size.
	 */
	vd = vchan_find_desc(&c->vc, cookie);
	अगर (vd) अणु
		state->residue = container_of(vd, काष्ठा sa11x0_dma_desc, vd)->size;
	पूर्ण अन्यथा अगर (!p) अणु
		state->residue = 0;
	पूर्ण अन्यथा अणु
		काष्ठा sa11x0_dma_desc *txd;
		माप_प्रकार bytes = 0;

		अगर (p->txd_करोne && p->txd_करोne->vd.tx.cookie == cookie)
			txd = p->txd_करोne;
		अन्यथा अगर (p->txd_load && p->txd_load->vd.tx.cookie == cookie)
			txd = p->txd_load;
		अन्यथा
			txd = शून्य;

		ret = c->status;
		अगर (txd) अणु
			dma_addr_t addr = sa11x0_dma_pos(p);
			अचिन्हित i;

			dev_vdbg(d->slave.dev, "tx_status: addr:%pad\n", &addr);

			क्रम (i = 0; i < txd->sglen; i++) अणु
				dev_vdbg(d->slave.dev, "tx_status: [%u] %x+%x\n",
					i, txd->sg[i].addr, txd->sg[i].len);
				अगर (addr >= txd->sg[i].addr &&
				    addr < txd->sg[i].addr + txd->sg[i].len) अणु
					अचिन्हित len;

					len = txd->sg[i].len -
						(addr - txd->sg[i].addr);
					dev_vdbg(d->slave.dev, "tx_status: [%u] +%x\n",
						i, len);
					bytes += len;
					i++;
					अवरोध;
				पूर्ण
			पूर्ण
			क्रम (; i < txd->sglen; i++) अणु
				dev_vdbg(d->slave.dev, "tx_status: [%u] %x+%x ++\n",
					i, txd->sg[i].addr, txd->sg[i].len);
				bytes += txd->sg[i].len;
			पूर्ण
		पूर्ण
		state->residue = bytes;
	पूर्ण
	spin_unlock_irqrestore(&c->vc.lock, flags);

	dev_vdbg(d->slave.dev, "tx_status: bytes 0x%x\n", state->residue);

	वापस ret;
पूर्ण

/*
 * Move pending txds to the issued list, and re-init pending list.
 * If not alपढ़ोy pending, add this channel to the list of pending
 * channels and trigger the tasklet to run.
 */
अटल व्योम sa11x0_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	काष्ठा sa11x0_dma_dev *d = to_sa11x0_dma(chan->device);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&c->vc.lock, flags);
	अगर (vchan_issue_pending(&c->vc)) अणु
		अगर (!c->phy) अणु
			spin_lock(&d->lock);
			अगर (list_empty(&c->node)) अणु
				list_add_tail(&c->node, &d->chan_pending);
				tasklet_schedule(&d->task);
				dev_dbg(d->slave.dev, "vchan %p: issued\n", &c->vc);
			पूर्ण
			spin_unlock(&d->lock);
		पूर्ण
	पूर्ण अन्यथा
		dev_dbg(d->slave.dev, "vchan %p: nothing to issue\n", &c->vc);
	spin_unlock_irqrestore(&c->vc.lock, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *sa11x0_dma_prep_slave_sg(
	काष्ठा dma_chan *chan, काष्ठा scatterlist *sg, अचिन्हित पूर्णांक sglen,
	क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	काष्ठा sa11x0_dma_desc *txd;
	काष्ठा scatterlist *sgent;
	अचिन्हित i, j = sglen;
	माप_प्रकार size = 0;

	/* SA11x0 channels can only operate in their native direction */
	अगर (dir != (c->ddar & DDAR_RW ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV)) अणु
		dev_err(chan->device->dev, "vchan %p: bad DMA direction: DDAR:%08x dir:%u\n",
			&c->vc, c->ddar, dir);
		वापस शून्य;
	पूर्ण

	/* Do not allow zero-sized txds */
	अगर (sglen == 0)
		वापस शून्य;

	क्रम_each_sg(sg, sgent, sglen, i) अणु
		dma_addr_t addr = sg_dma_address(sgent);
		अचिन्हित पूर्णांक len = sg_dma_len(sgent);

		अगर (len > DMA_MAX_SIZE)
			j += DIV_ROUND_UP(len, DMA_MAX_SIZE & ~DMA_ALIGN) - 1;
		अगर (addr & DMA_ALIGN) अणु
			dev_dbg(chan->device->dev, "vchan %p: bad buffer alignment: %pad\n",
				&c->vc, &addr);
			वापस शून्य;
		पूर्ण
	पूर्ण

	txd = kzalloc(काष्ठा_size(txd, sg, j), GFP_ATOMIC);
	अगर (!txd) अणु
		dev_dbg(chan->device->dev, "vchan %p: kzalloc failed\n", &c->vc);
		वापस शून्य;
	पूर्ण

	j = 0;
	क्रम_each_sg(sg, sgent, sglen, i) अणु
		dma_addr_t addr = sg_dma_address(sgent);
		अचिन्हित len = sg_dma_len(sgent);

		size += len;

		करो अणु
			अचिन्हित tlen = len;

			/*
			 * Check whether the transfer will fit.  If not, try
			 * to split the transfer up such that we end up with
			 * equal chunks - but make sure that we preserve the
			 * alignment.  This aव्योमs small segments.
			 */
			अगर (tlen > DMA_MAX_SIZE) अणु
				अचिन्हित mult = DIV_ROUND_UP(tlen,
					DMA_MAX_SIZE & ~DMA_ALIGN);

				tlen = (tlen / mult) & ~DMA_ALIGN;
			पूर्ण

			txd->sg[j].addr = addr;
			txd->sg[j].len = tlen;

			addr += tlen;
			len -= tlen;
			j++;
		पूर्ण जबतक (len);
	पूर्ण

	txd->ddar = c->ddar;
	txd->size = size;
	txd->sglen = j;

	dev_dbg(chan->device->dev, "vchan %p: txd %p: size %zu nr %u\n",
		&c->vc, &txd->vd, txd->size, txd->sglen);

	वापस vchan_tx_prep(&c->vc, &txd->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *sa11x0_dma_prep_dma_cyclic(
	काष्ठा dma_chan *chan, dma_addr_t addr, माप_प्रकार size, माप_प्रकार period,
	क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags)
अणु
	काष्ठा sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	काष्ठा sa11x0_dma_desc *txd;
	अचिन्हित i, j, k, sglen, sgperiod;

	/* SA11x0 channels can only operate in their native direction */
	अगर (dir != (c->ddar & DDAR_RW ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV)) अणु
		dev_err(chan->device->dev, "vchan %p: bad DMA direction: DDAR:%08x dir:%u\n",
			&c->vc, c->ddar, dir);
		वापस शून्य;
	पूर्ण

	sgperiod = DIV_ROUND_UP(period, DMA_MAX_SIZE & ~DMA_ALIGN);
	sglen = size * sgperiod / period;

	/* Do not allow zero-sized txds */
	अगर (sglen == 0)
		वापस शून्य;

	txd = kzalloc(काष्ठा_size(txd, sg, sglen), GFP_ATOMIC);
	अगर (!txd) अणु
		dev_dbg(chan->device->dev, "vchan %p: kzalloc failed\n", &c->vc);
		वापस शून्य;
	पूर्ण

	क्रम (i = k = 0; i < size / period; i++) अणु
		माप_प्रकार tlen, len = period;

		क्रम (j = 0; j < sgperiod; j++, k++) अणु
			tlen = len;

			अगर (tlen > DMA_MAX_SIZE) अणु
				अचिन्हित mult = DIV_ROUND_UP(tlen, DMA_MAX_SIZE & ~DMA_ALIGN);
				tlen = (tlen / mult) & ~DMA_ALIGN;
			पूर्ण

			txd->sg[k].addr = addr;
			txd->sg[k].len = tlen;
			addr += tlen;
			len -= tlen;
		पूर्ण

		WARN_ON(len != 0);
	पूर्ण

	WARN_ON(k != sglen);

	txd->ddar = c->ddar;
	txd->size = size;
	txd->sglen = sglen;
	txd->cyclic = 1;
	txd->period = sgperiod;

	वापस vchan_tx_prep(&c->vc, &txd->vd, DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
पूर्ण

अटल पूर्णांक sa11x0_dma_device_config(काष्ठा dma_chan *chan,
				    काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	u32 ddar = c->ddar & ((0xf << 4) | DDAR_RW);
	dma_addr_t addr;
	क्रमागत dma_slave_buswidth width;
	u32 maxburst;

	अगर (ddar & DDAR_RW) अणु
		addr = cfg->src_addr;
		width = cfg->src_addr_width;
		maxburst = cfg->src_maxburst;
	पूर्ण अन्यथा अणु
		addr = cfg->dst_addr;
		width = cfg->dst_addr_width;
		maxburst = cfg->dst_maxburst;
	पूर्ण

	अगर ((width != DMA_SLAVE_BUSWIDTH_1_BYTE &&
	     width != DMA_SLAVE_BUSWIDTH_2_BYTES) ||
	    (maxburst != 4 && maxburst != 8))
		वापस -EINVAL;

	अगर (width == DMA_SLAVE_BUSWIDTH_2_BYTES)
		ddar |= DDAR_DW;
	अगर (maxburst == 8)
		ddar |= DDAR_BS;

	dev_dbg(c->vc.chan.device->dev, "vchan %p: dma_slave_config addr %pad width %u burst %u\n",
		&c->vc, &addr, width, maxburst);

	c->ddar = ddar | (addr & 0xf0000000) | (addr & 0x003ffffc) << 6;

	वापस 0;
पूर्ण

अटल पूर्णांक sa11x0_dma_device_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	काष्ठा sa11x0_dma_dev *d = to_sa11x0_dma(chan->device);
	काष्ठा sa11x0_dma_phy *p;
	अचिन्हित दीर्घ flags;

	dev_dbg(d->slave.dev, "vchan %p: pause\n", &c->vc);
	spin_lock_irqsave(&c->vc.lock, flags);
	अगर (c->status == DMA_IN_PROGRESS) अणु
		c->status = DMA_PAUSED;

		p = c->phy;
		अगर (p) अणु
			ग_लिखोl(DCSR_RUN | DCSR_IE, p->base + DMA_DCSR_C);
		पूर्ण अन्यथा अणु
			spin_lock(&d->lock);
			list_del_init(&c->node);
			spin_unlock(&d->lock);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&c->vc.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sa11x0_dma_device_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	काष्ठा sa11x0_dma_dev *d = to_sa11x0_dma(chan->device);
	काष्ठा sa11x0_dma_phy *p;
	अचिन्हित दीर्घ flags;

	dev_dbg(d->slave.dev, "vchan %p: resume\n", &c->vc);
	spin_lock_irqsave(&c->vc.lock, flags);
	अगर (c->status == DMA_PAUSED) अणु
		c->status = DMA_IN_PROGRESS;

		p = c->phy;
		अगर (p) अणु
			ग_लिखोl(DCSR_RUN | DCSR_IE, p->base + DMA_DCSR_S);
		पूर्ण अन्यथा अगर (!list_empty(&c->vc.desc_issued)) अणु
			spin_lock(&d->lock);
			list_add_tail(&c->node, &d->chan_pending);
			spin_unlock(&d->lock);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&c->vc.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sa11x0_dma_device_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	काष्ठा sa11x0_dma_dev *d = to_sa11x0_dma(chan->device);
	काष्ठा sa11x0_dma_phy *p;
	LIST_HEAD(head);
	अचिन्हित दीर्घ flags;

	dev_dbg(d->slave.dev, "vchan %p: terminate all\n", &c->vc);
	/* Clear the tx descriptor lists */
	spin_lock_irqsave(&c->vc.lock, flags);
	vchan_get_all_descriptors(&c->vc, &head);

	p = c->phy;
	अगर (p) अणु
		dev_dbg(d->slave.dev, "pchan %u: terminating\n", p->num);
		/* vchan is asचिन्हित to a pchan - stop the channel */
		ग_लिखोl(DCSR_RUN | DCSR_IE |
		       DCSR_STRTA | DCSR_DONEA |
		       DCSR_STRTB | DCSR_DONEB,
		       p->base + DMA_DCSR_C);

		अगर (p->txd_load) अणु
			अगर (p->txd_load != p->txd_करोne)
				list_add_tail(&p->txd_load->vd.node, &head);
			p->txd_load = शून्य;
		पूर्ण
		अगर (p->txd_करोne) अणु
			list_add_tail(&p->txd_करोne->vd.node, &head);
			p->txd_करोne = शून्य;
		पूर्ण
		c->phy = शून्य;
		spin_lock(&d->lock);
		p->vchan = शून्य;
		spin_unlock(&d->lock);
		tasklet_schedule(&d->task);
	पूर्ण
	spin_unlock_irqrestore(&c->vc.lock, flags);
	vchan_dma_desc_मुक्त_list(&c->vc, &head);

	वापस 0;
पूर्ण

काष्ठा sa11x0_dma_channel_desc अणु
	u32 ddar;
	स्थिर अक्षर *name;
पूर्ण;

#घोषणा CD(d1, d2) अणु .ddar = DDAR_##d1 | d2, .name = #d1 पूर्ण
अटल स्थिर काष्ठा sa11x0_dma_channel_desc chan_desc[] = अणु
	CD(Ser0UDCTr, 0),
	CD(Ser0UDCRc, DDAR_RW),
	CD(Ser1SDLCTr, 0),
	CD(Ser1SDLCRc, DDAR_RW),
	CD(Ser1UARTTr, 0),
	CD(Ser1UARTRc, DDAR_RW),
	CD(Ser2ICPTr, 0),
	CD(Ser2ICPRc, DDAR_RW),
	CD(Ser3UARTTr, 0),
	CD(Ser3UARTRc, DDAR_RW),
	CD(Ser4MCP0Tr, 0),
	CD(Ser4MCP0Rc, DDAR_RW),
	CD(Ser4MCP1Tr, 0),
	CD(Ser4MCP1Rc, DDAR_RW),
	CD(Ser4SSPTr, 0),
	CD(Ser4SSPRc, DDAR_RW),
पूर्ण;

अटल स्थिर काष्ठा dma_slave_map sa11x0_dma_map[] = अणु
	अणु "sa11x0-ir", "tx", "Ser2ICPTr" पूर्ण,
	अणु "sa11x0-ir", "rx", "Ser2ICPRc" पूर्ण,
	अणु "sa11x0-ssp", "tx", "Ser4SSPTr" पूर्ण,
	अणु "sa11x0-ssp", "rx", "Ser4SSPRc" पूर्ण,
पूर्ण;

अटल bool sa11x0_dma_filter_fn(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
	स्थिर अक्षर *p = param;

	वापस !म_भेद(c->name, p);
पूर्ण

अटल पूर्णांक sa11x0_dma_init_dmadev(काष्ठा dma_device *dmadev,
	काष्ठा device *dev)
अणु
	अचिन्हित i;

	INIT_LIST_HEAD(&dmadev->channels);
	dmadev->dev = dev;
	dmadev->device_मुक्त_chan_resources = sa11x0_dma_मुक्त_chan_resources;
	dmadev->device_config = sa11x0_dma_device_config;
	dmadev->device_छोड़ो = sa11x0_dma_device_छोड़ो;
	dmadev->device_resume = sa11x0_dma_device_resume;
	dmadev->device_terminate_all = sa11x0_dma_device_terminate_all;
	dmadev->device_tx_status = sa11x0_dma_tx_status;
	dmadev->device_issue_pending = sa11x0_dma_issue_pending;

	क्रम (i = 0; i < ARRAY_SIZE(chan_desc); i++) अणु
		काष्ठा sa11x0_dma_chan *c;

		c = kzalloc(माप(*c), GFP_KERNEL);
		अगर (!c) अणु
			dev_err(dev, "no memory for channel %u\n", i);
			वापस -ENOMEM;
		पूर्ण

		c->status = DMA_IN_PROGRESS;
		c->ddar = chan_desc[i].ddar;
		c->name = chan_desc[i].name;
		INIT_LIST_HEAD(&c->node);

		c->vc.desc_मुक्त = sa11x0_dma_मुक्त_desc;
		vchan_init(&c->vc, dmadev);
	पूर्ण

	वापस dma_async_device_रेजिस्टर(dmadev);
पूर्ण

अटल पूर्णांक sa11x0_dma_request_irq(काष्ठा platक्रमm_device *pdev, पूर्णांक nr,
	व्योम *data)
अणु
	पूर्णांक irq = platक्रमm_get_irq(pdev, nr);

	अगर (irq <= 0)
		वापस -ENXIO;

	वापस request_irq(irq, sa11x0_dma_irq, 0, dev_name(&pdev->dev), data);
पूर्ण

अटल व्योम sa11x0_dma_मुक्त_irq(काष्ठा platक्रमm_device *pdev, पूर्णांक nr,
	व्योम *data)
अणु
	पूर्णांक irq = platक्रमm_get_irq(pdev, nr);
	अगर (irq > 0)
		मुक्त_irq(irq, data);
पूर्ण

अटल व्योम sa11x0_dma_मुक्त_channels(काष्ठा dma_device *dmadev)
अणु
	काष्ठा sa11x0_dma_chan *c, *cn;

	list_क्रम_each_entry_safe(c, cn, &dmadev->channels, vc.chan.device_node) अणु
		list_del(&c->vc.chan.device_node);
		tasklet_समाप्त(&c->vc.task);
		kमुक्त(c);
	पूर्ण
पूर्ण

अटल पूर्णांक sa11x0_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sa11x0_dma_dev *d;
	काष्ठा resource *res;
	अचिन्हित i;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENXIO;

	d = kzalloc(माप(*d), GFP_KERNEL);
	अगर (!d) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	spin_lock_init(&d->lock);
	INIT_LIST_HEAD(&d->chan_pending);

	d->slave.filter.fn = sa11x0_dma_filter_fn;
	d->slave.filter.mapcnt = ARRAY_SIZE(sa11x0_dma_map);
	d->slave.filter.map = sa11x0_dma_map;

	d->base = ioremap(res->start, resource_size(res));
	अगर (!d->base) अणु
		ret = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	tasklet_setup(&d->task, sa11x0_dma_tasklet);

	क्रम (i = 0; i < NR_PHY_CHAN; i++) अणु
		काष्ठा sa11x0_dma_phy *p = &d->phy[i];

		p->dev = d;
		p->num = i;
		p->base = d->base + i * DMA_SIZE;
		ग_लिखोl_relaxed(DCSR_RUN | DCSR_IE | DCSR_ERROR |
			DCSR_DONEA | DCSR_STRTA | DCSR_DONEB | DCSR_STRTB,
			p->base + DMA_DCSR_C);
		ग_लिखोl_relaxed(0, p->base + DMA_DDAR);

		ret = sa11x0_dma_request_irq(pdev, i, p);
		अगर (ret) अणु
			जबतक (i) अणु
				i--;
				sa11x0_dma_मुक्त_irq(pdev, i, &d->phy[i]);
			पूर्ण
			जाओ err_irq;
		पूर्ण
	पूर्ण

	dma_cap_set(DMA_SLAVE, d->slave.cap_mask);
	dma_cap_set(DMA_CYCLIC, d->slave.cap_mask);
	d->slave.device_prep_slave_sg = sa11x0_dma_prep_slave_sg;
	d->slave.device_prep_dma_cyclic = sa11x0_dma_prep_dma_cyclic;
	d->slave.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	d->slave.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	d->slave.src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
				   BIT(DMA_SLAVE_BUSWIDTH_2_BYTES);
	d->slave.dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
				   BIT(DMA_SLAVE_BUSWIDTH_2_BYTES);
	ret = sa11x0_dma_init_dmadev(&d->slave, &pdev->dev);
	अगर (ret) अणु
		dev_warn(d->slave.dev, "failed to register slave async device: %d\n",
			ret);
		जाओ err_slave_reg;
	पूर्ण

	platक्रमm_set_drvdata(pdev, d);
	वापस 0;

 err_slave_reg:
	sa11x0_dma_मुक्त_channels(&d->slave);
	क्रम (i = 0; i < NR_PHY_CHAN; i++)
		sa11x0_dma_मुक्त_irq(pdev, i, &d->phy[i]);
 err_irq:
	tasklet_समाप्त(&d->task);
	iounmap(d->base);
 err_ioremap:
	kमुक्त(d);
 err_alloc:
	वापस ret;
पूर्ण

अटल पूर्णांक sa11x0_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sa11x0_dma_dev *d = platक्रमm_get_drvdata(pdev);
	अचिन्हित pch;

	dma_async_device_unरेजिस्टर(&d->slave);

	sa11x0_dma_मुक्त_channels(&d->slave);
	क्रम (pch = 0; pch < NR_PHY_CHAN; pch++)
		sa11x0_dma_मुक्त_irq(pdev, pch, &d->phy[pch]);
	tasklet_समाप्त(&d->task);
	iounmap(d->base);
	kमुक्त(d);

	वापस 0;
पूर्ण

अटल पूर्णांक sa11x0_dma_suspend(काष्ठा device *dev)
अणु
	काष्ठा sa11x0_dma_dev *d = dev_get_drvdata(dev);
	अचिन्हित pch;

	क्रम (pch = 0; pch < NR_PHY_CHAN; pch++) अणु
		काष्ठा sa11x0_dma_phy *p = &d->phy[pch];
		u32 dcsr, saved_dcsr;

		dcsr = saved_dcsr = पढ़ोl_relaxed(p->base + DMA_DCSR_R);
		अगर (dcsr & DCSR_RUN) अणु
			ग_लिखोl(DCSR_RUN | DCSR_IE, p->base + DMA_DCSR_C);
			dcsr = पढ़ोl_relaxed(p->base + DMA_DCSR_R);
		पूर्ण

		saved_dcsr &= DCSR_RUN | DCSR_IE;
		अगर (dcsr & DCSR_BIU) अणु
			p->dbs[0] = पढ़ोl_relaxed(p->base + DMA_DBSB);
			p->dbt[0] = पढ़ोl_relaxed(p->base + DMA_DBTB);
			p->dbs[1] = पढ़ोl_relaxed(p->base + DMA_DBSA);
			p->dbt[1] = पढ़ोl_relaxed(p->base + DMA_DBTA);
			saved_dcsr |= (dcsr & DCSR_STRTA ? DCSR_STRTB : 0) |
				      (dcsr & DCSR_STRTB ? DCSR_STRTA : 0);
		पूर्ण अन्यथा अणु
			p->dbs[0] = पढ़ोl_relaxed(p->base + DMA_DBSA);
			p->dbt[0] = पढ़ोl_relaxed(p->base + DMA_DBTA);
			p->dbs[1] = पढ़ोl_relaxed(p->base + DMA_DBSB);
			p->dbt[1] = पढ़ोl_relaxed(p->base + DMA_DBTB);
			saved_dcsr |= dcsr & (DCSR_STRTA | DCSR_STRTB);
		पूर्ण
		p->dcsr = saved_dcsr;

		ग_लिखोl(DCSR_STRTA | DCSR_STRTB, p->base + DMA_DCSR_C);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sa11x0_dma_resume(काष्ठा device *dev)
अणु
	काष्ठा sa11x0_dma_dev *d = dev_get_drvdata(dev);
	अचिन्हित pch;

	क्रम (pch = 0; pch < NR_PHY_CHAN; pch++) अणु
		काष्ठा sa11x0_dma_phy *p = &d->phy[pch];
		काष्ठा sa11x0_dma_desc *txd = शून्य;
		u32 dcsr = पढ़ोl_relaxed(p->base + DMA_DCSR_R);

		WARN_ON(dcsr & (DCSR_BIU | DCSR_STRTA | DCSR_STRTB | DCSR_RUN));

		अगर (p->txd_करोne)
			txd = p->txd_करोne;
		अन्यथा अगर (p->txd_load)
			txd = p->txd_load;

		अगर (!txd)
			जारी;

		ग_लिखोl_relaxed(txd->ddar, p->base + DMA_DDAR);

		ग_लिखोl_relaxed(p->dbs[0], p->base + DMA_DBSA);
		ग_लिखोl_relaxed(p->dbt[0], p->base + DMA_DBTA);
		ग_लिखोl_relaxed(p->dbs[1], p->base + DMA_DBSB);
		ग_लिखोl_relaxed(p->dbt[1], p->base + DMA_DBTB);
		ग_लिखोl_relaxed(p->dcsr, p->base + DMA_DCSR_S);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sa11x0_dma_pm_ops = अणु
	.suspend_noirq = sa11x0_dma_suspend,
	.resume_noirq = sa11x0_dma_resume,
	.मुक्तze_noirq = sa11x0_dma_suspend,
	.thaw_noirq = sa11x0_dma_resume,
	.घातeroff_noirq = sa11x0_dma_suspend,
	.restore_noirq = sa11x0_dma_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver sa11x0_dma_driver = अणु
	.driver = अणु
		.name	= "sa11x0-dma",
		.pm	= &sa11x0_dma_pm_ops,
	पूर्ण,
	.probe		= sa11x0_dma_probe,
	.हटाओ		= sa11x0_dma_हटाओ,
पूर्ण;

अटल पूर्णांक __init sa11x0_dma_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sa11x0_dma_driver);
पूर्ण
subsys_initcall(sa11x0_dma_init);

अटल व्योम __निकास sa11x0_dma_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sa11x0_dma_driver);
पूर्ण
module_निकास(sa11x0_dma_निकास);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("SA-11x0 DMA driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sa11x0-dma");
