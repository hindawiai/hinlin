<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

/******************************************************************************
 Copyright (c)2006 - 2007 Myricom, Inc. क्रम some LRO specअगरic code
******************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/माला.स>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/sctp.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/slab.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/prefetch.h>
#समावेश <net/mpls.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/atomic.h>
#समावेश <net/xfrm.h>

#समावेश "ixgbevf.h"

स्थिर अक्षर ixgbevf_driver_name[] = "ixgbevf";
अटल स्थिर अक्षर ixgbevf_driver_string[] =
	"Intel(R) 10 Gigabit PCI Express Virtual Function Network Driver";

अटल अक्षर ixgbevf_copyright[] =
	"Copyright (c) 2009 - 2018 Intel Corporation.";

अटल स्थिर काष्ठा ixgbevf_info *ixgbevf_info_tbl[] = अणु
	[board_82599_vf]	= &ixgbevf_82599_vf_info,
	[board_82599_vf_hv]	= &ixgbevf_82599_vf_hv_info,
	[board_X540_vf]		= &ixgbevf_X540_vf_info,
	[board_X540_vf_hv]	= &ixgbevf_X540_vf_hv_info,
	[board_X550_vf]		= &ixgbevf_X550_vf_info,
	[board_X550_vf_hv]	= &ixgbevf_X550_vf_hv_info,
	[board_X550EM_x_vf]	= &ixgbevf_X550EM_x_vf_info,
	[board_X550EM_x_vf_hv]	= &ixgbevf_X550EM_x_vf_hv_info,
	[board_x550em_a_vf]	= &ixgbevf_x550em_a_vf_info,
पूर्ण;

/* ixgbevf_pci_tbl - PCI Device ID Table
 *
 * Wildcard entries (PCI_ANY_ID) should come last
 * Last entry must be all 0s
 *
 * अणु Venकरोr ID, Device ID, SubVenकरोr ID, SubDevice ID,
 *   Class, Class Mask, निजी data (not used) पूर्ण
 */
अटल स्थिर काष्ठा pci_device_id ixgbevf_pci_tbl[] = अणु
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_VF), board_82599_vf पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_82599_VF_HV), board_82599_vf_hv पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X540_VF), board_X540_vf पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X540_VF_HV), board_X540_vf_hv पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550_VF), board_X550_vf पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550_VF_HV), board_X550_vf_hv पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_X_VF), board_X550EM_x_vf पूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_X_VF_HV), board_X550EM_x_vf_hvपूर्ण,
	अणुPCI_VDEVICE(INTEL, IXGBE_DEV_ID_X550EM_A_VF), board_x550em_a_vf पूर्ण,
	/* required last entry */
	अणु0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, ixgbevf_pci_tbl);

MODULE_AUTHOR("Intel Corporation, <linux.nics@intel.com>");
MODULE_DESCRIPTION("Intel(R) 10 Gigabit Virtual Function Network Driver");
MODULE_LICENSE("GPL v2");

#घोषणा DEFAULT_MSG_ENABLE (NETIF_MSG_DRV|NETIF_MSG_PROBE|NETIF_MSG_LINK)
अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

अटल काष्ठा workqueue_काष्ठा *ixgbevf_wq;

अटल व्योम ixgbevf_service_event_schedule(काष्ठा ixgbevf_adapter *adapter)
अणु
	अगर (!test_bit(__IXGBEVF_DOWN, &adapter->state) &&
	    !test_bit(__IXGBEVF_REMOVING, &adapter->state) &&
	    !test_and_set_bit(__IXGBEVF_SERVICE_SCHED, &adapter->state))
		queue_work(ixgbevf_wq, &adapter->service_task);
पूर्ण

अटल व्योम ixgbevf_service_event_complete(काष्ठा ixgbevf_adapter *adapter)
अणु
	BUG_ON(!test_bit(__IXGBEVF_SERVICE_SCHED, &adapter->state));

	/* flush memory to make sure state is correct beक्रमe next watchकरोg */
	smp_mb__beक्रमe_atomic();
	clear_bit(__IXGBEVF_SERVICE_SCHED, &adapter->state);
पूर्ण

/* क्रमward decls */
अटल व्योम ixgbevf_queue_reset_subtask(काष्ठा ixgbevf_adapter *adapter);
अटल व्योम ixgbevf_set_itr(काष्ठा ixgbevf_q_vector *q_vector);
अटल व्योम ixgbevf_मुक्त_all_rx_resources(काष्ठा ixgbevf_adapter *adapter);
अटल bool ixgbevf_can_reuse_rx_page(काष्ठा ixgbevf_rx_buffer *rx_buffer);
अटल व्योम ixgbevf_reuse_rx_page(काष्ठा ixgbevf_ring *rx_ring,
				  काष्ठा ixgbevf_rx_buffer *old_buff);

अटल व्योम ixgbevf_हटाओ_adapter(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbevf_adapter *adapter = hw->back;

	अगर (!hw->hw_addr)
		वापस;
	hw->hw_addr = शून्य;
	dev_err(&adapter->pdev->dev, "Adapter removed\n");
	अगर (test_bit(__IXGBEVF_SERVICE_INITED, &adapter->state))
		ixgbevf_service_event_schedule(adapter);
पूर्ण

अटल व्योम ixgbevf_check_हटाओ(काष्ठा ixgbe_hw *hw, u32 reg)
अणु
	u32 value;

	/* The following check not only optimizes a bit by not
	 * perक्रमming a पढ़ो on the status रेजिस्टर when the
	 * रेजिस्टर just पढ़ो was a status रेजिस्टर पढ़ो that
	 * वापसed IXGBE_FAILED_READ_REG. It also blocks any
	 * potential recursion.
	 */
	अगर (reg == IXGBE_VFSTATUS) अणु
		ixgbevf_हटाओ_adapter(hw);
		वापस;
	पूर्ण
	value = ixgbevf_पढ़ो_reg(hw, IXGBE_VFSTATUS);
	अगर (value == IXGBE_FAILED_READ_REG)
		ixgbevf_हटाओ_adapter(hw);
पूर्ण

u32 ixgbevf_पढ़ो_reg(काष्ठा ixgbe_hw *hw, u32 reg)
अणु
	u8 __iomem *reg_addr = READ_ONCE(hw->hw_addr);
	u32 value;

	अगर (IXGBE_REMOVED(reg_addr))
		वापस IXGBE_FAILED_READ_REG;
	value = पढ़ोl(reg_addr + reg);
	अगर (unlikely(value == IXGBE_FAILED_READ_REG))
		ixgbevf_check_हटाओ(hw, reg);
	वापस value;
पूर्ण

/**
 * ixgbevf_set_ivar - set IVAR रेजिस्टरs - maps पूर्णांकerrupt causes to vectors
 * @adapter: poपूर्णांकer to adapter काष्ठा
 * @direction: 0 क्रम Rx, 1 क्रम Tx, -1 क्रम other causes
 * @queue: queue to map the corresponding पूर्णांकerrupt to
 * @msix_vector: the vector to map to the corresponding queue
 **/
अटल व्योम ixgbevf_set_ivar(काष्ठा ixgbevf_adapter *adapter, s8 direction,
			     u8 queue, u8 msix_vector)
अणु
	u32 ivar, index;
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	अगर (direction == -1) अणु
		/* other causes */
		msix_vector |= IXGBE_IVAR_ALLOC_VAL;
		ivar = IXGBE_READ_REG(hw, IXGBE_VTIVAR_MISC);
		ivar &= ~0xFF;
		ivar |= msix_vector;
		IXGBE_WRITE_REG(hw, IXGBE_VTIVAR_MISC, ivar);
	पूर्ण अन्यथा अणु
		/* Tx or Rx causes */
		msix_vector |= IXGBE_IVAR_ALLOC_VAL;
		index = ((16 * (queue & 1)) + (8 * direction));
		ivar = IXGBE_READ_REG(hw, IXGBE_VTIVAR(queue >> 1));
		ivar &= ~(0xFF << index);
		ivar |= (msix_vector << index);
		IXGBE_WRITE_REG(hw, IXGBE_VTIVAR(queue >> 1), ivar);
	पूर्ण
पूर्ण

अटल u64 ixgbevf_get_tx_completed(काष्ठा ixgbevf_ring *ring)
अणु
	वापस ring->stats.packets;
पूर्ण

अटल u32 ixgbevf_get_tx_pending(काष्ठा ixgbevf_ring *ring)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(ring->netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	u32 head = IXGBE_READ_REG(hw, IXGBE_VFTDH(ring->reg_idx));
	u32 tail = IXGBE_READ_REG(hw, IXGBE_VFTDT(ring->reg_idx));

	अगर (head != tail)
		वापस (head < tail) ?
			tail - head : (tail + ring->count - head);

	वापस 0;
पूर्ण

अटल अंतरभूत bool ixgbevf_check_tx_hang(काष्ठा ixgbevf_ring *tx_ring)
अणु
	u32 tx_करोne = ixgbevf_get_tx_completed(tx_ring);
	u32 tx_करोne_old = tx_ring->tx_stats.tx_करोne_old;
	u32 tx_pending = ixgbevf_get_tx_pending(tx_ring);

	clear_check_क्रम_tx_hang(tx_ring);

	/* Check क्रम a hung queue, but be thorough. This verअगरies
	 * that a transmit has been completed since the previous
	 * check AND there is at least one packet pending. The
	 * ARMED bit is set to indicate a potential hang.
	 */
	अगर ((tx_करोne_old == tx_करोne) && tx_pending) अणु
		/* make sure it is true क्रम two checks in a row */
		वापस test_and_set_bit(__IXGBEVF_HANG_CHECK_ARMED,
					&tx_ring->state);
	पूर्ण
	/* reset the countकरोwn */
	clear_bit(__IXGBEVF_HANG_CHECK_ARMED, &tx_ring->state);

	/* update completed stats and जारी */
	tx_ring->tx_stats.tx_करोne_old = tx_करोne;

	वापस false;
पूर्ण

अटल व्योम ixgbevf_tx_समयout_reset(काष्ठा ixgbevf_adapter *adapter)
अणु
	/* Do the reset outside of पूर्णांकerrupt context */
	अगर (!test_bit(__IXGBEVF_DOWN, &adapter->state)) अणु
		set_bit(__IXGBEVF_RESET_REQUESTED, &adapter->state);
		ixgbevf_service_event_schedule(adapter);
	पूर्ण
पूर्ण

/**
 * ixgbevf_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @txqueue: transmit queue hanging (unused)
 **/
अटल व्योम ixgbevf_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक __always_unused txqueue)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);

	ixgbevf_tx_समयout_reset(adapter);
पूर्ण

/**
 * ixgbevf_clean_tx_irq - Reclaim resources after transmit completes
 * @q_vector: board निजी काष्ठाure
 * @tx_ring: tx ring to clean
 * @napi_budget: Used to determine अगर we are in netpoll
 **/
अटल bool ixgbevf_clean_tx_irq(काष्ठा ixgbevf_q_vector *q_vector,
				 काष्ठा ixgbevf_ring *tx_ring, पूर्णांक napi_budget)
अणु
	काष्ठा ixgbevf_adapter *adapter = q_vector->adapter;
	काष्ठा ixgbevf_tx_buffer *tx_buffer;
	जोड़ ixgbe_adv_tx_desc *tx_desc;
	अचिन्हित पूर्णांक total_bytes = 0, total_packets = 0, total_ipsec = 0;
	अचिन्हित पूर्णांक budget = tx_ring->count / 2;
	अचिन्हित पूर्णांक i = tx_ring->next_to_clean;

	अगर (test_bit(__IXGBEVF_DOWN, &adapter->state))
		वापस true;

	tx_buffer = &tx_ring->tx_buffer_info[i];
	tx_desc = IXGBEVF_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	करो अणु
		जोड़ ixgbe_adv_tx_desc *eop_desc = tx_buffer->next_to_watch;

		/* अगर next_to_watch is not set then there is no work pending */
		अगर (!eop_desc)
			अवरोध;

		/* prevent any other पढ़ोs prior to eop_desc */
		smp_rmb();

		/* अगर DD is not set pending work has not been completed */
		अगर (!(eop_desc->wb.status & cpu_to_le32(IXGBE_TXD_STAT_DD)))
			अवरोध;

		/* clear next_to_watch to prevent false hangs */
		tx_buffer->next_to_watch = शून्य;

		/* update the statistics क्रम this packet */
		total_bytes += tx_buffer->bytecount;
		total_packets += tx_buffer->gso_segs;
		अगर (tx_buffer->tx_flags & IXGBE_TX_FLAGS_IPSEC)
			total_ipsec++;

		/* मुक्त the skb */
		अगर (ring_is_xdp(tx_ring))
			page_frag_मुक्त(tx_buffer->data);
		अन्यथा
			napi_consume_skb(tx_buffer->skb, napi_budget);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);

		/* clear tx_buffer data */
		dma_unmap_len_set(tx_buffer, len, 0);

		/* unmap reमुख्यing buffers */
		जबतक (tx_desc != eop_desc) अणु
			tx_buffer++;
			tx_desc++;
			i++;
			अगर (unlikely(!i)) अणु
				i -= tx_ring->count;
				tx_buffer = tx_ring->tx_buffer_info;
				tx_desc = IXGBEVF_TX_DESC(tx_ring, 0);
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
			tx_buffer = tx_ring->tx_buffer_info;
			tx_desc = IXGBEVF_TX_DESC(tx_ring, 0);
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
	adapter->tx_ipsec += total_ipsec;

	अगर (check_क्रम_tx_hang(tx_ring) && ixgbevf_check_tx_hang(tx_ring)) अणु
		काष्ठा ixgbe_hw *hw = &adapter->hw;
		जोड़ ixgbe_adv_tx_desc *eop_desc;

		eop_desc = tx_ring->tx_buffer_info[i].next_to_watch;

		pr_err("Detected Tx Unit Hang%s\n"
		       "  Tx Queue             <%d>\n"
		       "  TDH, TDT             <%x>, <%x>\n"
		       "  next_to_use          <%x>\n"
		       "  next_to_clean        <%x>\n"
		       "tx_buffer_info[next_to_clean]\n"
		       "  next_to_watch        <%p>\n"
		       "  eop_desc->wb.status  <%x>\n"
		       "  time_stamp           <%lx>\n"
		       "  jiffies              <%lx>\n",
		       ring_is_xdp(tx_ring) ? " XDP" : "",
		       tx_ring->queue_index,
		       IXGBE_READ_REG(hw, IXGBE_VFTDH(tx_ring->reg_idx)),
		       IXGBE_READ_REG(hw, IXGBE_VFTDT(tx_ring->reg_idx)),
		       tx_ring->next_to_use, i,
		       eop_desc, (eop_desc ? eop_desc->wb.status : 0),
		       tx_ring->tx_buffer_info[i].समय_stamp, jअगरfies);

		अगर (!ring_is_xdp(tx_ring))
			netअगर_stop_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);

		/* schedule immediate reset अगर we believe we hung */
		ixgbevf_tx_समयout_reset(adapter);

		वापस true;
	पूर्ण

	अगर (ring_is_xdp(tx_ring))
		वापस !!budget;

#घोषणा TX_WAKE_THRESHOLD (DESC_NEEDED * 2)
	अगर (unlikely(total_packets && netअगर_carrier_ok(tx_ring->netdev) &&
		     (ixgbevf_desc_unused(tx_ring) >= TX_WAKE_THRESHOLD))) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();

		अगर (__netअगर_subqueue_stopped(tx_ring->netdev,
					     tx_ring->queue_index) &&
		    !test_bit(__IXGBEVF_DOWN, &adapter->state)) अणु
			netअगर_wake_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);
			++tx_ring->tx_stats.restart_queue;
		पूर्ण
	पूर्ण

	वापस !!budget;
पूर्ण

/**
 * ixgbevf_rx_skb - Helper function to determine proper Rx method
 * @q_vector: काष्ठाure containing पूर्णांकerrupt and ring inक्रमmation
 * @skb: packet to send up
 **/
अटल व्योम ixgbevf_rx_skb(काष्ठा ixgbevf_q_vector *q_vector,
			   काष्ठा sk_buff *skb)
अणु
	napi_gro_receive(&q_vector->napi, skb);
पूर्ण

#घोषणा IXGBE_RSS_L4_TYPES_MASK \
	((1ul << IXGBE_RXDADV_RSSTYPE_IPV4_TCP) | \
	 (1ul << IXGBE_RXDADV_RSSTYPE_IPV4_UDP) | \
	 (1ul << IXGBE_RXDADV_RSSTYPE_IPV6_TCP) | \
	 (1ul << IXGBE_RXDADV_RSSTYPE_IPV6_UDP))

अटल अंतरभूत व्योम ixgbevf_rx_hash(काष्ठा ixgbevf_ring *ring,
				   जोड़ ixgbe_adv_rx_desc *rx_desc,
				   काष्ठा sk_buff *skb)
अणु
	u16 rss_type;

	अगर (!(ring->netdev->features & NETIF_F_RXHASH))
		वापस;

	rss_type = le16_to_cpu(rx_desc->wb.lower.lo_dword.hs_rss.pkt_info) &
		   IXGBE_RXDADV_RSSTYPE_MASK;

	अगर (!rss_type)
		वापस;

	skb_set_hash(skb, le32_to_cpu(rx_desc->wb.lower.hi_dword.rss),
		     (IXGBE_RSS_L4_TYPES_MASK & (1ul << rss_type)) ?
		     PKT_HASH_TYPE_L4 : PKT_HASH_TYPE_L3);
पूर्ण

/**
 * ixgbevf_rx_checksum - indicate in skb अगर hw indicated a good cksum
 * @ring: काष्ठाure containig ring specअगरic data
 * @rx_desc: current Rx descriptor being processed
 * @skb: skb currently being received and modअगरied
 **/
अटल अंतरभूत व्योम ixgbevf_rx_checksum(काष्ठा ixgbevf_ring *ring,
				       जोड़ ixgbe_adv_rx_desc *rx_desc,
				       काष्ठा sk_buff *skb)
अणु
	skb_checksum_none_निश्चित(skb);

	/* Rx csum disabled */
	अगर (!(ring->netdev->features & NETIF_F_RXCSUM))
		वापस;

	/* अगर IP and error */
	अगर (ixgbevf_test_staterr(rx_desc, IXGBE_RXD_STAT_IPCS) &&
	    ixgbevf_test_staterr(rx_desc, IXGBE_RXDADV_ERR_IPE)) अणु
		ring->rx_stats.csum_err++;
		वापस;
	पूर्ण

	अगर (!ixgbevf_test_staterr(rx_desc, IXGBE_RXD_STAT_L4CS))
		वापस;

	अगर (ixgbevf_test_staterr(rx_desc, IXGBE_RXDADV_ERR_TCPE)) अणु
		ring->rx_stats.csum_err++;
		वापस;
	पूर्ण

	/* It must be a TCP or UDP packet with a valid checksum */
	skb->ip_summed = CHECKSUM_UNNECESSARY;
पूर्ण

/**
 * ixgbevf_process_skb_fields - Populate skb header fields from Rx descriptor
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 * @skb: poपूर्णांकer to current skb being populated
 *
 * This function checks the ring, descriptor, and packet inक्रमmation in
 * order to populate the checksum, VLAN, protocol, and other fields within
 * the skb.
 **/
अटल व्योम ixgbevf_process_skb_fields(काष्ठा ixgbevf_ring *rx_ring,
				       जोड़ ixgbe_adv_rx_desc *rx_desc,
				       काष्ठा sk_buff *skb)
अणु
	ixgbevf_rx_hash(rx_ring, rx_desc, skb);
	ixgbevf_rx_checksum(rx_ring, rx_desc, skb);

	अगर (ixgbevf_test_staterr(rx_desc, IXGBE_RXD_STAT_VP)) अणु
		u16 vid = le16_to_cpu(rx_desc->wb.upper.vlan);
		अचिन्हित दीर्घ *active_vlans = netdev_priv(rx_ring->netdev);

		अगर (test_bit(vid & VLAN_VID_MASK, active_vlans))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
	पूर्ण

	अगर (ixgbevf_test_staterr(rx_desc, IXGBE_RXDADV_STAT_SECP))
		ixgbevf_ipsec_rx(rx_ring, rx_desc, skb);

	skb->protocol = eth_type_trans(skb, rx_ring->netdev);
पूर्ण

अटल
काष्ठा ixgbevf_rx_buffer *ixgbevf_get_rx_buffer(काष्ठा ixgbevf_ring *rx_ring,
						स्थिर अचिन्हित पूर्णांक size)
अणु
	काष्ठा ixgbevf_rx_buffer *rx_buffer;

	rx_buffer = &rx_ring->rx_buffer_info[rx_ring->next_to_clean];
	prefetchw(rx_buffer->page);

	/* we are reusing so sync this buffer क्रम CPU use */
	dma_sync_single_range_क्रम_cpu(rx_ring->dev,
				      rx_buffer->dma,
				      rx_buffer->page_offset,
				      size,
				      DMA_FROM_DEVICE);

	rx_buffer->pagecnt_bias--;

	वापस rx_buffer;
पूर्ण

अटल व्योम ixgbevf_put_rx_buffer(काष्ठा ixgbevf_ring *rx_ring,
				  काष्ठा ixgbevf_rx_buffer *rx_buffer,
				  काष्ठा sk_buff *skb)
अणु
	अगर (ixgbevf_can_reuse_rx_page(rx_buffer)) अणु
		/* hand second half of page back to the ring */
		ixgbevf_reuse_rx_page(rx_ring, rx_buffer);
	पूर्ण अन्यथा अणु
		अगर (IS_ERR(skb))
			/* We are not reusing the buffer so unmap it and मुक्त
			 * any references we are holding to it
			 */
			dma_unmap_page_attrs(rx_ring->dev, rx_buffer->dma,
					     ixgbevf_rx_pg_size(rx_ring),
					     DMA_FROM_DEVICE,
					     IXGBEVF_RX_DMA_ATTR);
		__page_frag_cache_drain(rx_buffer->page,
					rx_buffer->pagecnt_bias);
	पूर्ण

	/* clear contents of rx_buffer */
	rx_buffer->page = शून्य;
पूर्ण

/**
 * ixgbevf_is_non_eop - process handling of non-EOP buffers
 * @rx_ring: Rx ring being processed
 * @rx_desc: Rx descriptor क्रम current buffer
 *
 * This function updates next to clean.  If the buffer is an EOP buffer
 * this function निकासs वापसing false, otherwise it will place the
 * sk_buff in the next buffer to be chained and वापस true indicating
 * that this is in fact a non-EOP buffer.
 **/
अटल bool ixgbevf_is_non_eop(काष्ठा ixgbevf_ring *rx_ring,
			       जोड़ ixgbe_adv_rx_desc *rx_desc)
अणु
	u32 ntc = rx_ring->next_to_clean + 1;

	/* fetch, update, and store next to clean */
	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;

	prefetch(IXGBEVF_RX_DESC(rx_ring, ntc));

	अगर (likely(ixgbevf_test_staterr(rx_desc, IXGBE_RXD_STAT_EOP)))
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ixgbevf_rx_offset(काष्ठा ixgbevf_ring *rx_ring)
अणु
	वापस ring_uses_build_skb(rx_ring) ? IXGBEVF_SKB_PAD : 0;
पूर्ण

अटल bool ixgbevf_alloc_mapped_page(काष्ठा ixgbevf_ring *rx_ring,
				      काष्ठा ixgbevf_rx_buffer *bi)
अणु
	काष्ठा page *page = bi->page;
	dma_addr_t dma;

	/* since we are recycling buffers we should selकरोm need to alloc */
	अगर (likely(page))
		वापस true;

	/* alloc new page क्रम storage */
	page = dev_alloc_pages(ixgbevf_rx_pg_order(rx_ring));
	अगर (unlikely(!page)) अणु
		rx_ring->rx_stats.alloc_rx_page_failed++;
		वापस false;
	पूर्ण

	/* map page क्रम use */
	dma = dma_map_page_attrs(rx_ring->dev, page, 0,
				 ixgbevf_rx_pg_size(rx_ring),
				 DMA_FROM_DEVICE, IXGBEVF_RX_DMA_ATTR);

	/* अगर mapping failed मुक्त memory back to प्रणाली since
	 * there isn't much point in holding memory we can't use
	 */
	अगर (dma_mapping_error(rx_ring->dev, dma)) अणु
		__मुक्त_pages(page, ixgbevf_rx_pg_order(rx_ring));

		rx_ring->rx_stats.alloc_rx_page_failed++;
		वापस false;
	पूर्ण

	bi->dma = dma;
	bi->page = page;
	bi->page_offset = ixgbevf_rx_offset(rx_ring);
	bi->pagecnt_bias = 1;
	rx_ring->rx_stats.alloc_rx_page++;

	वापस true;
पूर्ण

/**
 * ixgbevf_alloc_rx_buffers - Replace used receive buffers; packet split
 * @rx_ring: rx descriptor ring (क्रम a specअगरic queue) to setup buffers on
 * @cleaned_count: number of buffers to replace
 **/
अटल व्योम ixgbevf_alloc_rx_buffers(काष्ठा ixgbevf_ring *rx_ring,
				     u16 cleaned_count)
अणु
	जोड़ ixgbe_adv_rx_desc *rx_desc;
	काष्ठा ixgbevf_rx_buffer *bi;
	अचिन्हित पूर्णांक i = rx_ring->next_to_use;

	/* nothing to करो or no valid netdev defined */
	अगर (!cleaned_count || !rx_ring->netdev)
		वापस;

	rx_desc = IXGBEVF_RX_DESC(rx_ring, i);
	bi = &rx_ring->rx_buffer_info[i];
	i -= rx_ring->count;

	करो अणु
		अगर (!ixgbevf_alloc_mapped_page(rx_ring, bi))
			अवरोध;

		/* sync the buffer क्रम use by the device */
		dma_sync_single_range_क्रम_device(rx_ring->dev, bi->dma,
						 bi->page_offset,
						 ixgbevf_rx_bufsz(rx_ring),
						 DMA_FROM_DEVICE);

		/* Refresh the desc even अगर pkt_addr didn't change
		 * because each ग_लिखो-back erases this info.
		 */
		rx_desc->पढ़ो.pkt_addr = cpu_to_le64(bi->dma + bi->page_offset);

		rx_desc++;
		bi++;
		i++;
		अगर (unlikely(!i)) अणु
			rx_desc = IXGBEVF_RX_DESC(rx_ring, 0);
			bi = rx_ring->rx_buffer_info;
			i -= rx_ring->count;
		पूर्ण

		/* clear the length क्रम the next_to_use descriptor */
		rx_desc->wb.upper.length = 0;

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
		ixgbevf_ग_लिखो_tail(rx_ring, i);
	पूर्ण
पूर्ण

/**
 * ixgbevf_cleanup_headers - Correct corrupted or empty headers
 * @rx_ring: rx descriptor ring packet is being transacted on
 * @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 * @skb: poपूर्णांकer to current skb being fixed
 *
 * Check क्रम corrupted packet headers caused by senders on the local L2
 * embedded NIC चयन not setting up their Tx Descriptors right.  These
 * should be very rare.
 *
 * Also address the हाल where we are pulling data in on pages only
 * and as such no data is present in the skb header.
 *
 * In addition अगर skb is not at least 60 bytes we need to pad it so that
 * it is large enough to qualअगरy as a valid Ethernet frame.
 *
 * Returns true अगर an error was encountered and skb was मुक्तd.
 **/
अटल bool ixgbevf_cleanup_headers(काष्ठा ixgbevf_ring *rx_ring,
				    जोड़ ixgbe_adv_rx_desc *rx_desc,
				    काष्ठा sk_buff *skb)
अणु
	/* XDP packets use error poपूर्णांकer so पात at this poपूर्णांक */
	अगर (IS_ERR(skb))
		वापस true;

	/* verअगरy that the packet करोes not have any known errors */
	अगर (unlikely(ixgbevf_test_staterr(rx_desc,
					  IXGBE_RXDADV_ERR_FRAME_ERR_MASK))) अणु
		काष्ठा net_device *netdev = rx_ring->netdev;

		अगर (!(netdev->features & NETIF_F_RXALL)) अणु
			dev_kमुक्त_skb_any(skb);
			वापस true;
		पूर्ण
	पूर्ण

	/* अगर eth_skb_pad वापसs an error the skb was मुक्तd */
	अगर (eth_skb_pad(skb))
		वापस true;

	वापस false;
पूर्ण

/**
 * ixgbevf_reuse_rx_page - page flip buffer and store it back on the ring
 * @rx_ring: rx descriptor ring to store buffers on
 * @old_buff: करोnor buffer to have page reused
 *
 * Synchronizes page क्रम reuse by the adapter
 **/
अटल व्योम ixgbevf_reuse_rx_page(काष्ठा ixgbevf_ring *rx_ring,
				  काष्ठा ixgbevf_rx_buffer *old_buff)
अणु
	काष्ठा ixgbevf_rx_buffer *new_buff;
	u16 nta = rx_ring->next_to_alloc;

	new_buff = &rx_ring->rx_buffer_info[nta];

	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* transfer page from old buffer to new buffer */
	new_buff->page = old_buff->page;
	new_buff->dma = old_buff->dma;
	new_buff->page_offset = old_buff->page_offset;
	new_buff->pagecnt_bias = old_buff->pagecnt_bias;
पूर्ण

अटल bool ixgbevf_can_reuse_rx_page(काष्ठा ixgbevf_rx_buffer *rx_buffer)
अणु
	अचिन्हित पूर्णांक pagecnt_bias = rx_buffer->pagecnt_bias;
	काष्ठा page *page = rx_buffer->page;

	/* aव्योम re-using remote and pfmeदो_स्मृति pages */
	अगर (!dev_page_is_reusable(page))
		वापस false;

#अगर (PAGE_SIZE < 8192)
	/* अगर we are only owner of page we can reuse it */
	अगर (unlikely((page_ref_count(page) - pagecnt_bias) > 1))
		वापस false;
#अन्यथा
#घोषणा IXGBEVF_LAST_OFFSET \
	(SKB_WITH_OVERHEAD(PAGE_SIZE) - IXGBEVF_RXBUFFER_2048)

	अगर (rx_buffer->page_offset > IXGBEVF_LAST_OFFSET)
		वापस false;

#पूर्ण_अगर

	/* If we have drained the page fragment pool we need to update
	 * the pagecnt_bias and page count so that we fully restock the
	 * number of references the driver holds.
	 */
	अगर (unlikely(!pagecnt_bias)) अणु
		page_ref_add(page, अच_लघु_उच्च);
		rx_buffer->pagecnt_bias = अच_लघु_उच्च;
	पूर्ण

	वापस true;
पूर्ण

/**
 * ixgbevf_add_rx_frag - Add contents of Rx buffer to sk_buff
 * @rx_ring: rx descriptor ring to transact packets on
 * @rx_buffer: buffer containing page to add
 * @skb: sk_buff to place the data पूर्णांकo
 * @size: size of buffer to be added
 *
 * This function will add the data contained in rx_buffer->page to the skb.
 **/
अटल व्योम ixgbevf_add_rx_frag(काष्ठा ixgbevf_ring *rx_ring,
				काष्ठा ixgbevf_rx_buffer *rx_buffer,
				काष्ठा sk_buff *skb,
				अचिन्हित पूर्णांक size)
अणु
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = ixgbevf_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = ring_uses_build_skb(rx_ring) ?
				SKB_DATA_ALIGN(IXGBEVF_SKB_PAD + size) :
				SKB_DATA_ALIGN(size);
#पूर्ण_अगर
	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, rx_buffer->page,
			rx_buffer->page_offset, size, truesize);
#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर
पूर्ण

अटल
काष्ठा sk_buff *ixgbevf_स्थिरruct_skb(काष्ठा ixgbevf_ring *rx_ring,
				      काष्ठा ixgbevf_rx_buffer *rx_buffer,
				      काष्ठा xdp_buff *xdp,
				      जोड़ ixgbe_adv_rx_desc *rx_desc)
अणु
	अचिन्हित पूर्णांक size = xdp->data_end - xdp->data;
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = ixgbevf_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(xdp->data_end -
					       xdp->data_hard_start);
#पूर्ण_अगर
	अचिन्हित पूर्णांक headlen;
	काष्ठा sk_buff *skb;

	/* prefetch first cache line of first page */
	net_prefetch(xdp->data);

	/* Note, we get here by enabling legacy-rx via:
	 *
	 *    ethtool --set-priv-flags <dev> legacy-rx on
	 *
	 * In this mode, we currently get 0 extra XDP headroom as
	 * opposed to having legacy-rx off, where we process XDP
	 * packets going to stack via ixgbevf_build_skb().
	 *
	 * For ixgbevf_स्थिरruct_skb() mode it means that the
	 * xdp->data_meta will always poपूर्णांक to xdp->data, since
	 * the helper cannot expand the head. Should this ever
	 * changed in future क्रम legacy-rx mode on, then lets also
	 * add xdp->data_meta handling here.
	 */

	/* allocate a skb to store the frags */
	skb = napi_alloc_skb(&rx_ring->q_vector->napi, IXGBEVF_RX_HDR_SIZE);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* Determine available headroom क्रम copy */
	headlen = size;
	अगर (headlen > IXGBEVF_RX_HDR_SIZE)
		headlen = eth_get_headlen(skb->dev, xdp->data,
					  IXGBEVF_RX_HDR_SIZE);

	/* align pull length to size of दीर्घ to optimize स_नकल perक्रमmance */
	स_नकल(__skb_put(skb, headlen), xdp->data,
	       ALIGN(headlen, माप(दीर्घ)));

	/* update all of the poपूर्णांकers */
	size -= headlen;
	अगर (size) अणु
		skb_add_rx_frag(skb, 0, rx_buffer->page,
				(xdp->data + headlen) -
					page_address(rx_buffer->page),
				size, truesize);
#अगर (PAGE_SIZE < 8192)
		rx_buffer->page_offset ^= truesize;
#अन्यथा
		rx_buffer->page_offset += truesize;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		rx_buffer->pagecnt_bias++;
	पूर्ण

	वापस skb;
पूर्ण

अटल अंतरभूत व्योम ixgbevf_irq_enable_queues(काष्ठा ixgbevf_adapter *adapter,
					     u32 qmask)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	IXGBE_WRITE_REG(hw, IXGBE_VTEIMS, qmask);
पूर्ण

अटल काष्ठा sk_buff *ixgbevf_build_skb(काष्ठा ixgbevf_ring *rx_ring,
					 काष्ठा ixgbevf_rx_buffer *rx_buffer,
					 काष्ठा xdp_buff *xdp,
					 जोड़ ixgbe_adv_rx_desc *rx_desc)
अणु
	अचिन्हित पूर्णांक metasize = xdp->data - xdp->data_meta;
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = ixgbevf_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) +
				SKB_DATA_ALIGN(xdp->data_end -
					       xdp->data_hard_start);
#पूर्ण_अगर
	काष्ठा sk_buff *skb;

	/* Prefetch first cache line of first page. If xdp->data_meta
	 * is unused, this poपूर्णांकs to xdp->data, otherwise, we likely
	 * have a consumer accessing first few bytes of meta data,
	 * and then actual data.
	 */
	net_prefetch(xdp->data_meta);

	/* build an skb around the page buffer */
	skb = build_skb(xdp->data_hard_start, truesize);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* update poपूर्णांकers within the skb to store the data */
	skb_reserve(skb, xdp->data - xdp->data_hard_start);
	__skb_put(skb, xdp->data_end - xdp->data);
	अगर (metasize)
		skb_metadata_set(skb, metasize);

	/* update buffer offset */
#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर

	वापस skb;
पूर्ण

#घोषणा IXGBEVF_XDP_PASS 0
#घोषणा IXGBEVF_XDP_CONSUMED 1
#घोषणा IXGBEVF_XDP_TX 2

अटल पूर्णांक ixgbevf_xmit_xdp_ring(काष्ठा ixgbevf_ring *ring,
				 काष्ठा xdp_buff *xdp)
अणु
	काष्ठा ixgbevf_tx_buffer *tx_buffer;
	जोड़ ixgbe_adv_tx_desc *tx_desc;
	u32 len, cmd_type;
	dma_addr_t dma;
	u16 i;

	len = xdp->data_end - xdp->data;

	अगर (unlikely(!ixgbevf_desc_unused(ring)))
		वापस IXGBEVF_XDP_CONSUMED;

	dma = dma_map_single(ring->dev, xdp->data, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(ring->dev, dma))
		वापस IXGBEVF_XDP_CONSUMED;

	/* record the location of the first descriptor क्रम this packet */
	i = ring->next_to_use;
	tx_buffer = &ring->tx_buffer_info[i];

	dma_unmap_len_set(tx_buffer, len, len);
	dma_unmap_addr_set(tx_buffer, dma, dma);
	tx_buffer->data = xdp->data;
	tx_buffer->bytecount = len;
	tx_buffer->gso_segs = 1;
	tx_buffer->protocol = 0;

	/* Populate minimal context descriptor that will provide क्रम the
	 * fact that we are expected to process Ethernet frames.
	 */
	अगर (!test_bit(__IXGBEVF_TX_XDP_RING_PRIMED, &ring->state)) अणु
		काष्ठा ixgbe_adv_tx_context_desc *context_desc;

		set_bit(__IXGBEVF_TX_XDP_RING_PRIMED, &ring->state);

		context_desc = IXGBEVF_TX_CTXTDESC(ring, 0);
		context_desc->vlan_macip_lens	=
			cpu_to_le32(ETH_HLEN << IXGBE_ADVTXD_MACLEN_SHIFT);
		context_desc->fceof_saidx	= 0;
		context_desc->type_tucmd_mlhl	=
			cpu_to_le32(IXGBE_TXD_CMD_DEXT |
				    IXGBE_ADVTXD_DTYP_CTXT);
		context_desc->mss_l4len_idx	= 0;

		i = 1;
	पूर्ण

	/* put descriptor type bits */
	cmd_type = IXGBE_ADVTXD_DTYP_DATA |
		   IXGBE_ADVTXD_DCMD_DEXT |
		   IXGBE_ADVTXD_DCMD_IFCS;
	cmd_type |= len | IXGBE_TXD_CMD;

	tx_desc = IXGBEVF_TX_DESC(ring, i);
	tx_desc->पढ़ो.buffer_addr = cpu_to_le64(dma);

	tx_desc->पढ़ो.cmd_type_len = cpu_to_le32(cmd_type);
	tx_desc->पढ़ो.olinfo_status =
			cpu_to_le32((len << IXGBE_ADVTXD_PAYLEN_SHIFT) |
				    IXGBE_ADVTXD_CC);

	/* Aव्योम any potential race with cleanup */
	smp_wmb();

	/* set next_to_watch value indicating a packet is present */
	i++;
	अगर (i == ring->count)
		i = 0;

	tx_buffer->next_to_watch = tx_desc;
	ring->next_to_use = i;

	वापस IXGBEVF_XDP_TX;
पूर्ण

अटल काष्ठा sk_buff *ixgbevf_run_xdp(काष्ठा ixgbevf_adapter *adapter,
				       काष्ठा ixgbevf_ring  *rx_ring,
				       काष्ठा xdp_buff *xdp)
अणु
	पूर्णांक result = IXGBEVF_XDP_PASS;
	काष्ठा ixgbevf_ring *xdp_ring;
	काष्ठा bpf_prog *xdp_prog;
	u32 act;

	rcu_पढ़ो_lock();
	xdp_prog = READ_ONCE(rx_ring->xdp_prog);

	अगर (!xdp_prog)
		जाओ xdp_out;

	act = bpf_prog_run_xdp(xdp_prog, xdp);
	चयन (act) अणु
	हाल XDP_PASS:
		अवरोध;
	हाल XDP_TX:
		xdp_ring = adapter->xdp_ring[rx_ring->queue_index];
		result = ixgbevf_xmit_xdp_ring(xdp_ring, xdp);
		अगर (result == IXGBEVF_XDP_CONSUMED)
			जाओ out_failure;
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
out_failure:
		trace_xdp_exception(rx_ring->netdev, xdp_prog, act);
		fallthrough; /* handle पातs by dropping packet */
	हाल XDP_DROP:
		result = IXGBEVF_XDP_CONSUMED;
		अवरोध;
	पूर्ण
xdp_out:
	rcu_पढ़ो_unlock();
	वापस ERR_PTR(-result);
पूर्ण

अटल अचिन्हित पूर्णांक ixgbevf_rx_frame_truesize(काष्ठा ixgbevf_ring *rx_ring,
					      अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक truesize;

#अगर (PAGE_SIZE < 8192)
	truesize = ixgbevf_rx_pg_size(rx_ring) / 2; /* Must be घातer-of-2 */
#अन्यथा
	truesize = ring_uses_build_skb(rx_ring) ?
		SKB_DATA_ALIGN(IXGBEVF_SKB_PAD + size) +
		SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) :
		SKB_DATA_ALIGN(size);
#पूर्ण_अगर
	वापस truesize;
पूर्ण

अटल व्योम ixgbevf_rx_buffer_flip(काष्ठा ixgbevf_ring *rx_ring,
				   काष्ठा ixgbevf_rx_buffer *rx_buffer,
				   अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक truesize = ixgbevf_rx_frame_truesize(rx_ring, size);

#अगर (PAGE_SIZE < 8192)
	rx_buffer->page_offset ^= truesize;
#अन्यथा
	rx_buffer->page_offset += truesize;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ixgbevf_clean_rx_irq(काष्ठा ixgbevf_q_vector *q_vector,
				काष्ठा ixgbevf_ring *rx_ring,
				पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक total_rx_bytes = 0, total_rx_packets = 0, frame_sz = 0;
	काष्ठा ixgbevf_adapter *adapter = q_vector->adapter;
	u16 cleaned_count = ixgbevf_desc_unused(rx_ring);
	काष्ठा sk_buff *skb = rx_ring->skb;
	bool xdp_xmit = false;
	काष्ठा xdp_buff xdp;

	/* Frame size depend on rx_ring setup when PAGE_SIZE=4K */
#अगर (PAGE_SIZE < 8192)
	frame_sz = ixgbevf_rx_frame_truesize(rx_ring, 0);
#पूर्ण_अगर
	xdp_init_buff(&xdp, frame_sz, &rx_ring->xdp_rxq);

	जबतक (likely(total_rx_packets < budget)) अणु
		काष्ठा ixgbevf_rx_buffer *rx_buffer;
		जोड़ ixgbe_adv_rx_desc *rx_desc;
		अचिन्हित पूर्णांक size;

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (cleaned_count >= IXGBEVF_RX_BUFFER_WRITE) अणु
			ixgbevf_alloc_rx_buffers(rx_ring, cleaned_count);
			cleaned_count = 0;
		पूर्ण

		rx_desc = IXGBEVF_RX_DESC(rx_ring, rx_ring->next_to_clean);
		size = le16_to_cpu(rx_desc->wb.upper.length);
		अगर (!size)
			अवरोध;

		/* This memory barrier is needed to keep us from पढ़ोing
		 * any other fields out of the rx_desc until we know the
		 * RXD_STAT_DD bit is set
		 */
		rmb();

		rx_buffer = ixgbevf_get_rx_buffer(rx_ring, size);

		/* retrieve a buffer from the ring */
		अगर (!skb) अणु
			अचिन्हित पूर्णांक offset = ixgbevf_rx_offset(rx_ring);
			अचिन्हित अक्षर *hard_start;

			hard_start = page_address(rx_buffer->page) +
				     rx_buffer->page_offset - offset;
			xdp_prepare_buff(&xdp, hard_start, offset, size, true);
#अगर (PAGE_SIZE > 4096)
			/* At larger PAGE_SIZE, frame_sz depend on len size */
			xdp.frame_sz = ixgbevf_rx_frame_truesize(rx_ring, size);
#पूर्ण_अगर
			skb = ixgbevf_run_xdp(adapter, rx_ring, &xdp);
		पूर्ण

		अगर (IS_ERR(skb)) अणु
			अगर (PTR_ERR(skb) == -IXGBEVF_XDP_TX) अणु
				xdp_xmit = true;
				ixgbevf_rx_buffer_flip(rx_ring, rx_buffer,
						       size);
			पूर्ण अन्यथा अणु
				rx_buffer->pagecnt_bias++;
			पूर्ण
			total_rx_packets++;
			total_rx_bytes += size;
		पूर्ण अन्यथा अगर (skb) अणु
			ixgbevf_add_rx_frag(rx_ring, rx_buffer, skb, size);
		पूर्ण अन्यथा अगर (ring_uses_build_skb(rx_ring)) अणु
			skb = ixgbevf_build_skb(rx_ring, rx_buffer,
						&xdp, rx_desc);
		पूर्ण अन्यथा अणु
			skb = ixgbevf_स्थिरruct_skb(rx_ring, rx_buffer,
						    &xdp, rx_desc);
		पूर्ण

		/* निकास अगर we failed to retrieve a buffer */
		अगर (!skb) अणु
			rx_ring->rx_stats.alloc_rx_buff_failed++;
			rx_buffer->pagecnt_bias++;
			अवरोध;
		पूर्ण

		ixgbevf_put_rx_buffer(rx_ring, rx_buffer, skb);
		cleaned_count++;

		/* fetch next buffer in frame अगर non-eop */
		अगर (ixgbevf_is_non_eop(rx_ring, rx_desc))
			जारी;

		/* verअगरy the packet layout is correct */
		अगर (ixgbevf_cleanup_headers(rx_ring, rx_desc, skb)) अणु
			skb = शून्य;
			जारी;
		पूर्ण

		/* probably a little skewed due to removing CRC */
		total_rx_bytes += skb->len;

		/* Workaround hardware that can't करो proper VEPA multicast
		 * source pruning.
		 */
		अगर ((skb->pkt_type == PACKET_BROADCAST ||
		     skb->pkt_type == PACKET_MULTICAST) &&
		    ether_addr_equal(rx_ring->netdev->dev_addr,
				     eth_hdr(skb)->h_source)) अणु
			dev_kमुक्त_skb_irq(skb);
			जारी;
		पूर्ण

		/* populate checksum, VLAN, and protocol */
		ixgbevf_process_skb_fields(rx_ring, rx_desc, skb);

		ixgbevf_rx_skb(q_vector, skb);

		/* reset skb poपूर्णांकer */
		skb = शून्य;

		/* update budget accounting */
		total_rx_packets++;
	पूर्ण

	/* place incomplete frames back on ring क्रम completion */
	rx_ring->skb = skb;

	अगर (xdp_xmit) अणु
		काष्ठा ixgbevf_ring *xdp_ring =
			adapter->xdp_ring[rx_ring->queue_index];

		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.
		 */
		wmb();
		ixgbevf_ग_लिखो_tail(xdp_ring, xdp_ring->next_to_use);
	पूर्ण

	u64_stats_update_begin(&rx_ring->syncp);
	rx_ring->stats.packets += total_rx_packets;
	rx_ring->stats.bytes += total_rx_bytes;
	u64_stats_update_end(&rx_ring->syncp);
	q_vector->rx.total_packets += total_rx_packets;
	q_vector->rx.total_bytes += total_rx_bytes;

	वापस total_rx_packets;
पूर्ण

/**
 * ixgbevf_poll - NAPI polling calback
 * @napi: napi काष्ठा with our devices info in it
 * @budget: amount of work driver is allowed to करो this pass, in packets
 *
 * This function will clean more than one or more rings associated with a
 * q_vector.
 **/
अटल पूर्णांक ixgbevf_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ixgbevf_q_vector *q_vector =
		container_of(napi, काष्ठा ixgbevf_q_vector, napi);
	काष्ठा ixgbevf_adapter *adapter = q_vector->adapter;
	काष्ठा ixgbevf_ring *ring;
	पूर्णांक per_ring_budget, work_करोne = 0;
	bool clean_complete = true;

	ixgbevf_क्रम_each_ring(ring, q_vector->tx) अणु
		अगर (!ixgbevf_clean_tx_irq(q_vector, ring, budget))
			clean_complete = false;
	पूर्ण

	अगर (budget <= 0)
		वापस budget;

	/* attempt to distribute budget to each queue fairly, but करोn't allow
	 * the budget to go below 1 because we'll निकास polling
	 */
	अगर (q_vector->rx.count > 1)
		per_ring_budget = max(budget/q_vector->rx.count, 1);
	अन्यथा
		per_ring_budget = budget;

	ixgbevf_क्रम_each_ring(ring, q_vector->rx) अणु
		पूर्णांक cleaned = ixgbevf_clean_rx_irq(q_vector, ring,
						   per_ring_budget);
		work_करोne += cleaned;
		अगर (cleaned >= per_ring_budget)
			clean_complete = false;
	पूर्ण

	/* If all work not completed, वापस budget and keep polling */
	अगर (!clean_complete)
		वापस budget;

	/* Exit the polling mode, but करोn't re-enable पूर्णांकerrupts अगर stack might
	 * poll us due to busy-polling
	 */
	अगर (likely(napi_complete_करोne(napi, work_करोne))) अणु
		अगर (adapter->rx_itr_setting == 1)
			ixgbevf_set_itr(q_vector);
		अगर (!test_bit(__IXGBEVF_DOWN, &adapter->state) &&
		    !test_bit(__IXGBEVF_REMOVING, &adapter->state))
			ixgbevf_irq_enable_queues(adapter,
						  BIT(q_vector->v_idx));
	पूर्ण

	वापस min(work_करोne, budget - 1);
पूर्ण

/**
 * ixgbevf_ग_लिखो_eitr - ग_लिखो VTEITR रेजिस्टर in hardware specअगरic way
 * @q_vector: काष्ठाure containing पूर्णांकerrupt and ring inक्रमmation
 **/
व्योम ixgbevf_ग_लिखो_eitr(काष्ठा ixgbevf_q_vector *q_vector)
अणु
	काष्ठा ixgbevf_adapter *adapter = q_vector->adapter;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक v_idx = q_vector->v_idx;
	u32 itr_reg = q_vector->itr & IXGBE_MAX_EITR;

	/* set the WDIS bit to not clear the समयr bits and cause an
	 * immediate निश्चितion of the पूर्णांकerrupt
	 */
	itr_reg |= IXGBE_EITR_CNT_WDIS;

	IXGBE_WRITE_REG(hw, IXGBE_VTEITR(v_idx), itr_reg);
पूर्ण

/**
 * ixgbevf_configure_msix - Configure MSI-X hardware
 * @adapter: board निजी काष्ठाure
 *
 * ixgbevf_configure_msix sets up the hardware to properly generate MSI-X
 * पूर्णांकerrupts.
 **/
अटल व्योम ixgbevf_configure_msix(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbevf_q_vector *q_vector;
	पूर्णांक q_vectors, v_idx;

	q_vectors = adapter->num_msix_vectors - NON_Q_VECTORS;
	adapter->eims_enable_mask = 0;

	/* Populate the IVAR table and set the ITR values to the
	 * corresponding रेजिस्टर.
	 */
	क्रम (v_idx = 0; v_idx < q_vectors; v_idx++) अणु
		काष्ठा ixgbevf_ring *ring;

		q_vector = adapter->q_vector[v_idx];

		ixgbevf_क्रम_each_ring(ring, q_vector->rx)
			ixgbevf_set_ivar(adapter, 0, ring->reg_idx, v_idx);

		ixgbevf_क्रम_each_ring(ring, q_vector->tx)
			ixgbevf_set_ivar(adapter, 1, ring->reg_idx, v_idx);

		अगर (q_vector->tx.ring && !q_vector->rx.ring) अणु
			/* Tx only vector */
			अगर (adapter->tx_itr_setting == 1)
				q_vector->itr = IXGBE_12K_ITR;
			अन्यथा
				q_vector->itr = adapter->tx_itr_setting;
		पूर्ण अन्यथा अणु
			/* Rx or Rx/Tx vector */
			अगर (adapter->rx_itr_setting == 1)
				q_vector->itr = IXGBE_20K_ITR;
			अन्यथा
				q_vector->itr = adapter->rx_itr_setting;
		पूर्ण

		/* add q_vector eims value to global eims_enable_mask */
		adapter->eims_enable_mask |= BIT(v_idx);

		ixgbevf_ग_लिखो_eitr(q_vector);
	पूर्ण

	ixgbevf_set_ivar(adapter, -1, 1, v_idx);
	/* setup eims_other and add value to global eims_enable_mask */
	adapter->eims_other = BIT(v_idx);
	adapter->eims_enable_mask |= adapter->eims_other;
पूर्ण

क्रमागत latency_range अणु
	lowest_latency = 0,
	low_latency = 1,
	bulk_latency = 2,
	latency_invalid = 255
पूर्ण;

/**
 * ixgbevf_update_itr - update the dynamic ITR value based on statistics
 * @q_vector: काष्ठाure containing पूर्णांकerrupt and ring inक्रमmation
 * @ring_container: काष्ठाure containing ring perक्रमmance data
 *
 * Stores a new ITR value based on packets and byte
 * counts during the last पूर्णांकerrupt.  The advantage of per पूर्णांकerrupt
 * computation is faster updates and more accurate ITR क्रम the current
 * traffic pattern.  Constants in this function were computed
 * based on theoretical maximum wire speed and thresholds were set based
 * on testing data as well as attempting to minimize response समय
 * जबतक increasing bulk throughput.
 **/
अटल व्योम ixgbevf_update_itr(काष्ठा ixgbevf_q_vector *q_vector,
			       काष्ठा ixgbevf_ring_container *ring_container)
अणु
	पूर्णांक bytes = ring_container->total_bytes;
	पूर्णांक packets = ring_container->total_packets;
	u32 समयpassed_us;
	u64 bytes_perपूर्णांक;
	u8 itr_setting = ring_container->itr;

	अगर (packets == 0)
		वापस;

	/* simple throttle rate management
	 *    0-20MB/s lowest (100000 पूर्णांकs/s)
	 *   20-100MB/s low   (20000 पूर्णांकs/s)
	 *  100-1249MB/s bulk (12000 पूर्णांकs/s)
	 */
	/* what was last पूर्णांकerrupt बारlice? */
	समयpassed_us = q_vector->itr >> 2;
	अगर (समयpassed_us == 0)
		वापस;

	bytes_perपूर्णांक = bytes / समयpassed_us; /* bytes/usec */

	चयन (itr_setting) अणु
	हाल lowest_latency:
		अगर (bytes_perपूर्णांक > 10)
			itr_setting = low_latency;
		अवरोध;
	हाल low_latency:
		अगर (bytes_perपूर्णांक > 20)
			itr_setting = bulk_latency;
		अन्यथा अगर (bytes_perपूर्णांक <= 10)
			itr_setting = lowest_latency;
		अवरोध;
	हाल bulk_latency:
		अगर (bytes_perपूर्णांक <= 20)
			itr_setting = low_latency;
		अवरोध;
	पूर्ण

	/* clear work counters since we have the values we need */
	ring_container->total_bytes = 0;
	ring_container->total_packets = 0;

	/* ग_लिखो updated itr to ring container */
	ring_container->itr = itr_setting;
पूर्ण

अटल व्योम ixgbevf_set_itr(काष्ठा ixgbevf_q_vector *q_vector)
अणु
	u32 new_itr = q_vector->itr;
	u8 current_itr;

	ixgbevf_update_itr(q_vector, &q_vector->tx);
	ixgbevf_update_itr(q_vector, &q_vector->rx);

	current_itr = max(q_vector->rx.itr, q_vector->tx.itr);

	चयन (current_itr) अणु
	/* counts and packets in update_itr are dependent on these numbers */
	हाल lowest_latency:
		new_itr = IXGBE_100K_ITR;
		अवरोध;
	हाल low_latency:
		new_itr = IXGBE_20K_ITR;
		अवरोध;
	हाल bulk_latency:
		new_itr = IXGBE_12K_ITR;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (new_itr != q_vector->itr) अणु
		/* करो an exponential smoothing */
		new_itr = (10 * new_itr * q_vector->itr) /
			  ((9 * new_itr) + q_vector->itr);

		/* save the algorithm value here */
		q_vector->itr = new_itr;

		ixgbevf_ग_लिखो_eitr(q_vector);
	पूर्ण
पूर्ण

अटल irqवापस_t ixgbevf_msix_other(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ixgbevf_adapter *adapter = data;
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	hw->mac.get_link_status = 1;

	ixgbevf_service_event_schedule(adapter);

	IXGBE_WRITE_REG(hw, IXGBE_VTEIMS, adapter->eims_other);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ixgbevf_msix_clean_rings - single unshared vector rx clean (all queues)
 * @irq: unused
 * @data: poपूर्णांकer to our q_vector काष्ठा क्रम this पूर्णांकerrupt vector
 **/
अटल irqवापस_t ixgbevf_msix_clean_rings(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ixgbevf_q_vector *q_vector = data;

	/* EIAM disabled पूर्णांकerrupts (on this vector) क्रम us */
	अगर (q_vector->rx.ring || q_vector->tx.ring)
		napi_schedule_irqoff(&q_vector->napi);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ixgbevf_request_msix_irqs - Initialize MSI-X पूर्णांकerrupts
 * @adapter: board निजी काष्ठाure
 *
 * ixgbevf_request_msix_irqs allocates MSI-X vectors and requests
 * पूर्णांकerrupts from the kernel.
 **/
अटल पूर्णांक ixgbevf_request_msix_irqs(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक q_vectors = adapter->num_msix_vectors - NON_Q_VECTORS;
	अचिन्हित पूर्णांक ri = 0, ti = 0;
	पूर्णांक vector, err;

	क्रम (vector = 0; vector < q_vectors; vector++) अणु
		काष्ठा ixgbevf_q_vector *q_vector = adapter->q_vector[vector];
		काष्ठा msix_entry *entry = &adapter->msix_entries[vector];

		अगर (q_vector->tx.ring && q_vector->rx.ring) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name),
				 "%s-TxRx-%u", netdev->name, ri++);
			ti++;
		पूर्ण अन्यथा अगर (q_vector->rx.ring) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name),
				 "%s-rx-%u", netdev->name, ri++);
		पूर्ण अन्यथा अगर (q_vector->tx.ring) अणु
			snम_लिखो(q_vector->name, माप(q_vector->name),
				 "%s-tx-%u", netdev->name, ti++);
		पूर्ण अन्यथा अणु
			/* skip this unused q_vector */
			जारी;
		पूर्ण
		err = request_irq(entry->vector, &ixgbevf_msix_clean_rings, 0,
				  q_vector->name, q_vector);
		अगर (err) अणु
			hw_dbg(&adapter->hw,
			       "request_irq failed for MSIX interrupt Error: %d\n",
			       err);
			जाओ मुक्त_queue_irqs;
		पूर्ण
	पूर्ण

	err = request_irq(adapter->msix_entries[vector].vector,
			  &ixgbevf_msix_other, 0, netdev->name, adapter);
	अगर (err) अणु
		hw_dbg(&adapter->hw, "request_irq for msix_other failed: %d\n",
		       err);
		जाओ मुक्त_queue_irqs;
	पूर्ण

	वापस 0;

मुक्त_queue_irqs:
	जबतक (vector) अणु
		vector--;
		मुक्त_irq(adapter->msix_entries[vector].vector,
			 adapter->q_vector[vector]);
	पूर्ण
	/* This failure is non-recoverable - it indicates the प्रणाली is
	 * out of MSIX vector resources and the VF driver cannot run
	 * without them.  Set the number of msix vectors to zero
	 * indicating that not enough can be allocated.  The error
	 * will be वापसed to the user indicating device खोलो failed.
	 * Any further attempts to क्रमce the driver to खोलो will also
	 * fail.  The only way to recover is to unload the driver and
	 * reload it again.  If the प्रणाली has recovered some MSIX
	 * vectors then it may succeed.
	 */
	adapter->num_msix_vectors = 0;
	वापस err;
पूर्ण

/**
 * ixgbevf_request_irq - initialize पूर्णांकerrupts
 * @adapter: board निजी काष्ठाure
 *
 * Attempts to configure पूर्णांकerrupts using the best available
 * capabilities of the hardware and kernel.
 **/
अटल पूर्णांक ixgbevf_request_irq(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक err = ixgbevf_request_msix_irqs(adapter);

	अगर (err)
		hw_dbg(&adapter->hw, "request_irq failed, Error %d\n", err);

	वापस err;
पूर्ण

अटल व्योम ixgbevf_मुक्त_irq(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक i, q_vectors;

	अगर (!adapter->msix_entries)
		वापस;

	q_vectors = adapter->num_msix_vectors;
	i = q_vectors - 1;

	मुक्त_irq(adapter->msix_entries[i].vector, adapter);
	i--;

	क्रम (; i >= 0; i--) अणु
		/* मुक्त only the irqs that were actually requested */
		अगर (!adapter->q_vector[i]->rx.ring &&
		    !adapter->q_vector[i]->tx.ring)
			जारी;

		मुक्त_irq(adapter->msix_entries[i].vector,
			 adapter->q_vector[i]);
	पूर्ण
पूर्ण

/**
 * ixgbevf_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter: board निजी काष्ठाure
 **/
अटल अंतरभूत व्योम ixgbevf_irq_disable(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;

	IXGBE_WRITE_REG(hw, IXGBE_VTEIAM, 0);
	IXGBE_WRITE_REG(hw, IXGBE_VTEIMC, ~0);
	IXGBE_WRITE_REG(hw, IXGBE_VTEIAC, 0);

	IXGBE_WRITE_FLUSH(hw);

	क्रम (i = 0; i < adapter->num_msix_vectors; i++)
		synchronize_irq(adapter->msix_entries[i].vector);
पूर्ण

/**
 * ixgbevf_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter: board निजी काष्ठाure
 **/
अटल अंतरभूत व्योम ixgbevf_irq_enable(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	IXGBE_WRITE_REG(hw, IXGBE_VTEIAM, adapter->eims_enable_mask);
	IXGBE_WRITE_REG(hw, IXGBE_VTEIAC, adapter->eims_enable_mask);
	IXGBE_WRITE_REG(hw, IXGBE_VTEIMS, adapter->eims_enable_mask);
पूर्ण

/**
 * ixgbevf_configure_tx_ring - Configure 82599 VF Tx ring after Reset
 * @adapter: board निजी काष्ठाure
 * @ring: काष्ठाure containing ring specअगरic data
 *
 * Configure the Tx descriptor ring after a reset.
 **/
अटल व्योम ixgbevf_configure_tx_ring(काष्ठा ixgbevf_adapter *adapter,
				      काष्ठा ixgbevf_ring *ring)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u64 tdba = ring->dma;
	पूर्णांक रुको_loop = 10;
	u32 txdctl = IXGBE_TXDCTL_ENABLE;
	u8 reg_idx = ring->reg_idx;

	/* disable queue to aव्योम issues जबतक updating state */
	IXGBE_WRITE_REG(hw, IXGBE_VFTXDCTL(reg_idx), IXGBE_TXDCTL_SWFLSH);
	IXGBE_WRITE_FLUSH(hw);

	IXGBE_WRITE_REG(hw, IXGBE_VFTDBAL(reg_idx), tdba & DMA_BIT_MASK(32));
	IXGBE_WRITE_REG(hw, IXGBE_VFTDBAH(reg_idx), tdba >> 32);
	IXGBE_WRITE_REG(hw, IXGBE_VFTDLEN(reg_idx),
			ring->count * माप(जोड़ ixgbe_adv_tx_desc));

	/* disable head ग_लिखोback */
	IXGBE_WRITE_REG(hw, IXGBE_VFTDWBAH(reg_idx), 0);
	IXGBE_WRITE_REG(hw, IXGBE_VFTDWBAL(reg_idx), 0);

	/* enable relaxed ordering */
	IXGBE_WRITE_REG(hw, IXGBE_VFDCA_TXCTRL(reg_idx),
			(IXGBE_DCA_TXCTRL_DESC_RRO_EN |
			 IXGBE_DCA_TXCTRL_DATA_RRO_EN));

	/* reset head and tail poपूर्णांकers */
	IXGBE_WRITE_REG(hw, IXGBE_VFTDH(reg_idx), 0);
	IXGBE_WRITE_REG(hw, IXGBE_VFTDT(reg_idx), 0);
	ring->tail = adapter->io_addr + IXGBE_VFTDT(reg_idx);

	/* reset ntu and ntc to place SW in sync with hardwdare */
	ring->next_to_clean = 0;
	ring->next_to_use = 0;

	/* In order to aव्योम issues WTHRESH + PTHRESH should always be equal
	 * to or less than the number of on chip descriptors, which is
	 * currently 40.
	 */
	txdctl |= (8 << 16);    /* WTHRESH = 8 */

	/* Setting PTHRESH to 32 both improves perक्रमmance */
	txdctl |= (1u << 8) |    /* HTHRESH = 1 */
		   32;           /* PTHRESH = 32 */

	/* reinitialize tx_buffer_info */
	स_रखो(ring->tx_buffer_info, 0,
	       माप(काष्ठा ixgbevf_tx_buffer) * ring->count);

	clear_bit(__IXGBEVF_HANG_CHECK_ARMED, &ring->state);
	clear_bit(__IXGBEVF_TX_XDP_RING_PRIMED, &ring->state);

	IXGBE_WRITE_REG(hw, IXGBE_VFTXDCTL(reg_idx), txdctl);

	/* poll to verअगरy queue is enabled */
	करो अणु
		usleep_range(1000, 2000);
		txdctl = IXGBE_READ_REG(hw, IXGBE_VFTXDCTL(reg_idx));
	पूर्ण  जबतक (--रुको_loop && !(txdctl & IXGBE_TXDCTL_ENABLE));
	अगर (!रुको_loop)
		hw_dbg(hw, "Could not enable Tx Queue %d\n", reg_idx);
पूर्ण

/**
 * ixgbevf_configure_tx - Configure 82599 VF Transmit Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Tx unit of the MAC after a reset.
 **/
अटल व्योम ixgbevf_configure_tx(काष्ठा ixgbevf_adapter *adapter)
अणु
	u32 i;

	/* Setup the HW Tx Head and Tail descriptor poपूर्णांकers */
	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		ixgbevf_configure_tx_ring(adapter, adapter->tx_ring[i]);
	क्रम (i = 0; i < adapter->num_xdp_queues; i++)
		ixgbevf_configure_tx_ring(adapter, adapter->xdp_ring[i]);
पूर्ण

#घोषणा IXGBE_SRRCTL_BSIZEHDRSIZE_SHIFT	2

अटल व्योम ixgbevf_configure_srrctl(काष्ठा ixgbevf_adapter *adapter,
				     काष्ठा ixgbevf_ring *ring, पूर्णांक index)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 srrctl;

	srrctl = IXGBE_SRRCTL_DROP_EN;

	srrctl |= IXGBEVF_RX_HDR_SIZE << IXGBE_SRRCTL_BSIZEHDRSIZE_SHIFT;
	अगर (ring_uses_large_buffer(ring))
		srrctl |= IXGBEVF_RXBUFFER_3072 >> IXGBE_SRRCTL_BSIZEPKT_SHIFT;
	अन्यथा
		srrctl |= IXGBEVF_RXBUFFER_2048 >> IXGBE_SRRCTL_BSIZEPKT_SHIFT;
	srrctl |= IXGBE_SRRCTL_DESCTYPE_ADV_ONEBUF;

	IXGBE_WRITE_REG(hw, IXGBE_VFSRRCTL(index), srrctl);
पूर्ण

अटल व्योम ixgbevf_setup_psrtype(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	/* PSRTYPE must be initialized in 82599 */
	u32 psrtype = IXGBE_PSRTYPE_TCPHDR | IXGBE_PSRTYPE_UDPHDR |
		      IXGBE_PSRTYPE_IPV4HDR | IXGBE_PSRTYPE_IPV6HDR |
		      IXGBE_PSRTYPE_L2HDR;

	अगर (adapter->num_rx_queues > 1)
		psrtype |= BIT(29);

	IXGBE_WRITE_REG(hw, IXGBE_VFPSRTYPE, psrtype);
पूर्ण

#घोषणा IXGBEVF_MAX_RX_DESC_POLL 10
अटल व्योम ixgbevf_disable_rx_queue(काष्ठा ixgbevf_adapter *adapter,
				     काष्ठा ixgbevf_ring *ring)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक रुको_loop = IXGBEVF_MAX_RX_DESC_POLL;
	u32 rxdctl;
	u8 reg_idx = ring->reg_idx;

	अगर (IXGBE_REMOVED(hw->hw_addr))
		वापस;
	rxdctl = IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(reg_idx));
	rxdctl &= ~IXGBE_RXDCTL_ENABLE;

	/* ग_लिखो value back with RXDCTL.ENABLE bit cleared */
	IXGBE_WRITE_REG(hw, IXGBE_VFRXDCTL(reg_idx), rxdctl);

	/* the hardware may take up to 100us to really disable the Rx queue */
	करो अणु
		udelay(10);
		rxdctl = IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(reg_idx));
	पूर्ण जबतक (--रुको_loop && (rxdctl & IXGBE_RXDCTL_ENABLE));

	अगर (!रुको_loop)
		pr_err("RXDCTL.ENABLE queue %d not cleared while polling\n",
		       reg_idx);
पूर्ण

अटल व्योम ixgbevf_rx_desc_queue_enable(काष्ठा ixgbevf_adapter *adapter,
					 काष्ठा ixgbevf_ring *ring)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक रुको_loop = IXGBEVF_MAX_RX_DESC_POLL;
	u32 rxdctl;
	u8 reg_idx = ring->reg_idx;

	अगर (IXGBE_REMOVED(hw->hw_addr))
		वापस;
	करो अणु
		usleep_range(1000, 2000);
		rxdctl = IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(reg_idx));
	पूर्ण जबतक (--रुको_loop && !(rxdctl & IXGBE_RXDCTL_ENABLE));

	अगर (!रुको_loop)
		pr_err("RXDCTL.ENABLE queue %d not set while polling\n",
		       reg_idx);
पूर्ण

/**
 * ixgbevf_init_rss_key - Initialize adapter RSS key
 * @adapter: device handle
 *
 * Allocates and initializes the RSS key अगर it is not allocated.
 **/
अटल अंतरभूत पूर्णांक ixgbevf_init_rss_key(काष्ठा ixgbevf_adapter *adapter)
अणु
	u32 *rss_key;

	अगर (!adapter->rss_key) अणु
		rss_key = kzalloc(IXGBEVF_RSS_HASH_KEY_SIZE, GFP_KERNEL);
		अगर (unlikely(!rss_key))
			वापस -ENOMEM;

		netdev_rss_key_fill(rss_key, IXGBEVF_RSS_HASH_KEY_SIZE);
		adapter->rss_key = rss_key;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ixgbevf_setup_vfmrqc(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 vfmrqc = 0, vfreta = 0;
	u16 rss_i = adapter->num_rx_queues;
	u8 i, j;

	/* Fill out hash function seeds */
	क्रम (i = 0; i < IXGBEVF_VFRSSRK_REGS; i++)
		IXGBE_WRITE_REG(hw, IXGBE_VFRSSRK(i), *(adapter->rss_key + i));

	क्रम (i = 0, j = 0; i < IXGBEVF_X550_VFRETA_SIZE; i++, j++) अणु
		अगर (j == rss_i)
			j = 0;

		adapter->rss_indir_tbl[i] = j;

		vfreta |= j << (i & 0x3) * 8;
		अगर ((i & 3) == 3) अणु
			IXGBE_WRITE_REG(hw, IXGBE_VFRETA(i >> 2), vfreta);
			vfreta = 0;
		पूर्ण
	पूर्ण

	/* Perक्रमm hash on these packet types */
	vfmrqc |= IXGBE_VFMRQC_RSS_FIELD_IPV4 |
		IXGBE_VFMRQC_RSS_FIELD_IPV4_TCP |
		IXGBE_VFMRQC_RSS_FIELD_IPV6 |
		IXGBE_VFMRQC_RSS_FIELD_IPV6_TCP;

	vfmrqc |= IXGBE_VFMRQC_RSSEN;

	IXGBE_WRITE_REG(hw, IXGBE_VFMRQC, vfmrqc);
पूर्ण

अटल व्योम ixgbevf_configure_rx_ring(काष्ठा ixgbevf_adapter *adapter,
				      काष्ठा ixgbevf_ring *ring)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	जोड़ ixgbe_adv_rx_desc *rx_desc;
	u64 rdba = ring->dma;
	u32 rxdctl;
	u8 reg_idx = ring->reg_idx;

	/* disable queue to aव्योम issues जबतक updating state */
	rxdctl = IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(reg_idx));
	ixgbevf_disable_rx_queue(adapter, ring);

	IXGBE_WRITE_REG(hw, IXGBE_VFRDBAL(reg_idx), rdba & DMA_BIT_MASK(32));
	IXGBE_WRITE_REG(hw, IXGBE_VFRDBAH(reg_idx), rdba >> 32);
	IXGBE_WRITE_REG(hw, IXGBE_VFRDLEN(reg_idx),
			ring->count * माप(जोड़ ixgbe_adv_rx_desc));

#अगर_अघोषित CONFIG_SPARC
	/* enable relaxed ordering */
	IXGBE_WRITE_REG(hw, IXGBE_VFDCA_RXCTRL(reg_idx),
			IXGBE_DCA_RXCTRL_DESC_RRO_EN);
#अन्यथा
	IXGBE_WRITE_REG(hw, IXGBE_VFDCA_RXCTRL(reg_idx),
			IXGBE_DCA_RXCTRL_DESC_RRO_EN |
			IXGBE_DCA_RXCTRL_DATA_WRO_EN);
#पूर्ण_अगर

	/* reset head and tail poपूर्णांकers */
	IXGBE_WRITE_REG(hw, IXGBE_VFRDH(reg_idx), 0);
	IXGBE_WRITE_REG(hw, IXGBE_VFRDT(reg_idx), 0);
	ring->tail = adapter->io_addr + IXGBE_VFRDT(reg_idx);

	/* initialize rx_buffer_info */
	स_रखो(ring->rx_buffer_info, 0,
	       माप(काष्ठा ixgbevf_rx_buffer) * ring->count);

	/* initialize Rx descriptor 0 */
	rx_desc = IXGBEVF_RX_DESC(ring, 0);
	rx_desc->wb.upper.length = 0;

	/* reset ntu and ntc to place SW in sync with hardwdare */
	ring->next_to_clean = 0;
	ring->next_to_use = 0;
	ring->next_to_alloc = 0;

	ixgbevf_configure_srrctl(adapter, ring, reg_idx);

	/* RXDCTL.RLPML करोes not work on 82599 */
	अगर (adapter->hw.mac.type != ixgbe_mac_82599_vf) अणु
		rxdctl &= ~(IXGBE_RXDCTL_RLPMLMASK |
			    IXGBE_RXDCTL_RLPML_EN);

#अगर (PAGE_SIZE < 8192)
		/* Limit the maximum frame size so we करोn't overrun the skb */
		अगर (ring_uses_build_skb(ring) &&
		    !ring_uses_large_buffer(ring))
			rxdctl |= IXGBEVF_MAX_FRAME_BUILD_SKB |
				  IXGBE_RXDCTL_RLPML_EN;
#पूर्ण_अगर
	पूर्ण

	rxdctl |= IXGBE_RXDCTL_ENABLE | IXGBE_RXDCTL_VME;
	IXGBE_WRITE_REG(hw, IXGBE_VFRXDCTL(reg_idx), rxdctl);

	ixgbevf_rx_desc_queue_enable(adapter, ring);
	ixgbevf_alloc_rx_buffers(ring, ixgbevf_desc_unused(ring));
पूर्ण

अटल व्योम ixgbevf_set_rx_buffer_len(काष्ठा ixgbevf_adapter *adapter,
				      काष्ठा ixgbevf_ring *rx_ring)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	अचिन्हित पूर्णांक max_frame = netdev->mtu + ETH_HLEN + ETH_FCS_LEN;

	/* set build_skb and buffer size flags */
	clear_ring_build_skb_enabled(rx_ring);
	clear_ring_uses_large_buffer(rx_ring);

	अगर (adapter->flags & IXGBEVF_FLAGS_LEGACY_RX)
		वापस;

	set_ring_build_skb_enabled(rx_ring);

	अगर (PAGE_SIZE < 8192) अणु
		अगर (max_frame <= IXGBEVF_MAX_FRAME_BUILD_SKB)
			वापस;

		set_ring_uses_large_buffer(rx_ring);
	पूर्ण
पूर्ण

/**
 * ixgbevf_configure_rx - Configure 82599 VF Receive Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Rx unit of the MAC after a reset.
 **/
अटल व्योम ixgbevf_configure_rx(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक i, ret;

	ixgbevf_setup_psrtype(adapter);
	अगर (hw->mac.type >= ixgbe_mac_X550_vf)
		ixgbevf_setup_vfmrqc(adapter);

	spin_lock_bh(&adapter->mbx_lock);
	/* notअगरy the PF of our पूर्णांकent to use this size of frame */
	ret = hw->mac.ops.set_rlpml(hw, netdev->mtu + ETH_HLEN + ETH_FCS_LEN);
	spin_unlock_bh(&adapter->mbx_lock);
	अगर (ret)
		dev_err(&adapter->pdev->dev,
			"Failed to set MTU at %d\n", netdev->mtu);

	/* Setup the HW Rx Head and Tail Descriptor Poपूर्णांकers and
	 * the Base and Length of the Rx Descriptor Ring
	 */
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा ixgbevf_ring *rx_ring = adapter->rx_ring[i];

		ixgbevf_set_rx_buffer_len(adapter, rx_ring);
		ixgbevf_configure_rx_ring(adapter, rx_ring);
	पूर्ण
पूर्ण

अटल पूर्णांक ixgbevf_vlan_rx_add_vid(काष्ठा net_device *netdev,
				   __be16 proto, u16 vid)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक err;

	spin_lock_bh(&adapter->mbx_lock);

	/* add VID to filter table */
	err = hw->mac.ops.set_vfta(hw, vid, 0, true);

	spin_unlock_bh(&adapter->mbx_lock);

	/* translate error वापस types so error makes sense */
	अगर (err == IXGBE_ERR_MBX)
		वापस -EIO;

	अगर (err == IXGBE_ERR_INVALID_ARGUMENT)
		वापस -EACCES;

	set_bit(vid, adapter->active_vlans);

	वापस err;
पूर्ण

अटल पूर्णांक ixgbevf_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				    __be16 proto, u16 vid)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक err;

	spin_lock_bh(&adapter->mbx_lock);

	/* हटाओ VID from filter table */
	err = hw->mac.ops.set_vfta(hw, vid, 0, false);

	spin_unlock_bh(&adapter->mbx_lock);

	clear_bit(vid, adapter->active_vlans);

	वापस err;
पूर्ण

अटल व्योम ixgbevf_restore_vlan(काष्ठा ixgbevf_adapter *adapter)
अणु
	u16 vid;

	क्रम_each_set_bit(vid, adapter->active_vlans, VLAN_N_VID)
		ixgbevf_vlan_rx_add_vid(adapter->netdev,
					htons(ETH_P_8021Q), vid);
पूर्ण

अटल पूर्णांक ixgbevf_ग_लिखो_uc_addr_list(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक count = 0;

	अगर (!netdev_uc_empty(netdev)) अणु
		काष्ठा netdev_hw_addr *ha;

		netdev_क्रम_each_uc_addr(ha, netdev) अणु
			hw->mac.ops.set_uc_addr(hw, ++count, ha->addr);
			udelay(200);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If the list is empty then send message to PF driver to
		 * clear all MAC VLANs on this VF.
		 */
		hw->mac.ops.set_uc_addr(hw, 0, शून्य);
	पूर्ण

	वापस count;
पूर्ण

/**
 * ixgbevf_set_rx_mode - Multicast and unicast set
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The set_rx_method entry poपूर्णांक is called whenever the multicast address
 * list, unicast address list or the network पूर्णांकerface flags are updated.
 * This routine is responsible क्रम configuring the hardware क्रम proper
 * multicast mode and configuring requested unicast filters.
 **/
अटल व्योम ixgbevf_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	अचिन्हित पूर्णांक flags = netdev->flags;
	पूर्णांक xcast_mode;

	/* request the most inclusive mode we need */
	अगर (flags & IFF_PROMISC)
		xcast_mode = IXGBEVF_XCAST_MODE_PROMISC;
	अन्यथा अगर (flags & IFF_ALLMULTI)
		xcast_mode = IXGBEVF_XCAST_MODE_ALLMULTI;
	अन्यथा अगर (flags & (IFF_BROADCAST | IFF_MULTICAST))
		xcast_mode = IXGBEVF_XCAST_MODE_MULTI;
	अन्यथा
		xcast_mode = IXGBEVF_XCAST_MODE_NONE;

	spin_lock_bh(&adapter->mbx_lock);

	hw->mac.ops.update_xcast_mode(hw, xcast_mode);

	/* reprogram multicast list */
	hw->mac.ops.update_mc_addr_list(hw, netdev);

	ixgbevf_ग_लिखो_uc_addr_list(netdev);

	spin_unlock_bh(&adapter->mbx_lock);
पूर्ण

अटल व्योम ixgbevf_napi_enable_all(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक q_idx;
	काष्ठा ixgbevf_q_vector *q_vector;
	पूर्णांक q_vectors = adapter->num_msix_vectors - NON_Q_VECTORS;

	क्रम (q_idx = 0; q_idx < q_vectors; q_idx++) अणु
		q_vector = adapter->q_vector[q_idx];
		napi_enable(&q_vector->napi);
	पूर्ण
पूर्ण

अटल व्योम ixgbevf_napi_disable_all(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक q_idx;
	काष्ठा ixgbevf_q_vector *q_vector;
	पूर्णांक q_vectors = adapter->num_msix_vectors - NON_Q_VECTORS;

	क्रम (q_idx = 0; q_idx < q_vectors; q_idx++) अणु
		q_vector = adapter->q_vector[q_idx];
		napi_disable(&q_vector->napi);
	पूर्ण
पूर्ण

अटल पूर्णांक ixgbevf_configure_dcb(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	अचिन्हित पूर्णांक def_q = 0;
	अचिन्हित पूर्णांक num_tcs = 0;
	अचिन्हित पूर्णांक num_rx_queues = adapter->num_rx_queues;
	अचिन्हित पूर्णांक num_tx_queues = adapter->num_tx_queues;
	पूर्णांक err;

	spin_lock_bh(&adapter->mbx_lock);

	/* fetch queue configuration from the PF */
	err = ixgbevf_get_queues(hw, &num_tcs, &def_q);

	spin_unlock_bh(&adapter->mbx_lock);

	अगर (err)
		वापस err;

	अगर (num_tcs > 1) अणु
		/* we need only one Tx queue */
		num_tx_queues = 1;

		/* update शेष Tx ring रेजिस्टर index */
		adapter->tx_ring[0]->reg_idx = def_q;

		/* we need as many queues as traffic classes */
		num_rx_queues = num_tcs;
	पूर्ण

	/* अगर we have a bad config पात request queue reset */
	अगर ((adapter->num_rx_queues != num_rx_queues) ||
	    (adapter->num_tx_queues != num_tx_queues)) अणु
		/* क्रमce mailbox समयout to prevent further messages */
		hw->mbx.समयout = 0;

		/* रुको क्रम watchकरोg to come around and bail us out */
		set_bit(__IXGBEVF_QUEUE_RESET_REQUESTED, &adapter->state);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ixgbevf_configure(काष्ठा ixgbevf_adapter *adapter)
अणु
	ixgbevf_configure_dcb(adapter);

	ixgbevf_set_rx_mode(adapter->netdev);

	ixgbevf_restore_vlan(adapter);
	ixgbevf_ipsec_restore(adapter);

	ixgbevf_configure_tx(adapter);
	ixgbevf_configure_rx(adapter);
पूर्ण

अटल व्योम ixgbevf_save_reset_stats(काष्ठा ixgbevf_adapter *adapter)
अणु
	/* Only save pre-reset stats अगर there are some */
	अगर (adapter->stats.vfgprc || adapter->stats.vfgptc) अणु
		adapter->stats.saved_reset_vfgprc += adapter->stats.vfgprc -
			adapter->stats.base_vfgprc;
		adapter->stats.saved_reset_vfgptc += adapter->stats.vfgptc -
			adapter->stats.base_vfgptc;
		adapter->stats.saved_reset_vfgorc += adapter->stats.vfgorc -
			adapter->stats.base_vfgorc;
		adapter->stats.saved_reset_vfgotc += adapter->stats.vfgotc -
			adapter->stats.base_vfgotc;
		adapter->stats.saved_reset_vfmprc += adapter->stats.vfmprc -
			adapter->stats.base_vfmprc;
	पूर्ण
पूर्ण

अटल व्योम ixgbevf_init_last_counter_stats(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	adapter->stats.last_vfgprc = IXGBE_READ_REG(hw, IXGBE_VFGPRC);
	adapter->stats.last_vfgorc = IXGBE_READ_REG(hw, IXGBE_VFGORC_LSB);
	adapter->stats.last_vfgorc |=
		(((u64)(IXGBE_READ_REG(hw, IXGBE_VFGORC_MSB))) << 32);
	adapter->stats.last_vfgptc = IXGBE_READ_REG(hw, IXGBE_VFGPTC);
	adapter->stats.last_vfgotc = IXGBE_READ_REG(hw, IXGBE_VFGOTC_LSB);
	adapter->stats.last_vfgotc |=
		(((u64)(IXGBE_READ_REG(hw, IXGBE_VFGOTC_MSB))) << 32);
	adapter->stats.last_vfmprc = IXGBE_READ_REG(hw, IXGBE_VFMPRC);

	adapter->stats.base_vfgprc = adapter->stats.last_vfgprc;
	adapter->stats.base_vfgorc = adapter->stats.last_vfgorc;
	adapter->stats.base_vfgptc = adapter->stats.last_vfgptc;
	adapter->stats.base_vfgotc = adapter->stats.last_vfgotc;
	adapter->stats.base_vfmprc = adapter->stats.last_vfmprc;
पूर्ण

अटल व्योम ixgbevf_negotiate_api(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	अटल स्थिर पूर्णांक api[] = अणु
		ixgbe_mbox_api_14,
		ixgbe_mbox_api_13,
		ixgbe_mbox_api_12,
		ixgbe_mbox_api_11,
		ixgbe_mbox_api_10,
		ixgbe_mbox_api_unknown
	पूर्ण;
	पूर्णांक err, idx = 0;

	spin_lock_bh(&adapter->mbx_lock);

	जबतक (api[idx] != ixgbe_mbox_api_unknown) अणु
		err = hw->mac.ops.negotiate_api_version(hw, api[idx]);
		अगर (!err)
			अवरोध;
		idx++;
	पूर्ण

	spin_unlock_bh(&adapter->mbx_lock);
पूर्ण

अटल व्योम ixgbevf_up_complete(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	ixgbevf_configure_msix(adapter);

	spin_lock_bh(&adapter->mbx_lock);

	अगर (is_valid_ether_addr(hw->mac.addr))
		hw->mac.ops.set_rar(hw, 0, hw->mac.addr, 0);
	अन्यथा
		hw->mac.ops.set_rar(hw, 0, hw->mac.perm_addr, 0);

	spin_unlock_bh(&adapter->mbx_lock);

	smp_mb__beक्रमe_atomic();
	clear_bit(__IXGBEVF_DOWN, &adapter->state);
	ixgbevf_napi_enable_all(adapter);

	/* clear any pending पूर्णांकerrupts, may स्वतः mask */
	IXGBE_READ_REG(hw, IXGBE_VTEICR);
	ixgbevf_irq_enable(adapter);

	/* enable transmits */
	netअगर_tx_start_all_queues(netdev);

	ixgbevf_save_reset_stats(adapter);
	ixgbevf_init_last_counter_stats(adapter);

	hw->mac.get_link_status = 1;
	mod_समयr(&adapter->service_समयr, jअगरfies);
पूर्ण

व्योम ixgbevf_up(काष्ठा ixgbevf_adapter *adapter)
अणु
	ixgbevf_configure(adapter);

	ixgbevf_up_complete(adapter);
पूर्ण

/**
 * ixgbevf_clean_rx_ring - Free Rx Buffers per Queue
 * @rx_ring: ring to मुक्त buffers from
 **/
अटल व्योम ixgbevf_clean_rx_ring(काष्ठा ixgbevf_ring *rx_ring)
अणु
	u16 i = rx_ring->next_to_clean;

	/* Free Rx ring sk_buff */
	अगर (rx_ring->skb) अणु
		dev_kमुक्त_skb(rx_ring->skb);
		rx_ring->skb = शून्य;
	पूर्ण

	/* Free all the Rx ring pages */
	जबतक (i != rx_ring->next_to_alloc) अणु
		काष्ठा ixgbevf_rx_buffer *rx_buffer;

		rx_buffer = &rx_ring->rx_buffer_info[i];

		/* Invalidate cache lines that may have been written to by
		 * device so that we aव्योम corrupting memory.
		 */
		dma_sync_single_range_क्रम_cpu(rx_ring->dev,
					      rx_buffer->dma,
					      rx_buffer->page_offset,
					      ixgbevf_rx_bufsz(rx_ring),
					      DMA_FROM_DEVICE);

		/* मुक्त resources associated with mapping */
		dma_unmap_page_attrs(rx_ring->dev,
				     rx_buffer->dma,
				     ixgbevf_rx_pg_size(rx_ring),
				     DMA_FROM_DEVICE,
				     IXGBEVF_RX_DMA_ATTR);

		__page_frag_cache_drain(rx_buffer->page,
					rx_buffer->pagecnt_bias);

		i++;
		अगर (i == rx_ring->count)
			i = 0;
	पूर्ण

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
पूर्ण

/**
 * ixgbevf_clean_tx_ring - Free Tx Buffers
 * @tx_ring: ring to be cleaned
 **/
अटल व्योम ixgbevf_clean_tx_ring(काष्ठा ixgbevf_ring *tx_ring)
अणु
	u16 i = tx_ring->next_to_clean;
	काष्ठा ixgbevf_tx_buffer *tx_buffer = &tx_ring->tx_buffer_info[i];

	जबतक (i != tx_ring->next_to_use) अणु
		जोड़ ixgbe_adv_tx_desc *eop_desc, *tx_desc;

		/* Free all the Tx ring sk_buffs */
		अगर (ring_is_xdp(tx_ring))
			page_frag_मुक्त(tx_buffer->data);
		अन्यथा
			dev_kमुक्त_skb_any(tx_buffer->skb);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);

		/* check क्रम eop_desc to determine the end of the packet */
		eop_desc = tx_buffer->next_to_watch;
		tx_desc = IXGBEVF_TX_DESC(tx_ring, i);

		/* unmap reमुख्यing buffers */
		जबतक (tx_desc != eop_desc) अणु
			tx_buffer++;
			tx_desc++;
			i++;
			अगर (unlikely(i == tx_ring->count)) अणु
				i = 0;
				tx_buffer = tx_ring->tx_buffer_info;
				tx_desc = IXGBEVF_TX_DESC(tx_ring, 0);
			पूर्ण

			/* unmap any reमुख्यing paged data */
			अगर (dma_unmap_len(tx_buffer, len))
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buffer, dma),
					       dma_unmap_len(tx_buffer, len),
					       DMA_TO_DEVICE);
		पूर्ण

		/* move us one more past the eop_desc क्रम start of next pkt */
		tx_buffer++;
		i++;
		अगर (unlikely(i == tx_ring->count)) अणु
			i = 0;
			tx_buffer = tx_ring->tx_buffer_info;
		पूर्ण
	पूर्ण

	/* reset next_to_use and next_to_clean */
	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

पूर्ण

/**
 * ixgbevf_clean_all_rx_rings - Free Rx Buffers क्रम all queues
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम ixgbevf_clean_all_rx_rings(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		ixgbevf_clean_rx_ring(adapter->rx_ring[i]);
पूर्ण

/**
 * ixgbevf_clean_all_tx_rings - Free Tx Buffers क्रम all queues
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम ixgbevf_clean_all_tx_rings(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		ixgbevf_clean_tx_ring(adapter->tx_ring[i]);
	क्रम (i = 0; i < adapter->num_xdp_queues; i++)
		ixgbevf_clean_tx_ring(adapter->xdp_ring[i]);
पूर्ण

व्योम ixgbevf_करोwn(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i;

	/* संकेत that we are करोwn to the पूर्णांकerrupt handler */
	अगर (test_and_set_bit(__IXGBEVF_DOWN, &adapter->state))
		वापस; /* करो nothing अगर alपढ़ोy करोwn */

	/* disable all enabled Rx queues */
	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		ixgbevf_disable_rx_queue(adapter, adapter->rx_ring[i]);

	usleep_range(10000, 20000);

	netअगर_tx_stop_all_queues(netdev);

	/* call carrier off first to aव्योम false dev_watchकरोg समयouts */
	netअगर_carrier_off(netdev);
	netअगर_tx_disable(netdev);

	ixgbevf_irq_disable(adapter);

	ixgbevf_napi_disable_all(adapter);

	del_समयr_sync(&adapter->service_समयr);

	/* disable transmits in the hardware now that पूर्णांकerrupts are off */
	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		u8 reg_idx = adapter->tx_ring[i]->reg_idx;

		IXGBE_WRITE_REG(hw, IXGBE_VFTXDCTL(reg_idx),
				IXGBE_TXDCTL_SWFLSH);
	पूर्ण

	क्रम (i = 0; i < adapter->num_xdp_queues; i++) अणु
		u8 reg_idx = adapter->xdp_ring[i]->reg_idx;

		IXGBE_WRITE_REG(hw, IXGBE_VFTXDCTL(reg_idx),
				IXGBE_TXDCTL_SWFLSH);
	पूर्ण

	अगर (!pci_channel_offline(adapter->pdev))
		ixgbevf_reset(adapter);

	ixgbevf_clean_all_tx_rings(adapter);
	ixgbevf_clean_all_rx_rings(adapter);
पूर्ण

व्योम ixgbevf_reinit_locked(काष्ठा ixgbevf_adapter *adapter)
अणु
	जबतक (test_and_set_bit(__IXGBEVF_RESETTING, &adapter->state))
		msleep(1);

	ixgbevf_करोwn(adapter);
	pci_set_master(adapter->pdev);
	ixgbevf_up(adapter);

	clear_bit(__IXGBEVF_RESETTING, &adapter->state);
पूर्ण

व्योम ixgbevf_reset(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (hw->mac.ops.reset_hw(hw)) अणु
		hw_dbg(hw, "PF still resetting\n");
	पूर्ण अन्यथा अणु
		hw->mac.ops.init_hw(hw);
		ixgbevf_negotiate_api(adapter);
	पूर्ण

	अगर (is_valid_ether_addr(adapter->hw.mac.addr)) अणु
		ether_addr_copy(netdev->dev_addr, adapter->hw.mac.addr);
		ether_addr_copy(netdev->perm_addr, adapter->hw.mac.addr);
	पूर्ण

	adapter->last_reset = jअगरfies;
पूर्ण

अटल पूर्णांक ixgbevf_acquire_msix_vectors(काष्ठा ixgbevf_adapter *adapter,
					पूर्णांक vectors)
अणु
	पूर्णांक vector_threshold;

	/* We'll want at least 2 (vector_threshold):
	 * 1) TxQ[0] + RxQ[0] handler
	 * 2) Other (Link Status Change, etc.)
	 */
	vector_threshold = MIN_MSIX_COUNT;

	/* The more we get, the more we will assign to Tx/Rx Cleanup
	 * क्रम the separate queues...where Rx Cleanup >= Tx Cleanup.
	 * Right now, we simply care about how many we'll get; we'll
	 * set them up later जबतक requesting irq's.
	 */
	vectors = pci_enable_msix_range(adapter->pdev, adapter->msix_entries,
					vector_threshold, vectors);

	अगर (vectors < 0) अणु
		dev_err(&adapter->pdev->dev,
			"Unable to allocate MSI-X interrupts\n");
		kमुक्त(adapter->msix_entries);
		adapter->msix_entries = शून्य;
		वापस vectors;
	पूर्ण

	/* Adjust क्रम only the vectors we'll use, which is minimum
	 * of max_msix_q_vectors + NON_Q_VECTORS, or the number of
	 * vectors we were allocated.
	 */
	adapter->num_msix_vectors = vectors;

	वापस 0;
पूर्ण

/**
 * ixgbevf_set_num_queues - Allocate queues क्रम device, feature dependent
 * @adapter: board निजी काष्ठाure to initialize
 *
 * This is the top level queue allocation routine.  The order here is very
 * important, starting with the "most" number of features turned on at once,
 * and ending with the smallest set of features.  This way large combinations
 * can be allocated अगर they're turned on, and smaller combinations are the
 * fall through conditions.
 *
 **/
अटल व्योम ixgbevf_set_num_queues(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	अचिन्हित पूर्णांक def_q = 0;
	अचिन्हित पूर्णांक num_tcs = 0;
	पूर्णांक err;

	/* Start with base हाल */
	adapter->num_rx_queues = 1;
	adapter->num_tx_queues = 1;
	adapter->num_xdp_queues = 0;

	spin_lock_bh(&adapter->mbx_lock);

	/* fetch queue configuration from the PF */
	err = ixgbevf_get_queues(hw, &num_tcs, &def_q);

	spin_unlock_bh(&adapter->mbx_lock);

	अगर (err)
		वापस;

	/* we need as many queues as traffic classes */
	अगर (num_tcs > 1) अणु
		adapter->num_rx_queues = num_tcs;
	पूर्ण अन्यथा अणु
		u16 rss = min_t(u16, num_online_cpus(), IXGBEVF_MAX_RSS_QUEUES);

		चयन (hw->api_version) अणु
		हाल ixgbe_mbox_api_11:
		हाल ixgbe_mbox_api_12:
		हाल ixgbe_mbox_api_13:
		हाल ixgbe_mbox_api_14:
			अगर (adapter->xdp_prog &&
			    hw->mac.max_tx_queues == rss)
				rss = rss > 3 ? 2 : 1;

			adapter->num_rx_queues = rss;
			adapter->num_tx_queues = rss;
			adapter->num_xdp_queues = adapter->xdp_prog ? rss : 0;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ixgbevf_set_पूर्णांकerrupt_capability - set MSI-X or FAIL अगर not supported
 * @adapter: board निजी काष्ठाure to initialize
 *
 * Attempt to configure the पूर्णांकerrupts using the best available
 * capabilities of the hardware and the kernel.
 **/
अटल पूर्णांक ixgbevf_set_पूर्णांकerrupt_capability(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक vector, v_budget;

	/* It's easy to be greedy क्रम MSI-X vectors, but it really
	 * करोesn't करो us much good अगर we have a lot more vectors
	 * than CPU's.  So let's be conservative and only ask क्रम
	 * (roughly) the same number of vectors as there are CPU's.
	 * The शेष is to use pairs of vectors.
	 */
	v_budget = max(adapter->num_rx_queues, adapter->num_tx_queues);
	v_budget = min_t(पूर्णांक, v_budget, num_online_cpus());
	v_budget += NON_Q_VECTORS;

	adapter->msix_entries = kसुस्मृति(v_budget,
					माप(काष्ठा msix_entry), GFP_KERNEL);
	अगर (!adapter->msix_entries)
		वापस -ENOMEM;

	क्रम (vector = 0; vector < v_budget; vector++)
		adapter->msix_entries[vector].entry = vector;

	/* A failure in MSI-X entry allocation isn't fatal, but the VF driver
	 * करोes not support any other modes, so we will simply fail here. Note
	 * that we clean up the msix_entries poपूर्णांकer अन्यथा-where.
	 */
	वापस ixgbevf_acquire_msix_vectors(adapter, v_budget);
पूर्ण

अटल व्योम ixgbevf_add_ring(काष्ठा ixgbevf_ring *ring,
			     काष्ठा ixgbevf_ring_container *head)
अणु
	ring->next = head->ring;
	head->ring = ring;
	head->count++;
पूर्ण

/**
 * ixgbevf_alloc_q_vector - Allocate memory क्रम a single पूर्णांकerrupt vector
 * @adapter: board निजी काष्ठाure to initialize
 * @v_idx: index of vector in adapter काष्ठा
 * @txr_count: number of Tx rings क्रम q vector
 * @txr_idx: index of first Tx ring to assign
 * @xdp_count: total number of XDP rings to allocate
 * @xdp_idx: index of first XDP ring to allocate
 * @rxr_count: number of Rx rings क्रम q vector
 * @rxr_idx: index of first Rx ring to assign
 *
 * We allocate one q_vector.  If allocation fails we वापस -ENOMEM.
 **/
अटल पूर्णांक ixgbevf_alloc_q_vector(काष्ठा ixgbevf_adapter *adapter, पूर्णांक v_idx,
				  पूर्णांक txr_count, पूर्णांक txr_idx,
				  पूर्णांक xdp_count, पूर्णांक xdp_idx,
				  पूर्णांक rxr_count, पूर्णांक rxr_idx)
अणु
	काष्ठा ixgbevf_q_vector *q_vector;
	पूर्णांक reg_idx = txr_idx + xdp_idx;
	काष्ठा ixgbevf_ring *ring;
	पूर्णांक ring_count, size;

	ring_count = txr_count + xdp_count + rxr_count;
	size = माप(*q_vector) + (माप(*ring) * ring_count);

	/* allocate q_vector and rings */
	q_vector = kzalloc(size, GFP_KERNEL);
	अगर (!q_vector)
		वापस -ENOMEM;

	/* initialize NAPI */
	netअगर_napi_add(adapter->netdev, &q_vector->napi, ixgbevf_poll, 64);

	/* tie q_vector and adapter together */
	adapter->q_vector[v_idx] = q_vector;
	q_vector->adapter = adapter;
	q_vector->v_idx = v_idx;

	/* initialize poपूर्णांकer to rings */
	ring = q_vector->ring;

	जबतक (txr_count) अणु
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Tx values */
		ixgbevf_add_ring(ring, &q_vector->tx);

		/* apply Tx specअगरic ring traits */
		ring->count = adapter->tx_ring_count;
		ring->queue_index = txr_idx;
		ring->reg_idx = reg_idx;

		/* assign ring to adapter */
		 adapter->tx_ring[txr_idx] = ring;

		/* update count and index */
		txr_count--;
		txr_idx++;
		reg_idx++;

		/* push poपूर्णांकer to next ring */
		ring++;
	पूर्ण

	जबतक (xdp_count) अणु
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Tx values */
		ixgbevf_add_ring(ring, &q_vector->tx);

		/* apply Tx specअगरic ring traits */
		ring->count = adapter->tx_ring_count;
		ring->queue_index = xdp_idx;
		ring->reg_idx = reg_idx;
		set_ring_xdp(ring);

		/* assign ring to adapter */
		adapter->xdp_ring[xdp_idx] = ring;

		/* update count and index */
		xdp_count--;
		xdp_idx++;
		reg_idx++;

		/* push poपूर्णांकer to next ring */
		ring++;
	पूर्ण

	जबतक (rxr_count) अणु
		/* assign generic ring traits */
		ring->dev = &adapter->pdev->dev;
		ring->netdev = adapter->netdev;

		/* configure backlink on ring */
		ring->q_vector = q_vector;

		/* update q_vector Rx values */
		ixgbevf_add_ring(ring, &q_vector->rx);

		/* apply Rx specअगरic ring traits */
		ring->count = adapter->rx_ring_count;
		ring->queue_index = rxr_idx;
		ring->reg_idx = rxr_idx;

		/* assign ring to adapter */
		adapter->rx_ring[rxr_idx] = ring;

		/* update count and index */
		rxr_count--;
		rxr_idx++;

		/* push poपूर्णांकer to next ring */
		ring++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbevf_मुक्त_q_vector - Free memory allocated क्रम specअगरic पूर्णांकerrupt vector
 * @adapter: board निजी काष्ठाure to initialize
 * @v_idx: index of vector in adapter काष्ठा
 *
 * This function मुक्तs the memory allocated to the q_vector.  In addition अगर
 * NAPI is enabled it will delete any references to the NAPI काष्ठा prior
 * to मुक्तing the q_vector.
 **/
अटल व्योम ixgbevf_मुक्त_q_vector(काष्ठा ixgbevf_adapter *adapter, पूर्णांक v_idx)
अणु
	काष्ठा ixgbevf_q_vector *q_vector = adapter->q_vector[v_idx];
	काष्ठा ixgbevf_ring *ring;

	ixgbevf_क्रम_each_ring(ring, q_vector->tx) अणु
		अगर (ring_is_xdp(ring))
			adapter->xdp_ring[ring->queue_index] = शून्य;
		अन्यथा
			adapter->tx_ring[ring->queue_index] = शून्य;
	पूर्ण

	ixgbevf_क्रम_each_ring(ring, q_vector->rx)
		adapter->rx_ring[ring->queue_index] = शून्य;

	adapter->q_vector[v_idx] = शून्य;
	netअगर_napi_del(&q_vector->napi);

	/* ixgbevf_get_stats() might access the rings on this vector,
	 * we must रुको a grace period beक्रमe मुक्तing it.
	 */
	kमुक्त_rcu(q_vector, rcu);
पूर्ण

/**
 * ixgbevf_alloc_q_vectors - Allocate memory क्रम पूर्णांकerrupt vectors
 * @adapter: board निजी काष्ठाure to initialize
 *
 * We allocate one q_vector per queue पूर्णांकerrupt.  If allocation fails we
 * वापस -ENOMEM.
 **/
अटल पूर्णांक ixgbevf_alloc_q_vectors(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक q_vectors = adapter->num_msix_vectors - NON_Q_VECTORS;
	पूर्णांक rxr_reमुख्यing = adapter->num_rx_queues;
	पूर्णांक txr_reमुख्यing = adapter->num_tx_queues;
	पूर्णांक xdp_reमुख्यing = adapter->num_xdp_queues;
	पूर्णांक rxr_idx = 0, txr_idx = 0, xdp_idx = 0, v_idx = 0;
	पूर्णांक err;

	अगर (q_vectors >= (rxr_reमुख्यing + txr_reमुख्यing + xdp_reमुख्यing)) अणु
		क्रम (; rxr_reमुख्यing; v_idx++, q_vectors--) अणु
			पूर्णांक rqpv = DIV_ROUND_UP(rxr_reमुख्यing, q_vectors);

			err = ixgbevf_alloc_q_vector(adapter, v_idx,
						     0, 0, 0, 0, rqpv, rxr_idx);
			अगर (err)
				जाओ err_out;

			/* update counts and index */
			rxr_reमुख्यing -= rqpv;
			rxr_idx += rqpv;
		पूर्ण
	पूर्ण

	क्रम (; q_vectors; v_idx++, q_vectors--) अणु
		पूर्णांक rqpv = DIV_ROUND_UP(rxr_reमुख्यing, q_vectors);
		पूर्णांक tqpv = DIV_ROUND_UP(txr_reमुख्यing, q_vectors);
		पूर्णांक xqpv = DIV_ROUND_UP(xdp_reमुख्यing, q_vectors);

		err = ixgbevf_alloc_q_vector(adapter, v_idx,
					     tqpv, txr_idx,
					     xqpv, xdp_idx,
					     rqpv, rxr_idx);

		अगर (err)
			जाओ err_out;

		/* update counts and index */
		rxr_reमुख्यing -= rqpv;
		rxr_idx += rqpv;
		txr_reमुख्यing -= tqpv;
		txr_idx += tqpv;
		xdp_reमुख्यing -= xqpv;
		xdp_idx += xqpv;
	पूर्ण

	वापस 0;

err_out:
	जबतक (v_idx) अणु
		v_idx--;
		ixgbevf_मुक्त_q_vector(adapter, v_idx);
	पूर्ण

	वापस -ENOMEM;
पूर्ण

/**
 * ixgbevf_मुक्त_q_vectors - Free memory allocated क्रम पूर्णांकerrupt vectors
 * @adapter: board निजी काष्ठाure to initialize
 *
 * This function मुक्तs the memory allocated to the q_vectors.  In addition अगर
 * NAPI is enabled it will delete any references to the NAPI काष्ठा prior
 * to मुक्तing the q_vector.
 **/
अटल व्योम ixgbevf_मुक्त_q_vectors(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक q_vectors = adapter->num_msix_vectors - NON_Q_VECTORS;

	जबतक (q_vectors) अणु
		q_vectors--;
		ixgbevf_मुक्त_q_vector(adapter, q_vectors);
	पूर्ण
पूर्ण

/**
 * ixgbevf_reset_पूर्णांकerrupt_capability - Reset MSIX setup
 * @adapter: board निजी काष्ठाure
 *
 **/
अटल व्योम ixgbevf_reset_पूर्णांकerrupt_capability(काष्ठा ixgbevf_adapter *adapter)
अणु
	अगर (!adapter->msix_entries)
		वापस;

	pci_disable_msix(adapter->pdev);
	kमुक्त(adapter->msix_entries);
	adapter->msix_entries = शून्य;
पूर्ण

/**
 * ixgbevf_init_पूर्णांकerrupt_scheme - Determine अगर MSIX is supported and init
 * @adapter: board निजी काष्ठाure to initialize
 *
 **/
अटल पूर्णांक ixgbevf_init_पूर्णांकerrupt_scheme(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक err;

	/* Number of supported queues */
	ixgbevf_set_num_queues(adapter);

	err = ixgbevf_set_पूर्णांकerrupt_capability(adapter);
	अगर (err) अणु
		hw_dbg(&adapter->hw,
		       "Unable to setup interrupt capabilities\n");
		जाओ err_set_पूर्णांकerrupt;
	पूर्ण

	err = ixgbevf_alloc_q_vectors(adapter);
	अगर (err) अणु
		hw_dbg(&adapter->hw, "Unable to allocate memory for queue vectors\n");
		जाओ err_alloc_q_vectors;
	पूर्ण

	hw_dbg(&adapter->hw, "Multiqueue %s: Rx Queue count = %u, Tx Queue count = %u XDP Queue count %u\n",
	       (adapter->num_rx_queues > 1) ? "Enabled" : "Disabled",
	       adapter->num_rx_queues, adapter->num_tx_queues,
	       adapter->num_xdp_queues);

	set_bit(__IXGBEVF_DOWN, &adapter->state);

	वापस 0;
err_alloc_q_vectors:
	ixgbevf_reset_पूर्णांकerrupt_capability(adapter);
err_set_पूर्णांकerrupt:
	वापस err;
पूर्ण

/**
 * ixgbevf_clear_पूर्णांकerrupt_scheme - Clear the current पूर्णांकerrupt scheme settings
 * @adapter: board निजी काष्ठाure to clear पूर्णांकerrupt scheme on
 *
 * We go through and clear पूर्णांकerrupt specअगरic resources and reset the काष्ठाure
 * to pre-load conditions
 **/
अटल व्योम ixgbevf_clear_पूर्णांकerrupt_scheme(काष्ठा ixgbevf_adapter *adapter)
अणु
	adapter->num_tx_queues = 0;
	adapter->num_xdp_queues = 0;
	adapter->num_rx_queues = 0;

	ixgbevf_मुक्त_q_vectors(adapter);
	ixgbevf_reset_पूर्णांकerrupt_capability(adapter);
पूर्ण

/**
 * ixgbevf_sw_init - Initialize general software काष्ठाures
 * @adapter: board निजी काष्ठाure to initialize
 *
 * ixgbevf_sw_init initializes the Adapter निजी data काष्ठाure.
 * Fields are initialized based on PCI device inक्रमmation and
 * OS network device settings (MTU size).
 **/
अटल पूर्णांक ixgbevf_sw_init(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err;

	/* PCI config space info */
	hw->venकरोr_id = pdev->venकरोr;
	hw->device_id = pdev->device;
	hw->revision_id = pdev->revision;
	hw->subप्रणाली_venकरोr_id = pdev->subप्रणाली_venकरोr;
	hw->subप्रणाली_device_id = pdev->subप्रणाली_device;

	hw->mbx.ops.init_params(hw);

	अगर (hw->mac.type >= ixgbe_mac_X550_vf) अणु
		err = ixgbevf_init_rss_key(adapter);
		अगर (err)
			जाओ out;
	पूर्ण

	/* assume legacy हाल in which PF would only give VF 2 queues */
	hw->mac.max_tx_queues = 2;
	hw->mac.max_rx_queues = 2;

	/* lock to protect mailbox accesses */
	spin_lock_init(&adapter->mbx_lock);

	err = hw->mac.ops.reset_hw(hw);
	अगर (err) अणु
		dev_info(&pdev->dev,
			 "PF still in reset state.  Is the PF interface up?\n");
	पूर्ण अन्यथा अणु
		err = hw->mac.ops.init_hw(hw);
		अगर (err) अणु
			pr_err("init_shared_code failed: %d\n", err);
			जाओ out;
		पूर्ण
		ixgbevf_negotiate_api(adapter);
		err = hw->mac.ops.get_mac_addr(hw, hw->mac.addr);
		अगर (err)
			dev_info(&pdev->dev, "Error reading MAC address\n");
		अन्यथा अगर (is_zero_ether_addr(adapter->hw.mac.addr))
			dev_info(&pdev->dev,
				 "MAC address not assigned by administrator.\n");
		ether_addr_copy(netdev->dev_addr, hw->mac.addr);
	पूर्ण

	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		dev_info(&pdev->dev, "Assigning random MAC address\n");
		eth_hw_addr_अक्रमom(netdev);
		ether_addr_copy(hw->mac.addr, netdev->dev_addr);
		ether_addr_copy(hw->mac.perm_addr, netdev->dev_addr);
	पूर्ण

	/* Enable dynamic पूर्णांकerrupt throttling rates */
	adapter->rx_itr_setting = 1;
	adapter->tx_itr_setting = 1;

	/* set शेष ring sizes */
	adapter->tx_ring_count = IXGBEVF_DEFAULT_TXD;
	adapter->rx_ring_count = IXGBEVF_DEFAULT_RXD;

	set_bit(__IXGBEVF_DOWN, &adapter->state);
	वापस 0;

out:
	वापस err;
पूर्ण

#घोषणा UPDATE_VF_COUNTER_32bit(reg, last_counter, counter)	\
	अणु							\
		u32 current_counter = IXGBE_READ_REG(hw, reg);	\
		अगर (current_counter < last_counter)		\
			counter += 0x100000000LL;		\
		last_counter = current_counter;			\
		counter &= 0xFFFFFFFF00000000LL;		\
		counter |= current_counter;			\
	पूर्ण

#घोषणा UPDATE_VF_COUNTER_36bit(reg_lsb, reg_msb, last_counter, counter) \
	अणु								 \
		u64 current_counter_lsb = IXGBE_READ_REG(hw, reg_lsb);	 \
		u64 current_counter_msb = IXGBE_READ_REG(hw, reg_msb);	 \
		u64 current_counter = (current_counter_msb << 32) |	 \
			current_counter_lsb;				 \
		अगर (current_counter < last_counter)			 \
			counter += 0x1000000000LL;			 \
		last_counter = current_counter;				 \
		counter &= 0xFFFFFFF000000000LL;			 \
		counter |= current_counter;				 \
	पूर्ण
/**
 * ixgbevf_update_stats - Update the board statistics counters.
 * @adapter: board निजी काष्ठाure
 **/
व्योम ixgbevf_update_stats(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u64 alloc_rx_page_failed = 0, alloc_rx_buff_failed = 0;
	u64 alloc_rx_page = 0, hw_csum_rx_error = 0;
	पूर्णांक i;

	अगर (test_bit(__IXGBEVF_DOWN, &adapter->state) ||
	    test_bit(__IXGBEVF_RESETTING, &adapter->state))
		वापस;

	UPDATE_VF_COUNTER_32bit(IXGBE_VFGPRC, adapter->stats.last_vfgprc,
				adapter->stats.vfgprc);
	UPDATE_VF_COUNTER_32bit(IXGBE_VFGPTC, adapter->stats.last_vfgptc,
				adapter->stats.vfgptc);
	UPDATE_VF_COUNTER_36bit(IXGBE_VFGORC_LSB, IXGBE_VFGORC_MSB,
				adapter->stats.last_vfgorc,
				adapter->stats.vfgorc);
	UPDATE_VF_COUNTER_36bit(IXGBE_VFGOTC_LSB, IXGBE_VFGOTC_MSB,
				adapter->stats.last_vfgotc,
				adapter->stats.vfgotc);
	UPDATE_VF_COUNTER_32bit(IXGBE_VFMPRC, adapter->stats.last_vfmprc,
				adapter->stats.vfmprc);

	क्रम (i = 0;  i  < adapter->num_rx_queues;  i++) अणु
		काष्ठा ixgbevf_ring *rx_ring = adapter->rx_ring[i];

		hw_csum_rx_error += rx_ring->rx_stats.csum_err;
		alloc_rx_page_failed += rx_ring->rx_stats.alloc_rx_page_failed;
		alloc_rx_buff_failed += rx_ring->rx_stats.alloc_rx_buff_failed;
		alloc_rx_page += rx_ring->rx_stats.alloc_rx_page;
	पूर्ण

	adapter->hw_csum_rx_error = hw_csum_rx_error;
	adapter->alloc_rx_page_failed = alloc_rx_page_failed;
	adapter->alloc_rx_buff_failed = alloc_rx_buff_failed;
	adapter->alloc_rx_page = alloc_rx_page;
पूर्ण

/**
 * ixgbevf_service_समयr - Timer Call-back
 * @t: poपूर्णांकer to समयr_list काष्ठा
 **/
अटल व्योम ixgbevf_service_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ixgbevf_adapter *adapter = from_समयr(adapter, t,
						     service_समयr);

	/* Reset the समयr */
	mod_समयr(&adapter->service_समयr, (HZ * 2) + jअगरfies);

	ixgbevf_service_event_schedule(adapter);
पूर्ण

अटल व्योम ixgbevf_reset_subtask(काष्ठा ixgbevf_adapter *adapter)
अणु
	अगर (!test_and_clear_bit(__IXGBEVF_RESET_REQUESTED, &adapter->state))
		वापस;

	rtnl_lock();
	/* If we're alपढ़ोy करोwn or resetting, just bail */
	अगर (test_bit(__IXGBEVF_DOWN, &adapter->state) ||
	    test_bit(__IXGBEVF_REMOVING, &adapter->state) ||
	    test_bit(__IXGBEVF_RESETTING, &adapter->state)) अणु
		rtnl_unlock();
		वापस;
	पूर्ण

	adapter->tx_समयout_count++;

	ixgbevf_reinit_locked(adapter);
	rtnl_unlock();
पूर्ण

/**
 * ixgbevf_check_hang_subtask - check क्रम hung queues and dropped पूर्णांकerrupts
 * @adapter: poपूर्णांकer to the device adapter काष्ठाure
 *
 * This function serves two purposes.  First it strobes the पूर्णांकerrupt lines
 * in order to make certain पूर्णांकerrupts are occurring.  Secondly it sets the
 * bits needed to check क्रम TX hangs.  As a result we should immediately
 * determine अगर a hang has occurred.
 **/
अटल व्योम ixgbevf_check_hang_subtask(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 eics = 0;
	पूर्णांक i;

	/* If we're करोwn or resetting, just bail */
	अगर (test_bit(__IXGBEVF_DOWN, &adapter->state) ||
	    test_bit(__IXGBEVF_RESETTING, &adapter->state))
		वापस;

	/* Force detection of hung controller */
	अगर (netअगर_carrier_ok(adapter->netdev)) अणु
		क्रम (i = 0; i < adapter->num_tx_queues; i++)
			set_check_क्रम_tx_hang(adapter->tx_ring[i]);
		क्रम (i = 0; i < adapter->num_xdp_queues; i++)
			set_check_क्रम_tx_hang(adapter->xdp_ring[i]);
	पूर्ण

	/* get one bit क्रम every active Tx/Rx पूर्णांकerrupt vector */
	क्रम (i = 0; i < adapter->num_msix_vectors - NON_Q_VECTORS; i++) अणु
		काष्ठा ixgbevf_q_vector *qv = adapter->q_vector[i];

		अगर (qv->rx.ring || qv->tx.ring)
			eics |= BIT(i);
	पूर्ण

	/* Cause software पूर्णांकerrupt to ensure rings are cleaned */
	IXGBE_WRITE_REG(hw, IXGBE_VTEICS, eics);
पूर्ण

/**
 * ixgbevf_watchकरोg_update_link - update the link status
 * @adapter: poपूर्णांकer to the device adapter काष्ठाure
 **/
अटल व्योम ixgbevf_watchकरोg_update_link(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 link_speed = adapter->link_speed;
	bool link_up = adapter->link_up;
	s32 err;

	spin_lock_bh(&adapter->mbx_lock);

	err = hw->mac.ops.check_link(hw, &link_speed, &link_up, false);

	spin_unlock_bh(&adapter->mbx_lock);

	/* अगर check क्रम link वापसs error we will need to reset */
	अगर (err && समय_after(jअगरfies, adapter->last_reset + (10 * HZ))) अणु
		set_bit(__IXGBEVF_RESET_REQUESTED, &adapter->state);
		link_up = false;
	पूर्ण

	adapter->link_up = link_up;
	adapter->link_speed = link_speed;
पूर्ण

/**
 * ixgbevf_watchकरोg_link_is_up - update netअगर_carrier status and
 *				 prपूर्णांक link up message
 * @adapter: poपूर्णांकer to the device adapter काष्ठाure
 **/
अटल व्योम ixgbevf_watchकरोg_link_is_up(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	/* only जारी अगर link was previously करोwn */
	अगर (netअगर_carrier_ok(netdev))
		वापस;

	dev_info(&adapter->pdev->dev, "NIC Link is Up %s\n",
		 (adapter->link_speed == IXGBE_LINK_SPEED_10GB_FULL) ?
		 "10 Gbps" :
		 (adapter->link_speed == IXGBE_LINK_SPEED_1GB_FULL) ?
		 "1 Gbps" :
		 (adapter->link_speed == IXGBE_LINK_SPEED_100_FULL) ?
		 "100 Mbps" :
		 "unknown speed");

	netअगर_carrier_on(netdev);
पूर्ण

/**
 * ixgbevf_watchकरोg_link_is_करोwn - update netअगर_carrier status and
 *				   prपूर्णांक link करोwn message
 * @adapter: poपूर्णांकer to the adapter काष्ठाure
 **/
अटल व्योम ixgbevf_watchकरोg_link_is_करोwn(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	adapter->link_speed = 0;

	/* only जारी अगर link was up previously */
	अगर (!netअगर_carrier_ok(netdev))
		वापस;

	dev_info(&adapter->pdev->dev, "NIC Link is Down\n");

	netअगर_carrier_off(netdev);
पूर्ण

/**
 * ixgbevf_watchकरोg_subtask - worker thपढ़ो to bring link up
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम ixgbevf_watchकरोg_subtask(काष्ठा ixgbevf_adapter *adapter)
अणु
	/* अगर पूर्णांकerface is करोwn करो nothing */
	अगर (test_bit(__IXGBEVF_DOWN, &adapter->state) ||
	    test_bit(__IXGBEVF_RESETTING, &adapter->state))
		वापस;

	ixgbevf_watchकरोg_update_link(adapter);

	अगर (adapter->link_up)
		ixgbevf_watchकरोg_link_is_up(adapter);
	अन्यथा
		ixgbevf_watchकरोg_link_is_करोwn(adapter);

	ixgbevf_update_stats(adapter);
पूर्ण

/**
 * ixgbevf_service_task - manages and runs subtasks
 * @work: poपूर्णांकer to work_काष्ठा containing our data
 **/
अटल व्योम ixgbevf_service_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ixgbevf_adapter *adapter = container_of(work,
						       काष्ठा ixgbevf_adapter,
						       service_task);
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	अगर (IXGBE_REMOVED(hw->hw_addr)) अणु
		अगर (!test_bit(__IXGBEVF_DOWN, &adapter->state)) अणु
			rtnl_lock();
			ixgbevf_करोwn(adapter);
			rtnl_unlock();
		पूर्ण
		वापस;
	पूर्ण

	ixgbevf_queue_reset_subtask(adapter);
	ixgbevf_reset_subtask(adapter);
	ixgbevf_watchकरोg_subtask(adapter);
	ixgbevf_check_hang_subtask(adapter);

	ixgbevf_service_event_complete(adapter);
पूर्ण

/**
 * ixgbevf_मुक्त_tx_resources - Free Tx Resources per Queue
 * @tx_ring: Tx descriptor ring क्रम a specअगरic queue
 *
 * Free all transmit software resources
 **/
व्योम ixgbevf_मुक्त_tx_resources(काष्ठा ixgbevf_ring *tx_ring)
अणु
	ixgbevf_clean_tx_ring(tx_ring);

	vमुक्त(tx_ring->tx_buffer_info);
	tx_ring->tx_buffer_info = शून्य;

	/* अगर not set, then करोn't मुक्त */
	अगर (!tx_ring->desc)
		वापस;

	dma_मुक्त_coherent(tx_ring->dev, tx_ring->size, tx_ring->desc,
			  tx_ring->dma);

	tx_ring->desc = शून्य;
पूर्ण

/**
 * ixgbevf_मुक्त_all_tx_resources - Free Tx Resources क्रम All Queues
 * @adapter: board निजी काष्ठाure
 *
 * Free all transmit software resources
 **/
अटल व्योम ixgbevf_मुक्त_all_tx_resources(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		अगर (adapter->tx_ring[i]->desc)
			ixgbevf_मुक्त_tx_resources(adapter->tx_ring[i]);
	क्रम (i = 0; i < adapter->num_xdp_queues; i++)
		अगर (adapter->xdp_ring[i]->desc)
			ixgbevf_मुक्त_tx_resources(adapter->xdp_ring[i]);
पूर्ण

/**
 * ixgbevf_setup_tx_resources - allocate Tx resources (Descriptors)
 * @tx_ring: Tx descriptor ring (क्रम a specअगरic queue) to setup
 *
 * Return 0 on success, negative on failure
 **/
पूर्णांक ixgbevf_setup_tx_resources(काष्ठा ixgbevf_ring *tx_ring)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(tx_ring->netdev);
	पूर्णांक size;

	size = माप(काष्ठा ixgbevf_tx_buffer) * tx_ring->count;
	tx_ring->tx_buffer_info = vदो_स्मृति(size);
	अगर (!tx_ring->tx_buffer_info)
		जाओ err;

	u64_stats_init(&tx_ring->syncp);

	/* round up to nearest 4K */
	tx_ring->size = tx_ring->count * माप(जोड़ ixgbe_adv_tx_desc);
	tx_ring->size = ALIGN(tx_ring->size, 4096);

	tx_ring->desc = dma_alloc_coherent(tx_ring->dev, tx_ring->size,
					   &tx_ring->dma, GFP_KERNEL);
	अगर (!tx_ring->desc)
		जाओ err;

	वापस 0;

err:
	vमुक्त(tx_ring->tx_buffer_info);
	tx_ring->tx_buffer_info = शून्य;
	hw_dbg(&adapter->hw, "Unable to allocate memory for the transmit descriptor ring\n");
	वापस -ENOMEM;
पूर्ण

/**
 * ixgbevf_setup_all_tx_resources - allocate all queues Tx resources
 * @adapter: board निजी काष्ठाure
 *
 * If this function वापसs with an error, then it's possible one or
 * more of the rings is populated (जबतक the rest are not).  It is the
 * callers duty to clean those orphaned rings.
 *
 * Return 0 on success, negative on failure
 **/
अटल पूर्णांक ixgbevf_setup_all_tx_resources(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक i, j = 0, err = 0;

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		err = ixgbevf_setup_tx_resources(adapter->tx_ring[i]);
		अगर (!err)
			जारी;
		hw_dbg(&adapter->hw, "Allocation for Tx Queue %u failed\n", i);
		जाओ err_setup_tx;
	पूर्ण

	क्रम (j = 0; j < adapter->num_xdp_queues; j++) अणु
		err = ixgbevf_setup_tx_resources(adapter->xdp_ring[j]);
		अगर (!err)
			जारी;
		hw_dbg(&adapter->hw, "Allocation for XDP Queue %u failed\n", j);
		जाओ err_setup_tx;
	पूर्ण

	वापस 0;
err_setup_tx:
	/* शुरुआत the index मुक्तing the rings as we go */
	जबतक (j--)
		ixgbevf_मुक्त_tx_resources(adapter->xdp_ring[j]);
	जबतक (i--)
		ixgbevf_मुक्त_tx_resources(adapter->tx_ring[i]);

	वापस err;
पूर्ण

/**
 * ixgbevf_setup_rx_resources - allocate Rx resources (Descriptors)
 * @adapter: board निजी काष्ठाure
 * @rx_ring: Rx descriptor ring (क्रम a specअगरic queue) to setup
 *
 * Returns 0 on success, negative on failure
 **/
पूर्णांक ixgbevf_setup_rx_resources(काष्ठा ixgbevf_adapter *adapter,
			       काष्ठा ixgbevf_ring *rx_ring)
अणु
	पूर्णांक size;

	size = माप(काष्ठा ixgbevf_rx_buffer) * rx_ring->count;
	rx_ring->rx_buffer_info = vदो_स्मृति(size);
	अगर (!rx_ring->rx_buffer_info)
		जाओ err;

	u64_stats_init(&rx_ring->syncp);

	/* Round up to nearest 4K */
	rx_ring->size = rx_ring->count * माप(जोड़ ixgbe_adv_rx_desc);
	rx_ring->size = ALIGN(rx_ring->size, 4096);

	rx_ring->desc = dma_alloc_coherent(rx_ring->dev, rx_ring->size,
					   &rx_ring->dma, GFP_KERNEL);

	अगर (!rx_ring->desc)
		जाओ err;

	/* XDP RX-queue info */
	अगर (xdp_rxq_info_reg(&rx_ring->xdp_rxq, adapter->netdev,
			     rx_ring->queue_index, 0) < 0)
		जाओ err;

	rx_ring->xdp_prog = adapter->xdp_prog;

	वापस 0;
err:
	vमुक्त(rx_ring->rx_buffer_info);
	rx_ring->rx_buffer_info = शून्य;
	dev_err(rx_ring->dev, "Unable to allocate memory for the Rx descriptor ring\n");
	वापस -ENOMEM;
पूर्ण

/**
 * ixgbevf_setup_all_rx_resources - allocate all queues Rx resources
 * @adapter: board निजी काष्ठाure
 *
 * If this function वापसs with an error, then it's possible one or
 * more of the rings is populated (जबतक the rest are not).  It is the
 * callers duty to clean those orphaned rings.
 *
 * Return 0 on success, negative on failure
 **/
अटल पूर्णांक ixgbevf_setup_all_rx_resources(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		err = ixgbevf_setup_rx_resources(adapter, adapter->rx_ring[i]);
		अगर (!err)
			जारी;
		hw_dbg(&adapter->hw, "Allocation for Rx Queue %u failed\n", i);
		जाओ err_setup_rx;
	पूर्ण

	वापस 0;
err_setup_rx:
	/* शुरुआत the index मुक्तing the rings as we go */
	जबतक (i--)
		ixgbevf_मुक्त_rx_resources(adapter->rx_ring[i]);
	वापस err;
पूर्ण

/**
 * ixgbevf_मुक्त_rx_resources - Free Rx Resources
 * @rx_ring: ring to clean the resources from
 *
 * Free all receive software resources
 **/
व्योम ixgbevf_मुक्त_rx_resources(काष्ठा ixgbevf_ring *rx_ring)
अणु
	ixgbevf_clean_rx_ring(rx_ring);

	rx_ring->xdp_prog = शून्य;
	xdp_rxq_info_unreg(&rx_ring->xdp_rxq);
	vमुक्त(rx_ring->rx_buffer_info);
	rx_ring->rx_buffer_info = शून्य;

	dma_मुक्त_coherent(rx_ring->dev, rx_ring->size, rx_ring->desc,
			  rx_ring->dma);

	rx_ring->desc = शून्य;
पूर्ण

/**
 * ixgbevf_मुक्त_all_rx_resources - Free Rx Resources क्रम All Queues
 * @adapter: board निजी काष्ठाure
 *
 * Free all receive software resources
 **/
अटल व्योम ixgbevf_मुक्त_all_rx_resources(काष्ठा ixgbevf_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		अगर (adapter->rx_ring[i]->desc)
			ixgbevf_मुक्त_rx_resources(adapter->rx_ring[i]);
पूर्ण

/**
 * ixgbevf_खोलो - Called when a network पूर्णांकerface is made active
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0 on success, negative value on failure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the watchकरोg समयr is started,
 * and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 **/
पूर्णांक ixgbevf_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक err;

	/* A previous failure to खोलो the device because of a lack of
	 * available MSIX vector resources may have reset the number
	 * of msix vectors variable to zero.  The only way to recover
	 * is to unload/reload the driver and hope that the प्रणाली has
	 * been able to recover some MSIX vector resources.
	 */
	अगर (!adapter->num_msix_vectors)
		वापस -ENOMEM;

	अगर (hw->adapter_stopped) अणु
		ixgbevf_reset(adapter);
		/* अगर adapter is still stopped then PF isn't up and
		 * the VF can't start.
		 */
		अगर (hw->adapter_stopped) अणु
			err = IXGBE_ERR_MBX;
			pr_err("Unable to start - perhaps the PF Driver isn't up yet\n");
			जाओ err_setup_reset;
		पूर्ण
	पूर्ण

	/* disallow खोलो during test */
	अगर (test_bit(__IXGBEVF_TESTING, &adapter->state))
		वापस -EBUSY;

	netअगर_carrier_off(netdev);

	/* allocate transmit descriptors */
	err = ixgbevf_setup_all_tx_resources(adapter);
	अगर (err)
		जाओ err_setup_tx;

	/* allocate receive descriptors */
	err = ixgbevf_setup_all_rx_resources(adapter);
	अगर (err)
		जाओ err_setup_rx;

	ixgbevf_configure(adapter);

	err = ixgbevf_request_irq(adapter);
	अगर (err)
		जाओ err_req_irq;

	/* Notअगरy the stack of the actual queue counts. */
	err = netअगर_set_real_num_tx_queues(netdev, adapter->num_tx_queues);
	अगर (err)
		जाओ err_set_queues;

	err = netअगर_set_real_num_rx_queues(netdev, adapter->num_rx_queues);
	अगर (err)
		जाओ err_set_queues;

	ixgbevf_up_complete(adapter);

	वापस 0;

err_set_queues:
	ixgbevf_मुक्त_irq(adapter);
err_req_irq:
	ixgbevf_मुक्त_all_rx_resources(adapter);
err_setup_rx:
	ixgbevf_मुक्त_all_tx_resources(adapter);
err_setup_tx:
	ixgbevf_reset(adapter);
err_setup_reset:

	वापस err;
पूर्ण

/**
 * ixgbevf_बंद_suspend - actions necessary to both suspend and बंद flows
 * @adapter: the निजी adapter काष्ठा
 *
 * This function should contain the necessary work common to both suspending
 * and closing of the device.
 */
अटल व्योम ixgbevf_बंद_suspend(काष्ठा ixgbevf_adapter *adapter)
अणु
	ixgbevf_करोwn(adapter);
	ixgbevf_मुक्त_irq(adapter);
	ixgbevf_मुक्त_all_tx_resources(adapter);
	ixgbevf_मुक्त_all_rx_resources(adapter);
पूर्ण

/**
 * ixgbevf_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 **/
पूर्णांक ixgbevf_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);

	अगर (netअगर_device_present(netdev))
		ixgbevf_बंद_suspend(adapter);

	वापस 0;
पूर्ण

अटल व्योम ixgbevf_queue_reset_subtask(काष्ठा ixgbevf_adapter *adapter)
अणु
	काष्ठा net_device *dev = adapter->netdev;

	अगर (!test_and_clear_bit(__IXGBEVF_QUEUE_RESET_REQUESTED,
				&adapter->state))
		वापस;

	/* अगर पूर्णांकerface is करोwn करो nothing */
	अगर (test_bit(__IXGBEVF_DOWN, &adapter->state) ||
	    test_bit(__IXGBEVF_RESETTING, &adapter->state))
		वापस;

	/* Hardware has to reinitialize queues and पूर्णांकerrupts to
	 * match packet buffer alignment. Unक्रमtunately, the
	 * hardware is not flexible enough to करो this dynamically.
	 */
	rtnl_lock();

	अगर (netअगर_running(dev))
		ixgbevf_बंद(dev);

	ixgbevf_clear_पूर्णांकerrupt_scheme(adapter);
	ixgbevf_init_पूर्णांकerrupt_scheme(adapter);

	अगर (netअगर_running(dev))
		ixgbevf_खोलो(dev);

	rtnl_unlock();
पूर्ण

अटल व्योम ixgbevf_tx_ctxtdesc(काष्ठा ixgbevf_ring *tx_ring,
				u32 vlan_macip_lens, u32 fceof_saidx,
				u32 type_tucmd, u32 mss_l4len_idx)
अणु
	काष्ठा ixgbe_adv_tx_context_desc *context_desc;
	u16 i = tx_ring->next_to_use;

	context_desc = IXGBEVF_TX_CTXTDESC(tx_ring, i);

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	/* set bits to identअगरy this as an advanced context descriptor */
	type_tucmd |= IXGBE_TXD_CMD_DEXT | IXGBE_ADVTXD_DTYP_CTXT;

	context_desc->vlan_macip_lens	= cpu_to_le32(vlan_macip_lens);
	context_desc->fceof_saidx	= cpu_to_le32(fceof_saidx);
	context_desc->type_tucmd_mlhl	= cpu_to_le32(type_tucmd);
	context_desc->mss_l4len_idx	= cpu_to_le32(mss_l4len_idx);
पूर्ण

अटल पूर्णांक ixgbevf_tso(काष्ठा ixgbevf_ring *tx_ring,
		       काष्ठा ixgbevf_tx_buffer *first,
		       u8 *hdr_len,
		       काष्ठा ixgbevf_ipsec_tx_data *itd)
अणु
	u32 vlan_macip_lens, type_tucmd, mss_l4len_idx;
	काष्ठा sk_buff *skb = first->skb;
	जोड़ अणु
		काष्ठा iphdr *v4;
		काष्ठा ipv6hdr *v6;
		अचिन्हित अक्षर *hdr;
	पूर्ण ip;
	जोड़ अणु
		काष्ठा tcphdr *tcp;
		अचिन्हित अक्षर *hdr;
	पूर्ण l4;
	u32 paylen, l4_offset;
	u32 fceof_saidx = 0;
	पूर्णांक err;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	अगर (!skb_is_gso(skb))
		वापस 0;

	err = skb_cow_head(skb, 0);
	अगर (err < 0)
		वापस err;

	अगर (eth_p_mpls(first->protocol))
		ip.hdr = skb_inner_network_header(skb);
	अन्यथा
		ip.hdr = skb_network_header(skb);
	l4.hdr = skb_checksum_start(skb);

	/* ADV DTYP TUCMD MKRLOC/ISCSIHEDLEN */
	type_tucmd = IXGBE_ADVTXD_TUCMD_L4T_TCP;

	/* initialize outer IP header fields */
	अगर (ip.v4->version == 4) अणु
		अचिन्हित अक्षर *csum_start = skb_checksum_start(skb);
		अचिन्हित अक्षर *trans_start = ip.hdr + (ip.v4->ihl * 4);
		पूर्णांक len = csum_start - trans_start;

		/* IP header will have to cancel out any data that
		 * is not a part of the outer IP header, so set to
		 * a reverse csum अगर needed, अन्यथा init check to 0.
		 */
		ip.v4->check = (skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL) ?
					   csum_fold(csum_partial(trans_start,
								  len, 0)) : 0;
		type_tucmd |= IXGBE_ADVTXD_TUCMD_IPV4;

		ip.v4->tot_len = 0;
		first->tx_flags |= IXGBE_TX_FLAGS_TSO |
				   IXGBE_TX_FLAGS_CSUM |
				   IXGBE_TX_FLAGS_IPV4;
	पूर्ण अन्यथा अणु
		ip.v6->payload_len = 0;
		first->tx_flags |= IXGBE_TX_FLAGS_TSO |
				   IXGBE_TX_FLAGS_CSUM;
	पूर्ण

	/* determine offset of inner transport header */
	l4_offset = l4.hdr - skb->data;

	/* compute length of segmentation header */
	*hdr_len = (l4.tcp->करोff * 4) + l4_offset;

	/* हटाओ payload length from inner checksum */
	paylen = skb->len - l4_offset;
	csum_replace_by_dअगरf(&l4.tcp->check, htonl(paylen));

	/* update gso size and bytecount with header size */
	first->gso_segs = skb_shinfo(skb)->gso_segs;
	first->bytecount += (first->gso_segs - 1) * *hdr_len;

	/* mss_l4len_id: use 1 as index क्रम TSO */
	mss_l4len_idx = (*hdr_len - l4_offset) << IXGBE_ADVTXD_L4LEN_SHIFT;
	mss_l4len_idx |= skb_shinfo(skb)->gso_size << IXGBE_ADVTXD_MSS_SHIFT;
	mss_l4len_idx |= (1u << IXGBE_ADVTXD_IDX_SHIFT);

	fceof_saidx |= itd->pfsa;
	type_tucmd |= itd->flags | itd->trailer_len;

	/* vlan_macip_lens: HEADLEN, MACLEN, VLAN tag */
	vlan_macip_lens = l4.hdr - ip.hdr;
	vlan_macip_lens |= (ip.hdr - skb->data) << IXGBE_ADVTXD_MACLEN_SHIFT;
	vlan_macip_lens |= first->tx_flags & IXGBE_TX_FLAGS_VLAN_MASK;

	ixgbevf_tx_ctxtdesc(tx_ring, vlan_macip_lens, fceof_saidx, type_tucmd,
			    mss_l4len_idx);

	वापस 1;
पूर्ण

अटल व्योम ixgbevf_tx_csum(काष्ठा ixgbevf_ring *tx_ring,
			    काष्ठा ixgbevf_tx_buffer *first,
			    काष्ठा ixgbevf_ipsec_tx_data *itd)
अणु
	काष्ठा sk_buff *skb = first->skb;
	u32 vlan_macip_lens = 0;
	u32 fceof_saidx = 0;
	u32 type_tucmd = 0;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		जाओ no_csum;

	चयन (skb->csum_offset) अणु
	हाल दुरत्व(काष्ठा tcphdr, check):
		type_tucmd = IXGBE_ADVTXD_TUCMD_L4T_TCP;
		fallthrough;
	हाल दुरत्व(काष्ठा udphdr, check):
		अवरोध;
	हाल दुरत्व(काष्ठा sctphdr, checksum):
		/* validate that this is actually an SCTP request */
		अगर (skb_csum_is_sctp(skb)) अणु
			type_tucmd = IXGBE_ADVTXD_TUCMD_L4T_SCTP;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		skb_checksum_help(skb);
		जाओ no_csum;
	पूर्ण

	अगर (first->protocol == htons(ETH_P_IP))
		type_tucmd |= IXGBE_ADVTXD_TUCMD_IPV4;

	/* update TX checksum flag */
	first->tx_flags |= IXGBE_TX_FLAGS_CSUM;
	vlan_macip_lens = skb_checksum_start_offset(skb) -
			  skb_network_offset(skb);
no_csum:
	/* vlan_macip_lens: MACLEN, VLAN tag */
	vlan_macip_lens |= skb_network_offset(skb) << IXGBE_ADVTXD_MACLEN_SHIFT;
	vlan_macip_lens |= first->tx_flags & IXGBE_TX_FLAGS_VLAN_MASK;

	fceof_saidx |= itd->pfsa;
	type_tucmd |= itd->flags | itd->trailer_len;

	ixgbevf_tx_ctxtdesc(tx_ring, vlan_macip_lens,
			    fceof_saidx, type_tucmd, 0);
पूर्ण

अटल __le32 ixgbevf_tx_cmd_type(u32 tx_flags)
अणु
	/* set type क्रम advanced descriptor with frame checksum insertion */
	__le32 cmd_type = cpu_to_le32(IXGBE_ADVTXD_DTYP_DATA |
				      IXGBE_ADVTXD_DCMD_IFCS |
				      IXGBE_ADVTXD_DCMD_DEXT);

	/* set HW VLAN bit अगर VLAN is present */
	अगर (tx_flags & IXGBE_TX_FLAGS_VLAN)
		cmd_type |= cpu_to_le32(IXGBE_ADVTXD_DCMD_VLE);

	/* set segmentation enable bits क्रम TSO/FSO */
	अगर (tx_flags & IXGBE_TX_FLAGS_TSO)
		cmd_type |= cpu_to_le32(IXGBE_ADVTXD_DCMD_TSE);

	वापस cmd_type;
पूर्ण

अटल व्योम ixgbevf_tx_olinfo_status(जोड़ ixgbe_adv_tx_desc *tx_desc,
				     u32 tx_flags, अचिन्हित पूर्णांक paylen)
अणु
	__le32 olinfo_status = cpu_to_le32(paylen << IXGBE_ADVTXD_PAYLEN_SHIFT);

	/* enable L4 checksum क्रम TSO and TX checksum offload */
	अगर (tx_flags & IXGBE_TX_FLAGS_CSUM)
		olinfo_status |= cpu_to_le32(IXGBE_ADVTXD_POPTS_TXSM);

	/* enble IPv4 checksum क्रम TSO */
	अगर (tx_flags & IXGBE_TX_FLAGS_IPV4)
		olinfo_status |= cpu_to_le32(IXGBE_ADVTXD_POPTS_IXSM);

	/* enable IPsec */
	अगर (tx_flags & IXGBE_TX_FLAGS_IPSEC)
		olinfo_status |= cpu_to_le32(IXGBE_ADVTXD_POPTS_IPSEC);

	/* use index 1 context क्रम TSO/FSO/FCOE/IPSEC */
	अगर (tx_flags & (IXGBE_TX_FLAGS_TSO | IXGBE_TX_FLAGS_IPSEC))
		olinfo_status |= cpu_to_le32(1u << IXGBE_ADVTXD_IDX_SHIFT);

	/* Check Context must be set अगर Tx चयन is enabled, which it
	 * always is क्रम हाल where भव functions are running
	 */
	olinfo_status |= cpu_to_le32(IXGBE_ADVTXD_CC);

	tx_desc->पढ़ो.olinfo_status = olinfo_status;
पूर्ण

अटल व्योम ixgbevf_tx_map(काष्ठा ixgbevf_ring *tx_ring,
			   काष्ठा ixgbevf_tx_buffer *first,
			   स्थिर u8 hdr_len)
अणु
	काष्ठा sk_buff *skb = first->skb;
	काष्ठा ixgbevf_tx_buffer *tx_buffer;
	जोड़ ixgbe_adv_tx_desc *tx_desc;
	skb_frag_t *frag;
	dma_addr_t dma;
	अचिन्हित पूर्णांक data_len, size;
	u32 tx_flags = first->tx_flags;
	__le32 cmd_type = ixgbevf_tx_cmd_type(tx_flags);
	u16 i = tx_ring->next_to_use;

	tx_desc = IXGBEVF_TX_DESC(tx_ring, i);

	ixgbevf_tx_olinfo_status(tx_desc, tx_flags, skb->len - hdr_len);

	size = skb_headlen(skb);
	data_len = skb->data_len;

	dma = dma_map_single(tx_ring->dev, skb->data, size, DMA_TO_DEVICE);

	tx_buffer = first;

	क्रम (frag = &skb_shinfo(skb)->frags[0];; frag++) अणु
		अगर (dma_mapping_error(tx_ring->dev, dma))
			जाओ dma_error;

		/* record length, and DMA address */
		dma_unmap_len_set(tx_buffer, len, size);
		dma_unmap_addr_set(tx_buffer, dma, dma);

		tx_desc->पढ़ो.buffer_addr = cpu_to_le64(dma);

		जबतक (unlikely(size > IXGBE_MAX_DATA_PER_TXD)) अणु
			tx_desc->पढ़ो.cmd_type_len =
				cmd_type | cpu_to_le32(IXGBE_MAX_DATA_PER_TXD);

			i++;
			tx_desc++;
			अगर (i == tx_ring->count) अणु
				tx_desc = IXGBEVF_TX_DESC(tx_ring, 0);
				i = 0;
			पूर्ण
			tx_desc->पढ़ो.olinfo_status = 0;

			dma += IXGBE_MAX_DATA_PER_TXD;
			size -= IXGBE_MAX_DATA_PER_TXD;

			tx_desc->पढ़ो.buffer_addr = cpu_to_le64(dma);
		पूर्ण

		अगर (likely(!data_len))
			अवरोध;

		tx_desc->पढ़ो.cmd_type_len = cmd_type | cpu_to_le32(size);

		i++;
		tx_desc++;
		अगर (i == tx_ring->count) अणु
			tx_desc = IXGBEVF_TX_DESC(tx_ring, 0);
			i = 0;
		पूर्ण
		tx_desc->पढ़ो.olinfo_status = 0;

		size = skb_frag_size(frag);
		data_len -= size;

		dma = skb_frag_dma_map(tx_ring->dev, frag, 0, size,
				       DMA_TO_DEVICE);

		tx_buffer = &tx_ring->tx_buffer_info[i];
	पूर्ण

	/* ग_लिखो last descriptor with RS and EOP bits */
	cmd_type |= cpu_to_le32(size) | cpu_to_le32(IXGBE_TXD_CMD);
	tx_desc->पढ़ो.cmd_type_len = cmd_type;

	/* set the बारtamp */
	first->समय_stamp = jअगरfies;

	skb_tx_बारtamp(skb);

	/* Force memory ग_लिखोs to complete beक्रमe letting h/w know there
	 * are new descriptors to fetch.  (Only applicable क्रम weak-ordered
	 * memory model archs, such as IA-64).
	 *
	 * We also need this memory barrier (wmb) to make certain all of the
	 * status bits have been updated beक्रमe next_to_watch is written.
	 */
	wmb();

	/* set next_to_watch value indicating a packet is present */
	first->next_to_watch = tx_desc;

	i++;
	अगर (i == tx_ring->count)
		i = 0;

	tx_ring->next_to_use = i;

	/* notअगरy HW of packet */
	ixgbevf_ग_लिखो_tail(tx_ring, i);

	वापस;
dma_error:
	dev_err(tx_ring->dev, "TX DMA map failed\n");
	tx_buffer = &tx_ring->tx_buffer_info[i];

	/* clear dma mappings क्रम failed tx_buffer_info map */
	जबतक (tx_buffer != first) अणु
		अगर (dma_unmap_len(tx_buffer, len))
			dma_unmap_page(tx_ring->dev,
				       dma_unmap_addr(tx_buffer, dma),
				       dma_unmap_len(tx_buffer, len),
				       DMA_TO_DEVICE);
		dma_unmap_len_set(tx_buffer, len, 0);

		अगर (i-- == 0)
			i += tx_ring->count;
		tx_buffer = &tx_ring->tx_buffer_info[i];
	पूर्ण

	अगर (dma_unmap_len(tx_buffer, len))
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);
	dma_unmap_len_set(tx_buffer, len, 0);

	dev_kमुक्त_skb_any(tx_buffer->skb);
	tx_buffer->skb = शून्य;

	tx_ring->next_to_use = i;
पूर्ण

अटल पूर्णांक __ixgbevf_maybe_stop_tx(काष्ठा ixgbevf_ring *tx_ring, पूर्णांक size)
अणु
	netअगर_stop_subqueue(tx_ring->netdev, tx_ring->queue_index);
	/* Herbert's original patch had:
	 *  smp_mb__after_netअगर_stop_queue();
	 * but since that करोesn't exist yet, just खोलो code it.
	 */
	smp_mb();

	/* We need to check again in a हाल another CPU has just
	 * made room available.
	 */
	अगर (likely(ixgbevf_desc_unused(tx_ring) < size))
		वापस -EBUSY;

	/* A reprieve! - use start_queue because it करोesn't call schedule */
	netअगर_start_subqueue(tx_ring->netdev, tx_ring->queue_index);
	++tx_ring->tx_stats.restart_queue;

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbevf_maybe_stop_tx(काष्ठा ixgbevf_ring *tx_ring, पूर्णांक size)
अणु
	अगर (likely(ixgbevf_desc_unused(tx_ring) >= size))
		वापस 0;
	वापस __ixgbevf_maybe_stop_tx(tx_ring, size);
पूर्ण

अटल पूर्णांक ixgbevf_xmit_frame_ring(काष्ठा sk_buff *skb,
				   काष्ठा ixgbevf_ring *tx_ring)
अणु
	काष्ठा ixgbevf_tx_buffer *first;
	पूर्णांक tso;
	u32 tx_flags = 0;
	u16 count = TXD_USE_COUNT(skb_headlen(skb));
	काष्ठा ixgbevf_ipsec_tx_data ipsec_tx = अणु 0 पूर्ण;
#अगर PAGE_SIZE > IXGBE_MAX_DATA_PER_TXD
	अचिन्हित लघु f;
#पूर्ण_अगर
	u8 hdr_len = 0;
	u8 *dst_mac = skb_header_poपूर्णांकer(skb, 0, 0, शून्य);

	अगर (!dst_mac || is_link_local_ether_addr(dst_mac)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* need: 1 descriptor per page * PAGE_SIZE/IXGBE_MAX_DATA_PER_TXD,
	 *       + 1 desc क्रम skb_headlen/IXGBE_MAX_DATA_PER_TXD,
	 *       + 2 desc gap to keep tail from touching head,
	 *       + 1 desc क्रम context descriptor,
	 * otherwise try next समय
	 */
#अगर PAGE_SIZE > IXGBE_MAX_DATA_PER_TXD
	क्रम (f = 0; f < skb_shinfo(skb)->nr_frags; f++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[f];

		count += TXD_USE_COUNT(skb_frag_size(frag));
	पूर्ण
#अन्यथा
	count += skb_shinfo(skb)->nr_frags;
#पूर्ण_अगर
	अगर (ixgbevf_maybe_stop_tx(tx_ring, count + 3)) अणु
		tx_ring->tx_stats.tx_busy++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* record the location of the first descriptor क्रम this packet */
	first = &tx_ring->tx_buffer_info[tx_ring->next_to_use];
	first->skb = skb;
	first->bytecount = skb->len;
	first->gso_segs = 1;

	अगर (skb_vlan_tag_present(skb)) अणु
		tx_flags |= skb_vlan_tag_get(skb);
		tx_flags <<= IXGBE_TX_FLAGS_VLAN_SHIFT;
		tx_flags |= IXGBE_TX_FLAGS_VLAN;
	पूर्ण

	/* record initial flags and protocol */
	first->tx_flags = tx_flags;
	first->protocol = vlan_get_protocol(skb);

#अगर_घोषित CONFIG_IXGBEVF_IPSEC
	अगर (xfrm_offload(skb) && !ixgbevf_ipsec_tx(tx_ring, first, &ipsec_tx))
		जाओ out_drop;
#पूर्ण_अगर
	tso = ixgbevf_tso(tx_ring, first, &hdr_len, &ipsec_tx);
	अगर (tso < 0)
		जाओ out_drop;
	अन्यथा अगर (!tso)
		ixgbevf_tx_csum(tx_ring, first, &ipsec_tx);

	ixgbevf_tx_map(tx_ring, first, hdr_len);

	ixgbevf_maybe_stop_tx(tx_ring, DESC_NEEDED);

	वापस NETDEV_TX_OK;

out_drop:
	dev_kमुक्त_skb_any(first->skb);
	first->skb = शून्य;

	वापस NETDEV_TX_OK;
पूर्ण

अटल netdev_tx_t ixgbevf_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbevf_ring *tx_ring;

	अगर (skb->len <= 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* The minimum packet size क्रम olinfo paylen is 17 so pad the skb
	 * in order to meet this minimum size requirement.
	 */
	अगर (skb->len < 17) अणु
		अगर (skb_padto(skb, 17))
			वापस NETDEV_TX_OK;
		skb->len = 17;
	पूर्ण

	tx_ring = adapter->tx_ring[skb->queue_mapping];
	वापस ixgbevf_xmit_frame_ring(skb, tx_ring);
पूर्ण

/**
 * ixgbevf_set_mac - Change the Ethernet Address of the NIC
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक ixgbevf_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा sockaddr *addr = p;
	पूर्णांक err;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	spin_lock_bh(&adapter->mbx_lock);

	err = hw->mac.ops.set_rar(hw, 0, addr->sa_data, 0);

	spin_unlock_bh(&adapter->mbx_lock);

	अगर (err)
		वापस -EPERM;

	ether_addr_copy(hw->mac.addr, addr->sa_data);
	ether_addr_copy(hw->mac.perm_addr, addr->sa_data);
	ether_addr_copy(netdev->dev_addr, addr->sa_data);

	वापस 0;
पूर्ण

/**
 * ixgbevf_change_mtu - Change the Maximum Transfer Unit
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक ixgbevf_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक max_frame = new_mtu + ETH_HLEN + ETH_FCS_LEN;
	पूर्णांक ret;

	/* prevent MTU being changed to a size unsupported by XDP */
	अगर (adapter->xdp_prog) अणु
		dev_warn(&adapter->pdev->dev, "MTU cannot be changed while XDP program is loaded\n");
		वापस -EPERM;
	पूर्ण

	spin_lock_bh(&adapter->mbx_lock);
	/* notअगरy the PF of our पूर्णांकent to use this size of frame */
	ret = hw->mac.ops.set_rlpml(hw, max_frame);
	spin_unlock_bh(&adapter->mbx_lock);
	अगर (ret)
		वापस -EINVAL;

	hw_dbg(hw, "changing MTU from %d to %d\n",
	       netdev->mtu, new_mtu);

	/* must set new MTU beक्रमe calling करोwn or up */
	netdev->mtu = new_mtu;

	अगर (netअगर_running(netdev))
		ixgbevf_reinit_locked(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ixgbevf_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev_d);
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);

	rtnl_lock();
	netअगर_device_detach(netdev);

	अगर (netअगर_running(netdev))
		ixgbevf_बंद_suspend(adapter);

	ixgbevf_clear_पूर्णांकerrupt_scheme(adapter);
	rtnl_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ixgbevf_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev_d);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	u32 err;

	adapter->hw.hw_addr = adapter->io_addr;
	smp_mb__beक्रमe_atomic();
	clear_bit(__IXGBEVF_DISABLED, &adapter->state);
	pci_set_master(pdev);

	ixgbevf_reset(adapter);

	rtnl_lock();
	err = ixgbevf_init_पूर्णांकerrupt_scheme(adapter);
	अगर (!err && netअगर_running(netdev))
		err = ixgbevf_खोलो(netdev);
	rtnl_unlock();
	अगर (err)
		वापस err;

	netअगर_device_attach(netdev);

	वापस err;
पूर्ण

अटल व्योम ixgbevf_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	ixgbevf_suspend(&pdev->dev);
पूर्ण

अटल व्योम ixgbevf_get_tx_ring_stats(काष्ठा rtnl_link_stats64 *stats,
				      स्थिर काष्ठा ixgbevf_ring *ring)
अणु
	u64 bytes, packets;
	अचिन्हित पूर्णांक start;

	अगर (ring) अणु
		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			bytes = ring->stats.bytes;
			packets = ring->stats.packets;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));
		stats->tx_bytes += bytes;
		stats->tx_packets += packets;
	पूर्ण
पूर्ण

अटल व्योम ixgbevf_get_stats(काष्ठा net_device *netdev,
			      काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);
	अचिन्हित पूर्णांक start;
	u64 bytes, packets;
	स्थिर काष्ठा ixgbevf_ring *ring;
	पूर्णांक i;

	ixgbevf_update_stats(adapter);

	stats->multicast = adapter->stats.vfmprc - adapter->stats.base_vfmprc;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		ring = adapter->rx_ring[i];
		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			bytes = ring->stats.bytes;
			packets = ring->stats.packets;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));
		stats->rx_bytes += bytes;
		stats->rx_packets += packets;
	पूर्ण

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		ring = adapter->tx_ring[i];
		ixgbevf_get_tx_ring_stats(stats, ring);
	पूर्ण

	क्रम (i = 0; i < adapter->num_xdp_queues; i++) अणु
		ring = adapter->xdp_ring[i];
		ixgbevf_get_tx_ring_stats(stats, ring);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

#घोषणा IXGBEVF_MAX_MAC_HDR_LEN		127
#घोषणा IXGBEVF_MAX_NETWORK_HDR_LEN	511

अटल netdev_features_t
ixgbevf_features_check(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       netdev_features_t features)
अणु
	अचिन्हित पूर्णांक network_hdr_len, mac_hdr_len;

	/* Make certain the headers can be described by a context descriptor */
	mac_hdr_len = skb_network_header(skb) - skb->data;
	अगर (unlikely(mac_hdr_len > IXGBEVF_MAX_MAC_HDR_LEN))
		वापस features & ~(NETIF_F_HW_CSUM |
				    NETIF_F_SCTP_CRC |
				    NETIF_F_HW_VLAN_CTAG_TX |
				    NETIF_F_TSO |
				    NETIF_F_TSO6);

	network_hdr_len = skb_checksum_start(skb) - skb_network_header(skb);
	अगर (unlikely(network_hdr_len >  IXGBEVF_MAX_NETWORK_HDR_LEN))
		वापस features & ~(NETIF_F_HW_CSUM |
				    NETIF_F_SCTP_CRC |
				    NETIF_F_TSO |
				    NETIF_F_TSO6);

	/* We can only support IPV4 TSO in tunnels अगर we can mangle the
	 * inner IP ID field, so strip TSO अगर MANGLEID is not supported.
	 */
	अगर (skb->encapsulation && !(features & NETIF_F_TSO_MANGLEID))
		features &= ~NETIF_F_TSO;

	वापस features;
पूर्ण

अटल पूर्णांक ixgbevf_xdp_setup(काष्ठा net_device *dev, काष्ठा bpf_prog *prog)
अणु
	पूर्णांक i, frame_size = dev->mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(dev);
	काष्ठा bpf_prog *old_prog;

	/* verअगरy ixgbevf ring attributes are sufficient क्रम XDP */
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा ixgbevf_ring *ring = adapter->rx_ring[i];

		अगर (frame_size > ixgbevf_rx_bufsz(ring))
			वापस -EINVAL;
	पूर्ण

	old_prog = xchg(&adapter->xdp_prog, prog);

	/* If transitioning XDP modes reconfigure rings */
	अगर (!!prog != !!old_prog) अणु
		/* Hardware has to reinitialize queues and पूर्णांकerrupts to
		 * match packet buffer alignment. Unक्रमtunately, the
		 * hardware is not flexible enough to करो this dynamically.
		 */
		अगर (netअगर_running(dev))
			ixgbevf_बंद(dev);

		ixgbevf_clear_पूर्णांकerrupt_scheme(adapter);
		ixgbevf_init_पूर्णांकerrupt_scheme(adapter);

		अगर (netअगर_running(dev))
			ixgbevf_खोलो(dev);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < adapter->num_rx_queues; i++)
			xchg(&adapter->rx_ring[i]->xdp_prog, adapter->xdp_prog);
	पूर्ण

	अगर (old_prog)
		bpf_prog_put(old_prog);

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbevf_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस ixgbevf_xdp_setup(dev, xdp->prog);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops ixgbevf_netdev_ops = अणु
	.nकरो_खोलो		= ixgbevf_खोलो,
	.nकरो_stop		= ixgbevf_बंद,
	.nकरो_start_xmit		= ixgbevf_xmit_frame,
	.nकरो_set_rx_mode	= ixgbevf_set_rx_mode,
	.nकरो_get_stats64	= ixgbevf_get_stats,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= ixgbevf_set_mac,
	.nकरो_change_mtu		= ixgbevf_change_mtu,
	.nकरो_tx_समयout		= ixgbevf_tx_समयout,
	.nकरो_vlan_rx_add_vid	= ixgbevf_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= ixgbevf_vlan_rx_समाप्त_vid,
	.nकरो_features_check	= ixgbevf_features_check,
	.nकरो_bpf		= ixgbevf_xdp,
पूर्ण;

अटल व्योम ixgbevf_assign_netdev_ops(काष्ठा net_device *dev)
अणु
	dev->netdev_ops = &ixgbevf_netdev_ops;
	ixgbevf_set_ethtool_ops(dev);
	dev->watchकरोg_समयo = 5 * HZ;
पूर्ण

/**
 * ixgbevf_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in ixgbevf_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * ixgbevf_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 **/
अटल पूर्णांक ixgbevf_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा ixgbevf_adapter *adapter = शून्य;
	काष्ठा ixgbe_hw *hw = शून्य;
	स्थिर काष्ठा ixgbevf_info *ii = ixgbevf_info_tbl[ent->driver_data];
	पूर्णांक err, pci_using_dac;
	bool disable_dev = false;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	अगर (!dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64))) अणु
		pci_using_dac = 1;
	पूर्ण अन्यथा अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev, "No usable DMA configuration, aborting\n");
			जाओ err_dma;
		पूर्ण
		pci_using_dac = 0;
	पूर्ण

	err = pci_request_regions(pdev, ixgbevf_driver_name);
	अगर (err) अणु
		dev_err(&pdev->dev, "pci_request_regions failed 0x%x\n", err);
		जाओ err_pci_reg;
	पूर्ण

	pci_set_master(pdev);

	netdev = alloc_etherdev_mq(माप(काष्ठा ixgbevf_adapter),
				   MAX_TX_QUEUES);
	अगर (!netdev) अणु
		err = -ENOMEM;
		जाओ err_alloc_etherdev;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);

	adapter = netdev_priv(netdev);

	adapter->netdev = netdev;
	adapter->pdev = pdev;
	hw = &adapter->hw;
	hw->back = adapter;
	adapter->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);

	/* call save state here in standalone driver because it relies on
	 * adapter काष्ठा to exist, and needs to call netdev_priv
	 */
	pci_save_state(pdev);

	hw->hw_addr = ioremap(pci_resource_start(pdev, 0),
			      pci_resource_len(pdev, 0));
	adapter->io_addr = hw->hw_addr;
	अगर (!hw->hw_addr) अणु
		err = -EIO;
		जाओ err_ioremap;
	पूर्ण

	ixgbevf_assign_netdev_ops(netdev);

	/* Setup HW API */
	स_नकल(&hw->mac.ops, ii->mac_ops, माप(hw->mac.ops));
	hw->mac.type  = ii->mac;

	स_नकल(&hw->mbx.ops, &ixgbevf_mbx_ops,
	       माप(काष्ठा ixgbe_mbx_operations));

	/* setup the निजी काष्ठाure */
	err = ixgbevf_sw_init(adapter);
	अगर (err)
		जाओ err_sw_init;

	/* The HW MAC address was set and/or determined in sw_init */
	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		pr_err("invalid MAC address\n");
		err = -EIO;
		जाओ err_sw_init;
	पूर्ण

	netdev->hw_features = NETIF_F_SG |
			      NETIF_F_TSO |
			      NETIF_F_TSO6 |
			      NETIF_F_RXCSUM |
			      NETIF_F_HW_CSUM |
			      NETIF_F_SCTP_CRC;

#घोषणा IXGBEVF_GSO_PARTIAL_FEATURES (NETIF_F_GSO_GRE | \
				      NETIF_F_GSO_GRE_CSUM | \
				      NETIF_F_GSO_IPXIP4 | \
				      NETIF_F_GSO_IPXIP6 | \
				      NETIF_F_GSO_UDP_TUNNEL | \
				      NETIF_F_GSO_UDP_TUNNEL_CSUM)

	netdev->gso_partial_features = IXGBEVF_GSO_PARTIAL_FEATURES;
	netdev->hw_features |= NETIF_F_GSO_PARTIAL |
			       IXGBEVF_GSO_PARTIAL_FEATURES;

	netdev->features = netdev->hw_features;

	अगर (pci_using_dac)
		netdev->features |= NETIF_F_HIGHDMA;

	netdev->vlan_features |= netdev->features | NETIF_F_TSO_MANGLEID;
	netdev->mpls_features |= NETIF_F_SG |
				 NETIF_F_TSO |
				 NETIF_F_TSO6 |
				 NETIF_F_HW_CSUM;
	netdev->mpls_features |= IXGBEVF_GSO_PARTIAL_FEATURES;
	netdev->hw_enc_features |= netdev->vlan_features;

	/* set this bit last since it cannot be part of vlan_features */
	netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER |
			    NETIF_F_HW_VLAN_CTAG_RX |
			    NETIF_F_HW_VLAN_CTAG_TX;

	netdev->priv_flags |= IFF_UNICAST_FLT;

	/* MTU range: 68 - 1504 or 9710 */
	netdev->min_mtu = ETH_MIN_MTU;
	चयन (adapter->hw.api_version) अणु
	हाल ixgbe_mbox_api_11:
	हाल ixgbe_mbox_api_12:
	हाल ixgbe_mbox_api_13:
	हाल ixgbe_mbox_api_14:
		netdev->max_mtu = IXGBE_MAX_JUMBO_FRAME_SIZE -
				  (ETH_HLEN + ETH_FCS_LEN);
		अवरोध;
	शेष:
		अगर (adapter->hw.mac.type != ixgbe_mac_82599_vf)
			netdev->max_mtu = IXGBE_MAX_JUMBO_FRAME_SIZE -
					  (ETH_HLEN + ETH_FCS_LEN);
		अन्यथा
			netdev->max_mtu = ETH_DATA_LEN + ETH_FCS_LEN;
		अवरोध;
	पूर्ण

	अगर (IXGBE_REMOVED(hw->hw_addr)) अणु
		err = -EIO;
		जाओ err_sw_init;
	पूर्ण

	समयr_setup(&adapter->service_समयr, ixgbevf_service_समयr, 0);

	INIT_WORK(&adapter->service_task, ixgbevf_service_task);
	set_bit(__IXGBEVF_SERVICE_INITED, &adapter->state);
	clear_bit(__IXGBEVF_SERVICE_SCHED, &adapter->state);

	err = ixgbevf_init_पूर्णांकerrupt_scheme(adapter);
	अगर (err)
		जाओ err_sw_init;

	म_नकल(netdev->name, "eth%d");

	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_रेजिस्टर;

	pci_set_drvdata(pdev, netdev);
	netअगर_carrier_off(netdev);
	ixgbevf_init_ipsec_offload(adapter);

	ixgbevf_init_last_counter_stats(adapter);

	/* prपूर्णांक the VF info */
	dev_info(&pdev->dev, "%pM\n", netdev->dev_addr);
	dev_info(&pdev->dev, "MAC: %d\n", hw->mac.type);

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_X550_vf:
		dev_info(&pdev->dev, "Intel(R) X550 Virtual Function\n");
		अवरोध;
	हाल ixgbe_mac_X540_vf:
		dev_info(&pdev->dev, "Intel(R) X540 Virtual Function\n");
		अवरोध;
	हाल ixgbe_mac_82599_vf:
	शेष:
		dev_info(&pdev->dev, "Intel(R) 82599 Virtual Function\n");
		अवरोध;
	पूर्ण

	वापस 0;

err_रेजिस्टर:
	ixgbevf_clear_पूर्णांकerrupt_scheme(adapter);
err_sw_init:
	ixgbevf_reset_पूर्णांकerrupt_capability(adapter);
	iounmap(adapter->io_addr);
	kमुक्त(adapter->rss_key);
err_ioremap:
	disable_dev = !test_and_set_bit(__IXGBEVF_DISABLED, &adapter->state);
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	pci_release_regions(pdev);
err_pci_reg:
err_dma:
	अगर (!adapter || disable_dev)
		pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * ixgbevf_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * ixgbevf_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  The could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 **/
अटल व्योम ixgbevf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा ixgbevf_adapter *adapter;
	bool disable_dev;

	अगर (!netdev)
		वापस;

	adapter = netdev_priv(netdev);

	set_bit(__IXGBEVF_REMOVING, &adapter->state);
	cancel_work_sync(&adapter->service_task);

	अगर (netdev->reg_state == NETREG_REGISTERED)
		unरेजिस्टर_netdev(netdev);

	ixgbevf_stop_ipsec_offload(adapter);
	ixgbevf_clear_पूर्णांकerrupt_scheme(adapter);
	ixgbevf_reset_पूर्णांकerrupt_capability(adapter);

	iounmap(adapter->io_addr);
	pci_release_regions(pdev);

	hw_dbg(&adapter->hw, "Remove complete\n");

	kमुक्त(adapter->rss_key);
	disable_dev = !test_and_set_bit(__IXGBEVF_DISABLED, &adapter->state);
	मुक्त_netdev(netdev);

	अगर (disable_dev)
		pci_disable_device(pdev);
पूर्ण

/**
 * ixgbevf_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 **/
अटल pci_ers_result_t ixgbevf_io_error_detected(काष्ठा pci_dev *pdev,
						  pci_channel_state_t state)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);

	अगर (!test_bit(__IXGBEVF_SERVICE_INITED, &adapter->state))
		वापस PCI_ERS_RESULT_DISCONNECT;

	rtnl_lock();
	netअगर_device_detach(netdev);

	अगर (netअगर_running(netdev))
		ixgbevf_बंद_suspend(adapter);

	अगर (state == pci_channel_io_perm_failure) अणु
		rtnl_unlock();
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	अगर (!test_and_set_bit(__IXGBEVF_DISABLED, &adapter->state))
		pci_disable_device(pdev);
	rtnl_unlock();

	/* Request a slot slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * ixgbevf_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot. Implementation
 * resembles the first-half of the ixgbevf_resume routine.
 **/
अटल pci_ers_result_t ixgbevf_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा ixgbevf_adapter *adapter = netdev_priv(netdev);

	अगर (pci_enable_device_mem(pdev)) अणु
		dev_err(&pdev->dev,
			"Cannot re-enable PCI device after reset.\n");
		वापस PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	adapter->hw.hw_addr = adapter->io_addr;
	smp_mb__beक्रमe_atomic();
	clear_bit(__IXGBEVF_DISABLED, &adapter->state);
	pci_set_master(pdev);

	ixgbevf_reset(adapter);

	वापस PCI_ERS_RESULT_RECOVERED;
पूर्ण

/**
 * ixgbevf_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells us that
 * its OK to resume normal operation. Implementation resembles the
 * second-half of the ixgbevf_resume routine.
 **/
अटल व्योम ixgbevf_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);

	rtnl_lock();
	अगर (netअगर_running(netdev))
		ixgbevf_खोलो(netdev);

	netअगर_device_attach(netdev);
	rtnl_unlock();
पूर्ण

/* PCI Error Recovery (ERS) */
अटल स्थिर काष्ठा pci_error_handlers ixgbevf_err_handler = अणु
	.error_detected = ixgbevf_io_error_detected,
	.slot_reset = ixgbevf_io_slot_reset,
	.resume = ixgbevf_io_resume,
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(ixgbevf_pm_ops, ixgbevf_suspend, ixgbevf_resume);

अटल काष्ठा pci_driver ixgbevf_driver = अणु
	.name		= ixgbevf_driver_name,
	.id_table	= ixgbevf_pci_tbl,
	.probe		= ixgbevf_probe,
	.हटाओ		= ixgbevf_हटाओ,

	/* Power Management Hooks */
	.driver.pm	= &ixgbevf_pm_ops,

	.shutकरोwn	= ixgbevf_shutकरोwn,
	.err_handler	= &ixgbevf_err_handler
पूर्ण;

/**
 * ixgbevf_init_module - Driver Registration Routine
 *
 * ixgbevf_init_module is the first routine called when the driver is
 * loaded. All it करोes is रेजिस्टर with the PCI subप्रणाली.
 **/
अटल पूर्णांक __init ixgbevf_init_module(व्योम)
अणु
	pr_info("%s\n", ixgbevf_driver_string);
	pr_info("%s\n", ixgbevf_copyright);
	ixgbevf_wq = create_singlethपढ़ो_workqueue(ixgbevf_driver_name);
	अगर (!ixgbevf_wq) अणु
		pr_err("%s: Failed to create workqueue\n", ixgbevf_driver_name);
		वापस -ENOMEM;
	पूर्ण

	वापस pci_रेजिस्टर_driver(&ixgbevf_driver);
पूर्ण

module_init(ixgbevf_init_module);

/**
 * ixgbevf_निकास_module - Driver Exit Cleanup Routine
 *
 * ixgbevf_निकास_module is called just beक्रमe the driver is हटाओd
 * from memory.
 **/
अटल व्योम __निकास ixgbevf_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&ixgbevf_driver);
	अगर (ixgbevf_wq) अणु
		destroy_workqueue(ixgbevf_wq);
		ixgbevf_wq = शून्य;
	पूर्ण
पूर्ण

#अगर_घोषित DEBUG
/**
 * ixgbevf_get_hw_dev_name - वापस device name string
 * used by hardware layer to prपूर्णांक debugging inक्रमmation
 * @hw: poपूर्णांकer to निजी hardware काष्ठा
 **/
अक्षर *ixgbevf_get_hw_dev_name(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbevf_adapter *adapter = hw->back;

	वापस adapter->netdev->name;
पूर्ण

#पूर्ण_अगर
module_निकास(ixgbevf_निकास_module);

/* ixgbevf_मुख्य.c */
