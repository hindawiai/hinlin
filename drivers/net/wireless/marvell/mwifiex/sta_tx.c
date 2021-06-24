<शैली गुरु>
/*
 * NXP Wireless LAN device driver: station TX data handling
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

/*
 * This function fills the TxPD क्रम tx packets.
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
व्योम *mwअगरiex_process_sta_txpd(काष्ठा mwअगरiex_निजी *priv,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा txpd *local_tx_pd;
	काष्ठा mwअगरiex_txinfo *tx_info = MWIFIEX_SKB_TXCB(skb);
	अचिन्हित पूर्णांक pad;
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

	pad = ((व्योम *)skb->data - (माप(*local_tx_pd) + hroom)-
			 शून्य) & (MWIFIEX_DMA_ALIGN_SZ - 1);
	skb_push(skb, माप(*local_tx_pd) + pad);

	local_tx_pd = (काष्ठा txpd *) skb->data;
	स_रखो(local_tx_pd, 0, माप(काष्ठा txpd));
	local_tx_pd->bss_num = priv->bss_num;
	local_tx_pd->bss_type = priv->bss_type;
	local_tx_pd->tx_pkt_length = cpu_to_le16((u16)(skb->len -
						       (माप(काष्ठा txpd) +
							pad)));

	local_tx_pd->priority = (u8) skb->priority;
	local_tx_pd->pkt_delay_2ms =
				mwअगरiex_wmm_compute_drv_pkt_delay(priv, skb);

	अगर (tx_info->flags & MWIFIEX_BUF_FLAG_EAPOL_TX_STATUS ||
	    tx_info->flags & MWIFIEX_BUF_FLAG_ACTION_TX_STATUS) अणु
		local_tx_pd->tx_token_id = tx_info->ack_frame_id;
		local_tx_pd->flags |= MWIFIEX_TXPD_FLAGS_REQ_TX_STATUS;
	पूर्ण

	अगर (local_tx_pd->priority <
	    ARRAY_SIZE(priv->wmm.user_pri_pkt_tx_ctrl))
		/*
		 * Set the priority specअगरic tx_control field, setting of 0 will
		 *   cause the शेष value to be used later in this function
		 */
		local_tx_pd->tx_control =
			cpu_to_le32(priv->wmm.user_pri_pkt_tx_ctrl[local_tx_pd->
								   priority]);

	अगर (adapter->pps_uapsd_mode) अणु
		अगर (mwअगरiex_check_last_packet_indication(priv)) अणु
			adapter->tx_lock_flag = true;
			local_tx_pd->flags =
				MWIFIEX_TxPD_POWER_MGMT_LAST_PACKET;
		पूर्ण
	पूर्ण

	अगर (tx_info->flags & MWIFIEX_BUF_FLAG_TDLS_PKT)
		local_tx_pd->flags |= MWIFIEX_TXPD_FLAGS_TDLS_PACKET;

	/* Offset of actual data */
	pkt_offset = माप(काष्ठा txpd) + pad;
	अगर (pkt_type == PKT_TYPE_MGMT) अणु
		/* Set the packet type and add header क्रम management frame */
		local_tx_pd->tx_pkt_type = cpu_to_le16(pkt_type);
		pkt_offset += MWIFIEX_MGMT_FRAME_HEADER_SIZE;
	पूर्ण

	local_tx_pd->tx_pkt_offset = cpu_to_le16(pkt_offset);

	/* make space क्रम adapter->पूर्णांकf_hdr_len */
	skb_push(skb, hroom);

	अगर (!local_tx_pd->tx_control)
		/* TxCtrl set by user or शेष */
		local_tx_pd->tx_control = cpu_to_le32(priv->pkt_tx_ctrl);

	वापस skb->data;
पूर्ण

/*
 * This function tells firmware to send a शून्य data packet.
 *
 * The function creates a शून्य data packet with TxPD and sends to the
 * firmware क्रम transmission, with highest priority setting.
 */
पूर्णांक mwअगरiex_send_null_packet(काष्ठा mwअगरiex_निजी *priv, u8 flags)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	काष्ठा txpd *local_tx_pd;
	काष्ठा mwअगरiex_tx_param tx_param;
/* माप(काष्ठा txpd) + Interface specअगरic header */
#घोषणा शून्य_PACKET_HDR 64
	u32 data_len = शून्य_PACKET_HDR;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;
	काष्ठा mwअगरiex_txinfo *tx_info = शून्य;

	अगर (test_bit(MWIFIEX_SURPRISE_REMOVED, &adapter->work_flags))
		वापस -1;

	अगर (!priv->media_connected)
		वापस -1;

	अगर (adapter->data_sent)
		वापस -1;

	अगर (adapter->अगर_ops.is_port_पढ़ोy &&
	    !adapter->अगर_ops.is_port_पढ़ोy(priv))
		वापस -1;

	skb = dev_alloc_skb(data_len);
	अगर (!skb)
		वापस -1;

	tx_info = MWIFIEX_SKB_TXCB(skb);
	स_रखो(tx_info, 0, माप(*tx_info));
	tx_info->bss_num = priv->bss_num;
	tx_info->bss_type = priv->bss_type;
	tx_info->pkt_len = data_len -
			(माप(काष्ठा txpd) + adapter->पूर्णांकf_hdr_len);
	skb_reserve(skb, माप(काष्ठा txpd) + adapter->पूर्णांकf_hdr_len);
	skb_push(skb, माप(काष्ठा txpd));

	local_tx_pd = (काष्ठा txpd *) skb->data;
	local_tx_pd->tx_control = cpu_to_le32(priv->pkt_tx_ctrl);
	local_tx_pd->flags = flags;
	local_tx_pd->priority = WMM_HIGHEST_PRIORITY;
	local_tx_pd->tx_pkt_offset = cpu_to_le16(माप(काष्ठा txpd));
	local_tx_pd->bss_num = priv->bss_num;
	local_tx_pd->bss_type = priv->bss_type;

	skb_push(skb, adapter->पूर्णांकf_hdr_len);
	अगर (adapter->अगरace_type == MWIFIEX_USB) अणु
		ret = adapter->अगर_ops.host_to_card(adapter, priv->usb_port,
						   skb, शून्य);
	पूर्ण अन्यथा अणु
		tx_param.next_pkt_len = 0;
		ret = adapter->अगर_ops.host_to_card(adapter, MWIFIEX_TYPE_DATA,
						   skb, &tx_param);
	पूर्ण
	चयन (ret) अणु
	हाल -EBUSY:
		dev_kमुक्त_skb_any(skb);
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: host_to_card failed: ret=%d\n",
			    __func__, ret);
		adapter->dbg.num_tx_host_to_card_failure++;
		अवरोध;
	हाल -1:
		dev_kमुक्त_skb_any(skb);
		mwअगरiex_dbg(adapter, ERROR,
			    "%s: host_to_card failed: ret=%d\n",
			    __func__, ret);
		adapter->dbg.num_tx_host_to_card_failure++;
		अवरोध;
	हाल 0:
		dev_kमुक्त_skb_any(skb);
		mwअगरiex_dbg(adapter, DATA,
			    "data: %s: host_to_card succeeded\n",
			    __func__);
		adapter->tx_lock_flag = true;
		अवरोध;
	हाल -EINPROGRESS:
		adapter->tx_lock_flag = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * This function checks अगर we need to send last packet indication.
 */
u8
mwअगरiex_check_last_packet_indication(काष्ठा mwअगरiex_निजी *priv)
अणु
	काष्ठा mwअगरiex_adapter *adapter = priv->adapter;
	u8 ret = false;

	अगर (!adapter->sleep_period.period)
		वापस ret;
	अगर (mwअगरiex_wmm_lists_empty(adapter))
			ret = true;

	अगर (ret && !adapter->cmd_sent && !adapter->curr_cmd &&
	    !is_command_pending(adapter)) अणु
		adapter->delay_null_pkt = false;
		ret = true;
	पूर्ण अन्यथा अणु
		ret = false;
		adapter->delay_null_pkt = true;
	पूर्ण
	वापस ret;
पूर्ण
