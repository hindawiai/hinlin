<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  drivers/net/veth.c
 *
 *  Copyright (C) 2007 OpenVZ http://खोलोvz.org, SWsoft Inc
 *
 * Author: Pavel Emelianov <xemul@खोलोvz.org>
 * Ethtool पूर्णांकerface from: Eric W. Biederman <ebiederm@xmission.com>
 *
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/u64_stats_sync.h>

#समावेश <net/rtnetlink.h>
#समावेश <net/dst.h>
#समावेश <net/xfrm.h>
#समावेश <net/xdp.h>
#समावेश <linux/veth.h>
#समावेश <linux/module.h>
#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश <linux/ptr_ring.h>
#समावेश <linux/bpf_trace.h>
#समावेश <linux/net_tstamp.h>

#घोषणा DRV_NAME	"veth"
#घोषणा DRV_VERSION	"1.0"

#घोषणा VETH_XDP_FLAG		BIT(0)
#घोषणा VETH_RING_SIZE		256
#घोषणा VETH_XDP_HEADROOM	(XDP_PACKET_HEADROOM + NET_IP_ALIGN)

#घोषणा VETH_XDP_TX_BULK_SIZE	16
#घोषणा VETH_XDP_BATCH		16

काष्ठा veth_stats अणु
	u64	rx_drops;
	/* xdp */
	u64	xdp_packets;
	u64	xdp_bytes;
	u64	xdp_redirect;
	u64	xdp_drops;
	u64	xdp_tx;
	u64	xdp_tx_err;
	u64	peer_tq_xdp_xmit;
	u64	peer_tq_xdp_xmit_err;
पूर्ण;

काष्ठा veth_rq_stats अणु
	काष्ठा veth_stats	vs;
	काष्ठा u64_stats_sync	syncp;
पूर्ण;

काष्ठा veth_rq अणु
	काष्ठा napi_काष्ठा	xdp_napi;
	काष्ठा napi_काष्ठा __rcu *napi; /* poपूर्णांकs to xdp_napi when the latter is initialized */
	काष्ठा net_device	*dev;
	काष्ठा bpf_prog __rcu	*xdp_prog;
	काष्ठा xdp_mem_info	xdp_mem;
	काष्ठा veth_rq_stats	stats;
	bool			rx_notअगरy_masked;
	काष्ठा ptr_ring		xdp_ring;
	काष्ठा xdp_rxq_info	xdp_rxq;
पूर्ण;

काष्ठा veth_priv अणु
	काष्ठा net_device __rcu	*peer;
	atomic64_t		dropped;
	काष्ठा bpf_prog		*_xdp_prog;
	काष्ठा veth_rq		*rq;
	अचिन्हित पूर्णांक		requested_headroom;
पूर्ण;

काष्ठा veth_xdp_tx_bq अणु
	काष्ठा xdp_frame *q[VETH_XDP_TX_BULK_SIZE];
	अचिन्हित पूर्णांक count;
पूर्ण;

/*
 * ethtool पूर्णांकerface
 */

काष्ठा veth_q_stat_desc अणु
	अक्षर	desc[ETH_GSTRING_LEN];
	माप_प्रकार	offset;
पूर्ण;

#घोषणा VETH_RQ_STAT(m)	दुरत्व(काष्ठा veth_stats, m)

अटल स्थिर काष्ठा veth_q_stat_desc veth_rq_stats_desc[] = अणु
	अणु "xdp_packets",	VETH_RQ_STAT(xdp_packets) पूर्ण,
	अणु "xdp_bytes",		VETH_RQ_STAT(xdp_bytes) पूर्ण,
	अणु "drops",		VETH_RQ_STAT(rx_drops) पूर्ण,
	अणु "xdp_redirect",	VETH_RQ_STAT(xdp_redirect) पूर्ण,
	अणु "xdp_drops",		VETH_RQ_STAT(xdp_drops) पूर्ण,
	अणु "xdp_tx",		VETH_RQ_STAT(xdp_tx) पूर्ण,
	अणु "xdp_tx_errors",	VETH_RQ_STAT(xdp_tx_err) पूर्ण,
पूर्ण;

#घोषणा VETH_RQ_STATS_LEN	ARRAY_SIZE(veth_rq_stats_desc)

अटल स्थिर काष्ठा veth_q_stat_desc veth_tq_stats_desc[] = अणु
	अणु "xdp_xmit",		VETH_RQ_STAT(peer_tq_xdp_xmit) पूर्ण,
	अणु "xdp_xmit_errors",	VETH_RQ_STAT(peer_tq_xdp_xmit_err) पूर्ण,
पूर्ण;

#घोषणा VETH_TQ_STATS_LEN	ARRAY_SIZE(veth_tq_stats_desc)

अटल काष्ठा अणु
	स्थिर अक्षर string[ETH_GSTRING_LEN];
पूर्ण ethtool_stats_keys[] = अणु
	अणु "peer_ifindex" पूर्ण,
पूर्ण;

अटल पूर्णांक veth_get_link_ksettings(काष्ठा net_device *dev,
				   काष्ठा ethtool_link_ksettings *cmd)
अणु
	cmd->base.speed		= SPEED_10000;
	cmd->base.duplex	= DUPLEX_FULL;
	cmd->base.port		= PORT_TP;
	cmd->base.स्वतःneg	= AUTONEG_DISABLE;
	वापस 0;
पूर्ण

अटल व्योम veth_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
पूर्ण

अटल व्योम veth_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	अक्षर *p = (अक्षर *)buf;
	पूर्णांक i, j;

	चयन(stringset) अणु
	हाल ETH_SS_STATS:
		स_नकल(p, &ethtool_stats_keys, माप(ethtool_stats_keys));
		p += माप(ethtool_stats_keys);
		क्रम (i = 0; i < dev->real_num_rx_queues; i++) अणु
			क्रम (j = 0; j < VETH_RQ_STATS_LEN; j++) अणु
				snम_लिखो(p, ETH_GSTRING_LEN,
					 "rx_queue_%u_%.18s",
					 i, veth_rq_stats_desc[j].desc);
				p += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < dev->real_num_tx_queues; i++) अणु
			क्रम (j = 0; j < VETH_TQ_STATS_LEN; j++) अणु
				snम_लिखो(p, ETH_GSTRING_LEN,
					 "tx_queue_%u_%.18s",
					 i, veth_tq_stats_desc[j].desc);
				p += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक veth_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(ethtool_stats_keys) +
		       VETH_RQ_STATS_LEN * dev->real_num_rx_queues +
		       VETH_TQ_STATS_LEN * dev->real_num_tx_queues;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम veth_get_ethtool_stats(काष्ठा net_device *dev,
		काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा veth_priv *rcv_priv, *priv = netdev_priv(dev);
	काष्ठा net_device *peer = rtnl_dereference(priv->peer);
	पूर्णांक i, j, idx;

	data[0] = peer ? peer->अगरindex : 0;
	idx = 1;
	क्रम (i = 0; i < dev->real_num_rx_queues; i++) अणु
		स्थिर काष्ठा veth_rq_stats *rq_stats = &priv->rq[i].stats;
		स्थिर व्योम *stats_base = (व्योम *)&rq_stats->vs;
		अचिन्हित पूर्णांक start;
		माप_प्रकार offset;

		करो अणु
			start = u64_stats_fetch_begin_irq(&rq_stats->syncp);
			क्रम (j = 0; j < VETH_RQ_STATS_LEN; j++) अणु
				offset = veth_rq_stats_desc[j].offset;
				data[idx + j] = *(u64 *)(stats_base + offset);
			पूर्ण
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&rq_stats->syncp, start));
		idx += VETH_RQ_STATS_LEN;
	पूर्ण

	अगर (!peer)
		वापस;

	rcv_priv = netdev_priv(peer);
	क्रम (i = 0; i < peer->real_num_rx_queues; i++) अणु
		स्थिर काष्ठा veth_rq_stats *rq_stats = &rcv_priv->rq[i].stats;
		स्थिर व्योम *base = (व्योम *)&rq_stats->vs;
		अचिन्हित पूर्णांक start, tx_idx = idx;
		माप_प्रकार offset;

		tx_idx += (i % dev->real_num_tx_queues) * VETH_TQ_STATS_LEN;
		करो अणु
			start = u64_stats_fetch_begin_irq(&rq_stats->syncp);
			क्रम (j = 0; j < VETH_TQ_STATS_LEN; j++) अणु
				offset = veth_tq_stats_desc[j].offset;
				data[tx_idx + j] += *(u64 *)(base + offset);
			पूर्ण
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&rq_stats->syncp, start));
	पूर्ण
पूर्ण

अटल व्योम veth_get_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *channels)
अणु
	channels->tx_count = dev->real_num_tx_queues;
	channels->rx_count = dev->real_num_rx_queues;
	channels->max_tx = dev->real_num_tx_queues;
	channels->max_rx = dev->real_num_rx_queues;
	channels->combined_count = min(dev->real_num_rx_queues, dev->real_num_tx_queues);
	channels->max_combined = min(dev->real_num_rx_queues, dev->real_num_tx_queues);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops veth_ethtool_ops = अणु
	.get_drvinfo		= veth_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_strings		= veth_get_strings,
	.get_sset_count		= veth_get_sset_count,
	.get_ethtool_stats	= veth_get_ethtool_stats,
	.get_link_ksettings	= veth_get_link_ksettings,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_channels		= veth_get_channels,
पूर्ण;

/* general routines */

अटल bool veth_is_xdp_frame(व्योम *ptr)
अणु
	वापस (अचिन्हित दीर्घ)ptr & VETH_XDP_FLAG;
पूर्ण

अटल काष्ठा xdp_frame *veth_ptr_to_xdp(व्योम *ptr)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)ptr & ~VETH_XDP_FLAG);
पूर्ण

अटल व्योम *veth_xdp_to_ptr(काष्ठा xdp_frame *xdp)
अणु
	वापस (व्योम *)((अचिन्हित दीर्घ)xdp | VETH_XDP_FLAG);
पूर्ण

अटल व्योम veth_ptr_मुक्त(व्योम *ptr)
अणु
	अगर (veth_is_xdp_frame(ptr))
		xdp_वापस_frame(veth_ptr_to_xdp(ptr));
	अन्यथा
		kमुक्त_skb(ptr);
पूर्ण

अटल व्योम __veth_xdp_flush(काष्ठा veth_rq *rq)
अणु
	/* Write ptr_ring beक्रमe पढ़ोing rx_notअगरy_masked */
	smp_mb();
	अगर (!rq->rx_notअगरy_masked) अणु
		rq->rx_notअगरy_masked = true;
		napi_schedule(&rq->xdp_napi);
	पूर्ण
पूर्ण

अटल पूर्णांक veth_xdp_rx(काष्ठा veth_rq *rq, काष्ठा sk_buff *skb)
अणु
	अगर (unlikely(ptr_ring_produce(&rq->xdp_ring, skb))) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NET_RX_DROP;
	पूर्ण

	वापस NET_RX_SUCCESS;
पूर्ण

अटल पूर्णांक veth_क्रमward_skb(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			    काष्ठा veth_rq *rq, bool xdp)
अणु
	वापस __dev_क्रमward_skb(dev, skb) ?: xdp ?
		veth_xdp_rx(rq, skb) :
		netअगर_rx(skb);
पूर्ण

/* वापस true अगर the specअगरied skb has chances of GRO aggregation
 * Don't strive क्रम accuracy, but try to aव्योम GRO overhead in the most
 * common scenarios.
 * When XDP is enabled, all traffic is considered eligible, as the xmit
 * device has TSO off.
 * When TSO is enabled on the xmit device, we are likely पूर्णांकerested only
 * in UDP aggregation, explicitly check क्रम that अगर the skb is suspected
 * - the sock_wमुक्त deकाष्ठाor is used by UDP, ICMP and XDP sockets -
 * to beदीर्घ to locally generated UDP traffic.
 */
अटल bool veth_skb_is_eligible_क्रम_gro(स्थिर काष्ठा net_device *dev,
					 स्थिर काष्ठा net_device *rcv,
					 स्थिर काष्ठा sk_buff *skb)
अणु
	वापस !(dev->features & NETIF_F_ALL_TSO) ||
		(skb->deकाष्ठाor == sock_wमुक्त &&
		 rcv->features & (NETIF_F_GRO_FRAGLIST | NETIF_F_GRO_UDP_FWD));
पूर्ण

अटल netdev_tx_t veth_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा veth_priv *rcv_priv, *priv = netdev_priv(dev);
	काष्ठा veth_rq *rq = शून्य;
	काष्ठा net_device *rcv;
	पूर्णांक length = skb->len;
	bool use_napi = false;
	पूर्णांक rxq;

	rcu_पढ़ो_lock();
	rcv = rcu_dereference(priv->peer);
	अगर (unlikely(!rcv)) अणु
		kमुक्त_skb(skb);
		जाओ drop;
	पूर्ण

	rcv_priv = netdev_priv(rcv);
	rxq = skb_get_queue_mapping(skb);
	अगर (rxq < rcv->real_num_rx_queues) अणु
		rq = &rcv_priv->rq[rxq];

		/* The napi poपूर्णांकer is available when an XDP program is
		 * attached or when GRO is enabled
		 * Don't bother with napi/GRO if the skb can't be aggregated
		 */
		use_napi = rcu_access_poपूर्णांकer(rq->napi) &&
			   veth_skb_is_eligible_क्रम_gro(dev, rcv, skb);
		skb_record_rx_queue(skb, rxq);
	पूर्ण

	skb_tx_बारtamp(skb);
	अगर (likely(veth_क्रमward_skb(rcv, skb, rq, use_napi) == NET_RX_SUCCESS)) अणु
		अगर (!use_napi)
			dev_lstats_add(dev, length);
	पूर्ण अन्यथा अणु
drop:
		atomic64_inc(&priv->dropped);
	पूर्ण

	अगर (use_napi)
		__veth_xdp_flush(rq);

	rcu_पढ़ो_unlock();

	वापस NETDEV_TX_OK;
पूर्ण

अटल u64 veth_stats_tx(काष्ठा net_device *dev, u64 *packets, u64 *bytes)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);

	dev_lstats_पढ़ो(dev, packets, bytes);
	वापस atomic64_पढ़ो(&priv->dropped);
पूर्ण

अटल व्योम veth_stats_rx(काष्ठा veth_stats *result, काष्ठा net_device *dev)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	result->peer_tq_xdp_xmit_err = 0;
	result->xdp_packets = 0;
	result->xdp_tx_err = 0;
	result->xdp_bytes = 0;
	result->rx_drops = 0;
	क्रम (i = 0; i < dev->num_rx_queues; i++) अणु
		u64 packets, bytes, drops, xdp_tx_err, peer_tq_xdp_xmit_err;
		काष्ठा veth_rq_stats *stats = &priv->rq[i].stats;
		अचिन्हित पूर्णांक start;

		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			peer_tq_xdp_xmit_err = stats->vs.peer_tq_xdp_xmit_err;
			xdp_tx_err = stats->vs.xdp_tx_err;
			packets = stats->vs.xdp_packets;
			bytes = stats->vs.xdp_bytes;
			drops = stats->vs.rx_drops;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));
		result->peer_tq_xdp_xmit_err += peer_tq_xdp_xmit_err;
		result->xdp_tx_err += xdp_tx_err;
		result->xdp_packets += packets;
		result->xdp_bytes += bytes;
		result->rx_drops += drops;
	पूर्ण
पूर्ण

अटल व्योम veth_get_stats64(काष्ठा net_device *dev,
			     काष्ठा rtnl_link_stats64 *tot)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);
	काष्ठा net_device *peer;
	काष्ठा veth_stats rx;
	u64 packets, bytes;

	tot->tx_dropped = veth_stats_tx(dev, &packets, &bytes);
	tot->tx_bytes = bytes;
	tot->tx_packets = packets;

	veth_stats_rx(&rx, dev);
	tot->tx_dropped += rx.xdp_tx_err;
	tot->rx_dropped = rx.rx_drops + rx.peer_tq_xdp_xmit_err;
	tot->rx_bytes = rx.xdp_bytes;
	tot->rx_packets = rx.xdp_packets;

	rcu_पढ़ो_lock();
	peer = rcu_dereference(priv->peer);
	अगर (peer) अणु
		veth_stats_tx(peer, &packets, &bytes);
		tot->rx_bytes += bytes;
		tot->rx_packets += packets;

		veth_stats_rx(&rx, peer);
		tot->tx_dropped += rx.peer_tq_xdp_xmit_err;
		tot->rx_dropped += rx.xdp_tx_err;
		tot->tx_bytes += rx.xdp_bytes;
		tot->tx_packets += rx.xdp_packets;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* fake multicast ability */
अटल व्योम veth_set_multicast_list(काष्ठा net_device *dev)
अणु
पूर्ण

अटल काष्ठा sk_buff *veth_build_skb(व्योम *head, पूर्णांक headroom, पूर्णांक len,
				      पूर्णांक buflen)
अणु
	काष्ठा sk_buff *skb;

	skb = build_skb(head, buflen);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, headroom);
	skb_put(skb, len);

	वापस skb;
पूर्ण

अटल पूर्णांक veth_select_rxq(काष्ठा net_device *dev)
अणु
	वापस smp_processor_id() % dev->real_num_rx_queues;
पूर्ण

अटल काष्ठा net_device *veth_peer_dev(काष्ठा net_device *dev)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);

	/* Callers must be under RCU पढ़ो side. */
	वापस rcu_dereference(priv->peer);
पूर्ण

अटल पूर्णांक veth_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n,
			 काष्ठा xdp_frame **frames,
			 u32 flags, bool nकरो_xmit)
अणु
	काष्ठा veth_priv *rcv_priv, *priv = netdev_priv(dev);
	पूर्णांक i, ret = -ENXIO, nxmit = 0;
	काष्ठा net_device *rcv;
	अचिन्हित पूर्णांक max_len;
	काष्ठा veth_rq *rq;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	rcv = rcu_dereference(priv->peer);
	अगर (unlikely(!rcv))
		जाओ out;

	rcv_priv = netdev_priv(rcv);
	rq = &rcv_priv->rq[veth_select_rxq(rcv)];
	/* The napi poपूर्णांकer is set अगर NAPI is enabled, which ensures that
	 * xdp_ring is initialized on receive side and the peer device is up.
	 */
	अगर (!rcu_access_poपूर्णांकer(rq->napi))
		जाओ out;

	max_len = rcv->mtu + rcv->hard_header_len + VLAN_HLEN;

	spin_lock(&rq->xdp_ring.producer_lock);
	क्रम (i = 0; i < n; i++) अणु
		काष्ठा xdp_frame *frame = frames[i];
		व्योम *ptr = veth_xdp_to_ptr(frame);

		अगर (unlikely(frame->len > max_len ||
			     __ptr_ring_produce(&rq->xdp_ring, ptr)))
			अवरोध;
		nxmit++;
	पूर्ण
	spin_unlock(&rq->xdp_ring.producer_lock);

	अगर (flags & XDP_XMIT_FLUSH)
		__veth_xdp_flush(rq);

	ret = nxmit;
	अगर (nकरो_xmit) अणु
		u64_stats_update_begin(&rq->stats.syncp);
		rq->stats.vs.peer_tq_xdp_xmit += nxmit;
		rq->stats.vs.peer_tq_xdp_xmit_err += n - nxmit;
		u64_stats_update_end(&rq->stats.syncp);
	पूर्ण

out:
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक veth_nकरो_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n,
			     काष्ठा xdp_frame **frames, u32 flags)
अणु
	पूर्णांक err;

	err = veth_xdp_xmit(dev, n, frames, flags, true);
	अगर (err < 0) अणु
		काष्ठा veth_priv *priv = netdev_priv(dev);

		atomic64_add(n, &priv->dropped);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम veth_xdp_flush_bq(काष्ठा veth_rq *rq, काष्ठा veth_xdp_tx_bq *bq)
अणु
	पूर्णांक sent, i, err = 0, drops;

	sent = veth_xdp_xmit(rq->dev, bq->count, bq->q, 0, false);
	अगर (sent < 0) अणु
		err = sent;
		sent = 0;
	पूर्ण

	क्रम (i = sent; unlikely(i < bq->count); i++)
		xdp_वापस_frame(bq->q[i]);

	drops = bq->count - sent;
	trace_xdp_bulk_tx(rq->dev, sent, drops, err);

	u64_stats_update_begin(&rq->stats.syncp);
	rq->stats.vs.xdp_tx += sent;
	rq->stats.vs.xdp_tx_err += drops;
	u64_stats_update_end(&rq->stats.syncp);

	bq->count = 0;
पूर्ण

अटल व्योम veth_xdp_flush(काष्ठा veth_rq *rq, काष्ठा veth_xdp_tx_bq *bq)
अणु
	काष्ठा veth_priv *rcv_priv, *priv = netdev_priv(rq->dev);
	काष्ठा net_device *rcv;
	काष्ठा veth_rq *rcv_rq;

	rcu_पढ़ो_lock();
	veth_xdp_flush_bq(rq, bq);
	rcv = rcu_dereference(priv->peer);
	अगर (unlikely(!rcv))
		जाओ out;

	rcv_priv = netdev_priv(rcv);
	rcv_rq = &rcv_priv->rq[veth_select_rxq(rcv)];
	/* xdp_ring is initialized on receive side? */
	अगर (unlikely(!rcu_access_poपूर्णांकer(rcv_rq->xdp_prog)))
		जाओ out;

	__veth_xdp_flush(rcv_rq);
out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक veth_xdp_tx(काष्ठा veth_rq *rq, काष्ठा xdp_buff *xdp,
		       काष्ठा veth_xdp_tx_bq *bq)
अणु
	काष्ठा xdp_frame *frame = xdp_convert_buff_to_frame(xdp);

	अगर (unlikely(!frame))
		वापस -EOVERFLOW;

	अगर (unlikely(bq->count == VETH_XDP_TX_BULK_SIZE))
		veth_xdp_flush_bq(rq, bq);

	bq->q[bq->count++] = frame;

	वापस 0;
पूर्ण

अटल काष्ठा xdp_frame *veth_xdp_rcv_one(काष्ठा veth_rq *rq,
					  काष्ठा xdp_frame *frame,
					  काष्ठा veth_xdp_tx_bq *bq,
					  काष्ठा veth_stats *stats)
अणु
	काष्ठा xdp_frame orig_frame;
	काष्ठा bpf_prog *xdp_prog;

	rcu_पढ़ो_lock();
	xdp_prog = rcu_dereference(rq->xdp_prog);
	अगर (likely(xdp_prog)) अणु
		काष्ठा xdp_buff xdp;
		u32 act;

		xdp_convert_frame_to_buff(frame, &xdp);
		xdp.rxq = &rq->xdp_rxq;

		act = bpf_prog_run_xdp(xdp_prog, &xdp);

		चयन (act) अणु
		हाल XDP_PASS:
			अगर (xdp_update_frame_from_buff(&xdp, frame))
				जाओ err_xdp;
			अवरोध;
		हाल XDP_TX:
			orig_frame = *frame;
			xdp.rxq->mem = frame->mem;
			अगर (unlikely(veth_xdp_tx(rq, &xdp, bq) < 0)) अणु
				trace_xdp_exception(rq->dev, xdp_prog, act);
				frame = &orig_frame;
				stats->rx_drops++;
				जाओ err_xdp;
			पूर्ण
			stats->xdp_tx++;
			rcu_पढ़ो_unlock();
			जाओ xdp_xmit;
		हाल XDP_REसूचीECT:
			orig_frame = *frame;
			xdp.rxq->mem = frame->mem;
			अगर (xdp_करो_redirect(rq->dev, &xdp, xdp_prog)) अणु
				frame = &orig_frame;
				stats->rx_drops++;
				जाओ err_xdp;
			पूर्ण
			stats->xdp_redirect++;
			rcu_पढ़ो_unlock();
			जाओ xdp_xmit;
		शेष:
			bpf_warn_invalid_xdp_action(act);
			fallthrough;
		हाल XDP_ABORTED:
			trace_xdp_exception(rq->dev, xdp_prog, act);
			fallthrough;
		हाल XDP_DROP:
			stats->xdp_drops++;
			जाओ err_xdp;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस frame;
err_xdp:
	rcu_पढ़ो_unlock();
	xdp_वापस_frame(frame);
xdp_xmit:
	वापस शून्य;
पूर्ण

/* frames array contains VETH_XDP_BATCH at most */
अटल व्योम veth_xdp_rcv_bulk_skb(काष्ठा veth_rq *rq, व्योम **frames,
				  पूर्णांक n_xdpf, काष्ठा veth_xdp_tx_bq *bq,
				  काष्ठा veth_stats *stats)
अणु
	व्योम *skbs[VETH_XDP_BATCH];
	पूर्णांक i;

	अगर (xdp_alloc_skb_bulk(skbs, n_xdpf,
			       GFP_ATOMIC | __GFP_ZERO) < 0) अणु
		क्रम (i = 0; i < n_xdpf; i++)
			xdp_वापस_frame(frames[i]);
		stats->rx_drops += n_xdpf;

		वापस;
	पूर्ण

	क्रम (i = 0; i < n_xdpf; i++) अणु
		काष्ठा sk_buff *skb = skbs[i];

		skb = __xdp_build_skb_from_frame(frames[i], skb,
						 rq->dev);
		अगर (!skb) अणु
			xdp_वापस_frame(frames[i]);
			stats->rx_drops++;
			जारी;
		पूर्ण
		napi_gro_receive(&rq->xdp_napi, skb);
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *veth_xdp_rcv_skb(काष्ठा veth_rq *rq,
					काष्ठा sk_buff *skb,
					काष्ठा veth_xdp_tx_bq *bq,
					काष्ठा veth_stats *stats)
अणु
	u32 pktlen, headroom, act, metalen, frame_sz;
	व्योम *orig_data, *orig_data_end;
	काष्ठा bpf_prog *xdp_prog;
	पूर्णांक mac_len, delta, off;
	काष्ठा xdp_buff xdp;

	skb_orphan_partial(skb);

	rcu_पढ़ो_lock();
	xdp_prog = rcu_dereference(rq->xdp_prog);
	अगर (unlikely(!xdp_prog)) अणु
		rcu_पढ़ो_unlock();
		जाओ out;
	पूर्ण

	mac_len = skb->data - skb_mac_header(skb);
	pktlen = skb->len + mac_len;
	headroom = skb_headroom(skb) - mac_len;

	अगर (skb_shared(skb) || skb_head_is_locked(skb) ||
	    skb_is_nonlinear(skb) || headroom < XDP_PACKET_HEADROOM) अणु
		काष्ठा sk_buff *nskb;
		पूर्णांक size, head_off;
		व्योम *head, *start;
		काष्ठा page *page;

		size = SKB_DATA_ALIGN(VETH_XDP_HEADROOM + pktlen) +
		       SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
		अगर (size > PAGE_SIZE)
			जाओ drop;

		page = alloc_page(GFP_ATOMIC | __GFP_NOWARN);
		अगर (!page)
			जाओ drop;

		head = page_address(page);
		start = head + VETH_XDP_HEADROOM;
		अगर (skb_copy_bits(skb, -mac_len, start, pktlen)) अणु
			page_frag_मुक्त(head);
			जाओ drop;
		पूर्ण

		nskb = veth_build_skb(head, VETH_XDP_HEADROOM + mac_len,
				      skb->len, PAGE_SIZE);
		अगर (!nskb) अणु
			page_frag_मुक्त(head);
			जाओ drop;
		पूर्ण

		skb_copy_header(nskb, skb);
		head_off = skb_headroom(nskb) - skb_headroom(skb);
		skb_headers_offset_update(nskb, head_off);
		consume_skb(skb);
		skb = nskb;
	पूर्ण

	/* SKB "head" area always have tailroom क्रम skb_shared_info */
	frame_sz = skb_end_poपूर्णांकer(skb) - skb->head;
	frame_sz += SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	xdp_init_buff(&xdp, frame_sz, &rq->xdp_rxq);
	xdp_prepare_buff(&xdp, skb->head, skb->mac_header, pktlen, true);

	orig_data = xdp.data;
	orig_data_end = xdp.data_end;

	act = bpf_prog_run_xdp(xdp_prog, &xdp);

	चयन (act) अणु
	हाल XDP_PASS:
		अवरोध;
	हाल XDP_TX:
		get_page(virt_to_page(xdp.data));
		consume_skb(skb);
		xdp.rxq->mem = rq->xdp_mem;
		अगर (unlikely(veth_xdp_tx(rq, &xdp, bq) < 0)) अणु
			trace_xdp_exception(rq->dev, xdp_prog, act);
			stats->rx_drops++;
			जाओ err_xdp;
		पूर्ण
		stats->xdp_tx++;
		rcu_पढ़ो_unlock();
		जाओ xdp_xmit;
	हाल XDP_REसूचीECT:
		get_page(virt_to_page(xdp.data));
		consume_skb(skb);
		xdp.rxq->mem = rq->xdp_mem;
		अगर (xdp_करो_redirect(rq->dev, &xdp, xdp_prog)) अणु
			stats->rx_drops++;
			जाओ err_xdp;
		पूर्ण
		stats->xdp_redirect++;
		rcu_पढ़ो_unlock();
		जाओ xdp_xmit;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(rq->dev, xdp_prog, act);
		fallthrough;
	हाल XDP_DROP:
		stats->xdp_drops++;
		जाओ xdp_drop;
	पूर्ण
	rcu_पढ़ो_unlock();

	/* check अगर bpf_xdp_adjust_head was used */
	delta = orig_data - xdp.data;
	off = mac_len + delta;
	अगर (off > 0)
		__skb_push(skb, off);
	अन्यथा अगर (off < 0)
		__skb_pull(skb, -off);
	skb->mac_header -= delta;

	/* check अगर bpf_xdp_adjust_tail was used */
	off = xdp.data_end - orig_data_end;
	अगर (off != 0)
		__skb_put(skb, off); /* positive on grow, negative on shrink */
	skb->protocol = eth_type_trans(skb, rq->dev);

	metalen = xdp.data - xdp.data_meta;
	अगर (metalen)
		skb_metadata_set(skb, metalen);
out:
	वापस skb;
drop:
	stats->rx_drops++;
xdp_drop:
	rcu_पढ़ो_unlock();
	kमुक्त_skb(skb);
	वापस शून्य;
err_xdp:
	rcu_पढ़ो_unlock();
	page_frag_मुक्त(xdp.data);
xdp_xmit:
	वापस शून्य;
पूर्ण

अटल पूर्णांक veth_xdp_rcv(काष्ठा veth_rq *rq, पूर्णांक budget,
			काष्ठा veth_xdp_tx_bq *bq,
			काष्ठा veth_stats *stats)
अणु
	पूर्णांक i, करोne = 0, n_xdpf = 0;
	व्योम *xdpf[VETH_XDP_BATCH];

	क्रम (i = 0; i < budget; i++) अणु
		व्योम *ptr = __ptr_ring_consume(&rq->xdp_ring);

		अगर (!ptr)
			अवरोध;

		अगर (veth_is_xdp_frame(ptr)) अणु
			/* nकरो_xdp_xmit */
			काष्ठा xdp_frame *frame = veth_ptr_to_xdp(ptr);

			stats->xdp_bytes += frame->len;
			frame = veth_xdp_rcv_one(rq, frame, bq, stats);
			अगर (frame) अणु
				/* XDP_PASS */
				xdpf[n_xdpf++] = frame;
				अगर (n_xdpf == VETH_XDP_BATCH) अणु
					veth_xdp_rcv_bulk_skb(rq, xdpf, n_xdpf,
							      bq, stats);
					n_xdpf = 0;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* nकरो_start_xmit */
			काष्ठा sk_buff *skb = ptr;

			stats->xdp_bytes += skb->len;
			skb = veth_xdp_rcv_skb(rq, skb, bq, stats);
			अगर (skb)
				napi_gro_receive(&rq->xdp_napi, skb);
		पूर्ण
		करोne++;
	पूर्ण

	अगर (n_xdpf)
		veth_xdp_rcv_bulk_skb(rq, xdpf, n_xdpf, bq, stats);

	u64_stats_update_begin(&rq->stats.syncp);
	rq->stats.vs.xdp_redirect += stats->xdp_redirect;
	rq->stats.vs.xdp_bytes += stats->xdp_bytes;
	rq->stats.vs.xdp_drops += stats->xdp_drops;
	rq->stats.vs.rx_drops += stats->rx_drops;
	rq->stats.vs.xdp_packets += करोne;
	u64_stats_update_end(&rq->stats.syncp);

	वापस करोne;
पूर्ण

अटल पूर्णांक veth_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा veth_rq *rq =
		container_of(napi, काष्ठा veth_rq, xdp_napi);
	काष्ठा veth_stats stats = अणुपूर्ण;
	काष्ठा veth_xdp_tx_bq bq;
	पूर्णांक करोne;

	bq.count = 0;

	xdp_set_वापस_frame_no_direct();
	करोne = veth_xdp_rcv(rq, budget, &bq, &stats);

	अगर (करोne < budget && napi_complete_करोne(napi, करोne)) अणु
		/* Write rx_notअगरy_masked beक्रमe पढ़ोing ptr_ring */
		smp_store_mb(rq->rx_notअगरy_masked, false);
		अगर (unlikely(!__ptr_ring_empty(&rq->xdp_ring))) अणु
			rq->rx_notअगरy_masked = true;
			napi_schedule(&rq->xdp_napi);
		पूर्ण
	पूर्ण

	अगर (stats.xdp_tx > 0)
		veth_xdp_flush(rq, &bq);
	अगर (stats.xdp_redirect > 0)
		xdp_करो_flush();
	xdp_clear_वापस_frame_no_direct();

	वापस करोne;
पूर्ण

अटल पूर्णांक __veth_napi_enable(काष्ठा net_device *dev)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);
	पूर्णांक err, i;

	क्रम (i = 0; i < dev->real_num_rx_queues; i++) अणु
		काष्ठा veth_rq *rq = &priv->rq[i];

		err = ptr_ring_init(&rq->xdp_ring, VETH_RING_SIZE, GFP_KERNEL);
		अगर (err)
			जाओ err_xdp_ring;
	पूर्ण

	क्रम (i = 0; i < dev->real_num_rx_queues; i++) अणु
		काष्ठा veth_rq *rq = &priv->rq[i];

		napi_enable(&rq->xdp_napi);
		rcu_assign_poपूर्णांकer(priv->rq[i].napi, &priv->rq[i].xdp_napi);
	पूर्ण

	वापस 0;
err_xdp_ring:
	क्रम (i--; i >= 0; i--)
		ptr_ring_cleanup(&priv->rq[i].xdp_ring, veth_ptr_मुक्त);

	वापस err;
पूर्ण

अटल व्योम veth_napi_del(काष्ठा net_device *dev)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < dev->real_num_rx_queues; i++) अणु
		काष्ठा veth_rq *rq = &priv->rq[i];

		rcu_assign_poपूर्णांकer(priv->rq[i].napi, शून्य);
		napi_disable(&rq->xdp_napi);
		__netअगर_napi_del(&rq->xdp_napi);
	पूर्ण
	synchronize_net();

	क्रम (i = 0; i < dev->real_num_rx_queues; i++) अणु
		काष्ठा veth_rq *rq = &priv->rq[i];

		rq->rx_notअगरy_masked = false;
		ptr_ring_cleanup(&rq->xdp_ring, veth_ptr_मुक्त);
	पूर्ण
पूर्ण

अटल bool veth_gro_requested(स्थिर काष्ठा net_device *dev)
अणु
	वापस !!(dev->wanted_features & NETIF_F_GRO);
पूर्ण

अटल पूर्णांक veth_enable_xdp(काष्ठा net_device *dev)
अणु
	bool napi_alपढ़ोy_on = veth_gro_requested(dev) && (dev->flags & IFF_UP);
	काष्ठा veth_priv *priv = netdev_priv(dev);
	पूर्णांक err, i;

	अगर (!xdp_rxq_info_is_reg(&priv->rq[0].xdp_rxq)) अणु
		क्रम (i = 0; i < dev->real_num_rx_queues; i++) अणु
			काष्ठा veth_rq *rq = &priv->rq[i];

			अगर (!napi_alपढ़ोy_on)
				netअगर_napi_add(dev, &rq->xdp_napi, veth_poll, NAPI_POLL_WEIGHT);
			err = xdp_rxq_info_reg(&rq->xdp_rxq, dev, i, rq->xdp_napi.napi_id);
			अगर (err < 0)
				जाओ err_rxq_reg;

			err = xdp_rxq_info_reg_mem_model(&rq->xdp_rxq,
							 MEM_TYPE_PAGE_SHARED,
							 शून्य);
			अगर (err < 0)
				जाओ err_reg_mem;

			/* Save original mem info as it can be overwritten */
			rq->xdp_mem = rq->xdp_rxq.mem;
		पूर्ण

		अगर (!napi_alपढ़ोy_on) अणु
			err = __veth_napi_enable(dev);
			अगर (err)
				जाओ err_rxq_reg;

			अगर (!veth_gro_requested(dev)) अणु
				/* user-space did not require GRO, but adding XDP
				 * is supposed to get GRO working
				 */
				dev->features |= NETIF_F_GRO;
				netdev_features_change(dev);
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dev->real_num_rx_queues; i++) अणु
		rcu_assign_poपूर्णांकer(priv->rq[i].xdp_prog, priv->_xdp_prog);
		rcu_assign_poपूर्णांकer(priv->rq[i].napi, &priv->rq[i].xdp_napi);
	पूर्ण

	वापस 0;
err_reg_mem:
	xdp_rxq_info_unreg(&priv->rq[i].xdp_rxq);
err_rxq_reg:
	क्रम (i--; i >= 0; i--) अणु
		काष्ठा veth_rq *rq = &priv->rq[i];

		xdp_rxq_info_unreg(&rq->xdp_rxq);
		अगर (!napi_alपढ़ोy_on)
			netअगर_napi_del(&rq->xdp_napi);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम veth_disable_xdp(काष्ठा net_device *dev)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < dev->real_num_rx_queues; i++)
		rcu_assign_poपूर्णांकer(priv->rq[i].xdp_prog, शून्य);

	अगर (!netअगर_running(dev) || !veth_gro_requested(dev)) अणु
		veth_napi_del(dev);

		/* अगर user-space did not require GRO, since adding XDP
		 * enabled it, clear it now
		 */
		अगर (!veth_gro_requested(dev) && netअगर_running(dev)) अणु
			dev->features &= ~NETIF_F_GRO;
			netdev_features_change(dev);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dev->real_num_rx_queues; i++) अणु
		काष्ठा veth_rq *rq = &priv->rq[i];

		rq->xdp_rxq.mem = rq->xdp_mem;
		xdp_rxq_info_unreg(&rq->xdp_rxq);
	पूर्ण
पूर्ण

अटल पूर्णांक veth_napi_enable(काष्ठा net_device *dev)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);
	पूर्णांक err, i;

	क्रम (i = 0; i < dev->real_num_rx_queues; i++) अणु
		काष्ठा veth_rq *rq = &priv->rq[i];

		netअगर_napi_add(dev, &rq->xdp_napi, veth_poll, NAPI_POLL_WEIGHT);
	पूर्ण

	err = __veth_napi_enable(dev);
	अगर (err) अणु
		क्रम (i = 0; i < dev->real_num_rx_queues; i++) अणु
			काष्ठा veth_rq *rq = &priv->rq[i];

			netअगर_napi_del(&rq->xdp_napi);
		पूर्ण
		वापस err;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक veth_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);
	काष्ठा net_device *peer = rtnl_dereference(priv->peer);
	पूर्णांक err;

	अगर (!peer)
		वापस -ENOTCONN;

	अगर (priv->_xdp_prog) अणु
		err = veth_enable_xdp(dev);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (veth_gro_requested(dev)) अणु
		err = veth_napi_enable(dev);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (peer->flags & IFF_UP) अणु
		netअगर_carrier_on(dev);
		netअगर_carrier_on(peer);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक veth_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);
	काष्ठा net_device *peer = rtnl_dereference(priv->peer);

	netअगर_carrier_off(dev);
	अगर (peer)
		netअगर_carrier_off(peer);

	अगर (priv->_xdp_prog)
		veth_disable_xdp(dev);
	अन्यथा अगर (veth_gro_requested(dev))
		veth_napi_del(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक is_valid_veth_mtu(पूर्णांक mtu)
अणु
	वापस mtu >= ETH_MIN_MTU && mtu <= ETH_MAX_MTU;
पूर्ण

अटल पूर्णांक veth_alloc_queues(काष्ठा net_device *dev)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	priv->rq = kसुस्मृति(dev->num_rx_queues, माप(*priv->rq), GFP_KERNEL);
	अगर (!priv->rq)
		वापस -ENOMEM;

	क्रम (i = 0; i < dev->num_rx_queues; i++) अणु
		priv->rq[i].dev = dev;
		u64_stats_init(&priv->rq[i].stats.syncp);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम veth_मुक्त_queues(काष्ठा net_device *dev)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);

	kमुक्त(priv->rq);
पूर्ण

अटल पूर्णांक veth_dev_init(काष्ठा net_device *dev)
अणु
	पूर्णांक err;

	dev->lstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_lstats);
	अगर (!dev->lstats)
		वापस -ENOMEM;

	err = veth_alloc_queues(dev);
	अगर (err) अणु
		मुक्त_percpu(dev->lstats);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम veth_dev_मुक्त(काष्ठा net_device *dev)
अणु
	veth_मुक्त_queues(dev);
	मुक्त_percpu(dev->lstats);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम veth_poll_controller(काष्ठा net_device *dev)
अणु
	/* veth only receives frames when its peer sends one
	 * Since it has nothing to करो with disabling irqs, we are guaranteed
	 * never to have pending data when we poll क्रम it so
	 * there is nothing to करो here.
	 *
	 * We need this though so netpoll recognizes us as an पूर्णांकerface that
	 * supports polling, which enables bridge devices in virt setups to
	 * still use netconsole
	 */
पूर्ण
#पूर्ण_अगर	/* CONFIG_NET_POLL_CONTROLLER */

अटल पूर्णांक veth_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);
	काष्ठा net_device *peer;
	पूर्णांक अगरlink;

	rcu_पढ़ो_lock();
	peer = rcu_dereference(priv->peer);
	अगरlink = peer ? peer->अगरindex : 0;
	rcu_पढ़ो_unlock();

	वापस अगरlink;
पूर्ण

अटल netdev_features_t veth_fix_features(काष्ठा net_device *dev,
					   netdev_features_t features)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);
	काष्ठा net_device *peer;

	peer = rtnl_dereference(priv->peer);
	अगर (peer) अणु
		काष्ठा veth_priv *peer_priv = netdev_priv(peer);

		अगर (peer_priv->_xdp_prog)
			features &= ~NETIF_F_GSO_SOFTWARE;
	पूर्ण
	अगर (priv->_xdp_prog)
		features |= NETIF_F_GRO;

	वापस features;
पूर्ण

अटल पूर्णांक veth_set_features(काष्ठा net_device *dev,
			     netdev_features_t features)
अणु
	netdev_features_t changed = features ^ dev->features;
	काष्ठा veth_priv *priv = netdev_priv(dev);
	पूर्णांक err;

	अगर (!(changed & NETIF_F_GRO) || !(dev->flags & IFF_UP) || priv->_xdp_prog)
		वापस 0;

	अगर (features & NETIF_F_GRO) अणु
		err = veth_napi_enable(dev);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		veth_napi_del(dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम veth_set_rx_headroom(काष्ठा net_device *dev, पूर्णांक new_hr)
अणु
	काष्ठा veth_priv *peer_priv, *priv = netdev_priv(dev);
	काष्ठा net_device *peer;

	अगर (new_hr < 0)
		new_hr = 0;

	rcu_पढ़ो_lock();
	peer = rcu_dereference(priv->peer);
	अगर (unlikely(!peer))
		जाओ out;

	peer_priv = netdev_priv(peer);
	priv->requested_headroom = new_hr;
	new_hr = max(priv->requested_headroom, peer_priv->requested_headroom);
	dev->needed_headroom = new_hr;
	peer->needed_headroom = new_hr;

out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक veth_xdp_set(काष्ठा net_device *dev, काष्ठा bpf_prog *prog,
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);
	काष्ठा bpf_prog *old_prog;
	काष्ठा net_device *peer;
	अचिन्हित पूर्णांक max_mtu;
	पूर्णांक err;

	old_prog = priv->_xdp_prog;
	priv->_xdp_prog = prog;
	peer = rtnl_dereference(priv->peer);

	अगर (prog) अणु
		अगर (!peer) अणु
			NL_SET_ERR_MSG_MOD(extack, "Cannot set XDP when peer is detached");
			err = -ENOTCONN;
			जाओ err;
		पूर्ण

		max_mtu = PAGE_SIZE - VETH_XDP_HEADROOM -
			  peer->hard_header_len -
			  SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
		अगर (peer->mtu > max_mtu) अणु
			NL_SET_ERR_MSG_MOD(extack, "Peer MTU is too large to set XDP");
			err = -दुस्फल;
			जाओ err;
		पूर्ण

		अगर (dev->real_num_rx_queues < peer->real_num_tx_queues) अणु
			NL_SET_ERR_MSG_MOD(extack, "XDP expects number of rx queues not less than peer tx queues");
			err = -ENOSPC;
			जाओ err;
		पूर्ण

		अगर (dev->flags & IFF_UP) अणु
			err = veth_enable_xdp(dev);
			अगर (err) अणु
				NL_SET_ERR_MSG_MOD(extack, "Setup for XDP failed");
				जाओ err;
			पूर्ण
		पूर्ण

		अगर (!old_prog) अणु
			peer->hw_features &= ~NETIF_F_GSO_SOFTWARE;
			peer->max_mtu = max_mtu;
		पूर्ण
	पूर्ण

	अगर (old_prog) अणु
		अगर (!prog) अणु
			अगर (dev->flags & IFF_UP)
				veth_disable_xdp(dev);

			अगर (peer) अणु
				peer->hw_features |= NETIF_F_GSO_SOFTWARE;
				peer->max_mtu = ETH_MAX_MTU;
			पूर्ण
		पूर्ण
		bpf_prog_put(old_prog);
	पूर्ण

	अगर ((!!old_prog ^ !!prog) && peer)
		netdev_update_features(peer);

	वापस 0;
err:
	priv->_xdp_prog = old_prog;

	वापस err;
पूर्ण

अटल पूर्णांक veth_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस veth_xdp_set(dev, xdp->prog, xdp->extack);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops veth_netdev_ops = अणु
	.nकरो_init            = veth_dev_init,
	.nकरो_खोलो            = veth_खोलो,
	.nकरो_stop            = veth_बंद,
	.nकरो_start_xmit      = veth_xmit,
	.nकरो_get_stats64     = veth_get_stats64,
	.nकरो_set_rx_mode     = veth_set_multicast_list,
	.nकरो_set_mac_address = eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= veth_poll_controller,
#पूर्ण_अगर
	.nकरो_get_अगरlink		= veth_get_अगरlink,
	.nकरो_fix_features	= veth_fix_features,
	.nकरो_set_features	= veth_set_features,
	.nकरो_features_check	= passthru_features_check,
	.nकरो_set_rx_headroom	= veth_set_rx_headroom,
	.nकरो_bpf		= veth_xdp,
	.nकरो_xdp_xmit		= veth_nकरो_xdp_xmit,
	.nकरो_get_peer_dev	= veth_peer_dev,
पूर्ण;

#घोषणा VETH_FEATURES (NETIF_F_SG | NETIF_F_FRAGLIST | NETIF_F_HW_CSUM | \
		       NETIF_F_RXCSUM | NETIF_F_SCTP_CRC | NETIF_F_HIGHDMA | \
		       NETIF_F_GSO_SOFTWARE | NETIF_F_GSO_ENCAP_ALL | \
		       NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX | \
		       NETIF_F_HW_VLAN_STAG_TX | NETIF_F_HW_VLAN_STAG_RX )

अटल व्योम veth_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);

	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	dev->priv_flags |= IFF_NO_QUEUE;
	dev->priv_flags |= IFF_PHONY_HEADROOM;

	dev->netdev_ops = &veth_netdev_ops;
	dev->ethtool_ops = &veth_ethtool_ops;
	dev->features |= NETIF_F_LLTX;
	dev->features |= VETH_FEATURES;
	dev->vlan_features = dev->features &
			     ~(NETIF_F_HW_VLAN_CTAG_TX |
			       NETIF_F_HW_VLAN_STAG_TX |
			       NETIF_F_HW_VLAN_CTAG_RX |
			       NETIF_F_HW_VLAN_STAG_RX);
	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = veth_dev_मुक्त;
	dev->max_mtu = ETH_MAX_MTU;

	dev->hw_features = VETH_FEATURES;
	dev->hw_enc_features = VETH_FEATURES;
	dev->mpls_features = NETIF_F_HW_CSUM | NETIF_F_GSO_SOFTWARE;
पूर्ण

/*
 * netlink पूर्णांकerface
 */

अटल पूर्णांक veth_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			 काष्ठा netlink_ext_ack *extack)
अणु
	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN)
			वापस -EINVAL;
		अगर (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS])))
			वापस -EADDRNOTAVAIL;
	पूर्ण
	अगर (tb[IFLA_MTU]) अणु
		अगर (!is_valid_veth_mtu(nla_get_u32(tb[IFLA_MTU])))
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा rtnl_link_ops veth_link_ops;

अटल व्योम veth_disable_gro(काष्ठा net_device *dev)
अणु
	dev->features &= ~NETIF_F_GRO;
	dev->wanted_features &= ~NETIF_F_GRO;
	netdev_update_features(dev);
पूर्ण

अटल पूर्णांक veth_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;
	काष्ठा net_device *peer;
	काष्ठा veth_priv *priv;
	अक्षर अगरname[IFNAMSIZ];
	काष्ठा nlattr *peer_tb[IFLA_MAX + 1], **tbp;
	अचिन्हित अक्षर name_assign_type;
	काष्ठा अगरinfomsg *अगरmp;
	काष्ठा net *net;

	/*
	 * create and रेजिस्टर peer first
	 */
	अगर (data != शून्य && data[VETH_INFO_PEER] != शून्य) अणु
		काष्ठा nlattr *nla_peer;

		nla_peer = data[VETH_INFO_PEER];
		अगरmp = nla_data(nla_peer);
		err = rtnl_nla_parse_अगरla(peer_tb,
					  nla_data(nla_peer) + माप(काष्ठा अगरinfomsg),
					  nla_len(nla_peer) - माप(काष्ठा अगरinfomsg),
					  शून्य);
		अगर (err < 0)
			वापस err;

		err = veth_validate(peer_tb, शून्य, extack);
		अगर (err < 0)
			वापस err;

		tbp = peer_tb;
	पूर्ण अन्यथा अणु
		अगरmp = शून्य;
		tbp = tb;
	पूर्ण

	अगर (अगरmp && tbp[IFLA_IFNAME]) अणु
		nla_strscpy(अगरname, tbp[IFLA_IFNAME], IFNAMSIZ);
		name_assign_type = NET_NAME_USER;
	पूर्ण अन्यथा अणु
		snम_लिखो(अगरname, IFNAMSIZ, DRV_NAME "%%d");
		name_assign_type = NET_NAME_ENUM;
	पूर्ण

	net = rtnl_link_get_net(src_net, tbp);
	अगर (IS_ERR(net))
		वापस PTR_ERR(net);

	peer = rtnl_create_link(net, अगरname, name_assign_type,
				&veth_link_ops, tbp, extack);
	अगर (IS_ERR(peer)) अणु
		put_net(net);
		वापस PTR_ERR(peer);
	पूर्ण

	अगर (!अगरmp || !tbp[IFLA_ADDRESS])
		eth_hw_addr_अक्रमom(peer);

	अगर (अगरmp && (dev->अगरindex != 0))
		peer->अगरindex = अगरmp->अगरi_index;

	peer->gso_max_size = dev->gso_max_size;
	peer->gso_max_segs = dev->gso_max_segs;

	err = रेजिस्टर_netdevice(peer);
	put_net(net);
	net = शून्य;
	अगर (err < 0)
		जाओ err_रेजिस्टर_peer;

	/* keep GRO disabled by शेष to be consistent with the established
	 * veth behavior
	 */
	veth_disable_gro(peer);
	netअगर_carrier_off(peer);

	err = rtnl_configure_link(peer, अगरmp);
	अगर (err < 0)
		जाओ err_configure_peer;

	/*
	 * रेजिस्टर dev last
	 *
	 * note, that since we've registered new device the dev's name
	 * should be re-allocated
	 */

	अगर (tb[IFLA_ADDRESS] == शून्य)
		eth_hw_addr_अक्रमom(dev);

	अगर (tb[IFLA_IFNAME])
		nla_strscpy(dev->name, tb[IFLA_IFNAME], IFNAMSIZ);
	अन्यथा
		snम_लिखो(dev->name, IFNAMSIZ, DRV_NAME "%%d");

	err = रेजिस्टर_netdevice(dev);
	अगर (err < 0)
		जाओ err_रेजिस्टर_dev;

	netअगर_carrier_off(dev);

	/*
	 * tie the deviced together
	 */

	priv = netdev_priv(dev);
	rcu_assign_poपूर्णांकer(priv->peer, peer);

	priv = netdev_priv(peer);
	rcu_assign_poपूर्णांकer(priv->peer, dev);

	veth_disable_gro(dev);
	वापस 0;

err_रेजिस्टर_dev:
	/* nothing to करो */
err_configure_peer:
	unरेजिस्टर_netdevice(peer);
	वापस err;

err_रेजिस्टर_peer:
	मुक्त_netdev(peer);
	वापस err;
पूर्ण

अटल व्योम veth_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा veth_priv *priv;
	काष्ठा net_device *peer;

	priv = netdev_priv(dev);
	peer = rtnl_dereference(priv->peer);

	/* Note : dellink() is called from शेष_device_निकास_batch(),
	 * beक्रमe a rcu_synchronize() poपूर्णांक. The devices are guaranteed
	 * not being मुक्तd beक्रमe one RCU grace period.
	 */
	RCU_INIT_POINTER(priv->peer, शून्य);
	unरेजिस्टर_netdevice_queue(dev, head);

	अगर (peer) अणु
		priv = netdev_priv(peer);
		RCU_INIT_POINTER(priv->peer, शून्य);
		unरेजिस्टर_netdevice_queue(peer, head);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nla_policy veth_policy[VETH_INFO_MAX + 1] = अणु
	[VETH_INFO_PEER]	= अणु .len = माप(काष्ठा अगरinfomsg) पूर्ण,
पूर्ण;

अटल काष्ठा net *veth_get_link_net(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा veth_priv *priv = netdev_priv(dev);
	काष्ठा net_device *peer = rtnl_dereference(priv->peer);

	वापस peer ? dev_net(peer) : dev_net(dev);
पूर्ण

अटल काष्ठा rtnl_link_ops veth_link_ops = अणु
	.kind		= DRV_NAME,
	.priv_size	= माप(काष्ठा veth_priv),
	.setup		= veth_setup,
	.validate	= veth_validate,
	.newlink	= veth_newlink,
	.dellink	= veth_dellink,
	.policy		= veth_policy,
	.maxtype	= VETH_INFO_MAX,
	.get_link_net	= veth_get_link_net,
पूर्ण;

/*
 * init/fini
 */

अटल __init पूर्णांक veth_init(व्योम)
अणु
	वापस rtnl_link_रेजिस्टर(&veth_link_ops);
पूर्ण

अटल __निकास व्योम veth_निकास(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&veth_link_ops);
पूर्ण

module_init(veth_init);
module_निकास(veth_निकास);

MODULE_DESCRIPTION("Virtual Ethernet Tunnel");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_RTNL_LINK(DRV_NAME);
