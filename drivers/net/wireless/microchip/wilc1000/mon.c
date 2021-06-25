<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#समावेश "cfg80211.h"

काष्ठा wilc_wfi_radiotap_hdr अणु
	काष्ठा ieee80211_radiotap_header hdr;
	u8 rate;
पूर्ण __packed;

काष्ठा wilc_wfi_radiotap_cb_hdr अणु
	काष्ठा ieee80211_radiotap_header hdr;
	u8 rate;
	u8 dump;
	u16 tx_flags;
पूर्ण __packed;

#घोषणा TX_RADIOTAP_PRESENT ((1 << IEEE80211_RADIOTAP_RATE) |	\
			     (1 << IEEE80211_RADIOTAP_TX_FLAGS))

व्योम wilc_wfi_monitor_rx(काष्ठा net_device *mon_dev, u8 *buff, u32 size)
अणु
	u32 header, pkt_offset;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा wilc_wfi_radiotap_hdr *hdr;
	काष्ठा wilc_wfi_radiotap_cb_hdr *cb_hdr;

	अगर (!mon_dev)
		वापस;

	अगर (!netअगर_running(mon_dev))
		वापस;

	/* Get WILC header */
	header = get_unaligned_le32(buff - HOST_HDR_OFFSET);
	/*
	 * The packet offset field contain info about what type of management
	 * the frame we are dealing with and ack status
	 */
	pkt_offset = FIELD_GET(WILC_PKT_HDR_OFFSET_FIELD, header);

	अगर (pkt_offset & IS_MANAGMEMENT_CALLBACK) अणु
		/* hostapd callback mgmt frame */

		skb = dev_alloc_skb(size + माप(*cb_hdr));
		अगर (!skb)
			वापस;

		skb_put_data(skb, buff, size);

		cb_hdr = skb_push(skb, माप(*cb_hdr));
		स_रखो(cb_hdr, 0, माप(*cb_hdr));

		cb_hdr->hdr.it_version = 0; /* PKTHDR_RADIOTAP_VERSION; */

		cb_hdr->hdr.it_len = cpu_to_le16(माप(*cb_hdr));

		cb_hdr->hdr.it_present = cpu_to_le32(TX_RADIOTAP_PRESENT);

		cb_hdr->rate = 5;

		अगर (pkt_offset & IS_MGMT_STATUS_SUCCES)	अणु
			/* success */
			cb_hdr->tx_flags = IEEE80211_RADIOTAP_F_TX_RTS;
		पूर्ण अन्यथा अणु
			cb_hdr->tx_flags = IEEE80211_RADIOTAP_F_TX_FAIL;
		पूर्ण

	पूर्ण अन्यथा अणु
		skb = dev_alloc_skb(size + माप(*hdr));

		अगर (!skb)
			वापस;

		skb_put_data(skb, buff, size);
		hdr = skb_push(skb, माप(*hdr));
		स_रखो(hdr, 0, माप(काष्ठा wilc_wfi_radiotap_hdr));
		hdr->hdr.it_version = 0; /* PKTHDR_RADIOTAP_VERSION; */
		hdr->hdr.it_len = cpu_to_le16(माप(*hdr));
		hdr->hdr.it_present = cpu_to_le32
				(1 << IEEE80211_RADIOTAP_RATE);
		hdr->rate = 5;
	पूर्ण

	skb->dev = mon_dev;
	skb_reset_mac_header(skb);
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = htons(ETH_P_802_2);
	स_रखो(skb->cb, 0, माप(skb->cb));

	netअगर_rx(skb);
पूर्ण

काष्ठा tx_complete_mon_data अणु
	पूर्णांक size;
	व्योम *buff;
पूर्ण;

अटल व्योम mgmt_tx_complete(व्योम *priv, पूर्णांक status)
अणु
	काष्ठा tx_complete_mon_data *pv_data = priv;
	/*
	 * in हाल of fully hosting mode, the मुक्तing will be करोne
	 * in response to the cfg packet
	 */
	kमुक्त(pv_data->buff);

	kमुक्त(pv_data);
पूर्ण

अटल पूर्णांक mon_mgmt_tx(काष्ठा net_device *dev, स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा tx_complete_mon_data *mgmt_tx = शून्य;

	अगर (!dev)
		वापस -EFAULT;

	netअगर_stop_queue(dev);
	mgmt_tx = kदो_स्मृति(माप(*mgmt_tx), GFP_ATOMIC);
	अगर (!mgmt_tx)
		वापस -ENOMEM;

	mgmt_tx->buff = kmemdup(buf, len, GFP_ATOMIC);
	अगर (!mgmt_tx->buff) अणु
		kमुक्त(mgmt_tx);
		वापस -ENOMEM;
	पूर्ण

	mgmt_tx->size = len;

	wilc_wlan_txq_add_mgmt_pkt(dev, mgmt_tx, mgmt_tx->buff, mgmt_tx->size,
				   mgmt_tx_complete);

	netअगर_wake_queue(dev);
	वापस 0;
पूर्ण

अटल netdev_tx_t wilc_wfi_mon_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
अणु
	u32 rtap_len, ret = 0;
	काष्ठा wilc_wfi_mon_priv  *mon_priv;
	काष्ठा sk_buff *skb2;
	काष्ठा wilc_wfi_radiotap_cb_hdr *cb_hdr;
	u8 srcadd[ETH_ALEN];
	u8 bssid[ETH_ALEN];

	mon_priv = netdev_priv(dev);
	अगर (!mon_priv)
		वापस -EFAULT;

	rtap_len = ieee80211_get_radiotap_len(skb->data);
	अगर (skb->len < rtap_len)
		वापस -1;

	skb_pull(skb, rtap_len);

	अगर (skb->data[0] == 0xc0 && is_broadcast_ether_addr(&skb->data[4])) अणु
		skb2 = dev_alloc_skb(skb->len + माप(*cb_hdr));
		अगर (!skb2)
			वापस -ENOMEM;

		skb_put_data(skb2, skb->data, skb->len);

		cb_hdr = skb_push(skb2, माप(*cb_hdr));
		स_रखो(cb_hdr, 0, माप(काष्ठा wilc_wfi_radiotap_cb_hdr));

		cb_hdr->hdr.it_version = 0; /* PKTHDR_RADIOTAP_VERSION; */

		cb_hdr->hdr.it_len = cpu_to_le16(माप(*cb_hdr));

		cb_hdr->hdr.it_present = cpu_to_le32(TX_RADIOTAP_PRESENT);

		cb_hdr->rate = 5;
		cb_hdr->tx_flags = 0x0004;

		skb2->dev = dev;
		skb_reset_mac_header(skb2);
		skb2->ip_summed = CHECKSUM_UNNECESSARY;
		skb2->pkt_type = PACKET_OTHERHOST;
		skb2->protocol = htons(ETH_P_802_2);
		स_रखो(skb2->cb, 0, माप(skb2->cb));

		netअगर_rx(skb2);

		वापस 0;
	पूर्ण
	skb->dev = mon_priv->real_ndev;

	ether_addr_copy(srcadd, &skb->data[10]);
	ether_addr_copy(bssid, &skb->data[16]);
	/*
	 * Identअगरy अगर data or mgmt packet, अगर source address and bssid
	 * fields are equal send it to mgmt frames handler
	 */
	अगर (!(स_भेद(srcadd, bssid, 6))) अणु
		ret = mon_mgmt_tx(mon_priv->real_ndev, skb->data, skb->len);
		अगर (ret)
			netdev_err(dev, "fail to mgmt tx\n");
		dev_kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		ret = wilc_mac_xmit(skb, mon_priv->real_ndev);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops wilc_wfi_netdev_ops = अणु
	.nकरो_start_xmit         = wilc_wfi_mon_xmit,

पूर्ण;

काष्ठा net_device *wilc_wfi_init_mon_पूर्णांकerface(काष्ठा wilc *wl,
					       स्थिर अक्षर *name,
					       काष्ठा net_device *real_dev)
अणु
	काष्ठा wilc_wfi_mon_priv *priv;

	/* If monitor पूर्णांकerface is alपढ़ोy initialized, वापस it */
	अगर (wl->monitor_dev)
		वापस wl->monitor_dev;

	wl->monitor_dev = alloc_etherdev(माप(काष्ठा wilc_wfi_mon_priv));
	अगर (!wl->monitor_dev)
		वापस शून्य;

	wl->monitor_dev->type = ARPHRD_IEEE80211_RADIOTAP;
	strlcpy(wl->monitor_dev->name, name, IFNAMSIZ);
	wl->monitor_dev->netdev_ops = &wilc_wfi_netdev_ops;
	wl->monitor_dev->needs_मुक्त_netdev = true;

	अगर (cfg80211_रेजिस्टर_netdevice(wl->monitor_dev)) अणु
		netdev_err(real_dev, "register_netdevice failed\n");
		मुक्त_netdev(wl->monitor_dev);
		वापस शून्य;
	पूर्ण
	priv = netdev_priv(wl->monitor_dev);

	priv->real_ndev = real_dev;

	वापस wl->monitor_dev;
पूर्ण

व्योम wilc_wfi_deinit_mon_पूर्णांकerface(काष्ठा wilc *wl, bool rtnl_locked)
अणु
	अगर (!wl->monitor_dev)
		वापस;

	अगर (rtnl_locked)
		cfg80211_unरेजिस्टर_netdevice(wl->monitor_dev);
	अन्यथा
		unरेजिस्टर_netdev(wl->monitor_dev);
	wl->monitor_dev = शून्य;
पूर्ण
