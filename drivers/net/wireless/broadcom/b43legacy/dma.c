<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43legacy wireless driver

  DMA ringbuffer and descriptor allocation/management

  Copyright (c) 2005, 2006 Michael Buesch <m@bues.ch>

  Some code in this file is derived from the b44.c driver
  Copyright (C) 2002 David S. Miller
  Copyright (C) Pekka Pietikainen


*/

#समावेश "b43legacy.h"
#समावेश "dma.h"
#समावेश "main.h"
#समावेश "debugfs.h"
#समावेश "xmit.h"

#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/dst.h>

/* 32bit DMA ops. */
अटल
काष्ठा b43legacy_dmadesc32 *op32_idx2desc(काष्ठा b43legacy_dmaring *ring,
					  पूर्णांक slot,
					  काष्ठा b43legacy_dmadesc_meta **meta)
अणु
	काष्ठा b43legacy_dmadesc32 *desc;

	*meta = &(ring->meta[slot]);
	desc = ring->descbase;
	desc = &(desc[slot]);

	वापस desc;
पूर्ण

अटल व्योम op32_fill_descriptor(काष्ठा b43legacy_dmaring *ring,
				 काष्ठा b43legacy_dmadesc32 *desc,
				 dma_addr_t dmaaddr, u16 bufsize,
				 पूर्णांक start, पूर्णांक end, पूर्णांक irq)
अणु
	काष्ठा b43legacy_dmadesc32 *descbase = ring->descbase;
	पूर्णांक slot;
	u32 ctl;
	u32 addr;
	u32 addrext;

	slot = (पूर्णांक)(desc - descbase);
	B43legacy_WARN_ON(!(slot >= 0 && slot < ring->nr_slots));

	addr = (u32)(dmaaddr & ~SSB_DMA_TRANSLATION_MASK);
	addrext = (u32)(dmaaddr & SSB_DMA_TRANSLATION_MASK)
		   >> SSB_DMA_TRANSLATION_SHIFT;
	addr |= ring->dev->dma.translation;
	ctl = (bufsize - ring->frameoffset)
	      & B43legacy_DMA32_DCTL_BYTECNT;
	अगर (slot == ring->nr_slots - 1)
		ctl |= B43legacy_DMA32_DCTL_DTABLEEND;
	अगर (start)
		ctl |= B43legacy_DMA32_DCTL_FRAMESTART;
	अगर (end)
		ctl |= B43legacy_DMA32_DCTL_FRAMEEND;
	अगर (irq)
		ctl |= B43legacy_DMA32_DCTL_IRQ;
	ctl |= (addrext << B43legacy_DMA32_DCTL_ADDREXT_SHIFT)
	       & B43legacy_DMA32_DCTL_ADDREXT_MASK;

	desc->control = cpu_to_le32(ctl);
	desc->address = cpu_to_le32(addr);
पूर्ण

अटल व्योम op32_poke_tx(काष्ठा b43legacy_dmaring *ring, पूर्णांक slot)
अणु
	b43legacy_dma_ग_लिखो(ring, B43legacy_DMA32_TXINDEX,
			    (u32)(slot * माप(काष्ठा b43legacy_dmadesc32)));
पूर्ण

अटल व्योम op32_tx_suspend(काष्ठा b43legacy_dmaring *ring)
अणु
	b43legacy_dma_ग_लिखो(ring, B43legacy_DMA32_TXCTL,
			    b43legacy_dma_पढ़ो(ring, B43legacy_DMA32_TXCTL)
			    | B43legacy_DMA32_TXSUSPEND);
पूर्ण

अटल व्योम op32_tx_resume(काष्ठा b43legacy_dmaring *ring)
अणु
	b43legacy_dma_ग_लिखो(ring, B43legacy_DMA32_TXCTL,
			    b43legacy_dma_पढ़ो(ring, B43legacy_DMA32_TXCTL)
			    & ~B43legacy_DMA32_TXSUSPEND);
पूर्ण

अटल पूर्णांक op32_get_current_rxslot(काष्ठा b43legacy_dmaring *ring)
अणु
	u32 val;

	val = b43legacy_dma_पढ़ो(ring, B43legacy_DMA32_RXSTATUS);
	val &= B43legacy_DMA32_RXDPTR;

	वापस (val / माप(काष्ठा b43legacy_dmadesc32));
पूर्ण

अटल व्योम op32_set_current_rxslot(काष्ठा b43legacy_dmaring *ring,
				    पूर्णांक slot)
अणु
	b43legacy_dma_ग_लिखो(ring, B43legacy_DMA32_RXINDEX,
			    (u32)(slot * माप(काष्ठा b43legacy_dmadesc32)));
पूर्ण

अटल अंतरभूत पूर्णांक मुक्त_slots(काष्ठा b43legacy_dmaring *ring)
अणु
	वापस (ring->nr_slots - ring->used_slots);
पूर्ण

अटल अंतरभूत पूर्णांक next_slot(काष्ठा b43legacy_dmaring *ring, पूर्णांक slot)
अणु
	B43legacy_WARN_ON(!(slot >= -1 && slot <= ring->nr_slots - 1));
	अगर (slot == ring->nr_slots - 1)
		वापस 0;
	वापस slot + 1;
पूर्ण

अटल अंतरभूत पूर्णांक prev_slot(काष्ठा b43legacy_dmaring *ring, पूर्णांक slot)
अणु
	B43legacy_WARN_ON(!(slot >= 0 && slot <= ring->nr_slots - 1));
	अगर (slot == 0)
		वापस ring->nr_slots - 1;
	वापस slot - 1;
पूर्ण

#अगर_घोषित CONFIG_B43LEGACY_DEBUG
अटल व्योम update_max_used_slots(काष्ठा b43legacy_dmaring *ring,
				  पूर्णांक current_used_slots)
अणु
	अगर (current_used_slots <= ring->max_used_slots)
		वापस;
	ring->max_used_slots = current_used_slots;
	अगर (b43legacy_debug(ring->dev, B43legacy_DBG_DMAVERBOSE))
		b43legacydbg(ring->dev->wl,
		       "max_used_slots increased to %d on %s ring %d\n",
		       ring->max_used_slots,
		       ring->tx ? "TX" : "RX",
		       ring->index);
पूर्ण
#अन्यथा
अटल अंतरभूत
व्योम update_max_used_slots(काष्ठा b43legacy_dmaring *ring,
			   पूर्णांक current_used_slots)
अणु पूर्ण
#पूर्ण_अगर /* DEBUG */

/* Request a slot क्रम usage. */
अटल अंतरभूत
पूर्णांक request_slot(काष्ठा b43legacy_dmaring *ring)
अणु
	पूर्णांक slot;

	B43legacy_WARN_ON(!ring->tx);
	B43legacy_WARN_ON(ring->stopped);
	B43legacy_WARN_ON(मुक्त_slots(ring) == 0);

	slot = next_slot(ring, ring->current_slot);
	ring->current_slot = slot;
	ring->used_slots++;

	update_max_used_slots(ring, ring->used_slots);

	वापस slot;
पूर्ण

/* Mac80211-queue to b43legacy-ring mapping */
अटल काष्ठा b43legacy_dmaring *priority_to_txring(
						काष्ठा b43legacy_wldev *dev,
						पूर्णांक queue_priority)
अणु
	काष्ठा b43legacy_dmaring *ring;

/*FIXME: For now we always run on TX-ring-1 */
वापस dev->dma.tx_ring1;

	/* 0 = highest priority */
	चयन (queue_priority) अणु
	शेष:
		B43legacy_WARN_ON(1);
		fallthrough;
	हाल 0:
		ring = dev->dma.tx_ring3;
		अवरोध;
	हाल 1:
		ring = dev->dma.tx_ring2;
		अवरोध;
	हाल 2:
		ring = dev->dma.tx_ring1;
		अवरोध;
	हाल 3:
		ring = dev->dma.tx_ring0;
		अवरोध;
	हाल 4:
		ring = dev->dma.tx_ring4;
		अवरोध;
	हाल 5:
		ring = dev->dma.tx_ring5;
		अवरोध;
	पूर्ण

	वापस ring;
पूर्ण

/* Bcm4301-ring to mac80211-queue mapping */
अटल अंतरभूत पूर्णांक txring_to_priority(काष्ठा b43legacy_dmaring *ring)
अणु
	अटल स्थिर u8 idx_to_prio[] =
		अणु 3, 2, 1, 0, 4, 5, पूर्ण;

/*FIXME: have only one queue, क्रम now */
वापस 0;

	वापस idx_to_prio[ring->index];
पूर्ण


अटल u16 b43legacy_dmacontroller_base(क्रमागत b43legacy_dmatype type,
					पूर्णांक controller_idx)
अणु
	अटल स्थिर u16 map32[] = अणु
		B43legacy_MMIO_DMA32_BASE0,
		B43legacy_MMIO_DMA32_BASE1,
		B43legacy_MMIO_DMA32_BASE2,
		B43legacy_MMIO_DMA32_BASE3,
		B43legacy_MMIO_DMA32_BASE4,
		B43legacy_MMIO_DMA32_BASE5,
	पूर्ण;

	B43legacy_WARN_ON(!(controller_idx >= 0 &&
			  controller_idx < ARRAY_SIZE(map32)));
	वापस map32[controller_idx];
पूर्ण

अटल अंतरभूत
dma_addr_t map_descbuffer(काष्ठा b43legacy_dmaring *ring,
			  अचिन्हित अक्षर *buf,
			  माप_प्रकार len,
			  पूर्णांक tx)
अणु
	dma_addr_t dmaaddr;

	अगर (tx)
		dmaaddr = dma_map_single(ring->dev->dev->dma_dev,
					     buf, len,
					     DMA_TO_DEVICE);
	अन्यथा
		dmaaddr = dma_map_single(ring->dev->dev->dma_dev,
					     buf, len,
					     DMA_FROM_DEVICE);

	वापस dmaaddr;
पूर्ण

अटल अंतरभूत
व्योम unmap_descbuffer(काष्ठा b43legacy_dmaring *ring,
		      dma_addr_t addr,
		      माप_प्रकार len,
		      पूर्णांक tx)
अणु
	अगर (tx)
		dma_unmap_single(ring->dev->dev->dma_dev,
				     addr, len,
				     DMA_TO_DEVICE);
	अन्यथा
		dma_unmap_single(ring->dev->dev->dma_dev,
				     addr, len,
				     DMA_FROM_DEVICE);
पूर्ण

अटल अंतरभूत
व्योम sync_descbuffer_क्रम_cpu(काष्ठा b43legacy_dmaring *ring,
			     dma_addr_t addr,
			     माप_प्रकार len)
अणु
	B43legacy_WARN_ON(ring->tx);

	dma_sync_single_क्रम_cpu(ring->dev->dev->dma_dev,
				addr, len, DMA_FROM_DEVICE);
पूर्ण

अटल अंतरभूत
व्योम sync_descbuffer_क्रम_device(काष्ठा b43legacy_dmaring *ring,
				dma_addr_t addr,
				माप_प्रकार len)
अणु
	B43legacy_WARN_ON(ring->tx);

	dma_sync_single_क्रम_device(ring->dev->dev->dma_dev,
				   addr, len, DMA_FROM_DEVICE);
पूर्ण

अटल अंतरभूत
व्योम मुक्त_descriptor_buffer(काष्ठा b43legacy_dmaring *ring,
			    काष्ठा b43legacy_dmadesc_meta *meta,
			    पूर्णांक irq_context)
अणु
	अगर (meta->skb) अणु
		अगर (irq_context)
			dev_kमुक्त_skb_irq(meta->skb);
		अन्यथा
			dev_kमुक्त_skb(meta->skb);
		meta->skb = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_ringmemory(काष्ठा b43legacy_dmaring *ring)
अणु
	/* GFP flags must match the flags in मुक्त_ringmemory()! */
	ring->descbase = dma_alloc_coherent(ring->dev->dev->dma_dev,
					    B43legacy_DMA_RINGMEMSIZE,
					    &(ring->dmabase), GFP_KERNEL);
	अगर (!ring->descbase)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_ringmemory(काष्ठा b43legacy_dmaring *ring)
अणु
	dma_मुक्त_coherent(ring->dev->dev->dma_dev, B43legacy_DMA_RINGMEMSIZE,
			  ring->descbase, ring->dmabase);
पूर्ण

/* Reset the RX DMA channel */
अटल पूर्णांक b43legacy_dmacontroller_rx_reset(काष्ठा b43legacy_wldev *dev,
					    u16 mmio_base,
					    क्रमागत b43legacy_dmatype type)
अणु
	पूर्णांक i;
	u32 value;
	u16 offset;

	might_sleep();

	offset = B43legacy_DMA32_RXCTL;
	b43legacy_ग_लिखो32(dev, mmio_base + offset, 0);
	क्रम (i = 0; i < 10; i++) अणु
		offset = B43legacy_DMA32_RXSTATUS;
		value = b43legacy_पढ़ो32(dev, mmio_base + offset);
		value &= B43legacy_DMA32_RXSTATE;
		अगर (value == B43legacy_DMA32_RXSTAT_DISABLED) अणु
			i = -1;
			अवरोध;
		पूर्ण
		msleep(1);
	पूर्ण
	अगर (i != -1) अणु
		b43legacyerr(dev->wl, "DMA RX reset timed out\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/* Reset the RX DMA channel */
अटल पूर्णांक b43legacy_dmacontroller_tx_reset(काष्ठा b43legacy_wldev *dev,
					    u16 mmio_base,
					    क्रमागत b43legacy_dmatype type)
अणु
	पूर्णांक i;
	u32 value;
	u16 offset;

	might_sleep();

	क्रम (i = 0; i < 10; i++) अणु
		offset = B43legacy_DMA32_TXSTATUS;
		value = b43legacy_पढ़ो32(dev, mmio_base + offset);
		value &= B43legacy_DMA32_TXSTATE;
		अगर (value == B43legacy_DMA32_TXSTAT_DISABLED ||
		    value == B43legacy_DMA32_TXSTAT_IDLEWAIT ||
		    value == B43legacy_DMA32_TXSTAT_STOPPED)
			अवरोध;
		msleep(1);
	पूर्ण
	offset = B43legacy_DMA32_TXCTL;
	b43legacy_ग_लिखो32(dev, mmio_base + offset, 0);
	क्रम (i = 0; i < 10; i++) अणु
		offset = B43legacy_DMA32_TXSTATUS;
		value = b43legacy_पढ़ो32(dev, mmio_base + offset);
		value &= B43legacy_DMA32_TXSTATE;
		अगर (value == B43legacy_DMA32_TXSTAT_DISABLED) अणु
			i = -1;
			अवरोध;
		पूर्ण
		msleep(1);
	पूर्ण
	अगर (i != -1) अणु
		b43legacyerr(dev->wl, "DMA TX reset timed out\n");
		वापस -ENODEV;
	पूर्ण
	/* ensure the reset is completed. */
	msleep(1);

	वापस 0;
पूर्ण

/* Check अगर a DMA mapping address is invalid. */
अटल bool b43legacy_dma_mapping_error(काष्ठा b43legacy_dmaring *ring,
					 dma_addr_t addr,
					 माप_प्रकार buffersize,
					 bool dma_to_device)
अणु
	अगर (unlikely(dma_mapping_error(ring->dev->dev->dma_dev, addr)))
		वापस true;

	चयन (ring->type) अणु
	हाल B43legacy_DMA_30BIT:
		अगर ((u64)addr + buffersize > (1ULL << 30))
			जाओ address_error;
		अवरोध;
	हाल B43legacy_DMA_32BIT:
		अगर ((u64)addr + buffersize > (1ULL << 32))
			जाओ address_error;
		अवरोध;
	पूर्ण

	/* The address is OK. */
	वापस false;

address_error:
	/* We can't support this address. Unmap it again. */
	unmap_descbuffer(ring, addr, buffersize, dma_to_device);

	वापस true;
पूर्ण

अटल पूर्णांक setup_rx_descbuffer(काष्ठा b43legacy_dmaring *ring,
			       काष्ठा b43legacy_dmadesc32 *desc,
			       काष्ठा b43legacy_dmadesc_meta *meta,
			       gfp_t gfp_flags)
अणु
	काष्ठा b43legacy_rxhdr_fw3 *rxhdr;
	काष्ठा b43legacy_hwtxstatus *txstat;
	dma_addr_t dmaaddr;
	काष्ठा sk_buff *skb;

	B43legacy_WARN_ON(ring->tx);

	skb = __dev_alloc_skb(ring->rx_buffersize, gfp_flags);
	अगर (unlikely(!skb))
		वापस -ENOMEM;
	dmaaddr = map_descbuffer(ring, skb->data,
				 ring->rx_buffersize, 0);
	अगर (b43legacy_dma_mapping_error(ring, dmaaddr, ring->rx_buffersize, 0)) अणु
		/* ugh. try to पुनः_स्मृति in zone_dma */
		gfp_flags |= GFP_DMA;

		dev_kमुक्त_skb_any(skb);

		skb = __dev_alloc_skb(ring->rx_buffersize, gfp_flags);
		अगर (unlikely(!skb))
			वापस -ENOMEM;
		dmaaddr = map_descbuffer(ring, skb->data,
					 ring->rx_buffersize, 0);
	पूर्ण

	अगर (b43legacy_dma_mapping_error(ring, dmaaddr, ring->rx_buffersize, 0)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस -EIO;
	पूर्ण

	meta->skb = skb;
	meta->dmaaddr = dmaaddr;
	op32_fill_descriptor(ring, desc, dmaaddr, ring->rx_buffersize, 0, 0, 0);

	rxhdr = (काष्ठा b43legacy_rxhdr_fw3 *)(skb->data);
	rxhdr->frame_len = 0;
	txstat = (काष्ठा b43legacy_hwtxstatus *)(skb->data);
	txstat->cookie = 0;

	वापस 0;
पूर्ण

/* Allocate the initial descbuffers.
 * This is used क्रम an RX ring only.
 */
अटल पूर्णांक alloc_initial_descbuffers(काष्ठा b43legacy_dmaring *ring)
अणु
	पूर्णांक i;
	पूर्णांक err = -ENOMEM;
	काष्ठा b43legacy_dmadesc32 *desc;
	काष्ठा b43legacy_dmadesc_meta *meta;

	क्रम (i = 0; i < ring->nr_slots; i++) अणु
		desc = op32_idx2desc(ring, i, &meta);

		err = setup_rx_descbuffer(ring, desc, meta, GFP_KERNEL);
		अगर (err) अणु
			b43legacyerr(ring->dev->wl,
			       "Failed to allocate initial descbuffers\n");
			जाओ err_unwind;
		पूर्ण
	पूर्ण
	mb(); /* all descbuffer setup beक्रमe next line */
	ring->used_slots = ring->nr_slots;
	err = 0;
out:
	वापस err;

err_unwind:
	क्रम (i--; i >= 0; i--) अणु
		desc = op32_idx2desc(ring, i, &meta);

		unmap_descbuffer(ring, meta->dmaaddr, ring->rx_buffersize, 0);
		dev_kमुक्त_skb(meta->skb);
	पूर्ण
	जाओ out;
पूर्ण

/* Do initial setup of the DMA controller.
 * Reset the controller, ग_लिखो the ring busaddress
 * and चयन the "enable" bit on.
 */
अटल पूर्णांक dmacontroller_setup(काष्ठा b43legacy_dmaring *ring)
अणु
	पूर्णांक err = 0;
	u32 value;
	u32 addrext;
	u32 trans = ring->dev->dma.translation;
	u32 ringbase = (u32)(ring->dmabase);

	अगर (ring->tx) अणु
		addrext = (ringbase & SSB_DMA_TRANSLATION_MASK)
			  >> SSB_DMA_TRANSLATION_SHIFT;
		value = B43legacy_DMA32_TXENABLE;
		value |= (addrext << B43legacy_DMA32_TXADDREXT_SHIFT)
			& B43legacy_DMA32_TXADDREXT_MASK;
		b43legacy_dma_ग_लिखो(ring, B43legacy_DMA32_TXCTL, value);
		b43legacy_dma_ग_लिखो(ring, B43legacy_DMA32_TXRING,
				    (ringbase & ~SSB_DMA_TRANSLATION_MASK)
				    | trans);
	पूर्ण अन्यथा अणु
		err = alloc_initial_descbuffers(ring);
		अगर (err)
			जाओ out;

		addrext = (ringbase & SSB_DMA_TRANSLATION_MASK)
			  >> SSB_DMA_TRANSLATION_SHIFT;
		value = (ring->frameoffset <<
			 B43legacy_DMA32_RXFROFF_SHIFT);
		value |= B43legacy_DMA32_RXENABLE;
		value |= (addrext << B43legacy_DMA32_RXADDREXT_SHIFT)
			 & B43legacy_DMA32_RXADDREXT_MASK;
		b43legacy_dma_ग_लिखो(ring, B43legacy_DMA32_RXCTL, value);
		b43legacy_dma_ग_लिखो(ring, B43legacy_DMA32_RXRING,
				    (ringbase & ~SSB_DMA_TRANSLATION_MASK)
				    | trans);
		b43legacy_dma_ग_लिखो(ring, B43legacy_DMA32_RXINDEX, 200);
	पूर्ण

out:
	वापस err;
पूर्ण

/* Shutकरोwn the DMA controller. */
अटल व्योम dmacontroller_cleanup(काष्ठा b43legacy_dmaring *ring)
अणु
	अगर (ring->tx) अणु
		b43legacy_dmacontroller_tx_reset(ring->dev, ring->mmio_base,
						 ring->type);
		b43legacy_dma_ग_लिखो(ring, B43legacy_DMA32_TXRING, 0);
	पूर्ण अन्यथा अणु
		b43legacy_dmacontroller_rx_reset(ring->dev, ring->mmio_base,
						 ring->type);
		b43legacy_dma_ग_लिखो(ring, B43legacy_DMA32_RXRING, 0);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_all_descbuffers(काष्ठा b43legacy_dmaring *ring)
अणु
	काष्ठा b43legacy_dmadesc_meta *meta;
	पूर्णांक i;

	अगर (!ring->used_slots)
		वापस;
	क्रम (i = 0; i < ring->nr_slots; i++) अणु
		op32_idx2desc(ring, i, &meta);

		अगर (!meta->skb) अणु
			B43legacy_WARN_ON(!ring->tx);
			जारी;
		पूर्ण
		अगर (ring->tx)
			unmap_descbuffer(ring, meta->dmaaddr,
					 meta->skb->len, 1);
		अन्यथा
			unmap_descbuffer(ring, meta->dmaaddr,
					 ring->rx_buffersize, 0);
		मुक्त_descriptor_buffer(ring, meta, 0);
	पूर्ण
पूर्ण

अटल क्रमागत b43legacy_dmatype b43legacy_engine_type(काष्ठा b43legacy_wldev *dev)
अणु
	u32 पंचांगp;
	u16 mmio_base;

	mmio_base = b43legacy_dmacontroller_base(0, 0);
	b43legacy_ग_लिखो32(dev,
			mmio_base + B43legacy_DMA32_TXCTL,
			B43legacy_DMA32_TXADDREXT_MASK);
	पंचांगp = b43legacy_पढ़ो32(dev, mmio_base +
			       B43legacy_DMA32_TXCTL);
	अगर (पंचांगp & B43legacy_DMA32_TXADDREXT_MASK)
		वापस B43legacy_DMA_32BIT;
	वापस B43legacy_DMA_30BIT;
पूर्ण

/* Main initialization function. */
अटल
काष्ठा b43legacy_dmaring *b43legacy_setup_dmaring(काष्ठा b43legacy_wldev *dev,
						  पूर्णांक controller_index,
						  पूर्णांक क्रम_tx,
						  क्रमागत b43legacy_dmatype type)
अणु
	काष्ठा b43legacy_dmaring *ring;
	पूर्णांक err;
	पूर्णांक nr_slots;
	dma_addr_t dma_test;

	ring = kzalloc(माप(*ring), GFP_KERNEL);
	अगर (!ring)
		जाओ out;
	ring->type = type;
	ring->dev = dev;

	nr_slots = B43legacy_RXRING_SLOTS;
	अगर (क्रम_tx)
		nr_slots = B43legacy_TXRING_SLOTS;

	ring->meta = kसुस्मृति(nr_slots, माप(काष्ठा b43legacy_dmadesc_meta),
			     GFP_KERNEL);
	अगर (!ring->meta)
		जाओ err_kमुक्त_ring;
	अगर (क्रम_tx) अणु
		ring->txhdr_cache = kसुस्मृति(nr_slots,
					माप(काष्ठा b43legacy_txhdr_fw3),
					GFP_KERNEL);
		अगर (!ring->txhdr_cache)
			जाओ err_kमुक्त_meta;

		/* test क्रम ability to dma to txhdr_cache */
		dma_test = dma_map_single(dev->dev->dma_dev, ring->txhdr_cache,
					      माप(काष्ठा b43legacy_txhdr_fw3),
					      DMA_TO_DEVICE);

		अगर (b43legacy_dma_mapping_error(ring, dma_test,
					माप(काष्ठा b43legacy_txhdr_fw3), 1)) अणु
			/* ugh पुनः_स्मृति */
			kमुक्त(ring->txhdr_cache);
			ring->txhdr_cache = kसुस्मृति(nr_slots,
					माप(काष्ठा b43legacy_txhdr_fw3),
					GFP_KERNEL | GFP_DMA);
			अगर (!ring->txhdr_cache)
				जाओ err_kमुक्त_meta;

			dma_test = dma_map_single(dev->dev->dma_dev,
					ring->txhdr_cache,
					माप(काष्ठा b43legacy_txhdr_fw3),
					DMA_TO_DEVICE);

			अगर (b43legacy_dma_mapping_error(ring, dma_test,
					माप(काष्ठा b43legacy_txhdr_fw3), 1))
				जाओ err_kमुक्त_txhdr_cache;
		पूर्ण

		dma_unmap_single(dev->dev->dma_dev, dma_test,
				 माप(काष्ठा b43legacy_txhdr_fw3),
				 DMA_TO_DEVICE);
	पूर्ण

	ring->nr_slots = nr_slots;
	ring->mmio_base = b43legacy_dmacontroller_base(type, controller_index);
	ring->index = controller_index;
	अगर (क्रम_tx) अणु
		ring->tx = true;
		ring->current_slot = -1;
	पूर्ण अन्यथा अणु
		अगर (ring->index == 0) अणु
			ring->rx_buffersize = B43legacy_DMA0_RX_BUFFERSIZE;
			ring->frameoffset = B43legacy_DMA0_RX_FRAMखातापूर्णFSET;
		पूर्ण अन्यथा अगर (ring->index == 3) अणु
			ring->rx_buffersize = B43legacy_DMA3_RX_BUFFERSIZE;
			ring->frameoffset = B43legacy_DMA3_RX_FRAMखातापूर्णFSET;
		पूर्ण अन्यथा
			B43legacy_WARN_ON(1);
	पूर्ण
#अगर_घोषित CONFIG_B43LEGACY_DEBUG
	ring->last_injected_overflow = jअगरfies;
#पूर्ण_अगर

	err = alloc_ringmemory(ring);
	अगर (err)
		जाओ err_kमुक्त_txhdr_cache;
	err = dmacontroller_setup(ring);
	अगर (err)
		जाओ err_मुक्त_ringmemory;

out:
	वापस ring;

err_मुक्त_ringmemory:
	मुक्त_ringmemory(ring);
err_kमुक्त_txhdr_cache:
	kमुक्त(ring->txhdr_cache);
err_kमुक्त_meta:
	kमुक्त(ring->meta);
err_kमुक्त_ring:
	kमुक्त(ring);
	ring = शून्य;
	जाओ out;
पूर्ण

/* Main cleanup function. */
अटल व्योम b43legacy_destroy_dmaring(काष्ठा b43legacy_dmaring *ring)
अणु
	अगर (!ring)
		वापस;

	b43legacydbg(ring->dev->wl, "DMA-%u 0x%04X (%s) max used slots:"
		     " %d/%d\n", (अचिन्हित पूर्णांक)(ring->type), ring->mmio_base,
		     (ring->tx) ? "TX" : "RX", ring->max_used_slots,
		     ring->nr_slots);
	/* Device IRQs are disabled prior entering this function,
	 * so no need to take care of concurrency with rx handler stuff.
	 */
	dmacontroller_cleanup(ring);
	मुक्त_all_descbuffers(ring);
	मुक्त_ringmemory(ring);

	kमुक्त(ring->txhdr_cache);
	kमुक्त(ring->meta);
	kमुक्त(ring);
पूर्ण

व्योम b43legacy_dma_मुक्त(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_dma *dma;

	अगर (b43legacy_using_pio(dev))
		वापस;
	dma = &dev->dma;

	b43legacy_destroy_dmaring(dma->rx_ring3);
	dma->rx_ring3 = शून्य;
	b43legacy_destroy_dmaring(dma->rx_ring0);
	dma->rx_ring0 = शून्य;

	b43legacy_destroy_dmaring(dma->tx_ring5);
	dma->tx_ring5 = शून्य;
	b43legacy_destroy_dmaring(dma->tx_ring4);
	dma->tx_ring4 = शून्य;
	b43legacy_destroy_dmaring(dma->tx_ring3);
	dma->tx_ring3 = शून्य;
	b43legacy_destroy_dmaring(dma->tx_ring2);
	dma->tx_ring2 = शून्य;
	b43legacy_destroy_dmaring(dma->tx_ring1);
	dma->tx_ring1 = शून्य;
	b43legacy_destroy_dmaring(dma->tx_ring0);
	dma->tx_ring0 = शून्य;
पूर्ण

पूर्णांक b43legacy_dma_init(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_dma *dma = &dev->dma;
	काष्ठा b43legacy_dmaring *ring;
	क्रमागत b43legacy_dmatype type = b43legacy_engine_type(dev);
	पूर्णांक err;

	err = dma_set_mask_and_coherent(dev->dev->dma_dev, DMA_BIT_MASK(type));
	अगर (err) अणु
#अगर_घोषित CONFIG_B43LEGACY_PIO
		b43legacywarn(dev->wl, "DMA for this device not supported. "
			"Falling back to PIO\n");
		dev->__using_pio = true;
		वापस -EAGAIN;
#अन्यथा
		b43legacyerr(dev->wl, "DMA for this device not supported and "
		       "no PIO support compiled in\n");
		वापस -EOPNOTSUPP;
#पूर्ण_अगर
	पूर्ण
	dma->translation = ssb_dma_translation(dev->dev);

	err = -ENOMEM;
	/* setup TX DMA channels. */
	ring = b43legacy_setup_dmaring(dev, 0, 1, type);
	अगर (!ring)
		जाओ out;
	dma->tx_ring0 = ring;

	ring = b43legacy_setup_dmaring(dev, 1, 1, type);
	अगर (!ring)
		जाओ err_destroy_tx0;
	dma->tx_ring1 = ring;

	ring = b43legacy_setup_dmaring(dev, 2, 1, type);
	अगर (!ring)
		जाओ err_destroy_tx1;
	dma->tx_ring2 = ring;

	ring = b43legacy_setup_dmaring(dev, 3, 1, type);
	अगर (!ring)
		जाओ err_destroy_tx2;
	dma->tx_ring3 = ring;

	ring = b43legacy_setup_dmaring(dev, 4, 1, type);
	अगर (!ring)
		जाओ err_destroy_tx3;
	dma->tx_ring4 = ring;

	ring = b43legacy_setup_dmaring(dev, 5, 1, type);
	अगर (!ring)
		जाओ err_destroy_tx4;
	dma->tx_ring5 = ring;

	/* setup RX DMA channels. */
	ring = b43legacy_setup_dmaring(dev, 0, 0, type);
	अगर (!ring)
		जाओ err_destroy_tx5;
	dma->rx_ring0 = ring;

	अगर (dev->dev->id.revision < 5) अणु
		ring = b43legacy_setup_dmaring(dev, 3, 0, type);
		अगर (!ring)
			जाओ err_destroy_rx0;
		dma->rx_ring3 = ring;
	पूर्ण

	b43legacydbg(dev->wl, "%u-bit DMA initialized\n", (अचिन्हित पूर्णांक)type);
	err = 0;
out:
	वापस err;

err_destroy_rx0:
	b43legacy_destroy_dmaring(dma->rx_ring0);
	dma->rx_ring0 = शून्य;
err_destroy_tx5:
	b43legacy_destroy_dmaring(dma->tx_ring5);
	dma->tx_ring5 = शून्य;
err_destroy_tx4:
	b43legacy_destroy_dmaring(dma->tx_ring4);
	dma->tx_ring4 = शून्य;
err_destroy_tx3:
	b43legacy_destroy_dmaring(dma->tx_ring3);
	dma->tx_ring3 = शून्य;
err_destroy_tx2:
	b43legacy_destroy_dmaring(dma->tx_ring2);
	dma->tx_ring2 = शून्य;
err_destroy_tx1:
	b43legacy_destroy_dmaring(dma->tx_ring1);
	dma->tx_ring1 = शून्य;
err_destroy_tx0:
	b43legacy_destroy_dmaring(dma->tx_ring0);
	dma->tx_ring0 = शून्य;
	जाओ out;
पूर्ण

/* Generate a cookie क्रम the TX header. */
अटल u16 generate_cookie(काष्ठा b43legacy_dmaring *ring,
			   पूर्णांक slot)
अणु
	u16 cookie = 0x1000;

	/* Use the upper 4 bits of the cookie as
	 * DMA controller ID and store the slot number
	 * in the lower 12 bits.
	 * Note that the cookie must never be 0, as this
	 * is a special value used in RX path.
	 */
	चयन (ring->index) अणु
	हाल 0:
		cookie = 0xA000;
		अवरोध;
	हाल 1:
		cookie = 0xB000;
		अवरोध;
	हाल 2:
		cookie = 0xC000;
		अवरोध;
	हाल 3:
		cookie = 0xD000;
		अवरोध;
	हाल 4:
		cookie = 0xE000;
		अवरोध;
	हाल 5:
		cookie = 0xF000;
		अवरोध;
	पूर्ण
	B43legacy_WARN_ON(!(((u16)slot & 0xF000) == 0x0000));
	cookie |= (u16)slot;

	वापस cookie;
पूर्ण

/* Inspect a cookie and find out to which controller/slot it beदीर्घs. */
अटल
काष्ठा b43legacy_dmaring *parse_cookie(काष्ठा b43legacy_wldev *dev,
				      u16 cookie, पूर्णांक *slot)
अणु
	काष्ठा b43legacy_dma *dma = &dev->dma;
	काष्ठा b43legacy_dmaring *ring = शून्य;

	चयन (cookie & 0xF000) अणु
	हाल 0xA000:
		ring = dma->tx_ring0;
		अवरोध;
	हाल 0xB000:
		ring = dma->tx_ring1;
		अवरोध;
	हाल 0xC000:
		ring = dma->tx_ring2;
		अवरोध;
	हाल 0xD000:
		ring = dma->tx_ring3;
		अवरोध;
	हाल 0xE000:
		ring = dma->tx_ring4;
		अवरोध;
	हाल 0xF000:
		ring = dma->tx_ring5;
		अवरोध;
	शेष:
		B43legacy_WARN_ON(1);
	पूर्ण
	*slot = (cookie & 0x0FFF);
	B43legacy_WARN_ON(!(ring && *slot >= 0 && *slot < ring->nr_slots));

	वापस ring;
पूर्ण

अटल पूर्णांक dma_tx_fragment(काष्ठा b43legacy_dmaring *ring,
			    काष्ठा sk_buff **in_skb)
अणु
	काष्ठा sk_buff *skb = *in_skb;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u8 *header;
	पूर्णांक slot, old_top_slot, old_used_slots;
	पूर्णांक err;
	काष्ठा b43legacy_dmadesc32 *desc;
	काष्ठा b43legacy_dmadesc_meta *meta;
	काष्ठा b43legacy_dmadesc_meta *meta_hdr;
	काष्ठा sk_buff *bounce_skb;

#घोषणा SLOTS_PER_PACKET  2
	B43legacy_WARN_ON(skb_shinfo(skb)->nr_frags != 0);

	old_top_slot = ring->current_slot;
	old_used_slots = ring->used_slots;

	/* Get a slot क्रम the header. */
	slot = request_slot(ring);
	desc = op32_idx2desc(ring, slot, &meta_hdr);
	स_रखो(meta_hdr, 0, माप(*meta_hdr));

	header = &(ring->txhdr_cache[slot * माप(
			       काष्ठा b43legacy_txhdr_fw3)]);
	err = b43legacy_generate_txhdr(ring->dev, header,
				 skb->data, skb->len, info,
				 generate_cookie(ring, slot));
	अगर (unlikely(err)) अणु
		ring->current_slot = old_top_slot;
		ring->used_slots = old_used_slots;
		वापस err;
	पूर्ण

	meta_hdr->dmaaddr = map_descbuffer(ring, (अचिन्हित अक्षर *)header,
					   माप(काष्ठा b43legacy_txhdr_fw3), 1);
	अगर (b43legacy_dma_mapping_error(ring, meta_hdr->dmaaddr,
					माप(काष्ठा b43legacy_txhdr_fw3), 1)) अणु
		ring->current_slot = old_top_slot;
		ring->used_slots = old_used_slots;
		वापस -EIO;
	पूर्ण
	op32_fill_descriptor(ring, desc, meta_hdr->dmaaddr,
			     माप(काष्ठा b43legacy_txhdr_fw3), 1, 0, 0);

	/* Get a slot क्रम the payload. */
	slot = request_slot(ring);
	desc = op32_idx2desc(ring, slot, &meta);
	स_रखो(meta, 0, माप(*meta));

	meta->skb = skb;
	meta->is_last_fragment = true;

	meta->dmaaddr = map_descbuffer(ring, skb->data, skb->len, 1);
	/* create a bounce buffer in zone_dma on mapping failure. */
	अगर (b43legacy_dma_mapping_error(ring, meta->dmaaddr, skb->len, 1)) अणु
		bounce_skb = alloc_skb(skb->len, GFP_KERNEL | GFP_DMA);
		अगर (!bounce_skb) अणु
			ring->current_slot = old_top_slot;
			ring->used_slots = old_used_slots;
			err = -ENOMEM;
			जाओ out_unmap_hdr;
		पूर्ण

		skb_put_data(bounce_skb, skb->data, skb->len);
		स_नकल(bounce_skb->cb, skb->cb, माप(skb->cb));
		bounce_skb->dev = skb->dev;
		skb_set_queue_mapping(bounce_skb, skb_get_queue_mapping(skb));
		info = IEEE80211_SKB_CB(bounce_skb);

		dev_kमुक्त_skb_any(skb);
		skb = bounce_skb;
		*in_skb = bounce_skb;
		meta->skb = skb;
		meta->dmaaddr = map_descbuffer(ring, skb->data, skb->len, 1);
		अगर (b43legacy_dma_mapping_error(ring, meta->dmaaddr, skb->len, 1)) अणु
			ring->current_slot = old_top_slot;
			ring->used_slots = old_used_slots;
			err = -EIO;
			जाओ out_मुक्त_bounce;
		पूर्ण
	पूर्ण

	op32_fill_descriptor(ring, desc, meta->dmaaddr,
			     skb->len, 0, 1, 1);

	wmb();	/* previous stuff MUST be करोne */
	/* Now transfer the whole frame. */
	op32_poke_tx(ring, next_slot(ring, slot));
	वापस 0;

out_मुक्त_bounce:
	dev_kमुक्त_skb_any(skb);
out_unmap_hdr:
	unmap_descbuffer(ring, meta_hdr->dmaaddr,
			 माप(काष्ठा b43legacy_txhdr_fw3), 1);
	वापस err;
पूर्ण

अटल अंतरभूत
पूर्णांक should_inject_overflow(काष्ठा b43legacy_dmaring *ring)
अणु
#अगर_घोषित CONFIG_B43LEGACY_DEBUG
	अगर (unlikely(b43legacy_debug(ring->dev,
				     B43legacy_DBG_DMAOVERFLOW))) अणु
		/* Check अगर we should inject another ringbuffer overflow
		 * to test handling of this situation in the stack. */
		अचिन्हित दीर्घ next_overflow;

		next_overflow = ring->last_injected_overflow + HZ;
		अगर (समय_after(jअगरfies, next_overflow)) अणु
			ring->last_injected_overflow = jअगरfies;
			b43legacydbg(ring->dev->wl,
			       "Injecting TX ring overflow on "
			       "DMA controller %d\n", ring->index);
			वापस 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_B43LEGACY_DEBUG */
	वापस 0;
पूर्ण

पूर्णांक b43legacy_dma_tx(काष्ठा b43legacy_wldev *dev,
		     काष्ठा sk_buff *skb)
अणु
	काष्ठा b43legacy_dmaring *ring;
	पूर्णांक err = 0;

	ring = priority_to_txring(dev, skb_get_queue_mapping(skb));
	B43legacy_WARN_ON(!ring->tx);

	अगर (unlikely(ring->stopped)) अणु
		/* We get here only because of a bug in mac80211.
		 * Because of a race, one packet may be queued after
		 * the queue is stopped, thus we got called when we shouldn't.
		 * For now, just refuse the transmit. */
		अगर (b43legacy_debug(dev, B43legacy_DBG_DMAVERBOSE))
			b43legacyerr(dev->wl, "Packet after queue stopped\n");
		वापस -ENOSPC;
	पूर्ण

	अगर (WARN_ON(मुक्त_slots(ring) < SLOTS_PER_PACKET)) अणु
		/* If we get here, we have a real error with the queue
		 * full, but queues not stopped. */
		b43legacyerr(dev->wl, "DMA queue overflow\n");
		वापस -ENOSPC;
	पूर्ण

	/* dma_tx_fragment might पुनः_स्मृतिate the skb, so invalidate poपूर्णांकers poपूर्णांकing
	 * पूर्णांकo the skb data or cb now. */
	err = dma_tx_fragment(ring, &skb);
	अगर (unlikely(err == -ENOKEY)) अणु
		/* Drop this packet, as we करोn't have the encryption key
		 * anymore and must not transmit it unencrypted. */
		dev_kमुक्त_skb_any(skb);
		वापस 0;
	पूर्ण
	अगर (unlikely(err)) अणु
		b43legacyerr(dev->wl, "DMA tx mapping failure\n");
		वापस err;
	पूर्ण
	अगर ((मुक्त_slots(ring) < SLOTS_PER_PACKET) ||
	    should_inject_overflow(ring)) अणु
		/* This TX ring is full. */
		अचिन्हित पूर्णांक skb_mapping = skb_get_queue_mapping(skb);
		ieee80211_stop_queue(dev->wl->hw, skb_mapping);
		dev->wl->tx_queue_stopped[skb_mapping] = 1;
		ring->stopped = true;
		अगर (b43legacy_debug(dev, B43legacy_DBG_DMAVERBOSE))
			b43legacydbg(dev->wl, "Stopped TX ring %d\n",
			       ring->index);
	पूर्ण
	वापस err;
पूर्ण

व्योम b43legacy_dma_handle_txstatus(काष्ठा b43legacy_wldev *dev,
				 स्थिर काष्ठा b43legacy_txstatus *status)
अणु
	काष्ठा b43legacy_dmaring *ring;
	काष्ठा b43legacy_dmadesc_meta *meta;
	पूर्णांक retry_limit;
	पूर्णांक slot;
	पूर्णांक firstused;

	ring = parse_cookie(dev, status->cookie, &slot);
	अगर (unlikely(!ring))
		वापस;
	B43legacy_WARN_ON(!ring->tx);

	/* Sanity check: TX packets are processed in-order on one ring.
	 * Check अगर the slot deduced from the cookie really is the first
	 * used slot. */
	firstused = ring->current_slot - ring->used_slots + 1;
	अगर (firstused < 0)
		firstused = ring->nr_slots + firstused;
	अगर (unlikely(slot != firstused)) अणु
		/* This possibly is a firmware bug and will result in
		 * malfunction, memory leaks and/or stall of DMA functionality.
		 */
		b43legacydbg(dev->wl, "Out of order TX status report on DMA "
			     "ring %d. Expected %d, but got %d\n",
			     ring->index, firstused, slot);
		वापस;
	पूर्ण

	जबतक (1) अणु
		B43legacy_WARN_ON(!(slot >= 0 && slot < ring->nr_slots));
		op32_idx2desc(ring, slot, &meta);

		अगर (meta->skb)
			unmap_descbuffer(ring, meta->dmaaddr,
					 meta->skb->len, 1);
		अन्यथा
			unmap_descbuffer(ring, meta->dmaaddr,
					 माप(काष्ठा b43legacy_txhdr_fw3),
					 1);

		अगर (meta->is_last_fragment) अणु
			काष्ठा ieee80211_tx_info *info;
			BUG_ON(!meta->skb);
			info = IEEE80211_SKB_CB(meta->skb);

			/* preserve the confiured retry limit beक्रमe clearing the status
			 * The xmit function has overwritten the rc's value with the actual
			 * retry limit करोne by the hardware */
			retry_limit = info->status.rates[0].count;
			ieee80211_tx_info_clear_status(info);

			अगर (status->acked)
				info->flags |= IEEE80211_TX_STAT_ACK;

			अगर (status->rts_count > dev->wl->hw->conf.लघु_frame_max_tx_count) अणु
				/*
				 * If the लघु retries (RTS, not data frame) have exceeded
				 * the limit, the hw will not have tried the selected rate,
				 * but will have used the fallback rate instead.
				 * Don't let the rate control count attempts क्रम the selected
				 * rate in this हाल, otherwise the statistics will be off.
				 */
				info->status.rates[0].count = 0;
				info->status.rates[1].count = status->frame_count;
			पूर्ण अन्यथा अणु
				अगर (status->frame_count > retry_limit) अणु
					info->status.rates[0].count = retry_limit;
					info->status.rates[1].count = status->frame_count -
							retry_limit;

				पूर्ण अन्यथा अणु
					info->status.rates[0].count = status->frame_count;
					info->status.rates[1].idx = -1;
				पूर्ण
			पूर्ण

			/* Call back to inक्रमm the ieee80211 subप्रणाली about the
			 * status of the transmission.
			 * Some fields of txstat are alपढ़ोy filled in dma_tx().
			 */
			ieee80211_tx_status_irqsafe(dev->wl->hw, meta->skb);
			/* skb is मुक्तd by ieee80211_tx_status_irqsafe() */
			meta->skb = शून्य;
		पूर्ण अन्यथा अणु
			/* No need to call मुक्त_descriptor_buffer here, as
			 * this is only the txhdr, which is not allocated.
			 */
			B43legacy_WARN_ON(meta->skb != शून्य);
		पूर्ण

		/* Everything unmapped and मुक्त'd. So it's not used anymore. */
		ring->used_slots--;

		अगर (meta->is_last_fragment)
			अवरोध;
		slot = next_slot(ring, slot);
	पूर्ण
	dev->stats.last_tx = jअगरfies;
	अगर (ring->stopped) अणु
		B43legacy_WARN_ON(मुक्त_slots(ring) < SLOTS_PER_PACKET);
		ring->stopped = false;
	पूर्ण

	अगर (dev->wl->tx_queue_stopped[ring->queue_prio]) अणु
		dev->wl->tx_queue_stopped[ring->queue_prio] = 0;
	पूर्ण अन्यथा अणु
		/* If the driver queue is running wake the corresponding
		 * mac80211 queue. */
		ieee80211_wake_queue(dev->wl->hw, ring->queue_prio);
		अगर (b43legacy_debug(dev, B43legacy_DBG_DMAVERBOSE))
			b43legacydbg(dev->wl, "Woke up TX ring %d\n",
				     ring->index);
	पूर्ण
	/* Add work to the queue. */
	ieee80211_queue_work(dev->wl->hw, &dev->wl->tx_work);
पूर्ण

अटल व्योम dma_rx(काष्ठा b43legacy_dmaring *ring,
		   पूर्णांक *slot)
अणु
	काष्ठा b43legacy_dmadesc32 *desc;
	काष्ठा b43legacy_dmadesc_meta *meta;
	काष्ठा b43legacy_rxhdr_fw3 *rxhdr;
	काष्ठा sk_buff *skb;
	u16 len;
	पूर्णांक err;
	dma_addr_t dmaaddr;

	desc = op32_idx2desc(ring, *slot, &meta);

	sync_descbuffer_क्रम_cpu(ring, meta->dmaaddr, ring->rx_buffersize);
	skb = meta->skb;

	अगर (ring->index == 3) अणु
		/* We received an xmit status. */
		काष्ठा b43legacy_hwtxstatus *hw =
				(काष्ठा b43legacy_hwtxstatus *)skb->data;
		पूर्णांक i = 0;

		जबतक (hw->cookie == 0) अणु
			अगर (i > 100)
				अवरोध;
			i++;
			udelay(2);
			barrier();
		पूर्ण
		b43legacy_handle_hwtxstatus(ring->dev, hw);
		/* recycle the descriptor buffer. */
		sync_descbuffer_क्रम_device(ring, meta->dmaaddr,
					   ring->rx_buffersize);

		वापस;
	पूर्ण
	rxhdr = (काष्ठा b43legacy_rxhdr_fw3 *)skb->data;
	len = le16_to_cpu(rxhdr->frame_len);
	अगर (len == 0) अणु
		पूर्णांक i = 0;

		करो अणु
			udelay(2);
			barrier();
			len = le16_to_cpu(rxhdr->frame_len);
		पूर्ण जबतक (len == 0 && i++ < 5);
		अगर (unlikely(len == 0)) अणु
			/* recycle the descriptor buffer. */
			sync_descbuffer_क्रम_device(ring, meta->dmaaddr,
						   ring->rx_buffersize);
			जाओ drop;
		पूर्ण
	पूर्ण
	अगर (unlikely(len > ring->rx_buffersize)) अणु
		/* The data did not fit पूर्णांकo one descriptor buffer
		 * and is split over multiple buffers.
		 * This should never happen, as we try to allocate buffers
		 * big enough. So simply ignore this packet.
		 */
		पूर्णांक cnt = 0;
		s32 पंचांगp = len;

		जबतक (1) अणु
			desc = op32_idx2desc(ring, *slot, &meta);
			/* recycle the descriptor buffer. */
			sync_descbuffer_क्रम_device(ring, meta->dmaaddr,
						   ring->rx_buffersize);
			*slot = next_slot(ring, *slot);
			cnt++;
			पंचांगp -= ring->rx_buffersize;
			अगर (पंचांगp <= 0)
				अवरोध;
		पूर्ण
		b43legacyerr(ring->dev->wl, "DMA RX buffer too small "
		       "(len: %u, buffer: %u, nr-dropped: %d)\n",
		       len, ring->rx_buffersize, cnt);
		जाओ drop;
	पूर्ण

	dmaaddr = meta->dmaaddr;
	err = setup_rx_descbuffer(ring, desc, meta, GFP_ATOMIC);
	अगर (unlikely(err)) अणु
		b43legacydbg(ring->dev->wl, "DMA RX: setup_rx_descbuffer()"
			     " failed\n");
		sync_descbuffer_क्रम_device(ring, dmaaddr,
					   ring->rx_buffersize);
		जाओ drop;
	पूर्ण

	unmap_descbuffer(ring, dmaaddr, ring->rx_buffersize, 0);
	skb_put(skb, len + ring->frameoffset);
	skb_pull(skb, ring->frameoffset);

	b43legacy_rx(ring->dev, skb, rxhdr);
drop:
	वापस;
पूर्ण

व्योम b43legacy_dma_rx(काष्ठा b43legacy_dmaring *ring)
अणु
	पूर्णांक slot;
	पूर्णांक current_slot;
	पूर्णांक used_slots = 0;

	B43legacy_WARN_ON(ring->tx);
	current_slot = op32_get_current_rxslot(ring);
	B43legacy_WARN_ON(!(current_slot >= 0 && current_slot <
			   ring->nr_slots));

	slot = ring->current_slot;
	क्रम (; slot != current_slot; slot = next_slot(ring, slot)) अणु
		dma_rx(ring, &slot);
		update_max_used_slots(ring, ++used_slots);
	पूर्ण
	op32_set_current_rxslot(ring, slot);
	ring->current_slot = slot;
पूर्ण

अटल व्योम b43legacy_dma_tx_suspend_ring(काष्ठा b43legacy_dmaring *ring)
अणु
	B43legacy_WARN_ON(!ring->tx);
	op32_tx_suspend(ring);
पूर्ण

अटल व्योम b43legacy_dma_tx_resume_ring(काष्ठा b43legacy_dmaring *ring)
अणु
	B43legacy_WARN_ON(!ring->tx);
	op32_tx_resume(ring);
पूर्ण

व्योम b43legacy_dma_tx_suspend(काष्ठा b43legacy_wldev *dev)
अणु
	b43legacy_घातer_saving_ctl_bits(dev, -1, 1);
	b43legacy_dma_tx_suspend_ring(dev->dma.tx_ring0);
	b43legacy_dma_tx_suspend_ring(dev->dma.tx_ring1);
	b43legacy_dma_tx_suspend_ring(dev->dma.tx_ring2);
	b43legacy_dma_tx_suspend_ring(dev->dma.tx_ring3);
	b43legacy_dma_tx_suspend_ring(dev->dma.tx_ring4);
	b43legacy_dma_tx_suspend_ring(dev->dma.tx_ring5);
पूर्ण

व्योम b43legacy_dma_tx_resume(काष्ठा b43legacy_wldev *dev)
अणु
	b43legacy_dma_tx_resume_ring(dev->dma.tx_ring5);
	b43legacy_dma_tx_resume_ring(dev->dma.tx_ring4);
	b43legacy_dma_tx_resume_ring(dev->dma.tx_ring3);
	b43legacy_dma_tx_resume_ring(dev->dma.tx_ring2);
	b43legacy_dma_tx_resume_ring(dev->dma.tx_ring1);
	b43legacy_dma_tx_resume_ring(dev->dma.tx_ring0);
	b43legacy_घातer_saving_ctl_bits(dev, -1, -1);
पूर्ण
