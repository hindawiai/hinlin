<शैली गुरु>
/*
  FUSE: Fileप्रणाली in Userspace
  Copyright (C) 2001-2008  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.
*/

#समावेश "fuse_i.h"

#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/statfs.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/pid_namespace.h>

MODULE_AUTHOR("Miklos Szeredi <miklos@szeredi.hu>");
MODULE_DESCRIPTION("Filesystem in Userspace");
MODULE_LICENSE("GPL");

अटल काष्ठा kmem_cache *fuse_inode_cachep;
काष्ठा list_head fuse_conn_list;
DEFINE_MUTEX(fuse_mutex);

अटल पूर्णांक set_global_limit(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);

अचिन्हित max_user_bgreq;
module_param_call(max_user_bgreq, set_global_limit, param_get_uपूर्णांक,
		  &max_user_bgreq, 0644);
__MODULE_PARM_TYPE(max_user_bgreq, "uint");
MODULE_PARM_DESC(max_user_bgreq,
 "Global limit for the maximum number of backgrounded requests an "
 "unprivileged user can set");

अचिन्हित max_user_congthresh;
module_param_call(max_user_congthresh, set_global_limit, param_get_uपूर्णांक,
		  &max_user_congthresh, 0644);
__MODULE_PARM_TYPE(max_user_congthresh, "uint");
MODULE_PARM_DESC(max_user_congthresh,
 "Global limit for the maximum congestion threshold an "
 "unprivileged user can set");

#घोषणा FUSE_SUPER_MAGIC 0x65735546

#घोषणा FUSE_DEFAULT_BLKSIZE 512

/** Maximum number of outstanding background requests */
#घोषणा FUSE_DEFAULT_MAX_BACKGROUND 12

/** Congestion starts at 75% of maximum */
#घोषणा FUSE_DEFAULT_CONGESTION_THRESHOLD (FUSE_DEFAULT_MAX_BACKGROUND * 3 / 4)

#अगर_घोषित CONFIG_BLOCK
अटल काष्ठा file_प्रणाली_type fuseblk_fs_type;
#पूर्ण_अगर

काष्ठा fuse_क्रमget_link *fuse_alloc_क्रमget(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा fuse_क्रमget_link), GFP_KERNEL_ACCOUNT);
पूर्ण

अटल काष्ठा inode *fuse_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा fuse_inode *fi;

	fi = kmem_cache_alloc(fuse_inode_cachep, GFP_KERNEL);
	अगर (!fi)
		वापस शून्य;

	fi->i_समय = 0;
	fi->inval_mask = 0;
	fi->nodeid = 0;
	fi->nlookup = 0;
	fi->attr_version = 0;
	fi->orig_ino = 0;
	fi->state = 0;
	mutex_init(&fi->mutex);
	init_rwsem(&fi->i_mmap_sem);
	spin_lock_init(&fi->lock);
	fi->क्रमget = fuse_alloc_क्रमget();
	अगर (!fi->क्रमget)
		जाओ out_मुक्त;

	अगर (IS_ENABLED(CONFIG_FUSE_DAX) && !fuse_dax_inode_alloc(sb, fi))
		जाओ out_मुक्त_क्रमget;

	वापस &fi->inode;

out_मुक्त_क्रमget:
	kमुक्त(fi->क्रमget);
out_मुक्त:
	kmem_cache_मुक्त(fuse_inode_cachep, fi);
	वापस शून्य;
पूर्ण

अटल व्योम fuse_मुक्त_inode(काष्ठा inode *inode)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	mutex_destroy(&fi->mutex);
	kमुक्त(fi->क्रमget);
#अगर_घोषित CONFIG_FUSE_DAX
	kमुक्त(fi->dax);
#पूर्ण_अगर
	kmem_cache_मुक्त(fuse_inode_cachep, fi);
पूर्ण

अटल व्योम fuse_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	अगर (inode->i_sb->s_flags & SB_ACTIVE) अणु
		काष्ठा fuse_conn *fc = get_fuse_conn(inode);

		अगर (FUSE_IS_DAX(inode))
			fuse_dax_inode_cleanup(inode);
		अगर (fi->nlookup) अणु
			fuse_queue_क्रमget(fc, fi->क्रमget, fi->nodeid,
					  fi->nlookup);
			fi->क्रमget = शून्य;
		पूर्ण
	पूर्ण
	अगर (S_ISREG(inode->i_mode) && !fuse_is_bad(inode)) अणु
		WARN_ON(!list_empty(&fi->ग_लिखो_files));
		WARN_ON(!list_empty(&fi->queued_ग_लिखोs));
	पूर्ण
पूर्ण

अटल पूर्णांक fuse_reconfigure(काष्ठा fs_context *fc)
अणु
	काष्ठा super_block *sb = fc->root->d_sb;

	sync_fileप्रणाली(sb);
	अगर (fc->sb_flags & SB_MANDLOCK)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/*
 * ino_t is 32-bits on 32-bit arch. We have to squash the 64-bit value करोwn
 * so that it will fit.
 */
अटल ino_t fuse_squash_ino(u64 ino64)
अणु
	ino_t ino = (ino_t) ino64;
	अगर (माप(ino_t) < माप(u64))
		ino ^= ino64 >> (माप(u64) - माप(ino_t)) * 8;
	वापस ino;
पूर्ण

व्योम fuse_change_attributes_common(काष्ठा inode *inode, काष्ठा fuse_attr *attr,
				   u64 attr_valid)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	lockdep_निश्चित_held(&fi->lock);

	fi->attr_version = atomic64_inc_वापस(&fc->attr_version);
	fi->i_समय = attr_valid;
	WRITE_ONCE(fi->inval_mask, 0);

	inode->i_ino     = fuse_squash_ino(attr->ino);
	inode->i_mode    = (inode->i_mode & S_IFMT) | (attr->mode & 07777);
	set_nlink(inode, attr->nlink);
	inode->i_uid     = make_kuid(fc->user_ns, attr->uid);
	inode->i_gid     = make_kgid(fc->user_ns, attr->gid);
	inode->i_blocks  = attr->blocks;
	inode->i_aसमय.tv_sec   = attr->aसमय;
	inode->i_aसमय.tv_nsec  = attr->aसमयnsec;
	/* mसमय from server may be stale due to local buffered ग_लिखो */
	अगर (!fc->ग_लिखोback_cache || !S_ISREG(inode->i_mode)) अणु
		inode->i_mसमय.tv_sec   = attr->mसमय;
		inode->i_mसमय.tv_nsec  = attr->mसमयnsec;
		inode->i_स_समय.tv_sec   = attr->स_समय;
		inode->i_स_समय.tv_nsec  = attr->स_समयnsec;
	पूर्ण

	अगर (attr->blksize != 0)
		inode->i_blkbits = ilog2(attr->blksize);
	अन्यथा
		inode->i_blkbits = inode->i_sb->s_blocksize_bits;

	/*
	 * Don't set the sticky bit in i_mode, unless we want the VFS
	 * to check permissions.  This prevents failures due to the
	 * check in may_delete().
	 */
	fi->orig_i_mode = inode->i_mode;
	अगर (!fc->शेष_permissions)
		inode->i_mode &= ~S_ISVTX;

	fi->orig_ino = attr->ino;

	/*
	 * We are refreshing inode data and it is possible that another
	 * client set suid/sgid or security.capability xattr. So clear
	 * S_NOSEC. Ideally, we could have cleared it only अगर suid/sgid
	 * was set or अगर security.capability xattr was set. But we करोn't
	 * know अगर security.capability has been set or not. So clear it
	 * anyway. Its less efficient but should be safe.
	 */
	inode->i_flags &= ~S_NOSEC;
पूर्ण

व्योम fuse_change_attributes(काष्ठा inode *inode, काष्ठा fuse_attr *attr,
			    u64 attr_valid, u64 attr_version)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	bool is_wb = fc->ग_लिखोback_cache;
	loff_t oldsize;
	काष्ठा बारpec64 old_mसमय;

	spin_lock(&fi->lock);
	अगर ((attr_version != 0 && fi->attr_version > attr_version) ||
	    test_bit(FUSE_I_SIZE_UNSTABLE, &fi->state)) अणु
		spin_unlock(&fi->lock);
		वापस;
	पूर्ण

	old_mसमय = inode->i_mसमय;
	fuse_change_attributes_common(inode, attr, attr_valid);

	oldsize = inode->i_size;
	/*
	 * In हाल of ग_लिखोback_cache enabled, the cached ग_लिखोs beyond खातापूर्ण
	 * extend local i_size without keeping userspace server in sync. So,
	 * attr->size coming from server can be stale. We cannot trust it.
	 */
	अगर (!is_wb || !S_ISREG(inode->i_mode))
		i_size_ग_लिखो(inode, attr->size);
	spin_unlock(&fi->lock);

	अगर (!is_wb && S_ISREG(inode->i_mode)) अणु
		bool inval = false;

		अगर (oldsize != attr->size) अणु
			truncate_pagecache(inode, attr->size);
			अगर (!fc->explicit_inval_data)
				inval = true;
		पूर्ण अन्यथा अगर (fc->स्वतः_inval_data) अणु
			काष्ठा बारpec64 new_mसमय = अणु
				.tv_sec = attr->mसमय,
				.tv_nsec = attr->mसमयnsec,
			पूर्ण;

			/*
			 * Auto inval mode also checks and invalidates अगर mसमय
			 * has changed.
			 */
			अगर (!बारpec64_equal(&old_mसमय, &new_mसमय))
				inval = true;
		पूर्ण

		अगर (inval)
			invalidate_inode_pages2(inode->i_mapping);
	पूर्ण
पूर्ण

अटल व्योम fuse_init_inode(काष्ठा inode *inode, काष्ठा fuse_attr *attr)
अणु
	inode->i_mode = attr->mode & S_IFMT;
	inode->i_size = attr->size;
	inode->i_mसमय.tv_sec  = attr->mसमय;
	inode->i_mसमय.tv_nsec = attr->mसमयnsec;
	inode->i_स_समय.tv_sec  = attr->स_समय;
	inode->i_स_समय.tv_nsec = attr->स_समयnsec;
	अगर (S_ISREG(inode->i_mode)) अणु
		fuse_init_common(inode);
		fuse_init_file_inode(inode);
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode))
		fuse_init_dir(inode);
	अन्यथा अगर (S_ISLNK(inode->i_mode))
		fuse_init_symlink(inode);
	अन्यथा अगर (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode) ||
		 S_ISFIFO(inode->i_mode) || S_ISSOCK(inode->i_mode)) अणु
		fuse_init_common(inode);
		init_special_inode(inode, inode->i_mode,
				   new_decode_dev(attr->rdev));
	पूर्ण अन्यथा
		BUG();
पूर्ण

अटल पूर्णांक fuse_inode_eq(काष्ठा inode *inode, व्योम *_nodeidp)
अणु
	u64 nodeid = *(u64 *) _nodeidp;
	अगर (get_node_id(inode) == nodeid)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक fuse_inode_set(काष्ठा inode *inode, व्योम *_nodeidp)
अणु
	u64 nodeid = *(u64 *) _nodeidp;
	get_fuse_inode(inode)->nodeid = nodeid;
	वापस 0;
पूर्ण

काष्ठा inode *fuse_iget(काष्ठा super_block *sb, u64 nodeid,
			पूर्णांक generation, काष्ठा fuse_attr *attr,
			u64 attr_valid, u64 attr_version)
अणु
	काष्ठा inode *inode;
	काष्ठा fuse_inode *fi;
	काष्ठा fuse_conn *fc = get_fuse_conn_super(sb);

	/*
	 * Auto mount poपूर्णांकs get their node id from the submount root, which is
	 * not a unique identअगरier within this fileप्रणाली.
	 *
	 * To aव्योम conflicts, करो not place submount poपूर्णांकs पूर्णांकo the inode hash
	 * table.
	 */
	अगर (fc->स्वतः_submounts && (attr->flags & FUSE_ATTR_SUBMOUNT) &&
	    S_ISसूची(attr->mode)) अणु
		inode = new_inode(sb);
		अगर (!inode)
			वापस शून्य;

		fuse_init_inode(inode, attr);
		get_fuse_inode(inode)->nodeid = nodeid;
		inode->i_flags |= S_AUTOMOUNT;
		जाओ करोne;
	पूर्ण

retry:
	inode = iget5_locked(sb, nodeid, fuse_inode_eq, fuse_inode_set, &nodeid);
	अगर (!inode)
		वापस शून्य;

	अगर ((inode->i_state & I_NEW)) अणु
		inode->i_flags |= S_NOATIME;
		अगर (!fc->ग_लिखोback_cache || !S_ISREG(attr->mode))
			inode->i_flags |= S_NOCMTIME;
		inode->i_generation = generation;
		fuse_init_inode(inode, attr);
		unlock_new_inode(inode);
	पूर्ण अन्यथा अगर (inode_wrong_type(inode, attr->mode)) अणु
		/* Inode has changed type, any I/O on the old should fail */
		fuse_make_bad(inode);
		iput(inode);
		जाओ retry;
	पूर्ण
करोne:
	fi = get_fuse_inode(inode);
	spin_lock(&fi->lock);
	fi->nlookup++;
	spin_unlock(&fi->lock);
	fuse_change_attributes(inode, attr, attr_valid, attr_version);

	वापस inode;
पूर्ण

काष्ठा inode *fuse_ilookup(काष्ठा fuse_conn *fc, u64 nodeid,
			   काष्ठा fuse_mount **fm)
अणु
	काष्ठा fuse_mount *fm_iter;
	काष्ठा inode *inode;

	WARN_ON(!rwsem_is_locked(&fc->समाप्तsb));
	list_क्रम_each_entry(fm_iter, &fc->mounts, fc_entry) अणु
		अगर (!fm_iter->sb)
			जारी;

		inode = ilookup5(fm_iter->sb, nodeid, fuse_inode_eq, &nodeid);
		अगर (inode) अणु
			अगर (fm)
				*fm = fm_iter;
			वापस inode;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक fuse_reverse_inval_inode(काष्ठा fuse_conn *fc, u64 nodeid,
			     loff_t offset, loff_t len)
अणु
	काष्ठा fuse_inode *fi;
	काष्ठा inode *inode;
	pgoff_t pg_start;
	pgoff_t pg_end;

	inode = fuse_ilookup(fc, nodeid, शून्य);
	अगर (!inode)
		वापस -ENOENT;

	fi = get_fuse_inode(inode);
	spin_lock(&fi->lock);
	fi->attr_version = atomic64_inc_वापस(&fc->attr_version);
	spin_unlock(&fi->lock);

	fuse_invalidate_attr(inode);
	क्रमget_all_cached_acls(inode);
	अगर (offset >= 0) अणु
		pg_start = offset >> PAGE_SHIFT;
		अगर (len <= 0)
			pg_end = -1;
		अन्यथा
			pg_end = (offset + len - 1) >> PAGE_SHIFT;
		invalidate_inode_pages2_range(inode->i_mapping,
					      pg_start, pg_end);
	पूर्ण
	iput(inode);
	वापस 0;
पूर्ण

bool fuse_lock_inode(काष्ठा inode *inode)
अणु
	bool locked = false;

	अगर (!get_fuse_conn(inode)->parallel_dirops) अणु
		mutex_lock(&get_fuse_inode(inode)->mutex);
		locked = true;
	पूर्ण

	वापस locked;
पूर्ण

व्योम fuse_unlock_inode(काष्ठा inode *inode, bool locked)
अणु
	अगर (locked)
		mutex_unlock(&get_fuse_inode(inode)->mutex);
पूर्ण

अटल व्योम fuse_umount_begin(काष्ठा super_block *sb)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn_super(sb);

	अगर (!fc->no_क्रमce_umount)
		fuse_पात_conn(fc);
पूर्ण

अटल व्योम fuse_send_destroy(काष्ठा fuse_mount *fm)
अणु
	अगर (fm->fc->conn_init) अणु
		FUSE_ARGS(args);

		args.opcode = FUSE_DESTROY;
		args.क्रमce = true;
		args.nocreds = true;
		fuse_simple_request(fm, &args);
	पूर्ण
पूर्ण

अटल व्योम fuse_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount_super(sb);

	fuse_conn_put(fm->fc);
	kमुक्त(fm);
पूर्ण

अटल व्योम convert_fuse_statfs(काष्ठा kstatfs *stbuf, काष्ठा fuse_kstatfs *attr)
अणु
	stbuf->f_type    = FUSE_SUPER_MAGIC;
	stbuf->f_bsize   = attr->bsize;
	stbuf->f_frsize  = attr->frsize;
	stbuf->f_blocks  = attr->blocks;
	stbuf->f_bमुक्त   = attr->bमुक्त;
	stbuf->f_bavail  = attr->bavail;
	stbuf->f_files   = attr->files;
	stbuf->f_fमुक्त   = attr->fमुक्त;
	stbuf->f_namelen = attr->namelen;
	/* fsid is left zero */
पूर्ण

अटल पूर्णांक fuse_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा fuse_mount *fm = get_fuse_mount_super(sb);
	FUSE_ARGS(args);
	काष्ठा fuse_statfs_out outarg;
	पूर्णांक err;

	अगर (!fuse_allow_current_process(fm->fc)) अणु
		buf->f_type = FUSE_SUPER_MAGIC;
		वापस 0;
	पूर्ण

	स_रखो(&outarg, 0, माप(outarg));
	args.in_numargs = 0;
	args.opcode = FUSE_STATFS;
	args.nodeid = get_node_id(d_inode(dentry));
	args.out_numargs = 1;
	args.out_args[0].size = माप(outarg);
	args.out_args[0].value = &outarg;
	err = fuse_simple_request(fm, &args);
	अगर (!err)
		convert_fuse_statfs(buf, &outarg.st);
	वापस err;
पूर्ण

क्रमागत अणु
	OPT_SOURCE,
	OPT_SUBTYPE,
	OPT_FD,
	OPT_ROOTMODE,
	OPT_USER_ID,
	OPT_GROUP_ID,
	OPT_DEFAULT_PERMISSIONS,
	OPT_ALLOW_OTHER,
	OPT_MAX_READ,
	OPT_BLKSIZE,
	OPT_ERR
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec fuse_fs_parameters[] = अणु
	fsparam_string	("source",		OPT_SOURCE),
	fsparam_u32	("fd",			OPT_FD),
	fsparam_u32oct	("rootmode",		OPT_ROOTMODE),
	fsparam_u32	("user_id",		OPT_USER_ID),
	fsparam_u32	("group_id",		OPT_GROUP_ID),
	fsparam_flag	("default_permissions",	OPT_DEFAULT_PERMISSIONS),
	fsparam_flag	("allow_other",		OPT_ALLOW_OTHER),
	fsparam_u32	("max_read",		OPT_MAX_READ),
	fsparam_u32	("blksize",		OPT_BLKSIZE),
	fsparam_string	("subtype",		OPT_SUBTYPE),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक fuse_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा fs_parse_result result;
	काष्ठा fuse_fs_context *ctx = fc->fs_निजी;
	पूर्णांक opt;

	अगर (fc->purpose == FS_CONTEXT_FOR_RECONFIGURE) अणु
		/*
		 * Ignore options coming from mount(MS_REMOUNT) क्रम backward
		 * compatibility.
		 */
		अगर (fc->oldapi)
			वापस 0;

		वापस invalfc(fc, "No changes allowed in reconfigure");
	पूर्ण

	opt = fs_parse(fc, fuse_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल OPT_SOURCE:
		अगर (fc->source)
			वापस invalfc(fc, "Multiple sources specified");
		fc->source = param->string;
		param->string = शून्य;
		अवरोध;

	हाल OPT_SUBTYPE:
		अगर (ctx->subtype)
			वापस invalfc(fc, "Multiple subtypes specified");
		ctx->subtype = param->string;
		param->string = शून्य;
		वापस 0;

	हाल OPT_FD:
		ctx->fd = result.uपूर्णांक_32;
		ctx->fd_present = true;
		अवरोध;

	हाल OPT_ROOTMODE:
		अगर (!fuse_valid_type(result.uपूर्णांक_32))
			वापस invalfc(fc, "Invalid rootmode");
		ctx->rooपंचांगode = result.uपूर्णांक_32;
		ctx->rooपंचांगode_present = true;
		अवरोध;

	हाल OPT_USER_ID:
		ctx->user_id = make_kuid(fc->user_ns, result.uपूर्णांक_32);
		अगर (!uid_valid(ctx->user_id))
			वापस invalfc(fc, "Invalid user_id");
		ctx->user_id_present = true;
		अवरोध;

	हाल OPT_GROUP_ID:
		ctx->group_id = make_kgid(fc->user_ns, result.uपूर्णांक_32);
		अगर (!gid_valid(ctx->group_id))
			वापस invalfc(fc, "Invalid group_id");
		ctx->group_id_present = true;
		अवरोध;

	हाल OPT_DEFAULT_PERMISSIONS:
		ctx->शेष_permissions = true;
		अवरोध;

	हाल OPT_ALLOW_OTHER:
		ctx->allow_other = true;
		अवरोध;

	हाल OPT_MAX_READ:
		ctx->max_पढ़ो = result.uपूर्णांक_32;
		अवरोध;

	हाल OPT_BLKSIZE:
		अगर (!ctx->is_bdev)
			वापस invalfc(fc, "blksize only supported for fuseblk");
		ctx->blksize = result.uपूर्णांक_32;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fuse_मुक्त_fc(काष्ठा fs_context *fc)
अणु
	काष्ठा fuse_fs_context *ctx = fc->fs_निजी;

	अगर (ctx) अणु
		kमुक्त(ctx->subtype);
		kमुक्त(ctx);
	पूर्ण
पूर्ण

अटल पूर्णांक fuse_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा super_block *sb = root->d_sb;
	काष्ठा fuse_conn *fc = get_fuse_conn_super(sb);

	अगर (fc->legacy_opts_show) अणु
		seq_म_लिखो(m, ",user_id=%u",
			   from_kuid_munged(fc->user_ns, fc->user_id));
		seq_म_लिखो(m, ",group_id=%u",
			   from_kgid_munged(fc->user_ns, fc->group_id));
		अगर (fc->शेष_permissions)
			seq_माला_दो(m, ",default_permissions");
		अगर (fc->allow_other)
			seq_माला_दो(m, ",allow_other");
		अगर (fc->max_पढ़ो != ~0)
			seq_म_लिखो(m, ",max_read=%u", fc->max_पढ़ो);
		अगर (sb->s_bdev && sb->s_blocksize != FUSE_DEFAULT_BLKSIZE)
			seq_म_लिखो(m, ",blksize=%lu", sb->s_blocksize);
	पूर्ण
#अगर_घोषित CONFIG_FUSE_DAX
	अगर (fc->dax)
		seq_माला_दो(m, ",dax");
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम fuse_iqueue_init(काष्ठा fuse_iqueue *fiq,
			     स्थिर काष्ठा fuse_iqueue_ops *ops,
			     व्योम *priv)
अणु
	स_रखो(fiq, 0, माप(काष्ठा fuse_iqueue));
	spin_lock_init(&fiq->lock);
	init_रुकोqueue_head(&fiq->रुकोq);
	INIT_LIST_HEAD(&fiq->pending);
	INIT_LIST_HEAD(&fiq->पूर्णांकerrupts);
	fiq->क्रमget_list_tail = &fiq->क्रमget_list_head;
	fiq->connected = 1;
	fiq->ops = ops;
	fiq->priv = priv;
पूर्ण

अटल व्योम fuse_pqueue_init(काष्ठा fuse_pqueue *fpq)
अणु
	अचिन्हित पूर्णांक i;

	spin_lock_init(&fpq->lock);
	क्रम (i = 0; i < FUSE_PQ_HASH_SIZE; i++)
		INIT_LIST_HEAD(&fpq->processing[i]);
	INIT_LIST_HEAD(&fpq->io);
	fpq->connected = 1;
पूर्ण

व्योम fuse_conn_init(काष्ठा fuse_conn *fc, काष्ठा fuse_mount *fm,
		    काष्ठा user_namespace *user_ns,
		    स्थिर काष्ठा fuse_iqueue_ops *fiq_ops, व्योम *fiq_priv)
अणु
	स_रखो(fc, 0, माप(*fc));
	spin_lock_init(&fc->lock);
	spin_lock_init(&fc->bg_lock);
	init_rwsem(&fc->समाप्तsb);
	refcount_set(&fc->count, 1);
	atomic_set(&fc->dev_count, 1);
	init_रुकोqueue_head(&fc->blocked_रुकोq);
	fuse_iqueue_init(&fc->iq, fiq_ops, fiq_priv);
	INIT_LIST_HEAD(&fc->bg_queue);
	INIT_LIST_HEAD(&fc->entry);
	INIT_LIST_HEAD(&fc->devices);
	atomic_set(&fc->num_रुकोing, 0);
	fc->max_background = FUSE_DEFAULT_MAX_BACKGROUND;
	fc->congestion_threshold = FUSE_DEFAULT_CONGESTION_THRESHOLD;
	atomic64_set(&fc->khctr, 0);
	fc->polled_files = RB_ROOT;
	fc->blocked = 0;
	fc->initialized = 0;
	fc->connected = 1;
	atomic64_set(&fc->attr_version, 1);
	get_अक्रमom_bytes(&fc->scramble_key, माप(fc->scramble_key));
	fc->pid_ns = get_pid_ns(task_active_pid_ns(current));
	fc->user_ns = get_user_ns(user_ns);
	fc->max_pages = FUSE_DEFAULT_MAX_PAGES_PER_REQ;
	fc->max_pages_limit = FUSE_MAX_MAX_PAGES;

	INIT_LIST_HEAD(&fc->mounts);
	list_add(&fm->fc_entry, &fc->mounts);
	fm->fc = fc;
पूर्ण
EXPORT_SYMBOL_GPL(fuse_conn_init);

व्योम fuse_conn_put(काष्ठा fuse_conn *fc)
अणु
	अगर (refcount_dec_and_test(&fc->count)) अणु
		काष्ठा fuse_iqueue *fiq = &fc->iq;

		अगर (IS_ENABLED(CONFIG_FUSE_DAX))
			fuse_dax_conn_मुक्त(fc);
		अगर (fiq->ops->release)
			fiq->ops->release(fiq);
		put_pid_ns(fc->pid_ns);
		put_user_ns(fc->user_ns);
		fc->release(fc);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fuse_conn_put);

काष्ठा fuse_conn *fuse_conn_get(काष्ठा fuse_conn *fc)
अणु
	refcount_inc(&fc->count);
	वापस fc;
पूर्ण
EXPORT_SYMBOL_GPL(fuse_conn_get);

अटल काष्ठा inode *fuse_get_root_inode(काष्ठा super_block *sb, अचिन्हित mode)
अणु
	काष्ठा fuse_attr attr;
	स_रखो(&attr, 0, माप(attr));

	attr.mode = mode;
	attr.ino = FUSE_ROOT_ID;
	attr.nlink = 1;
	वापस fuse_iget(sb, 1, 0, &attr, 0, 0);
पूर्ण

काष्ठा fuse_inode_handle अणु
	u64 nodeid;
	u32 generation;
पूर्ण;

अटल काष्ठा dentry *fuse_get_dentry(काष्ठा super_block *sb,
				      काष्ठा fuse_inode_handle *handle)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn_super(sb);
	काष्ठा inode *inode;
	काष्ठा dentry *entry;
	पूर्णांक err = -ESTALE;

	अगर (handle->nodeid == 0)
		जाओ out_err;

	inode = ilookup5(sb, handle->nodeid, fuse_inode_eq, &handle->nodeid);
	अगर (!inode) अणु
		काष्ठा fuse_entry_out outarg;
		स्थिर काष्ठा qstr name = QSTR_INIT(".", 1);

		अगर (!fc->export_support)
			जाओ out_err;

		err = fuse_lookup_name(sb, handle->nodeid, &name, &outarg,
				       &inode);
		अगर (err && err != -ENOENT)
			जाओ out_err;
		अगर (err || !inode) अणु
			err = -ESTALE;
			जाओ out_err;
		पूर्ण
		err = -EIO;
		अगर (get_node_id(inode) != handle->nodeid)
			जाओ out_iput;
	पूर्ण
	err = -ESTALE;
	अगर (inode->i_generation != handle->generation)
		जाओ out_iput;

	entry = d_obtain_alias(inode);
	अगर (!IS_ERR(entry) && get_node_id(inode) != FUSE_ROOT_ID)
		fuse_invalidate_entry_cache(entry);

	वापस entry;

 out_iput:
	iput(inode);
 out_err:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक fuse_encode_fh(काष्ठा inode *inode, u32 *fh, पूर्णांक *max_len,
			   काष्ठा inode *parent)
अणु
	पूर्णांक len = parent ? 6 : 3;
	u64 nodeid;
	u32 generation;

	अगर (*max_len < len) अणु
		*max_len = len;
		वापस  खाताID_INVALID;
	पूर्ण

	nodeid = get_fuse_inode(inode)->nodeid;
	generation = inode->i_generation;

	fh[0] = (u32)(nodeid >> 32);
	fh[1] = (u32)(nodeid & 0xffffffff);
	fh[2] = generation;

	अगर (parent) अणु
		nodeid = get_fuse_inode(parent)->nodeid;
		generation = parent->i_generation;

		fh[3] = (u32)(nodeid >> 32);
		fh[4] = (u32)(nodeid & 0xffffffff);
		fh[5] = generation;
	पूर्ण

	*max_len = len;
	वापस parent ? 0x82 : 0x81;
पूर्ण

अटल काष्ठा dentry *fuse_fh_to_dentry(काष्ठा super_block *sb,
		काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा fuse_inode_handle handle;

	अगर ((fh_type != 0x81 && fh_type != 0x82) || fh_len < 3)
		वापस शून्य;

	handle.nodeid = (u64) fid->raw[0] << 32;
	handle.nodeid |= (u64) fid->raw[1];
	handle.generation = fid->raw[2];
	वापस fuse_get_dentry(sb, &handle);
पूर्ण

अटल काष्ठा dentry *fuse_fh_to_parent(काष्ठा super_block *sb,
		काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा fuse_inode_handle parent;

	अगर (fh_type != 0x82 || fh_len < 6)
		वापस शून्य;

	parent.nodeid = (u64) fid->raw[3] << 32;
	parent.nodeid |= (u64) fid->raw[4];
	parent.generation = fid->raw[5];
	वापस fuse_get_dentry(sb, &parent);
पूर्ण

अटल काष्ठा dentry *fuse_get_parent(काष्ठा dentry *child)
अणु
	काष्ठा inode *child_inode = d_inode(child);
	काष्ठा fuse_conn *fc = get_fuse_conn(child_inode);
	काष्ठा inode *inode;
	काष्ठा dentry *parent;
	काष्ठा fuse_entry_out outarg;
	पूर्णांक err;

	अगर (!fc->export_support)
		वापस ERR_PTR(-ESTALE);

	err = fuse_lookup_name(child_inode->i_sb, get_node_id(child_inode),
			       &करोtकरोt_name, &outarg, &inode);
	अगर (err) अणु
		अगर (err == -ENOENT)
			वापस ERR_PTR(-ESTALE);
		वापस ERR_PTR(err);
	पूर्ण

	parent = d_obtain_alias(inode);
	अगर (!IS_ERR(parent) && get_node_id(inode) != FUSE_ROOT_ID)
		fuse_invalidate_entry_cache(parent);

	वापस parent;
पूर्ण

अटल स्थिर काष्ठा export_operations fuse_export_operations = अणु
	.fh_to_dentry	= fuse_fh_to_dentry,
	.fh_to_parent	= fuse_fh_to_parent,
	.encode_fh	= fuse_encode_fh,
	.get_parent	= fuse_get_parent,
पूर्ण;

अटल स्थिर काष्ठा super_operations fuse_super_operations = अणु
	.alloc_inode    = fuse_alloc_inode,
	.मुक्त_inode     = fuse_मुक्त_inode,
	.evict_inode	= fuse_evict_inode,
	.ग_लिखो_inode	= fuse_ग_लिखो_inode,
	.drop_inode	= generic_delete_inode,
	.put_super	= fuse_put_super,
	.umount_begin	= fuse_umount_begin,
	.statfs		= fuse_statfs,
	.show_options	= fuse_show_options,
पूर्ण;

अटल व्योम sanitize_global_limit(अचिन्हित *limit)
अणु
	/*
	 * The शेष maximum number of async requests is calculated to consume
	 * 1/2^13 of the total memory, assuming 392 bytes per request.
	 */
	अगर (*limit == 0)
		*limit = ((totalram_pages() << PAGE_SHIFT) >> 13) / 392;

	अगर (*limit >= 1 << 16)
		*limit = (1 << 16) - 1;
पूर्ण

अटल पूर्णांक set_global_limit(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक rv;

	rv = param_set_uपूर्णांक(val, kp);
	अगर (rv)
		वापस rv;

	sanitize_global_limit((अचिन्हित *)kp->arg);

	वापस 0;
पूर्ण

अटल व्योम process_init_limits(काष्ठा fuse_conn *fc, काष्ठा fuse_init_out *arg)
अणु
	पूर्णांक cap_sys_admin = capable(CAP_SYS_ADMIN);

	अगर (arg->minor < 13)
		वापस;

	sanitize_global_limit(&max_user_bgreq);
	sanitize_global_limit(&max_user_congthresh);

	spin_lock(&fc->bg_lock);
	अगर (arg->max_background) अणु
		fc->max_background = arg->max_background;

		अगर (!cap_sys_admin && fc->max_background > max_user_bgreq)
			fc->max_background = max_user_bgreq;
	पूर्ण
	अगर (arg->congestion_threshold) अणु
		fc->congestion_threshold = arg->congestion_threshold;

		अगर (!cap_sys_admin &&
		    fc->congestion_threshold > max_user_congthresh)
			fc->congestion_threshold = max_user_congthresh;
	पूर्ण
	spin_unlock(&fc->bg_lock);
पूर्ण

काष्ठा fuse_init_args अणु
	काष्ठा fuse_args args;
	काष्ठा fuse_init_in in;
	काष्ठा fuse_init_out out;
पूर्ण;

अटल व्योम process_init_reply(काष्ठा fuse_mount *fm, काष्ठा fuse_args *args,
			       पूर्णांक error)
अणु
	काष्ठा fuse_conn *fc = fm->fc;
	काष्ठा fuse_init_args *ia = container_of(args, typeof(*ia), args);
	काष्ठा fuse_init_out *arg = &ia->out;
	bool ok = true;

	अगर (error || arg->major != FUSE_KERNEL_VERSION)
		ok = false;
	अन्यथा अणु
		अचिन्हित दीर्घ ra_pages;

		process_init_limits(fc, arg);

		अगर (arg->minor >= 6) अणु
			ra_pages = arg->max_पढ़ोahead / PAGE_SIZE;
			अगर (arg->flags & FUSE_ASYNC_READ)
				fc->async_पढ़ो = 1;
			अगर (!(arg->flags & FUSE_POSIX_LOCKS))
				fc->no_lock = 1;
			अगर (arg->minor >= 17) अणु
				अगर (!(arg->flags & FUSE_FLOCK_LOCKS))
					fc->no_flock = 1;
			पूर्ण अन्यथा अणु
				अगर (!(arg->flags & FUSE_POSIX_LOCKS))
					fc->no_flock = 1;
			पूर्ण
			अगर (arg->flags & FUSE_ATOMIC_O_TRUNC)
				fc->atomic_o_trunc = 1;
			अगर (arg->minor >= 9) अणु
				/* LOOKUP has dependency on proto version */
				अगर (arg->flags & FUSE_EXPORT_SUPPORT)
					fc->export_support = 1;
			पूर्ण
			अगर (arg->flags & FUSE_BIG_WRITES)
				fc->big_ग_लिखोs = 1;
			अगर (arg->flags & FUSE_DONT_MASK)
				fc->करोnt_mask = 1;
			अगर (arg->flags & FUSE_AUTO_INVAL_DATA)
				fc->स्वतः_inval_data = 1;
			अन्यथा अगर (arg->flags & FUSE_EXPLICIT_INVAL_DATA)
				fc->explicit_inval_data = 1;
			अगर (arg->flags & FUSE_DO_READसूचीPLUS) अणु
				fc->करो_सूची_पढ़ोplus = 1;
				अगर (arg->flags & FUSE_READसूचीPLUS_AUTO)
					fc->सूची_पढ़ोplus_स्वतः = 1;
			पूर्ण
			अगर (arg->flags & FUSE_ASYNC_DIO)
				fc->async_dio = 1;
			अगर (arg->flags & FUSE_WRITEBACK_CACHE)
				fc->ग_लिखोback_cache = 1;
			अगर (arg->flags & FUSE_PARALLEL_सूचीOPS)
				fc->parallel_dirops = 1;
			अगर (arg->flags & FUSE_HANDLE_KILLPRIV)
				fc->handle_समाप्तpriv = 1;
			अगर (arg->समय_gran && arg->समय_gran <= 1000000000)
				fm->sb->s_समय_gran = arg->समय_gran;
			अगर ((arg->flags & FUSE_POSIX_ACL)) अणु
				fc->शेष_permissions = 1;
				fc->posix_acl = 1;
				fm->sb->s_xattr = fuse_acl_xattr_handlers;
			पूर्ण
			अगर (arg->flags & FUSE_CACHE_SYMLINKS)
				fc->cache_symlinks = 1;
			अगर (arg->flags & FUSE_ABORT_ERROR)
				fc->पात_err = 1;
			अगर (arg->flags & FUSE_MAX_PAGES) अणु
				fc->max_pages =
					min_t(अचिन्हित पूर्णांक, fc->max_pages_limit,
					max_t(अचिन्हित पूर्णांक, arg->max_pages, 1));
			पूर्ण
			अगर (IS_ENABLED(CONFIG_FUSE_DAX) &&
			    arg->flags & FUSE_MAP_ALIGNMENT &&
			    !fuse_dax_check_alignment(fc, arg->map_alignment)) अणु
				ok = false;
			पूर्ण
			अगर (arg->flags & FUSE_HANDLE_KILLPRIV_V2) अणु
				fc->handle_समाप्तpriv_v2 = 1;
				fm->sb->s_flags |= SB_NOSEC;
			पूर्ण
			अगर (arg->flags & FUSE_SETXATTR_EXT)
				fc->setxattr_ext = 1;
		पूर्ण अन्यथा अणु
			ra_pages = fc->max_पढ़ो / PAGE_SIZE;
			fc->no_lock = 1;
			fc->no_flock = 1;
		पूर्ण

		fm->sb->s_bdi->ra_pages =
				min(fm->sb->s_bdi->ra_pages, ra_pages);
		fc->minor = arg->minor;
		fc->max_ग_लिखो = arg->minor < 5 ? 4096 : arg->max_ग_लिखो;
		fc->max_ग_लिखो = max_t(अचिन्हित, 4096, fc->max_ग_लिखो);
		fc->conn_init = 1;
	पूर्ण
	kमुक्त(ia);

	अगर (!ok) अणु
		fc->conn_init = 0;
		fc->conn_error = 1;
	पूर्ण

	fuse_set_initialized(fc);
	wake_up_all(&fc->blocked_रुकोq);
पूर्ण

व्योम fuse_send_init(काष्ठा fuse_mount *fm)
अणु
	काष्ठा fuse_init_args *ia;

	ia = kzalloc(माप(*ia), GFP_KERNEL | __GFP_NOFAIL);

	ia->in.major = FUSE_KERNEL_VERSION;
	ia->in.minor = FUSE_KERNEL_MINOR_VERSION;
	ia->in.max_पढ़ोahead = fm->sb->s_bdi->ra_pages * PAGE_SIZE;
	ia->in.flags |=
		FUSE_ASYNC_READ | FUSE_POSIX_LOCKS | FUSE_ATOMIC_O_TRUNC |
		FUSE_EXPORT_SUPPORT | FUSE_BIG_WRITES | FUSE_DONT_MASK |
		FUSE_SPLICE_WRITE | FUSE_SPLICE_MOVE | FUSE_SPLICE_READ |
		FUSE_FLOCK_LOCKS | FUSE_HAS_IOCTL_सूची | FUSE_AUTO_INVAL_DATA |
		FUSE_DO_READसूचीPLUS | FUSE_READसूचीPLUS_AUTO | FUSE_ASYNC_DIO |
		FUSE_WRITEBACK_CACHE | FUSE_NO_OPEN_SUPPORT |
		FUSE_PARALLEL_सूचीOPS | FUSE_HANDLE_KILLPRIV | FUSE_POSIX_ACL |
		FUSE_ABORT_ERROR | FUSE_MAX_PAGES | FUSE_CACHE_SYMLINKS |
		FUSE_NO_OPENसूची_SUPPORT | FUSE_EXPLICIT_INVAL_DATA |
		FUSE_HANDLE_KILLPRIV_V2 | FUSE_SETXATTR_EXT;
#अगर_घोषित CONFIG_FUSE_DAX
	अगर (fm->fc->dax)
		ia->in.flags |= FUSE_MAP_ALIGNMENT;
#पूर्ण_अगर
	अगर (fm->fc->स्वतः_submounts)
		ia->in.flags |= FUSE_SUBMOUNTS;

	ia->args.opcode = FUSE_INIT;
	ia->args.in_numargs = 1;
	ia->args.in_args[0].size = माप(ia->in);
	ia->args.in_args[0].value = &ia->in;
	ia->args.out_numargs = 1;
	/* Variable length argument used क्रम backward compatibility
	   with पूर्णांकerface version < 7.5.  Rest of init_out is zeroed
	   by करो_get_request(), so a लघु reply is not a problem */
	ia->args.out_argvar = true;
	ia->args.out_args[0].size = माप(ia->out);
	ia->args.out_args[0].value = &ia->out;
	ia->args.क्रमce = true;
	ia->args.nocreds = true;
	ia->args.end = process_init_reply;

	अगर (fuse_simple_background(fm, &ia->args, GFP_KERNEL) != 0)
		process_init_reply(fm, &ia->args, -ENOTCONN);
पूर्ण
EXPORT_SYMBOL_GPL(fuse_send_init);

व्योम fuse_मुक्त_conn(काष्ठा fuse_conn *fc)
अणु
	WARN_ON(!list_empty(&fc->devices));
	kमुक्त_rcu(fc, rcu);
पूर्ण
EXPORT_SYMBOL_GPL(fuse_मुक्त_conn);

अटल पूर्णांक fuse_bdi_init(काष्ठा fuse_conn *fc, काष्ठा super_block *sb)
अणु
	पूर्णांक err;
	अक्षर *suffix = "";

	अगर (sb->s_bdev) अणु
		suffix = "-fuseblk";
		/*
		 * sb->s_bdi poपूर्णांकs to blkdev's bdi however we want to redirect
		 * it to our निजी bdi...
		 */
		bdi_put(sb->s_bdi);
		sb->s_bdi = &noop_backing_dev_info;
	पूर्ण
	err = super_setup_bdi_name(sb, "%u:%u%s", MAJOR(fc->dev),
				   MINOR(fc->dev), suffix);
	अगर (err)
		वापस err;

	/* fuse करोes it's own ग_लिखोback accounting */
	sb->s_bdi->capabilities &= ~BDI_CAP_WRITEBACK_ACCT;
	sb->s_bdi->capabilities |= BDI_CAP_STRICTLIMIT;

	/*
	 * For a single fuse fileप्रणाली use max 1% of dirty +
	 * ग_लिखोback threshold.
	 *
	 * This gives about 1M of ग_लिखो buffer क्रम memory maps on a
	 * machine with 1G and 10% dirty_ratio, which should be more
	 * than enough.
	 *
	 * Privileged users can उठाओ it by writing to
	 *
	 *    /sys/class/bdi/<bdi>/max_ratio
	 */
	bdi_set_max_ratio(sb->s_bdi, 1);

	वापस 0;
पूर्ण

काष्ठा fuse_dev *fuse_dev_alloc(व्योम)
अणु
	काष्ठा fuse_dev *fud;
	काष्ठा list_head *pq;

	fud = kzalloc(माप(काष्ठा fuse_dev), GFP_KERNEL);
	अगर (!fud)
		वापस शून्य;

	pq = kसुस्मृति(FUSE_PQ_HASH_SIZE, माप(काष्ठा list_head), GFP_KERNEL);
	अगर (!pq) अणु
		kमुक्त(fud);
		वापस शून्य;
	पूर्ण

	fud->pq.processing = pq;
	fuse_pqueue_init(&fud->pq);

	वापस fud;
पूर्ण
EXPORT_SYMBOL_GPL(fuse_dev_alloc);

व्योम fuse_dev_install(काष्ठा fuse_dev *fud, काष्ठा fuse_conn *fc)
अणु
	fud->fc = fuse_conn_get(fc);
	spin_lock(&fc->lock);
	list_add_tail(&fud->entry, &fc->devices);
	spin_unlock(&fc->lock);
पूर्ण
EXPORT_SYMBOL_GPL(fuse_dev_install);

काष्ठा fuse_dev *fuse_dev_alloc_install(काष्ठा fuse_conn *fc)
अणु
	काष्ठा fuse_dev *fud;

	fud = fuse_dev_alloc();
	अगर (!fud)
		वापस शून्य;

	fuse_dev_install(fud, fc);
	वापस fud;
पूर्ण
EXPORT_SYMBOL_GPL(fuse_dev_alloc_install);

व्योम fuse_dev_मुक्त(काष्ठा fuse_dev *fud)
अणु
	काष्ठा fuse_conn *fc = fud->fc;

	अगर (fc) अणु
		spin_lock(&fc->lock);
		list_del(&fud->entry);
		spin_unlock(&fc->lock);

		fuse_conn_put(fc);
	पूर्ण
	kमुक्त(fud->pq.processing);
	kमुक्त(fud);
पूर्ण
EXPORT_SYMBOL_GPL(fuse_dev_मुक्त);

अटल व्योम fuse_fill_attr_from_inode(काष्ठा fuse_attr *attr,
				      स्थिर काष्ठा fuse_inode *fi)
अणु
	*attr = (काष्ठा fuse_attr)अणु
		.ino		= fi->inode.i_ino,
		.size		= fi->inode.i_size,
		.blocks		= fi->inode.i_blocks,
		.aसमय		= fi->inode.i_aसमय.tv_sec,
		.mसमय		= fi->inode.i_mसमय.tv_sec,
		.स_समय		= fi->inode.i_स_समय.tv_sec,
		.aसमयnsec	= fi->inode.i_aसमय.tv_nsec,
		.mसमयnsec	= fi->inode.i_mसमय.tv_nsec,
		.स_समयnsec	= fi->inode.i_स_समय.tv_nsec,
		.mode		= fi->inode.i_mode,
		.nlink		= fi->inode.i_nlink,
		.uid		= fi->inode.i_uid.val,
		.gid		= fi->inode.i_gid.val,
		.rdev		= fi->inode.i_rdev,
		.blksize	= 1u << fi->inode.i_blkbits,
	पूर्ण;
पूर्ण

अटल व्योम fuse_sb_शेषs(काष्ठा super_block *sb)
अणु
	sb->s_magic = FUSE_SUPER_MAGIC;
	sb->s_op = &fuse_super_operations;
	sb->s_xattr = fuse_xattr_handlers;
	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	sb->s_समय_gran = 1;
	sb->s_export_op = &fuse_export_operations;
	sb->s_अगरlags |= SB_I_IMA_UNVERIFIABLE_SIGNATURE;
	अगर (sb->s_user_ns != &init_user_ns)
		sb->s_अगरlags |= SB_I_UNTRUSTED_MOUNTER;
	sb->s_flags &= ~(SB_NOSEC | SB_I_VERSION);

	/*
	 * If we are not in the initial user namespace posix
	 * acls must be translated.
	 */
	अगर (sb->s_user_ns != &init_user_ns)
		sb->s_xattr = fuse_no_acl_xattr_handlers;
पूर्ण

पूर्णांक fuse_fill_super_submount(काष्ठा super_block *sb,
			     काष्ठा fuse_inode *parent_fi)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount_super(sb);
	काष्ठा super_block *parent_sb = parent_fi->inode.i_sb;
	काष्ठा fuse_attr root_attr;
	काष्ठा inode *root;

	fuse_sb_शेषs(sb);
	fm->sb = sb;

	WARN_ON(sb->s_bdi != &noop_backing_dev_info);
	sb->s_bdi = bdi_get(parent_sb->s_bdi);

	sb->s_xattr = parent_sb->s_xattr;
	sb->s_समय_gran = parent_sb->s_समय_gran;
	sb->s_blocksize = parent_sb->s_blocksize;
	sb->s_blocksize_bits = parent_sb->s_blocksize_bits;
	sb->s_subtype = kstrdup(parent_sb->s_subtype, GFP_KERNEL);
	अगर (parent_sb->s_subtype && !sb->s_subtype)
		वापस -ENOMEM;

	fuse_fill_attr_from_inode(&root_attr, parent_fi);
	root = fuse_iget(sb, parent_fi->nodeid, 0, &root_attr, 0, 0);
	/*
	 * This inode is just a duplicate, so it is not looked up and
	 * its nlookup should not be incremented.  fuse_iget() करोes
	 * that, though, so unकरो it here.
	 */
	get_fuse_inode(root)->nlookup--;
	sb->s_d_op = &fuse_dentry_operations;
	sb->s_root = d_make_root(root);
	अगर (!sb->s_root)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक fuse_fill_super_common(काष्ठा super_block *sb, काष्ठा fuse_fs_context *ctx)
अणु
	काष्ठा fuse_dev *fud = शून्य;
	काष्ठा fuse_mount *fm = get_fuse_mount_super(sb);
	काष्ठा fuse_conn *fc = fm->fc;
	काष्ठा inode *root;
	काष्ठा dentry *root_dentry;
	पूर्णांक err;

	err = -EINVAL;
	अगर (sb->s_flags & SB_MANDLOCK)
		जाओ err;

	fuse_sb_शेषs(sb);

	अगर (ctx->is_bdev) अणु
#अगर_घोषित CONFIG_BLOCK
		err = -EINVAL;
		अगर (!sb_set_blocksize(sb, ctx->blksize))
			जाओ err;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		sb->s_blocksize = PAGE_SIZE;
		sb->s_blocksize_bits = PAGE_SHIFT;
	पूर्ण

	sb->s_subtype = ctx->subtype;
	ctx->subtype = शून्य;
	अगर (IS_ENABLED(CONFIG_FUSE_DAX)) अणु
		err = fuse_dax_conn_alloc(fc, ctx->dax_dev);
		अगर (err)
			जाओ err;
	पूर्ण

	अगर (ctx->fudptr) अणु
		err = -ENOMEM;
		fud = fuse_dev_alloc_install(fc);
		अगर (!fud)
			जाओ err_मुक्त_dax;
	पूर्ण

	fc->dev = sb->s_dev;
	fm->sb = sb;
	err = fuse_bdi_init(fc, sb);
	अगर (err)
		जाओ err_dev_मुक्त;

	/* Handle umasking inside the fuse code */
	अगर (sb->s_flags & SB_POSIXACL)
		fc->करोnt_mask = 1;
	sb->s_flags |= SB_POSIXACL;

	fc->शेष_permissions = ctx->शेष_permissions;
	fc->allow_other = ctx->allow_other;
	fc->user_id = ctx->user_id;
	fc->group_id = ctx->group_id;
	fc->legacy_opts_show = ctx->legacy_opts_show;
	fc->max_पढ़ो = max_t(अचिन्हित पूर्णांक, 4096, ctx->max_पढ़ो);
	fc->destroy = ctx->destroy;
	fc->no_control = ctx->no_control;
	fc->no_क्रमce_umount = ctx->no_क्रमce_umount;

	err = -ENOMEM;
	root = fuse_get_root_inode(sb, ctx->rooपंचांगode);
	sb->s_d_op = &fuse_root_dentry_operations;
	root_dentry = d_make_root(root);
	अगर (!root_dentry)
		जाओ err_dev_मुक्त;
	/* Root dentry करोesn't have .d_revalidate */
	sb->s_d_op = &fuse_dentry_operations;

	mutex_lock(&fuse_mutex);
	err = -EINVAL;
	अगर (ctx->fudptr && *ctx->fudptr)
		जाओ err_unlock;

	err = fuse_ctl_add_conn(fc);
	अगर (err)
		जाओ err_unlock;

	list_add_tail(&fc->entry, &fuse_conn_list);
	sb->s_root = root_dentry;
	अगर (ctx->fudptr)
		*ctx->fudptr = fud;
	mutex_unlock(&fuse_mutex);
	वापस 0;

 err_unlock:
	mutex_unlock(&fuse_mutex);
	dput(root_dentry);
 err_dev_मुक्त:
	अगर (fud)
		fuse_dev_मुक्त(fud);
 err_मुक्त_dax:
	अगर (IS_ENABLED(CONFIG_FUSE_DAX))
		fuse_dax_conn_मुक्त(fc);
 err:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fuse_fill_super_common);

अटल पूर्णांक fuse_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fsc)
अणु
	काष्ठा fuse_fs_context *ctx = fsc->fs_निजी;
	काष्ठा file *file;
	पूर्णांक err;
	काष्ठा fuse_conn *fc;
	काष्ठा fuse_mount *fm;

	err = -EINVAL;
	file = fget(ctx->fd);
	अगर (!file)
		जाओ err;

	/*
	 * Require mount to happen from the same user namespace which
	 * खोलोed /dev/fuse to prevent potential attacks.
	 */
	अगर ((file->f_op != &fuse_dev_operations) ||
	    (file->f_cred->user_ns != sb->s_user_ns))
		जाओ err_fput;
	ctx->fudptr = &file->निजी_data;

	fc = kदो_स्मृति(माप(*fc), GFP_KERNEL);
	err = -ENOMEM;
	अगर (!fc)
		जाओ err_fput;

	fm = kzalloc(माप(*fm), GFP_KERNEL);
	अगर (!fm) अणु
		kमुक्त(fc);
		जाओ err_fput;
	पूर्ण

	fuse_conn_init(fc, fm, sb->s_user_ns, &fuse_dev_fiq_ops, शून्य);
	fc->release = fuse_मुक्त_conn;

	sb->s_fs_info = fm;

	err = fuse_fill_super_common(sb, ctx);
	अगर (err)
		जाओ err_put_conn;
	/*
	 * atomic_dec_and_test() in fput() provides the necessary
	 * memory barrier क्रम file->निजी_data to be visible on all
	 * CPUs after this
	 */
	fput(file);
	fuse_send_init(get_fuse_mount_super(sb));
	वापस 0;

 err_put_conn:
	fuse_conn_put(fc);
	kमुक्त(fm);
	sb->s_fs_info = शून्य;
 err_fput:
	fput(file);
 err:
	वापस err;
पूर्ण

अटल पूर्णांक fuse_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा fuse_fs_context *ctx = fc->fs_निजी;

	अगर (!ctx->fd_present || !ctx->rooपंचांगode_present ||
	    !ctx->user_id_present || !ctx->group_id_present)
		वापस -EINVAL;

#अगर_घोषित CONFIG_BLOCK
	अगर (ctx->is_bdev)
		वापस get_tree_bdev(fc, fuse_fill_super);
#पूर्ण_अगर

	वापस get_tree_nodev(fc, fuse_fill_super);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations fuse_context_ops = अणु
	.मुक्त		= fuse_मुक्त_fc,
	.parse_param	= fuse_parse_param,
	.reconfigure	= fuse_reconfigure,
	.get_tree	= fuse_get_tree,
पूर्ण;

/*
 * Set up the fileप्रणाली mount context.
 */
अटल पूर्णांक fuse_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा fuse_fs_context *ctx;

	ctx = kzalloc(माप(काष्ठा fuse_fs_context), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->max_पढ़ो = ~0;
	ctx->blksize = FUSE_DEFAULT_BLKSIZE;
	ctx->legacy_opts_show = true;

#अगर_घोषित CONFIG_BLOCK
	अगर (fc->fs_type == &fuseblk_fs_type) अणु
		ctx->is_bdev = true;
		ctx->destroy = true;
	पूर्ण
#पूर्ण_अगर

	fc->fs_निजी = ctx;
	fc->ops = &fuse_context_ops;
	वापस 0;
पूर्ण

bool fuse_mount_हटाओ(काष्ठा fuse_mount *fm)
अणु
	काष्ठा fuse_conn *fc = fm->fc;
	bool last = false;

	करोwn_ग_लिखो(&fc->समाप्तsb);
	list_del_init(&fm->fc_entry);
	अगर (list_empty(&fc->mounts))
		last = true;
	up_ग_लिखो(&fc->समाप्तsb);

	वापस last;
पूर्ण
EXPORT_SYMBOL_GPL(fuse_mount_हटाओ);

व्योम fuse_conn_destroy(काष्ठा fuse_mount *fm)
अणु
	काष्ठा fuse_conn *fc = fm->fc;

	अगर (fc->destroy)
		fuse_send_destroy(fm);

	fuse_पात_conn(fc);
	fuse_रुको_पातed(fc);

	अगर (!list_empty(&fc->entry)) अणु
		mutex_lock(&fuse_mutex);
		list_del(&fc->entry);
		fuse_ctl_हटाओ_conn(fc);
		mutex_unlock(&fuse_mutex);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fuse_conn_destroy);

अटल व्योम fuse_sb_destroy(काष्ठा super_block *sb)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount_super(sb);
	bool last;

	अगर (fm) अणु
		last = fuse_mount_हटाओ(fm);
		अगर (last)
			fuse_conn_destroy(fm);
	पूर्ण
पूर्ण

अटल व्योम fuse_समाप्त_sb_anon(काष्ठा super_block *sb)
अणु
	fuse_sb_destroy(sb);
	समाप्त_anon_super(sb);
पूर्ण

अटल काष्ठा file_प्रणाली_type fuse_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "fuse",
	.fs_flags	= FS_HAS_SUBTYPE | FS_USERNS_MOUNT,
	.init_fs_context = fuse_init_fs_context,
	.parameters	= fuse_fs_parameters,
	.समाप्त_sb	= fuse_समाप्त_sb_anon,
पूर्ण;
MODULE_ALIAS_FS("fuse");

#अगर_घोषित CONFIG_BLOCK
अटल व्योम fuse_समाप्त_sb_blk(काष्ठा super_block *sb)
अणु
	fuse_sb_destroy(sb);
	समाप्त_block_super(sb);
पूर्ण

अटल काष्ठा file_प्रणाली_type fuseblk_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "fuseblk",
	.init_fs_context = fuse_init_fs_context,
	.parameters	= fuse_fs_parameters,
	.समाप्त_sb	= fuse_समाप्त_sb_blk,
	.fs_flags	= FS_REQUIRES_DEV | FS_HAS_SUBTYPE,
पूर्ण;
MODULE_ALIAS_FS("fuseblk");

अटल अंतरभूत पूर्णांक रेजिस्टर_fuseblk(व्योम)
अणु
	वापस रेजिस्टर_fileप्रणाली(&fuseblk_fs_type);
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_fuseblk(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&fuseblk_fs_type);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक रेजिस्टर_fuseblk(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_fuseblk(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम fuse_inode_init_once(व्योम *foo)
अणु
	काष्ठा inode *inode = foo;

	inode_init_once(inode);
पूर्ण

अटल पूर्णांक __init fuse_fs_init(व्योम)
अणु
	पूर्णांक err;

	fuse_inode_cachep = kmem_cache_create("fuse_inode",
			माप(काष्ठा fuse_inode), 0,
			SLAB_HWCACHE_ALIGN|SLAB_ACCOUNT|SLAB_RECLAIM_ACCOUNT,
			fuse_inode_init_once);
	err = -ENOMEM;
	अगर (!fuse_inode_cachep)
		जाओ out;

	err = रेजिस्टर_fuseblk();
	अगर (err)
		जाओ out2;

	err = रेजिस्टर_fileप्रणाली(&fuse_fs_type);
	अगर (err)
		जाओ out3;

	वापस 0;

 out3:
	unरेजिस्टर_fuseblk();
 out2:
	kmem_cache_destroy(fuse_inode_cachep);
 out:
	वापस err;
पूर्ण

अटल व्योम fuse_fs_cleanup(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&fuse_fs_type);
	unरेजिस्टर_fuseblk();

	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(fuse_inode_cachep);
पूर्ण

अटल काष्ठा kobject *fuse_kobj;

अटल पूर्णांक fuse_sysfs_init(व्योम)
अणु
	पूर्णांक err;

	fuse_kobj = kobject_create_and_add("fuse", fs_kobj);
	अगर (!fuse_kobj) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	err = sysfs_create_mount_poपूर्णांक(fuse_kobj, "connections");
	अगर (err)
		जाओ out_fuse_unरेजिस्टर;

	वापस 0;

 out_fuse_unरेजिस्टर:
	kobject_put(fuse_kobj);
 out_err:
	वापस err;
पूर्ण

अटल व्योम fuse_sysfs_cleanup(व्योम)
अणु
	sysfs_हटाओ_mount_poपूर्णांक(fuse_kobj, "connections");
	kobject_put(fuse_kobj);
पूर्ण

अटल पूर्णांक __init fuse_init(व्योम)
अणु
	पूर्णांक res;

	pr_info("init (API version %i.%i)\n",
		FUSE_KERNEL_VERSION, FUSE_KERNEL_MINOR_VERSION);

	INIT_LIST_HEAD(&fuse_conn_list);
	res = fuse_fs_init();
	अगर (res)
		जाओ err;

	res = fuse_dev_init();
	अगर (res)
		जाओ err_fs_cleanup;

	res = fuse_sysfs_init();
	अगर (res)
		जाओ err_dev_cleanup;

	res = fuse_ctl_init();
	अगर (res)
		जाओ err_sysfs_cleanup;

	sanitize_global_limit(&max_user_bgreq);
	sanitize_global_limit(&max_user_congthresh);

	वापस 0;

 err_sysfs_cleanup:
	fuse_sysfs_cleanup();
 err_dev_cleanup:
	fuse_dev_cleanup();
 err_fs_cleanup:
	fuse_fs_cleanup();
 err:
	वापस res;
पूर्ण

अटल व्योम __निकास fuse_निकास(व्योम)
अणु
	pr_debug("exit\n");

	fuse_ctl_cleanup();
	fuse_sysfs_cleanup();
	fuse_fs_cleanup();
	fuse_dev_cleanup();
पूर्ण

module_init(fuse_init);
module_निकास(fuse_निकास);
