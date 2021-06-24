<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* getroot.c: get the root dentry क्रम an NFS mount
 *
 * Copyright (C) 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>

#समावेश <linux/समय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/unistd.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/lockd/bind.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mount.h>
#समावेश <linux/vfs.h>
#समावेश <linux/namei.h>
#समावेश <linux/security.h>

#समावेश <linux/uaccess.h>

#समावेश "internal.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_CLIENT

/*
 * Set the superblock root dentry.
 * Note that this function मुक्तs the inode in हाल of error.
 */
अटल पूर्णांक nfs_superblock_set_dummy_root(काष्ठा super_block *sb, काष्ठा inode *inode)
अणु
	/* The mntroot acts as the dummy root dentry क्रम this superblock */
	अगर (sb->s_root == शून्य) अणु
		sb->s_root = d_make_root(inode);
		अगर (sb->s_root == शून्य)
			वापस -ENOMEM;
		ihold(inode);
		/*
		 * Ensure that this dentry is invisible to d_find_alias().
		 * Otherwise, it may be spliced पूर्णांकo the tree by
		 * d_splice_alias अगर a parent directory from the same
		 * fileप्रणाली माला_लो mounted at a later समय.
		 * This again causes shrink_dcache_क्रम_umount_subtree() to
		 * Oops, since the test क्रम IS_ROOT() will fail.
		 */
		spin_lock(&d_inode(sb->s_root)->i_lock);
		spin_lock(&sb->s_root->d_lock);
		hlist_del_init(&sb->s_root->d_u.d_alias);
		spin_unlock(&sb->s_root->d_lock);
		spin_unlock(&d_inode(sb->s_root)->i_lock);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * get an NFS2/NFS3 root dentry from the root filehandle
 */
पूर्णांक nfs_get_root(काष्ठा super_block *s, काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा nfs_server *server = NFS_SB(s);
	काष्ठा nfs_fsinfo fsinfo;
	काष्ठा dentry *root;
	काष्ठा inode *inode;
	अक्षर *name;
	पूर्णांक error = -ENOMEM;
	अचिन्हित दीर्घ kflags = 0, kflags_out = 0;

	name = kstrdup(fc->source, GFP_KERNEL);
	अगर (!name)
		जाओ out;

	/* get the actual root क्रम this mount */
	fsinfo.fattr = nfs_alloc_fattr();
	अगर (fsinfo.fattr == शून्य)
		जाओ out_name;

	fsinfo.fattr->label = nfs4_label_alloc(server, GFP_KERNEL);
	अगर (IS_ERR(fsinfo.fattr->label))
		जाओ out_fattr;
	error = server->nfs_client->rpc_ops->getroot(server, ctx->mntfh, &fsinfo);
	अगर (error < 0) अणु
		dprपूर्णांकk("nfs_get_root: getattr error = %d\n", -error);
		nfs_errorf(fc, "NFS: Couldn't getattr on root");
		जाओ out_label;
	पूर्ण

	inode = nfs_fhget(s, ctx->mntfh, fsinfo.fattr, शून्य);
	अगर (IS_ERR(inode)) अणु
		dprपूर्णांकk("nfs_get_root: get root inode failed\n");
		error = PTR_ERR(inode);
		nfs_errorf(fc, "NFS: Couldn't get root inode");
		जाओ out_label;
	पूर्ण

	error = nfs_superblock_set_dummy_root(s, inode);
	अगर (error != 0)
		जाओ out_label;

	/* root dentries normally start off anonymous and get spliced in later
	 * अगर the dentry tree reaches them; however अगर the dentry alपढ़ोy
	 * exists, we'll pick it up at this poपूर्णांक and use it as the root
	 */
	root = d_obtain_root(inode);
	अगर (IS_ERR(root)) अणु
		dprपूर्णांकk("nfs_get_root: get root dentry failed\n");
		error = PTR_ERR(root);
		nfs_errorf(fc, "NFS: Couldn't get root dentry");
		जाओ out_label;
	पूर्ण

	security_d_instantiate(root, inode);
	spin_lock(&root->d_lock);
	अगर (IS_ROOT(root) && !root->d_fsdata &&
	    !(root->d_flags & DCACHE_NFSFS_RENAMED)) अणु
		root->d_fsdata = name;
		name = शून्य;
	पूर्ण
	spin_unlock(&root->d_lock);
	fc->root = root;
	अगर (NFS_SB(s)->caps & NFS_CAP_SECURITY_LABEL)
		kflags |= SECURITY_LSM_NATIVE_LABELS;
	अगर (ctx->clone_data.sb) अणु
		अगर (d_inode(fc->root)->i_fop != &nfs_dir_operations) अणु
			error = -ESTALE;
			जाओ error_splat_root;
		पूर्ण
		/* clone lsm security options from the parent to the new sb */
		error = security_sb_clone_mnt_opts(ctx->clone_data.sb,
						   s, kflags, &kflags_out);
	पूर्ण अन्यथा अणु
		error = security_sb_set_mnt_opts(s, fc->security,
							kflags, &kflags_out);
	पूर्ण
	अगर (error)
		जाओ error_splat_root;
	अगर (NFS_SB(s)->caps & NFS_CAP_SECURITY_LABEL &&
		!(kflags_out & SECURITY_LSM_NATIVE_LABELS))
		NFS_SB(s)->caps &= ~NFS_CAP_SECURITY_LABEL;

	nfs_setsecurity(inode, fsinfo.fattr, fsinfo.fattr->label);
	error = 0;

out_label:
	nfs4_label_मुक्त(fsinfo.fattr->label);
out_fattr:
	nfs_मुक्त_fattr(fsinfo.fattr);
out_name:
	kमुक्त(name);
out:
	वापस error;
error_splat_root:
	dput(fc->root);
	fc->root = शून्य;
	जाओ out_label;
पूर्ण
