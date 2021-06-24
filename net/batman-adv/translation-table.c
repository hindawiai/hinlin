<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich, Antonio Quartulli
 */

#समावेश "translation-table.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/build_bug.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/cache.h>
#समावेश <linux/compiler.h>
#समावेश <linux/crc32c.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/init.h>
#समावेश <linux/jhash.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/workqueue.h>
#समावेश <net/genetlink.h>
#समावेश <net/netlink.h>
#समावेश <net/sock.h>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "bridge_loop_avoidance.h"
#समावेश "hard-interface.h"
#समावेश "hash.h"
#समावेश "log.h"
#समावेश "netlink.h"
#समावेश "originator.h"
#समावेश "soft-interface.h"
#समावेश "tvlv.h"

अटल काष्ठा kmem_cache *batadv_tl_cache __पढ़ो_mostly;
अटल काष्ठा kmem_cache *batadv_tg_cache __पढ़ो_mostly;
अटल काष्ठा kmem_cache *batadv_tt_orig_cache __पढ़ो_mostly;
अटल काष्ठा kmem_cache *batadv_tt_change_cache __पढ़ो_mostly;
अटल काष्ठा kmem_cache *batadv_tt_req_cache __पढ़ो_mostly;
अटल काष्ठा kmem_cache *batadv_tt_roam_cache __पढ़ो_mostly;

/* hash class keys */
अटल काष्ठा lock_class_key batadv_tt_local_hash_lock_class_key;
अटल काष्ठा lock_class_key batadv_tt_global_hash_lock_class_key;

अटल व्योम batadv_send_roam_adv(काष्ठा batadv_priv *bat_priv, u8 *client,
				 अचिन्हित लघु vid,
				 काष्ठा batadv_orig_node *orig_node);
अटल व्योम batadv_tt_purge(काष्ठा work_काष्ठा *work);
अटल व्योम
batadv_tt_global_del_orig_list(काष्ठा batadv_tt_global_entry *tt_global_entry);
अटल व्योम batadv_tt_global_del(काष्ठा batadv_priv *bat_priv,
				 काष्ठा batadv_orig_node *orig_node,
				 स्थिर अचिन्हित अक्षर *addr,
				 अचिन्हित लघु vid, स्थिर अक्षर *message,
				 bool roaming);

/**
 * batadv_compare_tt() - check अगर two TT entries are the same
 * @node: the list element poपूर्णांकer of the first TT entry
 * @data2: poपूर्णांकer to the tt_common_entry of the second TT entry
 *
 * Compare the MAC address and the VLAN ID of the two TT entries and check अगर
 * they are the same TT client.
 * Return: true अगर the two TT clients are the same, false otherwise
 */
अटल bool batadv_compare_tt(स्थिर काष्ठा hlist_node *node, स्थिर व्योम *data2)
अणु
	स्थिर व्योम *data1 = container_of(node, काष्ठा batadv_tt_common_entry,
					 hash_entry);
	स्थिर काष्ठा batadv_tt_common_entry *tt1 = data1;
	स्थिर काष्ठा batadv_tt_common_entry *tt2 = data2;

	वापस (tt1->vid == tt2->vid) && batadv_compare_eth(data1, data2);
पूर्ण

/**
 * batadv_choose_tt() - वापस the index of the tt entry in the hash table
 * @data: poपूर्णांकer to the tt_common_entry object to map
 * @size: the size of the hash table
 *
 * Return: the hash index where the object represented by 'data' should be
 * stored at.
 */
अटल अंतरभूत u32 batadv_choose_tt(स्थिर व्योम *data, u32 size)
अणु
	काष्ठा batadv_tt_common_entry *tt;
	u32 hash = 0;

	tt = (काष्ठा batadv_tt_common_entry *)data;
	hash = jhash(&tt->addr, ETH_ALEN, hash);
	hash = jhash(&tt->vid, माप(tt->vid), hash);

	वापस hash % size;
पूर्ण

/**
 * batadv_tt_hash_find() - look क्रम a client in the given hash table
 * @hash: the hash table to search
 * @addr: the mac address of the client to look क्रम
 * @vid: VLAN identअगरier
 *
 * Return: a poपूर्णांकer to the tt_common काष्ठा beदीर्घing to the searched client अगर
 * found, शून्य otherwise.
 */
अटल काष्ठा batadv_tt_common_entry *
batadv_tt_hash_find(काष्ठा batadv_hashtable *hash, स्थिर u8 *addr,
		    अचिन्हित लघु vid)
अणु
	काष्ठा hlist_head *head;
	काष्ठा batadv_tt_common_entry to_search, *tt, *tt_पंचांगp = शून्य;
	u32 index;

	अगर (!hash)
		वापस शून्य;

	ether_addr_copy(to_search.addr, addr);
	to_search.vid = vid;

	index = batadv_choose_tt(&to_search, hash->size);
	head = &hash->table[index];

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(tt, head, hash_entry) अणु
		अगर (!batadv_compare_eth(tt, addr))
			जारी;

		अगर (tt->vid != vid)
			जारी;

		अगर (!kref_get_unless_zero(&tt->refcount))
			जारी;

		tt_पंचांगp = tt;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस tt_पंचांगp;
पूर्ण

/**
 * batadv_tt_local_hash_find() - search the local table क्रम a given client
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: the mac address of the client to look क्रम
 * @vid: VLAN identअगरier
 *
 * Return: a poपूर्णांकer to the corresponding tt_local_entry काष्ठा अगर the client is
 * found, शून्य otherwise.
 */
अटल काष्ठा batadv_tt_local_entry *
batadv_tt_local_hash_find(काष्ठा batadv_priv *bat_priv, स्थिर u8 *addr,
			  अचिन्हित लघु vid)
अणु
	काष्ठा batadv_tt_common_entry *tt_common_entry;
	काष्ठा batadv_tt_local_entry *tt_local_entry = शून्य;

	tt_common_entry = batadv_tt_hash_find(bat_priv->tt.local_hash, addr,
					      vid);
	अगर (tt_common_entry)
		tt_local_entry = container_of(tt_common_entry,
					      काष्ठा batadv_tt_local_entry,
					      common);
	वापस tt_local_entry;
पूर्ण

/**
 * batadv_tt_global_hash_find() - search the global table क्रम a given client
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: the mac address of the client to look क्रम
 * @vid: VLAN identअगरier
 *
 * Return: a poपूर्णांकer to the corresponding tt_global_entry काष्ठा अगर the client
 * is found, शून्य otherwise.
 */
काष्ठा batadv_tt_global_entry *
batadv_tt_global_hash_find(काष्ठा batadv_priv *bat_priv, स्थिर u8 *addr,
			   अचिन्हित लघु vid)
अणु
	काष्ठा batadv_tt_common_entry *tt_common_entry;
	काष्ठा batadv_tt_global_entry *tt_global_entry = शून्य;

	tt_common_entry = batadv_tt_hash_find(bat_priv->tt.global_hash, addr,
					      vid);
	अगर (tt_common_entry)
		tt_global_entry = container_of(tt_common_entry,
					       काष्ठा batadv_tt_global_entry,
					       common);
	वापस tt_global_entry;
पूर्ण

/**
 * batadv_tt_local_entry_मुक्त_rcu() - मुक्त the tt_local_entry
 * @rcu: rcu poपूर्णांकer of the tt_local_entry
 */
अटल व्योम batadv_tt_local_entry_मुक्त_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा batadv_tt_local_entry *tt_local_entry;

	tt_local_entry = container_of(rcu, काष्ठा batadv_tt_local_entry,
				      common.rcu);

	kmem_cache_मुक्त(batadv_tl_cache, tt_local_entry);
पूर्ण

/**
 * batadv_tt_local_entry_release() - release tt_local_entry from lists and queue
 *  क्रम मुक्त after rcu grace period
 * @ref: kref poपूर्णांकer of the nc_node
 */
अटल व्योम batadv_tt_local_entry_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_tt_local_entry *tt_local_entry;

	tt_local_entry = container_of(ref, काष्ठा batadv_tt_local_entry,
				      common.refcount);

	batadv_softअगर_vlan_put(tt_local_entry->vlan);

	call_rcu(&tt_local_entry->common.rcu, batadv_tt_local_entry_मुक्त_rcu);
पूर्ण

/**
 * batadv_tt_local_entry_put() - decrement the tt_local_entry refcounter and
 *  possibly release it
 * @tt_local_entry: tt_local_entry to be मुक्त'd
 */
अटल व्योम
batadv_tt_local_entry_put(काष्ठा batadv_tt_local_entry *tt_local_entry)
अणु
	kref_put(&tt_local_entry->common.refcount,
		 batadv_tt_local_entry_release);
पूर्ण

/**
 * batadv_tt_global_entry_मुक्त_rcu() - मुक्त the tt_global_entry
 * @rcu: rcu poपूर्णांकer of the tt_global_entry
 */
अटल व्योम batadv_tt_global_entry_मुक्त_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा batadv_tt_global_entry *tt_global_entry;

	tt_global_entry = container_of(rcu, काष्ठा batadv_tt_global_entry,
				       common.rcu);

	kmem_cache_मुक्त(batadv_tg_cache, tt_global_entry);
पूर्ण

/**
 * batadv_tt_global_entry_release() - release tt_global_entry from lists and
 *  queue क्रम मुक्त after rcu grace period
 * @ref: kref poपूर्णांकer of the nc_node
 */
अटल व्योम batadv_tt_global_entry_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_tt_global_entry *tt_global_entry;

	tt_global_entry = container_of(ref, काष्ठा batadv_tt_global_entry,
				       common.refcount);

	batadv_tt_global_del_orig_list(tt_global_entry);

	call_rcu(&tt_global_entry->common.rcu, batadv_tt_global_entry_मुक्त_rcu);
पूर्ण

/**
 * batadv_tt_global_entry_put() - decrement the tt_global_entry refcounter and
 *  possibly release it
 * @tt_global_entry: tt_global_entry to be मुक्त'd
 */
व्योम batadv_tt_global_entry_put(काष्ठा batadv_tt_global_entry *tt_global_entry)
अणु
	kref_put(&tt_global_entry->common.refcount,
		 batadv_tt_global_entry_release);
पूर्ण

/**
 * batadv_tt_global_hash_count() - count the number of orig entries
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: the mac address of the client to count entries क्रम
 * @vid: VLAN identअगरier
 *
 * Return: the number of originators advertising the given address/data
 * (excluding our self).
 */
पूर्णांक batadv_tt_global_hash_count(काष्ठा batadv_priv *bat_priv,
				स्थिर u8 *addr, अचिन्हित लघु vid)
अणु
	काष्ठा batadv_tt_global_entry *tt_global_entry;
	पूर्णांक count;

	tt_global_entry = batadv_tt_global_hash_find(bat_priv, addr, vid);
	अगर (!tt_global_entry)
		वापस 0;

	count = atomic_पढ़ो(&tt_global_entry->orig_list_count);
	batadv_tt_global_entry_put(tt_global_entry);

	वापस count;
पूर्ण

/**
 * batadv_tt_local_size_mod() - change the size by v of the local table
 *  identअगरied by vid
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @vid: the VLAN identअगरier of the sub-table to change
 * @v: the amount to sum to the local table size
 */
अटल व्योम batadv_tt_local_size_mod(काष्ठा batadv_priv *bat_priv,
				     अचिन्हित लघु vid, पूर्णांक v)
अणु
	काष्ठा batadv_softअगर_vlan *vlan;

	vlan = batadv_softअगर_vlan_get(bat_priv, vid);
	अगर (!vlan)
		वापस;

	atomic_add(v, &vlan->tt.num_entries);

	batadv_softअगर_vlan_put(vlan);
पूर्ण

/**
 * batadv_tt_local_size_inc() - increase by one the local table size क्रम the
 *  given vid
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @vid: the VLAN identअगरier
 */
अटल व्योम batadv_tt_local_size_inc(काष्ठा batadv_priv *bat_priv,
				     अचिन्हित लघु vid)
अणु
	batadv_tt_local_size_mod(bat_priv, vid, 1);
पूर्ण

/**
 * batadv_tt_local_size_dec() - decrease by one the local table size क्रम the
 *  given vid
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @vid: the VLAN identअगरier
 */
अटल व्योम batadv_tt_local_size_dec(काष्ठा batadv_priv *bat_priv,
				     अचिन्हित लघु vid)
अणु
	batadv_tt_local_size_mod(bat_priv, vid, -1);
पूर्ण

/**
 * batadv_tt_global_size_mod() - change the size by v of the global table
 *  क्रम orig_node identअगरied by vid
 * @orig_node: the originator क्रम which the table has to be modअगरied
 * @vid: the VLAN identअगरier
 * @v: the amount to sum to the global table size
 */
अटल व्योम batadv_tt_global_size_mod(काष्ठा batadv_orig_node *orig_node,
				      अचिन्हित लघु vid, पूर्णांक v)
अणु
	काष्ठा batadv_orig_node_vlan *vlan;

	vlan = batadv_orig_node_vlan_new(orig_node, vid);
	अगर (!vlan)
		वापस;

	अगर (atomic_add_वापस(v, &vlan->tt.num_entries) == 0) अणु
		spin_lock_bh(&orig_node->vlan_list_lock);
		अगर (!hlist_unhashed(&vlan->list)) अणु
			hlist_del_init_rcu(&vlan->list);
			batadv_orig_node_vlan_put(vlan);
		पूर्ण
		spin_unlock_bh(&orig_node->vlan_list_lock);
	पूर्ण

	batadv_orig_node_vlan_put(vlan);
पूर्ण

/**
 * batadv_tt_global_size_inc() - increase by one the global table size क्रम the
 *  given vid
 * @orig_node: the originator which global table size has to be decreased
 * @vid: the vlan identअगरier
 */
अटल व्योम batadv_tt_global_size_inc(काष्ठा batadv_orig_node *orig_node,
				      अचिन्हित लघु vid)
अणु
	batadv_tt_global_size_mod(orig_node, vid, 1);
पूर्ण

/**
 * batadv_tt_global_size_dec() - decrease by one the global table size क्रम the
 *  given vid
 * @orig_node: the originator which global table size has to be decreased
 * @vid: the vlan identअगरier
 */
अटल व्योम batadv_tt_global_size_dec(काष्ठा batadv_orig_node *orig_node,
				      अचिन्हित लघु vid)
अणु
	batadv_tt_global_size_mod(orig_node, vid, -1);
पूर्ण

/**
 * batadv_tt_orig_list_entry_मुक्त_rcu() - मुक्त the orig_entry
 * @rcu: rcu poपूर्णांकer of the orig_entry
 */
अटल व्योम batadv_tt_orig_list_entry_मुक्त_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा batadv_tt_orig_list_entry *orig_entry;

	orig_entry = container_of(rcu, काष्ठा batadv_tt_orig_list_entry, rcu);

	kmem_cache_मुक्त(batadv_tt_orig_cache, orig_entry);
पूर्ण

/**
 * batadv_tt_orig_list_entry_release() - release tt orig entry from lists and
 *  queue क्रम मुक्त after rcu grace period
 * @ref: kref poपूर्णांकer of the tt orig entry
 */
अटल व्योम batadv_tt_orig_list_entry_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_tt_orig_list_entry *orig_entry;

	orig_entry = container_of(ref, काष्ठा batadv_tt_orig_list_entry,
				  refcount);

	batadv_orig_node_put(orig_entry->orig_node);
	call_rcu(&orig_entry->rcu, batadv_tt_orig_list_entry_मुक्त_rcu);
पूर्ण

/**
 * batadv_tt_orig_list_entry_put() - decrement the tt orig entry refcounter and
 *  possibly release it
 * @orig_entry: tt orig entry to be मुक्त'd
 */
अटल व्योम
batadv_tt_orig_list_entry_put(काष्ठा batadv_tt_orig_list_entry *orig_entry)
अणु
	kref_put(&orig_entry->refcount, batadv_tt_orig_list_entry_release);
पूर्ण

/**
 * batadv_tt_local_event() - store a local TT event (ADD/DEL)
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @tt_local_entry: the TT entry involved in the event
 * @event_flags: flags to store in the event काष्ठाure
 */
अटल व्योम batadv_tt_local_event(काष्ठा batadv_priv *bat_priv,
				  काष्ठा batadv_tt_local_entry *tt_local_entry,
				  u8 event_flags)
अणु
	काष्ठा batadv_tt_change_node *tt_change_node, *entry, *safe;
	काष्ठा batadv_tt_common_entry *common = &tt_local_entry->common;
	u8 flags = common->flags | event_flags;
	bool event_हटाओd = false;
	bool del_op_requested, del_op_entry;

	tt_change_node = kmem_cache_alloc(batadv_tt_change_cache, GFP_ATOMIC);
	अगर (!tt_change_node)
		वापस;

	tt_change_node->change.flags = flags;
	स_रखो(tt_change_node->change.reserved, 0,
	       माप(tt_change_node->change.reserved));
	ether_addr_copy(tt_change_node->change.addr, common->addr);
	tt_change_node->change.vid = htons(common->vid);

	del_op_requested = flags & BATADV_TT_CLIENT_DEL;

	/* check क्रम ADD+DEL or DEL+ADD events */
	spin_lock_bh(&bat_priv->tt.changes_list_lock);
	list_क्रम_each_entry_safe(entry, safe, &bat_priv->tt.changes_list,
				 list) अणु
		अगर (!batadv_compare_eth(entry->change.addr, common->addr))
			जारी;

		/* DEL+ADD in the same orig पूर्णांकerval have no effect and can be
		 * हटाओd to aव्योम silly behaviour on the receiver side. The
		 * other way around (ADD+DEL) can happen in हाल of roaming of
		 * a client still in the NEW state. Roaming of NEW clients is
		 * now possible due to स्वतःmatically recognition of "temporary"
		 * clients
		 */
		del_op_entry = entry->change.flags & BATADV_TT_CLIENT_DEL;
		अगर (!del_op_requested && del_op_entry)
			जाओ del;
		अगर (del_op_requested && !del_op_entry)
			जाओ del;

		/* this is a second add in the same originator पूर्णांकerval. It
		 * means that flags have been changed: update them!
		 */
		अगर (!del_op_requested && !del_op_entry)
			entry->change.flags = flags;

		जारी;
del:
		list_del(&entry->list);
		kmem_cache_मुक्त(batadv_tt_change_cache, entry);
		kmem_cache_मुक्त(batadv_tt_change_cache, tt_change_node);
		event_हटाओd = true;
		जाओ unlock;
	पूर्ण

	/* track the change in the OGMपूर्णांकerval list */
	list_add_tail(&tt_change_node->list, &bat_priv->tt.changes_list);

unlock:
	spin_unlock_bh(&bat_priv->tt.changes_list_lock);

	अगर (event_हटाओd)
		atomic_dec(&bat_priv->tt.local_changes);
	अन्यथा
		atomic_inc(&bat_priv->tt.local_changes);
पूर्ण

/**
 * batadv_tt_len() - compute length in bytes of given number of tt changes
 * @changes_num: number of tt changes
 *
 * Return: computed length in bytes.
 */
अटल पूर्णांक batadv_tt_len(पूर्णांक changes_num)
अणु
	वापस changes_num * माप(काष्ठा batadv_tvlv_tt_change);
पूर्ण

/**
 * batadv_tt_entries() - compute the number of entries fitting in tt_len bytes
 * @tt_len: available space
 *
 * Return: the number of entries.
 */
अटल u16 batadv_tt_entries(u16 tt_len)
अणु
	वापस tt_len / batadv_tt_len(1);
पूर्ण

/**
 * batadv_tt_local_table_transmit_size() - calculates the local translation
 *  table size when transmitted over the air
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: local translation table size in bytes.
 */
अटल पूर्णांक batadv_tt_local_table_transmit_size(काष्ठा batadv_priv *bat_priv)
अणु
	u16 num_vlan = 0;
	u16 tt_local_entries = 0;
	काष्ठा batadv_softअगर_vlan *vlan;
	पूर्णांक hdr_size;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(vlan, &bat_priv->softअगर_vlan_list, list) अणु
		num_vlan++;
		tt_local_entries += atomic_पढ़ो(&vlan->tt.num_entries);
	पूर्ण
	rcu_पढ़ो_unlock();

	/* header size of tvlv encapsulated tt response payload */
	hdr_size = माप(काष्ठा batadv_unicast_tvlv_packet);
	hdr_size += माप(काष्ठा batadv_tvlv_hdr);
	hdr_size += माप(काष्ठा batadv_tvlv_tt_data);
	hdr_size += num_vlan * माप(काष्ठा batadv_tvlv_tt_vlan_data);

	वापस hdr_size + batadv_tt_len(tt_local_entries);
पूर्ण

अटल पूर्णांक batadv_tt_local_init(काष्ठा batadv_priv *bat_priv)
अणु
	अगर (bat_priv->tt.local_hash)
		वापस 0;

	bat_priv->tt.local_hash = batadv_hash_new(1024);

	अगर (!bat_priv->tt.local_hash)
		वापस -ENOMEM;

	batadv_hash_set_lock_class(bat_priv->tt.local_hash,
				   &batadv_tt_local_hash_lock_class_key);

	वापस 0;
पूर्ण

अटल व्योम batadv_tt_global_मुक्त(काष्ठा batadv_priv *bat_priv,
				  काष्ठा batadv_tt_global_entry *tt_global,
				  स्थिर अक्षर *message)
अणु
	काष्ठा batadv_tt_global_entry *tt_हटाओd_entry;
	काष्ठा hlist_node *tt_हटाओd_node;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Deleting global tt entry %pM (vid: %d): %s\n",
		   tt_global->common.addr,
		   batadv_prपूर्णांक_vid(tt_global->common.vid), message);

	tt_हटाओd_node = batadv_hash_हटाओ(bat_priv->tt.global_hash,
					     batadv_compare_tt,
					     batadv_choose_tt,
					     &tt_global->common);
	अगर (!tt_हटाओd_node)
		वापस;

	/* drop reference of हटाओ hash entry */
	tt_हटाओd_entry = hlist_entry(tt_हटाओd_node,
				       काष्ठा batadv_tt_global_entry,
				       common.hash_entry);
	batadv_tt_global_entry_put(tt_हटाओd_entry);
पूर्ण

/**
 * batadv_tt_local_add() - add a new client to the local table or update an
 *  existing client
 * @soft_अगरace: netdev काष्ठा of the mesh पूर्णांकerface
 * @addr: the mac address of the client to add
 * @vid: VLAN identअगरier
 * @अगरindex: index of the पूर्णांकerface where the client is connected to (useful to
 *  identअगरy wireless clients)
 * @mark: the value contained in the skb->mark field of the received packet (अगर
 *  any)
 *
 * Return: true अगर the client was successfully added, false otherwise.
 */
bool batadv_tt_local_add(काष्ठा net_device *soft_अगरace, स्थिर u8 *addr,
			 अचिन्हित लघु vid, पूर्णांक अगरindex, u32 mark)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(soft_अगरace);
	काष्ठा batadv_tt_local_entry *tt_local;
	काष्ठा batadv_tt_global_entry *tt_global = शून्य;
	काष्ठा net *net = dev_net(soft_अगरace);
	काष्ठा batadv_softअगर_vlan *vlan;
	काष्ठा net_device *in_dev = शून्य;
	काष्ठा batadv_hard_अगरace *in_hardअगर = शून्य;
	काष्ठा hlist_head *head;
	काष्ठा batadv_tt_orig_list_entry *orig_entry;
	पूर्णांक hash_added, table_size, packet_size_max;
	bool ret = false;
	bool roamed_back = false;
	u8 remote_flags;
	u32 match_mark;

	अगर (अगरindex != BATADV_शून्य_IFINDEX)
		in_dev = dev_get_by_index(net, अगरindex);

	अगर (in_dev)
		in_hardअगर = batadv_hardअगर_get_by_netdev(in_dev);

	tt_local = batadv_tt_local_hash_find(bat_priv, addr, vid);

	अगर (!is_multicast_ether_addr(addr))
		tt_global = batadv_tt_global_hash_find(bat_priv, addr, vid);

	अगर (tt_local) अणु
		tt_local->last_seen = jअगरfies;
		अगर (tt_local->common.flags & BATADV_TT_CLIENT_PENDING) अणु
			batadv_dbg(BATADV_DBG_TT, bat_priv,
				   "Re-adding pending client %pM (vid: %d)\n",
				   addr, batadv_prपूर्णांक_vid(vid));
			/* whatever the reason why the PENDING flag was set,
			 * this is a client which was enqueued to be हटाओd in
			 * this orig_पूर्णांकerval. Since it popped up again, the
			 * flag can be reset like it was never enqueued
			 */
			tt_local->common.flags &= ~BATADV_TT_CLIENT_PENDING;
			जाओ add_event;
		पूर्ण

		अगर (tt_local->common.flags & BATADV_TT_CLIENT_ROAM) अणु
			batadv_dbg(BATADV_DBG_TT, bat_priv,
				   "Roaming client %pM (vid: %d) came back to its original location\n",
				   addr, batadv_prपूर्णांक_vid(vid));
			/* the ROAM flag is set because this client roamed away
			 * and the node got a roaming_advertisement message. Now
			 * that the client popped up again at its original
			 * location such flag can be unset
			 */
			tt_local->common.flags &= ~BATADV_TT_CLIENT_ROAM;
			roamed_back = true;
		पूर्ण
		जाओ check_roaming;
	पूर्ण

	/* Ignore the client अगर we cannot send it in a full table response. */
	table_size = batadv_tt_local_table_transmit_size(bat_priv);
	table_size += batadv_tt_len(1);
	packet_size_max = atomic_पढ़ो(&bat_priv->packet_size_max);
	अगर (table_size > packet_size_max) अणु
		net_ratelimited_function(batadv_info, soft_अगरace,
					 "Local translation table size (%i) exceeds maximum packet size (%i); Ignoring new local tt entry: %pM\n",
					 table_size, packet_size_max, addr);
		जाओ out;
	पूर्ण

	tt_local = kmem_cache_alloc(batadv_tl_cache, GFP_ATOMIC);
	अगर (!tt_local)
		जाओ out;

	/* increase the refcounter of the related vlan */
	vlan = batadv_softअगर_vlan_get(bat_priv, vid);
	अगर (!vlan) अणु
		net_ratelimited_function(batadv_info, soft_अगरace,
					 "adding TT local entry %pM to non-existent VLAN %d\n",
					 addr, batadv_prपूर्णांक_vid(vid));
		kmem_cache_मुक्त(batadv_tl_cache, tt_local);
		tt_local = शून्य;
		जाओ out;
	पूर्ण

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Creating new local tt entry: %pM (vid: %d, ttvn: %d)\n",
		   addr, batadv_prपूर्णांक_vid(vid),
		   (u8)atomic_पढ़ो(&bat_priv->tt.vn));

	ether_addr_copy(tt_local->common.addr, addr);
	/* The local entry has to be marked as NEW to aव्योम to send it in
	 * a full table response going out beक्रमe the next ttvn increment
	 * (consistency check)
	 */
	tt_local->common.flags = BATADV_TT_CLIENT_NEW;
	tt_local->common.vid = vid;
	अगर (batadv_is_wअगरi_hardअगर(in_hardअगर))
		tt_local->common.flags |= BATADV_TT_CLIENT_WIFI;
	kref_init(&tt_local->common.refcount);
	tt_local->last_seen = jअगरfies;
	tt_local->common.added_at = tt_local->last_seen;
	tt_local->vlan = vlan;

	/* the baपंचांगan पूर्णांकerface mac and multicast addresses should never be
	 * purged
	 */
	अगर (batadv_compare_eth(addr, soft_अगरace->dev_addr) ||
	    is_multicast_ether_addr(addr))
		tt_local->common.flags |= BATADV_TT_CLIENT_NOPURGE;

	kref_get(&tt_local->common.refcount);
	hash_added = batadv_hash_add(bat_priv->tt.local_hash, batadv_compare_tt,
				     batadv_choose_tt, &tt_local->common,
				     &tt_local->common.hash_entry);

	अगर (unlikely(hash_added != 0)) अणु
		/* हटाओ the reference क्रम the hash */
		batadv_tt_local_entry_put(tt_local);
		जाओ out;
	पूर्ण

add_event:
	batadv_tt_local_event(bat_priv, tt_local, BATADV_NO_FLAGS);

check_roaming:
	/* Check whether it is a roaming, but करोn't करो anything अगर the roaming
	 * process has alपढ़ोy been handled
	 */
	अगर (tt_global && !(tt_global->common.flags & BATADV_TT_CLIENT_ROAM)) अणु
		/* These node are probably going to update their tt table */
		head = &tt_global->orig_list;
		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(orig_entry, head, list) अणु
			batadv_send_roam_adv(bat_priv, tt_global->common.addr,
					     tt_global->common.vid,
					     orig_entry->orig_node);
		पूर्ण
		rcu_पढ़ो_unlock();
		अगर (roamed_back) अणु
			batadv_tt_global_मुक्त(bat_priv, tt_global,
					      "Roaming canceled");
			tt_global = शून्य;
		पूर्ण अन्यथा अणु
			/* The global entry has to be marked as ROAMING and
			 * has to be kept क्रम consistency purpose
			 */
			tt_global->common.flags |= BATADV_TT_CLIENT_ROAM;
			tt_global->roam_at = jअगरfies;
		पूर्ण
	पूर्ण

	/* store the current remote flags beक्रमe altering them. This helps
	 * understanding is flags are changing or not
	 */
	remote_flags = tt_local->common.flags & BATADV_TT_REMOTE_MASK;

	अगर (batadv_is_wअगरi_hardअगर(in_hardअगर))
		tt_local->common.flags |= BATADV_TT_CLIENT_WIFI;
	अन्यथा
		tt_local->common.flags &= ~BATADV_TT_CLIENT_WIFI;

	/* check the mark in the skb: अगर it's equal to the configured
	 * isolation_mark, it means the packet is coming from an isolated
	 * non-mesh client
	 */
	match_mark = (mark & bat_priv->isolation_mark_mask);
	अगर (bat_priv->isolation_mark_mask &&
	    match_mark == bat_priv->isolation_mark)
		tt_local->common.flags |= BATADV_TT_CLIENT_ISOLA;
	अन्यथा
		tt_local->common.flags &= ~BATADV_TT_CLIENT_ISOLA;

	/* अगर any "dynamic" flag has been modअगरied, resend an ADD event क्रम this
	 * entry so that all the nodes can get the new flags
	 */
	अगर (remote_flags ^ (tt_local->common.flags & BATADV_TT_REMOTE_MASK))
		batadv_tt_local_event(bat_priv, tt_local, BATADV_NO_FLAGS);

	ret = true;
out:
	अगर (in_hardअगर)
		batadv_hardअगर_put(in_hardअगर);
	अगर (in_dev)
		dev_put(in_dev);
	अगर (tt_local)
		batadv_tt_local_entry_put(tt_local);
	अगर (tt_global)
		batadv_tt_global_entry_put(tt_global);
	वापस ret;
पूर्ण

/**
 * batadv_tt_prepare_tvlv_global_data() - prepare the TVLV TT header to send
 *  within a TT Response directed to another node
 * @orig_node: originator क्रम which the TT data has to be prepared
 * @tt_data: uninitialised poपूर्णांकer to the address of the TVLV buffer
 * @tt_change: uninitialised poपूर्णांकer to the address of the area where the TT
 *  changed can be stored
 * @tt_len: poपूर्णांकer to the length to reserve to the tt_change. अगर -1 this
 *  function reserves the amount of space needed to send the entire global TT
 *  table. In हाल of success the value is updated with the real amount of
 *  reserved bytes
 * Allocate the needed amount of memory क्रम the entire TT TVLV and ग_लिखो its
 * header made up of one tvlv_tt_data object and a series of tvlv_tt_vlan_data
 * objects, one per active VLAN served by the originator node.
 *
 * Return: the size of the allocated buffer or 0 in हाल of failure.
 */
अटल u16
batadv_tt_prepare_tvlv_global_data(काष्ठा batadv_orig_node *orig_node,
				   काष्ठा batadv_tvlv_tt_data **tt_data,
				   काष्ठा batadv_tvlv_tt_change **tt_change,
				   s32 *tt_len)
अणु
	u16 num_vlan = 0;
	u16 num_entries = 0;
	u16 change_offset;
	u16 tvlv_len;
	काष्ठा batadv_tvlv_tt_vlan_data *tt_vlan;
	काष्ठा batadv_orig_node_vlan *vlan;
	u8 *tt_change_ptr;

	spin_lock_bh(&orig_node->vlan_list_lock);
	hlist_क्रम_each_entry(vlan, &orig_node->vlan_list, list) अणु
		num_vlan++;
		num_entries += atomic_पढ़ो(&vlan->tt.num_entries);
	पूर्ण

	change_offset = माप(**tt_data);
	change_offset += num_vlan * माप(*tt_vlan);

	/* अगर tt_len is negative, allocate the space needed by the full table */
	अगर (*tt_len < 0)
		*tt_len = batadv_tt_len(num_entries);

	tvlv_len = *tt_len;
	tvlv_len += change_offset;

	*tt_data = kदो_स्मृति(tvlv_len, GFP_ATOMIC);
	अगर (!*tt_data) अणु
		*tt_len = 0;
		जाओ out;
	पूर्ण

	(*tt_data)->flags = BATADV_NO_FLAGS;
	(*tt_data)->ttvn = atomic_पढ़ो(&orig_node->last_ttvn);
	(*tt_data)->num_vlan = htons(num_vlan);

	tt_vlan = (काष्ठा batadv_tvlv_tt_vlan_data *)(*tt_data + 1);
	hlist_क्रम_each_entry(vlan, &orig_node->vlan_list, list) अणु
		tt_vlan->vid = htons(vlan->vid);
		tt_vlan->crc = htonl(vlan->tt.crc);
		tt_vlan->reserved = 0;

		tt_vlan++;
	पूर्ण

	tt_change_ptr = (u8 *)*tt_data + change_offset;
	*tt_change = (काष्ठा batadv_tvlv_tt_change *)tt_change_ptr;

out:
	spin_unlock_bh(&orig_node->vlan_list_lock);
	वापस tvlv_len;
पूर्ण

/**
 * batadv_tt_prepare_tvlv_local_data() - allocate and prepare the TT TVLV क्रम
 *  this node
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @tt_data: uninitialised poपूर्णांकer to the address of the TVLV buffer
 * @tt_change: uninitialised poपूर्णांकer to the address of the area where the TT
 *  changes can be stored
 * @tt_len: poपूर्णांकer to the length to reserve to the tt_change. अगर -1 this
 *  function reserves the amount of space needed to send the entire local TT
 *  table. In हाल of success the value is updated with the real amount of
 *  reserved bytes
 *
 * Allocate the needed amount of memory क्रम the entire TT TVLV and ग_लिखो its
 * header made up by one tvlv_tt_data object and a series of tvlv_tt_vlan_data
 * objects, one per active VLAN.
 *
 * Return: the size of the allocated buffer or 0 in हाल of failure.
 */
अटल u16
batadv_tt_prepare_tvlv_local_data(काष्ठा batadv_priv *bat_priv,
				  काष्ठा batadv_tvlv_tt_data **tt_data,
				  काष्ठा batadv_tvlv_tt_change **tt_change,
				  s32 *tt_len)
अणु
	काष्ठा batadv_tvlv_tt_vlan_data *tt_vlan;
	काष्ठा batadv_softअगर_vlan *vlan;
	u16 num_vlan = 0;
	u16 vlan_entries = 0;
	u16 total_entries = 0;
	u16 tvlv_len;
	u8 *tt_change_ptr;
	पूर्णांक change_offset;

	spin_lock_bh(&bat_priv->softअगर_vlan_list_lock);
	hlist_क्रम_each_entry(vlan, &bat_priv->softअगर_vlan_list, list) अणु
		vlan_entries = atomic_पढ़ो(&vlan->tt.num_entries);
		अगर (vlan_entries < 1)
			जारी;

		num_vlan++;
		total_entries += vlan_entries;
	पूर्ण

	change_offset = माप(**tt_data);
	change_offset += num_vlan * माप(*tt_vlan);

	/* अगर tt_len is negative, allocate the space needed by the full table */
	अगर (*tt_len < 0)
		*tt_len = batadv_tt_len(total_entries);

	tvlv_len = *tt_len;
	tvlv_len += change_offset;

	*tt_data = kदो_स्मृति(tvlv_len, GFP_ATOMIC);
	अगर (!*tt_data) अणु
		tvlv_len = 0;
		जाओ out;
	पूर्ण

	(*tt_data)->flags = BATADV_NO_FLAGS;
	(*tt_data)->ttvn = atomic_पढ़ो(&bat_priv->tt.vn);
	(*tt_data)->num_vlan = htons(num_vlan);

	tt_vlan = (काष्ठा batadv_tvlv_tt_vlan_data *)(*tt_data + 1);
	hlist_क्रम_each_entry(vlan, &bat_priv->softअगर_vlan_list, list) अणु
		vlan_entries = atomic_पढ़ो(&vlan->tt.num_entries);
		अगर (vlan_entries < 1)
			जारी;

		tt_vlan->vid = htons(vlan->vid);
		tt_vlan->crc = htonl(vlan->tt.crc);
		tt_vlan->reserved = 0;

		tt_vlan++;
	पूर्ण

	tt_change_ptr = (u8 *)*tt_data + change_offset;
	*tt_change = (काष्ठा batadv_tvlv_tt_change *)tt_change_ptr;

out:
	spin_unlock_bh(&bat_priv->softअगर_vlan_list_lock);
	वापस tvlv_len;
पूर्ण

/**
 * batadv_tt_tvlv_container_update() - update the translation table tvlv
 *  container after local tt changes have been committed
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_tt_tvlv_container_update(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_tt_change_node *entry, *safe;
	काष्ठा batadv_tvlv_tt_data *tt_data;
	काष्ठा batadv_tvlv_tt_change *tt_change;
	पूर्णांक tt_dअगरf_len, tt_change_len = 0;
	पूर्णांक tt_dअगरf_entries_num = 0;
	पूर्णांक tt_dअगरf_entries_count = 0;
	u16 tvlv_len;

	tt_dअगरf_entries_num = atomic_पढ़ो(&bat_priv->tt.local_changes);
	tt_dअगरf_len = batadv_tt_len(tt_dअगरf_entries_num);

	/* अगर we have too many changes क्रम one packet करोn't send any
	 * and रुको क्रम the tt table request which will be fragmented
	 */
	अगर (tt_dअगरf_len > bat_priv->soft_अगरace->mtu)
		tt_dअगरf_len = 0;

	tvlv_len = batadv_tt_prepare_tvlv_local_data(bat_priv, &tt_data,
						     &tt_change, &tt_dअगरf_len);
	अगर (!tvlv_len)
		वापस;

	tt_data->flags = BATADV_TT_OGM_DIFF;

	अगर (tt_dअगरf_len == 0)
		जाओ container_रेजिस्टर;

	spin_lock_bh(&bat_priv->tt.changes_list_lock);
	atomic_set(&bat_priv->tt.local_changes, 0);

	list_क्रम_each_entry_safe(entry, safe, &bat_priv->tt.changes_list,
				 list) अणु
		अगर (tt_dअगरf_entries_count < tt_dअगरf_entries_num) अणु
			स_नकल(tt_change + tt_dअगरf_entries_count,
			       &entry->change,
			       माप(काष्ठा batadv_tvlv_tt_change));
			tt_dअगरf_entries_count++;
		पूर्ण
		list_del(&entry->list);
		kmem_cache_मुक्त(batadv_tt_change_cache, entry);
	पूर्ण
	spin_unlock_bh(&bat_priv->tt.changes_list_lock);

	/* Keep the buffer क्रम possible tt_request */
	spin_lock_bh(&bat_priv->tt.last_changeset_lock);
	kमुक्त(bat_priv->tt.last_changeset);
	bat_priv->tt.last_changeset_len = 0;
	bat_priv->tt.last_changeset = शून्य;
	tt_change_len = batadv_tt_len(tt_dअगरf_entries_count);
	/* check whether this new OGM has no changes due to size problems */
	अगर (tt_dअगरf_entries_count > 0) अणु
		/* अगर kदो_स्मृति() fails we will reply with the full table
		 * instead of providing the dअगरf
		 */
		bat_priv->tt.last_changeset = kzalloc(tt_dअगरf_len, GFP_ATOMIC);
		अगर (bat_priv->tt.last_changeset) अणु
			स_नकल(bat_priv->tt.last_changeset,
			       tt_change, tt_change_len);
			bat_priv->tt.last_changeset_len = tt_dअगरf_len;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&bat_priv->tt.last_changeset_lock);

container_रेजिस्टर:
	batadv_tvlv_container_रेजिस्टर(bat_priv, BATADV_TVLV_TT, 1, tt_data,
				       tvlv_len);
	kमुक्त(tt_data);
पूर्ण

/**
 * batadv_tt_local_dump_entry() - Dump one TT local entry पूर्णांकo a message
 * @msg :Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @cb: Control block containing additional options
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @common: tt local & tt global common data
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_tt_local_dump_entry(काष्ठा sk_buff *msg, u32 portid,
			   काष्ठा netlink_callback *cb,
			   काष्ठा batadv_priv *bat_priv,
			   काष्ठा batadv_tt_common_entry *common)
अणु
	व्योम *hdr;
	काष्ठा batadv_softअगर_vlan *vlan;
	काष्ठा batadv_tt_local_entry *local;
	अचिन्हित पूर्णांक last_seen_msecs;
	u32 crc;

	local = container_of(common, काष्ठा batadv_tt_local_entry, common);
	last_seen_msecs = jअगरfies_to_msecs(jअगरfies - local->last_seen);

	vlan = batadv_softअगर_vlan_get(bat_priv, common->vid);
	अगर (!vlan)
		वापस 0;

	crc = vlan->tt.crc;

	batadv_softअगर_vlan_put(vlan);

	hdr = genlmsg_put(msg, portid, cb->nlh->nlmsg_seq,
			  &batadv_netlink_family,  NLM_F_MULTI,
			  BATADV_CMD_GET_TRANSTABLE_LOCAL);
	अगर (!hdr)
		वापस -ENOBUFS;

	genl_dump_check_consistent(cb, hdr);

	अगर (nla_put(msg, BATADV_ATTR_TT_ADDRESS, ETH_ALEN, common->addr) ||
	    nla_put_u32(msg, BATADV_ATTR_TT_CRC32, crc) ||
	    nla_put_u16(msg, BATADV_ATTR_TT_VID, common->vid) ||
	    nla_put_u32(msg, BATADV_ATTR_TT_FLAGS, common->flags))
		जाओ nla_put_failure;

	अगर (!(common->flags & BATADV_TT_CLIENT_NOPURGE) &&
	    nla_put_u32(msg, BATADV_ATTR_LAST_SEEN_MSECS, last_seen_msecs))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

/**
 * batadv_tt_local_dump_bucket() - Dump one TT local bucket पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @cb: Control block containing additional options
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @hash: hash to dump
 * @bucket: bucket index to dump
 * @idx_s: Number of entries to skip
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_tt_local_dump_bucket(काष्ठा sk_buff *msg, u32 portid,
			    काष्ठा netlink_callback *cb,
			    काष्ठा batadv_priv *bat_priv,
			    काष्ठा batadv_hashtable *hash, अचिन्हित पूर्णांक bucket,
			    पूर्णांक *idx_s)
अणु
	काष्ठा batadv_tt_common_entry *common;
	पूर्णांक idx = 0;

	spin_lock_bh(&hash->list_locks[bucket]);
	cb->seq = atomic_पढ़ो(&hash->generation) << 1 | 1;

	hlist_क्रम_each_entry(common, &hash->table[bucket], hash_entry) अणु
		अगर (idx++ < *idx_s)
			जारी;

		अगर (batadv_tt_local_dump_entry(msg, portid, cb, bat_priv,
					       common)) अणु
			spin_unlock_bh(&hash->list_locks[bucket]);
			*idx_s = idx - 1;
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&hash->list_locks[bucket]);

	*idx_s = 0;
	वापस 0;
पूर्ण

/**
 * batadv_tt_local_dump() - Dump TT local entries पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @cb: Parameters from query
 *
 * Return: Error code, or 0 on success
 */
पूर्णांक batadv_tt_local_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(cb->skb->sk);
	काष्ठा net_device *soft_अगरace;
	काष्ठा batadv_priv *bat_priv;
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	काष्ठा batadv_hashtable *hash;
	पूर्णांक ret;
	पूर्णांक अगरindex;
	पूर्णांक bucket = cb->args[0];
	पूर्णांक idx = cb->args[1];
	पूर्णांक portid = NETLINK_CB(cb->skb).portid;

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

	hash = bat_priv->tt.local_hash;

	जबतक (bucket < hash->size) अणु
		अगर (batadv_tt_local_dump_bucket(msg, portid, cb, bat_priv,
						hash, bucket, &idx))
			अवरोध;

		bucket++;
	पूर्ण

	ret = msg->len;

 out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	अगर (soft_अगरace)
		dev_put(soft_अगरace);

	cb->args[0] = bucket;
	cb->args[1] = idx;

	वापस ret;
पूर्ण

अटल व्योम
batadv_tt_local_set_pending(काष्ठा batadv_priv *bat_priv,
			    काष्ठा batadv_tt_local_entry *tt_local_entry,
			    u16 flags, स्थिर अक्षर *message)
अणु
	batadv_tt_local_event(bat_priv, tt_local_entry, flags);

	/* The local client has to be marked as "pending to be removed" but has
	 * to be kept in the table in order to send it in a full table
	 * response issued beक्रमe the net ttvn increment (consistency check)
	 */
	tt_local_entry->common.flags |= BATADV_TT_CLIENT_PENDING;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Local tt entry (%pM, vid: %d) pending to be removed: %s\n",
		   tt_local_entry->common.addr,
		   batadv_prपूर्णांक_vid(tt_local_entry->common.vid), message);
पूर्ण

/**
 * batadv_tt_local_हटाओ() - logically हटाओ an entry from the local table
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: the MAC address of the client to हटाओ
 * @vid: VLAN identअगरier
 * @message: message to append to the log on deletion
 * @roaming: true अगर the deletion is due to a roaming event
 *
 * Return: the flags asचिन्हित to the local entry beक्रमe being deleted
 */
u16 batadv_tt_local_हटाओ(काष्ठा batadv_priv *bat_priv, स्थिर u8 *addr,
			   अचिन्हित लघु vid, स्थिर अक्षर *message,
			   bool roaming)
अणु
	काष्ठा batadv_tt_local_entry *tt_हटाओd_entry;
	काष्ठा batadv_tt_local_entry *tt_local_entry;
	u16 flags, curr_flags = BATADV_NO_FLAGS;
	काष्ठा hlist_node *tt_हटाओd_node;

	tt_local_entry = batadv_tt_local_hash_find(bat_priv, addr, vid);
	अगर (!tt_local_entry)
		जाओ out;

	curr_flags = tt_local_entry->common.flags;

	flags = BATADV_TT_CLIENT_DEL;
	/* अगर this global entry addition is due to a roaming, the node has to
	 * mark the local entry as "roamed" in order to correctly reroute
	 * packets later
	 */
	अगर (roaming) अणु
		flags |= BATADV_TT_CLIENT_ROAM;
		/* mark the local client as ROAMed */
		tt_local_entry->common.flags |= BATADV_TT_CLIENT_ROAM;
	पूर्ण

	अगर (!(tt_local_entry->common.flags & BATADV_TT_CLIENT_NEW)) अणु
		batadv_tt_local_set_pending(bat_priv, tt_local_entry, flags,
					    message);
		जाओ out;
	पूर्ण
	/* अगर this client has been added right now, it is possible to
	 * immediately purge it
	 */
	batadv_tt_local_event(bat_priv, tt_local_entry, BATADV_TT_CLIENT_DEL);

	tt_हटाओd_node = batadv_hash_हटाओ(bat_priv->tt.local_hash,
					     batadv_compare_tt,
					     batadv_choose_tt,
					     &tt_local_entry->common);
	अगर (!tt_हटाओd_node)
		जाओ out;

	/* drop reference of हटाओ hash entry */
	tt_हटाओd_entry = hlist_entry(tt_हटाओd_node,
				       काष्ठा batadv_tt_local_entry,
				       common.hash_entry);
	batadv_tt_local_entry_put(tt_हटाओd_entry);

out:
	अगर (tt_local_entry)
		batadv_tt_local_entry_put(tt_local_entry);

	वापस curr_flags;
पूर्ण

/**
 * batadv_tt_local_purge_list() - purge inactive tt local entries
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @head: poपूर्णांकer to the list containing the local tt entries
 * @समयout: parameter deciding whether a given tt local entry is considered
 *  inactive or not
 */
अटल व्योम batadv_tt_local_purge_list(काष्ठा batadv_priv *bat_priv,
				       काष्ठा hlist_head *head,
				       पूर्णांक समयout)
अणु
	काष्ठा batadv_tt_local_entry *tt_local_entry;
	काष्ठा batadv_tt_common_entry *tt_common_entry;
	काष्ठा hlist_node *node_पंचांगp;

	hlist_क्रम_each_entry_safe(tt_common_entry, node_पंचांगp, head,
				  hash_entry) अणु
		tt_local_entry = container_of(tt_common_entry,
					      काष्ठा batadv_tt_local_entry,
					      common);
		अगर (tt_local_entry->common.flags & BATADV_TT_CLIENT_NOPURGE)
			जारी;

		/* entry alपढ़ोy marked क्रम deletion */
		अगर (tt_local_entry->common.flags & BATADV_TT_CLIENT_PENDING)
			जारी;

		अगर (!batadv_has_समयd_out(tt_local_entry->last_seen, समयout))
			जारी;

		batadv_tt_local_set_pending(bat_priv, tt_local_entry,
					    BATADV_TT_CLIENT_DEL, "timed out");
	पूर्ण
पूर्ण

/**
 * batadv_tt_local_purge() - purge inactive tt local entries
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @समयout: parameter deciding whether a given tt local entry is considered
 *  inactive or not
 */
अटल व्योम batadv_tt_local_purge(काष्ठा batadv_priv *bat_priv,
				  पूर्णांक समयout)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->tt.local_hash;
	काष्ठा hlist_head *head;
	spinlock_t *list_lock; /* protects ग_लिखो access to the hash lists */
	u32 i;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];
		list_lock = &hash->list_locks[i];

		spin_lock_bh(list_lock);
		batadv_tt_local_purge_list(bat_priv, head, समयout);
		spin_unlock_bh(list_lock);
	पूर्ण
पूर्ण

अटल व्योम batadv_tt_local_table_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_hashtable *hash;
	spinlock_t *list_lock; /* protects ग_लिखो access to the hash lists */
	काष्ठा batadv_tt_common_entry *tt_common_entry;
	काष्ठा batadv_tt_local_entry *tt_local;
	काष्ठा hlist_node *node_पंचांगp;
	काष्ठा hlist_head *head;
	u32 i;

	अगर (!bat_priv->tt.local_hash)
		वापस;

	hash = bat_priv->tt.local_hash;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];
		list_lock = &hash->list_locks[i];

		spin_lock_bh(list_lock);
		hlist_क्रम_each_entry_safe(tt_common_entry, node_पंचांगp,
					  head, hash_entry) अणु
			hlist_del_rcu(&tt_common_entry->hash_entry);
			tt_local = container_of(tt_common_entry,
						काष्ठा batadv_tt_local_entry,
						common);

			batadv_tt_local_entry_put(tt_local);
		पूर्ण
		spin_unlock_bh(list_lock);
	पूर्ण

	batadv_hash_destroy(hash);

	bat_priv->tt.local_hash = शून्य;
पूर्ण

अटल पूर्णांक batadv_tt_global_init(काष्ठा batadv_priv *bat_priv)
अणु
	अगर (bat_priv->tt.global_hash)
		वापस 0;

	bat_priv->tt.global_hash = batadv_hash_new(1024);

	अगर (!bat_priv->tt.global_hash)
		वापस -ENOMEM;

	batadv_hash_set_lock_class(bat_priv->tt.global_hash,
				   &batadv_tt_global_hash_lock_class_key);

	वापस 0;
पूर्ण

अटल व्योम batadv_tt_changes_list_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_tt_change_node *entry, *safe;

	spin_lock_bh(&bat_priv->tt.changes_list_lock);

	list_क्रम_each_entry_safe(entry, safe, &bat_priv->tt.changes_list,
				 list) अणु
		list_del(&entry->list);
		kmem_cache_मुक्त(batadv_tt_change_cache, entry);
	पूर्ण

	atomic_set(&bat_priv->tt.local_changes, 0);
	spin_unlock_bh(&bat_priv->tt.changes_list_lock);
पूर्ण

/**
 * batadv_tt_global_orig_entry_find() - find a TT orig_list_entry
 * @entry: the TT global entry where the orig_list_entry has to be
 *  extracted from
 * @orig_node: the originator क्रम which the orig_list_entry has to be found
 *
 * retrieve the orig_tt_list_entry beदीर्घing to orig_node from the
 * batadv_tt_global_entry list
 *
 * Return: it with an increased refcounter, शून्य अगर not found
 */
अटल काष्ठा batadv_tt_orig_list_entry *
batadv_tt_global_orig_entry_find(स्थिर काष्ठा batadv_tt_global_entry *entry,
				 स्थिर काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_tt_orig_list_entry *पंचांगp_orig_entry, *orig_entry = शून्य;
	स्थिर काष्ठा hlist_head *head;

	rcu_पढ़ो_lock();
	head = &entry->orig_list;
	hlist_क्रम_each_entry_rcu(पंचांगp_orig_entry, head, list) अणु
		अगर (पंचांगp_orig_entry->orig_node != orig_node)
			जारी;
		अगर (!kref_get_unless_zero(&पंचांगp_orig_entry->refcount))
			जारी;

		orig_entry = पंचांगp_orig_entry;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस orig_entry;
पूर्ण

/**
 * batadv_tt_global_entry_has_orig() - check अगर a TT global entry is also
 *  handled by a given originator
 * @entry: the TT global entry to check
 * @orig_node: the originator to search in the list
 * @flags: a poपूर्णांकer to store TT flags क्रम the given @entry received
 *  from @orig_node
 *
 * find out अगर an orig_node is alपढ़ोy in the list of a tt_global_entry.
 *
 * Return: true अगर found, false otherwise
 */
अटल bool
batadv_tt_global_entry_has_orig(स्थिर काष्ठा batadv_tt_global_entry *entry,
				स्थिर काष्ठा batadv_orig_node *orig_node,
				u8 *flags)
अणु
	काष्ठा batadv_tt_orig_list_entry *orig_entry;
	bool found = false;

	orig_entry = batadv_tt_global_orig_entry_find(entry, orig_node);
	अगर (orig_entry) अणु
		found = true;

		अगर (flags)
			*flags = orig_entry->flags;

		batadv_tt_orig_list_entry_put(orig_entry);
	पूर्ण

	वापस found;
पूर्ण

/**
 * batadv_tt_global_sync_flags() - update TT sync flags
 * @tt_global: the TT global entry to update sync flags in
 *
 * Updates the sync flag bits in the tt_global flag attribute with a logical
 * OR of all sync flags from any of its TT orig entries.
 */
अटल व्योम
batadv_tt_global_sync_flags(काष्ठा batadv_tt_global_entry *tt_global)
अणु
	काष्ठा batadv_tt_orig_list_entry *orig_entry;
	स्थिर काष्ठा hlist_head *head;
	u16 flags = BATADV_NO_FLAGS;

	rcu_पढ़ो_lock();
	head = &tt_global->orig_list;
	hlist_क्रम_each_entry_rcu(orig_entry, head, list)
		flags |= orig_entry->flags;
	rcu_पढ़ो_unlock();

	flags |= tt_global->common.flags & (~BATADV_TT_SYNC_MASK);
	tt_global->common.flags = flags;
पूर्ण

/**
 * batadv_tt_global_orig_entry_add() - add or update a TT orig entry
 * @tt_global: the TT global entry to add an orig entry in
 * @orig_node: the originator to add an orig entry क्रम
 * @ttvn: translation table version number of this changeset
 * @flags: TT sync flags
 */
अटल व्योम
batadv_tt_global_orig_entry_add(काष्ठा batadv_tt_global_entry *tt_global,
				काष्ठा batadv_orig_node *orig_node, पूर्णांक ttvn,
				u8 flags)
अणु
	काष्ठा batadv_tt_orig_list_entry *orig_entry;

	spin_lock_bh(&tt_global->list_lock);

	orig_entry = batadv_tt_global_orig_entry_find(tt_global, orig_node);
	अगर (orig_entry) अणु
		/* refresh the ttvn: the current value could be a bogus one that
		 * was added during a "temporary client detection"
		 */
		orig_entry->ttvn = ttvn;
		orig_entry->flags = flags;
		जाओ sync_flags;
	पूर्ण

	orig_entry = kmem_cache_zalloc(batadv_tt_orig_cache, GFP_ATOMIC);
	अगर (!orig_entry)
		जाओ out;

	INIT_HLIST_NODE(&orig_entry->list);
	kref_get(&orig_node->refcount);
	batadv_tt_global_size_inc(orig_node, tt_global->common.vid);
	orig_entry->orig_node = orig_node;
	orig_entry->ttvn = ttvn;
	orig_entry->flags = flags;
	kref_init(&orig_entry->refcount);

	kref_get(&orig_entry->refcount);
	hlist_add_head_rcu(&orig_entry->list,
			   &tt_global->orig_list);
	atomic_inc(&tt_global->orig_list_count);

sync_flags:
	batadv_tt_global_sync_flags(tt_global);
out:
	अगर (orig_entry)
		batadv_tt_orig_list_entry_put(orig_entry);

	spin_unlock_bh(&tt_global->list_lock);
पूर्ण

/**
 * batadv_tt_global_add() - add a new TT global entry or update an existing one
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: the originator announcing the client
 * @tt_addr: the mac address of the non-mesh client
 * @vid: VLAN identअगरier
 * @flags: TT flags that have to be set क्रम this non-mesh client
 * @ttvn: the tt version number ever announcing this non-mesh client
 *
 * Add a new TT global entry क्रम the given originator. If the entry alपढ़ोy
 * exists add a new reference to the given originator (a global entry can have
 * references to multiple originators) and adjust the flags attribute to reflect
 * the function argument.
 * If a TT local entry exists क्रम this non-mesh client हटाओ it.
 *
 * The caller must hold the orig_node refcount.
 *
 * Return: true अगर the new entry has been added, false otherwise
 */
अटल bool batadv_tt_global_add(काष्ठा batadv_priv *bat_priv,
				 काष्ठा batadv_orig_node *orig_node,
				 स्थिर अचिन्हित अक्षर *tt_addr,
				 अचिन्हित लघु vid, u16 flags, u8 ttvn)
अणु
	काष्ठा batadv_tt_global_entry *tt_global_entry;
	काष्ठा batadv_tt_local_entry *tt_local_entry;
	bool ret = false;
	पूर्णांक hash_added;
	काष्ठा batadv_tt_common_entry *common;
	u16 local_flags;

	/* ignore global entries from backbone nodes */
	अगर (batadv_bla_is_backbone_gw_orig(bat_priv, orig_node->orig, vid))
		वापस true;

	tt_global_entry = batadv_tt_global_hash_find(bat_priv, tt_addr, vid);
	tt_local_entry = batadv_tt_local_hash_find(bat_priv, tt_addr, vid);

	/* अगर the node alपढ़ोy has a local client क्रम this entry, it has to रुको
	 * क्रम a roaming advertisement instead of manually messing up the global
	 * table
	 */
	अगर ((flags & BATADV_TT_CLIENT_TEMP) && tt_local_entry &&
	    !(tt_local_entry->common.flags & BATADV_TT_CLIENT_NEW))
		जाओ out;

	अगर (!tt_global_entry) अणु
		tt_global_entry = kmem_cache_zalloc(batadv_tg_cache,
						    GFP_ATOMIC);
		अगर (!tt_global_entry)
			जाओ out;

		common = &tt_global_entry->common;
		ether_addr_copy(common->addr, tt_addr);
		common->vid = vid;

		अगर (!is_multicast_ether_addr(common->addr))
			common->flags = flags & (~BATADV_TT_SYNC_MASK);

		tt_global_entry->roam_at = 0;
		/* node must store current समय in हाल of roaming. This is
		 * needed to purge this entry out on समयout (अगर nobody claims
		 * it)
		 */
		अगर (flags & BATADV_TT_CLIENT_ROAM)
			tt_global_entry->roam_at = jअगरfies;
		kref_init(&common->refcount);
		common->added_at = jअगरfies;

		INIT_HLIST_HEAD(&tt_global_entry->orig_list);
		atomic_set(&tt_global_entry->orig_list_count, 0);
		spin_lock_init(&tt_global_entry->list_lock);

		kref_get(&common->refcount);
		hash_added = batadv_hash_add(bat_priv->tt.global_hash,
					     batadv_compare_tt,
					     batadv_choose_tt, common,
					     &common->hash_entry);

		अगर (unlikely(hash_added != 0)) अणु
			/* हटाओ the reference क्रम the hash */
			batadv_tt_global_entry_put(tt_global_entry);
			जाओ out_हटाओ;
		पूर्ण
	पूर्ण अन्यथा अणु
		common = &tt_global_entry->common;
		/* If there is alपढ़ोy a global entry, we can use this one क्रम
		 * our processing.
		 * But अगर we are trying to add a temporary client then here are
		 * two options at this poपूर्णांक:
		 * 1) the global client is not a temporary client: the global
		 *    client has to be left as it is, temporary inक्रमmation
		 *    should never override any alपढ़ोy known client state
		 * 2) the global client is a temporary client: purge the
		 *    originator list and add the new one orig_entry
		 */
		अगर (flags & BATADV_TT_CLIENT_TEMP) अणु
			अगर (!(common->flags & BATADV_TT_CLIENT_TEMP))
				जाओ out;
			अगर (batadv_tt_global_entry_has_orig(tt_global_entry,
							    orig_node, शून्य))
				जाओ out_हटाओ;
			batadv_tt_global_del_orig_list(tt_global_entry);
			जाओ add_orig_entry;
		पूर्ण

		/* अगर the client was temporary added beक्रमe receiving the first
		 * OGM announcing it, we have to clear the TEMP flag. Also,
		 * हटाओ the previous temporary orig node and re-add it
		 * अगर required. If the orig entry changed, the new one which
		 * is a non-temporary entry is preferred.
		 */
		अगर (common->flags & BATADV_TT_CLIENT_TEMP) अणु
			batadv_tt_global_del_orig_list(tt_global_entry);
			common->flags &= ~BATADV_TT_CLIENT_TEMP;
		पूर्ण

		/* the change can carry possible "attribute" flags like the
		 * TT_CLIENT_TEMP, thereक्रमe they have to be copied in the
		 * client entry
		 */
		अगर (!is_multicast_ether_addr(common->addr))
			common->flags |= flags & (~BATADV_TT_SYNC_MASK);

		/* If there is the BATADV_TT_CLIENT_ROAM flag set, there is only
		 * one originator left in the list and we previously received a
		 * delete + roaming change क्रम this originator.
		 *
		 * We should first delete the old originator beक्रमe adding the
		 * new one.
		 */
		अगर (common->flags & BATADV_TT_CLIENT_ROAM) अणु
			batadv_tt_global_del_orig_list(tt_global_entry);
			common->flags &= ~BATADV_TT_CLIENT_ROAM;
			tt_global_entry->roam_at = 0;
		पूर्ण
	पूर्ण
add_orig_entry:
	/* add the new orig_entry (अगर needed) or update it */
	batadv_tt_global_orig_entry_add(tt_global_entry, orig_node, ttvn,
					flags & BATADV_TT_SYNC_MASK);

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Creating new global tt entry: %pM (vid: %d, via %pM)\n",
		   common->addr, batadv_prपूर्णांक_vid(common->vid),
		   orig_node->orig);
	ret = true;

out_हटाओ:
	/* Do not हटाओ multicast addresses from the local hash on
	 * global additions
	 */
	अगर (is_multicast_ether_addr(tt_addr))
		जाओ out;

	/* हटाओ address from local hash अगर present */
	local_flags = batadv_tt_local_हटाओ(bat_priv, tt_addr, vid,
					     "global tt received",
					     flags & BATADV_TT_CLIENT_ROAM);
	tt_global_entry->common.flags |= local_flags & BATADV_TT_CLIENT_WIFI;

	अगर (!(flags & BATADV_TT_CLIENT_ROAM))
		/* this is a normal global add. Thereक्रमe the client is not in a
		 * roaming state anymore.
		 */
		tt_global_entry->common.flags &= ~BATADV_TT_CLIENT_ROAM;

out:
	अगर (tt_global_entry)
		batadv_tt_global_entry_put(tt_global_entry);
	अगर (tt_local_entry)
		batadv_tt_local_entry_put(tt_local_entry);
	वापस ret;
पूर्ण

/**
 * batadv_transtable_best_orig() - Get best originator list entry from tt entry
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @tt_global_entry: global translation table entry to be analyzed
 *
 * This function assumes the caller holds rcu_पढ़ो_lock().
 * Return: best originator list entry or शून्य on errors.
 */
अटल काष्ठा batadv_tt_orig_list_entry *
batadv_transtable_best_orig(काष्ठा batadv_priv *bat_priv,
			    काष्ठा batadv_tt_global_entry *tt_global_entry)
अणु
	काष्ठा batadv_neigh_node *router, *best_router = शून्य;
	काष्ठा batadv_algo_ops *bao = bat_priv->algo_ops;
	काष्ठा hlist_head *head;
	काष्ठा batadv_tt_orig_list_entry *orig_entry, *best_entry = शून्य;

	head = &tt_global_entry->orig_list;
	hlist_क्रम_each_entry_rcu(orig_entry, head, list) अणु
		router = batadv_orig_router_get(orig_entry->orig_node,
						BATADV_IF_DEFAULT);
		अगर (!router)
			जारी;

		अगर (best_router &&
		    bao->neigh.cmp(router, BATADV_IF_DEFAULT, best_router,
				   BATADV_IF_DEFAULT) <= 0) अणु
			batadv_neigh_node_put(router);
			जारी;
		पूर्ण

		/* release the refcount क्रम the "old" best */
		अगर (best_router)
			batadv_neigh_node_put(best_router);

		best_entry = orig_entry;
		best_router = router;
	पूर्ण

	अगर (best_router)
		batadv_neigh_node_put(best_router);

	वापस best_entry;
पूर्ण

/**
 * batadv_tt_global_dump_subentry() - Dump all TT local entries पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @seq: Sequence number of netlink message
 * @common: tt local & tt global common data
 * @orig: Originator node announcing a non-mesh client
 * @best: Is the best originator क्रम the TT entry
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_tt_global_dump_subentry(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			       काष्ठा batadv_tt_common_entry *common,
			       काष्ठा batadv_tt_orig_list_entry *orig,
			       bool best)
अणु
	u16 flags = (common->flags & (~BATADV_TT_SYNC_MASK)) | orig->flags;
	व्योम *hdr;
	काष्ठा batadv_orig_node_vlan *vlan;
	u8 last_ttvn;
	u32 crc;

	vlan = batadv_orig_node_vlan_get(orig->orig_node,
					 common->vid);
	अगर (!vlan)
		वापस 0;

	crc = vlan->tt.crc;

	batadv_orig_node_vlan_put(vlan);

	hdr = genlmsg_put(msg, portid, seq, &batadv_netlink_family,
			  NLM_F_MULTI,
			  BATADV_CMD_GET_TRANSTABLE_GLOBAL);
	अगर (!hdr)
		वापस -ENOBUFS;

	last_ttvn = atomic_पढ़ो(&orig->orig_node->last_ttvn);

	अगर (nla_put(msg, BATADV_ATTR_TT_ADDRESS, ETH_ALEN, common->addr) ||
	    nla_put(msg, BATADV_ATTR_ORIG_ADDRESS, ETH_ALEN,
		    orig->orig_node->orig) ||
	    nla_put_u8(msg, BATADV_ATTR_TT_TTVN, orig->ttvn) ||
	    nla_put_u8(msg, BATADV_ATTR_TT_LAST_TTVN, last_ttvn) ||
	    nla_put_u32(msg, BATADV_ATTR_TT_CRC32, crc) ||
	    nla_put_u16(msg, BATADV_ATTR_TT_VID, common->vid) ||
	    nla_put_u32(msg, BATADV_ATTR_TT_FLAGS, flags))
		जाओ nla_put_failure;

	अगर (best && nla_put_flag(msg, BATADV_ATTR_FLAG_BEST))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

/**
 * batadv_tt_global_dump_entry() - Dump one TT global entry पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @seq: Sequence number of netlink message
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @common: tt local & tt global common data
 * @sub_s: Number of entries to skip
 *
 * This function assumes the caller holds rcu_पढ़ो_lock().
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_tt_global_dump_entry(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			    काष्ठा batadv_priv *bat_priv,
			    काष्ठा batadv_tt_common_entry *common, पूर्णांक *sub_s)
अणु
	काष्ठा batadv_tt_orig_list_entry *orig_entry, *best_entry;
	काष्ठा batadv_tt_global_entry *global;
	काष्ठा hlist_head *head;
	पूर्णांक sub = 0;
	bool best;

	global = container_of(common, काष्ठा batadv_tt_global_entry, common);
	best_entry = batadv_transtable_best_orig(bat_priv, global);
	head = &global->orig_list;

	hlist_क्रम_each_entry_rcu(orig_entry, head, list) अणु
		अगर (sub++ < *sub_s)
			जारी;

		best = (orig_entry == best_entry);

		अगर (batadv_tt_global_dump_subentry(msg, portid, seq, common,
						   orig_entry, best)) अणु
			*sub_s = sub - 1;
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण

	*sub_s = 0;
	वापस 0;
पूर्ण

/**
 * batadv_tt_global_dump_bucket() - Dump one TT local bucket पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @portid: Port making netlink request
 * @seq: Sequence number of netlink message
 * @bat_priv: The bat priv with all the soft पूर्णांकerface inक्रमmation
 * @head: Poपूर्णांकer to the list containing the global tt entries
 * @idx_s: Number of entries to skip
 * @sub: Number of entries to skip
 *
 * Return: Error code, or 0 on success
 */
अटल पूर्णांक
batadv_tt_global_dump_bucket(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			     काष्ठा batadv_priv *bat_priv,
			     काष्ठा hlist_head *head, पूर्णांक *idx_s, पूर्णांक *sub)
अणु
	काष्ठा batadv_tt_common_entry *common;
	पूर्णांक idx = 0;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(common, head, hash_entry) अणु
		अगर (idx++ < *idx_s)
			जारी;

		अगर (batadv_tt_global_dump_entry(msg, portid, seq, bat_priv,
						common, sub)) अणु
			rcu_पढ़ो_unlock();
			*idx_s = idx - 1;
			वापस -EMSGSIZE;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	*idx_s = 0;
	*sub = 0;
	वापस 0;
पूर्ण

/**
 * batadv_tt_global_dump() -  Dump TT global entries पूर्णांकo a message
 * @msg: Netlink message to dump पूर्णांकo
 * @cb: Parameters from query
 *
 * Return: Error code, or length of message on success
 */
पूर्णांक batadv_tt_global_dump(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(cb->skb->sk);
	काष्ठा net_device *soft_अगरace;
	काष्ठा batadv_priv *bat_priv;
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	काष्ठा batadv_hashtable *hash;
	काष्ठा hlist_head *head;
	पूर्णांक ret;
	पूर्णांक अगरindex;
	पूर्णांक bucket = cb->args[0];
	पूर्णांक idx = cb->args[1];
	पूर्णांक sub = cb->args[2];
	पूर्णांक portid = NETLINK_CB(cb->skb).portid;

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

	hash = bat_priv->tt.global_hash;

	जबतक (bucket < hash->size) अणु
		head = &hash->table[bucket];

		अगर (batadv_tt_global_dump_bucket(msg, portid,
						 cb->nlh->nlmsg_seq, bat_priv,
						 head, &idx, &sub))
			अवरोध;

		bucket++;
	पूर्ण

	ret = msg->len;

 out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	अगर (soft_अगरace)
		dev_put(soft_अगरace);

	cb->args[0] = bucket;
	cb->args[1] = idx;
	cb->args[2] = sub;

	वापस ret;
पूर्ण

/**
 * _batadv_tt_global_del_orig_entry() - हटाओ and मुक्त an orig_entry
 * @tt_global_entry: the global entry to हटाओ the orig_entry from
 * @orig_entry: the orig entry to हटाओ and मुक्त
 *
 * Remove an orig_entry from its list in the given tt_global_entry and
 * मुक्त this orig_entry afterwards.
 *
 * Caller must hold tt_global_entry->list_lock and ensure orig_entry->list is
 * part of a list.
 */
अटल व्योम
_batadv_tt_global_del_orig_entry(काष्ठा batadv_tt_global_entry *tt_global_entry,
				 काष्ठा batadv_tt_orig_list_entry *orig_entry)
अणु
	lockdep_निश्चित_held(&tt_global_entry->list_lock);

	batadv_tt_global_size_dec(orig_entry->orig_node,
				  tt_global_entry->common.vid);
	atomic_dec(&tt_global_entry->orig_list_count);
	/* requires holding tt_global_entry->list_lock and orig_entry->list
	 * being part of a list
	 */
	hlist_del_rcu(&orig_entry->list);
	batadv_tt_orig_list_entry_put(orig_entry);
पूर्ण

/* deletes the orig list of a tt_global_entry */
अटल व्योम
batadv_tt_global_del_orig_list(काष्ठा batadv_tt_global_entry *tt_global_entry)
अणु
	काष्ठा hlist_head *head;
	काष्ठा hlist_node *safe;
	काष्ठा batadv_tt_orig_list_entry *orig_entry;

	spin_lock_bh(&tt_global_entry->list_lock);
	head = &tt_global_entry->orig_list;
	hlist_क्रम_each_entry_safe(orig_entry, safe, head, list)
		_batadv_tt_global_del_orig_entry(tt_global_entry, orig_entry);
	spin_unlock_bh(&tt_global_entry->list_lock);
पूर्ण

/**
 * batadv_tt_global_del_orig_node() - हटाओ orig_node from a global tt entry
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @tt_global_entry: the global entry to हटाओ the orig_node from
 * @orig_node: the originator announcing the client
 * @message: message to append to the log on deletion
 *
 * Remove the given orig_node and its according orig_entry from the given
 * global tt entry.
 */
अटल व्योम
batadv_tt_global_del_orig_node(काष्ठा batadv_priv *bat_priv,
			       काष्ठा batadv_tt_global_entry *tt_global_entry,
			       काष्ठा batadv_orig_node *orig_node,
			       स्थिर अक्षर *message)
अणु
	काष्ठा hlist_head *head;
	काष्ठा hlist_node *safe;
	काष्ठा batadv_tt_orig_list_entry *orig_entry;
	अचिन्हित लघु vid;

	spin_lock_bh(&tt_global_entry->list_lock);
	head = &tt_global_entry->orig_list;
	hlist_क्रम_each_entry_safe(orig_entry, safe, head, list) अणु
		अगर (orig_entry->orig_node == orig_node) अणु
			vid = tt_global_entry->common.vid;
			batadv_dbg(BATADV_DBG_TT, bat_priv,
				   "Deleting %pM from global tt entry %pM (vid: %d): %s\n",
				   orig_node->orig,
				   tt_global_entry->common.addr,
				   batadv_prपूर्णांक_vid(vid), message);
			_batadv_tt_global_del_orig_entry(tt_global_entry,
							 orig_entry);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&tt_global_entry->list_lock);
पूर्ण

/* If the client is to be deleted, we check अगर it is the last origantor entry
 * within tt_global entry. If yes, we set the BATADV_TT_CLIENT_ROAM flag and the
 * समयr, otherwise we simply हटाओ the originator scheduled क्रम deletion.
 */
अटल व्योम
batadv_tt_global_del_roaming(काष्ठा batadv_priv *bat_priv,
			     काष्ठा batadv_tt_global_entry *tt_global_entry,
			     काष्ठा batadv_orig_node *orig_node,
			     स्थिर अक्षर *message)
अणु
	bool last_entry = true;
	काष्ठा hlist_head *head;
	काष्ठा batadv_tt_orig_list_entry *orig_entry;

	/* no local entry exists, हाल 1:
	 * Check अगर this is the last one or अगर other entries exist.
	 */

	rcu_पढ़ो_lock();
	head = &tt_global_entry->orig_list;
	hlist_क्रम_each_entry_rcu(orig_entry, head, list) अणु
		अगर (orig_entry->orig_node != orig_node) अणु
			last_entry = false;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (last_entry) अणु
		/* its the last one, mark क्रम roaming. */
		tt_global_entry->common.flags |= BATADV_TT_CLIENT_ROAM;
		tt_global_entry->roam_at = jअगरfies;
	पूर्ण अन्यथा अणु
		/* there is another entry, we can simply delete this
		 * one and can still use the other one.
		 */
		batadv_tt_global_del_orig_node(bat_priv, tt_global_entry,
					       orig_node, message);
	पूर्ण
पूर्ण

/**
 * batadv_tt_global_del() - हटाओ a client from the global table
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: an originator serving this client
 * @addr: the mac address of the client
 * @vid: VLAN identअगरier
 * @message: a message explaining the reason क्रम deleting the client to prपूर्णांक
 *  क्रम debugging purpose
 * @roaming: true अगर the deletion has been triggered by a roaming event
 */
अटल व्योम batadv_tt_global_del(काष्ठा batadv_priv *bat_priv,
				 काष्ठा batadv_orig_node *orig_node,
				 स्थिर अचिन्हित अक्षर *addr, अचिन्हित लघु vid,
				 स्थिर अक्षर *message, bool roaming)
अणु
	काष्ठा batadv_tt_global_entry *tt_global_entry;
	काष्ठा batadv_tt_local_entry *local_entry = शून्य;

	tt_global_entry = batadv_tt_global_hash_find(bat_priv, addr, vid);
	अगर (!tt_global_entry)
		जाओ out;

	अगर (!roaming) अणु
		batadv_tt_global_del_orig_node(bat_priv, tt_global_entry,
					       orig_node, message);

		अगर (hlist_empty(&tt_global_entry->orig_list))
			batadv_tt_global_मुक्त(bat_priv, tt_global_entry,
					      message);

		जाओ out;
	पूर्ण

	/* अगर we are deleting a global entry due to a roam
	 * event, there are two possibilities:
	 * 1) the client roamed from node A to node B => अगर there
	 *    is only one originator left क्रम this client, we mark
	 *    it with BATADV_TT_CLIENT_ROAM, we start a समयr and we
	 *    रुको क्रम node B to claim it. In हाल of समयout
	 *    the entry is purged.
	 *
	 *    If there are other originators left, we directly delete
	 *    the originator.
	 * 2) the client roamed to us => we can directly delete
	 *    the global entry, since it is useless now.
	 */
	local_entry = batadv_tt_local_hash_find(bat_priv,
						tt_global_entry->common.addr,
						vid);
	अगर (local_entry) अणु
		/* local entry exists, हाल 2: client roamed to us. */
		batadv_tt_global_del_orig_list(tt_global_entry);
		batadv_tt_global_मुक्त(bat_priv, tt_global_entry, message);
	पूर्ण अन्यथा अणु
		/* no local entry exists, हाल 1: check क्रम roaming */
		batadv_tt_global_del_roaming(bat_priv, tt_global_entry,
					     orig_node, message);
	पूर्ण

out:
	अगर (tt_global_entry)
		batadv_tt_global_entry_put(tt_global_entry);
	अगर (local_entry)
		batadv_tt_local_entry_put(local_entry);
पूर्ण

/**
 * batadv_tt_global_del_orig() - हटाओ all the TT global entries beदीर्घing to
 *  the given originator matching the provided vid
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: the originator owning the entries to हटाओ
 * @match_vid: the VLAN identअगरier to match. If negative all the entries will be
 *  हटाओd
 * @message: debug message to prपूर्णांक as "reason"
 */
व्योम batadv_tt_global_del_orig(काष्ठा batadv_priv *bat_priv,
			       काष्ठा batadv_orig_node *orig_node,
			       s32 match_vid,
			       स्थिर अक्षर *message)
अणु
	काष्ठा batadv_tt_global_entry *tt_global;
	काष्ठा batadv_tt_common_entry *tt_common_entry;
	u32 i;
	काष्ठा batadv_hashtable *hash = bat_priv->tt.global_hash;
	काष्ठा hlist_node *safe;
	काष्ठा hlist_head *head;
	spinlock_t *list_lock; /* protects ग_लिखो access to the hash lists */
	अचिन्हित लघु vid;

	अगर (!hash)
		वापस;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];
		list_lock = &hash->list_locks[i];

		spin_lock_bh(list_lock);
		hlist_क्रम_each_entry_safe(tt_common_entry, safe,
					  head, hash_entry) अणु
			/* हटाओ only matching entries */
			अगर (match_vid >= 0 && tt_common_entry->vid != match_vid)
				जारी;

			tt_global = container_of(tt_common_entry,
						 काष्ठा batadv_tt_global_entry,
						 common);

			batadv_tt_global_del_orig_node(bat_priv, tt_global,
						       orig_node, message);

			अगर (hlist_empty(&tt_global->orig_list)) अणु
				vid = tt_global->common.vid;
				batadv_dbg(BATADV_DBG_TT, bat_priv,
					   "Deleting global tt entry %pM (vid: %d): %s\n",
					   tt_global->common.addr,
					   batadv_prपूर्णांक_vid(vid), message);
				hlist_del_rcu(&tt_common_entry->hash_entry);
				batadv_tt_global_entry_put(tt_global);
			पूर्ण
		पूर्ण
		spin_unlock_bh(list_lock);
	पूर्ण
	clear_bit(BATADV_ORIG_CAPA_HAS_TT, &orig_node->capa_initialized);
पूर्ण

अटल bool batadv_tt_global_to_purge(काष्ठा batadv_tt_global_entry *tt_global,
				      अक्षर **msg)
अणु
	bool purge = false;
	अचिन्हित दीर्घ roam_समयout = BATADV_TT_CLIENT_ROAM_TIMEOUT;
	अचिन्हित दीर्घ temp_समयout = BATADV_TT_CLIENT_TEMP_TIMEOUT;

	अगर ((tt_global->common.flags & BATADV_TT_CLIENT_ROAM) &&
	    batadv_has_समयd_out(tt_global->roam_at, roam_समयout)) अणु
		purge = true;
		*msg = "Roaming timeout\n";
	पूर्ण

	अगर ((tt_global->common.flags & BATADV_TT_CLIENT_TEMP) &&
	    batadv_has_समयd_out(tt_global->common.added_at, temp_समयout)) अणु
		purge = true;
		*msg = "Temporary client timeout\n";
	पूर्ण

	वापस purge;
पूर्ण

अटल व्योम batadv_tt_global_purge(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->tt.global_hash;
	काष्ठा hlist_head *head;
	काष्ठा hlist_node *node_पंचांगp;
	spinlock_t *list_lock; /* protects ग_लिखो access to the hash lists */
	u32 i;
	अक्षर *msg = शून्य;
	काष्ठा batadv_tt_common_entry *tt_common;
	काष्ठा batadv_tt_global_entry *tt_global;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];
		list_lock = &hash->list_locks[i];

		spin_lock_bh(list_lock);
		hlist_क्रम_each_entry_safe(tt_common, node_पंचांगp, head,
					  hash_entry) अणु
			tt_global = container_of(tt_common,
						 काष्ठा batadv_tt_global_entry,
						 common);

			अगर (!batadv_tt_global_to_purge(tt_global, &msg))
				जारी;

			batadv_dbg(BATADV_DBG_TT, bat_priv,
				   "Deleting global tt entry %pM (vid: %d): %s\n",
				   tt_global->common.addr,
				   batadv_prपूर्णांक_vid(tt_global->common.vid),
				   msg);

			hlist_del_rcu(&tt_common->hash_entry);

			batadv_tt_global_entry_put(tt_global);
		पूर्ण
		spin_unlock_bh(list_lock);
	पूर्ण
पूर्ण

अटल व्योम batadv_tt_global_table_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_hashtable *hash;
	spinlock_t *list_lock; /* protects ग_लिखो access to the hash lists */
	काष्ठा batadv_tt_common_entry *tt_common_entry;
	काष्ठा batadv_tt_global_entry *tt_global;
	काष्ठा hlist_node *node_पंचांगp;
	काष्ठा hlist_head *head;
	u32 i;

	अगर (!bat_priv->tt.global_hash)
		वापस;

	hash = bat_priv->tt.global_hash;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];
		list_lock = &hash->list_locks[i];

		spin_lock_bh(list_lock);
		hlist_क्रम_each_entry_safe(tt_common_entry, node_पंचांगp,
					  head, hash_entry) अणु
			hlist_del_rcu(&tt_common_entry->hash_entry);
			tt_global = container_of(tt_common_entry,
						 काष्ठा batadv_tt_global_entry,
						 common);
			batadv_tt_global_entry_put(tt_global);
		पूर्ण
		spin_unlock_bh(list_lock);
	पूर्ण

	batadv_hash_destroy(hash);

	bat_priv->tt.global_hash = शून्य;
पूर्ण

अटल bool
_batadv_is_ap_isolated(काष्ठा batadv_tt_local_entry *tt_local_entry,
		       काष्ठा batadv_tt_global_entry *tt_global_entry)
अणु
	अगर (tt_local_entry->common.flags & BATADV_TT_CLIENT_WIFI &&
	    tt_global_entry->common.flags & BATADV_TT_CLIENT_WIFI)
		वापस true;

	/* check अगर the two clients are marked as isolated */
	अगर (tt_local_entry->common.flags & BATADV_TT_CLIENT_ISOLA &&
	    tt_global_entry->common.flags & BATADV_TT_CLIENT_ISOLA)
		वापस true;

	वापस false;
पूर्ण

/**
 * batadv_transtable_search() - get the mesh destination क्रम a given client
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @src: mac address of the source client
 * @addr: mac address of the destination client
 * @vid: VLAN identअगरier
 *
 * Return: a poपूर्णांकer to the originator that was selected as destination in the
 * mesh क्रम contacting the client 'addr', शून्य otherwise.
 * In हाल of multiple originators serving the same client, the function वापसs
 * the best one (best in terms of metric towards the destination node).
 *
 * If the two clients are AP isolated the function वापसs शून्य.
 */
काष्ठा batadv_orig_node *batadv_transtable_search(काष्ठा batadv_priv *bat_priv,
						  स्थिर u8 *src,
						  स्थिर u8 *addr,
						  अचिन्हित लघु vid)
अणु
	काष्ठा batadv_tt_local_entry *tt_local_entry = शून्य;
	काष्ठा batadv_tt_global_entry *tt_global_entry = शून्य;
	काष्ठा batadv_orig_node *orig_node = शून्य;
	काष्ठा batadv_tt_orig_list_entry *best_entry;

	अगर (src && batadv_vlan_ap_isola_get(bat_priv, vid)) अणु
		tt_local_entry = batadv_tt_local_hash_find(bat_priv, src, vid);
		अगर (!tt_local_entry ||
		    (tt_local_entry->common.flags & BATADV_TT_CLIENT_PENDING))
			जाओ out;
	पूर्ण

	tt_global_entry = batadv_tt_global_hash_find(bat_priv, addr, vid);
	अगर (!tt_global_entry)
		जाओ out;

	/* check whether the clients should not communicate due to AP
	 * isolation
	 */
	अगर (tt_local_entry &&
	    _batadv_is_ap_isolated(tt_local_entry, tt_global_entry))
		जाओ out;

	rcu_पढ़ो_lock();
	best_entry = batadv_transtable_best_orig(bat_priv, tt_global_entry);
	/* found anything? */
	अगर (best_entry)
		orig_node = best_entry->orig_node;
	अगर (orig_node && !kref_get_unless_zero(&orig_node->refcount))
		orig_node = शून्य;
	rcu_पढ़ो_unlock();

out:
	अगर (tt_global_entry)
		batadv_tt_global_entry_put(tt_global_entry);
	अगर (tt_local_entry)
		batadv_tt_local_entry_put(tt_local_entry);

	वापस orig_node;
पूर्ण

/**
 * batadv_tt_global_crc() - calculates the checksum of the local table beदीर्घing
 *  to the given orig_node
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: originator क्रम which the CRC should be computed
 * @vid: VLAN identअगरier क्रम which the CRC32 has to be computed
 *
 * This function computes the checksum क्रम the global table corresponding to a
 * specअगरic originator. In particular, the checksum is computed as follows: For
 * each client connected to the originator the CRC32C of the MAC address and the
 * VID is computed and then all the CRC32Cs of the various clients are xor'ed
 * together.
 *
 * The idea behind is that CRC32C should be used as much as possible in order to
 * produce a unique hash of the table, but since the order which is used to feed
 * the CRC32C function affects the result and since every node in the network
 * probably sorts the clients dअगरferently, the hash function cannot be directly
 * computed over the entire table. Hence the CRC32C is used only on
 * the single client entry, जबतक all the results are then xor'ed together
 * because the XOR operation can combine them all जबतक trying to reduce the
 * noise as much as possible.
 *
 * Return: the checksum of the global table of a given originator.
 */
अटल u32 batadv_tt_global_crc(काष्ठा batadv_priv *bat_priv,
				काष्ठा batadv_orig_node *orig_node,
				अचिन्हित लघु vid)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->tt.global_hash;
	काष्ठा batadv_tt_orig_list_entry *tt_orig;
	काष्ठा batadv_tt_common_entry *tt_common;
	काष्ठा batadv_tt_global_entry *tt_global;
	काष्ठा hlist_head *head;
	u32 i, crc_पंचांगp, crc = 0;
	u8 flags;
	__be16 पंचांगp_vid;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(tt_common, head, hash_entry) अणु
			tt_global = container_of(tt_common,
						 काष्ठा batadv_tt_global_entry,
						 common);
			/* compute the CRC only क्रम entries beदीर्घing to the
			 * VLAN identअगरied by the vid passed as parameter
			 */
			अगर (tt_common->vid != vid)
				जारी;

			/* Roaming clients are in the global table क्रम
			 * consistency only. They करोn't have to be
			 * taken पूर्णांकo account जबतक computing the
			 * global crc
			 */
			अगर (tt_common->flags & BATADV_TT_CLIENT_ROAM)
				जारी;
			/* Temporary clients have not been announced yet, so
			 * they have to be skipped जबतक computing the global
			 * crc
			 */
			अगर (tt_common->flags & BATADV_TT_CLIENT_TEMP)
				जारी;

			/* find out अगर this global entry is announced by this
			 * originator
			 */
			tt_orig = batadv_tt_global_orig_entry_find(tt_global,
								   orig_node);
			अगर (!tt_orig)
				जारी;

			/* use network order to पढ़ो the VID: this ensures that
			 * every node पढ़ोs the bytes in the same order.
			 */
			पंचांगp_vid = htons(tt_common->vid);
			crc_पंचांगp = crc32c(0, &पंचांगp_vid, माप(पंचांगp_vid));

			/* compute the CRC on flags that have to be kept in sync
			 * among nodes
			 */
			flags = tt_orig->flags;
			crc_पंचांगp = crc32c(crc_पंचांगp, &flags, माप(flags));

			crc ^= crc32c(crc_पंचांगp, tt_common->addr, ETH_ALEN);

			batadv_tt_orig_list_entry_put(tt_orig);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	वापस crc;
पूर्ण

/**
 * batadv_tt_local_crc() - calculates the checksum of the local table
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @vid: VLAN identअगरier क्रम which the CRC32 has to be computed
 *
 * For details about the computation, please refer to the करोcumentation क्रम
 * batadv_tt_global_crc().
 *
 * Return: the checksum of the local table
 */
अटल u32 batadv_tt_local_crc(काष्ठा batadv_priv *bat_priv,
			       अचिन्हित लघु vid)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->tt.local_hash;
	काष्ठा batadv_tt_common_entry *tt_common;
	काष्ठा hlist_head *head;
	u32 i, crc_पंचांगp, crc = 0;
	u8 flags;
	__be16 पंचांगp_vid;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(tt_common, head, hash_entry) अणु
			/* compute the CRC only क्रम entries beदीर्घing to the
			 * VLAN identअगरied by vid
			 */
			अगर (tt_common->vid != vid)
				जारी;

			/* not yet committed clients have not to be taken पूर्णांकo
			 * account जबतक computing the CRC
			 */
			अगर (tt_common->flags & BATADV_TT_CLIENT_NEW)
				जारी;

			/* use network order to पढ़ो the VID: this ensures that
			 * every node पढ़ोs the bytes in the same order.
			 */
			पंचांगp_vid = htons(tt_common->vid);
			crc_पंचांगp = crc32c(0, &पंचांगp_vid, माप(पंचांगp_vid));

			/* compute the CRC on flags that have to be kept in sync
			 * among nodes
			 */
			flags = tt_common->flags & BATADV_TT_SYNC_MASK;
			crc_पंचांगp = crc32c(crc_पंचांगp, &flags, माप(flags));

			crc ^= crc32c(crc_पंचांगp, tt_common->addr, ETH_ALEN);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	वापस crc;
पूर्ण

/**
 * batadv_tt_req_node_release() - मुक्त tt_req node entry
 * @ref: kref poपूर्णांकer of the tt req_node entry
 */
अटल व्योम batadv_tt_req_node_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_tt_req_node *tt_req_node;

	tt_req_node = container_of(ref, काष्ठा batadv_tt_req_node, refcount);

	kmem_cache_मुक्त(batadv_tt_req_cache, tt_req_node);
पूर्ण

/**
 * batadv_tt_req_node_put() - decrement the tt_req_node refcounter and
 *  possibly release it
 * @tt_req_node: tt_req_node to be मुक्त'd
 */
अटल व्योम batadv_tt_req_node_put(काष्ठा batadv_tt_req_node *tt_req_node)
अणु
	kref_put(&tt_req_node->refcount, batadv_tt_req_node_release);
पूर्ण

अटल व्योम batadv_tt_req_list_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_tt_req_node *node;
	काष्ठा hlist_node *safe;

	spin_lock_bh(&bat_priv->tt.req_list_lock);

	hlist_क्रम_each_entry_safe(node, safe, &bat_priv->tt.req_list, list) अणु
		hlist_del_init(&node->list);
		batadv_tt_req_node_put(node);
	पूर्ण

	spin_unlock_bh(&bat_priv->tt.req_list_lock);
पूर्ण

अटल व्योम batadv_tt_save_orig_buffer(काष्ठा batadv_priv *bat_priv,
				       काष्ठा batadv_orig_node *orig_node,
				       स्थिर व्योम *tt_buff,
				       u16 tt_buff_len)
अणु
	/* Replace the old buffer only अगर I received something in the
	 * last OGM (the OGM could carry no changes)
	 */
	spin_lock_bh(&orig_node->tt_buff_lock);
	अगर (tt_buff_len > 0) अणु
		kमुक्त(orig_node->tt_buff);
		orig_node->tt_buff_len = 0;
		orig_node->tt_buff = kदो_स्मृति(tt_buff_len, GFP_ATOMIC);
		अगर (orig_node->tt_buff) अणु
			स_नकल(orig_node->tt_buff, tt_buff, tt_buff_len);
			orig_node->tt_buff_len = tt_buff_len;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&orig_node->tt_buff_lock);
पूर्ण

अटल व्योम batadv_tt_req_purge(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_tt_req_node *node;
	काष्ठा hlist_node *safe;

	spin_lock_bh(&bat_priv->tt.req_list_lock);
	hlist_क्रम_each_entry_safe(node, safe, &bat_priv->tt.req_list, list) अणु
		अगर (batadv_has_समयd_out(node->issued_at,
					 BATADV_TT_REQUEST_TIMEOUT)) अणु
			hlist_del_init(&node->list);
			batadv_tt_req_node_put(node);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&bat_priv->tt.req_list_lock);
पूर्ण

/**
 * batadv_tt_req_node_new() - search and possibly create a tt_req_node object
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: orig node this request is being issued क्रम
 *
 * Return: the poपूर्णांकer to the new tt_req_node काष्ठा अगर no request
 * has alपढ़ोy been issued क्रम this orig_node, शून्य otherwise.
 */
अटल काष्ठा batadv_tt_req_node *
batadv_tt_req_node_new(काष्ठा batadv_priv *bat_priv,
		       काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_tt_req_node *tt_req_node_पंचांगp, *tt_req_node = शून्य;

	spin_lock_bh(&bat_priv->tt.req_list_lock);
	hlist_क्रम_each_entry(tt_req_node_पंचांगp, &bat_priv->tt.req_list, list) अणु
		अगर (batadv_compare_eth(tt_req_node_पंचांगp, orig_node) &&
		    !batadv_has_समयd_out(tt_req_node_पंचांगp->issued_at,
					  BATADV_TT_REQUEST_TIMEOUT))
			जाओ unlock;
	पूर्ण

	tt_req_node = kmem_cache_alloc(batadv_tt_req_cache, GFP_ATOMIC);
	अगर (!tt_req_node)
		जाओ unlock;

	kref_init(&tt_req_node->refcount);
	ether_addr_copy(tt_req_node->addr, orig_node->orig);
	tt_req_node->issued_at = jअगरfies;

	kref_get(&tt_req_node->refcount);
	hlist_add_head(&tt_req_node->list, &bat_priv->tt.req_list);
unlock:
	spin_unlock_bh(&bat_priv->tt.req_list_lock);
	वापस tt_req_node;
पूर्ण

/**
 * batadv_tt_local_valid() - verअगरy local tt entry and get flags
 * @entry_ptr: to be checked local tt entry
 * @data_ptr: not used but definition required to satisfy the callback prototype
 * @flags: a poपूर्णांकer to store TT flags क्रम this client to
 *
 * Checks the validity of the given local TT entry. If it is, then the provided
 * flags poपूर्णांकer is updated.
 *
 * Return: true अगर the entry is a valid, false otherwise.
 */
अटल bool batadv_tt_local_valid(स्थिर व्योम *entry_ptr,
				  स्थिर व्योम *data_ptr,
				  u8 *flags)
अणु
	स्थिर काष्ठा batadv_tt_common_entry *tt_common_entry = entry_ptr;

	अगर (tt_common_entry->flags & BATADV_TT_CLIENT_NEW)
		वापस false;

	अगर (flags)
		*flags = tt_common_entry->flags;

	वापस true;
पूर्ण

/**
 * batadv_tt_global_valid() - verअगरy global tt entry and get flags
 * @entry_ptr: to be checked global tt entry
 * @data_ptr: an orig_node object (may be शून्य)
 * @flags: a poपूर्णांकer to store TT flags क्रम this client to
 *
 * Checks the validity of the given global TT entry. If it is, then the provided
 * flags poपूर्णांकer is updated either with the common (summed) TT flags अगर data_ptr
 * is शून्य or the specअगरic, per originator TT flags otherwise.
 *
 * Return: true अगर the entry is a valid, false otherwise.
 */
अटल bool batadv_tt_global_valid(स्थिर व्योम *entry_ptr,
				   स्थिर व्योम *data_ptr,
				   u8 *flags)
अणु
	स्थिर काष्ठा batadv_tt_common_entry *tt_common_entry = entry_ptr;
	स्थिर काष्ठा batadv_tt_global_entry *tt_global_entry;
	स्थिर काष्ठा batadv_orig_node *orig_node = data_ptr;

	अगर (tt_common_entry->flags & BATADV_TT_CLIENT_ROAM ||
	    tt_common_entry->flags & BATADV_TT_CLIENT_TEMP)
		वापस false;

	tt_global_entry = container_of(tt_common_entry,
				       काष्ठा batadv_tt_global_entry,
				       common);

	वापस batadv_tt_global_entry_has_orig(tt_global_entry, orig_node,
					       flags);
पूर्ण

/**
 * batadv_tt_tvlv_generate() - fill the tvlv buff with the tt entries from the
 *  specअगरied tt hash
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @hash: hash table containing the tt entries
 * @tt_len: expected tvlv tt data buffer length in number of bytes
 * @tvlv_buff: poपूर्णांकer to the buffer to fill with the TT data
 * @valid_cb: function to filter tt change entries and to वापस TT flags
 * @cb_data: data passed to the filter function as argument
 *
 * Fills the tvlv buff with the tt entries from the specअगरied hash. If valid_cb
 * is not provided then this becomes a no-op.
 */
अटल व्योम batadv_tt_tvlv_generate(काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_hashtable *hash,
				    व्योम *tvlv_buff, u16 tt_len,
				    bool (*valid_cb)(स्थिर व्योम *,
						     स्थिर व्योम *,
						     u8 *flags),
				    व्योम *cb_data)
अणु
	काष्ठा batadv_tt_common_entry *tt_common_entry;
	काष्ठा batadv_tvlv_tt_change *tt_change;
	काष्ठा hlist_head *head;
	u16 tt_tot, tt_num_entries = 0;
	u8 flags;
	bool ret;
	u32 i;

	tt_tot = batadv_tt_entries(tt_len);
	tt_change = (काष्ठा batadv_tvlv_tt_change *)tvlv_buff;

	अगर (!valid_cb)
		वापस;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];

		hlist_क्रम_each_entry_rcu(tt_common_entry,
					 head, hash_entry) अणु
			अगर (tt_tot == tt_num_entries)
				अवरोध;

			ret = valid_cb(tt_common_entry, cb_data, &flags);
			अगर (!ret)
				जारी;

			ether_addr_copy(tt_change->addr, tt_common_entry->addr);
			tt_change->flags = flags;
			tt_change->vid = htons(tt_common_entry->vid);
			स_रखो(tt_change->reserved, 0,
			       माप(tt_change->reserved));

			tt_num_entries++;
			tt_change++;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * batadv_tt_global_check_crc() - check अगर all the CRCs are correct
 * @orig_node: originator क्रम which the CRCs have to be checked
 * @tt_vlan: poपूर्णांकer to the first tvlv VLAN entry
 * @num_vlan: number of tvlv VLAN entries
 *
 * Return: true अगर all the received CRCs match the locally stored ones, false
 * otherwise
 */
अटल bool batadv_tt_global_check_crc(काष्ठा batadv_orig_node *orig_node,
				       काष्ठा batadv_tvlv_tt_vlan_data *tt_vlan,
				       u16 num_vlan)
अणु
	काष्ठा batadv_tvlv_tt_vlan_data *tt_vlan_पंचांगp;
	काष्ठा batadv_orig_node_vlan *vlan;
	पूर्णांक i, orig_num_vlan;
	u32 crc;

	/* check अगर each received CRC matches the locally stored one */
	क्रम (i = 0; i < num_vlan; i++) अणु
		tt_vlan_पंचांगp = tt_vlan + i;

		/* अगर orig_node is a backbone node क्रम this VLAN, करोn't check
		 * the CRC as we ignore all the global entries over it
		 */
		अगर (batadv_bla_is_backbone_gw_orig(orig_node->bat_priv,
						   orig_node->orig,
						   ntohs(tt_vlan_पंचांगp->vid)))
			जारी;

		vlan = batadv_orig_node_vlan_get(orig_node,
						 ntohs(tt_vlan_पंचांगp->vid));
		अगर (!vlan)
			वापस false;

		crc = vlan->tt.crc;
		batadv_orig_node_vlan_put(vlan);

		अगर (crc != ntohl(tt_vlan_पंचांगp->crc))
			वापस false;
	पूर्ण

	/* check अगर any excess VLANs exist locally क्रम the originator
	 * which are not mentioned in the TVLV from the originator.
	 */
	rcu_पढ़ो_lock();
	orig_num_vlan = 0;
	hlist_क्रम_each_entry_rcu(vlan, &orig_node->vlan_list, list)
		orig_num_vlan++;
	rcu_पढ़ो_unlock();

	अगर (orig_num_vlan > num_vlan)
		वापस false;

	वापस true;
पूर्ण

/**
 * batadv_tt_local_update_crc() - update all the local CRCs
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
अटल व्योम batadv_tt_local_update_crc(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_softअगर_vlan *vlan;

	/* recompute the global CRC क्रम each VLAN */
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(vlan, &bat_priv->softअगर_vlan_list, list) अणु
		vlan->tt.crc = batadv_tt_local_crc(bat_priv, vlan->vid);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * batadv_tt_global_update_crc() - update all the global CRCs क्रम this orig_node
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: the orig_node क्रम which the CRCs have to be updated
 */
अटल व्योम batadv_tt_global_update_crc(काष्ठा batadv_priv *bat_priv,
					काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_orig_node_vlan *vlan;
	u32 crc;

	/* recompute the global CRC क्रम each VLAN */
	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(vlan, &orig_node->vlan_list, list) अणु
		/* अगर orig_node is a backbone node क्रम this VLAN, करोn't compute
		 * the CRC as we ignore all the global entries over it
		 */
		अगर (batadv_bla_is_backbone_gw_orig(bat_priv, orig_node->orig,
						   vlan->vid))
			जारी;

		crc = batadv_tt_global_crc(bat_priv, orig_node, vlan->vid);
		vlan->tt.crc = crc;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * batadv_send_tt_request() - send a TT Request message to a given node
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @dst_orig_node: the destination of the message
 * @ttvn: the version number that the source of the message is looking क्रम
 * @tt_vlan: poपूर्णांकer to the first tvlv VLAN object to request
 * @num_vlan: number of tvlv VLAN entries
 * @full_table: ask क्रम the entire translation table अगर true, जबतक only क्रम the
 *  last TT dअगरf otherwise
 *
 * Return: true अगर the TT Request was sent, false otherwise
 */
अटल bool batadv_send_tt_request(काष्ठा batadv_priv *bat_priv,
				   काष्ठा batadv_orig_node *dst_orig_node,
				   u8 ttvn,
				   काष्ठा batadv_tvlv_tt_vlan_data *tt_vlan,
				   u16 num_vlan, bool full_table)
अणु
	काष्ठा batadv_tvlv_tt_data *tvlv_tt_data = शून्य;
	काष्ठा batadv_tt_req_node *tt_req_node = शून्य;
	काष्ठा batadv_tvlv_tt_vlan_data *tt_vlan_req;
	काष्ठा batadv_hard_अगरace *primary_अगर;
	bool ret = false;
	पूर्णांक i, size;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		जाओ out;

	/* The new tt_req will be issued only अगर I'm not रुकोing क्रम a
	 * reply from the same orig_node yet
	 */
	tt_req_node = batadv_tt_req_node_new(bat_priv, dst_orig_node);
	अगर (!tt_req_node)
		जाओ out;

	size = माप(*tvlv_tt_data) + माप(*tt_vlan_req) * num_vlan;
	tvlv_tt_data = kzalloc(size, GFP_ATOMIC);
	अगर (!tvlv_tt_data)
		जाओ out;

	tvlv_tt_data->flags = BATADV_TT_REQUEST;
	tvlv_tt_data->ttvn = ttvn;
	tvlv_tt_data->num_vlan = htons(num_vlan);

	/* send all the CRCs within the request. This is needed by पूर्णांकermediate
	 * nodes to ensure they have the correct table beक्रमe replying
	 */
	tt_vlan_req = (काष्ठा batadv_tvlv_tt_vlan_data *)(tvlv_tt_data + 1);
	क्रम (i = 0; i < num_vlan; i++) अणु
		tt_vlan_req->vid = tt_vlan->vid;
		tt_vlan_req->crc = tt_vlan->crc;

		tt_vlan_req++;
		tt_vlan++;
	पूर्ण

	अगर (full_table)
		tvlv_tt_data->flags |= BATADV_TT_FULL_TABLE;

	batadv_dbg(BATADV_DBG_TT, bat_priv, "Sending TT_REQUEST to %pM [%c]\n",
		   dst_orig_node->orig, full_table ? 'F' : '.');

	batadv_inc_counter(bat_priv, BATADV_CNT_TT_REQUEST_TX);
	batadv_tvlv_unicast_send(bat_priv, primary_अगर->net_dev->dev_addr,
				 dst_orig_node->orig, BATADV_TVLV_TT, 1,
				 tvlv_tt_data, size);
	ret = true;

out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);

	अगर (ret && tt_req_node) अणु
		spin_lock_bh(&bat_priv->tt.req_list_lock);
		अगर (!hlist_unhashed(&tt_req_node->list)) अणु
			hlist_del_init(&tt_req_node->list);
			batadv_tt_req_node_put(tt_req_node);
		पूर्ण
		spin_unlock_bh(&bat_priv->tt.req_list_lock);
	पूर्ण

	अगर (tt_req_node)
		batadv_tt_req_node_put(tt_req_node);

	kमुक्त(tvlv_tt_data);
	वापस ret;
पूर्ण

/**
 * batadv_send_other_tt_response() - send reply to tt request concerning another
 *  node's translation table
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @tt_data: tt data containing the tt request inक्रमmation
 * @req_src: mac address of tt request sender
 * @req_dst: mac address of tt request recipient
 *
 * Return: true अगर tt request reply was sent, false otherwise.
 */
अटल bool batadv_send_other_tt_response(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_tvlv_tt_data *tt_data,
					  u8 *req_src, u8 *req_dst)
अणु
	काष्ठा batadv_orig_node *req_dst_orig_node;
	काष्ठा batadv_orig_node *res_dst_orig_node = शून्य;
	काष्ठा batadv_tvlv_tt_change *tt_change;
	काष्ठा batadv_tvlv_tt_data *tvlv_tt_data = शून्य;
	काष्ठा batadv_tvlv_tt_vlan_data *tt_vlan;
	bool ret = false, full_table;
	u8 orig_ttvn, req_ttvn;
	u16 tvlv_len;
	s32 tt_len;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Received TT_REQUEST from %pM for ttvn: %u (%pM) [%c]\n",
		   req_src, tt_data->ttvn, req_dst,
		   ((tt_data->flags & BATADV_TT_FULL_TABLE) ? 'F' : '.'));

	/* Let's get the orig node of the REAL destination */
	req_dst_orig_node = batadv_orig_hash_find(bat_priv, req_dst);
	अगर (!req_dst_orig_node)
		जाओ out;

	res_dst_orig_node = batadv_orig_hash_find(bat_priv, req_src);
	अगर (!res_dst_orig_node)
		जाओ out;

	orig_ttvn = (u8)atomic_पढ़ो(&req_dst_orig_node->last_ttvn);
	req_ttvn = tt_data->ttvn;

	tt_vlan = (काष्ठा batadv_tvlv_tt_vlan_data *)(tt_data + 1);
	/* this node करोesn't have the requested data */
	अगर (orig_ttvn != req_ttvn ||
	    !batadv_tt_global_check_crc(req_dst_orig_node, tt_vlan,
					ntohs(tt_data->num_vlan)))
		जाओ out;

	/* If the full table has been explicitly requested */
	अगर (tt_data->flags & BATADV_TT_FULL_TABLE ||
	    !req_dst_orig_node->tt_buff)
		full_table = true;
	अन्यथा
		full_table = false;

	/* TT fragmentation hasn't been implemented yet, so send as many
	 * TT entries fit a single packet as possible only
	 */
	अगर (!full_table) अणु
		spin_lock_bh(&req_dst_orig_node->tt_buff_lock);
		tt_len = req_dst_orig_node->tt_buff_len;

		tvlv_len = batadv_tt_prepare_tvlv_global_data(req_dst_orig_node,
							      &tvlv_tt_data,
							      &tt_change,
							      &tt_len);
		अगर (!tt_len)
			जाओ unlock;

		/* Copy the last orig_node's OGM buffer */
		स_नकल(tt_change, req_dst_orig_node->tt_buff,
		       req_dst_orig_node->tt_buff_len);
		spin_unlock_bh(&req_dst_orig_node->tt_buff_lock);
	पूर्ण अन्यथा अणु
		/* allocate the tvlv, put the tt_data and all the tt_vlan_data
		 * in the initial part
		 */
		tt_len = -1;
		tvlv_len = batadv_tt_prepare_tvlv_global_data(req_dst_orig_node,
							      &tvlv_tt_data,
							      &tt_change,
							      &tt_len);
		अगर (!tt_len)
			जाओ out;

		/* fill the rest of the tvlv with the real TT entries */
		batadv_tt_tvlv_generate(bat_priv, bat_priv->tt.global_hash,
					tt_change, tt_len,
					batadv_tt_global_valid,
					req_dst_orig_node);
	पूर्ण

	/* Don't send the response, अगर larger than fragmented packet. */
	tt_len = माप(काष्ठा batadv_unicast_tvlv_packet) + tvlv_len;
	अगर (tt_len > atomic_पढ़ो(&bat_priv->packet_size_max)) अणु
		net_ratelimited_function(batadv_info, bat_priv->soft_अगरace,
					 "Ignoring TT_REQUEST from %pM; Response size exceeds max packet size.\n",
					 res_dst_orig_node->orig);
		जाओ out;
	पूर्ण

	tvlv_tt_data->flags = BATADV_TT_RESPONSE;
	tvlv_tt_data->ttvn = req_ttvn;

	अगर (full_table)
		tvlv_tt_data->flags |= BATADV_TT_FULL_TABLE;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Sending TT_RESPONSE %pM for %pM [%c] (ttvn: %u)\n",
		   res_dst_orig_node->orig, req_dst_orig_node->orig,
		   full_table ? 'F' : '.', req_ttvn);

	batadv_inc_counter(bat_priv, BATADV_CNT_TT_RESPONSE_TX);

	batadv_tvlv_unicast_send(bat_priv, req_dst_orig_node->orig,
				 req_src, BATADV_TVLV_TT, 1, tvlv_tt_data,
				 tvlv_len);

	ret = true;
	जाओ out;

unlock:
	spin_unlock_bh(&req_dst_orig_node->tt_buff_lock);

out:
	अगर (res_dst_orig_node)
		batadv_orig_node_put(res_dst_orig_node);
	अगर (req_dst_orig_node)
		batadv_orig_node_put(req_dst_orig_node);
	kमुक्त(tvlv_tt_data);
	वापस ret;
पूर्ण

/**
 * batadv_send_my_tt_response() - send reply to tt request concerning this
 *  node's translation table
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @tt_data: tt data containing the tt request inक्रमmation
 * @req_src: mac address of tt request sender
 *
 * Return: true अगर tt request reply was sent, false otherwise.
 */
अटल bool batadv_send_my_tt_response(काष्ठा batadv_priv *bat_priv,
				       काष्ठा batadv_tvlv_tt_data *tt_data,
				       u8 *req_src)
अणु
	काष्ठा batadv_tvlv_tt_data *tvlv_tt_data = शून्य;
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	काष्ठा batadv_tvlv_tt_change *tt_change;
	काष्ठा batadv_orig_node *orig_node;
	u8 my_ttvn, req_ttvn;
	u16 tvlv_len;
	bool full_table;
	s32 tt_len;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Received TT_REQUEST from %pM for ttvn: %u (me) [%c]\n",
		   req_src, tt_data->ttvn,
		   ((tt_data->flags & BATADV_TT_FULL_TABLE) ? 'F' : '.'));

	spin_lock_bh(&bat_priv->tt.commit_lock);

	my_ttvn = (u8)atomic_पढ़ो(&bat_priv->tt.vn);
	req_ttvn = tt_data->ttvn;

	orig_node = batadv_orig_hash_find(bat_priv, req_src);
	अगर (!orig_node)
		जाओ out;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		जाओ out;

	/* If the full table has been explicitly requested or the gap
	 * is too big send the whole local translation table
	 */
	अगर (tt_data->flags & BATADV_TT_FULL_TABLE || my_ttvn != req_ttvn ||
	    !bat_priv->tt.last_changeset)
		full_table = true;
	अन्यथा
		full_table = false;

	/* TT fragmentation hasn't been implemented yet, so send as many
	 * TT entries fit a single packet as possible only
	 */
	अगर (!full_table) अणु
		spin_lock_bh(&bat_priv->tt.last_changeset_lock);

		tt_len = bat_priv->tt.last_changeset_len;
		tvlv_len = batadv_tt_prepare_tvlv_local_data(bat_priv,
							     &tvlv_tt_data,
							     &tt_change,
							     &tt_len);
		अगर (!tt_len || !tvlv_len)
			जाओ unlock;

		/* Copy the last orig_node's OGM buffer */
		स_नकल(tt_change, bat_priv->tt.last_changeset,
		       bat_priv->tt.last_changeset_len);
		spin_unlock_bh(&bat_priv->tt.last_changeset_lock);
	पूर्ण अन्यथा अणु
		req_ttvn = (u8)atomic_पढ़ो(&bat_priv->tt.vn);

		/* allocate the tvlv, put the tt_data and all the tt_vlan_data
		 * in the initial part
		 */
		tt_len = -1;
		tvlv_len = batadv_tt_prepare_tvlv_local_data(bat_priv,
							     &tvlv_tt_data,
							     &tt_change,
							     &tt_len);
		अगर (!tt_len || !tvlv_len)
			जाओ out;

		/* fill the rest of the tvlv with the real TT entries */
		batadv_tt_tvlv_generate(bat_priv, bat_priv->tt.local_hash,
					tt_change, tt_len,
					batadv_tt_local_valid, शून्य);
	पूर्ण

	tvlv_tt_data->flags = BATADV_TT_RESPONSE;
	tvlv_tt_data->ttvn = req_ttvn;

	अगर (full_table)
		tvlv_tt_data->flags |= BATADV_TT_FULL_TABLE;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Sending TT_RESPONSE to %pM [%c] (ttvn: %u)\n",
		   orig_node->orig, full_table ? 'F' : '.', req_ttvn);

	batadv_inc_counter(bat_priv, BATADV_CNT_TT_RESPONSE_TX);

	batadv_tvlv_unicast_send(bat_priv, primary_अगर->net_dev->dev_addr,
				 req_src, BATADV_TVLV_TT, 1, tvlv_tt_data,
				 tvlv_len);

	जाओ out;

unlock:
	spin_unlock_bh(&bat_priv->tt.last_changeset_lock);
out:
	spin_unlock_bh(&bat_priv->tt.commit_lock);
	अगर (orig_node)
		batadv_orig_node_put(orig_node);
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	kमुक्त(tvlv_tt_data);
	/* The packet was क्रम this host, so it करोesn't need to be re-routed */
	वापस true;
पूर्ण

/**
 * batadv_send_tt_response() - send reply to tt request
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @tt_data: tt data containing the tt request inक्रमmation
 * @req_src: mac address of tt request sender
 * @req_dst: mac address of tt request recipient
 *
 * Return: true अगर tt request reply was sent, false otherwise.
 */
अटल bool batadv_send_tt_response(काष्ठा batadv_priv *bat_priv,
				    काष्ठा batadv_tvlv_tt_data *tt_data,
				    u8 *req_src, u8 *req_dst)
अणु
	अगर (batadv_is_my_mac(bat_priv, req_dst))
		वापस batadv_send_my_tt_response(bat_priv, tt_data, req_src);
	वापस batadv_send_other_tt_response(bat_priv, tt_data, req_src,
					     req_dst);
पूर्ण

अटल व्योम _batadv_tt_update_changes(काष्ठा batadv_priv *bat_priv,
				      काष्ठा batadv_orig_node *orig_node,
				      काष्ठा batadv_tvlv_tt_change *tt_change,
				      u16 tt_num_changes, u8 ttvn)
अणु
	पूर्णांक i;
	पूर्णांक roams;

	क्रम (i = 0; i < tt_num_changes; i++) अणु
		अगर ((tt_change + i)->flags & BATADV_TT_CLIENT_DEL) अणु
			roams = (tt_change + i)->flags & BATADV_TT_CLIENT_ROAM;
			batadv_tt_global_del(bat_priv, orig_node,
					     (tt_change + i)->addr,
					     ntohs((tt_change + i)->vid),
					     "tt removed by changes",
					     roams);
		पूर्ण अन्यथा अणु
			अगर (!batadv_tt_global_add(bat_priv, orig_node,
						  (tt_change + i)->addr,
						  ntohs((tt_change + i)->vid),
						  (tt_change + i)->flags, ttvn))
				/* In हाल of problem जबतक storing a
				 * global_entry, we stop the updating
				 * procedure without committing the
				 * ttvn change. This will aव्योम to send
				 * corrupted data on tt_request
				 */
				वापस;
		पूर्ण
	पूर्ण
	set_bit(BATADV_ORIG_CAPA_HAS_TT, &orig_node->capa_initialized);
पूर्ण

अटल व्योम batadv_tt_fill_gtable(काष्ठा batadv_priv *bat_priv,
				  काष्ठा batadv_tvlv_tt_change *tt_change,
				  u8 ttvn, u8 *resp_src,
				  u16 num_entries)
अणु
	काष्ठा batadv_orig_node *orig_node;

	orig_node = batadv_orig_hash_find(bat_priv, resp_src);
	अगर (!orig_node)
		जाओ out;

	/* Purge the old table first.. */
	batadv_tt_global_del_orig(bat_priv, orig_node, -1,
				  "Received full table");

	_batadv_tt_update_changes(bat_priv, orig_node, tt_change, num_entries,
				  ttvn);

	spin_lock_bh(&orig_node->tt_buff_lock);
	kमुक्त(orig_node->tt_buff);
	orig_node->tt_buff_len = 0;
	orig_node->tt_buff = शून्य;
	spin_unlock_bh(&orig_node->tt_buff_lock);

	atomic_set(&orig_node->last_ttvn, ttvn);

out:
	अगर (orig_node)
		batadv_orig_node_put(orig_node);
पूर्ण

अटल व्योम batadv_tt_update_changes(काष्ठा batadv_priv *bat_priv,
				     काष्ठा batadv_orig_node *orig_node,
				     u16 tt_num_changes, u8 ttvn,
				     काष्ठा batadv_tvlv_tt_change *tt_change)
अणु
	_batadv_tt_update_changes(bat_priv, orig_node, tt_change,
				  tt_num_changes, ttvn);

	batadv_tt_save_orig_buffer(bat_priv, orig_node, tt_change,
				   batadv_tt_len(tt_num_changes));
	atomic_set(&orig_node->last_ttvn, ttvn);
पूर्ण

/**
 * batadv_is_my_client() - check अगर a client is served by the local node
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: the mac address of the client to check
 * @vid: VLAN identअगरier
 *
 * Return: true अगर the client is served by this node, false otherwise.
 */
bool batadv_is_my_client(काष्ठा batadv_priv *bat_priv, स्थिर u8 *addr,
			 अचिन्हित लघु vid)
अणु
	काष्ठा batadv_tt_local_entry *tt_local_entry;
	bool ret = false;

	tt_local_entry = batadv_tt_local_hash_find(bat_priv, addr, vid);
	अगर (!tt_local_entry)
		जाओ out;
	/* Check अगर the client has been logically deleted (but is kept क्रम
	 * consistency purpose)
	 */
	अगर ((tt_local_entry->common.flags & BATADV_TT_CLIENT_PENDING) ||
	    (tt_local_entry->common.flags & BATADV_TT_CLIENT_ROAM))
		जाओ out;
	ret = true;
out:
	अगर (tt_local_entry)
		batadv_tt_local_entry_put(tt_local_entry);
	वापस ret;
पूर्ण

/**
 * batadv_handle_tt_response() - process incoming tt reply
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @tt_data: tt data containing the tt request inक्रमmation
 * @resp_src: mac address of tt reply sender
 * @num_entries: number of tt change entries appended to the tt data
 */
अटल व्योम batadv_handle_tt_response(काष्ठा batadv_priv *bat_priv,
				      काष्ठा batadv_tvlv_tt_data *tt_data,
				      u8 *resp_src, u16 num_entries)
अणु
	काष्ठा batadv_tt_req_node *node;
	काष्ठा hlist_node *safe;
	काष्ठा batadv_orig_node *orig_node = शून्य;
	काष्ठा batadv_tvlv_tt_change *tt_change;
	u8 *tvlv_ptr = (u8 *)tt_data;
	u16 change_offset;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Received TT_RESPONSE from %pM for ttvn %d t_size: %d [%c]\n",
		   resp_src, tt_data->ttvn, num_entries,
		   ((tt_data->flags & BATADV_TT_FULL_TABLE) ? 'F' : '.'));

	orig_node = batadv_orig_hash_find(bat_priv, resp_src);
	अगर (!orig_node)
		जाओ out;

	spin_lock_bh(&orig_node->tt_lock);

	change_offset = माप(काष्ठा batadv_tvlv_tt_vlan_data);
	change_offset *= ntohs(tt_data->num_vlan);
	change_offset += माप(*tt_data);
	tvlv_ptr += change_offset;

	tt_change = (काष्ठा batadv_tvlv_tt_change *)tvlv_ptr;
	अगर (tt_data->flags & BATADV_TT_FULL_TABLE) अणु
		batadv_tt_fill_gtable(bat_priv, tt_change, tt_data->ttvn,
				      resp_src, num_entries);
	पूर्ण अन्यथा अणु
		batadv_tt_update_changes(bat_priv, orig_node, num_entries,
					 tt_data->ttvn, tt_change);
	पूर्ण

	/* Recalculate the CRC क्रम this orig_node and store it */
	batadv_tt_global_update_crc(bat_priv, orig_node);

	spin_unlock_bh(&orig_node->tt_lock);

	/* Delete the tt_req_node from pending tt_requests list */
	spin_lock_bh(&bat_priv->tt.req_list_lock);
	hlist_क्रम_each_entry_safe(node, safe, &bat_priv->tt.req_list, list) अणु
		अगर (!batadv_compare_eth(node->addr, resp_src))
			जारी;
		hlist_del_init(&node->list);
		batadv_tt_req_node_put(node);
	पूर्ण

	spin_unlock_bh(&bat_priv->tt.req_list_lock);
out:
	अगर (orig_node)
		batadv_orig_node_put(orig_node);
पूर्ण

अटल व्योम batadv_tt_roam_list_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_tt_roam_node *node, *safe;

	spin_lock_bh(&bat_priv->tt.roam_list_lock);

	list_क्रम_each_entry_safe(node, safe, &bat_priv->tt.roam_list, list) अणु
		list_del(&node->list);
		kmem_cache_मुक्त(batadv_tt_roam_cache, node);
	पूर्ण

	spin_unlock_bh(&bat_priv->tt.roam_list_lock);
पूर्ण

अटल व्योम batadv_tt_roam_purge(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_tt_roam_node *node, *safe;

	spin_lock_bh(&bat_priv->tt.roam_list_lock);
	list_क्रम_each_entry_safe(node, safe, &bat_priv->tt.roam_list, list) अणु
		अगर (!batadv_has_समयd_out(node->first_समय,
					  BATADV_ROAMING_MAX_TIME))
			जारी;

		list_del(&node->list);
		kmem_cache_मुक्त(batadv_tt_roam_cache, node);
	पूर्ण
	spin_unlock_bh(&bat_priv->tt.roam_list_lock);
पूर्ण

/**
 * batadv_tt_check_roam_count() - check अगर a client has roamed too frequently
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @client: mac address of the roaming client
 *
 * This function checks whether the client alपढ़ोy reached the
 * maximum number of possible roaming phases. In this हाल the ROAMING_ADV
 * will not be sent.
 *
 * Return: true अगर the ROAMING_ADV can be sent, false otherwise
 */
अटल bool batadv_tt_check_roam_count(काष्ठा batadv_priv *bat_priv, u8 *client)
अणु
	काष्ठा batadv_tt_roam_node *tt_roam_node;
	bool ret = false;

	spin_lock_bh(&bat_priv->tt.roam_list_lock);
	/* The new tt_req will be issued only अगर I'm not रुकोing क्रम a
	 * reply from the same orig_node yet
	 */
	list_क्रम_each_entry(tt_roam_node, &bat_priv->tt.roam_list, list) अणु
		अगर (!batadv_compare_eth(tt_roam_node->addr, client))
			जारी;

		अगर (batadv_has_समयd_out(tt_roam_node->first_समय,
					 BATADV_ROAMING_MAX_TIME))
			जारी;

		अगर (!batadv_atomic_dec_not_zero(&tt_roam_node->counter))
			/* Sorry, you roamed too many बार! */
			जाओ unlock;
		ret = true;
		अवरोध;
	पूर्ण

	अगर (!ret) अणु
		tt_roam_node = kmem_cache_alloc(batadv_tt_roam_cache,
						GFP_ATOMIC);
		अगर (!tt_roam_node)
			जाओ unlock;

		tt_roam_node->first_समय = jअगरfies;
		atomic_set(&tt_roam_node->counter,
			   BATADV_ROAMING_MAX_COUNT - 1);
		ether_addr_copy(tt_roam_node->addr, client);

		list_add(&tt_roam_node->list, &bat_priv->tt.roam_list);
		ret = true;
	पूर्ण

unlock:
	spin_unlock_bh(&bat_priv->tt.roam_list_lock);
	वापस ret;
पूर्ण

/**
 * batadv_send_roam_adv() - send a roaming advertisement message
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @client: mac address of the roaming client
 * @vid: VLAN identअगरier
 * @orig_node: message destination
 *
 * Send a ROAMING_ADV message to the node which was previously serving this
 * client. This is करोne to inक्रमm the node that from now on all traffic destined
 * क्रम this particular roamed client has to be क्रमwarded to the sender of the
 * roaming message.
 */
अटल व्योम batadv_send_roam_adv(काष्ठा batadv_priv *bat_priv, u8 *client,
				 अचिन्हित लघु vid,
				 काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_hard_अगरace *primary_अगर;
	काष्ठा batadv_tvlv_roam_adv tvlv_roam;

	primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
	अगर (!primary_अगर)
		जाओ out;

	/* beक्रमe going on we have to check whether the client has
	 * alपढ़ोy roamed to us too many बार
	 */
	अगर (!batadv_tt_check_roam_count(bat_priv, client))
		जाओ out;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Sending ROAMING_ADV to %pM (client %pM, vid: %d)\n",
		   orig_node->orig, client, batadv_prपूर्णांक_vid(vid));

	batadv_inc_counter(bat_priv, BATADV_CNT_TT_ROAM_ADV_TX);

	स_नकल(tvlv_roam.client, client, माप(tvlv_roam.client));
	tvlv_roam.vid = htons(vid);

	batadv_tvlv_unicast_send(bat_priv, primary_अगर->net_dev->dev_addr,
				 orig_node->orig, BATADV_TVLV_ROAM, 1,
				 &tvlv_roam, माप(tvlv_roam));

out:
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
पूर्ण

अटल व्योम batadv_tt_purge(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work;
	काष्ठा batadv_priv_tt *priv_tt;
	काष्ठा batadv_priv *bat_priv;

	delayed_work = to_delayed_work(work);
	priv_tt = container_of(delayed_work, काष्ठा batadv_priv_tt, work);
	bat_priv = container_of(priv_tt, काष्ठा batadv_priv, tt);

	batadv_tt_local_purge(bat_priv, BATADV_TT_LOCAL_TIMEOUT);
	batadv_tt_global_purge(bat_priv);
	batadv_tt_req_purge(bat_priv);
	batadv_tt_roam_purge(bat_priv);

	queue_delayed_work(batadv_event_workqueue, &bat_priv->tt.work,
			   msecs_to_jअगरfies(BATADV_TT_WORK_PERIOD));
पूर्ण

/**
 * batadv_tt_मुक्त() - Free translation table of soft पूर्णांकerface
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_tt_मुक्त(काष्ठा batadv_priv *bat_priv)
अणु
	batadv_tvlv_handler_unरेजिस्टर(bat_priv, BATADV_TVLV_ROAM, 1);

	batadv_tvlv_container_unरेजिस्टर(bat_priv, BATADV_TVLV_TT, 1);
	batadv_tvlv_handler_unरेजिस्टर(bat_priv, BATADV_TVLV_TT, 1);

	cancel_delayed_work_sync(&bat_priv->tt.work);

	batadv_tt_local_table_मुक्त(bat_priv);
	batadv_tt_global_table_मुक्त(bat_priv);
	batadv_tt_req_list_मुक्त(bat_priv);
	batadv_tt_changes_list_मुक्त(bat_priv);
	batadv_tt_roam_list_मुक्त(bat_priv);

	kमुक्त(bat_priv->tt.last_changeset);
पूर्ण

/**
 * batadv_tt_local_set_flags() - set or unset the specअगरied flags on the local
 *  table and possibly count them in the TT size
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @flags: the flag to चयन
 * @enable: whether to set or unset the flag
 * @count: whether to increase the TT size by the number of changed entries
 */
अटल व्योम batadv_tt_local_set_flags(काष्ठा batadv_priv *bat_priv, u16 flags,
				      bool enable, bool count)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->tt.local_hash;
	काष्ठा batadv_tt_common_entry *tt_common_entry;
	काष्ठा hlist_head *head;
	u32 i;

	अगर (!hash)
		वापस;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(tt_common_entry,
					 head, hash_entry) अणु
			अगर (enable) अणु
				अगर ((tt_common_entry->flags & flags) == flags)
					जारी;
				tt_common_entry->flags |= flags;
			पूर्ण अन्यथा अणु
				अगर (!(tt_common_entry->flags & flags))
					जारी;
				tt_common_entry->flags &= ~flags;
			पूर्ण

			अगर (!count)
				जारी;

			batadv_tt_local_size_inc(bat_priv,
						 tt_common_entry->vid);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण

/* Purge out all the tt local entries marked with BATADV_TT_CLIENT_PENDING */
अटल व्योम batadv_tt_local_purge_pending_clients(काष्ठा batadv_priv *bat_priv)
अणु
	काष्ठा batadv_hashtable *hash = bat_priv->tt.local_hash;
	काष्ठा batadv_tt_common_entry *tt_common;
	काष्ठा batadv_tt_local_entry *tt_local;
	काष्ठा hlist_node *node_पंचांगp;
	काष्ठा hlist_head *head;
	spinlock_t *list_lock; /* protects ग_लिखो access to the hash lists */
	u32 i;

	अगर (!hash)
		वापस;

	क्रम (i = 0; i < hash->size; i++) अणु
		head = &hash->table[i];
		list_lock = &hash->list_locks[i];

		spin_lock_bh(list_lock);
		hlist_क्रम_each_entry_safe(tt_common, node_पंचांगp, head,
					  hash_entry) अणु
			अगर (!(tt_common->flags & BATADV_TT_CLIENT_PENDING))
				जारी;

			batadv_dbg(BATADV_DBG_TT, bat_priv,
				   "Deleting local tt entry (%pM, vid: %d): pending\n",
				   tt_common->addr,
				   batadv_prपूर्णांक_vid(tt_common->vid));

			batadv_tt_local_size_dec(bat_priv, tt_common->vid);
			hlist_del_rcu(&tt_common->hash_entry);
			tt_local = container_of(tt_common,
						काष्ठा batadv_tt_local_entry,
						common);

			batadv_tt_local_entry_put(tt_local);
		पूर्ण
		spin_unlock_bh(list_lock);
	पूर्ण
पूर्ण

/**
 * batadv_tt_local_commit_changes_nolock() - commit all pending local tt changes
 *  which have been queued in the समय since the last commit
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Caller must hold tt->commit_lock.
 */
अटल व्योम batadv_tt_local_commit_changes_nolock(काष्ठा batadv_priv *bat_priv)
अणु
	lockdep_निश्चित_held(&bat_priv->tt.commit_lock);

	अगर (atomic_पढ़ो(&bat_priv->tt.local_changes) < 1) अणु
		अगर (!batadv_atomic_dec_not_zero(&bat_priv->tt.ogm_append_cnt))
			batadv_tt_tvlv_container_update(bat_priv);
		वापस;
	पूर्ण

	batadv_tt_local_set_flags(bat_priv, BATADV_TT_CLIENT_NEW, false, true);

	batadv_tt_local_purge_pending_clients(bat_priv);
	batadv_tt_local_update_crc(bat_priv);

	/* Increment the TTVN only once per OGM पूर्णांकerval */
	atomic_inc(&bat_priv->tt.vn);
	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Local changes committed, updating to ttvn %u\n",
		   (u8)atomic_पढ़ो(&bat_priv->tt.vn));

	/* reset the sending counter */
	atomic_set(&bat_priv->tt.ogm_append_cnt, BATADV_TT_OGM_APPEND_MAX);
	batadv_tt_tvlv_container_update(bat_priv);
पूर्ण

/**
 * batadv_tt_local_commit_changes() - commit all pending local tt changes which
 *  have been queued in the समय since the last commit
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 */
व्योम batadv_tt_local_commit_changes(काष्ठा batadv_priv *bat_priv)
अणु
	spin_lock_bh(&bat_priv->tt.commit_lock);
	batadv_tt_local_commit_changes_nolock(bat_priv);
	spin_unlock_bh(&bat_priv->tt.commit_lock);
पूर्ण

/**
 * batadv_is_ap_isolated() - Check अगर packet from upper layer should be dropped
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @src: source mac address of packet
 * @dst: destination mac address of packet
 * @vid: vlan id of packet
 *
 * Return: true when src+dst(+vid) pair should be isolated, false otherwise
 */
bool batadv_is_ap_isolated(काष्ठा batadv_priv *bat_priv, u8 *src, u8 *dst,
			   अचिन्हित लघु vid)
अणु
	काष्ठा batadv_tt_local_entry *tt_local_entry;
	काष्ठा batadv_tt_global_entry *tt_global_entry;
	काष्ठा batadv_softअगर_vlan *vlan;
	bool ret = false;

	vlan = batadv_softअगर_vlan_get(bat_priv, vid);
	अगर (!vlan)
		वापस false;

	अगर (!atomic_पढ़ो(&vlan->ap_isolation))
		जाओ vlan_put;

	tt_local_entry = batadv_tt_local_hash_find(bat_priv, dst, vid);
	अगर (!tt_local_entry)
		जाओ vlan_put;

	tt_global_entry = batadv_tt_global_hash_find(bat_priv, src, vid);
	अगर (!tt_global_entry)
		जाओ local_entry_put;

	अगर (_batadv_is_ap_isolated(tt_local_entry, tt_global_entry))
		ret = true;

	batadv_tt_global_entry_put(tt_global_entry);
local_entry_put:
	batadv_tt_local_entry_put(tt_local_entry);
vlan_put:
	batadv_softअगर_vlan_put(vlan);
	वापस ret;
पूर्ण

/**
 * batadv_tt_update_orig() - update global translation table with new tt
 *  inक्रमmation received via ogms
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: the orig_node of the ogm
 * @tt_buff: poपूर्णांकer to the first tvlv VLAN entry
 * @tt_num_vlan: number of tvlv VLAN entries
 * @tt_change: poपूर्णांकer to the first entry in the TT buffer
 * @tt_num_changes: number of tt changes inside the tt buffer
 * @ttvn: translation table version number of this changeset
 */
अटल व्योम batadv_tt_update_orig(काष्ठा batadv_priv *bat_priv,
				  काष्ठा batadv_orig_node *orig_node,
				  स्थिर व्योम *tt_buff, u16 tt_num_vlan,
				  काष्ठा batadv_tvlv_tt_change *tt_change,
				  u16 tt_num_changes, u8 ttvn)
अणु
	u8 orig_ttvn = (u8)atomic_पढ़ो(&orig_node->last_ttvn);
	काष्ठा batadv_tvlv_tt_vlan_data *tt_vlan;
	bool full_table = true;
	bool has_tt_init;

	tt_vlan = (काष्ठा batadv_tvlv_tt_vlan_data *)tt_buff;
	has_tt_init = test_bit(BATADV_ORIG_CAPA_HAS_TT,
			       &orig_node->capa_initialized);

	/* orig table not initialised AND first dअगरf is in the OGM OR the ttvn
	 * increased by one -> we can apply the attached changes
	 */
	अगर ((!has_tt_init && ttvn == 1) || ttvn - orig_ttvn == 1) अणु
		/* the OGM could not contain the changes due to their size or
		 * because they have alपढ़ोy been sent BATADV_TT_OGM_APPEND_MAX
		 * बार.
		 * In this हाल send a tt request
		 */
		अगर (!tt_num_changes) अणु
			full_table = false;
			जाओ request_table;
		पूर्ण

		spin_lock_bh(&orig_node->tt_lock);

		batadv_tt_update_changes(bat_priv, orig_node, tt_num_changes,
					 ttvn, tt_change);

		/* Even अगर we received the precomputed crc with the OGM, we
		 * prefer to recompute it to spot any possible inconsistency
		 * in the global table
		 */
		batadv_tt_global_update_crc(bat_priv, orig_node);

		spin_unlock_bh(&orig_node->tt_lock);

		/* The ttvn alone is not enough to guarantee consistency
		 * because a single value could represent dअगरferent states
		 * (due to the wrap around). Thus a node has to check whether
		 * the resulting table (after applying the changes) is still
		 * consistent or not. E.g. a node could disconnect जबतक its
		 * ttvn is X and reconnect on ttvn = X + TTVN_MAX: in this हाल
		 * checking the CRC value is mandatory to detect the
		 * inconsistency
		 */
		अगर (!batadv_tt_global_check_crc(orig_node, tt_vlan,
						tt_num_vlan))
			जाओ request_table;
	पूर्ण अन्यथा अणु
		/* अगर we missed more than one change or our tables are not
		 * in sync anymore -> request fresh tt data
		 */
		अगर (!has_tt_init || ttvn != orig_ttvn ||
		    !batadv_tt_global_check_crc(orig_node, tt_vlan,
						tt_num_vlan)) अणु
request_table:
			batadv_dbg(BATADV_DBG_TT, bat_priv,
				   "TT inconsistency for %pM. Need to retrieve the correct information (ttvn: %u last_ttvn: %u num_changes: %u)\n",
				   orig_node->orig, ttvn, orig_ttvn,
				   tt_num_changes);
			batadv_send_tt_request(bat_priv, orig_node, ttvn,
					       tt_vlan, tt_num_vlan,
					       full_table);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * batadv_tt_global_client_is_roaming() - check अगर a client is marked as roaming
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: the mac address of the client to check
 * @vid: VLAN identअगरier
 *
 * Return: true अगर we know that the client has moved from its old originator
 * to another one. This entry is still kept क्रम consistency purposes and will be
 * deleted later by a DEL or because of समयout
 */
bool batadv_tt_global_client_is_roaming(काष्ठा batadv_priv *bat_priv,
					u8 *addr, अचिन्हित लघु vid)
अणु
	काष्ठा batadv_tt_global_entry *tt_global_entry;
	bool ret = false;

	tt_global_entry = batadv_tt_global_hash_find(bat_priv, addr, vid);
	अगर (!tt_global_entry)
		जाओ out;

	ret = tt_global_entry->common.flags & BATADV_TT_CLIENT_ROAM;
	batadv_tt_global_entry_put(tt_global_entry);
out:
	वापस ret;
पूर्ण

/**
 * batadv_tt_local_client_is_roaming() - tells whether the client is roaming
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: the mac address of the local client to query
 * @vid: VLAN identअगरier
 *
 * Return: true अगर the local client is known to be roaming (it is not served by
 * this node anymore) or not. If yes, the client is still present in the table
 * to keep the latter consistent with the node TTVN
 */
bool batadv_tt_local_client_is_roaming(काष्ठा batadv_priv *bat_priv,
				       u8 *addr, अचिन्हित लघु vid)
अणु
	काष्ठा batadv_tt_local_entry *tt_local_entry;
	bool ret = false;

	tt_local_entry = batadv_tt_local_hash_find(bat_priv, addr, vid);
	अगर (!tt_local_entry)
		जाओ out;

	ret = tt_local_entry->common.flags & BATADV_TT_CLIENT_ROAM;
	batadv_tt_local_entry_put(tt_local_entry);
out:
	वापस ret;
पूर्ण

/**
 * batadv_tt_add_temporary_global_entry() - Add temporary entry to global TT
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig_node: orig node which the temporary entry should be associated with
 * @addr: mac address of the client
 * @vid: VLAN id of the new temporary global translation table
 *
 * Return: true when temporary tt entry could be added, false otherwise
 */
bool batadv_tt_add_temporary_global_entry(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_orig_node *orig_node,
					  स्थिर अचिन्हित अक्षर *addr,
					  अचिन्हित लघु vid)
अणु
	/* ignore loop detect macs, they are not supposed to be in the tt local
	 * data as well.
	 */
	अगर (batadv_bla_is_loopdetect_mac(addr))
		वापस false;

	अगर (!batadv_tt_global_add(bat_priv, orig_node, addr, vid,
				  BATADV_TT_CLIENT_TEMP,
				  atomic_पढ़ो(&orig_node->last_ttvn)))
		वापस false;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Added temporary global client (addr: %pM, vid: %d, orig: %pM)\n",
		   addr, batadv_prपूर्णांक_vid(vid), orig_node->orig);

	वापस true;
पूर्ण

/**
 * batadv_tt_local_reमाप_प्रकारo_mtu() - resize the local translation table fit the
 *  maximum packet size that can be transported through the mesh
 * @soft_अगरace: netdev काष्ठा of the mesh पूर्णांकerface
 *
 * Remove entries older than 'timeout' and half समयout अगर more entries need
 * to be हटाओd.
 */
व्योम batadv_tt_local_reमाप_प्रकारo_mtu(काष्ठा net_device *soft_अगरace)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(soft_अगरace);
	पूर्णांक packet_size_max = atomic_पढ़ो(&bat_priv->packet_size_max);
	पूर्णांक table_size, समयout = BATADV_TT_LOCAL_TIMEOUT / 2;
	bool reduced = false;

	spin_lock_bh(&bat_priv->tt.commit_lock);

	जबतक (true) अणु
		table_size = batadv_tt_local_table_transmit_size(bat_priv);
		अगर (packet_size_max >= table_size)
			अवरोध;

		batadv_tt_local_purge(bat_priv, समयout);
		batadv_tt_local_purge_pending_clients(bat_priv);

		समयout /= 2;
		reduced = true;
		net_ratelimited_function(batadv_info, soft_अगरace,
					 "Forced to purge local tt entries to fit new maximum fragment MTU (%i)\n",
					 packet_size_max);
	पूर्ण

	/* commit these changes immediately, to aव्योम synchronization problem
	 * with the TTVN
	 */
	अगर (reduced)
		batadv_tt_local_commit_changes_nolock(bat_priv);

	spin_unlock_bh(&bat_priv->tt.commit_lock);
पूर्ण

/**
 * batadv_tt_tvlv_ogm_handler_v1() - process incoming tt tvlv container
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @orig: the orig_node of the ogm
 * @flags: flags indicating the tvlv state (see batadv_tvlv_handler_flags)
 * @tvlv_value: tvlv buffer containing the gateway data
 * @tvlv_value_len: tvlv buffer length
 */
अटल व्योम batadv_tt_tvlv_ogm_handler_v1(काष्ठा batadv_priv *bat_priv,
					  काष्ठा batadv_orig_node *orig,
					  u8 flags, व्योम *tvlv_value,
					  u16 tvlv_value_len)
अणु
	काष्ठा batadv_tvlv_tt_vlan_data *tt_vlan;
	काष्ठा batadv_tvlv_tt_change *tt_change;
	काष्ठा batadv_tvlv_tt_data *tt_data;
	u16 num_entries, num_vlan;

	अगर (tvlv_value_len < माप(*tt_data))
		वापस;

	tt_data = (काष्ठा batadv_tvlv_tt_data *)tvlv_value;
	tvlv_value_len -= माप(*tt_data);

	num_vlan = ntohs(tt_data->num_vlan);

	अगर (tvlv_value_len < माप(*tt_vlan) * num_vlan)
		वापस;

	tt_vlan = (काष्ठा batadv_tvlv_tt_vlan_data *)(tt_data + 1);
	tt_change = (काष्ठा batadv_tvlv_tt_change *)(tt_vlan + num_vlan);
	tvlv_value_len -= माप(*tt_vlan) * num_vlan;

	num_entries = batadv_tt_entries(tvlv_value_len);

	batadv_tt_update_orig(bat_priv, orig, tt_vlan, num_vlan, tt_change,
			      num_entries, tt_data->ttvn);
पूर्ण

/**
 * batadv_tt_tvlv_unicast_handler_v1() - process incoming (unicast) tt tvlv
 *  container
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @src: mac address of tt tvlv sender
 * @dst: mac address of tt tvlv recipient
 * @tvlv_value: tvlv buffer containing the tt data
 * @tvlv_value_len: tvlv buffer length
 *
 * Return: NET_RX_DROP अगर the tt tvlv is to be re-routed, NET_RX_SUCCESS
 * otherwise.
 */
अटल पूर्णांक batadv_tt_tvlv_unicast_handler_v1(काष्ठा batadv_priv *bat_priv,
					     u8 *src, u8 *dst,
					     व्योम *tvlv_value,
					     u16 tvlv_value_len)
अणु
	काष्ठा batadv_tvlv_tt_data *tt_data;
	u16 tt_vlan_len, tt_num_entries;
	अक्षर tt_flag;
	bool ret;

	अगर (tvlv_value_len < माप(*tt_data))
		वापस NET_RX_SUCCESS;

	tt_data = (काष्ठा batadv_tvlv_tt_data *)tvlv_value;
	tvlv_value_len -= माप(*tt_data);

	tt_vlan_len = माप(काष्ठा batadv_tvlv_tt_vlan_data);
	tt_vlan_len *= ntohs(tt_data->num_vlan);

	अगर (tvlv_value_len < tt_vlan_len)
		वापस NET_RX_SUCCESS;

	tvlv_value_len -= tt_vlan_len;
	tt_num_entries = batadv_tt_entries(tvlv_value_len);

	चयन (tt_data->flags & BATADV_TT_DATA_TYPE_MASK) अणु
	हाल BATADV_TT_REQUEST:
		batadv_inc_counter(bat_priv, BATADV_CNT_TT_REQUEST_RX);

		/* If this node cannot provide a TT response the tt_request is
		 * क्रमwarded
		 */
		ret = batadv_send_tt_response(bat_priv, tt_data, src, dst);
		अगर (!ret) अणु
			अगर (tt_data->flags & BATADV_TT_FULL_TABLE)
				tt_flag = 'F';
			अन्यथा
				tt_flag = '.';

			batadv_dbg(BATADV_DBG_TT, bat_priv,
				   "Routing TT_REQUEST to %pM [%c]\n",
				   dst, tt_flag);
			/* tvlv API will re-route the packet */
			वापस NET_RX_DROP;
		पूर्ण
		अवरोध;
	हाल BATADV_TT_RESPONSE:
		batadv_inc_counter(bat_priv, BATADV_CNT_TT_RESPONSE_RX);

		अगर (batadv_is_my_mac(bat_priv, dst)) अणु
			batadv_handle_tt_response(bat_priv, tt_data,
						  src, tt_num_entries);
			वापस NET_RX_SUCCESS;
		पूर्ण

		अगर (tt_data->flags & BATADV_TT_FULL_TABLE)
			tt_flag =  'F';
		अन्यथा
			tt_flag = '.';

		batadv_dbg(BATADV_DBG_TT, bat_priv,
			   "Routing TT_RESPONSE to %pM [%c]\n", dst, tt_flag);

		/* tvlv API will re-route the packet */
		वापस NET_RX_DROP;
	पूर्ण

	वापस NET_RX_SUCCESS;
पूर्ण

/**
 * batadv_roam_tvlv_unicast_handler_v1() - process incoming tt roam tvlv
 *  container
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @src: mac address of tt tvlv sender
 * @dst: mac address of tt tvlv recipient
 * @tvlv_value: tvlv buffer containing the tt data
 * @tvlv_value_len: tvlv buffer length
 *
 * Return: NET_RX_DROP अगर the tt roam tvlv is to be re-routed, NET_RX_SUCCESS
 * otherwise.
 */
अटल पूर्णांक batadv_roam_tvlv_unicast_handler_v1(काष्ठा batadv_priv *bat_priv,
					       u8 *src, u8 *dst,
					       व्योम *tvlv_value,
					       u16 tvlv_value_len)
अणु
	काष्ठा batadv_tvlv_roam_adv *roaming_adv;
	काष्ठा batadv_orig_node *orig_node = शून्य;

	/* If this node is not the पूर्णांकended recipient of the
	 * roaming advertisement the packet is क्रमwarded
	 * (the tvlv API will re-route the packet).
	 */
	अगर (!batadv_is_my_mac(bat_priv, dst))
		वापस NET_RX_DROP;

	अगर (tvlv_value_len < माप(*roaming_adv))
		जाओ out;

	orig_node = batadv_orig_hash_find(bat_priv, src);
	अगर (!orig_node)
		जाओ out;

	batadv_inc_counter(bat_priv, BATADV_CNT_TT_ROAM_ADV_RX);
	roaming_adv = (काष्ठा batadv_tvlv_roam_adv *)tvlv_value;

	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Received ROAMING_ADV from %pM (client %pM)\n",
		   src, roaming_adv->client);

	batadv_tt_global_add(bat_priv, orig_node, roaming_adv->client,
			     ntohs(roaming_adv->vid), BATADV_TT_CLIENT_ROAM,
			     atomic_पढ़ो(&orig_node->last_ttvn) + 1);

out:
	अगर (orig_node)
		batadv_orig_node_put(orig_node);
	वापस NET_RX_SUCCESS;
पूर्ण

/**
 * batadv_tt_init() - initialise the translation table पूर्णांकernals
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 *
 * Return: 0 on success or negative error number in हाल of failure.
 */
पूर्णांक batadv_tt_init(काष्ठा batadv_priv *bat_priv)
अणु
	पूर्णांक ret;

	/* synchronized flags must be remote */
	BUILD_BUG_ON(!(BATADV_TT_SYNC_MASK & BATADV_TT_REMOTE_MASK));

	ret = batadv_tt_local_init(bat_priv);
	अगर (ret < 0)
		वापस ret;

	ret = batadv_tt_global_init(bat_priv);
	अगर (ret < 0)
		वापस ret;

	batadv_tvlv_handler_रेजिस्टर(bat_priv, batadv_tt_tvlv_ogm_handler_v1,
				     batadv_tt_tvlv_unicast_handler_v1,
				     BATADV_TVLV_TT, 1, BATADV_NO_FLAGS);

	batadv_tvlv_handler_रेजिस्टर(bat_priv, शून्य,
				     batadv_roam_tvlv_unicast_handler_v1,
				     BATADV_TVLV_ROAM, 1, BATADV_NO_FLAGS);

	INIT_DELAYED_WORK(&bat_priv->tt.work, batadv_tt_purge);
	queue_delayed_work(batadv_event_workqueue, &bat_priv->tt.work,
			   msecs_to_jअगरfies(BATADV_TT_WORK_PERIOD));

	वापस 1;
पूर्ण

/**
 * batadv_tt_global_is_isolated() - check अगर a client is marked as isolated
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @addr: the mac address of the client
 * @vid: the identअगरier of the VLAN where this client is connected
 *
 * Return: true अगर the client is marked with the TT_CLIENT_ISOLA flag, false
 * otherwise
 */
bool batadv_tt_global_is_isolated(काष्ठा batadv_priv *bat_priv,
				  स्थिर u8 *addr, अचिन्हित लघु vid)
अणु
	काष्ठा batadv_tt_global_entry *tt;
	bool ret;

	tt = batadv_tt_global_hash_find(bat_priv, addr, vid);
	अगर (!tt)
		वापस false;

	ret = tt->common.flags & BATADV_TT_CLIENT_ISOLA;

	batadv_tt_global_entry_put(tt);

	वापस ret;
पूर्ण

/**
 * batadv_tt_cache_init() - Initialize tt memory object cache
 *
 * Return: 0 on success or negative error number in हाल of failure.
 */
पूर्णांक __init batadv_tt_cache_init(व्योम)
अणु
	माप_प्रकार tl_size = माप(काष्ठा batadv_tt_local_entry);
	माप_प्रकार tg_size = माप(काष्ठा batadv_tt_global_entry);
	माप_प्रकार tt_orig_size = माप(काष्ठा batadv_tt_orig_list_entry);
	माप_प्रकार tt_change_size = माप(काष्ठा batadv_tt_change_node);
	माप_प्रकार tt_req_size = माप(काष्ठा batadv_tt_req_node);
	माप_प्रकार tt_roam_size = माप(काष्ठा batadv_tt_roam_node);

	batadv_tl_cache = kmem_cache_create("batadv_tl_cache", tl_size, 0,
					    SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!batadv_tl_cache)
		वापस -ENOMEM;

	batadv_tg_cache = kmem_cache_create("batadv_tg_cache", tg_size, 0,
					    SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!batadv_tg_cache)
		जाओ err_tt_tl_destroy;

	batadv_tt_orig_cache = kmem_cache_create("batadv_tt_orig_cache",
						 tt_orig_size, 0,
						 SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!batadv_tt_orig_cache)
		जाओ err_tt_tg_destroy;

	batadv_tt_change_cache = kmem_cache_create("batadv_tt_change_cache",
						   tt_change_size, 0,
						   SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!batadv_tt_change_cache)
		जाओ err_tt_orig_destroy;

	batadv_tt_req_cache = kmem_cache_create("batadv_tt_req_cache",
						tt_req_size, 0,
						SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!batadv_tt_req_cache)
		जाओ err_tt_change_destroy;

	batadv_tt_roam_cache = kmem_cache_create("batadv_tt_roam_cache",
						 tt_roam_size, 0,
						 SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!batadv_tt_roam_cache)
		जाओ err_tt_req_destroy;

	वापस 0;

err_tt_req_destroy:
	kmem_cache_destroy(batadv_tt_req_cache);
	batadv_tt_req_cache = शून्य;
err_tt_change_destroy:
	kmem_cache_destroy(batadv_tt_change_cache);
	batadv_tt_change_cache = शून्य;
err_tt_orig_destroy:
	kmem_cache_destroy(batadv_tt_orig_cache);
	batadv_tt_orig_cache = शून्य;
err_tt_tg_destroy:
	kmem_cache_destroy(batadv_tg_cache);
	batadv_tg_cache = शून्य;
err_tt_tl_destroy:
	kmem_cache_destroy(batadv_tl_cache);
	batadv_tl_cache = शून्य;

	वापस -ENOMEM;
पूर्ण

/**
 * batadv_tt_cache_destroy() - Destroy tt memory object cache
 */
व्योम batadv_tt_cache_destroy(व्योम)
अणु
	kmem_cache_destroy(batadv_tl_cache);
	kmem_cache_destroy(batadv_tg_cache);
	kmem_cache_destroy(batadv_tt_orig_cache);
	kmem_cache_destroy(batadv_tt_change_cache);
	kmem_cache_destroy(batadv_tt_req_cache);
	kmem_cache_destroy(batadv_tt_roam_cache);
पूर्ण
