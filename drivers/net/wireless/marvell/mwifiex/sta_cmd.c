<शैली गुरु>
/*
 * NXP Wireless LAN device driver: station command handling
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#समावेश "decl.h"
#समावेश "ioctl.h"
#समावेश "util.h"
#समावेश "fw.h"
#समावेश "main.h"
#समावेश "wmm.h"
#समावेश "11n.h"
#समावेश "11ac.h"

अटल bool drcs;
module_param(drcs, bool, 0644);
MODULE_PARM_DESC(drcs, "multi-channel operation:1, single-channel operation:0");

अटल bool disable_स्वतः_ds;
module_param(disable_स्वतः_ds, bool, 0);
MODULE_PARM_DESC(disable_स्वतः_ds,
		 "deepsleep enabled=0(default), deepsleep disabled=1");
/*
 * This function prepares command to set/get RSSI inक्रमmation.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting data/beacon average factors
 *      - Resetting SNR/NF/RSSI values in निजी काष्ठाure
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक
mwअगरiex_cmd_802_11_rssi_info(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा host_cmd_ds_command *cmd, u16 cmd_action)
अणु
	cmd->command = cpu_to_le16(HostCmd_CMD_RSSI_INFO);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_802_11_rssi_info) +
				S_DS_GEN);
	cmd->params.rssi_info.action = cpu_to_le16(cmd_action);
	cmd->params.rssi_info.ndata = cpu_to_le16(priv->data_avg_factor);
	cmd->params.rssi_info.nbcn = cpu_to_le16(priv->bcn_avg_factor);

	/* Reset SNR/NF/RSSI values in निजी काष्ठाure */
	priv->data_rssi_last = 0;
	priv->data_nf_last = 0;
	priv->data_rssi_avg = 0;
	priv->data_nf_avg = 0;
	priv->bcn_rssi_last = 0;
	priv->bcn_nf_last = 0;
	priv->bcn_rssi_avg = 0;
	priv->bcn_nf_avg = 0;

	वापस 0;
पूर्ण

/*
 * This function prepares command to set MAC control.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक mwअगरiex_cmd_mac_control(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा host_cmd_ds_command *cmd,
				   u16 cmd_action, u32 *action)
अणु
	काष्ठा host_cmd_ds_mac_control *mac_ctrl = &cmd->params.mac_ctrl;

	अगर (cmd_action != HostCmd_ACT_GEN_SET) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "mac_control: only support set cmd\n");
		वापस -1;
	पूर्ण

	cmd->command = cpu_to_le16(HostCmd_CMD_MAC_CONTROL);
	cmd->size =
		cpu_to_le16(माप(काष्ठा host_cmd_ds_mac_control) + S_DS_GEN);
	mac_ctrl->action = cpu_to_le32(*action);

	वापस 0;
पूर्ण

/*
 * This function prepares command to set/get SNMP MIB.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting SNMP MIB OID number and value
 *        (as required)
 *      - Ensuring correct endian-ness
 *
 * The following SNMP MIB OIDs are supported -
 *      - FRAG_THRESH_I     : Fragmentation threshold
 *      - RTS_THRESH_I      : RTS threshold
 *      - SHORT_RETRY_LIM_I : Short retry limit
 *      - DOT11D_I          : 11d support
 */
अटल पूर्णांक mwअगरiex_cmd_802_11_snmp_mib(काष्ठा mwअगरiex_निजी *priv,
				       काष्ठा host_cmd_ds_command *cmd,
				       u16 cmd_action, u32 cmd_oid,
				       u16 *ul_temp)
अणु
	काष्ठा host_cmd_ds_802_11_snmp_mib *snmp_mib = &cmd->params.smib;

	mwअगरiex_dbg(priv->adapter, CMD,
		    "cmd: SNMP_CMD: cmd_oid = 0x%x\n", cmd_oid);
	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_SNMP_MIB);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_802_11_snmp_mib)
				- 1 + S_DS_GEN);

	snmp_mib->oid = cpu_to_le16((u16)cmd_oid);
	अगर (cmd_action == HostCmd_ACT_GEN_GET) अणु
		snmp_mib->query_type = cpu_to_le16(HostCmd_ACT_GEN_GET);
		snmp_mib->buf_size = cpu_to_le16(MAX_SNMP_BUF_SIZE);
		le16_unaligned_add_cpu(&cmd->size, MAX_SNMP_BUF_SIZE);
	पूर्ण अन्यथा अगर (cmd_action == HostCmd_ACT_GEN_SET) अणु
		snmp_mib->query_type = cpu_to_le16(HostCmd_ACT_GEN_SET);
		snmp_mib->buf_size = cpu_to_le16(माप(u16));
		put_unaligned_le16(*ul_temp, snmp_mib->value);
		le16_unaligned_add_cpu(&cmd->size, माप(u16));
	पूर्ण

	mwअगरiex_dbg(priv->adapter, CMD,
		    "cmd: SNMP_CMD: Action=0x%x, OID=0x%x,\t"
		    "OIDSize=0x%x, Value=0x%x\n",
		    cmd_action, cmd_oid, le16_to_cpu(snmp_mib->buf_size),
		    get_unaligned_le16(snmp_mib->value));
	वापस 0;
पूर्ण

/*
 * This function prepares command to get log.
 *
 * Preparation includes -
 *      - Setting command ID and proper size
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक
mwअगरiex_cmd_802_11_get_log(काष्ठा host_cmd_ds_command *cmd)
अणु
	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_GET_LOG);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_802_11_get_log) +
				S_DS_GEN);
	वापस 0;
पूर्ण

/*
 * This function prepares command to set/get Tx data rate configuration.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting configuration index, rate scope and rate drop pattern
 *        parameters (as required)
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक mwअगरiex_cmd_tx_rate_cfg(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा host_cmd_ds_command *cmd,
				   u16 cmd_action, u16 *pbiपंचांगap_rates)
अणु
	काष्ठा host_cmd_ds_tx_rate_cfg *rate_cfg = &cmd->params.tx_rate_cfg;
	काष्ठा mwअगरiex_rate_scope *rate_scope;
	काष्ठा mwअगरiex_rate_drop_pattern *rate_drop;
	u32 i;

	cmd->command = cpu_to_le16(HostCmd_CMD_TX_RATE_CFG);

	rate_cfg->action = cpu_to_le16(cmd_action);
	rate_cfg->cfg_index = 0;

	rate_scope = (काष्ठा mwअगरiex_rate_scope *) ((u8 *) rate_cfg +
		      माप(काष्ठा host_cmd_ds_tx_rate_cfg));
	rate_scope->type = cpu_to_le16(TLV_TYPE_RATE_SCOPE);
	rate_scope->length = cpu_to_le16
		(माप(*rate_scope) - माप(काष्ठा mwअगरiex_ie_types_header));
	अगर (pbiपंचांगap_rates != शून्य) अणु
		rate_scope->hr_dsss_rate_biपंचांगap = cpu_to_le16(pbiपंचांगap_rates[0]);
		rate_scope->ofdm_rate_biपंचांगap = cpu_to_le16(pbiपंचांगap_rates[1]);
		क्रम (i = 0; i < ARRAY_SIZE(rate_scope->ht_mcs_rate_biपंचांगap); i++)
			rate_scope->ht_mcs_rate_biपंचांगap[i] =
				cpu_to_le16(pbiपंचांगap_rates[2 + i]);
		अगर (priv->adapter->fw_api_ver == MWIFIEX_FW_V15) अणु
			क्रम (i = 0;
			     i < ARRAY_SIZE(rate_scope->vht_mcs_rate_biपंचांगap);
			     i++)
				rate_scope->vht_mcs_rate_biपंचांगap[i] =
					cpu_to_le16(pbiपंचांगap_rates[10 + i]);
		पूर्ण
	पूर्ण अन्यथा अणु
		rate_scope->hr_dsss_rate_biपंचांगap =
			cpu_to_le16(priv->biपंचांगap_rates[0]);
		rate_scope->ofdm_rate_biपंचांगap =
			cpu_to_le16(priv->biपंचांगap_rates[1]);
		क्रम (i = 0; i < ARRAY_SIZE(rate_scope->ht_mcs_rate_biपंचांगap); i++)
			rate_scope->ht_mcs_rate_biपंचांगap[i] =
				cpu_to_le16(priv->biपंचांगap_rates[2 + i]);
		अगर (priv->adapter->fw_api_ver == MWIFIEX_FW_V15) अणु
			क्रम (i = 0;
			     i < ARRAY_SIZE(rate_scope->vht_mcs_rate_biपंचांगap);
			     i++)
				rate_scope->vht_mcs_rate_biपंचांगap[i] =
					cpu_to_le16(priv->biपंचांगap_rates[10 + i]);
		पूर्ण
	पूर्ण

	rate_drop = (काष्ठा mwअगरiex_rate_drop_pattern *) ((u8 *) rate_scope +
					     माप(काष्ठा mwअगरiex_rate_scope));
	rate_drop->type = cpu_to_le16(TLV_TYPE_RATE_DROP_CONTROL);
	rate_drop->length = cpu_to_le16(माप(rate_drop->rate_drop_mode));
	rate_drop->rate_drop_mode = 0;

	cmd->size =
		cpu_to_le16(S_DS_GEN + माप(काष्ठा host_cmd_ds_tx_rate_cfg) +
			    माप(काष्ठा mwअगरiex_rate_scope) +
			    माप(काष्ठा mwअगरiex_rate_drop_pattern));

	वापस 0;
पूर्ण

/*
 * This function prepares command to set/get Tx घातer configuration.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting Tx घातer mode, घातer group TLV
 *        (as required)
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक mwअगरiex_cmd_tx_घातer_cfg(काष्ठा host_cmd_ds_command *cmd,
				    u16 cmd_action,
				    काष्ठा host_cmd_ds_txpwr_cfg *txp)
अणु
	काष्ठा mwअगरiex_types_घातer_group *pg_tlv;
	काष्ठा host_cmd_ds_txpwr_cfg *cmd_txp_cfg = &cmd->params.txp_cfg;

	cmd->command = cpu_to_le16(HostCmd_CMD_TXPWR_CFG);
	cmd->size =
		cpu_to_le16(S_DS_GEN + माप(काष्ठा host_cmd_ds_txpwr_cfg));
	चयन (cmd_action) अणु
	हाल HostCmd_ACT_GEN_SET:
		अगर (txp->mode) अणु
			pg_tlv = (काष्ठा mwअगरiex_types_घातer_group
				  *) ((अचिन्हित दीर्घ) txp +
				     माप(काष्ठा host_cmd_ds_txpwr_cfg));
			स_हटाओ(cmd_txp_cfg, txp,
				माप(काष्ठा host_cmd_ds_txpwr_cfg) +
				माप(काष्ठा mwअगरiex_types_घातer_group) +
				le16_to_cpu(pg_tlv->length));

			pg_tlv = (काष्ठा mwअगरiex_types_घातer_group *) ((u8 *)
				  cmd_txp_cfg +
				  माप(काष्ठा host_cmd_ds_txpwr_cfg));
			cmd->size = cpu_to_le16(le16_to_cpu(cmd->size) +
				  माप(काष्ठा mwअगरiex_types_घातer_group) +
				  le16_to_cpu(pg_tlv->length));
		पूर्ण अन्यथा अणु
			स_हटाओ(cmd_txp_cfg, txp, माप(*txp));
		पूर्ण
		cmd_txp_cfg->action = cpu_to_le16(cmd_action);
		अवरोध;
	हाल HostCmd_ACT_GEN_GET:
		cmd_txp_cfg->action = cpu_to_le16(cmd_action);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function prepares command to get RF Tx घातer.
 */
अटल पूर्णांक mwअगरiex_cmd_rf_tx_घातer(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा host_cmd_ds_command *cmd,
				   u16 cmd_action, व्योम *data_buf)
अणु
	काष्ठा host_cmd_ds_rf_tx_pwr *txp = &cmd->params.txp;

	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_rf_tx_pwr)
				+ S_DS_GEN);
	cmd->command = cpu_to_le16(HostCmd_CMD_RF_TX_PWR);
	txp->action = cpu_to_le16(cmd_action);

	वापस 0;
पूर्ण

/*
 * This function prepares command to set rf antenna.
 */
अटल पूर्णांक mwअगरiex_cmd_rf_antenna(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा host_cmd_ds_command *cmd,
				  u16 cmd_action,
				  काष्ठा mwअगरiex_ds_ant_cfg *ant_cfg)
अणु
	काष्ठा host_cmd_ds_rf_ant_mimo *ant_mimo = &cmd->params.ant_mimo;
	काष्ठा host_cmd_ds_rf_ant_siso *ant_siso = &cmd->params.ant_siso;

	cmd->command = cpu_to_le16(HostCmd_CMD_RF_ANTENNA);

	चयन (cmd_action) अणु
	हाल HostCmd_ACT_GEN_SET:
		अगर (priv->adapter->hw_dev_mcs_support == HT_STREAM_2X2) अणु
			cmd->size = cpu_to_le16(माप(काष्ठा
						host_cmd_ds_rf_ant_mimo)
						+ S_DS_GEN);
			ant_mimo->action_tx = cpu_to_le16(HostCmd_ACT_SET_TX);
			ant_mimo->tx_ant_mode = cpu_to_le16((u16)ant_cfg->
							    tx_ant);
			ant_mimo->action_rx = cpu_to_le16(HostCmd_ACT_SET_RX);
			ant_mimo->rx_ant_mode = cpu_to_le16((u16)ant_cfg->
							    rx_ant);
		पूर्ण अन्यथा अणु
			cmd->size = cpu_to_le16(माप(काष्ठा
						host_cmd_ds_rf_ant_siso) +
						S_DS_GEN);
			ant_siso->action = cpu_to_le16(HostCmd_ACT_SET_BOTH);
			ant_siso->ant_mode = cpu_to_le16((u16)ant_cfg->tx_ant);
		पूर्ण
		अवरोध;
	हाल HostCmd_ACT_GEN_GET:
		अगर (priv->adapter->hw_dev_mcs_support == HT_STREAM_2X2) अणु
			cmd->size = cpu_to_le16(माप(काष्ठा
						host_cmd_ds_rf_ant_mimo) +
						S_DS_GEN);
			ant_mimo->action_tx = cpu_to_le16(HostCmd_ACT_GET_TX);
			ant_mimo->action_rx = cpu_to_le16(HostCmd_ACT_GET_RX);
		पूर्ण अन्यथा अणु
			cmd->size = cpu_to_le16(माप(काष्ठा
						host_cmd_ds_rf_ant_siso) +
						S_DS_GEN);
			ant_siso->action = cpu_to_le16(HostCmd_ACT_GET_BOTH);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function prepares command to set Host Sleep configuration.
 *
 * Preparation includes -
 *      - Setting command ID and proper size
 *      - Setting Host Sleep action, conditions, ARP filters
 *        (as required)
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक
mwअगरiex_cmd_802_11_hs_cfg(काष्ठा mwअगरiex_निजी *priv,
			  काष्ठा host_cmd_ds_command *cmd,
			  u16 cmd_action,
			  काष्ठा mwअगरiex_hs_config_param *hscfg_param)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा host_cmd_ds_802_11_hs_cfg_enh *hs_cfg = &cmd->params.opt_hs_cfg;
	u8 *tlv = (u8 *)hs_cfg + माप(काष्ठा host_cmd_ds_802_11_hs_cfg_enh);
	काष्ठा mwअगरiex_ps_param_in_hs *psparam_tlv = शून्य;
	bool hs_activate = false;
	u16 size;

	अगर (!hscfg_param)
		/* New Activate command */
		hs_activate = true;
	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_HS_CFG_ENH);

	अगर (!hs_activate &&
	    (hscfg_param->conditions != cpu_to_le32(HS_CFG_CANCEL)) &&
	    ((adapter->arp_filter_size > 0) &&
	     (adapter->arp_filter_size <= ARP_FILTER_MAX_BUF_SIZE))) अणु
		mwअगरiex_dbg(adapter, CMD,
			    "cmd: Attach %d bytes ArpFilter to HSCfg cmd\n",
			    adapter->arp_filter_size);
		स_नकल(((u8 *) hs_cfg) +
		       माप(काष्ठा host_cmd_ds_802_11_hs_cfg_enh),
		       adapter->arp_filter, adapter->arp_filter_size);
		size = adapter->arp_filter_size +
			माप(काष्ठा host_cmd_ds_802_11_hs_cfg_enh)
			+ S_DS_GEN;
		tlv = (u8 *)hs_cfg
			+ माप(काष्ठा host_cmd_ds_802_11_hs_cfg_enh)
			+ adapter->arp_filter_size;
	पूर्ण अन्यथा अणु
		size = S_DS_GEN + माप(काष्ठा host_cmd_ds_802_11_hs_cfg_enh);
	पूर्ण
	अगर (hs_activate) अणु
		hs_cfg->action = cpu_to_le16(HS_ACTIVATE);
		hs_cfg->params.hs_activate.resp_ctrl = cpu_to_le16(RESP_NEEDED);
	पूर्ण अन्यथा अणु
		hs_cfg->action = cpu_to_le16(HS_CONFIGURE);
		hs_cfg->params.hs_config.conditions = hscfg_param->conditions;
		hs_cfg->params.hs_config.gpio = hscfg_param->gpio;
		hs_cfg->params.hs_config.gap = hscfg_param->gap;

		size += माप(काष्ठा mwअगरiex_ps_param_in_hs);
		psparam_tlv = (काष्ठा mwअगरiex_ps_param_in_hs *)tlv;
		psparam_tlv->header.type =
			cpu_to_le16(TLV_TYPE_PS_PARAMS_IN_HS);
		psparam_tlv->header.len =
			cpu_to_le16(माप(काष्ठा mwअगरiex_ps_param_in_hs)
				- माप(काष्ठा mwअगरiex_ie_types_header));
		psparam_tlv->hs_wake_पूर्णांक = cpu_to_le32(HS_DEF_WAKE_INTERVAL);
		psparam_tlv->hs_inact_समयout =
			cpu_to_le32(HS_DEF_INACTIVITY_TIMEOUT);

		mwअगरiex_dbg(adapter, CMD,
			    "cmd: HS_CFG_CMD: condition:0x%x gpio:0x%x gap:0x%x\n",
			    hs_cfg->params.hs_config.conditions,
			    hs_cfg->params.hs_config.gpio,
			    hs_cfg->params.hs_config.gap);
	पूर्ण
	cmd->size = cpu_to_le16(size);

	वापस 0;
पूर्ण

/*
 * This function prepares command to set/get MAC address.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting MAC address (क्रम SET only)
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक mwअगरiex_cmd_802_11_mac_address(काष्ठा mwअगरiex_निजी *priv,
					  काष्ठा host_cmd_ds_command *cmd,
					  u16 cmd_action)
अणु
	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_MAC_ADDRESS);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_802_11_mac_address) +
				S_DS_GEN);
	cmd->result = 0;

	cmd->params.mac_addr.action = cpu_to_le16(cmd_action);

	अगर (cmd_action == HostCmd_ACT_GEN_SET)
		स_नकल(cmd->params.mac_addr.mac_addr, priv->curr_addr,
		       ETH_ALEN);
	वापस 0;
पूर्ण

/*
 * This function prepares command to set MAC multicast address.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting MAC multicast address
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक
mwअगरiex_cmd_mac_multicast_adr(काष्ठा host_cmd_ds_command *cmd,
			      u16 cmd_action,
			      काष्ठा mwअगरiex_multicast_list *mcast_list)
अणु
	काष्ठा host_cmd_ds_mac_multicast_adr *mcast_addr = &cmd->params.mc_addr;

	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_mac_multicast_adr) +
				S_DS_GEN);
	cmd->command = cpu_to_le16(HostCmd_CMD_MAC_MULTICAST_ADR);

	mcast_addr->action = cpu_to_le16(cmd_action);
	mcast_addr->num_of_adrs =
		cpu_to_le16((u16) mcast_list->num_multicast_addr);
	स_नकल(mcast_addr->mac_list, mcast_list->mac_list,
	       mcast_list->num_multicast_addr * ETH_ALEN);

	वापस 0;
पूर्ण

/*
 * This function prepares command to deauthenticate.
 *
 * Preparation includes -
 *      - Setting command ID and proper size
 *      - Setting AP MAC address and reason code
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक mwअगरiex_cmd_802_11_deauthenticate(काष्ठा mwअगरiex_निजी *priv,
					     काष्ठा host_cmd_ds_command *cmd,
					     u8 *mac)
अणु
	काष्ठा host_cmd_ds_802_11_deauthenticate *deauth = &cmd->params.deauth;

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_DEAUTHENTICATE);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_802_11_deauthenticate)
				+ S_DS_GEN);

	/* Set AP MAC address */
	स_नकल(deauth->mac_addr, mac, ETH_ALEN);

	mwअगरiex_dbg(priv->adapter, CMD, "cmd: Deauth: %pM\n", deauth->mac_addr);

	deauth->reason_code = cpu_to_le16(WLAN_REASON_DEAUTH_LEAVING);

	वापस 0;
पूर्ण

/*
 * This function prepares command to stop Ad-Hoc network.
 *
 * Preparation includes -
 *      - Setting command ID and proper size
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक mwअगरiex_cmd_802_11_ad_hoc_stop(काष्ठा host_cmd_ds_command *cmd)
अणु
	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_AD_HOC_STOP);
	cmd->size = cpu_to_le16(S_DS_GEN);
	वापस 0;
पूर्ण

/*
 * This function sets WEP key(s) to key parameter TLV(s).
 *
 * Multi-key parameter TLVs are supported, so we can send multiple
 * WEP keys in a single buffer.
 */
अटल पूर्णांक
mwअगरiex_set_keyparamset_wep(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा mwअगरiex_ie_type_key_param_set *key_param_set,
			    u16 *key_param_len)
अणु
	पूर्णांक cur_key_param_len;
	u8 i;

	/* Multi-key_param_set TLV is supported */
	क्रम (i = 0; i < NUM_WEP_KEYS; i++) अणु
		अगर ((priv->wep_key[i].key_length == WLAN_KEY_LEN_WEP40) ||
		    (priv->wep_key[i].key_length == WLAN_KEY_LEN_WEP104)) अणु
			key_param_set->type =
				cpu_to_le16(TLV_TYPE_KEY_MATERIAL);
/* Key_param_set WEP fixed length */
#घोषणा KEYPARAMSET_WEP_FIXED_LEN 8
			key_param_set->length = cpu_to_le16((u16)
					(priv->wep_key[i].
					 key_length +
					 KEYPARAMSET_WEP_FIXED_LEN));
			key_param_set->key_type_id =
				cpu_to_le16(KEY_TYPE_ID_WEP);
			key_param_set->key_info =
				cpu_to_le16(KEY_ENABLED | KEY_UNICAST |
					    KEY_MCAST);
			key_param_set->key_len =
				cpu_to_le16(priv->wep_key[i].key_length);
			/* Set WEP key index */
			key_param_set->key[0] = i;
			/* Set शेष Tx key flag */
			अगर (i ==
			    (priv->
			     wep_key_curr_index & HostCmd_WEP_KEY_INDEX_MASK))
				key_param_set->key[1] = 1;
			अन्यथा
				key_param_set->key[1] = 0;
			स_हटाओ(&key_param_set->key[2],
				priv->wep_key[i].key_material,
				priv->wep_key[i].key_length);

			cur_key_param_len = priv->wep_key[i].key_length +
				KEYPARAMSET_WEP_FIXED_LEN +
				माप(काष्ठा mwअगरiex_ie_types_header);
			*key_param_len += (u16) cur_key_param_len;
			key_param_set =
				(काष्ठा mwअगरiex_ie_type_key_param_set *)
						((u8 *)key_param_set +
						 cur_key_param_len);
		पूर्ण अन्यथा अगर (!priv->wep_key[i].key_length) अणु
			जारी;
		पूर्ण अन्यथा अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "key%d Length = %d is incorrect\n",
				    (i + 1), priv->wep_key[i].key_length);
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* This function populates key material v2 command
 * to set network key क्रम AES & CMAC AES.
 */
अटल पूर्णांक mwअगरiex_set_aes_key_v2(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा host_cmd_ds_command *cmd,
				  काष्ठा mwअगरiex_ds_encrypt_key *enc_key,
				  काष्ठा host_cmd_ds_802_11_key_material_v2 *km)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	u16 size, len = KEY_PARAMS_FIXED_LEN;

	अगर (enc_key->is_igtk_key) अणु
		mwअगरiex_dbg(adapter, INFO,
			    "%s: Set CMAC AES Key\n", __func__);
		अगर (enc_key->is_rx_seq_valid)
			स_नकल(km->key_param_set.key_params.cmac_aes.ipn,
			       enc_key->pn, enc_key->pn_len);
		km->key_param_set.key_info &= cpu_to_le16(~KEY_MCAST);
		km->key_param_set.key_info |= cpu_to_le16(KEY_IGTK);
		km->key_param_set.key_type = KEY_TYPE_ID_AES_CMAC;
		km->key_param_set.key_params.cmac_aes.key_len =
					  cpu_to_le16(enc_key->key_len);
		स_नकल(km->key_param_set.key_params.cmac_aes.key,
		       enc_key->key_material, enc_key->key_len);
		len += माप(काष्ठा mwअगरiex_cmac_aes_param);
	पूर्ण अन्यथा अगर (enc_key->is_igtk_def_key) अणु
		mwअगरiex_dbg(adapter, INFO,
			    "%s: Set CMAC default Key index\n", __func__);
		km->key_param_set.key_type = KEY_TYPE_ID_AES_CMAC_DEF;
		km->key_param_set.key_idx = enc_key->key_index & KEY_INDEX_MASK;
	पूर्ण अन्यथा अणु
		mwअगरiex_dbg(adapter, INFO,
			    "%s: Set AES Key\n", __func__);
		अगर (enc_key->is_rx_seq_valid)
			स_नकल(km->key_param_set.key_params.aes.pn,
			       enc_key->pn, enc_key->pn_len);
		km->key_param_set.key_type = KEY_TYPE_ID_AES;
		km->key_param_set.key_params.aes.key_len =
					  cpu_to_le16(enc_key->key_len);
		स_नकल(km->key_param_set.key_params.aes.key,
		       enc_key->key_material, enc_key->key_len);
		len += माप(काष्ठा mwअगरiex_aes_param);
	पूर्ण

	km->key_param_set.len = cpu_to_le16(len);
	size = len + माप(काष्ठा mwअगरiex_ie_types_header) +
	       माप(km->action) + S_DS_GEN;
	cmd->size = cpu_to_le16(size);

	वापस 0;
पूर्ण

/* This function prepares command to set/get/reset network key(s).
 * This function prepares key material command क्रम V2 क्रमmat.
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting WEP keys, WAPI keys or WPA keys aदीर्घ with required
 *        encryption (TKIP, AES) (as required)
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक
mwअगरiex_cmd_802_11_key_material_v2(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा host_cmd_ds_command *cmd,
				   u16 cmd_action, u32 cmd_oid,
				   काष्ठा mwअगरiex_ds_encrypt_key *enc_key)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	u8 *mac = enc_key->mac_addr;
	u16 key_info, len = KEY_PARAMS_FIXED_LEN;
	काष्ठा host_cmd_ds_802_11_key_material_v2 *km =
						&cmd->params.key_material_v2;

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_KEY_MATERIAL);
	km->action = cpu_to_le16(cmd_action);

	अगर (cmd_action == HostCmd_ACT_GEN_GET) अणु
		mwअगरiex_dbg(adapter, INFO, "%s: Get key\n", __func__);
		km->key_param_set.key_idx =
					enc_key->key_index & KEY_INDEX_MASK;
		km->key_param_set.type = cpu_to_le16(TLV_TYPE_KEY_PARAM_V2);
		km->key_param_set.len = cpu_to_le16(KEY_PARAMS_FIXED_LEN);
		स_नकल(km->key_param_set.mac_addr, mac, ETH_ALEN);

		अगर (enc_key->key_index & MWIFIEX_KEY_INDEX_UNICAST)
			key_info = KEY_UNICAST;
		अन्यथा
			key_info = KEY_MCAST;

		अगर (enc_key->is_igtk_key)
			key_info |= KEY_IGTK;

		km->key_param_set.key_info = cpu_to_le16(key_info);

		cmd->size = cpu_to_le16(माप(काष्ठा mwअगरiex_ie_types_header) +
					S_DS_GEN + KEY_PARAMS_FIXED_LEN +
					माप(km->action));
		वापस 0;
	पूर्ण

	स_रखो(&km->key_param_set, 0,
	       माप(काष्ठा mwअगरiex_ie_type_key_param_set_v2));

	अगर (enc_key->key_disable) अणु
		mwअगरiex_dbg(adapter, INFO, "%s: Remove key\n", __func__);
		km->action = cpu_to_le16(HostCmd_ACT_GEN_REMOVE);
		km->key_param_set.type = cpu_to_le16(TLV_TYPE_KEY_PARAM_V2);
		km->key_param_set.len = cpu_to_le16(KEY_PARAMS_FIXED_LEN);
		km->key_param_set.key_idx = enc_key->key_index & KEY_INDEX_MASK;
		key_info = KEY_MCAST | KEY_UNICAST;
		km->key_param_set.key_info = cpu_to_le16(key_info);
		स_नकल(km->key_param_set.mac_addr, mac, ETH_ALEN);
		cmd->size = cpu_to_le16(माप(काष्ठा mwअगरiex_ie_types_header) +
					S_DS_GEN + KEY_PARAMS_FIXED_LEN +
					माप(km->action));
		वापस 0;
	पूर्ण

	km->action = cpu_to_le16(HostCmd_ACT_GEN_SET);
	km->key_param_set.key_idx = enc_key->key_index & KEY_INDEX_MASK;
	km->key_param_set.type = cpu_to_le16(TLV_TYPE_KEY_PARAM_V2);
	key_info = KEY_ENABLED;
	स_नकल(km->key_param_set.mac_addr, mac, ETH_ALEN);

	अगर (enc_key->key_len <= WLAN_KEY_LEN_WEP104) अणु
		mwअगरiex_dbg(adapter, INFO, "%s: Set WEP Key\n", __func__);
		len += माप(काष्ठा mwअगरiex_wep_param);
		km->key_param_set.len = cpu_to_le16(len);
		km->key_param_set.key_type = KEY_TYPE_ID_WEP;

		अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) अणु
				key_info |= KEY_MCAST | KEY_UNICAST;
		पूर्ण अन्यथा अणु
			अगर (enc_key->is_current_wep_key) अणु
				key_info |= KEY_MCAST | KEY_UNICAST;
				अगर (km->key_param_set.key_idx ==
				    (priv->wep_key_curr_index & KEY_INDEX_MASK))
					key_info |= KEY_DEFAULT;
			पूर्ण अन्यथा अणु
				अगर (is_broadcast_ether_addr(mac))
					key_info |= KEY_MCAST;
				अन्यथा
					key_info |= KEY_UNICAST | KEY_DEFAULT;
			पूर्ण
		पूर्ण
		km->key_param_set.key_info = cpu_to_le16(key_info);

		km->key_param_set.key_params.wep.key_len =
						  cpu_to_le16(enc_key->key_len);
		स_नकल(km->key_param_set.key_params.wep.key,
		       enc_key->key_material, enc_key->key_len);

		cmd->size = cpu_to_le16(माप(काष्ठा mwअगरiex_ie_types_header) +
					len + माप(km->action) + S_DS_GEN);
		वापस 0;
	पूर्ण

	अगर (is_broadcast_ether_addr(mac))
		key_info |= KEY_MCAST | KEY_RX_KEY;
	अन्यथा
		key_info |= KEY_UNICAST | KEY_TX_KEY | KEY_RX_KEY;

	अगर (enc_key->is_wapi_key) अणु
		mwअगरiex_dbg(adapter, INFO, "%s: Set WAPI Key\n", __func__);
		km->key_param_set.key_type = KEY_TYPE_ID_WAPI;
		स_नकल(km->key_param_set.key_params.wapi.pn, enc_key->pn,
		       PN_LEN);
		km->key_param_set.key_params.wapi.key_len =
						cpu_to_le16(enc_key->key_len);
		स_नकल(km->key_param_set.key_params.wapi.key,
		       enc_key->key_material, enc_key->key_len);
		अगर (is_broadcast_ether_addr(mac))
			priv->sec_info.wapi_key_on = true;

		अगर (!priv->sec_info.wapi_key_on)
			key_info |= KEY_DEFAULT;
		km->key_param_set.key_info = cpu_to_le16(key_info);

		len += माप(काष्ठा mwअगरiex_wapi_param);
		km->key_param_set.len = cpu_to_le16(len);
		cmd->size = cpu_to_le16(माप(काष्ठा mwअगरiex_ie_types_header) +
					len + माप(km->action) + S_DS_GEN);
		वापस 0;
	पूर्ण

	अगर (priv->bss_mode == NL80211_IFTYPE_ADHOC) अणु
		key_info |= KEY_DEFAULT;
		/* Enable unicast bit क्रम WPA-NONE/ADHOC_AES */
		अगर (!priv->sec_info.wpa2_enabled &&
		    !is_broadcast_ether_addr(mac))
			key_info |= KEY_UNICAST;
	पूर्ण अन्यथा अणु
		/* Enable शेष key क्रम WPA/WPA2 */
		अगर (!priv->wpa_is_gtk_set)
			key_info |= KEY_DEFAULT;
	पूर्ण

	km->key_param_set.key_info = cpu_to_le16(key_info);

	अगर (enc_key->key_len == WLAN_KEY_LEN_CCMP)
		वापस mwअगरiex_set_aes_key_v2(priv, cmd, enc_key, km);

	अगर (enc_key->key_len == WLAN_KEY_LEN_TKIP) अणु
		mwअगरiex_dbg(adapter, INFO,
			    "%s: Set TKIP Key\n", __func__);
		अगर (enc_key->is_rx_seq_valid)
			स_नकल(km->key_param_set.key_params.tkip.pn,
			       enc_key->pn, enc_key->pn_len);
		km->key_param_set.key_type = KEY_TYPE_ID_TKIP;
		km->key_param_set.key_params.tkip.key_len =
						cpu_to_le16(enc_key->key_len);
		स_नकल(km->key_param_set.key_params.tkip.key,
		       enc_key->key_material, enc_key->key_len);

		len += माप(काष्ठा mwअगरiex_tkip_param);
		km->key_param_set.len = cpu_to_le16(len);
		cmd->size = cpu_to_le16(माप(काष्ठा mwअगरiex_ie_types_header) +
					len + माप(km->action) + S_DS_GEN);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function prepares command to set/get/reset network key(s).
 * This function prepares key material command क्रम V1 क्रमmat.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting WEP keys, WAPI keys or WPA keys aदीर्घ with required
 *        encryption (TKIP, AES) (as required)
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक
mwअगरiex_cmd_802_11_key_material_v1(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा host_cmd_ds_command *cmd,
				   u16 cmd_action, u32 cmd_oid,
				   काष्ठा mwअगरiex_ds_encrypt_key *enc_key)
अणु
	काष्ठा host_cmd_ds_802_11_key_material *key_material =
		&cmd->params.key_material;
	काष्ठा host_cmd_tlv_mac_addr *tlv_mac;
	u16 key_param_len = 0, cmd_size;
	पूर्णांक ret = 0;

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_KEY_MATERIAL);
	key_material->action = cpu_to_le16(cmd_action);

	अगर (cmd_action == HostCmd_ACT_GEN_GET) अणु
		cmd->size =
			cpu_to_le16(माप(key_material->action) + S_DS_GEN);
		वापस ret;
	पूर्ण

	अगर (!enc_key) अणु
		स_रखो(&key_material->key_param_set, 0,
		       (NUM_WEP_KEYS *
			माप(काष्ठा mwअगरiex_ie_type_key_param_set)));
		ret = mwअगरiex_set_keyparamset_wep(priv,
						  &key_material->key_param_set,
						  &key_param_len);
		cmd->size = cpu_to_le16(key_param_len +
				    माप(key_material->action) + S_DS_GEN);
		वापस ret;
	पूर्ण अन्यथा
		स_रखो(&key_material->key_param_set, 0,
		       माप(काष्ठा mwअगरiex_ie_type_key_param_set));
	अगर (enc_key->is_wapi_key) अणु
		काष्ठा mwअगरiex_ie_type_key_param_set *set;

		mwअगरiex_dbg(priv->adapter, INFO, "info: Set WAPI Key\n");
		set = &key_material->key_param_set;
		set->key_type_id = cpu_to_le16(KEY_TYPE_ID_WAPI);
		अगर (cmd_oid == KEY_INFO_ENABLED)
			set->key_info = cpu_to_le16(KEY_ENABLED);
		अन्यथा
			set->key_info = cpu_to_le16(!KEY_ENABLED);

		set->key[0] = enc_key->key_index;
		अगर (!priv->sec_info.wapi_key_on)
			set->key[1] = 1;
		अन्यथा
			/* set 0 when re-key */
			set->key[1] = 0;

		अगर (!is_broadcast_ether_addr(enc_key->mac_addr)) अणु
			/* WAPI pairwise key: unicast */
			set->key_info |= cpu_to_le16(KEY_UNICAST);
		पूर्ण अन्यथा अणु	/* WAPI group key: multicast */
			set->key_info |= cpu_to_le16(KEY_MCAST);
			priv->sec_info.wapi_key_on = true;
		पूर्ण

		set->type = cpu_to_le16(TLV_TYPE_KEY_MATERIAL);
		set->key_len = cpu_to_le16(WAPI_KEY_LEN);
		स_नकल(&set->key[2], enc_key->key_material, enc_key->key_len);
		स_नकल(&set->key[2 + enc_key->key_len], enc_key->pn, PN_LEN);
		set->length = cpu_to_le16(WAPI_KEY_LEN + KEYPARAMSET_FIXED_LEN);

		key_param_len = (WAPI_KEY_LEN + KEYPARAMSET_FIXED_LEN) +
				 माप(काष्ठा mwअगरiex_ie_types_header);
		cmd->size = cpu_to_le16(माप(key_material->action)
					+ S_DS_GEN +  key_param_len);
		वापस ret;
	पूर्ण
	अगर (enc_key->key_len == WLAN_KEY_LEN_CCMP) अणु
		अगर (enc_key->is_igtk_key) अणु
			mwअगरiex_dbg(priv->adapter, CMD, "cmd: CMAC_AES\n");
			key_material->key_param_set.key_type_id =
					cpu_to_le16(KEY_TYPE_ID_AES_CMAC);
			अगर (cmd_oid == KEY_INFO_ENABLED)
				key_material->key_param_set.key_info =
						cpu_to_le16(KEY_ENABLED);
			अन्यथा
				key_material->key_param_set.key_info =
						cpu_to_le16(!KEY_ENABLED);

			key_material->key_param_set.key_info |=
							cpu_to_le16(KEY_IGTK);
		पूर्ण अन्यथा अणु
			mwअगरiex_dbg(priv->adapter, CMD, "cmd: WPA_AES\n");
			key_material->key_param_set.key_type_id =
						cpu_to_le16(KEY_TYPE_ID_AES);
			अगर (cmd_oid == KEY_INFO_ENABLED)
				key_material->key_param_set.key_info =
						cpu_to_le16(KEY_ENABLED);
			अन्यथा
				key_material->key_param_set.key_info =
						cpu_to_le16(!KEY_ENABLED);

			अगर (enc_key->key_index & MWIFIEX_KEY_INDEX_UNICAST)
				/* AES pairwise key: unicast */
				key_material->key_param_set.key_info |=
						cpu_to_le16(KEY_UNICAST);
			अन्यथा	/* AES group key: multicast */
				key_material->key_param_set.key_info |=
							cpu_to_le16(KEY_MCAST);
		पूर्ण
	पूर्ण अन्यथा अगर (enc_key->key_len == WLAN_KEY_LEN_TKIP) अणु
		mwअगरiex_dbg(priv->adapter, CMD, "cmd: WPA_TKIP\n");
		key_material->key_param_set.key_type_id =
						cpu_to_le16(KEY_TYPE_ID_TKIP);
		key_material->key_param_set.key_info =
						cpu_to_le16(KEY_ENABLED);

		अगर (enc_key->key_index & MWIFIEX_KEY_INDEX_UNICAST)
				/* TKIP pairwise key: unicast */
			key_material->key_param_set.key_info |=
						cpu_to_le16(KEY_UNICAST);
		अन्यथा		/* TKIP group key: multicast */
			key_material->key_param_set.key_info |=
							cpu_to_le16(KEY_MCAST);
	पूर्ण

	अगर (key_material->key_param_set.key_type_id) अणु
		key_material->key_param_set.type =
					cpu_to_le16(TLV_TYPE_KEY_MATERIAL);
		key_material->key_param_set.key_len =
					cpu_to_le16((u16) enc_key->key_len);
		स_नकल(key_material->key_param_set.key, enc_key->key_material,
		       enc_key->key_len);
		key_material->key_param_set.length =
			cpu_to_le16((u16) enc_key->key_len +
				    KEYPARAMSET_FIXED_LEN);

		key_param_len = (u16)(enc_key->key_len + KEYPARAMSET_FIXED_LEN)
				+ माप(काष्ठा mwअगरiex_ie_types_header);

		अगर (le16_to_cpu(key_material->key_param_set.key_type_id) ==
							KEY_TYPE_ID_AES_CMAC) अणु
			काष्ठा mwअगरiex_cmac_param *param =
					(व्योम *)key_material->key_param_set.key;

			स_नकल(param->ipn, enc_key->pn, IGTK_PN_LEN);
			स_नकल(param->key, enc_key->key_material,
			       WLAN_KEY_LEN_AES_CMAC);

			key_param_len = माप(काष्ठा mwअगरiex_cmac_param);
			key_material->key_param_set.key_len =
						cpu_to_le16(key_param_len);
			key_param_len += KEYPARAMSET_FIXED_LEN;
			key_material->key_param_set.length =
						cpu_to_le16(key_param_len);
			key_param_len += माप(काष्ठा mwअगरiex_ie_types_header);
		पूर्ण

		cmd->size = cpu_to_le16(माप(key_material->action) + S_DS_GEN
					+ key_param_len);

		अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) अणु
			tlv_mac = (व्योम *)((u8 *)&key_material->key_param_set +
					   key_param_len);
			tlv_mac->header.type =
					cpu_to_le16(TLV_TYPE_STA_MAC_ADDR);
			tlv_mac->header.len = cpu_to_le16(ETH_ALEN);
			स_नकल(tlv_mac->mac_addr, enc_key->mac_addr, ETH_ALEN);
			cmd_size = key_param_len + S_DS_GEN +
				   माप(key_material->action) +
				   माप(काष्ठा host_cmd_tlv_mac_addr);
		पूर्ण अन्यथा अणु
			cmd_size = key_param_len + S_DS_GEN +
				   माप(key_material->action);
		पूर्ण
		cmd->size = cpu_to_le16(cmd_size);
	पूर्ण

	वापस ret;
पूर्ण

/* Wrapper function क्रम setting network key depending upon FW KEY API version */
अटल पूर्णांक
mwअगरiex_cmd_802_11_key_material(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा host_cmd_ds_command *cmd,
				u16 cmd_action, u32 cmd_oid,
				काष्ठा mwअगरiex_ds_encrypt_key *enc_key)
अणु
	अगर (priv->adapter->key_api_major_ver == KEY_API_VER_MAJOR_V2)
		वापस mwअगरiex_cmd_802_11_key_material_v2(priv, cmd,
							  cmd_action, cmd_oid,
							  enc_key);

	अन्यथा
		वापस mwअगरiex_cmd_802_11_key_material_v1(priv, cmd,
							  cmd_action, cmd_oid,
							  enc_key);
पूर्ण

/*
 * This function prepares command to set/get 11d करोमुख्य inक्रमmation.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting करोमुख्य inक्रमmation fields (क्रम SET only)
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक mwअगरiex_cmd_802_11d_करोमुख्य_info(काष्ठा mwअगरiex_निजी *priv,
					   काष्ठा host_cmd_ds_command *cmd,
					   u16 cmd_action)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा host_cmd_ds_802_11d_करोमुख्य_info *करोमुख्य_info =
		&cmd->params.करोमुख्य_info;
	काष्ठा mwअगरiex_ietypes_करोमुख्य_param_set *करोमुख्य =
		&करोमुख्य_info->करोमुख्य;
	u8 no_of_triplet = adapter->करोमुख्य_reg.no_of_triplet;

	mwअगरiex_dbg(adapter, INFO,
		    "info: 11D: no_of_triplet=0x%x\n", no_of_triplet);

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11D_DOMAIN_INFO);
	करोमुख्य_info->action = cpu_to_le16(cmd_action);
	अगर (cmd_action == HostCmd_ACT_GEN_GET) अणु
		cmd->size = cpu_to_le16(माप(करोमुख्य_info->action) + S_DS_GEN);
		वापस 0;
	पूर्ण

	/* Set करोमुख्य info fields */
	करोमुख्य->header.type = cpu_to_le16(WLAN_EID_COUNTRY);
	स_नकल(करोमुख्य->country_code, adapter->करोमुख्य_reg.country_code,
	       माप(करोमुख्य->country_code));

	करोमुख्य->header.len =
		cpu_to_le16((no_of_triplet *
			     माप(काष्ठा ieee80211_country_ie_triplet))
			    + माप(करोमुख्य->country_code));

	अगर (no_of_triplet) अणु
		स_नकल(करोमुख्य->triplet, adapter->करोमुख्य_reg.triplet,
		       no_of_triplet * माप(काष्ठा
					      ieee80211_country_ie_triplet));

		cmd->size = cpu_to_le16(माप(करोमुख्य_info->action) +
					le16_to_cpu(करोमुख्य->header.len) +
					माप(काष्ठा mwअगरiex_ie_types_header)
					+ S_DS_GEN);
	पूर्ण अन्यथा अणु
		cmd->size = cpu_to_le16(माप(करोमुख्य_info->action) + S_DS_GEN);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function prepares command to set/get IBSS coalescing status.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting status to enable or disable (क्रम SET only)
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक mwअगरiex_cmd_ibss_coalescing_status(काष्ठा host_cmd_ds_command *cmd,
					      u16 cmd_action, u16 *enable)
अणु
	काष्ठा host_cmd_ds_802_11_ibss_status *ibss_coal =
		&(cmd->params.ibss_coalescing);

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_IBSS_COALESCING_STATUS);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_802_11_ibss_status) +
				S_DS_GEN);
	cmd->result = 0;
	ibss_coal->action = cpu_to_le16(cmd_action);

	चयन (cmd_action) अणु
	हाल HostCmd_ACT_GEN_SET:
		अगर (enable)
			ibss_coal->enable = cpu_to_le16(*enable);
		अन्यथा
			ibss_coal->enable = 0;
		अवरोध;

		/* In other हाल.. Nothing to करो */
	हाल HostCmd_ACT_GEN_GET:
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* This function prepares command buffer to get/set memory location value.
 */
अटल पूर्णांक
mwअगरiex_cmd_mem_access(काष्ठा host_cmd_ds_command *cmd, u16 cmd_action,
		       व्योम *pdata_buf)
अणु
	काष्ठा mwअगरiex_ds_mem_rw *mem_rw = (व्योम *)pdata_buf;
	काष्ठा host_cmd_ds_mem_access *mem_access = (व्योम *)&cmd->params.mem;

	cmd->command = cpu_to_le16(HostCmd_CMD_MEM_ACCESS);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_mem_access) +
				S_DS_GEN);

	mem_access->action = cpu_to_le16(cmd_action);
	mem_access->addr = cpu_to_le32(mem_rw->addr);
	mem_access->value = cpu_to_le32(mem_rw->value);

	वापस 0;
पूर्ण

/*
 * This function prepares command to set/get रेजिस्टर value.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting रेजिस्टर offset (क्रम both GET and SET) and
 *        रेजिस्टर value (क्रम SET only)
 *      - Ensuring correct endian-ness
 *
 * The following type of रेजिस्टरs can be accessed with this function -
 *      - MAC रेजिस्टर
 *      - BBP रेजिस्टर
 *      - RF रेजिस्टर
 *      - PMIC रेजिस्टर
 *      - CAU रेजिस्टर
 *      - EEPROM
 */
अटल पूर्णांक mwअगरiex_cmd_reg_access(काष्ठा host_cmd_ds_command *cmd,
				  u16 cmd_action, व्योम *data_buf)
अणु
	काष्ठा mwअगरiex_ds_reg_rw *reg_rw = data_buf;

	चयन (le16_to_cpu(cmd->command)) अणु
	हाल HostCmd_CMD_MAC_REG_ACCESS:
	अणु
		काष्ठा host_cmd_ds_mac_reg_access *mac_reg;

		cmd->size = cpu_to_le16(माप(*mac_reg) + S_DS_GEN);
		mac_reg = &cmd->params.mac_reg;
		mac_reg->action = cpu_to_le16(cmd_action);
		mac_reg->offset = cpu_to_le16((u16) reg_rw->offset);
		mac_reg->value = cpu_to_le32(reg_rw->value);
		अवरोध;
	पूर्ण
	हाल HostCmd_CMD_BBP_REG_ACCESS:
	अणु
		काष्ठा host_cmd_ds_bbp_reg_access *bbp_reg;

		cmd->size = cpu_to_le16(माप(*bbp_reg) + S_DS_GEN);
		bbp_reg = &cmd->params.bbp_reg;
		bbp_reg->action = cpu_to_le16(cmd_action);
		bbp_reg->offset = cpu_to_le16((u16) reg_rw->offset);
		bbp_reg->value = (u8) reg_rw->value;
		अवरोध;
	पूर्ण
	हाल HostCmd_CMD_RF_REG_ACCESS:
	अणु
		काष्ठा host_cmd_ds_rf_reg_access *rf_reg;

		cmd->size = cpu_to_le16(माप(*rf_reg) + S_DS_GEN);
		rf_reg = &cmd->params.rf_reg;
		rf_reg->action = cpu_to_le16(cmd_action);
		rf_reg->offset = cpu_to_le16((u16) reg_rw->offset);
		rf_reg->value = (u8) reg_rw->value;
		अवरोध;
	पूर्ण
	हाल HostCmd_CMD_PMIC_REG_ACCESS:
	अणु
		काष्ठा host_cmd_ds_pmic_reg_access *pmic_reg;

		cmd->size = cpu_to_le16(माप(*pmic_reg) + S_DS_GEN);
		pmic_reg = &cmd->params.pmic_reg;
		pmic_reg->action = cpu_to_le16(cmd_action);
		pmic_reg->offset = cpu_to_le16((u16) reg_rw->offset);
		pmic_reg->value = (u8) reg_rw->value;
		अवरोध;
	पूर्ण
	हाल HostCmd_CMD_CAU_REG_ACCESS:
	अणु
		काष्ठा host_cmd_ds_rf_reg_access *cau_reg;

		cmd->size = cpu_to_le16(माप(*cau_reg) + S_DS_GEN);
		cau_reg = &cmd->params.rf_reg;
		cau_reg->action = cpu_to_le16(cmd_action);
		cau_reg->offset = cpu_to_le16((u16) reg_rw->offset);
		cau_reg->value = (u8) reg_rw->value;
		अवरोध;
	पूर्ण
	हाल HostCmd_CMD_802_11_EEPROM_ACCESS:
	अणु
		काष्ठा mwअगरiex_ds_पढ़ो_eeprom *rd_eeprom = data_buf;
		काष्ठा host_cmd_ds_802_11_eeprom_access *cmd_eeprom =
			&cmd->params.eeprom;

		cmd->size = cpu_to_le16(माप(*cmd_eeprom) + S_DS_GEN);
		cmd_eeprom->action = cpu_to_le16(cmd_action);
		cmd_eeprom->offset = cpu_to_le16(rd_eeprom->offset);
		cmd_eeprom->byte_count = cpu_to_le16(rd_eeprom->byte_count);
		cmd_eeprom->value = 0;
		अवरोध;
	पूर्ण
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function prepares command to set PCI-Express
 * host buffer configuration
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Setting host buffer configuration
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक
mwअगरiex_cmd_pcie_host_spec(काष्ठा mwअगरiex_निजी *priv,
			   काष्ठा host_cmd_ds_command *cmd, u16 action)
अणु
	काष्ठा host_cmd_ds_pcie_details *host_spec =
					&cmd->params.pcie_host_spec;
	काष्ठा pcie_service_card *card = priv->adapter->card;

	cmd->command = cpu_to_le16(HostCmd_CMD_PCIE_DESC_DETAILS);
	cmd->size = cpu_to_le16(माप(काष्ठा
					host_cmd_ds_pcie_details) + S_DS_GEN);
	cmd->result = 0;

	स_रखो(host_spec, 0, माप(काष्ठा host_cmd_ds_pcie_details));

	अगर (action != HostCmd_ACT_GEN_SET)
		वापस 0;

	/* Send the ring base addresses and count to firmware */
	host_spec->txbd_addr_lo = cpu_to_le32((u32)(card->txbd_ring_pbase));
	host_spec->txbd_addr_hi =
			cpu_to_le32((u32)(((u64)card->txbd_ring_pbase) >> 32));
	host_spec->txbd_count = cpu_to_le32(MWIFIEX_MAX_TXRX_BD);
	host_spec->rxbd_addr_lo = cpu_to_le32((u32)(card->rxbd_ring_pbase));
	host_spec->rxbd_addr_hi =
			cpu_to_le32((u32)(((u64)card->rxbd_ring_pbase) >> 32));
	host_spec->rxbd_count = cpu_to_le32(MWIFIEX_MAX_TXRX_BD);
	host_spec->evtbd_addr_lo = cpu_to_le32((u32)(card->evtbd_ring_pbase));
	host_spec->evtbd_addr_hi =
			cpu_to_le32((u32)(((u64)card->evtbd_ring_pbase) >> 32));
	host_spec->evtbd_count = cpu_to_le32(MWIFIEX_MAX_EVT_BD);
	अगर (card->sleep_cookie_vbase) अणु
		host_spec->sleep_cookie_addr_lo =
				cpu_to_le32((u32)(card->sleep_cookie_pbase));
		host_spec->sleep_cookie_addr_hi = cpu_to_le32((u32)(((u64)
					(card->sleep_cookie_pbase)) >> 32));
		mwअगरiex_dbg(priv->adapter, INFO,
			    "sleep_cook_lo phy addr: 0x%x\n",
			    host_spec->sleep_cookie_addr_lo);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function prepares command क्रम event subscription, configuration
 * and query. Events can be subscribed or unsubscribed. Current subscribed
 * events can be queried. Also, current subscribed events are reported in
 * every FW response.
 */
अटल पूर्णांक
mwअगरiex_cmd_802_11_subsc_evt(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा host_cmd_ds_command *cmd,
			     काष्ठा mwअगरiex_ds_misc_subsc_evt *subsc_evt_cfg)
अणु
	काष्ठा host_cmd_ds_802_11_subsc_evt *subsc_evt = &cmd->params.subsc_evt;
	काष्ठा mwअगरiex_ie_types_rssi_threshold *rssi_tlv;
	u16 event_biपंचांगap;
	u8 *pos;

	cmd->command = cpu_to_le16(HostCmd_CMD_802_11_SUBSCRIBE_EVENT);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_802_11_subsc_evt) +
				S_DS_GEN);

	subsc_evt->action = cpu_to_le16(subsc_evt_cfg->action);
	mwअगरiex_dbg(priv->adapter, CMD,
		    "cmd: action: %d\n", subsc_evt_cfg->action);

	/*For query requests, no configuration TLV काष्ठाures are to be added.*/
	अगर (subsc_evt_cfg->action == HostCmd_ACT_GEN_GET)
		वापस 0;

	subsc_evt->events = cpu_to_le16(subsc_evt_cfg->events);

	event_biपंचांगap = subsc_evt_cfg->events;
	mwअगरiex_dbg(priv->adapter, CMD, "cmd: event bitmap : %16x\n",
		    event_biपंचांगap);

	अगर (((subsc_evt_cfg->action == HostCmd_ACT_BITWISE_CLR) ||
	     (subsc_evt_cfg->action == HostCmd_ACT_BITWISE_SET)) &&
	    (event_biपंचांगap == 0)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Error: No event specified\t"
			    "for bitwise action type\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Append TLV काष्ठाures क्रम each of the specअगरied events क्रम
	 * subscribing or re-configuring. This is not required क्रम
	 * bitwise unsubscribing request.
	 */
	अगर (subsc_evt_cfg->action == HostCmd_ACT_BITWISE_CLR)
		वापस 0;

	pos = ((u8 *)subsc_evt) +
			माप(काष्ठा host_cmd_ds_802_11_subsc_evt);

	अगर (event_biपंचांगap & BITMASK_BCN_RSSI_LOW) अणु
		rssi_tlv = (काष्ठा mwअगरiex_ie_types_rssi_threshold *) pos;

		rssi_tlv->header.type = cpu_to_le16(TLV_TYPE_RSSI_LOW);
		rssi_tlv->header.len =
		    cpu_to_le16(माप(काष्ठा mwअगरiex_ie_types_rssi_threshold) -
				माप(काष्ठा mwअगरiex_ie_types_header));
		rssi_tlv->असल_value = subsc_evt_cfg->bcn_l_rssi_cfg.असल_value;
		rssi_tlv->evt_freq = subsc_evt_cfg->bcn_l_rssi_cfg.evt_freq;

		mwअगरiex_dbg(priv->adapter, EVENT,
			    "Cfg Beacon Low Rssi event,\t"
			    "RSSI:-%d dBm, Freq:%d\n",
			    subsc_evt_cfg->bcn_l_rssi_cfg.असल_value,
			    subsc_evt_cfg->bcn_l_rssi_cfg.evt_freq);

		pos += माप(काष्ठा mwअगरiex_ie_types_rssi_threshold);
		le16_unaligned_add_cpu(&cmd->size,
				       माप(
				       काष्ठा mwअगरiex_ie_types_rssi_threshold));
	पूर्ण

	अगर (event_biपंचांगap & BITMASK_BCN_RSSI_HIGH) अणु
		rssi_tlv = (काष्ठा mwअगरiex_ie_types_rssi_threshold *) pos;

		rssi_tlv->header.type = cpu_to_le16(TLV_TYPE_RSSI_HIGH);
		rssi_tlv->header.len =
		    cpu_to_le16(माप(काष्ठा mwअगरiex_ie_types_rssi_threshold) -
				माप(काष्ठा mwअगरiex_ie_types_header));
		rssi_tlv->असल_value = subsc_evt_cfg->bcn_h_rssi_cfg.असल_value;
		rssi_tlv->evt_freq = subsc_evt_cfg->bcn_h_rssi_cfg.evt_freq;

		mwअगरiex_dbg(priv->adapter, EVENT,
			    "Cfg Beacon High Rssi event,\t"
			    "RSSI:-%d dBm, Freq:%d\n",
			    subsc_evt_cfg->bcn_h_rssi_cfg.असल_value,
			    subsc_evt_cfg->bcn_h_rssi_cfg.evt_freq);

		pos += माप(काष्ठा mwअगरiex_ie_types_rssi_threshold);
		le16_unaligned_add_cpu(&cmd->size,
				       माप(
				       काष्ठा mwअगरiex_ie_types_rssi_threshold));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_cmd_append_rpn_expression(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा mwअगरiex_mef_entry *mef_entry,
				  u8 **buffer)
अणु
	काष्ठा mwअगरiex_mef_filter *filter = mef_entry->filter;
	पूर्णांक i, byte_len;
	u8 *stack_ptr = *buffer;

	क्रम (i = 0; i < MWIFIEX_MEF_MAX_FILTERS; i++) अणु
		filter = &mef_entry->filter[i];
		अगर (!filter->filt_type)
			अवरोध;
		put_unaligned_le32((u32)filter->repeat, stack_ptr);
		stack_ptr += 4;
		*stack_ptr = TYPE_DNUM;
		stack_ptr += 1;

		byte_len = filter->byte_seq[MWIFIEX_MEF_MAX_BYTESEQ];
		स_नकल(stack_ptr, filter->byte_seq, byte_len);
		stack_ptr += byte_len;
		*stack_ptr = byte_len;
		stack_ptr += 1;
		*stack_ptr = TYPE_BYTESEQ;
		stack_ptr += 1;
		put_unaligned_le32((u32)filter->offset, stack_ptr);
		stack_ptr += 4;
		*stack_ptr = TYPE_DNUM;
		stack_ptr += 1;

		*stack_ptr = filter->filt_type;
		stack_ptr += 1;

		अगर (filter->filt_action) अणु
			*stack_ptr = filter->filt_action;
			stack_ptr += 1;
		पूर्ण

		अगर (stack_ptr - *buffer > STACK_NBYTES)
			वापस -1;
	पूर्ण

	*buffer = stack_ptr;
	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_cmd_mef_cfg(काष्ठा mwअगरiex_निजी *priv,
		    काष्ठा host_cmd_ds_command *cmd,
		    काष्ठा mwअगरiex_ds_mef_cfg *mef)
अणु
	काष्ठा host_cmd_ds_mef_cfg *mef_cfg = &cmd->params.mef_cfg;
	काष्ठा mwअगरiex_fw_mef_entry *mef_entry = शून्य;
	u8 *pos = (u8 *)mef_cfg;
	u16 i;

	cmd->command = cpu_to_le16(HostCmd_CMD_MEF_CFG);

	mef_cfg->criteria = cpu_to_le32(mef->criteria);
	mef_cfg->num_entries = cpu_to_le16(mef->num_entries);
	pos += माप(*mef_cfg);

	क्रम (i = 0; i < mef->num_entries; i++) अणु
		mef_entry = (काष्ठा mwअगरiex_fw_mef_entry *)pos;
		mef_entry->mode = mef->mef_entry[i].mode;
		mef_entry->action = mef->mef_entry[i].action;
		pos += माप(*mef_cfg->mef_entry);

		अगर (mwअगरiex_cmd_append_rpn_expression(priv,
						      &mef->mef_entry[i], &pos))
			वापस -1;

		mef_entry->exprsize =
			cpu_to_le16(pos - mef_entry->expr);
	पूर्ण
	cmd->size = cpu_to_le16((u16) (pos - (u8 *)mef_cfg) + S_DS_GEN);

	वापस 0;
पूर्ण

/* This function parse cal data from ASCII to hex */
अटल u32 mwअगरiex_parse_cal_cfg(u8 *src, माप_प्रकार len, u8 *dst)
अणु
	u8 *s = src, *d = dst;

	जबतक (s - src < len) अणु
		अगर (*s && (है_खाली(*s) || *s == '\t')) अणु
			s++;
			जारी;
		पूर्ण
		अगर (है_षष्ठादशक(*s)) अणु
			*d++ = simple_म_से_दीर्घ(s, शून्य, 16);
			s += 2;
		पूर्ण अन्यथा अणु
			s++;
		पूर्ण
	पूर्ण

	वापस d - dst;
पूर्ण

पूर्णांक mwअगरiex_dnld_dt_cfgdata(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा device_node *node, स्थिर अक्षर *prefix)
अणु
#अगर_घोषित CONFIG_OF
	काष्ठा property *prop;
	माप_प्रकार len = म_माप(prefix);
	पूर्णांक ret;

	/* look क्रम all matching property names */
	क्रम_each_property_of_node(node, prop) अणु
		अगर (len > म_माप(prop->name) ||
		    म_भेदन(prop->name, prefix, len))
			जारी;

		/* property header is 6 bytes, data must fit in cmd buffer */
		अगर (prop->value && prop->length > 6 &&
		    prop->length <= MWIFIEX_SIZE_OF_CMD_BUFFER - S_DS_GEN) अणु
			ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_CFG_DATA,
					       HostCmd_ACT_GEN_SET, 0,
					       prop, true);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* This function prepares command of set_cfg_data. */
अटल पूर्णांक mwअगरiex_cmd_cfg_data(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा host_cmd_ds_command *cmd, व्योम *data_buf)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा property *prop = data_buf;
	u32 len;
	u8 *data = (u8 *)cmd + S_DS_GEN;
	पूर्णांक ret;

	अगर (prop) अणु
		len = prop->length;
		ret = of_property_पढ़ो_u8_array(adapter->dt_node, prop->name,
						data, len);
		अगर (ret)
			वापस ret;
		mwअगरiex_dbg(adapter, INFO,
			    "download cfg_data from device tree: %s\n",
			    prop->name);
	पूर्ण अन्यथा अगर (adapter->cal_data->data && adapter->cal_data->size > 0) अणु
		len = mwअगरiex_parse_cal_cfg((u8 *)adapter->cal_data->data,
					    adapter->cal_data->size, data);
		mwअगरiex_dbg(adapter, INFO,
			    "download cfg_data from config file\n");
	पूर्ण अन्यथा अणु
		वापस -1;
	पूर्ण

	cmd->command = cpu_to_le16(HostCmd_CMD_CFG_DATA);
	cmd->size = cpu_to_le16(S_DS_GEN + len);

	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_cmd_set_mc_policy(काष्ठा mwअगरiex_निजी *priv,
			  काष्ठा host_cmd_ds_command *cmd,
			  u16 cmd_action, व्योम *data_buf)
अणु
	काष्ठा host_cmd_ds_multi_chan_policy *mc_pol = &cmd->params.mc_policy;
	स्थिर u16 *drcs_info = data_buf;

	mc_pol->action = cpu_to_le16(cmd_action);
	mc_pol->policy = cpu_to_le16(*drcs_info);
	cmd->command = cpu_to_le16(HostCmd_CMD_MC_POLICY);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_multi_chan_policy) +
				S_DS_GEN);
	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_cmd_robust_coex(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा host_cmd_ds_command *cmd,
				   u16 cmd_action, bool *is_बारhare)
अणु
	काष्ठा host_cmd_ds_robust_coex *coex = &cmd->params.coex;
	काष्ठा mwअगरiex_ie_types_robust_coex *coex_tlv;

	cmd->command = cpu_to_le16(HostCmd_CMD_ROBUST_COEX);
	cmd->size = cpu_to_le16(माप(*coex) + माप(*coex_tlv) + S_DS_GEN);

	coex->action = cpu_to_le16(cmd_action);
	coex_tlv = (काष्ठा mwअगरiex_ie_types_robust_coex *)
				((u8 *)coex + माप(*coex));
	coex_tlv->header.type = cpu_to_le16(TLV_TYPE_ROBUST_COEX);
	coex_tlv->header.len = cpu_to_le16(माप(coex_tlv->mode));

	अगर (coex->action == HostCmd_ACT_GEN_GET)
		वापस 0;

	अगर (*is_बारhare)
		coex_tlv->mode = cpu_to_le32(MWIFIEX_COEX_MODE_TIMESHARE);
	अन्यथा
		coex_tlv->mode = cpu_to_le32(MWIFIEX_COEX_MODE_SPATIAL);

	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_cmd_gtk_rekey_offload(काष्ठा mwअगरiex_निजी *priv,
					 काष्ठा host_cmd_ds_command *cmd,
					 u16 cmd_action,
					 काष्ठा cfg80211_gtk_rekey_data *data)
अणु
	काष्ठा host_cmd_ds_gtk_rekey_params *rekey = &cmd->params.rekey;
	u64 rekey_ctr;

	cmd->command = cpu_to_le16(HostCmd_CMD_GTK_REKEY_OFFLOAD_CFG);
	cmd->size = cpu_to_le16(माप(*rekey) + S_DS_GEN);

	rekey->action = cpu_to_le16(cmd_action);
	अगर (cmd_action == HostCmd_ACT_GEN_SET) अणु
		स_नकल(rekey->kek, data->kek, NL80211_KEK_LEN);
		स_नकल(rekey->kck, data->kck, NL80211_KCK_LEN);
		rekey_ctr = be64_to_cpup((__be64 *)data->replay_ctr);
		rekey->replay_ctr_low = cpu_to_le32((u32)rekey_ctr);
		rekey->replay_ctr_high =
			cpu_to_le32((u32)((u64)rekey_ctr >> 32));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_cmd_chan_region_cfg(काष्ठा mwअगरiex_निजी *priv,
				       काष्ठा host_cmd_ds_command *cmd,
				       u16 cmd_action)
अणु
	काष्ठा host_cmd_ds_chan_region_cfg *reg = &cmd->params.reg_cfg;

	cmd->command = cpu_to_le16(HostCmd_CMD_CHAN_REGION_CFG);
	cmd->size = cpu_to_le16(माप(*reg) + S_DS_GEN);

	अगर (cmd_action == HostCmd_ACT_GEN_GET)
		reg->action = cpu_to_le16(cmd_action);

	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_cmd_coalesce_cfg(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा host_cmd_ds_command *cmd,
			 u16 cmd_action, व्योम *data_buf)
अणु
	काष्ठा host_cmd_ds_coalesce_cfg *coalesce_cfg =
						&cmd->params.coalesce_cfg;
	काष्ठा mwअगरiex_ds_coalesce_cfg *cfg = data_buf;
	काष्ठा coalesce_filt_field_param *param;
	u16 cnt, idx, length;
	काष्ठा coalesce_receive_filt_rule *rule;

	cmd->command = cpu_to_le16(HostCmd_CMD_COALESCE_CFG);
	cmd->size = cpu_to_le16(S_DS_GEN);

	coalesce_cfg->action = cpu_to_le16(cmd_action);
	coalesce_cfg->num_of_rules = cpu_to_le16(cfg->num_of_rules);
	rule = coalesce_cfg->rule;

	क्रम (cnt = 0; cnt < cfg->num_of_rules; cnt++) अणु
		rule->header.type = cpu_to_le16(TLV_TYPE_COALESCE_RULE);
		rule->max_coalescing_delay =
			cpu_to_le16(cfg->rule[cnt].max_coalescing_delay);
		rule->pkt_type = cfg->rule[cnt].pkt_type;
		rule->num_of_fields = cfg->rule[cnt].num_of_fields;

		length = 0;

		param = rule->params;
		क्रम (idx = 0; idx < cfg->rule[cnt].num_of_fields; idx++) अणु
			param->operation = cfg->rule[cnt].params[idx].operation;
			param->opeअक्रम_len =
					cfg->rule[cnt].params[idx].opeअक्रम_len;
			param->offset =
				cpu_to_le16(cfg->rule[cnt].params[idx].offset);
			स_नकल(param->opeअक्रम_byte_stream,
			       cfg->rule[cnt].params[idx].opeअक्रम_byte_stream,
			       param->opeअक्रम_len);

			length += माप(काष्ठा coalesce_filt_field_param);

			param++;
		पूर्ण

		/* Total rule length is माप max_coalescing_delay(u16),
		 * num_of_fields(u8), pkt_type(u8) and total length of the all
		 * params
		 */
		rule->header.len = cpu_to_le16(length + माप(u16) +
					       माप(u8) + माप(u8));

		/* Add the rule length to the command size*/
		le16_unaligned_add_cpu(&cmd->size,
				       le16_to_cpu(rule->header.len) +
				       माप(काष्ठा mwअगरiex_ie_types_header));

		rule = (व्योम *)((u8 *)rule->params + length);
	पूर्ण

	/* Add माप action, num_of_rules to total command length */
	le16_unaligned_add_cpu(&cmd->size, माप(u16) + माप(u16));

	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_cmd_tdls_config(काष्ठा mwअगरiex_निजी *priv,
			काष्ठा host_cmd_ds_command *cmd,
			u16 cmd_action, व्योम *data_buf)
अणु
	काष्ठा host_cmd_ds_tdls_config *tdls_config = &cmd->params.tdls_config;
	काष्ठा mwअगरiex_tdls_init_cs_params *config;
	काष्ठा mwअगरiex_tdls_config *init_config;
	u16 len;

	cmd->command = cpu_to_le16(HostCmd_CMD_TDLS_CONFIG);
	cmd->size = cpu_to_le16(S_DS_GEN);
	tdls_config->tdls_action = cpu_to_le16(cmd_action);
	le16_unaligned_add_cpu(&cmd->size, माप(tdls_config->tdls_action));

	चयन (cmd_action) अणु
	हाल ACT_TDLS_CS_ENABLE_CONFIG:
		init_config = data_buf;
		len = माप(*init_config);
		स_नकल(tdls_config->tdls_data, init_config, len);
		अवरोध;
	हाल ACT_TDLS_CS_INIT:
		config = data_buf;
		len = माप(*config);
		स_नकल(tdls_config->tdls_data, config, len);
		अवरोध;
	हाल ACT_TDLS_CS_STOP:
		len = माप(काष्ठा mwअगरiex_tdls_stop_cs_params);
		स_नकल(tdls_config->tdls_data, data_buf, len);
		अवरोध;
	हाल ACT_TDLS_CS_PARAMS:
		len = माप(काष्ठा mwअगरiex_tdls_config_cs_params);
		स_नकल(tdls_config->tdls_data, data_buf, len);
		अवरोध;
	शेष:
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Unknown TDLS configuration\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	le16_unaligned_add_cpu(&cmd->size, len);
	वापस 0;
पूर्ण

अटल पूर्णांक
mwअगरiex_cmd_tdls_oper(काष्ठा mwअगरiex_निजी *priv,
		      काष्ठा host_cmd_ds_command *cmd,
		      व्योम *data_buf)
अणु
	काष्ठा host_cmd_ds_tdls_oper *tdls_oper = &cmd->params.tdls_oper;
	काष्ठा mwअगरiex_ds_tdls_oper *oper = data_buf;
	काष्ठा host_cmd_tlv_rates *tlv_rates;
	काष्ठा mwअगरiex_ie_types_htcap *ht_capab;
	काष्ठा mwअगरiex_ie_types_qos_info *wmm_qos_info;
	काष्ठा mwअगरiex_ie_types_extcap *extcap;
	काष्ठा mwअगरiex_ie_types_vhtcap *vht_capab;
	काष्ठा mwअगरiex_ie_types_aid *aid;
	काष्ठा mwअगरiex_ie_types_tdls_idle_समयout *समयout;
	u8 *pos;
	u16 config_len = 0;
	काष्ठा station_parameters *params = priv->sta_params;

	cmd->command = cpu_to_le16(HostCmd_CMD_TDLS_OPER);
	cmd->size = cpu_to_le16(S_DS_GEN);
	le16_unaligned_add_cpu(&cmd->size,
			       माप(काष्ठा host_cmd_ds_tdls_oper));

	tdls_oper->reason = 0;
	स_नकल(tdls_oper->peer_mac, oper->peer_mac, ETH_ALEN);

	pos = (u8 *)tdls_oper + माप(काष्ठा host_cmd_ds_tdls_oper);

	चयन (oper->tdls_action) अणु
	हाल MWIFIEX_TDLS_DISABLE_LINK:
		tdls_oper->tdls_action = cpu_to_le16(ACT_TDLS_DELETE);
		अवरोध;
	हाल MWIFIEX_TDLS_CREATE_LINK:
		tdls_oper->tdls_action = cpu_to_le16(ACT_TDLS_CREATE);
		अवरोध;
	हाल MWIFIEX_TDLS_CONFIG_LINK:
		tdls_oper->tdls_action = cpu_to_le16(ACT_TDLS_CONFIG);

		अगर (!params) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "TDLS config params not available for %pM\n",
				    oper->peer_mac);
			वापस -ENODATA;
		पूर्ण

		put_unaligned_le16(params->capability, pos);
		config_len += माप(params->capability);

		wmm_qos_info = (व्योम *)(pos + config_len);
		wmm_qos_info->header.type = cpu_to_le16(WLAN_EID_QOS_CAPA);
		wmm_qos_info->header.len =
				cpu_to_le16(माप(wmm_qos_info->qos_info));
		wmm_qos_info->qos_info = 0;
		config_len += माप(काष्ठा mwअगरiex_ie_types_qos_info);

		अगर (params->ht_capa) अणु
			ht_capab = (काष्ठा mwअगरiex_ie_types_htcap *)(pos +
								    config_len);
			ht_capab->header.type =
					    cpu_to_le16(WLAN_EID_HT_CAPABILITY);
			ht_capab->header.len =
				   cpu_to_le16(माप(काष्ठा ieee80211_ht_cap));
			स_नकल(&ht_capab->ht_cap, params->ht_capa,
			       माप(काष्ठा ieee80211_ht_cap));
			config_len += माप(काष्ठा mwअगरiex_ie_types_htcap);
		पूर्ण

		अगर (params->supported_rates && params->supported_rates_len) अणु
			tlv_rates = (काष्ठा host_cmd_tlv_rates *)(pos +
								  config_len);
			tlv_rates->header.type =
					       cpu_to_le16(WLAN_EID_SUPP_RATES);
			tlv_rates->header.len =
				       cpu_to_le16(params->supported_rates_len);
			स_नकल(tlv_rates->rates, params->supported_rates,
			       params->supported_rates_len);
			config_len += माप(काष्ठा host_cmd_tlv_rates) +
				      params->supported_rates_len;
		पूर्ण

		अगर (params->ext_capab && params->ext_capab_len) अणु
			extcap = (काष्ठा mwअगरiex_ie_types_extcap *)(pos +
								    config_len);
			extcap->header.type =
					   cpu_to_le16(WLAN_EID_EXT_CAPABILITY);
			extcap->header.len = cpu_to_le16(params->ext_capab_len);
			स_नकल(extcap->ext_capab, params->ext_capab,
			       params->ext_capab_len);
			config_len += माप(काष्ठा mwअगरiex_ie_types_extcap) +
				      params->ext_capab_len;
		पूर्ण
		अगर (params->vht_capa) अणु
			vht_capab = (काष्ठा mwअगरiex_ie_types_vhtcap *)(pos +
								    config_len);
			vht_capab->header.type =
					   cpu_to_le16(WLAN_EID_VHT_CAPABILITY);
			vht_capab->header.len =
				  cpu_to_le16(माप(काष्ठा ieee80211_vht_cap));
			स_नकल(&vht_capab->vht_cap, params->vht_capa,
			       माप(काष्ठा ieee80211_vht_cap));
			config_len += माप(काष्ठा mwअगरiex_ie_types_vhtcap);
		पूर्ण
		अगर (params->aid) अणु
			aid = (काष्ठा mwअगरiex_ie_types_aid *)(pos + config_len);
			aid->header.type = cpu_to_le16(WLAN_EID_AID);
			aid->header.len = cpu_to_le16(माप(params->aid));
			aid->aid = cpu_to_le16(params->aid);
			config_len += माप(काष्ठा mwअगरiex_ie_types_aid);
		पूर्ण

		समयout = (व्योम *)(pos + config_len);
		समयout->header.type = cpu_to_le16(TLV_TYPE_TDLS_IDLE_TIMEOUT);
		समयout->header.len = cpu_to_le16(माप(समयout->value));
		समयout->value = cpu_to_le16(MWIFIEX_TDLS_IDLE_TIMEOUT_IN_SEC);
		config_len += माप(काष्ठा mwअगरiex_ie_types_tdls_idle_समयout);

		अवरोध;
	शेष:
		mwअगरiex_dbg(priv->adapter, ERROR, "Unknown TDLS operation\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	le16_unaligned_add_cpu(&cmd->size, config_len);

	वापस 0;
पूर्ण

/* This function prepares command of sdio rx aggr info. */
अटल पूर्णांक mwअगरiex_cmd_sdio_rx_aggr_cfg(काष्ठा host_cmd_ds_command *cmd,
					u16 cmd_action, व्योम *data_buf)
अणु
	काष्ठा host_cmd_sdio_sp_rx_aggr_cfg *cfg =
					&cmd->params.sdio_rx_aggr_cfg;

	cmd->command = cpu_to_le16(HostCmd_CMD_SDIO_SP_RX_AGGR_CFG);
	cmd->size =
		cpu_to_le16(माप(काष्ठा host_cmd_sdio_sp_rx_aggr_cfg) +
			    S_DS_GEN);
	cfg->action = cmd_action;
	अगर (cmd_action == HostCmd_ACT_GEN_SET)
		cfg->enable = *(u8 *)data_buf;

	वापस 0;
पूर्ण

/* This function prepares command to get HS wakeup reason.
 *
 * Preparation includes -
 *      - Setting command ID, action and proper size
 *      - Ensuring correct endian-ness
 */
अटल पूर्णांक mwअगरiex_cmd_get_wakeup_reason(काष्ठा mwअगरiex_निजी *priv,
					 काष्ठा host_cmd_ds_command *cmd)
अणु
	cmd->command = cpu_to_le16(HostCmd_CMD_HS_WAKEUP_REASON);
	cmd->size = cpu_to_le16(माप(काष्ठा host_cmd_ds_wakeup_reason) +
				S_DS_GEN);

	वापस 0;
पूर्ण

अटल पूर्णांक mwअगरiex_cmd_get_chan_info(काष्ठा host_cmd_ds_command *cmd,
				     u16 cmd_action)
अणु
	काष्ठा host_cmd_ds_sta_configure *sta_cfg_cmd = &cmd->params.sta_cfg;
	काष्ठा host_cmd_tlv_channel_band *tlv_band_channel =
	(काष्ठा host_cmd_tlv_channel_band *)sta_cfg_cmd->tlv_buffer;

	cmd->command = cpu_to_le16(HostCmd_CMD_STA_CONFIGURE);
	cmd->size = cpu_to_le16(माप(*sta_cfg_cmd) +
				माप(*tlv_band_channel) + S_DS_GEN);
	sta_cfg_cmd->action = cpu_to_le16(cmd_action);
	स_रखो(tlv_band_channel, 0, माप(*tlv_band_channel));
	tlv_band_channel->header.type = cpu_to_le16(TLV_TYPE_CHANNELBANDLIST);
	tlv_band_channel->header.len  = cpu_to_le16(माप(*tlv_band_channel) -
					माप(काष्ठा mwअगरiex_ie_types_header));

	वापस 0;
पूर्ण

/* This function check अगर the command is supported by firmware */
अटल पूर्णांक mwअगरiex_is_cmd_supported(काष्ठा mwअगरiex_निजी *priv, u16 cmd_no)
अणु
	अगर (!ISSUPP_ADHOC_ENABLED(priv->adapter->fw_cap_info)) अणु
		चयन (cmd_no) अणु
		हाल HostCmd_CMD_802_11_IBSS_COALESCING_STATUS:
		हाल HostCmd_CMD_802_11_AD_HOC_START:
		हाल HostCmd_CMD_802_11_AD_HOC_JOIN:
		हाल HostCmd_CMD_802_11_AD_HOC_STOP:
			वापस -EOPNOTSUPP;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function prepares the commands beक्रमe sending them to the firmware.
 *
 * This is a generic function which calls specअगरic command preparation
 * routines based upon the command number.
 */
पूर्णांक mwअगरiex_sta_prepare_cmd(काष्ठा mwअगरiex_निजी *priv, uपूर्णांक16_t cmd_no,
			    u16 cmd_action, u32 cmd_oid,
			    व्योम *data_buf, व्योम *cmd_buf)
अणु
	काष्ठा host_cmd_ds_command *cmd_ptr = cmd_buf;
	पूर्णांक ret = 0;

	अगर (mwअगरiex_is_cmd_supported(priv, cmd_no)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "0x%x command not supported by firmware\n",
			    cmd_no);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Prepare command */
	चयन (cmd_no) अणु
	हाल HostCmd_CMD_GET_HW_SPEC:
		ret = mwअगरiex_cmd_get_hw_spec(priv, cmd_ptr);
		अवरोध;
	हाल HostCmd_CMD_CFG_DATA:
		ret = mwअगरiex_cmd_cfg_data(priv, cmd_ptr, data_buf);
		अवरोध;
	हाल HostCmd_CMD_MAC_CONTROL:
		ret = mwअगरiex_cmd_mac_control(priv, cmd_ptr, cmd_action,
					      data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_MAC_ADDRESS:
		ret = mwअगरiex_cmd_802_11_mac_address(priv, cmd_ptr,
						     cmd_action);
		अवरोध;
	हाल HostCmd_CMD_MAC_MULTICAST_ADR:
		ret = mwअगरiex_cmd_mac_multicast_adr(cmd_ptr, cmd_action,
						    data_buf);
		अवरोध;
	हाल HostCmd_CMD_TX_RATE_CFG:
		ret = mwअगरiex_cmd_tx_rate_cfg(priv, cmd_ptr, cmd_action,
					      data_buf);
		अवरोध;
	हाल HostCmd_CMD_TXPWR_CFG:
		ret = mwअगरiex_cmd_tx_घातer_cfg(cmd_ptr, cmd_action,
					       data_buf);
		अवरोध;
	हाल HostCmd_CMD_RF_TX_PWR:
		ret = mwअगरiex_cmd_rf_tx_घातer(priv, cmd_ptr, cmd_action,
					      data_buf);
		अवरोध;
	हाल HostCmd_CMD_RF_ANTENNA:
		ret = mwअगरiex_cmd_rf_antenna(priv, cmd_ptr, cmd_action,
					     data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_PS_MODE_ENH:
		ret = mwअगरiex_cmd_enh_घातer_mode(priv, cmd_ptr, cmd_action,
						 (uपूर्णांक16_t)cmd_oid, data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_HS_CFG_ENH:
		ret = mwअगरiex_cmd_802_11_hs_cfg(priv, cmd_ptr, cmd_action,
				(काष्ठा mwअगरiex_hs_config_param *) data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_SCAN:
		ret = mwअगरiex_cmd_802_11_scan(cmd_ptr, data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_BG_SCAN_CONFIG:
		ret = mwअगरiex_cmd_802_11_bg_scan_config(priv, cmd_ptr,
							data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_BG_SCAN_QUERY:
		ret = mwअगरiex_cmd_802_11_bg_scan_query(cmd_ptr);
		अवरोध;
	हाल HostCmd_CMD_802_11_ASSOCIATE:
		ret = mwअगरiex_cmd_802_11_associate(priv, cmd_ptr, data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_DEAUTHENTICATE:
		ret = mwअगरiex_cmd_802_11_deauthenticate(priv, cmd_ptr,
							data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_AD_HOC_START:
		ret = mwअगरiex_cmd_802_11_ad_hoc_start(priv, cmd_ptr,
						      data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_GET_LOG:
		ret = mwअगरiex_cmd_802_11_get_log(cmd_ptr);
		अवरोध;
	हाल HostCmd_CMD_802_11_AD_HOC_JOIN:
		ret = mwअगरiex_cmd_802_11_ad_hoc_join(priv, cmd_ptr,
						     data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_AD_HOC_STOP:
		ret = mwअगरiex_cmd_802_11_ad_hoc_stop(cmd_ptr);
		अवरोध;
	हाल HostCmd_CMD_RSSI_INFO:
		ret = mwअगरiex_cmd_802_11_rssi_info(priv, cmd_ptr, cmd_action);
		अवरोध;
	हाल HostCmd_CMD_802_11_SNMP_MIB:
		ret = mwअगरiex_cmd_802_11_snmp_mib(priv, cmd_ptr, cmd_action,
						  cmd_oid, data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_TX_RATE_QUERY:
		cmd_ptr->command =
			cpu_to_le16(HostCmd_CMD_802_11_TX_RATE_QUERY);
		cmd_ptr->size =
			cpu_to_le16(माप(काष्ठा host_cmd_ds_tx_rate_query) +
				    S_DS_GEN);
		priv->tx_rate = 0;
		ret = 0;
		अवरोध;
	हाल HostCmd_CMD_VERSION_EXT:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->params.verext.version_str_sel =
			(u8)(get_unaligned((u32 *)data_buf));
		स_नकल(&cmd_ptr->params, data_buf,
		       माप(काष्ठा host_cmd_ds_version_ext));
		cmd_ptr->size =
			cpu_to_le16(माप(काष्ठा host_cmd_ds_version_ext) +
				    S_DS_GEN);
		ret = 0;
		अवरोध;
	हाल HostCmd_CMD_MGMT_FRAME_REG:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->params.reg_mask.action = cpu_to_le16(cmd_action);
		cmd_ptr->params.reg_mask.mask = cpu_to_le32(
						get_unaligned((u32 *)data_buf));
		cmd_ptr->size =
			cpu_to_le16(माप(काष्ठा host_cmd_ds_mgmt_frame_reg) +
				    S_DS_GEN);
		ret = 0;
		अवरोध;
	हाल HostCmd_CMD_REMAIN_ON_CHAN:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		स_नकल(&cmd_ptr->params, data_buf,
		       माप(काष्ठा host_cmd_ds_reमुख्य_on_chan));
		cmd_ptr->size =
		      cpu_to_le16(माप(काष्ठा host_cmd_ds_reमुख्य_on_chan) +
				  S_DS_GEN);
		अवरोध;
	हाल HostCmd_CMD_11AC_CFG:
		ret = mwअगरiex_cmd_11ac_cfg(priv, cmd_ptr, cmd_action, data_buf);
		अवरोध;
	हाल HostCmd_CMD_PACKET_AGGR_CTRL:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->params.pkt_aggr_ctrl.action = cpu_to_le16(cmd_action);
		cmd_ptr->params.pkt_aggr_ctrl.enable =
						cpu_to_le16(*(u16 *)data_buf);
		cmd_ptr->size =
			cpu_to_le16(माप(काष्ठा host_cmd_ds_pkt_aggr_ctrl) +
				    S_DS_GEN);
		अवरोध;
	हाल HostCmd_CMD_P2P_MODE_CFG:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->params.mode_cfg.action = cpu_to_le16(cmd_action);
		cmd_ptr->params.mode_cfg.mode = cpu_to_le16(
						get_unaligned((u16 *)data_buf));
		cmd_ptr->size =
			cpu_to_le16(माप(काष्ठा host_cmd_ds_p2p_mode_cfg) +
				    S_DS_GEN);
		अवरोध;
	हाल HostCmd_CMD_FUNC_INIT:
		अगर (priv->adapter->hw_status == MWIFIEX_HW_STATUS_RESET)
			priv->adapter->hw_status = MWIFIEX_HW_STATUS_READY;
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->size = cpu_to_le16(S_DS_GEN);
		अवरोध;
	हाल HostCmd_CMD_FUNC_SHUTDOWN:
		priv->adapter->hw_status = MWIFIEX_HW_STATUS_RESET;
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->size = cpu_to_le16(S_DS_GEN);
		अवरोध;
	हाल HostCmd_CMD_11N_ADDBA_REQ:
		ret = mwअगरiex_cmd_11n_addba_req(cmd_ptr, data_buf);
		अवरोध;
	हाल HostCmd_CMD_11N_DELBA:
		ret = mwअगरiex_cmd_11n_delba(cmd_ptr, data_buf);
		अवरोध;
	हाल HostCmd_CMD_11N_ADDBA_RSP:
		ret = mwअगरiex_cmd_11n_addba_rsp_gen(priv, cmd_ptr, data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_KEY_MATERIAL:
		ret = mwअगरiex_cmd_802_11_key_material(priv, cmd_ptr,
						      cmd_action, cmd_oid,
						      data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11D_DOMAIN_INFO:
		ret = mwअगरiex_cmd_802_11d_करोमुख्य_info(priv, cmd_ptr,
						      cmd_action);
		अवरोध;
	हाल HostCmd_CMD_RECONFIGURE_TX_BUFF:
		ret = mwअगरiex_cmd_recfg_tx_buf(priv, cmd_ptr, cmd_action,
					       data_buf);
		अवरोध;
	हाल HostCmd_CMD_AMSDU_AGGR_CTRL:
		ret = mwअगरiex_cmd_amsdu_aggr_ctrl(cmd_ptr, cmd_action,
						  data_buf);
		अवरोध;
	हाल HostCmd_CMD_11N_CFG:
		ret = mwअगरiex_cmd_11n_cfg(priv, cmd_ptr, cmd_action, data_buf);
		अवरोध;
	हाल HostCmd_CMD_WMM_GET_STATUS:
		mwअगरiex_dbg(priv->adapter, CMD,
			    "cmd: WMM: WMM_GET_STATUS cmd sent\n");
		cmd_ptr->command = cpu_to_le16(HostCmd_CMD_WMM_GET_STATUS);
		cmd_ptr->size =
			cpu_to_le16(माप(काष्ठा host_cmd_ds_wmm_get_status) +
				    S_DS_GEN);
		ret = 0;
		अवरोध;
	हाल HostCmd_CMD_802_11_IBSS_COALESCING_STATUS:
		ret = mwअगरiex_cmd_ibss_coalescing_status(cmd_ptr, cmd_action,
							 data_buf);
		अवरोध;
	हाल HostCmd_CMD_802_11_SCAN_EXT:
		ret = mwअगरiex_cmd_802_11_scan_ext(priv, cmd_ptr, data_buf);
		अवरोध;
	हाल HostCmd_CMD_MEM_ACCESS:
		ret = mwअगरiex_cmd_mem_access(cmd_ptr, cmd_action, data_buf);
		अवरोध;
	हाल HostCmd_CMD_MAC_REG_ACCESS:
	हाल HostCmd_CMD_BBP_REG_ACCESS:
	हाल HostCmd_CMD_RF_REG_ACCESS:
	हाल HostCmd_CMD_PMIC_REG_ACCESS:
	हाल HostCmd_CMD_CAU_REG_ACCESS:
	हाल HostCmd_CMD_802_11_EEPROM_ACCESS:
		ret = mwअगरiex_cmd_reg_access(cmd_ptr, cmd_action, data_buf);
		अवरोध;
	हाल HostCmd_CMD_SET_BSS_MODE:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		अगर (priv->bss_mode == NL80211_IFTYPE_ADHOC)
			cmd_ptr->params.bss_mode.con_type =
				CONNECTION_TYPE_ADHOC;
		अन्यथा अगर (priv->bss_mode == NL80211_IFTYPE_STATION ||
			 priv->bss_mode == NL80211_IFTYPE_P2P_CLIENT)
			cmd_ptr->params.bss_mode.con_type =
				CONNECTION_TYPE_INFRA;
		अन्यथा अगर (priv->bss_mode == NL80211_IFTYPE_AP ||
			 priv->bss_mode == NL80211_IFTYPE_P2P_GO)
			cmd_ptr->params.bss_mode.con_type = CONNECTION_TYPE_AP;
		cmd_ptr->size = cpu_to_le16(माप(काष्ठा
				host_cmd_ds_set_bss_mode) + S_DS_GEN);
		ret = 0;
		अवरोध;
	हाल HostCmd_CMD_PCIE_DESC_DETAILS:
		ret = mwअगरiex_cmd_pcie_host_spec(priv, cmd_ptr, cmd_action);
		अवरोध;
	हाल HostCmd_CMD_802_11_SUBSCRIBE_EVENT:
		ret = mwअगरiex_cmd_802_11_subsc_evt(priv, cmd_ptr, data_buf);
		अवरोध;
	हाल HostCmd_CMD_MEF_CFG:
		ret = mwअगरiex_cmd_mef_cfg(priv, cmd_ptr, data_buf);
		अवरोध;
	हाल HostCmd_CMD_COALESCE_CFG:
		ret = mwअगरiex_cmd_coalesce_cfg(priv, cmd_ptr, cmd_action,
					       data_buf);
		अवरोध;
	हाल HostCmd_CMD_TDLS_OPER:
		ret = mwअगरiex_cmd_tdls_oper(priv, cmd_ptr, data_buf);
		अवरोध;
	हाल HostCmd_CMD_TDLS_CONFIG:
		ret = mwअगरiex_cmd_tdls_config(priv, cmd_ptr, cmd_action,
					      data_buf);
		अवरोध;
	हाल HostCmd_CMD_CHAN_REPORT_REQUEST:
		ret = mwअगरiex_cmd_issue_chan_report_request(priv, cmd_ptr,
							    data_buf);
		अवरोध;
	हाल HostCmd_CMD_SDIO_SP_RX_AGGR_CFG:
		ret = mwअगरiex_cmd_sdio_rx_aggr_cfg(cmd_ptr, cmd_action,
						   data_buf);
		अवरोध;
	हाल HostCmd_CMD_HS_WAKEUP_REASON:
		ret = mwअगरiex_cmd_get_wakeup_reason(priv, cmd_ptr);
		अवरोध;
	हाल HostCmd_CMD_MC_POLICY:
		ret = mwअगरiex_cmd_set_mc_policy(priv, cmd_ptr, cmd_action,
						data_buf);
		अवरोध;
	हाल HostCmd_CMD_ROBUST_COEX:
		ret = mwअगरiex_cmd_robust_coex(priv, cmd_ptr, cmd_action,
					      data_buf);
		अवरोध;
	हाल HostCmd_CMD_GTK_REKEY_OFFLOAD_CFG:
		ret = mwअगरiex_cmd_gtk_rekey_offload(priv, cmd_ptr, cmd_action,
						    data_buf);
		अवरोध;
	हाल HostCmd_CMD_CHAN_REGION_CFG:
		ret = mwअगरiex_cmd_chan_region_cfg(priv, cmd_ptr, cmd_action);
		अवरोध;
	हाल HostCmd_CMD_FW_DUMP_EVENT:
		cmd_ptr->command = cpu_to_le16(cmd_no);
		cmd_ptr->size = cpu_to_le16(S_DS_GEN);
		अवरोध;
	हाल HostCmd_CMD_STA_CONFIGURE:
		ret = mwअगरiex_cmd_get_chan_info(cmd_ptr, cmd_action);
		अवरोध;
	शेष:
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "PREP_CMD: unknown cmd- %#x\n", cmd_no);
		ret = -1;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * This function issues commands to initialize firmware.
 *
 * This is called after firmware करोwnload to bring the card to
 * working state.
 * Function is also called during reinitialization of भव
 * पूर्णांकerfaces.
 *
 * The following commands are issued sequentially -
 *      - Set PCI-Express host buffer configuration (PCIE only)
 *      - Function init (क्रम first पूर्णांकerface only)
 *      - Read MAC address (क्रम first पूर्णांकerface only)
 *      - Reconfigure Tx buffer size (क्रम first पूर्णांकerface only)
 *      - Enable स्वतः deep sleep (क्रम first पूर्णांकerface only)
 *      - Get Tx rate
 *      - Get Tx घातer
 *      - Set IBSS coalescing status
 *      - Set AMSDU aggregation control
 *      - Set 11d control
 *      - Set MAC control (this must be the last command to initialize firmware)
 */
पूर्णांक mwअगरiex_sta_init_cmd(काष्ठा mwअगरiex_निजी *priv, u8 first_sta, bool init)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक ret;
	काष्ठा mwअगरiex_ds_11n_amsdu_aggr_ctrl amsdu_aggr_ctrl;
	काष्ठा mwअगरiex_ds_स्वतः_ds स्वतः_ds;
	क्रमागत state_11d_t state_11d;
	काष्ठा mwअगरiex_ds_11n_tx_cfg tx_cfg;
	u8 sdio_sp_rx_aggr_enable;
	u16 packet_aggr_enable;
	पूर्णांक data;

	अगर (first_sta) अणु
		अगर (priv->adapter->अगरace_type == MWIFIEX_PCIE) अणु
			ret = mwअगरiex_send_cmd(priv,
					       HostCmd_CMD_PCIE_DESC_DETAILS,
					       HostCmd_ACT_GEN_SET, 0, शून्य,
					       true);
			अगर (ret)
				वापस -1;
		पूर्ण

		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_FUNC_INIT,
				       HostCmd_ACT_GEN_SET, 0, शून्य, true);
		अगर (ret)
			वापस -1;

		/* Download calibration data to firmware.
		 * The cal-data can be पढ़ो from device tree and/or
		 * a configuration file and करोwnloaded to firmware.
		 */
		अगर (adapter->dt_node) अणु
			अगर (of_property_पढ़ो_u32(adapter->dt_node,
						 "marvell,wakeup-pin",
						 &data) == 0) अणु
				pr_debug("Wakeup pin = 0x%x\n", data);
				adapter->hs_cfg.gpio = data;
			पूर्ण

			mwअगरiex_dnld_dt_cfgdata(priv, adapter->dt_node,
						"marvell,caldata");
		पूर्ण

		अगर (adapter->cal_data)
			mwअगरiex_send_cmd(priv, HostCmd_CMD_CFG_DATA,
					 HostCmd_ACT_GEN_SET, 0, शून्य, true);

		/* Read MAC address from HW */
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_GET_HW_SPEC,
				       HostCmd_ACT_GEN_GET, 0, शून्य, true);
		अगर (ret)
			वापस -1;

		/** Set SDIO Single Port RX Aggr Info */
		अगर (priv->adapter->अगरace_type == MWIFIEX_SDIO &&
		    ISSUPP_SDIO_SPA_ENABLED(priv->adapter->fw_cap_info) &&
		    !priv->adapter->host_disable_sdio_rx_aggr) अणु
			sdio_sp_rx_aggr_enable = true;
			ret = mwअगरiex_send_cmd(priv,
					       HostCmd_CMD_SDIO_SP_RX_AGGR_CFG,
					       HostCmd_ACT_GEN_SET, 0,
					       &sdio_sp_rx_aggr_enable,
					       true);
			अगर (ret) अणु
				mwअगरiex_dbg(priv->adapter, ERROR,
					    "error while enabling SP aggregation..disable it");
				adapter->sdio_rx_aggr_enable = false;
			पूर्ण
		पूर्ण

		/* Reconfigure tx buf size */
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_RECONFIGURE_TX_BUFF,
				       HostCmd_ACT_GEN_SET, 0,
				       &priv->adapter->tx_buf_size, true);
		अगर (ret)
			वापस -1;

		अगर (priv->bss_type != MWIFIEX_BSS_TYPE_UAP) अणु
			/* Enable IEEE PS by शेष */
			priv->adapter->ps_mode = MWIFIEX_802_11_POWER_MODE_PSP;
			ret = mwअगरiex_send_cmd(priv,
					       HostCmd_CMD_802_11_PS_MODE_ENH,
					       EN_AUTO_PS, BITMAP_STA_PS, शून्य,
					       true);
			अगर (ret)
				वापस -1;
		पूर्ण

		अगर (drcs) अणु
			adapter->drcs_enabled = true;
			अगर (ISSUPP_DRCS_ENABLED(adapter->fw_cap_info))
				ret = mwअगरiex_send_cmd(priv,
						       HostCmd_CMD_MC_POLICY,
						       HostCmd_ACT_GEN_SET, 0,
						       &adapter->drcs_enabled,
						       true);
			अगर (ret)
				वापस -1;
		पूर्ण

		mwअगरiex_send_cmd(priv, HostCmd_CMD_CHAN_REGION_CFG,
				 HostCmd_ACT_GEN_GET, 0, शून्य, true);
	पूर्ण

	/* get tx rate */
	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_TX_RATE_CFG,
			       HostCmd_ACT_GEN_GET, 0, शून्य, true);
	अगर (ret)
		वापस -1;
	priv->data_rate = 0;

	/* get tx घातer */
	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_RF_TX_PWR,
			       HostCmd_ACT_GEN_GET, 0, शून्य, true);
	अगर (ret)
		वापस -1;

	स_रखो(&amsdu_aggr_ctrl, 0, माप(amsdu_aggr_ctrl));
	amsdu_aggr_ctrl.enable = true;
	/* Send request to firmware */
	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_AMSDU_AGGR_CTRL,
			       HostCmd_ACT_GEN_SET, 0,
			       &amsdu_aggr_ctrl, true);
	अगर (ret)
		वापस -1;
	/* MAC Control must be the last command in init_fw */
	/* set MAC Control */
	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_MAC_CONTROL,
			       HostCmd_ACT_GEN_SET, 0,
			       &priv->curr_pkt_filter, true);
	अगर (ret)
		वापस -1;

	अगर (!disable_स्वतः_ds && first_sta &&
	    priv->bss_type != MWIFIEX_BSS_TYPE_UAP) अणु
		/* Enable स्वतः deep sleep */
		स्वतः_ds.स्वतः_ds = DEEP_SLEEP_ON;
		स्वतः_ds.idle_समय = DEEP_SLEEP_IDLE_TIME;
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_PS_MODE_ENH,
				       EN_AUTO_PS, BITMAP_AUTO_DS,
				       &स्वतः_ds, true);
		अगर (ret)
			वापस -1;
	पूर्ण

	अगर (priv->bss_type != MWIFIEX_BSS_TYPE_UAP) अणु
		/* Send cmd to FW to enable/disable 11D function */
		state_11d = ENABLE_11D;
		ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_802_11_SNMP_MIB,
				       HostCmd_ACT_GEN_SET, DOT11D_I,
				       &state_11d, true);
		अगर (ret)
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "11D: failed to enable 11D\n");
	पूर्ण

	/* Pacekt aggregation handshake with firmware */
	अगर (aggr_ctrl) अणु
		packet_aggr_enable = true;
		mwअगरiex_send_cmd(priv, HostCmd_CMD_PACKET_AGGR_CTRL,
				 HostCmd_ACT_GEN_SET, 0,
				 &packet_aggr_enable, true);
	पूर्ण

	/* Send cmd to FW to configure 11n specअगरic configuration
	 * (Short GI, Channel BW, Green field support etc.) क्रम transmit
	 */
	tx_cfg.tx_htcap = MWIFIEX_FW_DEF_HTTXCFG;
	ret = mwअगरiex_send_cmd(priv, HostCmd_CMD_11N_CFG,
			       HostCmd_ACT_GEN_SET, 0, &tx_cfg, true);

	अगर (init) अणु
		/* set last_init_cmd beक्रमe sending the command */
		priv->adapter->last_init_cmd = HostCmd_CMD_11N_CFG;
		ret = -EINPROGRESS;
	पूर्ण

	वापस ret;
पूर्ण
