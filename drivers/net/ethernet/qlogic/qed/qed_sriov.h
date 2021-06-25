<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_SRIOV_H
#घोषणा _QED_SRIOV_H
#समावेश <linux/types.h>
#समावेश "qed_vf.h"

#घोषणा QED_ETH_VF_NUM_MAC_FILTERS 1
#घोषणा QED_ETH_VF_NUM_VLAN_FILTERS 2
#घोषणा QED_VF_ARRAY_LENGTH (3)

#अगर_घोषित CONFIG_QED_SRIOV
#घोषणा IS_VF(cdev)             ((cdev)->b_is_vf)
#घोषणा IS_PF(cdev)             (!((cdev)->b_is_vf))
#घोषणा IS_PF_SRIOV(p_hwfn)     (!!((p_hwfn)->cdev->p_iov_info))
#अन्यथा
#घोषणा IS_VF(cdev)             (0)
#घोषणा IS_PF(cdev)             (1)
#घोषणा IS_PF_SRIOV(p_hwfn)     (0)
#पूर्ण_अगर
#घोषणा IS_PF_SRIOV_ALLOC(p_hwfn)       (!!((p_hwfn)->pf_iov_info))

#घोषणा QED_MAX_VF_CHAINS_PER_PF 16

#घोषणा QED_ETH_MAX_VF_NUM_VLAN_FILTERS	\
	(MAX_NUM_VFS * QED_ETH_VF_NUM_VLAN_FILTERS)

क्रमागत qed_iov_vport_update_flag अणु
	QED_IOV_VP_UPDATE_ACTIVATE,
	QED_IOV_VP_UPDATE_VLAN_STRIP,
	QED_IOV_VP_UPDATE_TX_SWITCH,
	QED_IOV_VP_UPDATE_MCAST,
	QED_IOV_VP_UPDATE_ACCEPT_PARAM,
	QED_IOV_VP_UPDATE_RSS,
	QED_IOV_VP_UPDATE_ACCEPT_ANY_VLAN,
	QED_IOV_VP_UPDATE_SGE_TPA,
	QED_IOV_VP_UPDATE_MAX,
पूर्ण;

काष्ठा qed_खुला_vf_info अणु
	/* These copies will later be reflected in the bulletin board,
	 * but this copy should be newer.
	 */
	u8 क्रमced_mac[ETH_ALEN];
	u16 क्रमced_vlan;
	u8 mac[ETH_ALEN];

	/* IFLA_VF_LINK_STATE_<X> */
	पूर्णांक link_state;

	/* Currently configured Tx rate in MB/sec. 0 अगर unconfigured */
	पूर्णांक tx_rate;

	/* Trusted VFs can configure promiscuous mode.
	 * Also store shaकरोw promisc configuration अगर needed.
	 */
	bool is_trusted_configured;
	bool is_trusted_request;
	u8 rx_accept_mode;
	u8 tx_accept_mode;
पूर्ण;

काष्ठा qed_iov_vf_init_params अणु
	u16 rel_vf_id;

	/* Number of requested Queues; Currently, करोn't support dअगरferent
	 * number of Rx/Tx queues.
	 */

	u16 num_queues;

	/* Allow the client to choose which qzones to use क्रम Rx/Tx,
	 * and which queue_base to use क्रम Tx queues on a per-queue basis.
	 * Notice values should be relative to the PF resources.
	 */
	u16 req_rx_queue[QED_MAX_VF_CHAINS_PER_PF];
	u16 req_tx_queue[QED_MAX_VF_CHAINS_PER_PF];
पूर्ण;

/* This काष्ठा is part of qed_dev and contains data relevant to all hwfns;
 * Initialized only अगर SR-IOV cpabability is exposed in PCIe config space.
 */
काष्ठा qed_hw_sriov_info अणु
	पूर्णांक pos;		/* capability position */
	पूर्णांक nres;		/* number of resources */
	u32 cap;		/* SR-IOV Capabilities */
	u16 ctrl;		/* SR-IOV Control */
	u16 total_vfs;		/* total VFs associated with the PF */
	u16 num_vfs;		/* number of vfs that have been started */
	u16 initial_vfs;	/* initial VFs associated with the PF */
	u16 nr_virtfn;		/* number of VFs available */
	u16 offset;		/* first VF Routing ID offset */
	u16 stride;		/* following VF stride */
	u16 vf_device_id;	/* VF device id */
	u32 pgsz;		/* page size क्रम BAR alignment */
	u8 link;		/* Function Dependency Link */

	u32 first_vf_in_pf;
पूर्ण;

/* This mailbox is मुख्यtained per VF in its PF contains all inक्रमmation
 * required क्रम sending / receiving a message.
 */
काष्ठा qed_iov_vf_mbx अणु
	जोड़ vfpf_tlvs *req_virt;
	dma_addr_t req_phys;
	जोड़ pfvf_tlvs *reply_virt;
	dma_addr_t reply_phys;

	/* Address in VF where a pending message is located */
	dma_addr_t pending_req;

	/* Message from VF aरुकोs handling */
	bool b_pending_msg;

	u8 *offset;

	/* saved VF request header */
	काष्ठा vfpf_first_tlv first_tlv;
पूर्ण;

#घोषणा QED_IOV_LEGACY_QID_RX (0)
#घोषणा QED_IOV_LEGACY_QID_TX (1)
#घोषणा QED_IOV_QID_INVALID (0xFE)

काष्ठा qed_vf_queue_cid अणु
	bool b_is_tx;
	काष्ठा qed_queue_cid *p_cid;
पूर्ण;

/* Describes a qzone associated with the VF */
काष्ठा qed_vf_queue अणु
	u16 fw_rx_qid;
	u16 fw_tx_qid;

	काष्ठा qed_vf_queue_cid cids[MAX_QUEUES_PER_QZONE];
पूर्ण;

क्रमागत vf_state अणु
	VF_FREE = 0,		/* VF पढ़ोy to be acquired holds no resc */
	VF_ACQUIRED,		/* VF, acquired, but not initalized */
	VF_ENABLED,		/* VF, Enabled */
	VF_RESET,		/* VF, FLR'd, pending cleanup */
	VF_STOPPED		/* VF, Stopped */
पूर्ण;

काष्ठा qed_vf_vlan_shaकरोw अणु
	bool used;
	u16 vid;
पूर्ण;

काष्ठा qed_vf_shaकरोw_config अणु
	/* Shaकरोw copy of all guest vlans */
	काष्ठा qed_vf_vlan_shaकरोw vlans[QED_ETH_VF_NUM_VLAN_FILTERS + 1];

	/* Shaकरोw copy of all configured MACs; Empty अगर क्रमcing MACs */
	u8 macs[QED_ETH_VF_NUM_MAC_FILTERS][ETH_ALEN];
	u8 inner_vlan_removal;
पूर्ण;

/* PFs मुख्यtain an array of this काष्ठाure, per VF */
काष्ठा qed_vf_info अणु
	काष्ठा qed_iov_vf_mbx vf_mbx;
	क्रमागत vf_state state;
	bool b_init;
	bool b_malicious;
	u8 to_disable;

	काष्ठा qed_bulletin bulletin;
	dma_addr_t vf_bulletin;

	/* PF saves a copy of the last VF acquire message */
	काष्ठा vfpf_acquire_tlv acquire;

	u32 concrete_fid;
	u16 opaque_fid;
	u16 mtu;

	u8 vport_id;
	u8 relative_vf_id;
	u8 असल_vf_id;
#घोषणा QED_VF_ABS_ID(p_hwfn, p_vf)	(QED_PATH_ID(p_hwfn) ?		      \
					 (p_vf)->असल_vf_id + MAX_NUM_VFS_BB : \
					 (p_vf)->असल_vf_id)

	u8 vport_instance;
	u8 num_rxqs;
	u8 num_txqs;

	u16 rx_coal;
	u16 tx_coal;

	u8 num_sbs;

	u8 num_mac_filters;
	u8 num_vlan_filters;

	काष्ठा qed_vf_queue vf_queues[QED_MAX_VF_CHAINS_PER_PF];
	u16 igu_sbs[QED_MAX_VF_CHAINS_PER_PF];
	u8 num_active_rxqs;
	काष्ठा qed_खुला_vf_info p_vf_info;
	bool spoof_chk;
	bool req_spoofchk_val;

	/* Stores the configuration requested by VF */
	काष्ठा qed_vf_shaकरोw_config shaकरोw_config;

	/* A bitfield using bulletin's valid-map bits, used to indicate
	 * which of the bulletin board features have been configured.
	 */
	u64 configured_features;
#घोषणा QED_IOV_CONFIGURED_FEATURES_MASK        ((1 << MAC_ADDR_FORCED) | \
						 (1 << VLAN_ADDR_FORCED))
पूर्ण;

/* This काष्ठाure is part of qed_hwfn and used only क्रम PFs that have sriov
 * capability enabled.
 */
काष्ठा qed_pf_iov अणु
	काष्ठा qed_vf_info vfs_array[MAX_NUM_VFS];
	u64 pending_flr[QED_VF_ARRAY_LENGTH];

	/* Allocate message address continuosuly and split to each VF */
	व्योम *mbx_msg_virt_addr;
	dma_addr_t mbx_msg_phys_addr;
	u32 mbx_msg_size;
	व्योम *mbx_reply_virt_addr;
	dma_addr_t mbx_reply_phys_addr;
	u32 mbx_reply_size;
	व्योम *p_bulletins;
	dma_addr_t bulletins_phys;
	u32 bulletins_size;
पूर्ण;

क्रमागत qed_iov_wq_flag अणु
	QED_IOV_WQ_MSG_FLAG,
	QED_IOV_WQ_SET_UNICAST_FILTER_FLAG,
	QED_IOV_WQ_BULLETIN_UPDATE_FLAG,
	QED_IOV_WQ_STOP_WQ_FLAG,
	QED_IOV_WQ_FLR_FLAG,
	QED_IOV_WQ_TRUST_FLAG,
	QED_IOV_WQ_VF_FORCE_LINK_QUERY_FLAG,
पूर्ण;

बाह्य स्थिर काष्ठा qed_iov_hv_ops qed_iov_ops_pass;

#अगर_घोषित CONFIG_QED_SRIOV
/**
 * @brief Check अगर given VF ID @vfid is valid
 *        w.r.t. @b_enabled_only value
 *        अगर b_enabled_only = true - only enabled VF id is valid
 *        अन्यथा any VF id less than max_vfs is valid
 *
 * @param p_hwfn
 * @param rel_vf_id - Relative VF ID
 * @param b_enabled_only - consider only enabled VF
 * @param b_non_malicious - true अगरf we want to validate vf isn't malicious.
 *
 * @वापस bool - true क्रम valid VF ID
 */
bool qed_iov_is_valid_vfid(काष्ठा qed_hwfn *p_hwfn,
			   पूर्णांक rel_vf_id,
			   bool b_enabled_only, bool b_non_malicious);

/**
 * @brief - Given a VF index, वापस index of next [including that] active VF.
 *
 * @param p_hwfn
 * @param rel_vf_id
 *
 * @वापस MAX_NUM_VFS in हाल no further active VFs, otherwise index.
 */
u16 qed_iov_get_next_active_vf(काष्ठा qed_hwfn *p_hwfn, u16 rel_vf_id);

व्योम qed_iov_bulletin_set_udp_ports(काष्ठा qed_hwfn *p_hwfn,
				    पूर्णांक vfid, u16 vxlan_port, u16 geneve_port);

/**
 * @brief Read sriov related inक्रमmation and allocated resources
 *  पढ़ोs from configuration space, shmem, etc.
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_iov_hw_info(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_add_tlv - place a given tlv on the tlv buffer at next offset
 *
 * @param p_hwfn
 * @param p_iov
 * @param type
 * @param length
 *
 * @वापस poपूर्णांकer to the newly placed tlv
 */
व्योम *qed_add_tlv(काष्ठा qed_hwfn *p_hwfn, u8 **offset, u16 type, u16 length);

/**
 * @brief list the types and lengths of the tlvs on the buffer
 *
 * @param p_hwfn
 * @param tlvs_list
 */
व्योम qed_dp_tlv_list(काष्ठा qed_hwfn *p_hwfn, व्योम *tlvs_list);

/**
 * @brief qed_iov_alloc - allocate sriov related resources
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_iov_alloc(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_iov_setup - setup sriov related resources
 *
 * @param p_hwfn
 */
व्योम qed_iov_setup(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_iov_मुक्त - मुक्त sriov related resources
 *
 * @param p_hwfn
 */
व्योम qed_iov_मुक्त(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief मुक्त sriov related memory that was allocated during hw_prepare
 *
 * @param cdev
 */
व्योम qed_iov_मुक्त_hw_info(काष्ठा qed_dev *cdev);

/**
 * @brief Mark काष्ठाs of vfs that have been FLR-ed.
 *
 * @param p_hwfn
 * @param disabled_vfs - biपंचांगask of all VFs on path that were FLRed
 *
 * @वापस true अगरf one of the PF's vfs got FLRed. false otherwise.
 */
bool qed_iov_mark_vf_flr(काष्ठा qed_hwfn *p_hwfn, u32 *disabled_vfs);

/**
 * @brief Search extended TLVs in request/reply buffer.
 *
 * @param p_hwfn
 * @param p_tlvs_list - Poपूर्णांकer to tlvs list
 * @param req_type - Type of TLV
 *
 * @वापस poपूर्णांकer to tlv type अगर found, otherwise वापसs शून्य.
 */
व्योम *qed_iov_search_list_tlvs(काष्ठा qed_hwfn *p_hwfn,
			       व्योम *p_tlvs_list, u16 req_type);

व्योम qed_iov_wq_stop(काष्ठा qed_dev *cdev, bool schedule_first);
पूर्णांक qed_iov_wq_start(काष्ठा qed_dev *cdev);

व्योम qed_schedule_iov(काष्ठा qed_hwfn *hwfn, क्रमागत qed_iov_wq_flag flag);
व्योम qed_vf_start_iov_wq(काष्ठा qed_dev *cdev);
पूर्णांक qed_sriov_disable(काष्ठा qed_dev *cdev, bool pci_enabled);
व्योम qed_inक्रमm_vf_link_state(काष्ठा qed_hwfn *hwfn);
#अन्यथा
अटल अंतरभूत bool
qed_iov_is_valid_vfid(काष्ठा qed_hwfn *p_hwfn,
		      पूर्णांक rel_vf_id, bool b_enabled_only, bool b_non_malicious)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत u16 qed_iov_get_next_active_vf(काष्ठा qed_hwfn *p_hwfn,
					     u16 rel_vf_id)
अणु
	वापस MAX_NUM_VFS;
पूर्ण

अटल अंतरभूत व्योम
qed_iov_bulletin_set_udp_ports(काष्ठा qed_hwfn *p_hwfn, पूर्णांक vfid,
			       u16 vxlan_port, u16 geneve_port)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक qed_iov_hw_info(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक qed_iov_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qed_iov_setup(काष्ठा qed_hwfn *p_hwfn)
अणु
पूर्ण

अटल अंतरभूत व्योम qed_iov_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
पूर्ण

अटल अंतरभूत व्योम qed_iov_मुक्त_hw_info(काष्ठा qed_dev *cdev)
अणु
पूर्ण

अटल अंतरभूत bool qed_iov_mark_vf_flr(काष्ठा qed_hwfn *p_hwfn,
				       u32 *disabled_vfs)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम qed_iov_wq_stop(काष्ठा qed_dev *cdev, bool schedule_first)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक qed_iov_wq_start(काष्ठा qed_dev *cdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qed_schedule_iov(काष्ठा qed_hwfn *hwfn,
				    क्रमागत qed_iov_wq_flag flag)
अणु
पूर्ण

अटल अंतरभूत व्योम qed_vf_start_iov_wq(काष्ठा qed_dev *cdev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक qed_sriov_disable(काष्ठा qed_dev *cdev, bool pci_enabled)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qed_inक्रमm_vf_link_state(काष्ठा qed_hwfn *hwfn)
अणु
पूर्ण
#पूर्ण_अगर

#घोषणा qed_क्रम_each_vf(_p_hwfn, _i)			  \
	क्रम (_i = qed_iov_get_next_active_vf(_p_hwfn, 0); \
	     _i < MAX_NUM_VFS;				  \
	     _i = qed_iov_get_next_active_vf(_p_hwfn, _i + 1))

#पूर्ण_अगर
