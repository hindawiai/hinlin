<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_H
#घोषणा _QED_H

#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/zlib.h>
#समावेश <linux/hashtable.h>
#समावेश <linux/qed/qed_अगर.h>
#समावेश "qed_debug.h"
#समावेश "qed_hsi.h"

बाह्य स्थिर काष्ठा qed_common_ops qed_common_ops_pass;

#घोषणा QED_MAJOR_VERSION		8
#घोषणा QED_MINOR_VERSION		37
#घोषणा QED_REVISION_VERSION		0
#घोषणा QED_ENGINEERING_VERSION		20

#घोषणा QED_VERSION						 \
	((QED_MAJOR_VERSION << 24) | (QED_MINOR_VERSION << 16) | \
	 (QED_REVISION_VERSION << 8) | QED_ENGINEERING_VERSION)

#घोषणा STORM_FW_VERSION				       \
	((FW_MAJOR_VERSION << 24) | (FW_MINOR_VERSION << 16) | \
	 (FW_REVISION_VERSION << 8) | FW_ENGINEERING_VERSION)

#घोषणा MAX_HWFNS_PER_DEVICE    (4)
#घोषणा NAME_SIZE 16
#घोषणा VER_SIZE 16

#घोषणा QED_WFQ_UNIT	100

#घोषणा QED_WID_SIZE            (1024)
#घोषणा QED_MIN_WIDS		(4)
#घोषणा QED_PF_DEMS_SIZE        (4)

/* cau states */
क्रमागत qed_coalescing_mode अणु
	QED_COAL_MODE_DISABLE,
	QED_COAL_MODE_ENABLE
पूर्ण;

क्रमागत qed_nvm_cmd अणु
	QED_PUT_खाता_BEGIN = DRV_MSG_CODE_NVM_PUT_खाता_BEGIN,
	QED_PUT_खाता_DATA = DRV_MSG_CODE_NVM_PUT_खाता_DATA,
	QED_NVM_WRITE_NVRAM = DRV_MSG_CODE_NVM_WRITE_NVRAM,
	QED_GET_MCP_NVM_RESP = 0xFFFFFF00
पूर्ण;

काष्ठा qed_eth_cb_ops;
काष्ठा qed_dev_info;
जोड़ qed_mcp_protocol_stats;
क्रमागत qed_mcp_protocol_type;
क्रमागत qed_mfw_tlv_type;
जोड़ qed_mfw_tlv_data;

/* helpers */
#घोषणा QED_MFW_GET_FIELD(name, field) \
	(((name) & (field ## _MASK)) >> (field ## _SHIFT))

#घोषणा QED_MFW_SET_FIELD(name, field, value)				       \
	करो अणु								       \
		(name)	&= ~(field ## _MASK);	       \
		(name)	|= (((value) << (field ## _SHIFT)) & (field ## _MASK));\
	पूर्ण जबतक (0)

अटल अंतरभूत u32 qed_db_addr(u32 cid, u32 DEMS)
अणु
	u32 db_addr = FIELD_VALUE(DB_LEGACY_ADDR_DEMS, DEMS) |
		      (cid * QED_PF_DEMS_SIZE);

	वापस db_addr;
पूर्ण

अटल अंतरभूत u32 qed_db_addr_vf(u32 cid, u32 DEMS)
अणु
	u32 db_addr = FIELD_VALUE(DB_LEGACY_ADDR_DEMS, DEMS) |
		      FIELD_VALUE(DB_LEGACY_ADDR_ICID, cid);

	वापस db_addr;
पूर्ण

#घोषणा ALIGNED_TYPE_SIZE(type_name, p_hwfn)				     \
	((माप(type_name) + (u32)(1 << (p_hwfn->cdev->cache_shअगरt)) - 1) & \
	 ~((1 << (p_hwfn->cdev->cache_shअगरt)) - 1))

#घोषणा क्रम_each_hwfn(cdev, i)  क्रम (i = 0; i < cdev->num_hwfns; i++)

#घोषणा D_TRINE(val, cond1, cond2, true1, true2, def) \
	(val == (cond1) ? true1 :		      \
	 (val == (cond2) ? true2 : def))

/* क्रमward */
काष्ठा qed_ptt_pool;
काष्ठा qed_spq;
काष्ठा qed_sb_info;
काष्ठा qed_sb_attn_info;
काष्ठा qed_cxt_mngr;
काष्ठा qed_sb_sp_info;
काष्ठा qed_ll2_info;
काष्ठा qed_mcp_info;
काष्ठा qed_llh_info;

काष्ठा qed_rt_data अणु
	u32	*init_val;
	bool	*b_valid;
पूर्ण;

क्रमागत qed_tunn_mode अणु
	QED_MODE_L2GENEVE_TUNN,
	QED_MODE_IPGENEVE_TUNN,
	QED_MODE_L2GRE_TUNN,
	QED_MODE_IPGRE_TUNN,
	QED_MODE_VXLAN_TUNN,
पूर्ण;

क्रमागत qed_tunn_clss अणु
	QED_TUNN_CLSS_MAC_VLAN,
	QED_TUNN_CLSS_MAC_VNI,
	QED_TUNN_CLSS_INNER_MAC_VLAN,
	QED_TUNN_CLSS_INNER_MAC_VNI,
	QED_TUNN_CLSS_MAC_VLAN_DUAL_STAGE,
	MAX_QED_TUNN_CLSS,
पूर्ण;

काष्ठा qed_tunn_update_type अणु
	bool b_update_mode;
	bool b_mode_enabled;
	क्रमागत qed_tunn_clss tun_cls;
पूर्ण;

काष्ठा qed_tunn_update_udp_port अणु
	bool b_update_port;
	u16 port;
पूर्ण;

काष्ठा qed_tunnel_info अणु
	काष्ठा qed_tunn_update_type vxlan;
	काष्ठा qed_tunn_update_type l2_geneve;
	काष्ठा qed_tunn_update_type ip_geneve;
	काष्ठा qed_tunn_update_type l2_gre;
	काष्ठा qed_tunn_update_type ip_gre;

	काष्ठा qed_tunn_update_udp_port vxlan_port;
	काष्ठा qed_tunn_update_udp_port geneve_port;

	bool b_update_rx_cls;
	bool b_update_tx_cls;
पूर्ण;

काष्ठा qed_tunn_start_params अणु
	अचिन्हित दीर्घ	tunn_mode;
	u16		vxlan_udp_port;
	u16		geneve_udp_port;
	u8		update_vxlan_udp_port;
	u8		update_geneve_udp_port;
	u8		tunn_clss_vxlan;
	u8		tunn_clss_l2geneve;
	u8		tunn_clss_ipgeneve;
	u8		tunn_clss_l2gre;
	u8		tunn_clss_ipgre;
पूर्ण;

काष्ठा qed_tunn_update_params अणु
	अचिन्हित दीर्घ	tunn_mode_update_mask;
	अचिन्हित दीर्घ	tunn_mode;
	u16		vxlan_udp_port;
	u16		geneve_udp_port;
	u8		update_rx_pf_clss;
	u8		update_tx_pf_clss;
	u8		update_vxlan_udp_port;
	u8		update_geneve_udp_port;
	u8		tunn_clss_vxlan;
	u8		tunn_clss_l2geneve;
	u8		tunn_clss_ipgeneve;
	u8		tunn_clss_l2gre;
	u8		tunn_clss_ipgre;
पूर्ण;

/* The PCI personality is not quite synonymous to protocol ID:
 * 1. All personalities need CORE connections
 * 2. The Ethernet personality may support also the RoCE/iWARP protocol
 */
क्रमागत qed_pci_personality अणु
	QED_PCI_ETH,
	QED_PCI_FCOE,
	QED_PCI_ISCSI,
	QED_PCI_ETH_ROCE,
	QED_PCI_ETH_IWARP,
	QED_PCI_ETH_RDMA,
	QED_PCI_DEFAULT, /* शेष in shmem */
पूर्ण;

/* All VFs are symmetric, all counters are PF + all VFs */
काष्ठा qed_qm_iids अणु
	u32 cids;
	u32 vf_cids;
	u32 tids;
पूर्ण;

/* HW / FW resources, output of features supported below, most inक्रमmation
 * is received from MFW.
 */
क्रमागत qed_resources अणु
	QED_SB,
	QED_L2_QUEUE,
	QED_VPORT,
	QED_RSS_ENG,
	QED_PQ,
	QED_RL,
	QED_MAC,
	QED_VLAN,
	QED_RDMA_CNQ_RAM,
	QED_ILT,
	QED_LL2_RAM_QUEUE,
	QED_LL2_CTX_QUEUE,
	QED_CMDQS_CQS,
	QED_RDMA_STATS_QUEUE,
	QED_BDQ,
	QED_MAX_RESC,
पूर्ण;

क्रमागत QED_FEATURE अणु
	QED_PF_L2_QUE,
	QED_VF,
	QED_RDMA_CNQ,
	QED_ISCSI_CQ,
	QED_FCOE_CQ,
	QED_VF_L2_QUE,
	QED_MAX_FEATURES,
पूर्ण;

क्रमागत qed_dev_cap अणु
	QED_DEV_CAP_ETH,
	QED_DEV_CAP_FCOE,
	QED_DEV_CAP_ISCSI,
	QED_DEV_CAP_ROCE,
	QED_DEV_CAP_IWARP,
पूर्ण;

क्रमागत qed_wol_support अणु
	QED_WOL_SUPPORT_NONE,
	QED_WOL_SUPPORT_PME,
पूर्ण;

क्रमागत qed_db_rec_exec अणु
	DB_REC_DRY_RUN,
	DB_REC_REAL_DEAL,
	DB_REC_ONCE,
पूर्ण;

काष्ठा qed_hw_info अणु
	/* PCI personality */
	क्रमागत qed_pci_personality	personality;
#घोषणा QED_IS_RDMA_PERSONALITY(dev)					\
	((dev)->hw_info.personality == QED_PCI_ETH_ROCE ||		\
	 (dev)->hw_info.personality == QED_PCI_ETH_IWARP ||		\
	 (dev)->hw_info.personality == QED_PCI_ETH_RDMA)
#घोषणा QED_IS_ROCE_PERSONALITY(dev)					\
	((dev)->hw_info.personality == QED_PCI_ETH_ROCE ||		\
	 (dev)->hw_info.personality == QED_PCI_ETH_RDMA)
#घोषणा QED_IS_IWARP_PERSONALITY(dev)					\
	((dev)->hw_info.personality == QED_PCI_ETH_IWARP ||		\
	 (dev)->hw_info.personality == QED_PCI_ETH_RDMA)
#घोषणा QED_IS_L2_PERSONALITY(dev)					\
	((dev)->hw_info.personality == QED_PCI_ETH ||			\
	 QED_IS_RDMA_PERSONALITY(dev))
#घोषणा QED_IS_FCOE_PERSONALITY(dev)					\
	((dev)->hw_info.personality == QED_PCI_FCOE)
#घोषणा QED_IS_ISCSI_PERSONALITY(dev)					\
	((dev)->hw_info.personality == QED_PCI_ISCSI)

	/* Resource Allocation scheme results */
	u32				resc_start[QED_MAX_RESC];
	u32				resc_num[QED_MAX_RESC];
#घोषणा RESC_START(_p_hwfn, resc)	((_p_hwfn)->hw_info.resc_start[resc])
#घोषणा RESC_NUM(_p_hwfn, resc)		((_p_hwfn)->hw_info.resc_num[resc])
#घोषणा RESC_END(_p_hwfn, resc)		(RESC_START(_p_hwfn, resc) +	\
					 RESC_NUM(_p_hwfn, resc))

	u32				feat_num[QED_MAX_FEATURES];
#घोषणा FEAT_NUM(_p_hwfn, resc)		((_p_hwfn)->hw_info.feat_num[resc])

	/* Amount of traffic classes HW supports */
	u8				num_hw_tc;

	/* Amount of TCs which should be active according to DCBx or upper
	 * layer driver configuration.
	 */
	u8				num_active_tc;

	u8				offload_tc;
	bool				offload_tc_set;

	bool				multi_tc_roce_en;
#घोषणा IS_QED_MULTI_TC_ROCE(p_hwfn)	((p_hwfn)->hw_info.multi_tc_roce_en)

	u32				concrete_fid;
	u16				opaque_fid;
	u16				ovlan;
	u32				part_num[4];

	अचिन्हित अक्षर			hw_mac_addr[ETH_ALEN];
	u64				node_wwn;
	u64				port_wwn;

	u16				num_fcoe_conns;

	काष्ठा qed_igu_info		*p_igu_info;

	u32				hw_mode;
	अचिन्हित दीर्घ			device_capabilities;
	u16				mtu;

	क्रमागत qed_wol_support		b_wol_support;
पूर्ण;

/* maximun size of पढ़ो/ग_लिखो commands (HW limit) */
#घोषणा DMAE_MAX_RW_SIZE        0x2000

काष्ठा qed_dmae_info अणु
	/* Mutex क्रम synchronizing access to functions */
	काष्ठा mutex	mutex;

	u8		channel;

	dma_addr_t	completion_word_phys_addr;

	/* The memory location where the DMAE ग_लिखोs the completion
	 * value when an operation is finished on this context.
	 */
	u32		*p_completion_word;

	dma_addr_t	पूर्णांकermediate_buffer_phys_addr;

	/* An पूर्णांकermediate buffer क्रम DMAE operations that use भव
	 * addresses - data is DMA'd to/from this buffer and then
	 * स_नकल'd to/from the भव address
	 */
	u32		*p_पूर्णांकermediate_buffer;

	dma_addr_t	dmae_cmd_phys_addr;
	काष्ठा dmae_cmd *p_dmae_cmd;
पूर्ण;

काष्ठा qed_wfq_data अणु
	/* when feature is configured क्रम at least 1 vport */
	u32	min_speed;
	bool	configured;
पूर्ण;

काष्ठा qed_qm_info अणु
	काष्ठा init_qm_pq_params	*qm_pq_params;
	काष्ठा init_qm_vport_params	*qm_vport_params;
	काष्ठा init_qm_port_params	*qm_port_params;
	u16				start_pq;
	u8				start_vport;
	u16				 pure_lb_pq;
	u16				first_ofld_pq;
	u16				first_llt_pq;
	u16				pure_ack_pq;
	u16				ooo_pq;
	u16				first_vf_pq;
	u16				first_mcos_pq;
	u16				first_rl_pq;
	u16				num_pqs;
	u16				num_vf_pqs;
	u8				num_vports;
	u8				max_phys_tcs_per_port;
	u8				ooo_tc;
	bool				pf_rl_en;
	bool				pf_wfq_en;
	bool				vport_rl_en;
	bool				vport_wfq_en;
	u8				pf_wfq;
	u32				pf_rl;
	काष्ठा qed_wfq_data		*wfq_data;
	u8 num_pf_rls;
पूर्ण;

#घोषणा QED_OVERFLOW_BIT	1

काष्ठा qed_db_recovery_info अणु
	काष्ठा list_head list;

	/* Lock to protect the करोorbell recovery mechanism list */
	spinlock_t lock;
	bool करोrq_attn;
	u32 db_recovery_counter;
	अचिन्हित दीर्घ overflow;
पूर्ण;

काष्ठा storm_stats अणु
	u32     address;
	u32     len;
पूर्ण;

काष्ठा qed_storm_stats अणु
	काष्ठा storm_stats mstats;
	काष्ठा storm_stats pstats;
	काष्ठा storm_stats tstats;
	काष्ठा storm_stats ustats;
पूर्ण;

काष्ठा qed_fw_data अणु
	काष्ठा fw_ver_info	*fw_ver_info;
	स्थिर u8		*modes_tree_buf;
	जोड़ init_op		*init_ops;
	स्थिर u32		*arr_data;
	स्थिर u32		*fw_overlays;
	u32			fw_overlays_len;
	u32			init_ops_size;
पूर्ण;

क्रमागत qed_mf_mode_bit अणु
	/* Supports PF-classअगरication based on tag */
	QED_MF_OVLAN_CLSS,

	/* Supports PF-classअगरication based on MAC */
	QED_MF_LLH_MAC_CLSS,

	/* Supports PF-classअगरication based on protocol type */
	QED_MF_LLH_PROTO_CLSS,

	/* Requires a शेष PF to be set */
	QED_MF_NEED_DEF_PF,

	/* Allow LL2 to multicast/broadcast */
	QED_MF_LL2_NON_UNICAST,

	/* Allow Cross-PF [& child VFs] Tx-चयनing */
	QED_MF_INTER_PF_SWITCH,

	/* Unअगरied Fabtic Port support enabled */
	QED_MF_UFP_SPECIFIC,

	/* Disable Accelerated Receive Flow Steering (aRFS) */
	QED_MF_DISABLE_ARFS,

	/* Use vlan क्रम steering */
	QED_MF_8021Q_TAGGING,

	/* Use stag क्रम steering */
	QED_MF_8021AD_TAGGING,

	/* Allow DSCP to TC mapping */
	QED_MF_DSCP_TO_TC_MAP,

	/* Do not insert a vlan tag with id 0 */
	QED_MF_DONT_ADD_VLAN0_TAG,
पूर्ण;

क्रमागत qed_ufp_mode अणु
	QED_UFP_MODE_ETS,
	QED_UFP_MODE_VNIC_BW,
	QED_UFP_MODE_UNKNOWN
पूर्ण;

क्रमागत qed_ufp_pri_type अणु
	QED_UFP_PRI_OS,
	QED_UFP_PRI_VNIC,
	QED_UFP_PRI_UNKNOWN
पूर्ण;

काष्ठा qed_ufp_info अणु
	क्रमागत qed_ufp_pri_type pri_type;
	क्रमागत qed_ufp_mode mode;
	u8 tc;
पूर्ण;

क्रमागत BAR_ID अणु
	BAR_ID_0,		/* used क्रम GRC */
	BAR_ID_1		/* Used क्रम करोorbells */
पूर्ण;

काष्ठा qed_nvm_image_info अणु
	u32 num_images;
	काष्ठा bist_nvm_image_att *image_att;
	bool valid;
पूर्ण;

क्रमागत qed_hsi_def_type अणु
	QED_HSI_DEF_MAX_NUM_VFS,
	QED_HSI_DEF_MAX_NUM_L2_QUEUES,
	QED_HSI_DEF_MAX_NUM_PORTS,
	QED_HSI_DEF_MAX_SB_PER_PATH,
	QED_HSI_DEF_MAX_NUM_PFS,
	QED_HSI_DEF_MAX_NUM_VPORTS,
	QED_HSI_DEF_NUM_ETH_RSS_ENGINE,
	QED_HSI_DEF_MAX_QM_TX_QUEUES,
	QED_HSI_DEF_NUM_PXP_ILT_RECORDS,
	QED_HSI_DEF_NUM_RDMA_STATISTIC_COUNTERS,
	QED_HSI_DEF_MAX_QM_GLOBAL_RLS,
	QED_HSI_DEF_MAX_PBF_CMD_LINES,
	QED_HSI_DEF_MAX_BTB_BLOCKS,
	QED_NUM_HSI_DEFS
पूर्ण;

#घोषणा DRV_MODULE_VERSION		      \
	__stringअगरy(QED_MAJOR_VERSION) "."    \
	__stringअगरy(QED_MINOR_VERSION) "."    \
	__stringअगरy(QED_REVISION_VERSION) "." \
	__stringअगरy(QED_ENGINEERING_VERSION)

काष्ठा qed_simd_fp_handler अणु
	व्योम	*token;
	व्योम	(*func)(व्योम *);
पूर्ण;

क्रमागत qed_slowpath_wq_flag अणु
	QED_SLOWPATH_MFW_TLV_REQ,
	QED_SLOWPATH_PERIODIC_DB_REC,
पूर्ण;

काष्ठा qed_hwfn अणु
	काष्ठा qed_dev			*cdev;
	u8				my_id;          /* ID inside the PF */
#घोषणा IS_LEAD_HWFN(edev)              (!((edev)->my_id))
	u8				rel_pf_id;      /* Relative to engine*/
	u8				असल_pf_id;
#घोषणा QED_PATH_ID(_p_hwfn) \
	(QED_IS_K2((_p_hwfn)->cdev) ? 0 : ((_p_hwfn)->असल_pf_id & 1))
	u8				port_id;
	bool				b_active;

	u32				dp_module;
	u8				dp_level;
	अक्षर				name[NAME_SIZE];

	bool				hw_init_करोne;

	u8				num_funcs_on_engine;
	u8 enabled_func_idx;

	/* BAR access */
	व्योम __iomem			*regview;
	व्योम __iomem			*करोorbells;
	u64				db_phys_addr;
	अचिन्हित दीर्घ			db_size;

	/* PTT pool */
	काष्ठा qed_ptt_pool		*p_ptt_pool;

	/* HW info */
	काष्ठा qed_hw_info		hw_info;

	/* rt_array (क्रम init-tool) */
	काष्ठा qed_rt_data		rt_data;

	/* SPQ */
	काष्ठा qed_spq			*p_spq;

	/* EQ */
	काष्ठा qed_eq			*p_eq;

	/* Consolidate Q*/
	काष्ठा qed_consq		*p_consq;

	/* Slow-Path definitions */
	काष्ठा tasklet_काष्ठा		sp_dpc;
	bool				b_sp_dpc_enabled;

	काष्ठा qed_ptt			*p_मुख्य_ptt;
	काष्ठा qed_ptt			*p_dpc_ptt;

	/* PTP will be used only by the leading function.
	 * Usage of all PTP-apis should be synchronized as result.
	 */
	काष्ठा qed_ptt *p_ptp_ptt;

	काष्ठा qed_sb_sp_info		*p_sp_sb;
	काष्ठा qed_sb_attn_info		*p_sb_attn;

	/* Protocol related */
	bool				using_ll2;
	काष्ठा qed_ll2_info		*p_ll2_info;
	काष्ठा qed_ooo_info		*p_ooo_info;
	काष्ठा qed_rdma_info		*p_rdma_info;
	काष्ठा qed_iscsi_info		*p_iscsi_info;
	काष्ठा qed_fcoe_info		*p_fcoe_info;
	काष्ठा qed_pf_params		pf_params;

	bool b_rdma_enabled_in_prs;
	u32 rdma_prs_search_reg;

	काष्ठा qed_cxt_mngr		*p_cxt_mngr;

	/* Flag indicating whether पूर्णांकerrupts are enabled or not*/
	bool				b_पूर्णांक_enabled;
	bool				b_पूर्णांक_requested;

	/* True अगर the driver requests क्रम the link */
	bool				b_drv_link_init;

	काष्ठा qed_vf_iov		*vf_iov_info;
	काष्ठा qed_pf_iov		*pf_iov_info;
	काष्ठा qed_mcp_info		*mcp_info;

	काष्ठा qed_dcbx_info		*p_dcbx_info;

	काष्ठा qed_ufp_info		ufp_info;

	काष्ठा qed_dmae_info		dmae_info;

	/* QM init */
	काष्ठा qed_qm_info		qm_info;
	काष्ठा qed_storm_stats		storm_stats;

	/* Buffer क्रम unzipping firmware data */
	व्योम				*unzip_buf;

	काष्ठा dbg_tools_data		dbg_info;
	व्योम				*dbg_user_info;
	काष्ठा virt_mem_desc		dbg_arrays[MAX_BIN_DBG_BUFFER_TYPE];

	/* PWM region specअगरic data */
	u16				wid_count;
	u32				dpi_size;
	u32				dpi_count;

	/* This is used to calculate the करोorbell address */
	u32 dpi_start_offset;

	/* If one of the following is set then EDPM shouldn't be used */
	u8 dcbx_no_edpm;
	u8 db_bar_no_edpm;

	/* L2-related */
	काष्ठा qed_l2_info *p_l2_info;

	/* Mechanism क्रम recovering from करोorbell drop */
	काष्ठा qed_db_recovery_info db_recovery_info;

	/* Nvm images number and attributes */
	काष्ठा qed_nvm_image_info nvm_info;

	काष्ठा phys_mem_desc *fw_overlay_mem;
	काष्ठा qed_ptt *p_arfs_ptt;

	काष्ठा qed_simd_fp_handler	simd_proto_handler[64];

#अगर_घोषित CONFIG_QED_SRIOV
	काष्ठा workqueue_काष्ठा *iov_wq;
	काष्ठा delayed_work iov_task;
	अचिन्हित दीर्घ iov_task_flags;
#पूर्ण_अगर
	काष्ठा z_stream_s *stream;
	bool slowpath_wq_active;
	काष्ठा workqueue_काष्ठा *slowpath_wq;
	काष्ठा delayed_work slowpath_task;
	अचिन्हित दीर्घ slowpath_task_flags;
	u32 periodic_db_rec_count;
पूर्ण;

काष्ठा pci_params अणु
	पूर्णांक		pm_cap;

	अचिन्हित दीर्घ	mem_start;
	अचिन्हित दीर्घ	mem_end;
	अचिन्हित पूर्णांक	irq;
	u8		pf_num;
पूर्ण;

काष्ठा qed_पूर्णांक_param अणु
	u32	पूर्णांक_mode;
	u8	num_vectors;
	u8	min_msix_cnt; /* क्रम minimal functionality */
पूर्ण;

काष्ठा qed_पूर्णांक_params अणु
	काष्ठा qed_पूर्णांक_param	in;
	काष्ठा qed_पूर्णांक_param	out;
	काष्ठा msix_entry	*msix_table;
	bool			fp_initialized;
	u8			fp_msix_base;
	u8			fp_msix_cnt;
	u8			rdma_msix_base;
	u8			rdma_msix_cnt;
पूर्ण;

काष्ठा qed_dbg_feature अणु
	काष्ठा dentry *dentry;
	u8 *dump_buf;
	u32 buf_size;
	u32 dumped_dwords;
पूर्ण;

काष्ठा qed_dev अणु
	u32				dp_module;
	u8				dp_level;
	अक्षर				name[NAME_SIZE];

	क्रमागत qed_dev_type		type;
	/* Translate type/revision combo पूर्णांकo the proper conditions */
#घोषणा QED_IS_BB(dev)			((dev)->type == QED_DEV_TYPE_BB)
#घोषणा QED_IS_BB_B0(dev)		(QED_IS_BB(dev) && CHIP_REV_IS_B0(dev))
#घोषणा QED_IS_AH(dev)			((dev)->type == QED_DEV_TYPE_AH)
#घोषणा QED_IS_K2(dev)			QED_IS_AH(dev)
#घोषणा QED_IS_E4(dev)			(QED_IS_BB(dev) || QED_IS_AH(dev))
#घोषणा QED_IS_E5(dev)			((dev)->type == QED_DEV_TYPE_E5)

	u16				venकरोr_id;

	u16				device_id;
#घोषणा QED_DEV_ID_MASK			0xff00
#घोषणा QED_DEV_ID_MASK_BB		0x1600
#घोषणा QED_DEV_ID_MASK_AH		0x8000

	u16				chip_num;
#घोषणा CHIP_NUM_MASK			0xffff
#घोषणा CHIP_NUM_SHIFT			16

	u16				chip_rev;
#घोषणा CHIP_REV_MASK			0xf
#घोषणा CHIP_REV_SHIFT			12
#घोषणा CHIP_REV_IS_B0(_cdev)		((_cdev)->chip_rev == 1)

	u16				chip_metal;
#घोषणा CHIP_METAL_MASK			0xff
#घोषणा CHIP_METAL_SHIFT		4

	u16				chip_bond_id;
#घोषणा CHIP_BOND_ID_MASK		0xf
#घोषणा CHIP_BOND_ID_SHIFT		0

	u8				num_engines;
	u8				num_ports;
	u8				num_ports_in_engine;
	u8				num_funcs_in_port;

	u8				path_id;

	अचिन्हित दीर्घ			mf_bits;

	पूर्णांक				pcie_width;
	पूर्णांक				pcie_speed;

	/* Add MF related configuration */
	u8				mcp_rev;
	u8				boot_mode;

	/* WoL related configurations */
	u8 wol_config;
	u8 wol_mac[ETH_ALEN];

	u32				पूर्णांक_mode;
	क्रमागत qed_coalescing_mode	पूर्णांक_coalescing_mode;
	u16				rx_coalesce_usecs;
	u16				tx_coalesce_usecs;

	/* Start Bar offset of first hwfn */
	व्योम __iomem			*regview;
	व्योम __iomem			*करोorbells;
	u64				db_phys_addr;
	अचिन्हित दीर्घ			db_size;

	/* PCI */
	u8				cache_shअगरt;

	/* Init */
	स्थिर u32 *iro_arr;
#घोषणा IRO ((स्थिर काष्ठा iro *)p_hwfn->cdev->iro_arr)

	/* HW functions */
	u8				num_hwfns;
	काष्ठा qed_hwfn			hwfns[MAX_HWFNS_PER_DEVICE];

	/* Engine affinity */
	u8				l2_affin_hपूर्णांक;
	u8				fir_affin;
	u8				iwarp_affin;

	/* SRIOV */
	काष्ठा qed_hw_sriov_info *p_iov_info;
#घोषणा IS_QED_SRIOV(cdev)              (!!(cdev)->p_iov_info)
	काष्ठा qed_tunnel_info		tunnel;
	bool				b_is_vf;
	u32				drv_type;
	काष्ठा qed_eth_stats		*reset_stats;
	काष्ठा qed_fw_data		*fw_data;

	u32				mcp_nvm_resp;

	/* Recovery */
	bool recov_in_prog;

	/* Indicates whether should prevent attentions from being reनिश्चितed */
	bool attn_clr_en;

	/* LLH info */
	u8 ppfid_biपंचांगap;
	काष्ठा qed_llh_info *p_llh_info;

	/* Linux specअगरic here */
	काष्ठा qed_dev_info		common_dev_info;
	काष्ठा  qede_dev		*edev;
	काष्ठा  pci_dev			*pdev;
	u32 flags;
#घोषणा QED_FLAG_STORAGE_STARTED	(BIT(0))
	पूर्णांक				msg_enable;

	काष्ठा pci_params		pci_params;

	काष्ठा qed_पूर्णांक_params		पूर्णांक_params;

	u8				protocol;
#घोषणा IS_QED_ETH_IF(cdev)     ((cdev)->protocol == QED_PROTOCOL_ETH)
#घोषणा IS_QED_FCOE_IF(cdev)    ((cdev)->protocol == QED_PROTOCOL_FCOE)

	/* Callbacks to protocol driver */
	जोड़ अणु
		काष्ठा qed_common_cb_ops	*common;
		काष्ठा qed_eth_cb_ops		*eth;
		काष्ठा qed_fcoe_cb_ops		*fcoe;
		काष्ठा qed_iscsi_cb_ops		*iscsi;
	पूर्ण protocol_ops;
	व्योम				*ops_cookie;

#अगर_घोषित CONFIG_QED_LL2
	काष्ठा qed_cb_ll2_info		*ll2;
	u8				ll2_mac_address[ETH_ALEN];
#पूर्ण_अगर
	काष्ठा qed_dbg_feature dbg_features[DBG_FEATURE_NUM];
	u8 engine_क्रम_debug;
	bool disable_ilt_dump;
	bool				dbg_bin_dump;

	DECLARE_HASHTABLE(connections, 10);
	स्थिर काष्ठा firmware		*firmware;

	bool prपूर्णांक_dbg_data;

	u32 rdma_max_sge;
	u32 rdma_max_अंतरभूत;
	u32 rdma_max_srq_sge;
	u16 tunn_feature_mask;

	bool				iwarp_cmt;
पूर्ण;

u32 qed_get_hsi_def_val(काष्ठा qed_dev *cdev, क्रमागत qed_hsi_def_type type);

#घोषणा NUM_OF_VFS(dev)	\
	qed_get_hsi_def_val(dev, QED_HSI_DEF_MAX_NUM_VFS)
#घोषणा NUM_OF_L2_QUEUES(dev) \
	qed_get_hsi_def_val(dev, QED_HSI_DEF_MAX_NUM_L2_QUEUES)
#घोषणा NUM_OF_PORTS(dev) \
	qed_get_hsi_def_val(dev, QED_HSI_DEF_MAX_NUM_PORTS)
#घोषणा NUM_OF_SBS(dev)	\
	qed_get_hsi_def_val(dev, QED_HSI_DEF_MAX_SB_PER_PATH)
#घोषणा NUM_OF_ENG_PFS(dev) \
	qed_get_hsi_def_val(dev, QED_HSI_DEF_MAX_NUM_PFS)
#घोषणा NUM_OF_VPORTS(dev) \
	qed_get_hsi_def_val(dev, QED_HSI_DEF_MAX_NUM_VPORTS)
#घोषणा NUM_OF_RSS_ENGINES(dev)	\
	qed_get_hsi_def_val(dev, QED_HSI_DEF_NUM_ETH_RSS_ENGINE)
#घोषणा NUM_OF_QM_TX_QUEUES(dev) \
	qed_get_hsi_def_val(dev, QED_HSI_DEF_MAX_QM_TX_QUEUES)
#घोषणा NUM_OF_PXP_ILT_RECORDS(dev) \
	qed_get_hsi_def_val(dev, QED_HSI_DEF_NUM_PXP_ILT_RECORDS)
#घोषणा NUM_OF_RDMA_STATISTIC_COUNTERS(dev) \
	qed_get_hsi_def_val(dev, QED_HSI_DEF_NUM_RDMA_STATISTIC_COUNTERS)
#घोषणा NUM_OF_QM_GLOBAL_RLS(dev) \
	qed_get_hsi_def_val(dev, QED_HSI_DEF_MAX_QM_GLOBAL_RLS)
#घोषणा NUM_OF_PBF_CMD_LINES(dev) \
	qed_get_hsi_def_val(dev, QED_HSI_DEF_MAX_PBF_CMD_LINES)
#घोषणा NUM_OF_BTB_BLOCKS(dev) \
	qed_get_hsi_def_val(dev, QED_HSI_DEF_MAX_BTB_BLOCKS)


/**
 * @brief qed_concrete_to_sw_fid - get the sw function id from
 *        the concrete value.
 *
 * @param concrete_fid
 *
 * @वापस अंतरभूत u8
 */
अटल अंतरभूत u8 qed_concrete_to_sw_fid(काष्ठा qed_dev *cdev,
					u32 concrete_fid)
अणु
	u8 vfid = GET_FIELD(concrete_fid, PXP_CONCRETE_FID_VFID);
	u8 pfid = GET_FIELD(concrete_fid, PXP_CONCRETE_FID_PFID);
	u8 vf_valid = GET_FIELD(concrete_fid,
				PXP_CONCRETE_FID_VFVALID);
	u8 sw_fid;

	अगर (vf_valid)
		sw_fid = vfid + MAX_NUM_PFS;
	अन्यथा
		sw_fid = pfid;

	वापस sw_fid;
पूर्ण

#घोषणा PKT_LB_TC	9
#घोषणा MAX_NUM_VOQS_E4	20

पूर्णांक qed_configure_vport_wfq(काष्ठा qed_dev *cdev, u16 vp_id, u32 rate);
व्योम qed_configure_vp_wfq_on_link_change(काष्ठा qed_dev *cdev,
					 काष्ठा qed_ptt *p_ptt,
					 u32 min_pf_rate);

व्योम qed_clean_wfq_db(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);
पूर्णांक qed_device_num_engines(काष्ठा qed_dev *cdev);
व्योम qed_set_fw_mac_addr(__le16 *fw_msb,
			 __le16 *fw_mid, __le16 *fw_lsb, u8 *mac);

#घोषणा QED_LEADING_HWFN(dev)   (&dev->hwfns[0])
#घोषणा QED_IS_CMT(dev)		((dev)->num_hwfns > 1)
/* Macros क्रम getting the engine-affinitized hwfn (FIR: fcoe,iscsi,roce) */
#घोषणा QED_FIR_AFFIN_HWFN(dev)		(&(dev)->hwfns[dev->fir_affin])
#घोषणा QED_IWARP_AFFIN_HWFN(dev)       (&(dev)->hwfns[dev->iwarp_affin])
#घोषणा QED_AFFIN_HWFN(dev)				   \
	(QED_IS_IWARP_PERSONALITY(QED_LEADING_HWFN(dev)) ? \
	 QED_IWARP_AFFIN_HWFN(dev) : QED_FIR_AFFIN_HWFN(dev))
#घोषणा QED_AFFIN_HWFN_IDX(dev) (IS_LEAD_HWFN(QED_AFFIN_HWFN(dev)) ? 0 : 1)

/* Flags क्रम indication of required queues */
#घोषणा PQ_FLAGS_RLS    (BIT(0))
#घोषणा PQ_FLAGS_MCOS   (BIT(1))
#घोषणा PQ_FLAGS_LB     (BIT(2))
#घोषणा PQ_FLAGS_OOO    (BIT(3))
#घोषणा PQ_FLAGS_ACK    (BIT(4))
#घोषणा PQ_FLAGS_OFLD   (BIT(5))
#घोषणा PQ_FLAGS_VFS    (BIT(6))
#घोषणा PQ_FLAGS_LLT    (BIT(7))
#घोषणा PQ_FLAGS_MTC    (BIT(8))

/* physical queue index क्रम cm context पूर्णांकialization */
u16 qed_get_cm_pq_idx(काष्ठा qed_hwfn *p_hwfn, u32 pq_flags);
u16 qed_get_cm_pq_idx_mcos(काष्ठा qed_hwfn *p_hwfn, u8 tc);
u16 qed_get_cm_pq_idx_vf(काष्ठा qed_hwfn *p_hwfn, u16 vf);
u16 qed_get_cm_pq_idx_ofld_mtc(काष्ठा qed_hwfn *p_hwfn, u8 tc);
u16 qed_get_cm_pq_idx_llt_mtc(काष्ठा qed_hwfn *p_hwfn, u8 tc);

/* करोorbell recovery mechanism */
व्योम qed_db_recovery_dp(काष्ठा qed_hwfn *p_hwfn);
व्योम qed_db_recovery_execute(काष्ठा qed_hwfn *p_hwfn);
bool qed_edpm_enabled(काष्ठा qed_hwfn *p_hwfn);

/* Other Linux specअगरic common definitions */
#घोषणा DP_NAME(cdev) ((cdev)->name)

#घोषणा REG_ADDR(cdev, offset)          (व्योम __iomem *)((u8 __iomem *)\
						(cdev->regview) + \
							 (offset))

#घोषणा REG_RD(cdev, offset)            पढ़ोl(REG_ADDR(cdev, offset))
#घोषणा REG_WR(cdev, offset, val)       ग_लिखोl((u32)val, REG_ADDR(cdev, offset))
#घोषणा REG_WR16(cdev, offset, val)     ग_लिखोw((u16)val, REG_ADDR(cdev, offset))

#घोषणा DOORBELL(cdev, db_addr, val)			 \
	ग_लिखोl((u32)val, (व्योम __iomem *)((u8 __iomem *)\
					  (cdev->करोorbells) + (db_addr)))

#घोषणा MFW_PORT(_p_hwfn)       ((_p_hwfn)->असल_pf_id %			  \
				  qed_device_num_ports((_p_hwfn)->cdev))
पूर्णांक qed_device_num_ports(काष्ठा qed_dev *cdev);

/* Prototypes */
पूर्णांक qed_fill_dev_info(काष्ठा qed_dev *cdev,
		      काष्ठा qed_dev_info *dev_info);
व्योम qed_link_update(काष्ठा qed_hwfn *hwfn, काष्ठा qed_ptt *ptt);
व्योम qed_bw_update(काष्ठा qed_hwfn *hwfn, काष्ठा qed_ptt *ptt);
u32 qed_unzip_data(काष्ठा qed_hwfn *p_hwfn,
		   u32 input_len, u8 *input_buf,
		   u32 max_size, u8 *unzip_buf);
पूर्णांक qed_recovery_process(काष्ठा qed_dev *cdev);
व्योम qed_schedule_recovery_handler(काष्ठा qed_hwfn *p_hwfn);
व्योम qed_hw_error_occurred(काष्ठा qed_hwfn *p_hwfn,
			   क्रमागत qed_hw_err_type err_type);
व्योम qed_get_protocol_stats(काष्ठा qed_dev *cdev,
			    क्रमागत qed_mcp_protocol_type type,
			    जोड़ qed_mcp_protocol_stats *stats);
पूर्णांक qed_slowpath_irq_req(काष्ठा qed_hwfn *hwfn);
व्योम qed_slowpath_irq_sync(काष्ठा qed_hwfn *p_hwfn);
पूर्णांक qed_mfw_tlv_req(काष्ठा qed_hwfn *hwfn);

पूर्णांक qed_mfw_fill_tlv_data(काष्ठा qed_hwfn *hwfn,
			  क्रमागत qed_mfw_tlv_type type,
			  जोड़ qed_mfw_tlv_data *tlv_data);

व्योम qed_hw_info_set_offload_tc(काष्ठा qed_hw_info *p_info, u8 tc);

व्योम qed_periodic_db_rec_start(काष्ठा qed_hwfn *p_hwfn);
#पूर्ण_अगर /* _QED_H */
