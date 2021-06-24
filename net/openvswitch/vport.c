<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2007-2014 Nicira, Inc.
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/jhash.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/percpu.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/compat.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/module.h>

#समावेश "datapath.h"
#समावेश "vport.h"
#समावेश "vport-internal_dev.h"

अटल LIST_HEAD(vport_ops_list);

/* Protected by RCU पढ़ो lock क्रम पढ़ोing, ovs_mutex क्रम writing. */
अटल काष्ठा hlist_head *dev_table;
#घोषणा VPORT_HASH_BUCKETS 1024

/**
 *	ovs_vport_init - initialize vport subप्रणाली
 *
 * Called at module load समय to initialize the vport subप्रणाली.
 */
पूर्णांक ovs_vport_init(व्योम)
अणु
	dev_table = kसुस्मृति(VPORT_HASH_BUCKETS, माप(काष्ठा hlist_head),
			    GFP_KERNEL);
	अगर (!dev_table)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 *	ovs_vport_निकास - shutकरोwn vport subप्रणाली
 *
 * Called at module निकास समय to shutकरोwn the vport subप्रणाली.
 */
व्योम ovs_vport_निकास(व्योम)
अणु
	kमुक्त(dev_table);
पूर्ण

अटल काष्ठा hlist_head *hash_bucket(स्थिर काष्ठा net *net, स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक hash = jhash(name, म_माप(name), (अचिन्हित दीर्घ) net);
	वापस &dev_table[hash & (VPORT_HASH_BUCKETS - 1)];
पूर्ण

पूर्णांक __ovs_vport_ops_रेजिस्टर(काष्ठा vport_ops *ops)
अणु
	पूर्णांक err = -EEXIST;
	काष्ठा vport_ops *o;

	ovs_lock();
	list_क्रम_each_entry(o, &vport_ops_list, list)
		अगर (ops->type == o->type)
			जाओ errout;

	list_add_tail(&ops->list, &vport_ops_list);
	err = 0;
errout:
	ovs_unlock();
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__ovs_vport_ops_रेजिस्टर);

व्योम ovs_vport_ops_unरेजिस्टर(काष्ठा vport_ops *ops)
अणु
	ovs_lock();
	list_del(&ops->list);
	ovs_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(ovs_vport_ops_unरेजिस्टर);

/**
 *	ovs_vport_locate - find a port that has alपढ़ोy been created
 *
 * @net: network namespace
 * @name: name of port to find
 *
 * Must be called with ovs or RCU पढ़ो lock.
 */
काष्ठा vport *ovs_vport_locate(स्थिर काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा hlist_head *bucket = hash_bucket(net, name);
	काष्ठा vport *vport;

	hlist_क्रम_each_entry_rcu(vport, bucket, hash_node,
				 lockdep_ovsl_is_held())
		अगर (!म_भेद(name, ovs_vport_name(vport)) &&
		    net_eq(ovs_dp_get_net(vport->dp), net))
			वापस vport;

	वापस शून्य;
पूर्ण

/**
 *	ovs_vport_alloc - allocate and initialize new vport
 *
 * @priv_size: Size of निजी data area to allocate.
 * @ops: vport device ops
 * @parms: inक्रमmation about new vport.
 *
 * Allocate and initialize a new vport defined by @ops.  The vport will contain
 * a निजी data area of size @priv_size that can be accessed using
 * vport_priv().  Some parameters of the vport will be initialized from @parms.
 * @vports that are no दीर्घer needed should be released with
 * vport_मुक्त().
 */
काष्ठा vport *ovs_vport_alloc(पूर्णांक priv_size, स्थिर काष्ठा vport_ops *ops,
			      स्थिर काष्ठा vport_parms *parms)
अणु
	काष्ठा vport *vport;
	माप_प्रकार alloc_size;

	alloc_size = माप(काष्ठा vport);
	अगर (priv_size) अणु
		alloc_size = ALIGN(alloc_size, VPORT_ALIGN);
		alloc_size += priv_size;
	पूर्ण

	vport = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!vport)
		वापस ERR_PTR(-ENOMEM);

	vport->dp = parms->dp;
	vport->port_no = parms->port_no;
	vport->ops = ops;
	INIT_HLIST_NODE(&vport->dp_hash_node);

	अगर (ovs_vport_set_upcall_portids(vport, parms->upcall_portids)) अणु
		kमुक्त(vport);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस vport;
पूर्ण
EXPORT_SYMBOL_GPL(ovs_vport_alloc);

/**
 *	ovs_vport_मुक्त - uninitialize and मुक्त vport
 *
 * @vport: vport to मुक्त
 *
 * Frees a vport allocated with vport_alloc() when it is no दीर्घer needed.
 *
 * The caller must ensure that an RCU grace period has passed since the last
 * समय @vport was in a datapath.
 */
व्योम ovs_vport_मुक्त(काष्ठा vport *vport)
अणु
	/* vport is मुक्तd from RCU callback or error path, Thereक्रमe
	 * it is safe to use raw dereference.
	 */
	kमुक्त(rcu_dereference_raw(vport->upcall_portids));
	kमुक्त(vport);
पूर्ण
EXPORT_SYMBOL_GPL(ovs_vport_मुक्त);

अटल काष्ठा vport_ops *ovs_vport_lookup(स्थिर काष्ठा vport_parms *parms)
अणु
	काष्ठा vport_ops *ops;

	list_क्रम_each_entry(ops, &vport_ops_list, list)
		अगर (ops->type == parms->type)
			वापस ops;

	वापस शून्य;
पूर्ण

/**
 *	ovs_vport_add - add vport device (क्रम kernel callers)
 *
 * @parms: Inक्रमmation about new vport.
 *
 * Creates a new vport with the specअगरied configuration (which is dependent on
 * device type).  ovs_mutex must be held.
 */
काष्ठा vport *ovs_vport_add(स्थिर काष्ठा vport_parms *parms)
अणु
	काष्ठा vport_ops *ops;
	काष्ठा vport *vport;

	ops = ovs_vport_lookup(parms);
	अगर (ops) अणु
		काष्ठा hlist_head *bucket;

		अगर (!try_module_get(ops->owner))
			वापस ERR_PTR(-EAFNOSUPPORT);

		vport = ops->create(parms);
		अगर (IS_ERR(vport)) अणु
			module_put(ops->owner);
			वापस vport;
		पूर्ण

		bucket = hash_bucket(ovs_dp_get_net(vport->dp),
				     ovs_vport_name(vport));
		hlist_add_head_rcu(&vport->hash_node, bucket);
		वापस vport;
	पूर्ण

	/* Unlock to attempt module load and वापस -EAGAIN अगर load
	 * was successful as we need to restart the port addition
	 * workflow.
	 */
	ovs_unlock();
	request_module("vport-type-%d", parms->type);
	ovs_lock();

	अगर (!ovs_vport_lookup(parms))
		वापस ERR_PTR(-EAFNOSUPPORT);
	अन्यथा
		वापस ERR_PTR(-EAGAIN);
पूर्ण

/**
 *	ovs_vport_set_options - modअगरy existing vport device (क्रम kernel callers)
 *
 * @vport: vport to modअगरy.
 * @options: New configuration.
 *
 * Modअगरies an existing device with the specअगरied configuration (which is
 * dependent on device type).  ovs_mutex must be held.
 */
पूर्णांक ovs_vport_set_options(काष्ठा vport *vport, काष्ठा nlattr *options)
अणु
	अगर (!vport->ops->set_options)
		वापस -EOPNOTSUPP;
	वापस vport->ops->set_options(vport, options);
पूर्ण

/**
 *	ovs_vport_del - delete existing vport device
 *
 * @vport: vport to delete.
 *
 * Detaches @vport from its datapath and destroys it.  ovs_mutex must
 * be held.
 */
व्योम ovs_vport_del(काष्ठा vport *vport)
अणु
	hlist_del_rcu(&vport->hash_node);
	module_put(vport->ops->owner);
	vport->ops->destroy(vport);
पूर्ण

/**
 *	ovs_vport_get_stats - retrieve device stats
 *
 * @vport: vport from which to retrieve the stats
 * @stats: location to store stats
 *
 * Retrieves transmit, receive, and error stats क्रम the given device.
 *
 * Must be called with ovs_mutex or rcu_पढ़ो_lock.
 */
व्योम ovs_vport_get_stats(काष्ठा vport *vport, काष्ठा ovs_vport_stats *stats)
अणु
	स्थिर काष्ठा rtnl_link_stats64 *dev_stats;
	काष्ठा rtnl_link_stats64 temp;

	dev_stats = dev_get_stats(vport->dev, &temp);
	stats->rx_errors  = dev_stats->rx_errors;
	stats->tx_errors  = dev_stats->tx_errors;
	stats->tx_dropped = dev_stats->tx_dropped;
	stats->rx_dropped = dev_stats->rx_dropped;

	stats->rx_bytes	  = dev_stats->rx_bytes;
	stats->rx_packets = dev_stats->rx_packets;
	stats->tx_bytes	  = dev_stats->tx_bytes;
	stats->tx_packets = dev_stats->tx_packets;
पूर्ण

/**
 *	ovs_vport_get_options - retrieve device options
 *
 * @vport: vport from which to retrieve the options.
 * @skb: sk_buff where options should be appended.
 *
 * Retrieves the configuration of the given device, appending an
 * %OVS_VPORT_ATTR_OPTIONS attribute that in turn contains nested
 * vport-specअगरic attributes to @skb.
 *
 * Returns 0 अगर successful, -EMSGSIZE अगर @skb has insufficient room, or another
 * negative error code अगर a real error occurred.  If an error occurs, @skb is
 * left unmodअगरied.
 *
 * Must be called with ovs_mutex or rcu_पढ़ो_lock.
 */
पूर्णांक ovs_vport_get_options(स्थिर काष्ठा vport *vport, काष्ठा sk_buff *skb)
अणु
	काष्ठा nlattr *nla;
	पूर्णांक err;

	अगर (!vport->ops->get_options)
		वापस 0;

	nla = nla_nest_start_noflag(skb, OVS_VPORT_ATTR_OPTIONS);
	अगर (!nla)
		वापस -EMSGSIZE;

	err = vport->ops->get_options(vport, skb);
	अगर (err) अणु
		nla_nest_cancel(skb, nla);
		वापस err;
	पूर्ण

	nla_nest_end(skb, nla);
	वापस 0;
पूर्ण

/**
 *	ovs_vport_set_upcall_portids - set upcall portids of @vport.
 *
 * @vport: vport to modअगरy.
 * @ids: new configuration, an array of port ids.
 *
 * Sets the vport's upcall_portids to @ids.
 *
 * Returns 0 अगर successful, -EINVAL अगर @ids is zero length or cannot be parsed
 * as an array of U32.
 *
 * Must be called with ovs_mutex.
 */
पूर्णांक ovs_vport_set_upcall_portids(काष्ठा vport *vport, स्थिर काष्ठा nlattr *ids)
अणु
	काष्ठा vport_portids *old, *vport_portids;

	अगर (!nla_len(ids) || nla_len(ids) % माप(u32))
		वापस -EINVAL;

	old = ovsl_dereference(vport->upcall_portids);

	vport_portids = kदो_स्मृति(माप(*vport_portids) + nla_len(ids),
				GFP_KERNEL);
	अगर (!vport_portids)
		वापस -ENOMEM;

	vport_portids->n_ids = nla_len(ids) / माप(u32);
	vport_portids->rn_ids = reciprocal_value(vport_portids->n_ids);
	nla_स_नकल(vport_portids->ids, ids, nla_len(ids));

	rcu_assign_poपूर्णांकer(vport->upcall_portids, vport_portids);

	अगर (old)
		kमुक्त_rcu(old, rcu);
	वापस 0;
पूर्ण

/**
 *	ovs_vport_get_upcall_portids - get the upcall_portids of @vport.
 *
 * @vport: vport from which to retrieve the portids.
 * @skb: sk_buff where portids should be appended.
 *
 * Retrieves the configuration of the given vport, appending the
 * %OVS_VPORT_ATTR_UPCALL_PID attribute which is the array of upcall
 * portids to @skb.
 *
 * Returns 0 अगर successful, -EMSGSIZE अगर @skb has insufficient room.
 * If an error occurs, @skb is left unmodअगरied.  Must be called with
 * ovs_mutex or rcu_पढ़ो_lock.
 */
पूर्णांक ovs_vport_get_upcall_portids(स्थिर काष्ठा vport *vport,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा vport_portids *ids;

	ids = rcu_dereference_ovsl(vport->upcall_portids);

	अगर (vport->dp->user_features & OVS_DP_F_VPORT_PIDS)
		वापस nla_put(skb, OVS_VPORT_ATTR_UPCALL_PID,
			       ids->n_ids * माप(u32), (व्योम *)ids->ids);
	अन्यथा
		वापस nla_put_u32(skb, OVS_VPORT_ATTR_UPCALL_PID, ids->ids[0]);
पूर्ण

/**
 *	ovs_vport_find_upcall_portid - find the upcall portid to send upcall.
 *
 * @vport: vport from which the missed packet is received.
 * @skb: skb that the missed packet was received.
 *
 * Uses the skb_get_hash() to select the upcall portid to send the
 * upcall.
 *
 * Returns the portid of the target socket.  Must be called with rcu_पढ़ो_lock.
 */
u32 ovs_vport_find_upcall_portid(स्थिर काष्ठा vport *vport,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा vport_portids *ids;
	u32 ids_index;
	u32 hash;

	ids = rcu_dereference(vport->upcall_portids);

	/* If there is only one portid, select it in the fast-path. */
	अगर (ids->n_ids == 1)
		वापस ids->ids[0];

	hash = skb_get_hash(skb);
	ids_index = hash - ids->n_ids * reciprocal_भागide(hash, ids->rn_ids);
	वापस ids->ids[ids_index];
पूर्ण

/**
 *	ovs_vport_receive - pass up received packet to the datapath क्रम processing
 *
 * @vport: vport that received the packet
 * @skb: skb that was received
 * @tun_info: tunnel (अगर any) that carried packet
 *
 * Must be called with rcu_पढ़ो_lock.  The packet cannot be shared and
 * skb->data should poपूर्णांक to the Ethernet header.
 */
पूर्णांक ovs_vport_receive(काष्ठा vport *vport, काष्ठा sk_buff *skb,
		      स्थिर काष्ठा ip_tunnel_info *tun_info)
अणु
	काष्ठा sw_flow_key key;
	पूर्णांक error;

	OVS_CB(skb)->input_vport = vport;
	OVS_CB(skb)->mru = 0;
	OVS_CB(skb)->cutlen = 0;
	अगर (unlikely(dev_net(skb->dev) != ovs_dp_get_net(vport->dp))) अणु
		u32 mark;

		mark = skb->mark;
		skb_scrub_packet(skb, true);
		skb->mark = mark;
		tun_info = शून्य;
	पूर्ण

	/* Extract flow from 'skb' into 'key'. */
	error = ovs_flow_key_extract(tun_info, skb, &key);
	अगर (unlikely(error)) अणु
		kमुक्त_skb(skb);
		वापस error;
	पूर्ण
	ovs_dp_process_packet(skb, &key);
	वापस 0;
पूर्ण

अटल पूर्णांक packet_length(स्थिर काष्ठा sk_buff *skb,
			 काष्ठा net_device *dev)
अणु
	पूर्णांक length = skb->len - dev->hard_header_len;

	अगर (!skb_vlan_tag_present(skb) &&
	    eth_type_vlan(skb->protocol))
		length -= VLAN_HLEN;

	/* Don't subtract क्रम multiple VLAN tags. Most (all?) drivers allow
	 * (ETH_LEN + VLAN_HLEN) in addition to the mtu value, but almost none
	 * account क्रम 802.1ad. e.g. is_skb_क्रमwardable().
	 */

	वापस length > 0 ? length : 0;
पूर्ण

व्योम ovs_vport_send(काष्ठा vport *vport, काष्ठा sk_buff *skb, u8 mac_proto)
अणु
	पूर्णांक mtu = vport->dev->mtu;

	चयन (vport->dev->type) अणु
	हाल ARPHRD_NONE:
		अगर (mac_proto == MAC_PROTO_ETHERNET) अणु
			skb_reset_network_header(skb);
			skb_reset_mac_len(skb);
			skb->protocol = htons(ETH_P_TEB);
		पूर्ण अन्यथा अगर (mac_proto != MAC_PROTO_NONE) अणु
			WARN_ON_ONCE(1);
			जाओ drop;
		पूर्ण
		अवरोध;
	हाल ARPHRD_ETHER:
		अगर (mac_proto != MAC_PROTO_ETHERNET)
			जाओ drop;
		अवरोध;
	शेष:
		जाओ drop;
	पूर्ण

	अगर (unlikely(packet_length(skb, vport->dev) > mtu &&
		     !skb_is_gso(skb))) अणु
		vport->dev->stats.tx_errors++;
		अगर (vport->dev->flags & IFF_UP)
			net_warn_ratelimited("%s: dropped over-mtu packet: "
					     "%d > %d\n", vport->dev->name,
					     packet_length(skb, vport->dev),
					     mtu);
		जाओ drop;
	पूर्ण

	skb->dev = vport->dev;
	vport->ops->send(skb);
	वापस;

drop:
	kमुक्त_skb(skb);
पूर्ण
