<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008, 2009 खोलो80211s Ltd.
 * Author:     Luis Carlos Cobo <luisca@cozybit.com>
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/list.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <net/mac80211.h>
#समावेश "wme.h"
#समावेश "ieee80211_i.h"
#समावेश "mesh.h"

अटल व्योम mesh_path_मुक्त_rcu(काष्ठा mesh_table *tbl, काष्ठा mesh_path *mpath);

अटल u32 mesh_table_hash(स्थिर व्योम *addr, u32 len, u32 seed)
अणु
	/* Use last four bytes of hw addr as hash index */
	वापस jhash_1word(__get_unaligned_cpu32((u8 *)addr + 2), seed);
पूर्ण

अटल स्थिर काष्ठा rhashtable_params mesh_rht_params = अणु
	.nelem_hपूर्णांक = 2,
	.स्वतःmatic_shrinking = true,
	.key_len = ETH_ALEN,
	.key_offset = दुरत्व(काष्ठा mesh_path, dst),
	.head_offset = दुरत्व(काष्ठा mesh_path, rhash),
	.hashfn = mesh_table_hash,
पूर्ण;

अटल अंतरभूत bool mpath_expired(काष्ठा mesh_path *mpath)
अणु
	वापस (mpath->flags & MESH_PATH_ACTIVE) &&
	       समय_after(jअगरfies, mpath->exp_समय) &&
	       !(mpath->flags & MESH_PATH_FIXED);
पूर्ण

अटल व्योम mesh_path_rht_मुक्त(व्योम *ptr, व्योम *tblptr)
अणु
	काष्ठा mesh_path *mpath = ptr;
	काष्ठा mesh_table *tbl = tblptr;

	mesh_path_मुक्त_rcu(tbl, mpath);
पूर्ण

अटल काष्ठा mesh_table *mesh_table_alloc(व्योम)
अणु
	काष्ठा mesh_table *newtbl;

	newtbl = kदो_स्मृति(माप(काष्ठा mesh_table), GFP_ATOMIC);
	अगर (!newtbl)
		वापस शून्य;

	INIT_HLIST_HEAD(&newtbl->known_gates);
	INIT_HLIST_HEAD(&newtbl->walk_head);
	atomic_set(&newtbl->entries,  0);
	spin_lock_init(&newtbl->gates_lock);
	spin_lock_init(&newtbl->walk_lock);
	rhashtable_init(&newtbl->rhead, &mesh_rht_params);

	वापस newtbl;
पूर्ण

अटल व्योम mesh_table_मुक्त(काष्ठा mesh_table *tbl)
अणु
	rhashtable_मुक्त_and_destroy(&tbl->rhead,
				    mesh_path_rht_मुक्त, tbl);
	kमुक्त(tbl);
पूर्ण

/**
 * mesh_path_assign_nexthop - update mesh path next hop
 *
 * @mpath: mesh path to update
 * @sta: next hop to assign
 *
 * Locking: mpath->state_lock must be held when calling this function
 */
व्योम mesh_path_assign_nexthop(काष्ठा mesh_path *mpath, काष्ठा sta_info *sta)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *hdr;
	अचिन्हित दीर्घ flags;

	rcu_assign_poपूर्णांकer(mpath->next_hop, sta);

	spin_lock_irqsave(&mpath->frame_queue.lock, flags);
	skb_queue_walk(&mpath->frame_queue, skb) अणु
		hdr = (काष्ठा ieee80211_hdr *) skb->data;
		स_नकल(hdr->addr1, sta->sta.addr, ETH_ALEN);
		स_नकल(hdr->addr2, mpath->sdata->vअगर.addr, ETH_ALEN);
		ieee80211_mps_set_frame_flags(sta->sdata, sta, hdr);
	पूर्ण

	spin_unlock_irqrestore(&mpath->frame_queue.lock, flags);
पूर्ण

अटल व्योम prepare_क्रम_gate(काष्ठा sk_buff *skb, अक्षर *dst_addr,
			     काष्ठा mesh_path *gate_mpath)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ieee80211s_hdr *mshdr;
	पूर्णांक mesh_hdrlen, hdrlen;
	अक्षर *next_hop;

	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	mshdr = (काष्ठा ieee80211s_hdr *) (skb->data + hdrlen);

	अगर (!(mshdr->flags & MESH_FLAGS_AE)) अणु
		/* size of the fixed part of the mesh header */
		mesh_hdrlen = 6;

		/* make room क्रम the two extended addresses */
		skb_push(skb, 2 * ETH_ALEN);
		स_हटाओ(skb->data, hdr, hdrlen + mesh_hdrlen);

		hdr = (काष्ठा ieee80211_hdr *) skb->data;

		/* we preserve the previous mesh header and only add
		 * the new addreses */
		mshdr = (काष्ठा ieee80211s_hdr *) (skb->data + hdrlen);
		mshdr->flags = MESH_FLAGS_AE_A5_A6;
		स_नकल(mshdr->eaddr1, hdr->addr3, ETH_ALEN);
		स_नकल(mshdr->eaddr2, hdr->addr4, ETH_ALEN);
	पूर्ण

	/* update next hop */
	hdr = (काष्ठा ieee80211_hdr *) skb->data;
	rcu_पढ़ो_lock();
	next_hop = rcu_dereference(gate_mpath->next_hop)->sta.addr;
	स_नकल(hdr->addr1, next_hop, ETH_ALEN);
	rcu_पढ़ो_unlock();
	स_नकल(hdr->addr2, gate_mpath->sdata->vअगर.addr, ETH_ALEN);
	स_नकल(hdr->addr3, dst_addr, ETH_ALEN);
पूर्ण

/**
 * mesh_path_move_to_queue - Move or copy frames from one mpath queue to another
 *
 * This function is used to transfer or copy frames from an unresolved mpath to
 * a gate mpath.  The function also adds the Address Extension field and
 * updates the next hop.
 *
 * If a frame alपढ़ोy has an Address Extension field, only the next hop and
 * destination addresses are updated.
 *
 * The gate mpath must be an active mpath with a valid mpath->next_hop.
 *
 * @gate_mpath: An active mpath the frames will be sent to (i.e. the gate)
 * @from_mpath: The failed mpath
 * @copy: When true, copy all the frames to the new mpath queue.  When false,
 * move them.
 */
अटल व्योम mesh_path_move_to_queue(काष्ठा mesh_path *gate_mpath,
				    काष्ठा mesh_path *from_mpath,
				    bool copy)
अणु
	काष्ठा sk_buff *skb, *fskb, *पंचांगp;
	काष्ठा sk_buff_head failq;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(gate_mpath == from_mpath))
		वापस;
	अगर (WARN_ON(!gate_mpath->next_hop))
		वापस;

	__skb_queue_head_init(&failq);

	spin_lock_irqsave(&from_mpath->frame_queue.lock, flags);
	skb_queue_splice_init(&from_mpath->frame_queue, &failq);
	spin_unlock_irqrestore(&from_mpath->frame_queue.lock, flags);

	skb_queue_walk_safe(&failq, fskb, पंचांगp) अणु
		अगर (skb_queue_len(&gate_mpath->frame_queue) >=
				  MESH_FRAME_QUEUE_LEN) अणु
			mpath_dbg(gate_mpath->sdata, "mpath queue full!\n");
			अवरोध;
		पूर्ण

		skb = skb_copy(fskb, GFP_ATOMIC);
		अगर (WARN_ON(!skb))
			अवरोध;

		prepare_क्रम_gate(skb, gate_mpath->dst, gate_mpath);
		skb_queue_tail(&gate_mpath->frame_queue, skb);

		अगर (copy)
			जारी;

		__skb_unlink(fskb, &failq);
		kमुक्त_skb(fskb);
	पूर्ण

	mpath_dbg(gate_mpath->sdata, "Mpath queue for gate %pM has %d frames\n",
		  gate_mpath->dst, skb_queue_len(&gate_mpath->frame_queue));

	अगर (!copy)
		वापस;

	spin_lock_irqsave(&from_mpath->frame_queue.lock, flags);
	skb_queue_splice(&failq, &from_mpath->frame_queue);
	spin_unlock_irqrestore(&from_mpath->frame_queue.lock, flags);
पूर्ण


अटल काष्ठा mesh_path *mpath_lookup(काष्ठा mesh_table *tbl, स्थिर u8 *dst,
				      काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा mesh_path *mpath;

	mpath = rhashtable_lookup(&tbl->rhead, dst, mesh_rht_params);

	अगर (mpath && mpath_expired(mpath)) अणु
		spin_lock_bh(&mpath->state_lock);
		mpath->flags &= ~MESH_PATH_ACTIVE;
		spin_unlock_bh(&mpath->state_lock);
	पूर्ण
	वापस mpath;
पूर्ण

/**
 * mesh_path_lookup - look up a path in the mesh path table
 * @sdata: local subअगर
 * @dst: hardware address (ETH_ALEN length) of destination
 *
 * Returns: poपूर्णांकer to the mesh path काष्ठाure, or शून्य अगर not found
 *
 * Locking: must be called within a पढ़ो rcu section.
 */
काष्ठा mesh_path *
mesh_path_lookup(काष्ठा ieee80211_sub_अगर_data *sdata, स्थिर u8 *dst)
अणु
	वापस mpath_lookup(sdata->u.mesh.mesh_paths, dst, sdata);
पूर्ण

काष्ठा mesh_path *
mpp_path_lookup(काष्ठा ieee80211_sub_अगर_data *sdata, स्थिर u8 *dst)
अणु
	वापस mpath_lookup(sdata->u.mesh.mpp_paths, dst, sdata);
पूर्ण

अटल काष्ठा mesh_path *
__mesh_path_lookup_by_idx(काष्ठा mesh_table *tbl, पूर्णांक idx)
अणु
	पूर्णांक i = 0;
	काष्ठा mesh_path *mpath;

	hlist_क्रम_each_entry_rcu(mpath, &tbl->walk_head, walk_list) अणु
		अगर (i++ == idx)
			अवरोध;
	पूर्ण

	अगर (!mpath)
		वापस शून्य;

	अगर (mpath_expired(mpath)) अणु
		spin_lock_bh(&mpath->state_lock);
		mpath->flags &= ~MESH_PATH_ACTIVE;
		spin_unlock_bh(&mpath->state_lock);
	पूर्ण
	वापस mpath;
पूर्ण

/**
 * mesh_path_lookup_by_idx - look up a path in the mesh path table by its index
 * @idx: index
 * @sdata: local subअगर, or शून्य क्रम all entries
 *
 * Returns: poपूर्णांकer to the mesh path काष्ठाure, or शून्य अगर not found.
 *
 * Locking: must be called within a पढ़ो rcu section.
 */
काष्ठा mesh_path *
mesh_path_lookup_by_idx(काष्ठा ieee80211_sub_अगर_data *sdata, पूर्णांक idx)
अणु
	वापस __mesh_path_lookup_by_idx(sdata->u.mesh.mesh_paths, idx);
पूर्ण

/**
 * mpp_path_lookup_by_idx - look up a path in the proxy path table by its index
 * @idx: index
 * @sdata: local subअगर, or शून्य क्रम all entries
 *
 * Returns: poपूर्णांकer to the proxy path काष्ठाure, or शून्य अगर not found.
 *
 * Locking: must be called within a पढ़ो rcu section.
 */
काष्ठा mesh_path *
mpp_path_lookup_by_idx(काष्ठा ieee80211_sub_अगर_data *sdata, पूर्णांक idx)
अणु
	वापस __mesh_path_lookup_by_idx(sdata->u.mesh.mpp_paths, idx);
पूर्ण

/**
 * mesh_path_add_gate - add the given mpath to a mesh gate to our path table
 * @mpath: gate path to add to table
 */
पूर्णांक mesh_path_add_gate(काष्ठा mesh_path *mpath)
अणु
	काष्ठा mesh_table *tbl;
	पूर्णांक err;

	rcu_पढ़ो_lock();
	tbl = mpath->sdata->u.mesh.mesh_paths;

	spin_lock_bh(&mpath->state_lock);
	अगर (mpath->is_gate) अणु
		err = -EEXIST;
		spin_unlock_bh(&mpath->state_lock);
		जाओ err_rcu;
	पूर्ण
	mpath->is_gate = true;
	mpath->sdata->u.mesh.num_gates++;

	spin_lock(&tbl->gates_lock);
	hlist_add_head_rcu(&mpath->gate_list, &tbl->known_gates);
	spin_unlock(&tbl->gates_lock);

	spin_unlock_bh(&mpath->state_lock);

	mpath_dbg(mpath->sdata,
		  "Mesh path: Recorded new gate: %pM. %d known gates\n",
		  mpath->dst, mpath->sdata->u.mesh.num_gates);
	err = 0;
err_rcu:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

/**
 * mesh_gate_del - हटाओ a mesh gate from the list of known gates
 * @tbl: table which holds our list of known gates
 * @mpath: gate mpath
 */
अटल व्योम mesh_gate_del(काष्ठा mesh_table *tbl, काष्ठा mesh_path *mpath)
अणु
	lockdep_निश्चित_held(&mpath->state_lock);
	अगर (!mpath->is_gate)
		वापस;

	mpath->is_gate = false;
	spin_lock_bh(&tbl->gates_lock);
	hlist_del_rcu(&mpath->gate_list);
	mpath->sdata->u.mesh.num_gates--;
	spin_unlock_bh(&tbl->gates_lock);

	mpath_dbg(mpath->sdata,
		  "Mesh path: Deleted gate: %pM. %d known gates\n",
		  mpath->dst, mpath->sdata->u.mesh.num_gates);
पूर्ण

/**
 * mesh_gate_num - number of gates known to this पूर्णांकerface
 * @sdata: subअगर data
 */
पूर्णांक mesh_gate_num(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	वापस sdata->u.mesh.num_gates;
पूर्ण

अटल
काष्ठा mesh_path *mesh_path_new(काष्ठा ieee80211_sub_अगर_data *sdata,
				स्थिर u8 *dst, gfp_t gfp_flags)
अणु
	काष्ठा mesh_path *new_mpath;

	new_mpath = kzalloc(माप(काष्ठा mesh_path), gfp_flags);
	अगर (!new_mpath)
		वापस शून्य;

	स_नकल(new_mpath->dst, dst, ETH_ALEN);
	eth_broadcast_addr(new_mpath->rann_snd_addr);
	new_mpath->is_root = false;
	new_mpath->sdata = sdata;
	new_mpath->flags = 0;
	skb_queue_head_init(&new_mpath->frame_queue);
	new_mpath->exp_समय = jअगरfies;
	spin_lock_init(&new_mpath->state_lock);
	समयr_setup(&new_mpath->समयr, mesh_path_समयr, 0);

	वापस new_mpath;
पूर्ण

/**
 * mesh_path_add - allocate and add a new path to the mesh path table
 * @dst: destination address of the path (ETH_ALEN length)
 * @sdata: local subअगर
 *
 * Returns: 0 on success
 *
 * State: the initial state of the new path is set to 0
 */
काष्ठा mesh_path *mesh_path_add(काष्ठा ieee80211_sub_अगर_data *sdata,
				स्थिर u8 *dst)
अणु
	काष्ठा mesh_table *tbl;
	काष्ठा mesh_path *mpath, *new_mpath;

	अगर (ether_addr_equal(dst, sdata->vअगर.addr))
		/* never add ourselves as neighbours */
		वापस ERR_PTR(-ENOTSUPP);

	अगर (is_multicast_ether_addr(dst))
		वापस ERR_PTR(-ENOTSUPP);

	अगर (atomic_add_unless(&sdata->u.mesh.mpaths, 1, MESH_MAX_MPATHS) == 0)
		वापस ERR_PTR(-ENOSPC);

	new_mpath = mesh_path_new(sdata, dst, GFP_ATOMIC);
	अगर (!new_mpath)
		वापस ERR_PTR(-ENOMEM);

	tbl = sdata->u.mesh.mesh_paths;
	spin_lock_bh(&tbl->walk_lock);
	mpath = rhashtable_lookup_get_insert_fast(&tbl->rhead,
						  &new_mpath->rhash,
						  mesh_rht_params);
	अगर (!mpath)
		hlist_add_head(&new_mpath->walk_list, &tbl->walk_head);
	spin_unlock_bh(&tbl->walk_lock);

	अगर (mpath) अणु
		kमुक्त(new_mpath);

		अगर (IS_ERR(mpath))
			वापस mpath;

		new_mpath = mpath;
	पूर्ण

	sdata->u.mesh.mesh_paths_generation++;
	वापस new_mpath;
पूर्ण

पूर्णांक mpp_path_add(काष्ठा ieee80211_sub_अगर_data *sdata,
		 स्थिर u8 *dst, स्थिर u8 *mpp)
अणु
	काष्ठा mesh_table *tbl;
	काष्ठा mesh_path *new_mpath;
	पूर्णांक ret;

	अगर (ether_addr_equal(dst, sdata->vअगर.addr))
		/* never add ourselves as neighbours */
		वापस -ENOTSUPP;

	अगर (is_multicast_ether_addr(dst))
		वापस -ENOTSUPP;

	new_mpath = mesh_path_new(sdata, dst, GFP_ATOMIC);

	अगर (!new_mpath)
		वापस -ENOMEM;

	स_नकल(new_mpath->mpp, mpp, ETH_ALEN);
	tbl = sdata->u.mesh.mpp_paths;

	spin_lock_bh(&tbl->walk_lock);
	ret = rhashtable_lookup_insert_fast(&tbl->rhead,
					    &new_mpath->rhash,
					    mesh_rht_params);
	अगर (!ret)
		hlist_add_head_rcu(&new_mpath->walk_list, &tbl->walk_head);
	spin_unlock_bh(&tbl->walk_lock);

	अगर (ret)
		kमुक्त(new_mpath);

	sdata->u.mesh.mpp_paths_generation++;
	वापस ret;
पूर्ण


/**
 * mesh_plink_broken - deactivates paths and sends perr when a link अवरोधs
 *
 * @sta: broken peer link
 *
 * This function must be called from the rate control algorithm अगर enough
 * delivery errors suggest that a peer link is no दीर्घer usable.
 */
व्योम mesh_plink_broken(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा mesh_table *tbl = sdata->u.mesh.mesh_paths;
	अटल स्थिर u8 bcast[ETH_ALEN] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
	काष्ठा mesh_path *mpath;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(mpath, &tbl->walk_head, walk_list) अणु
		अगर (rcu_access_poपूर्णांकer(mpath->next_hop) == sta &&
		    mpath->flags & MESH_PATH_ACTIVE &&
		    !(mpath->flags & MESH_PATH_FIXED)) अणु
			spin_lock_bh(&mpath->state_lock);
			mpath->flags &= ~MESH_PATH_ACTIVE;
			++mpath->sn;
			spin_unlock_bh(&mpath->state_lock);
			mesh_path_error_tx(sdata,
				sdata->u.mesh.mshcfg.element_ttl,
				mpath->dst, mpath->sn,
				WLAN_REASON_MESH_PATH_DEST_UNREACHABLE, bcast);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम mesh_path_मुक्त_rcu(काष्ठा mesh_table *tbl,
			       काष्ठा mesh_path *mpath)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = mpath->sdata;

	spin_lock_bh(&mpath->state_lock);
	mpath->flags |= MESH_PATH_RESOLVING | MESH_PATH_DELETED;
	mesh_gate_del(tbl, mpath);
	spin_unlock_bh(&mpath->state_lock);
	del_समयr_sync(&mpath->समयr);
	atomic_dec(&sdata->u.mesh.mpaths);
	atomic_dec(&tbl->entries);
	mesh_path_flush_pending(mpath);
	kमुक्त_rcu(mpath, rcu);
पूर्ण

अटल व्योम __mesh_path_del(काष्ठा mesh_table *tbl, काष्ठा mesh_path *mpath)
अणु
	hlist_del_rcu(&mpath->walk_list);
	rhashtable_हटाओ_fast(&tbl->rhead, &mpath->rhash, mesh_rht_params);
	mesh_path_मुक्त_rcu(tbl, mpath);
पूर्ण

/**
 * mesh_path_flush_by_nexthop - Deletes mesh paths अगर their next hop matches
 *
 * @sta: mesh peer to match
 *
 * RCU notes: this function is called when a mesh plink transitions from
 * PLINK_ESTAB to any other state, since PLINK_ESTAB state is the only one that
 * allows path creation. This will happen beक्रमe the sta can be मुक्तd (because
 * sta_info_destroy() calls this) so any पढ़ोer in a rcu पढ़ो block will be
 * रक्षित against the plink disappearing.
 */
व्योम mesh_path_flush_by_nexthop(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा mesh_table *tbl = sdata->u.mesh.mesh_paths;
	काष्ठा mesh_path *mpath;
	काष्ठा hlist_node *n;

	spin_lock_bh(&tbl->walk_lock);
	hlist_क्रम_each_entry_safe(mpath, n, &tbl->walk_head, walk_list) अणु
		अगर (rcu_access_poपूर्णांकer(mpath->next_hop) == sta)
			__mesh_path_del(tbl, mpath);
	पूर्ण
	spin_unlock_bh(&tbl->walk_lock);
पूर्ण

अटल व्योम mpp_flush_by_proxy(काष्ठा ieee80211_sub_अगर_data *sdata,
			       स्थिर u8 *proxy)
अणु
	काष्ठा mesh_table *tbl = sdata->u.mesh.mpp_paths;
	काष्ठा mesh_path *mpath;
	काष्ठा hlist_node *n;

	spin_lock_bh(&tbl->walk_lock);
	hlist_क्रम_each_entry_safe(mpath, n, &tbl->walk_head, walk_list) अणु
		अगर (ether_addr_equal(mpath->mpp, proxy))
			__mesh_path_del(tbl, mpath);
	पूर्ण
	spin_unlock_bh(&tbl->walk_lock);
पूर्ण

अटल व्योम table_flush_by_अगरace(काष्ठा mesh_table *tbl)
अणु
	काष्ठा mesh_path *mpath;
	काष्ठा hlist_node *n;

	spin_lock_bh(&tbl->walk_lock);
	hlist_क्रम_each_entry_safe(mpath, n, &tbl->walk_head, walk_list) अणु
		__mesh_path_del(tbl, mpath);
	पूर्ण
	spin_unlock_bh(&tbl->walk_lock);
पूर्ण

/**
 * mesh_path_flush_by_अगरace - Deletes all mesh paths associated with a given अगरace
 *
 * This function deletes both mesh paths as well as mesh portal paths.
 *
 * @sdata: पूर्णांकerface data to match
 *
 */
व्योम mesh_path_flush_by_अगरace(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	table_flush_by_अगरace(sdata->u.mesh.mesh_paths);
	table_flush_by_अगरace(sdata->u.mesh.mpp_paths);
पूर्ण

/**
 * table_path_del - delete a path from the mesh or mpp table
 *
 * @tbl: mesh or mpp path table
 * @sdata: local subअगर
 * @addr: dst address (ETH_ALEN length)
 *
 * Returns: 0 अगर successful
 */
अटल पूर्णांक table_path_del(काष्ठा mesh_table *tbl,
			  काष्ठा ieee80211_sub_अगर_data *sdata,
			  स्थिर u8 *addr)
अणु
	काष्ठा mesh_path *mpath;

	spin_lock_bh(&tbl->walk_lock);
	mpath = rhashtable_lookup_fast(&tbl->rhead, addr, mesh_rht_params);
	अगर (!mpath) अणु
		spin_unlock_bh(&tbl->walk_lock);
		वापस -ENXIO;
	पूर्ण

	__mesh_path_del(tbl, mpath);
	spin_unlock_bh(&tbl->walk_lock);
	वापस 0;
पूर्ण


/**
 * mesh_path_del - delete a mesh path from the table
 *
 * @addr: dst address (ETH_ALEN length)
 * @sdata: local subअगर
 *
 * Returns: 0 अगर successful
 */
पूर्णांक mesh_path_del(काष्ठा ieee80211_sub_अगर_data *sdata, स्थिर u8 *addr)
अणु
	पूर्णांक err;

	/* flush relevant mpp entries first */
	mpp_flush_by_proxy(sdata, addr);

	err = table_path_del(sdata->u.mesh.mesh_paths, sdata, addr);
	sdata->u.mesh.mesh_paths_generation++;
	वापस err;
पूर्ण

/**
 * mesh_path_tx_pending - sends pending frames in a mesh path queue
 *
 * @mpath: mesh path to activate
 *
 * Locking: the state_lock of the mpath काष्ठाure must NOT be held when calling
 * this function.
 */
व्योम mesh_path_tx_pending(काष्ठा mesh_path *mpath)
अणु
	अगर (mpath->flags & MESH_PATH_ACTIVE)
		ieee80211_add_pending_skbs(mpath->sdata->local,
				&mpath->frame_queue);
पूर्ण

/**
 * mesh_path_send_to_gates - sends pending frames to all known mesh gates
 *
 * @mpath: mesh path whose queue will be emptied
 *
 * If there is only one gate, the frames are transferred from the failed mpath
 * queue to that gate's queue.  If there are more than one gates, the frames
 * are copied from each gate to the next.  After frames are copied, the
 * mpath queues are emptied onto the transmission queue.
 */
पूर्णांक mesh_path_send_to_gates(काष्ठा mesh_path *mpath)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = mpath->sdata;
	काष्ठा mesh_table *tbl;
	काष्ठा mesh_path *from_mpath = mpath;
	काष्ठा mesh_path *gate;
	bool copy = false;

	tbl = sdata->u.mesh.mesh_paths;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(gate, &tbl->known_gates, gate_list) अणु
		अगर (gate->flags & MESH_PATH_ACTIVE) अणु
			mpath_dbg(sdata, "Forwarding to %pM\n", gate->dst);
			mesh_path_move_to_queue(gate, from_mpath, copy);
			from_mpath = gate;
			copy = true;
		पूर्ण अन्यथा अणु
			mpath_dbg(sdata,
				  "Not forwarding to %pM (flags %#x)\n",
				  gate->dst, gate->flags);
		पूर्ण
	पूर्ण

	hlist_क्रम_each_entry_rcu(gate, &tbl->known_gates, gate_list) अणु
		mpath_dbg(sdata, "Sending to %pM\n", gate->dst);
		mesh_path_tx_pending(gate);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस (from_mpath == mpath) ? -EHOSTUNREACH : 0;
पूर्ण

/**
 * mesh_path_discard_frame - discard a frame whose path could not be resolved
 *
 * @skb: frame to discard
 * @sdata: network subअगर the frame was to be sent through
 *
 * Locking: the function must me called within a rcu_पढ़ो_lock region
 */
व्योम mesh_path_discard_frame(काष्ठा ieee80211_sub_अगर_data *sdata,
			     काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
	sdata->u.mesh.mshstats.dropped_frames_no_route++;
पूर्ण

/**
 * mesh_path_flush_pending - मुक्त the pending queue of a mesh path
 *
 * @mpath: mesh path whose queue has to be मुक्तd
 *
 * Locking: the function must me called within a rcu_पढ़ो_lock region
 */
व्योम mesh_path_flush_pending(काष्ठा mesh_path *mpath)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&mpath->frame_queue)) != शून्य)
		mesh_path_discard_frame(mpath->sdata, skb);
पूर्ण

/**
 * mesh_path_fix_nexthop - क्रमce a specअगरic next hop क्रम a mesh path
 *
 * @mpath: the mesh path to modअगरy
 * @next_hop: the next hop to क्रमce
 *
 * Locking: this function must be called holding mpath->state_lock
 */
व्योम mesh_path_fix_nexthop(काष्ठा mesh_path *mpath, काष्ठा sta_info *next_hop)
अणु
	spin_lock_bh(&mpath->state_lock);
	mesh_path_assign_nexthop(mpath, next_hop);
	mpath->sn = 0xffff;
	mpath->metric = 0;
	mpath->hop_count = 0;
	mpath->exp_समय = 0;
	mpath->flags = MESH_PATH_FIXED | MESH_PATH_SN_VALID;
	mesh_path_activate(mpath);
	spin_unlock_bh(&mpath->state_lock);
	ewma_mesh_fail_avg_init(&next_hop->mesh->fail_avg);
	/* init it at a low value - 0 start is tricky */
	ewma_mesh_fail_avg_add(&next_hop->mesh->fail_avg, 1);
	mesh_path_tx_pending(mpath);
पूर्ण

पूर्णांक mesh_pathtbl_init(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा mesh_table *tbl_path, *tbl_mpp;
	पूर्णांक ret;

	tbl_path = mesh_table_alloc();
	अगर (!tbl_path)
		वापस -ENOMEM;

	tbl_mpp = mesh_table_alloc();
	अगर (!tbl_mpp) अणु
		ret = -ENOMEM;
		जाओ मुक्त_path;
	पूर्ण

	sdata->u.mesh.mesh_paths = tbl_path;
	sdata->u.mesh.mpp_paths = tbl_mpp;

	वापस 0;

मुक्त_path:
	mesh_table_मुक्त(tbl_path);
	वापस ret;
पूर्ण

अटल
व्योम mesh_path_tbl_expire(काष्ठा ieee80211_sub_अगर_data *sdata,
			  काष्ठा mesh_table *tbl)
अणु
	काष्ठा mesh_path *mpath;
	काष्ठा hlist_node *n;

	spin_lock_bh(&tbl->walk_lock);
	hlist_क्रम_each_entry_safe(mpath, n, &tbl->walk_head, walk_list) अणु
		अगर ((!(mpath->flags & MESH_PATH_RESOLVING)) &&
		    (!(mpath->flags & MESH_PATH_FIXED)) &&
		     समय_after(jअगरfies, mpath->exp_समय + MESH_PATH_EXPIRE))
			__mesh_path_del(tbl, mpath);
	पूर्ण
	spin_unlock_bh(&tbl->walk_lock);
पूर्ण

व्योम mesh_path_expire(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	mesh_path_tbl_expire(sdata, sdata->u.mesh.mesh_paths);
	mesh_path_tbl_expire(sdata, sdata->u.mesh.mpp_paths);
पूर्ण

व्योम mesh_pathtbl_unरेजिस्टर(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	mesh_table_मुक्त(sdata->u.mesh.mesh_paths);
	mesh_table_मुक्त(sdata->u.mesh.mpp_paths);
पूर्ण
