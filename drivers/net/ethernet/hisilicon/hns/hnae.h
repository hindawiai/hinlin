<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#अगर_अघोषित __HNAE_H
#घोषणा __HNAE_H

/* Names used in this framework:
 *      ae handle (handle):
 *        a set of queues provided by AE
 *      ring buffer queue (rbq):
 *        the channel between upper layer and the AE, can करो tx and rx
 *      ring:
 *        a tx or rx channel within a rbq
 *      ring description (desc):
 *        an element in the ring with packet inक्रमmation
 *      buffer:
 *        a memory region referred by desc with the full packet payload
 *
 * "num" means a अटल number set as a parameter, "count" mean a dynamic
 *   number set जबतक running
 * "cb" means control block
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/phy.h>
#समावेश <linux/types.h>

#घोषणा HNAE_DRIVER_VERSION "2.0"
#घोषणा HNAE_DRIVER_NAME "hns"
#घोषणा HNAE_COPYRIGHT "Copyright(c) 2015 Huawei Corporation."
#घोषणा HNAE_DRIVER_STRING "Hisilicon Network Subsystem Driver"
#घोषणा HNAE_DEFAULT_DEVICE_DESCR "Hisilicon Network Subsystem"

#अगर_घोषित DEBUG

#अगर_अघोषित निश्चित
#घोषणा निश्चित(expr) \
करो अणु \
	अगर (!(expr)) अणु \
		pr_err("Assertion failed! %s, %s, %s, line %d\n", \
			   #expr, __खाता__, __func__, __LINE__); \
	पूर्ण \
पूर्ण जबतक (0)
#पूर्ण_अगर

#अन्यथा

#अगर_अघोषित निश्चित
#घोषणा निश्चित(expr)
#पूर्ण_अगर

#पूर्ण_अगर

#घोषणा AE_VERSION_1 ('6' << 16 | '6' << 8 | '0')
#घोषणा AE_VERSION_2 ('1' << 24 | '6' << 16 | '1' << 8 | '0')
#घोषणा AE_IS_VER1(ver) ((ver) == AE_VERSION_1)
#घोषणा AE_NAME_SIZE 16

#घोषणा BD_SIZE_2048_MAX_MTU   6000

/* some said the RX and TX RCB क्रमmat should not be the same in the future. But
 * it is the same now...
 */
#घोषणा RCB_REG_BASEADDR_L         0x00 /* P660 support only 32bit accessing */
#घोषणा RCB_REG_BASEADDR_H         0x04
#घोषणा RCB_REG_BD_NUM             0x08
#घोषणा RCB_REG_BD_LEN             0x0C
#घोषणा RCB_REG_PKTLINE            0x10
#घोषणा RCB_REG_TAIL               0x18
#घोषणा RCB_REG_HEAD               0x1C
#घोषणा RCB_REG_FBDNUM             0x20
#घोषणा RCB_REG_OFFSET             0x24 /* pkt num to be handled */
#घोषणा RCB_REG_PKTNUM_RECORD      0x2C /* total pkt received */

#घोषणा HNS_RX_HEAD_SIZE 256

#घोषणा HNAE_AE_REGISTER 0x1

#घोषणा RCB_RING_NAME_LEN (IFNAMSIZ + 4)

#घोषणा HNAE_LOWEST_LATENCY_COAL_PARAM	30
#घोषणा HNAE_LOW_LATENCY_COAL_PARAM	80
#घोषणा HNAE_BULK_LATENCY_COAL_PARAM	150

क्रमागत hnae_led_state अणु
	HNAE_LED_INACTIVE,
	HNAE_LED_ACTIVE,
	HNAE_LED_ON,
	HNAE_LED_OFF
पूर्ण;

#घोषणा HNS_RX_FLAG_VLAN_PRESENT 0x1
#घोषणा HNS_RX_FLAG_L3ID_IPV4 0x0
#घोषणा HNS_RX_FLAG_L3ID_IPV6 0x1
#घोषणा HNS_RX_FLAG_L4ID_UDP 0x0
#घोषणा HNS_RX_FLAG_L4ID_TCP 0x1
#घोषणा HNS_RX_FLAG_L4ID_SCTP 0x3

#घोषणा HNS_TXD_ASID_S 0
#घोषणा HNS_TXD_ASID_M (0xff << HNS_TXD_ASID_S)
#घोषणा HNS_TXD_BUFNUM_S 8
#घोषणा HNS_TXD_BUFNUM_M (0x3 << HNS_TXD_BUFNUM_S)
#घोषणा HNS_TXD_PORTID_S 10
#घोषणा HNS_TXD_PORTID_M (0x7 << HNS_TXD_PORTID_S)

#घोषणा HNS_TXD_RA_B 8
#घोषणा HNS_TXD_RI_B 9
#घोषणा HNS_TXD_L4CS_B 10
#घोषणा HNS_TXD_L3CS_B 11
#घोषणा HNS_TXD_FE_B 12
#घोषणा HNS_TXD_VLD_B 13
#घोषणा HNS_TXD_IPOFFSET_S 14
#घोषणा HNS_TXD_IPOFFSET_M (0xff << HNS_TXD_IPOFFSET_S)

#घोषणा HNS_RXD_IPOFFSET_S 0
#घोषणा HNS_RXD_IPOFFSET_M (0xff << HNS_TXD_IPOFFSET_S)
#घोषणा HNS_RXD_BUFNUM_S 8
#घोषणा HNS_RXD_BUFNUM_M (0x3 << HNS_RXD_BUFNUM_S)
#घोषणा HNS_RXD_PORTID_S 10
#घोषणा HNS_RXD_PORTID_M (0x7 << HNS_RXD_PORTID_S)
#घोषणा HNS_RXD_DMAC_S 13
#घोषणा HNS_RXD_DMAC_M (0x3 << HNS_RXD_DMAC_S)
#घोषणा HNS_RXD_VLAN_S 15
#घोषणा HNS_RXD_VLAN_M (0x3 << HNS_RXD_VLAN_S)
#घोषणा HNS_RXD_L3ID_S 17
#घोषणा HNS_RXD_L3ID_M (0xf << HNS_RXD_L3ID_S)
#घोषणा HNS_RXD_L4ID_S 21
#घोषणा HNS_RXD_L4ID_M (0xf << HNS_RXD_L4ID_S)
#घोषणा HNS_RXD_FE_B 25
#घोषणा HNS_RXD_FRAG_B 26
#घोषणा HNS_RXD_VLD_B 27
#घोषणा HNS_RXD_L2E_B 28
#घोषणा HNS_RXD_L3E_B 29
#घोषणा HNS_RXD_L4E_B 30
#घोषणा HNS_RXD_DROP_B 31

#घोषणा HNS_RXD_VLANID_S 8
#घोषणा HNS_RXD_VLANID_M (0xfff << HNS_RXD_VLANID_S)
#घोषणा HNS_RXD_CFI_B 20
#घोषणा HNS_RXD_PRI_S 21
#घोषणा HNS_RXD_PRI_M (0x7 << HNS_RXD_PRI_S)
#घोषणा HNS_RXD_ASID_S 24
#घोषणा HNS_RXD_ASID_M (0xff << HNS_RXD_ASID_S)

#घोषणा HNSV2_TXD_BUFNUM_S 0
#घोषणा HNSV2_TXD_BUFNUM_M (0x7 << HNSV2_TXD_BUFNUM_S)
#घोषणा HNSV2_TXD_PORTID_S	4
#घोषणा HNSV2_TXD_PORTID_M	(0X7 << HNSV2_TXD_PORTID_S)
#घोषणा HNSV2_TXD_RI_B   1
#घोषणा HNSV2_TXD_L4CS_B   2
#घोषणा HNSV2_TXD_L3CS_B   3
#घोषणा HNSV2_TXD_FE_B   4
#घोषणा HNSV2_TXD_VLD_B  5

#घोषणा HNSV2_TXD_TSE_B   0
#घोषणा HNSV2_TXD_VLAN_EN_B   1
#घोषणा HNSV2_TXD_SNAP_B   2
#घोषणा HNSV2_TXD_IPV6_B   3
#घोषणा HNSV2_TXD_SCTP_B   4

/* hardware spec ring buffer क्रमmat */
काष्ठा __packed hnae_desc अणु
	__le64 addr;
	जोड़ अणु
		काष्ठा अणु
			जोड़ अणु
				__le16 asid_bufnum_pid;
				__le16 asid;
			पूर्ण;
			__le16 send_size;
			जोड़ अणु
				__le32 flag_ipoffset;
				काष्ठा अणु
					__u8 bn_pid;
					__u8 ra_ri_cs_fe_vld;
					__u8 ip_offset;
					__u8 tse_vlan_snap_v6_sctp_nth;
				पूर्ण;
			पूर्ण;
			__le16 mss;
			__u8 l4_len;
			__u8 reserved1;
			__le16 paylen;
			__u8 vmid;
			__u8 qid;
			__le32 reserved2[2];
		पूर्ण tx;

		काष्ठा अणु
			__le32 ipoff_bnum_pid_flag;
			__le16 pkt_len;
			__le16 size;
			जोड़ अणु
				__le32 vlan_pri_asid;
				काष्ठा अणु
					__le16 asid;
					__le16 vlan_cfi_pri;
				पूर्ण;
			पूर्ण;
			__le32 rss_hash;
			__le32 reserved_1[2];
		पूर्ण rx;
	पूर्ण;
पूर्ण;

काष्ठा hnae_desc_cb अणु
	dma_addr_t dma; /* dma address of this desc */
	व्योम *buf;      /* cpu addr क्रम a desc */

	/* priv data क्रम the desc, e.g. skb when use with ip stack*/
	व्योम *priv;
	u32 page_offset;
	u32 length;     /* length of the buffer */

	u16 reuse_flag;

       /* desc type, used by the ring user to mark the type of the priv data */
	u16 type;
पूर्ण;

#घोषणा setflags(flags, bits) ((flags) |= (bits))
#घोषणा unsetflags(flags, bits) ((flags) &= ~(bits))

/* hnae_ring->flags fields */
#घोषणा RINGF_सूची 0x1	    /* TX or RX ring, set अगर TX */
#घोषणा is_tx_ring(ring) ((ring)->flags & RINGF_सूची)
#घोषणा is_rx_ring(ring) (!is_tx_ring(ring))
#घोषणा ring_to_dma_dir(ring) (is_tx_ring(ring) ? \
	DMA_TO_DEVICE : DMA_FROM_DEVICE)

काष्ठा ring_stats अणु
	u64 io_err_cnt;
	u64 sw_err_cnt;
	u64 seg_pkt_cnt;
	जोड़ अणु
		काष्ठा अणु
			u64 tx_pkts;
			u64 tx_bytes;
			u64 tx_err_cnt;
			u64 restart_queue;
			u64 tx_busy;
		पूर्ण;
		काष्ठा अणु
			u64 rx_pkts;
			u64 rx_bytes;
			u64 rx_err_cnt;
			u64 reuse_pg_cnt;
			u64 err_pkt_len;
			u64 non_vld_descs;
			u64 err_bd_num;
			u64 l2_err;
			u64 l3l4_csum_err;
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा hnae_queue;

काष्ठा hnae_ring अणु
	u8 __iomem *io_base; /* base io address क्रम the ring */
	काष्ठा hnae_desc *desc; /* dma map address space */
	काष्ठा hnae_desc_cb *desc_cb;
	काष्ठा hnae_queue *q;
	पूर्णांक irq;
	अक्षर ring_name[RCB_RING_NAME_LEN];

	/* statistic */
	काष्ठा ring_stats stats;

	dma_addr_t desc_dma_addr;
	u32 buf_size;       /* size क्रम hnae_desc->addr, preset by AE */
	u16 desc_num;       /* total number of desc */
	u16 max_desc_num_per_pkt;
	u16 max_raw_data_sz_per_desc;
	u16 max_pkt_size;
	पूर्णांक next_to_use;    /* idx of next spare desc */

	/* idx of lastest sent desc, the ring is empty when equal to
	 * next_to_use
	 */
	पूर्णांक next_to_clean;

	पूर्णांक flags;          /* ring attribute */
	पूर्णांक irq_init_flag;

	/* total rx bytes after last rx rate calucated */
	u64 coal_last_rx_bytes;
	अचिन्हित दीर्घ coal_last_jअगरfies;
	u32 coal_param;
	u32 coal_rx_rate;	/* rx rate in MB */
पूर्ण;

#घोषणा ring_ptr_move_fw(ring, p) \
	((ring)->p = ((ring)->p + 1) % (ring)->desc_num)
#घोषणा ring_ptr_move_bw(ring, p) \
	((ring)->p = ((ring)->p - 1 + (ring)->desc_num) % (ring)->desc_num)

क्रमागत hns_desc_type अणु
	DESC_TYPE_SKB,
	DESC_TYPE_PAGE,
पूर्ण;

#घोषणा निश्चित_is_ring_idx(ring, idx) \
	निश्चित((idx) >= 0 && (idx) < (ring)->desc_num)

/* the distance between [begin, end) in a ring buffer
 * note: there is a unuse slot between the begin and the end
 */
अटल अंतरभूत पूर्णांक ring_dist(काष्ठा hnae_ring *ring, पूर्णांक begin, पूर्णांक end)
अणु
	निश्चित_is_ring_idx(ring, begin);
	निश्चित_is_ring_idx(ring, end);

	वापस (end - begin + ring->desc_num) % ring->desc_num;
पूर्ण

अटल अंतरभूत पूर्णांक ring_space(काष्ठा hnae_ring *ring)
अणु
	वापस ring->desc_num -
		ring_dist(ring, ring->next_to_clean, ring->next_to_use) - 1;
पूर्ण

अटल अंतरभूत पूर्णांक is_ring_empty(काष्ठा hnae_ring *ring)
अणु
	निश्चित_is_ring_idx(ring, ring->next_to_use);
	निश्चित_is_ring_idx(ring, ring->next_to_clean);

	वापस ring->next_to_use == ring->next_to_clean;
पूर्ण

#घोषणा hnae_buf_size(_ring) ((_ring)->buf_size)
#घोषणा hnae_page_order(_ring) (get_order(hnae_buf_size(_ring)))
#घोषणा hnae_page_size(_ring) (PAGE_SIZE << hnae_page_order(_ring))

काष्ठा hnae_handle;

/* allocate and dma map space क्रम hnae desc */
काष्ठा hnae_buf_ops अणु
	पूर्णांक (*alloc_buffer)(काष्ठा hnae_ring *ring, काष्ठा hnae_desc_cb *cb);
	व्योम (*मुक्त_buffer)(काष्ठा hnae_ring *ring, काष्ठा hnae_desc_cb *cb);
	पूर्णांक (*map_buffer)(काष्ठा hnae_ring *ring, काष्ठा hnae_desc_cb *cb);
	व्योम (*unmap_buffer)(काष्ठा hnae_ring *ring, काष्ठा hnae_desc_cb *cb);
पूर्ण;

काष्ठा hnae_queue अणु
	u8 __iomem *io_base;
	phys_addr_t phy_base;
	काष्ठा hnae_ae_dev *dev;	/* the device who use this queue */
	काष्ठा hnae_ring rx_ring ____cacheline_पूर्णांकernodealigned_in_smp;
	काष्ठा hnae_ring tx_ring ____cacheline_पूर्णांकernodealigned_in_smp;
	काष्ठा hnae_handle *handle;
पूर्ण;

/*hnae loop mode*/
क्रमागत hnae_loop अणु
	MAC_INTERNALLOOP_MAC = 0,
	MAC_INTERNALLOOP_SERDES,
	MAC_INTERNALLOOP_PHY,
	MAC_LOOP_PHY_NONE,
	MAC_LOOP_NONE,
पूर्ण;

/*hnae port type*/
क्रमागत hnae_port_type अणु
	HNAE_PORT_SERVICE = 0,
	HNAE_PORT_DEBUG
पूर्ण;

/* mac media type */
क्रमागत hnae_media_type अणु
	HNAE_MEDIA_TYPE_UNKNOWN = 0,
	HNAE_MEDIA_TYPE_FIBER,
	HNAE_MEDIA_TYPE_COPPER,
	HNAE_MEDIA_TYPE_BACKPLANE,
पूर्ण;

/* This काष्ठा defines the operation on the handle.
 *
 * get_handle(): (mandatory)
 *   Get a handle from AE according to its name and options.
 *   the AE driver should manage the space used by handle and its queues जबतक
 *   the HNAE framework will allocate desc and desc_cb क्रम all rings in the
 *   queues.
 * put_handle():
 *   Release the handle.
 * start():
 *   Enable the hardware, include all queues
 * stop():
 *   Disable the hardware
 * set_opts(): (mandatory)
 *   Set options to the AE
 * get_opts(): (mandatory)
 *   Get options from the AE
 * get_status():
 *   Get the carrier state of the back channel of the handle, 1 क्रम ok, 0 क्रम
 *   non-ok
 * toggle_ring_irq(): (mandatory)
 *   Set the ring irq to be enabled(0) or disable(1)
 * toggle_queue_status(): (mandatory)
 *   Set the queue to be enabled(1) or disable(0), this will not change the
 *   ring irq state
 * adjust_link()
 *   adjust link status
 * set_loopback()
 *   set loopback
 * get_ring_bdnum_limit()
 *   get ring bd number limit
 * get_छोड़ोparam()
 *   get tx and rx of छोड़ो frame use
 * set_छोड़ोparam()
 *   set tx and rx of छोड़ो frame use
 * get_coalesce_usecs()
 *   get usecs to delay a TX पूर्णांकerrupt after a packet is sent
 * get_rx_max_coalesced_frames()
 *   get Maximum number of packets to be sent beक्रमe a TX पूर्णांकerrupt.
 * set_coalesce_usecs()
 *   set usecs to delay a TX पूर्णांकerrupt after a packet is sent
 * set_coalesce_frames()
 *   set Maximum number of packets to be sent beक्रमe a TX पूर्णांकerrupt.
 * get_ringnum()
 *   get RX/TX ring number
 * get_max_ringnum()
 *   get RX/TX ring maximum number
 * get_mac_addr()
 *   get mac address
 * set_mac_addr()
 *   set mac address
 * clr_mc_addr()
 *   clear mcast tcam table
 * set_mc_addr()
 *   set multicast mode
 * add_uc_addr()
 *   add ucast address
 * rm_uc_addr()
 *   हटाओ ucast address
 * set_mtu()
 *   set mtu
 * update_stats()
 *   update Old network device statistics
 * get_ethtool_stats()
 *   get ethtool network device statistics
 * get_strings()
 *   get a set of strings that describe the requested objects
 * get_sset_count()
 *   get number of strings that @get_strings will ग_लिखो
 * update_led_status()
 *   update the led status
 * set_led_id()
 *   set led id
 * get_regs()
 *   get regs dump
 * get_regs_len()
 *   get the len of the regs dump
 */
काष्ठा hnae_ae_ops अणु
	काष्ठा hnae_handle *(*get_handle)(काष्ठा hnae_ae_dev *dev,
					  u32 port_id);
	व्योम (*put_handle)(काष्ठा hnae_handle *handle);
	व्योम (*init_queue)(काष्ठा hnae_queue *q);
	व्योम (*fini_queue)(काष्ठा hnae_queue *q);
	पूर्णांक (*start)(काष्ठा hnae_handle *handle);
	व्योम (*stop)(काष्ठा hnae_handle *handle);
	व्योम (*reset)(काष्ठा hnae_handle *handle);
	पूर्णांक (*set_opts)(काष्ठा hnae_handle *handle, पूर्णांक type, व्योम *opts);
	पूर्णांक (*get_opts)(काष्ठा hnae_handle *handle, पूर्णांक type, व्योम **opts);
	पूर्णांक (*get_status)(काष्ठा hnae_handle *handle);
	पूर्णांक (*get_info)(काष्ठा hnae_handle *handle,
			u8 *स्वतः_neg, u16 *speed, u8 *duplex);
	व्योम (*toggle_ring_irq)(काष्ठा hnae_ring *ring, u32 val);
	व्योम (*adjust_link)(काष्ठा hnae_handle *handle, पूर्णांक speed, पूर्णांक duplex);
	bool (*need_adjust_link)(काष्ठा hnae_handle *handle,
				 पूर्णांक speed, पूर्णांक duplex);
	पूर्णांक (*set_loopback)(काष्ठा hnae_handle *handle,
			    क्रमागत hnae_loop loop_mode, पूर्णांक en);
	व्योम (*get_ring_bdnum_limit)(काष्ठा hnae_queue *queue,
				     u32 *uplimit);
	व्योम (*get_छोड़ोparam)(काष्ठा hnae_handle *handle,
			       u32 *स्वतः_neg, u32 *rx_en, u32 *tx_en);
	पूर्णांक (*set_छोड़ोparam)(काष्ठा hnae_handle *handle,
			      u32 स्वतः_neg, u32 rx_en, u32 tx_en);
	व्योम (*get_coalesce_usecs)(काष्ठा hnae_handle *handle,
				   u32 *tx_usecs, u32 *rx_usecs);
	व्योम (*get_max_coalesced_frames)(काष्ठा hnae_handle *handle,
					 u32 *tx_frames, u32 *rx_frames);
	पूर्णांक (*set_coalesce_usecs)(काष्ठा hnae_handle *handle, u32 समयout);
	पूर्णांक (*set_coalesce_frames)(काष्ठा hnae_handle *handle,
				   u32 tx_frames, u32 rx_frames);
	व्योम (*get_coalesce_range)(काष्ठा hnae_handle *handle,
				   u32 *tx_frames_low, u32 *rx_frames_low,
				   u32 *tx_frames_high, u32 *rx_frames_high,
				   u32 *tx_usecs_low, u32 *rx_usecs_low,
				   u32 *tx_usecs_high, u32 *rx_usecs_high);
	व्योम (*set_promisc_mode)(काष्ठा hnae_handle *handle, u32 en);
	पूर्णांक (*get_mac_addr)(काष्ठा hnae_handle *handle, व्योम **p);
	पूर्णांक (*set_mac_addr)(काष्ठा hnae_handle *handle, व्योम *p);
	पूर्णांक (*add_uc_addr)(काष्ठा hnae_handle *handle,
			   स्थिर अचिन्हित अक्षर *addr);
	पूर्णांक (*rm_uc_addr)(काष्ठा hnae_handle *handle,
			  स्थिर अचिन्हित अक्षर *addr);
	पूर्णांक (*clr_mc_addr)(काष्ठा hnae_handle *handle);
	पूर्णांक (*set_mc_addr)(काष्ठा hnae_handle *handle, व्योम *addr);
	पूर्णांक (*set_mtu)(काष्ठा hnae_handle *handle, पूर्णांक new_mtu);
	व्योम (*set_tso_stats)(काष्ठा hnae_handle *handle, पूर्णांक enable);
	व्योम (*update_stats)(काष्ठा hnae_handle *handle,
			     काष्ठा net_device_stats *net_stats);
	व्योम (*get_stats)(काष्ठा hnae_handle *handle, u64 *data);
	व्योम (*get_strings)(काष्ठा hnae_handle *handle,
			    u32 stringset, u8 *data);
	पूर्णांक (*get_sset_count)(काष्ठा hnae_handle *handle, पूर्णांक stringset);
	व्योम (*update_led_status)(काष्ठा hnae_handle *handle);
	पूर्णांक (*set_led_id)(काष्ठा hnae_handle *handle,
			  क्रमागत hnae_led_state status);
	व्योम (*get_regs)(काष्ठा hnae_handle *handle, व्योम *data);
	पूर्णांक (*get_regs_len)(काष्ठा hnae_handle *handle);
	u32	(*get_rss_key_size)(काष्ठा hnae_handle *handle);
	u32	(*get_rss_indir_size)(काष्ठा hnae_handle *handle);
	पूर्णांक	(*get_rss)(काष्ठा hnae_handle *handle, u32 *indir, u8 *key,
			   u8 *hfunc);
	पूर्णांक	(*set_rss)(काष्ठा hnae_handle *handle, स्थिर u32 *indir,
			   स्थिर u8 *key, स्थिर u8 hfunc);
पूर्ण;

काष्ठा hnae_ae_dev अणु
	काष्ठा device cls_dev; /* the class dev */
	काष्ठा device *dev; /* the presented dev */
	काष्ठा hnae_ae_ops *ops;
	काष्ठा list_head node;
	काष्ठा module *owner; /* the module who provides this dev */
	पूर्णांक id;
	अक्षर name[AE_NAME_SIZE];
	काष्ठा list_head handle_list;
	spinlock_t lock; /* lock to protect the handle_list */
पूर्ण;

काष्ठा hnae_handle अणु
	काष्ठा device *owner_dev; /* the device which make use of this handle */
	काष्ठा hnae_ae_dev *dev;  /* the device who provides this handle */
	काष्ठा phy_device *phy_dev;
	phy_पूर्णांकerface_t phy_अगर;
	u32 अगर_support;
	पूर्णांक q_num;
	पूर्णांक vf_id;
	अचिन्हित दीर्घ coal_last_jअगरfies;
	u32 coal_param;		/* self adapt coalesce param */
	/* the ring index of last ring that set coal param */
	u32 coal_ring_idx;
	u32 eport_id;
	u32 dport_id;	/* v2 tx bd should fill the dport_id */
	bool coal_adapt_en;
	क्रमागत hnae_port_type port_type;
	क्रमागत hnae_media_type media_type;
	काष्ठा list_head node;    /* list to hnae_ae_dev->handle_list */
	काष्ठा hnae_buf_ops *bops; /* operation क्रम the buffer */
	काष्ठा hnae_queue **qs;  /* array base of all queues */
पूर्ण;

#घोषणा ring_to_dev(ring) ((ring)->q->dev->dev)

काष्ठा hnae_handle *hnae_get_handle(काष्ठा device *owner_dev,
				    स्थिर काष्ठा fwnode_handle	*fwnode,
				    u32 port_id,
				    काष्ठा hnae_buf_ops *bops);

व्योम hnae_put_handle(काष्ठा hnae_handle *handle);
पूर्णांक hnae_ae_रेजिस्टर(काष्ठा hnae_ae_dev *dev, काष्ठा module *owner);
व्योम hnae_ae_unरेजिस्टर(काष्ठा hnae_ae_dev *dev);

पूर्णांक hnae_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
व्योम hnae_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक hnae_reinit_handle(काष्ठा hnae_handle *handle);

#घोषणा hnae_queue_xmit(q, buf_num) ग_लिखोl_relaxed(buf_num, \
	(q)->tx_ring.io_base + RCB_REG_TAIL)

#अगर_अघोषित निश्चित
#घोषणा निश्चित(cond)
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक hnae_reserve_buffer_map(काष्ठा hnae_ring *ring,
					  काष्ठा hnae_desc_cb *cb)
अणु
	काष्ठा hnae_buf_ops *bops = ring->q->handle->bops;
	पूर्णांक ret;

	ret = bops->alloc_buffer(ring, cb);
	अगर (ret)
		जाओ out;

	ret = bops->map_buffer(ring, cb);
	अगर (ret)
		जाओ out_with_buf;

	वापस 0;

out_with_buf:
	bops->मुक्त_buffer(ring, cb);
out:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक hnae_alloc_buffer_attach(काष्ठा hnae_ring *ring, पूर्णांक i)
अणु
	पूर्णांक ret = hnae_reserve_buffer_map(ring, &ring->desc_cb[i]);

	अगर (ret)
		वापस ret;

	ring->desc[i].addr = cpu_to_le64(ring->desc_cb[i].dma);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम hnae_buffer_detach(काष्ठा hnae_ring *ring, पूर्णांक i)
अणु
	ring->q->handle->bops->unmap_buffer(ring, &ring->desc_cb[i]);
	ring->desc[i].addr = 0;
पूर्ण

अटल अंतरभूत व्योम hnae_मुक्त_buffer_detach(काष्ठा hnae_ring *ring, पूर्णांक i)
अणु
	काष्ठा hnae_buf_ops *bops = ring->q->handle->bops;
	काष्ठा hnae_desc_cb *cb = &ring->desc_cb[i];

	अगर (!ring->desc_cb[i].dma)
		वापस;

	hnae_buffer_detach(ring, i);
	bops->मुक्त_buffer(ring, cb);
पूर्ण

/* detach a in-used buffer and replace with a reserved one  */
अटल अंतरभूत व्योम hnae_replace_buffer(काष्ठा hnae_ring *ring, पूर्णांक i,
				       काष्ठा hnae_desc_cb *res_cb)
अणु
	काष्ठा hnae_buf_ops *bops = ring->q->handle->bops;

	bops->unmap_buffer(ring, &ring->desc_cb[i]);
	ring->desc_cb[i] = *res_cb;
	ring->desc[i].addr = cpu_to_le64(ring->desc_cb[i].dma);
	ring->desc[i].rx.ipoff_bnum_pid_flag = 0;
पूर्ण

अटल अंतरभूत व्योम hnae_reuse_buffer(काष्ठा hnae_ring *ring, पूर्णांक i)
अणु
	ring->desc_cb[i].reuse_flag = 0;
	ring->desc[i].addr = cpu_to_le64(ring->desc_cb[i].dma
		+ ring->desc_cb[i].page_offset);
	ring->desc[i].rx.ipoff_bnum_pid_flag = 0;
पूर्ण

/* when reinit buffer size, we should reinit buffer description */
अटल अंतरभूत व्योम hnae_reinit_all_ring_desc(काष्ठा hnae_handle *h)
अणु
	पूर्णांक i, j;
	काष्ठा hnae_ring *ring;

	क्रम (i = 0; i < h->q_num; i++) अणु
		ring = &h->qs[i]->rx_ring;
		क्रम (j = 0; j < ring->desc_num; j++)
			ring->desc[j].addr = cpu_to_le64(ring->desc_cb[j].dma);
	पूर्ण

	wmb();	/* commit all data beक्रमe submit */
पूर्ण

/* when reinit buffer size, we should reinit page offset */
अटल अंतरभूत व्योम hnae_reinit_all_ring_page_off(काष्ठा hnae_handle *h)
अणु
	पूर्णांक i, j;
	काष्ठा hnae_ring *ring;

	क्रम (i = 0; i < h->q_num; i++) अणु
		ring = &h->qs[i]->rx_ring;
		क्रम (j = 0; j < ring->desc_num; j++) अणु
			ring->desc_cb[j].page_offset = 0;
			अगर (ring->desc[j].addr !=
			    cpu_to_le64(ring->desc_cb[j].dma))
				ring->desc[j].addr =
					cpu_to_le64(ring->desc_cb[j].dma);
		पूर्ण
	पूर्ण

	wmb();	/* commit all data beक्रमe submit */
पूर्ण

#घोषणा hnae_set_field(origin, mask, shअगरt, val) \
	करो अणु \
		(origin) &= (~(mask)); \
		(origin) |= ((val) << (shअगरt)) & (mask); \
	पूर्ण जबतक (0)

#घोषणा hnae_set_bit(origin, shअगरt, val) \
	hnae_set_field((origin), (0x1 << (shअगरt)), (shअगरt), (val))

#घोषणा hnae_get_field(origin, mask, shअगरt) (((origin) & (mask)) >> (shअगरt))

#घोषणा hnae_get_bit(origin, shअगरt) \
	hnae_get_field((origin), (0x1 << (shअगरt)), (shअगरt))

#पूर्ण_अगर
