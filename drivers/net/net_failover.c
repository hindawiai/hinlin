<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Intel Corporation. */

/* This provides a net_failover पूर्णांकerface क्रम paraभव drivers to
 * provide an alternate datapath by exporting APIs to create and
 * destroy a upper 'net_failover' netdev. The upper dev manages the
 * original paraभव पूर्णांकerface as a 'standby' netdev and uses the
 * generic failover infraकाष्ठाure to रेजिस्टर and manage a direct
 * attached VF as a 'primary' netdev. This enables live migration of
 * a VM with direct attached VF by failing over to the paraभव
 * datapath when the VF is unplugged.
 *
 * Some of the netdev management routines are based on bond/team driver as
 * this driver provides active-backup functionality similar to those drivers.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/pci.h>
#समावेश <net/sch_generic.h>
#समावेश <uapi/linux/अगर_arp.h>
#समावेश <net/net_failover.h>

अटल bool net_failover_xmit_पढ़ोy(काष्ठा net_device *dev)
अणु
	वापस netअगर_running(dev) && netअगर_carrier_ok(dev);
पूर्ण

अटल पूर्णांक net_failover_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा net_failover_info *nfo_info = netdev_priv(dev);
	काष्ठा net_device *primary_dev, *standby_dev;
	पूर्णांक err;

	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	अगर (primary_dev) अणु
		err = dev_खोलो(primary_dev, शून्य);
		अगर (err)
			जाओ err_primary_खोलो;
	पूर्ण

	standby_dev = rtnl_dereference(nfo_info->standby_dev);
	अगर (standby_dev) अणु
		err = dev_खोलो(standby_dev, शून्य);
		अगर (err)
			जाओ err_standby_खोलो;
	पूर्ण

	अगर ((primary_dev && net_failover_xmit_पढ़ोy(primary_dev)) ||
	    (standby_dev && net_failover_xmit_पढ़ोy(standby_dev))) अणु
		netअगर_carrier_on(dev);
		netअगर_tx_wake_all_queues(dev);
	पूर्ण

	वापस 0;

err_standby_खोलो:
	अगर (primary_dev)
		dev_बंद(primary_dev);
err_primary_खोलो:
	netअगर_tx_disable(dev);
	वापस err;
पूर्ण

अटल पूर्णांक net_failover_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा net_failover_info *nfo_info = netdev_priv(dev);
	काष्ठा net_device *slave_dev;

	netअगर_tx_disable(dev);

	slave_dev = rtnl_dereference(nfo_info->primary_dev);
	अगर (slave_dev)
		dev_बंद(slave_dev);

	slave_dev = rtnl_dereference(nfo_info->standby_dev);
	अगर (slave_dev)
		dev_बंद(slave_dev);

	वापस 0;
पूर्ण

अटल netdev_tx_t net_failover_drop_xmit(काष्ठा sk_buff *skb,
					  काष्ठा net_device *dev)
अणु
	atomic_दीर्घ_inc(&dev->tx_dropped);
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल netdev_tx_t net_failover_start_xmit(काष्ठा sk_buff *skb,
					   काष्ठा net_device *dev)
अणु
	काष्ठा net_failover_info *nfo_info = netdev_priv(dev);
	काष्ठा net_device *xmit_dev;

	/* Try xmit via primary netdev followed by standby netdev */
	xmit_dev = rcu_dereference_bh(nfo_info->primary_dev);
	अगर (!xmit_dev || !net_failover_xmit_पढ़ोy(xmit_dev)) अणु
		xmit_dev = rcu_dereference_bh(nfo_info->standby_dev);
		अगर (!xmit_dev || !net_failover_xmit_पढ़ोy(xmit_dev))
			वापस net_failover_drop_xmit(skb, dev);
	पूर्ण

	skb->dev = xmit_dev;
	skb->queue_mapping = qdisc_skb_cb(skb)->slave_dev_queue_mapping;

	वापस dev_queue_xmit(skb);
पूर्ण

अटल u16 net_failover_select_queue(काष्ठा net_device *dev,
				     काष्ठा sk_buff *skb,
				     काष्ठा net_device *sb_dev)
अणु
	काष्ठा net_failover_info *nfo_info = netdev_priv(dev);
	काष्ठा net_device *primary_dev;
	u16 txq;

	primary_dev = rcu_dereference(nfo_info->primary_dev);
	अगर (primary_dev) अणु
		स्थिर काष्ठा net_device_ops *ops = primary_dev->netdev_ops;

		अगर (ops->nकरो_select_queue)
			txq = ops->nकरो_select_queue(primary_dev, skb, sb_dev);
		अन्यथा
			txq = netdev_pick_tx(primary_dev, skb, शून्य);

		qdisc_skb_cb(skb)->slave_dev_queue_mapping = skb->queue_mapping;

		वापस txq;
	पूर्ण

	txq = skb_rx_queue_recorded(skb) ? skb_get_rx_queue(skb) : 0;

	/* Save the original txq to restore beक्रमe passing to the driver */
	qdisc_skb_cb(skb)->slave_dev_queue_mapping = skb->queue_mapping;

	अगर (unlikely(txq >= dev->real_num_tx_queues)) अणु
		करो अणु
			txq -= dev->real_num_tx_queues;
		पूर्ण जबतक (txq >= dev->real_num_tx_queues);
	पूर्ण

	वापस txq;
पूर्ण

/* fold stats, assuming all rtnl_link_stats64 fields are u64, but
 * that some drivers can provide 32bit values only.
 */
अटल व्योम net_failover_fold_stats(काष्ठा rtnl_link_stats64 *_res,
				    स्थिर काष्ठा rtnl_link_stats64 *_new,
				    स्थिर काष्ठा rtnl_link_stats64 *_old)
अणु
	स्थिर u64 *new = (स्थिर u64 *)_new;
	स्थिर u64 *old = (स्थिर u64 *)_old;
	u64 *res = (u64 *)_res;
	पूर्णांक i;

	क्रम (i = 0; i < माप(*_res) / माप(u64); i++) अणु
		u64 nv = new[i];
		u64 ov = old[i];
		s64 delta = nv - ov;

		/* detects अगर this particular field is 32bit only */
		अगर (((nv | ov) >> 32) == 0)
			delta = (s64)(s32)((u32)nv - (u32)ov);

		/* filter anomalies, some drivers reset their stats
		 * at करोwn/up events.
		 */
		अगर (delta > 0)
			res[i] += delta;
	पूर्ण
पूर्ण

अटल व्योम net_failover_get_stats(काष्ठा net_device *dev,
				   काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा net_failover_info *nfo_info = netdev_priv(dev);
	स्थिर काष्ठा rtnl_link_stats64 *new;
	काष्ठा rtnl_link_stats64 temp;
	काष्ठा net_device *slave_dev;

	spin_lock(&nfo_info->stats_lock);
	स_नकल(stats, &nfo_info->failover_stats, माप(*stats));

	rcu_पढ़ो_lock();

	slave_dev = rcu_dereference(nfo_info->primary_dev);
	अगर (slave_dev) अणु
		new = dev_get_stats(slave_dev, &temp);
		net_failover_fold_stats(stats, new, &nfo_info->primary_stats);
		स_नकल(&nfo_info->primary_stats, new, माप(*new));
	पूर्ण

	slave_dev = rcu_dereference(nfo_info->standby_dev);
	अगर (slave_dev) अणु
		new = dev_get_stats(slave_dev, &temp);
		net_failover_fold_stats(stats, new, &nfo_info->standby_stats);
		स_नकल(&nfo_info->standby_stats, new, माप(*new));
	पूर्ण

	rcu_पढ़ो_unlock();

	स_नकल(&nfo_info->failover_stats, stats, माप(*stats));
	spin_unlock(&nfo_info->stats_lock);
पूर्ण

अटल पूर्णांक net_failover_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा net_failover_info *nfo_info = netdev_priv(dev);
	काष्ठा net_device *primary_dev, *standby_dev;
	पूर्णांक ret = 0;

	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	अगर (primary_dev) अणु
		ret = dev_set_mtu(primary_dev, new_mtu);
		अगर (ret)
			वापस ret;
	पूर्ण

	standby_dev = rtnl_dereference(nfo_info->standby_dev);
	अगर (standby_dev) अणु
		ret = dev_set_mtu(standby_dev, new_mtu);
		अगर (ret) अणु
			अगर (primary_dev)
				dev_set_mtu(primary_dev, dev->mtu);
			वापस ret;
		पूर्ण
	पूर्ण

	dev->mtu = new_mtu;

	वापस 0;
पूर्ण

अटल व्योम net_failover_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा net_failover_info *nfo_info = netdev_priv(dev);
	काष्ठा net_device *slave_dev;

	rcu_पढ़ो_lock();

	slave_dev = rcu_dereference(nfo_info->primary_dev);
	अगर (slave_dev) अणु
		dev_uc_sync_multiple(slave_dev, dev);
		dev_mc_sync_multiple(slave_dev, dev);
	पूर्ण

	slave_dev = rcu_dereference(nfo_info->standby_dev);
	अगर (slave_dev) अणु
		dev_uc_sync_multiple(slave_dev, dev);
		dev_mc_sync_multiple(slave_dev, dev);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक net_failover_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto,
					u16 vid)
अणु
	काष्ठा net_failover_info *nfo_info = netdev_priv(dev);
	काष्ठा net_device *primary_dev, *standby_dev;
	पूर्णांक ret = 0;

	primary_dev = rcu_dereference(nfo_info->primary_dev);
	अगर (primary_dev) अणु
		ret = vlan_vid_add(primary_dev, proto, vid);
		अगर (ret)
			वापस ret;
	पूर्ण

	standby_dev = rcu_dereference(nfo_info->standby_dev);
	अगर (standby_dev) अणु
		ret = vlan_vid_add(standby_dev, proto, vid);
		अगर (ret)
			अगर (primary_dev)
				vlan_vid_del(primary_dev, proto, vid);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक net_failover_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto,
					 u16 vid)
अणु
	काष्ठा net_failover_info *nfo_info = netdev_priv(dev);
	काष्ठा net_device *slave_dev;

	slave_dev = rcu_dereference(nfo_info->primary_dev);
	अगर (slave_dev)
		vlan_vid_del(slave_dev, proto, vid);

	slave_dev = rcu_dereference(nfo_info->standby_dev);
	अगर (slave_dev)
		vlan_vid_del(slave_dev, proto, vid);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops failover_dev_ops = अणु
	.nकरो_खोलो		= net_failover_खोलो,
	.nकरो_stop		= net_failover_बंद,
	.nकरो_start_xmit		= net_failover_start_xmit,
	.nकरो_select_queue	= net_failover_select_queue,
	.nकरो_get_stats64	= net_failover_get_stats,
	.nकरो_change_mtu		= net_failover_change_mtu,
	.nकरो_set_rx_mode	= net_failover_set_rx_mode,
	.nकरो_vlan_rx_add_vid	= net_failover_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= net_failover_vlan_rx_समाप्त_vid,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_features_check	= passthru_features_check,
पूर्ण;

#घोषणा FAILOVER_NAME "net_failover"
#घोषणा FAILOVER_VERSION "0.1"

अटल व्योम nfo_ethtool_get_drvinfo(काष्ठा net_device *dev,
				    काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, FAILOVER_NAME, माप(drvinfo->driver));
	strlcpy(drvinfo->version, FAILOVER_VERSION, माप(drvinfo->version));
पूर्ण

अटल पूर्णांक nfo_ethtool_get_link_ksettings(काष्ठा net_device *dev,
					  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा net_failover_info *nfo_info = netdev_priv(dev);
	काष्ठा net_device *slave_dev;

	slave_dev = rtnl_dereference(nfo_info->primary_dev);
	अगर (!slave_dev || !net_failover_xmit_पढ़ोy(slave_dev)) अणु
		slave_dev = rtnl_dereference(nfo_info->standby_dev);
		अगर (!slave_dev || !net_failover_xmit_पढ़ोy(slave_dev)) अणु
			cmd->base.duplex = DUPLEX_UNKNOWN;
			cmd->base.port = PORT_OTHER;
			cmd->base.speed = SPEED_UNKNOWN;

			वापस 0;
		पूर्ण
	पूर्ण

	वापस __ethtool_get_link_ksettings(slave_dev, cmd);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops failover_ethtool_ops = अणु
	.get_drvinfo            = nfo_ethtool_get_drvinfo,
	.get_link               = ethtool_op_get_link,
	.get_link_ksettings     = nfo_ethtool_get_link_ksettings,
पूर्ण;

/* Called when slave dev is injecting data पूर्णांकo network stack.
 * Change the associated network device from lower dev to failover dev.
 * note: alपढ़ोy called with rcu_पढ़ो_lock
 */
अटल rx_handler_result_t net_failover_handle_frame(काष्ठा sk_buff **pskb)
अणु
	काष्ठा sk_buff *skb = *pskb;
	काष्ठा net_device *dev = rcu_dereference(skb->dev->rx_handler_data);
	काष्ठा net_failover_info *nfo_info = netdev_priv(dev);
	काष्ठा net_device *primary_dev, *standby_dev;

	primary_dev = rcu_dereference(nfo_info->primary_dev);
	standby_dev = rcu_dereference(nfo_info->standby_dev);

	अगर (primary_dev && skb->dev == standby_dev)
		वापस RX_HANDLER_EXACT;

	skb->dev = dev;

	वापस RX_HANDLER_ANOTHER;
पूर्ण

अटल व्योम net_failover_compute_features(काष्ठा net_device *dev)
अणु
	netdev_features_t vlan_features = FAILOVER_VLAN_FEATURES &
					  NETIF_F_ALL_FOR_ALL;
	netdev_features_t enc_features  = FAILOVER_ENC_FEATURES;
	अचिन्हित लघु max_hard_header_len = ETH_HLEN;
	अचिन्हित पूर्णांक dst_release_flag = IFF_XMIT_DST_RELEASE |
					IFF_XMIT_DST_RELEASE_PERM;
	काष्ठा net_failover_info *nfo_info = netdev_priv(dev);
	काष्ठा net_device *primary_dev, *standby_dev;

	primary_dev = rcu_dereference(nfo_info->primary_dev);
	अगर (primary_dev) अणु
		vlan_features =
			netdev_increment_features(vlan_features,
						  primary_dev->vlan_features,
						  FAILOVER_VLAN_FEATURES);
		enc_features =
			netdev_increment_features(enc_features,
						  primary_dev->hw_enc_features,
						  FAILOVER_ENC_FEATURES);

		dst_release_flag &= primary_dev->priv_flags;
		अगर (primary_dev->hard_header_len > max_hard_header_len)
			max_hard_header_len = primary_dev->hard_header_len;
	पूर्ण

	standby_dev = rcu_dereference(nfo_info->standby_dev);
	अगर (standby_dev) अणु
		vlan_features =
			netdev_increment_features(vlan_features,
						  standby_dev->vlan_features,
						  FAILOVER_VLAN_FEATURES);
		enc_features =
			netdev_increment_features(enc_features,
						  standby_dev->hw_enc_features,
						  FAILOVER_ENC_FEATURES);

		dst_release_flag &= standby_dev->priv_flags;
		अगर (standby_dev->hard_header_len > max_hard_header_len)
			max_hard_header_len = standby_dev->hard_header_len;
	पूर्ण

	dev->vlan_features = vlan_features;
	dev->hw_enc_features = enc_features | NETIF_F_GSO_ENCAP_ALL;
	dev->hard_header_len = max_hard_header_len;

	dev->priv_flags &= ~IFF_XMIT_DST_RELEASE;
	अगर (dst_release_flag == (IFF_XMIT_DST_RELEASE |
				 IFF_XMIT_DST_RELEASE_PERM))
		dev->priv_flags |= IFF_XMIT_DST_RELEASE;

	netdev_change_features(dev);
पूर्ण

अटल व्योम net_failover_lower_state_changed(काष्ठा net_device *slave_dev,
					     काष्ठा net_device *primary_dev,
					     काष्ठा net_device *standby_dev)
अणु
	काष्ठा netdev_lag_lower_state_info info;

	अगर (netअगर_carrier_ok(slave_dev))
		info.link_up = true;
	अन्यथा
		info.link_up = false;

	अगर (slave_dev == primary_dev) अणु
		अगर (netअगर_running(primary_dev))
			info.tx_enabled = true;
		अन्यथा
			info.tx_enabled = false;
	पूर्ण अन्यथा अणु
		अगर ((primary_dev && netअगर_running(primary_dev)) ||
		    (!netअगर_running(standby_dev)))
			info.tx_enabled = false;
		अन्यथा
			info.tx_enabled = true;
	पूर्ण

	netdev_lower_state_changed(slave_dev, &info);
पूर्ण

अटल पूर्णांक net_failover_slave_pre_रेजिस्टर(काष्ठा net_device *slave_dev,
					   काष्ठा net_device *failover_dev)
अणु
	काष्ठा net_device *standby_dev, *primary_dev;
	काष्ठा net_failover_info *nfo_info;
	bool slave_is_standby;

	nfo_info = netdev_priv(failover_dev);
	standby_dev = rtnl_dereference(nfo_info->standby_dev);
	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	slave_is_standby = slave_dev->dev.parent == failover_dev->dev.parent;
	अगर (slave_is_standby ? standby_dev : primary_dev) अणु
		netdev_err(failover_dev, "%s attempting to register as slave dev when %s already present\n",
			   slave_dev->name,
			   slave_is_standby ? "standby" : "primary");
		वापस -EINVAL;
	पूर्ण

	/* We want to allow only a direct attached VF device as a primary
	 * netdev. As there is no easy way to check क्रम a VF device, restrict
	 * this to a pci device.
	 */
	अगर (!slave_is_standby && (!slave_dev->dev.parent ||
				  !dev_is_pci(slave_dev->dev.parent)))
		वापस -EINVAL;

	अगर (failover_dev->features & NETIF_F_VLAN_CHALLENGED &&
	    vlan_uses_dev(failover_dev)) अणु
		netdev_err(failover_dev, "Device %s is VLAN challenged and failover device has VLAN set up\n",
			   failover_dev->name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक net_failover_slave_रेजिस्टर(काष्ठा net_device *slave_dev,
				       काष्ठा net_device *failover_dev)
अणु
	काष्ठा net_device *standby_dev, *primary_dev;
	काष्ठा net_failover_info *nfo_info;
	bool slave_is_standby;
	u32 orig_mtu;
	पूर्णांक err;

	/* Align MTU of slave with failover dev */
	orig_mtu = slave_dev->mtu;
	err = dev_set_mtu(slave_dev, failover_dev->mtu);
	अगर (err) अणु
		netdev_err(failover_dev, "unable to change mtu of %s to %u register failed\n",
			   slave_dev->name, failover_dev->mtu);
		जाओ करोne;
	पूर्ण

	dev_hold(slave_dev);

	अगर (netअगर_running(failover_dev)) अणु
		err = dev_खोलो(slave_dev, शून्य);
		अगर (err && (err != -EBUSY)) अणु
			netdev_err(failover_dev, "Opening slave %s failed err:%d\n",
				   slave_dev->name, err);
			जाओ err_dev_खोलो;
		पूर्ण
	पूर्ण

	netअगर_addr_lock_bh(failover_dev);
	dev_uc_sync_multiple(slave_dev, failover_dev);
	dev_mc_sync_multiple(slave_dev, failover_dev);
	netअगर_addr_unlock_bh(failover_dev);

	err = vlan_vids_add_by_dev(slave_dev, failover_dev);
	अगर (err) अणु
		netdev_err(failover_dev, "Failed to add vlan ids to device %s err:%d\n",
			   slave_dev->name, err);
		जाओ err_vlan_add;
	पूर्ण

	nfo_info = netdev_priv(failover_dev);
	standby_dev = rtnl_dereference(nfo_info->standby_dev);
	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	slave_is_standby = slave_dev->dev.parent == failover_dev->dev.parent;

	अगर (slave_is_standby) अणु
		rcu_assign_poपूर्णांकer(nfo_info->standby_dev, slave_dev);
		standby_dev = slave_dev;
		dev_get_stats(standby_dev, &nfo_info->standby_stats);
	पूर्ण अन्यथा अणु
		rcu_assign_poपूर्णांकer(nfo_info->primary_dev, slave_dev);
		primary_dev = slave_dev;
		dev_get_stats(primary_dev, &nfo_info->primary_stats);
		failover_dev->min_mtu = slave_dev->min_mtu;
		failover_dev->max_mtu = slave_dev->max_mtu;
	पूर्ण

	net_failover_lower_state_changed(slave_dev, primary_dev, standby_dev);
	net_failover_compute_features(failover_dev);

	call_netdevice_notअगरiers(NETDEV_JOIN, slave_dev);

	netdev_info(failover_dev, "failover %s slave:%s registered\n",
		    slave_is_standby ? "standby" : "primary", slave_dev->name);

	वापस 0;

err_vlan_add:
	dev_uc_unsync(slave_dev, failover_dev);
	dev_mc_unsync(slave_dev, failover_dev);
	dev_बंद(slave_dev);
err_dev_खोलो:
	dev_put(slave_dev);
	dev_set_mtu(slave_dev, orig_mtu);
करोne:
	वापस err;
पूर्ण

अटल पूर्णांक net_failover_slave_pre_unरेजिस्टर(काष्ठा net_device *slave_dev,
					     काष्ठा net_device *failover_dev)
अणु
	काष्ठा net_device *standby_dev, *primary_dev;
	काष्ठा net_failover_info *nfo_info;

	nfo_info = netdev_priv(failover_dev);
	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	standby_dev = rtnl_dereference(nfo_info->standby_dev);

	अगर (slave_dev != primary_dev && slave_dev != standby_dev)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक net_failover_slave_unरेजिस्टर(काष्ठा net_device *slave_dev,
					 काष्ठा net_device *failover_dev)
अणु
	काष्ठा net_device *standby_dev, *primary_dev;
	काष्ठा net_failover_info *nfo_info;
	bool slave_is_standby;

	nfo_info = netdev_priv(failover_dev);
	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	standby_dev = rtnl_dereference(nfo_info->standby_dev);

	अगर (WARN_ON_ONCE(slave_dev != primary_dev && slave_dev != standby_dev))
		वापस -ENODEV;

	vlan_vids_del_by_dev(slave_dev, failover_dev);
	dev_uc_unsync(slave_dev, failover_dev);
	dev_mc_unsync(slave_dev, failover_dev);
	dev_बंद(slave_dev);

	nfo_info = netdev_priv(failover_dev);
	dev_get_stats(failover_dev, &nfo_info->failover_stats);

	slave_is_standby = slave_dev->dev.parent == failover_dev->dev.parent;
	अगर (slave_is_standby) अणु
		RCU_INIT_POINTER(nfo_info->standby_dev, शून्य);
	पूर्ण अन्यथा अणु
		RCU_INIT_POINTER(nfo_info->primary_dev, शून्य);
		अगर (standby_dev) अणु
			failover_dev->min_mtu = standby_dev->min_mtu;
			failover_dev->max_mtu = standby_dev->max_mtu;
		पूर्ण
	पूर्ण

	dev_put(slave_dev);

	net_failover_compute_features(failover_dev);

	netdev_info(failover_dev, "failover %s slave:%s unregistered\n",
		    slave_is_standby ? "standby" : "primary", slave_dev->name);

	वापस 0;
पूर्ण

अटल पूर्णांक net_failover_slave_link_change(काष्ठा net_device *slave_dev,
					  काष्ठा net_device *failover_dev)
अणु
	काष्ठा net_device *primary_dev, *standby_dev;
	काष्ठा net_failover_info *nfo_info;

	nfo_info = netdev_priv(failover_dev);

	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	standby_dev = rtnl_dereference(nfo_info->standby_dev);

	अगर (slave_dev != primary_dev && slave_dev != standby_dev)
		वापस -ENODEV;

	अगर ((primary_dev && net_failover_xmit_पढ़ोy(primary_dev)) ||
	    (standby_dev && net_failover_xmit_पढ़ोy(standby_dev))) अणु
		netअगर_carrier_on(failover_dev);
		netअगर_tx_wake_all_queues(failover_dev);
	पूर्ण अन्यथा अणु
		dev_get_stats(failover_dev, &nfo_info->failover_stats);
		netअगर_carrier_off(failover_dev);
		netअगर_tx_stop_all_queues(failover_dev);
	पूर्ण

	net_failover_lower_state_changed(slave_dev, primary_dev, standby_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक net_failover_slave_name_change(काष्ठा net_device *slave_dev,
					  काष्ठा net_device *failover_dev)
अणु
	काष्ठा net_device *primary_dev, *standby_dev;
	काष्ठा net_failover_info *nfo_info;

	nfo_info = netdev_priv(failover_dev);

	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	standby_dev = rtnl_dereference(nfo_info->standby_dev);

	अगर (slave_dev != primary_dev && slave_dev != standby_dev)
		वापस -ENODEV;

	/* We need to bring up the slave after the नाम by udev in हाल
	 * खोलो failed with EBUSY when it was रेजिस्टरed.
	 */
	dev_खोलो(slave_dev, शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा failover_ops net_failover_ops = अणु
	.slave_pre_रेजिस्टर	= net_failover_slave_pre_रेजिस्टर,
	.slave_रेजिस्टर		= net_failover_slave_रेजिस्टर,
	.slave_pre_unरेजिस्टर	= net_failover_slave_pre_unरेजिस्टर,
	.slave_unरेजिस्टर	= net_failover_slave_unरेजिस्टर,
	.slave_link_change	= net_failover_slave_link_change,
	.slave_name_change	= net_failover_slave_name_change,
	.slave_handle_frame	= net_failover_handle_frame,
पूर्ण;

/**
 * net_failover_create - Create and रेजिस्टर a failover instance
 *
 * @standby_dev: standby netdev
 *
 * Creates a failover netdev and रेजिस्टरs a failover instance क्रम a standby
 * netdev. Used by paraभव drivers that use 3-netdev model.
 * The failover netdev acts as a master device and controls 2 slave devices -
 * the original standby netdev and a VF netdev with the same MAC माला_लो
 * रेजिस्टरed as primary netdev.
 *
 * Return: poपूर्णांकer to failover instance
 */
काष्ठा failover *net_failover_create(काष्ठा net_device *standby_dev)
अणु
	काष्ठा device *dev = standby_dev->dev.parent;
	काष्ठा net_device *failover_dev;
	काष्ठा failover *failover;
	पूर्णांक err;

	/* Alloc at least 2 queues, क्रम now we are going with 16 assuming
	 * that VF devices being enslaved won't have too many queues.
	 */
	failover_dev = alloc_etherdev_mq(माप(काष्ठा net_failover_info), 16);
	अगर (!failover_dev) अणु
		dev_err(dev, "Unable to allocate failover_netdev!\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	dev_net_set(failover_dev, dev_net(standby_dev));
	SET_NETDEV_DEV(failover_dev, dev);

	failover_dev->netdev_ops = &failover_dev_ops;
	failover_dev->ethtool_ops = &failover_ethtool_ops;

	/* Initialize the device options */
	failover_dev->priv_flags |= IFF_UNICAST_FLT | IFF_NO_QUEUE;
	failover_dev->priv_flags &= ~(IFF_XMIT_DST_RELEASE |
				       IFF_TX_SKB_SHARING);

	/* करोn't acquire failover netdev's netअगर_tx_lock when transmitting */
	failover_dev->features |= NETIF_F_LLTX;

	/* Don't allow failover devices to change network namespaces. */
	failover_dev->features |= NETIF_F_NETNS_LOCAL;

	failover_dev->hw_features = FAILOVER_VLAN_FEATURES |
				    NETIF_F_HW_VLAN_CTAG_TX |
				    NETIF_F_HW_VLAN_CTAG_RX |
				    NETIF_F_HW_VLAN_CTAG_FILTER;

	failover_dev->hw_features |= NETIF_F_GSO_ENCAP_ALL;
	failover_dev->features |= failover_dev->hw_features;

	स_नकल(failover_dev->dev_addr, standby_dev->dev_addr,
	       failover_dev->addr_len);

	failover_dev->min_mtu = standby_dev->min_mtu;
	failover_dev->max_mtu = standby_dev->max_mtu;

	err = रेजिस्टर_netdev(failover_dev);
	अगर (err) अणु
		dev_err(dev, "Unable to register failover_dev!\n");
		जाओ err_रेजिस्टर_netdev;
	पूर्ण

	netअगर_carrier_off(failover_dev);

	failover = failover_रेजिस्टर(failover_dev, &net_failover_ops);
	अगर (IS_ERR(failover)) अणु
		err = PTR_ERR(failover);
		जाओ err_failover_रेजिस्टर;
	पूर्ण

	वापस failover;

err_failover_रेजिस्टर:
	unरेजिस्टर_netdev(failover_dev);
err_रेजिस्टर_netdev:
	मुक्त_netdev(failover_dev);

	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(net_failover_create);

/**
 * net_failover_destroy - Destroy a failover instance
 *
 * @failover: poपूर्णांकer to failover instance
 *
 * Unरेजिस्टरs any slave netdevs associated with the failover instance by
 * calling failover_slave_unरेजिस्टर().
 * unरेजिस्टरs the failover instance itself and finally मुक्तs the failover
 * netdev. Used by paraभव drivers that use 3-netdev model.
 *
 */
व्योम net_failover_destroy(काष्ठा failover *failover)
अणु
	काष्ठा net_failover_info *nfo_info;
	काष्ठा net_device *failover_dev;
	काष्ठा net_device *slave_dev;

	अगर (!failover)
		वापस;

	failover_dev = rcu_dereference(failover->failover_dev);
	nfo_info = netdev_priv(failover_dev);

	netअगर_device_detach(failover_dev);

	rtnl_lock();

	slave_dev = rtnl_dereference(nfo_info->primary_dev);
	अगर (slave_dev)
		failover_slave_unरेजिस्टर(slave_dev);

	slave_dev = rtnl_dereference(nfo_info->standby_dev);
	अगर (slave_dev)
		failover_slave_unरेजिस्टर(slave_dev);

	failover_unरेजिस्टर(failover);

	unरेजिस्टर_netdevice(failover_dev);

	rtnl_unlock();

	मुक्त_netdev(failover_dev);
पूर्ण
EXPORT_SYMBOL_GPL(net_failover_destroy);

अटल __init पूर्णांक
net_failover_init(व्योम)
अणु
	वापस 0;
पूर्ण
module_init(net_failover_init);

अटल __निकास
व्योम net_failover_निकास(व्योम)
अणु
पूर्ण
module_निकास(net_failover_निकास);

MODULE_DESCRIPTION("Failover driver for Paravirtual drivers");
MODULE_LICENSE("GPL v2");
