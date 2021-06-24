<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver

  DMA ringbuffer and descriptor allocation/management

  Copyright (c) 2005, 2006 Michael Buesch <m@bues.ch>

  Some code in this file is derived from the b44.c driver
  Copyright (C) 2002 David S. Miller
  Copyright (C) Pekka Pietikainen


*/

#समावेश "b43.h"
#समावेश "dma.h"
#समावेश "main.h"
#समावेश "debugfs.h"
#समावेश "xmit.h"

#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/भाग64.h>


/* Required number of TX DMA slots per TX frame.
 * This currently is 2, because we put the header and the ieee80211 frame
 * पूर्णांकo separate slots. */
#घोषणा TX_SLOTS_PER_FRAME	2

अटल u32 b43_dma_address(काष्ठा b43_dma *dma, dma_addr_t dmaaddr,
			   क्रमागत b43_addrtype addrtype)
अणु
	u32 addr;

	चयन (addrtype) अणु
	हाल B43_DMA_ADDR_LOW:
		addr = lower_32_bits(dmaaddr);
		अगर (dma->translation_in_low) अणु
			addr &= ~SSB_DMA_TRANSLATION_MASK;
			addr |= dma->translation;
		पूर्ण
		अवरोध;
	हाल B43_DMA_ADDR_HIGH:
		addr = upper_32_bits(dmaaddr);
		अगर (!dma->translation_in_low) अणु
			addr &= ~SSB_DMA_TRANSLATION_MASK;
			addr |= dma->translation;
		पूर्ण
		अवरोध;
	हाल B43_DMA_ADDR_EXT:
		अगर (dma->translation_in_low)
			addr = lower_32_bits(dmaaddr);
		अन्यथा
			addr = upper_32_bits(dmaaddr);
		addr &= SSB_DMA_TRANSLATION_MASK;
		addr >>= SSB_DMA_TRANSLATION_SHIFT;
		अवरोध;
	पूर्ण

	वापस addr;
पूर्ण

/* 32bit DMA ops. */
अटल
काष्ठा b43_dmadesc_generic *op32_idx2desc(काष्ठा b43_dmaring *ring,
					  पूर्णांक slot,
					  काष्ठा b43_dmadesc_meta **meta)
अणु
	काष्ठा b43_dmadesc32 *desc;

	*meta = &(ring->meta[slot]);
	desc = ring->descbase;
	desc = &(desc[slot]);

	वापस (काष्ठा b43_dmadesc_generic *)desc;
पूर्ण

अटल व्योम op32_fill_descriptor(काष्ठा b43_dmaring *ring,
				 काष्ठा b43_dmadesc_generic *desc,
				 dma_addr_t dmaaddr, u16 bufsize,
				 पूर्णांक start, पूर्णांक end, पूर्णांक irq)
अणु
	काष्ठा b43_dmadesc32 *descbase = ring->descbase;
	पूर्णांक slot;
	u32 ctl;
	u32 addr;
	u32 addrext;

	slot = (पूर्णांक)(&(desc->dma32) - descbase);
	B43_WARN_ON(!(slot >= 0 && slot < ring->nr_slots));

	addr = b43_dma_address(&ring->dev->dma, dmaaddr, B43_DMA_ADDR_LOW);
	addrext = b43_dma_address(&ring->dev->dma, dmaaddr, B43_DMA_ADDR_EXT);

	ctl = bufsize & B43_DMA32_DCTL_BYTECNT;
	अगर (slot == ring->nr_slots - 1)
		ctl |= B43_DMA32_DCTL_DTABLEEND;
	अगर (start)
		ctl |= B43_DMA32_DCTL_FRAMESTART;
	अगर (end)
		ctl |= B43_DMA32_DCTL_FRAMEEND;
	अगर (irq)
		ctl |= B43_DMA32_DCTL_IRQ;
	ctl |= (addrext << B43_DMA32_DCTL_ADDREXT_SHIFT)
	    & B43_DMA32_DCTL_ADDREXT_MASK;

	desc->dma32.control = cpu_to_le32(ctl);
	desc->dma32.address = cpu_to_le32(addr);
पूर्ण

अटल व्योम op32_poke_tx(काष्ठा b43_dmaring *ring, पूर्णांक slot)
अणु
	b43_dma_ग_लिखो(ring, B43_DMA32_TXINDEX,
		      (u32) (slot * माप(काष्ठा b43_dmadesc32)));
पूर्ण

अटल व्योम op32_tx_suspend(काष्ठा b43_dmaring *ring)
अणु
	b43_dma_ग_लिखो(ring, B43_DMA32_TXCTL, b43_dma_पढ़ो(ring, B43_DMA32_TXCTL)
		      | B43_DMA32_TXSUSPEND);
पूर्ण

अटल व्योम op32_tx_resume(काष्ठा b43_dmaring *ring)
अणु
	b43_dma_ग_लिखो(ring, B43_DMA32_TXCTL, b43_dma_पढ़ो(ring, B43_DMA32_TXCTL)
		      & ~B43_DMA32_TXSUSPEND);
पूर्ण

अटल पूर्णांक op32_get_current_rxslot(काष्ठा b43_dmaring *ring)
अणु
	u32 val;

	val = b43_dma_पढ़ो(ring, B43_DMA32_RXSTATUS);
	val &= B43_DMA32_RXDPTR;

	वापस (val / माप(काष्ठा b43_dmadesc32));
पूर्ण

अटल व्योम op32_set_current_rxslot(काष्ठा b43_dmaring *ring, पूर्णांक slot)
अणु
	b43_dma_ग_लिखो(ring, B43_DMA32_RXINDEX,
		      (u32) (slot * माप(काष्ठा b43_dmadesc32)));
पूर्ण

अटल स्थिर काष्ठा b43_dma_ops dma32_ops = अणु
	.idx2desc = op32_idx2desc,
	.fill_descriptor = op32_fill_descriptor,
	.poke_tx = op32_poke_tx,
	.tx_suspend = op32_tx_suspend,
	.tx_resume = op32_tx_resume,
	.get_current_rxslot = op32_get_current_rxslot,
	.set_current_rxslot = op32_set_current_rxslot,
पूर्ण;

/* 64bit DMA ops. */
अटल
काष्ठा b43_dmadesc_generic *op64_idx2desc(काष्ठा b43_dmaring *ring,
					  पूर्णांक slot,
					  काष्ठा b43_dmadesc_meta **meta)
अणु
	काष्ठा b43_dmadesc64 *desc;

	*meta = &(ring->meta[slot]);
	desc = ring->descbase;
	desc = &(desc[slot]);

	वापस (काष्ठा b43_dmadesc_generic *)desc;
पूर्ण

अटल व्योम op64_fill_descriptor(काष्ठा b43_dmaring *ring,
				 काष्ठा b43_dmadesc_generic *desc,
				 dma_addr_t dmaaddr, u16 bufsize,
				 पूर्णांक start, पूर्णांक end, पूर्णांक irq)
अणु
	काष्ठा b43_dmadesc64 *descbase = ring->descbase;
	पूर्णांक slot;
	u32 ctl0 = 0, ctl1 = 0;
	u32 addrlo, addrhi;
	u32 addrext;

	slot = (पूर्णांक)(&(desc->dma64) - descbase);
	B43_WARN_ON(!(slot >= 0 && slot < ring->nr_slots));

	addrlo = b43_dma_address(&ring->dev->dma, dmaaddr, B43_DMA_ADDR_LOW);
	addrhi = b43_dma_address(&ring->dev->dma, dmaaddr, B43_DMA_ADDR_HIGH);
	addrext = b43_dma_address(&ring->dev->dma, dmaaddr, B43_DMA_ADDR_EXT);

	अगर (slot == ring->nr_slots - 1)
		ctl0 |= B43_DMA64_DCTL0_DTABLEEND;
	अगर (start)
		ctl0 |= B43_DMA64_DCTL0_FRAMESTART;
	अगर (end)
		ctl0 |= B43_DMA64_DCTL0_FRAMEEND;
	अगर (irq)
		ctl0 |= B43_DMA64_DCTL0_IRQ;
	ctl1 |= bufsize & B43_DMA64_DCTL1_BYTECNT;
	ctl1 |= (addrext << B43_DMA64_DCTL1_ADDREXT_SHIFT)
	    & B43_DMA64_DCTL1_ADDREXT_MASK;

	desc->dma64.control0 = cpu_to_le32(ctl0);
	desc->dma64.control1 = cpu_to_le32(ctl1);
	desc->dma64.address_low = cpu_to_le32(addrlo);
	desc->dma64.address_high = cpu_to_le32(addrhi);
पूर्ण

अटल व्योम op64_poke_tx(काष्ठा b43_dmaring *ring, पूर्णांक slot)
अणु
	b43_dma_ग_लिखो(ring, B43_DMA64_TXINDEX,
		      (u32) (slot * माप(काष्ठा b43_dmadesc64)));
पूर्ण

अटल व्योम op64_tx_suspend(काष्ठा b43_dmaring *ring)
अणु
	b43_dma_ग_लिखो(ring, B43_DMA64_TXCTL, b43_dma_पढ़ो(ring, B43_DMA64_TXCTL)
		      | B43_DMA64_TXSUSPEND);
पूर्ण

अटल व्योम op64_tx_resume(काष्ठा b43_dmaring *ring)
अणु
	b43_dma_ग_लिखो(ring, B43_DMA64_TXCTL, b43_dma_पढ़ो(ring, B43_DMA64_TXCTL)
		      & ~B43_DMA64_TXSUSPEND);
पूर्ण

अटल पूर्णांक op64_get_current_rxslot(काष्ठा b43_dmaring *ring)
अणु
	u32 val;

	val = b43_dma_पढ़ो(ring, B43_DMA64_RXSTATUS);
	val &= B43_DMA64_RXSTATDPTR;

	वापस (val / माप(काष्ठा b43_dmadesc64));
पूर्ण

अटल व्योम op64_set_current_rxslot(काष्ठा b43_dmaring *ring, पूर्णांक slot)
अणु
	b43_dma_ग_लिखो(ring, B43_DMA64_RXINDEX,
		      (u32) (slot * माप(काष्ठा b43_dmadesc64)));
पूर्ण

अटल स्थिर काष्ठा b43_dma_ops dma64_ops = अणु
	.idx2desc = op64_idx2desc,
	.fill_descriptor = op64_fill_descriptor,
	.poke_tx = op64_poke_tx,
	.tx_suspend = op64_tx_suspend,
	.tx_resume = op64_tx_resume,
	.get_current_rxslot = op64_get_current_rxslot,
	.set_current_rxslot = op64_set_current_rxslot,
पूर्ण;

अटल अंतरभूत पूर्णांक मुक्त_slots(काष्ठा b43_dmaring *ring)
अणु
	वापस (ring->nr_slots - ring->used_slots);
पूर्ण

अटल अंतरभूत पूर्णांक next_slot(काष्ठा b43_dmaring *ring, पूर्णांक slot)
अणु
	B43_WARN_ON(!(slot >= -1 && slot <= ring->nr_slots - 1));
	अगर (slot == ring->nr_slots - 1)
		वापस 0;
	वापस slot + 1;
पूर्ण

अटल अंतरभूत पूर्णांक prev_slot(काष्ठा b43_dmaring *ring, पूर्णांक slot)
अणु
	B43_WARN_ON(!(slot >= 0 && slot <= ring->nr_slots - 1));
	अगर (slot == 0)
		वापस ring->nr_slots - 1;
	वापस slot - 1;
पूर्ण

#अगर_घोषित CONFIG_B43_DEBUG
अटल व्योम update_max_used_slots(काष्ठा b43_dmaring *ring,
				  पूर्णांक current_used_slots)
अणु
	अगर (current_used_slots <= ring->max_used_slots)
		वापस;
	ring->max_used_slots = current_used_slots;
	अगर (b43_debug(ring->dev, B43_DBG_DMAVERBOSE)) अणु
		b43dbg(ring->dev->wl,
		       "max_used_slots increased to %d on %s ring %d\n",
		       ring->max_used_slots,
		       ring->tx ? "TX" : "RX", ring->index);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत
    व्योम update_max_used_slots(काष्ठा b43_dmaring *ring, पूर्णांक current_used_slots)
अणु
पूर्ण
#पूर्ण_अगर /* DEBUG */

/* Request a slot क्रम usage. */
अटल अंतरभूत पूर्णांक request_slot(काष्ठा b43_dmaring *ring)
अणु
	पूर्णांक slot;

	B43_WARN_ON(!ring->tx);
	B43_WARN_ON(ring->stopped);
	B43_WARN_ON(मुक्त_slots(ring) == 0);

	slot = next_slot(ring, ring->current_slot);
	ring->current_slot = slot;
	ring->used_slots++;

	update_max_used_slots(ring, ring->used_slots);

	वापस slot;
पूर्ण

अटल u16 b43_dmacontroller_base(क्रमागत b43_dmatype type, पूर्णांक controller_idx)
अणु
	अटल स्थिर u16 map64[] = अणु
		B43_MMIO_DMA64_BASE0,
		B43_MMIO_DMA64_BASE1,
		B43_MMIO_DMA64_BASE2,
		B43_MMIO_DMA64_BASE3,
		B43_MMIO_DMA64_BASE4,
		B43_MMIO_DMA64_BASE5,
	पूर्ण;
	अटल स्थिर u16 map32[] = अणु
		B43_MMIO_DMA32_BASE0,
		B43_MMIO_DMA32_BASE1,
		B43_MMIO_DMA32_BASE2,
		B43_MMIO_DMA32_BASE3,
		B43_MMIO_DMA32_BASE4,
		B43_MMIO_DMA32_BASE5,
	पूर्ण;

	अगर (type == B43_DMA_64BIT) अणु
		B43_WARN_ON(!(controller_idx >= 0 &&
			      controller_idx < ARRAY_SIZE(map64)));
		वापस map64[controller_idx];
	पूर्ण
	B43_WARN_ON(!(controller_idx >= 0 &&
		      controller_idx < ARRAY_SIZE(map32)));
	वापस map32[controller_idx];
पूर्ण

अटल अंतरभूत
    dma_addr_t map_descbuffer(काष्ठा b43_dmaring *ring,
			      अचिन्हित अक्षर *buf, माप_प्रकार len, पूर्णांक tx)
अणु
	dma_addr_t dmaaddr;

	अगर (tx) अणु
		dmaaddr = dma_map_single(ring->dev->dev->dma_dev,
					 buf, len, DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		dmaaddr = dma_map_single(ring->dev->dev->dma_dev,
					 buf, len, DMA_FROM_DEVICE);
	पूर्ण

	वापस dmaaddr;
पूर्ण

अटल अंतरभूत
    व्योम unmap_descbuffer(काष्ठा b43_dmaring *ring,
			  dma_addr_t addr, माप_प्रकार len, पूर्णांक tx)
अणु
	अगर (tx) अणु
		dma_unmap_single(ring->dev->dev->dma_dev,
				 addr, len, DMA_TO_DEVICE);
	पूर्ण अन्यथा अणु
		dma_unmap_single(ring->dev->dev->dma_dev,
				 addr, len, DMA_FROM_DEVICE);
	पूर्ण
पूर्ण

अटल अंतरभूत
    व्योम sync_descbuffer_क्रम_cpu(काष्ठा b43_dmaring *ring,
				 dma_addr_t addr, माप_प्रकार len)
अणु
	B43_WARN_ON(ring->tx);
	dma_sync_single_क्रम_cpu(ring->dev->dev->dma_dev,
				    addr, len, DMA_FROM_DEVICE);
पूर्ण

अटल अंतरभूत
    व्योम sync_descbuffer_क्रम_device(काष्ठा b43_dmaring *ring,
				    dma_addr_t addr, माप_प्रकार len)
अणु
	B43_WARN_ON(ring->tx);
	dma_sync_single_क्रम_device(ring->dev->dev->dma_dev,
				   addr, len, DMA_FROM_DEVICE);
पूर्ण

अटल अंतरभूत
    व्योम मुक्त_descriptor_buffer(काष्ठा b43_dmaring *ring,
				काष्ठा b43_dmadesc_meta *meta)
अणु
	अगर (meta->skb) अणु
		अगर (ring->tx)
			ieee80211_मुक्त_txskb(ring->dev->wl->hw, meta->skb);
		अन्यथा
			dev_kमुक्त_skb_any(meta->skb);
		meta->skb = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_ringmemory(काष्ठा b43_dmaring *ring)
अणु
	/* The specs call क्रम 4K buffers क्रम 30- and 32-bit DMA with 4K
	 * alignment and 8K buffers क्रम 64-bit DMA with 8K alignment.
	 * In practice we could use smaller buffers क्रम the latter, but the
	 * alignment is really important because of the hardware bug. If bit
	 * 0x00001000 is used in DMA address, some hardware (like BCM4331)
	 * copies that bit पूर्णांकo B43_DMA64_RXSTATUS and we get false values from
	 * B43_DMA64_RXSTATDPTR. Let's just use 8K buffers even if we don't use
	 * more than 256 slots क्रम ring.
	 */
	u16 ring_mem_size = (ring->type == B43_DMA_64BIT) ?
				B43_DMA64_RINGMEMSIZE : B43_DMA32_RINGMEMSIZE;

	ring->descbase = dma_alloc_coherent(ring->dev->dev->dma_dev,
					    ring_mem_size, &(ring->dmabase),
					    GFP_KERNEL);
	अगर (!ring->descbase)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_ringmemory(काष्ठा b43_dmaring *ring)
अणु
	u16 ring_mem_size = (ring->type == B43_DMA_64BIT) ?
				B43_DMA64_RINGMEMSIZE : B43_DMA32_RINGMEMSIZE;
	dma_मुक्त_coherent(ring->dev->dev->dma_dev, ring_mem_size,
			  ring->descbase, ring->dmabase);
पूर्ण

/* Reset the RX DMA channel */
अटल पूर्णांक b43_dmacontroller_rx_reset(काष्ठा b43_wldev *dev, u16 mmio_base,
				      क्रमागत b43_dmatype type)
अणु
	पूर्णांक i;
	u32 value;
	u16 offset;

	might_sleep();

	offset = (type == B43_DMA_64BIT) ? B43_DMA64_RXCTL : B43_DMA32_RXCTL;
	b43_ग_लिखो32(dev, mmio_base + offset, 0);
	क्रम (i = 0; i < 10; i++) अणु
		offset = (type == B43_DMA_64BIT) ? B43_DMA64_RXSTATUS :
						   B43_DMA32_RXSTATUS;
		value = b43_पढ़ो32(dev, mmio_base + offset);
		अगर (type == B43_DMA_64BIT) अणु
			value &= B43_DMA64_RXSTAT;
			अगर (value == B43_DMA64_RXSTAT_DISABLED) अणु
				i = -1;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			value &= B43_DMA32_RXSTATE;
			अगर (value == B43_DMA32_RXSTAT_DISABLED) अणु
				i = -1;
				अवरोध;
			पूर्ण
		पूर्ण
		msleep(1);
	पूर्ण
	अगर (i != -1) अणु
		b43err(dev->wl, "DMA RX reset timed out\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/* Reset the TX DMA channel */
अटल पूर्णांक b43_dmacontroller_tx_reset(काष्ठा b43_wldev *dev, u16 mmio_base,
				      क्रमागत b43_dmatype type)
अणु
	पूर्णांक i;
	u32 value;
	u16 offset;

	might_sleep();

	क्रम (i = 0; i < 10; i++) अणु
		offset = (type == B43_DMA_64BIT) ? B43_DMA64_TXSTATUS :
						   B43_DMA32_TXSTATUS;
		value = b43_पढ़ो32(dev, mmio_base + offset);
		अगर (type == B43_DMA_64BIT) अणु
			value &= B43_DMA64_TXSTAT;
			अगर (value == B43_DMA64_TXSTAT_DISABLED ||
			    value == B43_DMA64_TXSTAT_IDLEWAIT ||
			    value == B43_DMA64_TXSTAT_STOPPED)
				अवरोध;
		पूर्ण अन्यथा अणु
			value &= B43_DMA32_TXSTATE;
			अगर (value == B43_DMA32_TXSTAT_DISABLED ||
			    value == B43_DMA32_TXSTAT_IDLEWAIT ||
			    value == B43_DMA32_TXSTAT_STOPPED)
				अवरोध;
		पूर्ण
		msleep(1);
	पूर्ण
	offset = (type == B43_DMA_64BIT) ? B43_DMA64_TXCTL : B43_DMA32_TXCTL;
	b43_ग_लिखो32(dev, mmio_base + offset, 0);
	क्रम (i = 0; i < 10; i++) अणु
		offset = (type == B43_DMA_64BIT) ? B43_DMA64_TXSTATUS :
						   B43_DMA32_TXSTATUS;
		value = b43_पढ़ो32(dev, mmio_base + offset);
		अगर (type == B43_DMA_64BIT) अणु
			value &= B43_DMA64_TXSTAT;
			अगर (value == B43_DMA64_TXSTAT_DISABLED) अणु
				i = -1;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			value &= B43_DMA32_TXSTATE;
			अगर (value == B43_DMA32_TXSTAT_DISABLED) अणु
				i = -1;
				अवरोध;
			पूर्ण
		पूर्ण
		msleep(1);
	पूर्ण
	अगर (i != -1) अणु
		b43err(dev->wl, "DMA TX reset timed out\n");
		वापस -ENODEV;
	पूर्ण
	/* ensure the reset is completed. */
	msleep(1);

	वापस 0;
पूर्ण

/* Check अगर a DMA mapping address is invalid. */
अटल bool b43_dma_mapping_error(काष्ठा b43_dmaring *ring,
				  dma_addr_t addr,
				  माप_प्रकार buffersize, bool dma_to_device)
अणु
	अगर (unlikely(dma_mapping_error(ring->dev->dev->dma_dev, addr)))
		वापस true;

	चयन (ring->type) अणु
	हाल B43_DMA_30BIT:
		अगर ((u64)addr + buffersize > (1ULL << 30))
			जाओ address_error;
		अवरोध;
	हाल B43_DMA_32BIT:
		अगर ((u64)addr + buffersize > (1ULL << 32))
			जाओ address_error;
		अवरोध;
	हाल B43_DMA_64BIT:
		/* Currently we can't have addresses beyond
		 * 64bit in the kernel. */
		अवरोध;
	पूर्ण

	/* The address is OK. */
	वापस false;

address_error:
	/* We can't support this address. Unmap it again. */
	unmap_descbuffer(ring, addr, buffersize, dma_to_device);

	वापस true;
पूर्ण

अटल bool b43_rx_buffer_is_poisoned(काष्ठा b43_dmaring *ring, काष्ठा sk_buff *skb)
अणु
	अचिन्हित अक्षर *f = skb->data + ring->frameoffset;

	वापस ((f[0] & f[1] & f[2] & f[3] & f[4] & f[5] & f[6] & f[7]) == 0xFF);
पूर्ण

अटल व्योम b43_poison_rx_buffer(काष्ठा b43_dmaring *ring, काष्ठा sk_buff *skb)
अणु
	काष्ठा b43_rxhdr_fw4 *rxhdr;
	अचिन्हित अक्षर *frame;

	/* This poisons the RX buffer to detect DMA failures. */

	rxhdr = (काष्ठा b43_rxhdr_fw4 *)(skb->data);
	rxhdr->frame_len = 0;

	B43_WARN_ON(ring->rx_buffersize < ring->frameoffset + माप(काष्ठा b43_plcp_hdr6) + 2);
	frame = skb->data + ring->frameoffset;
	स_रखो(frame, 0xFF, माप(काष्ठा b43_plcp_hdr6) + 2 /* padding */);
पूर्ण

अटल पूर्णांक setup_rx_descbuffer(काष्ठा b43_dmaring *ring,
			       काष्ठा b43_dmadesc_generic *desc,
			       काष्ठा b43_dmadesc_meta *meta, gfp_t gfp_flags)
अणु
	dma_addr_t dmaaddr;
	काष्ठा sk_buff *skb;

	B43_WARN_ON(ring->tx);

	skb = __dev_alloc_skb(ring->rx_buffersize, gfp_flags);
	अगर (unlikely(!skb))
		वापस -ENOMEM;
	b43_poison_rx_buffer(ring, skb);
	dmaaddr = map_descbuffer(ring, skb->data, ring->rx_buffersize, 0);
	अगर (b43_dma_mapping_error(ring, dmaaddr, ring->rx_buffersize, 0)) अणु
		/* ugh. try to पुनः_स्मृति in zone_dma */
		gfp_flags |= GFP_DMA;

		dev_kमुक्त_skb_any(skb);

		skb = __dev_alloc_skb(ring->rx_buffersize, gfp_flags);
		अगर (unlikely(!skb))
			वापस -ENOMEM;
		b43_poison_rx_buffer(ring, skb);
		dmaaddr = map_descbuffer(ring, skb->data,
					 ring->rx_buffersize, 0);
		अगर (b43_dma_mapping_error(ring, dmaaddr, ring->rx_buffersize, 0)) अणु
			b43err(ring->dev->wl, "RX DMA buffer allocation failed\n");
			dev_kमुक्त_skb_any(skb);
			वापस -EIO;
		पूर्ण
	पूर्ण

	meta->skb = skb;
	meta->dmaaddr = dmaaddr;
	ring->ops->fill_descriptor(ring, desc, dmaaddr,
				   ring->rx_buffersize, 0, 0, 0);

	वापस 0;
पूर्ण

/* Allocate the initial descbuffers.
 * This is used क्रम an RX ring only.
 */
अटल पूर्णांक alloc_initial_descbuffers(काष्ठा b43_dmaring *ring)
अणु
	पूर्णांक i, err = -ENOMEM;
	काष्ठा b43_dmadesc_generic *desc;
	काष्ठा b43_dmadesc_meta *meta;

	क्रम (i = 0; i < ring->nr_slots; i++) अणु
		desc = ring->ops->idx2desc(ring, i, &meta);

		err = setup_rx_descbuffer(ring, desc, meta, GFP_KERNEL);
		अगर (err) अणु
			b43err(ring->dev->wl,
			       "Failed to allocate initial descbuffers\n");
			जाओ err_unwind;
		पूर्ण
	पूर्ण
	mb();
	ring->used_slots = ring->nr_slots;
	err = 0;
      out:
	वापस err;

      err_unwind:
	क्रम (i--; i >= 0; i--) अणु
		desc = ring->ops->idx2desc(ring, i, &meta);

		unmap_descbuffer(ring, meta->dmaaddr, ring->rx_buffersize, 0);
		dev_kमुक्त_skb(meta->skb);
	पूर्ण
	जाओ out;
पूर्ण

/* Do initial setup of the DMA controller.
 * Reset the controller, ग_लिखो the ring busaddress
 * and चयन the "enable" bit on.
 */
अटल पूर्णांक dmacontroller_setup(काष्ठा b43_dmaring *ring)
अणु
	पूर्णांक err = 0;
	u32 value;
	u32 addrext;
	bool parity = ring->dev->dma.parity;
	u32 addrlo;
	u32 addrhi;

	अगर (ring->tx) अणु
		अगर (ring->type == B43_DMA_64BIT) अणु
			u64 ringbase = (u64) (ring->dmabase);
			addrext = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_EXT);
			addrlo = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_LOW);
			addrhi = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_HIGH);

			value = B43_DMA64_TXENABLE;
			value |= (addrext << B43_DMA64_TXADDREXT_SHIFT)
			    & B43_DMA64_TXADDREXT_MASK;
			अगर (!parity)
				value |= B43_DMA64_TXPARITYDISABLE;
			b43_dma_ग_लिखो(ring, B43_DMA64_TXCTL, value);
			b43_dma_ग_लिखो(ring, B43_DMA64_TXRINGLO, addrlo);
			b43_dma_ग_लिखो(ring, B43_DMA64_TXRINGHI, addrhi);
		पूर्ण अन्यथा अणु
			u32 ringbase = (u32) (ring->dmabase);
			addrext = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_EXT);
			addrlo = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_LOW);

			value = B43_DMA32_TXENABLE;
			value |= (addrext << B43_DMA32_TXADDREXT_SHIFT)
			    & B43_DMA32_TXADDREXT_MASK;
			अगर (!parity)
				value |= B43_DMA32_TXPARITYDISABLE;
			b43_dma_ग_लिखो(ring, B43_DMA32_TXCTL, value);
			b43_dma_ग_लिखो(ring, B43_DMA32_TXRING, addrlo);
		पूर्ण
	पूर्ण अन्यथा अणु
		err = alloc_initial_descbuffers(ring);
		अगर (err)
			जाओ out;
		अगर (ring->type == B43_DMA_64BIT) अणु
			u64 ringbase = (u64) (ring->dmabase);
			addrext = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_EXT);
			addrlo = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_LOW);
			addrhi = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_HIGH);

			value = (ring->frameoffset << B43_DMA64_RXFROFF_SHIFT);
			value |= B43_DMA64_RXENABLE;
			value |= (addrext << B43_DMA64_RXADDREXT_SHIFT)
			    & B43_DMA64_RXADDREXT_MASK;
			अगर (!parity)
				value |= B43_DMA64_RXPARITYDISABLE;
			b43_dma_ग_लिखो(ring, B43_DMA64_RXCTL, value);
			b43_dma_ग_लिखो(ring, B43_DMA64_RXRINGLO, addrlo);
			b43_dma_ग_लिखो(ring, B43_DMA64_RXRINGHI, addrhi);
			b43_dma_ग_लिखो(ring, B43_DMA64_RXINDEX, ring->nr_slots *
				      माप(काष्ठा b43_dmadesc64));
		पूर्ण अन्यथा अणु
			u32 ringbase = (u32) (ring->dmabase);
			addrext = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_EXT);
			addrlo = b43_dma_address(&ring->dev->dma, ringbase, B43_DMA_ADDR_LOW);

			value = (ring->frameoffset << B43_DMA32_RXFROFF_SHIFT);
			value |= B43_DMA32_RXENABLE;
			value |= (addrext << B43_DMA32_RXADDREXT_SHIFT)
			    & B43_DMA32_RXADDREXT_MASK;
			अगर (!parity)
				value |= B43_DMA32_RXPARITYDISABLE;
			b43_dma_ग_लिखो(ring, B43_DMA32_RXCTL, value);
			b43_dma_ग_लिखो(ring, B43_DMA32_RXRING, addrlo);
			b43_dma_ग_लिखो(ring, B43_DMA32_RXINDEX, ring->nr_slots *
				      माप(काष्ठा b43_dmadesc32));
		पूर्ण
	पूर्ण

out:
	वापस err;
पूर्ण

/* Shutकरोwn the DMA controller. */
अटल व्योम dmacontroller_cleanup(काष्ठा b43_dmaring *ring)
अणु
	अगर (ring->tx) अणु
		b43_dmacontroller_tx_reset(ring->dev, ring->mmio_base,
					   ring->type);
		अगर (ring->type == B43_DMA_64BIT) अणु
			b43_dma_ग_लिखो(ring, B43_DMA64_TXRINGLO, 0);
			b43_dma_ग_लिखो(ring, B43_DMA64_TXRINGHI, 0);
		पूर्ण अन्यथा
			b43_dma_ग_लिखो(ring, B43_DMA32_TXRING, 0);
	पूर्ण अन्यथा अणु
		b43_dmacontroller_rx_reset(ring->dev, ring->mmio_base,
					   ring->type);
		अगर (ring->type == B43_DMA_64BIT) अणु
			b43_dma_ग_लिखो(ring, B43_DMA64_RXRINGLO, 0);
			b43_dma_ग_लिखो(ring, B43_DMA64_RXRINGHI, 0);
		पूर्ण अन्यथा
			b43_dma_ग_लिखो(ring, B43_DMA32_RXRING, 0);
	पूर्ण
पूर्ण

अटल व्योम मुक्त_all_descbuffers(काष्ठा b43_dmaring *ring)
अणु
	काष्ठा b43_dmadesc_meta *meta;
	पूर्णांक i;

	अगर (!ring->used_slots)
		वापस;
	क्रम (i = 0; i < ring->nr_slots; i++) अणु
		/* get meta - ignore वापसed value */
		ring->ops->idx2desc(ring, i, &meta);

		अगर (!meta->skb || b43_dma_ptr_is_poisoned(meta->skb)) अणु
			B43_WARN_ON(!ring->tx);
			जारी;
		पूर्ण
		अगर (ring->tx) अणु
			unmap_descbuffer(ring, meta->dmaaddr,
					 meta->skb->len, 1);
		पूर्ण अन्यथा अणु
			unmap_descbuffer(ring, meta->dmaaddr,
					 ring->rx_buffersize, 0);
		पूर्ण
		मुक्त_descriptor_buffer(ring, meta);
	पूर्ण
पूर्ण

अटल क्रमागत b43_dmatype b43_engine_type(काष्ठा b43_wldev *dev)
अणु
	u32 पंचांगp;
	u16 mmio_base;

	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		पंचांगp = bcma_aपढ़ो32(dev->dev->bdev, BCMA_IOST);
		अगर (पंचांगp & BCMA_IOST_DMA64)
			वापस B43_DMA_64BIT;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		पंचांगp = ssb_पढ़ो32(dev->dev->sdev, SSB_TMSHIGH);
		अगर (पंचांगp & SSB_TMSHIGH_DMA64)
			वापस B43_DMA_64BIT;
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	mmio_base = b43_dmacontroller_base(0, 0);
	b43_ग_लिखो32(dev, mmio_base + B43_DMA32_TXCTL, B43_DMA32_TXADDREXT_MASK);
	पंचांगp = b43_पढ़ो32(dev, mmio_base + B43_DMA32_TXCTL);
	अगर (पंचांगp & B43_DMA32_TXADDREXT_MASK)
		वापस B43_DMA_32BIT;
	वापस B43_DMA_30BIT;
पूर्ण

/* Main initialization function. */
अटल
काष्ठा b43_dmaring *b43_setup_dmaring(काष्ठा b43_wldev *dev,
				      पूर्णांक controller_index,
				      पूर्णांक क्रम_tx,
				      क्रमागत b43_dmatype type)
अणु
	काष्ठा b43_dmaring *ring;
	पूर्णांक i, err;
	dma_addr_t dma_test;

	ring = kzalloc(माप(*ring), GFP_KERNEL);
	अगर (!ring)
		जाओ out;

	ring->nr_slots = B43_RXRING_SLOTS;
	अगर (क्रम_tx)
		ring->nr_slots = B43_TXRING_SLOTS;

	ring->meta = kसुस्मृति(ring->nr_slots, माप(काष्ठा b43_dmadesc_meta),
			     GFP_KERNEL);
	अगर (!ring->meta)
		जाओ err_kमुक्त_ring;
	क्रम (i = 0; i < ring->nr_slots; i++)
		ring->meta->skb = B43_DMA_PTR_POISON;

	ring->type = type;
	ring->dev = dev;
	ring->mmio_base = b43_dmacontroller_base(type, controller_index);
	ring->index = controller_index;
	अगर (type == B43_DMA_64BIT)
		ring->ops = &dma64_ops;
	अन्यथा
		ring->ops = &dma32_ops;
	अगर (क्रम_tx) अणु
		ring->tx = true;
		ring->current_slot = -1;
	पूर्ण अन्यथा अणु
		अगर (ring->index == 0) अणु
			चयन (dev->fw.hdr_क्रमmat) अणु
			हाल B43_FW_HDR_598:
				ring->rx_buffersize = B43_DMA0_RX_FW598_बफ_मानE;
				ring->frameoffset = B43_DMA0_RX_FW598_FO;
				अवरोध;
			हाल B43_FW_HDR_410:
			हाल B43_FW_HDR_351:
				ring->rx_buffersize = B43_DMA0_RX_FW351_बफ_मानE;
				ring->frameoffset = B43_DMA0_RX_FW351_FO;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा
			B43_WARN_ON(1);
	पूर्ण
#अगर_घोषित CONFIG_B43_DEBUG
	ring->last_injected_overflow = jअगरfies;
#पूर्ण_अगर

	अगर (क्रम_tx) अणु
		/* Assumption: B43_TXRING_SLOTS can be भागided by TX_SLOTS_PER_FRAME */
		BUILD_BUG_ON(B43_TXRING_SLOTS % TX_SLOTS_PER_FRAME != 0);

		ring->txhdr_cache = kसुस्मृति(ring->nr_slots / TX_SLOTS_PER_FRAME,
					    b43_txhdr_size(dev),
					    GFP_KERNEL);
		अगर (!ring->txhdr_cache)
			जाओ err_kमुक्त_meta;

		/* test क्रम ability to dma to txhdr_cache */
		dma_test = dma_map_single(dev->dev->dma_dev,
					  ring->txhdr_cache,
					  b43_txhdr_size(dev),
					  DMA_TO_DEVICE);

		अगर (b43_dma_mapping_error(ring, dma_test,
					  b43_txhdr_size(dev), 1)) अणु
			/* ugh पुनः_स्मृति */
			kमुक्त(ring->txhdr_cache);
			ring->txhdr_cache = kसुस्मृति(ring->nr_slots / TX_SLOTS_PER_FRAME,
						    b43_txhdr_size(dev),
						    GFP_KERNEL | GFP_DMA);
			अगर (!ring->txhdr_cache)
				जाओ err_kमुक्त_meta;

			dma_test = dma_map_single(dev->dev->dma_dev,
						  ring->txhdr_cache,
						  b43_txhdr_size(dev),
						  DMA_TO_DEVICE);

			अगर (b43_dma_mapping_error(ring, dma_test,
						  b43_txhdr_size(dev), 1)) अणु

				b43err(dev->wl,
				       "TXHDR DMA allocation failed\n");
				जाओ err_kमुक्त_txhdr_cache;
			पूर्ण
		पूर्ण

		dma_unmap_single(dev->dev->dma_dev,
				 dma_test, b43_txhdr_size(dev),
				 DMA_TO_DEVICE);
	पूर्ण

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

#घोषणा भागide(a, b)	(अणु	\
	typeof(a) __a = a;	\
	करो_भाग(__a, b);		\
	__a;			\
  पूर्ण)

#घोषणा modulo(a, b)	(अणु	\
	typeof(a) __a = a;	\
	करो_भाग(__a, b);		\
  पूर्ण)

/* Main cleanup function. */
अटल व्योम b43_destroy_dmaring(काष्ठा b43_dmaring *ring,
				स्थिर अक्षर *ringname)
अणु
	अगर (!ring)
		वापस;

#अगर_घोषित CONFIG_B43_DEBUG
	अणु
		/* Prपूर्णांक some statistics. */
		u64 failed_packets = ring->nr_failed_tx_packets;
		u64 succeed_packets = ring->nr_succeed_tx_packets;
		u64 nr_packets = failed_packets + succeed_packets;
		u64 permille_failed = 0, average_tries = 0;

		अगर (nr_packets)
			permille_failed = भागide(failed_packets * 1000, nr_packets);
		अगर (nr_packets)
			average_tries = भागide(ring->nr_total_packet_tries * 100, nr_packets);

		b43dbg(ring->dev->wl, "DMA-%u %s: "
		       "Used slots %d/%d, Failed frames %llu/%llu = %llu.%01llu%%, "
		       "Average tries %llu.%02llu\n",
		       (अचिन्हित पूर्णांक)(ring->type), ringname,
		       ring->max_used_slots,
		       ring->nr_slots,
		       (अचिन्हित दीर्घ दीर्घ)failed_packets,
		       (अचिन्हित दीर्घ दीर्घ)nr_packets,
		       (अचिन्हित दीर्घ दीर्घ)भागide(permille_failed, 10),
		       (अचिन्हित दीर्घ दीर्घ)modulo(permille_failed, 10),
		       (अचिन्हित दीर्घ दीर्घ)भागide(average_tries, 100),
		       (अचिन्हित दीर्घ दीर्घ)modulo(average_tries, 100));
	पूर्ण
#पूर्ण_अगर /* DEBUG */

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

#घोषणा destroy_ring(dma, ring) करो अणु				\
	b43_destroy_dmaring((dma)->ring, __stringअगरy(ring));	\
	(dma)->ring = शून्य;					\
    पूर्ण जबतक (0)

व्योम b43_dma_मुक्त(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_dma *dma;

	अगर (b43_using_pio_transfers(dev))
		वापस;
	dma = &dev->dma;

	destroy_ring(dma, rx_ring);
	destroy_ring(dma, tx_ring_AC_BK);
	destroy_ring(dma, tx_ring_AC_BE);
	destroy_ring(dma, tx_ring_AC_VI);
	destroy_ring(dma, tx_ring_AC_VO);
	destroy_ring(dma, tx_ring_mcast);
पूर्ण

/* Some hardware with 64-bit DMA seems to be bugged and looks क्रम translation
 * bit in low address word instead of high one.
 */
अटल bool b43_dma_translation_in_low_word(काष्ठा b43_wldev *dev,
					    क्रमागत b43_dmatype type)
अणु
	अगर (type != B43_DMA_64BIT)
		वापस true;

#अगर_घोषित CONFIG_B43_SSB
	अगर (dev->dev->bus_type == B43_BUS_SSB &&
	    dev->dev->sdev->bus->bustype == SSB_BUSTYPE_PCI &&
	    !(pci_is_pcie(dev->dev->sdev->bus->host_pci) &&
	      ssb_पढ़ो32(dev->dev->sdev, SSB_TMSHIGH) & SSB_TMSHIGH_DMA64))
			वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

पूर्णांक b43_dma_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_dma *dma = &dev->dma;
	क्रमागत b43_dmatype type = b43_engine_type(dev);
	पूर्णांक err;

	err = dma_set_mask_and_coherent(dev->dev->dma_dev, DMA_BIT_MASK(type));
	अगर (err) अणु
		b43err(dev->wl, "The machine/kernel does not support "
		       "the required %u-bit DMA mask\n", type);
		वापस err;
	पूर्ण

	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		dma->translation = bcma_core_dma_translation(dev->dev->bdev);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		dma->translation = ssb_dma_translation(dev->dev->sdev);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
	dma->translation_in_low = b43_dma_translation_in_low_word(dev, type);

	dma->parity = true;
#अगर_घोषित CONFIG_B43_BCMA
	/* TODO: find out which SSB devices need disabling parity */
	अगर (dev->dev->bus_type == B43_BUS_BCMA)
		dma->parity = false;
#पूर्ण_अगर

	err = -ENOMEM;
	/* setup TX DMA channels. */
	dma->tx_ring_AC_BK = b43_setup_dmaring(dev, 0, 1, type);
	अगर (!dma->tx_ring_AC_BK)
		जाओ out;

	dma->tx_ring_AC_BE = b43_setup_dmaring(dev, 1, 1, type);
	अगर (!dma->tx_ring_AC_BE)
		जाओ err_destroy_bk;

	dma->tx_ring_AC_VI = b43_setup_dmaring(dev, 2, 1, type);
	अगर (!dma->tx_ring_AC_VI)
		जाओ err_destroy_be;

	dma->tx_ring_AC_VO = b43_setup_dmaring(dev, 3, 1, type);
	अगर (!dma->tx_ring_AC_VO)
		जाओ err_destroy_vi;

	dma->tx_ring_mcast = b43_setup_dmaring(dev, 4, 1, type);
	अगर (!dma->tx_ring_mcast)
		जाओ err_destroy_vo;

	/* setup RX DMA channel. */
	dma->rx_ring = b43_setup_dmaring(dev, 0, 0, type);
	अगर (!dma->rx_ring)
		जाओ err_destroy_mcast;

	/* No support क्रम the TX status DMA ring. */
	B43_WARN_ON(dev->dev->core_rev < 5);

	b43dbg(dev->wl, "%u-bit DMA initialized\n",
	       (अचिन्हित पूर्णांक)type);
	err = 0;
out:
	वापस err;

err_destroy_mcast:
	destroy_ring(dma, tx_ring_mcast);
err_destroy_vo:
	destroy_ring(dma, tx_ring_AC_VO);
err_destroy_vi:
	destroy_ring(dma, tx_ring_AC_VI);
err_destroy_be:
	destroy_ring(dma, tx_ring_AC_BE);
err_destroy_bk:
	destroy_ring(dma, tx_ring_AC_BK);
	वापस err;
पूर्ण

/* Generate a cookie क्रम the TX header. */
अटल u16 generate_cookie(काष्ठा b43_dmaring *ring, पूर्णांक slot)
अणु
	u16 cookie;

	/* Use the upper 4 bits of the cookie as
	 * DMA controller ID and store the slot number
	 * in the lower 12 bits.
	 * Note that the cookie must never be 0, as this
	 * is a special value used in RX path.
	 * It can also not be 0xFFFF because that is special
	 * क्रम multicast frames.
	 */
	cookie = (((u16)ring->index + 1) << 12);
	B43_WARN_ON(slot & ~0x0FFF);
	cookie |= (u16)slot;

	वापस cookie;
पूर्ण

/* Inspect a cookie and find out to which controller/slot it beदीर्घs. */
अटल
काष्ठा b43_dmaring *parse_cookie(काष्ठा b43_wldev *dev, u16 cookie, पूर्णांक *slot)
अणु
	काष्ठा b43_dma *dma = &dev->dma;
	काष्ठा b43_dmaring *ring = शून्य;

	चयन (cookie & 0xF000) अणु
	हाल 0x1000:
		ring = dma->tx_ring_AC_BK;
		अवरोध;
	हाल 0x2000:
		ring = dma->tx_ring_AC_BE;
		अवरोध;
	हाल 0x3000:
		ring = dma->tx_ring_AC_VI;
		अवरोध;
	हाल 0x4000:
		ring = dma->tx_ring_AC_VO;
		अवरोध;
	हाल 0x5000:
		ring = dma->tx_ring_mcast;
		अवरोध;
	पूर्ण
	*slot = (cookie & 0x0FFF);
	अगर (unlikely(!ring || *slot < 0 || *slot >= ring->nr_slots)) अणु
		b43dbg(dev->wl, "TX-status contains "
		       "invalid cookie: 0x%04X\n", cookie);
		वापस शून्य;
	पूर्ण

	वापस ring;
पूर्ण

अटल पूर्णांक dma_tx_fragment(काष्ठा b43_dmaring *ring,
			   काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा b43_dma_ops *ops = ring->ops;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा b43_निजी_tx_info *priv_info = b43_get_priv_tx_info(info);
	u8 *header;
	पूर्णांक slot, old_top_slot, old_used_slots;
	पूर्णांक err;
	काष्ठा b43_dmadesc_generic *desc;
	काष्ठा b43_dmadesc_meta *meta;
	काष्ठा b43_dmadesc_meta *meta_hdr;
	u16 cookie;
	माप_प्रकार hdrsize = b43_txhdr_size(ring->dev);

	/* Important note: If the number of used DMA slots per TX frame
	 * is changed here, the TX_SLOTS_PER_FRAME definition at the top of
	 * the file has to be updated, too!
	 */

	old_top_slot = ring->current_slot;
	old_used_slots = ring->used_slots;

	/* Get a slot क्रम the header. */
	slot = request_slot(ring);
	desc = ops->idx2desc(ring, slot, &meta_hdr);
	स_रखो(meta_hdr, 0, माप(*meta_hdr));

	header = &(ring->txhdr_cache[(slot / TX_SLOTS_PER_FRAME) * hdrsize]);
	cookie = generate_cookie(ring, slot);
	err = b43_generate_txhdr(ring->dev, header,
				 skb, info, cookie);
	अगर (unlikely(err)) अणु
		ring->current_slot = old_top_slot;
		ring->used_slots = old_used_slots;
		वापस err;
	पूर्ण

	meta_hdr->dmaaddr = map_descbuffer(ring, (अचिन्हित अक्षर *)header,
					   hdrsize, 1);
	अगर (b43_dma_mapping_error(ring, meta_hdr->dmaaddr, hdrsize, 1)) अणु
		ring->current_slot = old_top_slot;
		ring->used_slots = old_used_slots;
		वापस -EIO;
	पूर्ण
	ops->fill_descriptor(ring, desc, meta_hdr->dmaaddr,
			     hdrsize, 1, 0, 0);

	/* Get a slot क्रम the payload. */
	slot = request_slot(ring);
	desc = ops->idx2desc(ring, slot, &meta);
	स_रखो(meta, 0, माप(*meta));

	meta->skb = skb;
	meta->is_last_fragment = true;
	priv_info->bouncebuffer = शून्य;

	meta->dmaaddr = map_descbuffer(ring, skb->data, skb->len, 1);
	/* create a bounce buffer in zone_dma on mapping failure. */
	अगर (b43_dma_mapping_error(ring, meta->dmaaddr, skb->len, 1)) अणु
		priv_info->bouncebuffer = kmemdup(skb->data, skb->len,
						  GFP_ATOMIC | GFP_DMA);
		अगर (!priv_info->bouncebuffer) अणु
			ring->current_slot = old_top_slot;
			ring->used_slots = old_used_slots;
			err = -ENOMEM;
			जाओ out_unmap_hdr;
		पूर्ण

		meta->dmaaddr = map_descbuffer(ring, priv_info->bouncebuffer, skb->len, 1);
		अगर (b43_dma_mapping_error(ring, meta->dmaaddr, skb->len, 1)) अणु
			kमुक्त(priv_info->bouncebuffer);
			priv_info->bouncebuffer = शून्य;
			ring->current_slot = old_top_slot;
			ring->used_slots = old_used_slots;
			err = -EIO;
			जाओ out_unmap_hdr;
		पूर्ण
	पूर्ण

	ops->fill_descriptor(ring, desc, meta->dmaaddr, skb->len, 0, 1, 1);

	अगर (info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM) अणु
		/* Tell the firmware about the cookie of the last
		 * mcast frame, so it can clear the more-data bit in it. */
		b43_shm_ग_लिखो16(ring->dev, B43_SHM_SHARED,
				B43_SHM_SH_MCASTCOOKIE, cookie);
	पूर्ण
	/* Now transfer the whole frame. */
	wmb();
	ops->poke_tx(ring, next_slot(ring, slot));
	वापस 0;

out_unmap_hdr:
	unmap_descbuffer(ring, meta_hdr->dmaaddr,
			 hdrsize, 1);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक should_inject_overflow(काष्ठा b43_dmaring *ring)
अणु
#अगर_घोषित CONFIG_B43_DEBUG
	अगर (unlikely(b43_debug(ring->dev, B43_DBG_DMAOVERFLOW))) अणु
		/* Check अगर we should inject another ringbuffer overflow
		 * to test handling of this situation in the stack. */
		अचिन्हित दीर्घ next_overflow;

		next_overflow = ring->last_injected_overflow + HZ;
		अगर (समय_after(jअगरfies, next_overflow)) अणु
			ring->last_injected_overflow = jअगरfies;
			b43dbg(ring->dev->wl,
			       "Injecting TX ring overflow on "
			       "DMA controller %d\n", ring->index);
			वापस 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_B43_DEBUG */
	वापस 0;
पूर्ण

/* Static mapping of mac80211's queues (priorities) to b43 DMA rings. */
अटल काष्ठा b43_dmaring *select_ring_by_priority(काष्ठा b43_wldev *dev,
						   u8 queue_prio)
अणु
	काष्ठा b43_dmaring *ring;

	अगर (dev->qos_enabled) अणु
		/* 0 = highest priority */
		चयन (queue_prio) अणु
		शेष:
			B43_WARN_ON(1);
			fallthrough;
		हाल 0:
			ring = dev->dma.tx_ring_AC_VO;
			अवरोध;
		हाल 1:
			ring = dev->dma.tx_ring_AC_VI;
			अवरोध;
		हाल 2:
			ring = dev->dma.tx_ring_AC_BE;
			अवरोध;
		हाल 3:
			ring = dev->dma.tx_ring_AC_BK;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		ring = dev->dma.tx_ring_AC_BE;

	वापस ring;
पूर्ण

पूर्णांक b43_dma_tx(काष्ठा b43_wldev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा b43_dmaring *ring;
	काष्ठा ieee80211_hdr *hdr;
	पूर्णांक err = 0;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	अगर (info->flags & IEEE80211_TX_CTL_SEND_AFTER_DTIM) अणु
		/* The multicast ring will be sent after the DTIM */
		ring = dev->dma.tx_ring_mcast;
		/* Set the more-data bit. Ucode will clear it on
		 * the last frame क्रम us. */
		hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_MOREDATA);
	पूर्ण अन्यथा अणु
		/* Decide by priority where to put this frame. */
		ring = select_ring_by_priority(
			dev, skb_get_queue_mapping(skb));
	पूर्ण

	B43_WARN_ON(!ring->tx);

	अगर (unlikely(ring->stopped)) अणु
		/* We get here only because of a bug in mac80211.
		 * Because of a race, one packet may be queued after
		 * the queue is stopped, thus we got called when we shouldn't.
		 * For now, just refuse the transmit. */
		अगर (b43_debug(dev, B43_DBG_DMAVERBOSE))
			b43err(dev->wl, "Packet after queue stopped\n");
		err = -ENOSPC;
		जाओ out;
	पूर्ण

	अगर (WARN_ON(मुक्त_slots(ring) < TX_SLOTS_PER_FRAME)) अणु
		/* If we get here, we have a real error with the queue
		 * full, but queues not stopped. */
		b43err(dev->wl, "DMA queue overflow\n");
		err = -ENOSPC;
		जाओ out;
	पूर्ण

	/* Assign the queue number to the ring (अगर not alपढ़ोy करोne beक्रमe)
	 * so TX status handling can use it. The queue to ring mapping is
	 * अटल, so we करोn't need to store it per frame. */
	ring->queue_prio = skb_get_queue_mapping(skb);

	err = dma_tx_fragment(ring, skb);
	अगर (unlikely(err == -ENOKEY)) अणु
		/* Drop this packet, as we करोn't have the encryption key
		 * anymore and must not transmit it unencrypted. */
		ieee80211_मुक्त_txskb(dev->wl->hw, skb);
		err = 0;
		जाओ out;
	पूर्ण
	अगर (unlikely(err)) अणु
		b43err(dev->wl, "DMA tx mapping failure\n");
		जाओ out;
	पूर्ण
	अगर ((मुक्त_slots(ring) < TX_SLOTS_PER_FRAME) ||
	    should_inject_overflow(ring)) अणु
		/* This TX ring is full. */
		अचिन्हित पूर्णांक skb_mapping = skb_get_queue_mapping(skb);
		ieee80211_stop_queue(dev->wl->hw, skb_mapping);
		dev->wl->tx_queue_stopped[skb_mapping] = true;
		ring->stopped = true;
		अगर (b43_debug(dev, B43_DBG_DMAVERBOSE)) अणु
			b43dbg(dev->wl, "Stopped TX ring %d\n", ring->index);
		पूर्ण
	पूर्ण
out:

	वापस err;
पूर्ण

व्योम b43_dma_handle_txstatus(काष्ठा b43_wldev *dev,
			     स्थिर काष्ठा b43_txstatus *status)
अणु
	स्थिर काष्ठा b43_dma_ops *ops;
	काष्ठा b43_dmaring *ring;
	काष्ठा b43_dmadesc_meta *meta;
	अटल स्थिर काष्ठा b43_txstatus fake; /* filled with 0 */
	स्थिर काष्ठा b43_txstatus *txstat;
	पूर्णांक slot, firstused;
	bool frame_succeed;
	पूर्णांक skip;
	अटल u8 err_out1;

	ring = parse_cookie(dev, status->cookie, &slot);
	अगर (unlikely(!ring))
		वापस;
	B43_WARN_ON(!ring->tx);

	/* Sanity check: TX packets are processed in-order on one ring.
	 * Check अगर the slot deduced from the cookie really is the first
	 * used slot. */
	firstused = ring->current_slot - ring->used_slots + 1;
	अगर (firstused < 0)
		firstused = ring->nr_slots + firstused;

	skip = 0;
	अगर (unlikely(slot != firstused)) अणु
		/* This possibly is a firmware bug and will result in
		 * malfunction, memory leaks and/or stall of DMA functionality.
		 */
		अगर (slot == next_slot(ring, next_slot(ring, firstused))) अणु
			/* If a single header/data pair was missed, skip over
			 * the first two slots in an attempt to recover.
			 */
			slot = firstused;
			skip = 2;
			अगर (!err_out1) अणु
				/* Report the error once. */
				b43dbg(dev->wl,
				       "Skip on DMA ring %d slot %d.\n",
				       ring->index, slot);
				err_out1 = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* More than a single header/data pair were missed.
			 * Report this error. If running with खोलो-source
			 * firmware, then reset the controller to
			 * revive operation.
			 */
			b43dbg(dev->wl,
			       "Out of order TX status report on DMA ring %d. Expected %d, but got %d\n",
			       ring->index, firstused, slot);
			अगर (dev->fw.खोलोsource)
				b43_controller_restart(dev, "Out of order TX");
			वापस;
		पूर्ण
	पूर्ण

	ops = ring->ops;
	जबतक (1) अणु
		B43_WARN_ON(slot < 0 || slot >= ring->nr_slots);
		/* get meta - ignore वापसed value */
		ops->idx2desc(ring, slot, &meta);

		अगर (b43_dma_ptr_is_poisoned(meta->skb)) अणु
			b43dbg(dev->wl, "Poisoned TX slot %d (first=%d) "
			       "on ring %d\n",
			       slot, firstused, ring->index);
			अवरोध;
		पूर्ण

		अगर (meta->skb) अणु
			काष्ठा b43_निजी_tx_info *priv_info =
			     b43_get_priv_tx_info(IEEE80211_SKB_CB(meta->skb));

			unmap_descbuffer(ring, meta->dmaaddr,
					 meta->skb->len, 1);
			kमुक्त(priv_info->bouncebuffer);
			priv_info->bouncebuffer = शून्य;
		पूर्ण अन्यथा अणु
			unmap_descbuffer(ring, meta->dmaaddr,
					 b43_txhdr_size(dev), 1);
		पूर्ण

		अगर (meta->is_last_fragment) अणु
			काष्ठा ieee80211_tx_info *info;

			अगर (unlikely(!meta->skb)) अणु
				/* This is a scatter-gather fragment of a frame,
				 * so the skb poपूर्णांकer must not be शून्य.
				 */
				b43dbg(dev->wl, "TX status unexpected NULL skb "
				       "at slot %d (first=%d) on ring %d\n",
				       slot, firstused, ring->index);
				अवरोध;
			पूर्ण

			info = IEEE80211_SKB_CB(meta->skb);

			/*
			 * Call back to inक्रमm the ieee80211 subप्रणाली about
			 * the status of the transmission. When skipping over
			 * a missed TX status report, use a status काष्ठाure
			 * filled with zeros to indicate that the frame was not
			 * sent (frame_count 0) and not acknowledged
			 */
			अगर (unlikely(skip))
				txstat = &fake;
			अन्यथा
				txstat = status;

			frame_succeed = b43_fill_txstatus_report(dev, info,
								 txstat);
#अगर_घोषित CONFIG_B43_DEBUG
			अगर (frame_succeed)
				ring->nr_succeed_tx_packets++;
			अन्यथा
				ring->nr_failed_tx_packets++;
			ring->nr_total_packet_tries += status->frame_count;
#पूर्ण_अगर /* DEBUG */
			ieee80211_tx_status(dev->wl->hw, meta->skb);

			/* skb will be मुक्तd by ieee80211_tx_status().
			 * Poison our poपूर्णांकer. */
			meta->skb = B43_DMA_PTR_POISON;
		पूर्ण अन्यथा अणु
			/* No need to call मुक्त_descriptor_buffer here, as
			 * this is only the txhdr, which is not allocated.
			 */
			अगर (unlikely(meta->skb)) अणु
				b43dbg(dev->wl, "TX status unexpected non-NULL skb "
				       "at slot %d (first=%d) on ring %d\n",
				       slot, firstused, ring->index);
				अवरोध;
			पूर्ण
		पूर्ण

		/* Everything unmapped and मुक्त'd. So it's not used anymore. */
		ring->used_slots--;

		अगर (meta->is_last_fragment && !skip) अणु
			/* This is the last scatter-gather
			 * fragment of the frame. We are करोne. */
			अवरोध;
		पूर्ण
		slot = next_slot(ring, slot);
		अगर (skip > 0)
			--skip;
	पूर्ण
	अगर (ring->stopped) अणु
		B43_WARN_ON(मुक्त_slots(ring) < TX_SLOTS_PER_FRAME);
		ring->stopped = false;
	पूर्ण

	अगर (dev->wl->tx_queue_stopped[ring->queue_prio]) अणु
		dev->wl->tx_queue_stopped[ring->queue_prio] = false;
	पूर्ण अन्यथा अणु
		/* If the driver queue is running wake the corresponding
		 * mac80211 queue. */
		ieee80211_wake_queue(dev->wl->hw, ring->queue_prio);
		अगर (b43_debug(dev, B43_DBG_DMAVERBOSE)) अणु
			b43dbg(dev->wl, "Woke up TX ring %d\n", ring->index);
		पूर्ण
	पूर्ण
	/* Add work to the queue. */
	ieee80211_queue_work(dev->wl->hw, &dev->wl->tx_work);
पूर्ण

अटल व्योम dma_rx(काष्ठा b43_dmaring *ring, पूर्णांक *slot)
अणु
	स्थिर काष्ठा b43_dma_ops *ops = ring->ops;
	काष्ठा b43_dmadesc_generic *desc;
	काष्ठा b43_dmadesc_meta *meta;
	काष्ठा b43_rxhdr_fw4 *rxhdr;
	काष्ठा sk_buff *skb;
	u16 len;
	पूर्णांक err;
	dma_addr_t dmaaddr;

	desc = ops->idx2desc(ring, *slot, &meta);

	sync_descbuffer_क्रम_cpu(ring, meta->dmaaddr, ring->rx_buffersize);
	skb = meta->skb;

	rxhdr = (काष्ठा b43_rxhdr_fw4 *)skb->data;
	len = le16_to_cpu(rxhdr->frame_len);
	अगर (len == 0) अणु
		पूर्णांक i = 0;

		करो अणु
			udelay(2);
			barrier();
			len = le16_to_cpu(rxhdr->frame_len);
		पूर्ण जबतक (len == 0 && i++ < 5);
		अगर (unlikely(len == 0)) अणु
			dmaaddr = meta->dmaaddr;
			जाओ drop_recycle_buffer;
		पूर्ण
	पूर्ण
	अगर (unlikely(b43_rx_buffer_is_poisoned(ring, skb))) अणु
		/* Something went wrong with the DMA.
		 * The device did not touch the buffer and did not overग_लिखो the poison. */
		b43dbg(ring->dev->wl, "DMA RX: Dropping poisoned buffer.\n");
		dmaaddr = meta->dmaaddr;
		जाओ drop_recycle_buffer;
	पूर्ण
	अगर (unlikely(len + ring->frameoffset > ring->rx_buffersize)) अणु
		/* The data did not fit पूर्णांकo one descriptor buffer
		 * and is split over multiple buffers.
		 * This should never happen, as we try to allocate buffers
		 * big enough. So simply ignore this packet.
		 */
		पूर्णांक cnt = 0;
		s32 पंचांगp = len;

		जबतक (1) अणु
			desc = ops->idx2desc(ring, *slot, &meta);
			/* recycle the descriptor buffer. */
			b43_poison_rx_buffer(ring, meta->skb);
			sync_descbuffer_क्रम_device(ring, meta->dmaaddr,
						   ring->rx_buffersize);
			*slot = next_slot(ring, *slot);
			cnt++;
			पंचांगp -= ring->rx_buffersize;
			अगर (पंचांगp <= 0)
				अवरोध;
		पूर्ण
		b43err(ring->dev->wl, "DMA RX buffer too small "
		       "(len: %u, buffer: %u, nr-dropped: %d)\n",
		       len, ring->rx_buffersize, cnt);
		जाओ drop;
	पूर्ण

	dmaaddr = meta->dmaaddr;
	err = setup_rx_descbuffer(ring, desc, meta, GFP_ATOMIC);
	अगर (unlikely(err)) अणु
		b43dbg(ring->dev->wl, "DMA RX: setup_rx_descbuffer() failed\n");
		जाओ drop_recycle_buffer;
	पूर्ण

	unmap_descbuffer(ring, dmaaddr, ring->rx_buffersize, 0);
	skb_put(skb, len + ring->frameoffset);
	skb_pull(skb, ring->frameoffset);

	b43_rx(ring->dev, skb, rxhdr);
drop:
	वापस;

drop_recycle_buffer:
	/* Poison and recycle the RX buffer. */
	b43_poison_rx_buffer(ring, skb);
	sync_descbuffer_क्रम_device(ring, dmaaddr, ring->rx_buffersize);
पूर्ण

व्योम b43_dma_handle_rx_overflow(काष्ठा b43_dmaring *ring)
अणु
	पूर्णांक current_slot, previous_slot;

	B43_WARN_ON(ring->tx);

	/* Device has filled all buffers, drop all packets and let TCP
	 * decrease speed.
	 * Decrement RX index by one will let the device to see all slots
	 * as मुक्त again
	 */
	/*
	*TODO: How to increase rx_drop in mac80211?
	*/
	current_slot = ring->ops->get_current_rxslot(ring);
	previous_slot = prev_slot(ring, current_slot);
	ring->ops->set_current_rxslot(ring, previous_slot);
पूर्ण

व्योम b43_dma_rx(काष्ठा b43_dmaring *ring)
अणु
	स्थिर काष्ठा b43_dma_ops *ops = ring->ops;
	पूर्णांक slot, current_slot;
	पूर्णांक used_slots = 0;

	B43_WARN_ON(ring->tx);
	current_slot = ops->get_current_rxslot(ring);
	B43_WARN_ON(!(current_slot >= 0 && current_slot < ring->nr_slots));

	slot = ring->current_slot;
	क्रम (; slot != current_slot; slot = next_slot(ring, slot)) अणु
		dma_rx(ring, &slot);
		update_max_used_slots(ring, ++used_slots);
	पूर्ण
	wmb();
	ops->set_current_rxslot(ring, slot);
	ring->current_slot = slot;
पूर्ण

अटल व्योम b43_dma_tx_suspend_ring(काष्ठा b43_dmaring *ring)
अणु
	B43_WARN_ON(!ring->tx);
	ring->ops->tx_suspend(ring);
पूर्ण

अटल व्योम b43_dma_tx_resume_ring(काष्ठा b43_dmaring *ring)
अणु
	B43_WARN_ON(!ring->tx);
	ring->ops->tx_resume(ring);
पूर्ण

व्योम b43_dma_tx_suspend(काष्ठा b43_wldev *dev)
अणु
	b43_घातer_saving_ctl_bits(dev, B43_PS_AWAKE);
	b43_dma_tx_suspend_ring(dev->dma.tx_ring_AC_BK);
	b43_dma_tx_suspend_ring(dev->dma.tx_ring_AC_BE);
	b43_dma_tx_suspend_ring(dev->dma.tx_ring_AC_VI);
	b43_dma_tx_suspend_ring(dev->dma.tx_ring_AC_VO);
	b43_dma_tx_suspend_ring(dev->dma.tx_ring_mcast);
पूर्ण

व्योम b43_dma_tx_resume(काष्ठा b43_wldev *dev)
अणु
	b43_dma_tx_resume_ring(dev->dma.tx_ring_mcast);
	b43_dma_tx_resume_ring(dev->dma.tx_ring_AC_VO);
	b43_dma_tx_resume_ring(dev->dma.tx_ring_AC_VI);
	b43_dma_tx_resume_ring(dev->dma.tx_ring_AC_BE);
	b43_dma_tx_resume_ring(dev->dma.tx_ring_AC_BK);
	b43_घातer_saving_ctl_bits(dev, 0);
पूर्ण

अटल व्योम direct_fअगरo_rx(काष्ठा b43_wldev *dev, क्रमागत b43_dmatype type,
			   u16 mmio_base, bool enable)
अणु
	u32 ctl;

	अगर (type == B43_DMA_64BIT) अणु
		ctl = b43_पढ़ो32(dev, mmio_base + B43_DMA64_RXCTL);
		ctl &= ~B43_DMA64_RXसूचीECTFIFO;
		अगर (enable)
			ctl |= B43_DMA64_RXसूचीECTFIFO;
		b43_ग_लिखो32(dev, mmio_base + B43_DMA64_RXCTL, ctl);
	पूर्ण अन्यथा अणु
		ctl = b43_पढ़ो32(dev, mmio_base + B43_DMA32_RXCTL);
		ctl &= ~B43_DMA32_RXसूचीECTFIFO;
		अगर (enable)
			ctl |= B43_DMA32_RXसूचीECTFIFO;
		b43_ग_लिखो32(dev, mmio_base + B43_DMA32_RXCTL, ctl);
	पूर्ण
पूर्ण

/* Enable/Disable Direct FIFO Receive Mode (PIO) on a RX engine.
 * This is called from PIO code, so DMA काष्ठाures are not available. */
व्योम b43_dma_direct_fअगरo_rx(काष्ठा b43_wldev *dev,
			    अचिन्हित पूर्णांक engine_index, bool enable)
अणु
	क्रमागत b43_dmatype type;
	u16 mmio_base;

	type = b43_engine_type(dev);

	mmio_base = b43_dmacontroller_base(type, engine_index);
	direct_fअगरo_rx(dev, type, mmio_base, enable);
पूर्ण
