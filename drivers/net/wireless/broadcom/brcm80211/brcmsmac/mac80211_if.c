<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 * Copyright (c) 2013 Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#घोषणा __UNDEF_NO_VERSION__
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/etherdevice.h>
#समावेश <linux/sched.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/bcma/bcma.h>
#समावेश <net/mac80211.h>
#समावेश <defs.h>
#समावेश "phy/phy_int.h"
#समावेश "d11.h"
#समावेश "channel.h"
#समावेश "scb.h"
#समावेश "pub.h"
#समावेश "ucode_loader.h"
#समावेश "mac80211_if.h"
#समावेश "main.h"
#समावेश "debug.h"
#समावेश "led.h"

#घोषणा N_TX_QUEUES	4 /* #tx queues on mac80211<->driver पूर्णांकerface */
#घोषणा BRCMS_FLUSH_TIMEOUT	500 /* msec */

/* Flags we support */
#घोषणा MAC_FILTERS (FIF_ALLMULTI | \
	FIF_FCSFAIL | \
	FIF_CONTROL | \
	FIF_OTHER_BSS | \
	FIF_BCN_PRBRESP_PROMISC | \
	FIF_PSPOLL)

#घोषणा CHAN2GHZ(channel, freqency, chflags)  अणु \
	.band = NL80211_BAND_2GHZ, \
	.center_freq = (freqency), \
	.hw_value = (channel), \
	.flags = chflags, \
	.max_antenna_gain = 0, \
	.max_घातer = 19, \
पूर्ण

#घोषणा CHAN5GHZ(channel, chflags)  अणु \
	.band = NL80211_BAND_5GHZ, \
	.center_freq = 5000 + 5*(channel), \
	.hw_value = (channel), \
	.flags = chflags, \
	.max_antenna_gain = 0, \
	.max_घातer = 21, \
पूर्ण

#घोषणा RATE(rate100m, _flags) अणु \
	.bitrate = (rate100m), \
	.flags = (_flags), \
	.hw_value = (rate100m / 5), \
पूर्ण

काष्ठा firmware_hdr अणु
	__le32 offset;
	__le32 len;
	__le32 idx;
पूर्ण;

अटल स्थिर अक्षर * स्थिर brcms_firmwares[MAX_FW_IMAGES] = अणु
	"brcm/bcm43xx",
	शून्य
पूर्ण;

अटल पूर्णांक n_adapters_found;

MODULE_AUTHOR("Broadcom Corporation");
MODULE_DESCRIPTION("Broadcom 802.11n wireless LAN driver.");
MODULE_LICENSE("Dual BSD/GPL");
/* This needs to be adjusted when brcms_firmwares changes */
MODULE_FIRMWARE("brcm/bcm43xx-0.fw");
MODULE_FIRMWARE("brcm/bcm43xx_hdr-0.fw");

/* recognized BCMA Core IDs */
अटल काष्ठा bcma_device_id brcms_coreid_table[] = अणु
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_80211, 17, BCMA_ANY_CLASS),
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_80211, 23, BCMA_ANY_CLASS),
	BCMA_CORE(BCMA_MANUF_BCM, BCMA_CORE_80211, 24, BCMA_ANY_CLASS),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(bcma, brcms_coreid_table);

#अगर defined(CONFIG_BRCMDBG)
/*
 * Module parameter क्रम setting the debug message level. Available
 * flags are specअगरied by the BRCM_DL_* macros in
 * drivers/net/wireless/brcm80211/include/defs.h.
 */
module_param_named(debug, brcm_msg_level, uपूर्णांक, 0644);
#पूर्ण_अगर

अटल काष्ठा ieee80211_channel brcms_2ghz_chantable[] = अणु
	CHAN2GHZ(1, 2412, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN2GHZ(2, 2417, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN2GHZ(3, 2422, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN2GHZ(4, 2427, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN2GHZ(5, 2432, 0),
	CHAN2GHZ(6, 2437, 0),
	CHAN2GHZ(7, 2442, 0),
	CHAN2GHZ(8, 2447, IEEE80211_CHAN_NO_HT40PLUS),
	CHAN2GHZ(9, 2452, IEEE80211_CHAN_NO_HT40PLUS),
	CHAN2GHZ(10, 2457, IEEE80211_CHAN_NO_HT40PLUS),
	CHAN2GHZ(11, 2462, IEEE80211_CHAN_NO_HT40PLUS),
	CHAN2GHZ(12, 2467,
		 IEEE80211_CHAN_NO_IR |
		 IEEE80211_CHAN_NO_HT40PLUS),
	CHAN2GHZ(13, 2472,
		 IEEE80211_CHAN_NO_IR |
		 IEEE80211_CHAN_NO_HT40PLUS),
	CHAN2GHZ(14, 2484,
		 IEEE80211_CHAN_NO_IR |
		 IEEE80211_CHAN_NO_HT40PLUS | IEEE80211_CHAN_NO_HT40MINUS |
		 IEEE80211_CHAN_NO_OFDM)
पूर्ण;

अटल काष्ठा ieee80211_channel brcms_5ghz_nphy_chantable[] = अणु
	/* UNII-1 */
	CHAN5GHZ(36, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(40, IEEE80211_CHAN_NO_HT40PLUS),
	CHAN5GHZ(44, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(48, IEEE80211_CHAN_NO_HT40PLUS),
	/* UNII-2 */
	CHAN5GHZ(52,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(56,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40PLUS),
	CHAN5GHZ(60,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(64,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40PLUS),
	/* MID */
	CHAN5GHZ(100,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(104,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40PLUS),
	CHAN5GHZ(108,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(112,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40PLUS),
	CHAN5GHZ(116,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(120,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40PLUS),
	CHAN5GHZ(124,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(128,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40PLUS),
	CHAN5GHZ(132,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(136,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40PLUS),
	CHAN5GHZ(140,
		 IEEE80211_CHAN_RADAR |
		 IEEE80211_CHAN_NO_IR | IEEE80211_CHAN_NO_HT40PLUS |
		 IEEE80211_CHAN_NO_HT40MINUS),
	/* UNII-3 */
	CHAN5GHZ(149, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(153, IEEE80211_CHAN_NO_HT40PLUS),
	CHAN5GHZ(157, IEEE80211_CHAN_NO_HT40MINUS),
	CHAN5GHZ(161, IEEE80211_CHAN_NO_HT40PLUS),
	CHAN5GHZ(165, IEEE80211_CHAN_NO_HT40PLUS | IEEE80211_CHAN_NO_HT40MINUS)
पूर्ण;

/*
 * The rate table is used क्रम both 2.4G and 5G rates. The
 * latter being a subset as it करोes not support CCK rates.
 */
अटल काष्ठा ieee80211_rate legacy_ratetable[] = अणु
	RATE(10, 0),
	RATE(20, IEEE80211_RATE_SHORT_PREAMBLE),
	RATE(55, IEEE80211_RATE_SHORT_PREAMBLE),
	RATE(110, IEEE80211_RATE_SHORT_PREAMBLE),
	RATE(60, 0),
	RATE(90, 0),
	RATE(120, 0),
	RATE(180, 0),
	RATE(240, 0),
	RATE(360, 0),
	RATE(480, 0),
	RATE(540, 0),
पूर्ण;

अटल स्थिर काष्ठा ieee80211_supported_band brcms_band_2GHz_nphy_ढाँचा = अणु
	.band = NL80211_BAND_2GHZ,
	.channels = brcms_2ghz_chantable,
	.n_channels = ARRAY_SIZE(brcms_2ghz_chantable),
	.bitrates = legacy_ratetable,
	.n_bitrates = ARRAY_SIZE(legacy_ratetable),
	.ht_cap = अणु
		   /* from include/linux/ieee80211.h */
		   .cap = IEEE80211_HT_CAP_GRN_FLD |
			  IEEE80211_HT_CAP_SGI_20 | IEEE80211_HT_CAP_SGI_40,
		   .ht_supported = true,
		   .ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K,
		   .ampdu_density = AMPDU_DEF_MPDU_DENSITY,
		   .mcs = अणु
			   /* placeholders क्रम now */
			   .rx_mask = अणु0xff, 0xff, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
			   .rx_highest = cpu_to_le16(500),
			   .tx_params = IEEE80211_HT_MCS_TX_DEFINEDपूर्ण
		   पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_supported_band brcms_band_5GHz_nphy_ढाँचा = अणु
	.band = NL80211_BAND_5GHZ,
	.channels = brcms_5ghz_nphy_chantable,
	.n_channels = ARRAY_SIZE(brcms_5ghz_nphy_chantable),
	.bitrates = legacy_ratetable + BRCMS_LEGACY_5G_RATE_OFFSET,
	.n_bitrates = ARRAY_SIZE(legacy_ratetable) -
			BRCMS_LEGACY_5G_RATE_OFFSET,
	.ht_cap = अणु
		   .cap = IEEE80211_HT_CAP_GRN_FLD | IEEE80211_HT_CAP_SGI_20 |
			  IEEE80211_HT_CAP_SGI_40,
		   .ht_supported = true,
		   .ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K,
		   .ampdu_density = AMPDU_DEF_MPDU_DENSITY,
		   .mcs = अणु
			   /* placeholders क्रम now */
			   .rx_mask = अणु0xff, 0xff, 0, 0, 0, 0, 0, 0, 0, 0पूर्ण,
			   .rx_highest = cpu_to_le16(500),
			   .tx_params = IEEE80211_HT_MCS_TX_DEFINEDपूर्ण
		   पूर्ण
पूर्ण;

/* flags the given rate in rateset as requested */
अटल व्योम brcms_set_basic_rate(काष्ठा brcm_rateset *rs, u16 rate, bool is_br)
अणु
	u32 i;

	क्रम (i = 0; i < rs->count; i++) अणु
		अगर (rate != (rs->rates[i] & 0x7f))
			जारी;

		अगर (is_br)
			rs->rates[i] |= BRCMS_RATE_FLAG;
		अन्यथा
			rs->rates[i] &= BRCMS_RATE_MASK;
		वापस;
	पूर्ण
पूर्ण

/*
 * This function मुक्तs the WL per-device resources.
 *
 * This function मुक्तs resources owned by the WL device poपूर्णांकed to
 * by the wl parameter.
 *
 * precondition: can both be called locked and unlocked
 */
अटल व्योम brcms_मुक्त(काष्ठा brcms_info *wl)
अणु
	काष्ठा brcms_समयr *t, *next;

	/* मुक्त ucode data */
	अगर (wl->fw.fw_cnt)
		brcms_ucode_data_मुक्त(&wl->ucode);
	अगर (wl->irq)
		मुक्त_irq(wl->irq, wl);

	/* समाप्त dpc */
	tasklet_समाप्त(&wl->tasklet);

	अगर (wl->pub) अणु
		brcms_debugfs_detach(wl->pub);
		brcms_c_module_unरेजिस्टर(wl->pub, "linux", wl);
	पूर्ण

	/* मुक्त common resources */
	अगर (wl->wlc) अणु
		brcms_c_detach(wl->wlc);
		wl->wlc = शून्य;
		wl->pub = शून्य;
	पूर्ण

	/* भव पूर्णांकerface deletion is deferred so we cannot spinरुको */

	/* रुको क्रम all pending callbacks to complete */
	जबतक (atomic_पढ़ो(&wl->callbacks) > 0)
		schedule();

	/* मुक्त समयrs */
	क्रम (t = wl->समयrs; t; t = next) अणु
		next = t->next;
#अगर_घोषित DEBUG
		kमुक्त(t->name);
#पूर्ण_अगर
		kमुक्त(t);
	पूर्ण
पूर्ण

/*
* called from both kernel as from this kernel module (error flow on attach)
* precondition: perimeter lock is not acquired.
*/
अटल व्योम brcms_हटाओ(काष्ठा bcma_device *pdev)
अणु
	काष्ठा ieee80211_hw *hw = bcma_get_drvdata(pdev);
	काष्ठा brcms_info *wl = hw->priv;

	अगर (wl->wlc) अणु
		brcms_led_unरेजिस्टर(wl);
		wiphy_rfसमाप्त_set_hw_state(wl->pub->ieee_hw->wiphy, false);
		wiphy_rfसमाप्त_stop_polling(wl->pub->ieee_hw->wiphy);
		ieee80211_unरेजिस्टर_hw(hw);
	पूर्ण

	brcms_मुक्त(wl);

	bcma_set_drvdata(pdev, शून्य);
	ieee80211_मुक्त_hw(hw);
पूर्ण

/*
 * Precondition: Since this function is called in brcms_pci_probe() context,
 * no locking is required.
 */
अटल व्योम brcms_release_fw(काष्ठा brcms_info *wl)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < MAX_FW_IMAGES; i++) अणु
		release_firmware(wl->fw.fw_bin[i]);
		release_firmware(wl->fw.fw_hdr[i]);
	पूर्ण
पूर्ण

/*
 * Precondition: Since this function is called in brcms_pci_probe() context,
 * no locking is required.
 */
अटल पूर्णांक brcms_request_fw(काष्ठा brcms_info *wl, काष्ठा bcma_device *pdev)
अणु
	पूर्णांक status;
	काष्ठा device *device = &pdev->dev;
	अक्षर fw_name[100];
	पूर्णांक i;

	स_रखो(&wl->fw, 0, माप(काष्ठा brcms_firmware));
	क्रम (i = 0; i < MAX_FW_IMAGES; i++) अणु
		अगर (brcms_firmwares[i] == शून्य)
			अवरोध;
		प्र_लिखो(fw_name, "%s-%d.fw", brcms_firmwares[i],
			UCODE_LOADER_API_VER);
		status = request_firmware(&wl->fw.fw_bin[i], fw_name, device);
		अगर (status) अणु
			wiphy_err(wl->wiphy, "%s: fail to load firmware %s\n",
				  KBUILD_MODNAME, fw_name);
			वापस status;
		पूर्ण
		प्र_लिखो(fw_name, "%s_hdr-%d.fw", brcms_firmwares[i],
			UCODE_LOADER_API_VER);
		status = request_firmware(&wl->fw.fw_hdr[i], fw_name, device);
		अगर (status) अणु
			wiphy_err(wl->wiphy, "%s: fail to load firmware %s\n",
				  KBUILD_MODNAME, fw_name);
			वापस status;
		पूर्ण
		wl->fw.hdr_num_entries[i] =
		    wl->fw.fw_hdr[i]->size / (माप(काष्ठा firmware_hdr));
	पूर्ण
	wl->fw.fw_cnt = i;
	status = brcms_ucode_data_init(wl, &wl->ucode);
	brcms_release_fw(wl);
	वापस status;
पूर्ण

अटल व्योम brcms_ops_tx(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_tx_control *control,
			 काष्ठा sk_buff *skb)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);

	spin_lock_bh(&wl->lock);
	अगर (!wl->pub->up) अणु
		brcms_err(wl->wlc->hw->d11core, "ops->tx called while down\n");
		kमुक्त_skb(skb);
		जाओ करोne;
	पूर्ण
	अगर (brcms_c_sendpkt_mac80211(wl->wlc, skb, hw))
		tx_info->rate_driver_data[0] = control->sta;
 करोne:
	spin_unlock_bh(&wl->lock);
पूर्ण

अटल पूर्णांक brcms_ops_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	bool blocked;
	पूर्णांक err;

	अगर (!wl->ucode.bcm43xx_bomminor) अणु
		err = brcms_request_fw(wl, wl->wlc->hw->d11core);
		अगर (err)
			वापस -ENOENT;
	पूर्ण

	ieee80211_wake_queues(hw);
	spin_lock_bh(&wl->lock);
	blocked = brcms_rfसमाप्त_set_hw_state(wl);
	spin_unlock_bh(&wl->lock);
	अगर (!blocked)
		wiphy_rfसमाप्त_stop_polling(wl->pub->ieee_hw->wiphy);

	spin_lock_bh(&wl->lock);
	/* aव्योम acknowledging frames beक्रमe a non-monitor device is added */
	wl->mute_tx = true;

	अगर (!wl->pub->up)
		अगर (!blocked)
			err = brcms_up(wl);
		अन्यथा
			err = -ERFKILL;
	अन्यथा
		err = -ENODEV;
	spin_unlock_bh(&wl->lock);

	अगर (err != 0)
		brcms_err(wl->wlc->hw->d11core, "%s: brcms_up() returned %d\n",
			  __func__, err);

	bcma_core_pci_घातer_save(wl->wlc->hw->d11core->bus, true);
	वापस err;
पूर्ण

अटल व्योम brcms_ops_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	पूर्णांक status;

	ieee80211_stop_queues(hw);

	अगर (wl->wlc == शून्य)
		वापस;

	spin_lock_bh(&wl->lock);
	status = brcms_c_chipmatch(wl->wlc->hw->d11core);
	spin_unlock_bh(&wl->lock);
	अगर (!status) अणु
		brcms_err(wl->wlc->hw->d11core,
			  "wl: brcms_ops_stop: chipmatch failed\n");
		वापस;
	पूर्ण

	bcma_core_pci_घातer_save(wl->wlc->hw->d11core->bus, false);

	/* put driver in करोwn state */
	spin_lock_bh(&wl->lock);
	brcms_करोwn(wl);
	spin_unlock_bh(&wl->lock);
पूर्ण

अटल पूर्णांक
brcms_ops_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा brcms_info *wl = hw->priv;

	/* Just STA, AP and ADHOC क्रम now */
	अगर (vअगर->type != NL80211_IFTYPE_STATION &&
	    vअगर->type != NL80211_IFTYPE_AP &&
	    vअगर->type != NL80211_IFTYPE_ADHOC) अणु
		brcms_err(wl->wlc->hw->d11core,
			  "%s: Attempt to add type %d, only STA, AP and AdHoc for now\n",
			  __func__, vअगर->type);
		वापस -EOPNOTSUPP;
	पूर्ण

	spin_lock_bh(&wl->lock);
	wl->wlc->vअगर = vअगर;
	wl->mute_tx = false;
	brcms_c_mute(wl->wlc, false);
	अगर (vअगर->type == NL80211_IFTYPE_STATION)
		brcms_c_start_station(wl->wlc, vअगर->addr);
	अन्यथा अगर (vअगर->type == NL80211_IFTYPE_AP)
		brcms_c_start_ap(wl->wlc, vअगर->addr, vअगर->bss_conf.bssid,
				 vअगर->bss_conf.ssid, vअगर->bss_conf.ssid_len);
	अन्यथा अगर (vअगर->type == NL80211_IFTYPE_ADHOC)
		brcms_c_start_adhoc(wl->wlc, vअगर->addr);
	spin_unlock_bh(&wl->lock);

	वापस 0;
पूर्ण

अटल व्योम
brcms_ops_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा brcms_info *wl = hw->priv;

	spin_lock_bh(&wl->lock);
	wl->wlc->vअगर = शून्य;
	spin_unlock_bh(&wl->lock);
पूर्ण

अटल पूर्णांक brcms_ops_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा ieee80211_conf *conf = &hw->conf;
	काष्ठा brcms_info *wl = hw->priv;
	काष्ठा bcma_device *core = wl->wlc->hw->d11core;
	पूर्णांक err = 0;
	पूर्णांक new_पूर्णांक;

	spin_lock_bh(&wl->lock);
	अगर (changed & IEEE80211_CONF_CHANGE_LISTEN_INTERVAL) अणु
		brcms_c_set_beacon_listen_पूर्णांकerval(wl->wlc,
						   conf->listen_पूर्णांकerval);
	पूर्ण
	अगर (changed & IEEE80211_CONF_CHANGE_MONITOR)
		brcms_dbg_info(core, "%s: change monitor mode: %s\n",
			       __func__, conf->flags & IEEE80211_CONF_MONITOR ?
			       "true" : "false");
	अगर (changed & IEEE80211_CONF_CHANGE_PS)
		brcms_err(core, "%s: change power-save mode: %s (implement)\n",
			  __func__, conf->flags & IEEE80211_CONF_PS ?
			  "true" : "false");

	अगर (changed & IEEE80211_CONF_CHANGE_POWER) अणु
		err = brcms_c_set_tx_घातer(wl->wlc, conf->घातer_level);
		अगर (err < 0) अणु
			brcms_err(core, "%s: Error setting power_level\n",
				  __func__);
			जाओ config_out;
		पूर्ण
		new_पूर्णांक = brcms_c_get_tx_घातer(wl->wlc);
		अगर (new_पूर्णांक != conf->घातer_level)
			brcms_err(core,
				  "%s: Power level req != actual, %d %d\n",
				  __func__, conf->घातer_level,
				  new_पूर्णांक);
	पूर्ण
	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		अगर (conf->chandef.width == NL80211_CHAN_WIDTH_20 ||
		    conf->chandef.width == NL80211_CHAN_WIDTH_20_NOHT)
			err = brcms_c_set_channel(wl->wlc,
						  conf->chandef.chan->hw_value);
		अन्यथा
			err = -ENOTSUPP;
	पूर्ण
	अगर (changed & IEEE80211_CONF_CHANGE_RETRY_LIMITS)
		err = brcms_c_set_rate_limit(wl->wlc,
					     conf->लघु_frame_max_tx_count,
					     conf->दीर्घ_frame_max_tx_count);

 config_out:
	spin_unlock_bh(&wl->lock);
	वापस err;
पूर्ण

अटल व्योम
brcms_ops_bss_info_changed(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_bss_conf *info, u32 changed)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	काष्ठा bcma_device *core = wl->wlc->hw->d11core;

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		/* association status changed (associated/disassociated)
		 * also implies a change in the AID.
		 */
		brcms_err(core, "%s: %s: %sassociated\n", KBUILD_MODNAME,
			  __func__, info->assoc ? "" : "dis");
		spin_lock_bh(&wl->lock);
		brcms_c_associate_upd(wl->wlc, info->assoc);
		spin_unlock_bh(&wl->lock);
	पूर्ण
	अगर (changed & BSS_CHANGED_ERP_SLOT) अणु
		s8 val;

		/* slot timing changed */
		अगर (info->use_लघु_slot)
			val = 1;
		अन्यथा
			val = 0;
		spin_lock_bh(&wl->lock);
		brcms_c_set_लघुslot_override(wl->wlc, val);
		spin_unlock_bh(&wl->lock);
	पूर्ण

	अगर (changed & BSS_CHANGED_HT) अणु
		/* 802.11n parameters changed */
		u16 mode = info->ht_operation_mode;

		spin_lock_bh(&wl->lock);
		brcms_c_protection_upd(wl->wlc, BRCMS_PROT_N_CFG,
			mode & IEEE80211_HT_OP_MODE_PROTECTION);
		brcms_c_protection_upd(wl->wlc, BRCMS_PROT_N_NONGF,
			mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
		brcms_c_protection_upd(wl->wlc, BRCMS_PROT_N_OBSS,
			mode & IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT);
		spin_unlock_bh(&wl->lock);
	पूर्ण
	अगर (changed & BSS_CHANGED_BASIC_RATES) अणु
		काष्ठा ieee80211_supported_band *bi;
		u32 br_mask, i;
		u16 rate;
		काष्ठा brcm_rateset rs;
		पूर्णांक error;

		/* retrieve the current rates */
		spin_lock_bh(&wl->lock);
		brcms_c_get_current_rateset(wl->wlc, &rs);
		spin_unlock_bh(&wl->lock);

		br_mask = info->basic_rates;
		bi = hw->wiphy->bands[brcms_c_get_curband(wl->wlc)];
		क्रम (i = 0; i < bi->n_bitrates; i++) अणु
			/* convert to पूर्णांकernal rate value */
			rate = (bi->bitrates[i].bitrate << 1) / 10;

			/* set/clear basic rate flag */
			brcms_set_basic_rate(&rs, rate, br_mask & 1);
			br_mask >>= 1;
		पूर्ण

		/* update the rate set */
		spin_lock_bh(&wl->lock);
		error = brcms_c_set_rateset(wl->wlc, &rs);
		spin_unlock_bh(&wl->lock);
		अगर (error)
			brcms_err(core, "changing basic rates failed: %d\n",
				  error);
	पूर्ण
	अगर (changed & BSS_CHANGED_BEACON_INT) अणु
		/* Beacon पूर्णांकerval changed */
		spin_lock_bh(&wl->lock);
		brcms_c_set_beacon_period(wl->wlc, info->beacon_पूर्णांक);
		spin_unlock_bh(&wl->lock);
	पूर्ण
	अगर (changed & BSS_CHANGED_BSSID) अणु
		/* BSSID changed, क्रम whatever reason (IBSS and managed mode) */
		spin_lock_bh(&wl->lock);
		brcms_c_set_addrmatch(wl->wlc, RCM_BSSID_OFFSET, info->bssid);
		spin_unlock_bh(&wl->lock);
	पूर्ण
	अगर (changed & BSS_CHANGED_SSID) अणु
		/* BSSID changed, क्रम whatever reason (IBSS and managed mode) */
		spin_lock_bh(&wl->lock);
		brcms_c_set_ssid(wl->wlc, info->ssid, info->ssid_len);
		spin_unlock_bh(&wl->lock);
	पूर्ण
	अगर (changed & BSS_CHANGED_BEACON) अणु
		/* Beacon data changed, retrieve new beacon (beaconing modes) */
		काष्ठा sk_buff *beacon;
		u16 tim_offset = 0;

		spin_lock_bh(&wl->lock);
		beacon = ieee80211_beacon_get_tim(hw, vअगर, &tim_offset, शून्य);
		brcms_c_set_new_beacon(wl->wlc, beacon, tim_offset,
				       info->dtim_period);
		spin_unlock_bh(&wl->lock);
	पूर्ण

	अगर (changed & BSS_CHANGED_AP_PROBE_RESP) अणु
		काष्ठा sk_buff *probe_resp;

		spin_lock_bh(&wl->lock);
		probe_resp = ieee80211_proberesp_get(hw, vअगर);
		brcms_c_set_new_probe_resp(wl->wlc, probe_resp);
		spin_unlock_bh(&wl->lock);
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_ENABLED) अणु
		/* Beaconing should be enabled/disabled (beaconing modes) */
		brcms_err(core, "%s: Beacon enabled: %s\n", __func__,
			  info->enable_beacon ? "true" : "false");
		अगर (info->enable_beacon &&
		    hw->wiphy->flags & WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD) अणु
			brcms_c_enable_probe_resp(wl->wlc, true);
		पूर्ण अन्यथा अणु
			brcms_c_enable_probe_resp(wl->wlc, false);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_CQM) अणु
		/* Connection quality monitor config changed */
		brcms_err(core, "%s: cqm change: threshold %d, hys %d "
			  " (implement)\n", __func__, info->cqm_rssi_thold,
			  info->cqm_rssi_hyst);
	पूर्ण

	अगर (changed & BSS_CHANGED_IBSS) अणु
		/* IBSS join status changed */
		brcms_err(core, "%s: IBSS joined: %s (implement)\n",
			  __func__, info->ibss_joined ? "true" : "false");
	पूर्ण

	अगर (changed & BSS_CHANGED_ARP_FILTER) अणु
		/* Hardware ARP filter address list or state changed */
		brcms_err(core, "%s: arp filtering: %d addresses"
			  " (implement)\n", __func__, info->arp_addr_cnt);
	पूर्ण

	अगर (changed & BSS_CHANGED_QOS) अणु
		/*
		 * QoS क्रम this association was enabled/disabled.
		 * Note that it is only ever disabled क्रम station mode.
		 */
		brcms_err(core, "%s: qos enabled: %s (implement)\n",
			  __func__, info->qos ? "true" : "false");
	पूर्ण
	वापस;
पूर्ण

अटल व्योम
brcms_ops_configure_filter(काष्ठा ieee80211_hw *hw,
			अचिन्हित पूर्णांक changed_flags,
			अचिन्हित पूर्णांक *total_flags, u64 multicast)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	काष्ठा bcma_device *core = wl->wlc->hw->d11core;

	changed_flags &= MAC_FILTERS;
	*total_flags &= MAC_FILTERS;

	अगर (changed_flags & FIF_ALLMULTI)
		brcms_dbg_info(core, "FIF_ALLMULTI\n");
	अगर (changed_flags & FIF_FCSFAIL)
		brcms_dbg_info(core, "FIF_FCSFAIL\n");
	अगर (changed_flags & FIF_CONTROL)
		brcms_dbg_info(core, "FIF_CONTROL\n");
	अगर (changed_flags & FIF_OTHER_BSS)
		brcms_dbg_info(core, "FIF_OTHER_BSS\n");
	अगर (changed_flags & FIF_PSPOLL)
		brcms_dbg_info(core, "FIF_PSPOLL\n");
	अगर (changed_flags & FIF_BCN_PRBRESP_PROMISC)
		brcms_dbg_info(core, "FIF_BCN_PRBRESP_PROMISC\n");

	spin_lock_bh(&wl->lock);
	brcms_c_mac_promisc(wl->wlc, *total_flags);
	spin_unlock_bh(&wl->lock);
	वापस;
पूर्ण

अटल व्योम brcms_ops_sw_scan_start(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    स्थिर u8 *mac_addr)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	spin_lock_bh(&wl->lock);
	brcms_c_scan_start(wl->wlc);
	spin_unlock_bh(&wl->lock);
	वापस;
पूर्ण

अटल व्योम brcms_ops_sw_scan_complete(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	spin_lock_bh(&wl->lock);
	brcms_c_scan_stop(wl->wlc);
	spin_unlock_bh(&wl->lock);
	वापस;
पूर्ण

अटल पूर्णांक
brcms_ops_conf_tx(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर, u16 queue,
		  स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा brcms_info *wl = hw->priv;

	spin_lock_bh(&wl->lock);
	brcms_c_wme_setparams(wl->wlc, queue, params, true);
	spin_unlock_bh(&wl->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
brcms_ops_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	       काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	काष्ठा scb *scb = &wl->wlc->pri_scb;

	brcms_c_init_scb(scb);

	wl->pub->global_ampdu = &(scb->scb_ampdu);
	wl->pub->global_ampdu->scb = scb;
	wl->pub->global_ampdu->max_pdu = 16;

	/*
	 * minstrel_ht initiates addBA on our behalf by calling
	 * ieee80211_start_tx_ba_session()
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक
brcms_ops_ampdu_action(काष्ठा ieee80211_hw *hw,
		    काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	काष्ठा scb *scb = &wl->wlc->pri_scb;
	पूर्णांक status;
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u8 buf_size = params->buf_size;

	अगर (WARN_ON(scb->magic != SCB_MAGIC))
		वापस -EIDRM;
	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		spin_lock_bh(&wl->lock);
		status = brcms_c_aggregatable(wl->wlc, tid);
		spin_unlock_bh(&wl->lock);
		अगर (!status) अणु
			brcms_dbg_ht(wl->wlc->hw->d11core,
				     "START: tid %d is not agg\'able\n", tid);
			वापस -EINVAL;
		पूर्ण
		वापस IEEE80211_AMPDU_TX_START_IMMEDIATE;

	हाल IEEE80211_AMPDU_TX_STOP_CONT:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		spin_lock_bh(&wl->lock);
		brcms_c_ampdu_flush(wl->wlc, sta, tid);
		spin_unlock_bh(&wl->lock);
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		/*
		 * BA winकरोw size from ADDBA response ('buf_size') defines how
		 * many outstanding MPDUs are allowed क्रम the BA stream by
		 * recipient and traffic class. 'ampdu_factor' gives maximum
		 * AMPDU size.
		 */
		spin_lock_bh(&wl->lock);
		brcms_c_ampdu_tx_operational(wl->wlc, tid, buf_size,
			(1 << (IEEE80211_HT_MAX_AMPDU_FACTOR +
			 sta->ht_cap.ampdu_factor)) - 1);
		spin_unlock_bh(&wl->lock);
		/* Power save wakeup */
		अवरोध;
	शेष:
		brcms_err(wl->wlc->hw->d11core,
			  "%s: Invalid command, ignoring\n", __func__);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम brcms_ops_rfसमाप्त_poll(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	bool blocked;

	spin_lock_bh(&wl->lock);
	blocked = brcms_c_check_radio_disabled(wl->wlc);
	spin_unlock_bh(&wl->lock);

	wiphy_rfसमाप्त_set_hw_state(wl->pub->ieee_hw->wiphy, blocked);
पूर्ण

अटल bool brcms_tx_flush_completed(काष्ठा brcms_info *wl)
अणु
	bool result;

	spin_lock_bh(&wl->lock);
	result = brcms_c_tx_flush_completed(wl->wlc);
	spin_unlock_bh(&wl->lock);
	वापस result;
पूर्ण

अटल व्योम brcms_ops_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			    u32 queues, bool drop)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	पूर्णांक ret;

	no_prपूर्णांकk("%s: drop = %s\n", __func__, drop ? "true" : "false");

	ret = रुको_event_समयout(wl->tx_flush_wq,
				 brcms_tx_flush_completed(wl),
				 msecs_to_jअगरfies(BRCMS_FLUSH_TIMEOUT));

	brcms_dbg_mac80211(wl->wlc->hw->d11core,
			   "ret=%d\n", jअगरfies_to_msecs(ret));
पूर्ण

अटल u64 brcms_ops_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	u64 tsf;

	spin_lock_bh(&wl->lock);
	tsf = brcms_c_tsf_get(wl->wlc);
	spin_unlock_bh(&wl->lock);

	वापस tsf;
पूर्ण

अटल व्योम brcms_ops_set_tsf(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_vअगर *vअगर, u64 tsf)
अणु
	काष्ठा brcms_info *wl = hw->priv;

	spin_lock_bh(&wl->lock);
	brcms_c_tsf_set(wl->wlc, tsf);
	spin_unlock_bh(&wl->lock);
पूर्ण

अटल पूर्णांक brcms_ops_beacon_set_tim(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_sta *sta, bool set)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	काष्ठा sk_buff *beacon = शून्य;
	u16 tim_offset = 0;

	spin_lock_bh(&wl->lock);
	अगर (wl->wlc->vअगर)
		beacon = ieee80211_beacon_get_tim(hw, wl->wlc->vअगर,
						  &tim_offset, शून्य);
	अगर (beacon)
		brcms_c_set_new_beacon(wl->wlc, beacon, tim_offset,
				       wl->wlc->vअगर->bss_conf.dtim_period);
	spin_unlock_bh(&wl->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops brcms_ops = अणु
	.tx = brcms_ops_tx,
	.start = brcms_ops_start,
	.stop = brcms_ops_stop,
	.add_पूर्णांकerface = brcms_ops_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface = brcms_ops_हटाओ_पूर्णांकerface,
	.config = brcms_ops_config,
	.bss_info_changed = brcms_ops_bss_info_changed,
	.configure_filter = brcms_ops_configure_filter,
	.sw_scan_start = brcms_ops_sw_scan_start,
	.sw_scan_complete = brcms_ops_sw_scan_complete,
	.conf_tx = brcms_ops_conf_tx,
	.sta_add = brcms_ops_sta_add,
	.ampdu_action = brcms_ops_ampdu_action,
	.rfसमाप्त_poll = brcms_ops_rfसमाप्त_poll,
	.flush = brcms_ops_flush,
	.get_tsf = brcms_ops_get_tsf,
	.set_tsf = brcms_ops_set_tsf,
	.set_tim = brcms_ops_beacon_set_tim,
पूर्ण;

व्योम brcms_dpc(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा brcms_info *wl;

	wl = from_tasklet(wl, t, tasklet);

	spin_lock_bh(&wl->lock);

	/* call the common second level पूर्णांकerrupt handler */
	अगर (wl->pub->up) अणु
		अगर (wl->resched) अणु
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&wl->isr_lock, flags);
			brcms_c_पूर्णांकrsupd(wl->wlc);
			spin_unlock_irqrestore(&wl->isr_lock, flags);
		पूर्ण

		wl->resched = brcms_c_dpc(wl->wlc, true);
	पूर्ण

	/* brcms_c_dpc() may bring the driver करोwn */
	अगर (!wl->pub->up)
		जाओ करोne;

	/* re-schedule dpc */
	अगर (wl->resched)
		tasklet_schedule(&wl->tasklet);
	अन्यथा
		/* re-enable पूर्णांकerrupts */
		brcms_पूर्णांकrson(wl);

 करोne:
	spin_unlock_bh(&wl->lock);
	wake_up(&wl->tx_flush_wq);
पूर्ण

अटल irqवापस_t brcms_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा brcms_info *wl;
	irqवापस_t ret = IRQ_NONE;

	wl = (काष्ठा brcms_info *) dev_id;

	spin_lock(&wl->isr_lock);

	/* call common first level पूर्णांकerrupt handler */
	अगर (brcms_c_isr(wl->wlc)) अणु
		/* schedule second level handler */
		tasklet_schedule(&wl->tasklet);
		ret = IRQ_HANDLED;
	पूर्ण

	spin_unlock(&wl->isr_lock);

	वापस ret;
पूर्ण

/*
 * is called in brcms_pci_probe() context, thereक्रमe no locking required.
 */
अटल पूर्णांक ieee_hw_rate_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा brcms_info *wl = hw->priv;
	काष्ठा brcms_c_info *wlc = wl->wlc;
	काष्ठा ieee80211_supported_band *band;
	पूर्णांक has_5g = 0;
	u16 phy_type;

	hw->wiphy->bands[NL80211_BAND_2GHZ] = शून्य;
	hw->wiphy->bands[NL80211_BAND_5GHZ] = शून्य;

	phy_type = brcms_c_get_phy_type(wl->wlc, 0);
	अगर (phy_type == PHY_TYPE_N || phy_type == PHY_TYPE_LCN) अणु
		band = &wlc->bandstate[BAND_2G_INDEX]->band;
		*band = brcms_band_2GHz_nphy_ढाँचा;
		अगर (phy_type == PHY_TYPE_LCN) अणु
			/* Single stream */
			band->ht_cap.mcs.rx_mask[1] = 0;
			band->ht_cap.mcs.rx_highest = cpu_to_le16(72);
		पूर्ण
		hw->wiphy->bands[NL80211_BAND_2GHZ] = band;
	पूर्ण अन्यथा अणु
		वापस -EPERM;
	पूर्ण

	/* Assume all bands use the same phy.  True क्रम 11n devices. */
	अगर (wl->pub->_nbands > 1) अणु
		has_5g++;
		अगर (phy_type == PHY_TYPE_N || phy_type == PHY_TYPE_LCN) अणु
			band = &wlc->bandstate[BAND_5G_INDEX]->band;
			*band = brcms_band_5GHz_nphy_ढाँचा;
			hw->wiphy->bands[NL80211_BAND_5GHZ] = band;
		पूर्ण अन्यथा अणु
			वापस -EPERM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * is called in brcms_pci_probe() context, thereक्रमe no locking required.
 */
अटल पूर्णांक ieee_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);

	hw->extra_tx_headroom = brcms_c_get_header_len();
	hw->queues = N_TX_QUEUES;
	hw->max_rates = 2;	/* Primary rate and 1 fallback rate */

	/* channel change समय is dependent on chip and band  */
	hw->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
				     BIT(NL80211_IFTYPE_AP) |
				     BIT(NL80211_IFTYPE_ADHOC);

	/*
	 * deactivate sending probe responses by ucude, because this will
	 * cause problems when WPS is used.
	 *
	 * hw->wiphy->flags |= WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD;
	 */

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	hw->rate_control_algorithm = "minstrel_ht";

	hw->sta_data_size = 0;
	वापस ieee_hw_rate_init(hw);
पूर्ण

/*
 * attach to the WL device.
 *
 * Attach to the WL device identअगरied by venकरोr and device parameters.
 * regs is a host accessible memory address poपूर्णांकing to WL device रेजिस्टरs.
 *
 * is called in brcms_bcma_probe() context, thereक्रमe no locking required.
 */
अटल काष्ठा brcms_info *brcms_attach(काष्ठा bcma_device *pdev)
अणु
	काष्ठा brcms_info *wl = शून्य;
	पूर्णांक unit, err;
	काष्ठा ieee80211_hw *hw;
	u8 perm[ETH_ALEN];

	unit = n_adapters_found;
	err = 0;

	अगर (unit < 0)
		वापस शून्य;

	/* allocate निजी info */
	hw = bcma_get_drvdata(pdev);
	अगर (hw != शून्य)
		wl = hw->priv;
	अगर (WARN_ON(hw == शून्य) || WARN_ON(wl == शून्य))
		वापस शून्य;
	wl->wiphy = hw->wiphy;

	atomic_set(&wl->callbacks, 0);

	init_रुकोqueue_head(&wl->tx_flush_wq);

	/* setup the bottom half handler */
	tasklet_setup(&wl->tasklet, brcms_dpc);

	spin_lock_init(&wl->lock);
	spin_lock_init(&wl->isr_lock);

	/* common load-समय initialization */
	wl->wlc = brcms_c_attach((व्योम *)wl, pdev, unit, false, &err);
	अगर (!wl->wlc) अणु
		wiphy_err(wl->wiphy, "%s: attach() failed with code %d\n",
			  KBUILD_MODNAME, err);
		जाओ fail;
	पूर्ण
	wl->pub = brcms_c_pub(wl->wlc);

	wl->pub->ieee_hw = hw;

	/* रेजिस्टर our पूर्णांकerrupt handler */
	अगर (request_irq(pdev->irq, brcms_isr,
			IRQF_SHARED, KBUILD_MODNAME, wl)) अणु
		wiphy_err(wl->wiphy, "wl%d: request_irq() failed\n", unit);
		जाओ fail;
	पूर्ण
	wl->irq = pdev->irq;

	/* रेजिस्टर module */
	brcms_c_module_रेजिस्टर(wl->pub, "linux", wl, शून्य);

	अगर (ieee_hw_init(hw)) अणु
		wiphy_err(wl->wiphy, "wl%d: %s: ieee_hw_init failed!\n", unit,
			  __func__);
		जाओ fail;
	पूर्ण

	brcms_c_regd_init(wl->wlc);

	स_नकल(perm, &wl->pub->cur_etheraddr, ETH_ALEN);
	अगर (WARN_ON(!is_valid_ether_addr(perm)))
		जाओ fail;
	SET_IEEE80211_PERM_ADDR(hw, perm);

	err = ieee80211_रेजिस्टर_hw(hw);
	अगर (err)
		wiphy_err(wl->wiphy, "%s: ieee80211_register_hw failed, status"
			  "%d\n", __func__, err);

	अगर (wl->pub->srom_ccode[0] &&
	    regulatory_hपूर्णांक(wl->wiphy, wl->pub->srom_ccode))
		wiphy_err(wl->wiphy, "%s: regulatory hint failed\n", __func__);

	brcms_debugfs_attach(wl->pub);
	brcms_debugfs_create_files(wl->pub);
	n_adapters_found++;
	वापस wl;

fail:
	brcms_मुक्त(wl);
	वापस शून्य;
पूर्ण



/*
 * determines अगर a device is a WL device, and अगर so, attaches it.
 *
 * This function determines अगर a device poपूर्णांकed to by pdev is a WL device,
 * and अगर so, perक्रमms a brcms_attach() on it.
 *
 * Perimeter lock is initialized in the course of this function.
 */
अटल पूर्णांक brcms_bcma_probe(काष्ठा bcma_device *pdev)
अणु
	काष्ठा brcms_info *wl;
	काष्ठा ieee80211_hw *hw;

	dev_info(&pdev->dev, "mfg %x core %x rev %d class %d irq %d\n",
		 pdev->id.manuf, pdev->id.id, pdev->id.rev, pdev->id.class,
		 pdev->irq);

	अगर ((pdev->id.manuf != BCMA_MANUF_BCM) ||
	    (pdev->id.id != BCMA_CORE_80211))
		वापस -ENODEV;

	hw = ieee80211_alloc_hw(माप(काष्ठा brcms_info), &brcms_ops);
	अगर (!hw) अणु
		pr_err("%s: ieee80211_alloc_hw failed\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	SET_IEEE80211_DEV(hw, &pdev->dev);

	bcma_set_drvdata(pdev, hw);

	स_रखो(hw->priv, 0, माप(*wl));

	wl = brcms_attach(pdev);
	अगर (!wl) अणु
		pr_err("%s: brcms_attach failed!\n", __func__);
		वापस -ENODEV;
	पूर्ण
	brcms_led_रेजिस्टर(wl);

	वापस 0;
पूर्ण

अटल पूर्णांक brcms_suspend(काष्ठा bcma_device *pdev)
अणु
	काष्ठा brcms_info *wl;
	काष्ठा ieee80211_hw *hw;

	hw = bcma_get_drvdata(pdev);
	wl = hw->priv;
	अगर (!wl) अणु
		pr_err("%s: %s: no driver private struct!\n", KBUILD_MODNAME,
		       __func__);
		वापस -ENODEV;
	पूर्ण

	/* only need to flag hw is करोwn क्रम proper resume */
	spin_lock_bh(&wl->lock);
	wl->pub->hw_up = false;
	spin_unlock_bh(&wl->lock);

	brcms_dbg_info(wl->wlc->hw->d11core, "brcms_suspend ok\n");

	वापस 0;
पूर्ण

अटल पूर्णांक brcms_resume(काष्ठा bcma_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा bcma_driver brcms_bcma_driver = अणु
	.name     = KBUILD_MODNAME,
	.probe    = brcms_bcma_probe,
	.suspend  = brcms_suspend,
	.resume   = brcms_resume,
	.हटाओ   = brcms_हटाओ,
	.id_table = brcms_coreid_table,
पूर्ण;

/*
 * This is the मुख्य entry poपूर्णांक क्रम the brcmsmac driver.
 *
 * This function is scheduled upon module initialization and
 * करोes the driver registration, which result in brcms_bcma_probe()
 * call resulting in the driver bringup.
 */
अटल व्योम brcms_driver_init(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक error;

	error = bcma_driver_रेजिस्टर(&brcms_bcma_driver);
	अगर (error)
		pr_err("%s: register returned %d\n", __func__, error);
पूर्ण

अटल DECLARE_WORK(brcms_driver_work, brcms_driver_init);

अटल पूर्णांक __init brcms_module_init(व्योम)
अणु
	brcms_debugfs_init();
	अगर (!schedule_work(&brcms_driver_work))
		वापस -EBUSY;

	वापस 0;
पूर्ण

/*
 * This function unloads the brcmsmac driver from the प्रणाली.
 *
 * This function unconditionally unloads the brcmsmac driver module from the
 * प्रणाली.
 *
 */
अटल व्योम __निकास brcms_module_निकास(व्योम)
अणु
	cancel_work_sync(&brcms_driver_work);
	bcma_driver_unरेजिस्टर(&brcms_bcma_driver);
	brcms_debugfs_निकास();
पूर्ण

module_init(brcms_module_init);
module_निकास(brcms_module_निकास);

/*
 * precondition: perimeter lock has been acquired
 */
व्योम brcms_txflowcontrol(काष्ठा brcms_info *wl, काष्ठा brcms_अगर *wlअगर,
			 bool state, पूर्णांक prio)
अणु
	brcms_err(wl->wlc->hw->d11core, "Shouldn't be here %s\n", __func__);
पूर्ण

/*
 * precondition: perimeter lock has been acquired
 */
व्योम brcms_init(काष्ठा brcms_info *wl)
अणु
	brcms_dbg_info(wl->wlc->hw->d11core, "Initializing wl%d\n",
		       wl->pub->unit);
	brcms_reset(wl);
	brcms_c_init(wl->wlc, wl->mute_tx);
पूर्ण

/*
 * precondition: perimeter lock has been acquired
 */
uपूर्णांक brcms_reset(काष्ठा brcms_info *wl)
अणु
	brcms_dbg_info(wl->wlc->hw->d11core, "Resetting wl%d\n", wl->pub->unit);
	brcms_c_reset(wl->wlc);

	/* dpc will not be rescheduled */
	wl->resched = false;

	/* inक्रमm खुलाly that पूर्णांकerface is करोwn */
	wl->pub->up = false;

	वापस 0;
पूर्ण

व्योम brcms_fatal_error(काष्ठा brcms_info *wl)
अणु
	brcms_err(wl->wlc->hw->d11core, "wl%d: fatal error, reinitializing\n",
		  wl->wlc->pub->unit);
	brcms_reset(wl);
	ieee80211_restart_hw(wl->pub->ieee_hw);
पूर्ण

/*
 * These are पूर्णांकerrupt on/off entry poपूर्णांकs. Disable पूर्णांकerrupts
 * during पूर्णांकerrupt state transition.
 */
व्योम brcms_पूर्णांकrson(काष्ठा brcms_info *wl)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wl->isr_lock, flags);
	brcms_c_पूर्णांकrson(wl->wlc);
	spin_unlock_irqrestore(&wl->isr_lock, flags);
पूर्ण

u32 brcms_पूर्णांकrsoff(काष्ठा brcms_info *wl)
अणु
	अचिन्हित दीर्घ flags;
	u32 status;

	spin_lock_irqsave(&wl->isr_lock, flags);
	status = brcms_c_पूर्णांकrsoff(wl->wlc);
	spin_unlock_irqrestore(&wl->isr_lock, flags);
	वापस status;
पूर्ण

व्योम brcms_पूर्णांकrsrestore(काष्ठा brcms_info *wl, u32 macपूर्णांकmask)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wl->isr_lock, flags);
	brcms_c_पूर्णांकrsrestore(wl->wlc, macपूर्णांकmask);
	spin_unlock_irqrestore(&wl->isr_lock, flags);
पूर्ण

/*
 * precondition: perimeter lock has been acquired
 */
पूर्णांक brcms_up(काष्ठा brcms_info *wl)
अणु
	पूर्णांक error = 0;

	अगर (wl->pub->up)
		वापस 0;

	error = brcms_c_up(wl->wlc);

	वापस error;
पूर्ण

/*
 * precondition: perimeter lock has been acquired
 */
व्योम brcms_करोwn(काष्ठा brcms_info *wl)
	__must_hold(&wl->lock)
अणु
	uपूर्णांक callbacks, ret_val = 0;

	/* call common करोwn function */
	ret_val = brcms_c_करोwn(wl->wlc);
	callbacks = atomic_पढ़ो(&wl->callbacks) - ret_val;

	/* रुको क्रम करोwn callbacks to complete */
	spin_unlock_bh(&wl->lock);

	/* For HIGH_only driver, it's important to actually schedule other work,
	 * not just spin रुको since everything runs at schedule level
	 */
	SPINWAIT((atomic_पढ़ो(&wl->callbacks) > callbacks), 100 * 1000);

	spin_lock_bh(&wl->lock);
पूर्ण

/*
* precondition: perimeter lock is not acquired
 */
अटल व्योम _brcms_समयr(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा brcms_समयr *t = container_of(work, काष्ठा brcms_समयr,
					     dly_wrk.work);

	spin_lock_bh(&t->wl->lock);

	अगर (t->set) अणु
		अगर (t->periodic) अणु
			atomic_inc(&t->wl->callbacks);
			ieee80211_queue_delayed_work(t->wl->pub->ieee_hw,
						     &t->dly_wrk,
						     msecs_to_jअगरfies(t->ms));
		पूर्ण अन्यथा अणु
			t->set = false;
		पूर्ण

		t->fn(t->arg);
	पूर्ण

	atomic_dec(&t->wl->callbacks);

	spin_unlock_bh(&t->wl->lock);
पूर्ण

/*
 * Adds a समयr to the list. Caller supplies a समयr function.
 * Is called from wlc.
 *
 * precondition: perimeter lock has been acquired
 */
काष्ठा brcms_समयr *brcms_init_समयr(काष्ठा brcms_info *wl,
				     व्योम (*fn) (व्योम *arg),
				     व्योम *arg, स्थिर अक्षर *name)
अणु
	काष्ठा brcms_समयr *t;

	t = kzalloc(माप(काष्ठा brcms_समयr), GFP_ATOMIC);
	अगर (!t)
		वापस शून्य;

	INIT_DELAYED_WORK(&t->dly_wrk, _brcms_समयr);
	t->wl = wl;
	t->fn = fn;
	t->arg = arg;
	t->next = wl->समयrs;
	wl->समयrs = t;

#अगर_घोषित DEBUG
	t->name = kstrdup(name, GFP_ATOMIC);
#पूर्ण_अगर

	वापस t;
पूर्ण

/*
 * adds only the kernel समयr since it's going to be more accurate
 * as well as it's easier to make it periodic
 *
 * precondition: perimeter lock has been acquired
 */
व्योम brcms_add_समयr(काष्ठा brcms_समयr *t, uपूर्णांक ms, पूर्णांक periodic)
अणु
	काष्ठा ieee80211_hw *hw = t->wl->pub->ieee_hw;

#अगर_घोषित DEBUG
	अगर (t->set)
		brcms_dbg_info(t->wl->wlc->hw->d11core,
			       "%s: Already set. Name: %s, per %d\n",
			       __func__, t->name, periodic);
#पूर्ण_अगर
	t->ms = ms;
	t->periodic = (bool) periodic;
	अगर (!t->set) अणु
		t->set = true;
		atomic_inc(&t->wl->callbacks);
	पूर्ण

	ieee80211_queue_delayed_work(hw, &t->dly_wrk, msecs_to_jअगरfies(ms));
पूर्ण

/*
 * वापस true अगर समयr successfully deleted, false अगर still pending
 *
 * precondition: perimeter lock has been acquired
 */
bool brcms_del_समयr(काष्ठा brcms_समयr *t)
अणु
	अगर (t->set) अणु
		t->set = false;
		अगर (!cancel_delayed_work(&t->dly_wrk))
			वापस false;

		atomic_dec(&t->wl->callbacks);
	पूर्ण

	वापस true;
पूर्ण

/*
 * precondition: perimeter lock has been acquired
 */
व्योम brcms_मुक्त_समयr(काष्ठा brcms_समयr *t)
अणु
	काष्ठा brcms_info *wl = t->wl;
	काष्ठा brcms_समयr *पंचांगp;

	/* delete the समयr in हाल it is active */
	brcms_del_समयr(t);

	अगर (wl->समयrs == t) अणु
		wl->समयrs = wl->समयrs->next;
#अगर_घोषित DEBUG
		kमुक्त(t->name);
#पूर्ण_अगर
		kमुक्त(t);
		वापस;

	पूर्ण

	पंचांगp = wl->समयrs;
	जबतक (पंचांगp) अणु
		अगर (पंचांगp->next == t) अणु
			पंचांगp->next = t->next;
#अगर_घोषित DEBUG
			kमुक्त(t->name);
#पूर्ण_अगर
			kमुक्त(t);
			वापस;
		पूर्ण
		पंचांगp = पंचांगp->next;
	पूर्ण

पूर्ण

/*
 * precondition: no locking required
 */
पूर्णांक brcms_ucode_init_buf(काष्ठा brcms_info *wl, व्योम **pbuf, u32 idx)
अणु
	पूर्णांक i, entry;
	स्थिर u8 *pdata;
	काष्ठा firmware_hdr *hdr;
	क्रम (i = 0; i < wl->fw.fw_cnt; i++) अणु
		hdr = (काष्ठा firmware_hdr *)wl->fw.fw_hdr[i]->data;
		क्रम (entry = 0; entry < wl->fw.hdr_num_entries[i];
		     entry++, hdr++) अणु
			u32 len = le32_to_cpu(hdr->len);
			अगर (le32_to_cpu(hdr->idx) == idx) अणु
				pdata = wl->fw.fw_bin[i]->data +
					le32_to_cpu(hdr->offset);
				*pbuf = kvदो_स्मृति(len, GFP_KERNEL);
				अगर (*pbuf == शून्य)
					जाओ fail;
				स_नकल(*pbuf, pdata, len);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	brcms_err(wl->wlc->hw->d11core,
		  "ERROR: ucode buf tag:%d can not be found!\n", idx);
	*pbuf = शून्य;
fail:
	वापस -ENODATA;
पूर्ण

/*
 * Precondition: Since this function is called in brcms_bcma_probe() context,
 * no locking is required.
 */
पूर्णांक brcms_ucode_init_uपूर्णांक(काष्ठा brcms_info *wl, माप_प्रकार *n_bytes, u32 idx)
अणु
	पूर्णांक i, entry;
	स्थिर u8 *pdata;
	काष्ठा firmware_hdr *hdr;
	क्रम (i = 0; i < wl->fw.fw_cnt; i++) अणु
		hdr = (काष्ठा firmware_hdr *)wl->fw.fw_hdr[i]->data;
		क्रम (entry = 0; entry < wl->fw.hdr_num_entries[i];
		     entry++, hdr++) अणु
			अगर (le32_to_cpu(hdr->idx) == idx) अणु
				pdata = wl->fw.fw_bin[i]->data +
					le32_to_cpu(hdr->offset);
				अगर (le32_to_cpu(hdr->len) != 4) अणु
					brcms_err(wl->wlc->hw->d11core,
						  "ERROR: fw hdr len\n");
					वापस -ENOMSG;
				पूर्ण
				*n_bytes = le32_to_cpu(*((__le32 *) pdata));
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण
	brcms_err(wl->wlc->hw->d11core,
		  "ERROR: ucode tag:%d can not be found!\n", idx);
	वापस -ENOMSG;
पूर्ण

/*
 * precondition: can both be called locked and unlocked
 */
व्योम brcms_ucode_मुक्त_buf(व्योम *p)
अणु
	kvमुक्त(p);
पूर्ण

/*
 * checks validity of all firmware images loaded from user space
 *
 * Precondition: Since this function is called in brcms_bcma_probe() context,
 * no locking is required.
 */
पूर्णांक brcms_check_firmwares(काष्ठा brcms_info *wl)
अणु
	पूर्णांक i;
	पूर्णांक entry;
	पूर्णांक rc = 0;
	स्थिर काष्ठा firmware *fw;
	स्थिर काष्ठा firmware *fw_hdr;
	काष्ठा firmware_hdr *ucode_hdr;
	क्रम (i = 0; i < MAX_FW_IMAGES && rc == 0; i++) अणु
		fw =  wl->fw.fw_bin[i];
		fw_hdr = wl->fw.fw_hdr[i];
		अगर (fw == शून्य && fw_hdr == शून्य) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (fw == शून्य || fw_hdr == शून्य) अणु
			wiphy_err(wl->wiphy, "%s: invalid bin/hdr fw\n",
				  __func__);
			rc = -EBADF;
		पूर्ण अन्यथा अगर (fw_hdr->size % माप(काष्ठा firmware_hdr)) अणु
			wiphy_err(wl->wiphy, "%s: non integral fw hdr file "
				"size %zu/%zu\n", __func__, fw_hdr->size,
				माप(काष्ठा firmware_hdr));
			rc = -EBADF;
		पूर्ण अन्यथा अगर (fw->size < MIN_FW_SIZE || fw->size > MAX_FW_SIZE) अणु
			wiphy_err(wl->wiphy, "%s: out of bounds fw file size %zu\n",
				  __func__, fw->size);
			rc = -EBADF;
		पूर्ण अन्यथा अणु
			/* check अगर ucode section overruns firmware image */
			ucode_hdr = (काष्ठा firmware_hdr *)fw_hdr->data;
			क्रम (entry = 0; entry < wl->fw.hdr_num_entries[i] &&
			     !rc; entry++, ucode_hdr++) अणु
				अगर (le32_to_cpu(ucode_hdr->offset) +
				    le32_to_cpu(ucode_hdr->len) >
				    fw->size) अणु
					wiphy_err(wl->wiphy,
						  "%s: conflicting bin/hdr\n",
						  __func__);
					rc = -EBADF;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (rc == 0 && wl->fw.fw_cnt != i) अणु
		wiphy_err(wl->wiphy, "%s: invalid fw_cnt=%d\n", __func__,
			wl->fw.fw_cnt);
		rc = -EBADF;
	पूर्ण
	वापस rc;
पूर्ण

/*
 * precondition: perimeter lock has been acquired
 */
bool brcms_rfसमाप्त_set_hw_state(काष्ठा brcms_info *wl)
	__must_hold(&wl->lock)
अणु
	bool blocked = brcms_c_check_radio_disabled(wl->wlc);

	spin_unlock_bh(&wl->lock);
	wiphy_rfसमाप्त_set_hw_state(wl->pub->ieee_hw->wiphy, blocked);
	अगर (blocked)
		wiphy_rfसमाप्त_start_polling(wl->pub->ieee_hw->wiphy);
	spin_lock_bh(&wl->lock);
	वापस blocked;
पूर्ण
