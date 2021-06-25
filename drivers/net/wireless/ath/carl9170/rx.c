<शैली गुरु>
/*
 * Atheros CARL9170 driver
 *
 * 802.11 & command trap routines
 *
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2009, 2010, Christian Lamparter <chunkeey@googlemail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, see
 * http://www.gnu.org/licenses/.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *    Copyright (c) 2007-2008 Atheros Communications, Inc.
 *
 *    Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/crc32.h>
#समावेश <net/mac80211.h>
#समावेश "carl9170.h"
#समावेश "hw.h"
#समावेश "cmd.h"

अटल व्योम carl9170_dbg_message(काष्ठा ar9170 *ar, स्थिर अक्षर *buf, u32 len)
अणु
	bool restart = false;
	क्रमागत carl9170_restart_reasons reason = CARL9170_RR_NO_REASON;

	अगर (len > 3) अणु
		अगर (स_भेद(buf, CARL9170_ERR_MAGIC, 3) == 0) अणु
			ar->fw.err_counter++;
			अगर (ar->fw.err_counter > 3) अणु
				restart = true;
				reason = CARL9170_RR_TOO_MANY_FIRMWARE_ERRORS;
			पूर्ण
		पूर्ण

		अगर (स_भेद(buf, CARL9170_BUG_MAGIC, 3) == 0) अणु
			ar->fw.bug_counter++;
			restart = true;
			reason = CARL9170_RR_FATAL_FIRMWARE_ERROR;
		पूर्ण
	पूर्ण

	wiphy_info(ar->hw->wiphy, "FW: %.*s\n", len, buf);

	अगर (restart)
		carl9170_restart(ar, reason);
पूर्ण

अटल व्योम carl9170_handle_ps(काष्ठा ar9170 *ar, काष्ठा carl9170_rsp *rsp)
अणु
	u32 ps;
	bool new_ps;

	ps = le32_to_cpu(rsp->psm.state);

	new_ps = (ps & CARL9170_PSM_COUNTER) != CARL9170_PSM_WAKE;
	अगर (ar->ps.state != new_ps) अणु
		अगर (!new_ps) अणु
			ar->ps.sleep_ms = jअगरfies_to_msecs(jअगरfies -
				ar->ps.last_action);
		पूर्ण

		ar->ps.last_action = jअगरfies;

		ar->ps.state = new_ps;
	पूर्ण
पूर्ण

अटल पूर्णांक carl9170_check_sequence(काष्ठा ar9170 *ar, अचिन्हित पूर्णांक seq)
अणु
	अगर (ar->cmd_seq < -1)
		वापस 0;

	/*
	 * Initialize Counter
	 */
	अगर (ar->cmd_seq < 0)
		ar->cmd_seq = seq;

	/*
	 * The sequence is strictly monotonic increasing and it never skips!
	 *
	 * Thereक्रमe we can safely assume that whenever we received an
	 * unexpected sequence we have lost some valuable data.
	 */
	अगर (seq != ar->cmd_seq) अणु
		पूर्णांक count;

		count = (seq - ar->cmd_seq) % ar->fw.cmd_bufs;

		wiphy_err(ar->hw->wiphy, "lost %d command responses/traps! "
			  "w:%d g:%d\n", count, ar->cmd_seq, seq);

		carl9170_restart(ar, CARL9170_RR_LOST_RSP);
		वापस -EIO;
	पूर्ण

	ar->cmd_seq = (ar->cmd_seq + 1) % ar->fw.cmd_bufs;
	वापस 0;
पूर्ण

अटल व्योम carl9170_cmd_callback(काष्ठा ar9170 *ar, u32 len, व्योम *buffer)
अणु
	/*
	 * Some commands may have a variable response length
	 * and we cannot predict the correct length in advance.
	 * So we only check अगर we provided enough space क्रम the data.
	 */
	अगर (unlikely(ar->पढ़ोlen != (len - 4))) अणु
		dev_warn(&ar->udev->dev, "received invalid command response:"
			 "got %d, instead of %d\n", len - 4, ar->पढ़ोlen);
		prपूर्णांक_hex_dump_bytes("carl9170 cmd:", DUMP_PREFIX_OFFSET,
			ar->cmd_buf, (ar->cmd.hdr.len + 4) & 0x3f);
		prपूर्णांक_hex_dump_bytes("carl9170 rsp:", DUMP_PREFIX_OFFSET,
			buffer, len);
		/*
		 * Do not complete. The command बार out,
		 * and we get a stack trace from there.
		 */
		carl9170_restart(ar, CARL9170_RR_INVALID_RSP);
	पूर्ण

	spin_lock(&ar->cmd_lock);
	अगर (ar->पढ़ोbuf) अणु
		अगर (len >= 4)
			स_नकल(ar->पढ़ोbuf, buffer + 4, len - 4);

		ar->पढ़ोbuf = शून्य;
	पूर्ण
	complete(&ar->cmd_रुको);
	spin_unlock(&ar->cmd_lock);
पूर्ण

व्योम carl9170_handle_command_response(काष्ठा ar9170 *ar, व्योम *buf, u32 len)
अणु
	काष्ठा carl9170_rsp *cmd = buf;
	काष्ठा ieee80211_vअगर *vअगर;

	अगर ((cmd->hdr.cmd & CARL9170_RSP_FLAG) != CARL9170_RSP_FLAG) अणु
		अगर (!(cmd->hdr.cmd & CARL9170_CMD_ASYNC_FLAG))
			carl9170_cmd_callback(ar, len, buf);

		वापस;
	पूर्ण

	अगर (unlikely(cmd->hdr.len != (len - 4))) अणु
		अगर (net_ratelimit()) अणु
			wiphy_err(ar->hw->wiphy, "FW: received over-/under"
				"sized event %x (%d, but should be %d).\n",
			       cmd->hdr.cmd, cmd->hdr.len, len - 4);

			prपूर्णांक_hex_dump_bytes("dump:", DUMP_PREFIX_NONE,
					     buf, len);
		पूर्ण

		वापस;
	पूर्ण

	/* hardware event handlers */
	चयन (cmd->hdr.cmd) अणु
	हाल CARL9170_RSP_PRETBTT:
		/* pre-TBTT event */
		rcu_पढ़ो_lock();
		vअगर = carl9170_get_मुख्य_vअगर(ar);

		अगर (!vअगर) अणु
			rcu_पढ़ो_unlock();
			अवरोध;
		पूर्ण

		चयन (vअगर->type) अणु
		हाल NL80211_IFTYPE_STATION:
			carl9170_handle_ps(ar, cmd);
			अवरोध;

		हाल NL80211_IFTYPE_AP:
		हाल NL80211_IFTYPE_ADHOC:
		हाल NL80211_IFTYPE_MESH_POINT:
			carl9170_update_beacon(ar, true);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		rcu_पढ़ो_unlock();

		अवरोध;


	हाल CARL9170_RSP_TXCOMP:
		/* TX status notअगरication */
		carl9170_tx_process_status(ar, cmd);
		अवरोध;

	हाल CARL9170_RSP_BEACON_CONFIG:
		/*
		 * (IBSS) beacon send notअगरication
		 * bytes: 04 c2 XX YY B4 B3 B2 B1
		 *
		 * XX always 80
		 * YY always 00
		 * B1-B4 "should" be the number of send out beacons.
		 */
		अवरोध;

	हाल CARL9170_RSP_ATIM:
		/* End of Atim Winकरोw */
		अवरोध;

	हाल CARL9170_RSP_WATCHDOG:
		/* Watchकरोg Interrupt */
		carl9170_restart(ar, CARL9170_RR_WATCHDOG);
		अवरोध;

	हाल CARL9170_RSP_TEXT:
		/* firmware debug */
		carl9170_dbg_message(ar, (अक्षर *)buf + 4, len - 4);
		अवरोध;

	हाल CARL9170_RSP_HEXDUMP:
		wiphy_dbg(ar->hw->wiphy, "FW: HD %d\n", len - 4);
		prपूर्णांक_hex_dump_bytes("FW:", DUMP_PREFIX_NONE,
				     (अक्षर *)buf + 4, len - 4);
		अवरोध;

	हाल CARL9170_RSP_RADAR:
		अगर (!net_ratelimit())
			अवरोध;

		wiphy_info(ar->hw->wiphy, "FW: RADAR! Please report this "
		       "incident to linux-wireless@vger.kernel.org !\n");
		अवरोध;

	हाल CARL9170_RSP_GPIO:
#अगर_घोषित CONFIG_CARL9170_WPC
		अगर (ar->wps.pbc) अणु
			bool state = !!(cmd->gpio.gpio & cpu_to_le32(
				AR9170_GPIO_PORT_WPS_BUTTON_PRESSED));

			अगर (state != ar->wps.pbc_state) अणु
				ar->wps.pbc_state = state;
				input_report_key(ar->wps.pbc, KEY_WPS_BUTTON,
						 state);
				input_sync(ar->wps.pbc);
			पूर्ण
		पूर्ण
#पूर्ण_अगर /* CONFIG_CARL9170_WPC */
		अवरोध;

	हाल CARL9170_RSP_BOOT:
		complete(&ar->fw_boot_रुको);
		अवरोध;

	शेष:
		wiphy_err(ar->hw->wiphy, "FW: received unhandled event %x\n",
			cmd->hdr.cmd);
		prपूर्णांक_hex_dump_bytes("dump:", DUMP_PREFIX_NONE, buf, len);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक carl9170_rx_mac_status(काष्ठा ar9170 *ar,
	काष्ठा ar9170_rx_head *head, काष्ठा ar9170_rx_macstatus *mac,
	काष्ठा ieee80211_rx_status *status)
अणु
	काष्ठा ieee80211_channel *chan;
	u8 error, decrypt;

	BUILD_BUG_ON(माप(काष्ठा ar9170_rx_head) != 12);
	BUILD_BUG_ON(माप(काष्ठा ar9170_rx_macstatus) != 4);

	error = mac->error;

	अगर (error & AR9170_RX_ERROR_WRONG_RA) अणु
		अगर (!ar->snअगरfer_enabled)
			वापस -EINVAL;
	पूर्ण

	अगर (error & AR9170_RX_ERROR_PLCP) अणु
		अगर (!(ar->filter_state & FIF_PLCPFAIL))
			वापस -EINVAL;

		status->flag |= RX_FLAG_FAILED_PLCP_CRC;
	पूर्ण

	अगर (error & AR9170_RX_ERROR_FCS) अणु
		ar->tx_fcs_errors++;

		अगर (!(ar->filter_state & FIF_FCSFAIL))
			वापस -EINVAL;

		status->flag |= RX_FLAG_FAILED_FCS_CRC;
	पूर्ण

	decrypt = ar9170_get_decrypt_type(mac);
	अगर (!(decrypt & AR9170_RX_ENC_SOFTWARE) &&
	    decrypt != AR9170_ENC_ALG_NONE) अणु
		अगर ((decrypt == AR9170_ENC_ALG_TKIP) &&
		    (error & AR9170_RX_ERROR_MMIC))
			status->flag |= RX_FLAG_MMIC_ERROR;

		status->flag |= RX_FLAG_DECRYPTED;
	पूर्ण

	अगर (error & AR9170_RX_ERROR_DECRYPT && !ar->snअगरfer_enabled)
		वापस -ENODATA;

	error &= ~(AR9170_RX_ERROR_MMIC |
		   AR9170_RX_ERROR_FCS |
		   AR9170_RX_ERROR_WRONG_RA |
		   AR9170_RX_ERROR_DECRYPT |
		   AR9170_RX_ERROR_PLCP);

	/* drop any other error frames */
	अगर (unlikely(error)) अणु
		/* TODO: update netdevice's RX dropped/errors statistics */

		अगर (net_ratelimit())
			wiphy_dbg(ar->hw->wiphy, "received frame with "
			       "suspicious error code (%#x).\n", error);

		वापस -EINVAL;
	पूर्ण

	chan = ar->channel;
	अगर (chan) अणु
		status->band = chan->band;
		status->freq = chan->center_freq;
	पूर्ण

	चयन (mac->status & AR9170_RX_STATUS_MODULATION) अणु
	हाल AR9170_RX_STATUS_MODULATION_CCK:
		अगर (mac->status & AR9170_RX_STATUS_SHORT_PREAMBLE)
			status->enc_flags |= RX_ENC_FLAG_SHORTPRE;
		चयन (head->plcp[0]) अणु
		हाल AR9170_RX_PHY_RATE_CCK_1M:
			status->rate_idx = 0;
			अवरोध;
		हाल AR9170_RX_PHY_RATE_CCK_2M:
			status->rate_idx = 1;
			अवरोध;
		हाल AR9170_RX_PHY_RATE_CCK_5M:
			status->rate_idx = 2;
			अवरोध;
		हाल AR9170_RX_PHY_RATE_CCK_11M:
			status->rate_idx = 3;
			अवरोध;
		शेष:
			अगर (net_ratelimit()) अणु
				wiphy_err(ar->hw->wiphy, "invalid plcp cck "
				       "rate (%x).\n", head->plcp[0]);
			पूर्ण

			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल AR9170_RX_STATUS_MODULATION_DUPOFDM:
	हाल AR9170_RX_STATUS_MODULATION_OFDM:
		चयन (head->plcp[0] & 0xf) अणु
		हाल AR9170_TXRX_PHY_RATE_OFDM_6M:
			status->rate_idx = 0;
			अवरोध;
		हाल AR9170_TXRX_PHY_RATE_OFDM_9M:
			status->rate_idx = 1;
			अवरोध;
		हाल AR9170_TXRX_PHY_RATE_OFDM_12M:
			status->rate_idx = 2;
			अवरोध;
		हाल AR9170_TXRX_PHY_RATE_OFDM_18M:
			status->rate_idx = 3;
			अवरोध;
		हाल AR9170_TXRX_PHY_RATE_OFDM_24M:
			status->rate_idx = 4;
			अवरोध;
		हाल AR9170_TXRX_PHY_RATE_OFDM_36M:
			status->rate_idx = 5;
			अवरोध;
		हाल AR9170_TXRX_PHY_RATE_OFDM_48M:
			status->rate_idx = 6;
			अवरोध;
		हाल AR9170_TXRX_PHY_RATE_OFDM_54M:
			status->rate_idx = 7;
			अवरोध;
		शेष:
			अगर (net_ratelimit()) अणु
				wiphy_err(ar->hw->wiphy, "invalid plcp ofdm "
					"rate (%x).\n", head->plcp[0]);
			पूर्ण

			वापस -EINVAL;
		पूर्ण
		अगर (status->band == NL80211_BAND_2GHZ)
			status->rate_idx += 4;
		अवरोध;

	हाल AR9170_RX_STATUS_MODULATION_HT:
		अगर (head->plcp[3] & 0x80)
			status->bw = RATE_INFO_BW_40;
		अगर (head->plcp[6] & 0x80)
			status->enc_flags |= RX_ENC_FLAG_SHORT_GI;

		status->rate_idx = clamp(head->plcp[3] & 0x7f, 0, 75);
		status->encoding = RX_ENC_HT;
		अवरोध;

	शेष:
		BUG();
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम carl9170_rx_phy_status(काष्ठा ar9170 *ar,
	काष्ठा ar9170_rx_phystatus *phy, काष्ठा ieee80211_rx_status *status)
अणु
	पूर्णांक i;

	BUILD_BUG_ON(माप(काष्ठा ar9170_rx_phystatus) != 20);

	क्रम (i = 0; i < 3; i++)
		अगर (phy->rssi[i] != 0x80)
			status->antenna |= BIT(i);

	/* post-process RSSI */
	क्रम (i = 0; i < 7; i++)
		अगर (phy->rssi[i] & 0x80)
			phy->rssi[i] = ((~phy->rssi[i] & 0x7f) + 1) & 0x7f;

	/* TODO: we could करो something with phy_errors */
	status->संकेत = ar->noise[0] + phy->rssi_combined;
पूर्ण

अटल काष्ठा sk_buff *carl9170_rx_copy_data(u8 *buf, पूर्णांक len)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक reserved = 0;
	काष्ठा ieee80211_hdr *hdr = (व्योम *) buf;

	अगर (ieee80211_is_data_qos(hdr->frame_control)) अणु
		u8 *qc = ieee80211_get_qos_ctl(hdr);
		reserved += NET_IP_ALIGN;

		अगर (*qc & IEEE80211_QOS_CTL_A_MSDU_PRESENT)
			reserved += NET_IP_ALIGN;
	पूर्ण

	अगर (ieee80211_has_a4(hdr->frame_control))
		reserved += NET_IP_ALIGN;

	reserved = 32 + (reserved & NET_IP_ALIGN);

	skb = dev_alloc_skb(len + reserved);
	अगर (likely(skb)) अणु
		skb_reserve(skb, reserved);
		skb_put_data(skb, buf, len);
	पूर्ण

	वापस skb;
पूर्ण

अटल u8 *carl9170_find_ie(u8 *data, अचिन्हित पूर्णांक len, u8 ie)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)data;
	u8 *pos, *end;

	pos = (u8 *)mgmt->u.beacon.variable;
	end = data + len;
	जबतक (pos < end) अणु
		अगर (pos + 2 + pos[1] > end)
			वापस शून्य;

		अगर (pos[0] == ie)
			वापस pos;

		pos += 2 + pos[1];
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * NOTE:
 *
 * The firmware is in अक्षरge of waking up the device just beक्रमe
 * the AP is expected to transmit the next beacon.
 *
 * This leaves the driver with the important task of deciding when
 * to set the PHY back to bed again.
 */
अटल व्योम carl9170_ps_beacon(काष्ठा ar9170 *ar, व्योम *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ieee80211_hdr *hdr = data;
	काष्ठा ieee80211_tim_ie *tim_ie;
	काष्ठा ath_common *common = &ar->common;
	u8 *tim;
	u8 tim_len;
	bool cam;

	अगर (likely(!(ar->hw->conf.flags & IEEE80211_CONF_PS)))
		वापस;

	/* min. beacon length + FCS_LEN */
	अगर (len <= 40 + FCS_LEN)
		वापस;

	/* check अगर this really is a beacon */
	/* and only beacons from the associated BSSID, please */
	अगर (!ath_is_mybeacon(common, hdr) || !common->curaid)
		वापस;

	ar->ps.last_beacon = jअगरfies;

	tim = carl9170_find_ie(data, len - FCS_LEN, WLAN_EID_TIM);
	अगर (!tim)
		वापस;

	अगर (tim[1] < माप(*tim_ie))
		वापस;

	tim_len = tim[1];
	tim_ie = (काष्ठा ieee80211_tim_ie *) &tim[2];

	अगर (!WARN_ON_ONCE(!ar->hw->conf.ps_dtim_period))
		ar->ps.dtim_counter = (tim_ie->dtim_count - 1) %
			ar->hw->conf.ps_dtim_period;

	/* Check whenever the PHY can be turned off again. */

	/* 1. What about buffered unicast traffic क्रम our AID? */
	cam = ieee80211_check_tim(tim_ie, tim_len, ar->common.curaid);

	/* 2. Maybe the AP wants to send multicast/broadcast data? */
	cam |= !!(tim_ie->biपंचांगap_ctrl & 0x01);

	अगर (!cam) अणु
		/* back to low-घातer land. */
		ar->ps.off_override &= ~PS_OFF_BCN;
		carl9170_ps_check(ar);
	पूर्ण अन्यथा अणु
		/* क्रमce CAM */
		ar->ps.off_override |= PS_OFF_BCN;
	पूर्ण
पूर्ण

अटल व्योम carl9170_ba_check(काष्ठा ar9170 *ar, व्योम *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ieee80211_bar *bar = data;
	काष्ठा carl9170_bar_list_entry *entry;
	अचिन्हित पूर्णांक queue;

	अगर (likely(!ieee80211_is_back(bar->frame_control)))
		वापस;

	अगर (len <= माप(*bar) + FCS_LEN)
		वापस;

	queue = TID_TO_WME_AC(((le16_to_cpu(bar->control) &
		IEEE80211_BAR_CTRL_TID_INFO_MASK) >>
		IEEE80211_BAR_CTRL_TID_INFO_SHIFT) & 7);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(entry, &ar->bar_list[queue], list) अणु
		काष्ठा sk_buff *entry_skb = entry->skb;
		काष्ठा _carl9170_tx_superframe *super = (व्योम *)entry_skb->data;
		काष्ठा ieee80211_bar *entry_bar = (व्योम *)super->frame_data;

#घोषणा TID_CHECK(a, b) (						\
	((a) & cpu_to_le16(IEEE80211_BAR_CTRL_TID_INFO_MASK)) ==	\
	((b) & cpu_to_le16(IEEE80211_BAR_CTRL_TID_INFO_MASK)))		\

		अगर (bar->start_seq_num == entry_bar->start_seq_num &&
		    TID_CHECK(bar->control, entry_bar->control) &&
		    ether_addr_equal_64bits(bar->ra, entry_bar->ta) &&
		    ether_addr_equal_64bits(bar->ta, entry_bar->ra)) अणु
			काष्ठा ieee80211_tx_info *tx_info;

			tx_info = IEEE80211_SKB_CB(entry_skb);
			tx_info->flags |= IEEE80211_TX_STAT_ACK;

			spin_lock_bh(&ar->bar_list_lock[queue]);
			list_del_rcu(&entry->list);
			spin_unlock_bh(&ar->bar_list_lock[queue]);
			kमुक्त_rcu(entry, head);
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

#अघोषित TID_CHECK
पूर्ण

अटल bool carl9170_ampdu_check(काष्ठा ar9170 *ar, u8 *buf, u8 ms,
				 काष्ठा ieee80211_rx_status *rx_status)
अणु
	__le16 fc;

	अगर ((ms & AR9170_RX_STATUS_MPDU) == AR9170_RX_STATUS_MPDU_SINGLE) अणु
		/*
		 * This frame is not part of an aMPDU.
		 * Thereक्रमe it is not subjected to any
		 * of the following content restrictions.
		 */
		वापस true;
	पूर्ण

	rx_status->flag |= RX_FLAG_AMPDU_DETAILS | RX_FLAG_AMPDU_LAST_KNOWN;
	rx_status->ampdu_reference = ar->ampdu_ref;

	/*
	 * "802.11n - 7.4a.3 A-MPDU contents" describes in which contexts
	 * certain frame types can be part of an aMPDU.
	 *
	 * In order to keep the processing cost करोwn, I opted क्रम a
	 * stateless filter solely based on the frame control field.
	 */

	fc = ((काष्ठा ieee80211_hdr *)buf)->frame_control;
	अगर (ieee80211_is_data_qos(fc) && ieee80211_is_data_present(fc))
		वापस true;

	अगर (ieee80211_is_ack(fc) || ieee80211_is_back(fc) ||
	    ieee80211_is_back_req(fc))
		वापस true;

	अगर (ieee80211_is_action(fc))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक carl9170_handle_mpdu(काष्ठा ar9170 *ar, u8 *buf, पूर्णांक len,
				काष्ठा ieee80211_rx_status *status)
अणु
	काष्ठा sk_buff *skb;

	/* (driver) frame trap handler
	 *
	 * Because घातer-saving mode handing has to be implemented by
	 * the driver/firmware. We have to check each incoming beacon
	 * from the associated AP, अगर there's new data क्रम us (either
	 * broadcast/multicast or unicast) we have to react quickly.
	 *
	 * So, अगर you have you want to add additional frame trap
	 * handlers, this would be the perfect place!
	 */

	carl9170_ps_beacon(ar, buf, len);

	carl9170_ba_check(ar, buf, len);

	skb = carl9170_rx_copy_data(buf, len);
	अगर (!skb)
		वापस -ENOMEM;

	स_नकल(IEEE80211_SKB_RXCB(skb), status, माप(*status));
	ieee80211_rx(ar->hw, skb);
	वापस 0;
पूर्ण

/*
 * If the frame alignment is right (or the kernel has
 * CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS), and there
 * is only a single MPDU in the USB frame, then we could
 * submit to mac80211 the SKB directly. However, since
 * there may be multiple packets in one SKB in stream
 * mode, and we need to observe the proper ordering,
 * this is non-trivial.
 */
अटल व्योम carl9170_rx_untie_data(काष्ठा ar9170 *ar, u8 *buf, पूर्णांक len)
अणु
	काष्ठा ar9170_rx_head *head;
	काष्ठा ar9170_rx_macstatus *mac;
	काष्ठा ar9170_rx_phystatus *phy = शून्य;
	काष्ठा ieee80211_rx_status status;
	पूर्णांक mpdu_len;
	u8 mac_status;

	अगर (!IS_STARTED(ar))
		वापस;

	अगर (unlikely(len < माप(*mac)))
		जाओ drop;

	स_रखो(&status, 0, माप(status));

	mpdu_len = len - माप(*mac);

	mac = (व्योम *)(buf + mpdu_len);
	mac_status = mac->status;
	चयन (mac_status & AR9170_RX_STATUS_MPDU) अणु
	हाल AR9170_RX_STATUS_MPDU_FIRST:
		ar->ampdu_ref++;
		/* Aggregated MPDUs start with an PLCP header */
		अगर (likely(mpdu_len >= माप(काष्ठा ar9170_rx_head))) अणु
			head = (व्योम *) buf;

			/*
			 * The PLCP header needs to be cached क्रम the
			 * following MIDDLE + LAST A-MPDU packets.
			 *
			 * So, अगर you are wondering why all frames seem
			 * to share a common RX status inक्रमmation,
			 * then you have the answer right here...
			 */
			स_नकल(&ar->rx_plcp, (व्योम *) buf,
			       माप(काष्ठा ar9170_rx_head));

			mpdu_len -= माप(काष्ठा ar9170_rx_head);
			buf += माप(काष्ठा ar9170_rx_head);

			ar->rx_has_plcp = true;
		पूर्ण अन्यथा अणु
			अगर (net_ratelimit()) अणु
				wiphy_err(ar->hw->wiphy, "plcp info "
					"is clipped.\n");
			पूर्ण

			जाओ drop;
		पूर्ण
		अवरोध;

	हाल AR9170_RX_STATUS_MPDU_LAST:
		status.flag |= RX_FLAG_AMPDU_IS_LAST;

		/*
		 * The last frame of an A-MPDU has an extra tail
		 * which करोes contain the phy status of the whole
		 * aggregate.
		 */
		अगर (likely(mpdu_len >= माप(काष्ठा ar9170_rx_phystatus))) अणु
			mpdu_len -= माप(काष्ठा ar9170_rx_phystatus);
			phy = (व्योम *)(buf + mpdu_len);
		पूर्ण अन्यथा अणु
			अगर (net_ratelimit()) अणु
				wiphy_err(ar->hw->wiphy, "frame tail "
					"is clipped.\n");
			पूर्ण

			जाओ drop;
		पूर्ण
		fallthrough;

	हाल AR9170_RX_STATUS_MPDU_MIDDLE:
		/*  These are just data + mac status */
		अगर (unlikely(!ar->rx_has_plcp)) अणु
			अगर (!net_ratelimit())
				वापस;

			wiphy_err(ar->hw->wiphy, "rx stream does not start "
					"with a first_mpdu frame tag.\n");

			जाओ drop;
		पूर्ण

		head = &ar->rx_plcp;
		अवरोध;

	हाल AR9170_RX_STATUS_MPDU_SINGLE:
		/* single mpdu has both: plcp (head) and phy status (tail) */
		head = (व्योम *) buf;

		mpdu_len -= माप(काष्ठा ar9170_rx_head);
		mpdu_len -= माप(काष्ठा ar9170_rx_phystatus);

		buf += माप(काष्ठा ar9170_rx_head);
		phy = (व्योम *)(buf + mpdu_len);
		अवरोध;

	शेष:
		BUG();
		अवरोध;
	पूर्ण

	/* FC + DU + RA + FCS */
	अगर (unlikely(mpdu_len < (2 + 2 + ETH_ALEN + FCS_LEN)))
		जाओ drop;

	अगर (unlikely(carl9170_rx_mac_status(ar, head, mac, &status)))
		जाओ drop;

	अगर (!carl9170_ampdu_check(ar, buf, mac_status, &status))
		जाओ drop;

	अगर (phy)
		carl9170_rx_phy_status(ar, phy, &status);
	अन्यथा
		status.flag |= RX_FLAG_NO_SIGNAL_VAL;

	अगर (carl9170_handle_mpdu(ar, buf, mpdu_len, &status))
		जाओ drop;

	वापस;
drop:
	ar->rx_dropped++;
पूर्ण

अटल व्योम carl9170_rx_untie_cmds(काष्ठा ar9170 *ar, स्थिर u8 *respbuf,
				   स्थिर अचिन्हित पूर्णांक resplen)
अणु
	काष्ठा carl9170_rsp *cmd;
	पूर्णांक i = 0;

	जबतक (i < resplen) अणु
		cmd = (व्योम *) &respbuf[i];

		i += cmd->hdr.len + 4;
		अगर (unlikely(i > resplen))
			अवरोध;

		अगर (carl9170_check_sequence(ar, cmd->hdr.seq))
			अवरोध;

		carl9170_handle_command_response(ar, cmd, cmd->hdr.len + 4);
	पूर्ण

	अगर (unlikely(i != resplen)) अणु
		अगर (!net_ratelimit())
			वापस;

		wiphy_err(ar->hw->wiphy, "malformed firmware trap:\n");
		prपूर्णांक_hex_dump_bytes("rxcmd:", DUMP_PREFIX_OFFSET,
				     respbuf, resplen);
	पूर्ण
पूर्ण

अटल व्योम __carl9170_rx(काष्ठा ar9170 *ar, u8 *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i = 0;

	/* weird thing, but this is the same in the original driver */
	जबतक (len > 2 && i < 12 && buf[0] == 0xff && buf[1] == 0xff) अणु
		i += 2;
		len -= 2;
		buf += 2;
	पूर्ण

	अगर (unlikely(len < 4))
		वापस;

	/* found the 6 * 0xffff marker? */
	अगर (i == 12)
		carl9170_rx_untie_cmds(ar, buf, len);
	अन्यथा
		carl9170_rx_untie_data(ar, buf, len);
पूर्ण

अटल व्योम carl9170_rx_stream(काष्ठा ar9170 *ar, व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक tlen, wlen = 0, clen = 0;
	काष्ठा ar9170_stream *rx_stream;
	u8 *tbuf;

	tbuf = buf;
	tlen = len;

	जबतक (tlen >= 4) अणु
		rx_stream = (व्योम *) tbuf;
		clen = le16_to_cpu(rx_stream->length);
		wlen = ALIGN(clen, 4);

		/* check अगर this is stream has a valid tag.*/
		अगर (rx_stream->tag != cpu_to_le16(AR9170_RX_STREAM_TAG)) अणु
			/*
			 * TODO: handle the highly unlikely event that the
			 * corrupted stream has the TAG at the right position.
			 */

			/* check अगर the frame can be repaired. */
			अगर (!ar->rx_failover_missing) अणु

				/* this is not "short read". */
				अगर (net_ratelimit()) अणु
					wiphy_err(ar->hw->wiphy,
						"missing tag!\n");
				पूर्ण

				__carl9170_rx(ar, tbuf, tlen);
				वापस;
			पूर्ण

			अगर (ar->rx_failover_missing > tlen) अणु
				अगर (net_ratelimit()) अणु
					wiphy_err(ar->hw->wiphy,
						"possible multi "
						"stream corruption!\n");
					जाओ err_telluser;
				पूर्ण अन्यथा अणु
					जाओ err_silent;
				पूर्ण
			पूर्ण

			skb_put_data(ar->rx_failover, tbuf, tlen);
			ar->rx_failover_missing -= tlen;

			अगर (ar->rx_failover_missing <= 0) अणु
				/*
				 * nested carl9170_rx_stream call!
				 *
				 * termination is guaranteed, even when the
				 * combined frame also have an element with
				 * a bad tag.
				 */

				ar->rx_failover_missing = 0;
				carl9170_rx_stream(ar, ar->rx_failover->data,
						   ar->rx_failover->len);

				skb_reset_tail_poपूर्णांकer(ar->rx_failover);
				skb_trim(ar->rx_failover, 0);
			पूर्ण

			वापस;
		पूर्ण

		/* check अगर stream is clipped */
		अगर (wlen > tlen - 4) अणु
			अगर (ar->rx_failover_missing) अणु
				/* TODO: handle द्विगुन stream corruption. */
				अगर (net_ratelimit()) अणु
					wiphy_err(ar->hw->wiphy, "double rx "
						"stream corruption!\n");
					जाओ err_telluser;
				पूर्ण अन्यथा अणु
					जाओ err_silent;
				पूर्ण
			पूर्ण

			/*
			 * save incomplete data set.
			 * the firmware will resend the missing bits when
			 * the rx - descriptor comes round again.
			 */

			skb_put_data(ar->rx_failover, tbuf, tlen);
			ar->rx_failover_missing = clen - tlen;
			वापस;
		पूर्ण
		__carl9170_rx(ar, rx_stream->payload, clen);

		tbuf += wlen + 4;
		tlen -= wlen + 4;
	पूर्ण

	अगर (tlen) अणु
		अगर (net_ratelimit()) अणु
			wiphy_err(ar->hw->wiphy, "%d bytes of unprocessed "
				"data left in rx stream!\n", tlen);
		पूर्ण

		जाओ err_telluser;
	पूर्ण

	वापस;

err_telluser:
	wiphy_err(ar->hw->wiphy, "damaged RX stream data [want:%d, "
		"data:%d, rx:%d, pending:%d ]\n", clen, wlen, tlen,
		ar->rx_failover_missing);

	अगर (ar->rx_failover_missing)
		prपूर्णांक_hex_dump_bytes("rxbuf:", DUMP_PREFIX_OFFSET,
				     ar->rx_failover->data,
				     ar->rx_failover->len);

	prपूर्णांक_hex_dump_bytes("stream:", DUMP_PREFIX_OFFSET,
			     buf, len);

	wiphy_err(ar->hw->wiphy, "please check your hardware and cables, if "
		"you see this message frequently.\n");

err_silent:
	अगर (ar->rx_failover_missing) अणु
		skb_reset_tail_poपूर्णांकer(ar->rx_failover);
		skb_trim(ar->rx_failover, 0);
		ar->rx_failover_missing = 0;
	पूर्ण
पूर्ण

व्योम carl9170_rx(काष्ठा ar9170 *ar, व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	अगर (ar->fw.rx_stream)
		carl9170_rx_stream(ar, buf, len);
	अन्यथा
		__carl9170_rx(ar, buf, len);
पूर्ण
