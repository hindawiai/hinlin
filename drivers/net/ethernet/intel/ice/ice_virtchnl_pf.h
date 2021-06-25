<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _ICE_VIRTCHNL_PF_H_
#घोषणा _ICE_VIRTCHNL_PF_H_
#समावेश "ice.h"
#समावेश "ice_virtchnl_fdir.h"

/* Restrict number of MAC Addr and VLAN that non-trusted VF can programmed */
#घोषणा ICE_MAX_VLAN_PER_VF		8
/* MAC filters: 1 is reserved क्रम the VF's शेष/perm_addr/LAA MAC, 1 क्रम
 * broadcast, and 16 क्रम additional unicast/multicast filters
 */
#घोषणा ICE_MAX_MACADDR_PER_VF		18

/* Malicious Driver Detection */
#घोषणा ICE_DFLT_NUM_INVAL_MSGS_ALLOWED		10
#घोषणा ICE_MDD_EVENTS_THRESHOLD		30

/* Static VF transaction/status रेजिस्टर def */
#घोषणा VF_DEVICE_STATUS		0xAA
#घोषणा VF_TRANS_PENDING_M		0x20

/* रुको defines क्रम polling PF_PCI_CIAD रेजिस्टर status */
#घोषणा ICE_PCI_CIAD_WAIT_COUNT		100
#घोषणा ICE_PCI_CIAD_WAIT_DELAY_US	1

/* VF resource स्थिरraपूर्णांकs */
#घोषणा ICE_MAX_VF_COUNT		256
#घोषणा ICE_MIN_QS_PER_VF		1
#घोषणा ICE_NONQ_VECS_VF		1
#घोषणा ICE_MAX_SCATTER_QS_PER_VF	16
#घोषणा ICE_MAX_RSS_QS_PER_VF		16
#घोषणा ICE_NUM_VF_MSIX_MED		17
#घोषणा ICE_NUM_VF_MSIX_SMALL		5
#घोषणा ICE_NUM_VF_MSIX_MULTIQ_MIN	3
#घोषणा ICE_MIN_INTR_PER_VF		(ICE_MIN_QS_PER_VF + 1)
#घोषणा ICE_MAX_VF_RESET_TRIES		40
#घोषणा ICE_MAX_VF_RESET_SLEEP_MS	20

#घोषणा ice_क्रम_each_vf(pf, i) \
	क्रम ((i) = 0; (i) < (pf)->num_alloc_vfs; (i)++)

/* Specअगरic VF states */
क्रमागत ice_vf_states अणु
	ICE_VF_STATE_INIT = 0,		/* PF is initializing VF */
	ICE_VF_STATE_ACTIVE,		/* VF resources are allocated क्रम use */
	ICE_VF_STATE_QS_ENA,		/* VF queue(s) enabled */
	ICE_VF_STATE_DIS,
	ICE_VF_STATE_MC_PROMISC,
	ICE_VF_STATE_UC_PROMISC,
	ICE_VF_STATES_NBITS
पूर्ण;

/* VF capabilities */
क्रमागत ice_virtchnl_cap अणु
	ICE_VIRTCHNL_VF_CAP_L2 = 0,
	ICE_VIRTCHNL_VF_CAP_PRIVILEGE,
पूर्ण;

/* VF MDD events prपूर्णांक काष्ठाure */
काष्ठा ice_mdd_vf_events अणु
	u16 count;			/* total count of Rx|Tx events */
	/* count number of the last prपूर्णांकed event */
	u16 last_prपूर्णांकed;
पूर्ण;

/* VF inक्रमmation काष्ठाure */
काष्ठा ice_vf अणु
	काष्ठा ice_pf *pf;

	u16 vf_id;			/* VF ID in the PF space */
	u16 lan_vsi_idx;		/* index पूर्णांकo PF काष्ठा */
	u16 ctrl_vsi_idx;
	काष्ठा ice_vf_fdir fdir;
	/* first vector index of this VF in the PF space */
	पूर्णांक first_vector_idx;
	काष्ठा ice_sw *vf_sw_id;	/* चयन ID the VF VSIs connect to */
	काष्ठा virtchnl_version_info vf_ver;
	u32 driver_caps;		/* reported by VF driver */
	काष्ठा virtchnl_ether_addr dflt_lan_addr;
	DECLARE_BITMAP(txq_ena, ICE_MAX_RSS_QS_PER_VF);
	DECLARE_BITMAP(rxq_ena, ICE_MAX_RSS_QS_PER_VF);
	u16 port_vlan_info;		/* Port VLAN ID and QoS */
	u8 pf_set_mac:1;		/* VF MAC address set by VMM admin */
	u8 trusted:1;
	u8 spoofchk:1;
	u8 link_क्रमced:1;
	u8 link_up:1;			/* only valid अगर VF link is क्रमced */
	/* VSI indices - actual VSI poपूर्णांकers are मुख्यtained in the PF काष्ठाure
	 * When asचिन्हित, these will be non-zero, because VSI 0 is always
	 * the मुख्य LAN VSI क्रम the PF.
	 */
	u16 lan_vsi_num;		/* ID as used by firmware */
	अचिन्हित पूर्णांक tx_rate;		/* Tx bandwidth limit in Mbps */
	DECLARE_BITMAP(vf_states, ICE_VF_STATES_NBITS);	/* VF runसमय states */

	u64 num_inval_msgs;		/* number of continuous invalid msgs */
	u64 num_valid_msgs;		/* number of valid msgs detected */
	अचिन्हित दीर्घ vf_caps;		/* VF's adv. capabilities */
	u8 num_req_qs;			/* num of queue pairs requested by VF */
	u16 num_mac;
	u16 num_vf_qs;			/* num of queue configured per VF */
	काष्ठा ice_mdd_vf_events mdd_rx_events;
	काष्ठा ice_mdd_vf_events mdd_tx_events;
	DECLARE_BITMAP(opcodes_allowlist, VIRTCHNL_OP_MAX);
पूर्ण;

#अगर_घोषित CONFIG_PCI_IOV
व्योम ice_process_vflr_event(काष्ठा ice_pf *pf);
पूर्णांक ice_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs);
पूर्णांक ice_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf_id, u8 *mac);
पूर्णांक
ice_get_vf_cfg(काष्ठा net_device *netdev, पूर्णांक vf_id, काष्ठा अगरla_vf_info *ivi);

व्योम ice_मुक्त_vfs(काष्ठा ice_pf *pf);
व्योम ice_vc_process_vf_msg(काष्ठा ice_pf *pf, काष्ठा ice_rq_event_info *event);
व्योम ice_vc_notअगरy_link_state(काष्ठा ice_pf *pf);
व्योम ice_vc_notअगरy_reset(काष्ठा ice_pf *pf);
bool ice_reset_all_vfs(काष्ठा ice_pf *pf, bool is_vflr);
bool ice_reset_vf(काष्ठा ice_vf *vf, bool is_vflr);
व्योम ice_restore_all_vfs_msi_state(काष्ठा pci_dev *pdev);
bool
ice_is_malicious_vf(काष्ठा ice_pf *pf, काष्ठा ice_rq_event_info *event,
		    u16 num_msg_proc, u16 num_msg_pending);

पूर्णांक
ice_set_vf_port_vlan(काष्ठा net_device *netdev, पूर्णांक vf_id, u16 vlan_id, u8 qos,
		     __be16 vlan_proto);

पूर्णांक ice_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf_id, bool trusted);

पूर्णांक ice_set_vf_link_state(काष्ठा net_device *netdev, पूर्णांक vf_id, पूर्णांक link_state);

पूर्णांक ice_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf_id, bool ena);

पूर्णांक ice_calc_vf_reg_idx(काष्ठा ice_vf *vf, काष्ठा ice_q_vector *q_vector);

व्योम ice_set_vf_state_qs_dis(काष्ठा ice_vf *vf);
पूर्णांक
ice_get_vf_stats(काष्ठा net_device *netdev, पूर्णांक vf_id,
		 काष्ठा अगरla_vf_stats *vf_stats);
bool ice_is_any_vf_in_promisc(काष्ठा ice_pf *pf);
व्योम
ice_vf_lan_overflow_event(काष्ठा ice_pf *pf, काष्ठा ice_rq_event_info *event);
व्योम ice_prपूर्णांक_vfs_mdd_events(काष्ठा ice_pf *pf);
व्योम ice_prपूर्णांक_vf_rx_mdd_event(काष्ठा ice_vf *vf);
काष्ठा ice_vsi *ice_vf_ctrl_vsi_setup(काष्ठा ice_vf *vf);
पूर्णांक
ice_vc_send_msg_to_vf(काष्ठा ice_vf *vf, u32 v_opcode,
		      क्रमागत virtchnl_status_code v_retval, u8 *msg, u16 msglen);
bool ice_vc_isvalid_vsi_id(काष्ठा ice_vf *vf, u16 vsi_id);
#अन्यथा /* CONFIG_PCI_IOV */
#घोषणा ice_process_vflr_event(pf) करो अणुपूर्ण जबतक (0)
#घोषणा ice_मुक्त_vfs(pf) करो अणुपूर्ण जबतक (0)
#घोषणा ice_vc_process_vf_msg(pf, event) करो अणुपूर्ण जबतक (0)
#घोषणा ice_vc_notअगरy_link_state(pf) करो अणुपूर्ण जबतक (0)
#घोषणा ice_vc_notअगरy_reset(pf) करो अणुपूर्ण जबतक (0)
#घोषणा ice_set_vf_state_qs_dis(vf) करो अणुपूर्ण जबतक (0)
#घोषणा ice_vf_lan_overflow_event(pf, event) करो अणुपूर्ण जबतक (0)
#घोषणा ice_prपूर्णांक_vfs_mdd_events(pf) करो अणुपूर्ण जबतक (0)
#घोषणा ice_prपूर्णांक_vf_rx_mdd_event(vf) करो अणुपूर्ण जबतक (0)
#घोषणा ice_restore_all_vfs_msi_state(pdev) करो अणुपूर्ण जबतक (0)

अटल अंतरभूत bool
ice_is_malicious_vf(काष्ठा ice_pf __always_unused *pf,
		    काष्ठा ice_rq_event_info __always_unused *event,
		    u16 __always_unused num_msg_proc,
		    u16 __always_unused num_msg_pending)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool
ice_reset_all_vfs(काष्ठा ice_pf __always_unused *pf,
		  bool __always_unused is_vflr)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool
ice_reset_vf(काष्ठा ice_vf __always_unused *vf, bool __always_unused is_vflr)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_sriov_configure(काष्ठा pci_dev __always_unused *pdev,
		    पूर्णांक __always_unused num_vfs)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_set_vf_mac(काष्ठा net_device __always_unused *netdev,
	       पूर्णांक __always_unused vf_id, u8 __always_unused *mac)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_get_vf_cfg(काष्ठा net_device __always_unused *netdev,
	       पूर्णांक __always_unused vf_id,
	       काष्ठा अगरla_vf_info __always_unused *ivi)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_set_vf_trust(काष्ठा net_device __always_unused *netdev,
		 पूर्णांक __always_unused vf_id, bool __always_unused trusted)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_set_vf_port_vlan(काष्ठा net_device __always_unused *netdev,
		     पूर्णांक __always_unused vf_id, u16 __always_unused vid,
		     u8 __always_unused qos, __be16 __always_unused v_proto)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_set_vf_spoofchk(काष्ठा net_device __always_unused *netdev,
		    पूर्णांक __always_unused vf_id, bool __always_unused ena)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_set_vf_link_state(काष्ठा net_device __always_unused *netdev,
		      पूर्णांक __always_unused vf_id, पूर्णांक __always_unused link_state)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_calc_vf_reg_idx(काष्ठा ice_vf __always_unused *vf,
		    काष्ठा ice_q_vector __always_unused *q_vector)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
ice_get_vf_stats(काष्ठा net_device __always_unused *netdev,
		 पूर्णांक __always_unused vf_id,
		 काष्ठा अगरla_vf_stats __always_unused *vf_stats)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत bool ice_is_any_vf_in_promisc(काष्ठा ice_pf __always_unused *pf)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_IOV */
#पूर्ण_अगर /* _ICE_VIRTCHNL_PF_H_ */
