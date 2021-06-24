<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/nospec.h>

#समावेश "core.h"
#समावेश "bus.h"
#समावेश "trans.h"
#समावेश "commands.h"
#समावेश "cfg80211.h"
#समावेश "event.h"
#समावेश "util.h"
#समावेश "switchdev.h"

#घोषणा QTNF_PRIMARY_VIF_IDX	0

अटल bool slave_radar = true;
module_param(slave_radar, bool, 0644);
MODULE_PARM_DESC(slave_radar, "set 0 to disable radar detection in slave mode");

अटल bool dfs_offload;
module_param(dfs_offload, bool, 0644);
MODULE_PARM_DESC(dfs_offload, "set 1 to enable DFS offload to firmware");

अटल काष्ठा dentry *qtnf_debugfs_dir;

bool qtnf_slave_radar_get(व्योम)
अणु
	वापस slave_radar;
पूर्ण

bool qtnf_dfs_offload_get(व्योम)
अणु
	वापस dfs_offload;
पूर्ण

काष्ठा qtnf_wmac *qtnf_core_get_mac(स्थिर काष्ठा qtnf_bus *bus, u8 macid)
अणु
	काष्ठा qtnf_wmac *mac = शून्य;

	अगर (macid >= QTNF_MAX_MAC) अणु
		pr_err("invalid MAC index %u\n", macid);
		वापस शून्य;
	पूर्ण

	macid = array_index_nospec(macid, QTNF_MAX_MAC);
	mac = bus->mac[macid];

	अगर (unlikely(!mac)) अणु
		pr_err("MAC%u: not initialized\n", macid);
		वापस शून्य;
	पूर्ण

	वापस mac;
पूर्ण

/* Netdev handler क्रम खोलो.
 */
अटल पूर्णांक qtnf_netdev_खोलो(काष्ठा net_device *ndev)
अणु
	netअगर_carrier_off(ndev);
	qtnf_netdev_upकरोwn(ndev, 1);
	वापस 0;
पूर्ण

/* Netdev handler क्रम बंद.
 */
अटल पूर्णांक qtnf_netdev_बंद(काष्ठा net_device *ndev)
अणु
	netअगर_carrier_off(ndev);
	qtnf_भव_पूर्णांकf_cleanup(ndev);
	qtnf_netdev_upकरोwn(ndev, 0);
	वापस 0;
पूर्ण

अटल व्योम qtnf_packet_send_hi_pri(काष्ठा sk_buff *skb)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(skb->dev);

	skb_queue_tail(&vअगर->high_pri_tx_queue, skb);
	queue_work(vअगर->mac->bus->hprio_workqueue, &vअगर->high_pri_tx_work);
पूर्ण

/* Netdev handler क्रम data transmission.
 */
अटल netdev_tx_t
qtnf_netdev_hard_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा qtnf_vअगर *vअगर;
	काष्ठा qtnf_wmac *mac;

	vअगर = qtnf_netdev_get_priv(ndev);

	अगर (unlikely(skb->dev != ndev)) अणु
		pr_err_ratelimited("invalid skb->dev");
		dev_kमुक्त_skb_any(skb);
		वापस 0;
	पूर्ण

	अगर (unlikely(vअगर->wdev.अगरtype == NL80211_IFTYPE_UNSPECIFIED)) अणु
		pr_err_ratelimited("%s: VIF not initialized\n", ndev->name);
		dev_kमुक्त_skb_any(skb);
		वापस 0;
	पूर्ण

	mac = vअगर->mac;
	अगर (unlikely(!mac)) अणु
		pr_err_ratelimited("%s: NULL mac pointer", ndev->name);
		dev_kमुक्त_skb_any(skb);
		वापस 0;
	पूर्ण

	अगर (!skb->len || (skb->len > ETH_FRAME_LEN)) अणु
		pr_err_ratelimited("%s: invalid skb len %d\n", ndev->name,
				   skb->len);
		dev_kमुक्त_skb_any(skb);
		ndev->stats.tx_dropped++;
		वापस 0;
	पूर्ण

	/* tx path is enabled: reset vअगर समयout */
	vअगर->cons_tx_समयout_cnt = 0;

	अगर (unlikely(skb->protocol == htons(ETH_P_PAE))) अणु
		qtnf_packet_send_hi_pri(skb);
		dev_sw_netstats_tx_add(ndev, 1, skb->len);
		वापस NETDEV_TX_OK;
	पूर्ण

	वापस qtnf_bus_data_tx(mac->bus, skb, mac->macid, vअगर->vअगरid);
पूर्ण

/* Netdev handler क्रम transmission समयout.
 */
अटल व्योम qtnf_netdev_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(ndev);
	काष्ठा qtnf_wmac *mac;
	काष्ठा qtnf_bus *bus;

	अगर (unlikely(!vअगर || !vअगर->mac || !vअगर->mac->bus))
		वापस;

	mac = vअगर->mac;
	bus = mac->bus;

	pr_warn("VIF%u.%u: Tx timeout- %lu\n", mac->macid, vअगर->vअगरid, jअगरfies);

	qtnf_bus_data_tx_समयout(bus, ndev);
	ndev->stats.tx_errors++;

	अगर (++vअगर->cons_tx_समयout_cnt > QTNF_TX_TIMEOUT_TRSHLD) अणु
		pr_err("Tx timeout threshold exceeded !\n");
		pr_err("schedule interface %s reset !\n", netdev_name(ndev));
		queue_work(bus->workqueue, &vअगर->reset_work);
	पूर्ण
पूर्ण

अटल पूर्णांक qtnf_netdev_set_mac_address(काष्ठा net_device *ndev, व्योम *addr)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(ndev);
	काष्ठा sockaddr *sa = addr;
	पूर्णांक ret;
	अचिन्हित अक्षर old_addr[ETH_ALEN];

	स_नकल(old_addr, sa->sa_data, माप(old_addr));

	ret = eth_mac_addr(ndev, sa);
	अगर (ret)
		वापस ret;

	qtnf_scan_करोne(vअगर->mac, true);

	ret = qtnf_cmd_send_change_पूर्णांकf_type(vअगर, vअगर->wdev.अगरtype,
					     vअगर->wdev.use_4addr,
					     sa->sa_data);

	अगर (ret)
		स_नकल(ndev->dev_addr, old_addr, ETH_ALEN);

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_netdev_port_parent_id(काष्ठा net_device *ndev,
				      काष्ठा netdev_phys_item_id *ppid)
अणु
	स्थिर काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(ndev);
	स्थिर काष्ठा qtnf_bus *bus = vअगर->mac->bus;

	ppid->id_len = माप(bus->hw_id);
	स_नकल(&ppid->id, bus->hw_id, ppid->id_len);

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_netdev_alloc_pcpu_stats(काष्ठा net_device *dev)
अणु
	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);

	वापस dev->tstats ? 0 : -ENOMEM;
पूर्ण

अटल व्योम qtnf_netdev_मुक्त_pcpu_stats(काष्ठा net_device *dev)
अणु
	मुक्त_percpu(dev->tstats);
पूर्ण

/* Network device ops handlers */
स्थिर काष्ठा net_device_ops qtnf_netdev_ops = अणु
	.nकरो_init = qtnf_netdev_alloc_pcpu_stats,
	.nकरो_uninit = qtnf_netdev_मुक्त_pcpu_stats,
	.nकरो_खोलो = qtnf_netdev_खोलो,
	.nकरो_stop = qtnf_netdev_बंद,
	.nकरो_start_xmit = qtnf_netdev_hard_start_xmit,
	.nकरो_tx_समयout = qtnf_netdev_tx_समयout,
	.nकरो_get_stats64 = dev_get_tstats64,
	.nकरो_set_mac_address = qtnf_netdev_set_mac_address,
	.nकरो_get_port_parent_id = qtnf_netdev_port_parent_id,
पूर्ण;

अटल पूर्णांक qtnf_mac_init_single_band(काष्ठा wiphy *wiphy,
				     काष्ठा qtnf_wmac *mac,
				     क्रमागत nl80211_band band)
अणु
	पूर्णांक ret;

	wiphy->bands[band] = kzalloc(माप(*wiphy->bands[band]), GFP_KERNEL);
	अगर (!wiphy->bands[band])
		वापस -ENOMEM;

	wiphy->bands[band]->band = band;

	ret = qtnf_cmd_band_info_get(mac, wiphy->bands[band]);
	अगर (ret) अणु
		pr_err("MAC%u: band %u: failed to get chans info: %d\n",
		       mac->macid, band, ret);
		वापस ret;
	पूर्ण

	qtnf_band_init_rates(wiphy->bands[band]);

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_mac_init_bands(काष्ठा qtnf_wmac *mac)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(mac);
	पूर्णांक ret = 0;

	अगर (mac->macinfo.bands_cap & QLINK_BAND_2GHZ) अणु
		ret = qtnf_mac_init_single_band(wiphy, mac, NL80211_BAND_2GHZ);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (mac->macinfo.bands_cap & QLINK_BAND_5GHZ) अणु
		ret = qtnf_mac_init_single_band(wiphy, mac, NL80211_BAND_5GHZ);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (mac->macinfo.bands_cap & QLINK_BAND_60GHZ)
		ret = qtnf_mac_init_single_band(wiphy, mac, NL80211_BAND_60GHZ);

out:
	वापस ret;
पूर्ण

काष्ठा qtnf_vअगर *qtnf_mac_get_मुक्त_vअगर(काष्ठा qtnf_wmac *mac)
अणु
	काष्ठा qtnf_vअगर *vअगर;
	पूर्णांक i;

	क्रम (i = 0; i < QTNF_MAX_INTF; i++) अणु
		vअगर = &mac->अगरlist[i];
		अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_UNSPECIFIED)
			वापस vअगर;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा qtnf_vअगर *qtnf_mac_get_base_vअगर(काष्ठा qtnf_wmac *mac)
अणु
	काष्ठा qtnf_vअगर *vअगर;

	vअगर = &mac->अगरlist[QTNF_PRIMARY_VIF_IDX];

	अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_UNSPECIFIED)
		वापस शून्य;

	वापस vअगर;
पूर्ण

व्योम qtnf_mac_अगरace_comb_मुक्त(काष्ठा qtnf_wmac *mac)
अणु
	काष्ठा ieee80211_अगरace_combination *comb;
	पूर्णांक i;

	अगर (mac->macinfo.अगर_comb) अणु
		क्रम (i = 0; i < mac->macinfo.n_अगर_comb; i++) अणु
			comb = &mac->macinfo.अगर_comb[i];
			kमुक्त(comb->limits);
			comb->limits = शून्य;
		पूर्ण

		kमुक्त(mac->macinfo.अगर_comb);
		mac->macinfo.अगर_comb = शून्य;
	पूर्ण
पूर्ण

व्योम qtnf_mac_ext_caps_मुक्त(काष्ठा qtnf_wmac *mac)
अणु
	अगर (mac->macinfo.extended_capabilities_len) अणु
		kमुक्त(mac->macinfo.extended_capabilities);
		mac->macinfo.extended_capabilities = शून्य;

		kमुक्त(mac->macinfo.extended_capabilities_mask);
		mac->macinfo.extended_capabilities_mask = शून्य;

		mac->macinfo.extended_capabilities_len = 0;
	पूर्ण
पूर्ण

अटल व्योम qtnf_vअगर_reset_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qtnf_vअगर *vअगर = container_of(work, काष्ठा qtnf_vअगर, reset_work);

	rtnl_lock();

	अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_UNSPECIFIED) अणु
		rtnl_unlock();
		वापस;
	पूर्ण

	/* stop tx completely */
	netअगर_tx_stop_all_queues(vअगर->netdev);
	अगर (netअगर_carrier_ok(vअगर->netdev))
		netअगर_carrier_off(vअगर->netdev);

	qtnf_cfg80211_vअगर_reset(vअगर);

	rtnl_unlock();
पूर्ण

अटल व्योम qtnf_mac_init_primary_पूर्णांकf(काष्ठा qtnf_wmac *mac)
अणु
	काष्ठा qtnf_vअगर *vअगर = &mac->अगरlist[QTNF_PRIMARY_VIF_IDX];

	vअगर->wdev.अगरtype = NL80211_IFTYPE_STATION;
	vअगर->bss_priority = QTNF_DEF_BSS_PRIORITY;
	vअगर->wdev.wiphy = priv_to_wiphy(mac);
	INIT_WORK(&vअगर->reset_work, qtnf_vअगर_reset_handler);
	vअगर->cons_tx_समयout_cnt = 0;
पूर्ण

अटल व्योम qtnf_mac_scan_finish(काष्ठा qtnf_wmac *mac, bool पातed)
अणु
	काष्ठा cfg80211_scan_info info = अणु
		.पातed = पातed,
	पूर्ण;

	mutex_lock(&mac->mac_lock);

	अगर (mac->scan_req) अणु
		cfg80211_scan_करोne(mac->scan_req, &info);
		mac->scan_req = शून्य;
	पूर्ण

	mutex_unlock(&mac->mac_lock);
पूर्ण

व्योम qtnf_scan_करोne(काष्ठा qtnf_wmac *mac, bool पातed)
अणु
	cancel_delayed_work_sync(&mac->scan_समयout);
	qtnf_mac_scan_finish(mac, पातed);
पूर्ण

अटल व्योम qtnf_mac_scan_समयout(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qtnf_wmac *mac =
		container_of(work, काष्ठा qtnf_wmac, scan_समयout.work);

	pr_warn("MAC%d: scan timed out\n", mac->macid);
	qtnf_mac_scan_finish(mac, true);
पूर्ण

अटल व्योम qtnf_vअगर_send_data_high_pri(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qtnf_vअगर *vअगर =
		container_of(work, काष्ठा qtnf_vअगर, high_pri_tx_work);
	काष्ठा sk_buff *skb;

	अगर (!vअगर->netdev ||
	    vअगर->wdev.अगरtype == NL80211_IFTYPE_UNSPECIFIED)
		वापस;

	जबतक ((skb = skb_dequeue(&vअगर->high_pri_tx_queue))) अणु
		qtnf_cmd_send_frame(vअगर, 0, QLINK_FRAME_TX_FLAG_8023,
				    0, skb->data, skb->len);
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल काष्ठा qtnf_wmac *qtnf_core_mac_alloc(काष्ठा qtnf_bus *bus,
					     अचिन्हित पूर्णांक macid)
अणु
	काष्ठा platक्रमm_device *pdev = शून्य;
	काष्ठा qtnf_wmac *mac;
	काष्ठा qtnf_vअगर *vअगर;
	काष्ठा wiphy *wiphy;
	अचिन्हित पूर्णांक i;

	अगर (bus->hw_info.num_mac > 1) अणु
		pdev = platक्रमm_device_रेजिस्टर_data(bus->dev,
						     dev_name(bus->dev),
						     macid, शून्य, 0);
		अगर (IS_ERR(pdev))
			वापस ERR_PTR(-EINVAL);
	पूर्ण

	wiphy = qtnf_wiphy_allocate(bus, pdev);
	अगर (!wiphy) अणु
		अगर (pdev)
			platक्रमm_device_unरेजिस्टर(pdev);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	mac = wiphy_priv(wiphy);

	mac->macid = macid;
	mac->pdev = pdev;
	mac->bus = bus;
	mutex_init(&mac->mac_lock);
	INIT_DELAYED_WORK(&mac->scan_समयout, qtnf_mac_scan_समयout);

	क्रम (i = 0; i < QTNF_MAX_INTF; i++) अणु
		vअगर = &mac->अगरlist[i];

		स_रखो(vअगर, 0, माप(*vअगर));
		vअगर->wdev.अगरtype = NL80211_IFTYPE_UNSPECIFIED;
		vअगर->mac = mac;
		vअगर->vअगरid = i;
		qtnf_sta_list_init(&vअगर->sta_list);
		INIT_WORK(&vअगर->high_pri_tx_work, qtnf_vअगर_send_data_high_pri);
		skb_queue_head_init(&vअगर->high_pri_tx_queue);
	पूर्ण

	qtnf_mac_init_primary_पूर्णांकf(mac);
	bus->mac[macid] = mac;

	वापस mac;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops qtnf_ethtool_ops = अणु
	.get_drvinfo = cfg80211_get_drvinfo,
पूर्ण;

पूर्णांक qtnf_core_net_attach(काष्ठा qtnf_wmac *mac, काष्ठा qtnf_vअगर *vअगर,
			 स्थिर अक्षर *name, अचिन्हित अक्षर name_assign_type)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(mac);
	काष्ठा net_device *dev;
	व्योम *qdev_vअगर;
	पूर्णांक ret;

	dev = alloc_netdev_mqs(माप(काष्ठा qtnf_vअगर *), name,
			       name_assign_type, ether_setup, 1, 1);
	अगर (!dev)
		वापस -ENOMEM;

	vअगर->netdev = dev;

	dev->netdev_ops = &qtnf_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	dev_net_set(dev, wiphy_net(wiphy));
	dev->ieee80211_ptr = &vअगर->wdev;
	ether_addr_copy(dev->dev_addr, vअगर->mac_addr);
	dev->flags |= IFF_BROADCAST | IFF_MULTICAST;
	dev->watchकरोg_समयo = QTNF_DEF_WDOG_TIMEOUT;
	dev->tx_queue_len = 100;
	dev->ethtool_ops = &qtnf_ethtool_ops;

	अगर (qtnf_hwcap_is_set(&mac->bus->hw_info, QLINK_HW_CAPAB_HW_BRIDGE))
		dev->needed_tailroom = माप(काष्ठा qtnf_frame_meta_info);

	qdev_vअगर = netdev_priv(dev);
	*((व्योम **)qdev_vअगर) = vअगर;

	SET_NETDEV_DEV(dev, wiphy_dev(wiphy));

	ret = cfg80211_रेजिस्टर_netdevice(dev);
	अगर (ret) अणु
		मुक्त_netdev(dev);
		vअगर->netdev = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम qtnf_core_mac_detach(काष्ठा qtnf_bus *bus, अचिन्हित पूर्णांक macid)
अणु
	काष्ठा qtnf_wmac *mac;
	काष्ठा wiphy *wiphy;
	काष्ठा qtnf_vअगर *vअगर;
	अचिन्हित पूर्णांक i;
	क्रमागत nl80211_band band;

	mac = bus->mac[macid];

	अगर (!mac)
		वापस;

	wiphy = priv_to_wiphy(mac);

	क्रम (i = 0; i < QTNF_MAX_INTF; i++) अणु
		vअगर = &mac->अगरlist[i];
		rtnl_lock();
		अगर (vअगर->netdev &&
		    vअगर->wdev.अगरtype != NL80211_IFTYPE_UNSPECIFIED) अणु
			qtnf_भव_पूर्णांकf_cleanup(vअगर->netdev);
			qtnf_del_भव_पूर्णांकf(wiphy, &vअगर->wdev);
		पूर्ण
		rtnl_unlock();
		qtnf_sta_list_मुक्त(&vअगर->sta_list);
	पूर्ण

	अगर (mac->wiphy_रेजिस्टरed)
		wiphy_unरेजिस्टर(wiphy);

	क्रम (band = NL80211_BAND_2GHZ; band < NUM_NL80211_BANDS; ++band) अणु
		अगर (!wiphy->bands[band])
			जारी;

		kमुक्त(wiphy->bands[band]->अगरtype_data);
		wiphy->bands[band]->n_अगरtype_data = 0;

		kमुक्त(wiphy->bands[band]->channels);
		wiphy->bands[band]->n_channels = 0;

		kमुक्त(wiphy->bands[band]);
		wiphy->bands[band] = शून्य;
	पूर्ण

	platक्रमm_device_unरेजिस्टर(mac->pdev);
	qtnf_mac_अगरace_comb_मुक्त(mac);
	qtnf_mac_ext_caps_मुक्त(mac);
	kमुक्त(mac->macinfo.wowlan);
	kमुक्त(mac->rd);
	mac->rd = शून्य;
	wiphy_मुक्त(wiphy);
	bus->mac[macid] = शून्य;
पूर्ण

अटल पूर्णांक qtnf_core_mac_attach(काष्ठा qtnf_bus *bus, अचिन्हित पूर्णांक macid)
अणु
	काष्ठा qtnf_wmac *mac;
	काष्ठा qtnf_vअगर *vअगर;
	पूर्णांक ret;

	अगर (!(bus->hw_info.mac_biपंचांगap & BIT(macid))) अणु
		pr_info("MAC%u is not active in FW\n", macid);
		वापस 0;
	पूर्ण

	mac = qtnf_core_mac_alloc(bus, macid);
	अगर (IS_ERR(mac)) अणु
		pr_err("MAC%u allocation failed\n", macid);
		वापस PTR_ERR(mac);
	पूर्ण

	vअगर = qtnf_mac_get_base_vअगर(mac);
	अगर (!vअगर) अणु
		pr_err("MAC%u: primary VIF is not ready\n", macid);
		ret = -EFAULT;
		जाओ error;
	पूर्ण

	ret = qtnf_cmd_send_add_पूर्णांकf(vअगर, vअगर->wdev.अगरtype,
				     vअगर->wdev.use_4addr, vअगर->mac_addr);
	अगर (ret) अणु
		pr_err("MAC%u: failed to add VIF\n", macid);
		जाओ error;
	पूर्ण

	ret = qtnf_cmd_get_mac_info(mac);
	अगर (ret) अणु
		pr_err("MAC%u: failed to get MAC info\n", macid);
		जाओ error_del_vअगर;
	पूर्ण

	/* Use MAC address of the first active radio as a unique device ID */
	अगर (is_zero_ether_addr(mac->bus->hw_id))
		ether_addr_copy(mac->bus->hw_id, mac->macaddr);

	ret = qtnf_mac_init_bands(mac);
	अगर (ret) अणु
		pr_err("MAC%u: failed to init bands\n", macid);
		जाओ error_del_vअगर;
	पूर्ण

	ret = qtnf_wiphy_रेजिस्टर(&bus->hw_info, mac);
	अगर (ret) अणु
		pr_err("MAC%u: wiphy registration failed\n", macid);
		जाओ error_del_vअगर;
	पूर्ण

	mac->wiphy_रेजिस्टरed = 1;

	rtnl_lock();
	wiphy_lock(priv_to_wiphy(mac));
	ret = qtnf_core_net_attach(mac, vअगर, "wlan%d", NET_NAME_ENUM);
	wiphy_unlock(priv_to_wiphy(mac));
	rtnl_unlock();

	अगर (ret) अणु
		pr_err("MAC%u: failed to attach netdev\n", macid);
		जाओ error_del_vअगर;
	पूर्ण

	अगर (qtnf_hwcap_is_set(&bus->hw_info, QLINK_HW_CAPAB_HW_BRIDGE)) अणु
		ret = qtnf_cmd_netdev_changeupper(vअगर, vअगर->netdev->अगरindex);
		अगर (ret)
			जाओ error;
	पूर्ण

	pr_debug("MAC%u initialized\n", macid);

	वापस 0;

error_del_vअगर:
	qtnf_cmd_send_del_पूर्णांकf(vअगर);
	vअगर->wdev.अगरtype = NL80211_IFTYPE_UNSPECIFIED;
error:
	qtnf_core_mac_detach(bus, macid);
	वापस ret;
पूर्ण

bool qtnf_netdev_is_qtn(स्थिर काष्ठा net_device *ndev)
अणु
	वापस ndev->netdev_ops == &qtnf_netdev_ops;
पूर्ण

अटल पूर्णांक qtnf_check_br_ports(काष्ठा net_device *dev,
			       काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा net_device *ndev = (काष्ठा net_device *)priv->data;

	अगर (dev != ndev && netdev_port_same_parent_id(dev, ndev))
		वापस -ENOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_core_netdevice_event(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(ptr);
	स्थिर काष्ठा netdev_notअगरier_changeupper_info *info;
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)ndev,
	पूर्ण;
	काष्ठा net_device *brdev;
	काष्ठा qtnf_vअगर *vअगर;
	काष्ठा qtnf_bus *bus;
	पूर्णांक br_करोमुख्य;
	पूर्णांक ret = 0;

	अगर (!qtnf_netdev_is_qtn(ndev))
		वापस NOTIFY_DONE;

	अगर (!net_eq(dev_net(ndev), &init_net))
		वापस NOTIFY_OK;

	vअगर = qtnf_netdev_get_priv(ndev);
	bus = vअगर->mac->bus;

	चयन (event) अणु
	हाल NETDEV_CHANGEUPPER:
		info = ptr;
		brdev = info->upper_dev;

		अगर (!netअगर_is_bridge_master(brdev))
			अवरोध;

		pr_debug("[VIF%u.%u] change bridge: %s %s\n",
			 vअगर->mac->macid, vअगर->vअगरid, netdev_name(brdev),
			 info->linking ? "add" : "del");

		अगर (IS_ENABLED(CONFIG_NET_SWITCHDEV) &&
		    qtnf_hwcap_is_set(&bus->hw_info,
				      QLINK_HW_CAPAB_HW_BRIDGE)) अणु
			अगर (info->linking)
				br_करोमुख्य = brdev->अगरindex;
			अन्यथा
				br_करोमुख्य = ndev->अगरindex;

			ret = qtnf_cmd_netdev_changeupper(vअगर, br_करोमुख्य);
		पूर्ण अन्यथा अणु
			ret = netdev_walk_all_lower_dev(brdev,
							qtnf_check_br_ports,
							&priv);
		पूर्ण

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

पूर्णांक qtnf_core_attach(काष्ठा qtnf_bus *bus)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	qtnf_trans_init(bus);
	qtnf_bus_data_rx_start(bus);

	bus->workqueue = alloc_ordered_workqueue("QTNF_BUS", 0);
	अगर (!bus->workqueue) अणु
		pr_err("failed to alloc main workqueue\n");
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	bus->hprio_workqueue = alloc_workqueue("QTNF_HPRI", WQ_HIGHPRI, 0);
	अगर (!bus->hprio_workqueue) अणु
		pr_err("failed to alloc high prio workqueue\n");
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	INIT_WORK(&bus->event_work, qtnf_event_work_handler);

	ret = qtnf_cmd_send_init_fw(bus);
	अगर (ret) अणु
		pr_err("failed to init FW: %d\n", ret);
		जाओ error;
	पूर्ण

	अगर (QLINK_VER_MAJOR(bus->hw_info.ql_proto_ver) !=
	    QLINK_PROTO_VER_MAJOR) अणु
		pr_err("qlink driver vs FW version mismatch: %u vs %u\n",
		       QLINK_PROTO_VER_MAJOR,
		       QLINK_VER_MAJOR(bus->hw_info.ql_proto_ver));
		ret = -EPROTONOSUPPORT;
		जाओ error;
	पूर्ण

	bus->fw_state = QTNF_FW_STATE_ACTIVE;
	ret = qtnf_cmd_get_hw_info(bus);
	अगर (ret) अणु
		pr_err("failed to get HW info: %d\n", ret);
		जाओ error;
	पूर्ण

	अगर (qtnf_hwcap_is_set(&bus->hw_info, QLINK_HW_CAPAB_HW_BRIDGE) &&
	    bus->bus_ops->data_tx_use_meta_set)
		bus->bus_ops->data_tx_use_meta_set(bus, true);

	अगर (bus->hw_info.num_mac > QTNF_MAX_MAC) अणु
		pr_err("no support for number of MACs=%u\n",
		       bus->hw_info.num_mac);
		ret = -दुस्फल;
		जाओ error;
	पूर्ण

	क्रम (i = 0; i < bus->hw_info.num_mac; i++) अणु
		ret = qtnf_core_mac_attach(bus, i);

		अगर (ret) अणु
			pr_err("MAC%u: attach failed: %d\n", i, ret);
			जाओ error;
		पूर्ण
	पूर्ण

	bus->netdev_nb.notअगरier_call = qtnf_core_netdevice_event;
	ret = रेजिस्टर_netdevice_notअगरier(&bus->netdev_nb);
	अगर (ret) अणु
		pr_err("failed to register netdev notifier: %d\n", ret);
		जाओ error;
	पूर्ण

	bus->fw_state = QTNF_FW_STATE_RUNNING;
	वापस 0;

error:
	qtnf_core_detach(bus);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(qtnf_core_attach);

व्योम qtnf_core_detach(काष्ठा qtnf_bus *bus)
अणु
	अचिन्हित पूर्णांक macid;

	unरेजिस्टर_netdevice_notअगरier(&bus->netdev_nb);
	qtnf_bus_data_rx_stop(bus);

	क्रम (macid = 0; macid < QTNF_MAX_MAC; macid++)
		qtnf_core_mac_detach(bus, macid);

	अगर (qtnf_fw_is_up(bus))
		qtnf_cmd_send_deinit_fw(bus);

	bus->fw_state = QTNF_FW_STATE_DETACHED;

	अगर (bus->workqueue) अणु
		flush_workqueue(bus->workqueue);
		destroy_workqueue(bus->workqueue);
		bus->workqueue = शून्य;
	पूर्ण

	अगर (bus->hprio_workqueue) अणु
		flush_workqueue(bus->hprio_workqueue);
		destroy_workqueue(bus->hprio_workqueue);
		bus->hprio_workqueue = शून्य;
	पूर्ण

	qtnf_trans_मुक्त(bus);
पूर्ण
EXPORT_SYMBOL_GPL(qtnf_core_detach);

अटल अंतरभूत पूर्णांक qtnf_is_frame_meta_magic_valid(काष्ठा qtnf_frame_meta_info *m)
अणु
	वापस m->magic_s == HBM_FRAME_META_MAGIC_PATTERN_S &&
		m->magic_e == HBM_FRAME_META_MAGIC_PATTERN_E;
पूर्ण

काष्ठा net_device *qtnf_classअगरy_skb(काष्ठा qtnf_bus *bus, काष्ठा sk_buff *skb)
अणु
	काष्ठा qtnf_frame_meta_info *meta;
	काष्ठा net_device *ndev = शून्य;
	काष्ठा qtnf_wmac *mac;
	काष्ठा qtnf_vअगर *vअगर;

	अगर (unlikely(bus->fw_state != QTNF_FW_STATE_RUNNING))
		वापस शून्य;

	meta = (काष्ठा qtnf_frame_meta_info *)
		(skb_tail_poपूर्णांकer(skb) - माप(*meta));

	अगर (unlikely(!qtnf_is_frame_meta_magic_valid(meta))) अणु
		pr_err_ratelimited("invalid magic 0x%x:0x%x\n",
				   meta->magic_s, meta->magic_e);
		जाओ out;
	पूर्ण

	अगर (unlikely(meta->macid >= QTNF_MAX_MAC)) अणु
		pr_err_ratelimited("invalid mac(%u)\n", meta->macid);
		जाओ out;
	पूर्ण

	अगर (unlikely(meta->अगरidx >= QTNF_MAX_INTF)) अणु
		pr_err_ratelimited("invalid vif(%u)\n", meta->अगरidx);
		जाओ out;
	पूर्ण

	mac = bus->mac[meta->macid];

	अगर (unlikely(!mac)) अणु
		pr_err_ratelimited("mac(%d) does not exist\n", meta->macid);
		जाओ out;
	पूर्ण

	vअगर = &mac->अगरlist[meta->अगरidx];

	अगर (unlikely(vअगर->wdev.अगरtype == NL80211_IFTYPE_UNSPECIFIED)) अणु
		pr_err_ratelimited("vif(%u) does not exists\n", meta->अगरidx);
		जाओ out;
	पूर्ण

	ndev = vअगर->netdev;

	अगर (unlikely(!ndev)) अणु
		pr_err_ratelimited("netdev for wlan%u.%u does not exists\n",
				   meta->macid, meta->अगरidx);
		जाओ out;
	पूर्ण

	__skb_trim(skb, skb->len - माप(*meta));
	/* Firmware always handles packets that require flooding */
	qtnfmac_चयन_mark_skb_flooded(skb);

out:
	वापस ndev;
पूर्ण
EXPORT_SYMBOL_GPL(qtnf_classअगरy_skb);

व्योम qtnf_wake_all_queues(काष्ठा net_device *ndev)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(ndev);
	काष्ठा qtnf_wmac *mac;
	काष्ठा qtnf_bus *bus;
	पूर्णांक macid;
	पूर्णांक i;

	अगर (unlikely(!vअगर || !vअगर->mac || !vअगर->mac->bus))
		वापस;

	bus = vअगर->mac->bus;

	क्रम (macid = 0; macid < QTNF_MAX_MAC; macid++) अणु
		अगर (!(bus->hw_info.mac_biपंचांगap & BIT(macid)))
			जारी;

		mac = bus->mac[macid];
		क्रम (i = 0; i < QTNF_MAX_INTF; i++) अणु
			vअगर = &mac->अगरlist[i];
			अगर (vअगर->netdev && netअगर_queue_stopped(vअगर->netdev))
				netअगर_tx_wake_all_queues(vअगर->netdev);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(qtnf_wake_all_queues);

काष्ठा dentry *qtnf_get_debugfs_dir(व्योम)
अणु
	वापस qtnf_debugfs_dir;
पूर्ण
EXPORT_SYMBOL_GPL(qtnf_get_debugfs_dir);

अटल पूर्णांक __init qtnf_core_रेजिस्टर(व्योम)
अणु
	qtnf_debugfs_dir = debugfs_create_dir(KBUILD_MODNAME, शून्य);

	अगर (IS_ERR(qtnf_debugfs_dir))
		qtnf_debugfs_dir = शून्य;

	वापस 0;
पूर्ण

अटल व्योम __निकास qtnf_core_निकास(व्योम)
अणु
	debugfs_हटाओ(qtnf_debugfs_dir);
पूर्ण

module_init(qtnf_core_रेजिस्टर);
module_निकास(qtnf_core_निकास);

MODULE_AUTHOR("Quantenna Communications");
MODULE_DESCRIPTION("Quantenna 802.11 wireless LAN FullMAC driver.");
MODULE_LICENSE("GPL");
