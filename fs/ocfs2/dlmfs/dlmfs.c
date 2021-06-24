<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dlmfs.c
 *
 * Code which implements the kernel side of a minimal userspace
 * पूर्णांकerface to our DLM. This file handles the भव file प्रणाली
 * used क्रम communication with userspace. Credit should go to ramfs,
 * which was a ढाँचा क्रम the fs side of this module.
 *
 * Copyright (C) 2003, 2004 Oracle.  All rights reserved.
 */

/* Simple VFS hooks based on: */
/*
 * Resizable simple ram fileप्रणाली क्रम Linux.
 *
 * Copyright (C) 2000 Linus Torvalds.
 *               2000 Transmeta Corp.
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/backing-dev.h>
#समावेश <linux/poll.h>

#समावेश <linux/uaccess.h>

#समावेश "../stackglue.h"
#समावेश "userdlm.h"

#घोषणा MLOG_MASK_PREFIX ML_DLMFS
#समावेश "../cluster/masklog.h"


अटल स्थिर काष्ठा super_operations dlmfs_ops;
अटल स्थिर काष्ठा file_operations dlmfs_file_operations;
अटल स्थिर काष्ठा inode_operations dlmfs_dir_inode_operations;
अटल स्थिर काष्ठा inode_operations dlmfs_root_inode_operations;
अटल स्थिर काष्ठा inode_operations dlmfs_file_inode_operations;
अटल काष्ठा kmem_cache *dlmfs_inode_cache;

काष्ठा workqueue_काष्ठा *user_dlm_worker;



/*
 * These are the ABI capabilities of dlmfs.
 *
 * Over समय, dlmfs has added some features that were not part of the
 * initial ABI.  Unक्रमtunately, some of these features are not detectable
 * via standard usage.  For example, Linux's शेष poll always वापसs
 * EPOLLIN, so there is no way क्रम a caller of poll(2) to know when dlmfs
 * added poll support.  Instead, we provide this list of new capabilities.
 *
 * Capabilities is a पढ़ो-only attribute.  We करो it as a module parameter
 * so we can discover it whether dlmfs is built in, loaded, or even not
 * loaded.
 *
 * The ABI features are local to this machine's dlmfs mount.  This is
 * distinct from the locking protocol, which is concerned with पूर्णांकer-node
 * पूर्णांकeraction.
 *
 * Capabilities:
 * - bast	: EPOLLIN against the file descriptor of a held lock
 *		  signअगरies a bast fired on the lock.
 */
#घोषणा DLMFS_CAPABILITIES "bast stackglue"
अटल पूर्णांक param_set_dlmfs_capabilities(स्थिर अक्षर *val,
					स्थिर काष्ठा kernel_param *kp)
अणु
	prपूर्णांकk(KERN_ERR "%s: readonly parameter\n", kp->name);
	वापस -EINVAL;
पूर्ण
अटल पूर्णांक param_get_dlmfs_capabilities(अक्षर *buffer,
					स्थिर काष्ठा kernel_param *kp)
अणु
	वापस strlcpy(buffer, DLMFS_CAPABILITIES,
		       म_माप(DLMFS_CAPABILITIES) + 1);
पूर्ण
module_param_call(capabilities, param_set_dlmfs_capabilities,
		  param_get_dlmfs_capabilities, शून्य, 0444);
MODULE_PARM_DESC(capabilities, DLMFS_CAPABILITIES);


/*
 * decodes a set of खोलो flags पूर्णांकo a valid lock level and a set of flags.
 * वापसs < 0 अगर we have invalid flags
 * flags which mean something to us:
 * O_RDONLY -> PRMODE level
 * O_WRONLY -> EXMODE level
 *
 * O_NONBLOCK -> NOQUEUE
 */
अटल पूर्णांक dlmfs_decode_खोलो_flags(पूर्णांक खोलो_flags,
				   पूर्णांक *level,
				   पूर्णांक *flags)
अणु
	अगर (खोलो_flags & (O_WRONLY|O_RDWR))
		*level = DLM_LOCK_EX;
	अन्यथा
		*level = DLM_LOCK_PR;

	*flags = 0;
	अगर (खोलो_flags & O_NONBLOCK)
		*flags |= DLM_LKF_NOQUEUE;

	वापस 0;
पूर्ण

अटल पूर्णांक dlmfs_file_खोलो(काष्ठा inode *inode,
			   काष्ठा file *file)
अणु
	पूर्णांक status, level, flags;
	काष्ठा dlmfs_filp_निजी *fp = शून्य;
	काष्ठा dlmfs_inode_निजी *ip;

	अगर (S_ISसूची(inode->i_mode))
		BUG();

	mlog(0, "open called on inode %lu, flags 0x%x\n", inode->i_ino,
		file->f_flags);

	status = dlmfs_decode_खोलो_flags(file->f_flags, &level, &flags);
	अगर (status < 0)
		जाओ bail;

	/* We करोn't want to honor O_APPEND at पढ़ो/ग_लिखो समय as it
	 * करोesn't make sense क्रम LVB ग_लिखोs. */
	file->f_flags &= ~O_APPEND;

	fp = kदो_स्मृति(माप(*fp), GFP_NOFS);
	अगर (!fp) अणु
		status = -ENOMEM;
		जाओ bail;
	पूर्ण
	fp->fp_lock_level = level;

	ip = DLMFS_I(inode);

	status = user_dlm_cluster_lock(&ip->ip_lockres, level, flags);
	अगर (status < 0) अणु
		/* this is a strange error to वापस here but I want
		 * to be able userspace to be able to distinguish a
		 * valid lock request from one that simply couldn't be
		 * granted. */
		अगर (flags & DLM_LKF_NOQUEUE && status == -EAGAIN)
			status = -ETXTBSY;
		kमुक्त(fp);
		जाओ bail;
	पूर्ण

	file->निजी_data = fp;
bail:
	वापस status;
पूर्ण

अटल पूर्णांक dlmfs_file_release(काष्ठा inode *inode,
			      काष्ठा file *file)
अणु
	पूर्णांक level;
	काष्ठा dlmfs_inode_निजी *ip = DLMFS_I(inode);
	काष्ठा dlmfs_filp_निजी *fp = file->निजी_data;

	अगर (S_ISसूची(inode->i_mode))
		BUG();

	mlog(0, "close called on inode %lu\n", inode->i_ino);

	अगर (fp) अणु
		level = fp->fp_lock_level;
		अगर (level != DLM_LOCK_IV)
			user_dlm_cluster_unlock(&ip->ip_lockres, level);

		kमुक्त(fp);
		file->निजी_data = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * We करो ->setattr() just to override size changes.  Our size is the size
 * of the LVB and nothing अन्यथा.
 */
अटल पूर्णांक dlmfs_file_setattr(काष्ठा user_namespace *mnt_userns,
			      काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	पूर्णांक error;
	काष्ठा inode *inode = d_inode(dentry);

	attr->ia_valid &= ~ATTR_SIZE;
	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		वापस error;

	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

अटल __poll_t dlmfs_file_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t event = 0;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा dlmfs_inode_निजी *ip = DLMFS_I(inode);

	poll_रुको(file, &ip->ip_lockres.l_event, रुको);

	spin_lock(&ip->ip_lockres.l_lock);
	अगर (ip->ip_lockres.l_flags & USER_LOCK_BLOCKED)
		event = EPOLLIN | EPOLLRDNORM;
	spin_unlock(&ip->ip_lockres.l_lock);

	वापस event;
पूर्ण

अटल sमाप_प्रकार dlmfs_file_पढ़ो(काष्ठा file *file,
			       अक्षर __user *buf,
			       माप_प्रकार count,
			       loff_t *ppos)
अणु
	अक्षर lvb[DLM_LVB_LEN];

	अगर (!user_dlm_पढ़ो_lvb(file_inode(file), lvb))
		वापस 0;

	वापस simple_पढ़ो_from_buffer(buf, count, ppos, lvb, माप(lvb));
पूर्ण

अटल sमाप_प्रकार dlmfs_file_ग_लिखो(काष्ठा file *filp,
				स्थिर अक्षर __user *buf,
				माप_प्रकार count,
				loff_t *ppos)
अणु
	अक्षर lvb_buf[DLM_LVB_LEN];
	पूर्णांक bytes_left;
	काष्ठा inode *inode = file_inode(filp);

	mlog(0, "inode %lu, count = %zu, *ppos = %llu\n",
		inode->i_ino, count, *ppos);

	अगर (*ppos >= DLM_LVB_LEN)
		वापस -ENOSPC;

	/* करोn't ग_लिखो past the lvb */
	अगर (count > DLM_LVB_LEN - *ppos)
		count = DLM_LVB_LEN - *ppos;

	अगर (!count)
		वापस 0;

	bytes_left = copy_from_user(lvb_buf, buf, count);
	count -= bytes_left;
	अगर (count)
		user_dlm_ग_लिखो_lvb(inode, lvb_buf, count);

	*ppos = *ppos + count;
	mlog(0, "wrote %zu bytes\n", count);
	वापस count;
पूर्ण

अटल व्योम dlmfs_init_once(व्योम *foo)
अणु
	काष्ठा dlmfs_inode_निजी *ip =
		(काष्ठा dlmfs_inode_निजी *) foo;

	ip->ip_conn = शून्य;
	ip->ip_parent = शून्य;

	inode_init_once(&ip->ip_vfs_inode);
पूर्ण

अटल काष्ठा inode *dlmfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा dlmfs_inode_निजी *ip;

	ip = kmem_cache_alloc(dlmfs_inode_cache, GFP_NOFS);
	अगर (!ip)
		वापस शून्य;

	वापस &ip->ip_vfs_inode;
पूर्ण

अटल व्योम dlmfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(dlmfs_inode_cache, DLMFS_I(inode));
पूर्ण

अटल व्योम dlmfs_evict_inode(काष्ठा inode *inode)
अणु
	पूर्णांक status;
	काष्ठा dlmfs_inode_निजी *ip;

	clear_inode(inode);

	mlog(0, "inode %lu\n", inode->i_ino);

	ip = DLMFS_I(inode);

	अगर (S_ISREG(inode->i_mode)) अणु
		status = user_dlm_destroy_lock(&ip->ip_lockres);
		अगर (status < 0)
			mlog_त्रुटि_सं(status);
		iput(ip->ip_parent);
		जाओ clear_fields;
	पूर्ण

	mlog(0, "we're a directory, ip->ip_conn = 0x%p\n", ip->ip_conn);
	/* we must be a directory. If required, lets unरेजिस्टर the
	 * dlm context now. */
	अगर (ip->ip_conn)
		user_dlm_unरेजिस्टर(ip->ip_conn);
clear_fields:
	ip->ip_parent = शून्य;
	ip->ip_conn = शून्य;
पूर्ण

अटल काष्ठा inode *dlmfs_get_root_inode(काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode = new_inode(sb);
	umode_t mode = S_IFसूची | 0755;

	अगर (inode) अणु
		inode->i_ino = get_next_ino();
		inode_init_owner(&init_user_ns, inode, शून्य, mode);
		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
		inc_nlink(inode);

		inode->i_fop = &simple_dir_operations;
		inode->i_op = &dlmfs_root_inode_operations;
	पूर्ण

	वापस inode;
पूर्ण

अटल काष्ठा inode *dlmfs_get_inode(काष्ठा inode *parent,
				     काष्ठा dentry *dentry,
				     umode_t mode)
अणु
	काष्ठा super_block *sb = parent->i_sb;
	काष्ठा inode * inode = new_inode(sb);
	काष्ठा dlmfs_inode_निजी *ip;

	अगर (!inode)
		वापस शून्य;

	inode->i_ino = get_next_ino();
	inode_init_owner(&init_user_ns, inode, parent, mode);
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);

	ip = DLMFS_I(inode);
	ip->ip_conn = DLMFS_I(parent)->ip_conn;

	चयन (mode & S_IFMT) अणु
	शेष:
		/* क्रम now we करोn't support anything other than
		 * directories and regular files. */
		BUG();
		अवरोध;
	हाल S_IFREG:
		inode->i_op = &dlmfs_file_inode_operations;
		inode->i_fop = &dlmfs_file_operations;

		i_size_ग_लिखो(inode,  DLM_LVB_LEN);

		user_dlm_lock_res_init(&ip->ip_lockres, dentry);

		/* released at clear_inode समय, this insures that we
		 * get to drop the dlm reference on each lock *beक्रमe*
		 * we call the unरेजिस्टर code क्रम releasing parent
		 * directories. */
		ip->ip_parent = igrab(parent);
		BUG_ON(!ip->ip_parent);
		अवरोध;
	हाल S_IFसूची:
		inode->i_op = &dlmfs_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;

		/* directory inodes start off with i_nlink ==
		 * 2 (क्रम "." entry) */
		inc_nlink(inode);
		अवरोध;
	पूर्ण
	वापस inode;
पूर्ण

/*
 * File creation. Allocate an inode, and we're करोne..
 */
/* SMP-safe */
अटल पूर्णांक dlmfs_सूची_गढ़ो(काष्ठा user_namespace * mnt_userns,
		       काष्ठा inode * dir,
		       काष्ठा dentry * dentry,
		       umode_t mode)
अणु
	पूर्णांक status;
	काष्ठा inode *inode = शून्य;
	स्थिर काष्ठा qstr *करोमुख्य = &dentry->d_name;
	काष्ठा dlmfs_inode_निजी *ip;
	काष्ठा ocfs2_cluster_connection *conn;

	mlog(0, "mkdir %.*s\n", करोमुख्य->len, करोमुख्य->name);

	/* verअगरy that we have a proper करोमुख्य */
	अगर (करोमुख्य->len >= GROUP_NAME_MAX) अणु
		status = -EINVAL;
		mlog(ML_ERROR, "invalid domain name for directory.\n");
		जाओ bail;
	पूर्ण

	inode = dlmfs_get_inode(dir, dentry, mode | S_IFसूची);
	अगर (!inode) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	ip = DLMFS_I(inode);

	conn = user_dlm_रेजिस्टर(करोमुख्य);
	अगर (IS_ERR(conn)) अणु
		status = PTR_ERR(conn);
		mlog(ML_ERROR, "Error %d could not register domain \"%.*s\"\n",
		     status, करोमुख्य->len, करोमुख्य->name);
		जाओ bail;
	पूर्ण
	ip->ip_conn = conn;

	inc_nlink(dir);
	d_instantiate(dentry, inode);
	dget(dentry);	/* Extra count - pin the dentry in core */

	status = 0;
bail:
	अगर (status < 0)
		iput(inode);
	वापस status;
पूर्ण

अटल पूर्णांक dlmfs_create(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *dir,
			काष्ठा dentry *dentry,
			umode_t mode,
			bool excl)
अणु
	पूर्णांक status = 0;
	काष्ठा inode *inode;
	स्थिर काष्ठा qstr *name = &dentry->d_name;

	mlog(0, "create %.*s\n", name->len, name->name);

	/* verअगरy name is valid and करोesn't contain any dlm reserved
	 * अक्षरacters */
	अगर (name->len >= USER_DLM_LOCK_ID_MAX_LEN ||
	    name->name[0] == '$') अणु
		status = -EINVAL;
		mlog(ML_ERROR, "invalid lock name, %.*s\n", name->len,
		     name->name);
		जाओ bail;
	पूर्ण

	inode = dlmfs_get_inode(dir, dentry, mode | S_IFREG);
	अगर (!inode) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	d_instantiate(dentry, inode);
	dget(dentry);	/* Extra count - pin the dentry in core */
bail:
	वापस status;
पूर्ण

अटल पूर्णांक dlmfs_unlink(काष्ठा inode *dir,
			काष्ठा dentry *dentry)
अणु
	पूर्णांक status;
	काष्ठा inode *inode = d_inode(dentry);

	mlog(0, "unlink inode %lu\n", inode->i_ino);

	/* अगर there are no current holders, or none that are रुकोing
	 * to acquire a lock, this basically destroys our lockres. */
	status = user_dlm_destroy_lock(&DLMFS_I(inode)->ip_lockres);
	अगर (status < 0) अणु
		mlog(ML_ERROR, "unlink %pd, error %d from destroy\n",
		     dentry, status);
		जाओ bail;
	पूर्ण
	status = simple_unlink(dir, dentry);
bail:
	वापस status;
पूर्ण

अटल पूर्णांक dlmfs_fill_super(काष्ठा super_block * sb,
			    व्योम * data,
			    पूर्णांक silent)
अणु
	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = DLMFS_MAGIC;
	sb->s_op = &dlmfs_ops;
	sb->s_root = d_make_root(dlmfs_get_root_inode(sb));
	अगर (!sb->s_root)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations dlmfs_file_operations = अणु
	.खोलो		= dlmfs_file_खोलो,
	.release	= dlmfs_file_release,
	.poll		= dlmfs_file_poll,
	.पढ़ो		= dlmfs_file_पढ़ो,
	.ग_लिखो		= dlmfs_file_ग_लिखो,
	.llseek		= शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा inode_operations dlmfs_dir_inode_operations = अणु
	.create		= dlmfs_create,
	.lookup		= simple_lookup,
	.unlink		= dlmfs_unlink,
पूर्ण;

/* this way we can restrict सूची_गढ़ो to only the toplevel of the fs. */
अटल स्थिर काष्ठा inode_operations dlmfs_root_inode_operations = अणु
	.lookup		= simple_lookup,
	.सूची_गढ़ो		= dlmfs_सूची_गढ़ो,
	.सूची_हटाओ		= simple_सूची_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा super_operations dlmfs_ops = अणु
	.statfs		= simple_statfs,
	.alloc_inode	= dlmfs_alloc_inode,
	.मुक्त_inode	= dlmfs_मुक्त_inode,
	.evict_inode	= dlmfs_evict_inode,
	.drop_inode	= generic_delete_inode,
पूर्ण;

अटल स्थिर काष्ठा inode_operations dlmfs_file_inode_operations = अणु
	.getattr	= simple_getattr,
	.setattr	= dlmfs_file_setattr,
पूर्ण;

अटल काष्ठा dentry *dlmfs_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_nodev(fs_type, flags, data, dlmfs_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type dlmfs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "ocfs2_dlmfs",
	.mount		= dlmfs_mount,
	.समाप्त_sb	= समाप्त_litter_super,
पूर्ण;
MODULE_ALIAS_FS("ocfs2_dlmfs");

अटल पूर्णांक __init init_dlmfs_fs(व्योम)
अणु
	पूर्णांक status;
	पूर्णांक cleanup_inode = 0, cleanup_worker = 0;

	dlmfs_inode_cache = kmem_cache_create("dlmfs_inode_cache",
				माप(काष्ठा dlmfs_inode_निजी),
				0, (SLAB_HWCACHE_ALIGN|SLAB_RECLAIM_ACCOUNT|
					SLAB_MEM_SPREAD|SLAB_ACCOUNT),
				dlmfs_init_once);
	अगर (!dlmfs_inode_cache) अणु
		status = -ENOMEM;
		जाओ bail;
	पूर्ण
	cleanup_inode = 1;

	user_dlm_worker = alloc_workqueue("user_dlm", WQ_MEM_RECLAIM, 0);
	अगर (!user_dlm_worker) अणु
		status = -ENOMEM;
		जाओ bail;
	पूर्ण
	cleanup_worker = 1;

	user_dlm_set_locking_protocol();
	status = रेजिस्टर_fileप्रणाली(&dlmfs_fs_type);
bail:
	अगर (status) अणु
		अगर (cleanup_inode)
			kmem_cache_destroy(dlmfs_inode_cache);
		अगर (cleanup_worker)
			destroy_workqueue(user_dlm_worker);
	पूर्ण अन्यथा
		prपूर्णांकk("OCFS2 User DLM kernel interface loaded\n");
	वापस status;
पूर्ण

अटल व्योम __निकास निकास_dlmfs_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&dlmfs_fs_type);

	destroy_workqueue(user_dlm_worker);

	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(dlmfs_inode_cache);

पूर्ण

MODULE_AUTHOR("Oracle");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("OCFS2 DLM-Filesystem");

module_init(init_dlmfs_fs)
module_निकास(निकास_dlmfs_fs)
