<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2021 Intel Corporation. */

#अगर_अघोषित _I40E_H_
#घोषणा _I40E_H_

#समावेश <net/tcp.h>
#समावेश <net/udp.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/aer.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ioport.h>
#समावेश <linux/iommu.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/माला.स>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/sctp.h>
#समावेश <linux/pkt_sched.h>
#समावेश <linux/ipv6.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_macvlan.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश <net/tc_act/tc_mirred.h>
#समावेश <net/udp_tunnel.h>
#समावेश <net/xdp_sock.h>
#समावेश "i40e_type.h"
#समावेश "i40e_prototype.h"
#समावेश <linux/net/पूर्णांकel/i40e_client.h>
#समावेश <linux/avf/virtchnl.h>
#समावेश "i40e_virtchnl_pf.h"
#समावेश "i40e_txrx.h"
#समावेश "i40e_dcb.h"

/* Useful i40e शेषs */
#घोषणा I40E_MAX_VEB			16

#घोषणा I40E_MAX_NUM_DESCRIPTORS	4096
#घोषणा I40E_MAX_CSR_SPACE		(4 * 1024 * 1024 - 64 * 1024)
#घोषणा I40E_DEFAULT_NUM_DESCRIPTORS	512
#घोषणा I40E_REQ_DESCRIPTOR_MULTIPLE	32
#घोषणा I40E_MIN_NUM_DESCRIPTORS	64
#घोषणा I40E_MIN_MSIX			2
#घोषणा I40E_DEFAULT_NUM_VMDQ_VSI	8 /* max 256 VSIs */
#घोषणा I40E_MIN_VSI_ALLOC		83 /* LAN, ATR, FCOE, 64 VF */
/* max 16 qps */
#घोषणा i40e_शेष_queues_per_vmdq(pf) \
		(((pf)->hw_features & I40E_HW_RSS_AQ_CAPABLE) ? 4 : 1)
#घोषणा I40E_DEFAULT_QUEUES_PER_VF	4
#घोषणा I40E_MAX_VF_QUEUES		16
#घोषणा i40e_pf_get_max_q_per_tc(pf) \
		(((pf)->hw_features & I40E_HW_128_QP_RSS_CAPABLE) ? 128 : 64)
#घोषणा I40E_Fसूची_RING_COUNT		32
#घोषणा I40E_MAX_AQ_BUF_SIZE		4096
#घोषणा I40E_AQ_LEN			256
#घोषणा I40E_MIN_ARQ_LEN		1
#घोषणा I40E_MIN_ASQ_LEN		2
#घोषणा I40E_AQ_WORK_LIMIT		66 /* max number of VFs + a little */
#घोषणा I40E_MAX_USER_PRIORITY		8
#घोषणा I40E_DEFAULT_TRAFFIC_CLASS	BIT(0)
#घोषणा I40E_QUEUE_WAIT_RETRY_LIMIT	10
#घोषणा I40E_INT_NAME_STR_LEN		(IFNAMSIZ + 16)

#घोषणा I40E_NVM_VERSION_LO_SHIFT	0
#घोषणा I40E_NVM_VERSION_LO_MASK	(0xff << I40E_NVM_VERSION_LO_SHIFT)
#घोषणा I40E_NVM_VERSION_HI_SHIFT	12
#घोषणा I40E_NVM_VERSION_HI_MASK	(0xf << I40E_NVM_VERSION_HI_SHIFT)
#घोषणा I40E_OEM_VER_BUILD_MASK		0xffff
#घोषणा I40E_OEM_VER_PATCH_MASK		0xff
#घोषणा I40E_OEM_VER_BUILD_SHIFT	8
#घोषणा I40E_OEM_VER_SHIFT		24
#घोषणा I40E_PHY_DEBUG_ALL \
	(I40E_AQ_PHY_DEBUG_DISABLE_LINK_FW | \
	I40E_AQ_PHY_DEBUG_DISABLE_ALL_LINK_FW)

#घोषणा I40E_OEM_EETRACK_ID		0xffffffff
#घोषणा I40E_OEM_GEN_SHIFT		24
#घोषणा I40E_OEM_SNAP_MASK		0x00ff0000
#घोषणा I40E_OEM_SNAP_SHIFT		16
#घोषणा I40E_OEM_RELEASE_MASK		0x0000ffff

#घोषणा I40E_RX_DESC(R, i)	\
	(&(((जोड़ i40e_rx_desc *)((R)->desc))[i]))
#घोषणा I40E_TX_DESC(R, i)	\
	(&(((काष्ठा i40e_tx_desc *)((R)->desc))[i]))
#घोषणा I40E_TX_CTXTDESC(R, i)	\
	(&(((काष्ठा i40e_tx_context_desc *)((R)->desc))[i]))
#घोषणा I40E_TX_FसूचीDESC(R, i)	\
	(&(((काष्ठा i40e_filter_program_desc *)((R)->desc))[i]))

/* BW rate limiting */
#घोषणा I40E_BW_CREDIT_DIVISOR		50 /* 50Mbps per BW credit */
#घोषणा I40E_BW_MBPS_DIVISOR		125000 /* rate / (1000000 / 8) Mbps */
#घोषणा I40E_MAX_BW_INACTIVE_ACCUM	4 /* accumulate 4 credits max */

/* driver state flags */
क्रमागत i40e_state_t अणु
	__I40E_TESTING,
	__I40E_CONFIG_BUSY,
	__I40E_CONFIG_DONE,
	__I40E_DOWN,
	__I40E_SERVICE_SCHED,
	__I40E_ADMINQ_EVENT_PENDING,
	__I40E_MDD_EVENT_PENDING,
	__I40E_VFLR_EVENT_PENDING,
	__I40E_RESET_RECOVERY_PENDING,
	__I40E_TIMEOUT_RECOVERY_PENDING,
	__I40E_MISC_IRQ_REQUESTED,
	__I40E_RESET_INTR_RECEIVED,
	__I40E_REINIT_REQUESTED,
	__I40E_PF_RESET_REQUESTED,
	__I40E_PF_RESET_AND_REBUILD_REQUESTED,
	__I40E_CORE_RESET_REQUESTED,
	__I40E_GLOBAL_RESET_REQUESTED,
	__I40E_EMP_RESET_INTR_RECEIVED,
	__I40E_SUSPENDED,
	__I40E_PTP_TX_IN_PROGRESS,
	__I40E_BAD_EEPROM,
	__I40E_DOWN_REQUESTED,
	__I40E_FD_FLUSH_REQUESTED,
	__I40E_FD_ATR_AUTO_DISABLED,
	__I40E_FD_SB_AUTO_DISABLED,
	__I40E_RESET_FAILED,
	__I40E_PORT_SUSPENDED,
	__I40E_VF_DISABLE,
	__I40E_MACVLAN_SYNC_PENDING,
	__I40E_TEMP_LINK_POLLING,
	__I40E_CLIENT_SERVICE_REQUESTED,
	__I40E_CLIENT_L2_CHANGE,
	__I40E_CLIENT_RESET,
	__I40E_VIRTCHNL_OP_PENDING,
	__I40E_RECOVERY_MODE,
	__I40E_VF_RESETS_DISABLED,	/* disable resets during i40e_हटाओ */
	__I40E_VFS_RELEASING,
	/* This must be last as it determines the size of the BITMAP */
	__I40E_STATE_SIZE__,
पूर्ण;

#घोषणा I40E_PF_RESET_FLAG	BIT_ULL(__I40E_PF_RESET_REQUESTED)
#घोषणा I40E_PF_RESET_AND_REBUILD_FLAG	\
	BIT_ULL(__I40E_PF_RESET_AND_REBUILD_REQUESTED)

/* VSI state flags */
क्रमागत i40e_vsi_state_t अणु
	__I40E_VSI_DOWN,
	__I40E_VSI_NEEDS_RESTART,
	__I40E_VSI_SYNCING_FILTERS,
	__I40E_VSI_OVERFLOW_PROMISC,
	__I40E_VSI_REINIT_REQUESTED,
	__I40E_VSI_DOWN_REQUESTED,
	/* This must be last as it determines the size of the BITMAP */
	__I40E_VSI_STATE_SIZE__,
पूर्ण;

क्रमागत i40e_पूर्णांकerrupt_policy अणु
	I40E_INTERRUPT_BEST_CASE,
	I40E_INTERRUPT_MEDIUM,
	I40E_INTERRUPT_LOWEST
पूर्ण;

काष्ठा i40e_lump_tracking अणु
	u16 num_entries;
	u16 search_hपूर्णांक;
	u16 list[0];
#घोषणा I40E_PILE_VALID_BIT  0x8000
#घोषणा I40E_IWARP_IRQ_PILE_ID  (I40E_PILE_VALID_BIT - 2)
पूर्ण;

#घोषणा I40E_DEFAULT_ATR_SAMPLE_RATE	20
#घोषणा I40E_Fसूची_MAX_RAW_PACKET_SIZE	512
#घोषणा I40E_Fसूची_BUFFER_FULL_MARGIN	10
#घोषणा I40E_Fसूची_BUFFER_HEAD_ROOM	32
#घोषणा I40E_Fसूची_BUFFER_HEAD_ROOM_FOR_ATR (I40E_Fसूची_BUFFER_HEAD_ROOM * 4)

#घोषणा I40E_HKEY_ARRAY_SIZE	((I40E_PFQF_HKEY_MAX_INDEX + 1) * 4)
#घोषणा I40E_HLUT_ARRAY_SIZE	((I40E_PFQF_HLUT_MAX_INDEX + 1) * 4)
#घोषणा I40E_VF_HLUT_ARRAY_SIZE	((I40E_VFQF_HLUT1_MAX_INDEX + 1) * 4)

क्रमागत i40e_fd_stat_idx अणु
	I40E_FD_STAT_ATR,
	I40E_FD_STAT_SB,
	I40E_FD_STAT_ATR_TUNNEL,
	I40E_FD_STAT_PF_COUNT
पूर्ण;
#घोषणा I40E_FD_STAT_PF_IDX(pf_id) ((pf_id) * I40E_FD_STAT_PF_COUNT)
#घोषणा I40E_FD_ATR_STAT_IDX(pf_id) \
			(I40E_FD_STAT_PF_IDX(pf_id) + I40E_FD_STAT_ATR)
#घोषणा I40E_FD_SB_STAT_IDX(pf_id)  \
			(I40E_FD_STAT_PF_IDX(pf_id) + I40E_FD_STAT_SB)
#घोषणा I40E_FD_ATR_TUNNEL_STAT_IDX(pf_id) \
			(I40E_FD_STAT_PF_IDX(pf_id) + I40E_FD_STAT_ATR_TUNNEL)

/* The following काष्ठाure contains the data parsed from the user-defined
 * field of the ethtool_rx_flow_spec काष्ठाure.
 */
काष्ठा i40e_rx_flow_userdef अणु
	bool flex_filter;
	u16 flex_word;
	u16 flex_offset;
पूर्ण;

काष्ठा i40e_fdir_filter अणु
	काष्ठा hlist_node fdir_node;
	/* filter ipnut set */
	u8 flow_type;
	u8 ipl4_proto;
	/* TX packet view of src and dst */
	__be32 dst_ip;
	__be32 src_ip;
	__be32 dst_ip6[4];
	__be32 src_ip6[4];
	__be16 src_port;
	__be16 dst_port;
	__be32 sctp_v_tag;

	__be16 vlan_etype;
	__be16 vlan_tag;
	/* Flexible data to match within the packet payload */
	__be16 flex_word;
	u16 flex_offset;
	bool flex_filter;

	/* filter control */
	u16 q_index;
	u8  flex_off;
	u8  pctype;
	u16 dest_vsi;
	u8  dest_ctl;
	u8  fd_status;
	u16 cnt_index;
	u32 fd_id;
पूर्ण;

#घोषणा I40E_CLOUD_FIELD_OMAC		BIT(0)
#घोषणा I40E_CLOUD_FIELD_IMAC		BIT(1)
#घोषणा I40E_CLOUD_FIELD_IVLAN		BIT(2)
#घोषणा I40E_CLOUD_FIELD_TEN_ID		BIT(3)
#घोषणा I40E_CLOUD_FIELD_IIP		BIT(4)

#घोषणा I40E_CLOUD_FILTER_FLAGS_OMAC	I40E_CLOUD_FIELD_OMAC
#घोषणा I40E_CLOUD_FILTER_FLAGS_IMAC	I40E_CLOUD_FIELD_IMAC
#घोषणा I40E_CLOUD_FILTER_FLAGS_IMAC_IVLAN	(I40E_CLOUD_FIELD_IMAC | \
						 I40E_CLOUD_FIELD_IVLAN)
#घोषणा I40E_CLOUD_FILTER_FLAGS_IMAC_TEN_ID	(I40E_CLOUD_FIELD_IMAC | \
						 I40E_CLOUD_FIELD_TEN_ID)
#घोषणा I40E_CLOUD_FILTER_FLAGS_OMAC_TEN_ID_IMAC (I40E_CLOUD_FIELD_OMAC | \
						  I40E_CLOUD_FIELD_IMAC | \
						  I40E_CLOUD_FIELD_TEN_ID)
#घोषणा I40E_CLOUD_FILTER_FLAGS_IMAC_IVLAN_TEN_ID (I40E_CLOUD_FIELD_IMAC | \
						   I40E_CLOUD_FIELD_IVLAN | \
						   I40E_CLOUD_FIELD_TEN_ID)
#घोषणा I40E_CLOUD_FILTER_FLAGS_IIP	I40E_CLOUD_FIELD_IIP

काष्ठा i40e_cloud_filter अणु
	काष्ठा hlist_node cloud_node;
	अचिन्हित दीर्घ cookie;
	/* cloud filter input set follows */
	u8 dst_mac[ETH_ALEN];
	u8 src_mac[ETH_ALEN];
	__be16 vlan_id;
	u16 seid;       /* filter control */
	__be16 dst_port;
	__be16 src_port;
	u32 tenant_id;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा in_addr dst_ip;
			काष्ठा in_addr src_ip;
		पूर्ण v4;
		काष्ठा अणु
			काष्ठा in6_addr dst_ip6;
			काष्ठा in6_addr src_ip6;
		पूर्ण v6;
	पूर्ण ip;
#घोषणा dst_ipv6	ip.v6.dst_ip6.s6_addr32
#घोषणा src_ipv6	ip.v6.src_ip6.s6_addr32
#घोषणा dst_ipv4	ip.v4.dst_ip.s_addr
#घोषणा src_ipv4	ip.v4.src_ip.s_addr
	u16 n_proto;    /* Ethernet Protocol */
	u8 ip_proto;    /* IPPROTO value */
	u8 flags;
#घोषणा I40E_CLOUD_TNL_TYPE_NONE        0xff
	u8 tunnel_type;
पूर्ण;

#घोषणा I40E_DCB_PRIO_TYPE_STRICT	0
#घोषणा I40E_DCB_PRIO_TYPE_ETS		1
#घोषणा I40E_DCB_STRICT_PRIO_CREDITS	127
/* DCB per TC inक्रमmation data काष्ठाure */
काष्ठा i40e_tc_info अणु
	u16	qoffset;	/* Queue offset from base queue */
	u16	qcount;		/* Total Queues */
	u8	netdev_tc;	/* Netdev TC index अगर netdev associated */
पूर्ण;

/* TC configuration data काष्ठाure */
काष्ठा i40e_tc_configuration अणु
	u8	numtc;		/* Total number of enabled TCs */
	u8	enabled_tc;	/* TC map */
	काष्ठा i40e_tc_info tc_info[I40E_MAX_TRAFFIC_CLASS];
पूर्ण;

#घोषणा I40E_UDP_PORT_INDEX_UNUSED	255
काष्ठा i40e_udp_port_config अणु
	/* AdminQ command पूर्णांकerface expects port number in Host byte order */
	u16 port;
	u8 type;
	u8 filter_index;
पूर्ण;

#घोषणा I40_DDP_FLASH_REGION 100
#घोषणा I40E_PROखाता_INFO_SIZE 48
#घोषणा I40E_MAX_PROखाता_NUM 16
#घोषणा I40E_PROखाता_LIST_SIZE \
	(I40E_PROखाता_INFO_SIZE * I40E_MAX_PROखाता_NUM + 4)
#घोषणा I40E_DDP_PROखाता_PATH "intel/i40e/ddp/"
#घोषणा I40E_DDP_PROखाता_NAME_MAX 64

पूर्णांक i40e_ddp_load(काष्ठा net_device *netdev, स्थिर u8 *data, माप_प्रकार size,
		  bool is_add);
पूर्णांक i40e_ddp_flash(काष्ठा net_device *netdev, काष्ठा ethtool_flash *flash);

काष्ठा i40e_ddp_profile_list अणु
	u32 p_count;
	काष्ठा i40e_profile_info p_info[];
पूर्ण;

काष्ठा i40e_ddp_old_profile_list अणु
	काष्ठा list_head list;
	माप_प्रकार old_ddp_size;
	u8 old_ddp_buf[];
पूर्ण;

/* macros related to FLX_PIT */
#घोषणा I40E_FLEX_SET_FSIZE(fsize) (((fsize) << \
				    I40E_PRTQF_FLX_PIT_FSIZE_SHIFT) & \
				    I40E_PRTQF_FLX_PIT_FSIZE_MASK)
#घोषणा I40E_FLEX_SET_DST_WORD(dst) (((dst) << \
				     I40E_PRTQF_FLX_PIT_DEST_OFF_SHIFT) & \
				     I40E_PRTQF_FLX_PIT_DEST_OFF_MASK)
#घोषणा I40E_FLEX_SET_SRC_WORD(src) (((src) << \
				     I40E_PRTQF_FLX_PIT_SOURCE_OFF_SHIFT) & \
				     I40E_PRTQF_FLX_PIT_SOURCE_OFF_MASK)
#घोषणा I40E_FLEX_PREP_VAL(dst, fsize, src) (I40E_FLEX_SET_DST_WORD(dst) | \
					     I40E_FLEX_SET_FSIZE(fsize) | \
					     I40E_FLEX_SET_SRC_WORD(src))


#घोषणा I40E_MAX_FLEX_SRC_OFFSET 0x1F

/* macros related to GLQF_ORT */
#घोषणा I40E_ORT_SET_IDX(idx)		(((idx) << \
					  I40E_GLQF_ORT_PIT_INDX_SHIFT) & \
					 I40E_GLQF_ORT_PIT_INDX_MASK)

#घोषणा I40E_ORT_SET_COUNT(count)	(((count) << \
					  I40E_GLQF_ORT_FIELD_CNT_SHIFT) & \
					 I40E_GLQF_ORT_FIELD_CNT_MASK)

#घोषणा I40E_ORT_SET_PAYLOAD(payload)	(((payload) << \
					  I40E_GLQF_ORT_FLX_PAYLOAD_SHIFT) & \
					 I40E_GLQF_ORT_FLX_PAYLOAD_MASK)

#घोषणा I40E_ORT_PREP_VAL(idx, count, payload) (I40E_ORT_SET_IDX(idx) | \
						I40E_ORT_SET_COUNT(count) | \
						I40E_ORT_SET_PAYLOAD(payload))

#घोषणा I40E_L3_GLQF_ORT_IDX		34
#घोषणा I40E_L4_GLQF_ORT_IDX		35

/* Flex PIT रेजिस्टर index */
#घोषणा I40E_FLEX_PIT_IDX_START_L3	3
#घोषणा I40E_FLEX_PIT_IDX_START_L4	6

#घोषणा I40E_FLEX_PIT_TABLE_SIZE	3

#घोषणा I40E_FLEX_DEST_UNUSED		63

#घोषणा I40E_FLEX_INDEX_ENTRIES		8

/* Flex MASK to disable all flexible entries */
#घोषणा I40E_FLEX_INPUT_MASK	(I40E_FLEX_50_MASK | I40E_FLEX_51_MASK | \
				 I40E_FLEX_52_MASK | I40E_FLEX_53_MASK | \
				 I40E_FLEX_54_MASK | I40E_FLEX_55_MASK | \
				 I40E_FLEX_56_MASK | I40E_FLEX_57_MASK)

काष्ठा i40e_flex_pit अणु
	काष्ठा list_head list;
	u16 src_offset;
	u8 pit_index;
पूर्ण;

काष्ठा i40e_fwd_adapter अणु
	काष्ठा net_device *netdev;
	पूर्णांक bit_no;
पूर्ण;

काष्ठा i40e_channel अणु
	काष्ठा list_head list;
	bool initialized;
	u8 type;
	u16 vsi_number; /* Asचिन्हित VSI number from AQ 'Add VSI' response */
	u16 stat_counter_idx;
	u16 base_queue;
	u16 num_queue_pairs; /* Requested by user */
	u16 seid;

	u8 enabled_tc;
	काष्ठा i40e_aqc_vsi_properties_data info;

	u64 max_tx_rate;
	काष्ठा i40e_fwd_adapter *fwd;

	/* track this channel beदीर्घs to which VSI */
	काष्ठा i40e_vsi *parent_vsi;
पूर्ण;

अटल अंतरभूत bool i40e_is_channel_macvlan(काष्ठा i40e_channel *ch)
अणु
	वापस !!ch->fwd;
पूर्ण

अटल अंतरभूत u8 *i40e_channel_mac(काष्ठा i40e_channel *ch)
अणु
	अगर (i40e_is_channel_macvlan(ch))
		वापस ch->fwd->netdev->dev_addr;
	अन्यथा
		वापस शून्य;
पूर्ण

/* काष्ठा that defines the Ethernet device */
काष्ठा i40e_pf अणु
	काष्ठा pci_dev *pdev;
	काष्ठा i40e_hw hw;
	DECLARE_BITMAP(state, __I40E_STATE_SIZE__);
	काष्ठा msix_entry *msix_entries;
	bool fc_स्वतःneg_status;

	u16 eeprom_version;
	u16 num_vmdq_vsis;         /* num vmdq vsis this PF has set up */
	u16 num_vmdq_qps;          /* num queue pairs per vmdq pool */
	u16 num_vmdq_msix;         /* num queue vectors per vmdq pool */
	u16 num_req_vfs;           /* num VFs requested क्रम this PF */
	u16 num_vf_qps;            /* num queue pairs per VF */
	u16 num_lan_qps;           /* num lan queues this PF has set up */
	u16 num_lan_msix;          /* num queue vectors क्रम the base PF vsi */
	u16 num_fdsb_msix;         /* num queue vectors क्रम sideband Fdir */
	u16 num_iwarp_msix;        /* num of iwarp vectors क्रम this PF */
	पूर्णांक iwarp_base_vector;
	पूर्णांक queues_left;           /* queues left unclaimed */
	u16 alloc_rss_size;        /* allocated RSS queues */
	u16 rss_size_max;          /* HW defined max RSS queues */
	u16 fdir_pf_filter_count;  /* num of guaranteed filters क्रम this PF */
	u16 num_alloc_vsi;         /* num VSIs this driver supports */
	u8 atr_sample_rate;
	bool wol_en;

	काष्ठा hlist_head fdir_filter_list;
	u16 fdir_pf_active_filters;
	अचिन्हित दीर्घ fd_flush_बारtamp;
	u32 fd_flush_cnt;
	u32 fd_add_err;
	u32 fd_atr_cnt;

	/* Book-keeping of side-band filter count per flow-type.
	 * This is used to detect and handle input set changes क्रम
	 * respective flow-type.
	 */
	u16 fd_tcp4_filter_cnt;
	u16 fd_udp4_filter_cnt;
	u16 fd_sctp4_filter_cnt;
	u16 fd_ip4_filter_cnt;

	u16 fd_tcp6_filter_cnt;
	u16 fd_udp6_filter_cnt;
	u16 fd_sctp6_filter_cnt;
	u16 fd_ip6_filter_cnt;

	/* Flexible filter table values that need to be programmed पूर्णांकo
	 * hardware, which expects L3 and L4 to be programmed separately. We
	 * need to ensure that the values are in ascended order and करोn't have
	 * duplicates, so we track each L3 and L4 values in separate lists.
	 */
	काष्ठा list_head l3_flex_pit_list;
	काष्ठा list_head l4_flex_pit_list;

	काष्ठा udp_tunnel_nic_shared udp_tunnel_shared;
	काष्ठा udp_tunnel_nic_info udp_tunnel_nic;

	काष्ठा hlist_head cloud_filter_list;
	u16 num_cloud_filters;

	क्रमागत i40e_पूर्णांकerrupt_policy पूर्णांक_policy;
	u16 rx_itr_शेष;
	u16 tx_itr_शेष;
	u32 msg_enable;
	अक्षर पूर्णांक_name[I40E_INT_NAME_STR_LEN];
	u16 adminq_work_limit; /* num of admin receive queue desc to process */
	अचिन्हित दीर्घ service_समयr_period;
	अचिन्हित दीर्घ service_समयr_previous;
	काष्ठा समयr_list service_समयr;
	काष्ठा work_काष्ठा service_task;

	u32 hw_features;
#घोषणा I40E_HW_RSS_AQ_CAPABLE			BIT(0)
#घोषणा I40E_HW_128_QP_RSS_CAPABLE		BIT(1)
#घोषणा I40E_HW_ATR_EVICT_CAPABLE		BIT(2)
#घोषणा I40E_HW_WB_ON_ITR_CAPABLE		BIT(3)
#घोषणा I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE	BIT(4)
#घोषणा I40E_HW_NO_PCI_LINK_CHECK		BIT(5)
#घोषणा I40E_HW_100M_SGMII_CAPABLE		BIT(6)
#घोषणा I40E_HW_NO_DCB_SUPPORT			BIT(7)
#घोषणा I40E_HW_USE_SET_LLDP_MIB		BIT(8)
#घोषणा I40E_HW_GENEVE_OFFLOAD_CAPABLE		BIT(9)
#घोषणा I40E_HW_PTP_L4_CAPABLE			BIT(10)
#घोषणा I40E_HW_WOL_MC_MAGIC_PKT_WAKE		BIT(11)
#घोषणा I40E_HW_HAVE_CRT_RETIMER		BIT(13)
#घोषणा I40E_HW_OUTER_UDP_CSUM_CAPABLE		BIT(14)
#घोषणा I40E_HW_PHY_CONTROLS_LEDS		BIT(15)
#घोषणा I40E_HW_STOP_FW_LLDP			BIT(16)
#घोषणा I40E_HW_PORT_ID_VALID			BIT(17)
#घोषणा I40E_HW_RESTART_AUTONEG			BIT(18)

	u32 flags;
#घोषणा I40E_FLAG_RX_CSUM_ENABLED		BIT(0)
#घोषणा I40E_FLAG_MSI_ENABLED			BIT(1)
#घोषणा I40E_FLAG_MSIX_ENABLED			BIT(2)
#घोषणा I40E_FLAG_RSS_ENABLED			BIT(3)
#घोषणा I40E_FLAG_VMDQ_ENABLED			BIT(4)
#घोषणा I40E_FLAG_SRIOV_ENABLED			BIT(5)
#घोषणा I40E_FLAG_DCB_CAPABLE			BIT(6)
#घोषणा I40E_FLAG_DCB_ENABLED			BIT(7)
#घोषणा I40E_FLAG_FD_SB_ENABLED			BIT(8)
#घोषणा I40E_FLAG_FD_ATR_ENABLED		BIT(9)
#घोषणा I40E_FLAG_MFP_ENABLED			BIT(10)
#घोषणा I40E_FLAG_HW_ATR_EVICT_ENABLED		BIT(11)
#घोषणा I40E_FLAG_VEB_MODE_ENABLED		BIT(12)
#घोषणा I40E_FLAG_VEB_STATS_ENABLED		BIT(13)
#घोषणा I40E_FLAG_LINK_POLLING_ENABLED		BIT(14)
#घोषणा I40E_FLAG_TRUE_PROMISC_SUPPORT		BIT(15)
#घोषणा I40E_FLAG_LEGACY_RX			BIT(16)
#घोषणा I40E_FLAG_PTP				BIT(17)
#घोषणा I40E_FLAG_IWARP_ENABLED			BIT(18)
#घोषणा I40E_FLAG_LINK_DOWN_ON_CLOSE_ENABLED	BIT(19)
#घोषणा I40E_FLAG_SOURCE_PRUNING_DISABLED       BIT(20)
#घोषणा I40E_FLAG_TC_MQPRIO			BIT(21)
#घोषणा I40E_FLAG_FD_SB_INACTIVE		BIT(22)
#घोषणा I40E_FLAG_FD_SB_TO_CLOUD_FILTER		BIT(23)
#घोषणा I40E_FLAG_DISABLE_FW_LLDP		BIT(24)
#घोषणा I40E_FLAG_RS_FEC			BIT(25)
#घोषणा I40E_FLAG_BASE_R_FEC			BIT(26)
/* TOTAL_PORT_SHUTDOWN
 * Allows to physically disable the link on the NIC's port.
 * If enabled, (after link करोwn request from the OS)
 * no link, traffic or led activity is possible on that port.
 *
 * If I40E_FLAG_TOTAL_PORT_SHUTDOWN_ENABLED is set, the
 * I40E_FLAG_LINK_DOWN_ON_CLOSE_ENABLED must be explicitly क्रमced to true
 * and cannot be disabled by प्रणाली admin at that समय.
 * The functionalities are exclusive in terms of configuration, but they also
 * have similar behavior (allowing to disable physical link of the port),
 * with following dअगरferences:
 * - LINK_DOWN_ON_CLOSE_ENABLED is configurable at host OS run-समय and is
 *   supported by whole family of 7xx Intel Ethernet Controllers
 * - TOTAL_PORT_SHUTDOWN may be enabled only beक्रमe OS loads (in BIOS)
 *   only अगर motherboard's BIOS and NIC's FW has support of it
 * - when LINK_DOWN_ON_CLOSE_ENABLED is used, the link is being brought करोwn
 *   by sending phy_type=0 to NIC's FW
 * - when TOTAL_PORT_SHUTDOWN is used, phy_type is not altered, instead
 *   the link is being brought करोwn by clearing bit (I40E_AQ_PHY_ENABLE_LINK)
 *   in abilities field of i40e_aq_set_phy_config काष्ठाure
 */
#घोषणा I40E_FLAG_TOTAL_PORT_SHUTDOWN_ENABLED	BIT(27)

	काष्ठा i40e_client_instance *cinst;
	bool stat_offsets_loaded;
	काष्ठा i40e_hw_port_stats stats;
	काष्ठा i40e_hw_port_stats stats_offsets;
	u32 tx_समयout_count;
	u32 tx_समयout_recovery_level;
	अचिन्हित दीर्घ tx_समयout_last_recovery;
	u32 tx_sluggish_count;
	u32 hw_csum_rx_error;
	u32 led_status;
	u16 corer_count; /* Core reset count */
	u16 globr_count; /* Global reset count */
	u16 empr_count; /* EMP reset count */
	u16 pfr_count; /* PF reset count */
	u16 sw_पूर्णांक_count; /* SW पूर्णांकerrupt count */

	काष्ठा mutex चयन_mutex;
	u16 lan_vsi;       /* our शेष LAN VSI */
	u16 lan_veb;       /* initial relay, अगर exists */
#घोषणा I40E_NO_VEB	0xffff
#घोषणा I40E_NO_VSI	0xffff
	u16 next_vsi;      /* Next unallocated VSI - 0-based! */
	काष्ठा i40e_vsi **vsi;
	काष्ठा i40e_veb *veb[I40E_MAX_VEB];

	काष्ठा i40e_lump_tracking *qp_pile;
	काष्ठा i40e_lump_tracking *irq_pile;

	/* चयन config info */
	u16 pf_seid;
	u16 मुख्य_vsi_seid;
	u16 mac_seid;
	काष्ठा kobject *चयन_kobj;
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *i40e_dbg_pf;
#पूर्ण_अगर /* CONFIG_DEBUG_FS */
	bool cur_promisc;

	u16 instance; /* A unique number per i40e_pf instance in the प्रणाली */

	/* sr-iov config info */
	काष्ठा i40e_vf *vf;
	पूर्णांक num_alloc_vfs;	/* actual number of VFs allocated */
	u32 vf_aq_requests;
	u32 arq_overflows;	/* Not fatal, possibly indicative of problems */

	/* DCBx/DCBNL capability क्रम PF that indicates
	 * whether DCBx is managed by firmware or host
	 * based agent (LLDPAD). Also, indicates what
	 * flavor of DCBx protocol (IEEE/CEE) is supported
	 * by the device. For now we're supporting IEEE
	 * mode only.
	 */
	u16 dcbx_cap;

	काष्ठा i40e_filter_control_settings filter_settings;
	काष्ठा i40e_rx_pb_config pb_cfg; /* Current Rx packet buffer config */
	काष्ठा i40e_dcbx_config पंचांगp_cfg;

	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info ptp_caps;
	काष्ठा sk_buff *ptp_tx_skb;
	अचिन्हित दीर्घ ptp_tx_start;
	काष्ठा hwtstamp_config tstamp_config;
	काष्ठा बारpec64 ptp_prev_hw_समय;
	kसमय_प्रकार ptp_reset_start;
	काष्ठा mutex पंचांगreg_lock; /* Used to protect the SYSTIME रेजिस्टरs. */
	u32 ptp_adj_mult;
	u32 tx_hwtstamp_समयouts;
	u32 tx_hwtstamp_skipped;
	u32 rx_hwtstamp_cleared;
	u32 latch_event_flags;
	spinlock_t ptp_rx_lock; /* Used to protect Rx बारtamp रेजिस्टरs. */
	अचिन्हित दीर्घ latch_events[4];
	bool ptp_tx;
	bool ptp_rx;
	u16 rss_table_size; /* HW RSS table size */
	u32 max_bw;
	u32 min_bw;

	u32 ioremap_len;
	u32 fd_inv;
	u16 phy_led_val;

	u16 override_q_count;
	u16 last_sw_conf_flags;
	u16 last_sw_conf_valid_flags;
	/* List to keep previous DDP profiles to be rolled back in the future */
	काष्ठा list_head ddp_old_prof;
पूर्ण;

/**
 * i40e_mac_to_hkey - Convert a 6-byte MAC Address to a u64 hash key
 * @macaddr: the MAC Address as the base key
 *
 * Simply copies the address and वापसs it as a u64 क्रम hashing
 **/
अटल अंतरभूत u64 i40e_addr_to_hkey(स्थिर u8 *macaddr)
अणु
	u64 key = 0;

	ether_addr_copy((u8 *)&key, macaddr);
	वापस key;
पूर्ण

क्रमागत i40e_filter_state अणु
	I40E_FILTER_INVALID = 0,	/* Invalid state */
	I40E_FILTER_NEW,		/* New, not sent to FW yet */
	I40E_FILTER_ACTIVE,		/* Added to चयन by FW */
	I40E_FILTER_FAILED,		/* Rejected by FW */
	I40E_FILTER_REMOVE,		/* To be हटाओd */
/* There is no 'removed' state; the filter काष्ठा is मुक्तd */
पूर्ण;
काष्ठा i40e_mac_filter अणु
	काष्ठा hlist_node hlist;
	u8 macaddr[ETH_ALEN];
#घोषणा I40E_VLAN_ANY -1
	s16 vlan;
	क्रमागत i40e_filter_state state;
पूर्ण;

/* Wrapper काष्ठाure to keep track of filters जबतक we are preparing to send
 * firmware commands. We cannot send firmware commands जबतक holding a
 * spinlock, since it might sleep. To aव्योम this, we wrap the added filters in
 * a separate काष्ठाure, which will track the state change and update the real
 * filter जबतक under lock. We can't simply hold the filters in a separate
 * list, as this खोलोs a winकरोw क्रम a race condition when adding new MAC
 * addresses to all VLANs, or when adding new VLANs to all MAC addresses.
 */
काष्ठा i40e_new_mac_filter अणु
	काष्ठा hlist_node hlist;
	काष्ठा i40e_mac_filter *f;

	/* Track future changes to state separately */
	क्रमागत i40e_filter_state state;
पूर्ण;

काष्ठा i40e_veb अणु
	काष्ठा i40e_pf *pf;
	u16 idx;
	u16 veb_idx;		/* index of VEB parent */
	u16 seid;
	u16 uplink_seid;
	u16 stats_idx;		/* index of VEB parent */
	u8  enabled_tc;
	u16 bridge_mode;	/* Bridge Mode (VEB/VEPA) */
	u16 flags;
	u16 bw_limit;
	u8  bw_max_quanta;
	bool is_असल_credits;
	u8  bw_tc_share_credits[I40E_MAX_TRAFFIC_CLASS];
	u16 bw_tc_limit_credits[I40E_MAX_TRAFFIC_CLASS];
	u8  bw_tc_max_quanta[I40E_MAX_TRAFFIC_CLASS];
	काष्ठा kobject *kobj;
	bool stat_offsets_loaded;
	काष्ठा i40e_eth_stats stats;
	काष्ठा i40e_eth_stats stats_offsets;
	काष्ठा i40e_veb_tc_stats tc_stats;
	काष्ठा i40e_veb_tc_stats tc_stats_offsets;
पूर्ण;

/* काष्ठा that defines a VSI, associated with a dev */
काष्ठा i40e_vsi अणु
	काष्ठा net_device *netdev;
	अचिन्हित दीर्घ active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	bool netdev_रेजिस्टरed;
	bool stat_offsets_loaded;

	u32 current_netdev_flags;
	DECLARE_BITMAP(state, __I40E_VSI_STATE_SIZE__);
#घोषणा I40E_VSI_FLAG_FILTER_CHANGED	BIT(0)
#घोषणा I40E_VSI_FLAG_VEB_OWNER		BIT(1)
	अचिन्हित दीर्घ flags;

	/* Per VSI lock to protect elements/hash (MAC filter) */
	spinlock_t mac_filter_hash_lock;
	/* Fixed size hash table with 2^8 buckets क्रम MAC filters */
	DECLARE_HASHTABLE(mac_filter_hash, 8);
	bool has_vlan_filter;

	/* VSI stats */
	काष्ठा rtnl_link_stats64 net_stats;
	काष्ठा rtnl_link_stats64 net_stats_offsets;
	काष्ठा i40e_eth_stats eth_stats;
	काष्ठा i40e_eth_stats eth_stats_offsets;
	u32 tx_restart;
	u32 tx_busy;
	u64 tx_linearize;
	u64 tx_क्रमce_wb;
	u32 rx_buf_failed;
	u32 rx_page_failed;

	/* These are containers of ring poपूर्णांकers, allocated at run-समय */
	काष्ठा i40e_ring **rx_rings;
	काष्ठा i40e_ring **tx_rings;
	काष्ठा i40e_ring **xdp_rings; /* XDP Tx rings */

	u32  active_filters;
	u32  promisc_threshold;

	u16 work_limit;
	u16 पूर्णांक_rate_limit;	/* value in usecs */

	u16 rss_table_size;	/* HW RSS table size */
	u16 rss_size;		/* Allocated RSS queues */
	u8  *rss_hkey_user;	/* User configured hash keys */
	u8  *rss_lut_user;	/* User configured lookup table entries */


	u16 max_frame;
	u16 rx_buf_len;

	काष्ठा bpf_prog *xdp_prog;

	/* List of q_vectors allocated to this VSI */
	काष्ठा i40e_q_vector **q_vectors;
	पूर्णांक num_q_vectors;
	पूर्णांक base_vector;
	bool irqs_पढ़ोy;

	u16 seid;		/* HW index of this VSI (असलolute index) */
	u16 id;			/* VSI number */
	u16 uplink_seid;

	u16 base_queue;		/* vsi's first queue in hw array */
	u16 alloc_queue_pairs;	/* Allocated Tx/Rx queues */
	u16 req_queue_pairs;	/* User requested queue pairs */
	u16 num_queue_pairs;	/* Used tx and rx pairs */
	u16 num_tx_desc;
	u16 num_rx_desc;
	क्रमागत i40e_vsi_type type;  /* VSI type, e.g., LAN, FCoE, etc */
	s16 vf_id;		/* Virtual function ID क्रम SRIOV VSIs */

	काष्ठा tc_mqprio_qopt_offload mqprio_qopt; /* queue parameters */
	काष्ठा i40e_tc_configuration tc_config;
	काष्ठा i40e_aqc_vsi_properties_data info;

	/* VSI BW limit (असलolute across all TCs) */
	u16 bw_limit;		/* VSI BW Limit (0 = disabled) */
	u8  bw_max_quanta;	/* Max Quanta when BW limit is enabled */

	/* Relative TC credits across VSIs */
	u8  bw_ets_share_credits[I40E_MAX_TRAFFIC_CLASS];
	/* TC BW limit credits within VSI */
	u16  bw_ets_limit_credits[I40E_MAX_TRAFFIC_CLASS];
	/* TC BW limit max quanta within VSI */
	u8  bw_ets_max_quanta[I40E_MAX_TRAFFIC_CLASS];

	काष्ठा i40e_pf *back;	/* Backreference to associated PF */
	u16 idx;		/* index in pf->vsi[] */
	u16 veb_idx;		/* index of VEB parent */
	काष्ठा kobject *kobj;	/* sysfs object */
	bool current_isup;	/* Sync 'link up' logging */
	क्रमागत i40e_aq_link_speed current_speed;	/* Sync link speed logging */

	/* channel specअगरic fields */
	u16 cnt_q_avail;	/* num of queues available क्रम channel usage */
	u16 orig_rss_size;
	u16 current_rss_size;
	bool reconfig_rss;

	u16 next_base_queue;	/* next queue to be used क्रम channel setup */

	काष्ठा list_head ch_list;
	u16 tc_seid_map[I40E_MAX_TRAFFIC_CLASS];

	/* macvlan fields */
#घोषणा I40E_MAX_MACVLANS		128 /* Max HW vectors - 1 on FVL */
#घोषणा I40E_MIN_MACVLAN_VECTORS	2   /* Min vectors to enable macvlans */
	DECLARE_BITMAP(fwd_biपंचांगask, I40E_MAX_MACVLANS);
	काष्ठा list_head macvlan_list;
	पूर्णांक macvlan_cnt;

	व्योम *priv;	/* client driver data reference. */

	/* VSI specअगरic handlers */
	irqवापस_t (*irq_handler)(पूर्णांक irq, व्योम *data);

	अचिन्हित दीर्घ *af_xdp_zc_qps; /* tracks AF_XDP ZC enabled qps */
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

काष्ठा i40e_netdev_priv अणु
	काष्ठा i40e_vsi *vsi;
पूर्ण;

/* काष्ठा that defines an पूर्णांकerrupt vector */
काष्ठा i40e_q_vector अणु
	काष्ठा i40e_vsi *vsi;

	u16 v_idx;		/* index in the vsi->q_vector array. */
	u16 reg_idx;		/* रेजिस्टर index of the पूर्णांकerrupt */

	काष्ठा napi_काष्ठा napi;

	काष्ठा i40e_ring_container rx;
	काष्ठा i40e_ring_container tx;

	u8 itr_countकरोwn;	/* when 0 should adjust adaptive ITR */
	u8 num_ringpairs;	/* total number of ring pairs in vector */

	cpumask_t affinity_mask;
	काष्ठा irq_affinity_notअगरy affinity_notअगरy;

	काष्ठा rcu_head rcu;	/* to aव्योम race with update stats on मुक्त */
	अक्षर name[I40E_INT_NAME_STR_LEN];
	bool arm_wb_state;
पूर्ण ____cacheline_पूर्णांकernodealigned_in_smp;

/* lan device */
काष्ठा i40e_device अणु
	काष्ठा list_head list;
	काष्ठा i40e_pf *pf;
पूर्ण;

/**
 * i40e_nvm_version_str - क्रमmat the NVM version strings
 * @hw: ptr to the hardware info
 **/
अटल अंतरभूत अक्षर *i40e_nvm_version_str(काष्ठा i40e_hw *hw)
अणु
	अटल अक्षर buf[32];
	u32 full_ver;

	full_ver = hw->nvm.oem_ver;

	अगर (hw->nvm.eetrack == I40E_OEM_EETRACK_ID) अणु
		u8 gen, snap;
		u16 release;

		gen = (u8)(full_ver >> I40E_OEM_GEN_SHIFT);
		snap = (u8)((full_ver & I40E_OEM_SNAP_MASK) >>
			I40E_OEM_SNAP_SHIFT);
		release = (u16)(full_ver & I40E_OEM_RELEASE_MASK);

		snम_लिखो(buf, माप(buf), "%x.%x.%x", gen, snap, release);
	पूर्ण अन्यथा अणु
		u8 ver, patch;
		u16 build;

		ver = (u8)(full_ver >> I40E_OEM_VER_SHIFT);
		build = (u16)((full_ver >> I40E_OEM_VER_BUILD_SHIFT) &
			 I40E_OEM_VER_BUILD_MASK);
		patch = (u8)(full_ver & I40E_OEM_VER_PATCH_MASK);

		snम_लिखो(buf, माप(buf),
			 "%x.%02x 0x%x %d.%d.%d",
			 (hw->nvm.version & I40E_NVM_VERSION_HI_MASK) >>
				I40E_NVM_VERSION_HI_SHIFT,
			 (hw->nvm.version & I40E_NVM_VERSION_LO_MASK) >>
				I40E_NVM_VERSION_LO_SHIFT,
			 hw->nvm.eetrack, ver, build, patch);
	पूर्ण

	वापस buf;
पूर्ण

/**
 * i40e_netdev_to_pf: Retrieve the PF काष्ठा क्रम given netdev
 * @netdev: the corresponding netdev
 *
 * Return the PF काष्ठा क्रम the given netdev
 **/
अटल अंतरभूत काष्ठा i40e_pf *i40e_netdev_to_pf(काष्ठा net_device *netdev)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(netdev);
	काष्ठा i40e_vsi *vsi = np->vsi;

	वापस vsi->back;
पूर्ण

अटल अंतरभूत व्योम i40e_vsi_setup_irqhandler(काष्ठा i40e_vsi *vsi,
				irqवापस_t (*irq_handler)(पूर्णांक, व्योम *))
अणु
	vsi->irq_handler = irq_handler;
पूर्ण

/**
 * i40e_get_fd_cnt_all - get the total FD filter space available
 * @pf: poपूर्णांकer to the PF काष्ठा
 **/
अटल अंतरभूत पूर्णांक i40e_get_fd_cnt_all(काष्ठा i40e_pf *pf)
अणु
	वापस pf->hw.fdir_shared_filter_count + pf->fdir_pf_filter_count;
पूर्ण

/**
 * i40e_पढ़ो_fd_input_set - पढ़ोs value of flow director input set रेजिस्टर
 * @pf: poपूर्णांकer to the PF काष्ठा
 * @addr: रेजिस्टर addr
 *
 * This function पढ़ोs value of flow director input set रेजिस्टर
 * specअगरied by 'addr' (which is specअगरic to flow-type)
 **/
अटल अंतरभूत u64 i40e_पढ़ो_fd_input_set(काष्ठा i40e_pf *pf, u16 addr)
अणु
	u64 val;

	val = i40e_पढ़ो_rx_ctl(&pf->hw, I40E_PRTQF_FD_INSET(addr, 1));
	val <<= 32;
	val += i40e_पढ़ो_rx_ctl(&pf->hw, I40E_PRTQF_FD_INSET(addr, 0));

	वापस val;
पूर्ण

/**
 * i40e_ग_लिखो_fd_input_set - ग_लिखोs value पूर्णांकo flow director input set रेजिस्टर
 * @pf: poपूर्णांकer to the PF काष्ठा
 * @addr: रेजिस्टर addr
 * @val: value to be written
 *
 * This function ग_लिखोs specअगरied value to the रेजिस्टर specअगरied by 'addr'.
 * This रेजिस्टर is input set रेजिस्टर based on flow-type.
 **/
अटल अंतरभूत व्योम i40e_ग_लिखो_fd_input_set(काष्ठा i40e_pf *pf,
					   u16 addr, u64 val)
अणु
	i40e_ग_लिखो_rx_ctl(&pf->hw, I40E_PRTQF_FD_INSET(addr, 1),
			  (u32)(val >> 32));
	i40e_ग_लिखो_rx_ctl(&pf->hw, I40E_PRTQF_FD_INSET(addr, 0),
			  (u32)(val & 0xFFFFFFFFULL));
पूर्ण

/* needed by i40e_ethtool.c */
पूर्णांक i40e_up(काष्ठा i40e_vsi *vsi);
व्योम i40e_करोwn(काष्ठा i40e_vsi *vsi);
बाह्य स्थिर अक्षर i40e_driver_name[];
व्योम i40e_करो_reset_safe(काष्ठा i40e_pf *pf, u32 reset_flags);
व्योम i40e_करो_reset(काष्ठा i40e_pf *pf, u32 reset_flags, bool lock_acquired);
पूर्णांक i40e_config_rss(काष्ठा i40e_vsi *vsi, u8 *seed, u8 *lut, u16 lut_size);
पूर्णांक i40e_get_rss(काष्ठा i40e_vsi *vsi, u8 *seed, u8 *lut, u16 lut_size);
व्योम i40e_fill_rss_lut(काष्ठा i40e_pf *pf, u8 *lut,
		       u16 rss_table_size, u16 rss_size);
काष्ठा i40e_vsi *i40e_find_vsi_from_id(काष्ठा i40e_pf *pf, u16 id);
/**
 * i40e_find_vsi_by_type - Find and वापस Flow Director VSI
 * @pf: PF to search क्रम VSI
 * @type: Value indicating type of VSI we are looking क्रम
 **/
अटल अंतरभूत काष्ठा i40e_vsi *
i40e_find_vsi_by_type(काष्ठा i40e_pf *pf, u16 type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pf->num_alloc_vsi; i++) अणु
		काष्ठा i40e_vsi *vsi = pf->vsi[i];

		अगर (vsi && vsi->type == type)
			वापस vsi;
	पूर्ण

	वापस शून्य;
पूर्ण
व्योम i40e_update_stats(काष्ठा i40e_vsi *vsi);
व्योम i40e_update_veb_stats(काष्ठा i40e_veb *veb);
व्योम i40e_update_eth_stats(काष्ठा i40e_vsi *vsi);
काष्ठा rtnl_link_stats64 *i40e_get_vsi_stats_काष्ठा(काष्ठा i40e_vsi *vsi);
पूर्णांक i40e_fetch_चयन_configuration(काष्ठा i40e_pf *pf,
				    bool prपूर्णांकconfig);

पूर्णांक i40e_add_del_fdir(काष्ठा i40e_vsi *vsi,
		      काष्ठा i40e_fdir_filter *input, bool add);
व्योम i40e_fdir_check_and_reenable(काष्ठा i40e_pf *pf);
u32 i40e_get_current_fd_count(काष्ठा i40e_pf *pf);
u32 i40e_get_cur_guaranteed_fd_count(काष्ठा i40e_pf *pf);
u32 i40e_get_current_atr_cnt(काष्ठा i40e_pf *pf);
u32 i40e_get_global_fd_count(काष्ठा i40e_pf *pf);
bool i40e_set_ntuple(काष्ठा i40e_pf *pf, netdev_features_t features);
व्योम i40e_set_ethtool_ops(काष्ठा net_device *netdev);
काष्ठा i40e_mac_filter *i40e_add_filter(काष्ठा i40e_vsi *vsi,
					स्थिर u8 *macaddr, s16 vlan);
व्योम __i40e_del_filter(काष्ठा i40e_vsi *vsi, काष्ठा i40e_mac_filter *f);
व्योम i40e_del_filter(काष्ठा i40e_vsi *vsi, स्थिर u8 *macaddr, s16 vlan);
पूर्णांक i40e_sync_vsi_filters(काष्ठा i40e_vsi *vsi);
काष्ठा i40e_vsi *i40e_vsi_setup(काष्ठा i40e_pf *pf, u8 type,
				u16 uplink, u32 param1);
पूर्णांक i40e_vsi_release(काष्ठा i40e_vsi *vsi);
व्योम i40e_service_event_schedule(काष्ठा i40e_pf *pf);
व्योम i40e_notअगरy_client_of_vf_msg(काष्ठा i40e_vsi *vsi, u32 vf_id,
				  u8 *msg, u16 len);

पूर्णांक i40e_control_रुको_tx_q(पूर्णांक seid, काष्ठा i40e_pf *pf, पूर्णांक pf_q, bool is_xdp,
			   bool enable);
पूर्णांक i40e_control_रुको_rx_q(काष्ठा i40e_pf *pf, पूर्णांक pf_q, bool enable);
पूर्णांक i40e_vsi_start_rings(काष्ठा i40e_vsi *vsi);
व्योम i40e_vsi_stop_rings(काष्ठा i40e_vsi *vsi);
व्योम i40e_vsi_stop_rings_no_रुको(काष्ठा  i40e_vsi *vsi);
पूर्णांक i40e_vsi_रुको_queues_disabled(काष्ठा i40e_vsi *vsi);
पूर्णांक i40e_reconfig_rss_queues(काष्ठा i40e_pf *pf, पूर्णांक queue_count);
काष्ठा i40e_veb *i40e_veb_setup(काष्ठा i40e_pf *pf, u16 flags, u16 uplink_seid,
				u16 करोwnlink_seid, u8 enabled_tc);
व्योम i40e_veb_release(काष्ठा i40e_veb *veb);

पूर्णांक i40e_veb_config_tc(काष्ठा i40e_veb *veb, u8 enabled_tc);
पूर्णांक i40e_vsi_add_pvid(काष्ठा i40e_vsi *vsi, u16 vid);
व्योम i40e_vsi_हटाओ_pvid(काष्ठा i40e_vsi *vsi);
व्योम i40e_vsi_reset_stats(काष्ठा i40e_vsi *vsi);
व्योम i40e_pf_reset_stats(काष्ठा i40e_pf *pf);
#अगर_घोषित CONFIG_DEBUG_FS
व्योम i40e_dbg_pf_init(काष्ठा i40e_pf *pf);
व्योम i40e_dbg_pf_निकास(काष्ठा i40e_pf *pf);
व्योम i40e_dbg_init(व्योम);
व्योम i40e_dbg_निकास(व्योम);
#अन्यथा
अटल अंतरभूत व्योम i40e_dbg_pf_init(काष्ठा i40e_pf *pf) अणुपूर्ण
अटल अंतरभूत व्योम i40e_dbg_pf_निकास(काष्ठा i40e_pf *pf) अणुपूर्ण
अटल अंतरभूत व्योम i40e_dbg_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम i40e_dbg_निकास(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS*/
/* needed by client drivers */
पूर्णांक i40e_lan_add_device(काष्ठा i40e_pf *pf);
पूर्णांक i40e_lan_del_device(काष्ठा i40e_pf *pf);
व्योम i40e_client_subtask(काष्ठा i40e_pf *pf);
व्योम i40e_notअगरy_client_of_l2_param_changes(काष्ठा i40e_vsi *vsi);
व्योम i40e_notअगरy_client_of_netdev_बंद(काष्ठा i40e_vsi *vsi, bool reset);
व्योम i40e_notअगरy_client_of_vf_enable(काष्ठा i40e_pf *pf, u32 num_vfs);
व्योम i40e_notअगरy_client_of_vf_reset(काष्ठा i40e_pf *pf, u32 vf_id);
व्योम i40e_client_update_msix_info(काष्ठा i40e_pf *pf);
पूर्णांक i40e_vf_client_capable(काष्ठा i40e_pf *pf, u32 vf_id);
/**
 * i40e_irq_dynamic_enable - Enable शेष पूर्णांकerrupt generation settings
 * @vsi: poपूर्णांकer to a vsi
 * @vector: enable a particular Hw Interrupt vector, without base_vector
 **/
अटल अंतरभूत व्योम i40e_irq_dynamic_enable(काष्ठा i40e_vsi *vsi, पूर्णांक vector)
अणु
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_hw *hw = &pf->hw;
	u32 val;

	val = I40E_PFINT_DYN_CTLN_INTENA_MASK |
	      I40E_PFINT_DYN_CTLN_CLEARPBA_MASK |
	      (I40E_ITR_NONE << I40E_PFINT_DYN_CTLN_ITR_INDX_SHIFT);
	wr32(hw, I40E_PFINT_DYN_CTLN(vector + vsi->base_vector - 1), val);
	/* skip the flush */
पूर्ण

व्योम i40e_irq_dynamic_disable_icr0(काष्ठा i40e_pf *pf);
व्योम i40e_irq_dynamic_enable_icr0(काष्ठा i40e_pf *pf);
पूर्णांक i40e_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);
पूर्णांक i40e_खोलो(काष्ठा net_device *netdev);
पूर्णांक i40e_बंद(काष्ठा net_device *netdev);
पूर्णांक i40e_vsi_खोलो(काष्ठा i40e_vsi *vsi);
व्योम i40e_vlan_stripping_disable(काष्ठा i40e_vsi *vsi);
पूर्णांक i40e_add_vlan_all_mac(काष्ठा i40e_vsi *vsi, s16 vid);
पूर्णांक i40e_vsi_add_vlan(काष्ठा i40e_vsi *vsi, u16 vid);
व्योम i40e_rm_vlan_all_mac(काष्ठा i40e_vsi *vsi, s16 vid);
व्योम i40e_vsi_समाप्त_vlan(काष्ठा i40e_vsi *vsi, u16 vid);
काष्ठा i40e_mac_filter *i40e_add_mac_filter(काष्ठा i40e_vsi *vsi,
					    स्थिर u8 *macaddr);
पूर्णांक i40e_del_mac_filter(काष्ठा i40e_vsi *vsi, स्थिर u8 *macaddr);
bool i40e_is_vsi_in_vlan(काष्ठा i40e_vsi *vsi);
पूर्णांक i40e_count_filters(काष्ठा i40e_vsi *vsi);
काष्ठा i40e_mac_filter *i40e_find_mac(काष्ठा i40e_vsi *vsi, स्थिर u8 *macaddr);
व्योम i40e_vlan_stripping_enable(काष्ठा i40e_vsi *vsi);
अटल अंतरभूत bool i40e_is_sw_dcb(काष्ठा i40e_pf *pf)
अणु
	वापस !!(pf->flags & I40E_FLAG_DISABLE_FW_LLDP);
पूर्ण

#अगर_घोषित CONFIG_I40E_DCB
व्योम i40e_dcbnl_flush_apps(काष्ठा i40e_pf *pf,
			   काष्ठा i40e_dcbx_config *old_cfg,
			   काष्ठा i40e_dcbx_config *new_cfg);
व्योम i40e_dcbnl_set_all(काष्ठा i40e_vsi *vsi);
व्योम i40e_dcbnl_setup(काष्ठा i40e_vsi *vsi);
bool i40e_dcb_need_reconfig(काष्ठा i40e_pf *pf,
			    काष्ठा i40e_dcbx_config *old_cfg,
			    काष्ठा i40e_dcbx_config *new_cfg);
पूर्णांक i40e_hw_dcb_config(काष्ठा i40e_pf *pf, काष्ठा i40e_dcbx_config *new_cfg);
पूर्णांक i40e_dcb_sw_शेष_config(काष्ठा i40e_pf *pf);
#पूर्ण_अगर /* CONFIG_I40E_DCB */
व्योम i40e_ptp_rx_hang(काष्ठा i40e_pf *pf);
व्योम i40e_ptp_tx_hang(काष्ठा i40e_pf *pf);
व्योम i40e_ptp_tx_hwtstamp(काष्ठा i40e_pf *pf);
व्योम i40e_ptp_rx_hwtstamp(काष्ठा i40e_pf *pf, काष्ठा sk_buff *skb, u8 index);
व्योम i40e_ptp_set_increment(काष्ठा i40e_pf *pf);
पूर्णांक i40e_ptp_set_ts_config(काष्ठा i40e_pf *pf, काष्ठा अगरreq *अगरr);
पूर्णांक i40e_ptp_get_ts_config(काष्ठा i40e_pf *pf, काष्ठा अगरreq *अगरr);
व्योम i40e_ptp_save_hw_समय(काष्ठा i40e_pf *pf);
व्योम i40e_ptp_restore_hw_समय(काष्ठा i40e_pf *pf);
व्योम i40e_ptp_init(काष्ठा i40e_pf *pf);
व्योम i40e_ptp_stop(काष्ठा i40e_pf *pf);
पूर्णांक i40e_is_vsi_uplink_mode_veb(काष्ठा i40e_vsi *vsi);
i40e_status i40e_get_partition_bw_setting(काष्ठा i40e_pf *pf);
i40e_status i40e_set_partition_bw_setting(काष्ठा i40e_pf *pf);
i40e_status i40e_commit_partition_bw_setting(काष्ठा i40e_pf *pf);
व्योम i40e_prपूर्णांक_link_message(काष्ठा i40e_vsi *vsi, bool isup);

व्योम i40e_set_fec_in_flags(u8 fec_cfg, u32 *flags);

अटल अंतरभूत bool i40e_enabled_xdp_vsi(काष्ठा i40e_vsi *vsi)
अणु
	वापस !!READ_ONCE(vsi->xdp_prog);
पूर्ण

पूर्णांक i40e_create_queue_channel(काष्ठा i40e_vsi *vsi, काष्ठा i40e_channel *ch);
पूर्णांक i40e_set_bw_limit(काष्ठा i40e_vsi *vsi, u16 seid, u64 max_tx_rate);
पूर्णांक i40e_add_del_cloud_filter(काष्ठा i40e_vsi *vsi,
			      काष्ठा i40e_cloud_filter *filter,
			      bool add);
पूर्णांक i40e_add_del_cloud_filter_big_buf(काष्ठा i40e_vsi *vsi,
				      काष्ठा i40e_cloud_filter *filter,
				      bool add);
#पूर्ण_अगर /* _I40E_H_ */
