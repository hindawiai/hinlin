<शैली गुरु>
/******************************************************************************
 * This software may be used and distributed according to the terms of
 * the GNU General Public License (GPL), incorporated herein by reference.
 * Drivers based on or derived from this code fall under the GPL and must
 * retain the authorship, copyright and license notice.  This file is not
 * a complete program and may only be used when the entire operating
 * प्रणाली is licensed under the GPL.
 * See the file COPYING in this distribution क्रम more inक्रमmation.
 *
 * vxge-traffic.h: Driver क्रम Exar Corp's X3100 Series 10GbE PCIe I/O
 *                 Virtualized Server Adapter.
 * Copyright(c) 2002-2010 Exar Corp.
 ******************************************************************************/
#अगर_अघोषित VXGE_TRAFFIC_H
#घोषणा VXGE_TRAFFIC_H

#समावेश "vxge-reg.h"
#समावेश "vxge-version.h"

#घोषणा VXGE_HW_DTR_MAX_T_CODE		16
#घोषणा VXGE_HW_ALL_FOXES		0xFFFFFFFFFFFFFFFFULL
#घोषणा VXGE_HW_INTR_MASK_ALL		0xFFFFFFFFFFFFFFFFULL
#घोषणा	VXGE_HW_MAX_VIRTUAL_PATHS	17

#घोषणा VXGE_HW_MAC_MAX_MAC_PORT_ID	2

#घोषणा VXGE_HW_DEFAULT_32		0xffffffff
/* frames sizes */
#घोषणा VXGE_HW_HEADER_802_2_SIZE	3
#घोषणा VXGE_HW_HEADER_SNAP_SIZE	5
#घोषणा VXGE_HW_HEADER_VLAN_SIZE	4
#घोषणा VXGE_HW_MAC_HEADER_MAX_SIZE \
			(ETH_HLEN + \
			VXGE_HW_HEADER_802_2_SIZE + \
			VXGE_HW_HEADER_VLAN_SIZE + \
			VXGE_HW_HEADER_SNAP_SIZE)

/* 32bit alignments */
#घोषणा VXGE_HW_HEADER_ETHERNET_II_802_3_ALIGN		2
#घोषणा VXGE_HW_HEADER_802_2_SNAP_ALIGN			2
#घोषणा VXGE_HW_HEADER_802_2_ALIGN			3
#घोषणा VXGE_HW_HEADER_SNAP_ALIGN			1

#घोषणा VXGE_HW_L3_CKSUM_OK				0xFFFF
#घोषणा VXGE_HW_L4_CKSUM_OK				0xFFFF

/* Forward declarations */
काष्ठा __vxge_hw_device;
काष्ठा __vxge_hw_vpath_handle;
काष्ठा vxge_hw_vp_config;
काष्ठा __vxge_hw_भवpath;
काष्ठा __vxge_hw_channel;
काष्ठा __vxge_hw_fअगरo;
काष्ठा __vxge_hw_ring;
काष्ठा vxge_hw_ring_attr;
काष्ठा vxge_hw_mempool;

#अगर_अघोषित TRUE
#घोषणा TRUE 1
#पूर्ण_अगर

#अगर_अघोषित FALSE
#घोषणा FALSE 0
#पूर्ण_अगर

/*VXGE_HW_STATUS_H*/

#घोषणा VXGE_HW_EVENT_BASE			0
#घोषणा VXGE_LL_EVENT_BASE			100

/**
 * क्रमागत vxge_hw_event- Enumerates slow-path HW events.
 * @VXGE_HW_EVENT_UNKNOWN: Unknown (and invalid) event.
 * @VXGE_HW_EVENT_SERR: Serious vpath hardware error event.
 * @VXGE_HW_EVENT_ECCERR: vpath ECC error event.
 * @VXGE_HW_EVENT_VPATH_ERR: Error local to the respective vpath
 * @VXGE_HW_EVENT_FIFO_ERR: FIFO Doorbell fअगरo error.
 * @VXGE_HW_EVENT_SRPCIM_SERR: srpcim hardware error event.
 * @VXGE_HW_EVENT_MRPCIM_SERR: mrpcim hardware error event.
 * @VXGE_HW_EVENT_MRPCIM_ECCERR: mrpcim ecc error event.
 * @VXGE_HW_EVENT_RESET_START: Privileged entity is starting device reset
 * @VXGE_HW_EVENT_RESET_COMPLETE: Device reset has been completed
 * @VXGE_HW_EVENT_SLOT_FREEZE: Slot-मुक्तze event. Driver tries to distinguish
 * slot-मुक्तze from the rest critical events (e.g. ECC) when it is
 * impossible to PIO पढ़ो "through" the bus, i.e. when getting all-foxes.
 *
 * क्रमागत vxge_hw_event क्रमागतerates slow-path HW eventis.
 *
 * See also: काष्ठा vxge_hw_uld_cbsअणुपूर्ण, vxge_uld_link_up_fअणुपूर्ण,
 * vxge_uld_link_करोwn_fअणुपूर्ण.
 */
क्रमागत vxge_hw_event अणु
	VXGE_HW_EVENT_UNKNOWN		= 0,
	/* HW events */
	VXGE_HW_EVENT_RESET_START	= VXGE_HW_EVENT_BASE + 1,
	VXGE_HW_EVENT_RESET_COMPLETE	= VXGE_HW_EVENT_BASE + 2,
	VXGE_HW_EVENT_LINK_DOWN		= VXGE_HW_EVENT_BASE + 3,
	VXGE_HW_EVENT_LINK_UP		= VXGE_HW_EVENT_BASE + 4,
	VXGE_HW_EVENT_ALARM_CLEARED	= VXGE_HW_EVENT_BASE + 5,
	VXGE_HW_EVENT_ECCERR		= VXGE_HW_EVENT_BASE + 6,
	VXGE_HW_EVENT_MRPCIM_ECCERR	= VXGE_HW_EVENT_BASE + 7,
	VXGE_HW_EVENT_FIFO_ERR		= VXGE_HW_EVENT_BASE + 8,
	VXGE_HW_EVENT_VPATH_ERR		= VXGE_HW_EVENT_BASE + 9,
	VXGE_HW_EVENT_CRITICAL_ERR	= VXGE_HW_EVENT_BASE + 10,
	VXGE_HW_EVENT_SERR		= VXGE_HW_EVENT_BASE + 11,
	VXGE_HW_EVENT_SRPCIM_SERR	= VXGE_HW_EVENT_BASE + 12,
	VXGE_HW_EVENT_MRPCIM_SERR	= VXGE_HW_EVENT_BASE + 13,
	VXGE_HW_EVENT_SLOT_FREEZE	= VXGE_HW_EVENT_BASE + 14,
पूर्ण;

#घोषणा VXGE_HW_SET_LEVEL(a, b) (((a) > (b)) ? (a) : (b))

/*
 * काष्ठा vxge_hw_mempool_dma - Represents DMA objects passed to the
	caller.
 */
काष्ठा vxge_hw_mempool_dma अणु
	dma_addr_t			addr;
	काष्ठा pci_dev *handle;
	काष्ठा pci_dev *acc_handle;
पूर्ण;

/*
 * vxge_hw_mempool_item_f  - Mempool item alloc/मुक्त callback
 * @mempoolh: Memory pool handle.
 * @memblock: Address of memory block
 * @memblock_index: Index of memory block
 * @item: Item that माला_लो allocated or मुक्तd.
 * @index: Item's index in the memory pool.
 * @is_last: True, अगर this item is the last one in the pool; false - otherwise.
 * userdata: Per-pool user context.
 *
 * Memory pool allocation/deallocation callback.
 */

/*
 * काष्ठा vxge_hw_mempool - Memory pool.
 */
काष्ठा vxge_hw_mempool अणु

	व्योम (*item_func_alloc)(
	काष्ठा vxge_hw_mempool *mempoolh,
	u32			memblock_index,
	काष्ठा vxge_hw_mempool_dma	*dma_object,
	u32			index,
	u32			is_last);

	व्योम		*userdata;
	व्योम		**memblocks_arr;
	व्योम		**memblocks_priv_arr;
	काष्ठा vxge_hw_mempool_dma	*memblocks_dma_arr;
	काष्ठा __vxge_hw_device *devh;
	u32			memblock_size;
	u32			memblocks_max;
	u32			memblocks_allocated;
	u32			item_size;
	u32			items_max;
	u32			items_initial;
	u32			items_current;
	u32			items_per_memblock;
	व्योम		**items_arr;
	u32			items_priv_size;
पूर्ण;

#घोषणा	VXGE_HW_MAX_INTR_PER_VP				4
#घोषणा	VXGE_HW_VPATH_INTR_TX				0
#घोषणा	VXGE_HW_VPATH_INTR_RX				1
#घोषणा	VXGE_HW_VPATH_INTR_EINTA			2
#घोषणा	VXGE_HW_VPATH_INTR_BMAP				3

#घोषणा VXGE_HW_BLOCK_SIZE				4096

/**
 * काष्ठा vxge_hw_tim_पूर्णांकr_config - Titan Tim पूर्णांकerrupt configuration.
 * @पूर्णांकr_enable: Set to 1, अगर पूर्णांकerrupt is enabled.
 * @bसमयr_val: Boundary Timer Initialization value in units of 272 ns.
 * @समयr_ac_en: Timer Automatic Cancel. 1 : Automatic Canceling Enable: when
 *             निश्चितed, other पूर्णांकerrupt-generating entities will cancel the
 *             scheduled समयr पूर्णांकerrupt.
 * @समयr_ci_en: Timer Continuous Interrupt. 1 : Continuous Interrupting Enable:
 *             When निश्चितed, an पूर्णांकerrupt will be generated every समय the
 *             boundary समयr expires, even अगर no traffic has been transmitted
 *             on this पूर्णांकerrupt.
 * @समयr_ri_en: Timer Consecutive (Re-) Interrupt 1 : Consecutive
 *             (Re-) Interrupt Enable: When निश्चितed, an पूर्णांकerrupt will be
 *             generated the next समय the समयr expires, even अगर no traffic has
 *             been transmitted on this पूर्णांकerrupt. (This will only happen once
 *             each समय that this value is written to the TIM.) This bit is
 *             cleared by H/W at the end of the current-समयr-पूर्णांकerval when
 *             the पूर्णांकerrupt is triggered.
 * @rसमयr_val: Restriction Timer Initialization value in units of 272 ns.
 * @util_sel: Utilization Selector. Selects which of the workload approximations
 *             to use (e.g. legacy Tx utilization, Tx/Rx utilization, host
 *             specअगरied utilization etc.), selects one of
 *             the 17 host configured values.
 *             0-Virtual Path 0
 *             1-Virtual Path 1
 *             ...
 *             16-Virtual Path 17
 *             17-Legacy Tx network utilization, provided by TPA
 *             18-Legacy Rx network utilization, provided by FAU
 *             19-Average of legacy Rx and Tx utilization calculated from link
 *                utilization values.
 *             20-31-Invalid configurations
 *             32-Host utilization क्रम Virtual Path 0
 *             33-Host utilization क्रम Virtual Path 1
 *             ...
 *             48-Host utilization क्रम Virtual Path 17
 *             49-Legacy Tx network utilization, provided by TPA
 *             50-Legacy Rx network utilization, provided by FAU
 *             51-Average of legacy Rx and Tx utilization calculated from
 *                link utilization values.
 *             52-63-Invalid configurations
 * @lसमयr_val: Latency Timer Initialization Value in units of 272 ns.
 * @txd_cnt_en: TxD Return Event Count Enable. This configuration bit when set
 *             to 1 enables counting of TxD0 वापसs (संकेतled by PCC's),
 *             towards utilization event count values.
 * @urange_a: Defines the upper limit (in percent) क्रम this utilization range
 *             to be active. This range is considered active
 *             अगर 0 = UTIL = URNG_A
 *             and the UEC_A field (below) is non-zero.
 * @uec_a: Utilization Event Count A. If this range is active, the adapter will
 *             रुको until UEC_A events have occurred on the पूर्णांकerrupt beक्रमe
 *             generating an पूर्णांकerrupt.
 * @urange_b: Link utilization range B.
 * @uec_b: Utilization Event Count B.
 * @urange_c: Link utilization range C.
 * @uec_c: Utilization Event Count C.
 * @urange_d: Link utilization range D.
 * @uec_d: Utilization Event Count D.
 * Traffic Interrupt Controller Module पूर्णांकerrupt configuration.
 */
काष्ठा vxge_hw_tim_पूर्णांकr_config अणु

	u32				पूर्णांकr_enable;
#घोषणा VXGE_HW_TIM_INTR_ENABLE				1
#घोषणा VXGE_HW_TIM_INTR_DISABLE				0
#घोषणा VXGE_HW_TIM_INTR_DEFAULT				0

	u32				bसमयr_val;
#घोषणा VXGE_HW_MIN_TIM_BTIMER_VAL				0
#घोषणा VXGE_HW_MAX_TIM_BTIMER_VAL				67108864
#घोषणा VXGE_HW_USE_FLASH_DEFAULT				(~0)

	u32				समयr_ac_en;
#घोषणा VXGE_HW_TIM_TIMER_AC_ENABLE				1
#घोषणा VXGE_HW_TIM_TIMER_AC_DISABLE				0

	u32				समयr_ci_en;
#घोषणा VXGE_HW_TIM_TIMER_CI_ENABLE				1
#घोषणा VXGE_HW_TIM_TIMER_CI_DISABLE				0

	u32				समयr_ri_en;
#घोषणा VXGE_HW_TIM_TIMER_RI_ENABLE				1
#घोषणा VXGE_HW_TIM_TIMER_RI_DISABLE				0

	u32				rसमयr_val;
#घोषणा VXGE_HW_MIN_TIM_RTIMER_VAL				0
#घोषणा VXGE_HW_MAX_TIM_RTIMER_VAL				67108864

	u32				util_sel;
#घोषणा VXGE_HW_TIM_UTIL_SEL_LEGACY_TX_NET_UTIL		17
#घोषणा VXGE_HW_TIM_UTIL_SEL_LEGACY_RX_NET_UTIL		18
#घोषणा VXGE_HW_TIM_UTIL_SEL_LEGACY_TX_RX_AVE_NET_UTIL		19
#घोषणा VXGE_HW_TIM_UTIL_SEL_PER_VPATH				63

	u32				lसमयr_val;
#घोषणा VXGE_HW_MIN_TIM_LTIMER_VAL				0
#घोषणा VXGE_HW_MAX_TIM_LTIMER_VAL				67108864

	/* Line utilization पूर्णांकerrupts */
	u32				urange_a;
#घोषणा VXGE_HW_MIN_TIM_URANGE_A				0
#घोषणा VXGE_HW_MAX_TIM_URANGE_A				100

	u32				uec_a;
#घोषणा VXGE_HW_MIN_TIM_UEC_A					0
#घोषणा VXGE_HW_MAX_TIM_UEC_A					65535

	u32				urange_b;
#घोषणा VXGE_HW_MIN_TIM_URANGE_B				0
#घोषणा VXGE_HW_MAX_TIM_URANGE_B				100

	u32				uec_b;
#घोषणा VXGE_HW_MIN_TIM_UEC_B					0
#घोषणा VXGE_HW_MAX_TIM_UEC_B					65535

	u32				urange_c;
#घोषणा VXGE_HW_MIN_TIM_URANGE_C				0
#घोषणा VXGE_HW_MAX_TIM_URANGE_C				100

	u32				uec_c;
#घोषणा VXGE_HW_MIN_TIM_UEC_C					0
#घोषणा VXGE_HW_MAX_TIM_UEC_C					65535

	u32				uec_d;
#घोषणा VXGE_HW_MIN_TIM_UEC_D					0
#घोषणा VXGE_HW_MAX_TIM_UEC_D					65535
पूर्ण;

#घोषणा	VXGE_HW_STATS_OP_READ					0
#घोषणा	VXGE_HW_STATS_OP_CLEAR_STAT				1
#घोषणा	VXGE_HW_STATS_OP_CLEAR_ALL_VPATH_STATS			2
#घोषणा	VXGE_HW_STATS_OP_CLEAR_ALL_STATS_OF_LOC			2
#घोषणा	VXGE_HW_STATS_OP_CLEAR_ALL_STATS			3

#घोषणा	VXGE_HW_STATS_LOC_AGGR					17
#घोषणा VXGE_HW_STATS_AGGRn_OFFSET				0x00720

#घोषणा VXGE_HW_STATS_VPATH_TX_OFFSET				0x0
#घोषणा VXGE_HW_STATS_VPATH_RX_OFFSET				0x00090

#घोषणा	VXGE_HW_STATS_VPATH_PROG_EVENT_VNUM0_OFFSET	   (0x001d0 >> 3)
#घोषणा	VXGE_HW_STATS_GET_VPATH_PROG_EVENT_VNUM0(bits) \
						vxge_bVALn(bits, 0, 32)

#घोषणा	VXGE_HW_STATS_GET_VPATH_PROG_EVENT_VNUM1(bits) \
						vxge_bVALn(bits, 32, 32)

#घोषणा	VXGE_HW_STATS_VPATH_PROG_EVENT_VNUM2_OFFSET	   (0x001d8 >> 3)
#घोषणा	VXGE_HW_STATS_GET_VPATH_PROG_EVENT_VNUM2(bits) \
						vxge_bVALn(bits, 0, 32)

#घोषणा	VXGE_HW_STATS_GET_VPATH_PROG_EVENT_VNUM3(bits) \
						vxge_bVALn(bits, 32, 32)

/**
 * काष्ठा vxge_hw_xmac_aggr_stats - Per-Aggregator XMAC Statistics
 *
 * @tx_frms: Count of data frames transmitted on this Aggregator on all
 *             its Aggregation ports. Does not include LACPDUs or Marker PDUs.
 *             However, करोes include frames discarded by the Distribution
 *             function.
 * @tx_data_octets: Count of data and padding octets of frames transmitted
 *             on this Aggregator on all its Aggregation ports. Does not include
 *             octets of LACPDUs or Marker PDUs. However, करोes include octets of
 *             frames discarded by the Distribution function.
 * @tx_mcast_frms: Count of data frames transmitted (to a group destination
 *             address other than the broadcast address) on this Aggregator on
 *             all its Aggregation ports. Does not include LACPDUs or Marker
 *             PDUs. However, करोes include frames discarded by the Distribution
 *             function.
 * @tx_bcast_frms: Count of broadcast data frames transmitted on this Aggregator
 *             on all its Aggregation ports. Does not include LACPDUs or Marker
 *             PDUs. However, करोes include frames discarded by the Distribution
 *             function.
 * @tx_discarded_frms: Count of data frames to be transmitted on this Aggregator
 *             that are discarded by the Distribution function. This occurs when
 *             conversation are allocated to dअगरferent ports and have to be
 *             flushed on old ports
 * @tx_errored_frms: Count of data frames transmitted on this Aggregator that
 *             experience transmission errors on its Aggregation ports.
 * @rx_frms: Count of data frames received on this Aggregator on all its
 *             Aggregation ports. Does not include LACPDUs or Marker PDUs.
 *             Also, करोes not include frames discarded by the Collection
 *             function.
 * @rx_data_octets: Count of data and padding octets of frames received on this
 *             Aggregator on all its Aggregation ports. Does not include octets
 *             of LACPDUs or Marker PDUs. Also, करोes not include
 *             octets of frames
 *             discarded by the Collection function.
 * @rx_mcast_frms: Count of data frames received (from a group destination
 *             address other than the broadcast address) on this Aggregator on
 *             all its Aggregation ports. Does not include LACPDUs or Marker
 *             PDUs. Also, करोes not include frames discarded by the Collection
 *             function.
 * @rx_bcast_frms: Count of broadcast data frames received on this Aggregator on
 *             all its Aggregation ports. Does not include LACPDUs or Marker
 *             PDUs. Also, करोes not include frames discarded by the Collection
 *             function.
 * @rx_discarded_frms: Count of data frames received on this Aggregator that are
 *             discarded by the Collection function because the Collection
 *             function was disabled on the port which the frames are received.
 * @rx_errored_frms: Count of data frames received on this Aggregator that are
 *             discarded by its Aggregation ports, or are discarded by the
 *             Collection function of the Aggregator, or that are discarded by
 *             the Aggregator due to detection of an illegal Slow Protocols PDU.
 * @rx_unknown_slow_proto_frms: Count of data frames received on this Aggregator
 *             that are discarded by its Aggregation ports due to detection of
 *             an unknown Slow Protocols PDU.
 *
 * Per aggregator XMAC RX statistics.
 */
काष्ठा vxge_hw_xmac_aggr_stats अणु
/*0x000*/		u64	tx_frms;
/*0x008*/		u64	tx_data_octets;
/*0x010*/		u64	tx_mcast_frms;
/*0x018*/		u64	tx_bcast_frms;
/*0x020*/		u64	tx_discarded_frms;
/*0x028*/		u64	tx_errored_frms;
/*0x030*/		u64	rx_frms;
/*0x038*/		u64	rx_data_octets;
/*0x040*/		u64	rx_mcast_frms;
/*0x048*/		u64	rx_bcast_frms;
/*0x050*/		u64	rx_discarded_frms;
/*0x058*/		u64	rx_errored_frms;
/*0x060*/		u64	rx_unknown_slow_proto_frms;
पूर्ण __packed;

/**
 * काष्ठा vxge_hw_xmac_port_stats - XMAC Port Statistics
 *
 * @tx_ttl_frms: Count of successfully transmitted MAC frames
 * @tx_ttl_octets: Count of total octets of transmitted frames, not including
 *            framing अक्षरacters (i.e. less framing bits). To determine the
 *            total octets of transmitted frames, including framing अक्षरacters,
 *            multiply PORTn_TX_TTL_FRMS by 8 and add it to this stat (unless
 *            otherwise configured, this stat only counts frames that have
 *            8 bytes of preamble क्रम each frame). This stat can be configured
 *            (see XMAC_STATS_GLOBAL_CFG.TTL_FRMS_HANDLING) to count everything
 *            including the preamble octets.
 * @tx_data_octets: Count of data and padding octets of successfully transmitted
 *            frames.
 * @tx_mcast_frms: Count of successfully transmitted frames to a group address
 *            other than the broadcast address.
 * @tx_bcast_frms: Count of successfully transmitted frames to the broadcast
 *            group address.
 * @tx_ucast_frms: Count of transmitted frames containing a unicast address.
 *            Includes discarded frames that are not sent to the network.
 * @tx_tagged_frms: Count of transmitted frames containing a VLAN tag.
 * @tx_vld_ip: Count of transmitted IP datagrams that are passed to the network.
 * @tx_vld_ip_octets: Count of total octets of transmitted IP datagrams that
 *            are passed to the network.
 * @tx_icmp: Count of transmitted ICMP messages. Includes messages not sent
 *            due to problems within ICMP.
 * @tx_tcp: Count of transmitted TCP segments. Does not include segments
 *            containing retransmitted octets.
 * @tx_rst_tcp: Count of transmitted TCP segments containing the RST flag.
 * @tx_udp: Count of transmitted UDP datagrams.
 * @tx_parse_error: Increments when the TPA is unable to parse a packet. This
 *            generally occurs when a packet is corrupt somehow, including
 *            packets that have IP version mismatches, invalid Layer 2 control
 *            fields, etc. L3/L4 checksums are not offloaded, but the packet
 *            is still be transmitted.
 * @tx_unknown_protocol: Increments when the TPA encounters an unknown
 *            protocol, such as a new IPv6 extension header, or an unsupported
 *            Routing Type. The packet still has a checksum calculated but it
 *            may be incorrect.
 * @tx_छोड़ो_ctrl_frms: Count of MAC PAUSE control frames that are transmitted.
 *            Since, the only control frames supported by this device are
 *            PAUSE frames, this रेजिस्टर is a count of all transmitted MAC
 *            control frames.
 * @tx_marker_pdu_frms: Count of Marker PDUs transmitted
 * on this Aggregation port.
 * @tx_lacpdu_frms: Count of LACPDUs transmitted on this Aggregation port.
 * @tx_drop_ip: Count of transmitted IP datagrams that could not be passed to
 *            the network. Increments because of:
 *            1) An पूर्णांकernal processing error
 *            (such as an uncorrectable ECC error). 2) A frame parsing error
 *            during IP checksum calculation.
 * @tx_marker_resp_pdu_frms: Count of Marker Response PDUs transmitted on this
 *            Aggregation port.
 * @tx_xgmii_अक्षर2_match: Maपूर्णांकains a count of the number of transmitted XGMII
 *            अक्षरacters that match a pattern that is programmable through
 *            रेजिस्टर XMAC_STATS_TX_XGMII_CHAR_PORTn. By शेष, the pattern
 *            is set to /T/ (i.e. the terminate अक्षरacter), thus the statistic
 *            tracks the number of transmitted Terminate अक्षरacters.
 * @tx_xgmii_अक्षर1_match: Maपूर्णांकains a count of the number of transmitted XGMII
 *            अक्षरacters that match a pattern that is programmable through
 *            रेजिस्टर XMAC_STATS_TX_XGMII_CHAR_PORTn. By शेष, the pattern
 *            is set to /S/ (i.e. the start अक्षरacter),
 *            thus the statistic tracks
 *            the number of transmitted Start अक्षरacters.
 * @tx_xgmii_column2_match: Maपूर्णांकains a count of the number of transmitted XGMII
 *            columns that match a pattern that is programmable through रेजिस्टर
 *            XMAC_STATS_TX_XGMII_COLUMN2_PORTn. By शेष, the pattern is set
 *            to 4 x /E/ (i.e. a column containing all error अक्षरacters), thus
 *            the statistic tracks the number of Error columns transmitted at
 *            any समय. If XMAC_STATS_TX_XGMII_BEHAV_COLUMN2_PORTn.NEAR_COL1 is
 *            set to 1, then this stat increments when COLUMN2 is found within
 *            'n' clocks after COLUMN1. Here, 'n' is defined by
 *            XMAC_STATS_TX_XGMII_BEHAV_COLUMN2_PORTn.NUM_COL (अगर 'n' is set
 *            to 0, then it means to search anywhere क्रम COLUMN2).
 * @tx_xgmii_column1_match: Maपूर्णांकains a count of the number of transmitted XGMII
 *            columns that match a pattern that is programmable through रेजिस्टर
 *            XMAC_STATS_TX_XGMII_COLUMN1_PORTn. By शेष, the pattern is set
 *            to 4 x /I/ (i.e. a column containing all idle अक्षरacters),
 *            thus the statistic tracks the number of transmitted Idle columns.
 * @tx_any_err_frms: Count of transmitted frames containing any error that
 *            prevents them from being passed to the network. Increments अगर
 *            there is an ECC जबतक पढ़ोing the frame out of the transmit
 *            buffer. Also increments अगर the transmit protocol assist (TPA)
 *            block determines that the frame should not be sent.
 * @tx_drop_frms: Count of frames that could not be sent क्रम no other reason
 *            than पूर्णांकernal MAC processing. Increments once whenever the
 *            transmit buffer is flushed (due to an ECC error on a memory
 *            descriptor).
 * @rx_ttl_frms: Count of total received MAC frames, including frames received
 *            with frame-too-दीर्घ, FCS, or length errors. This stat can be
 *            configured (see XMAC_STATS_GLOBAL_CFG.TTL_FRMS_HANDLING) to count
 *            everything, even "frames" as small one byte of preamble.
 * @rx_vld_frms: Count of successfully received MAC frames. Does not include
 *            frames received with frame-too-दीर्घ, FCS, or length errors.
 * @rx_offload_frms: Count of offloaded received frames that are passed to
 *            the host.
 * @rx_ttl_octets: Count of total octets of received frames, not including
 *            framing अक्षरacters (i.e. less framing bits). To determine the
 *            total octets of received frames, including framing अक्षरacters,
 *            multiply PORTn_RX_TTL_FRMS by 8 and add it to this stat (unless
 *            otherwise configured, this stat only counts frames that have 8
 *            bytes of preamble क्रम each frame). This stat can be configured
 *            (see XMAC_STATS_GLOBAL_CFG.TTL_FRMS_HANDLING) to count everything,
 *            even the preamble octets of "frames" as small one byte of preamble
 * @rx_data_octets: Count of data and padding octets of successfully received
 *            frames. Does not include frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_offload_octets: Count of total octets, not including framing
 *            अक्षरacters, of offloaded received frames that are passed
 *            to the host.
 * @rx_vld_mcast_frms: Count of successfully received MAC frames containing a
 *	      nonbroadcast group address. Does not include frames received
 *            with frame-too-दीर्घ, FCS, or length errors.
 * @rx_vld_bcast_frms: Count of successfully received MAC frames containing
 *            the broadcast group address. Does not include frames received
 *            with frame-too-दीर्घ, FCS, or length errors.
 * @rx_accepted_ucast_frms: Count of successfully received frames containing
 *            a unicast address. Only includes frames that are passed to
 *            the प्रणाली.
 * @rx_accepted_nucast_frms: Count of successfully received frames containing
 *            a non-unicast (broadcast or multicast) address. Only includes
 *            frames that are passed to the प्रणाली. Could include, क्रम instance,
 *            non-unicast frames that contain FCS errors अगर the MAC_ERROR_CFG
 *            रेजिस्टर is set to pass FCS-errored frames to the host.
 * @rx_tagged_frms: Count of received frames containing a VLAN tag.
 * @rx_दीर्घ_frms: Count of received frames that are दीर्घer than RX_MAX_PYLD_LEN
 *            + 18 bytes (+ 22 bytes अगर VLAN-tagged).
 * @rx_usized_frms: Count of received frames of length (including FCS, but not
 *            framing bits) less than 64 octets, that are otherwise well-क्रमmed.
 *            In other words, counts runts.
 * @rx_osized_frms: Count of received frames of length (including FCS, but not
 *            framing bits) more than 1518 octets, that are otherwise
 *            well-क्रमmed. Note: If रेजिस्टर XMAC_STATS_GLOBAL_CFG.VLAN_HANDLING
 *            is set to 1, then "more than 1518 octets" becomes "more than 1518
 *            (1522 अगर VLAN-tagged) octets".
 * @rx_frag_frms: Count of received frames of length (including FCS, but not
 *            framing bits) less than 64 octets that had bad FCS. In other
 *            words, counts fragments.
 * @rx_jabber_frms: Count of received frames of length (including FCS, but not
 *            framing bits) more than 1518 octets that had bad FCS. In other
 *            words, counts jabbers. Note: If रेजिस्टर
 *            XMAC_STATS_GLOBAL_CFG.VLAN_HANDLING is set to 1, then "more than
 *            1518 octets" becomes "more than 1518 (1522 अगर VLAN-tagged)
 *            octets".
 * @rx_ttl_64_frms: Count of total received MAC frames with length (including
 *            FCS, but not framing bits) of exactly 64 octets. Includes frames
 *            received with frame-too-दीर्घ, FCS, or length errors.
 * @rx_ttl_65_127_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) of between 65 and 127
 *            octets inclusive. Includes frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_ttl_128_255_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) of between 128 and 255
 *            octets inclusive. Includes frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_ttl_256_511_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) of between 256 and 511
 *            octets inclusive. Includes frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_ttl_512_1023_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) of between 512 and 1023
 *            octets inclusive. Includes frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_ttl_1024_1518_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) of between 1024 and 1518
 *            octets inclusive. Includes frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_ttl_1519_4095_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) of between 1519 and 4095
 *            octets inclusive. Includes frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_ttl_4096_8191_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) of between 4096 and 8191
 *            octets inclusive. Includes frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_ttl_8192_max_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) of between 8192 and
 *            RX_MAX_PYLD_LEN+18 octets inclusive. Includes frames received
 *            with frame-too-दीर्घ, FCS, or length errors.
 * @rx_ttl_gt_max_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) exceeding
 *            RX_MAX_PYLD_LEN+18 (+22 bytes अगर VLAN-tagged) octets inclusive.
 *            Includes frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_ip: Count of received IP datagrams. Includes errored IP datagrams.
 * @rx_accepted_ip: Count of received IP datagrams that
 * 		are passed to the प्रणाली.
 * @rx_ip_octets: Count of number of octets in received IP datagrams. Includes
 *            errored IP datagrams.
 * @rx_err_ip: 	Count of received IP datagrams containing errors. For example,
 *            bad IP checksum.
 * @rx_icmp: Count of received ICMP messages. Includes errored ICMP messages.
 * @rx_tcp: Count of received TCP segments. Includes errored TCP segments.
 *            Note: This stat contains a count of all received TCP segments,
 *            regardless of whether or not they pertain to an established
 *            connection.
 * @rx_udp: Count of received UDP datagrams.
 * @rx_err_tcp: Count of received TCP segments containing errors. For example,
 *            bad TCP checksum.
 * @rx_छोड़ो_count: Count of number of छोड़ो quanta that the MAC has been in
 *            the छोड़ोd state. Recall, one छोड़ो quantum equates to 512
 *            bit बार.
 * @rx_छोड़ो_ctrl_frms: Count of received MAC PAUSE control frames.
 * @rx_unsup_ctrl_frms: Count of received MAC control frames that करो not
 *            contain the PAUSE opcode. The sum of RX_PAUSE_CTRL_FRMS and
 *            this रेजिस्टर is a count of all received MAC control frames.
 *            Note: This stat may be configured to count all layer 2 errors
 *            (i.e. length errors and FCS errors).
 * @rx_fcs_err_frms: Count of received MAC frames that करो not pass FCS. Does
 *            not include frames received with frame-too-दीर्घ or
 *            frame-too-लघु error.
 * @rx_in_rng_len_err_frms: Count of received frames with a length/type field
 *            value between 46 (42 क्रम VLAN-tagged frames) and 1500 (also 1500
 *            क्रम VLAN-tagged frames), inclusive, that करोes not match the
 *            number of data octets (including pad) received. Also contains
 *            a count of received frames with a length/type field less than
 *            46 (42 क्रम VLAN-tagged frames) and the number of data octets
 *            (including pad) received is greater than 46 (42 क्रम VLAN-tagged
 *            frames).
 * @rx_out_rng_len_err_frms:  Count of received frames with length/type field
 *            between 1501 and 1535 decimal, inclusive.
 * @rx_drop_frms: Count of received frames that could not be passed to the host.
 *            See PORTn_RX_L2_MGMT_DISCARD, PORTn_RX_RPA_DISCARD,
 *            PORTn_RX_TRASH_DISCARD, PORTn_RX_RTS_DISCARD, PORTn_RX_RED_DISCARD
 *            क्रम a list of reasons. Because the RMAC drops one frame at a समय,
 *            this stat also indicates the number of drop events.
 * @rx_discarded_frms: Count of received frames containing
 * 		any error that prevents
 *            them from being passed to the प्रणाली. See PORTn_RX_FCS_DISCARD,
 *            PORTn_RX_LEN_DISCARD, and PORTn_RX_SWITCH_DISCARD क्रम a list of
 *            reasons.
 * @rx_drop_ip: Count of received IP datagrams that could not be passed to the
 *            host. See PORTn_RX_DROP_FRMS क्रम a list of reasons.
 * @rx_drop_udp: Count of received UDP datagrams that are not delivered to the
 *            host. See PORTn_RX_DROP_FRMS क्रम a list of reasons.
 * @rx_marker_pdu_frms: Count of valid Marker PDUs received on this Aggregation
 *            port.
 * @rx_lacpdu_frms: Count of valid LACPDUs received on this Aggregation port.
 * @rx_unknown_pdu_frms: Count of received frames (on this Aggregation port)
 *            that carry the Slow Protocols EtherType, but contain an unknown
 *            PDU. Or frames that contain the Slow Protocols group MAC address,
 *            but करो not carry the Slow Protocols EtherType.
 * @rx_marker_resp_pdu_frms: Count of valid Marker Response PDUs received on
 *            this Aggregation port.
 * @rx_fcs_discard: Count of received frames that are discarded because the
 *            FCS check failed.
 * @rx_illegal_pdu_frms: Count of received frames (on this Aggregation port)
 *            that carry the Slow Protocols EtherType, but contain a badly
 *            क्रमmed PDU. Or frames that carry the Slow Protocols EtherType,
 *            but contain an illegal value of Protocol Subtype.
 * @rx_चयन_discard: Count of received frames that are discarded by the
 *            पूर्णांकernal चयन because they did not have an entry in the
 *            Filtering Database. This includes frames that had an invalid
 *            destination MAC address or VLAN ID. It also includes frames are
 *            discarded because they did not satisfy the length requirements
 *            of the target VPATH.
 * @rx_len_discard: Count of received frames that are discarded because of an
 *            invalid frame length (includes fragments, oversized frames and
 *            mismatch between frame length and length/type field). This stat
 *            can be configured
 *            (see XMAC_STATS_GLOBAL_CFG.LEN_DISCARD_HANDLING).
 * @rx_rpa_discard: Count of received frames that were discarded because the
 *            receive protocol assist (RPA) discovered and error in the frame
 *            or was unable to parse the frame.
 * @rx_l2_mgmt_discard: Count of Layer 2 management frames (eg. छोड़ो frames,
 *            Link Aggregation Control Protocol (LACP) frames, etc.) that are
 *            discarded.
 * @rx_rts_discard: Count of received frames that are discarded by the receive
 *            traffic steering (RTS) logic. Includes those frame discarded
 *            because the SSC response contradicted the चयन table, because
 *            the SSC समयd out, or because the target queue could not fit the
 *            frame.
 * @rx_trash_discard: Count of received frames that are discarded because
 *            receive traffic steering (RTS) steered the frame to the trash
 *            queue.
 * @rx_buff_full_discard: Count of received frames that are discarded because
 *            पूर्णांकernal buffers are full. Includes frames discarded because the
 *            RTS logic is रुकोing क्रम an SSC lookup that has no समयout bound.
 *            Also, includes frames that are dropped because the MAC2FAU buffer
 *            is nearly full -- this can happen अगर the बाह्यal receive buffer
 *            is full and the receive path is backing up.
 * @rx_red_discard: Count of received frames that are discarded because of RED
 *            (Ranकरोm Early Discard).
 * @rx_xgmii_ctrl_err_cnt: Maपूर्णांकains a count of unexpected or misplaced control
 *            अक्षरacters occurring between बार of normal data transmission
 *            (i.e. not included in RX_XGMII_DATA_ERR_CNT). This counter is
 *            incremented when either -
 *            1) The Reconciliation Sublayer (RS) is expecting one control
 *               अक्षरacter and माला_लो another (i.e. is expecting a Start
 *               अक्षरacter, but माला_लो another control अक्षरacter).
 *            2) Start control अक्षरacter is not in lane 0
 *            Only increments the count by one क्रम each XGMII column.
 * @rx_xgmii_data_err_cnt: Maपूर्णांकains a count of unexpected control अक्षरacters
 *            during normal data transmission. If the Reconciliation Sublayer
 *            (RS) receives a control अक्षरacter, other than a terminate control
 *            अक्षरacter, during receipt of data octets then this रेजिस्टर is
 *            incremented. Also increments अगर the start frame delimiter is not
 *            found in the correct location. Only increments the count by one
 *            क्रम each XGMII column.
 * @rx_xgmii_अक्षर1_match: Maपूर्णांकains a count of the number of XGMII अक्षरacters
 *            that match a pattern that is programmable through रेजिस्टर
 *            XMAC_STATS_RX_XGMII_CHAR_PORTn. By शेष, the pattern is set
 *            to /E/ (i.e. the error अक्षरacter), thus the statistic tracks the
 *            number of Error अक्षरacters received at any समय.
 * @rx_xgmii_err_sym: Count of the number of symbol errors in the received
 *            XGMII data (i.e. PHY indicates "Receive Error" on the XGMII).
 *            Only includes symbol errors that are observed between the XGMII
 *            Start Frame Delimiter and End Frame Delimiter, inclusive. And
 *            only increments the count by one क्रम each frame.
 * @rx_xgmii_column1_match: Maपूर्णांकains a count of the number of XGMII columns
 *            that match a pattern that is programmable through रेजिस्टर
 *            XMAC_STATS_RX_XGMII_COLUMN1_PORTn. By शेष, the pattern is set
 *            to 4 x /E/ (i.e. a column containing all error अक्षरacters), thus
 *            the statistic tracks the number of Error columns received at any
 *            समय.
 * @rx_xgmii_अक्षर2_match: Maपूर्णांकains a count of the number of XGMII अक्षरacters
 *            that match a pattern that is programmable through रेजिस्टर
 *            XMAC_STATS_RX_XGMII_CHAR_PORTn. By शेष, the pattern is set
 *            to /E/ (i.e. the error अक्षरacter), thus the statistic tracks the
 *            number of Error अक्षरacters received at any समय.
 * @rx_local_fault: Maपूर्णांकains a count of the number of बार that link
 *            transitioned from "up" to "down" due to a local fault.
 * @rx_xgmii_column2_match: Maपूर्णांकains a count of the number of XGMII columns
 *            that match a pattern that is programmable through रेजिस्टर
 *            XMAC_STATS_RX_XGMII_COLUMN2_PORTn. By शेष, the pattern is set
 *            to 4 x /E/ (i.e. a column containing all error अक्षरacters), thus
 *            the statistic tracks the number of Error columns received at any
 *            समय. If XMAC_STATS_RX_XGMII_BEHAV_COLUMN2_PORTn.NEAR_COL1 is set
 *            to 1, then this stat increments when COLUMN2 is found within 'n'
 *            घड़ीs after COLUMN1. Here, 'n' is defined by
 *            XMAC_STATS_RX_XGMII_BEHAV_COLUMN2_PORTn.NUM_COL (अगर 'n' is set to
 *            0, then it means to search anywhere क्रम COLUMN2).
 * @rx_jettison: Count of received frames that are jettisoned because पूर्णांकernal
 *            buffers are full.
 * @rx_remote_fault: Maपूर्णांकains a count of the number of बार that link
 *            transitioned from "up" to "down" due to a remote fault.
 *
 * XMAC Port Statistics.
 */
काष्ठा vxge_hw_xmac_port_stats अणु
/*0x000*/		u64	tx_ttl_frms;
/*0x008*/		u64	tx_ttl_octets;
/*0x010*/		u64	tx_data_octets;
/*0x018*/		u64	tx_mcast_frms;
/*0x020*/		u64	tx_bcast_frms;
/*0x028*/		u64	tx_ucast_frms;
/*0x030*/		u64	tx_tagged_frms;
/*0x038*/		u64	tx_vld_ip;
/*0x040*/		u64	tx_vld_ip_octets;
/*0x048*/		u64	tx_icmp;
/*0x050*/		u64	tx_tcp;
/*0x058*/		u64	tx_rst_tcp;
/*0x060*/		u64	tx_udp;
/*0x068*/		u32	tx_parse_error;
/*0x06c*/		u32	tx_unknown_protocol;
/*0x070*/		u64	tx_छोड़ो_ctrl_frms;
/*0x078*/		u32	tx_marker_pdu_frms;
/*0x07c*/		u32	tx_lacpdu_frms;
/*0x080*/		u32	tx_drop_ip;
/*0x084*/		u32	tx_marker_resp_pdu_frms;
/*0x088*/		u32	tx_xgmii_अक्षर2_match;
/*0x08c*/		u32	tx_xgmii_अक्षर1_match;
/*0x090*/		u32	tx_xgmii_column2_match;
/*0x094*/		u32	tx_xgmii_column1_match;
/*0x098*/		u32	unused1;
/*0x09c*/		u16	tx_any_err_frms;
/*0x09e*/		u16	tx_drop_frms;
/*0x0a0*/		u64	rx_ttl_frms;
/*0x0a8*/		u64	rx_vld_frms;
/*0x0b0*/		u64	rx_offload_frms;
/*0x0b8*/		u64	rx_ttl_octets;
/*0x0c0*/		u64	rx_data_octets;
/*0x0c8*/		u64	rx_offload_octets;
/*0x0d0*/		u64	rx_vld_mcast_frms;
/*0x0d8*/		u64	rx_vld_bcast_frms;
/*0x0e0*/		u64	rx_accepted_ucast_frms;
/*0x0e8*/		u64	rx_accepted_nucast_frms;
/*0x0f0*/		u64	rx_tagged_frms;
/*0x0f8*/		u64	rx_दीर्घ_frms;
/*0x100*/		u64	rx_usized_frms;
/*0x108*/		u64	rx_osized_frms;
/*0x110*/		u64	rx_frag_frms;
/*0x118*/		u64	rx_jabber_frms;
/*0x120*/		u64	rx_ttl_64_frms;
/*0x128*/		u64	rx_ttl_65_127_frms;
/*0x130*/		u64	rx_ttl_128_255_frms;
/*0x138*/		u64	rx_ttl_256_511_frms;
/*0x140*/		u64	rx_ttl_512_1023_frms;
/*0x148*/		u64	rx_ttl_1024_1518_frms;
/*0x150*/		u64	rx_ttl_1519_4095_frms;
/*0x158*/		u64	rx_ttl_4096_8191_frms;
/*0x160*/		u64	rx_ttl_8192_max_frms;
/*0x168*/		u64	rx_ttl_gt_max_frms;
/*0x170*/		u64	rx_ip;
/*0x178*/		u64	rx_accepted_ip;
/*0x180*/		u64	rx_ip_octets;
/*0x188*/		u64	rx_err_ip;
/*0x190*/		u64	rx_icmp;
/*0x198*/		u64	rx_tcp;
/*0x1a0*/		u64	rx_udp;
/*0x1a8*/		u64	rx_err_tcp;
/*0x1b0*/		u64	rx_छोड़ो_count;
/*0x1b8*/		u64	rx_छोड़ो_ctrl_frms;
/*0x1c0*/		u64	rx_unsup_ctrl_frms;
/*0x1c8*/		u64	rx_fcs_err_frms;
/*0x1d0*/		u64	rx_in_rng_len_err_frms;
/*0x1d8*/		u64	rx_out_rng_len_err_frms;
/*0x1e0*/		u64	rx_drop_frms;
/*0x1e8*/		u64	rx_discarded_frms;
/*0x1f0*/		u64	rx_drop_ip;
/*0x1f8*/		u64	rx_drop_udp;
/*0x200*/		u32	rx_marker_pdu_frms;
/*0x204*/		u32	rx_lacpdu_frms;
/*0x208*/		u32	rx_unknown_pdu_frms;
/*0x20c*/		u32	rx_marker_resp_pdu_frms;
/*0x210*/		u32	rx_fcs_discard;
/*0x214*/		u32	rx_illegal_pdu_frms;
/*0x218*/		u32	rx_चयन_discard;
/*0x21c*/		u32	rx_len_discard;
/*0x220*/		u32	rx_rpa_discard;
/*0x224*/		u32	rx_l2_mgmt_discard;
/*0x228*/		u32	rx_rts_discard;
/*0x22c*/		u32	rx_trash_discard;
/*0x230*/		u32	rx_buff_full_discard;
/*0x234*/		u32	rx_red_discard;
/*0x238*/		u32	rx_xgmii_ctrl_err_cnt;
/*0x23c*/		u32	rx_xgmii_data_err_cnt;
/*0x240*/		u32	rx_xgmii_अक्षर1_match;
/*0x244*/		u32	rx_xgmii_err_sym;
/*0x248*/		u32	rx_xgmii_column1_match;
/*0x24c*/		u32	rx_xgmii_अक्षर2_match;
/*0x250*/		u32	rx_local_fault;
/*0x254*/		u32	rx_xgmii_column2_match;
/*0x258*/		u32	rx_jettison;
/*0x25c*/		u32	rx_remote_fault;
पूर्ण __packed;

/**
 * काष्ठा vxge_hw_xmac_vpath_tx_stats - XMAC Vpath Tx Statistics
 *
 * @tx_ttl_eth_frms: Count of successfully transmitted MAC frames.
 * @tx_ttl_eth_octets: Count of total octets of transmitted frames,
 *             not including framing अक्षरacters (i.e. less framing bits).
 *             To determine the total octets of transmitted frames, including
 *             framing अक्षरacters, multiply TX_TTL_ETH_FRMS by 8 and add it to
 *             this stat (the device always prepends 8 bytes of preamble क्रम
 *             each frame)
 * @tx_data_octets: Count of data and padding octets of successfully transmitted
 *             frames.
 * @tx_mcast_frms: Count of successfully transmitted frames to a group address
 *             other than the broadcast address.
 * @tx_bcast_frms: Count of successfully transmitted frames to the broadcast
 *             group address.
 * @tx_ucast_frms: Count of transmitted frames containing a unicast address.
 *             Includes discarded frames that are not sent to the network.
 * @tx_tagged_frms: Count of transmitted frames containing a VLAN tag.
 * @tx_vld_ip: Count of transmitted IP datagrams that are passed to the network.
 * @tx_vld_ip_octets: Count of total octets of transmitted IP datagrams that
 *            are passed to the network.
 * @tx_icmp: Count of transmitted ICMP messages. Includes messages not sent due
 *            to problems within ICMP.
 * @tx_tcp: Count of transmitted TCP segments. Does not include segments
 *            containing retransmitted octets.
 * @tx_rst_tcp: Count of transmitted TCP segments containing the RST flag.
 * @tx_udp: Count of transmitted UDP datagrams.
 * @tx_unknown_protocol: Increments when the TPA encounters an unknown protocol,
 *            such as a new IPv6 extension header, or an unsupported Routing
 *            Type. The packet still has a checksum calculated but it may be
 *            incorrect.
 * @tx_lost_ip: Count of transmitted IP datagrams that could not be passed
 *            to the network. Increments because of: 1) An पूर्णांकernal processing
 *            error (such as an uncorrectable ECC error). 2) A frame parsing
 *            error during IP checksum calculation.
 * @tx_parse_error: Increments when the TPA is unable to parse a packet. This
 *            generally occurs when a packet is corrupt somehow, including
 *            packets that have IP version mismatches, invalid Layer 2 control
 *            fields, etc. L3/L4 checksums are not offloaded, but the packet
 *            is still be transmitted.
 * @tx_tcp_offload: For frames beदीर्घing to offloaded sessions only, a count
 *            of transmitted TCP segments. Does not include segments containing
 *            retransmitted octets.
 * @tx_retx_tcp_offload: For frames beदीर्घing to offloaded sessions only, the
 *            total number of segments retransmitted. Retransmitted segments
 *            that are sourced by the host are counted by the host.
 * @tx_lost_ip_offload: For frames beदीर्घing to offloaded sessions only, a count
 *            of transmitted IP datagrams that could not be passed to the
 *            network.
 *
 * XMAC Vpath TX Statistics.
 */
काष्ठा vxge_hw_xmac_vpath_tx_stats अणु
	u64	tx_ttl_eth_frms;
	u64	tx_ttl_eth_octets;
	u64	tx_data_octets;
	u64	tx_mcast_frms;
	u64	tx_bcast_frms;
	u64	tx_ucast_frms;
	u64	tx_tagged_frms;
	u64	tx_vld_ip;
	u64	tx_vld_ip_octets;
	u64	tx_icmp;
	u64	tx_tcp;
	u64	tx_rst_tcp;
	u64	tx_udp;
	u32	tx_unknown_protocol;
	u32	tx_lost_ip;
	u32	unused1;
	u32	tx_parse_error;
	u64	tx_tcp_offload;
	u64	tx_retx_tcp_offload;
	u64	tx_lost_ip_offload;
पूर्ण __packed;

/**
 * काष्ठा vxge_hw_xmac_vpath_rx_stats - XMAC Vpath RX Statistics
 *
 * @rx_ttl_eth_frms: Count of successfully received MAC frames.
 * @rx_vld_frms: Count of successfully received MAC frames. Does not include
 *            frames received with frame-too-दीर्घ, FCS, or length errors.
 * @rx_offload_frms: Count of offloaded received frames that are passed to
 *            the host.
 * @rx_ttl_eth_octets: Count of total octets of received frames, not including
 *            framing अक्षरacters (i.e. less framing bits). Only counts octets
 *            of frames that are at least 14 bytes (18 bytes क्रम VLAN-tagged)
 *            beक्रमe FCS. To determine the total octets of received frames,
 *            including framing अक्षरacters, multiply RX_TTL_ETH_FRMS by 8 and
 *            add it to this stat (the stat RX_TTL_ETH_FRMS only counts frames
 *            that have the required 8 bytes of preamble).
 * @rx_data_octets: Count of data and padding octets of successfully received
 *            frames. Does not include frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_offload_octets: Count of total octets, not including framing अक्षरacters,
 *            of offloaded received frames that are passed to the host.
 * @rx_vld_mcast_frms: Count of successfully received MAC frames containing a
 *            nonbroadcast group address. Does not include frames received with
 *            frame-too-दीर्घ, FCS, or length errors.
 * @rx_vld_bcast_frms: Count of successfully received MAC frames containing the
 *            broadcast group address. Does not include frames received with
 *            frame-too-दीर्घ, FCS, or length errors.
 * @rx_accepted_ucast_frms: Count of successfully received frames containing
 *            a unicast address. Only includes frames that are passed to the
 *            प्रणाली.
 * @rx_accepted_nucast_frms: Count of successfully received frames containing
 *            a non-unicast (broadcast or multicast) address. Only includes
 *            frames that are passed to the प्रणाली. Could include, क्रम instance,
 *            non-unicast frames that contain FCS errors अगर the MAC_ERROR_CFG
 *            रेजिस्टर is set to pass FCS-errored frames to the host.
 * @rx_tagged_frms: Count of received frames containing a VLAN tag.
 * @rx_दीर्घ_frms: Count of received frames that are दीर्घer than RX_MAX_PYLD_LEN
 *            + 18 bytes (+ 22 bytes अगर VLAN-tagged).
 * @rx_usized_frms: Count of received frames of length (including FCS, but not
 *            framing bits) less than 64 octets, that are otherwise well-क्रमmed.
 *            In other words, counts runts.
 * @rx_osized_frms: Count of received frames of length (including FCS, but not
 *            framing bits) more than 1518 octets, that are otherwise
 *            well-क्रमmed.
 * @rx_frag_frms: Count of received frames of length (including FCS, but not
 *            framing bits) less than 64 octets that had bad FCS.
 *            In other words, counts fragments.
 * @rx_jabber_frms: Count of received frames of length (including FCS, but not
 *            framing bits) more than 1518 octets that had bad FCS. In other
 *            words, counts jabbers.
 * @rx_ttl_64_frms: Count of total received MAC frames with length (including
 *            FCS, but not framing bits) of exactly 64 octets. Includes frames
 *            received with frame-too-दीर्घ, FCS, or length errors.
 * @rx_ttl_65_127_frms: Count of total received MAC frames
 * 		with length (including
 *            FCS, but not framing bits) of between 65 and 127 octets inclusive.
 *            Includes frames received with frame-too-दीर्घ, FCS,
 *            or length errors.
 * @rx_ttl_128_255_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits)
 *            of between 128 and 255 octets
 *            inclusive. Includes frames received with frame-too-दीर्घ, FCS,
 *            or length errors.
 * @rx_ttl_256_511_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits)
 *            of between 256 and 511 octets
 *            inclusive. Includes frames received with frame-too-दीर्घ, FCS, or
 *            length errors.
 * @rx_ttl_512_1023_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) of between 512 and 1023
 *            octets inclusive. Includes frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_ttl_1024_1518_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) of between 1024 and 1518
 *            octets inclusive. Includes frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_ttl_1519_4095_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) of between 1519 and 4095
 *            octets inclusive. Includes frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_ttl_4096_8191_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) of between 4096 and 8191
 *            octets inclusive. Includes frames received with frame-too-दीर्घ,
 *            FCS, or length errors.
 * @rx_ttl_8192_max_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) of between 8192 and
 *            RX_MAX_PYLD_LEN+18 octets inclusive. Includes frames received
 *            with frame-too-दीर्घ, FCS, or length errors.
 * @rx_ttl_gt_max_frms: Count of total received MAC frames with length
 *            (including FCS, but not framing bits) exceeding RX_MAX_PYLD_LEN+18
 *            (+22 bytes अगर VLAN-tagged) octets inclusive. Includes frames
 *            received with frame-too-दीर्घ, FCS, or length errors.
 * @rx_ip: Count of received IP datagrams. Includes errored IP datagrams.
 * @rx_accepted_ip: Count of received IP datagrams that
 * 		are passed to the प्रणाली.
 * @rx_ip_octets: Count of number of octets in received IP datagrams.
 *            Includes errored IP datagrams.
 * @rx_err_ip: Count of received IP datagrams containing errors. For example,
 *            bad IP checksum.
 * @rx_icmp: Count of received ICMP messages. Includes errored ICMP messages.
 * @rx_tcp: Count of received TCP segments. Includes errored TCP segments.
 *             Note: This stat contains a count of all received TCP segments,
 *             regardless of whether or not they pertain to an established
 *             connection.
 * @rx_udp: Count of received UDP datagrams.
 * @rx_err_tcp: Count of received TCP segments containing errors. For example,
 *             bad TCP checksum.
 * @rx_lost_frms: Count of received frames that could not be passed to the host.
 *             See RX_QUEUE_FULL_DISCARD and RX_RED_DISCARD
 *             क्रम a list of reasons.
 * @rx_lost_ip: Count of received IP datagrams that could not be passed to
 *             the host. See RX_LOST_FRMS क्रम a list of reasons.
 * @rx_lost_ip_offload: For frames beदीर्घing to offloaded sessions only, a count
 *             of received IP datagrams that could not be passed to the host.
 *             See RX_LOST_FRMS क्रम a list of reasons.
 * @rx_various_discard: Count of received frames that are discarded because
 *             the target receive queue is full.
 * @rx_sleep_discard: Count of received frames that are discarded because the
 *            target VPATH is asleep (a Wake-on-LAN magic packet can be used
 *            to awaken the VPATH).
 * @rx_red_discard: Count of received frames that are discarded because of RED
 *            (Ranकरोm Early Discard).
 * @rx_queue_full_discard: Count of received frames that are discarded because
 *             the target receive queue is full.
 * @rx_mpa_ok_frms: Count of received frames that pass the MPA checks.
 *
 * XMAC Vpath RX Statistics.
 */
काष्ठा vxge_hw_xmac_vpath_rx_stats अणु
	u64	rx_ttl_eth_frms;
	u64	rx_vld_frms;
	u64	rx_offload_frms;
	u64	rx_ttl_eth_octets;
	u64	rx_data_octets;
	u64	rx_offload_octets;
	u64	rx_vld_mcast_frms;
	u64	rx_vld_bcast_frms;
	u64	rx_accepted_ucast_frms;
	u64	rx_accepted_nucast_frms;
	u64	rx_tagged_frms;
	u64	rx_दीर्घ_frms;
	u64	rx_usized_frms;
	u64	rx_osized_frms;
	u64	rx_frag_frms;
	u64	rx_jabber_frms;
	u64	rx_ttl_64_frms;
	u64	rx_ttl_65_127_frms;
	u64	rx_ttl_128_255_frms;
	u64	rx_ttl_256_511_frms;
	u64	rx_ttl_512_1023_frms;
	u64	rx_ttl_1024_1518_frms;
	u64	rx_ttl_1519_4095_frms;
	u64	rx_ttl_4096_8191_frms;
	u64	rx_ttl_8192_max_frms;
	u64	rx_ttl_gt_max_frms;
	u64	rx_ip;
	u64	rx_accepted_ip;
	u64	rx_ip_octets;
	u64	rx_err_ip;
	u64	rx_icmp;
	u64	rx_tcp;
	u64	rx_udp;
	u64	rx_err_tcp;
	u64	rx_lost_frms;
	u64	rx_lost_ip;
	u64	rx_lost_ip_offload;
	u16	rx_various_discard;
	u16	rx_sleep_discard;
	u16	rx_red_discard;
	u16	rx_queue_full_discard;
	u64	rx_mpa_ok_frms;
पूर्ण __packed;

/**
 * काष्ठा vxge_hw_xmac_stats - XMAC Statistics
 *
 * @aggr_stats: Statistics on aggregate port(port 0, port 1)
 * @port_stats: Staticstics on ports(wire 0, wire 1, lag)
 * @vpath_tx_stats: Per vpath XMAC TX stats
 * @vpath_rx_stats: Per vpath XMAC RX stats
 *
 * XMAC Statistics.
 */
काष्ठा vxge_hw_xmac_stats अणु
	काष्ठा vxge_hw_xmac_aggr_stats
				aggr_stats[VXGE_HW_MAC_MAX_MAC_PORT_ID];
	काष्ठा vxge_hw_xmac_port_stats
				port_stats[VXGE_HW_MAC_MAX_MAC_PORT_ID+1];
	काष्ठा vxge_hw_xmac_vpath_tx_stats
				vpath_tx_stats[VXGE_HW_MAX_VIRTUAL_PATHS];
	काष्ठा vxge_hw_xmac_vpath_rx_stats
				vpath_rx_stats[VXGE_HW_MAX_VIRTUAL_PATHS];
पूर्ण;

/**
 * काष्ठा vxge_hw_vpath_stats_hw_info - Titan vpath hardware statistics.
 * @ini_num_mwr_sent: The number of PCI memory ग_लिखोs initiated by the PIC block
 *             क्रम the given VPATH
 * @ini_num_mrd_sent: The number of PCI memory पढ़ोs initiated by the PIC block
 * @ini_num_cpl_rcvd: The number of PCI पढ़ो completions received by the
 *             PIC block
 * @ini_num_mwr_byte_sent: The number of PCI memory ग_लिखो bytes sent by the PIC
 *             block to the host
 * @ini_num_cpl_byte_rcvd: The number of PCI पढ़ो completion bytes received by
 *             the PIC block
 * @wrcrdtarb_xoff: TBD
 * @rdcrdtarb_xoff: TBD
 * @vpath_genstats_count0: TBD
 * @vpath_genstats_count1: TBD
 * @vpath_genstats_count2: TBD
 * @vpath_genstats_count3: TBD
 * @vpath_genstats_count4: TBD
 * @vpath_gennstats_count5: TBD
 * @tx_stats: Transmit stats
 * @rx_stats: Receive stats
 * @prog_event_vnum1: Programmable statistic. Increments when पूर्णांकernal logic
 *             detects a certain event. See रेजिस्टर
 *             XMAC_STATS_CFG.EVENT_VNUM1_CFG क्रम more inक्रमmation.
 * @prog_event_vnum0: Programmable statistic. Increments when पूर्णांकernal logic
 *             detects a certain event. See रेजिस्टर
 *             XMAC_STATS_CFG.EVENT_VNUM0_CFG क्रम more inक्रमmation.
 * @prog_event_vnum3: Programmable statistic. Increments when पूर्णांकernal logic
 *             detects a certain event. See रेजिस्टर
 *             XMAC_STATS_CFG.EVENT_VNUM3_CFG क्रम more inक्रमmation.
 * @prog_event_vnum2: Programmable statistic. Increments when पूर्णांकernal logic
 *             detects a certain event. See रेजिस्टर
 *             XMAC_STATS_CFG.EVENT_VNUM2_CFG क्रम more inक्रमmation.
 * @rx_multi_cast_frame_discard: TBD
 * @rx_frm_transferred: TBD
 * @rxd_वापसed: TBD
 * @rx_mpa_len_fail_frms: Count of received frames
 * 		that fail the MPA length check
 * @rx_mpa_mrk_fail_frms: Count of received frames
 * 		that fail the MPA marker check
 * @rx_mpa_crc_fail_frms: Count of received frames that fail the MPA CRC check
 * @rx_permitted_frms: Count of frames that pass through the FAU and on to the
 *             frame buffer (and subsequently to the host).
 * @rx_vp_reset_discarded_frms: Count of receive frames that are discarded
 *             because the VPATH is in reset
 * @rx_wol_frms: Count of received "magic packet" frames. Stat increments
 *             whenever the received frame matches the VPATH's Wake-on-LAN
 *             signature(s) CRC.
 * @tx_vp_reset_discarded_frms: Count of transmit frames that are discarded
 *             because the VPATH is in reset. Includes frames that are discarded
 *             because the current VPIN करोes not match that VPIN of the frame
 *
 * Titan vpath hardware statistics.
 */
काष्ठा vxge_hw_vpath_stats_hw_info अणु
/*0x000*/	u32 ini_num_mwr_sent;
/*0x004*/	u32 unused1;
/*0x008*/	u32 ini_num_mrd_sent;
/*0x00c*/	u32 unused2;
/*0x010*/	u32 ini_num_cpl_rcvd;
/*0x014*/	u32 unused3;
/*0x018*/	u64 ini_num_mwr_byte_sent;
/*0x020*/	u64 ini_num_cpl_byte_rcvd;
/*0x028*/	u32 wrcrdtarb_xoff;
/*0x02c*/	u32 unused4;
/*0x030*/	u32 rdcrdtarb_xoff;
/*0x034*/	u32 unused5;
/*0x038*/	u32 vpath_genstats_count0;
/*0x03c*/	u32 vpath_genstats_count1;
/*0x040*/	u32 vpath_genstats_count2;
/*0x044*/	u32 vpath_genstats_count3;
/*0x048*/	u32 vpath_genstats_count4;
/*0x04c*/	u32 unused6;
/*0x050*/	u32 vpath_genstats_count5;
/*0x054*/	u32 unused7;
/*0x058*/	काष्ठा vxge_hw_xmac_vpath_tx_stats tx_stats;
/*0x0e8*/	काष्ठा vxge_hw_xmac_vpath_rx_stats rx_stats;
/*0x220*/	u64 unused9;
/*0x228*/	u32 prog_event_vnum1;
/*0x22c*/	u32 prog_event_vnum0;
/*0x230*/	u32 prog_event_vnum3;
/*0x234*/	u32 prog_event_vnum2;
/*0x238*/	u16 rx_multi_cast_frame_discard;
/*0x23a*/	u8 unused10[6];
/*0x240*/	u32 rx_frm_transferred;
/*0x244*/	u32 unused11;
/*0x248*/	u16 rxd_वापसed;
/*0x24a*/	u8 unused12[6];
/*0x252*/	u16 rx_mpa_len_fail_frms;
/*0x254*/	u16 rx_mpa_mrk_fail_frms;
/*0x256*/	u16 rx_mpa_crc_fail_frms;
/*0x258*/	u16 rx_permitted_frms;
/*0x25c*/	u64 rx_vp_reset_discarded_frms;
/*0x25e*/	u64 rx_wol_frms;
/*0x260*/	u64 tx_vp_reset_discarded_frms;
पूर्ण __packed;


/**
 * काष्ठा vxge_hw_device_stats_mrpcim_info - Titan mrpcim hardware statistics.
 * @pic.ini_rd_drop  	 0x0000  	 4  	 Number of DMA पढ़ोs initiated
 *  by the adapter that were discarded because the VPATH is out of service
 * @pic.ini_wr_drop 	0x0004 	4 	Number of DMA ग_लिखोs initiated by the
 *  adapter that were discared because the VPATH is out of service
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane0] 	0x0008 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane1] 	0x0010 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane2] 	0x0018 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane3] 	0x0020 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane4] 	0x0028 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane5] 	0x0030 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane6] 	0x0038 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane7] 	0x0040 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane8] 	0x0048 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane9] 	0x0050 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane10] 	0x0058 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane11] 	0x0060 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane12] 	0x0068 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane13] 	0x0070 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane14] 	0x0078 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane15] 	0x0080 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_ph_crdt_depleted[vplane16] 	0x0088 	4 	Number of बार
 *  the posted header credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane0] 	0x0090 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane1] 	0x0098 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane2] 	0x00a0 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane3] 	0x00a8 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane4] 	0x00b0 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane5] 	0x00b8 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane6] 	0x00c0 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane7] 	0x00c8 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane8] 	0x00d0 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane9] 	0x00d8 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane10] 	0x00e0 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane11] 	0x00e8 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane12] 	0x00f0 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane13] 	0x00f8 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane14] 	0x0100 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane15] 	0x0108 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.wrcrdtarb_pd_crdt_depleted[vplane16] 	0x0110 	4 	Number of बार
 *  the posted data credits क्रम upstream PCI ग_लिखोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane0] 	0x0118 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane1] 	0x0120 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane2] 	0x0128 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane3] 	0x0130 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane4] 	0x0138 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane5] 	0x0140 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane6] 	0x0148 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane7] 	0x0150 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane8] 	0x0158 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane9] 	0x0160 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane10] 	0x0168 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane11] 	0x0170 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane12] 	0x0178 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane13] 	0x0180 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane14] 	0x0188 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane15] 	0x0190 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.rdcrdtarb_nph_crdt_depleted[vplane16] 	0x0198 	4 	Number of बार
 *  the non-posted header credits क्रम upstream PCI पढ़ोs were depleted
 * @pic.ini_rd_vpin_drop 	0x01a0 	4 	Number of DMA पढ़ोs initiated by
 *  the adapter that were discarded because the VPATH instance number करोes
 *  not match
 * @pic.ini_wr_vpin_drop 	0x01a4 	4 	Number of DMA ग_लिखोs initiated
 *  by the adapter that were discarded because the VPATH instance number
 *  करोes not match
 * @pic.genstats_count0 	0x01a8 	4 	Configurable statistic #1. Refer
 *  to the GENSTATS0_CFG क्रम inक्रमmation on configuring this statistic
 * @pic.genstats_count1 	0x01ac 	4 	Configurable statistic #2. Refer
 *  to the GENSTATS1_CFG क्रम inक्रमmation on configuring this statistic
 * @pic.genstats_count2 	0x01b0 	4 	Configurable statistic #3. Refer
 *  to the GENSTATS2_CFG क्रम inक्रमmation on configuring this statistic
 * @pic.genstats_count3 	0x01b4 	4 	Configurable statistic #4. Refer
 *  to the GENSTATS3_CFG क्रम inक्रमmation on configuring this statistic
 * @pic.genstats_count4 	0x01b8 	4 	Configurable statistic #5. Refer
 *  to the GENSTATS4_CFG क्रम inक्रमmation on configuring this statistic
 * @pic.genstats_count5 	0x01c0 	4 	Configurable statistic #6. Refer
 *  to the GENSTATS5_CFG क्रम inक्रमmation on configuring this statistic
 * @pci.rstdrop_cpl 	0x01c8 	4
 * @pci.rstdrop_msg 	0x01cc 	4
 * @pci.rstdrop_client1 	0x01d0 	4
 * @pci.rstdrop_client0 	0x01d4 	4
 * @pci.rstdrop_client2 	0x01d8 	4
 * @pci.depl_cplh[vplane0] 	0x01e2 	2 	Number of बार completion
 *  header credits were depleted
 * @pci.depl_nph[vplane0] 	0x01e4 	2 	Number of बार non posted
 *  header credits were depleted
 * @pci.depl_ph[vplane0] 	0x01e6 	2 	Number of बार the posted
 *  header credits were depleted
 * @pci.depl_cplh[vplane1] 	0x01ea 	2
 * @pci.depl_nph[vplane1] 	0x01ec 	2
 * @pci.depl_ph[vplane1] 	0x01ee 	2
 * @pci.depl_cplh[vplane2] 	0x01f2 	2
 * @pci.depl_nph[vplane2] 	0x01f4 	2
 * @pci.depl_ph[vplane2] 	0x01f6 	2
 * @pci.depl_cplh[vplane3] 	0x01fa 	2
 * @pci.depl_nph[vplane3] 	0x01fc 	2
 * @pci.depl_ph[vplane3] 	0x01fe 	2
 * @pci.depl_cplh[vplane4] 	0x0202 	2
 * @pci.depl_nph[vplane4] 	0x0204 	2
 * @pci.depl_ph[vplane4] 	0x0206 	2
 * @pci.depl_cplh[vplane5] 	0x020a 	2
 * @pci.depl_nph[vplane5] 	0x020c 	2
 * @pci.depl_ph[vplane5] 	0x020e 	2
 * @pci.depl_cplh[vplane6] 	0x0212 	2
 * @pci.depl_nph[vplane6] 	0x0214 	2
 * @pci.depl_ph[vplane6] 	0x0216 	2
 * @pci.depl_cplh[vplane7] 	0x021a 	2
 * @pci.depl_nph[vplane7] 	0x021c 	2
 * @pci.depl_ph[vplane7] 	0x021e 	2
 * @pci.depl_cplh[vplane8] 	0x0222 	2
 * @pci.depl_nph[vplane8] 	0x0224 	2
 * @pci.depl_ph[vplane8] 	0x0226 	2
 * @pci.depl_cplh[vplane9] 	0x022a 	2
 * @pci.depl_nph[vplane9] 	0x022c 	2
 * @pci.depl_ph[vplane9] 	0x022e 	2
 * @pci.depl_cplh[vplane10] 	0x0232 	2
 * @pci.depl_nph[vplane10] 	0x0234 	2
 * @pci.depl_ph[vplane10] 	0x0236 	2
 * @pci.depl_cplh[vplane11] 	0x023a 	2
 * @pci.depl_nph[vplane11] 	0x023c 	2
 * @pci.depl_ph[vplane11] 	0x023e 	2
 * @pci.depl_cplh[vplane12] 	0x0242 	2
 * @pci.depl_nph[vplane12] 	0x0244 	2
 * @pci.depl_ph[vplane12] 	0x0246 	2
 * @pci.depl_cplh[vplane13] 	0x024a 	2
 * @pci.depl_nph[vplane13] 	0x024c 	2
 * @pci.depl_ph[vplane13] 	0x024e 	2
 * @pci.depl_cplh[vplane14] 	0x0252 	2
 * @pci.depl_nph[vplane14] 	0x0254 	2
 * @pci.depl_ph[vplane14] 	0x0256 	2
 * @pci.depl_cplh[vplane15] 	0x025a 	2
 * @pci.depl_nph[vplane15] 	0x025c 	2
 * @pci.depl_ph[vplane15] 	0x025e 	2
 * @pci.depl_cplh[vplane16] 	0x0262 	2
 * @pci.depl_nph[vplane16] 	0x0264 	2
 * @pci.depl_ph[vplane16] 	0x0266 	2
 * @pci.depl_cpld[vplane0] 	0x026a 	2 	Number of बार completion data
 *  credits were depleted
 * @pci.depl_npd[vplane0] 	0x026c 	2 	Number of बार non posted data
 *  credits were depleted
 * @pci.depl_pd[vplane0] 	0x026e 	2 	Number of बार the posted data
 *  credits were depleted
 * @pci.depl_cpld[vplane1] 	0x0272 	2
 * @pci.depl_npd[vplane1] 	0x0274 	2
 * @pci.depl_pd[vplane1] 	0x0276 	2
 * @pci.depl_cpld[vplane2] 	0x027a 	2
 * @pci.depl_npd[vplane2] 	0x027c 	2
 * @pci.depl_pd[vplane2] 	0x027e 	2
 * @pci.depl_cpld[vplane3] 	0x0282 	2
 * @pci.depl_npd[vplane3] 	0x0284 	2
 * @pci.depl_pd[vplane3] 	0x0286 	2
 * @pci.depl_cpld[vplane4] 	0x028a 	2
 * @pci.depl_npd[vplane4] 	0x028c 	2
 * @pci.depl_pd[vplane4] 	0x028e 	2
 * @pci.depl_cpld[vplane5] 	0x0292 	2
 * @pci.depl_npd[vplane5] 	0x0294 	2
 * @pci.depl_pd[vplane5] 	0x0296 	2
 * @pci.depl_cpld[vplane6] 	0x029a 	2
 * @pci.depl_npd[vplane6] 	0x029c 	2
 * @pci.depl_pd[vplane6] 	0x029e 	2
 * @pci.depl_cpld[vplane7] 	0x02a2 	2
 * @pci.depl_npd[vplane7] 	0x02a4 	2
 * @pci.depl_pd[vplane7] 	0x02a6 	2
 * @pci.depl_cpld[vplane8] 	0x02aa 	2
 * @pci.depl_npd[vplane8] 	0x02ac 	2
 * @pci.depl_pd[vplane8] 	0x02ae 	2
 * @pci.depl_cpld[vplane9] 	0x02b2 	2
 * @pci.depl_npd[vplane9] 	0x02b4 	2
 * @pci.depl_pd[vplane9] 	0x02b6 	2
 * @pci.depl_cpld[vplane10] 	0x02ba 	2
 * @pci.depl_npd[vplane10] 	0x02bc 	2
 * @pci.depl_pd[vplane10] 	0x02be 	2
 * @pci.depl_cpld[vplane11] 	0x02c2 	2
 * @pci.depl_npd[vplane11] 	0x02c4 	2
 * @pci.depl_pd[vplane11] 	0x02c6 	2
 * @pci.depl_cpld[vplane12] 	0x02ca 	2
 * @pci.depl_npd[vplane12] 	0x02cc 	2
 * @pci.depl_pd[vplane12] 	0x02ce 	2
 * @pci.depl_cpld[vplane13] 	0x02d2 	2
 * @pci.depl_npd[vplane13] 	0x02d4 	2
 * @pci.depl_pd[vplane13] 	0x02d6 	2
 * @pci.depl_cpld[vplane14] 	0x02da 	2
 * @pci.depl_npd[vplane14] 	0x02dc 	2
 * @pci.depl_pd[vplane14] 	0x02de 	2
 * @pci.depl_cpld[vplane15] 	0x02e2 	2
 * @pci.depl_npd[vplane15] 	0x02e4 	2
 * @pci.depl_pd[vplane15] 	0x02e6 	2
 * @pci.depl_cpld[vplane16] 	0x02ea 	2
 * @pci.depl_npd[vplane16] 	0x02ec 	2
 * @pci.depl_pd[vplane16] 	0x02ee 	2
 * @xgmac_port[3];
 * @xgmac_aggr[2];
 * @xgmac.global_prog_event_gnum0 	0x0ae0 	8 	Programmable statistic.
 *  Increments when पूर्णांकernal logic detects a certain event. See रेजिस्टर
 *  XMAC_STATS_GLOBAL_CFG.EVENT_GNUM0_CFG क्रम more inक्रमmation.
 * @xgmac.global_prog_event_gnum1 	0x0ae8 	8 	Programmable statistic.
 *  Increments when पूर्णांकernal logic detects a certain event. See रेजिस्टर
 *  XMAC_STATS_GLOBAL_CFG.EVENT_GNUM1_CFG क्रम more inक्रमmation.
 * @xgmac.orp_lro_events 	0x0af8 	8
 * @xgmac.orp_bs_events 	0x0b00 	8
 * @xgmac.orp_iwarp_events 	0x0b08 	8
 * @xgmac.tx_permitted_frms 	0x0b14 	4
 * @xgmac.port2_tx_any_frms 	0x0b1d 	1
 * @xgmac.port1_tx_any_frms 	0x0b1e 	1
 * @xgmac.port0_tx_any_frms 	0x0b1f 	1
 * @xgmac.port2_rx_any_frms 	0x0b25 	1
 * @xgmac.port1_rx_any_frms 	0x0b26 	1
 * @xgmac.port0_rx_any_frms 	0x0b27 	1
 *
 * Titan mrpcim hardware statistics.
 */
काष्ठा vxge_hw_device_stats_mrpcim_info अणु
/*0x0000*/	u32	pic_ini_rd_drop;
/*0x0004*/	u32	pic_ini_wr_drop;
/*0x0008*/	काष्ठा अणु
	/*0x0000*/	u32	pic_wrcrdtarb_ph_crdt_depleted;
	/*0x0004*/	u32	unused1;
		पूर्ण pic_wrcrdtarb_ph_crdt_depleted_vplane[17];
/*0x0090*/	काष्ठा अणु
	/*0x0000*/	u32	pic_wrcrdtarb_pd_crdt_depleted;
	/*0x0004*/	u32	unused2;
		पूर्ण pic_wrcrdtarb_pd_crdt_depleted_vplane[17];
/*0x0118*/	काष्ठा अणु
	/*0x0000*/	u32	pic_rdcrdtarb_nph_crdt_depleted;
	/*0x0004*/	u32	unused3;
		पूर्ण pic_rdcrdtarb_nph_crdt_depleted_vplane[17];
/*0x01a0*/	u32	pic_ini_rd_vpin_drop;
/*0x01a4*/	u32	pic_ini_wr_vpin_drop;
/*0x01a8*/	u32	pic_genstats_count0;
/*0x01ac*/	u32	pic_genstats_count1;
/*0x01b0*/	u32	pic_genstats_count2;
/*0x01b4*/	u32	pic_genstats_count3;
/*0x01b8*/	u32	pic_genstats_count4;
/*0x01bc*/	u32	unused4;
/*0x01c0*/	u32	pic_genstats_count5;
/*0x01c4*/	u32	unused5;
/*0x01c8*/	u32	pci_rstdrop_cpl;
/*0x01cc*/	u32	pci_rstdrop_msg;
/*0x01d0*/	u32	pci_rstdrop_client1;
/*0x01d4*/	u32	pci_rstdrop_client0;
/*0x01d8*/	u32	pci_rstdrop_client2;
/*0x01dc*/	u32	unused6;
/*0x01e0*/	काष्ठा अणु
	/*0x0000*/	u16	unused7;
	/*0x0002*/	u16	pci_depl_cplh;
	/*0x0004*/	u16	pci_depl_nph;
	/*0x0006*/	u16	pci_depl_ph;
		पूर्ण pci_depl_h_vplane[17];
/*0x0268*/	काष्ठा अणु
	/*0x0000*/	u16	unused8;
	/*0x0002*/	u16	pci_depl_cpld;
	/*0x0004*/	u16	pci_depl_npd;
	/*0x0006*/	u16	pci_depl_pd;
		पूर्ण pci_depl_d_vplane[17];
/*0x02f0*/	काष्ठा vxge_hw_xmac_port_stats xgmac_port[3];
/*0x0a10*/	काष्ठा vxge_hw_xmac_aggr_stats xgmac_aggr[2];
/*0x0ae0*/	u64	xgmac_global_prog_event_gnum0;
/*0x0ae8*/	u64	xgmac_global_prog_event_gnum1;
/*0x0af0*/	u64	unused7;
/*0x0af8*/	u64	unused8;
/*0x0b00*/	u64	unused9;
/*0x0b08*/	u64	unused10;
/*0x0b10*/	u32	unused11;
/*0x0b14*/	u32	xgmac_tx_permitted_frms;
/*0x0b18*/	u32	unused12;
/*0x0b1c*/	u8	unused13;
/*0x0b1d*/	u8	xgmac_port2_tx_any_frms;
/*0x0b1e*/	u8	xgmac_port1_tx_any_frms;
/*0x0b1f*/	u8	xgmac_port0_tx_any_frms;
/*0x0b20*/	u32	unused14;
/*0x0b24*/	u8	unused15;
/*0x0b25*/	u8	xgmac_port2_rx_any_frms;
/*0x0b26*/	u8	xgmac_port1_rx_any_frms;
/*0x0b27*/	u8	xgmac_port0_rx_any_frms;
पूर्ण __packed;

/**
 * काष्ठा vxge_hw_device_stats_hw_info - Titan hardware statistics.
 * @vpath_info: VPath statistics
 * @vpath_info_sav: Vpath statistics saved
 *
 * Titan hardware statistics.
 */
काष्ठा vxge_hw_device_stats_hw_info अणु
	काष्ठा vxge_hw_vpath_stats_hw_info
		*vpath_info[VXGE_HW_MAX_VIRTUAL_PATHS];
	काष्ठा vxge_hw_vpath_stats_hw_info
		vpath_info_sav[VXGE_HW_MAX_VIRTUAL_PATHS];
पूर्ण;

/**
 * काष्ठा vxge_hw_vpath_stats_sw_common_info - HW common
 * statistics क्रम queues.
 * @full_cnt: Number of बार the queue was full
 * @usage_cnt: usage count.
 * @usage_max: Maximum usage
 * @reserve_मुक्त_swaps_cnt: Reserve/मुक्त swap counter. Internal usage.
 * @total_compl_cnt: Total descriptor completion count.
 *
 * Hw queue counters
 * See also: काष्ठा vxge_hw_vpath_stats_sw_fअगरo_infoअणुपूर्ण,
 * काष्ठा vxge_hw_vpath_stats_sw_ring_infoअणुपूर्ण,
 */
काष्ठा vxge_hw_vpath_stats_sw_common_info अणु
	u32	full_cnt;
	u32	usage_cnt;
	u32	usage_max;
	u32	reserve_मुक्त_swaps_cnt;
	u32 total_compl_cnt;
पूर्ण;

/**
 * काष्ठा vxge_hw_vpath_stats_sw_fअगरo_info - HW fअगरo statistics
 * @common_stats: Common counters क्रम all queues
 * @total_posts: Total number of postings on the queue.
 * @total_buffers: Total number of buffers posted.
 * @txd_t_code_err_cnt: Array of transmit transfer codes. The position
 * (index) in this array reflects the transfer code type, क्रम instance
 * 0xA - "loss of link".
 * Value txd_t_code_err_cnt[i] reflects the
 * number of बार the corresponding transfer code was encountered.
 *
 * HW fअगरo counters
 * See also: काष्ठा vxge_hw_vpath_stats_sw_common_infoअणुपूर्ण,
 * काष्ठा vxge_hw_vpath_stats_sw_ring_infoअणुपूर्ण,
 */
काष्ठा vxge_hw_vpath_stats_sw_fअगरo_info अणु
	काष्ठा vxge_hw_vpath_stats_sw_common_info common_stats;
	u32 total_posts;
	u32 total_buffers;
	u32 txd_t_code_err_cnt[VXGE_HW_DTR_MAX_T_CODE];
पूर्ण;

/**
 * काष्ठा vxge_hw_vpath_stats_sw_ring_info - HW ring statistics
 * @common_stats: Common counters क्रम all queues
 * @rxd_t_code_err_cnt: Array of receive transfer codes. The position
 *             (index) in this array reflects the transfer code type,
 *             क्रम instance
 *             0x7 - क्रम "invalid receive buffer size", or 0x8 - क्रम ECC.
 *             Value rxd_t_code_err_cnt[i] reflects the
 *             number of बार the corresponding transfer code was encountered.
 *
 * HW ring counters
 * See also: काष्ठा vxge_hw_vpath_stats_sw_common_infoअणुपूर्ण,
 * काष्ठा vxge_hw_vpath_stats_sw_fअगरo_infoअणुपूर्ण,
 */
काष्ठा vxge_hw_vpath_stats_sw_ring_info अणु
	काष्ठा vxge_hw_vpath_stats_sw_common_info common_stats;
	u32 rxd_t_code_err_cnt[VXGE_HW_DTR_MAX_T_CODE];

पूर्ण;

/**
 * काष्ठा vxge_hw_vpath_stats_sw_err - HW vpath error statistics
 * @unknown_alarms:
 * @network_sustained_fault:
 * @network_sustained_ok:
 * @kdfcctl_fअगरo0_overग_लिखो:
 * @kdfcctl_fअगरo0_poison:
 * @kdfcctl_fअगरo0_dma_error:
 * @dblgen_fअगरo0_overflow:
 * @statsb_pअगर_chain_error:
 * @statsb_drop_समयout:
 * @target_illegal_access:
 * @ini_serr_det:
 * @prc_ring_bumps:
 * @prc_rxdcm_sc_err:
 * @prc_rxdcm_sc_पात:
 * @prc_quanta_size_err:
 *
 * HW vpath error statistics
 */
काष्ठा vxge_hw_vpath_stats_sw_err अणु
	u32	unknown_alarms;
	u32	network_sustained_fault;
	u32	network_sustained_ok;
	u32	kdfcctl_fअगरo0_overग_लिखो;
	u32	kdfcctl_fअगरo0_poison;
	u32	kdfcctl_fअगरo0_dma_error;
	u32	dblgen_fअगरo0_overflow;
	u32	statsb_pअगर_chain_error;
	u32	statsb_drop_समयout;
	u32	target_illegal_access;
	u32	ini_serr_det;
	u32	prc_ring_bumps;
	u32	prc_rxdcm_sc_err;
	u32	prc_rxdcm_sc_पात;
	u32	prc_quanta_size_err;
पूर्ण;

/**
 * काष्ठा vxge_hw_vpath_stats_sw_info - HW vpath sw statistics
 * @soft_reset_cnt: Number of बार soft reset is करोne on this vpath.
 * @error_stats: error counters क्रम the vpath
 * @ring_stats: counters क्रम ring beदीर्घing to the vpath
 * @fअगरo_stats: counters क्रम fअगरo beदीर्घing to the vpath
 *
 * HW vpath sw statistics
 * See also: काष्ठा vxge_hw_device_infoअणुपूर्ण पूर्ण.
 */
काष्ठा vxge_hw_vpath_stats_sw_info अणु
	u32    soft_reset_cnt;
	काष्ठा vxge_hw_vpath_stats_sw_err	error_stats;
	काष्ठा vxge_hw_vpath_stats_sw_ring_info	ring_stats;
	काष्ठा vxge_hw_vpath_stats_sw_fअगरo_info	fअगरo_stats;
पूर्ण;

/**
 * काष्ठा vxge_hw_device_stats_sw_info - HW own per-device statistics.
 *
 * @not_traffic_पूर्णांकr_cnt: Number of बार the host was पूर्णांकerrupted
 *                        without new completions.
 *                        "Non-traffic interrupt counter".
 * @traffic_पूर्णांकr_cnt: Number of traffic पूर्णांकerrupts क्रम the device.
 * @total_पूर्णांकr_cnt: Total number of traffic पूर्णांकerrupts क्रम the device.
 *                  @total_पूर्णांकr_cnt == @traffic_पूर्णांकr_cnt +
 *                              @not_traffic_पूर्णांकr_cnt
 * @soft_reset_cnt: Number of बार soft reset is करोne on this device.
 * @vpath_info: please see काष्ठा vxge_hw_vpath_stats_sw_infoअणुपूर्ण
 * HW per-device statistics.
 */
काष्ठा vxge_hw_device_stats_sw_info अणु
	u32	not_traffic_पूर्णांकr_cnt;
	u32	traffic_पूर्णांकr_cnt;
	u32	total_पूर्णांकr_cnt;
	u32	soft_reset_cnt;
	काष्ठा vxge_hw_vpath_stats_sw_info
		vpath_info[VXGE_HW_MAX_VIRTUAL_PATHS];
पूर्ण;

/**
 * काष्ठा vxge_hw_device_stats_sw_err - HW device error statistics.
 * @vpath_alarms: Number of vpath alarms
 *
 * HW Device error stats
 */
काष्ठा vxge_hw_device_stats_sw_err अणु
	u32     vpath_alarms;
पूर्ण;

/**
 * काष्ठा vxge_hw_device_stats - Contains HW per-device statistics,
 * including hw.
 * @devh: HW device handle.
 * @dma_addr: DMA address of the %hw_info. Given to device to fill-in the stats.
 * @hw_info_dmah: DMA handle used to map hw statistics onto the device memory
 *                space.
 * @hw_info_dma_acch: One more DMA handle used subsequently to मुक्त the
 *                    DMA object. Note that this and the previous handle have
 *                    physical meaning क्रम Solaris; on Winकरोws and Linux the
 *                    corresponding value will be simply poपूर्णांकer to PCI device.
 *
 * @hw_dev_info_stats: Titan statistics मुख्यtained by the hardware.
 * @sw_dev_info_stats: HW's "soft" device inक्रमmational statistics, e.g. number
 *                     of completions per पूर्णांकerrupt.
 * @sw_dev_err_stats: HW's "soft" device error statistics.
 *
 * Structure-container of HW per-device statistics. Note that per-channel
 * statistics are kept in separate काष्ठाures under HW's fअगरo and ring
 * channels.
 */
काष्ठा vxge_hw_device_stats अणु
	/* handles */
	काष्ठा __vxge_hw_device *devh;

	/* HW device hardware statistics */
	काष्ठा vxge_hw_device_stats_hw_info	hw_dev_info_stats;

	/* HW device "soft" stats */
	काष्ठा vxge_hw_device_stats_sw_err   sw_dev_err_stats;
	काष्ठा vxge_hw_device_stats_sw_info  sw_dev_info_stats;

पूर्ण;

क्रमागत vxge_hw_status vxge_hw_device_hw_stats_enable(
			काष्ठा __vxge_hw_device *devh);

क्रमागत vxge_hw_status vxge_hw_device_stats_get(
			काष्ठा __vxge_hw_device *devh,
			काष्ठा vxge_hw_device_stats_hw_info *hw_stats);

क्रमागत vxge_hw_status vxge_hw_driver_stats_get(
			काष्ठा __vxge_hw_device *devh,
			काष्ठा vxge_hw_device_stats_sw_info *sw_stats);

क्रमागत vxge_hw_status vxge_hw_mrpcim_stats_enable(काष्ठा __vxge_hw_device *devh);

क्रमागत vxge_hw_status vxge_hw_mrpcim_stats_disable(काष्ठा __vxge_hw_device *devh);

क्रमागत vxge_hw_status
vxge_hw_mrpcim_stats_access(
	काष्ठा __vxge_hw_device *devh,
	u32 operation,
	u32 location,
	u32 offset,
	u64 *stat);

क्रमागत vxge_hw_status
vxge_hw_device_xmac_stats_get(काष्ठा __vxge_hw_device *devh,
			      काष्ठा vxge_hw_xmac_stats *xmac_stats);

/**
 * क्रमागत क्रमागत vxge_hw_mgmt_reg_type - Register types.
 *
 * @vxge_hw_mgmt_reg_type_legacy: Legacy रेजिस्टरs
 * @vxge_hw_mgmt_reg_type_toc: TOC Registers
 * @vxge_hw_mgmt_reg_type_common: Common Registers
 * @vxge_hw_mgmt_reg_type_mrpcim: mrpcim रेजिस्टरs
 * @vxge_hw_mgmt_reg_type_srpcim: srpcim रेजिस्टरs
 * @vxge_hw_mgmt_reg_type_vpmgmt: vpath management रेजिस्टरs
 * @vxge_hw_mgmt_reg_type_vpath: vpath रेजिस्टरs
 *
 * Register type क्रमागतaration
 */
क्रमागत vxge_hw_mgmt_reg_type अणु
	vxge_hw_mgmt_reg_type_legacy = 0,
	vxge_hw_mgmt_reg_type_toc = 1,
	vxge_hw_mgmt_reg_type_common = 2,
	vxge_hw_mgmt_reg_type_mrpcim = 3,
	vxge_hw_mgmt_reg_type_srpcim = 4,
	vxge_hw_mgmt_reg_type_vpmgmt = 5,
	vxge_hw_mgmt_reg_type_vpath = 6
पूर्ण;

क्रमागत vxge_hw_status
vxge_hw_mgmt_reg_पढ़ो(काष्ठा __vxge_hw_device *devh,
		      क्रमागत vxge_hw_mgmt_reg_type type,
		      u32 index,
		      u32 offset,
		      u64 *value);

क्रमागत vxge_hw_status
vxge_hw_mgmt_reg_ग_लिखो(काष्ठा __vxge_hw_device *devh,
		      क्रमागत vxge_hw_mgmt_reg_type type,
		      u32 index,
		      u32 offset,
		      u64 value);

/**
 * क्रमागत क्रमागत vxge_hw_rxd_state - Descriptor (RXD) state.
 * @VXGE_HW_RXD_STATE_NONE: Invalid state.
 * @VXGE_HW_RXD_STATE_AVAIL: Descriptor is available क्रम reservation.
 * @VXGE_HW_RXD_STATE_POSTED: Descriptor is posted क्रम processing by the
 * device.
 * @VXGE_HW_RXD_STATE_FREED: Descriptor is मुक्त and can be reused क्रम
 * filling-in and posting later.
 *
 * Titan/HW descriptor states.
 *
 */
क्रमागत vxge_hw_rxd_state अणु
	VXGE_HW_RXD_STATE_NONE		= 0,
	VXGE_HW_RXD_STATE_AVAIL		= 1,
	VXGE_HW_RXD_STATE_POSTED	= 2,
	VXGE_HW_RXD_STATE_FREED		= 3
पूर्ण;

/**
 * काष्ठा vxge_hw_ring_rxd_info - Extended inक्रमmation associated with a
 * completed ring descriptor.
 * @syn_flag: SYN flag
 * @is_icmp: Is ICMP
 * @fast_path_eligible: Fast Path Eligible flag
 * @l3_cksum: in L3 checksum is valid
 * @l3_cksum: Result of IP checksum check (by Titan hardware).
 *            This field containing VXGE_HW_L3_CKSUM_OK would mean that
 *            the checksum is correct, otherwise - the datagram is
 *            corrupted.
 * @l4_cksum: in L4 checksum is valid
 * @l4_cksum: Result of TCP/UDP checksum check (by Titan hardware).
 *            This field containing VXGE_HW_L4_CKSUM_OK would mean that
 *            the checksum is correct. Otherwise - the packet is
 *            corrupted.
 * @frame: Zero or more of क्रमागत vxge_hw_frame_type flags.
 * 		See क्रमागत vxge_hw_frame_typeअणुपूर्ण.
 * @proto: zero or more of क्रमागत vxge_hw_frame_proto flags.  Reporting bits क्रम
 *            various higher-layer protocols, including (but note restricted to)
 *            TCP and UDP. See क्रमागत vxge_hw_frame_protoअणुपूर्ण.
 * @is_vlan: If vlan tag is valid
 * @vlan: VLAN tag extracted from the received frame.
 * @rth_bucket: RTH bucket
 * @rth_it_hit: Set, If RTH hash value calculated by the Titan hardware
 *             has a matching entry in the Indirection table.
 * @rth_spdm_hit: Set, If RTH hash value calculated by the Titan hardware
 *             has a matching entry in the Socket Pair Direct Match table.
 * @rth_hash_type: RTH hash code of the function used to calculate the hash.
 * @rth_value: Receive Traffic Hashing(RTH) hash value. Produced by Titan
 *             hardware अगर RTH is enabled.
 */
काष्ठा vxge_hw_ring_rxd_info अणु
	u32	syn_flag;
	u32	is_icmp;
	u32	fast_path_eligible;
	u32	l3_cksum_valid;
	u32	l3_cksum;
	u32	l4_cksum_valid;
	u32	l4_cksum;
	u32	frame;
	u32	proto;
	u32	is_vlan;
	u32	vlan;
	u32	rth_bucket;
	u32	rth_it_hit;
	u32	rth_spdm_hit;
	u32	rth_hash_type;
	u32	rth_value;
पूर्ण;
/**
 * क्रमागत vxge_hw_ring_tcode - Transfer codes वापसed by adapter
 * @VXGE_HW_RING_T_CODE_OK: Transfer ok.
 * @VXGE_HW_RING_T_CODE_L3_CKSUM_MISMATCH: Layer 3 checksum presentation
 *		configuration mismatch.
 * @VXGE_HW_RING_T_CODE_L4_CKSUM_MISMATCH: Layer 4 checksum presentation
 *		configuration mismatch.
 * @VXGE_HW_RING_T_CODE_L3_L4_CKSUM_MISMATCH: Layer 3 and Layer 4 checksum
 *		presentation configuration mismatch.
 * @VXGE_HW_RING_T_CODE_L3_PKT_ERR: Layer 3 error unparseable packet,
 *		such as unknown IPv6 header.
 * @VXGE_HW_RING_T_CODE_L2_FRM_ERR: Layer 2 error frame पूर्णांकegrity
 *		error, such as FCS or ECC).
 * @VXGE_HW_RING_T_CODE_BUF_SIZE_ERR: Buffer size error the RxD buffer(
 *		s) were not appropriately sized and data loss occurred.
 * @VXGE_HW_RING_T_CODE_INT_ECC_ERR: Internal ECC error RxD corrupted.
 * @VXGE_HW_RING_T_CODE_BENIGN_OVFLOW: Benign overflow the contents of
 *		Segment1 exceeded the capacity of Buffer1 and the reमुख्यder
 *		was placed in Buffer2. Segment2 now starts in Buffer3.
 *		No data loss or errors occurred.
 * @VXGE_HW_RING_T_CODE_ZERO_LEN_BUFF: Buffer size 0 one of the RxDs
 *		asचिन्हित buffers has a size of 0 bytes.
 * @VXGE_HW_RING_T_CODE_FRM_DROP: Frame dropped either due to
 *		VPath Reset or because of a VPIN mismatch.
 * @VXGE_HW_RING_T_CODE_UNUSED: Unused
 * @VXGE_HW_RING_T_CODE_MULTI_ERR: Multiple errors more than one
 *		transfer code condition occurred.
 *
 * Transfer codes वापसed by adapter.
 */
क्रमागत vxge_hw_ring_tcode अणु
	VXGE_HW_RING_T_CODE_OK				= 0x0,
	VXGE_HW_RING_T_CODE_L3_CKSUM_MISMATCH		= 0x1,
	VXGE_HW_RING_T_CODE_L4_CKSUM_MISMATCH		= 0x2,
	VXGE_HW_RING_T_CODE_L3_L4_CKSUM_MISMATCH	= 0x3,
	VXGE_HW_RING_T_CODE_L3_PKT_ERR			= 0x5,
	VXGE_HW_RING_T_CODE_L2_FRM_ERR			= 0x6,
	VXGE_HW_RING_T_CODE_BUF_SIZE_ERR		= 0x7,
	VXGE_HW_RING_T_CODE_INT_ECC_ERR			= 0x8,
	VXGE_HW_RING_T_CODE_BENIGN_OVFLOW		= 0x9,
	VXGE_HW_RING_T_CODE_ZERO_LEN_BUFF		= 0xA,
	VXGE_HW_RING_T_CODE_FRM_DROP			= 0xC,
	VXGE_HW_RING_T_CODE_UNUSED			= 0xE,
	VXGE_HW_RING_T_CODE_MULTI_ERR			= 0xF
पूर्ण;

क्रमागत vxge_hw_status vxge_hw_ring_rxd_reserve(
	काष्ठा __vxge_hw_ring *ring_handle,
	व्योम **rxdh);

व्योम
vxge_hw_ring_rxd_pre_post(
	काष्ठा __vxge_hw_ring *ring_handle,
	व्योम *rxdh);

व्योम
vxge_hw_ring_rxd_post_post(
	काष्ठा __vxge_hw_ring *ring_handle,
	व्योम *rxdh);

व्योम
vxge_hw_ring_rxd_post_post_wmb(
	काष्ठा __vxge_hw_ring *ring_handle,
	व्योम *rxdh);

व्योम vxge_hw_ring_rxd_post(
	काष्ठा __vxge_hw_ring *ring_handle,
	व्योम *rxdh);

क्रमागत vxge_hw_status vxge_hw_ring_rxd_next_completed(
	काष्ठा __vxge_hw_ring *ring_handle,
	व्योम **rxdh,
	u8 *t_code);

क्रमागत vxge_hw_status vxge_hw_ring_handle_tcode(
	काष्ठा __vxge_hw_ring *ring_handle,
	व्योम *rxdh,
	u8 t_code);

व्योम vxge_hw_ring_rxd_मुक्त(
	काष्ठा __vxge_hw_ring *ring_handle,
	व्योम *rxdh);

/**
 * क्रमागत क्रमागत vxge_hw_frame_proto - Higher-layer ethernet protocols.
 * @VXGE_HW_FRAME_PROTO_VLAN_TAGGED: VLAN.
 * @VXGE_HW_FRAME_PROTO_IPV4: IPv4.
 * @VXGE_HW_FRAME_PROTO_IPV6: IPv6.
 * @VXGE_HW_FRAME_PROTO_IP_FRAG: IP fragmented.
 * @VXGE_HW_FRAME_PROTO_TCP: TCP.
 * @VXGE_HW_FRAME_PROTO_UDP: UDP.
 * @VXGE_HW_FRAME_PROTO_TCP_OR_UDP: TCP or UDP.
 *
 * Higher layer ethernet protocols and options.
 */
क्रमागत vxge_hw_frame_proto अणु
	VXGE_HW_FRAME_PROTO_VLAN_TAGGED = 0x80,
	VXGE_HW_FRAME_PROTO_IPV4		= 0x10,
	VXGE_HW_FRAME_PROTO_IPV6		= 0x08,
	VXGE_HW_FRAME_PROTO_IP_FRAG		= 0x04,
	VXGE_HW_FRAME_PROTO_TCP			= 0x02,
	VXGE_HW_FRAME_PROTO_UDP			= 0x01,
	VXGE_HW_FRAME_PROTO_TCP_OR_UDP	= (VXGE_HW_FRAME_PROTO_TCP | \
						   VXGE_HW_FRAME_PROTO_UDP)
पूर्ण;

/**
 * क्रमागत क्रमागत vxge_hw_fअगरo_gather_code - Gather codes used in fअगरo TxD
 * @VXGE_HW_FIFO_GATHER_CODE_FIRST: First TxDL
 * @VXGE_HW_FIFO_GATHER_CODE_MIDDLE: Middle TxDL
 * @VXGE_HW_FIFO_GATHER_CODE_LAST: Last TxDL
 * @VXGE_HW_FIFO_GATHER_CODE_FIRST_LAST: First and Last TxDL.
 *
 * These gather codes are used to indicate the position of a TxD in a TxD list
 */
क्रमागत vxge_hw_fअगरo_gather_code अणु
	VXGE_HW_FIFO_GATHER_CODE_FIRST		= 0x2,
	VXGE_HW_FIFO_GATHER_CODE_MIDDLE		= 0x0,
	VXGE_HW_FIFO_GATHER_CODE_LAST		= 0x1,
	VXGE_HW_FIFO_GATHER_CODE_FIRST_LAST	= 0x3
पूर्ण;

/**
 * क्रमागत क्रमागत vxge_hw_fअगरo_tcode - tcodes used in fअगरo
 * @VXGE_HW_FIFO_T_CODE_OK: Transfer OK
 * @VXGE_HW_FIFO_T_CODE_PCI_READ_CORRUPT: PCI पढ़ो transaction (either TxD or
 *             frame data) वापसed with corrupt data.
 * @VXGE_HW_FIFO_T_CODE_PCI_READ_FAIL:PCI पढ़ो transaction was वापसed
 *             with no data.
 * @VXGE_HW_FIFO_T_CODE_INVALID_MSS: The host attempted to send either a
 *             frame or LSO MSS that was too दीर्घ (>9800B).
 * @VXGE_HW_FIFO_T_CODE_LSO_ERROR: Error detected during TCP/UDP Large Send
	*	       Offload operation, due to improper header ढाँचा,
	*	       unsupported protocol, etc.
 * @VXGE_HW_FIFO_T_CODE_UNUSED: Unused
 * @VXGE_HW_FIFO_T_CODE_MULTI_ERROR: Set to 1 by the adapter अगर multiple
 *             data buffer transfer errors are encountered (see below).
 *             Otherwise it is set to 0.
 *
 * These tcodes are वापसed in various API क्रम TxD status
 */
क्रमागत vxge_hw_fअगरo_tcode अणु
	VXGE_HW_FIFO_T_CODE_OK			= 0x0,
	VXGE_HW_FIFO_T_CODE_PCI_READ_CORRUPT	= 0x1,
	VXGE_HW_FIFO_T_CODE_PCI_READ_FAIL	= 0x2,
	VXGE_HW_FIFO_T_CODE_INVALID_MSS		= 0x3,
	VXGE_HW_FIFO_T_CODE_LSO_ERROR		= 0x4,
	VXGE_HW_FIFO_T_CODE_UNUSED		= 0x7,
	VXGE_HW_FIFO_T_CODE_MULTI_ERROR		= 0x8
पूर्ण;

क्रमागत vxge_hw_status vxge_hw_fअगरo_txdl_reserve(
	काष्ठा __vxge_hw_fअगरo *fअगरoh,
	व्योम **txdlh,
	व्योम **txdl_priv);

व्योम vxge_hw_fअगरo_txdl_buffer_set(
			काष्ठा __vxge_hw_fअगरo *fअगरo_handle,
			व्योम *txdlh,
			u32 frag_idx,
			dma_addr_t dma_poपूर्णांकer,
			u32 size);

व्योम vxge_hw_fअगरo_txdl_post(
			काष्ठा __vxge_hw_fअगरo *fअगरo_handle,
			व्योम *txdlh);

u32 vxge_hw_fअगरo_मुक्त_txdl_count_get(
			काष्ठा __vxge_hw_fअगरo *fअगरo_handle);

क्रमागत vxge_hw_status vxge_hw_fअगरo_txdl_next_completed(
	काष्ठा __vxge_hw_fअगरo *fअगरoh,
	व्योम **txdlh,
	क्रमागत vxge_hw_fअगरo_tcode *t_code);

क्रमागत vxge_hw_status vxge_hw_fअगरo_handle_tcode(
	काष्ठा __vxge_hw_fअगरo *fअगरoh,
	व्योम *txdlh,
	क्रमागत vxge_hw_fअगरo_tcode t_code);

व्योम vxge_hw_fअगरo_txdl_मुक्त(
	काष्ठा __vxge_hw_fअगरo *fअगरoh,
	व्योम *txdlh);

/*
 * Device
 */

#घोषणा VXGE_HW_RING_NEXT_BLOCK_POINTER_OFFSET	(VXGE_HW_BLOCK_SIZE-8)
#घोषणा VXGE_HW_RING_MEMBLOCK_IDX_OFFSET		(VXGE_HW_BLOCK_SIZE-16)

/*
 * काष्ठा __vxge_hw_ring_rxd_priv - Receive descriptor HW-निजी data.
 * @dma_addr: DMA (mapped) address of _this_ descriptor.
 * @dma_handle: DMA handle used to map the descriptor onto device.
 * @dma_offset: Descriptor's offset in the memory block. HW allocates
 *              descriptors in memory blocks of %VXGE_HW_BLOCK_SIZE
 *              bytes. Each memblock is contiguous DMA-able memory. Each
 *              memblock contains 1 or more 4KB RxD blocks visible to the
 *              Titan hardware.
 * @dma_object: DMA address and handle of the memory block that contains
 *              the descriptor. This member is used only in the "checked"
 *              version of the HW (to enक्रमce certain निश्चितions);
 *              otherwise it माला_लो compiled out.
 * @allocated: True अगर the descriptor is reserved, 0 otherwise. Internal usage.
 *
 * Per-receive decsriptor HW-निजी data. HW uses the space to keep DMA
 * inक्रमmation associated with the descriptor. Note that driver can ask HW
 * to allocate additional per-descriptor space क्रम its own (driver-specअगरic)
 * purposes.
 */
काष्ठा __vxge_hw_ring_rxd_priv अणु
	dma_addr_t	dma_addr;
	काष्ठा pci_dev *dma_handle;
	सूचक_भेद_प्रकार	dma_offset;
#अगर_घोषित VXGE_DEBUG_ASSERT
	काष्ठा vxge_hw_mempool_dma	*dma_object;
#पूर्ण_अगर
पूर्ण;

काष्ठा vxge_hw_mempool_cbs अणु
	व्योम (*item_func_alloc)(
			काष्ठा vxge_hw_mempool *mempoolh,
			u32			memblock_index,
			काष्ठा vxge_hw_mempool_dma	*dma_object,
			u32			index,
			u32			is_last);
पूर्ण;

#घोषणा VXGE_HW_VIRTUAL_PATH_HANDLE(vpath)				\
		((काष्ठा __vxge_hw_vpath_handle *)(vpath)->vpath_handles.next)

क्रमागत vxge_hw_status
__vxge_hw_vpath_rts_table_get(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u32			action,
	u32			rts_table,
	u32			offset,
	u64			*data1,
	u64			*data2);

क्रमागत vxge_hw_status
__vxge_hw_vpath_rts_table_set(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u32			action,
	u32			rts_table,
	u32			offset,
	u64			data1,
	u64			data2);

क्रमागत vxge_hw_status
__vxge_hw_vpath_enable(
	काष्ठा __vxge_hw_device *devh,
	u32			vp_id);

व्योम vxge_hw_device_पूर्णांकr_enable(
	काष्ठा __vxge_hw_device *devh);

u32 vxge_hw_device_set_पूर्णांकr_type(काष्ठा __vxge_hw_device *devh, u32 पूर्णांकr_mode);

व्योम vxge_hw_device_पूर्णांकr_disable(
	काष्ठा __vxge_hw_device *devh);

व्योम vxge_hw_device_mask_all(
	काष्ठा __vxge_hw_device *devh);

व्योम vxge_hw_device_unmask_all(
	काष्ठा __vxge_hw_device *devh);

क्रमागत vxge_hw_status vxge_hw_device_begin_irq(
	काष्ठा __vxge_hw_device *devh,
	u32 skip_alarms,
	u64 *reason);

व्योम vxge_hw_device_clear_tx_rx(
	काष्ठा __vxge_hw_device *devh);

/*
 *  Virtual Paths
 */

व्योम vxge_hw_vpath_dynamic_rti_rसमयr_set(काष्ठा __vxge_hw_ring *ring);

व्योम vxge_hw_vpath_dynamic_tti_rसमयr_set(काष्ठा __vxge_hw_fअगरo *fअगरo);

u32 vxge_hw_vpath_id(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle);

क्रमागत vxge_hw_vpath_mac_addr_add_mode अणु
	VXGE_HW_VPATH_MAC_ADDR_ADD_DUPLICATE = 0,
	VXGE_HW_VPATH_MAC_ADDR_DISCARD_DUPLICATE = 1,
	VXGE_HW_VPATH_MAC_ADDR_REPLACE_DUPLICATE = 2
पूर्ण;

क्रमागत vxge_hw_status
vxge_hw_vpath_mac_addr_add(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u8 *macaddr,
	u8 *macaddr_mask,
	क्रमागत vxge_hw_vpath_mac_addr_add_mode duplicate_mode);

क्रमागत vxge_hw_status
vxge_hw_vpath_mac_addr_get(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u8 *macaddr,
	u8 *macaddr_mask);

क्रमागत vxge_hw_status
vxge_hw_vpath_mac_addr_get_next(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u8 *macaddr,
	u8 *macaddr_mask);

क्रमागत vxge_hw_status
vxge_hw_vpath_mac_addr_delete(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u8 *macaddr,
	u8 *macaddr_mask);

क्रमागत vxge_hw_status
vxge_hw_vpath_vid_add(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u64			vid);

क्रमागत vxge_hw_status
vxge_hw_vpath_vid_delete(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u64			vid);

क्रमागत vxge_hw_status
vxge_hw_vpath_etype_add(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u64			etype);

क्रमागत vxge_hw_status
vxge_hw_vpath_etype_get(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u64			*etype);

क्रमागत vxge_hw_status
vxge_hw_vpath_etype_get_next(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u64			*etype);

क्रमागत vxge_hw_status
vxge_hw_vpath_etype_delete(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u64			etype);

क्रमागत vxge_hw_status vxge_hw_vpath_promisc_enable(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle);

क्रमागत vxge_hw_status vxge_hw_vpath_promisc_disable(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle);

क्रमागत vxge_hw_status vxge_hw_vpath_bcast_enable(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle);

क्रमागत vxge_hw_status vxge_hw_vpath_mcast_enable(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle);

क्रमागत vxge_hw_status vxge_hw_vpath_mcast_disable(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle);

क्रमागत vxge_hw_status vxge_hw_vpath_poll_rx(
	काष्ठा __vxge_hw_ring *ringh);

क्रमागत vxge_hw_status vxge_hw_vpath_poll_tx(
	काष्ठा __vxge_hw_fअगरo *fअगरoh,
	काष्ठा sk_buff ***skb_ptr, पूर्णांक nr_skb, पूर्णांक *more);

क्रमागत vxge_hw_status vxge_hw_vpath_alarm_process(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle,
	u32 skip_alarms);

व्योम
vxge_hw_vpath_msix_set(काष्ठा __vxge_hw_vpath_handle *vpath_handle,
		       पूर्णांक *tim_msix_id, पूर्णांक alarm_msix_id);

व्योम
vxge_hw_vpath_msix_mask(काष्ठा __vxge_hw_vpath_handle *vpath_handle,
			पूर्णांक msix_id);

व्योम vxge_hw_vpath_msix_clear(काष्ठा __vxge_hw_vpath_handle *vp, पूर्णांक msix_id);

व्योम vxge_hw_device_flush_io(काष्ठा __vxge_hw_device *devh);

व्योम
vxge_hw_vpath_msix_unmask(काष्ठा __vxge_hw_vpath_handle *vpath_handle,
			  पूर्णांक msix_id);

क्रमागत vxge_hw_status vxge_hw_vpath_पूर्णांकr_enable(
				काष्ठा __vxge_hw_vpath_handle *vpath_handle);

क्रमागत vxge_hw_status vxge_hw_vpath_पूर्णांकr_disable(
				काष्ठा __vxge_hw_vpath_handle *vpath_handle);

व्योम vxge_hw_vpath_पूर्णांकa_mask_tx_rx(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle);

व्योम vxge_hw_vpath_पूर्णांकa_unmask_tx_rx(
	काष्ठा __vxge_hw_vpath_handle *vpath_handle);

व्योम
vxge_hw_channel_msix_mask(काष्ठा __vxge_hw_channel *channelh, पूर्णांक msix_id);

व्योम
vxge_hw_channel_msix_unmask(काष्ठा __vxge_hw_channel *channelh, पूर्णांक msix_id);

व्योम
vxge_hw_channel_msix_clear(काष्ठा __vxge_hw_channel *channelh, पूर्णांक msix_id);

व्योम
vxge_hw_channel_dtr_try_complete(काष्ठा __vxge_hw_channel *channel,
				 व्योम **dtrh);

व्योम
vxge_hw_channel_dtr_complete(काष्ठा __vxge_hw_channel *channel);

व्योम
vxge_hw_channel_dtr_मुक्त(काष्ठा __vxge_hw_channel *channel, व्योम *dtrh);

पूर्णांक
vxge_hw_channel_dtr_count(काष्ठा __vxge_hw_channel *channel);

व्योम vxge_hw_vpath_tti_ci_set(काष्ठा __vxge_hw_fअगरo *fअगरo);

व्योम vxge_hw_vpath_dynamic_rti_ci_set(काष्ठा __vxge_hw_ring *ring);

#पूर्ण_अगर
