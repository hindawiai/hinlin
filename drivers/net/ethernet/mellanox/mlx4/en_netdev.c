<शैली गुरु>
/*
 * Copyright (c) 2007 Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#समावेश <linux/bpf.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/tcp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/hash.h>
#समावेश <net/ip.h>
#समावेश <net/vxlan.h>
#समावेश <net/devlink.h>

#समावेश <linux/mlx4/driver.h>
#समावेश <linux/mlx4/device.h>
#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/mlx4/cq.h>

#समावेश "mlx4_en.h"
#समावेश "en_port.h"

#घोषणा MLX4_EN_MAX_XDP_MTU ((पूर्णांक)(PAGE_SIZE - ETH_HLEN - (2 * VLAN_HLEN) - \
				XDP_PACKET_HEADROOM -			    \
				SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info))))

पूर्णांक mlx4_en_setup_tc(काष्ठा net_device *dev, u8 up)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	पूर्णांक i;
	अचिन्हित पूर्णांक offset = 0;

	अगर (up && up != MLX4_EN_NUM_UP_HIGH)
		वापस -EINVAL;

	netdev_set_num_tc(dev, up);
	netअगर_set_real_num_tx_queues(dev, priv->tx_ring_num[TX]);
	/* Partition Tx queues evenly amongst UP's */
	क्रम (i = 0; i < up; i++) अणु
		netdev_set_tc_queue(dev, i, priv->num_tx_rings_p_up, offset);
		offset += priv->num_tx_rings_p_up;
	पूर्ण

#अगर_घोषित CONFIG_MLX4_EN_DCB
	अगर (!mlx4_is_slave(priv->mdev->dev)) अणु
		अगर (up) अणु
			अगर (priv->dcbx_cap)
				priv->flags |= MLX4_EN_FLAG_DCB_ENABLED;
		पूर्ण अन्यथा अणु
			priv->flags &= ~MLX4_EN_FLAG_DCB_ENABLED;
			priv->cee_config.pfc_state = false;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_MLX4_EN_DCB */

	वापस 0;
पूर्ण

पूर्णांक mlx4_en_alloc_tx_queue_per_tc(काष्ठा net_device *dev, u8 tc)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_port_profile new_prof;
	काष्ठा mlx4_en_priv *पंचांगp;
	पूर्णांक total_count;
	पूर्णांक port_up = 0;
	पूर्णांक err = 0;

	पंचांगp = kzalloc(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	mutex_lock(&mdev->state_lock);
	स_नकल(&new_prof, priv->prof, माप(काष्ठा mlx4_en_port_profile));
	new_prof.num_up = (tc == 0) ? MLX4_EN_NUM_UP_LOW :
				      MLX4_EN_NUM_UP_HIGH;
	new_prof.tx_ring_num[TX] = new_prof.num_tx_rings_p_up *
				   new_prof.num_up;
	total_count = new_prof.tx_ring_num[TX] + new_prof.tx_ring_num[TX_XDP];
	अगर (total_count > MAX_TX_RINGS) अणु
		err = -EINVAL;
		en_err(priv,
		       "Total number of TX and XDP rings (%d) exceeds the maximum supported (%d)\n",
		       total_count, MAX_TX_RINGS);
		जाओ out;
	पूर्ण
	err = mlx4_en_try_alloc_resources(priv, पंचांगp, &new_prof, true);
	अगर (err)
		जाओ out;

	अगर (priv->port_up) अणु
		port_up = 1;
		mlx4_en_stop_port(dev, 1);
	पूर्ण

	mlx4_en_safe_replace_resources(priv, पंचांगp);
	अगर (port_up) अणु
		err = mlx4_en_start_port(dev);
		अगर (err) अणु
			en_err(priv, "Failed starting port for setup TC\n");
			जाओ out;
		पूर्ण
	पूर्ण

	err = mlx4_en_setup_tc(dev, tc);
out:
	mutex_unlock(&mdev->state_lock);
	kमुक्त(पंचांगp);
	वापस err;
पूर्ण

अटल पूर्णांक __mlx4_en_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			      व्योम *type_data)
अणु
	काष्ठा tc_mqprio_qopt *mqprio = type_data;

	अगर (type != TC_SETUP_QDISC_MQPRIO)
		वापस -EOPNOTSUPP;

	अगर (mqprio->num_tc && mqprio->num_tc != MLX4_EN_NUM_UP_HIGH)
		वापस -EINVAL;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;

	वापस mlx4_en_alloc_tx_queue_per_tc(dev, mqprio->num_tc);
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL

काष्ठा mlx4_en_filter अणु
	काष्ठा list_head next;
	काष्ठा work_काष्ठा work;

	u8     ip_proto;
	__be32 src_ip;
	__be32 dst_ip;
	__be16 src_port;
	__be16 dst_port;

	पूर्णांक rxq_index;
	काष्ठा mlx4_en_priv *priv;
	u32 flow_id;			/* RFS infraकाष्ठाure id */
	पूर्णांक id;				/* mlx4_en driver id */
	u64 reg_id;			/* Flow steering API id */
	u8 activated;			/* Used to prevent expiry beक्रमe filter
					 * is attached
					 */
	काष्ठा hlist_node filter_chain;
पूर्ण;

अटल व्योम mlx4_en_filter_rfs_expire(काष्ठा mlx4_en_priv *priv);

अटल क्रमागत mlx4_net_trans_rule_id mlx4_ip_proto_to_trans_rule_id(u8 ip_proto)
अणु
	चयन (ip_proto) अणु
	हाल IPPROTO_UDP:
		वापस MLX4_NET_TRANS_RULE_ID_UDP;
	हाल IPPROTO_TCP:
		वापस MLX4_NET_TRANS_RULE_ID_TCP;
	शेष:
		वापस MLX4_NET_TRANS_RULE_NUM;
	पूर्ण
पूर्ण;

/* Must not acquire state_lock, as its corresponding work_sync
 * is करोne under it.
 */
अटल व्योम mlx4_en_filter_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx4_en_filter *filter = container_of(work,
						     काष्ठा mlx4_en_filter,
						     work);
	काष्ठा mlx4_en_priv *priv = filter->priv;
	काष्ठा mlx4_spec_list spec_tcp_udp = अणु
		.id = mlx4_ip_proto_to_trans_rule_id(filter->ip_proto),
		अणु
			.tcp_udp = अणु
				.dst_port = filter->dst_port,
				.dst_port_msk = (__क्रमce __be16)-1,
				.src_port = filter->src_port,
				.src_port_msk = (__क्रमce __be16)-1,
			पूर्ण,
		पूर्ण,
	पूर्ण;
	काष्ठा mlx4_spec_list spec_ip = अणु
		.id = MLX4_NET_TRANS_RULE_ID_IPV4,
		अणु
			.ipv4 = अणु
				.dst_ip = filter->dst_ip,
				.dst_ip_msk = (__क्रमce __be32)-1,
				.src_ip = filter->src_ip,
				.src_ip_msk = (__क्रमce __be32)-1,
			पूर्ण,
		पूर्ण,
	पूर्ण;
	काष्ठा mlx4_spec_list spec_eth = अणु
		.id = MLX4_NET_TRANS_RULE_ID_ETH,
	पूर्ण;
	काष्ठा mlx4_net_trans_rule rule = अणु
		.list = LIST_HEAD_INIT(rule.list),
		.queue_mode = MLX4_NET_TRANS_Q_LIFO,
		.exclusive = 1,
		.allow_loopback = 1,
		.promisc_mode = MLX4_FS_REGULAR,
		.port = priv->port,
		.priority = MLX4_DOMAIN_RFS,
	पूर्ण;
	पूर्णांक rc;
	__be64 mac_mask = cpu_to_be64(MLX4_MAC_MASK << 16);

	अगर (spec_tcp_udp.id >= MLX4_NET_TRANS_RULE_NUM) अणु
		en_warn(priv, "RFS: ignoring unsupported ip protocol (%d)\n",
			filter->ip_proto);
		जाओ ignore;
	पूर्ण
	list_add_tail(&spec_eth.list, &rule.list);
	list_add_tail(&spec_ip.list, &rule.list);
	list_add_tail(&spec_tcp_udp.list, &rule.list);

	rule.qpn = priv->rss_map.qps[filter->rxq_index].qpn;
	स_नकल(spec_eth.eth.dst_mac, priv->dev->dev_addr, ETH_ALEN);
	स_नकल(spec_eth.eth.dst_mac_msk, &mac_mask, ETH_ALEN);

	filter->activated = 0;

	अगर (filter->reg_id) अणु
		rc = mlx4_flow_detach(priv->mdev->dev, filter->reg_id);
		अगर (rc && rc != -ENOENT)
			en_err(priv, "Error detaching flow. rc = %d\n", rc);
	पूर्ण

	rc = mlx4_flow_attach(priv->mdev->dev, &rule, &filter->reg_id);
	अगर (rc)
		en_err(priv, "Error attaching flow. err = %d\n", rc);

ignore:
	mlx4_en_filter_rfs_expire(priv);

	filter->activated = 1;
पूर्ण

अटल अंतरभूत काष्ठा hlist_head *
filter_hash_bucket(काष्ठा mlx4_en_priv *priv, __be32 src_ip, __be32 dst_ip,
		   __be16 src_port, __be16 dst_port)
अणु
	अचिन्हित दीर्घ l;
	पूर्णांक bucket_idx;

	l = (__क्रमce अचिन्हित दीर्घ)src_port |
	    ((__क्रमce अचिन्हित दीर्घ)dst_port << 2);
	l ^= (__क्रमce अचिन्हित दीर्घ)(src_ip ^ dst_ip);

	bucket_idx = hash_दीर्घ(l, MLX4_EN_FILTER_HASH_SHIFT);

	वापस &priv->filter_hash[bucket_idx];
पूर्ण

अटल काष्ठा mlx4_en_filter *
mlx4_en_filter_alloc(काष्ठा mlx4_en_priv *priv, पूर्णांक rxq_index, __be32 src_ip,
		     __be32 dst_ip, u8 ip_proto, __be16 src_port,
		     __be16 dst_port, u32 flow_id)
अणु
	काष्ठा mlx4_en_filter *filter = शून्य;

	filter = kzalloc(माप(काष्ठा mlx4_en_filter), GFP_ATOMIC);
	अगर (!filter)
		वापस शून्य;

	filter->priv = priv;
	filter->rxq_index = rxq_index;
	INIT_WORK(&filter->work, mlx4_en_filter_work);

	filter->src_ip = src_ip;
	filter->dst_ip = dst_ip;
	filter->ip_proto = ip_proto;
	filter->src_port = src_port;
	filter->dst_port = dst_port;

	filter->flow_id = flow_id;

	filter->id = priv->last_filter_id++ % RPS_NO_FILTER;

	list_add_tail(&filter->next, &priv->filters);
	hlist_add_head(&filter->filter_chain,
		       filter_hash_bucket(priv, src_ip, dst_ip, src_port,
					  dst_port));

	वापस filter;
पूर्ण

अटल व्योम mlx4_en_filter_मुक्त(काष्ठा mlx4_en_filter *filter)
अणु
	काष्ठा mlx4_en_priv *priv = filter->priv;
	पूर्णांक rc;

	list_del(&filter->next);

	rc = mlx4_flow_detach(priv->mdev->dev, filter->reg_id);
	अगर (rc && rc != -ENOENT)
		en_err(priv, "Error detaching flow. rc = %d\n", rc);

	kमुक्त(filter);
पूर्ण

अटल अंतरभूत काष्ठा mlx4_en_filter *
mlx4_en_filter_find(काष्ठा mlx4_en_priv *priv, __be32 src_ip, __be32 dst_ip,
		    u8 ip_proto, __be16 src_port, __be16 dst_port)
अणु
	काष्ठा mlx4_en_filter *filter;
	काष्ठा mlx4_en_filter *ret = शून्य;

	hlist_क्रम_each_entry(filter,
			     filter_hash_bucket(priv, src_ip, dst_ip,
						src_port, dst_port),
			     filter_chain) अणु
		अगर (filter->src_ip == src_ip &&
		    filter->dst_ip == dst_ip &&
		    filter->ip_proto == ip_proto &&
		    filter->src_port == src_port &&
		    filter->dst_port == dst_port) अणु
			ret = filter;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
mlx4_en_filter_rfs(काष्ठा net_device *net_dev, स्थिर काष्ठा sk_buff *skb,
		   u16 rxq_index, u32 flow_id)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(net_dev);
	काष्ठा mlx4_en_filter *filter;
	स्थिर काष्ठा iphdr *ip;
	स्थिर __be16 *ports;
	u8 ip_proto;
	__be32 src_ip;
	__be32 dst_ip;
	__be16 src_port;
	__be16 dst_port;
	पूर्णांक nhoff = skb_network_offset(skb);
	पूर्णांक ret = 0;

	अगर (skb->protocol != htons(ETH_P_IP))
		वापस -EPROTONOSUPPORT;

	ip = (स्थिर काष्ठा iphdr *)(skb->data + nhoff);
	अगर (ip_is_fragment(ip))
		वापस -EPROTONOSUPPORT;

	अगर ((ip->protocol != IPPROTO_TCP) && (ip->protocol != IPPROTO_UDP))
		वापस -EPROTONOSUPPORT;
	ports = (स्थिर __be16 *)(skb->data + nhoff + 4 * ip->ihl);

	ip_proto = ip->protocol;
	src_ip = ip->saddr;
	dst_ip = ip->daddr;
	src_port = ports[0];
	dst_port = ports[1];

	spin_lock_bh(&priv->filters_lock);
	filter = mlx4_en_filter_find(priv, src_ip, dst_ip, ip_proto,
				     src_port, dst_port);
	अगर (filter) अणु
		अगर (filter->rxq_index == rxq_index)
			जाओ out;

		filter->rxq_index = rxq_index;
	पूर्ण अन्यथा अणु
		filter = mlx4_en_filter_alloc(priv, rxq_index,
					      src_ip, dst_ip, ip_proto,
					      src_port, dst_port, flow_id);
		अगर (!filter) अणु
			ret = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण

	queue_work(priv->mdev->workqueue, &filter->work);

out:
	ret = filter->id;
err:
	spin_unlock_bh(&priv->filters_lock);

	वापस ret;
पूर्ण

व्योम mlx4_en_cleanup_filters(काष्ठा mlx4_en_priv *priv)
अणु
	काष्ठा mlx4_en_filter *filter, *पंचांगp;
	LIST_HEAD(del_list);

	spin_lock_bh(&priv->filters_lock);
	list_क्रम_each_entry_safe(filter, पंचांगp, &priv->filters, next) अणु
		list_move(&filter->next, &del_list);
		hlist_del(&filter->filter_chain);
	पूर्ण
	spin_unlock_bh(&priv->filters_lock);

	list_क्रम_each_entry_safe(filter, पंचांगp, &del_list, next) अणु
		cancel_work_sync(&filter->work);
		mlx4_en_filter_मुक्त(filter);
	पूर्ण
पूर्ण

अटल व्योम mlx4_en_filter_rfs_expire(काष्ठा mlx4_en_priv *priv)
अणु
	काष्ठा mlx4_en_filter *filter = शून्य, *पंचांगp, *last_filter = शून्य;
	LIST_HEAD(del_list);
	पूर्णांक i = 0;

	spin_lock_bh(&priv->filters_lock);
	list_क्रम_each_entry_safe(filter, पंचांगp, &priv->filters, next) अणु
		अगर (i > MLX4_EN_FILTER_EXPIRY_QUOTA)
			अवरोध;

		अगर (filter->activated &&
		    !work_pending(&filter->work) &&
		    rps_may_expire_flow(priv->dev,
					filter->rxq_index, filter->flow_id,
					filter->id)) अणु
			list_move(&filter->next, &del_list);
			hlist_del(&filter->filter_chain);
		पूर्ण अन्यथा
			last_filter = filter;

		i++;
	पूर्ण

	अगर (last_filter && (&last_filter->next != priv->filters.next))
		list_move(&priv->filters, &last_filter->next);

	spin_unlock_bh(&priv->filters_lock);

	list_क्रम_each_entry_safe(filter, पंचांगp, &del_list, next)
		mlx4_en_filter_मुक्त(filter);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mlx4_en_vlan_rx_add_vid(काष्ठा net_device *dev,
				   __be16 proto, u16 vid)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक err;
	पूर्णांक idx;

	en_dbg(HW, priv, "adding VLAN:%d\n", vid);

	set_bit(vid, priv->active_vlans);

	/* Add VID to port VLAN filter */
	mutex_lock(&mdev->state_lock);
	अगर (mdev->device_up && priv->port_up) अणु
		err = mlx4_SET_VLAN_FLTR(mdev->dev, priv);
		अगर (err) अणु
			en_err(priv, "Failed configuring VLAN filter\n");
			जाओ out;
		पूर्ण
	पूर्ण
	err = mlx4_रेजिस्टर_vlan(mdev->dev, priv->port, vid, &idx);
	अगर (err)
		en_dbg(HW, priv, "Failed adding vlan %d\n", vid);

out:
	mutex_unlock(&mdev->state_lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_en_vlan_rx_समाप्त_vid(काष्ठा net_device *dev,
				    __be16 proto, u16 vid)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक err = 0;

	en_dbg(HW, priv, "Killing VID:%d\n", vid);

	clear_bit(vid, priv->active_vlans);

	/* Remove VID from port VLAN filter */
	mutex_lock(&mdev->state_lock);
	mlx4_unरेजिस्टर_vlan(mdev->dev, priv->port, vid);

	अगर (mdev->device_up && priv->port_up) अणु
		err = mlx4_SET_VLAN_FLTR(mdev->dev, priv);
		अगर (err)
			en_err(priv, "Failed configuring VLAN filter\n");
	पूर्ण
	mutex_unlock(&mdev->state_lock);

	वापस err;
पूर्ण

अटल व्योम mlx4_en_u64_to_mac(अचिन्हित अक्षर dst_mac[ETH_ALEN + 2], u64 src_mac)
अणु
	पूर्णांक i;
	क्रम (i = ETH_ALEN - 1; i >= 0; --i) अणु
		dst_mac[i] = src_mac & 0xff;
		src_mac >>= 8;
	पूर्ण
	स_रखो(&dst_mac[ETH_ALEN], 0, 2);
पूर्ण


अटल पूर्णांक mlx4_en_tunnel_steer_add(काष्ठा mlx4_en_priv *priv, अचिन्हित अक्षर *addr,
				    पूर्णांक qpn, u64 *reg_id)
अणु
	पूर्णांक err;

	अगर (priv->mdev->dev->caps.tunnel_offload_mode != MLX4_TUNNEL_OFFLOAD_MODE_VXLAN ||
	    priv->mdev->dev->caps.dmfs_high_steer_mode == MLX4_STEERING_DMFS_A0_STATIC)
		वापस 0; /* करो nothing */

	err = mlx4_tunnel_steer_add(priv->mdev->dev, addr, priv->port, qpn,
				    MLX4_DOMAIN_NIC, reg_id);
	अगर (err) अणु
		en_err(priv, "failed to add vxlan steering rule, err %d\n", err);
		वापस err;
	पूर्ण
	en_dbg(DRV, priv, "added vxlan steering rule, mac %pM reg_id %llx\n", addr, *reg_id);
	वापस 0;
पूर्ण


अटल पूर्णांक mlx4_en_uc_steer_add(काष्ठा mlx4_en_priv *priv,
				अचिन्हित अक्षर *mac, पूर्णांक *qpn, u64 *reg_id)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_dev *dev = mdev->dev;
	पूर्णांक err;

	चयन (dev->caps.steering_mode) अणु
	हाल MLX4_STEERING_MODE_B0: अणु
		काष्ठा mlx4_qp qp;
		u8 gid[16] = अणु0पूर्ण;

		qp.qpn = *qpn;
		स_नकल(&gid[10], mac, ETH_ALEN);
		gid[5] = priv->port;

		err = mlx4_unicast_attach(dev, &qp, gid, 0, MLX4_PROT_ETH);
		अवरोध;
	पूर्ण
	हाल MLX4_STEERING_MODE_DEVICE_MANAGED: अणु
		काष्ठा mlx4_spec_list spec_eth = अणु अणुशून्यपूर्ण पूर्ण;
		__be64 mac_mask = cpu_to_be64(MLX4_MAC_MASK << 16);

		काष्ठा mlx4_net_trans_rule rule = अणु
			.queue_mode = MLX4_NET_TRANS_Q_FIFO,
			.exclusive = 0,
			.allow_loopback = 1,
			.promisc_mode = MLX4_FS_REGULAR,
			.priority = MLX4_DOMAIN_NIC,
		पूर्ण;

		rule.port = priv->port;
		rule.qpn = *qpn;
		INIT_LIST_HEAD(&rule.list);

		spec_eth.id = MLX4_NET_TRANS_RULE_ID_ETH;
		स_नकल(spec_eth.eth.dst_mac, mac, ETH_ALEN);
		स_नकल(spec_eth.eth.dst_mac_msk, &mac_mask, ETH_ALEN);
		list_add_tail(&spec_eth.list, &rule.list);

		err = mlx4_flow_attach(dev, &rule, reg_id);
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (err)
		en_warn(priv, "Failed Attaching Unicast\n");

	वापस err;
पूर्ण

अटल व्योम mlx4_en_uc_steer_release(काष्ठा mlx4_en_priv *priv,
				     अचिन्हित अक्षर *mac, पूर्णांक qpn, u64 reg_id)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_dev *dev = mdev->dev;

	चयन (dev->caps.steering_mode) अणु
	हाल MLX4_STEERING_MODE_B0: अणु
		काष्ठा mlx4_qp qp;
		u8 gid[16] = अणु0पूर्ण;

		qp.qpn = qpn;
		स_नकल(&gid[10], mac, ETH_ALEN);
		gid[5] = priv->port;

		mlx4_unicast_detach(dev, &qp, gid, MLX4_PROT_ETH);
		अवरोध;
	पूर्ण
	हाल MLX4_STEERING_MODE_DEVICE_MANAGED: अणु
		mlx4_flow_detach(dev, reg_id);
		अवरोध;
	पूर्ण
	शेष:
		en_err(priv, "Invalid steering mode.\n");
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_en_get_qp(काष्ठा mlx4_en_priv *priv)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_dev *dev = mdev->dev;
	पूर्णांक index = 0;
	पूर्णांक err = 0;
	पूर्णांक *qpn = &priv->base_qpn;
	u64 mac = mlx4_mac_to_u64(priv->dev->dev_addr);

	en_dbg(DRV, priv, "Registering MAC: %pM for adding\n",
	       priv->dev->dev_addr);
	index = mlx4_रेजिस्टर_mac(dev, priv->port, mac);
	अगर (index < 0) अणु
		err = index;
		en_err(priv, "Failed adding MAC: %pM\n",
		       priv->dev->dev_addr);
		वापस err;
	पूर्ण

	en_info(priv, "Steering Mode %d\n", dev->caps.steering_mode);

	अगर (dev->caps.steering_mode == MLX4_STEERING_MODE_A0) अणु
		पूर्णांक base_qpn = mlx4_get_base_qpn(dev, priv->port);
		*qpn = base_qpn + index;
		वापस 0;
	पूर्ण

	err = mlx4_qp_reserve_range(dev, 1, 1, qpn, MLX4_RESERVE_A0_QP,
				    MLX4_RES_USAGE_DRIVER);
	en_dbg(DRV, priv, "Reserved qp %d\n", *qpn);
	अगर (err) अणु
		en_err(priv, "Failed to reserve qp for mac registration\n");
		mlx4_unरेजिस्टर_mac(dev, priv->port, mac);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlx4_en_put_qp(काष्ठा mlx4_en_priv *priv)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_dev *dev = mdev->dev;
	पूर्णांक qpn = priv->base_qpn;

	अगर (dev->caps.steering_mode == MLX4_STEERING_MODE_A0) अणु
		u64 mac = mlx4_mac_to_u64(priv->dev->dev_addr);
		en_dbg(DRV, priv, "Registering MAC: %pM for deleting\n",
		       priv->dev->dev_addr);
		mlx4_unरेजिस्टर_mac(dev, priv->port, mac);
	पूर्ण अन्यथा अणु
		en_dbg(DRV, priv, "Releasing qp: port %d, qpn %d\n",
		       priv->port, qpn);
		mlx4_qp_release_range(dev, qpn, 1);
		priv->flags &= ~MLX4_EN_FLAG_FORCE_PROMISC;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_en_replace_mac(काष्ठा mlx4_en_priv *priv, पूर्णांक qpn,
			       अचिन्हित अक्षर *new_mac, अचिन्हित अक्षर *prev_mac)
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_dev *dev = mdev->dev;
	पूर्णांक err = 0;
	u64 new_mac_u64 = mlx4_mac_to_u64(new_mac);

	अगर (dev->caps.steering_mode != MLX4_STEERING_MODE_A0) अणु
		काष्ठा hlist_head *bucket;
		अचिन्हित पूर्णांक mac_hash;
		काष्ठा mlx4_mac_entry *entry;
		काष्ठा hlist_node *पंचांगp;
		u64 prev_mac_u64 = mlx4_mac_to_u64(prev_mac);

		bucket = &priv->mac_hash[prev_mac[MLX4_EN_MAC_HASH_IDX]];
		hlist_क्रम_each_entry_safe(entry, पंचांगp, bucket, hlist) अणु
			अगर (ether_addr_equal_64bits(entry->mac, prev_mac)) अणु
				mlx4_en_uc_steer_release(priv, entry->mac,
							 qpn, entry->reg_id);
				mlx4_unरेजिस्टर_mac(dev, priv->port,
						    prev_mac_u64);
				hlist_del_rcu(&entry->hlist);
				synchronize_rcu();
				स_नकल(entry->mac, new_mac, ETH_ALEN);
				entry->reg_id = 0;
				mac_hash = new_mac[MLX4_EN_MAC_HASH_IDX];
				hlist_add_head_rcu(&entry->hlist,
						   &priv->mac_hash[mac_hash]);
				mlx4_रेजिस्टर_mac(dev, priv->port, new_mac_u64);
				err = mlx4_en_uc_steer_add(priv, new_mac,
							   &qpn,
							   &entry->reg_id);
				अगर (err)
					वापस err;
				अगर (priv->tunnel_reg_id) अणु
					mlx4_flow_detach(priv->mdev->dev, priv->tunnel_reg_id);
					priv->tunnel_reg_id = 0;
				पूर्ण
				err = mlx4_en_tunnel_steer_add(priv, new_mac, qpn,
							       &priv->tunnel_reg_id);
				वापस err;
			पूर्ण
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	वापस __mlx4_replace_mac(dev, priv->port, qpn, new_mac_u64);
पूर्ण

अटल व्योम mlx4_en_update_user_mac(काष्ठा mlx4_en_priv *priv,
				    अचिन्हित अक्षर new_mac[ETH_ALEN + 2])
अणु
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक err;

	अगर (!(mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_USER_MAC_EN))
		वापस;

	err = mlx4_SET_PORT_user_mac(mdev->dev, priv->port, new_mac);
	अगर (err)
		en_err(priv, "Failed to pass user MAC(%pM) to Firmware for port %d, with error %d\n",
		       new_mac, priv->port, err);
पूर्ण

अटल पूर्णांक mlx4_en_करो_set_mac(काष्ठा mlx4_en_priv *priv,
			      अचिन्हित अक्षर new_mac[ETH_ALEN + 2])
अणु
	पूर्णांक err = 0;

	अगर (priv->port_up) अणु
		/* Remove old MAC and insert the new one */
		err = mlx4_en_replace_mac(priv, priv->base_qpn,
					  new_mac, priv->current_mac);
		अगर (err)
			en_err(priv, "Failed changing HW MAC address\n");
	पूर्ण अन्यथा
		en_dbg(HW, priv, "Port is down while registering mac, exiting...\n");

	अगर (!err)
		स_नकल(priv->current_mac, new_mac, माप(priv->current_mac));

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_en_set_mac(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा sockaddr *saddr = addr;
	अचिन्हित अक्षर new_mac[ETH_ALEN + 2];
	पूर्णांक err;

	अगर (!is_valid_ether_addr(saddr->sa_data))
		वापस -EADDRNOTAVAIL;

	mutex_lock(&mdev->state_lock);
	स_नकल(new_mac, saddr->sa_data, ETH_ALEN);
	err = mlx4_en_करो_set_mac(priv, new_mac);
	अगर (err)
		जाओ out;

	स_नकल(dev->dev_addr, saddr->sa_data, ETH_ALEN);
	mlx4_en_update_user_mac(priv, new_mac);
out:
	mutex_unlock(&mdev->state_lock);

	वापस err;
पूर्ण

अटल व्योम mlx4_en_clear_list(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_mc_list *पंचांगp, *mc_to_del;

	list_क्रम_each_entry_safe(mc_to_del, पंचांगp, &priv->mc_list, list) अणु
		list_del(&mc_to_del->list);
		kमुक्त(mc_to_del);
	पूर्ण
पूर्ण

अटल व्योम mlx4_en_cache_mclist(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;
	काष्ठा mlx4_en_mc_list *पंचांगp;

	mlx4_en_clear_list(dev);
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		पंचांगp = kzalloc(माप(काष्ठा mlx4_en_mc_list), GFP_ATOMIC);
		अगर (!पंचांगp) अणु
			mlx4_en_clear_list(dev);
			वापस;
		पूर्ण
		स_नकल(पंचांगp->addr, ha->addr, ETH_ALEN);
		list_add_tail(&पंचांगp->list, &priv->mc_list);
	पूर्ण
पूर्ण

अटल व्योम update_mclist_flags(काष्ठा mlx4_en_priv *priv,
				काष्ठा list_head *dst,
				काष्ठा list_head *src)
अणु
	काष्ठा mlx4_en_mc_list *dst_पंचांगp, *src_पंचांगp, *new_mc;
	bool found;

	/* Find all the entries that should be हटाओd from dst,
	 * These are the entries that are not found in src
	 */
	list_क्रम_each_entry(dst_पंचांगp, dst, list) अणु
		found = false;
		list_क्रम_each_entry(src_पंचांगp, src, list) अणु
			अगर (ether_addr_equal(dst_पंचांगp->addr, src_पंचांगp->addr)) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!found)
			dst_पंचांगp->action = MCLIST_REM;
	पूर्ण

	/* Add entries that exist in src but not in dst
	 * mark them as need to add
	 */
	list_क्रम_each_entry(src_पंचांगp, src, list) अणु
		found = false;
		list_क्रम_each_entry(dst_पंचांगp, dst, list) अणु
			अगर (ether_addr_equal(dst_पंचांगp->addr, src_पंचांगp->addr)) अणु
				dst_पंचांगp->action = MCLIST_NONE;
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!found) अणु
			new_mc = kmemdup(src_पंचांगp,
					 माप(काष्ठा mlx4_en_mc_list),
					 GFP_KERNEL);
			अगर (!new_mc)
				वापस;

			new_mc->action = MCLIST_ADD;
			list_add_tail(&new_mc->list, dst);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mlx4_en_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	अगर (!priv->port_up)
		वापस;

	queue_work(priv->mdev->workqueue, &priv->rx_mode_task);
पूर्ण

अटल व्योम mlx4_en_set_promisc_mode(काष्ठा mlx4_en_priv *priv,
				     काष्ठा mlx4_en_dev *mdev)
अणु
	पूर्णांक err = 0;

	अगर (!(priv->flags & MLX4_EN_FLAG_PROMISC)) अणु
		अगर (netअगर_msg_rx_status(priv))
			en_warn(priv, "Entering promiscuous mode\n");
		priv->flags |= MLX4_EN_FLAG_PROMISC;

		/* Enable promiscouos mode */
		चयन (mdev->dev->caps.steering_mode) अणु
		हाल MLX4_STEERING_MODE_DEVICE_MANAGED:
			err = mlx4_flow_steer_promisc_add(mdev->dev,
							  priv->port,
							  priv->base_qpn,
							  MLX4_FS_ALL_DEFAULT);
			अगर (err)
				en_err(priv, "Failed enabling promiscuous mode\n");
			priv->flags |= MLX4_EN_FLAG_MC_PROMISC;
			अवरोध;

		हाल MLX4_STEERING_MODE_B0:
			err = mlx4_unicast_promisc_add(mdev->dev,
						       priv->base_qpn,
						       priv->port);
			अगर (err)
				en_err(priv, "Failed enabling unicast promiscuous mode\n");

			/* Add the शेष qp number as multicast
			 * promisc
			 */
			अगर (!(priv->flags & MLX4_EN_FLAG_MC_PROMISC)) अणु
				err = mlx4_multicast_promisc_add(mdev->dev,
								 priv->base_qpn,
								 priv->port);
				अगर (err)
					en_err(priv, "Failed enabling multicast promiscuous mode\n");
				priv->flags |= MLX4_EN_FLAG_MC_PROMISC;
			पूर्ण
			अवरोध;

		हाल MLX4_STEERING_MODE_A0:
			err = mlx4_SET_PORT_qpn_calc(mdev->dev,
						     priv->port,
						     priv->base_qpn,
						     1);
			अगर (err)
				en_err(priv, "Failed enabling promiscuous mode\n");
			अवरोध;
		पूर्ण

		/* Disable port multicast filter (unconditionally) */
		err = mlx4_SET_MCAST_FLTR(mdev->dev, priv->port, 0,
					  0, MLX4_MCAST_DISABLE);
		अगर (err)
			en_err(priv, "Failed disabling multicast filter\n");
	पूर्ण
पूर्ण

अटल व्योम mlx4_en_clear_promisc_mode(काष्ठा mlx4_en_priv *priv,
				       काष्ठा mlx4_en_dev *mdev)
अणु
	पूर्णांक err = 0;

	अगर (netअगर_msg_rx_status(priv))
		en_warn(priv, "Leaving promiscuous mode\n");
	priv->flags &= ~MLX4_EN_FLAG_PROMISC;

	/* Disable promiscouos mode */
	चयन (mdev->dev->caps.steering_mode) अणु
	हाल MLX4_STEERING_MODE_DEVICE_MANAGED:
		err = mlx4_flow_steer_promisc_हटाओ(mdev->dev,
						     priv->port,
						     MLX4_FS_ALL_DEFAULT);
		अगर (err)
			en_err(priv, "Failed disabling promiscuous mode\n");
		priv->flags &= ~MLX4_EN_FLAG_MC_PROMISC;
		अवरोध;

	हाल MLX4_STEERING_MODE_B0:
		err = mlx4_unicast_promisc_हटाओ(mdev->dev,
						  priv->base_qpn,
						  priv->port);
		अगर (err)
			en_err(priv, "Failed disabling unicast promiscuous mode\n");
		/* Disable Multicast promisc */
		अगर (priv->flags & MLX4_EN_FLAG_MC_PROMISC) अणु
			err = mlx4_multicast_promisc_हटाओ(mdev->dev,
							    priv->base_qpn,
							    priv->port);
			अगर (err)
				en_err(priv, "Failed disabling multicast promiscuous mode\n");
			priv->flags &= ~MLX4_EN_FLAG_MC_PROMISC;
		पूर्ण
		अवरोध;

	हाल MLX4_STEERING_MODE_A0:
		err = mlx4_SET_PORT_qpn_calc(mdev->dev,
					     priv->port,
					     priv->base_qpn, 0);
		अगर (err)
			en_err(priv, "Failed disabling promiscuous mode\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mlx4_en_करो_multicast(काष्ठा mlx4_en_priv *priv,
				 काष्ठा net_device *dev,
				 काष्ठा mlx4_en_dev *mdev)
अणु
	काष्ठा mlx4_en_mc_list *mclist, *पंचांगp;
	u64 mcast_addr = 0;
	u8 mc_list[16] = अणु0पूर्ण;
	पूर्णांक err = 0;

	/* Enable/disable the multicast filter according to IFF_ALLMULTI */
	अगर (dev->flags & IFF_ALLMULTI) अणु
		err = mlx4_SET_MCAST_FLTR(mdev->dev, priv->port, 0,
					  0, MLX4_MCAST_DISABLE);
		अगर (err)
			en_err(priv, "Failed disabling multicast filter\n");

		/* Add the शेष qp number as multicast promisc */
		अगर (!(priv->flags & MLX4_EN_FLAG_MC_PROMISC)) अणु
			चयन (mdev->dev->caps.steering_mode) अणु
			हाल MLX4_STEERING_MODE_DEVICE_MANAGED:
				err = mlx4_flow_steer_promisc_add(mdev->dev,
								  priv->port,
								  priv->base_qpn,
								  MLX4_FS_MC_DEFAULT);
				अवरोध;

			हाल MLX4_STEERING_MODE_B0:
				err = mlx4_multicast_promisc_add(mdev->dev,
								 priv->base_qpn,
								 priv->port);
				अवरोध;

			हाल MLX4_STEERING_MODE_A0:
				अवरोध;
			पूर्ण
			अगर (err)
				en_err(priv, "Failed entering multicast promisc mode\n");
			priv->flags |= MLX4_EN_FLAG_MC_PROMISC;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Disable Multicast promisc */
		अगर (priv->flags & MLX4_EN_FLAG_MC_PROMISC) अणु
			चयन (mdev->dev->caps.steering_mode) अणु
			हाल MLX4_STEERING_MODE_DEVICE_MANAGED:
				err = mlx4_flow_steer_promisc_हटाओ(mdev->dev,
								     priv->port,
								     MLX4_FS_MC_DEFAULT);
				अवरोध;

			हाल MLX4_STEERING_MODE_B0:
				err = mlx4_multicast_promisc_हटाओ(mdev->dev,
								    priv->base_qpn,
								    priv->port);
				अवरोध;

			हाल MLX4_STEERING_MODE_A0:
				अवरोध;
			पूर्ण
			अगर (err)
				en_err(priv, "Failed disabling multicast promiscuous mode\n");
			priv->flags &= ~MLX4_EN_FLAG_MC_PROMISC;
		पूर्ण

		err = mlx4_SET_MCAST_FLTR(mdev->dev, priv->port, 0,
					  0, MLX4_MCAST_DISABLE);
		अगर (err)
			en_err(priv, "Failed disabling multicast filter\n");

		/* Flush mcast filter and init it with broadcast address */
		mlx4_SET_MCAST_FLTR(mdev->dev, priv->port, ETH_BCAST,
				    1, MLX4_MCAST_CONFIG);

		/* Update multicast list - we cache all addresses so they won't
		 * change जबतक HW is updated holding the command semaphor */
		netअगर_addr_lock_bh(dev);
		mlx4_en_cache_mclist(dev);
		netअगर_addr_unlock_bh(dev);
		list_क्रम_each_entry(mclist, &priv->mc_list, list) अणु
			mcast_addr = mlx4_mac_to_u64(mclist->addr);
			mlx4_SET_MCAST_FLTR(mdev->dev, priv->port,
					    mcast_addr, 0, MLX4_MCAST_CONFIG);
		पूर्ण
		err = mlx4_SET_MCAST_FLTR(mdev->dev, priv->port, 0,
					  0, MLX4_MCAST_ENABLE);
		अगर (err)
			en_err(priv, "Failed enabling multicast filter\n");

		update_mclist_flags(priv, &priv->curr_list, &priv->mc_list);
		list_क्रम_each_entry_safe(mclist, पंचांगp, &priv->curr_list, list) अणु
			अगर (mclist->action == MCLIST_REM) अणु
				/* detach this address and delete from list */
				स_नकल(&mc_list[10], mclist->addr, ETH_ALEN);
				mc_list[5] = priv->port;
				err = mlx4_multicast_detach(mdev->dev,
							    priv->rss_map.indir_qp,
							    mc_list,
							    MLX4_PROT_ETH,
							    mclist->reg_id);
				अगर (err)
					en_err(priv, "Fail to detach multicast address\n");

				अगर (mclist->tunnel_reg_id) अणु
					err = mlx4_flow_detach(priv->mdev->dev, mclist->tunnel_reg_id);
					अगर (err)
						en_err(priv, "Failed to detach multicast address\n");
				पूर्ण

				/* हटाओ from list */
				list_del(&mclist->list);
				kमुक्त(mclist);
			पूर्ण अन्यथा अगर (mclist->action == MCLIST_ADD) अणु
				/* attach the address */
				स_नकल(&mc_list[10], mclist->addr, ETH_ALEN);
				/* needed क्रम B0 steering support */
				mc_list[5] = priv->port;
				err = mlx4_multicast_attach(mdev->dev,
							    priv->rss_map.indir_qp,
							    mc_list,
							    priv->port, 0,
							    MLX4_PROT_ETH,
							    &mclist->reg_id);
				अगर (err)
					en_err(priv, "Fail to attach multicast address\n");

				err = mlx4_en_tunnel_steer_add(priv, &mc_list[10], priv->base_qpn,
							       &mclist->tunnel_reg_id);
				अगर (err)
					en_err(priv, "Failed to attach multicast address\n");
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mlx4_en_करो_uc_filter(काष्ठा mlx4_en_priv *priv,
				 काष्ठा net_device *dev,
				 काष्ठा mlx4_en_dev *mdev)
अणु
	काष्ठा netdev_hw_addr *ha;
	काष्ठा mlx4_mac_entry *entry;
	काष्ठा hlist_node *पंचांगp;
	bool found;
	u64 mac;
	पूर्णांक err = 0;
	काष्ठा hlist_head *bucket;
	अचिन्हित पूर्णांक i;
	पूर्णांक हटाओd = 0;
	u32 prev_flags;

	/* Note that we करो not need to protect our mac_hash traversal with rcu,
	 * since all modअगरication code is रक्षित by mdev->state_lock
	 */

	/* find what to हटाओ */
	क्रम (i = 0; i < MLX4_EN_MAC_HASH_SIZE; ++i) अणु
		bucket = &priv->mac_hash[i];
		hlist_क्रम_each_entry_safe(entry, पंचांगp, bucket, hlist) अणु
			found = false;
			netdev_क्रम_each_uc_addr(ha, dev) अणु
				अगर (ether_addr_equal_64bits(entry->mac,
							    ha->addr)) अणु
					found = true;
					अवरोध;
				पूर्ण
			पूर्ण

			/* MAC address of the port is not in uc list */
			अगर (ether_addr_equal_64bits(entry->mac,
						    priv->current_mac))
				found = true;

			अगर (!found) अणु
				mac = mlx4_mac_to_u64(entry->mac);
				mlx4_en_uc_steer_release(priv, entry->mac,
							 priv->base_qpn,
							 entry->reg_id);
				mlx4_unरेजिस्टर_mac(mdev->dev, priv->port, mac);

				hlist_del_rcu(&entry->hlist);
				kमुक्त_rcu(entry, rcu);
				en_dbg(DRV, priv, "Removed MAC %pM on port:%d\n",
				       entry->mac, priv->port);
				++हटाओd;
			पूर्ण
		पूर्ण
	पूर्ण

	/* अगर we didn't हटाओ anything, there is no use in trying to add
	 * again once we are in a क्रमced promisc mode state
	 */
	अगर ((priv->flags & MLX4_EN_FLAG_FORCE_PROMISC) && 0 == हटाओd)
		वापस;

	prev_flags = priv->flags;
	priv->flags &= ~MLX4_EN_FLAG_FORCE_PROMISC;

	/* find what to add */
	netdev_क्रम_each_uc_addr(ha, dev) अणु
		found = false;
		bucket = &priv->mac_hash[ha->addr[MLX4_EN_MAC_HASH_IDX]];
		hlist_क्रम_each_entry(entry, bucket, hlist) अणु
			अगर (ether_addr_equal_64bits(entry->mac, ha->addr)) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
			अगर (!entry) अणु
				en_err(priv, "Failed adding MAC %pM on port:%d (out of memory)\n",
				       ha->addr, priv->port);
				priv->flags |= MLX4_EN_FLAG_FORCE_PROMISC;
				अवरोध;
			पूर्ण
			mac = mlx4_mac_to_u64(ha->addr);
			स_नकल(entry->mac, ha->addr, ETH_ALEN);
			err = mlx4_रेजिस्टर_mac(mdev->dev, priv->port, mac);
			अगर (err < 0) अणु
				en_err(priv, "Failed registering MAC %pM on port %d: %d\n",
				       ha->addr, priv->port, err);
				kमुक्त(entry);
				priv->flags |= MLX4_EN_FLAG_FORCE_PROMISC;
				अवरोध;
			पूर्ण
			err = mlx4_en_uc_steer_add(priv, ha->addr,
						   &priv->base_qpn,
						   &entry->reg_id);
			अगर (err) अणु
				en_err(priv, "Failed adding MAC %pM on port %d: %d\n",
				       ha->addr, priv->port, err);
				mlx4_unरेजिस्टर_mac(mdev->dev, priv->port, mac);
				kमुक्त(entry);
				priv->flags |= MLX4_EN_FLAG_FORCE_PROMISC;
				अवरोध;
			पूर्ण अन्यथा अणु
				अचिन्हित पूर्णांक mac_hash;
				en_dbg(DRV, priv, "Added MAC %pM on port:%d\n",
				       ha->addr, priv->port);
				mac_hash = ha->addr[MLX4_EN_MAC_HASH_IDX];
				bucket = &priv->mac_hash[mac_hash];
				hlist_add_head_rcu(&entry->hlist, bucket);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (priv->flags & MLX4_EN_FLAG_FORCE_PROMISC) अणु
		en_warn(priv, "Forcing promiscuous mode on port:%d\n",
			priv->port);
	पूर्ण अन्यथा अगर (prev_flags & MLX4_EN_FLAG_FORCE_PROMISC) अणु
		en_warn(priv, "Stop forcing promiscuous mode on port:%d\n",
			priv->port);
	पूर्ण
पूर्ण

अटल व्योम mlx4_en_करो_set_rx_mode(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx4_en_priv *priv = container_of(work, काष्ठा mlx4_en_priv,
						 rx_mode_task);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा net_device *dev = priv->dev;

	mutex_lock(&mdev->state_lock);
	अगर (!mdev->device_up) अणु
		en_dbg(HW, priv, "Card is not up, ignoring rx mode change.\n");
		जाओ out;
	पूर्ण
	अगर (!priv->port_up) अणु
		en_dbg(HW, priv, "Port is down, ignoring rx mode change.\n");
		जाओ out;
	पूर्ण

	अगर (!netअगर_carrier_ok(dev)) अणु
		अगर (!mlx4_en_QUERY_PORT(mdev, priv->port)) अणु
			अगर (priv->port_state.link_state) अणु
				priv->last_link_state = MLX4_DEV_EVENT_PORT_UP;
				netअगर_carrier_on(dev);
				en_dbg(LINK, priv, "Link Up\n");
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (dev->priv_flags & IFF_UNICAST_FLT)
		mlx4_en_करो_uc_filter(priv, dev, mdev);

	/* Promsicuous mode: disable all filters */
	अगर ((dev->flags & IFF_PROMISC) ||
	    (priv->flags & MLX4_EN_FLAG_FORCE_PROMISC)) अणु
		mlx4_en_set_promisc_mode(priv, mdev);
		जाओ out;
	पूर्ण

	/* Not in promiscuous mode */
	अगर (priv->flags & MLX4_EN_FLAG_PROMISC)
		mlx4_en_clear_promisc_mode(priv, mdev);

	mlx4_en_करो_multicast(priv, dev, mdev);
out:
	mutex_unlock(&mdev->state_lock);
पूर्ण

अटल पूर्णांक mlx4_en_set_rss_steer_rules(काष्ठा mlx4_en_priv *priv)
अणु
	u64 reg_id;
	पूर्णांक err = 0;
	पूर्णांक *qpn = &priv->base_qpn;
	काष्ठा mlx4_mac_entry *entry;

	err = mlx4_en_uc_steer_add(priv, priv->dev->dev_addr, qpn, &reg_id);
	अगर (err)
		वापस err;

	err = mlx4_en_tunnel_steer_add(priv, priv->dev->dev_addr, *qpn,
				       &priv->tunnel_reg_id);
	अगर (err)
		जाओ tunnel_err;

	entry = kदो_स्मृति(माप(*entry), GFP_KERNEL);
	अगर (!entry) अणु
		err = -ENOMEM;
		जाओ alloc_err;
	पूर्ण

	स_नकल(entry->mac, priv->dev->dev_addr, माप(entry->mac));
	स_नकल(priv->current_mac, entry->mac, माप(priv->current_mac));
	entry->reg_id = reg_id;
	hlist_add_head_rcu(&entry->hlist,
			   &priv->mac_hash[entry->mac[MLX4_EN_MAC_HASH_IDX]]);

	वापस 0;

alloc_err:
	अगर (priv->tunnel_reg_id)
		mlx4_flow_detach(priv->mdev->dev, priv->tunnel_reg_id);

tunnel_err:
	mlx4_en_uc_steer_release(priv, priv->dev->dev_addr, *qpn, reg_id);
	वापस err;
पूर्ण

अटल व्योम mlx4_en_delete_rss_steer_rules(काष्ठा mlx4_en_priv *priv)
अणु
	u64 mac;
	अचिन्हित पूर्णांक i;
	पूर्णांक qpn = priv->base_qpn;
	काष्ठा hlist_head *bucket;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा mlx4_mac_entry *entry;

	क्रम (i = 0; i < MLX4_EN_MAC_HASH_SIZE; ++i) अणु
		bucket = &priv->mac_hash[i];
		hlist_क्रम_each_entry_safe(entry, पंचांगp, bucket, hlist) अणु
			mac = mlx4_mac_to_u64(entry->mac);
			en_dbg(DRV, priv, "Registering MAC:%pM for deleting\n",
			       entry->mac);
			mlx4_en_uc_steer_release(priv, entry->mac,
						 qpn, entry->reg_id);

			mlx4_unरेजिस्टर_mac(priv->mdev->dev, priv->port, mac);
			hlist_del_rcu(&entry->hlist);
			kमुक्त_rcu(entry, rcu);
		पूर्ण
	पूर्ण

	अगर (priv->tunnel_reg_id) अणु
		mlx4_flow_detach(priv->mdev->dev, priv->tunnel_reg_id);
		priv->tunnel_reg_id = 0;
	पूर्ण
पूर्ण

अटल व्योम mlx4_en_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_tx_ring *tx_ring = priv->tx_ring[TX][txqueue];

	अगर (netअगर_msg_समयr(priv))
		en_warn(priv, "Tx timeout called on port:%d\n", priv->port);

	en_warn(priv, "TX timeout on queue: %d, QP: 0x%x, CQ: 0x%x, Cons: 0x%x, Prod: 0x%x\n",
		txqueue, tx_ring->qpn, tx_ring->sp_cqn,
		tx_ring->cons, tx_ring->prod);

	priv->port_stats.tx_समयout++;
	अगर (!test_and_set_bit(MLX4_EN_STATE_FLAG_RESTARTING, &priv->state)) अणु
		en_dbg(DRV, priv, "Scheduling port restart\n");
		queue_work(mdev->workqueue, &priv->restart_task);
	पूर्ण
पूर्ण


अटल व्योम
mlx4_en_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	spin_lock_bh(&priv->stats_lock);
	mlx4_en_fold_software_stats(dev);
	netdev_stats_to_stats64(stats, &dev->stats);
	spin_unlock_bh(&priv->stats_lock);
पूर्ण

अटल व्योम mlx4_en_set_शेष_moderation(काष्ठा mlx4_en_priv *priv)
अणु
	काष्ठा mlx4_en_cq *cq;
	पूर्णांक i, t;

	/* If we haven't received a specअगरic coalescing setting
	 * (module param), we set the moderation parameters as follows:
	 * - moder_cnt is set to the number of mtu sized packets to
	 *   satisfy our coalescing target.
	 * - moder_समय is set to a fixed value.
	 */
	priv->rx_frames = MLX4_EN_RX_COAL_TARGET;
	priv->rx_usecs = MLX4_EN_RX_COAL_TIME;
	priv->tx_frames = MLX4_EN_TX_COAL_PKTS;
	priv->tx_usecs = MLX4_EN_TX_COAL_TIME;
	en_dbg(INTR, priv, "Default coalescing params for mtu:%d - rx_frames:%d rx_usecs:%d\n",
	       priv->dev->mtu, priv->rx_frames, priv->rx_usecs);

	/* Setup cq moderation params */
	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		cq = priv->rx_cq[i];
		cq->moder_cnt = priv->rx_frames;
		cq->moder_समय = priv->rx_usecs;
		priv->last_moder_समय[i] = MLX4_EN_AUTO_CONF;
		priv->last_moder_packets[i] = 0;
		priv->last_moder_bytes[i] = 0;
	पूर्ण

	क्रम (t = 0 ; t < MLX4_EN_NUM_TX_TYPES; t++) अणु
		क्रम (i = 0; i < priv->tx_ring_num[t]; i++) अणु
			cq = priv->tx_cq[t][i];
			cq->moder_cnt = priv->tx_frames;
			cq->moder_समय = priv->tx_usecs;
		पूर्ण
	पूर्ण

	/* Reset स्वतः-moderation params */
	priv->pkt_rate_low = MLX4_EN_RX_RATE_LOW;
	priv->rx_usecs_low = MLX4_EN_RX_COAL_TIME_LOW;
	priv->pkt_rate_high = MLX4_EN_RX_RATE_HIGH;
	priv->rx_usecs_high = MLX4_EN_RX_COAL_TIME_HIGH;
	priv->sample_पूर्णांकerval = MLX4_EN_SAMPLE_INTERVAL;
	priv->adaptive_rx_coal = 1;
	priv->last_moder_jअगरfies = 0;
	priv->last_moder_tx_packets = 0;
पूर्ण

अटल व्योम mlx4_en_स्वतः_moderation(काष्ठा mlx4_en_priv *priv)
अणु
	अचिन्हित दीर्घ period = (अचिन्हित दीर्घ) (jअगरfies - priv->last_moder_jअगरfies);
	u32 pkt_rate_high, pkt_rate_low;
	काष्ठा mlx4_en_cq *cq;
	अचिन्हित दीर्घ packets;
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ avg_pkt_size;
	अचिन्हित दीर्घ rx_packets;
	अचिन्हित दीर्घ rx_bytes;
	अचिन्हित दीर्घ rx_pkt_dअगरf;
	पूर्णांक moder_समय;
	पूर्णांक ring, err;

	अगर (!priv->adaptive_rx_coal || period < priv->sample_पूर्णांकerval * HZ)
		वापस;

	pkt_rate_low = READ_ONCE(priv->pkt_rate_low);
	pkt_rate_high = READ_ONCE(priv->pkt_rate_high);

	क्रम (ring = 0; ring < priv->rx_ring_num; ring++) अणु
		rx_packets = READ_ONCE(priv->rx_ring[ring]->packets);
		rx_bytes = READ_ONCE(priv->rx_ring[ring]->bytes);

		rx_pkt_dअगरf = rx_packets - priv->last_moder_packets[ring];
		packets = rx_pkt_dअगरf;
		rate = packets * HZ / period;
		avg_pkt_size = packets ? (rx_bytes -
				priv->last_moder_bytes[ring]) / packets : 0;

		/* Apply स्वतः-moderation only when packet rate
		 * exceeds a rate that it matters */
		अगर (rate > (MLX4_EN_RX_RATE_THRESH / priv->rx_ring_num) &&
		    avg_pkt_size > MLX4_EN_AVG_PKT_SMALL) अणु
			अगर (rate <= pkt_rate_low)
				moder_समय = priv->rx_usecs_low;
			अन्यथा अगर (rate >= pkt_rate_high)
				moder_समय = priv->rx_usecs_high;
			अन्यथा
				moder_समय = (rate - pkt_rate_low) *
					(priv->rx_usecs_high - priv->rx_usecs_low) /
					(pkt_rate_high - pkt_rate_low) +
					priv->rx_usecs_low;
		पूर्ण अन्यथा अणु
			moder_समय = priv->rx_usecs_low;
		पूर्ण

		cq = priv->rx_cq[ring];
		अगर (moder_समय != priv->last_moder_समय[ring] ||
		    cq->moder_cnt != priv->rx_frames) अणु
			priv->last_moder_समय[ring] = moder_समय;
			cq->moder_समय = moder_समय;
			cq->moder_cnt = priv->rx_frames;
			err = mlx4_en_set_cq_moder(priv, cq);
			अगर (err)
				en_err(priv, "Failed modifying moderation for cq:%d\n",
				       ring);
		पूर्ण
		priv->last_moder_packets[ring] = rx_packets;
		priv->last_moder_bytes[ring] = rx_bytes;
	पूर्ण

	priv->last_moder_jअगरfies = jअगरfies;
पूर्ण

अटल व्योम mlx4_en_करो_get_stats(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delay = to_delayed_work(work);
	काष्ठा mlx4_en_priv *priv = container_of(delay, काष्ठा mlx4_en_priv,
						 stats_task);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक err;

	mutex_lock(&mdev->state_lock);
	अगर (mdev->device_up) अणु
		अगर (priv->port_up) अणु
			err = mlx4_en_DUMP_ETH_STATS(mdev, priv->port, 0);
			अगर (err)
				en_dbg(HW, priv, "Could not update stats\n");

			mlx4_en_स्वतः_moderation(priv);
		पूर्ण

		queue_delayed_work(mdev->workqueue, &priv->stats_task, STATS_DELAY);
	पूर्ण
	अगर (mdev->mac_हटाओd[MLX4_MAX_PORTS + 1 - priv->port]) अणु
		mlx4_en_करो_set_mac(priv, priv->current_mac);
		mdev->mac_हटाओd[MLX4_MAX_PORTS + 1 - priv->port] = 0;
	पूर्ण
	mutex_unlock(&mdev->state_lock);
पूर्ण

/* mlx4_en_service_task - Run service task क्रम tasks that needed to be करोne
 * periodically
 */
अटल व्योम mlx4_en_service_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delay = to_delayed_work(work);
	काष्ठा mlx4_en_priv *priv = container_of(delay, काष्ठा mlx4_en_priv,
						 service_task);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;

	mutex_lock(&mdev->state_lock);
	अगर (mdev->device_up) अणु
		अगर (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_TS)
			mlx4_en_ptp_overflow_check(mdev);

		mlx4_en_recover_from_oom(priv);
		queue_delayed_work(mdev->workqueue, &priv->service_task,
				   SERVICE_TASK_DELAY);
	पूर्ण
	mutex_unlock(&mdev->state_lock);
पूर्ण

अटल व्योम mlx4_en_linkstate(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx4_en_priv *priv = container_of(work, काष्ठा mlx4_en_priv,
						 linkstate_task);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक linkstate = priv->link_state;

	mutex_lock(&mdev->state_lock);
	/* If observable port state changed set carrier state and
	 * report to प्रणाली log */
	अगर (priv->last_link_state != linkstate) अणु
		अगर (linkstate == MLX4_DEV_EVENT_PORT_DOWN) अणु
			en_info(priv, "Link Down\n");
			netअगर_carrier_off(priv->dev);
		पूर्ण अन्यथा अणु
			en_info(priv, "Link Up\n");
			netअगर_carrier_on(priv->dev);
		पूर्ण
	पूर्ण
	priv->last_link_state = linkstate;
	mutex_unlock(&mdev->state_lock);
पूर्ण

अटल पूर्णांक mlx4_en_init_affinity_hपूर्णांक(काष्ठा mlx4_en_priv *priv, पूर्णांक ring_idx)
अणु
	काष्ठा mlx4_en_rx_ring *ring = priv->rx_ring[ring_idx];
	पूर्णांक numa_node = priv->mdev->dev->numa_node;

	अगर (!zalloc_cpumask_var(&ring->affinity_mask, GFP_KERNEL))
		वापस -ENOMEM;

	cpumask_set_cpu(cpumask_local_spपढ़ो(ring_idx, numa_node),
			ring->affinity_mask);
	वापस 0;
पूर्ण

अटल व्योम mlx4_en_मुक्त_affinity_hपूर्णांक(काष्ठा mlx4_en_priv *priv, पूर्णांक ring_idx)
अणु
	मुक्त_cpumask_var(priv->rx_ring[ring_idx]->affinity_mask);
पूर्ण

अटल व्योम mlx4_en_init_recycle_ring(काष्ठा mlx4_en_priv *priv,
				      पूर्णांक tx_ring_idx)
अणु
	काष्ठा mlx4_en_tx_ring *tx_ring = priv->tx_ring[TX_XDP][tx_ring_idx];
	पूर्णांक rr_index = tx_ring_idx;

	tx_ring->मुक्त_tx_desc = mlx4_en_recycle_tx_desc;
	tx_ring->recycle_ring = priv->rx_ring[rr_index];
	en_dbg(DRV, priv, "Set tx_ring[%d][%d]->recycle_ring = rx_ring[%d]\n",
	       TX_XDP, tx_ring_idx, rr_index);
पूर्ण

पूर्णांक mlx4_en_start_port(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_cq *cq;
	काष्ठा mlx4_en_tx_ring *tx_ring;
	पूर्णांक rx_index = 0;
	पूर्णांक err = 0;
	पूर्णांक i, t;
	पूर्णांक j;
	u8 mc_list[16] = अणु0पूर्ण;

	अगर (priv->port_up) अणु
		en_dbg(DRV, priv, "start port called while port already up\n");
		वापस 0;
	पूर्ण

	INIT_LIST_HEAD(&priv->mc_list);
	INIT_LIST_HEAD(&priv->curr_list);
	INIT_LIST_HEAD(&priv->ethtool_list);
	स_रखो(&priv->ethtool_rules[0], 0,
	       माप(काष्ठा ethtool_flow_id) * MAX_NUM_OF_FS_RULES);

	/* Calculate Rx buf size */
	dev->mtu = min(dev->mtu, priv->max_mtu);
	mlx4_en_calc_rx_buf(dev);
	en_dbg(DRV, priv, "Rx buf size:%d\n", priv->rx_skb_size);

	/* Configure rx cq's and rings */
	err = mlx4_en_activate_rx_rings(priv);
	अगर (err) अणु
		en_err(priv, "Failed to activate RX rings\n");
		वापस err;
	पूर्ण
	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		cq = priv->rx_cq[i];

		err = mlx4_en_init_affinity_hपूर्णांक(priv, i);
		अगर (err) अणु
			en_err(priv, "Failed preparing IRQ affinity hint\n");
			जाओ cq_err;
		पूर्ण

		err = mlx4_en_activate_cq(priv, cq, i);
		अगर (err) अणु
			en_err(priv, "Failed activating Rx CQ\n");
			mlx4_en_मुक्त_affinity_hपूर्णांक(priv, i);
			जाओ cq_err;
		पूर्ण

		क्रम (j = 0; j < cq->size; j++) अणु
			काष्ठा mlx4_cqe *cqe = शून्य;

			cqe = mlx4_en_get_cqe(cq->buf, j, priv->cqe_size) +
			      priv->cqe_factor;
			cqe->owner_sr_opcode = MLX4_CQE_OWNER_MASK;
		पूर्ण

		err = mlx4_en_set_cq_moder(priv, cq);
		अगर (err) अणु
			en_err(priv, "Failed setting cq moderation parameters\n");
			mlx4_en_deactivate_cq(priv, cq);
			mlx4_en_मुक्त_affinity_hपूर्णांक(priv, i);
			जाओ cq_err;
		पूर्ण
		mlx4_en_arm_cq(priv, cq);
		priv->rx_ring[i]->cqn = cq->mcq.cqn;
		++rx_index;
	पूर्ण

	/* Set qp number */
	en_dbg(DRV, priv, "Getting qp number for port %d\n", priv->port);
	err = mlx4_en_get_qp(priv);
	अगर (err) अणु
		en_err(priv, "Failed getting eth qp\n");
		जाओ cq_err;
	पूर्ण
	mdev->mac_हटाओd[priv->port] = 0;

	priv->counter_index =
			mlx4_get_शेष_counter_index(mdev->dev, priv->port);

	err = mlx4_en_config_rss_steer(priv);
	अगर (err) अणु
		en_err(priv, "Failed configuring rss steering\n");
		जाओ mac_err;
	पूर्ण

	err = mlx4_en_create_drop_qp(priv);
	अगर (err)
		जाओ rss_err;

	/* Configure tx cq's and rings */
	क्रम (t = 0 ; t < MLX4_EN_NUM_TX_TYPES; t++) अणु
		u8 num_tx_rings_p_up = t == TX ?
			priv->num_tx_rings_p_up : priv->tx_ring_num[t];

		क्रम (i = 0; i < priv->tx_ring_num[t]; i++) अणु
			/* Configure cq */
			cq = priv->tx_cq[t][i];
			err = mlx4_en_activate_cq(priv, cq, i);
			अगर (err) अणु
				en_err(priv, "Failed allocating Tx CQ\n");
				जाओ tx_err;
			पूर्ण
			err = mlx4_en_set_cq_moder(priv, cq);
			अगर (err) अणु
				en_err(priv, "Failed setting cq moderation parameters\n");
				mlx4_en_deactivate_cq(priv, cq);
				जाओ tx_err;
			पूर्ण
			en_dbg(DRV, priv,
			       "Resetting index of collapsed CQ:%d to -1\n", i);
			cq->buf->wqe_index = cpu_to_be16(0xffff);

			/* Configure ring */
			tx_ring = priv->tx_ring[t][i];
			err = mlx4_en_activate_tx_ring(priv, tx_ring,
						       cq->mcq.cqn,
						       i / num_tx_rings_p_up);
			अगर (err) अणु
				en_err(priv, "Failed allocating Tx ring\n");
				mlx4_en_deactivate_cq(priv, cq);
				जाओ tx_err;
			पूर्ण
			clear_bit(MLX4_EN_TX_RING_STATE_RECOVERING, &tx_ring->state);
			अगर (t != TX_XDP) अणु
				tx_ring->tx_queue = netdev_get_tx_queue(dev, i);
				tx_ring->recycle_ring = शून्य;

				/* Arm CQ क्रम TX completions */
				mlx4_en_arm_cq(priv, cq);

			पूर्ण अन्यथा अणु
				mlx4_en_init_tx_xdp_ring_descs(priv, tx_ring);
				mlx4_en_init_recycle_ring(priv, i);
				/* XDP TX CQ should never be armed */
			पूर्ण

			/* Set initial ownership of all Tx TXBBs to SW (1) */
			क्रम (j = 0; j < tx_ring->buf_size; j += STAMP_STRIDE)
				*((u32 *)(tx_ring->buf + j)) = 0xffffffff;
		पूर्ण
	पूर्ण

	/* Configure port */
	err = mlx4_SET_PORT_general(mdev->dev, priv->port,
				    priv->rx_skb_size + ETH_FCS_LEN,
				    priv->prof->tx_छोड़ो,
				    priv->prof->tx_ppp,
				    priv->prof->rx_छोड़ो,
				    priv->prof->rx_ppp);
	अगर (err) अणु
		en_err(priv, "Failed setting port general configurations for port %d, with error %d\n",
		       priv->port, err);
		जाओ tx_err;
	पूर्ण

	err = mlx4_SET_PORT_user_mtu(mdev->dev, priv->port, dev->mtu);
	अगर (err) अणु
		en_err(priv, "Failed to pass user MTU(%d) to Firmware for port %d, with error %d\n",
		       dev->mtu, priv->port, err);
		जाओ tx_err;
	पूर्ण

	/* Set शेष qp number */
	err = mlx4_SET_PORT_qpn_calc(mdev->dev, priv->port, priv->base_qpn, 0);
	अगर (err) अणु
		en_err(priv, "Failed setting default qp numbers\n");
		जाओ tx_err;
	पूर्ण

	अगर (mdev->dev->caps.tunnel_offload_mode == MLX4_TUNNEL_OFFLOAD_MODE_VXLAN) अणु
		err = mlx4_SET_PORT_VXLAN(mdev->dev, priv->port, VXLAN_STEER_BY_OUTER_MAC, 1);
		अगर (err) अणु
			en_err(priv, "Failed setting port L2 tunnel configuration, err %d\n",
			       err);
			जाओ tx_err;
		पूर्ण
	पूर्ण

	/* Init port */
	en_dbg(HW, priv, "Initializing port\n");
	err = mlx4_INIT_PORT(mdev->dev, priv->port);
	अगर (err) अणु
		en_err(priv, "Failed Initializing port\n");
		जाओ tx_err;
	पूर्ण

	/* Set Unicast and VXLAN steering rules */
	अगर (mdev->dev->caps.steering_mode != MLX4_STEERING_MODE_A0 &&
	    mlx4_en_set_rss_steer_rules(priv))
		mlx4_warn(mdev, "Failed setting steering rules\n");

	/* Attach rx QP to bradcast address */
	eth_broadcast_addr(&mc_list[10]);
	mc_list[5] = priv->port; /* needed क्रम B0 steering support */
	अगर (mlx4_multicast_attach(mdev->dev, priv->rss_map.indir_qp, mc_list,
				  priv->port, 0, MLX4_PROT_ETH,
				  &priv->broadcast_id))
		mlx4_warn(mdev, "Failed Attaching Broadcast\n");

	/* Must reकरो promiscuous mode setup. */
	priv->flags &= ~(MLX4_EN_FLAG_PROMISC | MLX4_EN_FLAG_MC_PROMISC);

	/* Schedule multicast task to populate multicast list */
	queue_work(mdev->workqueue, &priv->rx_mode_task);

	अगर (priv->mdev->dev->caps.tunnel_offload_mode == MLX4_TUNNEL_OFFLOAD_MODE_VXLAN)
		udp_tunnel_nic_reset_ntf(dev);

	priv->port_up = true;

	/* Process all completions अगर exist to prevent
	 * the queues मुक्तzing अगर they are full
	 */
	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		local_bh_disable();
		napi_schedule(&priv->rx_cq[i]->napi);
		local_bh_enable();
	पूर्ण

	clear_bit(MLX4_EN_STATE_FLAG_RESTARTING, &priv->state);
	netअगर_tx_start_all_queues(dev);
	netअगर_device_attach(dev);

	वापस 0;

tx_err:
	अगर (t == MLX4_EN_NUM_TX_TYPES) अणु
		t--;
		i = priv->tx_ring_num[t];
	पूर्ण
	जबतक (t >= 0) अणु
		जबतक (i--) अणु
			mlx4_en_deactivate_tx_ring(priv, priv->tx_ring[t][i]);
			mlx4_en_deactivate_cq(priv, priv->tx_cq[t][i]);
		पूर्ण
		अगर (!t--)
			अवरोध;
		i = priv->tx_ring_num[t];
	पूर्ण
	mlx4_en_destroy_drop_qp(priv);
rss_err:
	mlx4_en_release_rss_steer(priv);
mac_err:
	mlx4_en_put_qp(priv);
cq_err:
	जबतक (rx_index--) अणु
		mlx4_en_deactivate_cq(priv, priv->rx_cq[rx_index]);
		mlx4_en_मुक्त_affinity_hपूर्णांक(priv, rx_index);
	पूर्ण
	क्रम (i = 0; i < priv->rx_ring_num; i++)
		mlx4_en_deactivate_rx_ring(priv, priv->rx_ring[i]);

	वापस err; /* need to बंद devices */
पूर्ण


व्योम mlx4_en_stop_port(काष्ठा net_device *dev, पूर्णांक detach)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_mc_list *mclist, *पंचांगp;
	काष्ठा ethtool_flow_id *flow, *पंचांगp_flow;
	पूर्णांक i, t;
	u8 mc_list[16] = अणु0पूर्ण;

	अगर (!priv->port_up) अणु
		en_dbg(DRV, priv, "stop port called while port already down\n");
		वापस;
	पूर्ण

	/* बंद port*/
	mlx4_CLOSE_PORT(mdev->dev, priv->port);

	/* Synchronize with tx routine */
	netअगर_tx_lock_bh(dev);
	अगर (detach)
		netअगर_device_detach(dev);
	netअगर_tx_stop_all_queues(dev);
	netअगर_tx_unlock_bh(dev);

	netअगर_tx_disable(dev);

	spin_lock_bh(&priv->stats_lock);
	mlx4_en_fold_software_stats(dev);
	/* Set port as not active */
	priv->port_up = false;
	spin_unlock_bh(&priv->stats_lock);

	priv->counter_index = MLX4_SINK_COUNTER_INDEX(mdev->dev);

	/* Promsicuous mode */
	अगर (mdev->dev->caps.steering_mode ==
	    MLX4_STEERING_MODE_DEVICE_MANAGED) अणु
		priv->flags &= ~(MLX4_EN_FLAG_PROMISC |
				 MLX4_EN_FLAG_MC_PROMISC);
		mlx4_flow_steer_promisc_हटाओ(mdev->dev,
					       priv->port,
					       MLX4_FS_ALL_DEFAULT);
		mlx4_flow_steer_promisc_हटाओ(mdev->dev,
					       priv->port,
					       MLX4_FS_MC_DEFAULT);
	पूर्ण अन्यथा अगर (priv->flags & MLX4_EN_FLAG_PROMISC) अणु
		priv->flags &= ~MLX4_EN_FLAG_PROMISC;

		/* Disable promiscouos mode */
		mlx4_unicast_promisc_हटाओ(mdev->dev, priv->base_qpn,
					    priv->port);

		/* Disable Multicast promisc */
		अगर (priv->flags & MLX4_EN_FLAG_MC_PROMISC) अणु
			mlx4_multicast_promisc_हटाओ(mdev->dev, priv->base_qpn,
						      priv->port);
			priv->flags &= ~MLX4_EN_FLAG_MC_PROMISC;
		पूर्ण
	पूर्ण

	/* Detach All multicasts */
	eth_broadcast_addr(&mc_list[10]);
	mc_list[5] = priv->port; /* needed क्रम B0 steering support */
	mlx4_multicast_detach(mdev->dev, priv->rss_map.indir_qp, mc_list,
			      MLX4_PROT_ETH, priv->broadcast_id);
	list_क्रम_each_entry(mclist, &priv->curr_list, list) अणु
		स_नकल(&mc_list[10], mclist->addr, ETH_ALEN);
		mc_list[5] = priv->port;
		mlx4_multicast_detach(mdev->dev, priv->rss_map.indir_qp,
				      mc_list, MLX4_PROT_ETH, mclist->reg_id);
		अगर (mclist->tunnel_reg_id)
			mlx4_flow_detach(mdev->dev, mclist->tunnel_reg_id);
	पूर्ण
	mlx4_en_clear_list(dev);
	list_क्रम_each_entry_safe(mclist, पंचांगp, &priv->curr_list, list) अणु
		list_del(&mclist->list);
		kमुक्त(mclist);
	पूर्ण

	/* Flush multicast filter */
	mlx4_SET_MCAST_FLTR(mdev->dev, priv->port, 0, 1, MLX4_MCAST_CONFIG);

	/* Remove flow steering rules क्रम the port*/
	अगर (mdev->dev->caps.steering_mode ==
	    MLX4_STEERING_MODE_DEVICE_MANAGED) अणु
		ASSERT_RTNL();
		list_क्रम_each_entry_safe(flow, पंचांगp_flow,
					 &priv->ethtool_list, list) अणु
			mlx4_flow_detach(mdev->dev, flow->id);
			list_del(&flow->list);
		पूर्ण
	पूर्ण

	mlx4_en_destroy_drop_qp(priv);

	/* Free TX Rings */
	क्रम (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++) अणु
		क्रम (i = 0; i < priv->tx_ring_num[t]; i++) अणु
			mlx4_en_deactivate_tx_ring(priv, priv->tx_ring[t][i]);
			mlx4_en_deactivate_cq(priv, priv->tx_cq[t][i]);
		पूर्ण
	पूर्ण
	msleep(10);

	क्रम (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++)
		क्रम (i = 0; i < priv->tx_ring_num[t]; i++)
			mlx4_en_मुक्त_tx_buf(dev, priv->tx_ring[t][i]);

	अगर (mdev->dev->caps.steering_mode != MLX4_STEERING_MODE_A0)
		mlx4_en_delete_rss_steer_rules(priv);

	/* Free RSS qps */
	mlx4_en_release_rss_steer(priv);

	/* Unरेजिस्टर Mac address क्रम the port */
	mlx4_en_put_qp(priv);
	अगर (!(mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_REASSIGN_MAC_EN))
		mdev->mac_हटाओd[priv->port] = 1;

	/* Free RX Rings */
	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		काष्ठा mlx4_en_cq *cq = priv->rx_cq[i];

		napi_synchronize(&cq->napi);
		mlx4_en_deactivate_rx_ring(priv, priv->rx_ring[i]);
		mlx4_en_deactivate_cq(priv, cq);

		mlx4_en_मुक्त_affinity_hपूर्णांक(priv, i);
	पूर्ण
पूर्ण

अटल व्योम mlx4_en_restart(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx4_en_priv *priv = container_of(work, काष्ठा mlx4_en_priv,
						 restart_task);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा net_device *dev = priv->dev;

	en_dbg(DRV, priv, "Watchdog task called for port %d\n", priv->port);

	rtnl_lock();
	mutex_lock(&mdev->state_lock);
	अगर (priv->port_up) अणु
		mlx4_en_stop_port(dev, 1);
		अगर (mlx4_en_start_port(dev))
			en_err(priv, "Failed restarting port %d\n", priv->port);
	पूर्ण
	mutex_unlock(&mdev->state_lock);
	rtnl_unlock();
पूर्ण

अटल व्योम mlx4_en_clear_stats(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_tx_ring **tx_ring;
	पूर्णांक i;

	अगर (!mlx4_is_slave(mdev->dev))
		अगर (mlx4_en_DUMP_ETH_STATS(mdev, priv->port, 1))
			en_dbg(HW, priv, "Failed dumping statistics\n");

	स_रखो(&priv->pkstats, 0, माप(priv->pkstats));
	स_रखो(&priv->port_stats, 0, माप(priv->port_stats));
	स_रखो(&priv->rx_flowstats, 0, माप(priv->rx_flowstats));
	स_रखो(&priv->tx_flowstats, 0, माप(priv->tx_flowstats));
	स_रखो(&priv->rx_priority_flowstats, 0,
	       माप(priv->rx_priority_flowstats));
	स_रखो(&priv->tx_priority_flowstats, 0,
	       माप(priv->tx_priority_flowstats));
	स_रखो(&priv->pf_stats, 0, माप(priv->pf_stats));

	tx_ring = priv->tx_ring[TX];
	क्रम (i = 0; i < priv->tx_ring_num[TX]; i++) अणु
		tx_ring[i]->bytes = 0;
		tx_ring[i]->packets = 0;
		tx_ring[i]->tx_csum = 0;
		tx_ring[i]->tx_dropped = 0;
		tx_ring[i]->queue_stopped = 0;
		tx_ring[i]->wake_queue = 0;
		tx_ring[i]->tso_packets = 0;
		tx_ring[i]->xmit_more = 0;
	पूर्ण
	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		priv->rx_ring[i]->bytes = 0;
		priv->rx_ring[i]->packets = 0;
		priv->rx_ring[i]->csum_ok = 0;
		priv->rx_ring[i]->csum_none = 0;
		priv->rx_ring[i]->csum_complete = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_en_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक err = 0;

	mutex_lock(&mdev->state_lock);

	अगर (!mdev->device_up) अणु
		en_err(priv, "Cannot open - device down/disabled\n");
		err = -EBUSY;
		जाओ out;
	पूर्ण

	/* Reset HW statistics and SW counters */
	mlx4_en_clear_stats(dev);

	err = mlx4_en_start_port(dev);
	अगर (err)
		en_err(priv, "Failed starting port:%d\n", priv->port);

out:
	mutex_unlock(&mdev->state_lock);
	वापस err;
पूर्ण


अटल पूर्णांक mlx4_en_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;

	en_dbg(IFDOWN, priv, "Close port called\n");

	mutex_lock(&mdev->state_lock);

	mlx4_en_stop_port(dev, 0);
	netअगर_carrier_off(dev);

	mutex_unlock(&mdev->state_lock);
	वापस 0;
पूर्ण

अटल व्योम mlx4_en_मुक्त_resources(काष्ठा mlx4_en_priv *priv)
अणु
	पूर्णांक i, t;

#अगर_घोषित CONFIG_RFS_ACCEL
	priv->dev->rx_cpu_rmap = शून्य;
#पूर्ण_अगर

	क्रम (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++) अणु
		क्रम (i = 0; i < priv->tx_ring_num[t]; i++) अणु
			अगर (priv->tx_ring[t] && priv->tx_ring[t][i])
				mlx4_en_destroy_tx_ring(priv,
							&priv->tx_ring[t][i]);
			अगर (priv->tx_cq[t] && priv->tx_cq[t][i])
				mlx4_en_destroy_cq(priv, &priv->tx_cq[t][i]);
		पूर्ण
		kमुक्त(priv->tx_ring[t]);
		kमुक्त(priv->tx_cq[t]);
	पूर्ण

	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		अगर (priv->rx_ring[i])
			mlx4_en_destroy_rx_ring(priv, &priv->rx_ring[i],
				priv->prof->rx_ring_size, priv->stride);
		अगर (priv->rx_cq[i])
			mlx4_en_destroy_cq(priv, &priv->rx_cq[i]);
	पूर्ण

पूर्ण

अटल पूर्णांक mlx4_en_alloc_resources(काष्ठा mlx4_en_priv *priv)
अणु
	काष्ठा mlx4_en_port_profile *prof = priv->prof;
	पूर्णांक i, t;
	पूर्णांक node;

	/* Create tx Rings */
	क्रम (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++) अणु
		क्रम (i = 0; i < priv->tx_ring_num[t]; i++) अणु
			node = cpu_to_node(i % num_online_cpus());
			अगर (mlx4_en_create_cq(priv, &priv->tx_cq[t][i],
					      prof->tx_ring_size, i, t, node))
				जाओ err;

			अगर (mlx4_en_create_tx_ring(priv, &priv->tx_ring[t][i],
						   prof->tx_ring_size,
						   TXBB_SIZE, node, i))
				जाओ err;
		पूर्ण
	पूर्ण

	/* Create rx Rings */
	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		node = cpu_to_node(i % num_online_cpus());
		अगर (mlx4_en_create_cq(priv, &priv->rx_cq[i],
				      prof->rx_ring_size, i, RX, node))
			जाओ err;

		अगर (mlx4_en_create_rx_ring(priv, &priv->rx_ring[i],
					   prof->rx_ring_size, priv->stride,
					   node, i))
			जाओ err;

	पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
	priv->dev->rx_cpu_rmap = mlx4_get_cpu_rmap(priv->mdev->dev, priv->port);
#पूर्ण_अगर

	वापस 0;

err:
	en_err(priv, "Failed to allocate NIC resources\n");
	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		अगर (priv->rx_ring[i])
			mlx4_en_destroy_rx_ring(priv, &priv->rx_ring[i],
						prof->rx_ring_size,
						priv->stride);
		अगर (priv->rx_cq[i])
			mlx4_en_destroy_cq(priv, &priv->rx_cq[i]);
	पूर्ण
	क्रम (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++) अणु
		क्रम (i = 0; i < priv->tx_ring_num[t]; i++) अणु
			अगर (priv->tx_ring[t][i])
				mlx4_en_destroy_tx_ring(priv,
							&priv->tx_ring[t][i]);
			अगर (priv->tx_cq[t][i])
				mlx4_en_destroy_cq(priv, &priv->tx_cq[t][i]);
		पूर्ण
	पूर्ण
	वापस -ENOMEM;
पूर्ण


अटल पूर्णांक mlx4_en_copy_priv(काष्ठा mlx4_en_priv *dst,
			     काष्ठा mlx4_en_priv *src,
			     काष्ठा mlx4_en_port_profile *prof)
अणु
	पूर्णांक t;

	स_नकल(&dst->hwtstamp_config, &prof->hwtstamp_config,
	       माप(dst->hwtstamp_config));
	dst->num_tx_rings_p_up = prof->num_tx_rings_p_up;
	dst->rx_ring_num = prof->rx_ring_num;
	dst->flags = prof->flags;
	dst->mdev = src->mdev;
	dst->port = src->port;
	dst->dev = src->dev;
	dst->prof = prof;
	dst->stride = roundup_घात_of_two(माप(काष्ठा mlx4_en_rx_desc) +
					 DS_SIZE * MLX4_EN_MAX_RX_FRAGS);

	क्रम (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++) अणु
		dst->tx_ring_num[t] = prof->tx_ring_num[t];
		अगर (!dst->tx_ring_num[t])
			जारी;

		dst->tx_ring[t] = kसुस्मृति(MAX_TX_RINGS,
					  माप(काष्ठा mlx4_en_tx_ring *),
					  GFP_KERNEL);
		अगर (!dst->tx_ring[t])
			जाओ err_मुक्त_tx;

		dst->tx_cq[t] = kसुस्मृति(MAX_TX_RINGS,
					माप(काष्ठा mlx4_en_cq *),
					GFP_KERNEL);
		अगर (!dst->tx_cq[t]) अणु
			kमुक्त(dst->tx_ring[t]);
			जाओ err_मुक्त_tx;
		पूर्ण
	पूर्ण

	वापस 0;

err_मुक्त_tx:
	जबतक (t--) अणु
		kमुक्त(dst->tx_ring[t]);
		kमुक्त(dst->tx_cq[t]);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल व्योम mlx4_en_update_priv(काष्ठा mlx4_en_priv *dst,
				काष्ठा mlx4_en_priv *src)
अणु
	पूर्णांक t;
	स_नकल(dst->rx_ring, src->rx_ring,
	       माप(काष्ठा mlx4_en_rx_ring *) * src->rx_ring_num);
	स_नकल(dst->rx_cq, src->rx_cq,
	       माप(काष्ठा mlx4_en_cq *) * src->rx_ring_num);
	स_नकल(&dst->hwtstamp_config, &src->hwtstamp_config,
	       माप(dst->hwtstamp_config));
	क्रम (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++) अणु
		dst->tx_ring_num[t] = src->tx_ring_num[t];
		dst->tx_ring[t] = src->tx_ring[t];
		dst->tx_cq[t] = src->tx_cq[t];
	पूर्ण
	dst->num_tx_rings_p_up = src->num_tx_rings_p_up;
	dst->rx_ring_num = src->rx_ring_num;
	स_नकल(dst->prof, src->prof, माप(काष्ठा mlx4_en_port_profile));
पूर्ण

पूर्णांक mlx4_en_try_alloc_resources(काष्ठा mlx4_en_priv *priv,
				काष्ठा mlx4_en_priv *पंचांगp,
				काष्ठा mlx4_en_port_profile *prof,
				bool carry_xdp_prog)
अणु
	काष्ठा bpf_prog *xdp_prog;
	पूर्णांक i, t;

	mlx4_en_copy_priv(पंचांगp, priv, prof);

	अगर (mlx4_en_alloc_resources(पंचांगp)) अणु
		en_warn(priv,
			"%s: Resource allocation failed, using previous configuration\n",
			__func__);
		क्रम (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++) अणु
			kमुक्त(पंचांगp->tx_ring[t]);
			kमुक्त(पंचांगp->tx_cq[t]);
		पूर्ण
		वापस -ENOMEM;
	पूर्ण

	/* All rx_rings has the same xdp_prog.  Pick the first one. */
	xdp_prog = rcu_dereference_रक्षित(
		priv->rx_ring[0]->xdp_prog,
		lockdep_is_held(&priv->mdev->state_lock));

	अगर (xdp_prog && carry_xdp_prog) अणु
		bpf_prog_add(xdp_prog, पंचांगp->rx_ring_num);
		क्रम (i = 0; i < पंचांगp->rx_ring_num; i++)
			rcu_assign_poपूर्णांकer(पंचांगp->rx_ring[i]->xdp_prog,
					   xdp_prog);
	पूर्ण

	वापस 0;
पूर्ण

व्योम mlx4_en_safe_replace_resources(काष्ठा mlx4_en_priv *priv,
				    काष्ठा mlx4_en_priv *पंचांगp)
अणु
	mlx4_en_मुक्त_resources(priv);
	mlx4_en_update_priv(priv, पंचांगp);
पूर्ण

व्योम mlx4_en_destroy_netdev(काष्ठा net_device *dev)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;

	en_dbg(DRV, priv, "Destroying netdev on port:%d\n", priv->port);

	/* Unरेजिस्टर device - this will बंद the port अगर it was up */
	अगर (priv->रेजिस्टरed) अणु
		devlink_port_type_clear(mlx4_get_devlink_port(mdev->dev,
							      priv->port));
		unरेजिस्टर_netdev(dev);
	पूर्ण

	अगर (priv->allocated)
		mlx4_मुक्त_hwq_res(mdev->dev, &priv->res, MLX4_EN_PAGE_SIZE);

	cancel_delayed_work(&priv->stats_task);
	cancel_delayed_work(&priv->service_task);
	/* flush any pending task क्रम this netdev */
	flush_workqueue(mdev->workqueue);

	अगर (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_TS)
		mlx4_en_हटाओ_बारtamp(mdev);

	/* Detach the netdev so tasks would not attempt to access it */
	mutex_lock(&mdev->state_lock);
	mdev->pndev[priv->port] = शून्य;
	mdev->upper[priv->port] = शून्य;

#अगर_घोषित CONFIG_RFS_ACCEL
	mlx4_en_cleanup_filters(priv);
#पूर्ण_अगर

	mlx4_en_मुक्त_resources(priv);
	mutex_unlock(&mdev->state_lock);

	मुक्त_netdev(dev);
पूर्ण

अटल bool mlx4_en_check_xdp_mtu(काष्ठा net_device *dev, पूर्णांक mtu)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	अगर (mtu > MLX4_EN_MAX_XDP_MTU) अणु
		en_err(priv, "mtu:%d > max:%d when XDP prog is attached\n",
		       mtu, MLX4_EN_MAX_XDP_MTU);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक mlx4_en_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	पूर्णांक err = 0;

	en_dbg(DRV, priv, "Change MTU called - current:%d new:%d\n",
		 dev->mtu, new_mtu);

	अगर (priv->tx_ring_num[TX_XDP] &&
	    !mlx4_en_check_xdp_mtu(dev, new_mtu))
		वापस -EOPNOTSUPP;

	dev->mtu = new_mtu;

	अगर (netअगर_running(dev)) अणु
		mutex_lock(&mdev->state_lock);
		अगर (!mdev->device_up) अणु
			/* NIC is probably restarting - let restart task reset
			 * the port */
			en_dbg(DRV, priv, "Change MTU called with card down!?\n");
		पूर्ण अन्यथा अणु
			mlx4_en_stop_port(dev, 1);
			err = mlx4_en_start_port(dev);
			अगर (err) अणु
				en_err(priv, "Failed restarting port:%d\n",
					 priv->port);
				अगर (!test_and_set_bit(MLX4_EN_STATE_FLAG_RESTARTING,
						      &priv->state))
					queue_work(mdev->workqueue, &priv->restart_task);
			पूर्ण
		पूर्ण
		mutex_unlock(&mdev->state_lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_hwtstamp_set(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा hwtstamp_config config;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	/* reserved क्रम future extensions */
	अगर (config.flags)
		वापस -EINVAL;

	/* device करोesn't support समय stamping */
	अगर (!(mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_TS))
		वापस -EINVAL;

	/* TX HW बारtamp */
	चयन (config.tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
	हाल HWTSTAMP_TX_ON:
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	/* RX HW बारtamp */
	चयन (config.rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		अवरोध;
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_SOME:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_NTP_ALL:
		config.rx_filter = HWTSTAMP_FILTER_ALL;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	अगर (mlx4_en_reset_config(dev, config, dev->features)) अणु
		config.tx_type = HWTSTAMP_TX_OFF;
		config.rx_filter = HWTSTAMP_FILTER_NONE;
	पूर्ण

	वापस copy_to_user(अगरr->अगरr_data, &config,
			    माप(config)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक mlx4_en_hwtstamp_get(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

	वापस copy_to_user(अगरr->अगरr_data, &priv->hwtstamp_config,
			    माप(priv->hwtstamp_config)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक mlx4_en_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		वापस mlx4_en_hwtstamp_set(dev, अगरr);
	हाल SIOCGHWTSTAMP:
		वापस mlx4_en_hwtstamp_get(dev, अगरr);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल netdev_features_t mlx4_en_fix_features(काष्ठा net_device *netdev,
					      netdev_features_t features)
अणु
	काष्ठा mlx4_en_priv *en_priv = netdev_priv(netdev);
	काष्ठा mlx4_en_dev *mdev = en_priv->mdev;

	/* Since there is no support क्रम separate RX C-TAG/S-TAG vlan accel
	 * enable/disable make sure S-TAG flag is always in same state as
	 * C-TAG.
	 */
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX &&
	    !(mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SKIP_OUTER_VLAN))
		features |= NETIF_F_HW_VLAN_STAG_RX;
	अन्यथा
		features &= ~NETIF_F_HW_VLAN_STAG_RX;

	वापस features;
पूर्ण

अटल पूर्णांक mlx4_en_set_features(काष्ठा net_device *netdev,
		netdev_features_t features)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(netdev);
	bool reset = false;
	पूर्णांक ret = 0;

	अगर (DEV_FEATURE_CHANGED(netdev, features, NETIF_F_RXFCS)) अणु
		en_info(priv, "Turn %s RX-FCS\n",
			(features & NETIF_F_RXFCS) ? "ON" : "OFF");
		reset = true;
	पूर्ण

	अगर (DEV_FEATURE_CHANGED(netdev, features, NETIF_F_RXALL)) अणु
		u8 ignore_fcs_value = (features & NETIF_F_RXALL) ? 1 : 0;

		en_info(priv, "Turn %s RX-ALL\n",
			ignore_fcs_value ? "ON" : "OFF");
		ret = mlx4_SET_PORT_fcs_check(priv->mdev->dev,
					      priv->port, ignore_fcs_value);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (DEV_FEATURE_CHANGED(netdev, features, NETIF_F_HW_VLAN_CTAG_RX)) अणु
		en_info(priv, "Turn %s RX vlan strip offload\n",
			(features & NETIF_F_HW_VLAN_CTAG_RX) ? "ON" : "OFF");
		reset = true;
	पूर्ण

	अगर (DEV_FEATURE_CHANGED(netdev, features, NETIF_F_HW_VLAN_CTAG_TX))
		en_info(priv, "Turn %s TX vlan strip offload\n",
			(features & NETIF_F_HW_VLAN_CTAG_TX) ? "ON" : "OFF");

	अगर (DEV_FEATURE_CHANGED(netdev, features, NETIF_F_HW_VLAN_STAG_TX))
		en_info(priv, "Turn %s TX S-VLAN strip offload\n",
			(features & NETIF_F_HW_VLAN_STAG_TX) ? "ON" : "OFF");

	अगर (DEV_FEATURE_CHANGED(netdev, features, NETIF_F_LOOPBACK)) अणु
		en_info(priv, "Turn %s loopback\n",
			(features & NETIF_F_LOOPBACK) ? "ON" : "OFF");
		mlx4_en_update_loopback_state(netdev, features);
	पूर्ण

	अगर (reset) अणु
		ret = mlx4_en_reset_config(netdev, priv->hwtstamp_config,
					   features);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_en_set_vf_mac(काष्ठा net_device *dev, पूर्णांक queue, u8 *mac)
अणु
	काष्ठा mlx4_en_priv *en_priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = en_priv->mdev;

	वापस mlx4_set_vf_mac(mdev->dev, en_priv->port, queue, mac);
पूर्ण

अटल पूर्णांक mlx4_en_set_vf_vlan(काष्ठा net_device *dev, पूर्णांक vf, u16 vlan, u8 qos,
			       __be16 vlan_proto)
अणु
	काष्ठा mlx4_en_priv *en_priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = en_priv->mdev;

	वापस mlx4_set_vf_vlan(mdev->dev, en_priv->port, vf, vlan, qos,
				vlan_proto);
पूर्ण

अटल पूर्णांक mlx4_en_set_vf_rate(काष्ठा net_device *dev, पूर्णांक vf, पूर्णांक min_tx_rate,
			       पूर्णांक max_tx_rate)
अणु
	काष्ठा mlx4_en_priv *en_priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = en_priv->mdev;

	वापस mlx4_set_vf_rate(mdev->dev, en_priv->port, vf, min_tx_rate,
				max_tx_rate);
पूर्ण

अटल पूर्णांक mlx4_en_set_vf_spoofchk(काष्ठा net_device *dev, पूर्णांक vf, bool setting)
अणु
	काष्ठा mlx4_en_priv *en_priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = en_priv->mdev;

	वापस mlx4_set_vf_spoofchk(mdev->dev, en_priv->port, vf, setting);
पूर्ण

अटल पूर्णांक mlx4_en_get_vf_config(काष्ठा net_device *dev, पूर्णांक vf, काष्ठा अगरla_vf_info *ivf)
अणु
	काष्ठा mlx4_en_priv *en_priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = en_priv->mdev;

	वापस mlx4_get_vf_config(mdev->dev, en_priv->port, vf, ivf);
पूर्ण

अटल पूर्णांक mlx4_en_set_vf_link_state(काष्ठा net_device *dev, पूर्णांक vf, पूर्णांक link_state)
अणु
	काष्ठा mlx4_en_priv *en_priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = en_priv->mdev;

	वापस mlx4_set_vf_link_state(mdev->dev, en_priv->port, vf, link_state);
पूर्ण

अटल पूर्णांक mlx4_en_get_vf_stats(काष्ठा net_device *dev, पूर्णांक vf,
				काष्ठा अगरla_vf_stats *vf_stats)
अणु
	काष्ठा mlx4_en_priv *en_priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = en_priv->mdev;

	वापस mlx4_get_vf_stats(mdev->dev, en_priv->port, vf, vf_stats);
पूर्ण

#घोषणा PORT_ID_BYTE_LEN 8
अटल पूर्णांक mlx4_en_get_phys_port_id(काष्ठा net_device *dev,
				    काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_dev *mdev = priv->mdev->dev;
	पूर्णांक i;
	u64 phys_port_id = mdev->caps.phys_port_id[priv->port];

	अगर (!phys_port_id)
		वापस -EOPNOTSUPP;

	ppid->id_len = माप(phys_port_id);
	क्रम (i = PORT_ID_BYTE_LEN - 1; i >= 0; --i) अणु
		ppid->id[i] =  phys_port_id & 0xff;
		phys_port_id >>= 8;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlx4_udp_tunnel_sync(काष्ठा net_device *dev, अचिन्हित पूर्णांक table)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा udp_tunnel_info ti;
	पूर्णांक ret;

	udp_tunnel_nic_get_port(dev, table, 0, &ti);
	priv->vxlan_port = ti.port;

	ret = mlx4_config_vxlan_port(priv->mdev->dev, priv->vxlan_port);
	अगर (ret)
		वापस ret;

	वापस mlx4_SET_PORT_VXLAN(priv->mdev->dev, priv->port,
				   VXLAN_STEER_BY_OUTER_MAC,
				   !!priv->vxlan_port);
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info mlx4_udp_tunnels = अणु
	.sync_table	= mlx4_udp_tunnel_sync,
	.flags		= UDP_TUNNEL_NIC_INFO_MAY_SLEEP |
			  UDP_TUNNEL_NIC_INFO_IPV4_ONLY,
	.tables		= अणु
		अणु .n_entries = 1, .tunnel_types = UDP_TUNNEL_TYPE_VXLAN, पूर्ण,
	पूर्ण,
पूर्ण;

अटल netdev_features_t mlx4_en_features_check(काष्ठा sk_buff *skb,
						काष्ठा net_device *dev,
						netdev_features_t features)
अणु
	features = vlan_features_check(skb, features);
	features = vxlan_features_check(skb, features);

	/* The ConnectX-3 करोesn't support outer IPv6 checksums but it करोes
	 * support inner IPv6 checksums and segmentation so  we need to
	 * strip that feature अगर this is an IPv6 encapsulated frame.
	 */
	अगर (skb->encapsulation &&
	    (skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		काष्ठा mlx4_en_priv *priv = netdev_priv(dev);

		अगर (!priv->vxlan_port ||
		    (ip_hdr(skb)->version != 4) ||
		    (udp_hdr(skb)->dest != priv->vxlan_port))
			features &= ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
	पूर्ण

	वापस features;
पूर्ण

अटल पूर्णांक mlx4_en_set_tx_maxrate(काष्ठा net_device *dev, पूर्णांक queue_index, u32 maxrate)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_tx_ring *tx_ring = priv->tx_ring[TX][queue_index];
	काष्ठा mlx4_update_qp_params params;
	पूर्णांक err;

	अगर (!(priv->mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_QP_RATE_LIMIT))
		वापस -EOPNOTSUPP;

	/* rate provided to us in Mbs, check अगर it fits पूर्णांकo 12 bits, अगर not use Gbs */
	अगर (maxrate >> 12) अणु
		params.rate_unit = MLX4_QP_RATE_LIMIT_GBS;
		params.rate_val  = maxrate / 1000;
	पूर्ण अन्यथा अगर (maxrate) अणु
		params.rate_unit = MLX4_QP_RATE_LIMIT_MBS;
		params.rate_val  = maxrate;
	पूर्ण अन्यथा अणु /* zero serves to revoke the QP rate-limitation */
		params.rate_unit = 0;
		params.rate_val  = 0;
	पूर्ण

	err = mlx4_update_qp(priv->mdev->dev, tx_ring->qpn, MLX4_UPDATE_QP_RATE_LIMIT,
			     &params);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_xdp_set(काष्ठा net_device *dev, काष्ठा bpf_prog *prog)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_port_profile new_prof;
	काष्ठा bpf_prog *old_prog;
	काष्ठा mlx4_en_priv *पंचांगp;
	पूर्णांक tx_changed = 0;
	पूर्णांक xdp_ring_num;
	पूर्णांक port_up = 0;
	पूर्णांक err;
	पूर्णांक i;

	xdp_ring_num = prog ? priv->rx_ring_num : 0;

	/* No need to reconfigure buffers when simply swapping the
	 * program क्रम a new one.
	 */
	अगर (priv->tx_ring_num[TX_XDP] == xdp_ring_num) अणु
		अगर (prog)
			bpf_prog_add(prog, priv->rx_ring_num - 1);

		mutex_lock(&mdev->state_lock);
		क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
			old_prog = rcu_dereference_रक्षित(
					priv->rx_ring[i]->xdp_prog,
					lockdep_is_held(&mdev->state_lock));
			rcu_assign_poपूर्णांकer(priv->rx_ring[i]->xdp_prog, prog);
			अगर (old_prog)
				bpf_prog_put(old_prog);
		पूर्ण
		mutex_unlock(&mdev->state_lock);
		वापस 0;
	पूर्ण

	अगर (!mlx4_en_check_xdp_mtu(dev, dev->mtu))
		वापस -EOPNOTSUPP;

	पंचांगp = kzalloc(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	अगर (prog)
		bpf_prog_add(prog, priv->rx_ring_num - 1);

	mutex_lock(&mdev->state_lock);
	स_नकल(&new_prof, priv->prof, माप(काष्ठा mlx4_en_port_profile));
	new_prof.tx_ring_num[TX_XDP] = xdp_ring_num;

	अगर (priv->tx_ring_num[TX] + xdp_ring_num > MAX_TX_RINGS) अणु
		tx_changed = 1;
		new_prof.tx_ring_num[TX] =
			MAX_TX_RINGS - ALIGN(xdp_ring_num, priv->prof->num_up);
		en_warn(priv, "Reducing the number of TX rings, to not exceed the max total rings number.\n");
	पूर्ण

	err = mlx4_en_try_alloc_resources(priv, पंचांगp, &new_prof, false);
	अगर (err) अणु
		अगर (prog)
			bpf_prog_sub(prog, priv->rx_ring_num - 1);
		जाओ unlock_out;
	पूर्ण

	अगर (priv->port_up) अणु
		port_up = 1;
		mlx4_en_stop_port(dev, 1);
	पूर्ण

	mlx4_en_safe_replace_resources(priv, पंचांगp);
	अगर (tx_changed)
		netअगर_set_real_num_tx_queues(dev, priv->tx_ring_num[TX]);

	क्रम (i = 0; i < priv->rx_ring_num; i++) अणु
		old_prog = rcu_dereference_रक्षित(
					priv->rx_ring[i]->xdp_prog,
					lockdep_is_held(&mdev->state_lock));
		rcu_assign_poपूर्णांकer(priv->rx_ring[i]->xdp_prog, prog);
		अगर (old_prog)
			bpf_prog_put(old_prog);
	पूर्ण

	अगर (port_up) अणु
		err = mlx4_en_start_port(dev);
		अगर (err) अणु
			en_err(priv, "Failed starting port %d for XDP change\n",
			       priv->port);
			अगर (!test_and_set_bit(MLX4_EN_STATE_FLAG_RESTARTING, &priv->state))
				queue_work(mdev->workqueue, &priv->restart_task);
		पूर्ण
	पूर्ण

unlock_out:
	mutex_unlock(&mdev->state_lock);
	kमुक्त(पंचांगp);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_xdp(काष्ठा net_device *dev, काष्ठा netdev_bpf *xdp)
अणु
	चयन (xdp->command) अणु
	हाल XDP_SETUP_PROG:
		वापस mlx4_xdp_set(dev, xdp->prog);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops mlx4_netdev_ops = अणु
	.nकरो_खोलो		= mlx4_en_खोलो,
	.nकरो_stop		= mlx4_en_बंद,
	.nकरो_start_xmit		= mlx4_en_xmit,
	.nकरो_select_queue	= mlx4_en_select_queue,
	.nकरो_get_stats64	= mlx4_en_get_stats64,
	.nकरो_set_rx_mode	= mlx4_en_set_rx_mode,
	.nकरो_set_mac_address	= mlx4_en_set_mac,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_change_mtu		= mlx4_en_change_mtu,
	.nकरो_करो_ioctl		= mlx4_en_ioctl,
	.nकरो_tx_समयout		= mlx4_en_tx_समयout,
	.nकरो_vlan_rx_add_vid	= mlx4_en_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= mlx4_en_vlan_rx_समाप्त_vid,
	.nकरो_set_features	= mlx4_en_set_features,
	.nकरो_fix_features	= mlx4_en_fix_features,
	.nकरो_setup_tc		= __mlx4_en_setup_tc,
#अगर_घोषित CONFIG_RFS_ACCEL
	.nकरो_rx_flow_steer	= mlx4_en_filter_rfs,
#पूर्ण_अगर
	.nकरो_get_phys_port_id	= mlx4_en_get_phys_port_id,
	.nकरो_features_check	= mlx4_en_features_check,
	.nकरो_set_tx_maxrate	= mlx4_en_set_tx_maxrate,
	.nकरो_bpf		= mlx4_xdp,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops mlx4_netdev_ops_master = अणु
	.nकरो_खोलो		= mlx4_en_खोलो,
	.nकरो_stop		= mlx4_en_बंद,
	.nकरो_start_xmit		= mlx4_en_xmit,
	.nकरो_select_queue	= mlx4_en_select_queue,
	.nकरो_get_stats64	= mlx4_en_get_stats64,
	.nकरो_set_rx_mode	= mlx4_en_set_rx_mode,
	.nकरो_set_mac_address	= mlx4_en_set_mac,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_change_mtu		= mlx4_en_change_mtu,
	.nकरो_tx_समयout		= mlx4_en_tx_समयout,
	.nकरो_vlan_rx_add_vid	= mlx4_en_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= mlx4_en_vlan_rx_समाप्त_vid,
	.nकरो_set_vf_mac		= mlx4_en_set_vf_mac,
	.nकरो_set_vf_vlan	= mlx4_en_set_vf_vlan,
	.nकरो_set_vf_rate	= mlx4_en_set_vf_rate,
	.nकरो_set_vf_spoofchk	= mlx4_en_set_vf_spoofchk,
	.nकरो_set_vf_link_state	= mlx4_en_set_vf_link_state,
	.nकरो_get_vf_stats       = mlx4_en_get_vf_stats,
	.nकरो_get_vf_config	= mlx4_en_get_vf_config,
	.nकरो_set_features	= mlx4_en_set_features,
	.nकरो_fix_features	= mlx4_en_fix_features,
	.nकरो_setup_tc		= __mlx4_en_setup_tc,
#अगर_घोषित CONFIG_RFS_ACCEL
	.nकरो_rx_flow_steer	= mlx4_en_filter_rfs,
#पूर्ण_अगर
	.nकरो_get_phys_port_id	= mlx4_en_get_phys_port_id,
	.nकरो_features_check	= mlx4_en_features_check,
	.nकरो_set_tx_maxrate	= mlx4_en_set_tx_maxrate,
	.nकरो_bpf		= mlx4_xdp,
पूर्ण;

काष्ठा mlx4_en_bond अणु
	काष्ठा work_काष्ठा work;
	काष्ठा mlx4_en_priv *priv;
	पूर्णांक is_bonded;
	काष्ठा mlx4_port_map port_map;
पूर्ण;

अटल व्योम mlx4_en_bond_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx4_en_bond *bond = container_of(work,
						     काष्ठा mlx4_en_bond,
						     work);
	पूर्णांक err = 0;
	काष्ठा mlx4_dev *dev = bond->priv->mdev->dev;

	अगर (bond->is_bonded) अणु
		अगर (!mlx4_is_bonded(dev)) अणु
			err = mlx4_bond(dev);
			अगर (err)
				en_err(bond->priv, "Fail to bond device\n");
		पूर्ण
		अगर (!err) अणु
			err = mlx4_port_map_set(dev, &bond->port_map);
			अगर (err)
				en_err(bond->priv, "Fail to set port map [%d][%d]: %d\n",
				       bond->port_map.port1,
				       bond->port_map.port2,
				       err);
		पूर्ण
	पूर्ण अन्यथा अगर (mlx4_is_bonded(dev)) अणु
		err = mlx4_unbond(dev);
		अगर (err)
			en_err(bond->priv, "Fail to unbond device\n");
	पूर्ण
	dev_put(bond->priv->dev);
	kमुक्त(bond);
पूर्ण

अटल पूर्णांक mlx4_en_queue_bond_work(काष्ठा mlx4_en_priv *priv, पूर्णांक is_bonded,
				   u8 v2p_p1, u8 v2p_p2)
अणु
	काष्ठा mlx4_en_bond *bond = शून्य;

	bond = kzalloc(माप(*bond), GFP_ATOMIC);
	अगर (!bond)
		वापस -ENOMEM;

	INIT_WORK(&bond->work, mlx4_en_bond_work);
	bond->priv = priv;
	bond->is_bonded = is_bonded;
	bond->port_map.port1 = v2p_p1;
	bond->port_map.port2 = v2p_p2;
	dev_hold(priv->dev);
	queue_work(priv->mdev->workqueue, &bond->work);
	वापस 0;
पूर्ण

पूर्णांक mlx4_en_netdev_event(काष्ठा notअगरier_block *this,
			 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *ndev = netdev_notअगरier_info_to_dev(ptr);
	u8 port = 0;
	काष्ठा mlx4_en_dev *mdev;
	काष्ठा mlx4_dev *dev;
	पूर्णांक i, num_eth_ports = 0;
	bool करो_bond = true;
	काष्ठा mlx4_en_priv *priv;
	u8 v2p_port1 = 0;
	u8 v2p_port2 = 0;

	अगर (!net_eq(dev_net(ndev), &init_net))
		वापस NOTIFY_DONE;

	mdev = container_of(this, काष्ठा mlx4_en_dev, nb);
	dev = mdev->dev;

	/* Go पूर्णांकo this mode only when two network devices set on two ports
	 * of the same mlx4 device are slaves of the same bonding master
	 */
	mlx4_क्रमeach_port(i, dev, MLX4_PORT_TYPE_ETH) अणु
		++num_eth_ports;
		अगर (!port && (mdev->pndev[i] == ndev))
			port = i;
		mdev->upper[i] = mdev->pndev[i] ?
			netdev_master_upper_dev_get(mdev->pndev[i]) : शून्य;
		/* condition not met: network device is a slave */
		अगर (!mdev->upper[i])
			करो_bond = false;
		अगर (num_eth_ports < 2)
			जारी;
		/* condition not met: same master */
		अगर (mdev->upper[i] != mdev->upper[i-1])
			करो_bond = false;
	पूर्ण
	/* condition not met: 2 salves */
	करो_bond = (num_eth_ports ==  2) ? करो_bond : false;

	/* handle only events that come with enough info */
	अगर ((करो_bond && (event != NETDEV_BONDING_INFO)) || !port)
		वापस NOTIFY_DONE;

	priv = netdev_priv(ndev);
	अगर (करो_bond) अणु
		काष्ठा netdev_notअगरier_bonding_info *notअगरier_info = ptr;
		काष्ठा netdev_bonding_info *bonding_info =
			&notअगरier_info->bonding_info;

		/* required mode 1, 2 or 4 */
		अगर ((bonding_info->master.bond_mode != BOND_MODE_ACTIVEBACKUP) &&
		    (bonding_info->master.bond_mode != BOND_MODE_XOR) &&
		    (bonding_info->master.bond_mode != BOND_MODE_8023AD))
			करो_bond = false;

		/* require exactly 2 slaves */
		अगर (bonding_info->master.num_slaves != 2)
			करो_bond = false;

		/* calc v2p */
		अगर (करो_bond) अणु
			अगर (bonding_info->master.bond_mode ==
			    BOND_MODE_ACTIVEBACKUP) अणु
				/* in active-backup mode भव ports are
				 * mapped to the physical port of the active
				 * slave */
				अगर (bonding_info->slave.state ==
				    BOND_STATE_BACKUP) अणु
					अगर (port == 1) अणु
						v2p_port1 = 2;
						v2p_port2 = 2;
					पूर्ण अन्यथा अणु
						v2p_port1 = 1;
						v2p_port2 = 1;
					पूर्ण
				पूर्ण अन्यथा अणु /* BOND_STATE_ACTIVE */
					अगर (port == 1) अणु
						v2p_port1 = 1;
						v2p_port2 = 1;
					पूर्ण अन्यथा अणु
						v2p_port1 = 2;
						v2p_port2 = 2;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु /* Active-Active */
				/* in active-active mode a भव port is
				 * mapped to the native physical port अगर and only
				 * अगर the physical port is up */
				__s8 link = bonding_info->slave.link;

				अगर (port == 1)
					v2p_port2 = 2;
				अन्यथा
					v2p_port1 = 1;
				अगर ((link == BOND_LINK_UP) ||
				    (link == BOND_LINK_FAIL)) अणु
					अगर (port == 1)
						v2p_port1 = 1;
					अन्यथा
						v2p_port2 = 2;
				पूर्ण अन्यथा अणु /* BOND_LINK_DOWN || BOND_LINK_BACK */
					अगर (port == 1)
						v2p_port1 = 2;
					अन्यथा
						v2p_port2 = 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	mlx4_en_queue_bond_work(priv, करो_bond,
				v2p_port1, v2p_port2);

	वापस NOTIFY_DONE;
पूर्ण

व्योम mlx4_en_update_pfc_stats_biपंचांगap(काष्ठा mlx4_dev *dev,
				     काष्ठा mlx4_en_stats_biपंचांगap *stats_biपंचांगap,
				     u8 rx_ppp, u8 rx_छोड़ो,
				     u8 tx_ppp, u8 tx_छोड़ो)
अणु
	पूर्णांक last_i = NUM_MAIN_STATS + NUM_PORT_STATS + NUM_PF_STATS;

	अगर (!mlx4_is_slave(dev) &&
	    (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_FLOWSTATS_EN)) अणु
		mutex_lock(&stats_biपंचांगap->mutex);
		biपंचांगap_clear(stats_biपंचांगap->biपंचांगap, last_i, NUM_FLOW_STATS);

		अगर (rx_ppp)
			biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i,
				   NUM_FLOW_PRIORITY_STATS_RX);
		last_i += NUM_FLOW_PRIORITY_STATS_RX;

		अगर (rx_छोड़ो && !(rx_ppp))
			biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i,
				   NUM_FLOW_STATS_RX);
		last_i += NUM_FLOW_STATS_RX;

		अगर (tx_ppp)
			biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i,
				   NUM_FLOW_PRIORITY_STATS_TX);
		last_i += NUM_FLOW_PRIORITY_STATS_TX;

		अगर (tx_छोड़ो && !(tx_ppp))
			biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i,
				   NUM_FLOW_STATS_TX);
		last_i += NUM_FLOW_STATS_TX;

		mutex_unlock(&stats_biपंचांगap->mutex);
	पूर्ण
पूर्ण

व्योम mlx4_en_set_stats_biपंचांगap(काष्ठा mlx4_dev *dev,
			      काष्ठा mlx4_en_stats_biपंचांगap *stats_biपंचांगap,
			      u8 rx_ppp, u8 rx_छोड़ो,
			      u8 tx_ppp, u8 tx_छोड़ो)
अणु
	पूर्णांक last_i = 0;

	mutex_init(&stats_biपंचांगap->mutex);
	biपंचांगap_zero(stats_biपंचांगap->biपंचांगap, NUM_ALL_STATS);

	अगर (mlx4_is_slave(dev)) अणु
		biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i +
					 MLX4_FIND_NETDEV_STAT(rx_packets), 1);
		biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i +
					 MLX4_FIND_NETDEV_STAT(tx_packets), 1);
		biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i +
					 MLX4_FIND_NETDEV_STAT(rx_bytes), 1);
		biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i +
					 MLX4_FIND_NETDEV_STAT(tx_bytes), 1);
		biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i +
					 MLX4_FIND_NETDEV_STAT(rx_dropped), 1);
		biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i +
					 MLX4_FIND_NETDEV_STAT(tx_dropped), 1);
	पूर्ण अन्यथा अणु
		biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i, NUM_MAIN_STATS);
	पूर्ण
	last_i += NUM_MAIN_STATS;

	biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i, NUM_PORT_STATS);
	last_i += NUM_PORT_STATS;

	अगर (mlx4_is_master(dev))
		biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i,
			   NUM_PF_STATS);
	last_i += NUM_PF_STATS;

	mlx4_en_update_pfc_stats_biपंचांगap(dev, stats_biपंचांगap,
					rx_ppp, rx_छोड़ो,
					tx_ppp, tx_छोड़ो);
	last_i += NUM_FLOW_STATS;

	अगर (!mlx4_is_slave(dev))
		biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i, NUM_PKT_STATS);
	last_i += NUM_PKT_STATS;

	biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i, NUM_XDP_STATS);
	last_i += NUM_XDP_STATS;

	अगर (!mlx4_is_slave(dev))
		biपंचांगap_set(stats_biपंचांगap->biपंचांगap, last_i, NUM_PHY_STATS);
	last_i += NUM_PHY_STATS;
पूर्ण

पूर्णांक mlx4_en_init_netdev(काष्ठा mlx4_en_dev *mdev, पूर्णांक port,
			काष्ठा mlx4_en_port_profile *prof)
अणु
	काष्ठा net_device *dev;
	काष्ठा mlx4_en_priv *priv;
	पूर्णांक i, t;
	पूर्णांक err;

	dev = alloc_etherdev_mqs(माप(काष्ठा mlx4_en_priv),
				 MAX_TX_RINGS, MAX_RX_RINGS);
	अगर (dev == शून्य)
		वापस -ENOMEM;

	netअगर_set_real_num_tx_queues(dev, prof->tx_ring_num[TX]);
	netअगर_set_real_num_rx_queues(dev, prof->rx_ring_num);

	SET_NETDEV_DEV(dev, &mdev->dev->persist->pdev->dev);
	dev->dev_port = port - 1;

	/*
	 * Initialize driver निजी data
	 */

	priv = netdev_priv(dev);
	स_रखो(priv, 0, माप(काष्ठा mlx4_en_priv));
	priv->counter_index = MLX4_SINK_COUNTER_INDEX(mdev->dev);
	spin_lock_init(&priv->stats_lock);
	INIT_WORK(&priv->rx_mode_task, mlx4_en_करो_set_rx_mode);
	INIT_WORK(&priv->restart_task, mlx4_en_restart);
	INIT_WORK(&priv->linkstate_task, mlx4_en_linkstate);
	INIT_DELAYED_WORK(&priv->stats_task, mlx4_en_करो_get_stats);
	INIT_DELAYED_WORK(&priv->service_task, mlx4_en_service_task);
#अगर_घोषित CONFIG_RFS_ACCEL
	INIT_LIST_HEAD(&priv->filters);
	spin_lock_init(&priv->filters_lock);
#पूर्ण_अगर

	priv->dev = dev;
	priv->mdev = mdev;
	priv->ddev = &mdev->pdev->dev;
	priv->prof = prof;
	priv->port = port;
	priv->port_up = false;
	priv->flags = prof->flags;
	priv->pflags = MLX4_EN_PRIV_FLAGS_BLUEFLAME;
	priv->ctrl_flags = cpu_to_be32(MLX4_WQE_CTRL_CQ_UPDATE |
			MLX4_WQE_CTRL_SOLICITED);
	priv->num_tx_rings_p_up = mdev->profile.max_num_tx_rings_p_up;
	priv->tx_work_limit = MLX4_EN_DEFAULT_TX_WORK;
	netdev_rss_key_fill(priv->rss_key, माप(priv->rss_key));

	क्रम (t = 0; t < MLX4_EN_NUM_TX_TYPES; t++) अणु
		priv->tx_ring_num[t] = prof->tx_ring_num[t];
		अगर (!priv->tx_ring_num[t])
			जारी;

		priv->tx_ring[t] = kसुस्मृति(MAX_TX_RINGS,
					   माप(काष्ठा mlx4_en_tx_ring *),
					   GFP_KERNEL);
		अगर (!priv->tx_ring[t]) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		priv->tx_cq[t] = kसुस्मृति(MAX_TX_RINGS,
					 माप(काष्ठा mlx4_en_cq *),
					 GFP_KERNEL);
		अगर (!priv->tx_cq[t]) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण
	priv->rx_ring_num = prof->rx_ring_num;
	priv->cqe_factor = (mdev->dev->caps.cqe_size == 64) ? 1 : 0;
	priv->cqe_size = mdev->dev->caps.cqe_size;
	priv->mac_index = -1;
	priv->msg_enable = MLX4_EN_MSG_LEVEL;
#अगर_घोषित CONFIG_MLX4_EN_DCB
	अगर (!mlx4_is_slave(priv->mdev->dev)) अणु
		u8 prio;

		क्रम (prio = 0; prio < IEEE_8021QAZ_MAX_TCS; ++prio) अणु
			priv->ets.prio_tc[prio] = prio;
			priv->ets.tc_tsa[prio]  = IEEE_8021QAZ_TSA_VENDOR;
		पूर्ण

		priv->dcbx_cap = DCB_CAP_DCBX_VER_CEE | DCB_CAP_DCBX_HOST |
			DCB_CAP_DCBX_VER_IEEE;
		priv->flags |= MLX4_EN_DCB_ENABLED;
		priv->cee_config.pfc_state = false;

		क्रम (i = 0; i < MLX4_EN_NUM_UP_HIGH; i++)
			priv->cee_config.dcb_pfc[i] = pfc_disabled;

		अगर (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ETS_CFG) अणु
			dev->dcbnl_ops = &mlx4_en_dcbnl_ops;
		पूर्ण अन्यथा अणु
			en_info(priv, "enabling only PFC DCB ops\n");
			dev->dcbnl_ops = &mlx4_en_dcbnl_pfc_ops;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	क्रम (i = 0; i < MLX4_EN_MAC_HASH_SIZE; ++i)
		INIT_HLIST_HEAD(&priv->mac_hash[i]);

	/* Query क्रम शेष mac and max mtu */
	priv->max_mtu = mdev->dev->caps.eth_mtu_cap[priv->port];

	अगर (mdev->dev->caps.rx_checksum_flags_port[priv->port] &
	    MLX4_RX_CSUM_MODE_VAL_NON_TCP_UDP)
		priv->flags |= MLX4_EN_FLAG_RX_CSUM_NON_TCP_UDP;

	/* Set शेष MAC */
	dev->addr_len = ETH_ALEN;
	mlx4_en_u64_to_mac(dev->dev_addr, mdev->dev->caps.def_mac[priv->port]);
	अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
		en_err(priv, "Port: %d, invalid mac burned: %pM, quitting\n",
		       priv->port, dev->dev_addr);
		err = -EINVAL;
		जाओ out;
	पूर्ण अन्यथा अगर (mlx4_is_slave(priv->mdev->dev) &&
		   (priv->mdev->dev->port_अक्रमom_macs & 1 << priv->port)) अणु
		/* Ranकरोm MAC was asचिन्हित in mlx4_slave_cap
		 * in mlx4_core module
		 */
		dev->addr_assign_type |= NET_ADDR_RANDOM;
		en_warn(priv, "Assigned random MAC address %pM\n", dev->dev_addr);
	पूर्ण

	स_नकल(priv->current_mac, dev->dev_addr, माप(priv->current_mac));

	priv->stride = roundup_घात_of_two(माप(काष्ठा mlx4_en_rx_desc) +
					  DS_SIZE * MLX4_EN_MAX_RX_FRAGS);
	err = mlx4_en_alloc_resources(priv);
	अगर (err)
		जाओ out;

	/* Initialize समय stamping config */
	priv->hwtstamp_config.flags = 0;
	priv->hwtstamp_config.tx_type = HWTSTAMP_TX_OFF;
	priv->hwtstamp_config.rx_filter = HWTSTAMP_FILTER_NONE;

	/* Allocate page क्रम receive rings */
	err = mlx4_alloc_hwq_res(mdev->dev, &priv->res,
				MLX4_EN_PAGE_SIZE);
	अगर (err) अणु
		en_err(priv, "Failed to allocate page for rx qps\n");
		जाओ out;
	पूर्ण
	priv->allocated = 1;

	/*
	 * Initialize netdev entry poपूर्णांकs
	 */
	अगर (mlx4_is_master(priv->mdev->dev))
		dev->netdev_ops = &mlx4_netdev_ops_master;
	अन्यथा
		dev->netdev_ops = &mlx4_netdev_ops;
	dev->watchकरोg_समयo = MLX4_EN_WATCHDOG_TIMEOUT;
	netअगर_set_real_num_tx_queues(dev, priv->tx_ring_num[TX]);
	netअगर_set_real_num_rx_queues(dev, priv->rx_ring_num);

	dev->ethtool_ops = &mlx4_en_ethtool_ops;

	/*
	 * Set driver features
	 */
	dev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	अगर (mdev->LSO_support)
		dev->hw_features |= NETIF_F_TSO | NETIF_F_TSO6;

	अगर (mdev->dev->caps.tunnel_offload_mode ==
	    MLX4_TUNNEL_OFFLOAD_MODE_VXLAN) अणु
		dev->hw_features |= NETIF_F_GSO_UDP_TUNNEL |
				    NETIF_F_GSO_UDP_TUNNEL_CSUM |
				    NETIF_F_GSO_PARTIAL;
		dev->features    |= NETIF_F_GSO_UDP_TUNNEL |
				    NETIF_F_GSO_UDP_TUNNEL_CSUM |
				    NETIF_F_GSO_PARTIAL;
		dev->gso_partial_features = NETIF_F_GSO_UDP_TUNNEL_CSUM;
		dev->hw_enc_features = NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
				       NETIF_F_RXCSUM |
				       NETIF_F_TSO | NETIF_F_TSO6 |
				       NETIF_F_GSO_UDP_TUNNEL |
				       NETIF_F_GSO_UDP_TUNNEL_CSUM |
				       NETIF_F_GSO_PARTIAL;

		dev->udp_tunnel_nic_info = &mlx4_udp_tunnels;
	पूर्ण

	dev->vlan_features = dev->hw_features;

	dev->hw_features |= NETIF_F_RXCSUM | NETIF_F_RXHASH;
	dev->features = dev->hw_features | NETIF_F_HIGHDMA |
			NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX |
			NETIF_F_HW_VLAN_CTAG_FILTER;
	dev->hw_features |= NETIF_F_LOOPBACK |
			NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX;

	अगर (!(mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SKIP_OUTER_VLAN)) अणु
		dev->features |= NETIF_F_HW_VLAN_STAG_RX |
			NETIF_F_HW_VLAN_STAG_FILTER;
		dev->hw_features |= NETIF_F_HW_VLAN_STAG_RX;
	पूर्ण

	अगर (mlx4_is_slave(mdev->dev)) अणु
		bool vlan_offload_disabled;
		पूर्णांक phv;

		err = get_phv_bit(mdev->dev, port, &phv);
		अगर (!err && phv) अणु
			dev->hw_features |= NETIF_F_HW_VLAN_STAG_TX;
			priv->pflags |= MLX4_EN_PRIV_FLAGS_PHV;
		पूर्ण
		err = mlx4_get_is_vlan_offload_disabled(mdev->dev, port,
							&vlan_offload_disabled);
		अगर (!err && vlan_offload_disabled) अणु
			dev->hw_features &= ~(NETIF_F_HW_VLAN_CTAG_TX |
					      NETIF_F_HW_VLAN_CTAG_RX |
					      NETIF_F_HW_VLAN_STAG_TX |
					      NETIF_F_HW_VLAN_STAG_RX);
			dev->features &= ~(NETIF_F_HW_VLAN_CTAG_TX |
					   NETIF_F_HW_VLAN_CTAG_RX |
					   NETIF_F_HW_VLAN_STAG_TX |
					   NETIF_F_HW_VLAN_STAG_RX);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_PHV_EN &&
		    !(mdev->dev->caps.flags2 &
		      MLX4_DEV_CAP_FLAG2_SKIP_OUTER_VLAN))
			dev->hw_features |= NETIF_F_HW_VLAN_STAG_TX;
	पूर्ण

	अगर (mdev->dev->caps.flags & MLX4_DEV_CAP_FLAG_FCS_KEEP)
		dev->hw_features |= NETIF_F_RXFCS;

	अगर (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_IGNORE_FCS)
		dev->hw_features |= NETIF_F_RXALL;

	अगर (mdev->dev->caps.steering_mode ==
	    MLX4_STEERING_MODE_DEVICE_MANAGED &&
	    mdev->dev->caps.dmfs_high_steer_mode != MLX4_STEERING_DMFS_A0_STATIC)
		dev->hw_features |= NETIF_F_NTUPLE;

	अगर (mdev->dev->caps.steering_mode != MLX4_STEERING_MODE_A0)
		dev->priv_flags |= IFF_UNICAST_FLT;

	/* Setting a शेष hash function value */
	अगर (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RSS_TOP) अणु
		priv->rss_hash_fn = ETH_RSS_HASH_TOP;
	पूर्ण अन्यथा अगर (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RSS_XOR) अणु
		priv->rss_hash_fn = ETH_RSS_HASH_XOR;
	पूर्ण अन्यथा अणु
		en_warn(priv,
			"No RSS hash capabilities exposed, using Toeplitz\n");
		priv->rss_hash_fn = ETH_RSS_HASH_TOP;
	पूर्ण

	/* MTU range: 68 - hw-specअगरic max */
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = priv->max_mtu;

	mdev->pndev[port] = dev;
	mdev->upper[port] = शून्य;

	netअगर_carrier_off(dev);
	mlx4_en_set_शेष_moderation(priv);

	en_warn(priv, "Using %d TX rings\n", prof->tx_ring_num[TX]);
	en_warn(priv, "Using %d RX rings\n", prof->rx_ring_num);

	mlx4_en_update_loopback_state(priv->dev, priv->dev->features);

	/* Configure port */
	mlx4_en_calc_rx_buf(dev);
	err = mlx4_SET_PORT_general(mdev->dev, priv->port,
				    priv->rx_skb_size + ETH_FCS_LEN,
				    prof->tx_छोड़ो, prof->tx_ppp,
				    prof->rx_छोड़ो, prof->rx_ppp);
	अगर (err) अणु
		en_err(priv, "Failed setting port general configurations for port %d, with error %d\n",
		       priv->port, err);
		जाओ out;
	पूर्ण

	अगर (mdev->dev->caps.tunnel_offload_mode == MLX4_TUNNEL_OFFLOAD_MODE_VXLAN) अणु
		err = mlx4_SET_PORT_VXLAN(mdev->dev, priv->port, VXLAN_STEER_BY_OUTER_MAC, 1);
		अगर (err) अणु
			en_err(priv, "Failed setting port L2 tunnel configuration, err %d\n",
			       err);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Init port */
	en_warn(priv, "Initializing port\n");
	err = mlx4_INIT_PORT(mdev->dev, priv->port);
	अगर (err) अणु
		en_err(priv, "Failed Initializing port\n");
		जाओ out;
	पूर्ण
	queue_delayed_work(mdev->workqueue, &priv->stats_task, STATS_DELAY);

	/* Initialize समय stamp mechanism */
	अगर (mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_TS)
		mlx4_en_init_बारtamp(mdev);

	queue_delayed_work(mdev->workqueue, &priv->service_task,
			   SERVICE_TASK_DELAY);

	mlx4_en_set_stats_biपंचांगap(mdev->dev, &priv->stats_biपंचांगap,
				 mdev->profile.prof[priv->port].rx_ppp,
				 mdev->profile.prof[priv->port].rx_छोड़ो,
				 mdev->profile.prof[priv->port].tx_ppp,
				 mdev->profile.prof[priv->port].tx_छोड़ो);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		en_err(priv, "Netdev registration failed for port %d\n", port);
		जाओ out;
	पूर्ण

	priv->रेजिस्टरed = 1;
	devlink_port_type_eth_set(mlx4_get_devlink_port(mdev->dev, priv->port),
				  dev);

	वापस 0;

out:
	mlx4_en_destroy_netdev(dev);
	वापस err;
पूर्ण

पूर्णांक mlx4_en_reset_config(काष्ठा net_device *dev,
			 काष्ठा hwtstamp_config ts_config,
			 netdev_features_t features)
अणु
	काष्ठा mlx4_en_priv *priv = netdev_priv(dev);
	काष्ठा mlx4_en_dev *mdev = priv->mdev;
	काष्ठा mlx4_en_port_profile new_prof;
	काष्ठा mlx4_en_priv *पंचांगp;
	पूर्णांक port_up = 0;
	पूर्णांक err = 0;

	अगर (priv->hwtstamp_config.tx_type == ts_config.tx_type &&
	    priv->hwtstamp_config.rx_filter == ts_config.rx_filter &&
	    !DEV_FEATURE_CHANGED(dev, features, NETIF_F_HW_VLAN_CTAG_RX) &&
	    !DEV_FEATURE_CHANGED(dev, features, NETIF_F_RXFCS))
		वापस 0; /* Nothing to change */

	अगर (DEV_FEATURE_CHANGED(dev, features, NETIF_F_HW_VLAN_CTAG_RX) &&
	    (features & NETIF_F_HW_VLAN_CTAG_RX) &&
	    (priv->hwtstamp_config.rx_filter != HWTSTAMP_FILTER_NONE)) अणु
		en_warn(priv, "Can't turn ON rx vlan offload while time-stamping rx filter is ON\n");
		वापस -EINVAL;
	पूर्ण

	पंचांगp = kzalloc(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	mutex_lock(&mdev->state_lock);

	स_नकल(&new_prof, priv->prof, माप(काष्ठा mlx4_en_port_profile));
	स_नकल(&new_prof.hwtstamp_config, &ts_config, माप(ts_config));

	err = mlx4_en_try_alloc_resources(priv, पंचांगp, &new_prof, true);
	अगर (err)
		जाओ out;

	अगर (priv->port_up) अणु
		port_up = 1;
		mlx4_en_stop_port(dev, 1);
	पूर्ण

	mlx4_en_safe_replace_resources(priv, पंचांगp);

	अगर (DEV_FEATURE_CHANGED(dev, features, NETIF_F_HW_VLAN_CTAG_RX)) अणु
		अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
			dev->features |= NETIF_F_HW_VLAN_CTAG_RX;
		अन्यथा
			dev->features &= ~NETIF_F_HW_VLAN_CTAG_RX;
	पूर्ण अन्यथा अगर (ts_config.rx_filter == HWTSTAMP_FILTER_NONE) अणु
		/* RX समय-stamping is OFF, update the RX vlan offload
		 * to the latest wanted state
		 */
		अगर (dev->wanted_features & NETIF_F_HW_VLAN_CTAG_RX)
			dev->features |= NETIF_F_HW_VLAN_CTAG_RX;
		अन्यथा
			dev->features &= ~NETIF_F_HW_VLAN_CTAG_RX;
	पूर्ण

	अगर (DEV_FEATURE_CHANGED(dev, features, NETIF_F_RXFCS)) अणु
		अगर (features & NETIF_F_RXFCS)
			dev->features |= NETIF_F_RXFCS;
		अन्यथा
			dev->features &= ~NETIF_F_RXFCS;
	पूर्ण

	/* RX vlan offload and RX समय-stamping can't co-exist !
	 * Regardless of the caller's choice,
	 * Turn Off RX vlan offload in हाल of समय-stamping is ON
	 */
	अगर (ts_config.rx_filter != HWTSTAMP_FILTER_NONE) अणु
		अगर (dev->features & NETIF_F_HW_VLAN_CTAG_RX)
			en_warn(priv, "Turning off RX vlan offload since RX time-stamping is ON\n");
		dev->features &= ~NETIF_F_HW_VLAN_CTAG_RX;
	पूर्ण

	अगर (port_up) अणु
		err = mlx4_en_start_port(dev);
		अगर (err)
			en_err(priv, "Failed starting port\n");
	पूर्ण

	अगर (!err)
		err = mlx4_en_moderation_update(priv);
out:
	mutex_unlock(&mdev->state_lock);
	kमुक्त(पंचांगp);
	अगर (!err)
		netdev_features_change(dev);
	वापस err;
पूर्ण
