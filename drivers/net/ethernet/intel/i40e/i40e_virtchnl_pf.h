<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _I40E_VIRTCHNL_PF_H_
#घोषणा _I40E_VIRTCHNL_PF_H_

#समावेश "i40e.h"

#घोषणा I40E_MAX_VLANID 4095

#घोषणा I40E_VIRTCHNL_SUPPORTED_QTYPES 2

#घोषणा I40E_DEFAULT_NUM_INVALID_MSGS_ALLOWED	10

#घोषणा I40E_VLAN_PRIORITY_SHIFT	13
#घोषणा I40E_VLAN_MASK			0xFFF
#घोषणा I40E_PRIORITY_MASK		0xE000

#घोषणा I40E_MAX_VF_PROMISC_FLAGS	3

/* Various queue ctrls */
क्रमागत i40e_queue_ctrl अणु
	I40E_QUEUE_CTRL_UNKNOWN = 0,
	I40E_QUEUE_CTRL_ENABLE,
	I40E_QUEUE_CTRL_ENABLECHECK,
	I40E_QUEUE_CTRL_DISABLE,
	I40E_QUEUE_CTRL_DISABLECHECK,
	I40E_QUEUE_CTRL_FASTDISABLE,
	I40E_QUEUE_CTRL_FASTDISABLECHECK,
पूर्ण;

/* VF states */
क्रमागत i40e_vf_states अणु
	I40E_VF_STATE_INIT = 0,
	I40E_VF_STATE_ACTIVE,
	I40E_VF_STATE_IWARPENA,
	I40E_VF_STATE_DISABLED,
	I40E_VF_STATE_MC_PROMISC,
	I40E_VF_STATE_UC_PROMISC,
	I40E_VF_STATE_PRE_ENABLE,
पूर्ण;

/* VF capabilities */
क्रमागत i40e_vf_capabilities अणु
	I40E_VIRTCHNL_VF_CAP_PRIVILEGE = 0,
	I40E_VIRTCHNL_VF_CAP_L2,
	I40E_VIRTCHNL_VF_CAP_IWARP,
पूर्ण;

/* In ADq, max 4 VSI's can be allocated per VF including primary VF VSI.
 * These variables are used to store indices, id's and number of queues
 * क्रम each VSI including that of primary VF VSI. Each Traffic class is
 * termed as channel and each channel can in-turn have 4 queues which
 * means max 16 queues overall per VF.
 */
काष्ठा i40evf_channel अणु
	u16 vsi_idx; /* index in PF काष्ठा क्रम all channel VSIs */
	u16 vsi_id; /* VSI ID used by firmware */
	u16 num_qps; /* number of queue pairs requested by user */
	u64 max_tx_rate; /* bandwidth rate allocation क्रम VSIs */
पूर्ण;

/* VF inक्रमmation काष्ठाure */
काष्ठा i40e_vf अणु
	काष्ठा i40e_pf *pf;

	/* VF id in the PF space */
	s16 vf_id;
	/* all VF vsis connect to the same parent */
	क्रमागत i40e_चयन_element_types parent_type;
	काष्ठा virtchnl_version_info vf_ver;
	u32 driver_caps; /* reported by VF driver */

	/* VF Port Extender (PE) stag अगर used */
	u16 stag;

	काष्ठा virtchnl_ether_addr शेष_lan_addr;
	u16 port_vlan_id;
	bool pf_set_mac;	/* The VMM admin set the VF MAC address */
	bool trusted;

	/* VSI indices - actual VSI poपूर्णांकers are मुख्यtained in the PF काष्ठाure
	 * When asचिन्हित, these will be non-zero, because VSI 0 is always
	 * the मुख्य LAN VSI क्रम the PF.
	 */
	u16 lan_vsi_idx;	/* index पूर्णांकo PF काष्ठा */
	u16 lan_vsi_id;		/* ID as used by firmware */

	u8 num_queue_pairs;	/* num of qps asचिन्हित to VF vsis */
	u8 num_req_queues;	/* num of requested qps */
	u64 num_mdd_events;	/* num of mdd events detected */
	/* num of continuous malक्रमmed or invalid msgs detected */
	u64 num_invalid_msgs;
	u64 num_valid_msgs;	/* num of valid msgs detected */

	अचिन्हित दीर्घ vf_caps;	/* vf's adv. capabilities */
	अचिन्हित दीर्घ vf_states;	/* vf's runसमय states */
	अचिन्हित पूर्णांक tx_rate;	/* Tx bandwidth limit in Mbps */
	bool link_क्रमced;
	bool link_up;		/* only valid अगर VF link is क्रमced */
	bool spoofchk;
	u16 num_vlan;

	/* ADq related variables */
	bool adq_enabled; /* flag to enable adq */
	u8 num_tc;
	काष्ठा i40evf_channel ch[I40E_MAX_VF_VSI];
	काष्ठा hlist_head cloud_filter_list;
	u16 num_cloud_filters;

	/* RDMA Client */
	काष्ठा virtchnl_iwarp_qvlist_info *qvlist_info;
पूर्ण;

व्योम i40e_मुक्त_vfs(काष्ठा i40e_pf *pf);
पूर्णांक i40e_pci_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक num_vfs);
पूर्णांक i40e_alloc_vfs(काष्ठा i40e_pf *pf, u16 num_alloc_vfs);
पूर्णांक i40e_vc_process_vf_msg(काष्ठा i40e_pf *pf, s16 vf_id, u32 v_opcode,
			   u32 v_retval, u8 *msg, u16 msglen);
पूर्णांक i40e_vc_process_vflr_event(काष्ठा i40e_pf *pf);
bool i40e_reset_vf(काष्ठा i40e_vf *vf, bool flr);
bool i40e_reset_all_vfs(काष्ठा i40e_pf *pf, bool flr);
व्योम i40e_vc_notअगरy_vf_reset(काष्ठा i40e_vf *vf);

/* VF configuration related iplink handlers */
पूर्णांक i40e_nकरो_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf_id, u8 *mac);
पूर्णांक i40e_nकरो_set_vf_port_vlan(काष्ठा net_device *netdev, पूर्णांक vf_id,
			      u16 vlan_id, u8 qos, __be16 vlan_proto);
पूर्णांक i40e_nकरो_set_vf_bw(काष्ठा net_device *netdev, पूर्णांक vf_id, पूर्णांक min_tx_rate,
		       पूर्णांक max_tx_rate);
पूर्णांक i40e_nकरो_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf_id, bool setting);
पूर्णांक i40e_nकरो_get_vf_config(काष्ठा net_device *netdev,
			   पूर्णांक vf_id, काष्ठा अगरla_vf_info *ivi);
पूर्णांक i40e_nकरो_set_vf_link_state(काष्ठा net_device *netdev, पूर्णांक vf_id, पूर्णांक link);
पूर्णांक i40e_nकरो_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf_id, bool enable);

व्योम i40e_vc_notअगरy_link_state(काष्ठा i40e_pf *pf);
व्योम i40e_vc_notअगरy_reset(काष्ठा i40e_pf *pf);
पूर्णांक i40e_get_vf_stats(काष्ठा net_device *netdev, पूर्णांक vf_id,
		      काष्ठा अगरla_vf_stats *vf_stats);

#पूर्ण_अगर /* _I40E_VIRTCHNL_PF_H_ */
