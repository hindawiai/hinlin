<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* drivers/net/wireless/virt_wअगरi.c
 *
 * A fake implementation of cfg80211_ops that can be tacked on to an ethernet
 * net_device to make it appear as a wireless connection.
 *
 * Copyright (C) 2018 Google, Inc.
 *
 * Author: schuffelen@google.com
 */

#समावेश <net/cfg80211.h>
#समावेश <net/rtnetlink.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>

अटल काष्ठा wiphy *common_wiphy;

काष्ठा virt_wअगरi_wiphy_priv अणु
	काष्ठा delayed_work scan_result;
	काष्ठा cfg80211_scan_request *scan_request;
	bool being_deleted;
पूर्ण;

अटल काष्ठा ieee80211_channel channel_2ghz = अणु
	.band = NL80211_BAND_2GHZ,
	.center_freq = 2432,
	.hw_value = 2432,
	.max_घातer = 20,
पूर्ण;

अटल काष्ठा ieee80211_rate bitrates_2ghz[] = अणु
	अणु .bitrate = 10 पूर्ण,
	अणु .bitrate = 20 पूर्ण,
	अणु .bitrate = 55 पूर्ण,
	अणु .bitrate = 110 पूर्ण,
	अणु .bitrate = 60 पूर्ण,
	अणु .bitrate = 120 पूर्ण,
	अणु .bitrate = 240 पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_supported_band band_2ghz = अणु
	.channels = &channel_2ghz,
	.bitrates = bitrates_2ghz,
	.band = NL80211_BAND_2GHZ,
	.n_channels = 1,
	.n_bitrates = ARRAY_SIZE(bitrates_2ghz),
	.ht_cap = अणु
		.ht_supported = true,
		.cap = IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
		       IEEE80211_HT_CAP_GRN_FLD |
		       IEEE80211_HT_CAP_SGI_20 |
		       IEEE80211_HT_CAP_SGI_40 |
		       IEEE80211_HT_CAP_DSSSCCK40,
		.ampdu_factor = 0x3,
		.ampdu_density = 0x6,
		.mcs = अणु
			.rx_mask = अणु0xff, 0xffपूर्ण,
			.tx_params = IEEE80211_HT_MCS_TX_DEFINED,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_channel channel_5ghz = अणु
	.band = NL80211_BAND_5GHZ,
	.center_freq = 5240,
	.hw_value = 5240,
	.max_घातer = 20,
पूर्ण;

अटल काष्ठा ieee80211_rate bitrates_5ghz[] = अणु
	अणु .bitrate = 60 पूर्ण,
	अणु .bitrate = 120 पूर्ण,
	अणु .bitrate = 240 पूर्ण,
पूर्ण;

#घोषणा RX_MCS_MAP (IEEE80211_VHT_MCS_SUPPORT_0_9 << 0 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 2 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 4 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 6 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 8 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 10 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 12 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 14)

#घोषणा TX_MCS_MAP (IEEE80211_VHT_MCS_SUPPORT_0_9 << 0 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 2 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 4 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 6 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 8 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 10 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 12 | \
		    IEEE80211_VHT_MCS_SUPPORT_0_9 << 14)

अटल काष्ठा ieee80211_supported_band band_5ghz = अणु
	.channels = &channel_5ghz,
	.bitrates = bitrates_5ghz,
	.band = NL80211_BAND_5GHZ,
	.n_channels = 1,
	.n_bitrates = ARRAY_SIZE(bitrates_5ghz),
	.ht_cap = अणु
		.ht_supported = true,
		.cap = IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
		       IEEE80211_HT_CAP_GRN_FLD |
		       IEEE80211_HT_CAP_SGI_20 |
		       IEEE80211_HT_CAP_SGI_40 |
		       IEEE80211_HT_CAP_DSSSCCK40,
		.ampdu_factor = 0x3,
		.ampdu_density = 0x6,
		.mcs = अणु
			.rx_mask = अणु0xff, 0xffपूर्ण,
			.tx_params = IEEE80211_HT_MCS_TX_DEFINED,
		पूर्ण,
	पूर्ण,
	.vht_cap = अणु
		.vht_supported = true,
		.cap = IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454 |
		       IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ |
		       IEEE80211_VHT_CAP_RXLDPC |
		       IEEE80211_VHT_CAP_SHORT_GI_80 |
		       IEEE80211_VHT_CAP_SHORT_GI_160 |
		       IEEE80211_VHT_CAP_TXSTBC |
		       IEEE80211_VHT_CAP_RXSTBC_1 |
		       IEEE80211_VHT_CAP_RXSTBC_2 |
		       IEEE80211_VHT_CAP_RXSTBC_3 |
		       IEEE80211_VHT_CAP_RXSTBC_4 |
		       IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK,
		.vht_mcs = अणु
			.rx_mcs_map = cpu_to_le16(RX_MCS_MAP),
			.tx_mcs_map = cpu_to_le16(TX_MCS_MAP),
		पूर्ण
	पूर्ण,
पूर्ण;

/* Asचिन्हित at module init. Guaranteed locally-administered and unicast. */
अटल u8 fake_router_bssid[ETH_ALEN] __ro_after_init = अणुपूर्ण;

/* Called with the rtnl lock held. */
अटल पूर्णांक virt_wअगरi_scan(काष्ठा wiphy *wiphy,
			  काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा virt_wअगरi_wiphy_priv *priv = wiphy_priv(wiphy);

	wiphy_debug(wiphy, "scan\n");

	अगर (priv->scan_request || priv->being_deleted)
		वापस -EBUSY;

	priv->scan_request = request;
	schedule_delayed_work(&priv->scan_result, HZ * 2);

	वापस 0;
पूर्ण

/* Acquires and releases the rdev BSS lock. */
अटल व्योम virt_wअगरi_scan_result(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा अणु
		u8 tag;
		u8 len;
		u8 ssid[8];
	पूर्ण __packed ssid = अणु
		.tag = WLAN_EID_SSID, .len = 8, .ssid = "VirtWifi",
	पूर्ण;
	काष्ठा cfg80211_bss *inक्रमmed_bss;
	काष्ठा virt_wअगरi_wiphy_priv *priv =
		container_of(work, काष्ठा virt_wअगरi_wiphy_priv,
			     scan_result.work);
	काष्ठा wiphy *wiphy = priv_to_wiphy(priv);
	काष्ठा cfg80211_scan_info scan_info = अणु .पातed = false पूर्ण;
	u64 tsf = भाग_u64(kसमय_get_bootसमय_ns(), 1000);

	inक्रमmed_bss = cfg80211_inक्रमm_bss(wiphy, &channel_5ghz,
					   CFG80211_BSS_FTYPE_PRESP,
					   fake_router_bssid, tsf,
					   WLAN_CAPABILITY_ESS, 0,
					   (व्योम *)&ssid, माप(ssid),
					   DBM_TO_MBM(-50), GFP_KERNEL);
	cfg80211_put_bss(wiphy, inक्रमmed_bss);

	/* Schedules work which acquires and releases the rtnl lock. */
	cfg80211_scan_करोne(priv->scan_request, &scan_info);
	priv->scan_request = शून्य;
पूर्ण

/* May acquire and release the rdev BSS lock. */
अटल व्योम virt_wअगरi_cancel_scan(काष्ठा wiphy *wiphy)
अणु
	काष्ठा virt_wअगरi_wiphy_priv *priv = wiphy_priv(wiphy);

	cancel_delayed_work_sync(&priv->scan_result);
	/* Clean up dangling callbacks अगर necessary. */
	अगर (priv->scan_request) अणु
		काष्ठा cfg80211_scan_info scan_info = अणु .पातed = true पूर्ण;
		/* Schedules work which acquires and releases the rtnl lock. */
		cfg80211_scan_करोne(priv->scan_request, &scan_info);
		priv->scan_request = शून्य;
	पूर्ण
पूर्ण

काष्ठा virt_wअगरi_netdev_priv अणु
	काष्ठा delayed_work connect;
	काष्ठा net_device *lowerdev;
	काष्ठा net_device *upperdev;
	u32 tx_packets;
	u32 tx_failed;
	u8 connect_requested_bss[ETH_ALEN];
	bool is_up;
	bool is_connected;
	bool being_deleted;
पूर्ण;

/* Called with the rtnl lock held. */
अटल पूर्णांक virt_wअगरi_connect(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
			     काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा virt_wअगरi_netdev_priv *priv = netdev_priv(netdev);
	bool could_schedule;

	अगर (priv->being_deleted || !priv->is_up)
		वापस -EBUSY;

	could_schedule = schedule_delayed_work(&priv->connect, HZ * 2);
	अगर (!could_schedule)
		वापस -EBUSY;

	अगर (sme->bssid)
		ether_addr_copy(priv->connect_requested_bss, sme->bssid);
	अन्यथा
		eth_zero_addr(priv->connect_requested_bss);

	wiphy_debug(wiphy, "connect\n");

	वापस 0;
पूर्ण

/* Acquires and releases the rdev event lock. */
अटल व्योम virt_wअगरi_connect_complete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virt_wअगरi_netdev_priv *priv =
		container_of(work, काष्ठा virt_wअगरi_netdev_priv, connect.work);
	u8 *requested_bss = priv->connect_requested_bss;
	bool has_addr = !is_zero_ether_addr(requested_bss);
	bool right_addr = ether_addr_equal(requested_bss, fake_router_bssid);
	u16 status = WLAN_STATUS_SUCCESS;

	अगर (!priv->is_up || (has_addr && !right_addr))
		status = WLAN_STATUS_UNSPECIFIED_FAILURE;
	अन्यथा
		priv->is_connected = true;

	/* Schedules an event that acquires the rtnl lock. */
	cfg80211_connect_result(priv->upperdev, requested_bss, शून्य, 0, शून्य, 0,
				status, GFP_KERNEL);
	netअगर_carrier_on(priv->upperdev);
पूर्ण

/* May acquire and release the rdev event lock. */
अटल व्योम virt_wअगरi_cancel_connect(काष्ठा net_device *netdev)
अणु
	काष्ठा virt_wअगरi_netdev_priv *priv = netdev_priv(netdev);

	/* If there is work pending, clean up dangling callbacks. */
	अगर (cancel_delayed_work_sync(&priv->connect)) अणु
		/* Schedules an event that acquires the rtnl lock. */
		cfg80211_connect_result(priv->upperdev,
					priv->connect_requested_bss, शून्य, 0,
					शून्य, 0,
					WLAN_STATUS_UNSPECIFIED_FAILURE,
					GFP_KERNEL);
	पूर्ण
पूर्ण

/* Called with the rtnl lock held. Acquires the rdev event lock. */
अटल पूर्णांक virt_wअगरi_disconnect(काष्ठा wiphy *wiphy, काष्ठा net_device *netdev,
				u16 reason_code)
अणु
	काष्ठा virt_wअगरi_netdev_priv *priv = netdev_priv(netdev);

	अगर (priv->being_deleted)
		वापस -EBUSY;

	wiphy_debug(wiphy, "disconnect\n");
	virt_wअगरi_cancel_connect(netdev);

	cfg80211_disconnected(netdev, reason_code, शून्य, 0, true, GFP_KERNEL);
	priv->is_connected = false;
	netअगर_carrier_off(netdev);

	वापस 0;
पूर्ण

/* Called with the rtnl lock held. */
अटल पूर्णांक virt_wअगरi_get_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				 स्थिर u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा virt_wअगरi_netdev_priv *priv = netdev_priv(dev);

	wiphy_debug(wiphy, "get_station\n");

	अगर (!priv->is_connected || !ether_addr_equal(mac, fake_router_bssid))
		वापस -ENOENT;

	sinfo->filled = BIT_ULL(NL80211_STA_INFO_TX_PACKETS) |
		BIT_ULL(NL80211_STA_INFO_TX_FAILED) |
		BIT_ULL(NL80211_STA_INFO_SIGNAL) |
		BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
	sinfo->tx_packets = priv->tx_packets;
	sinfo->tx_failed = priv->tx_failed;
	/* For CFG80211_SIGNAL_TYPE_MBM, value is expressed in _dBm_ */
	sinfo->संकेत = -50;
	sinfo->txrate = (काष्ठा rate_info) अणु
		.legacy = 10, /* units are 100kbit/s */
	पूर्ण;
	वापस 0;
पूर्ण

/* Called with the rtnl lock held. */
अटल पूर्णांक virt_wअगरi_dump_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  पूर्णांक idx, u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा virt_wअगरi_netdev_priv *priv = netdev_priv(dev);

	wiphy_debug(wiphy, "dump_station\n");

	अगर (idx != 0 || !priv->is_connected)
		वापस -ENOENT;

	ether_addr_copy(mac, fake_router_bssid);
	वापस virt_wअगरi_get_station(wiphy, dev, fake_router_bssid, sinfo);
पूर्ण

अटल स्थिर काष्ठा cfg80211_ops virt_wअगरi_cfg80211_ops = अणु
	.scan = virt_wअगरi_scan,

	.connect = virt_wअगरi_connect,
	.disconnect = virt_wअगरi_disconnect,

	.get_station = virt_wअगरi_get_station,
	.dump_station = virt_wअगरi_dump_station,
पूर्ण;

/* Acquires and releases the rtnl lock. */
अटल काष्ठा wiphy *virt_wअगरi_make_wiphy(व्योम)
अणु
	काष्ठा wiphy *wiphy;
	काष्ठा virt_wअगरi_wiphy_priv *priv;
	पूर्णांक err;

	wiphy = wiphy_new(&virt_wअगरi_cfg80211_ops, माप(*priv));

	अगर (!wiphy)
		वापस शून्य;

	wiphy->max_scan_ssids = 4;
	wiphy->max_scan_ie_len = 1000;
	wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_MBM;

	wiphy->bands[NL80211_BAND_2GHZ] = &band_2ghz;
	wiphy->bands[NL80211_BAND_5GHZ] = &band_5ghz;
	wiphy->bands[NL80211_BAND_60GHZ] = शून्य;

	wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION);

	priv = wiphy_priv(wiphy);
	priv->being_deleted = false;
	priv->scan_request = शून्य;
	INIT_DELAYED_WORK(&priv->scan_result, virt_wअगरi_scan_result);

	err = wiphy_रेजिस्टर(wiphy);
	अगर (err < 0) अणु
		wiphy_मुक्त(wiphy);
		वापस शून्य;
	पूर्ण

	वापस wiphy;
पूर्ण

/* Acquires and releases the rtnl lock. */
अटल व्योम virt_wअगरi_destroy_wiphy(काष्ठा wiphy *wiphy)
अणु
	काष्ठा virt_wअगरi_wiphy_priv *priv;

	WARN(!wiphy, "%s called with null wiphy", __func__);
	अगर (!wiphy)
		वापस;

	priv = wiphy_priv(wiphy);
	priv->being_deleted = true;
	virt_wअगरi_cancel_scan(wiphy);

	अगर (wiphy->रेजिस्टरed)
		wiphy_unरेजिस्टर(wiphy);
	wiphy_मुक्त(wiphy);
पूर्ण

/* Enters and निकासs a RCU-bh critical section. */
अटल netdev_tx_t virt_wअगरi_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
	काष्ठा virt_wअगरi_netdev_priv *priv = netdev_priv(dev);

	priv->tx_packets++;
	अगर (!priv->is_connected) अणु
		priv->tx_failed++;
		वापस NET_XMIT_DROP;
	पूर्ण

	skb->dev = priv->lowerdev;
	वापस dev_queue_xmit(skb);
पूर्ण

/* Called with rtnl lock held. */
अटल पूर्णांक virt_wअगरi_net_device_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा virt_wअगरi_netdev_priv *priv = netdev_priv(dev);

	priv->is_up = true;
	वापस 0;
पूर्ण

/* Called with rtnl lock held. */
अटल पूर्णांक virt_wअगरi_net_device_stop(काष्ठा net_device *dev)
अणु
	काष्ठा virt_wअगरi_netdev_priv *n_priv = netdev_priv(dev);

	n_priv->is_up = false;

	अगर (!dev->ieee80211_ptr)
		वापस 0;

	virt_wअगरi_cancel_scan(dev->ieee80211_ptr->wiphy);
	virt_wअगरi_cancel_connect(dev);
	netअगर_carrier_off(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक virt_wअगरi_net_device_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा virt_wअगरi_netdev_priv *priv = netdev_priv(dev);

	वापस priv->lowerdev->अगरindex;
पूर्ण

अटल स्थिर काष्ठा net_device_ops virt_wअगरi_ops = अणु
	.nकरो_start_xmit = virt_wअगरi_start_xmit,
	.nकरो_खोलो	= virt_wअगरi_net_device_खोलो,
	.nकरो_stop	= virt_wअगरi_net_device_stop,
	.nकरो_get_अगरlink = virt_wअगरi_net_device_get_अगरlink,
पूर्ण;

/* Invoked as part of rtnl lock release. */
अटल व्योम virt_wअगरi_net_device_deकाष्ठाor(काष्ठा net_device *dev)
अणु
	/* Delayed past dellink to allow nl80211 to react to the device being
	 * deleted.
	 */
	kमुक्त(dev->ieee80211_ptr);
	dev->ieee80211_ptr = शून्य;
पूर्ण

/* No lock पूर्णांकeraction. */
अटल व्योम virt_wअगरi_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);
	dev->netdev_ops = &virt_wअगरi_ops;
	dev->needs_मुक्त_netdev  = true;
पूर्ण

/* Called in a RCU पढ़ो critical section from netअगर_receive_skb */
अटल rx_handler_result_t virt_wअगरi_rx_handler(काष्ठा sk_buff **pskb)
अणु
	काष्ठा sk_buff *skb = *pskb;
	काष्ठा virt_wअगरi_netdev_priv *priv =
		rcu_dereference(skb->dev->rx_handler_data);

	अगर (!priv->is_connected)
		वापस RX_HANDLER_PASS;

	/* GFP_ATOMIC because this is a packet पूर्णांकerrupt handler. */
	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb) अणु
		dev_err(&priv->upperdev->dev, "can't skb_share_check\n");
		वापस RX_HANDLER_CONSUMED;
	पूर्ण

	*pskb = skb;
	skb->dev = priv->upperdev;
	skb->pkt_type = PACKET_HOST;
	वापस RX_HANDLER_ANOTHER;
पूर्ण

/* Called with rtnl lock held. */
अटल पूर्णांक virt_wअगरi_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			     काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा virt_wअगरi_netdev_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	अगर (!tb[IFLA_LINK])
		वापस -EINVAL;

	netअगर_carrier_off(dev);

	priv->upperdev = dev;
	priv->lowerdev = __dev_get_by_index(src_net,
					    nla_get_u32(tb[IFLA_LINK]));

	अगर (!priv->lowerdev)
		वापस -ENODEV;
	अगर (!tb[IFLA_MTU])
		dev->mtu = priv->lowerdev->mtu;
	अन्यथा अगर (dev->mtu > priv->lowerdev->mtu)
		वापस -EINVAL;

	err = netdev_rx_handler_रेजिस्टर(priv->lowerdev, virt_wअगरi_rx_handler,
					 priv);
	अगर (err) अणु
		dev_err(&priv->lowerdev->dev,
			"can't netdev_rx_handler_register: %d\n", err);
		वापस err;
	पूर्ण

	eth_hw_addr_inherit(dev, priv->lowerdev);
	netअगर_stacked_transfer_operstate(priv->lowerdev, dev);

	SET_NETDEV_DEV(dev, &priv->lowerdev->dev);
	dev->ieee80211_ptr = kzalloc(माप(*dev->ieee80211_ptr), GFP_KERNEL);

	अगर (!dev->ieee80211_ptr) अणु
		err = -ENOMEM;
		जाओ हटाओ_handler;
	पूर्ण

	dev->ieee80211_ptr->अगरtype = NL80211_IFTYPE_STATION;
	dev->ieee80211_ptr->wiphy = common_wiphy;

	err = रेजिस्टर_netdevice(dev);
	अगर (err) अणु
		dev_err(&priv->lowerdev->dev, "can't register_netdevice: %d\n",
			err);
		जाओ मुक्त_wireless_dev;
	पूर्ण

	err = netdev_upper_dev_link(priv->lowerdev, dev, extack);
	अगर (err) अणु
		dev_err(&priv->lowerdev->dev, "can't netdev_upper_dev_link: %d\n",
			err);
		जाओ unरेजिस्टर_netdev;
	पूर्ण

	dev->priv_deकाष्ठाor = virt_wअगरi_net_device_deकाष्ठाor;
	priv->being_deleted = false;
	priv->is_connected = false;
	priv->is_up = false;
	INIT_DELAYED_WORK(&priv->connect, virt_wअगरi_connect_complete);
	__module_get(THIS_MODULE);

	वापस 0;
unरेजिस्टर_netdev:
	unरेजिस्टर_netdevice(dev);
मुक्त_wireless_dev:
	kमुक्त(dev->ieee80211_ptr);
	dev->ieee80211_ptr = शून्य;
हटाओ_handler:
	netdev_rx_handler_unरेजिस्टर(priv->lowerdev);

	वापस err;
पूर्ण

/* Called with rtnl lock held. */
अटल व्योम virt_wअगरi_dellink(काष्ठा net_device *dev,
			      काष्ठा list_head *head)
अणु
	काष्ठा virt_wअगरi_netdev_priv *priv = netdev_priv(dev);

	अगर (dev->ieee80211_ptr)
		virt_wअगरi_cancel_scan(dev->ieee80211_ptr->wiphy);

	priv->being_deleted = true;
	virt_wअगरi_cancel_connect(dev);
	netअगर_carrier_off(dev);

	netdev_rx_handler_unरेजिस्टर(priv->lowerdev);
	netdev_upper_dev_unlink(priv->lowerdev, dev);

	unरेजिस्टर_netdevice_queue(dev, head);
	module_put(THIS_MODULE);

	/* Deleting the wiphy is handled in the module deकाष्ठाor. */
पूर्ण

अटल काष्ठा rtnl_link_ops virt_wअगरi_link_ops = अणु
	.kind		= "virt_wifi",
	.setup		= virt_wअगरi_setup,
	.newlink	= virt_wअगरi_newlink,
	.dellink	= virt_wअगरi_dellink,
	.priv_size	= माप(काष्ठा virt_wअगरi_netdev_priv),
पूर्ण;

अटल bool netअगर_is_virt_wअगरi_dev(स्थिर काष्ठा net_device *dev)
अणु
	वापस rcu_access_poपूर्णांकer(dev->rx_handler) == virt_wअगरi_rx_handler;
पूर्ण

अटल पूर्णांक virt_wअगरi_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			   व्योम *ptr)
अणु
	काष्ठा net_device *lower_dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा virt_wअगरi_netdev_priv *priv;
	काष्ठा net_device *upper_dev;
	LIST_HEAD(list_समाप्त);

	अगर (!netअगर_is_virt_wअगरi_dev(lower_dev))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UNREGISTER:
		priv = rtnl_dereference(lower_dev->rx_handler_data);
		अगर (!priv)
			वापस NOTIFY_DONE;

		upper_dev = priv->upperdev;

		upper_dev->rtnl_link_ops->dellink(upper_dev, &list_समाप्त);
		unरेजिस्टर_netdevice_many(&list_समाप्त);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block virt_wअगरi_notअगरier = अणु
	.notअगरier_call = virt_wअगरi_event,
पूर्ण;

/* Acquires and releases the rtnl lock. */
अटल पूर्णांक __init virt_wअगरi_init_module(व्योम)
अणु
	पूर्णांक err;

	/* Guaranteed to be locallly-administered and not multicast. */
	eth_अक्रमom_addr(fake_router_bssid);

	err = रेजिस्टर_netdevice_notअगरier(&virt_wअगरi_notअगरier);
	अगर (err)
		वापस err;

	err = -ENOMEM;
	common_wiphy = virt_wअगरi_make_wiphy();
	अगर (!common_wiphy)
		जाओ notअगरier;

	err = rtnl_link_रेजिस्टर(&virt_wअगरi_link_ops);
	अगर (err)
		जाओ destroy_wiphy;

	वापस 0;

destroy_wiphy:
	virt_wअगरi_destroy_wiphy(common_wiphy);
notअगरier:
	unरेजिस्टर_netdevice_notअगरier(&virt_wअगरi_notअगरier);
	वापस err;
पूर्ण

/* Acquires and releases the rtnl lock. */
अटल व्योम __निकास virt_wअगरi_cleanup_module(व्योम)
अणु
	/* Will delete any devices that depend on the wiphy. */
	rtnl_link_unरेजिस्टर(&virt_wअगरi_link_ops);
	virt_wअगरi_destroy_wiphy(common_wiphy);
	unरेजिस्टर_netdevice_notअगरier(&virt_wअगरi_notअगरier);
पूर्ण

module_init(virt_wअगरi_init_module);
module_निकास(virt_wअगरi_cleanup_module);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Cody Schuffelen <schuffelen@google.com>");
MODULE_DESCRIPTION("Driver for a wireless wrapper of ethernet devices");
MODULE_ALIAS_RTNL_LINK("virt_wifi");
