<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * namei.c
 *
 * Create and नाम file, directory, symlinks
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 *
 *  Portions of this code from linux/fs/ext3/dir.c
 *
 *  Copyright (C) 1992, 1993, 1994, 1995
 *  Remy Card (card@masi.ibp.fr)
 *  Laborम_से_पre MASI - Institut Blaise pascal
 *  Universite Pierre et Marie Curie (Paris VI)
 *
 *   from
 *
 *   linux/fs/minix/dir.c
 *
 *   Copyright (C) 1991, 1992 Linux Torvalds
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/quotaops.h>
#समावेश <linux/iversion.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "dcache.h"
#समावेश "dir.h"
#समावेश "dlmglue.h"
#समावेश "extent_map.h"
#समावेश "file.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "namei.h"
#समावेश "suballoc.h"
#समावेश "super.h"
#समावेश "symlink.h"
#समावेश "sysfile.h"
#समावेश "uptodate.h"
#समावेश "xattr.h"
#समावेश "acl.h"
#समावेश "ocfs2_trace.h"
#समावेश "ioctl.h"

#समावेश "buffer_head_io.h"

अटल पूर्णांक ocfs2_mknod_locked(काष्ठा ocfs2_super *osb,
			      काष्ठा inode *dir,
			      काष्ठा inode *inode,
			      dev_t dev,
			      काष्ठा buffer_head **new_fe_bh,
			      काष्ठा buffer_head *parent_fe_bh,
			      handle_t *handle,
			      काष्ठा ocfs2_alloc_context *inode_ac);

अटल पूर्णांक ocfs2_prepare_orphan_dir(काष्ठा ocfs2_super *osb,
				    काष्ठा inode **ret_orphan_dir,
				    u64 blkno,
				    अक्षर *name,
				    काष्ठा ocfs2_dir_lookup_result *lookup,
				    bool dio);

अटल पूर्णांक ocfs2_orphan_add(काष्ठा ocfs2_super *osb,
			    handle_t *handle,
			    काष्ठा inode *inode,
			    काष्ठा buffer_head *fe_bh,
			    अक्षर *name,
			    काष्ठा ocfs2_dir_lookup_result *lookup,
			    काष्ठा inode *orphan_dir_inode,
			    bool dio);

अटल पूर्णांक ocfs2_create_symlink_data(काष्ठा ocfs2_super *osb,
				     handle_t *handle,
				     काष्ठा inode *inode,
				     स्थिर अक्षर *symname);

अटल पूर्णांक ocfs2_द्विगुन_lock(काष्ठा ocfs2_super *osb,
			     काष्ठा buffer_head **bh1,
			     काष्ठा inode *inode1,
			     काष्ठा buffer_head **bh2,
			     काष्ठा inode *inode2,
			     पूर्णांक नाम);

अटल व्योम ocfs2_द्विगुन_unlock(काष्ठा inode *inode1, काष्ठा inode *inode2);
/* An orphan dir name is an 8 byte value, prपूर्णांकed as a hex string */
#घोषणा OCFS2_ORPHAN_NAMELEN ((पूर्णांक)(2 * माप(u64)))

अटल काष्ठा dentry *ocfs2_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				   अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक status;
	u64 blkno;
	काष्ठा inode *inode = शून्य;
	काष्ठा dentry *ret;
	काष्ठा ocfs2_inode_info *oi;

	trace_ocfs2_lookup(dir, dentry, dentry->d_name.len,
			   dentry->d_name.name,
			   (अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno, 0);

	अगर (dentry->d_name.len > OCFS2_MAX_खाताNAME_LEN) अणु
		ret = ERR_PTR(-ENAMETOOLONG);
		जाओ bail;
	पूर्ण

	status = ocfs2_inode_lock_nested(dir, शून्य, 0, OI_LS_PARENT);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		ret = ERR_PTR(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_lookup_ino_from_name(dir, dentry->d_name.name,
					    dentry->d_name.len, &blkno);
	अगर (status < 0)
		जाओ bail_add;

	inode = ocfs2_iget(OCFS2_SB(dir->i_sb), blkno, 0, 0);
	अगर (IS_ERR(inode)) अणु
		ret = ERR_PTR(-EACCES);
		जाओ bail_unlock;
	पूर्ण

	oi = OCFS2_I(inode);
	/* Clear any orphaned state... If we were able to look up the
	 * inode from a directory, it certainly can't be orphaned. We
	 * might have the bad state from a node which पूर्णांकended to
	 * orphan this inode but crashed beक्रमe it could commit the
	 * unlink. */
	spin_lock(&oi->ip_lock);
	oi->ip_flags &= ~OCFS2_INODE_MAYBE_ORPHANED;
	spin_unlock(&oi->ip_lock);

bail_add:
	ret = d_splice_alias(inode, dentry);

	अगर (inode) अणु
		/*
		 * If d_splice_alias() finds a DCACHE_DISCONNECTED
		 * dentry, it will d_move() it on top of ourse. The
		 * वापस value will indicate this however, so in
		 * those हालs, we चयन them around क्रम the locking
		 * code.
		 *
		 * NOTE: This dentry alपढ़ोy has ->d_op set from
		 * ocfs2_get_parent() and ocfs2_get_dentry()
		 */
		अगर (!IS_ERR_OR_शून्य(ret))
			dentry = ret;

		status = ocfs2_dentry_attach_lock(dentry, inode,
						  OCFS2_I(dir)->ip_blkno);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			ret = ERR_PTR(status);
			जाओ bail_unlock;
		पूर्ण
	पूर्ण अन्यथा
		ocfs2_dentry_attach_gen(dentry);

bail_unlock:
	/* Don't drop the cluster lock until *after* the d_add --
	 * unlink on another node will message us to हटाओ that
	 * dentry under this lock so otherwise we can race this with
	 * the करोwnconvert thपढ़ो and have a stale dentry. */
	ocfs2_inode_unlock(dir, 0);

bail:

	trace_ocfs2_lookup_ret(ret);

	वापस ret;
पूर्ण

अटल काष्ठा inode *ocfs2_get_init_inode(काष्ठा inode *dir, umode_t mode)
अणु
	काष्ठा inode *inode;
	पूर्णांक status;

	inode = new_inode(dir->i_sb);
	अगर (!inode) अणु
		mlog(ML_ERROR, "new_inode failed!\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* populate as many fields early on as possible - many of
	 * these are used by the support functions here and in
	 * callers. */
	अगर (S_ISसूची(mode))
		set_nlink(inode, 2);
	inode_init_owner(&init_user_ns, inode, dir, mode);
	status = dquot_initialize(inode);
	अगर (status)
		वापस ERR_PTR(status);

	वापस inode;
पूर्ण

अटल व्योम ocfs2_cleanup_add_entry_failure(काष्ठा ocfs2_super *osb,
		काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा ocfs2_dentry_lock *dl = dentry->d_fsdata;

	ocfs2_simple_drop_lockres(osb, &dl->dl_lockres);
	ocfs2_lock_res_मुक्त(&dl->dl_lockres);
	BUG_ON(dl->dl_count != 1);
	spin_lock(&dentry_attach_lock);
	dentry->d_fsdata = शून्य;
	spin_unlock(&dentry_attach_lock);
	kमुक्त(dl);
	iput(inode);
पूर्ण

अटल पूर्णांक ocfs2_mknod(काष्ठा user_namespace *mnt_userns,
		       काष्ठा inode *dir,
		       काष्ठा dentry *dentry,
		       umode_t mode,
		       dev_t dev)
अणु
	पूर्णांक status = 0;
	काष्ठा buffer_head *parent_fe_bh = शून्य;
	handle_t *handle = शून्य;
	काष्ठा ocfs2_super *osb;
	काष्ठा ocfs2_dinode *dirfe;
	काष्ठा buffer_head *new_fe_bh = शून्य;
	काष्ठा inode *inode = शून्य;
	काष्ठा ocfs2_alloc_context *inode_ac = शून्य;
	काष्ठा ocfs2_alloc_context *data_ac = शून्य;
	काष्ठा ocfs2_alloc_context *meta_ac = शून्य;
	पूर्णांक want_clusters = 0;
	पूर्णांक want_meta = 0;
	पूर्णांक xattr_credits = 0;
	काष्ठा ocfs2_security_xattr_info si = अणु
		.enable = 1,
	पूर्ण;
	पूर्णांक did_quota_inode = 0;
	काष्ठा ocfs2_dir_lookup_result lookup = अणु शून्य, पूर्ण;
	sigset_t oldset;
	पूर्णांक did_block_संकेतs = 0;
	काष्ठा ocfs2_dentry_lock *dl = शून्य;

	trace_ocfs2_mknod(dir, dentry, dentry->d_name.len, dentry->d_name.name,
			  (अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno,
			  (अचिन्हित दीर्घ)dev, mode);

	status = dquot_initialize(dir);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	/* get our super block */
	osb = OCFS2_SB(dir->i_sb);

	status = ocfs2_inode_lock(dir, &parent_fe_bh, 1);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	अगर (S_ISसूची(mode) && (dir->i_nlink >= ocfs2_link_max(osb))) अणु
		status = -EMLINK;
		जाओ leave;
	पूर्ण

	dirfe = (काष्ठा ocfs2_dinode *) parent_fe_bh->b_data;
	अगर (!ocfs2_पढ़ो_links_count(dirfe)) अणु
		/* can't make a file in a deleted directory. */
		status = -ENOENT;
		जाओ leave;
	पूर्ण

	status = ocfs2_check_dir_क्रम_entry(dir, dentry->d_name.name,
					   dentry->d_name.len);
	अगर (status)
		जाओ leave;

	/* get a spot inside the dir. */
	status = ocfs2_prepare_dir_क्रम_insert(osb, dir, parent_fe_bh,
					      dentry->d_name.name,
					      dentry->d_name.len, &lookup);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	/* reserve an inode spot */
	status = ocfs2_reserve_new_inode(osb, &inode_ac);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	inode = ocfs2_get_init_inode(dir, mode);
	अगर (IS_ERR(inode)) अणु
		status = PTR_ERR(inode);
		inode = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	/* get security xattr */
	status = ocfs2_init_security_get(inode, dir, &dentry->d_name, &si);
	अगर (status) अणु
		अगर (status == -EOPNOTSUPP)
			si.enable = 0;
		अन्यथा अणु
			mlog_त्रुटि_सं(status);
			जाओ leave;
		पूर्ण
	पूर्ण

	/* calculate meta data/clusters क्रम setting security and acl xattr */
	status = ocfs2_calc_xattr_init(dir, parent_fe_bh, mode,
				       &si, &want_clusters,
				       &xattr_credits, &want_meta);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	/* Reserve a cluster अगर creating an extent based directory. */
	अगर (S_ISसूची(mode) && !ocfs2_supports_अंतरभूत_data(osb)) अणु
		want_clusters += 1;

		/* Dir indexing requires extra space as well */
		अगर (ocfs2_supports_indexed_dirs(osb))
			want_meta++;
	पूर्ण

	status = ocfs2_reserve_new_metadata_blocks(osb, want_meta, &meta_ac);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	status = ocfs2_reserve_clusters(osb, want_clusters, &data_ac);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	handle = ocfs2_start_trans(osb, ocfs2_mknod_credits(osb->sb,
							    S_ISसूची(mode),
							    xattr_credits));
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	/* Starting to change things, restart is no दीर्घer possible. */
	ocfs2_block_संकेतs(&oldset);
	did_block_संकेतs = 1;

	status = dquot_alloc_inode(inode);
	अगर (status)
		जाओ leave;
	did_quota_inode = 1;

	/* करो the real work now. */
	status = ocfs2_mknod_locked(osb, dir, inode, dev,
				    &new_fe_bh, parent_fe_bh, handle,
				    inode_ac);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	अगर (S_ISसूची(mode)) अणु
		status = ocfs2_fill_new_dir(osb, handle, dir, inode,
					    new_fe_bh, data_ac, meta_ac);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ leave;
		पूर्ण

		status = ocfs2_journal_access_di(handle, INODE_CACHE(dir),
						 parent_fe_bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ leave;
		पूर्ण
		ocfs2_add_links_count(dirfe, 1);
		ocfs2_journal_dirty(handle, parent_fe_bh);
		inc_nlink(dir);
	पूर्ण

	status = ocfs2_init_acl(handle, inode, dir, new_fe_bh, parent_fe_bh,
			 meta_ac, data_ac);

	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ roll_back;
	पूर्ण

	अगर (si.enable) अणु
		status = ocfs2_init_security_set(handle, inode, new_fe_bh, &si,
						 meta_ac, data_ac);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ roll_back;
		पूर्ण
	पूर्ण

	/*
	 * Do this beक्रमe adding the entry to the directory. We add
	 * also set d_op after success so that ->d_iput() will cleanup
	 * the dentry lock even अगर ocfs2_add_entry() fails below.
	 */
	status = ocfs2_dentry_attach_lock(dentry, inode,
					  OCFS2_I(dir)->ip_blkno);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ roll_back;
	पूर्ण

	dl = dentry->d_fsdata;

	status = ocfs2_add_entry(handle, dentry, inode,
				 OCFS2_I(inode)->ip_blkno, parent_fe_bh,
				 &lookup);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ roll_back;
	पूर्ण

	insert_inode_hash(inode);
	d_instantiate(dentry, inode);
	status = 0;

roll_back:
	अगर (status < 0 && S_ISसूची(mode)) अणु
		ocfs2_add_links_count(dirfe, -1);
		drop_nlink(dir);
	पूर्ण

leave:
	अगर (status < 0 && did_quota_inode)
		dquot_मुक्त_inode(inode);
	अगर (handle)
		ocfs2_commit_trans(osb, handle);

	ocfs2_inode_unlock(dir, 1);
	अगर (did_block_संकेतs)
		ocfs2_unblock_संकेतs(&oldset);

	brअन्यथा(new_fe_bh);
	brअन्यथा(parent_fe_bh);
	kमुक्त(si.value);

	ocfs2_मुक्त_dir_lookup_result(&lookup);

	अगर (inode_ac)
		ocfs2_मुक्त_alloc_context(inode_ac);

	अगर (data_ac)
		ocfs2_मुक्त_alloc_context(data_ac);

	अगर (meta_ac)
		ocfs2_मुक्त_alloc_context(meta_ac);

	/*
	 * We should call iput after the i_mutex of the biपंचांगap been
	 * unlocked in ocfs2_मुक्त_alloc_context, or the
	 * ocfs2_delete_inode will mutex_lock again.
	 */
	अगर ((status < 0) && inode) अणु
		अगर (dl)
			ocfs2_cleanup_add_entry_failure(osb, dentry, inode);

		OCFS2_I(inode)->ip_flags |= OCFS2_INODE_SKIP_ORPHAN_सूची;
		clear_nlink(inode);
		iput(inode);
	पूर्ण

	अगर (status)
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

अटल पूर्णांक __ocfs2_mknod_locked(काष्ठा inode *dir,
				काष्ठा inode *inode,
				dev_t dev,
				काष्ठा buffer_head **new_fe_bh,
				काष्ठा buffer_head *parent_fe_bh,
				handle_t *handle,
				काष्ठा ocfs2_alloc_context *inode_ac,
				u64 fe_blkno, u64 suballoc_loc, u16 suballoc_bit)
अणु
	पूर्णांक status = 0;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	काष्ठा ocfs2_dinode *fe = शून्य;
	काष्ठा ocfs2_extent_list *fel;
	u16 feat;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा बारpec64 ts;

	*new_fe_bh = शून्य;

	/* populate as many fields early on as possible - many of
	 * these are used by the support functions here and in
	 * callers. */
	inode->i_ino = ino_from_blkno(osb->sb, fe_blkno);
	oi->ip_blkno = fe_blkno;
	spin_lock(&osb->osb_lock);
	inode->i_generation = osb->s_next_generation++;
	spin_unlock(&osb->osb_lock);

	*new_fe_bh = sb_getblk(osb->sb, fe_blkno);
	अगर (!*new_fe_bh) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण
	ocfs2_set_new_buffer_uptodate(INODE_CACHE(inode), *new_fe_bh);

	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode),
					 *new_fe_bh,
					 OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	fe = (काष्ठा ocfs2_dinode *) (*new_fe_bh)->b_data;
	स_रखो(fe, 0, osb->sb->s_blocksize);

	fe->i_generation = cpu_to_le32(inode->i_generation);
	fe->i_fs_generation = cpu_to_le32(osb->fs_generation);
	fe->i_blkno = cpu_to_le64(fe_blkno);
	fe->i_suballoc_loc = cpu_to_le64(suballoc_loc);
	fe->i_suballoc_bit = cpu_to_le16(suballoc_bit);
	fe->i_suballoc_slot = cpu_to_le16(inode_ac->ac_alloc_slot);
	fe->i_uid = cpu_to_le32(i_uid_पढ़ो(inode));
	fe->i_gid = cpu_to_le32(i_gid_पढ़ो(inode));
	fe->i_mode = cpu_to_le16(inode->i_mode);
	अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode))
		fe->id1.dev1.i_rdev = cpu_to_le64(huge_encode_dev(dev));

	ocfs2_set_links_count(fe, inode->i_nlink);

	fe->i_last_eb_blk = 0;
	म_नकल(fe->i_signature, OCFS2_INODE_SIGNATURE);
	fe->i_flags |= cpu_to_le32(OCFS2_VALID_FL);
	kसमय_get_real_ts64(&ts);
	fe->i_aसमय = fe->i_स_समय = fe->i_mसमय =
		cpu_to_le64(ts.tv_sec);
	fe->i_mसमय_nsec = fe->i_स_समय_nsec = fe->i_aसमय_nsec =
		cpu_to_le32(ts.tv_nsec);
	fe->i_dसमय = 0;

	/*
	 * If supported, directories start with अंतरभूत data. If अंतरभूत
	 * isn't supported, but indexing is, we start them as indexed.
	 */
	feat = le16_to_cpu(fe->i_dyn_features);
	अगर (S_ISसूची(inode->i_mode) && ocfs2_supports_अंतरभूत_data(osb)) अणु
		fe->i_dyn_features = cpu_to_le16(feat | OCFS2_INLINE_DATA_FL);

		fe->id2.i_data.id_count = cpu_to_le16(
				ocfs2_max_अंतरभूत_data_with_xattr(osb->sb, fe));
	पूर्ण अन्यथा अणु
		fel = &fe->id2.i_list;
		fel->l_tree_depth = 0;
		fel->l_next_मुक्त_rec = 0;
		fel->l_count = cpu_to_le16(ocfs2_extent_recs_per_inode(osb->sb));
	पूर्ण

	ocfs2_journal_dirty(handle, *new_fe_bh);

	ocfs2_populate_inode(inode, fe, 1);
	ocfs2_ci_set_new(osb, INODE_CACHE(inode));
	अगर (!ocfs2_mount_local(osb)) अणु
		status = ocfs2_create_new_inode_locks(inode);
		अगर (status < 0)
			mlog_त्रुटि_सं(status);
	पूर्ण

	ocfs2_update_inode_fsync_trans(handle, inode, 1);

leave:
	अगर (status < 0) अणु
		अगर (*new_fe_bh) अणु
			brअन्यथा(*new_fe_bh);
			*new_fe_bh = शून्य;
		पूर्ण
	पूर्ण

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_mknod_locked(काष्ठा ocfs2_super *osb,
			      काष्ठा inode *dir,
			      काष्ठा inode *inode,
			      dev_t dev,
			      काष्ठा buffer_head **new_fe_bh,
			      काष्ठा buffer_head *parent_fe_bh,
			      handle_t *handle,
			      काष्ठा ocfs2_alloc_context *inode_ac)
अणु
	पूर्णांक status = 0;
	u64 suballoc_loc, fe_blkno = 0;
	u16 suballoc_bit;

	*new_fe_bh = शून्य;

	status = ocfs2_claim_new_inode(handle, dir, parent_fe_bh,
				       inode_ac, &suballoc_loc,
				       &suballoc_bit, &fe_blkno);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	status = __ocfs2_mknod_locked(dir, inode, dev, new_fe_bh,
				    parent_fe_bh, handle, inode_ac,
				    fe_blkno, suballoc_loc, suballoc_bit);
	अगर (status < 0) अणु
		u64 bg_blkno = ocfs2_which_suballoc_group(fe_blkno, suballoc_bit);
		पूर्णांक पंचांगp = ocfs2_मुक्त_suballoc_bits(handle, inode_ac->ac_inode,
				inode_ac->ac_bh, suballoc_bit, bg_blkno, 1);
		अगर (पंचांगp)
			mlog_त्रुटि_सं(पंचांगp);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns,
		       काष्ठा inode *dir,
		       काष्ठा dentry *dentry,
		       umode_t mode)
अणु
	पूर्णांक ret;

	trace_ocfs2_सूची_गढ़ो(dir, dentry, dentry->d_name.len, dentry->d_name.name,
			  OCFS2_I(dir)->ip_blkno, mode);
	ret = ocfs2_mknod(&init_user_ns, dir, dentry, mode | S_IFसूची, 0);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_create(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *dir,
			काष्ठा dentry *dentry,
			umode_t mode,
			bool excl)
अणु
	पूर्णांक ret;

	trace_ocfs2_create(dir, dentry, dentry->d_name.len, dentry->d_name.name,
			   (अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno, mode);
	ret = ocfs2_mknod(&init_user_ns, dir, dentry, mode | S_IFREG, 0);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_link(काष्ठा dentry *old_dentry,
		      काष्ठा inode *dir,
		      काष्ठा dentry *dentry)
अणु
	handle_t *handle;
	काष्ठा inode *inode = d_inode(old_dentry);
	काष्ठा inode *old_dir = d_inode(old_dentry->d_parent);
	पूर्णांक err;
	काष्ठा buffer_head *fe_bh = शून्य;
	काष्ठा buffer_head *old_dir_bh = शून्य;
	काष्ठा buffer_head *parent_fe_bh = शून्य;
	काष्ठा ocfs2_dinode *fe = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	काष्ठा ocfs2_dir_lookup_result lookup = अणु शून्य, पूर्ण;
	sigset_t oldset;
	u64 old_de_ino;

	trace_ocfs2_link((अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
			 old_dentry->d_name.len, old_dentry->d_name.name,
			 dentry->d_name.len, dentry->d_name.name);

	अगर (S_ISसूची(inode->i_mode))
		वापस -EPERM;

	err = dquot_initialize(dir);
	अगर (err) अणु
		mlog_त्रुटि_सं(err);
		वापस err;
	पूर्ण

	err = ocfs2_द्विगुन_lock(osb, &old_dir_bh, old_dir,
			&parent_fe_bh, dir, 0);
	अगर (err < 0) अणु
		अगर (err != -ENOENT)
			mlog_त्रुटि_सं(err);
		वापस err;
	पूर्ण

	/* make sure both dirs have bhs
	 * get an extra ref on old_dir_bh अगर old==new */
	अगर (!parent_fe_bh) अणु
		अगर (old_dir_bh) अणु
			parent_fe_bh = old_dir_bh;
			get_bh(parent_fe_bh);
		पूर्ण अन्यथा अणु
			mlog(ML_ERROR, "%s: no old_dir_bh!\n", osb->uuid_str);
			err = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!dir->i_nlink) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	err = ocfs2_lookup_ino_from_name(old_dir, old_dentry->d_name.name,
			old_dentry->d_name.len, &old_de_ino);
	अगर (err) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	/*
	 * Check whether another node हटाओd the source inode जबतक we
	 * were in the vfs.
	 */
	अगर (old_de_ino != OCFS2_I(inode)->ip_blkno) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	err = ocfs2_check_dir_क्रम_entry(dir, dentry->d_name.name,
					dentry->d_name.len);
	अगर (err)
		जाओ out;

	err = ocfs2_prepare_dir_क्रम_insert(osb, dir, parent_fe_bh,
					   dentry->d_name.name,
					   dentry->d_name.len, &lookup);
	अगर (err < 0) अणु
		mlog_त्रुटि_सं(err);
		जाओ out;
	पूर्ण

	err = ocfs2_inode_lock(inode, &fe_bh, 1);
	अगर (err < 0) अणु
		अगर (err != -ENOENT)
			mlog_त्रुटि_सं(err);
		जाओ out;
	पूर्ण

	fe = (काष्ठा ocfs2_dinode *) fe_bh->b_data;
	अगर (ocfs2_पढ़ो_links_count(fe) >= ocfs2_link_max(osb)) अणु
		err = -EMLINK;
		जाओ out_unlock_inode;
	पूर्ण

	handle = ocfs2_start_trans(osb, ocfs2_link_credits(osb->sb));
	अगर (IS_ERR(handle)) अणु
		err = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(err);
		जाओ out_unlock_inode;
	पूर्ण

	/* Starting to change things, restart is no दीर्घer possible. */
	ocfs2_block_संकेतs(&oldset);

	err = ocfs2_journal_access_di(handle, INODE_CACHE(inode), fe_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (err < 0) अणु
		mlog_त्रुटि_सं(err);
		जाओ out_commit;
	पूर्ण

	inc_nlink(inode);
	inode->i_स_समय = current_समय(inode);
	ocfs2_set_links_count(fe, inode->i_nlink);
	fe->i_स_समय = cpu_to_le64(inode->i_स_समय.tv_sec);
	fe->i_स_समय_nsec = cpu_to_le32(inode->i_स_समय.tv_nsec);
	ocfs2_journal_dirty(handle, fe_bh);

	err = ocfs2_add_entry(handle, dentry, inode,
			      OCFS2_I(inode)->ip_blkno,
			      parent_fe_bh, &lookup);
	अगर (err) अणु
		ocfs2_add_links_count(fe, -1);
		drop_nlink(inode);
		mlog_त्रुटि_सं(err);
		जाओ out_commit;
	पूर्ण

	err = ocfs2_dentry_attach_lock(dentry, inode, OCFS2_I(dir)->ip_blkno);
	अगर (err) अणु
		mlog_त्रुटि_सं(err);
		जाओ out_commit;
	पूर्ण

	ihold(inode);
	d_instantiate(dentry, inode);

out_commit:
	ocfs2_commit_trans(osb, handle);
	ocfs2_unblock_संकेतs(&oldset);
out_unlock_inode:
	ocfs2_inode_unlock(inode, 1);

out:
	ocfs2_द्विगुन_unlock(old_dir, dir);

	brअन्यथा(fe_bh);
	brअन्यथा(parent_fe_bh);
	brअन्यथा(old_dir_bh);

	ocfs2_मुक्त_dir_lookup_result(&lookup);

	अगर (err)
		mlog_त्रुटि_सं(err);

	वापस err;
पूर्ण

/*
 * Takes and drops an exclusive lock on the given dentry. This will
 * क्रमce other nodes to drop it.
 */
अटल पूर्णांक ocfs2_remote_dentry_delete(काष्ठा dentry *dentry)
अणु
	पूर्णांक ret;

	ret = ocfs2_dentry_lock(dentry, 1);
	अगर (ret)
		mlog_त्रुटि_सं(ret);
	अन्यथा
		ocfs2_dentry_unlock(dentry, 1);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_inode_is_unlinkable(काष्ठा inode *inode)
अणु
	अगर (S_ISसूची(inode->i_mode)) अणु
		अगर (inode->i_nlink == 2)
			वापस 1;
		वापस 0;
	पूर्ण

	अगर (inode->i_nlink == 1)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_unlink(काष्ठा inode *dir,
			काष्ठा dentry *dentry)
अणु
	पूर्णांक status;
	पूर्णांक child_locked = 0;
	bool is_unlinkable = false;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा inode *orphan_dir = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	u64 blkno;
	काष्ठा ocfs2_dinode *fe = शून्य;
	काष्ठा buffer_head *fe_bh = शून्य;
	काष्ठा buffer_head *parent_node_bh = शून्य;
	handle_t *handle = शून्य;
	अक्षर orphan_name[OCFS2_ORPHAN_NAMELEN + 1];
	काष्ठा ocfs2_dir_lookup_result lookup = अणु शून्य, पूर्ण;
	काष्ठा ocfs2_dir_lookup_result orphan_insert = अणु शून्य, पूर्ण;

	trace_ocfs2_unlink(dir, dentry, dentry->d_name.len,
			   dentry->d_name.name,
			   (अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno,
			   (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);

	status = dquot_initialize(dir);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	BUG_ON(d_inode(dentry->d_parent) != dir);

	अगर (inode == osb->root_inode)
		वापस -EPERM;

	status = ocfs2_inode_lock_nested(dir, &parent_node_bh, 1,
					 OI_LS_PARENT);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	status = ocfs2_find_files_on_disk(dentry->d_name.name,
					  dentry->d_name.len, &blkno, dir,
					  &lookup);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	अगर (OCFS2_I(inode)->ip_blkno != blkno) अणु
		status = -ENOENT;

		trace_ocfs2_unlink_noent(
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
				(अचिन्हित दीर्घ दीर्घ)blkno,
				OCFS2_I(inode)->ip_flags);
		जाओ leave;
	पूर्ण

	status = ocfs2_inode_lock(inode, &fe_bh, 1);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण
	child_locked = 1;

	अगर (S_ISसूची(inode->i_mode)) अणु
		अगर (inode->i_nlink != 2 || !ocfs2_empty_dir(inode)) अणु
			status = -ENOTEMPTY;
			जाओ leave;
		पूर्ण
	पूर्ण

	status = ocfs2_remote_dentry_delete(dentry);
	अगर (status < 0) अणु
		/* This remote delete should succeed under all normal
		 * circumstances. */
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	अगर (ocfs2_inode_is_unlinkable(inode)) अणु
		status = ocfs2_prepare_orphan_dir(osb, &orphan_dir,
						  OCFS2_I(inode)->ip_blkno,
						  orphan_name, &orphan_insert,
						  false);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ leave;
		पूर्ण
		is_unlinkable = true;
	पूर्ण

	handle = ocfs2_start_trans(osb, ocfs2_unlink_credits(osb->sb));
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode), fe_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	fe = (काष्ठा ocfs2_dinode *) fe_bh->b_data;

	/* delete the name from the parent dir */
	status = ocfs2_delete_entry(handle, dir, &lookup);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	अगर (S_ISसूची(inode->i_mode))
		drop_nlink(inode);
	drop_nlink(inode);
	ocfs2_set_links_count(fe, inode->i_nlink);
	ocfs2_journal_dirty(handle, fe_bh);

	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	अगर (S_ISसूची(inode->i_mode))
		drop_nlink(dir);

	status = ocfs2_mark_inode_dirty(handle, dir, parent_node_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		अगर (S_ISसूची(inode->i_mode))
			inc_nlink(dir);
		जाओ leave;
	पूर्ण

	अगर (is_unlinkable) अणु
		status = ocfs2_orphan_add(osb, handle, inode, fe_bh,
				orphan_name, &orphan_insert, orphan_dir, false);
		अगर (status < 0)
			mlog_त्रुटि_सं(status);
	पूर्ण

leave:
	अगर (handle)
		ocfs2_commit_trans(osb, handle);

	अगर (orphan_dir) अणु
		/* This was locked क्रम us in ocfs2_prepare_orphan_dir() */
		ocfs2_inode_unlock(orphan_dir, 1);
		inode_unlock(orphan_dir);
		iput(orphan_dir);
	पूर्ण

	अगर (child_locked)
		ocfs2_inode_unlock(inode, 1);

	ocfs2_inode_unlock(dir, 1);

	brअन्यथा(fe_bh);
	brअन्यथा(parent_node_bh);

	ocfs2_मुक्त_dir_lookup_result(&orphan_insert);
	ocfs2_मुक्त_dir_lookup_result(&lookup);

	अगर (status && (status != -ENOTEMPTY) && (status != -ENOENT))
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_check_अगर_ancestor(काष्ठा ocfs2_super *osb,
		u64 src_inode_no, u64 dest_inode_no)
अणु
	पूर्णांक ret = 0, i = 0;
	u64 parent_inode_no = 0;
	u64 child_inode_no = src_inode_no;
	काष्ठा inode *child_inode;

#घोषणा MAX_LOOKUP_TIMES 32
	जबतक (1) अणु
		child_inode = ocfs2_iget(osb, child_inode_no, 0, 0);
		अगर (IS_ERR(child_inode)) अणु
			ret = PTR_ERR(child_inode);
			अवरोध;
		पूर्ण

		ret = ocfs2_inode_lock(child_inode, शून्य, 0);
		अगर (ret < 0) अणु
			iput(child_inode);
			अगर (ret != -ENOENT)
				mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		ret = ocfs2_lookup_ino_from_name(child_inode, "..", 2,
				&parent_inode_no);
		ocfs2_inode_unlock(child_inode, 0);
		iput(child_inode);
		अगर (ret < 0) अणु
			ret = -ENOENT;
			अवरोध;
		पूर्ण

		अगर (parent_inode_no == dest_inode_no) अणु
			ret = 1;
			अवरोध;
		पूर्ण

		अगर (parent_inode_no == osb->root_inode->i_ino) अणु
			ret = 0;
			अवरोध;
		पूर्ण

		child_inode_no = parent_inode_no;

		अगर (++i >= MAX_LOOKUP_TIMES) अणु
			mlog_ratelimited(ML_NOTICE, "max lookup times reached, "
					"filesystem may have nested directories, "
					"src inode: %llu, dest inode: %llu.\n",
					(अचिन्हित दीर्घ दीर्घ)src_inode_no,
					(अचिन्हित दीर्घ दीर्घ)dest_inode_no);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * The only place this should be used is नाम and link!
 * अगर they have the same id, then the 1st one is the only one locked.
 */
अटल पूर्णांक ocfs2_द्विगुन_lock(काष्ठा ocfs2_super *osb,
			     काष्ठा buffer_head **bh1,
			     काष्ठा inode *inode1,
			     काष्ठा buffer_head **bh2,
			     काष्ठा inode *inode2,
			     पूर्णांक नाम)
अणु
	पूर्णांक status;
	पूर्णांक inode1_is_ancestor, inode2_is_ancestor;
	काष्ठा ocfs2_inode_info *oi1 = OCFS2_I(inode1);
	काष्ठा ocfs2_inode_info *oi2 = OCFS2_I(inode2);

	trace_ocfs2_द्विगुन_lock((अचिन्हित दीर्घ दीर्घ)oi1->ip_blkno,
				(अचिन्हित दीर्घ दीर्घ)oi2->ip_blkno);

	अगर (*bh1)
		*bh1 = शून्य;
	अगर (*bh2)
		*bh2 = शून्य;

	/* we always want to lock the one with the lower lockid first.
	 * and अगर they are nested, we lock ancestor first */
	अगर (oi1->ip_blkno != oi2->ip_blkno) अणु
		inode1_is_ancestor = ocfs2_check_अगर_ancestor(osb, oi2->ip_blkno,
				oi1->ip_blkno);
		अगर (inode1_is_ancestor < 0) अणु
			status = inode1_is_ancestor;
			जाओ bail;
		पूर्ण

		inode2_is_ancestor = ocfs2_check_अगर_ancestor(osb, oi1->ip_blkno,
				oi2->ip_blkno);
		अगर (inode2_is_ancestor < 0) अणु
			status = inode2_is_ancestor;
			जाओ bail;
		पूर्ण

		अगर ((inode1_is_ancestor == 1) ||
				(oi1->ip_blkno < oi2->ip_blkno &&
				inode2_is_ancestor == 0)) अणु
			/* चयन id1 and id2 around */
			swap(bh2, bh1);
			swap(inode2, inode1);
		पूर्ण
		/* lock id2 */
		status = ocfs2_inode_lock_nested(inode2, bh2, 1,
				नाम == 1 ? OI_LS_RENAME1 : OI_LS_PARENT);
		अगर (status < 0) अणु
			अगर (status != -ENOENT)
				mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	/* lock id1 */
	status = ocfs2_inode_lock_nested(inode1, bh1, 1,
			नाम == 1 ?  OI_LS_RENAME2 : OI_LS_PARENT);
	अगर (status < 0) अणु
		/*
		 * An error वापस must mean that no cluster locks
		 * were held on function निकास.
		 */
		अगर (oi1->ip_blkno != oi2->ip_blkno) अणु
			ocfs2_inode_unlock(inode2, 1);
			brअन्यथा(*bh2);
			*bh2 = शून्य;
		पूर्ण

		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
	पूर्ण

	trace_ocfs2_द्विगुन_lock_end(
			(अचिन्हित दीर्घ दीर्घ)oi1->ip_blkno,
			(अचिन्हित दीर्घ दीर्घ)oi2->ip_blkno);

bail:
	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल व्योम ocfs2_द्विगुन_unlock(काष्ठा inode *inode1, काष्ठा inode *inode2)
अणु
	ocfs2_inode_unlock(inode1, 1);

	अगर (inode1 != inode2)
		ocfs2_inode_unlock(inode2, 1);
पूर्ण

अटल पूर्णांक ocfs2_नाम(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *old_dir,
			काष्ठा dentry *old_dentry,
			काष्ठा inode *new_dir,
			काष्ठा dentry *new_dentry,
			अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक status = 0, नाम_lock = 0, parents_locked = 0, target_exists = 0;
	पूर्णांक old_child_locked = 0, new_child_locked = 0, update_करोt_करोt = 0;
	काष्ठा inode *old_inode = d_inode(old_dentry);
	काष्ठा inode *new_inode = d_inode(new_dentry);
	काष्ठा inode *orphan_dir = शून्य;
	काष्ठा ocfs2_dinode *newfe = शून्य;
	अक्षर orphan_name[OCFS2_ORPHAN_NAMELEN + 1];
	काष्ठा buffer_head *newfe_bh = शून्य;
	काष्ठा buffer_head *old_inode_bh = शून्य;
	काष्ठा ocfs2_super *osb = शून्य;
	u64 newfe_blkno, old_de_ino;
	handle_t *handle = शून्य;
	काष्ठा buffer_head *old_dir_bh = शून्य;
	काष्ठा buffer_head *new_dir_bh = शून्य;
	u32 old_dir_nlink = old_dir->i_nlink;
	काष्ठा ocfs2_dinode *old_di;
	काष्ठा ocfs2_dir_lookup_result old_inode_करोt_करोt_res = अणु शून्य, पूर्ण;
	काष्ठा ocfs2_dir_lookup_result target_lookup_res = अणु शून्य, पूर्ण;
	काष्ठा ocfs2_dir_lookup_result old_entry_lookup = अणु शून्य, पूर्ण;
	काष्ठा ocfs2_dir_lookup_result orphan_insert = अणु शून्य, पूर्ण;
	काष्ठा ocfs2_dir_lookup_result target_insert = अणु शून्य, पूर्ण;
	bool should_add_orphan = false;

	अगर (flags)
		वापस -EINVAL;

	/* At some poपूर्णांक it might be nice to अवरोध this function up a
	 * bit. */

	trace_ocfs2_नाम(old_dir, old_dentry, new_dir, new_dentry,
			   old_dentry->d_name.len, old_dentry->d_name.name,
			   new_dentry->d_name.len, new_dentry->d_name.name);

	status = dquot_initialize(old_dir);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	status = dquot_initialize(new_dir);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	osb = OCFS2_SB(old_dir->i_sb);

	अगर (new_inode) अणु
		अगर (!igrab(new_inode))
			BUG();
	पूर्ण

	/* Assume a directory hierarchy thusly:
	 * a/b/c
	 * a/d
	 * a,b,c, and d are all directories.
	 *
	 * from cwd of 'a' on both nodes:
	 * node1: mv b/c d
	 * node2: mv d   b/c
	 *
	 * And that's why, just like the VFS, we need a file प्रणाली
	 * नाम lock. */
	अगर (old_dir != new_dir && S_ISसूची(old_inode->i_mode)) अणु
		status = ocfs2_नाम_lock(osb);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
		नाम_lock = 1;

		/* here we cannot guarantee the inodes haven't just been
		 * changed, so check अगर they are nested again */
		status = ocfs2_check_अगर_ancestor(osb, new_dir->i_ino,
				old_inode->i_ino);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण अन्यथा अगर (status == 1) अणु
			status = -EPERM;
			trace_ocfs2_नाम_not_permitted(
					(अचिन्हित दीर्घ दीर्घ)old_inode->i_ino,
					(अचिन्हित दीर्घ दीर्घ)new_dir->i_ino);
			जाओ bail;
		पूर्ण
	पूर्ण

	/* अगर old and new are the same, this'll just करो one lock. */
	status = ocfs2_द्विगुन_lock(osb, &old_dir_bh, old_dir,
				   &new_dir_bh, new_dir, 1);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	parents_locked = 1;

	अगर (!new_dir->i_nlink) अणु
		status = -EACCES;
		जाओ bail;
	पूर्ण

	/* make sure both dirs have bhs
	 * get an extra ref on old_dir_bh अगर old==new */
	अगर (!new_dir_bh) अणु
		अगर (old_dir_bh) अणु
			new_dir_bh = old_dir_bh;
			get_bh(new_dir_bh);
		पूर्ण अन्यथा अणु
			mlog(ML_ERROR, "no old_dir_bh!\n");
			status = -EIO;
			जाओ bail;
		पूर्ण
	पूर्ण

	/*
	 * Aside from allowing a meta data update, the locking here
	 * also ensures that the करोwnconvert thपढ़ो on other nodes
	 * won't have to concurrently करोwnconvert the inode and the
	 * dentry locks.
	 */
	status = ocfs2_inode_lock_nested(old_inode, &old_inode_bh, 1,
					 OI_LS_PARENT);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	old_child_locked = 1;

	status = ocfs2_remote_dentry_delete(old_dentry);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	अगर (S_ISसूची(old_inode->i_mode)) अणु
		u64 old_inode_parent;

		update_करोt_करोt = 1;
		status = ocfs2_find_files_on_disk("..", 2, &old_inode_parent,
						  old_inode,
						  &old_inode_करोt_करोt_res);
		अगर (status) अणु
			status = -EIO;
			जाओ bail;
		पूर्ण

		अगर (old_inode_parent != OCFS2_I(old_dir)->ip_blkno) अणु
			status = -EIO;
			जाओ bail;
		पूर्ण

		अगर (!new_inode && new_dir != old_dir &&
		    new_dir->i_nlink >= ocfs2_link_max(osb)) अणु
			status = -EMLINK;
			जाओ bail;
		पूर्ण
	पूर्ण

	status = ocfs2_lookup_ino_from_name(old_dir, old_dentry->d_name.name,
					    old_dentry->d_name.len,
					    &old_de_ino);
	अगर (status) अणु
		status = -ENOENT;
		जाओ bail;
	पूर्ण

	/*
	 *  Check क्रम inode number is _not_ due to possible IO errors.
	 *  We might सूची_हटाओ the source, keep it as pwd of some process
	 *  and merrily समाप्त the link to whatever was created under the
	 *  same name. Goodbye sticky bit ;-<
	 */
	अगर (old_de_ino != OCFS2_I(old_inode)->ip_blkno) अणु
		status = -ENOENT;
		जाओ bail;
	पूर्ण

	/* check अगर the target alपढ़ोy exists (in which हाल we need
	 * to delete it */
	status = ocfs2_find_files_on_disk(new_dentry->d_name.name,
					  new_dentry->d_name.len,
					  &newfe_blkno, new_dir,
					  &target_lookup_res);
	/* The only error we allow here is -ENOENT because the new
	 * file not existing is perfectly valid. */
	अगर ((status < 0) && (status != -ENOENT)) अणु
		/* If we cannot find the file specअगरied we should just */
		/* वापस the error... */
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	अगर (status == 0)
		target_exists = 1;

	अगर (!target_exists && new_inode) अणु
		/*
		 * Target was unlinked by another node जबतक we were
		 * रुकोing to get to ocfs2_नाम(). There isn't
		 * anything we can करो here to help the situation, so
		 * bubble up the appropriate error.
		 */
		status = -ENOENT;
		जाओ bail;
	पूर्ण

	/* In हाल we need to overग_लिखो an existing file, we blow it
	 * away first */
	अगर (target_exists) अणु
		/* VFS didn't think there existed an inode here, but
		 * someone अन्यथा in the cluster must have raced our
		 * नाम to create one. Today we error cleanly, in
		 * the future we should consider calling iget to build
		 * a new काष्ठा inode क्रम this entry. */
		अगर (!new_inode) अणु
			status = -EACCES;

			trace_ocfs2_नाम_target_exists(new_dentry->d_name.len,
						new_dentry->d_name.name);
			जाओ bail;
		पूर्ण

		अगर (OCFS2_I(new_inode)->ip_blkno != newfe_blkno) अणु
			status = -EACCES;

			trace_ocfs2_नाम_disagree(
			     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(new_inode)->ip_blkno,
			     (अचिन्हित दीर्घ दीर्घ)newfe_blkno,
			     OCFS2_I(new_inode)->ip_flags);
			जाओ bail;
		पूर्ण

		status = ocfs2_inode_lock(new_inode, &newfe_bh, 1);
		अगर (status < 0) अणु
			अगर (status != -ENOENT)
				mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
		new_child_locked = 1;

		status = ocfs2_remote_dentry_delete(new_dentry);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		newfe = (काष्ठा ocfs2_dinode *) newfe_bh->b_data;

		trace_ocfs2_नाम_over_existing(
		     (अचिन्हित दीर्घ दीर्घ)newfe_blkno, newfe_bh, newfe_bh ?
		     (अचिन्हित दीर्घ दीर्घ)newfe_bh->b_blocknr : 0ULL);

		अगर (S_ISसूची(new_inode->i_mode) || (new_inode->i_nlink == 1)) अणु
			status = ocfs2_prepare_orphan_dir(osb, &orphan_dir,
						OCFS2_I(new_inode)->ip_blkno,
						orphan_name, &orphan_insert,
						false);
			अगर (status < 0) अणु
				mlog_त्रुटि_सं(status);
				जाओ bail;
			पूर्ण
			should_add_orphan = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		BUG_ON(d_inode(new_dentry->d_parent) != new_dir);

		status = ocfs2_check_dir_क्रम_entry(new_dir,
						   new_dentry->d_name.name,
						   new_dentry->d_name.len);
		अगर (status)
			जाओ bail;

		status = ocfs2_prepare_dir_क्रम_insert(osb, new_dir, new_dir_bh,
						      new_dentry->d_name.name,
						      new_dentry->d_name.len,
						      &target_insert);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	handle = ocfs2_start_trans(osb, ocfs2_नाम_credits(osb->sb));
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	अगर (target_exists) अणु
		अगर (S_ISसूची(new_inode->i_mode)) अणु
			अगर (new_inode->i_nlink != 2 ||
			    !ocfs2_empty_dir(new_inode)) अणु
				status = -ENOTEMPTY;
				जाओ bail;
			पूर्ण
		पूर्ण
		status = ocfs2_journal_access_di(handle, INODE_CACHE(new_inode),
						 newfe_bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		/* change the dirent to poपूर्णांक to the correct inode */
		status = ocfs2_update_entry(new_dir, handle, &target_lookup_res,
					    old_inode);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
		inode_inc_iversion(new_dir);

		अगर (S_ISसूची(new_inode->i_mode))
			ocfs2_set_links_count(newfe, 0);
		अन्यथा
			ocfs2_add_links_count(newfe, -1);
		ocfs2_journal_dirty(handle, newfe_bh);
		अगर (should_add_orphan) अणु
			status = ocfs2_orphan_add(osb, handle, new_inode,
					newfe_bh, orphan_name,
					&orphan_insert, orphan_dir, false);
			अगर (status < 0) अणु
				mlog_त्रुटि_सं(status);
				जाओ bail;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* अगर the name was not found in new_dir, add it now */
		status = ocfs2_add_entry(handle, new_dentry, old_inode,
					 OCFS2_I(old_inode)->ip_blkno,
					 new_dir_bh, &target_insert);
	पूर्ण

	old_inode->i_स_समय = current_समय(old_inode);
	mark_inode_dirty(old_inode);

	status = ocfs2_journal_access_di(handle, INODE_CACHE(old_inode),
					 old_inode_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status >= 0) अणु
		old_di = (काष्ठा ocfs2_dinode *) old_inode_bh->b_data;

		old_di->i_स_समय = cpu_to_le64(old_inode->i_स_समय.tv_sec);
		old_di->i_स_समय_nsec = cpu_to_le32(old_inode->i_स_समय.tv_nsec);
		ocfs2_journal_dirty(handle, old_inode_bh);
	पूर्ण अन्यथा
		mlog_त्रुटि_सं(status);

	/*
	 * Now that the name has been added to new_dir, हटाओ the old name.
	 *
	 * We करोn't keep any directory entry context around until now
	 * because the insert might have changed the type of directory
	 * we're dealing with.
	 */
	status = ocfs2_find_entry(old_dentry->d_name.name,
				  old_dentry->d_name.len, old_dir,
				  &old_entry_lookup);
	अगर (status) अणु
		अगर (!is_journal_पातed(osb->journal->j_journal)) अणु
			ocfs2_error(osb->sb, "new entry %.*s is added, but old entry %.*s "
					"is not deleted.",
					new_dentry->d_name.len, new_dentry->d_name.name,
					old_dentry->d_name.len, old_dentry->d_name.name);
		पूर्ण
		जाओ bail;
	पूर्ण

	status = ocfs2_delete_entry(handle, old_dir, &old_entry_lookup);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		अगर (!is_journal_पातed(osb->journal->j_journal)) अणु
			ocfs2_error(osb->sb, "new entry %.*s is added, but old entry %.*s "
					"is not deleted.",
					new_dentry->d_name.len, new_dentry->d_name.name,
					old_dentry->d_name.len, old_dentry->d_name.name);
		पूर्ण
		जाओ bail;
	पूर्ण

	अगर (new_inode) अणु
		drop_nlink(new_inode);
		new_inode->i_स_समय = current_समय(new_inode);
	पूर्ण
	old_dir->i_स_समय = old_dir->i_mसमय = current_समय(old_dir);

	अगर (update_करोt_करोt) अणु
		status = ocfs2_update_entry(old_inode, handle,
					    &old_inode_करोt_करोt_res, new_dir);
		drop_nlink(old_dir);
		अगर (new_inode) अणु
			drop_nlink(new_inode);
		पूर्ण अन्यथा अणु
			inc_nlink(new_dir);
			mark_inode_dirty(new_dir);
		पूर्ण
	पूर्ण
	mark_inode_dirty(old_dir);
	ocfs2_mark_inode_dirty(handle, old_dir, old_dir_bh);
	अगर (new_inode) अणु
		mark_inode_dirty(new_inode);
		ocfs2_mark_inode_dirty(handle, new_inode, newfe_bh);
	पूर्ण

	अगर (old_dir != new_dir) अणु
		/* Keep the same बार on both directories.*/
		new_dir->i_स_समय = new_dir->i_mसमय = old_dir->i_स_समय;

		/*
		 * This will also pick up the i_nlink change from the
		 * block above.
		 */
		ocfs2_mark_inode_dirty(handle, new_dir, new_dir_bh);
	पूर्ण

	अगर (old_dir_nlink != old_dir->i_nlink) अणु
		अगर (!old_dir_bh) अणु
			mlog(ML_ERROR, "need to change nlink for old dir "
			     "%llu from %d to %d but bh is NULL!\n",
			     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(old_dir)->ip_blkno,
			     (पूर्णांक)old_dir_nlink, old_dir->i_nlink);
		पूर्ण अन्यथा अणु
			काष्ठा ocfs2_dinode *fe;
			status = ocfs2_journal_access_di(handle,
							 INODE_CACHE(old_dir),
							 old_dir_bh,
							 OCFS2_JOURNAL_ACCESS_WRITE);
			fe = (काष्ठा ocfs2_dinode *) old_dir_bh->b_data;
			ocfs2_set_links_count(fe, old_dir->i_nlink);
			ocfs2_journal_dirty(handle, old_dir_bh);
		पूर्ण
	पूर्ण
	ocfs2_dentry_move(old_dentry, new_dentry, old_dir, new_dir);
	status = 0;
bail:
	अगर (handle)
		ocfs2_commit_trans(osb, handle);

	अगर (orphan_dir) अणु
		/* This was locked क्रम us in ocfs2_prepare_orphan_dir() */
		ocfs2_inode_unlock(orphan_dir, 1);
		inode_unlock(orphan_dir);
		iput(orphan_dir);
	पूर्ण

	अगर (new_child_locked)
		ocfs2_inode_unlock(new_inode, 1);

	अगर (old_child_locked)
		ocfs2_inode_unlock(old_inode, 1);

	अगर (parents_locked)
		ocfs2_द्विगुन_unlock(old_dir, new_dir);

	अगर (नाम_lock)
		ocfs2_नाम_unlock(osb);

	अगर (new_inode)
		sync_mapping_buffers(old_inode->i_mapping);

	iput(new_inode);

	ocfs2_मुक्त_dir_lookup_result(&target_lookup_res);
	ocfs2_मुक्त_dir_lookup_result(&old_entry_lookup);
	ocfs2_मुक्त_dir_lookup_result(&old_inode_करोt_करोt_res);
	ocfs2_मुक्त_dir_lookup_result(&orphan_insert);
	ocfs2_मुक्त_dir_lookup_result(&target_insert);

	brअन्यथा(newfe_bh);
	brअन्यथा(old_inode_bh);
	brअन्यथा(old_dir_bh);
	brअन्यथा(new_dir_bh);

	अगर (status)
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

/*
 * we expect i_size = म_माप(symname). Copy symname पूर्णांकo the file
 * data, including the null terminator.
 */
अटल पूर्णांक ocfs2_create_symlink_data(काष्ठा ocfs2_super *osb,
				     handle_t *handle,
				     काष्ठा inode *inode,
				     स्थिर अक्षर *symname)
अणु
	काष्ठा buffer_head **bhs = शून्य;
	स्थिर अक्षर *c;
	काष्ठा super_block *sb = osb->sb;
	u64 p_blkno, p_blocks;
	पूर्णांक भव, blocks, status, i, bytes_left;

	bytes_left = i_size_पढ़ो(inode) + 1;
	/* we can't trust i_blocks because we're actually going to
	 * ग_लिखो i_size + 1 bytes. */
	blocks = (bytes_left + sb->s_blocksize - 1) >> sb->s_blocksize_bits;

	trace_ocfs2_create_symlink_data((अचिन्हित दीर्घ दीर्घ)inode->i_blocks,
					i_size_पढ़ो(inode), blocks);

	/* Sanity check -- make sure we're going to fit. */
	अगर (bytes_left >
	    ocfs2_clusters_to_bytes(sb, OCFS2_I(inode)->ip_clusters)) अणु
		status = -EIO;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	bhs = kसुस्मृति(blocks, माप(काष्ठा buffer_head *), GFP_KERNEL);
	अगर (!bhs) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_extent_map_get_blocks(inode, 0, &p_blkno, &p_blocks,
					     शून्य);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	/* links can never be larger than one cluster so we know this
	 * is all going to be contiguous, but करो a sanity check
	 * anyway. */
	अगर ((p_blocks << sb->s_blocksize_bits) < bytes_left) अणु
		status = -EIO;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	भव = 0;
	जबतक(bytes_left > 0) अणु
		c = &symname[भव * sb->s_blocksize];

		bhs[भव] = sb_getblk(sb, p_blkno);
		अगर (!bhs[भव]) अणु
			status = -ENOMEM;
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
		ocfs2_set_new_buffer_uptodate(INODE_CACHE(inode),
					      bhs[भव]);

		status = ocfs2_journal_access(handle, INODE_CACHE(inode),
					      bhs[भव],
					      OCFS2_JOURNAL_ACCESS_CREATE);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		स_रखो(bhs[भव]->b_data, 0, sb->s_blocksize);

		स_नकल(bhs[भव]->b_data, c,
		       (bytes_left > sb->s_blocksize) ? sb->s_blocksize :
		       bytes_left);

		ocfs2_journal_dirty(handle, bhs[भव]);

		भव++;
		p_blkno++;
		bytes_left -= sb->s_blocksize;
	पूर्ण

	status = 0;
bail:

	अगर (bhs) अणु
		क्रम(i = 0; i < blocks; i++)
			brअन्यथा(bhs[i]);
		kमुक्त(bhs);
	पूर्ण

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_symlink(काष्ठा user_namespace *mnt_userns,
			 काष्ठा inode *dir,
			 काष्ठा dentry *dentry,
			 स्थिर अक्षर *symname)
अणु
	पूर्णांक status, l, credits;
	u64 newsize;
	काष्ठा ocfs2_super *osb = शून्य;
	काष्ठा inode *inode = शून्य;
	काष्ठा super_block *sb;
	काष्ठा buffer_head *new_fe_bh = शून्य;
	काष्ठा buffer_head *parent_fe_bh = शून्य;
	काष्ठा ocfs2_dinode *fe = शून्य;
	काष्ठा ocfs2_dinode *dirfe;
	handle_t *handle = शून्य;
	काष्ठा ocfs2_alloc_context *inode_ac = शून्य;
	काष्ठा ocfs2_alloc_context *data_ac = शून्य;
	काष्ठा ocfs2_alloc_context *xattr_ac = शून्य;
	पूर्णांक want_clusters = 0;
	पूर्णांक xattr_credits = 0;
	काष्ठा ocfs2_security_xattr_info si = अणु
		.enable = 1,
	पूर्ण;
	पूर्णांक did_quota = 0, did_quota_inode = 0;
	काष्ठा ocfs2_dir_lookup_result lookup = अणु शून्य, पूर्ण;
	sigset_t oldset;
	पूर्णांक did_block_संकेतs = 0;
	काष्ठा ocfs2_dentry_lock *dl = शून्य;

	trace_ocfs2_symlink_begin(dir, dentry, symname,
				  dentry->d_name.len, dentry->d_name.name);

	status = dquot_initialize(dir);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	sb = dir->i_sb;
	osb = OCFS2_SB(sb);

	l = म_माप(symname) + 1;

	credits = ocfs2_calc_symlink_credits(sb);

	/* lock the parent directory */
	status = ocfs2_inode_lock(dir, &parent_fe_bh, 1);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	dirfe = (काष्ठा ocfs2_dinode *) parent_fe_bh->b_data;
	अगर (!ocfs2_पढ़ो_links_count(dirfe)) अणु
		/* can't make a file in a deleted directory. */
		status = -ENOENT;
		जाओ bail;
	पूर्ण

	status = ocfs2_check_dir_क्रम_entry(dir, dentry->d_name.name,
					   dentry->d_name.len);
	अगर (status)
		जाओ bail;

	status = ocfs2_prepare_dir_क्रम_insert(osb, dir, parent_fe_bh,
					      dentry->d_name.name,
					      dentry->d_name.len, &lookup);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_reserve_new_inode(osb, &inode_ac);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	inode = ocfs2_get_init_inode(dir, S_IFLNK | S_IRWXUGO);
	अगर (IS_ERR(inode)) अणु
		status = PTR_ERR(inode);
		inode = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	/* get security xattr */
	status = ocfs2_init_security_get(inode, dir, &dentry->d_name, &si);
	अगर (status) अणु
		अगर (status == -EOPNOTSUPP)
			si.enable = 0;
		अन्यथा अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	/* calculate meta data/clusters क्रम setting security xattr */
	अगर (si.enable) अणु
		status = ocfs2_calc_security_init(dir, &si, &want_clusters,
						  &xattr_credits, &xattr_ac);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	/* करोn't reserve biपंचांगap space क्रम fast symlinks. */
	अगर (l > ocfs2_fast_symlink_अक्षरs(sb))
		want_clusters += 1;

	status = ocfs2_reserve_clusters(osb, want_clusters, &data_ac);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	handle = ocfs2_start_trans(osb, credits + xattr_credits);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	/* Starting to change things, restart is no दीर्घer possible. */
	ocfs2_block_संकेतs(&oldset);
	did_block_संकेतs = 1;

	status = dquot_alloc_inode(inode);
	अगर (status)
		जाओ bail;
	did_quota_inode = 1;

	trace_ocfs2_symlink_create(dir, dentry, dentry->d_name.len,
				   dentry->d_name.name,
				   (अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno,
				   inode->i_mode);

	status = ocfs2_mknod_locked(osb, dir, inode,
				    0, &new_fe_bh, parent_fe_bh, handle,
				    inode_ac);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	fe = (काष्ठा ocfs2_dinode *) new_fe_bh->b_data;
	inode->i_rdev = 0;
	newsize = l - 1;
	inode->i_op = &ocfs2_symlink_inode_operations;
	inode_nohighmem(inode);
	अगर (l > ocfs2_fast_symlink_अक्षरs(sb)) अणु
		u32 offset = 0;

		status = dquot_alloc_space_nodirty(inode,
		    ocfs2_clusters_to_bytes(osb->sb, 1));
		अगर (status)
			जाओ bail;
		did_quota = 1;
		inode->i_mapping->a_ops = &ocfs2_aops;
		status = ocfs2_add_inode_data(osb, inode, &offset, 1, 0,
					      new_fe_bh,
					      handle, data_ac, शून्य,
					      शून्य);
		अगर (status < 0) अणु
			अगर (status != -ENOSPC && status != -EINTR) अणु
				mlog(ML_ERROR,
				     "Failed to extend file to %llu\n",
				     (अचिन्हित दीर्घ दीर्घ)newsize);
				mlog_त्रुटि_सं(status);
				status = -ENOSPC;
			पूर्ण
			जाओ bail;
		पूर्ण
		i_size_ग_लिखो(inode, newsize);
		inode->i_blocks = ocfs2_inode_sector_count(inode);
	पूर्ण अन्यथा अणु
		inode->i_mapping->a_ops = &ocfs2_fast_symlink_aops;
		स_नकल((अक्षर *) fe->id2.i_symlink, symname, l);
		i_size_ग_लिखो(inode, newsize);
		inode->i_blocks = 0;
	पूर्ण

	status = ocfs2_mark_inode_dirty(handle, inode, new_fe_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	अगर (!ocfs2_inode_is_fast_symlink(inode)) अणु
		status = ocfs2_create_symlink_data(osb, handle, inode,
						   symname);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	अगर (si.enable) अणु
		status = ocfs2_init_security_set(handle, inode, new_fe_bh, &si,
						 xattr_ac, data_ac);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	/*
	 * Do this beक्रमe adding the entry to the directory. We add
	 * also set d_op after success so that ->d_iput() will cleanup
	 * the dentry lock even अगर ocfs2_add_entry() fails below.
	 */
	status = ocfs2_dentry_attach_lock(dentry, inode, OCFS2_I(dir)->ip_blkno);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	dl = dentry->d_fsdata;

	status = ocfs2_add_entry(handle, dentry, inode,
				 le64_to_cpu(fe->i_blkno), parent_fe_bh,
				 &lookup);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	insert_inode_hash(inode);
	d_instantiate(dentry, inode);
bail:
	अगर (status < 0 && did_quota)
		dquot_मुक्त_space_nodirty(inode,
					ocfs2_clusters_to_bytes(osb->sb, 1));
	अगर (status < 0 && did_quota_inode)
		dquot_मुक्त_inode(inode);
	अगर (handle)
		ocfs2_commit_trans(osb, handle);

	ocfs2_inode_unlock(dir, 1);
	अगर (did_block_संकेतs)
		ocfs2_unblock_संकेतs(&oldset);

	brअन्यथा(new_fe_bh);
	brअन्यथा(parent_fe_bh);
	kमुक्त(si.value);
	ocfs2_मुक्त_dir_lookup_result(&lookup);
	अगर (inode_ac)
		ocfs2_मुक्त_alloc_context(inode_ac);
	अगर (data_ac)
		ocfs2_मुक्त_alloc_context(data_ac);
	अगर (xattr_ac)
		ocfs2_मुक्त_alloc_context(xattr_ac);
	अगर ((status < 0) && inode) अणु
		अगर (dl)
			ocfs2_cleanup_add_entry_failure(osb, dentry, inode);

		OCFS2_I(inode)->ip_flags |= OCFS2_INODE_SKIP_ORPHAN_सूची;
		clear_nlink(inode);
		iput(inode);
	पूर्ण

	अगर (status)
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_blkno_stringअगरy(u64 blkno, अक्षर *name)
अणु
	पूर्णांक status, namelen;

	namelen = snम_लिखो(name, OCFS2_ORPHAN_NAMELEN + 1, "%016llx",
			   (दीर्घ दीर्घ)blkno);
	अगर (namelen <= 0) अणु
		अगर (namelen)
			status = namelen;
		अन्यथा
			status = -EINVAL;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	अगर (namelen != OCFS2_ORPHAN_NAMELEN) अणु
		status = -EINVAL;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	trace_ocfs2_blkno_stringअगरy(blkno, name, namelen);

	status = 0;
bail:
	अगर (status < 0)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_lookup_lock_orphan_dir(काष्ठा ocfs2_super *osb,
					काष्ठा inode **ret_orphan_dir,
					काष्ठा buffer_head **ret_orphan_dir_bh)
अणु
	काष्ठा inode *orphan_dir_inode;
	काष्ठा buffer_head *orphan_dir_bh = शून्य;
	पूर्णांक ret = 0;

	orphan_dir_inode = ocfs2_get_प्रणाली_file_inode(osb,
						       ORPHAN_सूची_SYSTEM_INODE,
						       osb->slot_num);
	अगर (!orphan_dir_inode) अणु
		ret = -ENOENT;
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	inode_lock(orphan_dir_inode);

	ret = ocfs2_inode_lock(orphan_dir_inode, &orphan_dir_bh, 1);
	अगर (ret < 0) अणु
		inode_unlock(orphan_dir_inode);
		iput(orphan_dir_inode);

		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	*ret_orphan_dir = orphan_dir_inode;
	*ret_orphan_dir_bh = orphan_dir_bh;

	वापस 0;
पूर्ण

अटल पूर्णांक __ocfs2_prepare_orphan_dir(काष्ठा inode *orphan_dir_inode,
				      काष्ठा buffer_head *orphan_dir_bh,
				      u64 blkno,
				      अक्षर *name,
				      काष्ठा ocfs2_dir_lookup_result *lookup,
				      bool dio)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_super *osb = OCFS2_SB(orphan_dir_inode->i_sb);
	पूर्णांक namelen = dio ?
			(OCFS2_DIO_ORPHAN_PREFIX_LEN + OCFS2_ORPHAN_NAMELEN) :
			OCFS2_ORPHAN_NAMELEN;

	अगर (dio) अणु
		ret = snम_लिखो(name, OCFS2_DIO_ORPHAN_PREFIX_LEN + 1, "%s",
				OCFS2_DIO_ORPHAN_PREFIX);
		अगर (ret != OCFS2_DIO_ORPHAN_PREFIX_LEN) अणु
			ret = -EINVAL;
			mlog_त्रुटि_सं(ret);
			वापस ret;
		पूर्ण

		ret = ocfs2_blkno_stringअगरy(blkno,
				name + OCFS2_DIO_ORPHAN_PREFIX_LEN);
	पूर्ण अन्यथा
		ret = ocfs2_blkno_stringअगरy(blkno, name);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	ret = ocfs2_prepare_dir_क्रम_insert(osb, orphan_dir_inode,
					   orphan_dir_bh, name,
					   namelen, lookup);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ocfs2_prepare_orphan_dir() - Prepare an orphan directory क्रम
 * insertion of an orphan.
 * @osb: ocfs2 file प्रणाली
 * @ret_orphan_dir: Orphan dir inode - वापसed locked!
 * @blkno: Actual block number of the inode to be inserted पूर्णांकo orphan dir.
 * @lookup: dir lookup result, to be passed back पूर्णांकo functions like
 *          ocfs2_orphan_add
 *
 * Returns zero on success and the ret_orphan_dir, name and lookup
 * fields will be populated.
 *
 * Returns non-zero on failure. 
 */
अटल पूर्णांक ocfs2_prepare_orphan_dir(काष्ठा ocfs2_super *osb,
				    काष्ठा inode **ret_orphan_dir,
				    u64 blkno,
				    अक्षर *name,
				    काष्ठा ocfs2_dir_lookup_result *lookup,
				    bool dio)
अणु
	काष्ठा inode *orphan_dir_inode = शून्य;
	काष्ठा buffer_head *orphan_dir_bh = शून्य;
	पूर्णांक ret = 0;

	ret = ocfs2_lookup_lock_orphan_dir(osb, &orphan_dir_inode,
					   &orphan_dir_bh);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	ret = __ocfs2_prepare_orphan_dir(orphan_dir_inode, orphan_dir_bh,
					 blkno, name, lookup, dio);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	*ret_orphan_dir = orphan_dir_inode;

out:
	brअन्यथा(orphan_dir_bh);

	अगर (ret) अणु
		ocfs2_inode_unlock(orphan_dir_inode, 1);
		inode_unlock(orphan_dir_inode);
		iput(orphan_dir_inode);
	पूर्ण

	अगर (ret)
		mlog_त्रुटि_सं(ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_orphan_add(काष्ठा ocfs2_super *osb,
			    handle_t *handle,
			    काष्ठा inode *inode,
			    काष्ठा buffer_head *fe_bh,
			    अक्षर *name,
			    काष्ठा ocfs2_dir_lookup_result *lookup,
			    काष्ठा inode *orphan_dir_inode,
			    bool dio)
अणु
	काष्ठा buffer_head *orphan_dir_bh = शून्य;
	पूर्णांक status = 0;
	काष्ठा ocfs2_dinode *orphan_fe;
	काष्ठा ocfs2_dinode *fe = (काष्ठा ocfs2_dinode *) fe_bh->b_data;
	पूर्णांक namelen = dio ?
			(OCFS2_DIO_ORPHAN_PREFIX_LEN + OCFS2_ORPHAN_NAMELEN) :
			OCFS2_ORPHAN_NAMELEN;

	trace_ocfs2_orphan_add_begin(
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);

	status = ocfs2_पढ़ो_inode_block(orphan_dir_inode, &orphan_dir_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	status = ocfs2_journal_access_di(handle,
					 INODE_CACHE(orphan_dir_inode),
					 orphan_dir_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	/*
	 * We're going to journal the change of i_flags and i_orphaned_slot.
	 * It's safe anyway, though some callers may duplicate the journaling.
	 * Journaling within the func just make the logic look more
	 * straightक्रमward.
	 */
	status = ocfs2_journal_access_di(handle,
					 INODE_CACHE(inode),
					 fe_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	/* we're a cluster, and nlink can change on disk from
	 * underneath us... */
	orphan_fe = (काष्ठा ocfs2_dinode *) orphan_dir_bh->b_data;
	अगर (S_ISसूची(inode->i_mode))
		ocfs2_add_links_count(orphan_fe, 1);
	set_nlink(orphan_dir_inode, ocfs2_पढ़ो_links_count(orphan_fe));
	ocfs2_journal_dirty(handle, orphan_dir_bh);

	status = __ocfs2_add_entry(handle, orphan_dir_inode, name,
				   namelen, inode,
				   OCFS2_I(inode)->ip_blkno,
				   orphan_dir_bh, lookup);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ rollback;
	पूर्ण

	अगर (dio) अणु
		/* Update flag OCFS2_DIO_ORPHANED_FL and record the orphan
		 * slot.
		 */
		fe->i_flags |= cpu_to_le32(OCFS2_DIO_ORPHANED_FL);
		fe->i_dio_orphaned_slot = cpu_to_le16(osb->slot_num);
	पूर्ण अन्यथा अणु
		fe->i_flags |= cpu_to_le32(OCFS2_ORPHANED_FL);
		OCFS2_I(inode)->ip_flags &= ~OCFS2_INODE_SKIP_ORPHAN_सूची;

		/* Record which orphan dir our inode now resides
		 * in. delete_inode will use this to determine which orphan
		 * dir to lock. */
		fe->i_orphaned_slot = cpu_to_le16(osb->slot_num);
	पूर्ण

	ocfs2_journal_dirty(handle, fe_bh);

	trace_ocfs2_orphan_add_end((अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno,
				   osb->slot_num);

rollback:
	अगर (status < 0) अणु
		अगर (S_ISसूची(inode->i_mode))
			ocfs2_add_links_count(orphan_fe, -1);
		set_nlink(orphan_dir_inode, ocfs2_पढ़ो_links_count(orphan_fe));
	पूर्ण

leave:
	brअन्यथा(orphan_dir_bh);

	वापस status;
पूर्ण

/* unlike orphan_add, we expect the orphan dir to alपढ़ोy be locked here. */
पूर्णांक ocfs2_orphan_del(काष्ठा ocfs2_super *osb,
		     handle_t *handle,
		     काष्ठा inode *orphan_dir_inode,
		     काष्ठा inode *inode,
		     काष्ठा buffer_head *orphan_dir_bh,
		     bool dio)
अणु
	अक्षर name[OCFS2_DIO_ORPHAN_PREFIX_LEN + OCFS2_ORPHAN_NAMELEN + 1];
	काष्ठा ocfs2_dinode *orphan_fe;
	पूर्णांक status = 0;
	काष्ठा ocfs2_dir_lookup_result lookup = अणु शून्य, पूर्ण;

	अगर (dio) अणु
		status = snम_लिखो(name, OCFS2_DIO_ORPHAN_PREFIX_LEN + 1, "%s",
				OCFS2_DIO_ORPHAN_PREFIX);
		अगर (status != OCFS2_DIO_ORPHAN_PREFIX_LEN) अणु
			status = -EINVAL;
			mlog_त्रुटि_सं(status);
			वापस status;
		पूर्ण

		status = ocfs2_blkno_stringअगरy(OCFS2_I(inode)->ip_blkno,
				name + OCFS2_DIO_ORPHAN_PREFIX_LEN);
	पूर्ण अन्यथा
		status = ocfs2_blkno_stringअगरy(OCFS2_I(inode)->ip_blkno, name);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	trace_ocfs2_orphan_del(
	     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(orphan_dir_inode)->ip_blkno,
	     name, म_माप(name));

	status = ocfs2_journal_access_di(handle,
					 INODE_CACHE(orphan_dir_inode),
					 orphan_dir_bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	/* find it's spot in the orphan directory */
	status = ocfs2_find_entry(name, म_माप(name), orphan_dir_inode,
				  &lookup);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	/* हटाओ it from the orphan directory */
	status = ocfs2_delete_entry(handle, orphan_dir_inode, &lookup);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	/* करो the i_nlink dance! :) */
	orphan_fe = (काष्ठा ocfs2_dinode *) orphan_dir_bh->b_data;
	अगर (S_ISसूची(inode->i_mode))
		ocfs2_add_links_count(orphan_fe, -1);
	set_nlink(orphan_dir_inode, ocfs2_पढ़ो_links_count(orphan_fe));
	ocfs2_journal_dirty(handle, orphan_dir_bh);

leave:
	ocfs2_मुक्त_dir_lookup_result(&lookup);

	अगर (status)
		mlog_त्रुटि_सं(status);
	वापस status;
पूर्ण

/**
 * ocfs2_prep_new_orphaned_file() - Prepare the orphan dir to receive a newly
 * allocated file. This is dअगरferent from the typical 'add to orphan dir'
 * operation in that the inode करोes not yet exist. This is a problem because
 * the orphan dir stringअगरies the inode block number to come up with it's
 * dirent. Obviously अगर the inode करोes not yet exist we have a chicken and egg
 * problem. This function works around it by calling deeper पूर्णांकo the orphan
 * and suballoc code than other callers. Use this only by necessity.
 * @dir: The directory which this inode will ultimately wind up under - not the
 * orphan dir!
 * @dir_bh: buffer_head the @dir inode block
 * @orphan_name: string of length (CFS2_ORPHAN_NAMELEN + 1). Will be filled
 * with the string to be used क्रम orphan dirent. Pass back to the orphan dir
 * code.
 * @ret_orphan_dir: orphan dir inode वापसed to be passed back पूर्णांकo orphan
 * dir code.
 * @ret_di_blkno: block number where the new inode will be allocated.
 * @orphan_insert: Dir insert context to be passed back पूर्णांकo orphan dir code.
 * @ret_inode_ac: Inode alloc context to be passed back to the allocator.
 *
 * Returns zero on success and the ret_orphan_dir, name and lookup
 * fields will be populated.
 *
 * Returns non-zero on failure. 
 */
अटल पूर्णांक ocfs2_prep_new_orphaned_file(काष्ठा inode *dir,
					काष्ठा buffer_head *dir_bh,
					अक्षर *orphan_name,
					काष्ठा inode **ret_orphan_dir,
					u64 *ret_di_blkno,
					काष्ठा ocfs2_dir_lookup_result *orphan_insert,
					काष्ठा ocfs2_alloc_context **ret_inode_ac)
अणु
	पूर्णांक ret;
	u64 di_blkno;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	काष्ठा inode *orphan_dir = शून्य;
	काष्ठा buffer_head *orphan_dir_bh = शून्य;
	काष्ठा ocfs2_alloc_context *inode_ac = शून्य;

	ret = ocfs2_lookup_lock_orphan_dir(osb, &orphan_dir, &orphan_dir_bh);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	/* reserve an inode spot */
	ret = ocfs2_reserve_new_inode(osb, &inode_ac);
	अगर (ret < 0) अणु
		अगर (ret != -ENOSPC)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_find_new_inode_loc(dir, dir_bh, inode_ac,
				       &di_blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = __ocfs2_prepare_orphan_dir(orphan_dir, orphan_dir_bh,
					 di_blkno, orphan_name, orphan_insert,
					 false);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

out:
	अगर (ret == 0) अणु
		*ret_orphan_dir = orphan_dir;
		*ret_di_blkno = di_blkno;
		*ret_inode_ac = inode_ac;
		/*
		 * orphan_name and orphan_insert are alपढ़ोy up to
		 * date via prepare_orphan_dir
		 */
	पूर्ण अन्यथा अणु
		/* Unroll reserve_new_inode* */
		अगर (inode_ac)
			ocfs2_मुक्त_alloc_context(inode_ac);

		/* Unroll orphan dir locking */
		inode_unlock(orphan_dir);
		ocfs2_inode_unlock(orphan_dir, 1);
		iput(orphan_dir);
	पूर्ण

	brअन्यथा(orphan_dir_bh);

	वापस ret;
पूर्ण

पूर्णांक ocfs2_create_inode_in_orphan(काष्ठा inode *dir,
				 पूर्णांक mode,
				 काष्ठा inode **new_inode)
अणु
	पूर्णांक status, did_quota_inode = 0;
	काष्ठा inode *inode = शून्य;
	काष्ठा inode *orphan_dir = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	handle_t *handle = शून्य;
	अक्षर orphan_name[OCFS2_ORPHAN_NAMELEN + 1];
	काष्ठा buffer_head *parent_di_bh = शून्य;
	काष्ठा buffer_head *new_di_bh = शून्य;
	काष्ठा ocfs2_alloc_context *inode_ac = शून्य;
	काष्ठा ocfs2_dir_lookup_result orphan_insert = अणु शून्य, पूर्ण;
	u64 di_blkno, suballoc_loc;
	u16 suballoc_bit;

	status = ocfs2_inode_lock(dir, &parent_di_bh, 1);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	status = ocfs2_prep_new_orphaned_file(dir, parent_di_bh,
					      orphan_name, &orphan_dir,
					      &di_blkno, &orphan_insert, &inode_ac);
	अगर (status < 0) अणु
		अगर (status != -ENOSPC)
			mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	inode = ocfs2_get_init_inode(dir, mode);
	अगर (IS_ERR(inode)) अणु
		status = PTR_ERR(inode);
		inode = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	handle = ocfs2_start_trans(osb, ocfs2_mknod_credits(osb->sb, 0, 0));
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	status = dquot_alloc_inode(inode);
	अगर (status)
		जाओ leave;
	did_quota_inode = 1;

	status = ocfs2_claim_new_inode_at_loc(handle, dir, inode_ac,
					      &suballoc_loc,
					      &suballoc_bit, di_blkno);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	clear_nlink(inode);
	/* करो the real work now. */
	status = __ocfs2_mknod_locked(dir, inode,
				      0, &new_di_bh, parent_di_bh, handle,
				      inode_ac, di_blkno, suballoc_loc,
				      suballoc_bit);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	status = ocfs2_orphan_add(osb, handle, inode, new_di_bh, orphan_name,
				  &orphan_insert, orphan_dir, false);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	/* get खोलो lock so that only nodes can't हटाओ it from orphan dir. */
	status = ocfs2_खोलो_lock(inode);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	insert_inode_hash(inode);
leave:
	अगर (status < 0 && did_quota_inode)
		dquot_मुक्त_inode(inode);
	अगर (handle)
		ocfs2_commit_trans(osb, handle);

	अगर (orphan_dir) अणु
		/* This was locked क्रम us in ocfs2_prepare_orphan_dir() */
		ocfs2_inode_unlock(orphan_dir, 1);
		inode_unlock(orphan_dir);
		iput(orphan_dir);
	पूर्ण

	अगर ((status < 0) && inode) अणु
		clear_nlink(inode);
		iput(inode);
	पूर्ण

	अगर (inode_ac)
		ocfs2_मुक्त_alloc_context(inode_ac);

	brअन्यथा(new_di_bh);

	अगर (!status)
		*new_inode = inode;

	ocfs2_मुक्त_dir_lookup_result(&orphan_insert);

	ocfs2_inode_unlock(dir, 1);
	brअन्यथा(parent_di_bh);
	वापस status;
पूर्ण

पूर्णांक ocfs2_add_inode_to_orphan(काष्ठा ocfs2_super *osb,
	काष्ठा inode *inode)
अणु
	अक्षर orphan_name[OCFS2_DIO_ORPHAN_PREFIX_LEN + OCFS2_ORPHAN_NAMELEN + 1];
	काष्ठा inode *orphan_dir_inode = शून्य;
	काष्ठा ocfs2_dir_lookup_result orphan_insert = अणु शून्य, पूर्ण;
	काष्ठा buffer_head *di_bh = शून्य;
	पूर्णांक status = 0;
	handle_t *handle = शून्य;
	काष्ठा ocfs2_dinode *di = शून्य;

	status = ocfs2_inode_lock(inode, &di_bh, 1);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	di = (काष्ठा ocfs2_dinode *) di_bh->b_data;
	/*
	 * Another append dio crashed?
	 * If so, manually recover it first.
	 */
	अगर (unlikely(di->i_flags & cpu_to_le32(OCFS2_DIO_ORPHANED_FL))) अणु
		status = ocfs2_truncate_file(inode, di_bh, i_size_पढ़ो(inode));
		अगर (status < 0) अणु
			अगर (status != -ENOSPC)
				mlog_त्रुटि_सं(status);
			जाओ bail_unlock_inode;
		पूर्ण

		status = ocfs2_del_inode_from_orphan(osb, inode, di_bh, 0, 0);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail_unlock_inode;
		पूर्ण
	पूर्ण

	status = ocfs2_prepare_orphan_dir(osb, &orphan_dir_inode,
			OCFS2_I(inode)->ip_blkno,
			orphan_name,
			&orphan_insert,
			true);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail_unlock_inode;
	पूर्ण

	handle = ocfs2_start_trans(osb,
			OCFS2_INODE_ADD_TO_ORPHAN_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		जाओ bail_unlock_orphan;
	पूर्ण

	status = ocfs2_orphan_add(osb, handle, inode, di_bh, orphan_name,
			&orphan_insert, orphan_dir_inode, true);
	अगर (status)
		mlog_त्रुटि_सं(status);

	ocfs2_commit_trans(osb, handle);

bail_unlock_orphan:
	ocfs2_inode_unlock(orphan_dir_inode, 1);
	inode_unlock(orphan_dir_inode);
	iput(orphan_dir_inode);

	ocfs2_मुक्त_dir_lookup_result(&orphan_insert);

bail_unlock_inode:
	ocfs2_inode_unlock(inode, 1);
	brअन्यथा(di_bh);

bail:
	वापस status;
पूर्ण

पूर्णांक ocfs2_del_inode_from_orphan(काष्ठा ocfs2_super *osb,
		काष्ठा inode *inode, काष्ठा buffer_head *di_bh,
		पूर्णांक update_isize, loff_t end)
अणु
	काष्ठा inode *orphan_dir_inode = शून्य;
	काष्ठा buffer_head *orphan_dir_bh = शून्य;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	handle_t *handle = शून्य;
	पूर्णांक status = 0;

	orphan_dir_inode = ocfs2_get_प्रणाली_file_inode(osb,
			ORPHAN_सूची_SYSTEM_INODE,
			le16_to_cpu(di->i_dio_orphaned_slot));
	अगर (!orphan_dir_inode) अणु
		status = -ENOENT;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	inode_lock(orphan_dir_inode);
	status = ocfs2_inode_lock(orphan_dir_inode, &orphan_dir_bh, 1);
	अगर (status < 0) अणु
		inode_unlock(orphan_dir_inode);
		iput(orphan_dir_inode);
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	handle = ocfs2_start_trans(osb,
			OCFS2_INODE_DEL_FROM_ORPHAN_CREDITS);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		जाओ bail_unlock_orphan;
	पूर्ण

	BUG_ON(!(di->i_flags & cpu_to_le32(OCFS2_DIO_ORPHANED_FL)));

	status = ocfs2_orphan_del(osb, handle, orphan_dir_inode,
				inode, orphan_dir_bh, true);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail_commit;
	पूर्ण

	status = ocfs2_journal_access_di(handle,
			INODE_CACHE(inode),
			di_bh,
			OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail_commit;
	पूर्ण

	di->i_flags &= ~cpu_to_le32(OCFS2_DIO_ORPHANED_FL);
	di->i_dio_orphaned_slot = 0;

	अगर (update_isize) अणु
		status = ocfs2_set_inode_size(handle, inode, di_bh, end);
		अगर (status)
			mlog_त्रुटि_सं(status);
	पूर्ण अन्यथा
		ocfs2_journal_dirty(handle, di_bh);

bail_commit:
	ocfs2_commit_trans(osb, handle);

bail_unlock_orphan:
	ocfs2_inode_unlock(orphan_dir_inode, 1);
	inode_unlock(orphan_dir_inode);
	brअन्यथा(orphan_dir_bh);
	iput(orphan_dir_inode);

bail:
	वापस status;
पूर्ण

पूर्णांक ocfs2_mv_orphaned_inode_to_new(काष्ठा inode *dir,
				   काष्ठा inode *inode,
				   काष्ठा dentry *dentry)
अणु
	पूर्णांक status = 0;
	काष्ठा buffer_head *parent_di_bh = शून्य;
	handle_t *handle = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	काष्ठा ocfs2_dinode *dir_di, *di;
	काष्ठा inode *orphan_dir_inode = शून्य;
	काष्ठा buffer_head *orphan_dir_bh = शून्य;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_dir_lookup_result lookup = अणु शून्य, पूर्ण;

	trace_ocfs2_mv_orphaned_inode_to_new(dir, dentry,
				dentry->d_name.len, dentry->d_name.name,
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno,
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);

	status = ocfs2_inode_lock(dir, &parent_di_bh, 1);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	dir_di = (काष्ठा ocfs2_dinode *) parent_di_bh->b_data;
	अगर (!dir_di->i_links_count) अणु
		/* can't make a file in a deleted directory. */
		status = -ENOENT;
		जाओ leave;
	पूर्ण

	status = ocfs2_check_dir_क्रम_entry(dir, dentry->d_name.name,
					   dentry->d_name.len);
	अगर (status)
		जाओ leave;

	/* get a spot inside the dir. */
	status = ocfs2_prepare_dir_क्रम_insert(osb, dir, parent_di_bh,
					      dentry->d_name.name,
					      dentry->d_name.len, &lookup);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	orphan_dir_inode = ocfs2_get_प्रणाली_file_inode(osb,
						       ORPHAN_सूची_SYSTEM_INODE,
						       osb->slot_num);
	अगर (!orphan_dir_inode) अणु
		status = -ENOENT;
		mlog_त्रुटि_सं(status);
		जाओ leave;
	पूर्ण

	inode_lock(orphan_dir_inode);

	status = ocfs2_inode_lock(orphan_dir_inode, &orphan_dir_bh, 1);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		inode_unlock(orphan_dir_inode);
		iput(orphan_dir_inode);
		जाओ leave;
	पूर्ण

	status = ocfs2_पढ़ो_inode_block(inode, &di_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ orphan_unlock;
	पूर्ण

	handle = ocfs2_start_trans(osb, ocfs2_नाम_credits(osb->sb));
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ orphan_unlock;
	पूर्ण

	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode),
					 di_bh, OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_commit;
	पूर्ण

	status = ocfs2_orphan_del(osb, handle, orphan_dir_inode, inode,
				  orphan_dir_bh, false);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_commit;
	पूर्ण

	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	di->i_flags &= ~cpu_to_le32(OCFS2_ORPHANED_FL);
	di->i_orphaned_slot = 0;
	set_nlink(inode, 1);
	ocfs2_set_links_count(di, inode->i_nlink);
	ocfs2_update_inode_fsync_trans(handle, inode, 1);
	ocfs2_journal_dirty(handle, di_bh);

	status = ocfs2_add_entry(handle, dentry, inode,
				 OCFS2_I(inode)->ip_blkno, parent_di_bh,
				 &lookup);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_commit;
	पूर्ण

	status = ocfs2_dentry_attach_lock(dentry, inode,
					  OCFS2_I(dir)->ip_blkno);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_commit;
	पूर्ण

	d_instantiate(dentry, inode);
	status = 0;
out_commit:
	ocfs2_commit_trans(osb, handle);
orphan_unlock:
	ocfs2_inode_unlock(orphan_dir_inode, 1);
	inode_unlock(orphan_dir_inode);
	iput(orphan_dir_inode);
leave:

	ocfs2_inode_unlock(dir, 1);

	brअन्यथा(di_bh);
	brअन्यथा(parent_di_bh);
	brअन्यथा(orphan_dir_bh);

	ocfs2_मुक्त_dir_lookup_result(&lookup);

	अगर (status)
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

स्थिर काष्ठा inode_operations ocfs2_dir_iops = अणु
	.create		= ocfs2_create,
	.lookup		= ocfs2_lookup,
	.link		= ocfs2_link,
	.unlink		= ocfs2_unlink,
	.सूची_हटाओ		= ocfs2_unlink,
	.symlink	= ocfs2_symlink,
	.सूची_गढ़ो		= ocfs2_सूची_गढ़ो,
	.mknod		= ocfs2_mknod,
	.नाम		= ocfs2_नाम,
	.setattr	= ocfs2_setattr,
	.getattr	= ocfs2_getattr,
	.permission	= ocfs2_permission,
	.listxattr	= ocfs2_listxattr,
	.fiemap         = ocfs2_fiemap,
	.get_acl	= ocfs2_iop_get_acl,
	.set_acl	= ocfs2_iop_set_acl,
	.fileattr_get	= ocfs2_fileattr_get,
	.fileattr_set	= ocfs2_fileattr_set,
पूर्ण;
