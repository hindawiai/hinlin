<शैली गुरु>
/*
 * NXP Wireless LAN device driver: 802.11n RX Re-ordering
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

#अगर_अघोषित _MWIFIEX_11N_RXREORDER_H_
#घोषणा _MWIFIEX_11N_RXREORDER_H_

#घोषणा MIN_FLUSH_TIMER_MS		50
#घोषणा MIN_FLUSH_TIMER_15_MS		15
#घोषणा MWIFIEX_BA_WIN_SIZE_32		32

#घोषणा PKT_TYPE_BAR 0xE7
#घोषणा MAX_TID_VALUE			(2 << 11)
#घोषणा TWOPOW11			(2 << 10)

#घोषणा BLOCKACKPARAM_TID_POS		2
#घोषणा BLOCKACKPARAM_AMSDU_SUPP_MASK	0x1
#घोषणा BLOCKACKPARAM_WINSIZE_POS	6
#घोषणा DELBA_TID_POS			12
#घोषणा DELBA_INITIATOR_POS		11
#घोषणा TYPE_DELBA_SENT			1
#घोषणा TYPE_DELBA_RECEIVE		2
#घोषणा IMMEDIATE_BLOCK_ACK		0x2

#घोषणा ADDBA_RSP_STATUS_ACCEPT 0

#घोषणा MWIFIEX_DEF_11N_RX_SEQ_NUM	0xffff
#घोषणा BA_SETUP_MAX_PACKET_THRESHOLD	16
#घोषणा BA_SETUP_PACKET_OFFSET		16

क्रमागत mwअगरiex_rxreor_flags अणु
	RXREOR_FORCE_NO_DROP		= 1<<0,
	RXREOR_INIT_WINDOW_SHIFT	= 1<<1,
पूर्ण;

अटल अंतरभूत व्योम mwअगरiex_reset_11n_rx_seq_num(काष्ठा mwअगरiex_निजी *priv)
अणु
	स_रखो(priv->rx_seq, 0xff, माप(priv->rx_seq));
पूर्ण

पूर्णांक mwअगरiex_11n_rx_reorder_pkt(काष्ठा mwअगरiex_निजी *,
			       u16 seqNum,
			       u16 tid, u8 *ta,
			       u8 pkttype, व्योम *payload);
व्योम mwअगरiex_del_ba_tbl(काष्ठा mwअगरiex_निजी *priv, पूर्णांक Tid,
			u8 *PeerMACAddr, u8 type, पूर्णांक initiator);
व्योम mwअगरiex_11n_ba_stream_समयout(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा host_cmd_ds_11n_baसमयout *event);
पूर्णांक mwअगरiex_ret_11n_addba_resp(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा host_cmd_ds_command
			       *resp);
पूर्णांक mwअगरiex_cmd_11n_delba(काष्ठा host_cmd_ds_command *cmd,
			  व्योम *data_buf);
पूर्णांक mwअगरiex_cmd_11n_addba_rsp_gen(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा host_cmd_ds_command *cmd,
				  काष्ठा host_cmd_ds_11n_addba_req
				  *cmd_addba_req);
पूर्णांक mwअगरiex_cmd_11n_addba_req(काष्ठा host_cmd_ds_command *cmd,
			      व्योम *data_buf);
व्योम mwअगरiex_11n_cleanup_reorder_tbl(काष्ठा mwअगरiex_निजी *priv);
काष्ठा mwअगरiex_rx_reorder_tbl *mwअगरiex_11n_get_rxreorder_tbl(काष्ठा
							   mwअगरiex_निजी
							   *priv, पूर्णांक tid,
							   u8 *ta);
काष्ठा mwअगरiex_rx_reorder_tbl *
mwअगरiex_11n_get_rx_reorder_tbl(काष्ठा mwअगरiex_निजी *priv, पूर्णांक tid, u8 *ta);
व्योम mwअगरiex_11n_del_rx_reorder_tbl_by_ta(काष्ठा mwअगरiex_निजी *priv, u8 *ta);
व्योम mwअगरiex_update_rxreor_flags(काष्ठा mwअगरiex_adapter *adapter, u8 flags);
व्योम mwअगरiex_11n_rxba_sync_event(काष्ठा mwअगरiex_निजी *priv,
				 u8 *event_buf, u16 len);
#पूर्ण_अगर /* _MWIFIEX_11N_RXREORDER_H_ */
