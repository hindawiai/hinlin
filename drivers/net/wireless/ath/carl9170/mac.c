<शैली गुरु>
/*
 * Atheros CARL9170 driver
 *
 * MAC programming
 *
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
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

#समावेश <यंत्र/unaligned.h>

#समावेश "carl9170.h"
#समावेश "cmd.h"

पूर्णांक carl9170_set_dyn_sअगरs_ack(काष्ठा ar9170 *ar)
अणु
	u32 val;

	अगर (conf_is_ht40(&ar->hw->conf))
		val = 0x010a;
	अन्यथा अणु
		अगर (ar->hw->conf.chandef.chan->band == NL80211_BAND_2GHZ)
			val = 0x105;
		अन्यथा
			val = 0x104;
	पूर्ण

	वापस carl9170_ग_लिखो_reg(ar, AR9170_MAC_REG_DYNAMIC_SIFS_ACK, val);
पूर्ण

पूर्णांक carl9170_set_rts_cts_rate(काष्ठा ar9170 *ar)
अणु
	u32 rts_rate, cts_rate;

	अगर (conf_is_ht(&ar->hw->conf)) अणु
		/* 12 mbit OFDM */
		rts_rate = 0x1da;
		cts_rate = 0x10a;
	पूर्ण अन्यथा अणु
		अगर (ar->hw->conf.chandef.chan->band == NL80211_BAND_2GHZ) अणु
			/* 11 mbit CCK */
			rts_rate = 033;
			cts_rate = 003;
		पूर्ण अन्यथा अणु
			/* 6 mbit OFDM */
			rts_rate = 0x1bb;
			cts_rate = 0x10b;
		पूर्ण
	पूर्ण

	वापस carl9170_ग_लिखो_reg(ar, AR9170_MAC_REG_RTS_CTS_RATE,
				  rts_rate | (cts_rate) << 16);
पूर्ण

पूर्णांक carl9170_set_slot_समय(काष्ठा ar9170 *ar)
अणु
	काष्ठा ieee80211_vअगर *vअगर;
	u32 slotसमय = 20;

	rcu_पढ़ो_lock();
	vअगर = carl9170_get_मुख्य_vअगर(ar);
	अगर (!vअगर) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	अगर ((ar->hw->conf.chandef.chan->band == NL80211_BAND_5GHZ) ||
	    vअगर->bss_conf.use_लघु_slot)
		slotसमय = 9;

	rcu_पढ़ो_unlock();

	वापस carl9170_ग_लिखो_reg(ar, AR9170_MAC_REG_SLOT_TIME,
				  slotसमय << 10);
पूर्ण

पूर्णांक carl9170_set_mac_rates(काष्ठा ar9170 *ar)
अणु
	काष्ठा ieee80211_vअगर *vअगर;
	u32 basic, mandatory;

	rcu_पढ़ो_lock();
	vअगर = carl9170_get_मुख्य_vअगर(ar);

	अगर (!vअगर) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	basic = (vअगर->bss_conf.basic_rates & 0xf);
	basic |= (vअगर->bss_conf.basic_rates & 0xff0) << 4;
	rcu_पढ़ो_unlock();

	अगर (ar->hw->conf.chandef.chan->band == NL80211_BAND_5GHZ)
		mandatory = 0xff00; /* OFDM 6/9/12/18/24/36/48/54 */
	अन्यथा
		mandatory = 0xff0f; /* OFDM (6/9../54) + CCK (1/2/5.5/11) */

	carl9170_regग_लिखो_begin(ar);
	carl9170_regग_लिखो(AR9170_MAC_REG_BASIC_RATE, basic);
	carl9170_regग_लिखो(AR9170_MAC_REG_MANDATORY_RATE, mandatory);
	carl9170_regग_लिखो_finish();

	वापस carl9170_regग_लिखो_result();
पूर्ण

पूर्णांक carl9170_set_qos(काष्ठा ar9170 *ar)
अणु
	carl9170_regग_लिखो_begin(ar);

	carl9170_regग_लिखो(AR9170_MAC_REG_AC0_CW, ar->edcf[0].cw_min |
			  (ar->edcf[0].cw_max << 16));
	carl9170_regग_लिखो(AR9170_MAC_REG_AC1_CW, ar->edcf[1].cw_min |
			  (ar->edcf[1].cw_max << 16));
	carl9170_regग_लिखो(AR9170_MAC_REG_AC2_CW, ar->edcf[2].cw_min |
			  (ar->edcf[2].cw_max << 16));
	carl9170_regग_लिखो(AR9170_MAC_REG_AC3_CW, ar->edcf[3].cw_min |
			  (ar->edcf[3].cw_max << 16));
	carl9170_regग_लिखो(AR9170_MAC_REG_AC4_CW, ar->edcf[4].cw_min |
			  (ar->edcf[4].cw_max << 16));

	carl9170_regग_लिखो(AR9170_MAC_REG_AC2_AC1_AC0_AIFS,
			  ((ar->edcf[0].aअगरs * 9 + 10)) |
			  ((ar->edcf[1].aअगरs * 9 + 10) << 12) |
			  ((ar->edcf[2].aअगरs * 9 + 10) << 24));
	carl9170_regग_लिखो(AR9170_MAC_REG_AC4_AC3_AC2_AIFS,
			  ((ar->edcf[2].aअगरs * 9 + 10) >> 8) |
			  ((ar->edcf[3].aअगरs * 9 + 10) << 4) |
			  ((ar->edcf[4].aअगरs * 9 + 10) << 16));

	carl9170_regग_लिखो(AR9170_MAC_REG_AC1_AC0_TXOP,
			  ar->edcf[0].txop | ar->edcf[1].txop << 16);
	carl9170_regग_लिखो(AR9170_MAC_REG_AC3_AC2_TXOP,
			  ar->edcf[2].txop | ar->edcf[3].txop << 16 |
			  ar->edcf[4].txop << 24);

	carl9170_regग_लिखो_finish();

	वापस carl9170_regग_लिखो_result();
पूर्ण

पूर्णांक carl9170_init_mac(काष्ठा ar9170 *ar)
अणु
	carl9170_regग_लिखो_begin(ar);

	/* चयन MAC to OTUS पूर्णांकerface */
	carl9170_regग_लिखो(0x1c3600, 0x3);

	carl9170_regग_लिखो(AR9170_MAC_REG_ACK_EXTENSION, 0x40);

	carl9170_regग_लिखो(AR9170_MAC_REG_RETRY_MAX, 0x0);

	carl9170_regग_लिखो(AR9170_MAC_REG_FRAMETYPE_FILTER,
			  AR9170_MAC_FTF_MONITOR);

	/* enable MMIC */
	carl9170_regग_लिखो(AR9170_MAC_REG_SNIFFER,
			AR9170_MAC_SNIFFER_DEFAULTS);

	carl9170_regग_लिखो(AR9170_MAC_REG_RX_THRESHOLD, 0xc1f80);

	carl9170_regग_लिखो(AR9170_MAC_REG_RX_PE_DELAY, 0x70);
	carl9170_regग_लिखो(AR9170_MAC_REG_EIFS_AND_SIFS, 0xa144000);
	carl9170_regग_लिखो(AR9170_MAC_REG_SLOT_TIME, 9 << 10);

	/* CF-END & CF-ACK rate => 24M OFDM */
	carl9170_regग_लिखो(AR9170_MAC_REG_TID_CFACK_CFEND_RATE, 0x59900000);

	/* NAV protects ACK only (in TXOP) */
	carl9170_regग_लिखो(AR9170_MAC_REG_TXOP_DURATION, 0x201);

	/* Set Beacon PHY CTRL's TPC to 0x7, TA1=1 */
	/* OTUS set AM to 0x1 */
	carl9170_regग_लिखो(AR9170_MAC_REG_BCN_HT1, 0x8000170);

	carl9170_regग_लिखो(AR9170_MAC_REG_BACKOFF_PROTECT, 0x105);

	/* Aggregation MAX number and समयout */
	carl9170_regग_लिखो(AR9170_MAC_REG_AMPDU_FACTOR, 0x8000a);
	carl9170_regग_लिखो(AR9170_MAC_REG_AMPDU_DENSITY, 0x140a07);

	carl9170_regग_लिखो(AR9170_MAC_REG_FRAMETYPE_FILTER,
			  AR9170_MAC_FTF_DEFAULTS);

	carl9170_regग_लिखो(AR9170_MAC_REG_RX_CONTROL,
			  AR9170_MAC_RX_CTRL_DEAGG |
			  AR9170_MAC_RX_CTRL_SHORT_FILTER);

	/* rate sets */
	carl9170_regग_लिखो(AR9170_MAC_REG_BASIC_RATE, 0x150f);
	carl9170_regग_लिखो(AR9170_MAC_REG_MANDATORY_RATE, 0x150f);
	carl9170_regग_लिखो(AR9170_MAC_REG_RTS_CTS_RATE, 0x0030033);

	/* MIMO response control */
	carl9170_regग_लिखो(AR9170_MAC_REG_ACK_TPC, 0x4003c1e);

	carl9170_regग_लिखो(AR9170_MAC_REG_AMPDU_RX_THRESH, 0xffff);

	/* set PHY रेजिस्टर पढ़ो समयout (??) */
	carl9170_regग_लिखो(AR9170_MAC_REG_MISC_680, 0xf00008);

	/* Disable Rx TimeOut, workaround क्रम BB. */
	carl9170_regग_लिखो(AR9170_MAC_REG_RX_TIMEOUT, 0x0);

	/* Set WLAN DMA पूर्णांकerrupt mode: generate पूर्णांक per packet */
	carl9170_regग_लिखो(AR9170_MAC_REG_TXRX_MPI, 0x110011);

	carl9170_regग_लिखो(AR9170_MAC_REG_FCS_SELECT,
			AR9170_MAC_FCS_FIFO_PROT);

	/* Disables the CF_END frame, unकरोcumented रेजिस्टर */
	carl9170_regग_लिखो(AR9170_MAC_REG_TXOP_NOT_ENOUGH_IND,
			0x141e0f48);

	/* reset group hash table */
	carl9170_regग_लिखो(AR9170_MAC_REG_GROUP_HASH_TBL_L, 0xffffffff);
	carl9170_regग_लिखो(AR9170_MAC_REG_GROUP_HASH_TBL_H, 0xffffffff);

	/* disable PRETBTT पूर्णांकerrupt */
	carl9170_regग_लिखो(AR9170_MAC_REG_PRETBTT, 0x0);
	carl9170_regग_लिखो(AR9170_MAC_REG_BCN_PERIOD, 0x0);

	carl9170_regग_लिखो_finish();

	वापस carl9170_regग_लिखो_result();
पूर्ण

अटल पूर्णांक carl9170_set_mac_reg(काष्ठा ar9170 *ar,
				स्थिर u32 reg, स्थिर u8 *mac)
अणु
	अटल स्थिर u8 zero[ETH_ALEN] = अणु 0 पूर्ण;

	अगर (!mac)
		mac = zero;

	carl9170_regग_लिखो_begin(ar);

	carl9170_regग_लिखो(reg, get_unaligned_le32(mac));
	carl9170_regग_लिखो(reg + 4, get_unaligned_le16(mac + 4));

	carl9170_regग_लिखो_finish();

	वापस carl9170_regग_लिखो_result();
पूर्ण

पूर्णांक carl9170_mod_भव_mac(काष्ठा ar9170 *ar, स्थिर अचिन्हित पूर्णांक id,
			     स्थिर u8 *mac)
अणु
	अगर (WARN_ON(id >= ar->fw.vअगर_num))
		वापस -EINVAL;

	वापस carl9170_set_mac_reg(ar,
		AR9170_MAC_REG_ACK_TABLE + (id - 1) * 8, mac);
पूर्ण

पूर्णांक carl9170_update_multicast(काष्ठा ar9170 *ar, स्थिर u64 mc_hash)
अणु
	पूर्णांक err;

	carl9170_regग_लिखो_begin(ar);
	carl9170_regग_लिखो(AR9170_MAC_REG_GROUP_HASH_TBL_H, mc_hash >> 32);
	carl9170_regग_लिखो(AR9170_MAC_REG_GROUP_HASH_TBL_L, mc_hash);
	carl9170_regग_लिखो_finish();
	err = carl9170_regग_लिखो_result();
	अगर (err)
		वापस err;

	ar->cur_mc_hash = mc_hash;
	वापस 0;
पूर्ण

पूर्णांक carl9170_set_operating_mode(काष्ठा ar9170 *ar)
अणु
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ath_common *common = &ar->common;
	u8 *mac_addr, *bssid;
	u32 cam_mode = AR9170_MAC_CAM_DEFAULTS;
	u32 enc_mode = AR9170_MAC_ENCRYPTION_DEFAULTS |
		AR9170_MAC_ENCRYPTION_MGMT_RX_SOFTWARE;
	u32 rx_ctrl = AR9170_MAC_RX_CTRL_DEAGG |
		      AR9170_MAC_RX_CTRL_SHORT_FILTER;
	u32 snअगरfer = AR9170_MAC_SNIFFER_DEFAULTS;
	पूर्णांक err = 0;

	rcu_पढ़ो_lock();
	vअगर = carl9170_get_मुख्य_vअगर(ar);

	अगर (vअगर) अणु
		mac_addr = common->macaddr;
		bssid = common->curbssid;

		चयन (vअगर->type) अणु
		हाल NL80211_IFTYPE_ADHOC:
			cam_mode |= AR9170_MAC_CAM_IBSS;
			अवरोध;
		हाल NL80211_IFTYPE_MESH_POINT:
		हाल NL80211_IFTYPE_AP:
			cam_mode |= AR9170_MAC_CAM_AP;

			/* iwlagn 802.11n STA Workaround */
			rx_ctrl |= AR9170_MAC_RX_CTRL_PASS_TO_HOST;
			अवरोध;
		हाल NL80211_IFTYPE_STATION:
			cam_mode |= AR9170_MAC_CAM_STA;
			rx_ctrl |= AR9170_MAC_RX_CTRL_PASS_TO_HOST;
			अवरोध;
		शेष:
			WARN(1, "Unsupported operation mode %x\n", vअगर->type);
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Enable monitor mode
		 *
		 * rx_ctrl |= AR9170_MAC_RX_CTRL_ACK_IN_SNIFFER;
		 * snअगरfer |= AR9170_MAC_SNIFFER_ENABLE_PROMISC;
		 *
		 * When the hardware is in SNIFFER_PROMISC mode,
		 * it generates spurious ACKs क्रम every incoming
		 * frame. This confuses every peer in the
		 * vicinity and the network throughput will suffer
		 * badly.
		 *
		 * Hence, the hardware will be put पूर्णांकo station
		 * mode and just the rx filters are disabled.
		 */
		cam_mode |= AR9170_MAC_CAM_STA;
		rx_ctrl |= AR9170_MAC_RX_CTRL_PASS_TO_HOST;
		mac_addr = common->macaddr;
		bssid = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (err)
		वापस err;

	अगर (ar->rx_software_decryption)
		enc_mode |= AR9170_MAC_ENCRYPTION_RX_SOFTWARE;

	अगर (ar->snअगरfer_enabled) अणु
		enc_mode |= AR9170_MAC_ENCRYPTION_RX_SOFTWARE;
	पूर्ण

	err = carl9170_set_mac_reg(ar, AR9170_MAC_REG_MAC_ADDR_L, mac_addr);
	अगर (err)
		वापस err;

	err = carl9170_set_mac_reg(ar, AR9170_MAC_REG_BSSID_L, bssid);
	अगर (err)
		वापस err;

	carl9170_regग_लिखो_begin(ar);
	carl9170_regग_लिखो(AR9170_MAC_REG_SNIFFER, snअगरfer);
	carl9170_regग_लिखो(AR9170_MAC_REG_CAM_MODE, cam_mode);
	carl9170_regग_लिखो(AR9170_MAC_REG_ENCRYPTION, enc_mode);
	carl9170_regग_लिखो(AR9170_MAC_REG_RX_CONTROL, rx_ctrl);
	carl9170_regग_लिखो_finish();

	वापस carl9170_regग_लिखो_result();
पूर्ण

पूर्णांक carl9170_set_hwretry_limit(काष्ठा ar9170 *ar, स्थिर अचिन्हित पूर्णांक max_retry)
अणु
	u32 पंचांगp = min_t(u32, 0x33333, max_retry * 0x11111);

	वापस carl9170_ग_लिखो_reg(ar, AR9170_MAC_REG_RETRY_MAX, पंचांगp);
पूर्ण

पूर्णांक carl9170_set_beacon_समयrs(काष्ठा ar9170 *ar)
अणु
	काष्ठा ieee80211_vअगर *vअगर;
	u32 v = 0;
	u32 pretbtt = 0;

	rcu_पढ़ो_lock();
	vअगर = carl9170_get_मुख्य_vअगर(ar);

	अगर (vअगर) अणु
		काष्ठा carl9170_vअगर_info *mvअगर;
		mvअगर = (व्योम *) vअगर->drv_priv;

		अगर (mvअगर->enable_beacon && !WARN_ON(!ar->beacon_enabled)) अणु
			ar->global_beacon_पूर्णांक = vअगर->bss_conf.beacon_पूर्णांक /
						ar->beacon_enabled;

			SET_VAL(AR9170_MAC_BCN_DTIM, v,
				vअगर->bss_conf.dtim_period);

			चयन (vअगर->type) अणु
			हाल NL80211_IFTYPE_MESH_POINT:
			हाल NL80211_IFTYPE_ADHOC:
				v |= AR9170_MAC_BCN_IBSS_MODE;
				अवरोध;
			हाल NL80211_IFTYPE_AP:
				v |= AR9170_MAC_BCN_AP_MODE;
				अवरोध;
			शेष:
				WARN_ON_ONCE(1);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
			ar->global_beacon_पूर्णांक = vअगर->bss_conf.beacon_पूर्णांक;

			SET_VAL(AR9170_MAC_BCN_DTIM, v,
				ar->hw->conf.ps_dtim_period);

			v |= AR9170_MAC_BCN_STA_PS |
			     AR9170_MAC_BCN_PWR_MGT;
		पूर्ण

		अगर (ar->global_beacon_पूर्णांक) अणु
			अगर (ar->global_beacon_पूर्णांक < 15) अणु
				rcu_पढ़ो_unlock();
				वापस -दुस्फल;
			पूर्ण

			ar->global_pretbtt = ar->global_beacon_पूर्णांक -
					CARL9170_PRETBTT_KUS;
		पूर्ण अन्यथा अणु
			ar->global_pretbtt = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		ar->global_beacon_पूर्णांक = 0;
		ar->global_pretbtt = 0;
	पूर्ण

	rcu_पढ़ो_unlock();

	SET_VAL(AR9170_MAC_BCN_PERIOD, v, ar->global_beacon_पूर्णांक);
	SET_VAL(AR9170_MAC_PRETBTT, pretbtt, ar->global_pretbtt);
	SET_VAL(AR9170_MAC_PRETBTT2, pretbtt, ar->global_pretbtt);

	carl9170_regग_लिखो_begin(ar);
	carl9170_regग_लिखो(AR9170_MAC_REG_PRETBTT, pretbtt);
	carl9170_regग_लिखो(AR9170_MAC_REG_BCN_PERIOD, v);
	carl9170_regग_लिखो_finish();
	वापस carl9170_regग_लिखो_result();
पूर्ण

पूर्णांक carl9170_upload_key(काष्ठा ar9170 *ar, स्थिर u8 id, स्थिर u8 *mac,
			स्थिर u8 ktype, स्थिर u8 keyidx, स्थिर u8 *keydata,
			स्थिर पूर्णांक keylen)
अणु
	काष्ठा carl9170_set_key_cmd key = अणु पूर्ण;
	अटल स्थिर u8 bcast[ETH_ALEN] = अणु
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;

	mac = mac ? : bcast;

	key.user = cpu_to_le16(id);
	key.keyId = cpu_to_le16(keyidx);
	key.type = cpu_to_le16(ktype);
	स_नकल(&key.macAddr, mac, ETH_ALEN);
	अगर (keydata)
		स_नकल(&key.key, keydata, keylen);

	वापस carl9170_exec_cmd(ar, CARL9170_CMD_EKEY,
		माप(key), (u8 *)&key, 0, शून्य);
पूर्ण

पूर्णांक carl9170_disable_key(काष्ठा ar9170 *ar, स्थिर u8 id)
अणु
	काष्ठा carl9170_disable_key_cmd key = अणु पूर्ण;

	key.user = cpu_to_le16(id);

	वापस carl9170_exec_cmd(ar, CARL9170_CMD_DKEY,
		माप(key), (u8 *)&key, 0, शून्य);
पूर्ण

पूर्णांक carl9170_set_mac_tpc(काष्ठा ar9170 *ar, काष्ठा ieee80211_channel *channel)
अणु
	अचिन्हित पूर्णांक घातer, chains;

	अगर (ar->eeprom.tx_mask != 1)
		chains = AR9170_TX_PHY_TXCHAIN_2;
	अन्यथा
		chains = AR9170_TX_PHY_TXCHAIN_1;

	चयन (channel->band) अणु
	हाल NL80211_BAND_2GHZ:
		घातer = ar->घातer_2G_ofdm[0] & 0x3f;
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		घातer = ar->घातer_5G_leg[0] & 0x3f;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	घातer = min_t(अचिन्हित पूर्णांक, घातer, ar->hw->conf.घातer_level * 2);

	carl9170_regग_लिखो_begin(ar);
	carl9170_regग_लिखो(AR9170_MAC_REG_ACK_TPC,
			  0x3c1e | घातer << 20 | chains << 26);
	carl9170_regग_लिखो(AR9170_MAC_REG_RTS_CTS_TPC,
			  घातer << 5 | chains << 11 |
			  घातer << 21 | chains << 27);
	carl9170_regग_लिखो(AR9170_MAC_REG_CFEND_QOSशून्य_TPC,
			  घातer << 5 | chains << 11 |
			  घातer << 21 | chains << 27);
	carl9170_regग_लिखो_finish();
	वापस carl9170_regग_लिखो_result();
पूर्ण
