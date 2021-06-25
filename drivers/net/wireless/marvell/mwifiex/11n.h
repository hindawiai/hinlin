<शैली गुरु>
/*
 * NXP Wireless LAN device driver: 802.11n
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

#अगर_अघोषित _MWIFIEX_11N_H_
#घोषणा _MWIFIEX_11N_H_

#समावेश "11n_aggr.h"
#समावेश "11n_rxreorder.h"
#समावेश "wmm.h"

पूर्णांक mwअगरiex_ret_11n_delba(काष्ठा mwअगरiex_निजी *priv,
			  काष्ठा host_cmd_ds_command *resp);
पूर्णांक mwअगरiex_ret_11n_addba_req(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा host_cmd_ds_command *resp);
पूर्णांक mwअगरiex_cmd_11n_cfg(काष्ठा mwअगरiex_निजी *priv,
			काष्ठा host_cmd_ds_command *cmd, u16 cmd_action,
			काष्ठा mwअगरiex_ds_11n_tx_cfg *txcfg);
पूर्णांक mwअगरiex_cmd_append_11n_tlv(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा mwअगरiex_bssdescriptor *bss_desc,
			       u8 **buffer);
पूर्णांक mwअगरiex_fill_cap_info(काष्ठा mwअगरiex_निजी *, u8 radio_type,
			  काष्ठा ieee80211_ht_cap *);
पूर्णांक mwअगरiex_set_get_11n_htcap_cfg(काष्ठा mwअगरiex_निजी *priv,
				  u16 action, पूर्णांक *htcap_cfg);
व्योम mwअगरiex_11n_delete_tx_ba_stream_tbl_entry(काष्ठा mwअगरiex_निजी *priv,
					     काष्ठा mwअगरiex_tx_ba_stream_tbl
					     *tx_tbl);
व्योम mwअगरiex_11n_delete_all_tx_ba_stream_tbl(काष्ठा mwअगरiex_निजी *priv);
काष्ठा mwअगरiex_tx_ba_stream_tbl *mwअगरiex_get_ba_tbl(काष्ठा
							     mwअगरiex_निजी
							     *priv, पूर्णांक tid,
							     u8 *ra);
व्योम mwअगरiex_create_ba_tbl(काष्ठा mwअगरiex_निजी *priv, u8 *ra, पूर्णांक tid,
			   क्रमागत mwअगरiex_ba_status ba_status);
पूर्णांक mwअगरiex_send_addba(काष्ठा mwअगरiex_निजी *priv, पूर्णांक tid, u8 *peer_mac);
पूर्णांक mwअगरiex_send_delba(काष्ठा mwअगरiex_निजी *priv, पूर्णांक tid, u8 *peer_mac,
		       पूर्णांक initiator);
व्योम mwअगरiex_11n_delete_ba_stream(काष्ठा mwअगरiex_निजी *priv, u8 *del_ba);
पूर्णांक mwअगरiex_get_rx_reorder_tbl(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा mwअगरiex_ds_rx_reorder_tbl *buf);
पूर्णांक mwअगरiex_get_tx_ba_stream_tbl(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा mwअगरiex_ds_tx_ba_stream_tbl *buf);
पूर्णांक mwअगरiex_cmd_recfg_tx_buf(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा host_cmd_ds_command *cmd,
			     पूर्णांक cmd_action, u16 *buf_size);
पूर्णांक mwअगरiex_cmd_amsdu_aggr_ctrl(काष्ठा host_cmd_ds_command *cmd,
				पूर्णांक cmd_action,
				काष्ठा mwअगरiex_ds_11n_amsdu_aggr_ctrl *aa_ctrl);
व्योम mwअगरiex_del_tx_ba_stream_tbl_by_ra(काष्ठा mwअगरiex_निजी *priv, u8 *ra);
u8 mwअगरiex_get_sec_chan_offset(पूर्णांक chan);

अटल अंतरभूत u8
mwअगरiex_is_station_ampdu_allowed(काष्ठा mwअगरiex_निजी *priv,
				 काष्ठा mwअगरiex_ra_list_tbl *ptr, पूर्णांक tid)
अणु
	काष्ठा mwअगरiex_sta_node *node = mwअगरiex_get_sta_entry(priv, ptr->ra);

	अगर (unlikely(!node))
		वापस false;

	वापस (node->ampdu_sta[tid] != BA_STREAM_NOT_ALLOWED) ? true : false;
पूर्ण

/* This function checks whether AMPDU is allowed or not क्रम a particular TID. */
अटल अंतरभूत u8
mwअगरiex_is_ampdu_allowed(काष्ठा mwअगरiex_निजी *priv,
			 काष्ठा mwअगरiex_ra_list_tbl *ptr, पूर्णांक tid)
अणु
	अगर (is_broadcast_ether_addr(ptr->ra))
		वापस false;
	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) अणु
		वापस mwअगरiex_is_station_ampdu_allowed(priv, ptr, tid);
	पूर्ण अन्यथा अणु
		अगर (ptr->tdls_link)
			वापस mwअगरiex_is_station_ampdu_allowed(priv, ptr, tid);

		वापस (priv->aggr_prio_tbl[tid].ampdu_ap !=
			BA_STREAM_NOT_ALLOWED) ? true : false;
	पूर्ण
पूर्ण

/*
 * This function checks whether AMSDU is allowed or not क्रम a particular TID.
 */
अटल अंतरभूत u8
mwअगरiex_is_amsdu_allowed(काष्ठा mwअगरiex_निजी *priv, पूर्णांक tid)
अणु
	वापस (((priv->aggr_prio_tbl[tid].amsdu != BA_STREAM_NOT_ALLOWED) &&
		 (priv->is_data_rate_स्वतः || !(priv->biपंचांगap_rates[2] & 0x03)))
		? true : false);
पूर्ण

/*
 * This function checks whether a space is available क्रम new BA stream or not.
 */
अटल अंतरभूत u8 mwअगरiex_space_avail_क्रम_new_ba_stream(
					काष्ठा mwअगरiex_adapter *adapter)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	u8 i;
	u32 ba_stream_num = 0, ba_stream_max;

	ba_stream_max = MWIFIEX_MAX_TX_BASTREAM_SUPPORTED;

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		priv = adapter->priv[i];
		अगर (priv)
			ba_stream_num += mwअगरiex_wmm_list_len(
				&priv->tx_ba_stream_tbl_ptr);
	पूर्ण

	अगर (adapter->fw_api_ver == MWIFIEX_FW_V15) अणु
		ba_stream_max =
			       GETSUPP_TXBASTREAMS(adapter->hw_करोt_11n_dev_cap);
		अगर (!ba_stream_max)
			ba_stream_max = MWIFIEX_MAX_TX_BASTREAM_SUPPORTED;
	पूर्ण

	वापस ((ba_stream_num < ba_stream_max) ? true : false);
पूर्ण

/*
 * This function finds the correct Tx BA stream to delete.
 *
 * Upon successfully locating, both the TID and the RA are वापसed.
 */
अटल अंतरभूत u8
mwअगरiex_find_stream_to_delete(काष्ठा mwअगरiex_निजी *priv, पूर्णांक ptr_tid,
			      पूर्णांक *ptid, u8 *ra)
अणु
	पूर्णांक tid;
	u8 ret = false;
	काष्ठा mwअगरiex_tx_ba_stream_tbl *tx_tbl;

	tid = priv->aggr_prio_tbl[ptr_tid].ampdu_user;

	spin_lock_bh(&priv->tx_ba_stream_tbl_lock);
	list_क्रम_each_entry(tx_tbl, &priv->tx_ba_stream_tbl_ptr, list) अणु
		अगर (tid > priv->aggr_prio_tbl[tx_tbl->tid].ampdu_user) अणु
			tid = priv->aggr_prio_tbl[tx_tbl->tid].ampdu_user;
			*ptid = tx_tbl->tid;
			स_नकल(ra, tx_tbl->ra, ETH_ALEN);
			ret = true;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->tx_ba_stream_tbl_lock);

	वापस ret;
पूर्ण

/*
 * This function checks whether associated station is 11n enabled
 */
अटल अंतरभूत पूर्णांक mwअगरiex_is_sta_11n_enabled(काष्ठा mwअगरiex_निजी *priv,
					     काष्ठा mwअगरiex_sta_node *node)
अणु
	अगर (!node || ((priv->bss_role == MWIFIEX_BSS_ROLE_UAP) &&
		      !priv->ap_11n_enabled) ||
	    ((priv->bss_mode == NL80211_IFTYPE_ADHOC) &&
	     !priv->adapter->adhoc_11n_enabled))
		वापस 0;

	वापस node->is_11n_enabled;
पूर्ण

अटल अंतरभूत u8
mwअगरiex_tdls_peer_11n_enabled(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *ra)
अणु
	काष्ठा mwअगरiex_sta_node *node = mwअगरiex_get_sta_entry(priv, ra);
	अगर (node)
		वापस node->is_11n_enabled;

	वापस false;
पूर्ण
#पूर्ण_अगर /* !_MWIFIEX_11N_H_ */
