<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Super block/fileप्रणाली wide operations
 *
 * Copyright (C) 1996 Peter J. Braam <braam@maths.ox.ac.uk> and 
 * Michael Callahan <callahan@maths.ox.ac.uk> 
 * 
 * Rewritten क्रम Linux 2.1.  Peter Braam <braam@cs.cmu.edu>
 * Copyright (C) Carnegie Mellon University
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/unistd.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/file.h>
#समावेश <linux/vfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fs.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/coda.h>
#समावेश "coda_psdev.h"
#समावेश "coda_linux.h"
#समावेश "coda_cache.h"

#समावेश "coda_int.h"

/* VFS super_block ops */
अटल व्योम coda_evict_inode(काष्ठा inode *);
अटल व्योम coda_put_super(काष्ठा super_block *);
अटल पूर्णांक coda_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf);

अटल काष्ठा kmem_cache * coda_inode_cachep;

अटल काष्ठा inode *coda_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा coda_inode_info *ei;
	ei = kmem_cache_alloc(coda_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;
	स_रखो(&ei->c_fid, 0, माप(काष्ठा CodaFid));
	ei->c_flags = 0;
	ei->c_uid = GLOBAL_ROOT_UID;
	ei->c_cached_perm = 0;
	spin_lock_init(&ei->c_lock);
	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम coda_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(coda_inode_cachep, ITOC(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा coda_inode_info *ei = (काष्ठा coda_inode_info *) foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण

पूर्णांक __init coda_init_inodecache(व्योम)
अणु
	coda_inode_cachep = kmem_cache_create("coda_inode_cache",
				माप(काष्ठा coda_inode_info), 0,
				SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD|
				SLAB_ACCOUNT, init_once);
	अगर (coda_inode_cachep == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम coda_destroy_inodecache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(coda_inode_cachep);
पूर्ण

अटल पूर्णांक coda_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	sync_fileप्रणाली(sb);
	*flags |= SB_NOATIME;
	वापस 0;
पूर्ण

/* exported operations */
अटल स्थिर काष्ठा super_operations coda_super_operations =
अणु
	.alloc_inode	= coda_alloc_inode,
	.मुक्त_inode	= coda_मुक्त_inode,
	.evict_inode	= coda_evict_inode,
	.put_super	= coda_put_super,
	.statfs		= coda_statfs,
	.remount_fs	= coda_remount,
पूर्ण;

अटल पूर्णांक get_device_index(काष्ठा coda_mount_data *data)
अणु
	काष्ठा fd f;
	काष्ठा inode *inode;
	पूर्णांक idx;

	अगर (data == शून्य) अणु
		pr_warn("%s: Bad mount data\n", __func__);
		वापस -1;
	पूर्ण

	अगर (data->version != CODA_MOUNT_VERSION) अणु
		pr_warn("%s: Bad mount version\n", __func__);
		वापस -1;
	पूर्ण

	f = fdget(data->fd);
	अगर (!f.file)
		जाओ Ebadf;
	inode = file_inode(f.file);
	अगर (!S_ISCHR(inode->i_mode) || imajor(inode) != CODA_PSDEV_MAJOR) अणु
		fdput(f);
		जाओ Ebadf;
	पूर्ण

	idx = iminor(inode);
	fdput(f);

	अगर (idx < 0 || idx >= MAX_CODADEVS) अणु
		pr_warn("%s: Bad minor number\n", __func__);
		वापस -1;
	पूर्ण

	वापस idx;
Ebadf:
	pr_warn("%s: Bad file\n", __func__);
	वापस -1;
पूर्ण

अटल पूर्णांक coda_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा inode *root = शून्य;
	काष्ठा venus_comm *vc;
	काष्ठा CodaFid fid;
	पूर्णांक error;
	पूर्णांक idx;

	अगर (task_active_pid_ns(current) != &init_pid_ns)
		वापस -EINVAL;

	idx = get_device_index((काष्ठा coda_mount_data *) data);

	/* Ignore errors in data, क्रम backward compatibility */
	अगर(idx == -1)
		idx = 0;
	
	pr_info("%s: device index: %i\n", __func__,  idx);

	vc = &coda_comms[idx];
	mutex_lock(&vc->vc_mutex);

	अगर (!vc->vc_inuse) अणु
		pr_warn("%s: No pseudo device\n", __func__);
		error = -EINVAL;
		जाओ unlock_out;
	पूर्ण

	अगर (vc->vc_sb) अणु
		pr_warn("%s: Device already mounted\n", __func__);
		error = -EBUSY;
		जाओ unlock_out;
	पूर्ण

	vc->vc_sb = sb;
	mutex_unlock(&vc->vc_mutex);

	sb->s_fs_info = vc;
	sb->s_flags |= SB_NOATIME;
	sb->s_blocksize = 4096;	/* XXXXX  what करो we put here?? */
	sb->s_blocksize_bits = 12;
	sb->s_magic = CODA_SUPER_MAGIC;
	sb->s_op = &coda_super_operations;
	sb->s_d_op = &coda_dentry_operations;
	sb->s_समय_gran = 1;
	sb->s_समय_min = S64_MIN;
	sb->s_समय_max = S64_MAX;

	error = super_setup_bdi(sb);
	अगर (error)
		जाओ error;

	/* get root fid from Venus: this needs the root inode */
	error = venus_rootfid(sb, &fid);
	अगर ( error ) अणु
		pr_warn("%s: coda_get_rootfid failed with %d\n",
			__func__, error);
		जाओ error;
	पूर्ण
	pr_info("%s: rootfid is %s\n", __func__, coda_f2s(&fid));
	
	/* make root inode */
        root = coda_cnode_make(&fid, sb);
        अगर (IS_ERR(root)) अणु
		error = PTR_ERR(root);
		pr_warn("Failure of coda_cnode_make for root: error %d\n",
			error);
		जाओ error;
	पूर्ण 

	pr_info("%s: rootinode is %ld dev %s\n",
		__func__, root->i_ino, root->i_sb->s_id);
	sb->s_root = d_make_root(root);
	अगर (!sb->s_root) अणु
		error = -EINVAL;
		जाओ error;
	पूर्ण
	वापस 0;

error:
	mutex_lock(&vc->vc_mutex);
	vc->vc_sb = शून्य;
	sb->s_fs_info = शून्य;
unlock_out:
	mutex_unlock(&vc->vc_mutex);
	वापस error;
पूर्ण

अटल व्योम coda_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा venus_comm *vcp = coda_vcp(sb);
	mutex_lock(&vcp->vc_mutex);
	vcp->vc_sb = शून्य;
	sb->s_fs_info = शून्य;
	mutex_unlock(&vcp->vc_mutex);
	mutex_destroy(&vcp->vc_mutex);

	pr_info("Bye bye.\n");
पूर्ण

अटल व्योम coda_evict_inode(काष्ठा inode *inode)
अणु
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	coda_cache_clear_inode(inode);
पूर्ण

पूर्णांक coda_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		 काष्ठा kstat *stat, u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err = coda_revalidate_inode(d_inode(path->dentry));
	अगर (!err)
		generic_fillattr(&init_user_ns, d_inode(path->dentry), stat);
	वापस err;
पूर्ण

पूर्णांक coda_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *de,
		 काष्ठा iattr *iattr)
अणु
	काष्ठा inode *inode = d_inode(de);
	काष्ठा coda_vattr vattr;
	पूर्णांक error;

	स_रखो(&vattr, 0, माप(vattr)); 

	inode->i_स_समय = current_समय(inode);
	coda_iattr_to_vattr(iattr, &vattr);
	vattr.va_type = C_VNON; /* cannot set type */

	/* Venus is responsible क्रम truncating the container-file!!! */
	error = venus_setattr(inode->i_sb, coda_i2f(inode), &vattr);

	अगर (!error) अणु
	        coda_vattr_to_iattr(inode, &vattr); 
		coda_cache_clear_inode(inode);
	पूर्ण
	वापस error;
पूर्ण

स्थिर काष्ठा inode_operations coda_file_inode_operations = अणु
	.permission	= coda_permission,
	.getattr	= coda_getattr,
	.setattr	= coda_setattr,
पूर्ण;

अटल पूर्णांक coda_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	पूर्णांक error;
	
	error = venus_statfs(dentry, buf);

	अगर (error) अणु
		/* fake something like AFS करोes */
		buf->f_blocks = 9000000;
		buf->f_bमुक्त  = 9000000;
		buf->f_bavail = 9000000;
		buf->f_files  = 9000000;
		buf->f_fमुक्त  = 9000000;
	पूर्ण

	/* and fill in the rest */
	buf->f_type = CODA_SUPER_MAGIC;
	buf->f_bsize = 4096;
	buf->f_namelen = CODA_MAXNAMLEN;

	वापस 0; 
पूर्ण

/* init_coda: used by fileप्रणालीs.c to रेजिस्टर coda */

अटल काष्ठा dentry *coda_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_nodev(fs_type, flags, data, coda_fill_super);
पूर्ण

काष्ठा file_प्रणाली_type coda_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "coda",
	.mount		= coda_mount,
	.समाप्त_sb	= समाप्त_anon_super,
	.fs_flags	= FS_BINARY_MOUNTDATA,
पूर्ण;
MODULE_ALIAS_FS("coda");

