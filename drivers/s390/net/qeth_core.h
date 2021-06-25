<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Copyright IBM Corp. 2007
 *    Author(s): Utz Bacher <utz.bacher@de.ibm.com>,
 *		 Frank Pavlic <fpavlic@de.ibm.com>,
 *		 Thomas Spatzier <tspat@de.ibm.com>,
 *		 Frank Blaschka <frank.blaschka@de.ibm.com>
 */

#अगर_अघोषित __QETH_CORE_H__
#घोषणा __QETH_CORE_H__

#समावेश <linux/completion.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/in6.h>
#समावेश <linux/bitops.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/ip.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/refcount.h>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>

#समावेश <net/dst.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/ipv6.h>
#समावेश <net/अगर_inet6.h>
#समावेश <net/addrconf.h>
#समावेश <net/route.h>
#समावेश <net/sch_generic.h>
#समावेश <net/tcp.h>

#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/qdपन.स>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/ccwgroup.h>
#समावेश <यंत्र/sysinfo.h>

#समावेश <uapi/linux/अगर_link.h>

#समावेश "qeth_core_mpc.h"

/**
 * Debug Facility stuff
 */
क्रमागत qeth_dbf_names अणु
	QETH_DBF_SETUP,
	QETH_DBF_MSG,
	QETH_DBF_CTRL,
	QETH_DBF_INFOS	/* must be last element */
पूर्ण;

काष्ठा qeth_dbf_info अणु
	अक्षर name[DEBUG_MAX_NAME_LEN];
	पूर्णांक pages;
	पूर्णांक areas;
	पूर्णांक len;
	पूर्णांक level;
	काष्ठा debug_view *view;
	debug_info_t *id;
पूर्ण;

#घोषणा QETH_DBF_CTRL_LEN 256U

#घोषणा QETH_DBF_TEXT(name, level, text) \
	debug_text_event(qeth_dbf[QETH_DBF_##name].id, level, text)

#घोषणा QETH_DBF_HEX(name, level, addr, len) \
	debug_event(qeth_dbf[QETH_DBF_##name].id, level, (व्योम *)(addr), len)

#घोषणा QETH_DBF_MESSAGE(level, text...) \
	debug_प्र_लिखो_event(qeth_dbf[QETH_DBF_MSG].id, level, text)

#घोषणा QETH_DBF_TEXT_(name, level, text...) \
	qeth_dbf_दीर्घtext(qeth_dbf[QETH_DBF_##name].id, level, text)

#घोषणा QETH_CARD_TEXT(card, level, text) \
	debug_text_event(card->debug, level, text)

#घोषणा QETH_CARD_HEX(card, level, addr, len) \
	debug_event(card->debug, level, (व्योम *)(addr), len)

#घोषणा QETH_CARD_MESSAGE(card, text...) \
	debug_प्र_लिखो_event(card->debug, level, text)

#घोषणा QETH_CARD_TEXT_(card, level, text...) \
	qeth_dbf_दीर्घtext(card->debug, level, text)

#घोषणा SENSE_COMMAND_REJECT_BYTE 0
#घोषणा SENSE_COMMAND_REJECT_FLAG 0x80
#घोषणा SENSE_RESETTING_EVENT_BYTE 1
#घोषणा SENSE_RESETTING_EVENT_FLAG 0x80

अटल अंतरभूत u32 qeth_get_device_id(काष्ठा ccw_device *cdev)
अणु
	काष्ठा ccw_dev_id dev_id;
	u32 id;

	ccw_device_get_id(cdev, &dev_id);
	id = dev_id.devno;
	id |= (u32) (dev_id.ssid << 16);

	वापस id;
पूर्ण

/*
 * Common IO related definitions
 */
#घोषणा CARD_RDEV(card) card->पढ़ो.ccwdev
#घोषणा CARD_WDEV(card) card->ग_लिखो.ccwdev
#घोषणा CARD_DDEV(card) card->data.ccwdev
#घोषणा CARD_BUS_ID(card) dev_name(&card->gdev->dev)
#घोषणा CARD_RDEV_ID(card) dev_name(&card->पढ़ो.ccwdev->dev)
#घोषणा CARD_WDEV_ID(card) dev_name(&card->ग_लिखो.ccwdev->dev)
#घोषणा CARD_DDEV_ID(card) dev_name(&card->data.ccwdev->dev)
#घोषणा CCW_DEVID(cdev)		(qeth_get_device_id(cdev))
#घोषणा CARD_DEVID(card)	(CCW_DEVID(CARD_RDEV(card)))

/* Routing stuff */
काष्ठा qeth_routing_info अणु
	क्रमागत qeth_routing_types type;
पूर्ण;

/* SETBRIDGEPORT stuff */
क्रमागत qeth_sbp_roles अणु
	QETH_SBP_ROLE_NONE	= 0,
	QETH_SBP_ROLE_PRIMARY	= 1,
	QETH_SBP_ROLE_SECONDARY	= 2,
पूर्ण;

क्रमागत qeth_sbp_states अणु
	QETH_SBP_STATE_INACTIVE	= 0,
	QETH_SBP_STATE_STANDBY	= 1,
	QETH_SBP_STATE_ACTIVE	= 2,
पूर्ण;

#घोषणा QETH_SBP_HOST_NOTIFICATION 1

काष्ठा qeth_sbp_info अणु
	__u32 supported_funcs;
	क्रमागत qeth_sbp_roles role;
	__u32 hostnotअगरication:1;
	__u32 reflect_promisc:1;
	__u32 reflect_promisc_primary:1;
पूर्ण;

काष्ठा qeth_vnicc_info अणु
	/* supported/currently configured VNICCs; updated in IPA exchanges */
	u32 sup_अक्षरs;
	u32 cur_अक्षरs;
	/* supported commands: biपंचांगasks which VNICCs support respective cmd */
	u32 set_अक्षर_sup;
	u32 माला_लोet_समयout_sup;
	/* समयout value क्रम the learning अक्षरacteristic */
	u32 learning_समयout;
	/* अक्षरacteristics wanted/configured by user */
	u32 wanted_अक्षरs;
	/* has user explicitly enabled rx_bcast जबतक online? */
	bool rx_bcast_enabled;
पूर्ण;

#घोषणा QETH_IDX_FUNC_LEVEL_OSD		 0x0101
#घोषणा QETH_IDX_FUNC_LEVEL_IQD		 0x4108

#घोषणा QETH_बफ_मानE		4096
#घोषणा CCW_CMD_WRITE		0x01
#घोषणा CCW_CMD_READ		0x02

/**
 * some more defs
 */
#घोषणा QETH_TX_TIMEOUT		(100 * HZ)
#घोषणा QETH_RCD_TIMEOUT	(60 * HZ)
#घोषणा QETH_RECLAIM_WORK_TIME	HZ
#घोषणा QETH_MAX_PORTNO		15

/*****************************************************************************/
/* QDIO queue and buffer handling                                            */
/*****************************************************************************/
#घोषणा QETH_MAX_OUT_QUEUES	4
#घोषणा QETH_IQD_MIN_TXQ	2	/* One क्रम ucast, one क्रम mcast. */
#घोषणा QETH_IQD_MCAST_TXQ	0
#घोषणा QETH_IQD_MIN_UCAST_TXQ	1

#घोषणा QETH_MAX_IN_QUEUES	2
#घोषणा QETH_RX_COPYBREAK      (PAGE_SIZE >> 1)
#घोषणा QETH_IN_BUF_SIZE_DEFAULT 65536
#घोषणा QETH_IN_BUF_COUNT_DEFAULT 64
#घोषणा QETH_IN_BUF_COUNT_HSDEFAULT 128
#घोषणा QETH_IN_BUF_COUNT_MIN	8U
#घोषणा QETH_IN_BUF_COUNT_MAX	128U
#घोषणा QETH_MAX_BUFFER_ELEMENTS(card) ((card)->qdio.in_buf_size >> 12)
#घोषणा QETH_IN_BUF_REQUEUE_THRESHOLD(card) \
		 ((card)->qdio.in_buf_pool.buf_count / 2)

/* buffers we have to be behind beक्रमe we get a PCI */
#घोषणा QETH_PCI_THRESHOLD_A(card) ((card)->qdio.in_buf_pool.buf_count+1)
/*enqueued मुक्त buffers left beक्रमe we get a PCI*/
#घोषणा QETH_PCI_THRESHOLD_B(card) 0
/*not used unless the microcode माला_लो patched*/
#घोषणा QETH_PCI_TIMER_VALUE(card) 3

/* priority queing */
#घोषणा QETH_PRIOQ_DEFAULT QETH_NO_PRIO_QUEUEING
#घोषणा QETH_DEFAULT_QUEUE    2
#घोषणा QETH_NO_PRIO_QUEUEING 0
#घोषणा QETH_PRIO_Q_ING_PREC  1
#घोषणा QETH_PRIO_Q_ING_TOS   2
#घोषणा QETH_PRIO_Q_ING_SKB   3
#घोषणा QETH_PRIO_Q_ING_VLAN  4
#घोषणा QETH_PRIO_Q_ING_FIXED 5

/* Packing */
#घोषणा QETH_LOW_WATERMARK_PACK  2
#घोषणा QETH_HIGH_WATERMARK_PACK 5
#घोषणा QETH_WATERMARK_PACK_FUZZ 1

काष्ठा qeth_hdr_layer3 अणु
	__u8  id;
	__u8  flags;
	__u16 inbound_checksum; /*TSO:__u16 seqno */
	__u32 token;		/*TSO: __u32 reserved */
	__u16 length;
	__u8  vlan_prio;
	__u8  ext_flags;
	__u16 vlan_id;
	__u16 frame_offset;
	जोड़ अणु
		/* TX: */
		काष्ठा in6_addr addr;
		/* RX: */
		काष्ठा rx अणु
			u8 res1[2];
			u8 src_mac[6];
			u8 res2[4];
			u16 vlan_id;
			u8 res3[2];
		पूर्ण rx;
	पूर्ण next_hop;
पूर्ण;

काष्ठा qeth_hdr_layer2 अणु
	__u8 id;
	__u8 flags[3];
	__u8 port_no;
	__u8 hdr_length;
	__u16 pkt_length;
	__u16 seq_no;
	__u16 vlan_id;
	__u32 reserved;
	__u8 reserved2[16];
पूर्ण __attribute__ ((packed));

काष्ठा qeth_hdr_osn अणु
	__u8 id;
	__u8 reserved;
	__u16 seq_no;
	__u16 reserved2;
	__u16 control_flags;
	__u16 pdu_length;
	__u8 reserved3[18];
	__u32 ccid;
पूर्ण __attribute__ ((packed));

काष्ठा qeth_hdr अणु
	जोड़ अणु
		काष्ठा qeth_hdr_layer2 l2;
		काष्ठा qeth_hdr_layer3 l3;
		काष्ठा qeth_hdr_osn    osn;
	पूर्ण hdr;
पूर्ण __attribute__ ((packed));

#घोषणा QETH_QIB_PQUE_ORDER_RR		0
#घोषणा QETH_QIB_PQUE_UNITS_SBAL	2
#घोषणा QETH_QIB_PQUE_PRIO_DEFAULT	4

काष्ठा qeth_qib_parms अणु
	अक्षर pcit_magic[4];
	u32 pcit_a;
	u32 pcit_b;
	u32 pcit_c;
	अक्षर blkt_magic[4];
	u32 blkt_total;
	u32 blkt_पूर्णांकer_packet;
	u32 blkt_पूर्णांकer_packet_jumbo;
	अक्षर pque_magic[4];
	u8 pque_order;
	u8 pque_units;
	u16 reserved;
	u32 pque_priority[4];
पूर्ण;

/*TCP Segmentation Offload header*/
काष्ठा qeth_hdr_ext_tso अणु
	__u16 hdr_tot_len;
	__u8  imb_hdr_no;
	__u8  reserved;
	__u8  hdr_type;
	__u8  hdr_version;
	__u16 hdr_len;
	__u32 payload_len;
	__u16 mss;
	__u16 dg_hdr_len;
	__u8  padding[16];
पूर्ण __attribute__ ((packed));

काष्ठा qeth_hdr_tso अणु
	काष्ठा qeth_hdr hdr;	/*hdr->hdr.l3.xxx*/
	काष्ठा qeth_hdr_ext_tso ext;
पूर्ण __attribute__ ((packed));


/* flags क्रम qeth_hdr.flags */
#घोषणा QETH_HDR_PASSTHRU 0x10
#घोषणा QETH_HDR_IPV6     0x80
#घोषणा QETH_HDR_CAST_MASK 0x07
क्रमागत qeth_cast_flags अणु
	QETH_CAST_UNICAST   = 0x06,
	QETH_CAST_MULTICAST = 0x04,
	QETH_CAST_BROADCAST = 0x05,
	QETH_CAST_ANYCAST   = 0x07,
	QETH_CAST_NOCAST    = 0x00,
पूर्ण;

क्रमागत qeth_layer2_frame_flags अणु
	QETH_LAYER2_FLAG_MULTICAST = 0x01,
	QETH_LAYER2_FLAG_BROADCAST = 0x02,
	QETH_LAYER2_FLAG_UNICAST   = 0x04,
	QETH_LAYER2_FLAG_VLAN      = 0x10,
पूर्ण;

क्रमागत qeth_header_ids अणु
	QETH_HEADER_TYPE_LAYER3 = 0x01,
	QETH_HEADER_TYPE_LAYER2 = 0x02,
	QETH_HEADER_TYPE_L3_TSO	= 0x03,
	QETH_HEADER_TYPE_OSN    = 0x04,
	QETH_HEADER_TYPE_L2_TSO	= 0x06,
	QETH_HEADER_MASK_INVAL	= 0x80,
पूर्ण;
/* flags क्रम qeth_hdr.ext_flags */
#घोषणा QETH_HDR_EXT_VLAN_FRAME       0x01
#घोषणा QETH_HDR_EXT_TOKEN_ID         0x02
#घोषणा QETH_HDR_EXT_INCLUDE_VLAN_TAG 0x04
#घोषणा QETH_HDR_EXT_SRC_MAC_ADDR     0x08
#घोषणा QETH_HDR_EXT_CSUM_HDR_REQ     0x10
#घोषणा QETH_HDR_EXT_CSUM_TRANSP_REQ  0x20
#घोषणा QETH_HDR_EXT_UDP	      0x40 /*bit off क्रम TCP*/

अटल अंतरभूत bool qeth_l2_same_vlan(काष्ठा qeth_hdr_layer2 *h1,
				     काष्ठा qeth_hdr_layer2 *h2)
अणु
	वापस !((h1->flags[2] ^ h2->flags[2]) & QETH_LAYER2_FLAG_VLAN) &&
	       h1->vlan_id == h2->vlan_id;
पूर्ण

अटल अंतरभूत bool qeth_l3_iqd_same_vlan(काष्ठा qeth_hdr_layer3 *h1,
					 काष्ठा qeth_hdr_layer3 *h2)
अणु
	वापस !((h1->ext_flags ^ h2->ext_flags) & QETH_HDR_EXT_VLAN_FRAME) &&
	       h1->vlan_id == h2->vlan_id;
पूर्ण

अटल अंतरभूत bool qeth_l3_same_next_hop(काष्ठा qeth_hdr_layer3 *h1,
					 काष्ठा qeth_hdr_layer3 *h2)
अणु
	वापस !((h1->flags ^ h2->flags) & QETH_HDR_IPV6) &&
	       ipv6_addr_equal(&h1->next_hop.addr, &h2->next_hop.addr);
पूर्ण

काष्ठा qeth_local_addr अणु
	काष्ठा hlist_node hnode;
	काष्ठा rcu_head rcu;
	काष्ठा in6_addr addr;
पूर्ण;

क्रमागत qeth_qdio_info_states अणु
	QETH_QDIO_UNINITIALIZED,
	QETH_QDIO_ALLOCATED,
	QETH_QDIO_ESTABLISHED,
	QETH_QDIO_CLEANING
पूर्ण;

काष्ठा qeth_buffer_pool_entry अणु
	काष्ठा list_head list;
	काष्ठा list_head init_list;
	काष्ठा page *elements[QDIO_MAX_ELEMENTS_PER_BUFFER];
पूर्ण;

काष्ठा qeth_qdio_buffer_pool अणु
	काष्ठा list_head entry_list;
	पूर्णांक buf_count;
पूर्ण;

काष्ठा qeth_qdio_buffer अणु
	काष्ठा qdio_buffer *buffer;
	/* the buffer pool entry currently associated to this buffer */
	काष्ठा qeth_buffer_pool_entry *pool_entry;
	काष्ठा sk_buff *rx_skb;
पूर्ण;

काष्ठा qeth_qdio_q अणु
	काष्ठा qdio_buffer *qdio_bufs[QDIO_MAX_BUFFERS_PER_Q];
	काष्ठा qeth_qdio_buffer bufs[QDIO_MAX_BUFFERS_PER_Q];
	पूर्णांक next_buf_to_init;
पूर्ण;

क्रमागत qeth_qdio_out_buffer_state अणु
	/* Owned by driver, in order to be filled. */
	QETH_QDIO_BUF_EMPTY,
	/* Filled by driver; owned by hardware in order to be sent. */
	QETH_QDIO_BUF_PRIMED,
	/* Discovered by the TX completion code: */
	QETH_QDIO_BUF_PENDING,
	/* Finished by the TX completion code: */
	QETH_QDIO_BUF_NEED_QAOB,
	/* Received QAOB notअगरication on CQ: */
	QETH_QDIO_BUF_QAOB_OK,
	QETH_QDIO_BUF_QAOB_ERROR,
पूर्ण;

काष्ठा qeth_qdio_out_buffer अणु
	काष्ठा qdio_buffer *buffer;
	atomic_t state;
	पूर्णांक next_element_to_fill;
	अचिन्हित पूर्णांक frames;
	अचिन्हित पूर्णांक bytes;
	काष्ठा sk_buff_head skb_list;
	पूर्णांक is_header[QDIO_MAX_ELEMENTS_PER_BUFFER];

	काष्ठा qeth_qdio_out_q *q;
	काष्ठा list_head list_entry;
	काष्ठा qaob *aob;
पूर्ण;

काष्ठा qeth_card;

#घोषणा QETH_CARD_STAT_ADD(_c, _stat, _val)	((_c)->stats._stat += (_val))
#घोषणा QETH_CARD_STAT_INC(_c, _stat)		QETH_CARD_STAT_ADD(_c, _stat, 1)

#घोषणा QETH_TXQ_STAT_ADD(_q, _stat, _val)	((_q)->stats._stat += (_val))
#घोषणा QETH_TXQ_STAT_INC(_q, _stat)		QETH_TXQ_STAT_ADD(_q, _stat, 1)

काष्ठा qeth_card_stats अणु
	u64 rx_bufs;
	u64 rx_skb_csum;
	u64 rx_sg_skbs;
	u64 rx_sg_frags;
	u64 rx_sg_alloc_page;

	u64 rx_dropped_nomem;
	u64 rx_dropped_notsupp;
	u64 rx_dropped_runt;

	/* rtnl_link_stats64 */
	u64 rx_packets;
	u64 rx_bytes;
	u64 rx_multicast;
	u64 rx_length_errors;
	u64 rx_frame_errors;
	u64 rx_fअगरo_errors;
पूर्ण;

काष्ठा qeth_out_q_stats अणु
	u64 bufs;
	u64 bufs_pack;
	u64 buf_elements;
	u64 skbs_pack;
	u64 skbs_sg;
	u64 skbs_csum;
	u64 skbs_tso;
	u64 skbs_linearized;
	u64 skbs_linearized_fail;
	u64 tso_bytes;
	u64 packing_mode_चयन;
	u64 stopped;
	u64 करोorbell;
	u64 coal_frames;
	u64 completion_yield;
	u64 completion_समयr;

	/* rtnl_link_stats64 */
	u64 tx_packets;
	u64 tx_bytes;
	u64 tx_errors;
	u64 tx_dropped;
पूर्ण;

#घोषणा QETH_TX_MAX_COALESCED_FRAMES	1
#घोषणा QETH_TX_COALESCE_USECS		25
#घोषणा QETH_TX_TIMER_USECS		500

काष्ठा qeth_qdio_out_q अणु
	काष्ठा qdio_buffer *qdio_bufs[QDIO_MAX_BUFFERS_PER_Q];
	काष्ठा qeth_qdio_out_buffer *bufs[QDIO_MAX_BUFFERS_PER_Q];
	काष्ठा list_head pending_bufs;
	काष्ठा qeth_out_q_stats stats;
	spinlock_t lock;
	अचिन्हित पूर्णांक priority;
	u8 next_buf_to_fill;
	u8 max_elements;
	u8 queue_no;
	u8 करो_pack;
	काष्ठा qeth_card *card;
	/*
	 * number of buffers that are currently filled (PRIMED)
	 * -> these buffers are hardware-owned
	 */
	atomic_t used_buffers;
	/* indicates whether PCI flag must be set (or अगर one is outstanding) */
	atomic_t set_pci_flags_count;
	काष्ठा napi_काष्ठा napi;
	काष्ठा समयr_list समयr;
	काष्ठा qeth_hdr *prev_hdr;
	अचिन्हित पूर्णांक coalesced_frames;
	u8 bulk_start;
	u8 bulk_count;
	u8 bulk_max;

	अचिन्हित पूर्णांक coalesce_usecs;
	अचिन्हित पूर्णांक max_coalesced_frames;
पूर्ण;

#घोषणा qeth_क्रम_each_output_queue(card, q, i)		\
	क्रम (i = 0; i < card->qdio.no_out_queues &&	\
		    (q = card->qdio.out_qs[i]); i++)

#घोषणा	qeth_napi_to_out_queue(n) container_of(n, काष्ठा qeth_qdio_out_q, napi)

अटल अंतरभूत व्योम qeth_tx_arm_समयr(काष्ठा qeth_qdio_out_q *queue,
				     अचिन्हित दीर्घ usecs)
अणु
	समयr_reduce(&queue->समयr, usecs_to_jअगरfies(usecs) + jअगरfies);
पूर्ण

अटल अंतरभूत bool qeth_out_queue_is_full(काष्ठा qeth_qdio_out_q *queue)
अणु
	वापस atomic_पढ़ो(&queue->used_buffers) >= QDIO_MAX_BUFFERS_PER_Q;
पूर्ण

अटल अंतरभूत bool qeth_out_queue_is_empty(काष्ठा qeth_qdio_out_q *queue)
अणु
	वापस atomic_पढ़ो(&queue->used_buffers) == 0;
पूर्ण

काष्ठा qeth_qdio_info अणु
	atomic_t state;
	/* input */
	पूर्णांक no_in_queues;
	काष्ठा qeth_qdio_q *in_q;
	काष्ठा qeth_qdio_q *c_q;
	काष्ठा qeth_qdio_buffer_pool in_buf_pool;
	काष्ठा qeth_qdio_buffer_pool init_pool;
	पूर्णांक in_buf_size;

	/* output */
	अचिन्हित पूर्णांक no_out_queues;
	काष्ठा qeth_qdio_out_q *out_qs[QETH_MAX_OUT_QUEUES];

	/* priority queueing */
	पूर्णांक करो_prio_queueing;
	पूर्णांक शेष_out_queue;
पूर्ण;

/**
 *  channel state machine
 */
क्रमागत qeth_channel_states अणु
	CH_STATE_UP,
	CH_STATE_DOWN,
	CH_STATE_HALTED,
	CH_STATE_STOPPED,
पूर्ण;
/**
 * card state machine
 */
क्रमागत qeth_card_states अणु
	CARD_STATE_DOWN,
	CARD_STATE_SOFTSETUP,
पूर्ण;

/**
 * Protocol versions
 */
क्रमागत qeth_prot_versions अणु
	QETH_PROT_NONE = 0x0000,
	QETH_PROT_IPV4 = 0x0004,
	QETH_PROT_IPV6 = 0x0006,
पूर्ण;

क्रमागत qeth_cq अणु
	QETH_CQ_DISABLED = 0,
	QETH_CQ_ENABLED = 1,
	QETH_CQ_NOTAVAILABLE = 2,
पूर्ण;

काष्ठा qeth_ipato अणु
	bool enabled;
	bool invert4;
	bool invert6;
	काष्ठा list_head entries;
पूर्ण;

काष्ठा qeth_channel अणु
	काष्ठा ccw_device *ccwdev;
	काष्ठा qeth_cmd_buffer *active_cmd;
	क्रमागत qeth_channel_states state;
	atomic_t irq_pending;
पूर्ण;

काष्ठा qeth_reply अणु
	पूर्णांक (*callback)(काष्ठा qeth_card *card, काष्ठा qeth_reply *reply,
			अचिन्हित दीर्घ data);
	व्योम *param;
पूर्ण;

काष्ठा qeth_cmd_buffer अणु
	काष्ठा list_head list_entry;
	काष्ठा completion करोne;
	spinlock_t lock;
	अचिन्हित पूर्णांक length;
	refcount_t ref_count;
	काष्ठा qeth_channel *channel;
	काष्ठा qeth_reply reply;
	दीर्घ समयout;
	अचिन्हित अक्षर *data;
	व्योम (*finalize)(काष्ठा qeth_card *card, काष्ठा qeth_cmd_buffer *iob);
	bool (*match)(काष्ठा qeth_cmd_buffer *iob,
		      काष्ठा qeth_cmd_buffer *reply);
	व्योम (*callback)(काष्ठा qeth_card *card, काष्ठा qeth_cmd_buffer *iob,
			 अचिन्हित पूर्णांक data_length);
	पूर्णांक rc;
पूर्ण;

अटल अंतरभूत व्योम qeth_get_cmd(काष्ठा qeth_cmd_buffer *iob)
अणु
	refcount_inc(&iob->ref_count);
पूर्ण

अटल अंतरभूत काष्ठा qeth_ipa_cmd *__ipa_reply(काष्ठा qeth_cmd_buffer *iob)
अणु
	अगर (!IS_IPA(iob->data))
		वापस शून्य;

	वापस (काष्ठा qeth_ipa_cmd *) PDU_ENCAPSULATION(iob->data);
पूर्ण

अटल अंतरभूत काष्ठा qeth_ipa_cmd *__ipa_cmd(काष्ठा qeth_cmd_buffer *iob)
अणु
	वापस (काष्ठा qeth_ipa_cmd *)(iob->data + IPA_PDU_HEADER_SIZE);
पूर्ण

अटल अंतरभूत काष्ठा ccw1 *__ccw_from_cmd(काष्ठा qeth_cmd_buffer *iob)
अणु
	वापस (काष्ठा ccw1 *)(iob->data + ALIGN(iob->length, 8));
पूर्ण

अटल अंतरभूत bool qeth_trylock_channel(काष्ठा qeth_channel *channel)
अणु
	वापस atomic_cmpxchg(&channel->irq_pending, 0, 1) == 0;
पूर्ण

/**
 *  OSA card related definitions
 */
काष्ठा qeth_token अणु
	__u32 issuer_rm_w;
	__u32 issuer_rm_r;
	__u32 cm_filter_w;
	__u32 cm_filter_r;
	__u32 cm_connection_w;
	__u32 cm_connection_r;
	__u32 ulp_filter_w;
	__u32 ulp_filter_r;
	__u32 ulp_connection_w;
	__u32 ulp_connection_r;
पूर्ण;

काष्ठा qeth_seqno अणु
	__u32 trans_hdr;
	__u32 pdu_hdr;
	__u32 pdu_hdr_ack;
	__u16 ipa;
पूर्ण;

काष्ठा qeth_card_blkt अणु
	पूर्णांक समय_प्रकारotal;
	पूर्णांक पूर्णांकer_packet;
	पूर्णांक पूर्णांकer_packet_jumbo;
पूर्ण;

क्रमागत qeth_pnso_mode अणु
	QETH_PNSO_NONE,
	QETH_PNSO_BRIDGEPORT,
	QETH_PNSO_ADDR_INFO,
पूर्ण;

क्रमागत qeth_link_mode अणु
	QETH_LINK_MODE_UNKNOWN,
	QETH_LINK_MODE_FIBRE_SHORT,
	QETH_LINK_MODE_FIBRE_LONG,
पूर्ण;

काष्ठा qeth_link_info अणु
	u32 speed;
	u8 duplex;
	u8 port;
	क्रमागत qeth_link_mode link_mode;
पूर्ण;

#घोषणा QETH_BROADCAST_WITH_ECHO    0x01
#घोषणा QETH_BROADCAST_WITHOUT_ECHO 0x02
काष्ठा qeth_card_info अणु
	अचिन्हित लघु unit_addr2;
	अचिन्हित लघु cula;
	__u16 func_level;
	अक्षर mcl_level[QETH_MCL_LENGTH + 1];
	/* द्विगुनword below corresponds to net_अगर_token */
	u16 ddev_devno;
	u8 cssid;
	u8 iid;
	u8 ssid;
	u8 chpid;
	u16 chid;
	u8 ids_valid:1; /* cssid,iid,chid */
	u8 dev_addr_is_रेजिस्टरed:1;
	u8 खोलो_when_online:1;
	u8 promisc_mode:1;
	u8 use_v1_blkt:1;
	u8 is_vm_nic:1;
	/* no bitfield, we take a poपूर्णांकer on these two: */
	u8 has_lp2lp_cso_v6;
	u8 has_lp2lp_cso_v4;
	क्रमागत qeth_pnso_mode pnso_mode;
	क्रमागत qeth_card_types type;
	क्रमागत qeth_link_types link_type;
	पूर्णांक broadcast_capable;
	bool layer_enक्रमced;
	काष्ठा qeth_card_blkt blkt;
	__u32 diagass_support;
	__u32 hwtrap;
	काष्ठा qeth_link_info link_info;
पूर्ण;

क्रमागत qeth_discipline_id अणु
	QETH_DISCIPLINE_UNDETERMINED = -1,
	QETH_DISCIPLINE_LAYER3 = 0,
	QETH_DISCIPLINE_LAYER2 = 1,
पूर्ण;

काष्ठा qeth_card_options अणु
	काष्ठा qeth_ipa_caps ipa4;
	काष्ठा qeth_ipa_caps ipa6;
	काष्ठा qeth_routing_info route4;
	काष्ठा qeth_routing_info route6;
	काष्ठा qeth_ipa_caps adp; /* Adapter parameters */
	काष्ठा qeth_sbp_info sbp; /* SETBRIDGEPORT options */
	काष्ठा qeth_vnicc_info vnicc; /* VNICC options */
	क्रमागत qeth_discipline_id layer;
	क्रमागत qeth_ipa_isolation_modes isolation;
	पूर्णांक snअगरfer;
	क्रमागत qeth_cq cq;
	अक्षर hsuid[9];
पूर्ण;

#घोषणा	IS_LAYER2(card)	((card)->options.layer == QETH_DISCIPLINE_LAYER2)
#घोषणा	IS_LAYER3(card)	((card)->options.layer == QETH_DISCIPLINE_LAYER3)

/*
 * thपढ़ो bits क्रम qeth_card thपढ़ो masks
 */
क्रमागत qeth_thपढ़ोs अणु
	QETH_RECOVER_THREAD = 1,
पूर्ण;

काष्ठा qeth_osn_info अणु
	पूर्णांक (*assist_cb)(काष्ठा net_device *dev, व्योम *data);
	पूर्णांक (*data_cb)(काष्ठा sk_buff *skb);
पूर्ण;

काष्ठा qeth_discipline अणु
	स्थिर काष्ठा device_type *devtype;
	पूर्णांक (*setup) (काष्ठा ccwgroup_device *);
	व्योम (*हटाओ) (काष्ठा ccwgroup_device *);
	पूर्णांक (*set_online)(काष्ठा qeth_card *card, bool carrier_ok);
	व्योम (*set_offline)(काष्ठा qeth_card *card);
	पूर्णांक (*करो_ioctl)(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
	पूर्णांक (*control_event_handler)(काष्ठा qeth_card *card,
					काष्ठा qeth_ipa_cmd *cmd);
पूर्ण;

क्रमागत qeth_addr_disposition अणु
	QETH_DISP_ADDR_DELETE = 0,
	QETH_DISP_ADDR_DO_NOTHING = 1,
	QETH_DISP_ADDR_ADD = 2,
पूर्ण;

काष्ठा qeth_rx अणु
	पूर्णांक b_count;
	पूर्णांक b_index;
	u8 buf_element;
	पूर्णांक e_offset;
	पूर्णांक qdio_err;
	u8 bufs_refill;
पूर्ण;

काष्ठा qeth_चयन_info अणु
	__u32 capabilities;
	__u32 settings;
पूर्ण;

काष्ठा qeth_priv अणु
	अचिन्हित पूर्णांक rx_copyअवरोध;
	अचिन्हित पूर्णांक tx_wanted_queues;
	u32 brport_hw_features;
	u32 brport_features;
पूर्ण;

#घोषणा QETH_NAPI_WEIGHT NAPI_POLL_WEIGHT

काष्ठा qeth_card अणु
	क्रमागत qeth_card_states state;
	spinlock_t lock;
	काष्ठा ccwgroup_device *gdev;
	काष्ठा qeth_cmd_buffer *पढ़ो_cmd;
	काष्ठा qeth_channel पढ़ो;
	काष्ठा qeth_channel ग_लिखो;
	काष्ठा qeth_channel data;

	काष्ठा net_device *dev;
	काष्ठा dentry *debugfs;
	काष्ठा qeth_card_stats stats;
	काष्ठा qeth_card_info info;
	काष्ठा qeth_token token;
	काष्ठा qeth_seqno seqno;
	काष्ठा qeth_card_options options;

	काष्ठा workqueue_काष्ठा *event_wq;
	काष्ठा workqueue_काष्ठा *cmd_wq;
	रुको_queue_head_t रुको_q;

	काष्ठा mutex ip_lock;
	/* रक्षित by ip_lock: */
	DECLARE_HASHTABLE(ip_htable, 4);
	काष्ठा qeth_ipato ipato;

	DECLARE_HASHTABLE(local_addrs4, 4);
	DECLARE_HASHTABLE(local_addrs6, 4);
	spinlock_t local_addrs4_lock;
	spinlock_t local_addrs6_lock;
	DECLARE_HASHTABLE(rx_mode_addrs, 4);
	काष्ठा work_काष्ठा rx_mode_work;
	काष्ठा work_काष्ठा kernel_thपढ़ो_starter;
	spinlock_t thपढ़ो_mask_lock;
	अचिन्हित दीर्घ thपढ़ो_start_mask;
	अचिन्हित दीर्घ thपढ़ो_allowed_mask;
	अचिन्हित दीर्घ thपढ़ो_running_mask;
	काष्ठा list_head cmd_रुकोer_list;
	/* QDIO buffer handling */
	काष्ठा qeth_qdio_info qdio;
	पूर्णांक पढ़ो_or_ग_लिखो_problem;
	काष्ठा qeth_osn_info osn_info;
	स्थिर काष्ठा qeth_discipline *discipline;
	atomic_t क्रमce_alloc_skb;
	काष्ठा service_level qeth_service_level;
	काष्ठा qdio_ssqd_desc ssqd;
	debug_info_t *debug;
	काष्ठा mutex sbp_lock;
	काष्ठा mutex conf_mutex;
	काष्ठा mutex discipline_mutex;
	काष्ठा napi_काष्ठा napi;
	काष्ठा qeth_rx rx;
	काष्ठा delayed_work buffer_reclaim_work;
	काष्ठा work_काष्ठा बंद_dev_work;
पूर्ण;

अटल अंतरभूत bool qeth_card_hw_is_reachable(काष्ठा qeth_card *card)
अणु
	वापस card->state == CARD_STATE_SOFTSETUP;
पूर्ण

अटल अंतरभूत व्योम qeth_unlock_channel(काष्ठा qeth_card *card,
				       काष्ठा qeth_channel *channel)
अणु
	atomic_set(&channel->irq_pending, 0);
	wake_up(&card->रुको_q);
पूर्ण

काष्ठा qeth_trap_id अणु
	__u16 lparnr;
	अक्षर vmname[8];
	__u8 chpid;
	__u8 ssid;
	__u16 devno;
पूर्ण __packed;

अटल अंतरभूत bool qeth_uses_tx_prio_queueing(काष्ठा qeth_card *card)
अणु
	वापस card->qdio.करो_prio_queueing != QETH_NO_PRIO_QUEUEING;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक qeth_tx_actual_queues(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_priv *priv = netdev_priv(card->dev);

	अगर (qeth_uses_tx_prio_queueing(card))
		वापस min(card->dev->num_tx_queues, card->qdio.no_out_queues);

	वापस min(priv->tx_wanted_queues, card->qdio.no_out_queues);
पूर्ण

अटल अंतरभूत u16 qeth_iqd_translate_txq(काष्ठा net_device *dev, u16 txq)
अणु
	अगर (txq == QETH_IQD_MCAST_TXQ)
		वापस dev->num_tx_queues - 1;
	अगर (txq == dev->num_tx_queues - 1)
		वापस QETH_IQD_MCAST_TXQ;
	वापस txq;
पूर्ण

अटल अंतरभूत bool qeth_iqd_is_mcast_queue(काष्ठा qeth_card *card,
					   काष्ठा qeth_qdio_out_q *queue)
अणु
	वापस qeth_iqd_translate_txq(card->dev, queue->queue_no) ==
	       QETH_IQD_MCAST_TXQ;
पूर्ण

अटल अंतरभूत व्योम qeth_scrub_qdio_buffer(काष्ठा qdio_buffer *buf,
					  अचिन्हित पूर्णांक elements)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < elements; i++)
		स_रखो(&buf->element[i], 0, माप(काष्ठा qdio_buffer_element));
	buf->element[14].sflags = 0;
	buf->element[15].sflags = 0;
पूर्ण

/**
 * qeth_get_elements_क्रम_range() -	find number of SBALEs to cover range.
 * @start:				Start of the address range.
 * @end:				Address after the end of the range.
 *
 * Returns the number of pages, and thus QDIO buffer elements, needed to cover
 * the specअगरied address range.
 */
अटल अंतरभूत पूर्णांक qeth_get_elements_क्रम_range(addr_t start, addr_t end)
अणु
	वापस PFN_UP(end) - PFN_DOWN(start);
पूर्ण

अटल अंतरभूत पूर्णांक qeth_get_ether_cast_type(काष्ठा sk_buff *skb)
अणु
	u8 *addr = eth_hdr(skb)->h_dest;

	अगर (is_multicast_ether_addr(addr))
		वापस is_broadcast_ether_addr(addr) ? RTN_BROADCAST :
						       RTN_MULTICAST;
	वापस RTN_UNICAST;
पूर्ण

अटल अंतरभूत काष्ठा dst_entry *qeth_dst_check_rcu(काष्ठा sk_buff *skb,
						   __be16 proto)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा rt6_info *rt;

	rt = (काष्ठा rt6_info *) dst;
	अगर (dst) अणु
		अगर (proto == htons(ETH_P_IPV6))
			dst = dst_check(dst, rt6_get_cookie(rt));
		अन्यथा
			dst = dst_check(dst, 0);
	पूर्ण

	वापस dst;
पूर्ण

अटल अंतरभूत __be32 qeth_next_hop_v4_rcu(काष्ठा sk_buff *skb,
					  काष्ठा dst_entry *dst)
अणु
	काष्ठा rtable *rt = (काष्ठा rtable *) dst;

	वापस (rt) ? rt_nexthop(rt, ip_hdr(skb)->daddr) : ip_hdr(skb)->daddr;
पूर्ण

अटल अंतरभूत काष्ठा in6_addr *qeth_next_hop_v6_rcu(काष्ठा sk_buff *skb,
						    काष्ठा dst_entry *dst)
अणु
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *) dst;

	अगर (rt && !ipv6_addr_any(&rt->rt6i_gateway))
		वापस &rt->rt6i_gateway;
	अन्यथा
		वापस &ipv6_hdr(skb)->daddr;
पूर्ण

अटल अंतरभूत व्योम qeth_tx_csum(काष्ठा sk_buff *skb, u8 *flags, __be16 proto)
अणु
	*flags |= QETH_HDR_EXT_CSUM_TRANSP_REQ;
	अगर ((proto == htons(ETH_P_IP) && ip_hdr(skb)->protocol == IPPROTO_UDP) ||
	    (proto == htons(ETH_P_IPV6) && ipv6_hdr(skb)->nexthdr == IPPROTO_UDP))
		*flags |= QETH_HDR_EXT_UDP;
पूर्ण

अटल अंतरभूत व्योम qeth_put_buffer_pool_entry(काष्ठा qeth_card *card,
		काष्ठा qeth_buffer_pool_entry *entry)
अणु
	list_add_tail(&entry->list, &card->qdio.in_buf_pool.entry_list);
पूर्ण

अटल अंतरभूत पूर्णांक qeth_is_diagass_supported(काष्ठा qeth_card *card,
		क्रमागत qeth_diags_cmds cmd)
अणु
	वापस card->info.diagass_support & (__u32)cmd;
पूर्ण

पूर्णांक qeth_send_simple_setassparms_prot(काष्ठा qeth_card *card,
				      क्रमागत qeth_ipa_funcs ipa_func,
				      u16 cmd_code, u32 *data,
				      क्रमागत qeth_prot_versions prot);
/* IPv4 variant */
अटल अंतरभूत पूर्णांक qeth_send_simple_setassparms(काष्ठा qeth_card *card,
					       क्रमागत qeth_ipa_funcs ipa_func,
					       u16 cmd_code, u32 *data)
अणु
	वापस qeth_send_simple_setassparms_prot(card, ipa_func, cmd_code,
						 data, QETH_PROT_IPV4);
पूर्ण

अटल अंतरभूत पूर्णांक qeth_send_simple_setassparms_v6(काष्ठा qeth_card *card,
						  क्रमागत qeth_ipa_funcs ipa_func,
						  u16 cmd_code, u32 *data)
अणु
	वापस qeth_send_simple_setassparms_prot(card, ipa_func, cmd_code,
						 data, QETH_PROT_IPV6);
पूर्ण

पूर्णांक qeth_get_priority_queue(काष्ठा qeth_card *card, काष्ठा sk_buff *skb);

बाह्य स्थिर काष्ठा qeth_discipline qeth_l2_discipline;
बाह्य स्थिर काष्ठा qeth_discipline qeth_l3_discipline;
बाह्य स्थिर काष्ठा ethtool_ops qeth_ethtool_ops;
बाह्य स्थिर काष्ठा ethtool_ops qeth_osn_ethtool_ops;
बाह्य स्थिर काष्ठा attribute_group *qeth_dev_groups[];
बाह्य स्थिर काष्ठा attribute_group *qeth_osn_dev_groups[];
बाह्य स्थिर काष्ठा device_type qeth_generic_devtype;

स्थिर अक्षर *qeth_get_cardname_लघु(काष्ठा qeth_card *);
पूर्णांक qeth_resize_buffer_pool(काष्ठा qeth_card *card, अचिन्हित पूर्णांक count);
पूर्णांक qeth_setup_discipline(काष्ठा qeth_card *card, क्रमागत qeth_discipline_id disc);
व्योम qeth_हटाओ_discipline(काष्ठा qeth_card *card);

/* exports क्रम qeth discipline device drivers */
बाह्य काष्ठा kmem_cache *qeth_core_header_cache;
बाह्य काष्ठा qeth_dbf_info qeth_dbf[QETH_DBF_INFOS];

काष्ठा net_device *qeth_clone_netdev(काष्ठा net_device *orig);
काष्ठा qeth_card *qeth_get_card_by_busid(अक्षर *bus_id);
व्योम qeth_set_allowed_thपढ़ोs(काष्ठा qeth_card *card, अचिन्हित दीर्घ thपढ़ोs,
			      पूर्णांक clear_start_mask);
पूर्णांक qeth_thपढ़ोs_running(काष्ठा qeth_card *, अचिन्हित दीर्घ);
पूर्णांक qeth_set_offline(काष्ठा qeth_card *card, स्थिर काष्ठा qeth_discipline *disc,
		     bool resetting);

पूर्णांक qeth_send_ipa_cmd(काष्ठा qeth_card *, काष्ठा qeth_cmd_buffer *,
		  पूर्णांक (*reply_cb)
		  (काष्ठा qeth_card *, काष्ठा qeth_reply *, अचिन्हित दीर्घ),
		  व्योम *);
काष्ठा qeth_cmd_buffer *qeth_ipa_alloc_cmd(काष्ठा qeth_card *card,
					   क्रमागत qeth_ipa_cmds cmd_code,
					   क्रमागत qeth_prot_versions prot,
					   अचिन्हित पूर्णांक data_length);
काष्ठा qeth_cmd_buffer *qeth_alloc_cmd(काष्ठा qeth_channel *channel,
				       अचिन्हित पूर्णांक length, अचिन्हित पूर्णांक ccws,
				       दीर्घ समयout);
काष्ठा qeth_cmd_buffer *qeth_get_setassparms_cmd(काष्ठा qeth_card *card,
						 क्रमागत qeth_ipa_funcs ipa_func,
						 u16 cmd_code,
						 अचिन्हित पूर्णांक data_length,
						 क्रमागत qeth_prot_versions prot);
काष्ठा qeth_cmd_buffer *qeth_get_diag_cmd(काष्ठा qeth_card *card,
					  क्रमागत qeth_diags_cmds sub_cmd,
					  अचिन्हित पूर्णांक data_length);
व्योम qeth_notअगरy_cmd(काष्ठा qeth_cmd_buffer *iob, पूर्णांक reason);
व्योम qeth_put_cmd(काष्ठा qeth_cmd_buffer *iob);

पूर्णांक qeth_schedule_recovery(काष्ठा qeth_card *card);
पूर्णांक qeth_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget);
व्योम qeth_setadp_promisc_mode(काष्ठा qeth_card *card, bool enable);
पूर्णांक qeth_setadpparms_change_macaddr(काष्ठा qeth_card *);
व्योम qeth_tx_समयout(काष्ठा net_device *, अचिन्हित पूर्णांक txqueue);
व्योम qeth_prepare_ipa_cmd(काष्ठा qeth_card *card, काष्ठा qeth_cmd_buffer *iob,
			  u16 cmd_length,
			  bool (*match)(काष्ठा qeth_cmd_buffer *iob,
					काष्ठा qeth_cmd_buffer *reply));
पूर्णांक qeth_query_चयन_attributes(काष्ठा qeth_card *card,
				  काष्ठा qeth_चयन_info *sw_info);
पूर्णांक qeth_query_card_info(काष्ठा qeth_card *card,
			 काष्ठा qeth_link_info *link_info);
पूर्णांक qeth_setadpparms_set_access_ctrl(काष्ठा qeth_card *card,
				     क्रमागत qeth_ipa_isolation_modes mode);

अचिन्हित पूर्णांक qeth_count_elements(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक data_offset);
पूर्णांक qeth_करो_send_packet(काष्ठा qeth_card *card, काष्ठा qeth_qdio_out_q *queue,
			काष्ठा sk_buff *skb, काष्ठा qeth_hdr *hdr,
			अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक hd_len,
			पूर्णांक elements_needed);
पूर्णांक qeth_करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
व्योम qeth_dbf_दीर्घtext(debug_info_t *id, पूर्णांक level, अक्षर *text, ...);
पूर्णांक qeth_configure_cq(काष्ठा qeth_card *, क्रमागत qeth_cq);
पूर्णांक qeth_hw_trap(काष्ठा qeth_card *, क्रमागत qeth_diags_trap_action);
पूर्णांक qeth_setassparms_cb(काष्ठा qeth_card *, काष्ठा qeth_reply *, अचिन्हित दीर्घ);
पूर्णांक qeth_set_features(काष्ठा net_device *, netdev_features_t);
व्योम qeth_enable_hw_features(काष्ठा net_device *dev);
netdev_features_t qeth_fix_features(काष्ठा net_device *, netdev_features_t);
netdev_features_t qeth_features_check(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev,
				      netdev_features_t features);
व्योम qeth_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats);
पूर्णांक qeth_set_real_num_tx_queues(काष्ठा qeth_card *card, अचिन्हित पूर्णांक count);
u16 qeth_iqd_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			  u8 cast_type, काष्ठा net_device *sb_dev);
पूर्णांक qeth_खोलो(काष्ठा net_device *dev);
पूर्णांक qeth_stop(काष्ठा net_device *dev);

पूर्णांक qeth_vm_request_mac(काष्ठा qeth_card *card);
पूर्णांक qeth_xmit(काष्ठा qeth_card *card, काष्ठा sk_buff *skb,
	      काष्ठा qeth_qdio_out_q *queue, __be16 proto,
	      व्योम (*fill_header)(काष्ठा qeth_qdio_out_q *queue,
				  काष्ठा qeth_hdr *hdr, काष्ठा sk_buff *skb,
				  __be16 proto, अचिन्हित पूर्णांक data_len));

/* exports क्रम OSN */
पूर्णांक qeth_osn_assist(काष्ठा net_device *, व्योम *, पूर्णांक);
पूर्णांक qeth_osn_रेजिस्टर(अचिन्हित अक्षर *पढ़ो_dev_no, काष्ठा net_device **,
		पूर्णांक (*assist_cb)(काष्ठा net_device *, व्योम *),
		पूर्णांक (*data_cb)(काष्ठा sk_buff *));
व्योम qeth_osn_deरेजिस्टर(काष्ठा net_device *);

#पूर्ण_अगर /* __QETH_CORE_H__ */
