<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/spinlock.h>
#समावेश <linux/namei.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/xattr.h>

#समावेश "super.h"
#समावेश "mds_client.h"

/*
 * Directory operations: सूची_पढ़ो, lookup, create, link, unlink,
 * नाम, etc.
 */

/*
 * Ceph MDS operations are specअगरied in terms of a base ino and
 * relative path.  Thus, the client can specअगरy an operation on a
 * specअगरic inode (e.g., a getattr due to ख_स्थिति(2)), or as a path
 * relative to, say, the root directory.
 *
 * Normally, we limit ourselves to strict inode ops (no path component)
 * or dentry operations (a single path component relative to an ino).  The
 * exception to this is खोलो_root_dentry(), which will खोलो the mount
 * poपूर्णांक by name.
 */

स्थिर काष्ठा dentry_operations ceph_dentry_ops;

अटल bool __dentry_lease_is_valid(काष्ठा ceph_dentry_info *di);
अटल पूर्णांक __dir_lease_try_check(स्थिर काष्ठा dentry *dentry);

/*
 * Initialize ceph dentry state.
 */
अटल पूर्णांक ceph_d_init(काष्ठा dentry *dentry)
अणु
	काष्ठा ceph_dentry_info *di;
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(dentry->d_sb);

	di = kmem_cache_zalloc(ceph_dentry_cachep, GFP_KERNEL);
	अगर (!di)
		वापस -ENOMEM;          /* oh well */

	di->dentry = dentry;
	di->lease_session = शून्य;
	di->समय = jअगरfies;
	dentry->d_fsdata = di;
	INIT_LIST_HEAD(&di->lease_list);

	atomic64_inc(&mdsc->metric.total_dentries);

	वापस 0;
पूर्ण

/*
 * क्रम f_pos क्रम सूची_पढ़ो:
 * - hash order:
 *	(0xff << 52) | ((24 bits hash) << 28) |
 *	(the nth entry has hash collision);
 * - frag+name order;
 *	((frag value) << 28) | (the nth entry in frag);
 */
#घोषणा OFFSET_BITS	28
#घोषणा OFFSET_MASK	((1 << OFFSET_BITS) - 1)
#घोषणा HASH_ORDER	(0xffull << (OFFSET_BITS + 24))
loff_t ceph_make_fpos(अचिन्हित high, अचिन्हित off, bool hash_order)
अणु
	loff_t fpos = ((loff_t)high << 28) | (loff_t)off;
	अगर (hash_order)
		fpos |= HASH_ORDER;
	वापस fpos;
पूर्ण

अटल bool is_hash_order(loff_t p)
अणु
	वापस (p & HASH_ORDER) == HASH_ORDER;
पूर्ण

अटल अचिन्हित fpos_frag(loff_t p)
अणु
	वापस p >> OFFSET_BITS;
पूर्ण

अटल अचिन्हित fpos_hash(loff_t p)
अणु
	वापस ceph_frag_value(fpos_frag(p));
पूर्ण

अटल अचिन्हित fpos_off(loff_t p)
अणु
	वापस p & OFFSET_MASK;
पूर्ण

अटल पूर्णांक fpos_cmp(loff_t l, loff_t r)
अणु
	पूर्णांक v = ceph_frag_compare(fpos_frag(l), fpos_frag(r));
	अगर (v)
		वापस v;
	वापस (पूर्णांक)(fpos_off(l) - fpos_off(r));
पूर्ण

/*
 * make note of the last dentry we पढ़ो, so we can
 * जारी at the same lexicographical poपूर्णांक,
 * regardless of what dir changes take place on the
 * server.
 */
अटल पूर्णांक note_last_dentry(काष्ठा ceph_dir_file_info *dfi, स्थिर अक्षर *name,
		            पूर्णांक len, अचिन्हित next_offset)
अणु
	अक्षर *buf = kदो_स्मृति(len+1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	kमुक्त(dfi->last_name);
	dfi->last_name = buf;
	स_नकल(dfi->last_name, name, len);
	dfi->last_name[len] = 0;
	dfi->next_offset = next_offset;
	करोut("note_last_dentry '%s'\n", dfi->last_name);
	वापस 0;
पूर्ण


अटल काष्ठा dentry *
__dcache_find_get_entry(काष्ठा dentry *parent, u64 idx,
			काष्ठा ceph_सूची_पढ़ो_cache_control *cache_ctl)
अणु
	काष्ठा inode *dir = d_inode(parent);
	काष्ठा dentry *dentry;
	अचिन्हित idx_mask = (PAGE_SIZE / माप(काष्ठा dentry *)) - 1;
	loff_t ptr_pos = idx * माप(काष्ठा dentry *);
	pgoff_t ptr_pgoff = ptr_pos >> PAGE_SHIFT;

	अगर (ptr_pos >= i_size_पढ़ो(dir))
		वापस शून्य;

	अगर (!cache_ctl->page || ptr_pgoff != page_index(cache_ctl->page)) अणु
		ceph_सूची_पढ़ो_cache_release(cache_ctl);
		cache_ctl->page = find_lock_page(&dir->i_data, ptr_pgoff);
		अगर (!cache_ctl->page) अणु
			करोut(" page %lu not found\n", ptr_pgoff);
			वापस ERR_PTR(-EAGAIN);
		पूर्ण
		/* पढ़ोing/filling the cache are serialized by
		   i_mutex, no need to use page lock */
		unlock_page(cache_ctl->page);
		cache_ctl->dentries = kmap(cache_ctl->page);
	पूर्ण

	cache_ctl->index = idx & idx_mask;

	rcu_पढ़ो_lock();
	spin_lock(&parent->d_lock);
	/* check i_size again here, because empty directory can be
	 * marked as complete जबतक not holding the i_mutex. */
	अगर (ceph_dir_is_complete_ordered(dir) && ptr_pos < i_size_पढ़ो(dir))
		dentry = cache_ctl->dentries[cache_ctl->index];
	अन्यथा
		dentry = शून्य;
	spin_unlock(&parent->d_lock);
	अगर (dentry && !lockref_get_not_dead(&dentry->d_lockref))
		dentry = शून्य;
	rcu_पढ़ो_unlock();
	वापस dentry ? : ERR_PTR(-EAGAIN);
पूर्ण

/*
 * When possible, we try to satisfy a सूची_पढ़ो by peeking at the
 * dcache.  We make this work by carefully ordering dentries on
 * d_child when we initially get results back from the MDS, and
 * falling back to a "normal" sync सूची_पढ़ो अगर any dentries in the dir
 * are dropped.
 *
 * Complete dir indicates that we have all dentries in the dir.  It is
 * defined IFF we hold CEPH_CAP_खाता_SHARED (which will be revoked by
 * the MDS अगर/when the directory is modअगरied).
 */
अटल पूर्णांक __dcache_सूची_पढ़ो(काष्ठा file *file,  काष्ठा dir_context *ctx,
			    पूर्णांक shared_gen)
अणु
	काष्ठा ceph_dir_file_info *dfi = file->निजी_data;
	काष्ठा dentry *parent = file->f_path.dentry;
	काष्ठा inode *dir = d_inode(parent);
	काष्ठा dentry *dentry, *last = शून्य;
	काष्ठा ceph_dentry_info *di;
	काष्ठा ceph_सूची_पढ़ो_cache_control cache_ctl = अणुपूर्ण;
	u64 idx = 0;
	पूर्णांक err = 0;

	करोut("__dcache_readdir %p v%u at %llx\n", dir, (अचिन्हित)shared_gen, ctx->pos);

	/* search start position */
	अगर (ctx->pos > 2) अणु
		u64 count = भाग_u64(i_size_पढ़ो(dir), माप(काष्ठा dentry *));
		जबतक (count > 0) अणु
			u64 step = count >> 1;
			dentry = __dcache_find_get_entry(parent, idx + step,
							 &cache_ctl);
			अगर (!dentry) अणु
				/* use linar search */
				idx = 0;
				अवरोध;
			पूर्ण
			अगर (IS_ERR(dentry)) अणु
				err = PTR_ERR(dentry);
				जाओ out;
			पूर्ण
			di = ceph_dentry(dentry);
			spin_lock(&dentry->d_lock);
			अगर (fpos_cmp(di->offset, ctx->pos) < 0) अणु
				idx += step + 1;
				count -= step + 1;
			पूर्ण अन्यथा अणु
				count = step;
			पूर्ण
			spin_unlock(&dentry->d_lock);
			dput(dentry);
		पूर्ण

		करोut("__dcache_readdir %p cache idx %llu\n", dir, idx);
	पूर्ण


	क्रम (;;) अणु
		bool emit_dentry = false;
		dentry = __dcache_find_get_entry(parent, idx++, &cache_ctl);
		अगर (!dentry) अणु
			dfi->file_info.flags |= CEPH_F_ATEND;
			err = 0;
			अवरोध;
		पूर्ण
		अगर (IS_ERR(dentry)) अणु
			err = PTR_ERR(dentry);
			जाओ out;
		पूर्ण

		spin_lock(&dentry->d_lock);
		di = ceph_dentry(dentry);
		अगर (d_unhashed(dentry) ||
		    d_really_is_negative(dentry) ||
		    di->lease_shared_gen != shared_gen) अणु
			spin_unlock(&dentry->d_lock);
			dput(dentry);
			err = -EAGAIN;
			जाओ out;
		पूर्ण
		अगर (fpos_cmp(ctx->pos, di->offset) <= 0) अणु
			__ceph_dentry_dir_lease_touch(di);
			emit_dentry = true;
		पूर्ण
		spin_unlock(&dentry->d_lock);

		अगर (emit_dentry) अणु
			करोut(" %llx dentry %p %pd %p\n", di->offset,
			     dentry, dentry, d_inode(dentry));
			ctx->pos = di->offset;
			अगर (!dir_emit(ctx, dentry->d_name.name,
				      dentry->d_name.len, ceph_present_inode(d_inode(dentry)),
				      d_inode(dentry)->i_mode >> 12)) अणु
				dput(dentry);
				err = 0;
				अवरोध;
			पूर्ण
			ctx->pos++;

			अगर (last)
				dput(last);
			last = dentry;
		पूर्ण अन्यथा अणु
			dput(dentry);
		पूर्ण
	पूर्ण
out:
	ceph_सूची_पढ़ो_cache_release(&cache_ctl);
	अगर (last) अणु
		पूर्णांक ret;
		di = ceph_dentry(last);
		ret = note_last_dentry(dfi, last->d_name.name, last->d_name.len,
				       fpos_off(di->offset) + 1);
		अगर (ret < 0)
			err = ret;
		dput(last);
		/* last_name no दीर्घer match cache index */
		अगर (dfi->सूची_पढ़ो_cache_idx >= 0) अणु
			dfi->सूची_पढ़ो_cache_idx = -1;
			dfi->dir_release_count = 0;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल bool need_send_सूची_पढ़ो(काष्ठा ceph_dir_file_info *dfi, loff_t pos)
अणु
	अगर (!dfi->last_सूची_पढ़ो)
		वापस true;
	अगर (is_hash_order(pos))
		वापस !ceph_frag_contains_value(dfi->frag, fpos_hash(pos));
	अन्यथा
		वापस dfi->frag != fpos_frag(pos);
पूर्ण

अटल पूर्णांक ceph_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा ceph_dir_file_info *dfi = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	पूर्णांक i;
	पूर्णांक err;
	अचिन्हित frag = -1;
	काष्ठा ceph_mds_reply_info_parsed *rinfo;

	करोut("readdir %p file %p pos %llx\n", inode, file, ctx->pos);
	अगर (dfi->file_info.flags & CEPH_F_ATEND)
		वापस 0;

	/* always start with . and .. */
	अगर (ctx->pos == 0) अणु
		करोut("readdir off 0 -> '.'\n");
		अगर (!dir_emit(ctx, ".", 1, ceph_present_inode(inode),
			    inode->i_mode >> 12))
			वापस 0;
		ctx->pos = 1;
	पूर्ण
	अगर (ctx->pos == 1) अणु
		u64 ino;
		काष्ठा dentry *dentry = file->f_path.dentry;

		spin_lock(&dentry->d_lock);
		ino = ceph_present_inode(dentry->d_parent->d_inode);
		spin_unlock(&dentry->d_lock);

		करोut("readdir off 1 -> '..'\n");
		अगर (!dir_emit(ctx, "..", 2, ino, inode->i_mode >> 12))
			वापस 0;
		ctx->pos = 2;
	पूर्ण

	spin_lock(&ci->i_ceph_lock);
	/* request Fx cap. अगर have Fx, we करोn't need to release Fs cap
	 * क्रम later create/unlink. */
	__ceph_touch_भ_शेषe(ci, mdsc, CEPH_खाता_MODE_WR);
	/* can we use the dcache? */
	अगर (ceph_test_mount_opt(fsc, DCACHE) &&
	    !ceph_test_mount_opt(fsc, NOASYNCREADसूची) &&
	    ceph_snap(inode) != CEPH_SNAPसूची &&
	    __ceph_dir_is_complete_ordered(ci) &&
	    __ceph_caps_issued_mask_metric(ci, CEPH_CAP_खाता_SHARED, 1)) अणु
		पूर्णांक shared_gen = atomic_पढ़ो(&ci->i_shared_gen);

		spin_unlock(&ci->i_ceph_lock);
		err = __dcache_सूची_पढ़ो(file, ctx, shared_gen);
		अगर (err != -EAGAIN)
			वापस err;
	पूर्ण अन्यथा अणु
		spin_unlock(&ci->i_ceph_lock);
	पूर्ण

	/* proceed with a normal सूची_पढ़ो */
more:
	/* करो we have the correct frag content buffered? */
	अगर (need_send_सूची_पढ़ो(dfi, ctx->pos)) अणु
		काष्ठा ceph_mds_request *req;
		पूर्णांक op = ceph_snap(inode) == CEPH_SNAPसूची ?
			CEPH_MDS_OP_LSSNAP : CEPH_MDS_OP_READसूची;

		/* discard old result, अगर any */
		अगर (dfi->last_सूची_पढ़ो) अणु
			ceph_mdsc_put_request(dfi->last_सूची_पढ़ो);
			dfi->last_सूची_पढ़ो = शून्य;
		पूर्ण

		अगर (is_hash_order(ctx->pos)) अणु
			/* fragtree isn't always accurate. choose frag
			 * based on previous reply when possible. */
			अगर (frag == (अचिन्हित)-1)
				frag = ceph_choose_frag(ci, fpos_hash(ctx->pos),
							शून्य, शून्य);
		पूर्ण अन्यथा अणु
			frag = fpos_frag(ctx->pos);
		पूर्ण

		करोut("readdir fetching %llx.%llx frag %x offset '%s'\n",
		     ceph_vinop(inode), frag, dfi->last_name);
		req = ceph_mdsc_create_request(mdsc, op, USE_AUTH_MDS);
		अगर (IS_ERR(req))
			वापस PTR_ERR(req);
		err = ceph_alloc_सूची_पढ़ो_reply_buffer(req, inode);
		अगर (err) अणु
			ceph_mdsc_put_request(req);
			वापस err;
		पूर्ण
		/* hपूर्णांकs to request -> mds selection code */
		req->r_direct_mode = USE_AUTH_MDS;
		अगर (op == CEPH_MDS_OP_READसूची) अणु
			req->r_direct_hash = ceph_frag_value(frag);
			__set_bit(CEPH_MDS_R_सूचीECT_IS_HASH, &req->r_req_flags);
			req->r_inode_drop = CEPH_CAP_खाता_EXCL;
		पूर्ण
		अगर (dfi->last_name) अणु
			req->r_path2 = kstrdup(dfi->last_name, GFP_KERNEL);
			अगर (!req->r_path2) अणु
				ceph_mdsc_put_request(req);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण अन्यथा अगर (is_hash_order(ctx->pos)) अणु
			req->r_args.सूची_पढ़ो.offset_hash =
				cpu_to_le32(fpos_hash(ctx->pos));
		पूर्ण

		req->r_dir_release_cnt = dfi->dir_release_count;
		req->r_dir_ordered_cnt = dfi->dir_ordered_count;
		req->r_सूची_पढ़ो_cache_idx = dfi->सूची_पढ़ो_cache_idx;
		req->r_सूची_पढ़ो_offset = dfi->next_offset;
		req->r_args.सूची_पढ़ो.frag = cpu_to_le32(frag);
		req->r_args.सूची_पढ़ो.flags =
				cpu_to_le16(CEPH_READसूची_REPLY_BITFLAGS);

		req->r_inode = inode;
		ihold(inode);
		req->r_dentry = dget(file->f_path.dentry);
		err = ceph_mdsc_करो_request(mdsc, शून्य, req);
		अगर (err < 0) अणु
			ceph_mdsc_put_request(req);
			वापस err;
		पूर्ण
		करोut("readdir got and parsed readdir result=%d on "
		     "frag %x, end=%d, complete=%d, hash_order=%d\n",
		     err, frag,
		     (पूर्णांक)req->r_reply_info.dir_end,
		     (पूर्णांक)req->r_reply_info.dir_complete,
		     (पूर्णांक)req->r_reply_info.hash_order);

		rinfo = &req->r_reply_info;
		अगर (le32_to_cpu(rinfo->dir_dir->frag) != frag) अणु
			frag = le32_to_cpu(rinfo->dir_dir->frag);
			अगर (!rinfo->hash_order) अणु
				dfi->next_offset = req->r_सूची_पढ़ो_offset;
				/* adjust ctx->pos to beginning of frag */
				ctx->pos = ceph_make_fpos(frag,
							  dfi->next_offset,
							  false);
			पूर्ण
		पूर्ण

		dfi->frag = frag;
		dfi->last_सूची_पढ़ो = req;

		अगर (test_bit(CEPH_MDS_R_DID_PREPOPULATE, &req->r_req_flags)) अणु
			dfi->सूची_पढ़ो_cache_idx = req->r_सूची_पढ़ो_cache_idx;
			अगर (dfi->सूची_पढ़ो_cache_idx < 0) अणु
				/* preclude from marking dir ordered */
				dfi->dir_ordered_count = 0;
			पूर्ण अन्यथा अगर (ceph_frag_is_lefपंचांगost(frag) &&
				   dfi->next_offset == 2) अणु
				/* note dir version at start of सूची_पढ़ो so
				 * we can tell अगर any dentries get dropped */
				dfi->dir_release_count = req->r_dir_release_cnt;
				dfi->dir_ordered_count = req->r_dir_ordered_cnt;
			पूर्ण
		पूर्ण अन्यथा अणु
			करोut("readdir !did_prepopulate\n");
			/* disable सूची_पढ़ो cache */
			dfi->सूची_पढ़ो_cache_idx = -1;
			/* preclude from marking dir complete */
			dfi->dir_release_count = 0;
		पूर्ण

		/* note next offset and last dentry name */
		अगर (rinfo->dir_nr > 0) अणु
			काष्ठा ceph_mds_reply_dir_entry *rde =
					rinfo->dir_entries + (rinfo->dir_nr-1);
			अचिन्हित next_offset = req->r_reply_info.dir_end ?
					2 : (fpos_off(rde->offset) + 1);
			err = note_last_dentry(dfi, rde->name, rde->name_len,
					       next_offset);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अगर (req->r_reply_info.dir_end) अणु
			dfi->next_offset = 2;
			/* keep last name */
		पूर्ण
	पूर्ण

	rinfo = &dfi->last_सूची_पढ़ो->r_reply_info;
	करोut("readdir frag %x num %d pos %llx chunk first %llx\n",
	     dfi->frag, rinfo->dir_nr, ctx->pos,
	     rinfo->dir_nr ? rinfo->dir_entries[0].offset : 0LL);

	i = 0;
	/* search start position */
	अगर (rinfo->dir_nr > 0) अणु
		पूर्णांक step, nr = rinfo->dir_nr;
		जबतक (nr > 0) अणु
			step = nr >> 1;
			अगर (rinfo->dir_entries[i + step].offset < ctx->pos) अणु
				i +=  step + 1;
				nr -= step + 1;
			पूर्ण अन्यथा अणु
				nr = step;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (; i < rinfo->dir_nr; i++) अणु
		काष्ठा ceph_mds_reply_dir_entry *rde = rinfo->dir_entries + i;

		BUG_ON(rde->offset < ctx->pos);

		ctx->pos = rde->offset;
		करोut("readdir (%d/%d) -> %llx '%.*s' %p\n",
		     i, rinfo->dir_nr, ctx->pos,
		     rde->name_len, rde->name, &rde->inode.in);

		BUG_ON(!rde->inode.in);

		अगर (!dir_emit(ctx, rde->name, rde->name_len,
			      ceph_present_ino(inode->i_sb, le64_to_cpu(rde->inode.in->ino)),
			      le32_to_cpu(rde->inode.in->mode) >> 12)) अणु
			करोut("filldir stopping us...\n");
			वापस 0;
		पूर्ण
		ctx->pos++;
	पूर्ण

	ceph_mdsc_put_request(dfi->last_सूची_पढ़ो);
	dfi->last_सूची_पढ़ो = शून्य;

	अगर (dfi->next_offset > 2) अणु
		frag = dfi->frag;
		जाओ more;
	पूर्ण

	/* more frags? */
	अगर (!ceph_frag_is_righपंचांगost(dfi->frag)) अणु
		frag = ceph_frag_next(dfi->frag);
		अगर (is_hash_order(ctx->pos)) अणु
			loff_t new_pos = ceph_make_fpos(ceph_frag_value(frag),
							dfi->next_offset, true);
			अगर (new_pos > ctx->pos)
				ctx->pos = new_pos;
			/* keep last_name */
		पूर्ण अन्यथा अणु
			ctx->pos = ceph_make_fpos(frag, dfi->next_offset,
							false);
			kमुक्त(dfi->last_name);
			dfi->last_name = शून्य;
		पूर्ण
		करोut("readdir next frag is %x\n", frag);
		जाओ more;
	पूर्ण
	dfi->file_info.flags |= CEPH_F_ATEND;

	/*
	 * अगर dir_release_count still matches the dir, no dentries
	 * were released during the whole सूची_पढ़ो, and we should have
	 * the complete dir contents in our cache.
	 */
	अगर (atomic64_पढ़ो(&ci->i_release_count) ==
					dfi->dir_release_count) अणु
		spin_lock(&ci->i_ceph_lock);
		अगर (dfi->dir_ordered_count ==
				atomic64_पढ़ो(&ci->i_ordered_count)) अणु
			करोut(" marking %p complete and ordered\n", inode);
			/* use i_size to track number of entries in
			 * सूची_पढ़ो cache */
			BUG_ON(dfi->सूची_पढ़ो_cache_idx < 0);
			i_size_ग_लिखो(inode, dfi->सूची_पढ़ो_cache_idx *
				     माप(काष्ठा dentry*));
		पूर्ण अन्यथा अणु
			करोut(" marking %p complete\n", inode);
		पूर्ण
		__ceph_dir_set_complete(ci, dfi->dir_release_count,
					dfi->dir_ordered_count);
		spin_unlock(&ci->i_ceph_lock);
	पूर्ण

	करोut("readdir %p file %p done.\n", inode, file);
	वापस 0;
पूर्ण

अटल व्योम reset_सूची_पढ़ो(काष्ठा ceph_dir_file_info *dfi)
अणु
	अगर (dfi->last_सूची_पढ़ो) अणु
		ceph_mdsc_put_request(dfi->last_सूची_पढ़ो);
		dfi->last_सूची_पढ़ो = शून्य;
	पूर्ण
	kमुक्त(dfi->last_name);
	dfi->last_name = शून्य;
	dfi->dir_release_count = 0;
	dfi->सूची_पढ़ो_cache_idx = -1;
	dfi->next_offset = 2;  /* compensate क्रम . and .. */
	dfi->file_info.flags &= ~CEPH_F_ATEND;
पूर्ण

/*
 * discard buffered सूची_पढ़ो content on seekdir(0), or seek to new frag,
 * or seek prior to current chunk
 */
अटल bool need_reset_सूची_पढ़ो(काष्ठा ceph_dir_file_info *dfi, loff_t new_pos)
अणु
	काष्ठा ceph_mds_reply_info_parsed *rinfo;
	loff_t chunk_offset;
	अगर (new_pos == 0)
		वापस true;
	अगर (is_hash_order(new_pos)) अणु
		/* no need to reset last_name क्रम a क्रमward seek when
		 * dentries are sotred in hash order */
	पूर्ण अन्यथा अगर (dfi->frag != fpos_frag(new_pos)) अणु
		वापस true;
	पूर्ण
	rinfo = dfi->last_सूची_पढ़ो ? &dfi->last_सूची_पढ़ो->r_reply_info : शून्य;
	अगर (!rinfo || !rinfo->dir_nr)
		वापस true;
	chunk_offset = rinfo->dir_entries[0].offset;
	वापस new_pos < chunk_offset ||
	       is_hash_order(new_pos) != is_hash_order(chunk_offset);
पूर्ण

अटल loff_t ceph_dir_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा ceph_dir_file_info *dfi = file->निजी_data;
	काष्ठा inode *inode = file->f_mapping->host;
	loff_t retval;

	inode_lock(inode);
	retval = -EINVAL;
	चयन (whence) अणु
	हाल प्रस्तुत_से:
		offset += file->f_pos;
		अवरोध;
	हाल शुरू_से:
		अवरोध;
	हाल अंत_से:
		retval = -EOPNOTSUPP;
		जाओ out;
	शेष:
		जाओ out;
	पूर्ण

	अगर (offset >= 0) अणु
		अगर (need_reset_सूची_पढ़ो(dfi, offset)) अणु
			करोut("dir_llseek dropping %p content\n", file);
			reset_सूची_पढ़ो(dfi);
		पूर्ण अन्यथा अगर (is_hash_order(offset) && offset > file->f_pos) अणु
			/* क्रम hash offset, we करोn't know अगर a क्रमward seek
			 * is within same frag */
			dfi->dir_release_count = 0;
			dfi->सूची_पढ़ो_cache_idx = -1;
		पूर्ण

		अगर (offset != file->f_pos) अणु
			file->f_pos = offset;
			file->f_version = 0;
			dfi->file_info.flags &= ~CEPH_F_ATEND;
		पूर्ण
		retval = offset;
	पूर्ण
out:
	inode_unlock(inode);
	वापस retval;
पूर्ण

/*
 * Handle lookups क्रम the hidden .snap directory.
 */
काष्ठा dentry *ceph_handle_snapdir(काष्ठा ceph_mds_request *req,
				   काष्ठा dentry *dentry, पूर्णांक err)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(dentry->d_sb);
	काष्ठा inode *parent = d_inode(dentry->d_parent); /* we hold i_mutex */

	/* .snap dir? */
	अगर (err == -ENOENT &&
	    ceph_snap(parent) == CEPH_NOSNAP &&
	    म_भेद(dentry->d_name.name, fsc->mount_options->snapdir_name) == 0) अणु
		काष्ठा dentry *res;
		काष्ठा inode *inode = ceph_get_snapdir(parent);

		res = d_splice_alias(inode, dentry);
		करोut("ENOENT on snapdir %p '%pd', linking to snapdir %p. Spliced dentry %p\n",
		     dentry, dentry, inode, res);
		अगर (res)
			dentry = res;
	पूर्ण
	वापस dentry;
पूर्ण

/*
 * Figure out final result of a lookup/खोलो request.
 *
 * Mainly, make sure we वापस the final req->r_dentry (अगर it alपढ़ोy
 * existed) in place of the original VFS-provided dentry when they
 * dअगरfer.
 *
 * Gracefully handle the हाल where the MDS replies with -ENOENT and
 * no trace (which it may करो, at its discretion, e.g., अगर it करोesn't
 * care to issue a lease on the negative dentry).
 */
काष्ठा dentry *ceph_finish_lookup(काष्ठा ceph_mds_request *req,
				  काष्ठा dentry *dentry, पूर्णांक err)
अणु
	अगर (err == -ENOENT) अणु
		/* no trace? */
		err = 0;
		अगर (!req->r_reply_info.head->is_dentry) अणु
			करोut("ENOENT and no trace, dentry %p inode %p\n",
			     dentry, d_inode(dentry));
			अगर (d_really_is_positive(dentry)) अणु
				d_drop(dentry);
				err = -ENOENT;
			पूर्ण अन्यथा अणु
				d_add(dentry, शून्य);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (err)
		dentry = ERR_PTR(err);
	अन्यथा अगर (dentry != req->r_dentry)
		dentry = dget(req->r_dentry);   /* we got spliced */
	अन्यथा
		dentry = शून्य;
	वापस dentry;
पूर्ण

अटल bool is_root_ceph_dentry(काष्ठा inode *inode, काष्ठा dentry *dentry)
अणु
	वापस ceph_ino(inode) == CEPH_INO_ROOT &&
		म_भेदन(dentry->d_name.name, ".ceph", 5) == 0;
पूर्ण

/*
 * Look up a single dir entry.  If there is a lookup पूर्णांकent, inक्रमm
 * the MDS so that it माला_लो our 'caps wanted' value in a single op.
 */
अटल काष्ठा dentry *ceph_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(dir->i_sb);
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(dir->i_sb);
	काष्ठा ceph_mds_request *req;
	काष्ठा dentry *res;
	पूर्णांक op;
	पूर्णांक mask;
	पूर्णांक err;

	करोut("lookup %p dentry %p '%pd'\n",
	     dir, dentry, dentry);

	अगर (dentry->d_name.len > NAME_MAX)
		वापस ERR_PTR(-ENAMETOOLONG);

	/* can we conclude ENOENT locally? */
	अगर (d_really_is_negative(dentry)) अणु
		काष्ठा ceph_inode_info *ci = ceph_inode(dir);
		काष्ठा ceph_dentry_info *di = ceph_dentry(dentry);

		spin_lock(&ci->i_ceph_lock);
		करोut(" dir %p flags are 0x%lx\n", dir, ci->i_ceph_flags);
		अगर (म_भेदन(dentry->d_name.name,
			    fsc->mount_options->snapdir_name,
			    dentry->d_name.len) &&
		    !is_root_ceph_dentry(dir, dentry) &&
		    ceph_test_mount_opt(fsc, DCACHE) &&
		    __ceph_dir_is_complete(ci) &&
		    __ceph_caps_issued_mask_metric(ci, CEPH_CAP_खाता_SHARED, 1)) अणु
			__ceph_touch_भ_शेषe(ci, mdsc, CEPH_खाता_MODE_RD);
			spin_unlock(&ci->i_ceph_lock);
			करोut(" dir %p complete, -ENOENT\n", dir);
			d_add(dentry, शून्य);
			di->lease_shared_gen = atomic_पढ़ो(&ci->i_shared_gen);
			वापस शून्य;
		पूर्ण
		spin_unlock(&ci->i_ceph_lock);
	पूर्ण

	op = ceph_snap(dir) == CEPH_SNAPसूची ?
		CEPH_MDS_OP_LOOKUPSNAP : CEPH_MDS_OP_LOOKUP;
	req = ceph_mdsc_create_request(mdsc, op, USE_ANY_MDS);
	अगर (IS_ERR(req))
		वापस ERR_CAST(req);
	req->r_dentry = dget(dentry);
	req->r_num_caps = 2;

	mask = CEPH_STAT_CAP_INODE | CEPH_CAP_AUTH_SHARED;
	अगर (ceph_security_xattr_wanted(dir))
		mask |= CEPH_CAP_XATTR_SHARED;
	req->r_args.getattr.mask = cpu_to_le32(mask);

	req->r_parent = dir;
	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	err = ceph_mdsc_करो_request(mdsc, शून्य, req);
	res = ceph_handle_snapdir(req, dentry, err);
	अगर (IS_ERR(res)) अणु
		err = PTR_ERR(res);
	पूर्ण अन्यथा अणु
		dentry = res;
		err = 0;
	पूर्ण
	dentry = ceph_finish_lookup(req, dentry, err);
	ceph_mdsc_put_request(req);  /* will dput(dentry) */
	करोut("lookup result=%p\n", dentry);
	वापस dentry;
पूर्ण

/*
 * If we करो a create but get no trace back from the MDS, follow up with
 * a lookup (the VFS expects us to link up the provided dentry).
 */
पूर्णांक ceph_handle_notrace_create(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *result = ceph_lookup(dir, dentry, 0);

	अगर (result && !IS_ERR(result)) अणु
		/*
		 * We created the item, then did a lookup, and found
		 * it was alपढ़ोy linked to another inode we alपढ़ोy
		 * had in our cache (and thus got spliced). To not
		 * confuse VFS (especially when inode is a directory),
		 * we करोn't link our dentry to that inode, वापस an
		 * error instead.
		 *
		 * This event should be rare and it happens only when
		 * we talk to old MDS. Recent MDS करोes not send traceless
		 * reply क्रम request that creates new inode.
		 */
		d_drop(result);
		वापस -ESTALE;
	पूर्ण
	वापस PTR_ERR(result);
पूर्ण

अटल पूर्णांक ceph_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(dir->i_sb);
	काष्ठा ceph_mds_request *req;
	काष्ठा ceph_acl_sec_ctx as_ctx = अणुपूर्ण;
	पूर्णांक err;

	अगर (ceph_snap(dir) != CEPH_NOSNAP)
		वापस -EROFS;

	अगर (ceph_quota_is_max_files_exceeded(dir)) अणु
		err = -EDQUOT;
		जाओ out;
	पूर्ण

	err = ceph_pre_init_acls(dir, &mode, &as_ctx);
	अगर (err < 0)
		जाओ out;
	err = ceph_security_init_secctx(dentry, mode, &as_ctx);
	अगर (err < 0)
		जाओ out;

	करोut("mknod in dir %p dentry %p mode 0%ho rdev %d\n",
	     dir, dentry, mode, rdev);
	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_MKNOD, USE_AUTH_MDS);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ out;
	पूर्ण
	req->r_dentry = dget(dentry);
	req->r_num_caps = 2;
	req->r_parent = dir;
	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	req->r_args.mknod.mode = cpu_to_le32(mode);
	req->r_args.mknod.rdev = cpu_to_le32(rdev);
	req->r_dentry_drop = CEPH_CAP_खाता_SHARED | CEPH_CAP_AUTH_EXCL;
	req->r_dentry_unless = CEPH_CAP_खाता_EXCL;
	अगर (as_ctx.pagelist) अणु
		req->r_pagelist = as_ctx.pagelist;
		as_ctx.pagelist = शून्य;
	पूर्ण
	err = ceph_mdsc_करो_request(mdsc, dir, req);
	अगर (!err && !req->r_reply_info.head->is_dentry)
		err = ceph_handle_notrace_create(dir, dentry);
	ceph_mdsc_put_request(req);
out:
	अगर (!err)
		ceph_init_inode_acls(d_inode(dentry), &as_ctx);
	अन्यथा
		d_drop(dentry);
	ceph_release_acl_sec_ctx(&as_ctx);
	वापस err;
पूर्ण

अटल पूर्णांक ceph_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	वापस ceph_mknod(mnt_userns, dir, dentry, mode, 0);
पूर्ण

अटल पूर्णांक ceph_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, स्थिर अक्षर *dest)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(dir->i_sb);
	काष्ठा ceph_mds_request *req;
	काष्ठा ceph_acl_sec_ctx as_ctx = अणुपूर्ण;
	पूर्णांक err;

	अगर (ceph_snap(dir) != CEPH_NOSNAP)
		वापस -EROFS;

	अगर (ceph_quota_is_max_files_exceeded(dir)) अणु
		err = -EDQUOT;
		जाओ out;
	पूर्ण

	err = ceph_security_init_secctx(dentry, S_IFLNK | 0777, &as_ctx);
	अगर (err < 0)
		जाओ out;

	करोut("symlink in dir %p dentry %p to '%s'\n", dir, dentry, dest);
	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_SYMLINK, USE_AUTH_MDS);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ out;
	पूर्ण
	req->r_path2 = kstrdup(dest, GFP_KERNEL);
	अगर (!req->r_path2) अणु
		err = -ENOMEM;
		ceph_mdsc_put_request(req);
		जाओ out;
	पूर्ण
	req->r_parent = dir;
	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	req->r_dentry = dget(dentry);
	req->r_num_caps = 2;
	req->r_dentry_drop = CEPH_CAP_खाता_SHARED | CEPH_CAP_AUTH_EXCL;
	req->r_dentry_unless = CEPH_CAP_खाता_EXCL;
	अगर (as_ctx.pagelist) अणु
		req->r_pagelist = as_ctx.pagelist;
		as_ctx.pagelist = शून्य;
	पूर्ण
	err = ceph_mdsc_करो_request(mdsc, dir, req);
	अगर (!err && !req->r_reply_info.head->is_dentry)
		err = ceph_handle_notrace_create(dir, dentry);
	ceph_mdsc_put_request(req);
out:
	अगर (err)
		d_drop(dentry);
	ceph_release_acl_sec_ctx(&as_ctx);
	वापस err;
पूर्ण

अटल पूर्णांक ceph_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(dir->i_sb);
	काष्ठा ceph_mds_request *req;
	काष्ठा ceph_acl_sec_ctx as_ctx = अणुपूर्ण;
	पूर्णांक err = -EROFS;
	पूर्णांक op;

	अगर (ceph_snap(dir) == CEPH_SNAPसूची) अणु
		/* सूची_गढ़ो .snap/foo is a MKSNAP */
		op = CEPH_MDS_OP_MKSNAP;
		करोut("mksnap dir %p snap '%pd' dn %p\n", dir,
		     dentry, dentry);
	पूर्ण अन्यथा अगर (ceph_snap(dir) == CEPH_NOSNAP) अणु
		करोut("mkdir dir %p dn %p mode 0%ho\n", dir, dentry, mode);
		op = CEPH_MDS_OP_MKसूची;
	पूर्ण अन्यथा अणु
		जाओ out;
	पूर्ण

	अगर (op == CEPH_MDS_OP_MKसूची &&
	    ceph_quota_is_max_files_exceeded(dir)) अणु
		err = -EDQUOT;
		जाओ out;
	पूर्ण

	mode |= S_IFसूची;
	err = ceph_pre_init_acls(dir, &mode, &as_ctx);
	अगर (err < 0)
		जाओ out;
	err = ceph_security_init_secctx(dentry, mode, &as_ctx);
	अगर (err < 0)
		जाओ out;

	req = ceph_mdsc_create_request(mdsc, op, USE_AUTH_MDS);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->r_dentry = dget(dentry);
	req->r_num_caps = 2;
	req->r_parent = dir;
	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	req->r_args.सूची_गढ़ो.mode = cpu_to_le32(mode);
	req->r_dentry_drop = CEPH_CAP_खाता_SHARED | CEPH_CAP_AUTH_EXCL;
	req->r_dentry_unless = CEPH_CAP_खाता_EXCL;
	अगर (as_ctx.pagelist) अणु
		req->r_pagelist = as_ctx.pagelist;
		as_ctx.pagelist = शून्य;
	पूर्ण
	err = ceph_mdsc_करो_request(mdsc, dir, req);
	अगर (!err &&
	    !req->r_reply_info.head->is_target &&
	    !req->r_reply_info.head->is_dentry)
		err = ceph_handle_notrace_create(dir, dentry);
	ceph_mdsc_put_request(req);
out:
	अगर (!err)
		ceph_init_inode_acls(d_inode(dentry), &as_ctx);
	अन्यथा
		d_drop(dentry);
	ceph_release_acl_sec_ctx(&as_ctx);
	वापस err;
पूर्ण

अटल पूर्णांक ceph_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
		     काष्ठा dentry *dentry)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(dir->i_sb);
	काष्ठा ceph_mds_request *req;
	पूर्णांक err;

	अगर (ceph_snap(dir) != CEPH_NOSNAP)
		वापस -EROFS;

	करोut("link in dir %p old_dentry %p dentry %p\n", dir,
	     old_dentry, dentry);
	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_LINK, USE_AUTH_MDS);
	अगर (IS_ERR(req)) अणु
		d_drop(dentry);
		वापस PTR_ERR(req);
	पूर्ण
	req->r_dentry = dget(dentry);
	req->r_num_caps = 2;
	req->r_old_dentry = dget(old_dentry);
	req->r_parent = dir;
	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	req->r_dentry_drop = CEPH_CAP_खाता_SHARED;
	req->r_dentry_unless = CEPH_CAP_खाता_EXCL;
	/* release LINK_SHARED on source inode (mds will lock it) */
	req->r_old_inode_drop = CEPH_CAP_LINK_SHARED | CEPH_CAP_LINK_EXCL;
	err = ceph_mdsc_करो_request(mdsc, dir, req);
	अगर (err) अणु
		d_drop(dentry);
	पूर्ण अन्यथा अगर (!req->r_reply_info.head->is_dentry) अणु
		ihold(d_inode(old_dentry));
		d_instantiate(dentry, d_inode(old_dentry));
	पूर्ण
	ceph_mdsc_put_request(req);
	वापस err;
पूर्ण

अटल व्योम ceph_async_unlink_cb(काष्ठा ceph_mds_client *mdsc,
				 काष्ठा ceph_mds_request *req)
अणु
	पूर्णांक result = req->r_err ? req->r_err :
			le32_to_cpu(req->r_reply_info.head->result);

	अगर (result == -EJUKEBOX)
		जाओ out;

	/* If op failed, mark everyone involved क्रम errors */
	अगर (result) अणु
		पूर्णांक pathlen = 0;
		u64 base = 0;
		अक्षर *path = ceph_mdsc_build_path(req->r_dentry, &pathlen,
						  &base, 0);

		/* mark error on parent + clear complete */
		mapping_set_error(req->r_parent->i_mapping, result);
		ceph_dir_clear_complete(req->r_parent);

		/* drop the dentry -- we करोn't know its status */
		अगर (!d_unhashed(req->r_dentry))
			d_drop(req->r_dentry);

		/* mark inode itself क्रम an error (since metadata is bogus) */
		mapping_set_error(req->r_old_inode->i_mapping, result);

		pr_warn("ceph: async unlink failure path=(%llx)%s result=%d!\n",
			base, IS_ERR(path) ? "<<bad>>" : path, result);
		ceph_mdsc_मुक्त_path(path, pathlen);
	पूर्ण
out:
	iput(req->r_old_inode);
	ceph_mdsc_release_dir_caps(req);
पूर्ण

अटल पूर्णांक get_caps_क्रम_async_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(dir);
	काष्ठा ceph_dentry_info *di;
	पूर्णांक got = 0, want = CEPH_CAP_खाता_EXCL | CEPH_CAP_सूची_UNLINK;

	spin_lock(&ci->i_ceph_lock);
	अगर ((__ceph_caps_issued(ci, शून्य) & want) == want) अणु
		ceph_take_cap_refs(ci, want, false);
		got = want;
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);

	/* If we didn't get anything, वापस 0 */
	अगर (!got)
		वापस 0;

        spin_lock(&dentry->d_lock);
        di = ceph_dentry(dentry);
	/*
	 * - We are holding Fx, which implies Fs caps.
	 * - Only support async unlink क्रम primary linkage
	 */
	अगर (atomic_पढ़ो(&ci->i_shared_gen) != di->lease_shared_gen ||
	    !(di->flags & CEPH_DENTRY_PRIMARY_LINK))
		want = 0;
        spin_unlock(&dentry->d_lock);

	/* Do we still want what we've got? */
	अगर (want == got)
		वापस got;

	ceph_put_cap_refs(ci, got);
	वापस 0;
पूर्ण

/*
 * सूची_हटाओ and unlink are dअगरfer only by the metadata op code
 */
अटल पूर्णांक ceph_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(dir->i_sb);
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा ceph_mds_request *req;
	bool try_async = ceph_test_mount_opt(fsc, ASYNC_सूचीOPS);
	पूर्णांक err = -EROFS;
	पूर्णांक op;

	अगर (ceph_snap(dir) == CEPH_SNAPसूची) अणु
		/* सूची_हटाओ .snap/foo is RMSNAP */
		करोut("rmsnap dir %p '%pd' dn %p\n", dir, dentry, dentry);
		op = CEPH_MDS_OP_RMSNAP;
	पूर्ण अन्यथा अगर (ceph_snap(dir) == CEPH_NOSNAP) अणु
		करोut("unlink/rmdir dir %p dn %p inode %p\n",
		     dir, dentry, inode);
		op = d_is_dir(dentry) ?
			CEPH_MDS_OP_RMसूची : CEPH_MDS_OP_UNLINK;
	पूर्ण अन्यथा
		जाओ out;
retry:
	req = ceph_mdsc_create_request(mdsc, op, USE_AUTH_MDS);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ out;
	पूर्ण
	req->r_dentry = dget(dentry);
	req->r_num_caps = 2;
	req->r_parent = dir;
	req->r_dentry_drop = CEPH_CAP_खाता_SHARED;
	req->r_dentry_unless = CEPH_CAP_खाता_EXCL;
	req->r_inode_drop = ceph_drop_caps_क्रम_unlink(inode);

	अगर (try_async && op == CEPH_MDS_OP_UNLINK &&
	    (req->r_dir_caps = get_caps_क्रम_async_unlink(dir, dentry))) अणु
		करोut("async unlink on %llu/%.*s caps=%s", ceph_ino(dir),
		     dentry->d_name.len, dentry->d_name.name,
		     ceph_cap_string(req->r_dir_caps));
		set_bit(CEPH_MDS_R_ASYNC, &req->r_req_flags);
		req->r_callback = ceph_async_unlink_cb;
		req->r_old_inode = d_inode(dentry);
		ihold(req->r_old_inode);
		err = ceph_mdsc_submit_request(mdsc, dir, req);
		अगर (!err) अणु
			/*
			 * We have enough caps, so we assume that the unlink
			 * will succeed. Fix up the target inode and dcache.
			 */
			drop_nlink(inode);
			d_delete(dentry);
		पूर्ण अन्यथा अगर (err == -EJUKEBOX) अणु
			try_async = false;
			ceph_mdsc_put_request(req);
			जाओ retry;
		पूर्ण
	पूर्ण अन्यथा अणु
		set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
		err = ceph_mdsc_करो_request(mdsc, dir, req);
		अगर (!err && !req->r_reply_info.head->is_dentry)
			d_delete(dentry);
	पूर्ण

	ceph_mdsc_put_request(req);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ceph_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		       काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		       काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(old_dir->i_sb);
	काष्ठा ceph_mds_request *req;
	पूर्णांक op = CEPH_MDS_OP_RENAME;
	पूर्णांक err;

	अगर (flags)
		वापस -EINVAL;

	अगर (ceph_snap(old_dir) != ceph_snap(new_dir))
		वापस -EXDEV;
	अगर (ceph_snap(old_dir) != CEPH_NOSNAP) अणु
		अगर (old_dir == new_dir && ceph_snap(old_dir) == CEPH_SNAPसूची)
			op = CEPH_MDS_OP_RENAMESNAP;
		अन्यथा
			वापस -EROFS;
	पूर्ण
	/* करोn't allow cross-quota नामs */
	अगर ((old_dir != new_dir) &&
	    (!ceph_quota_is_same_realm(old_dir, new_dir)))
		वापस -EXDEV;

	करोut("rename dir %p dentry %p to dir %p dentry %p\n",
	     old_dir, old_dentry, new_dir, new_dentry);
	req = ceph_mdsc_create_request(mdsc, op, USE_AUTH_MDS);
	अगर (IS_ERR(req))
		वापस PTR_ERR(req);
	ihold(old_dir);
	req->r_dentry = dget(new_dentry);
	req->r_num_caps = 2;
	req->r_old_dentry = dget(old_dentry);
	req->r_old_dentry_dir = old_dir;
	req->r_parent = new_dir;
	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	req->r_old_dentry_drop = CEPH_CAP_खाता_SHARED;
	req->r_old_dentry_unless = CEPH_CAP_खाता_EXCL;
	req->r_dentry_drop = CEPH_CAP_खाता_SHARED;
	req->r_dentry_unless = CEPH_CAP_खाता_EXCL;
	/* release LINK_RDCACHE on source inode (mds will lock it) */
	req->r_old_inode_drop = CEPH_CAP_LINK_SHARED | CEPH_CAP_LINK_EXCL;
	अगर (d_really_is_positive(new_dentry)) अणु
		req->r_inode_drop =
			ceph_drop_caps_क्रम_unlink(d_inode(new_dentry));
	पूर्ण
	err = ceph_mdsc_करो_request(mdsc, old_dir, req);
	अगर (!err && !req->r_reply_info.head->is_dentry) अणु
		/*
		 * Normally d_move() is करोne by fill_trace (called by
		 * करो_request, above).  If there is no trace, we need
		 * to करो it here.
		 */
		d_move(old_dentry, new_dentry);
	पूर्ण
	ceph_mdsc_put_request(req);
	वापस err;
पूर्ण

/*
 * Move dentry to tail of mdsc->dentry_leases list when lease is updated.
 * Leases at front of the list will expire first. (Assume all leases have
 * similar duration)
 *
 * Called under dentry->d_lock.
 */
व्योम __ceph_dentry_lease_touch(काष्ठा ceph_dentry_info *di)
अणु
	काष्ठा dentry *dn = di->dentry;
	काष्ठा ceph_mds_client *mdsc;

	करोut("dentry_lease_touch %p %p '%pd'\n", di, dn, dn);

	di->flags |= CEPH_DENTRY_LEASE_LIST;
	अगर (di->flags & CEPH_DENTRY_SHRINK_LIST) अणु
		di->flags |= CEPH_DENTRY_REFERENCED;
		वापस;
	पूर्ण

	mdsc = ceph_sb_to_client(dn->d_sb)->mdsc;
	spin_lock(&mdsc->dentry_list_lock);
	list_move_tail(&di->lease_list, &mdsc->dentry_leases);
	spin_unlock(&mdsc->dentry_list_lock);
पूर्ण

अटल व्योम __dentry_dir_lease_touch(काष्ठा ceph_mds_client* mdsc,
				     काष्ठा ceph_dentry_info *di)
अणु
	di->flags &= ~(CEPH_DENTRY_LEASE_LIST | CEPH_DENTRY_REFERENCED);
	di->lease_gen = 0;
	di->समय = jअगरfies;
	list_move_tail(&di->lease_list, &mdsc->dentry_dir_leases);
पूर्ण

/*
 * When dir lease is used, add dentry to tail of mdsc->dentry_dir_leases
 * list अगर it's not in the list, otherwise set 'referenced' flag.
 *
 * Called under dentry->d_lock.
 */
व्योम __ceph_dentry_dir_lease_touch(काष्ठा ceph_dentry_info *di)
अणु
	काष्ठा dentry *dn = di->dentry;
	काष्ठा ceph_mds_client *mdsc;

	करोut("dentry_dir_lease_touch %p %p '%pd' (offset 0x%llx)\n",
	     di, dn, dn, di->offset);

	अगर (!list_empty(&di->lease_list)) अणु
		अगर (di->flags & CEPH_DENTRY_LEASE_LIST) अणु
			/* करोn't हटाओ dentry from dentry lease list
			 * अगर its lease is valid */
			अगर (__dentry_lease_is_valid(di))
				वापस;
		पूर्ण अन्यथा अणु
			di->flags |= CEPH_DENTRY_REFERENCED;
			वापस;
		पूर्ण
	पूर्ण

	अगर (di->flags & CEPH_DENTRY_SHRINK_LIST) अणु
		di->flags |= CEPH_DENTRY_REFERENCED;
		di->flags &= ~CEPH_DENTRY_LEASE_LIST;
		वापस;
	पूर्ण

	mdsc = ceph_sb_to_client(dn->d_sb)->mdsc;
	spin_lock(&mdsc->dentry_list_lock);
	__dentry_dir_lease_touch(mdsc, di),
	spin_unlock(&mdsc->dentry_list_lock);
पूर्ण

अटल व्योम __dentry_lease_unlist(काष्ठा ceph_dentry_info *di)
अणु
	काष्ठा ceph_mds_client *mdsc;
	अगर (di->flags & CEPH_DENTRY_SHRINK_LIST)
		वापस;
	अगर (list_empty(&di->lease_list))
		वापस;

	mdsc = ceph_sb_to_client(di->dentry->d_sb)->mdsc;
	spin_lock(&mdsc->dentry_list_lock);
	list_del_init(&di->lease_list);
	spin_unlock(&mdsc->dentry_list_lock);
पूर्ण

क्रमागत अणु
	KEEP	= 0,
	DELETE	= 1,
	TOUCH	= 2,
	STOP	= 4,
पूर्ण;

काष्ठा ceph_lease_walk_control अणु
	bool dir_lease;
	bool expire_dir_lease;
	अचिन्हित दीर्घ nr_to_scan;
	अचिन्हित दीर्घ dir_lease_ttl;
पूर्ण;

अटल अचिन्हित दीर्घ
__dentry_leases_walk(काष्ठा ceph_mds_client *mdsc,
		     काष्ठा ceph_lease_walk_control *lwc,
		     पूर्णांक (*check)(काष्ठा dentry*, व्योम*))
अणु
	काष्ठा ceph_dentry_info *di, *पंचांगp;
	काष्ठा dentry *dentry, *last = शून्य;
	काष्ठा list_head* list;
        LIST_HEAD(dispose);
	अचिन्हित दीर्घ मुक्तd = 0;
	पूर्णांक ret = 0;

	list = lwc->dir_lease ? &mdsc->dentry_dir_leases : &mdsc->dentry_leases;
	spin_lock(&mdsc->dentry_list_lock);
	list_क्रम_each_entry_safe(di, पंचांगp, list, lease_list) अणु
		अगर (!lwc->nr_to_scan)
			अवरोध;
		--lwc->nr_to_scan;

		dentry = di->dentry;
		अगर (last == dentry)
			अवरोध;

		अगर (!spin_trylock(&dentry->d_lock))
			जारी;

		अगर (__lockref_is_dead(&dentry->d_lockref)) अणु
			list_del_init(&di->lease_list);
			जाओ next;
		पूर्ण

		ret = check(dentry, lwc);
		अगर (ret & TOUCH) अणु
			/* move it पूर्णांकo tail of dir lease list */
			__dentry_dir_lease_touch(mdsc, di);
			अगर (!last)
				last = dentry;
		पूर्ण
		अगर (ret & DELETE) अणु
			/* stale lease */
			di->flags &= ~CEPH_DENTRY_REFERENCED;
			अगर (dentry->d_lockref.count > 0) अणु
				/* update_dentry_lease() will re-add
				 * it to lease list, or
				 * ceph_d_delete() will वापस 1 when
				 * last reference is dropped */
				list_del_init(&di->lease_list);
			पूर्ण अन्यथा अणु
				di->flags |= CEPH_DENTRY_SHRINK_LIST;
				list_move_tail(&di->lease_list, &dispose);
				dget_dlock(dentry);
			पूर्ण
		पूर्ण
next:
		spin_unlock(&dentry->d_lock);
		अगर (ret & STOP)
			अवरोध;
	पूर्ण
	spin_unlock(&mdsc->dentry_list_lock);

	जबतक (!list_empty(&dispose)) अणु
		di = list_first_entry(&dispose, काष्ठा ceph_dentry_info,
				      lease_list);
		dentry = di->dentry;
		spin_lock(&dentry->d_lock);

		list_del_init(&di->lease_list);
		di->flags &= ~CEPH_DENTRY_SHRINK_LIST;
		अगर (di->flags & CEPH_DENTRY_REFERENCED) अणु
			spin_lock(&mdsc->dentry_list_lock);
			अगर (di->flags & CEPH_DENTRY_LEASE_LIST) अणु
				list_add_tail(&di->lease_list,
					      &mdsc->dentry_leases);
			पूर्ण अन्यथा अणु
				__dentry_dir_lease_touch(mdsc, di);
			पूर्ण
			spin_unlock(&mdsc->dentry_list_lock);
		पूर्ण अन्यथा अणु
			मुक्तd++;
		पूर्ण

		spin_unlock(&dentry->d_lock);
		/* ceph_d_delete() करोes the trick */
		dput(dentry);
	पूर्ण
	वापस मुक्तd;
पूर्ण

अटल पूर्णांक __dentry_lease_check(काष्ठा dentry *dentry, व्योम *arg)
अणु
	काष्ठा ceph_dentry_info *di = ceph_dentry(dentry);
	पूर्णांक ret;

	अगर (__dentry_lease_is_valid(di))
		वापस STOP;
	ret = __dir_lease_try_check(dentry);
	अगर (ret == -EBUSY)
		वापस KEEP;
	अगर (ret > 0)
		वापस TOUCH;
	वापस DELETE;
पूर्ण

अटल पूर्णांक __dir_lease_check(काष्ठा dentry *dentry, व्योम *arg)
अणु
	काष्ठा ceph_lease_walk_control *lwc = arg;
	काष्ठा ceph_dentry_info *di = ceph_dentry(dentry);

	पूर्णांक ret = __dir_lease_try_check(dentry);
	अगर (ret == -EBUSY)
		वापस KEEP;
	अगर (ret > 0) अणु
		अगर (समय_beक्रमe(jअगरfies, di->समय + lwc->dir_lease_ttl))
			वापस STOP;
		/* Move dentry to tail of dir lease list अगर we करोn't want
		 * to delete it. So dentries in the list are checked in a
		 * round robin manner */
		अगर (!lwc->expire_dir_lease)
			वापस TOUCH;
		अगर (dentry->d_lockref.count > 0 ||
		    (di->flags & CEPH_DENTRY_REFERENCED))
			वापस TOUCH;
		/* invalidate dir lease */
		di->lease_shared_gen = 0;
	पूर्ण
	वापस DELETE;
पूर्ण

पूर्णांक ceph_trim_dentries(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_lease_walk_control lwc;
	अचिन्हित दीर्घ count;
	अचिन्हित दीर्घ मुक्तd;

	spin_lock(&mdsc->caps_list_lock);
        अगर (mdsc->caps_use_max > 0 &&
            mdsc->caps_use_count > mdsc->caps_use_max)
		count = mdsc->caps_use_count - mdsc->caps_use_max;
	अन्यथा
		count = 0;
        spin_unlock(&mdsc->caps_list_lock);

	lwc.dir_lease = false;
	lwc.nr_to_scan  = CEPH_CAPS_PER_RELEASE * 2;
	मुक्तd = __dentry_leases_walk(mdsc, &lwc, __dentry_lease_check);
	अगर (!lwc.nr_to_scan) /* more invalid leases */
		वापस -EAGAIN;

	अगर (lwc.nr_to_scan < CEPH_CAPS_PER_RELEASE)
		lwc.nr_to_scan = CEPH_CAPS_PER_RELEASE;

	lwc.dir_lease = true;
	lwc.expire_dir_lease = मुक्तd < count;
	lwc.dir_lease_ttl = mdsc->fsc->mount_options->caps_wanted_delay_max * HZ;
	मुक्तd +=__dentry_leases_walk(mdsc, &lwc, __dir_lease_check);
	अगर (!lwc.nr_to_scan) /* more to check */
		वापस -EAGAIN;

	वापस मुक्तd > 0 ? 1 : 0;
पूर्ण

/*
 * Ensure a dentry lease will no दीर्घer revalidate.
 */
व्योम ceph_invalidate_dentry_lease(काष्ठा dentry *dentry)
अणु
	काष्ठा ceph_dentry_info *di = ceph_dentry(dentry);
	spin_lock(&dentry->d_lock);
	di->समय = jअगरfies;
	di->lease_shared_gen = 0;
	di->flags &= ~CEPH_DENTRY_PRIMARY_LINK;
	__dentry_lease_unlist(di);
	spin_unlock(&dentry->d_lock);
पूर्ण

/*
 * Check अगर dentry lease is valid.  If not, delete the lease.  Try to
 * renew अगर the least is more than half up.
 */
अटल bool __dentry_lease_is_valid(काष्ठा ceph_dentry_info *di)
अणु
	काष्ठा ceph_mds_session *session;

	अगर (!di->lease_gen)
		वापस false;

	session = di->lease_session;
	अगर (session) अणु
		u32 gen;
		अचिन्हित दीर्घ ttl;

		spin_lock(&session->s_gen_ttl_lock);
		gen = session->s_cap_gen;
		ttl = session->s_cap_ttl;
		spin_unlock(&session->s_gen_ttl_lock);

		अगर (di->lease_gen == gen &&
		    समय_beक्रमe(jअगरfies, ttl) &&
		    समय_beक्रमe(jअगरfies, di->समय))
			वापस true;
	पूर्ण
	di->lease_gen = 0;
	वापस false;
पूर्ण

अटल पूर्णांक dentry_lease_is_valid(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ceph_dentry_info *di;
	काष्ठा ceph_mds_session *session = शून्य;
	u32 seq = 0;
	पूर्णांक valid = 0;

	spin_lock(&dentry->d_lock);
	di = ceph_dentry(dentry);
	अगर (di && __dentry_lease_is_valid(di)) अणु
		valid = 1;

		अगर (di->lease_renew_after &&
		    समय_after(jअगरfies, di->lease_renew_after)) अणु
			/*
			 * We should renew. If we're in RCU walk mode
			 * though, we can't करो that so just वापस
			 * -ECHILD.
			 */
			अगर (flags & LOOKUP_RCU) अणु
				valid = -ECHILD;
			पूर्ण अन्यथा अणु
				session = ceph_get_mds_session(di->lease_session);
				seq = di->lease_seq;
				di->lease_renew_after = 0;
				di->lease_renew_from = jअगरfies;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&dentry->d_lock);

	अगर (session) अणु
		ceph_mdsc_lease_send_msg(session, dentry,
					 CEPH_MDS_LEASE_RENEW, seq);
		ceph_put_mds_session(session);
	पूर्ण
	करोut("dentry_lease_is_valid - dentry %p = %d\n", dentry, valid);
	वापस valid;
पूर्ण

/*
 * Called under dentry->d_lock.
 */
अटल पूर्णांक __dir_lease_try_check(स्थिर काष्ठा dentry *dentry)
अणु
	काष्ठा ceph_dentry_info *di = ceph_dentry(dentry);
	काष्ठा inode *dir;
	काष्ठा ceph_inode_info *ci;
	पूर्णांक valid = 0;

	अगर (!di->lease_shared_gen)
		वापस 0;
	अगर (IS_ROOT(dentry))
		वापस 0;

	dir = d_inode(dentry->d_parent);
	ci = ceph_inode(dir);

	अगर (spin_trylock(&ci->i_ceph_lock)) अणु
		अगर (atomic_पढ़ो(&ci->i_shared_gen) == di->lease_shared_gen &&
		    __ceph_caps_issued_mask(ci, CEPH_CAP_खाता_SHARED, 0))
			valid = 1;
		spin_unlock(&ci->i_ceph_lock);
	पूर्ण अन्यथा अणु
		valid = -EBUSY;
	पूर्ण

	अगर (!valid)
		di->lease_shared_gen = 0;
	वापस valid;
पूर्ण

/*
 * Check अगर directory-wide content lease/cap is valid.
 */
अटल पूर्णांक dir_lease_is_valid(काष्ठा inode *dir, काष्ठा dentry *dentry,
			      काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(dir);
	पूर्णांक valid;
	पूर्णांक shared_gen;

	spin_lock(&ci->i_ceph_lock);
	valid = __ceph_caps_issued_mask(ci, CEPH_CAP_खाता_SHARED, 1);
	अगर (valid) अणु
		__ceph_touch_भ_शेषe(ci, mdsc, CEPH_खाता_MODE_RD);
		shared_gen = atomic_पढ़ो(&ci->i_shared_gen);
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);
	अगर (valid) अणु
		काष्ठा ceph_dentry_info *di;
		spin_lock(&dentry->d_lock);
		di = ceph_dentry(dentry);
		अगर (dir == d_inode(dentry->d_parent) &&
		    di && di->lease_shared_gen == shared_gen)
			__ceph_dentry_dir_lease_touch(di);
		अन्यथा
			valid = 0;
		spin_unlock(&dentry->d_lock);
	पूर्ण
	करोut("dir_lease_is_valid dir %p v%u dentry %p = %d\n",
	     dir, (अचिन्हित)atomic_पढ़ो(&ci->i_shared_gen), dentry, valid);
	वापस valid;
पूर्ण

/*
 * Check अगर cached dentry can be trusted.
 */
अटल पूर्णांक ceph_d_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक valid = 0;
	काष्ठा dentry *parent;
	काष्ठा inode *dir, *inode;
	काष्ठा ceph_mds_client *mdsc;

	अगर (flags & LOOKUP_RCU) अणु
		parent = READ_ONCE(dentry->d_parent);
		dir = d_inode_rcu(parent);
		अगर (!dir)
			वापस -ECHILD;
		inode = d_inode_rcu(dentry);
	पूर्ण अन्यथा अणु
		parent = dget_parent(dentry);
		dir = d_inode(parent);
		inode = d_inode(dentry);
	पूर्ण

	करोut("d_revalidate %p '%pd' inode %p offset 0x%llx\n", dentry,
	     dentry, inode, ceph_dentry(dentry)->offset);

	mdsc = ceph_sb_to_client(dir->i_sb)->mdsc;

	/* always trust cached snapped dentries, snapdir dentry */
	अगर (ceph_snap(dir) != CEPH_NOSNAP) अणु
		करोut("d_revalidate %p '%pd' inode %p is SNAPPED\n", dentry,
		     dentry, inode);
		valid = 1;
	पूर्ण अन्यथा अगर (inode && ceph_snap(inode) == CEPH_SNAPसूची) अणु
		valid = 1;
	पूर्ण अन्यथा अणु
		valid = dentry_lease_is_valid(dentry, flags);
		अगर (valid == -ECHILD)
			वापस valid;
		अगर (valid || dir_lease_is_valid(dir, dentry, mdsc)) अणु
			अगर (inode)
				valid = ceph_is_any_caps(inode);
			अन्यथा
				valid = 1;
		पूर्ण
	पूर्ण

	अगर (!valid) अणु
		काष्ठा ceph_mds_request *req;
		पूर्णांक op, err;
		u32 mask;

		अगर (flags & LOOKUP_RCU)
			वापस -ECHILD;

		percpu_counter_inc(&mdsc->metric.d_lease_mis);

		op = ceph_snap(dir) == CEPH_SNAPसूची ?
			CEPH_MDS_OP_LOOKUPSNAP : CEPH_MDS_OP_LOOKUP;
		req = ceph_mdsc_create_request(mdsc, op, USE_ANY_MDS);
		अगर (!IS_ERR(req)) अणु
			req->r_dentry = dget(dentry);
			req->r_num_caps = 2;
			req->r_parent = dir;

			mask = CEPH_STAT_CAP_INODE | CEPH_CAP_AUTH_SHARED;
			अगर (ceph_security_xattr_wanted(dir))
				mask |= CEPH_CAP_XATTR_SHARED;
			req->r_args.getattr.mask = cpu_to_le32(mask);

			err = ceph_mdsc_करो_request(mdsc, शून्य, req);
			चयन (err) अणु
			हाल 0:
				अगर (d_really_is_positive(dentry) &&
				    d_inode(dentry) == req->r_target_inode)
					valid = 1;
				अवरोध;
			हाल -ENOENT:
				अगर (d_really_is_negative(dentry))
					valid = 1;
				fallthrough;
			शेष:
				अवरोध;
			पूर्ण
			ceph_mdsc_put_request(req);
			करोut("d_revalidate %p lookup result=%d\n",
			     dentry, err);
		पूर्ण
	पूर्ण अन्यथा अणु
		percpu_counter_inc(&mdsc->metric.d_lease_hit);
	पूर्ण

	करोut("d_revalidate %p %s\n", dentry, valid ? "valid" : "invalid");
	अगर (!valid)
		ceph_dir_clear_complete(dir);

	अगर (!(flags & LOOKUP_RCU))
		dput(parent);
	वापस valid;
पूर्ण

/*
 * Delete unused dentry that करोesn't have valid lease
 *
 * Called under dentry->d_lock.
 */
अटल पूर्णांक ceph_d_delete(स्थिर काष्ठा dentry *dentry)
अणु
	काष्ठा ceph_dentry_info *di;

	/* won't release caps */
	अगर (d_really_is_negative(dentry))
		वापस 0;
	अगर (ceph_snap(d_inode(dentry)) != CEPH_NOSNAP)
		वापस 0;
	/* vaild lease? */
	di = ceph_dentry(dentry);
	अगर (di) अणु
		अगर (__dentry_lease_is_valid(di))
			वापस 0;
		अगर (__dir_lease_try_check(dentry))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Release our ceph_dentry_info.
 */
अटल व्योम ceph_d_release(काष्ठा dentry *dentry)
अणु
	काष्ठा ceph_dentry_info *di = ceph_dentry(dentry);
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(dentry->d_sb);

	करोut("d_release %p\n", dentry);

	atomic64_dec(&fsc->mdsc->metric.total_dentries);

	spin_lock(&dentry->d_lock);
	__dentry_lease_unlist(di);
	dentry->d_fsdata = शून्य;
	spin_unlock(&dentry->d_lock);

	अगर (di->lease_session)
		ceph_put_mds_session(di->lease_session);
	kmem_cache_मुक्त(ceph_dentry_cachep, di);
पूर्ण

/*
 * When the VFS prunes a dentry from the cache, we need to clear the
 * complete flag on the parent directory.
 *
 * Called under dentry->d_lock.
 */
अटल व्योम ceph_d_prune(काष्ठा dentry *dentry)
अणु
	काष्ठा ceph_inode_info *dir_ci;
	काष्ठा ceph_dentry_info *di;

	करोut("ceph_d_prune %pd %p\n", dentry, dentry);

	/* करो we have a valid parent? */
	अगर (IS_ROOT(dentry))
		वापस;

	/* we hold d_lock, so d_parent is stable */
	dir_ci = ceph_inode(d_inode(dentry->d_parent));
	अगर (dir_ci->i_vino.snap == CEPH_SNAPसूची)
		वापस;

	/* who calls d_delete() should also disable dcache सूची_पढ़ो */
	अगर (d_really_is_negative(dentry))
		वापस;

	/* d_fsdata करोes not get cleared until d_release */
	अगर (!d_unhashed(dentry)) अणु
		__ceph_dir_clear_complete(dir_ci);
		वापस;
	पूर्ण

	/* Disable dcache सूची_पढ़ो just in हाल that someone called d_drop()
	 * or d_invalidate(), but MDS didn't revoke CEPH_CAP_खाता_SHARED
	 * properly (dcache सूची_पढ़ो is still enabled) */
	di = ceph_dentry(dentry);
	अगर (di->offset > 0 &&
	    di->lease_shared_gen == atomic_पढ़ो(&dir_ci->i_shared_gen))
		__ceph_dir_clear_ordered(dir_ci);
पूर्ण

/*
 * पढ़ो() on a dir.  This weird पूर्णांकerface hack only works अगर mounted
 * with '-o dirstat'.
 */
अटल sमाप_प्रकार ceph_पढ़ो_dir(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार size,
			     loff_t *ppos)
अणु
	काष्ठा ceph_dir_file_info *dfi = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक left;
	स्थिर पूर्णांक bufsize = 1024;

	अगर (!ceph_test_mount_opt(ceph_sb_to_client(inode->i_sb), सूचीSTAT))
		वापस -EISसूची;

	अगर (!dfi->dir_info) अणु
		dfi->dir_info = kदो_स्मृति(bufsize, GFP_KERNEL);
		अगर (!dfi->dir_info)
			वापस -ENOMEM;
		dfi->dir_info_len =
			snम_लिखो(dfi->dir_info, bufsize,
				"entries:   %20lld\n"
				" files:    %20lld\n"
				" subdirs:  %20lld\n"
				"rentries:  %20lld\n"
				" rfiles:   %20lld\n"
				" rsubdirs: %20lld\n"
				"rbytes:    %20lld\n"
				"rctime:    %10lld.%09ld\n",
				ci->i_files + ci->i_subdirs,
				ci->i_files,
				ci->i_subdirs,
				ci->i_rfiles + ci->i_rsubdirs,
				ci->i_rfiles,
				ci->i_rsubdirs,
				ci->i_rbytes,
				ci->i_rस_समय.tv_sec,
				ci->i_rस_समय.tv_nsec);
	पूर्ण

	अगर (*ppos >= dfi->dir_info_len)
		वापस 0;
	size = min_t(अचिन्हित, size, dfi->dir_info_len-*ppos);
	left = copy_to_user(buf, dfi->dir_info + *ppos, size);
	अगर (left == size)
		वापस -EFAULT;
	*ppos += (size - left);
	वापस size - left;
पूर्ण



/*
 * Return name hash क्रम a given dentry.  This is dependent on
 * the parent directory's hash function.
 */
अचिन्हित ceph_dentry_hash(काष्ठा inode *dir, काष्ठा dentry *dn)
अणु
	काष्ठा ceph_inode_info *dci = ceph_inode(dir);
	अचिन्हित hash;

	चयन (dci->i_dir_layout.dl_dir_hash) अणु
	हाल 0:	/* क्रम backward compat */
	हाल CEPH_STR_HASH_LINUX:
		वापस dn->d_name.hash;

	शेष:
		spin_lock(&dn->d_lock);
		hash = ceph_str_hash(dci->i_dir_layout.dl_dir_hash,
				     dn->d_name.name, dn->d_name.len);
		spin_unlock(&dn->d_lock);
		वापस hash;
	पूर्ण
पूर्ण

स्थिर काष्ठा file_operations ceph_dir_fops = अणु
	.पढ़ो = ceph_पढ़ो_dir,
	.iterate = ceph_सूची_पढ़ो,
	.llseek = ceph_dir_llseek,
	.खोलो = ceph_खोलो,
	.release = ceph_release,
	.unlocked_ioctl = ceph_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.fsync = ceph_fsync,
	.lock = ceph_lock,
	.flock = ceph_flock,
पूर्ण;

स्थिर काष्ठा file_operations ceph_snapdir_fops = अणु
	.iterate = ceph_सूची_पढ़ो,
	.llseek = ceph_dir_llseek,
	.खोलो = ceph_खोलो,
	.release = ceph_release,
पूर्ण;

स्थिर काष्ठा inode_operations ceph_dir_iops = अणु
	.lookup = ceph_lookup,
	.permission = ceph_permission,
	.getattr = ceph_getattr,
	.setattr = ceph_setattr,
	.listxattr = ceph_listxattr,
	.get_acl = ceph_get_acl,
	.set_acl = ceph_set_acl,
	.mknod = ceph_mknod,
	.symlink = ceph_symlink,
	.सूची_गढ़ो = ceph_सूची_गढ़ो,
	.link = ceph_link,
	.unlink = ceph_unlink,
	.सूची_हटाओ = ceph_unlink,
	.नाम = ceph_नाम,
	.create = ceph_create,
	.atomic_खोलो = ceph_atomic_खोलो,
पूर्ण;

स्थिर काष्ठा inode_operations ceph_snapdir_iops = अणु
	.lookup = ceph_lookup,
	.permission = ceph_permission,
	.getattr = ceph_getattr,
	.सूची_गढ़ो = ceph_सूची_गढ़ो,
	.सूची_हटाओ = ceph_unlink,
	.नाम = ceph_नाम,
पूर्ण;

स्थिर काष्ठा dentry_operations ceph_dentry_ops = अणु
	.d_revalidate = ceph_d_revalidate,
	.d_delete = ceph_d_delete,
	.d_release = ceph_d_release,
	.d_prune = ceph_d_prune,
	.d_init = ceph_d_init,
पूर्ण;
