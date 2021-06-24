<शैली गुरु>
/*
 * Linux driver क्रम VMware's vmxnet3 ethernet NIC.
 *
 * Copyright (C) 2008-2020, VMware, Inc. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; version 2 of the License and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA.
 *
 * The full GNU General Public License is included in this distribution in
 * the file called "COPYING".
 *
 * Maपूर्णांकained by: pv-drivers@vmware.com
 *
 */

#अगर_अघोषित _VMXNET3_INT_H
#घोषणा _VMXNET3_INT_H

#समावेश <linux/bitops.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/compiler.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/ioport.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/समयr.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/page.h>

#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/in.h>
#समावेश <linux/etherdevice.h>
#समावेश <यंत्र/checksum.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/log2.h>

#समावेश "vmxnet3_defs.h"

#अगर_घोषित DEBUG
# define VMXNET3_DRIVER_VERSION_REPORT VMXNET3_DRIVER_VERSION_STRING"-NAPI(debug)"
#अन्यथा
# define VMXNET3_DRIVER_VERSION_REPORT VMXNET3_DRIVER_VERSION_STRING"-NAPI"
#पूर्ण_अगर


/*
 * Version numbers
 */
#घोषणा VMXNET3_DRIVER_VERSION_STRING   "1.5.0.0-k"

/* Each byte of this 32-bit पूर्णांकeger encodes a version number in
 * VMXNET3_DRIVER_VERSION_STRING.
 */
#घोषणा VMXNET3_DRIVER_VERSION_NUM      0x01050000

#अगर defined(CONFIG_PCI_MSI)
	/* RSS only makes sense अगर MSI-X is supported. */
	#घोषणा VMXNET3_RSS
#पूर्ण_अगर

#घोषणा VMXNET3_REV_4		3	/* Vmxnet3 Rev. 4 */
#घोषणा VMXNET3_REV_3		2	/* Vmxnet3 Rev. 3 */
#घोषणा VMXNET3_REV_2		1	/* Vmxnet3 Rev. 2 */
#घोषणा VMXNET3_REV_1		0	/* Vmxnet3 Rev. 1 */

/*
 * Capabilities
 */

क्रमागत अणु
	VMNET_CAP_SG	        = 0x0001, /* Can करो scatter-gather transmits. */
	VMNET_CAP_IP4_CSUM      = 0x0002, /* Can checksum only TCP/UDP over
					   * IPv4 */
	VMNET_CAP_HW_CSUM       = 0x0004, /* Can checksum all packets. */
	VMNET_CAP_HIGH_DMA      = 0x0008, /* Can DMA to high memory. */
	VMNET_CAP_TOE	        = 0x0010, /* Supports TCP/IP offload. */
	VMNET_CAP_TSO	        = 0x0020, /* Supports TCP Segmentation
					   * offload */
	VMNET_CAP_SW_TSO        = 0x0040, /* Supports SW TCP Segmentation */
	VMNET_CAP_VMXNET_APROM  = 0x0080, /* Vmxnet APROM support */
	VMNET_CAP_HW_TX_VLAN    = 0x0100, /* Can we करो VLAN tagging in HW */
	VMNET_CAP_HW_RX_VLAN    = 0x0200, /* Can we करो VLAN untagging in HW */
	VMNET_CAP_SW_VLAN       = 0x0400, /* VLAN tagging/untagging in SW */
	VMNET_CAP_WAKE_PCKT_RCV = 0x0800, /* Can wake on network packet recv? */
	VMNET_CAP_ENABLE_INT_INLINE = 0x1000,  /* Enable Interrupt Inline */
	VMNET_CAP_ENABLE_HEADER_COPY = 0x2000,  /* copy header क्रम vmkernel */
	VMNET_CAP_TX_CHAIN      = 0x4000, /* Guest can use multiple tx entries
					  * क्रम a pkt */
	VMNET_CAP_RX_CHAIN      = 0x8000, /* pkt can span multiple rx entries */
	VMNET_CAP_LPD           = 0x10000, /* large pkt delivery */
	VMNET_CAP_BPF           = 0x20000, /* BPF Support in VMXNET Virtual HW*/
	VMNET_CAP_SG_SPAN_PAGES = 0x40000, /* Scatter-gather can span multiple*/
					   /* pages transmits */
	VMNET_CAP_IP6_CSUM      = 0x80000, /* Can करो IPv6 csum offload. */
	VMNET_CAP_TSO6         = 0x100000, /* TSO seg. offload क्रम IPv6 pkts. */
	VMNET_CAP_TSO256k      = 0x200000, /* Can करो TSO seg offload क्रम */
					   /* pkts up to 256kB. */
	VMNET_CAP_UPT          = 0x400000  /* Support UPT */
पूर्ण;

/*
 * Maximum devices supported.
 */
#घोषणा MAX_ETHERNET_CARDS		10
#घोषणा MAX_PCI_PASSTHRU_DEVICE		6

काष्ठा vmxnet3_cmd_ring अणु
	जोड़ Vmxnet3_GenericDesc *base;
	u32		size;
	u32		next2fill;
	u32		next2comp;
	u8		gen;
	dma_addr_t	basePA;
पूर्ण;

अटल अंतरभूत व्योम
vmxnet3_cmd_ring_adv_next2fill(काष्ठा vmxnet3_cmd_ring *ring)
अणु
	ring->next2fill++;
	अगर (unlikely(ring->next2fill == ring->size)) अणु
		ring->next2fill = 0;
		VMXNET3_FLIP_RING_GEN(ring->gen);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
vmxnet3_cmd_ring_adv_next2comp(काष्ठा vmxnet3_cmd_ring *ring)
अणु
	VMXNET3_INC_RING_IDX_ONLY(ring->next2comp, ring->size);
पूर्ण

अटल अंतरभूत पूर्णांक
vmxnet3_cmd_ring_desc_avail(काष्ठा vmxnet3_cmd_ring *ring)
अणु
	वापस (ring->next2comp > ring->next2fill ? 0 : ring->size) +
		ring->next2comp - ring->next2fill - 1;
पूर्ण

काष्ठा vmxnet3_comp_ring अणु
	जोड़ Vmxnet3_GenericDesc *base;
	u32               size;
	u32               next2proc;
	u8                gen;
	u8                पूर्णांकr_idx;
	dma_addr_t           basePA;
पूर्ण;

अटल अंतरभूत व्योम
vmxnet3_comp_ring_adv_next2proc(काष्ठा vmxnet3_comp_ring *ring)
अणु
	ring->next2proc++;
	अगर (unlikely(ring->next2proc == ring->size)) अणु
		ring->next2proc = 0;
		VMXNET3_FLIP_RING_GEN(ring->gen);
	पूर्ण
पूर्ण

काष्ठा vmxnet3_tx_data_ring अणु
	काष्ठा Vmxnet3_TxDataDesc *base;
	u32              size;
	dma_addr_t          basePA;
पूर्ण;

क्रमागत vmxnet3_buf_map_type अणु
	VMXNET3_MAP_INVALID = 0,
	VMXNET3_MAP_NONE,
	VMXNET3_MAP_SINGLE,
	VMXNET3_MAP_PAGE,
पूर्ण;

काष्ठा vmxnet3_tx_buf_info अणु
	u32      map_type;
	u16      len;
	u16      sop_idx;
	dma_addr_t  dma_addr;
	काष्ठा sk_buff *skb;
पूर्ण;

काष्ठा vmxnet3_tq_driver_stats अणु
	u64 drop_total;     /* # of pkts dropped by the driver, the
				* counters below track droppings due to
				* dअगरferent reasons
				*/
	u64 drop_too_many_frags;
	u64 drop_oversized_hdr;
	u64 drop_hdr_inspect_err;
	u64 drop_tso;

	u64 tx_ring_full;
	u64 linearized;         /* # of pkts linearized */
	u64 copy_skb_header;    /* # of बार we have to copy skb header */
	u64 oversized_hdr;
पूर्ण;

काष्ठा vmxnet3_tx_ctx अणु
	bool   ipv4;
	bool   ipv6;
	u16 mss;
	u32    l4_offset;	/* only valid क्रम pkts requesting tso or csum
				 * offloading. For encap offload, it refers to
				 * inner L4 offset i.e. it includes outer header
				 * encap header and inner eth and ip header size
				 */

	u32	l4_hdr_size;	/* only valid अगर mss != 0
				 * Refers to inner L4 hdr size क्रम encap
				 * offload
				 */
	u32 copy_size;       /* # of bytes copied पूर्णांकo the data ring */
	जोड़ Vmxnet3_GenericDesc *sop_txd;
	जोड़ Vmxnet3_GenericDesc *eop_txd;
पूर्ण;

काष्ठा vmxnet3_tx_queue अणु
	अक्षर			name[IFNAMSIZ+8]; /* To identअगरy पूर्णांकerrupt */
	काष्ठा vmxnet3_adapter		*adapter;
	spinlock_t                      tx_lock;
	काष्ठा vmxnet3_cmd_ring         tx_ring;
	काष्ठा vmxnet3_tx_buf_info      *buf_info;
	काष्ठा vmxnet3_tx_data_ring     data_ring;
	काष्ठा vmxnet3_comp_ring        comp_ring;
	काष्ठा Vmxnet3_TxQueueCtrl      *shared;
	काष्ठा vmxnet3_tq_driver_stats  stats;
	bool                            stopped;
	पूर्णांक                             num_stop;  /* # of बार the queue is
						    * stopped */
	पूर्णांक				qid;
	u16				txdata_desc_size;
पूर्ण __attribute__((__aligned__(SMP_CACHE_BYTES)));

क्रमागत vmxnet3_rx_buf_type अणु
	VMXNET3_RX_BUF_NONE = 0,
	VMXNET3_RX_BUF_SKB = 1,
	VMXNET3_RX_BUF_PAGE = 2
पूर्ण;

काष्ठा vmxnet3_rx_buf_info अणु
	क्रमागत vmxnet3_rx_buf_type buf_type;
	u16     len;
	जोड़ अणु
		काष्ठा sk_buff *skb;
		काष्ठा page    *page;
	पूर्ण;
	dma_addr_t dma_addr;
पूर्ण;

काष्ठा vmxnet3_rx_ctx अणु
	काष्ठा sk_buff *skb;
	u32 sop_idx;
पूर्ण;

काष्ठा vmxnet3_rq_driver_stats अणु
	u64 drop_total;
	u64 drop_err;
	u64 drop_fcs;
	u64 rx_buf_alloc_failure;
पूर्ण;

काष्ठा vmxnet3_rx_data_ring अणु
	Vmxnet3_RxDataDesc *base;
	dma_addr_t basePA;
	u16 desc_size;
पूर्ण;

काष्ठा vmxnet3_rx_queue अणु
	अक्षर			name[IFNAMSIZ + 8]; /* To identअगरy पूर्णांकerrupt */
	काष्ठा vmxnet3_adapter	  *adapter;
	काष्ठा napi_काष्ठा        napi;
	काष्ठा vmxnet3_cmd_ring   rx_ring[2];
	काष्ठा vmxnet3_rx_data_ring data_ring;
	काष्ठा vmxnet3_comp_ring  comp_ring;
	काष्ठा vmxnet3_rx_ctx     rx_ctx;
	u32 qid;            /* rqID in RCD क्रम buffer from 1st ring */
	u32 qid2;           /* rqID in RCD क्रम buffer from 2nd ring */
	u32 dataRingQid;    /* rqID in RCD क्रम buffer from data ring */
	काष्ठा vmxnet3_rx_buf_info     *buf_info[2];
	काष्ठा Vmxnet3_RxQueueCtrl            *shared;
	काष्ठा vmxnet3_rq_driver_stats  stats;
पूर्ण __attribute__((__aligned__(SMP_CACHE_BYTES)));

#घोषणा VMXNET3_DEVICE_MAX_TX_QUEUES 8
#घोषणा VMXNET3_DEVICE_MAX_RX_QUEUES 8   /* Keep this value as a घातer of 2 */

/* Should be less than UPT1_RSS_MAX_IND_TABLE_SIZE */
#घोषणा VMXNET3_RSS_IND_TABLE_SIZE (VMXNET3_DEVICE_MAX_RX_QUEUES * 4)

#घोषणा VMXNET3_LINUX_MAX_MSIX_VECT     (VMXNET3_DEVICE_MAX_TX_QUEUES + \
					 VMXNET3_DEVICE_MAX_RX_QUEUES + 1)
#घोषणा VMXNET3_LINUX_MIN_MSIX_VECT     2 /* 1 क्रम tx-rx pair and 1 क्रम event */


काष्ठा vmxnet3_पूर्णांकr अणु
	क्रमागत vmxnet3_पूर्णांकr_mask_mode  mask_mode;
	क्रमागत vmxnet3_पूर्णांकr_type       type;	/* MSI-X, MSI, or INTx? */
	u8  num_पूर्णांकrs;			/* # of पूर्णांकr vectors */
	u8  event_पूर्णांकr_idx;		/* idx of the पूर्णांकr vector क्रम event */
	u8  mod_levels[VMXNET3_LINUX_MAX_MSIX_VECT]; /* moderation level */
	अक्षर	event_msi_vector_name[IFNAMSIZ+17];
#अगर_घोषित CONFIG_PCI_MSI
	काष्ठा msix_entry msix_entries[VMXNET3_LINUX_MAX_MSIX_VECT];
#पूर्ण_अगर
पूर्ण;

/* Interrupt sharing schemes, share_पूर्णांकr */
#घोषणा VMXNET3_INTR_BUDDYSHARE 0    /* Corresponding tx,rx queues share irq */
#घोषणा VMXNET3_INTR_TXSHARE 1	     /* All tx queues share one irq */
#घोषणा VMXNET3_INTR_DONTSHARE 2     /* each queue has its own irq */


#घोषणा VMXNET3_STATE_BIT_RESETTING   0
#घोषणा VMXNET3_STATE_BIT_QUIESCED    1
काष्ठा vmxnet3_adapter अणु
	काष्ठा vmxnet3_tx_queue		tx_queue[VMXNET3_DEVICE_MAX_TX_QUEUES];
	काष्ठा vmxnet3_rx_queue		rx_queue[VMXNET3_DEVICE_MAX_RX_QUEUES];
	अचिन्हित दीर्घ			active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	काष्ठा vmxnet3_पूर्णांकr		पूर्णांकr;
	spinlock_t			cmd_lock;
	काष्ठा Vmxnet3_DriverShared	*shared;
	काष्ठा Vmxnet3_PMConf		*pm_conf;
	काष्ठा Vmxnet3_TxQueueDesc	*tqd_start;     /* all tx queue desc */
	काष्ठा Vmxnet3_RxQueueDesc	*rqd_start;	/* all rx queue desc */
	काष्ठा net_device		*netdev;
	काष्ठा pci_dev			*pdev;

	u8			__iomem *hw_addr0; /* क्रम BAR 0 */
	u8			__iomem *hw_addr1; /* क्रम BAR 1 */
	u8                              version;

#अगर_घोषित VMXNET3_RSS
	काष्ठा UPT1_RSSConf		*rss_conf;
	bool				rss;
#पूर्ण_अगर
	u32				num_rx_queues;
	u32				num_tx_queues;

	/* rx buffer related */
	अचिन्हित			skb_buf_size;
	पूर्णांक		rx_buf_per_pkt;  /* only apply to the 1st ring */
	dma_addr_t			shared_pa;
	dma_addr_t queue_desc_pa;
	dma_addr_t coal_conf_pa;

	/* Wake-on-LAN */
	u32     wol;

	/* Link speed */
	u32     link_speed; /* in mbps */

	u64     tx_समयout_count;

	/* Ring sizes */
	u32 tx_ring_size;
	u32 rx_ring_size;
	u32 rx_ring2_size;

	/* Size of buffer in the data ring */
	u16 txdata_desc_size;
	u16 rxdata_desc_size;

	bool rxdataring_enabled;
	bool शेष_rss_fields;
	क्रमागत Vmxnet3_RSSField rss_fields;

	काष्ठा work_काष्ठा work;

	अचिन्हित दीर्घ  state;    /* VMXNET3_STATE_BIT_xxx */

	पूर्णांक share_पूर्णांकr;

	काष्ठा Vmxnet3_CoalesceScheme *coal_conf;
	bool   शेष_coal_mode;

	dma_addr_t adapter_pa;
	dma_addr_t pm_conf_pa;
	dma_addr_t rss_conf_pa;
पूर्ण;

#घोषणा VMXNET3_WRITE_BAR0_REG(adapter, reg, val)  \
	ग_लिखोl((val), (adapter)->hw_addr0 + (reg))
#घोषणा VMXNET3_READ_BAR0_REG(adapter, reg)        \
	पढ़ोl((adapter)->hw_addr0 + (reg))

#घोषणा VMXNET3_WRITE_BAR1_REG(adapter, reg, val)  \
	ग_लिखोl((val), (adapter)->hw_addr1 + (reg))
#घोषणा VMXNET3_READ_BAR1_REG(adapter, reg)        \
	पढ़ोl((adapter)->hw_addr1 + (reg))

#घोषणा VMXNET3_WAKE_QUEUE_THRESHOLD(tq)  (5)
#घोषणा VMXNET3_RX_ALLOC_THRESHOLD(rq, ring_idx, adapter) \
	((rq)->rx_ring[ring_idx].size >> 3)

#घोषणा VMXNET3_GET_ADDR_LO(dma)   ((u32)(dma))
#घोषणा VMXNET3_GET_ADDR_HI(dma)   ((u32)(((u64)(dma)) >> 32))

#घोषणा VMXNET3_VERSION_GE_2(adapter) \
	(adapter->version >= VMXNET3_REV_2 + 1)
#घोषणा VMXNET3_VERSION_GE_3(adapter) \
	(adapter->version >= VMXNET3_REV_3 + 1)
#घोषणा VMXNET3_VERSION_GE_4(adapter) \
	(adapter->version >= VMXNET3_REV_4 + 1)

/* must be a multiple of VMXNET3_RING_SIZE_ALIGN */
#घोषणा VMXNET3_DEF_TX_RING_SIZE    512
#घोषणा VMXNET3_DEF_RX_RING_SIZE    1024
#घोषणा VMXNET3_DEF_RX_RING2_SIZE   256

#घोषणा VMXNET3_DEF_RXDATA_DESC_SIZE 128

#घोषणा VMXNET3_MAX_ETH_HDR_SIZE    22
#घोषणा VMXNET3_MAX_SKB_BUF_SIZE    (3*1024)

#घोषणा VMXNET3_GET_RING_IDX(adapter, rqID)		\
	((rqID >= adapter->num_rx_queues &&		\
	 rqID < 2 * adapter->num_rx_queues) ? 1 : 0)	\

#घोषणा VMXNET3_RX_DATA_RING(adapter, rqID)		\
	(rqID >= 2 * adapter->num_rx_queues &&		\
	rqID < 3 * adapter->num_rx_queues)		\

#घोषणा VMXNET3_COAL_STATIC_DEFAULT_DEPTH	64

#घोषणा VMXNET3_COAL_RBC_RATE(usecs) (1000000 / usecs)
#घोषणा VMXNET3_COAL_RBC_USECS(rbc_rate) (1000000 / rbc_rate)
#घोषणा VMXNET3_RSS_FIELDS_DEFAULT (VMXNET3_RSS_FIELDS_TCPIP4 | \
				    VMXNET3_RSS_FIELDS_TCPIP6)

पूर्णांक
vmxnet3_quiesce_dev(काष्ठा vmxnet3_adapter *adapter);

पूर्णांक
vmxnet3_activate_dev(काष्ठा vmxnet3_adapter *adapter);

व्योम
vmxnet3_क्रमce_बंद(काष्ठा vmxnet3_adapter *adapter);

व्योम
vmxnet3_reset_dev(काष्ठा vmxnet3_adapter *adapter);

व्योम
vmxnet3_tq_destroy_all(काष्ठा vmxnet3_adapter *adapter);

व्योम
vmxnet3_rq_destroy_all(काष्ठा vmxnet3_adapter *adapter);

netdev_features_t
vmxnet3_fix_features(काष्ठा net_device *netdev, netdev_features_t features);

netdev_features_t
vmxnet3_features_check(काष्ठा sk_buff *skb,
		       काष्ठा net_device *netdev, netdev_features_t features);

पूर्णांक
vmxnet3_set_features(काष्ठा net_device *netdev, netdev_features_t features);

पूर्णांक
vmxnet3_create_queues(काष्ठा vmxnet3_adapter *adapter,
		      u32 tx_ring_size, u32 rx_ring_size, u32 rx_ring2_size,
		      u16 txdata_desc_size, u16 rxdata_desc_size);

व्योम vmxnet3_set_ethtool_ops(काष्ठा net_device *netdev);

व्योम vmxnet3_get_stats64(काष्ठा net_device *dev,
			 काष्ठा rtnl_link_stats64 *stats);

बाह्य अक्षर vmxnet3_driver_name[];
#पूर्ण_अगर
