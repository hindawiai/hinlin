<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009 - 2018 Intel Corporation. */

/* Linux PRO/1000 Ethernet Driver मुख्य header file */

#अगर_अघोषित _IGBVF_H_
#घोषणा _IGBVF_H_

#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_vlan.h>

#समावेश "vf.h"

/* Forward declarations */
काष्ठा igbvf_info;
काष्ठा igbvf_adapter;

/* Interrupt defines */
#घोषणा IGBVF_START_ITR		488 /* ~8000 पूर्णांकs/sec */
#घोषणा IGBVF_4K_ITR		980
#घोषणा IGBVF_20K_ITR		196
#घोषणा IGBVF_70K_ITR		56

क्रमागत latency_range अणु
	lowest_latency = 0,
	low_latency = 1,
	bulk_latency = 2,
	latency_invalid = 255
पूर्ण;

/* Interrupt modes, as used by the IntMode parameter */
#घोषणा IGBVF_INT_MODE_LEGACY	0
#घोषणा IGBVF_INT_MODE_MSI	1
#घोषणा IGBVF_INT_MODE_MSIX	2

/* Tx/Rx descriptor defines */
#घोषणा IGBVF_DEFAULT_TXD	256
#घोषणा IGBVF_MAX_TXD		4096
#घोषणा IGBVF_MIN_TXD		80

#घोषणा IGBVF_DEFAULT_RXD	256
#घोषणा IGBVF_MAX_RXD		4096
#घोषणा IGBVF_MIN_RXD		80

#घोषणा IGBVF_MIN_ITR_USECS	10 /* 100000 irq/sec */
#घोषणा IGBVF_MAX_ITR_USECS	10000 /* 100    irq/sec */

/* RX descriptor control thresholds.
 * PTHRESH - MAC will consider prefetch अगर it has fewer than this number of
 *	   descriptors available in its onboard memory.
 *	   Setting this to 0 disables RX descriptor prefetch.
 * HTHRESH - MAC will only prefetch अगर there are at least this many descriptors
 *	   available in host memory.
 *	   If PTHRESH is 0, this should also be 0.
 * WTHRESH - RX descriptor ग_लिखोback threshold - MAC will delay writing back
 *	   descriptors until either it has this many to ग_लिखो back, or the
 *	   ITR समयr expires.
 */
#घोषणा IGBVF_RX_PTHRESH	16
#घोषणा IGBVF_RX_HTHRESH	8
#घोषणा IGBVF_RX_WTHRESH	1

/* this is the size past which hardware will drop packets when setting LPE=0 */
#घोषणा MAXIMUM_ETHERNET_VLAN_SIZE	1522

#घोषणा IGBVF_FC_PAUSE_TIME	0x0680 /* 858 usec */

/* How many Tx Descriptors करो we need to call netअगर_wake_queue ? */
#घोषणा IGBVF_TX_QUEUE_WAKE	32
/* How many Rx Buffers करो we bundle पूर्णांकo one ग_लिखो to the hardware ? */
#घोषणा IGBVF_RX_BUFFER_WRITE	16 /* Must be घातer of 2 */

#घोषणा AUTO_ALL_MODES		0
#घोषणा IGBVF_EEPROM_APME	0x0400

#घोषणा IGBVF_MNG_VLAN_NONE	(-1)

#घोषणा IGBVF_MAX_MAC_FILTERS	3

/* Number of packet split data buffers (not including the header buffer) */
#घोषणा PS_PAGE_BUFFERS		(MAX_PS_BUFFERS - 1)

क्रमागत igbvf_boards अणु
	board_vf,
	board_i350_vf,
पूर्ण;

काष्ठा igbvf_queue_stats अणु
	u64 packets;
	u64 bytes;
पूर्ण;

/* wrappers around a poपूर्णांकer to a socket buffer,
 * so a DMA handle can be stored aदीर्घ with the buffer
 */
काष्ठा igbvf_buffer अणु
	dma_addr_t dma;
	काष्ठा sk_buff *skb;
	जोड़ अणु
		/* Tx */
		काष्ठा अणु
			अचिन्हित दीर्घ समय_stamp;
			जोड़ e1000_adv_tx_desc *next_to_watch;
			u16 length;
			u16 mapped_as_page;
		पूर्ण;
		/* Rx */
		काष्ठा अणु
			काष्ठा page *page;
			u64 page_dma;
			अचिन्हित पूर्णांक page_offset;
		पूर्ण;
	पूर्ण;
पूर्ण;

जोड़ igbvf_desc अणु
	जोड़ e1000_adv_rx_desc rx_desc;
	जोड़ e1000_adv_tx_desc tx_desc;
	काष्ठा e1000_adv_tx_context_desc tx_context_desc;
पूर्ण;

काष्ठा igbvf_ring अणु
	काष्ठा igbvf_adapter *adapter;  /* backlink */
	जोड़ igbvf_desc *desc;	/* poपूर्णांकer to ring memory  */
	dma_addr_t dma;		/* phys address of ring    */
	अचिन्हित पूर्णांक size;	/* length of ring in bytes */
	अचिन्हित पूर्णांक count;	/* number of desc. in ring */

	u16 next_to_use;
	u16 next_to_clean;

	u16 head;
	u16 tail;

	/* array of buffer inक्रमmation काष्ठाs */
	काष्ठा igbvf_buffer *buffer_info;
	काष्ठा napi_काष्ठा napi;

	अक्षर name[IFNAMSIZ + 5];
	u32 eims_value;
	u32 itr_val;
	क्रमागत latency_range itr_range;
	u16 itr_रेजिस्टर;
	पूर्णांक set_itr;

	काष्ठा sk_buff *rx_skb_top;

	काष्ठा igbvf_queue_stats stats;
पूर्ण;

/* board specअगरic निजी data काष्ठाure */
काष्ठा igbvf_adapter अणु
	काष्ठा समयr_list watchकरोg_समयr;
	काष्ठा समयr_list blink_समयr;

	काष्ठा work_काष्ठा reset_task;
	काष्ठा work_काष्ठा watchकरोg_task;

	स्थिर काष्ठा igbvf_info *ei;

	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	u32 bd_number;
	u32 rx_buffer_len;
	u32 polling_पूर्णांकerval;
	u16 mng_vlan_id;
	u16 link_speed;
	u16 link_duplex;

	spinlock_t tx_queue_lock; /* prevent concurrent tail updates */

	/* track device up/करोwn/testing state */
	अचिन्हित दीर्घ state;

	/* Interrupt Throttle Rate */
	u32 requested_itr; /* पूर्णांकs/sec or adaptive */
	u32 current_itr; /* Actual ITR रेजिस्टर value, not पूर्णांकs/sec */

	/* Tx */
	काष्ठा igbvf_ring *tx_ring /* One per active queue */
	____cacheline_aligned_in_smp;

	अचिन्हित पूर्णांक restart_queue;
	u32 txd_cmd;

	u32 tx_पूर्णांक_delay;
	u32 tx_असल_पूर्णांक_delay;

	अचिन्हित पूर्णांक total_tx_bytes;
	अचिन्हित पूर्णांक total_tx_packets;
	अचिन्हित पूर्णांक total_rx_bytes;
	अचिन्हित पूर्णांक total_rx_packets;

	/* Tx stats */
	u32 tx_समयout_count;
	u32 tx_fअगरo_head;
	u32 tx_head_addr;
	u32 tx_fअगरo_size;
	u32 tx_dma_failed;

	/* Rx */
	काष्ठा igbvf_ring *rx_ring;

	u32 rx_पूर्णांक_delay;
	u32 rx_असल_पूर्णांक_delay;

	/* Rx stats */
	u64 hw_csum_err;
	u64 hw_csum_good;
	u64 rx_hdr_split;
	u32 alloc_rx_buff_failed;
	u32 rx_dma_failed;

	अचिन्हित पूर्णांक rx_ps_hdr_size;
	u32 max_frame_size;
	u32 min_frame_size;

	/* OS defined काष्ठाs */
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;
	spinlock_t stats_lock; /* prevent concurrent stats updates */

	/* काष्ठाs defined in e1000_hw.h */
	काष्ठा e1000_hw hw;

	/* The VF counters करोn't clear on पढ़ो so we have to get a base
	 * count on driver start up and always subtract that base on
	 * on the first update, thus the flag..
	 */
	काष्ठा e1000_vf_stats stats;
	u64 zero_base;

	काष्ठा igbvf_ring test_tx_ring;
	काष्ठा igbvf_ring test_rx_ring;
	u32 test_icr;

	u32 msg_enable;
	काष्ठा msix_entry *msix_entries;
	पूर्णांक पूर्णांक_mode;
	u32 eims_enable_mask;
	u32 eims_other;
	u32 पूर्णांक_counter0;
	u32 पूर्णांक_counter1;

	u32 eeprom_wol;
	u32 wol;
	u32 pba;

	bool fc_स्वतःneg;

	अचिन्हित दीर्घ led_status;

	अचिन्हित पूर्णांक flags;
	अचिन्हित दीर्घ last_reset;
पूर्ण;

काष्ठा igbvf_info अणु
	क्रमागत e1000_mac_type	mac;
	अचिन्हित पूर्णांक		flags;
	u32			pba;
	व्योम			(*init_ops)(काष्ठा e1000_hw *);
	s32			(*get_variants)(काष्ठा igbvf_adapter *);
पूर्ण;

/* hardware capability, feature, and workaround flags */
#घोषणा IGBVF_FLAG_RX_CSUM_DISABLED	BIT(0)
#घोषणा IGBVF_FLAG_RX_LB_VLAN_BSWAP	BIT(1)
#घोषणा IGBVF_RX_DESC_ADV(R, i)     \
	(&((((R).desc))[i].rx_desc))
#घोषणा IGBVF_TX_DESC_ADV(R, i)     \
	(&((((R).desc))[i].tx_desc))
#घोषणा IGBVF_TX_CTXTDESC_ADV(R, i) \
	(&((((R).desc))[i].tx_context_desc))

क्रमागत igbvf_state_t अणु
	__IGBVF_TESTING,
	__IGBVF_RESETTING,
	__IGBVF_DOWN
पूर्ण;

बाह्य अक्षर igbvf_driver_name[];

व्योम igbvf_check_options(काष्ठा igbvf_adapter *);
व्योम igbvf_set_ethtool_ops(काष्ठा net_device *);

पूर्णांक igbvf_up(काष्ठा igbvf_adapter *);
व्योम igbvf_करोwn(काष्ठा igbvf_adapter *);
व्योम igbvf_reinit_locked(काष्ठा igbvf_adapter *);
पूर्णांक igbvf_setup_rx_resources(काष्ठा igbvf_adapter *, काष्ठा igbvf_ring *);
पूर्णांक igbvf_setup_tx_resources(काष्ठा igbvf_adapter *, काष्ठा igbvf_ring *);
व्योम igbvf_मुक्त_rx_resources(काष्ठा igbvf_ring *);
व्योम igbvf_मुक्त_tx_resources(काष्ठा igbvf_ring *);
व्योम igbvf_update_stats(काष्ठा igbvf_adapter *);

बाह्य अचिन्हित पूर्णांक copyअवरोध;

#पूर्ण_अगर /* _IGBVF_H_ */
