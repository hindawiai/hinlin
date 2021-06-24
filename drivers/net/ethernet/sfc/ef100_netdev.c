<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2018 Solarflare Communications Inc.
 * Copyright 2019-2020 Xilinx Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */
#समावेश "net_driver.h"
#समावेश "mcdi_port_common.h"
#समावेश "mcdi_functions.h"
#समावेश "efx_common.h"
#समावेश "efx_channels.h"
#समावेश "tx_common.h"
#समावेश "ef100_netdev.h"
#समावेश "ef100_ethtool.h"
#समावेश "nic_common.h"
#समावेश "ef100_nic.h"
#समावेश "ef100_tx.h"
#समावेश "ef100_regs.h"
#समावेश "mcdi_filters.h"
#समावेश "rx_common.h"

अटल व्योम ef100_update_name(काष्ठा efx_nic *efx)
अणु
	म_नकल(efx->name, efx->net_dev->name);
पूर्ण

अटल पूर्णांक ef100_alloc_vis(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक *allocated_vis)
अणु
	/* EF100 uses a single TXQ per channel, as all checksum offloading
	 * is configured in the TX descriptor, and there is no TX Pacer क्रम
	 * HIGHPRI queues.
	 */
	अचिन्हित पूर्णांक tx_vis = efx->n_tx_channels + efx->n_extra_tx_channels;
	अचिन्हित पूर्णांक rx_vis = efx->n_rx_channels;
	अचिन्हित पूर्णांक min_vis, max_vis;

	EFX_WARN_ON_PARANOID(efx->tx_queues_per_channel != 1);

	tx_vis += efx->n_xdp_channels * efx->xdp_tx_per_channel;

	max_vis = max(rx_vis, tx_vis);
	/* Currently करोn't handle resource starvation and only accept
	 * our maximum needs and no less.
	 */
	min_vis = max_vis;

	वापस efx_mcdi_alloc_vis(efx, min_vis, max_vis,
				  शून्य, allocated_vis);
पूर्ण

अटल पूर्णांक ef100_remap_bar(काष्ठा efx_nic *efx, पूर्णांक max_vis)
अणु
	अचिन्हित पूर्णांक uc_mem_map_size;
	व्योम __iomem *membase;

	efx->max_vis = max_vis;
	uc_mem_map_size = PAGE_ALIGN(max_vis * efx->vi_stride);

	/* Extend the original UC mapping of the memory BAR */
	membase = ioremap(efx->membase_phys, uc_mem_map_size);
	अगर (!membase) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "could not extend memory BAR to %x\n",
			  uc_mem_map_size);
		वापस -ENOMEM;
	पूर्ण
	iounmap(efx->membase);
	efx->membase = membase;
	वापस 0;
पूर्ण

/* Context: process, rtnl_lock() held.
 * Note that the kernel will ignore our वापस code; this method
 * should really be a व्योम.
 */
अटल पूर्णांक ef100_net_stop(काष्ठा net_device *net_dev)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	netअगर_dbg(efx, अगरकरोwn, efx->net_dev, "closing on CPU %d\n",
		  raw_smp_processor_id());

	netअगर_stop_queue(net_dev);
	efx_stop_all(efx);
	efx_mcdi_mac_fini_stats(efx);
	efx_disable_पूर्णांकerrupts(efx);
	efx_clear_पूर्णांकerrupt_affinity(efx);
	efx_nic_fini_पूर्णांकerrupt(efx);
	efx_हटाओ_filters(efx);
	efx_fini_napi(efx);
	efx_हटाओ_channels(efx);
	efx_mcdi_मुक्त_vis(efx);
	efx_हटाओ_पूर्णांकerrupts(efx);

	वापस 0;
पूर्ण

/* Context: process, rtnl_lock() held. */
अटल पूर्णांक ef100_net_खोलो(काष्ठा net_device *net_dev)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	अचिन्हित पूर्णांक allocated_vis;
	पूर्णांक rc;

	ef100_update_name(efx);
	netअगर_dbg(efx, अगरup, net_dev, "opening device on CPU %d\n",
		  raw_smp_processor_id());

	rc = efx_check_disabled(efx);
	अगर (rc)
		जाओ fail;

	rc = efx_probe_पूर्णांकerrupts(efx);
	अगर (rc)
		जाओ fail;

	rc = efx_set_channels(efx);
	अगर (rc)
		जाओ fail;

	rc = efx_mcdi_मुक्त_vis(efx);
	अगर (rc)
		जाओ fail;

	rc = ef100_alloc_vis(efx, &allocated_vis);
	अगर (rc)
		जाओ fail;

	rc = efx_probe_channels(efx);
	अगर (rc)
		वापस rc;

	rc = ef100_remap_bar(efx, allocated_vis);
	अगर (rc)
		जाओ fail;

	efx_init_napi(efx);

	rc = efx_probe_filters(efx);
	अगर (rc)
		जाओ fail;

	rc = efx_nic_init_पूर्णांकerrupt(efx);
	अगर (rc)
		जाओ fail;
	efx_set_पूर्णांकerrupt_affinity(efx);

	rc = efx_enable_पूर्णांकerrupts(efx);
	अगर (rc)
		जाओ fail;

	/* in हाल the MC rebooted जबतक we were stopped, consume the change
	 * to the warm reboot count
	 */
	(व्योम) efx_mcdi_poll_reboot(efx);

	rc = efx_mcdi_mac_init_stats(efx);
	अगर (rc)
		जाओ fail;

	efx_start_all(efx);

	/* Link state detection is normally event-driven; we have
	 * to poll now because we could have missed a change
	 */
	mutex_lock(&efx->mac_lock);
	अगर (efx_mcdi_phy_poll(efx))
		efx_link_status_changed(efx);
	mutex_unlock(&efx->mac_lock);

	वापस 0;

fail:
	ef100_net_stop(net_dev);
	वापस rc;
पूर्ण

/* Initiate a packet transmission.  We use one channel per CPU
 * (sharing when we have more CPUs than channels).
 *
 * Context: non-blocking.
 * Note that वापसing anything other than NETDEV_TX_OK will cause the
 * OS to मुक्त the skb.
 */
अटल netdev_tx_t ef100_hard_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *net_dev)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा efx_channel *channel;
	पूर्णांक rc;

	channel = efx_get_tx_channel(efx, skb_get_queue_mapping(skb));
	netअगर_vdbg(efx, tx_queued, efx->net_dev,
		   "%s len %d data %d channel %d\n", __func__,
		   skb->len, skb->data_len, channel->channel);
	अगर (!efx->n_channels || !efx->n_tx_channels || !channel) अणु
		netअगर_stop_queue(net_dev);
		जाओ err;
	पूर्ण

	tx_queue = &channel->tx_queue[0];
	rc = ef100_enqueue_skb(tx_queue, skb);
	अगर (rc == 0)
		वापस NETDEV_TX_OK;

err:
	net_dev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ef100_netdev_ops = अणु
	.nकरो_खोलो               = ef100_net_खोलो,
	.nकरो_stop               = ef100_net_stop,
	.nकरो_start_xmit         = ef100_hard_start_xmit,
	.nकरो_tx_समयout         = efx_watchकरोg,
	.nकरो_get_stats64        = efx_net_stats,
	.nकरो_change_mtu         = efx_change_mtu,
	.nकरो_validate_addr      = eth_validate_addr,
	.nकरो_set_mac_address    = efx_set_mac_address,
	.nकरो_set_rx_mode        = efx_set_rx_mode, /* Lookout */
	.nकरो_set_features       = efx_set_features,
	.nकरो_get_phys_port_id   = efx_get_phys_port_id,
	.nकरो_get_phys_port_name = efx_get_phys_port_name,
#अगर_घोषित CONFIG_RFS_ACCEL
	.nकरो_rx_flow_steer      = efx_filter_rfs,
#पूर्ण_अगर
पूर्ण;

/*	Netdev registration
 */
पूर्णांक ef100_netdev_event(काष्ठा notअगरier_block *this,
		       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा efx_nic *efx = container_of(this, काष्ठा efx_nic, netdev_notअगरier);
	काष्ठा net_device *net_dev = netdev_notअगरier_info_to_dev(ptr);

	अगर (netdev_priv(net_dev) == efx && event == NETDEV_CHANGENAME)
		ef100_update_name(efx);

	वापस NOTIFY_DONE;
पूर्ण

पूर्णांक ef100_रेजिस्टर_netdev(काष्ठा efx_nic *efx)
अणु
	काष्ठा net_device *net_dev = efx->net_dev;
	पूर्णांक rc;

	net_dev->watchकरोg_समयo = 5 * HZ;
	net_dev->irq = efx->pci_dev->irq;
	net_dev->netdev_ops = &ef100_netdev_ops;
	net_dev->min_mtu = EFX_MIN_MTU;
	net_dev->max_mtu = EFX_MAX_MTU;
	net_dev->ethtool_ops = &ef100_ethtool_ops;

	rtnl_lock();

	rc = dev_alloc_name(net_dev, net_dev->name);
	अगर (rc < 0)
		जाओ fail_locked;
	ef100_update_name(efx);

	rc = रेजिस्टर_netdevice(net_dev);
	अगर (rc)
		जाओ fail_locked;

	/* Always start with carrier off; PHY events will detect the link */
	netअगर_carrier_off(net_dev);

	efx->state = STATE_READY;
	rtnl_unlock();
	efx_init_mcdi_logging(efx);

	वापस 0;

fail_locked:
	rtnl_unlock();
	netअगर_err(efx, drv, efx->net_dev, "could not register net dev\n");
	वापस rc;
पूर्ण

व्योम ef100_unरेजिस्टर_netdev(काष्ठा efx_nic *efx)
अणु
	अगर (efx_dev_रेजिस्टरed(efx)) अणु
		efx_fini_mcdi_logging(efx);
		efx->state = STATE_UNINIT;
		unरेजिस्टर_netdev(efx->net_dev);
	पूर्ण
पूर्ण
