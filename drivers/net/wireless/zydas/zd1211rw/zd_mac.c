<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* ZD1211 USB-WLAN driver क्रम Linux
 *
 * Copyright (C) 2005-2007 Ulrich Kunitz <kune@deine-taler.de>
 * Copyright (C) 2006-2007 Daniel Drake <dsd@gentoo.org>
 * Copyright (C) 2006-2007 Michael Wu <flamingice@sourmilk.net>
 * Copyright (C) 2007-2008 Luis R. Rodriguez <mcgrof@winlab.rutgers.edu>
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/jअगरfies.h>
#समावेश <net/ieee80211_radiotap.h>

#समावेश "zd_def.h"
#समावेश "zd_chip.h"
#समावेश "zd_mac.h"
#समावेश "zd_rf.h"

काष्ठा zd_reg_alpha2_map अणु
	u32 reg;
	अक्षर alpha2[2];
पूर्ण;

अटल काष्ठा zd_reg_alpha2_map reg_alpha2_map[] = अणु
	अणु ZD_REGDOMAIN_FCC, "US" पूर्ण,
	अणु ZD_REGDOMAIN_IC, "CA" पूर्ण,
	अणु ZD_REGDOMAIN_ETSI, "DE" पूर्ण, /* Generic ETSI, use most restrictive */
	अणु ZD_REGDOMAIN_JAPAN, "JP" पूर्ण,
	अणु ZD_REGDOMAIN_JAPAN_2, "JP" पूर्ण,
	अणु ZD_REGDOMAIN_JAPAN_3, "JP" पूर्ण,
	अणु ZD_REGDOMAIN_SPAIN, "ES" पूर्ण,
	अणु ZD_REGDOMAIN_FRANCE, "FR" पूर्ण,
पूर्ण;

/* This table contains the hardware specअगरic values क्रम the modulation rates. */
अटल स्थिर काष्ठा ieee80211_rate zd_rates[] = अणु
	अणु .bitrate = 10,
	  .hw_value = ZD_CCK_RATE_1M, पूर्ण,
	अणु .bitrate = 20,
	  .hw_value = ZD_CCK_RATE_2M,
	  .hw_value_लघु = ZD_CCK_RATE_2M | ZD_CCK_PREA_SHORT,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 55,
	  .hw_value = ZD_CCK_RATE_5_5M,
	  .hw_value_लघु = ZD_CCK_RATE_5_5M | ZD_CCK_PREA_SHORT,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 110,
	  .hw_value = ZD_CCK_RATE_11M,
	  .hw_value_लघु = ZD_CCK_RATE_11M | ZD_CCK_PREA_SHORT,
	  .flags = IEEE80211_RATE_SHORT_PREAMBLE पूर्ण,
	अणु .bitrate = 60,
	  .hw_value = ZD_OFDM_RATE_6M,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 90,
	  .hw_value = ZD_OFDM_RATE_9M,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 120,
	  .hw_value = ZD_OFDM_RATE_12M,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 180,
	  .hw_value = ZD_OFDM_RATE_18M,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 240,
	  .hw_value = ZD_OFDM_RATE_24M,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 360,
	  .hw_value = ZD_OFDM_RATE_36M,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 480,
	  .hw_value = ZD_OFDM_RATE_48M,
	  .flags = 0 पूर्ण,
	अणु .bitrate = 540,
	  .hw_value = ZD_OFDM_RATE_54M,
	  .flags = 0 पूर्ण,
पूर्ण;

/*
 * Zydas retry rates table. Each line is listed in the same order as
 * in zd_rates[] and contains all the rate used when a packet is sent
 * starting with a given rates. Let's consider an example :
 *
 * "11 Mbits : 4, 3, 2, 1, 0" means :
 * - packet is sent using 4 dअगरferent rates
 * - 1st rate is index 3 (ie 11 Mbits)
 * - 2nd rate is index 2 (ie 5.5 Mbits)
 * - 3rd rate is index 1 (ie 2 Mbits)
 * - 4th rate is index 0 (ie 1 Mbits)
 */

अटल स्थिर काष्ठा tx_retry_rate zd_retry_rates[] = अणु
	अणु /*  1 Mbits */	1, अणु 0 पूर्णपूर्ण,
	अणु /*  2 Mbits */	2, अणु 1,  0 पूर्णपूर्ण,
	अणु /*  5.5 Mbits */	3, अणु 2,  1, 0 पूर्णपूर्ण,
	अणु /* 11 Mbits */	4, अणु 3,  2, 1, 0 पूर्णपूर्ण,
	अणु /*  6 Mbits */	5, अणु 4,  3, 2, 1, 0 पूर्णपूर्ण,
	अणु /*  9 Mbits */	6, अणु 5,  4, 3, 2, 1, 0पूर्णपूर्ण,
	अणु /* 12 Mbits */	5, अणु 6,  3, 2, 1, 0 पूर्णपूर्ण,
	अणु /* 18 Mbits */	6, अणु 7,  6, 3, 2, 1, 0 पूर्णपूर्ण,
	अणु /* 24 Mbits */	6, अणु 8,  6, 3, 2, 1, 0 पूर्णपूर्ण,
	अणु /* 36 Mbits */	7, अणु 9,  8, 6, 3, 2, 1, 0 पूर्णपूर्ण,
	अणु /* 48 Mbits */	8, अणु10,  9, 8, 6, 3, 2, 1, 0 पूर्णपूर्ण,
	अणु /* 54 Mbits */	9, अणु11, 10, 9, 8, 6, 3, 2, 1, 0 पूर्णपूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_channel zd_channels[] = अणु
	अणु .center_freq = 2412, .hw_value = 1 पूर्ण,
	अणु .center_freq = 2417, .hw_value = 2 पूर्ण,
	अणु .center_freq = 2422, .hw_value = 3 पूर्ण,
	अणु .center_freq = 2427, .hw_value = 4 पूर्ण,
	अणु .center_freq = 2432, .hw_value = 5 पूर्ण,
	अणु .center_freq = 2437, .hw_value = 6 पूर्ण,
	अणु .center_freq = 2442, .hw_value = 7 पूर्ण,
	अणु .center_freq = 2447, .hw_value = 8 पूर्ण,
	अणु .center_freq = 2452, .hw_value = 9 पूर्ण,
	अणु .center_freq = 2457, .hw_value = 10 पूर्ण,
	अणु .center_freq = 2462, .hw_value = 11 पूर्ण,
	अणु .center_freq = 2467, .hw_value = 12 पूर्ण,
	अणु .center_freq = 2472, .hw_value = 13 पूर्ण,
	अणु .center_freq = 2484, .hw_value = 14 पूर्ण,
पूर्ण;

अटल व्योम housekeeping_init(काष्ठा zd_mac *mac);
अटल व्योम housekeeping_enable(काष्ठा zd_mac *mac);
अटल व्योम housekeeping_disable(काष्ठा zd_mac *mac);
अटल व्योम beacon_init(काष्ठा zd_mac *mac);
अटल व्योम beacon_enable(काष्ठा zd_mac *mac);
अटल व्योम beacon_disable(काष्ठा zd_mac *mac);
अटल व्योम set_rts_cts(काष्ठा zd_mac *mac, अचिन्हित पूर्णांक लघु_preamble);
अटल पूर्णांक zd_mac_config_beacon(काष्ठा ieee80211_hw *hw,
				काष्ठा sk_buff *beacon, bool in_पूर्णांकr);

अटल पूर्णांक zd_reg2alpha2(u8 regकरोमुख्य, अक्षर *alpha2)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा zd_reg_alpha2_map *reg_map;
	क्रम (i = 0; i < ARRAY_SIZE(reg_alpha2_map); i++) अणु
		reg_map = &reg_alpha2_map[i];
		अगर (regकरोमुख्य == reg_map->reg) अणु
			alpha2[0] = reg_map->alpha2[0];
			alpha2[1] = reg_map->alpha2[1];
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक zd_check_संकेत(काष्ठा ieee80211_hw *hw, पूर्णांक संकेत)
अणु
	काष्ठा zd_mac *mac = zd_hw_mac(hw);

	dev_dbg_f_cond(zd_mac_dev(mac), संकेत < 0 || संकेत > 100,
			"%s: signal value from device not in range 0..100, "
			"but %d.\n", __func__, संकेत);

	अगर (संकेत < 0)
		संकेत = 0;
	अन्यथा अगर (संकेत > 100)
		संकेत = 100;

	वापस संकेत;
पूर्ण

पूर्णांक zd_mac_preinit_hw(काष्ठा ieee80211_hw *hw)
अणु
	पूर्णांक r;
	u8 addr[ETH_ALEN];
	काष्ठा zd_mac *mac = zd_hw_mac(hw);

	r = zd_chip_पढ़ो_mac_addr_fw(&mac->chip, addr);
	अगर (r)
		वापस r;

	SET_IEEE80211_PERM_ADDR(hw, addr);

	वापस 0;
पूर्ण

पूर्णांक zd_mac_init_hw(काष्ठा ieee80211_hw *hw)
अणु
	पूर्णांक r;
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	काष्ठा zd_chip *chip = &mac->chip;
	अक्षर alpha2[2];
	u8 शेष_regकरोमुख्य;

	r = zd_chip_enable_पूर्णांक(chip);
	अगर (r)
		जाओ out;
	r = zd_chip_init_hw(chip);
	अगर (r)
		जाओ disable_पूर्णांक;

	ZD_ASSERT(!irqs_disabled());

	r = zd_पढ़ो_regकरोमुख्य(chip, &शेष_regकरोमुख्य);
	अगर (r)
		जाओ disable_पूर्णांक;
	spin_lock_irq(&mac->lock);
	mac->regकरोमुख्य = mac->शेष_regकरोमुख्य = शेष_regकरोमुख्य;
	spin_unlock_irq(&mac->lock);

	/* We must inक्रमm the device that we are करोing encryption/decryption in
	 * software at the moment. */
	r = zd_set_encryption_type(chip, ENC_SNIFFER);
	अगर (r)
		जाओ disable_पूर्णांक;

	r = zd_reg2alpha2(mac->regकरोमुख्य, alpha2);
	अगर (r)
		जाओ disable_पूर्णांक;

	r = regulatory_hपूर्णांक(hw->wiphy, alpha2);
disable_पूर्णांक:
	zd_chip_disable_पूर्णांक(chip);
out:
	वापस r;
पूर्ण

व्योम zd_mac_clear(काष्ठा zd_mac *mac)
अणु
	flush_workqueue(zd_workqueue);
	zd_chip_clear(&mac->chip);
	ZD_MEMCLEAR(mac, माप(काष्ठा zd_mac));
पूर्ण

अटल पूर्णांक set_rx_filter(काष्ठा zd_mac *mac)
अणु
	अचिन्हित दीर्घ flags;
	u32 filter = STA_RX_FILTER;

	spin_lock_irqsave(&mac->lock, flags);
	अगर (mac->pass_ctrl)
		filter |= RX_FILTER_CTRL;
	spin_unlock_irqrestore(&mac->lock, flags);

	वापस zd_ioग_लिखो32(&mac->chip, CR_RX_FILTER, filter);
पूर्ण

अटल पूर्णांक set_mac_and_bssid(काष्ठा zd_mac *mac)
अणु
	पूर्णांक r;

	अगर (!mac->vअगर)
		वापस -1;

	r = zd_ग_लिखो_mac_addr(&mac->chip, mac->vअगर->addr);
	अगर (r)
		वापस r;

	/* Venकरोr driver after setting MAC either sets BSSID क्रम AP or
	 * filter क्रम other modes.
	 */
	अगर (mac->type != NL80211_IFTYPE_AP)
		वापस set_rx_filter(mac);
	अन्यथा
		वापस zd_ग_लिखो_bssid(&mac->chip, mac->vअगर->addr);
पूर्ण

अटल पूर्णांक set_mc_hash(काष्ठा zd_mac *mac)
अणु
	काष्ठा zd_mc_hash hash;
	zd_mc_clear(&hash);
	वापस zd_chip_set_multicast_hash(&mac->chip, &hash);
पूर्ण

पूर्णांक zd_op_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	काष्ठा zd_chip *chip = &mac->chip;
	काष्ठा zd_usb *usb = &chip->usb;
	पूर्णांक r;

	अगर (!usb->initialized) अणु
		r = zd_usb_init_hw(usb);
		अगर (r)
			जाओ out;
	पूर्ण

	r = zd_chip_enable_पूर्णांक(chip);
	अगर (r < 0)
		जाओ out;

	r = zd_chip_set_basic_rates(chip, CR_RATES_80211B | CR_RATES_80211G);
	अगर (r < 0)
		जाओ disable_पूर्णांक;
	r = set_rx_filter(mac);
	अगर (r)
		जाओ disable_पूर्णांक;
	r = set_mc_hash(mac);
	अगर (r)
		जाओ disable_पूर्णांक;

	/* Wait after setting the multicast hash table and घातering on
	 * the radio otherwise पूर्णांकerface bring up will fail. This matches
	 * what the venकरोr driver did.
	 */
	msleep(10);

	r = zd_chip_चयन_radio_on(chip);
	अगर (r < 0) अणु
		dev_err(zd_chip_dev(chip),
			"%s: failed to set radio on\n", __func__);
		जाओ disable_पूर्णांक;
	पूर्ण
	r = zd_chip_enable_rxtx(chip);
	अगर (r < 0)
		जाओ disable_radio;
	r = zd_chip_enable_hwपूर्णांक(chip);
	अगर (r < 0)
		जाओ disable_rxtx;

	housekeeping_enable(mac);
	beacon_enable(mac);
	set_bit(ZD_DEVICE_RUNNING, &mac->flags);
	वापस 0;
disable_rxtx:
	zd_chip_disable_rxtx(chip);
disable_radio:
	zd_chip_चयन_radio_off(chip);
disable_पूर्णांक:
	zd_chip_disable_पूर्णांक(chip);
out:
	वापस r;
पूर्ण

व्योम zd_op_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	काष्ठा zd_chip *chip = &mac->chip;
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head *ack_रुको_queue = &mac->ack_रुको_queue;

	clear_bit(ZD_DEVICE_RUNNING, &mac->flags);

	/* The order here deliberately is a little dअगरferent from the खोलो()
	 * method, since we need to make sure there is no opportunity क्रम RX
	 * frames to be processed by mac80211 after we have stopped it.
	 */

	zd_chip_disable_rxtx(chip);
	beacon_disable(mac);
	housekeeping_disable(mac);
	flush_workqueue(zd_workqueue);

	zd_chip_disable_hwपूर्णांक(chip);
	zd_chip_चयन_radio_off(chip);
	zd_chip_disable_पूर्णांक(chip);


	जबतक ((skb = skb_dequeue(ack_रुको_queue)))
		dev_kमुक्त_skb_any(skb);
पूर्ण

पूर्णांक zd_restore_settings(काष्ठा zd_mac *mac)
अणु
	काष्ठा sk_buff *beacon;
	काष्ठा zd_mc_hash multicast_hash;
	अचिन्हित पूर्णांक लघु_preamble;
	पूर्णांक r, beacon_पूर्णांकerval, beacon_period;
	u8 channel;

	dev_dbg_f(zd_mac_dev(mac), "\n");

	spin_lock_irq(&mac->lock);
	multicast_hash = mac->multicast_hash;
	लघु_preamble = mac->लघु_preamble;
	beacon_पूर्णांकerval = mac->beacon.पूर्णांकerval;
	beacon_period = mac->beacon.period;
	channel = mac->channel;
	spin_unlock_irq(&mac->lock);

	r = set_mac_and_bssid(mac);
	अगर (r < 0) अणु
		dev_dbg_f(zd_mac_dev(mac), "set_mac_and_bssid failed, %d\n", r);
		वापस r;
	पूर्ण

	r = zd_chip_set_channel(&mac->chip, channel);
	अगर (r < 0) अणु
		dev_dbg_f(zd_mac_dev(mac), "zd_chip_set_channel failed, %d\n",
			  r);
		वापस r;
	पूर्ण

	set_rts_cts(mac, लघु_preamble);

	r = zd_chip_set_multicast_hash(&mac->chip, &multicast_hash);
	अगर (r < 0) अणु
		dev_dbg_f(zd_mac_dev(mac),
			  "zd_chip_set_multicast_hash failed, %d\n", r);
		वापस r;
	पूर्ण

	अगर (mac->type == NL80211_IFTYPE_MESH_POINT ||
	    mac->type == NL80211_IFTYPE_ADHOC ||
	    mac->type == NL80211_IFTYPE_AP) अणु
		अगर (mac->vअगर != शून्य) अणु
			beacon = ieee80211_beacon_get(mac->hw, mac->vअगर);
			अगर (beacon)
				zd_mac_config_beacon(mac->hw, beacon, false);
		पूर्ण

		zd_set_beacon_पूर्णांकerval(&mac->chip, beacon_पूर्णांकerval,
					beacon_period, mac->type);

		spin_lock_irq(&mac->lock);
		mac->beacon.last_update = jअगरfies;
		spin_unlock_irq(&mac->lock);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * zd_mac_tx_status - reports tx status of a packet अगर required
 * @hw: a &काष्ठा ieee80211_hw poपूर्णांकer
 * @skb: a sk-buffer
 * @ackssi: ACK संकेत strength
 * @tx_status: success and/or retry
 *
 * This inक्रमmation calls ieee80211_tx_status_irqsafe() अगर required by the
 * control inक्रमmation. It copies the control inक्रमmation पूर्णांकo the status
 * inक्रमmation.
 *
 * If no status inक्रमmation has been requested, the skb is मुक्तd.
 */
अटल व्योम zd_mac_tx_status(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb,
		      पूर्णांक ackssi, काष्ठा tx_status *tx_status)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	पूर्णांक i;
	पूर्णांक success = 1, retry = 1;
	पूर्णांक first_idx;
	स्थिर काष्ठा tx_retry_rate *retries;

	ieee80211_tx_info_clear_status(info);

	अगर (tx_status) अणु
		success = !tx_status->failure;
		retry = tx_status->retry + success;
	पूर्ण

	अगर (success) अणु
		/* success */
		info->flags |= IEEE80211_TX_STAT_ACK;
	पूर्ण अन्यथा अणु
		/* failure */
		info->flags &= ~IEEE80211_TX_STAT_ACK;
	पूर्ण

	first_idx = info->status.rates[0].idx;
	ZD_ASSERT(0<=first_idx && first_idx<ARRAY_SIZE(zd_retry_rates));
	retries = &zd_retry_rates[first_idx];
	ZD_ASSERT(1 <= retry && retry <= retries->count);

	info->status.rates[0].idx = retries->rate[0];
	info->status.rates[0].count = 1; // (retry > 1 ? 2 : 1);

	क्रम (i=1; i<IEEE80211_TX_MAX_RATES-1 && i<retry; i++) अणु
		info->status.rates[i].idx = retries->rate[i];
		info->status.rates[i].count = 1; // ((i==retry-1) && success ? 1:2);
	पूर्ण
	क्रम (; i<IEEE80211_TX_MAX_RATES && i<retry; i++) अणु
		info->status.rates[i].idx = retries->rate[retry - 1];
		info->status.rates[i].count = 1; // (success ? 1:2);
	पूर्ण
	अगर (i<IEEE80211_TX_MAX_RATES)
		info->status.rates[i].idx = -1; /* terminate */

	info->status.ack_संकेत = zd_check_संकेत(hw, ackssi);
	ieee80211_tx_status_irqsafe(hw, skb);
पूर्ण

/**
 * zd_mac_tx_failed - callback क्रम failed frames
 * @urb: poपूर्णांकer to the urb काष्ठाure
 *
 * This function is called अगर a frame couldn't be successfully
 * transferred. The first frame from the tx queue, will be selected and
 * reported as error to the upper layers.
 */
व्योम zd_mac_tx_failed(काष्ठा urb *urb)
अणु
	काष्ठा ieee80211_hw * hw = zd_usb_to_hw(urb->context);
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	काष्ठा sk_buff_head *q = &mac->ack_रुको_queue;
	काष्ठा sk_buff *skb;
	काष्ठा tx_status *tx_status = (काष्ठा tx_status *)urb->transfer_buffer;
	अचिन्हित दीर्घ flags;
	पूर्णांक success = !tx_status->failure;
	पूर्णांक retry = tx_status->retry + success;
	पूर्णांक found = 0;
	पूर्णांक i, position = 0;

	spin_lock_irqsave(&q->lock, flags);

	skb_queue_walk(q, skb) अणु
		काष्ठा ieee80211_hdr *tx_hdr;
		काष्ठा ieee80211_tx_info *info;
		पूर्णांक first_idx, final_idx;
		स्थिर काष्ठा tx_retry_rate *retries;
		u8 final_rate;

		position ++;

		/* अगर the hardware reports a failure and we had a 802.11 ACK
		 * pending, then we skip the first skb when searching क्रम a
		 * matching frame */
		अगर (tx_status->failure && mac->ack_pending &&
		    skb_queue_is_first(q, skb)) अणु
			जारी;
		पूर्ण

		tx_hdr = (काष्ठा ieee80211_hdr *)skb->data;

		/* we skip all frames not matching the reported destination */
		अगर (unlikely(!ether_addr_equal(tx_hdr->addr1, tx_status->mac)))
			जारी;

		/* we skip all frames not matching the reported final rate */

		info = IEEE80211_SKB_CB(skb);
		first_idx = info->status.rates[0].idx;
		ZD_ASSERT(0<=first_idx && first_idx<ARRAY_SIZE(zd_retry_rates));
		retries = &zd_retry_rates[first_idx];
		अगर (retry <= 0 || retry > retries->count)
			जारी;

		final_idx = retries->rate[retry - 1];
		final_rate = zd_rates[final_idx].hw_value;

		अगर (final_rate != tx_status->rate) अणु
			जारी;
		पूर्ण

		found = 1;
		अवरोध;
	पूर्ण

	अगर (found) अणु
		क्रम (i=1; i<=position; i++) अणु
			skb = __skb_dequeue(q);
			zd_mac_tx_status(hw, skb,
					 mac->ack_pending ? mac->ack_संकेत : 0,
					 i == position ? tx_status : शून्य);
			mac->ack_pending = 0;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&q->lock, flags);
पूर्ण

/**
 * zd_mac_tx_to_dev - callback क्रम USB layer
 * @skb: a &sk_buff poपूर्णांकer
 * @error: error value, 0 अगर transmission successful
 *
 * Inक्रमms the MAC layer that the frame has successfully transferred to the
 * device. If an ACK is required and the transfer to the device has been
 * successful, the packets are put on the @ack_रुको_queue with
 * the control set हटाओd.
 */
व्योम zd_mac_tx_to_dev(काष्ठा sk_buff *skb, पूर्णांक error)
अणु
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hw *hw = info->rate_driver_data[0];
	काष्ठा zd_mac *mac = zd_hw_mac(hw);

	ieee80211_tx_info_clear_status(info);

	skb_pull(skb, माप(काष्ठा zd_ctrlset));
	अगर (unlikely(error ||
	    (info->flags & IEEE80211_TX_CTL_NO_ACK))) अणु
		/*
		 * FIXME : करो we need to fill in anything ?
		 */
		ieee80211_tx_status_irqsafe(hw, skb);
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff_head *q = &mac->ack_रुको_queue;

		skb_queue_tail(q, skb);
		जबतक (skb_queue_len(q) > ZD_MAC_MAX_ACK_WAITERS) अणु
			zd_mac_tx_status(hw, skb_dequeue(q),
					 mac->ack_pending ? mac->ack_संकेत : 0,
					 शून्य);
			mac->ack_pending = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक zd_calc_tx_length_us(u8 *service, u8 zd_rate, u16 tx_length)
अणु
	/* ZD_PURE_RATE() must be used to हटाओ the modulation type flag of
	 * the zd-rate values.
	 */
	अटल स्थिर u8 rate_भागisor[] = अणु
		[ZD_PURE_RATE(ZD_CCK_RATE_1M)]   =  1,
		[ZD_PURE_RATE(ZD_CCK_RATE_2M)]	 =  2,
		/* Bits must be द्विगुनd. */
		[ZD_PURE_RATE(ZD_CCK_RATE_5_5M)] = 11,
		[ZD_PURE_RATE(ZD_CCK_RATE_11M)]	 = 11,
		[ZD_PURE_RATE(ZD_OFDM_RATE_6M)]  =  6,
		[ZD_PURE_RATE(ZD_OFDM_RATE_9M)]  =  9,
		[ZD_PURE_RATE(ZD_OFDM_RATE_12M)] = 12,
		[ZD_PURE_RATE(ZD_OFDM_RATE_18M)] = 18,
		[ZD_PURE_RATE(ZD_OFDM_RATE_24M)] = 24,
		[ZD_PURE_RATE(ZD_OFDM_RATE_36M)] = 36,
		[ZD_PURE_RATE(ZD_OFDM_RATE_48M)] = 48,
		[ZD_PURE_RATE(ZD_OFDM_RATE_54M)] = 54,
	पूर्ण;

	u32 bits = (u32)tx_length * 8;
	u32 भागisor;

	भागisor = rate_भागisor[ZD_PURE_RATE(zd_rate)];
	अगर (भागisor == 0)
		वापस -EINVAL;

	चयन (zd_rate) अणु
	हाल ZD_CCK_RATE_5_5M:
		bits = (2*bits) + 10; /* round up to the next पूर्णांकeger */
		अवरोध;
	हाल ZD_CCK_RATE_11M:
		अगर (service) अणु
			u32 t = bits % 11;
			*service &= ~ZD_PLCP_SERVICE_LENGTH_EXTENSION;
			अगर (0 < t && t <= 3) अणु
				*service |= ZD_PLCP_SERVICE_LENGTH_EXTENSION;
			पूर्ण
		पूर्ण
		bits += 10; /* round up to the next पूर्णांकeger */
		अवरोध;
	पूर्ण

	वापस bits/भागisor;
पूर्ण

अटल व्योम cs_set_control(काष्ठा zd_mac *mac, काष्ठा zd_ctrlset *cs,
	                   काष्ठा ieee80211_hdr *header,
	                   काष्ठा ieee80211_tx_info *info)
अणु
	/*
	 * CONTROL TODO:
	 * - अगर backoff needed, enable bit 0
	 * - अगर burst (backoff not needed) disable bit 0
	 */

	cs->control = 0;

	/* First fragment */
	अगर (info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT)
		cs->control |= ZD_CS_NEED_RANDOM_BACKOFF;

	/* No ACK expected (multicast, etc.) */
	अगर (info->flags & IEEE80211_TX_CTL_NO_ACK)
		cs->control |= ZD_CS_NO_ACK;

	/* PS-POLL */
	अगर (ieee80211_is_pspoll(header->frame_control))
		cs->control |= ZD_CS_PS_POLL_FRAME;

	अगर (info->control.rates[0].flags & IEEE80211_TX_RC_USE_RTS_CTS)
		cs->control |= ZD_CS_RTS;

	अगर (info->control.rates[0].flags & IEEE80211_TX_RC_USE_CTS_PROTECT)
		cs->control |= ZD_CS_SELF_CTS;

	/* FIXME: Management frame? */
पूर्ण

अटल bool zd_mac_match_cur_beacon(काष्ठा zd_mac *mac, काष्ठा sk_buff *beacon)
अणु
	अगर (!mac->beacon.cur_beacon)
		वापस false;

	अगर (mac->beacon.cur_beacon->len != beacon->len)
		वापस false;

	वापस !स_भेद(beacon->data, mac->beacon.cur_beacon->data, beacon->len);
पूर्ण

अटल व्योम zd_mac_मुक्त_cur_beacon_locked(काष्ठा zd_mac *mac)
अणु
	ZD_ASSERT(mutex_is_locked(&mac->chip.mutex));

	kमुक्त_skb(mac->beacon.cur_beacon);
	mac->beacon.cur_beacon = शून्य;
पूर्ण

अटल व्योम zd_mac_मुक्त_cur_beacon(काष्ठा zd_mac *mac)
अणु
	mutex_lock(&mac->chip.mutex);
	zd_mac_मुक्त_cur_beacon_locked(mac);
	mutex_unlock(&mac->chip.mutex);
पूर्ण

अटल पूर्णांक zd_mac_config_beacon(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *beacon,
				bool in_पूर्णांकr)
अणु
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	पूर्णांक r, ret, num_cmds, req_pos = 0;
	u32 पंचांगp, j = 0;
	/* 4 more bytes क्रम tail CRC */
	u32 full_len = beacon->len + 4;
	अचिन्हित दीर्घ end_jअगरfies, message_jअगरfies;
	काष्ठा zd_ioreq32 *ioreqs;

	mutex_lock(&mac->chip.mutex);

	/* Check अगर hw alपढ़ोy has this beacon. */
	अगर (zd_mac_match_cur_beacon(mac, beacon)) अणु
		r = 0;
		जाओ out_noमुक्त;
	पूर्ण

	/* Alloc memory क्रम full beacon ग_लिखो at once. */
	num_cmds = 1 + zd_chip_is_zd1211b(&mac->chip) + full_len;
	ioreqs = kदो_स्मृति_array(num_cmds, माप(काष्ठा zd_ioreq32),
			       GFP_KERNEL);
	अगर (!ioreqs) अणु
		r = -ENOMEM;
		जाओ out_noमुक्त;
	पूर्ण

	r = zd_ioग_लिखो32_locked(&mac->chip, 0, CR_BCN_FIFO_SEMAPHORE);
	अगर (r < 0)
		जाओ out;
	r = zd_ioपढ़ो32_locked(&mac->chip, &पंचांगp, CR_BCN_FIFO_SEMAPHORE);
	अगर (r < 0)
		जाओ release_sema;
	अगर (in_पूर्णांकr && पंचांगp & 0x2) अणु
		r = -EBUSY;
		जाओ release_sema;
	पूर्ण

	end_jअगरfies = jअगरfies + HZ / 2; /*~500ms*/
	message_jअगरfies = jअगरfies + HZ / 10; /*~100ms*/
	जबतक (पंचांगp & 0x2) अणु
		r = zd_ioपढ़ो32_locked(&mac->chip, &पंचांगp, CR_BCN_FIFO_SEMAPHORE);
		अगर (r < 0)
			जाओ release_sema;
		अगर (समय_is_beक्रमe_eq_jअगरfies(message_jअगरfies)) अणु
			message_jअगरfies = jअगरfies + HZ / 10;
			dev_err(zd_mac_dev(mac),
					"CR_BCN_FIFO_SEMAPHORE not ready\n");
			अगर (समय_is_beक्रमe_eq_jअगरfies(end_jअगरfies))  अणु
				dev_err(zd_mac_dev(mac),
						"Giving up beacon config.\n");
				r = -ETIMEDOUT;
				जाओ reset_device;
			पूर्ण
		पूर्ण
		msleep(20);
	पूर्ण

	ioreqs[req_pos].addr = CR_BCN_FIFO;
	ioreqs[req_pos].value = full_len - 1;
	req_pos++;
	अगर (zd_chip_is_zd1211b(&mac->chip)) अणु
		ioreqs[req_pos].addr = CR_BCN_LENGTH;
		ioreqs[req_pos].value = full_len - 1;
		req_pos++;
	पूर्ण

	क्रम (j = 0 ; j < beacon->len; j++) अणु
		ioreqs[req_pos].addr = CR_BCN_FIFO;
		ioreqs[req_pos].value = *((u8 *)(beacon->data + j));
		req_pos++;
	पूर्ण

	क्रम (j = 0; j < 4; j++) अणु
		ioreqs[req_pos].addr = CR_BCN_FIFO;
		ioreqs[req_pos].value = 0x0;
		req_pos++;
	पूर्ण

	BUG_ON(req_pos != num_cmds);

	r = zd_ioग_लिखो32a_locked(&mac->chip, ioreqs, num_cmds);

release_sema:
	/*
	 * Try very hard to release device beacon semaphore, as otherwise
	 * device/driver can be left in unusable state.
	 */
	end_jअगरfies = jअगरfies + HZ / 2; /*~500ms*/
	ret = zd_ioग_लिखो32_locked(&mac->chip, 1, CR_BCN_FIFO_SEMAPHORE);
	जबतक (ret < 0) अणु
		अगर (in_पूर्णांकr || समय_is_beक्रमe_eq_jअगरfies(end_jअगरfies)) अणु
			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		msleep(20);
		ret = zd_ioग_लिखो32_locked(&mac->chip, 1, CR_BCN_FIFO_SEMAPHORE);
	पूर्ण

	अगर (ret < 0)
		dev_err(zd_mac_dev(mac), "Could not release "
					 "CR_BCN_FIFO_SEMAPHORE!\n");
	अगर (r < 0 || ret < 0) अणु
		अगर (r >= 0)
			r = ret;

		/* We करोn't know अगर beacon was written successfully or not,
		 * so clear current. */
		zd_mac_मुक्त_cur_beacon_locked(mac);

		जाओ out;
	पूर्ण

	/* Beacon has now been written successfully, update current. */
	zd_mac_मुक्त_cur_beacon_locked(mac);
	mac->beacon.cur_beacon = beacon;
	beacon = शून्य;

	/* 802.11b/g 2.4G CCK 1Mb
	 * 802.11a, not yet implemented, uses dअगरferent values (see GPL venकरोr
	 * driver)
	 */
	r = zd_ioग_लिखो32_locked(&mac->chip, 0x00000400 | (full_len << 19),
				CR_BCN_PLCP_CFG);
out:
	kमुक्त(ioreqs);
out_noमुक्त:
	kमुक्त_skb(beacon);
	mutex_unlock(&mac->chip.mutex);

	वापस r;

reset_device:
	zd_mac_मुक्त_cur_beacon_locked(mac);
	kमुक्त_skb(beacon);

	mutex_unlock(&mac->chip.mutex);
	kमुक्त(ioreqs);

	/* semaphore stuck, reset device to aव्योम fw मुक्तze later */
	dev_warn(zd_mac_dev(mac), "CR_BCN_FIFO_SEMAPHORE stuck, "
				  "resetting device...");
	usb_queue_reset_device(mac->chip.usb.पूर्णांकf);

	वापस r;
पूर्ण

अटल पूर्णांक fill_ctrlset(काष्ठा zd_mac *mac,
			काष्ठा sk_buff *skb)
अणु
	पूर्णांक r;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	अचिन्हित पूर्णांक frag_len = skb->len + FCS_LEN;
	अचिन्हित पूर्णांक packet_length;
	काष्ठा ieee80211_rate *txrate;
	काष्ठा zd_ctrlset *cs = skb_push(skb, माप(काष्ठा zd_ctrlset));
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	ZD_ASSERT(frag_len <= 0xffff);

	/*
	 * Firmware computes the duration itself (क्रम all frames except PSPoll)
	 * and needs the field set to 0 at input, otherwise firmware messes up
	 * duration_id and sets bits 14 and 15 on.
	 */
	अगर (!ieee80211_is_pspoll(hdr->frame_control))
		hdr->duration_id = 0;

	txrate = ieee80211_get_tx_rate(mac->hw, info);

	cs->modulation = txrate->hw_value;
	अगर (info->control.rates[0].flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
		cs->modulation = txrate->hw_value_लघु;

	cs->tx_length = cpu_to_le16(frag_len);

	cs_set_control(mac, cs, hdr, info);

	packet_length = frag_len + माप(काष्ठा zd_ctrlset) + 10;
	ZD_ASSERT(packet_length <= 0xffff);
	/* ZD1211B: Computing the length dअगरference this way, gives us
	 * flexibility to compute the packet length.
	 */
	cs->packet_length = cpu_to_le16(zd_chip_is_zd1211b(&mac->chip) ?
			packet_length - frag_len : packet_length);

	/*
	 * CURRENT LENGTH:
	 * - transmit frame length in microseconds
	 * - seems to be derived from frame length
	 * - see Cal_Us_Service() in zdअंतरभूतf.h
	 * - अगर macp->bTxBurstEnable is enabled, then multiply by 4
	 *  - bTxBurstEnable is never set in the venकरोr driver
	 *
	 * SERVICE:
	 * - "for PLCP configuration"
	 * - always 0 except in some situations at 802.11b 11M
	 * - see line 53 of zdअंतरभूतf.h
	 */
	cs->service = 0;
	r = zd_calc_tx_length_us(&cs->service, ZD_RATE(cs->modulation),
		                 le16_to_cpu(cs->tx_length));
	अगर (r < 0)
		वापस r;
	cs->current_length = cpu_to_le16(r);
	cs->next_frame_length = 0;

	वापस 0;
पूर्ण

/**
 * zd_op_tx - transmits a network frame to the device
 *
 * @hw: a &काष्ठा ieee80211_hw poपूर्णांकer
 * @control: the control काष्ठाure
 * @skb: socket buffer
 *
 * This function transmit an IEEE 802.11 network frame to the device. The
 * control block of the skbuff will be initialized. If necessary the incoming
 * mac80211 queues will be stopped.
 */
अटल व्योम zd_op_tx(काष्ठा ieee80211_hw *hw,
		     काष्ठा ieee80211_tx_control *control,
		     काष्ठा sk_buff *skb)
अणु
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	पूर्णांक r;

	r = fill_ctrlset(mac, skb);
	अगर (r)
		जाओ fail;

	info->rate_driver_data[0] = hw;

	r = zd_usb_tx(&mac->chip.usb, skb);
	अगर (r)
		जाओ fail;
	वापस;

fail:
	dev_kमुक्त_skb(skb);
पूर्ण

/**
 * filter_ack - filters incoming packets क्रम acknowledgements
 * @hw: a &काष्ठा ieee80211_hw poपूर्णांकer
 * @rx_hdr: received header
 * @stats: the status क्रम the received packet
 *
 * This functions looks क्रम ACK packets and tries to match them with the
 * frames in the tx queue. If a match is found the frame will be dequeued and
 * the upper layers is inक्रमmed about the successful transmission. If
 * mac80211 queues have been stopped and the number of frames still to be
 * transmitted is low the queues will be खोलोed again.
 *
 * Returns 1 अगर the frame was an ACK, 0 अगर it was ignored.
 */
अटल पूर्णांक filter_ack(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_hdr *rx_hdr,
		      काष्ठा ieee80211_rx_status *stats)
अणु
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head *q;
	अचिन्हित दीर्घ flags;
	पूर्णांक found = 0;
	पूर्णांक i, position = 0;

	अगर (!ieee80211_is_ack(rx_hdr->frame_control))
		वापस 0;

	q = &mac->ack_रुको_queue;
	spin_lock_irqsave(&q->lock, flags);
	skb_queue_walk(q, skb) अणु
		काष्ठा ieee80211_hdr *tx_hdr;

		position ++;

		अगर (mac->ack_pending && skb_queue_is_first(q, skb))
		    जारी;

		tx_hdr = (काष्ठा ieee80211_hdr *)skb->data;
		अगर (likely(ether_addr_equal(tx_hdr->addr2, rx_hdr->addr1)))
		अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found) अणु
		क्रम (i=1; i<position; i++) अणु
			skb = __skb_dequeue(q);
			zd_mac_tx_status(hw, skb,
					 mac->ack_pending ? mac->ack_संकेत : 0,
					 शून्य);
			mac->ack_pending = 0;
		पूर्ण

		mac->ack_pending = 1;
		mac->ack_संकेत = stats->संकेत;

		/* Prevent pending tx-packet on AP-mode */
		अगर (mac->type == NL80211_IFTYPE_AP) अणु
			skb = __skb_dequeue(q);
			zd_mac_tx_status(hw, skb, mac->ack_संकेत, शून्य);
			mac->ack_pending = 0;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&q->lock, flags);
	वापस 1;
पूर्ण

पूर्णांक zd_mac_rx(काष्ठा ieee80211_hw *hw, स्थिर u8 *buffer, अचिन्हित पूर्णांक length)
अणु
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	काष्ठा ieee80211_rx_status stats;
	स्थिर काष्ठा rx_status *status;
	काष्ठा sk_buff *skb;
	पूर्णांक bad_frame = 0;
	__le16 fc;
	पूर्णांक need_padding;
	पूर्णांक i;
	u8 rate;

	अगर (length < ZD_PLCP_HEADER_SIZE + 10 /* IEEE80211_1ADDR_LEN */ +
	             FCS_LEN + माप(काष्ठा rx_status))
		वापस -EINVAL;

	स_रखो(&stats, 0, माप(stats));

	/* Note about pass_failed_fcs and pass_ctrl access below:
	 * mac locking पूर्णांकentionally omitted here, as this is the only unlocked
	 * पढ़ोer and the only ग_लिखोr is configure_filter. Plus, अगर there were
	 * any races accessing these variables, it wouldn't really matter.
	 * If mac80211 ever provides a way क्रम us to access filter flags
	 * from outside configure_filter, we could improve on this. Also, this
	 * situation may change once we implement some kind of DMA-पूर्णांकo-skb
	 * RX path. */

	/* Caller has to ensure that length >= माप(काष्ठा rx_status). */
	status = (काष्ठा rx_status *)
		(buffer + (length - माप(काष्ठा rx_status)));
	अगर (status->frame_status & ZD_RX_ERROR) अणु
		अगर (mac->pass_failed_fcs &&
				(status->frame_status & ZD_RX_CRC32_ERROR)) अणु
			stats.flag |= RX_FLAG_FAILED_FCS_CRC;
			bad_frame = 1;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	stats.freq = zd_channels[_zd_chip_get_channel(&mac->chip) - 1].center_freq;
	stats.band = NL80211_BAND_2GHZ;
	stats.संकेत = zd_check_संकेत(hw, status->संकेत_strength);

	rate = zd_rx_rate(buffer, status);

	/* toकरो: वापस index in the big चयनes in zd_rx_rate instead */
	क्रम (i = 0; i < mac->band.n_bitrates; i++)
		अगर (rate == mac->band.bitrates[i].hw_value)
			stats.rate_idx = i;

	length -= ZD_PLCP_HEADER_SIZE + माप(काष्ठा rx_status);
	buffer += ZD_PLCP_HEADER_SIZE;

	/* Except क्रम bad frames, filter each frame to see अगर it is an ACK, in
	 * which हाल our पूर्णांकernal TX tracking is updated. Normally we then
	 * bail here as there's no need to pass ACKs on up to the stack, but
	 * there is also the हाल where the stack has requested us to pass
	 * control frames on up (pass_ctrl) which we must consider. */
	अगर (!bad_frame &&
			filter_ack(hw, (काष्ठा ieee80211_hdr *)buffer, &stats)
			&& !mac->pass_ctrl)
		वापस 0;

	fc = get_unaligned((__le16*)buffer);
	need_padding = ieee80211_is_data_qos(fc) ^ ieee80211_has_a4(fc);

	skb = dev_alloc_skb(length + (need_padding ? 2 : 0));
	अगर (skb == शून्य)
		वापस -ENOMEM;
	अगर (need_padding) अणु
		/* Make sure the payload data is 4 byte aligned. */
		skb_reserve(skb, 2);
	पूर्ण

	/* FIXME : could we aव्योम this big स_नकल ? */
	skb_put_data(skb, buffer, length);

	स_नकल(IEEE80211_SKB_RXCB(skb), &stats, माप(stats));
	ieee80211_rx_irqsafe(hw, skb);
	वापस 0;
पूर्ण

अटल पूर्णांक zd_op_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा zd_mac *mac = zd_hw_mac(hw);

	/* using NL80211_IFTYPE_UNSPECIFIED to indicate no mode selected */
	अगर (mac->type != NL80211_IFTYPE_UNSPECIFIED)
		वापस -EOPNOTSUPP;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_AP:
		mac->type = vअगर->type;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	mac->vअगर = vअगर;

	वापस set_mac_and_bssid(mac);
पूर्ण

अटल व्योम zd_op_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	mac->type = NL80211_IFTYPE_UNSPECIFIED;
	mac->vअगर = शून्य;
	zd_set_beacon_पूर्णांकerval(&mac->chip, 0, 0, NL80211_IFTYPE_UNSPECIFIED);
	zd_ग_लिखो_mac_addr(&mac->chip, शून्य);

	zd_mac_मुक्त_cur_beacon(mac);
पूर्ण

अटल पूर्णांक zd_op_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	काष्ठा ieee80211_conf *conf = &hw->conf;

	spin_lock_irq(&mac->lock);
	mac->channel = conf->chandef.chan->hw_value;
	spin_unlock_irq(&mac->lock);

	वापस zd_chip_set_channel(&mac->chip, conf->chandef.chan->hw_value);
पूर्ण

अटल व्योम zd_beacon_करोne(काष्ठा zd_mac *mac)
अणु
	काष्ठा sk_buff *skb, *beacon;

	अगर (!test_bit(ZD_DEVICE_RUNNING, &mac->flags))
		वापस;
	अगर (!mac->vअगर || mac->vअगर->type != NL80211_IFTYPE_AP)
		वापस;

	/*
	 * Send out buffered broad- and multicast frames.
	 */
	जबतक (!ieee80211_queue_stopped(mac->hw, 0)) अणु
		skb = ieee80211_get_buffered_bc(mac->hw, mac->vअगर);
		अगर (!skb)
			अवरोध;
		zd_op_tx(mac->hw, शून्य, skb);
	पूर्ण

	/*
	 * Fetch next beacon so that tim_count is updated.
	 */
	beacon = ieee80211_beacon_get(mac->hw, mac->vअगर);
	अगर (beacon)
		zd_mac_config_beacon(mac->hw, beacon, true);

	spin_lock_irq(&mac->lock);
	mac->beacon.last_update = jअगरfies;
	spin_unlock_irq(&mac->lock);
पूर्ण

अटल व्योम zd_process_पूर्णांकr(काष्ठा work_काष्ठा *work)
अणु
	u16 पूर्णांक_status;
	अचिन्हित दीर्घ flags;
	काष्ठा zd_mac *mac = container_of(work, काष्ठा zd_mac, process_पूर्णांकr);

	spin_lock_irqsave(&mac->lock, flags);
	पूर्णांक_status = le16_to_cpu(*(__le16 *)(mac->पूर्णांकr_buffer + 4));
	spin_unlock_irqrestore(&mac->lock, flags);

	अगर (पूर्णांक_status & INT_CFG_NEXT_BCN) अणु
		/*dev_dbg_f_limit(zd_mac_dev(mac), "INT_CFG_NEXT_BCN\n");*/
		zd_beacon_करोne(mac);
	पूर्ण अन्यथा अणु
		dev_dbg_f(zd_mac_dev(mac), "Unsupported interrupt\n");
	पूर्ण

	zd_chip_enable_hwपूर्णांक(&mac->chip);
पूर्ण


अटल u64 zd_op_prepare_multicast(काष्ठा ieee80211_hw *hw,
				   काष्ठा netdev_hw_addr_list *mc_list)
अणु
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	काष्ठा zd_mc_hash hash;
	काष्ठा netdev_hw_addr *ha;

	zd_mc_clear(&hash);

	netdev_hw_addr_list_क्रम_each(ha, mc_list) अणु
		dev_dbg_f(zd_mac_dev(mac), "mc addr %pM\n", ha->addr);
		zd_mc_add_addr(&hash, ha->addr);
	पूर्ण

	वापस hash.low | ((u64)hash.high << 32);
पूर्ण

#घोषणा SUPPORTED_FIF_FLAGS \
	(FIF_ALLMULTI | FIF_FCSFAIL | FIF_CONTROL | \
	FIF_OTHER_BSS | FIF_BCN_PRBRESP_PROMISC)
अटल व्योम zd_op_configure_filter(काष्ठा ieee80211_hw *hw,
			अचिन्हित पूर्णांक changed_flags,
			अचिन्हित पूर्णांक *new_flags,
			u64 multicast)
अणु
	काष्ठा zd_mc_hash hash = अणु
		.low = multicast,
		.high = multicast >> 32,
	पूर्ण;
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	/* Only deal with supported flags */
	changed_flags &= SUPPORTED_FIF_FLAGS;
	*new_flags &= SUPPORTED_FIF_FLAGS;

	/*
	 * If multicast parameter (as वापसed by zd_op_prepare_multicast)
	 * has changed, no bit in changed_flags is set. To handle this
	 * situation, we करो not वापस अगर changed_flags is 0. If we करो so,
	 * we will have some issue with IPv6 which uses multicast क्रम link
	 * layer address resolution.
	 */
	अगर (*new_flags & FIF_ALLMULTI)
		zd_mc_add_all(&hash);

	spin_lock_irqsave(&mac->lock, flags);
	mac->pass_failed_fcs = !!(*new_flags & FIF_FCSFAIL);
	mac->pass_ctrl = !!(*new_flags & FIF_CONTROL);
	mac->multicast_hash = hash;
	spin_unlock_irqrestore(&mac->lock, flags);

	zd_chip_set_multicast_hash(&mac->chip, &hash);

	अगर (changed_flags & FIF_CONTROL) अणु
		r = set_rx_filter(mac);
		अगर (r)
			dev_err(zd_mac_dev(mac), "set_rx_filter error %d\n", r);
	पूर्ण

	/* no handling required क्रम FIF_OTHER_BSS as we करोn't currently
	 * करो BSSID filtering */
	/* FIXME: in future it would be nice to enable the probe response
	 * filter (so that the driver करोesn't see them) until
	 * FIF_BCN_PRBRESP_PROMISC is set. however due to atomicity here, we'd
	 * have to schedule work to enable prbresp reception, which might
	 * happen too late. For now we'll just listen and क्रमward them all the
	 * समय. */
पूर्ण

अटल व्योम set_rts_cts(काष्ठा zd_mac *mac, अचिन्हित पूर्णांक लघु_preamble)
अणु
	mutex_lock(&mac->chip.mutex);
	zd_chip_set_rts_cts_rate_locked(&mac->chip, लघु_preamble);
	mutex_unlock(&mac->chip.mutex);
पूर्ण

अटल व्योम zd_op_bss_info_changed(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_bss_conf *bss_conf,
				   u32 changes)
अणु
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	पूर्णांक associated;

	dev_dbg_f(zd_mac_dev(mac), "changes: %x\n", changes);

	अगर (mac->type == NL80211_IFTYPE_MESH_POINT ||
	    mac->type == NL80211_IFTYPE_ADHOC ||
	    mac->type == NL80211_IFTYPE_AP) अणु
		associated = true;
		अगर (changes & BSS_CHANGED_BEACON) अणु
			काष्ठा sk_buff *beacon = ieee80211_beacon_get(hw, vअगर);

			अगर (beacon) अणु
				zd_chip_disable_hwपूर्णांक(&mac->chip);
				zd_mac_config_beacon(hw, beacon, false);
				zd_chip_enable_hwपूर्णांक(&mac->chip);
			पूर्ण
		पूर्ण

		अगर (changes & BSS_CHANGED_BEACON_ENABLED) अणु
			u16 पूर्णांकerval = 0;
			u8 period = 0;

			अगर (bss_conf->enable_beacon) अणु
				period = bss_conf->dtim_period;
				पूर्णांकerval = bss_conf->beacon_पूर्णांक;
			पूर्ण

			spin_lock_irq(&mac->lock);
			mac->beacon.period = period;
			mac->beacon.पूर्णांकerval = पूर्णांकerval;
			mac->beacon.last_update = jअगरfies;
			spin_unlock_irq(&mac->lock);

			zd_set_beacon_पूर्णांकerval(&mac->chip, पूर्णांकerval, period,
					       mac->type);
		पूर्ण
	पूर्ण अन्यथा
		associated = is_valid_ether_addr(bss_conf->bssid);

	spin_lock_irq(&mac->lock);
	mac->associated = associated;
	spin_unlock_irq(&mac->lock);

	/* TODO: करो hardware bssid filtering */

	अगर (changes & BSS_CHANGED_ERP_PREAMBLE) अणु
		spin_lock_irq(&mac->lock);
		mac->लघु_preamble = bss_conf->use_लघु_preamble;
		spin_unlock_irq(&mac->lock);

		set_rts_cts(mac, bss_conf->use_लघु_preamble);
	पूर्ण
पूर्ण

अटल u64 zd_op_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा zd_mac *mac = zd_hw_mac(hw);
	वापस zd_chip_get_tsf(&mac->chip);
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops zd_ops = अणु
	.tx			= zd_op_tx,
	.start			= zd_op_start,
	.stop			= zd_op_stop,
	.add_पूर्णांकerface		= zd_op_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= zd_op_हटाओ_पूर्णांकerface,
	.config			= zd_op_config,
	.prepare_multicast	= zd_op_prepare_multicast,
	.configure_filter	= zd_op_configure_filter,
	.bss_info_changed	= zd_op_bss_info_changed,
	.get_tsf		= zd_op_get_tsf,
पूर्ण;

काष्ठा ieee80211_hw *zd_mac_alloc_hw(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा zd_mac *mac;
	काष्ठा ieee80211_hw *hw;

	hw = ieee80211_alloc_hw(माप(काष्ठा zd_mac), &zd_ops);
	अगर (!hw) अणु
		dev_dbg_f(&पूर्णांकf->dev, "out of memory\n");
		वापस शून्य;
	पूर्ण

	mac = zd_hw_mac(hw);

	स_रखो(mac, 0, माप(*mac));
	spin_lock_init(&mac->lock);
	mac->hw = hw;

	mac->type = NL80211_IFTYPE_UNSPECIFIED;

	स_नकल(mac->channels, zd_channels, माप(zd_channels));
	स_नकल(mac->rates, zd_rates, माप(zd_rates));
	mac->band.n_bitrates = ARRAY_SIZE(zd_rates);
	mac->band.bitrates = mac->rates;
	mac->band.n_channels = ARRAY_SIZE(zd_channels);
	mac->band.channels = mac->channels;

	hw->wiphy->bands[NL80211_BAND_2GHZ] = &mac->band;

	ieee80211_hw_set(hw, MFP_CAPABLE);
	ieee80211_hw_set(hw, HOST_BROADCAST_PS_BUFFERING);
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, SIGNAL_UNSPEC);

	hw->wiphy->पूर्णांकerface_modes =
		BIT(NL80211_IFTYPE_MESH_POINT) |
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_ADHOC) |
		BIT(NL80211_IFTYPE_AP);

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	hw->max_संकेत = 100;
	hw->queues = 1;
	hw->extra_tx_headroom = माप(काष्ठा zd_ctrlset);

	/*
	 * Tell mac80211 that we support multi rate retries
	 */
	hw->max_rates = IEEE80211_TX_MAX_RATES;
	hw->max_rate_tries = 18;	/* 9 rates * 2 retries/rate */

	skb_queue_head_init(&mac->ack_रुको_queue);
	mac->ack_pending = 0;

	zd_chip_init(&mac->chip, hw, पूर्णांकf);
	housekeeping_init(mac);
	beacon_init(mac);
	INIT_WORK(&mac->process_पूर्णांकr, zd_process_पूर्णांकr);

	SET_IEEE80211_DEV(hw, &पूर्णांकf->dev);
	वापस hw;
पूर्ण

#घोषणा BEACON_WATCHDOG_DELAY round_jअगरfies_relative(HZ)

अटल व्योम beacon_watchकरोg_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zd_mac *mac =
		container_of(work, काष्ठा zd_mac, beacon.watchकरोg_work.work);
	काष्ठा sk_buff *beacon;
	अचिन्हित दीर्घ समयout;
	पूर्णांक पूर्णांकerval, period;

	अगर (!test_bit(ZD_DEVICE_RUNNING, &mac->flags))
		जाओ rearm;
	अगर (mac->type != NL80211_IFTYPE_AP || !mac->vअगर)
		जाओ rearm;

	spin_lock_irq(&mac->lock);
	पूर्णांकerval = mac->beacon.पूर्णांकerval;
	period = mac->beacon.period;
	समयout = mac->beacon.last_update +
			msecs_to_jअगरfies(पूर्णांकerval * 1024 / 1000) * 3;
	spin_unlock_irq(&mac->lock);

	अगर (पूर्णांकerval > 0 && समय_is_beक्रमe_jअगरfies(समयout)) अणु
		dev_dbg_f(zd_mac_dev(mac), "beacon interrupt stalled, "
					   "restarting. "
					   "(interval: %d, dtim: %d)\n",
					   पूर्णांकerval, period);

		zd_chip_disable_hwपूर्णांक(&mac->chip);

		beacon = ieee80211_beacon_get(mac->hw, mac->vअगर);
		अगर (beacon) अणु
			zd_mac_मुक्त_cur_beacon(mac);

			zd_mac_config_beacon(mac->hw, beacon, false);
		पूर्ण

		zd_set_beacon_पूर्णांकerval(&mac->chip, पूर्णांकerval, period, mac->type);

		zd_chip_enable_hwपूर्णांक(&mac->chip);

		spin_lock_irq(&mac->lock);
		mac->beacon.last_update = jअगरfies;
		spin_unlock_irq(&mac->lock);
	पूर्ण

rearm:
	queue_delayed_work(zd_workqueue, &mac->beacon.watchकरोg_work,
			   BEACON_WATCHDOG_DELAY);
पूर्ण

अटल व्योम beacon_init(काष्ठा zd_mac *mac)
अणु
	INIT_DELAYED_WORK(&mac->beacon.watchकरोg_work, beacon_watchकरोg_handler);
पूर्ण

अटल व्योम beacon_enable(काष्ठा zd_mac *mac)
अणु
	dev_dbg_f(zd_mac_dev(mac), "\n");

	mac->beacon.last_update = jअगरfies;
	queue_delayed_work(zd_workqueue, &mac->beacon.watchकरोg_work,
			   BEACON_WATCHDOG_DELAY);
पूर्ण

अटल व्योम beacon_disable(काष्ठा zd_mac *mac)
अणु
	dev_dbg_f(zd_mac_dev(mac), "\n");
	cancel_delayed_work_sync(&mac->beacon.watchकरोg_work);

	zd_mac_मुक्त_cur_beacon(mac);
पूर्ण

#घोषणा LINK_LED_WORK_DELAY HZ

अटल व्योम link_led_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zd_mac *mac =
		container_of(work, काष्ठा zd_mac, housekeeping.link_led_work.work);
	काष्ठा zd_chip *chip = &mac->chip;
	पूर्णांक is_associated;
	पूर्णांक r;

	अगर (!test_bit(ZD_DEVICE_RUNNING, &mac->flags))
		जाओ requeue;

	spin_lock_irq(&mac->lock);
	is_associated = mac->associated;
	spin_unlock_irq(&mac->lock);

	r = zd_chip_control_leds(chip,
		                 is_associated ? ZD_LED_ASSOCIATED : ZD_LED_SCANNING);
	अगर (r)
		dev_dbg_f(zd_mac_dev(mac), "zd_chip_control_leds error %d\n", r);

requeue:
	queue_delayed_work(zd_workqueue, &mac->housekeeping.link_led_work,
		           LINK_LED_WORK_DELAY);
पूर्ण

अटल व्योम housekeeping_init(काष्ठा zd_mac *mac)
अणु
	INIT_DELAYED_WORK(&mac->housekeeping.link_led_work, link_led_handler);
पूर्ण

अटल व्योम housekeeping_enable(काष्ठा zd_mac *mac)
अणु
	dev_dbg_f(zd_mac_dev(mac), "\n");
	queue_delayed_work(zd_workqueue, &mac->housekeeping.link_led_work,
			   0);
पूर्ण

अटल व्योम housekeeping_disable(काष्ठा zd_mac *mac)
अणु
	dev_dbg_f(zd_mac_dev(mac), "\n");
	cancel_delayed_work_sync(&mac->housekeeping.link_led_work);
	zd_chip_control_leds(&mac->chip, ZD_LED_OFF);
पूर्ण
