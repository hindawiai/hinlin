<शैली गुरु>
/*
 * NXP Wireless LAN device driver: 802.11n Aggregation
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
#समावेश "11n_aggr.h"

/*
 * Creates an AMSDU subframe क्रम aggregation पूर्णांकo one AMSDU packet.
 *
 * The resultant AMSDU subframe क्रमmat is -
 *
 * +---- ~ -----+---- ~ ------+---- ~ -----+----- ~ -----+---- ~ -----+
 * |     DA     |     SA      |   Length   | SNAP header |   MSDU     |
 * | data[0..5] | data[6..11] |            |             | data[14..] |
 * +---- ~ -----+---- ~ ------+---- ~ -----+----- ~ -----+---- ~ -----+
 * <--6-bytes--> <--6-bytes--> <--2-bytes--><--8-bytes--> <--n-bytes-->
 *
 * This function also computes the amount of padding required to make the
 * buffer length multiple of 4 bytes.
 *
 * Data => |DA|SA|SNAP-TYPE|........    .|
 * MSDU => |DA|SA|Length|SNAP|......   ..|
 */
अटल पूर्णांक
mwअगरiex_11n_क्रमm_amsdu_pkt(काष्ठा sk_buff *skb_aggr,
			   काष्ठा sk_buff *skb_src, पूर्णांक *pad)

अणु
	पूर्णांक dt_offset;
	काष्ठा rfc_1042_hdr snap = अणु
		0xaa,		/* LLC DSAP */
		0xaa,		/* LLC SSAP */
		0x03,		/* LLC CTRL */
		अणु0x00, 0x00, 0x00पूर्ण,	/* SNAP OUI */
		0x0000		/* SNAP type */
			/*
			 * This field will be overwritten
			 * later with ethertype
			 */
	पूर्ण;
	काष्ठा tx_packet_hdr *tx_header;

	tx_header = skb_put(skb_aggr, माप(*tx_header));

	/* Copy DA and SA */
	dt_offset = 2 * ETH_ALEN;
	स_नकल(&tx_header->eth803_hdr, skb_src->data, dt_offset);

	/* Copy SNAP header */
	snap.snap_type = ((काष्ठा ethhdr *)skb_src->data)->h_proto;

	dt_offset += माप(__be16);

	स_नकल(&tx_header->rfc1042_hdr, &snap, माप(काष्ठा rfc_1042_hdr));

	skb_pull(skb_src, dt_offset);

	/* Update Length field */
	tx_header->eth803_hdr.h_proto = htons(skb_src->len + LLC_SNAP_LEN);

	/* Add payload */
	skb_put_data(skb_aggr, skb_src->data, skb_src->len);

	/* Add padding क्रम new MSDU to start from 4 byte boundary */
	*pad = (4 - ((अचिन्हित दीर्घ)skb_aggr->tail & 0x3)) % 4;

	वापस skb_aggr->len + *pad;
पूर्ण

/*
 * Adds TxPD to AMSDU header.
 *
 * Each AMSDU packet will contain one TxPD at the beginning,
 * followed by multiple AMSDU subframes.
 */
अटल व्योम
mwअगरiex_11n_क्रमm_amsdu_txpd(काष्ठा mwअगरiex_निजी *priv,
			    काष्ठा sk_buff *skb)
अणु
	काष्ठा txpd *local_tx_pd;
	काष्ठा mwअगरiex_txinfo *tx_info = MWIFIEX_SKB_TXCB(skb);

	skb_push(skb, माप(*local_tx_pd));

	local_tx_pd = (काष्ठा txpd *) skb->data;
	स_रखो(local_tx_pd, 0, माप(काष्ठा txpd));

	/* Original priority has been overwritten */
	local_tx_pd->priority = (u8) skb->priority;
	local_tx_pd->pkt_delay_2ms =
		mwअगरiex_wmm_compute_drv_pkt_delay(priv, skb);
	local_tx_pd->bss_num = priv->bss_num;
	local_tx_pd->bss_type = priv->bss_type;
	/* Always zero as the data is followed by काष्ठा txpd */
	local_tx_pd->tx_pkt_offset = cpu_to_le16(माप(काष्ठा txpd));
	local_tx_pd->tx_pkt_type = cpu_to_le16(PKT_TYPE_AMSDU);
	local_tx_pd->tx_pkt_length = cpu_to_le16(skb->len -
						 माप(*local_tx_pd));

	अगर (tx_info->flags & MWIFIEX_BUF_FLAG_TDLS_PKT)
		local_tx_pd->flags |= MWIFIEX_TXPD_FLAGS_TDLS_PACKET;

	अगर (local_tx_pd->tx_control == 0)
		/* TxCtrl set by user or शेष */
		local_tx_pd->tx_control = cpu_to_le32(priv->pkt_tx_ctrl);

	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA &&
	    priv->adapter->pps_uapsd_mode) अणु
		अगर (true == mwअगरiex_check_last_packet_indication(priv)) अणु
			priv->adapter->tx_lock_flag = true;
			local_tx_pd->flags =
				MWIFIEX_TxPD_POWER_MGMT_LAST_PACKET;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Create aggregated packet.
 *
 * This function creates an aggregated MSDU packet, by combining buffers
 * from the RA list. Each inभागidual buffer is encapsulated as an AMSDU
 * subframe and all such subframes are concatenated together to क्रमm the
 * AMSDU packet.
 *
 * A TxPD is also added to the front of the resultant AMSDU packets क्रम
 * transmission. The resultant packets क्रमmat is -
 *
 * +---- ~ ----+------ ~ ------+------ ~ ------+-..-+------ ~ ------+
 * |    TxPD   |AMSDU sub-frame|AMSDU sub-frame| .. |AMSDU sub-frame|
 * |           |       1       |       2       | .. |       n       |
 * +---- ~ ----+------ ~ ------+------ ~ ------+ .. +------ ~ ------+
 */
पूर्णांक
mwअगरiex_11n_aggregate_pkt(काष्ठा mwअगरiex_निजी *priv,
			  काष्ठा mwअगरiex_ra_list_tbl *pra_list,
			  पूर्णांक ptrindex)
			  __releases(&priv->wmm.ra_list_spinlock)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा sk_buff *skb_aggr, *skb_src;
	काष्ठा mwअगरiex_txinfo *tx_info_aggr, *tx_info_src;
	पूर्णांक pad = 0, aggr_num = 0, ret;
	काष्ठा mwअगरiex_tx_param tx_param;
	काष्ठा txpd *ptx_pd = शून्य;
	पूर्णांक headroom = adapter->पूर्णांकf_hdr_len;

	skb_src = skb_peek(&pra_list->skb_head);
	अगर (!skb_src) अणु
		spin_unlock_bh(&priv->wmm.ra_list_spinlock);
		वापस 0;
	पूर्ण

	tx_info_src = MWIFIEX_SKB_TXCB(skb_src);
	skb_aggr = mwअगरiex_alloc_dma_align_buf(adapter->tx_buf_size,
					       GFP_ATOMIC);
	अगर (!skb_aggr) अणु
		spin_unlock_bh(&priv->wmm.ra_list_spinlock);
		वापस -1;
	पूर्ण

	/* skb_aggr->data alपढ़ोy 64 byte align, just reserve bus पूर्णांकerface
	 * header and txpd.
	 */
	skb_reserve(skb_aggr, headroom + माप(काष्ठा txpd));
	tx_info_aggr =  MWIFIEX_SKB_TXCB(skb_aggr);

	स_रखो(tx_info_aggr, 0, माप(*tx_info_aggr));
	tx_info_aggr->bss_type = tx_info_src->bss_type;
	tx_info_aggr->bss_num = tx_info_src->bss_num;

	अगर (tx_info_src->flags & MWIFIEX_BUF_FLAG_TDLS_PKT)
		tx_info_aggr->flags |= MWIFIEX_BUF_FLAG_TDLS_PKT;
	tx_info_aggr->flags |= MWIFIEX_BUF_FLAG_AGGR_PKT;
	skb_aggr->priority = skb_src->priority;
	skb_aggr->tstamp = skb_src->tstamp;

	करो अणु
		/* Check अगर AMSDU can accommodate this MSDU */
		अगर ((skb_aggr->len + skb_src->len + LLC_SNAP_LEN) >
		    adapter->tx_buf_size)
			अवरोध;

		skb_src = skb_dequeue(&pra_list->skb_head);
		pra_list->total_pkt_count--;
		atomic_dec(&priv->wmm.tx_pkts_queued);
		aggr_num++;
		spin_unlock_bh(&priv->wmm.ra_list_spinlock);
		mwअगरiex_11n_क्रमm_amsdu_pkt(skb_aggr, skb_src, &pad);

		mwअगरiex_ग_लिखो_data_complete(adapter, skb_src, 0, 0);

		spin_lock_bh(&priv->wmm.ra_list_spinlock);

		अगर (!mwअगरiex_is_ralist_valid(priv, pra_list, ptrindex)) अणु
			spin_unlock_bh(&priv->wmm.ra_list_spinlock);
			वापस -1;
		पूर्ण

		अगर (skb_tailroom(skb_aggr) < pad) अणु
			pad = 0;
			अवरोध;
		पूर्ण
		skb_put(skb_aggr, pad);

		skb_src = skb_peek(&pra_list->skb_head);

	पूर्ण जबतक (skb_src);

	spin_unlock_bh(&priv->wmm.ra_list_spinlock);

	/* Last AMSDU packet करोes not need padding */
	skb_trim(skb_aggr, skb_aggr->len - pad);

	/* Form AMSDU */
	mwअगरiex_11n_क्रमm_amsdu_txpd(priv, skb_aggr);
	अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA)
		ptx_pd = (काष्ठा txpd *)skb_aggr->data;

	skb_push(skb_aggr, headroom);
	tx_info_aggr->aggr_num = aggr_num * 2;
	अगर (adapter->data_sent || adapter->tx_lock_flag) अणु
		atomic_add(aggr_num * 2, &adapter->tx_queued);
		skb_queue_tail(&adapter->tx_data_q, skb_aggr);
		वापस 0;
	पूर्ण

	अगर (skb_src)
		tx_param.next_pkt_len = skb_src->len + माप(काष्ठा txpd);
	अन्यथा
		tx_param.next_pkt_len = 0;

	अगर (adapter->अगरace_type == MWIFIEX_USB) अणु
		ret = adapter->अगर_ops.host_to_card(adapter, priv->usb_port,
						   skb_aggr, &tx_param);
	पूर्ण अन्यथा अणु

		ret = adapter->अगर_ops.host_to_card(adapter, MWIFIEX_TYPE_DATA,
						   skb_aggr, &tx_param);
	पूर्ण
	चयन (ret) अणु
	हाल -EBUSY:
		spin_lock_bh(&priv->wmm.ra_list_spinlock);
		अगर (!mwअगरiex_is_ralist_valid(priv, pra_list, ptrindex)) अणु
			spin_unlock_bh(&priv->wmm.ra_list_spinlock);
			mwअगरiex_ग_लिखो_data_complete(adapter, skb_aggr, 1, -1);
			वापस -1;
		पूर्ण
		अगर (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_STA &&
		    adapter->pps_uapsd_mode && adapter->tx_lock_flag) अणु
				priv->adapter->tx_lock_flag = false;
				अगर (ptx_pd)
					ptx_pd->flags = 0;
		पूर्ण

		skb_queue_tail(&pra_list->skb_head, skb_aggr);

		pra_list->total_pkt_count++;

		atomic_inc(&priv->wmm.tx_pkts_queued);

		tx_info_aggr->flags |= MWIFIEX_BUF_FLAG_REQUEUED_PKT;
		spin_unlock_bh(&priv->wmm.ra_list_spinlock);
		mwअगरiex_dbg(adapter, ERROR, "data: -EBUSY is returned\n");
		अवरोध;
	हाल -1:
		mwअगरiex_dbg(adapter, ERROR, "%s: host_to_card failed: %#x\n",
			    __func__, ret);
		adapter->dbg.num_tx_host_to_card_failure++;
		mwअगरiex_ग_लिखो_data_complete(adapter, skb_aggr, 1, ret);
		वापस 0;
	हाल -EINPROGRESS:
		अवरोध;
	हाल 0:
		mwअगरiex_ग_लिखो_data_complete(adapter, skb_aggr, 1, ret);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (ret != -EBUSY) अणु
		mwअगरiex_rotate_priolists(priv, pra_list, ptrindex);
	पूर्ण

	वापस 0;
पूर्ण
