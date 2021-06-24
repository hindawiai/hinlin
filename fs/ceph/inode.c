<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/xattr.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sort.h>
#समावेश <linux/iversion.h>

#समावेश "super.h"
#समावेश "mds_client.h"
#समावेश "cache.h"
#समावेश <linux/ceph/decode.h>

/*
 * Ceph inode operations
 *
 * Implement basic inode helpers (get, alloc) and inode ops (getattr,
 * setattr, etc.), xattr helpers, and helpers क्रम assimilating
 * metadata वापसed by the MDS पूर्णांकo our cache.
 *
 * Also define helpers क्रम करोing asynchronous ग_लिखोback, invalidation,
 * and truncation क्रम the benefit of those who can't afक्रमd to block
 * (typically because they are in the message handler path).
 */

अटल स्थिर काष्ठा inode_operations ceph_symlink_iops;

अटल व्योम ceph_inode_work(काष्ठा work_काष्ठा *work);

/*
 * find or create an inode, given the ceph ino number
 */
अटल पूर्णांक ceph_set_ino_cb(काष्ठा inode *inode, व्योम *data)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(inode->i_sb);

	ci->i_vino = *(काष्ठा ceph_vino *)data;
	inode->i_ino = ceph_vino_to_ino_t(ci->i_vino);
	inode_set_iversion_raw(inode, 0);
	percpu_counter_inc(&mdsc->metric.total_inodes);

	वापस 0;
पूर्ण

काष्ठा inode *ceph_get_inode(काष्ठा super_block *sb, काष्ठा ceph_vino vino)
अणु
	काष्ठा inode *inode;

	अगर (ceph_vino_is_reserved(vino))
		वापस ERR_PTR(-EREMOTEIO);

	inode = iget5_locked(sb, (अचिन्हित दीर्घ)vino.ino, ceph_ino_compare,
			     ceph_set_ino_cb, &vino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	करोut("get_inode on %llu=%llx.%llx got %p new %d\n", ceph_present_inode(inode),
	     ceph_vinop(inode), inode, !!(inode->i_state & I_NEW));
	वापस inode;
पूर्ण

/*
 * get/स्थिरuct snapdir inode क्रम a given directory
 */
काष्ठा inode *ceph_get_snapdir(काष्ठा inode *parent)
अणु
	काष्ठा ceph_vino vino = अणु
		.ino = ceph_ino(parent),
		.snap = CEPH_SNAPसूची,
	पूर्ण;
	काष्ठा inode *inode = ceph_get_inode(parent->i_sb, vino);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);

	अगर (IS_ERR(inode))
		वापस inode;

	अगर (!S_ISसूची(parent->i_mode)) अणु
		pr_warn_once("bad snapdir parent type (mode=0%o)\n",
			     parent->i_mode);
		वापस ERR_PTR(-ENOTसूची);
	पूर्ण

	अगर (!(inode->i_state & I_NEW) && !S_ISसूची(inode->i_mode)) अणु
		pr_warn_once("bad snapdir inode type (mode=0%o)\n",
			     inode->i_mode);
		वापस ERR_PTR(-ENOTसूची);
	पूर्ण

	inode->i_mode = parent->i_mode;
	inode->i_uid = parent->i_uid;
	inode->i_gid = parent->i_gid;
	inode->i_mसमय = parent->i_mसमय;
	inode->i_स_समय = parent->i_स_समय;
	inode->i_aसमय = parent->i_aसमय;
	ci->i_rbytes = 0;
	ci->i_bसमय = ceph_inode(parent)->i_bसमय;

	अगर (inode->i_state & I_NEW) अणु
		inode->i_op = &ceph_snapdir_iops;
		inode->i_fop = &ceph_snapdir_fops;
		ci->i_snap_caps = CEPH_CAP_PIN; /* so we can खोलो */
		unlock_new_inode(inode);
	पूर्ण

	वापस inode;
पूर्ण

स्थिर काष्ठा inode_operations ceph_file_iops = अणु
	.permission = ceph_permission,
	.setattr = ceph_setattr,
	.getattr = ceph_getattr,
	.listxattr = ceph_listxattr,
	.get_acl = ceph_get_acl,
	.set_acl = ceph_set_acl,
पूर्ण;


/*
 * We use a 'frag tree' to keep track of the MDS's directory fragments
 * क्रम a given inode (usually there is just a single fragment).  We
 * need to know when a child frag is delegated to a new MDS, or when
 * it is flagged as replicated, so we can direct our requests
 * accordingly.
 */

/*
 * find/create a frag in the tree
 */
अटल काष्ठा ceph_inode_frag *__get_or_create_frag(काष्ठा ceph_inode_info *ci,
						    u32 f)
अणु
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा ceph_inode_frag *frag;
	पूर्णांक c;

	p = &ci->i_fragtree.rb_node;
	जबतक (*p) अणु
		parent = *p;
		frag = rb_entry(parent, काष्ठा ceph_inode_frag, node);
		c = ceph_frag_compare(f, frag->frag);
		अगर (c < 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (c > 0)
			p = &(*p)->rb_right;
		अन्यथा
			वापस frag;
	पूर्ण

	frag = kदो_स्मृति(माप(*frag), GFP_NOFS);
	अगर (!frag)
		वापस ERR_PTR(-ENOMEM);

	frag->frag = f;
	frag->split_by = 0;
	frag->mds = -1;
	frag->ndist = 0;

	rb_link_node(&frag->node, parent, p);
	rb_insert_color(&frag->node, &ci->i_fragtree);

	करोut("get_or_create_frag added %llx.%llx frag %x\n",
	     ceph_vinop(&ci->vfs_inode), f);
	वापस frag;
पूर्ण

/*
 * find a specअगरic frag @f
 */
काष्ठा ceph_inode_frag *__ceph_find_frag(काष्ठा ceph_inode_info *ci, u32 f)
अणु
	काष्ठा rb_node *n = ci->i_fragtree.rb_node;

	जबतक (n) अणु
		काष्ठा ceph_inode_frag *frag =
			rb_entry(n, काष्ठा ceph_inode_frag, node);
		पूर्णांक c = ceph_frag_compare(f, frag->frag);
		अगर (c < 0)
			n = n->rb_left;
		अन्यथा अगर (c > 0)
			n = n->rb_right;
		अन्यथा
			वापस frag;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Choose frag containing the given value @v.  If @pfrag is
 * specअगरied, copy the frag delegation info to the caller अगर
 * it is present.
 */
अटल u32 __ceph_choose_frag(काष्ठा ceph_inode_info *ci, u32 v,
			      काष्ठा ceph_inode_frag *pfrag, पूर्णांक *found)
अणु
	u32 t = ceph_frag_make(0, 0);
	काष्ठा ceph_inode_frag *frag;
	अचिन्हित nway, i;
	u32 n;

	अगर (found)
		*found = 0;

	जबतक (1) अणु
		WARN_ON(!ceph_frag_contains_value(t, v));
		frag = __ceph_find_frag(ci, t);
		अगर (!frag)
			अवरोध; /* t is a leaf */
		अगर (frag->split_by == 0) अणु
			अगर (pfrag)
				स_नकल(pfrag, frag, माप(*pfrag));
			अगर (found)
				*found = 1;
			अवरोध;
		पूर्ण

		/* choose child */
		nway = 1 << frag->split_by;
		करोut("choose_frag(%x) %x splits by %d (%d ways)\n", v, t,
		     frag->split_by, nway);
		क्रम (i = 0; i < nway; i++) अणु
			n = ceph_frag_make_child(t, frag->split_by, i);
			अगर (ceph_frag_contains_value(n, v)) अणु
				t = n;
				अवरोध;
			पूर्ण
		पूर्ण
		BUG_ON(i == nway);
	पूर्ण
	करोut("choose_frag(%x) = %x\n", v, t);

	वापस t;
पूर्ण

u32 ceph_choose_frag(काष्ठा ceph_inode_info *ci, u32 v,
		     काष्ठा ceph_inode_frag *pfrag, पूर्णांक *found)
अणु
	u32 ret;
	mutex_lock(&ci->i_fragtree_mutex);
	ret = __ceph_choose_frag(ci, v, pfrag, found);
	mutex_unlock(&ci->i_fragtree_mutex);
	वापस ret;
पूर्ण

/*
 * Process dirfrag (delegation) info from the mds.  Include leaf
 * fragment in tree ONLY अगर ndist > 0.  Otherwise, only
 * branches/splits are included in i_fragtree)
 */
अटल पूर्णांक ceph_fill_dirfrag(काष्ठा inode *inode,
			     काष्ठा ceph_mds_reply_dirfrag *dirinfo)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_inode_frag *frag;
	u32 id = le32_to_cpu(dirinfo->frag);
	पूर्णांक mds = le32_to_cpu(dirinfo->auth);
	पूर्णांक ndist = le32_to_cpu(dirinfo->ndist);
	पूर्णांक diri_auth = -1;
	पूर्णांक i;
	पूर्णांक err = 0;

	spin_lock(&ci->i_ceph_lock);
	अगर (ci->i_auth_cap)
		diri_auth = ci->i_auth_cap->mds;
	spin_unlock(&ci->i_ceph_lock);

	अगर (mds == -1) /* Cसूची_AUTH_PARENT */
		mds = diri_auth;

	mutex_lock(&ci->i_fragtree_mutex);
	अगर (ndist == 0 && mds == diri_auth) अणु
		/* no delegation info needed. */
		frag = __ceph_find_frag(ci, id);
		अगर (!frag)
			जाओ out;
		अगर (frag->split_by == 0) अणु
			/* tree leaf, हटाओ */
			करोut("fill_dirfrag removed %llx.%llx frag %x"
			     " (no ref)\n", ceph_vinop(inode), id);
			rb_erase(&frag->node, &ci->i_fragtree);
			kमुक्त(frag);
		पूर्ण अन्यथा अणु
			/* tree branch, keep and clear */
			करोut("fill_dirfrag cleared %llx.%llx frag %x"
			     " referral\n", ceph_vinop(inode), id);
			frag->mds = -1;
			frag->ndist = 0;
		पूर्ण
		जाओ out;
	पूर्ण


	/* find/add this frag to store mds delegation info */
	frag = __get_or_create_frag(ci, id);
	अगर (IS_ERR(frag)) अणु
		/* this is not the end of the world; we can जारी
		   with bad/inaccurate delegation info */
		pr_err("fill_dirfrag ENOMEM on mds ref %llx.%llx fg %x\n",
		       ceph_vinop(inode), le32_to_cpu(dirinfo->frag));
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	frag->mds = mds;
	frag->ndist = min_t(u32, ndist, CEPH_MAX_सूचीFRAG_REP);
	क्रम (i = 0; i < frag->ndist; i++)
		frag->dist[i] = le32_to_cpu(dirinfo->dist[i]);
	करोut("fill_dirfrag %llx.%llx frag %x ndist=%d\n",
	     ceph_vinop(inode), frag->frag, frag->ndist);

out:
	mutex_unlock(&ci->i_fragtree_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक frag_tree_split_cmp(स्थिर व्योम *l, स्थिर व्योम *r)
अणु
	काष्ठा ceph_frag_tree_split *ls = (काष्ठा ceph_frag_tree_split*)l;
	काष्ठा ceph_frag_tree_split *rs = (काष्ठा ceph_frag_tree_split*)r;
	वापस ceph_frag_compare(le32_to_cpu(ls->frag),
				 le32_to_cpu(rs->frag));
पूर्ण

अटल bool is_frag_child(u32 f, काष्ठा ceph_inode_frag *frag)
अणु
	अगर (!frag)
		वापस f == ceph_frag_make(0, 0);
	अगर (ceph_frag_bits(f) != ceph_frag_bits(frag->frag) + frag->split_by)
		वापस false;
	वापस ceph_frag_contains_value(frag->frag, ceph_frag_value(f));
पूर्ण

अटल पूर्णांक ceph_fill_fragtree(काष्ठा inode *inode,
			      काष्ठा ceph_frag_tree_head *fragtree,
			      काष्ठा ceph_mds_reply_dirfrag *dirinfo)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_inode_frag *frag, *prev_frag = शून्य;
	काष्ठा rb_node *rb_node;
	अचिन्हित i, split_by, nsplits;
	u32 id;
	bool update = false;

	mutex_lock(&ci->i_fragtree_mutex);
	nsplits = le32_to_cpu(fragtree->nsplits);
	अगर (nsplits != ci->i_fragtree_nsplits) अणु
		update = true;
	पूर्ण अन्यथा अगर (nsplits) अणु
		i = pअक्रमom_u32() % nsplits;
		id = le32_to_cpu(fragtree->splits[i].frag);
		अगर (!__ceph_find_frag(ci, id))
			update = true;
	पूर्ण अन्यथा अगर (!RB_EMPTY_ROOT(&ci->i_fragtree)) अणु
		rb_node = rb_first(&ci->i_fragtree);
		frag = rb_entry(rb_node, काष्ठा ceph_inode_frag, node);
		अगर (frag->frag != ceph_frag_make(0, 0) || rb_next(rb_node))
			update = true;
	पूर्ण
	अगर (!update && dirinfo) अणु
		id = le32_to_cpu(dirinfo->frag);
		अगर (id != __ceph_choose_frag(ci, id, शून्य, शून्य))
			update = true;
	पूर्ण
	अगर (!update)
		जाओ out_unlock;

	अगर (nsplits > 1) अणु
		sort(fragtree->splits, nsplits, माप(fragtree->splits[0]),
		     frag_tree_split_cmp, शून्य);
	पूर्ण

	करोut("fill_fragtree %llx.%llx\n", ceph_vinop(inode));
	rb_node = rb_first(&ci->i_fragtree);
	क्रम (i = 0; i < nsplits; i++) अणु
		id = le32_to_cpu(fragtree->splits[i].frag);
		split_by = le32_to_cpu(fragtree->splits[i].by);
		अगर (split_by == 0 || ceph_frag_bits(id) + split_by > 24) अणु
			pr_err("fill_fragtree %llx.%llx invalid split %d/%u, "
			       "frag %x split by %d\n", ceph_vinop(inode),
			       i, nsplits, id, split_by);
			जारी;
		पूर्ण
		frag = शून्य;
		जबतक (rb_node) अणु
			frag = rb_entry(rb_node, काष्ठा ceph_inode_frag, node);
			अगर (ceph_frag_compare(frag->frag, id) >= 0) अणु
				अगर (frag->frag != id)
					frag = शून्य;
				अन्यथा
					rb_node = rb_next(rb_node);
				अवरोध;
			पूर्ण
			rb_node = rb_next(rb_node);
			/* delete stale split/leaf node */
			अगर (frag->split_by > 0 ||
			    !is_frag_child(frag->frag, prev_frag)) अणु
				rb_erase(&frag->node, &ci->i_fragtree);
				अगर (frag->split_by > 0)
					ci->i_fragtree_nsplits--;
				kमुक्त(frag);
			पूर्ण
			frag = शून्य;
		पूर्ण
		अगर (!frag) अणु
			frag = __get_or_create_frag(ci, id);
			अगर (IS_ERR(frag))
				जारी;
		पूर्ण
		अगर (frag->split_by == 0)
			ci->i_fragtree_nsplits++;
		frag->split_by = split_by;
		करोut(" frag %x split by %d\n", frag->frag, frag->split_by);
		prev_frag = frag;
	पूर्ण
	जबतक (rb_node) अणु
		frag = rb_entry(rb_node, काष्ठा ceph_inode_frag, node);
		rb_node = rb_next(rb_node);
		/* delete stale split/leaf node */
		अगर (frag->split_by > 0 ||
		    !is_frag_child(frag->frag, prev_frag)) अणु
			rb_erase(&frag->node, &ci->i_fragtree);
			अगर (frag->split_by > 0)
				ci->i_fragtree_nsplits--;
			kमुक्त(frag);
		पूर्ण
	पूर्ण
out_unlock:
	mutex_unlock(&ci->i_fragtree_mutex);
	वापस 0;
पूर्ण

/*
 * initialize a newly allocated inode.
 */
काष्ठा inode *ceph_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा ceph_inode_info *ci;
	पूर्णांक i;

	ci = kmem_cache_alloc(ceph_inode_cachep, GFP_NOFS);
	अगर (!ci)
		वापस शून्य;

	करोut("alloc_inode %p\n", &ci->vfs_inode);

	spin_lock_init(&ci->i_ceph_lock);

	ci->i_version = 0;
	ci->i_अंतरभूत_version = 0;
	ci->i_समय_warp_seq = 0;
	ci->i_ceph_flags = 0;
	atomic64_set(&ci->i_ordered_count, 1);
	atomic64_set(&ci->i_release_count, 1);
	atomic64_set(&ci->i_complete_seq[0], 0);
	atomic64_set(&ci->i_complete_seq[1], 0);
	ci->i_symlink = शून्य;

	ci->i_max_bytes = 0;
	ci->i_max_files = 0;

	स_रखो(&ci->i_dir_layout, 0, माप(ci->i_dir_layout));
	स_रखो(&ci->i_cached_layout, 0, माप(ci->i_cached_layout));
	RCU_INIT_POINTER(ci->i_layout.pool_ns, शून्य);

	ci->i_fragtree = RB_ROOT;
	mutex_init(&ci->i_fragtree_mutex);

	ci->i_xattrs.blob = शून्य;
	ci->i_xattrs.pपुनः_स्मृति_blob = शून्य;
	ci->i_xattrs.dirty = false;
	ci->i_xattrs.index = RB_ROOT;
	ci->i_xattrs.count = 0;
	ci->i_xattrs.names_size = 0;
	ci->i_xattrs.vals_size = 0;
	ci->i_xattrs.version = 0;
	ci->i_xattrs.index_version = 0;

	ci->i_caps = RB_ROOT;
	ci->i_auth_cap = शून्य;
	ci->i_dirty_caps = 0;
	ci->i_flushing_caps = 0;
	INIT_LIST_HEAD(&ci->i_dirty_item);
	INIT_LIST_HEAD(&ci->i_flushing_item);
	ci->i_pपुनः_स्मृति_cap_flush = शून्य;
	INIT_LIST_HEAD(&ci->i_cap_flush_list);
	init_रुकोqueue_head(&ci->i_cap_wq);
	ci->i_hold_caps_max = 0;
	INIT_LIST_HEAD(&ci->i_cap_delay_list);
	INIT_LIST_HEAD(&ci->i_cap_snaps);
	ci->i_head_snapc = शून्य;
	ci->i_snap_caps = 0;

	ci->i_last_rd = ci->i_last_wr = jअगरfies - 3600 * HZ;
	क्रम (i = 0; i < CEPH_खाता_MODE_BITS; i++)
		ci->i_nr_by_mode[i] = 0;

	mutex_init(&ci->i_truncate_mutex);
	ci->i_truncate_seq = 0;
	ci->i_truncate_size = 0;
	ci->i_truncate_pending = 0;

	ci->i_max_size = 0;
	ci->i_reported_size = 0;
	ci->i_wanted_max_size = 0;
	ci->i_requested_max_size = 0;

	ci->i_pin_ref = 0;
	ci->i_rd_ref = 0;
	ci->i_rdcache_ref = 0;
	ci->i_wr_ref = 0;
	ci->i_wb_ref = 0;
	ci->i_fx_ref = 0;
	ci->i_wrbuffer_ref = 0;
	ci->i_wrbuffer_ref_head = 0;
	atomic_set(&ci->i_filelock_ref, 0);
	atomic_set(&ci->i_shared_gen, 1);
	ci->i_rdcache_gen = 0;
	ci->i_rdcache_revoking = 0;

	INIT_LIST_HEAD(&ci->i_unsafe_dirops);
	INIT_LIST_HEAD(&ci->i_unsafe_iops);
	spin_lock_init(&ci->i_unsafe_lock);

	ci->i_snap_realm = शून्य;
	INIT_LIST_HEAD(&ci->i_snap_realm_item);
	INIT_LIST_HEAD(&ci->i_snap_flush_item);

	INIT_WORK(&ci->i_work, ceph_inode_work);
	ci->i_work_mask = 0;
	स_रखो(&ci->i_bसमय, '\0', माप(ci->i_bसमय));

	ceph_fscache_inode_init(ci);

	ci->i_meta_err = 0;

	वापस &ci->vfs_inode;
पूर्ण

व्योम ceph_मुक्त_inode(काष्ठा inode *inode)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);

	kमुक्त(ci->i_symlink);
	kmem_cache_मुक्त(ceph_inode_cachep, ci);
पूर्ण

व्योम ceph_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(inode->i_sb);
	काष्ठा ceph_inode_frag *frag;
	काष्ठा rb_node *n;

	करोut("evict_inode %p ino %llx.%llx\n", inode, ceph_vinop(inode));

	percpu_counter_dec(&mdsc->metric.total_inodes);

	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);

	ceph_fscache_unरेजिस्टर_inode_cookie(ci);

	__ceph_हटाओ_caps(ci);

	अगर (__ceph_has_any_quota(ci))
		ceph_adjust_quota_realms_count(inode, false);

	/*
	 * we may still have a snap_realm reference अगर there are stray
	 * caps in i_snap_caps.
	 */
	अगर (ci->i_snap_realm) अणु
		अगर (ceph_snap(inode) == CEPH_NOSNAP) अणु
			काष्ठा ceph_snap_realm *realm = ci->i_snap_realm;
			करोut(" dropping residual ref to snap realm %p\n",
			     realm);
			spin_lock(&realm->inodes_with_caps_lock);
			list_del_init(&ci->i_snap_realm_item);
			ci->i_snap_realm = शून्य;
			अगर (realm->ino == ci->i_vino.ino)
				realm->inode = शून्य;
			spin_unlock(&realm->inodes_with_caps_lock);
			ceph_put_snap_realm(mdsc, realm);
		पूर्ण अन्यथा अणु
			ceph_put_snapid_map(mdsc, ci->i_snapid_map);
			ci->i_snap_realm = शून्य;
		पूर्ण
	पूर्ण

	जबतक ((n = rb_first(&ci->i_fragtree)) != शून्य) अणु
		frag = rb_entry(n, काष्ठा ceph_inode_frag, node);
		rb_erase(n, &ci->i_fragtree);
		kमुक्त(frag);
	पूर्ण
	ci->i_fragtree_nsplits = 0;

	__ceph_destroy_xattrs(ci);
	अगर (ci->i_xattrs.blob)
		ceph_buffer_put(ci->i_xattrs.blob);
	अगर (ci->i_xattrs.pपुनः_स्मृति_blob)
		ceph_buffer_put(ci->i_xattrs.pपुनः_स्मृति_blob);

	ceph_put_string(rcu_dereference_raw(ci->i_layout.pool_ns));
	ceph_put_string(rcu_dereference_raw(ci->i_cached_layout.pool_ns));
पूर्ण

अटल अंतरभूत blkcnt_t calc_inode_blocks(u64 size)
अणु
	वापस (size + (1<<9) - 1) >> 9;
पूर्ण

/*
 * Helpers to fill in size, स_समय, mसमय, and aसमय.  We have to be
 * careful because either the client or MDS may have more up to date
 * info, depending on which capabilities are held, and whether
 * समय_warp_seq or truncate_seq have increased.  (Ordinarily, mसमय
 * and size are monotonically increasing, except when uबार() or
 * truncate() increments the corresponding _seq values.)
 */
पूर्णांक ceph_fill_file_size(काष्ठा inode *inode, पूर्णांक issued,
			u32 truncate_seq, u64 truncate_size, u64 size)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक queue_trunc = 0;
	loff_t isize = i_size_पढ़ो(inode);

	अगर (ceph_seq_cmp(truncate_seq, ci->i_truncate_seq) > 0 ||
	    (truncate_seq == ci->i_truncate_seq && size > isize)) अणु
		करोut("size %lld -> %llu\n", isize, size);
		अगर (size > 0 && S_ISसूची(inode->i_mode)) अणु
			pr_err("fill_file_size non-zero size for directory\n");
			size = 0;
		पूर्ण
		i_size_ग_लिखो(inode, size);
		inode->i_blocks = calc_inode_blocks(size);
		ci->i_reported_size = size;
		अगर (truncate_seq != ci->i_truncate_seq) अणु
			करोut("truncate_seq %u -> %u\n",
			     ci->i_truncate_seq, truncate_seq);
			ci->i_truncate_seq = truncate_seq;

			/* the MDS should have revoked these caps */
			WARN_ON_ONCE(issued & (CEPH_CAP_खाता_EXCL |
					       CEPH_CAP_खाता_RD |
					       CEPH_CAP_खाता_WR |
					       CEPH_CAP_खाता_LAZYIO));
			/*
			 * If we hold relevant caps, or in the हाल where we're
			 * not the only client referencing this file and we
			 * करोn't hold those caps, then we need to check whether
			 * the file is either खोलोed or mmaped
			 */
			अगर ((issued & (CEPH_CAP_खाता_CACHE|
				       CEPH_CAP_खाता_BUFFER)) ||
			    mapping_mapped(inode->i_mapping) ||
			    __ceph_is_file_खोलोed(ci)) अणु
				ci->i_truncate_pending++;
				queue_trunc = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (ceph_seq_cmp(truncate_seq, ci->i_truncate_seq) >= 0 &&
	    ci->i_truncate_size != truncate_size) अणु
		करोut("truncate_size %lld -> %llu\n", ci->i_truncate_size,
		     truncate_size);
		ci->i_truncate_size = truncate_size;
	पूर्ण

	अगर (queue_trunc)
		ceph_fscache_invalidate(inode);

	वापस queue_trunc;
पूर्ण

व्योम ceph_fill_file_समय(काष्ठा inode *inode, पूर्णांक issued,
			 u64 समय_warp_seq, काष्ठा बारpec64 *स_समय,
			 काष्ठा बारpec64 *mसमय, काष्ठा बारpec64 *aसमय)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक warn = 0;

	अगर (issued & (CEPH_CAP_खाता_EXCL|
		      CEPH_CAP_खाता_WR|
		      CEPH_CAP_खाता_BUFFER|
		      CEPH_CAP_AUTH_EXCL|
		      CEPH_CAP_XATTR_EXCL)) अणु
		अगर (ci->i_version == 0 ||
		    बारpec64_compare(स_समय, &inode->i_स_समय) > 0) अणु
			करोut("ctime %lld.%09ld -> %lld.%09ld inc w/ cap\n",
			     inode->i_स_समय.tv_sec, inode->i_स_समय.tv_nsec,
			     स_समय->tv_sec, स_समय->tv_nsec);
			inode->i_स_समय = *स_समय;
		पूर्ण
		अगर (ci->i_version == 0 ||
		    ceph_seq_cmp(समय_warp_seq, ci->i_समय_warp_seq) > 0) अणु
			/* the MDS did a uबार() */
			करोut("mtime %lld.%09ld -> %lld.%09ld "
			     "tw %d -> %d\n",
			     inode->i_mसमय.tv_sec, inode->i_mसमय.tv_nsec,
			     mसमय->tv_sec, mसमय->tv_nsec,
			     ci->i_समय_warp_seq, (पूर्णांक)समय_warp_seq);

			inode->i_mसमय = *mसमय;
			inode->i_aसमय = *aसमय;
			ci->i_समय_warp_seq = समय_warp_seq;
		पूर्ण अन्यथा अगर (समय_warp_seq == ci->i_समय_warp_seq) अणु
			/* nobody did uबार(); take the max */
			अगर (बारpec64_compare(mसमय, &inode->i_mसमय) > 0) अणु
				करोut("mtime %lld.%09ld -> %lld.%09ld inc\n",
				     inode->i_mसमय.tv_sec,
				     inode->i_mसमय.tv_nsec,
				     mसमय->tv_sec, mसमय->tv_nsec);
				inode->i_mसमय = *mसमय;
			पूर्ण
			अगर (बारpec64_compare(aसमय, &inode->i_aसमय) > 0) अणु
				करोut("atime %lld.%09ld -> %lld.%09ld inc\n",
				     inode->i_aसमय.tv_sec,
				     inode->i_aसमय.tv_nsec,
				     aसमय->tv_sec, aसमय->tv_nsec);
				inode->i_aसमय = *aसमय;
			पूर्ण
		पूर्ण अन्यथा अगर (issued & CEPH_CAP_खाता_EXCL) अणु
			/* we did a uबार(); ignore mds values */
		पूर्ण अन्यथा अणु
			warn = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* we have no ग_लिखो|excl caps; whatever the MDS says is true */
		अगर (ceph_seq_cmp(समय_warp_seq, ci->i_समय_warp_seq) >= 0) अणु
			inode->i_स_समय = *स_समय;
			inode->i_mसमय = *mसमय;
			inode->i_aसमय = *aसमय;
			ci->i_समय_warp_seq = समय_warp_seq;
		पूर्ण अन्यथा अणु
			warn = 1;
		पूर्ण
	पूर्ण
	अगर (warn) /* समय_warp_seq shouldn't go backwards */
		करोut("%p mds time_warp_seq %llu < %u\n",
		     inode, समय_warp_seq, ci->i_समय_warp_seq);
पूर्ण

/*
 * Populate an inode based on info from mds.  May be called on new or
 * existing inodes.
 */
पूर्णांक ceph_fill_inode(काष्ठा inode *inode, काष्ठा page *locked_page,
		    काष्ठा ceph_mds_reply_info_in *iinfo,
		    काष्ठा ceph_mds_reply_dirfrag *dirinfo,
		    काष्ठा ceph_mds_session *session, पूर्णांक cap_भ_शेषe,
		    काष्ठा ceph_cap_reservation *caps_reservation)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(inode->i_sb);
	काष्ठा ceph_mds_reply_inode *info = iinfo->in;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक issued, new_issued, info_caps;
	काष्ठा बारpec64 mसमय, aसमय, स_समय;
	काष्ठा ceph_buffer *xattr_blob = शून्य;
	काष्ठा ceph_buffer *old_blob = शून्य;
	काष्ठा ceph_string *pool_ns = शून्य;
	काष्ठा ceph_cap *new_cap = शून्य;
	पूर्णांक err = 0;
	bool wake = false;
	bool queue_trunc = false;
	bool new_version = false;
	bool fill_अंतरभूत = false;
	umode_t mode = le32_to_cpu(info->mode);
	dev_t rdev = le32_to_cpu(info->rdev);

	करोut("%s %p ino %llx.%llx v %llu had %llu\n", __func__,
	     inode, ceph_vinop(inode), le64_to_cpu(info->version),
	     ci->i_version);

	/* Once I_NEW is cleared, we can't change type or dev numbers */
	अगर (inode->i_state & I_NEW) अणु
		inode->i_mode = mode;
	पूर्ण अन्यथा अणु
		अगर (inode_wrong_type(inode, mode)) अणु
			pr_warn_once("inode type changed! (ino %llx.%llx is 0%o, mds says 0%o)\n",
				     ceph_vinop(inode), inode->i_mode, mode);
			वापस -ESTALE;
		पूर्ण

		अगर ((S_ISCHR(mode) || S_ISBLK(mode)) && inode->i_rdev != rdev) अणु
			pr_warn_once("dev inode rdev changed! (ino %llx.%llx is %u:%u, mds says %u:%u)\n",
				     ceph_vinop(inode), MAJOR(inode->i_rdev),
				     MINOR(inode->i_rdev), MAJOR(rdev),
				     MINOR(rdev));
			वापस -ESTALE;
		पूर्ण
	पूर्ण

	info_caps = le32_to_cpu(info->cap.caps);

	/* pपुनः_स्मृति new cap काष्ठा */
	अगर (info_caps && ceph_snap(inode) == CEPH_NOSNAP) अणु
		new_cap = ceph_get_cap(mdsc, caps_reservation);
		अगर (!new_cap)
			वापस -ENOMEM;
	पूर्ण

	/*
	 * pपुनः_स्मृति xattr data, अगर it looks like we'll need it.  only
	 * अगर len > 4 (meaning there are actually xattrs; the first 4
	 * bytes are the xattr count).
	 */
	अगर (iinfo->xattr_len > 4) अणु
		xattr_blob = ceph_buffer_new(iinfo->xattr_len, GFP_NOFS);
		अगर (!xattr_blob)
			pr_err("%s ENOMEM xattr blob %d bytes\n", __func__,
			       iinfo->xattr_len);
	पूर्ण

	अगर (iinfo->pool_ns_len > 0)
		pool_ns = ceph_find_or_create_string(iinfo->pool_ns_data,
						     iinfo->pool_ns_len);

	अगर (ceph_snap(inode) != CEPH_NOSNAP && !ci->i_snapid_map)
		ci->i_snapid_map = ceph_get_snapid_map(mdsc, ceph_snap(inode));

	spin_lock(&ci->i_ceph_lock);

	/*
	 * provided version will be odd अगर inode value is projected,
	 * even अगर stable.  skip the update अगर we have newer stable
	 * info (ours>=theirs, e.g. due to racing mds replies), unless
	 * we are getting projected (unstable) info (in which हाल the
	 * version is odd, and we want ours>theirs).
	 *   us   them
	 *   2    2     skip
	 *   3    2     skip
	 *   3    3     update
	 */
	अगर (ci->i_version == 0 ||
	    ((info->cap.flags & CEPH_CAP_FLAG_AUTH) &&
	     le64_to_cpu(info->version) > (ci->i_version & ~1)))
		new_version = true;

	/* Update change_attribute */
	inode_set_max_iversion_raw(inode, iinfo->change_attr);

	__ceph_caps_issued(ci, &issued);
	issued |= __ceph_caps_dirty(ci);
	new_issued = ~issued & info_caps;

	/* directories have fl_stripe_unit set to zero */
	अगर (le32_to_cpu(info->layout.fl_stripe_unit))
		inode->i_blkbits =
			fls(le32_to_cpu(info->layout.fl_stripe_unit)) - 1;
	अन्यथा
		inode->i_blkbits = CEPH_BLOCK_SHIFT;

	__ceph_update_quota(ci, iinfo->max_bytes, iinfo->max_files);

	अगर ((new_version || (new_issued & CEPH_CAP_AUTH_SHARED)) &&
	    (issued & CEPH_CAP_AUTH_EXCL) == 0) अणु
		inode->i_mode = mode;
		inode->i_uid = make_kuid(&init_user_ns, le32_to_cpu(info->uid));
		inode->i_gid = make_kgid(&init_user_ns, le32_to_cpu(info->gid));
		करोut("%p mode 0%o uid.gid %d.%d\n", inode, inode->i_mode,
		     from_kuid(&init_user_ns, inode->i_uid),
		     from_kgid(&init_user_ns, inode->i_gid));
		ceph_decode_बारpec64(&ci->i_bसमय, &iinfo->bसमय);
		ceph_decode_बारpec64(&ci->i_snap_bसमय, &iinfo->snap_bसमय);
	पूर्ण

	अगर ((new_version || (new_issued & CEPH_CAP_LINK_SHARED)) &&
	    (issued & CEPH_CAP_LINK_EXCL) == 0)
		set_nlink(inode, le32_to_cpu(info->nlink));

	अगर (new_version || (new_issued & CEPH_CAP_ANY_RD)) अणु
		/* be careful with mसमय, aसमय, size */
		ceph_decode_बारpec64(&aसमय, &info->aसमय);
		ceph_decode_बारpec64(&mसमय, &info->mसमय);
		ceph_decode_बारpec64(&स_समय, &info->स_समय);
		ceph_fill_file_समय(inode, issued,
				le32_to_cpu(info->समय_warp_seq),
				&स_समय, &mसमय, &aसमय);
	पूर्ण

	अगर (new_version || (info_caps & CEPH_CAP_खाता_SHARED)) अणु
		ci->i_files = le64_to_cpu(info->files);
		ci->i_subdirs = le64_to_cpu(info->subdirs);
	पूर्ण

	अगर (new_version ||
	    (new_issued & (CEPH_CAP_ANY_खाता_RD | CEPH_CAP_ANY_खाता_WR))) अणु
		s64 old_pool = ci->i_layout.pool_id;
		काष्ठा ceph_string *old_ns;

		ceph_file_layout_from_legacy(&ci->i_layout, &info->layout);
		old_ns = rcu_dereference_रक्षित(ci->i_layout.pool_ns,
					lockdep_is_held(&ci->i_ceph_lock));
		rcu_assign_poपूर्णांकer(ci->i_layout.pool_ns, pool_ns);

		अगर (ci->i_layout.pool_id != old_pool || pool_ns != old_ns)
			ci->i_ceph_flags &= ~CEPH_I_POOL_PERM;

		pool_ns = old_ns;

		queue_trunc = ceph_fill_file_size(inode, issued,
					le32_to_cpu(info->truncate_seq),
					le64_to_cpu(info->truncate_size),
					le64_to_cpu(info->size));
		/* only update max_size on auth cap */
		अगर ((info->cap.flags & CEPH_CAP_FLAG_AUTH) &&
		    ci->i_max_size != le64_to_cpu(info->max_size)) अणु
			करोut("max_size %lld -> %llu\n", ci->i_max_size,
					le64_to_cpu(info->max_size));
			ci->i_max_size = le64_to_cpu(info->max_size);
		पूर्ण
	पूर्ण

	/* layout and rstat are not tracked by capability, update them अगर
	 * the inode info is from auth mds */
	अगर (new_version || (info->cap.flags & CEPH_CAP_FLAG_AUTH)) अणु
		अगर (S_ISसूची(inode->i_mode)) अणु
			ci->i_dir_layout = iinfo->dir_layout;
			ci->i_rbytes = le64_to_cpu(info->rbytes);
			ci->i_rfiles = le64_to_cpu(info->rfiles);
			ci->i_rsubdirs = le64_to_cpu(info->rsubdirs);
			ci->i_dir_pin = iinfo->dir_pin;
			ci->i_rsnaps = iinfo->rsnaps;
			ceph_decode_बारpec64(&ci->i_rस_समय, &info->rस_समय);
		पूर्ण
	पूर्ण

	/* xattrs */
	/* note that अगर i_xattrs.len <= 4, i_xattrs.data will still be शून्य. */
	अगर ((ci->i_xattrs.version == 0 || !(issued & CEPH_CAP_XATTR_EXCL))  &&
	    le64_to_cpu(info->xattr_version) > ci->i_xattrs.version) अणु
		अगर (ci->i_xattrs.blob)
			old_blob = ci->i_xattrs.blob;
		ci->i_xattrs.blob = xattr_blob;
		अगर (xattr_blob)
			स_नकल(ci->i_xattrs.blob->vec.iov_base,
			       iinfo->xattr_data, iinfo->xattr_len);
		ci->i_xattrs.version = le64_to_cpu(info->xattr_version);
		ceph_क्रमget_all_cached_acls(inode);
		ceph_security_invalidate_secctx(inode);
		xattr_blob = शून्य;
	पूर्ण

	/* finally update i_version */
	अगर (le64_to_cpu(info->version) > ci->i_version)
		ci->i_version = le64_to_cpu(info->version);

	inode->i_mapping->a_ops = &ceph_aops;

	चयन (inode->i_mode & S_IFMT) अणु
	हाल S_IFIFO:
	हाल S_IFBLK:
	हाल S_IFCHR:
	हाल S_IFSOCK:
		inode->i_blkbits = PAGE_SHIFT;
		init_special_inode(inode, inode->i_mode, rdev);
		inode->i_op = &ceph_file_iops;
		अवरोध;
	हाल S_IFREG:
		inode->i_op = &ceph_file_iops;
		inode->i_fop = &ceph_file_fops;
		अवरोध;
	हाल S_IFLNK:
		inode->i_op = &ceph_symlink_iops;
		अगर (!ci->i_symlink) अणु
			u32 symlen = iinfo->symlink_len;
			अक्षर *sym;

			spin_unlock(&ci->i_ceph_lock);

			अगर (symlen != i_size_पढ़ो(inode)) अणु
				pr_err("%s %llx.%llx BAD symlink "
					"size %lld\n", __func__,
					ceph_vinop(inode),
					i_size_पढ़ो(inode));
				i_size_ग_लिखो(inode, symlen);
				inode->i_blocks = calc_inode_blocks(symlen);
			पूर्ण

			err = -ENOMEM;
			sym = kstrndup(iinfo->symlink, symlen, GFP_NOFS);
			अगर (!sym)
				जाओ out;

			spin_lock(&ci->i_ceph_lock);
			अगर (!ci->i_symlink)
				ci->i_symlink = sym;
			अन्यथा
				kमुक्त(sym); /* lost a race */
		पूर्ण
		inode->i_link = ci->i_symlink;
		अवरोध;
	हाल S_IFसूची:
		inode->i_op = &ceph_dir_iops;
		inode->i_fop = &ceph_dir_fops;
		अवरोध;
	शेष:
		pr_err("%s %llx.%llx BAD mode 0%o\n", __func__,
		       ceph_vinop(inode), inode->i_mode);
	पूर्ण

	/* were we issued a capability? */
	अगर (info_caps) अणु
		अगर (ceph_snap(inode) == CEPH_NOSNAP) अणु
			ceph_add_cap(inode, session,
				     le64_to_cpu(info->cap.cap_id),
				     info_caps,
				     le32_to_cpu(info->cap.wanted),
				     le32_to_cpu(info->cap.seq),
				     le32_to_cpu(info->cap.mseq),
				     le64_to_cpu(info->cap.realm),
				     info->cap.flags, &new_cap);

			/* set dir completion flag? */
			अगर (S_ISसूची(inode->i_mode) &&
			    ci->i_files == 0 && ci->i_subdirs == 0 &&
			    (info_caps & CEPH_CAP_खाता_SHARED) &&
			    (issued & CEPH_CAP_खाता_EXCL) == 0 &&
			    !__ceph_dir_is_complete(ci)) अणु
				करोut(" marking %p complete (empty)\n", inode);
				i_size_ग_लिखो(inode, 0);
				__ceph_dir_set_complete(ci,
					atomic64_पढ़ो(&ci->i_release_count),
					atomic64_पढ़ो(&ci->i_ordered_count));
			पूर्ण

			wake = true;
		पूर्ण अन्यथा अणु
			करोut(" %p got snap_caps %s\n", inode,
			     ceph_cap_string(info_caps));
			ci->i_snap_caps |= info_caps;
		पूर्ण
	पूर्ण

	अगर (iinfo->अंतरभूत_version > 0 &&
	    iinfo->अंतरभूत_version >= ci->i_अंतरभूत_version) अणु
		पूर्णांक cache_caps = CEPH_CAP_खाता_CACHE | CEPH_CAP_खाता_LAZYIO;
		ci->i_अंतरभूत_version = iinfo->अंतरभूत_version;
		अगर (ci->i_अंतरभूत_version != CEPH_INLINE_NONE &&
		    (locked_page || (info_caps & cache_caps)))
			fill_अंतरभूत = true;
	पूर्ण

	अगर (cap_भ_शेषe >= 0) अणु
		अगर (!info_caps)
			pr_warn("mds issued no caps on %llx.%llx\n",
				ceph_vinop(inode));
		__ceph_touch_भ_शेषe(ci, mdsc, cap_भ_शेषe);
	पूर्ण

	spin_unlock(&ci->i_ceph_lock);

	अगर (fill_अंतरभूत)
		ceph_fill_अंतरभूत_data(inode, locked_page,
				      iinfo->अंतरभूत_data, iinfo->अंतरभूत_len);

	अगर (wake)
		wake_up_all(&ci->i_cap_wq);

	/* queue truncate अगर we saw i_size decrease */
	अगर (queue_trunc)
		ceph_queue_vmtruncate(inode);

	/* populate frag tree */
	अगर (S_ISसूची(inode->i_mode))
		ceph_fill_fragtree(inode, &info->fragtree, dirinfo);

	/* update delegation info? */
	अगर (dirinfo)
		ceph_fill_dirfrag(inode, dirinfo);

	err = 0;
out:
	अगर (new_cap)
		ceph_put_cap(mdsc, new_cap);
	ceph_buffer_put(old_blob);
	ceph_buffer_put(xattr_blob);
	ceph_put_string(pool_ns);
	वापस err;
पूर्ण

/*
 * caller should hold session s_mutex and dentry->d_lock.
 */
अटल व्योम __update_dentry_lease(काष्ठा inode *dir, काष्ठा dentry *dentry,
				  काष्ठा ceph_mds_reply_lease *lease,
				  काष्ठा ceph_mds_session *session,
				  अचिन्हित दीर्घ from_समय,
				  काष्ठा ceph_mds_session **old_lease_session)
अणु
	काष्ठा ceph_dentry_info *di = ceph_dentry(dentry);
	अचिन्हित mask = le16_to_cpu(lease->mask);
	दीर्घ अचिन्हित duration = le32_to_cpu(lease->duration_ms);
	दीर्घ अचिन्हित ttl = from_समय + (duration * HZ) / 1000;
	दीर्घ अचिन्हित half_ttl = from_समय + (duration * HZ / 2) / 1000;

	करोut("update_dentry_lease %p duration %lu ms ttl %lu\n",
	     dentry, duration, ttl);

	/* only track leases on regular dentries */
	अगर (ceph_snap(dir) != CEPH_NOSNAP)
		वापस;

	अगर (mask & CEPH_LEASE_PRIMARY_LINK)
		di->flags |= CEPH_DENTRY_PRIMARY_LINK;
	अन्यथा
		di->flags &= ~CEPH_DENTRY_PRIMARY_LINK;

	di->lease_shared_gen = atomic_पढ़ो(&ceph_inode(dir)->i_shared_gen);
	अगर (!(mask & CEPH_LEASE_VALID)) अणु
		__ceph_dentry_dir_lease_touch(di);
		वापस;
	पूर्ण

	अगर (di->lease_gen == session->s_cap_gen &&
	    समय_beक्रमe(ttl, di->समय))
		वापस;  /* we alपढ़ोy have a newer lease. */

	अगर (di->lease_session && di->lease_session != session) अणु
		*old_lease_session = di->lease_session;
		di->lease_session = शून्य;
	पूर्ण

	अगर (!di->lease_session)
		di->lease_session = ceph_get_mds_session(session);
	di->lease_gen = session->s_cap_gen;
	di->lease_seq = le32_to_cpu(lease->seq);
	di->lease_renew_after = half_ttl;
	di->lease_renew_from = 0;
	di->समय = ttl;

	__ceph_dentry_lease_touch(di);
पूर्ण

अटल अंतरभूत व्योम update_dentry_lease(काष्ठा inode *dir, काष्ठा dentry *dentry,
					काष्ठा ceph_mds_reply_lease *lease,
					काष्ठा ceph_mds_session *session,
					अचिन्हित दीर्घ from_समय)
अणु
	काष्ठा ceph_mds_session *old_lease_session = शून्य;
	spin_lock(&dentry->d_lock);
	__update_dentry_lease(dir, dentry, lease, session, from_समय,
			      &old_lease_session);
	spin_unlock(&dentry->d_lock);
	अगर (old_lease_session)
		ceph_put_mds_session(old_lease_session);
पूर्ण

/*
 * update dentry lease without having parent inode locked
 */
अटल व्योम update_dentry_lease_careful(काष्ठा dentry *dentry,
					काष्ठा ceph_mds_reply_lease *lease,
					काष्ठा ceph_mds_session *session,
					अचिन्हित दीर्घ from_समय,
					अक्षर *dname, u32 dname_len,
					काष्ठा ceph_vino *pdvino,
					काष्ठा ceph_vino *ptvino)

अणु
	काष्ठा inode *dir;
	काष्ठा ceph_mds_session *old_lease_session = शून्य;

	spin_lock(&dentry->d_lock);
	/* make sure dentry's name matches target */
	अगर (dentry->d_name.len != dname_len ||
	    स_भेद(dentry->d_name.name, dname, dname_len))
		जाओ out_unlock;

	dir = d_inode(dentry->d_parent);
	/* make sure parent matches dvino */
	अगर (!ceph_ino_compare(dir, pdvino))
		जाओ out_unlock;

	/* make sure dentry's inode matches target. शून्य ptvino means that
	 * we expect a negative dentry */
	अगर (ptvino) अणु
		अगर (d_really_is_negative(dentry))
			जाओ out_unlock;
		अगर (!ceph_ino_compare(d_inode(dentry), ptvino))
			जाओ out_unlock;
	पूर्ण अन्यथा अणु
		अगर (d_really_is_positive(dentry))
			जाओ out_unlock;
	पूर्ण

	__update_dentry_lease(dir, dentry, lease, session,
			      from_समय, &old_lease_session);
out_unlock:
	spin_unlock(&dentry->d_lock);
	अगर (old_lease_session)
		ceph_put_mds_session(old_lease_session);
पूर्ण

/*
 * splice a dentry to an inode.
 * caller must hold directory i_mutex क्रम this to be safe.
 */
अटल पूर्णांक splice_dentry(काष्ठा dentry **pdn, काष्ठा inode *in)
अणु
	काष्ठा dentry *dn = *pdn;
	काष्ठा dentry *realdn;

	BUG_ON(d_inode(dn));

	अगर (S_ISसूची(in->i_mode)) अणु
		/* If inode is directory, d_splice_alias() below will हटाओ
		 * 'realdn' from its origin parent. We need to ensure that
		 * origin parent's readdir cache will not reference 'realdn'
		 */
		realdn = d_find_any_alias(in);
		अगर (realdn) अणु
			काष्ठा ceph_dentry_info *di = ceph_dentry(realdn);
			spin_lock(&realdn->d_lock);

			realdn->d_op->d_prune(realdn);

			di->समय = jअगरfies;
			di->lease_shared_gen = 0;
			di->offset = 0;

			spin_unlock(&realdn->d_lock);
			dput(realdn);
		पूर्ण
	पूर्ण

	/* dn must be unhashed */
	अगर (!d_unhashed(dn))
		d_drop(dn);
	realdn = d_splice_alias(in, dn);
	अगर (IS_ERR(realdn)) अणु
		pr_err("splice_dentry error %ld %p inode %p ino %llx.%llx\n",
		       PTR_ERR(realdn), dn, in, ceph_vinop(in));
		वापस PTR_ERR(realdn);
	पूर्ण

	अगर (realdn) अणु
		करोut("dn %p (%d) spliced with %p (%d) "
		     "inode %p ino %llx.%llx\n",
		     dn, d_count(dn),
		     realdn, d_count(realdn),
		     d_inode(realdn), ceph_vinop(d_inode(realdn)));
		dput(dn);
		*pdn = realdn;
	पूर्ण अन्यथा अणु
		BUG_ON(!ceph_dentry(dn));
		करोut("dn %p attached to %p ino %llx.%llx\n",
		     dn, d_inode(dn), ceph_vinop(d_inode(dn)));
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Incorporate results पूर्णांकo the local cache.  This is either just
 * one inode, or a directory, dentry, and possibly linked-to inode (e.g.,
 * after a lookup).
 *
 * A reply may contain
 *         a directory inode aदीर्घ with a dentry.
 *  and/or a target inode
 *
 * Called with snap_rwsem (पढ़ो).
 */
पूर्णांक ceph_fill_trace(काष्ठा super_block *sb, काष्ठा ceph_mds_request *req)
अणु
	काष्ठा ceph_mds_session *session = req->r_session;
	काष्ठा ceph_mds_reply_info_parsed *rinfo = &req->r_reply_info;
	काष्ठा inode *in = शून्य;
	काष्ठा ceph_vino tvino, dvino;
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(sb);
	पूर्णांक err = 0;

	करोut("fill_trace %p is_dentry %d is_target %d\n", req,
	     rinfo->head->is_dentry, rinfo->head->is_target);

	अगर (!rinfo->head->is_target && !rinfo->head->is_dentry) अणु
		करोut("fill_trace reply is empty!\n");
		अगर (rinfo->head->result == 0 && req->r_parent)
			ceph_invalidate_dir_request(req);
		वापस 0;
	पूर्ण

	अगर (rinfo->head->is_dentry) अणु
		काष्ठा inode *dir = req->r_parent;

		अगर (dir) अणु
			err = ceph_fill_inode(dir, शून्य, &rinfo->diri,
					      rinfo->dirfrag, session, -1,
					      &req->r_caps_reservation);
			अगर (err < 0)
				जाओ करोne;
		पूर्ण अन्यथा अणु
			WARN_ON_ONCE(1);
		पूर्ण

		अगर (dir && req->r_op == CEPH_MDS_OP_LOOKUPNAME &&
		    test_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags) &&
		    !test_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags)) अणु
			काष्ठा qstr dname;
			काष्ठा dentry *dn, *parent;

			BUG_ON(!rinfo->head->is_target);
			BUG_ON(req->r_dentry);

			parent = d_find_any_alias(dir);
			BUG_ON(!parent);

			dname.name = rinfo->dname;
			dname.len = rinfo->dname_len;
			dname.hash = full_name_hash(parent, dname.name, dname.len);
			tvino.ino = le64_to_cpu(rinfo->targeti.in->ino);
			tvino.snap = le64_to_cpu(rinfo->targeti.in->snapid);
retry_lookup:
			dn = d_lookup(parent, &dname);
			करोut("d_lookup on parent=%p name=%.*s got %p\n",
			     parent, dname.len, dname.name, dn);

			अगर (!dn) अणु
				dn = d_alloc(parent, &dname);
				करोut("d_alloc %p '%.*s' = %p\n", parent,
				     dname.len, dname.name, dn);
				अगर (!dn) अणु
					dput(parent);
					err = -ENOMEM;
					जाओ करोne;
				पूर्ण
				err = 0;
			पूर्ण अन्यथा अगर (d_really_is_positive(dn) &&
				   (ceph_ino(d_inode(dn)) != tvino.ino ||
				    ceph_snap(d_inode(dn)) != tvino.snap)) अणु
				करोut(" dn %p points to wrong inode %p\n",
				     dn, d_inode(dn));
				ceph_dir_clear_ordered(dir);
				d_delete(dn);
				dput(dn);
				जाओ retry_lookup;
			पूर्ण

			req->r_dentry = dn;
			dput(parent);
		पूर्ण
	पूर्ण

	अगर (rinfo->head->is_target) अणु
		/* Should be filled in by handle_reply */
		BUG_ON(!req->r_target_inode);

		in = req->r_target_inode;
		err = ceph_fill_inode(in, req->r_locked_page, &rinfo->targeti,
				शून्य, session,
				(!test_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags) &&
				 !test_bit(CEPH_MDS_R_ASYNC, &req->r_req_flags) &&
				 rinfo->head->result == 0) ?  req->r_भ_शेषe : -1,
				&req->r_caps_reservation);
		अगर (err < 0) अणु
			pr_err("ceph_fill_inode badness %p %llx.%llx\n",
				in, ceph_vinop(in));
			req->r_target_inode = शून्य;
			अगर (in->i_state & I_NEW)
				discard_new_inode(in);
			अन्यथा
				iput(in);
			जाओ करोne;
		पूर्ण
		अगर (in->i_state & I_NEW)
			unlock_new_inode(in);
	पूर्ण

	/*
	 * ignore null lease/binding on snapdir ENOENT, or अन्यथा we
	 * will have trouble splicing in the भव snapdir later
	 */
	अगर (rinfo->head->is_dentry &&
            !test_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags) &&
	    test_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags) &&
	    (rinfo->head->is_target || म_भेदन(req->r_dentry->d_name.name,
					       fsc->mount_options->snapdir_name,
					       req->r_dentry->d_name.len))) अणु
		/*
		 * lookup link नाम   : null -> possibly existing inode
		 * mknod symlink सूची_गढ़ो  : null -> new inode
		 * unlink               : linked -> null
		 */
		काष्ठा inode *dir = req->r_parent;
		काष्ठा dentry *dn = req->r_dentry;
		bool have_dir_cap, have_lease;

		BUG_ON(!dn);
		BUG_ON(!dir);
		BUG_ON(d_inode(dn->d_parent) != dir);

		dvino.ino = le64_to_cpu(rinfo->diri.in->ino);
		dvino.snap = le64_to_cpu(rinfo->diri.in->snapid);

		BUG_ON(ceph_ino(dir) != dvino.ino);
		BUG_ON(ceph_snap(dir) != dvino.snap);

		/* करो we have a lease on the whole dir? */
		have_dir_cap =
			(le32_to_cpu(rinfo->diri.in->cap.caps) &
			 CEPH_CAP_खाता_SHARED);

		/* करो we have a dn lease? */
		have_lease = have_dir_cap ||
			le32_to_cpu(rinfo->dlease->duration_ms);
		अगर (!have_lease)
			करोut("fill_trace  no dentry lease or dir cap\n");

		/* नाम? */
		अगर (req->r_old_dentry && req->r_op == CEPH_MDS_OP_RENAME) अणु
			काष्ठा inode *olddir = req->r_old_dentry_dir;
			BUG_ON(!olddir);

			करोut(" src %p '%pd' dst %p '%pd'\n",
			     req->r_old_dentry,
			     req->r_old_dentry,
			     dn, dn);
			करोut("fill_trace doing d_move %p -> %p\n",
			     req->r_old_dentry, dn);

			/* d_move screws up sibling dentries' offsets */
			ceph_dir_clear_ordered(dir);
			ceph_dir_clear_ordered(olddir);

			d_move(req->r_old_dentry, dn);
			करोut(" src %p '%pd' dst %p '%pd'\n",
			     req->r_old_dentry,
			     req->r_old_dentry,
			     dn, dn);

			/* ensure target dentry is invalidated, despite
			   rehashing bug in vfs_नाम_dir */
			ceph_invalidate_dentry_lease(dn);

			करोut("dn %p gets new offset %lld\n", req->r_old_dentry,
			     ceph_dentry(req->r_old_dentry)->offset);

			/* swap r_dentry and r_old_dentry in हाल that
			 * splice_dentry() माला_लो called later. This is safe
			 * because no other place will use them */
			req->r_dentry = req->r_old_dentry;
			req->r_old_dentry = dn;
			dn = req->r_dentry;
		पूर्ण

		/* null dentry? */
		अगर (!rinfo->head->is_target) अणु
			करोut("fill_trace null dentry\n");
			अगर (d_really_is_positive(dn)) अणु
				करोut("d_delete %p\n", dn);
				ceph_dir_clear_ordered(dir);
				d_delete(dn);
			पूर्ण अन्यथा अगर (have_lease) अणु
				अगर (d_unhashed(dn))
					d_add(dn, शून्य);
				update_dentry_lease(dir, dn,
						    rinfo->dlease, session,
						    req->r_request_started);
			पूर्ण
			जाओ करोne;
		पूर्ण

		/* attach proper inode */
		अगर (d_really_is_negative(dn)) अणु
			ceph_dir_clear_ordered(dir);
			ihold(in);
			err = splice_dentry(&req->r_dentry, in);
			अगर (err < 0)
				जाओ करोne;
			dn = req->r_dentry;  /* may have spliced */
		पूर्ण अन्यथा अगर (d_really_is_positive(dn) && d_inode(dn) != in) अणु
			करोut(" %p links to %p %llx.%llx, not %llx.%llx\n",
			     dn, d_inode(dn), ceph_vinop(d_inode(dn)),
			     ceph_vinop(in));
			d_invalidate(dn);
			have_lease = false;
		पूर्ण

		अगर (have_lease) अणु
			update_dentry_lease(dir, dn,
					    rinfo->dlease, session,
					    req->r_request_started);
		पूर्ण
		करोut(" final dn %p\n", dn);
	पूर्ण अन्यथा अगर ((req->r_op == CEPH_MDS_OP_LOOKUPSNAP ||
		    req->r_op == CEPH_MDS_OP_MKSNAP) &&
	           test_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags) &&
		   !test_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags)) अणु
		काष्ठा inode *dir = req->r_parent;

		/* fill out a snapdir LOOKUPSNAP dentry */
		BUG_ON(!dir);
		BUG_ON(ceph_snap(dir) != CEPH_SNAPसूची);
		BUG_ON(!req->r_dentry);
		करोut(" linking snapped dir %p to dn %p\n", in, req->r_dentry);
		ceph_dir_clear_ordered(dir);
		ihold(in);
		err = splice_dentry(&req->r_dentry, in);
		अगर (err < 0)
			जाओ करोne;
	पूर्ण अन्यथा अगर (rinfo->head->is_dentry && req->r_dentry) अणु
		/* parent inode is not locked, be carefull */
		काष्ठा ceph_vino *ptvino = शून्य;
		dvino.ino = le64_to_cpu(rinfo->diri.in->ino);
		dvino.snap = le64_to_cpu(rinfo->diri.in->snapid);
		अगर (rinfo->head->is_target) अणु
			tvino.ino = le64_to_cpu(rinfo->targeti.in->ino);
			tvino.snap = le64_to_cpu(rinfo->targeti.in->snapid);
			ptvino = &tvino;
		पूर्ण
		update_dentry_lease_careful(req->r_dentry, rinfo->dlease,
					    session, req->r_request_started,
					    rinfo->dname, rinfo->dname_len,
					    &dvino, ptvino);
	पूर्ण
करोne:
	करोut("fill_trace done err=%d\n", err);
	वापस err;
पूर्ण

/*
 * Prepopulate our cache with सूची_पढ़ो results, leases, etc.
 */
अटल पूर्णांक सूची_पढ़ो_prepopulate_inodes_only(काष्ठा ceph_mds_request *req,
					   काष्ठा ceph_mds_session *session)
अणु
	काष्ठा ceph_mds_reply_info_parsed *rinfo = &req->r_reply_info;
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < rinfo->dir_nr; i++) अणु
		काष्ठा ceph_mds_reply_dir_entry *rde = rinfo->dir_entries + i;
		काष्ठा ceph_vino vino;
		काष्ठा inode *in;
		पूर्णांक rc;

		vino.ino = le64_to_cpu(rde->inode.in->ino);
		vino.snap = le64_to_cpu(rde->inode.in->snapid);

		in = ceph_get_inode(req->r_dentry->d_sb, vino);
		अगर (IS_ERR(in)) अणु
			err = PTR_ERR(in);
			करोut("new_inode badness got %d\n", err);
			जारी;
		पूर्ण
		rc = ceph_fill_inode(in, शून्य, &rde->inode, शून्य, session,
				     -1, &req->r_caps_reservation);
		अगर (rc < 0) अणु
			pr_err("ceph_fill_inode badness on %p got %d\n",
			       in, rc);
			err = rc;
			अगर (in->i_state & I_NEW) अणु
				ihold(in);
				discard_new_inode(in);
			पूर्ण
		पूर्ण अन्यथा अगर (in->i_state & I_NEW) अणु
			unlock_new_inode(in);
		पूर्ण

		/* aव्योम calling iput_final() in mds dispatch thपढ़ोs */
		ceph_async_iput(in);
	पूर्ण

	वापस err;
पूर्ण

व्योम ceph_सूची_पढ़ो_cache_release(काष्ठा ceph_सूची_पढ़ो_cache_control *ctl)
अणु
	अगर (ctl->page) अणु
		kunmap(ctl->page);
		put_page(ctl->page);
		ctl->page = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक fill_सूची_पढ़ो_cache(काष्ठा inode *dir, काष्ठा dentry *dn,
			      काष्ठा ceph_सूची_पढ़ो_cache_control *ctl,
			      काष्ठा ceph_mds_request *req)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(dir);
	अचिन्हित nsize = PAGE_SIZE / माप(काष्ठा dentry*);
	अचिन्हित idx = ctl->index % nsize;
	pgoff_t pgoff = ctl->index / nsize;

	अगर (!ctl->page || pgoff != page_index(ctl->page)) अणु
		ceph_सूची_पढ़ो_cache_release(ctl);
		अगर (idx == 0)
			ctl->page = grab_cache_page(&dir->i_data, pgoff);
		अन्यथा
			ctl->page = find_lock_page(&dir->i_data, pgoff);
		अगर (!ctl->page) अणु
			ctl->index = -1;
			वापस idx == 0 ? -ENOMEM : 0;
		पूर्ण
		/* पढ़ोing/filling the cache are serialized by
		 * i_mutex, no need to use page lock */
		unlock_page(ctl->page);
		ctl->dentries = kmap(ctl->page);
		अगर (idx == 0)
			स_रखो(ctl->dentries, 0, PAGE_SIZE);
	पूर्ण

	अगर (req->r_dir_release_cnt == atomic64_पढ़ो(&ci->i_release_count) &&
	    req->r_dir_ordered_cnt == atomic64_पढ़ो(&ci->i_ordered_count)) अणु
		करोut("readdir cache dn %p idx %d\n", dn, ctl->index);
		ctl->dentries[idx] = dn;
		ctl->index++;
	पूर्ण अन्यथा अणु
		करोut("disable readdir cache\n");
		ctl->index = -1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक ceph_सूची_पढ़ो_prepopulate(काष्ठा ceph_mds_request *req,
			     काष्ठा ceph_mds_session *session)
अणु
	काष्ठा dentry *parent = req->r_dentry;
	काष्ठा ceph_inode_info *ci = ceph_inode(d_inode(parent));
	काष्ठा ceph_mds_reply_info_parsed *rinfo = &req->r_reply_info;
	काष्ठा qstr dname;
	काष्ठा dentry *dn;
	काष्ठा inode *in;
	पूर्णांक err = 0, skipped = 0, ret, i;
	u32 frag = le32_to_cpu(req->r_args.सूची_पढ़ो.frag);
	u32 last_hash = 0;
	u32 fpos_offset;
	काष्ठा ceph_सूची_पढ़ो_cache_control cache_ctl = अणुपूर्ण;

	अगर (test_bit(CEPH_MDS_R_ABORTED, &req->r_req_flags))
		वापस सूची_पढ़ो_prepopulate_inodes_only(req, session);

	अगर (rinfo->hash_order) अणु
		अगर (req->r_path2) अणु
			last_hash = ceph_str_hash(ci->i_dir_layout.dl_dir_hash,
						  req->r_path2,
						  म_माप(req->r_path2));
			last_hash = ceph_frag_value(last_hash);
		पूर्ण अन्यथा अगर (rinfo->offset_hash) अणु
			/* mds understands offset_hash */
			WARN_ON_ONCE(req->r_सूची_पढ़ो_offset != 2);
			last_hash = le32_to_cpu(req->r_args.सूची_पढ़ो.offset_hash);
		पूर्ण
	पूर्ण

	अगर (rinfo->dir_dir &&
	    le32_to_cpu(rinfo->dir_dir->frag) != frag) अणु
		करोut("readdir_prepopulate got new frag %x -> %x\n",
		     frag, le32_to_cpu(rinfo->dir_dir->frag));
		frag = le32_to_cpu(rinfo->dir_dir->frag);
		अगर (!rinfo->hash_order)
			req->r_सूची_पढ़ो_offset = 2;
	पूर्ण

	अगर (le32_to_cpu(rinfo->head->op) == CEPH_MDS_OP_LSSNAP) अणु
		करोut("readdir_prepopulate %d items under SNAPDIR dn %p\n",
		     rinfo->dir_nr, parent);
	पूर्ण अन्यथा अणु
		करोut("readdir_prepopulate %d items under dn %p\n",
		     rinfo->dir_nr, parent);
		अगर (rinfo->dir_dir)
			ceph_fill_dirfrag(d_inode(parent), rinfo->dir_dir);

		अगर (ceph_frag_is_lefपंचांगost(frag) &&
		    req->r_सूची_पढ़ो_offset == 2 &&
		    !(rinfo->hash_order && last_hash)) अणु
			/* note dir version at start of सूची_पढ़ो so we can
			 * tell अगर any dentries get dropped */
			req->r_dir_release_cnt =
				atomic64_पढ़ो(&ci->i_release_count);
			req->r_dir_ordered_cnt =
				atomic64_पढ़ो(&ci->i_ordered_count);
			req->r_सूची_पढ़ो_cache_idx = 0;
		पूर्ण
	पूर्ण

	cache_ctl.index = req->r_सूची_पढ़ो_cache_idx;
	fpos_offset = req->r_सूची_पढ़ो_offset;

	/* FIXME: release caps/leases अगर error occurs */
	क्रम (i = 0; i < rinfo->dir_nr; i++) अणु
		काष्ठा ceph_mds_reply_dir_entry *rde = rinfo->dir_entries + i;
		काष्ठा ceph_vino tvino;

		dname.name = rde->name;
		dname.len = rde->name_len;
		dname.hash = full_name_hash(parent, dname.name, dname.len);

		tvino.ino = le64_to_cpu(rde->inode.in->ino);
		tvino.snap = le64_to_cpu(rde->inode.in->snapid);

		अगर (rinfo->hash_order) अणु
			u32 hash = ceph_str_hash(ci->i_dir_layout.dl_dir_hash,
						 rde->name, rde->name_len);
			hash = ceph_frag_value(hash);
			अगर (hash != last_hash)
				fpos_offset = 2;
			last_hash = hash;
			rde->offset = ceph_make_fpos(hash, fpos_offset++, true);
		पूर्ण अन्यथा अणु
			rde->offset = ceph_make_fpos(frag, fpos_offset++, false);
		पूर्ण

retry_lookup:
		dn = d_lookup(parent, &dname);
		करोut("d_lookup on parent=%p name=%.*s got %p\n",
		     parent, dname.len, dname.name, dn);

		अगर (!dn) अणु
			dn = d_alloc(parent, &dname);
			करोut("d_alloc %p '%.*s' = %p\n", parent,
			     dname.len, dname.name, dn);
			अगर (!dn) अणु
				करोut("d_alloc badness\n");
				err = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (d_really_is_positive(dn) &&
			   (ceph_ino(d_inode(dn)) != tvino.ino ||
			    ceph_snap(d_inode(dn)) != tvino.snap)) अणु
			काष्ठा ceph_dentry_info *di = ceph_dentry(dn);
			करोut(" dn %p points to wrong inode %p\n",
			     dn, d_inode(dn));

			spin_lock(&dn->d_lock);
			अगर (di->offset > 0 &&
			    di->lease_shared_gen ==
			    atomic_पढ़ो(&ci->i_shared_gen)) अणु
				__ceph_dir_clear_ordered(ci);
				di->offset = 0;
			पूर्ण
			spin_unlock(&dn->d_lock);

			d_delete(dn);
			dput(dn);
			जाओ retry_lookup;
		पूर्ण

		/* inode */
		अगर (d_really_is_positive(dn)) अणु
			in = d_inode(dn);
		पूर्ण अन्यथा अणु
			in = ceph_get_inode(parent->d_sb, tvino);
			अगर (IS_ERR(in)) अणु
				करोut("new_inode badness\n");
				d_drop(dn);
				dput(dn);
				err = PTR_ERR(in);
				जाओ out;
			पूर्ण
		पूर्ण

		ret = ceph_fill_inode(in, शून्य, &rde->inode, शून्य, session,
				      -1, &req->r_caps_reservation);
		अगर (ret < 0) अणु
			pr_err("ceph_fill_inode badness on %p\n", in);
			अगर (d_really_is_negative(dn)) अणु
				/* aव्योम calling iput_final() in mds
				 * dispatch thपढ़ोs */
				अगर (in->i_state & I_NEW) अणु
					ihold(in);
					discard_new_inode(in);
				पूर्ण
				ceph_async_iput(in);
			पूर्ण
			d_drop(dn);
			err = ret;
			जाओ next_item;
		पूर्ण
		अगर (in->i_state & I_NEW)
			unlock_new_inode(in);

		अगर (d_really_is_negative(dn)) अणु
			अगर (ceph_security_xattr_deadlock(in)) अणु
				करोut(" skip splicing dn %p to inode %p"
				     " (security xattr deadlock)\n", dn, in);
				ceph_async_iput(in);
				skipped++;
				जाओ next_item;
			पूर्ण

			err = splice_dentry(&dn, in);
			अगर (err < 0)
				जाओ next_item;
		पूर्ण

		ceph_dentry(dn)->offset = rde->offset;

		update_dentry_lease(d_inode(parent), dn,
				    rde->lease, req->r_session,
				    req->r_request_started);

		अगर (err == 0 && skipped == 0 && cache_ctl.index >= 0) अणु
			ret = fill_सूची_पढ़ो_cache(d_inode(parent), dn,
						 &cache_ctl, req);
			अगर (ret < 0)
				err = ret;
		पूर्ण
next_item:
		dput(dn);
	पूर्ण
out:
	अगर (err == 0 && skipped == 0) अणु
		set_bit(CEPH_MDS_R_DID_PREPOPULATE, &req->r_req_flags);
		req->r_सूची_पढ़ो_cache_idx = cache_ctl.index;
	पूर्ण
	ceph_सूची_पढ़ो_cache_release(&cache_ctl);
	करोut("readdir_prepopulate done\n");
	वापस err;
पूर्ण

bool ceph_inode_set_size(काष्ठा inode *inode, loff_t size)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	bool ret;

	spin_lock(&ci->i_ceph_lock);
	करोut("set_size %p %llu -> %llu\n", inode, i_size_पढ़ो(inode), size);
	i_size_ग_लिखो(inode, size);
	inode->i_blocks = calc_inode_blocks(size);

	ret = __ceph_should_report_size(ci);

	spin_unlock(&ci->i_ceph_lock);
	वापस ret;
पूर्ण

/*
 * Put reference to inode, but aव्योम calling iput_final() in current thपढ़ो.
 * iput_final() may रुको क्रम reahahead pages. The रुको can cause deadlock in
 * some contexts.
 */
व्योम ceph_async_iput(काष्ठा inode *inode)
अणु
	अगर (!inode)
		वापस;
	क्रम (;;) अणु
		अगर (atomic_add_unless(&inode->i_count, -1, 1))
			अवरोध;
		अगर (queue_work(ceph_inode_to_client(inode)->inode_wq,
			       &ceph_inode(inode)->i_work))
			अवरोध;
		/* queue work failed, i_count must be at least 2 */
	पूर्ण
पूर्ण

व्योम ceph_queue_inode_work(काष्ठा inode *inode, पूर्णांक work_bit)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	set_bit(work_bit, &ci->i_work_mask);

	ihold(inode);
	अगर (queue_work(fsc->inode_wq, &ci->i_work)) अणु
		करोut("queue_inode_work %p, mask=%lx\n", inode, ci->i_work_mask);
	पूर्ण अन्यथा अणु
		करोut("queue_inode_work %p already queued, mask=%lx\n",
		     inode, ci->i_work_mask);
		iput(inode);
	पूर्ण
पूर्ण

अटल व्योम ceph_करो_invalidate_pages(काष्ठा inode *inode)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	u32 orig_gen;
	पूर्णांक check = 0;

	mutex_lock(&ci->i_truncate_mutex);

	अगर (READ_ONCE(fsc->mount_state) >= CEPH_MOUNT_SHUTDOWN) अणु
		pr_warn_ratelimited("invalidate_pages %p %lld forced umount\n",
				    inode, ceph_ino(inode));
		mapping_set_error(inode->i_mapping, -EIO);
		truncate_pagecache(inode, 0);
		mutex_unlock(&ci->i_truncate_mutex);
		जाओ out;
	पूर्ण

	spin_lock(&ci->i_ceph_lock);
	करोut("invalidate_pages %p gen %d revoking %d\n", inode,
	     ci->i_rdcache_gen, ci->i_rdcache_revoking);
	अगर (ci->i_rdcache_revoking != ci->i_rdcache_gen) अणु
		अगर (__ceph_caps_revoking_other(ci, शून्य, CEPH_CAP_खाता_CACHE))
			check = 1;
		spin_unlock(&ci->i_ceph_lock);
		mutex_unlock(&ci->i_truncate_mutex);
		जाओ out;
	पूर्ण
	orig_gen = ci->i_rdcache_gen;
	spin_unlock(&ci->i_ceph_lock);

	ceph_fscache_invalidate(inode);
	अगर (invalidate_inode_pages2(inode->i_mapping) < 0) अणु
		pr_err("invalidate_pages %p fails\n", inode);
	पूर्ण

	spin_lock(&ci->i_ceph_lock);
	अगर (orig_gen == ci->i_rdcache_gen &&
	    orig_gen == ci->i_rdcache_revoking) अणु
		करोut("invalidate_pages %p gen %d successful\n", inode,
		     ci->i_rdcache_gen);
		ci->i_rdcache_revoking--;
		check = 1;
	पूर्ण अन्यथा अणु
		करोut("invalidate_pages %p gen %d raced, now %d revoking %d\n",
		     inode, orig_gen, ci->i_rdcache_gen,
		     ci->i_rdcache_revoking);
		अगर (__ceph_caps_revoking_other(ci, शून्य, CEPH_CAP_खाता_CACHE))
			check = 1;
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);
	mutex_unlock(&ci->i_truncate_mutex);
out:
	अगर (check)
		ceph_check_caps(ci, 0, शून्य);
पूर्ण

/*
 * Make sure any pending truncation is applied beक्रमe करोing anything
 * that may depend on it.
 */
व्योम __ceph_करो_pending_vmtruncate(काष्ठा inode *inode)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	u64 to;
	पूर्णांक wrbuffer_refs, finish = 0;

	mutex_lock(&ci->i_truncate_mutex);
retry:
	spin_lock(&ci->i_ceph_lock);
	अगर (ci->i_truncate_pending == 0) अणु
		करोut("__do_pending_vmtruncate %p none pending\n", inode);
		spin_unlock(&ci->i_ceph_lock);
		mutex_unlock(&ci->i_truncate_mutex);
		वापस;
	पूर्ण

	/*
	 * make sure any dirty snapped pages are flushed beक्रमe we
	 * possibly truncate them.. so ग_लिखो AND block!
	 */
	अगर (ci->i_wrbuffer_ref_head < ci->i_wrbuffer_ref) अणु
		spin_unlock(&ci->i_ceph_lock);
		करोut("__do_pending_vmtruncate %p flushing snaps first\n",
		     inode);
		filemap_ग_लिखो_and_रुको_range(&inode->i_data, 0,
					     inode->i_sb->s_maxbytes);
		जाओ retry;
	पूर्ण

	/* there should be no पढ़ोer or ग_लिखोr */
	WARN_ON_ONCE(ci->i_rd_ref || ci->i_wr_ref);

	to = ci->i_truncate_size;
	wrbuffer_refs = ci->i_wrbuffer_ref;
	करोut("__do_pending_vmtruncate %p (%d) to %lld\n", inode,
	     ci->i_truncate_pending, to);
	spin_unlock(&ci->i_ceph_lock);

	truncate_pagecache(inode, to);

	spin_lock(&ci->i_ceph_lock);
	अगर (to == ci->i_truncate_size) अणु
		ci->i_truncate_pending = 0;
		finish = 1;
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);
	अगर (!finish)
		जाओ retry;

	mutex_unlock(&ci->i_truncate_mutex);

	अगर (wrbuffer_refs == 0)
		ceph_check_caps(ci, 0, शून्य);

	wake_up_all(&ci->i_cap_wq);
पूर्ण

अटल व्योम ceph_inode_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ceph_inode_info *ci = container_of(work, काष्ठा ceph_inode_info,
						 i_work);
	काष्ठा inode *inode = &ci->vfs_inode;

	अगर (test_and_clear_bit(CEPH_I_WORK_WRITEBACK, &ci->i_work_mask)) अणु
		करोut("writeback %p\n", inode);
		filemap_fdataग_लिखो(&inode->i_data);
	पूर्ण
	अगर (test_and_clear_bit(CEPH_I_WORK_INVALIDATE_PAGES, &ci->i_work_mask))
		ceph_करो_invalidate_pages(inode);

	अगर (test_and_clear_bit(CEPH_I_WORK_VMTRUNCATE, &ci->i_work_mask))
		__ceph_करो_pending_vmtruncate(inode);

	अगर (test_and_clear_bit(CEPH_I_WORK_CHECK_CAPS, &ci->i_work_mask))
		ceph_check_caps(ci, 0, शून्य);

	अगर (test_and_clear_bit(CEPH_I_WORK_FLUSH_SNAPS, &ci->i_work_mask))
		ceph_flush_snaps(ci, शून्य);

	iput(inode);
पूर्ण

/*
 * symlinks
 */
अटल स्थिर काष्ठा inode_operations ceph_symlink_iops = अणु
	.get_link = simple_get_link,
	.setattr = ceph_setattr,
	.getattr = ceph_getattr,
	.listxattr = ceph_listxattr,
पूर्ण;

पूर्णांक __ceph_setattr(काष्ठा inode *inode, काष्ठा iattr *attr)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	अचिन्हित पूर्णांक ia_valid = attr->ia_valid;
	काष्ठा ceph_mds_request *req;
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_client(inode->i_sb)->mdsc;
	काष्ठा ceph_cap_flush *pपुनः_स्मृति_cf;
	पूर्णांक issued;
	पूर्णांक release = 0, dirtied = 0;
	पूर्णांक mask = 0;
	पूर्णांक err = 0;
	पूर्णांक inode_dirty_flags = 0;
	bool lock_snap_rwsem = false;

	pपुनः_स्मृति_cf = ceph_alloc_cap_flush();
	अगर (!pपुनः_स्मृति_cf)
		वापस -ENOMEM;

	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_SETATTR,
				       USE_AUTH_MDS);
	अगर (IS_ERR(req)) अणु
		ceph_मुक्त_cap_flush(pपुनः_स्मृति_cf);
		वापस PTR_ERR(req);
	पूर्ण

	spin_lock(&ci->i_ceph_lock);
	issued = __ceph_caps_issued(ci, शून्य);

	अगर (!ci->i_head_snapc &&
	    (issued & (CEPH_CAP_ANY_EXCL | CEPH_CAP_खाता_WR))) अणु
		lock_snap_rwsem = true;
		अगर (!करोwn_पढ़ो_trylock(&mdsc->snap_rwsem)) अणु
			spin_unlock(&ci->i_ceph_lock);
			करोwn_पढ़ो(&mdsc->snap_rwsem);
			spin_lock(&ci->i_ceph_lock);
			issued = __ceph_caps_issued(ci, शून्य);
		पूर्ण
	पूर्ण

	करोut("setattr %p issued %s\n", inode, ceph_cap_string(issued));

	अगर (ia_valid & ATTR_UID) अणु
		करोut("setattr %p uid %d -> %d\n", inode,
		     from_kuid(&init_user_ns, inode->i_uid),
		     from_kuid(&init_user_ns, attr->ia_uid));
		अगर (issued & CEPH_CAP_AUTH_EXCL) अणु
			inode->i_uid = attr->ia_uid;
			dirtied |= CEPH_CAP_AUTH_EXCL;
		पूर्ण अन्यथा अगर ((issued & CEPH_CAP_AUTH_SHARED) == 0 ||
			   !uid_eq(attr->ia_uid, inode->i_uid)) अणु
			req->r_args.setattr.uid = cpu_to_le32(
				from_kuid(&init_user_ns, attr->ia_uid));
			mask |= CEPH_SETATTR_UID;
			release |= CEPH_CAP_AUTH_SHARED;
		पूर्ण
	पूर्ण
	अगर (ia_valid & ATTR_GID) अणु
		करोut("setattr %p gid %d -> %d\n", inode,
		     from_kgid(&init_user_ns, inode->i_gid),
		     from_kgid(&init_user_ns, attr->ia_gid));
		अगर (issued & CEPH_CAP_AUTH_EXCL) अणु
			inode->i_gid = attr->ia_gid;
			dirtied |= CEPH_CAP_AUTH_EXCL;
		पूर्ण अन्यथा अगर ((issued & CEPH_CAP_AUTH_SHARED) == 0 ||
			   !gid_eq(attr->ia_gid, inode->i_gid)) अणु
			req->r_args.setattr.gid = cpu_to_le32(
				from_kgid(&init_user_ns, attr->ia_gid));
			mask |= CEPH_SETATTR_GID;
			release |= CEPH_CAP_AUTH_SHARED;
		पूर्ण
	पूर्ण
	अगर (ia_valid & ATTR_MODE) अणु
		करोut("setattr %p mode 0%o -> 0%o\n", inode, inode->i_mode,
		     attr->ia_mode);
		अगर (issued & CEPH_CAP_AUTH_EXCL) अणु
			inode->i_mode = attr->ia_mode;
			dirtied |= CEPH_CAP_AUTH_EXCL;
		पूर्ण अन्यथा अगर ((issued & CEPH_CAP_AUTH_SHARED) == 0 ||
			   attr->ia_mode != inode->i_mode) अणु
			inode->i_mode = attr->ia_mode;
			req->r_args.setattr.mode = cpu_to_le32(attr->ia_mode);
			mask |= CEPH_SETATTR_MODE;
			release |= CEPH_CAP_AUTH_SHARED;
		पूर्ण
	पूर्ण

	अगर (ia_valid & ATTR_ATIME) अणु
		करोut("setattr %p atime %lld.%ld -> %lld.%ld\n", inode,
		     inode->i_aसमय.tv_sec, inode->i_aसमय.tv_nsec,
		     attr->ia_aसमय.tv_sec, attr->ia_aसमय.tv_nsec);
		अगर (issued & CEPH_CAP_खाता_EXCL) अणु
			ci->i_समय_warp_seq++;
			inode->i_aसमय = attr->ia_aसमय;
			dirtied |= CEPH_CAP_खाता_EXCL;
		पूर्ण अन्यथा अगर ((issued & CEPH_CAP_खाता_WR) &&
			   बारpec64_compare(&inode->i_aसमय,
					    &attr->ia_aसमय) < 0) अणु
			inode->i_aसमय = attr->ia_aसमय;
			dirtied |= CEPH_CAP_खाता_WR;
		पूर्ण अन्यथा अगर ((issued & CEPH_CAP_खाता_SHARED) == 0 ||
			   !बारpec64_equal(&inode->i_aसमय, &attr->ia_aसमय)) अणु
			ceph_encode_बारpec64(&req->r_args.setattr.aसमय,
					       &attr->ia_aसमय);
			mask |= CEPH_SETATTR_ATIME;
			release |= CEPH_CAP_खाता_SHARED |
				   CEPH_CAP_खाता_RD | CEPH_CAP_खाता_WR;
		पूर्ण
	पूर्ण
	अगर (ia_valid & ATTR_SIZE) अणु
		loff_t isize = i_size_पढ़ो(inode);

		करोut("setattr %p size %lld -> %lld\n", inode, isize, attr->ia_size);
		अगर ((issued & CEPH_CAP_खाता_EXCL) && attr->ia_size > isize) अणु
			i_size_ग_लिखो(inode, attr->ia_size);
			inode->i_blocks = calc_inode_blocks(attr->ia_size);
			ci->i_reported_size = attr->ia_size;
			dirtied |= CEPH_CAP_खाता_EXCL;
			ia_valid |= ATTR_MTIME;
		पूर्ण अन्यथा अगर ((issued & CEPH_CAP_खाता_SHARED) == 0 ||
			   attr->ia_size != isize) अणु
			req->r_args.setattr.size = cpu_to_le64(attr->ia_size);
			req->r_args.setattr.old_size = cpu_to_le64(isize);
			mask |= CEPH_SETATTR_SIZE;
			release |= CEPH_CAP_खाता_SHARED | CEPH_CAP_खाता_EXCL |
				   CEPH_CAP_खाता_RD | CEPH_CAP_खाता_WR;
		पूर्ण
	पूर्ण
	अगर (ia_valid & ATTR_MTIME) अणु
		करोut("setattr %p mtime %lld.%ld -> %lld.%ld\n", inode,
		     inode->i_mसमय.tv_sec, inode->i_mसमय.tv_nsec,
		     attr->ia_mसमय.tv_sec, attr->ia_mसमय.tv_nsec);
		अगर (issued & CEPH_CAP_खाता_EXCL) अणु
			ci->i_समय_warp_seq++;
			inode->i_mसमय = attr->ia_mसमय;
			dirtied |= CEPH_CAP_खाता_EXCL;
		पूर्ण अन्यथा अगर ((issued & CEPH_CAP_खाता_WR) &&
			   बारpec64_compare(&inode->i_mसमय,
					    &attr->ia_mसमय) < 0) अणु
			inode->i_mसमय = attr->ia_mसमय;
			dirtied |= CEPH_CAP_खाता_WR;
		पूर्ण अन्यथा अगर ((issued & CEPH_CAP_खाता_SHARED) == 0 ||
			   !बारpec64_equal(&inode->i_mसमय, &attr->ia_mसमय)) अणु
			ceph_encode_बारpec64(&req->r_args.setattr.mसमय,
					       &attr->ia_mसमय);
			mask |= CEPH_SETATTR_MTIME;
			release |= CEPH_CAP_खाता_SHARED |
				   CEPH_CAP_खाता_RD | CEPH_CAP_खाता_WR;
		पूर्ण
	पूर्ण

	/* these करो nothing */
	अगर (ia_valid & ATTR_CTIME) अणु
		bool only = (ia_valid & (ATTR_SIZE|ATTR_MTIME|ATTR_ATIME|
					 ATTR_MODE|ATTR_UID|ATTR_GID)) == 0;
		करोut("setattr %p ctime %lld.%ld -> %lld.%ld (%s)\n", inode,
		     inode->i_स_समय.tv_sec, inode->i_स_समय.tv_nsec,
		     attr->ia_स_समय.tv_sec, attr->ia_स_समय.tv_nsec,
		     only ? "ctime only" : "ignored");
		अगर (only) अणु
			/*
			 * अगर kernel wants to dirty स_समय but nothing अन्यथा,
			 * we need to choose a cap to dirty under, or करो
			 * a almost-no-op setattr
			 */
			अगर (issued & CEPH_CAP_AUTH_EXCL)
				dirtied |= CEPH_CAP_AUTH_EXCL;
			अन्यथा अगर (issued & CEPH_CAP_खाता_EXCL)
				dirtied |= CEPH_CAP_खाता_EXCL;
			अन्यथा अगर (issued & CEPH_CAP_XATTR_EXCL)
				dirtied |= CEPH_CAP_XATTR_EXCL;
			अन्यथा
				mask |= CEPH_SETATTR_CTIME;
		पूर्ण
	पूर्ण
	अगर (ia_valid & ATTR_खाता)
		करोut("setattr %p ATTR_FILE ... hrm!\n", inode);

	अगर (dirtied) अणु
		inode_dirty_flags = __ceph_mark_dirty_caps(ci, dirtied,
							   &pपुनः_स्मृति_cf);
		inode->i_स_समय = attr->ia_स_समय;
	पूर्ण

	release &= issued;
	spin_unlock(&ci->i_ceph_lock);
	अगर (lock_snap_rwsem)
		up_पढ़ो(&mdsc->snap_rwsem);

	अगर (inode_dirty_flags)
		__mark_inode_dirty(inode, inode_dirty_flags);


	अगर (mask) अणु
		req->r_inode = inode;
		ihold(inode);
		req->r_inode_drop = release;
		req->r_args.setattr.mask = cpu_to_le32(mask);
		req->r_num_caps = 1;
		req->r_stamp = attr->ia_स_समय;
		err = ceph_mdsc_करो_request(mdsc, शून्य, req);
	पूर्ण
	करोut("setattr %p result=%d (%s locally, %d remote)\n", inode, err,
	     ceph_cap_string(dirtied), mask);

	ceph_mdsc_put_request(req);
	ceph_मुक्त_cap_flush(pपुनः_स्मृति_cf);

	अगर (err >= 0 && (mask & CEPH_SETATTR_SIZE))
		__ceph_करो_pending_vmtruncate(inode);

	वापस err;
पूर्ण

/*
 * setattr
 */
पूर्णांक ceph_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		 काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	पूर्णांक err;

	अगर (ceph_snap(inode) != CEPH_NOSNAP)
		वापस -EROFS;

	err = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (err != 0)
		वापस err;

	अगर ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size > max(i_size_पढ़ो(inode), fsc->max_file_size))
		वापस -EFBIG;

	अगर ((attr->ia_valid & ATTR_SIZE) &&
	    ceph_quota_is_max_bytes_exceeded(inode, attr->ia_size))
		वापस -EDQUOT;

	err = __ceph_setattr(inode, attr);

	अगर (err >= 0 && (attr->ia_valid & ATTR_MODE))
		err = posix_acl_chmod(&init_user_ns, inode, attr->ia_mode);

	वापस err;
पूर्ण

/*
 * Verअगरy that we have a lease on the given mask.  If not,
 * करो a getattr against an mds.
 */
पूर्णांक __ceph_करो_getattr(काष्ठा inode *inode, काष्ठा page *locked_page,
		      पूर्णांक mask, bool क्रमce)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(inode->i_sb);
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	काष्ठा ceph_mds_request *req;
	पूर्णांक mode;
	पूर्णांक err;

	अगर (ceph_snap(inode) == CEPH_SNAPसूची) अणु
		करोut("do_getattr inode %p SNAPDIR\n", inode);
		वापस 0;
	पूर्ण

	करोut("do_getattr inode %p mask %s mode 0%o\n",
	     inode, ceph_cap_string(mask), inode->i_mode);
	अगर (!क्रमce && ceph_caps_issued_mask_metric(ceph_inode(inode), mask, 1))
			वापस 0;

	mode = (mask & CEPH_STAT_RSTAT) ? USE_AUTH_MDS : USE_ANY_MDS;
	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_GETATTR, mode);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);
	req->r_inode = inode;
	ihold(inode);
	req->r_num_caps = 1;
	req->r_args.getattr.mask = cpu_to_le32(mask);
	req->r_locked_page = locked_page;
	err = ceph_mdsc_करो_request(mdsc, शून्य, req);
	अगर (locked_page && err == 0) अणु
		u64 अंतरभूत_version = req->r_reply_info.targeti.अंतरभूत_version;
		अगर (अंतरभूत_version == 0) अणु
			/* the reply is supposed to contain अंतरभूत data */
			err = -EINVAL;
		पूर्ण अन्यथा अगर (अंतरभूत_version == CEPH_INLINE_NONE) अणु
			err = -ENODATA;
		पूर्ण अन्यथा अणु
			err = req->r_reply_info.targeti.अंतरभूत_len;
		पूर्ण
	पूर्ण
	ceph_mdsc_put_request(req);
	करोut("do_getattr result=%d\n", err);
	वापस err;
पूर्ण


/*
 * Check inode permissions.  We verअगरy we have a valid value क्रम
 * the AUTH cap, then call the generic handler.
 */
पूर्णांक ceph_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		    पूर्णांक mask)
अणु
	पूर्णांक err;

	अगर (mask & MAY_NOT_BLOCK)
		वापस -ECHILD;

	err = ceph_करो_getattr(inode, CEPH_CAP_AUTH_SHARED, false);

	अगर (!err)
		err = generic_permission(&init_user_ns, inode, mask);
	वापस err;
पूर्ण

/* Craft a mask of needed caps given a set of requested statx attrs. */
अटल पूर्णांक statx_to_caps(u32 want, umode_t mode)
अणु
	पूर्णांक mask = 0;

	अगर (want & (STATX_MODE|STATX_UID|STATX_GID|STATX_CTIME|STATX_BTIME))
		mask |= CEPH_CAP_AUTH_SHARED;

	अगर (want & (STATX_NLINK|STATX_CTIME)) अणु
		/*
		 * The link count क्रम directories depends on inode->i_subdirs,
		 * and that is only updated when Fs caps are held.
		 */
		अगर (S_ISसूची(mode))
			mask |= CEPH_CAP_खाता_SHARED;
		अन्यथा
			mask |= CEPH_CAP_LINK_SHARED;
	पूर्ण

	अगर (want & (STATX_ATIME|STATX_MTIME|STATX_CTIME|STATX_SIZE|
		    STATX_BLOCKS))
		mask |= CEPH_CAP_खाता_SHARED;

	अगर (want & (STATX_CTIME))
		mask |= CEPH_CAP_XATTR_SHARED;

	वापस mask;
पूर्ण

/*
 * Get all the attributes. If we have sufficient caps क्रम the requested attrs,
 * then we can aव्योम talking to the MDS at all.
 */
पूर्णांक ceph_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		 काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	u32 valid_mask = STATX_BASIC_STATS;
	पूर्णांक err = 0;

	/* Skip the getattr altogether अगर we're asked not to sync */
	अगर (!(flags & AT_STATX_DONT_SYNC)) अणु
		err = ceph_करो_getattr(inode,
				statx_to_caps(request_mask, inode->i_mode),
				flags & AT_STATX_FORCE_SYNC);
		अगर (err)
			वापस err;
	पूर्ण

	generic_fillattr(&init_user_ns, inode, stat);
	stat->ino = ceph_present_inode(inode);

	/*
	 * bसमय on newly-allocated inodes is 0, so अगर this is still set to
	 * that, then assume that it's not valid.
	 */
	अगर (ci->i_bसमय.tv_sec || ci->i_bसमय.tv_nsec) अणु
		stat->bसमय = ci->i_bसमय;
		valid_mask |= STATX_BTIME;
	पूर्ण

	अगर (ceph_snap(inode) == CEPH_NOSNAP)
		stat->dev = inode->i_sb->s_dev;
	अन्यथा
		stat->dev = ci->i_snapid_map ? ci->i_snapid_map->dev : 0;

	अगर (S_ISसूची(inode->i_mode)) अणु
		अगर (ceph_test_mount_opt(ceph_sb_to_client(inode->i_sb),
					RBYTES))
			stat->size = ci->i_rbytes;
		अन्यथा
			stat->size = ci->i_files + ci->i_subdirs;
		stat->blocks = 0;
		stat->blksize = 65536;
		/*
		 * Some applications rely on the number of st_nlink
		 * value on directories to be either 0 (अगर unlinked)
		 * or 2 + number of subdirectories.
		 */
		अगर (stat->nlink == 1)
			/* '.' + '..' + subdirs */
			stat->nlink = 1 + 1 + ci->i_subdirs;
	पूर्ण

	stat->result_mask = request_mask & valid_mask;
	वापस err;
पूर्ण
