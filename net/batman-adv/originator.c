<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#समावेश "originator.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/workqueue.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "bat_algo.h"
#समावेश "distributed-arp-table.h"
#समावेश "fragmentation.h"
#समावेश "gateway_client.h"
#समावेश "hard-interface.h"
#समावेश "hash.h"
#समावेश "log.h"
#समावेश "multicast.h"
#समावेश "netlink.h"
#समावेश "network-coding.h"
#समावेश "routing.h"
#समावेश "soft-interface.h"
#समावेश "translation-table.h"

/* hash class keys */
अटल काष्ठा lock_class_key batadv_orig_hash_lock_class_key;

/**
 * batadv_orig_hash_find() - Find and वापस originator from orig_hash
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @data: mac address of the originator
 *
 * Return: orig_node (with increased refcnt), शून्य on errors
 */
काष्ठा batadv_orig_node *
batadv_orig_hash_find(काष्ठा batadv_priv *bat_priv, स्थिर व्योम *data)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->orig_hash;
	काष्ठा hlist_head *head;
	काष्ठा batadv_orig_node *orig_node, *orig_node_पंचांगp = शून्य;
	पूर्णांक index;

	अगर (!hash)
		वापस शून्य;

	index = batadv_choose_orig(data, hash->size);
	head = &hash->table[index];

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(orig_node, head, hash_entry) अणु
		अगर (!batadv_compare_eth(orig_node, data))
			जारी;

		अगर (!kref_get_unless_zero(&orig_node->refcount))
			जारी;

		orig_node_पंचांगp = orig_node;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस orig_node_पंचांगp;
पूर्ण

अटल व्योम batadv_purge_orig(काष्ठा work_काष्ठा *work);

/**
 * batadv_compare_orig() - comparing function used in the originator hash table
 * @node: node in the local table
 * @data2: second object to compare the node to
 *
 * Return: true अगर they are the same originator
 */
bool batadv_compare_orig(स्थिर काष्ठा hlist_node *node, स्थिर व्योम *data2)
अणु
	स्थिर व्योम *data1 = container_of(node, काष्ठा batadv_orig_node,
					 hash_entry);

	वापस batadv_compare_eth(data1, data2);
पूर्ण

/**
 * batadv_orig_node_vlan_get() - get an orig_node_vlan object
 * @orig_node: the originator serving the VLAN
 * @vid: the VLAN identअगरier
 *
 * Return: the vlan object identअगरied by vid and beदीर्घing to orig_node or शून्य
 * अगर it करोes not exist.
 */
काष्ठा batadv_orig_node_vlan *
batadv_orig_node_vlan_get(काष्ठा batadv_orig_node *orig_node,
			  अचिन्हित लघु vid)
अणु
	काष्ठा batadv_orig_node_vlan *vlan = शून्य, *पंचांगp;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp, &orig_node->vlan_list, list) अणु
		अगर (पंचांगp->vid != vid)
			जारी;

		अगर (!kref_get_unless_zero(&पंचांगp->refcount))
			जारी;

		vlan = पंचांगp;

		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस vlan;
पूर्ण

/**
 * batadv_orig_node_vlan_new() - search and possibly create an orig_node_vlan
 *  object
 * @orig_node: the originator serving the VLAN
 * @vid: the VLAN identअगरier
 *
 * Return: शून्य in हाल of failure or the vlan object identअगरied by vid and
 * beदीर्घing to orig_node otherwise. The object is created and added to the list
 * अगर it करोes not exist.
 *
 * The object is वापसed with refcounter increased by 1.
 */
काष्ठा batadv_orig_node_vlan *
batadv_orig_node_vlan_new(काष्ठा batadv_orig_node *orig_node,
			  अचिन्हित लघु vid)
अणु
	काष्ठा batadv_orig_node_vlan *vlan;

	spin_lock_bh(&orig_node->vlan_list_lock);

	/* first look अगर an object क्रम this vid alपढ़ोy exists */
	vlan = batadv_orig_node_vlan_get(orig_node, vid);
	अगर (vlan)
		जाओ out;

	vlan = kzalloc(माप(*vlan), GFP_ATOMIC);
	अगर (!vlan)
		जाओ out;

	kref_init(&vlan->refcount);
	vlan->vid = vid;

	kref_get(&vlan->refcount);
	hlist_add_head_rcu(&vlan->list, &orig_node->vlan_list);

out:
	spin_unlock_bh(&orig_node->vlan_list_lock);

	वापस vlan;
पूर्ण

/**
 * batadv_orig_node_vlan_release() - release originator-vlan object from lists
 *  and queue क्रम मुक्त after rcu grace period
 * @ref: kref poपूर्णांकer of the originator-vlan object
 */
अटल व्योम batadv_orig_node_vlan_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_orig_node_vlan *orig_vlan;

	orig_vlan = container_of(ref, काष्ठा batadv_orig_node_vlan, refcount);

	kमुक्त_rcu(orig_vlan, rcu);
पूर्ण

/**
 * batadv_orig_node_vlan_put() - decrement the refcounter and possibly release
 *  the originator-vlan object
 * @orig_vlan: the originator-vlan object to release
 */
व्योम batadv_orig_node_vlan_put(काष्ठा batadv_orig_node_vlan *orig_vlan)
अणु
	kref_put(&orig_vlan->refcount, batadv_orig_node_vlan_release);
पूर्ण

/**
 * batadv_originator_init() - Initialize all originator काष्ठाures
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
पूर्णांक batadv_originator_init(काष्ठा batadv_priv *bat_priv)
अणु
	अगर (bat_priv->orig_hash)
		वापस 0;

	bat_priv->orig_hash = batadv_hash_new(1024);

	अगर (!bat_priv->orig_hash)
		जाओ err;

	batadv_hash_set_lock_class(bat_priv->orig_hash,
				   &batadv_orig_hash_lock_class_key);

	INIT_DELAYED_WORK(&bat_priv->orig_work, batadv_purge_orig);
	queue_delayed_work(batadv_event_workqueue,
			   &bat_priv->orig_work,
			   msecs_to_jअगरfies(BATADV_ORIG_WORK_PERIOD));

	वापस 0;

err:
	वापस -ENOMEM;
पूर्ण

/**
 * batadv_neigh_अगरinfo_release() - release neigh_अगरinfo from lists and queue क्रम
 *  मुक्त after rcu grace period
 * @ref: kref poपूर्णांकer of the neigh_अगरinfo
 */
अटल व्योम batadv_neigh_अगरinfo_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_neigh_अगरinfo *neigh_अगरinfo;

	neigh_अगरinfo = container_of(ref, काष्ठा batadv_neigh_अगरinfo, refcount);

	अगर (neigh_अगरinfo->अगर_outgoing != BATADV_IF_DEFAULT)
		batadv_hardअगर_put(neigh_अगरinfo->अगर_outgoing);

	kमुक्त_rcu(neigh_अगरinfo, rcu);
पूर्ण

/**
 * batadv_neigh_अगरinfo_put() - decrement the refcounter and possibly release
 *  the neigh_अगरinfo
 * @neigh_अगरinfo: the neigh_अगरinfo object to release
 */
व्योम batadv_neigh_अगरinfo_put(काष्ठा batadv_neigh_अगरinfo *neigh_अगरinfo)
अणु
	kref_put(&neigh_अगरinfo->refcount, batadv_neigh_अगरinfo_release);
पूर्ण

/**
 * batadv_hardअगर_neigh_release() - release hardअगर neigh node from lists and
 *  queue क्रम मुक्त after rcu grace period
 * @ref: kref poपूर्णांकer of the neigh_node
 */
अटल व्योम batadv_hardअगर_neigh_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh;

	hardअगर_neigh = container_of(ref, काष्ठा batadv_hardअगर_neigh_node,
				    refcount);

	spin_lock_bh(&hardअगर_neigh->अगर_incoming->neigh_list_lock);
	hlist_del_init_rcu(&hardअगर_neigh->list);
	spin_unlock_bh(&hardअगर_neigh->अगर_incoming->neigh_list_lock);

	batadv_hardअगर_put(hardअगर_neigh->अगर_incoming);
	kमुक्त_rcu(hardअगर_neigh, rcu);
पूर्ण

/**
 * batadv_hardअगर_neigh_put() - decrement the hardअगर neighbors refcounter
 *  and possibly release it
 * @hardअगर_neigh: hardअगर neigh neighbor to मुक्त
 */
व्योम batadv_hardअगर_neigh_put(काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh)
अणु
	kref_put(&hardअगर_neigh->refcount, batadv_hardअगर_neigh_release);
पूर्ण

/**
 * batadv_neigh_node_release() - release neigh_node from lists and queue क्रम
 *  मुक्त after rcu grace period
 * @ref: kref poपूर्णांकer of the neigh_node
 */
अटल व्योम batadv_neigh_node_release(काष्ठा kref *ref)
अणु
	काष्ठा hlist_node *node_पंचांगp;
	काष्ठा batadv_neigh_node *neigh_node;
	काष्ठा batadv_neigh_अगरinfo *neigh_अगरinfo;

	neigh_node = container_of(ref, काष्ठा batadv_neigh_node, refcount);

	hlist_क्रम_each_entry_safe(neigh_अगरinfo, node_पंचांगp,
				  &neigh_node->अगरinfo_list, list) अणु
		batadv_neigh_अगरinfo_put(neigh_अगरinfo);
	पूर्ण

	batadv_hardअगर_neigh_put(neigh_node->hardअगर_neigh);

	batadv_hardअगर_put(neigh_node->अगर_incoming);

	kमुक्त_rcu(neigh_node, rcu);
पूर्ण

/**
 * batadv_neigh_node_put() - decrement the neighbors refcounter and possibly
 *  release it
 * @neigh_node: neigh neighbor to मुक्त
 */
व्योम batadv_neigh_node_put(काष्ठा batadv_neigh_node *neigh_node)
अणु
	kref_put(&neigh_node->refcount, batadv_neigh_node_release);
पूर्ण

/**
 * batadv_orig_router_get() - router to the originator depending on अगरace
 * @orig_node: the orig node क्रम the router
 * @अगर_outgoing: the पूर्णांकerface where the payload packet has been received or
 *  the OGM should be sent to
 *
 * Return: the neighbor which should be the router क्रम this orig_node/अगरace.
 *
 * The object is वापसed with refcounter increased by 1.
 */
काष्ठा batadv_neigh_node *
batadv_orig_router_get(काष्ठा batadv_orig_node *orig_node,
		       स्थिर काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo;
	काष्ठा batadv_neigh_node *router = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(orig_अगरinfo, &orig_node->अगरinfo_list, list) अणु
		अगर (orig_अगरinfo->अगर_outgoing != अगर_outgoing)
			जारी;

		router = rcu_dereference(orig_अगरinfo->router);
		अवरोध;
	पूर्ण

	अगर (router && !kref_get_unless_zero(&router->refcount))
		router = शून्य;

	rcu_पढ़ो_unlock();
	वापस router;
पूर्ण

/**
 * batadv_orig_अगरinfo_get() - find the अगरinfo from an orig_node
 * @orig_node: the orig node to be queried
 * @अगर_outgoing: the पूर्णांकerface क्रम which the अगरinfo should be acquired
 *
 * Return: the requested orig_अगरinfo or शून्य अगर not found.
 *
 * The object is वापसed with refcounter increased by 1.
 */
काष्ठा batadv_orig_अगरinfo *
batadv_orig_अगरinfo_get(काष्ठा batadv_orig_node *orig_node,
		       काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_orig_अगरinfo *पंचांगp, *orig_अगरinfo = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp, &orig_node->अगरinfo_list,
				 list) अणु
		अगर (पंचांगp->अगर_outgoing != अगर_outgoing)
			जारी;

		अगर (!kref_get_unless_zero(&पंचांगp->refcount))
			जारी;

		orig_अगरinfo = पंचांगp;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस orig_अगरinfo;
पूर्ण

/**
 * batadv_orig_अगरinfo_new() - search and possibly create an orig_अगरinfo object
 * @orig_node: the orig node to be queried
 * @अगर_outgoing: the पूर्णांकerface क्रम which the अगरinfo should be acquired
 *
 * Return: शून्य in हाल of failure or the orig_अगरinfo object क्रम the अगर_outgoing
 * पूर्णांकerface otherwise. The object is created and added to the list
 * अगर it करोes not exist.
 *
 * The object is वापसed with refcounter increased by 1.
 */
काष्ठा batadv_orig_अगरinfo *
batadv_orig_अगरinfo_new(काष्ठा batadv_orig_node *orig_node,
		       काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo;
	अचिन्हित दीर्घ reset_समय;

	spin_lock_bh(&orig_node->neigh_list_lock);

	orig_अगरinfo = batadv_orig_अगरinfo_get(orig_node, अगर_outgoing);
	अगर (orig_अगरinfo)
		जाओ out;

	orig_अगरinfo = kzalloc(माप(*orig_अगरinfo), GFP_ATOMIC);
	अगर (!orig_अगरinfo)
		जाओ out;

	अगर (अगर_outgoing != BATADV_IF_DEFAULT)
		kref_get(&अगर_outgoing->refcount);

	reset_समय = jअगरfies - 1;
	reset_समय -= msecs_to_jअगरfies(BATADV_RESET_PROTECTION_MS);
	orig_अगरinfo->baपंचांगan_seqno_reset = reset_समय;
	orig_अगरinfo->अगर_outgoing = अगर_outgoing;
	INIT_HLIST_NODE(&orig_अगरinfo->list);
	kref_init(&orig_अगरinfo->refcount);

	kref_get(&orig_अगरinfo->refcount);
	hlist_add_head_rcu(&orig_अगरinfo->list,
			   &orig_node->अगरinfo_list);
out:
	spin_unlock_bh(&orig_node->neigh_list_lock);
	वापस orig_अगरinfo;
पूर्ण

/**
 * batadv_neigh_अगरinfo_get() - find the अगरinfo from an neigh_node
 * @neigh: the neigh node to be queried
 * @अगर_outgoing: the पूर्णांकerface क्रम which the अगरinfo should be acquired
 *
 * The object is वापसed with refcounter increased by 1.
 *
 * Return: the requested neigh_अगरinfo or शून्य अगर not found
 */
काष्ठा batadv_neigh_अगरinfo *
batadv_neigh_अगरinfo_get(काष्ठा batadv_neigh_node *neigh,
			काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_neigh_अगरinfo *neigh_अगरinfo = शून्य,
				   *पंचांगp_neigh_अगरinfo;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp_neigh_अगरinfo, &neigh->अगरinfo_list,
				 list) अणु
		अगर (पंचांगp_neigh_अगरinfo->अगर_outgoing != अगर_outgoing)
			जारी;

		अगर (!kref_get_unless_zero(&पंचांगp_neigh_अगरinfo->refcount))
			जारी;

		neigh_अगरinfo = पंचांगp_neigh_अगरinfo;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस neigh_अगरinfo;
पूर्ण

/**
 * batadv_neigh_अगरinfo_new() - search and possibly create an neigh_अगरinfo object
 * @neigh: the neigh node to be queried
 * @अगर_outgoing: the पूर्णांकerface क्रम which the अगरinfo should be acquired
 *
 * Return: शून्य in हाल of failure or the neigh_अगरinfo object क्रम the
 * अगर_outgoing पूर्णांकerface otherwise. The object is created and added to the list
 * अगर it करोes not exist.
 *
 * The object is वापसed with refcounter increased by 1.
 */
काष्ठा batadv_neigh_अगरinfo *
batadv_neigh_अगरinfo_new(काष्ठा batadv_neigh_node *neigh,
			काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_neigh_अगरinfo *neigh_अगरinfo;

	spin_lock_bh(&neigh->अगरinfo_lock);

	neigh_अगरinfo = batadv_neigh_अगरinfo_get(neigh, अगर_outgoing);
	अगर (neigh_अगरinfo)
		जाओ out;

	neigh_अगरinfo = kzalloc(माप(*neigh_अगरinfo), GFP_ATOMIC);
	अगर (!neigh_अगरinfo)
		जाओ out;

	अगर (अगर_outgoing)
		kref_get(&अगर_outgoing->refcount);

	INIT_HLIST_NODE(&neigh_अगरinfo->list);
	kref_init(&neigh_अगरinfo->refcount);
	neigh_अगरinfo->अगर_outgoing = अगर_outgoing;

	kref_get(&neigh_अगरinfo->refcount);
	hlist_add_head_rcu(&neigh_अगरinfo->list, &neigh->अगरinfo_list);

out:
	spin_unlock_bh(&neigh->अगरinfo_lock);

	वापस neigh_अगरinfo;
पूर्ण

/**
 * batadv_neigh_node_get() - retrieve a neighbour from the list
 * @orig_node: originator which the neighbour beदीर्घs to
 * @hard_अगरace: the पूर्णांकerface where this neighbour is connected to
 * @addr: the address of the neighbour
 *
 * Looks क्रम and possibly वापसs a neighbour beदीर्घing to this originator list
 * which is connected through the provided hard पूर्णांकerface.
 *
 * Return: neighbor when found. Otherwise शून्य
 */
अटल काष्ठा batadv_neigh_node *
batadv_neigh_node_get(स्थिर काष्ठा batadv_orig_node *orig_node,
		      स्थिर काष्ठा batadv_hard_अगरace *hard_अगरace,
		      स्थिर u8 *addr)
अणु
	काष्ठा batadv_neigh_node *पंचांगp_neigh_node, *res = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp_neigh_node, &orig_node->neigh_list, list) अणु
		अगर (!batadv_compare_eth(पंचांगp_neigh_node->addr, addr))
			जारी;

		अगर (पंचांगp_neigh_node->अगर_incoming != hard_अगरace)
			जारी;

		अगर (!kref_get_unless_zero(&पंचांगp_neigh_node->refcount))
			जारी;

		res = पंचांगp_neigh_node;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस res;
पूर्ण

/**
 * batadv_hardअगर_neigh_create() - create a hardअगर neighbour node
 * @hard_अगरace: the पूर्णांकerface this neighbour is connected to
 * @neigh_addr: the पूर्णांकerface address of the neighbour to retrieve
 * @orig_node: originator object representing the neighbour
 *
 * Return: the hardअगर neighbour node अगर found or created or शून्य otherwise.
 */
अटल काष्ठा batadv_hardअगर_neigh_node *
batadv_hardअगर_neigh_create(काष्ठा batadv_hard_अगरace *hard_अगरace,
			   स्थिर u8 *neigh_addr,
			   काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(hard_अगरace->soft_अगरace);
	काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh;

	spin_lock_bh(&hard_अगरace->neigh_list_lock);

	/* check अगर neighbor hasn't been added in the meanसमय */
	hardअगर_neigh = batadv_hardअगर_neigh_get(hard_अगरace, neigh_addr);
	अगर (hardअगर_neigh)
		जाओ out;

	hardअगर_neigh = kzalloc(माप(*hardअगर_neigh), GFP_ATOMIC);
	अगर (!hardअगर_neigh)
		जाओ out;

	kref_get(&hard_अगरace->refcount);
	INIT_HLIST_NODE(&hardअगर_neigh->list);
	ether_addr_copy(hardअगर_neigh->addr, neigh_addr);
	ether_addr_copy(hardअगर_neigh->orig, orig_node->orig);
	hardअगर_neigh->अगर_incoming = hard_अगरace;
	hardअगर_neigh->last_seen = jअगरfies;

	kref_init(&hardअगर_neigh->refcount);

	अगर (bat_priv->algo_ops->neigh.hardअगर_init)
		bat_priv->algo_ops->neigh.hardअगर_init(hardअगर_neigh);

	hlist_add_head_rcu(&hardअगर_neigh->list, &hard_अगरace->neigh_list);

out:
	spin_unlock_bh(&hard_अगरace->neigh_list_lock);
	वापस hardअगर_neigh;
पूर्ण

/**
 * batadv_hardअगर_neigh_get_or_create() - retrieve or create a hardअगर neighbour
 *  node
 * @hard_अगरace: the पूर्णांकerface this neighbour is connected to
 * @neigh_addr: the पूर्णांकerface address of the neighbour to retrieve
 * @orig_node: originator object representing the neighbour
 *
 * Return: the hardअगर neighbour node अगर found or created or शून्य otherwise.
 */
अटल काष्ठा batadv_hardअगर_neigh_node *
batadv_hardअगर_neigh_get_or_create(काष्ठा batadv_hard_अगरace *hard_अगरace,
				  स्थिर u8 *neigh_addr,
				  काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh;

	/* first check without locking to aव्योम the overhead */
	hardअगर_neigh = batadv_hardअगर_neigh_get(hard_अगरace, neigh_addr);
	अगर (hardअगर_neigh)
		वापस hardअगर_neigh;

	वापस batadv_hardअगर_neigh_create(hard_अगरace, neigh_addr, orig_node);
पूर्ण

/**
 * batadv_hardअगर_neigh_get() - retrieve a hardअगर neighbour from the list
 * @hard_अगरace: the पूर्णांकerface where this neighbour is connected to
 * @neigh_addr: the address of the neighbour
 *
 * Looks क्रम and possibly वापसs a neighbour beदीर्घing to this hard पूर्णांकerface.
 *
 * Return: neighbor when found. Otherwise शून्य
 */
काष्ठा batadv_hardअगर_neigh_node *
batadv_hardअगर_neigh_get(स्थिर काष्ठा batadv_hard_अगरace *hard_अगरace,
			स्थिर u8 *neigh_addr)
अणु
	काष्ठा batadv_hardअगर_neigh_node *पंचांगp_hardअगर_neigh, *hardअगर_neigh = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(पंचांगp_hardअगर_neigh,
				 &hard_अगरace->neigh_list, list) अणु
		अगर (!batadv_compare_eth(पंचांगp_hardअगर_neigh->addr, neigh_addr))
			जारी;

		अगर (!kref_get_unless_zero(&पंचांगp_hardअगर_neigh->refcount))
			जारी;

		hardअगर_neigh = पंचांगp_hardअगर_neigh;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस hardअगर_neigh;
पूर्ण

/**
 * batadv_neigh_node_create() - create a neigh node object
 * @orig_node: originator object representing the neighbour
 * @hard_अगरace: the पूर्णांकerface where the neighbour is connected to
 * @neigh_addr: the mac address of the neighbour पूर्णांकerface
 *
 * Allocates a new neigh_node object and initialises all the generic fields.
 *
 * Return: the neighbour node अगर found or created or शून्य otherwise.
 */
अटल काष्ठा batadv_neigh_node *
batadv_neigh_node_create(काष्ठा batadv_orig_node *orig_node,
			 काष्ठा batadv_hard_अगरace *hard_अगरace,
			 स्थिर u8 *neigh_addr)
अणु
	काष्ठा batadv_neigh_node *neigh_node;
	काष्ठा batadv_hardअगर_neigh_node *hardअगर_neigh = शून्य;

	spin_lock_bh(&orig_node->neigh_list_lock);

	neigh_node = batadv_neigh_node_get(orig_node, hard_अगरace, neigh_addr);
	अगर (neigh_node)
		जाओ out;

	hardअगर_neigh = batadv_hardअगर_neigh_get_or_create(hard_अगरace,
							 neigh_addr, orig_node);
	अगर (!hardअगर_neigh)
		जाओ out;

	neigh_node = kzalloc(माप(*neigh_node), GFP_ATOMIC);
	अगर (!neigh_node)
		जाओ out;

	INIT_HLIST_NODE(&neigh_node->list);
	INIT_HLIST_HEAD(&neigh_node->अगरinfo_list);
	spin_lock_init(&neigh_node->अगरinfo_lock);

	kref_get(&hard_अगरace->refcount);
	ether_addr_copy(neigh_node->addr, neigh_addr);
	neigh_node->अगर_incoming = hard_अगरace;
	neigh_node->orig_node = orig_node;
	neigh_node->last_seen = jअगरfies;

	/* increment unique neighbor refcount */
	kref_get(&hardअगर_neigh->refcount);
	neigh_node->hardअगर_neigh = hardअगर_neigh;

	/* extra reference क्रम वापस */
	kref_init(&neigh_node->refcount);

	kref_get(&neigh_node->refcount);
	hlist_add_head_rcu(&neigh_node->list, &orig_node->neigh_list);

	batadv_dbg(BATADV_DBG_BATMAN, orig_node->bat_priv,
		   "Creating new neighbor %pM for orig_node %pM on interface %s\n",
		   neigh_addr, orig_node->orig, hard_अगरace->net_dev->name);

out:
	spin_unlock_bh(&orig_node->neigh_list_lock);

	अगर (hardअगर_neigh)
		batadv_hardअगर_neigh_put(hardअगर_neigh);
	वापस neigh_node;
पूर्ण

/**
 * batadv_neigh_node_get_or_create() - retrieve or create a neigh node object
 * @orig_node: originator object representing the neighbour
 * @hard_अगरace: the पूर्णांकerface where the neighbour is connected to
 * @neigh_addr: the mac address of the neighbour पूर्णांकerface
 *
 * Return: the neighbour node अगर found or created or शून्य otherwise.
 */
काष्ठा batadv_neigh_node *
batadv_neigh_node_get_or_create(काष्ठा batadv_orig_node *orig_node,
				काष्ठा batadv_hard_अगरace *hard_अगरace,
				स्थिर u8 *neigh_addr)
अणु
	काष्ठा batadv_neigh_node *neigh_node;

	/* first check without locking to aव्योम the overhead */
	neigh_node = batadv_neigh_node_get(orig_node, hard_अगरace, neigh_addr);
	अगर (neigh_node)
		वापस neigh_node;

	वापस batadv_neigh_node_create(orig_node, hard_अगरace, neigh_addr);
पूर्ण

/**
 * batadv_hardअगर_neigh_dump() - Dump to netlink the neighbor infos क्रम a
 *  specअगरic outgoing पूर्णांकerface
 * @msg: message to dump पूर्णांकo
 * @cb: parameters क्रम the dump
 *
 * Return: 0 or error value
 */
पूर्णांक batadv_hardअगर_neigh_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(cb->skb->sk);
	काष्ठा net_device *soft_अगरace;
	काष्ठा net_device *hard_अगरace = शून्य;
	काष्ठा batadv_hard_अगरace *hardअगर = BATADV_IF_DEFAULT;
	काष्ठा batadv_priv *bat_priv;
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	पूर्णांक ret;
	पूर्णांक अगरindex, hard_अगरindex;

	अगरindex = batadv_netlink_get_अगरindex(cb->nlh, BATADV_ATTR_MESH_IFINDEX);
	अगर (!अगरindex)
		वापस -EINVAL;

	soft_अगरace = dev_get_by_index(net, अगरindex);
	अगर (!soft_अगरace || !batadv_softअगर_is_valid(soft_अगरace)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	bat_priv = netdev_priv(soft_अगरace);

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर || primary_अगर->अगर_status != BATADV_IF_ACTIVE) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	hard_अगरindex = batadv_netlink_get_अगरindex(cb->nlh,
						  BATADV_ATTR_HARD_IFINDEX);
	अगर (hard_अगरindex) अणु
		hard_अगरace = dev_get_by_index(net, hard_अगरindex);
		अगर (hard_अगरace)
			hardअगर = batadv_hardअगर_get_by_netdev(hard_अगरace);

		अगर (!hardअगर) अणु
			ret = -ENODEV;
			जाओ out;
		पूर्ण

		अगर (hardअगर->soft_अगरace != soft_अगरace) अणु
			ret = -ENOENT;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!bat_priv->algo_ops->neigh.dump) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	bat_priv->algo_ops->neigh.dump(msg, cb, bat_priv, hardअगर);

	ret = msg->len;

 out:
	अगर (hardअगर)
		batadv_hardअगर_put(hardअगर);
	अगर (hard_अगरace)
		dev_put(hard_अगरace);
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	अगर (soft_अगरace)
		dev_put(soft_अगरace);

	वापस ret;
पूर्ण

/**
 * batadv_orig_अगरinfo_release() - release orig_अगरinfo from lists and queue क्रम
 *  मुक्त after rcu grace period
 * @ref: kref poपूर्णांकer of the orig_अगरinfo
 */
अटल व्योम batadv_orig_अगरinfo_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo;
	काष्ठा batadv_neigh_node *router;

	orig_अगरinfo = container_of(ref, काष्ठा batadv_orig_अगरinfo, refcount);

	अगर (orig_अगरinfo->अगर_outgoing != BATADV_IF_DEFAULT)
		batadv_hardअगर_put(orig_अगरinfo->अगर_outgoing);

	/* this is the last reference to this object */
	router = rcu_dereference_रक्षित(orig_अगरinfo->router, true);
	अगर (router)
		batadv_neigh_node_put(router);

	kमुक्त_rcu(orig_अगरinfo, rcu);
पूर्ण

/**
 * batadv_orig_अगरinfo_put() - decrement the refcounter and possibly release
 *  the orig_अगरinfo
 * @orig_अगरinfo: the orig_अगरinfo object to release
 */
व्योम batadv_orig_अगरinfo_put(काष्ठा batadv_orig_अगरinfo *orig_अगरinfo)
अणु
	kref_put(&orig_अगरinfo->refcount, batadv_orig_अगरinfo_release);
पूर्ण

/**
 * batadv_orig_node_मुक्त_rcu() - मुक्त the orig_node
 * @rcu: rcu poपूर्णांकer of the orig_node
 */
अटल व्योम batadv_orig_node_मुक्त_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा batadv_orig_node *orig_node;

	orig_node = container_of(rcu, काष्ठा batadv_orig_node, rcu);

	batadv_mcast_purge_orig(orig_node);

	batadv_frag_purge_orig(orig_node, शून्य);

	kमुक्त(orig_node->tt_buff);
	kमुक्त(orig_node);
पूर्ण

/**
 * batadv_orig_node_release() - release orig_node from lists and queue क्रम
 *  मुक्त after rcu grace period
 * @ref: kref poपूर्णांकer of the orig_node
 */
अटल व्योम batadv_orig_node_release(काष्ठा kref *ref)
अणु
	काष्ठा hlist_node *node_पंचांगp;
	काष्ठा batadv_neigh_node *neigh_node;
	काष्ठा batadv_orig_node *orig_node;
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo;
	काष्ठा batadv_orig_node_vlan *vlan;
	काष्ठा batadv_orig_अगरinfo *last_candidate;

	orig_node = container_of(ref, काष्ठा batadv_orig_node, refcount);

	spin_lock_bh(&orig_node->neigh_list_lock);

	/* क्रम all neighbors towards this originator ... */
	hlist_क्रम_each_entry_safe(neigh_node, node_पंचांगp,
				  &orig_node->neigh_list, list) अणु
		hlist_del_rcu(&neigh_node->list);
		batadv_neigh_node_put(neigh_node);
	पूर्ण

	hlist_क्रम_each_entry_safe(orig_अगरinfo, node_पंचांगp,
				  &orig_node->अगरinfo_list, list) अणु
		hlist_del_rcu(&orig_अगरinfo->list);
		batadv_orig_अगरinfo_put(orig_अगरinfo);
	पूर्ण

	last_candidate = orig_node->last_bonding_candidate;
	orig_node->last_bonding_candidate = शून्य;
	spin_unlock_bh(&orig_node->neigh_list_lock);

	अगर (last_candidate)
		batadv_orig_अगरinfo_put(last_candidate);

	spin_lock_bh(&orig_node->vlan_list_lock);
	hlist_क्रम_each_entry_safe(vlan, node_पंचांगp, &orig_node->vlan_list, list) अणु
		hlist_del_rcu(&vlan->list);
		batadv_orig_node_vlan_put(vlan);
	पूर्ण
	spin_unlock_bh(&orig_node->vlan_list_lock);

	/* Free nc_nodes */
	batadv_nc_purge_orig(orig_node->bat_priv, orig_node, शून्य);

	call_rcu(&orig_node->rcu, batadv_orig_node_मुक्त_rcu);
पूर्ण

/**
 * batadv_orig_node_put() - decrement the orig node refcounter and possibly
 *  release it
 * @orig_node: the orig node to मुक्त
 */
व्योम batadv_orig_node_put(काष्ठा batadv_orig_node *orig_node)
अणु
	kref_put(&orig_node->refcount, batadv_orig_node_release);
पूर्ण

/**
 * batadv_originator_मुक्त() - Free all originator काष्ठाures
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_originator_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->orig_hash;
	काष्ठा hlist_node *node_पंचांगp;
	काष्ठा hlist_head *head;
	spinlock_t *list_lock; /* spinlock to protect ग_लिखो access */
	काष्ठा batadv_orig_node *orig_node;
	u32 i;

	अगर (!hash)
		वापस;

	cancel_delayed_work_sync(&bat_priv->orig_work);

	bat_priv->orig_hash = शून्य;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];
		list_lock = &hash->list_locks[i];

		spin_lock_bh(list_lock);
		hlist_क्रम_each_entry_safe(orig_node, node_पंचांगp,
					  head, hash_entry) अणु
			hlist_del_rcu(&orig_node->hash_entry);
			batadv_orig_node_put(orig_node);
		पूर्ण
		spin_unlock_bh(list_lock);
	पूर्ण

	batadv_hash_destroy(hash);
पूर्ण

/**
 * batadv_orig_node_new() - creates a new orig_node
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: the mac address of the originator
 *
 * Creates a new originator object and initialises all the generic fields.
 * The new object is not added to the originator list.
 *
 * Return: the newly created object or शून्य on failure.
 */
काष्ठा batadv_orig_node *batadv_orig_node_new(काष्ठा batadv_priv *bat_priv,
					      स्थिर u8 *addr)
अणु
	काष्ठा batadv_orig_node *orig_node;
	काष्ठा batadv_orig_node_vlan *vlan;
	अचिन्हित दीर्घ reset_समय;
	पूर्णांक i;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Creating new originator: %pM\n", addr);

	orig_node = kzalloc(माप(*orig_node), GFP_ATOMIC);
	अगर (!orig_node)
		वापस शून्य;

	INIT_HLIST_HEAD(&orig_node->neigh_list);
	INIT_HLIST_HEAD(&orig_node->vlan_list);
	INIT_HLIST_HEAD(&orig_node->अगरinfo_list);
	spin_lock_init(&orig_node->bcast_seqno_lock);
	spin_lock_init(&orig_node->neigh_list_lock);
	spin_lock_init(&orig_node->tt_buff_lock);
	spin_lock_init(&orig_node->tt_lock);
	spin_lock_init(&orig_node->vlan_list_lock);

	batadv_nc_init_orig(orig_node);

	/* extra reference क्रम वापस */
	kref_init(&orig_node->refcount);

	orig_node->bat_priv = bat_priv;
	ether_addr_copy(orig_node->orig, addr);
	batadv_dat_init_orig_node_addr(orig_node);
	atomic_set(&orig_node->last_ttvn, 0);
	orig_node->tt_buff = शून्य;
	orig_node->tt_buff_len = 0;
	orig_node->last_seen = jअगरfies;
	reset_समय = jअगरfies - 1 - msecs_to_jअगरfies(BATADV_RESET_PROTECTION_MS);
	orig_node->bcast_seqno_reset = reset_समय;

#अगर_घोषित CONFIG_BATMAN_ADV_MCAST
	orig_node->mcast_flags = BATADV_MCAST_WANT_NO_RTR4;
	orig_node->mcast_flags |= BATADV_MCAST_WANT_NO_RTR6;
	INIT_HLIST_NODE(&orig_node->mcast_want_all_unsnoopables_node);
	INIT_HLIST_NODE(&orig_node->mcast_want_all_ipv4_node);
	INIT_HLIST_NODE(&orig_node->mcast_want_all_ipv6_node);
	spin_lock_init(&orig_node->mcast_handler_lock);
#पूर्ण_अगर

	/* create a vlan object क्रम the "untagged" LAN */
	vlan = batadv_orig_node_vlan_new(orig_node, BATADV_NO_FLAGS);
	अगर (!vlan)
		जाओ मुक्त_orig_node;
	/* batadv_orig_node_vlan_new() increases the refcounter.
	 * Immediately release vlan since it is not needed anymore in this
	 * context
	 */
	batadv_orig_node_vlan_put(vlan);

	क्रम (i = 0; i < BATADV_FRAG_BUFFER_COUNT; i++) अणु
		INIT_HLIST_HEAD(&orig_node->fragments[i].fragment_list);
		spin_lock_init(&orig_node->fragments[i].lock);
		orig_node->fragments[i].size = 0;
	पूर्ण

	वापस orig_node;
मुक्त_orig_node:
	kमुक्त(orig_node);
	वापस शून्य;
पूर्ण

/**
 * batadv_purge_neigh_अगरinfo() - purge obsolete अगरinfo entries from neighbor
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @neigh: orig node which is to be checked
 */
अटल व्योम
batadv_purge_neigh_अगरinfo(काष्ठा batadv_priv *bat_priv,
			  काष्ठा batadv_neigh_node *neigh)
अणु
	काष्ठा batadv_neigh_अगरinfo *neigh_अगरinfo;
	काष्ठा batadv_hard_अगरace *अगर_outgoing;
	काष्ठा hlist_node *node_पंचांगp;

	spin_lock_bh(&neigh->अगरinfo_lock);

	/* क्रम all अगरinfo objects क्रम this neighinator */
	hlist_क्रम_each_entry_safe(neigh_अगरinfo, node_पंचांगp,
				  &neigh->अगरinfo_list, list) अणु
		अगर_outgoing = neigh_अगरinfo->अगर_outgoing;

		/* always keep the शेष पूर्णांकerface */
		अगर (अगर_outgoing == BATADV_IF_DEFAULT)
			जारी;

		/* करोn't purge अगर the पूर्णांकerface is not (going) करोwn */
		अगर (अगर_outgoing->अगर_status != BATADV_IF_INACTIVE &&
		    अगर_outgoing->अगर_status != BATADV_IF_NOT_IN_USE &&
		    अगर_outgoing->अगर_status != BATADV_IF_TO_BE_REMOVED)
			जारी;

		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "neighbor/ifinfo purge: neighbor %pM, iface: %s\n",
			   neigh->addr, अगर_outgoing->net_dev->name);

		hlist_del_rcu(&neigh_अगरinfo->list);
		batadv_neigh_अगरinfo_put(neigh_अगरinfo);
	पूर्ण

	spin_unlock_bh(&neigh->अगरinfo_lock);
पूर्ण

/**
 * batadv_purge_orig_अगरinfo() - purge obsolete अगरinfo entries from originator
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: orig node which is to be checked
 *
 * Return: true अगर any अगरinfo entry was purged, false otherwise.
 */
अटल bool
batadv_purge_orig_अगरinfo(काष्ठा batadv_priv *bat_priv,
			 काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_orig_अगरinfo *orig_अगरinfo;
	काष्ठा batadv_hard_अगरace *अगर_outgoing;
	काष्ठा hlist_node *node_पंचांगp;
	bool अगरinfo_purged = false;

	spin_lock_bh(&orig_node->neigh_list_lock);

	/* क्रम all अगरinfo objects क्रम this originator */
	hlist_क्रम_each_entry_safe(orig_अगरinfo, node_पंचांगp,
				  &orig_node->अगरinfo_list, list) अणु
		अगर_outgoing = orig_अगरinfo->अगर_outgoing;

		/* always keep the शेष पूर्णांकerface */
		अगर (अगर_outgoing == BATADV_IF_DEFAULT)
			जारी;

		/* करोn't purge अगर the पूर्णांकerface is not (going) करोwn */
		अगर (अगर_outgoing->अगर_status != BATADV_IF_INACTIVE &&
		    अगर_outgoing->अगर_status != BATADV_IF_NOT_IN_USE &&
		    अगर_outgoing->अगर_status != BATADV_IF_TO_BE_REMOVED)
			जारी;

		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "router/ifinfo purge: originator %pM, iface: %s\n",
			   orig_node->orig, अगर_outgoing->net_dev->name);

		अगरinfo_purged = true;

		hlist_del_rcu(&orig_अगरinfo->list);
		batadv_orig_अगरinfo_put(orig_अगरinfo);
		अगर (orig_node->last_bonding_candidate == orig_अगरinfo) अणु
			orig_node->last_bonding_candidate = शून्य;
			batadv_orig_अगरinfo_put(orig_अगरinfo);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&orig_node->neigh_list_lock);

	वापस अगरinfo_purged;
पूर्ण

/**
 * batadv_purge_orig_neighbors() - purges neighbors from originator
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: orig node which is to be checked
 *
 * Return: true अगर any neighbor was purged, false otherwise
 */
अटल bool
batadv_purge_orig_neighbors(काष्ठा batadv_priv *bat_priv,
			    काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा hlist_node *node_पंचांगp;
	काष्ठा batadv_neigh_node *neigh_node;
	bool neigh_purged = false;
	अचिन्हित दीर्घ last_seen;
	काष्ठा batadv_hard_अगरace *अगर_incoming;

	spin_lock_bh(&orig_node->neigh_list_lock);

	/* क्रम all neighbors towards this originator ... */
	hlist_क्रम_each_entry_safe(neigh_node, node_पंचांगp,
				  &orig_node->neigh_list, list) अणु
		last_seen = neigh_node->last_seen;
		अगर_incoming = neigh_node->अगर_incoming;

		अगर (batadv_has_समयd_out(last_seen, BATADV_PURGE_TIMEOUT) ||
		    अगर_incoming->अगर_status == BATADV_IF_INACTIVE ||
		    अगर_incoming->अगर_status == BATADV_IF_NOT_IN_USE ||
		    अगर_incoming->अगर_status == BATADV_IF_TO_BE_REMOVED) अणु
			अगर (अगर_incoming->अगर_status == BATADV_IF_INACTIVE ||
			    अगर_incoming->अगर_status == BATADV_IF_NOT_IN_USE ||
			    अगर_incoming->अगर_status == BATADV_IF_TO_BE_REMOVED)
				batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
					   "neighbor purge: originator %pM, neighbor: %pM, iface: %s\n",
					   orig_node->orig, neigh_node->addr,
					   अगर_incoming->net_dev->name);
			अन्यथा
				batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
					   "neighbor timeout: originator %pM, neighbor: %pM, last_seen: %u\n",
					   orig_node->orig, neigh_node->addr,
					   jअगरfies_to_msecs(last_seen));

			neigh_purged = true;

			hlist_del_rcu(&neigh_node->list);
			batadv_neigh_node_put(neigh_node);
		पूर्ण अन्यथा अणु
			/* only necessary अगर not the whole neighbor is to be
			 * deleted, but some पूर्णांकerface has been हटाओd.
			 */
			batadv_purge_neigh_अगरinfo(bat_priv, neigh_node);
		पूर्ण
	पूर्ण

	spin_unlock_bh(&orig_node->neigh_list_lock);
	वापस neigh_purged;
पूर्ण

/**
 * batadv_find_best_neighbor() - finds the best neighbor after purging
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: orig node which is to be checked
 * @अगर_outgoing: the पूर्णांकerface क्रम which the metric should be compared
 *
 * Return: the current best neighbor, with refcount increased.
 */
अटल काष्ठा batadv_neigh_node *
batadv_find_best_neighbor(काष्ठा batadv_priv *bat_priv,
			  काष्ठा batadv_orig_node *orig_node,
			  काष्ठा batadv_hard_अगरace *अगर_outgoing)
अणु
	काष्ठा batadv_neigh_node *best = शून्य, *neigh;
	काष्ठा batadv_algo_ops *bao = bat_priv->algo_ops;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(neigh, &orig_node->neigh_list, list) अणु
		अगर (best && (bao->neigh.cmp(neigh, अगर_outgoing, best,
					    अगर_outgoing) <= 0))
			जारी;

		अगर (!kref_get_unless_zero(&neigh->refcount))
			जारी;

		अगर (best)
			batadv_neigh_node_put(best);

		best = neigh;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस best;
पूर्ण

/**
 * batadv_purge_orig_node() - purges obsolete inक्रमmation from an orig_node
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: orig node which is to be checked
 *
 * This function checks अगर the orig_node or subकाष्ठाures of it have become
 * obsolete, and purges this inक्रमmation अगर that's the हाल.
 *
 * Return: true अगर the orig_node is to be हटाओd, false otherwise.
 */
अटल bool batadv_purge_orig_node(काष्ठा batadv_priv *bat_priv,
				   काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_neigh_node *best_neigh_node;
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	bool changed_अगरinfo, changed_neigh;

	अगर (batadv_has_समयd_out(orig_node->last_seen,
				 2 * BATADV_PURGE_TIMEOUT)) अणु
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Originator timeout: originator %pM, last_seen %u\n",
			   orig_node->orig,
			   jअगरfies_to_msecs(orig_node->last_seen));
		वापस true;
	पूर्ण
	changed_अगरinfo = batadv_purge_orig_अगरinfo(bat_priv, orig_node);
	changed_neigh = batadv_purge_orig_neighbors(bat_priv, orig_node);

	अगर (!changed_अगरinfo && !changed_neigh)
		वापस false;

	/* first क्रम शून्य ... */
	best_neigh_node = batadv_find_best_neighbor(bat_priv, orig_node,
						    BATADV_IF_DEFAULT);
	batadv_update_route(bat_priv, orig_node, BATADV_IF_DEFAULT,
			    best_neigh_node);
	अगर (best_neigh_node)
		batadv_neigh_node_put(best_neigh_node);

	/* ... then क्रम all other पूर्णांकerfaces. */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->अगर_status != BATADV_IF_ACTIVE)
			जारी;

		अगर (hard_अगरace->soft_अगरace != bat_priv->soft_अगरace)
			जारी;

		अगर (!kref_get_unless_zero(&hard_अगरace->refcount))
			जारी;

		best_neigh_node = batadv_find_best_neighbor(bat_priv,
							    orig_node,
							    hard_अगरace);
		batadv_update_route(bat_priv, orig_node, hard_अगरace,
				    best_neigh_node);
		अगर (best_neigh_node)
			batadv_neigh_node_put(best_neigh_node);

		batadv_hardअगर_put(hard_अगरace);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस false;
पूर्ण

/**
 * batadv_purge_orig_ref() - Purge all outdated originators
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_purge_orig_ref(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->orig_hash;
	काष्ठा hlist_node *node_पंचांगp;
	काष्ठा hlist_head *head;
	spinlock_t *list_lock; /* spinlock to protect ग_लिखो access */
	काष्ठा batadv_orig_node *orig_node;
	u32 i;

	अगर (!hash)
		वापस;

	/* क्रम all origins... */
	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];
		list_lock = &hash->list_locks[i];

		spin_lock_bh(list_lock);
		hlist_क्रम_each_entry_safe(orig_node, node_पंचांगp,
					  head, hash_entry) अणु
			अगर (batadv_purge_orig_node(bat_priv, orig_node)) अणु
				batadv_gw_node_delete(bat_priv, orig_node);
				hlist_del_rcu(&orig_node->hash_entry);
				batadv_tt_global_del_orig(orig_node->bat_priv,
							  orig_node, -1,
							  "originator timed out");
				batadv_orig_node_put(orig_node);
				जारी;
			पूर्ण

			batadv_frag_purge_orig(orig_node,
					       batadv_frag_check_entry);
		पूर्ण
		spin_unlock_bh(list_lock);
	पूर्ण

	batadv_gw_election(bat_priv);
पूर्ण

अटल व्योम batadv_purge_orig(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work;
	काष्ठा batadv_priv *bat_priv;

	delayed_work = to_delayed_work(work);
	bat_priv = container_of(delayed_work, काष्ठा batadv_priv, orig_work);
	batadv_purge_orig_ref(bat_priv);
	queue_delayed_work(batadv_event_workqueue,
			   &bat_priv->orig_work,
			   msecs_to_jअगरfies(BATADV_ORIG_WORK_PERIOD));
पूर्ण

/**
 * batadv_orig_dump() - Dump to netlink the originator infos क्रम a specअगरic
 *  outgoing पूर्णांकerface
 * @msg: message to dump पूर्णांकo
 * @cb: parameters क्रम the dump
 *
 * Return: 0 or error value
 */
पूर्णांक batadv_orig_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(cb->skb->sk);
	काष्ठा net_device *soft_अगरace;
	काष्ठा net_device *hard_अगरace = शून्य;
	काष्ठा batadv_hard_अगरace *hardअगर = BATADV_IF_DEFAULT;
	काष्ठा batadv_priv *bat_priv;
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	पूर्णांक ret;
	पूर्णांक अगरindex, hard_अगरindex;

	अगरindex = batadv_netlink_get_अगरindex(cb->nlh, BATADV_ATTR_MESH_IFINDEX);
	अगर (!अगरindex)
		वापस -EINVAL;

	soft_अगरace = dev_get_by_index(net, अगरindex);
	अगर (!soft_अगरace || !batadv_softअगर_is_valid(soft_अगरace)) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	bat_priv = netdev_priv(soft_अगरace);

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर || primary_अगर->अगर_status != BATADV_IF_ACTIVE) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	hard_अगरindex = batadv_netlink_get_अगरindex(cb->nlh,
						  BATADV_ATTR_HARD_IFINDEX);
	अगर (hard_अगरindex) अणु
		hard_अगरace = dev_get_by_index(net, hard_अगरindex);
		अगर (hard_अगरace)
			hardअगर = batadv_hardअगर_get_by_netdev(hard_अगरace);

		अगर (!hardअगर) अणु
			ret = -ENODEV;
			जाओ out;
		पूर्ण

		अगर (hardअगर->soft_अगरace != soft_अगरace) अणु
			ret = -ENOENT;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!bat_priv->algo_ops->orig.dump) अणु
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	bat_priv->algo_ops->orig.dump(msg, cb, bat_priv, hardअगर);

	ret = msg->len;

 out:
	अगर (hardअगर)
		batadv_hardअगर_put(hardअगर);
	अगर (hard_अगरace)
		dev_put(hard_अगरace);
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	अगर (soft_अगरace)
		dev_put(soft_अगरace);

	वापस ret;
पूर्ण
