<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/रुको.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/iversion.h>

#समावेश "super.h"
#समावेश "mds_client.h"
#समावेश "cache.h"
#समावेश <linux/ceph/decode.h>
#समावेश <linux/ceph/messenger.h>

/*
 * Capability management
 *
 * The Ceph metadata servers control client access to inode metadata
 * and file data by issuing capabilities, granting clients permission
 * to पढ़ो and/or ग_लिखो both inode field and file data to OSDs
 * (storage nodes).  Each capability consists of a set of bits
 * indicating which operations are allowed.
 *
 * If the client holds a *_SHARED cap, the client has a coherent value
 * that can be safely पढ़ो from the cached inode.
 *
 * In the हाल of a *_EXCL (exclusive) or खाता_WR capabilities, the
 * client is allowed to change inode attributes (e.g., file size,
 * mसमय), note its dirty state in the ceph_cap, and asynchronously
 * flush that metadata change to the MDS.
 *
 * In the event of a conflicting operation (perhaps by another
 * client), the MDS will revoke the conflicting client capabilities.
 *
 * In order क्रम a client to cache an inode, it must hold a capability
 * with at least one MDS server.  When inodes are released, release
 * notअगरications are batched and periodically sent en masse to the MDS
 * cluster to release server state.
 */

अटल u64 __get_oldest_flush_tid(काष्ठा ceph_mds_client *mdsc);
अटल व्योम __kick_flushing_caps(काष्ठा ceph_mds_client *mdsc,
				 काष्ठा ceph_mds_session *session,
				 काष्ठा ceph_inode_info *ci,
				 u64 oldest_flush_tid);

/*
 * Generate पढ़ोable cap strings क्रम debugging output.
 */
#घोषणा MAX_CAP_STR 20
अटल अक्षर cap_str[MAX_CAP_STR][40];
अटल DEFINE_SPINLOCK(cap_str_lock);
अटल पूर्णांक last_cap_str;

अटल अक्षर *gcap_string(अक्षर *s, पूर्णांक c)
अणु
	अगर (c & CEPH_CAP_GSHARED)
		*s++ = 's';
	अगर (c & CEPH_CAP_GEXCL)
		*s++ = 'x';
	अगर (c & CEPH_CAP_GCACHE)
		*s++ = 'c';
	अगर (c & CEPH_CAP_GRD)
		*s++ = 'r';
	अगर (c & CEPH_CAP_GWR)
		*s++ = 'w';
	अगर (c & CEPH_CAP_GBUFFER)
		*s++ = 'b';
	अगर (c & CEPH_CAP_GWREXTEND)
		*s++ = 'a';
	अगर (c & CEPH_CAP_GLAZYIO)
		*s++ = 'l';
	वापस s;
पूर्ण

स्थिर अक्षर *ceph_cap_string(पूर्णांक caps)
अणु
	पूर्णांक i;
	अक्षर *s;
	पूर्णांक c;

	spin_lock(&cap_str_lock);
	i = last_cap_str++;
	अगर (last_cap_str == MAX_CAP_STR)
		last_cap_str = 0;
	spin_unlock(&cap_str_lock);

	s = cap_str[i];

	अगर (caps & CEPH_CAP_PIN)
		*s++ = 'p';

	c = (caps >> CEPH_CAP_SAUTH) & 3;
	अगर (c) अणु
		*s++ = 'A';
		s = gcap_string(s, c);
	पूर्ण

	c = (caps >> CEPH_CAP_SLINK) & 3;
	अगर (c) अणु
		*s++ = 'L';
		s = gcap_string(s, c);
	पूर्ण

	c = (caps >> CEPH_CAP_SXATTR) & 3;
	अगर (c) अणु
		*s++ = 'X';
		s = gcap_string(s, c);
	पूर्ण

	c = caps >> CEPH_CAP_Sखाता;
	अगर (c) अणु
		*s++ = 'F';
		s = gcap_string(s, c);
	पूर्ण

	अगर (s == cap_str[i])
		*s++ = '-';
	*s = 0;
	वापस cap_str[i];
पूर्ण

व्योम ceph_caps_init(काष्ठा ceph_mds_client *mdsc)
अणु
	INIT_LIST_HEAD(&mdsc->caps_list);
	spin_lock_init(&mdsc->caps_list_lock);
पूर्ण

व्योम ceph_caps_finalize(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_cap *cap;

	spin_lock(&mdsc->caps_list_lock);
	जबतक (!list_empty(&mdsc->caps_list)) अणु
		cap = list_first_entry(&mdsc->caps_list,
				       काष्ठा ceph_cap, caps_item);
		list_del(&cap->caps_item);
		kmem_cache_मुक्त(ceph_cap_cachep, cap);
	पूर्ण
	mdsc->caps_total_count = 0;
	mdsc->caps_avail_count = 0;
	mdsc->caps_use_count = 0;
	mdsc->caps_reserve_count = 0;
	mdsc->caps_min_count = 0;
	spin_unlock(&mdsc->caps_list_lock);
पूर्ण

व्योम ceph_adjust_caps_max_min(काष्ठा ceph_mds_client *mdsc,
			      काष्ठा ceph_mount_options *fsopt)
अणु
	spin_lock(&mdsc->caps_list_lock);
	mdsc->caps_min_count = fsopt->max_सूची_पढ़ो;
	अगर (mdsc->caps_min_count < 1024)
		mdsc->caps_min_count = 1024;
	mdsc->caps_use_max = fsopt->caps_max;
	अगर (mdsc->caps_use_max > 0 &&
	    mdsc->caps_use_max < mdsc->caps_min_count)
		mdsc->caps_use_max = mdsc->caps_min_count;
	spin_unlock(&mdsc->caps_list_lock);
पूर्ण

अटल व्योम __ceph_unreserve_caps(काष्ठा ceph_mds_client *mdsc, पूर्णांक nr_caps)
अणु
	काष्ठा ceph_cap *cap;
	पूर्णांक i;

	अगर (nr_caps) अणु
		BUG_ON(mdsc->caps_reserve_count < nr_caps);
		mdsc->caps_reserve_count -= nr_caps;
		अगर (mdsc->caps_avail_count >=
		    mdsc->caps_reserve_count + mdsc->caps_min_count) अणु
			mdsc->caps_total_count -= nr_caps;
			क्रम (i = 0; i < nr_caps; i++) अणु
				cap = list_first_entry(&mdsc->caps_list,
					काष्ठा ceph_cap, caps_item);
				list_del(&cap->caps_item);
				kmem_cache_मुक्त(ceph_cap_cachep, cap);
			पूर्ण
		पूर्ण अन्यथा अणु
			mdsc->caps_avail_count += nr_caps;
		पूर्ण

		करोut("%s: caps %d = %d used + %d resv + %d avail\n",
		     __func__,
		     mdsc->caps_total_count, mdsc->caps_use_count,
		     mdsc->caps_reserve_count, mdsc->caps_avail_count);
		BUG_ON(mdsc->caps_total_count != mdsc->caps_use_count +
						 mdsc->caps_reserve_count +
						 mdsc->caps_avail_count);
	पूर्ण
पूर्ण

/*
 * Called under mdsc->mutex.
 */
पूर्णांक ceph_reserve_caps(काष्ठा ceph_mds_client *mdsc,
		      काष्ठा ceph_cap_reservation *ctx, पूर्णांक need)
अणु
	पूर्णांक i, j;
	काष्ठा ceph_cap *cap;
	पूर्णांक have;
	पूर्णांक alloc = 0;
	पूर्णांक max_caps;
	पूर्णांक err = 0;
	bool trimmed = false;
	काष्ठा ceph_mds_session *s;
	LIST_HEAD(newcaps);

	करोut("reserve caps ctx=%p need=%d\n", ctx, need);

	/* first reserve any caps that are alपढ़ोy allocated */
	spin_lock(&mdsc->caps_list_lock);
	अगर (mdsc->caps_avail_count >= need)
		have = need;
	अन्यथा
		have = mdsc->caps_avail_count;
	mdsc->caps_avail_count -= have;
	mdsc->caps_reserve_count += have;
	BUG_ON(mdsc->caps_total_count != mdsc->caps_use_count +
					 mdsc->caps_reserve_count +
					 mdsc->caps_avail_count);
	spin_unlock(&mdsc->caps_list_lock);

	क्रम (i = have; i < need; ) अणु
		cap = kmem_cache_alloc(ceph_cap_cachep, GFP_NOFS);
		अगर (cap) अणु
			list_add(&cap->caps_item, &newcaps);
			alloc++;
			i++;
			जारी;
		पूर्ण

		अगर (!trimmed) अणु
			क्रम (j = 0; j < mdsc->max_sessions; j++) अणु
				s = __ceph_lookup_mds_session(mdsc, j);
				अगर (!s)
					जारी;
				mutex_unlock(&mdsc->mutex);

				mutex_lock(&s->s_mutex);
				max_caps = s->s_nr_caps - (need - i);
				ceph_trim_caps(mdsc, s, max_caps);
				mutex_unlock(&s->s_mutex);

				ceph_put_mds_session(s);
				mutex_lock(&mdsc->mutex);
			पूर्ण
			trimmed = true;

			spin_lock(&mdsc->caps_list_lock);
			अगर (mdsc->caps_avail_count) अणु
				पूर्णांक more_have;
				अगर (mdsc->caps_avail_count >= need - i)
					more_have = need - i;
				अन्यथा
					more_have = mdsc->caps_avail_count;

				i += more_have;
				have += more_have;
				mdsc->caps_avail_count -= more_have;
				mdsc->caps_reserve_count += more_have;

			पूर्ण
			spin_unlock(&mdsc->caps_list_lock);

			जारी;
		पूर्ण

		pr_warn("reserve caps ctx=%p ENOMEM need=%d got=%d\n",
			ctx, need, have + alloc);
		err = -ENOMEM;
		अवरोध;
	पूर्ण

	अगर (!err) अणु
		BUG_ON(have + alloc != need);
		ctx->count = need;
		ctx->used = 0;
	पूर्ण

	spin_lock(&mdsc->caps_list_lock);
	mdsc->caps_total_count += alloc;
	mdsc->caps_reserve_count += alloc;
	list_splice(&newcaps, &mdsc->caps_list);

	BUG_ON(mdsc->caps_total_count != mdsc->caps_use_count +
					 mdsc->caps_reserve_count +
					 mdsc->caps_avail_count);

	अगर (err)
		__ceph_unreserve_caps(mdsc, have + alloc);

	spin_unlock(&mdsc->caps_list_lock);

	करोut("reserve caps ctx=%p %d = %d used + %d resv + %d avail\n",
	     ctx, mdsc->caps_total_count, mdsc->caps_use_count,
	     mdsc->caps_reserve_count, mdsc->caps_avail_count);
	वापस err;
पूर्ण

व्योम ceph_unreserve_caps(काष्ठा ceph_mds_client *mdsc,
			 काष्ठा ceph_cap_reservation *ctx)
अणु
	bool reclaim = false;
	अगर (!ctx->count)
		वापस;

	करोut("unreserve caps ctx=%p count=%d\n", ctx, ctx->count);
	spin_lock(&mdsc->caps_list_lock);
	__ceph_unreserve_caps(mdsc, ctx->count);
	ctx->count = 0;

	अगर (mdsc->caps_use_max > 0 &&
	    mdsc->caps_use_count > mdsc->caps_use_max)
		reclaim = true;
	spin_unlock(&mdsc->caps_list_lock);

	अगर (reclaim)
		ceph_reclaim_caps_nr(mdsc, ctx->used);
पूर्ण

काष्ठा ceph_cap *ceph_get_cap(काष्ठा ceph_mds_client *mdsc,
			      काष्ठा ceph_cap_reservation *ctx)
अणु
	काष्ठा ceph_cap *cap = शून्य;

	/* temporary, until we करो something about cap import/export */
	अगर (!ctx) अणु
		cap = kmem_cache_alloc(ceph_cap_cachep, GFP_NOFS);
		अगर (cap) अणु
			spin_lock(&mdsc->caps_list_lock);
			mdsc->caps_use_count++;
			mdsc->caps_total_count++;
			spin_unlock(&mdsc->caps_list_lock);
		पूर्ण अन्यथा अणु
			spin_lock(&mdsc->caps_list_lock);
			अगर (mdsc->caps_avail_count) अणु
				BUG_ON(list_empty(&mdsc->caps_list));

				mdsc->caps_avail_count--;
				mdsc->caps_use_count++;
				cap = list_first_entry(&mdsc->caps_list,
						काष्ठा ceph_cap, caps_item);
				list_del(&cap->caps_item);

				BUG_ON(mdsc->caps_total_count != mdsc->caps_use_count +
				       mdsc->caps_reserve_count + mdsc->caps_avail_count);
			पूर्ण
			spin_unlock(&mdsc->caps_list_lock);
		पूर्ण

		वापस cap;
	पूर्ण

	spin_lock(&mdsc->caps_list_lock);
	करोut("get_cap ctx=%p (%d) %d = %d used + %d resv + %d avail\n",
	     ctx, ctx->count, mdsc->caps_total_count, mdsc->caps_use_count,
	     mdsc->caps_reserve_count, mdsc->caps_avail_count);
	BUG_ON(!ctx->count);
	BUG_ON(ctx->count > mdsc->caps_reserve_count);
	BUG_ON(list_empty(&mdsc->caps_list));

	ctx->count--;
	ctx->used++;
	mdsc->caps_reserve_count--;
	mdsc->caps_use_count++;

	cap = list_first_entry(&mdsc->caps_list, काष्ठा ceph_cap, caps_item);
	list_del(&cap->caps_item);

	BUG_ON(mdsc->caps_total_count != mdsc->caps_use_count +
	       mdsc->caps_reserve_count + mdsc->caps_avail_count);
	spin_unlock(&mdsc->caps_list_lock);
	वापस cap;
पूर्ण

व्योम ceph_put_cap(काष्ठा ceph_mds_client *mdsc, काष्ठा ceph_cap *cap)
अणु
	spin_lock(&mdsc->caps_list_lock);
	करोut("put_cap %p %d = %d used + %d resv + %d avail\n",
	     cap, mdsc->caps_total_count, mdsc->caps_use_count,
	     mdsc->caps_reserve_count, mdsc->caps_avail_count);
	mdsc->caps_use_count--;
	/*
	 * Keep some pपुनः_स्मृतिated caps around (ceph_min_count), to
	 * aव्योम lots of मुक्त/alloc churn.
	 */
	अगर (mdsc->caps_avail_count >= mdsc->caps_reserve_count +
				      mdsc->caps_min_count) अणु
		mdsc->caps_total_count--;
		kmem_cache_मुक्त(ceph_cap_cachep, cap);
	पूर्ण अन्यथा अणु
		mdsc->caps_avail_count++;
		list_add(&cap->caps_item, &mdsc->caps_list);
	पूर्ण

	BUG_ON(mdsc->caps_total_count != mdsc->caps_use_count +
	       mdsc->caps_reserve_count + mdsc->caps_avail_count);
	spin_unlock(&mdsc->caps_list_lock);
पूर्ण

व्योम ceph_reservation_status(काष्ठा ceph_fs_client *fsc,
			     पूर्णांक *total, पूर्णांक *avail, पूर्णांक *used, पूर्णांक *reserved,
			     पूर्णांक *min)
अणु
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;

	spin_lock(&mdsc->caps_list_lock);

	अगर (total)
		*total = mdsc->caps_total_count;
	अगर (avail)
		*avail = mdsc->caps_avail_count;
	अगर (used)
		*used = mdsc->caps_use_count;
	अगर (reserved)
		*reserved = mdsc->caps_reserve_count;
	अगर (min)
		*min = mdsc->caps_min_count;

	spin_unlock(&mdsc->caps_list_lock);
पूर्ण

/*
 * Find ceph_cap क्रम given mds, अगर any.
 *
 * Called with i_ceph_lock held.
 */
अटल काष्ठा ceph_cap *__get_cap_क्रम_mds(काष्ठा ceph_inode_info *ci, पूर्णांक mds)
अणु
	काष्ठा ceph_cap *cap;
	काष्ठा rb_node *n = ci->i_caps.rb_node;

	जबतक (n) अणु
		cap = rb_entry(n, काष्ठा ceph_cap, ci_node);
		अगर (mds < cap->mds)
			n = n->rb_left;
		अन्यथा अगर (mds > cap->mds)
			n = n->rb_right;
		अन्यथा
			वापस cap;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा ceph_cap *ceph_get_cap_क्रम_mds(काष्ठा ceph_inode_info *ci, पूर्णांक mds)
अणु
	काष्ठा ceph_cap *cap;

	spin_lock(&ci->i_ceph_lock);
	cap = __get_cap_क्रम_mds(ci, mds);
	spin_unlock(&ci->i_ceph_lock);
	वापस cap;
पूर्ण

/*
 * Called under i_ceph_lock.
 */
अटल व्योम __insert_cap_node(काष्ठा ceph_inode_info *ci,
			      काष्ठा ceph_cap *new)
अणु
	काष्ठा rb_node **p = &ci->i_caps.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा ceph_cap *cap = शून्य;

	जबतक (*p) अणु
		parent = *p;
		cap = rb_entry(parent, काष्ठा ceph_cap, ci_node);
		अगर (new->mds < cap->mds)
			p = &(*p)->rb_left;
		अन्यथा अगर (new->mds > cap->mds)
			p = &(*p)->rb_right;
		अन्यथा
			BUG();
	पूर्ण

	rb_link_node(&new->ci_node, parent, p);
	rb_insert_color(&new->ci_node, &ci->i_caps);
पूर्ण

/*
 * (re)set cap hold समयouts, which control the delayed release
 * of unused caps back to the MDS.  Should be called on cap use.
 */
अटल व्योम __cap_set_समयouts(काष्ठा ceph_mds_client *mdsc,
			       काष्ठा ceph_inode_info *ci)
अणु
	काष्ठा ceph_mount_options *opt = mdsc->fsc->mount_options;
	ci->i_hold_caps_max = round_jअगरfies(jअगरfies +
					    opt->caps_wanted_delay_max * HZ);
	करोut("__cap_set_timeouts %p %lu\n", &ci->vfs_inode,
	     ci->i_hold_caps_max - jअगरfies);
पूर्ण

/*
 * (Re)queue cap at the end of the delayed cap release list.
 *
 * If I_FLUSH is set, leave the inode at the front of the list.
 *
 * Caller holds i_ceph_lock
 *    -> we take mdsc->cap_delay_lock
 */
अटल व्योम __cap_delay_requeue(काष्ठा ceph_mds_client *mdsc,
				काष्ठा ceph_inode_info *ci)
अणु
	करोut("__cap_delay_requeue %p flags 0x%lx at %lu\n", &ci->vfs_inode,
	     ci->i_ceph_flags, ci->i_hold_caps_max);
	अगर (!mdsc->stopping) अणु
		spin_lock(&mdsc->cap_delay_lock);
		अगर (!list_empty(&ci->i_cap_delay_list)) अणु
			अगर (ci->i_ceph_flags & CEPH_I_FLUSH)
				जाओ no_change;
			list_del_init(&ci->i_cap_delay_list);
		पूर्ण
		__cap_set_समयouts(mdsc, ci);
		list_add_tail(&ci->i_cap_delay_list, &mdsc->cap_delay_list);
no_change:
		spin_unlock(&mdsc->cap_delay_lock);
	पूर्ण
पूर्ण

/*
 * Queue an inode क्रम immediate ग_लिखोback.  Mark inode with I_FLUSH,
 * indicating we should send a cap message to flush dirty metadata
 * asap, and move to the front of the delayed cap list.
 */
अटल व्योम __cap_delay_requeue_front(काष्ठा ceph_mds_client *mdsc,
				      काष्ठा ceph_inode_info *ci)
अणु
	करोut("__cap_delay_requeue_front %p\n", &ci->vfs_inode);
	spin_lock(&mdsc->cap_delay_lock);
	ci->i_ceph_flags |= CEPH_I_FLUSH;
	अगर (!list_empty(&ci->i_cap_delay_list))
		list_del_init(&ci->i_cap_delay_list);
	list_add(&ci->i_cap_delay_list, &mdsc->cap_delay_list);
	spin_unlock(&mdsc->cap_delay_lock);
पूर्ण

/*
 * Cancel delayed work on cap.
 *
 * Caller must hold i_ceph_lock.
 */
अटल व्योम __cap_delay_cancel(काष्ठा ceph_mds_client *mdsc,
			       काष्ठा ceph_inode_info *ci)
अणु
	करोut("__cap_delay_cancel %p\n", &ci->vfs_inode);
	अगर (list_empty(&ci->i_cap_delay_list))
		वापस;
	spin_lock(&mdsc->cap_delay_lock);
	list_del_init(&ci->i_cap_delay_list);
	spin_unlock(&mdsc->cap_delay_lock);
पूर्ण

/* Common issue checks क्रम add_cap, handle_cap_grant. */
अटल व्योम __check_cap_issue(काष्ठा ceph_inode_info *ci, काष्ठा ceph_cap *cap,
			      अचिन्हित issued)
अणु
	अचिन्हित had = __ceph_caps_issued(ci, शून्य);

	lockdep_निश्चित_held(&ci->i_ceph_lock);

	/*
	 * Each समय we receive खाता_CACHE anew, we increment
	 * i_rdcache_gen.
	 */
	अगर (S_ISREG(ci->vfs_inode.i_mode) &&
	    (issued & (CEPH_CAP_खाता_CACHE|CEPH_CAP_खाता_LAZYIO)) &&
	    (had & (CEPH_CAP_खाता_CACHE|CEPH_CAP_खाता_LAZYIO)) == 0) अणु
		ci->i_rdcache_gen++;
	पूर्ण

	/*
	 * If खाता_SHARED is newly issued, mark dir not complete. We करोn't
	 * know what happened to this directory जबतक we didn't have the cap.
	 * If खाता_SHARED is being revoked, also mark dir not complete. It
	 * stops on-going cached सूची_पढ़ो.
	 */
	अगर ((issued & CEPH_CAP_खाता_SHARED) != (had & CEPH_CAP_खाता_SHARED)) अणु
		अगर (issued & CEPH_CAP_खाता_SHARED)
			atomic_inc(&ci->i_shared_gen);
		अगर (S_ISसूची(ci->vfs_inode.i_mode)) अणु
			करोut(" marking %p NOT complete\n", &ci->vfs_inode);
			__ceph_dir_clear_complete(ci);
		पूर्ण
	पूर्ण

	/* Wipe saved layout अगर we're losing सूची_CREATE caps */
	अगर (S_ISसूची(ci->vfs_inode.i_mode) && (had & CEPH_CAP_सूची_CREATE) &&
		!(issued & CEPH_CAP_सूची_CREATE)) अणु
	     ceph_put_string(rcu_dereference_raw(ci->i_cached_layout.pool_ns));
	     स_रखो(&ci->i_cached_layout, 0, माप(ci->i_cached_layout));
	पूर्ण
पूर्ण

/**
 * change_auth_cap_ses - move inode to appropriate lists when auth caps change
 * @ci: inode to be moved
 * @session: new auth caps session
 */
अटल व्योम change_auth_cap_ses(काष्ठा ceph_inode_info *ci,
				काष्ठा ceph_mds_session *session)
अणु
	lockdep_निश्चित_held(&ci->i_ceph_lock);

	अगर (list_empty(&ci->i_dirty_item) && list_empty(&ci->i_flushing_item))
		वापस;

	spin_lock(&session->s_mdsc->cap_dirty_lock);
	अगर (!list_empty(&ci->i_dirty_item))
		list_move(&ci->i_dirty_item, &session->s_cap_dirty);
	अगर (!list_empty(&ci->i_flushing_item))
		list_move_tail(&ci->i_flushing_item, &session->s_cap_flushing);
	spin_unlock(&session->s_mdsc->cap_dirty_lock);
पूर्ण

/*
 * Add a capability under the given MDS session.
 *
 * Caller should hold session snap_rwsem (पढ़ो) and ci->i_ceph_lock
 *
 * @भ_शेषe is the खोलो file mode, अगर we are खोलोing a file, otherwise
 * it is < 0.  (This is so we can atomically add the cap and add an
 * खोलो file reference to it.)
 */
व्योम ceph_add_cap(काष्ठा inode *inode,
		  काष्ठा ceph_mds_session *session, u64 cap_id,
		  अचिन्हित issued, अचिन्हित wanted,
		  अचिन्हित seq, अचिन्हित mseq, u64 realmino, पूर्णांक flags,
		  काष्ठा ceph_cap **new_cap)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_inode_to_client(inode)->mdsc;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_cap *cap;
	पूर्णांक mds = session->s_mds;
	पूर्णांक actual_wanted;
	u32 gen;

	lockdep_निश्चित_held(&ci->i_ceph_lock);

	करोut("add_cap %p mds%d cap %llx %s seq %d\n", inode,
	     session->s_mds, cap_id, ceph_cap_string(issued), seq);

	spin_lock(&session->s_gen_ttl_lock);
	gen = session->s_cap_gen;
	spin_unlock(&session->s_gen_ttl_lock);

	cap = __get_cap_क्रम_mds(ci, mds);
	अगर (!cap) अणु
		cap = *new_cap;
		*new_cap = शून्य;

		cap->issued = 0;
		cap->implemented = 0;
		cap->mds = mds;
		cap->mds_wanted = 0;
		cap->mseq = 0;

		cap->ci = ci;
		__insert_cap_node(ci, cap);

		/* add to session cap list */
		cap->session = session;
		spin_lock(&session->s_cap_lock);
		list_add_tail(&cap->session_caps, &session->s_caps);
		session->s_nr_caps++;
		atomic64_inc(&mdsc->metric.total_caps);
		spin_unlock(&session->s_cap_lock);
	पूर्ण अन्यथा अणु
		spin_lock(&session->s_cap_lock);
		list_move_tail(&cap->session_caps, &session->s_caps);
		spin_unlock(&session->s_cap_lock);

		अगर (cap->cap_gen < gen)
			cap->issued = cap->implemented = CEPH_CAP_PIN;

		/*
		 * auth mds of the inode changed. we received the cap export
		 * message, but still haven't received the cap import message.
		 * handle_cap_export() updated the new auth MDS' cap.
		 *
		 * "ceph_seq_cmp(seq, cap->seq) <= 0" means we are processing
		 * a message that was send beक्रमe the cap import message. So
		 * करोn't हटाओ caps.
		 */
		अगर (ceph_seq_cmp(seq, cap->seq) <= 0) अणु
			WARN_ON(cap != ci->i_auth_cap);
			WARN_ON(cap->cap_id != cap_id);
			seq = cap->seq;
			mseq = cap->mseq;
			issued |= cap->issued;
			flags |= CEPH_CAP_FLAG_AUTH;
		पूर्ण
	पूर्ण

	अगर (!ci->i_snap_realm ||
	    ((flags & CEPH_CAP_FLAG_AUTH) &&
	     realmino != (u64)-1 && ci->i_snap_realm->ino != realmino)) अणु
		/*
		 * add this inode to the appropriate snap realm
		 */
		काष्ठा ceph_snap_realm *realm = ceph_lookup_snap_realm(mdsc,
							       realmino);
		अगर (realm) अणु
			काष्ठा ceph_snap_realm *oldrealm = ci->i_snap_realm;
			अगर (oldrealm) अणु
				spin_lock(&oldrealm->inodes_with_caps_lock);
				list_del_init(&ci->i_snap_realm_item);
				spin_unlock(&oldrealm->inodes_with_caps_lock);
			पूर्ण

			spin_lock(&realm->inodes_with_caps_lock);
			list_add(&ci->i_snap_realm_item,
				 &realm->inodes_with_caps);
			ci->i_snap_realm = realm;
			अगर (realm->ino == ci->i_vino.ino)
				realm->inode = inode;
			spin_unlock(&realm->inodes_with_caps_lock);

			अगर (oldrealm)
				ceph_put_snap_realm(mdsc, oldrealm);
		पूर्ण अन्यथा अणु
			pr_err("ceph_add_cap: couldn't find snap realm %llx\n",
			       realmino);
			WARN_ON(!realm);
		पूर्ण
	पूर्ण

	__check_cap_issue(ci, cap, issued);

	/*
	 * If we are issued caps we करोn't want, or the mds' wanted
	 * value appears to be off, queue a check so we'll release
	 * later and/or update the mds wanted value.
	 */
	actual_wanted = __ceph_caps_wanted(ci);
	अगर ((wanted & ~actual_wanted) ||
	    (issued & ~actual_wanted & CEPH_CAP_ANY_WR)) अणु
		करोut(" issued %s, mds wanted %s, actual %s, queueing\n",
		     ceph_cap_string(issued), ceph_cap_string(wanted),
		     ceph_cap_string(actual_wanted));
		__cap_delay_requeue(mdsc, ci);
	पूर्ण

	अगर (flags & CEPH_CAP_FLAG_AUTH) अणु
		अगर (!ci->i_auth_cap ||
		    ceph_seq_cmp(ci->i_auth_cap->mseq, mseq) < 0) अणु
			अगर (ci->i_auth_cap &&
			    ci->i_auth_cap->session != cap->session)
				change_auth_cap_ses(ci, cap->session);
			ci->i_auth_cap = cap;
			cap->mds_wanted = wanted;
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON(ci->i_auth_cap == cap);
	पूर्ण

	करोut("add_cap inode %p (%llx.%llx) cap %p %s now %s seq %d mds%d\n",
	     inode, ceph_vinop(inode), cap, ceph_cap_string(issued),
	     ceph_cap_string(issued|cap->issued), seq, mds);
	cap->cap_id = cap_id;
	cap->issued = issued;
	cap->implemented |= issued;
	अगर (ceph_seq_cmp(mseq, cap->mseq) > 0)
		cap->mds_wanted = wanted;
	अन्यथा
		cap->mds_wanted |= wanted;
	cap->seq = seq;
	cap->issue_seq = seq;
	cap->mseq = mseq;
	cap->cap_gen = gen;
पूर्ण

/*
 * Return true अगर cap has not समयd out and beदीर्घs to the current
 * generation of the MDS session (i.e. has not gone 'stale' due to
 * us losing touch with the mds).
 */
अटल पूर्णांक __cap_is_valid(काष्ठा ceph_cap *cap)
अणु
	अचिन्हित दीर्घ ttl;
	u32 gen;

	spin_lock(&cap->session->s_gen_ttl_lock);
	gen = cap->session->s_cap_gen;
	ttl = cap->session->s_cap_ttl;
	spin_unlock(&cap->session->s_gen_ttl_lock);

	अगर (cap->cap_gen < gen || समय_after_eq(jअगरfies, ttl)) अणु
		करोut("__cap_is_valid %p cap %p issued %s "
		     "but STALE (gen %u vs %u)\n", &cap->ci->vfs_inode,
		     cap, ceph_cap_string(cap->issued), cap->cap_gen, gen);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Return set of valid cap bits issued to us.  Note that caps समय
 * out, and may be invalidated in bulk अगर the client session बार out
 * and session->s_cap_gen is bumped.
 */
पूर्णांक __ceph_caps_issued(काष्ठा ceph_inode_info *ci, पूर्णांक *implemented)
अणु
	पूर्णांक have = ci->i_snap_caps;
	काष्ठा ceph_cap *cap;
	काष्ठा rb_node *p;

	अगर (implemented)
		*implemented = 0;
	क्रम (p = rb_first(&ci->i_caps); p; p = rb_next(p)) अणु
		cap = rb_entry(p, काष्ठा ceph_cap, ci_node);
		अगर (!__cap_is_valid(cap))
			जारी;
		करोut("__ceph_caps_issued %p cap %p issued %s\n",
		     &ci->vfs_inode, cap, ceph_cap_string(cap->issued));
		have |= cap->issued;
		अगर (implemented)
			*implemented |= cap->implemented;
	पूर्ण
	/*
	 * exclude caps issued by non-auth MDS, but are been revoking
	 * by the auth MDS. The non-auth MDS should be revoking/exporting
	 * these caps, but the message is delayed.
	 */
	अगर (ci->i_auth_cap) अणु
		cap = ci->i_auth_cap;
		have &= ~cap->implemented | cap->issued;
	पूर्ण
	वापस have;
पूर्ण

/*
 * Get cap bits issued by caps other than @ocap
 */
पूर्णांक __ceph_caps_issued_other(काष्ठा ceph_inode_info *ci, काष्ठा ceph_cap *ocap)
अणु
	पूर्णांक have = ci->i_snap_caps;
	काष्ठा ceph_cap *cap;
	काष्ठा rb_node *p;

	क्रम (p = rb_first(&ci->i_caps); p; p = rb_next(p)) अणु
		cap = rb_entry(p, काष्ठा ceph_cap, ci_node);
		अगर (cap == ocap)
			जारी;
		अगर (!__cap_is_valid(cap))
			जारी;
		have |= cap->issued;
	पूर्ण
	वापस have;
पूर्ण

/*
 * Move a cap to the end of the LRU (oldest caps at list head, newest
 * at list tail).
 */
अटल व्योम __touch_cap(काष्ठा ceph_cap *cap)
अणु
	काष्ठा ceph_mds_session *s = cap->session;

	spin_lock(&s->s_cap_lock);
	अगर (!s->s_cap_iterator) अणु
		करोut("__touch_cap %p cap %p mds%d\n", &cap->ci->vfs_inode, cap,
		     s->s_mds);
		list_move_tail(&cap->session_caps, &s->s_caps);
	पूर्ण अन्यथा अणु
		करोut("__touch_cap %p cap %p mds%d NOP, iterating over caps\n",
		     &cap->ci->vfs_inode, cap, s->s_mds);
	पूर्ण
	spin_unlock(&s->s_cap_lock);
पूर्ण

/*
 * Check अगर we hold the given mask.  If so, move the cap(s) to the
 * front of their respective LRUs.  (This is the preferred way क्रम
 * callers to check क्रम caps they want.)
 */
पूर्णांक __ceph_caps_issued_mask(काष्ठा ceph_inode_info *ci, पूर्णांक mask, पूर्णांक touch)
अणु
	काष्ठा ceph_cap *cap;
	काष्ठा rb_node *p;
	पूर्णांक have = ci->i_snap_caps;

	अगर ((have & mask) == mask) अणु
		करोut("__ceph_caps_issued_mask ino 0x%llx snap issued %s"
		     " (mask %s)\n", ceph_ino(&ci->vfs_inode),
		     ceph_cap_string(have),
		     ceph_cap_string(mask));
		वापस 1;
	पूर्ण

	क्रम (p = rb_first(&ci->i_caps); p; p = rb_next(p)) अणु
		cap = rb_entry(p, काष्ठा ceph_cap, ci_node);
		अगर (!__cap_is_valid(cap))
			जारी;
		अगर ((cap->issued & mask) == mask) अणु
			करोut("__ceph_caps_issued_mask ino 0x%llx cap %p issued %s"
			     " (mask %s)\n", ceph_ino(&ci->vfs_inode), cap,
			     ceph_cap_string(cap->issued),
			     ceph_cap_string(mask));
			अगर (touch)
				__touch_cap(cap);
			वापस 1;
		पूर्ण

		/* करोes a combination of caps satisfy mask? */
		have |= cap->issued;
		अगर ((have & mask) == mask) अणु
			करोut("__ceph_caps_issued_mask ino 0x%llx combo issued %s"
			     " (mask %s)\n", ceph_ino(&ci->vfs_inode),
			     ceph_cap_string(cap->issued),
			     ceph_cap_string(mask));
			अगर (touch) अणु
				काष्ठा rb_node *q;

				/* touch this + preceding caps */
				__touch_cap(cap);
				क्रम (q = rb_first(&ci->i_caps); q != p;
				     q = rb_next(q)) अणु
					cap = rb_entry(q, काष्ठा ceph_cap,
						       ci_node);
					अगर (!__cap_is_valid(cap))
						जारी;
					अगर (cap->issued & mask)
						__touch_cap(cap);
				पूर्ण
			पूर्ण
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __ceph_caps_issued_mask_metric(काष्ठा ceph_inode_info *ci, पूर्णांक mask,
				   पूर्णांक touch)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(ci->vfs_inode.i_sb);
	पूर्णांक r;

	r = __ceph_caps_issued_mask(ci, mask, touch);
	अगर (r)
		ceph_update_cap_hit(&fsc->mdsc->metric);
	अन्यथा
		ceph_update_cap_mis(&fsc->mdsc->metric);
	वापस r;
पूर्ण

/*
 * Return true अगर mask caps are currently being revoked by an MDS.
 */
पूर्णांक __ceph_caps_revoking_other(काष्ठा ceph_inode_info *ci,
			       काष्ठा ceph_cap *ocap, पूर्णांक mask)
अणु
	काष्ठा ceph_cap *cap;
	काष्ठा rb_node *p;

	क्रम (p = rb_first(&ci->i_caps); p; p = rb_next(p)) अणु
		cap = rb_entry(p, काष्ठा ceph_cap, ci_node);
		अगर (cap != ocap &&
		    (cap->implemented & ~cap->issued & mask))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ceph_caps_revoking(काष्ठा ceph_inode_info *ci, पूर्णांक mask)
अणु
	काष्ठा inode *inode = &ci->vfs_inode;
	पूर्णांक ret;

	spin_lock(&ci->i_ceph_lock);
	ret = __ceph_caps_revoking_other(ci, शून्य, mask);
	spin_unlock(&ci->i_ceph_lock);
	करोut("ceph_caps_revoking %p %s = %d\n", inode,
	     ceph_cap_string(mask), ret);
	वापस ret;
पूर्ण

पूर्णांक __ceph_caps_used(काष्ठा ceph_inode_info *ci)
अणु
	पूर्णांक used = 0;
	अगर (ci->i_pin_ref)
		used |= CEPH_CAP_PIN;
	अगर (ci->i_rd_ref)
		used |= CEPH_CAP_खाता_RD;
	अगर (ci->i_rdcache_ref ||
	    (S_ISREG(ci->vfs_inode.i_mode) &&
	     ci->vfs_inode.i_data.nrpages))
		used |= CEPH_CAP_खाता_CACHE;
	अगर (ci->i_wr_ref)
		used |= CEPH_CAP_खाता_WR;
	अगर (ci->i_wb_ref || ci->i_wrbuffer_ref)
		used |= CEPH_CAP_खाता_BUFFER;
	अगर (ci->i_fx_ref)
		used |= CEPH_CAP_खाता_EXCL;
	वापस used;
पूर्ण

#घोषणा FMODE_WAIT_BIAS 1000

/*
 * wanted, by virtue of खोलो file modes
 */
पूर्णांक __ceph_caps_file_wanted(काष्ठा ceph_inode_info *ci)
अणु
	स्थिर पूर्णांक PIN_SHIFT = ffs(CEPH_खाता_MODE_PIN);
	स्थिर पूर्णांक RD_SHIFT = ffs(CEPH_खाता_MODE_RD);
	स्थिर पूर्णांक WR_SHIFT = ffs(CEPH_खाता_MODE_WR);
	स्थिर पूर्णांक LAZY_SHIFT = ffs(CEPH_खाता_MODE_LAZY);
	काष्ठा ceph_mount_options *opt =
		ceph_inode_to_client(&ci->vfs_inode)->mount_options;
	अचिन्हित दीर्घ used_cutoff = jअगरfies - opt->caps_wanted_delay_max * HZ;
	अचिन्हित दीर्घ idle_cutoff = jअगरfies - opt->caps_wanted_delay_min * HZ;

	अगर (S_ISसूची(ci->vfs_inode.i_mode)) अणु
		पूर्णांक want = 0;

		/* use used_cutoff here, to keep dir's wanted caps दीर्घer */
		अगर (ci->i_nr_by_mode[RD_SHIFT] > 0 ||
		    समय_after(ci->i_last_rd, used_cutoff))
			want |= CEPH_CAP_ANY_SHARED;

		अगर (ci->i_nr_by_mode[WR_SHIFT] > 0 ||
		    समय_after(ci->i_last_wr, used_cutoff)) अणु
			want |= CEPH_CAP_ANY_SHARED | CEPH_CAP_खाता_EXCL;
			अगर (opt->flags & CEPH_MOUNT_OPT_ASYNC_सूचीOPS)
				want |= CEPH_CAP_ANY_सूची_OPS;
		पूर्ण

		अगर (want || ci->i_nr_by_mode[PIN_SHIFT] > 0)
			want |= CEPH_CAP_PIN;

		वापस want;
	पूर्ण अन्यथा अणु
		पूर्णांक bits = 0;

		अगर (ci->i_nr_by_mode[RD_SHIFT] > 0) अणु
			अगर (ci->i_nr_by_mode[RD_SHIFT] >= FMODE_WAIT_BIAS ||
			    समय_after(ci->i_last_rd, used_cutoff))
				bits |= 1 << RD_SHIFT;
		पूर्ण अन्यथा अगर (समय_after(ci->i_last_rd, idle_cutoff)) अणु
			bits |= 1 << RD_SHIFT;
		पूर्ण

		अगर (ci->i_nr_by_mode[WR_SHIFT] > 0) अणु
			अगर (ci->i_nr_by_mode[WR_SHIFT] >= FMODE_WAIT_BIAS ||
			    समय_after(ci->i_last_wr, used_cutoff))
				bits |= 1 << WR_SHIFT;
		पूर्ण अन्यथा अगर (समय_after(ci->i_last_wr, idle_cutoff)) अणु
			bits |= 1 << WR_SHIFT;
		पूर्ण

		/* check lazyio only when पढ़ो/ग_लिखो is wanted */
		अगर ((bits & (CEPH_खाता_MODE_RDWR << 1)) &&
		    ci->i_nr_by_mode[LAZY_SHIFT] > 0)
			bits |= 1 << LAZY_SHIFT;

		वापस bits ? ceph_caps_क्रम_mode(bits >> 1) : 0;
	पूर्ण
पूर्ण

/*
 * wanted, by virtue of खोलो file modes AND cap refs (buffered/cached data)
 */
पूर्णांक __ceph_caps_wanted(काष्ठा ceph_inode_info *ci)
अणु
	पूर्णांक w = __ceph_caps_file_wanted(ci) | __ceph_caps_used(ci);
	अगर (S_ISसूची(ci->vfs_inode.i_mode)) अणु
		/* we want EXCL अगर holding caps of dir ops */
		अगर (w & CEPH_CAP_ANY_सूची_OPS)
			w |= CEPH_CAP_खाता_EXCL;
	पूर्ण अन्यथा अणु
		/* we want EXCL अगर dirty data */
		अगर (w & CEPH_CAP_खाता_BUFFER)
			w |= CEPH_CAP_खाता_EXCL;
	पूर्ण
	वापस w;
पूर्ण

/*
 * Return caps we have रेजिस्टरed with the MDS(s) as 'wanted'.
 */
पूर्णांक __ceph_caps_mds_wanted(काष्ठा ceph_inode_info *ci, bool check)
अणु
	काष्ठा ceph_cap *cap;
	काष्ठा rb_node *p;
	पूर्णांक mds_wanted = 0;

	क्रम (p = rb_first(&ci->i_caps); p; p = rb_next(p)) अणु
		cap = rb_entry(p, काष्ठा ceph_cap, ci_node);
		अगर (check && !__cap_is_valid(cap))
			जारी;
		अगर (cap == ci->i_auth_cap)
			mds_wanted |= cap->mds_wanted;
		अन्यथा
			mds_wanted |= (cap->mds_wanted & ~CEPH_CAP_ANY_खाता_WR);
	पूर्ण
	वापस mds_wanted;
पूर्ण

पूर्णांक ceph_is_any_caps(काष्ठा inode *inode)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक ret;

	spin_lock(&ci->i_ceph_lock);
	ret = __ceph_is_any_real_caps(ci);
	spin_unlock(&ci->i_ceph_lock);

	वापस ret;
पूर्ण

अटल व्योम drop_inode_snap_realm(काष्ठा ceph_inode_info *ci)
अणु
	काष्ठा ceph_snap_realm *realm = ci->i_snap_realm;
	spin_lock(&realm->inodes_with_caps_lock);
	list_del_init(&ci->i_snap_realm_item);
	ci->i_snap_realm_counter++;
	ci->i_snap_realm = शून्य;
	अगर (realm->ino == ci->i_vino.ino)
		realm->inode = शून्य;
	spin_unlock(&realm->inodes_with_caps_lock);
	ceph_put_snap_realm(ceph_sb_to_client(ci->vfs_inode.i_sb)->mdsc,
			    realm);
पूर्ण

/*
 * Remove a cap.  Take steps to deal with a racing iterate_session_caps.
 *
 * caller should hold i_ceph_lock.
 * caller will not hold session s_mutex अगर called from destroy_inode.
 */
व्योम __ceph_हटाओ_cap(काष्ठा ceph_cap *cap, bool queue_release)
अणु
	काष्ठा ceph_mds_session *session = cap->session;
	काष्ठा ceph_inode_info *ci = cap->ci;
	काष्ठा ceph_mds_client *mdsc;
	पूर्णांक हटाओd = 0;

	/* 'ci' being शून्य means the हटाओ have alपढ़ोy occurred */
	अगर (!ci) अणु
		करोut("%s: cap inode is NULL\n", __func__);
		वापस;
	पूर्ण

	करोut("__ceph_remove_cap %p from %p\n", cap, &ci->vfs_inode);

	mdsc = ceph_inode_to_client(&ci->vfs_inode)->mdsc;

	/* हटाओ from inode's cap rbtree, and clear auth cap */
	rb_erase(&cap->ci_node, &ci->i_caps);
	अगर (ci->i_auth_cap == cap) अणु
		WARN_ON_ONCE(!list_empty(&ci->i_dirty_item) &&
			     !mdsc->fsc->blocklisted);
		ci->i_auth_cap = शून्य;
	पूर्ण

	/* हटाओ from session list */
	spin_lock(&session->s_cap_lock);
	अगर (session->s_cap_iterator == cap) अणु
		/* not yet, we are iterating over this very cap */
		करोut("__ceph_remove_cap  delaying %p removal from session %p\n",
		     cap, cap->session);
	पूर्ण अन्यथा अणु
		list_del_init(&cap->session_caps);
		session->s_nr_caps--;
		atomic64_dec(&mdsc->metric.total_caps);
		cap->session = शून्य;
		हटाओd = 1;
	पूर्ण
	/* protect backpoपूर्णांकer with s_cap_lock: see iterate_session_caps */
	cap->ci = शून्य;

	/*
	 * s_cap_reconnect is रक्षित by s_cap_lock. no one changes
	 * s_cap_gen जबतक session is in the reconnect state.
	 */
	अगर (queue_release &&
	    (!session->s_cap_reconnect || cap->cap_gen == session->s_cap_gen)) अणु
		cap->queue_release = 1;
		अगर (हटाओd) अणु
			__ceph_queue_cap_release(session, cap);
			हटाओd = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		cap->queue_release = 0;
	पूर्ण
	cap->cap_ino = ci->i_vino.ino;

	spin_unlock(&session->s_cap_lock);

	अगर (हटाओd)
		ceph_put_cap(mdsc, cap);

	अगर (!__ceph_is_any_real_caps(ci)) अणु
		/* when reconnect denied, we हटाओ session caps क्रमcibly,
		 * i_wr_ref can be non-zero. If there are ongoing ग_लिखो,
		 * keep i_snap_realm.
		 */
		अगर (ci->i_wr_ref == 0 && ci->i_snap_realm)
			drop_inode_snap_realm(ci);

		__cap_delay_cancel(mdsc, ci);
	पूर्ण
पूर्ण

काष्ठा cap_msg_args अणु
	काष्ठा ceph_mds_session	*session;
	u64			ino, cid, follows;
	u64			flush_tid, oldest_flush_tid, size, max_size;
	u64			xattr_version;
	u64			change_attr;
	काष्ठा ceph_buffer	*xattr_buf;
	काष्ठा ceph_buffer	*old_xattr_buf;
	काष्ठा बारpec64	aसमय, mसमय, स_समय, bसमय;
	पूर्णांक			op, caps, wanted, dirty;
	u32			seq, issue_seq, mseq, समय_warp_seq;
	u32			flags;
	kuid_t			uid;
	kgid_t			gid;
	umode_t			mode;
	bool			अंतरभूत_data;
	bool			wake;
पूर्ण;

/*
 * cap काष्ठा size + flock buffer size + अंतरभूत version + अंतरभूत data size +
 * osd_epoch_barrier + oldest_flush_tid
 */
#घोषणा CAP_MSG_SIZE (माप(काष्ठा ceph_mds_caps) + \
		      4 + 8 + 4 + 4 + 8 + 4 + 4 + 4 + 8 + 8 + 4)

/* Marshal up the cap msg to the MDS */
अटल व्योम encode_cap_msg(काष्ठा ceph_msg *msg, काष्ठा cap_msg_args *arg)
अणु
	काष्ठा ceph_mds_caps *fc;
	व्योम *p;
	काष्ठा ceph_osd_client *osdc = &arg->session->s_mdsc->fsc->client->osdc;

	करोut("%s %s %llx %llx caps %s wanted %s dirty %s seq %u/%u tid %llu/%llu mseq %u follows %lld size %llu/%llu xattr_ver %llu xattr_len %d\n",
	     __func__, ceph_cap_op_name(arg->op), arg->cid, arg->ino,
	     ceph_cap_string(arg->caps), ceph_cap_string(arg->wanted),
	     ceph_cap_string(arg->dirty), arg->seq, arg->issue_seq,
	     arg->flush_tid, arg->oldest_flush_tid, arg->mseq, arg->follows,
	     arg->size, arg->max_size, arg->xattr_version,
	     arg->xattr_buf ? (पूर्णांक)arg->xattr_buf->vec.iov_len : 0);

	msg->hdr.version = cpu_to_le16(10);
	msg->hdr.tid = cpu_to_le64(arg->flush_tid);

	fc = msg->front.iov_base;
	स_रखो(fc, 0, माप(*fc));

	fc->cap_id = cpu_to_le64(arg->cid);
	fc->op = cpu_to_le32(arg->op);
	fc->seq = cpu_to_le32(arg->seq);
	fc->issue_seq = cpu_to_le32(arg->issue_seq);
	fc->migrate_seq = cpu_to_le32(arg->mseq);
	fc->caps = cpu_to_le32(arg->caps);
	fc->wanted = cpu_to_le32(arg->wanted);
	fc->dirty = cpu_to_le32(arg->dirty);
	fc->ino = cpu_to_le64(arg->ino);
	fc->snap_follows = cpu_to_le64(arg->follows);

	fc->size = cpu_to_le64(arg->size);
	fc->max_size = cpu_to_le64(arg->max_size);
	ceph_encode_बारpec64(&fc->mसमय, &arg->mसमय);
	ceph_encode_बारpec64(&fc->aसमय, &arg->aसमय);
	ceph_encode_बारpec64(&fc->स_समय, &arg->स_समय);
	fc->समय_warp_seq = cpu_to_le32(arg->समय_warp_seq);

	fc->uid = cpu_to_le32(from_kuid(&init_user_ns, arg->uid));
	fc->gid = cpu_to_le32(from_kgid(&init_user_ns, arg->gid));
	fc->mode = cpu_to_le32(arg->mode);

	fc->xattr_version = cpu_to_le64(arg->xattr_version);
	अगर (arg->xattr_buf) अणु
		msg->middle = ceph_buffer_get(arg->xattr_buf);
		fc->xattr_len = cpu_to_le32(arg->xattr_buf->vec.iov_len);
		msg->hdr.middle_len = cpu_to_le32(arg->xattr_buf->vec.iov_len);
	पूर्ण

	p = fc + 1;
	/* flock buffer size (version 2) */
	ceph_encode_32(&p, 0);
	/* अंतरभूत version (version 4) */
	ceph_encode_64(&p, arg->अंतरभूत_data ? 0 : CEPH_INLINE_NONE);
	/* अंतरभूत data size */
	ceph_encode_32(&p, 0);
	/*
	 * osd_epoch_barrier (version 5)
	 * The epoch_barrier is रक्षित osdc->lock, so READ_ONCE here in
	 * हाल it was recently changed
	 */
	ceph_encode_32(&p, READ_ONCE(osdc->epoch_barrier));
	/* oldest_flush_tid (version 6) */
	ceph_encode_64(&p, arg->oldest_flush_tid);

	/*
	 * caller_uid/caller_gid (version 7)
	 *
	 * Currently, we करोn't properly track which caller dirtied the caps
	 * last, and क्रमce a flush of them when there is a conflict. For now,
	 * just set this to 0:0, to emulate how the MDS has worked up to now.
	 */
	ceph_encode_32(&p, 0);
	ceph_encode_32(&p, 0);

	/* pool namespace (version 8) (mds always ignores this) */
	ceph_encode_32(&p, 0);

	/* bसमय and change_attr (version 9) */
	ceph_encode_बारpec64(p, &arg->bसमय);
	p += माप(काष्ठा ceph_बारpec);
	ceph_encode_64(&p, arg->change_attr);

	/* Advisory flags (version 10) */
	ceph_encode_32(&p, arg->flags);
पूर्ण

/*
 * Queue cap releases when an inode is dropped from our cache.
 */
व्योम __ceph_हटाओ_caps(काष्ठा ceph_inode_info *ci)
अणु
	काष्ठा rb_node *p;

	/* lock i_ceph_lock, because ceph_d_revalidate(..., LOOKUP_RCU)
	 * may call __ceph_caps_issued_mask() on a मुक्तing inode. */
	spin_lock(&ci->i_ceph_lock);
	p = rb_first(&ci->i_caps);
	जबतक (p) अणु
		काष्ठा ceph_cap *cap = rb_entry(p, काष्ठा ceph_cap, ci_node);
		p = rb_next(p);
		__ceph_हटाओ_cap(cap, true);
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);
पूर्ण

/*
 * Prepare to send a cap message to an MDS. Update the cap state, and populate
 * the arg काष्ठा with the parameters that will need to be sent. This should
 * be करोne under the i_ceph_lock to guard against changes to cap state.
 *
 * Make note of max_size reported/requested from mds, revoked caps
 * that have now been implemented.
 */
अटल व्योम __prep_cap(काष्ठा cap_msg_args *arg, काष्ठा ceph_cap *cap,
		       पूर्णांक op, पूर्णांक flags, पूर्णांक used, पूर्णांक want, पूर्णांक retain,
		       पूर्णांक flushing, u64 flush_tid, u64 oldest_flush_tid)
अणु
	काष्ठा ceph_inode_info *ci = cap->ci;
	काष्ठा inode *inode = &ci->vfs_inode;
	पूर्णांक held, revoking;

	lockdep_निश्चित_held(&ci->i_ceph_lock);

	held = cap->issued | cap->implemented;
	revoking = cap->implemented & ~cap->issued;
	retain &= ~revoking;

	करोut("%s %p cap %p session %p %s -> %s (revoking %s)\n",
	     __func__, inode, cap, cap->session,
	     ceph_cap_string(held), ceph_cap_string(held & retain),
	     ceph_cap_string(revoking));
	BUG_ON((retain & CEPH_CAP_PIN) == 0);

	ci->i_ceph_flags &= ~CEPH_I_FLUSH;

	cap->issued &= retain;  /* drop bits we करोn't want */
	/*
	 * Wake up any रुकोers on wanted -> needed transition. This is due to
	 * the weird transition from buffered to sync IO... we need to flush
	 * dirty pages _beक्रमe_ allowing sync ग_लिखोs to aव्योम reordering.
	 */
	arg->wake = cap->implemented & ~cap->issued;
	cap->implemented &= cap->issued | used;
	cap->mds_wanted = want;

	arg->session = cap->session;
	arg->ino = ceph_vino(inode).ino;
	arg->cid = cap->cap_id;
	arg->follows = flushing ? ci->i_head_snapc->seq : 0;
	arg->flush_tid = flush_tid;
	arg->oldest_flush_tid = oldest_flush_tid;

	arg->size = i_size_पढ़ो(inode);
	ci->i_reported_size = arg->size;
	arg->max_size = ci->i_wanted_max_size;
	अगर (cap == ci->i_auth_cap) अणु
		अगर (want & CEPH_CAP_ANY_खाता_WR)
			ci->i_requested_max_size = arg->max_size;
		अन्यथा
			ci->i_requested_max_size = 0;
	पूर्ण

	अगर (flushing & CEPH_CAP_XATTR_EXCL) अणु
		arg->old_xattr_buf = __ceph_build_xattrs_blob(ci);
		arg->xattr_version = ci->i_xattrs.version;
		arg->xattr_buf = ci->i_xattrs.blob;
	पूर्ण अन्यथा अणु
		arg->xattr_buf = शून्य;
		arg->old_xattr_buf = शून्य;
	पूर्ण

	arg->mसमय = inode->i_mसमय;
	arg->aसमय = inode->i_aसमय;
	arg->स_समय = inode->i_स_समय;
	arg->bसमय = ci->i_bसमय;
	arg->change_attr = inode_peek_iversion_raw(inode);

	arg->op = op;
	arg->caps = cap->implemented;
	arg->wanted = want;
	arg->dirty = flushing;

	arg->seq = cap->seq;
	arg->issue_seq = cap->issue_seq;
	arg->mseq = cap->mseq;
	arg->समय_warp_seq = ci->i_समय_warp_seq;

	arg->uid = inode->i_uid;
	arg->gid = inode->i_gid;
	arg->mode = inode->i_mode;

	arg->अंतरभूत_data = ci->i_अंतरभूत_version != CEPH_INLINE_NONE;
	अगर (!(flags & CEPH_CLIENT_CAPS_PENDING_CAPSNAP) &&
	    !list_empty(&ci->i_cap_snaps)) अणु
		काष्ठा ceph_cap_snap *capsnap;
		list_क्रम_each_entry_reverse(capsnap, &ci->i_cap_snaps, ci_item) अणु
			अगर (capsnap->cap_flush.tid)
				अवरोध;
			अगर (capsnap->need_flush) अणु
				flags |= CEPH_CLIENT_CAPS_PENDING_CAPSNAP;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	arg->flags = flags;
पूर्ण

/*
 * Send a cap msg on the given inode.
 *
 * Caller should hold snap_rwsem (पढ़ो), s_mutex.
 */
अटल व्योम __send_cap(काष्ठा cap_msg_args *arg, काष्ठा ceph_inode_info *ci)
अणु
	काष्ठा ceph_msg *msg;
	काष्ठा inode *inode = &ci->vfs_inode;

	msg = ceph_msg_new(CEPH_MSG_CLIENT_CAPS, CAP_MSG_SIZE, GFP_NOFS, false);
	अगर (!msg) अणु
		pr_err("error allocating cap msg: ino (%llx.%llx) flushing %s tid %llu, requeuing cap.\n",
		       ceph_vinop(inode), ceph_cap_string(arg->dirty),
		       arg->flush_tid);
		spin_lock(&ci->i_ceph_lock);
		__cap_delay_requeue(arg->session->s_mdsc, ci);
		spin_unlock(&ci->i_ceph_lock);
		वापस;
	पूर्ण

	encode_cap_msg(msg, arg);
	ceph_con_send(&arg->session->s_con, msg);
	ceph_buffer_put(arg->old_xattr_buf);
	अगर (arg->wake)
		wake_up_all(&ci->i_cap_wq);
पूर्ण

अटल अंतरभूत पूर्णांक __send_flush_snap(काष्ठा inode *inode,
				    काष्ठा ceph_mds_session *session,
				    काष्ठा ceph_cap_snap *capsnap,
				    u32 mseq, u64 oldest_flush_tid)
अणु
	काष्ठा cap_msg_args	arg;
	काष्ठा ceph_msg		*msg;

	msg = ceph_msg_new(CEPH_MSG_CLIENT_CAPS, CAP_MSG_SIZE, GFP_NOFS, false);
	अगर (!msg)
		वापस -ENOMEM;

	arg.session = session;
	arg.ino = ceph_vino(inode).ino;
	arg.cid = 0;
	arg.follows = capsnap->follows;
	arg.flush_tid = capsnap->cap_flush.tid;
	arg.oldest_flush_tid = oldest_flush_tid;

	arg.size = capsnap->size;
	arg.max_size = 0;
	arg.xattr_version = capsnap->xattr_version;
	arg.xattr_buf = capsnap->xattr_blob;
	arg.old_xattr_buf = शून्य;

	arg.aसमय = capsnap->aसमय;
	arg.mसमय = capsnap->mसमय;
	arg.स_समय = capsnap->स_समय;
	arg.bसमय = capsnap->bसमय;
	arg.change_attr = capsnap->change_attr;

	arg.op = CEPH_CAP_OP_FLUSHSNAP;
	arg.caps = capsnap->issued;
	arg.wanted = 0;
	arg.dirty = capsnap->dirty;

	arg.seq = 0;
	arg.issue_seq = 0;
	arg.mseq = mseq;
	arg.समय_warp_seq = capsnap->समय_warp_seq;

	arg.uid = capsnap->uid;
	arg.gid = capsnap->gid;
	arg.mode = capsnap->mode;

	arg.अंतरभूत_data = capsnap->अंतरभूत_data;
	arg.flags = 0;
	arg.wake = false;

	encode_cap_msg(msg, &arg);
	ceph_con_send(&arg.session->s_con, msg);
	वापस 0;
पूर्ण

/*
 * When a snapshot is taken, clients accumulate dirty metadata on
 * inodes with capabilities in ceph_cap_snaps to describe the file
 * state at the समय the snapshot was taken.  This must be flushed
 * asynchronously back to the MDS once sync ग_लिखोs complete and dirty
 * data is written out.
 *
 * Called under i_ceph_lock.  Takes s_mutex as needed.
 */
अटल व्योम __ceph_flush_snaps(काष्ठा ceph_inode_info *ci,
			       काष्ठा ceph_mds_session *session)
		__releases(ci->i_ceph_lock)
		__acquires(ci->i_ceph_lock)
अणु
	काष्ठा inode *inode = &ci->vfs_inode;
	काष्ठा ceph_mds_client *mdsc = session->s_mdsc;
	काष्ठा ceph_cap_snap *capsnap;
	u64 oldest_flush_tid = 0;
	u64 first_tid = 1, last_tid = 0;

	करोut("__flush_snaps %p session %p\n", inode, session);

	list_क्रम_each_entry(capsnap, &ci->i_cap_snaps, ci_item) अणु
		/*
		 * we need to रुको क्रम sync ग_लिखोs to complete and क्रम dirty
		 * pages to be written out.
		 */
		अगर (capsnap->dirty_pages || capsnap->writing)
			अवरोध;

		/* should be हटाओd by ceph_try_drop_cap_snap() */
		BUG_ON(!capsnap->need_flush);

		/* only flush each capsnap once */
		अगर (capsnap->cap_flush.tid > 0) अणु
			करोut(" already flushed %p, skipping\n", capsnap);
			जारी;
		पूर्ण

		spin_lock(&mdsc->cap_dirty_lock);
		capsnap->cap_flush.tid = ++mdsc->last_cap_flush_tid;
		list_add_tail(&capsnap->cap_flush.g_list,
			      &mdsc->cap_flush_list);
		अगर (oldest_flush_tid == 0)
			oldest_flush_tid = __get_oldest_flush_tid(mdsc);
		अगर (list_empty(&ci->i_flushing_item)) अणु
			list_add_tail(&ci->i_flushing_item,
				      &session->s_cap_flushing);
		पूर्ण
		spin_unlock(&mdsc->cap_dirty_lock);

		list_add_tail(&capsnap->cap_flush.i_list,
			      &ci->i_cap_flush_list);

		अगर (first_tid == 1)
			first_tid = capsnap->cap_flush.tid;
		last_tid = capsnap->cap_flush.tid;
	पूर्ण

	ci->i_ceph_flags &= ~CEPH_I_FLUSH_SNAPS;

	जबतक (first_tid <= last_tid) अणु
		काष्ठा ceph_cap *cap = ci->i_auth_cap;
		काष्ठा ceph_cap_flush *cf;
		पूर्णांक ret;

		अगर (!(cap && cap->session == session)) अणु
			करोut("__flush_snaps %p auth cap %p not mds%d, "
			     "stop\n", inode, cap, session->s_mds);
			अवरोध;
		पूर्ण

		ret = -ENOENT;
		list_क्रम_each_entry(cf, &ci->i_cap_flush_list, i_list) अणु
			अगर (cf->tid >= first_tid) अणु
				ret = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (ret < 0)
			अवरोध;

		first_tid = cf->tid + 1;

		capsnap = container_of(cf, काष्ठा ceph_cap_snap, cap_flush);
		refcount_inc(&capsnap->nref);
		spin_unlock(&ci->i_ceph_lock);

		करोut("__flush_snaps %p capsnap %p tid %llu %s\n",
		     inode, capsnap, cf->tid, ceph_cap_string(capsnap->dirty));

		ret = __send_flush_snap(inode, session, capsnap, cap->mseq,
					oldest_flush_tid);
		अगर (ret < 0) अणु
			pr_err("__flush_snaps: error sending cap flushsnap, "
			       "ino (%llx.%llx) tid %llu follows %llu\n",
				ceph_vinop(inode), cf->tid, capsnap->follows);
		पूर्ण

		ceph_put_cap_snap(capsnap);
		spin_lock(&ci->i_ceph_lock);
	पूर्ण
पूर्ण

व्योम ceph_flush_snaps(काष्ठा ceph_inode_info *ci,
		      काष्ठा ceph_mds_session **psession)
अणु
	काष्ठा inode *inode = &ci->vfs_inode;
	काष्ठा ceph_mds_client *mdsc = ceph_inode_to_client(inode)->mdsc;
	काष्ठा ceph_mds_session *session = शून्य;
	पूर्णांक mds;

	करोut("ceph_flush_snaps %p\n", inode);
	अगर (psession)
		session = *psession;
retry:
	spin_lock(&ci->i_ceph_lock);
	अगर (!(ci->i_ceph_flags & CEPH_I_FLUSH_SNAPS)) अणु
		करोut(" no capsnap needs flush, doing nothing\n");
		जाओ out;
	पूर्ण
	अगर (!ci->i_auth_cap) अणु
		करोut(" no auth cap (migrating?), doing nothing\n");
		जाओ out;
	पूर्ण

	mds = ci->i_auth_cap->session->s_mds;
	अगर (session && session->s_mds != mds) अणु
		करोut(" oops, wrong session %p mutex\n", session);
		mutex_unlock(&session->s_mutex);
		ceph_put_mds_session(session);
		session = शून्य;
	पूर्ण
	अगर (!session) अणु
		spin_unlock(&ci->i_ceph_lock);
		mutex_lock(&mdsc->mutex);
		session = __ceph_lookup_mds_session(mdsc, mds);
		mutex_unlock(&mdsc->mutex);
		अगर (session) अणु
			करोut(" inverting session/ino locks on %p\n", session);
			mutex_lock(&session->s_mutex);
		पूर्ण
		जाओ retry;
	पूर्ण

	// make sure flushsnap messages are sent in proper order.
	अगर (ci->i_ceph_flags & CEPH_I_KICK_FLUSH)
		__kick_flushing_caps(mdsc, session, ci, 0);

	__ceph_flush_snaps(ci, session);
out:
	spin_unlock(&ci->i_ceph_lock);

	अगर (psession) अणु
		*psession = session;
	पूर्ण अन्यथा अगर (session) अणु
		mutex_unlock(&session->s_mutex);
		ceph_put_mds_session(session);
	पूर्ण
	/* we flushed them all; हटाओ this inode from the queue */
	spin_lock(&mdsc->snap_flush_lock);
	list_del_init(&ci->i_snap_flush_item);
	spin_unlock(&mdsc->snap_flush_lock);
पूर्ण

/*
 * Mark caps dirty.  If inode is newly dirty, वापस the dirty flags.
 * Caller is then responsible क्रम calling __mark_inode_dirty with the
 * वापसed flags value.
 */
पूर्णांक __ceph_mark_dirty_caps(काष्ठा ceph_inode_info *ci, पूर्णांक mask,
			   काष्ठा ceph_cap_flush **pcf)
अणु
	काष्ठा ceph_mds_client *mdsc =
		ceph_sb_to_client(ci->vfs_inode.i_sb)->mdsc;
	काष्ठा inode *inode = &ci->vfs_inode;
	पूर्णांक was = ci->i_dirty_caps;
	पूर्णांक dirty = 0;

	lockdep_निश्चित_held(&ci->i_ceph_lock);

	अगर (!ci->i_auth_cap) अणु
		pr_warn("__mark_dirty_caps %p %llx mask %s, "
			"but no auth cap (session was closed?)\n",
			inode, ceph_ino(inode), ceph_cap_string(mask));
		वापस 0;
	पूर्ण

	करोut("__mark_dirty_caps %p %s dirty %s -> %s\n", &ci->vfs_inode,
	     ceph_cap_string(mask), ceph_cap_string(was),
	     ceph_cap_string(was | mask));
	ci->i_dirty_caps |= mask;
	अगर (was == 0) अणु
		काष्ठा ceph_mds_session *session = ci->i_auth_cap->session;

		WARN_ON_ONCE(ci->i_pपुनः_स्मृति_cap_flush);
		swap(ci->i_pपुनः_स्मृति_cap_flush, *pcf);

		अगर (!ci->i_head_snapc) अणु
			WARN_ON_ONCE(!rwsem_is_locked(&mdsc->snap_rwsem));
			ci->i_head_snapc = ceph_get_snap_context(
				ci->i_snap_realm->cached_context);
		पूर्ण
		करोut(" inode %p now dirty snapc %p auth cap %p\n",
		     &ci->vfs_inode, ci->i_head_snapc, ci->i_auth_cap);
		BUG_ON(!list_empty(&ci->i_dirty_item));
		spin_lock(&mdsc->cap_dirty_lock);
		list_add(&ci->i_dirty_item, &session->s_cap_dirty);
		spin_unlock(&mdsc->cap_dirty_lock);
		अगर (ci->i_flushing_caps == 0) अणु
			ihold(inode);
			dirty |= I_सूचीTY_SYNC;
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(!ci->i_pपुनः_स्मृति_cap_flush);
	पूर्ण
	BUG_ON(list_empty(&ci->i_dirty_item));
	अगर (((was | ci->i_flushing_caps) & CEPH_CAP_खाता_BUFFER) &&
	    (mask & CEPH_CAP_खाता_BUFFER))
		dirty |= I_सूचीTY_DATASYNC;
	__cap_delay_requeue(mdsc, ci);
	वापस dirty;
पूर्ण

काष्ठा ceph_cap_flush *ceph_alloc_cap_flush(व्योम)
अणु
	वापस kmem_cache_alloc(ceph_cap_flush_cachep, GFP_KERNEL);
पूर्ण

व्योम ceph_मुक्त_cap_flush(काष्ठा ceph_cap_flush *cf)
अणु
	अगर (cf)
		kmem_cache_मुक्त(ceph_cap_flush_cachep, cf);
पूर्ण

अटल u64 __get_oldest_flush_tid(काष्ठा ceph_mds_client *mdsc)
अणु
	अगर (!list_empty(&mdsc->cap_flush_list)) अणु
		काष्ठा ceph_cap_flush *cf =
			list_first_entry(&mdsc->cap_flush_list,
					 काष्ठा ceph_cap_flush, g_list);
		वापस cf->tid;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Remove cap_flush from the mdsc's or inode's flushing cap list.
 * Return true अगर caller needs to wake up flush रुकोers.
 */
अटल bool __detach_cap_flush_from_mdsc(काष्ठा ceph_mds_client *mdsc,
					 काष्ठा ceph_cap_flush *cf)
अणु
	काष्ठा ceph_cap_flush *prev;
	bool wake = cf->wake;

	अगर (wake && cf->g_list.prev != &mdsc->cap_flush_list) अणु
		prev = list_prev_entry(cf, g_list);
		prev->wake = true;
		wake = false;
	पूर्ण
	list_del(&cf->g_list);
	वापस wake;
पूर्ण

अटल bool __detach_cap_flush_from_ci(काष्ठा ceph_inode_info *ci,
				       काष्ठा ceph_cap_flush *cf)
अणु
	काष्ठा ceph_cap_flush *prev;
	bool wake = cf->wake;

	अगर (wake && cf->i_list.prev != &ci->i_cap_flush_list) अणु
		prev = list_prev_entry(cf, i_list);
		prev->wake = true;
		wake = false;
	पूर्ण
	list_del(&cf->i_list);
	वापस wake;
पूर्ण

/*
 * Add dirty inode to the flushing list.  Asचिन्हित a seq number so we
 * can रुको क्रम caps to flush without starving.
 *
 * Called under i_ceph_lock. Returns the flush tid.
 */
अटल u64 __mark_caps_flushing(काष्ठा inode *inode,
				काष्ठा ceph_mds_session *session, bool wake,
				u64 *oldest_flush_tid)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_client(inode->i_sb)->mdsc;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_cap_flush *cf = शून्य;
	पूर्णांक flushing;

	lockdep_निश्चित_held(&ci->i_ceph_lock);
	BUG_ON(ci->i_dirty_caps == 0);
	BUG_ON(list_empty(&ci->i_dirty_item));
	BUG_ON(!ci->i_pपुनः_स्मृति_cap_flush);

	flushing = ci->i_dirty_caps;
	करोut("__mark_caps_flushing flushing %s, flushing_caps %s -> %s\n",
	     ceph_cap_string(flushing),
	     ceph_cap_string(ci->i_flushing_caps),
	     ceph_cap_string(ci->i_flushing_caps | flushing));
	ci->i_flushing_caps |= flushing;
	ci->i_dirty_caps = 0;
	करोut(" inode %p now !dirty\n", inode);

	swap(cf, ci->i_pपुनः_स्मृति_cap_flush);
	cf->caps = flushing;
	cf->wake = wake;

	spin_lock(&mdsc->cap_dirty_lock);
	list_del_init(&ci->i_dirty_item);

	cf->tid = ++mdsc->last_cap_flush_tid;
	list_add_tail(&cf->g_list, &mdsc->cap_flush_list);
	*oldest_flush_tid = __get_oldest_flush_tid(mdsc);

	अगर (list_empty(&ci->i_flushing_item)) अणु
		list_add_tail(&ci->i_flushing_item, &session->s_cap_flushing);
		mdsc->num_cap_flushing++;
	पूर्ण
	spin_unlock(&mdsc->cap_dirty_lock);

	list_add_tail(&cf->i_list, &ci->i_cap_flush_list);

	वापस cf->tid;
पूर्ण

/*
 * try to invalidate mapping pages without blocking.
 */
अटल पूर्णांक try_nonblocking_invalidate(काष्ठा inode *inode)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	u32 invalidating_gen = ci->i_rdcache_gen;

	spin_unlock(&ci->i_ceph_lock);
	ceph_fscache_invalidate(inode);
	invalidate_mapping_pages(&inode->i_data, 0, -1);
	spin_lock(&ci->i_ceph_lock);

	अगर (inode->i_data.nrpages == 0 &&
	    invalidating_gen == ci->i_rdcache_gen) अणु
		/* success. */
		करोut("try_nonblocking_invalidate %p success\n", inode);
		/* save any racing async invalidate some trouble */
		ci->i_rdcache_revoking = ci->i_rdcache_gen - 1;
		वापस 0;
	पूर्ण
	करोut("try_nonblocking_invalidate %p failed\n", inode);
	वापस -1;
पूर्ण

bool __ceph_should_report_size(काष्ठा ceph_inode_info *ci)
अणु
	loff_t size = i_size_पढ़ो(&ci->vfs_inode);
	/* mds will adjust max size according to the reported size */
	अगर (ci->i_flushing_caps & CEPH_CAP_खाता_WR)
		वापस false;
	अगर (size >= ci->i_max_size)
		वापस true;
	/* half of previous max_size increment has been used */
	अगर (ci->i_max_size > ci->i_reported_size &&
	    (size << 1) >= ci->i_max_size + ci->i_reported_size)
		वापस true;
	वापस false;
पूर्ण

/*
 * Swiss army knअगरe function to examine currently used and wanted
 * versus held caps.  Release, flush, ack revoked caps to mds as
 * appropriate.
 *
 *  CHECK_CAPS_AUTHONLY - we should only check the auth cap
 *  CHECK_CAPS_FLUSH - we should flush any dirty caps immediately, without
 *    further delay.
 */
व्योम ceph_check_caps(काष्ठा ceph_inode_info *ci, पूर्णांक flags,
		     काष्ठा ceph_mds_session *session)
अणु
	काष्ठा inode *inode = &ci->vfs_inode;
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(inode->i_sb);
	काष्ठा ceph_cap *cap;
	u64 flush_tid, oldest_flush_tid;
	पूर्णांक file_wanted, used, cap_used;
	पूर्णांक took_snap_rwsem = 0;             /* true अगर mdsc->snap_rwsem held */
	पूर्णांक issued, implemented, want, retain, revoking, flushing = 0;
	पूर्णांक mds = -1;   /* keep track of how far we've gone through i_caps list
			   to aव्योम an infinite loop on retry */
	काष्ठा rb_node *p;
	bool queue_invalidate = false;
	bool tried_invalidate = false;

	spin_lock(&ci->i_ceph_lock);
	अगर (ci->i_ceph_flags & CEPH_I_FLUSH)
		flags |= CHECK_CAPS_FLUSH;

	जाओ retry_locked;
retry:
	spin_lock(&ci->i_ceph_lock);
retry_locked:
	/* Caps wanted by virtue of active खोलो files. */
	file_wanted = __ceph_caps_file_wanted(ci);

	/* Caps which have active references against them */
	used = __ceph_caps_used(ci);

	/*
	 * "issued" represents the current caps that the MDS wants us to have.
	 * "implemented" is the set that we have been granted, and includes the
	 * ones that have not yet been वापसed to the MDS (the "revoking" set,
	 * usually because they have outstanding references).
	 */
	issued = __ceph_caps_issued(ci, &implemented);
	revoking = implemented & ~issued;

	want = file_wanted;

	/* The ones we currently want to retain (may be adjusted below) */
	retain = file_wanted | used | CEPH_CAP_PIN;
	अगर (!mdsc->stopping && inode->i_nlink > 0) अणु
		अगर (file_wanted) अणु
			retain |= CEPH_CAP_ANY;       /* be greedy */
		पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode) &&
			   (issued & CEPH_CAP_खाता_SHARED) &&
			   __ceph_dir_is_complete(ci)) अणु
			/*
			 * If a directory is complete, we want to keep
			 * the exclusive cap. So that MDS करोes not end up
			 * revoking the shared cap on every create/unlink
			 * operation.
			 */
			अगर (IS_RDONLY(inode)) अणु
				want = CEPH_CAP_ANY_SHARED;
			पूर्ण अन्यथा अणु
				want |= CEPH_CAP_ANY_SHARED | CEPH_CAP_खाता_EXCL;
			पूर्ण
			retain |= want;
		पूर्ण अन्यथा अणु

			retain |= CEPH_CAP_ANY_SHARED;
			/*
			 * keep RD only अगर we didn't have the file खोलो RW,
			 * because then the mds would revoke it anyway to
			 * journal max_size=0.
			 */
			अगर (ci->i_max_size == 0)
				retain |= CEPH_CAP_ANY_RD;
		पूर्ण
	पूर्ण

	करोut("check_caps %p file_want %s used %s dirty %s flushing %s"
	     " issued %s revoking %s retain %s %s%s\n", inode,
	     ceph_cap_string(file_wanted),
	     ceph_cap_string(used), ceph_cap_string(ci->i_dirty_caps),
	     ceph_cap_string(ci->i_flushing_caps),
	     ceph_cap_string(issued), ceph_cap_string(revoking),
	     ceph_cap_string(retain),
	     (flags & CHECK_CAPS_AUTHONLY) ? " AUTHONLY" : "",
	     (flags & CHECK_CAPS_FLUSH) ? " FLUSH" : "");

	/*
	 * If we no दीर्घer need to hold onto old our caps, and we may
	 * have cached pages, but करोn't want them, then try to invalidate.
	 * If we fail, it's because pages are locked.... try again later.
	 */
	अगर ((!(flags & CHECK_CAPS_NOINVAL) || mdsc->stopping) &&
	    S_ISREG(inode->i_mode) &&
	    !(ci->i_wb_ref || ci->i_wrbuffer_ref) &&   /* no dirty pages... */
	    inode->i_data.nrpages &&		/* have cached pages */
	    (revoking & (CEPH_CAP_खाता_CACHE|
			 CEPH_CAP_खाता_LAZYIO)) && /*  or revoking cache */
	    !tried_invalidate) अणु
		करोut("check_caps trying to invalidate on %p\n", inode);
		अगर (try_nonblocking_invalidate(inode) < 0) अणु
			करोut("check_caps queuing invalidate\n");
			queue_invalidate = true;
			ci->i_rdcache_revoking = ci->i_rdcache_gen;
		पूर्ण
		tried_invalidate = true;
		जाओ retry_locked;
	पूर्ण

	क्रम (p = rb_first(&ci->i_caps); p; p = rb_next(p)) अणु
		पूर्णांक mflags = 0;
		काष्ठा cap_msg_args arg;

		cap = rb_entry(p, काष्ठा ceph_cap, ci_node);

		/* aव्योम looping क्रमever */
		अगर (mds >= cap->mds ||
		    ((flags & CHECK_CAPS_AUTHONLY) && cap != ci->i_auth_cap))
			जारी;

		/* NOTE: no side-effects allowed, until we take s_mutex */

		/*
		 * If we have an auth cap, we करोn't need to consider any
		 * overlapping caps as used.
		 */
		cap_used = used;
		अगर (ci->i_auth_cap && cap != ci->i_auth_cap)
			cap_used &= ~ci->i_auth_cap->issued;

		revoking = cap->implemented & ~cap->issued;
		करोut(" mds%d cap %p used %s issued %s implemented %s revoking %s\n",
		     cap->mds, cap, ceph_cap_string(cap_used),
		     ceph_cap_string(cap->issued),
		     ceph_cap_string(cap->implemented),
		     ceph_cap_string(revoking));

		अगर (cap == ci->i_auth_cap &&
		    (cap->issued & CEPH_CAP_खाता_WR)) अणु
			/* request larger max_size from MDS? */
			अगर (ci->i_wanted_max_size > ci->i_max_size &&
			    ci->i_wanted_max_size > ci->i_requested_max_size) अणु
				करोut("requesting new max_size\n");
				जाओ ack;
			पूर्ण

			/* approaching file_max? */
			अगर (__ceph_should_report_size(ci)) अणु
				करोut("i_size approaching max_size\n");
				जाओ ack;
			पूर्ण
		पूर्ण
		/* flush anything dirty? */
		अगर (cap == ci->i_auth_cap) अणु
			अगर ((flags & CHECK_CAPS_FLUSH) && ci->i_dirty_caps) अणु
				करोut("flushing dirty caps\n");
				जाओ ack;
			पूर्ण
			अगर (ci->i_ceph_flags & CEPH_I_FLUSH_SNAPS) अणु
				करोut("flushing snap caps\n");
				जाओ ack;
			पूर्ण
		पूर्ण

		/* completed revocation? going करोwn and there are no caps? */
		अगर (revoking && (revoking & cap_used) == 0) अणु
			करोut("completed revocation of %s\n",
			     ceph_cap_string(cap->implemented & ~cap->issued));
			जाओ ack;
		पूर्ण

		/* want more caps from mds? */
		अगर (want & ~cap->mds_wanted) अणु
			अगर (want & ~(cap->mds_wanted | cap->issued))
				जाओ ack;
			अगर (!__cap_is_valid(cap))
				जाओ ack;
		पूर्ण

		/* things we might delay */
		अगर ((cap->issued & ~retain) == 0)
			जारी;     /* nope, all good */

ack:
		अगर (session && session != cap->session) अणु
			करोut("oops, wrong session %p mutex\n", session);
			mutex_unlock(&session->s_mutex);
			session = शून्य;
		पूर्ण
		अगर (!session) अणु
			session = cap->session;
			अगर (mutex_trylock(&session->s_mutex) == 0) अणु
				करोut("inverting session/ino locks on %p\n",
				     session);
				session = ceph_get_mds_session(session);
				spin_unlock(&ci->i_ceph_lock);
				अगर (took_snap_rwsem) अणु
					up_पढ़ो(&mdsc->snap_rwsem);
					took_snap_rwsem = 0;
				पूर्ण
				अगर (session) अणु
					mutex_lock(&session->s_mutex);
					ceph_put_mds_session(session);
				पूर्ण अन्यथा अणु
					/*
					 * Because we take the reference जबतक
					 * holding the i_ceph_lock, it should
					 * never be शून्य. Throw a warning अगर it
					 * ever is.
					 */
					WARN_ON_ONCE(true);
				पूर्ण
				जाओ retry;
			पूर्ण
		पूर्ण

		/* kick flushing and flush snaps beक्रमe sending normal
		 * cap message */
		अगर (cap == ci->i_auth_cap &&
		    (ci->i_ceph_flags &
		     (CEPH_I_KICK_FLUSH | CEPH_I_FLUSH_SNAPS))) अणु
			अगर (ci->i_ceph_flags & CEPH_I_KICK_FLUSH)
				__kick_flushing_caps(mdsc, session, ci, 0);
			अगर (ci->i_ceph_flags & CEPH_I_FLUSH_SNAPS)
				__ceph_flush_snaps(ci, session);

			जाओ retry_locked;
		पूर्ण

		/* take snap_rwsem after session mutex */
		अगर (!took_snap_rwsem) अणु
			अगर (करोwn_पढ़ो_trylock(&mdsc->snap_rwsem) == 0) अणु
				करोut("inverting snap/in locks on %p\n",
				     inode);
				spin_unlock(&ci->i_ceph_lock);
				करोwn_पढ़ो(&mdsc->snap_rwsem);
				took_snap_rwsem = 1;
				जाओ retry;
			पूर्ण
			took_snap_rwsem = 1;
		पूर्ण

		अगर (cap == ci->i_auth_cap && ci->i_dirty_caps) अणु
			flushing = ci->i_dirty_caps;
			flush_tid = __mark_caps_flushing(inode, session, false,
							 &oldest_flush_tid);
			अगर (flags & CHECK_CAPS_FLUSH &&
			    list_empty(&session->s_cap_dirty))
				mflags |= CEPH_CLIENT_CAPS_SYNC;
		पूर्ण अन्यथा अणु
			flushing = 0;
			flush_tid = 0;
			spin_lock(&mdsc->cap_dirty_lock);
			oldest_flush_tid = __get_oldest_flush_tid(mdsc);
			spin_unlock(&mdsc->cap_dirty_lock);
		पूर्ण

		mds = cap->mds;  /* remember mds, so we करोn't repeat */

		__prep_cap(&arg, cap, CEPH_CAP_OP_UPDATE, mflags, cap_used,
			   want, retain, flushing, flush_tid, oldest_flush_tid);
		spin_unlock(&ci->i_ceph_lock);

		__send_cap(&arg, ci);

		जाओ retry; /* retake i_ceph_lock and restart our cap scan. */
	पूर्ण

	/* periodically re-calculate caps wanted by खोलो files */
	अगर (__ceph_is_any_real_caps(ci) &&
	    list_empty(&ci->i_cap_delay_list) &&
	    (file_wanted & ~CEPH_CAP_PIN) &&
	    !(used & (CEPH_CAP_खाता_RD | CEPH_CAP_ANY_खाता_WR))) अणु
		__cap_delay_requeue(mdsc, ci);
	पूर्ण

	spin_unlock(&ci->i_ceph_lock);

	अगर (queue_invalidate)
		ceph_queue_invalidate(inode);

	अगर (session)
		mutex_unlock(&session->s_mutex);
	अगर (took_snap_rwsem)
		up_पढ़ो(&mdsc->snap_rwsem);
पूर्ण

/*
 * Try to flush dirty caps back to the auth mds.
 */
अटल पूर्णांक try_flush_caps(काष्ठा inode *inode, u64 *ptid)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_client(inode->i_sb)->mdsc;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_mds_session *session = शून्य;
	पूर्णांक flushing = 0;
	u64 flush_tid = 0, oldest_flush_tid = 0;

retry:
	spin_lock(&ci->i_ceph_lock);
retry_locked:
	अगर (ci->i_dirty_caps && ci->i_auth_cap) अणु
		काष्ठा ceph_cap *cap = ci->i_auth_cap;
		काष्ठा cap_msg_args arg;

		अगर (session != cap->session) अणु
			spin_unlock(&ci->i_ceph_lock);
			अगर (session)
				mutex_unlock(&session->s_mutex);
			session = cap->session;
			mutex_lock(&session->s_mutex);
			जाओ retry;
		पूर्ण
		अगर (cap->session->s_state < CEPH_MDS_SESSION_OPEN) अणु
			spin_unlock(&ci->i_ceph_lock);
			जाओ out;
		पूर्ण

		अगर (ci->i_ceph_flags &
		    (CEPH_I_KICK_FLUSH | CEPH_I_FLUSH_SNAPS)) अणु
			अगर (ci->i_ceph_flags & CEPH_I_KICK_FLUSH)
				__kick_flushing_caps(mdsc, session, ci, 0);
			अगर (ci->i_ceph_flags & CEPH_I_FLUSH_SNAPS)
				__ceph_flush_snaps(ci, session);
			जाओ retry_locked;
		पूर्ण

		flushing = ci->i_dirty_caps;
		flush_tid = __mark_caps_flushing(inode, session, true,
						 &oldest_flush_tid);

		__prep_cap(&arg, cap, CEPH_CAP_OP_FLUSH, CEPH_CLIENT_CAPS_SYNC,
			   __ceph_caps_used(ci), __ceph_caps_wanted(ci),
			   (cap->issued | cap->implemented),
			   flushing, flush_tid, oldest_flush_tid);
		spin_unlock(&ci->i_ceph_lock);

		__send_cap(&arg, ci);
	पूर्ण अन्यथा अणु
		अगर (!list_empty(&ci->i_cap_flush_list)) अणु
			काष्ठा ceph_cap_flush *cf =
				list_last_entry(&ci->i_cap_flush_list,
						काष्ठा ceph_cap_flush, i_list);
			cf->wake = true;
			flush_tid = cf->tid;
		पूर्ण
		flushing = ci->i_flushing_caps;
		spin_unlock(&ci->i_ceph_lock);
	पूर्ण
out:
	अगर (session)
		mutex_unlock(&session->s_mutex);

	*ptid = flush_tid;
	वापस flushing;
पूर्ण

/*
 * Return true अगर we've flushed caps through the given flush_tid.
 */
अटल पूर्णांक caps_are_flushed(काष्ठा inode *inode, u64 flush_tid)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक ret = 1;

	spin_lock(&ci->i_ceph_lock);
	अगर (!list_empty(&ci->i_cap_flush_list)) अणु
		काष्ठा ceph_cap_flush * cf =
			list_first_entry(&ci->i_cap_flush_list,
					 काष्ठा ceph_cap_flush, i_list);
		अगर (cf->tid <= flush_tid)
			ret = 0;
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);
	वापस ret;
पूर्ण

/*
 * रुको क्रम any unsafe requests to complete.
 */
अटल पूर्णांक unsafe_request_रुको(काष्ठा inode *inode)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_mds_request *req1 = शून्य, *req2 = शून्य;
	पूर्णांक ret, err = 0;

	spin_lock(&ci->i_unsafe_lock);
	अगर (S_ISसूची(inode->i_mode) && !list_empty(&ci->i_unsafe_dirops)) अणु
		req1 = list_last_entry(&ci->i_unsafe_dirops,
					काष्ठा ceph_mds_request,
					r_unsafe_dir_item);
		ceph_mdsc_get_request(req1);
	पूर्ण
	अगर (!list_empty(&ci->i_unsafe_iops)) अणु
		req2 = list_last_entry(&ci->i_unsafe_iops,
					काष्ठा ceph_mds_request,
					r_unsafe_target_item);
		ceph_mdsc_get_request(req2);
	पूर्ण
	spin_unlock(&ci->i_unsafe_lock);

	करोut("unsafe_request_wait %p wait on tid %llu %llu\n",
	     inode, req1 ? req1->r_tid : 0ULL, req2 ? req2->r_tid : 0ULL);
	अगर (req1) अणु
		ret = !रुको_क्रम_completion_समयout(&req1->r_safe_completion,
					ceph_समयout_jअगरfies(req1->r_समयout));
		अगर (ret)
			err = -EIO;
		ceph_mdsc_put_request(req1);
	पूर्ण
	अगर (req2) अणु
		ret = !रुको_क्रम_completion_समयout(&req2->r_safe_completion,
					ceph_समयout_jअगरfies(req2->r_समयout));
		अगर (ret)
			err = -EIO;
		ceph_mdsc_put_request(req2);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक ceph_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा ceph_file_info *fi = file->निजी_data;
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	u64 flush_tid;
	पूर्णांक ret, err;
	पूर्णांक dirty;

	करोut("fsync %p%s\n", inode, datasync ? " datasync" : "");

	ret = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (datasync)
		जाओ out;

	ret = ceph_रुको_on_async_create(inode);
	अगर (ret)
		जाओ out;

	dirty = try_flush_caps(inode, &flush_tid);
	करोut("fsync dirty caps are %s\n", ceph_cap_string(dirty));

	err = unsafe_request_रुको(inode);

	/*
	 * only रुको on non-file metadata ग_लिखोback (the mds
	 * can recover size and mसमय, so we करोn't need to
	 * रुको क्रम that)
	 */
	अगर (!err && (dirty & ~CEPH_CAP_ANY_खाता_WR)) अणु
		err = रुको_event_पूर्णांकerruptible(ci->i_cap_wq,
					caps_are_flushed(inode, flush_tid));
	पूर्ण

	अगर (err < 0)
		ret = err;

	अगर (errseq_check(&ci->i_meta_err, READ_ONCE(fi->meta_err))) अणु
		spin_lock(&file->f_lock);
		err = errseq_check_and_advance(&ci->i_meta_err,
					       &fi->meta_err);
		spin_unlock(&file->f_lock);
		अगर (err < 0)
			ret = err;
	पूर्ण
out:
	करोut("fsync %p%s result=%d\n", inode, datasync ? " datasync" : "", ret);
	वापस ret;
पूर्ण

/*
 * Flush any dirty caps back to the mds.  If we aren't asked to रुको,
 * queue inode क्रम flush but करोn't करो so immediately, because we can
 * get by with fewer MDS messages अगर we रुको क्रम data ग_लिखोback to
 * complete first.
 */
पूर्णांक ceph_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	u64 flush_tid;
	पूर्णांक err = 0;
	पूर्णांक dirty;
	पूर्णांक रुको = (wbc->sync_mode == WB_SYNC_ALL && !wbc->क्रम_sync);

	करोut("write_inode %p wait=%d\n", inode, रुको);
	अगर (रुको) अणु
		dirty = try_flush_caps(inode, &flush_tid);
		अगर (dirty)
			err = रुको_event_पूर्णांकerruptible(ci->i_cap_wq,
				       caps_are_flushed(inode, flush_tid));
	पूर्ण अन्यथा अणु
		काष्ठा ceph_mds_client *mdsc =
			ceph_sb_to_client(inode->i_sb)->mdsc;

		spin_lock(&ci->i_ceph_lock);
		अगर (__ceph_caps_dirty(ci))
			__cap_delay_requeue_front(mdsc, ci);
		spin_unlock(&ci->i_ceph_lock);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम __kick_flushing_caps(काष्ठा ceph_mds_client *mdsc,
				 काष्ठा ceph_mds_session *session,
				 काष्ठा ceph_inode_info *ci,
				 u64 oldest_flush_tid)
	__releases(ci->i_ceph_lock)
	__acquires(ci->i_ceph_lock)
अणु
	काष्ठा inode *inode = &ci->vfs_inode;
	काष्ठा ceph_cap *cap;
	काष्ठा ceph_cap_flush *cf;
	पूर्णांक ret;
	u64 first_tid = 0;
	u64 last_snap_flush = 0;

	ci->i_ceph_flags &= ~CEPH_I_KICK_FLUSH;

	list_क्रम_each_entry_reverse(cf, &ci->i_cap_flush_list, i_list) अणु
		अगर (!cf->caps) अणु
			last_snap_flush = cf->tid;
			अवरोध;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(cf, &ci->i_cap_flush_list, i_list) अणु
		अगर (cf->tid < first_tid)
			जारी;

		cap = ci->i_auth_cap;
		अगर (!(cap && cap->session == session)) अणु
			pr_err("%p auth cap %p not mds%d ???\n",
			       inode, cap, session->s_mds);
			अवरोध;
		पूर्ण

		first_tid = cf->tid + 1;

		अगर (cf->caps) अणु
			काष्ठा cap_msg_args arg;

			करोut("kick_flushing_caps %p cap %p tid %llu %s\n",
			     inode, cap, cf->tid, ceph_cap_string(cf->caps));
			__prep_cap(&arg, cap, CEPH_CAP_OP_FLUSH,
					 (cf->tid < last_snap_flush ?
					  CEPH_CLIENT_CAPS_PENDING_CAPSNAP : 0),
					  __ceph_caps_used(ci),
					  __ceph_caps_wanted(ci),
					  (cap->issued | cap->implemented),
					  cf->caps, cf->tid, oldest_flush_tid);
			spin_unlock(&ci->i_ceph_lock);
			__send_cap(&arg, ci);
		पूर्ण अन्यथा अणु
			काष्ठा ceph_cap_snap *capsnap =
					container_of(cf, काष्ठा ceph_cap_snap,
						    cap_flush);
			करोut("kick_flushing_caps %p capsnap %p tid %llu %s\n",
			     inode, capsnap, cf->tid,
			     ceph_cap_string(capsnap->dirty));

			refcount_inc(&capsnap->nref);
			spin_unlock(&ci->i_ceph_lock);

			ret = __send_flush_snap(inode, session, capsnap, cap->mseq,
						oldest_flush_tid);
			अगर (ret < 0) अणु
				pr_err("kick_flushing_caps: error sending "
					"cap flushsnap, ino (%llx.%llx) "
					"tid %llu follows %llu\n",
					ceph_vinop(inode), cf->tid,
					capsnap->follows);
			पूर्ण

			ceph_put_cap_snap(capsnap);
		पूर्ण

		spin_lock(&ci->i_ceph_lock);
	पूर्ण
पूर्ण

व्योम ceph_early_kick_flushing_caps(काष्ठा ceph_mds_client *mdsc,
				   काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_inode_info *ci;
	काष्ठा ceph_cap *cap;
	u64 oldest_flush_tid;

	करोut("early_kick_flushing_caps mds%d\n", session->s_mds);

	spin_lock(&mdsc->cap_dirty_lock);
	oldest_flush_tid = __get_oldest_flush_tid(mdsc);
	spin_unlock(&mdsc->cap_dirty_lock);

	list_क्रम_each_entry(ci, &session->s_cap_flushing, i_flushing_item) अणु
		spin_lock(&ci->i_ceph_lock);
		cap = ci->i_auth_cap;
		अगर (!(cap && cap->session == session)) अणु
			pr_err("%p auth cap %p not mds%d ???\n",
				&ci->vfs_inode, cap, session->s_mds);
			spin_unlock(&ci->i_ceph_lock);
			जारी;
		पूर्ण


		/*
		 * अगर flushing caps were revoked, we re-send the cap flush
		 * in client reconnect stage. This guarantees MDS * processes
		 * the cap flush message beक्रमe issuing the flushing caps to
		 * other client.
		 */
		अगर ((cap->issued & ci->i_flushing_caps) !=
		    ci->i_flushing_caps) अणु
			/* encode_caps_cb() also will reset these sequence
			 * numbers. make sure sequence numbers in cap flush
			 * message match later reconnect message */
			cap->seq = 0;
			cap->issue_seq = 0;
			cap->mseq = 0;
			__kick_flushing_caps(mdsc, session, ci,
					     oldest_flush_tid);
		पूर्ण अन्यथा अणु
			ci->i_ceph_flags |= CEPH_I_KICK_FLUSH;
		पूर्ण

		spin_unlock(&ci->i_ceph_lock);
	पूर्ण
पूर्ण

व्योम ceph_kick_flushing_caps(काष्ठा ceph_mds_client *mdsc,
			     काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_inode_info *ci;
	काष्ठा ceph_cap *cap;
	u64 oldest_flush_tid;

	lockdep_निश्चित_held(&session->s_mutex);

	करोut("kick_flushing_caps mds%d\n", session->s_mds);

	spin_lock(&mdsc->cap_dirty_lock);
	oldest_flush_tid = __get_oldest_flush_tid(mdsc);
	spin_unlock(&mdsc->cap_dirty_lock);

	list_क्रम_each_entry(ci, &session->s_cap_flushing, i_flushing_item) अणु
		spin_lock(&ci->i_ceph_lock);
		cap = ci->i_auth_cap;
		अगर (!(cap && cap->session == session)) अणु
			pr_err("%p auth cap %p not mds%d ???\n",
				&ci->vfs_inode, cap, session->s_mds);
			spin_unlock(&ci->i_ceph_lock);
			जारी;
		पूर्ण
		अगर (ci->i_ceph_flags & CEPH_I_KICK_FLUSH) अणु
			__kick_flushing_caps(mdsc, session, ci,
					     oldest_flush_tid);
		पूर्ण
		spin_unlock(&ci->i_ceph_lock);
	पूर्ण
पूर्ण

व्योम ceph_kick_flushing_inode_caps(काष्ठा ceph_mds_session *session,
				   काष्ठा ceph_inode_info *ci)
अणु
	काष्ठा ceph_mds_client *mdsc = session->s_mdsc;
	काष्ठा ceph_cap *cap = ci->i_auth_cap;

	lockdep_निश्चित_held(&ci->i_ceph_lock);

	करोut("%s %p flushing %s\n", __func__, &ci->vfs_inode,
	     ceph_cap_string(ci->i_flushing_caps));

	अगर (!list_empty(&ci->i_cap_flush_list)) अणु
		u64 oldest_flush_tid;
		spin_lock(&mdsc->cap_dirty_lock);
		list_move_tail(&ci->i_flushing_item,
			       &cap->session->s_cap_flushing);
		oldest_flush_tid = __get_oldest_flush_tid(mdsc);
		spin_unlock(&mdsc->cap_dirty_lock);

		__kick_flushing_caps(mdsc, session, ci, oldest_flush_tid);
	पूर्ण
पूर्ण


/*
 * Take references to capabilities we hold, so that we करोn't release
 * them to the MDS prematurely.
 */
व्योम ceph_take_cap_refs(काष्ठा ceph_inode_info *ci, पूर्णांक got,
			    bool snap_rwsem_locked)
अणु
	lockdep_निश्चित_held(&ci->i_ceph_lock);

	अगर (got & CEPH_CAP_PIN)
		ci->i_pin_ref++;
	अगर (got & CEPH_CAP_खाता_RD)
		ci->i_rd_ref++;
	अगर (got & CEPH_CAP_खाता_CACHE)
		ci->i_rdcache_ref++;
	अगर (got & CEPH_CAP_खाता_EXCL)
		ci->i_fx_ref++;
	अगर (got & CEPH_CAP_खाता_WR) अणु
		अगर (ci->i_wr_ref == 0 && !ci->i_head_snapc) अणु
			BUG_ON(!snap_rwsem_locked);
			ci->i_head_snapc = ceph_get_snap_context(
					ci->i_snap_realm->cached_context);
		पूर्ण
		ci->i_wr_ref++;
	पूर्ण
	अगर (got & CEPH_CAP_खाता_BUFFER) अणु
		अगर (ci->i_wb_ref == 0)
			ihold(&ci->vfs_inode);
		ci->i_wb_ref++;
		करोut("%s %p wb %d -> %d (?)\n", __func__,
		     &ci->vfs_inode, ci->i_wb_ref-1, ci->i_wb_ref);
	पूर्ण
पूर्ण

/*
 * Try to grab cap references.  Specअगरy those refs we @want, and the
 * minimal set we @need.  Also include the larger offset we are writing
 * to (when applicable), and check against max_size here as well.
 * Note that caller is responsible क्रम ensuring max_size increases are
 * requested from the MDS.
 *
 * Returns 0 अगर caps were not able to be acquired (yet), 1 अगर succeed,
 * or a negative error code. There are 3 speical error codes:
 *  -EAGAIN: need to sleep but non-blocking is specअगरied
 *  -EFBIG:  ask caller to call check_max_size() and try again.
 *  -ESTALE: ask caller to call ceph_renew_caps() and try again.
 */
क्रमागत अणु
	/* first 8 bits are reserved क्रम CEPH_खाता_MODE_FOO */
	NON_BLOCKING	= (1 << 8),
	CHECK_खाताLOCK	= (1 << 9),
पूर्ण;

अटल पूर्णांक try_get_cap_refs(काष्ठा inode *inode, पूर्णांक need, पूर्णांक want,
			    loff_t enकरोff, पूर्णांक flags, पूर्णांक *got)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_mds_client *mdsc = ceph_inode_to_client(inode)->mdsc;
	पूर्णांक ret = 0;
	पूर्णांक have, implemented;
	bool snap_rwsem_locked = false;

	करोut("get_cap_refs %p need %s want %s\n", inode,
	     ceph_cap_string(need), ceph_cap_string(want));

again:
	spin_lock(&ci->i_ceph_lock);

	अगर ((flags & CHECK_खाताLOCK) &&
	    (ci->i_ceph_flags & CEPH_I_ERROR_खाताLOCK)) अणु
		करोut("try_get_cap_refs %p error filelock\n", inode);
		ret = -EIO;
		जाओ out_unlock;
	पूर्ण

	/* finish pending truncate */
	जबतक (ci->i_truncate_pending) अणु
		spin_unlock(&ci->i_ceph_lock);
		अगर (snap_rwsem_locked) अणु
			up_पढ़ो(&mdsc->snap_rwsem);
			snap_rwsem_locked = false;
		पूर्ण
		__ceph_करो_pending_vmtruncate(inode);
		spin_lock(&ci->i_ceph_lock);
	पूर्ण

	have = __ceph_caps_issued(ci, &implemented);

	अगर (have & need & CEPH_CAP_खाता_WR) अणु
		अगर (enकरोff >= 0 && enकरोff > (loff_t)ci->i_max_size) अणु
			करोut("get_cap_refs %p endoff %llu > maxsize %llu\n",
			     inode, enकरोff, ci->i_max_size);
			अगर (enकरोff > ci->i_requested_max_size)
				ret = ci->i_auth_cap ? -EFBIG : -ESTALE;
			जाओ out_unlock;
		पूर्ण
		/*
		 * If a sync ग_लिखो is in progress, we must रुको, so that we
		 * can get a final snapshot value क्रम size+mसमय.
		 */
		अगर (__ceph_have_pending_cap_snap(ci)) अणु
			करोut("get_cap_refs %p cap_snap_pending\n", inode);
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	अगर ((have & need) == need) अणु
		/*
		 * Look at (implemented & ~have & not) so that we keep रुकोing
		 * on transition from wanted -> needed caps.  This is needed
		 * क्रम WRBUFFER|WR -> WR to aव्योम a new WR sync ग_लिखो from
		 * going beक्रमe a prior buffered ग_लिखोback happens.
		 */
		पूर्णांक not = want & ~(have & need);
		पूर्णांक revoking = implemented & ~have;
		करोut("get_cap_refs %p have %s but not %s (revoking %s)\n",
		     inode, ceph_cap_string(have), ceph_cap_string(not),
		     ceph_cap_string(revoking));
		अगर ((revoking & not) == 0) अणु
			अगर (!snap_rwsem_locked &&
			    !ci->i_head_snapc &&
			    (need & CEPH_CAP_खाता_WR)) अणु
				अगर (!करोwn_पढ़ो_trylock(&mdsc->snap_rwsem)) अणु
					/*
					 * we can not call करोwn_पढ़ो() when
					 * task isn't in TASK_RUNNING state
					 */
					अगर (flags & NON_BLOCKING) अणु
						ret = -EAGAIN;
						जाओ out_unlock;
					पूर्ण

					spin_unlock(&ci->i_ceph_lock);
					करोwn_पढ़ो(&mdsc->snap_rwsem);
					snap_rwsem_locked = true;
					जाओ again;
				पूर्ण
				snap_rwsem_locked = true;
			पूर्ण
			अगर ((have & want) == want)
				*got = need | want;
			अन्यथा
				*got = need;
			ceph_take_cap_refs(ci, *got, true);
			ret = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक session_पढ़ोonly = false;
		पूर्णांक mds_wanted;
		अगर (ci->i_auth_cap &&
		    (need & (CEPH_CAP_खाता_WR | CEPH_CAP_खाता_EXCL))) अणु
			काष्ठा ceph_mds_session *s = ci->i_auth_cap->session;
			spin_lock(&s->s_cap_lock);
			session_पढ़ोonly = s->s_पढ़ोonly;
			spin_unlock(&s->s_cap_lock);
		पूर्ण
		अगर (session_पढ़ोonly) अणु
			करोut("get_cap_refs %p need %s but mds%d readonly\n",
			     inode, ceph_cap_string(need), ci->i_auth_cap->mds);
			ret = -EROFS;
			जाओ out_unlock;
		पूर्ण

		अगर (READ_ONCE(mdsc->fsc->mount_state) >= CEPH_MOUNT_SHUTDOWN) अणु
			करोut("get_cap_refs %p forced umount\n", inode);
			ret = -EIO;
			जाओ out_unlock;
		पूर्ण
		mds_wanted = __ceph_caps_mds_wanted(ci, false);
		अगर (need & ~mds_wanted) अणु
			करोut("get_cap_refs %p need %s > mds_wanted %s\n",
			     inode, ceph_cap_string(need),
			     ceph_cap_string(mds_wanted));
			ret = -ESTALE;
			जाओ out_unlock;
		पूर्ण

		करोut("get_cap_refs %p have %s need %s\n", inode,
		     ceph_cap_string(have), ceph_cap_string(need));
	पूर्ण
out_unlock:

	__ceph_touch_भ_शेषe(ci, mdsc, flags);

	spin_unlock(&ci->i_ceph_lock);
	अगर (snap_rwsem_locked)
		up_पढ़ो(&mdsc->snap_rwsem);

	अगर (!ret)
		ceph_update_cap_mis(&mdsc->metric);
	अन्यथा अगर (ret == 1)
		ceph_update_cap_hit(&mdsc->metric);

	करोut("get_cap_refs %p ret %d got %s\n", inode,
	     ret, ceph_cap_string(*got));
	वापस ret;
पूर्ण

/*
 * Check the offset we are writing up to against our current
 * max_size.  If necessary, tell the MDS we want to ग_लिखो to
 * a larger offset.
 */
अटल व्योम check_max_size(काष्ठा inode *inode, loff_t enकरोff)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक check = 0;

	/* करो we need to explicitly request a larger max_size? */
	spin_lock(&ci->i_ceph_lock);
	अगर (enकरोff >= ci->i_max_size && enकरोff > ci->i_wanted_max_size) अणु
		करोut("write %p at large endoff %llu, req max_size\n",
		     inode, enकरोff);
		ci->i_wanted_max_size = enकरोff;
	पूर्ण
	/* duplicate ceph_check_caps()'s logic */
	अगर (ci->i_auth_cap &&
	    (ci->i_auth_cap->issued & CEPH_CAP_खाता_WR) &&
	    ci->i_wanted_max_size > ci->i_max_size &&
	    ci->i_wanted_max_size > ci->i_requested_max_size)
		check = 1;
	spin_unlock(&ci->i_ceph_lock);
	अगर (check)
		ceph_check_caps(ci, CHECK_CAPS_AUTHONLY, शून्य);
पूर्ण

अटल अंतरभूत पूर्णांक get_used_भ_शेषe(पूर्णांक caps)
अणु
	पूर्णांक भ_शेषe = 0;
	अगर (caps & CEPH_CAP_खाता_RD)
		भ_शेषe |= CEPH_खाता_MODE_RD;
	अगर (caps & CEPH_CAP_खाता_WR)
		भ_शेषe |= CEPH_खाता_MODE_WR;
	वापस भ_शेषe;
पूर्ण

पूर्णांक ceph_try_get_caps(काष्ठा inode *inode, पूर्णांक need, पूर्णांक want,
		      bool nonblock, पूर्णांक *got)
अणु
	पूर्णांक ret, flags;

	BUG_ON(need & ~CEPH_CAP_खाता_RD);
	BUG_ON(want & ~(CEPH_CAP_खाता_CACHE | CEPH_CAP_खाता_LAZYIO |
			CEPH_CAP_खाता_SHARED | CEPH_CAP_खाता_EXCL |
			CEPH_CAP_ANY_सूची_OPS));
	अगर (need) अणु
		ret = ceph_pool_perm_check(inode, need);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	flags = get_used_भ_शेषe(need | want);
	अगर (nonblock)
		flags |= NON_BLOCKING;

	ret = try_get_cap_refs(inode, need, want, 0, flags, got);
	/* three special error codes */
	अगर (ret == -EAGAIN || ret == -EFBIG || ret == -ESTALE)
		ret = 0;
	वापस ret;
पूर्ण

/*
 * Wait क्रम caps, and take cap references.  If we can't get a WR cap
 * due to a small max_size, make sure we check_max_size (and possibly
 * ask the mds) so we करोn't get hung up indefinitely.
 */
पूर्णांक ceph_get_caps(काष्ठा file *filp, पूर्णांक need, पूर्णांक want, loff_t enकरोff, पूर्णांक *got)
अणु
	काष्ठा ceph_file_info *fi = filp->निजी_data;
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	पूर्णांक ret, _got, flags;

	ret = ceph_pool_perm_check(inode, need);
	अगर (ret < 0)
		वापस ret;

	अगर ((fi->भ_शेषe & CEPH_खाता_MODE_WR) &&
	    fi->filp_gen != READ_ONCE(fsc->filp_gen))
		वापस -EBADF;

	flags = get_used_भ_शेषe(need | want);

	जबतक (true) अणु
		flags &= CEPH_खाता_MODE_MASK;
		अगर (atomic_पढ़ो(&fi->num_locks))
			flags |= CHECK_खाताLOCK;
		_got = 0;
		ret = try_get_cap_refs(inode, need, want, enकरोff,
				       flags, &_got);
		WARN_ON_ONCE(ret == -EAGAIN);
		अगर (!ret) अणु
			काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
			काष्ठा cap_रुको cw;
			DEFINE_WAIT_FUNC(रुको, woken_wake_function);

			cw.ino = ceph_ino(inode);
			cw.tgid = current->tgid;
			cw.need = need;
			cw.want = want;

			spin_lock(&mdsc->caps_list_lock);
			list_add(&cw.list, &mdsc->cap_रुको_list);
			spin_unlock(&mdsc->caps_list_lock);

			/* make sure used भ_शेषe not समयout */
			ceph_get_भ_शेषe(ci, flags, FMODE_WAIT_BIAS);
			add_रुको_queue(&ci->i_cap_wq, &रुको);

			flags |= NON_BLOCKING;
			जबतक (!(ret = try_get_cap_refs(inode, need, want,
							enकरोff, flags, &_got))) अणु
				अगर (संकेत_pending(current)) अणु
					ret = -ERESTARTSYS;
					अवरोध;
				पूर्ण
				रुको_woken(&रुको, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
			पूर्ण

			हटाओ_रुको_queue(&ci->i_cap_wq, &रुको);
			ceph_put_भ_शेषe(ci, flags, FMODE_WAIT_BIAS);

			spin_lock(&mdsc->caps_list_lock);
			list_del(&cw.list);
			spin_unlock(&mdsc->caps_list_lock);

			अगर (ret == -EAGAIN)
				जारी;
		पूर्ण

		अगर ((fi->भ_शेषe & CEPH_खाता_MODE_WR) &&
		    fi->filp_gen != READ_ONCE(fsc->filp_gen)) अणु
			अगर (ret >= 0 && _got)
				ceph_put_cap_refs(ci, _got);
			वापस -EBADF;
		पूर्ण

		अगर (ret < 0) अणु
			अगर (ret == -EFBIG || ret == -ESTALE) अणु
				पूर्णांक ret2 = ceph_रुको_on_async_create(inode);
				अगर (ret2 < 0)
					वापस ret2;
			पूर्ण
			अगर (ret == -EFBIG) अणु
				check_max_size(inode, enकरोff);
				जारी;
			पूर्ण
			अगर (ret == -ESTALE) अणु
				/* session was समाप्तed, try renew caps */
				ret = ceph_renew_caps(inode, flags);
				अगर (ret == 0)
					जारी;
			पूर्ण
			वापस ret;
		पूर्ण

		अगर (S_ISREG(ci->vfs_inode.i_mode) &&
		    ci->i_अंतरभूत_version != CEPH_INLINE_NONE &&
		    (_got & (CEPH_CAP_खाता_CACHE|CEPH_CAP_खाता_LAZYIO)) &&
		    i_size_पढ़ो(inode) > 0) अणु
			काष्ठा page *page =
				find_get_page(inode->i_mapping, 0);
			अगर (page) अणु
				bool uptodate = PageUptodate(page);

				put_page(page);
				अगर (uptodate)
					अवरोध;
			पूर्ण
			/*
			 * drop cap refs first because getattr जबतक
			 * holding * caps refs can cause deadlock.
			 */
			ceph_put_cap_refs(ci, _got);
			_got = 0;

			/*
			 * getattr request will bring अंतरभूत data पूर्णांकo
			 * page cache
			 */
			ret = __ceph_करो_getattr(inode, शून्य,
						CEPH_STAT_CAP_INLINE_DATA,
						true);
			अगर (ret < 0)
				वापस ret;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
	*got = _got;
	वापस 0;
पूर्ण

/*
 * Take cap refs.  Caller must alपढ़ोy know we hold at least one ref
 * on the caps in question or we करोn't know this is safe.
 */
व्योम ceph_get_cap_refs(काष्ठा ceph_inode_info *ci, पूर्णांक caps)
अणु
	spin_lock(&ci->i_ceph_lock);
	ceph_take_cap_refs(ci, caps, false);
	spin_unlock(&ci->i_ceph_lock);
पूर्ण


/*
 * drop cap_snap that is not associated with any snapshot.
 * we करोn't need to send FLUSHSNAP message क्रम it.
 */
अटल पूर्णांक ceph_try_drop_cap_snap(काष्ठा ceph_inode_info *ci,
				  काष्ठा ceph_cap_snap *capsnap)
अणु
	अगर (!capsnap->need_flush &&
	    !capsnap->writing && !capsnap->dirty_pages) अणु
		करोut("dropping cap_snap %p follows %llu\n",
		     capsnap, capsnap->follows);
		BUG_ON(capsnap->cap_flush.tid > 0);
		ceph_put_snap_context(capsnap->context);
		अगर (!list_is_last(&capsnap->ci_item, &ci->i_cap_snaps))
			ci->i_ceph_flags |= CEPH_I_FLUSH_SNAPS;

		list_del(&capsnap->ci_item);
		ceph_put_cap_snap(capsnap);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

क्रमागत put_cap_refs_mode अणु
	PUT_CAP_REFS_SYNC = 0,
	PUT_CAP_REFS_NO_CHECK,
	PUT_CAP_REFS_ASYNC,
पूर्ण;

/*
 * Release cap refs.
 *
 * If we released the last ref on any given cap, call ceph_check_caps
 * to release (or schedule a release).
 *
 * If we are releasing a WR cap (from a sync ग_लिखो), finalize any affected
 * cap_snap, and wake up any रुकोers.
 */
अटल व्योम __ceph_put_cap_refs(काष्ठा ceph_inode_info *ci, पूर्णांक had,
				क्रमागत put_cap_refs_mode mode)
अणु
	काष्ठा inode *inode = &ci->vfs_inode;
	पूर्णांक last = 0, put = 0, flushsnaps = 0, wake = 0;
	bool check_flushsnaps = false;

	spin_lock(&ci->i_ceph_lock);
	अगर (had & CEPH_CAP_PIN)
		--ci->i_pin_ref;
	अगर (had & CEPH_CAP_खाता_RD)
		अगर (--ci->i_rd_ref == 0)
			last++;
	अगर (had & CEPH_CAP_खाता_CACHE)
		अगर (--ci->i_rdcache_ref == 0)
			last++;
	अगर (had & CEPH_CAP_खाता_EXCL)
		अगर (--ci->i_fx_ref == 0)
			last++;
	अगर (had & CEPH_CAP_खाता_BUFFER) अणु
		अगर (--ci->i_wb_ref == 0) अणु
			last++;
			/* put the ref held by ceph_take_cap_refs() */
			put++;
			check_flushsnaps = true;
		पूर्ण
		करोut("put_cap_refs %p wb %d -> %d (?)\n",
		     inode, ci->i_wb_ref+1, ci->i_wb_ref);
	पूर्ण
	अगर (had & CEPH_CAP_खाता_WR) अणु
		अगर (--ci->i_wr_ref == 0) अणु
			last++;
			check_flushsnaps = true;
			अगर (ci->i_wrbuffer_ref_head == 0 &&
			    ci->i_dirty_caps == 0 &&
			    ci->i_flushing_caps == 0) अणु
				BUG_ON(!ci->i_head_snapc);
				ceph_put_snap_context(ci->i_head_snapc);
				ci->i_head_snapc = शून्य;
			पूर्ण
			/* see comment in __ceph_हटाओ_cap() */
			अगर (!__ceph_is_any_real_caps(ci) && ci->i_snap_realm)
				drop_inode_snap_realm(ci);
		पूर्ण
	पूर्ण
	अगर (check_flushsnaps && __ceph_have_pending_cap_snap(ci)) अणु
		काष्ठा ceph_cap_snap *capsnap =
			list_last_entry(&ci->i_cap_snaps,
					काष्ठा ceph_cap_snap,
					ci_item);

		capsnap->writing = 0;
		अगर (ceph_try_drop_cap_snap(ci, capsnap))
			/* put the ref held by ceph_queue_cap_snap() */
			put++;
		अन्यथा अगर (__ceph_finish_cap_snap(ci, capsnap))
			flushsnaps = 1;
		wake = 1;
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);

	करोut("put_cap_refs %p had %s%s%s\n", inode, ceph_cap_string(had),
	     last ? " last" : "", put ? " put" : "");

	चयन (mode) अणु
	हाल PUT_CAP_REFS_SYNC:
		अगर (last)
			ceph_check_caps(ci, 0, शून्य);
		अन्यथा अगर (flushsnaps)
			ceph_flush_snaps(ci, शून्य);
		अवरोध;
	हाल PUT_CAP_REFS_ASYNC:
		अगर (last)
			ceph_queue_check_caps(inode);
		अन्यथा अगर (flushsnaps)
			ceph_queue_flush_snaps(inode);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (wake)
		wake_up_all(&ci->i_cap_wq);
	जबतक (put-- > 0)
		iput(inode);
पूर्ण

व्योम ceph_put_cap_refs(काष्ठा ceph_inode_info *ci, पूर्णांक had)
अणु
	__ceph_put_cap_refs(ci, had, PUT_CAP_REFS_SYNC);
पूर्ण

व्योम ceph_put_cap_refs_async(काष्ठा ceph_inode_info *ci, पूर्णांक had)
अणु
	__ceph_put_cap_refs(ci, had, PUT_CAP_REFS_ASYNC);
पूर्ण

व्योम ceph_put_cap_refs_no_check_caps(काष्ठा ceph_inode_info *ci, पूर्णांक had)
अणु
	__ceph_put_cap_refs(ci, had, PUT_CAP_REFS_NO_CHECK);
पूर्ण

/*
 * Release @nr WRBUFFER refs on dirty pages क्रम the given @snapc snap
 * context.  Adjust per-snap dirty page accounting as appropriate.
 * Once all dirty data क्रम a cap_snap is flushed, flush snapped file
 * metadata back to the MDS.  If we dropped the last ref, call
 * ceph_check_caps.
 */
व्योम ceph_put_wrbuffer_cap_refs(काष्ठा ceph_inode_info *ci, पूर्णांक nr,
				काष्ठा ceph_snap_context *snapc)
अणु
	काष्ठा inode *inode = &ci->vfs_inode;
	काष्ठा ceph_cap_snap *capsnap = शून्य;
	पूर्णांक put = 0;
	bool last = false;
	bool found = false;
	bool flush_snaps = false;
	bool complete_capsnap = false;

	spin_lock(&ci->i_ceph_lock);
	ci->i_wrbuffer_ref -= nr;
	अगर (ci->i_wrbuffer_ref == 0) अणु
		last = true;
		put++;
	पूर्ण

	अगर (ci->i_head_snapc == snapc) अणु
		ci->i_wrbuffer_ref_head -= nr;
		अगर (ci->i_wrbuffer_ref_head == 0 &&
		    ci->i_wr_ref == 0 &&
		    ci->i_dirty_caps == 0 &&
		    ci->i_flushing_caps == 0) अणु
			BUG_ON(!ci->i_head_snapc);
			ceph_put_snap_context(ci->i_head_snapc);
			ci->i_head_snapc = शून्य;
		पूर्ण
		करोut("put_wrbuffer_cap_refs on %p head %d/%d -> %d/%d %s\n",
		     inode,
		     ci->i_wrbuffer_ref+nr, ci->i_wrbuffer_ref_head+nr,
		     ci->i_wrbuffer_ref, ci->i_wrbuffer_ref_head,
		     last ? " LAST" : "");
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(capsnap, &ci->i_cap_snaps, ci_item) अणु
			अगर (capsnap->context == snapc) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
		BUG_ON(!found);
		capsnap->dirty_pages -= nr;
		अगर (capsnap->dirty_pages == 0) अणु
			complete_capsnap = true;
			अगर (!capsnap->writing) अणु
				अगर (ceph_try_drop_cap_snap(ci, capsnap)) अणु
					put++;
				पूर्ण अन्यथा अणु
					ci->i_ceph_flags |= CEPH_I_FLUSH_SNAPS;
					flush_snaps = true;
				पूर्ण
			पूर्ण
		पूर्ण
		करोut("put_wrbuffer_cap_refs on %p cap_snap %p "
		     " snap %lld %d/%d -> %d/%d %s%s\n",
		     inode, capsnap, capsnap->context->seq,
		     ci->i_wrbuffer_ref+nr, capsnap->dirty_pages + nr,
		     ci->i_wrbuffer_ref, capsnap->dirty_pages,
		     last ? " (wrbuffer last)" : "",
		     complete_capsnap ? " (complete capsnap)" : "");
	पूर्ण

	spin_unlock(&ci->i_ceph_lock);

	अगर (last) अणु
		ceph_check_caps(ci, 0, शून्य);
	पूर्ण अन्यथा अगर (flush_snaps) अणु
		ceph_flush_snaps(ci, शून्य);
	पूर्ण
	अगर (complete_capsnap)
		wake_up_all(&ci->i_cap_wq);
	जबतक (put-- > 0) अणु
		/* aव्योम calling iput_final() in osd dispatch thपढ़ोs */
		ceph_async_iput(inode);
	पूर्ण
पूर्ण

/*
 * Invalidate unlinked inode's aliases, so we can drop the inode ASAP.
 */
अटल व्योम invalidate_aliases(काष्ठा inode *inode)
अणु
	काष्ठा dentry *dn, *prev = शून्य;

	करोut("invalidate_aliases inode %p\n", inode);
	d_prune_aliases(inode);
	/*
	 * For non-directory inode, d_find_alias() only वापसs
	 * hashed dentry. After calling d_invalidate(), the
	 * dentry becomes unhashed.
	 *
	 * For directory inode, d_find_alias() can वापस
	 * unhashed dentry. But directory inode should have
	 * one alias at most.
	 */
	जबतक ((dn = d_find_alias(inode))) अणु
		अगर (dn == prev) अणु
			dput(dn);
			अवरोध;
		पूर्ण
		d_invalidate(dn);
		अगर (prev)
			dput(prev);
		prev = dn;
	पूर्ण
	अगर (prev)
		dput(prev);
पूर्ण

काष्ठा cap_extra_info अणु
	काष्ठा ceph_string *pool_ns;
	/* अंतरभूत data */
	u64 अंतरभूत_version;
	व्योम *अंतरभूत_data;
	u32 अंतरभूत_len;
	/* dirstat */
	bool dirstat_valid;
	u64 nfiles;
	u64 nsubdirs;
	u64 change_attr;
	/* currently issued */
	पूर्णांक issued;
	काष्ठा बारpec64 bसमय;
पूर्ण;

/*
 * Handle a cap GRANT message from the MDS.  (Note that a GRANT may
 * actually be a revocation अगर it specअगरies a smaller cap set.)
 *
 * caller holds s_mutex and i_ceph_lock, we drop both.
 */
अटल व्योम handle_cap_grant(काष्ठा inode *inode,
			     काष्ठा ceph_mds_session *session,
			     काष्ठा ceph_cap *cap,
			     काष्ठा ceph_mds_caps *grant,
			     काष्ठा ceph_buffer *xattr_buf,
			     काष्ठा cap_extra_info *extra_info)
	__releases(ci->i_ceph_lock)
	__releases(session->s_mdsc->snap_rwsem)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक seq = le32_to_cpu(grant->seq);
	पूर्णांक newcaps = le32_to_cpu(grant->caps);
	पूर्णांक used, wanted, dirty;
	u64 size = le64_to_cpu(grant->size);
	u64 max_size = le64_to_cpu(grant->max_size);
	अचिन्हित अक्षर check_caps = 0;
	bool was_stale = cap->cap_gen < session->s_cap_gen;
	bool wake = false;
	bool ग_लिखोback = false;
	bool queue_trunc = false;
	bool queue_invalidate = false;
	bool deleted_inode = false;
	bool fill_अंतरभूत = false;

	करोut("handle_cap_grant inode %p cap %p mds%d seq %d %s\n",
	     inode, cap, session->s_mds, seq, ceph_cap_string(newcaps));
	करोut(" size %llu max_size %llu, i_size %llu\n", size, max_size,
		i_size_पढ़ो(inode));


	/*
	 * If CACHE is being revoked, and we have no dirty buffers,
	 * try to invalidate (once).  (If there are dirty buffers, we
	 * will invalidate _after_ ग_लिखोback.)
	 */
	अगर (S_ISREG(inode->i_mode) && /* करोn't invalidate सूची_पढ़ो cache */
	    ((cap->issued & ~newcaps) & CEPH_CAP_खाता_CACHE) &&
	    (newcaps & CEPH_CAP_खाता_LAZYIO) == 0 &&
	    !(ci->i_wrbuffer_ref || ci->i_wb_ref)) अणु
		अगर (try_nonblocking_invalidate(inode)) अणु
			/* there were locked pages.. invalidate later
			   in a separate thपढ़ो. */
			अगर (ci->i_rdcache_revoking != ci->i_rdcache_gen) अणु
				queue_invalidate = true;
				ci->i_rdcache_revoking = ci->i_rdcache_gen;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (was_stale)
		cap->issued = cap->implemented = CEPH_CAP_PIN;

	/*
	 * auth mds of the inode changed. we received the cap export message,
	 * but still haven't received the cap import message. handle_cap_export
	 * updated the new auth MDS' cap.
	 *
	 * "ceph_seq_cmp(seq, cap->seq) <= 0" means we are processing a message
	 * that was sent beक्रमe the cap import message. So करोn't हटाओ caps.
	 */
	अगर (ceph_seq_cmp(seq, cap->seq) <= 0) अणु
		WARN_ON(cap != ci->i_auth_cap);
		WARN_ON(cap->cap_id != le64_to_cpu(grant->cap_id));
		seq = cap->seq;
		newcaps |= cap->issued;
	पूर्ण

	/* side effects now are allowed */
	cap->cap_gen = session->s_cap_gen;
	cap->seq = seq;

	__check_cap_issue(ci, cap, newcaps);

	inode_set_max_iversion_raw(inode, extra_info->change_attr);

	अगर ((newcaps & CEPH_CAP_AUTH_SHARED) &&
	    (extra_info->issued & CEPH_CAP_AUTH_EXCL) == 0) अणु
		umode_t mode = le32_to_cpu(grant->mode);

		अगर (inode_wrong_type(inode, mode))
			pr_warn_once("inode type changed! (ino %llx.%llx is 0%o, mds says 0%o)\n",
				     ceph_vinop(inode), inode->i_mode, mode);
		अन्यथा
			inode->i_mode = mode;
		inode->i_uid = make_kuid(&init_user_ns, le32_to_cpu(grant->uid));
		inode->i_gid = make_kgid(&init_user_ns, le32_to_cpu(grant->gid));
		ci->i_bसमय = extra_info->bसमय;
		करोut("%p mode 0%o uid.gid %d.%d\n", inode, inode->i_mode,
		     from_kuid(&init_user_ns, inode->i_uid),
		     from_kgid(&init_user_ns, inode->i_gid));
	पूर्ण

	अगर ((newcaps & CEPH_CAP_LINK_SHARED) &&
	    (extra_info->issued & CEPH_CAP_LINK_EXCL) == 0) अणु
		set_nlink(inode, le32_to_cpu(grant->nlink));
		अगर (inode->i_nlink == 0 &&
		    (newcaps & (CEPH_CAP_LINK_SHARED | CEPH_CAP_LINK_EXCL)))
			deleted_inode = true;
	पूर्ण

	अगर ((extra_info->issued & CEPH_CAP_XATTR_EXCL) == 0 &&
	    grant->xattr_len) अणु
		पूर्णांक len = le32_to_cpu(grant->xattr_len);
		u64 version = le64_to_cpu(grant->xattr_version);

		अगर (version > ci->i_xattrs.version) अणु
			करोut(" got new xattrs v%llu on %p len %d\n",
			     version, inode, len);
			अगर (ci->i_xattrs.blob)
				ceph_buffer_put(ci->i_xattrs.blob);
			ci->i_xattrs.blob = ceph_buffer_get(xattr_buf);
			ci->i_xattrs.version = version;
			ceph_क्रमget_all_cached_acls(inode);
			ceph_security_invalidate_secctx(inode);
		पूर्ण
	पूर्ण

	अगर (newcaps & CEPH_CAP_ANY_RD) अणु
		काष्ठा बारpec64 mसमय, aसमय, स_समय;
		/* स_समय/mसमय/aसमय? */
		ceph_decode_बारpec64(&mसमय, &grant->mसमय);
		ceph_decode_बारpec64(&aसमय, &grant->aसमय);
		ceph_decode_बारpec64(&स_समय, &grant->स_समय);
		ceph_fill_file_समय(inode, extra_info->issued,
				    le32_to_cpu(grant->समय_warp_seq),
				    &स_समय, &mसमय, &aसमय);
	पूर्ण

	अगर ((newcaps & CEPH_CAP_खाता_SHARED) && extra_info->dirstat_valid) अणु
		ci->i_files = extra_info->nfiles;
		ci->i_subdirs = extra_info->nsubdirs;
	पूर्ण

	अगर (newcaps & (CEPH_CAP_ANY_खाता_RD | CEPH_CAP_ANY_खाता_WR)) अणु
		/* file layout may have changed */
		s64 old_pool = ci->i_layout.pool_id;
		काष्ठा ceph_string *old_ns;

		ceph_file_layout_from_legacy(&ci->i_layout, &grant->layout);
		old_ns = rcu_dereference_रक्षित(ci->i_layout.pool_ns,
					lockdep_is_held(&ci->i_ceph_lock));
		rcu_assign_poपूर्णांकer(ci->i_layout.pool_ns, extra_info->pool_ns);

		अगर (ci->i_layout.pool_id != old_pool ||
		    extra_info->pool_ns != old_ns)
			ci->i_ceph_flags &= ~CEPH_I_POOL_PERM;

		extra_info->pool_ns = old_ns;

		/* size/truncate_seq? */
		queue_trunc = ceph_fill_file_size(inode, extra_info->issued,
					le32_to_cpu(grant->truncate_seq),
					le64_to_cpu(grant->truncate_size),
					size);
	पूर्ण

	अगर (ci->i_auth_cap == cap && (newcaps & CEPH_CAP_ANY_खाता_WR)) अणु
		अगर (max_size != ci->i_max_size) अणु
			करोut("max_size %lld -> %llu\n",
			     ci->i_max_size, max_size);
			ci->i_max_size = max_size;
			अगर (max_size >= ci->i_wanted_max_size) अणु
				ci->i_wanted_max_size = 0;  /* reset */
				ci->i_requested_max_size = 0;
			पूर्ण
			wake = true;
		पूर्ण
	पूर्ण

	/* check cap bits */
	wanted = __ceph_caps_wanted(ci);
	used = __ceph_caps_used(ci);
	dirty = __ceph_caps_dirty(ci);
	करोut(" my wanted = %s, used = %s, dirty %s\n",
	     ceph_cap_string(wanted),
	     ceph_cap_string(used),
	     ceph_cap_string(dirty));

	अगर ((was_stale || le32_to_cpu(grant->op) == CEPH_CAP_OP_IMPORT) &&
	    (wanted & ~(cap->mds_wanted | newcaps))) अणु
		/*
		 * If mds is importing cap, prior cap messages that update
		 * 'wanted' may get dropped by mds (migrate seq mismatch).
		 *
		 * We करोn't send cap message to update 'wanted' अगर what we
		 * want are alपढ़ोy issued. If mds revokes caps, cap message
		 * that releases caps also tells mds what we want. But अगर
		 * caps got revoked by mds क्रमcedly (session stale). We may
		 * haven't told mds what we want.
		 */
		check_caps = 1;
	पूर्ण

	/* revocation, grant, or no-op? */
	अगर (cap->issued & ~newcaps) अणु
		पूर्णांक revoking = cap->issued & ~newcaps;

		करोut("revocation: %s -> %s (revoking %s)\n",
		     ceph_cap_string(cap->issued),
		     ceph_cap_string(newcaps),
		     ceph_cap_string(revoking));
		अगर (S_ISREG(inode->i_mode) &&
		    (revoking & used & CEPH_CAP_खाता_BUFFER))
			ग_लिखोback = true;  /* initiate ग_लिखोback; will delay ack */
		अन्यथा अगर (queue_invalidate &&
			 revoking == CEPH_CAP_खाता_CACHE &&
			 (newcaps & CEPH_CAP_खाता_LAZYIO) == 0)
			; /* करो nothing yet, invalidation will be queued */
		अन्यथा अगर (cap == ci->i_auth_cap)
			check_caps = 1; /* check auth cap only */
		अन्यथा
			check_caps = 2; /* check all caps */
		cap->issued = newcaps;
		cap->implemented |= newcaps;
	पूर्ण अन्यथा अगर (cap->issued == newcaps) अणु
		करोut("caps unchanged: %s -> %s\n",
		     ceph_cap_string(cap->issued), ceph_cap_string(newcaps));
	पूर्ण अन्यथा अणु
		करोut("grant: %s -> %s\n", ceph_cap_string(cap->issued),
		     ceph_cap_string(newcaps));
		/* non-auth MDS is revoking the newly grant caps ? */
		अगर (cap == ci->i_auth_cap &&
		    __ceph_caps_revoking_other(ci, cap, newcaps))
		    check_caps = 2;

		cap->issued = newcaps;
		cap->implemented |= newcaps; /* add bits only, to
					      * aव्योम stepping on a
					      * pending revocation */
		wake = true;
	पूर्ण
	BUG_ON(cap->issued & ~cap->implemented);

	अगर (extra_info->अंतरभूत_version > 0 &&
	    extra_info->अंतरभूत_version >= ci->i_अंतरभूत_version) अणु
		ci->i_अंतरभूत_version = extra_info->अंतरभूत_version;
		अगर (ci->i_अंतरभूत_version != CEPH_INLINE_NONE &&
		    (newcaps & (CEPH_CAP_खाता_CACHE|CEPH_CAP_खाता_LAZYIO)))
			fill_अंतरभूत = true;
	पूर्ण

	अगर (ci->i_auth_cap == cap &&
	    le32_to_cpu(grant->op) == CEPH_CAP_OP_IMPORT) अणु
		अगर (newcaps & ~extra_info->issued)
			wake = true;

		अगर (ci->i_requested_max_size > max_size ||
		    !(le32_to_cpu(grant->wanted) & CEPH_CAP_ANY_खाता_WR)) अणु
			/* re-request max_size अगर necessary */
			ci->i_requested_max_size = 0;
			wake = true;
		पूर्ण

		ceph_kick_flushing_inode_caps(session, ci);
		spin_unlock(&ci->i_ceph_lock);
		up_पढ़ो(&session->s_mdsc->snap_rwsem);
	पूर्ण अन्यथा अणु
		spin_unlock(&ci->i_ceph_lock);
	पूर्ण

	अगर (fill_अंतरभूत)
		ceph_fill_अंतरभूत_data(inode, शून्य, extra_info->अंतरभूत_data,
				      extra_info->अंतरभूत_len);

	अगर (queue_trunc)
		ceph_queue_vmtruncate(inode);

	अगर (ग_लिखोback)
		/*
		 * queue inode क्रम ग_लिखोback: we can't actually call
		 * filemap_ग_लिखो_and_रुको, etc. from message handler
		 * context.
		 */
		ceph_queue_ग_लिखोback(inode);
	अगर (queue_invalidate)
		ceph_queue_invalidate(inode);
	अगर (deleted_inode)
		invalidate_aliases(inode);
	अगर (wake)
		wake_up_all(&ci->i_cap_wq);

	अगर (check_caps == 1)
		ceph_check_caps(ci, CHECK_CAPS_AUTHONLY | CHECK_CAPS_NOINVAL,
				session);
	अन्यथा अगर (check_caps == 2)
		ceph_check_caps(ci, CHECK_CAPS_NOINVAL, session);
	अन्यथा
		mutex_unlock(&session->s_mutex);
पूर्ण

/*
 * Handle FLUSH_ACK from MDS, indicating that metadata we sent to the
 * MDS has been safely committed.
 */
अटल व्योम handle_cap_flush_ack(काष्ठा inode *inode, u64 flush_tid,
				 काष्ठा ceph_mds_caps *m,
				 काष्ठा ceph_mds_session *session,
				 काष्ठा ceph_cap *cap)
	__releases(ci->i_ceph_lock)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_client(inode->i_sb)->mdsc;
	काष्ठा ceph_cap_flush *cf, *पंचांगp_cf;
	LIST_HEAD(to_हटाओ);
	अचिन्हित seq = le32_to_cpu(m->seq);
	पूर्णांक dirty = le32_to_cpu(m->dirty);
	पूर्णांक cleaned = 0;
	bool drop = false;
	bool wake_ci = false;
	bool wake_mdsc = false;

	list_क्रम_each_entry_safe(cf, पंचांगp_cf, &ci->i_cap_flush_list, i_list) अणु
		/* Is this the one that was flushed? */
		अगर (cf->tid == flush_tid)
			cleaned = cf->caps;

		/* Is this a capsnap? */
		अगर (cf->caps == 0)
			जारी;

		अगर (cf->tid <= flush_tid) अणु
			/*
			 * An earlier or current tid. The FLUSH_ACK should
			 * represent a superset of this flush's caps.
			 */
			wake_ci |= __detach_cap_flush_from_ci(ci, cf);
			list_add_tail(&cf->i_list, &to_हटाओ);
		पूर्ण अन्यथा अणु
			/*
			 * This is a later one. Any caps in it are still dirty
			 * so करोn't count them as cleaned.
			 */
			cleaned &= ~cf->caps;
			अगर (!cleaned)
				अवरोध;
		पूर्ण
	पूर्ण

	करोut("handle_cap_flush_ack inode %p mds%d seq %d on %s cleaned %s,"
	     " flushing %s -> %s\n",
	     inode, session->s_mds, seq, ceph_cap_string(dirty),
	     ceph_cap_string(cleaned), ceph_cap_string(ci->i_flushing_caps),
	     ceph_cap_string(ci->i_flushing_caps & ~cleaned));

	अगर (list_empty(&to_हटाओ) && !cleaned)
		जाओ out;

	ci->i_flushing_caps &= ~cleaned;

	spin_lock(&mdsc->cap_dirty_lock);

	list_क्रम_each_entry(cf, &to_हटाओ, i_list)
		wake_mdsc |= __detach_cap_flush_from_mdsc(mdsc, cf);

	अगर (ci->i_flushing_caps == 0) अणु
		अगर (list_empty(&ci->i_cap_flush_list)) अणु
			list_del_init(&ci->i_flushing_item);
			अगर (!list_empty(&session->s_cap_flushing)) अणु
				करोut(" mds%d still flushing cap on %p\n",
				     session->s_mds,
				     &list_first_entry(&session->s_cap_flushing,
						काष्ठा ceph_inode_info,
						i_flushing_item)->vfs_inode);
			पूर्ण
		पूर्ण
		mdsc->num_cap_flushing--;
		करोut(" inode %p now !flushing\n", inode);

		अगर (ci->i_dirty_caps == 0) अणु
			करोut(" inode %p now clean\n", inode);
			BUG_ON(!list_empty(&ci->i_dirty_item));
			drop = true;
			अगर (ci->i_wr_ref == 0 &&
			    ci->i_wrbuffer_ref_head == 0) अणु
				BUG_ON(!ci->i_head_snapc);
				ceph_put_snap_context(ci->i_head_snapc);
				ci->i_head_snapc = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			BUG_ON(list_empty(&ci->i_dirty_item));
		पूर्ण
	पूर्ण
	spin_unlock(&mdsc->cap_dirty_lock);

out:
	spin_unlock(&ci->i_ceph_lock);

	जबतक (!list_empty(&to_हटाओ)) अणु
		cf = list_first_entry(&to_हटाओ,
				      काष्ठा ceph_cap_flush, i_list);
		list_del(&cf->i_list);
		ceph_मुक्त_cap_flush(cf);
	पूर्ण

	अगर (wake_ci)
		wake_up_all(&ci->i_cap_wq);
	अगर (wake_mdsc)
		wake_up_all(&mdsc->cap_flushing_wq);
	अगर (drop)
		iput(inode);
पूर्ण

/*
 * Handle FLUSHSNAP_ACK.  MDS has flushed snap data to disk and we can
 * throw away our cap_snap.
 *
 * Caller hold s_mutex.
 */
अटल व्योम handle_cap_flushsnap_ack(काष्ठा inode *inode, u64 flush_tid,
				     काष्ठा ceph_mds_caps *m,
				     काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_client(inode->i_sb)->mdsc;
	u64 follows = le64_to_cpu(m->snap_follows);
	काष्ठा ceph_cap_snap *capsnap;
	bool flushed = false;
	bool wake_ci = false;
	bool wake_mdsc = false;

	करोut("handle_cap_flushsnap_ack inode %p ci %p mds%d follows %lld\n",
	     inode, ci, session->s_mds, follows);

	spin_lock(&ci->i_ceph_lock);
	list_क्रम_each_entry(capsnap, &ci->i_cap_snaps, ci_item) अणु
		अगर (capsnap->follows == follows) अणु
			अगर (capsnap->cap_flush.tid != flush_tid) अणु
				करोut(" cap_snap %p follows %lld tid %lld !="
				     " %lld\n", capsnap, follows,
				     flush_tid, capsnap->cap_flush.tid);
				अवरोध;
			पूर्ण
			flushed = true;
			अवरोध;
		पूर्ण अन्यथा अणु
			करोut(" skipping cap_snap %p follows %lld\n",
			     capsnap, capsnap->follows);
		पूर्ण
	पूर्ण
	अगर (flushed) अणु
		WARN_ON(capsnap->dirty_pages || capsnap->writing);
		करोut(" removing %p cap_snap %p follows %lld\n",
		     inode, capsnap, follows);
		list_del(&capsnap->ci_item);
		wake_ci |= __detach_cap_flush_from_ci(ci, &capsnap->cap_flush);

		spin_lock(&mdsc->cap_dirty_lock);

		अगर (list_empty(&ci->i_cap_flush_list))
			list_del_init(&ci->i_flushing_item);

		wake_mdsc |= __detach_cap_flush_from_mdsc(mdsc,
							  &capsnap->cap_flush);
		spin_unlock(&mdsc->cap_dirty_lock);
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);
	अगर (flushed) अणु
		ceph_put_snap_context(capsnap->context);
		ceph_put_cap_snap(capsnap);
		अगर (wake_ci)
			wake_up_all(&ci->i_cap_wq);
		अगर (wake_mdsc)
			wake_up_all(&mdsc->cap_flushing_wq);
		iput(inode);
	पूर्ण
पूर्ण

/*
 * Handle TRUNC from MDS, indicating file truncation.
 *
 * caller hold s_mutex.
 */
अटल bool handle_cap_trunc(काष्ठा inode *inode,
			     काष्ठा ceph_mds_caps *trunc,
			     काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक mds = session->s_mds;
	पूर्णांक seq = le32_to_cpu(trunc->seq);
	u32 truncate_seq = le32_to_cpu(trunc->truncate_seq);
	u64 truncate_size = le64_to_cpu(trunc->truncate_size);
	u64 size = le64_to_cpu(trunc->size);
	पूर्णांक implemented = 0;
	पूर्णांक dirty = __ceph_caps_dirty(ci);
	पूर्णांक issued = __ceph_caps_issued(ceph_inode(inode), &implemented);
	bool queue_trunc = false;

	lockdep_निश्चित_held(&ci->i_ceph_lock);

	issued |= implemented | dirty;

	करोut("handle_cap_trunc inode %p mds%d seq %d to %lld seq %d\n",
	     inode, mds, seq, truncate_size, truncate_seq);
	queue_trunc = ceph_fill_file_size(inode, issued,
					  truncate_seq, truncate_size, size);
	वापस queue_trunc;
पूर्ण

/*
 * Handle EXPORT from MDS.  Cap is being migrated _from_ this mds to a
 * dअगरferent one.  If we are the most recent migration we've seen (as
 * indicated by mseq), make note of the migrating cap bits क्रम the
 * duration (until we see the corresponding IMPORT).
 *
 * caller holds s_mutex
 */
अटल व्योम handle_cap_export(काष्ठा inode *inode, काष्ठा ceph_mds_caps *ex,
			      काष्ठा ceph_mds_cap_peer *ph,
			      काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_inode_to_client(inode)->mdsc;
	काष्ठा ceph_mds_session *tsession = शून्य;
	काष्ठा ceph_cap *cap, *tcap, *new_cap = शून्य;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	u64 t_cap_id;
	अचिन्हित mseq = le32_to_cpu(ex->migrate_seq);
	अचिन्हित t_seq, t_mseq;
	पूर्णांक target, issued;
	पूर्णांक mds = session->s_mds;

	अगर (ph) अणु
		t_cap_id = le64_to_cpu(ph->cap_id);
		t_seq = le32_to_cpu(ph->seq);
		t_mseq = le32_to_cpu(ph->mseq);
		target = le32_to_cpu(ph->mds);
	पूर्ण अन्यथा अणु
		t_cap_id = t_seq = t_mseq = 0;
		target = -1;
	पूर्ण

	करोut("handle_cap_export inode %p ci %p mds%d mseq %d target %d\n",
	     inode, ci, mds, mseq, target);
retry:
	spin_lock(&ci->i_ceph_lock);
	cap = __get_cap_क्रम_mds(ci, mds);
	अगर (!cap || cap->cap_id != le64_to_cpu(ex->cap_id))
		जाओ out_unlock;

	अगर (target < 0) अणु
		__ceph_हटाओ_cap(cap, false);
		जाओ out_unlock;
	पूर्ण

	/*
	 * now we know we haven't received the cap import message yet
	 * because the exported cap still exist.
	 */

	issued = cap->issued;
	अगर (issued != cap->implemented)
		pr_err_ratelimited("handle_cap_export: issued != implemented: "
				"ino (%llx.%llx) mds%d seq %d mseq %d "
				"issued %s implemented %s\n",
				ceph_vinop(inode), mds, cap->seq, cap->mseq,
				ceph_cap_string(issued),
				ceph_cap_string(cap->implemented));


	tcap = __get_cap_क्रम_mds(ci, target);
	अगर (tcap) अणु
		/* alपढ़ोy have caps from the target */
		अगर (tcap->cap_id == t_cap_id &&
		    ceph_seq_cmp(tcap->seq, t_seq) < 0) अणु
			करोut(" updating import cap %p mds%d\n", tcap, target);
			tcap->cap_id = t_cap_id;
			tcap->seq = t_seq - 1;
			tcap->issue_seq = t_seq - 1;
			tcap->issued |= issued;
			tcap->implemented |= issued;
			अगर (cap == ci->i_auth_cap) अणु
				ci->i_auth_cap = tcap;
				change_auth_cap_ses(ci, tcap->session);
			पूर्ण
		पूर्ण
		__ceph_हटाओ_cap(cap, false);
		जाओ out_unlock;
	पूर्ण अन्यथा अगर (tsession) अणु
		/* add placeholder क्रम the export tagert */
		पूर्णांक flag = (cap == ci->i_auth_cap) ? CEPH_CAP_FLAG_AUTH : 0;
		tcap = new_cap;
		ceph_add_cap(inode, tsession, t_cap_id, issued, 0,
			     t_seq - 1, t_mseq, (u64)-1, flag, &new_cap);

		अगर (!list_empty(&ci->i_cap_flush_list) &&
		    ci->i_auth_cap == tcap) अणु
			spin_lock(&mdsc->cap_dirty_lock);
			list_move_tail(&ci->i_flushing_item,
				       &tcap->session->s_cap_flushing);
			spin_unlock(&mdsc->cap_dirty_lock);
		पूर्ण

		__ceph_हटाओ_cap(cap, false);
		जाओ out_unlock;
	पूर्ण

	spin_unlock(&ci->i_ceph_lock);
	mutex_unlock(&session->s_mutex);

	/* खोलो target session */
	tsession = ceph_mdsc_खोलो_export_target_session(mdsc, target);
	अगर (!IS_ERR(tsession)) अणु
		अगर (mds > target) अणु
			mutex_lock(&session->s_mutex);
			mutex_lock_nested(&tsession->s_mutex,
					  SINGLE_DEPTH_NESTING);
		पूर्ण अन्यथा अणु
			mutex_lock(&tsession->s_mutex);
			mutex_lock_nested(&session->s_mutex,
					  SINGLE_DEPTH_NESTING);
		पूर्ण
		new_cap = ceph_get_cap(mdsc, शून्य);
	पूर्ण अन्यथा अणु
		WARN_ON(1);
		tsession = शून्य;
		target = -1;
		mutex_lock(&session->s_mutex);
	पूर्ण
	जाओ retry;

out_unlock:
	spin_unlock(&ci->i_ceph_lock);
	mutex_unlock(&session->s_mutex);
	अगर (tsession) अणु
		mutex_unlock(&tsession->s_mutex);
		ceph_put_mds_session(tsession);
	पूर्ण
	अगर (new_cap)
		ceph_put_cap(mdsc, new_cap);
पूर्ण

/*
 * Handle cap IMPORT.
 *
 * caller holds s_mutex. acquires i_ceph_lock
 */
अटल व्योम handle_cap_import(काष्ठा ceph_mds_client *mdsc,
			      काष्ठा inode *inode, काष्ठा ceph_mds_caps *im,
			      काष्ठा ceph_mds_cap_peer *ph,
			      काष्ठा ceph_mds_session *session,
			      काष्ठा ceph_cap **target_cap, पूर्णांक *old_issued)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_cap *cap, *ocap, *new_cap = शून्य;
	पूर्णांक mds = session->s_mds;
	पूर्णांक issued;
	अचिन्हित caps = le32_to_cpu(im->caps);
	अचिन्हित wanted = le32_to_cpu(im->wanted);
	अचिन्हित seq = le32_to_cpu(im->seq);
	अचिन्हित mseq = le32_to_cpu(im->migrate_seq);
	u64 realmino = le64_to_cpu(im->realm);
	u64 cap_id = le64_to_cpu(im->cap_id);
	u64 p_cap_id;
	पूर्णांक peer;

	अगर (ph) अणु
		p_cap_id = le64_to_cpu(ph->cap_id);
		peer = le32_to_cpu(ph->mds);
	पूर्ण अन्यथा अणु
		p_cap_id = 0;
		peer = -1;
	पूर्ण

	करोut("handle_cap_import inode %p ci %p mds%d mseq %d peer %d\n",
	     inode, ci, mds, mseq, peer);
retry:
	cap = __get_cap_क्रम_mds(ci, mds);
	अगर (!cap) अणु
		अगर (!new_cap) अणु
			spin_unlock(&ci->i_ceph_lock);
			new_cap = ceph_get_cap(mdsc, शून्य);
			spin_lock(&ci->i_ceph_lock);
			जाओ retry;
		पूर्ण
		cap = new_cap;
	पूर्ण अन्यथा अणु
		अगर (new_cap) अणु
			ceph_put_cap(mdsc, new_cap);
			new_cap = शून्य;
		पूर्ण
	पूर्ण

	__ceph_caps_issued(ci, &issued);
	issued |= __ceph_caps_dirty(ci);

	ceph_add_cap(inode, session, cap_id, caps, wanted, seq, mseq,
		     realmino, CEPH_CAP_FLAG_AUTH, &new_cap);

	ocap = peer >= 0 ? __get_cap_क्रम_mds(ci, peer) : शून्य;
	अगर (ocap && ocap->cap_id == p_cap_id) अणु
		करोut(" remove export cap %p mds%d flags %d\n",
		     ocap, peer, ph->flags);
		अगर ((ph->flags & CEPH_CAP_FLAG_AUTH) &&
		    (ocap->seq != le32_to_cpu(ph->seq) ||
		     ocap->mseq != le32_to_cpu(ph->mseq))) अणु
			pr_err_ratelimited("handle_cap_import: "
					"mismatched seq/mseq: ino (%llx.%llx) "
					"mds%d seq %d mseq %d importer mds%d "
					"has peer seq %d mseq %d\n",
					ceph_vinop(inode), peer, ocap->seq,
					ocap->mseq, mds, le32_to_cpu(ph->seq),
					le32_to_cpu(ph->mseq));
		पूर्ण
		__ceph_हटाओ_cap(ocap, (ph->flags & CEPH_CAP_FLAG_RELEASE));
	पूर्ण

	*old_issued = issued;
	*target_cap = cap;
पूर्ण

/*
 * Handle a caps message from the MDS.
 *
 * Identअगरy the appropriate session, inode, and call the right handler
 * based on the cap op.
 */
व्योम ceph_handle_caps(काष्ठा ceph_mds_session *session,
		      काष्ठा ceph_msg *msg)
अणु
	काष्ठा ceph_mds_client *mdsc = session->s_mdsc;
	काष्ठा inode *inode;
	काष्ठा ceph_inode_info *ci;
	काष्ठा ceph_cap *cap;
	काष्ठा ceph_mds_caps *h;
	काष्ठा ceph_mds_cap_peer *peer = शून्य;
	काष्ठा ceph_snap_realm *realm = शून्य;
	पूर्णांक op;
	पूर्णांक msg_version = le16_to_cpu(msg->hdr.version);
	u32 seq, mseq;
	काष्ठा ceph_vino vino;
	व्योम *snaptrace;
	माप_प्रकार snaptrace_len;
	व्योम *p, *end;
	काष्ठा cap_extra_info extra_info = अणुपूर्ण;
	bool queue_trunc;

	करोut("handle_caps from mds%d\n", session->s_mds);

	/* decode */
	end = msg->front.iov_base + msg->front.iov_len;
	अगर (msg->front.iov_len < माप(*h))
		जाओ bad;
	h = msg->front.iov_base;
	op = le32_to_cpu(h->op);
	vino.ino = le64_to_cpu(h->ino);
	vino.snap = CEPH_NOSNAP;
	seq = le32_to_cpu(h->seq);
	mseq = le32_to_cpu(h->migrate_seq);

	snaptrace = h + 1;
	snaptrace_len = le32_to_cpu(h->snap_trace_len);
	p = snaptrace + snaptrace_len;

	अगर (msg_version >= 2) अणु
		u32 flock_len;
		ceph_decode_32_safe(&p, end, flock_len, bad);
		अगर (p + flock_len > end)
			जाओ bad;
		p += flock_len;
	पूर्ण

	अगर (msg_version >= 3) अणु
		अगर (op == CEPH_CAP_OP_IMPORT) अणु
			अगर (p + माप(*peer) > end)
				जाओ bad;
			peer = p;
			p += माप(*peer);
		पूर्ण अन्यथा अगर (op == CEPH_CAP_OP_EXPORT) अणु
			/* recorded in unused fields */
			peer = (व्योम *)&h->size;
		पूर्ण
	पूर्ण

	अगर (msg_version >= 4) अणु
		ceph_decode_64_safe(&p, end, extra_info.अंतरभूत_version, bad);
		ceph_decode_32_safe(&p, end, extra_info.अंतरभूत_len, bad);
		अगर (p + extra_info.अंतरभूत_len > end)
			जाओ bad;
		extra_info.अंतरभूत_data = p;
		p += extra_info.अंतरभूत_len;
	पूर्ण

	अगर (msg_version >= 5) अणु
		काष्ठा ceph_osd_client	*osdc = &mdsc->fsc->client->osdc;
		u32			epoch_barrier;

		ceph_decode_32_safe(&p, end, epoch_barrier, bad);
		ceph_osdc_update_epoch_barrier(osdc, epoch_barrier);
	पूर्ण

	अगर (msg_version >= 8) अणु
		u32 pool_ns_len;

		/* version >= 6 */
		ceph_decode_skip_64(&p, end, bad);	// flush_tid
		/* version >= 7 */
		ceph_decode_skip_32(&p, end, bad);	// caller_uid
		ceph_decode_skip_32(&p, end, bad);	// caller_gid
		/* version >= 8 */
		ceph_decode_32_safe(&p, end, pool_ns_len, bad);
		अगर (pool_ns_len > 0) अणु
			ceph_decode_need(&p, end, pool_ns_len, bad);
			extra_info.pool_ns =
				ceph_find_or_create_string(p, pool_ns_len);
			p += pool_ns_len;
		पूर्ण
	पूर्ण

	अगर (msg_version >= 9) अणु
		काष्ठा ceph_बारpec *bसमय;

		अगर (p + माप(*bसमय) > end)
			जाओ bad;
		bसमय = p;
		ceph_decode_बारpec64(&extra_info.bसमय, bसमय);
		p += माप(*bसमय);
		ceph_decode_64_safe(&p, end, extra_info.change_attr, bad);
	पूर्ण

	अगर (msg_version >= 11) अणु
		/* version >= 10 */
		ceph_decode_skip_32(&p, end, bad); // flags
		/* version >= 11 */
		extra_info.dirstat_valid = true;
		ceph_decode_64_safe(&p, end, extra_info.nfiles, bad);
		ceph_decode_64_safe(&p, end, extra_info.nsubdirs, bad);
	पूर्ण

	/* lookup ino */
	inode = ceph_find_inode(mdsc->fsc->sb, vino);
	ci = ceph_inode(inode);
	करोut(" op %s ino %llx.%llx inode %p\n", ceph_cap_op_name(op), vino.ino,
	     vino.snap, inode);

	mutex_lock(&session->s_mutex);
	inc_session_sequence(session);
	करोut(" mds%d seq %lld cap seq %u\n", session->s_mds, session->s_seq,
	     (अचिन्हित)seq);

	अगर (!inode) अणु
		करोut(" i don't have ino %llx\n", vino.ino);

		अगर (op == CEPH_CAP_OP_IMPORT) अणु
			cap = ceph_get_cap(mdsc, शून्य);
			cap->cap_ino = vino.ino;
			cap->queue_release = 1;
			cap->cap_id = le64_to_cpu(h->cap_id);
			cap->mseq = mseq;
			cap->seq = seq;
			cap->issue_seq = seq;
			spin_lock(&session->s_cap_lock);
			__ceph_queue_cap_release(session, cap);
			spin_unlock(&session->s_cap_lock);
		पूर्ण
		जाओ flush_cap_releases;
	पूर्ण

	/* these will work even अगर we करोn't have a cap yet */
	चयन (op) अणु
	हाल CEPH_CAP_OP_FLUSHSNAP_ACK:
		handle_cap_flushsnap_ack(inode, le64_to_cpu(msg->hdr.tid),
					 h, session);
		जाओ करोne;

	हाल CEPH_CAP_OP_EXPORT:
		handle_cap_export(inode, h, peer, session);
		जाओ करोne_unlocked;

	हाल CEPH_CAP_OP_IMPORT:
		realm = शून्य;
		अगर (snaptrace_len) अणु
			करोwn_ग_लिखो(&mdsc->snap_rwsem);
			ceph_update_snap_trace(mdsc, snaptrace,
					       snaptrace + snaptrace_len,
					       false, &realm);
			करोwngrade_ग_लिखो(&mdsc->snap_rwsem);
		पूर्ण अन्यथा अणु
			करोwn_पढ़ो(&mdsc->snap_rwsem);
		पूर्ण
		spin_lock(&ci->i_ceph_lock);
		handle_cap_import(mdsc, inode, h, peer, session,
				  &cap, &extra_info.issued);
		handle_cap_grant(inode, session, cap,
				 h, msg->middle, &extra_info);
		अगर (realm)
			ceph_put_snap_realm(mdsc, realm);
		जाओ करोne_unlocked;
	पूर्ण

	/* the rest require a cap */
	spin_lock(&ci->i_ceph_lock);
	cap = __get_cap_क्रम_mds(ceph_inode(inode), session->s_mds);
	अगर (!cap) अणु
		करोut(" no cap on %p ino %llx.%llx from mds%d\n",
		     inode, ceph_ino(inode), ceph_snap(inode),
		     session->s_mds);
		spin_unlock(&ci->i_ceph_lock);
		जाओ flush_cap_releases;
	पूर्ण

	/* note that each of these drops i_ceph_lock क्रम us */
	चयन (op) अणु
	हाल CEPH_CAP_OP_REVOKE:
	हाल CEPH_CAP_OP_GRANT:
		__ceph_caps_issued(ci, &extra_info.issued);
		extra_info.issued |= __ceph_caps_dirty(ci);
		handle_cap_grant(inode, session, cap,
				 h, msg->middle, &extra_info);
		जाओ करोne_unlocked;

	हाल CEPH_CAP_OP_FLUSH_ACK:
		handle_cap_flush_ack(inode, le64_to_cpu(msg->hdr.tid),
				     h, session, cap);
		अवरोध;

	हाल CEPH_CAP_OP_TRUNC:
		queue_trunc = handle_cap_trunc(inode, h, session);
		spin_unlock(&ci->i_ceph_lock);
		अगर (queue_trunc)
			ceph_queue_vmtruncate(inode);
		अवरोध;

	शेष:
		spin_unlock(&ci->i_ceph_lock);
		pr_err("ceph_handle_caps: unknown cap op %d %s\n", op,
		       ceph_cap_op_name(op));
	पूर्ण

करोne:
	mutex_unlock(&session->s_mutex);
करोne_unlocked:
	ceph_put_string(extra_info.pool_ns);
	/* aव्योम calling iput_final() in mds dispatch thपढ़ोs */
	ceph_async_iput(inode);
	वापस;

flush_cap_releases:
	/*
	 * send any cap release message to try to move things
	 * aदीर्घ क्रम the mds (who clearly thinks we still have this
	 * cap).
	 */
	ceph_flush_cap_releases(mdsc, session);
	जाओ करोne;

bad:
	pr_err("ceph_handle_caps: corrupt message\n");
	ceph_msg_dump(msg);
	वापस;
पूर्ण

/*
 * Delayed work handler to process end of delayed cap release LRU list.
 */
व्योम ceph_check_delayed_caps(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा inode *inode;
	काष्ठा ceph_inode_info *ci;

	करोut("check_delayed_caps\n");
	spin_lock(&mdsc->cap_delay_lock);
	जबतक (!list_empty(&mdsc->cap_delay_list)) अणु
		ci = list_first_entry(&mdsc->cap_delay_list,
				      काष्ठा ceph_inode_info,
				      i_cap_delay_list);
		अगर ((ci->i_ceph_flags & CEPH_I_FLUSH) == 0 &&
		    समय_beक्रमe(jअगरfies, ci->i_hold_caps_max))
			अवरोध;
		list_del_init(&ci->i_cap_delay_list);

		inode = igrab(&ci->vfs_inode);
		अगर (inode) अणु
			spin_unlock(&mdsc->cap_delay_lock);
			करोut("check_delayed_caps on %p\n", inode);
			ceph_check_caps(ci, 0, शून्य);
			/* aव्योम calling iput_final() in tick thपढ़ो */
			ceph_async_iput(inode);
			spin_lock(&mdsc->cap_delay_lock);
		पूर्ण
	पूर्ण
	spin_unlock(&mdsc->cap_delay_lock);
पूर्ण

/*
 * Flush all dirty caps to the mds
 */
अटल व्योम flush_dirty_session_caps(काष्ठा ceph_mds_session *s)
अणु
	काष्ठा ceph_mds_client *mdsc = s->s_mdsc;
	काष्ठा ceph_inode_info *ci;
	काष्ठा inode *inode;

	करोut("flush_dirty_caps\n");
	spin_lock(&mdsc->cap_dirty_lock);
	जबतक (!list_empty(&s->s_cap_dirty)) अणु
		ci = list_first_entry(&s->s_cap_dirty, काष्ठा ceph_inode_info,
				      i_dirty_item);
		inode = &ci->vfs_inode;
		ihold(inode);
		करोut("flush_dirty_caps %p\n", inode);
		spin_unlock(&mdsc->cap_dirty_lock);
		ceph_check_caps(ci, CHECK_CAPS_FLUSH, शून्य);
		iput(inode);
		spin_lock(&mdsc->cap_dirty_lock);
	पूर्ण
	spin_unlock(&mdsc->cap_dirty_lock);
	करोut("flush_dirty_caps done\n");
पूर्ण

अटल व्योम iterate_sessions(काष्ठा ceph_mds_client *mdsc,
			     व्योम (*cb)(काष्ठा ceph_mds_session *))
अणु
	पूर्णांक mds;

	mutex_lock(&mdsc->mutex);
	क्रम (mds = 0; mds < mdsc->max_sessions; ++mds) अणु
		काष्ठा ceph_mds_session *s;

		अगर (!mdsc->sessions[mds])
			जारी;

		s = ceph_get_mds_session(mdsc->sessions[mds]);
		अगर (!s)
			जारी;

		mutex_unlock(&mdsc->mutex);
		cb(s);
		ceph_put_mds_session(s);
		mutex_lock(&mdsc->mutex);
	पूर्ण
	mutex_unlock(&mdsc->mutex);
पूर्ण

व्योम ceph_flush_dirty_caps(काष्ठा ceph_mds_client *mdsc)
अणु
	iterate_sessions(mdsc, flush_dirty_session_caps);
पूर्ण

व्योम __ceph_touch_भ_शेषe(काष्ठा ceph_inode_info *ci,
			काष्ठा ceph_mds_client *mdsc, पूर्णांक भ_शेषe)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	अगर (भ_शेषe & CEPH_खाता_MODE_RD)
		ci->i_last_rd = now;
	अगर (भ_शेषe & CEPH_खाता_MODE_WR)
		ci->i_last_wr = now;
	/* queue periodic check */
	अगर (भ_शेषe &&
	    __ceph_is_any_real_caps(ci) &&
	    list_empty(&ci->i_cap_delay_list))
		__cap_delay_requeue(mdsc, ci);
पूर्ण

व्योम ceph_get_भ_शेषe(काष्ठा ceph_inode_info *ci, पूर्णांक भ_शेषe, पूर्णांक count)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(ci->vfs_inode.i_sb);
	पूर्णांक bits = (भ_शेषe << 1) | 1;
	bool is_खोलोed = false;
	पूर्णांक i;

	अगर (count == 1)
		atomic64_inc(&mdsc->metric.खोलोed_files);

	spin_lock(&ci->i_ceph_lock);
	क्रम (i = 0; i < CEPH_खाता_MODE_BITS; i++) अणु
		अगर (bits & (1 << i))
			ci->i_nr_by_mode[i] += count;

		/*
		 * If any of the mode ref is larger than 1,
		 * that means it has been alपढ़ोy खोलोed by
		 * others. Just skip checking the PIN ref.
		 */
		अगर (i && ci->i_nr_by_mode[i] > 1)
			is_खोलोed = true;
	पूर्ण

	अगर (!is_खोलोed)
		percpu_counter_inc(&mdsc->metric.खोलोed_inodes);
	spin_unlock(&ci->i_ceph_lock);
पूर्ण

/*
 * Drop खोलो file reference.  If we were the last खोलो file,
 * we may need to release capabilities to the MDS (or schedule
 * their delayed release).
 */
व्योम ceph_put_भ_शेषe(काष्ठा ceph_inode_info *ci, पूर्णांक भ_शेषe, पूर्णांक count)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(ci->vfs_inode.i_sb);
	पूर्णांक bits = (भ_शेषe << 1) | 1;
	bool is_बंदd = true;
	पूर्णांक i;

	अगर (count == 1)
		atomic64_dec(&mdsc->metric.खोलोed_files);

	spin_lock(&ci->i_ceph_lock);
	क्रम (i = 0; i < CEPH_खाता_MODE_BITS; i++) अणु
		अगर (bits & (1 << i)) अणु
			BUG_ON(ci->i_nr_by_mode[i] < count);
			ci->i_nr_by_mode[i] -= count;
		पूर्ण

		/*
		 * If any of the mode ref is not 0 after
		 * decreased, that means it is still खोलोed
		 * by others. Just skip checking the PIN ref.
		 */
		अगर (i && ci->i_nr_by_mode[i])
			is_बंदd = false;
	पूर्ण

	अगर (is_बंदd)
		percpu_counter_dec(&mdsc->metric.खोलोed_inodes);
	spin_unlock(&ci->i_ceph_lock);
पूर्ण

/*
 * For a soon-to-be unlinked file, drop the LINK caps. If it
 * looks like the link count will hit 0, drop any other caps (other
 * than PIN) we करोn't specअगरically want (due to the file still being
 * खोलो).
 */
पूर्णांक ceph_drop_caps_क्रम_unlink(काष्ठा inode *inode)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक drop = CEPH_CAP_LINK_SHARED | CEPH_CAP_LINK_EXCL;

	spin_lock(&ci->i_ceph_lock);
	अगर (inode->i_nlink == 1) अणु
		drop |= ~(__ceph_caps_wanted(ci) | CEPH_CAP_PIN);

		अगर (__ceph_caps_dirty(ci)) अणु
			काष्ठा ceph_mds_client *mdsc =
				ceph_inode_to_client(inode)->mdsc;
			__cap_delay_requeue_front(mdsc, ci);
		पूर्ण
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);
	वापस drop;
पूर्ण

/*
 * Helpers क्रम embedding cap and dentry lease releases पूर्णांकo mds
 * requests.
 *
 * @क्रमce is used by dentry_release (below) to क्रमce inclusion of a
 * record क्रम the directory inode, even when there aren't any caps to
 * drop.
 */
पूर्णांक ceph_encode_inode_release(व्योम **p, काष्ठा inode *inode,
			      पूर्णांक mds, पूर्णांक drop, पूर्णांक unless, पूर्णांक क्रमce)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_cap *cap;
	काष्ठा ceph_mds_request_release *rel = *p;
	पूर्णांक used, dirty;
	पूर्णांक ret = 0;

	spin_lock(&ci->i_ceph_lock);
	used = __ceph_caps_used(ci);
	dirty = __ceph_caps_dirty(ci);

	करोut("encode_inode_release %p mds%d used|dirty %s drop %s unless %s\n",
	     inode, mds, ceph_cap_string(used|dirty), ceph_cap_string(drop),
	     ceph_cap_string(unless));

	/* only drop unused, clean caps */
	drop &= ~(used | dirty);

	cap = __get_cap_क्रम_mds(ci, mds);
	अगर (cap && __cap_is_valid(cap)) अणु
		unless &= cap->issued;
		अगर (unless) अणु
			अगर (unless & CEPH_CAP_AUTH_EXCL)
				drop &= ~CEPH_CAP_AUTH_SHARED;
			अगर (unless & CEPH_CAP_LINK_EXCL)
				drop &= ~CEPH_CAP_LINK_SHARED;
			अगर (unless & CEPH_CAP_XATTR_EXCL)
				drop &= ~CEPH_CAP_XATTR_SHARED;
			अगर (unless & CEPH_CAP_खाता_EXCL)
				drop &= ~CEPH_CAP_खाता_SHARED;
		पूर्ण

		अगर (क्रमce || (cap->issued & drop)) अणु
			अगर (cap->issued & drop) अणु
				पूर्णांक wanted = __ceph_caps_wanted(ci);
				करोut("encode_inode_release %p cap %p "
				     "%s -> %s, wanted %s -> %s\n", inode, cap,
				     ceph_cap_string(cap->issued),
				     ceph_cap_string(cap->issued & ~drop),
				     ceph_cap_string(cap->mds_wanted),
				     ceph_cap_string(wanted));

				cap->issued &= ~drop;
				cap->implemented &= ~drop;
				cap->mds_wanted = wanted;
				अगर (cap == ci->i_auth_cap &&
				    !(wanted & CEPH_CAP_ANY_खाता_WR))
					ci->i_requested_max_size = 0;
			पूर्ण अन्यथा अणु
				करोut("encode_inode_release %p cap %p %s"
				     " (force)\n", inode, cap,
				     ceph_cap_string(cap->issued));
			पूर्ण

			rel->ino = cpu_to_le64(ceph_ino(inode));
			rel->cap_id = cpu_to_le64(cap->cap_id);
			rel->seq = cpu_to_le32(cap->seq);
			rel->issue_seq = cpu_to_le32(cap->issue_seq);
			rel->mseq = cpu_to_le32(cap->mseq);
			rel->caps = cpu_to_le32(cap->implemented);
			rel->wanted = cpu_to_le32(cap->mds_wanted);
			rel->dname_len = 0;
			rel->dname_seq = 0;
			*p += माप(*rel);
			ret = 1;
		पूर्ण अन्यथा अणु
			करोut("encode_inode_release %p cap %p %s (noop)\n",
			     inode, cap, ceph_cap_string(cap->issued));
		पूर्ण
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);
	वापस ret;
पूर्ण

पूर्णांक ceph_encode_dentry_release(व्योम **p, काष्ठा dentry *dentry,
			       काष्ठा inode *dir,
			       पूर्णांक mds, पूर्णांक drop, पूर्णांक unless)
अणु
	काष्ठा dentry *parent = शून्य;
	काष्ठा ceph_mds_request_release *rel = *p;
	काष्ठा ceph_dentry_info *di = ceph_dentry(dentry);
	पूर्णांक क्रमce = 0;
	पूर्णांक ret;

	/*
	 * क्रमce an record क्रम the directory caps अगर we have a dentry lease.
	 * this is racy (can't take i_ceph_lock and d_lock together), but it
	 * करोesn't have to be perfect; the mds will revoke anything we don't
	 * release.
	 */
	spin_lock(&dentry->d_lock);
	अगर (di->lease_session && di->lease_session->s_mds == mds)
		क्रमce = 1;
	अगर (!dir) अणु
		parent = dget(dentry->d_parent);
		dir = d_inode(parent);
	पूर्ण
	spin_unlock(&dentry->d_lock);

	ret = ceph_encode_inode_release(p, dir, mds, drop, unless, क्रमce);
	dput(parent);

	spin_lock(&dentry->d_lock);
	अगर (ret && di->lease_session && di->lease_session->s_mds == mds) अणु
		करोut("encode_dentry_release %p mds%d seq %d\n",
		     dentry, mds, (पूर्णांक)di->lease_seq);
		rel->dname_len = cpu_to_le32(dentry->d_name.len);
		स_नकल(*p, dentry->d_name.name, dentry->d_name.len);
		*p += dentry->d_name.len;
		rel->dname_seq = cpu_to_le32(di->lease_seq);
		__ceph_mdsc_drop_dentry_lease(dentry);
	पूर्ण
	spin_unlock(&dentry->d_lock);
	वापस ret;
पूर्ण
