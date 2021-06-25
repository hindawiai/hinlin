<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2005-2013 Solarflare Communications Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/in.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/topology.h>
#समावेश <linux/gfp.h>
#समावेश <linux/aer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश "net_driver.h"
#समावेश <net/gre.h>
#समावेश <net/udp_tunnel.h>
#समावेश "efx.h"
#समावेश "efx_common.h"
#समावेश "efx_channels.h"
#समावेश "ef100.h"
#समावेश "rx_common.h"
#समावेश "tx_common.h"
#समावेश "nic.h"
#समावेश "io.h"
#समावेश "selftest.h"
#समावेश "sriov.h"

#समावेश "mcdi_port_common.h"
#समावेश "mcdi_pcol.h"
#समावेश "workarounds.h"

/**************************************************************************
 *
 * Configurable values
 *
 *************************************************************************/

module_param_named(पूर्णांकerrupt_mode, efx_पूर्णांकerrupt_mode, uपूर्णांक, 0444);
MODULE_PARM_DESC(पूर्णांकerrupt_mode,
		 "Interrupt mode (0=>MSIX 1=>MSI 2=>legacy)");

module_param(rss_cpus, uपूर्णांक, 0444);
MODULE_PARM_DESC(rss_cpus, "Number of CPUs to use for Receive-Side Scaling");

/*
 * Use separate channels क्रम TX and RX events
 *
 * Set this to 1 to use separate channels क्रम TX and RX. It allows us
 * to control पूर्णांकerrupt affinity separately क्रम TX and RX.
 *
 * This is only used in MSI-X पूर्णांकerrupt mode
 */
bool efx_separate_tx_channels;
module_param(efx_separate_tx_channels, bool, 0444);
MODULE_PARM_DESC(efx_separate_tx_channels,
		 "Use separate channels for TX and RX");

/* Initial पूर्णांकerrupt moderation settings.  They can be modअगरied after
 * module load with ethtool.
 *
 * The शेष क्रम RX should strike a balance between increasing the
 * round-trip latency and reducing overhead.
 */
अटल अचिन्हित पूर्णांक rx_irq_mod_usec = 60;

/* Initial पूर्णांकerrupt moderation settings.  They can be modअगरied after
 * module load with ethtool.
 *
 * This शेष is chosen to ensure that a 10G link करोes not go idle
 * जबतक a TX queue is stopped after it has become full.  A queue is
 * restarted when it drops below half full.  The समय this takes (assuming
 * worst हाल 3 descriptors per packet and 1024 descriptors) is
 *   512 / 3 * 1.2 = 205 usec.
 */
अटल अचिन्हित पूर्णांक tx_irq_mod_usec = 150;

अटल bool phy_flash_cfg;
module_param(phy_flash_cfg, bool, 0644);
MODULE_PARM_DESC(phy_flash_cfg, "Set PHYs into reflash mode initially");

अटल अचिन्हित debug = (NETIF_MSG_DRV | NETIF_MSG_PROBE |
			 NETIF_MSG_LINK | NETIF_MSG_IFDOWN |
			 NETIF_MSG_IFUP | NETIF_MSG_RX_ERR |
			 NETIF_MSG_TX_ERR | NETIF_MSG_HW);
module_param(debug, uपूर्णांक, 0);
MODULE_PARM_DESC(debug, "Bitmapped debugging message enable value");

/**************************************************************************
 *
 * Utility functions and prototypes
 *
 *************************************************************************/

अटल व्योम efx_हटाओ_port(काष्ठा efx_nic *efx);
अटल पूर्णांक efx_xdp_setup_prog(काष्ठा efx_nic *efx, काष्ठा bpf_prog *prog);
अटल पूर्णांक efx_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp);
अटल पूर्णांक efx_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n, काष्ठा xdp_frame **xdpfs,
			u32 flags);

#घोषणा EFX_ASSERT_RESET_SERIALISED(efx)		\
	करो अणु						\
		अगर ((efx->state == STATE_READY) ||	\
		    (efx->state == STATE_RECOVERY) ||	\
		    (efx->state == STATE_DISABLED))	\
			ASSERT_RTNL();			\
	पूर्ण जबतक (0)

/**************************************************************************
 *
 * Port handling
 *
 **************************************************************************/

अटल व्योम efx_fini_port(काष्ठा efx_nic *efx);

अटल पूर्णांक efx_probe_port(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	netअगर_dbg(efx, probe, efx->net_dev, "create port\n");

	अगर (phy_flash_cfg)
		efx->phy_mode = PHY_MODE_SPECIAL;

	/* Connect up MAC/PHY operations table */
	rc = efx->type->probe_port(efx);
	अगर (rc)
		वापस rc;

	/* Initialise MAC address to permanent address */
	ether_addr_copy(efx->net_dev->dev_addr, efx->net_dev->perm_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक efx_init_port(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	netअगर_dbg(efx, drv, efx->net_dev, "init port\n");

	mutex_lock(&efx->mac_lock);

	efx->port_initialized = true;

	/* Ensure the PHY advertises the correct flow control settings */
	rc = efx_mcdi_port_reconfigure(efx);
	अगर (rc && rc != -EPERM)
		जाओ fail;

	mutex_unlock(&efx->mac_lock);
	वापस 0;

fail:
	mutex_unlock(&efx->mac_lock);
	वापस rc;
पूर्ण

अटल व्योम efx_fini_port(काष्ठा efx_nic *efx)
अणु
	netअगर_dbg(efx, drv, efx->net_dev, "shut down port\n");

	अगर (!efx->port_initialized)
		वापस;

	efx->port_initialized = false;

	efx->link_state.up = false;
	efx_link_status_changed(efx);
पूर्ण

अटल व्योम efx_हटाओ_port(काष्ठा efx_nic *efx)
अणु
	netअगर_dbg(efx, drv, efx->net_dev, "destroying port\n");

	efx->type->हटाओ_port(efx);
पूर्ण

/**************************************************************************
 *
 * NIC handling
 *
 **************************************************************************/

अटल LIST_HEAD(efx_primary_list);
अटल LIST_HEAD(efx_unassociated_list);

अटल bool efx_same_controller(काष्ठा efx_nic *left, काष्ठा efx_nic *right)
अणु
	वापस left->type == right->type &&
		left->vpd_sn && right->vpd_sn &&
		!म_भेद(left->vpd_sn, right->vpd_sn);
पूर्ण

अटल व्योम efx_associate(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_nic *other, *next;

	अगर (efx->primary == efx) अणु
		/* Adding primary function; look क्रम secondaries */

		netअगर_dbg(efx, probe, efx->net_dev, "adding to primary list\n");
		list_add_tail(&efx->node, &efx_primary_list);

		list_क्रम_each_entry_safe(other, next, &efx_unassociated_list,
					 node) अणु
			अगर (efx_same_controller(efx, other)) अणु
				list_del(&other->node);
				netअगर_dbg(other, probe, other->net_dev,
					  "moving to secondary list of %s %s\n",
					  pci_name(efx->pci_dev),
					  efx->net_dev->name);
				list_add_tail(&other->node,
					      &efx->secondary_list);
				other->primary = efx;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Adding secondary function; look क्रम primary */

		list_क्रम_each_entry(other, &efx_primary_list, node) अणु
			अगर (efx_same_controller(efx, other)) अणु
				netअगर_dbg(efx, probe, efx->net_dev,
					  "adding to secondary list of %s %s\n",
					  pci_name(other->pci_dev),
					  other->net_dev->name);
				list_add_tail(&efx->node,
					      &other->secondary_list);
				efx->primary = other;
				वापस;
			पूर्ण
		पूर्ण

		netअगर_dbg(efx, probe, efx->net_dev,
			  "adding to unassociated list\n");
		list_add_tail(&efx->node, &efx_unassociated_list);
	पूर्ण
पूर्ण

अटल व्योम efx_dissociate(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_nic *other, *next;

	list_del(&efx->node);
	efx->primary = शून्य;

	list_क्रम_each_entry_safe(other, next, &efx->secondary_list, node) अणु
		list_del(&other->node);
		netअगर_dbg(other, probe, other->net_dev,
			  "moving to unassociated list\n");
		list_add_tail(&other->node, &efx_unassociated_list);
		other->primary = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक efx_probe_nic(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	netअगर_dbg(efx, probe, efx->net_dev, "creating NIC\n");

	/* Carry out hardware-type specअगरic initialisation */
	rc = efx->type->probe(efx);
	अगर (rc)
		वापस rc;

	करो अणु
		अगर (!efx->max_channels || !efx->max_tx_channels) अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "Insufficient resources to allocate"
				  " any channels\n");
			rc = -ENOSPC;
			जाओ fail1;
		पूर्ण

		/* Determine the number of channels and queues by trying
		 * to hook in MSI-X पूर्णांकerrupts.
		 */
		rc = efx_probe_पूर्णांकerrupts(efx);
		अगर (rc)
			जाओ fail1;

		rc = efx_set_channels(efx);
		अगर (rc)
			जाओ fail1;

		/* dimension_resources can fail with EAGAIN */
		rc = efx->type->dimension_resources(efx);
		अगर (rc != 0 && rc != -EAGAIN)
			जाओ fail2;

		अगर (rc == -EAGAIN)
			/* try again with new max_channels */
			efx_हटाओ_पूर्णांकerrupts(efx);

	पूर्ण जबतक (rc == -EAGAIN);

	अगर (efx->n_channels > 1)
		netdev_rss_key_fill(efx->rss_context.rx_hash_key,
				    माप(efx->rss_context.rx_hash_key));
	efx_set_शेष_rx_indir_table(efx, &efx->rss_context);

	/* Initialise the पूर्णांकerrupt moderation settings */
	efx->irq_mod_step_us = DIV_ROUND_UP(efx->समयr_quantum_ns, 1000);
	efx_init_irq_moderation(efx, tx_irq_mod_usec, rx_irq_mod_usec, true,
				true);

	वापस 0;

fail2:
	efx_हटाओ_पूर्णांकerrupts(efx);
fail1:
	efx->type->हटाओ(efx);
	वापस rc;
पूर्ण

अटल व्योम efx_हटाओ_nic(काष्ठा efx_nic *efx)
अणु
	netअगर_dbg(efx, drv, efx->net_dev, "destroying NIC\n");

	efx_हटाओ_पूर्णांकerrupts(efx);
	efx->type->हटाओ(efx);
पूर्ण

/**************************************************************************
 *
 * NIC startup/shutकरोwn
 *
 *************************************************************************/

अटल पूर्णांक efx_probe_all(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	rc = efx_probe_nic(efx);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev, "failed to create NIC\n");
		जाओ fail1;
	पूर्ण

	rc = efx_probe_port(efx);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev, "failed to create port\n");
		जाओ fail2;
	पूर्ण

	BUILD_BUG_ON(EFX_DEFAULT_DMAQ_SIZE < EFX_RXQ_MIN_ENT);
	अगर (WARN_ON(EFX_DEFAULT_DMAQ_SIZE < EFX_TXQ_MIN_ENT(efx))) अणु
		rc = -EINVAL;
		जाओ fail3;
	पूर्ण

#अगर_घोषित CONFIG_SFC_SRIOV
	rc = efx->type->vचयनing_probe(efx);
	अगर (rc) /* not fatal; the PF will still work fine */
		netअगर_warn(efx, probe, efx->net_dev,
			   "failed to setup vswitching rc=%d;"
			   " VFs may not function\n", rc);
#पूर्ण_अगर

	rc = efx_probe_filters(efx);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "failed to create filter tables\n");
		जाओ fail4;
	पूर्ण

	rc = efx_probe_channels(efx);
	अगर (rc)
		जाओ fail5;

	वापस 0;

 fail5:
	efx_हटाओ_filters(efx);
 fail4:
#अगर_घोषित CONFIG_SFC_SRIOV
	efx->type->vचयनing_हटाओ(efx);
#पूर्ण_अगर
 fail3:
	efx_हटाओ_port(efx);
 fail2:
	efx_हटाओ_nic(efx);
 fail1:
	वापस rc;
पूर्ण

अटल व्योम efx_हटाओ_all(काष्ठा efx_nic *efx)
अणु
	rtnl_lock();
	efx_xdp_setup_prog(efx, शून्य);
	rtnl_unlock();

	efx_हटाओ_channels(efx);
	efx_हटाओ_filters(efx);
#अगर_घोषित CONFIG_SFC_SRIOV
	efx->type->vचयनing_हटाओ(efx);
#पूर्ण_अगर
	efx_हटाओ_port(efx);
	efx_हटाओ_nic(efx);
पूर्ण

/**************************************************************************
 *
 * Interrupt moderation
 *
 **************************************************************************/
अचिन्हित पूर्णांक efx_usecs_to_ticks(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक usecs)
अणु
	अगर (usecs == 0)
		वापस 0;
	अगर (usecs * 1000 < efx->समयr_quantum_ns)
		वापस 1; /* never round करोwn to 0 */
	वापस usecs * 1000 / efx->समयr_quantum_ns;
पूर्ण

अचिन्हित पूर्णांक efx_ticks_to_usecs(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक ticks)
अणु
	/* We must round up when converting ticks to microseconds
	 * because we round करोwn when converting the other way.
	 */
	वापस DIV_ROUND_UP(ticks * efx->समयr_quantum_ns, 1000);
पूर्ण

/* Set पूर्णांकerrupt moderation parameters */
पूर्णांक efx_init_irq_moderation(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक tx_usecs,
			    अचिन्हित पूर्णांक rx_usecs, bool rx_adaptive,
			    bool rx_may_override_tx)
अणु
	काष्ठा efx_channel *channel;
	अचिन्हित पूर्णांक समयr_max_us;

	EFX_ASSERT_RESET_SERIALISED(efx);

	समयr_max_us = efx->समयr_max_ns / 1000;

	अगर (tx_usecs > समयr_max_us || rx_usecs > समयr_max_us)
		वापस -EINVAL;

	अगर (tx_usecs != rx_usecs && efx->tx_channel_offset == 0 &&
	    !rx_may_override_tx) अणु
		netअगर_err(efx, drv, efx->net_dev, "Channels are shared. "
			  "RX and TX IRQ moderation must be equal\n");
		वापस -EINVAL;
	पूर्ण

	efx->irq_rx_adaptive = rx_adaptive;
	efx->irq_rx_moderation_us = rx_usecs;
	efx_क्रम_each_channel(channel, efx) अणु
		अगर (efx_channel_has_rx_queue(channel))
			channel->irq_moderation_us = rx_usecs;
		अन्यथा अगर (efx_channel_has_tx_queues(channel))
			channel->irq_moderation_us = tx_usecs;
		अन्यथा अगर (efx_channel_is_xdp_tx(channel))
			channel->irq_moderation_us = tx_usecs;
	पूर्ण

	वापस 0;
पूर्ण

व्योम efx_get_irq_moderation(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक *tx_usecs,
			    अचिन्हित पूर्णांक *rx_usecs, bool *rx_adaptive)
अणु
	*rx_adaptive = efx->irq_rx_adaptive;
	*rx_usecs = efx->irq_rx_moderation_us;

	/* If channels are shared between RX and TX, so is IRQ
	 * moderation.  Otherwise, IRQ moderation is the same क्रम all
	 * TX channels and is not adaptive.
	 */
	अगर (efx->tx_channel_offset == 0) अणु
		*tx_usecs = *rx_usecs;
	पूर्ण अन्यथा अणु
		काष्ठा efx_channel *tx_channel;

		tx_channel = efx->channel[efx->tx_channel_offset];
		*tx_usecs = tx_channel->irq_moderation_us;
	पूर्ण
पूर्ण

/**************************************************************************
 *
 * ioctls
 *
 *************************************************************************/

/* Net device ioctl
 * Context: process, rtnl_lock() held.
 */
अटल पूर्णांक efx_ioctl(काष्ठा net_device *net_dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);

	अगर (cmd == SIOCSHWTSTAMP)
		वापस efx_ptp_set_ts_config(efx, अगरr);
	अगर (cmd == SIOCGHWTSTAMP)
		वापस efx_ptp_get_ts_config(efx, अगरr);

	/* Convert phy_id from older PRTAD/DEVAD क्रमmat */
	अगर ((cmd == SIOCGMIIREG || cmd == SIOCSMIIREG) &&
	    (data->phy_id & 0xfc00) == 0x0400)
		data->phy_id ^= MDIO_PHY_ID_C45 | 0x0400;

	वापस mdio_mii_ioctl(&efx->mdio, data, cmd);
पूर्ण

/**************************************************************************
 *
 * Kernel net device पूर्णांकerface
 *
 *************************************************************************/

/* Context: process, rtnl_lock() held. */
पूर्णांक efx_net_खोलो(काष्ठा net_device *net_dev)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	पूर्णांक rc;

	netअगर_dbg(efx, अगरup, efx->net_dev, "opening device on CPU %d\n",
		  raw_smp_processor_id());

	rc = efx_check_disabled(efx);
	अगर (rc)
		वापस rc;
	अगर (efx->phy_mode & PHY_MODE_SPECIAL)
		वापस -EBUSY;
	अगर (efx_mcdi_poll_reboot(efx) && efx_reset(efx, RESET_TYPE_ALL))
		वापस -EIO;

	/* Notअगरy the kernel of the link state polled during driver load,
	 * beक्रमe the monitor starts running */
	efx_link_status_changed(efx);

	efx_start_all(efx);
	अगर (efx->state == STATE_DISABLED || efx->reset_pending)
		netअगर_device_detach(efx->net_dev);
	efx_selftest_async_start(efx);
	वापस 0;
पूर्ण

/* Context: process, rtnl_lock() held.
 * Note that the kernel will ignore our वापस code; this method
 * should really be a व्योम.
 */
पूर्णांक efx_net_stop(काष्ठा net_device *net_dev)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	netअगर_dbg(efx, अगरकरोwn, efx->net_dev, "closing on CPU %d\n",
		  raw_smp_processor_id());

	/* Stop the device and flush all the channels */
	efx_stop_all(efx);

	वापस 0;
पूर्ण

अटल पूर्णांक efx_vlan_rx_add_vid(काष्ठा net_device *net_dev, __be16 proto, u16 vid)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	अगर (efx->type->vlan_rx_add_vid)
		वापस efx->type->vlan_rx_add_vid(efx, proto, vid);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक efx_vlan_rx_समाप्त_vid(काष्ठा net_device *net_dev, __be16 proto, u16 vid)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	अगर (efx->type->vlan_rx_समाप्त_vid)
		वापस efx->type->vlan_rx_समाप्त_vid(efx, proto, vid);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा net_device_ops efx_netdev_ops = अणु
	.nकरो_खोलो		= efx_net_खोलो,
	.nकरो_stop		= efx_net_stop,
	.nकरो_get_stats64	= efx_net_stats,
	.nकरो_tx_समयout		= efx_watchकरोg,
	.nकरो_start_xmit		= efx_hard_start_xmit,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= efx_ioctl,
	.nकरो_change_mtu		= efx_change_mtu,
	.nकरो_set_mac_address	= efx_set_mac_address,
	.nकरो_set_rx_mode	= efx_set_rx_mode,
	.nकरो_set_features	= efx_set_features,
	.nकरो_features_check	= efx_features_check,
	.nकरो_vlan_rx_add_vid	= efx_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= efx_vlan_rx_समाप्त_vid,
#अगर_घोषित CONFIG_SFC_SRIOV
	.nकरो_set_vf_mac		= efx_sriov_set_vf_mac,
	.nकरो_set_vf_vlan	= efx_sriov_set_vf_vlan,
	.nकरो_set_vf_spoofchk	= efx_sriov_set_vf_spoofchk,
	.nकरो_get_vf_config	= efx_sriov_get_vf_config,
	.nकरो_set_vf_link_state  = efx_sriov_set_vf_link_state,
#पूर्ण_अगर
	.nकरो_get_phys_port_id   = efx_get_phys_port_id,
	.nकरो_get_phys_port_name	= efx_get_phys_port_name,
	.nकरो_setup_tc		= efx_setup_tc,
#अगर_घोषित CONFIG_RFS_ACCEL
	.nकरो_rx_flow_steer	= efx_filter_rfs,
#पूर्ण_अगर
	.nकरो_xdp_xmit		= efx_xdp_xmit,
	.nकरो_bpf		= efx_xdp
पूर्ण;

अटल पूर्णांक efx_xdp_setup_prog(काष्ठा efx_nic *efx, काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog *old_prog;

	अगर (efx->xdp_rxq_info_failed) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "Unable to bind XDP program due to previous failure of rxq_info\n");
		वापस -EINVAL;
	पूर्ण

	अगर (prog && efx->net_dev->mtu > efx_xdp_max_mtu(efx)) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "Unable to configure XDP with MTU of %d (max: %d)\n",
			  efx->net_dev->mtu, efx_xdp_max_mtu(efx));
		वापस -EINVAL;
	पूर्ण

	old_prog = rtnl_dereference(efx->xdp_prog);
	rcu_assign_poपूर्णांकer(efx->xdp_prog, prog);
	/* Release the reference that was originally passed by the caller. */
	अगर (old_prog)
		bpf_prog_put(old_prog);

	वापस 0;
पूर्ण

/* Context: process, rtnl_lock() held. */
अटल पूर्णांक efx_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	काष्ठा efx_nic *efx = netdev_priv(dev);

	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस efx_xdp_setup_prog(efx, xdp->prog);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक efx_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n, काष्ठा xdp_frame **xdpfs,
			u32 flags)
अणु
	काष्ठा efx_nic *efx = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	वापस efx_xdp_tx_buffers(efx, n, xdpfs, flags & XDP_XMIT_FLUSH);
पूर्ण

अटल व्योम efx_update_name(काष्ठा efx_nic *efx)
अणु
	म_नकल(efx->name, efx->net_dev->name);
	efx_mtd_नाम(efx);
	efx_set_channel_names(efx);
पूर्ण

अटल पूर्णांक efx_netdev_event(काष्ठा notअगरier_block *this,
			    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *net_dev = netdev_notअगरier_info_to_dev(ptr);

	अगर ((net_dev->netdev_ops == &efx_netdev_ops) &&
	    event == NETDEV_CHANGENAME)
		efx_update_name(netdev_priv(net_dev));

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block efx_netdev_notअगरier = अणु
	.notअगरier_call = efx_netdev_event,
पूर्ण;

अटल sमाप_प्रकार
show_phy_type(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा efx_nic *efx = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", efx->phy_type);
पूर्ण
अटल DEVICE_ATTR(phy_type, 0444, show_phy_type, शून्य);

अटल पूर्णांक efx_रेजिस्टर_netdev(काष्ठा efx_nic *efx)
अणु
	काष्ठा net_device *net_dev = efx->net_dev;
	काष्ठा efx_channel *channel;
	पूर्णांक rc;

	net_dev->watchकरोg_समयo = 5 * HZ;
	net_dev->irq = efx->pci_dev->irq;
	net_dev->netdev_ops = &efx_netdev_ops;
	अगर (efx_nic_rev(efx) >= EFX_REV_HUNT_A0)
		net_dev->priv_flags |= IFF_UNICAST_FLT;
	net_dev->ethtool_ops = &efx_ethtool_ops;
	net_dev->gso_max_segs = EFX_TSO_MAX_SEGS;
	net_dev->min_mtu = EFX_MIN_MTU;
	net_dev->max_mtu = EFX_MAX_MTU;

	rtnl_lock();

	/* Enable resets to be scheduled and check whether any were
	 * alपढ़ोy requested.  If so, the NIC is probably hosed so we
	 * पात.
	 */
	efx->state = STATE_READY;
	smp_mb(); /* ensure we change state beक्रमe checking reset_pending */
	अगर (efx->reset_pending) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "aborting probe due to scheduled reset\n");
		rc = -EIO;
		जाओ fail_locked;
	पूर्ण

	rc = dev_alloc_name(net_dev, net_dev->name);
	अगर (rc < 0)
		जाओ fail_locked;
	efx_update_name(efx);

	/* Always start with carrier off; PHY events will detect the link */
	netअगर_carrier_off(net_dev);

	rc = रेजिस्टर_netdevice(net_dev);
	अगर (rc)
		जाओ fail_locked;

	efx_क्रम_each_channel(channel, efx) अणु
		काष्ठा efx_tx_queue *tx_queue;
		efx_क्रम_each_channel_tx_queue(tx_queue, channel)
			efx_init_tx_queue_core_txq(tx_queue);
	पूर्ण

	efx_associate(efx);

	rtnl_unlock();

	rc = device_create_file(&efx->pci_dev->dev, &dev_attr_phy_type);
	अगर (rc) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "failed to init net dev attributes\n");
		जाओ fail_रेजिस्टरed;
	पूर्ण

	efx_init_mcdi_logging(efx);

	वापस 0;

fail_रेजिस्टरed:
	rtnl_lock();
	efx_dissociate(efx);
	unरेजिस्टर_netdevice(net_dev);
fail_locked:
	efx->state = STATE_UNINIT;
	rtnl_unlock();
	netअगर_err(efx, drv, efx->net_dev, "could not register net dev\n");
	वापस rc;
पूर्ण

अटल व्योम efx_unरेजिस्टर_netdev(काष्ठा efx_nic *efx)
अणु
	अगर (!efx->net_dev)
		वापस;

	BUG_ON(netdev_priv(efx->net_dev) != efx);

	अगर (efx_dev_रेजिस्टरed(efx)) अणु
		strlcpy(efx->name, pci_name(efx->pci_dev), माप(efx->name));
		efx_fini_mcdi_logging(efx);
		device_हटाओ_file(&efx->pci_dev->dev, &dev_attr_phy_type);
		unरेजिस्टर_netdev(efx->net_dev);
	पूर्ण
पूर्ण

/**************************************************************************
 *
 * List of NICs we support
 *
 **************************************************************************/

/* PCI device ID table */
अटल स्थिर काष्ठा pci_device_id efx_pci_table[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_SOLARFLARE, 0x0803),	/* SFC9020 */
	 .driver_data = (अचिन्हित दीर्घ) &siena_a0_nic_typeपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_SOLARFLARE, 0x0813),	/* SFL9021 */
	 .driver_data = (अचिन्हित दीर्घ) &siena_a0_nic_typeपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_SOLARFLARE, 0x0903),  /* SFC9120 PF */
	 .driver_data = (अचिन्हित दीर्घ) &efx_hunt_a0_nic_typeपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_SOLARFLARE, 0x1903),  /* SFC9120 VF */
	 .driver_data = (अचिन्हित दीर्घ) &efx_hunt_a0_vf_nic_typeपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_SOLARFLARE, 0x0923),  /* SFC9140 PF */
	 .driver_data = (अचिन्हित दीर्घ) &efx_hunt_a0_nic_typeपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_SOLARFLARE, 0x1923),  /* SFC9140 VF */
	 .driver_data = (अचिन्हित दीर्घ) &efx_hunt_a0_vf_nic_typeपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_SOLARFLARE, 0x0a03),  /* SFC9220 PF */
	 .driver_data = (अचिन्हित दीर्घ) &efx_hunt_a0_nic_typeपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_SOLARFLARE, 0x1a03),  /* SFC9220 VF */
	 .driver_data = (अचिन्हित दीर्घ) &efx_hunt_a0_vf_nic_typeपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_SOLARFLARE, 0x0b03),  /* SFC9250 PF */
	 .driver_data = (अचिन्हित दीर्घ) &efx_hunt_a0_nic_typeपूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_SOLARFLARE, 0x1b03),  /* SFC9250 VF */
	 .driver_data = (अचिन्हित दीर्घ) &efx_hunt_a0_vf_nic_typeपूर्ण,
	अणु0पूर्ण			/* end of list */
पूर्ण;

/**************************************************************************
 *
 * Data housekeeping
 *
 **************************************************************************/

व्योम efx_update_sw_stats(काष्ठा efx_nic *efx, u64 *stats)
अणु
	u64 n_rx_nodesc_trunc = 0;
	काष्ठा efx_channel *channel;

	efx_क्रम_each_channel(channel, efx)
		n_rx_nodesc_trunc += channel->n_rx_nodesc_trunc;
	stats[GENERIC_STAT_rx_nodesc_trunc] = n_rx_nodesc_trunc;
	stats[GENERIC_STAT_rx_noskb_drops] = atomic_पढ़ो(&efx->n_rx_noskb_drops);
पूर्ण

/**************************************************************************
 *
 * PCI पूर्णांकerface
 *
 **************************************************************************/

/* Main body of final NIC shutकरोwn code
 * This is called only at module unload (or hotplug removal).
 */
अटल व्योम efx_pci_हटाओ_मुख्य(काष्ठा efx_nic *efx)
अणु
	/* Flush reset_work. It can no दीर्घer be scheduled since we
	 * are not READY.
	 */
	BUG_ON(efx->state == STATE_READY);
	efx_flush_reset_workqueue(efx);

	efx_disable_पूर्णांकerrupts(efx);
	efx_clear_पूर्णांकerrupt_affinity(efx);
	efx_nic_fini_पूर्णांकerrupt(efx);
	efx_fini_port(efx);
	efx->type->fini(efx);
	efx_fini_napi(efx);
	efx_हटाओ_all(efx);
पूर्ण

/* Final NIC shutकरोwn
 * This is called only at module unload (or hotplug removal).  A PF can call
 * this on its VFs to ensure they are unbound first.
 */
अटल व्योम efx_pci_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा efx_nic *efx;

	efx = pci_get_drvdata(pci_dev);
	अगर (!efx)
		वापस;

	/* Mark the NIC as fini, then stop the पूर्णांकerface */
	rtnl_lock();
	efx_dissociate(efx);
	dev_बंद(efx->net_dev);
	efx_disable_पूर्णांकerrupts(efx);
	efx->state = STATE_UNINIT;
	rtnl_unlock();

	अगर (efx->type->sriov_fini)
		efx->type->sriov_fini(efx);

	efx_unरेजिस्टर_netdev(efx);

	efx_mtd_हटाओ(efx);

	efx_pci_हटाओ_मुख्य(efx);

	efx_fini_io(efx);
	netअगर_dbg(efx, drv, efx->net_dev, "shutdown successful\n");

	efx_fini_काष्ठा(efx);
	मुक्त_netdev(efx->net_dev);

	pci_disable_pcie_error_reporting(pci_dev);
पूर्ण;

/* NIC VPD inक्रमmation
 * Called during probe to display the part number of the
 * installed NIC.  VPD is potentially very large but this should
 * always appear within the first 512 bytes.
 */
#घोषणा SFC_VPD_LEN 512
अटल व्योम efx_probe_vpd_strings(काष्ठा efx_nic *efx)
अणु
	काष्ठा pci_dev *dev = efx->pci_dev;
	अक्षर vpd_data[SFC_VPD_LEN];
	sमाप_प्रकार vpd_size;
	पूर्णांक ro_start, ro_size, i, j;

	/* Get the vpd data from the device */
	vpd_size = pci_पढ़ो_vpd(dev, 0, माप(vpd_data), vpd_data);
	अगर (vpd_size <= 0) अणु
		netअगर_err(efx, drv, efx->net_dev, "Unable to read VPD\n");
		वापस;
	पूर्ण

	/* Get the Read only section */
	ro_start = pci_vpd_find_tag(vpd_data, vpd_size, PCI_VPD_LRDT_RO_DATA);
	अगर (ro_start < 0) अणु
		netअगर_err(efx, drv, efx->net_dev, "VPD Read-only not found\n");
		वापस;
	पूर्ण

	ro_size = pci_vpd_lrdt_size(&vpd_data[ro_start]);
	j = ro_size;
	i = ro_start + PCI_VPD_LRDT_TAG_SIZE;
	अगर (i + j > vpd_size)
		j = vpd_size - i;

	/* Get the Part number */
	i = pci_vpd_find_info_keyword(vpd_data, i, j, "PN");
	अगर (i < 0) अणु
		netअगर_err(efx, drv, efx->net_dev, "Part number not found\n");
		वापस;
	पूर्ण

	j = pci_vpd_info_field_size(&vpd_data[i]);
	i += PCI_VPD_INFO_FLD_HDR_SIZE;
	अगर (i + j > vpd_size) अणु
		netअगर_err(efx, drv, efx->net_dev, "Incomplete part number\n");
		वापस;
	पूर्ण

	netअगर_info(efx, drv, efx->net_dev,
		   "Part Number : %.*s\n", j, &vpd_data[i]);

	i = ro_start + PCI_VPD_LRDT_TAG_SIZE;
	j = ro_size;
	i = pci_vpd_find_info_keyword(vpd_data, i, j, "SN");
	अगर (i < 0) अणु
		netअगर_err(efx, drv, efx->net_dev, "Serial number not found\n");
		वापस;
	पूर्ण

	j = pci_vpd_info_field_size(&vpd_data[i]);
	i += PCI_VPD_INFO_FLD_HDR_SIZE;
	अगर (i + j > vpd_size) अणु
		netअगर_err(efx, drv, efx->net_dev, "Incomplete serial number\n");
		वापस;
	पूर्ण

	efx->vpd_sn = kदो_स्मृति(j + 1, GFP_KERNEL);
	अगर (!efx->vpd_sn)
		वापस;

	snम_लिखो(efx->vpd_sn, j + 1, "%s", &vpd_data[i]);
पूर्ण


/* Main body of NIC initialisation
 * This is called at module load (or hotplug insertion, theoretically).
 */
अटल पूर्णांक efx_pci_probe_मुख्य(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	/* Do start-of-day initialisation */
	rc = efx_probe_all(efx);
	अगर (rc)
		जाओ fail1;

	efx_init_napi(efx);

	करोwn_ग_लिखो(&efx->filter_sem);
	rc = efx->type->init(efx);
	up_ग_लिखो(&efx->filter_sem);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "failed to initialise NIC\n");
		जाओ fail3;
	पूर्ण

	rc = efx_init_port(efx);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "failed to initialise port\n");
		जाओ fail4;
	पूर्ण

	rc = efx_nic_init_पूर्णांकerrupt(efx);
	अगर (rc)
		जाओ fail5;

	efx_set_पूर्णांकerrupt_affinity(efx);
	rc = efx_enable_पूर्णांकerrupts(efx);
	अगर (rc)
		जाओ fail6;

	वापस 0;

 fail6:
	efx_clear_पूर्णांकerrupt_affinity(efx);
	efx_nic_fini_पूर्णांकerrupt(efx);
 fail5:
	efx_fini_port(efx);
 fail4:
	efx->type->fini(efx);
 fail3:
	efx_fini_napi(efx);
	efx_हटाओ_all(efx);
 fail1:
	वापस rc;
पूर्ण

अटल पूर्णांक efx_pci_probe_post_io(काष्ठा efx_nic *efx)
अणु
	काष्ठा net_device *net_dev = efx->net_dev;
	पूर्णांक rc = efx_pci_probe_मुख्य(efx);

	अगर (rc)
		वापस rc;

	अगर (efx->type->sriov_init) अणु
		rc = efx->type->sriov_init(efx);
		अगर (rc)
			netअगर_err(efx, probe, efx->net_dev,
				  "SR-IOV can't be enabled rc %d\n", rc);
	पूर्ण

	/* Determine netdevice features */
	net_dev->features |= (efx->type->offload_features | NETIF_F_SG |
			      NETIF_F_TSO | NETIF_F_RXCSUM | NETIF_F_RXALL);
	अगर (efx->type->offload_features & (NETIF_F_IPV6_CSUM | NETIF_F_HW_CSUM))
		net_dev->features |= NETIF_F_TSO6;
	/* Check whether device supports TSO */
	अगर (!efx->type->tso_versions || !efx->type->tso_versions(efx))
		net_dev->features &= ~NETIF_F_ALL_TSO;
	/* Mask क्रम features that also apply to VLAN devices */
	net_dev->vlan_features |= (NETIF_F_HW_CSUM | NETIF_F_SG |
				   NETIF_F_HIGHDMA | NETIF_F_ALL_TSO |
				   NETIF_F_RXCSUM);

	net_dev->hw_features |= net_dev->features & ~efx->fixed_features;

	/* Disable receiving frames with bad FCS, by शेष. */
	net_dev->features &= ~NETIF_F_RXALL;

	/* Disable VLAN filtering by शेष.  It may be enक्रमced अगर
	 * the feature is fixed (i.e. VLAN filters are required to
	 * receive VLAN tagged packets due to vPort restrictions).
	 */
	net_dev->features &= ~NETIF_F_HW_VLAN_CTAG_FILTER;
	net_dev->features |= efx->fixed_features;

	rc = efx_रेजिस्टर_netdev(efx);
	अगर (!rc)
		वापस 0;

	efx_pci_हटाओ_मुख्य(efx);
	वापस rc;
पूर्ण

/* NIC initialisation
 *
 * This is called at module load (or hotplug insertion,
 * theoretically).  It sets up PCI mappings, resets the NIC,
 * sets up and रेजिस्टरs the network devices with the kernel and hooks
 * the पूर्णांकerrupt service routine.  It करोes not prepare the device क्रम
 * transmission; this is left to the first समय one of the network
 * पूर्णांकerfaces is brought up (i.e. efx_net_खोलो).
 */
अटल पूर्णांक efx_pci_probe(काष्ठा pci_dev *pci_dev,
			 स्थिर काष्ठा pci_device_id *entry)
अणु
	काष्ठा net_device *net_dev;
	काष्ठा efx_nic *efx;
	पूर्णांक rc;

	/* Allocate and initialise a काष्ठा net_device and काष्ठा efx_nic */
	net_dev = alloc_etherdev_mqs(माप(*efx), EFX_MAX_CORE_TX_QUEUES,
				     EFX_MAX_RX_QUEUES);
	अगर (!net_dev)
		वापस -ENOMEM;
	efx = netdev_priv(net_dev);
	efx->type = (स्थिर काष्ठा efx_nic_type *) entry->driver_data;
	efx->fixed_features |= NETIF_F_HIGHDMA;

	pci_set_drvdata(pci_dev, efx);
	SET_NETDEV_DEV(net_dev, &pci_dev->dev);
	rc = efx_init_काष्ठा(efx, pci_dev, net_dev);
	अगर (rc)
		जाओ fail1;

	netअगर_info(efx, probe, efx->net_dev,
		   "Solarflare NIC detected\n");

	अगर (!efx->type->is_vf)
		efx_probe_vpd_strings(efx);

	/* Set up basic I/O (BAR mappings etc) */
	rc = efx_init_io(efx, efx->type->mem_bar(efx), efx->type->max_dma_mask,
			 efx->type->mem_map_size(efx));
	अगर (rc)
		जाओ fail2;

	rc = efx_pci_probe_post_io(efx);
	अगर (rc) अणु
		/* On failure, retry once immediately.
		 * If we पातed probe due to a scheduled reset, dismiss it.
		 */
		efx->reset_pending = 0;
		rc = efx_pci_probe_post_io(efx);
		अगर (rc) अणु
			/* On another failure, retry once more
			 * after a 50-305ms delay.
			 */
			अचिन्हित अक्षर r;

			get_अक्रमom_bytes(&r, 1);
			msleep((अचिन्हित पूर्णांक)r + 50);
			efx->reset_pending = 0;
			rc = efx_pci_probe_post_io(efx);
		पूर्ण
	पूर्ण
	अगर (rc)
		जाओ fail3;

	netअगर_dbg(efx, probe, efx->net_dev, "initialisation successful\n");

	/* Try to create MTDs, but allow this to fail */
	rtnl_lock();
	rc = efx_mtd_probe(efx);
	rtnl_unlock();
	अगर (rc && rc != -EPERM)
		netअगर_warn(efx, probe, efx->net_dev,
			   "failed to create MTDs (%d)\n", rc);

	(व्योम)pci_enable_pcie_error_reporting(pci_dev);

	अगर (efx->type->udp_tnl_push_ports)
		efx->type->udp_tnl_push_ports(efx);

	वापस 0;

 fail3:
	efx_fini_io(efx);
 fail2:
	efx_fini_काष्ठा(efx);
 fail1:
	WARN_ON(rc > 0);
	netअगर_dbg(efx, drv, efx->net_dev, "initialisation failed. rc=%d\n", rc);
	मुक्त_netdev(net_dev);
	वापस rc;
पूर्ण

/* efx_pci_sriov_configure वापसs the actual number of Virtual Functions
 * enabled on success
 */
#अगर_घोषित CONFIG_SFC_SRIOV
अटल पूर्णांक efx_pci_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक num_vfs)
अणु
	पूर्णांक rc;
	काष्ठा efx_nic *efx = pci_get_drvdata(dev);

	अगर (efx->type->sriov_configure) अणु
		rc = efx->type->sriov_configure(efx, num_vfs);
		अगर (rc)
			वापस rc;
		अन्यथा
			वापस num_vfs;
	पूर्ण अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक efx_pm_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा efx_nic *efx = dev_get_drvdata(dev);

	rtnl_lock();

	अगर (efx->state != STATE_DISABLED) अणु
		efx->state = STATE_UNINIT;

		efx_device_detach_sync(efx);

		efx_stop_all(efx);
		efx_disable_पूर्णांकerrupts(efx);
	पूर्ण

	rtnl_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक efx_pm_thaw(काष्ठा device *dev)
अणु
	पूर्णांक rc;
	काष्ठा efx_nic *efx = dev_get_drvdata(dev);

	rtnl_lock();

	अगर (efx->state != STATE_DISABLED) अणु
		rc = efx_enable_पूर्णांकerrupts(efx);
		अगर (rc)
			जाओ fail;

		mutex_lock(&efx->mac_lock);
		efx_mcdi_port_reconfigure(efx);
		mutex_unlock(&efx->mac_lock);

		efx_start_all(efx);

		efx_device_attach_अगर_not_resetting(efx);

		efx->state = STATE_READY;

		efx->type->resume_wol(efx);
	पूर्ण

	rtnl_unlock();

	/* Reschedule any quenched resets scheduled during efx_pm_मुक्तze() */
	efx_queue_reset_work(efx);

	वापस 0;

fail:
	rtnl_unlock();

	वापस rc;
पूर्ण

अटल पूर्णांक efx_pm_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा efx_nic *efx = pci_get_drvdata(pci_dev);

	efx->type->fini(efx);

	efx->reset_pending = 0;

	pci_save_state(pci_dev);
	वापस pci_set_घातer_state(pci_dev, PCI_D3hot);
पूर्ण

/* Used क्रम both resume and restore */
अटल पूर्णांक efx_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev);
	काष्ठा efx_nic *efx = pci_get_drvdata(pci_dev);
	पूर्णांक rc;

	rc = pci_set_घातer_state(pci_dev, PCI_D0);
	अगर (rc)
		वापस rc;
	pci_restore_state(pci_dev);
	rc = pci_enable_device(pci_dev);
	अगर (rc)
		वापस rc;
	pci_set_master(efx->pci_dev);
	rc = efx->type->reset(efx, RESET_TYPE_ALL);
	अगर (rc)
		वापस rc;
	करोwn_ग_लिखो(&efx->filter_sem);
	rc = efx->type->init(efx);
	up_ग_लिखो(&efx->filter_sem);
	अगर (rc)
		वापस rc;
	rc = efx_pm_thaw(dev);
	वापस rc;
पूर्ण

अटल पूर्णांक efx_pm_suspend(काष्ठा device *dev)
अणु
	पूर्णांक rc;

	efx_pm_मुक्तze(dev);
	rc = efx_pm_घातeroff(dev);
	अगर (rc)
		efx_pm_resume(dev);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops efx_pm_ops = अणु
	.suspend	= efx_pm_suspend,
	.resume		= efx_pm_resume,
	.मुक्तze		= efx_pm_मुक्तze,
	.thaw		= efx_pm_thaw,
	.घातeroff	= efx_pm_घातeroff,
	.restore	= efx_pm_resume,
पूर्ण;

अटल काष्ठा pci_driver efx_pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= efx_pci_table,
	.probe		= efx_pci_probe,
	.हटाओ		= efx_pci_हटाओ,
	.driver.pm	= &efx_pm_ops,
	.err_handler	= &efx_err_handlers,
#अगर_घोषित CONFIG_SFC_SRIOV
	.sriov_configure = efx_pci_sriov_configure,
#पूर्ण_अगर
पूर्ण;

/**************************************************************************
 *
 * Kernel module पूर्णांकerface
 *
 *************************************************************************/

अटल पूर्णांक __init efx_init_module(व्योम)
अणु
	पूर्णांक rc;

	prपूर्णांकk(KERN_INFO "Solarflare NET driver\n");

	rc = रेजिस्टर_netdevice_notअगरier(&efx_netdev_notअगरier);
	अगर (rc)
		जाओ err_notअगरier;

#अगर_घोषित CONFIG_SFC_SRIOV
	rc = efx_init_sriov();
	अगर (rc)
		जाओ err_sriov;
#पूर्ण_अगर

	rc = efx_create_reset_workqueue();
	अगर (rc)
		जाओ err_reset;

	rc = pci_रेजिस्टर_driver(&efx_pci_driver);
	अगर (rc < 0)
		जाओ err_pci;

	rc = pci_रेजिस्टर_driver(&ef100_pci_driver);
	अगर (rc < 0)
		जाओ err_pci_ef100;

	वापस 0;

 err_pci_ef100:
	pci_unरेजिस्टर_driver(&efx_pci_driver);
 err_pci:
	efx_destroy_reset_workqueue();
 err_reset:
#अगर_घोषित CONFIG_SFC_SRIOV
	efx_fini_sriov();
 err_sriov:
#पूर्ण_अगर
	unरेजिस्टर_netdevice_notअगरier(&efx_netdev_notअगरier);
 err_notअगरier:
	वापस rc;
पूर्ण

अटल व्योम __निकास efx_निकास_module(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "Solarflare NET driver unloading\n");

	pci_unरेजिस्टर_driver(&ef100_pci_driver);
	pci_unरेजिस्टर_driver(&efx_pci_driver);
	efx_destroy_reset_workqueue();
#अगर_घोषित CONFIG_SFC_SRIOV
	efx_fini_sriov();
#पूर्ण_अगर
	unरेजिस्टर_netdevice_notअगरier(&efx_netdev_notअगरier);

पूर्ण

module_init(efx_init_module);
module_निकास(efx_निकास_module);

MODULE_AUTHOR("Solarflare Communications and "
	      "Michael Brown <mbrown@fensystems.co.uk>");
MODULE_DESCRIPTION("Solarflare network driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, efx_pci_table);
