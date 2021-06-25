<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dcbnl.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश "qed.h"
#समावेश "qed_cxt.h"
#समावेश "qed_dcbx.h"
#समावेश "qed_hsi.h"
#समावेश "qed_sp.h"
#समावेश "qed_sriov.h"
#समावेश "qed_rdma.h"
#अगर_घोषित CONFIG_DCB
#समावेश <linux/qed/qed_eth_अगर.h>
#पूर्ण_अगर

#घोषणा QED_DCBX_MAX_MIB_READ_TRY       (100)
#घोषणा QED_ETH_TYPE_DEFAULT            (0)
#घोषणा QED_ETH_TYPE_ROCE               (0x8915)
#घोषणा QED_UDP_PORT_TYPE_ROCE_V2       (0x12B7)
#घोषणा QED_ETH_TYPE_FCOE               (0x8906)
#घोषणा QED_TCP_PORT_ISCSI              (0xCBC)

#घोषणा QED_DCBX_INVALID_PRIORITY       0xFF

/* Get Traffic Class from priority traffic class table, 4 bits represent
 * the traffic class corresponding to the priority.
 */
#घोषणा QED_DCBX_PRIO2TC(prio_tc_tbl, prio) \
	((u32)(prio_tc_tbl >> ((7 - prio) * 4)) & 0x7)

अटल स्थिर काष्ठा qed_dcbx_app_metadata qed_dcbx_app_update[] = अणु
	अणुDCBX_PROTOCOL_ISCSI, "ISCSI", QED_PCI_ISCSIपूर्ण,
	अणुDCBX_PROTOCOL_FCOE, "FCOE", QED_PCI_FCOEपूर्ण,
	अणुDCBX_PROTOCOL_ROCE, "ROCE", QED_PCI_ETH_ROCEपूर्ण,
	अणुDCBX_PROTOCOL_ROCE_V2, "ROCE_V2", QED_PCI_ETH_ROCEपूर्ण,
	अणुDCBX_PROTOCOL_ETH, "ETH", QED_PCI_ETHपूर्ण,
पूर्ण;

अटल bool qed_dcbx_app_ethtype(u32 app_info_biपंचांगap)
अणु
	वापस !!(QED_MFW_GET_FIELD(app_info_biपंचांगap, DCBX_APP_SF) ==
		  DCBX_APP_SF_ETHTYPE);
पूर्ण

अटल bool qed_dcbx_ieee_app_ethtype(u32 app_info_biपंचांगap)
अणु
	u8 mfw_val = QED_MFW_GET_FIELD(app_info_biपंचांगap, DCBX_APP_SF_IEEE);

	/* Old MFW */
	अगर (mfw_val == DCBX_APP_SF_IEEE_RESERVED)
		वापस qed_dcbx_app_ethtype(app_info_biपंचांगap);

	वापस !!(mfw_val == DCBX_APP_SF_IEEE_ETHTYPE);
पूर्ण

अटल bool qed_dcbx_app_port(u32 app_info_biपंचांगap)
अणु
	वापस !!(QED_MFW_GET_FIELD(app_info_biपंचांगap, DCBX_APP_SF) ==
		  DCBX_APP_SF_PORT);
पूर्ण

अटल bool qed_dcbx_ieee_app_port(u32 app_info_biपंचांगap, u8 type)
अणु
	u8 mfw_val = QED_MFW_GET_FIELD(app_info_biपंचांगap, DCBX_APP_SF_IEEE);

	/* Old MFW */
	अगर (mfw_val == DCBX_APP_SF_IEEE_RESERVED)
		वापस qed_dcbx_app_port(app_info_biपंचांगap);

	वापस !!(mfw_val == type || mfw_val == DCBX_APP_SF_IEEE_TCP_UDP_PORT);
पूर्ण

अटल bool qed_dcbx_शेष_tlv(u32 app_info_biपंचांगap, u16 proto_id, bool ieee)
अणु
	bool ethtype;

	अगर (ieee)
		ethtype = qed_dcbx_ieee_app_ethtype(app_info_biपंचांगap);
	अन्यथा
		ethtype = qed_dcbx_app_ethtype(app_info_biपंचांगap);

	वापस !!(ethtype && (proto_id == QED_ETH_TYPE_DEFAULT));
पूर्ण

अटल bool qed_dcbx_iscsi_tlv(u32 app_info_biपंचांगap, u16 proto_id, bool ieee)
अणु
	bool port;

	अगर (ieee)
		port = qed_dcbx_ieee_app_port(app_info_biपंचांगap,
					      DCBX_APP_SF_IEEE_TCP_PORT);
	अन्यथा
		port = qed_dcbx_app_port(app_info_biपंचांगap);

	वापस !!(port && (proto_id == QED_TCP_PORT_ISCSI));
पूर्ण

अटल bool qed_dcbx_fcoe_tlv(u32 app_info_biपंचांगap, u16 proto_id, bool ieee)
अणु
	bool ethtype;

	अगर (ieee)
		ethtype = qed_dcbx_ieee_app_ethtype(app_info_biपंचांगap);
	अन्यथा
		ethtype = qed_dcbx_app_ethtype(app_info_biपंचांगap);

	वापस !!(ethtype && (proto_id == QED_ETH_TYPE_FCOE));
पूर्ण

अटल bool qed_dcbx_roce_tlv(u32 app_info_biपंचांगap, u16 proto_id, bool ieee)
अणु
	bool ethtype;

	अगर (ieee)
		ethtype = qed_dcbx_ieee_app_ethtype(app_info_biपंचांगap);
	अन्यथा
		ethtype = qed_dcbx_app_ethtype(app_info_biपंचांगap);

	वापस !!(ethtype && (proto_id == QED_ETH_TYPE_ROCE));
पूर्ण

अटल bool qed_dcbx_roce_v2_tlv(u32 app_info_biपंचांगap, u16 proto_id, bool ieee)
अणु
	bool port;

	अगर (ieee)
		port = qed_dcbx_ieee_app_port(app_info_biपंचांगap,
					      DCBX_APP_SF_IEEE_UDP_PORT);
	अन्यथा
		port = qed_dcbx_app_port(app_info_biपंचांगap);

	वापस !!(port && (proto_id == QED_UDP_PORT_TYPE_ROCE_V2));
पूर्ण

अटल व्योम
qed_dcbx_dp_protocol(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_dcbx_results *p_data)
अणु
	क्रमागत dcbx_protocol_type id;
	पूर्णांक i;

	DP_VERBOSE(p_hwfn, QED_MSG_DCB, "DCBX negotiated: %d\n",
		   p_data->dcbx_enabled);

	क्रम (i = 0; i < ARRAY_SIZE(qed_dcbx_app_update); i++) अणु
		id = qed_dcbx_app_update[i].id;

		DP_VERBOSE(p_hwfn, QED_MSG_DCB,
			   "%s info: update %d, enable %d, prio %d, tc %d, num_tc %d\n",
			   qed_dcbx_app_update[i].name, p_data->arr[id].update,
			   p_data->arr[id].enable, p_data->arr[id].priority,
			   p_data->arr[id].tc, p_hwfn->hw_info.num_active_tc);
	पूर्ण
पूर्ण

अटल व्योम
qed_dcbx_set_params(काष्ठा qed_dcbx_results *p_data,
		    काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
		    bool app_tlv, bool enable, u8 prio, u8 tc,
		    क्रमागत dcbx_protocol_type type,
		    क्रमागत qed_pci_personality personality)
अणु
	/* PF update ramrod data */
	p_data->arr[type].enable = enable;
	p_data->arr[type].priority = prio;
	p_data->arr[type].tc = tc;
	अगर (enable)
		p_data->arr[type].update = UPDATE_DCB;
	अन्यथा
		p_data->arr[type].update = DONT_UPDATE_DCB_DSCP;

	अगर (test_bit(QED_MF_DONT_ADD_VLAN0_TAG, &p_hwfn->cdev->mf_bits))
		p_data->arr[type].करोnt_add_vlan0 = true;

	/* QM reconf data */
	अगर (app_tlv && p_hwfn->hw_info.personality == personality)
		qed_hw_info_set_offload_tc(&p_hwfn->hw_info, tc);

	/* Configure dcbx vlan priority in करोorbell block क्रम roce EDPM */
	अगर (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits) &&
	    type == DCBX_PROTOCOL_ROCE) अणु
		qed_wr(p_hwfn, p_ptt, DORQ_REG_TAG1_OVRD_MODE, 1);
		qed_wr(p_hwfn, p_ptt, DORQ_REG_PF_PCP_BB_K2, prio << 1);
	पूर्ण
पूर्ण

/* Update app protocol data and hw_info fields with the TLV info */
अटल व्योम
qed_dcbx_update_app_info(काष्ठा qed_dcbx_results *p_data,
			 काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			 bool app_tlv, bool enable, u8 prio, u8 tc,
			 क्रमागत dcbx_protocol_type type)
अणु
	क्रमागत qed_pci_personality personality;
	क्रमागत dcbx_protocol_type id;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(qed_dcbx_app_update); i++) अणु
		id = qed_dcbx_app_update[i].id;

		अगर (type != id)
			जारी;

		personality = qed_dcbx_app_update[i].personality;

		qed_dcbx_set_params(p_data, p_hwfn, p_ptt, app_tlv, enable,
				    prio, tc, type, personality);
	पूर्ण
पूर्ण

अटल bool
qed_dcbx_get_app_protocol_type(काष्ठा qed_hwfn *p_hwfn,
			       u32 app_prio_biपंचांगap,
			       u16 id, क्रमागत dcbx_protocol_type *type, bool ieee)
अणु
	अगर (qed_dcbx_fcoe_tlv(app_prio_biपंचांगap, id, ieee)) अणु
		*type = DCBX_PROTOCOL_FCOE;
	पूर्ण अन्यथा अगर (qed_dcbx_roce_tlv(app_prio_biपंचांगap, id, ieee)) अणु
		*type = DCBX_PROTOCOL_ROCE;
	पूर्ण अन्यथा अगर (qed_dcbx_iscsi_tlv(app_prio_biपंचांगap, id, ieee)) अणु
		*type = DCBX_PROTOCOL_ISCSI;
	पूर्ण अन्यथा अगर (qed_dcbx_शेष_tlv(app_prio_biपंचांगap, id, ieee)) अणु
		*type = DCBX_PROTOCOL_ETH;
	पूर्ण अन्यथा अगर (qed_dcbx_roce_v2_tlv(app_prio_biपंचांगap, id, ieee)) अणु
		*type = DCBX_PROTOCOL_ROCE_V2;
	पूर्ण अन्यथा अणु
		*type = DCBX_MAX_PROTOCOL_TYPE;
		DP_VERBOSE(p_hwfn, QED_MSG_DCB,
			   "No action required, App TLV entry = 0x%x\n",
			   app_prio_biपंचांगap);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Parse app TLV's to update TC inक्रमmation in hw_info काष्ठाure क्रम
 * reconfiguring QM. Get protocol specअगरic data क्रम PF update ramrod command.
 */
अटल पूर्णांक
qed_dcbx_process_tlv(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
		     काष्ठा qed_dcbx_results *p_data,
		     काष्ठा dcbx_app_priority_entry *p_tbl,
		     u32 pri_tc_tbl, पूर्णांक count, u8 dcbx_version)
अणु
	क्रमागत dcbx_protocol_type type;
	bool enable, ieee, eth_tlv;
	u8 tc, priority_map;
	u16 protocol_id;
	पूर्णांक priority;
	पूर्णांक i;

	DP_VERBOSE(p_hwfn, QED_MSG_DCB, "Num APP entries = %d\n", count);

	ieee = (dcbx_version == DCBX_CONFIG_VERSION_IEEE);
	eth_tlv = false;
	/* Parse APP TLV */
	क्रम (i = 0; i < count; i++) अणु
		protocol_id = QED_MFW_GET_FIELD(p_tbl[i].entry,
						DCBX_APP_PROTOCOL_ID);
		priority_map = QED_MFW_GET_FIELD(p_tbl[i].entry,
						 DCBX_APP_PRI_MAP);
		priority = ffs(priority_map) - 1;
		अगर (priority < 0) अणु
			DP_ERR(p_hwfn, "Invalid priority\n");
			वापस -EINVAL;
		पूर्ण

		tc = QED_DCBX_PRIO2TC(pri_tc_tbl, priority);
		अगर (qed_dcbx_get_app_protocol_type(p_hwfn, p_tbl[i].entry,
						   protocol_id, &type, ieee)) अणु
			/* ETH always have the enable bit reset, as it माला_लो
			 * vlan inक्रमmation per packet. For other protocols,
			 * should be set according to the dcbx_enabled
			 * indication, but we only got here अगर there was an
			 * app tlv क्रम the protocol, so dcbx must be enabled.
			 */
			अगर (type == DCBX_PROTOCOL_ETH) अणु
				enable = false;
				eth_tlv = true;
			पूर्ण अन्यथा अणु
				enable = true;
			पूर्ण

			qed_dcbx_update_app_info(p_data, p_hwfn, p_ptt, true,
						 enable, priority, tc, type);
		पूर्ण
	पूर्ण

	/* If Eth TLV is not detected, use UFP TC as शेष TC */
	अगर (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits) && !eth_tlv)
		p_data->arr[DCBX_PROTOCOL_ETH].tc = p_hwfn->ufp_info.tc;

	/* Update ramrod protocol data and hw_info fields
	 * with शेष info when corresponding APP TLV's are not detected.
	 * The enabled field has a dअगरferent logic क्रम ethernet as only क्रम
	 * ethernet dcb should disabled by शेष, as the inक्रमmation arrives
	 * from the OS (unless an explicit app tlv was present).
	 */
	tc = p_data->arr[DCBX_PROTOCOL_ETH].tc;
	priority = p_data->arr[DCBX_PROTOCOL_ETH].priority;
	क्रम (type = 0; type < DCBX_MAX_PROTOCOL_TYPE; type++) अणु
		अगर (p_data->arr[type].update)
			जारी;

		enable = (type == DCBX_PROTOCOL_ETH) ? false : !!dcbx_version;
		qed_dcbx_update_app_info(p_data, p_hwfn, p_ptt, false, enable,
					 priority, tc, type);
	पूर्ण

	वापस 0;
पूर्ण

/* Parse app TLV's to update TC inक्रमmation in hw_info काष्ठाure क्रम
 * reconfiguring QM. Get protocol specअगरic data क्रम PF update ramrod command.
 */
अटल पूर्णांक
qed_dcbx_process_mib_info(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा dcbx_app_priority_feature *p_app;
	काष्ठा dcbx_app_priority_entry *p_tbl;
	काष्ठा qed_dcbx_results data = अणु 0 पूर्ण;
	काष्ठा dcbx_ets_feature *p_ets;
	काष्ठा qed_hw_info *p_info;
	u32 pri_tc_tbl, flags;
	u8 dcbx_version;
	पूर्णांक num_entries;
	पूर्णांक rc = 0;

	flags = p_hwfn->p_dcbx_info->operational.flags;
	dcbx_version = QED_MFW_GET_FIELD(flags, DCBX_CONFIG_VERSION);

	p_app = &p_hwfn->p_dcbx_info->operational.features.app;
	p_tbl = p_app->app_pri_tbl;

	p_ets = &p_hwfn->p_dcbx_info->operational.features.ets;
	pri_tc_tbl = p_ets->pri_tc_tbl[0];

	p_info = &p_hwfn->hw_info;
	num_entries = QED_MFW_GET_FIELD(p_app->flags, DCBX_APP_NUM_ENTRIES);

	rc = qed_dcbx_process_tlv(p_hwfn, p_ptt, &data, p_tbl, pri_tc_tbl,
				  num_entries, dcbx_version);
	अगर (rc)
		वापस rc;

	p_info->num_active_tc = QED_MFW_GET_FIELD(p_ets->flags,
						  DCBX_ETS_MAX_TCS);
	p_hwfn->qm_info.ooo_tc = QED_MFW_GET_FIELD(p_ets->flags, DCBX_OOO_TC);
	data.pf_id = p_hwfn->rel_pf_id;
	data.dcbx_enabled = !!dcbx_version;

	qed_dcbx_dp_protocol(p_hwfn, &data);

	स_नकल(&p_hwfn->p_dcbx_info->results, &data,
	       माप(काष्ठा qed_dcbx_results));

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_dcbx_copy_mib(काष्ठा qed_hwfn *p_hwfn,
		  काष्ठा qed_ptt *p_ptt,
		  काष्ठा qed_dcbx_mib_meta_data *p_data,
		  क्रमागत qed_mib_पढ़ो_type type)
अणु
	u32 prefix_seq_num, suffix_seq_num;
	पूर्णांक पढ़ो_count = 0;
	पूर्णांक rc = 0;

	/* The data is considered to be valid only अगर both sequence numbers are
	 * the same.
	 */
	करो अणु
		अगर (type == QED_DCBX_REMOTE_LLDP_MIB) अणु
			qed_स_नकल_from(p_hwfn, p_ptt, p_data->lldp_remote,
					p_data->addr, p_data->size);
			prefix_seq_num = p_data->lldp_remote->prefix_seq_num;
			suffix_seq_num = p_data->lldp_remote->suffix_seq_num;
		पूर्ण अन्यथा अणु
			qed_स_नकल_from(p_hwfn, p_ptt, p_data->mib,
					p_data->addr, p_data->size);
			prefix_seq_num = p_data->mib->prefix_seq_num;
			suffix_seq_num = p_data->mib->suffix_seq_num;
		पूर्ण
		पढ़ो_count++;

		DP_VERBOSE(p_hwfn,
			   QED_MSG_DCB,
			   "mib type = %d, try count = %d prefix seq num  = %d suffix seq num = %d\n",
			   type, पढ़ो_count, prefix_seq_num, suffix_seq_num);
	पूर्ण जबतक ((prefix_seq_num != suffix_seq_num) &&
		 (पढ़ो_count < QED_DCBX_MAX_MIB_READ_TRY));

	अगर (पढ़ो_count >= QED_DCBX_MAX_MIB_READ_TRY) अणु
		DP_ERR(p_hwfn,
		       "MIB read err, mib type = %d, try count = %d prefix seq num = %d suffix seq num = %d\n",
		       type, पढ़ो_count, prefix_seq_num, suffix_seq_num);
		rc = -EIO;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम
qed_dcbx_get_priority_info(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_dcbx_app_prio *p_prio,
			   काष्ठा qed_dcbx_results *p_results)
अणु
	u8 val;

	p_prio->roce = QED_DCBX_INVALID_PRIORITY;
	p_prio->roce_v2 = QED_DCBX_INVALID_PRIORITY;
	p_prio->iscsi = QED_DCBX_INVALID_PRIORITY;
	p_prio->fcoe = QED_DCBX_INVALID_PRIORITY;

	अगर (p_results->arr[DCBX_PROTOCOL_ROCE].update &&
	    p_results->arr[DCBX_PROTOCOL_ROCE].enable)
		p_prio->roce = p_results->arr[DCBX_PROTOCOL_ROCE].priority;

	अगर (p_results->arr[DCBX_PROTOCOL_ROCE_V2].update &&
	    p_results->arr[DCBX_PROTOCOL_ROCE_V2].enable) अणु
		val = p_results->arr[DCBX_PROTOCOL_ROCE_V2].priority;
		p_prio->roce_v2 = val;
	पूर्ण

	अगर (p_results->arr[DCBX_PROTOCOL_ISCSI].update &&
	    p_results->arr[DCBX_PROTOCOL_ISCSI].enable)
		p_prio->iscsi = p_results->arr[DCBX_PROTOCOL_ISCSI].priority;

	अगर (p_results->arr[DCBX_PROTOCOL_FCOE].update &&
	    p_results->arr[DCBX_PROTOCOL_FCOE].enable)
		p_prio->fcoe = p_results->arr[DCBX_PROTOCOL_FCOE].priority;

	अगर (p_results->arr[DCBX_PROTOCOL_ETH].update &&
	    p_results->arr[DCBX_PROTOCOL_ETH].enable)
		p_prio->eth = p_results->arr[DCBX_PROTOCOL_ETH].priority;

	DP_VERBOSE(p_hwfn, QED_MSG_DCB,
		   "Priorities: iscsi %d, roce %d, roce v2 %d, fcoe %d, eth %d\n",
		   p_prio->iscsi, p_prio->roce, p_prio->roce_v2, p_prio->fcoe,
		   p_prio->eth);
पूर्ण

अटल व्योम
qed_dcbx_get_app_data(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा dcbx_app_priority_feature *p_app,
		      काष्ठा dcbx_app_priority_entry *p_tbl,
		      काष्ठा qed_dcbx_params *p_params, bool ieee)
अणु
	काष्ठा qed_app_entry *entry;
	u8 pri_map;
	पूर्णांक i;

	p_params->app_willing = QED_MFW_GET_FIELD(p_app->flags,
						  DCBX_APP_WILLING);
	p_params->app_valid = QED_MFW_GET_FIELD(p_app->flags, DCBX_APP_ENABLED);
	p_params->app_error = QED_MFW_GET_FIELD(p_app->flags, DCBX_APP_ERROR);
	p_params->num_app_entries = QED_MFW_GET_FIELD(p_app->flags,
						      DCBX_APP_NUM_ENTRIES);
	क्रम (i = 0; i < DCBX_MAX_APP_PROTOCOL; i++) अणु
		entry = &p_params->app_entry[i];
		अगर (ieee) अणु
			u8 sf_ieee;
			u32 val;

			sf_ieee = QED_MFW_GET_FIELD(p_tbl[i].entry,
						    DCBX_APP_SF_IEEE);
			चयन (sf_ieee) अणु
			हाल DCBX_APP_SF_IEEE_RESERVED:
				/* Old MFW */
				val = QED_MFW_GET_FIELD(p_tbl[i].entry,
							DCBX_APP_SF);
				entry->sf_ieee = val ?
				    QED_DCBX_SF_IEEE_TCP_UDP_PORT :
				    QED_DCBX_SF_IEEE_ETHTYPE;
				अवरोध;
			हाल DCBX_APP_SF_IEEE_ETHTYPE:
				entry->sf_ieee = QED_DCBX_SF_IEEE_ETHTYPE;
				अवरोध;
			हाल DCBX_APP_SF_IEEE_TCP_PORT:
				entry->sf_ieee = QED_DCBX_SF_IEEE_TCP_PORT;
				अवरोध;
			हाल DCBX_APP_SF_IEEE_UDP_PORT:
				entry->sf_ieee = QED_DCBX_SF_IEEE_UDP_PORT;
				अवरोध;
			हाल DCBX_APP_SF_IEEE_TCP_UDP_PORT:
				entry->sf_ieee = QED_DCBX_SF_IEEE_TCP_UDP_PORT;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			entry->ethtype = !(QED_MFW_GET_FIELD(p_tbl[i].entry,
							     DCBX_APP_SF));
		पूर्ण

		pri_map = QED_MFW_GET_FIELD(p_tbl[i].entry, DCBX_APP_PRI_MAP);
		entry->prio = ffs(pri_map) - 1;
		entry->proto_id = QED_MFW_GET_FIELD(p_tbl[i].entry,
						    DCBX_APP_PROTOCOL_ID);
		qed_dcbx_get_app_protocol_type(p_hwfn, p_tbl[i].entry,
					       entry->proto_id,
					       &entry->proto_type, ieee);
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_DCB,
		   "APP params: willing %d, valid %d error = %d\n",
		   p_params->app_willing, p_params->app_valid,
		   p_params->app_error);
पूर्ण

अटल व्योम
qed_dcbx_get_pfc_data(काष्ठा qed_hwfn *p_hwfn,
		      u32 pfc, काष्ठा qed_dcbx_params *p_params)
अणु
	u8 pfc_map;

	p_params->pfc.willing = QED_MFW_GET_FIELD(pfc, DCBX_PFC_WILLING);
	p_params->pfc.max_tc = QED_MFW_GET_FIELD(pfc, DCBX_PFC_CAPS);
	p_params->pfc.enabled = QED_MFW_GET_FIELD(pfc, DCBX_PFC_ENABLED);
	pfc_map = QED_MFW_GET_FIELD(pfc, DCBX_PFC_PRI_EN_BITMAP);
	p_params->pfc.prio[0] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_0);
	p_params->pfc.prio[1] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_1);
	p_params->pfc.prio[2] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_2);
	p_params->pfc.prio[3] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_3);
	p_params->pfc.prio[4] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_4);
	p_params->pfc.prio[5] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_5);
	p_params->pfc.prio[6] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_6);
	p_params->pfc.prio[7] = !!(pfc_map & DCBX_PFC_PRI_EN_BITMAP_PRI_7);

	DP_VERBOSE(p_hwfn, QED_MSG_DCB,
		   "PFC params: willing %d, pfc_bitmap %u max_tc = %u enabled = %d\n",
		   p_params->pfc.willing, pfc_map, p_params->pfc.max_tc,
		   p_params->pfc.enabled);
पूर्ण

अटल व्योम
qed_dcbx_get_ets_data(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा dcbx_ets_feature *p_ets,
		      काष्ठा qed_dcbx_params *p_params)
अणु
	__be32 bw_map[2], tsa_map[2];
	u32 pri_map;
	पूर्णांक i;

	p_params->ets_willing = QED_MFW_GET_FIELD(p_ets->flags,
						  DCBX_ETS_WILLING);
	p_params->ets_enabled = QED_MFW_GET_FIELD(p_ets->flags,
						  DCBX_ETS_ENABLED);
	p_params->ets_cbs = QED_MFW_GET_FIELD(p_ets->flags, DCBX_ETS_CBS);
	p_params->max_ets_tc = QED_MFW_GET_FIELD(p_ets->flags,
						 DCBX_ETS_MAX_TCS);
	DP_VERBOSE(p_hwfn, QED_MSG_DCB,
		   "ETS params: willing %d, enabled = %d ets_cbs %d pri_tc_tbl_0 %x max_ets_tc %d\n",
		   p_params->ets_willing, p_params->ets_enabled,
		   p_params->ets_cbs, p_ets->pri_tc_tbl[0],
		   p_params->max_ets_tc);

	अगर (p_params->ets_enabled && !p_params->max_ets_tc) अणु
		p_params->max_ets_tc = QED_MAX_PFC_PRIORITIES;
		DP_VERBOSE(p_hwfn, QED_MSG_DCB,
			   "ETS params: max_ets_tc is forced to %d\n",
		p_params->max_ets_tc);
	पूर्ण

	/* 8 bit tsa and bw data corresponding to each of the 8 TC's are
	 * encoded in a type u32 array of size 2.
	 */
	cpu_to_be32_array(bw_map, p_ets->tc_bw_tbl, 2);
	cpu_to_be32_array(tsa_map, p_ets->tc_tsa_tbl, 2);
	pri_map = p_ets->pri_tc_tbl[0];

	क्रम (i = 0; i < QED_MAX_PFC_PRIORITIES; i++) अणु
		p_params->ets_tc_bw_tbl[i] = ((u8 *)bw_map)[i];
		p_params->ets_tc_tsa_tbl[i] = ((u8 *)tsa_map)[i];
		p_params->ets_pri_tc_tbl[i] = QED_DCBX_PRIO2TC(pri_map, i);
		DP_VERBOSE(p_hwfn, QED_MSG_DCB,
			   "elem %d  bw_tbl %x tsa_tbl %x\n",
			   i, p_params->ets_tc_bw_tbl[i],
			   p_params->ets_tc_tsa_tbl[i]);
	पूर्ण
पूर्ण

अटल व्योम
qed_dcbx_get_common_params(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा dcbx_app_priority_feature *p_app,
			   काष्ठा dcbx_app_priority_entry *p_tbl,
			   काष्ठा dcbx_ets_feature *p_ets,
			   u32 pfc, काष्ठा qed_dcbx_params *p_params, bool ieee)
अणु
	qed_dcbx_get_app_data(p_hwfn, p_app, p_tbl, p_params, ieee);
	qed_dcbx_get_ets_data(p_hwfn, p_ets, p_params);
	qed_dcbx_get_pfc_data(p_hwfn, pfc, p_params);
पूर्ण

अटल व्योम
qed_dcbx_get_local_params(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_dcbx_get *params)
अणु
	काष्ठा dcbx_features *p_feat;

	p_feat = &p_hwfn->p_dcbx_info->local_admin.features;
	qed_dcbx_get_common_params(p_hwfn, &p_feat->app,
				   p_feat->app.app_pri_tbl, &p_feat->ets,
				   p_feat->pfc, &params->local.params, false);
	params->local.valid = true;
पूर्ण

अटल व्योम
qed_dcbx_get_remote_params(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_dcbx_get *params)
अणु
	काष्ठा dcbx_features *p_feat;

	p_feat = &p_hwfn->p_dcbx_info->remote.features;
	qed_dcbx_get_common_params(p_hwfn, &p_feat->app,
				   p_feat->app.app_pri_tbl, &p_feat->ets,
				   p_feat->pfc, &params->remote.params, false);
	params->remote.valid = true;
पूर्ण

अटल व्योम
qed_dcbx_get_operational_params(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_dcbx_get *params)
अणु
	काष्ठा qed_dcbx_operational_params *p_operational;
	काष्ठा qed_dcbx_results *p_results;
	काष्ठा dcbx_features *p_feat;
	bool enabled, err;
	u32 flags;
	bool val;

	flags = p_hwfn->p_dcbx_info->operational.flags;

	/* If DCBx version is non zero, then negotiation
	 * was successfuly perक्रमmed
	 */
	p_operational = &params->operational;
	enabled = !!(QED_MFW_GET_FIELD(flags, DCBX_CONFIG_VERSION) !=
		     DCBX_CONFIG_VERSION_DISABLED);
	अगर (!enabled) अणु
		p_operational->enabled = enabled;
		p_operational->valid = false;
		DP_VERBOSE(p_hwfn, QED_MSG_DCB, "Dcbx is disabled\n");
		वापस;
	पूर्ण

	p_feat = &p_hwfn->p_dcbx_info->operational.features;
	p_results = &p_hwfn->p_dcbx_info->results;

	val = !!(QED_MFW_GET_FIELD(flags, DCBX_CONFIG_VERSION) ==
		 DCBX_CONFIG_VERSION_IEEE);
	p_operational->ieee = val;
	val = !!(QED_MFW_GET_FIELD(flags, DCBX_CONFIG_VERSION) ==
		 DCBX_CONFIG_VERSION_CEE);
	p_operational->cee = val;

	val = !!(QED_MFW_GET_FIELD(flags, DCBX_CONFIG_VERSION) ==
		 DCBX_CONFIG_VERSION_STATIC);
	p_operational->local = val;

	DP_VERBOSE(p_hwfn, QED_MSG_DCB,
		   "Version support: ieee %d, cee %d, static %d\n",
		   p_operational->ieee, p_operational->cee,
		   p_operational->local);

	qed_dcbx_get_common_params(p_hwfn, &p_feat->app,
				   p_feat->app.app_pri_tbl, &p_feat->ets,
				   p_feat->pfc, &params->operational.params,
				   p_operational->ieee);
	qed_dcbx_get_priority_info(p_hwfn, &p_operational->app_prio, p_results);
	err = QED_MFW_GET_FIELD(p_feat->app.flags, DCBX_APP_ERROR);
	p_operational->err = err;
	p_operational->enabled = enabled;
	p_operational->valid = true;
पूर्ण

अटल व्योम
qed_dcbx_get_local_lldp_params(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_dcbx_get *params)
अणु
	काष्ठा lldp_config_params_s *p_local;

	p_local = &p_hwfn->p_dcbx_info->lldp_local[LLDP_NEAREST_BRIDGE];

	स_नकल(params->lldp_local.local_chassis_id, p_local->local_chassis_id,
	       माप(p_local->local_chassis_id));
	स_नकल(params->lldp_local.local_port_id, p_local->local_port_id,
	       माप(p_local->local_port_id));
पूर्ण

अटल व्योम
qed_dcbx_get_remote_lldp_params(काष्ठा qed_hwfn *p_hwfn,
				काष्ठा qed_dcbx_get *params)
अणु
	काष्ठा lldp_status_params_s *p_remote;

	p_remote = &p_hwfn->p_dcbx_info->lldp_remote[LLDP_NEAREST_BRIDGE];

	स_नकल(params->lldp_remote.peer_chassis_id, p_remote->peer_chassis_id,
	       माप(p_remote->peer_chassis_id));
	स_नकल(params->lldp_remote.peer_port_id, p_remote->peer_port_id,
	       माप(p_remote->peer_port_id));
पूर्ण

अटल पूर्णांक
qed_dcbx_get_params(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_dcbx_get *p_params,
		    क्रमागत qed_mib_पढ़ो_type type)
अणु
	चयन (type) अणु
	हाल QED_DCBX_REMOTE_MIB:
		qed_dcbx_get_remote_params(p_hwfn, p_params);
		अवरोध;
	हाल QED_DCBX_LOCAL_MIB:
		qed_dcbx_get_local_params(p_hwfn, p_params);
		अवरोध;
	हाल QED_DCBX_OPERATIONAL_MIB:
		qed_dcbx_get_operational_params(p_hwfn, p_params);
		अवरोध;
	हाल QED_DCBX_REMOTE_LLDP_MIB:
		qed_dcbx_get_remote_lldp_params(p_hwfn, p_params);
		अवरोध;
	हाल QED_DCBX_LOCAL_LLDP_MIB:
		qed_dcbx_get_local_lldp_params(p_hwfn, p_params);
		अवरोध;
	शेष:
		DP_ERR(p_hwfn, "MIB read err, unknown mib type %d\n", type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qed_dcbx_पढ़ो_local_lldp_mib(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_dcbx_mib_meta_data data;
	पूर्णांक rc = 0;

	स_रखो(&data, 0, माप(data));
	data.addr = p_hwfn->mcp_info->port_addr + दुरत्व(काष्ठा खुला_port,
							   lldp_config_params);
	data.lldp_local = p_hwfn->p_dcbx_info->lldp_local;
	data.size = माप(काष्ठा lldp_config_params_s);
	qed_स_नकल_from(p_hwfn, p_ptt, data.lldp_local, data.addr, data.size);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_dcbx_पढ़ो_remote_lldp_mib(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt,
			      क्रमागत qed_mib_पढ़ो_type type)
अणु
	काष्ठा qed_dcbx_mib_meta_data data;
	पूर्णांक rc = 0;

	स_रखो(&data, 0, माप(data));
	data.addr = p_hwfn->mcp_info->port_addr + दुरत्व(काष्ठा खुला_port,
							   lldp_status_params);
	data.lldp_remote = p_hwfn->p_dcbx_info->lldp_remote;
	data.size = माप(काष्ठा lldp_status_params_s);
	rc = qed_dcbx_copy_mib(p_hwfn, p_ptt, &data, type);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_dcbx_पढ़ो_operational_mib(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt,
			      क्रमागत qed_mib_पढ़ो_type type)
अणु
	काष्ठा qed_dcbx_mib_meta_data data;
	पूर्णांक rc = 0;

	स_रखो(&data, 0, माप(data));
	data.addr = p_hwfn->mcp_info->port_addr +
		    दुरत्व(काष्ठा खुला_port, operational_dcbx_mib);
	data.mib = &p_hwfn->p_dcbx_info->operational;
	data.size = माप(काष्ठा dcbx_mib);
	rc = qed_dcbx_copy_mib(p_hwfn, p_ptt, &data, type);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_dcbx_पढ़ो_remote_mib(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_ptt *p_ptt, क्रमागत qed_mib_पढ़ो_type type)
अणु
	काष्ठा qed_dcbx_mib_meta_data data;
	पूर्णांक rc = 0;

	स_रखो(&data, 0, माप(data));
	data.addr = p_hwfn->mcp_info->port_addr +
		    दुरत्व(काष्ठा खुला_port, remote_dcbx_mib);
	data.mib = &p_hwfn->p_dcbx_info->remote;
	data.size = माप(काष्ठा dcbx_mib);
	rc = qed_dcbx_copy_mib(p_hwfn, p_ptt, &data, type);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_dcbx_पढ़ो_local_mib(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt)
अणु
	काष्ठा qed_dcbx_mib_meta_data data;
	पूर्णांक rc = 0;

	स_रखो(&data, 0, माप(data));
	data.addr = p_hwfn->mcp_info->port_addr +
		    दुरत्व(काष्ठा खुला_port, local_admin_dcbx_mib);
	data.local_admin = &p_hwfn->p_dcbx_info->local_admin;
	data.size = माप(काष्ठा dcbx_local_params);
	qed_स_नकल_from(p_hwfn, p_ptt, data.local_admin, data.addr, data.size);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_dcbx_पढ़ो_mib(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_ptt *p_ptt, क्रमागत qed_mib_पढ़ो_type type)
अणु
	पूर्णांक rc = -EINVAL;

	चयन (type) अणु
	हाल QED_DCBX_OPERATIONAL_MIB:
		rc = qed_dcbx_पढ़ो_operational_mib(p_hwfn, p_ptt, type);
		अवरोध;
	हाल QED_DCBX_REMOTE_MIB:
		rc = qed_dcbx_पढ़ो_remote_mib(p_hwfn, p_ptt, type);
		अवरोध;
	हाल QED_DCBX_LOCAL_MIB:
		rc = qed_dcbx_पढ़ो_local_mib(p_hwfn, p_ptt);
		अवरोध;
	हाल QED_DCBX_REMOTE_LLDP_MIB:
		rc = qed_dcbx_पढ़ो_remote_lldp_mib(p_hwfn, p_ptt, type);
		अवरोध;
	हाल QED_DCBX_LOCAL_LLDP_MIB:
		rc = qed_dcbx_पढ़ो_local_lldp_mib(p_hwfn, p_ptt);
		अवरोध;
	शेष:
		DP_ERR(p_hwfn, "MIB read err, unknown mib type %d\n", type);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम qed_dcbx_aen(काष्ठा qed_hwfn *hwfn, u32 mib_type)
अणु
	काष्ठा qed_common_cb_ops *op = hwfn->cdev->protocol_ops.common;
	व्योम *cookie = hwfn->cdev->ops_cookie;

	अगर (cookie && op->dcbx_aen)
		op->dcbx_aen(cookie, &hwfn->p_dcbx_info->get, mib_type);
पूर्ण

/* Read updated MIB.
 * Reconfigure QM and invoke PF update ramrod command अगर operational MIB
 * change is detected.
 */
पूर्णांक
qed_dcbx_mib_update_event(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, क्रमागत qed_mib_पढ़ो_type type)
अणु
	पूर्णांक rc = 0;

	rc = qed_dcbx_पढ़ो_mib(p_hwfn, p_ptt, type);
	अगर (rc)
		वापस rc;

	अगर (type == QED_DCBX_OPERATIONAL_MIB) अणु
		rc = qed_dcbx_process_mib_info(p_hwfn, p_ptt);
		अगर (!rc) अणु
			/* reconfigure tcs of QM queues according
			 * to negotiation results
			 */
			qed_qm_reconf(p_hwfn, p_ptt);

			/* update storm FW with negotiation results */
			qed_sp_pf_update(p_hwfn);

			/* क्रम roce PFs, we may want to enable/disable DPM
			 * when DCBx change occurs
			 */
			अगर (p_hwfn->hw_info.personality ==
			    QED_PCI_ETH_ROCE)
				qed_roce_dpm_dcbx(p_hwfn, p_ptt);
		पूर्ण
	पूर्ण

	qed_dcbx_get_params(p_hwfn, &p_hwfn->p_dcbx_info->get, type);

	अगर (type == QED_DCBX_OPERATIONAL_MIB) अणु
		काष्ठा qed_dcbx_results *p_data;
		u16 val;

		/* Configure in NIG which protocols support EDPM and should
		 * honor PFC.
		 */
		p_data = &p_hwfn->p_dcbx_info->results;
		val = (0x1 << p_data->arr[DCBX_PROTOCOL_ROCE].tc) |
		      (0x1 << p_data->arr[DCBX_PROTOCOL_ROCE_V2].tc);
		val <<= NIG_REG_TX_EDPM_CTRL_TX_EDPM_TC_EN_SHIFT;
		val |= NIG_REG_TX_EDPM_CTRL_TX_EDPM_EN;
		qed_wr(p_hwfn, p_ptt, NIG_REG_TX_EDPM_CTRL, val);
	पूर्ण

	qed_dcbx_aen(p_hwfn, type);

	वापस rc;
पूर्ण

पूर्णांक qed_dcbx_info_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	p_hwfn->p_dcbx_info = kzalloc(माप(*p_hwfn->p_dcbx_info), GFP_KERNEL);
	अगर (!p_hwfn->p_dcbx_info)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम qed_dcbx_info_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	kमुक्त(p_hwfn->p_dcbx_info);
	p_hwfn->p_dcbx_info = शून्य;
पूर्ण

अटल व्योम qed_dcbx_update_protocol_data(काष्ठा protocol_dcb_data *p_data,
					  काष्ठा qed_dcbx_results *p_src,
					  क्रमागत dcbx_protocol_type type)
अणु
	p_data->dcb_enable_flag = p_src->arr[type].enable;
	p_data->dcb_priority = p_src->arr[type].priority;
	p_data->dcb_tc = p_src->arr[type].tc;
	p_data->dcb_करोnt_add_vlan0 = p_src->arr[type].करोnt_add_vlan0;
पूर्ण

/* Set pf update ramrod command params */
व्योम qed_dcbx_set_pf_update_params(काष्ठा qed_dcbx_results *p_src,
				   काष्ठा pf_update_ramrod_data *p_dest)
अणु
	काष्ठा protocol_dcb_data *p_dcb_data;
	u8 update_flag;

	update_flag = p_src->arr[DCBX_PROTOCOL_FCOE].update;
	p_dest->update_fcoe_dcb_data_mode = update_flag;

	update_flag = p_src->arr[DCBX_PROTOCOL_ROCE].update;
	p_dest->update_roce_dcb_data_mode = update_flag;

	update_flag = p_src->arr[DCBX_PROTOCOL_ROCE_V2].update;
	p_dest->update_rroce_dcb_data_mode = update_flag;

	update_flag = p_src->arr[DCBX_PROTOCOL_ISCSI].update;
	p_dest->update_iscsi_dcb_data_mode = update_flag;
	update_flag = p_src->arr[DCBX_PROTOCOL_ETH].update;
	p_dest->update_eth_dcb_data_mode = update_flag;

	p_dcb_data = &p_dest->fcoe_dcb_data;
	qed_dcbx_update_protocol_data(p_dcb_data, p_src, DCBX_PROTOCOL_FCOE);
	p_dcb_data = &p_dest->roce_dcb_data;
	qed_dcbx_update_protocol_data(p_dcb_data, p_src, DCBX_PROTOCOL_ROCE);
	p_dcb_data = &p_dest->rroce_dcb_data;
	qed_dcbx_update_protocol_data(p_dcb_data, p_src, DCBX_PROTOCOL_ROCE_V2);
	p_dcb_data = &p_dest->iscsi_dcb_data;
	qed_dcbx_update_protocol_data(p_dcb_data, p_src, DCBX_PROTOCOL_ISCSI);
	p_dcb_data = &p_dest->eth_dcb_data;
	qed_dcbx_update_protocol_data(p_dcb_data, p_src, DCBX_PROTOCOL_ETH);
पूर्ण

u8 qed_dcbx_get_priority_tc(काष्ठा qed_hwfn *p_hwfn, u8 pri)
अणु
	काष्ठा qed_dcbx_get *dcbx_info = &p_hwfn->p_dcbx_info->get;

	अगर (pri >= QED_MAX_PFC_PRIORITIES) अणु
		DP_ERR(p_hwfn, "Invalid priority %d\n", pri);
		वापस QED_DCBX_DEFAULT_TC;
	पूर्ण

	अगर (!dcbx_info->operational.valid) अणु
		DP_VERBOSE(p_hwfn, QED_MSG_DCB,
			   "Dcbx parameters not available\n");
		वापस QED_DCBX_DEFAULT_TC;
	पूर्ण

	वापस dcbx_info->operational.params.ets_pri_tc_tbl[pri];
पूर्ण

#अगर_घोषित CONFIG_DCB
अटल पूर्णांक qed_dcbx_query_params(काष्ठा qed_hwfn *p_hwfn,
				 काष्ठा qed_dcbx_get *p_get,
				 क्रमागत qed_mib_पढ़ो_type type)
अणु
	काष्ठा qed_ptt *p_ptt;
	पूर्णांक rc;

	अगर (IS_VF(p_hwfn->cdev))
		वापस -EINVAL;

	p_ptt = qed_ptt_acquire(p_hwfn);
	अगर (!p_ptt)
		वापस -EBUSY;

	rc = qed_dcbx_पढ़ो_mib(p_hwfn, p_ptt, type);
	अगर (rc)
		जाओ out;

	rc = qed_dcbx_get_params(p_hwfn, p_get, type);

out:
	qed_ptt_release(p_hwfn, p_ptt);
	वापस rc;
पूर्ण

अटल व्योम
qed_dcbx_set_pfc_data(काष्ठा qed_hwfn *p_hwfn,
		      u32 *pfc, काष्ठा qed_dcbx_params *p_params)
अणु
	u8 pfc_map = 0;
	पूर्णांक i;

	*pfc &= ~DCBX_PFC_ERROR_MASK;

	अगर (p_params->pfc.willing)
		*pfc |= DCBX_PFC_WILLING_MASK;
	अन्यथा
		*pfc &= ~DCBX_PFC_WILLING_MASK;

	अगर (p_params->pfc.enabled)
		*pfc |= DCBX_PFC_ENABLED_MASK;
	अन्यथा
		*pfc &= ~DCBX_PFC_ENABLED_MASK;

	*pfc &= ~DCBX_PFC_CAPS_MASK;
	*pfc |= (u32)p_params->pfc.max_tc << DCBX_PFC_CAPS_SHIFT;

	क्रम (i = 0; i < QED_MAX_PFC_PRIORITIES; i++)
		अगर (p_params->pfc.prio[i])
			pfc_map |= BIT(i);

	*pfc &= ~DCBX_PFC_PRI_EN_BITMAP_MASK;
	*pfc |= (pfc_map << DCBX_PFC_PRI_EN_BITMAP_SHIFT);

	DP_VERBOSE(p_hwfn, QED_MSG_DCB, "pfc = 0x%x\n", *pfc);
पूर्ण

अटल व्योम
qed_dcbx_set_ets_data(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा dcbx_ets_feature *p_ets,
		      काष्ठा qed_dcbx_params *p_params)
अणु
	__be32 bw_map[2], tsa_map[2];
	u32 val;
	पूर्णांक i;

	अगर (p_params->ets_willing)
		p_ets->flags |= DCBX_ETS_WILLING_MASK;
	अन्यथा
		p_ets->flags &= ~DCBX_ETS_WILLING_MASK;

	अगर (p_params->ets_cbs)
		p_ets->flags |= DCBX_ETS_CBS_MASK;
	अन्यथा
		p_ets->flags &= ~DCBX_ETS_CBS_MASK;

	अगर (p_params->ets_enabled)
		p_ets->flags |= DCBX_ETS_ENABLED_MASK;
	अन्यथा
		p_ets->flags &= ~DCBX_ETS_ENABLED_MASK;

	p_ets->flags &= ~DCBX_ETS_MAX_TCS_MASK;
	p_ets->flags |= (u32)p_params->max_ets_tc << DCBX_ETS_MAX_TCS_SHIFT;

	p_ets->pri_tc_tbl[0] = 0;

	क्रम (i = 0; i < QED_MAX_PFC_PRIORITIES; i++) अणु
		((u8 *)bw_map)[i] = p_params->ets_tc_bw_tbl[i];
		((u8 *)tsa_map)[i] = p_params->ets_tc_tsa_tbl[i];

		/* Copy the priority value to the corresponding 4 bits in the
		 * traffic class table.
		 */
		val = (((u32)p_params->ets_pri_tc_tbl[i]) << ((7 - i) * 4));
		p_ets->pri_tc_tbl[0] |= val;
	पूर्ण

	be32_to_cpu_array(p_ets->tc_bw_tbl, bw_map, 2);
	be32_to_cpu_array(p_ets->tc_tsa_tbl, tsa_map, 2);
पूर्ण

अटल व्योम
qed_dcbx_set_app_data(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा dcbx_app_priority_feature *p_app,
		      काष्ठा qed_dcbx_params *p_params, bool ieee)
अणु
	u32 *entry;
	पूर्णांक i;

	अगर (p_params->app_willing)
		p_app->flags |= DCBX_APP_WILLING_MASK;
	अन्यथा
		p_app->flags &= ~DCBX_APP_WILLING_MASK;

	अगर (p_params->app_valid)
		p_app->flags |= DCBX_APP_ENABLED_MASK;
	अन्यथा
		p_app->flags &= ~DCBX_APP_ENABLED_MASK;

	p_app->flags &= ~DCBX_APP_NUM_ENTRIES_MASK;
	p_app->flags |= (u32)p_params->num_app_entries <<
	    DCBX_APP_NUM_ENTRIES_SHIFT;

	क्रम (i = 0; i < DCBX_MAX_APP_PROTOCOL; i++) अणु
		entry = &p_app->app_pri_tbl[i].entry;
		*entry = 0;
		अगर (ieee) अणु
			*entry &= ~(DCBX_APP_SF_IEEE_MASK | DCBX_APP_SF_MASK);
			चयन (p_params->app_entry[i].sf_ieee) अणु
			हाल QED_DCBX_SF_IEEE_ETHTYPE:
				*entry |= ((u32)DCBX_APP_SF_IEEE_ETHTYPE <<
					   DCBX_APP_SF_IEEE_SHIFT);
				*entry |= ((u32)DCBX_APP_SF_ETHTYPE <<
					   DCBX_APP_SF_SHIFT);
				अवरोध;
			हाल QED_DCBX_SF_IEEE_TCP_PORT:
				*entry |= ((u32)DCBX_APP_SF_IEEE_TCP_PORT <<
					   DCBX_APP_SF_IEEE_SHIFT);
				*entry |= ((u32)DCBX_APP_SF_PORT <<
					   DCBX_APP_SF_SHIFT);
				अवरोध;
			हाल QED_DCBX_SF_IEEE_UDP_PORT:
				*entry |= ((u32)DCBX_APP_SF_IEEE_UDP_PORT <<
					   DCBX_APP_SF_IEEE_SHIFT);
				*entry |= ((u32)DCBX_APP_SF_PORT <<
					   DCBX_APP_SF_SHIFT);
				अवरोध;
			हाल QED_DCBX_SF_IEEE_TCP_UDP_PORT:
				*entry |= ((u32)DCBX_APP_SF_IEEE_TCP_UDP_PORT <<
					   DCBX_APP_SF_IEEE_SHIFT);
				*entry |= ((u32)DCBX_APP_SF_PORT <<
					   DCBX_APP_SF_SHIFT);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			*entry &= ~DCBX_APP_SF_MASK;
			अगर (p_params->app_entry[i].ethtype)
				*entry |= ((u32)DCBX_APP_SF_ETHTYPE <<
					   DCBX_APP_SF_SHIFT);
			अन्यथा
				*entry |= ((u32)DCBX_APP_SF_PORT <<
					   DCBX_APP_SF_SHIFT);
		पूर्ण

		*entry &= ~DCBX_APP_PROTOCOL_ID_MASK;
		*entry |= ((u32)p_params->app_entry[i].proto_id <<
			   DCBX_APP_PROTOCOL_ID_SHIFT);
		*entry &= ~DCBX_APP_PRI_MAP_MASK;
		*entry |= ((u32)(p_params->app_entry[i].prio) <<
			   DCBX_APP_PRI_MAP_SHIFT);
	पूर्ण
पूर्ण

अटल व्योम
qed_dcbx_set_local_params(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा dcbx_local_params *local_admin,
			  काष्ठा qed_dcbx_set *params)
अणु
	bool ieee = false;

	local_admin->flags = 0;
	स_नकल(&local_admin->features,
	       &p_hwfn->p_dcbx_info->operational.features,
	       माप(local_admin->features));

	अगर (params->enabled) अणु
		local_admin->config = params->ver_num;
		ieee = !!(params->ver_num & DCBX_CONFIG_VERSION_IEEE);
	पूर्ण अन्यथा अणु
		local_admin->config = DCBX_CONFIG_VERSION_DISABLED;
	पूर्ण

	DP_VERBOSE(p_hwfn, QED_MSG_DCB, "Dcbx version = %d\n",
		   local_admin->config);

	अगर (params->override_flags & QED_DCBX_OVERRIDE_PFC_CFG)
		qed_dcbx_set_pfc_data(p_hwfn, &local_admin->features.pfc,
				      &params->config.params);

	अगर (params->override_flags & QED_DCBX_OVERRIDE_ETS_CFG)
		qed_dcbx_set_ets_data(p_hwfn, &local_admin->features.ets,
				      &params->config.params);

	अगर (params->override_flags & QED_DCBX_OVERRIDE_APP_CFG)
		qed_dcbx_set_app_data(p_hwfn, &local_admin->features.app,
				      &params->config.params, ieee);
पूर्ण

पूर्णांक qed_dcbx_config_params(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt,
			   काष्ठा qed_dcbx_set *params, bool hw_commit)
अणु
	काष्ठा dcbx_local_params local_admin;
	काष्ठा qed_dcbx_mib_meta_data data;
	u32 resp = 0, param = 0;
	पूर्णांक rc = 0;

	अगर (!hw_commit) अणु
		स_नकल(&p_hwfn->p_dcbx_info->set, params,
		       माप(काष्ठा qed_dcbx_set));
		वापस 0;
	पूर्ण

	/* clear set-parmas cache */
	स_रखो(&p_hwfn->p_dcbx_info->set, 0, माप(p_hwfn->p_dcbx_info->set));

	स_रखो(&local_admin, 0, माप(local_admin));
	qed_dcbx_set_local_params(p_hwfn, &local_admin, params);

	data.addr = p_hwfn->mcp_info->port_addr +
	    दुरत्व(काष्ठा खुला_port, local_admin_dcbx_mib);
	data.local_admin = &local_admin;
	data.size = माप(काष्ठा dcbx_local_params);
	qed_स_नकल_to(p_hwfn, p_ptt, data.addr, data.local_admin, data.size);

	rc = qed_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_SET_DCBX,
			 1 << DRV_MB_PARAM_LLDP_SEND_SHIFT, &resp, &param);
	अगर (rc)
		DP_NOTICE(p_hwfn, "Failed to send DCBX update request\n");

	वापस rc;
पूर्ण

पूर्णांक qed_dcbx_get_config_params(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_dcbx_set *params)
अणु
	काष्ठा qed_dcbx_get *dcbx_info;
	पूर्णांक rc;

	अगर (p_hwfn->p_dcbx_info->set.config.valid) अणु
		स_नकल(params, &p_hwfn->p_dcbx_info->set,
		       माप(काष्ठा qed_dcbx_set));
		वापस 0;
	पूर्ण

	dcbx_info = kzalloc(माप(*dcbx_info), GFP_KERNEL);
	अगर (!dcbx_info)
		वापस -ENOMEM;

	rc = qed_dcbx_query_params(p_hwfn, dcbx_info, QED_DCBX_OPERATIONAL_MIB);
	अगर (rc) अणु
		kमुक्त(dcbx_info);
		वापस rc;
	पूर्ण

	p_hwfn->p_dcbx_info->set.override_flags = 0;
	p_hwfn->p_dcbx_info->set.ver_num = DCBX_CONFIG_VERSION_DISABLED;
	अगर (dcbx_info->operational.cee)
		p_hwfn->p_dcbx_info->set.ver_num |= DCBX_CONFIG_VERSION_CEE;
	अगर (dcbx_info->operational.ieee)
		p_hwfn->p_dcbx_info->set.ver_num |= DCBX_CONFIG_VERSION_IEEE;
	अगर (dcbx_info->operational.local)
		p_hwfn->p_dcbx_info->set.ver_num |= DCBX_CONFIG_VERSION_STATIC;

	p_hwfn->p_dcbx_info->set.enabled = dcbx_info->operational.enabled;
	BUILD_BUG_ON(माप(dcbx_info->operational.params) !=
		     माप(p_hwfn->p_dcbx_info->set.config.params));
	स_नकल(&p_hwfn->p_dcbx_info->set.config.params,
	       &dcbx_info->operational.params,
	       माप(p_hwfn->p_dcbx_info->set.config.params));
	p_hwfn->p_dcbx_info->set.config.valid = true;

	स_नकल(params, &p_hwfn->p_dcbx_info->set, माप(काष्ठा qed_dcbx_set));

	kमुक्त(dcbx_info);

	वापस 0;
पूर्ण

अटल काष्ठा qed_dcbx_get *qed_dcbnl_get_dcbx(काष्ठा qed_hwfn *hwfn,
					       क्रमागत qed_mib_पढ़ो_type type)
अणु
	काष्ठा qed_dcbx_get *dcbx_info;

	dcbx_info = kzalloc(माप(*dcbx_info), GFP_ATOMIC);
	अगर (!dcbx_info)
		वापस शून्य;

	अगर (qed_dcbx_query_params(hwfn, dcbx_info, type)) अणु
		kमुक्त(dcbx_info);
		वापस शून्य;
	पूर्ण

	अगर ((type == QED_DCBX_OPERATIONAL_MIB) &&
	    !dcbx_info->operational.enabled) अणु
		DP_INFO(hwfn, "DCBX is not enabled/operational\n");
		kमुक्त(dcbx_info);
		वापस शून्य;
	पूर्ण

	वापस dcbx_info;
पूर्ण

अटल u8 qed_dcbnl_माला_लोtate(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	bool enabled;

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस 0;

	enabled = dcbx_info->operational.enabled;
	DP_VERBOSE(hwfn, QED_MSG_DCB, "DCB state = %d\n", enabled);
	kमुक्त(dcbx_info);

	वापस enabled;
पूर्ण

अटल u8 qed_dcbnl_setstate(काष्ठा qed_dev *cdev, u8 state)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_set dcbx_set;
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "DCB state = %d\n", state);

	स_रखो(&dcbx_set, 0, माप(dcbx_set));
	rc = qed_dcbx_get_config_params(hwfn, &dcbx_set);
	अगर (rc)
		वापस 1;

	dcbx_set.enabled = !!state;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस 1;

	rc = qed_dcbx_config_params(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_release(hwfn, ptt);

	वापस rc ? 1 : 0;
पूर्ण

अटल व्योम qed_dcbnl_getpgtccfgtx(काष्ठा qed_dev *cdev, पूर्णांक tc, u8 *prio_type,
				   u8 *pgid, u8 *bw_pct, u8 *up_map)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "tc = %d\n", tc);
	*prio_type = *pgid = *bw_pct = *up_map = 0;
	अगर (tc < 0 || tc >= QED_MAX_PFC_PRIORITIES) अणु
		DP_INFO(hwfn, "Invalid tc %d\n", tc);
		वापस;
	पूर्ण

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस;

	*pgid = dcbx_info->operational.params.ets_pri_tc_tbl[tc];
	kमुक्त(dcbx_info);
पूर्ण

अटल व्योम qed_dcbnl_getpgbwgcfgtx(काष्ठा qed_dev *cdev, पूर्णांक pgid, u8 *bw_pct)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;

	*bw_pct = 0;
	DP_VERBOSE(hwfn, QED_MSG_DCB, "pgid = %d\n", pgid);
	अगर (pgid < 0 || pgid >= QED_MAX_PFC_PRIORITIES) अणु
		DP_INFO(hwfn, "Invalid pgid %d\n", pgid);
		वापस;
	पूर्ण

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस;

	*bw_pct = dcbx_info->operational.params.ets_tc_bw_tbl[pgid];
	DP_VERBOSE(hwfn, QED_MSG_DCB, "bw_pct = %d\n", *bw_pct);
	kमुक्त(dcbx_info);
पूर्ण

अटल व्योम qed_dcbnl_getpgtccfgrx(काष्ठा qed_dev *cdev, पूर्णांक tc, u8 *prio,
				   u8 *bwg_id, u8 *bw_pct, u8 *up_map)
अणु
	DP_INFO(QED_LEADING_HWFN(cdev), "Rx ETS is not supported\n");
	*prio = *bwg_id = *bw_pct = *up_map = 0;
पूर्ण

अटल व्योम qed_dcbnl_getpgbwgcfgrx(काष्ठा qed_dev *cdev,
				    पूर्णांक bwg_id, u8 *bw_pct)
अणु
	DP_INFO(QED_LEADING_HWFN(cdev), "Rx ETS is not supported\n");
	*bw_pct = 0;
पूर्ण

अटल व्योम qed_dcbnl_getpfccfg(काष्ठा qed_dev *cdev,
				पूर्णांक priority, u8 *setting)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "priority = %d\n", priority);
	अगर (priority < 0 || priority >= QED_MAX_PFC_PRIORITIES) अणु
		DP_INFO(hwfn, "Invalid priority %d\n", priority);
		वापस;
	पूर्ण

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस;

	*setting = dcbx_info->operational.params.pfc.prio[priority];
	DP_VERBOSE(hwfn, QED_MSG_DCB, "setting = %d\n", *setting);
	kमुक्त(dcbx_info);
पूर्ण

अटल व्योम qed_dcbnl_setpfccfg(काष्ठा qed_dev *cdev, पूर्णांक priority, u8 setting)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_set dcbx_set;
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "priority = %d setting = %d\n",
		   priority, setting);
	अगर (priority < 0 || priority >= QED_MAX_PFC_PRIORITIES) अणु
		DP_INFO(hwfn, "Invalid priority %d\n", priority);
		वापस;
	पूर्ण

	स_रखो(&dcbx_set, 0, माप(dcbx_set));
	rc = qed_dcbx_get_config_params(hwfn, &dcbx_set);
	अगर (rc)
		वापस;

	dcbx_set.override_flags |= QED_DCBX_OVERRIDE_PFC_CFG;
	dcbx_set.config.params.pfc.prio[priority] = !!setting;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस;

	rc = qed_dcbx_config_params(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_release(hwfn, ptt);
पूर्ण

अटल u8 qed_dcbnl_अ_लोap(काष्ठा qed_dev *cdev, पूर्णांक capid, u8 *cap)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	पूर्णांक rc = 0;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "capid = %d\n", capid);
	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस 1;

	चयन (capid) अणु
	हाल DCB_CAP_ATTR_PG:
	हाल DCB_CAP_ATTR_PFC:
	हाल DCB_CAP_ATTR_UP2TC:
	हाल DCB_CAP_ATTR_GSP:
		*cap = true;
		अवरोध;
	हाल DCB_CAP_ATTR_PG_TCS:
	हाल DCB_CAP_ATTR_PFC_TCS:
		*cap = 0x80;
		अवरोध;
	हाल DCB_CAP_ATTR_DCBX:
		*cap = (DCB_CAP_DCBX_VER_CEE | DCB_CAP_DCBX_VER_IEEE |
			DCB_CAP_DCBX_STATIC);
		अवरोध;
	शेष:
		*cap = false;
		rc = 1;
	पूर्ण

	DP_VERBOSE(hwfn, QED_MSG_DCB, "id = %d caps = %d\n", capid, *cap);
	kमुक्त(dcbx_info);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_dcbnl_getnumtcs(काष्ठा qed_dev *cdev, पूर्णांक tcid, u8 *num)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	पूर्णांक rc = 0;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "tcid = %d\n", tcid);
	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस -EINVAL;

	चयन (tcid) अणु
	हाल DCB_NUMTCS_ATTR_PG:
		*num = dcbx_info->operational.params.max_ets_tc;
		अवरोध;
	हाल DCB_NUMTCS_ATTR_PFC:
		*num = dcbx_info->operational.params.pfc.max_tc;
		अवरोध;
	शेष:
		rc = -EINVAL;
	पूर्ण

	kमुक्त(dcbx_info);
	DP_VERBOSE(hwfn, QED_MSG_DCB, "numtcs = %d\n", *num);

	वापस rc;
पूर्ण

अटल u8 qed_dcbnl_getpfcstate(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	bool enabled;

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस 0;

	enabled = dcbx_info->operational.params.pfc.enabled;
	DP_VERBOSE(hwfn, QED_MSG_DCB, "pfc state = %d\n", enabled);
	kमुक्त(dcbx_info);

	वापस enabled;
पूर्ण

अटल u8 qed_dcbnl_getdcbx(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	u8 mode = 0;

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस 0;

	अगर (dcbx_info->operational.ieee)
		mode |= DCB_CAP_DCBX_VER_IEEE;
	अगर (dcbx_info->operational.cee)
		mode |= DCB_CAP_DCBX_VER_CEE;
	अगर (dcbx_info->operational.local)
		mode |= DCB_CAP_DCBX_STATIC;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "dcb mode = %d\n", mode);
	kमुक्त(dcbx_info);

	वापस mode;
पूर्ण

अटल व्योम qed_dcbnl_setpgtccfgtx(काष्ठा qed_dev *cdev,
				   पूर्णांक tc,
				   u8 pri_type, u8 pgid, u8 bw_pct, u8 up_map)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_set dcbx_set;
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc;

	DP_VERBOSE(hwfn, QED_MSG_DCB,
		   "tc = %d pri_type = %d pgid = %d bw_pct = %d up_map = %d\n",
		   tc, pri_type, pgid, bw_pct, up_map);

	अगर (tc < 0 || tc >= QED_MAX_PFC_PRIORITIES) अणु
		DP_INFO(hwfn, "Invalid tc %d\n", tc);
		वापस;
	पूर्ण

	स_रखो(&dcbx_set, 0, माप(dcbx_set));
	rc = qed_dcbx_get_config_params(hwfn, &dcbx_set);
	अगर (rc)
		वापस;

	dcbx_set.override_flags |= QED_DCBX_OVERRIDE_ETS_CFG;
	dcbx_set.config.params.ets_pri_tc_tbl[tc] = pgid;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस;

	rc = qed_dcbx_config_params(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_release(hwfn, ptt);
पूर्ण

अटल व्योम qed_dcbnl_setpgtccfgrx(काष्ठा qed_dev *cdev, पूर्णांक prio,
				   u8 pri_type, u8 pgid, u8 bw_pct, u8 up_map)
अणु
	DP_INFO(QED_LEADING_HWFN(cdev), "Rx ETS is not supported\n");
पूर्ण

अटल व्योम qed_dcbnl_setpgbwgcfgtx(काष्ठा qed_dev *cdev, पूर्णांक pgid, u8 bw_pct)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_set dcbx_set;
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "pgid = %d bw_pct = %d\n", pgid, bw_pct);
	अगर (pgid < 0 || pgid >= QED_MAX_PFC_PRIORITIES) अणु
		DP_INFO(hwfn, "Invalid pgid %d\n", pgid);
		वापस;
	पूर्ण

	स_रखो(&dcbx_set, 0, माप(dcbx_set));
	rc = qed_dcbx_get_config_params(hwfn, &dcbx_set);
	अगर (rc)
		वापस;

	dcbx_set.override_flags |= QED_DCBX_OVERRIDE_ETS_CFG;
	dcbx_set.config.params.ets_tc_bw_tbl[pgid] = bw_pct;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस;

	rc = qed_dcbx_config_params(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_release(hwfn, ptt);
पूर्ण

अटल व्योम qed_dcbnl_setpgbwgcfgrx(काष्ठा qed_dev *cdev, पूर्णांक pgid, u8 bw_pct)
अणु
	DP_INFO(QED_LEADING_HWFN(cdev), "Rx ETS is not supported\n");
पूर्ण

अटल u8 qed_dcbnl_setall(काष्ठा qed_dev *cdev)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_set dcbx_set;
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc;

	स_रखो(&dcbx_set, 0, माप(dcbx_set));
	rc = qed_dcbx_get_config_params(hwfn, &dcbx_set);
	अगर (rc)
		वापस 1;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस 1;

	rc = qed_dcbx_config_params(hwfn, ptt, &dcbx_set, 1);

	qed_ptt_release(hwfn, ptt);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_dcbnl_setnumtcs(काष्ठा qed_dev *cdev, पूर्णांक tcid, u8 num)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_set dcbx_set;
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "tcid = %d num = %d\n", tcid, num);
	स_रखो(&dcbx_set, 0, माप(dcbx_set));
	rc = qed_dcbx_get_config_params(hwfn, &dcbx_set);
	अगर (rc)
		वापस 1;

	चयन (tcid) अणु
	हाल DCB_NUMTCS_ATTR_PG:
		dcbx_set.override_flags |= QED_DCBX_OVERRIDE_ETS_CFG;
		dcbx_set.config.params.max_ets_tc = num;
		अवरोध;
	हाल DCB_NUMTCS_ATTR_PFC:
		dcbx_set.override_flags |= QED_DCBX_OVERRIDE_PFC_CFG;
		dcbx_set.config.params.pfc.max_tc = num;
		अवरोध;
	शेष:
		DP_INFO(hwfn, "Invalid tcid %d\n", tcid);
		वापस -EINVAL;
	पूर्ण

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EINVAL;

	rc = qed_dcbx_config_params(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_release(hwfn, ptt);

	वापस 0;
पूर्ण

अटल व्योम qed_dcbnl_setpfcstate(काष्ठा qed_dev *cdev, u8 state)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_set dcbx_set;
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "new state = %d\n", state);

	स_रखो(&dcbx_set, 0, माप(dcbx_set));
	rc = qed_dcbx_get_config_params(hwfn, &dcbx_set);
	अगर (rc)
		वापस;

	dcbx_set.override_flags |= QED_DCBX_OVERRIDE_PFC_CFG;
	dcbx_set.config.params.pfc.enabled = !!state;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस;

	rc = qed_dcbx_config_params(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_release(hwfn, ptt);
पूर्ण

अटल पूर्णांक qed_dcbnl_getapp(काष्ठा qed_dev *cdev, u8 idtype, u16 idval)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	काष्ठा qed_app_entry *entry;
	bool ethtype;
	u8 prio = 0;
	पूर्णांक i;

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस -EINVAL;

	ethtype = !!(idtype == DCB_APP_IDTYPE_ETHTYPE);
	क्रम (i = 0; i < QED_DCBX_MAX_APP_PROTOCOL; i++) अणु
		entry = &dcbx_info->operational.params.app_entry[i];
		अगर ((entry->ethtype == ethtype) && (entry->proto_id == idval)) अणु
			prio = entry->prio;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == QED_DCBX_MAX_APP_PROTOCOL) अणु
		DP_ERR(cdev, "App entry (%d, %d) not found\n", idtype, idval);
		kमुक्त(dcbx_info);
		वापस -EINVAL;
	पूर्ण

	kमुक्त(dcbx_info);

	वापस prio;
पूर्ण

अटल पूर्णांक qed_dcbnl_setapp(काष्ठा qed_dev *cdev,
			    u8 idtype, u16 idval, u8 pri_map)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_set dcbx_set;
	काष्ठा qed_app_entry *entry;
	काष्ठा qed_ptt *ptt;
	bool ethtype;
	पूर्णांक rc, i;

	स_रखो(&dcbx_set, 0, माप(dcbx_set));
	rc = qed_dcbx_get_config_params(hwfn, &dcbx_set);
	अगर (rc)
		वापस -EINVAL;

	ethtype = !!(idtype == DCB_APP_IDTYPE_ETHTYPE);
	क्रम (i = 0; i < QED_DCBX_MAX_APP_PROTOCOL; i++) अणु
		entry = &dcbx_set.config.params.app_entry[i];
		अगर ((entry->ethtype == ethtype) && (entry->proto_id == idval))
			अवरोध;
		/* First empty slot */
		अगर (!entry->proto_id) अणु
			dcbx_set.config.params.num_app_entries++;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == QED_DCBX_MAX_APP_PROTOCOL) अणु
		DP_ERR(cdev, "App table is full\n");
		वापस -EBUSY;
	पूर्ण

	dcbx_set.override_flags |= QED_DCBX_OVERRIDE_APP_CFG;
	dcbx_set.config.params.app_entry[i].ethtype = ethtype;
	dcbx_set.config.params.app_entry[i].proto_id = idval;
	dcbx_set.config.params.app_entry[i].prio = pri_map;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EBUSY;

	rc = qed_dcbx_config_params(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_release(hwfn, ptt);

	वापस rc;
पूर्ण

अटल u8 qed_dcbnl_setdcbx(काष्ठा qed_dev *cdev, u8 mode)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_set dcbx_set;
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "new mode = %x\n", mode);

	अगर (!(mode & DCB_CAP_DCBX_VER_IEEE) &&
	    !(mode & DCB_CAP_DCBX_VER_CEE) && !(mode & DCB_CAP_DCBX_STATIC)) अणु
		DP_INFO(hwfn, "Allowed modes are cee, ieee or static\n");
		वापस 1;
	पूर्ण

	स_रखो(&dcbx_set, 0, माप(dcbx_set));
	rc = qed_dcbx_get_config_params(hwfn, &dcbx_set);
	अगर (rc)
		वापस 1;

	dcbx_set.ver_num = 0;
	अगर (mode & DCB_CAP_DCBX_VER_CEE) अणु
		dcbx_set.ver_num |= DCBX_CONFIG_VERSION_CEE;
		dcbx_set.enabled = true;
	पूर्ण

	अगर (mode & DCB_CAP_DCBX_VER_IEEE) अणु
		dcbx_set.ver_num |= DCBX_CONFIG_VERSION_IEEE;
		dcbx_set.enabled = true;
	पूर्ण

	अगर (mode & DCB_CAP_DCBX_STATIC) अणु
		dcbx_set.ver_num |= DCBX_CONFIG_VERSION_STATIC;
		dcbx_set.enabled = true;
	पूर्ण

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस 1;

	rc = qed_dcbx_config_params(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_release(hwfn, ptt);

	वापस rc;
पूर्ण

अटल u8 qed_dcbnl_getfeatcfg(काष्ठा qed_dev *cdev, पूर्णांक featid, u8 *flags)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "Feature id  = %d\n", featid);
	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस 1;

	*flags = 0;
	चयन (featid) अणु
	हाल DCB_FEATCFG_ATTR_PG:
		अगर (dcbx_info->operational.params.ets_enabled)
			*flags = DCB_FEATCFG_ENABLE;
		अन्यथा
			*flags = DCB_FEATCFG_ERROR;
		अवरोध;
	हाल DCB_FEATCFG_ATTR_PFC:
		अगर (dcbx_info->operational.params.pfc.enabled)
			*flags = DCB_FEATCFG_ENABLE;
		अन्यथा
			*flags = DCB_FEATCFG_ERROR;
		अवरोध;
	हाल DCB_FEATCFG_ATTR_APP:
		अगर (dcbx_info->operational.params.app_valid)
			*flags = DCB_FEATCFG_ENABLE;
		अन्यथा
			*flags = DCB_FEATCFG_ERROR;
		अवरोध;
	शेष:
		DP_INFO(hwfn, "Invalid feature-ID %d\n", featid);
		kमुक्त(dcbx_info);
		वापस 1;
	पूर्ण

	DP_VERBOSE(hwfn, QED_MSG_DCB, "flags = %d\n", *flags);
	kमुक्त(dcbx_info);

	वापस 0;
पूर्ण

अटल u8 qed_dcbnl_setfeatcfg(काष्ठा qed_dev *cdev, पूर्णांक featid, u8 flags)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_set dcbx_set;
	bool enabled, willing;
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "featid = %d flags = %d\n",
		   featid, flags);
	स_रखो(&dcbx_set, 0, माप(dcbx_set));
	rc = qed_dcbx_get_config_params(hwfn, &dcbx_set);
	अगर (rc)
		वापस 1;

	enabled = !!(flags & DCB_FEATCFG_ENABLE);
	willing = !!(flags & DCB_FEATCFG_WILLING);
	चयन (featid) अणु
	हाल DCB_FEATCFG_ATTR_PG:
		dcbx_set.override_flags |= QED_DCBX_OVERRIDE_ETS_CFG;
		dcbx_set.config.params.ets_enabled = enabled;
		dcbx_set.config.params.ets_willing = willing;
		अवरोध;
	हाल DCB_FEATCFG_ATTR_PFC:
		dcbx_set.override_flags |= QED_DCBX_OVERRIDE_PFC_CFG;
		dcbx_set.config.params.pfc.enabled = enabled;
		dcbx_set.config.params.pfc.willing = willing;
		अवरोध;
	हाल DCB_FEATCFG_ATTR_APP:
		dcbx_set.override_flags |= QED_DCBX_OVERRIDE_APP_CFG;
		dcbx_set.config.params.app_willing = willing;
		अवरोध;
	शेष:
		DP_INFO(hwfn, "Invalid feature-ID %d\n", featid);
		वापस 1;
	पूर्ण

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस 1;

	rc = qed_dcbx_config_params(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_release(hwfn, ptt);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_dcbnl_peer_getappinfo(काष्ठा qed_dev *cdev,
				     काष्ठा dcb_peer_app_info *info,
				     u16 *app_count)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_REMOTE_MIB);
	अगर (!dcbx_info)
		वापस -EINVAL;

	info->willing = dcbx_info->remote.params.app_willing;
	info->error = dcbx_info->remote.params.app_error;
	*app_count = dcbx_info->remote.params.num_app_entries;
	kमुक्त(dcbx_info);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_dcbnl_peer_getapptable(काष्ठा qed_dev *cdev,
				      काष्ठा dcb_app *table)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	पूर्णांक i;

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_REMOTE_MIB);
	अगर (!dcbx_info)
		वापस -EINVAL;

	क्रम (i = 0; i < dcbx_info->remote.params.num_app_entries; i++) अणु
		अगर (dcbx_info->remote.params.app_entry[i].ethtype)
			table[i].selector = DCB_APP_IDTYPE_ETHTYPE;
		अन्यथा
			table[i].selector = DCB_APP_IDTYPE_PORTNUM;
		table[i].priority = dcbx_info->remote.params.app_entry[i].prio;
		table[i].protocol =
		    dcbx_info->remote.params.app_entry[i].proto_id;
	पूर्ण

	kमुक्त(dcbx_info);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_dcbnl_cee_peer_getpfc(काष्ठा qed_dev *cdev, काष्ठा cee_pfc *pfc)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	पूर्णांक i;

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_REMOTE_MIB);
	अगर (!dcbx_info)
		वापस -EINVAL;

	क्रम (i = 0; i < QED_MAX_PFC_PRIORITIES; i++)
		अगर (dcbx_info->remote.params.pfc.prio[i])
			pfc->pfc_en |= BIT(i);

	pfc->tcs_supported = dcbx_info->remote.params.pfc.max_tc;
	DP_VERBOSE(hwfn, QED_MSG_DCB, "pfc state = %d tcs_supported = %d\n",
		   pfc->pfc_en, pfc->tcs_supported);
	kमुक्त(dcbx_info);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_dcbnl_cee_peer_getpg(काष्ठा qed_dev *cdev, काष्ठा cee_pg *pg)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	पूर्णांक i;

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_REMOTE_MIB);
	अगर (!dcbx_info)
		वापस -EINVAL;

	pg->willing = dcbx_info->remote.params.ets_willing;
	क्रम (i = 0; i < QED_MAX_PFC_PRIORITIES; i++) अणु
		pg->pg_bw[i] = dcbx_info->remote.params.ets_tc_bw_tbl[i];
		pg->prio_pg[i] = dcbx_info->remote.params.ets_pri_tc_tbl[i];
	पूर्ण

	DP_VERBOSE(hwfn, QED_MSG_DCB, "willing = %d", pg->willing);
	kमुक्त(dcbx_info);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_dcbnl_get_ieee_pfc(काष्ठा qed_dev *cdev,
				  काष्ठा ieee_pfc *pfc, bool remote)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_params *params;
	काष्ठा qed_dcbx_get *dcbx_info;
	पूर्णांक rc, i;

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस -EINVAL;

	अगर (!dcbx_info->operational.ieee) अणु
		DP_INFO(hwfn, "DCBX is not enabled/operational in IEEE mode\n");
		kमुक्त(dcbx_info);
		वापस -EINVAL;
	पूर्ण

	अगर (remote) अणु
		स_रखो(dcbx_info, 0, माप(*dcbx_info));
		rc = qed_dcbx_query_params(hwfn, dcbx_info,
					   QED_DCBX_REMOTE_MIB);
		अगर (rc) अणु
			kमुक्त(dcbx_info);
			वापस -EINVAL;
		पूर्ण

		params = &dcbx_info->remote.params;
	पूर्ण अन्यथा अणु
		params = &dcbx_info->operational.params;
	पूर्ण

	pfc->pfc_cap = params->pfc.max_tc;
	pfc->pfc_en = 0;
	क्रम (i = 0; i < QED_MAX_PFC_PRIORITIES; i++)
		अगर (params->pfc.prio[i])
			pfc->pfc_en |= BIT(i);

	kमुक्त(dcbx_info);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_dcbnl_ieee_getpfc(काष्ठा qed_dev *cdev, काष्ठा ieee_pfc *pfc)
अणु
	वापस qed_dcbnl_get_ieee_pfc(cdev, pfc, false);
पूर्ण

अटल पूर्णांक qed_dcbnl_ieee_setpfc(काष्ठा qed_dev *cdev, काष्ठा ieee_pfc *pfc)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	काष्ठा qed_dcbx_set dcbx_set;
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc, i;

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस -EINVAL;

	अगर (!dcbx_info->operational.ieee) अणु
		DP_INFO(hwfn, "DCBX is not enabled/operational in IEEE mode\n");
		kमुक्त(dcbx_info);
		वापस -EINVAL;
	पूर्ण

	kमुक्त(dcbx_info);

	स_रखो(&dcbx_set, 0, माप(dcbx_set));
	rc = qed_dcbx_get_config_params(hwfn, &dcbx_set);
	अगर (rc)
		वापस -EINVAL;

	dcbx_set.override_flags |= QED_DCBX_OVERRIDE_PFC_CFG;
	क्रम (i = 0; i < QED_MAX_PFC_PRIORITIES; i++)
		dcbx_set.config.params.pfc.prio[i] = !!(pfc->pfc_en & BIT(i));

	dcbx_set.config.params.pfc.max_tc = pfc->pfc_cap;

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EINVAL;

	rc = qed_dcbx_config_params(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_release(hwfn, ptt);

	वापस rc;
पूर्ण

अटल पूर्णांक qed_dcbnl_get_ieee_ets(काष्ठा qed_dev *cdev,
				  काष्ठा ieee_ets *ets, bool remote)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	काष्ठा qed_dcbx_params *params;
	पूर्णांक rc;

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस -EINVAL;

	अगर (!dcbx_info->operational.ieee) अणु
		DP_INFO(hwfn, "DCBX is not enabled/operational in IEEE mode\n");
		kमुक्त(dcbx_info);
		वापस -EINVAL;
	पूर्ण

	अगर (remote) अणु
		स_रखो(dcbx_info, 0, माप(*dcbx_info));
		rc = qed_dcbx_query_params(hwfn, dcbx_info,
					   QED_DCBX_REMOTE_MIB);
		अगर (rc) अणु
			kमुक्त(dcbx_info);
			वापस -EINVAL;
		पूर्ण

		params = &dcbx_info->remote.params;
	पूर्ण अन्यथा अणु
		params = &dcbx_info->operational.params;
	पूर्ण

	ets->ets_cap = params->max_ets_tc;
	ets->willing = params->ets_willing;
	ets->cbs = params->ets_cbs;
	स_नकल(ets->tc_tx_bw, params->ets_tc_bw_tbl, माप(ets->tc_tx_bw));
	स_नकल(ets->tc_tsa, params->ets_tc_tsa_tbl, माप(ets->tc_tsa));
	स_नकल(ets->prio_tc, params->ets_pri_tc_tbl, माप(ets->prio_tc));
	kमुक्त(dcbx_info);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_dcbnl_ieee_getets(काष्ठा qed_dev *cdev, काष्ठा ieee_ets *ets)
अणु
	वापस qed_dcbnl_get_ieee_ets(cdev, ets, false);
पूर्ण

अटल पूर्णांक qed_dcbnl_ieee_setets(काष्ठा qed_dev *cdev, काष्ठा ieee_ets *ets)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	काष्ठा qed_dcbx_set dcbx_set;
	काष्ठा qed_ptt *ptt;
	पूर्णांक rc;

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस -EINVAL;

	अगर (!dcbx_info->operational.ieee) अणु
		DP_INFO(hwfn, "DCBX is not enabled/operational in IEEE mode\n");
		kमुक्त(dcbx_info);
		वापस -EINVAL;
	पूर्ण

	kमुक्त(dcbx_info);

	स_रखो(&dcbx_set, 0, माप(dcbx_set));
	rc = qed_dcbx_get_config_params(hwfn, &dcbx_set);
	अगर (rc)
		वापस -EINVAL;

	dcbx_set.override_flags |= QED_DCBX_OVERRIDE_ETS_CFG;
	dcbx_set.config.params.max_ets_tc = ets->ets_cap;
	dcbx_set.config.params.ets_willing = ets->willing;
	dcbx_set.config.params.ets_cbs = ets->cbs;
	स_नकल(dcbx_set.config.params.ets_tc_bw_tbl, ets->tc_tx_bw,
	       माप(ets->tc_tx_bw));
	स_नकल(dcbx_set.config.params.ets_tc_tsa_tbl, ets->tc_tsa,
	       माप(ets->tc_tsa));
	स_नकल(dcbx_set.config.params.ets_pri_tc_tbl, ets->prio_tc,
	       माप(ets->prio_tc));

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EINVAL;

	rc = qed_dcbx_config_params(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_release(hwfn, ptt);

	वापस rc;
पूर्ण

अटल पूर्णांक
qed_dcbnl_ieee_peer_getets(काष्ठा qed_dev *cdev, काष्ठा ieee_ets *ets)
अणु
	वापस qed_dcbnl_get_ieee_ets(cdev, ets, true);
पूर्ण

अटल पूर्णांक
qed_dcbnl_ieee_peer_getpfc(काष्ठा qed_dev *cdev, काष्ठा ieee_pfc *pfc)
अणु
	वापस qed_dcbnl_get_ieee_pfc(cdev, pfc, true);
पूर्ण

अटल पूर्णांक qed_get_sf_ieee_value(u8 selector, u8 *sf_ieee)
अणु
	चयन (selector) अणु
	हाल IEEE_8021QAZ_APP_SEL_ETHERTYPE:
		*sf_ieee = QED_DCBX_SF_IEEE_ETHTYPE;
		अवरोध;
	हाल IEEE_8021QAZ_APP_SEL_STREAM:
		*sf_ieee = QED_DCBX_SF_IEEE_TCP_PORT;
		अवरोध;
	हाल IEEE_8021QAZ_APP_SEL_DGRAM:
		*sf_ieee = QED_DCBX_SF_IEEE_UDP_PORT;
		अवरोध;
	हाल IEEE_8021QAZ_APP_SEL_ANY:
		*sf_ieee = QED_DCBX_SF_IEEE_TCP_UDP_PORT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qed_dcbnl_ieee_getapp(काष्ठा qed_dev *cdev, काष्ठा dcb_app *app)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	काष्ठा qed_app_entry *entry;
	u8 prio = 0;
	u8 sf_ieee;
	पूर्णांक i;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "selector = %d protocol = %d\n",
		   app->selector, app->protocol);

	अगर (qed_get_sf_ieee_value(app->selector, &sf_ieee)) अणु
		DP_INFO(cdev, "Invalid selector field value %d\n",
			app->selector);
		वापस -EINVAL;
	पूर्ण

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस -EINVAL;

	अगर (!dcbx_info->operational.ieee) अणु
		DP_INFO(hwfn, "DCBX is not enabled/operational in IEEE mode\n");
		kमुक्त(dcbx_info);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < QED_DCBX_MAX_APP_PROTOCOL; i++) अणु
		entry = &dcbx_info->operational.params.app_entry[i];
		अगर ((entry->sf_ieee == sf_ieee) &&
		    (entry->proto_id == app->protocol)) अणु
			prio = entry->prio;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == QED_DCBX_MAX_APP_PROTOCOL) अणु
		DP_ERR(cdev, "App entry (%d, %d) not found\n", app->selector,
		       app->protocol);
		kमुक्त(dcbx_info);
		वापस -EINVAL;
	पूर्ण

	app->priority = ffs(prio) - 1;

	kमुक्त(dcbx_info);

	वापस 0;
पूर्ण

अटल पूर्णांक qed_dcbnl_ieee_setapp(काष्ठा qed_dev *cdev, काष्ठा dcb_app *app)
अणु
	काष्ठा qed_hwfn *hwfn = QED_LEADING_HWFN(cdev);
	काष्ठा qed_dcbx_get *dcbx_info;
	काष्ठा qed_dcbx_set dcbx_set;
	काष्ठा qed_app_entry *entry;
	काष्ठा qed_ptt *ptt;
	u8 sf_ieee;
	पूर्णांक rc, i;

	DP_VERBOSE(hwfn, QED_MSG_DCB, "selector = %d protocol = %d pri = %d\n",
		   app->selector, app->protocol, app->priority);
	अगर (app->priority >= QED_MAX_PFC_PRIORITIES) अणु
		DP_INFO(hwfn, "Invalid priority %d\n", app->priority);
		वापस -EINVAL;
	पूर्ण

	अगर (qed_get_sf_ieee_value(app->selector, &sf_ieee)) अणु
		DP_INFO(cdev, "Invalid selector field value %d\n",
			app->selector);
		वापस -EINVAL;
	पूर्ण

	dcbx_info = qed_dcbnl_get_dcbx(hwfn, QED_DCBX_OPERATIONAL_MIB);
	अगर (!dcbx_info)
		वापस -EINVAL;

	अगर (!dcbx_info->operational.ieee) अणु
		DP_INFO(hwfn, "DCBX is not enabled/operational in IEEE mode\n");
		kमुक्त(dcbx_info);
		वापस -EINVAL;
	पूर्ण

	kमुक्त(dcbx_info);

	स_रखो(&dcbx_set, 0, माप(dcbx_set));
	rc = qed_dcbx_get_config_params(hwfn, &dcbx_set);
	अगर (rc)
		वापस -EINVAL;

	क्रम (i = 0; i < QED_DCBX_MAX_APP_PROTOCOL; i++) अणु
		entry = &dcbx_set.config.params.app_entry[i];
		अगर ((entry->sf_ieee == sf_ieee) &&
		    (entry->proto_id == app->protocol))
			अवरोध;
		/* First empty slot */
		अगर (!entry->proto_id) अणु
			dcbx_set.config.params.num_app_entries++;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i == QED_DCBX_MAX_APP_PROTOCOL) अणु
		DP_ERR(cdev, "App table is full\n");
		वापस -EBUSY;
	पूर्ण

	dcbx_set.override_flags |= QED_DCBX_OVERRIDE_APP_CFG;
	dcbx_set.config.params.app_entry[i].sf_ieee = sf_ieee;
	dcbx_set.config.params.app_entry[i].proto_id = app->protocol;
	dcbx_set.config.params.app_entry[i].prio = BIT(app->priority);

	ptt = qed_ptt_acquire(hwfn);
	अगर (!ptt)
		वापस -EBUSY;

	rc = qed_dcbx_config_params(hwfn, ptt, &dcbx_set, 0);

	qed_ptt_release(hwfn, ptt);

	वापस rc;
पूर्ण

स्थिर काष्ठा qed_eth_dcbnl_ops qed_dcbnl_ops_pass = अणु
	.माला_लोtate = qed_dcbnl_माला_लोtate,
	.setstate = qed_dcbnl_setstate,
	.getpgtccfgtx = qed_dcbnl_getpgtccfgtx,
	.getpgbwgcfgtx = qed_dcbnl_getpgbwgcfgtx,
	.getpgtccfgrx = qed_dcbnl_getpgtccfgrx,
	.getpgbwgcfgrx = qed_dcbnl_getpgbwgcfgrx,
	.getpfccfg = qed_dcbnl_getpfccfg,
	.setpfccfg = qed_dcbnl_setpfccfg,
	.अ_लोap = qed_dcbnl_अ_लोap,
	.getnumtcs = qed_dcbnl_getnumtcs,
	.getpfcstate = qed_dcbnl_getpfcstate,
	.getdcbx = qed_dcbnl_getdcbx,
	.setpgtccfgtx = qed_dcbnl_setpgtccfgtx,
	.setpgtccfgrx = qed_dcbnl_setpgtccfgrx,
	.setpgbwgcfgtx = qed_dcbnl_setpgbwgcfgtx,
	.setpgbwgcfgrx = qed_dcbnl_setpgbwgcfgrx,
	.setall = qed_dcbnl_setall,
	.setnumtcs = qed_dcbnl_setnumtcs,
	.setpfcstate = qed_dcbnl_setpfcstate,
	.setapp = qed_dcbnl_setapp,
	.setdcbx = qed_dcbnl_setdcbx,
	.setfeatcfg = qed_dcbnl_setfeatcfg,
	.getfeatcfg = qed_dcbnl_getfeatcfg,
	.getapp = qed_dcbnl_getapp,
	.peer_getappinfo = qed_dcbnl_peer_getappinfo,
	.peer_getapptable = qed_dcbnl_peer_getapptable,
	.cee_peer_getpfc = qed_dcbnl_cee_peer_getpfc,
	.cee_peer_getpg = qed_dcbnl_cee_peer_getpg,
	.ieee_getpfc = qed_dcbnl_ieee_getpfc,
	.ieee_setpfc = qed_dcbnl_ieee_setpfc,
	.ieee_getets = qed_dcbnl_ieee_getets,
	.ieee_setets = qed_dcbnl_ieee_setets,
	.ieee_peer_getpfc = qed_dcbnl_ieee_peer_getpfc,
	.ieee_peer_getets = qed_dcbnl_ieee_peer_getets,
	.ieee_getapp = qed_dcbnl_ieee_getapp,
	.ieee_setapp = qed_dcbnl_ieee_setapp,
पूर्ण;

#पूर्ण_अगर
