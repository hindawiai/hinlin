<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>
#समावेश <linux/ceph/striper.h>

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/fभाग.स>
#समावेश <linux/iversion.h>
#समावेश <linux/kसमय.स>

#समावेश "super.h"
#समावेश "mds_client.h"
#समावेश "cache.h"
#समावेश "io.h"
#समावेश "metric.h"

अटल __le32 ceph_flags_sys2wire(u32 flags)
अणु
	u32 wire_flags = 0;

	चयन (flags & O_ACCMODE) अणु
	हाल O_RDONLY:
		wire_flags |= CEPH_O_RDONLY;
		अवरोध;
	हाल O_WRONLY:
		wire_flags |= CEPH_O_WRONLY;
		अवरोध;
	हाल O_RDWR:
		wire_flags |= CEPH_O_RDWR;
		अवरोध;
	पूर्ण

	flags &= ~O_ACCMODE;

#घोषणा ceph_sys2wire(a) अगर (flags & a) अणु wire_flags |= CEPH_##a; flags &= ~a; पूर्ण

	ceph_sys2wire(O_CREAT);
	ceph_sys2wire(O_EXCL);
	ceph_sys2wire(O_TRUNC);
	ceph_sys2wire(O_सूचीECTORY);
	ceph_sys2wire(O_NOFOLLOW);

#अघोषित ceph_sys2wire

	अगर (flags)
		करोut("unused open flags: %x\n", flags);

	वापस cpu_to_le32(wire_flags);
पूर्ण

/*
 * Ceph file operations
 *
 * Implement basic खोलो/बंद functionality, and implement
 * पढ़ो/ग_लिखो.
 *
 * We implement three modes of file I/O:
 *  - buffered uses the generic_file_aio_अणुपढ़ो,ग_लिखोपूर्ण helpers
 *
 *  - synchronous is used when there is multi-client पढ़ो/ग_लिखो
 *    sharing, aव्योमs the page cache, and synchronously रुकोs क्रम an
 *    ack from the OSD.
 *
 *  - direct io takes the variant of the sync path that references
 *    user pages directly.
 *
 * fsync() flushes and रुकोs on dirty pages, but just queues metadata
 * क्रम ग_लिखोback: since the MDS can recover size and mसमय there is no
 * need to रुको क्रम MDS acknowledgement.
 */

/*
 * How many pages to get in one call to iov_iter_get_pages().  This
 * determines the size of the on-stack array used as a buffer.
 */
#घोषणा ITER_GET_BVECS_PAGES	64

अटल sमाप_प्रकार __iter_get_bvecs(काष्ठा iov_iter *iter, माप_प्रकार maxsize,
				काष्ठा bio_vec *bvecs)
अणु
	माप_प्रकार size = 0;
	पूर्णांक bvec_idx = 0;

	अगर (maxsize > iov_iter_count(iter))
		maxsize = iov_iter_count(iter);

	जबतक (size < maxsize) अणु
		काष्ठा page *pages[ITER_GET_BVECS_PAGES];
		sमाप_प्रकार bytes;
		माप_प्रकार start;
		पूर्णांक idx = 0;

		bytes = iov_iter_get_pages(iter, pages, maxsize - size,
					   ITER_GET_BVECS_PAGES, &start);
		अगर (bytes < 0)
			वापस size ?: bytes;

		iov_iter_advance(iter, bytes);
		size += bytes;

		क्रम ( ; bytes; idx++, bvec_idx++) अणु
			काष्ठा bio_vec bv = अणु
				.bv_page = pages[idx],
				.bv_len = min_t(पूर्णांक, bytes, PAGE_SIZE - start),
				.bv_offset = start,
			पूर्ण;

			bvecs[bvec_idx] = bv;
			bytes -= bv.bv_len;
			start = 0;
		पूर्ण
	पूर्ण

	वापस size;
पूर्ण

/*
 * iov_iter_get_pages() only considers one iov_iter segment, no matter
 * what maxsize or maxpages are given.  For ITER_BVEC that is a single
 * page.
 *
 * Attempt to get up to @maxsize bytes worth of pages from @iter.
 * Return the number of bytes in the created bio_vec array, or an error.
 */
अटल sमाप_प्रकार iter_get_bvecs_alloc(काष्ठा iov_iter *iter, माप_प्रकार maxsize,
				    काष्ठा bio_vec **bvecs, पूर्णांक *num_bvecs)
अणु
	काष्ठा bio_vec *bv;
	माप_प्रकार orig_count = iov_iter_count(iter);
	sमाप_प्रकार bytes;
	पूर्णांक npages;

	iov_iter_truncate(iter, maxsize);
	npages = iov_iter_npages(iter, पूर्णांक_उच्च);
	iov_iter_reexpand(iter, orig_count);

	/*
	 * __iter_get_bvecs() may populate only part of the array -- zero it
	 * out.
	 */
	bv = kvदो_स्मृति_array(npages, माप(*bv), GFP_KERNEL | __GFP_ZERO);
	अगर (!bv)
		वापस -ENOMEM;

	bytes = __iter_get_bvecs(iter, maxsize, bv);
	अगर (bytes < 0) अणु
		/*
		 * No pages were pinned -- just मुक्त the array.
		 */
		kvमुक्त(bv);
		वापस bytes;
	पूर्ण

	*bvecs = bv;
	*num_bvecs = npages;
	वापस bytes;
पूर्ण

अटल व्योम put_bvecs(काष्ठा bio_vec *bvecs, पूर्णांक num_bvecs, bool should_dirty)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_bvecs; i++) अणु
		अगर (bvecs[i].bv_page) अणु
			अगर (should_dirty)
				set_page_dirty_lock(bvecs[i].bv_page);
			put_page(bvecs[i].bv_page);
		पूर्ण
	पूर्ण
	kvमुक्त(bvecs);
पूर्ण

/*
 * Prepare an खोलो request.  Pपुनः_स्मृतिate ceph_cap to aव्योम an
 * inopportune ENOMEM later.
 */
अटल काष्ठा ceph_mds_request *
prepare_खोलो_request(काष्ठा super_block *sb, पूर्णांक flags, पूर्णांक create_mode)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(sb);
	काष्ठा ceph_mds_request *req;
	पूर्णांक want_auth = USE_ANY_MDS;
	पूर्णांक op = (flags & O_CREAT) ? CEPH_MDS_OP_CREATE : CEPH_MDS_OP_OPEN;

	अगर (flags & (O_WRONLY|O_RDWR|O_CREAT|O_TRUNC))
		want_auth = USE_AUTH_MDS;

	req = ceph_mdsc_create_request(mdsc, op, want_auth);
	अगर (IS_ERR(req))
		जाओ out;
	req->r_भ_शेषe = ceph_flags_to_mode(flags);
	req->r_args.खोलो.flags = ceph_flags_sys2wire(flags);
	req->r_args.खोलो.mode = cpu_to_le32(create_mode);
out:
	वापस req;
पूर्ण

अटल पूर्णांक ceph_init_file_info(काष्ठा inode *inode, काष्ठा file *file,
					पूर्णांक भ_शेषe, bool isdir)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_file_info *fi;

	करोut("%s %p %p 0%o (%s)\n", __func__, inode, file,
			inode->i_mode, isdir ? "dir" : "regular");
	BUG_ON(inode->i_fop->release != ceph_release);

	अगर (isdir) अणु
		काष्ठा ceph_dir_file_info *dfi =
			kmem_cache_zalloc(ceph_dir_file_cachep, GFP_KERNEL);
		अगर (!dfi)
			वापस -ENOMEM;

		file->निजी_data = dfi;
		fi = &dfi->file_info;
		dfi->next_offset = 2;
		dfi->सूची_पढ़ो_cache_idx = -1;
	पूर्ण अन्यथा अणु
		fi = kmem_cache_zalloc(ceph_file_cachep, GFP_KERNEL);
		अगर (!fi)
			वापस -ENOMEM;

		file->निजी_data = fi;
	पूर्ण

	ceph_get_भ_शेषe(ci, भ_शेषe, 1);
	fi->भ_शेषe = भ_शेषe;

	spin_lock_init(&fi->rw_contexts_lock);
	INIT_LIST_HEAD(&fi->rw_contexts);
	fi->meta_err = errseq_sample(&ci->i_meta_err);
	fi->filp_gen = READ_ONCE(ceph_inode_to_client(inode)->filp_gen);

	वापस 0;
पूर्ण

/*
 * initialize निजी काष्ठा file data.
 * अगर we fail, clean up by dropping भ_शेषe reference on the ceph_inode
 */
अटल पूर्णांक ceph_init_file(काष्ठा inode *inode, काष्ठा file *file, पूर्णांक भ_शेषe)
अणु
	पूर्णांक ret = 0;

	चयन (inode->i_mode & S_IFMT) अणु
	हाल S_IFREG:
		ceph_fscache_रेजिस्टर_inode_cookie(inode);
		ceph_fscache_file_set_cookie(inode, file);
		fallthrough;
	हाल S_IFसूची:
		ret = ceph_init_file_info(inode, file, भ_शेषe,
						S_ISसूची(inode->i_mode));
		अवरोध;

	हाल S_IFLNK:
		करोut("init_file %p %p 0%o (symlink)\n", inode, file,
		     inode->i_mode);
		अवरोध;

	शेष:
		करोut("init_file %p %p 0%o (special)\n", inode, file,
		     inode->i_mode);
		/*
		 * we need to drop the खोलो ref now, since we करोn't
		 * have .release set to ceph_release.
		 */
		BUG_ON(inode->i_fop->release == ceph_release);

		/* call the proper खोलो fop */
		ret = inode->i_fop->खोलो(inode, file);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * try renew caps after session माला_लो समाप्तed.
 */
पूर्णांक ceph_renew_caps(काष्ठा inode *inode, पूर्णांक भ_शेषe)
अणु
	काष्ठा ceph_mds_client *mdsc = ceph_sb_to_mdsc(inode->i_sb);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_mds_request *req;
	पूर्णांक err, flags, wanted;

	spin_lock(&ci->i_ceph_lock);
	__ceph_touch_भ_शेषe(ci, mdsc, भ_शेषe);
	wanted = __ceph_caps_file_wanted(ci);
	अगर (__ceph_is_any_real_caps(ci) &&
	    (!(wanted & CEPH_CAP_ANY_WR) || ci->i_auth_cap)) अणु
		पूर्णांक issued = __ceph_caps_issued(ci, शून्य);
		spin_unlock(&ci->i_ceph_lock);
		करोut("renew caps %p want %s issued %s updating mds_wanted\n",
		     inode, ceph_cap_string(wanted), ceph_cap_string(issued));
		ceph_check_caps(ci, 0, शून्य);
		वापस 0;
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);

	flags = 0;
	अगर ((wanted & CEPH_CAP_खाता_RD) && (wanted & CEPH_CAP_खाता_WR))
		flags = O_RDWR;
	अन्यथा अगर (wanted & CEPH_CAP_खाता_RD)
		flags = O_RDONLY;
	अन्यथा अगर (wanted & CEPH_CAP_खाता_WR)
		flags = O_WRONLY;
#अगर_घोषित O_LAZY
	अगर (wanted & CEPH_CAP_खाता_LAZYIO)
		flags |= O_LAZY;
#पूर्ण_अगर

	req = prepare_खोलो_request(inode->i_sb, flags, 0);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->r_inode = inode;
	ihold(inode);
	req->r_num_caps = 1;

	err = ceph_mdsc_करो_request(mdsc, शून्य, req);
	ceph_mdsc_put_request(req);
out:
	करोut("renew caps %p open result=%d\n", inode, err);
	वापस err < 0 ? err : 0;
पूर्ण

/*
 * If we alपढ़ोy have the requisite capabilities, we can satisfy
 * the खोलो request locally (no need to request new caps from the
 * MDS).  We करो, however, need to inक्रमm the MDS (asynchronously)
 * अगर our wanted caps set expands.
 */
पूर्णांक ceph_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(inode->i_sb);
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	काष्ठा ceph_mds_request *req;
	काष्ठा ceph_file_info *fi = file->निजी_data;
	पूर्णांक err;
	पूर्णांक flags, भ_शेषe, wanted;

	अगर (fi) अणु
		करोut("open file %p is already opened\n", file);
		वापस 0;
	पूर्ण

	/* filter out O_CREAT|O_EXCL; vfs did that alपढ़ोy.  yuck. */
	flags = file->f_flags & ~(O_CREAT|O_EXCL);
	अगर (S_ISसूची(inode->i_mode))
		flags = O_सूचीECTORY;  /* mds likes to know */

	करोut("open inode %p ino %llx.%llx file %p flags %d (%d)\n", inode,
	     ceph_vinop(inode), file, flags, file->f_flags);
	भ_शेषe = ceph_flags_to_mode(flags);
	wanted = ceph_caps_क्रम_mode(भ_शेषe);

	/* snapped files are पढ़ो-only */
	अगर (ceph_snap(inode) != CEPH_NOSNAP && (file->f_mode & FMODE_WRITE))
		वापस -EROFS;

	/* trivially खोलो snapdir */
	अगर (ceph_snap(inode) == CEPH_SNAPसूची) अणु
		वापस ceph_init_file(inode, file, भ_शेषe);
	पूर्ण

	/*
	 * No need to block अगर we have caps on the auth MDS (क्रम
	 * ग_लिखो) or any MDS (क्रम पढ़ो).  Update wanted set
	 * asynchronously.
	 */
	spin_lock(&ci->i_ceph_lock);
	अगर (__ceph_is_any_real_caps(ci) &&
	    (((भ_शेषe & CEPH_खाता_MODE_WR) == 0) || ci->i_auth_cap)) अणु
		पूर्णांक mds_wanted = __ceph_caps_mds_wanted(ci, true);
		पूर्णांक issued = __ceph_caps_issued(ci, शून्य);

		करोut("open %p fmode %d want %s issued %s using existing\n",
		     inode, भ_शेषe, ceph_cap_string(wanted),
		     ceph_cap_string(issued));
		__ceph_touch_भ_शेषe(ci, mdsc, भ_शेषe);
		spin_unlock(&ci->i_ceph_lock);

		/* adjust wanted? */
		अगर ((issued & wanted) != wanted &&
		    (mds_wanted & wanted) != wanted &&
		    ceph_snap(inode) != CEPH_SNAPसूची)
			ceph_check_caps(ci, 0, शून्य);

		वापस ceph_init_file(inode, file, भ_शेषe);
	पूर्ण अन्यथा अगर (ceph_snap(inode) != CEPH_NOSNAP &&
		   (ci->i_snap_caps & wanted) == wanted) अणु
		__ceph_touch_भ_शेषe(ci, mdsc, भ_शेषe);
		spin_unlock(&ci->i_ceph_lock);
		वापस ceph_init_file(inode, file, भ_शेषe);
	पूर्ण

	spin_unlock(&ci->i_ceph_lock);

	करोut("open fmode %d wants %s\n", भ_शेषe, ceph_cap_string(wanted));
	req = prepare_खोलो_request(inode->i_sb, flags, 0);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ out;
	पूर्ण
	req->r_inode = inode;
	ihold(inode);

	req->r_num_caps = 1;
	err = ceph_mdsc_करो_request(mdsc, शून्य, req);
	अगर (!err)
		err = ceph_init_file(inode, file, req->r_भ_शेषe);
	ceph_mdsc_put_request(req);
	करोut("open result=%d on %llx.%llx\n", err, ceph_vinop(inode));
out:
	वापस err;
पूर्ण

/* Clone the layout from a synchronous create, अगर the dir now has Dc caps */
अटल व्योम
cache_file_layout(काष्ठा inode *dst, काष्ठा inode *src)
अणु
	काष्ठा ceph_inode_info *cdst = ceph_inode(dst);
	काष्ठा ceph_inode_info *csrc = ceph_inode(src);

	spin_lock(&cdst->i_ceph_lock);
	अगर ((__ceph_caps_issued(cdst, शून्य) & CEPH_CAP_सूची_CREATE) &&
	    !ceph_file_layout_is_valid(&cdst->i_cached_layout)) अणु
		स_नकल(&cdst->i_cached_layout, &csrc->i_layout,
			माप(cdst->i_cached_layout));
		rcu_assign_poपूर्णांकer(cdst->i_cached_layout.pool_ns,
				   ceph_try_get_string(csrc->i_layout.pool_ns));
	पूर्ण
	spin_unlock(&cdst->i_ceph_lock);
पूर्ण

/*
 * Try to set up an async create. We need caps, a file layout, and inode number,
 * and either a lease on the dentry or complete dir info. If any of those
 * criteria are not satisfied, then वापस false and the caller can go
 * synchronous.
 */
अटल पूर्णांक try_prep_async_create(काष्ठा inode *dir, काष्ठा dentry *dentry,
				 काष्ठा ceph_file_layout *lo, u64 *pino)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(dir);
	काष्ठा ceph_dentry_info *di = ceph_dentry(dentry);
	पूर्णांक got = 0, want = CEPH_CAP_खाता_EXCL | CEPH_CAP_सूची_CREATE;
	u64 ino;

	spin_lock(&ci->i_ceph_lock);
	/* No auth cap means no chance क्रम Dc caps */
	अगर (!ci->i_auth_cap)
		जाओ no_async;

	/* Any delegated inos? */
	अगर (xa_empty(&ci->i_auth_cap->session->s_delegated_inos))
		जाओ no_async;

	अगर (!ceph_file_layout_is_valid(&ci->i_cached_layout))
		जाओ no_async;

	अगर ((__ceph_caps_issued(ci, शून्य) & want) != want)
		जाओ no_async;

	अगर (d_in_lookup(dentry)) अणु
		अगर (!__ceph_dir_is_complete(ci))
			जाओ no_async;
		spin_lock(&dentry->d_lock);
		di->lease_shared_gen = atomic_पढ़ो(&ci->i_shared_gen);
		spin_unlock(&dentry->d_lock);
	पूर्ण अन्यथा अगर (atomic_पढ़ो(&ci->i_shared_gen) !=
		   READ_ONCE(di->lease_shared_gen)) अणु
		जाओ no_async;
	पूर्ण

	ino = ceph_get_deleg_ino(ci->i_auth_cap->session);
	अगर (!ino)
		जाओ no_async;

	*pino = ino;
	ceph_take_cap_refs(ci, want, false);
	स_नकल(lo, &ci->i_cached_layout, माप(*lo));
	rcu_assign_poपूर्णांकer(lo->pool_ns,
			   ceph_try_get_string(ci->i_cached_layout.pool_ns));
	got = want;
no_async:
	spin_unlock(&ci->i_ceph_lock);
	वापस got;
पूर्ण

अटल व्योम restore_deleg_ino(काष्ठा inode *dir, u64 ino)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(dir);
	काष्ठा ceph_mds_session *s = शून्य;

	spin_lock(&ci->i_ceph_lock);
	अगर (ci->i_auth_cap)
		s = ceph_get_mds_session(ci->i_auth_cap->session);
	spin_unlock(&ci->i_ceph_lock);
	अगर (s) अणु
		पूर्णांक err = ceph_restore_deleg_ino(s, ino);
		अगर (err)
			pr_warn("ceph: unable to restore delegated ino 0x%llx to session: %d\n",
				ino, err);
		ceph_put_mds_session(s);
	पूर्ण
पूर्ण

अटल व्योम ceph_async_create_cb(काष्ठा ceph_mds_client *mdsc,
                                 काष्ठा ceph_mds_request *req)
अणु
	पूर्णांक result = req->r_err ? req->r_err :
			le32_to_cpu(req->r_reply_info.head->result);

	अगर (result == -EJUKEBOX)
		जाओ out;

	mapping_set_error(req->r_parent->i_mapping, result);

	अगर (result) अणु
		काष्ठा dentry *dentry = req->r_dentry;
		पूर्णांक pathlen = 0;
		u64 base = 0;
		अक्षर *path = ceph_mdsc_build_path(req->r_dentry, &pathlen,
						  &base, 0);

		ceph_dir_clear_complete(req->r_parent);
		अगर (!d_unhashed(dentry))
			d_drop(dentry);

		/* FIXME: start वापसing I/O errors on all accesses? */
		pr_warn("ceph: async create failure path=(%llx)%s result=%d!\n",
			base, IS_ERR(path) ? "<<bad>>" : path, result);
		ceph_mdsc_मुक्त_path(path, pathlen);
	पूर्ण

	अगर (req->r_target_inode) अणु
		काष्ठा ceph_inode_info *ci = ceph_inode(req->r_target_inode);
		u64 ino = ceph_vino(req->r_target_inode).ino;

		अगर (req->r_deleg_ino != ino)
			pr_warn("%s: inode number mismatch! err=%d deleg_ino=0x%llx target=0x%llx\n",
				__func__, req->r_err, req->r_deleg_ino, ino);
		mapping_set_error(req->r_target_inode->i_mapping, result);

		spin_lock(&ci->i_ceph_lock);
		अगर (ci->i_ceph_flags & CEPH_I_ASYNC_CREATE) अणु
			ci->i_ceph_flags &= ~CEPH_I_ASYNC_CREATE;
			wake_up_bit(&ci->i_ceph_flags, CEPH_ASYNC_CREATE_BIT);
		पूर्ण
		ceph_kick_flushing_inode_caps(req->r_session, ci);
		spin_unlock(&ci->i_ceph_lock);
	पूर्ण अन्यथा अणु
		pr_warn("%s: no req->r_target_inode for 0x%llx\n", __func__,
			req->r_deleg_ino);
	पूर्ण
out:
	ceph_mdsc_release_dir_caps(req);
पूर्ण

अटल पूर्णांक ceph_finish_async_create(काष्ठा inode *dir, काष्ठा dentry *dentry,
				    काष्ठा file *file, umode_t mode,
				    काष्ठा ceph_mds_request *req,
				    काष्ठा ceph_acl_sec_ctx *as_ctx,
				    काष्ठा ceph_file_layout *lo)
अणु
	पूर्णांक ret;
	अक्षर xattr_buf[4];
	काष्ठा ceph_mds_reply_inode in = अणु पूर्ण;
	काष्ठा ceph_mds_reply_info_in iinfo = अणु .in = &in पूर्ण;
	काष्ठा ceph_inode_info *ci = ceph_inode(dir);
	काष्ठा inode *inode;
	काष्ठा बारpec64 now;
	काष्ठा ceph_vino vino = अणु .ino = req->r_deleg_ino,
				  .snap = CEPH_NOSNAP पूर्ण;

	kसमय_get_real_ts64(&now);

	inode = ceph_get_inode(dentry->d_sb, vino);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	iinfo.अंतरभूत_version = CEPH_INLINE_NONE;
	iinfo.change_attr = 1;
	ceph_encode_बारpec64(&iinfo.bसमय, &now);

	iinfo.xattr_len = ARRAY_SIZE(xattr_buf);
	iinfo.xattr_data = xattr_buf;
	स_रखो(iinfo.xattr_data, 0, iinfo.xattr_len);

	in.ino = cpu_to_le64(vino.ino);
	in.snapid = cpu_to_le64(CEPH_NOSNAP);
	in.version = cpu_to_le64(1);	// ???
	in.cap.caps = in.cap.wanted = cpu_to_le32(CEPH_CAP_ALL_खाता);
	in.cap.cap_id = cpu_to_le64(1);
	in.cap.realm = cpu_to_le64(ci->i_snap_realm->ino);
	in.cap.flags = CEPH_CAP_FLAG_AUTH;
	in.स_समय = in.mसमय = in.aसमय = iinfo.bसमय;
	in.mode = cpu_to_le32((u32)mode);
	in.truncate_seq = cpu_to_le32(1);
	in.truncate_size = cpu_to_le64(-1ULL);
	in.xattr_version = cpu_to_le64(1);
	in.uid = cpu_to_le32(from_kuid(&init_user_ns, current_fsuid()));
	in.gid = cpu_to_le32(from_kgid(&init_user_ns, dir->i_mode & S_ISGID ?
				dir->i_gid : current_fsgid()));
	in.nlink = cpu_to_le32(1);
	in.max_size = cpu_to_le64(lo->stripe_unit);

	ceph_file_layout_to_legacy(lo, &in.layout);

	ret = ceph_fill_inode(inode, शून्य, &iinfo, शून्य, req->r_session,
			      req->r_भ_शेषe, शून्य);
	अगर (ret) अणु
		करोut("%s failed to fill inode: %d\n", __func__, ret);
		ceph_dir_clear_complete(dir);
		अगर (!d_unhashed(dentry))
			d_drop(dentry);
		अगर (inode->i_state & I_NEW)
			discard_new_inode(inode);
	पूर्ण अन्यथा अणु
		काष्ठा dentry *dn;

		करोut("%s d_adding new inode 0x%llx to 0x%llx/%s\n", __func__,
			vino.ino, ceph_ino(dir), dentry->d_name.name);
		ceph_dir_clear_ordered(dir);
		ceph_init_inode_acls(inode, as_ctx);
		अगर (inode->i_state & I_NEW) अणु
			/*
			 * If it's not I_NEW, then someone created this beक्रमe
			 * we got here. Assume the server is aware of it at
			 * that poपूर्णांक and करोn't worry about setting
			 * CEPH_I_ASYNC_CREATE.
			 */
			ceph_inode(inode)->i_ceph_flags = CEPH_I_ASYNC_CREATE;
			unlock_new_inode(inode);
		पूर्ण
		अगर (d_in_lookup(dentry) || d_really_is_negative(dentry)) अणु
			अगर (!d_unhashed(dentry))
				d_drop(dentry);
			dn = d_splice_alias(inode, dentry);
			WARN_ON_ONCE(dn && dn != dentry);
		पूर्ण
		file->f_mode |= FMODE_CREATED;
		ret = finish_खोलो(file, dentry, ceph_खोलो);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Do a lookup + खोलो with a single request.  If we get a non-existent
 * file or symlink, वापस 1 so the VFS can retry.
 */
पूर्णांक ceph_atomic_खोलो(काष्ठा inode *dir, काष्ठा dentry *dentry,
		     काष्ठा file *file, अचिन्हित flags, umode_t mode)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_sb_to_client(dir->i_sb);
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	काष्ठा ceph_mds_request *req;
	काष्ठा dentry *dn;
	काष्ठा ceph_acl_sec_ctx as_ctx = अणुपूर्ण;
	bool try_async = ceph_test_mount_opt(fsc, ASYNC_सूचीOPS);
	पूर्णांक mask;
	पूर्णांक err;

	करोut("atomic_open %p dentry %p '%pd' %s flags %d mode 0%o\n",
	     dir, dentry, dentry,
	     d_unhashed(dentry) ? "unhashed" : "hashed", flags, mode);

	अगर (dentry->d_name.len > NAME_MAX)
		वापस -ENAMETOOLONG;

	अगर (flags & O_CREAT) अणु
		अगर (ceph_quota_is_max_files_exceeded(dir))
			वापस -EDQUOT;
		err = ceph_pre_init_acls(dir, &mode, &as_ctx);
		अगर (err < 0)
			वापस err;
		err = ceph_security_init_secctx(dentry, mode, &as_ctx);
		अगर (err < 0)
			जाओ out_ctx;
	पूर्ण अन्यथा अगर (!d_in_lookup(dentry)) अणु
		/* If it's not being looked up, it's negative */
		वापस -ENOENT;
	पूर्ण
retry:
	/* करो the खोलो */
	req = prepare_खोलो_request(dir->i_sb, flags, mode);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ out_ctx;
	पूर्ण
	req->r_dentry = dget(dentry);
	req->r_num_caps = 2;
	mask = CEPH_STAT_CAP_INODE | CEPH_CAP_AUTH_SHARED;
	अगर (ceph_security_xattr_wanted(dir))
		mask |= CEPH_CAP_XATTR_SHARED;
	req->r_args.खोलो.mask = cpu_to_le32(mask);
	req->r_parent = dir;

	अगर (flags & O_CREAT) अणु
		काष्ठा ceph_file_layout lo;

		req->r_dentry_drop = CEPH_CAP_खाता_SHARED | CEPH_CAP_AUTH_EXCL;
		req->r_dentry_unless = CEPH_CAP_खाता_EXCL;
		अगर (as_ctx.pagelist) अणु
			req->r_pagelist = as_ctx.pagelist;
			as_ctx.pagelist = शून्य;
		पूर्ण
		अगर (try_async &&
		    (req->r_dir_caps =
		      try_prep_async_create(dir, dentry, &lo,
					    &req->r_deleg_ino))) अणु
			set_bit(CEPH_MDS_R_ASYNC, &req->r_req_flags);
			req->r_args.खोलो.flags |= cpu_to_le32(CEPH_O_EXCL);
			req->r_callback = ceph_async_create_cb;
			err = ceph_mdsc_submit_request(mdsc, dir, req);
			अगर (!err) अणु
				err = ceph_finish_async_create(dir, dentry,
							file, mode, req,
							&as_ctx, &lo);
			पूर्ण अन्यथा अगर (err == -EJUKEBOX) अणु
				restore_deleg_ino(dir, req->r_deleg_ino);
				ceph_mdsc_put_request(req);
				try_async = false;
				जाओ retry;
			पूर्ण
			जाओ out_req;
		पूर्ण
	पूर्ण

	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	err = ceph_mdsc_करो_request(mdsc,
				   (flags & (O_CREAT|O_TRUNC)) ? dir : शून्य,
				   req);
	dentry = ceph_handle_snapdir(req, dentry, err);
	अगर (IS_ERR(dentry)) अणु
		err = PTR_ERR(dentry);
		जाओ out_req;
	पूर्ण
	err = 0;

	अगर ((flags & O_CREAT) && !req->r_reply_info.head->is_dentry)
		err = ceph_handle_notrace_create(dir, dentry);

	अगर (d_in_lookup(dentry)) अणु
		dn = ceph_finish_lookup(req, dentry, err);
		अगर (IS_ERR(dn))
			err = PTR_ERR(dn);
	पूर्ण अन्यथा अणु
		/* we were given a hashed negative dentry */
		dn = शून्य;
	पूर्ण
	अगर (err)
		जाओ out_req;
	अगर (dn || d_really_is_negative(dentry) || d_is_symlink(dentry)) अणु
		/* make vfs retry on splice, ENOENT, or symlink */
		करोut("atomic_open finish_no_open on dn %p\n", dn);
		err = finish_no_खोलो(file, dn);
	पूर्ण अन्यथा अणु
		करोut("atomic_open finish_open on dn %p\n", dn);
		अगर (req->r_op == CEPH_MDS_OP_CREATE && req->r_reply_info.has_create_ino) अणु
			काष्ठा inode *newino = d_inode(dentry);

			cache_file_layout(dir, newino);
			ceph_init_inode_acls(newino, &as_ctx);
			file->f_mode |= FMODE_CREATED;
		पूर्ण
		err = finish_खोलो(file, dentry, ceph_खोलो);
	पूर्ण
out_req:
	ceph_mdsc_put_request(req);
out_ctx:
	ceph_release_acl_sec_ctx(&as_ctx);
	करोut("atomic_open result=%d\n", err);
	वापस err;
पूर्ण

पूर्णांक ceph_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);

	अगर (S_ISसूची(inode->i_mode)) अणु
		काष्ठा ceph_dir_file_info *dfi = file->निजी_data;
		करोut("release inode %p dir file %p\n", inode, file);
		WARN_ON(!list_empty(&dfi->file_info.rw_contexts));

		ceph_put_भ_शेषe(ci, dfi->file_info.भ_शेषe, 1);

		अगर (dfi->last_सूची_पढ़ो)
			ceph_mdsc_put_request(dfi->last_सूची_पढ़ो);
		kमुक्त(dfi->last_name);
		kमुक्त(dfi->dir_info);
		kmem_cache_मुक्त(ceph_dir_file_cachep, dfi);
	पूर्ण अन्यथा अणु
		काष्ठा ceph_file_info *fi = file->निजी_data;
		करोut("release inode %p regular file %p\n", inode, file);
		WARN_ON(!list_empty(&fi->rw_contexts));

		ceph_put_भ_शेषe(ci, fi->भ_शेषe, 1);

		kmem_cache_मुक्त(ceph_file_cachep, fi);
	पूर्ण

	/* wake up anyone रुकोing क्रम caps on this inode */
	wake_up_all(&ci->i_cap_wq);
	वापस 0;
पूर्ण

क्रमागत अणु
	HAVE_RETRIED = 1,
	CHECK_खातापूर्ण =    2,
	READ_INLINE =  3,
पूर्ण;

/*
 * Completely synchronous पढ़ो and ग_लिखो methods.  Direct from __user
 * buffer to osd, or directly to user pages (अगर O_सूचीECT).
 *
 * If the पढ़ो spans object boundary, just करो multiple पढ़ोs.  (That's not
 * atomic, but good enough क्रम now.)
 *
 * If we get a लघु result from the OSD, check against i_size; we need to
 * only वापस a लघु पढ़ो to the caller अगर we hit खातापूर्ण.
 */
अटल sमाप_प्रकार ceph_sync_पढ़ो(काष्ठा kiocb *iocb, काष्ठा iov_iter *to,
			      पूर्णांक *retry_op)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_osd_client *osdc = &fsc->client->osdc;
	sमाप_प्रकार ret;
	u64 off = iocb->ki_pos;
	u64 len = iov_iter_count(to);

	करोut("sync_read on file %p %llu~%u %s\n", file, off, (अचिन्हित)len,
	     (file->f_flags & O_सूचीECT) ? "O_DIRECT" : "");

	अगर (!len)
		वापस 0;
	/*
	 * flush any page cache pages in this range.  this
	 * will make concurrent normal and sync io slow,
	 * but it will at least behave sensibly when they are
	 * in sequence.
	 */
	ret = filemap_ग_लिखो_and_रुको_range(inode->i_mapping,
					   off, off + len - 1);
	अगर (ret < 0)
		वापस ret;

	ret = 0;
	जबतक ((len = iov_iter_count(to)) > 0) अणु
		काष्ठा ceph_osd_request *req;
		काष्ठा page **pages;
		पूर्णांक num_pages;
		माप_प्रकार page_off;
		u64 i_size;
		bool more;
		पूर्णांक idx;
		माप_प्रकार left;

		req = ceph_osdc_new_request(osdc, &ci->i_layout,
					ci->i_vino, off, &len, 0, 1,
					CEPH_OSD_OP_READ, CEPH_OSD_FLAG_READ,
					शून्य, ci->i_truncate_seq,
					ci->i_truncate_size, false);
		अगर (IS_ERR(req)) अणु
			ret = PTR_ERR(req);
			अवरोध;
		पूर्ण

		more = len < iov_iter_count(to);

		num_pages = calc_pages_क्रम(off, len);
		page_off = off & ~PAGE_MASK;
		pages = ceph_alloc_page_vector(num_pages, GFP_KERNEL);
		अगर (IS_ERR(pages)) अणु
			ceph_osdc_put_request(req);
			ret = PTR_ERR(pages);
			अवरोध;
		पूर्ण

		osd_req_op_extent_osd_data_pages(req, 0, pages, len, page_off,
						 false, false);
		ret = ceph_osdc_start_request(osdc, req, false);
		अगर (!ret)
			ret = ceph_osdc_रुको_request(osdc, req);

		ceph_update_पढ़ो_metrics(&fsc->mdsc->metric,
					 req->r_start_latency,
					 req->r_end_latency,
					 ret);

		ceph_osdc_put_request(req);

		i_size = i_size_पढ़ो(inode);
		करोut("sync_read %llu~%llu got %zd i_size %llu%s\n",
		     off, len, ret, i_size, (more ? " MORE" : ""));

		अगर (ret == -ENOENT)
			ret = 0;
		अगर (ret >= 0 && ret < len && (off + ret < i_size)) अणु
			पूर्णांक zlen = min(len - ret, i_size - off - ret);
			पूर्णांक zoff = page_off + ret;
			करोut("sync_read zero gap %llu~%llu\n",
                             off + ret, off + ret + zlen);
			ceph_zero_page_vector_range(zoff, zlen, pages);
			ret += zlen;
		पूर्ण

		idx = 0;
		left = ret > 0 ? ret : 0;
		जबतक (left > 0) अणु
			माप_प्रकार len, copied;
			page_off = off & ~PAGE_MASK;
			len = min_t(माप_प्रकार, left, PAGE_SIZE - page_off);
			SetPageUptodate(pages[idx]);
			copied = copy_page_to_iter(pages[idx++],
						   page_off, len, to);
			off += copied;
			left -= copied;
			अगर (copied < len) अणु
				ret = -EFAULT;
				अवरोध;
			पूर्ण
		पूर्ण
		ceph_release_page_vector(pages, num_pages);

		अगर (ret < 0) अणु
			अगर (ret == -EBLOCKLISTED)
				fsc->blocklisted = true;
			अवरोध;
		पूर्ण

		अगर (off >= i_size || !more)
			अवरोध;
	पूर्ण

	अगर (off > iocb->ki_pos) अणु
		अगर (ret >= 0 &&
		    iov_iter_count(to) > 0 && off >= i_size_पढ़ो(inode))
			*retry_op = CHECK_खातापूर्ण;
		ret = off - iocb->ki_pos;
		iocb->ki_pos = off;
	पूर्ण

	करोut("sync_read result %zd retry_op %d\n", ret, *retry_op);
	वापस ret;
पूर्ण

काष्ठा ceph_aio_request अणु
	काष्ठा kiocb *iocb;
	माप_प्रकार total_len;
	bool ग_लिखो;
	bool should_dirty;
	पूर्णांक error;
	काष्ठा list_head osd_reqs;
	अचिन्हित num_reqs;
	atomic_t pending_reqs;
	काष्ठा बारpec64 mसमय;
	काष्ठा ceph_cap_flush *pपुनः_स्मृति_cf;
पूर्ण;

काष्ठा ceph_aio_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा ceph_osd_request *req;
पूर्ण;

अटल व्योम ceph_aio_retry_work(काष्ठा work_काष्ठा *work);

अटल व्योम ceph_aio_complete(काष्ठा inode *inode,
			      काष्ठा ceph_aio_request *aio_req)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक ret;

	अगर (!atomic_dec_and_test(&aio_req->pending_reqs))
		वापस;

	अगर (aio_req->iocb->ki_flags & IOCB_सूचीECT)
		inode_dio_end(inode);

	ret = aio_req->error;
	अगर (!ret)
		ret = aio_req->total_len;

	करोut("ceph_aio_complete %p rc %d\n", inode, ret);

	अगर (ret >= 0 && aio_req->ग_लिखो) अणु
		पूर्णांक dirty;

		loff_t enकरोff = aio_req->iocb->ki_pos + aio_req->total_len;
		अगर (enकरोff > i_size_पढ़ो(inode)) अणु
			अगर (ceph_inode_set_size(inode, enकरोff))
				ceph_check_caps(ci, CHECK_CAPS_AUTHONLY, शून्य);
		पूर्ण

		spin_lock(&ci->i_ceph_lock);
		ci->i_अंतरभूत_version = CEPH_INLINE_NONE;
		dirty = __ceph_mark_dirty_caps(ci, CEPH_CAP_खाता_WR,
					       &aio_req->pपुनः_स्मृति_cf);
		spin_unlock(&ci->i_ceph_lock);
		अगर (dirty)
			__mark_inode_dirty(inode, dirty);

	पूर्ण

	ceph_put_cap_refs(ci, (aio_req->ग_लिखो ? CEPH_CAP_खाता_WR :
						CEPH_CAP_खाता_RD));

	aio_req->iocb->ki_complete(aio_req->iocb, ret, 0);

	ceph_मुक्त_cap_flush(aio_req->pपुनः_स्मृति_cf);
	kमुक्त(aio_req);
पूर्ण

अटल व्योम ceph_aio_complete_req(काष्ठा ceph_osd_request *req)
अणु
	पूर्णांक rc = req->r_result;
	काष्ठा inode *inode = req->r_inode;
	काष्ठा ceph_aio_request *aio_req = req->r_priv;
	काष्ठा ceph_osd_data *osd_data = osd_req_op_extent_osd_data(req, 0);
	काष्ठा ceph_client_metric *metric = &ceph_sb_to_mdsc(inode->i_sb)->metric;

	BUG_ON(osd_data->type != CEPH_OSD_DATA_TYPE_BVECS);
	BUG_ON(!osd_data->num_bvecs);

	करोut("ceph_aio_complete_req %p rc %d bytes %u\n",
	     inode, rc, osd_data->bvec_pos.iter.bi_size);

	अगर (rc == -EOLDSNAPC) अणु
		काष्ठा ceph_aio_work *aio_work;
		BUG_ON(!aio_req->ग_लिखो);

		aio_work = kदो_स्मृति(माप(*aio_work), GFP_NOFS);
		अगर (aio_work) अणु
			INIT_WORK(&aio_work->work, ceph_aio_retry_work);
			aio_work->req = req;
			queue_work(ceph_inode_to_client(inode)->inode_wq,
				   &aio_work->work);
			वापस;
		पूर्ण
		rc = -ENOMEM;
	पूर्ण अन्यथा अगर (!aio_req->ग_लिखो) अणु
		अगर (rc == -ENOENT)
			rc = 0;
		अगर (rc >= 0 && osd_data->bvec_pos.iter.bi_size > rc) अणु
			काष्ठा iov_iter i;
			पूर्णांक zlen = osd_data->bvec_pos.iter.bi_size - rc;

			/*
			 * If पढ़ो is satisfied by single OSD request,
			 * it can pass खातापूर्ण. Otherwise पढ़ो is within
			 * i_size.
			 */
			अगर (aio_req->num_reqs == 1) अणु
				loff_t i_size = i_size_पढ़ो(inode);
				loff_t enकरोff = aio_req->iocb->ki_pos + rc;
				अगर (enकरोff < i_size)
					zlen = min_t(माप_प्रकार, zlen,
						     i_size - enकरोff);
				aio_req->total_len = rc + zlen;
			पूर्ण

			iov_iter_bvec(&i, READ, osd_data->bvec_pos.bvecs,
				      osd_data->num_bvecs,
				      osd_data->bvec_pos.iter.bi_size);
			iov_iter_advance(&i, rc);
			iov_iter_zero(zlen, &i);
		पूर्ण
	पूर्ण

	/* r_start_latency == 0 means the request was not submitted */
	अगर (req->r_start_latency) अणु
		अगर (aio_req->ग_लिखो)
			ceph_update_ग_लिखो_metrics(metric, req->r_start_latency,
						  req->r_end_latency, rc);
		अन्यथा
			ceph_update_पढ़ो_metrics(metric, req->r_start_latency,
						 req->r_end_latency, rc);
	पूर्ण

	put_bvecs(osd_data->bvec_pos.bvecs, osd_data->num_bvecs,
		  aio_req->should_dirty);
	ceph_osdc_put_request(req);

	अगर (rc < 0)
		cmpxchg(&aio_req->error, 0, rc);

	ceph_aio_complete(inode, aio_req);
	वापस;
पूर्ण

अटल व्योम ceph_aio_retry_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ceph_aio_work *aio_work =
		container_of(work, काष्ठा ceph_aio_work, work);
	काष्ठा ceph_osd_request *orig_req = aio_work->req;
	काष्ठा ceph_aio_request *aio_req = orig_req->r_priv;
	काष्ठा inode *inode = orig_req->r_inode;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_snap_context *snapc;
	काष्ठा ceph_osd_request *req;
	पूर्णांक ret;

	spin_lock(&ci->i_ceph_lock);
	अगर (__ceph_have_pending_cap_snap(ci)) अणु
		काष्ठा ceph_cap_snap *capsnap =
			list_last_entry(&ci->i_cap_snaps,
					काष्ठा ceph_cap_snap,
					ci_item);
		snapc = ceph_get_snap_context(capsnap->context);
	पूर्ण अन्यथा अणु
		BUG_ON(!ci->i_head_snapc);
		snapc = ceph_get_snap_context(ci->i_head_snapc);
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);

	req = ceph_osdc_alloc_request(orig_req->r_osdc, snapc, 1,
			false, GFP_NOFS);
	अगर (!req) अणु
		ret = -ENOMEM;
		req = orig_req;
		जाओ out;
	पूर्ण

	req->r_flags = /* CEPH_OSD_FLAG_ORDERSNAP | */ CEPH_OSD_FLAG_WRITE;
	ceph_oloc_copy(&req->r_base_oloc, &orig_req->r_base_oloc);
	ceph_oid_copy(&req->r_base_oid, &orig_req->r_base_oid);

	req->r_ops[0] = orig_req->r_ops[0];

	req->r_mसमय = aio_req->mसमय;
	req->r_data_offset = req->r_ops[0].extent.offset;

	ret = ceph_osdc_alloc_messages(req, GFP_NOFS);
	अगर (ret) अणु
		ceph_osdc_put_request(req);
		req = orig_req;
		जाओ out;
	पूर्ण

	ceph_osdc_put_request(orig_req);

	req->r_callback = ceph_aio_complete_req;
	req->r_inode = inode;
	req->r_priv = aio_req;

	ret = ceph_osdc_start_request(req->r_osdc, req, false);
out:
	अगर (ret < 0) अणु
		req->r_result = ret;
		ceph_aio_complete_req(req);
	पूर्ण

	ceph_put_snap_context(snapc);
	kमुक्त(aio_work);
पूर्ण

अटल sमाप_प्रकार
ceph_direct_पढ़ो_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter,
		       काष्ठा ceph_snap_context *snapc,
		       काष्ठा ceph_cap_flush **pcf)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_client_metric *metric = &fsc->mdsc->metric;
	काष्ठा ceph_vino vino;
	काष्ठा ceph_osd_request *req;
	काष्ठा bio_vec *bvecs;
	काष्ठा ceph_aio_request *aio_req = शून्य;
	पूर्णांक num_pages = 0;
	पूर्णांक flags;
	पूर्णांक ret = 0;
	काष्ठा बारpec64 mसमय = current_समय(inode);
	माप_प्रकार count = iov_iter_count(iter);
	loff_t pos = iocb->ki_pos;
	bool ग_लिखो = iov_iter_rw(iter) == WRITE;
	bool should_dirty = !ग_लिखो && iter_is_iovec(iter);

	अगर (ग_लिखो && ceph_snap(file_inode(file)) != CEPH_NOSNAP)
		वापस -EROFS;

	करोut("sync_direct_%s on file %p %lld~%u snapc %p seq %lld\n",
	     (ग_लिखो ? "write" : "read"), file, pos, (अचिन्हित)count,
	     snapc, snapc ? snapc->seq : 0);

	अगर (ग_लिखो) अणु
		पूर्णांक ret2 = invalidate_inode_pages2_range(inode->i_mapping,
					pos >> PAGE_SHIFT,
					(pos + count - 1) >> PAGE_SHIFT);
		अगर (ret2 < 0)
			करोut("invalidate_inode_pages2_range returned %d\n", ret2);

		flags = /* CEPH_OSD_FLAG_ORDERSNAP | */ CEPH_OSD_FLAG_WRITE;
	पूर्ण अन्यथा अणु
		flags = CEPH_OSD_FLAG_READ;
	पूर्ण

	जबतक (iov_iter_count(iter) > 0) अणु
		u64 size = iov_iter_count(iter);
		sमाप_प्रकार len;

		अगर (ग_लिखो)
			size = min_t(u64, size, fsc->mount_options->wsize);
		अन्यथा
			size = min_t(u64, size, fsc->mount_options->rsize);

		vino = ceph_vino(inode);
		req = ceph_osdc_new_request(&fsc->client->osdc, &ci->i_layout,
					    vino, pos, &size, 0,
					    1,
					    ग_लिखो ? CEPH_OSD_OP_WRITE :
						    CEPH_OSD_OP_READ,
					    flags, snapc,
					    ci->i_truncate_seq,
					    ci->i_truncate_size,
					    false);
		अगर (IS_ERR(req)) अणु
			ret = PTR_ERR(req);
			अवरोध;
		पूर्ण

		len = iter_get_bvecs_alloc(iter, size, &bvecs, &num_pages);
		अगर (len < 0) अणु
			ceph_osdc_put_request(req);
			ret = len;
			अवरोध;
		पूर्ण
		अगर (len != size)
			osd_req_op_extent_update(req, 0, len);

		/*
		 * To simplअगरy error handling, allow AIO when IO within i_size
		 * or IO can be satisfied by single OSD request.
		 */
		अगर (pos == iocb->ki_pos && !is_sync_kiocb(iocb) &&
		    (len == count || pos + count <= i_size_पढ़ो(inode))) अणु
			aio_req = kzalloc(माप(*aio_req), GFP_KERNEL);
			अगर (aio_req) अणु
				aio_req->iocb = iocb;
				aio_req->ग_लिखो = ग_लिखो;
				aio_req->should_dirty = should_dirty;
				INIT_LIST_HEAD(&aio_req->osd_reqs);
				अगर (ग_लिखो) अणु
					aio_req->mसमय = mसमय;
					swap(aio_req->pपुनः_स्मृति_cf, *pcf);
				पूर्ण
			पूर्ण
			/* ignore error */
		पूर्ण

		अगर (ग_लिखो) अणु
			/*
			 * throw out any page cache pages in this range. this
			 * may block.
			 */
			truncate_inode_pages_range(inode->i_mapping, pos,
						   PAGE_ALIGN(pos + len) - 1);

			req->r_mसमय = mसमय;
		पूर्ण

		osd_req_op_extent_osd_data_bvecs(req, 0, bvecs, num_pages, len);

		अगर (aio_req) अणु
			aio_req->total_len += len;
			aio_req->num_reqs++;
			atomic_inc(&aio_req->pending_reqs);

			req->r_callback = ceph_aio_complete_req;
			req->r_inode = inode;
			req->r_priv = aio_req;
			list_add_tail(&req->r_निजी_item, &aio_req->osd_reqs);

			pos += len;
			जारी;
		पूर्ण

		ret = ceph_osdc_start_request(req->r_osdc, req, false);
		अगर (!ret)
			ret = ceph_osdc_रुको_request(&fsc->client->osdc, req);

		अगर (ग_लिखो)
			ceph_update_ग_लिखो_metrics(metric, req->r_start_latency,
						  req->r_end_latency, ret);
		अन्यथा
			ceph_update_पढ़ो_metrics(metric, req->r_start_latency,
						 req->r_end_latency, ret);

		size = i_size_पढ़ो(inode);
		अगर (!ग_लिखो) अणु
			अगर (ret == -ENOENT)
				ret = 0;
			अगर (ret >= 0 && ret < len && pos + ret < size) अणु
				काष्ठा iov_iter i;
				पूर्णांक zlen = min_t(माप_प्रकार, len - ret,
						 size - pos - ret);

				iov_iter_bvec(&i, READ, bvecs, num_pages, len);
				iov_iter_advance(&i, ret);
				iov_iter_zero(zlen, &i);
				ret += zlen;
			पूर्ण
			अगर (ret >= 0)
				len = ret;
		पूर्ण

		put_bvecs(bvecs, num_pages, should_dirty);
		ceph_osdc_put_request(req);
		अगर (ret < 0)
			अवरोध;

		pos += len;
		अगर (!ग_लिखो && pos >= size)
			अवरोध;

		अगर (ग_लिखो && pos > size) अणु
			अगर (ceph_inode_set_size(inode, pos))
				ceph_check_caps(ceph_inode(inode),
						CHECK_CAPS_AUTHONLY,
						शून्य);
		पूर्ण
	पूर्ण

	अगर (aio_req) अणु
		LIST_HEAD(osd_reqs);

		अगर (aio_req->num_reqs == 0) अणु
			kमुक्त(aio_req);
			वापस ret;
		पूर्ण

		ceph_get_cap_refs(ci, ग_लिखो ? CEPH_CAP_खाता_WR :
					      CEPH_CAP_खाता_RD);

		list_splice(&aio_req->osd_reqs, &osd_reqs);
		inode_dio_begin(inode);
		जबतक (!list_empty(&osd_reqs)) अणु
			req = list_first_entry(&osd_reqs,
					       काष्ठा ceph_osd_request,
					       r_निजी_item);
			list_del_init(&req->r_निजी_item);
			अगर (ret >= 0)
				ret = ceph_osdc_start_request(req->r_osdc,
							      req, false);
			अगर (ret < 0) अणु
				req->r_result = ret;
				ceph_aio_complete_req(req);
			पूर्ण
		पूर्ण
		वापस -EIOCBQUEUED;
	पूर्ण

	अगर (ret != -EOLDSNAPC && pos > iocb->ki_pos) अणु
		ret = pos - iocb->ki_pos;
		iocb->ki_pos = pos;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Synchronous ग_लिखो, straight from __user poपूर्णांकer or user pages.
 *
 * If ग_लिखो spans object boundary, just करो multiple ग_लिखोs.  (For a
 * correct atomic ग_लिखो, we should e.g. take ग_लिखो locks on all
 * objects, rollback on failure, etc.)
 */
अटल sमाप_प्रकार
ceph_sync_ग_लिखो(काष्ठा kiocb *iocb, काष्ठा iov_iter *from, loff_t pos,
		काष्ठा ceph_snap_context *snapc)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_vino vino;
	काष्ठा ceph_osd_request *req;
	काष्ठा page **pages;
	u64 len;
	पूर्णांक num_pages;
	पूर्णांक written = 0;
	पूर्णांक flags;
	पूर्णांक ret;
	bool check_caps = false;
	काष्ठा बारpec64 mसमय = current_समय(inode);
	माप_प्रकार count = iov_iter_count(from);

	अगर (ceph_snap(file_inode(file)) != CEPH_NOSNAP)
		वापस -EROFS;

	करोut("sync_write on file %p %lld~%u snapc %p seq %lld\n",
	     file, pos, (अचिन्हित)count, snapc, snapc->seq);

	ret = filemap_ग_लिखो_and_रुको_range(inode->i_mapping,
					   pos, pos + count - 1);
	अगर (ret < 0)
		वापस ret;

	ret = invalidate_inode_pages2_range(inode->i_mapping,
					    pos >> PAGE_SHIFT,
					    (pos + count - 1) >> PAGE_SHIFT);
	अगर (ret < 0)
		करोut("invalidate_inode_pages2_range returned %d\n", ret);

	flags = /* CEPH_OSD_FLAG_ORDERSNAP | */ CEPH_OSD_FLAG_WRITE;

	जबतक ((len = iov_iter_count(from)) > 0) अणु
		माप_प्रकार left;
		पूर्णांक n;

		vino = ceph_vino(inode);
		req = ceph_osdc_new_request(&fsc->client->osdc, &ci->i_layout,
					    vino, pos, &len, 0, 1,
					    CEPH_OSD_OP_WRITE, flags, snapc,
					    ci->i_truncate_seq,
					    ci->i_truncate_size,
					    false);
		अगर (IS_ERR(req)) अणु
			ret = PTR_ERR(req);
			अवरोध;
		पूर्ण

		/*
		 * ग_लिखो from beginning of first page,
		 * regardless of io alignment
		 */
		num_pages = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;

		pages = ceph_alloc_page_vector(num_pages, GFP_KERNEL);
		अगर (IS_ERR(pages)) अणु
			ret = PTR_ERR(pages);
			जाओ out;
		पूर्ण

		left = len;
		क्रम (n = 0; n < num_pages; n++) अणु
			माप_प्रकार plen = min_t(माप_प्रकार, left, PAGE_SIZE);
			ret = copy_page_from_iter(pages[n], 0, plen, from);
			अगर (ret != plen) अणु
				ret = -EFAULT;
				अवरोध;
			पूर्ण
			left -= ret;
		पूर्ण

		अगर (ret < 0) अणु
			ceph_release_page_vector(pages, num_pages);
			जाओ out;
		पूर्ण

		req->r_inode = inode;

		osd_req_op_extent_osd_data_pages(req, 0, pages, len, 0,
						false, true);

		req->r_mसमय = mसमय;
		ret = ceph_osdc_start_request(&fsc->client->osdc, req, false);
		अगर (!ret)
			ret = ceph_osdc_रुको_request(&fsc->client->osdc, req);

		ceph_update_ग_लिखो_metrics(&fsc->mdsc->metric, req->r_start_latency,
					  req->r_end_latency, ret);
out:
		ceph_osdc_put_request(req);
		अगर (ret != 0) अणु
			ceph_set_error_ग_लिखो(ci);
			अवरोध;
		पूर्ण

		ceph_clear_error_ग_लिखो(ci);
		pos += len;
		written += len;
		अगर (pos > i_size_पढ़ो(inode)) अणु
			check_caps = ceph_inode_set_size(inode, pos);
			अगर (check_caps)
				ceph_check_caps(ceph_inode(inode),
						CHECK_CAPS_AUTHONLY,
						शून्य);
		पूर्ण

	पूर्ण

	अगर (ret != -EOLDSNAPC && written > 0) अणु
		ret = written;
		iocb->ki_pos = pos;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Wrap generic_file_aio_पढ़ो with checks क्रम cap bits on the inode.
 * Atomically grab references, so that those bits are not released
 * back to the MDS mid-पढ़ो.
 *
 * Hmm, the sync पढ़ो हाल isn't actually async... should it be?
 */
अटल sमाप_प्रकार ceph_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *filp = iocb->ki_filp;
	काष्ठा ceph_file_info *fi = filp->निजी_data;
	माप_प्रकार len = iov_iter_count(to);
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	bool direct_lock = iocb->ki_flags & IOCB_सूचीECT;
	sमाप_प्रकार ret;
	पूर्णांक want, got = 0;
	पूर्णांक retry_op = 0, पढ़ो = 0;

again:
	करोut("aio_read %p %llx.%llx %llu~%u trying to get caps on %p\n",
	     inode, ceph_vinop(inode), iocb->ki_pos, (अचिन्हित)len, inode);

	अगर (direct_lock)
		ceph_start_io_direct(inode);
	अन्यथा
		ceph_start_io_पढ़ो(inode);

	अगर (fi->भ_शेषe & CEPH_खाता_MODE_LAZY)
		want = CEPH_CAP_खाता_CACHE | CEPH_CAP_खाता_LAZYIO;
	अन्यथा
		want = CEPH_CAP_खाता_CACHE;
	ret = ceph_get_caps(filp, CEPH_CAP_खाता_RD, want, -1, &got);
	अगर (ret < 0) अणु
		अगर (iocb->ki_flags & IOCB_सूचीECT)
			ceph_end_io_direct(inode);
		अन्यथा
			ceph_end_io_पढ़ो(inode);
		वापस ret;
	पूर्ण

	अगर ((got & (CEPH_CAP_खाता_CACHE|CEPH_CAP_खाता_LAZYIO)) == 0 ||
	    (iocb->ki_flags & IOCB_सूचीECT) ||
	    (fi->flags & CEPH_F_SYNC)) अणु

		करोut("aio_sync_read %p %llx.%llx %llu~%u got cap refs on %s\n",
		     inode, ceph_vinop(inode), iocb->ki_pos, (अचिन्हित)len,
		     ceph_cap_string(got));

		अगर (ci->i_अंतरभूत_version == CEPH_INLINE_NONE) अणु
			अगर (!retry_op && (iocb->ki_flags & IOCB_सूचीECT)) अणु
				ret = ceph_direct_पढ़ो_ग_लिखो(iocb, to,
							     शून्य, शून्य);
				अगर (ret >= 0 && ret < len)
					retry_op = CHECK_खातापूर्ण;
			पूर्ण अन्यथा अणु
				ret = ceph_sync_पढ़ो(iocb, to, &retry_op);
			पूर्ण
		पूर्ण अन्यथा अणु
			retry_op = READ_INLINE;
		पूर्ण
	पूर्ण अन्यथा अणु
		CEPH_DEFINE_RW_CONTEXT(rw_ctx, got);
		करोut("aio_read %p %llx.%llx %llu~%u got cap refs on %s\n",
		     inode, ceph_vinop(inode), iocb->ki_pos, (अचिन्हित)len,
		     ceph_cap_string(got));
		ceph_add_rw_context(fi, &rw_ctx);
		ret = generic_file_पढ़ो_iter(iocb, to);
		ceph_del_rw_context(fi, &rw_ctx);
	पूर्ण

	करोut("aio_read %p %llx.%llx dropping cap refs on %s = %d\n",
	     inode, ceph_vinop(inode), ceph_cap_string(got), (पूर्णांक)ret);
	ceph_put_cap_refs(ci, got);

	अगर (direct_lock)
		ceph_end_io_direct(inode);
	अन्यथा
		ceph_end_io_पढ़ो(inode);

	अगर (retry_op > HAVE_RETRIED && ret >= 0) अणु
		पूर्णांक statret;
		काष्ठा page *page = शून्य;
		loff_t i_size;
		अगर (retry_op == READ_INLINE) अणु
			page = __page_cache_alloc(GFP_KERNEL);
			अगर (!page)
				वापस -ENOMEM;
		पूर्ण

		statret = __ceph_करो_getattr(inode, page,
					    CEPH_STAT_CAP_INLINE_DATA, !!page);
		अगर (statret < 0) अणु
			अगर (page)
				__मुक्त_page(page);
			अगर (statret == -ENODATA) अणु
				BUG_ON(retry_op != READ_INLINE);
				जाओ again;
			पूर्ण
			वापस statret;
		पूर्ण

		i_size = i_size_पढ़ो(inode);
		अगर (retry_op == READ_INLINE) अणु
			BUG_ON(ret > 0 || पढ़ो > 0);
			अगर (iocb->ki_pos < i_size &&
			    iocb->ki_pos < PAGE_SIZE) अणु
				loff_t end = min_t(loff_t, i_size,
						   iocb->ki_pos + len);
				end = min_t(loff_t, end, PAGE_SIZE);
				अगर (statret < end)
					zero_user_segment(page, statret, end);
				ret = copy_page_to_iter(page,
						iocb->ki_pos & ~PAGE_MASK,
						end - iocb->ki_pos, to);
				iocb->ki_pos += ret;
				पढ़ो += ret;
			पूर्ण
			अगर (iocb->ki_pos < i_size && पढ़ो < len) अणु
				माप_प्रकार zlen = min_t(माप_प्रकार, len - पढ़ो,
						    i_size - iocb->ki_pos);
				ret = iov_iter_zero(zlen, to);
				iocb->ki_pos += ret;
				पढ़ो += ret;
			पूर्ण
			__मुक्त_pages(page, 0);
			वापस पढ़ो;
		पूर्ण

		/* hit खातापूर्ण or hole? */
		अगर (retry_op == CHECK_खातापूर्ण && iocb->ki_pos < i_size &&
		    ret < len) अणु
			करोut("sync_read hit hole, ppos %lld < size %lld"
			     ", reading more\n", iocb->ki_pos, i_size);

			पढ़ो += ret;
			len -= ret;
			retry_op = HAVE_RETRIED;
			जाओ again;
		पूर्ण
	पूर्ण

	अगर (ret >= 0)
		ret += पढ़ो;

	वापस ret;
पूर्ण

/*
 * Take cap references to aव्योम releasing caps to MDS mid-ग_लिखो.
 *
 * If we are synchronous, and ग_लिखो with an old snap context, the OSD
 * may वापस EOLDSNAPC.  In that हाल, retry the ग_लिखो.. _after_
 * dropping our cap refs and allowing the pending snap to logically
 * complete _beक्रमe_ this ग_लिखो occurs.
 *
 * If we are near ENOSPC, ग_लिखो synchronously.
 */
अटल sमाप_प्रकार ceph_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा ceph_file_info *fi = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_osd_client *osdc = &fsc->client->osdc;
	काष्ठा ceph_cap_flush *pपुनः_स्मृति_cf;
	sमाप_प्रकार count, written = 0;
	पूर्णांक err, want, got;
	bool direct_lock = false;
	u32 map_flags;
	u64 pool_flags;
	loff_t pos;
	loff_t limit = max(i_size_पढ़ो(inode), fsc->max_file_size);

	अगर (ceph_snap(inode) != CEPH_NOSNAP)
		वापस -EROFS;

	pपुनः_स्मृति_cf = ceph_alloc_cap_flush();
	अगर (!pपुनः_स्मृति_cf)
		वापस -ENOMEM;

	अगर ((iocb->ki_flags & (IOCB_सूचीECT | IOCB_APPEND)) == IOCB_सूचीECT)
		direct_lock = true;

retry_snap:
	अगर (direct_lock)
		ceph_start_io_direct(inode);
	अन्यथा
		ceph_start_io_ग_लिखो(inode);

	/* We can ग_लिखो back this queue in page reclaim */
	current->backing_dev_info = inode_to_bdi(inode);

	अगर (iocb->ki_flags & IOCB_APPEND) अणु
		err = ceph_करो_getattr(inode, CEPH_STAT_CAP_SIZE, false);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	err = generic_ग_लिखो_checks(iocb, from);
	अगर (err <= 0)
		जाओ out;

	pos = iocb->ki_pos;
	अगर (unlikely(pos >= limit)) अणु
		err = -EFBIG;
		जाओ out;
	पूर्ण अन्यथा अणु
		iov_iter_truncate(from, limit - pos);
	पूर्ण

	count = iov_iter_count(from);
	अगर (ceph_quota_is_max_bytes_exceeded(inode, pos + count)) अणु
		err = -EDQUOT;
		जाओ out;
	पूर्ण

	err = file_हटाओ_privs(file);
	अगर (err)
		जाओ out;

	err = file_update_समय(file);
	अगर (err)
		जाओ out;

	inode_inc_iversion_raw(inode);

	अगर (ci->i_अंतरभूत_version != CEPH_INLINE_NONE) अणु
		err = ceph_unअंतरभूत_data(file, शून्य);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	करोwn_पढ़ो(&osdc->lock);
	map_flags = osdc->osdmap->flags;
	pool_flags = ceph_pg_pool_flags(osdc->osdmap, ci->i_layout.pool_id);
	up_पढ़ो(&osdc->lock);
	अगर ((map_flags & CEPH_OSDMAP_FULL) ||
	    (pool_flags & CEPH_POOL_FLAG_FULL)) अणु
		err = -ENOSPC;
		जाओ out;
	पूर्ण

	करोut("aio_write %p %llx.%llx %llu~%zd getting caps. i_size %llu\n",
	     inode, ceph_vinop(inode), pos, count, i_size_पढ़ो(inode));
	अगर (fi->भ_शेषe & CEPH_खाता_MODE_LAZY)
		want = CEPH_CAP_खाता_BUFFER | CEPH_CAP_खाता_LAZYIO;
	अन्यथा
		want = CEPH_CAP_खाता_BUFFER;
	got = 0;
	err = ceph_get_caps(file, CEPH_CAP_खाता_WR, want, pos + count, &got);
	अगर (err < 0)
		जाओ out;

	करोut("aio_write %p %llx.%llx %llu~%zd got cap refs on %s\n",
	     inode, ceph_vinop(inode), pos, count, ceph_cap_string(got));

	अगर ((got & (CEPH_CAP_खाता_BUFFER|CEPH_CAP_खाता_LAZYIO)) == 0 ||
	    (iocb->ki_flags & IOCB_सूचीECT) || (fi->flags & CEPH_F_SYNC) ||
	    (ci->i_ceph_flags & CEPH_I_ERROR_WRITE)) अणु
		काष्ठा ceph_snap_context *snapc;
		काष्ठा iov_iter data;

		spin_lock(&ci->i_ceph_lock);
		अगर (__ceph_have_pending_cap_snap(ci)) अणु
			काष्ठा ceph_cap_snap *capsnap =
					list_last_entry(&ci->i_cap_snaps,
							काष्ठा ceph_cap_snap,
							ci_item);
			snapc = ceph_get_snap_context(capsnap->context);
		पूर्ण अन्यथा अणु
			BUG_ON(!ci->i_head_snapc);
			snapc = ceph_get_snap_context(ci->i_head_snapc);
		पूर्ण
		spin_unlock(&ci->i_ceph_lock);

		/* we might need to revert back to that poपूर्णांक */
		data = *from;
		अगर (iocb->ki_flags & IOCB_सूचीECT)
			written = ceph_direct_पढ़ो_ग_लिखो(iocb, &data, snapc,
							 &pपुनः_स्मृति_cf);
		अन्यथा
			written = ceph_sync_ग_लिखो(iocb, &data, pos, snapc);
		अगर (direct_lock)
			ceph_end_io_direct(inode);
		अन्यथा
			ceph_end_io_ग_लिखो(inode);
		अगर (written > 0)
			iov_iter_advance(from, written);
		ceph_put_snap_context(snapc);
	पूर्ण अन्यथा अणु
		/*
		 * No need to acquire the i_truncate_mutex. Because
		 * the MDS revokes Fwb caps beक्रमe sending truncate
		 * message to us. We can't get Fwb cap जबतक there
		 * are pending vmtruncate. So ग_लिखो and vmtruncate
		 * can not run at the same समय
		 */
		written = generic_perक्रमm_ग_लिखो(file, from, pos);
		अगर (likely(written >= 0))
			iocb->ki_pos = pos + written;
		ceph_end_io_ग_लिखो(inode);
	पूर्ण

	अगर (written >= 0) अणु
		पूर्णांक dirty;

		spin_lock(&ci->i_ceph_lock);
		ci->i_अंतरभूत_version = CEPH_INLINE_NONE;
		dirty = __ceph_mark_dirty_caps(ci, CEPH_CAP_खाता_WR,
					       &pपुनः_स्मृति_cf);
		spin_unlock(&ci->i_ceph_lock);
		अगर (dirty)
			__mark_inode_dirty(inode, dirty);
		अगर (ceph_quota_is_max_bytes_approaching(inode, iocb->ki_pos))
			ceph_check_caps(ci, 0, शून्य);
	पूर्ण

	करोut("aio_write %p %llx.%llx %llu~%u  dropping cap refs on %s\n",
	     inode, ceph_vinop(inode), pos, (अचिन्हित)count,
	     ceph_cap_string(got));
	ceph_put_cap_refs(ci, got);

	अगर (written == -EOLDSNAPC) अणु
		करोut("aio_write %p %llx.%llx %llu~%u" "got EOLDSNAPC, retrying\n",
		     inode, ceph_vinop(inode), pos, (अचिन्हित)count);
		जाओ retry_snap;
	पूर्ण

	अगर (written >= 0) अणु
		अगर ((map_flags & CEPH_OSDMAP_NEARFULL) ||
		    (pool_flags & CEPH_POOL_FLAG_NEARFULL))
			iocb->ki_flags |= IOCB_DSYNC;
		written = generic_ग_लिखो_sync(iocb, written);
	पूर्ण

	जाओ out_unlocked;
out:
	अगर (direct_lock)
		ceph_end_io_direct(inode);
	अन्यथा
		ceph_end_io_ग_लिखो(inode);
out_unlocked:
	ceph_मुक्त_cap_flush(pपुनः_स्मृति_cf);
	current->backing_dev_info = शून्य;
	वापस written ? written : err;
पूर्ण

/*
 * llseek.  be sure to verअगरy file size on अंत_से.
 */
अटल loff_t ceph_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	loff_t i_size;
	loff_t ret;

	inode_lock(inode);

	अगर (whence == अंत_से || whence == SEEK_DATA || whence == SEEK_HOLE) अणु
		ret = ceph_करो_getattr(inode, CEPH_STAT_CAP_SIZE, false);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	i_size = i_size_पढ़ो(inode);
	चयन (whence) अणु
	हाल अंत_से:
		offset += i_size;
		अवरोध;
	हाल प्रस्तुत_से:
		/*
		 * Here we special-हाल the lseek(fd, 0, प्रस्तुत_से)
		 * position-querying operation.  Aव्योम rewriting the "same"
		 * f_pos value back to the file because a concurrent पढ़ो(),
		 * ग_लिखो() or lseek() might have altered it
		 */
		अगर (offset == 0) अणु
			ret = file->f_pos;
			जाओ out;
		पूर्ण
		offset += file->f_pos;
		अवरोध;
	हाल SEEK_DATA:
		अगर (offset < 0 || offset >= i_size) अणु
			ret = -ENXIO;
			जाओ out;
		पूर्ण
		अवरोध;
	हाल SEEK_HOLE:
		अगर (offset < 0 || offset >= i_size) अणु
			ret = -ENXIO;
			जाओ out;
		पूर्ण
		offset = i_size;
		अवरोध;
	पूर्ण

	ret = vfs_setpos(file, offset, max(i_size, fsc->max_file_size));

out:
	inode_unlock(inode);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम ceph_zero_partial_page(
	काष्ठा inode *inode, loff_t offset, अचिन्हित size)
अणु
	काष्ठा page *page;
	pgoff_t index = offset >> PAGE_SHIFT;

	page = find_lock_page(inode->i_mapping, index);
	अगर (page) अणु
		रुको_on_page_ग_लिखोback(page);
		zero_user(page, offset & (PAGE_SIZE - 1), size);
		unlock_page(page);
		put_page(page);
	पूर्ण
पूर्ण

अटल व्योम ceph_zero_pagecache_range(काष्ठा inode *inode, loff_t offset,
				      loff_t length)
अणु
	loff_t nearly = round_up(offset, PAGE_SIZE);
	अगर (offset < nearly) अणु
		loff_t size = nearly - offset;
		अगर (length < size)
			size = length;
		ceph_zero_partial_page(inode, offset, size);
		offset += size;
		length -= size;
	पूर्ण
	अगर (length >= PAGE_SIZE) अणु
		loff_t size = round_करोwn(length, PAGE_SIZE);
		truncate_pagecache_range(inode, offset, offset + size - 1);
		offset += size;
		length -= size;
	पूर्ण
	अगर (length)
		ceph_zero_partial_page(inode, offset, length);
पूर्ण

अटल पूर्णांक ceph_zero_partial_object(काष्ठा inode *inode,
				    loff_t offset, loff_t *length)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_osd_request *req;
	पूर्णांक ret = 0;
	loff_t zero = 0;
	पूर्णांक op;

	अगर (!length) अणु
		op = offset ? CEPH_OSD_OP_DELETE : CEPH_OSD_OP_TRUNCATE;
		length = &zero;
	पूर्ण अन्यथा अणु
		op = CEPH_OSD_OP_ZERO;
	पूर्ण

	req = ceph_osdc_new_request(&fsc->client->osdc, &ci->i_layout,
					ceph_vino(inode),
					offset, length,
					0, 1, op,
					CEPH_OSD_FLAG_WRITE,
					शून्य, 0, 0, false);
	अगर (IS_ERR(req)) अणु
		ret = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->r_mसमय = inode->i_mसमय;
	ret = ceph_osdc_start_request(&fsc->client->osdc, req, false);
	अगर (!ret) अणु
		ret = ceph_osdc_रुको_request(&fsc->client->osdc, req);
		अगर (ret == -ENOENT)
			ret = 0;
	पूर्ण
	ceph_osdc_put_request(req);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ceph_zero_objects(काष्ठा inode *inode, loff_t offset, loff_t length)
अणु
	पूर्णांक ret = 0;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	s32 stripe_unit = ci->i_layout.stripe_unit;
	s32 stripe_count = ci->i_layout.stripe_count;
	s32 object_size = ci->i_layout.object_size;
	u64 object_set_size = object_size * stripe_count;
	u64 nearly, t;

	/* round offset up to next period boundary */
	nearly = offset + object_set_size - 1;
	t = nearly;
	nearly -= करो_भाग(t, object_set_size);

	जबतक (length && offset < nearly) अणु
		loff_t size = length;
		ret = ceph_zero_partial_object(inode, offset, &size);
		अगर (ret < 0)
			वापस ret;
		offset += size;
		length -= size;
	पूर्ण
	जबतक (length >= object_set_size) अणु
		पूर्णांक i;
		loff_t pos = offset;
		क्रम (i = 0; i < stripe_count; ++i) अणु
			ret = ceph_zero_partial_object(inode, pos, शून्य);
			अगर (ret < 0)
				वापस ret;
			pos += stripe_unit;
		पूर्ण
		offset += object_set_size;
		length -= object_set_size;
	पूर्ण
	जबतक (length) अणु
		loff_t size = length;
		ret = ceph_zero_partial_object(inode, offset, &size);
		अगर (ret < 0)
			वापस ret;
		offset += size;
		length -= size;
	पूर्ण
	वापस ret;
पूर्ण

अटल दीर्घ ceph_fallocate(काष्ठा file *file, पूर्णांक mode,
				loff_t offset, loff_t length)
अणु
	काष्ठा ceph_file_info *fi = file->निजी_data;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_cap_flush *pपुनः_स्मृति_cf;
	पूर्णांक want, got = 0;
	पूर्णांक dirty;
	पूर्णांक ret = 0;
	loff_t enकरोff = 0;
	loff_t size;

	अगर (mode != (FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE))
		वापस -EOPNOTSUPP;

	अगर (!S_ISREG(inode->i_mode))
		वापस -EOPNOTSUPP;

	pपुनः_स्मृति_cf = ceph_alloc_cap_flush();
	अगर (!pपुनः_स्मृति_cf)
		वापस -ENOMEM;

	inode_lock(inode);

	अगर (ceph_snap(inode) != CEPH_NOSNAP) अणु
		ret = -EROFS;
		जाओ unlock;
	पूर्ण

	अगर (ci->i_अंतरभूत_version != CEPH_INLINE_NONE) अणु
		ret = ceph_unअंतरभूत_data(file, शून्य);
		अगर (ret < 0)
			जाओ unlock;
	पूर्ण

	size = i_size_पढ़ो(inode);

	/* Are we punching a hole beyond खातापूर्ण? */
	अगर (offset >= size)
		जाओ unlock;
	अगर ((offset + length) > size)
		length = size - offset;

	अगर (fi->भ_शेषe & CEPH_खाता_MODE_LAZY)
		want = CEPH_CAP_खाता_BUFFER | CEPH_CAP_खाता_LAZYIO;
	अन्यथा
		want = CEPH_CAP_खाता_BUFFER;

	ret = ceph_get_caps(file, CEPH_CAP_खाता_WR, want, enकरोff, &got);
	अगर (ret < 0)
		जाओ unlock;

	ceph_zero_pagecache_range(inode, offset, length);
	ret = ceph_zero_objects(inode, offset, length);

	अगर (!ret) अणु
		spin_lock(&ci->i_ceph_lock);
		ci->i_अंतरभूत_version = CEPH_INLINE_NONE;
		dirty = __ceph_mark_dirty_caps(ci, CEPH_CAP_खाता_WR,
					       &pपुनः_स्मृति_cf);
		spin_unlock(&ci->i_ceph_lock);
		अगर (dirty)
			__mark_inode_dirty(inode, dirty);
	पूर्ण

	ceph_put_cap_refs(ci, got);
unlock:
	inode_unlock(inode);
	ceph_मुक्त_cap_flush(pपुनः_स्मृति_cf);
	वापस ret;
पूर्ण

/*
 * This function tries to get खाता_WR capabilities क्रम dst_ci and खाता_RD क्रम
 * src_ci.  Two attempts are made to obtain both caps, and an error is वापस अगर
 * this fails; zero is वापसed on success.
 */
अटल पूर्णांक get_rd_wr_caps(काष्ठा file *src_filp, पूर्णांक *src_got,
			  काष्ठा file *dst_filp,
			  loff_t dst_enकरोff, पूर्णांक *dst_got)
अणु
	पूर्णांक ret = 0;
	bool retrying = false;

retry_caps:
	ret = ceph_get_caps(dst_filp, CEPH_CAP_खाता_WR, CEPH_CAP_खाता_BUFFER,
			    dst_enकरोff, dst_got);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Since we're alपढ़ोy holding the खाता_WR capability क्रम the dst file,
	 * we would risk a deadlock by using ceph_get_caps.  Thus, we'll करो some
	 * retry dance instead to try to get both capabilities.
	 */
	ret = ceph_try_get_caps(file_inode(src_filp),
				CEPH_CAP_खाता_RD, CEPH_CAP_खाता_SHARED,
				false, src_got);
	अगर (ret <= 0) अणु
		/* Start by dropping dst_ci caps and getting src_ci caps */
		ceph_put_cap_refs(ceph_inode(file_inode(dst_filp)), *dst_got);
		अगर (retrying) अणु
			अगर (!ret)
				/* ceph_try_get_caps masks EAGAIN */
				ret = -EAGAIN;
			वापस ret;
		पूर्ण
		ret = ceph_get_caps(src_filp, CEPH_CAP_खाता_RD,
				    CEPH_CAP_खाता_SHARED, -1, src_got);
		अगर (ret < 0)
			वापस ret;
		/*... drop src_ci caps too, and retry */
		ceph_put_cap_refs(ceph_inode(file_inode(src_filp)), *src_got);
		retrying = true;
		जाओ retry_caps;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम put_rd_wr_caps(काष्ठा ceph_inode_info *src_ci, पूर्णांक src_got,
			   काष्ठा ceph_inode_info *dst_ci, पूर्णांक dst_got)
अणु
	ceph_put_cap_refs(src_ci, src_got);
	ceph_put_cap_refs(dst_ci, dst_got);
पूर्ण

/*
 * This function करोes several size-related checks, वापसing an error अगर:
 *  - source file is smaller than off+len
 *  - destination file size is not OK (inode_newsize_ok())
 *  - max bytes quotas is exceeded
 */
अटल पूर्णांक is_file_size_ok(काष्ठा inode *src_inode, काष्ठा inode *dst_inode,
			   loff_t src_off, loff_t dst_off, माप_प्रकार len)
अणु
	loff_t size, enकरोff;

	size = i_size_पढ़ो(src_inode);
	/*
	 * Don't copy beyond source file खातापूर्ण.  Instead of simply setting length
	 * to (size - src_off), just drop to VFS शेष implementation, as the
	 * local i_size may be stale due to other clients writing to the source
	 * inode.
	 */
	अगर (src_off + len > size) अणु
		करोut("Copy beyond EOF (%llu + %zu > %llu)\n",
		     src_off, len, size);
		वापस -EOPNOTSUPP;
	पूर्ण
	size = i_size_पढ़ो(dst_inode);

	enकरोff = dst_off + len;
	अगर (inode_newsize_ok(dst_inode, enकरोff))
		वापस -EOPNOTSUPP;

	अगर (ceph_quota_is_max_bytes_exceeded(dst_inode, enकरोff))
		वापस -EDQUOT;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ceph_करो_objects_copy(काष्ठा ceph_inode_info *src_ci, u64 *src_off,
				    काष्ठा ceph_inode_info *dst_ci, u64 *dst_off,
				    काष्ठा ceph_fs_client *fsc,
				    माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा ceph_object_locator src_oloc, dst_oloc;
	काष्ठा ceph_object_id src_oid, dst_oid;
	माप_प्रकार bytes = 0;
	u64 src_objnum, src_objoff, dst_objnum, dst_objoff;
	u32 src_objlen, dst_objlen;
	u32 object_size = src_ci->i_layout.object_size;
	पूर्णांक ret;

	src_oloc.pool = src_ci->i_layout.pool_id;
	src_oloc.pool_ns = ceph_try_get_string(src_ci->i_layout.pool_ns);
	dst_oloc.pool = dst_ci->i_layout.pool_id;
	dst_oloc.pool_ns = ceph_try_get_string(dst_ci->i_layout.pool_ns);

	जबतक (len >= object_size) अणु
		ceph_calc_file_object_mapping(&src_ci->i_layout, *src_off,
					      object_size, &src_objnum,
					      &src_objoff, &src_objlen);
		ceph_calc_file_object_mapping(&dst_ci->i_layout, *dst_off,
					      object_size, &dst_objnum,
					      &dst_objoff, &dst_objlen);
		ceph_oid_init(&src_oid);
		ceph_oid_म_लिखो(&src_oid, "%llx.%08llx",
				src_ci->i_vino.ino, src_objnum);
		ceph_oid_init(&dst_oid);
		ceph_oid_म_लिखो(&dst_oid, "%llx.%08llx",
				dst_ci->i_vino.ino, dst_objnum);
		/* Do an object remote copy */
		ret = ceph_osdc_copy_from(&fsc->client->osdc,
					  src_ci->i_vino.snap, 0,
					  &src_oid, &src_oloc,
					  CEPH_OSD_OP_FLAG_FADVISE_SEQUENTIAL |
					  CEPH_OSD_OP_FLAG_FADVISE_NOCACHE,
					  &dst_oid, &dst_oloc,
					  CEPH_OSD_OP_FLAG_FADVISE_SEQUENTIAL |
					  CEPH_OSD_OP_FLAG_FADVISE_DONTNEED,
					  dst_ci->i_truncate_seq,
					  dst_ci->i_truncate_size,
					  CEPH_OSD_COPY_FROM_FLAG_TRUNCATE_SEQ);
		अगर (ret) अणु
			अगर (ret == -EOPNOTSUPP) अणु
				fsc->have_copy_from2 = false;
				pr_notice("OSDs don't support copy-from2; disabling copy offload\n");
			पूर्ण
			करोut("ceph_osdc_copy_from returned %d\n", ret);
			अगर (!bytes)
				bytes = ret;
			जाओ out;
		पूर्ण
		len -= object_size;
		bytes += object_size;
		*src_off += object_size;
		*dst_off += object_size;
	पूर्ण

out:
	ceph_oloc_destroy(&src_oloc);
	ceph_oloc_destroy(&dst_oloc);
	वापस bytes;
पूर्ण

अटल sमाप_प्रकार __ceph_copy_file_range(काष्ठा file *src_file, loff_t src_off,
				      काष्ठा file *dst_file, loff_t dst_off,
				      माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *src_inode = file_inode(src_file);
	काष्ठा inode *dst_inode = file_inode(dst_file);
	काष्ठा ceph_inode_info *src_ci = ceph_inode(src_inode);
	काष्ठा ceph_inode_info *dst_ci = ceph_inode(dst_inode);
	काष्ठा ceph_cap_flush *pपुनः_स्मृति_cf;
	काष्ठा ceph_fs_client *src_fsc = ceph_inode_to_client(src_inode);
	loff_t size;
	sमाप_प्रकार ret = -EIO, bytes;
	u64 src_objnum, dst_objnum, src_objoff, dst_objoff;
	u32 src_objlen, dst_objlen;
	पूर्णांक src_got = 0, dst_got = 0, err, dirty;

	अगर (src_inode->i_sb != dst_inode->i_sb) अणु
		काष्ठा ceph_fs_client *dst_fsc = ceph_inode_to_client(dst_inode);

		अगर (ceph_fsid_compare(&src_fsc->client->fsid,
				      &dst_fsc->client->fsid)) अणु
			करोut("Copying files across clusters: src: %pU dst: %pU\n",
			     &src_fsc->client->fsid, &dst_fsc->client->fsid);
			वापस -EXDEV;
		पूर्ण
	पूर्ण
	अगर (ceph_snap(dst_inode) != CEPH_NOSNAP)
		वापस -EROFS;

	/*
	 * Some of the checks below will वापस -EOPNOTSUPP, which will क्रमce a
	 * fallback to the शेष VFS copy_file_range implementation.  This is
	 * desirable in several हालs (क्रम ex, the 'len' is smaller than the
	 * size of the objects, or in हालs where that would be more
	 * efficient).
	 */

	अगर (ceph_test_mount_opt(src_fsc, NOCOPYFROM))
		वापस -EOPNOTSUPP;

	अगर (!src_fsc->have_copy_from2)
		वापस -EOPNOTSUPP;

	/*
	 * Striped file layouts require that we copy partial objects, but the
	 * OSD copy-from operation only supports full-object copies.  Limit
	 * this to non-striped file layouts क्रम now.
	 */
	अगर ((src_ci->i_layout.stripe_unit != dst_ci->i_layout.stripe_unit) ||
	    (src_ci->i_layout.stripe_count != 1) ||
	    (dst_ci->i_layout.stripe_count != 1) ||
	    (src_ci->i_layout.object_size != dst_ci->i_layout.object_size)) अणु
		करोut("Invalid src/dst files layout\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (len < src_ci->i_layout.object_size)
		वापस -EOPNOTSUPP; /* no remote copy will be करोne */

	pपुनः_स्मृति_cf = ceph_alloc_cap_flush();
	अगर (!pपुनः_स्मृति_cf)
		वापस -ENOMEM;

	/* Start by sync'ing the source and destination files */
	ret = file_ग_लिखो_and_रुको_range(src_file, src_off, (src_off + len));
	अगर (ret < 0) अणु
		करोut("failed to write src file (%zd)\n", ret);
		जाओ out;
	पूर्ण
	ret = file_ग_लिखो_and_रुको_range(dst_file, dst_off, (dst_off + len));
	अगर (ret < 0) अणु
		करोut("failed to write dst file (%zd)\n", ret);
		जाओ out;
	पूर्ण

	/*
	 * We need खाता_WR caps क्रम dst_ci and खाता_RD क्रम src_ci as other
	 * clients may have dirty data in their caches.  And OSDs know nothing
	 * about caps, so they can't safely करो the remote object copies.
	 */
	err = get_rd_wr_caps(src_file, &src_got,
			     dst_file, (dst_off + len), &dst_got);
	अगर (err < 0) अणु
		करोut("get_rd_wr_caps returned %d\n", err);
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	ret = is_file_size_ok(src_inode, dst_inode, src_off, dst_off, len);
	अगर (ret < 0)
		जाओ out_caps;

	/* Drop dst file cached pages */
	ret = invalidate_inode_pages2_range(dst_inode->i_mapping,
					    dst_off >> PAGE_SHIFT,
					    (dst_off + len) >> PAGE_SHIFT);
	अगर (ret < 0) अणु
		करोut("Failed to invalidate inode pages (%zd)\n", ret);
		ret = 0; /* XXX */
	पूर्ण
	ceph_calc_file_object_mapping(&src_ci->i_layout, src_off,
				      src_ci->i_layout.object_size,
				      &src_objnum, &src_objoff, &src_objlen);
	ceph_calc_file_object_mapping(&dst_ci->i_layout, dst_off,
				      dst_ci->i_layout.object_size,
				      &dst_objnum, &dst_objoff, &dst_objlen);
	/* object-level offsets need to the same */
	अगर (src_objoff != dst_objoff) अणु
		ret = -EOPNOTSUPP;
		जाओ out_caps;
	पूर्ण

	/*
	 * Do a manual copy अगर the object offset isn't object aligned.
	 * 'src_objlen' contains the bytes left until the end of the object,
	 * starting at the src_off
	 */
	अगर (src_objoff) अणु
		करोut("Initial partial copy of %u bytes\n", src_objlen);

		/*
		 * we need to temporarily drop all caps as we'll be calling
		 * अणुपढ़ो,ग_लिखोपूर्ण_iter, which will get caps again.
		 */
		put_rd_wr_caps(src_ci, src_got, dst_ci, dst_got);
		ret = करो_splice_direct(src_file, &src_off, dst_file,
				       &dst_off, src_objlen, flags);
		/* Abort on लघु copies or on error */
		अगर (ret < src_objlen) अणु
			करोut("Failed partial copy (%zd)\n", ret);
			जाओ out;
		पूर्ण
		len -= ret;
		err = get_rd_wr_caps(src_file, &src_got,
				     dst_file, (dst_off + len), &dst_got);
		अगर (err < 0)
			जाओ out;
		err = is_file_size_ok(src_inode, dst_inode,
				      src_off, dst_off, len);
		अगर (err < 0)
			जाओ out_caps;
	पूर्ण

	size = i_size_पढ़ो(dst_inode);
	bytes = ceph_करो_objects_copy(src_ci, &src_off, dst_ci, &dst_off,
				     src_fsc, len, flags);
	अगर (bytes <= 0) अणु
		अगर (!ret)
			ret = bytes;
		जाओ out_caps;
	पूर्ण
	करोut("Copied %zu bytes out of %zu\n", bytes, len);
	len -= bytes;
	ret += bytes;

	file_update_समय(dst_file);
	inode_inc_iversion_raw(dst_inode);

	अगर (dst_off > size) अणु
		/* Let the MDS know about dst file size change */
		अगर (ceph_inode_set_size(dst_inode, dst_off) ||
		    ceph_quota_is_max_bytes_approaching(dst_inode, dst_off))
			ceph_check_caps(dst_ci, CHECK_CAPS_AUTHONLY, शून्य);
	पूर्ण
	/* Mark Fw dirty */
	spin_lock(&dst_ci->i_ceph_lock);
	dst_ci->i_अंतरभूत_version = CEPH_INLINE_NONE;
	dirty = __ceph_mark_dirty_caps(dst_ci, CEPH_CAP_खाता_WR, &pपुनः_स्मृति_cf);
	spin_unlock(&dst_ci->i_ceph_lock);
	अगर (dirty)
		__mark_inode_dirty(dst_inode, dirty);

out_caps:
	put_rd_wr_caps(src_ci, src_got, dst_ci, dst_got);

	/*
	 * Do the final manual copy अगर we still have some bytes left, unless
	 * there were errors in remote object copies (len >= object_size).
	 */
	अगर (len && (len < src_ci->i_layout.object_size)) अणु
		करोut("Final partial copy of %zu bytes\n", len);
		bytes = करो_splice_direct(src_file, &src_off, dst_file,
					 &dst_off, len, flags);
		अगर (bytes > 0)
			ret += bytes;
		अन्यथा
			करोut("Failed partial copy (%zd)\n", bytes);
	पूर्ण

out:
	ceph_मुक्त_cap_flush(pपुनः_स्मृति_cf);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ceph_copy_file_range(काष्ठा file *src_file, loff_t src_off,
				    काष्ठा file *dst_file, loff_t dst_off,
				    माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	sमाप_प्रकार ret;

	ret = __ceph_copy_file_range(src_file, src_off, dst_file, dst_off,
				     len, flags);

	अगर (ret == -EOPNOTSUPP || ret == -EXDEV)
		ret = generic_copy_file_range(src_file, src_off, dst_file,
					      dst_off, len, flags);
	वापस ret;
पूर्ण

स्थिर काष्ठा file_operations ceph_file_fops = अणु
	.खोलो = ceph_खोलो,
	.release = ceph_release,
	.llseek = ceph_llseek,
	.पढ़ो_iter = ceph_पढ़ो_iter,
	.ग_लिखो_iter = ceph_ग_लिखो_iter,
	.mmap = ceph_mmap,
	.fsync = ceph_fsync,
	.lock = ceph_lock,
	.setlease = simple_nosetlease,
	.flock = ceph_flock,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.unlocked_ioctl = ceph_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.fallocate	= ceph_fallocate,
	.copy_file_range = ceph_copy_file_range,
पूर्ण;
