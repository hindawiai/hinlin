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

#समावेश "decl.h"
#समावेश "ioctl.h"
#समावेश "util.h"
#समावेश "fw.h"
#समावेश "main.h"
#समावेश "wmm.h"
#समावेश "11n.h"
#समावेश "11n_rxreorder.h"

/* This function will dispatch amsdu packet and क्रमward it to kernel/upper
 * layer.
 */
अटल पूर्णांक mwअगरiex_11n_dispatch_amsdu_pkt(काष्ठा mwअगरiex_निजी *priv,
					  काष्ठा sk_buff *skb)
अणु
	काष्ठा rxpd *local_rx_pd = (काष्ठा rxpd *)(skb->data);
	पूर्णांक ret;

	अगर (le16_to_cpu(local_rx_pd->rx_pkt_type) == PKT_TYPE_AMSDU) अणु
		काष्ठा sk_buff_head list;
		काष्ठा sk_buff *rx_skb;

		__skb_queue_head_init(&list);

		skb_pull(skb, le16_to_cpu(local_rx_pd->rx_pkt_offset));
		skb_trim(skb, le16_to_cpu(local_rx_pd->rx_pkt_length));

		ieee80211_amsdu_to_8023s(skb, &list, priv->curr_addr,
					 priv->wdev.अगरtype, 0, शून्य, शून्य);

		जबतक (!skb_queue_empty(&list)) अणु
			काष्ठा rx_packet_hdr *rx_hdr;

			rx_skb = __skb_dequeue(&list);
			rx_hdr = (काष्ठा rx_packet_hdr *)rx_skb->data;
			अगर (ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
			    ntohs(rx_hdr->eth803_hdr.h_proto) == ETH_P_TDLS) अणु
				mwअगरiex_process_tdls_action_frame(priv,
								  (u8 *)rx_hdr,
								  skb->len);
			पूर्ण

			अगर (priv->bss_role == MWIFIEX_BSS_ROLE_UAP)
				ret = mwअगरiex_uap_recv_packet(priv, rx_skb);
			अन्यथा
				ret = mwअगरiex_recv_packet(priv, rx_skb);
			अगर (ret == -1)
				mwअगरiex_dbg(priv->adapter, ERROR,
					    "Rx of A-MSDU failed");
		पूर्ण
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

/* This function will process the rx packet and क्रमward it to kernel/upper
 * layer.
 */
अटल पूर्णांक mwअगरiex_11n_dispatch_pkt(काष्ठा mwअगरiex_निजी *priv,
				    काष्ठा sk_buff *payload)
अणु

	पूर्णांक ret;

	अगर (!payload) अणु
		mwअगरiex_dbg(priv->adapter, INFO, "info: fw drop data\n");
		वापस 0;
	पूर्ण

	ret = mwअगरiex_11n_dispatch_amsdu_pkt(priv, payload);
	अगर (!ret)
		वापस 0;

	अगर (priv->bss_role == MWIFIEX_BSS_ROLE_UAP)
		वापस mwअगरiex_handle_uap_rx_क्रमward(priv, payload);

	वापस mwअगरiex_process_rx_packet(priv, payload);
पूर्ण

/*
 * This function dispatches all packets in the Rx reorder table until the
 * start winकरोw.
 *
 * There could be holes in the buffer, which are skipped by the function.
 * Since the buffer is linear, the function uses rotation to simulate
 * circular buffer.
 */
अटल व्योम
mwअगरiex_11n_dispatch_pkt_until_start_win(काष्ठा mwअगरiex_निजी *priv,
					 काष्ठा mwअगरiex_rx_reorder_tbl *tbl,
					 पूर्णांक start_win)
अणु
	काष्ठा sk_buff_head list;
	काष्ठा sk_buff *skb;
	पूर्णांक pkt_to_send, i;

	__skb_queue_head_init(&list);
	spin_lock_bh(&priv->rx_reorder_tbl_lock);

	pkt_to_send = (start_win > tbl->start_win) ?
		      min((start_win - tbl->start_win), tbl->win_size) :
		      tbl->win_size;

	क्रम (i = 0; i < pkt_to_send; ++i) अणु
		अगर (tbl->rx_reorder_ptr[i]) अणु
			skb = tbl->rx_reorder_ptr[i];
			__skb_queue_tail(&list, skb);
			tbl->rx_reorder_ptr[i] = शून्य;
		पूर्ण
	पूर्ण

	/*
	 * We करोn't have a circular buffer, hence use rotation to simulate
	 * circular buffer
	 */
	क्रम (i = 0; i < tbl->win_size - pkt_to_send; ++i) अणु
		tbl->rx_reorder_ptr[i] = tbl->rx_reorder_ptr[pkt_to_send + i];
		tbl->rx_reorder_ptr[pkt_to_send + i] = शून्य;
	पूर्ण

	tbl->start_win = start_win;
	spin_unlock_bh(&priv->rx_reorder_tbl_lock);

	जबतक ((skb = __skb_dequeue(&list)))
		mwअगरiex_11n_dispatch_pkt(priv, skb);
पूर्ण

/*
 * This function dispatches all packets in the Rx reorder table until
 * a hole is found.
 *
 * The start winकरोw is adjusted स्वतःmatically when a hole is located.
 * Since the buffer is linear, the function uses rotation to simulate
 * circular buffer.
 */
अटल व्योम
mwअगरiex_11n_scan_and_dispatch(काष्ठा mwअगरiex_निजी *priv,
			      काष्ठा mwअगरiex_rx_reorder_tbl *tbl)
अणु
	काष्ठा sk_buff_head list;
	काष्ठा sk_buff *skb;
	पूर्णांक i, j, xchg;

	__skb_queue_head_init(&list);
	spin_lock_bh(&priv->rx_reorder_tbl_lock);

	क्रम (i = 0; i < tbl->win_size; ++i) अणु
		अगर (!tbl->rx_reorder_ptr[i])
			अवरोध;
		skb = tbl->rx_reorder_ptr[i];
		__skb_queue_tail(&list, skb);
		tbl->rx_reorder_ptr[i] = शून्य;
	पूर्ण

	/*
	 * We करोn't have a circular buffer, hence use rotation to simulate
	 * circular buffer
	 */
	अगर (i > 0) अणु
		xchg = tbl->win_size - i;
		क्रम (j = 0; j < xchg; ++j) अणु
			tbl->rx_reorder_ptr[j] = tbl->rx_reorder_ptr[i + j];
			tbl->rx_reorder_ptr[i + j] = शून्य;
		पूर्ण
	पूर्ण
	tbl->start_win = (tbl->start_win + i) & (MAX_TID_VALUE - 1);

	spin_unlock_bh(&priv->rx_reorder_tbl_lock);

	जबतक ((skb = __skb_dequeue(&list)))
		mwअगरiex_11n_dispatch_pkt(priv, skb);
पूर्ण

/*
 * This function deletes the Rx reorder table and मुक्तs the memory.
 *
 * The function stops the associated समयr and dispatches all the
 * pending packets in the Rx reorder table beक्रमe deletion.
 */
अटल व्योम
mwअगरiex_del_rx_reorder_entry(काष्ठा mwअगरiex_निजी *priv,
			     काष्ठा mwअगरiex_rx_reorder_tbl *tbl)
अणु
	पूर्णांक start_win;

	अगर (!tbl)
		वापस;

	spin_lock_bh(&priv->adapter->rx_proc_lock);
	priv->adapter->rx_locked = true;
	अगर (priv->adapter->rx_processing) अणु
		spin_unlock_bh(&priv->adapter->rx_proc_lock);
		flush_workqueue(priv->adapter->rx_workqueue);
	पूर्ण अन्यथा अणु
		spin_unlock_bh(&priv->adapter->rx_proc_lock);
	पूर्ण

	start_win = (tbl->start_win + tbl->win_size) & (MAX_TID_VALUE - 1);
	mwअगरiex_11n_dispatch_pkt_until_start_win(priv, tbl, start_win);

	del_समयr_sync(&tbl->समयr_context.समयr);
	tbl->समयr_context.समयr_is_set = false;

	spin_lock_bh(&priv->rx_reorder_tbl_lock);
	list_del(&tbl->list);
	spin_unlock_bh(&priv->rx_reorder_tbl_lock);

	kमुक्त(tbl->rx_reorder_ptr);
	kमुक्त(tbl);

	spin_lock_bh(&priv->adapter->rx_proc_lock);
	priv->adapter->rx_locked = false;
	spin_unlock_bh(&priv->adapter->rx_proc_lock);

पूर्ण

/*
 * This function वापसs the poपूर्णांकer to an entry in Rx reordering
 * table which matches the given TA/TID pair.
 */
काष्ठा mwअगरiex_rx_reorder_tbl *
mwअगरiex_11n_get_rx_reorder_tbl(काष्ठा mwअगरiex_निजी *priv, पूर्णांक tid, u8 *ta)
अणु
	काष्ठा mwअगरiex_rx_reorder_tbl *tbl;

	spin_lock_bh(&priv->rx_reorder_tbl_lock);
	list_क्रम_each_entry(tbl, &priv->rx_reorder_tbl_ptr, list) अणु
		अगर (!स_भेद(tbl->ta, ta, ETH_ALEN) && tbl->tid == tid) अणु
			spin_unlock_bh(&priv->rx_reorder_tbl_lock);
			वापस tbl;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->rx_reorder_tbl_lock);

	वापस शून्य;
पूर्ण

/* This function retrieves the poपूर्णांकer to an entry in Rx reordering
 * table which matches the given TA and deletes it.
 */
व्योम mwअगरiex_11n_del_rx_reorder_tbl_by_ta(काष्ठा mwअगरiex_निजी *priv, u8 *ta)
अणु
	काष्ठा mwअगरiex_rx_reorder_tbl *tbl, *पंचांगp;

	अगर (!ta)
		वापस;

	spin_lock_bh(&priv->rx_reorder_tbl_lock);
	list_क्रम_each_entry_safe(tbl, पंचांगp, &priv->rx_reorder_tbl_ptr, list) अणु
		अगर (!स_भेद(tbl->ta, ta, ETH_ALEN)) अणु
			spin_unlock_bh(&priv->rx_reorder_tbl_lock);
			mwअगरiex_del_rx_reorder_entry(priv, tbl);
			spin_lock_bh(&priv->rx_reorder_tbl_lock);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->rx_reorder_tbl_lock);

	वापस;
पूर्ण

/*
 * This function finds the last sequence number used in the packets
 * buffered in Rx reordering table.
 */
अटल पूर्णांक
mwअगरiex_11n_find_last_seq_num(काष्ठा reorder_पंचांगr_cnxt *ctx)
अणु
	काष्ठा mwअगरiex_rx_reorder_tbl *rx_reorder_tbl_ptr = ctx->ptr;
	काष्ठा mwअगरiex_निजी *priv = ctx->priv;
	पूर्णांक i;

	spin_lock_bh(&priv->rx_reorder_tbl_lock);
	क्रम (i = rx_reorder_tbl_ptr->win_size - 1; i >= 0; --i) अणु
		अगर (rx_reorder_tbl_ptr->rx_reorder_ptr[i]) अणु
			spin_unlock_bh(&priv->rx_reorder_tbl_lock);
			वापस i;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&priv->rx_reorder_tbl_lock);

	वापस -1;
पूर्ण

/*
 * This function flushes all the packets in Rx reordering table.
 *
 * The function checks अगर any packets are currently buffered in the
 * table or not. In हाल there are packets available, it dispatches
 * them and then dumps the Rx reordering table.
 */
अटल व्योम
mwअगरiex_flush_data(काष्ठा समयr_list *t)
अणु
	काष्ठा reorder_पंचांगr_cnxt *ctx =
		from_समयr(ctx, t, समयr);
	पूर्णांक start_win, seq_num;

	ctx->समयr_is_set = false;
	seq_num = mwअगरiex_11n_find_last_seq_num(ctx);

	अगर (seq_num < 0)
		वापस;

	mwअगरiex_dbg(ctx->priv->adapter, INFO, "info: flush data %d\n", seq_num);
	start_win = (ctx->ptr->start_win + seq_num + 1) & (MAX_TID_VALUE - 1);
	mwअगरiex_11n_dispatch_pkt_until_start_win(ctx->priv, ctx->ptr,
						 start_win);
पूर्ण

/*
 * This function creates an entry in Rx reordering table क्रम the
 * given TA/TID.
 *
 * The function also initializes the entry with sequence number, winकरोw
 * size as well as initializes the समयr.
 *
 * If the received TA/TID pair is alपढ़ोy present, all the packets are
 * dispatched and the winकरोw size is moved until the SSN.
 */
अटल व्योम
mwअगरiex_11n_create_rx_reorder_tbl(काष्ठा mwअगरiex_निजी *priv, u8 *ta,
				  पूर्णांक tid, पूर्णांक win_size, पूर्णांक seq_num)
अणु
	पूर्णांक i;
	काष्ठा mwअगरiex_rx_reorder_tbl *tbl, *new_node;
	u16 last_seq = 0;
	काष्ठा mwअगरiex_sta_node *node;

	/*
	 * If we get a TID, ta pair which is alपढ़ोy present dispatch all the
	 * the packets and move the winकरोw size until the ssn
	 */
	tbl = mwअगरiex_11n_get_rx_reorder_tbl(priv, tid, ta);
	अगर (tbl) अणु
		mwअगरiex_11n_dispatch_pkt_until_start_win(priv, tbl, seq_num);
		वापस;
	पूर्ण
	/* अगर !tbl then create one */
	new_node = kzalloc(माप(काष्ठा mwअगरiex_rx_reorder_tbl), GFP_KERNEL);
	अगर (!new_node)
		वापस;

	INIT_LIST_HEAD(&new_node->list);
	new_node->tid = tid;
	स_नकल(new_node->ta, ta, ETH_ALEN);
	new_node->start_win = seq_num;
	new_node->init_win = seq_num;
	new_node->flags = 0;

	spin_lock_bh(&priv->sta_list_spinlock);
	अगर (mwअगरiex_queuing_ra_based(priv)) अणु
		अगर (priv->bss_role == MWIFIEX_BSS_ROLE_UAP) अणु
			node = mwअगरiex_get_sta_entry(priv, ta);
			अगर (node)
				last_seq = node->rx_seq[tid];
		पूर्ण
	पूर्ण अन्यथा अणु
		node = mwअगरiex_get_sta_entry(priv, ta);
		अगर (node)
			last_seq = node->rx_seq[tid];
		अन्यथा
			last_seq = priv->rx_seq[tid];
	पूर्ण
	spin_unlock_bh(&priv->sta_list_spinlock);

	mwअगरiex_dbg(priv->adapter, INFO,
		    "info: last_seq=%d start_win=%d\n",
		    last_seq, new_node->start_win);

	अगर (last_seq != MWIFIEX_DEF_11N_RX_SEQ_NUM &&
	    last_seq >= new_node->start_win) अणु
		new_node->start_win = last_seq + 1;
		new_node->flags |= RXREOR_INIT_WINDOW_SHIFT;
	पूर्ण

	new_node->win_size = win_size;

	new_node->rx_reorder_ptr = kसुस्मृति(win_size, माप(व्योम *),
					   GFP_KERNEL);
	अगर (!new_node->rx_reorder_ptr) अणु
		kमुक्त(new_node);
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "%s: failed to alloc reorder_ptr\n", __func__);
		वापस;
	पूर्ण

	new_node->समयr_context.ptr = new_node;
	new_node->समयr_context.priv = priv;
	new_node->समयr_context.समयr_is_set = false;

	समयr_setup(&new_node->समयr_context.समयr, mwअगरiex_flush_data, 0);

	क्रम (i = 0; i < win_size; ++i)
		new_node->rx_reorder_ptr[i] = शून्य;

	spin_lock_bh(&priv->rx_reorder_tbl_lock);
	list_add_tail(&new_node->list, &priv->rx_reorder_tbl_ptr);
	spin_unlock_bh(&priv->rx_reorder_tbl_lock);
पूर्ण

अटल व्योम
mwअगरiex_11n_rxreorder_समयr_restart(काष्ठा mwअगरiex_rx_reorder_tbl *tbl)
अणु
	u32 min_flush_समय;

	अगर (tbl->win_size >= MWIFIEX_BA_WIN_SIZE_32)
		min_flush_समय = MIN_FLUSH_TIMER_15_MS;
	अन्यथा
		min_flush_समय = MIN_FLUSH_TIMER_MS;

	mod_समयr(&tbl->समयr_context.समयr,
		  jअगरfies + msecs_to_jअगरfies(min_flush_समय * tbl->win_size));

	tbl->समयr_context.समयr_is_set = true;
पूर्ण

/*
 * This function prepares command क्रम adding a BA request.
 *
 * Preparation includes -
 *      - Setting command ID and proper size
 *      - Setting add BA request buffer
 *      - Ensuring correct endian-ness
 */
पूर्णांक mwअगरiex_cmd_11n_addba_req(काष्ठा host_cmd_ds_command *cmd, व्योम *data_buf)
अणु
	काष्ठा host_cmd_ds_11n_addba_req *add_ba_req = &cmd->params.add_ba_req;

	cmd->command = cpu_to_le16(HostCmd_CMD_11N_ADDBA_REQ);
	cmd->size = cpu_to_le16(माप(*add_ba_req) + S_DS_GEN);
	स_नकल(add_ba_req, data_buf, माप(*add_ba_req));

	वापस 0;
पूर्ण

/*
 * This function prepares command क्रम adding a BA response.
 *
 * Preparation includes -
 *      - Setting command ID and proper size
 *      - Setting add BA response buffer
 *      - Ensuring correct endian-ness
 */
पूर्णांक mwअगरiex_cmd_11n_addba_rsp_gen(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा host_cmd_ds_command *cmd,
				  काष्ठा host_cmd_ds_11n_addba_req
				  *cmd_addba_req)
अणु
	काष्ठा host_cmd_ds_11n_addba_rsp *add_ba_rsp = &cmd->params.add_ba_rsp;
	काष्ठा mwअगरiex_sta_node *sta_ptr;
	u32 rx_win_size = priv->add_ba_param.rx_win_size;
	u8 tid;
	पूर्णांक win_size;
	uपूर्णांक16_t block_ack_param_set;

	अगर ((GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA) &&
	    ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info) &&
	    priv->adapter->is_hw_11ac_capable &&
	    स_भेद(priv->cfg_bssid, cmd_addba_req->peer_mac_addr, ETH_ALEN)) अणु
		spin_lock_bh(&priv->sta_list_spinlock);
		sta_ptr = mwअगरiex_get_sta_entry(priv,
						cmd_addba_req->peer_mac_addr);
		अगर (!sta_ptr) अणु
			spin_unlock_bh(&priv->sta_list_spinlock);
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "BA setup with unknown TDLS peer %pM!\n",
				    cmd_addba_req->peer_mac_addr);
			वापस -1;
		पूर्ण
		अगर (sta_ptr->is_11ac_enabled)
			rx_win_size = MWIFIEX_11AC_STA_AMPDU_DEF_RXWINSIZE;
		spin_unlock_bh(&priv->sta_list_spinlock);
	पूर्ण

	cmd->command = cpu_to_le16(HostCmd_CMD_11N_ADDBA_RSP);
	cmd->size = cpu_to_le16(माप(*add_ba_rsp) + S_DS_GEN);

	स_नकल(add_ba_rsp->peer_mac_addr, cmd_addba_req->peer_mac_addr,
	       ETH_ALEN);
	add_ba_rsp->dialog_token = cmd_addba_req->dialog_token;
	add_ba_rsp->block_ack_पंचांगo = cmd_addba_req->block_ack_पंचांगo;
	add_ba_rsp->ssn = cmd_addba_req->ssn;

	block_ack_param_set = le16_to_cpu(cmd_addba_req->block_ack_param_set);
	tid = (block_ack_param_set & IEEE80211_ADDBA_PARAM_TID_MASK)
		>> BLOCKACKPARAM_TID_POS;
	add_ba_rsp->status_code = cpu_to_le16(ADDBA_RSP_STATUS_ACCEPT);
	block_ack_param_set &= ~IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK;

	/* If we करोn't support AMSDU inside AMPDU, reset the bit */
	अगर (!priv->add_ba_param.rx_amsdu ||
	    (priv->aggr_prio_tbl[tid].amsdu == BA_STREAM_NOT_ALLOWED))
		block_ack_param_set &= ~BLOCKACKPARAM_AMSDU_SUPP_MASK;
	block_ack_param_set |= rx_win_size << BLOCKACKPARAM_WINSIZE_POS;
	add_ba_rsp->block_ack_param_set = cpu_to_le16(block_ack_param_set);
	win_size = (le16_to_cpu(add_ba_rsp->block_ack_param_set)
					& IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK)
					>> BLOCKACKPARAM_WINSIZE_POS;
	cmd_addba_req->block_ack_param_set = cpu_to_le16(block_ack_param_set);

	mwअगरiex_11n_create_rx_reorder_tbl(priv, cmd_addba_req->peer_mac_addr,
					  tid, win_size,
					  le16_to_cpu(cmd_addba_req->ssn));
	वापस 0;
पूर्ण

/*
 * This function prepares command क्रम deleting a BA request.
 *
 * Preparation includes -
 *      - Setting command ID and proper size
 *      - Setting del BA request buffer
 *      - Ensuring correct endian-ness
 */
पूर्णांक mwअगरiex_cmd_11n_delba(काष्ठा host_cmd_ds_command *cmd, व्योम *data_buf)
अणु
	काष्ठा host_cmd_ds_11n_delba *del_ba = &cmd->params.del_ba;

	cmd->command = cpu_to_le16(HostCmd_CMD_11N_DELBA);
	cmd->size = cpu_to_le16(माप(*del_ba) + S_DS_GEN);
	स_नकल(del_ba, data_buf, माप(*del_ba));

	वापस 0;
पूर्ण

/*
 * This function identअगरies अगर Rx reordering is needed क्रम a received packet.
 *
 * In हाल reordering is required, the function will करो the reordering
 * beक्रमe sending it to kernel.
 *
 * The Rx reorder table is checked first with the received TID/TA pair. If
 * not found, the received packet is dispatched immediately. But अगर found,
 * the packet is reordered and all the packets in the updated Rx reordering
 * table is dispatched until a hole is found.
 *
 * For sequence number less than the starting winकरोw, the packet is dropped.
 */
पूर्णांक mwअगरiex_11n_rx_reorder_pkt(काष्ठा mwअगरiex_निजी *priv,
				u16 seq_num, u16 tid,
				u8 *ta, u8 pkt_type, व्योम *payload)
अणु
	काष्ठा mwअगरiex_rx_reorder_tbl *tbl;
	पूर्णांक prev_start_win, start_win, end_win, win_size;
	u16 pkt_index;
	bool init_winकरोw_shअगरt = false;
	पूर्णांक ret = 0;

	tbl = mwअगरiex_11n_get_rx_reorder_tbl(priv, tid, ta);
	अगर (!tbl) अणु
		अगर (pkt_type != PKT_TYPE_BAR)
			mwअगरiex_11n_dispatch_pkt(priv, payload);
		वापस ret;
	पूर्ण

	अगर ((pkt_type == PKT_TYPE_AMSDU) && !tbl->amsdu) अणु
		mwअगरiex_11n_dispatch_pkt(priv, payload);
		वापस ret;
	पूर्ण

	start_win = tbl->start_win;
	prev_start_win = start_win;
	win_size = tbl->win_size;
	end_win = ((start_win + win_size) - 1) & (MAX_TID_VALUE - 1);
	अगर (tbl->flags & RXREOR_INIT_WINDOW_SHIFT) अणु
		init_winकरोw_shअगरt = true;
		tbl->flags &= ~RXREOR_INIT_WINDOW_SHIFT;
	पूर्ण

	अगर (tbl->flags & RXREOR_FORCE_NO_DROP) अणु
		mwअगरiex_dbg(priv->adapter, INFO,
			    "RXREOR_FORCE_NO_DROP when HS is activated\n");
		tbl->flags &= ~RXREOR_FORCE_NO_DROP;
	पूर्ण अन्यथा अगर (init_winकरोw_shअगरt && seq_num < start_win &&
		   seq_num >= tbl->init_win) अणु
		mwअगरiex_dbg(priv->adapter, INFO,
			    "Sender TID sequence number reset %d->%d for SSN %d\n",
			    start_win, seq_num, tbl->init_win);
		tbl->start_win = start_win = seq_num;
		end_win = ((start_win + win_size) - 1) & (MAX_TID_VALUE - 1);
	पूर्ण अन्यथा अणु
		/*
		 * If seq_num is less then starting win then ignore and drop
		 * the packet
		 */
		अगर ((start_win + TWOPOW11) > (MAX_TID_VALUE - 1)) अणु
			अगर (seq_num >= ((start_win + TWOPOW11) &
					(MAX_TID_VALUE - 1)) &&
			    seq_num < start_win) अणु
				ret = -1;
				जाओ करोne;
			पूर्ण
		पूर्ण अन्यथा अगर ((seq_num < start_win) ||
			   (seq_num >= (start_win + TWOPOW11))) अणु
			ret = -1;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/*
	 * If this packet is a BAR we adjust seq_num as
	 * WinStart = seq_num
	 */
	अगर (pkt_type == PKT_TYPE_BAR)
		seq_num = ((seq_num + win_size) - 1) & (MAX_TID_VALUE - 1);

	अगर (((end_win < start_win) &&
	     (seq_num < start_win) && (seq_num > end_win)) ||
	    ((end_win > start_win) && ((seq_num > end_win) ||
				       (seq_num < start_win)))) अणु
		end_win = seq_num;
		अगर (((end_win - win_size) + 1) >= 0)
			start_win = (end_win - win_size) + 1;
		अन्यथा
			start_win = (MAX_TID_VALUE - (win_size - end_win)) + 1;
		mwअगरiex_11n_dispatch_pkt_until_start_win(priv, tbl, start_win);
	पूर्ण

	अगर (pkt_type != PKT_TYPE_BAR) अणु
		अगर (seq_num >= start_win)
			pkt_index = seq_num - start_win;
		अन्यथा
			pkt_index = (seq_num+MAX_TID_VALUE) - start_win;

		अगर (tbl->rx_reorder_ptr[pkt_index]) अणु
			ret = -1;
			जाओ करोne;
		पूर्ण

		tbl->rx_reorder_ptr[pkt_index] = payload;
	पूर्ण

	/*
	 * Dispatch all packets sequentially from start_win until a
	 * hole is found and adjust the start_win appropriately
	 */
	mwअगरiex_11n_scan_and_dispatch(priv, tbl);

करोne:
	अगर (!tbl->समयr_context.समयr_is_set ||
	    prev_start_win != tbl->start_win)
		mwअगरiex_11n_rxreorder_समयr_restart(tbl);
	वापस ret;
पूर्ण

/*
 * This function deletes an entry क्रम a given TID/TA pair.
 *
 * The TID/TA are taken from del BA event body.
 */
व्योम
mwअगरiex_del_ba_tbl(काष्ठा mwअगरiex_निजी *priv, पूर्णांक tid, u8 *peer_mac,
		   u8 type, पूर्णांक initiator)
अणु
	काष्ठा mwअगरiex_rx_reorder_tbl *tbl;
	काष्ठा mwअगरiex_tx_ba_stream_tbl *ptx_tbl;
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;
	u8 cleanup_rx_reorder_tbl;
	पूर्णांक tid_करोwn;

	अगर (type == TYPE_DELBA_RECEIVE)
		cleanup_rx_reorder_tbl = (initiator) ? true : false;
	अन्यथा
		cleanup_rx_reorder_tbl = (initiator) ? false : true;

	mwअगरiex_dbg(priv->adapter, EVENT, "event: DELBA: %pM tid=%d initiator=%d\n",
		    peer_mac, tid, initiator);

	अगर (cleanup_rx_reorder_tbl) अणु
		tbl = mwअगरiex_11n_get_rx_reorder_tbl(priv, tid,
								 peer_mac);
		अगर (!tbl) अणु
			mwअगरiex_dbg(priv->adapter, EVENT,
				    "event: TID, TA not found in table\n");
			वापस;
		पूर्ण
		mwअगरiex_del_rx_reorder_entry(priv, tbl);
	पूर्ण अन्यथा अणु
		ptx_tbl = mwअगरiex_get_ba_tbl(priv, tid, peer_mac);
		अगर (!ptx_tbl) अणु
			mwअगरiex_dbg(priv->adapter, EVENT,
				    "event: TID, RA not found in table\n");
			वापस;
		पूर्ण

		tid_करोwn = mwअगरiex_wmm_करोwngrade_tid(priv, tid);
		ra_list = mwअगरiex_wmm_get_ralist_node(priv, tid_करोwn, peer_mac);
		अगर (ra_list) अणु
			ra_list->amsdu_in_ampdu = false;
			ra_list->ba_status = BA_SETUP_NONE;
		पूर्ण
		spin_lock_bh(&priv->tx_ba_stream_tbl_lock);
		mwअगरiex_11n_delete_tx_ba_stream_tbl_entry(priv, ptx_tbl);
		spin_unlock_bh(&priv->tx_ba_stream_tbl_lock);
	पूर्ण
पूर्ण

/*
 * This function handles the command response of an add BA response.
 *
 * Handling includes changing the header fields पूर्णांकo CPU क्रमmat and
 * creating the stream, provided the add BA is accepted.
 */
पूर्णांक mwअगरiex_ret_11n_addba_resp(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा host_cmd_ds_command *resp)
अणु
	काष्ठा host_cmd_ds_11n_addba_rsp *add_ba_rsp = &resp->params.add_ba_rsp;
	पूर्णांक tid, win_size;
	काष्ठा mwअगरiex_rx_reorder_tbl *tbl;
	uपूर्णांक16_t block_ack_param_set;

	block_ack_param_set = le16_to_cpu(add_ba_rsp->block_ack_param_set);

	tid = (block_ack_param_set & IEEE80211_ADDBA_PARAM_TID_MASK)
		>> BLOCKACKPARAM_TID_POS;
	/*
	 * Check अगर we had rejected the ADDBA, अगर yes then करो not create
	 * the stream
	 */
	अगर (le16_to_cpu(add_ba_rsp->status_code) != BA_RESULT_SUCCESS) अणु
		mwअगरiex_dbg(priv->adapter, ERROR, "ADDBA RSP: failed %pM tid=%d)\n",
			    add_ba_rsp->peer_mac_addr, tid);

		tbl = mwअगरiex_11n_get_rx_reorder_tbl(priv, tid,
						     add_ba_rsp->peer_mac_addr);
		अगर (tbl)
			mwअगरiex_del_rx_reorder_entry(priv, tbl);

		वापस 0;
	पूर्ण

	win_size = (block_ack_param_set & IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK)
		    >> BLOCKACKPARAM_WINSIZE_POS;

	tbl = mwअगरiex_11n_get_rx_reorder_tbl(priv, tid,
					     add_ba_rsp->peer_mac_addr);
	अगर (tbl) अणु
		अगर ((block_ack_param_set & BLOCKACKPARAM_AMSDU_SUPP_MASK) &&
		    priv->add_ba_param.rx_amsdu &&
		    (priv->aggr_prio_tbl[tid].amsdu != BA_STREAM_NOT_ALLOWED))
			tbl->amsdu = true;
		अन्यथा
			tbl->amsdu = false;
	पूर्ण

	mwअगरiex_dbg(priv->adapter, CMD,
		    "cmd: ADDBA RSP: %pM tid=%d ssn=%d win_size=%d\n",
		add_ba_rsp->peer_mac_addr, tid, add_ba_rsp->ssn, win_size);

	वापस 0;
पूर्ण

/*
 * This function handles BA stream समयout event by preparing and sending
 * a command to the firmware.
 */
व्योम mwअगरiex_11n_ba_stream_समयout(काष्ठा mwअगरiex_निजी *priv,
				   काष्ठा host_cmd_ds_11n_baसमयout *event)
अणु
	काष्ठा host_cmd_ds_11n_delba delba;

	स_रखो(&delba, 0, माप(काष्ठा host_cmd_ds_11n_delba));
	स_नकल(delba.peer_mac_addr, event->peer_mac_addr, ETH_ALEN);

	delba.del_ba_param_set |=
		cpu_to_le16((u16) event->tid << DELBA_TID_POS);
	delba.del_ba_param_set |= cpu_to_le16(
		(u16) event->origninator << DELBA_INITIATOR_POS);
	delba.reason_code = cpu_to_le16(WLAN_REASON_QSTA_TIMEOUT);
	mwअगरiex_send_cmd(priv, HostCmd_CMD_11N_DELBA, 0, 0, &delba, false);
पूर्ण

/*
 * This function cleans up the Rx reorder table by deleting all the entries
 * and re-initializing.
 */
व्योम mwअगरiex_11n_cleanup_reorder_tbl(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_rx_reorder_tbl *del_tbl_ptr, *पंचांगp_node;

	spin_lock_bh(&priv->rx_reorder_tbl_lock);
	list_क्रम_each_entry_safe(del_tbl_ptr, पंचांगp_node,
				 &priv->rx_reorder_tbl_ptr, list) अणु
		spin_unlock_bh(&priv->rx_reorder_tbl_lock);
		mwअगरiex_del_rx_reorder_entry(priv, del_tbl_ptr);
		spin_lock_bh(&priv->rx_reorder_tbl_lock);
	पूर्ण
	INIT_LIST_HEAD(&priv->rx_reorder_tbl_ptr);
	spin_unlock_bh(&priv->rx_reorder_tbl_lock);

	mwअगरiex_reset_11n_rx_seq_num(priv);
पूर्ण

/*
 * This function updates all rx_reorder_tbl's flags.
 */
व्योम mwअगरiex_update_rxreor_flags(काष्ठा mwअगरiex_adapter *adapter, u8 flags)
अणु
	काष्ठा mwअगरiex_निजी *priv;
	काष्ठा mwअगरiex_rx_reorder_tbl *tbl;
	पूर्णांक i;

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		priv = adapter->priv[i];
		अगर (!priv)
			जारी;

		spin_lock_bh(&priv->rx_reorder_tbl_lock);
		list_क्रम_each_entry(tbl, &priv->rx_reorder_tbl_ptr, list)
			tbl->flags = flags;
		spin_unlock_bh(&priv->rx_reorder_tbl_lock);
	पूर्ण

	वापस;
पूर्ण

/* This function update all the rx_win_size based on coex flag
 */
अटल व्योम mwअगरiex_update_ampdu_rxwinsize(काष्ठा mwअगरiex_adapter *adapter,
					   bool coex_flag)
अणु
	u8 i;
	u32 rx_win_size;
	काष्ठा mwअगरiex_निजी *priv;

	dev_dbg(adapter->dev, "Update rxwinsize %d\n", coex_flag);

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		अगर (!adapter->priv[i])
			जारी;
		priv = adapter->priv[i];
		rx_win_size = priv->add_ba_param.rx_win_size;
		अगर (coex_flag) अणु
			अगर (priv->bss_type == MWIFIEX_BSS_TYPE_STA)
				priv->add_ba_param.rx_win_size =
					MWIFIEX_STA_COEX_AMPDU_DEF_RXWINSIZE;
			अगर (priv->bss_type == MWIFIEX_BSS_TYPE_P2P)
				priv->add_ba_param.rx_win_size =
					MWIFIEX_STA_COEX_AMPDU_DEF_RXWINSIZE;
			अगर (priv->bss_type == MWIFIEX_BSS_TYPE_UAP)
				priv->add_ba_param.rx_win_size =
					MWIFIEX_UAP_COEX_AMPDU_DEF_RXWINSIZE;
		पूर्ण अन्यथा अणु
			अगर (priv->bss_type == MWIFIEX_BSS_TYPE_STA)
				priv->add_ba_param.rx_win_size =
					MWIFIEX_STA_AMPDU_DEF_RXWINSIZE;
			अगर (priv->bss_type == MWIFIEX_BSS_TYPE_P2P)
				priv->add_ba_param.rx_win_size =
					MWIFIEX_STA_AMPDU_DEF_RXWINSIZE;
			अगर (priv->bss_type == MWIFIEX_BSS_TYPE_UAP)
				priv->add_ba_param.rx_win_size =
					MWIFIEX_UAP_AMPDU_DEF_RXWINSIZE;
		पूर्ण

		अगर (adapter->coex_win_size && adapter->coex_rx_win_size)
			priv->add_ba_param.rx_win_size =
					adapter->coex_rx_win_size;

		अगर (rx_win_size != priv->add_ba_param.rx_win_size) अणु
			अगर (!priv->media_connected)
				जारी;
			क्रम (i = 0; i < MAX_NUM_TID; i++)
				mwअगरiex_11n_delba(priv, i);
		पूर्ण
	पूर्ण
पूर्ण

/* This function check coex क्रम RX BA
 */
व्योम mwअगरiex_coex_ampdu_rxwinsize(काष्ठा mwअगरiex_adapter *adapter)
अणु
	u8 i;
	काष्ठा mwअगरiex_निजी *priv;
	u8 count = 0;

	क्रम (i = 0; i < adapter->priv_num; i++) अणु
		अगर (adapter->priv[i]) अणु
			priv = adapter->priv[i];
			अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA) अणु
				अगर (priv->media_connected)
					count++;
			पूर्ण
			अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) अणु
				अगर (priv->bss_started)
					count++;
			पूर्ण
		पूर्ण
		अगर (count >= MWIFIEX_BSS_COEX_COUNT)
			अवरोध;
	पूर्ण
	अगर (count >= MWIFIEX_BSS_COEX_COUNT)
		mwअगरiex_update_ampdu_rxwinsize(adapter, true);
	अन्यथा
		mwअगरiex_update_ampdu_rxwinsize(adapter, false);
पूर्ण

/* This function handles rxba_sync event
 */
व्योम mwअगरiex_11n_rxba_sync_event(काष्ठा mwअगरiex_निजी *priv,
				 u8 *event_buf, u16 len)
अणु
	काष्ठा mwअगरiex_ie_types_rxba_sync *tlv_rxba = (व्योम *)event_buf;
	u16 tlv_type, tlv_len;
	काष्ठा mwअगरiex_rx_reorder_tbl *rx_reor_tbl_ptr;
	u8 i, j;
	u16 seq_num, tlv_seq_num, tlv_biपंचांगap_len;
	पूर्णांक tlv_buf_left = len;
	पूर्णांक ret;
	u8 *पंचांगp;

	mwअगरiex_dbg_dump(priv->adapter, EVT_D, "RXBA_SYNC event:",
			 event_buf, len);
	जबतक (tlv_buf_left >= माप(*tlv_rxba)) अणु
		tlv_type = le16_to_cpu(tlv_rxba->header.type);
		tlv_len  = le16_to_cpu(tlv_rxba->header.len);
		अगर (tlv_type != TLV_TYPE_RXBA_SYNC) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "Wrong TLV id=0x%x\n", tlv_type);
			वापस;
		पूर्ण

		tlv_seq_num = le16_to_cpu(tlv_rxba->seq_num);
		tlv_biपंचांगap_len = le16_to_cpu(tlv_rxba->biपंचांगap_len);
		mwअगरiex_dbg(priv->adapter, INFO,
			    "%pM tid=%d seq_num=%d bitmap_len=%d\n",
			    tlv_rxba->mac, tlv_rxba->tid, tlv_seq_num,
			    tlv_biपंचांगap_len);

		rx_reor_tbl_ptr =
			mwअगरiex_11n_get_rx_reorder_tbl(priv, tlv_rxba->tid,
						       tlv_rxba->mac);
		अगर (!rx_reor_tbl_ptr) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "Can not find rx_reorder_tbl!");
			वापस;
		पूर्ण

		क्रम (i = 0; i < tlv_biपंचांगap_len; i++) अणु
			क्रम (j = 0 ; j < 8; j++) अणु
				अगर (tlv_rxba->biपंचांगap[i] & (1 << j)) अणु
					seq_num = (MAX_TID_VALUE - 1) &
						(tlv_seq_num + i * 8 + j);

					mwअगरiex_dbg(priv->adapter, ERROR,
						    "drop packet,seq=%d\n",
						    seq_num);

					ret = mwअगरiex_11n_rx_reorder_pkt
					(priv, seq_num, tlv_rxba->tid,
					 tlv_rxba->mac, 0, शून्य);

					अगर (ret)
						mwअगरiex_dbg(priv->adapter,
							    ERROR,
							    "Fail to drop packet");
				पूर्ण
			पूर्ण
		पूर्ण

		tlv_buf_left -= (माप(*tlv_rxba) + tlv_len);
		पंचांगp = (u8 *)tlv_rxba + tlv_len + माप(*tlv_rxba);
		tlv_rxba = (काष्ठा mwअगरiex_ie_types_rxba_sync *)पंचांगp;
	पूर्ण
पूर्ण
