<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <linux/etherdevice.h>
#समावेश <linux/io-64-nonatomic-hi-lo.h>
#समावेश <linux/lockdep.h>
#समावेश <net/dst_metadata.h>

#समावेश "nfpcore/nfp_cpp.h"
#समावेश "nfpcore/nfp_nsp.h"
#समावेश "nfp_app.h"
#समावेश "nfp_main.h"
#समावेश "nfp_net.h"
#समावेश "nfp_net_ctrl.h"
#समावेश "nfp_net_repr.h"
#समावेश "nfp_net_sriov.h"
#समावेश "nfp_port.h"

काष्ठा net_device *
nfp_repr_get_locked(काष्ठा nfp_app *app, काष्ठा nfp_reprs *set, अचिन्हित पूर्णांक id)
अणु
	वापस rcu_dereference_रक्षित(set->reprs[id],
					 lockdep_is_held(&app->pf->lock));
पूर्ण

अटल व्योम
nfp_repr_inc_tx_stats(काष्ठा net_device *netdev, अचिन्हित पूर्णांक len,
		      पूर्णांक tx_status)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);
	काष्ठा nfp_repr_pcpu_stats *stats;

	अगर (unlikely(tx_status != NET_XMIT_SUCCESS &&
		     tx_status != NET_XMIT_CN)) अणु
		this_cpu_inc(repr->stats->tx_drops);
		वापस;
	पूर्ण

	stats = this_cpu_ptr(repr->stats);
	u64_stats_update_begin(&stats->syncp);
	stats->tx_packets++;
	stats->tx_bytes += len;
	u64_stats_update_end(&stats->syncp);
पूर्ण

व्योम nfp_repr_inc_rx_stats(काष्ठा net_device *netdev, अचिन्हित पूर्णांक len)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);
	काष्ठा nfp_repr_pcpu_stats *stats;

	stats = this_cpu_ptr(repr->stats);
	u64_stats_update_begin(&stats->syncp);
	stats->rx_packets++;
	stats->rx_bytes += len;
	u64_stats_update_end(&stats->syncp);
पूर्ण

अटल व्योम
nfp_repr_phy_port_get_stats64(काष्ठा nfp_port *port,
			      काष्ठा rtnl_link_stats64 *stats)
अणु
	u8 __iomem *mem = port->eth_stats;

	stats->tx_packets = पढ़ोq(mem + NFP_MAC_STATS_TX_FRAMES_TRANSMITTED_OK);
	stats->tx_bytes = पढ़ोq(mem + NFP_MAC_STATS_TX_OUT_OCTETS);
	stats->tx_dropped = पढ़ोq(mem + NFP_MAC_STATS_TX_OUT_ERRORS);

	stats->rx_packets = पढ़ोq(mem + NFP_MAC_STATS_RX_FRAMES_RECEIVED_OK);
	stats->rx_bytes = पढ़ोq(mem + NFP_MAC_STATS_RX_IN_OCTETS);
	stats->rx_dropped = पढ़ोq(mem + NFP_MAC_STATS_RX_IN_ERRORS);
पूर्ण

अटल व्योम
nfp_repr_vnic_get_stats64(काष्ठा nfp_port *port,
			  काष्ठा rtnl_link_stats64 *stats)
अणु
	/* TX and RX stats are flipped as we are वापसing the stats as seen
	 * at the चयन port corresponding to the VF.
	 */
	stats->tx_packets = पढ़ोq(port->vnic + NFP_NET_CFG_STATS_RX_FRAMES);
	stats->tx_bytes = पढ़ोq(port->vnic + NFP_NET_CFG_STATS_RX_OCTETS);
	stats->tx_dropped = पढ़ोq(port->vnic + NFP_NET_CFG_STATS_RX_DISCARDS);

	stats->rx_packets = पढ़ोq(port->vnic + NFP_NET_CFG_STATS_TX_FRAMES);
	stats->rx_bytes = पढ़ोq(port->vnic + NFP_NET_CFG_STATS_TX_OCTETS);
	stats->rx_dropped = पढ़ोq(port->vnic + NFP_NET_CFG_STATS_TX_DISCARDS);
पूर्ण

अटल व्योम
nfp_repr_get_stats64(काष्ठा net_device *netdev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);

	अगर (WARN_ON(!repr->port))
		वापस;

	चयन (repr->port->type) अणु
	हाल NFP_PORT_PHYS_PORT:
		अगर (!__nfp_port_get_eth_port(repr->port))
			अवरोध;
		nfp_repr_phy_port_get_stats64(repr->port, stats);
		अवरोध;
	हाल NFP_PORT_PF_PORT:
	हाल NFP_PORT_VF_PORT:
		nfp_repr_vnic_get_stats64(repr->port, stats);
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल bool
nfp_repr_has_offload_stats(स्थिर काष्ठा net_device *dev, पूर्णांक attr_id)
अणु
	चयन (attr_id) अणु
	हाल IFLA_OFFLOAD_XSTATS_CPU_HIT:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक
nfp_repr_get_host_stats64(स्थिर काष्ठा net_device *netdev,
			  काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		u64 tbytes, tpkts, tdrops, rbytes, rpkts;
		काष्ठा nfp_repr_pcpu_stats *repr_stats;
		अचिन्हित पूर्णांक start;

		repr_stats = per_cpu_ptr(repr->stats, i);
		करो अणु
			start = u64_stats_fetch_begin_irq(&repr_stats->syncp);
			tbytes = repr_stats->tx_bytes;
			tpkts = repr_stats->tx_packets;
			tdrops = repr_stats->tx_drops;
			rbytes = repr_stats->rx_bytes;
			rpkts = repr_stats->rx_packets;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&repr_stats->syncp, start));

		stats->tx_bytes += tbytes;
		stats->tx_packets += tpkts;
		stats->tx_dropped += tdrops;
		stats->rx_bytes += rbytes;
		stats->rx_packets += rpkts;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_repr_get_offload_stats(पूर्णांक attr_id, स्थिर काष्ठा net_device *dev,
			   व्योम *stats)
अणु
	चयन (attr_id) अणु
	हाल IFLA_OFFLOAD_XSTATS_CPU_HIT:
		वापस nfp_repr_get_host_stats64(dev, stats);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक nfp_repr_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);
	पूर्णांक err;

	err = nfp_app_check_mtu(repr->app, netdev, new_mtu);
	अगर (err)
		वापस err;

	err = nfp_app_repr_change_mtu(repr->app, netdev, new_mtu);
	अगर (err)
		वापस err;

	netdev->mtu = new_mtu;

	वापस 0;
पूर्ण

अटल netdev_tx_t nfp_repr_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);
	अचिन्हित पूर्णांक len = skb->len;
	पूर्णांक ret;

	skb_dst_drop(skb);
	dst_hold((काष्ठा dst_entry *)repr->dst);
	skb_dst_set(skb, (काष्ठा dst_entry *)repr->dst);
	skb->dev = repr->dst->u.port_info.lower_dev;

	ret = dev_queue_xmit(skb);
	nfp_repr_inc_tx_stats(netdev, len, ret);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक nfp_repr_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);
	पूर्णांक err;

	err = nfp_app_repr_stop(repr->app, repr);
	अगर (err)
		वापस err;

	nfp_port_configure(netdev, false);
	वापस 0;
पूर्ण

अटल पूर्णांक nfp_repr_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);
	पूर्णांक err;

	err = nfp_port_configure(netdev, true);
	अगर (err)
		वापस err;

	err = nfp_app_repr_खोलो(repr->app, repr);
	अगर (err)
		जाओ err_port_disable;

	वापस 0;

err_port_disable:
	nfp_port_configure(netdev, false);
	वापस err;
पूर्ण

अटल netdev_features_t
nfp_repr_fix_features(काष्ठा net_device *netdev, netdev_features_t features)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);
	netdev_features_t old_features = features;
	netdev_features_t lower_features;
	काष्ठा net_device *lower_dev;

	lower_dev = repr->dst->u.port_info.lower_dev;

	lower_features = lower_dev->features;
	अगर (lower_features & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM))
		lower_features |= NETIF_F_HW_CSUM;

	features = netdev_पूर्णांकersect_features(features, lower_features);
	features |= old_features & (NETIF_F_SOFT_FEATURES | NETIF_F_HW_TC);
	features |= NETIF_F_LLTX;

	वापस features;
पूर्ण

स्थिर काष्ठा net_device_ops nfp_repr_netdev_ops = अणु
	.nकरो_init		= nfp_app_nकरो_init,
	.nकरो_uninit		= nfp_app_nकरो_uninit,
	.nकरो_खोलो		= nfp_repr_खोलो,
	.nकरो_stop		= nfp_repr_stop,
	.nकरो_start_xmit		= nfp_repr_xmit,
	.nकरो_change_mtu		= nfp_repr_change_mtu,
	.nकरो_get_stats64	= nfp_repr_get_stats64,
	.nकरो_has_offload_stats	= nfp_repr_has_offload_stats,
	.nकरो_get_offload_stats	= nfp_repr_get_offload_stats,
	.nकरो_get_phys_port_name	= nfp_port_get_phys_port_name,
	.nकरो_setup_tc		= nfp_port_setup_tc,
	.nकरो_set_vf_mac		= nfp_app_set_vf_mac,
	.nकरो_set_vf_vlan	= nfp_app_set_vf_vlan,
	.nकरो_set_vf_spoofchk	= nfp_app_set_vf_spoofchk,
	.nकरो_set_vf_trust	= nfp_app_set_vf_trust,
	.nकरो_get_vf_config	= nfp_app_get_vf_config,
	.nकरो_set_vf_link_state	= nfp_app_set_vf_link_state,
	.nकरो_fix_features	= nfp_repr_fix_features,
	.nकरो_set_features	= nfp_port_set_features,
	.nकरो_set_mac_address    = eth_mac_addr,
	.nकरो_get_port_parent_id	= nfp_port_get_port_parent_id,
	.nकरो_get_devlink_port	= nfp_devlink_get_devlink_port,
पूर्ण;

व्योम
nfp_repr_transfer_features(काष्ठा net_device *netdev, काष्ठा net_device *lower)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);

	अगर (repr->dst->u.port_info.lower_dev != lower)
		वापस;

	netdev->gso_max_size = lower->gso_max_size;
	netdev->gso_max_segs = lower->gso_max_segs;

	netdev_update_features(netdev);
पूर्ण

अटल व्योम nfp_repr_clean(काष्ठा nfp_repr *repr)
अणु
	unरेजिस्टर_netdev(repr->netdev);
	nfp_app_repr_clean(repr->app, repr->netdev);
	dst_release((काष्ठा dst_entry *)repr->dst);
	nfp_port_मुक्त(repr->port);
पूर्ण

अटल काष्ठा lock_class_key nfp_repr_netdev_xmit_lock_key;

अटल व्योम nfp_repr_set_lockdep_class_one(काष्ठा net_device *dev,
					   काष्ठा netdev_queue *txq,
					   व्योम *_unused)
अणु
	lockdep_set_class(&txq->_xmit_lock, &nfp_repr_netdev_xmit_lock_key);
पूर्ण

अटल व्योम nfp_repr_set_lockdep_class(काष्ठा net_device *dev)
अणु
	netdev_क्रम_each_tx_queue(dev, nfp_repr_set_lockdep_class_one, शून्य);
पूर्ण

पूर्णांक nfp_repr_init(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
		  u32 cmsg_port_id, काष्ठा nfp_port *port,
		  काष्ठा net_device *pf_netdev)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);
	काष्ठा nfp_net *nn = netdev_priv(pf_netdev);
	u32 repr_cap = nn->tlv_caps.repr_cap;
	पूर्णांक err;

	nfp_repr_set_lockdep_class(netdev);

	repr->port = port;
	repr->dst = metadata_dst_alloc(0, METADATA_HW_PORT_MUX, GFP_KERNEL);
	अगर (!repr->dst)
		वापस -ENOMEM;
	repr->dst->u.port_info.port_id = cmsg_port_id;
	repr->dst->u.port_info.lower_dev = pf_netdev;

	netdev->netdev_ops = &nfp_repr_netdev_ops;
	netdev->ethtool_ops = &nfp_port_ethtool_ops;

	netdev->max_mtu = pf_netdev->max_mtu;

	/* Set features the lower device can support with representors */
	अगर (repr_cap & NFP_NET_CFG_CTRL_LIVE_ADDR)
		netdev->priv_flags |= IFF_LIVE_ADDR_CHANGE;

	netdev->hw_features = NETIF_F_HIGHDMA;
	अगर (repr_cap & NFP_NET_CFG_CTRL_RXCSUM_ANY)
		netdev->hw_features |= NETIF_F_RXCSUM;
	अगर (repr_cap & NFP_NET_CFG_CTRL_TXCSUM)
		netdev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	अगर (repr_cap & NFP_NET_CFG_CTRL_GATHER)
		netdev->hw_features |= NETIF_F_SG;
	अगर ((repr_cap & NFP_NET_CFG_CTRL_LSO && nn->fw_ver.major > 2) ||
	    repr_cap & NFP_NET_CFG_CTRL_LSO2)
		netdev->hw_features |= NETIF_F_TSO | NETIF_F_TSO6;
	अगर (repr_cap & NFP_NET_CFG_CTRL_RSS_ANY)
		netdev->hw_features |= NETIF_F_RXHASH;
	अगर (repr_cap & NFP_NET_CFG_CTRL_VXLAN) अणु
		अगर (repr_cap & NFP_NET_CFG_CTRL_LSO)
			netdev->hw_features |= NETIF_F_GSO_UDP_TUNNEL;
	पूर्ण
	अगर (repr_cap & NFP_NET_CFG_CTRL_NVGRE) अणु
		अगर (repr_cap & NFP_NET_CFG_CTRL_LSO)
			netdev->hw_features |= NETIF_F_GSO_GRE;
	पूर्ण
	अगर (repr_cap & (NFP_NET_CFG_CTRL_VXLAN | NFP_NET_CFG_CTRL_NVGRE))
		netdev->hw_enc_features = netdev->hw_features;

	netdev->vlan_features = netdev->hw_features;

	अगर (repr_cap & NFP_NET_CFG_CTRL_RXVLAN)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_RX;
	अगर (repr_cap & NFP_NET_CFG_CTRL_TXVLAN) अणु
		अगर (repr_cap & NFP_NET_CFG_CTRL_LSO2)
			netdev_warn(netdev, "Device advertises both TSO2 and TXVLAN. Refusing to enable TXVLAN.\n");
		अन्यथा
			netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_TX;
	पूर्ण
	अगर (repr_cap & NFP_NET_CFG_CTRL_CTAG_FILTER)
		netdev->hw_features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	netdev->features = netdev->hw_features;

	/* Advertise but disable TSO by शेष. */
	netdev->features &= ~(NETIF_F_TSO | NETIF_F_TSO6);
	netdev->gso_max_segs = NFP_NET_LSO_MAX_SEGS;

	netdev->priv_flags |= IFF_NO_QUEUE | IFF_DISABLE_NETPOLL;
	netdev->features |= NETIF_F_LLTX;

	अगर (nfp_app_has_tc(app)) अणु
		netdev->features |= NETIF_F_HW_TC;
		netdev->hw_features |= NETIF_F_HW_TC;
	पूर्ण

	err = nfp_app_repr_init(app, netdev);
	अगर (err)
		जाओ err_clean;

	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_repr_clean;

	वापस 0;

err_repr_clean:
	nfp_app_repr_clean(app, netdev);
err_clean:
	dst_release((काष्ठा dst_entry *)repr->dst);
	वापस err;
पूर्ण

अटल व्योम __nfp_repr_मुक्त(काष्ठा nfp_repr *repr)
अणु
	मुक्त_percpu(repr->stats);
	मुक्त_netdev(repr->netdev);
पूर्ण

व्योम nfp_repr_मुक्त(काष्ठा net_device *netdev)
अणु
	__nfp_repr_मुक्त(netdev_priv(netdev));
पूर्ण

काष्ठा net_device *
nfp_repr_alloc_mqs(काष्ठा nfp_app *app, अचिन्हित पूर्णांक txqs, अचिन्हित पूर्णांक rxqs)
अणु
	काष्ठा net_device *netdev;
	काष्ठा nfp_repr *repr;

	netdev = alloc_etherdev_mqs(माप(*repr), txqs, rxqs);
	अगर (!netdev)
		वापस शून्य;

	netअगर_carrier_off(netdev);

	repr = netdev_priv(netdev);
	repr->netdev = netdev;
	repr->app = app;

	repr->stats = netdev_alloc_pcpu_stats(काष्ठा nfp_repr_pcpu_stats);
	अगर (!repr->stats)
		जाओ err_मुक्त_netdev;

	वापस netdev;

err_मुक्त_netdev:
	मुक्त_netdev(netdev);
	वापस शून्य;
पूर्ण

व्योम nfp_repr_clean_and_मुक्त(काष्ठा nfp_repr *repr)
अणु
	nfp_info(repr->app->cpp, "Destroying Representor(%s)\n",
		 repr->netdev->name);
	nfp_repr_clean(repr);
	__nfp_repr_मुक्त(repr);
पूर्ण

व्योम nfp_reprs_clean_and_मुक्त(काष्ठा nfp_app *app, काष्ठा nfp_reprs *reprs)
अणु
	काष्ठा net_device *netdev;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < reprs->num_reprs; i++) अणु
		netdev = nfp_repr_get_locked(app, reprs, i);
		अगर (netdev)
			nfp_repr_clean_and_मुक्त(netdev_priv(netdev));
	पूर्ण

	kमुक्त(reprs);
पूर्ण

व्योम
nfp_reprs_clean_and_मुक्त_by_type(काष्ठा nfp_app *app, क्रमागत nfp_repr_type type)
अणु
	काष्ठा net_device *netdev;
	काष्ठा nfp_reprs *reprs;
	पूर्णांक i;

	reprs = rcu_dereference_रक्षित(app->reprs[type],
					  lockdep_is_held(&app->pf->lock));
	अगर (!reprs)
		वापस;

	/* Preclean must happen beक्रमe we हटाओ the reprs reference from the
	 * app below.
	 */
	क्रम (i = 0; i < reprs->num_reprs; i++) अणु
		netdev = nfp_repr_get_locked(app, reprs, i);
		अगर (netdev)
			nfp_app_repr_preclean(app, netdev);
	पूर्ण

	reprs = nfp_app_reprs_set(app, type, शून्य);

	synchronize_rcu();
	nfp_reprs_clean_and_मुक्त(app, reprs);
पूर्ण

काष्ठा nfp_reprs *nfp_reprs_alloc(अचिन्हित पूर्णांक num_reprs)
अणु
	काष्ठा nfp_reprs *reprs;

	reprs = kzalloc(माप(*reprs) +
			num_reprs * माप(काष्ठा net_device *), GFP_KERNEL);
	अगर (!reprs)
		वापस शून्य;
	reprs->num_reprs = num_reprs;

	वापस reprs;
पूर्ण

पूर्णांक nfp_reprs_resync_phys_ports(काष्ठा nfp_app *app)
अणु
	काष्ठा net_device *netdev;
	काष्ठा nfp_reprs *reprs;
	काष्ठा nfp_repr *repr;
	पूर्णांक i;

	reprs = nfp_reprs_get_locked(app, NFP_REPR_TYPE_PHYS_PORT);
	अगर (!reprs)
		वापस 0;

	क्रम (i = 0; i < reprs->num_reprs; i++) अणु
		netdev = nfp_repr_get_locked(app, reprs, i);
		अगर (!netdev)
			जारी;

		repr = netdev_priv(netdev);
		अगर (repr->port->type != NFP_PORT_INVALID)
			जारी;

		nfp_app_repr_preclean(app, netdev);
		rtnl_lock();
		rcu_assign_poपूर्णांकer(reprs->reprs[i], शून्य);
		rtnl_unlock();
		synchronize_rcu();
		nfp_repr_clean(repr);
	पूर्ण

	वापस 0;
पूर्ण
