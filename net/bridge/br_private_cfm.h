<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */

#अगर_अघोषित _BR_PRIVATE_CFM_H_
#घोषणा _BR_PRIVATE_CFM_H_

#समावेश "br_private.h"
#समावेश <uapi/linux/cfm_bridge.h>

काष्ठा br_cfm_mep_create अणु
	क्रमागत br_cfm_करोमुख्य करोमुख्य; /* Doमुख्य क्रम this MEP */
	क्रमागत br_cfm_mep_direction direction; /* Up or Down MEP direction */
	u32 अगरindex; /* Residence port */
पूर्ण;

पूर्णांक br_cfm_mep_create(काष्ठा net_bridge *br,
		      स्थिर u32 instance,
		      काष्ठा br_cfm_mep_create *स्थिर create,
		      काष्ठा netlink_ext_ack *extack);

पूर्णांक br_cfm_mep_delete(काष्ठा net_bridge *br,
		      स्थिर u32 instance,
		      काष्ठा netlink_ext_ack *extack);

काष्ठा br_cfm_mep_config अणु
	u32 mdlevel;
	u32 mepid; /* MEPID क्रम this MEP */
	काष्ठा mac_addr unicast_mac; /* The MEP unicast MAC */
पूर्ण;

पूर्णांक br_cfm_mep_config_set(काष्ठा net_bridge *br,
			  स्थिर u32 instance,
			  स्थिर काष्ठा br_cfm_mep_config *स्थिर config,
			  काष्ठा netlink_ext_ack *extack);

काष्ठा br_cfm_maid अणु
	u8 data[CFM_MAID_LENGTH];
पूर्ण;

काष्ठा br_cfm_cc_config अणु
	/* Expected received CCM PDU MAID. */
	काष्ठा br_cfm_maid exp_maid;

	/* Expected received CCM PDU पूर्णांकerval. */
	/* Transmitting CCM PDU पूर्णांकerval when CCM tx is enabled. */
	क्रमागत br_cfm_ccm_पूर्णांकerval exp_पूर्णांकerval;

	bool enable; /* Enable/disable CCM PDU handling */
पूर्ण;

पूर्णांक br_cfm_cc_config_set(काष्ठा net_bridge *br,
			 स्थिर u32 instance,
			 स्थिर काष्ठा br_cfm_cc_config *स्थिर config,
			 काष्ठा netlink_ext_ack *extack);

पूर्णांक br_cfm_cc_peer_mep_add(काष्ठा net_bridge *br, स्थिर u32 instance,
			   u32 peer_mep_id,
			   काष्ठा netlink_ext_ack *extack);
पूर्णांक br_cfm_cc_peer_mep_हटाओ(काष्ठा net_bridge *br, स्थिर u32 instance,
			      u32 peer_mep_id,
			      काष्ठा netlink_ext_ack *extack);

/* Transmitted CCM Remote Defect Indication status set.
 * This RDI is inserted in transmitted CCM PDUs अगर CCM transmission is enabled.
 * See br_cfm_cc_ccm_tx() with पूर्णांकerval != BR_CFM_CCM_INTERVAL_NONE
 */
पूर्णांक br_cfm_cc_rdi_set(काष्ठा net_bridge *br, स्थिर u32 instance,
		      स्थिर bool rdi, काष्ठा netlink_ext_ack *extack);

/* OAM PDU Tx inक्रमmation */
काष्ठा br_cfm_cc_ccm_tx_info अणु
	काष्ठा mac_addr dmac;
	/* The CCM will be transmitted क्रम this period in seconds.
	 * Call br_cfm_cc_ccm_tx beक्रमe समयout to keep transmission alive.
	 * When period is zero any ongoing transmission will be stopped.
	 */
	u32 period;

	bool seq_no_update; /* Update Tx CCM sequence number */
	bool अगर_tlv; /* Insert Interface Status TLV */
	u8 अगर_tlv_value; /* Interface Status TLV value */
	bool port_tlv; /* Insert Port Status TLV */
	u8 port_tlv_value; /* Port Status TLV value */
	/* Sender ID TLV ??
	 * Organization-Specअगरic TLV ??
	 */
पूर्ण;

पूर्णांक br_cfm_cc_ccm_tx(काष्ठा net_bridge *br, स्थिर u32 instance,
		     स्थिर काष्ठा br_cfm_cc_ccm_tx_info *स्थिर tx_info,
		     काष्ठा netlink_ext_ack *extack);

काष्ठा br_cfm_mep_status अणु
	/* Indications that an OAM PDU has been seen. */
	bool opcode_unexp_seen; /* RX of OAM PDU with unexpected opcode */
	bool version_unexp_seen; /* RX of OAM PDU with unexpected version */
	bool rx_level_low_seen; /* Rx of OAM PDU with level low */
पूर्ण;

काष्ठा br_cfm_cc_peer_status अणु
	/* This CCM related status is based on the latest received CCM PDU. */
	u8 port_tlv_value; /* Port Status TLV value */
	u8 अगर_tlv_value; /* Interface Status TLV value */

	/* CCM has not been received क्रम 3.25 पूर्णांकervals */
	u8 ccm_defect:1;

	/* (RDI == 1) क्रम last received CCM PDU */
	u8 rdi:1;

	/* Indications that a CCM PDU has been seen. */
	u8 seen:1; /* CCM PDU received */
	u8 tlv_seen:1; /* CCM PDU with TLV received */
	/* CCM PDU with unexpected sequence number received */
	u8 seq_unexp_seen:1;
पूर्ण;

काष्ठा br_cfm_mep अणु
	/* list header of MEP instances */
	काष्ठा hlist_node		head;
	u32				instance;
	काष्ठा br_cfm_mep_create	create;
	काष्ठा br_cfm_mep_config	config;
	काष्ठा br_cfm_cc_config		cc_config;
	काष्ठा br_cfm_cc_ccm_tx_info	cc_ccm_tx_info;
	/* List of multiple peer MEPs */
	काष्ठा hlist_head		peer_mep_list;
	काष्ठा net_bridge_port __rcu	*b_port;
	अचिन्हित दीर्घ			ccm_tx_end;
	काष्ठा delayed_work		ccm_tx_dwork;
	u32				ccm_tx_snumber;
	u32				ccm_rx_snumber;
	काष्ठा br_cfm_mep_status	status;
	bool				rdi;
	काष्ठा rcu_head			rcu;
पूर्ण;

काष्ठा br_cfm_peer_mep अणु
	काष्ठा hlist_node		head;
	काष्ठा br_cfm_mep		*mep;
	काष्ठा delayed_work		ccm_rx_dwork;
	u32				mepid;
	काष्ठा br_cfm_cc_peer_status	cc_status;
	u32				ccm_rx_count_miss;
	काष्ठा rcu_head			rcu;
पूर्ण;

#पूर्ण_अगर /* _BR_PRIVATE_CFM_H_ */
