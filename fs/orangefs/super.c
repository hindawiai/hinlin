<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */

#समावेश "protocol.h"
#समावेश "orangefs-kernel.h"
#समावेश "orangefs-bufmap.h"

#समावेश <linux/parser.h>
#समावेश <linux/hashtable.h>

/* a cache क्रम orangefs-inode objects (i.e. orangefs inode निजी data) */
अटल काष्ठा kmem_cache *orangefs_inode_cache;

/* list क्रम storing orangefs specअगरic superblocks in use */
LIST_HEAD(orangefs_superblocks);

DEFINE_SPINLOCK(orangefs_superblocks_lock);

क्रमागत अणु
	Opt_पूर्णांकr,
	Opt_acl,
	Opt_local_lock,

	Opt_err
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणु Opt_acl,		"acl" पूर्ण,
	अणु Opt_पूर्णांकr,		"intr" पूर्ण,
	अणु Opt_local_lock,	"local_lock" पूर्ण,
	अणु Opt_err,	शून्य पूर्ण
पूर्ण;

uपूर्णांक64_t orangefs_features;

अटल पूर्णांक orangefs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा orangefs_sb_info_s *orangefs_sb = ORANGEFS_SB(root->d_sb);

	अगर (root->d_sb->s_flags & SB_POSIXACL)
		seq_माला_दो(m, ",acl");
	अगर (orangefs_sb->flags & ORANGEFS_OPT_INTR)
		seq_माला_दो(m, ",intr");
	अगर (orangefs_sb->flags & ORANGEFS_OPT_LOCAL_LOCK)
		seq_माला_दो(m, ",local_lock");
	वापस 0;
पूर्ण

अटल पूर्णांक parse_mount_options(काष्ठा super_block *sb, अक्षर *options,
		पूर्णांक silent)
अणु
	काष्ठा orangefs_sb_info_s *orangefs_sb = ORANGEFS_SB(sb);
	substring_t args[MAX_OPT_ARGS];
	अक्षर *p;

	/*
	 * Force any potential flags that might be set from the mount
	 * to zero, ie, initialize to unset.
	 */
	sb->s_flags &= ~SB_POSIXACL;
	orangefs_sb->flags &= ~ORANGEFS_OPT_INTR;
	orangefs_sb->flags &= ~ORANGEFS_OPT_LOCAL_LOCK;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;

		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_acl:
			sb->s_flags |= SB_POSIXACL;
			अवरोध;
		हाल Opt_पूर्णांकr:
			orangefs_sb->flags |= ORANGEFS_OPT_INTR;
			अवरोध;
		हाल Opt_local_lock:
			orangefs_sb->flags |= ORANGEFS_OPT_LOCAL_LOCK;
			अवरोध;
		शेष:
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस 0;
fail:
	अगर (!silent)
		gossip_err("Error: mount option [%s] is not supported.\n", p);
	वापस -EINVAL;
पूर्ण

अटल व्योम orangefs_inode_cache_ctor(व्योम *req)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = req;

	inode_init_once(&orangefs_inode->vfs_inode);
	init_rwsem(&orangefs_inode->xattr_sem);
पूर्ण

अटल काष्ठा inode *orangefs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode;

	orangefs_inode = kmem_cache_alloc(orangefs_inode_cache, GFP_KERNEL);
	अगर (!orangefs_inode)
		वापस शून्य;

	/*
	 * We want to clear everything except क्रम rw_semaphore and the
	 * vfs_inode.
	 */
	स_रखो(&orangefs_inode->refn.khandle, 0, 16);
	orangefs_inode->refn.fs_id = ORANGEFS_FS_ID_शून्य;
	orangefs_inode->last_failed_block_index_पढ़ो = 0;
	स_रखो(orangefs_inode->link_target, 0, माप(orangefs_inode->link_target));

	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "orangefs_alloc_inode: allocated %p\n",
		     &orangefs_inode->vfs_inode);
	वापस &orangefs_inode->vfs_inode;
पूर्ण

अटल व्योम orangefs_मुक्त_inode(काष्ठा inode *inode)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);
	काष्ठा orangefs_cached_xattr *cx;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक i;

	hash_क्रम_each_safe(orangefs_inode->xattr_cache, i, पंचांगp, cx, node) अणु
		hlist_del(&cx->node);
		kमुक्त(cx);
	पूर्ण

	kmem_cache_मुक्त(orangefs_inode_cache, orangefs_inode);
पूर्ण

अटल व्योम orangefs_destroy_inode(काष्ठा inode *inode)
अणु
	काष्ठा orangefs_inode_s *orangefs_inode = ORANGEFS_I(inode);

	gossip_debug(GOSSIP_SUPER_DEBUG,
			"%s: deallocated %p destroying inode %pU\n",
			__func__, orangefs_inode, get_khandle_from_ino(inode));
पूर्ण

अटल पूर्णांक orangefs_ग_लिखो_inode(काष्ठा inode *inode,
				काष्ठा ग_लिखोback_control *wbc)
अणु
	gossip_debug(GOSSIP_SUPER_DEBUG, "orangefs_write_inode\n");
	वापस orangefs_inode_setattr(inode);
पूर्ण

/*
 * NOTE: inक्रमmation filled in here is typically reflected in the
 * output of the प्रणाली command 'df'
*/
अटल पूर्णांक orangefs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा orangefs_kernel_op_s *new_op = शून्य;
	पूर्णांक flags = 0;
	काष्ठा super_block *sb = शून्य;

	sb = dentry->d_sb;

	gossip_debug(GOSSIP_SUPER_DEBUG,
			"%s: called on sb %p (fs_id is %d)\n",
			__func__,
			sb,
			(पूर्णांक)(ORANGEFS_SB(sb)->fs_id));

	new_op = op_alloc(ORANGEFS_VFS_OP_STATFS);
	अगर (!new_op)
		वापस ret;
	new_op->upcall.req.statfs.fs_id = ORANGEFS_SB(sb)->fs_id;

	अगर (ORANGEFS_SB(sb)->flags & ORANGEFS_OPT_INTR)
		flags = ORANGEFS_OP_INTERRUPTIBLE;

	ret = service_operation(new_op, "orangefs_statfs", flags);

	अगर (new_op->करोwncall.status < 0)
		जाओ out_op_release;

	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "%s: got %ld blocks available | "
		     "%ld blocks total | %ld block size | "
		     "%ld files total | %ld files avail\n",
		     __func__,
		     (दीर्घ)new_op->करोwncall.resp.statfs.blocks_avail,
		     (दीर्घ)new_op->करोwncall.resp.statfs.blocks_total,
		     (दीर्घ)new_op->करोwncall.resp.statfs.block_size,
		     (दीर्घ)new_op->करोwncall.resp.statfs.files_total,
		     (दीर्घ)new_op->करोwncall.resp.statfs.files_avail);

	buf->f_type = sb->s_magic;
	स_नकल(&buf->f_fsid, &ORANGEFS_SB(sb)->fs_id, माप(buf->f_fsid));
	buf->f_bsize = new_op->करोwncall.resp.statfs.block_size;
	buf->f_namelen = ORANGEFS_NAME_MAX;

	buf->f_blocks = (sector_t) new_op->करोwncall.resp.statfs.blocks_total;
	buf->f_bमुक्त = (sector_t) new_op->करोwncall.resp.statfs.blocks_avail;
	buf->f_bavail = (sector_t) new_op->करोwncall.resp.statfs.blocks_avail;
	buf->f_files = (sector_t) new_op->करोwncall.resp.statfs.files_total;
	buf->f_fमुक्त = (sector_t) new_op->करोwncall.resp.statfs.files_avail;
	buf->f_frsize = sb->s_blocksize;

out_op_release:
	op_release(new_op);
	gossip_debug(GOSSIP_SUPER_DEBUG, "%s: returning %d\n", __func__, ret);
	वापस ret;
पूर्ण

/*
 * Remount as initiated by VFS layer.  We just need to reparse the mount
 * options, no need to संकेत pvfs2-client-core about it.
 */
अटल पूर्णांक orangefs_remount_fs(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	gossip_debug(GOSSIP_SUPER_DEBUG, "orangefs_remount_fs: called\n");
	वापस parse_mount_options(sb, data, 1);
पूर्ण

/*
 * Remount as initiated by pvfs2-client-core on restart.  This is used to
 * repopulate mount inक्रमmation left from previous pvfs2-client-core.
 *
 * the idea here is that given a valid superblock, we're
 * re-initializing the user space client with the initial mount
 * inक्रमmation specअगरied when the super block was first initialized.
 * this is very dअगरferent than the first initialization/creation of a
 * superblock.  we use the special service_priority_operation to make
 * sure that the mount माला_लो ahead of any other pending operation that
 * is रुकोing क्रम servicing.  this means that the pvfs2-client won't
 * fail to start several बार क्रम all other pending operations beक्रमe
 * the client regains all of the mount inक्रमmation from us.
 * NOTE: this function assumes that the request_mutex is alपढ़ोy acquired!
 */
पूर्णांक orangefs_remount(काष्ठा orangefs_sb_info_s *orangefs_sb)
अणु
	काष्ठा orangefs_kernel_op_s *new_op;
	पूर्णांक ret = -EINVAL;

	gossip_debug(GOSSIP_SUPER_DEBUG, "orangefs_remount: called\n");

	new_op = op_alloc(ORANGEFS_VFS_OP_FS_MOUNT);
	अगर (!new_op)
		वापस -ENOMEM;
	म_नकलन(new_op->upcall.req.fs_mount.orangefs_config_server,
		orangefs_sb->devname,
		ORANGEFS_MAX_SERVER_ADDR_LEN);

	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "Attempting ORANGEFS Remount via host %s\n",
		     new_op->upcall.req.fs_mount.orangefs_config_server);

	/*
	 * we assume that the calling function has alपढ़ोy acquired the
	 * request_mutex to prevent other operations from bypassing
	 * this one
	 */
	ret = service_operation(new_op, "orangefs_remount",
		ORANGEFS_OP_PRIORITY | ORANGEFS_OP_NO_MUTEX);
	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "orangefs_remount: mount got return value of %d\n",
		     ret);
	अगर (ret == 0) अणु
		/*
		 * store the id asचिन्हित to this sb -- it's just a
		 * लघु-lived mapping that the प्रणाली पूर्णांकerface uses
		 * to map this superblock to a particular mount entry
		 */
		orangefs_sb->id = new_op->करोwncall.resp.fs_mount.id;
		orangefs_sb->mount_pending = 0;
	पूर्ण

	op_release(new_op);

	अगर (orangefs_userspace_version >= 20906) अणु
		new_op = op_alloc(ORANGEFS_VFS_OP_FEATURES);
		अगर (!new_op)
			वापस -ENOMEM;
		new_op->upcall.req.features.features = 0;
		ret = service_operation(new_op, "orangefs_features",
		    ORANGEFS_OP_PRIORITY | ORANGEFS_OP_NO_MUTEX);
		अगर (!ret)
			orangefs_features =
			    new_op->करोwncall.resp.features.features;
		अन्यथा
			orangefs_features = 0;
		op_release(new_op);
	पूर्ण अन्यथा अणु
		orangefs_features = 0;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक fsid_key_table_initialize(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम fsid_key_table_finalize(व्योम)
अणु
पूर्ण

अटल स्थिर काष्ठा super_operations orangefs_s_ops = अणु
	.alloc_inode = orangefs_alloc_inode,
	.मुक्त_inode = orangefs_मुक्त_inode,
	.destroy_inode = orangefs_destroy_inode,
	.ग_लिखो_inode = orangefs_ग_लिखो_inode,
	.drop_inode = generic_delete_inode,
	.statfs = orangefs_statfs,
	.remount_fs = orangefs_remount_fs,
	.show_options = orangefs_show_options,
पूर्ण;

अटल काष्ठा dentry *orangefs_fh_to_dentry(काष्ठा super_block *sb,
				  काष्ठा fid *fid,
				  पूर्णांक fh_len,
				  पूर्णांक fh_type)
अणु
	काष्ठा orangefs_object_kref refn;

	अगर (fh_len < 5 || fh_type > 2)
		वापस शून्य;

	ORANGEFS_khandle_from(&(refn.khandle), fid->raw, 16);
	refn.fs_id = (u32) fid->raw[4];
	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "fh_to_dentry: handle %pU, fs_id %d\n",
		     &refn.khandle,
		     refn.fs_id);

	वापस d_obtain_alias(orangefs_iget(sb, &refn));
पूर्ण

अटल पूर्णांक orangefs_encode_fh(काष्ठा inode *inode,
		    __u32 *fh,
		    पूर्णांक *max_len,
		    काष्ठा inode *parent)
अणु
	पूर्णांक len = parent ? 10 : 5;
	पूर्णांक type = 1;
	काष्ठा orangefs_object_kref refn;

	अगर (*max_len < len) अणु
		gossip_err("fh buffer is too small for encoding\n");
		*max_len = len;
		type = 255;
		जाओ out;
	पूर्ण

	refn = ORANGEFS_I(inode)->refn;
	ORANGEFS_khandle_to(&refn.khandle, fh, 16);
	fh[4] = refn.fs_id;

	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "Encoding fh: handle %pU, fsid %u\n",
		     &refn.khandle,
		     refn.fs_id);


	अगर (parent) अणु
		refn = ORANGEFS_I(parent)->refn;
		ORANGEFS_khandle_to(&refn.khandle, (अक्षर *) fh + 20, 16);
		fh[9] = refn.fs_id;

		type = 2;
		gossip_debug(GOSSIP_SUPER_DEBUG,
			     "Encoding parent: handle %pU, fsid %u\n",
			     &refn.khandle,
			     refn.fs_id);
	पूर्ण
	*max_len = len;

out:
	वापस type;
पूर्ण

अटल स्थिर काष्ठा export_operations orangefs_export_ops = अणु
	.encode_fh = orangefs_encode_fh,
	.fh_to_dentry = orangefs_fh_to_dentry,
पूर्ण;

अटल पूर्णांक orangefs_unmount(पूर्णांक id, __s32 fs_id, स्थिर अक्षर *devname)
अणु
	काष्ठा orangefs_kernel_op_s *op;
	पूर्णांक r;
	op = op_alloc(ORANGEFS_VFS_OP_FS_UMOUNT);
	अगर (!op)
		वापस -ENOMEM;
	op->upcall.req.fs_umount.id = id;
	op->upcall.req.fs_umount.fs_id = fs_id;
	म_नकलन(op->upcall.req.fs_umount.orangefs_config_server,
	    devname, ORANGEFS_MAX_SERVER_ADDR_LEN - 1);
	r = service_operation(op, "orangefs_fs_umount", 0);
	/* Not much to करो about an error here. */
	अगर (r)
		gossip_err("orangefs_unmount: service_operation %d\n", r);
	op_release(op);
	वापस r;
पूर्ण

अटल पूर्णांक orangefs_fill_sb(काष्ठा super_block *sb,
		काष्ठा orangefs_fs_mount_response *fs_mount,
		व्योम *data, पूर्णांक silent)
अणु
	पूर्णांक ret;
	काष्ठा inode *root;
	काष्ठा dentry *root_dentry;
	काष्ठा orangefs_object_kref root_object;

	ORANGEFS_SB(sb)->sb = sb;

	ORANGEFS_SB(sb)->root_khandle = fs_mount->root_khandle;
	ORANGEFS_SB(sb)->fs_id = fs_mount->fs_id;
	ORANGEFS_SB(sb)->id = fs_mount->id;

	अगर (data) अणु
		ret = parse_mount_options(sb, data, silent);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Hang the xattr handlers off the superblock */
	sb->s_xattr = orangefs_xattr_handlers;
	sb->s_magic = ORANGEFS_SUPER_MAGIC;
	sb->s_op = &orangefs_s_ops;
	sb->s_d_op = &orangefs_dentry_operations;

	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_maxbytes = MAX_LFS_खाताSIZE;

	ret = super_setup_bdi(sb);
	अगर (ret)
		वापस ret;

	root_object.khandle = ORANGEFS_SB(sb)->root_khandle;
	root_object.fs_id = ORANGEFS_SB(sb)->fs_id;
	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "get inode %pU, fsid %d\n",
		     &root_object.khandle,
		     root_object.fs_id);

	root = orangefs_iget(sb, &root_object);
	अगर (IS_ERR(root))
		वापस PTR_ERR(root);

	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "Allocated root inode [%p] with mode %x\n",
		     root,
		     root->i_mode);

	/* allocates and places root dentry in dcache */
	root_dentry = d_make_root(root);
	अगर (!root_dentry)
		वापस -ENOMEM;

	sb->s_export_op = &orangefs_export_ops;
	sb->s_root = root_dentry;
	वापस 0;
पूर्ण

काष्ठा dentry *orangefs_mount(काष्ठा file_प्रणाली_type *fst,
			   पूर्णांक flags,
			   स्थिर अक्षर *devname,
			   व्योम *data)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा super_block *sb = ERR_PTR(-EINVAL);
	काष्ठा orangefs_kernel_op_s *new_op;
	काष्ठा dentry *d = ERR_PTR(-EINVAL);

	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "orangefs_mount: called with devname %s\n",
		     devname);

	अगर (!devname) अणु
		gossip_err("ERROR: device name not specified.\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	new_op = op_alloc(ORANGEFS_VFS_OP_FS_MOUNT);
	अगर (!new_op)
		वापस ERR_PTR(-ENOMEM);

	म_नकलन(new_op->upcall.req.fs_mount.orangefs_config_server,
		devname,
		ORANGEFS_MAX_SERVER_ADDR_LEN - 1);

	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "Attempting ORANGEFS Mount via host %s\n",
		     new_op->upcall.req.fs_mount.orangefs_config_server);

	ret = service_operation(new_op, "orangefs_mount", 0);
	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "orangefs_mount: mount got return value of %d\n", ret);
	अगर (ret)
		जाओ मुक्त_op;

	अगर (new_op->करोwncall.resp.fs_mount.fs_id == ORANGEFS_FS_ID_शून्य) अणु
		gossip_err("ERROR: Retrieved null fs_id\n");
		ret = -EINVAL;
		जाओ मुक्त_op;
	पूर्ण

	sb = sget(fst, शून्य, set_anon_super, flags, शून्य);

	अगर (IS_ERR(sb)) अणु
		d = ERR_CAST(sb);
		orangefs_unmount(new_op->करोwncall.resp.fs_mount.id,
		    new_op->करोwncall.resp.fs_mount.fs_id, devname);
		जाओ मुक्त_op;
	पूर्ण

	/* alloc and init our निजी orangefs sb info */
	sb->s_fs_info = kzalloc(माप(काष्ठा orangefs_sb_info_s), GFP_KERNEL);
	अगर (!ORANGEFS_SB(sb)) अणु
		d = ERR_PTR(-ENOMEM);
		जाओ मुक्त_op;
	पूर्ण

	ret = orangefs_fill_sb(sb,
	      &new_op->करोwncall.resp.fs_mount, data,
	      flags & SB_SILENT ? 1 : 0);

	अगर (ret) अणु
		d = ERR_PTR(ret);
		जाओ मुक्त_sb_and_op;
	पूर्ण

	/*
	 * on successful mount, store the devname and data
	 * used
	 */
	म_नकलन(ORANGEFS_SB(sb)->devname,
		devname,
		ORANGEFS_MAX_SERVER_ADDR_LEN - 1);

	/* mount_pending must be cleared */
	ORANGEFS_SB(sb)->mount_pending = 0;

	/*
	 * finally, add this sb to our list of known orangefs
	 * sb's
	 */
	gossip_debug(GOSSIP_SUPER_DEBUG,
		     "Adding SB %p to orangefs superblocks\n",
		     ORANGEFS_SB(sb));
	spin_lock(&orangefs_superblocks_lock);
	list_add_tail(&ORANGEFS_SB(sb)->list, &orangefs_superblocks);
	spin_unlock(&orangefs_superblocks_lock);
	op_release(new_op);

	/* Must be हटाओd from the list now. */
	ORANGEFS_SB(sb)->no_list = 0;

	अगर (orangefs_userspace_version >= 20906) अणु
		new_op = op_alloc(ORANGEFS_VFS_OP_FEATURES);
		अगर (!new_op)
			वापस ERR_PTR(-ENOMEM);
		new_op->upcall.req.features.features = 0;
		ret = service_operation(new_op, "orangefs_features", 0);
		orangefs_features = new_op->करोwncall.resp.features.features;
		op_release(new_op);
	पूर्ण अन्यथा अणु
		orangefs_features = 0;
	पूर्ण

	वापस dget(sb->s_root);

मुक्त_sb_and_op:
	/* Will call orangefs_समाप्त_sb with sb not in list. */
	ORANGEFS_SB(sb)->no_list = 1;
	/* ORANGEFS_VFS_OP_FS_UMOUNT is करोne by orangefs_समाप्त_sb. */
	deactivate_locked_super(sb);
मुक्त_op:
	gossip_err("orangefs_mount: mount request failed with %d\n", ret);
	अगर (ret == -EINVAL) अणु
		gossip_err("Ensure that all orangefs-servers have the same FS configuration files\n");
		gossip_err("Look at pvfs2-client-core log file (typically /tmp/pvfs2-client.log) for more details\n");
	पूर्ण

	op_release(new_op);

	वापस d;
पूर्ण

व्योम orangefs_समाप्त_sb(काष्ठा super_block *sb)
अणु
	पूर्णांक r;
	gossip_debug(GOSSIP_SUPER_DEBUG, "orangefs_kill_sb: called\n");

	/* provided sb cleanup */
	समाप्त_anon_super(sb);

	अगर (!ORANGEFS_SB(sb)) अणु
		mutex_lock(&orangefs_request_mutex);
		mutex_unlock(&orangefs_request_mutex);
		वापस;
	पूर्ण
	/*
	 * issue the unmount to userspace to tell it to हटाओ the
	 * dynamic mount info it has क्रम this superblock
	 */
	r = orangefs_unmount(ORANGEFS_SB(sb)->id, ORANGEFS_SB(sb)->fs_id,
	    ORANGEFS_SB(sb)->devname);
	अगर (!r)
		ORANGEFS_SB(sb)->mount_pending = 1;

	अगर (!ORANGEFS_SB(sb)->no_list) अणु
		/* हटाओ the sb from our list of orangefs specअगरic sb's */
		spin_lock(&orangefs_superblocks_lock);
		/* not list_del_init */
		__list_del_entry(&ORANGEFS_SB(sb)->list);
		ORANGEFS_SB(sb)->list.prev = शून्य;
		spin_unlock(&orangefs_superblocks_lock);
	पूर्ण

	/*
	 * make sure that ORANGEFS_DEV_REMOUNT_ALL loop that might've seen us
	 * माला_लो completed beक्रमe we मुक्त the dang thing.
	 */
	mutex_lock(&orangefs_request_mutex);
	mutex_unlock(&orangefs_request_mutex);

	/* मुक्त the orangefs superblock निजी data */
	kमुक्त(ORANGEFS_SB(sb));
पूर्ण

पूर्णांक orangefs_inode_cache_initialize(व्योम)
अणु
	orangefs_inode_cache = kmem_cache_create_usercopy(
					"orangefs_inode_cache",
					माप(काष्ठा orangefs_inode_s),
					0,
					ORANGEFS_CACHE_CREATE_FLAGS,
					दुरत्व(काष्ठा orangefs_inode_s,
						link_target),
					माप_field(काष्ठा orangefs_inode_s,
						link_target),
					orangefs_inode_cache_ctor);

	अगर (!orangefs_inode_cache) अणु
		gossip_err("Cannot create orangefs_inode_cache\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक orangefs_inode_cache_finalize(व्योम)
अणु
	kmem_cache_destroy(orangefs_inode_cache);
	वापस 0;
पूर्ण
