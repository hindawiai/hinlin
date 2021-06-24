<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Firmware I/O code क्रम mac80211 Prism54 drivers
 *
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 * Copyright (c) 2007-2009, Christian Lamparter <chunkeey@web.de>
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 *
 * Based on:
 * - the islsm (sofपंचांगac prism54) driver, which is:
 *   Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 * - stlc45xx driver
 *   Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
 */

#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/export.h>

#समावेश <net/mac80211.h>

#समावेश "p54.h"
#समावेश "eeprom.h"
#समावेश "lmac.h"

पूर्णांक p54_parse_firmware(काष्ठा ieee80211_hw *dev, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा p54_common *priv = dev->priv;
	काष्ठा exp_अगर *exp_अगर;
	काष्ठा bootrec *bootrec;
	u32 *data = (u32 *)fw->data;
	u32 *end_data = (u32 *)fw->data + (fw->size >> 2);
	u8 *fw_version = शून्य;
	माप_प्रकार len;
	पूर्णांक i;
	पूर्णांक maxlen;

	अगर (priv->rx_start)
		वापस 0;

	जबतक (data < end_data && *data)
		data++;

	जबतक (data < end_data && !*data)
		data++;

	bootrec = (काष्ठा bootrec *) data;

	जबतक (bootrec->data <= end_data && (bootrec->data +
	       (len = le32_to_cpu(bootrec->len))) <= end_data) अणु
		u32 code = le32_to_cpu(bootrec->code);
		चयन (code) अणु
		हाल BR_CODE_COMPONENT_ID:
			priv->fw_पूर्णांकerface = be32_to_cpup((__be32 *)
					     bootrec->data);
			चयन (priv->fw_पूर्णांकerface) अणु
			हाल FW_LM86:
			हाल FW_LM20:
			हाल FW_LM87: अणु
				अक्षर *अगरtype = (अक्षर *)bootrec->data;
				wiphy_info(priv->hw->wiphy,
					   "p54 detected a LM%c%c firmware\n",
					   अगरtype[2], अगरtype[3]);
				अवरोध;
				पूर्ण
			हाल FW_FMAC:
			शेष:
				wiphy_err(priv->hw->wiphy,
					  "unsupported firmware\n");
				वापस -ENODEV;
			पूर्ण
			अवरोध;
		हाल BR_CODE_COMPONENT_VERSION:
			/* 24 bytes should be enough क्रम all firmwares */
			अगर (strnlen((अचिन्हित अक्षर *) bootrec->data, 24) < 24)
				fw_version = (अचिन्हित अक्षर *) bootrec->data;
			अवरोध;
		हाल BR_CODE_DESCR: अणु
			काष्ठा bootrec_desc *desc =
				(काष्ठा bootrec_desc *)bootrec->data;
			priv->rx_start = le32_to_cpu(desc->rx_start);
			/* FIXME add sanity checking */
			priv->rx_end = le32_to_cpu(desc->rx_end) - 0x3500;
			priv->headroom = desc->headroom;
			priv->tailroom = desc->tailroom;
			priv->privacy_caps = desc->privacy_caps;
			priv->rx_keycache_size = desc->rx_keycache_size;
			अगर (le32_to_cpu(bootrec->len) == 11)
				priv->rx_mtu = le16_to_cpu(desc->rx_mtu);
			अन्यथा
				priv->rx_mtu = (माप_प्रकार)
					0x620 - priv->tx_hdr_len;
			maxlen = priv->tx_hdr_len + /* USB devices */
				 माप(काष्ठा p54_rx_data) +
				 4 + /* rx alignment */
				 IEEE80211_MAX_FRAG_THRESHOLD;
			अगर (priv->rx_mtu > maxlen && PAGE_SIZE == 4096) अणु
				prपूर्णांकk(KERN_INFO "p54: rx_mtu reduced from %d "
				       "to %d\n", priv->rx_mtu, maxlen);
				priv->rx_mtu = maxlen;
			पूर्ण
			अवरोध;
			पूर्ण
		हाल BR_CODE_EXPOSED_IF:
			exp_अगर = (काष्ठा exp_अगर *) bootrec->data;
			क्रम (i = 0; i < (len * माप(*exp_अगर) / 4); i++)
				अगर (exp_अगर[i].अगर_id == cpu_to_le16(IF_ID_LMAC))
					priv->fw_var = le16_to_cpu(exp_अगर[i].variant);
			अवरोध;
		हाल BR_CODE_DEPENDENT_IF:
			अवरोध;
		हाल BR_CODE_END_OF_BRA:
		हाल LEGACY_BR_CODE_END_OF_BRA:
			end_data = शून्य;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		bootrec = (काष्ठा bootrec *)&bootrec->data[len];
	पूर्ण

	अगर (fw_version) अणु
		wiphy_info(priv->hw->wiphy,
			   "FW rev %s - Softmac protocol %x.%x\n",
			   fw_version, priv->fw_var >> 8, priv->fw_var & 0xff);
		snम_लिखो(dev->wiphy->fw_version, माप(dev->wiphy->fw_version),
				"%s - %x.%x", fw_version,
				priv->fw_var >> 8, priv->fw_var & 0xff);
	पूर्ण

	अगर (priv->fw_var < 0x500)
		wiphy_info(priv->hw->wiphy,
			   "you are using an obsolete firmware. "
			   "visit http://wireless.wiki.kernel.org/en/users/Drivers/p54 "
			   "and grab one for \"kernel >= 2.6.28\"!\n");

	अगर (priv->fw_var >= 0x300) अणु
		/* Firmware supports QoS, use it! */

		अगर (priv->fw_var >= 0x500) अणु
			priv->tx_stats[P54_QUEUE_AC_VO].limit = 16;
			priv->tx_stats[P54_QUEUE_AC_VI].limit = 16;
			priv->tx_stats[P54_QUEUE_AC_BE].limit = 16;
			priv->tx_stats[P54_QUEUE_AC_BK].limit = 16;
		पूर्ण अन्यथा अणु
			priv->tx_stats[P54_QUEUE_AC_VO].limit = 3;
			priv->tx_stats[P54_QUEUE_AC_VI].limit = 4;
			priv->tx_stats[P54_QUEUE_AC_BE].limit = 3;
			priv->tx_stats[P54_QUEUE_AC_BK].limit = 2;
		पूर्ण
		priv->hw->queues = P54_QUEUE_AC_NUM;
	पूर्ण

	wiphy_info(priv->hw->wiphy,
		   "cryptographic accelerator WEP:%s, TKIP:%s, CCMP:%s\n",
		   (priv->privacy_caps & BR_DESC_PRIV_CAP_WEP) ? "YES" : "no",
		   (priv->privacy_caps &
		    (BR_DESC_PRIV_CAP_TKIP | BR_DESC_PRIV_CAP_MICHAEL))
		   ? "YES" : "no",
		   (priv->privacy_caps & BR_DESC_PRIV_CAP_AESCCMP)
		   ? "YES" : "no");

	अगर (priv->rx_keycache_size) अणु
		/*
		 * NOTE:
		 *
		 * The firmware provides at most 255 (0 - 254) slots
		 * क्रम keys which are then used to offload decryption.
		 * As a result the 255 entry (aka 0xff) can be used
		 * safely by the driver to mark keys that didn't fit
		 * पूर्णांकo the full cache. This trick saves us from
		 * keeping a extra list क्रम uploaded keys.
		 */

		priv->used_rxkeys = kसुस्मृति(BITS_TO_LONGS(priv->rx_keycache_size),
					    माप(दीर्घ),
					    GFP_KERNEL);

		अगर (!priv->used_rxkeys)
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(p54_parse_firmware);

अटल काष्ठा sk_buff *p54_alloc_skb(काष्ठा p54_common *priv, u16 hdr_flags,
				     u16 payload_len, u16 type, gfp_t memflags)
अणु
	काष्ठा p54_hdr *hdr;
	काष्ठा sk_buff *skb;
	माप_प्रकार frame_len = माप(*hdr) + payload_len;

	अगर (frame_len > P54_MAX_CTRL_FRAME_LEN)
		वापस शून्य;

	अगर (unlikely(skb_queue_len(&priv->tx_pending) > 64))
		वापस शून्य;

	skb = __dev_alloc_skb(priv->tx_hdr_len + frame_len, memflags);
	अगर (!skb)
		वापस शून्य;
	skb_reserve(skb, priv->tx_hdr_len);

	hdr = skb_put(skb, माप(*hdr));
	hdr->flags = cpu_to_le16(hdr_flags);
	hdr->len = cpu_to_le16(payload_len);
	hdr->type = cpu_to_le16(type);
	hdr->tries = hdr->rts_tries = 0;
	वापस skb;
पूर्ण

पूर्णांक p54_करोwnload_eeprom(काष्ठा p54_common *priv, व्योम *buf,
			u16 offset, u16 len)
अणु
	काष्ठा p54_eeprom_lm86 *eeprom_hdr;
	काष्ठा sk_buff *skb;
	माप_प्रकार eeprom_hdr_size;
	पूर्णांक ret = 0;
	दीर्घ समयout;

	अगर (priv->fw_var >= 0x509)
		eeprom_hdr_size = माप(*eeprom_hdr);
	अन्यथा
		eeprom_hdr_size = 0x4;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL, eeprom_hdr_size +
			    len, P54_CONTROL_TYPE_EEPROM_READBACK,
			    GFP_KERNEL);
	अगर (unlikely(!skb))
		वापस -ENOMEM;

	mutex_lock(&priv->eeprom_mutex);
	priv->eeprom = buf;
	eeprom_hdr = skb_put(skb, eeprom_hdr_size + len);

	अगर (priv->fw_var < 0x509) अणु
		eeprom_hdr->v1.offset = cpu_to_le16(offset);
		eeprom_hdr->v1.len = cpu_to_le16(len);
	पूर्ण अन्यथा अणु
		eeprom_hdr->v2.offset = cpu_to_le32(offset);
		eeprom_hdr->v2.len = cpu_to_le16(len);
		eeprom_hdr->v2.magic2 = 0xf;
		स_नकल(eeprom_hdr->v2.magic, (स्थिर अक्षर *)"LOCK", 4);
	पूर्ण

	p54_tx(priv, skb);

	समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&priv->eeprom_comp, HZ);
	अगर (समयout <= 0) अणु
		wiphy_err(priv->hw->wiphy,
			"device does not respond or signal received!\n");
		ret = -EBUSY;
	पूर्ण
	priv->eeprom = शून्य;
	mutex_unlock(&priv->eeprom_mutex);
	वापस ret;
पूर्ण

पूर्णांक p54_update_beacon_tim(काष्ठा p54_common *priv, u16 aid, bool set)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा p54_tim *tim;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL_OPSET, माप(*tim),
			    P54_CONTROL_TYPE_TIM, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस -ENOMEM;

	tim = skb_put(skb, माप(*tim));
	tim->count = 1;
	tim->entry[0] = cpu_to_le16(set ? (aid | 0x8000) : aid);
	p54_tx(priv, skb);
	वापस 0;
पूर्ण

पूर्णांक p54_sta_unlock(काष्ठा p54_common *priv, u8 *addr)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा p54_sta_unlock *sta;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL_OPSET, माप(*sta),
			    P54_CONTROL_TYPE_PSM_STA_UNLOCK, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस -ENOMEM;

	sta = skb_put(skb, माप(*sta));
	स_नकल(sta->addr, addr, ETH_ALEN);
	p54_tx(priv, skb);
	वापस 0;
पूर्ण

पूर्णांक p54_tx_cancel(काष्ठा p54_common *priv, __le32 req_id)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा p54_txcancel *cancel;
	u32 _req_id = le32_to_cpu(req_id);

	अगर (unlikely(_req_id < priv->rx_start || _req_id > priv->rx_end))
		वापस -EINVAL;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL_OPSET, माप(*cancel),
			    P54_CONTROL_TYPE_TXCANCEL, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस -ENOMEM;

	cancel = skb_put(skb, माप(*cancel));
	cancel->req_id = req_id;
	p54_tx(priv, skb);
	वापस 0;
पूर्ण

पूर्णांक p54_setup_mac(काष्ठा p54_common *priv)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा p54_setup_mac *setup;
	u16 mode;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL_OPSET, माप(*setup),
			    P54_CONTROL_TYPE_SETUP, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	setup = skb_put(skb, माप(*setup));
	अगर (!(priv->hw->conf.flags & IEEE80211_CONF_IDLE)) अणु
		चयन (priv->mode) अणु
		हाल NL80211_IFTYPE_STATION:
			mode = P54_FILTER_TYPE_STATION;
			अवरोध;
		हाल NL80211_IFTYPE_AP:
			mode = P54_FILTER_TYPE_AP;
			अवरोध;
		हाल NL80211_IFTYPE_ADHOC:
		हाल NL80211_IFTYPE_MESH_POINT:
			mode = P54_FILTER_TYPE_IBSS;
			अवरोध;
		हाल NL80211_IFTYPE_MONITOR:
			mode = P54_FILTER_TYPE_PROMISCUOUS;
			अवरोध;
		शेष:
			mode = P54_FILTER_TYPE_HIBERNATE;
			अवरोध;
		पूर्ण

		/*
		 * "TRANSPARENT and PROMISCUOUS are mutually exclusive"
		 * STSW45X0C LMAC API - page 12
		 */
		अगर (priv->filter_flags & FIF_OTHER_BSS &&
		    (mode != P54_FILTER_TYPE_PROMISCUOUS))
			mode |= P54_FILTER_TYPE_TRANSPARENT;
	पूर्ण अन्यथा अणु
		mode = P54_FILTER_TYPE_HIBERNATE;
	पूर्ण

	setup->mac_mode = cpu_to_le16(mode);
	स_नकल(setup->mac_addr, priv->mac_addr, ETH_ALEN);
	स_नकल(setup->bssid, priv->bssid, ETH_ALEN);
	setup->rx_antenna = 2 & priv->rx_भागersity_mask; /* स्वतःmatic */
	setup->rx_align = 0;
	अगर (priv->fw_var < 0x500) अणु
		setup->v1.basic_rate_mask = cpu_to_le32(priv->basic_rate_mask);
		स_रखो(setup->v1.rts_rates, 0, 8);
		setup->v1.rx_addr = cpu_to_le32(priv->rx_end);
		setup->v1.max_rx = cpu_to_le16(priv->rx_mtu);
		setup->v1.rxhw = cpu_to_le16(priv->rxhw);
		setup->v1.wakeup_समयr = cpu_to_le16(priv->wakeup_समयr);
		setup->v1.unalloc0 = cpu_to_le16(0);
	पूर्ण अन्यथा अणु
		setup->v2.rx_addr = cpu_to_le32(priv->rx_end);
		setup->v2.max_rx = cpu_to_le16(priv->rx_mtu);
		setup->v2.rxhw = cpu_to_le16(priv->rxhw);
		setup->v2.समयr = cpu_to_le16(priv->wakeup_समयr);
		setup->v2.truncate = cpu_to_le16(48896);
		setup->v2.basic_rate_mask = cpu_to_le32(priv->basic_rate_mask);
		setup->v2.sbss_offset = 0;
		setup->v2.mcast_winकरोw = 0;
		setup->v2.rx_rssi_threshold = 0;
		setup->v2.rx_ed_threshold = 0;
		setup->v2.ref_घड़ी = cpu_to_le32(644245094);
		setup->v2.lpf_bandwidth = cpu_to_le16(65535);
		setup->v2.osc_start_delay = cpu_to_le16(65535);
	पूर्ण
	p54_tx(priv, skb);
	priv->phy_idle = mode == P54_FILTER_TYPE_HIBERNATE;
	वापस 0;
पूर्ण

पूर्णांक p54_scan(काष्ठा p54_common *priv, u16 mode, u16 dwell)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा p54_hdr *hdr;
	काष्ठा p54_scan_head *head;
	काष्ठा p54_iq_स्वतःcal_entry *iq_स्वतःcal;
	जोड़ p54_scan_body_जोड़ *body;
	काष्ठा p54_scan_tail_rate *rate;
	काष्ठा pda_rssi_cal_entry *rssi;
	काष्ठा p54_rssi_db_entry *rssi_data;
	अचिन्हित पूर्णांक i;
	व्योम *entry;
	__le16 freq = cpu_to_le16(priv->hw->conf.chandef.chan->center_freq);

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL_OPSET, माप(*head) +
			    2 + माप(*iq_स्वतःcal) + माप(*body) +
			    माप(*rate) + 2 * माप(*rssi),
			    P54_CONTROL_TYPE_SCAN, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	head = skb_put(skb, माप(*head));
	स_रखो(head->scan_params, 0, माप(head->scan_params));
	head->mode = cpu_to_le16(mode);
	head->dwell = cpu_to_le16(dwell);
	head->freq = freq;

	अगर (priv->rxhw == PDR_SYNTH_FRONTEND_LONGBOW) अणु
		__le16 *pa_घातer_poपूर्णांकs = skb_put(skb, 2);
		*pa_घातer_poपूर्णांकs = cpu_to_le16(0x0c);
	पूर्ण

	iq_स्वतःcal = skb_put(skb, माप(*iq_स्वतःcal));
	क्रम (i = 0; i < priv->iq_स्वतःcal_len; i++) अणु
		अगर (priv->iq_स्वतःcal[i].freq != freq)
			जारी;

		स_नकल(iq_स्वतःcal, &priv->iq_स्वतःcal[i].params,
		       माप(काष्ठा p54_iq_स्वतःcal_entry));
		अवरोध;
	पूर्ण
	अगर (i == priv->iq_स्वतःcal_len)
		जाओ err;

	अगर (priv->rxhw == PDR_SYNTH_FRONTEND_LONGBOW)
		body = skb_put(skb, माप(body->दीर्घbow));
	अन्यथा
		body = skb_put(skb, माप(body->normal));

	क्रम (i = 0; i < priv->output_limit->entries; i++) अणु
		__le16 *entry_freq = (व्योम *) (priv->output_limit->data +
				     priv->output_limit->entry_size * i);

		अगर (*entry_freq != freq)
			जारी;

		अगर (priv->rxhw == PDR_SYNTH_FRONTEND_LONGBOW) अणु
			स_नकल(&body->दीर्घbow.घातer_limits,
			       (व्योम *) entry_freq + माप(__le16),
			       priv->output_limit->entry_size);
		पूर्ण अन्यथा अणु
			काष्ठा pda_channel_output_limit *limits =
			       (व्योम *) entry_freq;

			body->normal.val_barker = 0x38;
			body->normal.val_bpsk = body->normal.dup_bpsk =
				limits->val_bpsk;
			body->normal.val_qpsk = body->normal.dup_qpsk =
				limits->val_qpsk;
			body->normal.val_16qam = body->normal.dup_16qam =
				limits->val_16qam;
			body->normal.val_64qam = body->normal.dup_64qam =
				limits->val_64qam;
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (i == priv->output_limit->entries)
		जाओ err;

	entry = (व्योम *)(priv->curve_data->data + priv->curve_data->offset);
	क्रम (i = 0; i < priv->curve_data->entries; i++) अणु
		अगर (*((__le16 *)entry) != freq) अणु
			entry += priv->curve_data->entry_size;
			जारी;
		पूर्ण

		अगर (priv->rxhw == PDR_SYNTH_FRONTEND_LONGBOW) अणु
			स_नकल(&body->दीर्घbow.curve_data,
				entry + माप(__le16),
				priv->curve_data->entry_size);
		पूर्ण अन्यथा अणु
			काष्ठा p54_scan_body *chan = &body->normal;
			काष्ठा pda_pa_curve_data *curve_data =
				(व्योम *) priv->curve_data->data;

			entry += माप(__le16);
			chan->pa_poपूर्णांकs_per_curve = 8;
			स_रखो(chan->curve_data, 0, माप(chan->curve_data));
			स_नकल(chan->curve_data, entry,
			       माप(काष्ठा p54_pa_curve_data_sample) *
			       min((u8)8, curve_data->poपूर्णांकs_per_channel));
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (i == priv->curve_data->entries)
		जाओ err;

	अगर ((priv->fw_var >= 0x500) && (priv->fw_var < 0x509)) अणु
		rate = skb_put(skb, माप(*rate));
		rate->basic_rate_mask = cpu_to_le32(priv->basic_rate_mask);
		क्रम (i = 0; i < माप(rate->rts_rates); i++)
			rate->rts_rates[i] = i;
	पूर्ण

	rssi = skb_put(skb, माप(*rssi));
	rssi_data = p54_rssi_find(priv, le16_to_cpu(freq));
	rssi->mul = cpu_to_le16(rssi_data->mul);
	rssi->add = cpu_to_le16(rssi_data->add);
	अगर (priv->rxhw == PDR_SYNTH_FRONTEND_LONGBOW) अणु
		/* Longbow frontend needs ever more */
		rssi = skb_put(skb, माप(*rssi));
		rssi->mul = cpu_to_le16(rssi_data->दीर्घbow_unkn);
		rssi->add = cpu_to_le16(rssi_data->दीर्घbow_unk2);
	पूर्ण

	अगर (priv->fw_var >= 0x509) अणु
		rate = skb_put(skb, माप(*rate));
		rate->basic_rate_mask = cpu_to_le32(priv->basic_rate_mask);
		क्रम (i = 0; i < माप(rate->rts_rates); i++)
			rate->rts_rates[i] = i;
	पूर्ण

	hdr = (काष्ठा p54_hdr *) skb->data;
	hdr->len = cpu_to_le16(skb->len - माप(*hdr));

	p54_tx(priv, skb);
	priv->cur_rssi = rssi_data;
	वापस 0;

err:
	wiphy_err(priv->hw->wiphy, "frequency change to channel %d failed.\n",
		  ieee80211_frequency_to_channel(
			  priv->hw->conf.chandef.chan->center_freq));

	dev_kमुक्त_skb_any(skb);
	वापस -EINVAL;
पूर्ण

पूर्णांक p54_set_leds(काष्ठा p54_common *priv)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा p54_led *led;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL_OPSET, माप(*led),
			    P54_CONTROL_TYPE_LED, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस -ENOMEM;

	led = skb_put(skb, माप(*led));
	led->flags = cpu_to_le16(0x0003);
	led->mask[0] = led->mask[1] = cpu_to_le16(priv->softled_state);
	led->delay[0] = cpu_to_le16(1);
	led->delay[1] = cpu_to_le16(0);
	p54_tx(priv, skb);
	वापस 0;
पूर्ण

पूर्णांक p54_set_edcf(काष्ठा p54_common *priv)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा p54_edcf *edcf;
	u8 rtd;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL_OPSET, माप(*edcf),
			    P54_CONTROL_TYPE_DCFINIT, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस -ENOMEM;

	edcf = skb_put(skb, माप(*edcf));
	अगर (priv->use_लघु_slot) अणु
		edcf->slotसमय = 9;
		edcf->sअगरs = 0x10;
		edcf->eofpad = 0x00;
	पूर्ण अन्यथा अणु
		edcf->slotसमय = 20;
		edcf->sअगरs = 0x0a;
		edcf->eofpad = 0x06;
	पूर्ण
	/*
	 * calculate the extra round trip delay according to the
	 * क्रमmula from 802.11-2007 17.3.8.6.
	 */
	rtd = 3 * priv->coverage_class;
	edcf->slotसमय += rtd;
	edcf->round_trip_delay = cpu_to_le16(rtd);
	/* (see prism54/isl_oid.h क्रम further details) */
	edcf->frameburst = cpu_to_le16(0);
	edcf->flags = 0;
	स_रखो(edcf->mapping, 0, माप(edcf->mapping));
	स_नकल(edcf->queue, priv->qos_params, माप(edcf->queue));
	p54_tx(priv, skb);
	वापस 0;
पूर्ण

पूर्णांक p54_set_ps(काष्ठा p54_common *priv)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा p54_psm *psm;
	अचिन्हित पूर्णांक i;
	u16 mode;

	अगर (priv->hw->conf.flags & IEEE80211_CONF_PS &&
	    !priv->घातersave_override)
		mode = P54_PSM | P54_PSM_BEACON_TIMEOUT | P54_PSM_DTIM |
		       P54_PSM_CHECKSUM | P54_PSM_MCBC;
	अन्यथा
		mode = P54_PSM_CAM;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL_OPSET, माप(*psm),
			    P54_CONTROL_TYPE_PSM, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	psm = skb_put(skb, माप(*psm));
	psm->mode = cpu_to_le16(mode);
	psm->aid = cpu_to_le16(priv->aid);
	क्रम (i = 0; i < ARRAY_SIZE(psm->पूर्णांकervals); i++) अणु
		psm->पूर्णांकervals[i].पूर्णांकerval =
			cpu_to_le16(priv->hw->conf.listen_पूर्णांकerval);
		psm->पूर्णांकervals[i].periods = cpu_to_le16(1);
	पूर्ण

	psm->beacon_rssi_skip_max = 200;
	psm->rssi_delta_threshold = 0;
	psm->nr = 1;
	psm->exclude[0] = WLAN_EID_TIM;

	p54_tx(priv, skb);
	priv->phy_ps = mode != P54_PSM_CAM;
	वापस 0;
पूर्ण

पूर्णांक p54_init_xbow_synth(काष्ठा p54_common *priv)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा p54_xbow_synth *xbow;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL_OPSET, माप(*xbow),
			    P54_CONTROL_TYPE_XBOW_SYNTH_CFG, GFP_KERNEL);
	अगर (unlikely(!skb))
		वापस -ENOMEM;

	xbow = skb_put(skb, माप(*xbow));
	xbow->magic1 = cpu_to_le16(0x1);
	xbow->magic2 = cpu_to_le16(0x2);
	xbow->freq = cpu_to_le16(5390);
	स_रखो(xbow->padding, 0, माप(xbow->padding));
	p54_tx(priv, skb);
	वापस 0;
पूर्ण

पूर्णांक p54_upload_key(काष्ठा p54_common *priv, u8 algo, पूर्णांक slot, u8 idx, u8 len,
		   u8 *addr, u8* key)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा p54_keycache *rxkey;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL_OPSET, माप(*rxkey),
			    P54_CONTROL_TYPE_RX_KEYCACHE, GFP_KERNEL);
	अगर (unlikely(!skb))
		वापस -ENOMEM;

	rxkey = skb_put(skb, माप(*rxkey));
	rxkey->entry = slot;
	rxkey->key_id = idx;
	rxkey->key_type = algo;
	अगर (addr)
		स_नकल(rxkey->mac, addr, ETH_ALEN);
	अन्यथा
		eth_broadcast_addr(rxkey->mac);

	चयन (algo) अणु
	हाल P54_CRYPTO_WEP:
	हाल P54_CRYPTO_AESCCMP:
		rxkey->key_len = min_t(u8, 16, len);
		स_नकल(rxkey->key, key, rxkey->key_len);
		अवरोध;

	हाल P54_CRYPTO_TKIPMICHAEL:
		rxkey->key_len = 24;
		स_नकल(rxkey->key, key, 16);
		स_नकल(&(rxkey->key[16]), &(key
			[NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY]), 8);
		अवरोध;

	हाल P54_CRYPTO_NONE:
		rxkey->key_len = 0;
		स_रखो(rxkey->key, 0, माप(rxkey->key));
		अवरोध;

	शेष:
		wiphy_err(priv->hw->wiphy,
			  "invalid cryptographic algorithm: %d\n", algo);
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	p54_tx(priv, skb);
	वापस 0;
पूर्ण

पूर्णांक p54_fetch_statistics(काष्ठा p54_common *priv)
अणु
	काष्ठा ieee80211_tx_info *txinfo;
	काष्ठा p54_tx_info *p54info;
	काष्ठा sk_buff *skb;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL,
			    माप(काष्ठा p54_statistics),
			    P54_CONTROL_TYPE_STAT_READBACK, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	/*
	 * The statistic feedback causes some extra headaches here, अगर it
	 * is not to crash/corrupt the firmware data काष्ठाures.
	 *
	 * Unlike all other Control Get OIDs we can not use helpers like
	 * skb_put to reserve the space क्रम the data we're requesting.
	 * Instead the extra frame length -which will hold the results later-
	 * will only be told to the p54_assign_address, so that following
	 * frames won't be placed पूर्णांकo the  allegedly empty area.
	 */
	txinfo = IEEE80211_SKB_CB(skb);
	p54info = (व्योम *) txinfo->rate_driver_data;
	p54info->extra_len = माप(काष्ठा p54_statistics);

	p54_tx(priv, skb);
	वापस 0;
पूर्ण

पूर्णांक p54_set_groupfilter(काष्ठा p54_common *priv)
अणु
	काष्ठा p54_group_address_table *grp;
	काष्ठा sk_buff *skb;
	bool on = false;

	skb = p54_alloc_skb(priv, P54_HDR_FLAG_CONTROL_OPSET, माप(*grp),
			    P54_CONTROL_TYPE_GROUP_ADDRESS_TABLE, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	grp = skb_put(skb, माप(*grp));

	on = !(priv->filter_flags & FIF_ALLMULTI) &&
	     (priv->mc_maclist_num > 0 &&
	      priv->mc_maclist_num <= MC_FILTER_ADDRESS_NUM);

	अगर (on) अणु
		grp->filter_enable = cpu_to_le16(1);
		grp->num_address = cpu_to_le16(priv->mc_maclist_num);
		स_नकल(grp->mac_list, priv->mc_maclist, माप(grp->mac_list));
	पूर्ण अन्यथा अणु
		grp->filter_enable = cpu_to_le16(0);
		grp->num_address = cpu_to_le16(0);
		स_रखो(grp->mac_list, 0, माप(grp->mac_list));
	पूर्ण

	p54_tx(priv, skb);
	वापस 0;
पूर्ण
