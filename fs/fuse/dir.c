<शैली गुरु>
/*
  FUSE: Fileप्रणाली in Userspace
  Copyright (C) 2001-2008  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.
*/

#समावेश "fuse_i.h"

#समावेश <linux/pagemap.h>
#समावेश <linux/file.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/sched.h>
#समावेश <linux/namei.h>
#समावेश <linux/slab.h>
#समावेश <linux/xattr.h>
#समावेश <linux/iversion.h>
#समावेश <linux/posix_acl.h>

अटल व्योम fuse_advise_use_सूची_पढ़ोplus(काष्ठा inode *dir)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(dir);

	set_bit(FUSE_I_ADVISE_RDPLUS, &fi->state);
पूर्ण

#अगर BITS_PER_LONG >= 64
अटल अंतरभूत व्योम __fuse_dentry_समय_रखो(काष्ठा dentry *entry, u64 समय)
अणु
	entry->d_fsdata = (व्योम *) समय;
पूर्ण

अटल अंतरभूत u64 fuse_dentry_समय(स्थिर काष्ठा dentry *entry)
अणु
	वापस (u64)entry->d_fsdata;
पूर्ण

#अन्यथा
जोड़ fuse_dentry अणु
	u64 समय;
	काष्ठा rcu_head rcu;
पूर्ण;

अटल अंतरभूत व्योम __fuse_dentry_समय_रखो(काष्ठा dentry *dentry, u64 समय)
अणु
	((जोड़ fuse_dentry *) dentry->d_fsdata)->समय = समय;
पूर्ण

अटल अंतरभूत u64 fuse_dentry_समय(स्थिर काष्ठा dentry *entry)
अणु
	वापस ((जोड़ fuse_dentry *) entry->d_fsdata)->समय;
पूर्ण
#पूर्ण_अगर

अटल व्योम fuse_dentry_समय_रखो(काष्ठा dentry *dentry, u64 समय)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn_super(dentry->d_sb);
	bool delete = !समय && fc->delete_stale;
	/*
	 * Mess with DCACHE_OP_DELETE because dput() will be faster without it.
	 * Don't care about races, either way it's just an optimization
	 */
	अगर ((!delete && (dentry->d_flags & DCACHE_OP_DELETE)) ||
	    (delete && !(dentry->d_flags & DCACHE_OP_DELETE))) अणु
		spin_lock(&dentry->d_lock);
		अगर (!delete)
			dentry->d_flags &= ~DCACHE_OP_DELETE;
		अन्यथा
			dentry->d_flags |= DCACHE_OP_DELETE;
		spin_unlock(&dentry->d_lock);
	पूर्ण

	__fuse_dentry_समय_रखो(dentry, समय);
पूर्ण

/*
 * FUSE caches dentries and attributes with separate समयout.  The
 * समय in jअगरfies until the dentry/attributes are valid is stored in
 * dentry->d_fsdata and fuse_inode->i_समय respectively.
 */

/*
 * Calculate the समय in jअगरfies until a dentry/attributes are valid
 */
अटल u64 समय_प्रकारo_jअगरfies(u64 sec, u32 nsec)
अणु
	अगर (sec || nsec) अणु
		काष्ठा बारpec64 ts = अणु
			sec,
			min_t(u32, nsec, NSEC_PER_SEC - 1)
		पूर्ण;

		वापस get_jअगरfies_64() + बारpec64_to_jअगरfies(&ts);
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

/*
 * Set dentry and possibly attribute समयouts from the lookup/mk*
 * replies
 */
व्योम fuse_change_entry_समयout(काष्ठा dentry *entry, काष्ठा fuse_entry_out *o)
अणु
	fuse_dentry_समय_रखो(entry,
		समय_प्रकारo_jअगरfies(o->entry_valid, o->entry_valid_nsec));
पूर्ण

अटल u64 attr_समयout(काष्ठा fuse_attr_out *o)
अणु
	वापस समय_प्रकारo_jअगरfies(o->attr_valid, o->attr_valid_nsec);
पूर्ण

u64 entry_attr_समयout(काष्ठा fuse_entry_out *o)
अणु
	वापस समय_प्रकारo_jअगरfies(o->attr_valid, o->attr_valid_nsec);
पूर्ण

अटल व्योम fuse_invalidate_attr_mask(काष्ठा inode *inode, u32 mask)
अणु
	set_mask_bits(&get_fuse_inode(inode)->inval_mask, 0, mask);
पूर्ण

/*
 * Mark the attributes as stale, so that at the next call to
 * ->getattr() they will be fetched from userspace
 */
व्योम fuse_invalidate_attr(काष्ठा inode *inode)
अणु
	fuse_invalidate_attr_mask(inode, STATX_BASIC_STATS);
पूर्ण

अटल व्योम fuse_dir_changed(काष्ठा inode *dir)
अणु
	fuse_invalidate_attr(dir);
	inode_maybe_inc_iversion(dir, false);
पूर्ण

/**
 * Mark the attributes as stale due to an aसमय change.  Aव्योम the invalidate अगर
 * aसमय is not used.
 */
व्योम fuse_invalidate_aसमय(काष्ठा inode *inode)
अणु
	अगर (!IS_RDONLY(inode))
		fuse_invalidate_attr_mask(inode, STATX_ATIME);
पूर्ण

/*
 * Just mark the entry as stale, so that a next attempt to look it up
 * will result in a new lookup call to userspace
 *
 * This is called when a dentry is about to become negative and the
 * समयout is unknown (unlink, सूची_हटाओ, नाम and in some हालs
 * lookup)
 */
व्योम fuse_invalidate_entry_cache(काष्ठा dentry *entry)
अणु
	fuse_dentry_समय_रखो(entry, 0);
पूर्ण

/*
 * Same as fuse_invalidate_entry_cache(), but also try to हटाओ the
 * dentry from the hash
 */
अटल व्योम fuse_invalidate_entry(काष्ठा dentry *entry)
अणु
	d_invalidate(entry);
	fuse_invalidate_entry_cache(entry);
पूर्ण

अटल व्योम fuse_lookup_init(काष्ठा fuse_conn *fc, काष्ठा fuse_args *args,
			     u64 nodeid, स्थिर काष्ठा qstr *name,
			     काष्ठा fuse_entry_out *outarg)
अणु
	स_रखो(outarg, 0, माप(काष्ठा fuse_entry_out));
	args->opcode = FUSE_LOOKUP;
	args->nodeid = nodeid;
	args->in_numargs = 1;
	args->in_args[0].size = name->len + 1;
	args->in_args[0].value = name->name;
	args->out_numargs = 1;
	args->out_args[0].size = माप(काष्ठा fuse_entry_out);
	args->out_args[0].value = outarg;
पूर्ण

/*
 * Check whether the dentry is still valid
 *
 * If the entry validity समयout has expired and the dentry is
 * positive, try to reकरो the lookup.  If the lookup results in a
 * dअगरferent inode, then let the VFS invalidate the dentry and reकरो
 * the lookup once more.  If the lookup results in the same inode,
 * then refresh the attributes, समयouts and mark the dentry valid.
 */
अटल पूर्णांक fuse_dentry_revalidate(काष्ठा dentry *entry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	काष्ठा dentry *parent;
	काष्ठा fuse_mount *fm;
	काष्ठा fuse_inode *fi;
	पूर्णांक ret;

	inode = d_inode_rcu(entry);
	अगर (inode && fuse_is_bad(inode))
		जाओ invalid;
	अन्यथा अगर (समय_beक्रमe64(fuse_dentry_समय(entry), get_jअगरfies_64()) ||
		 (flags & (LOOKUP_EXCL | LOOKUP_REVAL))) अणु
		काष्ठा fuse_entry_out outarg;
		FUSE_ARGS(args);
		काष्ठा fuse_क्रमget_link *क्रमget;
		u64 attr_version;

		/* For negative dentries, always करो a fresh lookup */
		अगर (!inode)
			जाओ invalid;

		ret = -ECHILD;
		अगर (flags & LOOKUP_RCU)
			जाओ out;

		fm = get_fuse_mount(inode);

		क्रमget = fuse_alloc_क्रमget();
		ret = -ENOMEM;
		अगर (!क्रमget)
			जाओ out;

		attr_version = fuse_get_attr_version(fm->fc);

		parent = dget_parent(entry);
		fuse_lookup_init(fm->fc, &args, get_node_id(d_inode(parent)),
				 &entry->d_name, &outarg);
		ret = fuse_simple_request(fm, &args);
		dput(parent);
		/* Zero nodeid is same as -ENOENT */
		अगर (!ret && !outarg.nodeid)
			ret = -ENOENT;
		अगर (!ret) अणु
			fi = get_fuse_inode(inode);
			अगर (outarg.nodeid != get_node_id(inode) ||
			    (bool) IS_AUTOMOUNT(inode) != (bool) (outarg.attr.flags & FUSE_ATTR_SUBMOUNT)) अणु
				fuse_queue_क्रमget(fm->fc, क्रमget,
						  outarg.nodeid, 1);
				जाओ invalid;
			पूर्ण
			spin_lock(&fi->lock);
			fi->nlookup++;
			spin_unlock(&fi->lock);
		पूर्ण
		kमुक्त(क्रमget);
		अगर (ret == -ENOMEM)
			जाओ out;
		अगर (ret || fuse_invalid_attr(&outarg.attr) ||
		    inode_wrong_type(inode, outarg.attr.mode))
			जाओ invalid;

		क्रमget_all_cached_acls(inode);
		fuse_change_attributes(inode, &outarg.attr,
				       entry_attr_समयout(&outarg),
				       attr_version);
		fuse_change_entry_समयout(entry, &outarg);
	पूर्ण अन्यथा अगर (inode) अणु
		fi = get_fuse_inode(inode);
		अगर (flags & LOOKUP_RCU) अणु
			अगर (test_bit(FUSE_I_INIT_RDPLUS, &fi->state))
				वापस -ECHILD;
		पूर्ण अन्यथा अगर (test_and_clear_bit(FUSE_I_INIT_RDPLUS, &fi->state)) अणु
			parent = dget_parent(entry);
			fuse_advise_use_सूची_पढ़ोplus(d_inode(parent));
			dput(parent);
		पूर्ण
	पूर्ण
	ret = 1;
out:
	वापस ret;

invalid:
	ret = 0;
	जाओ out;
पूर्ण

#अगर BITS_PER_LONG < 64
अटल पूर्णांक fuse_dentry_init(काष्ठा dentry *dentry)
अणु
	dentry->d_fsdata = kzalloc(माप(जोड़ fuse_dentry),
				   GFP_KERNEL_ACCOUNT | __GFP_RECLAIMABLE);

	वापस dentry->d_fsdata ? 0 : -ENOMEM;
पूर्ण
अटल व्योम fuse_dentry_release(काष्ठा dentry *dentry)
अणु
	जोड़ fuse_dentry *fd = dentry->d_fsdata;

	kमुक्त_rcu(fd, rcu);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक fuse_dentry_delete(स्थिर काष्ठा dentry *dentry)
अणु
	वापस समय_beक्रमe64(fuse_dentry_समय(dentry), get_jअगरfies_64());
पूर्ण

/*
 * Create a fuse_mount object with a new superblock (with path->dentry
 * as the root), and वापस that mount so it can be स्वतः-mounted on
 * @path.
 */
अटल काष्ठा vfsmount *fuse_dentry_स्वतःmount(काष्ठा path *path)
अणु
	काष्ठा fs_context *fsc;
	काष्ठा fuse_mount *parent_fm = get_fuse_mount_super(path->mnt->mnt_sb);
	काष्ठा fuse_conn *fc = parent_fm->fc;
	काष्ठा fuse_mount *fm;
	काष्ठा vfsmount *mnt;
	काष्ठा fuse_inode *mp_fi = get_fuse_inode(d_inode(path->dentry));
	काष्ठा super_block *sb;
	पूर्णांक err;

	fsc = fs_context_क्रम_submount(path->mnt->mnt_sb->s_type, path->dentry);
	अगर (IS_ERR(fsc)) अणु
		err = PTR_ERR(fsc);
		जाओ out;
	पूर्ण

	err = -ENOMEM;
	fm = kzalloc(माप(काष्ठा fuse_mount), GFP_KERNEL);
	अगर (!fm)
		जाओ out_put_fsc;

	fsc->s_fs_info = fm;
	sb = sget_fc(fsc, शून्य, set_anon_super_fc);
	अगर (IS_ERR(sb)) अणु
		err = PTR_ERR(sb);
		kमुक्त(fm);
		जाओ out_put_fsc;
	पूर्ण
	fm->fc = fuse_conn_get(fc);

	/* Initialize superblock, making @mp_fi its root */
	err = fuse_fill_super_submount(sb, mp_fi);
	अगर (err)
		जाओ out_put_sb;

	sb->s_flags |= SB_ACTIVE;
	fsc->root = dget(sb->s_root);
	/* We are करोne configuring the superblock, so unlock it */
	up_ग_लिखो(&sb->s_umount);

	करोwn_ग_लिखो(&fc->समाप्तsb);
	list_add_tail(&fm->fc_entry, &fc->mounts);
	up_ग_लिखो(&fc->समाप्तsb);

	/* Create the submount */
	mnt = vfs_create_mount(fsc);
	अगर (IS_ERR(mnt)) अणु
		err = PTR_ERR(mnt);
		जाओ out_put_fsc;
	पूर्ण
	mntget(mnt);
	put_fs_context(fsc);
	वापस mnt;

out_put_sb:
	/*
	 * Only jump here when fsc->root is शून्य and sb is still locked
	 * (otherwise put_fs_context() will put the superblock)
	 */
	deactivate_locked_super(sb);
out_put_fsc:
	put_fs_context(fsc);
out:
	वापस ERR_PTR(err);
पूर्ण

स्थिर काष्ठा dentry_operations fuse_dentry_operations = अणु
	.d_revalidate	= fuse_dentry_revalidate,
	.d_delete	= fuse_dentry_delete,
#अगर BITS_PER_LONG < 64
	.d_init		= fuse_dentry_init,
	.d_release	= fuse_dentry_release,
#पूर्ण_अगर
	.d_स्वतःmount	= fuse_dentry_स्वतःmount,
पूर्ण;

स्थिर काष्ठा dentry_operations fuse_root_dentry_operations = अणु
#अगर BITS_PER_LONG < 64
	.d_init		= fuse_dentry_init,
	.d_release	= fuse_dentry_release,
#पूर्ण_अगर
पूर्ण;

पूर्णांक fuse_valid_type(पूर्णांक m)
अणु
	वापस S_ISREG(m) || S_ISसूची(m) || S_ISLNK(m) || S_ISCHR(m) ||
		S_ISBLK(m) || S_ISFIFO(m) || S_ISSOCK(m);
पूर्ण

bool fuse_invalid_attr(काष्ठा fuse_attr *attr)
अणु
	वापस !fuse_valid_type(attr->mode) ||
		attr->size > Lदीर्घ_उच्च;
पूर्ण

पूर्णांक fuse_lookup_name(काष्ठा super_block *sb, u64 nodeid, स्थिर काष्ठा qstr *name,
		     काष्ठा fuse_entry_out *outarg, काष्ठा inode **inode)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount_super(sb);
	FUSE_ARGS(args);
	काष्ठा fuse_क्रमget_link *क्रमget;
	u64 attr_version;
	पूर्णांक err;

	*inode = शून्य;
	err = -ENAMETOOLONG;
	अगर (name->len > FUSE_NAME_MAX)
		जाओ out;


	क्रमget = fuse_alloc_क्रमget();
	err = -ENOMEM;
	अगर (!क्रमget)
		जाओ out;

	attr_version = fuse_get_attr_version(fm->fc);

	fuse_lookup_init(fm->fc, &args, nodeid, name, outarg);
	err = fuse_simple_request(fm, &args);
	/* Zero nodeid is same as -ENOENT, but with valid समयout */
	अगर (err || !outarg->nodeid)
		जाओ out_put_क्रमget;

	err = -EIO;
	अगर (!outarg->nodeid)
		जाओ out_put_क्रमget;
	अगर (fuse_invalid_attr(&outarg->attr))
		जाओ out_put_क्रमget;

	*inode = fuse_iget(sb, outarg->nodeid, outarg->generation,
			   &outarg->attr, entry_attr_समयout(outarg),
			   attr_version);
	err = -ENOMEM;
	अगर (!*inode) अणु
		fuse_queue_क्रमget(fm->fc, क्रमget, outarg->nodeid, 1);
		जाओ out;
	पूर्ण
	err = 0;

 out_put_क्रमget:
	kमुक्त(क्रमget);
 out:
	वापस err;
पूर्ण

अटल काष्ठा dentry *fuse_lookup(काष्ठा inode *dir, काष्ठा dentry *entry,
				  अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;
	काष्ठा fuse_entry_out outarg;
	काष्ठा inode *inode;
	काष्ठा dentry *newent;
	bool outarg_valid = true;
	bool locked;

	अगर (fuse_is_bad(dir))
		वापस ERR_PTR(-EIO);

	locked = fuse_lock_inode(dir);
	err = fuse_lookup_name(dir->i_sb, get_node_id(dir), &entry->d_name,
			       &outarg, &inode);
	fuse_unlock_inode(dir, locked);
	अगर (err == -ENOENT) अणु
		outarg_valid = false;
		err = 0;
	पूर्ण
	अगर (err)
		जाओ out_err;

	err = -EIO;
	अगर (inode && get_node_id(inode) == FUSE_ROOT_ID)
		जाओ out_iput;

	newent = d_splice_alias(inode, entry);
	err = PTR_ERR(newent);
	अगर (IS_ERR(newent))
		जाओ out_err;

	entry = newent ? newent : entry;
	अगर (outarg_valid)
		fuse_change_entry_समयout(entry, &outarg);
	अन्यथा
		fuse_invalidate_entry_cache(entry);

	अगर (inode)
		fuse_advise_use_सूची_पढ़ोplus(dir);
	वापस newent;

 out_iput:
	iput(inode);
 out_err:
	वापस ERR_PTR(err);
पूर्ण

/*
 * Atomic create+खोलो operation
 *
 * If the fileप्रणाली करोesn't support this, then fall back to separate
 * 'mknod' + 'open' requests.
 */
अटल पूर्णांक fuse_create_खोलो(काष्ठा inode *dir, काष्ठा dentry *entry,
			    काष्ठा file *file, अचिन्हित पूर्णांक flags,
			    umode_t mode)
अणु
	पूर्णांक err;
	काष्ठा inode *inode;
	काष्ठा fuse_mount *fm = get_fuse_mount(dir);
	FUSE_ARGS(args);
	काष्ठा fuse_क्रमget_link *क्रमget;
	काष्ठा fuse_create_in inarg;
	काष्ठा fuse_खोलो_out outखोलो;
	काष्ठा fuse_entry_out outentry;
	काष्ठा fuse_inode *fi;
	काष्ठा fuse_file *ff;

	/* Userspace expects S_IFREG in create mode */
	BUG_ON((mode & S_IFMT) != S_IFREG);

	क्रमget = fuse_alloc_क्रमget();
	err = -ENOMEM;
	अगर (!क्रमget)
		जाओ out_err;

	err = -ENOMEM;
	ff = fuse_file_alloc(fm);
	अगर (!ff)
		जाओ out_put_क्रमget_req;

	अगर (!fm->fc->करोnt_mask)
		mode &= ~current_umask();

	flags &= ~O_NOCTTY;
	स_रखो(&inarg, 0, माप(inarg));
	स_रखो(&outentry, 0, माप(outentry));
	inarg.flags = flags;
	inarg.mode = mode;
	inarg.umask = current_umask();

	अगर (fm->fc->handle_समाप्तpriv_v2 && (flags & O_TRUNC) &&
	    !(flags & O_EXCL) && !capable(CAP_FSETID)) अणु
		inarg.खोलो_flags |= FUSE_OPEN_KILL_SUIDGID;
	पूर्ण

	args.opcode = FUSE_CREATE;
	args.nodeid = get_node_id(dir);
	args.in_numargs = 2;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.in_args[1].size = entry->d_name.len + 1;
	args.in_args[1].value = entry->d_name.name;
	args.out_numargs = 2;
	args.out_args[0].size = माप(outentry);
	args.out_args[0].value = &outentry;
	args.out_args[1].size = माप(outखोलो);
	args.out_args[1].value = &outखोलो;
	err = fuse_simple_request(fm, &args);
	अगर (err)
		जाओ out_मुक्त_ff;

	err = -EIO;
	अगर (!S_ISREG(outentry.attr.mode) || invalid_nodeid(outentry.nodeid) ||
	    fuse_invalid_attr(&outentry.attr))
		जाओ out_मुक्त_ff;

	ff->fh = outखोलो.fh;
	ff->nodeid = outentry.nodeid;
	ff->खोलो_flags = outखोलो.खोलो_flags;
	inode = fuse_iget(dir->i_sb, outentry.nodeid, outentry.generation,
			  &outentry.attr, entry_attr_समयout(&outentry), 0);
	अगर (!inode) अणु
		flags &= ~(O_CREAT | O_EXCL | O_TRUNC);
		fuse_sync_release(शून्य, ff, flags);
		fuse_queue_क्रमget(fm->fc, क्रमget, outentry.nodeid, 1);
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण
	kमुक्त(क्रमget);
	d_instantiate(entry, inode);
	fuse_change_entry_समयout(entry, &outentry);
	fuse_dir_changed(dir);
	err = finish_खोलो(file, entry, generic_file_खोलो);
	अगर (err) अणु
		fi = get_fuse_inode(inode);
		fuse_sync_release(fi, ff, flags);
	पूर्ण अन्यथा अणु
		file->निजी_data = ff;
		fuse_finish_खोलो(inode, file);
	पूर्ण
	वापस err;

out_मुक्त_ff:
	fuse_file_मुक्त(ff);
out_put_क्रमget_req:
	kमुक्त(क्रमget);
out_err:
	वापस err;
पूर्ण

अटल पूर्णांक fuse_mknod(काष्ठा user_namespace *, काष्ठा inode *, काष्ठा dentry *,
		      umode_t, dev_t);
अटल पूर्णांक fuse_atomic_खोलो(काष्ठा inode *dir, काष्ठा dentry *entry,
			    काष्ठा file *file, अचिन्हित flags,
			    umode_t mode)
अणु
	पूर्णांक err;
	काष्ठा fuse_conn *fc = get_fuse_conn(dir);
	काष्ठा dentry *res = शून्य;

	अगर (fuse_is_bad(dir))
		वापस -EIO;

	अगर (d_in_lookup(entry)) अणु
		res = fuse_lookup(dir, entry, 0);
		अगर (IS_ERR(res))
			वापस PTR_ERR(res);

		अगर (res)
			entry = res;
	पूर्ण

	अगर (!(flags & O_CREAT) || d_really_is_positive(entry))
		जाओ no_खोलो;

	/* Only creates */
	file->f_mode |= FMODE_CREATED;

	अगर (fc->no_create)
		जाओ mknod;

	err = fuse_create_खोलो(dir, entry, file, flags, mode);
	अगर (err == -ENOSYS) अणु
		fc->no_create = 1;
		जाओ mknod;
	पूर्ण
out_dput:
	dput(res);
	वापस err;

mknod:
	err = fuse_mknod(&init_user_ns, dir, entry, mode, 0);
	अगर (err)
		जाओ out_dput;
no_खोलो:
	वापस finish_no_खोलो(file, res);
पूर्ण

/*
 * Code shared between mknod, सूची_गढ़ो, symlink and link
 */
अटल पूर्णांक create_new_entry(काष्ठा fuse_mount *fm, काष्ठा fuse_args *args,
			    काष्ठा inode *dir, काष्ठा dentry *entry,
			    umode_t mode)
अणु
	काष्ठा fuse_entry_out outarg;
	काष्ठा inode *inode;
	काष्ठा dentry *d;
	पूर्णांक err;
	काष्ठा fuse_क्रमget_link *क्रमget;

	अगर (fuse_is_bad(dir))
		वापस -EIO;

	क्रमget = fuse_alloc_क्रमget();
	अगर (!क्रमget)
		वापस -ENOMEM;

	स_रखो(&outarg, 0, माप(outarg));
	args->nodeid = get_node_id(dir);
	args->out_numargs = 1;
	args->out_args[0].size = माप(outarg);
	args->out_args[0].value = &outarg;
	err = fuse_simple_request(fm, args);
	अगर (err)
		जाओ out_put_क्रमget_req;

	err = -EIO;
	अगर (invalid_nodeid(outarg.nodeid) || fuse_invalid_attr(&outarg.attr))
		जाओ out_put_क्रमget_req;

	अगर ((outarg.attr.mode ^ mode) & S_IFMT)
		जाओ out_put_क्रमget_req;

	inode = fuse_iget(dir->i_sb, outarg.nodeid, outarg.generation,
			  &outarg.attr, entry_attr_समयout(&outarg), 0);
	अगर (!inode) अणु
		fuse_queue_क्रमget(fm->fc, क्रमget, outarg.nodeid, 1);
		वापस -ENOMEM;
	पूर्ण
	kमुक्त(क्रमget);

	d_drop(entry);
	d = d_splice_alias(inode, entry);
	अगर (IS_ERR(d))
		वापस PTR_ERR(d);

	अगर (d) अणु
		fuse_change_entry_समयout(d, &outarg);
		dput(d);
	पूर्ण अन्यथा अणु
		fuse_change_entry_समयout(entry, &outarg);
	पूर्ण
	fuse_dir_changed(dir);
	वापस 0;

 out_put_क्रमget_req:
	kमुक्त(क्रमget);
	वापस err;
पूर्ण

अटल पूर्णांक fuse_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *entry, umode_t mode, dev_t rdev)
अणु
	काष्ठा fuse_mknod_in inarg;
	काष्ठा fuse_mount *fm = get_fuse_mount(dir);
	FUSE_ARGS(args);

	अगर (!fm->fc->करोnt_mask)
		mode &= ~current_umask();

	स_रखो(&inarg, 0, माप(inarg));
	inarg.mode = mode;
	inarg.rdev = new_encode_dev(rdev);
	inarg.umask = current_umask();
	args.opcode = FUSE_MKNOD;
	args.in_numargs = 2;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.in_args[1].size = entry->d_name.len + 1;
	args.in_args[1].value = entry->d_name.name;
	वापस create_new_entry(fm, &args, dir, entry, mode);
पूर्ण

अटल पूर्णांक fuse_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *entry, umode_t mode, bool excl)
अणु
	वापस fuse_mknod(&init_user_ns, dir, entry, mode, 0);
पूर्ण

अटल पूर्णांक fuse_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *entry, umode_t mode)
अणु
	काष्ठा fuse_सूची_गढ़ो_in inarg;
	काष्ठा fuse_mount *fm = get_fuse_mount(dir);
	FUSE_ARGS(args);

	अगर (!fm->fc->करोnt_mask)
		mode &= ~current_umask();

	स_रखो(&inarg, 0, माप(inarg));
	inarg.mode = mode;
	inarg.umask = current_umask();
	args.opcode = FUSE_MKसूची;
	args.in_numargs = 2;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.in_args[1].size = entry->d_name.len + 1;
	args.in_args[1].value = entry->d_name.name;
	वापस create_new_entry(fm, &args, dir, entry, S_IFसूची);
पूर्ण

अटल पूर्णांक fuse_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *entry, स्थिर अक्षर *link)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount(dir);
	अचिन्हित len = म_माप(link) + 1;
	FUSE_ARGS(args);

	args.opcode = FUSE_SYMLINK;
	args.in_numargs = 2;
	args.in_args[0].size = entry->d_name.len + 1;
	args.in_args[0].value = entry->d_name.name;
	args.in_args[1].size = len;
	args.in_args[1].value = link;
	वापस create_new_entry(fm, &args, dir, entry, S_IFLNK);
पूर्ण

व्योम fuse_update_स_समय(काष्ठा inode *inode)
अणु
	अगर (!IS_NOCMTIME(inode)) अणु
		inode->i_स_समय = current_समय(inode);
		mark_inode_dirty_sync(inode);
	पूर्ण
पूर्ण

अटल पूर्णांक fuse_unlink(काष्ठा inode *dir, काष्ठा dentry *entry)
अणु
	पूर्णांक err;
	काष्ठा fuse_mount *fm = get_fuse_mount(dir);
	FUSE_ARGS(args);

	अगर (fuse_is_bad(dir))
		वापस -EIO;

	args.opcode = FUSE_UNLINK;
	args.nodeid = get_node_id(dir);
	args.in_numargs = 1;
	args.in_args[0].size = entry->d_name.len + 1;
	args.in_args[0].value = entry->d_name.name;
	err = fuse_simple_request(fm, &args);
	अगर (!err) अणु
		काष्ठा inode *inode = d_inode(entry);
		काष्ठा fuse_inode *fi = get_fuse_inode(inode);

		spin_lock(&fi->lock);
		fi->attr_version = atomic64_inc_वापस(&fm->fc->attr_version);
		/*
		 * If i_nlink == 0 then unlink करोesn't make sense, yet this can
		 * happen अगर userspace fileप्रणाली is careless.  It would be
		 * dअगरficult to enक्रमce correct nlink usage so just ignore this
		 * condition here
		 */
		अगर (inode->i_nlink > 0)
			drop_nlink(inode);
		spin_unlock(&fi->lock);
		fuse_invalidate_attr(inode);
		fuse_dir_changed(dir);
		fuse_invalidate_entry_cache(entry);
		fuse_update_स_समय(inode);
	पूर्ण अन्यथा अगर (err == -EINTR)
		fuse_invalidate_entry(entry);
	वापस err;
पूर्ण

अटल पूर्णांक fuse_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *entry)
अणु
	पूर्णांक err;
	काष्ठा fuse_mount *fm = get_fuse_mount(dir);
	FUSE_ARGS(args);

	अगर (fuse_is_bad(dir))
		वापस -EIO;

	args.opcode = FUSE_RMसूची;
	args.nodeid = get_node_id(dir);
	args.in_numargs = 1;
	args.in_args[0].size = entry->d_name.len + 1;
	args.in_args[0].value = entry->d_name.name;
	err = fuse_simple_request(fm, &args);
	अगर (!err) अणु
		clear_nlink(d_inode(entry));
		fuse_dir_changed(dir);
		fuse_invalidate_entry_cache(entry);
	पूर्ण अन्यथा अगर (err == -EINTR)
		fuse_invalidate_entry(entry);
	वापस err;
पूर्ण

अटल पूर्णांक fuse_नाम_common(काष्ठा inode *olddir, काष्ठा dentry *oldent,
			      काष्ठा inode *newdir, काष्ठा dentry *newent,
			      अचिन्हित पूर्णांक flags, पूर्णांक opcode, माप_प्रकार argsize)
अणु
	पूर्णांक err;
	काष्ठा fuse_नाम2_in inarg;
	काष्ठा fuse_mount *fm = get_fuse_mount(olddir);
	FUSE_ARGS(args);

	स_रखो(&inarg, 0, argsize);
	inarg.newdir = get_node_id(newdir);
	inarg.flags = flags;
	args.opcode = opcode;
	args.nodeid = get_node_id(olddir);
	args.in_numargs = 3;
	args.in_args[0].size = argsize;
	args.in_args[0].value = &inarg;
	args.in_args[1].size = oldent->d_name.len + 1;
	args.in_args[1].value = oldent->d_name.name;
	args.in_args[2].size = newent->d_name.len + 1;
	args.in_args[2].value = newent->d_name.name;
	err = fuse_simple_request(fm, &args);
	अगर (!err) अणु
		/* स_समय changes */
		fuse_invalidate_attr(d_inode(oldent));
		fuse_update_स_समय(d_inode(oldent));

		अगर (flags & RENAME_EXCHANGE) अणु
			fuse_invalidate_attr(d_inode(newent));
			fuse_update_स_समय(d_inode(newent));
		पूर्ण

		fuse_dir_changed(olddir);
		अगर (olddir != newdir)
			fuse_dir_changed(newdir);

		/* newent will end up negative */
		अगर (!(flags & RENAME_EXCHANGE) && d_really_is_positive(newent)) अणु
			fuse_invalidate_attr(d_inode(newent));
			fuse_invalidate_entry_cache(newent);
			fuse_update_स_समय(d_inode(newent));
		पूर्ण
	पूर्ण अन्यथा अगर (err == -EINTR) अणु
		/* If request was पूर्णांकerrupted, DEITY only knows अगर the
		   नाम actually took place.  If the invalidation
		   fails (e.g. some process has CWD under the नामd
		   directory), then there can be inconsistency between
		   the dcache and the real fileप्रणाली.  Tough luck. */
		fuse_invalidate_entry(oldent);
		अगर (d_really_is_positive(newent))
			fuse_invalidate_entry(newent);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक fuse_नाम2(काष्ठा user_namespace *mnt_userns, काष्ठा inode *olddir,
			काष्ठा dentry *oldent, काष्ठा inode *newdir,
			काष्ठा dentry *newent, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(olddir);
	पूर्णांक err;

	अगर (fuse_is_bad(olddir))
		वापस -EIO;

	अगर (flags & ~(RENAME_NOREPLACE | RENAME_EXCHANGE | RENAME_WHITEOUT))
		वापस -EINVAL;

	अगर (flags) अणु
		अगर (fc->no_नाम2 || fc->minor < 23)
			वापस -EINVAL;

		err = fuse_नाम_common(olddir, oldent, newdir, newent, flags,
					 FUSE_RENAME2,
					 माप(काष्ठा fuse_नाम2_in));
		अगर (err == -ENOSYS) अणु
			fc->no_नाम2 = 1;
			err = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = fuse_नाम_common(olddir, oldent, newdir, newent, 0,
					 FUSE_RENAME,
					 माप(काष्ठा fuse_नाम_in));
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक fuse_link(काष्ठा dentry *entry, काष्ठा inode *newdir,
		     काष्ठा dentry *newent)
अणु
	पूर्णांक err;
	काष्ठा fuse_link_in inarg;
	काष्ठा inode *inode = d_inode(entry);
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	FUSE_ARGS(args);

	स_रखो(&inarg, 0, माप(inarg));
	inarg.oldnodeid = get_node_id(inode);
	args.opcode = FUSE_LINK;
	args.in_numargs = 2;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.in_args[1].size = newent->d_name.len + 1;
	args.in_args[1].value = newent->d_name.name;
	err = create_new_entry(fm, &args, newdir, newent, inode->i_mode);
	/* Contrary to "normal" fileप्रणालीs it can happen that link
	   makes two "logical" inodes poपूर्णांक to the same "physical"
	   inode.  We invalidate the attributes of the old one, so it
	   will reflect changes in the backing inode (link count,
	   etc.)
	*/
	अगर (!err) अणु
		काष्ठा fuse_inode *fi = get_fuse_inode(inode);

		spin_lock(&fi->lock);
		fi->attr_version = atomic64_inc_वापस(&fm->fc->attr_version);
		अगर (likely(inode->i_nlink < अच_पूर्णांक_उच्च))
			inc_nlink(inode);
		spin_unlock(&fi->lock);
		fuse_invalidate_attr(inode);
		fuse_update_स_समय(inode);
	पूर्ण अन्यथा अगर (err == -EINTR) अणु
		fuse_invalidate_attr(inode);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम fuse_fillattr(काष्ठा inode *inode, काष्ठा fuse_attr *attr,
			  काष्ठा kstat *stat)
अणु
	अचिन्हित पूर्णांक blkbits;
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);

	/* see the comment in fuse_change_attributes() */
	अगर (fc->ग_लिखोback_cache && S_ISREG(inode->i_mode)) अणु
		attr->size = i_size_पढ़ो(inode);
		attr->mसमय = inode->i_mसमय.tv_sec;
		attr->mसमयnsec = inode->i_mसमय.tv_nsec;
		attr->स_समय = inode->i_स_समय.tv_sec;
		attr->स_समयnsec = inode->i_स_समय.tv_nsec;
	पूर्ण

	stat->dev = inode->i_sb->s_dev;
	stat->ino = attr->ino;
	stat->mode = (inode->i_mode & S_IFMT) | (attr->mode & 07777);
	stat->nlink = attr->nlink;
	stat->uid = make_kuid(fc->user_ns, attr->uid);
	stat->gid = make_kgid(fc->user_ns, attr->gid);
	stat->rdev = inode->i_rdev;
	stat->aसमय.tv_sec = attr->aसमय;
	stat->aसमय.tv_nsec = attr->aसमयnsec;
	stat->mसमय.tv_sec = attr->mसमय;
	stat->mसमय.tv_nsec = attr->mसमयnsec;
	stat->स_समय.tv_sec = attr->स_समय;
	stat->स_समय.tv_nsec = attr->स_समयnsec;
	stat->size = attr->size;
	stat->blocks = attr->blocks;

	अगर (attr->blksize != 0)
		blkbits = ilog2(attr->blksize);
	अन्यथा
		blkbits = inode->i_sb->s_blocksize_bits;

	stat->blksize = 1 << blkbits;
पूर्ण

अटल पूर्णांक fuse_करो_getattr(काष्ठा inode *inode, काष्ठा kstat *stat,
			   काष्ठा file *file)
अणु
	पूर्णांक err;
	काष्ठा fuse_getattr_in inarg;
	काष्ठा fuse_attr_out outarg;
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	FUSE_ARGS(args);
	u64 attr_version;

	attr_version = fuse_get_attr_version(fm->fc);

	स_रखो(&inarg, 0, माप(inarg));
	स_रखो(&outarg, 0, माप(outarg));
	/* Directories have separate file-handle space */
	अगर (file && S_ISREG(inode->i_mode)) अणु
		काष्ठा fuse_file *ff = file->निजी_data;

		inarg.getattr_flags |= FUSE_GETATTR_FH;
		inarg.fh = ff->fh;
	पूर्ण
	args.opcode = FUSE_GETATTR;
	args.nodeid = get_node_id(inode);
	args.in_numargs = 1;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	args.out_numargs = 1;
	args.out_args[0].size = माप(outarg);
	args.out_args[0].value = &outarg;
	err = fuse_simple_request(fm, &args);
	अगर (!err) अणु
		अगर (fuse_invalid_attr(&outarg.attr) ||
		    inode_wrong_type(inode, outarg.attr.mode)) अणु
			fuse_make_bad(inode);
			err = -EIO;
		पूर्ण अन्यथा अणु
			fuse_change_attributes(inode, &outarg.attr,
					       attr_समयout(&outarg),
					       attr_version);
			अगर (stat)
				fuse_fillattr(inode, &outarg.attr, stat);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक fuse_update_get_attr(काष्ठा inode *inode, काष्ठा file *file,
				काष्ठा kstat *stat, u32 request_mask,
				अचिन्हित पूर्णांक flags)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	पूर्णांक err = 0;
	bool sync;

	अगर (flags & AT_STATX_FORCE_SYNC)
		sync = true;
	अन्यथा अगर (flags & AT_STATX_DONT_SYNC)
		sync = false;
	अन्यथा अगर (request_mask & READ_ONCE(fi->inval_mask))
		sync = true;
	अन्यथा
		sync = समय_beक्रमe64(fi->i_समय, get_jअगरfies_64());

	अगर (sync) अणु
		क्रमget_all_cached_acls(inode);
		err = fuse_करो_getattr(inode, stat, file);
	पूर्ण अन्यथा अगर (stat) अणु
		generic_fillattr(&init_user_ns, inode, stat);
		stat->mode = fi->orig_i_mode;
		stat->ino = fi->orig_ino;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक fuse_update_attributes(काष्ठा inode *inode, काष्ठा file *file)
अणु
	/* Do *not* need to get aसमय क्रम पूर्णांकernal purposes */
	वापस fuse_update_get_attr(inode, file, शून्य,
				    STATX_BASIC_STATS & ~STATX_ATIME, 0);
पूर्ण

पूर्णांक fuse_reverse_inval_entry(काष्ठा fuse_conn *fc, u64 parent_nodeid,
			     u64 child_nodeid, काष्ठा qstr *name)
अणु
	पूर्णांक err = -ENOTसूची;
	काष्ठा inode *parent;
	काष्ठा dentry *dir;
	काष्ठा dentry *entry;

	parent = fuse_ilookup(fc, parent_nodeid, शून्य);
	अगर (!parent)
		वापस -ENOENT;

	inode_lock(parent);
	अगर (!S_ISसूची(parent->i_mode))
		जाओ unlock;

	err = -ENOENT;
	dir = d_find_alias(parent);
	अगर (!dir)
		जाओ unlock;

	name->hash = full_name_hash(dir, name->name, name->len);
	entry = d_lookup(dir, name);
	dput(dir);
	अगर (!entry)
		जाओ unlock;

	fuse_dir_changed(parent);
	fuse_invalidate_entry(entry);

	अगर (child_nodeid != 0 && d_really_is_positive(entry)) अणु
		inode_lock(d_inode(entry));
		अगर (get_node_id(d_inode(entry)) != child_nodeid) अणु
			err = -ENOENT;
			जाओ badentry;
		पूर्ण
		अगर (d_mountpoपूर्णांक(entry)) अणु
			err = -EBUSY;
			जाओ badentry;
		पूर्ण
		अगर (d_is_dir(entry)) अणु
			shrink_dcache_parent(entry);
			अगर (!simple_empty(entry)) अणु
				err = -ENOTEMPTY;
				जाओ badentry;
			पूर्ण
			d_inode(entry)->i_flags |= S_DEAD;
		पूर्ण
		करोnt_mount(entry);
		clear_nlink(d_inode(entry));
		err = 0;
 badentry:
		inode_unlock(d_inode(entry));
		अगर (!err)
			d_delete(entry);
	पूर्ण अन्यथा अणु
		err = 0;
	पूर्ण
	dput(entry);

 unlock:
	inode_unlock(parent);
	iput(parent);
	वापस err;
पूर्ण

/*
 * Calling पूर्णांकo a user-controlled fileप्रणाली gives the fileप्रणाली
 * daemon ptrace-like capabilities over the current process.  This
 * means, that the fileप्रणाली daemon is able to record the exact
 * fileप्रणाली operations perक्रमmed, and can also control the behavior
 * of the requester process in otherwise impossible ways.  For example
 * it can delay the operation क्रम arbitrary length of समय allowing
 * DoS against the requester.
 *
 * For this reason only those processes can call पूर्णांकo the fileप्रणाली,
 * क्रम which the owner of the mount has ptrace privilege.  This
 * excludes processes started by other users, suid or sgid processes.
 */
पूर्णांक fuse_allow_current_process(काष्ठा fuse_conn *fc)
अणु
	स्थिर काष्ठा cred *cred;

	अगर (fc->allow_other)
		वापस current_in_userns(fc->user_ns);

	cred = current_cred();
	अगर (uid_eq(cred->euid, fc->user_id) &&
	    uid_eq(cred->suid, fc->user_id) &&
	    uid_eq(cred->uid,  fc->user_id) &&
	    gid_eq(cred->egid, fc->group_id) &&
	    gid_eq(cred->sgid, fc->group_id) &&
	    gid_eq(cred->gid,  fc->group_id))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक fuse_access(काष्ठा inode *inode, पूर्णांक mask)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	FUSE_ARGS(args);
	काष्ठा fuse_access_in inarg;
	पूर्णांक err;

	BUG_ON(mask & MAY_NOT_BLOCK);

	अगर (fm->fc->no_access)
		वापस 0;

	स_रखो(&inarg, 0, माप(inarg));
	inarg.mask = mask & (MAY_READ | MAY_WRITE | MAY_EXEC);
	args.opcode = FUSE_ACCESS;
	args.nodeid = get_node_id(inode);
	args.in_numargs = 1;
	args.in_args[0].size = माप(inarg);
	args.in_args[0].value = &inarg;
	err = fuse_simple_request(fm, &args);
	अगर (err == -ENOSYS) अणु
		fm->fc->no_access = 1;
		err = 0;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक fuse_perm_getattr(काष्ठा inode *inode, पूर्णांक mask)
अणु
	अगर (mask & MAY_NOT_BLOCK)
		वापस -ECHILD;

	क्रमget_all_cached_acls(inode);
	वापस fuse_करो_getattr(inode, शून्य, शून्य);
पूर्ण

/*
 * Check permission.  The two basic access models of FUSE are:
 *
 * 1) Local access checking ('default_permissions' mount option) based
 * on file mode.  This is the plain old disk fileप्रणाली permission
 * modell.
 *
 * 2) "Remote" access checking, where server is responsible क्रम
 * checking permission in each inode operation.  An exception to this
 * is अगर ->permission() was invoked from sys_access() in which हाल an
 * access request is sent.  Execute permission is still checked
 * locally based on file mode.
 */
अटल पूर्णांक fuse_permission(काष्ठा user_namespace *mnt_userns,
			   काष्ठा inode *inode, पूर्णांक mask)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	bool refreshed = false;
	पूर्णांक err = 0;

	अगर (fuse_is_bad(inode))
		वापस -EIO;

	अगर (!fuse_allow_current_process(fc))
		वापस -EACCES;

	/*
	 * If attributes are needed, refresh them beक्रमe proceeding
	 */
	अगर (fc->शेष_permissions ||
	    ((mask & MAY_EXEC) && S_ISREG(inode->i_mode))) अणु
		काष्ठा fuse_inode *fi = get_fuse_inode(inode);
		u32 perm_mask = STATX_MODE | STATX_UID | STATX_GID;

		अगर (perm_mask & READ_ONCE(fi->inval_mask) ||
		    समय_beक्रमe64(fi->i_समय, get_jअगरfies_64())) अणु
			refreshed = true;

			err = fuse_perm_getattr(inode, mask);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (fc->शेष_permissions) अणु
		err = generic_permission(&init_user_ns, inode, mask);

		/* If permission is denied, try to refresh file
		   attributes.  This is also needed, because the root
		   node will at first have no permissions */
		अगर (err == -EACCES && !refreshed) अणु
			err = fuse_perm_getattr(inode, mask);
			अगर (!err)
				err = generic_permission(&init_user_ns,
							 inode, mask);
		पूर्ण

		/* Note: the opposite of the above test करोes not
		   exist.  So अगर permissions are revoked this won't be
		   noticed immediately, only after the attribute
		   समयout has expired */
	पूर्ण अन्यथा अगर (mask & (MAY_ACCESS | MAY_CHसूची)) अणु
		err = fuse_access(inode, mask);
	पूर्ण अन्यथा अगर ((mask & MAY_EXEC) && S_ISREG(inode->i_mode)) अणु
		अगर (!(inode->i_mode & S_IXUGO)) अणु
			अगर (refreshed)
				वापस -EACCES;

			err = fuse_perm_getattr(inode, mask);
			अगर (!err && !(inode->i_mode & S_IXUGO))
				वापस -EACCES;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक fuse_पढ़ोlink_page(काष्ठा inode *inode, काष्ठा page *page)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	काष्ठा fuse_page_desc desc = अणु .length = PAGE_SIZE - 1 पूर्ण;
	काष्ठा fuse_args_pages ap = अणु
		.num_pages = 1,
		.pages = &page,
		.descs = &desc,
	पूर्ण;
	अक्षर *link;
	sमाप_प्रकार res;

	ap.args.opcode = FUSE_READLINK;
	ap.args.nodeid = get_node_id(inode);
	ap.args.out_pages = true;
	ap.args.out_argvar = true;
	ap.args.page_zeroing = true;
	ap.args.out_numargs = 1;
	ap.args.out_args[0].size = desc.length;
	res = fuse_simple_request(fm, &ap.args);

	fuse_invalidate_aसमय(inode);

	अगर (res < 0)
		वापस res;

	अगर (WARN_ON(res >= PAGE_SIZE))
		वापस -EIO;

	link = page_address(page);
	link[res] = '\0';

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *fuse_get_link(काष्ठा dentry *dentry, काष्ठा inode *inode,
				 काष्ठा delayed_call *callback)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा page *page;
	पूर्णांक err;

	err = -EIO;
	अगर (fuse_is_bad(inode))
		जाओ out_err;

	अगर (fc->cache_symlinks)
		वापस page_get_link(dentry, inode, callback);

	err = -ECHILD;
	अगर (!dentry)
		जाओ out_err;

	page = alloc_page(GFP_KERNEL);
	err = -ENOMEM;
	अगर (!page)
		जाओ out_err;

	err = fuse_पढ़ोlink_page(inode, page);
	अगर (err) अणु
		__मुक्त_page(page);
		जाओ out_err;
	पूर्ण

	set_delayed_call(callback, page_put_link, page);

	वापस page_address(page);

out_err:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक fuse_dir_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस fuse_खोलो_common(inode, file, true);
पूर्ण

अटल पूर्णांक fuse_dir_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	fuse_release_common(file, true);

	वापस 0;
पूर्ण

अटल पूर्णांक fuse_dir_fsync(काष्ठा file *file, loff_t start, loff_t end,
			  पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	पूर्णांक err;

	अगर (fuse_is_bad(inode))
		वापस -EIO;

	अगर (fc->no_fsyncdir)
		वापस 0;

	inode_lock(inode);
	err = fuse_fsync_common(file, start, end, datasync, FUSE_FSYNCसूची);
	अगर (err == -ENOSYS) अणु
		fc->no_fsyncdir = 1;
		err = 0;
	पूर्ण
	inode_unlock(inode);

	वापस err;
पूर्ण

अटल दीर्घ fuse_dir_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			    अचिन्हित दीर्घ arg)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(file->f_mapping->host);

	/* FUSE_IOCTL_सूची only supported क्रम API version >= 7.18 */
	अगर (fc->minor < 18)
		वापस -ENOTTY;

	वापस fuse_ioctl_common(file, cmd, arg, FUSE_IOCTL_सूची);
पूर्ण

अटल दीर्घ fuse_dir_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				   अचिन्हित दीर्घ arg)
अणु
	काष्ठा fuse_conn *fc = get_fuse_conn(file->f_mapping->host);

	अगर (fc->minor < 18)
		वापस -ENOTTY;

	वापस fuse_ioctl_common(file, cmd, arg,
				 FUSE_IOCTL_COMPAT | FUSE_IOCTL_सूची);
पूर्ण

अटल bool update_mसमय(अचिन्हित ivalid, bool trust_local_mसमय)
अणु
	/* Always update अगर mसमय is explicitly set  */
	अगर (ivalid & ATTR_MTIME_SET)
		वापस true;

	/* Or अगर kernel i_mसमय is the official one */
	अगर (trust_local_mसमय)
		वापस true;

	/* If it's an open(O_TRUNC) or an ftruncate(), don't update */
	अगर ((ivalid & ATTR_SIZE) && (ivalid & (ATTR_OPEN | ATTR_खाता)))
		वापस false;

	/* In all other हालs update */
	वापस true;
पूर्ण

अटल व्योम iattr_to_fattr(काष्ठा fuse_conn *fc, काष्ठा iattr *iattr,
			   काष्ठा fuse_setattr_in *arg, bool trust_local_cmसमय)
अणु
	अचिन्हित ivalid = iattr->ia_valid;

	अगर (ivalid & ATTR_MODE)
		arg->valid |= FATTR_MODE,   arg->mode = iattr->ia_mode;
	अगर (ivalid & ATTR_UID)
		arg->valid |= FATTR_UID,    arg->uid = from_kuid(fc->user_ns, iattr->ia_uid);
	अगर (ivalid & ATTR_GID)
		arg->valid |= FATTR_GID,    arg->gid = from_kgid(fc->user_ns, iattr->ia_gid);
	अगर (ivalid & ATTR_SIZE)
		arg->valid |= FATTR_SIZE,   arg->size = iattr->ia_size;
	अगर (ivalid & ATTR_ATIME) अणु
		arg->valid |= FATTR_ATIME;
		arg->aसमय = iattr->ia_aसमय.tv_sec;
		arg->aसमयnsec = iattr->ia_aसमय.tv_nsec;
		अगर (!(ivalid & ATTR_ATIME_SET))
			arg->valid |= FATTR_ATIME_NOW;
	पूर्ण
	अगर ((ivalid & ATTR_MTIME) && update_mसमय(ivalid, trust_local_cmसमय)) अणु
		arg->valid |= FATTR_MTIME;
		arg->mसमय = iattr->ia_mसमय.tv_sec;
		arg->mसमयnsec = iattr->ia_mसमय.tv_nsec;
		अगर (!(ivalid & ATTR_MTIME_SET) && !trust_local_cmसमय)
			arg->valid |= FATTR_MTIME_NOW;
	पूर्ण
	अगर ((ivalid & ATTR_CTIME) && trust_local_cmसमय) अणु
		arg->valid |= FATTR_CTIME;
		arg->स_समय = iattr->ia_स_समय.tv_sec;
		arg->स_समयnsec = iattr->ia_स_समय.tv_nsec;
	पूर्ण
पूर्ण

/*
 * Prevent concurrent ग_लिखोpages on inode
 *
 * This is करोne by adding a negative bias to the inode ग_लिखो counter
 * and रुकोing क्रम all pending ग_लिखोs to finish.
 */
व्योम fuse_set_noग_लिखो(काष्ठा inode *inode)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	BUG_ON(!inode_is_locked(inode));

	spin_lock(&fi->lock);
	BUG_ON(fi->ग_लिखोctr < 0);
	fi->ग_लिखोctr += FUSE_NOWRITE;
	spin_unlock(&fi->lock);
	रुको_event(fi->page_रुकोq, fi->ग_लिखोctr == FUSE_NOWRITE);
पूर्ण

/*
 * Allow ग_लिखोpages on inode
 *
 * Remove the bias from the ग_लिखोcounter and send any queued
 * ग_लिखोpages.
 */
अटल व्योम __fuse_release_noग_लिखो(काष्ठा inode *inode)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	BUG_ON(fi->ग_लिखोctr != FUSE_NOWRITE);
	fi->ग_लिखोctr = 0;
	fuse_flush_ग_लिखोpages(inode);
पूर्ण

व्योम fuse_release_noग_लिखो(काष्ठा inode *inode)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	spin_lock(&fi->lock);
	__fuse_release_noग_लिखो(inode);
	spin_unlock(&fi->lock);
पूर्ण

अटल व्योम fuse_setattr_fill(काष्ठा fuse_conn *fc, काष्ठा fuse_args *args,
			      काष्ठा inode *inode,
			      काष्ठा fuse_setattr_in *inarg_p,
			      काष्ठा fuse_attr_out *outarg_p)
अणु
	args->opcode = FUSE_SETATTR;
	args->nodeid = get_node_id(inode);
	args->in_numargs = 1;
	args->in_args[0].size = माप(*inarg_p);
	args->in_args[0].value = inarg_p;
	args->out_numargs = 1;
	args->out_args[0].size = माप(*outarg_p);
	args->out_args[0].value = outarg_p;
पूर्ण

/*
 * Flush inode->i_mसमय to the server
 */
पूर्णांक fuse_flush_बार(काष्ठा inode *inode, काष्ठा fuse_file *ff)
अणु
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	FUSE_ARGS(args);
	काष्ठा fuse_setattr_in inarg;
	काष्ठा fuse_attr_out outarg;

	स_रखो(&inarg, 0, माप(inarg));
	स_रखो(&outarg, 0, माप(outarg));

	inarg.valid = FATTR_MTIME;
	inarg.mसमय = inode->i_mसमय.tv_sec;
	inarg.mसमयnsec = inode->i_mसमय.tv_nsec;
	अगर (fm->fc->minor >= 23) अणु
		inarg.valid |= FATTR_CTIME;
		inarg.स_समय = inode->i_स_समय.tv_sec;
		inarg.स_समयnsec = inode->i_स_समय.tv_nsec;
	पूर्ण
	अगर (ff) अणु
		inarg.valid |= FATTR_FH;
		inarg.fh = ff->fh;
	पूर्ण
	fuse_setattr_fill(fm->fc, &args, inode, &inarg, &outarg);

	वापस fuse_simple_request(fm, &args);
पूर्ण

/*
 * Set attributes, and at the same समय refresh them.
 *
 * Truncation is slightly complicated, because the 'truncate' request
 * may fail, in which हाल we करोn't want to touch the mapping.
 * vmtruncate() करोesn't allow क्रम this हाल, so करो the rlimit checking
 * and the actual truncation by hand.
 */
पूर्णांक fuse_करो_setattr(काष्ठा dentry *dentry, काष्ठा iattr *attr,
		    काष्ठा file *file)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा fuse_mount *fm = get_fuse_mount(inode);
	काष्ठा fuse_conn *fc = fm->fc;
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);
	FUSE_ARGS(args);
	काष्ठा fuse_setattr_in inarg;
	काष्ठा fuse_attr_out outarg;
	bool is_truncate = false;
	bool is_wb = fc->ग_लिखोback_cache;
	loff_t oldsize;
	पूर्णांक err;
	bool trust_local_cmसमय = is_wb && S_ISREG(inode->i_mode);
	bool fault_blocked = false;

	अगर (!fc->शेष_permissions)
		attr->ia_valid |= ATTR_FORCE;

	err = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (err)
		वापस err;

	अगर (attr->ia_valid & ATTR_SIZE) अणु
		अगर (WARN_ON(!S_ISREG(inode->i_mode)))
			वापस -EIO;
		is_truncate = true;
	पूर्ण

	अगर (FUSE_IS_DAX(inode) && is_truncate) अणु
		करोwn_ग_लिखो(&fi->i_mmap_sem);
		fault_blocked = true;
		err = fuse_dax_अवरोध_layouts(inode, 0, 0);
		अगर (err) अणु
			up_ग_लिखो(&fi->i_mmap_sem);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (attr->ia_valid & ATTR_OPEN) अणु
		/* This is coming from खोलो(..., ... | O_TRUNC); */
		WARN_ON(!(attr->ia_valid & ATTR_SIZE));
		WARN_ON(attr->ia_size != 0);
		अगर (fc->atomic_o_trunc) अणु
			/*
			 * No need to send request to userspace, since actual
			 * truncation has alपढ़ोy been करोne by OPEN.  But still
			 * need to truncate page cache.
			 */
			i_size_ग_लिखो(inode, 0);
			truncate_pagecache(inode, 0);
			जाओ out;
		पूर्ण
		file = शून्य;
	पूर्ण

	/* Flush dirty data/metadata beक्रमe non-truncate SETATTR */
	अगर (is_wb && S_ISREG(inode->i_mode) &&
	    attr->ia_valid &
			(ATTR_MODE | ATTR_UID | ATTR_GID | ATTR_MTIME_SET |
			 ATTR_TIMES_SET)) अणु
		err = ग_लिखो_inode_now(inode, true);
		अगर (err)
			वापस err;

		fuse_set_noग_लिखो(inode);
		fuse_release_noग_लिखो(inode);
	पूर्ण

	अगर (is_truncate) अणु
		fuse_set_noग_लिखो(inode);
		set_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);
		अगर (trust_local_cmसमय && attr->ia_size != inode->i_size)
			attr->ia_valid |= ATTR_MTIME | ATTR_CTIME;
	पूर्ण

	स_रखो(&inarg, 0, माप(inarg));
	स_रखो(&outarg, 0, माप(outarg));
	iattr_to_fattr(fc, attr, &inarg, trust_local_cmसमय);
	अगर (file) अणु
		काष्ठा fuse_file *ff = file->निजी_data;
		inarg.valid |= FATTR_FH;
		inarg.fh = ff->fh;
	पूर्ण

	/* Kill suid/sgid क्रम non-directory chown unconditionally */
	अगर (fc->handle_समाप्तpriv_v2 && !S_ISसूची(inode->i_mode) &&
	    attr->ia_valid & (ATTR_UID | ATTR_GID))
		inarg.valid |= FATTR_KILL_SUIDGID;

	अगर (attr->ia_valid & ATTR_SIZE) अणु
		/* For mandatory locking in truncate */
		inarg.valid |= FATTR_LOCKOWNER;
		inarg.lock_owner = fuse_lock_owner_id(fc, current->files);

		/* Kill suid/sgid क्रम truncate only अगर no CAP_FSETID */
		अगर (fc->handle_समाप्तpriv_v2 && !capable(CAP_FSETID))
			inarg.valid |= FATTR_KILL_SUIDGID;
	पूर्ण
	fuse_setattr_fill(fc, &args, inode, &inarg, &outarg);
	err = fuse_simple_request(fm, &args);
	अगर (err) अणु
		अगर (err == -EINTR)
			fuse_invalidate_attr(inode);
		जाओ error;
	पूर्ण

	अगर (fuse_invalid_attr(&outarg.attr) ||
	    inode_wrong_type(inode, outarg.attr.mode)) अणु
		fuse_make_bad(inode);
		err = -EIO;
		जाओ error;
	पूर्ण

	spin_lock(&fi->lock);
	/* the kernel मुख्यtains i_mसमय locally */
	अगर (trust_local_cmसमय) अणु
		अगर (attr->ia_valid & ATTR_MTIME)
			inode->i_mसमय = attr->ia_mसमय;
		अगर (attr->ia_valid & ATTR_CTIME)
			inode->i_स_समय = attr->ia_स_समय;
		/* FIXME: clear I_सूचीTY_SYNC? */
	पूर्ण

	fuse_change_attributes_common(inode, &outarg.attr,
				      attr_समयout(&outarg));
	oldsize = inode->i_size;
	/* see the comment in fuse_change_attributes() */
	अगर (!is_wb || is_truncate || !S_ISREG(inode->i_mode))
		i_size_ग_लिखो(inode, outarg.attr.size);

	अगर (is_truncate) अणु
		/* NOTE: this may release/reacquire fi->lock */
		__fuse_release_noग_लिखो(inode);
	पूर्ण
	spin_unlock(&fi->lock);

	/*
	 * Only call invalidate_inode_pages2() after removing
	 * FUSE_NOWRITE, otherwise fuse_launder_page() would deadlock.
	 */
	अगर ((is_truncate || !is_wb) &&
	    S_ISREG(inode->i_mode) && oldsize != outarg.attr.size) अणु
		truncate_pagecache(inode, outarg.attr.size);
		invalidate_inode_pages2(inode->i_mapping);
	पूर्ण

	clear_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);
out:
	अगर (fault_blocked)
		up_ग_लिखो(&fi->i_mmap_sem);

	वापस 0;

error:
	अगर (is_truncate)
		fuse_release_noग_लिखो(inode);

	clear_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);

	अगर (fault_blocked)
		up_ग_लिखो(&fi->i_mmap_sem);
	वापस err;
पूर्ण

अटल पूर्णांक fuse_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *entry,
			काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(entry);
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);
	काष्ठा file *file = (attr->ia_valid & ATTR_खाता) ? attr->ia_file : शून्य;
	पूर्णांक ret;

	अगर (fuse_is_bad(inode))
		वापस -EIO;

	अगर (!fuse_allow_current_process(get_fuse_conn(inode)))
		वापस -EACCES;

	अगर (attr->ia_valid & (ATTR_KILL_SUID | ATTR_KILL_SGID)) अणु
		attr->ia_valid &= ~(ATTR_KILL_SUID | ATTR_KILL_SGID |
				    ATTR_MODE);

		/*
		 * The only sane way to reliably समाप्त suid/sgid is to करो it in
		 * the userspace fileप्रणाली
		 *
		 * This should be करोne on ग_लिखो(), truncate() and chown().
		 */
		अगर (!fc->handle_समाप्तpriv && !fc->handle_समाप्तpriv_v2) अणु
			/*
			 * ia_mode calculation may have used stale i_mode.
			 * Refresh and recalculate.
			 */
			ret = fuse_करो_getattr(inode, शून्य, file);
			अगर (ret)
				वापस ret;

			attr->ia_mode = inode->i_mode;
			अगर (inode->i_mode & S_ISUID) अणु
				attr->ia_valid |= ATTR_MODE;
				attr->ia_mode &= ~S_ISUID;
			पूर्ण
			अगर ((inode->i_mode & (S_ISGID | S_IXGRP)) == (S_ISGID | S_IXGRP)) अणु
				attr->ia_valid |= ATTR_MODE;
				attr->ia_mode &= ~S_ISGID;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!attr->ia_valid)
		वापस 0;

	ret = fuse_करो_setattr(entry, attr, file);
	अगर (!ret) अणु
		/*
		 * If fileप्रणाली supports acls it may have updated acl xattrs in
		 * the fileप्रणाली, so क्रमget cached acls क्रम the inode.
		 */
		अगर (fc->posix_acl)
			क्रमget_all_cached_acls(inode);

		/* Directory mode changed, may need to revalidate access */
		अगर (d_is_dir(entry) && (attr->ia_valid & ATTR_MODE))
			fuse_invalidate_entry_cache(entry);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक fuse_getattr(काष्ठा user_namespace *mnt_userns,
			स्थिर काष्ठा path *path, काष्ठा kstat *stat,
			u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा fuse_conn *fc = get_fuse_conn(inode);

	अगर (fuse_is_bad(inode))
		वापस -EIO;

	अगर (!fuse_allow_current_process(fc)) अणु
		अगर (!request_mask) अणु
			/*
			 * If user explicitly requested *nothing* then करोn't
			 * error out, but वापस st_dev only.
			 */
			stat->result_mask = 0;
			stat->dev = inode->i_sb->s_dev;
			वापस 0;
		पूर्ण
		वापस -EACCES;
	पूर्ण

	वापस fuse_update_get_attr(inode, शून्य, stat, request_mask, flags);
पूर्ण

अटल स्थिर काष्ठा inode_operations fuse_dir_inode_operations = अणु
	.lookup		= fuse_lookup,
	.सूची_गढ़ो		= fuse_सूची_गढ़ो,
	.symlink	= fuse_symlink,
	.unlink		= fuse_unlink,
	.सूची_हटाओ		= fuse_सूची_हटाओ,
	.नाम		= fuse_नाम2,
	.link		= fuse_link,
	.setattr	= fuse_setattr,
	.create		= fuse_create,
	.atomic_खोलो	= fuse_atomic_खोलो,
	.mknod		= fuse_mknod,
	.permission	= fuse_permission,
	.getattr	= fuse_getattr,
	.listxattr	= fuse_listxattr,
	.get_acl	= fuse_get_acl,
	.set_acl	= fuse_set_acl,
	.fileattr_get	= fuse_fileattr_get,
	.fileattr_set	= fuse_fileattr_set,
पूर्ण;

अटल स्थिर काष्ठा file_operations fuse_dir_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= fuse_सूची_पढ़ो,
	.खोलो		= fuse_dir_खोलो,
	.release	= fuse_dir_release,
	.fsync		= fuse_dir_fsync,
	.unlocked_ioctl	= fuse_dir_ioctl,
	.compat_ioctl	= fuse_dir_compat_ioctl,
पूर्ण;

अटल स्थिर काष्ठा inode_operations fuse_common_inode_operations = अणु
	.setattr	= fuse_setattr,
	.permission	= fuse_permission,
	.getattr	= fuse_getattr,
	.listxattr	= fuse_listxattr,
	.get_acl	= fuse_get_acl,
	.set_acl	= fuse_set_acl,
	.fileattr_get	= fuse_fileattr_get,
	.fileattr_set	= fuse_fileattr_set,
पूर्ण;

अटल स्थिर काष्ठा inode_operations fuse_symlink_inode_operations = अणु
	.setattr	= fuse_setattr,
	.get_link	= fuse_get_link,
	.getattr	= fuse_getattr,
	.listxattr	= fuse_listxattr,
पूर्ण;

व्योम fuse_init_common(काष्ठा inode *inode)
अणु
	inode->i_op = &fuse_common_inode_operations;
पूर्ण

व्योम fuse_init_dir(काष्ठा inode *inode)
अणु
	काष्ठा fuse_inode *fi = get_fuse_inode(inode);

	inode->i_op = &fuse_dir_inode_operations;
	inode->i_fop = &fuse_dir_operations;

	spin_lock_init(&fi->rdc.lock);
	fi->rdc.cached = false;
	fi->rdc.size = 0;
	fi->rdc.pos = 0;
	fi->rdc.version = 0;
पूर्ण

अटल पूर्णांक fuse_symlink_पढ़ोpage(काष्ठा file *null, काष्ठा page *page)
अणु
	पूर्णांक err = fuse_पढ़ोlink_page(page->mapping->host, page);

	अगर (!err)
		SetPageUptodate(page);

	unlock_page(page);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा address_space_operations fuse_symlink_aops = अणु
	.पढ़ोpage	= fuse_symlink_पढ़ोpage,
पूर्ण;

व्योम fuse_init_symlink(काष्ठा inode *inode)
अणु
	inode->i_op = &fuse_symlink_inode_operations;
	inode->i_data.a_ops = &fuse_symlink_aops;
	inode_nohighmem(inode);
पूर्ण
