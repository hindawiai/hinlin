<शैली गुरु>
/*
 * NXP Wireless LAN device driver: AP TX and RX data handling
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
#समावेश "main.h"
#समावेश "wmm.h"
#समावेश "11n_aggr.h"
#समावेश "11n_rxreorder.h"

/* This function checks अगर particular RA list has packets more than low bridge
 * packet threshold and then deletes packet from this RA list.
 * Function deletes packets from such RA list and वापसs true. If no such list
 * is found, false is वापसed.
 */
अटल bool
mwअगरiex_uap_del_tx_pkts_in_ralist(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा list_head *ra_list_head,
				  पूर्णांक tid)
अणु
	काष्ठा mwअगरiex_ra_list_tbl *ra_list;
	काष्ठा sk_buff *skb, *पंचांगp;
	bool pkt_deleted = false;
	काष्ठा mwअगरiex_txinfo *tx_info;
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;

	list_क्रम_each_entry(ra_list, ra_list_head, list) अणु
		अगर (skb_queue_empty(&ra_list->skb_head))
			जारी;

		skb_queue_walk_safe(&ra_list->skb_head, skb, पंचांगp) अणु
			tx_info = MWIFIEX_SKB_TXCB(skb);
			अगर (tx_info->flags & MWIFIEX_BUF_FLAG_BRIDGED_PKT) अणु
				__skb_unlink(skb, &ra_list->skb_head);
				mwअगरiex_ग_लिखो_data_complete(adapter, skb, 0,
							    -1);
				अगर (ra_list->tx_छोड़ोd)
					priv->wmm.pkts_छोड़ोd[tid]--;
				अन्यथा
					atomic_dec(&priv->wmm.tx_pkts_queued);
				pkt_deleted = true;
			पूर्ण
			अगर ((atomic_पढ़ो(&adapter->pending_bridged_pkts) <=
					     MWIFIEX_BRIDGED_PKTS_THR_LOW))
				अवरोध;
		पूर्ण
	पूर्ण

	वापस pkt_deleted;
पूर्ण

/* This function deletes packets from particular RA List. RA list index
 * from which packets are deleted is preserved so that packets from next RA
 * list are deleted upon subsequent call thus मुख्यtaining fairness.
 */
अटल व्योम mwअगरiex_uap_cleanup_tx_queues(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा list_head *ra_list;
	पूर्णांक i;

	spin_lock_bh(&priv->wmm.ra_list_spinlock);

	क्रम (i = 0; i < MAX_NUM_TID; i++, priv->del_list_idx++) अणु
		अगर (priv->del_list_idx == MAX_NUM_TID)
			priv->del_list_idx = 0;
		ra_list = &priv->wmm.tid_tbl_ptr[priv->del_list_idx].ra_list;
		अगर (mwअगरiex_uap_del_tx_pkts_in_ralist(priv, ra_list, i)) अणु
			priv->del_list_idx++;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&priv->wmm.ra_list_spinlock);
पूर्ण


अटल व्योम mwअगरiex_uap_queue_bridged_pkt(काष्ठा mwअगरiex_निजी *priv,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा uap_rxpd *uap_rx_pd;
	काष्ठा rx_packet_hdr *rx_pkt_hdr;
	काष्ठा sk_buff *new_skb;
	काष्ठा mwअगरiex_txinfo *tx_info;
	पूर्णांक hdr_chop;
	काष्ठा ethhdr *p_ethhdr;
	काष्ठा mwअगरiex_sta_node *src_node;
	पूर्णांक index;

	uap_rx_pd = (काष्ठा uap_rxpd *)(skb->data);
	rx_pkt_hdr = (व्योम *)uap_rx_pd + le16_to_cpu(uap_rx_pd->rx_pkt_offset);

	अगर ((atomic_पढ़ो(&adapter->pending_bridged_pkts) >=
					     MWIFIEX_BRIDGED_PKTS_THR_HIGH)) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "Tx: Bridge packet limit reached. Drop packet!\n");
		kमुक्त_skb(skb);
		mwअगरiex_uap_cleanup_tx_queues(priv);
		वापस;
	पूर्ण

	अगर ((!स_भेद(&rx_pkt_hdr->rfc1042_hdr, bridge_tunnel_header,
		     माप(bridge_tunnel_header))) ||
	    (!स_भेद(&rx_pkt_hdr->rfc1042_hdr, rfc1042_header,
		     माप(rfc1042_header)) &&
	     ntohs(rx_pkt_hdr->rfc1042_hdr.snap_type) != ETH_P_AARP &&
	     ntohs(rx_pkt_hdr->rfc1042_hdr.snap_type) != ETH_P_IPX)) अणु
		/* Replace the 803 header and rfc1042 header (llc/snap) with
		 * an Ethernet II header, keep the src/dst and snap_type
		 * (ethertype).
		 *
		 * The firmware only passes up SNAP frames converting all RX
		 * data from 802.11 to 802.2/LLC/SNAP frames.
		 *
		 * To create the Ethernet II, just move the src, dst address
		 * right beक्रमe the snap_type.
		 */
		p_ethhdr = (काष्ठा ethhdr *)
			((u8 *)(&rx_pkt_hdr->eth803_hdr)
			 + माप(rx_pkt_hdr->eth803_hdr)
			 + माप(rx_pkt_hdr->rfc1042_hdr)
			 - माप(rx_pkt_hdr->eth803_hdr.h_dest)
			 - माप(rx_pkt_hdr->eth803_hdr.h_source)
			 - माप(rx_pkt_hdr->rfc1042_hdr.snap_type));
		स_नकल(p_ethhdr->h_source, rx_pkt_hdr->eth803_hdr.h_source,
		       माप(p_ethhdr->h_source));
		स_नकल(p_ethhdr->h_dest, rx_pkt_hdr->eth803_hdr.h_dest,
		       माप(p_ethhdr->h_dest));
		/* Chop off the rxpd + the excess memory from
		 * 802.2/llc/snap header that was हटाओd.
		 */
		hdr_chop = (u8 *)p_ethhdr - (u8 *)uap_rx_pd;
	पूर्ण अन्यथा अणु
		/* Chop off the rxpd */
		hdr_chop = (u8 *)&rx_pkt_hdr->eth803_hdr - (u8 *)uap_rx_pd;
	पूर्ण

	/* Chop off the leading header bytes so that it poपूर्णांकs
	 * to the start of either the reस्थिरructed EthII frame
	 * or the 802.2/llc/snap frame.
	 */
	skb_pull(skb, hdr_chop);

	अगर (skb_headroom(skb) < MWIFIEX_MIN_DATA_HEADER_LEN) अणु
		mwअगरiex_dbg(priv->adapter, ERROR,
			    "data: Tx: insufficient skb headroom %d\n",
			    skb_headroom(skb));
		/* Insufficient skb headroom - allocate a new skb */
		new_skb =
			skb_पुनः_स्मृति_headroom(skb, MWIFIEX_MIN_DATA_HEADER_LEN);
		अगर (unlikely(!new_skb)) अणु
			mwअगरiex_dbg(priv->adapter, ERROR,
				    "Tx: cannot allocate new_skb\n");
			kमुक्त_skb(skb);
			priv->stats.tx_dropped++;
			वापस;
		पूर्ण

		kमुक्त_skb(skb);
		skb = new_skb;
		mwअगरiex_dbg(priv->adapter, INFO,
			    "info: new skb headroom %d\n",
			    skb_headroom(skb));
	पूर्ण

	tx_info = MWIFIEX_SKB_TXCB(skb);
	स_रखो(tx_info, 0, माप(*tx_info));
	tx_info->bss_num = priv->bss_num;
	tx_info->bss_type = priv->bss_type;
	tx_info->flags |= MWIFIEX_BUF_FLAG_BRIDGED_PKT;

	src_node = mwअगरiex_get_sta_entry(priv, rx_pkt_hdr->eth803_hdr.h_source);
	अगर (src_node) अणु
		src_node->stats.last_rx = jअगरfies;
		src_node->stats.rx_bytes += skb->len;
		src_node->stats.rx_packets++;
		src_node->stats.last_tx_rate = uap_rx_pd->rx_rate;
		src_node->stats.last_tx_htinfo = uap_rx_pd->ht_info;
	पूर्ण

	अगर (is_unicast_ether_addr(rx_pkt_hdr->eth803_hdr.h_dest)) अणु
		/* Update bridge packet statistics as the
		 * packet is not going to kernel/upper layer.
		 */
		priv->stats.rx_bytes += skb->len;
		priv->stats.rx_packets++;

		/* Sending bridge packet to TX queue, so save the packet
		 * length in TXCB to update statistics in TX complete.
		 */
		tx_info->pkt_len = skb->len;
	पूर्ण

	__net_बारtamp(skb);

	index = mwअगरiex_1d_to_wmm_queue[skb->priority];
	atomic_inc(&priv->wmm_tx_pending[index]);
	mwअगरiex_wmm_add_buf_txqueue(priv, skb);
	atomic_inc(&adapter->tx_pending);
	atomic_inc(&adapter->pending_bridged_pkts);

	mwअगरiex_queue_मुख्य_work(priv->adapter);

	वापस;
पूर्ण

/*
 * This function contains logic क्रम AP packet क्रमwarding.
 *
 * If a packet is multicast/broadcast, it is sent to kernel/upper layer
 * as well as queued back to AP TX queue so that it can be sent to other
 * associated stations.
 * If a packet is unicast and RA is present in associated station list,
 * it is again requeued पूर्णांकo AP TX queue.
 * If a packet is unicast and RA is not in associated station list,
 * packet is क्रमwarded to kernel to handle routing logic.
 */
पूर्णांक mwअगरiex_handle_uap_rx_क्रमward(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा uap_rxpd *uap_rx_pd;
	काष्ठा rx_packet_hdr *rx_pkt_hdr;
	u8 ra[ETH_ALEN];
	काष्ठा sk_buff *skb_uap;

	uap_rx_pd = (काष्ठा uap_rxpd *)(skb->data);
	rx_pkt_hdr = (व्योम *)uap_rx_pd + le16_to_cpu(uap_rx_pd->rx_pkt_offset);

	/* करोn't करो packet क्रमwarding in disconnected state */
	अगर (!priv->media_connected) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "drop packet in disconnected state.\n");
		dev_kमुक्त_skb_any(skb);
		वापस 0;
	पूर्ण

	स_नकल(ra, rx_pkt_hdr->eth803_hdr.h_dest, ETH_ALEN);

	अगर (is_multicast_ether_addr(ra)) अणु
		skb_uap = skb_copy(skb, GFP_ATOMIC);
		mwअगरiex_uap_queue_bridged_pkt(priv, skb_uap);
	पूर्ण अन्यथा अणु
		अगर (mwअगरiex_get_sta_entry(priv, ra)) अणु
			/* Requeue Intra-BSS packet */
			mwअगरiex_uap_queue_bridged_pkt(priv, skb);
			वापस 0;
		पूर्ण
	पूर्ण

	/* Forward unicat/Inter-BSS packets to kernel. */
	वापस mwअगरiex_process_rx_packet(priv, skb);
पूर्ण

पूर्णांक mwअगरiex_uap_recv_packet(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा mwअगरiex_sta_node *src_node;
	काष्ठा ethhdr *p_ethhdr;
	काष्ठा sk_buff *skb_uap;
	काष्ठा mwअगरiex_txinfo *tx_info;

	अगर (!skb)
		वापस -1;

	p_ethhdr = (व्योम *)skb->data;
	src_node = mwअगरiex_get_sta_entry(priv, p_ethhdr->h_source);
	अगर (src_node) अणु
		src_node->stats.last_rx = jअगरfies;
		src_node->stats.rx_bytes += skb->len;
		src_node->stats.rx_packets++;
	पूर्ण

	अगर (is_multicast_ether_addr(p_ethhdr->h_dest) ||
	    mwअगरiex_get_sta_entry(priv, p_ethhdr->h_dest)) अणु
		अगर (skb_headroom(skb) < MWIFIEX_MIN_DATA_HEADER_LEN)
			skb_uap =
			skb_पुनः_स्मृति_headroom(skb, MWIFIEX_MIN_DATA_HEADER_LEN);
		अन्यथा
			skb_uap = skb_copy(skb, GFP_ATOMIC);

		अगर (likely(skb_uap)) अणु
			tx_info = MWIFIEX_SKB_TXCB(skb_uap);
			स_रखो(tx_info, 0, माप(*tx_info));
			tx_info->bss_num = priv->bss_num;
			tx_info->bss_type = priv->bss_type;
			tx_info->flags |= MWIFIEX_BUF_FLAG_BRIDGED_PKT;
			__net_बारtamp(skb_uap);
			mwअगरiex_wmm_add_buf_txqueue(priv, skb_uap);
			atomic_inc(&adapter->tx_pending);
			atomic_inc(&adapter->pending_bridged_pkts);
			अगर ((atomic_पढ़ो(&adapter->pending_bridged_pkts) >=
					MWIFIEX_BRIDGED_PKTS_THR_HIGH)) अणु
				mwअगरiex_dbg(adapter, ERROR,
					    "Tx: Bridge packet limit reached. Drop packet!\n");
				mwअगरiex_uap_cleanup_tx_queues(priv);
			पूर्ण

		पूर्ण अन्यथा अणु
			mwअगरiex_dbg(adapter, ERROR, "failed to allocate skb_uap");
		पूर्ण

		mwअगरiex_queue_मुख्य_work(adapter);
		/* Don't क्रमward Intra-BSS unicast packet to upper layer*/
		अगर (mwअगरiex_get_sta_entry(priv, p_ethhdr->h_dest))
			वापस 0;
	पूर्ण

	skb->dev = priv->netdev;
	skb->protocol = eth_type_trans(skb, priv->netdev);
	skb->ip_summed = CHECKSUM_NONE;

	/* This is required only in हाल of 11n and USB/PCIE as we alloc
	 * a buffer of 4K only अगर its 11N (to be able to receive 4K
	 * AMSDU packets). In हाल of SD we allocate buffers based
	 * on the size of packet and hence this is not needed.
	 *
	 * Modअगरying the truesize here as our allocation क्रम each
	 * skb is 4K but we only receive 2K packets and this cause
	 * the kernel to start dropping packets in हाल where
	 * application has allocated buffer based on 2K size i.e.
	 * अगर there a 64K packet received (in IP fragments and
	 * application allocates 64K to receive this packet but
	 * this packet would almost द्विगुन up because we allocate
	 * each 1.5K fragment in 4K and pass it up. As soon as the
	 * 64K limit hits kernel will start to drop rest of the
	 * fragments. Currently we fail the Filesndl-ht.scr script
	 * क्रम UDP, hence this fix
	 */
	अगर ((adapter->अगरace_type == MWIFIEX_USB ||
	     adapter->अगरace_type == MWIFIEX_PCIE) &&
	    skb->truesize > MWIFIEX_RX_DATA_BUF_SIZE)
		skb->truesize += (skb->len - MWIFIEX_RX_DATA_BUF_SIZE);

	/* Forward multicast/broadcast packet to upper layer*/
	netअगर_rx_any_context(skb);
	वापस 0;
पूर्ण

/*
 * This function processes the packet received on AP पूर्णांकerface.
 *
 * The function looks पूर्णांकo the RxPD and perक्रमms sanity tests on the
 * received buffer to ensure its a valid packet beक्रमe processing it
 * further. If the packet is determined to be aggregated, it is
 * de-aggregated accordingly. Then skb is passed to AP packet क्रमwarding logic.
 *
 * The completion callback is called after processing is complete.
 */
पूर्णांक mwअगरiex_process_uap_rx_packet(काष्ठा mwअगरiex_निजी *priv,
				  काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	पूर्णांक ret;
	काष्ठा uap_rxpd *uap_rx_pd;
	काष्ठा rx_packet_hdr *rx_pkt_hdr;
	u16 rx_pkt_type;
	u8 ta[ETH_ALEN], pkt_type;
	काष्ठा mwअगरiex_sta_node *node;

	uap_rx_pd = (काष्ठा uap_rxpd *)(skb->data);
	rx_pkt_type = le16_to_cpu(uap_rx_pd->rx_pkt_type);
	rx_pkt_hdr = (व्योम *)uap_rx_pd + le16_to_cpu(uap_rx_pd->rx_pkt_offset);

	ether_addr_copy(ta, rx_pkt_hdr->eth803_hdr.h_source);

	अगर ((le16_to_cpu(uap_rx_pd->rx_pkt_offset) +
	     le16_to_cpu(uap_rx_pd->rx_pkt_length)) > (u16) skb->len) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "wrong rx packet: len=%d, offset=%d, length=%d\n",
			    skb->len, le16_to_cpu(uap_rx_pd->rx_pkt_offset),
			    le16_to_cpu(uap_rx_pd->rx_pkt_length));
		priv->stats.rx_dropped++;

		node = mwअगरiex_get_sta_entry(priv, ta);
		अगर (node)
			node->stats.tx_failed++;

		dev_kमुक्त_skb_any(skb);
		वापस 0;
	पूर्ण

	अगर (rx_pkt_type == PKT_TYPE_MGMT) अणु
		ret = mwअगरiex_process_mgmt_packet(priv, skb);
		अगर (ret)
			mwअगरiex_dbg(adapter, DATA, "Rx of mgmt packet failed");
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण


	अगर (rx_pkt_type != PKT_TYPE_BAR && uap_rx_pd->priority < MAX_NUM_TID) अणु
		spin_lock_bh(&priv->sta_list_spinlock);
		node = mwअगरiex_get_sta_entry(priv, ta);
		अगर (node)
			node->rx_seq[uap_rx_pd->priority] =
						le16_to_cpu(uap_rx_pd->seq_num);
		spin_unlock_bh(&priv->sta_list_spinlock);
	पूर्ण

	अगर (!priv->ap_11n_enabled ||
	    (!mwअगरiex_11n_get_rx_reorder_tbl(priv, uap_rx_pd->priority, ta) &&
	    (le16_to_cpu(uap_rx_pd->rx_pkt_type) != PKT_TYPE_AMSDU))) अणु
		ret = mwअगरiex_handle_uap_rx_क्रमward(priv, skb);
		वापस ret;
	पूर्ण

	/* Reorder and send to kernel */
	pkt_type = (u8)le16_to_cpu(uap_rx_pd->rx_pkt_type);
	ret = mwअगरiex_11n_rx_reorder_pkt(priv, le16_to_cpu(uap_rx_pd->seq_num),
					 uap_rx_pd->priority, ta, pkt_type,
					 skb);

	अगर (ret || (rx_pkt_type == PKT_TYPE_BAR))
		dev_kमुक्त_skb_any(skb);

	अगर (ret)
		priv->stats.rx_dropped++;

	वापस ret;
पूर्ण

/*
 * This function fills the TxPD क्रम AP tx packets.
 *
 * The Tx buffer received by this function should alपढ़ोy have the
 * header space allocated क्रम TxPD.
 *
 * This function inserts the TxPD in between पूर्णांकerface header and actual
 * data and adjusts the buffer poपूर्णांकers accordingly.
 *
 * The following TxPD fields are set by this function, as required -
 *      - BSS number
 *      - Tx packet length and offset
 *      - Priority
 *      - Packet delay
 *      - Priority specअगरic Tx control
 *      - Flags
 */
व्योम *mwअगरiex_process_uap_txpd(काष्ठा mwअगरiex_निजी *priv,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा uap_txpd *txpd;
	काष्ठा mwअगरiex_txinfo *tx_info = MWIFIEX_SKB_TXCB(skb);
	पूर्णांक pad;
	u16 pkt_type, pkt_offset;
	पूर्णांक hroom = adapter->पूर्णांकf_hdr_len;

	अगर (!skb->len) अणु
		mwअगरiex_dbg(adapter, ERROR,
			    "Tx: bad packet length: %d\n", skb->len);
		tx_info->status_code = -1;
		वापस skb->data;
	पूर्ण

	BUG_ON(skb_headroom(skb) < MWIFIEX_MIN_DATA_HEADER_LEN);

	pkt_type = mwअगरiex_is_skb_mgmt_frame(skb) ? PKT_TYPE_MGMT : 0;

	pad = ((व्योम *)skb->data - (माप(*txpd) + hroom) - शून्य) &
			(MWIFIEX_DMA_ALIGN_SZ - 1);

	skb_push(skb, माप(*txpd) + pad);

	txpd = (काष्ठा uap_txpd *)skb->data;
	स_रखो(txpd, 0, माप(*txpd));
	txpd->bss_num = priv->bss_num;
	txpd->bss_type = priv->bss_type;
	txpd->tx_pkt_length = cpu_to_le16((u16)(skb->len - (माप(*txpd) +
						pad)));
	txpd->priority = (u8)skb->priority;

	txpd->pkt_delay_2ms = mwअगरiex_wmm_compute_drv_pkt_delay(priv, skb);

	अगर (tx_info->flags & MWIFIEX_BUF_FLAG_EAPOL_TX_STATUS ||
	    tx_info->flags & MWIFIEX_BUF_FLAG_ACTION_TX_STATUS) अणु
		txpd->tx_token_id = tx_info->ack_frame_id;
		txpd->flags |= MWIFIEX_TXPD_FLAGS_REQ_TX_STATUS;
	पूर्ण

	अगर (txpd->priority < ARRAY_SIZE(priv->wmm.user_pri_pkt_tx_ctrl))
		/*
		 * Set the priority specअगरic tx_control field, setting of 0 will
		 * cause the शेष value to be used later in this function.
		 */
		txpd->tx_control =
		    cpu_to_le32(priv->wmm.user_pri_pkt_tx_ctrl[txpd->priority]);

	/* Offset of actual data */
	pkt_offset = माप(*txpd) + pad;
	अगर (pkt_type == PKT_TYPE_MGMT) अणु
		/* Set the packet type and add header क्रम management frame */
		txpd->tx_pkt_type = cpu_to_le16(pkt_type);
		pkt_offset += MWIFIEX_MGMT_FRAME_HEADER_SIZE;
	पूर्ण

	txpd->tx_pkt_offset = cpu_to_le16(pkt_offset);

	/* make space क्रम adapter->पूर्णांकf_hdr_len */
	skb_push(skb, hroom);

	अगर (!txpd->tx_control)
		/* TxCtrl set by user or शेष */
		txpd->tx_control = cpu_to_le32(priv->pkt_tx_ctrl);

	वापस skb->data;
पूर्ण
