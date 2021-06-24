<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  Marvell OcteonTx2 RVU Admin Function driver
 *
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित MBOX_H
#घोषणा MBOX_H

#समावेश <linux/etherdevice.h>
#समावेश <linux/sizes.h>

#समावेश "rvu_struct.h"
#समावेश "common.h"

#घोषणा MBOX_SIZE		SZ_64K

/* AF/PF: PF initiated, PF/VF VF initiated */
#घोषणा MBOX_DOWN_RX_START	0
#घोषणा MBOX_DOWN_RX_SIZE	(46 * SZ_1K)
#घोषणा MBOX_DOWN_TX_START	(MBOX_DOWN_RX_START + MBOX_DOWN_RX_SIZE)
#घोषणा MBOX_DOWN_TX_SIZE	(16 * SZ_1K)
/* AF/PF: AF initiated, PF/VF PF initiated */
#घोषणा MBOX_UP_RX_START	(MBOX_DOWN_TX_START + MBOX_DOWN_TX_SIZE)
#घोषणा MBOX_UP_RX_SIZE		SZ_1K
#घोषणा MBOX_UP_TX_START	(MBOX_UP_RX_START + MBOX_UP_RX_SIZE)
#घोषणा MBOX_UP_TX_SIZE		SZ_1K

#अगर MBOX_UP_TX_SIZE + MBOX_UP_TX_START != MBOX_SIZE
# error "incorrect mailbox area sizes"
#पूर्ण_अगर

#घोषणा INTR_MASK(pfvfs) ((pfvfs < 64) ? (BIT_ULL(pfvfs) - 1) : (~0ull))

#घोषणा MBOX_RSP_TIMEOUT	3000 /* Time(ms) to रुको क्रम mbox response */

#घोषणा MBOX_MSG_ALIGN		16  /* Align mbox msg start to 16bytes */

/* Mailbox directions */
#घोषणा MBOX_सूची_AFPF		0  /* AF replies to PF */
#घोषणा MBOX_सूची_PFAF		1  /* PF sends messages to AF */
#घोषणा MBOX_सूची_PFVF		2  /* PF replies to VF */
#घोषणा MBOX_सूची_VFPF		3  /* VF sends messages to PF */
#घोषणा MBOX_सूची_AFPF_UP	4  /* AF sends messages to PF */
#घोषणा MBOX_सूची_PFAF_UP	5  /* PF replies to AF */
#घोषणा MBOX_सूची_PFVF_UP	6  /* PF sends messages to VF */
#घोषणा MBOX_सूची_VFPF_UP	7  /* VF replies to PF */

काष्ठा otx2_mbox_dev अणु
	व्योम	    *mbase;   /* This dev's mbox region */
	व्योम	    *hwbase;
	spinlock_t  mbox_lock;
	u16         msg_size; /* Total msg size to be sent */
	u16         rsp_size; /* Total rsp size to be sure the reply is ok */
	u16         num_msgs; /* No of msgs sent or रुकोing क्रम response */
	u16         msgs_acked; /* No of msgs क्रम which response is received */
पूर्ण;

काष्ठा otx2_mbox अणु
	काष्ठा pci_dev *pdev;
	व्योम   *hwbase;  /* Mbox region advertised by HW */
	व्योम   *reg_base;/* CSR base क्रम this dev */
	u64    trigger;  /* Trigger mbox notअगरication */
	u16    tr_shअगरt; /* Mbox trigger shअगरt */
	u64    rx_start; /* Offset of Rx region in mbox memory */
	u64    tx_start; /* Offset of Tx region in mbox memory */
	u16    rx_size;  /* Size of Rx region */
	u16    tx_size;  /* Size of Tx region */
	u16    ndevs;    /* The number of peers */
	काष्ठा otx2_mbox_dev *dev;
पूर्ण;

/* Header which precedes all mbox messages */
काष्ठा mbox_hdr अणु
	u64 msg_size;	/* Total msgs size embedded */
	u16  num_msgs;   /* No of msgs embedded */
पूर्ण;

/* Header which precedes every msg and is also part of it */
काष्ठा mbox_msghdr अणु
	u16 pcअगरunc;     /* Who's sending this msg */
	u16 id;          /* Mbox message ID */
#घोषणा OTX2_MBOX_REQ_SIG (0xdead)
#घोषणा OTX2_MBOX_RSP_SIG (0xbeef)
	u16 sig;         /* Signature, क्रम validating corrupted msgs */
#घोषणा OTX2_MBOX_VERSION (0x0007)
	u16 ver;         /* Version of msg's काष्ठाure क्रम this ID */
	u16 next_msgoff; /* Offset of next msg within mailbox region */
	पूर्णांक rc;          /* Msg process'ed response code */
पूर्ण;

व्योम otx2_mbox_reset(काष्ठा otx2_mbox *mbox, पूर्णांक devid);
व्योम __otx2_mbox_reset(काष्ठा otx2_mbox *mbox, पूर्णांक devid);
व्योम otx2_mbox_destroy(काष्ठा otx2_mbox *mbox);
पूर्णांक otx2_mbox_init(काष्ठा otx2_mbox *mbox, व्योम __क्रमce *hwbase,
		   काष्ठा pci_dev *pdev, व्योम __क्रमce *reg_base,
		   पूर्णांक direction, पूर्णांक ndevs);
पूर्णांक otx2_mbox_regions_init(काष्ठा otx2_mbox *mbox, व्योम __क्रमce **hwbase,
			   काष्ठा pci_dev *pdev, व्योम __क्रमce *reg_base,
			   पूर्णांक direction, पूर्णांक ndevs);
व्योम otx2_mbox_msg_send(काष्ठा otx2_mbox *mbox, पूर्णांक devid);
पूर्णांक otx2_mbox_रुको_क्रम_rsp(काष्ठा otx2_mbox *mbox, पूर्णांक devid);
पूर्णांक otx2_mbox_busy_poll_क्रम_rsp(काष्ठा otx2_mbox *mbox, पूर्णांक devid);
काष्ठा mbox_msghdr *otx2_mbox_alloc_msg_rsp(काष्ठा otx2_mbox *mbox, पूर्णांक devid,
					    पूर्णांक size, पूर्णांक size_rsp);
काष्ठा mbox_msghdr *otx2_mbox_get_rsp(काष्ठा otx2_mbox *mbox, पूर्णांक devid,
				      काष्ठा mbox_msghdr *msg);
पूर्णांक otx2_mbox_check_rsp_msgs(काष्ठा otx2_mbox *mbox, पूर्णांक devid);
पूर्णांक otx2_reply_invalid_msg(काष्ठा otx2_mbox *mbox, पूर्णांक devid,
			   u16 pcअगरunc, u16 id);
bool otx2_mbox_nonempty(काष्ठा otx2_mbox *mbox, पूर्णांक devid);
स्थिर अक्षर *otx2_mbox_id2name(u16 id);
अटल अंतरभूत काष्ठा mbox_msghdr *otx2_mbox_alloc_msg(काष्ठा otx2_mbox *mbox,
						      पूर्णांक devid, पूर्णांक size)
अणु
	वापस otx2_mbox_alloc_msg_rsp(mbox, devid, size, 0);
पूर्ण

/* Mailbox message types */
#घोषणा MBOX_MSG_MASK				0xFFFF
#घोषणा MBOX_MSG_INVALID			0xFFFE
#घोषणा MBOX_MSG_MAX				0xFFFF

#घोषणा MBOX_MESSAGES							\
/* Generic mbox IDs (range 0x000 - 0x1FF) */				\
M(READY,		0x001, पढ़ोy, msg_req, पढ़ोy_msg_rsp)		\
M(ATTACH_RESOURCES,	0x002, attach_resources, rsrc_attach, msg_rsp)	\
M(DETACH_RESOURCES,	0x003, detach_resources, rsrc_detach, msg_rsp)	\
M(MSIX_OFFSET,		0x005, msix_offset, msg_req, msix_offset_rsp)	\
M(VF_FLR,		0x006, vf_flr, msg_req, msg_rsp)		\
M(PTP_OP,		0x007, ptp_op, ptp_req, ptp_rsp)		\
M(GET_HW_CAP,		0x008, get_hw_cap, msg_req, get_hw_cap_rsp)	\
/* CGX mbox IDs (range 0x200 - 0x3FF) */				\
M(CGX_START_RXTX,	0x200, cgx_start_rxtx, msg_req, msg_rsp)	\
M(CGX_STOP_RXTX,	0x201, cgx_stop_rxtx, msg_req, msg_rsp)		\
M(CGX_STATS,		0x202, cgx_stats, msg_req, cgx_stats_rsp)	\
M(CGX_MAC_ADDR_SET,	0x203, cgx_mac_addr_set, cgx_mac_addr_set_or_get,    \
				cgx_mac_addr_set_or_get)		\
M(CGX_MAC_ADDR_GET,	0x204, cgx_mac_addr_get, cgx_mac_addr_set_or_get,    \
				cgx_mac_addr_set_or_get)		\
M(CGX_PROMISC_ENABLE,	0x205, cgx_promisc_enable, msg_req, msg_rsp)	\
M(CGX_PROMISC_DISABLE,	0x206, cgx_promisc_disable, msg_req, msg_rsp)	\
M(CGX_START_LINKEVENTS, 0x207, cgx_start_linkevents, msg_req, msg_rsp)	\
M(CGX_STOP_LINKEVENTS,	0x208, cgx_stop_linkevents, msg_req, msg_rsp)	\
M(CGX_GET_LINKINFO,	0x209, cgx_get_linkinfo, msg_req, cgx_link_info_msg) \
M(CGX_INTLBK_ENABLE,	0x20A, cgx_पूर्णांकlbk_enable, msg_req, msg_rsp)	\
M(CGX_INTLBK_DISABLE,	0x20B, cgx_पूर्णांकlbk_disable, msg_req, msg_rsp)	\
M(CGX_PTP_RX_ENABLE,	0x20C, cgx_ptp_rx_enable, msg_req, msg_rsp)	\
M(CGX_PTP_RX_DISABLE,	0x20D, cgx_ptp_rx_disable, msg_req, msg_rsp)	\
M(CGX_CFG_PAUSE_FRM,	0x20E, cgx_cfg_छोड़ो_frm, cgx_छोड़ो_frm_cfg,	\
			       cgx_छोड़ो_frm_cfg)			\
M(CGX_FEC_SET,		0x210, cgx_set_fec_param, fec_mode, fec_mode)   \
M(CGX_FEC_STATS,	0x211, cgx_fec_stats, msg_req, cgx_fec_stats_rsp) \
M(CGX_GET_PHY_FEC_STATS, 0x212, cgx_get_phy_fec_stats, msg_req, msg_rsp) \
M(CGX_FW_DATA_GET,	0x213, cgx_get_aux_link_info, msg_req, cgx_fw_data) \
M(CGX_SET_LINK_MODE,	0x214, cgx_set_link_mode, cgx_set_link_mode_req,\
			       cgx_set_link_mode_rsp)	\
M(CGX_FEATURES_GET,	0x215, cgx_features_get, msg_req,		\
			       cgx_features_info_msg)			\
M(RPM_STATS,		0x216, rpm_stats, msg_req, rpm_stats_rsp)	\
 /* NPA mbox IDs (range 0x400 - 0x5FF) */				\
/* NPA mbox IDs (range 0x400 - 0x5FF) */				\
M(NPA_LF_ALLOC,		0x400, npa_lf_alloc,				\
				npa_lf_alloc_req, npa_lf_alloc_rsp)	\
M(NPA_LF_FREE,		0x401, npa_lf_मुक्त, msg_req, msg_rsp)		\
M(NPA_AQ_ENQ,		0x402, npa_aq_enq, npa_aq_enq_req, npa_aq_enq_rsp)   \
M(NPA_HWCTX_DISABLE,	0x403, npa_hwctx_disable, hwctx_disable_req, msg_rsp)\
/* SSO/SSOW mbox IDs (range 0x600 - 0x7FF) */				\
/* TIM mbox IDs (range 0x800 - 0x9FF) */				\
/* CPT mbox IDs (range 0xA00 - 0xBFF) */				\
M(CPT_LF_ALLOC,		0xA00, cpt_lf_alloc, cpt_lf_alloc_req_msg,	\
			       msg_rsp)					\
M(CPT_LF_FREE,		0xA01, cpt_lf_मुक्त, msg_req, msg_rsp)		\
M(CPT_RD_WR_REGISTER,	0xA02, cpt_rd_wr_रेजिस्टर,  cpt_rd_wr_reg_msg,	\
			       cpt_rd_wr_reg_msg)			\
M(CPT_STATS,            0xA05, cpt_sts, cpt_sts_req, cpt_sts_rsp)	\
M(CPT_RXC_TIME_CFG,     0xA06, cpt_rxc_समय_cfg, cpt_rxc_समय_cfg_req,  \
			       msg_rsp)                                 \
/* NPC mbox IDs (range 0x6000 - 0x7FFF) */				\
M(NPC_MCAM_ALLOC_ENTRY,	0x6000, npc_mcam_alloc_entry, npc_mcam_alloc_entry_req,\
				npc_mcam_alloc_entry_rsp)		\
M(NPC_MCAM_FREE_ENTRY,	0x6001, npc_mcam_मुक्त_entry,			\
				 npc_mcam_मुक्त_entry_req, msg_rsp)	\
M(NPC_MCAM_WRITE_ENTRY,	0x6002, npc_mcam_ग_लिखो_entry,			\
				 npc_mcam_ग_लिखो_entry_req, msg_rsp)	\
M(NPC_MCAM_ENA_ENTRY,   0x6003, npc_mcam_ena_entry,			\
				 npc_mcam_ena_dis_entry_req, msg_rsp)	\
M(NPC_MCAM_DIS_ENTRY,   0x6004, npc_mcam_dis_entry,			\
				 npc_mcam_ena_dis_entry_req, msg_rsp)	\
M(NPC_MCAM_SHIFT_ENTRY, 0x6005, npc_mcam_shअगरt_entry, npc_mcam_shअगरt_entry_req,\
				npc_mcam_shअगरt_entry_rsp)		\
M(NPC_MCAM_ALLOC_COUNTER, 0x6006, npc_mcam_alloc_counter,		\
					npc_mcam_alloc_counter_req,	\
					npc_mcam_alloc_counter_rsp)	\
M(NPC_MCAM_FREE_COUNTER,  0x6007, npc_mcam_मुक्त_counter,		\
				    npc_mcam_oper_counter_req, msg_rsp)	\
M(NPC_MCAM_UNMAP_COUNTER, 0x6008, npc_mcam_unmap_counter,		\
				   npc_mcam_unmap_counter_req, msg_rsp)	\
M(NPC_MCAM_CLEAR_COUNTER, 0x6009, npc_mcam_clear_counter,		\
				   npc_mcam_oper_counter_req, msg_rsp)	\
M(NPC_MCAM_COUNTER_STATS, 0x600a, npc_mcam_counter_stats,		\
				   npc_mcam_oper_counter_req,		\
				   npc_mcam_oper_counter_rsp)		\
M(NPC_MCAM_ALLOC_AND_WRITE_ENTRY, 0x600b, npc_mcam_alloc_and_ग_लिखो_entry,      \
					  npc_mcam_alloc_and_ग_लिखो_entry_req,  \
					  npc_mcam_alloc_and_ग_लिखो_entry_rsp)  \
M(NPC_GET_KEX_CFG,	  0x600c, npc_get_kex_cfg,			\
				   msg_req, npc_get_kex_cfg_rsp)	\
M(NPC_INSTALL_FLOW,	  0x600d, npc_install_flow,			       \
				  npc_install_flow_req, npc_install_flow_rsp)  \
M(NPC_DELETE_FLOW,	  0x600e, npc_delete_flow,			\
				  npc_delete_flow_req, msg_rsp)		\
M(NPC_MCAM_READ_ENTRY,	  0x600f, npc_mcam_पढ़ो_entry,			\
				  npc_mcam_पढ़ो_entry_req,		\
				  npc_mcam_पढ़ो_entry_rsp)		\
M(NPC_MCAM_READ_BASE_RULE, 0x6011, npc_पढ़ो_base_steer_rule,            \
				   msg_req, npc_mcam_पढ़ो_base_rule_rsp)  \
M(NPC_MCAM_GET_STATS, 0x6012, npc_mcam_entry_stats,                     \
				   npc_mcam_get_stats_req,              \
				   npc_mcam_get_stats_rsp)              \
/* NIX mbox IDs (range 0x8000 - 0xFFFF) */				\
M(NIX_LF_ALLOC,		0x8000, nix_lf_alloc,				\
				 nix_lf_alloc_req, nix_lf_alloc_rsp)	\
M(NIX_LF_FREE,		0x8001, nix_lf_मुक्त, nix_lf_मुक्त_req, msg_rsp)	\
M(NIX_AQ_ENQ,		0x8002, nix_aq_enq, nix_aq_enq_req, nix_aq_enq_rsp)  \
M(NIX_HWCTX_DISABLE,	0x8003, nix_hwctx_disable,			\
				 hwctx_disable_req, msg_rsp)		\
M(NIX_TXSCH_ALLOC,	0x8004, nix_txsch_alloc,			\
				 nix_txsch_alloc_req, nix_txsch_alloc_rsp)   \
M(NIX_TXSCH_FREE,	0x8005, nix_txsch_मुक्त, nix_txsch_मुक्त_req, msg_rsp) \
M(NIX_TXSCHQ_CFG,	0x8006, nix_txschq_cfg, nix_txschq_config, msg_rsp)  \
M(NIX_STATS_RST,	0x8007, nix_stats_rst, msg_req, msg_rsp)	\
M(NIX_VTAG_CFG,		0x8008, nix_vtag_cfg, nix_vtag_config,		\
				 nix_vtag_config_rsp)			\
M(NIX_RSS_FLOWKEY_CFG,  0x8009, nix_rss_flowkey_cfg,			\
				 nix_rss_flowkey_cfg,			\
				 nix_rss_flowkey_cfg_rsp)		\
M(NIX_SET_MAC_ADDR,	0x800a, nix_set_mac_addr, nix_set_mac_addr, msg_rsp) \
M(NIX_SET_RX_MODE,	0x800b, nix_set_rx_mode, nix_rx_mode, msg_rsp)	\
M(NIX_SET_HW_FRS,	0x800c, nix_set_hw_frs, nix_frs_cfg, msg_rsp)	\
M(NIX_LF_START_RX,	0x800d, nix_lf_start_rx, msg_req, msg_rsp)	\
M(NIX_LF_STOP_RX,	0x800e, nix_lf_stop_rx, msg_req, msg_rsp)	\
M(NIX_MARK_FORMAT_CFG,	0x800f, nix_mark_क्रमmat_cfg,			\
				 nix_mark_क्रमmat_cfg,			\
				 nix_mark_क्रमmat_cfg_rsp)		\
M(NIX_SET_RX_CFG,	0x8010, nix_set_rx_cfg, nix_rx_cfg, msg_rsp)	\
M(NIX_LSO_FORMAT_CFG,	0x8011, nix_lso_क्रमmat_cfg,			\
				 nix_lso_क्रमmat_cfg,			\
				 nix_lso_क्रमmat_cfg_rsp)		\
M(NIX_LF_PTP_TX_ENABLE, 0x8013, nix_lf_ptp_tx_enable, msg_req, msg_rsp)	\
M(NIX_LF_PTP_TX_DISABLE, 0x8014, nix_lf_ptp_tx_disable, msg_req, msg_rsp) \
M(NIX_BP_ENABLE,	0x8016, nix_bp_enable, nix_bp_cfg_req,	\
				nix_bp_cfg_rsp)	\
M(NIX_BP_DISABLE,	0x8017, nix_bp_disable, nix_bp_cfg_req, msg_rsp) \
M(NIX_GET_MAC_ADDR, 0x8018, nix_get_mac_addr, msg_req, nix_get_mac_addr_rsp) \
M(NIX_CN10K_AQ_ENQ,	0x8019, nix_cn10k_aq_enq, nix_cn10k_aq_enq_req, \
				nix_cn10k_aq_enq_rsp)			\
M(NIX_GET_HW_INFO,	0x801a, nix_get_hw_info, msg_req, nix_hw_info)

/* Messages initiated by AF (range 0xC00 - 0xDFF) */
#घोषणा MBOX_UP_CGX_MESSAGES						\
M(CGX_LINK_EVENT,	0xC00, cgx_link_event, cgx_link_info_msg, msg_rsp)

क्रमागत अणु
#घोषणा M(_name, _id, _1, _2, _3) MBOX_MSG_ ## _name = _id,
MBOX_MESSAGES
MBOX_UP_CGX_MESSAGES
#अघोषित M
पूर्ण;

/* Mailbox message क्रमmats */

#घोषणा RVU_DEFAULT_PF_FUNC     0xFFFF

/* Generic request msg used क्रम those mbox messages which
 * करोn't send any data in the request.
 */
काष्ठा msg_req अणु
	काष्ठा mbox_msghdr hdr;
पूर्ण;

/* Generic response msg used an ack or response क्रम those mbox
 * messages which करोn't have a specअगरic rsp msg क्रमmat.
 */
काष्ठा msg_rsp अणु
	काष्ठा mbox_msghdr hdr;
पूर्ण;

/* RVU mailbox error codes
 * Range 256 - 300.
 */
क्रमागत rvu_af_status अणु
	RVU_INVALID_VF_ID           = -256,
पूर्ण;

काष्ठा पढ़ोy_msg_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u16    sclk_freq;	/* SCLK frequency (in MHz) */
	u16    rclk_freq;	/* RCLK frequency (in MHz) */
पूर्ण;

/* Structure क्रम requesting resource provisioning.
 * 'modify' flag to be used when either requesting more
 * or to detach partial of a certain resource type.
 * Rest of the fields specअगरy how many of what type to
 * be attached.
 * To request LFs from two blocks of same type this mailbox
 * can be sent twice as below:
 *      काष्ठा rsrc_attach *attach;
 *       .. Allocate memory क्रम message ..
 *       attach->cptlfs = 3; <3 LFs from CPT0>
 *       .. Send message ..
 *       .. Allocate memory क्रम message ..
 *       attach->modअगरy = 1;
 *       attach->cpt_blkaddr = BLKADDR_CPT1;
 *       attach->cptlfs = 2; <2 LFs from CPT1>
 *       .. Send message ..
 */
काष्ठा rsrc_attach अणु
	काष्ठा mbox_msghdr hdr;
	u8   modअगरy:1;
	u8   npalf:1;
	u8   nixlf:1;
	u16  sso;
	u16  ssow;
	u16  timlfs;
	u16  cptlfs;
	पूर्णांक  cpt_blkaddr; /* BLKADDR_CPT0/BLKADDR_CPT1 or 0 क्रम BLKADDR_CPT0 */
पूर्ण;

/* Structure क्रम relinquishing resources.
 * 'partial' flag to be used when relinquishing all resources
 * but only of a certain type. If not set, all resources of all
 * types provisioned to the RVU function will be detached.
 */
काष्ठा rsrc_detach अणु
	काष्ठा mbox_msghdr hdr;
	u8 partial:1;
	u8 npalf:1;
	u8 nixlf:1;
	u8 sso:1;
	u8 ssow:1;
	u8 timlfs:1;
	u8 cptlfs:1;
पूर्ण;

#घोषणा MSIX_VECTOR_INVALID	0xFFFF
#घोषणा MAX_RVU_BLKLF_CNT	256

काष्ठा msix_offset_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u16  npa_msixoff;
	u16  nix_msixoff;
	u8   sso;
	u8   ssow;
	u8   timlfs;
	u8   cptlfs;
	u16  sso_msixoff[MAX_RVU_BLKLF_CNT];
	u16  ssow_msixoff[MAX_RVU_BLKLF_CNT];
	u16  timlf_msixoff[MAX_RVU_BLKLF_CNT];
	u16  cptlf_msixoff[MAX_RVU_BLKLF_CNT];
	u8   cpt1_lfs;
	u16  cpt1_lf_msixoff[MAX_RVU_BLKLF_CNT];
पूर्ण;

काष्ठा get_hw_cap_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u8 nix_fixed_txschq_mapping; /* Schq mapping fixed or flexible */
	u8 nix_shaping;		     /* Is shaping and coloring supported */
पूर्ण;

/* CGX mbox message क्रमmats */

काष्ठा cgx_stats_rsp अणु
	काष्ठा mbox_msghdr hdr;
#घोषणा CGX_RX_STATS_COUNT	9
#घोषणा CGX_TX_STATS_COUNT	18
	u64 rx_stats[CGX_RX_STATS_COUNT];
	u64 tx_stats[CGX_TX_STATS_COUNT];
पूर्ण;

काष्ठा cgx_fec_stats_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u64 fec_corr_blks;
	u64 fec_uncorr_blks;
पूर्ण;
/* Structure क्रम requesting the operation क्रम
 * setting/getting mac address in the CGX पूर्णांकerface
 */
काष्ठा cgx_mac_addr_set_or_get अणु
	काष्ठा mbox_msghdr hdr;
	u8 mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा cgx_link_user_info अणु
	uपूर्णांक64_t link_up:1;
	uपूर्णांक64_t full_duplex:1;
	uपूर्णांक64_t lmac_type_id:4;
	uपूर्णांक64_t speed:20; /* speed in Mbps */
	uपूर्णांक64_t an:1;		/* AN supported or not */
	uपूर्णांक64_t fec:2;	 /* FEC type अगर enabled अन्यथा 0 */
#घोषणा LMACTYPE_STR_LEN 16
	अक्षर lmac_type[LMACTYPE_STR_LEN];
पूर्ण;

काष्ठा cgx_link_info_msg अणु
	काष्ठा mbox_msghdr hdr;
	काष्ठा cgx_link_user_info link_info;
पूर्ण;

काष्ठा cgx_छोड़ो_frm_cfg अणु
	काष्ठा mbox_msghdr hdr;
	u8 set;
	/* set = 1 अगर the request is to config छोड़ो frames */
	/* set = 0 अगर the request is to fetch छोड़ो frames config */
	u8 rx_छोड़ो;
	u8 tx_छोड़ो;
पूर्ण;

क्रमागत fec_type अणु
	OTX2_FEC_NONE,
	OTX2_FEC_BASER,
	OTX2_FEC_RS,
	OTX2_FEC_STATS_CNT = 2,
	OTX2_FEC_OFF,
पूर्ण;

काष्ठा fec_mode अणु
	काष्ठा mbox_msghdr hdr;
	पूर्णांक fec;
पूर्ण;

काष्ठा sfp_eeprom_s अणु
#घोषणा SFP_EEPROM_SIZE 256
	u16 sff_id;
	u8 buf[SFP_EEPROM_SIZE];
	u64 reserved;
पूर्ण;

काष्ठा phy_s अणु
	काष्ठा अणु
		u64 can_change_mod_type:1;
		u64 mod_type:1;
		u64 has_fec_stats:1;
	पूर्ण misc;
	काष्ठा fec_stats_s अणु
		u32 rsfec_corr_cws;
		u32 rsfec_uncorr_cws;
		u32 brfec_corr_blks;
		u32 brfec_uncorr_blks;
	पूर्ण fec_stats;
पूर्ण;

काष्ठा cgx_lmac_fwdata_s अणु
	u16 rw_valid;
	u64 supported_fec;
	u64 supported_an;
	u64 supported_link_modes;
	/* only applicable अगर AN is supported */
	u64 advertised_fec;
	u64 advertised_link_modes;
	/* Only applicable अगर SFP/QSFP slot is present */
	काष्ठा sfp_eeprom_s sfp_eeprom;
	काष्ठा phy_s phy;
#घोषणा LMAC_FWDATA_RESERVED_MEM 1021
	u64 reserved[LMAC_FWDATA_RESERVED_MEM];
पूर्ण;

काष्ठा cgx_fw_data अणु
	काष्ठा mbox_msghdr hdr;
	काष्ठा cgx_lmac_fwdata_s fwdata;
पूर्ण;

काष्ठा cgx_set_link_mode_args अणु
	u32 speed;
	u8 duplex;
	u8 an;
	u8 ports;
	u64 mode;
पूर्ण;

काष्ठा cgx_set_link_mode_req अणु
#घोषणा AUTONEG_UNKNOWN		0xff
	काष्ठा mbox_msghdr hdr;
	काष्ठा cgx_set_link_mode_args args;
पूर्ण;

काष्ठा cgx_set_link_mode_rsp अणु
	काष्ठा mbox_msghdr hdr;
	पूर्णांक status;
पूर्ण;

#घोषणा RVU_LMAC_FEAT_FC		BIT_ULL(0) /* छोड़ो frames */
#घोषणा RVU_LMAC_FEAT_PTP		BIT_ULL(1) /* precision समय protocol */
#घोषणा RVU_MAC_VERSION			BIT_ULL(2)
#घोषणा RVU_MAC_CGX			BIT_ULL(3)
#घोषणा RVU_MAC_RPM			BIT_ULL(4)

काष्ठा cgx_features_info_msg अणु
	काष्ठा mbox_msghdr hdr;
	u64    lmac_features;
पूर्ण;

काष्ठा rpm_stats_rsp अणु
	काष्ठा mbox_msghdr hdr;
#घोषणा RPM_RX_STATS_COUNT		43
#घोषणा RPM_TX_STATS_COUNT		34
	u64 rx_stats[RPM_RX_STATS_COUNT];
	u64 tx_stats[RPM_TX_STATS_COUNT];
पूर्ण;

/* NPA mbox message क्रमmats */

/* NPA mailbox error codes
 * Range 301 - 400.
 */
क्रमागत npa_af_status अणु
	NPA_AF_ERR_PARAM            = -301,
	NPA_AF_ERR_AQ_FULL          = -302,
	NPA_AF_ERR_AQ_ENQUEUE       = -303,
	NPA_AF_ERR_AF_LF_INVALID    = -304,
	NPA_AF_ERR_AF_LF_ALLOC      = -305,
	NPA_AF_ERR_LF_RESET         = -306,
पूर्ण;

/* For NPA LF context alloc and init */
काष्ठा npa_lf_alloc_req अणु
	काष्ठा mbox_msghdr hdr;
	पूर्णांक node;
	पूर्णांक aura_sz;  /* No of auras */
	u32 nr_pools; /* No of pools */
	u64 way_mask;
पूर्ण;

काष्ठा npa_lf_alloc_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u32 stack_pg_ptrs;  /* No of ptrs per stack page */
	u32 stack_pg_bytes; /* Size of stack page */
	u16 qपूर्णांकs; /* NPA_AF_CONST::QINTS */
पूर्ण;

/* NPA AQ enqueue msg */
काष्ठा npa_aq_enq_req अणु
	काष्ठा mbox_msghdr hdr;
	u32 aura_id;
	u8 ctype;
	u8 op;
	जोड़ अणु
		/* Valid when op == WRITE/INIT and ctype == AURA.
		 * LF fills the pool_id in aura.pool_addr. AF will translate
		 * the pool_id to pool context poपूर्णांकer.
		 */
		काष्ठा npa_aura_s aura;
		/* Valid when op == WRITE/INIT and ctype == POOL */
		काष्ठा npa_pool_s pool;
	पूर्ण;
	/* Mask data when op == WRITE (1=ग_लिखो, 0=करोn't ग_लिखो) */
	जोड़ अणु
		/* Valid when op == WRITE and ctype == AURA */
		काष्ठा npa_aura_s aura_mask;
		/* Valid when op == WRITE and ctype == POOL */
		काष्ठा npa_pool_s pool_mask;
	पूर्ण;
पूर्ण;

काष्ठा npa_aq_enq_rsp अणु
	काष्ठा mbox_msghdr hdr;
	जोड़ अणु
		/* Valid when op == READ and ctype == AURA */
		काष्ठा npa_aura_s aura;
		/* Valid when op == READ and ctype == POOL */
		काष्ठा npa_pool_s pool;
	पूर्ण;
पूर्ण;

/* Disable all contexts of type 'ctype' */
काष्ठा hwctx_disable_req अणु
	काष्ठा mbox_msghdr hdr;
	u8 ctype;
पूर्ण;

/* NIX mbox message क्रमmats */

/* NIX mailbox error codes
 * Range 401 - 500.
 */
क्रमागत nix_af_status अणु
	NIX_AF_ERR_PARAM            = -401,
	NIX_AF_ERR_AQ_FULL          = -402,
	NIX_AF_ERR_AQ_ENQUEUE       = -403,
	NIX_AF_ERR_AF_LF_INVALID    = -404,
	NIX_AF_ERR_AF_LF_ALLOC      = -405,
	NIX_AF_ERR_TLX_ALLOC_FAIL   = -406,
	NIX_AF_ERR_TLX_INVALID      = -407,
	NIX_AF_ERR_RSS_SIZE_INVALID = -408,
	NIX_AF_ERR_RSS_GRPS_INVALID = -409,
	NIX_AF_ERR_FRS_INVALID      = -410,
	NIX_AF_ERR_RX_LINK_INVALID  = -411,
	NIX_AF_INVAL_TXSCHQ_CFG     = -412,
	NIX_AF_SMQ_FLUSH_FAILED     = -413,
	NIX_AF_ERR_LF_RESET         = -414,
	NIX_AF_ERR_RSS_NOSPC_FIELD  = -415,
	NIX_AF_ERR_RSS_NOSPC_ALGO   = -416,
	NIX_AF_ERR_MARK_CFG_FAIL    = -417,
	NIX_AF_ERR_LSO_CFG_FAIL     = -418,
	NIX_AF_INVAL_NPA_PF_FUNC    = -419,
	NIX_AF_INVAL_SSO_PF_FUNC    = -420,
	NIX_AF_ERR_TX_VTAG_NOSPC    = -421,
	NIX_AF_ERR_RX_VTAG_INUSE    = -422,
	NIX_AF_ERR_NPC_KEY_NOT_SUPP = -423,
पूर्ण;

/* For NIX RX vtag action  */
क्रमागत nix_rx_vtag0_type अणु
	NIX_AF_LFX_RX_VTAG_TYPE0, /* reserved क्रम rx vlan offload */
	NIX_AF_LFX_RX_VTAG_TYPE1,
	NIX_AF_LFX_RX_VTAG_TYPE2,
	NIX_AF_LFX_RX_VTAG_TYPE3,
	NIX_AF_LFX_RX_VTAG_TYPE4,
	NIX_AF_LFX_RX_VTAG_TYPE5,
	NIX_AF_LFX_RX_VTAG_TYPE6,
	NIX_AF_LFX_RX_VTAG_TYPE7,
पूर्ण;

/* For NIX LF context alloc and init */
काष्ठा nix_lf_alloc_req अणु
	काष्ठा mbox_msghdr hdr;
	पूर्णांक node;
	u32 rq_cnt;   /* No of receive queues */
	u32 sq_cnt;   /* No of send queues */
	u32 cq_cnt;   /* No of completion queues */
	u8  xqe_sz;
	u16 rss_sz;
	u8  rss_grps;
	u16 npa_func;
	u16 sso_func;
	u64 rx_cfg;   /* See NIX_AF_LF(0..127)_RX_CFG */
	u64 way_mask;
पूर्ण;

काष्ठा nix_lf_alloc_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u16	sqb_size;
	u16	rx_chan_base;
	u16	tx_chan_base;
	u8      rx_chan_cnt; /* total number of RX channels */
	u8      tx_chan_cnt; /* total number of TX channels */
	u8	lso_tsov4_idx;
	u8	lso_tsov6_idx;
	u8      mac_addr[ETH_ALEN];
	u8	lf_rx_stats; /* NIX_AF_CONST1::LF_RX_STATS */
	u8	lf_tx_stats; /* NIX_AF_CONST1::LF_TX_STATS */
	u16	cपूर्णांकs; /* NIX_AF_CONST2::CINTS */
	u16	qपूर्णांकs; /* NIX_AF_CONST2::QINTS */
	u8	cgx_links;  /* No. of CGX links present in HW */
	u8	lbk_links;  /* No. of LBK links present in HW */
	u8	sdp_links;  /* No. of SDP links present in HW */
पूर्ण;

काष्ठा nix_lf_मुक्त_req अणु
	काष्ठा mbox_msghdr hdr;
#घोषणा NIX_LF_DISABLE_FLOWS		BIT_ULL(0)
#घोषणा NIX_LF_DONT_FREE_TX_VTAG	BIT_ULL(1)
	u64 flags;
पूर्ण;

/* CN10K NIX AQ enqueue msg */
काष्ठा nix_cn10k_aq_enq_req अणु
	काष्ठा mbox_msghdr hdr;
	u32  qidx;
	u8 ctype;
	u8 op;
	जोड़ अणु
		काष्ठा nix_cn10k_rq_ctx_s rq;
		काष्ठा nix_cn10k_sq_ctx_s sq;
		काष्ठा nix_cq_ctx_s cq;
		काष्ठा nix_rsse_s   rss;
		काष्ठा nix_rx_mce_s mce;
	पूर्ण;
	जोड़ अणु
		काष्ठा nix_cn10k_rq_ctx_s rq_mask;
		काष्ठा nix_cn10k_sq_ctx_s sq_mask;
		काष्ठा nix_cq_ctx_s cq_mask;
		काष्ठा nix_rsse_s   rss_mask;
		काष्ठा nix_rx_mce_s mce_mask;
	पूर्ण;
पूर्ण;

काष्ठा nix_cn10k_aq_enq_rsp अणु
	काष्ठा mbox_msghdr hdr;
	जोड़ अणु
		काष्ठा nix_cn10k_rq_ctx_s rq;
		काष्ठा nix_cn10k_sq_ctx_s sq;
		काष्ठा nix_cq_ctx_s cq;
		काष्ठा nix_rsse_s   rss;
		काष्ठा nix_rx_mce_s mce;
	पूर्ण;
पूर्ण;

/* NIX AQ enqueue msg */
काष्ठा nix_aq_enq_req अणु
	काष्ठा mbox_msghdr hdr;
	u32  qidx;
	u8 ctype;
	u8 op;
	जोड़ अणु
		काष्ठा nix_rq_ctx_s rq;
		काष्ठा nix_sq_ctx_s sq;
		काष्ठा nix_cq_ctx_s cq;
		काष्ठा nix_rsse_s   rss;
		काष्ठा nix_rx_mce_s mce;
	पूर्ण;
	जोड़ अणु
		काष्ठा nix_rq_ctx_s rq_mask;
		काष्ठा nix_sq_ctx_s sq_mask;
		काष्ठा nix_cq_ctx_s cq_mask;
		काष्ठा nix_rsse_s   rss_mask;
		काष्ठा nix_rx_mce_s mce_mask;
	पूर्ण;
पूर्ण;

काष्ठा nix_aq_enq_rsp अणु
	काष्ठा mbox_msghdr hdr;
	जोड़ अणु
		काष्ठा nix_rq_ctx_s rq;
		काष्ठा nix_sq_ctx_s sq;
		काष्ठा nix_cq_ctx_s cq;
		काष्ठा nix_rsse_s   rss;
		काष्ठा nix_rx_mce_s mce;
	पूर्ण;
पूर्ण;

/* Tx scheduler/shaper mailbox messages */

#घोषणा MAX_TXSCHQ_PER_FUNC		128

काष्ठा nix_txsch_alloc_req अणु
	काष्ठा mbox_msghdr hdr;
	/* Scheduler queue count request at each level */
	u16 schq_contig[NIX_TXSCH_LVL_CNT]; /* No of contiguous queues */
	u16 schq[NIX_TXSCH_LVL_CNT]; /* No of non-contiguous queues */
पूर्ण;

काष्ठा nix_txsch_alloc_rsp अणु
	काष्ठा mbox_msghdr hdr;
	/* Scheduler queue count allocated at each level */
	u16 schq_contig[NIX_TXSCH_LVL_CNT];
	u16 schq[NIX_TXSCH_LVL_CNT];
	/* Scheduler queue list allocated at each level */
	u16 schq_contig_list[NIX_TXSCH_LVL_CNT][MAX_TXSCHQ_PER_FUNC];
	u16 schq_list[NIX_TXSCH_LVL_CNT][MAX_TXSCHQ_PER_FUNC];
	u8  aggr_level; /* Traffic aggregation scheduler level */
	u8  aggr_lvl_rr_prio; /* Aggregation lvl's RR_PRIO config */
	u8  link_cfg_lvl; /* LINKX_CFG CSRs mapped to TL3 or TL2's index ? */
पूर्ण;

काष्ठा nix_txsch_मुक्त_req अणु
	काष्ठा mbox_msghdr hdr;
#घोषणा TXSCHQ_FREE_ALL BIT_ULL(0)
	u16 flags;
	/* Scheduler queue level to be मुक्तd */
	u16 schq_lvl;
	/* List of scheduler queues to be मुक्तd */
	u16 schq;
पूर्ण;

काष्ठा nix_txschq_config अणु
	काष्ठा mbox_msghdr hdr;
	u8 lvl;	/* SMQ/MDQ/TL4/TL3/TL2/TL1 */
#घोषणा TXSCHQ_IDX_SHIFT	16
#घोषणा TXSCHQ_IDX_MASK		(BIT_ULL(10) - 1)
#घोषणा TXSCHQ_IDX(reg, shअगरt)	(((reg) >> (shअगरt)) & TXSCHQ_IDX_MASK)
	u8 num_regs;
#घोषणा MAX_REGS_PER_MBOX_MSG	20
	u64 reg[MAX_REGS_PER_MBOX_MSG];
	u64 regval[MAX_REGS_PER_MBOX_MSG];
पूर्ण;

काष्ठा nix_vtag_config अणु
	काष्ठा mbox_msghdr hdr;
	/* '0' for 4 octet VTAG, '1' क्रम 8 octet VTAG */
	u8 vtag_size;
	/* cfg_type is '0' क्रम tx vlan cfg
	 * cfg_type is '1' क्रम rx vlan cfg
	 */
	u8 cfg_type;
	जोड़ अणु
		/* valid when cfg_type is '0' */
		काष्ठा अणु
			u64 vtag0;
			u64 vtag1;

			/* cfg_vtag0 & cfg_vtag1 fields are valid
			 * when मुक्त_vtag0 & मुक्त_vtag1 are '0's.
			 */
			/* cfg_vtag0 = 1 to configure vtag0 */
			u8 cfg_vtag0 :1;
			/* cfg_vtag1 = 1 to configure vtag1 */
			u8 cfg_vtag1 :1;

			/* vtag0_idx & vtag1_idx are only valid when
			 * both cfg_vtag0 & cfg_vtag1 are '0's,
			 * these fields are used aदीर्घ with मुक्त_vtag0
			 * & मुक्त_vtag1 to मुक्त the nix lf's tx_vlan
			 * configuration.
			 *
			 * Denotes the indices of tx_vtag def रेजिस्टरs
			 * that needs to be cleared and मुक्तd.
			 */
			पूर्णांक vtag0_idx;
			पूर्णांक vtag1_idx;

			/* मुक्त_vtag0 & मुक्त_vtag1 fields are valid
			 * when cfg_vtag0 & cfg_vtag1 are '0's.
			 */
			/* मुक्त_vtag0 = 1 clears vtag0 configuration
			 * vtag0_idx denotes the index to be cleared.
			 */
			u8 मुक्त_vtag0 :1;
			/* मुक्त_vtag1 = 1 clears vtag1 configuration
			 * vtag1_idx denotes the index to be cleared.
			 */
			u8 मुक्त_vtag1 :1;
		पूर्ण tx;

		/* valid when cfg_type is '1' */
		काष्ठा अणु
			/* rx vtag type index, valid values are in 0..7 range */
			u8 vtag_type;
			/* rx vtag strip */
			u8 strip_vtag :1;
			/* rx vtag capture */
			u8 capture_vtag :1;
		पूर्ण rx;
	पूर्ण;
पूर्ण;

काष्ठा nix_vtag_config_rsp अणु
	काष्ठा mbox_msghdr hdr;
	पूर्णांक vtag0_idx;
	पूर्णांक vtag1_idx;
	/* Indices of tx_vtag def रेजिस्टरs used to configure
	 * tx vtag0 & vtag1 headers, these indices are valid
	 * when nix_vtag_config mbox requested क्रम vtag0 and/
	 * or vtag1 configuration.
	 */
पूर्ण;

काष्ठा nix_rss_flowkey_cfg अणु
	काष्ठा mbox_msghdr hdr;
	पूर्णांक	mcam_index;  /* MCAM entry index to modअगरy */
#घोषणा NIX_FLOW_KEY_TYPE_PORT	BIT(0)
#घोषणा NIX_FLOW_KEY_TYPE_IPV4	BIT(1)
#घोषणा NIX_FLOW_KEY_TYPE_IPV6	BIT(2)
#घोषणा NIX_FLOW_KEY_TYPE_TCP	BIT(3)
#घोषणा NIX_FLOW_KEY_TYPE_UDP	BIT(4)
#घोषणा NIX_FLOW_KEY_TYPE_SCTP	BIT(5)
#घोषणा NIX_FLOW_KEY_TYPE_NVGRE    BIT(6)
#घोषणा NIX_FLOW_KEY_TYPE_VXLAN    BIT(7)
#घोषणा NIX_FLOW_KEY_TYPE_GENEVE   BIT(8)
#घोषणा NIX_FLOW_KEY_TYPE_ETH_DMAC BIT(9)
#घोषणा NIX_FLOW_KEY_TYPE_IPV6_EXT BIT(10)
#घोषणा NIX_FLOW_KEY_TYPE_GTPU       BIT(11)
#घोषणा NIX_FLOW_KEY_TYPE_INNR_IPV4     BIT(12)
#घोषणा NIX_FLOW_KEY_TYPE_INNR_IPV6     BIT(13)
#घोषणा NIX_FLOW_KEY_TYPE_INNR_TCP      BIT(14)
#घोषणा NIX_FLOW_KEY_TYPE_INNR_UDP      BIT(15)
#घोषणा NIX_FLOW_KEY_TYPE_INNR_SCTP     BIT(16)
#घोषणा NIX_FLOW_KEY_TYPE_INNR_ETH_DMAC BIT(17)
#घोषणा NIX_FLOW_KEY_TYPE_VLAN		BIT(20)
#घोषणा NIX_FLOW_KEY_TYPE_IPV4_PROTO	BIT(21)
#घोषणा NIX_FLOW_KEY_TYPE_AH		BIT(22)
#घोषणा NIX_FLOW_KEY_TYPE_ESP		BIT(23)
	u32	flowkey_cfg; /* Flowkey types selected */
	u8	group;       /* RSS context or group */
पूर्ण;

काष्ठा nix_rss_flowkey_cfg_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u8	alg_idx; /* Selected algo index */
पूर्ण;

काष्ठा nix_set_mac_addr अणु
	काष्ठा mbox_msghdr hdr;
	u8 mac_addr[ETH_ALEN]; /* MAC address to be set क्रम this pcअगरunc */
पूर्ण;

काष्ठा nix_get_mac_addr_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u8 mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा nix_mark_क्रमmat_cfg अणु
	काष्ठा mbox_msghdr hdr;
	u8 offset;
	u8 y_mask;
	u8 y_val;
	u8 r_mask;
	u8 r_val;
पूर्ण;

काष्ठा nix_mark_क्रमmat_cfg_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u8 mark_क्रमmat_idx;
पूर्ण;

काष्ठा nix_rx_mode अणु
	काष्ठा mbox_msghdr hdr;
#घोषणा NIX_RX_MODE_UCAST	BIT(0)
#घोषणा NIX_RX_MODE_PROMISC	BIT(1)
#घोषणा NIX_RX_MODE_ALLMULTI	BIT(2)
	u16	mode;
पूर्ण;

काष्ठा nix_rx_cfg अणु
	काष्ठा mbox_msghdr hdr;
#घोषणा NIX_RX_OL3_VERIFY   BIT(0)
#घोषणा NIX_RX_OL4_VERIFY   BIT(1)
	u8 len_verअगरy; /* Outer L3/L4 len check */
#घोषणा NIX_RX_CSUM_OL4_VERIFY  BIT(0)
	u8 csum_verअगरy; /* Outer L4 checksum verअगरication */
पूर्ण;

काष्ठा nix_frs_cfg अणु
	काष्ठा mbox_msghdr hdr;
	u8	update_smq;    /* Update SMQ's min/max lens */
	u8	update_minlen; /* Set minlen also */
	u8	sdp_link;      /* Set SDP RX link */
	u16	maxlen;
	u16	minlen;
पूर्ण;

काष्ठा nix_lso_क्रमmat_cfg अणु
	काष्ठा mbox_msghdr hdr;
	u64 field_mask;
#घोषणा NIX_LSO_FIELD_MAX	8
	u64 fields[NIX_LSO_FIELD_MAX];
पूर्ण;

काष्ठा nix_lso_क्रमmat_cfg_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u8 lso_क्रमmat_idx;
पूर्ण;

काष्ठा nix_bp_cfg_req अणु
	काष्ठा mbox_msghdr hdr;
	u16	chan_base; /* Starting channel number */
	u8	chan_cnt; /* Number of channels */
	u8	bpid_per_chan;
	/* bpid_per_chan = 0 assigns single bp id क्रम range of channels */
	/* bpid_per_chan = 1 assigns separate bp id क्रम each channel */
पूर्ण;

/* PF can be mapped to either CGX or LBK पूर्णांकerface,
 * so maximum 64 channels are possible.
 */
#घोषणा NIX_MAX_BPID_CHAN	64
काष्ठा nix_bp_cfg_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u16	chan_bpid[NIX_MAX_BPID_CHAN]; /* Channel and bpid mapping */
	u8	chan_cnt; /* Number of channel क्रम which bpids are asचिन्हित */
पूर्ण;

काष्ठा nix_hw_info अणु
	काष्ठा mbox_msghdr hdr;
	u16 max_mtu;
	u16 min_mtu;
पूर्ण;

/* NPC mbox message काष्ठाs */

#घोषणा NPC_MCAM_ENTRY_INVALID	0xFFFF
#घोषणा NPC_MCAM_INVALID_MAP	0xFFFF

/* NPC mailbox error codes
 * Range 701 - 800.
 */
क्रमागत npc_af_status अणु
	NPC_MCAM_INVALID_REQ	= -701,
	NPC_MCAM_ALLOC_DENIED	= -702,
	NPC_MCAM_ALLOC_FAILED	= -703,
	NPC_MCAM_PERM_DENIED	= -704,
पूर्ण;

काष्ठा npc_mcam_alloc_entry_req अणु
	काष्ठा mbox_msghdr hdr;
#घोषणा NPC_MAX_NONCONTIG_ENTRIES	256
	u8  contig;   /* Contiguous entries ? */
#घोषणा NPC_MCAM_ANY_PRIO		0
#घोषणा NPC_MCAM_LOWER_PRIO		1
#घोषणा NPC_MCAM_HIGHER_PRIO		2
	u8  priority; /* Lower or higher w.r.t ref_entry */
	u16 ref_entry;
	u16 count;    /* Number of entries requested */
पूर्ण;

काष्ठा npc_mcam_alloc_entry_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u16 entry; /* Entry allocated or start index अगर contiguous.
		    * Invalid inहाल of non-contiguous.
		    */
	u16 count; /* Number of entries allocated */
	u16 मुक्त_count; /* Number of entries available */
	u16 entry_list[NPC_MAX_NONCONTIG_ENTRIES];
पूर्ण;

काष्ठा npc_mcam_मुक्त_entry_req अणु
	काष्ठा mbox_msghdr hdr;
	u16 entry; /* Entry index to be मुक्तd */
	u8  all;   /* If all entries allocated to this PFVF to be मुक्तd */
पूर्ण;

काष्ठा mcam_entry अणु
#घोषणा NPC_MAX_KWS_IN_KEY	7 /* Number of keywords in max keywidth */
	u64	kw[NPC_MAX_KWS_IN_KEY];
	u64	kw_mask[NPC_MAX_KWS_IN_KEY];
	u64	action;
	u64	vtag_action;
पूर्ण;

काष्ठा npc_mcam_ग_लिखो_entry_req अणु
	काष्ठा mbox_msghdr hdr;
	काष्ठा mcam_entry entry_data;
	u16 entry;	 /* MCAM entry to ग_लिखो this match key */
	u16 cntr;	 /* Counter क्रम this MCAM entry */
	u8  पूर्णांकf;	 /* Rx or Tx पूर्णांकerface */
	u8  enable_entry;/* Enable this MCAM entry ? */
	u8  set_cntr;    /* Set counter क्रम this entry ? */
पूर्ण;

/* Enable/Disable a given entry */
काष्ठा npc_mcam_ena_dis_entry_req अणु
	काष्ठा mbox_msghdr hdr;
	u16 entry;
पूर्ण;

काष्ठा npc_mcam_shअगरt_entry_req अणु
	काष्ठा mbox_msghdr hdr;
#घोषणा NPC_MCAM_MAX_SHIFTS	64
	u16 curr_entry[NPC_MCAM_MAX_SHIFTS];
	u16 new_entry[NPC_MCAM_MAX_SHIFTS];
	u16 shअगरt_count; /* Number of entries to shअगरt */
पूर्ण;

काष्ठा npc_mcam_shअगरt_entry_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u16 failed_entry_idx; /* Index in 'curr_entry', not entry itself */
पूर्ण;

काष्ठा npc_mcam_alloc_counter_req अणु
	काष्ठा mbox_msghdr hdr;
	u8  contig;	/* Contiguous counters ? */
#घोषणा NPC_MAX_NONCONTIG_COUNTERS       64
	u16 count;	/* Number of counters requested */
पूर्ण;

काष्ठा npc_mcam_alloc_counter_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u16 cntr;   /* Counter allocated or start index अगर contiguous.
		     * Invalid inहाल of non-contiguous.
		     */
	u16 count;  /* Number of counters allocated */
	u16 cntr_list[NPC_MAX_NONCONTIG_COUNTERS];
पूर्ण;

काष्ठा npc_mcam_oper_counter_req अणु
	काष्ठा mbox_msghdr hdr;
	u16 cntr;   /* Free a counter or clear/fetch it's stats */
पूर्ण;

काष्ठा npc_mcam_oper_counter_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u64 stat;  /* valid only जबतक fetching counter's stats */
पूर्ण;

काष्ठा npc_mcam_unmap_counter_req अणु
	काष्ठा mbox_msghdr hdr;
	u16 cntr;
	u16 entry; /* Entry and counter to be unmapped */
	u8  all;   /* Unmap all entries using this counter ? */
पूर्ण;

काष्ठा npc_mcam_alloc_and_ग_लिखो_entry_req अणु
	काष्ठा mbox_msghdr hdr;
	काष्ठा mcam_entry entry_data;
	u16 ref_entry;
	u8  priority;    /* Lower or higher w.r.t ref_entry */
	u8  पूर्णांकf;	 /* Rx or Tx पूर्णांकerface */
	u8  enable_entry;/* Enable this MCAM entry ? */
	u8  alloc_cntr;  /* Allocate counter and map ? */
पूर्ण;

काष्ठा npc_mcam_alloc_and_ग_लिखो_entry_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u16 entry;
	u16 cntr;
पूर्ण;

काष्ठा npc_get_kex_cfg_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u64 rx_keyx_cfg;   /* NPC_AF_INTF(0)_KEX_CFG */
	u64 tx_keyx_cfg;   /* NPC_AF_INTF(1)_KEX_CFG */
#घोषणा NPC_MAX_INTF	2
#घोषणा NPC_MAX_LID	8
#घोषणा NPC_MAX_LT	16
#घोषणा NPC_MAX_LD	2
#घोषणा NPC_MAX_LFL	16
	/* NPC_AF_KEX_LDATA(0..1)_FLAGS_CFG */
	u64 kex_ld_flags[NPC_MAX_LD];
	/* NPC_AF_INTF(0..1)_LID(0..7)_LT(0..15)_LD(0..1)_CFG */
	u64 पूर्णांकf_lid_lt_ld[NPC_MAX_INTF][NPC_MAX_LID][NPC_MAX_LT][NPC_MAX_LD];
	/* NPC_AF_INTF(0..1)_LDATA(0..1)_FLAGS(0..15)_CFG */
	u64 पूर्णांकf_ld_flags[NPC_MAX_INTF][NPC_MAX_LD][NPC_MAX_LFL];
#घोषणा MKEX_NAME_LEN 128
	u8 mkex_pfl_name[MKEX_NAME_LEN];
पूर्ण;

काष्ठा flow_msg अणु
	अचिन्हित अक्षर dmac[6];
	अचिन्हित अक्षर smac[6];
	__be16 etype;
	__be16 vlan_etype;
	__be16 vlan_tci;
	जोड़ अणु
		__be32 ip4src;
		__be32 ip6src[4];
	पूर्ण;
	जोड़ अणु
		__be32 ip4dst;
		__be32 ip6dst[4];
	पूर्ण;
	u8 tos;
	u8 ip_ver;
	u8 ip_proto;
	u8 tc;
	__be16 sport;
	__be16 dport;
पूर्ण;

काष्ठा npc_install_flow_req अणु
	काष्ठा mbox_msghdr hdr;
	काष्ठा flow_msg packet;
	काष्ठा flow_msg mask;
	u64 features;
	u16 entry;
	u16 channel;
	u16 chan_mask;
	u8 पूर्णांकf;
	u8 set_cntr; /* If counter is available set counter क्रम this entry ? */
	u8 शेष_rule;
	u8 append; /* overग_लिखो(0) or append(1) flow to शेष rule? */
	u16 vf;
	/* action */
	u32 index;
	u16 match_id;
	u8 flow_key_alg;
	u8 op;
	/* vtag rx action */
	u8 vtag0_type;
	u8 vtag0_valid;
	u8 vtag1_type;
	u8 vtag1_valid;
	/* vtag tx action */
	u16 vtag0_def;
	u8  vtag0_op;
	u16 vtag1_def;
	u8  vtag1_op;
पूर्ण;

काष्ठा npc_install_flow_rsp अणु
	काष्ठा mbox_msghdr hdr;
	पूर्णांक counter; /* negative अगर no counter अन्यथा counter number */
पूर्ण;

काष्ठा npc_delete_flow_req अणु
	काष्ठा mbox_msghdr hdr;
	u16 entry;
	u16 start;/*Disable range of entries */
	u16 end;
	u8 all; /* PF + VFs */
पूर्ण;

काष्ठा npc_mcam_पढ़ो_entry_req अणु
	काष्ठा mbox_msghdr hdr;
	u16 entry;	 /* MCAM entry to पढ़ो */
पूर्ण;

काष्ठा npc_mcam_पढ़ो_entry_rsp अणु
	काष्ठा mbox_msghdr hdr;
	काष्ठा mcam_entry entry_data;
	u8 पूर्णांकf;
	u8 enable;
पूर्ण;

काष्ठा npc_mcam_पढ़ो_base_rule_rsp अणु
	काष्ठा mbox_msghdr hdr;
	काष्ठा mcam_entry entry;
पूर्ण;

काष्ठा npc_mcam_get_stats_req अणु
	काष्ठा mbox_msghdr hdr;
	u16 entry; /* mcam entry */
पूर्ण;

काष्ठा npc_mcam_get_stats_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u64 stat;  /* counter stats */
	u8 stat_ena; /* enabled */
पूर्ण;

क्रमागत ptp_op अणु
	PTP_OP_ADJFINE = 0,
	PTP_OP_GET_CLOCK = 1,
पूर्ण;

काष्ठा ptp_req अणु
	काष्ठा mbox_msghdr hdr;
	u8 op;
	s64 scaled_ppm;
पूर्ण;

काष्ठा ptp_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u64 clk;
पूर्ण;

/* CPT mailbox error codes
 * Range 901 - 1000.
 */
क्रमागत cpt_af_status अणु
	CPT_AF_ERR_PARAM		= -901,
	CPT_AF_ERR_GRP_INVALID		= -902,
	CPT_AF_ERR_LF_INVALID		= -903,
	CPT_AF_ERR_ACCESS_DENIED	= -904,
	CPT_AF_ERR_SSO_PF_FUNC_INVALID	= -905,
	CPT_AF_ERR_NIX_PF_FUNC_INVALID	= -906
पूर्ण;

/* CPT mbox message क्रमmats */
काष्ठा cpt_rd_wr_reg_msg अणु
	काष्ठा mbox_msghdr hdr;
	u64 reg_offset;
	u64 *ret_val;
	u64 val;
	u8 is_ग_लिखो;
	पूर्णांक blkaddr;
पूर्ण;

काष्ठा cpt_lf_alloc_req_msg अणु
	काष्ठा mbox_msghdr hdr;
	u16 nix_pf_func;
	u16 sso_pf_func;
	u16 eng_grpmsk;
	पूर्णांक blkaddr;
पूर्ण;

/* Mailbox message request and response क्रमmat क्रम CPT stats. */
काष्ठा cpt_sts_req अणु
	काष्ठा mbox_msghdr hdr;
	u8 blkaddr;
पूर्ण;

काष्ठा cpt_sts_rsp अणु
	काष्ठा mbox_msghdr hdr;
	u64 inst_req_pc;
	u64 inst_lat_pc;
	u64 rd_req_pc;
	u64 rd_lat_pc;
	u64 rd_uc_pc;
	u64 active_cycles_pc;
	u64 ctx_mis_pc;
	u64 ctx_hit_pc;
	u64 ctx_aop_pc;
	u64 ctx_aop_lat_pc;
	u64 ctx_अगरetch_pc;
	u64 ctx_अगरetch_lat_pc;
	u64 ctx_ffetch_pc;
	u64 ctx_ffetch_lat_pc;
	u64 ctx_wback_pc;
	u64 ctx_wback_lat_pc;
	u64 ctx_psh_pc;
	u64 ctx_psh_lat_pc;
	u64 ctx_err;
	u64 ctx_enc_id;
	u64 ctx_flush_समयr;
	u64 rxc_समय;
	u64 rxc_समय_cfg;
	u64 rxc_active_sts;
	u64 rxc_zombie_sts;
	u64 busy_sts_ae;
	u64 मुक्त_sts_ae;
	u64 busy_sts_se;
	u64 मुक्त_sts_se;
	u64 busy_sts_ie;
	u64 मुक्त_sts_ie;
	u64 exe_err_info;
	u64 cptclk_cnt;
	u64 diag;
	u64 rxc_dfrg;
	u64 x2p_link_cfg0;
	u64 x2p_link_cfg1;
पूर्ण;

/* Mailbox message request क्रमmat to configure reassembly समयout. */
काष्ठा cpt_rxc_समय_cfg_req अणु
	काष्ठा mbox_msghdr hdr;
	पूर्णांक blkaddr;
	u32 step;
	u16 zombie_thres;
	u16 zombie_limit;
	u16 active_thres;
	u16 active_limit;
पूर्ण;

#पूर्ण_अगर /* MBOX_H */
