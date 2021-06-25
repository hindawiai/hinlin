<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Device probe and रेजिस्टर.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 * Copyright (c) 2008, Johannes Berg <johannes@sipsolutions.net>
 * Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2007-2009, Christian Lamparter <chunkeey@web.de>
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 * Copyright (c) 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 */
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/firmware.h>

#समावेश "main.h"
#समावेश "wfx.h"
#समावेश "fwio.h"
#समावेश "hwio.h"
#समावेश "bus.h"
#समावेश "bh.h"
#समावेश "sta.h"
#समावेश "key.h"
#समावेश "scan.h"
#समावेश "debug.h"
#समावेश "data_tx.h"
#समावेश "hif_tx_mib.h"
#समावेश "hif_api_cmd.h"

#घोषणा WFX_PDS_MAX_SIZE 1500

MODULE_DESCRIPTION("Silicon Labs 802.11 Wireless LAN driver for WFx");
MODULE_AUTHOR("Jथऊrथखme Pouiller <jerome.pouiller@silabs.com>");
MODULE_LICENSE("GPL");

#घोषणा RATETAB_ENT(_rate, _rateid, _flags) अणु \
	.bitrate  = (_rate),   \
	.hw_value = (_rateid), \
	.flags    = (_flags),  \
पूर्ण

अटल काष्ठा ieee80211_rate wfx_rates[] = अणु
	RATETAB_ENT(10,  0,  0),
	RATETAB_ENT(20,  1,  IEEE80211_RATE_SHORT_PREAMBLE),
	RATETAB_ENT(55,  2,  IEEE80211_RATE_SHORT_PREAMBLE),
	RATETAB_ENT(110, 3,  IEEE80211_RATE_SHORT_PREAMBLE),
	RATETAB_ENT(60,  6,  0),
	RATETAB_ENT(90,  7,  0),
	RATETAB_ENT(120, 8,  0),
	RATETAB_ENT(180, 9,  0),
	RATETAB_ENT(240, 10, 0),
	RATETAB_ENT(360, 11, 0),
	RATETAB_ENT(480, 12, 0),
	RATETAB_ENT(540, 13, 0),
पूर्ण;

#घोषणा CHAN2G(_channel, _freq, _flags) अणु \
	.band = NL80211_BAND_2GHZ, \
	.center_freq = (_freq),    \
	.hw_value = (_channel),    \
	.flags = (_flags),         \
	.max_antenna_gain = 0,     \
	.max_घातer = 30,           \
पूर्ण

अटल काष्ठा ieee80211_channel wfx_2ghz_chantable[] = अणु
	CHAN2G(1,  2412, 0),
	CHAN2G(2,  2417, 0),
	CHAN2G(3,  2422, 0),
	CHAN2G(4,  2427, 0),
	CHAN2G(5,  2432, 0),
	CHAN2G(6,  2437, 0),
	CHAN2G(7,  2442, 0),
	CHAN2G(8,  2447, 0),
	CHAN2G(9,  2452, 0),
	CHAN2G(10, 2457, 0),
	CHAN2G(11, 2462, 0),
	CHAN2G(12, 2467, 0),
	CHAN2G(13, 2472, 0),
	CHAN2G(14, 2484, 0),
पूर्ण;

अटल स्थिर काष्ठा ieee80211_supported_band wfx_band_2ghz = अणु
	.channels = wfx_2ghz_chantable,
	.n_channels = ARRAY_SIZE(wfx_2ghz_chantable),
	.bitrates = wfx_rates,
	.n_bitrates = ARRAY_SIZE(wfx_rates),
	.ht_cap = अणु
		// Receive caps
		.cap = IEEE80211_HT_CAP_GRN_FLD | IEEE80211_HT_CAP_SGI_20 |
		       IEEE80211_HT_CAP_MAX_AMSDU |
		       (1 << IEEE80211_HT_CAP_RX_STBC_SHIFT),
		.ht_supported = 1,
		.ampdu_factor = IEEE80211_HT_MAX_AMPDU_16K,
		.ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE,
		.mcs = अणु
			.rx_mask = अणु 0xFF पूर्ण, // MCS0 to MCS7
			.rx_highest = cpu_to_le16(72),
			.tx_params = IEEE80211_HT_MCS_TX_DEFINED,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_limit wdev_अगरace_limits[] = अणु
	अणु .max = 1, .types = BIT(NL80211_IFTYPE_STATION) पूर्ण,
	अणु .max = 1, .types = BIT(NL80211_IFTYPE_AP) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination wfx_अगरace_combinations[] = अणु
	अणु
		.num_dअगरferent_channels = 2,
		.max_पूर्णांकerfaces = 2,
		.limits = wdev_अगरace_limits,
		.n_limits = ARRAY_SIZE(wdev_अगरace_limits),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_ops wfx_ops = अणु
	.start			= wfx_start,
	.stop			= wfx_stop,
	.add_पूर्णांकerface		= wfx_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= wfx_हटाओ_पूर्णांकerface,
	.config                 = wfx_config,
	.tx			= wfx_tx,
	.join_ibss		= wfx_join_ibss,
	.leave_ibss		= wfx_leave_ibss,
	.conf_tx		= wfx_conf_tx,
	.hw_scan		= wfx_hw_scan,
	.cancel_hw_scan		= wfx_cancel_hw_scan,
	.start_ap		= wfx_start_ap,
	.stop_ap		= wfx_stop_ap,
	.sta_add		= wfx_sta_add,
	.sta_हटाओ		= wfx_sta_हटाओ,
	.set_tim		= wfx_set_tim,
	.set_key		= wfx_set_key,
	.set_rts_threshold	= wfx_set_rts_threshold,
	.set_शेष_unicast_key = wfx_set_शेष_unicast_key,
	.bss_info_changed	= wfx_bss_info_changed,
	.configure_filter	= wfx_configure_filter,
	.ampdu_action		= wfx_ampdu_action,
	.flush			= wfx_flush,
	.add_chanctx		= wfx_add_chanctx,
	.हटाओ_chanctx		= wfx_हटाओ_chanctx,
	.change_chanctx		= wfx_change_chanctx,
	.assign_vअगर_chanctx	= wfx_assign_vअगर_chanctx,
	.unassign_vअगर_chanctx	= wfx_unassign_vअगर_chanctx,
पूर्ण;

bool wfx_api_older_than(काष्ठा wfx_dev *wdev, पूर्णांक major, पूर्णांक minor)
अणु
	अगर (wdev->hw_caps.api_version_major < major)
		वापस true;
	अगर (wdev->hw_caps.api_version_major > major)
		वापस false;
	अगर (wdev->hw_caps.api_version_minor < minor)
		वापस true;
	वापस false;
पूर्ण

/* NOTE: wfx_send_pds() destroy buf */
पूर्णांक wfx_send_pds(काष्ठा wfx_dev *wdev, u8 *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;
	पूर्णांक start, brace_level, i;

	start = 0;
	brace_level = 0;
	अगर (buf[0] != '{') अणु
		dev_err(wdev->dev, "valid PDS start with '{'. Did you forget to compress it?\n");
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 1; i < len - 1; i++) अणु
		अगर (buf[i] == '{')
			brace_level++;
		अगर (buf[i] == '}')
			brace_level--;
		अगर (buf[i] == '}' && !brace_level) अणु
			i++;
			अगर (i - start + 1 > WFX_PDS_MAX_SIZE)
				वापस -EFBIG;
			buf[start] = '{';
			buf[i] = 0;
			dev_dbg(wdev->dev, "send PDS '%s}'\n", buf + start);
			buf[i] = '}';
			ret = hअगर_configuration(wdev, buf + start,
						i - start + 1);
			अगर (ret > 0) अणु
				dev_err(wdev->dev, "PDS bytes %d to %d: invalid data (unsupported options?)\n",
					start, i);
				वापस -EINVAL;
			पूर्ण
			अगर (ret == -ETIMEDOUT) अणु
				dev_err(wdev->dev, "PDS bytes %d to %d: chip didn't reply (corrupted file?)\n",
					start, i);
				वापस ret;
			पूर्ण
			अगर (ret) अणु
				dev_err(wdev->dev, "PDS bytes %d to %d: chip returned an unknown error\n",
					start, i);
				वापस -EIO;
			पूर्ण
			buf[i] = ',';
			start = i;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wfx_send_pdata_pds(काष्ठा wfx_dev *wdev)
अणु
	पूर्णांक ret = 0;
	स्थिर काष्ठा firmware *pds;
	u8 *पंचांगp_buf;

	ret = request_firmware(&pds, wdev->pdata.file_pds, wdev->dev);
	अगर (ret) अणु
		dev_err(wdev->dev, "can't load PDS file %s\n",
			wdev->pdata.file_pds);
		जाओ err1;
	पूर्ण
	पंचांगp_buf = kmemdup(pds->data, pds->size, GFP_KERNEL);
	अगर (!पंचांगp_buf) अणु
		ret = -ENOMEM;
		जाओ err2;
	पूर्ण
	ret = wfx_send_pds(wdev, पंचांगp_buf, pds->size);
	kमुक्त(पंचांगp_buf);
err2:
	release_firmware(pds);
err1:
	वापस ret;
पूर्ण

अटल व्योम wfx_मुक्त_common(व्योम *data)
अणु
	काष्ठा wfx_dev *wdev = data;

	mutex_destroy(&wdev->tx_घातer_loop_info_lock);
	mutex_destroy(&wdev->rx_stats_lock);
	mutex_destroy(&wdev->conf_mutex);
	ieee80211_मुक्त_hw(wdev->hw);
पूर्ण

काष्ठा wfx_dev *wfx_init_common(काष्ठा device *dev,
				स्थिर काष्ठा wfx_platक्रमm_data *pdata,
				स्थिर काष्ठा hwbus_ops *hwbus_ops,
				व्योम *hwbus_priv)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा wfx_dev *wdev;

	hw = ieee80211_alloc_hw(माप(काष्ठा wfx_dev), &wfx_ops);
	अगर (!hw)
		वापस शून्य;

	SET_IEEE80211_DEV(hw, dev);

	ieee80211_hw_set(hw, TX_AMPDU_SETUP_IN_HW);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, CONNECTION_MONITOR);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SUPPORTS_DYNAMIC_PS);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, SUPPORTS_PS);
	ieee80211_hw_set(hw, MFP_CAPABLE);

	hw->vअगर_data_size = माप(काष्ठा wfx_vअगर);
	hw->sta_data_size = माप(काष्ठा wfx_sta_priv);
	hw->queues = 4;
	hw->max_rates = 8;
	hw->max_rate_tries = 8;
	hw->extra_tx_headroom = माप(काष्ठा hअगर_msg)
				+ माप(काष्ठा hअगर_req_tx)
				+ 4 /* alignment */ + 8 /* TKIP IV */;
	hw->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
				     BIT(NL80211_IFTYPE_ADHOC) |
				     BIT(NL80211_IFTYPE_AP);
	hw->wiphy->probe_resp_offload = NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS |
					NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2 |
					NL80211_PROBE_RESP_OFFLOAD_SUPPORT_P2P |
					NL80211_PROBE_RESP_OFFLOAD_SUPPORT_80211U;
	hw->wiphy->features |= NL80211_FEATURE_AP_SCAN;
	hw->wiphy->flags |= WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD;
	hw->wiphy->flags |= WIPHY_FLAG_AP_UAPSD;
	hw->wiphy->max_ap_assoc_sta = HIF_LINK_ID_MAX;
	hw->wiphy->max_scan_ssids = 2;
	hw->wiphy->max_scan_ie_len = IEEE80211_MAX_DATA_LEN;
	hw->wiphy->n_अगरace_combinations = ARRAY_SIZE(wfx_अगरace_combinations);
	hw->wiphy->अगरace_combinations = wfx_अगरace_combinations;
	hw->wiphy->bands[NL80211_BAND_2GHZ] = devm_kदो_स्मृति(dev, माप(wfx_band_2ghz), GFP_KERNEL);
	// FIXME: also copy wfx_rates and wfx_2ghz_chantable
	स_नकल(hw->wiphy->bands[NL80211_BAND_2GHZ], &wfx_band_2ghz,
	       माप(wfx_band_2ghz));

	wdev = hw->priv;
	wdev->hw = hw;
	wdev->dev = dev;
	wdev->hwbus_ops = hwbus_ops;
	wdev->hwbus_priv = hwbus_priv;
	स_नकल(&wdev->pdata, pdata, माप(*pdata));
	of_property_पढ़ो_string(dev->of_node, "config-file",
				&wdev->pdata.file_pds);
	wdev->pdata.gpio_wakeup = devm_gpiod_get_optional(dev, "wakeup",
							  GPIOD_OUT_LOW);
	अगर (IS_ERR(wdev->pdata.gpio_wakeup))
		वापस शून्य;
	अगर (wdev->pdata.gpio_wakeup)
		gpiod_set_consumer_name(wdev->pdata.gpio_wakeup, "wfx wakeup");

	mutex_init(&wdev->conf_mutex);
	mutex_init(&wdev->rx_stats_lock);
	mutex_init(&wdev->tx_घातer_loop_info_lock);
	init_completion(&wdev->firmware_पढ़ोy);
	INIT_DELAYED_WORK(&wdev->cooling_समयout_work,
			  wfx_cooling_समयout_work);
	skb_queue_head_init(&wdev->tx_pending);
	init_रुकोqueue_head(&wdev->tx_dequeue);
	wfx_init_hअगर_cmd(&wdev->hअगर_cmd);
	wdev->क्रमce_ps_समयout = -1;

	अगर (devm_add_action_or_reset(dev, wfx_मुक्त_common, wdev))
		वापस शून्य;

	वापस wdev;
पूर्ण

पूर्णांक wfx_probe(काष्ठा wfx_dev *wdev)
अणु
	पूर्णांक i;
	पूर्णांक err;
	काष्ठा gpio_desc *gpio_saved;

	// During first part of boot, gpio_wakeup cannot yet been used. So
	// prevent bh() to touch it.
	gpio_saved = wdev->pdata.gpio_wakeup;
	wdev->pdata.gpio_wakeup = शून्य;
	wdev->poll_irq = true;

	wfx_bh_रेजिस्टर(wdev);

	err = wfx_init_device(wdev);
	अगर (err)
		जाओ err0;

	wfx_bh_poll_irq(wdev);
	err = रुको_क्रम_completion_समयout(&wdev->firmware_पढ़ोy, 1 * HZ);
	अगर (err <= 0) अणु
		अगर (err == 0) अणु
			dev_err(wdev->dev, "timeout while waiting for startup indication\n");
			err = -ETIMEDOUT;
		पूर्ण अन्यथा अगर (err == -ERESTARTSYS) अणु
			dev_info(wdev->dev, "probe interrupted by user\n");
		पूर्ण
		जाओ err0;
	पूर्ण

	// FIXME: fill wiphy::hw_version
	dev_info(wdev->dev, "started firmware %d.%d.%d \"%s\" (API: %d.%d, keyset: %02X, caps: 0x%.8X)\n",
		 wdev->hw_caps.firmware_major, wdev->hw_caps.firmware_minor,
		 wdev->hw_caps.firmware_build, wdev->hw_caps.firmware_label,
		 wdev->hw_caps.api_version_major, wdev->hw_caps.api_version_minor,
		 wdev->keyset, wdev->hw_caps.link_mode);
	snम_लिखो(wdev->hw->wiphy->fw_version,
		 माप(wdev->hw->wiphy->fw_version),
		 "%d.%d.%d",
		 wdev->hw_caps.firmware_major,
		 wdev->hw_caps.firmware_minor,
		 wdev->hw_caps.firmware_build);

	अगर (wfx_api_older_than(wdev, 1, 0)) अणु
		dev_err(wdev->dev,
			"unsupported firmware API version (expect 1 while firmware returns %d)\n",
			wdev->hw_caps.api_version_major);
		err = -ENOTSUPP;
		जाओ err0;
	पूर्ण

	अगर (wdev->hw_caps.link_mode == SEC_LINK_ENFORCED) अणु
		dev_err(wdev->dev,
			"chip require secure_link, but can't negotiate it\n");
		जाओ err0;
	पूर्ण

	अगर (wdev->hw_caps.region_sel_mode) अणु
		wdev->hw->wiphy->bands[NL80211_BAND_2GHZ]->channels[11].flags |= IEEE80211_CHAN_NO_IR;
		wdev->hw->wiphy->bands[NL80211_BAND_2GHZ]->channels[12].flags |= IEEE80211_CHAN_NO_IR;
		wdev->hw->wiphy->bands[NL80211_BAND_2GHZ]->channels[13].flags |= IEEE80211_CHAN_DISABLED;
	पूर्ण

	dev_dbg(wdev->dev, "sending configuration file %s\n",
		wdev->pdata.file_pds);
	err = wfx_send_pdata_pds(wdev);
	अगर (err < 0)
		जाओ err0;

	wdev->poll_irq = false;
	err = wdev->hwbus_ops->irq_subscribe(wdev->hwbus_priv);
	अगर (err)
		जाओ err0;

	err = hअगर_use_multi_tx_conf(wdev, true);
	अगर (err)
		dev_err(wdev->dev, "misconfigured IRQ?\n");

	wdev->pdata.gpio_wakeup = gpio_saved;
	अगर (wdev->pdata.gpio_wakeup) अणु
		dev_dbg(wdev->dev,
			"enable 'quiescent' power mode with wakeup GPIO and PDS file %s\n",
			wdev->pdata.file_pds);
		gpiod_set_value_cansleep(wdev->pdata.gpio_wakeup, 1);
		control_reg_ग_लिखो(wdev, 0);
		hअगर_set_operational_mode(wdev, HIF_OP_POWER_MODE_QUIESCENT);
	पूर्ण अन्यथा अणु
		hअगर_set_operational_mode(wdev, HIF_OP_POWER_MODE_DOZE);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wdev->addresses); i++) अणु
		eth_zero_addr(wdev->addresses[i].addr);
		err = of_get_mac_address(wdev->dev->of_node,
					 wdev->addresses[i].addr);
		अगर (!err) अणु
			wdev->addresses[i].addr[ETH_ALEN - 1] += i;
		पूर्ण अन्यथा अणु
			ether_addr_copy(wdev->addresses[i].addr,
					wdev->hw_caps.mac_addr[i]);
		पूर्ण
		अगर (!is_valid_ether_addr(wdev->addresses[i].addr)) अणु
			dev_warn(wdev->dev, "using random MAC address\n");
			eth_अक्रमom_addr(wdev->addresses[i].addr);
		पूर्ण
		dev_info(wdev->dev, "MAC address %d: %pM\n", i,
			 wdev->addresses[i].addr);
	पूर्ण
	wdev->hw->wiphy->n_addresses = ARRAY_SIZE(wdev->addresses);
	wdev->hw->wiphy->addresses = wdev->addresses;

	err = ieee80211_रेजिस्टर_hw(wdev->hw);
	अगर (err)
		जाओ err1;

	err = wfx_debug_init(wdev);
	अगर (err)
		जाओ err2;

	वापस 0;

err2:
	ieee80211_unरेजिस्टर_hw(wdev->hw);
err1:
	wdev->hwbus_ops->irq_unsubscribe(wdev->hwbus_priv);
err0:
	wfx_bh_unरेजिस्टर(wdev);
	वापस err;
पूर्ण

व्योम wfx_release(काष्ठा wfx_dev *wdev)
अणु
	ieee80211_unरेजिस्टर_hw(wdev->hw);
	hअगर_shutकरोwn(wdev);
	wdev->hwbus_ops->irq_unsubscribe(wdev->hwbus_priv);
	wfx_bh_unरेजिस्टर(wdev);
पूर्ण

अटल पूर्णांक __init wfx_core_init(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (IS_ENABLED(CONFIG_SPI))
		ret = spi_रेजिस्टर_driver(&wfx_spi_driver);
	अगर (IS_ENABLED(CONFIG_MMC) && !ret)
		ret = sdio_रेजिस्टर_driver(&wfx_sdio_driver);
	वापस ret;
पूर्ण
module_init(wfx_core_init);

अटल व्योम __निकास wfx_core_निकास(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_MMC))
		sdio_unरेजिस्टर_driver(&wfx_sdio_driver);
	अगर (IS_ENABLED(CONFIG_SPI))
		spi_unरेजिस्टर_driver(&wfx_spi_driver);
पूर्ण
module_निकास(wfx_core_निकास);
