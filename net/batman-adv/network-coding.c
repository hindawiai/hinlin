<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Martin Hundebथचll, Jeppe Ledet-Pedersen
 */

#समावेश "network-coding.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/init.h>
#समावेश <linux/jhash.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pअक्रमom.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/workqueue.h>
#समावेश <uapi/linux/batadv_packet.h>

#समावेश "hash.h"
#समावेश "log.h"
#समावेश "originator.h"
#समावेश "routing.h"
#समावेश "send.h"
#समावेश "tvlv.h"

अटल काष्ठा lock_class_key batadv_nc_coding_hash_lock_class_key;
अटल काष्ठा lock_class_key batadv_nc_decoding_hash_lock_class_key;

अटल व्योम batadv_nc_worker(काष्ठा work_काष्ठा *work);
अटल पूर्णांक batadv_nc_recv_coded_packet(काष्ठा sk_buff *skb,
				       काष्ठा batadv_hard_अगरace *recv_अगर);

/**
 * batadv_nc_init() - one-समय initialization क्रम network coding
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
पूर्णांक __init batadv_nc_init(व्योम)
अणु
	पूर्णांक ret;

	/* Register our packet type */
	ret = batadv_recv_handler_रेजिस्टर(BATADV_CODED,
					   batadv_nc_recv_coded_packet);

	वापस ret;
पूर्ण

/**
 * batadv_nc_start_समयr() - initialise the nc periodic worker
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_nc_start_समयr(काष्ठा batadv_priv *bat_priv)
अणु
	queue_delayed_work(batadv_event_workqueue, &bat_priv->nc.work,
			   msecs_to_jअगरfies(10));
पूर्ण

/**
 * batadv_nc_tvlv_container_update() - update the network coding tvlv container
 *  after network coding setting change
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_nc_tvlv_container_update(काष्ठा batadv_priv *bat_priv)
अणु
	अक्षर nc_mode;

	nc_mode = atomic_पढ़ो(&bat_priv->network_coding);

	चयन (nc_mode) अणु
	हाल 0:
		batadv_tvlv_container_unरेजिस्टर(bat_priv, BATADV_TVLV_NC, 1);
		अवरोध;
	हाल 1:
		batadv_tvlv_container_रेजिस्टर(bat_priv, BATADV_TVLV_NC, 1,
					       शून्य, 0);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * batadv_nc_status_update() - update the network coding tvlv container after
 *  network coding setting change
 * @net_dev: the soft पूर्णांकerface net device
 */
व्योम batadv_nc_status_update(काष्ठा net_device *net_dev)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(net_dev);

	batadv_nc_tvlv_container_update(bat_priv);
पूर्ण

/**
 * batadv_nc_tvlv_ogm_handler_v1() - process incoming nc tvlv container
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig: the orig_node of the ogm
 * @flags: flags indicating the tvlv state (see batadv_tvlv_handler_flags)
 * @tvlv_value: tvlv buffer containing the gateway data
 * @tvlv_value_len: tvlv buffer length
 */
अटल व्योम batadv_nc_tvlv_ogm_handler_v1(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_orig_node *orig,
					  u8 flags,
					  व्योम *tvlv_value, u16 tvlv_value_len)
अणु
	अगर (flags & BATADV_TVLV_HANDLER_OGM_CIFNOTFND)
		clear_bit(BATADV_ORIG_CAPA_HAS_NC, &orig->capabilities);
	अन्यथा
		set_bit(BATADV_ORIG_CAPA_HAS_NC, &orig->capabilities);
पूर्ण

/**
 * batadv_nc_mesh_init() - initialise coding hash table and start housekeeping
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
पूर्णांक batadv_nc_mesh_init(काष्ठा batadv_priv *bat_priv)
अणु
	bat_priv->nc.बारtamp_fwd_flush = jअगरfies;
	bat_priv->nc.बारtamp_snअगरfed_purge = jअगरfies;

	अगर (bat_priv->nc.coding_hash || bat_priv->nc.decoding_hash)
		वापस 0;

	bat_priv->nc.coding_hash = batadv_hash_new(128);
	अगर (!bat_priv->nc.coding_hash)
		जाओ err;

	batadv_hash_set_lock_class(bat_priv->nc.coding_hash,
				   &batadv_nc_coding_hash_lock_class_key);

	bat_priv->nc.decoding_hash = batadv_hash_new(128);
	अगर (!bat_priv->nc.decoding_hash)
		जाओ err;

	batadv_hash_set_lock_class(bat_priv->nc.decoding_hash,
				   &batadv_nc_decoding_hash_lock_class_key);

	INIT_DELAYED_WORK(&bat_priv->nc.work, batadv_nc_worker);
	batadv_nc_start_समयr(bat_priv);

	batadv_tvlv_handler_रेजिस्टर(bat_priv, batadv_nc_tvlv_ogm_handler_v1,
				     शून्य, BATADV_TVLV_NC, 1,
				     BATADV_TVLV_HANDLER_OGM_CIFNOTFND);
	batadv_nc_tvlv_container_update(bat_priv);
	वापस 0;

err:
	वापस -ENOMEM;
पूर्ण

/**
 * batadv_nc_init_bat_priv() - initialise the nc specअगरic bat_priv variables
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_nc_init_bat_priv(काष्ठा batadv_priv *bat_priv)
अणु
	atomic_set(&bat_priv->network_coding, 0);
	bat_priv->nc.min_tq = 200;
	bat_priv->nc.max_fwd_delay = 10;
	bat_priv->nc.max_buffer_समय = 200;
पूर्ण

/**
 * batadv_nc_init_orig() - initialise the nc fields of an orig_node
 * @orig_node: the orig_node which is going to be initialised
 */
व्योम batadv_nc_init_orig(काष्ठा batadv_orig_node *orig_node)
अणु
	INIT_LIST_HEAD(&orig_node->in_coding_list);
	INIT_LIST_HEAD(&orig_node->out_coding_list);
	spin_lock_init(&orig_node->in_coding_list_lock);
	spin_lock_init(&orig_node->out_coding_list_lock);
पूर्ण

/**
 * batadv_nc_node_release() - release nc_node from lists and queue क्रम मुक्त
 *  after rcu grace period
 * @ref: kref poपूर्णांकer of the nc_node
 */
अटल व्योम batadv_nc_node_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_nc_node *nc_node;

	nc_node = container_of(ref, काष्ठा batadv_nc_node, refcount);

	batadv_orig_node_put(nc_node->orig_node);
	kमुक्त_rcu(nc_node, rcu);
पूर्ण

/**
 * batadv_nc_node_put() - decrement the nc_node refcounter and possibly
 *  release it
 * @nc_node: nc_node to be मुक्त'd
 */
अटल व्योम batadv_nc_node_put(काष्ठा batadv_nc_node *nc_node)
अणु
	kref_put(&nc_node->refcount, batadv_nc_node_release);
पूर्ण

/**
 * batadv_nc_path_release() - release nc_path from lists and queue क्रम मुक्त
 *  after rcu grace period
 * @ref: kref poपूर्णांकer of the nc_path
 */
अटल व्योम batadv_nc_path_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_nc_path *nc_path;

	nc_path = container_of(ref, काष्ठा batadv_nc_path, refcount);

	kमुक्त_rcu(nc_path, rcu);
पूर्ण

/**
 * batadv_nc_path_put() - decrement the nc_path refcounter and possibly
 *  release it
 * @nc_path: nc_path to be मुक्त'd
 */
अटल व्योम batadv_nc_path_put(काष्ठा batadv_nc_path *nc_path)
अणु
	kref_put(&nc_path->refcount, batadv_nc_path_release);
पूर्ण

/**
 * batadv_nc_packet_मुक्त() - मुक्तs nc packet
 * @nc_packet: the nc packet to मुक्त
 * @dropped: whether the packet is मुक्तd because is dropped
 */
अटल व्योम batadv_nc_packet_मुक्त(काष्ठा batadv_nc_packet *nc_packet,
				  bool dropped)
अणु
	अगर (dropped)
		kमुक्त_skb(nc_packet->skb);
	अन्यथा
		consume_skb(nc_packet->skb);

	batadv_nc_path_put(nc_packet->nc_path);
	kमुक्त(nc_packet);
पूर्ण

/**
 * batadv_nc_to_purge_nc_node() - checks whether an nc node has to be purged
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @nc_node: the nc node to check
 *
 * Return: true अगर the entry has to be purged now, false otherwise
 */
अटल bool batadv_nc_to_purge_nc_node(काष्ठा batadv_priv *bat_priv,
				       काष्ठा batadv_nc_node *nc_node)
अणु
	अगर (atomic_पढ़ो(&bat_priv->mesh_state) != BATADV_MESH_ACTIVE)
		वापस true;

	वापस batadv_has_समयd_out(nc_node->last_seen, BATADV_NC_NODE_TIMEOUT);
पूर्ण

/**
 * batadv_nc_to_purge_nc_path_coding() - checks whether an nc path has समयd out
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @nc_path: the nc path to check
 *
 * Return: true अगर the entry has to be purged now, false otherwise
 */
अटल bool batadv_nc_to_purge_nc_path_coding(काष्ठा batadv_priv *bat_priv,
					      काष्ठा batadv_nc_path *nc_path)
अणु
	अगर (atomic_पढ़ो(&bat_priv->mesh_state) != BATADV_MESH_ACTIVE)
		वापस true;

	/* purge the path when no packets has been added क्रम 10 बार the
	 * max_fwd_delay समय
	 */
	वापस batadv_has_समयd_out(nc_path->last_valid,
				    bat_priv->nc.max_fwd_delay * 10);
पूर्ण

/**
 * batadv_nc_to_purge_nc_path_decoding() - checks whether an nc path has समयd
 *  out
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @nc_path: the nc path to check
 *
 * Return: true अगर the entry has to be purged now, false otherwise
 */
अटल bool batadv_nc_to_purge_nc_path_decoding(काष्ठा batadv_priv *bat_priv,
						काष्ठा batadv_nc_path *nc_path)
अणु
	अगर (atomic_पढ़ो(&bat_priv->mesh_state) != BATADV_MESH_ACTIVE)
		वापस true;

	/* purge the path when no packets has been added क्रम 10 बार the
	 * max_buffer समय
	 */
	वापस batadv_has_समयd_out(nc_path->last_valid,
				    bat_priv->nc.max_buffer_समय * 10);
पूर्ण

/**
 * batadv_nc_purge_orig_nc_nodes() - go through list of nc nodes and purge stale
 *  entries
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @list: list of nc nodes
 * @lock: nc node list lock
 * @to_purge: function in अक्षरge to decide whether an entry has to be purged or
 *	      not. This function takes the nc node as argument and has to वापस
 *	      a boolean value: true अगर the entry has to be deleted, false
 *	      otherwise
 */
अटल व्योम
batadv_nc_purge_orig_nc_nodes(काष्ठा batadv_priv *bat_priv,
			      काष्ठा list_head *list,
			      spinlock_t *lock,
			      bool (*to_purge)(काष्ठा batadv_priv *,
					       काष्ठा batadv_nc_node *))
अणु
	काष्ठा batadv_nc_node *nc_node, *nc_node_पंचांगp;

	/* For each nc_node in list */
	spin_lock_bh(lock);
	list_क्रम_each_entry_safe(nc_node, nc_node_पंचांगp, list, list) अणु
		/* अगर an helper function has been passed as parameter,
		 * ask it अगर the entry has to be purged or not
		 */
		अगर (to_purge && !to_purge(bat_priv, nc_node))
			जारी;

		batadv_dbg(BATADV_DBG_NC, bat_priv,
			   "Removing nc_node %pM -> %pM\n",
			   nc_node->addr, nc_node->orig_node->orig);
		list_del_rcu(&nc_node->list);
		batadv_nc_node_put(nc_node);
	पूर्ण
	spin_unlock_bh(lock);
पूर्ण

/**
 * batadv_nc_purge_orig() - purges all nc node data attached of the given
 *  originator
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: orig_node with the nc node entries to be purged
 * @to_purge: function in अक्षरge to decide whether an entry has to be purged or
 *	      not. This function takes the nc node as argument and has to वापस
 *	      a boolean value: true is the entry has to be deleted, false
 *	      otherwise
 */
व्योम batadv_nc_purge_orig(काष्ठा batadv_priv *bat_priv,
			  काष्ठा batadv_orig_node *orig_node,
			  bool (*to_purge)(काष्ठा batadv_priv *,
					   काष्ठा batadv_nc_node *))
अणु
	/* Check ingoing nc_node's of this orig_node */
	batadv_nc_purge_orig_nc_nodes(bat_priv, &orig_node->in_coding_list,
				      &orig_node->in_coding_list_lock,
				      to_purge);

	/* Check outgoing nc_node's of this orig_node */
	batadv_nc_purge_orig_nc_nodes(bat_priv, &orig_node->out_coding_list,
				      &orig_node->out_coding_list_lock,
				      to_purge);
पूर्ण

/**
 * batadv_nc_purge_orig_hash() - traverse entire originator hash to check अगर
 *  they have समयd out nc nodes
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_nc_purge_orig_hash(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->orig_hash;
	काष्ठा hlist_head *head;
	काष्ठा batadv_orig_node *orig_node;
	u32 i;

	अगर (!hash)
		वापस;

	/* For each orig_node */
	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(orig_node, head, hash_entry)
			batadv_nc_purge_orig(bat_priv, orig_node,
					     batadv_nc_to_purge_nc_node);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

/**
 * batadv_nc_purge_paths() - traverse all nc paths part of the hash and हटाओ
 *  unused ones
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @hash: hash table containing the nc paths to check
 * @to_purge: function in अक्षरge to decide whether an entry has to be purged or
 *	      not. This function takes the nc node as argument and has to वापस
 *	      a boolean value: true is the entry has to be deleted, false
 *	      otherwise
 */
अटल व्योम batadv_nc_purge_paths(काष्ठा batadv_priv *bat_priv,
				  काष्ठा batadv_hashtable *hash,
				  bool (*to_purge)(काष्ठा batadv_priv *,
						   काष्ठा batadv_nc_path *))
अणु
	काष्ठा hlist_head *head;
	काष्ठा hlist_node *node_पंचांगp;
	काष्ठा batadv_nc_path *nc_path;
	spinlock_t *lock; /* Protects lists in hash */
	u32 i;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];
		lock = &hash->list_locks[i];

		/* For each nc_path in this bin */
		spin_lock_bh(lock);
		hlist_क्रम_each_entry_safe(nc_path, node_पंचांगp, head, hash_entry) अणु
			/* अगर an helper function has been passed as parameter,
			 * ask it अगर the entry has to be purged or not
			 */
			अगर (to_purge && !to_purge(bat_priv, nc_path))
				जारी;

			/* purging an non-empty nc_path should never happen, but
			 * is observed under high CPU load. Delay the purging
			 * until next iteration to allow the packet_list to be
			 * emptied first.
			 */
			अगर (!unlikely(list_empty(&nc_path->packet_list))) अणु
				net_ratelimited_function(prपूर्णांकk,
							 KERN_WARNING
							 "Skipping free of non-empty nc_path (%pM -> %pM)!\n",
							 nc_path->prev_hop,
							 nc_path->next_hop);
				जारी;
			पूर्ण

			/* nc_path is unused, so हटाओ it */
			batadv_dbg(BATADV_DBG_NC, bat_priv,
				   "Remove nc_path %pM -> %pM\n",
				   nc_path->prev_hop, nc_path->next_hop);
			hlist_del_rcu(&nc_path->hash_entry);
			batadv_nc_path_put(nc_path);
		पूर्ण
		spin_unlock_bh(lock);
	पूर्ण
पूर्ण

/**
 * batadv_nc_hash_key_gen() - computes the nc_path hash key
 * @key: buffer to hold the final hash key
 * @src: source ethernet mac address going पूर्णांकo the hash key
 * @dst: destination ethernet mac address going पूर्णांकo the hash key
 */
अटल व्योम batadv_nc_hash_key_gen(काष्ठा batadv_nc_path *key, स्थिर अक्षर *src,
				   स्थिर अक्षर *dst)
अणु
	स_नकल(key->prev_hop, src, माप(key->prev_hop));
	स_नकल(key->next_hop, dst, माप(key->next_hop));
पूर्ण

/**
 * batadv_nc_hash_choose() - compute the hash value क्रम an nc path
 * @data: data to hash
 * @size: size of the hash table
 *
 * Return: the selected index in the hash table क्रम the given data.
 */
अटल u32 batadv_nc_hash_choose(स्थिर व्योम *data, u32 size)
अणु
	स्थिर काष्ठा batadv_nc_path *nc_path = data;
	u32 hash = 0;

	hash = jhash(&nc_path->prev_hop, माप(nc_path->prev_hop), hash);
	hash = jhash(&nc_path->next_hop, माप(nc_path->next_hop), hash);

	वापस hash % size;
पूर्ण

/**
 * batadv_nc_hash_compare() - comparing function used in the network coding hash
 *  tables
 * @node: node in the local table
 * @data2: second object to compare the node to
 *
 * Return: true अगर the two entry are the same, false otherwise
 */
अटल bool batadv_nc_hash_compare(स्थिर काष्ठा hlist_node *node,
				   स्थिर व्योम *data2)
अणु
	स्थिर काष्ठा batadv_nc_path *nc_path1, *nc_path2;

	nc_path1 = container_of(node, काष्ठा batadv_nc_path, hash_entry);
	nc_path2 = data2;

	/* Return 1 अगर the two keys are identical */
	अगर (!batadv_compare_eth(nc_path1->prev_hop, nc_path2->prev_hop))
		वापस false;

	अगर (!batadv_compare_eth(nc_path1->next_hop, nc_path2->next_hop))
		वापस false;

	वापस true;
पूर्ण

/**
 * batadv_nc_hash_find() - search क्रम an existing nc path and वापस it
 * @hash: hash table containing the nc path
 * @data: search key
 *
 * Return: the nc_path अगर found, शून्य otherwise.
 */
अटल काष्ठा batadv_nc_path *
batadv_nc_hash_find(काष्ठा batadv_hashtable *hash,
		    व्योम *data)
अणु
	काष्ठा hlist_head *head;
	काष्ठा batadv_nc_path *nc_path, *nc_path_पंचांगp = शून्य;
	पूर्णांक index;

	अगर (!hash)
		वापस शून्य;

	index = batadv_nc_hash_choose(data, hash->size);
	head = &hash->table[index];

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(nc_path, head, hash_entry) अणु
		अगर (!batadv_nc_hash_compare(&nc_path->hash_entry, data))
			जारी;

		अगर (!kref_get_unless_zero(&nc_path->refcount))
			जारी;

		nc_path_पंचांगp = nc_path;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस nc_path_पंचांगp;
पूर्ण

/**
 * batadv_nc_send_packet() - send non-coded packet and मुक्त nc_packet काष्ठा
 * @nc_packet: the nc packet to send
 */
अटल व्योम batadv_nc_send_packet(काष्ठा batadv_nc_packet *nc_packet)
अणु
	batadv_send_unicast_skb(nc_packet->skb, nc_packet->neigh_node);
	nc_packet->skb = शून्य;
	batadv_nc_packet_मुक्त(nc_packet, false);
पूर्ण

/**
 * batadv_nc_snअगरfed_purge() - Checks बारtamp of given snअगरfed nc_packet.
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @nc_path: the nc path the packet beदीर्घs to
 * @nc_packet: the nc packet to be checked
 *
 * Checks whether the given snअगरfed (overheard) nc_packet has hit its buffering
 * समयout. If so, the packet is no दीर्घer kept and the entry deleted from the
 * queue. Has to be called with the appropriate locks.
 *
 * Return: false as soon as the entry in the fअगरo queue has not been समयd out
 * yet and true otherwise.
 */
अटल bool batadv_nc_snअगरfed_purge(काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_nc_path *nc_path,
				    काष्ठा batadv_nc_packet *nc_packet)
अणु
	अचिन्हित दीर्घ समयout = bat_priv->nc.max_buffer_समय;
	bool res = false;

	lockdep_निश्चित_held(&nc_path->packet_list_lock);

	/* Packets are added to tail, so the reमुख्यing packets did not समय
	 * out and we can stop processing the current queue
	 */
	अगर (atomic_पढ़ो(&bat_priv->mesh_state) == BATADV_MESH_ACTIVE &&
	    !batadv_has_समयd_out(nc_packet->बारtamp, समयout))
		जाओ out;

	/* purge nc packet */
	list_del(&nc_packet->list);
	batadv_nc_packet_मुक्त(nc_packet, true);

	res = true;

out:
	वापस res;
पूर्ण

/**
 * batadv_nc_fwd_flush() - Checks the बारtamp of the given nc packet.
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @nc_path: the nc path the packet beदीर्घs to
 * @nc_packet: the nc packet to be checked
 *
 * Checks whether the given nc packet has hit its क्रमward समयout. If so, the
 * packet is no दीर्घer delayed, immediately sent and the entry deleted from the
 * queue. Has to be called with the appropriate locks.
 *
 * Return: false as soon as the entry in the fअगरo queue has not been समयd out
 * yet and true otherwise.
 */
अटल bool batadv_nc_fwd_flush(काष्ठा batadv_priv *bat_priv,
				काष्ठा batadv_nc_path *nc_path,
				काष्ठा batadv_nc_packet *nc_packet)
अणु
	अचिन्हित दीर्घ समयout = bat_priv->nc.max_fwd_delay;

	lockdep_निश्चित_held(&nc_path->packet_list_lock);

	/* Packets are added to tail, so the reमुख्यing packets did not समय
	 * out and we can stop processing the current queue
	 */
	अगर (atomic_पढ़ो(&bat_priv->mesh_state) == BATADV_MESH_ACTIVE &&
	    !batadv_has_समयd_out(nc_packet->बारtamp, समयout))
		वापस false;

	/* Send packet */
	batadv_inc_counter(bat_priv, BATADV_CNT_FORWARD);
	batadv_add_counter(bat_priv, BATADV_CNT_FORWARD_BYTES,
			   nc_packet->skb->len + ETH_HLEN);
	list_del(&nc_packet->list);
	batadv_nc_send_packet(nc_packet);

	वापस true;
पूर्ण

/**
 * batadv_nc_process_nc_paths() - traverse given nc packet pool and मुक्त समयd
 *  out nc packets
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @hash: to be processed hash table
 * @process_fn: Function called to process given nc packet. Should वापस true
 *	        to encourage this function to proceed with the next packet.
 *	        Otherwise the rest of the current queue is skipped.
 */
अटल व्योम
batadv_nc_process_nc_paths(काष्ठा batadv_priv *bat_priv,
			   काष्ठा batadv_hashtable *hash,
			   bool (*process_fn)(काष्ठा batadv_priv *,
					      काष्ठा batadv_nc_path *,
					      काष्ठा batadv_nc_packet *))
अणु
	काष्ठा hlist_head *head;
	काष्ठा batadv_nc_packet *nc_packet, *nc_packet_पंचांगp;
	काष्ठा batadv_nc_path *nc_path;
	bool ret;
	पूर्णांक i;

	अगर (!hash)
		वापस;

	/* Loop hash table bins */
	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];

		/* Loop coding paths */
		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(nc_path, head, hash_entry) अणु
			/* Loop packets */
			spin_lock_bh(&nc_path->packet_list_lock);
			list_क्रम_each_entry_safe(nc_packet, nc_packet_पंचांगp,
						 &nc_path->packet_list, list) अणु
				ret = process_fn(bat_priv, nc_path, nc_packet);
				अगर (!ret)
					अवरोध;
			पूर्ण
			spin_unlock_bh(&nc_path->packet_list_lock);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

/**
 * batadv_nc_worker() - periodic task क्रम housekeeping related to network
 *  coding
 * @work: kernel work काष्ठा
 */
अटल व्योम batadv_nc_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work;
	काष्ठा batadv_priv_nc *priv_nc;
	काष्ठा batadv_priv *bat_priv;
	अचिन्हित दीर्घ समयout;

	delayed_work = to_delayed_work(work);
	priv_nc = container_of(delayed_work, काष्ठा batadv_priv_nc, work);
	bat_priv = container_of(priv_nc, काष्ठा batadv_priv, nc);

	batadv_nc_purge_orig_hash(bat_priv);
	batadv_nc_purge_paths(bat_priv, bat_priv->nc.coding_hash,
			      batadv_nc_to_purge_nc_path_coding);
	batadv_nc_purge_paths(bat_priv, bat_priv->nc.decoding_hash,
			      batadv_nc_to_purge_nc_path_decoding);

	समयout = bat_priv->nc.max_fwd_delay;

	अगर (batadv_has_समयd_out(bat_priv->nc.बारtamp_fwd_flush, समयout)) अणु
		batadv_nc_process_nc_paths(bat_priv, bat_priv->nc.coding_hash,
					   batadv_nc_fwd_flush);
		bat_priv->nc.बारtamp_fwd_flush = jअगरfies;
	पूर्ण

	अगर (batadv_has_समयd_out(bat_priv->nc.बारtamp_snअगरfed_purge,
				 bat_priv->nc.max_buffer_समय)) अणु
		batadv_nc_process_nc_paths(bat_priv, bat_priv->nc.decoding_hash,
					   batadv_nc_snअगरfed_purge);
		bat_priv->nc.बारtamp_snअगरfed_purge = jअगरfies;
	पूर्ण

	/* Schedule a new check */
	batadv_nc_start_समयr(bat_priv);
पूर्ण

/**
 * batadv_can_nc_with_orig() - checks whether the given orig node is suitable
 *  क्रम coding or not
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: neighboring orig node which may be used as nc candidate
 * @ogm_packet: incoming ogm packet also used क्रम the checks
 *
 * Return: true अगर:
 *  1) The OGM must have the most recent sequence number.
 *  2) The TTL must be decremented by one and only one.
 *  3) The OGM must be received from the first hop from orig_node.
 *  4) The TQ value of the OGM must be above bat_priv->nc.min_tq.
 */
अटल bool batadv_can_nc_with_orig(काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_orig_node *orig_node,
				    काष्ठा batadv_ogm_packet *ogm_packet)
अणु
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo;
	u32 last_real_seqno;
	u8 last_ttl;

	orig_अगरinfo = batadv_orig_अगरinfo_get(orig_node, BATADV_IF_DEFAULT);
	अगर (!orig_अगरinfo)
		वापस false;

	last_ttl = orig_अगरinfo->last_ttl;
	last_real_seqno = orig_अगरinfo->last_real_seqno;
	batadv_orig_अगरinfo_put(orig_अगरinfo);

	अगर (last_real_seqno != ntohl(ogm_packet->seqno))
		वापस false;
	अगर (last_ttl != ogm_packet->ttl + 1)
		वापस false;
	अगर (!batadv_compare_eth(ogm_packet->orig, ogm_packet->prev_sender))
		वापस false;
	अगर (ogm_packet->tq < bat_priv->nc.min_tq)
		वापस false;

	वापस true;
पूर्ण

/**
 * batadv_nc_find_nc_node() - search क्रम an existing nc node and वापस it
 * @orig_node: orig node originating the ogm packet
 * @orig_neigh_node: neighboring orig node from which we received the ogm packet
 *  (can be equal to orig_node)
 * @in_coding: traverse incoming or outgoing network coding list
 *
 * Return: the nc_node अगर found, शून्य otherwise.
 */
अटल काष्ठा batadv_nc_node *
batadv_nc_find_nc_node(काष्ठा batadv_orig_node *orig_node,
		       काष्ठा batadv_orig_node *orig_neigh_node,
		       bool in_coding)
अणु
	काष्ठा batadv_nc_node *nc_node, *nc_node_out = शून्य;
	काष्ठा list_head *list;

	अगर (in_coding)
		list = &orig_neigh_node->in_coding_list;
	अन्यथा
		list = &orig_neigh_node->out_coding_list;

	/* Traverse list of nc_nodes to orig_node */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(nc_node, list, list) अणु
		अगर (!batadv_compare_eth(nc_node->addr, orig_node->orig))
			जारी;

		अगर (!kref_get_unless_zero(&nc_node->refcount))
			जारी;

		/* Found a match */
		nc_node_out = nc_node;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस nc_node_out;
पूर्ण

/**
 * batadv_nc_get_nc_node() - retrieves an nc node or creates the entry अगर it was
 *  not found
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: orig node originating the ogm packet
 * @orig_neigh_node: neighboring orig node from which we received the ogm packet
 *  (can be equal to orig_node)
 * @in_coding: traverse incoming or outgoing network coding list
 *
 * Return: the nc_node अगर found or created, शून्य in हाल of an error.
 */
अटल काष्ठा batadv_nc_node *
batadv_nc_get_nc_node(काष्ठा batadv_priv *bat_priv,
		      काष्ठा batadv_orig_node *orig_node,
		      काष्ठा batadv_orig_node *orig_neigh_node,
		      bool in_coding)
अणु
	काष्ठा batadv_nc_node *nc_node;
	spinlock_t *lock; /* Used to lock list selected by "int in_coding" */
	काष्ठा list_head *list;

	/* Select ingoing or outgoing coding node */
	अगर (in_coding) अणु
		lock = &orig_neigh_node->in_coding_list_lock;
		list = &orig_neigh_node->in_coding_list;
	पूर्ण अन्यथा अणु
		lock = &orig_neigh_node->out_coding_list_lock;
		list = &orig_neigh_node->out_coding_list;
	पूर्ण

	spin_lock_bh(lock);

	/* Check अगर nc_node is alपढ़ोy added */
	nc_node = batadv_nc_find_nc_node(orig_node, orig_neigh_node, in_coding);

	/* Node found */
	अगर (nc_node)
		जाओ unlock;

	nc_node = kzalloc(माप(*nc_node), GFP_ATOMIC);
	अगर (!nc_node)
		जाओ unlock;

	/* Initialize nc_node */
	INIT_LIST_HEAD(&nc_node->list);
	kref_init(&nc_node->refcount);
	ether_addr_copy(nc_node->addr, orig_node->orig);
	kref_get(&orig_neigh_node->refcount);
	nc_node->orig_node = orig_neigh_node;

	batadv_dbg(BATADV_DBG_NC, bat_priv, "Adding nc_node %pM -> %pM\n",
		   nc_node->addr, nc_node->orig_node->orig);

	/* Add nc_node to orig_node */
	kref_get(&nc_node->refcount);
	list_add_tail_rcu(&nc_node->list, list);

unlock:
	spin_unlock_bh(lock);

	वापस nc_node;
पूर्ण

/**
 * batadv_nc_update_nc_node() - updates stored incoming and outgoing nc node
 *  काष्ठाs (best called on incoming OGMs)
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: orig node originating the ogm packet
 * @orig_neigh_node: neighboring orig node from which we received the ogm packet
 *  (can be equal to orig_node)
 * @ogm_packet: incoming ogm packet
 * @is_single_hop_neigh: orig_node is a single hop neighbor
 */
व्योम batadv_nc_update_nc_node(काष्ठा batadv_priv *bat_priv,
			      काष्ठा batadv_orig_node *orig_node,
			      काष्ठा batadv_orig_node *orig_neigh_node,
			      काष्ठा batadv_ogm_packet *ogm_packet,
			      पूर्णांक is_single_hop_neigh)
अणु
	काष्ठा batadv_nc_node *in_nc_node = शून्य;
	काष्ठा batadv_nc_node *out_nc_node = शून्य;

	/* Check अगर network coding is enabled */
	अगर (!atomic_पढ़ो(&bat_priv->network_coding))
		जाओ out;

	/* check अगर orig node is network coding enabled */
	अगर (!test_bit(BATADV_ORIG_CAPA_HAS_NC, &orig_node->capabilities))
		जाओ out;

	/* accept ogms from 'good' neighbors and single hop neighbors */
	अगर (!batadv_can_nc_with_orig(bat_priv, orig_node, ogm_packet) &&
	    !is_single_hop_neigh)
		जाओ out;

	/* Add orig_node as in_nc_node on hop */
	in_nc_node = batadv_nc_get_nc_node(bat_priv, orig_node,
					   orig_neigh_node, true);
	अगर (!in_nc_node)
		जाओ out;

	in_nc_node->last_seen = jअगरfies;

	/* Add hop as out_nc_node on orig_node */
	out_nc_node = batadv_nc_get_nc_node(bat_priv, orig_neigh_node,
					    orig_node, false);
	अगर (!out_nc_node)
		जाओ out;

	out_nc_node->last_seen = jअगरfies;

out:
	अगर (in_nc_node)
		batadv_nc_node_put(in_nc_node);
	अगर (out_nc_node)
		batadv_nc_node_put(out_nc_node);
पूर्ण

/**
 * batadv_nc_get_path() - get existing nc_path or allocate a new one
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @hash: hash table containing the nc path
 * @src: ethernet source address - first half of the nc path search key
 * @dst: ethernet destination address - second half of the nc path search key
 *
 * Return: poपूर्णांकer to nc_path अगर the path was found or created, वापसs शून्य
 * on error.
 */
अटल काष्ठा batadv_nc_path *batadv_nc_get_path(काष्ठा batadv_priv *bat_priv,
						 काष्ठा batadv_hashtable *hash,
						 u8 *src,
						 u8 *dst)
अणु
	पूर्णांक hash_added;
	काष्ठा batadv_nc_path *nc_path, nc_path_key;

	batadv_nc_hash_key_gen(&nc_path_key, src, dst);

	/* Search क्रम existing nc_path */
	nc_path = batadv_nc_hash_find(hash, (व्योम *)&nc_path_key);

	अगर (nc_path) अणु
		/* Set बारtamp to delay removal of nc_path */
		nc_path->last_valid = jअगरfies;
		वापस nc_path;
	पूर्ण

	/* No existing nc_path was found; create a new */
	nc_path = kzalloc(माप(*nc_path), GFP_ATOMIC);

	अगर (!nc_path)
		वापस शून्य;

	/* Initialize nc_path */
	INIT_LIST_HEAD(&nc_path->packet_list);
	spin_lock_init(&nc_path->packet_list_lock);
	kref_init(&nc_path->refcount);
	nc_path->last_valid = jअगरfies;
	ether_addr_copy(nc_path->next_hop, dst);
	ether_addr_copy(nc_path->prev_hop, src);

	batadv_dbg(BATADV_DBG_NC, bat_priv, "Adding nc_path %pM -> %pM\n",
		   nc_path->prev_hop,
		   nc_path->next_hop);

	/* Add nc_path to hash table */
	kref_get(&nc_path->refcount);
	hash_added = batadv_hash_add(hash, batadv_nc_hash_compare,
				     batadv_nc_hash_choose, &nc_path_key,
				     &nc_path->hash_entry);

	अगर (hash_added < 0) अणु
		kमुक्त(nc_path);
		वापस शून्य;
	पूर्ण

	वापस nc_path;
पूर्ण

/**
 * batadv_nc_अक्रमom_weight_tq() - scale the receivers TQ-value to aव्योम unfair
 *  selection of a receiver with slightly lower TQ than the other
 * @tq: to be weighted tq value
 *
 * Return: scaled tq value
 */
अटल u8 batadv_nc_अक्रमom_weight_tq(u8 tq)
अणु
	/* अक्रमomize the estimated packet loss (max TQ - estimated TQ) */
	u8 अक्रम_tq = pअक्रमom_u32_max(BATADV_TQ_MAX_VALUE + 1 - tq);

	/* convert to (अक्रमomized) estimated tq again */
	वापस BATADV_TQ_MAX_VALUE - अक्रम_tq;
पूर्ण

/**
 * batadv_nc_memxor() - XOR destination with source
 * @dst: byte array to XOR पूर्णांकo
 * @src: byte array to XOR from
 * @len: length of destination array
 */
अटल व्योम batadv_nc_memxor(अक्षर *dst, स्थिर अक्षर *src, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < len; ++i)
		dst[i] ^= src[i];
पूर्ण

/**
 * batadv_nc_code_packets() - code a received unicast_packet with an nc packet
 *  पूर्णांकo a coded_packet and send it
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: data skb to क्रमward
 * @ethhdr: poपूर्णांकer to the ethernet header inside the skb
 * @nc_packet: काष्ठाure containing the packet to the skb can be coded with
 * @neigh_node: next hop to क्रमward packet to
 *
 * Return: true अगर both packets are consumed, false otherwise.
 */
अटल bool batadv_nc_code_packets(काष्ठा batadv_priv *bat_priv,
				   काष्ठा sk_buff *skb,
				   काष्ठा ethhdr *ethhdr,
				   काष्ठा batadv_nc_packet *nc_packet,
				   काष्ठा batadv_neigh_node *neigh_node)
अणु
	u8 tq_weighted_neigh, tq_weighted_coding, tq_पंचांगp;
	काष्ठा sk_buff *skb_dest, *skb_src;
	काष्ठा batadv_unicast_packet *packet1;
	काष्ठा batadv_unicast_packet *packet2;
	काष्ठा batadv_coded_packet *coded_packet;
	काष्ठा batadv_neigh_node *neigh_पंचांगp, *router_neigh, *first_dest;
	काष्ठा batadv_neigh_node *router_coding = शून्य, *second_dest;
	काष्ठा batadv_neigh_अगरinfo *router_neigh_अगरinfo = शून्य;
	काष्ठा batadv_neigh_अगरinfo *router_coding_अगरinfo = शून्य;
	u8 *first_source, *second_source;
	__be32 packet_id1, packet_id2;
	माप_प्रकार count;
	bool res = false;
	पूर्णांक coding_len;
	पूर्णांक unicast_size = माप(*packet1);
	पूर्णांक coded_size = माप(*coded_packet);
	पूर्णांक header_add = coded_size - unicast_size;

	/* TODO: करो we need to consider the outgoing पूर्णांकerface क्रम
	 * coded packets?
	 */
	router_neigh = batadv_orig_router_get(neigh_node->orig_node,
					      BATADV_IF_DEFAULT);
	अगर (!router_neigh)
		जाओ out;

	router_neigh_अगरinfo = batadv_neigh_अगरinfo_get(router_neigh,
						      BATADV_IF_DEFAULT);
	अगर (!router_neigh_अगरinfo)
		जाओ out;

	neigh_पंचांगp = nc_packet->neigh_node;
	router_coding = batadv_orig_router_get(neigh_पंचांगp->orig_node,
					       BATADV_IF_DEFAULT);
	अगर (!router_coding)
		जाओ out;

	router_coding_अगरinfo = batadv_neigh_अगरinfo_get(router_coding,
						       BATADV_IF_DEFAULT);
	अगर (!router_coding_अगरinfo)
		जाओ out;

	tq_पंचांगp = router_neigh_अगरinfo->bat_iv.tq_avg;
	tq_weighted_neigh = batadv_nc_अक्रमom_weight_tq(tq_पंचांगp);
	tq_पंचांगp = router_coding_अगरinfo->bat_iv.tq_avg;
	tq_weighted_coding = batadv_nc_अक्रमom_weight_tq(tq_पंचांगp);

	/* Select one destination क्रम the MAC-header dst-field based on
	 * weighted TQ-values.
	 */
	अगर (tq_weighted_neigh >= tq_weighted_coding) अणु
		/* Destination from nc_packet is selected क्रम MAC-header */
		first_dest = nc_packet->neigh_node;
		first_source = nc_packet->nc_path->prev_hop;
		second_dest = neigh_node;
		second_source = ethhdr->h_source;
		packet1 = (काष्ठा batadv_unicast_packet *)nc_packet->skb->data;
		packet2 = (काष्ठा batadv_unicast_packet *)skb->data;
		packet_id1 = nc_packet->packet_id;
		packet_id2 = batadv_skb_crc32(skb,
					      skb->data + माप(*packet2));
	पूर्ण अन्यथा अणु
		/* Destination क्रम skb is selected क्रम MAC-header */
		first_dest = neigh_node;
		first_source = ethhdr->h_source;
		second_dest = nc_packet->neigh_node;
		second_source = nc_packet->nc_path->prev_hop;
		packet1 = (काष्ठा batadv_unicast_packet *)skb->data;
		packet2 = (काष्ठा batadv_unicast_packet *)nc_packet->skb->data;
		packet_id1 = batadv_skb_crc32(skb,
					      skb->data + माप(*packet1));
		packet_id2 = nc_packet->packet_id;
	पूर्ण

	/* Instead of zero padding the smallest data buffer, we
	 * code पूर्णांकo the largest.
	 */
	अगर (skb->len <= nc_packet->skb->len) अणु
		skb_dest = nc_packet->skb;
		skb_src = skb;
	पूर्ण अन्यथा अणु
		skb_dest = skb;
		skb_src = nc_packet->skb;
	पूर्ण

	/* coding_len is used when decoding the packet लघुer packet */
	coding_len = skb_src->len - unicast_size;

	अगर (skb_linearize(skb_dest) < 0 || skb_linearize(skb_src) < 0)
		जाओ out;

	skb_push(skb_dest, header_add);

	coded_packet = (काष्ठा batadv_coded_packet *)skb_dest->data;
	skb_reset_mac_header(skb_dest);

	coded_packet->packet_type = BATADV_CODED;
	coded_packet->version = BATADV_COMPAT_VERSION;
	coded_packet->ttl = packet1->ttl;

	/* Info about first unicast packet */
	ether_addr_copy(coded_packet->first_source, first_source);
	ether_addr_copy(coded_packet->first_orig_dest, packet1->dest);
	coded_packet->first_crc = packet_id1;
	coded_packet->first_ttvn = packet1->ttvn;

	/* Info about second unicast packet */
	ether_addr_copy(coded_packet->second_dest, second_dest->addr);
	ether_addr_copy(coded_packet->second_source, second_source);
	ether_addr_copy(coded_packet->second_orig_dest, packet2->dest);
	coded_packet->second_crc = packet_id2;
	coded_packet->second_ttl = packet2->ttl;
	coded_packet->second_ttvn = packet2->ttvn;
	coded_packet->coded_len = htons(coding_len);

	/* This is where the magic happens: Code skb_src पूर्णांकo skb_dest */
	batadv_nc_memxor(skb_dest->data + coded_size,
			 skb_src->data + unicast_size, coding_len);

	/* Update counters accordingly */
	अगर (BATADV_SKB_CB(skb_src)->decoded &&
	    BATADV_SKB_CB(skb_dest)->decoded) अणु
		/* Both packets are recoded */
		count = skb_src->len + ETH_HLEN;
		count += skb_dest->len + ETH_HLEN;
		batadv_add_counter(bat_priv, BATADV_CNT_NC_RECODE, 2);
		batadv_add_counter(bat_priv, BATADV_CNT_NC_RECODE_BYTES, count);
	पूर्ण अन्यथा अगर (!BATADV_SKB_CB(skb_src)->decoded &&
		   !BATADV_SKB_CB(skb_dest)->decoded) अणु
		/* Both packets are newly coded */
		count = skb_src->len + ETH_HLEN;
		count += skb_dest->len + ETH_HLEN;
		batadv_add_counter(bat_priv, BATADV_CNT_NC_CODE, 2);
		batadv_add_counter(bat_priv, BATADV_CNT_NC_CODE_BYTES, count);
	पूर्ण अन्यथा अगर (BATADV_SKB_CB(skb_src)->decoded &&
		   !BATADV_SKB_CB(skb_dest)->decoded) अणु
		/* skb_src recoded and skb_dest is newly coded */
		batadv_inc_counter(bat_priv, BATADV_CNT_NC_RECODE);
		batadv_add_counter(bat_priv, BATADV_CNT_NC_RECODE_BYTES,
				   skb_src->len + ETH_HLEN);
		batadv_inc_counter(bat_priv, BATADV_CNT_NC_CODE);
		batadv_add_counter(bat_priv, BATADV_CNT_NC_CODE_BYTES,
				   skb_dest->len + ETH_HLEN);
	पूर्ण अन्यथा अगर (!BATADV_SKB_CB(skb_src)->decoded &&
		   BATADV_SKB_CB(skb_dest)->decoded) अणु
		/* skb_src is newly coded and skb_dest is recoded */
		batadv_inc_counter(bat_priv, BATADV_CNT_NC_CODE);
		batadv_add_counter(bat_priv, BATADV_CNT_NC_CODE_BYTES,
				   skb_src->len + ETH_HLEN);
		batadv_inc_counter(bat_priv, BATADV_CNT_NC_RECODE);
		batadv_add_counter(bat_priv, BATADV_CNT_NC_RECODE_BYTES,
				   skb_dest->len + ETH_HLEN);
	पूर्ण

	/* skb_src is now coded पूर्णांकo skb_dest, so मुक्त it */
	consume_skb(skb_src);

	/* aव्योम duplicate मुक्त of skb from nc_packet */
	nc_packet->skb = शून्य;
	batadv_nc_packet_मुक्त(nc_packet, false);

	/* Send the coded packet and वापस true */
	batadv_send_unicast_skb(skb_dest, first_dest);
	res = true;
out:
	अगर (router_neigh)
		batadv_neigh_node_put(router_neigh);
	अगर (router_coding)
		batadv_neigh_node_put(router_coding);
	अगर (router_neigh_अगरinfo)
		batadv_neigh_अगरinfo_put(router_neigh_अगरinfo);
	अगर (router_coding_अगरinfo)
		batadv_neigh_अगरinfo_put(router_coding_अगरinfo);
	वापस res;
पूर्ण

/**
 * batadv_nc_skb_coding_possible() - true अगर a decoded skb is available at dst.
 * @skb: data skb to क्रमward
 * @dst: destination mac address of the other skb to code with
 * @src: source mac address of skb
 *
 * Whenever we network code a packet we have to check whether we received it in
 * a network coded क्रमm. If so, we may not be able to use it क्रम coding because
 * some neighbors may also have received (overheard) the packet in the network
 * coded क्रमm without being able to decode it. It is hard to know which of the
 * neighboring nodes was able to decode the packet, thereक्रमe we can only
 * re-code the packet अगर the source of the previous encoded packet is involved.
 * Since the source encoded the packet we can be certain it has all necessary
 * decode inक्रमmation.
 *
 * Return: true अगर coding of a decoded packet is allowed.
 */
अटल bool batadv_nc_skb_coding_possible(काष्ठा sk_buff *skb, u8 *dst, u8 *src)
अणु
	अगर (BATADV_SKB_CB(skb)->decoded && !batadv_compare_eth(dst, src))
		वापस false;
	वापस true;
पूर्ण

/**
 * batadv_nc_path_search() - Find the coding path matching in_nc_node and
 *  out_nc_node to retrieve a buffered packet that can be used क्रम coding.
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @in_nc_node: poपूर्णांकer to skb next hop's neighbor nc node
 * @out_nc_node: poपूर्णांकer to skb source's neighbor nc node
 * @skb: data skb to क्रमward
 * @eth_dst: next hop mac address of skb
 *
 * Return: true अगर coding of a decoded skb is allowed.
 */
अटल काष्ठा batadv_nc_packet *
batadv_nc_path_search(काष्ठा batadv_priv *bat_priv,
		      काष्ठा batadv_nc_node *in_nc_node,
		      काष्ठा batadv_nc_node *out_nc_node,
		      काष्ठा sk_buff *skb,
		      u8 *eth_dst)
अणु
	काष्ठा batadv_nc_path *nc_path, nc_path_key;
	काष्ठा batadv_nc_packet *nc_packet_out = शून्य;
	काष्ठा batadv_nc_packet *nc_packet, *nc_packet_पंचांगp;
	काष्ठा batadv_hashtable *hash = bat_priv->nc.coding_hash;
	पूर्णांक idx;

	अगर (!hash)
		वापस शून्य;

	/* Create almost path key */
	batadv_nc_hash_key_gen(&nc_path_key, in_nc_node->addr,
			       out_nc_node->addr);
	idx = batadv_nc_hash_choose(&nc_path_key, hash->size);

	/* Check क्रम coding opportunities in this nc_path */
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(nc_path, &hash->table[idx], hash_entry) अणु
		अगर (!batadv_compare_eth(nc_path->prev_hop, in_nc_node->addr))
			जारी;

		अगर (!batadv_compare_eth(nc_path->next_hop, out_nc_node->addr))
			जारी;

		spin_lock_bh(&nc_path->packet_list_lock);
		अगर (list_empty(&nc_path->packet_list)) अणु
			spin_unlock_bh(&nc_path->packet_list_lock);
			जारी;
		पूर्ण

		list_क्रम_each_entry_safe(nc_packet, nc_packet_पंचांगp,
					 &nc_path->packet_list, list) अणु
			अगर (!batadv_nc_skb_coding_possible(nc_packet->skb,
							   eth_dst,
							   in_nc_node->addr))
				जारी;

			/* Coding opportunity is found! */
			list_del(&nc_packet->list);
			nc_packet_out = nc_packet;
			अवरोध;
		पूर्ण

		spin_unlock_bh(&nc_path->packet_list_lock);
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस nc_packet_out;
पूर्ण

/**
 * batadv_nc_skb_src_search() - Loops through the list of neighboring nodes of
 *  the skb's sender (may be equal to the originator).
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: data skb to क्रमward
 * @eth_dst: next hop mac address of skb
 * @eth_src: source mac address of skb
 * @in_nc_node: poपूर्णांकer to skb next hop's neighbor nc node
 *
 * Return: an nc packet अगर a suitable coding packet was found, शून्य otherwise.
 */
अटल काष्ठा batadv_nc_packet *
batadv_nc_skb_src_search(काष्ठा batadv_priv *bat_priv,
			 काष्ठा sk_buff *skb,
			 u8 *eth_dst,
			 u8 *eth_src,
			 काष्ठा batadv_nc_node *in_nc_node)
अणु
	काष्ठा batadv_orig_node *orig_node;
	काष्ठा batadv_nc_node *out_nc_node;
	काष्ठा batadv_nc_packet *nc_packet = शून्य;

	orig_node = batadv_orig_hash_find(bat_priv, eth_src);
	अगर (!orig_node)
		वापस शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(out_nc_node,
				&orig_node->out_coding_list, list) अणु
		/* Check अगर the skb is decoded and अगर recoding is possible */
		अगर (!batadv_nc_skb_coding_possible(skb,
						   out_nc_node->addr, eth_src))
			जारी;

		/* Search क्रम an opportunity in this nc_path */
		nc_packet = batadv_nc_path_search(bat_priv, in_nc_node,
						  out_nc_node, skb, eth_dst);
		अगर (nc_packet)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	batadv_orig_node_put(orig_node);
	वापस nc_packet;
पूर्ण

/**
 * batadv_nc_skb_store_beक्रमe_coding() - set the ethernet src and dst of the
 *  unicast skb beक्रमe it is stored क्रम use in later decoding
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: data skb to store
 * @eth_dst_new: new destination mac address of skb
 */
अटल व्योम batadv_nc_skb_store_beक्रमe_coding(काष्ठा batadv_priv *bat_priv,
					      काष्ठा sk_buff *skb,
					      u8 *eth_dst_new)
अणु
	काष्ठा ethhdr *ethhdr;

	/* Copy skb header to change the mac header */
	skb = pskb_copy_क्रम_clone(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस;

	/* Set the mac header as अगर we actually sent the packet uncoded */
	ethhdr = eth_hdr(skb);
	ether_addr_copy(ethhdr->h_source, ethhdr->h_dest);
	ether_addr_copy(ethhdr->h_dest, eth_dst_new);

	/* Set data poपूर्णांकer to MAC header to mimic packets from our tx path */
	skb_push(skb, ETH_HLEN);

	/* Add the packet to the decoding packet pool */
	batadv_nc_skb_store_क्रम_decoding(bat_priv, skb);

	/* batadv_nc_skb_store_क्रम_decoding() clones the skb, so we must मुक्त
	 * our ref
	 */
	consume_skb(skb);
पूर्ण

/**
 * batadv_nc_skb_dst_search() - Loops through list of neighboring nodes to dst.
 * @skb: data skb to क्रमward
 * @neigh_node: next hop to क्रमward packet to
 * @ethhdr: poपूर्णांकer to the ethernet header inside the skb
 *
 * Loops through the list of neighboring nodes the next hop has a good
 * connection to (receives OGMs with a sufficient quality). We need to find a
 * neighbor of our next hop that potentially sent a packet which our next hop
 * also received (overheard) and has stored क्रम later decoding.
 *
 * Return: true अगर the skb was consumed (encoded packet sent) or false otherwise
 */
अटल bool batadv_nc_skb_dst_search(काष्ठा sk_buff *skb,
				     काष्ठा batadv_neigh_node *neigh_node,
				     काष्ठा ethhdr *ethhdr)
अणु
	काष्ठा net_device *netdev = neigh_node->अगर_incoming->soft_अगरace;
	काष्ठा batadv_priv *bat_priv = netdev_priv(netdev);
	काष्ठा batadv_orig_node *orig_node = neigh_node->orig_node;
	काष्ठा batadv_nc_node *nc_node;
	काष्ठा batadv_nc_packet *nc_packet = शून्य;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(nc_node, &orig_node->in_coding_list, list) अणु
		/* Search क्रम coding opportunity with this in_nc_node */
		nc_packet = batadv_nc_skb_src_search(bat_priv, skb,
						     neigh_node->addr,
						     ethhdr->h_source, nc_node);

		/* Opportunity was found, so stop searching */
		अगर (nc_packet)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!nc_packet)
		वापस false;

	/* Save packets क्रम later decoding */
	batadv_nc_skb_store_beक्रमe_coding(bat_priv, skb,
					  neigh_node->addr);
	batadv_nc_skb_store_beक्रमe_coding(bat_priv, nc_packet->skb,
					  nc_packet->neigh_node->addr);

	/* Code and send packets */
	अगर (batadv_nc_code_packets(bat_priv, skb, ethhdr, nc_packet,
				   neigh_node))
		वापस true;

	/* out of mem ? Coding failed - we have to मुक्त the buffered packet
	 * to aव्योम memleaks. The skb passed as argument will be dealt with
	 * by the calling function.
	 */
	batadv_nc_send_packet(nc_packet);
	वापस false;
पूर्ण

/**
 * batadv_nc_skb_add_to_path() - buffer skb क्रम later encoding / decoding
 * @skb: skb to add to path
 * @nc_path: path to add skb to
 * @neigh_node: next hop to क्रमward packet to
 * @packet_id: checksum to identअगरy packet
 *
 * Return: true अगर the packet was buffered or false in हाल of an error.
 */
अटल bool batadv_nc_skb_add_to_path(काष्ठा sk_buff *skb,
				      काष्ठा batadv_nc_path *nc_path,
				      काष्ठा batadv_neigh_node *neigh_node,
				      __be32 packet_id)
अणु
	काष्ठा batadv_nc_packet *nc_packet;

	nc_packet = kzalloc(माप(*nc_packet), GFP_ATOMIC);
	अगर (!nc_packet)
		वापस false;

	/* Initialize nc_packet */
	nc_packet->बारtamp = jअगरfies;
	nc_packet->packet_id = packet_id;
	nc_packet->skb = skb;
	nc_packet->neigh_node = neigh_node;
	nc_packet->nc_path = nc_path;

	/* Add coding packet to list */
	spin_lock_bh(&nc_path->packet_list_lock);
	list_add_tail(&nc_packet->list, &nc_path->packet_list);
	spin_unlock_bh(&nc_path->packet_list_lock);

	वापस true;
पूर्ण

/**
 * batadv_nc_skb_क्रमward() - try to code a packet or add it to the coding packet
 *  buffer
 * @skb: data skb to क्रमward
 * @neigh_node: next hop to क्रमward packet to
 *
 * Return: true अगर the skb was consumed (encoded packet sent) or false otherwise
 */
bool batadv_nc_skb_क्रमward(काष्ठा sk_buff *skb,
			   काष्ठा batadv_neigh_node *neigh_node)
अणु
	स्थिर काष्ठा net_device *netdev = neigh_node->अगर_incoming->soft_अगरace;
	काष्ठा batadv_priv *bat_priv = netdev_priv(netdev);
	काष्ठा batadv_unicast_packet *packet;
	काष्ठा batadv_nc_path *nc_path;
	काष्ठा ethhdr *ethhdr = eth_hdr(skb);
	__be32 packet_id;
	u8 *payload;

	/* Check अगर network coding is enabled */
	अगर (!atomic_पढ़ो(&bat_priv->network_coding))
		जाओ out;

	/* We only handle unicast packets */
	payload = skb_network_header(skb);
	packet = (काष्ठा batadv_unicast_packet *)payload;
	अगर (packet->packet_type != BATADV_UNICAST)
		जाओ out;

	/* Try to find a coding opportunity and send the skb अगर one is found */
	अगर (batadv_nc_skb_dst_search(skb, neigh_node, ethhdr))
		वापस true;

	/* Find or create a nc_path क्रम this src-dst pair */
	nc_path = batadv_nc_get_path(bat_priv,
				     bat_priv->nc.coding_hash,
				     ethhdr->h_source,
				     neigh_node->addr);

	अगर (!nc_path)
		जाओ out;

	/* Add skb to nc_path */
	packet_id = batadv_skb_crc32(skb, payload + माप(*packet));
	अगर (!batadv_nc_skb_add_to_path(skb, nc_path, neigh_node, packet_id))
		जाओ मुक्त_nc_path;

	/* Packet is consumed */
	वापस true;

मुक्त_nc_path:
	batadv_nc_path_put(nc_path);
out:
	/* Packet is not consumed */
	वापस false;
पूर्ण

/**
 * batadv_nc_skb_store_क्रम_decoding() - save a clone of the skb which can be
 *  used when decoding coded packets
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: data skb to store
 */
व्योम batadv_nc_skb_store_क्रम_decoding(काष्ठा batadv_priv *bat_priv,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा batadv_unicast_packet *packet;
	काष्ठा batadv_nc_path *nc_path;
	काष्ठा ethhdr *ethhdr = eth_hdr(skb);
	__be32 packet_id;
	u8 *payload;

	/* Check अगर network coding is enabled */
	अगर (!atomic_पढ़ो(&bat_priv->network_coding))
		जाओ out;

	/* Check क्रम supported packet type */
	payload = skb_network_header(skb);
	packet = (काष्ठा batadv_unicast_packet *)payload;
	अगर (packet->packet_type != BATADV_UNICAST)
		जाओ out;

	/* Find existing nc_path or create a new */
	nc_path = batadv_nc_get_path(bat_priv,
				     bat_priv->nc.decoding_hash,
				     ethhdr->h_source,
				     ethhdr->h_dest);

	अगर (!nc_path)
		जाओ out;

	/* Clone skb and adjust skb->data to poपूर्णांक at baपंचांगan header */
	skb = skb_clone(skb, GFP_ATOMIC);
	अगर (unlikely(!skb))
		जाओ मुक्त_nc_path;

	अगर (unlikely(!pskb_may_pull(skb, ETH_HLEN)))
		जाओ मुक्त_skb;

	अगर (unlikely(!skb_pull_rcsum(skb, ETH_HLEN)))
		जाओ मुक्त_skb;

	/* Add skb to nc_path */
	packet_id = batadv_skb_crc32(skb, payload + माप(*packet));
	अगर (!batadv_nc_skb_add_to_path(skb, nc_path, शून्य, packet_id))
		जाओ मुक्त_skb;

	batadv_inc_counter(bat_priv, BATADV_CNT_NC_BUFFER);
	वापस;

मुक्त_skb:
	kमुक्त_skb(skb);
मुक्त_nc_path:
	batadv_nc_path_put(nc_path);
out:
	वापस;
पूर्ण

/**
 * batadv_nc_skb_store_snअगरfed_unicast() - check अगर a received unicast packet
 *  should be saved in the decoding buffer and, अगर so, store it there
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: unicast skb to store
 */
व्योम batadv_nc_skb_store_snअगरfed_unicast(काष्ठा batadv_priv *bat_priv,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *ethhdr = eth_hdr(skb);

	अगर (batadv_is_my_mac(bat_priv, ethhdr->h_dest))
		वापस;

	/* Set data poपूर्णांकer to MAC header to mimic packets from our tx path */
	skb_push(skb, ETH_HLEN);

	batadv_nc_skb_store_क्रम_decoding(bat_priv, skb);
पूर्ण

/**
 * batadv_nc_skb_decode_packet() - decode given skb using the decode data stored
 *  in nc_packet
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @skb: unicast skb to decode
 * @nc_packet: decode data needed to decode the skb
 *
 * Return: poपूर्णांकer to decoded unicast packet अगर the packet was decoded or शून्य
 * in हाल of an error.
 */
अटल काष्ठा batadv_unicast_packet *
batadv_nc_skb_decode_packet(काष्ठा batadv_priv *bat_priv, काष्ठा sk_buff *skb,
			    काष्ठा batadv_nc_packet *nc_packet)
अणु
	स्थिर पूर्णांक h_size = माप(काष्ठा batadv_unicast_packet);
	स्थिर पूर्णांक h_dअगरf = माप(काष्ठा batadv_coded_packet) - h_size;
	काष्ठा batadv_unicast_packet *unicast_packet;
	काष्ठा batadv_coded_packet coded_packet_पंचांगp;
	काष्ठा ethhdr *ethhdr, ethhdr_पंचांगp;
	u8 *orig_dest, ttl, ttvn;
	अचिन्हित पूर्णांक coding_len;
	पूर्णांक err;

	/* Save headers temporarily */
	स_नकल(&coded_packet_पंचांगp, skb->data, माप(coded_packet_पंचांगp));
	स_नकल(&ethhdr_पंचांगp, skb_mac_header(skb), माप(ethhdr_पंचांगp));

	अगर (skb_cow(skb, 0) < 0)
		वापस शून्य;

	अगर (unlikely(!skb_pull_rcsum(skb, h_dअगरf)))
		वापस शून्य;

	/* Data poपूर्णांकs to baपंचांगan header, so set mac header 14 bytes beक्रमe
	 * and network to data
	 */
	skb_set_mac_header(skb, -ETH_HLEN);
	skb_reset_network_header(skb);

	/* Reस्थिरruct original mac header */
	ethhdr = eth_hdr(skb);
	*ethhdr = ethhdr_पंचांगp;

	/* Select the correct unicast header inक्रमmation based on the location
	 * of our mac address in the coded_packet header
	 */
	अगर (batadv_is_my_mac(bat_priv, coded_packet_पंचांगp.second_dest)) अणु
		/* If we are the second destination the packet was overheard,
		 * so the Ethernet address must be copied to h_dest and
		 * pkt_type changed from PACKET_OTHERHOST to PACKET_HOST
		 */
		ether_addr_copy(ethhdr->h_dest, coded_packet_पंचांगp.second_dest);
		skb->pkt_type = PACKET_HOST;

		orig_dest = coded_packet_पंचांगp.second_orig_dest;
		ttl = coded_packet_पंचांगp.second_ttl;
		ttvn = coded_packet_पंचांगp.second_ttvn;
	पूर्ण अन्यथा अणु
		orig_dest = coded_packet_पंचांगp.first_orig_dest;
		ttl = coded_packet_पंचांगp.ttl;
		ttvn = coded_packet_पंचांगp.first_ttvn;
	पूर्ण

	coding_len = ntohs(coded_packet_पंचांगp.coded_len);

	अगर (coding_len > skb->len)
		वापस शून्य;

	/* Here the magic is reversed:
	 *   extract the missing packet from the received coded packet
	 */
	batadv_nc_memxor(skb->data + h_size,
			 nc_packet->skb->data + h_size,
			 coding_len);

	/* Resize decoded skb अगर decoded with larger packet */
	अगर (nc_packet->skb->len > coding_len + h_size) अणु
		err = pskb_trim_rcsum(skb, coding_len + h_size);
		अगर (err)
			वापस शून्य;
	पूर्ण

	/* Create decoded unicast packet */
	unicast_packet = (काष्ठा batadv_unicast_packet *)skb->data;
	unicast_packet->packet_type = BATADV_UNICAST;
	unicast_packet->version = BATADV_COMPAT_VERSION;
	unicast_packet->ttl = ttl;
	ether_addr_copy(unicast_packet->dest, orig_dest);
	unicast_packet->ttvn = ttvn;

	batadv_nc_packet_मुक्त(nc_packet, false);
	वापस unicast_packet;
पूर्ण

/**
 * batadv_nc_find_decoding_packet() - search through buffered decoding data to
 *  find the data needed to decode the coded packet
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @ethhdr: poपूर्णांकer to the ethernet header inside the coded packet
 * @coded: coded packet we try to find decode data क्रम
 *
 * Return: poपूर्णांकer to nc packet अगर the needed data was found or शून्य otherwise.
 */
अटल काष्ठा batadv_nc_packet *
batadv_nc_find_decoding_packet(काष्ठा batadv_priv *bat_priv,
			       काष्ठा ethhdr *ethhdr,
			       काष्ठा batadv_coded_packet *coded)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->nc.decoding_hash;
	काष्ठा batadv_nc_packet *पंचांगp_nc_packet, *nc_packet = शून्य;
	काष्ठा batadv_nc_path *nc_path, nc_path_key;
	u8 *dest, *source;
	__be32 packet_id;
	पूर्णांक index;

	अगर (!hash)
		वापस शून्य;

	/* Select the correct packet id based on the location of our mac-addr */
	dest = ethhdr->h_source;
	अगर (!batadv_is_my_mac(bat_priv, coded->second_dest)) अणु
		source = coded->second_source;
		packet_id = coded->second_crc;
	पूर्ण अन्यथा अणु
		source = coded->first_source;
		packet_id = coded->first_crc;
	पूर्ण

	batadv_nc_hash_key_gen(&nc_path_key, source, dest);
	index = batadv_nc_hash_choose(&nc_path_key, hash->size);

	/* Search क्रम matching coding path */
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(nc_path, &hash->table[index], hash_entry) अणु
		/* Find matching nc_packet */
		spin_lock_bh(&nc_path->packet_list_lock);
		list_क्रम_each_entry(पंचांगp_nc_packet,
				    &nc_path->packet_list, list) अणु
			अगर (packet_id == पंचांगp_nc_packet->packet_id) अणु
				list_del(&पंचांगp_nc_packet->list);

				nc_packet = पंचांगp_nc_packet;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&nc_path->packet_list_lock);

		अगर (nc_packet)
			अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!nc_packet)
		batadv_dbg(BATADV_DBG_NC, bat_priv,
			   "No decoding packet found for %u\n", packet_id);

	वापस nc_packet;
पूर्ण

/**
 * batadv_nc_recv_coded_packet() - try to decode coded packet and enqueue the
 *  resulting unicast packet
 * @skb: incoming coded packet
 * @recv_अगर: poपूर्णांकer to पूर्णांकerface this packet was received on
 *
 * Return: NET_RX_SUCCESS अगर the packet has been consumed or NET_RX_DROP
 * otherwise.
 */
अटल पूर्णांक batadv_nc_recv_coded_packet(काष्ठा sk_buff *skb,
				       काष्ठा batadv_hard_अगरace *recv_अगर)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(recv_अगर->soft_अगरace);
	काष्ठा batadv_unicast_packet *unicast_packet;
	काष्ठा batadv_coded_packet *coded_packet;
	काष्ठा batadv_nc_packet *nc_packet;
	काष्ठा ethhdr *ethhdr;
	पूर्णांक hdr_size = माप(*coded_packet);

	/* Check अगर network coding is enabled */
	अगर (!atomic_पढ़ो(&bat_priv->network_coding))
		जाओ मुक्त_skb;

	/* Make sure we can access (and हटाओ) header */
	अगर (unlikely(!pskb_may_pull(skb, hdr_size)))
		जाओ मुक्त_skb;

	coded_packet = (काष्ठा batadv_coded_packet *)skb->data;
	ethhdr = eth_hdr(skb);

	/* Verअगरy frame is destined क्रम us */
	अगर (!batadv_is_my_mac(bat_priv, ethhdr->h_dest) &&
	    !batadv_is_my_mac(bat_priv, coded_packet->second_dest))
		जाओ मुक्त_skb;

	/* Update stat counter */
	अगर (batadv_is_my_mac(bat_priv, coded_packet->second_dest))
		batadv_inc_counter(bat_priv, BATADV_CNT_NC_SNIFFED);

	nc_packet = batadv_nc_find_decoding_packet(bat_priv, ethhdr,
						   coded_packet);
	अगर (!nc_packet) अणु
		batadv_inc_counter(bat_priv, BATADV_CNT_NC_DECODE_FAILED);
		जाओ मुक्त_skb;
	पूर्ण

	/* Make skb's linear, because decoding accesses the entire buffer */
	अगर (skb_linearize(skb) < 0)
		जाओ मुक्त_nc_packet;

	अगर (skb_linearize(nc_packet->skb) < 0)
		जाओ मुक्त_nc_packet;

	/* Decode the packet */
	unicast_packet = batadv_nc_skb_decode_packet(bat_priv, skb, nc_packet);
	अगर (!unicast_packet) अणु
		batadv_inc_counter(bat_priv, BATADV_CNT_NC_DECODE_FAILED);
		जाओ मुक्त_nc_packet;
	पूर्ण

	/* Mark packet as decoded to करो correct recoding when क्रमwarding */
	BATADV_SKB_CB(skb)->decoded = true;
	batadv_inc_counter(bat_priv, BATADV_CNT_NC_DECODE);
	batadv_add_counter(bat_priv, BATADV_CNT_NC_DECODE_BYTES,
			   skb->len + ETH_HLEN);
	वापस batadv_recv_unicast_packet(skb, recv_अगर);

मुक्त_nc_packet:
	batadv_nc_packet_मुक्त(nc_packet, true);
मुक्त_skb:
	kमुक्त_skb(skb);

	वापस NET_RX_DROP;
पूर्ण

/**
 * batadv_nc_mesh_मुक्त() - clean up network coding memory
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_nc_mesh_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	batadv_tvlv_container_unरेजिस्टर(bat_priv, BATADV_TVLV_NC, 1);
	batadv_tvlv_handler_unरेजिस्टर(bat_priv, BATADV_TVLV_NC, 1);
	cancel_delayed_work_sync(&bat_priv->nc.work);

	batadv_nc_purge_paths(bat_priv, bat_priv->nc.coding_hash, शून्य);
	batadv_hash_destroy(bat_priv->nc.coding_hash);
	batadv_nc_purge_paths(bat_priv, bat_priv->nc.decoding_hash, शून्य);
	batadv_hash_destroy(bat_priv->nc.decoding_hash);
पूर्ण
