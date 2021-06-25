<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2019 Intel Corporation. */

#अगर_अघोषित _FM10K_H_
#घोषणा _FM10K_H_

#समावेश <linux/types.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/pci.h>

#समावेश "fm10k_pf.h"
#समावेश "fm10k_vf.h"

#घोषणा FM10K_MAX_JUMBO_FRAME_SIZE	15342	/* Maximum supported size 15K */

#घोषणा MAX_QUEUES	FM10K_MAX_QUEUES_PF

#घोषणा FM10K_MIN_RXD		 128
#घोषणा FM10K_MAX_RXD		4096
#घोषणा FM10K_DEFAULT_RXD	 256

#घोषणा FM10K_MIN_TXD		 128
#घोषणा FM10K_MAX_TXD		4096
#घोषणा FM10K_DEFAULT_TXD	 256
#घोषणा FM10K_DEFAULT_TX_WORK	 256

#घोषणा FM10K_RXBUFFER_256	  256
#घोषणा FM10K_RX_HDR_LEN	FM10K_RXBUFFER_256
#घोषणा FM10K_RXBUFFER_2048	 2048
#घोषणा FM10K_RX_BUFSZ		FM10K_RXBUFFER_2048

/* How many Rx Buffers करो we bundle पूर्णांकo one ग_लिखो to the hardware ? */
#घोषणा FM10K_RX_BUFFER_WRITE	16	/* Must be घातer of 2 */

#घोषणा FM10K_MAX_STATIONS	63
काष्ठा fm10k_l2_accel अणु
	पूर्णांक size;
	u16 count;
	u16 dglort;
	काष्ठा rcu_head rcu;
	काष्ठा net_device *macvlan[];
पूर्ण;

क्रमागत fm10k_ring_state_t अणु
	__FM10K_TX_DETECT_HANG,
	__FM10K_HANG_CHECK_ARMED,
	__FM10K_TX_XPS_INIT_DONE,
	/* This must be last and is used to calculate BITMAP size */
	__FM10K_TX_STATE_SIZE__,
पूर्ण;

#घोषणा check_क्रम_tx_hang(ring) \
	test_bit(__FM10K_TX_DETECT_HANG, (ring)->state)
#घोषणा set_check_क्रम_tx_hang(ring) \
	set_bit(__FM10K_TX_DETECT_HANG, (ring)->state)
#घोषणा clear_check_क्रम_tx_hang(ring) \
	clear_bit(__FM10K_TX_DETECT_HANG, (ring)->state)

काष्ठा fm10k_tx_buffer अणु
	काष्ठा fm10k_tx_desc *next_to_watch;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक bytecount;
	u16 gso_segs;
	u16 tx_flags;
	DEFINE_DMA_UNMAP_ADDR(dma);
	DEFINE_DMA_UNMAP_LEN(len);
पूर्ण;

काष्ठा fm10k_rx_buffer अणु
	dma_addr_t dma;
	काष्ठा page *page;
	u32 page_offset;
पूर्ण;

काष्ठा fm10k_queue_stats अणु
	u64 packets;
	u64 bytes;
पूर्ण;

काष्ठा fm10k_tx_queue_stats अणु
	u64 restart_queue;
	u64 csum_err;
	u64 tx_busy;
	u64 tx_करोne_old;
	u64 csum_good;
पूर्ण;

काष्ठा fm10k_rx_queue_stats अणु
	u64 alloc_failed;
	u64 csum_err;
	u64 errors;
	u64 csum_good;
	u64 चयन_errors;
	u64 drops;
	u64 pp_errors;
	u64 link_errors;
	u64 length_errors;
पूर्ण;

काष्ठा fm10k_ring अणु
	काष्ठा fm10k_q_vector *q_vector;/* backpoपूर्णांकer to host q_vector */
	काष्ठा net_device *netdev;	/* netdev ring beदीर्घs to */
	काष्ठा device *dev;		/* device क्रम DMA mapping */
	काष्ठा fm10k_l2_accel __rcu *l2_accel;	/* L2 acceleration list */
	व्योम *desc;			/* descriptor ring memory */
	जोड़ अणु
		काष्ठा fm10k_tx_buffer *tx_buffer;
		काष्ठा fm10k_rx_buffer *rx_buffer;
	पूर्ण;
	u32 __iomem *tail;
	DECLARE_BITMAP(state, __FM10K_TX_STATE_SIZE__);
	dma_addr_t dma;			/* phys. address of descriptor ring */
	अचिन्हित पूर्णांक size;		/* length in bytes */

	u8 queue_index;			/* needed क्रम queue management */
	u8 reg_idx;			/* holds the special value that माला_लो
					 * the hardware रेजिस्टर offset
					 * associated with this ring, which is
					 * dअगरferent क्रम DCB and RSS modes
					 */
	u8 qos_pc;			/* priority class of queue */
	u16 vid;			/* शेष VLAN ID of queue */
	u16 count;			/* amount of descriptors */

	u16 next_to_alloc;
	u16 next_to_use;
	u16 next_to_clean;

	काष्ठा fm10k_queue_stats stats;
	काष्ठा u64_stats_sync syncp;
	जोड़ अणु
		/* Tx */
		काष्ठा fm10k_tx_queue_stats tx_stats;
		/* Rx */
		काष्ठा अणु
			काष्ठा fm10k_rx_queue_stats rx_stats;
			काष्ठा sk_buff *skb;
		पूर्ण;
	पूर्ण;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

काष्ठा fm10k_ring_container अणु
	काष्ठा fm10k_ring *ring;	/* poपूर्णांकer to linked list of rings */
	अचिन्हित पूर्णांक total_bytes;	/* total bytes processed this पूर्णांक */
	अचिन्हित पूर्णांक total_packets;	/* total packets processed this पूर्णांक */
	u16 work_limit;			/* total work allowed per पूर्णांकerrupt */
	u16 itr;			/* पूर्णांकerrupt throttle rate value */
	u8 itr_scale;			/* ITR adjusपंचांगent based on PCI speed */
	u8 count;			/* total number of rings in vector */
पूर्ण;

#घोषणा FM10K_ITR_MAX		0x0FFF	/* maximum value क्रम ITR */
#घोषणा FM10K_ITR_10K		100	/* 100us */
#घोषणा FM10K_ITR_20K		50	/* 50us */
#घोषणा FM10K_ITR_40K		25	/* 25us */
#घोषणा FM10K_ITR_ADAPTIVE	0x8000	/* adaptive पूर्णांकerrupt moderation flag */

#घोषणा ITR_IS_ADAPTIVE(itr) (!!(itr & FM10K_ITR_ADAPTIVE))

#घोषणा FM10K_TX_ITR_DEFAULT	FM10K_ITR_40K
#घोषणा FM10K_RX_ITR_DEFAULT	FM10K_ITR_20K
#घोषणा FM10K_ITR_ENABLE	(FM10K_ITR_AUTOMASK | FM10K_ITR_MASK_CLEAR)

अटल अंतरभूत काष्ठा netdev_queue *txring_txq(स्थिर काष्ठा fm10k_ring *ring)
अणु
	वापस &ring->netdev->_tx[ring->queue_index];
पूर्ण

/* iterator क्रम handling rings in ring container */
#घोषणा fm10k_क्रम_each_ring(pos, head) \
	क्रम (pos = &(head).ring[(head).count]; (--pos) >= (head).ring;)

#घोषणा MAX_Q_VECTORS 256
#घोषणा MIN_Q_VECTORS	1
क्रमागत fm10k_non_q_vectors अणु
	FM10K_MBX_VECTOR,
	NON_Q_VECTORS
पूर्ण;

#घोषणा MIN_MSIX_COUNT(hw)	(MIN_Q_VECTORS + NON_Q_VECTORS)

काष्ठा fm10k_q_vector अणु
	काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface;
	u32 __iomem *itr;	/* poपूर्णांकer to ITR रेजिस्टर क्रम this vector */
	u16 v_idx;		/* index of q_vector within पूर्णांकerface array */
	काष्ठा fm10k_ring_container rx, tx;

	काष्ठा napi_काष्ठा napi;
	cpumask_t affinity_mask;
	अक्षर name[IFNAMSIZ + 9];

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dbg_q_vector;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
	काष्ठा rcu_head rcu;	/* to aव्योम race with update stats on मुक्त */

	/* क्रम dynamic allocation of rings associated with this q_vector */
	काष्ठा fm10k_ring ring[] ____cacheline_पूर्णांकernodealigned_in_smp;
पूर्ण;

क्रमागत fm10k_ring_f_क्रमागत अणु
	RING_F_RSS,
	RING_F_QOS,
	RING_F_ARRAY_SIZE  /* must be last in क्रमागत set */
पूर्ण;

काष्ठा fm10k_ring_feature अणु
	u16 limit;	/* upper limit on feature indices */
	u16 indices;	/* current value of indices */
	u16 mask;	/* Mask used क्रम feature to ring mapping */
	u16 offset;	/* offset to start of feature */
पूर्ण;

काष्ठा fm10k_iov_data अणु
	अचिन्हित पूर्णांक		num_vfs;
	अचिन्हित पूर्णांक		next_vf_mbx;
	काष्ठा rcu_head		rcu;
	काष्ठा fm10k_vf_info	vf_info[];
पूर्ण;

क्रमागत fm10k_macvlan_request_type अणु
	FM10K_UC_MAC_REQUEST,
	FM10K_MC_MAC_REQUEST,
	FM10K_VLAN_REQUEST
पूर्ण;

काष्ठा fm10k_macvlan_request अणु
	क्रमागत fm10k_macvlan_request_type type;
	काष्ठा list_head list;
	जोड़ अणु
		काष्ठा fm10k_mac_request अणु
			u8 addr[ETH_ALEN];
			u16 glort;
			u16 vid;
		पूर्ण mac;
		काष्ठा fm10k_vlan_request अणु
			u32 vid;
			u8 vsi;
		पूर्ण vlan;
	पूर्ण;
	bool set;
पूर्ण;

/* one work queue क्रम entire driver */
बाह्य काष्ठा workqueue_काष्ठा *fm10k_workqueue;

/* The following क्रमागतeration contains flags which indicate or enable modअगरied
 * driver behaviors. To aव्योम race conditions, the flags are stored in
 * a BITMAP in the fm10k_पूर्णांकfc काष्ठाure. The BITMAP should be accessed using
 * atomic *_bit() operations.
 */
क्रमागत fm10k_flags_t अणु
	FM10K_FLAG_RESET_REQUESTED,
	FM10K_FLAG_RSS_FIELD_IPV4_UDP,
	FM10K_FLAG_RSS_FIELD_IPV6_UDP,
	FM10K_FLAG_SWPRI_CONFIG,
	/* __FM10K_FLAGS_SIZE__ is used to calculate the size of
	 * पूर्णांकerface->flags and must be the last value in this
	 * क्रमागतeration.
	 */
	__FM10K_FLAGS_SIZE__
पूर्ण;

क्रमागत fm10k_state_t अणु
	__FM10K_RESETTING,
	__FM10K_RESET_DETACHED,
	__FM10K_RESET_SUSPENDED,
	__FM10K_DOWN,
	__FM10K_SERVICE_SCHED,
	__FM10K_SERVICE_REQUEST,
	__FM10K_SERVICE_DISABLE,
	__FM10K_MACVLAN_SCHED,
	__FM10K_MACVLAN_REQUEST,
	__FM10K_MACVLAN_DISABLE,
	__FM10K_LINK_DOWN,
	__FM10K_UPDATING_STATS,
	/* This value must be last and determines the BITMAP size */
	__FM10K_STATE_SIZE__,
पूर्ण;

काष्ठा fm10k_पूर्णांकfc अणु
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	काष्ठा net_device *netdev;
	काष्ठा fm10k_l2_accel *l2_accel; /* poपूर्णांकer to L2 acceleration list */
	काष्ठा pci_dev *pdev;
	DECLARE_BITMAP(state, __FM10K_STATE_SIZE__);

	/* Access flag values using atomic *_bit() operations */
	DECLARE_BITMAP(flags, __FM10K_FLAGS_SIZE__);

	पूर्णांक xcast_mode;

	/* Tx fast path data */
	पूर्णांक num_tx_queues;
	u16 tx_itr;

	/* Rx fast path data */
	पूर्णांक num_rx_queues;
	u16 rx_itr;

	/* TX */
	काष्ठा fm10k_ring *tx_ring[MAX_QUEUES] ____cacheline_aligned_in_smp;

	u64 restart_queue;
	u64 tx_busy;
	u64 tx_csum_errors;
	u64 alloc_failed;
	u64 rx_csum_errors;

	u64 tx_bytes_nic;
	u64 tx_packets_nic;
	u64 rx_bytes_nic;
	u64 rx_packets_nic;
	u64 rx_drops_nic;
	u64 rx_overrun_pf;
	u64 rx_overrun_vf;

	/* Debug Statistics */
	u64 hw_sm_mbx_full;
	u64 hw_csum_tx_good;
	u64 hw_csum_rx_good;
	u64 rx_चयन_errors;
	u64 rx_drops;
	u64 rx_pp_errors;
	u64 rx_link_errors;
	u64 rx_length_errors;

	u32 tx_समयout_count;

	/* RX */
	काष्ठा fm10k_ring *rx_ring[MAX_QUEUES];

	/* Queueing vectors */
	काष्ठा fm10k_q_vector *q_vector[MAX_Q_VECTORS];
	काष्ठा msix_entry *msix_entries;
	पूर्णांक num_q_vectors;	/* current number of q_vectors क्रम device */
	काष्ठा fm10k_ring_feature ring_feature[RING_F_ARRAY_SIZE];

	/* SR-IOV inक्रमmation management काष्ठाure */
	काष्ठा fm10k_iov_data *iov_data;

	काष्ठा fm10k_hw_stats stats;
	काष्ठा fm10k_hw hw;
	/* Mailbox lock */
	spinlock_t mbx_lock;
	u32 __iomem *uc_addr;
	u32 __iomem *sw_addr;
	u16 msg_enable;
	u16 tx_ring_count;
	u16 rx_ring_count;
	काष्ठा समयr_list service_समयr;
	काष्ठा work_काष्ठा service_task;
	अचिन्हित दीर्घ next_stats_update;
	अचिन्हित दीर्घ next_tx_hang_check;
	अचिन्हित दीर्घ last_reset;
	अचिन्हित दीर्घ link_करोwn_event;
	bool host_पढ़ोy;
	bool lport_map_failed;

	u32 reta[FM10K_RETA_SIZE];
	u32 rssrk[FM10K_RSSRK_SIZE];

	/* UDP encapsulation port tracking inक्रमmation */
	__be16 vxlan_port;
	__be16 geneve_port;

	/* MAC/VLAN update queue */
	काष्ठा list_head macvlan_requests;
	काष्ठा delayed_work macvlan_task;
	/* MAC/VLAN update queue lock */
	spinlock_t macvlan_lock;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *dbg_पूर्णांकfc;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

#अगर_घोषित CONFIG_DCB
	u8 pfc_en;
#पूर्ण_अगर
	u8 rx_छोड़ो;

	/* GLORT resources in use by PF */
	u16 glort;
	u16 glort_count;

	/* VLAN ID क्रम updating multicast/unicast lists */
	u16 vid;
पूर्ण;

अटल अंतरभूत व्योम fm10k_mbx_lock(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	spin_lock(&पूर्णांकerface->mbx_lock);
पूर्ण

अटल अंतरभूत व्योम fm10k_mbx_unlock(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	spin_unlock(&पूर्णांकerface->mbx_lock);
पूर्ण

अटल अंतरभूत पूर्णांक fm10k_mbx_trylock(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface)
अणु
	वापस spin_trylock(&पूर्णांकerface->mbx_lock);
पूर्ण

/* fm10k_test_staterr - test bits in Rx descriptor status and error fields */
अटल अंतरभूत __le32 fm10k_test_staterr(जोड़ fm10k_rx_desc *rx_desc,
					स्थिर u32 stat_err_bits)
अणु
	वापस rx_desc->d.staterr & cpu_to_le32(stat_err_bits);
पूर्ण

/* fm10k_desc_unused - calculate अगर we have unused descriptors */
अटल अंतरभूत u16 fm10k_desc_unused(काष्ठा fm10k_ring *ring)
अणु
	s16 unused = ring->next_to_clean - ring->next_to_use - 1;

	वापस likely(unused < 0) ? unused + ring->count : unused;
पूर्ण

#घोषणा FM10K_TX_DESC(R, i)	\
	(&(((काष्ठा fm10k_tx_desc *)((R)->desc))[i]))
#घोषणा FM10K_RX_DESC(R, i)	\
	 (&(((जोड़ fm10k_rx_desc *)((R)->desc))[i]))

#घोषणा FM10K_MAX_TXD_PWR	14
#घोषणा FM10K_MAX_DATA_PER_TXD	(1u << FM10K_MAX_TXD_PWR)

/* Tx Descriptors needed, worst हाल */
#घोषणा TXD_USE_COUNT(S)	DIV_ROUND_UP((S), FM10K_MAX_DATA_PER_TXD)
#घोषणा DESC_NEEDED	(MAX_SKB_FRAGS + 4)

क्रमागत fm10k_tx_flags अणु
	/* Tx offload flags */
	FM10K_TX_FLAGS_CSUM	= 0x01,
पूर्ण;

/* This काष्ठाure is stored as little endian values as that is the native
 * क्रमmat of the Rx descriptor.  The ordering of these fields is reversed
 * from the actual ftag header to allow क्रम a single bswap to take care
 * of placing all of the values in network order
 */
जोड़ fm10k_ftag_info अणु
	__le64 ftag;
	काष्ठा अणु
		/* dglort and sglort combined पूर्णांकo a single 32bit desc पढ़ो */
		__le32 glort;
		/* upper 16 bits of VLAN are reserved 0 क्रम swpri_type_user */
		__le32 vlan;
	पूर्ण d;
	काष्ठा अणु
		__le16 dglort;
		__le16 sglort;
		__le16 vlan;
		__le16 swpri_type_user;
	पूर्ण w;
पूर्ण;

काष्ठा fm10k_cb अणु
	जोड़ अणु
		__le64 tstamp;
		अचिन्हित दीर्घ ts_tx_समयout;
	पूर्ण;
	जोड़ fm10k_ftag_info fi;
पूर्ण;

#घोषणा FM10K_CB(skb) ((काष्ठा fm10k_cb *)(skb)->cb)

/* मुख्य */
बाह्य अक्षर fm10k_driver_name[];
पूर्णांक fm10k_init_queueing_scheme(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
व्योम fm10k_clear_queueing_scheme(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
__be16 fm10k_tx_encap_offload(काष्ठा sk_buff *skb);
netdev_tx_t fm10k_xmit_frame_ring(काष्ठा sk_buff *skb,
				  काष्ठा fm10k_ring *tx_ring);
व्योम fm10k_tx_समयout_reset(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
u64 fm10k_get_tx_pending(काष्ठा fm10k_ring *ring, bool in_sw);
bool fm10k_check_tx_hang(काष्ठा fm10k_ring *tx_ring);
व्योम fm10k_alloc_rx_buffers(काष्ठा fm10k_ring *rx_ring, u16 cleaned_count);

/* PCI */
व्योम fm10k_mbx_मुक्त_irq(काष्ठा fm10k_पूर्णांकfc *);
पूर्णांक fm10k_mbx_request_irq(काष्ठा fm10k_पूर्णांकfc *);
व्योम fm10k_qv_मुक्त_irq(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
पूर्णांक fm10k_qv_request_irq(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
पूर्णांक fm10k_रेजिस्टर_pci_driver(व्योम);
व्योम fm10k_unरेजिस्टर_pci_driver(व्योम);
व्योम fm10k_up(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
व्योम fm10k_करोwn(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
व्योम fm10k_update_stats(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
व्योम fm10k_service_event_schedule(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
व्योम fm10k_macvlan_schedule(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
व्योम fm10k_update_rx_drop_en(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);

/* Netdev */
काष्ठा net_device *fm10k_alloc_netdev(स्थिर काष्ठा fm10k_info *info);
पूर्णांक fm10k_setup_rx_resources(काष्ठा fm10k_ring *);
पूर्णांक fm10k_setup_tx_resources(काष्ठा fm10k_ring *);
व्योम fm10k_मुक्त_rx_resources(काष्ठा fm10k_ring *);
व्योम fm10k_मुक्त_tx_resources(काष्ठा fm10k_ring *);
व्योम fm10k_clean_all_rx_rings(काष्ठा fm10k_पूर्णांकfc *);
व्योम fm10k_clean_all_tx_rings(काष्ठा fm10k_पूर्णांकfc *);
व्योम fm10k_unmap_and_मुक्त_tx_resource(काष्ठा fm10k_ring *,
				      काष्ठा fm10k_tx_buffer *);
व्योम fm10k_restore_rx_state(काष्ठा fm10k_पूर्णांकfc *);
व्योम fm10k_reset_rx_state(काष्ठा fm10k_पूर्णांकfc *);
पूर्णांक fm10k_setup_tc(काष्ठा net_device *dev, u8 tc);
पूर्णांक fm10k_खोलो(काष्ठा net_device *netdev);
पूर्णांक fm10k_बंद(काष्ठा net_device *netdev);
पूर्णांक fm10k_queue_vlan_request(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface, u32 vid,
			     u8 vsi, bool set);
पूर्णांक fm10k_queue_mac_request(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface, u16 glort,
			    स्थिर अचिन्हित अक्षर *addr, u16 vid, bool set);
व्योम fm10k_clear_macvlan_queue(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface,
			       u16 glort, bool vlans);

/* Ethtool */
व्योम fm10k_set_ethtool_ops(काष्ठा net_device *dev);
व्योम fm10k_ग_लिखो_reta(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface, स्थिर u32 *indir);

/* IOV */
s32 fm10k_iov_event(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
s32 fm10k_iov_mbx(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
व्योम fm10k_iov_suspend(काष्ठा pci_dev *pdev);
पूर्णांक fm10k_iov_resume(काष्ठा pci_dev *pdev);
व्योम fm10k_iov_disable(काष्ठा pci_dev *pdev);
पूर्णांक fm10k_iov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs);
व्योम fm10k_iov_update_stats(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
s32 fm10k_iov_update_pvid(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface, u16 glort, u16 pvid);
पूर्णांक fm10k_nकरो_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf_idx, u8 *mac);
पूर्णांक fm10k_nकरो_set_vf_vlan(काष्ठा net_device *netdev,
			  पूर्णांक vf_idx, u16 vid, u8 qos, __be16 vlan_proto);
पूर्णांक fm10k_nकरो_set_vf_bw(काष्ठा net_device *netdev, पूर्णांक vf_idx,
			पूर्णांक __always_unused min_rate, पूर्णांक max_rate);
पूर्णांक fm10k_nकरो_get_vf_config(काष्ठा net_device *netdev,
			    पूर्णांक vf_idx, काष्ठा अगरla_vf_info *ivi);
पूर्णांक fm10k_nकरो_get_vf_stats(काष्ठा net_device *netdev,
			   पूर्णांक vf_idx, काष्ठा अगरla_vf_stats *stats);

/* DebugFS */
#अगर_घोषित CONFIG_DEBUG_FS
व्योम fm10k_dbg_q_vector_init(काष्ठा fm10k_q_vector *q_vector);
व्योम fm10k_dbg_q_vector_निकास(काष्ठा fm10k_q_vector *q_vector);
व्योम fm10k_dbg_पूर्णांकfc_init(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
व्योम fm10k_dbg_पूर्णांकfc_निकास(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface);
व्योम fm10k_dbg_init(व्योम);
व्योम fm10k_dbg_निकास(व्योम);
#अन्यथा
अटल अंतरभूत व्योम fm10k_dbg_q_vector_init(काष्ठा fm10k_q_vector *q_vector) अणुपूर्ण
अटल अंतरभूत व्योम fm10k_dbg_q_vector_निकास(काष्ठा fm10k_q_vector *q_vector) अणुपूर्ण
अटल अंतरभूत व्योम fm10k_dbg_पूर्णांकfc_init(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface) अणुपूर्ण
अटल अंतरभूत व्योम fm10k_dbg_पूर्णांकfc_निकास(काष्ठा fm10k_पूर्णांकfc *पूर्णांकerface) अणुपूर्ण
अटल अंतरभूत व्योम fm10k_dbg_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम fm10k_dbg_निकास(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

/* DCB */
#अगर_घोषित CONFIG_DCB
व्योम fm10k_dcbnl_set_ops(काष्ठा net_device *dev);
#अन्यथा
अटल अंतरभूत व्योम fm10k_dcbnl_set_ops(काष्ठा net_device *dev) अणुपूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _FM10K_H_ */
