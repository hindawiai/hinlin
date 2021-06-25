<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/sort.h>
#समावेश <linux/slab.h>
#समावेश <linux/iversion.h>
#समावेश "super.h"
#समावेश "mds_client.h"
#समावेश <linux/ceph/decode.h>

/* unused map expires after 5 minutes */
#घोषणा CEPH_SNAPID_MAP_TIMEOUT	(5 * 60 * HZ)

/*
 * Snapshots in ceph are driven in large part by cooperation from the
 * client.  In contrast to local file प्रणालीs or file servers that
 * implement snapshots at a single poपूर्णांक in the प्रणाली, ceph's
 * distributed access to storage requires clients to help decide
 * whether a ग_लिखो logically occurs beक्रमe or after a recently created
 * snapshot.
 *
 * This provides a perfect instantanous client-wide snapshot.  Between
 * clients, however, snapshots may appear to be applied at slightly
 * dअगरferent poपूर्णांकs in समय, depending on delays in delivering the
 * snapshot notअगरication.
 *
 * Snapshots are _not_ file प्रणाली-wide.  Instead, each snapshot
 * applies to the subdirectory nested beneath some directory.  This
 * effectively भागides the hierarchy पूर्णांकo multiple "realms," where all
 * of the files contained by each realm share the same set of
 * snapshots.  An inभागidual realm's snap set contains snapshots
 * explicitly created on that realm, as well as any snaps in its
 * parent's snap set _after_ the point at which the parent became it's
 * parent (due to, say, a नाम).  Similarly, snaps from prior parents
 * during the समय पूर्णांकervals during which they were the parent are included.
 *
 * The client is spared most of this detail, क्रमtunately... it must only
 * मुख्यtains a hierarchy of realms reflecting the current parent/child
 * realm relationship, and क्रम each realm has an explicit list of snaps
 * inherited from prior parents.
 *
 * A snap_realm काष्ठा is मुख्यtained क्रम realms containing every inode
 * with an खोलो cap in the प्रणाली.  (The needed snap realm inक्रमmation is
 * provided by the MDS whenever a cap is issued, i.e., on खोलो.)  A 'seq'
 * version number is used to ensure that as realm parameters change (new
 * snapshot, new parent, etc.) the client's realm hierarchy is updated.
 *
 * The realm hierarchy drives the generation of a 'snap context' क्रम each
 * realm, which simply lists the resulting set of snaps क्रम the realm.  This
 * is attached to any ग_लिखोs sent to OSDs.
 */
/*
 * Unक्रमtunately error handling is a bit mixed here.  If we get a snap
 * update, but करोn't have enough memory to update our realm hierarchy,
 * it's not clear what we can करो about it (besides complaining to the
 * console).
 */


/*
 * increase ref count क्रम the realm
 *
 * caller must hold snap_rwsem क्रम ग_लिखो.
 */
व्योम ceph_get_snap_realm(काष्ठा ceph_mds_client *mdsc,
			 काष्ठा ceph_snap_realm *realm)
अणु
	करोut("get_realm %p %d -> %d\n", realm,
	     atomic_पढ़ो(&realm->nref), atomic_पढ़ो(&realm->nref)+1);
	/*
	 * since we _only_ increment realm refs or empty the empty
	 * list with snap_rwsem held, adjusting the empty list here is
	 * safe.  we करो need to protect against concurrent empty list
	 * additions, however.
	 */
	अगर (atomic_inc_वापस(&realm->nref) == 1) अणु
		spin_lock(&mdsc->snap_empty_lock);
		list_del_init(&realm->empty_item);
		spin_unlock(&mdsc->snap_empty_lock);
	पूर्ण
पूर्ण

अटल व्योम __insert_snap_realm(काष्ठा rb_root *root,
				काष्ठा ceph_snap_realm *new)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा ceph_snap_realm *r = शून्य;

	जबतक (*p) अणु
		parent = *p;
		r = rb_entry(parent, काष्ठा ceph_snap_realm, node);
		अगर (new->ino < r->ino)
			p = &(*p)->rb_left;
		अन्यथा अगर (new->ino > r->ino)
			p = &(*p)->rb_right;
		अन्यथा
			BUG();
	पूर्ण

	rb_link_node(&new->node, parent, p);
	rb_insert_color(&new->node, root);
पूर्ण

/*
 * create and get the realm rooted at @ino and bump its ref count.
 *
 * caller must hold snap_rwsem क्रम ग_लिखो.
 */
अटल काष्ठा ceph_snap_realm *ceph_create_snap_realm(
	काष्ठा ceph_mds_client *mdsc,
	u64 ino)
अणु
	काष्ठा ceph_snap_realm *realm;

	realm = kzalloc(माप(*realm), GFP_NOFS);
	अगर (!realm)
		वापस ERR_PTR(-ENOMEM);

	atomic_set(&realm->nref, 1);    /* क्रम caller */
	realm->ino = ino;
	INIT_LIST_HEAD(&realm->children);
	INIT_LIST_HEAD(&realm->child_item);
	INIT_LIST_HEAD(&realm->empty_item);
	INIT_LIST_HEAD(&realm->dirty_item);
	INIT_LIST_HEAD(&realm->inodes_with_caps);
	spin_lock_init(&realm->inodes_with_caps_lock);
	__insert_snap_realm(&mdsc->snap_realms, realm);
	mdsc->num_snap_realms++;

	करोut("create_snap_realm %llx %p\n", realm->ino, realm);
	वापस realm;
पूर्ण

/*
 * lookup the realm rooted at @ino.
 *
 * caller must hold snap_rwsem क्रम ग_लिखो.
 */
अटल काष्ठा ceph_snap_realm *__lookup_snap_realm(काष्ठा ceph_mds_client *mdsc,
						   u64 ino)
अणु
	काष्ठा rb_node *n = mdsc->snap_realms.rb_node;
	काष्ठा ceph_snap_realm *r;

	जबतक (n) अणु
		r = rb_entry(n, काष्ठा ceph_snap_realm, node);
		अगर (ino < r->ino)
			n = n->rb_left;
		अन्यथा अगर (ino > r->ino)
			n = n->rb_right;
		अन्यथा अणु
			करोut("lookup_snap_realm %llx %p\n", r->ino, r);
			वापस r;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा ceph_snap_realm *ceph_lookup_snap_realm(काष्ठा ceph_mds_client *mdsc,
					       u64 ino)
अणु
	काष्ठा ceph_snap_realm *r;
	r = __lookup_snap_realm(mdsc, ino);
	अगर (r)
		ceph_get_snap_realm(mdsc, r);
	वापस r;
पूर्ण

अटल व्योम __put_snap_realm(काष्ठा ceph_mds_client *mdsc,
			     काष्ठा ceph_snap_realm *realm);

/*
 * called with snap_rwsem (ग_लिखो)
 */
अटल व्योम __destroy_snap_realm(काष्ठा ceph_mds_client *mdsc,
				 काष्ठा ceph_snap_realm *realm)
अणु
	करोut("__destroy_snap_realm %p %llx\n", realm, realm->ino);

	rb_erase(&realm->node, &mdsc->snap_realms);
	mdsc->num_snap_realms--;

	अगर (realm->parent) अणु
		list_del_init(&realm->child_item);
		__put_snap_realm(mdsc, realm->parent);
	पूर्ण

	kमुक्त(realm->prior_parent_snaps);
	kमुक्त(realm->snaps);
	ceph_put_snap_context(realm->cached_context);
	kमुक्त(realm);
पूर्ण

/*
 * caller holds snap_rwsem (ग_लिखो)
 */
अटल व्योम __put_snap_realm(काष्ठा ceph_mds_client *mdsc,
			     काष्ठा ceph_snap_realm *realm)
अणु
	करोut("__put_snap_realm %llx %p %d -> %d\n", realm->ino, realm,
	     atomic_पढ़ो(&realm->nref), atomic_पढ़ो(&realm->nref)-1);
	अगर (atomic_dec_and_test(&realm->nref))
		__destroy_snap_realm(mdsc, realm);
पूर्ण

/*
 * caller needn't hold any locks
 */
व्योम ceph_put_snap_realm(काष्ठा ceph_mds_client *mdsc,
			 काष्ठा ceph_snap_realm *realm)
अणु
	करोut("put_snap_realm %llx %p %d -> %d\n", realm->ino, realm,
	     atomic_पढ़ो(&realm->nref), atomic_पढ़ो(&realm->nref)-1);
	अगर (!atomic_dec_and_test(&realm->nref))
		वापस;

	अगर (करोwn_ग_लिखो_trylock(&mdsc->snap_rwsem)) अणु
		__destroy_snap_realm(mdsc, realm);
		up_ग_लिखो(&mdsc->snap_rwsem);
	पूर्ण अन्यथा अणु
		spin_lock(&mdsc->snap_empty_lock);
		list_add(&realm->empty_item, &mdsc->snap_empty);
		spin_unlock(&mdsc->snap_empty_lock);
	पूर्ण
पूर्ण

/*
 * Clean up any realms whose ref counts have dropped to zero.  Note
 * that this करोes not include realms who were created but not yet
 * used.
 *
 * Called under snap_rwsem (ग_लिखो)
 */
अटल व्योम __cleanup_empty_realms(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_snap_realm *realm;

	spin_lock(&mdsc->snap_empty_lock);
	जबतक (!list_empty(&mdsc->snap_empty)) अणु
		realm = list_first_entry(&mdsc->snap_empty,
				   काष्ठा ceph_snap_realm, empty_item);
		list_del(&realm->empty_item);
		spin_unlock(&mdsc->snap_empty_lock);
		__destroy_snap_realm(mdsc, realm);
		spin_lock(&mdsc->snap_empty_lock);
	पूर्ण
	spin_unlock(&mdsc->snap_empty_lock);
पूर्ण

व्योम ceph_cleanup_empty_realms(काष्ठा ceph_mds_client *mdsc)
अणु
	करोwn_ग_लिखो(&mdsc->snap_rwsem);
	__cleanup_empty_realms(mdsc);
	up_ग_लिखो(&mdsc->snap_rwsem);
पूर्ण

/*
 * adjust the parent realm of a given @realm.  adjust child list, and parent
 * poपूर्णांकers, and ref counts appropriately.
 *
 * वापस true अगर parent was changed, 0 अगर unchanged, <0 on error.
 *
 * caller must hold snap_rwsem क्रम ग_लिखो.
 */
अटल पूर्णांक adjust_snap_realm_parent(काष्ठा ceph_mds_client *mdsc,
				    काष्ठा ceph_snap_realm *realm,
				    u64 parentino)
अणु
	काष्ठा ceph_snap_realm *parent;

	अगर (realm->parent_ino == parentino)
		वापस 0;

	parent = ceph_lookup_snap_realm(mdsc, parentino);
	अगर (!parent) अणु
		parent = ceph_create_snap_realm(mdsc, parentino);
		अगर (IS_ERR(parent))
			वापस PTR_ERR(parent);
	पूर्ण
	करोut("adjust_snap_realm_parent %llx %p: %llx %p -> %llx %p\n",
	     realm->ino, realm, realm->parent_ino, realm->parent,
	     parentino, parent);
	अगर (realm->parent) अणु
		list_del_init(&realm->child_item);
		ceph_put_snap_realm(mdsc, realm->parent);
	पूर्ण
	realm->parent_ino = parentino;
	realm->parent = parent;
	list_add(&realm->child_item, &parent->children);
	वापस 1;
पूर्ण


अटल पूर्णांक cmpu64_rev(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	अगर (*(u64 *)a < *(u64 *)b)
		वापस 1;
	अगर (*(u64 *)a > *(u64 *)b)
		वापस -1;
	वापस 0;
पूर्ण


/*
 * build the snap context क्रम a given realm.
 */
अटल पूर्णांक build_snap_context(काष्ठा ceph_snap_realm *realm,
			      काष्ठा list_head* dirty_realms)
अणु
	काष्ठा ceph_snap_realm *parent = realm->parent;
	काष्ठा ceph_snap_context *snapc;
	पूर्णांक err = 0;
	u32 num = realm->num_prior_parent_snaps + realm->num_snaps;

	/*
	 * build parent context, अगर it hasn't been built.
	 * conservatively estimate that all parent snaps might be
	 * included by us.
	 */
	अगर (parent) अणु
		अगर (!parent->cached_context) अणु
			err = build_snap_context(parent, dirty_realms);
			अगर (err)
				जाओ fail;
		पूर्ण
		num += parent->cached_context->num_snaps;
	पूर्ण

	/* करो i actually need to update?  not अगर my context seq
	   matches realm seq, and my parents' करोes to.  (this works
	   because we rebuild_snap_realms() works _करोwnward_ in
	   hierarchy after each update.) */
	अगर (realm->cached_context &&
	    realm->cached_context->seq == realm->seq &&
	    (!parent ||
	     realm->cached_context->seq >= parent->cached_context->seq)) अणु
		करोut("build_snap_context %llx %p: %p seq %lld (%u snaps)"
		     " (unchanged)\n",
		     realm->ino, realm, realm->cached_context,
		     realm->cached_context->seq,
		     (अचिन्हित पूर्णांक)realm->cached_context->num_snaps);
		वापस 0;
	पूर्ण

	/* alloc new snap context */
	err = -ENOMEM;
	अगर (num > (SIZE_MAX - माप(*snapc)) / माप(u64))
		जाओ fail;
	snapc = ceph_create_snap_context(num, GFP_NOFS);
	अगर (!snapc)
		जाओ fail;

	/* build (reverse sorted) snap vector */
	num = 0;
	snapc->seq = realm->seq;
	अगर (parent) अणु
		u32 i;

		/* include any of parent's snaps occurring _after_ my
		   parent became my parent */
		क्रम (i = 0; i < parent->cached_context->num_snaps; i++)
			अगर (parent->cached_context->snaps[i] >=
			    realm->parent_since)
				snapc->snaps[num++] =
					parent->cached_context->snaps[i];
		अगर (parent->cached_context->seq > snapc->seq)
			snapc->seq = parent->cached_context->seq;
	पूर्ण
	स_नकल(snapc->snaps + num, realm->snaps,
	       माप(u64)*realm->num_snaps);
	num += realm->num_snaps;
	स_नकल(snapc->snaps + num, realm->prior_parent_snaps,
	       माप(u64)*realm->num_prior_parent_snaps);
	num += realm->num_prior_parent_snaps;

	sort(snapc->snaps, num, माप(u64), cmpu64_rev, शून्य);
	snapc->num_snaps = num;
	करोut("build_snap_context %llx %p: %p seq %lld (%u snaps)\n",
	     realm->ino, realm, snapc, snapc->seq,
	     (अचिन्हित पूर्णांक) snapc->num_snaps);

	ceph_put_snap_context(realm->cached_context);
	realm->cached_context = snapc;
	/* queue realm क्रम cap_snap creation */
	list_add_tail(&realm->dirty_item, dirty_realms);
	वापस 0;

fail:
	/*
	 * अगर we fail, clear old (incorrect) cached_context... hopefully
	 * we'll have better luck building it later
	 */
	अगर (realm->cached_context) अणु
		ceph_put_snap_context(realm->cached_context);
		realm->cached_context = शून्य;
	पूर्ण
	pr_err("build_snap_context %llx %p fail %d\n", realm->ino,
	       realm, err);
	वापस err;
पूर्ण

/*
 * rebuild snap context क्रम the given realm and all of its children.
 */
अटल व्योम rebuild_snap_realms(काष्ठा ceph_snap_realm *realm,
				काष्ठा list_head *dirty_realms)
अणु
	काष्ठा ceph_snap_realm *child;

	करोut("rebuild_snap_realms %llx %p\n", realm->ino, realm);
	build_snap_context(realm, dirty_realms);

	list_क्रम_each_entry(child, &realm->children, child_item)
		rebuild_snap_realms(child, dirty_realms);
पूर्ण


/*
 * helper to allocate and decode an array of snapids.  मुक्त prior
 * instance, अगर any.
 */
अटल पूर्णांक dup_array(u64 **dst, __le64 *src, u32 num)
अणु
	u32 i;

	kमुक्त(*dst);
	अगर (num) अणु
		*dst = kसुस्मृति(num, माप(u64), GFP_NOFS);
		अगर (!*dst)
			वापस -ENOMEM;
		क्रम (i = 0; i < num; i++)
			(*dst)[i] = get_unaligned_le64(src + i);
	पूर्ण अन्यथा अणु
		*dst = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool has_new_snaps(काष्ठा ceph_snap_context *o,
			  काष्ठा ceph_snap_context *n)
अणु
	अगर (n->num_snaps == 0)
		वापस false;
	/* snaps are in descending order */
	वापस n->snaps[0] > o->seq;
पूर्ण

/*
 * When a snapshot is applied, the size/mसमय inode metadata is queued
 * in a ceph_cap_snap (one क्रम each snapshot) until ग_लिखोback
 * completes and the metadata can be flushed back to the MDS.
 *
 * However, अगर a (sync) ग_लिखो is currently in-progress when we apply
 * the snapshot, we have to रुको until the ग_लिखो succeeds or fails
 * (and a final size/mसमय is known).  In this हाल the
 * cap_snap->writing = 1, and is said to be "pending."  When the ग_लिखो
 * finishes, we __ceph_finish_cap_snap().
 *
 * Caller must hold snap_rwsem क्रम पढ़ो (i.e., the realm topology won't
 * change).
 */
व्योम ceph_queue_cap_snap(काष्ठा ceph_inode_info *ci)
अणु
	काष्ठा inode *inode = &ci->vfs_inode;
	काष्ठा ceph_cap_snap *capsnap;
	काष्ठा ceph_snap_context *old_snapc, *new_snapc;
	काष्ठा ceph_buffer *old_blob = शून्य;
	पूर्णांक used, dirty;

	capsnap = kzalloc(माप(*capsnap), GFP_NOFS);
	अगर (!capsnap) अणु
		pr_err("ENOMEM allocating ceph_cap_snap on %p\n", inode);
		वापस;
	पूर्ण

	spin_lock(&ci->i_ceph_lock);
	used = __ceph_caps_used(ci);
	dirty = __ceph_caps_dirty(ci);

	old_snapc = ci->i_head_snapc;
	new_snapc = ci->i_snap_realm->cached_context;

	/*
	 * If there is a ग_लिखो in progress, treat that as a dirty Fw,
	 * even though it hasn't completed yet; by the समय we finish
	 * up this capsnap it will be.
	 */
	अगर (used & CEPH_CAP_खाता_WR)
		dirty |= CEPH_CAP_खाता_WR;

	अगर (__ceph_have_pending_cap_snap(ci)) अणु
		/* there is no poपूर्णांक in queuing multiple "pending" cap_snaps,
		   as no new ग_लिखोs are allowed to start when pending, so any
		   ग_लिखोs in progress now were started beक्रमe the previous
		   cap_snap.  lucky us. */
		करोut("queue_cap_snap %p already pending\n", inode);
		जाओ update_snapc;
	पूर्ण
	अगर (ci->i_wrbuffer_ref_head == 0 &&
	    !(dirty & (CEPH_CAP_ANY_EXCL|CEPH_CAP_खाता_WR))) अणु
		करोut("queue_cap_snap %p nothing dirty|writing\n", inode);
		जाओ update_snapc;
	पूर्ण

	BUG_ON(!old_snapc);

	/*
	 * There is no need to send FLUSHSNAP message to MDS अगर there is
	 * no new snapshot. But when there is dirty pages or on-going
	 * ग_लिखोs, we still need to create cap_snap. cap_snap is needed
	 * by the ग_लिखो path and page ग_लिखोback path.
	 *
	 * also see ceph_try_drop_cap_snap()
	 */
	अगर (has_new_snaps(old_snapc, new_snapc)) अणु
		अगर (dirty & (CEPH_CAP_ANY_EXCL|CEPH_CAP_खाता_WR))
			capsnap->need_flush = true;
	पूर्ण अन्यथा अणु
		अगर (!(used & CEPH_CAP_खाता_WR) &&
		    ci->i_wrbuffer_ref_head == 0) अणु
			करोut("queue_cap_snap %p "
			     "no new_snap|dirty_page|writing\n", inode);
			जाओ update_snapc;
		पूर्ण
	पूर्ण

	करोut("queue_cap_snap %p cap_snap %p queuing under %p %s %s\n",
	     inode, capsnap, old_snapc, ceph_cap_string(dirty),
	     capsnap->need_flush ? "" : "no_flush");
	ihold(inode);

	refcount_set(&capsnap->nref, 1);
	INIT_LIST_HEAD(&capsnap->ci_item);

	capsnap->follows = old_snapc->seq;
	capsnap->issued = __ceph_caps_issued(ci, शून्य);
	capsnap->dirty = dirty;

	capsnap->mode = inode->i_mode;
	capsnap->uid = inode->i_uid;
	capsnap->gid = inode->i_gid;

	अगर (dirty & CEPH_CAP_XATTR_EXCL) अणु
		old_blob = __ceph_build_xattrs_blob(ci);
		capsnap->xattr_blob =
			ceph_buffer_get(ci->i_xattrs.blob);
		capsnap->xattr_version = ci->i_xattrs.version;
	पूर्ण अन्यथा अणु
		capsnap->xattr_blob = शून्य;
		capsnap->xattr_version = 0;
	पूर्ण

	capsnap->अंतरभूत_data = ci->i_अंतरभूत_version != CEPH_INLINE_NONE;

	/* dirty page count moved from _head to this cap_snap;
	   all subsequent ग_लिखोs page dirties occur _after_ this
	   snapshot. */
	capsnap->dirty_pages = ci->i_wrbuffer_ref_head;
	ci->i_wrbuffer_ref_head = 0;
	capsnap->context = old_snapc;
	list_add_tail(&capsnap->ci_item, &ci->i_cap_snaps);

	अगर (used & CEPH_CAP_खाता_WR) अणु
		करोut("queue_cap_snap %p cap_snap %p snapc %p"
		     " seq %llu used WR, now pending\n", inode,
		     capsnap, old_snapc, old_snapc->seq);
		capsnap->writing = 1;
	पूर्ण अन्यथा अणु
		/* note mसमय, size NOW. */
		__ceph_finish_cap_snap(ci, capsnap);
	पूर्ण
	capsnap = शून्य;
	old_snapc = शून्य;

update_snapc:
       अगर (ci->i_wrbuffer_ref_head == 0 &&
           ci->i_wr_ref == 0 &&
           ci->i_dirty_caps == 0 &&
           ci->i_flushing_caps == 0) अणु
               ci->i_head_snapc = शून्य;
       पूर्ण अन्यथा अणु
		ci->i_head_snapc = ceph_get_snap_context(new_snapc);
		करोut(" new snapc is %p\n", new_snapc);
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);

	ceph_buffer_put(old_blob);
	kमुक्त(capsnap);
	ceph_put_snap_context(old_snapc);
पूर्ण

/*
 * Finalize the size, mसमय क्रम a cap_snap.. that is, settle on final values
 * to be used क्रम the snapshot, to be flushed back to the mds.
 *
 * If capsnap can now be flushed, add to snap_flush list, and वापस 1.
 *
 * Caller must hold i_ceph_lock.
 */
पूर्णांक __ceph_finish_cap_snap(काष्ठा ceph_inode_info *ci,
			    काष्ठा ceph_cap_snap *capsnap)
अणु
	काष्ठा inode *inode = &ci->vfs_inode;
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(inode->i_sb);

	BUG_ON(capsnap->writing);
	capsnap->size = i_size_पढ़ो(inode);
	capsnap->mसमय = inode->i_mसमय;
	capsnap->aसमय = inode->i_aसमय;
	capsnap->स_समय = inode->i_स_समय;
	capsnap->bसमय = ci->i_bसमय;
	capsnap->change_attr = inode_peek_iversion_raw(inode);
	capsnap->समय_warp_seq = ci->i_समय_warp_seq;
	capsnap->truncate_size = ci->i_truncate_size;
	capsnap->truncate_seq = ci->i_truncate_seq;
	अगर (capsnap->dirty_pages) अणु
		करोut("finish_cap_snap %p cap_snap %p snapc %p %llu %s s=%llu "
		     "still has %d dirty pages\n", inode, capsnap,
		     capsnap->context, capsnap->context->seq,
		     ceph_cap_string(capsnap->dirty), capsnap->size,
		     capsnap->dirty_pages);
		वापस 0;
	पूर्ण

	/* Fb cap still in use, delay it */
	अगर (ci->i_wb_ref) अणु
		करोut("finish_cap_snap %p cap_snap %p snapc %p %llu %s s=%llu "
		     "used WRBUFFER, delaying\n", inode, capsnap,
		     capsnap->context, capsnap->context->seq,
		     ceph_cap_string(capsnap->dirty), capsnap->size);
		capsnap->writing = 1;
		वापस 0;
	पूर्ण

	ci->i_ceph_flags |= CEPH_I_FLUSH_SNAPS;
	करोut("finish_cap_snap %p cap_snap %p snapc %p %llu %s s=%llu\n",
	     inode, capsnap, capsnap->context,
	     capsnap->context->seq, ceph_cap_string(capsnap->dirty),
	     capsnap->size);

	spin_lock(&mdsc->snap_flush_lock);
	अगर (list_empty(&ci->i_snap_flush_item))
		list_add_tail(&ci->i_snap_flush_item, &mdsc->snap_flush_list);
	spin_unlock(&mdsc->snap_flush_lock);
	वापस 1;  /* caller may want to ceph_flush_snaps */
पूर्ण

/*
 * Queue cap_snaps क्रम snap ग_लिखोback क्रम this realm and its children.
 * Called under snap_rwsem, so realm topology won't change.
 */
अटल व्योम queue_realm_cap_snaps(काष्ठा ceph_snap_realm *realm)
अणु
	काष्ठा ceph_inode_info *ci;
	काष्ठा inode *lastinode = शून्य;

	करोut("queue_realm_cap_snaps %p %llx inodes\n", realm, realm->ino);

	spin_lock(&realm->inodes_with_caps_lock);
	list_क्रम_each_entry(ci, &realm->inodes_with_caps, i_snap_realm_item) अणु
		काष्ठा inode *inode = igrab(&ci->vfs_inode);
		अगर (!inode)
			जारी;
		spin_unlock(&realm->inodes_with_caps_lock);
		/* aव्योम calling iput_final() जबतक holding
		 * mdsc->snap_rwsem or in mds dispatch thपढ़ोs */
		ceph_async_iput(lastinode);
		lastinode = inode;
		ceph_queue_cap_snap(ci);
		spin_lock(&realm->inodes_with_caps_lock);
	पूर्ण
	spin_unlock(&realm->inodes_with_caps_lock);
	ceph_async_iput(lastinode);

	करोut("queue_realm_cap_snaps %p %llx done\n", realm, realm->ino);
पूर्ण

/*
 * Parse and apply a snapblob "snap trace" from the MDS.  This specअगरies
 * the snap realm parameters from a given realm and all of its ancestors,
 * up to the root.
 *
 * Caller must hold snap_rwsem क्रम ग_लिखो.
 */
पूर्णांक ceph_update_snap_trace(काष्ठा ceph_mds_client *mdsc,
			   व्योम *p, व्योम *e, bool deletion,
			   काष्ठा ceph_snap_realm **realm_ret)
अणु
	काष्ठा ceph_mds_snap_realm *ri;    /* encoded */
	__le64 *snaps;                     /* encoded */
	__le64 *prior_parent_snaps;        /* encoded */
	काष्ठा ceph_snap_realm *realm = शून्य;
	काष्ठा ceph_snap_realm *first_realm = शून्य;
	पूर्णांक invalidate = 0;
	पूर्णांक err = -ENOMEM;
	LIST_HEAD(dirty_realms);

	करोut("update_snap_trace deletion=%d\n", deletion);
more:
	ceph_decode_need(&p, e, माप(*ri), bad);
	ri = p;
	p += माप(*ri);
	ceph_decode_need(&p, e, माप(u64)*(le32_to_cpu(ri->num_snaps) +
			    le32_to_cpu(ri->num_prior_parent_snaps)), bad);
	snaps = p;
	p += माप(u64) * le32_to_cpu(ri->num_snaps);
	prior_parent_snaps = p;
	p += माप(u64) * le32_to_cpu(ri->num_prior_parent_snaps);

	realm = ceph_lookup_snap_realm(mdsc, le64_to_cpu(ri->ino));
	अगर (!realm) अणु
		realm = ceph_create_snap_realm(mdsc, le64_to_cpu(ri->ino));
		अगर (IS_ERR(realm)) अणु
			err = PTR_ERR(realm);
			जाओ fail;
		पूर्ण
	पूर्ण

	/* ensure the parent is correct */
	err = adjust_snap_realm_parent(mdsc, realm, le64_to_cpu(ri->parent));
	अगर (err < 0)
		जाओ fail;
	invalidate += err;

	अगर (le64_to_cpu(ri->seq) > realm->seq) अणु
		करोut("update_snap_trace updating %llx %p %lld -> %lld\n",
		     realm->ino, realm, realm->seq, le64_to_cpu(ri->seq));
		/* update realm parameters, snap lists */
		realm->seq = le64_to_cpu(ri->seq);
		realm->created = le64_to_cpu(ri->created);
		realm->parent_since = le64_to_cpu(ri->parent_since);

		realm->num_snaps = le32_to_cpu(ri->num_snaps);
		err = dup_array(&realm->snaps, snaps, realm->num_snaps);
		अगर (err < 0)
			जाओ fail;

		realm->num_prior_parent_snaps =
			le32_to_cpu(ri->num_prior_parent_snaps);
		err = dup_array(&realm->prior_parent_snaps, prior_parent_snaps,
				realm->num_prior_parent_snaps);
		अगर (err < 0)
			जाओ fail;

		अगर (realm->seq > mdsc->last_snap_seq)
			mdsc->last_snap_seq = realm->seq;

		invalidate = 1;
	पूर्ण अन्यथा अगर (!realm->cached_context) अणु
		करोut("update_snap_trace %llx %p seq %lld new\n",
		     realm->ino, realm, realm->seq);
		invalidate = 1;
	पूर्ण अन्यथा अणु
		करोut("update_snap_trace %llx %p seq %lld unchanged\n",
		     realm->ino, realm, realm->seq);
	पूर्ण

	करोut("done with %llx %p, invalidated=%d, %p %p\n", realm->ino,
	     realm, invalidate, p, e);

	/* invalidate when we reach the _end_ (root) of the trace */
	अगर (invalidate && p >= e)
		rebuild_snap_realms(realm, &dirty_realms);

	अगर (!first_realm)
		first_realm = realm;
	अन्यथा
		ceph_put_snap_realm(mdsc, realm);

	अगर (p < e)
		जाओ more;

	/*
	 * queue cap snaps _after_ we've built the new snap contexts,
	 * so that i_head_snapc can be set appropriately.
	 */
	जबतक (!list_empty(&dirty_realms)) अणु
		realm = list_first_entry(&dirty_realms, काष्ठा ceph_snap_realm,
					 dirty_item);
		list_del_init(&realm->dirty_item);
		queue_realm_cap_snaps(realm);
	पूर्ण

	अगर (realm_ret)
		*realm_ret = first_realm;
	अन्यथा
		ceph_put_snap_realm(mdsc, first_realm);

	__cleanup_empty_realms(mdsc);
	वापस 0;

bad:
	err = -EINVAL;
fail:
	अगर (realm && !IS_ERR(realm))
		ceph_put_snap_realm(mdsc, realm);
	अगर (first_realm)
		ceph_put_snap_realm(mdsc, first_realm);
	pr_err("update_snap_trace error %d\n", err);
	वापस err;
पूर्ण


/*
 * Send any cap_snaps that are queued क्रम flush.  Try to carry
 * s_mutex across multiple snap flushes to aव्योम locking overhead.
 *
 * Caller holds no locks.
 */
अटल व्योम flush_snaps(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_inode_info *ci;
	काष्ठा inode *inode;
	काष्ठा ceph_mds_session *session = शून्य;

	करोut("flush_snaps\n");
	spin_lock(&mdsc->snap_flush_lock);
	जबतक (!list_empty(&mdsc->snap_flush_list)) अणु
		ci = list_first_entry(&mdsc->snap_flush_list,
				काष्ठा ceph_inode_info, i_snap_flush_item);
		inode = &ci->vfs_inode;
		ihold(inode);
		spin_unlock(&mdsc->snap_flush_lock);
		ceph_flush_snaps(ci, &session);
		/* aव्योम calling iput_final() जबतक holding
		 * session->s_mutex or in mds dispatch thपढ़ोs */
		ceph_async_iput(inode);
		spin_lock(&mdsc->snap_flush_lock);
	पूर्ण
	spin_unlock(&mdsc->snap_flush_lock);

	अगर (session) अणु
		mutex_unlock(&session->s_mutex);
		ceph_put_mds_session(session);
	पूर्ण
	करोut("flush_snaps done\n");
पूर्ण


/*
 * Handle a snap notअगरication from the MDS.
 *
 * This can take two basic क्रमms: the simplest is just a snap creation
 * or deletion notअगरication on an existing realm.  This should update the
 * realm and its children.
 *
 * The more dअगरficult हाल is realm creation, due to snap creation at a
 * new poपूर्णांक in the file hierarchy, or due to a नाम that moves a file or
 * directory पूर्णांकo another realm.
 */
व्योम ceph_handle_snap(काष्ठा ceph_mds_client *mdsc,
		      काष्ठा ceph_mds_session *session,
		      काष्ठा ceph_msg *msg)
अणु
	काष्ठा super_block *sb = mdsc->fsc->sb;
	पूर्णांक mds = session->s_mds;
	u64 split;
	पूर्णांक op;
	पूर्णांक trace_len;
	काष्ठा ceph_snap_realm *realm = शून्य;
	व्योम *p = msg->front.iov_base;
	व्योम *e = p + msg->front.iov_len;
	काष्ठा ceph_mds_snap_head *h;
	पूर्णांक num_split_inos, num_split_realms;
	__le64 *split_inos = शून्य, *split_realms = शून्य;
	पूर्णांक i;
	पूर्णांक locked_rwsem = 0;

	/* decode */
	अगर (msg->front.iov_len < माप(*h))
		जाओ bad;
	h = p;
	op = le32_to_cpu(h->op);
	split = le64_to_cpu(h->split);   /* non-zero अगर we are splitting an
					  * existing realm */
	num_split_inos = le32_to_cpu(h->num_split_inos);
	num_split_realms = le32_to_cpu(h->num_split_realms);
	trace_len = le32_to_cpu(h->trace_len);
	p += माप(*h);

	करोut("handle_snap from mds%d op %s split %llx tracelen %d\n", mds,
	     ceph_snap_op_name(op), split, trace_len);

	mutex_lock(&session->s_mutex);
	inc_session_sequence(session);
	mutex_unlock(&session->s_mutex);

	करोwn_ग_लिखो(&mdsc->snap_rwsem);
	locked_rwsem = 1;

	अगर (op == CEPH_SNAP_OP_SPLIT) अणु
		काष्ठा ceph_mds_snap_realm *ri;

		/*
		 * A "split" अवरोधs part of an existing realm off पूर्णांकo
		 * a new realm.  The MDS provides a list of inodes
		 * (with caps) and child realms that beदीर्घ to the new
		 * child.
		 */
		split_inos = p;
		p += माप(u64) * num_split_inos;
		split_realms = p;
		p += माप(u64) * num_split_realms;
		ceph_decode_need(&p, e, माप(*ri), bad);
		/* we will peek at realm info here, but will _not_
		 * advance p, as the realm update will occur below in
		 * ceph_update_snap_trace. */
		ri = p;

		realm = ceph_lookup_snap_realm(mdsc, split);
		अगर (!realm) अणु
			realm = ceph_create_snap_realm(mdsc, split);
			अगर (IS_ERR(realm))
				जाओ out;
		पूर्ण

		करोut("splitting snap_realm %llx %p\n", realm->ino, realm);
		क्रम (i = 0; i < num_split_inos; i++) अणु
			काष्ठा ceph_vino vino = अणु
				.ino = le64_to_cpu(split_inos[i]),
				.snap = CEPH_NOSNAP,
			पूर्ण;
			काष्ठा inode *inode = ceph_find_inode(sb, vino);
			काष्ठा ceph_inode_info *ci;
			काष्ठा ceph_snap_realm *oldrealm;

			अगर (!inode)
				जारी;
			ci = ceph_inode(inode);

			spin_lock(&ci->i_ceph_lock);
			अगर (!ci->i_snap_realm)
				जाओ skip_inode;
			/*
			 * If this inode beदीर्घs to a realm that was
			 * created after our new realm, we experienced
			 * a race (due to another split notअगरications
			 * arriving from a dअगरferent MDS).  So skip
			 * this inode.
			 */
			अगर (ci->i_snap_realm->created >
			    le64_to_cpu(ri->created)) अणु
				करोut(" leaving %p in newer realm %llx %p\n",
				     inode, ci->i_snap_realm->ino,
				     ci->i_snap_realm);
				जाओ skip_inode;
			पूर्ण
			करोut(" will move %p to split realm %llx %p\n",
			     inode, realm->ino, realm);
			/*
			 * Move the inode to the new realm
			 */
			oldrealm = ci->i_snap_realm;
			spin_lock(&oldrealm->inodes_with_caps_lock);
			list_del_init(&ci->i_snap_realm_item);
			spin_unlock(&oldrealm->inodes_with_caps_lock);

			spin_lock(&realm->inodes_with_caps_lock);
			list_add(&ci->i_snap_realm_item,
				 &realm->inodes_with_caps);
			ci->i_snap_realm = realm;
			अगर (realm->ino == ci->i_vino.ino)
                                realm->inode = inode;
			spin_unlock(&realm->inodes_with_caps_lock);

			spin_unlock(&ci->i_ceph_lock);

			ceph_get_snap_realm(mdsc, realm);
			ceph_put_snap_realm(mdsc, oldrealm);

			/* aव्योम calling iput_final() जबतक holding
			 * mdsc->snap_rwsem or mds in dispatch thपढ़ोs */
			ceph_async_iput(inode);
			जारी;

skip_inode:
			spin_unlock(&ci->i_ceph_lock);
			ceph_async_iput(inode);
		पूर्ण

		/* we may have taken some of the old realm's children. */
		क्रम (i = 0; i < num_split_realms; i++) अणु
			काष्ठा ceph_snap_realm *child =
				__lookup_snap_realm(mdsc,
					   le64_to_cpu(split_realms[i]));
			अगर (!child)
				जारी;
			adjust_snap_realm_parent(mdsc, child, realm->ino);
		पूर्ण
	पूर्ण

	/*
	 * update using the provided snap trace. अगर we are deleting a
	 * snap, we can aव्योम queueing cap_snaps.
	 */
	ceph_update_snap_trace(mdsc, p, e,
			       op == CEPH_SNAP_OP_DESTROY, शून्य);

	अगर (op == CEPH_SNAP_OP_SPLIT)
		/* we took a reference when we created the realm, above */
		ceph_put_snap_realm(mdsc, realm);

	__cleanup_empty_realms(mdsc);

	up_ग_लिखो(&mdsc->snap_rwsem);

	flush_snaps(mdsc);
	वापस;

bad:
	pr_err("corrupt snap message from mds%d\n", mds);
	ceph_msg_dump(msg);
out:
	अगर (locked_rwsem)
		up_ग_लिखो(&mdsc->snap_rwsem);
	वापस;
पूर्ण

काष्ठा ceph_snapid_map* ceph_get_snapid_map(काष्ठा ceph_mds_client *mdsc,
					    u64 snap)
अणु
	काष्ठा ceph_snapid_map *sm, *exist;
	काष्ठा rb_node **p, *parent;
	पूर्णांक ret;

	exist = शून्य;
	spin_lock(&mdsc->snapid_map_lock);
	p = &mdsc->snapid_map_tree.rb_node;
	जबतक (*p) अणु
		exist = rb_entry(*p, काष्ठा ceph_snapid_map, node);
		अगर (snap > exist->snap) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (snap < exist->snap) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			अगर (atomic_inc_वापस(&exist->ref) == 1)
				list_del_init(&exist->lru);
			अवरोध;
		पूर्ण
		exist = शून्य;
	पूर्ण
	spin_unlock(&mdsc->snapid_map_lock);
	अगर (exist) अणु
		करोut("found snapid map %llx -> %x\n", exist->snap, exist->dev);
		वापस exist;
	पूर्ण

	sm = kदो_स्मृति(माप(*sm), GFP_NOFS);
	अगर (!sm)
		वापस शून्य;

	ret = get_anon_bdev(&sm->dev);
	अगर (ret < 0) अणु
		kमुक्त(sm);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&sm->lru);
	atomic_set(&sm->ref, 1);
	sm->snap = snap;

	exist = शून्य;
	parent = शून्य;
	p = &mdsc->snapid_map_tree.rb_node;
	spin_lock(&mdsc->snapid_map_lock);
	जबतक (*p) अणु
		parent = *p;
		exist = rb_entry(*p, काष्ठा ceph_snapid_map, node);
		अगर (snap > exist->snap)
			p = &(*p)->rb_left;
		अन्यथा अगर (snap < exist->snap)
			p = &(*p)->rb_right;
		अन्यथा
			अवरोध;
		exist = शून्य;
	पूर्ण
	अगर (exist) अणु
		अगर (atomic_inc_वापस(&exist->ref) == 1)
			list_del_init(&exist->lru);
	पूर्ण अन्यथा अणु
		rb_link_node(&sm->node, parent, p);
		rb_insert_color(&sm->node, &mdsc->snapid_map_tree);
	पूर्ण
	spin_unlock(&mdsc->snapid_map_lock);
	अगर (exist) अणु
		मुक्त_anon_bdev(sm->dev);
		kमुक्त(sm);
		करोut("found snapid map %llx -> %x\n", exist->snap, exist->dev);
		वापस exist;
	पूर्ण

	करोut("create snapid map %llx -> %x\n", sm->snap, sm->dev);
	वापस sm;
पूर्ण

व्योम ceph_put_snapid_map(काष्ठा ceph_mds_client* mdsc,
			 काष्ठा ceph_snapid_map *sm)
अणु
	अगर (!sm)
		वापस;
	अगर (atomic_dec_and_lock(&sm->ref, &mdsc->snapid_map_lock)) अणु
		अगर (!RB_EMPTY_NODE(&sm->node)) अणु
			sm->last_used = jअगरfies;
			list_add_tail(&sm->lru, &mdsc->snapid_map_lru);
			spin_unlock(&mdsc->snapid_map_lock);
		पूर्ण अन्यथा अणु
			/* alपढ़ोy cleaned up by
			 * ceph_cleanup_snapid_map() */
			spin_unlock(&mdsc->snapid_map_lock);
			kमुक्त(sm);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ceph_trim_snapid_map(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_snapid_map *sm;
	अचिन्हित दीर्घ now;
	LIST_HEAD(to_मुक्त);

	spin_lock(&mdsc->snapid_map_lock);
	now = jअगरfies;

	जबतक (!list_empty(&mdsc->snapid_map_lru)) अणु
		sm = list_first_entry(&mdsc->snapid_map_lru,
				      काष्ठा ceph_snapid_map, lru);
		अगर (समय_after(sm->last_used + CEPH_SNAPID_MAP_TIMEOUT, now))
			अवरोध;

		rb_erase(&sm->node, &mdsc->snapid_map_tree);
		list_move(&sm->lru, &to_मुक्त);
	पूर्ण
	spin_unlock(&mdsc->snapid_map_lock);

	जबतक (!list_empty(&to_मुक्त)) अणु
		sm = list_first_entry(&to_मुक्त, काष्ठा ceph_snapid_map, lru);
		list_del(&sm->lru);
		करोut("trim snapid map %llx -> %x\n", sm->snap, sm->dev);
		मुक्त_anon_bdev(sm->dev);
		kमुक्त(sm);
	पूर्ण
पूर्ण

व्योम ceph_cleanup_snapid_map(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_snapid_map *sm;
	काष्ठा rb_node *p;
	LIST_HEAD(to_मुक्त);

	spin_lock(&mdsc->snapid_map_lock);
	जबतक ((p = rb_first(&mdsc->snapid_map_tree))) अणु
		sm = rb_entry(p, काष्ठा ceph_snapid_map, node);
		rb_erase(p, &mdsc->snapid_map_tree);
		RB_CLEAR_NODE(p);
		list_move(&sm->lru, &to_मुक्त);
	पूर्ण
	spin_unlock(&mdsc->snapid_map_lock);

	जबतक (!list_empty(&to_मुक्त)) अणु
		sm = list_first_entry(&to_मुक्त, काष्ठा ceph_snapid_map, lru);
		list_del(&sm->lru);
		मुक्त_anon_bdev(sm->dev);
		अगर (WARN_ON_ONCE(atomic_पढ़ो(&sm->ref))) अणु
			pr_err("snapid map %llx -> %x still in use\n",
			       sm->snap, sm->dev);
		पूर्ण
		kमुक्त(sm);
	पूर्ण
पूर्ण
