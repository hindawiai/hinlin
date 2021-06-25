<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 **********************************************************************/

/*!  \पile  octeon_network.h
 *   \मrief Host NIC Driver: Structure and Macro definitions used by NIC Module.
 */

#अगर_अघोषित __OCTEON_NETWORK_H__
#घोषणा __OCTEON_NETWORK_H__
#समावेश <linux/ptp_घड़ी_kernel.h>

#घोषणा LIO_MAX_MTU_SIZE (OCTNET_MAX_FRM_SIZE - OCTNET_FRM_HEADER_SIZE)
#घोषणा LIO_MIN_MTU_SIZE ETH_MIN_MTU

/* Bit mask values क्रम lio->अगरstate */
#घोषणा   LIO_IFSTATE_DROQ_OPS             0x01
#घोषणा   LIO_IFSTATE_REGISTERED           0x02
#घोषणा   LIO_IFSTATE_RUNNING              0x04
#घोषणा   LIO_IFSTATE_RX_TIMESTAMP_ENABLED 0x08
#घोषणा   LIO_IFSTATE_RESETTING		   0x10

काष्ठा liquidio_अगर_cfg_resp अणु
	u64 rh;
	काष्ठा liquidio_अगर_cfg_info cfg_info;
	u64 status;
पूर्ण;

#घोषणा LIO_IFCFG_WAIT_TIME    3000 /* In milli seconds */
#घोषणा LIQUIDIO_NDEV_STATS_POLL_TIME_MS 200

/* Structure of a node in list of gather components मुख्यtained by
 * NIC driver क्रम each network device.
 */
काष्ठा octnic_gather अणु
	/* List manipulation. Next and prev poपूर्णांकers. */
	काष्ठा list_head list;

	/* Size of the gather component at sg in bytes. */
	पूर्णांक sg_size;

	/* Number of bytes that sg was adjusted to make it 8B-aligned. */
	पूर्णांक adjust;

	/* Gather component that can accommodate max sized fragment list
	 * received from the IP layer.
	 */
	काष्ठा octeon_sg_entry *sg;

	dma_addr_t sg_dma_ptr;
पूर्ण;

काष्ठा oct_nic_stats_resp अणु
	u64     rh;
	काष्ठा oct_link_stats stats;
	u64     status;
पूर्ण;

काष्ठा oct_nic_vf_stats_resp अणु
	u64     rh;
	u64	spoofmac_cnt;
	u64     status;
पूर्ण;

काष्ठा oct_nic_stats_ctrl अणु
	काष्ठा completion complete;
	काष्ठा net_device *netdev;
पूर्ण;

काष्ठा oct_nic_seapi_resp अणु
	u64 rh;
	जोड़ अणु
		u32 fec_setting;
		u32 speed;
	पूर्ण;
	u64 status;
पूर्ण;

/** LiquidIO per-पूर्णांकerface network निजी data */
काष्ठा lio अणु
	/** State of the पूर्णांकerface. Rx/Tx happens only in the RUNNING state.  */
	atomic_t अगरstate;

	/** Octeon Interface index number. This device will be represented as
	 *  oct<अगरidx> in the प्रणाली.
	 */
	पूर्णांक अगरidx;

	/** Octeon Input queue to use to transmit क्रम this network पूर्णांकerface. */
	पूर्णांक txq;

	/** Octeon Output queue from which pkts arrive
	 * क्रम this network पूर्णांकerface.
	 */
	पूर्णांक rxq;

	/** Guards each glist */
	spinlock_t *glist_lock;

	/** Array of gather component linked lists */
	काष्ठा list_head *glist;
	व्योम **glists_virt_base;
	dma_addr_t *glists_dma_base;
	u32 glist_entry_size;

	/** Poपूर्णांकer to the NIC properties क्रम the Octeon device this network
	 *  पूर्णांकerface is associated with.
	 */
	काष्ठा octdev_props *octprops;

	/** Poपूर्णांकer to the octeon device काष्ठाure. */
	काष्ठा octeon_device *oct_dev;

	काष्ठा net_device *netdev;

	/** Link inक्रमmation sent by the core application क्रम this पूर्णांकerface. */
	काष्ठा oct_link_info linfo;

	/** counter of link changes */
	u64 link_changes;

	/** Size of Tx queue क्रम this octeon device. */
	u32 tx_qsize;

	/** Size of Rx queue क्रम this octeon device. */
	u32 rx_qsize;

	/** Size of MTU this octeon device. */
	u32 mtu;

	/** msg level flag per पूर्णांकerface. */
	u32 msg_enable;

	/** Copy of Interface capabilities: TSO, TSO6, LRO, Chescksums . */
	u64 dev_capability;

	/* Copy of transmit encapsulation capabilities:
	 * TSO, TSO6, Checksums क्रम this device क्रम Kernel
	 * 3.10.0 onwards
	 */
	u64 enc_dev_capability;

	/** Copy of beacaon reg in phy */
	u32 phy_beacon_val;

	/** Copy of ctrl reg in phy */
	u32 led_ctrl_val;

	/* PTP घड़ी inक्रमmation */
	काष्ठा ptp_घड़ी_info ptp_info;
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	s64 ptp_adjust;

	/* क्रम atomic access to Octeon PTP reg and data काष्ठा */
	spinlock_t ptp_lock;

	/* Interface info */
	u32	पूर्णांकf_खोलो;

	/* work queue क्रम  txq status */
	काष्ठा cavium_wq	txq_status_wq;

	/* work queue क्रम  rxq oom status */
	काष्ठा cavium_wq rxq_status_wq[MAX_POSSIBLE_OCTEON_OUTPUT_QUEUES];

	/* work queue क्रम  link status */
	काष्ठा cavium_wq	link_status_wq;

	/* work queue to regularly send local समय to octeon firmware */
	काष्ठा cavium_wq	sync_octeon_समय_wq;

	पूर्णांक netdev_uc_count;
	काष्ठा cavium_wk stats_wk;
पूर्ण;

#घोषणा LIO_SIZE         (माप(काष्ठा lio))
#घोषणा GET_LIO(netdev)  ((काष्ठा lio *)netdev_priv(netdev))

#घोषणा LIO_MAX_CORES                16

/**
 * \मrief Enable or disable feature
 * @param netdev    poपूर्णांकer to network device
 * @param cmd       Command that just requires acknowledgment
 * @param param1    Parameter to command
 */
पूर्णांक liquidio_set_feature(काष्ठा net_device *netdev, पूर्णांक cmd, u16 param1);

पूर्णांक setup_rx_oom_poll_fn(काष्ठा net_device *netdev);

व्योम cleanup_rx_oom_poll_fn(काष्ठा net_device *netdev);

/**
 * \मrief Link control command completion callback
 * @param nctrl_ptr poपूर्णांकer to control packet काष्ठाure
 *
 * This routine is called by the callback function when a ctrl pkt sent to
 * core app completes. The nctrl_ptr contains a copy of the command type
 * and data sent to the core app. This routine is only called अगर the ctrl
 * pkt was sent successfully to the core app.
 */
व्योम liquidio_link_ctrl_cmd_completion(व्योम *nctrl_ptr);

पूर्णांक liquidio_setup_io_queues(काष्ठा octeon_device *octeon_dev, पूर्णांक अगरidx,
			     u32 num_iqs, u32 num_oqs);

irqवापस_t liquidio_msix_पूर्णांकr_handler(पूर्णांक irq __attribute__((unused)),
				       व्योम *dev);

पूर्णांक octeon_setup_पूर्णांकerrupt(काष्ठा octeon_device *oct, u32 num_ioqs);

व्योम lio_fetch_stats(काष्ठा work_काष्ठा *work);

पूर्णांक lio_रुको_क्रम_clean_oq(काष्ठा octeon_device *oct);
/**
 * \मrief Register ethtool operations
 * @param netdev    poपूर्णांकer to network device
 */
व्योम liquidio_set_ethtool_ops(काष्ठा net_device *netdev);

व्योम lio_delete_glists(काष्ठा lio *lio);

पूर्णांक lio_setup_glists(काष्ठा octeon_device *oct, काष्ठा lio *lio, पूर्णांक num_qs);

पूर्णांक liquidio_get_speed(काष्ठा lio *lio);
पूर्णांक liquidio_set_speed(काष्ठा lio *lio, पूर्णांक speed);
पूर्णांक liquidio_get_fec(काष्ठा lio *lio);
पूर्णांक liquidio_set_fec(काष्ठा lio *lio, पूर्णांक on_off);

/**
 * \मrief Net device change_mtu
 * @param netdev network device
 */
पूर्णांक liquidio_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu);
#घोषणा LIO_CHANGE_MTU_SUCCESS 1
#घोषणा LIO_CHANGE_MTU_FAIL    2

#घोषणा SKB_ADJ_MASK  0x3F
#घोषणा SKB_ADJ       (SKB_ADJ_MASK + 1)

#घोषणा MIN_SKB_SIZE       256 /* 8 bytes and more - 8 bytes क्रम PTP */
#घोषणा LIO_RXBUFFER_SZ    2048

अटल अंतरभूत व्योम
*recv_buffer_alloc(काष्ठा octeon_device *oct,
		   काष्ठा octeon_skb_page_info *pg_info)
अणु
	काष्ठा page *page;
	काष्ठा sk_buff *skb;
	काष्ठा octeon_skb_page_info *skb_pg_info;

	page = alloc_page(GFP_ATOMIC);
	अगर (unlikely(!page))
		वापस शून्य;

	skb = dev_alloc_skb(MIN_SKB_SIZE + SKB_ADJ);
	अगर (unlikely(!skb)) अणु
		__मुक्त_page(page);
		pg_info->page = शून्य;
		वापस शून्य;
	पूर्ण

	अगर ((अचिन्हित दीर्घ)skb->data & SKB_ADJ_MASK) अणु
		u32 r = SKB_ADJ - ((अचिन्हित दीर्घ)skb->data & SKB_ADJ_MASK);

		skb_reserve(skb, r);
	पूर्ण

	skb_pg_info = ((काष्ठा octeon_skb_page_info *)(skb->cb));
	/* Get DMA info */
	pg_info->dma = dma_map_page(&oct->pci_dev->dev, page, 0,
				    PAGE_SIZE, DMA_FROM_DEVICE);

	/* Mapping failed!! */
	अगर (dma_mapping_error(&oct->pci_dev->dev, pg_info->dma)) अणु
		__मुक्त_page(page);
		dev_kमुक्त_skb_any((काष्ठा sk_buff *)skb);
		pg_info->page = शून्य;
		वापस शून्य;
	पूर्ण

	pg_info->page = page;
	pg_info->page_offset = 0;
	skb_pg_info->page = page;
	skb_pg_info->page_offset = 0;
	skb_pg_info->dma = pg_info->dma;

	वापस (व्योम *)skb;
पूर्ण

अटल अंतरभूत व्योम
*recv_buffer_fast_alloc(u32 size)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा octeon_skb_page_info *skb_pg_info;

	skb = dev_alloc_skb(size + SKB_ADJ);
	अगर (unlikely(!skb))
		वापस शून्य;

	अगर ((अचिन्हित दीर्घ)skb->data & SKB_ADJ_MASK) अणु
		u32 r = SKB_ADJ - ((अचिन्हित दीर्घ)skb->data & SKB_ADJ_MASK);

		skb_reserve(skb, r);
	पूर्ण

	skb_pg_info = ((काष्ठा octeon_skb_page_info *)(skb->cb));
	skb_pg_info->page = शून्य;
	skb_pg_info->page_offset = 0;
	skb_pg_info->dma = 0;

	वापस skb;
पूर्ण

अटल अंतरभूत पूर्णांक
recv_buffer_recycle(काष्ठा octeon_device *oct, व्योम *buf)
अणु
	काष्ठा octeon_skb_page_info *pg_info = buf;

	अगर (!pg_info->page) अणु
		dev_err(&oct->pci_dev->dev, "%s: pg_info->page NULL\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	अगर (unlikely(page_count(pg_info->page) != 1) ||
	    unlikely(page_to_nid(pg_info->page)	!= numa_node_id())) अणु
		dma_unmap_page(&oct->pci_dev->dev,
			       pg_info->dma, (PAGE_SIZE << 0),
			       DMA_FROM_DEVICE);
		pg_info->dma = 0;
		pg_info->page = शून्य;
		pg_info->page_offset = 0;
		वापस -ENOMEM;
	पूर्ण

	/* Flip to other half of the buffer */
	अगर (pg_info->page_offset == 0)
		pg_info->page_offset = LIO_RXBUFFER_SZ;
	अन्यथा
		pg_info->page_offset = 0;
	page_ref_inc(pg_info->page);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
*recv_buffer_reuse(काष्ठा octeon_device *oct, व्योम *buf)
अणु
	काष्ठा octeon_skb_page_info *pg_info = buf, *skb_pg_info;
	काष्ठा sk_buff *skb;

	skb = dev_alloc_skb(MIN_SKB_SIZE + SKB_ADJ);
	अगर (unlikely(!skb)) अणु
		dma_unmap_page(&oct->pci_dev->dev,
			       pg_info->dma, (PAGE_SIZE << 0),
			       DMA_FROM_DEVICE);
		वापस शून्य;
	पूर्ण

	अगर ((अचिन्हित दीर्घ)skb->data & SKB_ADJ_MASK) अणु
		u32 r = SKB_ADJ - ((अचिन्हित दीर्घ)skb->data & SKB_ADJ_MASK);

		skb_reserve(skb, r);
	पूर्ण

	skb_pg_info = ((काष्ठा octeon_skb_page_info *)(skb->cb));
	skb_pg_info->page = pg_info->page;
	skb_pg_info->page_offset = pg_info->page_offset;
	skb_pg_info->dma = pg_info->dma;

	वापस skb;
पूर्ण

अटल अंतरभूत व्योम
recv_buffer_destroy(व्योम *buffer, काष्ठा octeon_skb_page_info *pg_info)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)buffer;

	put_page(pg_info->page);
	pg_info->dma = 0;
	pg_info->page = शून्य;
	pg_info->page_offset = 0;

	अगर (skb)
		dev_kमुक्त_skb_any(skb);
पूर्ण

अटल अंतरभूत व्योम recv_buffer_मुक्त(व्योम *buffer)
अणु
	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)buffer;
	काष्ठा octeon_skb_page_info *pg_info;

	pg_info = ((काष्ठा octeon_skb_page_info *)(skb->cb));

	अगर (pg_info->page) अणु
		put_page(pg_info->page);
		pg_info->dma = 0;
		pg_info->page = शून्य;
		pg_info->page_offset = 0;
	पूर्ण

	dev_kमुक्त_skb_any((काष्ठा sk_buff *)buffer);
पूर्ण

अटल अंतरभूत व्योम
recv_buffer_fast_मुक्त(व्योम *buffer)
अणु
	dev_kमुक्त_skb_any((काष्ठा sk_buff *)buffer);
पूर्ण

अटल अंतरभूत व्योम tx_buffer_मुक्त(व्योम *buffer)
अणु
	dev_kमुक्त_skb_any((काष्ठा sk_buff *)buffer);
पूर्ण

#घोषणा lio_dma_alloc(oct, size, dma_addr) \
	dma_alloc_coherent(&(oct)->pci_dev->dev, size, dma_addr, GFP_KERNEL)
#घोषणा lio_dma_मुक्त(oct, size, virt_addr, dma_addr) \
	dma_मुक्त_coherent(&(oct)->pci_dev->dev, size, virt_addr, dma_addr)

अटल अंतरभूत
व्योम *get_rbd(काष्ठा sk_buff *skb)
अणु
	काष्ठा octeon_skb_page_info *pg_info;
	अचिन्हित अक्षर *va;

	pg_info = ((काष्ठा octeon_skb_page_info *)(skb->cb));
	va = page_address(pg_info->page) + pg_info->page_offset;

	वापस va;
पूर्ण

अटल अंतरभूत u64
lio_map_ring(व्योम *buf)
अणु
	dma_addr_t dma_addr;

	काष्ठा sk_buff *skb = (काष्ठा sk_buff *)buf;
	काष्ठा octeon_skb_page_info *pg_info;

	pg_info = ((काष्ठा octeon_skb_page_info *)(skb->cb));
	अगर (!pg_info->page) अणु
		pr_err("%s: pg_info->page NULL\n", __func__);
		WARN_ON(1);
	पूर्ण

	/* Get DMA info */
	dma_addr = pg_info->dma;
	अगर (!pg_info->dma) अणु
		pr_err("%s: ERROR it should be already available\n",
		       __func__);
		WARN_ON(1);
	पूर्ण
	dma_addr += pg_info->page_offset;

	वापस (u64)dma_addr;
पूर्ण

अटल अंतरभूत व्योम
lio_unmap_ring(काष्ठा pci_dev *pci_dev,
	       u64 buf_ptr)

अणु
	dma_unmap_page(&pci_dev->dev,
		       buf_ptr, (PAGE_SIZE << 0),
		       DMA_FROM_DEVICE);
पूर्ण

अटल अंतरभूत व्योम *octeon_fast_packet_alloc(u32 size)
अणु
	वापस recv_buffer_fast_alloc(size);
पूर्ण

अटल अंतरभूत व्योम octeon_fast_packet_next(काष्ठा octeon_droq *droq,
					   काष्ठा sk_buff *nicbuf,
					   पूर्णांक copy_len,
					   पूर्णांक idx)
अणु
	skb_put_data(nicbuf, get_rbd(droq->recv_buf_list[idx].buffer),
		     copy_len);
पूर्ण

/**
 * \मrief check पूर्णांकerface state
 * @param lio per-network निजी data
 * @param state_flag flag state to check
 */
अटल अंतरभूत पूर्णांक अगरstate_check(काष्ठा lio *lio, पूर्णांक state_flag)
अणु
	वापस atomic_पढ़ो(&lio->अगरstate) & state_flag;
पूर्ण

/**
 * \मrief set पूर्णांकerface state
 * @param lio per-network निजी data
 * @param state_flag flag state to set
 */
अटल अंतरभूत व्योम अगरstate_set(काष्ठा lio *lio, पूर्णांक state_flag)
अणु
	atomic_set(&lio->अगरstate, (atomic_पढ़ो(&lio->अगरstate) | state_flag));
पूर्ण

/**
 * \मrief clear पूर्णांकerface state
 * @param lio per-network निजी data
 * @param state_flag flag state to clear
 */
अटल अंतरभूत व्योम अगरstate_reset(काष्ठा lio *lio, पूर्णांक state_flag)
अणु
	atomic_set(&lio->अगरstate, (atomic_पढ़ो(&lio->अगरstate) & ~(state_flag)));
पूर्ण

/**
 * \मrief रुको क्रम all pending requests to complete
 * @param oct Poपूर्णांकer to Octeon device
 *
 * Called during shutकरोwn sequence
 */
अटल अंतरभूत पूर्णांक रुको_क्रम_pending_requests(काष्ठा octeon_device *oct)
अणु
	पूर्णांक i, pcount = 0;

	क्रम (i = 0; i < MAX_IO_PENDING_PKT_COUNT; i++) अणु
		pcount = atomic_पढ़ो(
		    &oct->response_list[OCTEON_ORDERED_SC_LIST]
			 .pending_req_count);
		अगर (pcount)
			schedule_समयout_unपूर्णांकerruptible(HZ / 10);
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (pcount)
		वापस 1;

	वापस 0;
पूर्ण

/**
 * \मrief Stop Tx queues
 * @param netdev network device
 */
अटल अंतरभूत व्योम stop_txqs(काष्ठा net_device *netdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < netdev->real_num_tx_queues; i++)
		netअगर_stop_subqueue(netdev, i);
पूर्ण

/**
 * \मrief Wake Tx queues
 * @param netdev network device
 */
अटल अंतरभूत व्योम wake_txqs(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	पूर्णांक i, qno;

	क्रम (i = 0; i < netdev->real_num_tx_queues; i++) अणु
		qno = lio->linfo.txpciq[i % lio->oct_dev->num_iqs].s.q_no;

		अगर (__netअगर_subqueue_stopped(netdev, i)) अणु
			INCR_INSTRQUEUE_PKT_COUNT(lio->oct_dev, qno,
						  tx_restart, 1);
			netअगर_wake_subqueue(netdev, i);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * \मrief Start Tx queues
 * @param netdev network device
 */
अटल अंतरभूत व्योम start_txqs(काष्ठा net_device *netdev)
अणु
	काष्ठा lio *lio = GET_LIO(netdev);
	पूर्णांक i;

	अगर (lio->linfo.link.s.link_up) अणु
		क्रम (i = 0; i < netdev->real_num_tx_queues; i++)
			netअगर_start_subqueue(netdev, i);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक skb_iq(काष्ठा octeon_device *oct, काष्ठा sk_buff *skb)
अणु
	वापस skb->queue_mapping % oct->num_iqs;
पूर्ण

/**
 * Remove the node at the head of the list. The list would be empty at
 * the end of this call अगर there are no more nodes in the list.
 */
अटल अंतरभूत काष्ठा list_head *lio_list_delete_head(काष्ठा list_head *root)
अणु
	काष्ठा list_head *node;

	अगर (list_empty_careful(root))
		node = शून्य;
	अन्यथा
		node = root->next;

	अगर (node)
		list_del(node);

	वापस node;
पूर्ण

#पूर्ण_अगर
