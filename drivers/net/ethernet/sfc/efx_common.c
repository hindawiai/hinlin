<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2018 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#समावेश "net_driver.h"
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <net/gre.h>
#समावेश "efx_common.h"
#समावेश "efx_channels.h"
#समावेश "efx.h"
#समावेश "mcdi.h"
#समावेश "selftest.h"
#समावेश "rx_common.h"
#समावेश "tx_common.h"
#समावेश "nic.h"
#समावेश "mcdi_port_common.h"
#समावेश "io.h"
#समावेश "mcdi_pcol.h"

अटल अचिन्हित पूर्णांक debug = (NETIF_MSG_DRV | NETIF_MSG_PROBE |
			     NETIF_MSG_LINK | NETIF_MSG_IFDOWN |
			     NETIF_MSG_IFUP | NETIF_MSG_RX_ERR |
			     NETIF_MSG_TX_ERR | NETIF_MSG_HW);
module_param(debug, uपूर्णांक, 0);
MODULE_PARM_DESC(debug, "Bitmapped debugging message enable value");

/* This is the समय (in jअगरfies) between invocations of the hardware
 * monitor.
 * On Falcon-based NICs, this will:
 * - Check the on-board hardware monitor;
 * - Poll the link state and reconfigure the hardware as necessary.
 * On Siena-based NICs क्रम घातer प्रणालीs with EEH support, this will give EEH a
 * chance to start.
 */
अटल अचिन्हित पूर्णांक efx_monitor_पूर्णांकerval = 1 * HZ;

/* How often and how many बार to poll क्रम a reset जबतक रुकोing क्रम a
 * BIST that another function started to complete.
 */
#घोषणा BIST_WAIT_DELAY_MS	100
#घोषणा BIST_WAIT_DELAY_COUNT	100

/* Default stats update समय */
#घोषणा STATS_PERIOD_MS_DEFAULT 1000

स्थिर अचिन्हित पूर्णांक efx_reset_type_max = RESET_TYPE_MAX;
स्थिर अक्षर *स्थिर efx_reset_type_names[] = अणु
	[RESET_TYPE_INVISIBLE]          = "INVISIBLE",
	[RESET_TYPE_ALL]                = "ALL",
	[RESET_TYPE_RECOVER_OR_ALL]     = "RECOVER_OR_ALL",
	[RESET_TYPE_WORLD]              = "WORLD",
	[RESET_TYPE_RECOVER_OR_DISABLE] = "RECOVER_OR_DISABLE",
	[RESET_TYPE_DATAPATH]           = "DATAPATH",
	[RESET_TYPE_MC_BIST]		= "MC_BIST",
	[RESET_TYPE_DISABLE]            = "DISABLE",
	[RESET_TYPE_TX_WATCHDOG]        = "TX_WATCHDOG",
	[RESET_TYPE_INT_ERROR]          = "INT_ERROR",
	[RESET_TYPE_DMA_ERROR]          = "DMA_ERROR",
	[RESET_TYPE_TX_SKIP]            = "TX_SKIP",
	[RESET_TYPE_MC_FAILURE]         = "MC_FAILURE",
	[RESET_TYPE_MCDI_TIMEOUT]	= "MCDI_TIMEOUT (FLR)",
पूर्ण;

#घोषणा RESET_TYPE(type) \
	STRING_TABLE_LOOKUP(type, efx_reset_type)

/* Loopback mode names (see LOOPBACK_MODE()) */
स्थिर अचिन्हित पूर्णांक efx_loopback_mode_max = LOOPBACK_MAX;
स्थिर अक्षर *स्थिर efx_loopback_mode_names[] = अणु
	[LOOPBACK_NONE]		= "NONE",
	[LOOPBACK_DATA]		= "DATAPATH",
	[LOOPBACK_GMAC]		= "GMAC",
	[LOOPBACK_XGMII]	= "XGMII",
	[LOOPBACK_XGXS]		= "XGXS",
	[LOOPBACK_XAUI]		= "XAUI",
	[LOOPBACK_GMII]		= "GMII",
	[LOOPBACK_SGMII]	= "SGMII",
	[LOOPBACK_XGBR]		= "XGBR",
	[LOOPBACK_XFI]		= "XFI",
	[LOOPBACK_XAUI_FAR]	= "XAUI_FAR",
	[LOOPBACK_GMII_FAR]	= "GMII_FAR",
	[LOOPBACK_SGMII_FAR]	= "SGMII_FAR",
	[LOOPBACK_XFI_FAR]	= "XFI_FAR",
	[LOOPBACK_GPHY]		= "GPHY",
	[LOOPBACK_PHYXS]	= "PHYXS",
	[LOOPBACK_PCS]		= "PCS",
	[LOOPBACK_PMAPMD]	= "PMA/PMD",
	[LOOPBACK_XPORT]	= "XPORT",
	[LOOPBACK_XGMII_WS]	= "XGMII_WS",
	[LOOPBACK_XAUI_WS]	= "XAUI_WS",
	[LOOPBACK_XAUI_WS_FAR]  = "XAUI_WS_FAR",
	[LOOPBACK_XAUI_WS_NEAR] = "XAUI_WS_NEAR",
	[LOOPBACK_GMII_WS]	= "GMII_WS",
	[LOOPBACK_XFI_WS]	= "XFI_WS",
	[LOOPBACK_XFI_WS_FAR]	= "XFI_WS_FAR",
	[LOOPBACK_PHYXS_WS]	= "PHYXS_WS",
पूर्ण;

/* Reset workqueue. If any NIC has a hardware failure then a reset will be
 * queued onto this work queue. This is not a per-nic work queue, because
 * efx_reset_work() acquires the rtnl lock, so resets are naturally serialised.
 */
अटल काष्ठा workqueue_काष्ठा *reset_workqueue;

पूर्णांक efx_create_reset_workqueue(व्योम)
अणु
	reset_workqueue = create_singlethपढ़ो_workqueue("sfc_reset");
	अगर (!reset_workqueue) अणु
		prपूर्णांकk(KERN_ERR "Failed to create reset workqueue\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम efx_queue_reset_work(काष्ठा efx_nic *efx)
अणु
	queue_work(reset_workqueue, &efx->reset_work);
पूर्ण

व्योम efx_flush_reset_workqueue(काष्ठा efx_nic *efx)
अणु
	cancel_work_sync(&efx->reset_work);
पूर्ण

व्योम efx_destroy_reset_workqueue(व्योम)
अणु
	अगर (reset_workqueue) अणु
		destroy_workqueue(reset_workqueue);
		reset_workqueue = शून्य;
	पूर्ण
पूर्ण

/* We assume that efx->type->reconfigure_mac will always try to sync RX
 * filters and thereक्रमe needs to पढ़ो-lock the filter table against मुक्तing
 */
व्योम efx_mac_reconfigure(काष्ठा efx_nic *efx, bool mtu_only)
अणु
	अगर (efx->type->reconfigure_mac) अणु
		करोwn_पढ़ो(&efx->filter_sem);
		efx->type->reconfigure_mac(efx, mtu_only);
		up_पढ़ो(&efx->filter_sem);
	पूर्ण
पूर्ण

/* Asynchronous work item क्रम changing MAC promiscuity and multicast
 * hash.  Aव्योम a drain/rx_ingress enable by reconfiguring the current
 * MAC directly.
 */
अटल व्योम efx_mac_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा efx_nic *efx = container_of(data, काष्ठा efx_nic, mac_work);

	mutex_lock(&efx->mac_lock);
	अगर (efx->port_enabled)
		efx_mac_reconfigure(efx, false);
	mutex_unlock(&efx->mac_lock);
पूर्ण

पूर्णांक efx_set_mac_address(काष्ठा net_device *net_dev, व्योम *data)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	काष्ठा sockaddr *addr = data;
	u8 *new_addr = addr->sa_data;
	u8 old_addr[6];
	पूर्णांक rc;

	अगर (!is_valid_ether_addr(new_addr)) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "invalid ethernet MAC address requested: %pM\n",
			  new_addr);
		वापस -EADDRNOTAVAIL;
	पूर्ण

	/* save old address */
	ether_addr_copy(old_addr, net_dev->dev_addr);
	ether_addr_copy(net_dev->dev_addr, new_addr);
	अगर (efx->type->set_mac_address) अणु
		rc = efx->type->set_mac_address(efx);
		अगर (rc) अणु
			ether_addr_copy(net_dev->dev_addr, old_addr);
			वापस rc;
		पूर्ण
	पूर्ण

	/* Reconfigure the MAC */
	mutex_lock(&efx->mac_lock);
	efx_mac_reconfigure(efx, false);
	mutex_unlock(&efx->mac_lock);

	वापस 0;
पूर्ण

/* Context: netअगर_addr_lock held, BHs disabled. */
व्योम efx_set_rx_mode(काष्ठा net_device *net_dev)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	अगर (efx->port_enabled)
		queue_work(efx->workqueue, &efx->mac_work);
	/* Otherwise efx_start_port() will करो this */
पूर्ण

पूर्णांक efx_set_features(काष्ठा net_device *net_dev, netdev_features_t data)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	पूर्णांक rc;

	/* If disabling RX n-tuple filtering, clear existing filters */
	अगर (net_dev->features & ~data & NETIF_F_NTUPLE) अणु
		rc = efx->type->filter_clear_rx(efx, EFX_FILTER_PRI_MANUAL);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* If Rx VLAN filter is changed, update filters via mac_reconfigure.
	 * If rx-fcs is changed, mac_reconfigure updates that too.
	 */
	अगर ((net_dev->features ^ data) & (NETIF_F_HW_VLAN_CTAG_FILTER |
					  NETIF_F_RXFCS)) अणु
		/* efx_set_rx_mode() will schedule MAC work to update filters
		 * when a new features are finally set in net_dev.
		 */
		efx_set_rx_mode(net_dev);
	पूर्ण

	वापस 0;
पूर्ण

/* This ensures that the kernel is kept inक्रमmed (via
 * netअगर_carrier_on/off) of the link status, and also मुख्यtains the
 * link status's stop on the port's TX queue.
 */
व्योम efx_link_status_changed(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_link_state *link_state = &efx->link_state;

	/* SFC Bug 5356: A net_dev notअगरier is रेजिस्टरed, so we must ensure
	 * that no events are triggered between unरेजिस्टर_netdev() and the
	 * driver unloading. A more general condition is that NETDEV_CHANGE
	 * can only be generated between NETDEV_UP and NETDEV_DOWN
	 */
	अगर (!netअगर_running(efx->net_dev))
		वापस;

	अगर (link_state->up != netअगर_carrier_ok(efx->net_dev)) अणु
		efx->n_link_state_changes++;

		अगर (link_state->up)
			netअगर_carrier_on(efx->net_dev);
		अन्यथा
			netअगर_carrier_off(efx->net_dev);
	पूर्ण

	/* Status message क्रम kernel log */
	अगर (link_state->up)
		netअगर_info(efx, link, efx->net_dev,
			   "link up at %uMbps %s-duplex (MTU %d)\n",
			   link_state->speed, link_state->fd ? "full" : "half",
			   efx->net_dev->mtu);
	अन्यथा
		netअगर_info(efx, link, efx->net_dev, "link down\n");
पूर्ण

अचिन्हित पूर्णांक efx_xdp_max_mtu(काष्ठा efx_nic *efx)
अणु
	/* The maximum MTU that we can fit in a single page, allowing क्रम
	 * framing, overhead and XDP headroom + tailroom.
	 */
	पूर्णांक overhead = EFX_MAX_FRAME_LEN(0) + माप(काष्ठा efx_rx_page_state) +
		       efx->rx_prefix_size + efx->type->rx_buffer_padding +
		       efx->rx_ip_align + EFX_XDP_HEADROOM + EFX_XDP_TAILROOM;

	वापस PAGE_SIZE - overhead;
पूर्ण

/* Context: process, rtnl_lock() held. */
पूर्णांक efx_change_mtu(काष्ठा net_device *net_dev, पूर्णांक new_mtu)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	पूर्णांक rc;

	rc = efx_check_disabled(efx);
	अगर (rc)
		वापस rc;

	अगर (rtnl_dereference(efx->xdp_prog) &&
	    new_mtu > efx_xdp_max_mtu(efx)) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "Requested MTU of %d too big for XDP (max: %d)\n",
			  new_mtu, efx_xdp_max_mtu(efx));
		वापस -EINVAL;
	पूर्ण

	netअगर_dbg(efx, drv, efx->net_dev, "changing MTU to %d\n", new_mtu);

	efx_device_detach_sync(efx);
	efx_stop_all(efx);

	mutex_lock(&efx->mac_lock);
	net_dev->mtu = new_mtu;
	efx_mac_reconfigure(efx, true);
	mutex_unlock(&efx->mac_lock);

	efx_start_all(efx);
	efx_device_attach_अगर_not_resetting(efx);
	वापस 0;
पूर्ण

/**************************************************************************
 *
 * Hardware monitor
 *
 **************************************************************************/

/* Run periodically off the general workqueue */
अटल व्योम efx_monitor(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा efx_nic *efx = container_of(data, काष्ठा efx_nic,
					   monitor_work.work);

	netअगर_vdbg(efx, समयr, efx->net_dev,
		   "hardware monitor executing on CPU %d\n",
		   raw_smp_processor_id());
	BUG_ON(efx->type->monitor == शून्य);

	/* If the mac_lock is alपढ़ोy held then it is likely a port
	 * reconfiguration is alपढ़ोy in place, which will likely करो
	 * most of the work of monitor() anyway.
	 */
	अगर (mutex_trylock(&efx->mac_lock)) अणु
		अगर (efx->port_enabled && efx->type->monitor)
			efx->type->monitor(efx);
		mutex_unlock(&efx->mac_lock);
	पूर्ण

	efx_start_monitor(efx);
पूर्ण

व्योम efx_start_monitor(काष्ठा efx_nic *efx)
अणु
	अगर (efx->type->monitor)
		queue_delayed_work(efx->workqueue, &efx->monitor_work,
				   efx_monitor_पूर्णांकerval);
पूर्ण

/**************************************************************************
 *
 * Event queue processing
 *
 *************************************************************************/

/* Channels are shutकरोwn and reinitialised whilst the NIC is running
 * to propagate configuration changes (mtu, checksum offload), or
 * to clear hardware error conditions
 */
अटल व्योम efx_start_datapath(काष्ठा efx_nic *efx)
अणु
	netdev_features_t old_features = efx->net_dev->features;
	bool old_rx_scatter = efx->rx_scatter;
	माप_प्रकार rx_buf_len;

	/* Calculate the rx buffer allocation parameters required to
	 * support the current MTU, including padding क्रम header
	 * alignment and overruns.
	 */
	efx->rx_dma_len = (efx->rx_prefix_size +
			   EFX_MAX_FRAME_LEN(efx->net_dev->mtu) +
			   efx->type->rx_buffer_padding);
	rx_buf_len = (माप(काष्ठा efx_rx_page_state)   + EFX_XDP_HEADROOM +
		      efx->rx_ip_align + efx->rx_dma_len + EFX_XDP_TAILROOM);

	अगर (rx_buf_len <= PAGE_SIZE) अणु
		efx->rx_scatter = efx->type->always_rx_scatter;
		efx->rx_buffer_order = 0;
	पूर्ण अन्यथा अगर (efx->type->can_rx_scatter) अणु
		BUILD_BUG_ON(EFX_RX_USR_BUF_SIZE % L1_CACHE_BYTES);
		BUILD_BUG_ON(माप(काष्ठा efx_rx_page_state) +
			     2 * ALIGN(NET_IP_ALIGN + EFX_RX_USR_BUF_SIZE,
				       EFX_RX_BUF_ALIGNMENT) >
			     PAGE_SIZE);
		efx->rx_scatter = true;
		efx->rx_dma_len = EFX_RX_USR_BUF_SIZE;
		efx->rx_buffer_order = 0;
	पूर्ण अन्यथा अणु
		efx->rx_scatter = false;
		efx->rx_buffer_order = get_order(rx_buf_len);
	पूर्ण

	efx_rx_config_page_split(efx);
	अगर (efx->rx_buffer_order)
		netअगर_dbg(efx, drv, efx->net_dev,
			  "RX buf len=%u; page order=%u batch=%u\n",
			  efx->rx_dma_len, efx->rx_buffer_order,
			  efx->rx_pages_per_batch);
	अन्यथा
		netअगर_dbg(efx, drv, efx->net_dev,
			  "RX buf len=%u step=%u bpp=%u; page batch=%u\n",
			  efx->rx_dma_len, efx->rx_page_buf_step,
			  efx->rx_bufs_per_page, efx->rx_pages_per_batch);

	/* Restore previously fixed features in hw_features and हटाओ
	 * features which are fixed now
	 */
	efx->net_dev->hw_features |= efx->net_dev->features;
	efx->net_dev->hw_features &= ~efx->fixed_features;
	efx->net_dev->features |= efx->fixed_features;
	अगर (efx->net_dev->features != old_features)
		netdev_features_change(efx->net_dev);

	/* RX filters may also have scatter-enabled flags */
	अगर ((efx->rx_scatter != old_rx_scatter) &&
	    efx->type->filter_update_rx_scatter)
		efx->type->filter_update_rx_scatter(efx);

	/* We must keep at least one descriptor in a TX ring empty.
	 * We could aव्योम this when the queue size करोes not exactly
	 * match the hardware ring size, but it's not that important.
	 * Thereक्रमe we stop the queue when one more skb might fill
	 * the ring completely.  We wake it when half way back to
	 * empty.
	 */
	efx->txq_stop_thresh = efx->txq_entries - efx_tx_max_skb_descs(efx);
	efx->txq_wake_thresh = efx->txq_stop_thresh / 2;

	/* Initialise the channels */
	efx_start_channels(efx);

	efx_ptp_start_datapath(efx);

	अगर (netअगर_device_present(efx->net_dev))
		netअगर_tx_wake_all_queues(efx->net_dev);
पूर्ण

अटल व्योम efx_stop_datapath(काष्ठा efx_nic *efx)
अणु
	EFX_ASSERT_RESET_SERIALISED(efx);
	BUG_ON(efx->port_enabled);

	efx_ptp_stop_datapath(efx);

	efx_stop_channels(efx);
पूर्ण

/**************************************************************************
 *
 * Port handling
 *
 **************************************************************************/

/* Equivalent to efx_link_set_advertising with all-zeroes, except करोes not
 * क्रमce the Autoneg bit on.
 */
व्योम efx_link_clear_advertising(काष्ठा efx_nic *efx)
अणु
	biपंचांगap_zero(efx->link_advertising, __ETHTOOL_LINK_MODE_MASK_NBITS);
	efx->wanted_fc &= ~(EFX_FC_TX | EFX_FC_RX);
पूर्ण

व्योम efx_link_set_wanted_fc(काष्ठा efx_nic *efx, u8 wanted_fc)
अणु
	efx->wanted_fc = wanted_fc;
	अगर (efx->link_advertising[0]) अणु
		अगर (wanted_fc & EFX_FC_RX)
			efx->link_advertising[0] |= (ADVERTISED_Pause |
						     ADVERTISED_Asym_Pause);
		अन्यथा
			efx->link_advertising[0] &= ~(ADVERTISED_Pause |
						      ADVERTISED_Asym_Pause);
		अगर (wanted_fc & EFX_FC_TX)
			efx->link_advertising[0] ^= ADVERTISED_Asym_Pause;
	पूर्ण
पूर्ण

अटल व्योम efx_start_port(काष्ठा efx_nic *efx)
अणु
	netअगर_dbg(efx, अगरup, efx->net_dev, "start port\n");
	BUG_ON(efx->port_enabled);

	mutex_lock(&efx->mac_lock);
	efx->port_enabled = true;

	/* Ensure MAC ingress/egress is enabled */
	efx_mac_reconfigure(efx, false);

	mutex_unlock(&efx->mac_lock);
पूर्ण

/* Cancel work क्रम MAC reconfiguration, periodic hardware monitoring
 * and the async self-test, रुको क्रम them to finish and prevent them
 * being scheduled again.  This करोesn't cover online resets, which
 * should only be cancelled when removing the device.
 */
अटल व्योम efx_stop_port(काष्ठा efx_nic *efx)
अणु
	netअगर_dbg(efx, अगरकरोwn, efx->net_dev, "stop port\n");

	EFX_ASSERT_RESET_SERIALISED(efx);

	mutex_lock(&efx->mac_lock);
	efx->port_enabled = false;
	mutex_unlock(&efx->mac_lock);

	/* Serialise against efx_set_multicast_list() */
	netअगर_addr_lock_bh(efx->net_dev);
	netअगर_addr_unlock_bh(efx->net_dev);

	cancel_delayed_work_sync(&efx->monitor_work);
	efx_selftest_async_cancel(efx);
	cancel_work_sync(&efx->mac_work);
पूर्ण

/* If the पूर्णांकerface is supposed to be running but is not, start
 * the hardware and software data path, regular activity क्रम the port
 * (MAC statistics, link polling, etc.) and schedule the port to be
 * reconfigured.  Interrupts must alपढ़ोy be enabled.  This function
 * is safe to call multiple बार, so दीर्घ as the NIC is not disabled.
 * Requires the RTNL lock.
 */
व्योम efx_start_all(काष्ठा efx_nic *efx)
अणु
	EFX_ASSERT_RESET_SERIALISED(efx);
	BUG_ON(efx->state == STATE_DISABLED);

	/* Check that it is appropriate to restart the पूर्णांकerface. All
	 * of these flags are safe to पढ़ो under just the rtnl lock
	 */
	अगर (efx->port_enabled || !netअगर_running(efx->net_dev) ||
	    efx->reset_pending)
		वापस;

	efx_start_port(efx);
	efx_start_datapath(efx);

	/* Start the hardware monitor अगर there is one */
	efx_start_monitor(efx);

	/* Link state detection is normally event-driven; we have
	 * to poll now because we could have missed a change
	 */
	mutex_lock(&efx->mac_lock);
	अगर (efx_mcdi_phy_poll(efx))
		efx_link_status_changed(efx);
	mutex_unlock(&efx->mac_lock);

	अगर (efx->type->start_stats) अणु
		efx->type->start_stats(efx);
		efx->type->pull_stats(efx);
		spin_lock_bh(&efx->stats_lock);
		efx->type->update_stats(efx, शून्य, शून्य);
		spin_unlock_bh(&efx->stats_lock);
	पूर्ण
पूर्ण

/* Quiesce the hardware and software data path, and regular activity
 * क्रम the port without bringing the link करोwn.  Safe to call multiple
 * बार with the NIC in almost any state, but पूर्णांकerrupts should be
 * enabled.  Requires the RTNL lock.
 */
व्योम efx_stop_all(काष्ठा efx_nic *efx)
अणु
	EFX_ASSERT_RESET_SERIALISED(efx);

	/* port_enabled can be पढ़ो safely under the rtnl lock */
	अगर (!efx->port_enabled)
		वापस;

	अगर (efx->type->update_stats) अणु
		/* update stats beक्रमe we go करोwn so we can accurately count
		 * rx_nodesc_drops
		 */
		efx->type->pull_stats(efx);
		spin_lock_bh(&efx->stats_lock);
		efx->type->update_stats(efx, शून्य, शून्य);
		spin_unlock_bh(&efx->stats_lock);
		efx->type->stop_stats(efx);
	पूर्ण

	efx_stop_port(efx);

	/* Stop the kernel transmit पूर्णांकerface.  This is only valid अगर
	 * the device is stopped or detached; otherwise the watchकरोg
	 * may fire immediately.
	 */
	WARN_ON(netअगर_running(efx->net_dev) &&
		netअगर_device_present(efx->net_dev));
	netअगर_tx_disable(efx->net_dev);

	efx_stop_datapath(efx);
पूर्ण

/* Context: process, dev_base_lock or RTNL held, non-blocking. */
व्योम efx_net_stats(काष्ठा net_device *net_dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	spin_lock_bh(&efx->stats_lock);
	efx_nic_update_stats_atomic(efx, शून्य, stats);
	spin_unlock_bh(&efx->stats_lock);
पूर्ण

/* Push loopback/घातer/transmit disable settings to the PHY, and reconfigure
 * the MAC appropriately. All other PHY configuration changes are pushed
 * through phy_op->set_settings(), and pushed asynchronously to the MAC
 * through efx_monitor().
 *
 * Callers must hold the mac_lock
 */
पूर्णांक __efx_reconfigure_port(काष्ठा efx_nic *efx)
अणु
	क्रमागत efx_phy_mode phy_mode;
	पूर्णांक rc = 0;

	WARN_ON(!mutex_is_locked(&efx->mac_lock));

	/* Disable PHY transmit in mac level loopbacks */
	phy_mode = efx->phy_mode;
	अगर (LOOPBACK_INTERNAL(efx))
		efx->phy_mode |= PHY_MODE_TX_DISABLED;
	अन्यथा
		efx->phy_mode &= ~PHY_MODE_TX_DISABLED;

	अगर (efx->type->reconfigure_port)
		rc = efx->type->reconfigure_port(efx);

	अगर (rc)
		efx->phy_mode = phy_mode;

	वापस rc;
पूर्ण

/* Reinitialise the MAC to pick up new PHY settings, even अगर the port is
 * disabled.
 */
पूर्णांक efx_reconfigure_port(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	EFX_ASSERT_RESET_SERIALISED(efx);

	mutex_lock(&efx->mac_lock);
	rc = __efx_reconfigure_port(efx);
	mutex_unlock(&efx->mac_lock);

	वापस rc;
पूर्ण

/**************************************************************************
 *
 * Device reset and suspend
 *
 **************************************************************************/

अटल व्योम efx_रुको_क्रम_bist_end(काष्ठा efx_nic *efx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BIST_WAIT_DELAY_COUNT; ++i) अणु
		अगर (efx_mcdi_poll_reboot(efx))
			जाओ out;
		msleep(BIST_WAIT_DELAY_MS);
	पूर्ण

	netअगर_err(efx, drv, efx->net_dev, "Warning: No MC reboot after BIST mode\n");
out:
	/* Either way unset the BIST flag. If we found no reboot we probably
	 * won't recover, but we should try.
	 */
	efx->mc_bist_क्रम_other_fn = false;
पूर्ण

/* Try recovery mechanisms.
 * For now only EEH is supported.
 * Returns 0 अगर the recovery mechanisms are unsuccessful.
 * Returns a non-zero value otherwise.
 */
पूर्णांक efx_try_recovery(काष्ठा efx_nic *efx)
अणु
#अगर_घोषित CONFIG_EEH
	/* A PCI error can occur and not be seen by EEH because nothing
	 * happens on the PCI bus. In this हाल the driver may fail and
	 * schedule a 'recover or reset', leading to this recovery handler.
	 * Manually call the eeh failure check function.
	 */
	काष्ठा eeh_dev *eehdev = pci_dev_to_eeh_dev(efx->pci_dev);
	अगर (eeh_dev_check_failure(eehdev)) अणु
		/* The EEH mechanisms will handle the error and reset the
		 * device अगर necessary.
		 */
		वापस 1;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* Tears करोwn the entire software state and most of the hardware state
 * beक्रमe reset.
 */
व्योम efx_reset_करोwn(काष्ठा efx_nic *efx, क्रमागत reset_type method)
अणु
	EFX_ASSERT_RESET_SERIALISED(efx);

	अगर (method == RESET_TYPE_MCDI_TIMEOUT)
		efx->type->prepare_flr(efx);

	efx_stop_all(efx);
	efx_disable_पूर्णांकerrupts(efx);

	mutex_lock(&efx->mac_lock);
	करोwn_ग_लिखो(&efx->filter_sem);
	mutex_lock(&efx->rss_lock);
	efx->type->fini(efx);
पूर्ण

/* Context: netअगर_tx_lock held, BHs disabled. */
व्योम efx_watchकरोg(काष्ठा net_device *net_dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	netअगर_err(efx, tx_err, efx->net_dev,
		  "TX stuck with port_enabled=%d: resetting channels\n",
		  efx->port_enabled);

	efx_schedule_reset(efx, RESET_TYPE_TX_WATCHDOG);
पूर्ण

/* This function will always ensure that the locks acquired in
 * efx_reset_करोwn() are released. A failure वापस code indicates
 * that we were unable to reinitialise the hardware, and the
 * driver should be disabled. If ok is false, then the rx and tx
 * engines are not restarted, pending a RESET_DISABLE.
 */
पूर्णांक efx_reset_up(काष्ठा efx_nic *efx, क्रमागत reset_type method, bool ok)
अणु
	पूर्णांक rc;

	EFX_ASSERT_RESET_SERIALISED(efx);

	अगर (method == RESET_TYPE_MCDI_TIMEOUT)
		efx->type->finish_flr(efx);

	/* Ensure that SRAM is initialised even अगर we're disabling the device */
	rc = efx->type->init(efx);
	अगर (rc) अणु
		netअगर_err(efx, drv, efx->net_dev, "failed to initialise NIC\n");
		जाओ fail;
	पूर्ण

	अगर (!ok)
		जाओ fail;

	अगर (efx->port_initialized && method != RESET_TYPE_INVISIBLE &&
	    method != RESET_TYPE_DATAPATH) अणु
		rc = efx_mcdi_port_reconfigure(efx);
		अगर (rc && rc != -EPERM)
			netअगर_err(efx, drv, efx->net_dev,
				  "could not restore PHY settings\n");
	पूर्ण

	rc = efx_enable_पूर्णांकerrupts(efx);
	अगर (rc)
		जाओ fail;

#अगर_घोषित CONFIG_SFC_SRIOV
	rc = efx->type->vचयनing_restore(efx);
	अगर (rc) /* not fatal; the PF will still work fine */
		netअगर_warn(efx, probe, efx->net_dev,
			   "failed to restore vswitching rc=%d;"
			   " VFs may not function\n", rc);
#पूर्ण_अगर

	अगर (efx->type->rx_restore_rss_contexts)
		efx->type->rx_restore_rss_contexts(efx);
	mutex_unlock(&efx->rss_lock);
	efx->type->filter_table_restore(efx);
	up_ग_लिखो(&efx->filter_sem);
	अगर (efx->type->sriov_reset)
		efx->type->sriov_reset(efx);

	mutex_unlock(&efx->mac_lock);

	efx_start_all(efx);

	अगर (efx->type->udp_tnl_push_ports)
		efx->type->udp_tnl_push_ports(efx);

	वापस 0;

fail:
	efx->port_initialized = false;

	mutex_unlock(&efx->rss_lock);
	up_ग_लिखो(&efx->filter_sem);
	mutex_unlock(&efx->mac_lock);

	वापस rc;
पूर्ण

/* Reset the NIC using the specअगरied method.  Note that the reset may
 * fail, in which हाल the card will be left in an unusable state.
 *
 * Caller must hold the rtnl_lock.
 */
पूर्णांक efx_reset(काष्ठा efx_nic *efx, क्रमागत reset_type method)
अणु
	पूर्णांक rc, rc2 = 0;
	bool disabled;

	netअगर_info(efx, drv, efx->net_dev, "resetting (%s)\n",
		   RESET_TYPE(method));

	efx_device_detach_sync(efx);
	/* efx_reset_करोwn() grअसल locks that prevent recovery on EF100.
	 * EF100 reset is handled in the efx_nic_type callback below.
	 */
	अगर (efx_nic_rev(efx) != EFX_REV_EF100)
		efx_reset_करोwn(efx, method);

	rc = efx->type->reset(efx, method);
	अगर (rc) अणु
		netअगर_err(efx, drv, efx->net_dev, "failed to reset hardware\n");
		जाओ out;
	पूर्ण

	/* Clear flags क्रम the scopes we covered.  We assume the NIC and
	 * driver are now quiescent so that there is no race here.
	 */
	अगर (method < RESET_TYPE_MAX_METHOD)
		efx->reset_pending &= -(1 << (method + 1));
	अन्यथा /* it करोesn't fit पूर्णांकo the well-ordered scope hierarchy */
		__clear_bit(method, &efx->reset_pending);

	/* Reinitialise bus-mastering, which may have been turned off beक्रमe
	 * the reset was scheduled. This is still appropriate, even in the
	 * RESET_TYPE_DISABLE since this driver generally assumes the hardware
	 * can respond to requests.
	 */
	pci_set_master(efx->pci_dev);

out:
	/* Leave device stopped अगर necessary */
	disabled = rc ||
		method == RESET_TYPE_DISABLE ||
		method == RESET_TYPE_RECOVER_OR_DISABLE;
	अगर (efx_nic_rev(efx) != EFX_REV_EF100)
		rc2 = efx_reset_up(efx, method, !disabled);
	अगर (rc2) अणु
		disabled = true;
		अगर (!rc)
			rc = rc2;
	पूर्ण

	अगर (disabled) अणु
		dev_बंद(efx->net_dev);
		netअगर_err(efx, drv, efx->net_dev, "has been disabled\n");
		efx->state = STATE_DISABLED;
	पूर्ण अन्यथा अणु
		netअगर_dbg(efx, drv, efx->net_dev, "reset complete\n");
		efx_device_attach_अगर_not_resetting(efx);
	पूर्ण
	वापस rc;
पूर्ण

/* The worker thपढ़ो exists so that code that cannot sleep can
 * schedule a reset क्रम later.
 */
अटल व्योम efx_reset_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा efx_nic *efx = container_of(data, काष्ठा efx_nic, reset_work);
	अचिन्हित दीर्घ pending;
	क्रमागत reset_type method;

	pending = READ_ONCE(efx->reset_pending);
	method = fls(pending) - 1;

	अगर (method == RESET_TYPE_MC_BIST)
		efx_रुको_क्रम_bist_end(efx);

	अगर ((method == RESET_TYPE_RECOVER_OR_DISABLE ||
	     method == RESET_TYPE_RECOVER_OR_ALL) &&
	    efx_try_recovery(efx))
		वापस;

	अगर (!pending)
		वापस;

	rtnl_lock();

	/* We checked the state in efx_schedule_reset() but it may
	 * have changed by now.  Now that we have the RTNL lock,
	 * it cannot change again.
	 */
	अगर (efx->state == STATE_READY)
		(व्योम)efx_reset(efx, method);

	rtnl_unlock();
पूर्ण

व्योम efx_schedule_reset(काष्ठा efx_nic *efx, क्रमागत reset_type type)
अणु
	क्रमागत reset_type method;

	अगर (efx->state == STATE_RECOVERY) अणु
		netअगर_dbg(efx, drv, efx->net_dev,
			  "recovering: skip scheduling %s reset\n",
			  RESET_TYPE(type));
		वापस;
	पूर्ण

	चयन (type) अणु
	हाल RESET_TYPE_INVISIBLE:
	हाल RESET_TYPE_ALL:
	हाल RESET_TYPE_RECOVER_OR_ALL:
	हाल RESET_TYPE_WORLD:
	हाल RESET_TYPE_DISABLE:
	हाल RESET_TYPE_RECOVER_OR_DISABLE:
	हाल RESET_TYPE_DATAPATH:
	हाल RESET_TYPE_MC_BIST:
	हाल RESET_TYPE_MCDI_TIMEOUT:
		method = type;
		netअगर_dbg(efx, drv, efx->net_dev, "scheduling %s reset\n",
			  RESET_TYPE(method));
		अवरोध;
	शेष:
		method = efx->type->map_reset_reason(type);
		netअगर_dbg(efx, drv, efx->net_dev,
			  "scheduling %s reset for %s\n",
			  RESET_TYPE(method), RESET_TYPE(type));
		अवरोध;
	पूर्ण

	set_bit(method, &efx->reset_pending);
	smp_mb(); /* ensure we change reset_pending beक्रमe checking state */

	/* If we're not READY then just leave the flags set as the cue
	 * to पात probing or reschedule the reset later.
	 */
	अगर (READ_ONCE(efx->state) != STATE_READY)
		वापस;

	/* efx_process_channel() will no दीर्घer पढ़ो events once a
	 * reset is scheduled. So चयन back to poll'd MCDI completions.
	 */
	efx_mcdi_mode_poll(efx);

	efx_queue_reset_work(efx);
पूर्ण

/**************************************************************************
 *
 * Dummy NIC operations
 *
 * Can be used क्रम some unimplemented operations
 * Needed so all function poपूर्णांकers are valid and करो not have to be tested
 * beक्रमe use
 *
 **************************************************************************/
पूर्णांक efx_port_dummy_op_पूर्णांक(काष्ठा efx_nic *efx)
अणु
	वापस 0;
पूर्ण
व्योम efx_port_dummy_op_व्योम(काष्ठा efx_nic *efx) अणुपूर्ण

/**************************************************************************
 *
 * Data housekeeping
 *
 **************************************************************************/

/* This zeroes out and then fills in the invariants in a काष्ठा
 * efx_nic (including all sub-काष्ठाures).
 */
पूर्णांक efx_init_काष्ठा(काष्ठा efx_nic *efx,
		    काष्ठा pci_dev *pci_dev, काष्ठा net_device *net_dev)
अणु
	पूर्णांक rc = -ENOMEM;

	/* Initialise common काष्ठाures */
	INIT_LIST_HEAD(&efx->node);
	INIT_LIST_HEAD(&efx->secondary_list);
	spin_lock_init(&efx->biu_lock);
#अगर_घोषित CONFIG_SFC_MTD
	INIT_LIST_HEAD(&efx->mtd_list);
#पूर्ण_अगर
	INIT_WORK(&efx->reset_work, efx_reset_work);
	INIT_DELAYED_WORK(&efx->monitor_work, efx_monitor);
	efx_selftest_async_init(efx);
	efx->pci_dev = pci_dev;
	efx->msg_enable = debug;
	efx->state = STATE_UNINIT;
	strlcpy(efx->name, pci_name(pci_dev), माप(efx->name));

	efx->net_dev = net_dev;
	efx->rx_prefix_size = efx->type->rx_prefix_size;
	efx->rx_ip_align =
		NET_IP_ALIGN ? (efx->rx_prefix_size + NET_IP_ALIGN) % 4 : 0;
	efx->rx_packet_hash_offset =
		efx->type->rx_hash_offset - efx->type->rx_prefix_size;
	efx->rx_packet_ts_offset =
		efx->type->rx_ts_offset - efx->type->rx_prefix_size;
	INIT_LIST_HEAD(&efx->rss_context.list);
	efx->rss_context.context_id = EFX_MCDI_RSS_CONTEXT_INVALID;
	mutex_init(&efx->rss_lock);
	efx->vport_id = EVB_PORT_ID_ASSIGNED;
	spin_lock_init(&efx->stats_lock);
	efx->vi_stride = EFX_DEFAULT_VI_STRIDE;
	efx->num_mac_stats = MC_CMD_MAC_NSTATS;
	BUILD_BUG_ON(MC_CMD_MAC_NSTATS - 1 != MC_CMD_MAC_GENERATION_END);
	mutex_init(&efx->mac_lock);
	init_rwsem(&efx->filter_sem);
#अगर_घोषित CONFIG_RFS_ACCEL
	mutex_init(&efx->rps_mutex);
	spin_lock_init(&efx->rps_hash_lock);
	/* Failure to allocate is not fatal, but may degrade ARFS perक्रमmance */
	efx->rps_hash_table = kसुस्मृति(EFX_ARFS_HASH_TABLE_SIZE,
				      माप(*efx->rps_hash_table), GFP_KERNEL);
#पूर्ण_अगर
	efx->mdio.dev = net_dev;
	INIT_WORK(&efx->mac_work, efx_mac_work);
	init_रुकोqueue_head(&efx->flush_wq);

	efx->tx_queues_per_channel = 1;
	efx->rxq_entries = EFX_DEFAULT_DMAQ_SIZE;
	efx->txq_entries = EFX_DEFAULT_DMAQ_SIZE;

	efx->mem_bar = अच_पूर्णांक_उच्च;

	rc = efx_init_channels(efx);
	अगर (rc)
		जाओ fail;

	/* Would be good to use the net_dev name, but we're too early */
	snम_लिखो(efx->workqueue_name, माप(efx->workqueue_name), "sfc%s",
		 pci_name(pci_dev));
	efx->workqueue = create_singlethपढ़ो_workqueue(efx->workqueue_name);
	अगर (!efx->workqueue) अणु
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	efx_fini_काष्ठा(efx);
	वापस rc;
पूर्ण

व्योम efx_fini_काष्ठा(काष्ठा efx_nic *efx)
अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	kमुक्त(efx->rps_hash_table);
#पूर्ण_अगर

	efx_fini_channels(efx);

	kमुक्त(efx->vpd_sn);

	अगर (efx->workqueue) अणु
		destroy_workqueue(efx->workqueue);
		efx->workqueue = शून्य;
	पूर्ण
पूर्ण

/* This configures the PCI device to enable I/O and DMA. */
पूर्णांक efx_init_io(काष्ठा efx_nic *efx, पूर्णांक bar, dma_addr_t dma_mask,
		अचिन्हित पूर्णांक mem_map_size)
अणु
	काष्ठा pci_dev *pci_dev = efx->pci_dev;
	पूर्णांक rc;

	efx->mem_bar = अच_पूर्णांक_उच्च;

	netअगर_dbg(efx, probe, efx->net_dev, "initialising I/O bar=%d\n", bar);

	rc = pci_enable_device(pci_dev);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "failed to enable PCI device\n");
		जाओ fail1;
	पूर्ण

	pci_set_master(pci_dev);

	rc = dma_set_mask_and_coherent(&pci_dev->dev, dma_mask);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "could not find a suitable DMA mask\n");
		जाओ fail2;
	पूर्ण
	netअगर_dbg(efx, probe, efx->net_dev,
		  "using DMA mask %llx\n", (अचिन्हित दीर्घ दीर्घ)dma_mask);

	efx->membase_phys = pci_resource_start(efx->pci_dev, bar);
	अगर (!efx->membase_phys) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "ERROR: No BAR%d mapping from the BIOS. "
			  "Try pci=realloc on the kernel command line\n", bar);
		rc = -ENODEV;
		जाओ fail3;
	पूर्ण

	rc = pci_request_region(pci_dev, bar, "sfc");
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "request for memory BAR[%d] failed\n", bar);
		rc = -EIO;
		जाओ fail3;
	पूर्ण
	efx->mem_bar = bar;
	efx->membase = ioremap(efx->membase_phys, mem_map_size);
	अगर (!efx->membase) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "could not map memory BAR[%d] at %llx+%x\n", bar,
			  (अचिन्हित दीर्घ दीर्घ)efx->membase_phys, mem_map_size);
		rc = -ENOMEM;
		जाओ fail4;
	पूर्ण
	netअगर_dbg(efx, probe, efx->net_dev,
		  "memory BAR[%d] at %llx+%x (virtual %p)\n", bar,
		  (अचिन्हित दीर्घ दीर्घ)efx->membase_phys, mem_map_size,
		  efx->membase);

	वापस 0;

fail4:
	pci_release_region(efx->pci_dev, bar);
fail3:
	efx->membase_phys = 0;
fail2:
	pci_disable_device(efx->pci_dev);
fail1:
	वापस rc;
पूर्ण

व्योम efx_fini_io(काष्ठा efx_nic *efx)
अणु
	netअगर_dbg(efx, drv, efx->net_dev, "shutting down I/O\n");

	अगर (efx->membase) अणु
		iounmap(efx->membase);
		efx->membase = शून्य;
	पूर्ण

	अगर (efx->membase_phys) अणु
		pci_release_region(efx->pci_dev, efx->mem_bar);
		efx->membase_phys = 0;
		efx->mem_bar = अच_पूर्णांक_उच्च;
	पूर्ण

	/* Don't disable bus-mastering अगर VFs are asचिन्हित */
	अगर (!pci_vfs_asचिन्हित(efx->pci_dev))
		pci_disable_device(efx->pci_dev);
पूर्ण

#अगर_घोषित CONFIG_SFC_MCDI_LOGGING
अटल sमाप_प्रकार show_mcdi_log(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा efx_nic *efx = dev_get_drvdata(dev);
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", mcdi->logging_enabled);
पूर्ण

अटल sमाप_प्रकार set_mcdi_log(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा efx_nic *efx = dev_get_drvdata(dev);
	काष्ठा efx_mcdi_अगरace *mcdi = efx_mcdi(efx);
	bool enable = count > 0 && *buf != '0';

	mcdi->logging_enabled = enable;
	वापस count;
पूर्ण

अटल DEVICE_ATTR(mcdi_logging, 0644, show_mcdi_log, set_mcdi_log);

व्योम efx_init_mcdi_logging(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc = device_create_file(&efx->pci_dev->dev, &dev_attr_mcdi_logging);

	अगर (rc) अणु
		netअगर_warn(efx, drv, efx->net_dev,
			   "failed to init net dev attributes\n");
	पूर्ण
पूर्ण

व्योम efx_fini_mcdi_logging(काष्ठा efx_nic *efx)
अणु
	device_हटाओ_file(&efx->pci_dev->dev, &dev_attr_mcdi_logging);
पूर्ण
#पूर्ण_अगर

/* A PCI error affecting this device was detected.
 * At this poपूर्णांक MMIO and DMA may be disabled.
 * Stop the software path and request a slot reset.
 */
अटल pci_ers_result_t efx_io_error_detected(काष्ठा pci_dev *pdev,
					      pci_channel_state_t state)
अणु
	pci_ers_result_t status = PCI_ERS_RESULT_RECOVERED;
	काष्ठा efx_nic *efx = pci_get_drvdata(pdev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	rtnl_lock();

	अगर (efx->state != STATE_DISABLED) अणु
		efx->state = STATE_RECOVERY;
		efx->reset_pending = 0;

		efx_device_detach_sync(efx);

		efx_stop_all(efx);
		efx_disable_पूर्णांकerrupts(efx);

		status = PCI_ERS_RESULT_NEED_RESET;
	पूर्ण अन्यथा अणु
		/* If the पूर्णांकerface is disabled we करोn't want to करो anything
		 * with it.
		 */
		status = PCI_ERS_RESULT_RECOVERED;
	पूर्ण

	rtnl_unlock();

	pci_disable_device(pdev);

	वापस status;
पूर्ण

/* Fake a successful reset, which will be perक्रमmed later in efx_io_resume. */
अटल pci_ers_result_t efx_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा efx_nic *efx = pci_get_drvdata(pdev);
	pci_ers_result_t status = PCI_ERS_RESULT_RECOVERED;

	अगर (pci_enable_device(pdev)) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "Cannot re-enable PCI device after reset.\n");
		status =  PCI_ERS_RESULT_DISCONNECT;
	पूर्ण

	वापस status;
पूर्ण

/* Perक्रमm the actual reset and resume I/O operations. */
अटल व्योम efx_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा efx_nic *efx = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rtnl_lock();

	अगर (efx->state == STATE_DISABLED)
		जाओ out;

	rc = efx_reset(efx, RESET_TYPE_ALL);
	अगर (rc) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "efx_reset failed after PCI error (%d)\n", rc);
	पूर्ण अन्यथा अणु
		efx->state = STATE_READY;
		netअगर_dbg(efx, hw, efx->net_dev,
			  "Done resetting and resuming IO after PCI error.\n");
	पूर्ण

out:
	rtnl_unlock();
पूर्ण

/* For simplicity and reliability, we always require a slot reset and try to
 * reset the hardware when a pci error affecting the device is detected.
 * We leave both the link_reset and mmio_enabled callback unimplemented:
 * with our request क्रम slot reset the mmio_enabled callback will never be
 * called, and the link_reset callback is not used by AER or EEH mechanisms.
 */
स्थिर काष्ठा pci_error_handlers efx_err_handlers = अणु
	.error_detected = efx_io_error_detected,
	.slot_reset	= efx_io_slot_reset,
	.resume		= efx_io_resume,
पूर्ण;

/* Determine whether the NIC will be able to handle TX offloads क्रम a given
 * encapsulated packet.
 */
अटल bool efx_can_encap_offloads(काष्ठा efx_nic *efx, काष्ठा sk_buff *skb)
अणु
	काष्ठा gre_base_hdr *greh;
	__be16 dst_port;
	u8 ipproto;

	/* Does the NIC support encap offloads?
	 * If not, we should never get here, because we shouldn't have
	 * advertised encap offload feature flags in the first place.
	 */
	अगर (WARN_ON_ONCE(!efx->type->udp_tnl_has_port))
		वापस false;

	/* Determine encapsulation protocol in use */
	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		ipproto = ip_hdr(skb)->protocol;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		/* If there are extension headers, this will cause us to
		 * think we can't offload something that we maybe could have.
		 */
		ipproto = ipv6_hdr(skb)->nexthdr;
		अवरोध;
	शेष:
		/* Not IP, so can't offload it */
		वापस false;
	पूर्ण
	चयन (ipproto) अणु
	हाल IPPROTO_GRE:
		/* We support NVGRE but not IP over GRE or अक्रमom gretaps.
		 * Specअगरically, the NIC will accept GRE as encapsulated अगर
		 * the inner protocol is Ethernet, but only handle it
		 * correctly अगर the GRE header is 8 bytes दीर्घ.  Moreover,
		 * it will not update the Checksum or Sequence Number fields
		 * अगर they are present.  (The Routing Present flag,
		 * GRE_ROUTING, cannot be set अन्यथा the header would be more
		 * than 8 bytes दीर्घ; so we करोn't have to worry about it.)
		 */
		अगर (skb->inner_protocol_type != ENCAP_TYPE_ETHER)
			वापस false;
		अगर (ntohs(skb->inner_protocol) != ETH_P_TEB)
			वापस false;
		अगर (skb_inner_mac_header(skb) - skb_transport_header(skb) != 8)
			वापस false;
		greh = (काष्ठा gre_base_hdr *)skb_transport_header(skb);
		वापस !(greh->flags & (GRE_CSUM | GRE_SEQ));
	हाल IPPROTO_UDP:
		/* If the port is रेजिस्टरed क्रम a UDP tunnel, we assume the
		 * packet is क्रम that tunnel, and the NIC will handle it as
		 * such.  If not, the NIC won't know what to करो with it.
		 */
		dst_port = udp_hdr(skb)->dest;
		वापस efx->type->udp_tnl_has_port(efx, dst_port);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

netdev_features_t efx_features_check(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				     netdev_features_t features)
अणु
	काष्ठा efx_nic *efx = netdev_priv(dev);

	अगर (skb->encapsulation) अणु
		अगर (features & NETIF_F_GSO_MASK)
			/* Hardware can only करो TSO with at most 208 bytes
			 * of headers.
			 */
			अगर (skb_inner_transport_offset(skb) >
			    EFX_TSO2_MAX_HDRLEN)
				features &= ~(NETIF_F_GSO_MASK);
		अगर (features & (NETIF_F_GSO_MASK | NETIF_F_CSUM_MASK))
			अगर (!efx_can_encap_offloads(efx, skb))
				features &= ~(NETIF_F_GSO_MASK |
					      NETIF_F_CSUM_MASK);
	पूर्ण
	वापस features;
पूर्ण

पूर्णांक efx_get_phys_port_id(काष्ठा net_device *net_dev,
			 काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	अगर (efx->type->get_phys_port_id)
		वापस efx->type->get_phys_port_id(efx, ppid);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक efx_get_phys_port_name(काष्ठा net_device *net_dev, अक्षर *name, माप_प्रकार len)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	अगर (snम_लिखो(name, len, "p%u", efx->port_num) >= len)
		वापस -EINVAL;
	वापस 0;
पूर्ण
