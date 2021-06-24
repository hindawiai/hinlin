<शैली गुरु>
/*
 * Driver क्रम (BCM4706)? GBit MAC core on BCMA bus.
 *
 * Copyright (C) 2012 Rafaध Miधecki <zajec5@gmail.com>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */


#घोषणा pr_fmt(fmt)		KBUILD_MODNAME ": " fmt

#समावेश <linux/bcma/bcma.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bcm47xx_nvram.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <net/dsa.h>
#समावेश "bgmac.h"

अटल bool bgmac_रुको_value(काष्ठा bgmac *bgmac, u16 reg, u32 mask,
			     u32 value, पूर्णांक समयout)
अणु
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < समयout / 10; i++) अणु
		val = bgmac_पढ़ो(bgmac, reg);
		अगर ((val & mask) == value)
			वापस true;
		udelay(10);
	पूर्ण
	dev_err(bgmac->dev, "Timeout waiting for reg 0x%X\n", reg);
	वापस false;
पूर्ण

/**************************************************
 * DMA
 **************************************************/

अटल व्योम bgmac_dma_tx_reset(काष्ठा bgmac *bgmac, काष्ठा bgmac_dma_ring *ring)
अणु
	u32 val;
	पूर्णांक i;

	अगर (!ring->mmio_base)
		वापस;

	/* Suspend DMA TX ring first.
	 * bgmac_रुको_value करोesn't support रुकोing क्रम any of few values, so
	 * implement whole loop here.
	 */
	bgmac_ग_लिखो(bgmac, ring->mmio_base + BGMAC_DMA_TX_CTL,
		    BGMAC_DMA_TX_SUSPEND);
	क्रम (i = 0; i < 10000 / 10; i++) अणु
		val = bgmac_पढ़ो(bgmac, ring->mmio_base + BGMAC_DMA_TX_STATUS);
		val &= BGMAC_DMA_TX_STAT;
		अगर (val == BGMAC_DMA_TX_STAT_DISABLED ||
		    val == BGMAC_DMA_TX_STAT_IDLEWAIT ||
		    val == BGMAC_DMA_TX_STAT_STOPPED) अणु
			i = 0;
			अवरोध;
		पूर्ण
		udelay(10);
	पूर्ण
	अगर (i)
		dev_err(bgmac->dev, "Timeout suspending DMA TX ring 0x%X (BGMAC_DMA_TX_STAT: 0x%08X)\n",
			ring->mmio_base, val);

	/* Remove SUSPEND bit */
	bgmac_ग_लिखो(bgmac, ring->mmio_base + BGMAC_DMA_TX_CTL, 0);
	अगर (!bgmac_रुको_value(bgmac,
			      ring->mmio_base + BGMAC_DMA_TX_STATUS,
			      BGMAC_DMA_TX_STAT, BGMAC_DMA_TX_STAT_DISABLED,
			      10000)) अणु
		dev_warn(bgmac->dev, "DMA TX ring 0x%X wasn't disabled on time, waiting additional 300us\n",
			 ring->mmio_base);
		udelay(300);
		val = bgmac_पढ़ो(bgmac, ring->mmio_base + BGMAC_DMA_TX_STATUS);
		अगर ((val & BGMAC_DMA_TX_STAT) != BGMAC_DMA_TX_STAT_DISABLED)
			dev_err(bgmac->dev, "Reset of DMA TX ring 0x%X failed\n",
				ring->mmio_base);
	पूर्ण
पूर्ण

अटल व्योम bgmac_dma_tx_enable(काष्ठा bgmac *bgmac,
				काष्ठा bgmac_dma_ring *ring)
अणु
	u32 ctl;

	ctl = bgmac_पढ़ो(bgmac, ring->mmio_base + BGMAC_DMA_TX_CTL);
	अगर (bgmac->feature_flags & BGMAC_FEAT_TX_MASK_SETUP) अणु
		ctl &= ~BGMAC_DMA_TX_BL_MASK;
		ctl |= BGMAC_DMA_TX_BL_128 << BGMAC_DMA_TX_BL_SHIFT;

		ctl &= ~BGMAC_DMA_TX_MR_MASK;
		ctl |= BGMAC_DMA_TX_MR_2 << BGMAC_DMA_TX_MR_SHIFT;

		ctl &= ~BGMAC_DMA_TX_PC_MASK;
		ctl |= BGMAC_DMA_TX_PC_16 << BGMAC_DMA_TX_PC_SHIFT;

		ctl &= ~BGMAC_DMA_TX_PT_MASK;
		ctl |= BGMAC_DMA_TX_PT_8 << BGMAC_DMA_TX_PT_SHIFT;
	पूर्ण
	ctl |= BGMAC_DMA_TX_ENABLE;
	ctl |= BGMAC_DMA_TX_PARITY_DISABLE;
	bgmac_ग_लिखो(bgmac, ring->mmio_base + BGMAC_DMA_TX_CTL, ctl);
पूर्ण

अटल व्योम
bgmac_dma_tx_add_buf(काष्ठा bgmac *bgmac, काष्ठा bgmac_dma_ring *ring,
		     पूर्णांक i, पूर्णांक len, u32 ctl0)
अणु
	काष्ठा bgmac_slot_info *slot;
	काष्ठा bgmac_dma_desc *dma_desc;
	u32 ctl1;

	अगर (i == BGMAC_TX_RING_SLOTS - 1)
		ctl0 |= BGMAC_DESC_CTL0_EOT;

	ctl1 = len & BGMAC_DESC_CTL1_LEN;

	slot = &ring->slots[i];
	dma_desc = &ring->cpu_base[i];
	dma_desc->addr_low = cpu_to_le32(lower_32_bits(slot->dma_addr));
	dma_desc->addr_high = cpu_to_le32(upper_32_bits(slot->dma_addr));
	dma_desc->ctl0 = cpu_to_le32(ctl0);
	dma_desc->ctl1 = cpu_to_le32(ctl1);
पूर्ण

अटल netdev_tx_t bgmac_dma_tx_add(काष्ठा bgmac *bgmac,
				    काष्ठा bgmac_dma_ring *ring,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा device *dma_dev = bgmac->dma_dev;
	काष्ठा net_device *net_dev = bgmac->net_dev;
	पूर्णांक index = ring->end % BGMAC_TX_RING_SLOTS;
	काष्ठा bgmac_slot_info *slot = &ring->slots[index];
	पूर्णांक nr_frags;
	u32 flags;
	पूर्णांक i;

	अगर (skb->len > BGMAC_DESC_CTL1_LEN) अणु
		netdev_err(bgmac->net_dev, "Too long skb (%d)\n", skb->len);
		जाओ err_drop;
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		skb_checksum_help(skb);

	nr_frags = skb_shinfo(skb)->nr_frags;

	/* ring->end - ring->start will वापस the number of valid slots,
	 * even when ring->end overflows
	 */
	अगर (ring->end - ring->start + nr_frags + 1 >= BGMAC_TX_RING_SLOTS) अणु
		netdev_err(bgmac->net_dev, "TX ring is full, queue should be stopped!\n");
		netअगर_stop_queue(net_dev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	slot->dma_addr = dma_map_single(dma_dev, skb->data, skb_headlen(skb),
					DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dma_dev, slot->dma_addr)))
		जाओ err_dma_head;

	flags = BGMAC_DESC_CTL0_SOF;
	अगर (!nr_frags)
		flags |= BGMAC_DESC_CTL0_खातापूर्ण | BGMAC_DESC_CTL0_IOC;

	bgmac_dma_tx_add_buf(bgmac, ring, index, skb_headlen(skb), flags);
	flags = 0;

	क्रम (i = 0; i < nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		पूर्णांक len = skb_frag_size(frag);

		index = (index + 1) % BGMAC_TX_RING_SLOTS;
		slot = &ring->slots[index];
		slot->dma_addr = skb_frag_dma_map(dma_dev, frag, 0,
						  len, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(dma_dev, slot->dma_addr)))
			जाओ err_dma;

		अगर (i == nr_frags - 1)
			flags |= BGMAC_DESC_CTL0_खातापूर्ण | BGMAC_DESC_CTL0_IOC;

		bgmac_dma_tx_add_buf(bgmac, ring, index, len, flags);
	पूर्ण

	slot->skb = skb;
	ring->end += nr_frags + 1;
	netdev_sent_queue(net_dev, skb->len);

	wmb();

	/* Increase ring->end to poपूर्णांक empty slot. We tell hardware the first
	 * slot it should *not* पढ़ो.
	 */
	bgmac_ग_लिखो(bgmac, ring->mmio_base + BGMAC_DMA_TX_INDEX,
		    ring->index_base +
		    (ring->end % BGMAC_TX_RING_SLOTS) *
		    माप(काष्ठा bgmac_dma_desc));

	अगर (ring->end - ring->start >= BGMAC_TX_RING_SLOTS - 8)
		netअगर_stop_queue(net_dev);

	वापस NETDEV_TX_OK;

err_dma:
	dma_unmap_single(dma_dev, slot->dma_addr, skb_headlen(skb),
			 DMA_TO_DEVICE);

	जबतक (i-- > 0) अणु
		पूर्णांक index = (ring->end + i) % BGMAC_TX_RING_SLOTS;
		काष्ठा bgmac_slot_info *slot = &ring->slots[index];
		u32 ctl1 = le32_to_cpu(ring->cpu_base[index].ctl1);
		पूर्णांक len = ctl1 & BGMAC_DESC_CTL1_LEN;

		dma_unmap_page(dma_dev, slot->dma_addr, len, DMA_TO_DEVICE);
	पूर्ण

err_dma_head:
	netdev_err(bgmac->net_dev, "Mapping error of skb on ring 0x%X\n",
		   ring->mmio_base);

err_drop:
	dev_kमुक्त_skb(skb);
	net_dev->stats.tx_dropped++;
	net_dev->stats.tx_errors++;
	वापस NETDEV_TX_OK;
पूर्ण

/* Free transmitted packets */
अटल व्योम bgmac_dma_tx_मुक्त(काष्ठा bgmac *bgmac, काष्ठा bgmac_dma_ring *ring)
अणु
	काष्ठा device *dma_dev = bgmac->dma_dev;
	पूर्णांक empty_slot;
	अचिन्हित bytes_compl = 0, pkts_compl = 0;

	/* The last slot that hardware didn't consume yet */
	empty_slot = bgmac_पढ़ो(bgmac, ring->mmio_base + BGMAC_DMA_TX_STATUS);
	empty_slot &= BGMAC_DMA_TX_STATDPTR;
	empty_slot -= ring->index_base;
	empty_slot &= BGMAC_DMA_TX_STATDPTR;
	empty_slot /= माप(काष्ठा bgmac_dma_desc);

	जबतक (ring->start != ring->end) अणु
		पूर्णांक slot_idx = ring->start % BGMAC_TX_RING_SLOTS;
		काष्ठा bgmac_slot_info *slot = &ring->slots[slot_idx];
		u32 ctl0, ctl1;
		पूर्णांक len;

		अगर (slot_idx == empty_slot)
			अवरोध;

		ctl0 = le32_to_cpu(ring->cpu_base[slot_idx].ctl0);
		ctl1 = le32_to_cpu(ring->cpu_base[slot_idx].ctl1);
		len = ctl1 & BGMAC_DESC_CTL1_LEN;
		अगर (ctl0 & BGMAC_DESC_CTL0_SOF)
			/* Unmap no दीर्घer used buffer */
			dma_unmap_single(dma_dev, slot->dma_addr, len,
					 DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_page(dma_dev, slot->dma_addr, len,
				       DMA_TO_DEVICE);

		अगर (slot->skb) अणु
			bgmac->net_dev->stats.tx_bytes += slot->skb->len;
			bgmac->net_dev->stats.tx_packets++;
			bytes_compl += slot->skb->len;
			pkts_compl++;

			/* Free memory! :) */
			dev_kमुक्त_skb(slot->skb);
			slot->skb = शून्य;
		पूर्ण

		slot->dma_addr = 0;
		ring->start++;
	पूर्ण

	अगर (!pkts_compl)
		वापस;

	netdev_completed_queue(bgmac->net_dev, pkts_compl, bytes_compl);

	अगर (netअगर_queue_stopped(bgmac->net_dev))
		netअगर_wake_queue(bgmac->net_dev);
पूर्ण

अटल व्योम bgmac_dma_rx_reset(काष्ठा bgmac *bgmac, काष्ठा bgmac_dma_ring *ring)
अणु
	अगर (!ring->mmio_base)
		वापस;

	bgmac_ग_लिखो(bgmac, ring->mmio_base + BGMAC_DMA_RX_CTL, 0);
	अगर (!bgmac_रुको_value(bgmac,
			      ring->mmio_base + BGMAC_DMA_RX_STATUS,
			      BGMAC_DMA_RX_STAT, BGMAC_DMA_RX_STAT_DISABLED,
			      10000))
		dev_err(bgmac->dev, "Reset of ring 0x%X RX failed\n",
			ring->mmio_base);
पूर्ण

अटल व्योम bgmac_dma_rx_enable(काष्ठा bgmac *bgmac,
				काष्ठा bgmac_dma_ring *ring)
अणु
	u32 ctl;

	ctl = bgmac_पढ़ो(bgmac, ring->mmio_base + BGMAC_DMA_RX_CTL);

	/* preserve ONLY bits 16-17 from current hardware value */
	ctl &= BGMAC_DMA_RX_ADDREXT_MASK;

	अगर (bgmac->feature_flags & BGMAC_FEAT_RX_MASK_SETUP) अणु
		ctl &= ~BGMAC_DMA_RX_BL_MASK;
		ctl |= BGMAC_DMA_RX_BL_128 << BGMAC_DMA_RX_BL_SHIFT;

		ctl &= ~BGMAC_DMA_RX_PC_MASK;
		ctl |= BGMAC_DMA_RX_PC_8 << BGMAC_DMA_RX_PC_SHIFT;

		ctl &= ~BGMAC_DMA_RX_PT_MASK;
		ctl |= BGMAC_DMA_RX_PT_1 << BGMAC_DMA_RX_PT_SHIFT;
	पूर्ण
	ctl |= BGMAC_DMA_RX_ENABLE;
	ctl |= BGMAC_DMA_RX_PARITY_DISABLE;
	ctl |= BGMAC_DMA_RX_OVERFLOW_CONT;
	ctl |= BGMAC_RX_FRAME_OFFSET << BGMAC_DMA_RX_FRAME_OFFSET_SHIFT;
	bgmac_ग_लिखो(bgmac, ring->mmio_base + BGMAC_DMA_RX_CTL, ctl);
पूर्ण

अटल पूर्णांक bgmac_dma_rx_skb_क्रम_slot(काष्ठा bgmac *bgmac,
				     काष्ठा bgmac_slot_info *slot)
अणु
	काष्ठा device *dma_dev = bgmac->dma_dev;
	dma_addr_t dma_addr;
	काष्ठा bgmac_rx_header *rx;
	व्योम *buf;

	/* Alloc skb */
	buf = netdev_alloc_frag(BGMAC_RX_ALLOC_SIZE);
	अगर (!buf)
		वापस -ENOMEM;

	/* Poison - अगर everything goes fine, hardware will overग_लिखो it */
	rx = buf + BGMAC_RX_BUF_OFFSET;
	rx->len = cpu_to_le16(0xdead);
	rx->flags = cpu_to_le16(0xbeef);

	/* Map skb क्रम the DMA */
	dma_addr = dma_map_single(dma_dev, buf + BGMAC_RX_BUF_OFFSET,
				  BGMAC_RX_BUF_SIZE, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dma_dev, dma_addr)) अणु
		netdev_err(bgmac->net_dev, "DMA mapping error\n");
		put_page(virt_to_head_page(buf));
		वापस -ENOMEM;
	पूर्ण

	/* Update the slot */
	slot->buf = buf;
	slot->dma_addr = dma_addr;

	वापस 0;
पूर्ण

अटल व्योम bgmac_dma_rx_update_index(काष्ठा bgmac *bgmac,
				      काष्ठा bgmac_dma_ring *ring)
अणु
	dma_wmb();

	bgmac_ग_लिखो(bgmac, ring->mmio_base + BGMAC_DMA_RX_INDEX,
		    ring->index_base +
		    ring->end * माप(काष्ठा bgmac_dma_desc));
पूर्ण

अटल व्योम bgmac_dma_rx_setup_desc(काष्ठा bgmac *bgmac,
				    काष्ठा bgmac_dma_ring *ring, पूर्णांक desc_idx)
अणु
	काष्ठा bgmac_dma_desc *dma_desc = ring->cpu_base + desc_idx;
	u32 ctl0 = 0, ctl1 = 0;

	अगर (desc_idx == BGMAC_RX_RING_SLOTS - 1)
		ctl0 |= BGMAC_DESC_CTL0_EOT;
	ctl1 |= BGMAC_RX_BUF_SIZE & BGMAC_DESC_CTL1_LEN;
	/* Is there any BGMAC device that requires extension? */
	/* ctl1 |= (addrext << B43_DMA64_DCTL1_ADDREXT_SHIFT) &
	 * B43_DMA64_DCTL1_ADDREXT_MASK;
	 */

	dma_desc->addr_low = cpu_to_le32(lower_32_bits(ring->slots[desc_idx].dma_addr));
	dma_desc->addr_high = cpu_to_le32(upper_32_bits(ring->slots[desc_idx].dma_addr));
	dma_desc->ctl0 = cpu_to_le32(ctl0);
	dma_desc->ctl1 = cpu_to_le32(ctl1);

	ring->end = desc_idx;
पूर्ण

अटल व्योम bgmac_dma_rx_poison_buf(काष्ठा device *dma_dev,
				    काष्ठा bgmac_slot_info *slot)
अणु
	काष्ठा bgmac_rx_header *rx = slot->buf + BGMAC_RX_BUF_OFFSET;

	dma_sync_single_क्रम_cpu(dma_dev, slot->dma_addr, BGMAC_RX_BUF_SIZE,
				DMA_FROM_DEVICE);
	rx->len = cpu_to_le16(0xdead);
	rx->flags = cpu_to_le16(0xbeef);
	dma_sync_single_क्रम_device(dma_dev, slot->dma_addr, BGMAC_RX_BUF_SIZE,
				   DMA_FROM_DEVICE);
पूर्ण

अटल पूर्णांक bgmac_dma_rx_पढ़ो(काष्ठा bgmac *bgmac, काष्ठा bgmac_dma_ring *ring,
			     पूर्णांक weight)
अणु
	u32 end_slot;
	पूर्णांक handled = 0;

	end_slot = bgmac_पढ़ो(bgmac, ring->mmio_base + BGMAC_DMA_RX_STATUS);
	end_slot &= BGMAC_DMA_RX_STATDPTR;
	end_slot -= ring->index_base;
	end_slot &= BGMAC_DMA_RX_STATDPTR;
	end_slot /= माप(काष्ठा bgmac_dma_desc);

	जबतक (ring->start != end_slot) अणु
		काष्ठा device *dma_dev = bgmac->dma_dev;
		काष्ठा bgmac_slot_info *slot = &ring->slots[ring->start];
		काष्ठा bgmac_rx_header *rx = slot->buf + BGMAC_RX_BUF_OFFSET;
		काष्ठा sk_buff *skb;
		व्योम *buf = slot->buf;
		dma_addr_t dma_addr = slot->dma_addr;
		u16 len, flags;

		करो अणु
			/* Prepare new skb as replacement */
			अगर (bgmac_dma_rx_skb_क्रम_slot(bgmac, slot)) अणु
				bgmac_dma_rx_poison_buf(dma_dev, slot);
				अवरोध;
			पूर्ण

			/* Unmap buffer to make it accessible to the CPU */
			dma_unmap_single(dma_dev, dma_addr,
					 BGMAC_RX_BUF_SIZE, DMA_FROM_DEVICE);

			/* Get info from the header */
			len = le16_to_cpu(rx->len);
			flags = le16_to_cpu(rx->flags);

			/* Check क्रम poison and drop or pass the packet */
			अगर (len == 0xdead && flags == 0xbeef) अणु
				netdev_err(bgmac->net_dev, "Found poisoned packet at slot %d, DMA issue!\n",
					   ring->start);
				put_page(virt_to_head_page(buf));
				bgmac->net_dev->stats.rx_errors++;
				अवरोध;
			पूर्ण

			अगर (len > BGMAC_RX_ALLOC_SIZE) अणु
				netdev_err(bgmac->net_dev, "Found oversized packet at slot %d, DMA issue!\n",
					   ring->start);
				put_page(virt_to_head_page(buf));
				bgmac->net_dev->stats.rx_length_errors++;
				bgmac->net_dev->stats.rx_errors++;
				अवरोध;
			पूर्ण

			/* Omit CRC. */
			len -= ETH_FCS_LEN;

			skb = build_skb(buf, BGMAC_RX_ALLOC_SIZE);
			अगर (unlikely(!skb)) अणु
				netdev_err(bgmac->net_dev, "build_skb failed\n");
				put_page(virt_to_head_page(buf));
				bgmac->net_dev->stats.rx_errors++;
				अवरोध;
			पूर्ण
			skb_put(skb, BGMAC_RX_FRAME_OFFSET +
				BGMAC_RX_BUF_OFFSET + len);
			skb_pull(skb, BGMAC_RX_FRAME_OFFSET +
				 BGMAC_RX_BUF_OFFSET);

			skb_checksum_none_निश्चित(skb);
			skb->protocol = eth_type_trans(skb, bgmac->net_dev);
			bgmac->net_dev->stats.rx_bytes += len;
			bgmac->net_dev->stats.rx_packets++;
			napi_gro_receive(&bgmac->napi, skb);
			handled++;
		पूर्ण जबतक (0);

		bgmac_dma_rx_setup_desc(bgmac, ring, ring->start);

		अगर (++ring->start >= BGMAC_RX_RING_SLOTS)
			ring->start = 0;

		अगर (handled >= weight) /* Should never be greater */
			अवरोध;
	पूर्ण

	bgmac_dma_rx_update_index(bgmac, ring);

	वापस handled;
पूर्ण

/* Does ring support unaligned addressing? */
अटल bool bgmac_dma_unaligned(काष्ठा bgmac *bgmac,
				काष्ठा bgmac_dma_ring *ring,
				क्रमागत bgmac_dma_ring_type ring_type)
अणु
	चयन (ring_type) अणु
	हाल BGMAC_DMA_RING_TX:
		bgmac_ग_लिखो(bgmac, ring->mmio_base + BGMAC_DMA_TX_RINGLO,
			    0xff0);
		अगर (bgmac_पढ़ो(bgmac, ring->mmio_base + BGMAC_DMA_TX_RINGLO))
			वापस true;
		अवरोध;
	हाल BGMAC_DMA_RING_RX:
		bgmac_ग_लिखो(bgmac, ring->mmio_base + BGMAC_DMA_RX_RINGLO,
			    0xff0);
		अगर (bgmac_पढ़ो(bgmac, ring->mmio_base + BGMAC_DMA_RX_RINGLO))
			वापस true;
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम bgmac_dma_tx_ring_मुक्त(काष्ठा bgmac *bgmac,
				   काष्ठा bgmac_dma_ring *ring)
अणु
	काष्ठा device *dma_dev = bgmac->dma_dev;
	काष्ठा bgmac_dma_desc *dma_desc = ring->cpu_base;
	काष्ठा bgmac_slot_info *slot;
	पूर्णांक i;

	क्रम (i = 0; i < BGMAC_TX_RING_SLOTS; i++) अणु
		u32 ctl1 = le32_to_cpu(dma_desc[i].ctl1);
		अचिन्हित पूर्णांक len = ctl1 & BGMAC_DESC_CTL1_LEN;

		slot = &ring->slots[i];
		dev_kमुक्त_skb(slot->skb);

		अगर (!slot->dma_addr)
			जारी;

		अगर (slot->skb)
			dma_unmap_single(dma_dev, slot->dma_addr,
					 len, DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_page(dma_dev, slot->dma_addr,
				       len, DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल व्योम bgmac_dma_rx_ring_मुक्त(काष्ठा bgmac *bgmac,
				   काष्ठा bgmac_dma_ring *ring)
अणु
	काष्ठा device *dma_dev = bgmac->dma_dev;
	काष्ठा bgmac_slot_info *slot;
	पूर्णांक i;

	क्रम (i = 0; i < BGMAC_RX_RING_SLOTS; i++) अणु
		slot = &ring->slots[i];
		अगर (!slot->dma_addr)
			जारी;

		dma_unmap_single(dma_dev, slot->dma_addr,
				 BGMAC_RX_BUF_SIZE,
				 DMA_FROM_DEVICE);
		put_page(virt_to_head_page(slot->buf));
		slot->dma_addr = 0;
	पूर्ण
पूर्ण

अटल व्योम bgmac_dma_ring_desc_मुक्त(काष्ठा bgmac *bgmac,
				     काष्ठा bgmac_dma_ring *ring,
				     पूर्णांक num_slots)
अणु
	काष्ठा device *dma_dev = bgmac->dma_dev;
	पूर्णांक size;

	अगर (!ring->cpu_base)
	    वापस;

	/* Free ring of descriptors */
	size = num_slots * माप(काष्ठा bgmac_dma_desc);
	dma_मुक्त_coherent(dma_dev, size, ring->cpu_base,
			  ring->dma_base);
पूर्ण

अटल व्योम bgmac_dma_cleanup(काष्ठा bgmac *bgmac)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BGMAC_MAX_TX_RINGS; i++)
		bgmac_dma_tx_ring_मुक्त(bgmac, &bgmac->tx_ring[i]);

	क्रम (i = 0; i < BGMAC_MAX_RX_RINGS; i++)
		bgmac_dma_rx_ring_मुक्त(bgmac, &bgmac->rx_ring[i]);
पूर्ण

अटल व्योम bgmac_dma_मुक्त(काष्ठा bgmac *bgmac)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BGMAC_MAX_TX_RINGS; i++)
		bgmac_dma_ring_desc_मुक्त(bgmac, &bgmac->tx_ring[i],
					 BGMAC_TX_RING_SLOTS);

	क्रम (i = 0; i < BGMAC_MAX_RX_RINGS; i++)
		bgmac_dma_ring_desc_मुक्त(bgmac, &bgmac->rx_ring[i],
					 BGMAC_RX_RING_SLOTS);
पूर्ण

अटल पूर्णांक bgmac_dma_alloc(काष्ठा bgmac *bgmac)
अणु
	काष्ठा device *dma_dev = bgmac->dma_dev;
	काष्ठा bgmac_dma_ring *ring;
	अटल स्थिर u16 ring_base[] = अणु BGMAC_DMA_BASE0, BGMAC_DMA_BASE1,
					 BGMAC_DMA_BASE2, BGMAC_DMA_BASE3, पूर्ण;
	पूर्णांक size; /* ring size: dअगरferent क्रम Tx and Rx */
	पूर्णांक i;

	BUILD_BUG_ON(BGMAC_MAX_TX_RINGS > ARRAY_SIZE(ring_base));
	BUILD_BUG_ON(BGMAC_MAX_RX_RINGS > ARRAY_SIZE(ring_base));

	अगर (!(bgmac->feature_flags & BGMAC_FEAT_IDM_MASK)) अणु
		अगर (!(bgmac_idm_पढ़ो(bgmac, BCMA_IOST) & BCMA_IOST_DMA64)) अणु
			dev_err(bgmac->dev, "Core does not report 64-bit DMA\n");
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < BGMAC_MAX_TX_RINGS; i++) अणु
		ring = &bgmac->tx_ring[i];
		ring->mmio_base = ring_base[i];

		/* Alloc ring of descriptors */
		size = BGMAC_TX_RING_SLOTS * माप(काष्ठा bgmac_dma_desc);
		ring->cpu_base = dma_alloc_coherent(dma_dev, size,
						    &ring->dma_base,
						    GFP_KERNEL);
		अगर (!ring->cpu_base) अणु
			dev_err(bgmac->dev, "Allocation of TX ring 0x%X failed\n",
				ring->mmio_base);
			जाओ err_dma_मुक्त;
		पूर्ण

		ring->unaligned = bgmac_dma_unaligned(bgmac, ring,
						      BGMAC_DMA_RING_TX);
		अगर (ring->unaligned)
			ring->index_base = lower_32_bits(ring->dma_base);
		अन्यथा
			ring->index_base = 0;

		/* No need to alloc TX slots yet */
	पूर्ण

	क्रम (i = 0; i < BGMAC_MAX_RX_RINGS; i++) अणु
		ring = &bgmac->rx_ring[i];
		ring->mmio_base = ring_base[i];

		/* Alloc ring of descriptors */
		size = BGMAC_RX_RING_SLOTS * माप(काष्ठा bgmac_dma_desc);
		ring->cpu_base = dma_alloc_coherent(dma_dev, size,
						    &ring->dma_base,
						    GFP_KERNEL);
		अगर (!ring->cpu_base) अणु
			dev_err(bgmac->dev, "Allocation of RX ring 0x%X failed\n",
				ring->mmio_base);
			जाओ err_dma_मुक्त;
		पूर्ण

		ring->unaligned = bgmac_dma_unaligned(bgmac, ring,
						      BGMAC_DMA_RING_RX);
		अगर (ring->unaligned)
			ring->index_base = lower_32_bits(ring->dma_base);
		अन्यथा
			ring->index_base = 0;
	पूर्ण

	वापस 0;

err_dma_मुक्त:
	bgmac_dma_मुक्त(bgmac);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक bgmac_dma_init(काष्ठा bgmac *bgmac)
अणु
	काष्ठा bgmac_dma_ring *ring;
	पूर्णांक i, err;

	क्रम (i = 0; i < BGMAC_MAX_TX_RINGS; i++) अणु
		ring = &bgmac->tx_ring[i];

		अगर (!ring->unaligned)
			bgmac_dma_tx_enable(bgmac, ring);
		bgmac_ग_लिखो(bgmac, ring->mmio_base + BGMAC_DMA_TX_RINGLO,
			    lower_32_bits(ring->dma_base));
		bgmac_ग_लिखो(bgmac, ring->mmio_base + BGMAC_DMA_TX_RINGHI,
			    upper_32_bits(ring->dma_base));
		अगर (ring->unaligned)
			bgmac_dma_tx_enable(bgmac, ring);

		ring->start = 0;
		ring->end = 0;	/* Poपूर्णांकs the slot that should *not* be पढ़ो */
	पूर्ण

	क्रम (i = 0; i < BGMAC_MAX_RX_RINGS; i++) अणु
		पूर्णांक j;

		ring = &bgmac->rx_ring[i];

		अगर (!ring->unaligned)
			bgmac_dma_rx_enable(bgmac, ring);
		bgmac_ग_लिखो(bgmac, ring->mmio_base + BGMAC_DMA_RX_RINGLO,
			    lower_32_bits(ring->dma_base));
		bgmac_ग_लिखो(bgmac, ring->mmio_base + BGMAC_DMA_RX_RINGHI,
			    upper_32_bits(ring->dma_base));
		अगर (ring->unaligned)
			bgmac_dma_rx_enable(bgmac, ring);

		ring->start = 0;
		ring->end = 0;
		क्रम (j = 0; j < BGMAC_RX_RING_SLOTS; j++) अणु
			err = bgmac_dma_rx_skb_क्रम_slot(bgmac, &ring->slots[j]);
			अगर (err)
				जाओ error;

			bgmac_dma_rx_setup_desc(bgmac, ring, j);
		पूर्ण

		bgmac_dma_rx_update_index(bgmac, ring);
	पूर्ण

	वापस 0;

error:
	bgmac_dma_cleanup(bgmac);
	वापस err;
पूर्ण


/**************************************************
 * Chip ops
 **************************************************/

/* TODO: can we just drop @क्रमce? Can we करोn't reset MAC at all अगर there is
 * nothing to change? Try अगर after stabilizng driver.
 */
अटल व्योम bgmac_umac_cmd_maskset(काष्ठा bgmac *bgmac, u32 mask, u32 set,
				   bool क्रमce)
अणु
	u32 cmdcfg = bgmac_umac_पढ़ो(bgmac, UMAC_CMD);
	u32 new_val = (cmdcfg & mask) | set;
	u32 cmdcfg_sr;

	अगर (bgmac->feature_flags & BGMAC_FEAT_CMDCFG_SR_REV4)
		cmdcfg_sr = CMD_SW_RESET;
	अन्यथा
		cmdcfg_sr = CMD_SW_RESET_OLD;

	bgmac_umac_maskset(bgmac, UMAC_CMD, ~0, cmdcfg_sr);
	udelay(2);

	अगर (new_val != cmdcfg || क्रमce)
		bgmac_umac_ग_लिखो(bgmac, UMAC_CMD, new_val);

	bgmac_umac_maskset(bgmac, UMAC_CMD, ~cmdcfg_sr, 0);
	udelay(2);
पूर्ण

अटल व्योम bgmac_ग_लिखो_mac_address(काष्ठा bgmac *bgmac, u8 *addr)
अणु
	u32 पंचांगp;

	पंचांगp = (addr[0] << 24) | (addr[1] << 16) | (addr[2] << 8) | addr[3];
	bgmac_umac_ग_लिखो(bgmac, UMAC_MAC0, पंचांगp);
	पंचांगp = (addr[4] << 8) | addr[5];
	bgmac_umac_ग_लिखो(bgmac, UMAC_MAC1, पंचांगp);
पूर्ण

अटल व्योम bgmac_set_rx_mode(काष्ठा net_device *net_dev)
अणु
	काष्ठा bgmac *bgmac = netdev_priv(net_dev);

	अगर (net_dev->flags & IFF_PROMISC)
		bgmac_umac_cmd_maskset(bgmac, ~0, CMD_PROMISC, true);
	अन्यथा
		bgmac_umac_cmd_maskset(bgmac, ~CMD_PROMISC, 0, true);
पूर्ण

#अगर 0 /* We करोn't use that regs yet */
अटल व्योम bgmac_chip_stats_update(काष्ठा bgmac *bgmac)
अणु
	पूर्णांक i;

	अगर (!(bgmac->feature_flags & BGMAC_FEAT_NO_CLR_MIB)) अणु
		क्रम (i = 0; i < BGMAC_NUM_MIB_TX_REGS; i++)
			bgmac->mib_tx_regs[i] =
				bgmac_पढ़ो(bgmac,
					   BGMAC_TX_GOOD_OCTETS + (i * 4));
		क्रम (i = 0; i < BGMAC_NUM_MIB_RX_REGS; i++)
			bgmac->mib_rx_regs[i] =
				bgmac_पढ़ो(bgmac,
					   BGMAC_RX_GOOD_OCTETS + (i * 4));
	पूर्ण

	/* TODO: what अन्यथा? how to handle BCM4706? Specs are needed */
पूर्ण
#पूर्ण_अगर

अटल व्योम bgmac_clear_mib(काष्ठा bgmac *bgmac)
अणु
	पूर्णांक i;

	अगर (bgmac->feature_flags & BGMAC_FEAT_NO_CLR_MIB)
		वापस;

	bgmac_set(bgmac, BGMAC_DEV_CTL, BGMAC_DC_MROR);
	क्रम (i = 0; i < BGMAC_NUM_MIB_TX_REGS; i++)
		bgmac_पढ़ो(bgmac, BGMAC_TX_GOOD_OCTETS + (i * 4));
	क्रम (i = 0; i < BGMAC_NUM_MIB_RX_REGS; i++)
		bgmac_पढ़ो(bgmac, BGMAC_RX_GOOD_OCTETS + (i * 4));
पूर्ण

/* http://bcm-v4.sipsolutions.net/mac-gbit/gmac/gmac_speed */
अटल व्योम bgmac_mac_speed(काष्ठा bgmac *bgmac)
अणु
	u32 mask = ~(CMD_SPEED_MASK << CMD_SPEED_SHIFT | CMD_HD_EN);
	u32 set = 0;

	चयन (bgmac->mac_speed) अणु
	हाल SPEED_10:
		set |= CMD_SPEED_10 << CMD_SPEED_SHIFT;
		अवरोध;
	हाल SPEED_100:
		set |= CMD_SPEED_100 << CMD_SPEED_SHIFT;
		अवरोध;
	हाल SPEED_1000:
		set |= CMD_SPEED_1000 << CMD_SPEED_SHIFT;
		अवरोध;
	हाल SPEED_2500:
		set |= CMD_SPEED_2500 << CMD_SPEED_SHIFT;
		अवरोध;
	शेष:
		dev_err(bgmac->dev, "Unsupported speed: %d\n",
			bgmac->mac_speed);
	पूर्ण

	अगर (bgmac->mac_duplex == DUPLEX_HALF)
		set |= CMD_HD_EN;

	bgmac_umac_cmd_maskset(bgmac, mask, set, true);
पूर्ण

अटल व्योम bgmac_miiconfig(काष्ठा bgmac *bgmac)
अणु
	अगर (bgmac->feature_flags & BGMAC_FEAT_FORCE_SPEED_2500) अणु
		अगर (!(bgmac->feature_flags & BGMAC_FEAT_IDM_MASK)) अणु
			bgmac_idm_ग_लिखो(bgmac, BCMA_IOCTL,
					bgmac_idm_पढ़ो(bgmac, BCMA_IOCTL) |
					0x40 | BGMAC_BCMA_IOCTL_SW_CLKEN);
		पूर्ण
		bgmac->mac_speed = SPEED_2500;
		bgmac->mac_duplex = DUPLEX_FULL;
		bgmac_mac_speed(bgmac);
	पूर्ण अन्यथा अणु
		u8 imode;

		imode = (bgmac_पढ़ो(bgmac, BGMAC_DEV_STATUS) &
			BGMAC_DS_MM_MASK) >> BGMAC_DS_MM_SHIFT;
		अगर (imode == 0 || imode == 1) अणु
			bgmac->mac_speed = SPEED_100;
			bgmac->mac_duplex = DUPLEX_FULL;
			bgmac_mac_speed(bgmac);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bgmac_chip_reset_idm_config(काष्ठा bgmac *bgmac)
अणु
	u32 iost;

	iost = bgmac_idm_पढ़ो(bgmac, BCMA_IOST);
	अगर (bgmac->feature_flags & BGMAC_FEAT_IOST_ATTACHED)
		iost &= ~BGMAC_BCMA_IOST_ATTACHED;

	/* 3GMAC: क्रम BCM4707 & BCM47094, only करो core reset at bgmac_probe() */
	अगर (!(bgmac->feature_flags & BGMAC_FEAT_NO_RESET)) अणु
		u32 flags = 0;

		अगर (iost & BGMAC_BCMA_IOST_ATTACHED) अणु
			flags = BGMAC_BCMA_IOCTL_SW_CLKEN;
			अगर (!bgmac->has_robosw)
				flags |= BGMAC_BCMA_IOCTL_SW_RESET;
		पूर्ण
		bgmac_clk_enable(bgmac, flags);
	पूर्ण

	अगर (iost & BGMAC_BCMA_IOST_ATTACHED && !bgmac->has_robosw)
		bgmac_idm_ग_लिखो(bgmac, BCMA_IOCTL,
				bgmac_idm_पढ़ो(bgmac, BCMA_IOCTL) &
				~BGMAC_BCMA_IOCTL_SW_RESET);
पूर्ण

/* http://bcm-v4.sipsolutions.net/mac-gbit/gmac/chipreset */
अटल व्योम bgmac_chip_reset(काष्ठा bgmac *bgmac)
अणु
	u32 cmdcfg_sr;
	पूर्णांक i;

	अगर (bgmac_clk_enabled(bgmac)) अणु
		अगर (!bgmac->stats_grabbed) अणु
			/* bgmac_chip_stats_update(bgmac); */
			bgmac->stats_grabbed = true;
		पूर्ण

		क्रम (i = 0; i < BGMAC_MAX_TX_RINGS; i++)
			bgmac_dma_tx_reset(bgmac, &bgmac->tx_ring[i]);

		bgmac_umac_cmd_maskset(bgmac, ~0, CMD_LCL_LOOP_EN, false);
		udelay(1);

		क्रम (i = 0; i < BGMAC_MAX_RX_RINGS; i++)
			bgmac_dma_rx_reset(bgmac, &bgmac->rx_ring[i]);

		/* TODO: Clear software multicast filter list */
	पूर्ण

	अगर (!(bgmac->feature_flags & BGMAC_FEAT_IDM_MASK))
		bgmac_chip_reset_idm_config(bgmac);

	/* Request Misc PLL क्रम corerev > 2 */
	अगर (bgmac->feature_flags & BGMAC_FEAT_MISC_PLL_REQ) अणु
		bgmac_set(bgmac, BCMA_CLKCTLST,
			  BGMAC_BCMA_CLKCTLST_MISC_PLL_REQ);
		bgmac_रुको_value(bgmac, BCMA_CLKCTLST,
				 BGMAC_BCMA_CLKCTLST_MISC_PLL_ST,
				 BGMAC_BCMA_CLKCTLST_MISC_PLL_ST,
				 1000);
	पूर्ण

	अगर (bgmac->feature_flags & BGMAC_FEAT_SW_TYPE_PHY) अणु
		u8 et_swtype = 0;
		u8 sw_type = BGMAC_CHIPCTL_1_SW_TYPE_EPHY |
			     BGMAC_CHIPCTL_1_IF_TYPE_MII;
		अक्षर buf[4];

		अगर (bcm47xx_nvram_दो_पर्या("et_swtype", buf, माप(buf)) > 0) अणु
			अगर (kstrtou8(buf, 0, &et_swtype))
				dev_err(bgmac->dev, "Failed to parse et_swtype (%s)\n",
					buf);
			et_swtype &= 0x0f;
			et_swtype <<= 4;
			sw_type = et_swtype;
		पूर्ण अन्यथा अगर (bgmac->feature_flags & BGMAC_FEAT_SW_TYPE_EPHYRMII) अणु
			sw_type = BGMAC_CHIPCTL_1_IF_TYPE_RMII |
				  BGMAC_CHIPCTL_1_SW_TYPE_EPHYRMII;
		पूर्ण अन्यथा अगर (bgmac->feature_flags & BGMAC_FEAT_SW_TYPE_RGMII) अणु
			sw_type = BGMAC_CHIPCTL_1_IF_TYPE_RGMII |
				  BGMAC_CHIPCTL_1_SW_TYPE_RGMII;
		पूर्ण
		bgmac_cco_ctl_maskset(bgmac, 1, ~(BGMAC_CHIPCTL_1_IF_TYPE_MASK |
						  BGMAC_CHIPCTL_1_SW_TYPE_MASK),
				      sw_type);
	पूर्ण अन्यथा अगर (bgmac->feature_flags & BGMAC_FEAT_CC4_IF_SW_TYPE) अणु
		u32 sw_type = BGMAC_CHIPCTL_4_IF_TYPE_MII |
			      BGMAC_CHIPCTL_4_SW_TYPE_EPHY;
		u8 et_swtype = 0;
		अक्षर buf[4];

		अगर (bcm47xx_nvram_दो_पर्या("et_swtype", buf, माप(buf)) > 0) अणु
			अगर (kstrtou8(buf, 0, &et_swtype))
				dev_err(bgmac->dev, "Failed to parse et_swtype (%s)\n",
					buf);
			sw_type = (et_swtype & 0x0f) << 12;
		पूर्ण अन्यथा अगर (bgmac->feature_flags & BGMAC_FEAT_CC4_IF_SW_TYPE_RGMII) अणु
			sw_type = BGMAC_CHIPCTL_4_IF_TYPE_RGMII |
				  BGMAC_CHIPCTL_4_SW_TYPE_RGMII;
		पूर्ण
		bgmac_cco_ctl_maskset(bgmac, 4, ~(BGMAC_CHIPCTL_4_IF_TYPE_MASK |
						  BGMAC_CHIPCTL_4_SW_TYPE_MASK),
				      sw_type);
	पूर्ण अन्यथा अगर (bgmac->feature_flags & BGMAC_FEAT_CC7_IF_TYPE_RGMII) अणु
		bgmac_cco_ctl_maskset(bgmac, 7, ~BGMAC_CHIPCTL_7_IF_TYPE_MASK,
				      BGMAC_CHIPCTL_7_IF_TYPE_RGMII);
	पूर्ण

	/* http://bcm-v4.sipsolutions.net/mac-gbit/gmac/gmac_reset
	 * Specs करोn't say about using UMAC_CMD_SR, but in this routine
	 * UMAC_CMD is पढ़ो _after_ putting chip in a reset. So it has to
	 * be keps until taking MAC out of the reset.
	 */
	अगर (bgmac->feature_flags & BGMAC_FEAT_CMDCFG_SR_REV4)
		cmdcfg_sr = CMD_SW_RESET;
	अन्यथा
		cmdcfg_sr = CMD_SW_RESET_OLD;

	bgmac_umac_cmd_maskset(bgmac,
			       ~(CMD_TX_EN |
				 CMD_RX_EN |
				 CMD_RX_PAUSE_IGNORE |
				 CMD_TX_ADDR_INS |
				 CMD_HD_EN |
				 CMD_LCL_LOOP_EN |
				 CMD_CNTL_FRM_EN |
				 CMD_RMT_LOOP_EN |
				 CMD_RX_ERR_DISC |
				 CMD_PRBL_EN |
				 CMD_TX_PAUSE_IGNORE |
				 CMD_PAD_EN |
				 CMD_PAUSE_FWD),
			       CMD_PROMISC |
			       CMD_NO_LEN_CHK |
			       CMD_CNTL_FRM_EN |
			       cmdcfg_sr,
			       false);
	bgmac->mac_speed = SPEED_UNKNOWN;
	bgmac->mac_duplex = DUPLEX_UNKNOWN;

	bgmac_clear_mib(bgmac);
	अगर (bgmac->feature_flags & BGMAC_FEAT_CMN_PHY_CTL)
		bgmac_cmn_maskset32(bgmac, BCMA_GMAC_CMN_PHY_CTL, ~0,
				    BCMA_GMAC_CMN_PC_MTE);
	अन्यथा
		bgmac_set(bgmac, BGMAC_PHY_CNTL, BGMAC_PC_MTE);
	bgmac_miiconfig(bgmac);
	अगर (bgmac->mii_bus)
		bgmac->mii_bus->reset(bgmac->mii_bus);

	netdev_reset_queue(bgmac->net_dev);
पूर्ण

अटल व्योम bgmac_chip_पूर्णांकrs_on(काष्ठा bgmac *bgmac)
अणु
	bgmac_ग_लिखो(bgmac, BGMAC_INT_MASK, bgmac->पूर्णांक_mask);
पूर्ण

अटल व्योम bgmac_chip_पूर्णांकrs_off(काष्ठा bgmac *bgmac)
अणु
	bgmac_ग_लिखो(bgmac, BGMAC_INT_MASK, 0);
	bgmac_पढ़ो(bgmac, BGMAC_INT_MASK);
पूर्ण

/* http://bcm-v4.sipsolutions.net/mac-gbit/gmac/gmac_enable */
अटल व्योम bgmac_enable(काष्ठा bgmac *bgmac)
अणु
	u32 cmdcfg_sr;
	u32 cmdcfg;
	u32 mode;

	अगर (bgmac->feature_flags & BGMAC_FEAT_CMDCFG_SR_REV4)
		cmdcfg_sr = CMD_SW_RESET;
	अन्यथा
		cmdcfg_sr = CMD_SW_RESET_OLD;

	cmdcfg = bgmac_umac_पढ़ो(bgmac, UMAC_CMD);
	bgmac_umac_cmd_maskset(bgmac, ~(CMD_TX_EN | CMD_RX_EN),
			       cmdcfg_sr, true);
	udelay(2);
	cmdcfg |= CMD_TX_EN | CMD_RX_EN;
	bgmac_umac_ग_लिखो(bgmac, UMAC_CMD, cmdcfg);

	mode = (bgmac_पढ़ो(bgmac, BGMAC_DEV_STATUS) & BGMAC_DS_MM_MASK) >>
		BGMAC_DS_MM_SHIFT;
	अगर (bgmac->feature_flags & BGMAC_FEAT_CLKCTLST || mode != 0)
		bgmac_set(bgmac, BCMA_CLKCTLST, BCMA_CLKCTLST_FORCEHT);
	अगर (!(bgmac->feature_flags & BGMAC_FEAT_CLKCTLST) && mode == 2)
		bgmac_cco_ctl_maskset(bgmac, 1, ~0,
				      BGMAC_CHIPCTL_1_RXC_DLL_BYPASS);

	अगर (bgmac->feature_flags & (BGMAC_FEAT_FLW_CTRL1 |
				    BGMAC_FEAT_FLW_CTRL2)) अणु
		u32 fl_ctl;

		अगर (bgmac->feature_flags & BGMAC_FEAT_FLW_CTRL1)
			fl_ctl = 0x2300e1;
		अन्यथा
			fl_ctl = 0x03cb04cb;

		bgmac_ग_लिखो(bgmac, BGMAC_FLOW_CTL_THRESH, fl_ctl);
		bgmac_umac_ग_लिखो(bgmac, UMAC_PAUSE_CTRL, 0x27fff);
	पूर्ण

	अगर (bgmac->feature_flags & BGMAC_FEAT_SET_RXQ_CLK) अणु
		u32 rxq_ctl;
		u16 bp_clk;
		u8 mdp;

		rxq_ctl = bgmac_पढ़ो(bgmac, BGMAC_RXQ_CTL);
		rxq_ctl &= ~BGMAC_RXQ_CTL_MDP_MASK;
		bp_clk = bgmac_get_bus_घड़ी(bgmac) / 1000000;
		mdp = (bp_clk * 128 / 1000) - 3;
		rxq_ctl |= (mdp << BGMAC_RXQ_CTL_MDP_SHIFT);
		bgmac_ग_लिखो(bgmac, BGMAC_RXQ_CTL, rxq_ctl);
	पूर्ण
पूर्ण

/* http://bcm-v4.sipsolutions.net/mac-gbit/gmac/chipinit */
अटल व्योम bgmac_chip_init(काष्ठा bgmac *bgmac)
अणु
	/* Clear any erroneously pending पूर्णांकerrupts */
	bgmac_ग_लिखो(bgmac, BGMAC_INT_STATUS, ~0);

	/* 1 पूर्णांकerrupt per received frame */
	bgmac_ग_लिखो(bgmac, BGMAC_INT_RECV_LAZY, 1 << BGMAC_IRL_FC_SHIFT);

	/* Enable 802.3x tx flow control (honor received PAUSE frames) */
	bgmac_umac_cmd_maskset(bgmac, ~CMD_RX_PAUSE_IGNORE, 0, true);

	bgmac_set_rx_mode(bgmac->net_dev);

	bgmac_ग_लिखो_mac_address(bgmac, bgmac->net_dev->dev_addr);

	अगर (bgmac->loopback)
		bgmac_umac_cmd_maskset(bgmac, ~0, CMD_LCL_LOOP_EN, false);
	अन्यथा
		bgmac_umac_cmd_maskset(bgmac, ~CMD_LCL_LOOP_EN, 0, false);

	bgmac_umac_ग_लिखो(bgmac, UMAC_MAX_FRAME_LEN, 32 + ETHER_MAX_LEN);

	bgmac_chip_पूर्णांकrs_on(bgmac);

	bgmac_enable(bgmac);
पूर्ण

अटल irqवापस_t bgmac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bgmac *bgmac = netdev_priv(dev_id);

	u32 पूर्णांक_status = bgmac_पढ़ो(bgmac, BGMAC_INT_STATUS);
	पूर्णांक_status &= bgmac->पूर्णांक_mask;

	अगर (!पूर्णांक_status)
		वापस IRQ_NONE;

	पूर्णांक_status &= ~(BGMAC_IS_TX0 | BGMAC_IS_RX);
	अगर (पूर्णांक_status)
		dev_err(bgmac->dev, "Unknown IRQs: 0x%08X\n", पूर्णांक_status);

	/* Disable new पूर्णांकerrupts until handling existing ones */
	bgmac_chip_पूर्णांकrs_off(bgmac);

	napi_schedule(&bgmac->napi);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bgmac_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक weight)
अणु
	काष्ठा bgmac *bgmac = container_of(napi, काष्ठा bgmac, napi);
	पूर्णांक handled = 0;

	/* Ack */
	bgmac_ग_लिखो(bgmac, BGMAC_INT_STATUS, ~0);

	bgmac_dma_tx_मुक्त(bgmac, &bgmac->tx_ring[0]);
	handled += bgmac_dma_rx_पढ़ो(bgmac, &bgmac->rx_ring[0], weight);

	/* Poll again अगर more events arrived in the meanसमय */
	अगर (bgmac_पढ़ो(bgmac, BGMAC_INT_STATUS) & (BGMAC_IS_TX0 | BGMAC_IS_RX))
		वापस weight;

	अगर (handled < weight) अणु
		napi_complete_करोne(napi, handled);
		bgmac_chip_पूर्णांकrs_on(bgmac);
	पूर्ण

	वापस handled;
पूर्ण

/**************************************************
 * net_device_ops
 **************************************************/

अटल पूर्णांक bgmac_खोलो(काष्ठा net_device *net_dev)
अणु
	काष्ठा bgmac *bgmac = netdev_priv(net_dev);
	पूर्णांक err = 0;

	bgmac_chip_reset(bgmac);

	err = bgmac_dma_init(bgmac);
	अगर (err)
		वापस err;

	/* Specs say about reclaiming rings here, but we करो that in DMA init */
	bgmac_chip_init(bgmac);

	err = request_irq(bgmac->irq, bgmac_पूर्णांकerrupt, IRQF_SHARED,
			  net_dev->name, net_dev);
	अगर (err < 0) अणु
		dev_err(bgmac->dev, "IRQ request error: %d!\n", err);
		bgmac_dma_cleanup(bgmac);
		वापस err;
	पूर्ण
	napi_enable(&bgmac->napi);

	phy_start(net_dev->phydev);

	netअगर_start_queue(net_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक bgmac_stop(काष्ठा net_device *net_dev)
अणु
	काष्ठा bgmac *bgmac = netdev_priv(net_dev);

	netअगर_carrier_off(net_dev);

	phy_stop(net_dev->phydev);

	napi_disable(&bgmac->napi);
	bgmac_chip_पूर्णांकrs_off(bgmac);
	मुक्त_irq(bgmac->irq, net_dev);

	bgmac_chip_reset(bgmac);
	bgmac_dma_cleanup(bgmac);

	वापस 0;
पूर्ण

अटल netdev_tx_t bgmac_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *net_dev)
अणु
	काष्ठा bgmac *bgmac = netdev_priv(net_dev);
	काष्ठा bgmac_dma_ring *ring;

	/* No QOS support yet */
	ring = &bgmac->tx_ring[0];
	वापस bgmac_dma_tx_add(bgmac, ring, skb);
पूर्ण

अटल पूर्णांक bgmac_set_mac_address(काष्ठा net_device *net_dev, व्योम *addr)
अणु
	काष्ठा bgmac *bgmac = netdev_priv(net_dev);
	काष्ठा sockaddr *sa = addr;
	पूर्णांक ret;

	ret = eth_prepare_mac_addr_change(net_dev, addr);
	अगर (ret < 0)
		वापस ret;

	ether_addr_copy(net_dev->dev_addr, sa->sa_data);
	bgmac_ग_लिखो_mac_address(bgmac, net_dev->dev_addr);

	eth_commit_mac_addr_change(net_dev, addr);
	वापस 0;
पूर्ण

अटल पूर्णांक bgmac_change_mtu(काष्ठा net_device *net_dev, पूर्णांक mtu)
अणु
	काष्ठा bgmac *bgmac = netdev_priv(net_dev);

	bgmac_umac_ग_लिखो(bgmac, UMAC_MAX_FRAME_LEN, 32 + mtu);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops bgmac_netdev_ops = अणु
	.nकरो_खोलो		= bgmac_खोलो,
	.nकरो_stop		= bgmac_stop,
	.nकरो_start_xmit		= bgmac_start_xmit,
	.nकरो_set_rx_mode	= bgmac_set_rx_mode,
	.nकरो_set_mac_address	= bgmac_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl           = phy_करो_ioctl_running,
	.nकरो_change_mtu		= bgmac_change_mtu,
पूर्ण;

/**************************************************
 * ethtool_ops
 **************************************************/

काष्ठा bgmac_stat अणु
	u8 size;
	u32 offset;
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा bgmac_stat bgmac_get_strings_stats[] = अणु
	अणु 8, BGMAC_TX_GOOD_OCTETS, "tx_good_octets" पूर्ण,
	अणु 4, BGMAC_TX_GOOD_PKTS, "tx_good" पूर्ण,
	अणु 8, BGMAC_TX_OCTETS, "tx_octets" पूर्ण,
	अणु 4, BGMAC_TX_PKTS, "tx_pkts" पूर्ण,
	अणु 4, BGMAC_TX_BROADCAST_PKTS, "tx_broadcast" पूर्ण,
	अणु 4, BGMAC_TX_MULTICAST_PKTS, "tx_multicast" पूर्ण,
	अणु 4, BGMAC_TX_LEN_64, "tx_64" पूर्ण,
	अणु 4, BGMAC_TX_LEN_65_TO_127, "tx_65_127" पूर्ण,
	अणु 4, BGMAC_TX_LEN_128_TO_255, "tx_128_255" पूर्ण,
	अणु 4, BGMAC_TX_LEN_256_TO_511, "tx_256_511" पूर्ण,
	अणु 4, BGMAC_TX_LEN_512_TO_1023, "tx_512_1023" पूर्ण,
	अणु 4, BGMAC_TX_LEN_1024_TO_1522, "tx_1024_1522" पूर्ण,
	अणु 4, BGMAC_TX_LEN_1523_TO_2047, "tx_1523_2047" पूर्ण,
	अणु 4, BGMAC_TX_LEN_2048_TO_4095, "tx_2048_4095" पूर्ण,
	अणु 4, BGMAC_TX_LEN_4096_TO_8191, "tx_4096_8191" पूर्ण,
	अणु 4, BGMAC_TX_LEN_8192_TO_MAX, "tx_8192_max" पूर्ण,
	अणु 4, BGMAC_TX_JABBER_PKTS, "tx_jabber" पूर्ण,
	अणु 4, BGMAC_TX_OVERSIZE_PKTS, "tx_oversize" पूर्ण,
	अणु 4, BGMAC_TX_FRAGMENT_PKTS, "tx_fragment" पूर्ण,
	अणु 4, BGMAC_TX_UNDERRUNS, "tx_underruns" पूर्ण,
	अणु 4, BGMAC_TX_TOTAL_COLS, "tx_total_cols" पूर्ण,
	अणु 4, BGMAC_TX_SINGLE_COLS, "tx_single_cols" पूर्ण,
	अणु 4, BGMAC_TX_MULTIPLE_COLS, "tx_multiple_cols" पूर्ण,
	अणु 4, BGMAC_TX_EXCESSIVE_COLS, "tx_excessive_cols" पूर्ण,
	अणु 4, BGMAC_TX_LATE_COLS, "tx_late_cols" पूर्ण,
	अणु 4, BGMAC_TX_DEFERED, "tx_defered" पूर्ण,
	अणु 4, BGMAC_TX_CARRIER_LOST, "tx_carrier_lost" पूर्ण,
	अणु 4, BGMAC_TX_PAUSE_PKTS, "tx_pause" पूर्ण,
	अणु 4, BGMAC_TX_UNI_PKTS, "tx_unicast" पूर्ण,
	अणु 4, BGMAC_TX_Q0_PKTS, "tx_q0" पूर्ण,
	अणु 8, BGMAC_TX_Q0_OCTETS, "tx_q0_octets" पूर्ण,
	अणु 4, BGMAC_TX_Q1_PKTS, "tx_q1" पूर्ण,
	अणु 8, BGMAC_TX_Q1_OCTETS, "tx_q1_octets" पूर्ण,
	अणु 4, BGMAC_TX_Q2_PKTS, "tx_q2" पूर्ण,
	अणु 8, BGMAC_TX_Q2_OCTETS, "tx_q2_octets" पूर्ण,
	अणु 4, BGMAC_TX_Q3_PKTS, "tx_q3" पूर्ण,
	अणु 8, BGMAC_TX_Q3_OCTETS, "tx_q3_octets" पूर्ण,
	अणु 8, BGMAC_RX_GOOD_OCTETS, "rx_good_octets" पूर्ण,
	अणु 4, BGMAC_RX_GOOD_PKTS, "rx_good" पूर्ण,
	अणु 8, BGMAC_RX_OCTETS, "rx_octets" पूर्ण,
	अणु 4, BGMAC_RX_PKTS, "rx_pkts" पूर्ण,
	अणु 4, BGMAC_RX_BROADCAST_PKTS, "rx_broadcast" पूर्ण,
	अणु 4, BGMAC_RX_MULTICAST_PKTS, "rx_multicast" पूर्ण,
	अणु 4, BGMAC_RX_LEN_64, "rx_64" पूर्ण,
	अणु 4, BGMAC_RX_LEN_65_TO_127, "rx_65_127" पूर्ण,
	अणु 4, BGMAC_RX_LEN_128_TO_255, "rx_128_255" पूर्ण,
	अणु 4, BGMAC_RX_LEN_256_TO_511, "rx_256_511" पूर्ण,
	अणु 4, BGMAC_RX_LEN_512_TO_1023, "rx_512_1023" पूर्ण,
	अणु 4, BGMAC_RX_LEN_1024_TO_1522, "rx_1024_1522" पूर्ण,
	अणु 4, BGMAC_RX_LEN_1523_TO_2047, "rx_1523_2047" पूर्ण,
	अणु 4, BGMAC_RX_LEN_2048_TO_4095, "rx_2048_4095" पूर्ण,
	अणु 4, BGMAC_RX_LEN_4096_TO_8191, "rx_4096_8191" पूर्ण,
	अणु 4, BGMAC_RX_LEN_8192_TO_MAX, "rx_8192_max" पूर्ण,
	अणु 4, BGMAC_RX_JABBER_PKTS, "rx_jabber" पूर्ण,
	अणु 4, BGMAC_RX_OVERSIZE_PKTS, "rx_oversize" पूर्ण,
	अणु 4, BGMAC_RX_FRAGMENT_PKTS, "rx_fragment" पूर्ण,
	अणु 4, BGMAC_RX_MISSED_PKTS, "rx_missed" पूर्ण,
	अणु 4, BGMAC_RX_CRC_ALIGN_ERRS, "rx_crc_align" पूर्ण,
	अणु 4, BGMAC_RX_UNDERSIZE, "rx_undersize" पूर्ण,
	अणु 4, BGMAC_RX_CRC_ERRS, "rx_crc" पूर्ण,
	अणु 4, BGMAC_RX_ALIGN_ERRS, "rx_align" पूर्ण,
	अणु 4, BGMAC_RX_SYMBOL_ERRS, "rx_symbol" पूर्ण,
	अणु 4, BGMAC_RX_PAUSE_PKTS, "rx_pause" पूर्ण,
	अणु 4, BGMAC_RX_NONPAUSE_PKTS, "rx_nonpause" पूर्ण,
	अणु 4, BGMAC_RX_SACHANGES, "rx_sa_changes" पूर्ण,
	अणु 4, BGMAC_RX_UNI_PKTS, "rx_unicast" पूर्ण,
पूर्ण;

#घोषणा BGMAC_STATS_LEN	ARRAY_SIZE(bgmac_get_strings_stats)

अटल पूर्णांक bgmac_get_sset_count(काष्ठा net_device *dev, पूर्णांक string_set)
अणु
	चयन (string_set) अणु
	हाल ETH_SS_STATS:
		वापस BGMAC_STATS_LEN;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम bgmac_get_strings(काष्ठा net_device *dev, u32 stringset,
			      u8 *data)
अणु
	पूर्णांक i;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (i = 0; i < BGMAC_STATS_LEN; i++)
		strlcpy(data + i * ETH_GSTRING_LEN,
			bgmac_get_strings_stats[i].name, ETH_GSTRING_LEN);
पूर्ण

अटल व्योम bgmac_get_ethtool_stats(काष्ठा net_device *dev,
				    काष्ठा ethtool_stats *ss, uपूर्णांक64_t *data)
अणु
	काष्ठा bgmac *bgmac = netdev_priv(dev);
	स्थिर काष्ठा bgmac_stat *s;
	अचिन्हित पूर्णांक i;
	u64 val;

	अगर (!netअगर_running(dev))
		वापस;

	क्रम (i = 0; i < BGMAC_STATS_LEN; i++) अणु
		s = &bgmac_get_strings_stats[i];
		val = 0;
		अगर (s->size == 8)
			val = (u64)bgmac_पढ़ो(bgmac, s->offset + 4) << 32;
		val |= bgmac_पढ़ो(bgmac, s->offset);
		data[i] = val;
	पूर्ण
पूर्ण

अटल व्योम bgmac_get_drvinfo(काष्ठा net_device *net_dev,
			      काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, KBUILD_MODNAME, माप(info->driver));
	strlcpy(info->bus_info, "AXI", माप(info->bus_info));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops bgmac_ethtool_ops = अणु
	.get_strings		= bgmac_get_strings,
	.get_sset_count		= bgmac_get_sset_count,
	.get_ethtool_stats	= bgmac_get_ethtool_stats,
	.get_drvinfo		= bgmac_get_drvinfo,
	.get_link_ksettings     = phy_ethtool_get_link_ksettings,
	.set_link_ksettings     = phy_ethtool_set_link_ksettings,
पूर्ण;

/**************************************************
 * MII
 **************************************************/

व्योम bgmac_adjust_link(काष्ठा net_device *net_dev)
अणु
	काष्ठा bgmac *bgmac = netdev_priv(net_dev);
	काष्ठा phy_device *phy_dev = net_dev->phydev;
	bool update = false;

	अगर (phy_dev->link) अणु
		अगर (phy_dev->speed != bgmac->mac_speed) अणु
			bgmac->mac_speed = phy_dev->speed;
			update = true;
		पूर्ण

		अगर (phy_dev->duplex != bgmac->mac_duplex) अणु
			bgmac->mac_duplex = phy_dev->duplex;
			update = true;
		पूर्ण
	पूर्ण

	अगर (update) अणु
		bgmac_mac_speed(bgmac);
		phy_prपूर्णांक_status(phy_dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(bgmac_adjust_link);

पूर्णांक bgmac_phy_connect_direct(काष्ठा bgmac *bgmac)
अणु
	काष्ठा fixed_phy_status fphy_status = अणु
		.link = 1,
		.speed = SPEED_1000,
		.duplex = DUPLEX_FULL,
	पूर्ण;
	काष्ठा phy_device *phy_dev;
	पूर्णांक err;

	phy_dev = fixed_phy_रेजिस्टर(PHY_POLL, &fphy_status, शून्य);
	अगर (!phy_dev || IS_ERR(phy_dev)) अणु
		dev_err(bgmac->dev, "Failed to register fixed PHY device\n");
		वापस -ENODEV;
	पूर्ण

	err = phy_connect_direct(bgmac->net_dev, phy_dev, bgmac_adjust_link,
				 PHY_INTERFACE_MODE_MII);
	अगर (err) अणु
		dev_err(bgmac->dev, "Connecting PHY failed\n");
		वापस err;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(bgmac_phy_connect_direct);

काष्ठा bgmac *bgmac_alloc(काष्ठा device *dev)
अणु
	काष्ठा net_device *net_dev;
	काष्ठा bgmac *bgmac;

	/* Allocation and references */
	net_dev = devm_alloc_etherdev(dev, माप(*bgmac));
	अगर (!net_dev)
		वापस शून्य;

	net_dev->netdev_ops = &bgmac_netdev_ops;
	net_dev->ethtool_ops = &bgmac_ethtool_ops;

	bgmac = netdev_priv(net_dev);
	bgmac->dev = dev;
	bgmac->net_dev = net_dev;

	वापस bgmac;
पूर्ण
EXPORT_SYMBOL_GPL(bgmac_alloc);

पूर्णांक bgmac_enet_probe(काष्ठा bgmac *bgmac)
अणु
	काष्ठा net_device *net_dev = bgmac->net_dev;
	पूर्णांक err;

	bgmac_chip_पूर्णांकrs_off(bgmac);

	net_dev->irq = bgmac->irq;
	SET_NETDEV_DEV(net_dev, bgmac->dev);
	dev_set_drvdata(bgmac->dev, bgmac);

	अगर (!is_valid_ether_addr(net_dev->dev_addr)) अणु
		dev_err(bgmac->dev, "Invalid MAC addr: %pM\n",
			net_dev->dev_addr);
		eth_hw_addr_अक्रमom(net_dev);
		dev_warn(bgmac->dev, "Using random MAC: %pM\n",
			 net_dev->dev_addr);
	पूर्ण

	/* This (reset &) enable is not preset in specs or reference driver but
	 * Broadcom करोes it in arch PCI code when enabling fake PCI device.
	 */
	bgmac_clk_enable(bgmac, 0);

	/* This seems to be fixing IRQ by assigning OOB #6 to the core */
	अगर (!(bgmac->feature_flags & BGMAC_FEAT_IDM_MASK)) अणु
		अगर (bgmac->feature_flags & BGMAC_FEAT_IRQ_ID_OOB_6)
			bgmac_idm_ग_लिखो(bgmac, BCMA_OOB_SEL_OUT_A30, 0x86);
	पूर्ण

	bgmac_chip_reset(bgmac);

	err = bgmac_dma_alloc(bgmac);
	अगर (err) अणु
		dev_err(bgmac->dev, "Unable to alloc memory for DMA\n");
		जाओ err_out;
	पूर्ण

	bgmac->पूर्णांक_mask = BGMAC_IS_ERRMASK | BGMAC_IS_RX | BGMAC_IS_TX_MASK;
	अगर (bcm47xx_nvram_दो_पर्या("et0_no_txint", शून्य, 0) == 0)
		bgmac->पूर्णांक_mask &= ~BGMAC_IS_TX_MASK;

	netअगर_napi_add(net_dev, &bgmac->napi, bgmac_poll, BGMAC_WEIGHT);

	err = bgmac_phy_connect(bgmac);
	अगर (err) अणु
		dev_err(bgmac->dev, "Cannot connect to phy\n");
		जाओ err_dma_मुक्त;
	पूर्ण

	net_dev->features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	net_dev->hw_features = net_dev->features;
	net_dev->vlan_features = net_dev->features;

	/* Omit FCS from max MTU size */
	net_dev->max_mtu = BGMAC_RX_MAX_FRAME_SIZE - ETH_FCS_LEN;

	err = रेजिस्टर_netdev(bgmac->net_dev);
	अगर (err) अणु
		dev_err(bgmac->dev, "Cannot register net device\n");
		जाओ err_phy_disconnect;
	पूर्ण

	netअगर_carrier_off(net_dev);

	वापस 0;

err_phy_disconnect:
	phy_disconnect(net_dev->phydev);
err_dma_मुक्त:
	bgmac_dma_मुक्त(bgmac);
err_out:

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(bgmac_enet_probe);

व्योम bgmac_enet_हटाओ(काष्ठा bgmac *bgmac)
अणु
	unरेजिस्टर_netdev(bgmac->net_dev);
	phy_disconnect(bgmac->net_dev->phydev);
	netअगर_napi_del(&bgmac->napi);
	bgmac_dma_मुक्त(bgmac);
	मुक्त_netdev(bgmac->net_dev);
पूर्ण
EXPORT_SYMBOL_GPL(bgmac_enet_हटाओ);

पूर्णांक bgmac_enet_suspend(काष्ठा bgmac *bgmac)
अणु
	अगर (!netअगर_running(bgmac->net_dev))
		वापस 0;

	phy_stop(bgmac->net_dev->phydev);

	netअगर_stop_queue(bgmac->net_dev);

	napi_disable(&bgmac->napi);

	netअगर_tx_lock(bgmac->net_dev);
	netअगर_device_detach(bgmac->net_dev);
	netअगर_tx_unlock(bgmac->net_dev);

	bgmac_chip_पूर्णांकrs_off(bgmac);
	bgmac_chip_reset(bgmac);
	bgmac_dma_cleanup(bgmac);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bgmac_enet_suspend);

पूर्णांक bgmac_enet_resume(काष्ठा bgmac *bgmac)
अणु
	पूर्णांक rc;

	अगर (!netअगर_running(bgmac->net_dev))
		वापस 0;

	rc = bgmac_dma_init(bgmac);
	अगर (rc)
		वापस rc;

	bgmac_chip_init(bgmac);

	napi_enable(&bgmac->napi);

	netअगर_tx_lock(bgmac->net_dev);
	netअगर_device_attach(bgmac->net_dev);
	netअगर_tx_unlock(bgmac->net_dev);

	netअगर_start_queue(bgmac->net_dev);

	phy_start(bgmac->net_dev->phydev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bgmac_enet_resume);

MODULE_AUTHOR("Rafaध Miधecki");
MODULE_LICENSE("GPL");
