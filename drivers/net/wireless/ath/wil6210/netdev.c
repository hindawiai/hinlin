<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश "wil6210.h"
#समावेश "txrx.h"

bool wil_has_other_active_अगरaces(काष्ठा wil6210_priv *wil,
				 काष्ठा net_device *ndev, bool up, bool ok)
अणु
	पूर्णांक i;
	काष्ठा wil6210_vअगर *vअगर;
	काष्ठा net_device *ndev_i;

	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		vअगर = wil->vअगरs[i];
		अगर (vअगर) अणु
			ndev_i = vअगर_to_ndev(vअगर);
			अगर (ndev_i != ndev)
				अगर ((up && (ndev_i->flags & IFF_UP)) ||
				    (ok && netअगर_carrier_ok(ndev_i)))
					वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

bool wil_has_active_अगरaces(काष्ठा wil6210_priv *wil, bool up, bool ok)
अणु
	/* use शून्य ndev argument to check all पूर्णांकerfaces */
	वापस wil_has_other_active_अगरaces(wil, शून्य, up, ok);
पूर्ण

अटल पूर्णांक wil_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा wil6210_priv *wil = ndev_to_wil(ndev);
	पूर्णांक rc = 0;

	wil_dbg_misc(wil, "open\n");

	अगर (debug_fw ||
	    test_bit(WMI_FW_CAPABILITY_WMI_ONLY, wil->fw_capabilities)) अणु
		wil_err(wil, "while in debug_fw or wmi_only mode\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!wil_has_other_active_अगरaces(wil, ndev, true, false)) अणु
		wil_dbg_misc(wil, "open, first iface\n");
		rc = wil_pm_runसमय_get(wil);
		अगर (rc < 0)
			वापस rc;

		rc = wil_up(wil);
		अगर (rc)
			wil_pm_runसमय_put(wil);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक wil_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा wil6210_priv *wil = ndev_to_wil(ndev);
	पूर्णांक rc = 0;

	wil_dbg_misc(wil, "stop\n");

	अगर (!wil_has_other_active_अगरaces(wil, ndev, true, false)) अणु
		wil_dbg_misc(wil, "stop, last iface\n");
		rc = wil_करोwn(wil);
		अगर (!rc)
			wil_pm_runसमय_put(wil);
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा net_device_ops wil_netdev_ops = अणु
	.nकरो_खोलो		= wil_खोलो,
	.nकरो_stop		= wil_stop,
	.nकरो_start_xmit		= wil_start_xmit,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक wil6210_netdev_poll_rx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा wil6210_priv *wil = container_of(napi, काष्ठा wil6210_priv,
						napi_rx);
	पूर्णांक quota = budget;
	पूर्णांक करोne;

	wil_rx_handle(wil, &quota);
	करोne = budget - quota;

	अगर (करोne < budget) अणु
		napi_complete_करोne(napi, करोne);
		wil6210_unmask_irq_rx(wil);
		wil_dbg_txrx(wil, "NAPI RX complete\n");
	पूर्ण

	wil_dbg_txrx(wil, "NAPI RX poll(%d) done %d\n", budget, करोne);

	वापस करोne;
पूर्ण

अटल पूर्णांक wil6210_netdev_poll_rx_edma(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा wil6210_priv *wil = container_of(napi, काष्ठा wil6210_priv,
						napi_rx);
	पूर्णांक quota = budget;
	पूर्णांक करोne;

	wil_rx_handle_edma(wil, &quota);
	करोne = budget - quota;

	अगर (करोne < budget) अणु
		napi_complete_करोne(napi, करोne);
		wil6210_unmask_irq_rx_edma(wil);
		wil_dbg_txrx(wil, "NAPI RX complete\n");
	पूर्ण

	wil_dbg_txrx(wil, "NAPI RX poll(%d) done %d\n", budget, करोne);

	वापस करोne;
पूर्ण

अटल पूर्णांक wil6210_netdev_poll_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा wil6210_priv *wil = container_of(napi, काष्ठा wil6210_priv,
						napi_tx);
	पूर्णांक tx_करोne = 0;
	uपूर्णांक i;

	/* always process ALL Tx complete, regardless budget - it is fast */
	क्रम (i = 0; i < WIL6210_MAX_TX_RINGS; i++) अणु
		काष्ठा wil_ring *ring = &wil->ring_tx[i];
		काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[i];
		काष्ठा wil6210_vअगर *vअगर;

		अगर (!ring->va || !txdata->enabled ||
		    txdata->mid >= GET_MAX_VIFS(wil))
			जारी;

		vअगर = wil->vअगरs[txdata->mid];
		अगर (unlikely(!vअगर)) अणु
			wil_dbg_txrx(wil, "Invalid MID %d\n", txdata->mid);
			जारी;
		पूर्ण

		tx_करोne += wil_tx_complete(vअगर, i);
	पूर्ण

	अगर (tx_करोne < budget) अणु
		napi_complete(napi);
		wil6210_unmask_irq_tx(wil);
		wil_dbg_txrx(wil, "NAPI TX complete\n");
	पूर्ण

	wil_dbg_txrx(wil, "NAPI TX poll(%d) done %d\n", budget, tx_करोne);

	वापस min(tx_करोne, budget);
पूर्ण

अटल पूर्णांक wil6210_netdev_poll_tx_edma(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा wil6210_priv *wil = container_of(napi, काष्ठा wil6210_priv,
						napi_tx);
	पूर्णांक tx_करोne;
	/* There is only one status TX ring */
	काष्ठा wil_status_ring *sring = &wil->srings[wil->tx_sring_idx];

	अगर (!sring->va)
		वापस 0;

	tx_करोne = wil_tx_sring_handler(wil, sring);

	अगर (tx_करोne < budget) अणु
		napi_complete(napi);
		wil6210_unmask_irq_tx_edma(wil);
		wil_dbg_txrx(wil, "NAPI TX complete\n");
	पूर्ण

	wil_dbg_txrx(wil, "NAPI TX poll(%d) done %d\n", budget, tx_करोne);

	वापस min(tx_करोne, budget);
पूर्ण

अटल व्योम wil_dev_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);
	dev->max_mtu = mtu_max;
	dev->tx_queue_len = WIL_TX_Q_LEN_DEFAULT;
पूर्ण

अटल व्योम wil_vअगर_deinit(काष्ठा wil6210_vअगर *vअगर)
अणु
	del_समयr_sync(&vअगर->scan_समयr);
	del_समयr_sync(&vअगर->p2p.discovery_समयr);
	cancel_work_sync(&vअगर->disconnect_worker);
	cancel_work_sync(&vअगर->p2p.discovery_expired_work);
	cancel_work_sync(&vअगर->p2p.delayed_listen_work);
	wil_probe_client_flush(vअगर);
	cancel_work_sync(&vअगर->probe_client_worker);
	cancel_work_sync(&vअगर->enable_tx_key_worker);
पूर्ण

व्योम wil_vअगर_मुक्त(काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा net_device *ndev = vअगर_to_ndev(vअगर);

	wil_vअगर_deinit(vअगर);
	मुक्त_netdev(ndev);
पूर्ण

अटल व्योम wil_ndev_deकाष्ठाor(काष्ठा net_device *ndev)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);

	wil_vअगर_deinit(vअगर);
पूर्ण

अटल व्योम wil_connect_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा wil6210_vअगर *vअगर = from_समयr(vअगर, t, connect_समयr);
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	bool q;

	wil_err(wil, "Connect timeout detected, disconnect station\n");

	/* reschedule to thपढ़ो context - disconnect won't
	 * run from atomic context.
	 * queue on wmi_wq to prevent race with connect event.
	 */
	q = queue_work(wil->wmi_wq, &vअगर->disconnect_worker);
	wil_dbg_wmi(wil, "queue_work of disconnect_worker -> %d\n", q);
पूर्ण

अटल व्योम wil_scan_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा wil6210_vअगर *vअगर = from_समयr(vअगर, t, scan_समयr);
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);

	clear_bit(wil_status_fwपढ़ोy, wil->status);
	wil_err(wil, "Scan timeout detected, start fw error recovery\n");
	wil_fw_error_recovery(wil);
पूर्ण

अटल व्योम wil_p2p_discovery_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा wil6210_vअगर *vअगर = from_समयr(vअगर, t, p2p.discovery_समयr);
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);

	wil_dbg_misc(wil, "p2p_discovery_timer_fn\n");

	schedule_work(&vअगर->p2p.discovery_expired_work);
पूर्ण

अटल व्योम wil_vअगर_init(काष्ठा wil6210_vअगर *vअगर)
अणु
	vअगर->bcast_ring = -1;

	mutex_init(&vअगर->probe_client_mutex);

	समयr_setup(&vअगर->connect_समयr, wil_connect_समयr_fn, 0);
	समयr_setup(&vअगर->scan_समयr, wil_scan_समयr_fn, 0);
	समयr_setup(&vअगर->p2p.discovery_समयr, wil_p2p_discovery_समयr_fn, 0);

	INIT_WORK(&vअगर->probe_client_worker, wil_probe_client_worker);
	INIT_WORK(&vअगर->disconnect_worker, wil_disconnect_worker);
	INIT_WORK(&vअगर->p2p.discovery_expired_work, wil_p2p_listen_expired);
	INIT_WORK(&vअगर->p2p.delayed_listen_work, wil_p2p_delayed_listen_work);
	INIT_WORK(&vअगर->enable_tx_key_worker, wil_enable_tx_key_worker);

	INIT_LIST_HEAD(&vअगर->probe_client_pending);

	vअगर->net_queue_stopped = 1;
पूर्ण

अटल u8 wil_vअगर_find_मुक्त_mid(काष्ठा wil6210_priv *wil)
अणु
	u8 i;

	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		अगर (!wil->vअगरs[i])
			वापस i;
	पूर्ण

	वापस U8_MAX;
पूर्ण

काष्ठा wil6210_vअगर *
wil_vअगर_alloc(काष्ठा wil6210_priv *wil, स्थिर अक्षर *name,
	      अचिन्हित अक्षर name_assign_type, क्रमागत nl80211_अगरtype अगरtype)
अणु
	काष्ठा net_device *ndev;
	काष्ठा wireless_dev *wdev;
	काष्ठा wil6210_vअगर *vअगर;
	u8 mid;

	mid = wil_vअगर_find_मुक्त_mid(wil);
	अगर (mid == U8_MAX) अणु
		wil_err(wil, "no available virtual interface\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	ndev = alloc_netdev(माप(*vअगर), name, name_assign_type,
			    wil_dev_setup);
	अगर (!ndev) अणु
		dev_err(wil_to_dev(wil), "alloc_netdev failed\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	अगर (mid == 0) अणु
		wil->मुख्य_ndev = ndev;
	पूर्ण अन्यथा अणु
		ndev->priv_deकाष्ठाor = wil_ndev_deकाष्ठाor;
		ndev->needs_मुक्त_netdev = true;
	पूर्ण

	vअगर = ndev_to_vअगर(ndev);
	vअगर->ndev = ndev;
	vअगर->wil = wil;
	vअगर->mid = mid;
	wil_vअगर_init(vअगर);

	wdev = &vअगर->wdev;
	wdev->wiphy = wil->wiphy;
	wdev->अगरtype = अगरtype;

	ndev->netdev_ops = &wil_netdev_ops;
	wil_set_ethtoolops(ndev);
	ndev->ieee80211_ptr = wdev;
	ndev->hw_features = NETIF_F_HW_CSUM | NETIF_F_RXCSUM |
			    NETIF_F_SG | NETIF_F_GRO |
			    NETIF_F_TSO | NETIF_F_TSO6;

	ndev->features |= ndev->hw_features;
	SET_NETDEV_DEV(ndev, wiphy_dev(wdev->wiphy));
	wdev->netdev = ndev;
	वापस vअगर;
पूर्ण

व्योम *wil_अगर_alloc(काष्ठा device *dev)
अणु
	काष्ठा wil6210_priv *wil;
	काष्ठा wil6210_vअगर *vअगर;
	पूर्णांक rc = 0;

	wil = wil_cfg80211_init(dev);
	अगर (IS_ERR(wil)) अणु
		dev_err(dev, "wil_cfg80211_init failed\n");
		वापस wil;
	पूर्ण

	rc = wil_priv_init(wil);
	अगर (rc) अणु
		dev_err(dev, "wil_priv_init failed\n");
		जाओ out_cfg;
	पूर्ण

	wil_dbg_misc(wil, "if_alloc\n");

	vअगर = wil_vअगर_alloc(wil, "wlan%d", NET_NAME_UNKNOWN,
			    NL80211_IFTYPE_STATION);
	अगर (IS_ERR(vअगर)) अणु
		dev_err(dev, "wil_vif_alloc failed\n");
		rc = -ENOMEM;
		जाओ out_priv;
	पूर्ण

	wil->radio_wdev = vअगर_to_wdev(vअगर);

	वापस wil;

out_priv:
	wil_priv_deinit(wil);

out_cfg:
	wil_cfg80211_deinit(wil);

	वापस ERR_PTR(rc);
पूर्ण

व्योम wil_अगर_मुक्त(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा net_device *ndev = wil->मुख्य_ndev;

	wil_dbg_misc(wil, "if_free\n");

	अगर (!ndev)
		वापस;

	wil_priv_deinit(wil);

	wil->मुख्य_ndev = शून्य;
	wil_ndev_deकाष्ठाor(ndev);
	मुक्त_netdev(ndev);

	wil_cfg80211_deinit(wil);
पूर्ण

पूर्णांक wil_vअगर_add(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा net_device *ndev = vअगर_to_ndev(vअगर);
	काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);
	bool any_active = wil_has_active_अगरaces(wil, true, false);
	पूर्णांक rc;

	ASSERT_RTNL();

	अगर (wil->vअगरs[vअगर->mid]) अणु
		dev_err(&ndev->dev, "VIF with mid %d already in use\n",
			vअगर->mid);
		वापस -EEXIST;
	पूर्ण
	अगर (any_active && vअगर->mid != 0) अणु
		rc = wmi_port_allocate(wil, vअगर->mid, ndev->dev_addr,
				       wdev->अगरtype);
		अगर (rc)
			वापस rc;
	पूर्ण
	rc = cfg80211_रेजिस्टर_netdevice(ndev);
	अगर (rc < 0) अणु
		dev_err(&ndev->dev, "Failed to register netdev: %d\n", rc);
		अगर (any_active && vअगर->mid != 0)
			wmi_port_delete(wil, vअगर->mid);
		वापस rc;
	पूर्ण

	wil->vअगरs[vअगर->mid] = vअगर;
	वापस 0;
पूर्ण

पूर्णांक wil_अगर_add(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wiphy *wiphy = wil->wiphy;
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	पूर्णांक rc;

	wil_dbg_misc(wil, "entered");

	strlcpy(wiphy->fw_version, wil->fw_version, माप(wiphy->fw_version));

	rc = wiphy_रेजिस्टर(wiphy);
	अगर (rc < 0) अणु
		wil_err(wil, "failed to register wiphy, err %d\n", rc);
		वापस rc;
	पूर्ण

	init_dummy_netdev(&wil->napi_ndev);
	अगर (wil->use_enhanced_dma_hw) अणु
		netअगर_napi_add(&wil->napi_ndev, &wil->napi_rx,
			       wil6210_netdev_poll_rx_edma,
			       WIL6210_NAPI_BUDGET);
		netअगर_tx_napi_add(&wil->napi_ndev,
				  &wil->napi_tx, wil6210_netdev_poll_tx_edma,
				  WIL6210_NAPI_BUDGET);
	पूर्ण अन्यथा अणु
		netअगर_napi_add(&wil->napi_ndev, &wil->napi_rx,
			       wil6210_netdev_poll_rx,
			       WIL6210_NAPI_BUDGET);
		netअगर_tx_napi_add(&wil->napi_ndev,
				  &wil->napi_tx, wil6210_netdev_poll_tx,
				  WIL6210_NAPI_BUDGET);
	पूर्ण

	wil_update_net_queues_bh(wil, vअगर, शून्य, true);

	rtnl_lock();
	wiphy_lock(wiphy);
	rc = wil_vअगर_add(wil, vअगर);
	wiphy_unlock(wiphy);
	rtnl_unlock();
	अगर (rc < 0)
		जाओ out_wiphy;

	वापस 0;

out_wiphy:
	wiphy_unरेजिस्टर(wiphy);
	वापस rc;
पूर्ण

व्योम wil_vअगर_हटाओ(काष्ठा wil6210_priv *wil, u8 mid)
अणु
	काष्ठा wil6210_vअगर *vअगर;
	काष्ठा net_device *ndev;
	bool any_active = wil_has_active_अगरaces(wil, true, false);

	ASSERT_RTNL();
	अगर (mid >= GET_MAX_VIFS(wil)) अणु
		wil_err(wil, "invalid MID: %d\n", mid);
		वापस;
	पूर्ण

	vअगर = wil->vअगरs[mid];
	अगर (!vअगर) अणु
		wil_err(wil, "MID %d not registered\n", mid);
		वापस;
	पूर्ण

	mutex_lock(&wil->mutex);
	wil6210_disconnect(vअगर, शून्य, WLAN_REASON_DEAUTH_LEAVING);
	mutex_unlock(&wil->mutex);

	ndev = vअगर_to_ndev(vअगर);
	/* during unरेजिस्टर_netdevice cfg80211_leave may perक्रमm operations
	 * such as stop AP, disconnect, so we only clear the VIF afterwards
	 */
	cfg80211_unरेजिस्टर_netdevice(ndev);

	अगर (any_active && vअगर->mid != 0)
		wmi_port_delete(wil, vअगर->mid);

	/* make sure no one is accessing the VIF beक्रमe removing */
	mutex_lock(&wil->vअगर_mutex);
	wil->vअगरs[mid] = शून्य;
	/* ensure NAPI code will see the शून्य VIF */
	wmb();
	अगर (test_bit(wil_status_napi_en, wil->status)) अणु
		napi_synchronize(&wil->napi_rx);
		napi_synchronize(&wil->napi_tx);
	पूर्ण
	mutex_unlock(&wil->vअगर_mutex);

	flush_work(&wil->wmi_event_worker);
	del_समयr_sync(&vअगर->connect_समयr);
	cancel_work_sync(&vअगर->disconnect_worker);
	wil_probe_client_flush(vअगर);
	cancel_work_sync(&vअगर->probe_client_worker);
	cancel_work_sync(&vअगर->enable_tx_key_worker);
	/* क्रम VIFs, ndev will be मुक्तd by deकाष्ठाor after RTNL is unlocked.
	 * the मुख्य पूर्णांकerface will be मुक्तd in wil_अगर_मुक्त, we need to keep it
	 * a bit दीर्घer so logging macros will work.
	 */
पूर्ण

व्योम wil_अगर_हटाओ(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	काष्ठा wireless_dev *wdev = ndev->ieee80211_ptr;
	काष्ठा wiphy *wiphy = wdev->wiphy;

	wil_dbg_misc(wil, "if_remove\n");

	rtnl_lock();
	wiphy_lock(wiphy);
	wil_vअगर_हटाओ(wil, 0);
	wiphy_unlock(wiphy);
	rtnl_unlock();

	netअगर_napi_del(&wil->napi_tx);
	netअगर_napi_del(&wil->napi_rx);

	wiphy_unरेजिस्टर(wiphy);
पूर्ण
