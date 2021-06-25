<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Thunderbolt driver - NHI driver
 *
 * The NHI (native host पूर्णांकerface) is the pci device that allows us to send and
 * receive frames from the thunderbolt bus.
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2018, Intel Corporation
 */

#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/property.h>
#समावेश <linux/platक्रमm_data/x86/apple.h>

#समावेश "nhi.h"
#समावेश "nhi_regs.h"
#समावेश "tb.h"

#घोषणा RING_TYPE(ring) ((ring)->is_tx ? "TX ring" : "RX ring")

#घोषणा RING_FIRST_USABLE_HOPID	1

/*
 * Minimal number of vectors when we use MSI-X. Two क्रम control channel
 * Rx/Tx and the rest four are क्रम cross करोमुख्य DMA paths.
 */
#घोषणा MSIX_MIN_VECS		6
#घोषणा MSIX_MAX_VECS		16

#घोषणा NHI_MAILBOX_TIMEOUT	500 /* ms */

अटल पूर्णांक ring_पूर्णांकerrupt_index(काष्ठा tb_ring *ring)
अणु
	पूर्णांक bit = ring->hop;
	अगर (!ring->is_tx)
		bit += ring->nhi->hop_count;
	वापस bit;
पूर्ण

/*
 * ring_पूर्णांकerrupt_active() - activate/deactivate पूर्णांकerrupts क्रम a single ring
 *
 * ring->nhi->lock must be held.
 */
अटल व्योम ring_पूर्णांकerrupt_active(काष्ठा tb_ring *ring, bool active)
अणु
	पूर्णांक reg = REG_RING_INTERRUPT_BASE +
		  ring_पूर्णांकerrupt_index(ring) / 32 * 4;
	पूर्णांक bit = ring_पूर्णांकerrupt_index(ring) & 31;
	पूर्णांक mask = 1 << bit;
	u32 old, new;

	अगर (ring->irq > 0) अणु
		u32 step, shअगरt, ivr, misc;
		व्योम __iomem *ivr_base;
		पूर्णांक index;

		अगर (ring->is_tx)
			index = ring->hop;
		अन्यथा
			index = ring->hop + ring->nhi->hop_count;

		/*
		 * Ask the hardware to clear पूर्णांकerrupt status bits स्वतःmatically
		 * since we alपढ़ोy know which पूर्णांकerrupt was triggered.
		 */
		misc = ioपढ़ो32(ring->nhi->iobase + REG_DMA_MISC);
		अगर (!(misc & REG_DMA_MISC_INT_AUTO_CLEAR)) अणु
			misc |= REG_DMA_MISC_INT_AUTO_CLEAR;
			ioग_लिखो32(misc, ring->nhi->iobase + REG_DMA_MISC);
		पूर्ण

		ivr_base = ring->nhi->iobase + REG_INT_VEC_ALLOC_BASE;
		step = index / REG_INT_VEC_ALLOC_REGS * REG_INT_VEC_ALLOC_BITS;
		shअगरt = index % REG_INT_VEC_ALLOC_REGS * REG_INT_VEC_ALLOC_BITS;
		ivr = ioपढ़ो32(ivr_base + step);
		ivr &= ~(REG_INT_VEC_ALLOC_MASK << shअगरt);
		अगर (active)
			ivr |= ring->vector << shअगरt;
		ioग_लिखो32(ivr, ivr_base + step);
	पूर्ण

	old = ioपढ़ो32(ring->nhi->iobase + reg);
	अगर (active)
		new = old | mask;
	अन्यथा
		new = old & ~mask;

	dev_dbg(&ring->nhi->pdev->dev,
		"%s interrupt at register %#x bit %d (%#x -> %#x)\n",
		active ? "enabling" : "disabling", reg, bit, old, new);

	अगर (new == old)
		dev_WARN(&ring->nhi->pdev->dev,
					 "interrupt for %s %d is already %s\n",
					 RING_TYPE(ring), ring->hop,
					 active ? "enabled" : "disabled");
	ioग_लिखो32(new, ring->nhi->iobase + reg);
पूर्ण

/*
 * nhi_disable_पूर्णांकerrupts() - disable पूर्णांकerrupts क्रम all rings
 *
 * Use only during init and shutकरोwn.
 */
अटल व्योम nhi_disable_पूर्णांकerrupts(काष्ठा tb_nhi *nhi)
अणु
	पूर्णांक i = 0;
	/* disable पूर्णांकerrupts */
	क्रम (i = 0; i < RING_INTERRUPT_REG_COUNT(nhi); i++)
		ioग_लिखो32(0, nhi->iobase + REG_RING_INTERRUPT_BASE + 4 * i);

	/* clear पूर्णांकerrupt status bits */
	क्रम (i = 0; i < RING_NOTIFY_REG_COUNT(nhi); i++)
		ioपढ़ो32(nhi->iobase + REG_RING_NOTIFY_BASE + 4 * i);
पूर्ण

/* ring helper methods */

अटल व्योम __iomem *ring_desc_base(काष्ठा tb_ring *ring)
अणु
	व्योम __iomem *io = ring->nhi->iobase;
	io += ring->is_tx ? REG_TX_RING_BASE : REG_RX_RING_BASE;
	io += ring->hop * 16;
	वापस io;
पूर्ण

अटल व्योम __iomem *ring_options_base(काष्ठा tb_ring *ring)
अणु
	व्योम __iomem *io = ring->nhi->iobase;
	io += ring->is_tx ? REG_TX_OPTIONS_BASE : REG_RX_OPTIONS_BASE;
	io += ring->hop * 32;
	वापस io;
पूर्ण

अटल व्योम ring_ioग_लिखो_cons(काष्ठा tb_ring *ring, u16 cons)
अणु
	/*
	 * The other 16-bits in the रेजिस्टर is पढ़ो-only and ग_लिखोs to it
	 * are ignored by the hardware so we can save one ioपढ़ो32() by
	 * filling the पढ़ो-only bits with zeroes.
	 */
	ioग_लिखो32(cons, ring_desc_base(ring) + 8);
पूर्ण

अटल व्योम ring_ioग_लिखो_prod(काष्ठा tb_ring *ring, u16 prod)
अणु
	/* See ring_ioग_लिखो_cons() above क्रम explanation */
	ioग_लिखो32(prod << 16, ring_desc_base(ring) + 8);
पूर्ण

अटल व्योम ring_ioग_लिखो32desc(काष्ठा tb_ring *ring, u32 value, u32 offset)
अणु
	ioग_लिखो32(value, ring_desc_base(ring) + offset);
पूर्ण

अटल व्योम ring_ioग_लिखो64desc(काष्ठा tb_ring *ring, u64 value, u32 offset)
अणु
	ioग_लिखो32(value, ring_desc_base(ring) + offset);
	ioग_लिखो32(value >> 32, ring_desc_base(ring) + offset + 4);
पूर्ण

अटल व्योम ring_ioग_लिखो32options(काष्ठा tb_ring *ring, u32 value, u32 offset)
अणु
	ioग_लिखो32(value, ring_options_base(ring) + offset);
पूर्ण

अटल bool ring_full(काष्ठा tb_ring *ring)
अणु
	वापस ((ring->head + 1) % ring->size) == ring->tail;
पूर्ण

अटल bool ring_empty(काष्ठा tb_ring *ring)
अणु
	वापस ring->head == ring->tail;
पूर्ण

/*
 * ring_ग_लिखो_descriptors() - post frames from ring->queue to the controller
 *
 * ring->lock is held.
 */
अटल व्योम ring_ग_लिखो_descriptors(काष्ठा tb_ring *ring)
अणु
	काष्ठा ring_frame *frame, *n;
	काष्ठा ring_desc *descriptor;
	list_क्रम_each_entry_safe(frame, n, &ring->queue, list) अणु
		अगर (ring_full(ring))
			अवरोध;
		list_move_tail(&frame->list, &ring->in_flight);
		descriptor = &ring->descriptors[ring->head];
		descriptor->phys = frame->buffer_phy;
		descriptor->समय = 0;
		descriptor->flags = RING_DESC_POSTED | RING_DESC_INTERRUPT;
		अगर (ring->is_tx) अणु
			descriptor->length = frame->size;
			descriptor->eof = frame->eof;
			descriptor->sof = frame->sof;
		पूर्ण
		ring->head = (ring->head + 1) % ring->size;
		अगर (ring->is_tx)
			ring_ioग_लिखो_prod(ring, ring->head);
		अन्यथा
			ring_ioग_लिखो_cons(ring, ring->head);
	पूर्ण
पूर्ण

/*
 * ring_work() - progress completed frames
 *
 * If the ring is shutting करोwn then all frames are marked as canceled and
 * their callbacks are invoked.
 *
 * Otherwise we collect all completed frame from the ring buffer, ग_लिखो new
 * frame to the ring buffer and invoke the callbacks क्रम the completed frames.
 */
अटल व्योम ring_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tb_ring *ring = container_of(work, typeof(*ring), work);
	काष्ठा ring_frame *frame;
	bool canceled = false;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(करोne);

	spin_lock_irqsave(&ring->lock, flags);

	अगर (!ring->running) अणु
		/*  Move all frames to करोne and mark them as canceled. */
		list_splice_tail_init(&ring->in_flight, &करोne);
		list_splice_tail_init(&ring->queue, &करोne);
		canceled = true;
		जाओ invoke_callback;
	पूर्ण

	जबतक (!ring_empty(ring)) अणु
		अगर (!(ring->descriptors[ring->tail].flags
				& RING_DESC_COMPLETED))
			अवरोध;
		frame = list_first_entry(&ring->in_flight, typeof(*frame),
					 list);
		list_move_tail(&frame->list, &करोne);
		अगर (!ring->is_tx) अणु
			frame->size = ring->descriptors[ring->tail].length;
			frame->eof = ring->descriptors[ring->tail].eof;
			frame->sof = ring->descriptors[ring->tail].sof;
			frame->flags = ring->descriptors[ring->tail].flags;
		पूर्ण
		ring->tail = (ring->tail + 1) % ring->size;
	पूर्ण
	ring_ग_लिखो_descriptors(ring);

invoke_callback:
	/* allow callbacks to schedule new work */
	spin_unlock_irqrestore(&ring->lock, flags);
	जबतक (!list_empty(&करोne)) अणु
		frame = list_first_entry(&करोne, typeof(*frame), list);
		/*
		 * The callback may reenqueue or delete frame.
		 * Do not hold on to it.
		 */
		list_del_init(&frame->list);
		अगर (frame->callback)
			frame->callback(ring, frame, canceled);
	पूर्ण
पूर्ण

पूर्णांक __tb_ring_enqueue(काष्ठा tb_ring *ring, काष्ठा ring_frame *frame)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&ring->lock, flags);
	अगर (ring->running) अणु
		list_add_tail(&frame->list, &ring->queue);
		ring_ग_लिखो_descriptors(ring);
	पूर्ण अन्यथा अणु
		ret = -ESHUTDOWN;
	पूर्ण
	spin_unlock_irqrestore(&ring->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__tb_ring_enqueue);

/**
 * tb_ring_poll() - Poll one completed frame from the ring
 * @ring: Ring to poll
 *
 * This function can be called when @start_poll callback of the @ring
 * has been called. It will पढ़ो one completed frame from the ring and
 * वापस it to the caller. Returns %शून्य अगर there is no more completed
 * frames.
 */
काष्ठा ring_frame *tb_ring_poll(काष्ठा tb_ring *ring)
अणु
	काष्ठा ring_frame *frame = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ring->lock, flags);
	अगर (!ring->running)
		जाओ unlock;
	अगर (ring_empty(ring))
		जाओ unlock;

	अगर (ring->descriptors[ring->tail].flags & RING_DESC_COMPLETED) अणु
		frame = list_first_entry(&ring->in_flight, typeof(*frame),
					 list);
		list_del_init(&frame->list);

		अगर (!ring->is_tx) अणु
			frame->size = ring->descriptors[ring->tail].length;
			frame->eof = ring->descriptors[ring->tail].eof;
			frame->sof = ring->descriptors[ring->tail].sof;
			frame->flags = ring->descriptors[ring->tail].flags;
		पूर्ण

		ring->tail = (ring->tail + 1) % ring->size;
	पूर्ण

unlock:
	spin_unlock_irqrestore(&ring->lock, flags);
	वापस frame;
पूर्ण
EXPORT_SYMBOL_GPL(tb_ring_poll);

अटल व्योम __ring_पूर्णांकerrupt_mask(काष्ठा tb_ring *ring, bool mask)
अणु
	पूर्णांक idx = ring_पूर्णांकerrupt_index(ring);
	पूर्णांक reg = REG_RING_INTERRUPT_BASE + idx / 32 * 4;
	पूर्णांक bit = idx % 32;
	u32 val;

	val = ioपढ़ो32(ring->nhi->iobase + reg);
	अगर (mask)
		val &= ~BIT(bit);
	अन्यथा
		val |= BIT(bit);
	ioग_लिखो32(val, ring->nhi->iobase + reg);
पूर्ण

/* Both @nhi->lock and @ring->lock should be held */
अटल व्योम __ring_पूर्णांकerrupt(काष्ठा tb_ring *ring)
अणु
	अगर (!ring->running)
		वापस;

	अगर (ring->start_poll) अणु
		__ring_पूर्णांकerrupt_mask(ring, true);
		ring->start_poll(ring->poll_data);
	पूर्ण अन्यथा अणु
		schedule_work(&ring->work);
	पूर्ण
पूर्ण

/**
 * tb_ring_poll_complete() - Re-start पूर्णांकerrupt क्रम the ring
 * @ring: Ring to re-start the पूर्णांकerrupt
 *
 * This will re-start (unmask) the ring पूर्णांकerrupt once the user is करोne
 * with polling.
 */
व्योम tb_ring_poll_complete(काष्ठा tb_ring *ring)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ring->nhi->lock, flags);
	spin_lock(&ring->lock);
	अगर (ring->start_poll)
		__ring_पूर्णांकerrupt_mask(ring, false);
	spin_unlock(&ring->lock);
	spin_unlock_irqrestore(&ring->nhi->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(tb_ring_poll_complete);

अटल irqवापस_t ring_msix(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tb_ring *ring = data;

	spin_lock(&ring->nhi->lock);
	spin_lock(&ring->lock);
	__ring_पूर्णांकerrupt(ring);
	spin_unlock(&ring->lock);
	spin_unlock(&ring->nhi->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ring_request_msix(काष्ठा tb_ring *ring, bool no_suspend)
अणु
	काष्ठा tb_nhi *nhi = ring->nhi;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक ret;

	अगर (!nhi->pdev->msix_enabled)
		वापस 0;

	ret = ida_simple_get(&nhi->msix_ida, 0, MSIX_MAX_VECS, GFP_KERNEL);
	अगर (ret < 0)
		वापस ret;

	ring->vector = ret;

	ret = pci_irq_vector(ring->nhi->pdev, ring->vector);
	अगर (ret < 0)
		जाओ err_ida_हटाओ;

	ring->irq = ret;

	irqflags = no_suspend ? IRQF_NO_SUSPEND : 0;
	ret = request_irq(ring->irq, ring_msix, irqflags, "thunderbolt", ring);
	अगर (ret)
		जाओ err_ida_हटाओ;

	वापस 0;

err_ida_हटाओ:
	ida_simple_हटाओ(&nhi->msix_ida, ring->vector);

	वापस ret;
पूर्ण

अटल व्योम ring_release_msix(काष्ठा tb_ring *ring)
अणु
	अगर (ring->irq <= 0)
		वापस;

	मुक्त_irq(ring->irq, ring);
	ida_simple_हटाओ(&ring->nhi->msix_ida, ring->vector);
	ring->vector = 0;
	ring->irq = 0;
पूर्ण

अटल पूर्णांक nhi_alloc_hop(काष्ठा tb_nhi *nhi, काष्ठा tb_ring *ring)
अणु
	पूर्णांक ret = 0;

	spin_lock_irq(&nhi->lock);

	अगर (ring->hop < 0) अणु
		अचिन्हित पूर्णांक i;

		/*
		 * Automatically allocate HopID from the non-reserved
		 * range 1 .. hop_count - 1.
		 */
		क्रम (i = RING_FIRST_USABLE_HOPID; i < nhi->hop_count; i++) अणु
			अगर (ring->is_tx) अणु
				अगर (!nhi->tx_rings[i]) अणु
					ring->hop = i;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (!nhi->rx_rings[i]) अणु
					ring->hop = i;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ring->hop < 0 || ring->hop >= nhi->hop_count) अणु
		dev_warn(&nhi->pdev->dev, "invalid hop: %d\n", ring->hop);
		ret = -EINVAL;
		जाओ err_unlock;
	पूर्ण
	अगर (ring->is_tx && nhi->tx_rings[ring->hop]) अणु
		dev_warn(&nhi->pdev->dev, "TX hop %d already allocated\n",
			 ring->hop);
		ret = -EBUSY;
		जाओ err_unlock;
	पूर्ण अन्यथा अगर (!ring->is_tx && nhi->rx_rings[ring->hop]) अणु
		dev_warn(&nhi->pdev->dev, "RX hop %d already allocated\n",
			 ring->hop);
		ret = -EBUSY;
		जाओ err_unlock;
	पूर्ण

	अगर (ring->is_tx)
		nhi->tx_rings[ring->hop] = ring;
	अन्यथा
		nhi->rx_rings[ring->hop] = ring;

err_unlock:
	spin_unlock_irq(&nhi->lock);

	वापस ret;
पूर्ण

अटल काष्ठा tb_ring *tb_ring_alloc(काष्ठा tb_nhi *nhi, u32 hop, पूर्णांक size,
				     bool transmit, अचिन्हित पूर्णांक flags,
				     पूर्णांक e2e_tx_hop, u16 sof_mask, u16 eof_mask,
				     व्योम (*start_poll)(व्योम *),
				     व्योम *poll_data)
अणु
	काष्ठा tb_ring *ring = शून्य;

	dev_dbg(&nhi->pdev->dev, "allocating %s ring %d of size %d\n",
		transmit ? "TX" : "RX", hop, size);

	ring = kzalloc(माप(*ring), GFP_KERNEL);
	अगर (!ring)
		वापस शून्य;

	spin_lock_init(&ring->lock);
	INIT_LIST_HEAD(&ring->queue);
	INIT_LIST_HEAD(&ring->in_flight);
	INIT_WORK(&ring->work, ring_work);

	ring->nhi = nhi;
	ring->hop = hop;
	ring->is_tx = transmit;
	ring->size = size;
	ring->flags = flags;
	ring->e2e_tx_hop = e2e_tx_hop;
	ring->sof_mask = sof_mask;
	ring->eof_mask = eof_mask;
	ring->head = 0;
	ring->tail = 0;
	ring->running = false;
	ring->start_poll = start_poll;
	ring->poll_data = poll_data;

	ring->descriptors = dma_alloc_coherent(&ring->nhi->pdev->dev,
			size * माप(*ring->descriptors),
			&ring->descriptors_dma, GFP_KERNEL | __GFP_ZERO);
	अगर (!ring->descriptors)
		जाओ err_मुक्त_ring;

	अगर (ring_request_msix(ring, flags & RING_FLAG_NO_SUSPEND))
		जाओ err_मुक्त_descs;

	अगर (nhi_alloc_hop(nhi, ring))
		जाओ err_release_msix;

	वापस ring;

err_release_msix:
	ring_release_msix(ring);
err_मुक्त_descs:
	dma_मुक्त_coherent(&ring->nhi->pdev->dev,
			  ring->size * माप(*ring->descriptors),
			  ring->descriptors, ring->descriptors_dma);
err_मुक्त_ring:
	kमुक्त(ring);

	वापस शून्य;
पूर्ण

/**
 * tb_ring_alloc_tx() - Allocate DMA ring क्रम transmit
 * @nhi: Poपूर्णांकer to the NHI the ring is to be allocated
 * @hop: HopID (ring) to allocate
 * @size: Number of entries in the ring
 * @flags: Flags क्रम the ring
 */
काष्ठा tb_ring *tb_ring_alloc_tx(काष्ठा tb_nhi *nhi, पूर्णांक hop, पूर्णांक size,
				 अचिन्हित पूर्णांक flags)
अणु
	वापस tb_ring_alloc(nhi, hop, size, true, flags, 0, 0, 0, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(tb_ring_alloc_tx);

/**
 * tb_ring_alloc_rx() - Allocate DMA ring क्रम receive
 * @nhi: Poपूर्णांकer to the NHI the ring is to be allocated
 * @hop: HopID (ring) to allocate. Pass %-1 क्रम स्वतःmatic allocation.
 * @size: Number of entries in the ring
 * @flags: Flags क्रम the ring
 * @e2e_tx_hop: Transmit HopID when E2E is enabled in @flags
 * @sof_mask: Mask of PDF values that start a frame
 * @eof_mask: Mask of PDF values that end a frame
 * @start_poll: If not %शून्य the ring will call this function when an
 *		पूर्णांकerrupt is triggered and masked, instead of callback
 *		in each Rx frame.
 * @poll_data: Optional data passed to @start_poll
 */
काष्ठा tb_ring *tb_ring_alloc_rx(काष्ठा tb_nhi *nhi, पूर्णांक hop, पूर्णांक size,
				 अचिन्हित पूर्णांक flags, पूर्णांक e2e_tx_hop,
				 u16 sof_mask, u16 eof_mask,
				 व्योम (*start_poll)(व्योम *), व्योम *poll_data)
अणु
	वापस tb_ring_alloc(nhi, hop, size, false, flags, e2e_tx_hop, sof_mask, eof_mask,
			     start_poll, poll_data);
पूर्ण
EXPORT_SYMBOL_GPL(tb_ring_alloc_rx);

/**
 * tb_ring_start() - enable a ring
 * @ring: Ring to start
 *
 * Must not be invoked in parallel with tb_ring_stop().
 */
व्योम tb_ring_start(काष्ठा tb_ring *ring)
अणु
	u16 frame_size;
	u32 flags;

	spin_lock_irq(&ring->nhi->lock);
	spin_lock(&ring->lock);
	अगर (ring->nhi->going_away)
		जाओ err;
	अगर (ring->running) अणु
		dev_WARN(&ring->nhi->pdev->dev, "ring already started\n");
		जाओ err;
	पूर्ण
	dev_dbg(&ring->nhi->pdev->dev, "starting %s %d\n",
		RING_TYPE(ring), ring->hop);

	अगर (ring->flags & RING_FLAG_FRAME) अणु
		/* Means 4096 */
		frame_size = 0;
		flags = RING_FLAG_ENABLE;
	पूर्ण अन्यथा अणु
		frame_size = TB_FRAME_SIZE;
		flags = RING_FLAG_ENABLE | RING_FLAG_RAW;
	पूर्ण

	ring_ioग_लिखो64desc(ring, ring->descriptors_dma, 0);
	अगर (ring->is_tx) अणु
		ring_ioग_लिखो32desc(ring, ring->size, 12);
		ring_ioग_लिखो32options(ring, 0, 4); /* समय releated ? */
		ring_ioग_लिखो32options(ring, flags, 0);
	पूर्ण अन्यथा अणु
		u32 sof_eof_mask = ring->sof_mask << 16 | ring->eof_mask;

		ring_ioग_लिखो32desc(ring, (frame_size << 16) | ring->size, 12);
		ring_ioग_लिखो32options(ring, sof_eof_mask, 4);
		ring_ioग_लिखो32options(ring, flags, 0);
	पूर्ण

	/*
	 * Now that the ring valid bit is set we can configure E2E अगर
	 * enabled क्रम the ring.
	 */
	अगर (ring->flags & RING_FLAG_E2E) अणु
		अगर (!ring->is_tx) अणु
			u32 hop;

			hop = ring->e2e_tx_hop << REG_RX_OPTIONS_E2E_HOP_SHIFT;
			hop &= REG_RX_OPTIONS_E2E_HOP_MASK;
			flags |= hop;

			dev_dbg(&ring->nhi->pdev->dev,
				"enabling E2E for %s %d with TX HopID %d\n",
				RING_TYPE(ring), ring->hop, ring->e2e_tx_hop);
		पूर्ण अन्यथा अणु
			dev_dbg(&ring->nhi->pdev->dev, "enabling E2E for %s %d\n",
				RING_TYPE(ring), ring->hop);
		पूर्ण

		flags |= RING_FLAG_E2E_FLOW_CONTROL;
		ring_ioग_लिखो32options(ring, flags, 0);
	पूर्ण

	ring_पूर्णांकerrupt_active(ring, true);
	ring->running = true;
err:
	spin_unlock(&ring->lock);
	spin_unlock_irq(&ring->nhi->lock);
पूर्ण
EXPORT_SYMBOL_GPL(tb_ring_start);

/**
 * tb_ring_stop() - shutकरोwn a ring
 * @ring: Ring to stop
 *
 * Must not be invoked from a callback.
 *
 * This method will disable the ring. Further calls to
 * tb_ring_tx/tb_ring_rx will वापस -ESHUTDOWN until ring_stop has been
 * called.
 *
 * All enqueued frames will be canceled and their callbacks will be executed
 * with frame->canceled set to true (on the callback thपढ़ो). This method
 * वापसs only after all callback invocations have finished.
 */
व्योम tb_ring_stop(काष्ठा tb_ring *ring)
अणु
	spin_lock_irq(&ring->nhi->lock);
	spin_lock(&ring->lock);
	dev_dbg(&ring->nhi->pdev->dev, "stopping %s %d\n",
		RING_TYPE(ring), ring->hop);
	अगर (ring->nhi->going_away)
		जाओ err;
	अगर (!ring->running) अणु
		dev_WARN(&ring->nhi->pdev->dev, "%s %d already stopped\n",
			 RING_TYPE(ring), ring->hop);
		जाओ err;
	पूर्ण
	ring_पूर्णांकerrupt_active(ring, false);

	ring_ioग_लिखो32options(ring, 0, 0);
	ring_ioग_लिखो64desc(ring, 0, 0);
	ring_ioग_लिखो32desc(ring, 0, 8);
	ring_ioग_लिखो32desc(ring, 0, 12);
	ring->head = 0;
	ring->tail = 0;
	ring->running = false;

err:
	spin_unlock(&ring->lock);
	spin_unlock_irq(&ring->nhi->lock);

	/*
	 * schedule ring->work to invoke callbacks on all reमुख्यing frames.
	 */
	schedule_work(&ring->work);
	flush_work(&ring->work);
पूर्ण
EXPORT_SYMBOL_GPL(tb_ring_stop);

/*
 * tb_ring_मुक्त() - मुक्त ring
 *
 * When this method वापसs all invocations of ring->callback will have
 * finished.
 *
 * Ring must be stopped.
 *
 * Must NOT be called from ring_frame->callback!
 */
व्योम tb_ring_मुक्त(काष्ठा tb_ring *ring)
अणु
	spin_lock_irq(&ring->nhi->lock);
	/*
	 * Dissociate the ring from the NHI. This also ensures that
	 * nhi_पूर्णांकerrupt_work cannot reschedule ring->work.
	 */
	अगर (ring->is_tx)
		ring->nhi->tx_rings[ring->hop] = शून्य;
	अन्यथा
		ring->nhi->rx_rings[ring->hop] = शून्य;

	अगर (ring->running) अणु
		dev_WARN(&ring->nhi->pdev->dev, "%s %d still running\n",
			 RING_TYPE(ring), ring->hop);
	पूर्ण
	spin_unlock_irq(&ring->nhi->lock);

	ring_release_msix(ring);

	dma_मुक्त_coherent(&ring->nhi->pdev->dev,
			  ring->size * माप(*ring->descriptors),
			  ring->descriptors, ring->descriptors_dma);

	ring->descriptors = शून्य;
	ring->descriptors_dma = 0;


	dev_dbg(&ring->nhi->pdev->dev, "freeing %s %d\n", RING_TYPE(ring),
		ring->hop);

	/*
	 * ring->work can no दीर्घer be scheduled (it is scheduled only
	 * by nhi_पूर्णांकerrupt_work, ring_stop and ring_msix). Wait क्रम it
	 * to finish beक्रमe मुक्तing the ring.
	 */
	flush_work(&ring->work);
	kमुक्त(ring);
पूर्ण
EXPORT_SYMBOL_GPL(tb_ring_मुक्त);

/**
 * nhi_mailbox_cmd() - Send a command through NHI mailbox
 * @nhi: Poपूर्णांकer to the NHI काष्ठाure
 * @cmd: Command to send
 * @data: Data to be send with the command
 *
 * Sends mailbox command to the firmware running on NHI. Returns %0 in
 * हाल of success and negative त्रुटि_सं in हाल of failure.
 */
पूर्णांक nhi_mailbox_cmd(काष्ठा tb_nhi *nhi, क्रमागत nhi_mailbox_cmd cmd, u32 data)
अणु
	kसमय_प्रकार समयout;
	u32 val;

	ioग_लिखो32(data, nhi->iobase + REG_INMAIL_DATA);

	val = ioपढ़ो32(nhi->iobase + REG_INMAIL_CMD);
	val &= ~(REG_INMAIL_CMD_MASK | REG_INMAIL_ERROR);
	val |= REG_INMAIL_OP_REQUEST | cmd;
	ioग_लिखो32(val, nhi->iobase + REG_INMAIL_CMD);

	समयout = kसमय_add_ms(kसमय_get(), NHI_MAILBOX_TIMEOUT);
	करो अणु
		val = ioपढ़ो32(nhi->iobase + REG_INMAIL_CMD);
		अगर (!(val & REG_INMAIL_OP_REQUEST))
			अवरोध;
		usleep_range(10, 20);
	पूर्ण जबतक (kसमय_beक्रमe(kसमय_get(), समयout));

	अगर (val & REG_INMAIL_OP_REQUEST)
		वापस -ETIMEDOUT;
	अगर (val & REG_INMAIL_ERROR)
		वापस -EIO;

	वापस 0;
पूर्ण

/**
 * nhi_mailbox_mode() - Return current firmware operation mode
 * @nhi: Poपूर्णांकer to the NHI काष्ठाure
 *
 * The function पढ़ोs current firmware operation mode using NHI mailbox
 * रेजिस्टरs and वापसs it to the caller.
 */
क्रमागत nhi_fw_mode nhi_mailbox_mode(काष्ठा tb_nhi *nhi)
अणु
	u32 val;

	val = ioपढ़ो32(nhi->iobase + REG_OUTMAIL_CMD);
	val &= REG_OUTMAIL_CMD_OPMODE_MASK;
	val >>= REG_OUTMAIL_CMD_OPMODE_SHIFT;

	वापस (क्रमागत nhi_fw_mode)val;
पूर्ण

अटल व्योम nhi_पूर्णांकerrupt_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tb_nhi *nhi = container_of(work, typeof(*nhi), पूर्णांकerrupt_work);
	पूर्णांक value = 0; /* Suppress uninitialized usage warning. */
	पूर्णांक bit;
	पूर्णांक hop = -1;
	पूर्णांक type = 0; /* current पूर्णांकerrupt type 0: TX, 1: RX, 2: RX overflow */
	काष्ठा tb_ring *ring;

	spin_lock_irq(&nhi->lock);

	/*
	 * Starting at REG_RING_NOTIFY_BASE there are three status bitfields
	 * (TX, RX, RX overflow). We iterate over the bits and पढ़ो a new
	 * dwords as required. The रेजिस्टरs are cleared on पढ़ो.
	 */
	क्रम (bit = 0; bit < 3 * nhi->hop_count; bit++) अणु
		अगर (bit % 32 == 0)
			value = ioपढ़ो32(nhi->iobase
					 + REG_RING_NOTIFY_BASE
					 + 4 * (bit / 32));
		अगर (++hop == nhi->hop_count) अणु
			hop = 0;
			type++;
		पूर्ण
		अगर ((value & (1 << (bit % 32))) == 0)
			जारी;
		अगर (type == 2) अणु
			dev_warn(&nhi->pdev->dev,
				 "RX overflow for ring %d\n",
				 hop);
			जारी;
		पूर्ण
		अगर (type == 0)
			ring = nhi->tx_rings[hop];
		अन्यथा
			ring = nhi->rx_rings[hop];
		अगर (ring == शून्य) अणु
			dev_warn(&nhi->pdev->dev,
				 "got interrupt for inactive %s ring %d\n",
				 type ? "RX" : "TX",
				 hop);
			जारी;
		पूर्ण

		spin_lock(&ring->lock);
		__ring_पूर्णांकerrupt(ring);
		spin_unlock(&ring->lock);
	पूर्ण
	spin_unlock_irq(&nhi->lock);
पूर्ण

अटल irqवापस_t nhi_msi(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा tb_nhi *nhi = data;
	schedule_work(&nhi->पूर्णांकerrupt_work);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __nhi_suspend_noirq(काष्ठा device *dev, bool wakeup)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा tb *tb = pci_get_drvdata(pdev);
	काष्ठा tb_nhi *nhi = tb->nhi;
	पूर्णांक ret;

	ret = tb_करोमुख्य_suspend_noirq(tb);
	अगर (ret)
		वापस ret;

	अगर (nhi->ops && nhi->ops->suspend_noirq) अणु
		ret = nhi->ops->suspend_noirq(tb->nhi, wakeup);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nhi_suspend_noirq(काष्ठा device *dev)
अणु
	वापस __nhi_suspend_noirq(dev, device_may_wakeup(dev));
पूर्ण

अटल पूर्णांक nhi_मुक्तze_noirq(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा tb *tb = pci_get_drvdata(pdev);

	वापस tb_करोमुख्य_मुक्तze_noirq(tb);
पूर्ण

अटल पूर्णांक nhi_thaw_noirq(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा tb *tb = pci_get_drvdata(pdev);

	वापस tb_करोमुख्य_thaw_noirq(tb);
पूर्ण

अटल bool nhi_wake_supported(काष्ठा pci_dev *pdev)
अणु
	u8 val;

	/*
	 * If घातer rails are sustainable क्रम wakeup from S4 this
	 * property is set by the BIOS.
	 */
	अगर (device_property_पढ़ो_u8(&pdev->dev, "WAKE_SUPPORTED", &val))
		वापस !!val;

	वापस true;
पूर्ण

अटल पूर्णांक nhi_घातeroff_noirq(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	bool wakeup;

	wakeup = device_may_wakeup(dev) && nhi_wake_supported(pdev);
	वापस __nhi_suspend_noirq(dev, wakeup);
पूर्ण

अटल व्योम nhi_enable_पूर्णांक_throttling(काष्ठा tb_nhi *nhi)
अणु
	/* Throttling is specअगरied in 256ns increments */
	u32 throttle = DIV_ROUND_UP(128 * NSEC_PER_USEC, 256);
	अचिन्हित पूर्णांक i;

	/*
	 * Configure पूर्णांकerrupt throttling क्रम all vectors even अगर we
	 * only use few.
	 */
	क्रम (i = 0; i < MSIX_MAX_VECS; i++) अणु
		u32 reg = REG_INT_THROTTLING_RATE + i * 4;
		ioग_लिखो32(throttle, nhi->iobase + reg);
	पूर्ण
पूर्ण

अटल पूर्णांक nhi_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा tb *tb = pci_get_drvdata(pdev);
	काष्ठा tb_nhi *nhi = tb->nhi;
	पूर्णांक ret;

	/*
	 * Check that the device is still there. It may be that the user
	 * unplugged last device which causes the host controller to go
	 * away on PCs.
	 */
	अगर (!pci_device_is_present(pdev)) अणु
		nhi->going_away = true;
	पूर्ण अन्यथा अणु
		अगर (nhi->ops && nhi->ops->resume_noirq) अणु
			ret = nhi->ops->resume_noirq(nhi);
			अगर (ret)
				वापस ret;
		पूर्ण
		nhi_enable_पूर्णांक_throttling(tb->nhi);
	पूर्ण

	वापस tb_करोमुख्य_resume_noirq(tb);
पूर्ण

अटल पूर्णांक nhi_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा tb *tb = pci_get_drvdata(pdev);

	वापस tb_करोमुख्य_suspend(tb);
पूर्ण

अटल व्योम nhi_complete(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा tb *tb = pci_get_drvdata(pdev);

	/*
	 * If we were runसमय suspended when प्रणाली suspend started,
	 * schedule runसमय resume now. It should bring the करोमुख्य back
	 * to functional state.
	 */
	अगर (pm_runसमय_suspended(&pdev->dev))
		pm_runसमय_resume(&pdev->dev);
	अन्यथा
		tb_करोमुख्य_complete(tb);
पूर्ण

अटल पूर्णांक nhi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा tb *tb = pci_get_drvdata(pdev);
	काष्ठा tb_nhi *nhi = tb->nhi;
	पूर्णांक ret;

	ret = tb_करोमुख्य_runसमय_suspend(tb);
	अगर (ret)
		वापस ret;

	अगर (nhi->ops && nhi->ops->runसमय_suspend) अणु
		ret = nhi->ops->runसमय_suspend(tb->nhi);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nhi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा tb *tb = pci_get_drvdata(pdev);
	काष्ठा tb_nhi *nhi = tb->nhi;
	पूर्णांक ret;

	अगर (nhi->ops && nhi->ops->runसमय_resume) अणु
		ret = nhi->ops->runसमय_resume(nhi);
		अगर (ret)
			वापस ret;
	पूर्ण

	nhi_enable_पूर्णांक_throttling(nhi);
	वापस tb_करोमुख्य_runसमय_resume(tb);
पूर्ण

अटल व्योम nhi_shutकरोwn(काष्ठा tb_nhi *nhi)
अणु
	पूर्णांक i;

	dev_dbg(&nhi->pdev->dev, "shutdown\n");

	क्रम (i = 0; i < nhi->hop_count; i++) अणु
		अगर (nhi->tx_rings[i])
			dev_WARN(&nhi->pdev->dev,
				 "TX ring %d is still active\n", i);
		अगर (nhi->rx_rings[i])
			dev_WARN(&nhi->pdev->dev,
				 "RX ring %d is still active\n", i);
	पूर्ण
	nhi_disable_पूर्णांकerrupts(nhi);
	/*
	 * We have to release the irq beक्रमe calling flush_work. Otherwise an
	 * alपढ़ोy executing IRQ handler could call schedule_work again.
	 */
	अगर (!nhi->pdev->msix_enabled) अणु
		devm_मुक्त_irq(&nhi->pdev->dev, nhi->pdev->irq, nhi);
		flush_work(&nhi->पूर्णांकerrupt_work);
	पूर्ण
	ida_destroy(&nhi->msix_ida);

	अगर (nhi->ops && nhi->ops->shutकरोwn)
		nhi->ops->shutकरोwn(nhi);
पूर्ण

अटल पूर्णांक nhi_init_msi(काष्ठा tb_nhi *nhi)
अणु
	काष्ठा pci_dev *pdev = nhi->pdev;
	पूर्णांक res, irq, nvec;

	/* In हाल someone left them on. */
	nhi_disable_पूर्णांकerrupts(nhi);

	nhi_enable_पूर्णांक_throttling(nhi);

	ida_init(&nhi->msix_ida);

	/*
	 * The NHI has 16 MSI-X vectors or a single MSI. We first try to
	 * get all MSI-X vectors and अगर we succeed, each ring will have
	 * one MSI-X. If क्रम some reason that करोes not work out, we
	 * fallback to a single MSI.
	 */
	nvec = pci_alloc_irq_vectors(pdev, MSIX_MIN_VECS, MSIX_MAX_VECS,
				     PCI_IRQ_MSIX);
	अगर (nvec < 0) अणु
		nvec = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSI);
		अगर (nvec < 0)
			वापस nvec;

		INIT_WORK(&nhi->पूर्णांकerrupt_work, nhi_पूर्णांकerrupt_work);

		irq = pci_irq_vector(nhi->pdev, 0);
		अगर (irq < 0)
			वापस irq;

		res = devm_request_irq(&pdev->dev, irq, nhi_msi,
				       IRQF_NO_SUSPEND, "thunderbolt", nhi);
		अगर (res) अणु
			dev_err(&pdev->dev, "request_irq failed, aborting\n");
			वापस res;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool nhi_imr_valid(काष्ठा pci_dev *pdev)
अणु
	u8 val;

	अगर (!device_property_पढ़ो_u8(&pdev->dev, "IMR_VALID", &val))
		वापस !!val;

	वापस true;
पूर्ण

/*
 * During suspend the Thunderbolt controller is reset and all PCIe
 * tunnels are lost. The NHI driver will try to reestablish all tunnels
 * during resume. This adds device links between the tunneled PCIe
 * करोwnstream ports and the NHI so that the device core will make sure
 * NHI is resumed first beक्रमe the rest.
 */
अटल व्योम tb_apple_add_links(काष्ठा tb_nhi *nhi)
अणु
	काष्ठा pci_dev *upstream, *pdev;

	अगर (!x86_apple_machine)
		वापस;

	चयन (nhi->pdev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_LIGHT_RIDGE:
	हाल PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_4C:
	हाल PCI_DEVICE_ID_INTEL_FALCON_RIDGE_2C_NHI:
	हाल PCI_DEVICE_ID_INTEL_FALCON_RIDGE_4C_NHI:
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	upstream = pci_upstream_bridge(nhi->pdev);
	जबतक (upstream) अणु
		अगर (!pci_is_pcie(upstream))
			वापस;
		अगर (pci_pcie_type(upstream) == PCI_EXP_TYPE_UPSTREAM)
			अवरोध;
		upstream = pci_upstream_bridge(upstream);
	पूर्ण

	अगर (!upstream)
		वापस;

	/*
	 * For each hotplug करोwnstream port, create add device link
	 * back to NHI so that PCIe tunnels can be re-established after
	 * sleep.
	 */
	क्रम_each_pci_bridge(pdev, upstream->subordinate) अणु
		स्थिर काष्ठा device_link *link;

		अगर (!pci_is_pcie(pdev))
			जारी;
		अगर (pci_pcie_type(pdev) != PCI_EXP_TYPE_DOWNSTREAM ||
		    !pdev->is_hotplug_bridge)
			जारी;

		link = device_link_add(&pdev->dev, &nhi->pdev->dev,
				       DL_FLAG_AUTOREMOVE_SUPPLIER |
				       DL_FLAG_PM_RUNTIME);
		अगर (link) अणु
			dev_dbg(&nhi->pdev->dev, "created link from %s\n",
				dev_name(&pdev->dev));
		पूर्ण अन्यथा अणु
			dev_warn(&nhi->pdev->dev, "device link creation from %s failed\n",
				 dev_name(&pdev->dev));
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा tb *nhi_select_cm(काष्ठा tb_nhi *nhi)
अणु
	काष्ठा tb *tb;

	/*
	 * USB4 हाल is simple. If we got control of any of the
	 * capabilities, we use software CM.
	 */
	अगर (tb_acpi_is_native())
		वापस tb_probe(nhi);

	/*
	 * Either firmware based CM is running (we did not get control
	 * from the firmware) or this is pre-USB4 PC so try first
	 * firmware CM and then fallback to software CM.
	 */
	tb = icm_probe(nhi);
	अगर (!tb)
		tb = tb_probe(nhi);

	वापस tb;
पूर्ण

अटल पूर्णांक nhi_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा tb_nhi *nhi;
	काष्ठा tb *tb;
	पूर्णांक res;

	अगर (!nhi_imr_valid(pdev)) अणु
		dev_warn(&pdev->dev, "firmware image not valid, aborting\n");
		वापस -ENODEV;
	पूर्ण

	res = pcim_enable_device(pdev);
	अगर (res) अणु
		dev_err(&pdev->dev, "cannot enable PCI device, aborting\n");
		वापस res;
	पूर्ण

	res = pcim_iomap_regions(pdev, 1 << 0, "thunderbolt");
	अगर (res) अणु
		dev_err(&pdev->dev, "cannot obtain PCI resources, aborting\n");
		वापस res;
	पूर्ण

	nhi = devm_kzalloc(&pdev->dev, माप(*nhi), GFP_KERNEL);
	अगर (!nhi)
		वापस -ENOMEM;

	nhi->pdev = pdev;
	nhi->ops = (स्थिर काष्ठा tb_nhi_ops *)id->driver_data;
	/* cannot fail - table is allocated bin pcim_iomap_regions */
	nhi->iobase = pcim_iomap_table(pdev)[0];
	nhi->hop_count = ioपढ़ो32(nhi->iobase + REG_HOP_COUNT) & 0x3ff;
	dev_dbg(&pdev->dev, "total paths: %d\n", nhi->hop_count);

	nhi->tx_rings = devm_kसुस्मृति(&pdev->dev, nhi->hop_count,
				     माप(*nhi->tx_rings), GFP_KERNEL);
	nhi->rx_rings = devm_kसुस्मृति(&pdev->dev, nhi->hop_count,
				     माप(*nhi->rx_rings), GFP_KERNEL);
	अगर (!nhi->tx_rings || !nhi->rx_rings)
		वापस -ENOMEM;

	res = nhi_init_msi(nhi);
	अगर (res) अणु
		dev_err(&pdev->dev, "cannot enable MSI, aborting\n");
		वापस res;
	पूर्ण

	spin_lock_init(&nhi->lock);

	res = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (res)
		res = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	अगर (res) अणु
		dev_err(&pdev->dev, "failed to set DMA mask\n");
		वापस res;
	पूर्ण

	pci_set_master(pdev);

	अगर (nhi->ops && nhi->ops->init) अणु
		res = nhi->ops->init(nhi);
		अगर (res)
			वापस res;
	पूर्ण

	tb_apple_add_links(nhi);
	tb_acpi_add_links(nhi);

	tb = nhi_select_cm(nhi);
	अगर (!tb) अणु
		dev_err(&nhi->pdev->dev,
			"failed to determine connection manager, aborting\n");
		वापस -ENODEV;
	पूर्ण

	dev_dbg(&nhi->pdev->dev, "NHI initialized, starting thunderbolt\n");

	res = tb_करोमुख्य_add(tb);
	अगर (res) अणु
		/*
		 * At this poपूर्णांक the RX/TX rings might alपढ़ोy have been
		 * activated. Do a proper shutकरोwn.
		 */
		tb_करोमुख्य_put(tb);
		nhi_shutकरोwn(nhi);
		वापस res;
	पूर्ण
	pci_set_drvdata(pdev, tb);

	device_wakeup_enable(&pdev->dev);

	pm_runसमय_allow(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, TB_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम nhi_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा tb *tb = pci_get_drvdata(pdev);
	काष्ठा tb_nhi *nhi = tb->nhi;

	pm_runसमय_get_sync(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_क्रमbid(&pdev->dev);

	tb_करोमुख्य_हटाओ(tb);
	nhi_shutकरोwn(nhi);
पूर्ण

/*
 * The tunneled pci bridges are siblings of us. Use resume_noirq to reenable
 * the tunnels asap. A corresponding pci quirk blocks the करोwnstream bridges
 * resume_noirq until we are करोne.
 */
अटल स्थिर काष्ठा dev_pm_ops nhi_pm_ops = अणु
	.suspend_noirq = nhi_suspend_noirq,
	.resume_noirq = nhi_resume_noirq,
	.मुक्तze_noirq = nhi_मुक्तze_noirq,  /*
					    * we just disable hotplug, the
					    * pci-tunnels stay alive.
					    */
	.thaw_noirq = nhi_thaw_noirq,
	.restore_noirq = nhi_resume_noirq,
	.suspend = nhi_suspend,
	.घातeroff_noirq = nhi_घातeroff_noirq,
	.घातeroff = nhi_suspend,
	.complete = nhi_complete,
	.runसमय_suspend = nhi_runसमय_suspend,
	.runसमय_resume = nhi_runसमय_resume,
पूर्ण;

अटल काष्ठा pci_device_id nhi_ids[] = अणु
	/*
	 * We have to specअगरy class, the TB bridges use the same device and
	 * venकरोr (sub)id on gen 1 and gen 2 controllers.
	 */
	अणु
		.class = PCI_CLASS_SYSTEM_OTHER << 8, .class_mask = ~0,
		.venकरोr = PCI_VENDOR_ID_INTEL,
		.device = PCI_DEVICE_ID_INTEL_LIGHT_RIDGE,
		.subvenकरोr = 0x2222, .subdevice = 0x1111,
	पूर्ण,
	अणु
		.class = PCI_CLASS_SYSTEM_OTHER << 8, .class_mask = ~0,
		.venकरोr = PCI_VENDOR_ID_INTEL,
		.device = PCI_DEVICE_ID_INTEL_CACTUS_RIDGE_4C,
		.subvenकरोr = 0x2222, .subdevice = 0x1111,
	पूर्ण,
	अणु
		.class = PCI_CLASS_SYSTEM_OTHER << 8, .class_mask = ~0,
		.venकरोr = PCI_VENDOR_ID_INTEL,
		.device = PCI_DEVICE_ID_INTEL_FALCON_RIDGE_2C_NHI,
		.subvenकरोr = PCI_ANY_ID, .subdevice = PCI_ANY_ID,
	पूर्ण,
	अणु
		.class = PCI_CLASS_SYSTEM_OTHER << 8, .class_mask = ~0,
		.venकरोr = PCI_VENDOR_ID_INTEL,
		.device = PCI_DEVICE_ID_INTEL_FALCON_RIDGE_4C_NHI,
		.subvenकरोr = PCI_ANY_ID, .subdevice = PCI_ANY_ID,
	पूर्ण,

	/* Thunderbolt 3 */
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_2C_NHI) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_4C_NHI) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_USBONLY_NHI) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_NHI) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_LP_USBONLY_NHI) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_2C_NHI) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_4C_NHI) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ALPINE_RIDGE_C_USBONLY_NHI) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_TITAN_RIDGE_2C_NHI) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_TITAN_RIDGE_4C_NHI) पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ICL_NHI0),
	  .driver_data = (kernel_uदीर्घ_t)&icl_nhi_ops पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_ICL_NHI1),
	  .driver_data = (kernel_uदीर्घ_t)&icl_nhi_ops पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_TGL_NHI0),
	  .driver_data = (kernel_uदीर्घ_t)&icl_nhi_ops पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_TGL_NHI1),
	  .driver_data = (kernel_uदीर्घ_t)&icl_nhi_ops पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_TGL_H_NHI0),
	  .driver_data = (kernel_uदीर्घ_t)&icl_nhi_ops पूर्ण,
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_INTEL_TGL_H_NHI1),
	  .driver_data = (kernel_uदीर्घ_t)&icl_nhi_ops पूर्ण,

	/* Any USB4 compliant host */
	अणु PCI_DEVICE_CLASS(PCI_CLASS_SERIAL_USB_USB4, ~0) पूर्ण,

	अणु 0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, nhi_ids);
MODULE_LICENSE("GPL");

अटल काष्ठा pci_driver nhi_driver = अणु
	.name = "thunderbolt",
	.id_table = nhi_ids,
	.probe = nhi_probe,
	.हटाओ = nhi_हटाओ,
	.shutकरोwn = nhi_हटाओ,
	.driver.pm = &nhi_pm_ops,
पूर्ण;

अटल पूर्णांक __init nhi_init(व्योम)
अणु
	पूर्णांक ret;

	ret = tb_करोमुख्य_init();
	अगर (ret)
		वापस ret;
	ret = pci_रेजिस्टर_driver(&nhi_driver);
	अगर (ret)
		tb_करोमुख्य_निकास();
	वापस ret;
पूर्ण

अटल व्योम __निकास nhi_unload(व्योम)
अणु
	pci_unरेजिस्टर_driver(&nhi_driver);
	tb_करोमुख्य_निकास();
पूर्ण

rootfs_initcall(nhi_init);
module_निकास(nhi_unload);
