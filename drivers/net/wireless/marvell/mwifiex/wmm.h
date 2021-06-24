<शैली गुरु>
/*
 * NXP Wireless LAN device driver: WMM
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

#अगर_अघोषित _MWIFIEX_WMM_H_
#घोषणा _MWIFIEX_WMM_H_

क्रमागत ieee_types_wmm_aciaअगरsn_biपंचांगasks अणु
	MWIFIEX_AIFSN = (BIT(0) | BIT(1) | BIT(2) | BIT(3)),
	MWIFIEX_ACM = BIT(4),
	MWIFIEX_ACI = (BIT(5) | BIT(6)),
पूर्ण;

क्रमागत ieee_types_wmm_ecw_biपंचांगasks अणु
	MWIFIEX_ECW_MIN = (BIT(0) | BIT(1) | BIT(2) | BIT(3)),
	MWIFIEX_ECW_MAX = (BIT(4) | BIT(5) | BIT(6) | BIT(7)),
पूर्ण;

बाह्य स्थिर u16 mwअगरiex_1d_to_wmm_queue[];
बाह्य स्थिर u8 tos_to_tid_inv[];

/*
 * This function retrieves the TID of the given RA list.
 */
अटल अंतरभूत पूर्णांक
mwअगरiex_get_tid(काष्ठा mwअगरiex_ra_list_tbl *ptr)
अणु
	काष्ठा sk_buff *skb;

	अगर (skb_queue_empty(&ptr->skb_head))
		वापस 0;

	skb = skb_peek(&ptr->skb_head);

	वापस skb->priority;
पूर्ण

/*
 * This function माला_लो the length of a list.
 */
अटल अंतरभूत पूर्णांक
mwअगरiex_wmm_list_len(काष्ठा list_head *head)
अणु
	काष्ठा list_head *pos;
	पूर्णांक count = 0;

	list_क्रम_each(pos, head)
		++count;

	वापस count;
पूर्ण

/*
 * This function checks अगर a RA list is empty or not.
 */
अटल अंतरभूत u8
mwअगरiex_wmm_is_ra_list_empty(काष्ठा list_head *ra_list_hhead)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;
	पूर्णांक is_list_empty;

	list_क्रम_each_entry(ra_list, ra_list_hhead, list) अणु
		is_list_empty = skb_queue_empty(&ra_list->skb_head);
		अगर (!is_list_empty)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम mwअगरiex_wmm_add_buf_txqueue(काष्ठा mwअगरiex_निजी *priv,
				 काष्ठा sk_buff *skb);
व्योम mwअगरiex_wmm_add_buf_bypass_txqueue(काष्ठा mwअगरiex_निजी *priv,
					काष्ठा sk_buff *skb);
व्योम mwअगरiex_ralist_add(काष्ठा mwअगरiex_निजी *priv, स्थिर u8 *ra);
व्योम mwअगरiex_rotate_priolists(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा mwअगरiex_ra_list_tbl *ra, पूर्णांक tid);

पूर्णांक mwअगरiex_wmm_lists_empty(काष्ठा mwअगरiex_adapter *adapter);
पूर्णांक mwअगरiex_bypass_txlist_empty(काष्ठा mwअगरiex_adapter *adapter);
व्योम mwअगरiex_wmm_process_tx(काष्ठा mwअगरiex_adapter *adapter);
व्योम mwअगरiex_process_bypass_tx(काष्ठा mwअगरiex_adapter *adapter);
पूर्णांक mwअगरiex_is_ralist_valid(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा mwअगरiex_ra_list_tbl *ra_list, पूर्णांक tid);

u8 mwअगरiex_wmm_compute_drv_pkt_delay(काष्ठा mwअगरiex_निजी *priv,
				     स्थिर काष्ठा sk_buff *skb);
व्योम mwअगरiex_wmm_init(काष्ठा mwअगरiex_adapter *adapter);

u32 mwअगरiex_wmm_process_association_req(काष्ठा mwअगरiex_निजी *priv,
					u8 **assoc_buf,
					काष्ठा ieee_types_wmm_parameter *wmmie,
					काष्ठा ieee80211_ht_cap *htcap);

व्योम mwअगरiex_wmm_setup_queue_priorities(काष्ठा mwअगरiex_निजी *priv,
					काष्ठा ieee_types_wmm_parameter *wmm_ie);
व्योम mwअगरiex_wmm_setup_ac_करोwngrade(काष्ठा mwअगरiex_निजी *priv);
पूर्णांक mwअगरiex_ret_wmm_get_status(काष्ठा mwअगरiex_निजी *priv,
			       स्थिर काष्ठा host_cmd_ds_command *resp);
काष्ठा mwअगरiex_ra_list_tbl *
mwअगरiex_wmm_get_queue_raptr(काष्ठा mwअगरiex_निजी *priv, u8 tid,
			    स्थिर u8 *ra_addr);
u8 mwअगरiex_wmm_करोwngrade_tid(काष्ठा mwअगरiex_निजी *priv, u32 tid);
व्योम mwअगरiex_update_ralist_tx_छोड़ो(काष्ठा mwअगरiex_निजी *priv, u8 *mac,
				    u8 tx_छोड़ो);
व्योम mwअगरiex_update_ralist_tx_छोड़ो_in_tdls_cs(काष्ठा mwअगरiex_निजी *priv,
					       u8 *mac, u8 tx_छोड़ो);

काष्ठा mwअगरiex_ra_list_tbl *mwअगरiex_wmm_get_ralist_node(काष्ठा mwअगरiex_निजी
					*priv, u8 tid, स्थिर u8 *ra_addr);
#पूर्ण_अगर /* !_MWIFIEX_WMM_H_ */
