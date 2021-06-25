<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012 Bryan Schumaker <bjschuma@netapp.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <linux/nfs4_mount.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_ssc.h>
#समावेश "delegation.h"
#समावेश "internal.h"
#समावेश "nfs4_fs.h"
#समावेश "nfs4idmap.h"
#समावेश "dns_resolve.h"
#समावेश "pnfs.h"
#समावेश "nfs.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_VFS

अटल पूर्णांक nfs4_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc);
अटल व्योम nfs4_evict_inode(काष्ठा inode *inode);

अटल स्थिर काष्ठा super_operations nfs4_sops = अणु
	.alloc_inode	= nfs_alloc_inode,
	.मुक्त_inode	= nfs_मुक्त_inode,
	.ग_लिखो_inode	= nfs4_ग_लिखो_inode,
	.drop_inode	= nfs_drop_inode,
	.statfs		= nfs_statfs,
	.evict_inode	= nfs4_evict_inode,
	.umount_begin	= nfs_umount_begin,
	.show_options	= nfs_show_options,
	.show_devname	= nfs_show_devname,
	.show_path	= nfs_show_path,
	.show_stats	= nfs_show_stats,
पूर्ण;

काष्ठा nfs_subversion nfs_v4 = अणु
	.owner		= THIS_MODULE,
	.nfs_fs		= &nfs4_fs_type,
	.rpc_vers	= &nfs_version4,
	.rpc_ops	= &nfs_v4_clientops,
	.sops		= &nfs4_sops,
	.xattr		= nfs4_xattr_handlers,
पूर्ण;

अटल पूर्णांक nfs4_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक ret = nfs_ग_लिखो_inode(inode, wbc);

	अगर (ret == 0)
		ret = pnfs_layoutcommit_inode(inode,
				wbc->sync_mode == WB_SYNC_ALL);
	वापस ret;
पूर्ण

/*
 * Clean out any reमुख्यing NFSv4 state that might be left over due
 * to खोलो() calls that passed nfs_atomic_lookup, but failed to call
 * nfs_खोलो().
 */
अटल व्योम nfs4_evict_inode(काष्ठा inode *inode)
अणु
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	/* If we are holding a delegation, वापस and मुक्त it */
	nfs_inode_evict_delegation(inode);
	/* Note that above delegवापस would trigger pnfs वापस-on-बंद */
	pnfs_वापस_layout(inode);
	pnfs_destroy_layout_final(NFS_I(inode));
	/* First call standard NFS clear_inode() code */
	nfs_clear_inode(inode);
	nfs4_xattr_cache_zap(inode);
पूर्ण

काष्ठा nfs_referral_count अणु
	काष्ठा list_head list;
	स्थिर काष्ठा task_काष्ठा *task;
	अचिन्हित पूर्णांक referral_count;
पूर्ण;

अटल LIST_HEAD(nfs_referral_count_list);
अटल DEFINE_SPINLOCK(nfs_referral_count_list_lock);

अटल काष्ठा nfs_referral_count *nfs_find_referral_count(व्योम)
अणु
	काष्ठा nfs_referral_count *p;

	list_क्रम_each_entry(p, &nfs_referral_count_list, list) अणु
		अगर (p->task == current)
			वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा NFS_MAX_NESTED_REFERRALS 2

अटल पूर्णांक nfs_referral_loop_protect(व्योम)
अणु
	काष्ठा nfs_referral_count *p, *new;
	पूर्णांक ret = -ENOMEM;

	new = kदो_स्मृति(माप(*new), GFP_KERNEL);
	अगर (!new)
		जाओ out;
	new->task = current;
	new->referral_count = 1;

	ret = 0;
	spin_lock(&nfs_referral_count_list_lock);
	p = nfs_find_referral_count();
	अगर (p != शून्य) अणु
		अगर (p->referral_count >= NFS_MAX_NESTED_REFERRALS)
			ret = -ELOOP;
		अन्यथा
			p->referral_count++;
	पूर्ण अन्यथा अणु
		list_add(&new->list, &nfs_referral_count_list);
		new = शून्य;
	पूर्ण
	spin_unlock(&nfs_referral_count_list_lock);
	kमुक्त(new);
out:
	वापस ret;
पूर्ण

अटल व्योम nfs_referral_loop_unprotect(व्योम)
अणु
	काष्ठा nfs_referral_count *p;

	spin_lock(&nfs_referral_count_list_lock);
	p = nfs_find_referral_count();
	p->referral_count--;
	अगर (p->referral_count == 0)
		list_del(&p->list);
	अन्यथा
		p = शून्य;
	spin_unlock(&nfs_referral_count_list_lock);
	kमुक्त(p);
पूर्ण

अटल पूर्णांक करो_nfs4_mount(काष्ठा nfs_server *server,
			 काष्ठा fs_context *fc,
			 स्थिर अक्षर *hostname,
			 स्थिर अक्षर *export_path)
अणु
	काष्ठा nfs_fs_context *root_ctx;
	काष्ठा fs_context *root_fc;
	काष्ठा vfsmount *root_mnt;
	काष्ठा dentry *dentry;
	माप_प्रकार len;
	पूर्णांक ret;

	काष्ठा fs_parameter param = अणु
		.key	= "source",
		.type	= fs_value_is_string,
		.dirfd	= -1,
	पूर्ण;

	अगर (IS_ERR(server))
		वापस PTR_ERR(server);

	root_fc = vfs_dup_fs_context(fc);
	अगर (IS_ERR(root_fc)) अणु
		nfs_मुक्त_server(server);
		वापस PTR_ERR(root_fc);
	पूर्ण
	kमुक्त(root_fc->source);
	root_fc->source = शून्य;

	root_ctx = nfs_fc2context(root_fc);
	root_ctx->पूर्णांकernal = true;
	root_ctx->server = server;
	/* We leave export_path unset as it's not used to find the root. */

	len = म_माप(hostname) + 5;
	param.string = kदो_स्मृति(len, GFP_KERNEL);
	अगर (param.string == शून्य) अणु
		put_fs_context(root_fc);
		वापस -ENOMEM;
	पूर्ण

	/* Does hostname needs to be enबंदd in brackets? */
	अगर (म_अक्षर(hostname, ':'))
		param.size = snम_लिखो(param.string, len, "[%s]:/", hostname);
	अन्यथा
		param.size = snम_लिखो(param.string, len, "%s:/", hostname);
	ret = vfs_parse_fs_param(root_fc, &param);
	kमुक्त(param.string);
	अगर (ret < 0) अणु
		put_fs_context(root_fc);
		वापस ret;
	पूर्ण
	root_mnt = fc_mount(root_fc);
	put_fs_context(root_fc);

	अगर (IS_ERR(root_mnt))
		वापस PTR_ERR(root_mnt);

	ret = nfs_referral_loop_protect();
	अगर (ret) अणु
		mntput(root_mnt);
		वापस ret;
	पूर्ण

	dentry = mount_subtree(root_mnt, export_path);
	nfs_referral_loop_unprotect();

	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	fc->root = dentry;
	वापस 0;
पूर्ण

पूर्णांक nfs4_try_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	पूर्णांक err;

	dfprपूर्णांकk(MOUNT, "--> nfs4_try_get_tree()\n");

	/* We create a mount क्रम the server's root, walk to the requested
	 * location and then create another mount क्रम that.
	 */
	err= करो_nfs4_mount(nfs4_create_server(fc),
			   fc, ctx->nfs_server.hostname,
			   ctx->nfs_server.export_path);
	अगर (err) अणु
		nfs_ख_त्रुटिf(fc, MOUNT, "NFS4: Couldn't follow remote path");
		dfprपूर्णांकk(MOUNT, "<-- nfs4_try_get_tree() = %d [error]\n", err);
	पूर्ण अन्यथा अणु
		dfprपूर्णांकk(MOUNT, "<-- nfs4_try_get_tree() = 0\n");
	पूर्ण
	वापस err;
पूर्ण

/*
 * Create an NFS4 server record on referral traversal
 */
पूर्णांक nfs4_get_referral_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	पूर्णांक err;

	dprपूर्णांकk("--> nfs4_referral_mount()\n");

	/* create a new volume representation */
	err = करो_nfs4_mount(nfs4_create_referral_server(fc),
			    fc, ctx->nfs_server.hostname,
			    ctx->nfs_server.export_path);
	अगर (err) अणु
		nfs_ख_त्रुटिf(fc, MOUNT, "NFS4: Couldn't follow remote path");
		dfprपूर्णांकk(MOUNT, "<-- nfs4_get_referral_tree() = %d [error]\n", err);
	पूर्ण अन्यथा अणु
		dfprपूर्णांकk(MOUNT, "<-- nfs4_get_referral_tree() = 0\n");
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __init init_nfs_v4(व्योम)
अणु
	पूर्णांक err;

	err = nfs_dns_resolver_init();
	अगर (err)
		जाओ out;

	err = nfs_idmap_init();
	अगर (err)
		जाओ out1;

#अगर_घोषित CONFIG_NFS_V4_2
	err = nfs4_xattr_cache_init();
	अगर (err)
		जाओ out2;
#पूर्ण_अगर

	err = nfs4_रेजिस्टर_sysctl();
	अगर (err)
		जाओ out2;

#अगर_घोषित CONFIG_NFS_V4_2
	nfs42_ssc_रेजिस्टर_ops();
#पूर्ण_अगर
	रेजिस्टर_nfs_version(&nfs_v4);
	वापस 0;
out2:
	nfs_idmap_quit();
out1:
	nfs_dns_resolver_destroy();
out:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_nfs_v4(व्योम)
अणु
	/* Not called in the _init(), conditionally loaded */
	nfs4_pnfs_v3_ds_connect_unload();

	unरेजिस्टर_nfs_version(&nfs_v4);
#अगर_घोषित CONFIG_NFS_V4_2
	nfs4_xattr_cache_निकास();
	nfs42_ssc_unरेजिस्टर_ops();
#पूर्ण_अगर
	nfs4_unरेजिस्टर_sysctl();
	nfs_idmap_quit();
	nfs_dns_resolver_destroy();
पूर्ण

MODULE_LICENSE("GPL");

module_init(init_nfs_v4);
module_निकास(निकास_nfs_v4);
