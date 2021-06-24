<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _ICE_TYPE_H_
#घोषणा _ICE_TYPE_H_

#घोषणा ICE_BYTES_PER_WORD	2
#घोषणा ICE_BYTES_PER_DWORD	4

#समावेश "ice_status.h"
#समावेश "ice_hw_autogen.h"
#समावेश "ice_osdep.h"
#समावेश "ice_controlq.h"
#समावेश "ice_lan_tx_rx.h"
#समावेश "ice_flex_type.h"
#समावेश "ice_protocol_type.h"

अटल अंतरभूत bool ice_is_tc_ena(अचिन्हित दीर्घ biपंचांगap, u8 tc)
अणु
	वापस test_bit(tc, &biपंचांगap);
पूर्ण

अटल अंतरभूत u64 round_up_64bit(u64 a, u32 b)
अणु
	वापस भाग64_दीर्घ(((a) + (b) / 2), (b));
पूर्ण

अटल अंतरभूत u32 ice_round_to_num(u32 N, u32 R)
अणु
	वापस ((((N) % (R)) < ((R) / 2)) ? (((N) / (R)) * (R)) :
		((((N) + (R) - 1) / (R)) * (R)));
पूर्ण

/* Driver always calls मुख्य vsi_handle first */
#घोषणा ICE_MAIN_VSI_HANDLE		0

/* debug masks - set these bits in hw->debug_mask to control output */
#घोषणा ICE_DBG_INIT		BIT_ULL(1)
#घोषणा ICE_DBG_FW_LOG		BIT_ULL(3)
#घोषणा ICE_DBG_LINK		BIT_ULL(4)
#घोषणा ICE_DBG_PHY		BIT_ULL(5)
#घोषणा ICE_DBG_QCTX		BIT_ULL(6)
#घोषणा ICE_DBG_NVM		BIT_ULL(7)
#घोषणा ICE_DBG_LAN		BIT_ULL(8)
#घोषणा ICE_DBG_FLOW		BIT_ULL(9)
#घोषणा ICE_DBG_SW		BIT_ULL(13)
#घोषणा ICE_DBG_SCHED		BIT_ULL(14)
#घोषणा ICE_DBG_PKG		BIT_ULL(16)
#घोषणा ICE_DBG_RES		BIT_ULL(17)
#घोषणा ICE_DBG_AQ_MSG		BIT_ULL(24)
#घोषणा ICE_DBG_AQ_DESC		BIT_ULL(25)
#घोषणा ICE_DBG_AQ_DESC_BUF	BIT_ULL(26)
#घोषणा ICE_DBG_AQ_CMD		BIT_ULL(27)
#घोषणा ICE_DBG_USER		BIT_ULL(31)

क्रमागत ice_aq_res_ids अणु
	ICE_NVM_RES_ID = 1,
	ICE_SPD_RES_ID,
	ICE_CHANGE_LOCK_RES_ID,
	ICE_GLOBAL_CFG_LOCK_RES_ID
पूर्ण;

/* FW update समयout definitions are in milliseconds */
#घोषणा ICE_NVM_TIMEOUT			180000
#घोषणा ICE_CHANGE_LOCK_TIMEOUT		1000
#घोषणा ICE_GLOBAL_CFG_LOCK_TIMEOUT	3000

क्रमागत ice_aq_res_access_type अणु
	ICE_RES_READ = 1,
	ICE_RES_WRITE
पूर्ण;

काष्ठा ice_driver_ver अणु
	u8 major_ver;
	u8 minor_ver;
	u8 build_ver;
	u8 subbuild_ver;
	u8 driver_string[32];
पूर्ण;

क्रमागत ice_fc_mode अणु
	ICE_FC_NONE = 0,
	ICE_FC_RX_PAUSE,
	ICE_FC_TX_PAUSE,
	ICE_FC_FULL,
	ICE_FC_PFC,
	ICE_FC_DFLT
पूर्ण;

क्रमागत ice_phy_cache_mode अणु
	ICE_FC_MODE = 0,
	ICE_SPEED_MODE,
	ICE_FEC_MODE
पूर्ण;

क्रमागत ice_fec_mode अणु
	ICE_FEC_NONE = 0,
	ICE_FEC_RS,
	ICE_FEC_BASER,
	ICE_FEC_AUTO
पूर्ण;

काष्ठा ice_phy_cache_mode_data अणु
	जोड़ अणु
		क्रमागत ice_fec_mode curr_user_fec_req;
		क्रमागत ice_fc_mode curr_user_fc_req;
		u16 curr_user_speed_req;
	पूर्ण data;
पूर्ण;

क्रमागत ice_set_fc_aq_failures अणु
	ICE_SET_FC_AQ_FAIL_NONE = 0,
	ICE_SET_FC_AQ_FAIL_GET,
	ICE_SET_FC_AQ_FAIL_SET,
	ICE_SET_FC_AQ_FAIL_UPDATE
पूर्ण;

/* Various MAC types */
क्रमागत ice_mac_type अणु
	ICE_MAC_UNKNOWN = 0,
	ICE_MAC_E810,
	ICE_MAC_GENERIC,
पूर्ण;

/* Media Types */
क्रमागत ice_media_type अणु
	ICE_MEDIA_UNKNOWN = 0,
	ICE_MEDIA_FIBER,
	ICE_MEDIA_BASET,
	ICE_MEDIA_BACKPLANE,
	ICE_MEDIA_DA,
पूर्ण;

क्रमागत ice_vsi_type अणु
	ICE_VSI_PF = 0,
	ICE_VSI_VF = 1,
	ICE_VSI_CTRL = 3,	/* equates to ICE_VSI_PF with 1 queue pair */
	ICE_VSI_LB = 6,
पूर्ण;

काष्ठा ice_link_status अणु
	/* Refer to ice_aq_phy_type क्रम bits definition */
	u64 phy_type_low;
	u64 phy_type_high;
	u8 topo_media_conflict;
	u16 max_frame_size;
	u16 link_speed;
	u16 req_speeds;
	u8 lse_ena;	/* Link Status Event notअगरication */
	u8 link_info;
	u8 an_info;
	u8 ext_info;
	u8 fec_info;
	u8 pacing;
	/* Refer to #घोषणा from module_type[ICE_MODULE_TYPE_TOTAL_BYTE] of
	 * ice_aqc_get_phy_caps काष्ठाure
	 */
	u8 module_type[ICE_MODULE_TYPE_TOTAL_BYTE];
पूर्ण;

/* Dअगरferent reset sources क्रम which a disable queue AQ call has to be made in
 * order to clean the Tx scheduler as a part of the reset
 */
क्रमागत ice_disq_rst_src अणु
	ICE_NO_RESET = 0,
	ICE_VM_RESET,
	ICE_VF_RESET,
पूर्ण;

/* PHY info such as phy_type, etc... */
काष्ठा ice_phy_info अणु
	काष्ठा ice_link_status link_info;
	काष्ठा ice_link_status link_info_old;
	u64 phy_type_low;
	u64 phy_type_high;
	क्रमागत ice_media_type media_type;
	u8 get_link_info;
	/* Please refer to काष्ठा ice_aqc_get_link_status_data to get
	 * detail of enable bit in curr_user_speed_req
	 */
	u16 curr_user_speed_req;
	क्रमागत ice_fec_mode curr_user_fec_req;
	क्रमागत ice_fc_mode curr_user_fc_req;
	काष्ठा ice_aqc_set_phy_cfg_data curr_user_phy_cfg;
पूर्ण;

/* protocol क्रमागतeration क्रम filters */
क्रमागत ice_fltr_ptype अणु
	/* NONE - used क्रम undef/error */
	ICE_FLTR_PTYPE_NONF_NONE = 0,
	ICE_FLTR_PTYPE_NONF_IPV4_UDP,
	ICE_FLTR_PTYPE_NONF_IPV4_TCP,
	ICE_FLTR_PTYPE_NONF_IPV4_SCTP,
	ICE_FLTR_PTYPE_NONF_IPV4_OTHER,
	ICE_FLTR_PTYPE_NONF_IPV4_GTPU_IPV4_UDP,
	ICE_FLTR_PTYPE_NONF_IPV4_GTPU_IPV4_TCP,
	ICE_FLTR_PTYPE_NONF_IPV4_GTPU_IPV4_ICMP,
	ICE_FLTR_PTYPE_NONF_IPV4_GTPU_IPV4_OTHER,
	ICE_FLTR_PTYPE_NONF_IPV6_GTPU_IPV6_OTHER,
	ICE_FLTR_PTYPE_NONF_IPV4_L2TPV3,
	ICE_FLTR_PTYPE_NONF_IPV6_L2TPV3,
	ICE_FLTR_PTYPE_NONF_IPV4_ESP,
	ICE_FLTR_PTYPE_NONF_IPV6_ESP,
	ICE_FLTR_PTYPE_NONF_IPV4_AH,
	ICE_FLTR_PTYPE_NONF_IPV6_AH,
	ICE_FLTR_PTYPE_NONF_IPV4_NAT_T_ESP,
	ICE_FLTR_PTYPE_NONF_IPV6_NAT_T_ESP,
	ICE_FLTR_PTYPE_NONF_IPV4_PFCP_NODE,
	ICE_FLTR_PTYPE_NONF_IPV4_PFCP_SESSION,
	ICE_FLTR_PTYPE_NONF_IPV6_PFCP_NODE,
	ICE_FLTR_PTYPE_NONF_IPV6_PFCP_SESSION,
	ICE_FLTR_PTYPE_NON_IP_L2,
	ICE_FLTR_PTYPE_FRAG_IPV4,
	ICE_FLTR_PTYPE_NONF_IPV6_UDP,
	ICE_FLTR_PTYPE_NONF_IPV6_TCP,
	ICE_FLTR_PTYPE_NONF_IPV6_SCTP,
	ICE_FLTR_PTYPE_NONF_IPV6_OTHER,
	ICE_FLTR_PTYPE_MAX,
पूर्ण;

क्रमागत ice_fd_hw_seg अणु
	ICE_FD_HW_SEG_NON_TUN = 0,
	ICE_FD_HW_SEG_TUN,
	ICE_FD_HW_SEG_MAX,
पूर्ण;

/* 2 VSI = 1 ICE_VSI_PF + 1 ICE_VSI_CTRL */
#घोषणा ICE_MAX_Fसूची_VSI_PER_FILTER	2

काष्ठा ice_fd_hw_prof अणु
	काष्ठा ice_flow_seg_info *fdir_seg[ICE_FD_HW_SEG_MAX];
	पूर्णांक cnt;
	u64 entry_h[ICE_MAX_Fसूची_VSI_PER_FILTER][ICE_FD_HW_SEG_MAX];
	u16 vsi_h[ICE_MAX_Fसूची_VSI_PER_FILTER];
पूर्ण;

/* Common HW capabilities क्रम SW use */
काष्ठा ice_hw_common_caps अणु
	u32 valid_functions;
	/* DCB capabilities */
	u32 active_tc_biपंचांगap;
	u32 maxtc;

	/* Tx/Rx queues */
	u16 num_rxq;		/* Number/Total Rx queues */
	u16 rxq_first_id;	/* First queue ID क्रम Rx queues */
	u16 num_txq;		/* Number/Total Tx queues */
	u16 txq_first_id;	/* First queue ID क्रम Tx queues */

	/* MSI-X vectors */
	u16 num_msix_vectors;
	u16 msix_vector_first_id;

	/* Max MTU क्रम function or device */
	u16 max_mtu;

	/* Virtualization support */
	u8 sr_iov_1_1;			/* SR-IOV enabled */

	/* RSS related capabilities */
	u16 rss_table_size;		/* 512 क्रम PFs and 64 क्रम VFs */
	u8 rss_table_entry_width;	/* RSS Entry width in bits */

	u8 dcb;

	bool nvm_update_pending_nvm;
	bool nvm_update_pending_orom;
	bool nvm_update_pending_netlist;
#घोषणा ICE_NVM_PENDING_NVM_IMAGE		BIT(0)
#घोषणा ICE_NVM_PENDING_OROM			BIT(1)
#घोषणा ICE_NVM_PENDING_NETLIST			BIT(2)
	bool nvm_unअगरied_update;
#घोषणा ICE_NVM_MGMT_UNIFIED_UPD_SUPPORT	BIT(3)
पूर्ण;

/* Function specअगरic capabilities */
काष्ठा ice_hw_func_caps अणु
	काष्ठा ice_hw_common_caps common_cap;
	u32 num_allocd_vfs;		/* Number of allocated VFs */
	u32 vf_base_id;			/* Logical ID of the first VF */
	u32 guar_num_vsi;
	u32 fd_fltr_guar;		/* Number of filters guaranteed */
	u32 fd_fltr_best_efक्रमt;	/* Number of best efक्रमt filters */
पूर्ण;

/* Device wide capabilities */
काष्ठा ice_hw_dev_caps अणु
	काष्ठा ice_hw_common_caps common_cap;
	u32 num_vfs_exposed;		/* Total number of VFs exposed */
	u32 num_vsi_allocd_to_host;	/* Excluding EMP VSI */
	u32 num_flow_director_fltr;	/* Number of FD filters available */
	u32 num_funcs;
पूर्ण;

/* MAC info */
काष्ठा ice_mac_info अणु
	u8 lan_addr[ETH_ALEN];
	u8 perm_addr[ETH_ALEN];
पूर्ण;

/* Reset types used to determine which kind of reset was requested. These
 * defines match what the RESET_TYPE field of the GLGEN_RSTAT रेजिस्टर.
 * ICE_RESET_PFR करोes not match any RESET_TYPE field in the GLGEN_RSTAT रेजिस्टर
 * because its reset source is dअगरferent than the other types listed.
 */
क्रमागत ice_reset_req अणु
	ICE_RESET_POR	= 0,
	ICE_RESET_INVAL	= 0,
	ICE_RESET_CORER	= 1,
	ICE_RESET_GLOBR	= 2,
	ICE_RESET_EMPR	= 3,
	ICE_RESET_PFR	= 4,
पूर्ण;

/* Bus parameters */
काष्ठा ice_bus_info अणु
	u16 device;
	u8 func;
पूर्ण;

/* Flow control (FC) parameters */
काष्ठा ice_fc_info अणु
	क्रमागत ice_fc_mode current_mode;	/* FC mode in effect */
	क्रमागत ice_fc_mode req_mode;	/* FC mode requested by caller */
पूर्ण;

/* Option ROM version inक्रमmation */
काष्ठा ice_orom_info अणु
	u8 major;			/* Major version of OROM */
	u8 patch;			/* Patch version of OROM */
	u16 build;			/* Build version of OROM */
पूर्ण;

/* NVM version inक्रमmation */
काष्ठा ice_nvm_info अणु
	u32 eetrack;
	u8 major;
	u8 minor;
पूर्ण;

/* netlist version inक्रमmation */
काष्ठा ice_netlist_info अणु
	u32 major;			/* major high/low */
	u32 minor;			/* minor high/low */
	u32 type;			/* type high/low */
	u32 rev;			/* revision high/low */
	u32 hash;			/* SHA-1 hash word */
	u16 cust_ver;			/* customer version */
पूर्ण;

/* Enumeration of possible flash banks क्रम the NVM, OROM, and Netlist modules
 * of the flash image.
 */
क्रमागत ice_flash_bank अणु
	ICE_INVALID_FLASH_BANK,
	ICE_1ST_FLASH_BANK,
	ICE_2ND_FLASH_BANK,
पूर्ण;

/* Enumeration of which flash bank is desired to पढ़ो from, either the active
 * bank or the inactive bank. Used to असलtract 1st and 2nd bank notion from
 * code which just wants to पढ़ो the active or inactive flash bank.
 */
क्रमागत ice_bank_select अणु
	ICE_ACTIVE_FLASH_BANK,
	ICE_INACTIVE_FLASH_BANK,
पूर्ण;

/* inक्रमmation क्रम accessing NVM, OROM, and Netlist flash banks */
काष्ठा ice_bank_info अणु
	u32 nvm_ptr;				/* Poपूर्णांकer to 1st NVM bank */
	u32 nvm_size;				/* Size of NVM bank */
	u32 orom_ptr;				/* Poपूर्णांकer to 1st OROM bank */
	u32 orom_size;				/* Size of OROM bank */
	u32 netlist_ptr;			/* Poपूर्णांकer to 1st Netlist bank */
	u32 netlist_size;			/* Size of Netlist bank */
	क्रमागत ice_flash_bank nvm_bank;		/* Active NVM bank */
	क्रमागत ice_flash_bank orom_bank;		/* Active OROM bank */
	क्रमागत ice_flash_bank netlist_bank;	/* Active Netlist bank */
पूर्ण;

/* Flash Chip Inक्रमmation */
काष्ठा ice_flash_info अणु
	काष्ठा ice_orom_info orom;	/* Option ROM version info */
	काष्ठा ice_nvm_info nvm;	/* NVM version inक्रमmation */
	काष्ठा ice_netlist_info netlist;/* Netlist version info */
	काष्ठा ice_bank_info banks;	/* Flash Bank inक्रमmation */
	u16 sr_words;			/* Shaकरोw RAM size in words */
	u32 flash_size;			/* Size of available flash in bytes */
	u8 blank_nvm_mode;		/* is NVM empty (no FW present) */
पूर्ण;

काष्ठा ice_link_शेष_override_tlv अणु
	u8 options;
#घोषणा ICE_LINK_OVERRIDE_OPT_M		0x3F
#घोषणा ICE_LINK_OVERRIDE_STRICT_MODE	BIT(0)
#घोषणा ICE_LINK_OVERRIDE_EPCT_DIS	BIT(1)
#घोषणा ICE_LINK_OVERRIDE_PORT_DIS	BIT(2)
#घोषणा ICE_LINK_OVERRIDE_EN		BIT(3)
#घोषणा ICE_LINK_OVERRIDE_AUTO_LINK_DIS	BIT(4)
#घोषणा ICE_LINK_OVERRIDE_EEE_EN	BIT(5)
	u8 phy_config;
#घोषणा ICE_LINK_OVERRIDE_PHY_CFG_S	8
#घोषणा ICE_LINK_OVERRIDE_PHY_CFG_M	(0xC3 << ICE_LINK_OVERRIDE_PHY_CFG_S)
#घोषणा ICE_LINK_OVERRIDE_PAUSE_M	0x3
#घोषणा ICE_LINK_OVERRIDE_LESM_EN	BIT(6)
#घोषणा ICE_LINK_OVERRIDE_AUTO_FEC_EN	BIT(7)
	u8 fec_options;
#घोषणा ICE_LINK_OVERRIDE_FEC_OPT_M	0xFF
	u8 rsvd1;
	u64 phy_type_low;
	u64 phy_type_high;
पूर्ण;

#घोषणा ICE_NVM_VER_LEN	32

/* Max number of port to queue branches w.r.t topology */
#घोषणा ICE_MAX_TRAFFIC_CLASS 8
#घोषणा ICE_TXSCHED_MAX_BRANCHES ICE_MAX_TRAFFIC_CLASS

#घोषणा ice_क्रम_each_traffic_class(_i)	\
	क्रम ((_i) = 0; (_i) < ICE_MAX_TRAFFIC_CLASS; (_i)++)

/* ICE_DFLT_AGG_ID means that all new VM(s)/VSI node connects
 * to driver defined policy क्रम शेष aggregator
 */
#घोषणा ICE_INVAL_TEID 0xFFFFFFFF
#घोषणा ICE_DFLT_AGG_ID 0

काष्ठा ice_sched_node अणु
	काष्ठा ice_sched_node *parent;
	काष्ठा ice_sched_node *sibling; /* next sibling in the same layer */
	काष्ठा ice_sched_node **children;
	काष्ठा ice_aqc_txsched_elem_data info;
	u32 agg_id;			/* aggregator group ID */
	u16 vsi_handle;
	u8 in_use;			/* suspended or in use */
	u8 tx_sched_layer;		/* Logical Layer (1-9) */
	u8 num_children;
	u8 tc_num;
	u8 owner;
#घोषणा ICE_SCHED_NODE_OWNER_LAN	0
पूर्ण;

/* Access Macros क्रम Tx Sched Elements data */
#घोषणा ICE_TXSCHED_GET_NODE_TEID(x) le32_to_cpu((x)->info.node_teid)

/* The aggregator type determines अगर identअगरier is क्रम a VSI group,
 * aggregator group, aggregator of queues, or queue group.
 */
क्रमागत ice_agg_type अणु
	ICE_AGG_TYPE_UNKNOWN = 0,
	ICE_AGG_TYPE_VSI,
	ICE_AGG_TYPE_AGG, /* aggregator */
	ICE_AGG_TYPE_Q,
	ICE_AGG_TYPE_QG
पूर्ण;

/* Rate limit types */
क्रमागत ice_rl_type अणु
	ICE_UNKNOWN_BW = 0,
	ICE_MIN_BW,		/* क्रम CIR profile */
	ICE_MAX_BW,		/* क्रम EIR profile */
	ICE_SHARED_BW		/* क्रम shared profile */
पूर्ण;

#घोषणा ICE_SCHED_MIN_BW		500		/* in Kbps */
#घोषणा ICE_SCHED_MAX_BW		100000000	/* in Kbps */
#घोषणा ICE_SCHED_DFLT_BW		0xFFFFFFFF	/* unlimited */
#घोषणा ICE_SCHED_DFLT_RL_PROF_ID	0
#घोषणा ICE_SCHED_NO_SHARED_RL_PROF_ID	0xFFFF
#घोषणा ICE_SCHED_DFLT_BW_WT		4
#घोषणा ICE_SCHED_INVAL_PROF_ID		0xFFFF
#घोषणा ICE_SCHED_DFLT_BURST_SIZE	(15 * 1024)	/* in bytes (15k) */

 /* Data काष्ठाure क्रम saving BW inक्रमmation */
क्रमागत ice_bw_type अणु
	ICE_BW_TYPE_PRIO,
	ICE_BW_TYPE_CIR,
	ICE_BW_TYPE_CIR_WT,
	ICE_BW_TYPE_EIR,
	ICE_BW_TYPE_EIR_WT,
	ICE_BW_TYPE_SHARED,
	ICE_BW_TYPE_CNT		/* This must be last */
पूर्ण;

काष्ठा ice_bw अणु
	u32 bw;
	u16 bw_alloc;
पूर्ण;

काष्ठा ice_bw_type_info अणु
	DECLARE_BITMAP(bw_t_biपंचांगap, ICE_BW_TYPE_CNT);
	u8 generic;
	काष्ठा ice_bw cir_bw;
	काष्ठा ice_bw eir_bw;
	u32 shared_bw;
पूर्ण;

/* VSI queue context काष्ठाure क्रम given TC */
काष्ठा ice_q_ctx अणु
	u16  q_handle;
	u32  q_teid;
	/* bw_t_info saves queue BW inक्रमmation */
	काष्ठा ice_bw_type_info bw_t_info;
पूर्ण;

/* VSI type list entry to locate corresponding VSI/aggregator nodes */
काष्ठा ice_sched_vsi_info अणु
	काष्ठा ice_sched_node *vsi_node[ICE_MAX_TRAFFIC_CLASS];
	काष्ठा ice_sched_node *ag_node[ICE_MAX_TRAFFIC_CLASS];
	काष्ठा list_head list_entry;
	u16 max_lanq[ICE_MAX_TRAFFIC_CLASS];
पूर्ण;

/* driver defines the policy */
काष्ठा ice_sched_tx_policy अणु
	u16 max_num_vsis;
	u8 max_num_lan_qs_per_tc[ICE_MAX_TRAFFIC_CLASS];
	u8 rdma_ena;
पूर्ण;

/* CEE or IEEE 802.1Qaz ETS Configuration data */
काष्ठा ice_dcb_ets_cfg अणु
	u8 willing;
	u8 cbs;
	u8 maxtcs;
	u8 prio_table[ICE_MAX_TRAFFIC_CLASS];
	u8 tcbwtable[ICE_MAX_TRAFFIC_CLASS];
	u8 tsatable[ICE_MAX_TRAFFIC_CLASS];
पूर्ण;

/* CEE or IEEE 802.1Qaz PFC Configuration data */
काष्ठा ice_dcb_pfc_cfg अणु
	u8 willing;
	u8 mbc;
	u8 pfccap;
	u8 pfcena;
पूर्ण;

/* CEE or IEEE 802.1Qaz Application Priority data */
काष्ठा ice_dcb_app_priority_table अणु
	u16 prot_id;
	u8 priority;
	u8 selector;
पूर्ण;

#घोषणा ICE_MAX_USER_PRIORITY	8
#घोषणा ICE_DCBX_MAX_APPS	32
#घोषणा ICE_LLDPDU_SIZE		1500
#घोषणा ICE_TLV_STATUS_OPER	0x1
#घोषणा ICE_TLV_STATUS_SYNC	0x2
#घोषणा ICE_TLV_STATUS_ERR	0x4
#घोषणा ICE_APP_PROT_ID_ISCSI_860 0x035c
#घोषणा ICE_APP_SEL_ETHTYPE	0x1
#घोषणा ICE_APP_SEL_TCPIP	0x2
#घोषणा ICE_CEE_APP_SEL_ETHTYPE	0x0
#घोषणा ICE_SR_LINK_DEFAULT_OVERRIDE_PTR	0x134
#घोषणा ICE_CEE_APP_SEL_TCPIP	0x1

काष्ठा ice_dcbx_cfg अणु
	u32 numapps;
	u32 tlv_status; /* CEE mode TLV status */
	काष्ठा ice_dcb_ets_cfg etscfg;
	काष्ठा ice_dcb_ets_cfg etsrec;
	काष्ठा ice_dcb_pfc_cfg pfc;
	काष्ठा ice_dcb_app_priority_table app[ICE_DCBX_MAX_APPS];
	u8 dcbx_mode;
#घोषणा ICE_DCBX_MODE_CEE	0x1
#घोषणा ICE_DCBX_MODE_IEEE	0x2
	u8 app_mode;
#घोषणा ICE_DCBX_APPS_NON_WILLING	0x1
पूर्ण;

काष्ठा ice_qos_cfg अणु
	काष्ठा ice_dcbx_cfg local_dcbx_cfg;	/* Oper/Local Cfg */
	काष्ठा ice_dcbx_cfg desired_dcbx_cfg;	/* CEE Desired Cfg */
	काष्ठा ice_dcbx_cfg remote_dcbx_cfg;	/* Peer Cfg */
	u8 dcbx_status : 3;			/* see ICE_DCBX_STATUS_DIS */
	u8 is_sw_lldp : 1;
पूर्ण;

काष्ठा ice_port_info अणु
	काष्ठा ice_sched_node *root;	/* Root Node per Port */
	काष्ठा ice_hw *hw;		/* back poपूर्णांकer to HW instance */
	u32 last_node_teid;		/* scheduler last node info */
	u16 sw_id;			/* Initial चयन ID beदीर्घs to port */
	u16 pf_vf_num;
	u8 port_state;
#घोषणा ICE_SCHED_PORT_STATE_INIT	0x0
#घोषणा ICE_SCHED_PORT_STATE_READY	0x1
	u8 lport;
#घोषणा ICE_LPORT_MASK			0xff
	u16 dflt_tx_vsi_rule_id;
	u16 dflt_tx_vsi_num;
	u16 dflt_rx_vsi_rule_id;
	u16 dflt_rx_vsi_num;
	काष्ठा ice_fc_info fc;
	काष्ठा ice_mac_info mac;
	काष्ठा ice_phy_info phy;
	काष्ठा mutex sched_lock;	/* protect access to TXSched tree */
	काष्ठा ice_sched_node *
		sib_head[ICE_MAX_TRAFFIC_CLASS][ICE_AQC_TOPO_MAX_LEVEL_NUM];
	/* List contain profile ID(s) and other params per layer */
	काष्ठा list_head rl_prof_list[ICE_AQC_TOPO_MAX_LEVEL_NUM];
	काष्ठा ice_qos_cfg qos_cfg;
	u8 is_vf:1;
पूर्ण;

काष्ठा ice_चयन_info अणु
	काष्ठा list_head vsi_list_map_head;
	काष्ठा ice_sw_recipe *recp_list;
पूर्ण;

/* FW logging configuration */
काष्ठा ice_fw_log_evnt अणु
	u8 cfg : 4;	/* New event enables to configure */
	u8 cur : 4;	/* Current/active event enables */
पूर्ण;

काष्ठा ice_fw_log_cfg अणु
	u8 cq_en : 1;    /* FW logging is enabled via the control queue */
	u8 uart_en : 1;  /* FW logging is enabled via UART क्रम all PFs */
	u8 actv_evnts;   /* Cumulation of currently enabled log events */

#घोषणा ICE_FW_LOG_EVNT_INFO	(ICE_AQC_FW_LOG_INFO_EN >> ICE_AQC_FW_LOG_EN_S)
#घोषणा ICE_FW_LOG_EVNT_INIT	(ICE_AQC_FW_LOG_INIT_EN >> ICE_AQC_FW_LOG_EN_S)
#घोषणा ICE_FW_LOG_EVNT_FLOW	(ICE_AQC_FW_LOG_FLOW_EN >> ICE_AQC_FW_LOG_EN_S)
#घोषणा ICE_FW_LOG_EVNT_ERR	(ICE_AQC_FW_LOG_ERR_EN >> ICE_AQC_FW_LOG_EN_S)
	काष्ठा ice_fw_log_evnt evnts[ICE_AQC_FW_LOG_ID_MAX];
पूर्ण;

/* Enum defining the dअगरferent states of the mailbox snapshot in the
 * PF-VF mailbox overflow detection algorithm. The snapshot can be in
 * states:
 * 1. ICE_MAL_VF_DETECT_STATE_NEW_SNAPSHOT - generate a new अटल snapshot
 * within the mailbox buffer.
 * 2. ICE_MAL_VF_DETECT_STATE_TRAVERSE - iterate through the mailbox snaphot
 * 3. ICE_MAL_VF_DETECT_STATE_DETECT - track the messages sent per VF via the
 * mailbox and mark any VFs sending more messages than the threshold limit set.
 * 4. ICE_MAL_VF_DETECT_STATE_INVALID - Invalid mailbox state set to 0xFFFFFFFF.
 */
क्रमागत ice_mbx_snapshot_state अणु
	ICE_MAL_VF_DETECT_STATE_NEW_SNAPSHOT = 0,
	ICE_MAL_VF_DETECT_STATE_TRAVERSE,
	ICE_MAL_VF_DETECT_STATE_DETECT,
	ICE_MAL_VF_DETECT_STATE_INVALID = 0xFFFFFFFF,
पूर्ण;

/* Structure to hold inक्रमmation of the अटल snapshot and the mailbox
 * buffer data used to generate and track the snapshot.
 * 1. state: the state of the mailbox snapshot in the malicious VF
 * detection state handler ice_mbx_vf_state_handler()
 * 2. head: head of the mailbox snapshot in a circular mailbox buffer
 * 3. tail: tail of the mailbox snapshot in a circular mailbox buffer
 * 4. num_iterations: number of messages traversed in circular mailbox buffer
 * 5. num_msg_proc: number of messages processed in mailbox
 * 6. num_pending_arq: number of pending asynchronous messages
 * 7. max_num_msgs_mbx: maximum messages in mailbox क्रम currently
 * serviced work item or पूर्णांकerrupt.
 */
काष्ठा ice_mbx_snap_buffer_data अणु
	क्रमागत ice_mbx_snapshot_state state;
	u32 head;
	u32 tail;
	u32 num_iterations;
	u16 num_msg_proc;
	u16 num_pending_arq;
	u16 max_num_msgs_mbx;
पूर्ण;

/* Structure to track messages sent by VFs on mailbox:
 * 1. vf_cntr: a counter array of VFs to track the number of
 * asynchronous messages sent by each VF
 * 2. vfcntr_len: number of entries in VF counter array
 */
काष्ठा ice_mbx_vf_counter अणु
	u32 *vf_cntr;
	u32 vfcntr_len;
पूर्ण;

/* Structure to hold data relevant to the captured अटल snapshot
 * of the PF-VF mailbox.
 */
काष्ठा ice_mbx_snapshot अणु
	काष्ठा ice_mbx_snap_buffer_data mbx_buf;
	काष्ठा ice_mbx_vf_counter mbx_vf;
पूर्ण;

/* Structure to hold data to be used क्रम capturing or updating a
 * अटल snapshot.
 * 1. num_msg_proc: number of messages processed in mailbox
 * 2. num_pending_arq: number of pending asynchronous messages
 * 3. max_num_msgs_mbx: maximum messages in mailbox क्रम currently
 * serviced work item or पूर्णांकerrupt.
 * 4. async_watermark_val: An upper threshold set by caller to determine
 * अगर the pending arq count is large enough to assume that there is
 * the possibility of a mailicious VF.
 */
काष्ठा ice_mbx_data अणु
	u16 num_msg_proc;
	u16 num_pending_arq;
	u16 max_num_msgs_mbx;
	u16 async_watermark_val;
पूर्ण;

/* Port hardware description */
काष्ठा ice_hw अणु
	u8 __iomem *hw_addr;
	व्योम *back;
	काष्ठा ice_aqc_layer_props *layer_info;
	काष्ठा ice_port_info *port_info;
	/* PSM घड़ी frequency क्रम calculating RL profile params */
	u32 psm_clk_freq;
	u64 debug_mask;		/* biपंचांगap क्रम debug mask */
	क्रमागत ice_mac_type mac_type;

	u16 fd_ctr_base;	/* FD counter base index */

	/* pci info */
	u16 device_id;
	u16 venकरोr_id;
	u16 subप्रणाली_device_id;
	u16 subप्रणाली_venकरोr_id;
	u8 revision_id;

	u8 pf_id;		/* device profile info */

	u16 max_burst_size;	/* driver sets this value */

	/* Tx Scheduler values */
	u8 num_tx_sched_layers;
	u8 num_tx_sched_phys_layers;
	u8 flattened_layers;
	u8 max_cgds;
	u8 sw_entry_poपूर्णांक_layer;
	u16 max_children[ICE_AQC_TOPO_MAX_LEVEL_NUM];
	काष्ठा list_head agg_list;	/* lists all aggregator */

	काष्ठा ice_vsi_ctx *vsi_ctx[ICE_MAX_VSI];
	u8 evb_veb;		/* true क्रम VEB, false क्रम VEPA */
	u8 reset_ongoing;	/* true अगर HW is in reset, false otherwise */
	काष्ठा ice_bus_info bus;
	काष्ठा ice_flash_info flash;
	काष्ठा ice_hw_dev_caps dev_caps;	/* device capabilities */
	काष्ठा ice_hw_func_caps func_caps;	/* function capabilities */

	काष्ठा ice_चयन_info *चयन_info;	/* चयन filter lists */

	/* Control Queue info */
	काष्ठा ice_ctl_q_info adminq;
	काष्ठा ice_ctl_q_info mailboxq;

	u8 api_branch;		/* API branch version */
	u8 api_maj_ver;		/* API major version */
	u8 api_min_ver;		/* API minor version */
	u8 api_patch;		/* API patch version */
	u8 fw_branch;		/* firmware branch version */
	u8 fw_maj_ver;		/* firmware major version */
	u8 fw_min_ver;		/* firmware minor version */
	u8 fw_patch;		/* firmware patch version */
	u32 fw_build;		/* firmware build number */

	काष्ठा ice_fw_log_cfg fw_log;

/* Device max aggregate bandwidths corresponding to the GL_PWR_MODE_CTL
 * रेजिस्टर. Used क्रम determining the ITR/INTRL granularity during
 * initialization.
 */
#घोषणा ICE_MAX_AGG_BW_200G	0x0
#घोषणा ICE_MAX_AGG_BW_100G	0X1
#घोषणा ICE_MAX_AGG_BW_50G	0x2
#घोषणा ICE_MAX_AGG_BW_25G	0x3
	/* ITR granularity क्रम dअगरferent speeds */
#घोषणा ICE_ITR_GRAN_ABOVE_25	2
#घोषणा ICE_ITR_GRAN_MAX_25	4
	/* ITR granularity in 1 us */
	u8 itr_gran;
	/* INTRL granularity क्रम dअगरferent speeds */
#घोषणा ICE_INTRL_GRAN_ABOVE_25	4
#घोषणा ICE_INTRL_GRAN_MAX_25	8
	/* INTRL granularity in 1 us */
	u8 पूर्णांकrl_gran;

	u8 ucast_shared;	/* true अगर VSIs can share unicast addr */

	/* Active package version (currently active) */
	काष्ठा ice_pkg_ver active_pkg_ver;
	u32 active_track_id;
	u8 active_pkg_name[ICE_PKG_NAME_SIZE];
	u8 active_pkg_in_nvm;

	क्रमागत ice_aq_err pkg_dwnld_status;

	/* Driver's package ver - (from the Ice Metadata section) */
	काष्ठा ice_pkg_ver pkg_ver;
	u8 pkg_name[ICE_PKG_NAME_SIZE];

	/* Driver's Ice segment क्रमmat version and ID (from the Ice seg) */
	काष्ठा ice_pkg_ver ice_seg_fmt_ver;
	u8 ice_seg_id[ICE_SEG_ID_SIZE];

	/* Poपूर्णांकer to the ice segment */
	काष्ठा ice_seg *seg;

	/* Poपूर्णांकer to allocated copy of pkg memory */
	u8 *pkg_copy;
	u32 pkg_size;

	/* tunneling info */
	काष्ठा mutex tnl_lock;
	काष्ठा ice_tunnel_table tnl;

	काष्ठा udp_tunnel_nic_shared udp_tunnel_shared;
	काष्ठा udp_tunnel_nic_info udp_tunnel_nic;

	/* HW block tables */
	काष्ठा ice_blk_info blk[ICE_BLK_COUNT];
	काष्ठा mutex fl_profs_locks[ICE_BLK_COUNT];	/* lock fltr profiles */
	काष्ठा list_head fl_profs[ICE_BLK_COUNT];

	/* Flow Director filter info */
	पूर्णांक fdir_active_fltr;

	काष्ठा mutex fdir_fltr_lock;	/* protect Flow Director */
	काष्ठा list_head fdir_list_head;

	/* Book-keeping of side-band filter count per flow-type.
	 * This is used to detect and handle input set changes क्रम
	 * respective flow-type.
	 */
	u16 fdir_fltr_cnt[ICE_FLTR_PTYPE_MAX];

	काष्ठा ice_fd_hw_prof **fdir_prof;
	DECLARE_BITMAP(fdir_perfect_fltr, ICE_FLTR_PTYPE_MAX);
	काष्ठा mutex rss_locks;	/* protect RSS configuration */
	काष्ठा list_head rss_list_head;
	काष्ठा ice_mbx_snapshot mbx_snapshot;
पूर्ण;

/* Statistics collected by each port, VSI, VEB, and S-channel */
काष्ठा ice_eth_stats अणु
	u64 rx_bytes;			/* gorc */
	u64 rx_unicast;			/* uprc */
	u64 rx_multicast;		/* mprc */
	u64 rx_broadcast;		/* bprc */
	u64 rx_discards;		/* rdpc */
	u64 rx_unknown_protocol;	/* rupp */
	u64 tx_bytes;			/* gotc */
	u64 tx_unicast;			/* uptc */
	u64 tx_multicast;		/* mptc */
	u64 tx_broadcast;		/* bptc */
	u64 tx_discards;		/* tdpc */
	u64 tx_errors;			/* tepc */
पूर्ण;

#घोषणा ICE_MAX_UP	8

/* Statistics collected by the MAC */
काष्ठा ice_hw_port_stats अणु
	/* eth stats collected by the port */
	काष्ठा ice_eth_stats eth;
	/* additional port specअगरic stats */
	u64 tx_dropped_link_करोwn;	/* tकरोld */
	u64 crc_errors;			/* crcerrs */
	u64 illegal_bytes;		/* illerrc */
	u64 error_bytes;		/* errbc */
	u64 mac_local_faults;		/* mlfc */
	u64 mac_remote_faults;		/* mrfc */
	u64 rx_len_errors;		/* rlec */
	u64 link_xon_rx;		/* lxonrxc */
	u64 link_xoff_rx;		/* lxoffrxc */
	u64 link_xon_tx;		/* lxontxc */
	u64 link_xoff_tx;		/* lxofftxc */
	u64 priority_xon_rx[8];		/* pxonrxc[8] */
	u64 priority_xoff_rx[8];	/* pxoffrxc[8] */
	u64 priority_xon_tx[8];		/* pxontxc[8] */
	u64 priority_xoff_tx[8];	/* pxofftxc[8] */
	u64 priority_xon_2_xoff[8];	/* pxon2offc[8] */
	u64 rx_size_64;			/* prc64 */
	u64 rx_size_127;		/* prc127 */
	u64 rx_size_255;		/* prc255 */
	u64 rx_size_511;		/* prc511 */
	u64 rx_size_1023;		/* prc1023 */
	u64 rx_size_1522;		/* prc1522 */
	u64 rx_size_big;		/* prc9522 */
	u64 rx_undersize;		/* ruc */
	u64 rx_fragments;		/* rfc */
	u64 rx_oversize;		/* roc */
	u64 rx_jabber;			/* rjc */
	u64 tx_size_64;			/* ptc64 */
	u64 tx_size_127;		/* ptc127 */
	u64 tx_size_255;		/* ptc255 */
	u64 tx_size_511;		/* ptc511 */
	u64 tx_size_1023;		/* ptc1023 */
	u64 tx_size_1522;		/* ptc1522 */
	u64 tx_size_big;		/* ptc9522 */
	/* flow director stats */
	u32 fd_sb_status;
	u64 fd_sb_match;
पूर्ण;

काष्ठा ice_aq_get_set_rss_lut_params अणु
	u16 vsi_handle;		/* software VSI handle */
	u16 lut_size;		/* size of the LUT buffer */
	u8 lut_type;		/* type of the LUT (i.e. VSI, PF, Global) */
	u8 *lut;		/* input RSS LUT क्रम set and output RSS LUT क्रम get */
	u8 global_lut_id;	/* only valid when lut_type is global */
पूर्ण;

/* Checksum and Shaकरोw RAM poपूर्णांकers */
#घोषणा ICE_SR_NVM_CTRL_WORD		0x00
#घोषणा ICE_SR_BOOT_CFG_PTR		0x132
#घोषणा ICE_SR_NVM_WOL_CFG		0x19
#घोषणा ICE_NVM_OROM_VER_OFF		0x02
#घोषणा ICE_SR_PBA_BLOCK_PTR		0x16
#घोषणा ICE_SR_NVM_DEV_STARTER_VER	0x18
#घोषणा ICE_SR_NVM_EETRACK_LO		0x2D
#घोषणा ICE_SR_NVM_EETRACK_HI		0x2E
#घोषणा ICE_NVM_VER_LO_SHIFT		0
#घोषणा ICE_NVM_VER_LO_MASK		(0xff << ICE_NVM_VER_LO_SHIFT)
#घोषणा ICE_NVM_VER_HI_SHIFT		12
#घोषणा ICE_NVM_VER_HI_MASK		(0xf << ICE_NVM_VER_HI_SHIFT)
#घोषणा ICE_OROM_VER_PATCH_SHIFT	0
#घोषणा ICE_OROM_VER_PATCH_MASK		(0xff << ICE_OROM_VER_PATCH_SHIFT)
#घोषणा ICE_OROM_VER_BUILD_SHIFT	8
#घोषणा ICE_OROM_VER_BUILD_MASK		(0xffff << ICE_OROM_VER_BUILD_SHIFT)
#घोषणा ICE_OROM_VER_SHIFT		24
#घोषणा ICE_OROM_VER_MASK		(0xff << ICE_OROM_VER_SHIFT)
#घोषणा ICE_SR_PFA_PTR			0x40
#घोषणा ICE_SR_1ST_NVM_BANK_PTR		0x42
#घोषणा ICE_SR_NVM_BANK_SIZE		0x43
#घोषणा ICE_SR_1ST_OROM_BANK_PTR	0x44
#घोषणा ICE_SR_OROM_BANK_SIZE		0x45
#घोषणा ICE_SR_NETLIST_BANK_PTR		0x46
#घोषणा ICE_SR_NETLIST_BANK_SIZE	0x47
#घोषणा ICE_SR_SECTOR_SIZE_IN_WORDS	0x800

/* CSS Header words */
#घोषणा ICE_NVM_CSS_SREV_L			0x14
#घोषणा ICE_NVM_CSS_SREV_H			0x15

/* Length of CSS header section in words */
#घोषणा ICE_CSS_HEADER_LENGTH			330

/* Offset of Shaकरोw RAM copy in the NVM bank area. */
#घोषणा ICE_NVM_SR_COPY_WORD_OFFSET		roundup(ICE_CSS_HEADER_LENGTH, 32)

/* Size in bytes of Option ROM trailer */
#घोषणा ICE_NVM_OROM_TRAILER_LENGTH		(2 * ICE_CSS_HEADER_LENGTH)

/* The Link Topology Netlist section is stored as a series of words. It is
 * stored in the NVM as a TLV, with the first two words containing the type
 * and length.
 */
#घोषणा ICE_NETLIST_LINK_TOPO_MOD_ID		0x011B
#घोषणा ICE_NETLIST_TYPE_OFFSET			0x0000
#घोषणा ICE_NETLIST_LEN_OFFSET			0x0001

/* The Link Topology section follows the TLV header. When पढ़ोing the netlist
 * using ice_पढ़ो_netlist_module, we need to account क्रम the 2-word TLV
 * header.
 */
#घोषणा ICE_NETLIST_LINK_TOPO_OFFSET(n)		((n) + 2)

#घोषणा ICE_LINK_TOPO_MODULE_LEN		ICE_NETLIST_LINK_TOPO_OFFSET(0x0000)
#घोषणा ICE_LINK_TOPO_NODE_COUNT		ICE_NETLIST_LINK_TOPO_OFFSET(0x0001)

#घोषणा ICE_LINK_TOPO_NODE_COUNT_M		ICE_M(0x3FF, 0)

/* The Netlist ID Block is located after all of the Link Topology nodes. */
#घोषणा ICE_NETLIST_ID_BLK_SIZE			0x30
#घोषणा ICE_NETLIST_ID_BLK_OFFSET(n)		ICE_NETLIST_LINK_TOPO_OFFSET(0x0004 + 2 * (n))

/* netlist ID block field offsets (word offsets) */
#घोषणा ICE_NETLIST_ID_BLK_MAJOR_VER_LOW	0x02
#घोषणा ICE_NETLIST_ID_BLK_MAJOR_VER_HIGH	0x03
#घोषणा ICE_NETLIST_ID_BLK_MINOR_VER_LOW	0x04
#घोषणा ICE_NETLIST_ID_BLK_MINOR_VER_HIGH	0x05
#घोषणा ICE_NETLIST_ID_BLK_TYPE_LOW		0x06
#घोषणा ICE_NETLIST_ID_BLK_TYPE_HIGH		0x07
#घोषणा ICE_NETLIST_ID_BLK_REV_LOW		0x08
#घोषणा ICE_NETLIST_ID_BLK_REV_HIGH		0x09
#घोषणा ICE_NETLIST_ID_BLK_SHA_HASH_WORD(n)	(0x0A + (n))
#घोषणा ICE_NETLIST_ID_BLK_CUST_VER		0x2F

/* Auxiliary field, mask, and shअगरt definition क्रम Shaकरोw RAM and NVM Flash */
#घोषणा ICE_SR_CTRL_WORD_1_S		0x06
#घोषणा ICE_SR_CTRL_WORD_1_M		(0x03 << ICE_SR_CTRL_WORD_1_S)
#घोषणा ICE_SR_CTRL_WORD_VALID		0x1
#घोषणा ICE_SR_CTRL_WORD_OROM_BANK	BIT(3)
#घोषणा ICE_SR_CTRL_WORD_NETLIST_BANK	BIT(4)
#घोषणा ICE_SR_CTRL_WORD_NVM_BANK	BIT(5)

#घोषणा ICE_SR_NVM_PTR_4KB_UNITS	BIT(15)

/* Link override related */
#घोषणा ICE_SR_PFA_LINK_OVERRIDE_WORDS		10
#घोषणा ICE_SR_PFA_LINK_OVERRIDE_PHY_WORDS	4
#घोषणा ICE_SR_PFA_LINK_OVERRIDE_OFFSET		2
#घोषणा ICE_SR_PFA_LINK_OVERRIDE_FEC_OFFSET	1
#घोषणा ICE_SR_PFA_LINK_OVERRIDE_PHY_OFFSET	2
#घोषणा ICE_FW_API_LINK_OVERRIDE_MAJ		1
#घोषणा ICE_FW_API_LINK_OVERRIDE_MIN		5
#घोषणा ICE_FW_API_LINK_OVERRIDE_PATCH		2

#घोषणा ICE_SR_WORDS_IN_1KB		512

/* Hash redirection LUT क्रम VSI - maximum array size */
#घोषणा ICE_VSIQF_HLUT_ARRAY_SIZE	((VSIQF_HLUT_MAX_INDEX + 1) * 4)

/* AQ API version क्रम LLDP_FILTER_CONTROL */
#घोषणा ICE_FW_API_LLDP_FLTR_MAJ	1
#घोषणा ICE_FW_API_LLDP_FLTR_MIN	7
#घोषणा ICE_FW_API_LLDP_FLTR_PATCH	1

/* AQ API version क्रम report शेष configuration */
#घोषणा ICE_FW_API_REPORT_DFLT_CFG_MAJ		1
#घोषणा ICE_FW_API_REPORT_DFLT_CFG_MIN		7
#घोषणा ICE_FW_API_REPORT_DFLT_CFG_PATCH	3

#पूर्ण_अगर /* _ICE_TYPE_H_ */
