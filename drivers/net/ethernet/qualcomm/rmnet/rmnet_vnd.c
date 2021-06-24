<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2013-2018, The Linux Foundation. All rights reserved.
 *
 * RMNET Data भव network driver
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/pkt_sched.h>
#समावेश "rmnet_config.h"
#समावेश "rmnet_handlers.h"
#समावेश "rmnet_private.h"
#समावेश "rmnet_map.h"
#समावेश "rmnet_vnd.h"

/* RX/TX Fixup */

व्योम rmnet_vnd_rx_fixup(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(dev);
	काष्ठा rmnet_pcpu_stats *pcpu_ptr;

	pcpu_ptr = this_cpu_ptr(priv->pcpu_stats);

	u64_stats_update_begin(&pcpu_ptr->syncp);
	pcpu_ptr->stats.rx_pkts++;
	pcpu_ptr->stats.rx_bytes += skb->len;
	u64_stats_update_end(&pcpu_ptr->syncp);
पूर्ण

व्योम rmnet_vnd_tx_fixup(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(dev);
	काष्ठा rmnet_pcpu_stats *pcpu_ptr;

	pcpu_ptr = this_cpu_ptr(priv->pcpu_stats);

	u64_stats_update_begin(&pcpu_ptr->syncp);
	pcpu_ptr->stats.tx_pkts++;
	pcpu_ptr->stats.tx_bytes += skb->len;
	u64_stats_update_end(&pcpu_ptr->syncp);
पूर्ण

/* Network Device Operations */

अटल netdev_tx_t rmnet_vnd_start_xmit(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev)
अणु
	काष्ठा rmnet_priv *priv;

	priv = netdev_priv(dev);
	अगर (priv->real_dev) अणु
		rmnet_egress_handler(skb);
	पूर्ण अन्यथा अणु
		this_cpu_inc(priv->pcpu_stats->stats.tx_drops);
		kमुक्त_skb(skb);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक rmnet_vnd_headroom(काष्ठा rmnet_port *port)
अणु
	u32 headroom;

	headroom = माप(काष्ठा rmnet_map_header);

	अगर (port->data_क्रमmat & RMNET_FLAGS_EGRESS_MAP_CKSUMV4)
		headroom += माप(काष्ठा rmnet_map_ul_csum_header);

	वापस headroom;
पूर्ण

अटल पूर्णांक rmnet_vnd_change_mtu(काष्ठा net_device *rmnet_dev, पूर्णांक new_mtu)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(rmnet_dev);
	काष्ठा rmnet_port *port;
	u32 headroom;

	port = rmnet_get_port_rtnl(priv->real_dev);

	headroom = rmnet_vnd_headroom(port);

	अगर (new_mtu < 0 || new_mtu > RMNET_MAX_PACKET_SIZE ||
	    new_mtu > (priv->real_dev->mtu - headroom))
		वापस -EINVAL;

	rmnet_dev->mtu = new_mtu;
	वापस 0;
पूर्ण

अटल पूर्णांक rmnet_vnd_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(dev);

	वापस priv->real_dev->अगरindex;
पूर्ण

अटल पूर्णांक rmnet_vnd_init(काष्ठा net_device *dev)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	priv->pcpu_stats = alloc_percpu(काष्ठा rmnet_pcpu_stats);
	अगर (!priv->pcpu_stats)
		वापस -ENOMEM;

	err = gro_cells_init(&priv->gro_cells, dev);
	अगर (err) अणु
		मुक्त_percpu(priv->pcpu_stats);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rmnet_vnd_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(dev);

	gro_cells_destroy(&priv->gro_cells);
	मुक्त_percpu(priv->pcpu_stats);
पूर्ण

अटल व्योम rmnet_get_stats64(काष्ठा net_device *dev,
			      काष्ठा rtnl_link_stats64 *s)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(dev);
	काष्ठा rmnet_vnd_stats total_stats = अणु पूर्ण;
	काष्ठा rmnet_pcpu_stats *pcpu_ptr;
	काष्ठा rmnet_vnd_stats snapshot;
	अचिन्हित पूर्णांक cpu, start;

	क्रम_each_possible_cpu(cpu) अणु
		pcpu_ptr = per_cpu_ptr(priv->pcpu_stats, cpu);

		करो अणु
			start = u64_stats_fetch_begin_irq(&pcpu_ptr->syncp);
			snapshot = pcpu_ptr->stats;	/* काष्ठा assignment */
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&pcpu_ptr->syncp, start));

		total_stats.rx_pkts += snapshot.rx_pkts;
		total_stats.rx_bytes += snapshot.rx_bytes;
		total_stats.tx_pkts += snapshot.tx_pkts;
		total_stats.tx_bytes += snapshot.tx_bytes;
		total_stats.tx_drops += snapshot.tx_drops;
	पूर्ण

	s->rx_packets = total_stats.rx_pkts;
	s->rx_bytes = total_stats.rx_bytes;
	s->tx_packets = total_stats.tx_pkts;
	s->tx_bytes = total_stats.tx_bytes;
	s->tx_dropped = total_stats.tx_drops;
पूर्ण

अटल स्थिर काष्ठा net_device_ops rmnet_vnd_ops = अणु
	.nकरो_start_xmit = rmnet_vnd_start_xmit,
	.nकरो_change_mtu = rmnet_vnd_change_mtu,
	.nकरो_get_अगरlink = rmnet_vnd_get_अगरlink,
	.nकरो_add_slave  = rmnet_add_bridge,
	.nकरो_del_slave  = rmnet_del_bridge,
	.nकरो_init       = rmnet_vnd_init,
	.nकरो_uninit     = rmnet_vnd_uninit,
	.nकरो_get_stats64 = rmnet_get_stats64,
पूर्ण;

अटल स्थिर अक्षर rmnet_gstrings_stats[][ETH_GSTRING_LEN] = अणु
	"Checksum ok",
	"Checksum valid bit not set",
	"Checksum validation failed",
	"Checksum error bad buffer",
	"Checksum error bad ip version",
	"Checksum error bad transport",
	"Checksum skipped on ip fragment",
	"Checksum skipped",
	"Checksum computed in software",
पूर्ण;

अटल व्योम rmnet_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(buf, &rmnet_gstrings_stats,
		       माप(rmnet_gstrings_stats));
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rmnet_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(rmnet_gstrings_stats);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम rmnet_get_ethtool_stats(काष्ठा net_device *dev,
				    काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा rmnet_priv *priv = netdev_priv(dev);
	काष्ठा rmnet_priv_stats *st = &priv->stats;

	अगर (!data)
		वापस;

	स_नकल(data, st, ARRAY_SIZE(rmnet_gstrings_stats) * माप(u64));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops rmnet_ethtool_ops = अणु
	.get_ethtool_stats = rmnet_get_ethtool_stats,
	.get_strings = rmnet_get_strings,
	.get_sset_count = rmnet_get_sset_count,
पूर्ण;

/* Called by kernel whenever a new rmnet<n> device is created. Sets MTU,
 * flags, ARP type, needed headroom, etc...
 */
व्योम rmnet_vnd_setup(काष्ठा net_device *rmnet_dev)
अणु
	rmnet_dev->netdev_ops = &rmnet_vnd_ops;
	rmnet_dev->mtu = RMNET_DFLT_PACKET_SIZE;
	rmnet_dev->needed_headroom = RMNET_NEEDED_HEADROOM;
	eth_अक्रमom_addr(rmnet_dev->dev_addr);
	rmnet_dev->tx_queue_len = RMNET_TX_QUEUE_LEN;

	/* Raw IP mode */
	rmnet_dev->header_ops = शून्य;  /* No header */
	rmnet_dev->type = ARPHRD_RAWIP;
	rmnet_dev->hard_header_len = 0;
	rmnet_dev->flags &= ~(IFF_BROADCAST | IFF_MULTICAST);

	rmnet_dev->needs_मुक्त_netdev = true;
	rmnet_dev->ethtool_ops = &rmnet_ethtool_ops;

	rmnet_dev->features |= NETIF_F_LLTX;

	/* This perm addr will be used as पूर्णांकerface identअगरier by IPv6 */
	rmnet_dev->addr_assign_type = NET_ADDR_RANDOM;
	eth_अक्रमom_addr(rmnet_dev->perm_addr);
पूर्ण

/* Exposed API */

पूर्णांक rmnet_vnd_newlink(u8 id, काष्ठा net_device *rmnet_dev,
		      काष्ठा rmnet_port *port,
		      काष्ठा net_device *real_dev,
		      काष्ठा rmnet_endpoपूर्णांक *ep,
		      काष्ठा netlink_ext_ack *extack)

अणु
	काष्ठा rmnet_priv *priv = netdev_priv(rmnet_dev);
	u32 headroom;
	पूर्णांक rc;

	अगर (rmnet_get_endpoपूर्णांक(port, id)) अणु
		NL_SET_ERR_MSG_MOD(extack, "MUX ID already exists");
		वापस -EBUSY;
	पूर्ण

	rmnet_dev->hw_features = NETIF_F_RXCSUM;
	rmnet_dev->hw_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	rmnet_dev->hw_features |= NETIF_F_SG;

	priv->real_dev = real_dev;

	headroom = rmnet_vnd_headroom(port);

	अगर (rmnet_vnd_change_mtu(rmnet_dev, real_dev->mtu - headroom)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid MTU on real dev");
		वापस -EINVAL;
	पूर्ण

	rc = रेजिस्टर_netdevice(rmnet_dev);
	अगर (!rc) अणु
		ep->egress_dev = rmnet_dev;
		ep->mux_id = id;
		port->nr_rmnet_devs++;

		rmnet_dev->rtnl_link_ops = &rmnet_link_ops;

		priv->mux_id = id;

		netdev_dbg(rmnet_dev, "rmnet dev created\n");
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक rmnet_vnd_dellink(u8 id, काष्ठा rmnet_port *port,
		      काष्ठा rmnet_endpoपूर्णांक *ep)
अणु
	अगर (id >= RMNET_MAX_LOGICAL_EP || !ep->egress_dev)
		वापस -EINVAL;

	ep->egress_dev = शून्य;
	port->nr_rmnet_devs--;
	वापस 0;
पूर्ण

पूर्णांक rmnet_vnd_करो_flow_control(काष्ठा net_device *rmnet_dev, पूर्णांक enable)
अणु
	netdev_dbg(rmnet_dev, "Setting VND TX queue state to %d\n", enable);
	/* Although we expect similar number of enable/disable
	 * commands, optimize क्रम the disable. That is more
	 * latency sensitive than enable
	 */
	अगर (unlikely(enable))
		netअगर_wake_queue(rmnet_dev);
	अन्यथा
		netअगर_stop_queue(rmnet_dev);

	वापस 0;
पूर्ण

पूर्णांक rmnet_vnd_validate_real_dev_mtu(काष्ठा net_device *real_dev)
अणु
	काष्ठा hlist_node *पंचांगp_ep;
	काष्ठा rmnet_endpoपूर्णांक *ep;
	काष्ठा rmnet_port *port;
	अचिन्हित दीर्घ bkt_ep;
	u32 headroom;

	port = rmnet_get_port_rtnl(real_dev);

	headroom = rmnet_vnd_headroom(port);

	hash_क्रम_each_safe(port->muxed_ep, bkt_ep, पंचांगp_ep, ep, hlnode) अणु
		अगर (ep->egress_dev->mtu > (real_dev->mtu - headroom))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rmnet_vnd_update_dev_mtu(काष्ठा rmnet_port *port,
			     काष्ठा net_device *real_dev)
अणु
	काष्ठा hlist_node *पंचांगp_ep;
	काष्ठा rmnet_endpoपूर्णांक *ep;
	अचिन्हित दीर्घ bkt_ep;
	u32 headroom;

	headroom = rmnet_vnd_headroom(port);

	hash_क्रम_each_safe(port->muxed_ep, bkt_ep, पंचांगp_ep, ep, hlnode) अणु
		अगर (ep->egress_dev->mtu <= (real_dev->mtu - headroom))
			जारी;

		अगर (rmnet_vnd_change_mtu(ep->egress_dev,
					 real_dev->mtu - headroom))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
