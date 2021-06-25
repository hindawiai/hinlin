<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2020 Mellanox Technologies. All rights reserved */

#समावेश "reg.h"
#समावेश "core.h"
#समावेश "spectrum.h"
#समावेश "core_env.h"

अटल स्थिर अक्षर mlxsw_sp_driver_version[] = "1.0";

अटल व्योम mlxsw_sp_port_get_drvinfo(काष्ठा net_device *dev,
				      काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;

	strlcpy(drvinfo->driver, mlxsw_sp->bus_info->device_kind,
		माप(drvinfo->driver));
	strlcpy(drvinfo->version, mlxsw_sp_driver_version,
		माप(drvinfo->version));
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "%d.%d.%d",
		 mlxsw_sp->bus_info->fw_rev.major,
		 mlxsw_sp->bus_info->fw_rev.minor,
		 mlxsw_sp->bus_info->fw_rev.subminor);
	strlcpy(drvinfo->bus_info, mlxsw_sp->bus_info->device_name,
		माप(drvinfo->bus_info));
पूर्ण

काष्ठा mlxsw_sp_ethtool_link_ext_state_opcode_mapping अणु
	u32 status_opcode;
	क्रमागत ethtool_link_ext_state link_ext_state;
	u8 link_ext_substate;
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_ethtool_link_ext_state_opcode_mapping
mlxsw_sp_link_ext_state_opcode_map[] = अणु
	अणु2, ETHTOOL_LINK_EXT_STATE_AUTONEG,
		ETHTOOL_LINK_EXT_SUBSTATE_AN_NO_PARTNER_DETECTEDपूर्ण,
	अणु3, ETHTOOL_LINK_EXT_STATE_AUTONEG,
		ETHTOOL_LINK_EXT_SUBSTATE_AN_ACK_NOT_RECEIVEDपूर्ण,
	अणु4, ETHTOOL_LINK_EXT_STATE_AUTONEG,
		ETHTOOL_LINK_EXT_SUBSTATE_AN_NEXT_PAGE_EXCHANGE_FAILEDपूर्ण,
	अणु36, ETHTOOL_LINK_EXT_STATE_AUTONEG,
		ETHTOOL_LINK_EXT_SUBSTATE_AN_NO_PARTNER_DETECTED_FORCE_MODEपूर्ण,
	अणु38, ETHTOOL_LINK_EXT_STATE_AUTONEG,
		ETHTOOL_LINK_EXT_SUBSTATE_AN_FEC_MISMATCH_DURING_OVERRIDEपूर्ण,
	अणु39, ETHTOOL_LINK_EXT_STATE_AUTONEG,
		ETHTOOL_LINK_EXT_SUBSTATE_AN_NO_HCDपूर्ण,

	अणु5, ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
		ETHTOOL_LINK_EXT_SUBSTATE_LT_KR_FRAME_LOCK_NOT_ACQUIREDपूर्ण,
	अणु6, ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
		ETHTOOL_LINK_EXT_SUBSTATE_LT_KR_LINK_INHIBIT_TIMEOUTपूर्ण,
	अणु7, ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
		ETHTOOL_LINK_EXT_SUBSTATE_LT_KR_LINK_PARTNER_DID_NOT_SET_RECEIVER_READYपूर्ण,
	अणु8, ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE, 0पूर्ण,
	अणु14, ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE,
		ETHTOOL_LINK_EXT_SUBSTATE_LT_REMOTE_FAULTपूर्ण,

	अणु9, ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
		ETHTOOL_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_ACQUIRE_BLOCK_LOCKपूर्ण,
	अणु10, ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
		ETHTOOL_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_ACQUIRE_AM_LOCKपूर्ण,
	अणु11, ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
		ETHTOOL_LINK_EXT_SUBSTATE_LLM_PCS_DID_NOT_GET_ALIGN_STATUSपूर्ण,
	अणु12, ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
		ETHTOOL_LINK_EXT_SUBSTATE_LLM_FC_FEC_IS_NOT_LOCKEDपूर्ण,
	अणु13, ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH,
		ETHTOOL_LINK_EXT_SUBSTATE_LLM_RS_FEC_IS_NOT_LOCKEDपूर्ण,

	अणु15, ETHTOOL_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY, 0पूर्ण,
	अणु17, ETHTOOL_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY,
		ETHTOOL_LINK_EXT_SUBSTATE_BSI_LARGE_NUMBER_OF_PHYSICAL_ERRORSपूर्ण,
	अणु42, ETHTOOL_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY,
		ETHTOOL_LINK_EXT_SUBSTATE_BSI_UNSUPPORTED_RATEपूर्ण,

	अणु1024, ETHTOOL_LINK_EXT_STATE_NO_CABLE, 0पूर्ण,

	अणु16, ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE,
		ETHTOOL_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLEपूर्ण,
	अणु20, ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE,
		ETHTOOL_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLEपूर्ण,
	अणु29, ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE,
		ETHTOOL_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLEपूर्ण,
	अणु1025, ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE,
		ETHTOOL_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLEपूर्ण,
	अणु1029, ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE,
		ETHTOOL_LINK_EXT_SUBSTATE_CI_UNSUPPORTED_CABLEपूर्ण,
	अणु1031, ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE, 0पूर्ण,

	अणु1027, ETHTOOL_LINK_EXT_STATE_EEPROM_ISSUE, 0पूर्ण,

	अणु23, ETHTOOL_LINK_EXT_STATE_CALIBRATION_FAILURE, 0पूर्ण,

	अणु1032, ETHTOOL_LINK_EXT_STATE_POWER_BUDGET_EXCEEDED, 0पूर्ण,

	अणु1030, ETHTOOL_LINK_EXT_STATE_OVERHEAT, 0पूर्ण,
पूर्ण;

अटल व्योम
mlxsw_sp_port_set_link_ext_state(काष्ठा mlxsw_sp_ethtool_link_ext_state_opcode_mapping
				 link_ext_state_mapping,
				 काष्ठा ethtool_link_ext_state_info *link_ext_state_info)
अणु
	चयन (link_ext_state_mapping.link_ext_state) अणु
	हाल ETHTOOL_LINK_EXT_STATE_AUTONEG:
		link_ext_state_info->स्वतःneg =
			link_ext_state_mapping.link_ext_substate;
		अवरोध;
	हाल ETHTOOL_LINK_EXT_STATE_LINK_TRAINING_FAILURE:
		link_ext_state_info->link_training =
			link_ext_state_mapping.link_ext_substate;
		अवरोध;
	हाल ETHTOOL_LINK_EXT_STATE_LINK_LOGICAL_MISMATCH:
		link_ext_state_info->link_logical_mismatch =
			link_ext_state_mapping.link_ext_substate;
		अवरोध;
	हाल ETHTOOL_LINK_EXT_STATE_BAD_SIGNAL_INTEGRITY:
		link_ext_state_info->bad_संकेत_पूर्णांकegrity =
			link_ext_state_mapping.link_ext_substate;
		अवरोध;
	हाल ETHTOOL_LINK_EXT_STATE_CABLE_ISSUE:
		link_ext_state_info->cable_issue =
			link_ext_state_mapping.link_ext_substate;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	link_ext_state_info->link_ext_state = link_ext_state_mapping.link_ext_state;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_get_link_ext_state(काष्ठा net_device *dev,
				 काष्ठा ethtool_link_ext_state_info *link_ext_state_info)
अणु
	काष्ठा mlxsw_sp_ethtool_link_ext_state_opcode_mapping link_ext_state_mapping;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	अक्षर pddr_pl[MLXSW_REG_PDDR_LEN];
	पूर्णांक opcode, err, i;
	u32 status_opcode;

	अगर (netअगर_carrier_ok(dev))
		वापस -ENODATA;

	mlxsw_reg_pddr_pack(pddr_pl, mlxsw_sp_port->local_port,
			    MLXSW_REG_PDDR_PAGE_SELECT_TROUBLESHOOTING_INFO);

	opcode = MLXSW_REG_PDDR_TRBLSH_GROUP_OPCODE_MONITOR;
	mlxsw_reg_pddr_trblsh_group_opcode_set(pddr_pl, opcode);

	err = mlxsw_reg_query(mlxsw_sp_port->mlxsw_sp->core, MLXSW_REG(pddr),
			      pddr_pl);
	अगर (err)
		वापस err;

	status_opcode = mlxsw_reg_pddr_trblsh_status_opcode_get(pddr_pl);
	अगर (!status_opcode)
		वापस -ENODATA;

	क्रम (i = 0; i < ARRAY_SIZE(mlxsw_sp_link_ext_state_opcode_map); i++) अणु
		link_ext_state_mapping = mlxsw_sp_link_ext_state_opcode_map[i];
		अगर (link_ext_state_mapping.status_opcode == status_opcode) अणु
			mlxsw_sp_port_set_link_ext_state(link_ext_state_mapping,
							 link_ext_state_info);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENODATA;
पूर्ण

अटल व्योम mlxsw_sp_port_get_छोड़ोparam(काष्ठा net_device *dev,
					 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	छोड़ो->rx_छोड़ो = mlxsw_sp_port->link.rx_छोड़ो;
	छोड़ो->tx_छोड़ो = mlxsw_sp_port->link.tx_छोड़ो;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_छोड़ो_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	अक्षर pfcc_pl[MLXSW_REG_PFCC_LEN];

	mlxsw_reg_pfcc_pack(pfcc_pl, mlxsw_sp_port->local_port);
	mlxsw_reg_pfcc_pprx_set(pfcc_pl, छोड़ो->rx_छोड़ो);
	mlxsw_reg_pfcc_pptx_set(pfcc_pl, छोड़ो->tx_छोड़ो);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp_port->mlxsw_sp->core, MLXSW_REG(pfcc),
			       pfcc_pl);
पूर्ण

/* Maximum delay buffer needed in हाल of PAUSE frames. Similar to PFC delay, but is
 * measured in bytes. Assumes 100m cable and करोes not take पूर्णांकo account MTU.
 */
#घोषणा MLXSW_SP_PAUSE_DELAY_BYTES 19476

अटल पूर्णांक mlxsw_sp_port_set_छोड़ोparam(काष्ठा net_device *dev,
					काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	bool छोड़ो_en = छोड़ो->tx_छोड़ो || छोड़ो->rx_छोड़ो;
	काष्ठा mlxsw_sp_hdroom orig_hdroom;
	काष्ठा mlxsw_sp_hdroom hdroom;
	पूर्णांक prio;
	पूर्णांक err;

	अगर (mlxsw_sp_port->dcb.pfc && mlxsw_sp_port->dcb.pfc->pfc_en) अणु
		netdev_err(dev, "PFC already enabled on port\n");
		वापस -EINVAL;
	पूर्ण

	अगर (छोड़ो->स्वतःneg) अणु
		netdev_err(dev, "PAUSE frames autonegotiation isn't supported\n");
		वापस -EINVAL;
	पूर्ण

	orig_hdroom = *mlxsw_sp_port->hdroom;

	hdroom = orig_hdroom;
	अगर (छोड़ो_en)
		hdroom.delay_bytes = MLXSW_SP_PAUSE_DELAY_BYTES;
	अन्यथा
		hdroom.delay_bytes = 0;

	क्रम (prio = 0; prio < IEEE_8021QAZ_MAX_TCS; prio++)
		hdroom.prios.prio[prio].lossy = !छोड़ो_en;

	mlxsw_sp_hdroom_bufs_reset_lossiness(&hdroom);
	mlxsw_sp_hdroom_bufs_reset_sizes(mlxsw_sp_port, &hdroom);

	err = mlxsw_sp_hdroom_configure(mlxsw_sp_port, &hdroom);
	अगर (err) अणु
		netdev_err(dev, "Failed to configure port's headroom\n");
		वापस err;
	पूर्ण

	err = mlxsw_sp_port_छोड़ो_set(mlxsw_sp_port, छोड़ो);
	अगर (err) अणु
		netdev_err(dev, "Failed to set PAUSE parameters\n");
		जाओ err_port_छोड़ो_configure;
	पूर्ण

	mlxsw_sp_port->link.rx_छोड़ो = छोड़ो->rx_छोड़ो;
	mlxsw_sp_port->link.tx_छोड़ो = छोड़ो->tx_छोड़ो;

	वापस 0;

err_port_छोड़ो_configure:
	mlxsw_sp_hdroom_configure(mlxsw_sp_port, &orig_hdroom);
	वापस err;
पूर्ण

काष्ठा mlxsw_sp_port_hw_stats अणु
	अक्षर str[ETH_GSTRING_LEN];
	u64 (*getter)(स्थिर अक्षर *payload);
	bool cells_bytes;
पूर्ण;

अटल काष्ठा mlxsw_sp_port_hw_stats mlxsw_sp_port_hw_stats[] = अणु
	अणु
		.str = "a_frames_transmitted_ok",
		.getter = mlxsw_reg_ppcnt_a_frames_transmitted_ok_get,
	पूर्ण,
	अणु
		.str = "a_frames_received_ok",
		.getter = mlxsw_reg_ppcnt_a_frames_received_ok_get,
	पूर्ण,
	अणु
		.str = "a_frame_check_sequence_errors",
		.getter = mlxsw_reg_ppcnt_a_frame_check_sequence_errors_get,
	पूर्ण,
	अणु
		.str = "a_alignment_errors",
		.getter = mlxsw_reg_ppcnt_a_alignment_errors_get,
	पूर्ण,
	अणु
		.str = "a_octets_transmitted_ok",
		.getter = mlxsw_reg_ppcnt_a_octets_transmitted_ok_get,
	पूर्ण,
	अणु
		.str = "a_octets_received_ok",
		.getter = mlxsw_reg_ppcnt_a_octets_received_ok_get,
	पूर्ण,
	अणु
		.str = "a_multicast_frames_xmitted_ok",
		.getter = mlxsw_reg_ppcnt_a_multicast_frames_xmitted_ok_get,
	पूर्ण,
	अणु
		.str = "a_broadcast_frames_xmitted_ok",
		.getter = mlxsw_reg_ppcnt_a_broadcast_frames_xmitted_ok_get,
	पूर्ण,
	अणु
		.str = "a_multicast_frames_received_ok",
		.getter = mlxsw_reg_ppcnt_a_multicast_frames_received_ok_get,
	पूर्ण,
	अणु
		.str = "a_broadcast_frames_received_ok",
		.getter = mlxsw_reg_ppcnt_a_broadcast_frames_received_ok_get,
	पूर्ण,
	अणु
		.str = "a_in_range_length_errors",
		.getter = mlxsw_reg_ppcnt_a_in_range_length_errors_get,
	पूर्ण,
	अणु
		.str = "a_out_of_range_length_field",
		.getter = mlxsw_reg_ppcnt_a_out_of_range_length_field_get,
	पूर्ण,
	अणु
		.str = "a_frame_too_long_errors",
		.getter = mlxsw_reg_ppcnt_a_frame_too_दीर्घ_errors_get,
	पूर्ण,
	अणु
		.str = "a_symbol_error_during_carrier",
		.getter = mlxsw_reg_ppcnt_a_symbol_error_during_carrier_get,
	पूर्ण,
	अणु
		.str = "a_mac_control_frames_transmitted",
		.getter = mlxsw_reg_ppcnt_a_mac_control_frames_transmitted_get,
	पूर्ण,
	अणु
		.str = "a_mac_control_frames_received",
		.getter = mlxsw_reg_ppcnt_a_mac_control_frames_received_get,
	पूर्ण,
	अणु
		.str = "a_unsupported_opcodes_received",
		.getter = mlxsw_reg_ppcnt_a_unsupported_opcodes_received_get,
	पूर्ण,
	अणु
		.str = "a_pause_mac_ctrl_frames_received",
		.getter = mlxsw_reg_ppcnt_a_छोड़ो_mac_ctrl_frames_received_get,
	पूर्ण,
	अणु
		.str = "a_pause_mac_ctrl_frames_xmitted",
		.getter = mlxsw_reg_ppcnt_a_छोड़ो_mac_ctrl_frames_transmitted_get,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP_PORT_HW_STATS_LEN ARRAY_SIZE(mlxsw_sp_port_hw_stats)

अटल काष्ठा mlxsw_sp_port_hw_stats mlxsw_sp_port_hw_rfc_2863_stats[] = अणु
	अणु
		.str = "if_in_discards",
		.getter = mlxsw_reg_ppcnt_अगर_in_discards_get,
	पूर्ण,
	अणु
		.str = "if_out_discards",
		.getter = mlxsw_reg_ppcnt_अगर_out_discards_get,
	पूर्ण,
	अणु
		.str = "if_out_errors",
		.getter = mlxsw_reg_ppcnt_अगर_out_errors_get,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP_PORT_HW_RFC_2863_STATS_LEN \
	ARRAY_SIZE(mlxsw_sp_port_hw_rfc_2863_stats)

अटल काष्ठा mlxsw_sp_port_hw_stats mlxsw_sp_port_hw_rfc_2819_stats[] = अणु
	अणु
		.str = "ether_stats_undersize_pkts",
		.getter = mlxsw_reg_ppcnt_ether_stats_undersize_pkts_get,
	पूर्ण,
	अणु
		.str = "ether_stats_oversize_pkts",
		.getter = mlxsw_reg_ppcnt_ether_stats_oversize_pkts_get,
	पूर्ण,
	अणु
		.str = "ether_stats_fragments",
		.getter = mlxsw_reg_ppcnt_ether_stats_fragments_get,
	पूर्ण,
	अणु
		.str = "ether_pkts64octets",
		.getter = mlxsw_reg_ppcnt_ether_stats_pkts64octets_get,
	पूर्ण,
	अणु
		.str = "ether_pkts65to127octets",
		.getter = mlxsw_reg_ppcnt_ether_stats_pkts65to127octets_get,
	पूर्ण,
	अणु
		.str = "ether_pkts128to255octets",
		.getter = mlxsw_reg_ppcnt_ether_stats_pkts128to255octets_get,
	पूर्ण,
	अणु
		.str = "ether_pkts256to511octets",
		.getter = mlxsw_reg_ppcnt_ether_stats_pkts256to511octets_get,
	पूर्ण,
	अणु
		.str = "ether_pkts512to1023octets",
		.getter = mlxsw_reg_ppcnt_ether_stats_pkts512to1023octets_get,
	पूर्ण,
	अणु
		.str = "ether_pkts1024to1518octets",
		.getter = mlxsw_reg_ppcnt_ether_stats_pkts1024to1518octets_get,
	पूर्ण,
	अणु
		.str = "ether_pkts1519to2047octets",
		.getter = mlxsw_reg_ppcnt_ether_stats_pkts1519to2047octets_get,
	पूर्ण,
	अणु
		.str = "ether_pkts2048to4095octets",
		.getter = mlxsw_reg_ppcnt_ether_stats_pkts2048to4095octets_get,
	पूर्ण,
	अणु
		.str = "ether_pkts4096to8191octets",
		.getter = mlxsw_reg_ppcnt_ether_stats_pkts4096to8191octets_get,
	पूर्ण,
	अणु
		.str = "ether_pkts8192to10239octets",
		.getter = mlxsw_reg_ppcnt_ether_stats_pkts8192to10239octets_get,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP_PORT_HW_RFC_2819_STATS_LEN \
	ARRAY_SIZE(mlxsw_sp_port_hw_rfc_2819_stats)

अटल काष्ठा mlxsw_sp_port_hw_stats mlxsw_sp_port_hw_rfc_3635_stats[] = अणु
	अणु
		.str = "dot3stats_fcs_errors",
		.getter = mlxsw_reg_ppcnt_करोt3stats_fcs_errors_get,
	पूर्ण,
	अणु
		.str = "dot3stats_symbol_errors",
		.getter = mlxsw_reg_ppcnt_करोt3stats_symbol_errors_get,
	पूर्ण,
	अणु
		.str = "dot3control_in_unknown_opcodes",
		.getter = mlxsw_reg_ppcnt_करोt3control_in_unknown_opcodes_get,
	पूर्ण,
	अणु
		.str = "dot3in_pause_frames",
		.getter = mlxsw_reg_ppcnt_करोt3in_छोड़ो_frames_get,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP_PORT_HW_RFC_3635_STATS_LEN \
	ARRAY_SIZE(mlxsw_sp_port_hw_rfc_3635_stats)

अटल काष्ठा mlxsw_sp_port_hw_stats mlxsw_sp_port_hw_ext_stats[] = अणु
	अणु
		.str = "ecn_marked",
		.getter = mlxsw_reg_ppcnt_ecn_marked_get,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP_PORT_HW_EXT_STATS_LEN ARRAY_SIZE(mlxsw_sp_port_hw_ext_stats)

अटल काष्ठा mlxsw_sp_port_hw_stats mlxsw_sp_port_hw_discard_stats[] = अणु
	अणु
		.str = "discard_ingress_general",
		.getter = mlxsw_reg_ppcnt_ingress_general_get,
	पूर्ण,
	अणु
		.str = "discard_ingress_policy_engine",
		.getter = mlxsw_reg_ppcnt_ingress_policy_engine_get,
	पूर्ण,
	अणु
		.str = "discard_ingress_vlan_membership",
		.getter = mlxsw_reg_ppcnt_ingress_vlan_membership_get,
	पूर्ण,
	अणु
		.str = "discard_ingress_tag_frame_type",
		.getter = mlxsw_reg_ppcnt_ingress_tag_frame_type_get,
	पूर्ण,
	अणु
		.str = "discard_egress_vlan_membership",
		.getter = mlxsw_reg_ppcnt_egress_vlan_membership_get,
	पूर्ण,
	अणु
		.str = "discard_loopback_filter",
		.getter = mlxsw_reg_ppcnt_loopback_filter_get,
	पूर्ण,
	अणु
		.str = "discard_egress_general",
		.getter = mlxsw_reg_ppcnt_egress_general_get,
	पूर्ण,
	अणु
		.str = "discard_egress_hoq",
		.getter = mlxsw_reg_ppcnt_egress_hoq_get,
	पूर्ण,
	अणु
		.str = "discard_egress_policy_engine",
		.getter = mlxsw_reg_ppcnt_egress_policy_engine_get,
	पूर्ण,
	अणु
		.str = "discard_ingress_tx_link_down",
		.getter = mlxsw_reg_ppcnt_ingress_tx_link_करोwn_get,
	पूर्ण,
	अणु
		.str = "discard_egress_stp_filter",
		.getter = mlxsw_reg_ppcnt_egress_stp_filter_get,
	पूर्ण,
	अणु
		.str = "discard_egress_sll",
		.getter = mlxsw_reg_ppcnt_egress_sll_get,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP_PORT_HW_DISCARD_STATS_LEN \
	ARRAY_SIZE(mlxsw_sp_port_hw_discard_stats)

अटल काष्ठा mlxsw_sp_port_hw_stats mlxsw_sp_port_hw_prio_stats[] = अणु
	अणु
		.str = "rx_octets_prio",
		.getter = mlxsw_reg_ppcnt_rx_octets_get,
	पूर्ण,
	अणु
		.str = "rx_frames_prio",
		.getter = mlxsw_reg_ppcnt_rx_frames_get,
	पूर्ण,
	अणु
		.str = "tx_octets_prio",
		.getter = mlxsw_reg_ppcnt_tx_octets_get,
	पूर्ण,
	अणु
		.str = "tx_frames_prio",
		.getter = mlxsw_reg_ppcnt_tx_frames_get,
	पूर्ण,
	अणु
		.str = "rx_pause_prio",
		.getter = mlxsw_reg_ppcnt_rx_छोड़ो_get,
	पूर्ण,
	अणु
		.str = "rx_pause_duration_prio",
		.getter = mlxsw_reg_ppcnt_rx_छोड़ो_duration_get,
	पूर्ण,
	अणु
		.str = "tx_pause_prio",
		.getter = mlxsw_reg_ppcnt_tx_छोड़ो_get,
	पूर्ण,
	अणु
		.str = "tx_pause_duration_prio",
		.getter = mlxsw_reg_ppcnt_tx_छोड़ो_duration_get,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP_PORT_HW_PRIO_STATS_LEN ARRAY_SIZE(mlxsw_sp_port_hw_prio_stats)

अटल काष्ठा mlxsw_sp_port_hw_stats mlxsw_sp_port_hw_tc_stats[] = अणु
	अणु
		.str = "tc_transmit_queue_tc",
		.getter = mlxsw_reg_ppcnt_tc_transmit_queue_get,
		.cells_bytes = true,
	पूर्ण,
	अणु
		.str = "tc_no_buffer_discard_uc_tc",
		.getter = mlxsw_reg_ppcnt_tc_no_buffer_discard_uc_get,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP_PORT_HW_TC_STATS_LEN ARRAY_SIZE(mlxsw_sp_port_hw_tc_stats)

काष्ठा mlxsw_sp_port_stats अणु
	अक्षर str[ETH_GSTRING_LEN];
	u64 (*getter)(काष्ठा mlxsw_sp_port *mlxsw_sp_port);
पूर्ण;

अटल u64
mlxsw_sp_port_get_transceiver_overheat_stats(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp_port_mapping port_mapping = mlxsw_sp_port->mapping;
	काष्ठा mlxsw_core *mlxsw_core = mlxsw_sp_port->mlxsw_sp->core;
	u64 stats;
	पूर्णांक err;

	err = mlxsw_env_module_overheat_counter_get(mlxsw_core,
						    port_mapping.module,
						    &stats);
	अगर (err)
		वापस mlxsw_sp_port->module_overheat_initial_val;

	वापस stats - mlxsw_sp_port->module_overheat_initial_val;
पूर्ण

अटल काष्ठा mlxsw_sp_port_stats mlxsw_sp_port_transceiver_stats[] = अणु
	अणु
		.str = "transceiver_overheat",
		.getter = mlxsw_sp_port_get_transceiver_overheat_stats,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP_PORT_HW_TRANSCEIVER_STATS_LEN ARRAY_SIZE(mlxsw_sp_port_transceiver_stats)

#घोषणा MLXSW_SP_PORT_ETHTOOL_STATS_LEN (MLXSW_SP_PORT_HW_STATS_LEN + \
					 MLXSW_SP_PORT_HW_RFC_2863_STATS_LEN + \
					 MLXSW_SP_PORT_HW_RFC_2819_STATS_LEN + \
					 MLXSW_SP_PORT_HW_RFC_3635_STATS_LEN + \
					 MLXSW_SP_PORT_HW_EXT_STATS_LEN + \
					 MLXSW_SP_PORT_HW_DISCARD_STATS_LEN + \
					 (MLXSW_SP_PORT_HW_PRIO_STATS_LEN * \
					  IEEE_8021QAZ_MAX_TCS) + \
					 (MLXSW_SP_PORT_HW_TC_STATS_LEN * \
					  TC_MAX_QUEUE) + \
					  MLXSW_SP_PORT_HW_TRANSCEIVER_STATS_LEN)

अटल व्योम mlxsw_sp_port_get_prio_strings(u8 **p, पूर्णांक prio)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP_PORT_HW_PRIO_STATS_LEN; i++) अणु
		snम_लिखो(*p, ETH_GSTRING_LEN, "%.29s_%.1d",
			 mlxsw_sp_port_hw_prio_stats[i].str, prio);
		*p += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_port_get_tc_strings(u8 **p, पूर्णांक tc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP_PORT_HW_TC_STATS_LEN; i++) अणु
		snम_लिखो(*p, ETH_GSTRING_LEN, "%.29s_%.1d",
			 mlxsw_sp_port_hw_tc_stats[i].str, tc);
		*p += ETH_GSTRING_LEN;
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_port_get_strings(काष्ठा net_device *dev,
				      u32 stringset, u8 *data)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < MLXSW_SP_PORT_HW_STATS_LEN; i++) अणु
			स_नकल(p, mlxsw_sp_port_hw_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण

		क्रम (i = 0; i < MLXSW_SP_PORT_HW_RFC_2863_STATS_LEN; i++) अणु
			स_नकल(p, mlxsw_sp_port_hw_rfc_2863_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण

		क्रम (i = 0; i < MLXSW_SP_PORT_HW_RFC_2819_STATS_LEN; i++) अणु
			स_नकल(p, mlxsw_sp_port_hw_rfc_2819_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण

		क्रम (i = 0; i < MLXSW_SP_PORT_HW_RFC_3635_STATS_LEN; i++) अणु
			स_नकल(p, mlxsw_sp_port_hw_rfc_3635_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण

		क्रम (i = 0; i < MLXSW_SP_PORT_HW_EXT_STATS_LEN; i++) अणु
			स_नकल(p, mlxsw_sp_port_hw_ext_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण

		क्रम (i = 0; i < MLXSW_SP_PORT_HW_DISCARD_STATS_LEN; i++) अणु
			स_नकल(p, mlxsw_sp_port_hw_discard_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण

		क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
			mlxsw_sp_port_get_prio_strings(&p, i);

		क्रम (i = 0; i < TC_MAX_QUEUE; i++)
			mlxsw_sp_port_get_tc_strings(&p, i);

		mlxsw_sp_port->mlxsw_sp->ptp_ops->get_stats_strings(&p);

		क्रम (i = 0; i < MLXSW_SP_PORT_HW_TRANSCEIVER_STATS_LEN; i++) अणु
			स_नकल(p, mlxsw_sp_port_transceiver_stats[i].str,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_port_set_phys_id(काष्ठा net_device *dev,
				     क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर mlcr_pl[MLXSW_REG_MLCR_LEN];
	bool active;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		active = true;
		अवरोध;
	हाल ETHTOOL_ID_INACTIVE:
		active = false;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	mlxsw_reg_mlcr_pack(mlcr_pl, mlxsw_sp_port->local_port, active);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(mlcr), mlcr_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_get_hw_stats_by_group(काष्ठा mlxsw_sp_port_hw_stats **p_hw_stats,
			       पूर्णांक *p_len, क्रमागत mlxsw_reg_ppcnt_grp grp)
अणु
	चयन (grp) अणु
	हाल MLXSW_REG_PPCNT_IEEE_8023_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_stats;
		*p_len = MLXSW_SP_PORT_HW_STATS_LEN;
		अवरोध;
	हाल MLXSW_REG_PPCNT_RFC_2863_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_rfc_2863_stats;
		*p_len = MLXSW_SP_PORT_HW_RFC_2863_STATS_LEN;
		अवरोध;
	हाल MLXSW_REG_PPCNT_RFC_2819_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_rfc_2819_stats;
		*p_len = MLXSW_SP_PORT_HW_RFC_2819_STATS_LEN;
		अवरोध;
	हाल MLXSW_REG_PPCNT_RFC_3635_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_rfc_3635_stats;
		*p_len = MLXSW_SP_PORT_HW_RFC_3635_STATS_LEN;
		अवरोध;
	हाल MLXSW_REG_PPCNT_EXT_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_ext_stats;
		*p_len = MLXSW_SP_PORT_HW_EXT_STATS_LEN;
		अवरोध;
	हाल MLXSW_REG_PPCNT_DISCARD_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_discard_stats;
		*p_len = MLXSW_SP_PORT_HW_DISCARD_STATS_LEN;
		अवरोध;
	हाल MLXSW_REG_PPCNT_PRIO_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_prio_stats;
		*p_len = MLXSW_SP_PORT_HW_PRIO_STATS_LEN;
		अवरोध;
	हाल MLXSW_REG_PPCNT_TC_CNT:
		*p_hw_stats = mlxsw_sp_port_hw_tc_stats;
		*p_len = MLXSW_SP_PORT_HW_TC_STATS_LEN;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __mlxsw_sp_port_get_stats(काष्ठा net_device *dev,
				      क्रमागत mlxsw_reg_ppcnt_grp grp, पूर्णांक prio,
				      u64 *data, पूर्णांक data_index)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_port_hw_stats *hw_stats;
	अक्षर ppcnt_pl[MLXSW_REG_PPCNT_LEN];
	पूर्णांक i, len;
	पूर्णांक err;

	err = mlxsw_sp_get_hw_stats_by_group(&hw_stats, &len, grp);
	अगर (err)
		वापस;
	mlxsw_sp_port_get_stats_raw(dev, grp, prio, ppcnt_pl);
	क्रम (i = 0; i < len; i++) अणु
		data[data_index + i] = hw_stats[i].getter(ppcnt_pl);
		अगर (!hw_stats[i].cells_bytes)
			जारी;
		data[data_index + i] = mlxsw_sp_cells_bytes(mlxsw_sp,
							    data[data_index + i]);
	पूर्ण
पूर्ण

अटल व्योम __mlxsw_sp_port_get_env_stats(काष्ठा net_device *dev, u64 *data, पूर्णांक data_index,
					  काष्ठा mlxsw_sp_port_stats *port_stats,
					  पूर्णांक len)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		data[data_index + i] = port_stats[i].getter(mlxsw_sp_port);
पूर्ण

अटल व्योम mlxsw_sp_port_get_stats(काष्ठा net_device *dev,
				    काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	पूर्णांक i, data_index = 0;

	/* IEEE 802.3 Counters */
	__mlxsw_sp_port_get_stats(dev, MLXSW_REG_PPCNT_IEEE_8023_CNT, 0,
				  data, data_index);
	data_index = MLXSW_SP_PORT_HW_STATS_LEN;

	/* RFC 2863 Counters */
	__mlxsw_sp_port_get_stats(dev, MLXSW_REG_PPCNT_RFC_2863_CNT, 0,
				  data, data_index);
	data_index += MLXSW_SP_PORT_HW_RFC_2863_STATS_LEN;

	/* RFC 2819 Counters */
	__mlxsw_sp_port_get_stats(dev, MLXSW_REG_PPCNT_RFC_2819_CNT, 0,
				  data, data_index);
	data_index += MLXSW_SP_PORT_HW_RFC_2819_STATS_LEN;

	/* RFC 3635 Counters */
	__mlxsw_sp_port_get_stats(dev, MLXSW_REG_PPCNT_RFC_3635_CNT, 0,
				  data, data_index);
	data_index += MLXSW_SP_PORT_HW_RFC_3635_STATS_LEN;

	/* Extended Counters */
	__mlxsw_sp_port_get_stats(dev, MLXSW_REG_PPCNT_EXT_CNT, 0,
				  data, data_index);
	data_index += MLXSW_SP_PORT_HW_EXT_STATS_LEN;

	/* Discard Counters */
	__mlxsw_sp_port_get_stats(dev, MLXSW_REG_PPCNT_DISCARD_CNT, 0,
				  data, data_index);
	data_index += MLXSW_SP_PORT_HW_DISCARD_STATS_LEN;

	/* Per-Priority Counters */
	क्रम (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) अणु
		__mlxsw_sp_port_get_stats(dev, MLXSW_REG_PPCNT_PRIO_CNT, i,
					  data, data_index);
		data_index += MLXSW_SP_PORT_HW_PRIO_STATS_LEN;
	पूर्ण

	/* Per-TC Counters */
	क्रम (i = 0; i < TC_MAX_QUEUE; i++) अणु
		__mlxsw_sp_port_get_stats(dev, MLXSW_REG_PPCNT_TC_CNT, i,
					  data, data_index);
		data_index += MLXSW_SP_PORT_HW_TC_STATS_LEN;
	पूर्ण

	/* PTP counters */
	mlxsw_sp_port->mlxsw_sp->ptp_ops->get_stats(mlxsw_sp_port,
						    data, data_index);
	data_index += mlxsw_sp_port->mlxsw_sp->ptp_ops->get_stats_count();

	/* Transceiver counters */
	__mlxsw_sp_port_get_env_stats(dev, data, data_index, mlxsw_sp_port_transceiver_stats,
				      MLXSW_SP_PORT_HW_TRANSCEIVER_STATS_LEN);
	data_index += MLXSW_SP_PORT_HW_TRANSCEIVER_STATS_LEN;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस MLXSW_SP_PORT_ETHTOOL_STATS_LEN +
			mlxsw_sp_port->mlxsw_sp->ptp_ops->get_stats_count();
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_port_get_link_supported(काष्ठा mlxsw_sp *mlxsw_sp, u32 eth_proto_cap,
				 काष्ठा ethtool_link_ksettings *cmd)
अणु
	स्थिर काष्ठा mlxsw_sp_port_type_speed_ops *ops;

	ops = mlxsw_sp->port_type_speed_ops;

	ethtool_link_ksettings_add_link_mode(cmd, supported, Asym_Pause);
	ethtool_link_ksettings_add_link_mode(cmd, supported, Autoneg);
	ethtool_link_ksettings_add_link_mode(cmd, supported, Pause);

	ops->from_ptys_supported_port(mlxsw_sp, eth_proto_cap, cmd);
	ops->from_ptys_link(mlxsw_sp, eth_proto_cap,
			    cmd->link_modes.supported);
पूर्ण

अटल व्योम
mlxsw_sp_port_get_link_advertise(काष्ठा mlxsw_sp *mlxsw_sp,
				 u32 eth_proto_admin, bool स्वतःneg,
				 काष्ठा ethtool_link_ksettings *cmd)
अणु
	स्थिर काष्ठा mlxsw_sp_port_type_speed_ops *ops;

	ops = mlxsw_sp->port_type_speed_ops;

	अगर (!स्वतःneg)
		वापस;

	ethtool_link_ksettings_add_link_mode(cmd, advertising, Autoneg);
	ops->from_ptys_link(mlxsw_sp, eth_proto_admin,
			    cmd->link_modes.advertising);
पूर्ण

अटल u8
mlxsw_sp_port_connector_port(क्रमागत mlxsw_reg_ptys_connector_type connector_type)
अणु
	चयन (connector_type) अणु
	हाल MLXSW_REG_PTYS_CONNECTOR_TYPE_UNKNOWN_OR_NO_CONNECTOR:
		वापस PORT_OTHER;
	हाल MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_NONE:
		वापस PORT_NONE;
	हाल MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_TP:
		वापस PORT_TP;
	हाल MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_AUI:
		वापस PORT_AUI;
	हाल MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_BNC:
		वापस PORT_BNC;
	हाल MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_MII:
		वापस PORT_MII;
	हाल MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_FIBRE:
		वापस PORT_FIBRE;
	हाल MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_DA:
		वापस PORT_DA;
	हाल MLXSW_REG_PTYS_CONNECTOR_TYPE_PORT_OTHER:
		वापस PORT_OTHER;
	शेष:
		WARN_ON_ONCE(1);
		वापस PORT_OTHER;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_port_ptys_query(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    u32 *p_eth_proto_cap, u32 *p_eth_proto_admin,
				    u32 *p_eth_proto_oper, u8 *p_connector_type)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	स्थिर काष्ठा mlxsw_sp_port_type_speed_ops *ops;
	अक्षर ptys_pl[MLXSW_REG_PTYS_LEN];
	पूर्णांक err;

	ops = mlxsw_sp->port_type_speed_ops;

	ops->reg_ptys_eth_pack(mlxsw_sp, ptys_pl, mlxsw_sp_port->local_port, 0, false);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ptys), ptys_pl);
	अगर (err)
		वापस err;

	ops->reg_ptys_eth_unpack(mlxsw_sp, ptys_pl, p_eth_proto_cap, p_eth_proto_admin,
				 p_eth_proto_oper);
	अगर (p_connector_type)
		*p_connector_type = mlxsw_reg_ptys_connector_type_get(ptys_pl);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_get_link_ksettings(काष्ठा net_device *dev,
					    काष्ठा ethtool_link_ksettings *cmd)
अणु
	u32 eth_proto_cap, eth_proto_admin, eth_proto_oper;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	स्थिर काष्ठा mlxsw_sp_port_type_speed_ops *ops;
	u8 connector_type;
	bool स्वतःneg;
	पूर्णांक err;

	err = mlxsw_sp_port_ptys_query(mlxsw_sp_port, &eth_proto_cap, &eth_proto_admin,
				       &eth_proto_oper, &connector_type);
	अगर (err)
		वापस err;

	ops = mlxsw_sp->port_type_speed_ops;
	स्वतःneg = mlxsw_sp_port->link.स्वतःneg;

	mlxsw_sp_port_get_link_supported(mlxsw_sp, eth_proto_cap, cmd);

	mlxsw_sp_port_get_link_advertise(mlxsw_sp, eth_proto_admin, स्वतःneg, cmd);

	cmd->base.स्वतःneg = स्वतःneg ? AUTONEG_ENABLE : AUTONEG_DISABLE;
	cmd->base.port = mlxsw_sp_port_connector_port(connector_type);
	ops->from_ptys_link_mode(mlxsw_sp, netअगर_carrier_ok(dev),
				 eth_proto_oper, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_set_link_ksettings(काष्ठा net_device *dev,
				 स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	स्थिर काष्ठा mlxsw_sp_port_type_speed_ops *ops;
	अक्षर ptys_pl[MLXSW_REG_PTYS_LEN];
	u32 eth_proto_cap, eth_proto_new;
	bool स्वतःneg;
	पूर्णांक err;

	ops = mlxsw_sp->port_type_speed_ops;

	ops->reg_ptys_eth_pack(mlxsw_sp, ptys_pl, mlxsw_sp_port->local_port,
			       0, false);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ptys), ptys_pl);
	अगर (err)
		वापस err;
	ops->reg_ptys_eth_unpack(mlxsw_sp, ptys_pl, &eth_proto_cap, शून्य, शून्य);

	स्वतःneg = cmd->base.स्वतःneg == AUTONEG_ENABLE;
	eth_proto_new = स्वतःneg ?
		ops->to_ptys_advert_link(mlxsw_sp, cmd) :
		ops->to_ptys_speed_lanes(mlxsw_sp, mlxsw_sp_port->mapping.width,
					 cmd);

	eth_proto_new = eth_proto_new & eth_proto_cap;
	अगर (!eth_proto_new) अणु
		netdev_err(dev, "No supported speed or lanes requested\n");
		वापस -EINVAL;
	पूर्ण

	ops->reg_ptys_eth_pack(mlxsw_sp, ptys_pl, mlxsw_sp_port->local_port,
			       eth_proto_new, स्वतःneg);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ptys), ptys_pl);
	अगर (err)
		वापस err;

	mlxsw_sp_port->link.स्वतःneg = स्वतःneg;

	अगर (!netअगर_running(dev))
		वापस 0;

	mlxsw_sp_port_admin_status_set(mlxsw_sp_port, false);
	mlxsw_sp_port_admin_status_set(mlxsw_sp_port, true);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_get_module_info(काष्ठा net_device *netdev,
				    काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(netdev);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	पूर्णांक err;

	err = mlxsw_env_get_module_info(mlxsw_sp->core,
					mlxsw_sp_port->mapping.module,
					modinfo);

	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_get_module_eeprom(काष्ठा net_device *netdev,
				      काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(netdev);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	पूर्णांक err;

	err = mlxsw_env_get_module_eeprom(netdev, mlxsw_sp->core,
					  mlxsw_sp_port->mapping.module, ee,
					  data);

	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_get_ts_info(काष्ठा net_device *netdev, काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(netdev);
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;

	वापस mlxsw_sp->ptp_ops->get_ts_info(mlxsw_sp, info);
पूर्ण

अटल व्योम
mlxsw_sp_get_eth_phy_stats(काष्ठा net_device *dev,
			   काष्ठा ethtool_eth_phy_stats *phy_stats)
अणु
	अक्षर ppcnt_pl[MLXSW_REG_PPCNT_LEN];

	अगर (mlxsw_sp_port_get_stats_raw(dev, MLXSW_REG_PPCNT_IEEE_8023_CNT,
					0, ppcnt_pl))
		वापस;

	phy_stats->SymbolErrorDuringCarrier =
		mlxsw_reg_ppcnt_a_symbol_error_during_carrier_get(ppcnt_pl);
पूर्ण

अटल व्योम
mlxsw_sp_get_eth_mac_stats(काष्ठा net_device *dev,
			   काष्ठा ethtool_eth_mac_stats *mac_stats)
अणु
	अक्षर ppcnt_pl[MLXSW_REG_PPCNT_LEN];

	अगर (mlxsw_sp_port_get_stats_raw(dev, MLXSW_REG_PPCNT_IEEE_8023_CNT,
					0, ppcnt_pl))
		वापस;

	mac_stats->FramesTransmittedOK =
		mlxsw_reg_ppcnt_a_frames_transmitted_ok_get(ppcnt_pl);
	mac_stats->FramesReceivedOK =
		mlxsw_reg_ppcnt_a_frames_received_ok_get(ppcnt_pl);
	mac_stats->FrameCheckSequenceErrors =
		mlxsw_reg_ppcnt_a_frame_check_sequence_errors_get(ppcnt_pl);
	mac_stats->AlignmentErrors =
		mlxsw_reg_ppcnt_a_alignment_errors_get(ppcnt_pl);
	mac_stats->OctetsTransmittedOK =
		mlxsw_reg_ppcnt_a_octets_transmitted_ok_get(ppcnt_pl);
	mac_stats->OctetsReceivedOK =
		mlxsw_reg_ppcnt_a_octets_received_ok_get(ppcnt_pl);
	mac_stats->MulticastFramesXmittedOK =
		mlxsw_reg_ppcnt_a_multicast_frames_xmitted_ok_get(ppcnt_pl);
	mac_stats->BroadcastFramesXmittedOK =
		mlxsw_reg_ppcnt_a_broadcast_frames_xmitted_ok_get(ppcnt_pl);
	mac_stats->MulticastFramesReceivedOK =
		mlxsw_reg_ppcnt_a_multicast_frames_received_ok_get(ppcnt_pl);
	mac_stats->BroadcastFramesReceivedOK =
		mlxsw_reg_ppcnt_a_broadcast_frames_received_ok_get(ppcnt_pl);
	mac_stats->InRangeLengthErrors =
		mlxsw_reg_ppcnt_a_in_range_length_errors_get(ppcnt_pl);
	mac_stats->OutOfRangeLengthField =
		mlxsw_reg_ppcnt_a_out_of_range_length_field_get(ppcnt_pl);
	mac_stats->FrameTooLongErrors =
		mlxsw_reg_ppcnt_a_frame_too_दीर्घ_errors_get(ppcnt_pl);
पूर्ण

अटल व्योम
mlxsw_sp_get_eth_ctrl_stats(काष्ठा net_device *dev,
			    काष्ठा ethtool_eth_ctrl_stats *ctrl_stats)
अणु
	अक्षर ppcnt_pl[MLXSW_REG_PPCNT_LEN];

	अगर (mlxsw_sp_port_get_stats_raw(dev, MLXSW_REG_PPCNT_IEEE_8023_CNT,
					0, ppcnt_pl))
		वापस;

	ctrl_stats->MACControlFramesTransmitted =
		mlxsw_reg_ppcnt_a_mac_control_frames_transmitted_get(ppcnt_pl);
	ctrl_stats->MACControlFramesReceived =
		mlxsw_reg_ppcnt_a_mac_control_frames_received_get(ppcnt_pl);
	ctrl_stats->UnsupportedOpcodesReceived =
		mlxsw_reg_ppcnt_a_unsupported_opcodes_received_get(ppcnt_pl);
पूर्ण

अटल स्थिर काष्ठा ethtool_rmon_hist_range mlxsw_rmon_ranges[] = अणु
	अणु    0,    64 पूर्ण,
	अणु   65,   127 पूर्ण,
	अणु  128,   255 पूर्ण,
	अणु  256,   511 पूर्ण,
	अणु  512,  1023 पूर्ण,
	अणु 1024,  1518 पूर्ण,
	अणु 1519,  2047 पूर्ण,
	अणु 2048,  4095 पूर्ण,
	अणु 4096,  8191 पूर्ण,
	अणु 8192, 10239 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
mlxsw_sp_get_rmon_stats(काष्ठा net_device *dev,
			काष्ठा ethtool_rmon_stats *rmon,
			स्थिर काष्ठा ethtool_rmon_hist_range **ranges)
अणु
	अक्षर ppcnt_pl[MLXSW_REG_PPCNT_LEN];

	अगर (mlxsw_sp_port_get_stats_raw(dev, MLXSW_REG_PPCNT_RFC_2819_CNT,
					0, ppcnt_pl))
		वापस;

	rmon->undersize_pkts =
		mlxsw_reg_ppcnt_ether_stats_undersize_pkts_get(ppcnt_pl);
	rmon->oversize_pkts =
		mlxsw_reg_ppcnt_ether_stats_oversize_pkts_get(ppcnt_pl);
	rmon->fragments =
		mlxsw_reg_ppcnt_ether_stats_fragments_get(ppcnt_pl);

	rmon->hist[0] = mlxsw_reg_ppcnt_ether_stats_pkts64octets_get(ppcnt_pl);
	rmon->hist[1] =
		mlxsw_reg_ppcnt_ether_stats_pkts65to127octets_get(ppcnt_pl);
	rmon->hist[2] =
		mlxsw_reg_ppcnt_ether_stats_pkts128to255octets_get(ppcnt_pl);
	rmon->hist[3] =
		mlxsw_reg_ppcnt_ether_stats_pkts256to511octets_get(ppcnt_pl);
	rmon->hist[4] =
		mlxsw_reg_ppcnt_ether_stats_pkts512to1023octets_get(ppcnt_pl);
	rmon->hist[5] =
		mlxsw_reg_ppcnt_ether_stats_pkts1024to1518octets_get(ppcnt_pl);
	rmon->hist[6] =
		mlxsw_reg_ppcnt_ether_stats_pkts1519to2047octets_get(ppcnt_pl);
	rmon->hist[7] =
		mlxsw_reg_ppcnt_ether_stats_pkts2048to4095octets_get(ppcnt_pl);
	rmon->hist[8] =
		mlxsw_reg_ppcnt_ether_stats_pkts4096to8191octets_get(ppcnt_pl);
	rmon->hist[9] =
		mlxsw_reg_ppcnt_ether_stats_pkts8192to10239octets_get(ppcnt_pl);

	*ranges = mlxsw_rmon_ranges;
पूर्ण

स्थिर काष्ठा ethtool_ops mlxsw_sp_port_ethtool_ops = अणु
	.cap_link_lanes_supported	= true,
	.get_drvinfo			= mlxsw_sp_port_get_drvinfo,
	.get_link			= ethtool_op_get_link,
	.get_link_ext_state		= mlxsw_sp_port_get_link_ext_state,
	.get_छोड़ोparam			= mlxsw_sp_port_get_छोड़ोparam,
	.set_छोड़ोparam			= mlxsw_sp_port_set_छोड़ोparam,
	.get_strings			= mlxsw_sp_port_get_strings,
	.set_phys_id			= mlxsw_sp_port_set_phys_id,
	.get_ethtool_stats		= mlxsw_sp_port_get_stats,
	.get_sset_count			= mlxsw_sp_port_get_sset_count,
	.get_link_ksettings		= mlxsw_sp_port_get_link_ksettings,
	.set_link_ksettings		= mlxsw_sp_port_set_link_ksettings,
	.get_module_info		= mlxsw_sp_get_module_info,
	.get_module_eeprom		= mlxsw_sp_get_module_eeprom,
	.get_ts_info			= mlxsw_sp_get_ts_info,
	.get_eth_phy_stats		= mlxsw_sp_get_eth_phy_stats,
	.get_eth_mac_stats		= mlxsw_sp_get_eth_mac_stats,
	.get_eth_ctrl_stats		= mlxsw_sp_get_eth_ctrl_stats,
	.get_rmon_stats			= mlxsw_sp_get_rmon_stats,
पूर्ण;

काष्ठा mlxsw_sp1_port_link_mode अणु
	क्रमागत ethtool_link_mode_bit_indices mask_ethtool;
	u32 mask;
	u32 speed;
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp1_port_link_mode mlxsw_sp1_port_link_mode[] = अणु
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_SGMII |
				  MLXSW_REG_PTYS_ETH_SPEED_1000BASE_KX,
		.mask_ethtool	= ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
		.speed		= SPEED_1000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_10GBASE_CX4 |
				  MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KX4,
		.mask_ethtool	= ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT,
		.speed		= SPEED_10000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KR |
				  MLXSW_REG_PTYS_ETH_SPEED_10GBASE_CR |
				  MLXSW_REG_PTYS_ETH_SPEED_10GBASE_SR |
				  MLXSW_REG_PTYS_ETH_SPEED_10GBASE_ER_LR,
		.mask_ethtool	= ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
		.speed		= SPEED_10000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_40GBASE_CR4,
		.mask_ethtool	= ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT,
		.speed		= SPEED_40000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_40GBASE_KR4,
		.mask_ethtool	= ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT,
		.speed		= SPEED_40000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_40GBASE_SR4,
		.mask_ethtool	= ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT,
		.speed		= SPEED_40000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_40GBASE_LR4_ER4,
		.mask_ethtool	= ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT,
		.speed		= SPEED_40000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_25GBASE_CR,
		.mask_ethtool	= ETHTOOL_LINK_MODE_25000baseCR_Full_BIT,
		.speed		= SPEED_25000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_25GBASE_KR,
		.mask_ethtool	= ETHTOOL_LINK_MODE_25000baseKR_Full_BIT,
		.speed		= SPEED_25000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_25GBASE_SR,
		.mask_ethtool	= ETHTOOL_LINK_MODE_25000baseSR_Full_BIT,
		.speed		= SPEED_25000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_50GBASE_CR2,
		.mask_ethtool	= ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT,
		.speed		= SPEED_50000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_50GBASE_KR2,
		.mask_ethtool	= ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT,
		.speed		= SPEED_50000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_50GBASE_SR2,
		.mask_ethtool	= ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT,
		.speed		= SPEED_50000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_100GBASE_CR4,
		.mask_ethtool	= ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT,
		.speed		= SPEED_100000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_100GBASE_SR4,
		.mask_ethtool	= ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT,
		.speed		= SPEED_100000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_100GBASE_KR4,
		.mask_ethtool	= ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT,
		.speed		= SPEED_100000,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_ETH_SPEED_100GBASE_LR4_ER4,
		.mask_ethtool	= ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT,
		.speed		= SPEED_100000,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP1_PORT_LINK_MODE_LEN ARRAY_SIZE(mlxsw_sp1_port_link_mode)

अटल व्योम
mlxsw_sp1_from_ptys_supported_port(काष्ठा mlxsw_sp *mlxsw_sp,
				   u32 ptys_eth_proto,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	अगर (ptys_eth_proto & (MLXSW_REG_PTYS_ETH_SPEED_10GBASE_CR |
			      MLXSW_REG_PTYS_ETH_SPEED_10GBASE_SR |
			      MLXSW_REG_PTYS_ETH_SPEED_40GBASE_CR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_40GBASE_SR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_100GBASE_SR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_SGMII))
		ethtool_link_ksettings_add_link_mode(cmd, supported, FIBRE);

	अगर (ptys_eth_proto & (MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KR |
			      MLXSW_REG_PTYS_ETH_SPEED_10GBASE_KX4 |
			      MLXSW_REG_PTYS_ETH_SPEED_40GBASE_KR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_100GBASE_KR4 |
			      MLXSW_REG_PTYS_ETH_SPEED_1000BASE_KX))
		ethtool_link_ksettings_add_link_mode(cmd, supported, Backplane);
पूर्ण

अटल व्योम
mlxsw_sp1_from_ptys_link(काष्ठा mlxsw_sp *mlxsw_sp, u32 ptys_eth_proto,
			 अचिन्हित दीर्घ *mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP1_PORT_LINK_MODE_LEN; i++) अणु
		अगर (ptys_eth_proto & mlxsw_sp1_port_link_mode[i].mask)
			__set_bit(mlxsw_sp1_port_link_mode[i].mask_ethtool,
				  mode);
	पूर्ण
पूर्ण

अटल u32
mlxsw_sp1_from_ptys_speed(काष्ठा mlxsw_sp *mlxsw_sp, u32 ptys_eth_proto)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP1_PORT_LINK_MODE_LEN; i++) अणु
		अगर (ptys_eth_proto & mlxsw_sp1_port_link_mode[i].mask)
			वापस mlxsw_sp1_port_link_mode[i].speed;
	पूर्ण

	वापस SPEED_UNKNOWN;
पूर्ण

अटल व्योम
mlxsw_sp1_from_ptys_link_mode(काष्ठा mlxsw_sp *mlxsw_sp, bool carrier_ok,
			      u32 ptys_eth_proto,
			      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा mlxsw_sp1_port_link_mode link;
	पूर्णांक i;

	cmd->base.speed = SPEED_UNKNOWN;
	cmd->base.duplex = DUPLEX_UNKNOWN;
	cmd->lanes = 0;

	अगर (!carrier_ok)
		वापस;

	क्रम (i = 0; i < MLXSW_SP1_PORT_LINK_MODE_LEN; i++) अणु
		अगर (ptys_eth_proto & mlxsw_sp1_port_link_mode[i].mask) अणु
			link = mlxsw_sp1_port_link_mode[i];
			ethtool_params_from_link_mode(cmd,
						      link.mask_ethtool);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp1_ptys_max_speed(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 *p_max_speed)
अणु
	u32 eth_proto_cap;
	u32 max_speed = 0;
	पूर्णांक err;
	पूर्णांक i;

	err = mlxsw_sp_port_ptys_query(mlxsw_sp_port, &eth_proto_cap, शून्य, शून्य, शून्य);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < MLXSW_SP1_PORT_LINK_MODE_LEN; i++) अणु
		अगर ((eth_proto_cap & mlxsw_sp1_port_link_mode[i].mask) &&
		    mlxsw_sp1_port_link_mode[i].speed > max_speed)
			max_speed = mlxsw_sp1_port_link_mode[i].speed;
	पूर्ण

	*p_max_speed = max_speed;
	वापस 0;
पूर्ण

अटल u32
mlxsw_sp1_to_ptys_advert_link(काष्ठा mlxsw_sp *mlxsw_sp,
			      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	u32 ptys_proto = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP1_PORT_LINK_MODE_LEN; i++) अणु
		अगर (test_bit(mlxsw_sp1_port_link_mode[i].mask_ethtool,
			     cmd->link_modes.advertising))
			ptys_proto |= mlxsw_sp1_port_link_mode[i].mask;
	पूर्ण
	वापस ptys_proto;
पूर्ण

अटल u32 mlxsw_sp1_to_ptys_speed_lanes(काष्ठा mlxsw_sp *mlxsw_sp, u8 width,
					 स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	u32 ptys_proto = 0;
	पूर्णांक i;

	अगर (cmd->lanes > width)
		वापस ptys_proto;

	क्रम (i = 0; i < MLXSW_SP1_PORT_LINK_MODE_LEN; i++) अणु
		अगर (cmd->base.speed == mlxsw_sp1_port_link_mode[i].speed)
			ptys_proto |= mlxsw_sp1_port_link_mode[i].mask;
	पूर्ण
	वापस ptys_proto;
पूर्ण

अटल व्योम
mlxsw_sp1_reg_ptys_eth_pack(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *payload,
			    u8 local_port, u32 proto_admin, bool स्वतःneg)
अणु
	mlxsw_reg_ptys_eth_pack(payload, local_port, proto_admin, स्वतःneg);
पूर्ण

अटल व्योम
mlxsw_sp1_reg_ptys_eth_unpack(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *payload,
			      u32 *p_eth_proto_cap, u32 *p_eth_proto_admin,
			      u32 *p_eth_proto_oper)
अणु
	mlxsw_reg_ptys_eth_unpack(payload, p_eth_proto_cap, p_eth_proto_admin,
				  p_eth_proto_oper);
पूर्ण

अटल u32 mlxsw_sp1_ptys_proto_cap_masked_get(u32 eth_proto_cap)
अणु
	u32 ptys_proto_cap_masked = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP1_PORT_LINK_MODE_LEN; i++) अणु
		अगर (mlxsw_sp1_port_link_mode[i].mask & eth_proto_cap)
			ptys_proto_cap_masked |=
				mlxsw_sp1_port_link_mode[i].mask;
	पूर्ण

	वापस ptys_proto_cap_masked;
पूर्ण

स्थिर काष्ठा mlxsw_sp_port_type_speed_ops mlxsw_sp1_port_type_speed_ops = अणु
	.from_ptys_supported_port	= mlxsw_sp1_from_ptys_supported_port,
	.from_ptys_link			= mlxsw_sp1_from_ptys_link,
	.from_ptys_speed		= mlxsw_sp1_from_ptys_speed,
	.from_ptys_link_mode		= mlxsw_sp1_from_ptys_link_mode,
	.ptys_max_speed			= mlxsw_sp1_ptys_max_speed,
	.to_ptys_advert_link		= mlxsw_sp1_to_ptys_advert_link,
	.to_ptys_speed_lanes		= mlxsw_sp1_to_ptys_speed_lanes,
	.reg_ptys_eth_pack		= mlxsw_sp1_reg_ptys_eth_pack,
	.reg_ptys_eth_unpack		= mlxsw_sp1_reg_ptys_eth_unpack,
	.ptys_proto_cap_masked_get	= mlxsw_sp1_ptys_proto_cap_masked_get,
पूर्ण;

अटल स्थिर क्रमागत ethtool_link_mode_bit_indices
mlxsw_sp2_mask_ethtool_sgmii_100m[] = अणु
	ETHTOOL_LINK_MODE_100baseT_Full_BIT,
पूर्ण;

#घोषणा MLXSW_SP2_MASK_ETHTOOL_SGMII_100M_LEN \
	ARRAY_SIZE(mlxsw_sp2_mask_ethtool_sgmii_100m)

अटल स्थिर क्रमागत ethtool_link_mode_bit_indices
mlxsw_sp2_mask_ethtool_1000base_x_sgmii[] = अणु
	ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
	ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
पूर्ण;

#घोषणा MLXSW_SP2_MASK_ETHTOOL_1000BASE_X_SGMII_LEN \
	ARRAY_SIZE(mlxsw_sp2_mask_ethtool_1000base_x_sgmii)

अटल स्थिर क्रमागत ethtool_link_mode_bit_indices
mlxsw_sp2_mask_ethtool_5gbase_r[] = अणु
	ETHTOOL_LINK_MODE_5000baseT_Full_BIT,
पूर्ण;

#घोषणा MLXSW_SP2_MASK_ETHTOOL_5GBASE_R_LEN \
	ARRAY_SIZE(mlxsw_sp2_mask_ethtool_5gbase_r)

अटल स्थिर क्रमागत ethtool_link_mode_bit_indices
mlxsw_sp2_mask_ethtool_xfi_xaui_1_10g[] = अणु
	ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseR_FEC_BIT,
	ETHTOOL_LINK_MODE_10000baseCR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseSR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseLR_Full_BIT,
	ETHTOOL_LINK_MODE_10000baseER_Full_BIT,
पूर्ण;

#घोषणा MLXSW_SP2_MASK_ETHTOOL_XFI_XAUI_1_10G_LEN \
	ARRAY_SIZE(mlxsw_sp2_mask_ethtool_xfi_xaui_1_10g)

अटल स्थिर क्रमागत ethtool_link_mode_bit_indices
mlxsw_sp2_mask_ethtool_xlaui_4_xlppi_4_40g[] = अणु
	ETHTOOL_LINK_MODE_40000baseKR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseCR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseSR4_Full_BIT,
	ETHTOOL_LINK_MODE_40000baseLR4_Full_BIT,
पूर्ण;

#घोषणा MLXSW_SP2_MASK_ETHTOOL_XLAUI_4_XLPPI_4_40G_LEN \
	ARRAY_SIZE(mlxsw_sp2_mask_ethtool_xlaui_4_xlppi_4_40g)

अटल स्थिर क्रमागत ethtool_link_mode_bit_indices
mlxsw_sp2_mask_ethtool_25gaui_1_25gbase_cr_kr[] = अणु
	ETHTOOL_LINK_MODE_25000baseCR_Full_BIT,
	ETHTOOL_LINK_MODE_25000baseKR_Full_BIT,
	ETHTOOL_LINK_MODE_25000baseSR_Full_BIT,
पूर्ण;

#घोषणा MLXSW_SP2_MASK_ETHTOOL_25GAUI_1_25GBASE_CR_KR_LEN \
	ARRAY_SIZE(mlxsw_sp2_mask_ethtool_25gaui_1_25gbase_cr_kr)

अटल स्थिर क्रमागत ethtool_link_mode_bit_indices
mlxsw_sp2_mask_ethtool_50gaui_2_laui_2_50gbase_cr2_kr2[] = अणु
	ETHTOOL_LINK_MODE_50000baseCR2_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseKR2_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseSR2_Full_BIT,
पूर्ण;

#घोषणा MLXSW_SP2_MASK_ETHTOOL_50GAUI_2_LAUI_2_50GBASE_CR2_KR2_LEN \
	ARRAY_SIZE(mlxsw_sp2_mask_ethtool_50gaui_2_laui_2_50gbase_cr2_kr2)

अटल स्थिर क्रमागत ethtool_link_mode_bit_indices
mlxsw_sp2_mask_ethtool_50gaui_1_laui_1_50gbase_cr_kr[] = अणु
	ETHTOOL_LINK_MODE_50000baseKR_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseSR_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseCR_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseLR_ER_FR_Full_BIT,
	ETHTOOL_LINK_MODE_50000baseDR_Full_BIT,
पूर्ण;

#घोषणा MLXSW_SP2_MASK_ETHTOOL_50GAUI_1_LAUI_1_50GBASE_CR_KR_LEN \
	ARRAY_SIZE(mlxsw_sp2_mask_ethtool_50gaui_1_laui_1_50gbase_cr_kr)

अटल स्थिर क्रमागत ethtool_link_mode_bit_indices
mlxsw_sp2_mask_ethtool_caui_4_100gbase_cr4_kr4[] = अणु
	ETHTOOL_LINK_MODE_100000baseKR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseSR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseCR4_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseLR4_ER4_Full_BIT,
पूर्ण;

#घोषणा MLXSW_SP2_MASK_ETHTOOL_CAUI_4_100GBASE_CR4_KR4_LEN \
	ARRAY_SIZE(mlxsw_sp2_mask_ethtool_caui_4_100gbase_cr4_kr4)

अटल स्थिर क्रमागत ethtool_link_mode_bit_indices
mlxsw_sp2_mask_ethtool_100gaui_2_100gbase_cr2_kr2[] = अणु
	ETHTOOL_LINK_MODE_100000baseKR2_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseSR2_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseCR2_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseLR2_ER2_FR2_Full_BIT,
	ETHTOOL_LINK_MODE_100000baseDR2_Full_BIT,
पूर्ण;

#घोषणा MLXSW_SP2_MASK_ETHTOOL_100GAUI_2_100GBASE_CR2_KR2_LEN \
	ARRAY_SIZE(mlxsw_sp2_mask_ethtool_100gaui_2_100gbase_cr2_kr2)

अटल स्थिर क्रमागत ethtool_link_mode_bit_indices
mlxsw_sp2_mask_ethtool_200gaui_4_200gbase_cr4_kr4[] = अणु
	ETHTOOL_LINK_MODE_200000baseKR4_Full_BIT,
	ETHTOOL_LINK_MODE_200000baseSR4_Full_BIT,
	ETHTOOL_LINK_MODE_200000baseLR4_ER4_FR4_Full_BIT,
	ETHTOOL_LINK_MODE_200000baseDR4_Full_BIT,
	ETHTOOL_LINK_MODE_200000baseCR4_Full_BIT,
पूर्ण;

#घोषणा MLXSW_SP2_MASK_ETHTOOL_200GAUI_4_200GBASE_CR4_KR4_LEN \
	ARRAY_SIZE(mlxsw_sp2_mask_ethtool_200gaui_4_200gbase_cr4_kr4)

अटल स्थिर क्रमागत ethtool_link_mode_bit_indices
mlxsw_sp2_mask_ethtool_400gaui_8[] = अणु
	ETHTOOL_LINK_MODE_400000baseKR8_Full_BIT,
	ETHTOOL_LINK_MODE_400000baseSR8_Full_BIT,
	ETHTOOL_LINK_MODE_400000baseLR8_ER8_FR8_Full_BIT,
	ETHTOOL_LINK_MODE_400000baseDR8_Full_BIT,
	ETHTOOL_LINK_MODE_400000baseCR8_Full_BIT,
पूर्ण;

#घोषणा MLXSW_SP2_MASK_ETHTOOL_400GAUI_8_LEN \
	ARRAY_SIZE(mlxsw_sp2_mask_ethtool_400gaui_8)

#घोषणा MLXSW_SP_PORT_MASK_WIDTH_1X	BIT(0)
#घोषणा MLXSW_SP_PORT_MASK_WIDTH_2X	BIT(1)
#घोषणा MLXSW_SP_PORT_MASK_WIDTH_4X	BIT(2)
#घोषणा MLXSW_SP_PORT_MASK_WIDTH_8X	BIT(3)

अटल u8 mlxsw_sp_port_mask_width_get(u8 width)
अणु
	चयन (width) अणु
	हाल 1:
		वापस MLXSW_SP_PORT_MASK_WIDTH_1X;
	हाल 2:
		वापस MLXSW_SP_PORT_MASK_WIDTH_2X;
	हाल 4:
		वापस MLXSW_SP_PORT_MASK_WIDTH_4X;
	हाल 8:
		वापस MLXSW_SP_PORT_MASK_WIDTH_8X;
	शेष:
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण
पूर्ण

काष्ठा mlxsw_sp2_port_link_mode अणु
	स्थिर क्रमागत ethtool_link_mode_bit_indices *mask_ethtool;
	पूर्णांक m_ethtool_len;
	u32 mask;
	u32 speed;
	u32 width;
	u8 mask_sup_width;
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp2_port_link_mode mlxsw_sp2_port_link_mode[] = अणु
	अणु
		.mask		= MLXSW_REG_PTYS_EXT_ETH_SPEED_SGMII_100M,
		.mask_ethtool	= mlxsw_sp2_mask_ethtool_sgmii_100m,
		.m_ethtool_len	= MLXSW_SP2_MASK_ETHTOOL_SGMII_100M_LEN,
		.mask_sup_width	= MLXSW_SP_PORT_MASK_WIDTH_1X |
				  MLXSW_SP_PORT_MASK_WIDTH_2X |
				  MLXSW_SP_PORT_MASK_WIDTH_4X |
				  MLXSW_SP_PORT_MASK_WIDTH_8X,
		.speed		= SPEED_100,
		.width		= 1,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_EXT_ETH_SPEED_1000BASE_X_SGMII,
		.mask_ethtool	= mlxsw_sp2_mask_ethtool_1000base_x_sgmii,
		.m_ethtool_len	= MLXSW_SP2_MASK_ETHTOOL_1000BASE_X_SGMII_LEN,
		.mask_sup_width	= MLXSW_SP_PORT_MASK_WIDTH_1X |
				  MLXSW_SP_PORT_MASK_WIDTH_2X |
				  MLXSW_SP_PORT_MASK_WIDTH_4X |
				  MLXSW_SP_PORT_MASK_WIDTH_8X,
		.speed		= SPEED_1000,
		.width		= 1,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_EXT_ETH_SPEED_5GBASE_R,
		.mask_ethtool	= mlxsw_sp2_mask_ethtool_5gbase_r,
		.m_ethtool_len	= MLXSW_SP2_MASK_ETHTOOL_5GBASE_R_LEN,
		.mask_sup_width	= MLXSW_SP_PORT_MASK_WIDTH_1X |
				  MLXSW_SP_PORT_MASK_WIDTH_2X |
				  MLXSW_SP_PORT_MASK_WIDTH_4X |
				  MLXSW_SP_PORT_MASK_WIDTH_8X,
		.speed		= SPEED_5000,
		.width		= 1,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_EXT_ETH_SPEED_XFI_XAUI_1_10G,
		.mask_ethtool	= mlxsw_sp2_mask_ethtool_xfi_xaui_1_10g,
		.m_ethtool_len	= MLXSW_SP2_MASK_ETHTOOL_XFI_XAUI_1_10G_LEN,
		.mask_sup_width	= MLXSW_SP_PORT_MASK_WIDTH_1X |
				  MLXSW_SP_PORT_MASK_WIDTH_2X |
				  MLXSW_SP_PORT_MASK_WIDTH_4X |
				  MLXSW_SP_PORT_MASK_WIDTH_8X,
		.speed		= SPEED_10000,
		.width		= 1,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_EXT_ETH_SPEED_XLAUI_4_XLPPI_4_40G,
		.mask_ethtool	= mlxsw_sp2_mask_ethtool_xlaui_4_xlppi_4_40g,
		.m_ethtool_len	= MLXSW_SP2_MASK_ETHTOOL_XLAUI_4_XLPPI_4_40G_LEN,
		.mask_sup_width	= MLXSW_SP_PORT_MASK_WIDTH_4X |
				  MLXSW_SP_PORT_MASK_WIDTH_8X,
		.speed		= SPEED_40000,
		.width		= 4,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_EXT_ETH_SPEED_25GAUI_1_25GBASE_CR_KR,
		.mask_ethtool	= mlxsw_sp2_mask_ethtool_25gaui_1_25gbase_cr_kr,
		.m_ethtool_len	= MLXSW_SP2_MASK_ETHTOOL_25GAUI_1_25GBASE_CR_KR_LEN,
		.mask_sup_width	= MLXSW_SP_PORT_MASK_WIDTH_1X |
				  MLXSW_SP_PORT_MASK_WIDTH_2X |
				  MLXSW_SP_PORT_MASK_WIDTH_4X |
				  MLXSW_SP_PORT_MASK_WIDTH_8X,
		.speed		= SPEED_25000,
		.width		= 1,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_EXT_ETH_SPEED_50GAUI_2_LAUI_2_50GBASE_CR2_KR2,
		.mask_ethtool	= mlxsw_sp2_mask_ethtool_50gaui_2_laui_2_50gbase_cr2_kr2,
		.m_ethtool_len	= MLXSW_SP2_MASK_ETHTOOL_50GAUI_2_LAUI_2_50GBASE_CR2_KR2_LEN,
		.mask_sup_width	= MLXSW_SP_PORT_MASK_WIDTH_2X |
				  MLXSW_SP_PORT_MASK_WIDTH_4X |
				  MLXSW_SP_PORT_MASK_WIDTH_8X,
		.speed		= SPEED_50000,
		.width		= 2,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_EXT_ETH_SPEED_50GAUI_1_LAUI_1_50GBASE_CR_KR,
		.mask_ethtool	= mlxsw_sp2_mask_ethtool_50gaui_1_laui_1_50gbase_cr_kr,
		.m_ethtool_len	= MLXSW_SP2_MASK_ETHTOOL_50GAUI_1_LAUI_1_50GBASE_CR_KR_LEN,
		.mask_sup_width	= MLXSW_SP_PORT_MASK_WIDTH_1X,
		.speed		= SPEED_50000,
		.width		= 1,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_EXT_ETH_SPEED_CAUI_4_100GBASE_CR4_KR4,
		.mask_ethtool	= mlxsw_sp2_mask_ethtool_caui_4_100gbase_cr4_kr4,
		.m_ethtool_len	= MLXSW_SP2_MASK_ETHTOOL_CAUI_4_100GBASE_CR4_KR4_LEN,
		.mask_sup_width	= MLXSW_SP_PORT_MASK_WIDTH_4X |
				  MLXSW_SP_PORT_MASK_WIDTH_8X,
		.speed		= SPEED_100000,
		.width		= 4,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_EXT_ETH_SPEED_100GAUI_2_100GBASE_CR2_KR2,
		.mask_ethtool	= mlxsw_sp2_mask_ethtool_100gaui_2_100gbase_cr2_kr2,
		.m_ethtool_len	= MLXSW_SP2_MASK_ETHTOOL_100GAUI_2_100GBASE_CR2_KR2_LEN,
		.mask_sup_width	= MLXSW_SP_PORT_MASK_WIDTH_2X,
		.speed		= SPEED_100000,
		.width		= 2,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_EXT_ETH_SPEED_200GAUI_4_200GBASE_CR4_KR4,
		.mask_ethtool	= mlxsw_sp2_mask_ethtool_200gaui_4_200gbase_cr4_kr4,
		.m_ethtool_len	= MLXSW_SP2_MASK_ETHTOOL_200GAUI_4_200GBASE_CR4_KR4_LEN,
		.mask_sup_width	= MLXSW_SP_PORT_MASK_WIDTH_4X |
				  MLXSW_SP_PORT_MASK_WIDTH_8X,
		.speed		= SPEED_200000,
		.width		= 4,
	पूर्ण,
	अणु
		.mask		= MLXSW_REG_PTYS_EXT_ETH_SPEED_400GAUI_8,
		.mask_ethtool	= mlxsw_sp2_mask_ethtool_400gaui_8,
		.m_ethtool_len	= MLXSW_SP2_MASK_ETHTOOL_400GAUI_8_LEN,
		.mask_sup_width	= MLXSW_SP_PORT_MASK_WIDTH_8X,
		.speed		= SPEED_400000,
		.width		= 8,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP2_PORT_LINK_MODE_LEN ARRAY_SIZE(mlxsw_sp2_port_link_mode)

अटल व्योम
mlxsw_sp2_from_ptys_supported_port(काष्ठा mlxsw_sp *mlxsw_sp,
				   u32 ptys_eth_proto,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	ethtool_link_ksettings_add_link_mode(cmd, supported, FIBRE);
	ethtool_link_ksettings_add_link_mode(cmd, supported, Backplane);
पूर्ण

अटल व्योम
mlxsw_sp2_set_bit_ethtool(स्थिर काष्ठा mlxsw_sp2_port_link_mode *link_mode,
			  अचिन्हित दीर्घ *mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < link_mode->m_ethtool_len; i++)
		__set_bit(link_mode->mask_ethtool[i], mode);
पूर्ण

अटल व्योम
mlxsw_sp2_from_ptys_link(काष्ठा mlxsw_sp *mlxsw_sp, u32 ptys_eth_proto,
			 अचिन्हित दीर्घ *mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP2_PORT_LINK_MODE_LEN; i++) अणु
		अगर (ptys_eth_proto & mlxsw_sp2_port_link_mode[i].mask)
			mlxsw_sp2_set_bit_ethtool(&mlxsw_sp2_port_link_mode[i],
						  mode);
	पूर्ण
पूर्ण

अटल u32
mlxsw_sp2_from_ptys_speed(काष्ठा mlxsw_sp *mlxsw_sp, u32 ptys_eth_proto)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP2_PORT_LINK_MODE_LEN; i++) अणु
		अगर (ptys_eth_proto & mlxsw_sp2_port_link_mode[i].mask)
			वापस mlxsw_sp2_port_link_mode[i].speed;
	पूर्ण

	वापस SPEED_UNKNOWN;
पूर्ण

अटल व्योम
mlxsw_sp2_from_ptys_link_mode(काष्ठा mlxsw_sp *mlxsw_sp, bool carrier_ok,
			      u32 ptys_eth_proto,
			      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा mlxsw_sp2_port_link_mode link;
	पूर्णांक i;

	cmd->base.speed = SPEED_UNKNOWN;
	cmd->base.duplex = DUPLEX_UNKNOWN;
	cmd->lanes = 0;

	अगर (!carrier_ok)
		वापस;

	क्रम (i = 0; i < MLXSW_SP2_PORT_LINK_MODE_LEN; i++) अणु
		अगर (ptys_eth_proto & mlxsw_sp2_port_link_mode[i].mask) अणु
			link = mlxsw_sp2_port_link_mode[i];
			ethtool_params_from_link_mode(cmd,
						      link.mask_ethtool[1]);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp2_ptys_max_speed(काष्ठा mlxsw_sp_port *mlxsw_sp_port, u32 *p_max_speed)
अणु
	u32 eth_proto_cap;
	u32 max_speed = 0;
	पूर्णांक err;
	पूर्णांक i;

	err = mlxsw_sp_port_ptys_query(mlxsw_sp_port, &eth_proto_cap, शून्य, शून्य, शून्य);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < MLXSW_SP2_PORT_LINK_MODE_LEN; i++) अणु
		अगर ((eth_proto_cap & mlxsw_sp2_port_link_mode[i].mask) &&
		    mlxsw_sp2_port_link_mode[i].speed > max_speed)
			max_speed = mlxsw_sp2_port_link_mode[i].speed;
	पूर्ण

	*p_max_speed = max_speed;
	वापस 0;
पूर्ण

अटल bool
mlxsw_sp2_test_bit_ethtool(स्थिर काष्ठा mlxsw_sp2_port_link_mode *link_mode,
			   स्थिर अचिन्हित दीर्घ *mode)
अणु
	पूर्णांक cnt = 0;
	पूर्णांक i;

	क्रम (i = 0; i < link_mode->m_ethtool_len; i++) अणु
		अगर (test_bit(link_mode->mask_ethtool[i], mode))
			cnt++;
	पूर्ण

	वापस cnt == link_mode->m_ethtool_len;
पूर्ण

अटल u32
mlxsw_sp2_to_ptys_advert_link(काष्ठा mlxsw_sp *mlxsw_sp,
			      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	u32 ptys_proto = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP2_PORT_LINK_MODE_LEN; i++) अणु
		अगर (mlxsw_sp2_test_bit_ethtool(&mlxsw_sp2_port_link_mode[i],
					       cmd->link_modes.advertising))
			ptys_proto |= mlxsw_sp2_port_link_mode[i].mask;
	पूर्ण
	वापस ptys_proto;
पूर्ण

अटल u32 mlxsw_sp2_to_ptys_speed_lanes(काष्ठा mlxsw_sp *mlxsw_sp, u8 width,
					 स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	u8 mask_width = mlxsw_sp_port_mask_width_get(width);
	काष्ठा mlxsw_sp2_port_link_mode link_mode;
	u32 ptys_proto = 0;
	पूर्णांक i;

	अगर (cmd->lanes > width)
		वापस ptys_proto;

	क्रम (i = 0; i < MLXSW_SP2_PORT_LINK_MODE_LEN; i++) अणु
		अगर (cmd->base.speed == mlxsw_sp2_port_link_mode[i].speed) अणु
			link_mode = mlxsw_sp2_port_link_mode[i];

			अगर (!cmd->lanes) अणु
				/* If number of lanes was not set by user space,
				 * choose the link mode that supports the width
				 * of the port.
				 */
				अगर (mask_width & link_mode.mask_sup_width)
					ptys_proto |= link_mode.mask;
			पूर्ण अन्यथा अगर (cmd->lanes == link_mode.width) अणु
				/* Else अगर the number of lanes was set, choose
				 * the link mode that its actual width equals to
				 * it.
				 */
				ptys_proto |= link_mode.mask;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ptys_proto;
पूर्ण

अटल व्योम
mlxsw_sp2_reg_ptys_eth_pack(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *payload,
			    u8 local_port, u32 proto_admin,
			    bool स्वतःneg)
अणु
	mlxsw_reg_ptys_ext_eth_pack(payload, local_port, proto_admin, स्वतःneg);
पूर्ण

अटल व्योम
mlxsw_sp2_reg_ptys_eth_unpack(काष्ठा mlxsw_sp *mlxsw_sp, अक्षर *payload,
			      u32 *p_eth_proto_cap, u32 *p_eth_proto_admin,
			      u32 *p_eth_proto_oper)
अणु
	mlxsw_reg_ptys_ext_eth_unpack(payload, p_eth_proto_cap,
				      p_eth_proto_admin, p_eth_proto_oper);
पूर्ण

अटल u32 mlxsw_sp2_ptys_proto_cap_masked_get(u32 eth_proto_cap)
अणु
	u32 ptys_proto_cap_masked = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP2_PORT_LINK_MODE_LEN; i++) अणु
		अगर (mlxsw_sp2_port_link_mode[i].mask & eth_proto_cap)
			ptys_proto_cap_masked |=
				mlxsw_sp2_port_link_mode[i].mask;
	पूर्ण

	वापस ptys_proto_cap_masked;
पूर्ण

स्थिर काष्ठा mlxsw_sp_port_type_speed_ops mlxsw_sp2_port_type_speed_ops = अणु
	.from_ptys_supported_port	= mlxsw_sp2_from_ptys_supported_port,
	.from_ptys_link			= mlxsw_sp2_from_ptys_link,
	.from_ptys_speed		= mlxsw_sp2_from_ptys_speed,
	.from_ptys_link_mode		= mlxsw_sp2_from_ptys_link_mode,
	.ptys_max_speed			= mlxsw_sp2_ptys_max_speed,
	.to_ptys_advert_link		= mlxsw_sp2_to_ptys_advert_link,
	.to_ptys_speed_lanes		= mlxsw_sp2_to_ptys_speed_lanes,
	.reg_ptys_eth_pack		= mlxsw_sp2_reg_ptys_eth_pack,
	.reg_ptys_eth_unpack		= mlxsw_sp2_reg_ptys_eth_unpack,
	.ptys_proto_cap_masked_get	= mlxsw_sp2_ptys_proto_cap_masked_get,
पूर्ण;
