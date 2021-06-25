<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2019 Intel Corporation. */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip.h>
#समावेश <net/tcp.h>
#समावेश <linux/अगर_macvlan.h>
#समावेश <linux/prefetch.h>

#समावेश "fm10k.h"

#घोषणा DRV_SUMMARY	"Intel(R) Ethernet Switch Host Interface Driver"
अक्षर fm10k_driver_name[] = "fm10k";
अटल स्थिर अक्षर fm10k_driver_string[] = DRV_SUMMARY;
अटल स्थिर अक्षर fm10k_copyright[] =
	"Copyright(c) 2013 - 2019 Intel Corporation.";

MODULE_AUTHOR("Intel Corporation, <linux.nics@intel.com>");
MODULE_DESCRIPTION(DRV_SUMMARY);
MODULE_LICENSE("GPL v2");

/* single workqueue क्रम entire fm10k driver */
काष्ठा workqueue_काष्ठा *fm10k_workqueue;

/**
 * fm10k_init_module - Driver Registration Routine
 *
 * fm10k_init_module is the first routine called when the driver is
 * loaded.  All it करोes is रेजिस्टर with the PCI subप्रणाली.
 **/
अटल पूर्णांक __init fm10k_init_module(व्योम)
अणु
	pr_info("%s\n", fm10k_driver_string);
	pr_info("%s\n", fm10k_copyright);

	/* create driver workqueue */
	fm10k_workqueue = alloc_workqueue("%s", WQ_MEM_RECLAIM, 0,
					  fm10k_driver_name);
	अगर (!fm10k_workqueue)
		वापस -ENOMEM;

	fm10k_dbg_init();

	वापस fm10k_रेजिस्टर_pci_driver();
पूर्ण
module_init(fm10k_init_module);

/**
 * fm10k_निकास_module - Driver Exit Cleanup Routine
 *
 * fm10k_निकास_module is called just beक्रमe the driver is हटाओd
 * from memory.
 **/
अटल व्योम __निकास fm10k_निकास_module(व्योम)
अणु
	fm10k_unरेजिस्टर_pci_driver();

	fm10k_dbg_निकास();

	/* destroy driver workqueue */
	destroy_workqueue(fm10k_workqueue);
पूर्ण
module_निकास(fm10k_निकास_module);

अटल bool fm10k_alloc_mapped_page(काष्ठा fm10k_ring *rx_ring,
				    काष्ठा fm10k_rx_buffer *bi)
अणु
	काष्ठा page *page = bi->page;
	dma_addr_t dma;

	/* Only page will be शून्य अगर buffer was consumed */
	अगर (likely(page))
		वापस true;

	/* alloc new page क्रम storage */
	page = dev_alloc_page();
	अगर (unlikely(!page)) अणु
		rx_ring->rx_stats.alloc_failed++;
		वापस false;
	पूर्ण

	/* map page क्रम use */
	dma = dma_map_page(rx_ring->dev, page, 0, PAGE_SIZE, DMA_FROM_DEVICE);

	/* अगर mapping failed मुक्त memory back to प्रणाली since
	 * there isn't much point in holding memory we can't use
	 */
	अगर (dma_mapping_error(rx_ring->dev, dma)) अणु
		__मुक्त_page(page);

		rx_ring->rx_stats.alloc_failed++;
		वापस false;
	पूर्ण

	bi->dma = dma;
	bi->page = page;
	bi->page_offset = 0;

	वापस true;
पूर्ण

/**
 * fm10k_alloc_rx_buffers - Replace used receive buffers
 * @rx_ring: ring to place buffers on
 * @cleaned_count: number of buffers to replace
 **/
व्योम fm10k_alloc_rx_buffers(काष्ठा fm10k_ring *rx_ring, u16 cleaned_count)
अणु
	जोड़ fm10k_rx_desc *rx_desc;
	काष्ठा fm10k_rx_buffer *bi;
	u16 i = rx_ring->next_to_use;

	/* nothing to करो */
	अगर (!cleaned_count)
		वापस;

	rx_desc = FM10K_RX_DESC(rx_ring, i);
	bi = &rx_ring->rx_buffer[i];
	i -= rx_ring->count;

	करो अणु
		अगर (!fm10k_alloc_mapped_page(rx_ring, bi))
			अवरोध;

		/* Refresh the desc even अगर buffer_addrs didn't change
		 * because each ग_लिखो-back erases this info.
		 */
		rx_desc->q.pkt_addr = cpu_to_le64(bi->dma + bi->page_offset);

		rx_desc++;
		bi++;
		i++;
		अगर (unlikely(!i)) अणु
			rx_desc = FM10K_RX_DESC(rx_ring, 0);
			bi = rx_ring->rx_buffer;
			i -= rx_ring->count;
		पूर्ण

		/* clear the status bits क्रम the next_to_use descriptor */
		rx_desc->d.staterr = 0;

		cleaned_count--;
	पूर्ण जबतक (cleaned_count);

	i += rx_ring->count;

	अगर (rx_ring->next_to_use != i) अणु
		/* record the next descriptor to use */
		rx_ring->next_to_use = i;

		/* update next to alloc since we have filled the ring */
		rx_ring->next_to_alloc = i;

		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable क्रम weak-ordered memory model archs,
		 * such as IA-64).
		 */
		wmb();

		/* notअगरy hardware of new descriptors */
		ग_लिखोl(i, rx_ring->tail);
	पूर्ण
पूर्ण

/**
 * fm10k_reuse_rx_page - page flip buffer and store it back on the ring
 * @rx_ring: rx descriptor ring to store buffers on
 * @old_buff: करोnor buffer to have page reused
 *
 * Synchronizes page क्रम reuse by the पूर्णांकerface
 **/
अटल व्योम fm10k_reuse_rx_page(काष्ठा fm10k_ring *rx_ring,
				काष्ठा fm10k_rx_buffer *old_buff)
अणु
	काष्ठा fm10k_rx_buffer *new_buff;
	u16 nta = rx_ring->next_to_alloc;

	new_buff = &rx_ring->rx_buffer[nta];

	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* transfer page from old buffer to new buffer */
	*new_buff = *old_buff;

	/* sync the buffer क्रम use by the device */
	dma_sync_single_range_क्रम_device(rx_ring->dev, old_buff->dma,
					 old_buff->page_offset,
					 FM10K_RX_BUFSZ,
					 DMA_FROM_DEVICE);
पूर्ण

अटल bool fm10k_can_reuse_rx_page(काष्ठा fm10k_rx_buffer *rx_buffer,
				    काष्ठा page *page,
				    अचिन्हित पूर्णांक __maybe_unused truesize)
अणु
	/* aव्योम re-using remote and pfmeदो_स्मृति pages */
	अगर (!dev_page_is_reusable(page))
		वापस false;

#अगर (PAGE_SIZE < 8192)
	/* अगर we are only owner of page we can reuse it */
	अगर (unlikely(page_count(page) != 1))
		वापस false;

	/* flip page offset to other buffer */
	rx_buffer->page_offset ^= FM10K_RX_BUFSZ;
#अन्यथा
	/* move offset up to the next cache line */
	rx_buffer->page_offset += truesize;

	अगर (rx_buffer->page_offset > (PAGE_SIZE - FM10K_RX_BUFSZ))
		वापस false;
#पूर्ण_अगर

	/* Even अगर we own the page, we are not allowed to use atomic_set()
	 * This would अवरोध get_page_unless_zero() users.
	 */
	page_ref_inc(page);

	वापस true;
पूर्ण

/**
 * fm10k_add_rx_frag - Add contents of Rx buffer to sk_buff
 * @rx_buffer: buffer containing page to add
 * @size: packet size from rx_desc
 * @rx_desc: descriptor containing length of buffer written by hardware
 * @skb: sk_buff to place the data पूर्णांकo
 *
 * This function will add the data contained in rx_buffer->page to the skb.
 * This is करोne either through a direct copy अगर the data in the buffer is
 * less than the skb header size, otherwise it will just attach the page as
 * a frag to the skb.
 *
 * The function will then update the page offset अगर necessary and वापस
 * true अगर the buffer can be reused by the पूर्णांकerface.
 **/
अटल bool fm10k_add_rx_frag(काष्ठा fm10k_rx_buffer *rx_buffer,
			      अचिन्हित पूर्णांक size,
			      जोड़ fm10k_rx_desc *rx_desc,
			      काष्ठा sk_buff *skb)
अणु
	काष्ठा page *page = rx_buffer->page;
	अचिन्हित अक्षर *va = page_address(page) + rx_buffer->page_offset;
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = FM10K_RX_BUFSZ;
#अन्यथा
	अचिन्हित पूर्णांक truesize = ALIGN(size, 512);
#पूर्ण_अगर
	अचिन्हित पूर्णांक pull_len;

	अगर (unlikely(skb_is_nonlinear(skb)))
		जाओ add_tail_frag;

	अगर (likely(size <= FM10K_RX_HDR_LEN)) अणु
		स_नकल(__skb_put(skb, size), va, ALIGN(size, माप(दीर्घ)));

		/* page is reusable, we can reuse buffer as-is */
		अगर (dev_page_is_reusable(page))
			वापस true;

		/* this page cannot be reused so discard it */
		__मुक्त_page(page);
		वापस false;
	पूर्ण

	/* we need the header to contain the greater of either ETH_HLEN or
	 * 60 bytes अगर the skb->len is less than 60 क्रम skb_pad.
	 */
	pull_len = eth_get_headlen(skb->dev, va, FM10K_RX_HDR_LEN);

	/* align pull length to size of दीर्घ to optimize स_नकल perक्रमmance */
	स_नकल(__skb_put(skb, pull_len), va, ALIGN(pull_len, माप(दीर्घ)));

	/* update all of the poपूर्णांकers */
	va += pull_len;
	size -= pull_len;

add_tail_frag:
	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, page,
			(अचिन्हित दीर्घ)va & ~PAGE_MASK, size, truesize);

	वापस fm10k_can_reuse_rx_page(rx_buffer, page, truesize);
पूर्ण

अटल काष्ठा sk_buff *fm10k_fetch_rx_buffer(काष्ठा fm10k_ring *rx_ring,
					     जोड़ fm10k_rx_desc *rx_desc,
					     काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक size = le16_to_cpu(rx_desc->w.length);
	काष्ठा fm10k_rx_buffer *rx_buffer;
	काष्ठा page *page;

	rx_buffer = &rx_ring->rx_buffer[rx_ring->next_to_clean];
	page = rx_buffer->page;
	prefetchw(page);

	अगर (likely(!skb)) अणु
		व्योम *page_addr = page_address(page) +
				  rx_buffer->page_offset;

		/* prefetch first cache line of first page */
		net_prefetch(page_addr);

		/* allocate a skb to store the frags */
		skb = napi_alloc_skb(&rx_ring->q_vector->napi,
				     FM10K_RX_HDR_LEN);
		अगर (unlikely(!skb)) अणु
			rx_ring->rx_stats.alloc_failed++;
			वापस शून्य;
		पूर्ण

		/* we will be copying header पूर्णांकo skb->data in
		 * pskb_may_pull so it is in our पूर्णांकerest to prefetch
		 * it now to aव्योम a possible cache miss
		 */
		prefetchw(skb->data);
	पूर्ण

	/* we are reusing so sync this buffer क्रम CPU use */
	dma_sync_single_range_क्रम_cpu(rx_ring->dev,
				      rx_buffer->dma,
				      rx_buffer->page_offset,
				      size,
				      DMA_FROM_DEVICE);

	/* pull page पूर्णांकo skb */
	अगर (fm10k_add_rx_frag(rx_buffer, size, rx_desc, skb)) अणु
		/* hand second half of page back to the ring */
		fm10k_reuse_rx_page(rx_ring, rx_buffer);
	पूर्ण अन्यथा अणु
		/* we are not reusing the buffer so unmap it */
		dma_unmap_page(rx_ring->dev, rx_buffer->dma,
			       PAGE_SIZE, DMA_FROM_DEVICE);
	पूर्ण

	/* clear contents of rx_buffer */
	rx_buffer->page = शून्य;

	वापस skb;
पूर्ण

अटल अंतरभूत व्योम fm10k_rx_checksum(काष्ठा fm10k_ring *ring,
				     जोड़ fm10k_rx_desc *rx_desc,
				     काष्ठा sk_buff *skb)
अणु
	skb_checksum_none_निश्चित(skb);

	/* Rx checksum disabled via ethtool */
	अगर (!(ring->netdev->features & NETIF_F_RXCSUM))
		वापस;

	/* TCP/UDP checksum error bit is set */
	अगर (fm10k_test_staterr(rx_desc,
			       FM10K_RXD_STATUS_L4E |
			       FM10K_RXD_STATUS_L4E2 |
			       FM10K_RXD_STATUS_IPE |
			       FM10K_RXD_STATUS_IPE2)) अणु
		ring->rx_stats.csum_err++;
		वापस;
	पूर्ण

	/* It must be a TCP or UDP packet with a valid checksum */
	अगर (fm10k_test_staterr(rx_desc, FM10K_RXD_STATUS_L4CS2))
		skb->encapsulation = true;
	अन्यथा अगर (!fm10k_test_staterr(rx_desc, FM10K_RXD_STATUS_L4CS))
		वापस;

	skb->ip_summed = CHECKSUM_UNNECESSARY;

	ring->rx_stats.csum_good++;
पूर्ण

#घोषणा FM10K_RSS_L4_TYPES_MASK \
	(BIT(FM10K_RSSTYPE_IPV4_TCP) | \
	 BIT(FM10K_RSSTYPE_IPV4_UDP) | \
	 BIT(FM10K_RSSTYPE_IPV6_TCP) | \
	 BIT(FM10K_RSSTYPE_IPV6_UDP))

अटल अंतरभूत व्योम fm10k_rx_hash(काष्ठा fm10k_ring *ring,
				 जोड़ fm10k_rx_desc *rx_desc,
				 काष्ठा sk_buff *skb)
अणु
	u16 rss_type;

	अगर (!(ring->netdev->features & NETIF_F_RXHASH))
		वापस;

	rss_type = le16_to_cpu(rx_desc->w.pkt_info) & FM10K_RXD_RSSTYPE_MASK;
	अगर (!rss_type)
		वापस;

	skb_set_hash(skb, le32_to_cpu(rx_desc->d.rss),
		     (BIT(rss_type) & FM10K_RSS_L4_TYPES_MASK) ?
		     PKT_HASH_TYPE_L4 : PKT_HASH_TYPE_L3);
पूर्ण

अटल व्योम fm10k_type_trans(काष्ठा fm10k_ring *rx_ring,
			     जोड़ fm10k_rx_desc __maybe_unused *rx_desc,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = rx_ring->netdev;
	काष्ठा fm10k_l2_accel *l2_accel = rcu_dereference_bh(rx_ring->l2_accel);

	/* check to see अगर DGLORT beदीर्घs to a MACVLAN */
	अगर (l2_accel) अणु
		u16 idx = le16_to_cpu(FM10K_CB(skb)->fi.w.dglort) - 1;

		idx -= l2_accel->dglort;
		अगर (idx < l2_accel->size && l2_accel->macvlan[idx])
			dev = l2_accel->macvlan[idx];
		अन्यथा
			l2_accel = शून्य;
	पूर्ण

	/* Record Rx queue, or update macvlan statistics */
	अगर (!l2_accel)
		skb_record_rx_queue(skb, rx_ring->queue_index);
	अन्यथा
		macvlan_count_rx(netdev_priv(dev), skb->len + ETH_HLEN, true,
				 false);

	skb->protocol = eth_type_trans(skb, dev);
पूर्ण

/**
 * fm10k_process_skb_fields - Populate skb header fields from Rx descriptor
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 * @skb: poपूर्णांकer to current skb being populated
 *
 * This function checks the ring, descriptor, and packet inक्रमmation in
 * order to populate the hash, checksum, VLAN, बारtamp, protocol, and
 * other fields within the skb.
 **/
अटल अचिन्हित पूर्णांक fm10k_process_skb_fields(काष्ठा fm10k_ring *rx_ring,
					     जोड़ fm10k_rx_desc *rx_desc,
					     काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक len = skb->len;

	fm10k_rx_hash(rx_ring, rx_desc, skb);

	fm10k_rx_checksum(rx_ring, rx_desc, skb);

	FM10K_CB(skb)->tstamp = rx_desc->q.बारtamp;

	FM10K_CB(skb)->fi.w.vlan = rx_desc->w.vlan;

	FM10K_CB(skb)->fi.d.glort = rx_desc->d.glort;

	अगर (rx_desc->w.vlan) अणु
		u16 vid = le16_to_cpu(rx_desc->w.vlan);

		अगर ((vid & VLAN_VID_MASK) != rx_ring->vid)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
		अन्यथा अगर (vid & VLAN_PRIO_MASK)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       vid & VLAN_PRIO_MASK);
	पूर्ण

	fm10k_type_trans(rx_ring, rx_desc, skb);

	वापस len;
पूर्ण

/**
 * fm10k_is_non_eop - process handling of non-EOP buffers
 * @rx_ring: Rx ring being processed
 * @rx_desc: Rx descriptor क्रम current buffer
 *
 * This function updates next to clean.  If the buffer is an EOP buffer
 * this function निकासs वापसing false, otherwise it will place the
 * sk_buff in the next buffer to be chained and वापस true indicating
 * that this is in fact a non-EOP buffer.
 **/
अटल bool fm10k_is_non_eop(काष्ठा fm10k_ring *rx_ring,
			     जोड़ fm10k_rx_desc *rx_desc)
अणु
	u32 ntc = rx_ring->next_to_clean + 1;

	/* fetch, update, and store next to clean */
	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;

	prefetch(FM10K_RX_DESC(rx_ring, ntc));

	अगर (likely(fm10k_test_staterr(rx_desc, FM10K_RXD_STATUS_EOP)))
		वापस false;

	वापस true;
पूर्ण

/**
 * fm10k_cleanup_headers - Correct corrupted or empty headers
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 * @skb: poपूर्णांकer to current skb being fixed
 *
 * Address the हाल where we are pulling data in on pages only
 * and as such no data is present in the skb header.
 *
 * In addition अगर skb is not at least 60 bytes we need to pad it so that
 * it is large enough to qualअगरy as a valid Ethernet frame.
 *
 * Returns true अगर an error was encountered and skb was मुक्तd.
 **/
अटल bool fm10k_cleanup_headers(काष्ठा fm10k_ring *rx_ring,
				  जोड़ fm10k_rx_desc *rx_desc,
				  काष्ठा sk_buff *skb)
अणु
	अगर (unlikely((fm10k_test_staterr(rx_desc,
					 FM10K_RXD_STATUS_RXE)))) अणु
#घोषणा FM10K_TEST_RXD_BIT(rxd, bit) \
	((rxd)->w.csum_err & cpu_to_le16(bit))
		अगर (FM10K_TEST_RXD_BIT(rx_desc, FM10K_RXD_ERR_SWITCH_ERROR))
			rx_ring->rx_stats.चयन_errors++;
		अगर (FM10K_TEST_RXD_BIT(rx_desc, FM10K_RXD_ERR_NO_DESCRIPTOR))
			rx_ring->rx_stats.drops++;
		अगर (FM10K_TEST_RXD_BIT(rx_desc, FM10K_RXD_ERR_PP_ERROR))
			rx_ring->rx_stats.pp_errors++;
		अगर (FM10K_TEST_RXD_BIT(rx_desc, FM10K_RXD_ERR_SWITCH_READY))
			rx_ring->rx_stats.link_errors++;
		अगर (FM10K_TEST_RXD_BIT(rx_desc, FM10K_RXD_ERR_TOO_BIG))
			rx_ring->rx_stats.length_errors++;
		dev_kमुक्त_skb_any(skb);
		rx_ring->rx_stats.errors++;
		वापस true;
	पूर्ण

	/* अगर eth_skb_pad वापसs an error the skb was मुक्तd */
	अगर (eth_skb_pad(skb))
		वापस true;

	वापस false;
पूर्ण

/**
 * fm10k_receive_skb - helper function to handle rx indications
 * @q_vector: काष्ठाure containing पूर्णांकerrupt and ring inक्रमmation
 * @skb: packet to send up
 **/
अटल व्योम fm10k_receive_skb(काष्ठा fm10k_q_vector *q_vector,
			      काष्ठा sk_buff *skb)
अणु
	napi_gro_receive(&q_vector->napi, skb);
पूर्ण

अटल पूर्णांक fm10k_clean_rx_irq(काष्ठा fm10k_q_vector *q_vector,
			      काष्ठा fm10k_ring *rx_ring,
			      पूर्णांक budget)
अणु
	काष्ठा sk_buff *skb = rx_ring->skb;
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0;
	u16 cleaned_count = fm10k_desc_unused(rx_ring);

	जबतक (likely(total_packets < budget)) अणु
		जोड़ fm10k_rx_desc *rx_desc;

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (cleaned_count >= FM10K_RX_BUFFER_WRITE) अणु
			fm10k_alloc_rx_buffers(rx_ring, cleaned_count);
			cleaned_count = 0;
		पूर्ण

		rx_desc = FM10K_RX_DESC(rx_ring, rx_ring->next_to_clean);

		अगर (!rx_desc->d.staterr)
			अवरोध;

		/* This memory barrier is needed to keep us from पढ़ोing
		 * any other fields out of the rx_desc until we know the
		 * descriptor has been written back
		 */
		dma_rmb();

		/* retrieve a buffer from the ring */
		skb = fm10k_fetch_rx_buffer(rx_ring, rx_desc, skb);

		/* निकास अगर we failed to retrieve a buffer */
		अगर (!skb)
			अवरोध;

		cleaned_count++;

		/* fetch next buffer in frame अगर non-eop */
		अगर (fm10k_is_non_eop(rx_ring, rx_desc))
			जारी;

		/* verअगरy the packet layout is correct */
		अगर (fm10k_cleanup_headers(rx_ring, rx_desc, skb)) अणु
			skb = शून्य;
			जारी;
		पूर्ण

		/* populate checksum, बारtamp, VLAN, and protocol */
		total_bytes += fm10k_process_skb_fields(rx_ring, rx_desc, skb);

		fm10k_receive_skb(q_vector, skb);

		/* reset skb poपूर्णांकer */
		skb = शून्य;

		/* update budget accounting */
		total_packets++;
	पूर्ण

	/* place incomplete frames back on ring क्रम completion */
	rx_ring->skb = skb;

	u64_stats_update_begin(&rx_ring->syncp);
	rx_ring->stats.packets += total_packets;
	rx_ring->stats.bytes += total_bytes;
	u64_stats_update_end(&rx_ring->syncp);
	q_vector->rx.total_packets += total_packets;
	q_vector->rx.total_bytes += total_bytes;

	वापस total_packets;
पूर्ण

#घोषणा VXLAN_HLEN (माप(काष्ठा udphdr) + 8)
अटल काष्ठा ethhdr *fm10k_port_is_vxlan(काष्ठा sk_buff *skb)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = netdev_priv(skb->dev);

	अगर (पूर्णांकerface->vxlan_port != udp_hdr(skb)->dest)
		वापस शून्य;

	/* वापस offset of udp_hdr plus 8 bytes क्रम VXLAN header */
	वापस (काष्ठा ethhdr *)(skb_transport_header(skb) + VXLAN_HLEN);
पूर्ण

#घोषणा FM10K_NVGRE_RESERVED0_FLAGS htons(0x9FFF)
#घोषणा NVGRE_TNI htons(0x2000)
काष्ठा fm10k_nvgre_hdr अणु
	__be16 flags;
	__be16 proto;
	__be32 tni;
पूर्ण;

अटल काष्ठा ethhdr *fm10k_gre_is_nvgre(काष्ठा sk_buff *skb)
अणु
	काष्ठा fm10k_nvgre_hdr *nvgre_hdr;
	पूर्णांक hlen = ip_hdrlen(skb);

	/* currently only IPv4 is supported due to hlen above */
	अगर (vlan_get_protocol(skb) != htons(ETH_P_IP))
		वापस शून्य;

	/* our transport header should be NVGRE */
	nvgre_hdr = (काष्ठा fm10k_nvgre_hdr *)(skb_network_header(skb) + hlen);

	/* verअगरy all reserved flags are 0 */
	अगर (nvgre_hdr->flags & FM10K_NVGRE_RESERVED0_FLAGS)
		वापस शून्य;

	/* report start of ethernet header */
	अगर (nvgre_hdr->flags & NVGRE_TNI)
		वापस (काष्ठा ethhdr *)(nvgre_hdr + 1);

	वापस (काष्ठा ethhdr *)(&nvgre_hdr->tni);
पूर्ण

__be16 fm10k_tx_encap_offload(काष्ठा sk_buff *skb)
अणु
	u8 l4_hdr = 0, inner_l4_hdr = 0, inner_l4_hlen;
	काष्ठा ethhdr *eth_hdr;

	अगर (skb->inner_protocol_type != ENCAP_TYPE_ETHER ||
	    skb->inner_protocol != htons(ETH_P_TEB))
		वापस 0;

	चयन (vlan_get_protocol(skb)) अणु
	हाल htons(ETH_P_IP):
		l4_hdr = ip_hdr(skb)->protocol;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		l4_hdr = ipv6_hdr(skb)->nexthdr;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	चयन (l4_hdr) अणु
	हाल IPPROTO_UDP:
		eth_hdr = fm10k_port_is_vxlan(skb);
		अवरोध;
	हाल IPPROTO_GRE:
		eth_hdr = fm10k_gre_is_nvgre(skb);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (!eth_hdr)
		वापस 0;

	चयन (eth_hdr->h_proto) अणु
	हाल htons(ETH_P_IP):
		inner_l4_hdr = inner_ip_hdr(skb)->protocol;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		inner_l4_hdr = inner_ipv6_hdr(skb)->nexthdr;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	चयन (inner_l4_hdr) अणु
	हाल IPPROTO_TCP:
		inner_l4_hlen = inner_tcp_hdrlen(skb);
		अवरोध;
	हाल IPPROTO_UDP:
		inner_l4_hlen = 8;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	/* The hardware allows tunnel offloads only अगर the combined inner and
	 * outer header is 184 bytes or less
	 */
	अगर (skb_inner_transport_header(skb) + inner_l4_hlen -
	    skb_mac_header(skb) > FM10K_TUNNEL_HEADER_LENGTH)
		वापस 0;

	वापस eth_hdr->h_proto;
पूर्ण

अटल पूर्णांक fm10k_tso(काष्ठा fm10k_ring *tx_ring,
		     काष्ठा fm10k_tx_buffer *first)
अणु
	काष्ठा sk_buff *skb = first->skb;
	काष्ठा fm10k_tx_desc *tx_desc;
	अचिन्हित अक्षर *th;
	u8 hdrlen;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	अगर (!skb_is_gso(skb))
		वापस 0;

	/* compute header lengths */
	अगर (skb->encapsulation) अणु
		अगर (!fm10k_tx_encap_offload(skb))
			जाओ err_vxlan;
		th = skb_inner_transport_header(skb);
	पूर्ण अन्यथा अणु
		th = skb_transport_header(skb);
	पूर्ण

	/* compute offset from SOF to transport header and add header len */
	hdrlen = (th - skb->data) + (((काष्ठा tcphdr *)th)->करोff << 2);

	first->tx_flags |= FM10K_TX_FLAGS_CSUM;

	/* update gso size and bytecount with header size */
	first->gso_segs = skb_shinfo(skb)->gso_segs;
	first->bytecount += (first->gso_segs - 1) * hdrlen;

	/* populate Tx descriptor header size and mss */
	tx_desc = FM10K_TX_DESC(tx_ring, tx_ring->next_to_use);
	tx_desc->hdrlen = hdrlen;
	tx_desc->mss = cpu_to_le16(skb_shinfo(skb)->gso_size);

	वापस 1;

err_vxlan:
	tx_ring->netdev->features &= ~NETIF_F_GSO_UDP_TUNNEL;
	अगर (net_ratelimit())
		netdev_err(tx_ring->netdev,
			   "TSO requested for unsupported tunnel, disabling offload\n");
	वापस -1;
पूर्ण

अटल व्योम fm10k_tx_csum(काष्ठा fm10k_ring *tx_ring,
			  काष्ठा fm10k_tx_buffer *first)
अणु
	काष्ठा sk_buff *skb = first->skb;
	काष्ठा fm10k_tx_desc *tx_desc;
	जोड़ अणु
		काष्ठा iphdr *ipv4;
		काष्ठा ipv6hdr *ipv6;
		u8 *raw;
	पूर्ण network_hdr;
	u8 *transport_hdr;
	__be16 frag_off;
	__be16 protocol;
	u8 l4_hdr = 0;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		जाओ no_csum;

	अगर (skb->encapsulation) अणु
		protocol = fm10k_tx_encap_offload(skb);
		अगर (!protocol) अणु
			अगर (skb_checksum_help(skb)) अणु
				dev_warn(tx_ring->dev,
					 "failed to offload encap csum!\n");
				tx_ring->tx_stats.csum_err++;
			पूर्ण
			जाओ no_csum;
		पूर्ण
		network_hdr.raw = skb_inner_network_header(skb);
		transport_hdr = skb_inner_transport_header(skb);
	पूर्ण अन्यथा अणु
		protocol = vlan_get_protocol(skb);
		network_hdr.raw = skb_network_header(skb);
		transport_hdr = skb_transport_header(skb);
	पूर्ण

	चयन (protocol) अणु
	हाल htons(ETH_P_IP):
		l4_hdr = network_hdr.ipv4->protocol;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		l4_hdr = network_hdr.ipv6->nexthdr;
		अगर (likely((transport_hdr - network_hdr.raw) ==
			   माप(काष्ठा ipv6hdr)))
			अवरोध;
		ipv6_skip_exthdr(skb, network_hdr.raw - skb->data +
				      माप(काष्ठा ipv6hdr),
				 &l4_hdr, &frag_off);
		अगर (unlikely(frag_off))
			l4_hdr = NEXTHDR_FRAGMENT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (l4_hdr) अणु
	हाल IPPROTO_TCP:
	हाल IPPROTO_UDP:
		अवरोध;
	हाल IPPROTO_GRE:
		अगर (skb->encapsulation)
			अवरोध;
		fallthrough;
	शेष:
		अगर (unlikely(net_ratelimit())) अणु
			dev_warn(tx_ring->dev,
				 "partial checksum, version=%d l4 proto=%x\n",
				 protocol, l4_hdr);
		पूर्ण
		skb_checksum_help(skb);
		tx_ring->tx_stats.csum_err++;
		जाओ no_csum;
	पूर्ण

	/* update TX checksum flag */
	first->tx_flags |= FM10K_TX_FLAGS_CSUM;
	tx_ring->tx_stats.csum_good++;

no_csum:
	/* populate Tx descriptor header size and mss */
	tx_desc = FM10K_TX_DESC(tx_ring, tx_ring->next_to_use);
	tx_desc->hdrlen = 0;
	tx_desc->mss = 0;
पूर्ण

#घोषणा FM10K_SET_FLAG(_input, _flag, _result) \
	((_flag <= _result) ? \
	 ((u32)(_input & _flag) * (_result / _flag)) : \
	 ((u32)(_input & _flag) / (_flag / _result)))

अटल u8 fm10k_tx_desc_flags(काष्ठा sk_buff *skb, u32 tx_flags)
अणु
	/* set type क्रम advanced descriptor with frame checksum insertion */
	u32 desc_flags = 0;

	/* set checksum offload bits */
	desc_flags |= FM10K_SET_FLAG(tx_flags, FM10K_TX_FLAGS_CSUM,
				     FM10K_TXD_FLAG_CSUM);

	वापस desc_flags;
पूर्ण

अटल bool fm10k_tx_desc_push(काष्ठा fm10k_ring *tx_ring,
			       काष्ठा fm10k_tx_desc *tx_desc, u16 i,
			       dma_addr_t dma, अचिन्हित पूर्णांक size, u8 desc_flags)
अणु
	/* set RS and INT क्रम last frame in a cache line */
	अगर ((++i & (FM10K_TXD_WB_FIFO_SIZE - 1)) == 0)
		desc_flags |= FM10K_TXD_FLAG_RS | FM10K_TXD_FLAG_INT;

	/* record values to descriptor */
	tx_desc->buffer_addr = cpu_to_le64(dma);
	tx_desc->flags = desc_flags;
	tx_desc->buflen = cpu_to_le16(size);

	/* वापस true अगर we just wrapped the ring */
	वापस i == tx_ring->count;
पूर्ण

अटल पूर्णांक __fm10k_maybe_stop_tx(काष्ठा fm10k_ring *tx_ring, u16 size)
अणु
	netअगर_stop_subqueue(tx_ring->netdev, tx_ring->queue_index);

	/* Memory barrier beक्रमe checking head and tail */
	smp_mb();

	/* Check again in a हाल another CPU has just made room available */
	अगर (likely(fm10k_desc_unused(tx_ring) < size))
		वापस -EBUSY;

	/* A reprieve! - use start_queue because it करोesn't call schedule */
	netअगर_start_subqueue(tx_ring->netdev, tx_ring->queue_index);
	++tx_ring->tx_stats.restart_queue;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक fm10k_maybe_stop_tx(काष्ठा fm10k_ring *tx_ring, u16 size)
अणु
	अगर (likely(fm10k_desc_unused(tx_ring) >= size))
		वापस 0;
	वापस __fm10k_maybe_stop_tx(tx_ring, size);
पूर्ण

अटल व्योम fm10k_tx_map(काष्ठा fm10k_ring *tx_ring,
			 काष्ठा fm10k_tx_buffer *first)
अणु
	काष्ठा sk_buff *skb = first->skb;
	काष्ठा fm10k_tx_buffer *tx_buffer;
	काष्ठा fm10k_tx_desc *tx_desc;
	skb_frag_t *frag;
	अचिन्हित अक्षर *data;
	dma_addr_t dma;
	अचिन्हित पूर्णांक data_len, size;
	u32 tx_flags = first->tx_flags;
	u16 i = tx_ring->next_to_use;
	u8 flags = fm10k_tx_desc_flags(skb, tx_flags);

	tx_desc = FM10K_TX_DESC(tx_ring, i);

	/* add HW VLAN tag */
	अगर (skb_vlan_tag_present(skb))
		tx_desc->vlan = cpu_to_le16(skb_vlan_tag_get(skb));
	अन्यथा
		tx_desc->vlan = 0;

	size = skb_headlen(skb);
	data = skb->data;

	dma = dma_map_single(tx_ring->dev, data, size, DMA_TO_DEVICE);

	data_len = skb->data_len;
	tx_buffer = first;

	क्रम (frag = &skb_shinfo(skb)->frags[0];; frag++) अणु
		अगर (dma_mapping_error(tx_ring->dev, dma))
			जाओ dma_error;

		/* record length, and DMA address */
		dma_unmap_len_set(tx_buffer, len, size);
		dma_unmap_addr_set(tx_buffer, dma, dma);

		जबतक (unlikely(size > FM10K_MAX_DATA_PER_TXD)) अणु
			अगर (fm10k_tx_desc_push(tx_ring, tx_desc++, i++, dma,
					       FM10K_MAX_DATA_PER_TXD, flags)) अणु
				tx_desc = FM10K_TX_DESC(tx_ring, 0);
				i = 0;
			पूर्ण

			dma += FM10K_MAX_DATA_PER_TXD;
			size -= FM10K_MAX_DATA_PER_TXD;
		पूर्ण

		अगर (likely(!data_len))
			अवरोध;

		अगर (fm10k_tx_desc_push(tx_ring, tx_desc++, i++,
				       dma, size, flags)) अणु
			tx_desc = FM10K_TX_DESC(tx_ring, 0);
			i = 0;
		पूर्ण

		size = skb_frag_size(frag);
		data_len -= size;

		dma = skb_frag_dma_map(tx_ring->dev, frag, 0, size,
				       DMA_TO_DEVICE);

		tx_buffer = &tx_ring->tx_buffer[i];
	पूर्ण

	/* ग_लिखो last descriptor with LAST bit set */
	flags |= FM10K_TXD_FLAG_LAST;

	अगर (fm10k_tx_desc_push(tx_ring, tx_desc, i++, dma, size, flags))
		i = 0;

	/* record bytecount क्रम BQL */
	netdev_tx_sent_queue(txring_txq(tx_ring), first->bytecount);

	/* record SW बारtamp अगर HW बारtamp is not available */
	skb_tx_बारtamp(first->skb);

	/* Force memory ग_लिखोs to complete beक्रमe letting h/w know there
	 * are new descriptors to fetch.  (Only applicable क्रम weak-ordered
	 * memory model archs, such as IA-64).
	 *
	 * We also need this memory barrier to make certain all of the
	 * status bits have been updated beक्रमe next_to_watch is written.
	 */
	wmb();

	/* set next_to_watch value indicating a packet is present */
	first->next_to_watch = tx_desc;

	tx_ring->next_to_use = i;

	/* Make sure there is space in the ring क्रम the next send. */
	fm10k_maybe_stop_tx(tx_ring, DESC_NEEDED);

	/* notअगरy HW of packet */
	अगर (netअगर_xmit_stopped(txring_txq(tx_ring)) || !netdev_xmit_more()) अणु
		ग_लिखोl(i, tx_ring->tail);
	पूर्ण

	वापस;
dma_error:
	dev_err(tx_ring->dev, "TX DMA map failed\n");

	/* clear dma mappings क्रम failed tx_buffer map */
	क्रम (;;) अणु
		tx_buffer = &tx_ring->tx_buffer[i];
		fm10k_unmap_and_मुक्त_tx_resource(tx_ring, tx_buffer);
		अगर (tx_buffer == first)
			अवरोध;
		अगर (i == 0)
			i = tx_ring->count;
		i--;
	पूर्ण

	tx_ring->next_to_use = i;
पूर्ण

netdev_tx_t fm10k_xmit_frame_ring(काष्ठा sk_buff *skb,
				  काष्ठा fm10k_ring *tx_ring)
अणु
	u16 count = TXD_USE_COUNT(skb_headlen(skb));
	काष्ठा fm10k_tx_buffer *first;
	अचिन्हित लघु f;
	u32 tx_flags = 0;
	पूर्णांक tso;

	/* need: 1 descriptor per page * PAGE_SIZE/FM10K_MAX_DATA_PER_TXD,
	 *       + 1 desc क्रम skb_headlen/FM10K_MAX_DATA_PER_TXD,
	 *       + 2 desc gap to keep tail from touching head
	 * otherwise try next समय
	 */
	क्रम (f = 0; f < skb_shinfo(skb)->nr_frags; f++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[f];

		count += TXD_USE_COUNT(skb_frag_size(frag));
	पूर्ण

	अगर (fm10k_maybe_stop_tx(tx_ring, count + 3)) अणु
		tx_ring->tx_stats.tx_busy++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* record the location of the first descriptor क्रम this packet */
	first = &tx_ring->tx_buffer[tx_ring->next_to_use];
	first->skb = skb;
	first->bytecount = max_t(अचिन्हित पूर्णांक, skb->len, ETH_ZLEN);
	first->gso_segs = 1;

	/* record initial flags and protocol */
	first->tx_flags = tx_flags;

	tso = fm10k_tso(tx_ring, first);
	अगर (tso < 0)
		जाओ out_drop;
	अन्यथा अगर (!tso)
		fm10k_tx_csum(tx_ring, first);

	fm10k_tx_map(tx_ring, first);

	वापस NETDEV_TX_OK;

out_drop:
	dev_kमुक्त_skb_any(first->skb);
	first->skb = शून्य;

	वापस NETDEV_TX_OK;
पूर्ण

अटल u64 fm10k_get_tx_completed(काष्ठा fm10k_ring *ring)
अणु
	वापस ring->stats.packets;
पूर्ण

/**
 * fm10k_get_tx_pending - how many Tx descriptors not processed
 * @ring: the ring काष्ठाure
 * @in_sw: is tx_pending being checked in SW or in HW?
 */
u64 fm10k_get_tx_pending(काष्ठा fm10k_ring *ring, bool in_sw)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = ring->q_vector->पूर्णांकerface;
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	u32 head, tail;

	अगर (likely(in_sw)) अणु
		head = ring->next_to_clean;
		tail = ring->next_to_use;
	पूर्ण अन्यथा अणु
		head = fm10k_पढ़ो_reg(hw, FM10K_TDH(ring->reg_idx));
		tail = fm10k_पढ़ो_reg(hw, FM10K_TDT(ring->reg_idx));
	पूर्ण

	वापस ((head <= tail) ? tail : tail + ring->count) - head;
पूर्ण

bool fm10k_check_tx_hang(काष्ठा fm10k_ring *tx_ring)
अणु
	u32 tx_करोne = fm10k_get_tx_completed(tx_ring);
	u32 tx_करोne_old = tx_ring->tx_stats.tx_करोne_old;
	u32 tx_pending = fm10k_get_tx_pending(tx_ring, true);

	clear_check_क्रम_tx_hang(tx_ring);

	/* Check क्रम a hung queue, but be thorough. This verअगरies
	 * that a transmit has been completed since the previous
	 * check AND there is at least one packet pending. By
	 * requiring this to fail twice we aव्योम races with
	 * clearing the ARMED bit and conditions where we
	 * run the check_tx_hang logic with a transmit completion
	 * pending but without समय to complete it yet.
	 */
	अगर (!tx_pending || (tx_करोne_old != tx_करोne)) अणु
		/* update completed stats and जारी */
		tx_ring->tx_stats.tx_करोne_old = tx_करोne;
		/* reset the countकरोwn */
		clear_bit(__FM10K_HANG_CHECK_ARMED, tx_ring->state);

		वापस false;
	पूर्ण

	/* make sure it is true क्रम two checks in a row */
	वापस test_and_set_bit(__FM10K_HANG_CHECK_ARMED, tx_ring->state);
पूर्ण

/**
 * fm10k_tx_समयout_reset - initiate reset due to Tx समयout
 * @पूर्णांकerface: driver निजी काष्ठा
 **/
व्योम fm10k_tx_समयout_reset(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	/* Do the reset outside of पूर्णांकerrupt context */
	अगर (!test_bit(__FM10K_DOWN, पूर्णांकerface->state)) अणु
		पूर्णांकerface->tx_समयout_count++;
		set_bit(FM10K_FLAG_RESET_REQUESTED, पूर्णांकerface->flags);
		fm10k_service_event_schedule(पूर्णांकerface);
	पूर्ण
पूर्ण

/**
 * fm10k_clean_tx_irq - Reclaim resources after transmit completes
 * @q_vector: काष्ठाure containing पूर्णांकerrupt and ring inक्रमmation
 * @tx_ring: tx ring to clean
 * @napi_budget: Used to determine अगर we are in netpoll
 **/
अटल bool fm10k_clean_tx_irq(काष्ठा fm10k_q_vector *q_vector,
			       काष्ठा fm10k_ring *tx_ring, पूर्णांक napi_budget)
अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface = q_vector->पूर्णांकerface;
	काष्ठा fm10k_tx_buffer *tx_buffer;
	काष्ठा fm10k_tx_desc *tx_desc;
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0;
	अचिन्हित पूर्णांक budget = q_vector->tx.work_limit;
	अचिन्हित पूर्णांक i = tx_ring->next_to_clean;

	अगर (test_bit(__FM10K_DOWN, पूर्णांकerface->state))
		वापस true;

	tx_buffer = &tx_ring->tx_buffer[i];
	tx_desc = FM10K_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	करो अणु
		काष्ठा fm10k_tx_desc *eop_desc = tx_buffer->next_to_watch;

		/* अगर next_to_watch is not set then there is no work pending */
		अगर (!eop_desc)
			अवरोध;

		/* prevent any other पढ़ोs prior to eop_desc */
		smp_rmb();

		/* अगर DD is not set pending work has not been completed */
		अगर (!(eop_desc->flags & FM10K_TXD_FLAG_DONE))
			अवरोध;

		/* clear next_to_watch to prevent false hangs */
		tx_buffer->next_to_watch = शून्य;

		/* update the statistics क्रम this packet */
		total_bytes += tx_buffer->bytecount;
		total_packets += tx_buffer->gso_segs;

		/* मुक्त the skb */
		napi_consume_skb(tx_buffer->skb, napi_budget);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);

		/* clear tx_buffer data */
		tx_buffer->skb = शून्य;
		dma_unmap_len_set(tx_buffer, len, 0);

		/* unmap reमुख्यing buffers */
		जबतक (tx_desc != eop_desc) अणु
			tx_buffer++;
			tx_desc++;
			i++;
			अगर (unlikely(!i)) अणु
				i -= tx_ring->count;
				tx_buffer = tx_ring->tx_buffer;
				tx_desc = FM10K_TX_DESC(tx_ring, 0);
			पूर्ण

			/* unmap any reमुख्यing paged data */
			अगर (dma_unmap_len(tx_buffer, len)) अणु
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buffer, dma),
					       dma_unmap_len(tx_buffer, len),
					       DMA_TO_DEVICE);
				dma_unmap_len_set(tx_buffer, len, 0);
			पूर्ण
		पूर्ण

		/* move us one more past the eop_desc क्रम start of next pkt */
		tx_buffer++;
		tx_desc++;
		i++;
		अगर (unlikely(!i)) अणु
			i -= tx_ring->count;
			tx_buffer = tx_ring->tx_buffer;
			tx_desc = FM10K_TX_DESC(tx_ring, 0);
		पूर्ण

		/* issue prefetch क्रम next Tx descriptor */
		prefetch(tx_desc);

		/* update budget accounting */
		budget--;
	पूर्ण जबतक (likely(budget));

	i += tx_ring->count;
	tx_ring->next_to_clean = i;
	u64_stats_update_begin(&tx_ring->syncp);
	tx_ring->stats.bytes += total_bytes;
	tx_ring->stats.packets += total_packets;
	u64_stats_update_end(&tx_ring->syncp);
	q_vector->tx.total_bytes += total_bytes;
	q_vector->tx.total_packets += total_packets;

	अगर (check_क्रम_tx_hang(tx_ring) && fm10k_check_tx_hang(tx_ring)) अणु
		/* schedule immediate reset अगर we believe we hung */
		काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;

		netअगर_err(पूर्णांकerface, drv, tx_ring->netdev,
			  "Detected Tx Unit Hang\n"
			  "  Tx Queue             <%d>\n"
			  "  TDH, TDT             <%x>, <%x>\n"
			  "  next_to_use          <%x>\n"
			  "  next_to_clean        <%x>\n",
			  tx_ring->queue_index,
			  fm10k_पढ़ो_reg(hw, FM10K_TDH(tx_ring->reg_idx)),
			  fm10k_पढ़ो_reg(hw, FM10K_TDT(tx_ring->reg_idx)),
			  tx_ring->next_to_use, i);

		netअगर_stop_subqueue(tx_ring->netdev,
				    tx_ring->queue_index);

		netअगर_info(पूर्णांकerface, probe, tx_ring->netdev,
			   "tx hang %d detected on queue %d, resetting interface\n",
			   पूर्णांकerface->tx_समयout_count + 1,
			   tx_ring->queue_index);

		fm10k_tx_समयout_reset(पूर्णांकerface);

		/* the netdev is about to reset, no poपूर्णांक in enabling stuff */
		वापस true;
	पूर्ण

	/* notअगरy netdev of completed buffers */
	netdev_tx_completed_queue(txring_txq(tx_ring),
				  total_packets, total_bytes);

#घोषणा TX_WAKE_THRESHOLD min_t(u16, FM10K_MIN_TXD - 1, DESC_NEEDED * 2)
	अगर (unlikely(total_packets && netअगर_carrier_ok(tx_ring->netdev) &&
		     (fm10k_desc_unused(tx_ring) >= TX_WAKE_THRESHOLD))) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		अगर (__netअगर_subqueue_stopped(tx_ring->netdev,
					     tx_ring->queue_index) &&
		    !test_bit(__FM10K_DOWN, पूर्णांकerface->state)) अणु
			netअगर_wake_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);
			++tx_ring->tx_stats.restart_queue;
		पूर्ण
	पूर्ण

	वापस !!budget;
पूर्ण

/**
 * fm10k_update_itr - update the dynamic ITR value based on packet size
 *
 *      Stores a new ITR value based on strictly on packet size.  The
 *      भागisors and thresholds used by this function were determined based
 *      on theoretical maximum wire speed and testing data, in order to
 *      minimize response समय जबतक increasing bulk throughput.
 *
 * @ring_container: Container क्रम rings to have ITR updated
 **/
अटल व्योम fm10k_update_itr(काष्ठा fm10k_ring_container *ring_container)
अणु
	अचिन्हित पूर्णांक avg_wire_size, packets, itr_round;

	/* Only update ITR अगर we are using adaptive setting */
	अगर (!ITR_IS_ADAPTIVE(ring_container->itr))
		जाओ clear_counts;

	packets = ring_container->total_packets;
	अगर (!packets)
		जाओ clear_counts;

	avg_wire_size = ring_container->total_bytes / packets;

	/* The following is a crude approximation of:
	 *  wmem_शेष / (size + overhead) = desired_pkts_per_पूर्णांक
	 *  rate / bits_per_byte / (size + ethernet overhead) = pkt_rate
	 *  (desired_pkt_rate / pkt_rate) * usecs_per_sec = ITR value
	 *
	 * Assuming wmem_शेष is 212992 and overhead is 640 bytes per
	 * packet, (256 skb, 64 headroom, 320 shared info), we can reduce the
	 * क्रमmula करोwn to
	 *
	 *  (34 * (size + 24)) / (size + 640) = ITR
	 *
	 * We first करो some math on the packet size and then finally bitshअगरt
	 * by 8 after rounding up. We also have to account क्रम PCIe link speed
	 * dअगरference as ITR scales based on this.
	 */
	अगर (avg_wire_size <= 360) अणु
		/* Start at 250K पूर्णांकs/sec and gradually drop to 77K पूर्णांकs/sec */
		avg_wire_size *= 8;
		avg_wire_size += 376;
	पूर्ण अन्यथा अगर (avg_wire_size <= 1152) अणु
		/* 77K पूर्णांकs/sec to 45K पूर्णांकs/sec */
		avg_wire_size *= 3;
		avg_wire_size += 2176;
	पूर्ण अन्यथा अगर (avg_wire_size <= 1920) अणु
		/* 45K पूर्णांकs/sec to 38K पूर्णांकs/sec */
		avg_wire_size += 4480;
	पूर्ण अन्यथा अणु
		/* plateau at a limit of 38K पूर्णांकs/sec */
		avg_wire_size = 6656;
	पूर्ण

	/* Perक्रमm final bitshअगरt क्रम भागision after rounding up to ensure
	 * that the calculation will never get below a 1. The bit shअगरt
	 * accounts क्रम changes in the ITR due to PCIe link speed.
	 */
	itr_round = READ_ONCE(ring_container->itr_scale) + 8;
	avg_wire_size += BIT(itr_round) - 1;
	avg_wire_size >>= itr_round;

	/* ग_लिखो back value and retain adaptive flag */
	ring_container->itr = avg_wire_size | FM10K_ITR_ADAPTIVE;

clear_counts:
	ring_container->total_bytes = 0;
	ring_container->total_packets = 0;
पूर्ण

अटल व्योम fm10k_qv_enable(काष्ठा fm10k_q_vector *q_vector)
अणु
	/* Enable स्वतः-mask and clear the current mask */
	u32 itr = FM10K_ITR_ENABLE;

	/* Update Tx ITR */
	fm10k_update_itr(&q_vector->tx);

	/* Update Rx ITR */
	fm10k_update_itr(&q_vector->rx);

	/* Store Tx itr in समयr slot 0 */
	itr |= (q_vector->tx.itr & FM10K_ITR_MAX);

	/* Shअगरt Rx itr to समयr slot 1 */
	itr |= (q_vector->rx.itr & FM10K_ITR_MAX) << FM10K_ITR_INTERVAL1_SHIFT;

	/* Write the final value to the ITR रेजिस्टर */
	ग_लिखोl(itr, q_vector->itr);
पूर्ण

अटल पूर्णांक fm10k_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा fm10k_q_vector *q_vector =
			       container_of(napi, काष्ठा fm10k_q_vector, napi);
	काष्ठा fm10k_ring *ring;
	पूर्णांक per_ring_budget, work_करोne = 0;
	bool clean_complete = true;

	fm10k_क्रम_each_ring(ring, q_vector->tx) अणु
		अगर (!fm10k_clean_tx_irq(q_vector, ring, budget))
			clean_complete = false;
	पूर्ण

	/* Handle हाल where we are called by netpoll with a budget of 0 */
	अगर (budget <= 0)
		वापस budget;

	/* attempt to distribute budget to each queue fairly, but करोn't
	 * allow the budget to go below 1 because we'll निकास polling
	 */
	अगर (q_vector->rx.count > 1)
		per_ring_budget = max(budget / q_vector->rx.count, 1);
	अन्यथा
		per_ring_budget = budget;

	fm10k_क्रम_each_ring(ring, q_vector->rx) अणु
		पूर्णांक work = fm10k_clean_rx_irq(q_vector, ring, per_ring_budget);

		work_करोne += work;
		अगर (work >= per_ring_budget)
			clean_complete = false;
	पूर्ण

	/* If all work not completed, वापस budget and keep polling */
	अगर (!clean_complete)
		वापस budget;

	/* Exit the polling mode, but करोn't re-enable पूर्णांकerrupts अगर stack might
	 * poll us due to busy-polling
	 */
	अगर (likely(napi_complete_करोne(napi, work_करोne)))
		fm10k_qv_enable(q_vector);

	वापस min(work_करोne, budget - 1);
पूर्ण

/**
 * fm10k_set_qos_queues: Allocate queues क्रम a QOS-enabled device
 * @पूर्णांकerface: board निजी काष्ठाure to initialize
 *
 * When QoS (Quality of Service) is enabled, allocate queues क्रम
 * each traffic class.  If multiqueue isn't available,then पात QoS
 * initialization.
 *
 * This function handles all combinations of Qos and RSS.
 *
 **/
अटल bool fm10k_set_qos_queues(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा net_device *dev = पूर्णांकerface->netdev;
	काष्ठा fm10k_ring_feature *f;
	पूर्णांक rss_i, i;
	पूर्णांक pcs;

	/* Map queue offset and counts onto allocated tx queues */
	pcs = netdev_get_num_tc(dev);

	अगर (pcs <= 1)
		वापस false;

	/* set QoS mask and indices */
	f = &पूर्णांकerface->ring_feature[RING_F_QOS];
	f->indices = pcs;
	f->mask = BIT(fls(pcs - 1)) - 1;

	/* determine the upper limit क्रम our current DCB mode */
	rss_i = पूर्णांकerface->hw.mac.max_queues / pcs;
	rss_i = BIT(fls(rss_i) - 1);

	/* set RSS mask and indices */
	f = &पूर्णांकerface->ring_feature[RING_F_RSS];
	rss_i = min_t(u16, rss_i, f->limit);
	f->indices = rss_i;
	f->mask = BIT(fls(rss_i - 1)) - 1;

	/* configure छोड़ो class to queue mapping */
	क्रम (i = 0; i < pcs; i++)
		netdev_set_tc_queue(dev, i, rss_i, rss_i * i);

	पूर्णांकerface->num_rx_queues = rss_i * pcs;
	पूर्णांकerface->num_tx_queues = rss_i * pcs;

	वापस true;
पूर्ण

/**
 * fm10k_set_rss_queues: Allocate queues क्रम RSS
 * @पूर्णांकerface: board निजी काष्ठाure to initialize
 *
 * This is our "base" multiqueue mode.  RSS (Receive Side Scaling) will try
 * to allocate one Rx queue per CPU, and अगर available, one Tx queue per CPU.
 *
 **/
अटल bool fm10k_set_rss_queues(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_ring_feature *f;
	u16 rss_i;

	f = &पूर्णांकerface->ring_feature[RING_F_RSS];
	rss_i = min_t(u16, पूर्णांकerface->hw.mac.max_queues, f->limit);

	/* record indices and घातer of 2 mask क्रम RSS */
	f->indices = rss_i;
	f->mask = BIT(fls(rss_i - 1)) - 1;

	पूर्णांकerface->num_rx_queues = rss_i;
	पूर्णांकerface->num_tx_queues = rss_i;

	वापस true;
पूर्ण

/**
 * fm10k_set_num_queues: Allocate queues क्रम device, feature dependent
 * @पूर्णांकerface: board निजी काष्ठाure to initialize
 *
 * This is the top level queue allocation routine.  The order here is very
 * important, starting with the "most" number of features turned on at once,
 * and ending with the smallest set of features.  This way large combinations
 * can be allocated अगर they're turned on, and smaller combinations are the
 * fall through conditions.
 *
 **/
अटल व्योम fm10k_set_num_queues(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	/* Attempt to setup QoS and RSS first */
	अगर (fm10k_set_qos_queues(पूर्णांकerface))
		वापस;

	/* If we करोn't have QoS, just fallback to only RSS. */
	fm10k_set_rss_queues(पूर्णांकerface);
पूर्ण

/**
 * fm10k_reset_num_queues - Reset the number of queues to zero
 * @पूर्णांकerface: board निजी काष्ठाure
 *
 * This function should be called whenever we need to reset the number of
 * queues after an error condition.
 */
अटल व्योम fm10k_reset_num_queues(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांकerface->num_tx_queues = 0;
	पूर्णांकerface->num_rx_queues = 0;
	पूर्णांकerface->num_q_vectors = 0;
पूर्ण

/**
 * fm10k_alloc_q_vector - Allocate memory क्रम a single पूर्णांकerrupt vector
 * @पूर्णांकerface: board निजी काष्ठाure to initialize
 * @v_count: q_vectors allocated on पूर्णांकerface, used क्रम ring पूर्णांकerleaving
 * @v_idx: index of vector in पूर्णांकerface काष्ठा
 * @txr_count: total number of Tx rings to allocate
 * @txr_idx: index of first Tx ring to allocate
 * @rxr_count: total number of Rx rings to allocate
 * @rxr_idx: index of first Rx ring to allocate
 *
 * We allocate one q_vector.  If allocation fails we वापस -ENOMEM.
 **/
अटल पूर्णांक fm10k_alloc_q_vector(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface,
				अचिन्हित पूर्णांक v_count, अचिन्हित पूर्णांक v_idx,
				अचिन्हित पूर्णांक txr_count, अचिन्हित पूर्णांक txr_idx,
				अचिन्हित पूर्णांक rxr_count, अचिन्हित पूर्णांक rxr_idx)
अणु
	काष्ठा fm10k_q_vector *q_vector;
	काष्ठा fm10k_ring *ring;
	पूर्णांक ring_count;

	ring_count = txr_count + rxr_count;

	/* allocate q_vector and rings */
	q_vector = kzalloc(काष्ठा_size(q_vector, ring, ring_count), GFP_KERNEL);
	अगर (!q_vector)
		वापस -ENOMEM;

	/* initialize NAPI */
	netअगर_napi_add(पूर्णांकerface->netdev, &q_vector->napi,
		       fm10k_poll, NAPI_POLL_WEIGHT);

	/* tie q_vector and पूर्णांकerface together */
	पूर्णांकerface->q_vector[v_idx] = q_vector;
	q_vector->पूर्णांकerface = पूर्णांकerface;
	q_vector->v_idx = v_idx;

	/* initialize poपूर्णांकer to rings */
	ring = q_vector->ring;

	/* save Tx ring container info */
	q_vector->tx.ring = ring;
	q_vector->tx.work_limit = FM10K_DEFAULT_TX_WORK;
	q_vector->tx.itr = पूर्णांकerface->tx_itr;
	q_vector->tx.itr_scale = पूर्णांकerface->hw.mac.itr_scale;
	q_vector->tx.count = txr_count;

	जबतक (txr_count) अणु
		/* assign generic ring traits */
		ring->dev = &पूर्णांकerface->pdev->dev;
		ring->netdev = पूर्णांकerface->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* apply Tx specअगरic ring traits */
		ring->count = पूर्णांकerface->tx_ring_count;
		ring->queue_index = txr_idx;

		/* assign ring to पूर्णांकerface */
		पूर्णांकerface->tx_ring[txr_idx] = ring;

		/* update count and index */
		txr_count--;
		txr_idx += v_count;

		/* push poपूर्णांकer to next ring */
		ring++;
	पूर्ण

	/* save Rx ring container info */
	q_vector->rx.ring = ring;
	q_vector->rx.itr = पूर्णांकerface->rx_itr;
	q_vector->rx.itr_scale = पूर्णांकerface->hw.mac.itr_scale;
	q_vector->rx.count = rxr_count;

	जबतक (rxr_count) अणु
		/* assign generic ring traits */
		ring->dev = &पूर्णांकerface->pdev->dev;
		ring->netdev = पूर्णांकerface->netdev;
		rcu_assign_poपूर्णांकer(ring->l2_accel, पूर्णांकerface->l2_accel);

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* apply Rx specअगरic ring traits */
		ring->count = पूर्णांकerface->rx_ring_count;
		ring->queue_index = rxr_idx;

		/* assign ring to पूर्णांकerface */
		पूर्णांकerface->rx_ring[rxr_idx] = ring;

		/* update count and index */
		rxr_count--;
		rxr_idx += v_count;

		/* push poपूर्णांकer to next ring */
		ring++;
	पूर्ण

	fm10k_dbg_q_vector_init(q_vector);

	वापस 0;
पूर्ण

/**
 * fm10k_मुक्त_q_vector - Free memory allocated क्रम specअगरic पूर्णांकerrupt vector
 * @पूर्णांकerface: board निजी काष्ठाure to initialize
 * @v_idx: Index of vector to be मुक्तd
 *
 * This function मुक्तs the memory allocated to the q_vector.  In addition अगर
 * NAPI is enabled it will delete any references to the NAPI काष्ठा prior
 * to मुक्तing the q_vector.
 **/
अटल व्योम fm10k_मुक्त_q_vector(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface, पूर्णांक v_idx)
अणु
	काष्ठा fm10k_q_vector *q_vector = पूर्णांकerface->q_vector[v_idx];
	काष्ठा fm10k_ring *ring;

	fm10k_dbg_q_vector_निकास(q_vector);

	fm10k_क्रम_each_ring(ring, q_vector->tx)
		पूर्णांकerface->tx_ring[ring->queue_index] = शून्य;

	fm10k_क्रम_each_ring(ring, q_vector->rx)
		पूर्णांकerface->rx_ring[ring->queue_index] = शून्य;

	पूर्णांकerface->q_vector[v_idx] = शून्य;
	netअगर_napi_del(&q_vector->napi);
	kमुक्त_rcu(q_vector, rcu);
पूर्ण

/**
 * fm10k_alloc_q_vectors - Allocate memory क्रम पूर्णांकerrupt vectors
 * @पूर्णांकerface: board निजी काष्ठाure to initialize
 *
 * We allocate one q_vector per queue पूर्णांकerrupt.  If allocation fails we
 * वापस -ENOMEM.
 **/
अटल पूर्णांक fm10k_alloc_q_vectors(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	अचिन्हित पूर्णांक q_vectors = पूर्णांकerface->num_q_vectors;
	अचिन्हित पूर्णांक rxr_reमुख्यing = पूर्णांकerface->num_rx_queues;
	अचिन्हित पूर्णांक txr_reमुख्यing = पूर्णांकerface->num_tx_queues;
	अचिन्हित पूर्णांक rxr_idx = 0, txr_idx = 0, v_idx = 0;
	पूर्णांक err;

	अगर (q_vectors >= (rxr_reमुख्यing + txr_reमुख्यing)) अणु
		क्रम (; rxr_reमुख्यing; v_idx++) अणु
			err = fm10k_alloc_q_vector(पूर्णांकerface, q_vectors, v_idx,
						   0, 0, 1, rxr_idx);
			अगर (err)
				जाओ err_out;

			/* update counts and index */
			rxr_reमुख्यing--;
			rxr_idx++;
		पूर्ण
	पूर्ण

	क्रम (; v_idx < q_vectors; v_idx++) अणु
		पूर्णांक rqpv = DIV_ROUND_UP(rxr_reमुख्यing, q_vectors - v_idx);
		पूर्णांक tqpv = DIV_ROUND_UP(txr_reमुख्यing, q_vectors - v_idx);

		err = fm10k_alloc_q_vector(पूर्णांकerface, q_vectors, v_idx,
					   tqpv, txr_idx,
					   rqpv, rxr_idx);

		अगर (err)
			जाओ err_out;

		/* update counts and index */
		rxr_reमुख्यing -= rqpv;
		txr_reमुख्यing -= tqpv;
		rxr_idx++;
		txr_idx++;
	पूर्ण

	वापस 0;

err_out:
	fm10k_reset_num_queues(पूर्णांकerface);

	जबतक (v_idx--)
		fm10k_मुक्त_q_vector(पूर्णांकerface, v_idx);

	वापस -ENOMEM;
पूर्ण

/**
 * fm10k_मुक्त_q_vectors - Free memory allocated क्रम पूर्णांकerrupt vectors
 * @पूर्णांकerface: board निजी काष्ठाure to initialize
 *
 * This function मुक्तs the memory allocated to the q_vectors.  In addition अगर
 * NAPI is enabled it will delete any references to the NAPI काष्ठा prior
 * to मुक्तing the q_vector.
 **/
अटल व्योम fm10k_मुक्त_q_vectors(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक v_idx = पूर्णांकerface->num_q_vectors;

	fm10k_reset_num_queues(पूर्णांकerface);

	जबतक (v_idx--)
		fm10k_मुक्त_q_vector(पूर्णांकerface, v_idx);
पूर्ण

/**
 * fm10k_reset_msix_capability - reset MSI-X capability
 * @पूर्णांकerface: board निजी काष्ठाure to initialize
 *
 * Reset the MSI-X capability back to its starting state
 **/
अटल व्योम fm10k_reset_msix_capability(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	pci_disable_msix(पूर्णांकerface->pdev);
	kमुक्त(पूर्णांकerface->msix_entries);
	पूर्णांकerface->msix_entries = शून्य;
पूर्ण

/**
 * fm10k_init_msix_capability - configure MSI-X capability
 * @पूर्णांकerface: board निजी काष्ठाure to initialize
 *
 * Attempt to configure the पूर्णांकerrupts using the best available
 * capabilities of the hardware and the kernel.
 **/
अटल पूर्णांक fm10k_init_msix_capability(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा fm10k_hw *hw = &पूर्णांकerface->hw;
	पूर्णांक v_budget, vector;

	/* It's easy to be greedy क्रम MSI-X vectors, but it really
	 * करोesn't करो us much good अगर we have a lot more vectors
	 * than CPU's.  So let's be conservative and only ask क्रम
	 * (roughly) the same number of vectors as there are CPU's.
	 * the शेष is to use pairs of vectors
	 */
	v_budget = max(पूर्णांकerface->num_rx_queues, पूर्णांकerface->num_tx_queues);
	v_budget = min_t(u16, v_budget, num_online_cpus());

	/* account क्रम vectors not related to queues */
	v_budget += NON_Q_VECTORS;

	/* At the same समय, hardware can only support a maximum of
	 * hw.mac->max_msix_vectors vectors.  With features
	 * such as RSS and VMDq, we can easily surpass the number of Rx and Tx
	 * descriptor queues supported by our device.  Thus, we cap it off in
	 * those rare हालs where the cpu count also exceeds our vector limit.
	 */
	v_budget = min_t(पूर्णांक, v_budget, hw->mac.max_msix_vectors);

	/* A failure in MSI-X entry allocation is fatal. */
	पूर्णांकerface->msix_entries = kसुस्मृति(v_budget, माप(काष्ठा msix_entry),
					  GFP_KERNEL);
	अगर (!पूर्णांकerface->msix_entries)
		वापस -ENOMEM;

	/* populate entry values */
	क्रम (vector = 0; vector < v_budget; vector++)
		पूर्णांकerface->msix_entries[vector].entry = vector;

	/* Attempt to enable MSI-X with requested value */
	v_budget = pci_enable_msix_range(पूर्णांकerface->pdev,
					 पूर्णांकerface->msix_entries,
					 MIN_MSIX_COUNT(hw),
					 v_budget);
	अगर (v_budget < 0) अणु
		kमुक्त(पूर्णांकerface->msix_entries);
		पूर्णांकerface->msix_entries = शून्य;
		वापस v_budget;
	पूर्ण

	/* record the number of queues available क्रम q_vectors */
	पूर्णांकerface->num_q_vectors = v_budget - NON_Q_VECTORS;

	वापस 0;
पूर्ण

/**
 * fm10k_cache_ring_qos - Descriptor ring to रेजिस्टर mapping क्रम QoS
 * @पूर्णांकerface: Interface काष्ठाure continaining rings and devices
 *
 * Cache the descriptor ring offsets क्रम Qos
 **/
अटल bool fm10k_cache_ring_qos(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	काष्ठा net_device *dev = पूर्णांकerface->netdev;
	पूर्णांक pc, offset, rss_i, i;
	u16 pc_stride = पूर्णांकerface->ring_feature[RING_F_QOS].mask + 1;
	u8 num_pcs = netdev_get_num_tc(dev);

	अगर (num_pcs <= 1)
		वापस false;

	rss_i = पूर्णांकerface->ring_feature[RING_F_RSS].indices;

	क्रम (pc = 0, offset = 0; pc < num_pcs; pc++, offset += rss_i) अणु
		पूर्णांक q_idx = pc;

		क्रम (i = 0; i < rss_i; i++) अणु
			पूर्णांकerface->tx_ring[offset + i]->reg_idx = q_idx;
			पूर्णांकerface->tx_ring[offset + i]->qos_pc = pc;
			पूर्णांकerface->rx_ring[offset + i]->reg_idx = q_idx;
			पूर्णांकerface->rx_ring[offset + i]->qos_pc = pc;
			q_idx += pc_stride;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/**
 * fm10k_cache_ring_rss - Descriptor ring to रेजिस्टर mapping क्रम RSS
 * @पूर्णांकerface: Interface काष्ठाure continaining rings and devices
 *
 * Cache the descriptor ring offsets क्रम RSS
 **/
अटल व्योम fm10k_cache_ring_rss(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < पूर्णांकerface->num_rx_queues; i++)
		पूर्णांकerface->rx_ring[i]->reg_idx = i;

	क्रम (i = 0; i < पूर्णांकerface->num_tx_queues; i++)
		पूर्णांकerface->tx_ring[i]->reg_idx = i;
पूर्ण

/**
 * fm10k_assign_rings - Map rings to network devices
 * @पूर्णांकerface: Interface काष्ठाure containing rings and devices
 *
 * This function is meant to go though and configure both the network
 * devices so that they contain rings, and configure the rings so that
 * they function with their network devices.
 **/
अटल व्योम fm10k_assign_rings(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	अगर (fm10k_cache_ring_qos(पूर्णांकerface))
		वापस;

	fm10k_cache_ring_rss(पूर्णांकerface);
पूर्ण

अटल व्योम fm10k_init_reta(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	u16 i, rss_i = पूर्णांकerface->ring_feature[RING_F_RSS].indices;
	u32 reta;

	/* If the Rx flow indirection table has been configured manually, we
	 * need to मुख्यtain it when possible.
	 */
	अगर (netअगर_is_rxfh_configured(पूर्णांकerface->netdev)) अणु
		क्रम (i = FM10K_RETA_SIZE; i--;) अणु
			reta = पूर्णांकerface->reta[i];
			अगर ((((reta << 24) >> 24) < rss_i) &&
			    (((reta << 16) >> 24) < rss_i) &&
			    (((reta <<  8) >> 24) < rss_i) &&
			    (((reta)       >> 24) < rss_i))
				जारी;

			/* this should never happen */
			dev_err(&पूर्णांकerface->pdev->dev,
				"RSS indirection table assigned flows out of queue bounds. Reconfiguring.\n");
			जाओ repopulate_reta;
		पूर्ण

		/* करो nothing अगर all of the elements are in bounds */
		वापस;
	पूर्ण

repopulate_reta:
	fm10k_ग_लिखो_reta(पूर्णांकerface, शून्य);
पूर्ण

/**
 * fm10k_init_queueing_scheme - Determine proper queueing scheme
 * @पूर्णांकerface: board निजी काष्ठाure to initialize
 *
 * We determine which queueing scheme to use based on...
 * - Hardware queue count (num_*_queues)
 *   - defined by miscellaneous hardware support/features (RSS, etc.)
 **/
पूर्णांक fm10k_init_queueing_scheme(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	पूर्णांक err;

	/* Number of supported queues */
	fm10k_set_num_queues(पूर्णांकerface);

	/* Configure MSI-X capability */
	err = fm10k_init_msix_capability(पूर्णांकerface);
	अगर (err) अणु
		dev_err(&पूर्णांकerface->pdev->dev,
			"Unable to initialize MSI-X capability\n");
		जाओ err_init_msix;
	पूर्ण

	/* Allocate memory क्रम queues */
	err = fm10k_alloc_q_vectors(पूर्णांकerface);
	अगर (err) अणु
		dev_err(&पूर्णांकerface->pdev->dev,
			"Unable to allocate queue vectors\n");
		जाओ err_alloc_q_vectors;
	पूर्ण

	/* Map rings to devices, and map devices to physical queues */
	fm10k_assign_rings(पूर्णांकerface);

	/* Initialize RSS redirection table */
	fm10k_init_reta(पूर्णांकerface);

	वापस 0;

err_alloc_q_vectors:
	fm10k_reset_msix_capability(पूर्णांकerface);
err_init_msix:
	fm10k_reset_num_queues(पूर्णांकerface);
	वापस err;
पूर्ण

/**
 * fm10k_clear_queueing_scheme - Clear the current queueing scheme settings
 * @पूर्णांकerface: board निजी काष्ठाure to clear queueing scheme on
 *
 * We go through and clear queueing specअगरic resources and reset the काष्ठाure
 * to pre-load conditions
 **/
व्योम fm10k_clear_queueing_scheme(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	fm10k_मुक्त_q_vectors(पूर्णांकerface);
	fm10k_reset_msix_capability(पूर्णांकerface);
पूर्ण
