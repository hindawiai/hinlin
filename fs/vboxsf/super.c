<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * VirtualBox Guest Shared Folders support: Virtual File System.
 *
 * Module initialization/finalization
 * File प्रणाली registration/deregistration
 * Superblock पढ़ोing
 * Few utility functions
 *
 * Copyright (C) 2006-2018 Oracle Corporation
 */

#समावेश <linux/idr.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/magic.h>
#समावेश <linux/module.h>
#समावेश <linux/nls.h>
#समावेश <linux/statfs.h>
#समावेश <linux/vbox_utils.h>
#समावेश "vfsmod.h"

#घोषणा VBOXSF_SUPER_MAGIC 0x786f4256 /* 'VBox' little endian */

#घोषणा VBSF_MOUNT_SIGNATURE_BYTE_0 ('\000')
#घोषणा VBSF_MOUNT_SIGNATURE_BYTE_1 ('\377')
#घोषणा VBSF_MOUNT_SIGNATURE_BYTE_2 ('\376')
#घोषणा VBSF_MOUNT_SIGNATURE_BYTE_3 ('\375')

अटल पूर्णांक follow_symlinks;
module_param(follow_symlinks, पूर्णांक, 0444);
MODULE_PARM_DESC(follow_symlinks,
		 "Let host resolve symlinks rather than showing them");

अटल DEFINE_IDA(vboxsf_bdi_ida);
अटल DEFINE_MUTEX(vboxsf_setup_mutex);
अटल bool vboxsf_setup_करोne;
अटल काष्ठा super_operations vboxsf_super_ops; /* क्रमward declaration */
अटल काष्ठा kmem_cache *vboxsf_inode_cachep;

अटल अक्षर * स्थिर vboxsf_शेष_nls = CONFIG_NLS_DEFAULT;

क्रमागत  अणु opt_nls, opt_uid, opt_gid, opt_ttl, opt_dmode, opt_भ_शेषe,
	opt_dmask, opt_fmask पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec vboxsf_fs_parameters[] = अणु
	fsparam_string	("nls",		opt_nls),
	fsparam_u32	("uid",		opt_uid),
	fsparam_u32	("gid",		opt_gid),
	fsparam_u32	("ttl",		opt_ttl),
	fsparam_u32oct	("dmode",	opt_dmode),
	fsparam_u32oct	("fmode",	opt_भ_शेषe),
	fsparam_u32oct	("dmask",	opt_dmask),
	fsparam_u32oct	("fmask",	opt_fmask),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक vboxsf_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा vboxsf_fs_context *ctx = fc->fs_निजी;
	काष्ठा fs_parse_result result;
	kuid_t uid;
	kgid_t gid;
	पूर्णांक opt;

	opt = fs_parse(fc, vboxsf_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल opt_nls:
		अगर (ctx->nls_name || fc->purpose != FS_CONTEXT_FOR_MOUNT) अणु
			vbg_err("vboxsf: Cannot reconfigure nls option\n");
			वापस -EINVAL;
		पूर्ण
		ctx->nls_name = param->string;
		param->string = शून्य;
		अवरोध;
	हाल opt_uid:
		uid = make_kuid(current_user_ns(), result.uपूर्णांक_32);
		अगर (!uid_valid(uid))
			वापस -EINVAL;
		ctx->o.uid = uid;
		अवरोध;
	हाल opt_gid:
		gid = make_kgid(current_user_ns(), result.uपूर्णांक_32);
		अगर (!gid_valid(gid))
			वापस -EINVAL;
		ctx->o.gid = gid;
		अवरोध;
	हाल opt_ttl:
		ctx->o.ttl = msecs_to_jअगरfies(result.uपूर्णांक_32);
		अवरोध;
	हाल opt_dmode:
		अगर (result.uपूर्णांक_32 & ~0777)
			वापस -EINVAL;
		ctx->o.dmode = result.uपूर्णांक_32;
		ctx->o.dmode_set = true;
		अवरोध;
	हाल opt_भ_शेषe:
		अगर (result.uपूर्णांक_32 & ~0777)
			वापस -EINVAL;
		ctx->o.भ_शेषe = result.uपूर्णांक_32;
		ctx->o.भ_शेषe_set = true;
		अवरोध;
	हाल opt_dmask:
		अगर (result.uपूर्णांक_32 & ~07777)
			वापस -EINVAL;
		ctx->o.dmask = result.uपूर्णांक_32;
		अवरोध;
	हाल opt_fmask:
		अगर (result.uपूर्णांक_32 & ~07777)
			वापस -EINVAL;
		ctx->o.fmask = result.uपूर्णांक_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vboxsf_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा vboxsf_fs_context *ctx = fc->fs_निजी;
	काष्ठा shfl_string *folder_name, root_path;
	काष्ठा vboxsf_sbi *sbi;
	काष्ठा dentry *droot;
	काष्ठा inode *iroot;
	अक्षर *nls_name;
	माप_प्रकार size;
	पूर्णांक err;

	अगर (!fc->source)
		वापस -EINVAL;

	sbi = kzalloc(माप(*sbi), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;

	sbi->o = ctx->o;
	idr_init(&sbi->ino_idr);
	spin_lock_init(&sbi->ino_idr_lock);
	sbi->next_generation = 1;
	sbi->bdi_id = -1;

	/* Load nls अगर not utf8 */
	nls_name = ctx->nls_name ? ctx->nls_name : vboxsf_शेष_nls;
	अगर (म_भेद(nls_name, "utf8") != 0) अणु
		अगर (nls_name == vboxsf_शेष_nls)
			sbi->nls = load_nls_शेष();
		अन्यथा
			sbi->nls = load_nls(nls_name);

		अगर (!sbi->nls) अणु
			vbg_err("vboxsf: Count not load '%s' nls\n", nls_name);
			err = -EINVAL;
			जाओ fail_मुक्त;
		पूर्ण
	पूर्ण

	sbi->bdi_id = ida_simple_get(&vboxsf_bdi_ida, 0, 0, GFP_KERNEL);
	अगर (sbi->bdi_id < 0) अणु
		err = sbi->bdi_id;
		जाओ fail_मुक्त;
	पूर्ण

	err = super_setup_bdi_name(sb, "vboxsf-%d", sbi->bdi_id);
	अगर (err)
		जाओ fail_मुक्त;
	sb->s_bdi->ra_pages = 0;
	sb->s_bdi->io_pages = 0;

	/* Turn source पूर्णांकo a shfl_string and map the folder */
	size = म_माप(fc->source) + 1;
	folder_name = kदो_स्मृति(SHFLSTRING_HEADER_SIZE + size, GFP_KERNEL);
	अगर (!folder_name) अणु
		err = -ENOMEM;
		जाओ fail_मुक्त;
	पूर्ण
	folder_name->size = size;
	folder_name->length = size - 1;
	strlcpy(folder_name->string.utf8, fc->source, size);
	err = vboxsf_map_folder(folder_name, &sbi->root);
	kमुक्त(folder_name);
	अगर (err) अणु
		vbg_err("vboxsf: Host rejected mount of '%s' with error %d\n",
			fc->source, err);
		जाओ fail_मुक्त;
	पूर्ण

	root_path.length = 1;
	root_path.size = 2;
	root_path.string.utf8[0] = '/';
	root_path.string.utf8[1] = 0;
	err = vboxsf_stat(sbi, &root_path, &sbi->root_info);
	अगर (err)
		जाओ fail_unmap;

	sb->s_magic = VBOXSF_SUPER_MAGIC;
	sb->s_blocksize = 1024;
	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	sb->s_op = &vboxsf_super_ops;
	sb->s_d_op = &vboxsf_dentry_ops;

	iroot = iget_locked(sb, 0);
	अगर (!iroot) अणु
		err = -ENOMEM;
		जाओ fail_unmap;
	पूर्ण
	vboxsf_init_inode(sbi, iroot, &sbi->root_info, false);
	unlock_new_inode(iroot);

	droot = d_make_root(iroot);
	अगर (!droot) अणु
		err = -ENOMEM;
		जाओ fail_unmap;
	पूर्ण

	sb->s_root = droot;
	sb->s_fs_info = sbi;
	वापस 0;

fail_unmap:
	vboxsf_unmap_folder(sbi->root);
fail_मुक्त:
	अगर (sbi->bdi_id >= 0)
		ida_simple_हटाओ(&vboxsf_bdi_ida, sbi->bdi_id);
	अगर (sbi->nls)
		unload_nls(sbi->nls);
	idr_destroy(&sbi->ino_idr);
	kमुक्त(sbi);
	वापस err;
पूर्ण

अटल व्योम vboxsf_inode_init_once(व्योम *data)
अणु
	काष्ठा vboxsf_inode *sf_i = data;

	mutex_init(&sf_i->handle_list_mutex);
	inode_init_once(&sf_i->vfs_inode);
पूर्ण

अटल काष्ठा inode *vboxsf_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा vboxsf_inode *sf_i;

	sf_i = kmem_cache_alloc(vboxsf_inode_cachep, GFP_NOFS);
	अगर (!sf_i)
		वापस शून्य;

	sf_i->क्रमce_restat = 0;
	INIT_LIST_HEAD(&sf_i->handle_list);

	वापस &sf_i->vfs_inode;
पूर्ण

अटल व्योम vboxsf_मुक्त_inode(काष्ठा inode *inode)
अणु
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(inode->i_sb);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sbi->ino_idr_lock, flags);
	idr_हटाओ(&sbi->ino_idr, inode->i_ino);
	spin_unlock_irqrestore(&sbi->ino_idr_lock, flags);
	kmem_cache_मुक्त(vboxsf_inode_cachep, VBOXSF_I(inode));
पूर्ण

अटल व्योम vboxsf_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(sb);

	vboxsf_unmap_folder(sbi->root);
	अगर (sbi->bdi_id >= 0)
		ida_simple_हटाओ(&vboxsf_bdi_ida, sbi->bdi_id);
	अगर (sbi->nls)
		unload_nls(sbi->nls);

	/*
	 * vboxsf_मुक्त_inode uses the idr, make sure all delayed rcu मुक्त
	 * inodes are flushed.
	 */
	rcu_barrier();
	idr_destroy(&sbi->ino_idr);
	kमुक्त(sbi);
पूर्ण

अटल पूर्णांक vboxsf_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *stat)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा shfl_volinfo shfl_volinfo;
	काष्ठा vboxsf_sbi *sbi;
	u32 buf_len;
	पूर्णांक err;

	sbi = VBOXSF_SBI(sb);
	buf_len = माप(shfl_volinfo);
	err = vboxsf_fsinfo(sbi->root, 0, SHFL_INFO_GET | SHFL_INFO_VOLUME,
			    &buf_len, &shfl_volinfo);
	अगर (err)
		वापस err;

	stat->f_type = VBOXSF_SUPER_MAGIC;
	stat->f_bsize = shfl_volinfo.bytes_per_allocation_unit;

	करो_भाग(shfl_volinfo.total_allocation_bytes,
	       shfl_volinfo.bytes_per_allocation_unit);
	stat->f_blocks = shfl_volinfo.total_allocation_bytes;

	करो_भाग(shfl_volinfo.available_allocation_bytes,
	       shfl_volinfo.bytes_per_allocation_unit);
	stat->f_bमुक्त  = shfl_volinfo.available_allocation_bytes;
	stat->f_bavail = shfl_volinfo.available_allocation_bytes;

	stat->f_files = 1000;
	/*
	 * Don't वापस 0 here since the guest may then think that it is not
	 * possible to create any more files.
	 */
	stat->f_fमुक्त = 1000000;
	stat->f_fsid.val[0] = 0;
	stat->f_fsid.val[1] = 0;
	stat->f_namelen = 255;
	वापस 0;
पूर्ण

अटल काष्ठा super_operations vboxsf_super_ops = अणु
	.alloc_inode	= vboxsf_alloc_inode,
	.मुक्त_inode	= vboxsf_मुक्त_inode,
	.put_super	= vboxsf_put_super,
	.statfs		= vboxsf_statfs,
पूर्ण;

अटल पूर्णांक vboxsf_setup(व्योम)
अणु
	पूर्णांक err;

	mutex_lock(&vboxsf_setup_mutex);

	अगर (vboxsf_setup_करोne)
		जाओ success;

	vboxsf_inode_cachep =
		kmem_cache_create("vboxsf_inode_cache",
				  माप(काष्ठा vboxsf_inode), 0,
				  (SLAB_RECLAIM_ACCOUNT | SLAB_MEM_SPREAD |
				   SLAB_ACCOUNT),
				  vboxsf_inode_init_once);
	अगर (!vboxsf_inode_cachep) अणु
		err = -ENOMEM;
		जाओ fail_nomem;
	पूर्ण

	err = vboxsf_connect();
	अगर (err) अणु
		vbg_err("vboxsf: err %d connecting to guest PCI-device\n", err);
		vbg_err("vboxsf: make sure you are inside a VirtualBox VM\n");
		vbg_err("vboxsf: and check dmesg for vboxguest errors\n");
		जाओ fail_मुक्त_cache;
	पूर्ण

	err = vboxsf_set_utf8();
	अगर (err) अणु
		vbg_err("vboxsf_setutf8 error %d\n", err);
		जाओ fail_disconnect;
	पूर्ण

	अगर (!follow_symlinks) अणु
		err = vboxsf_set_symlinks();
		अगर (err)
			vbg_warn("vboxsf: Unable to show symlinks: %d\n", err);
	पूर्ण

	vboxsf_setup_करोne = true;
success:
	mutex_unlock(&vboxsf_setup_mutex);
	वापस 0;

fail_disconnect:
	vboxsf_disconnect();
fail_मुक्त_cache:
	kmem_cache_destroy(vboxsf_inode_cachep);
fail_nomem:
	mutex_unlock(&vboxsf_setup_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक vboxsf_parse_monolithic(काष्ठा fs_context *fc, व्योम *data)
अणु
	अचिन्हित अक्षर *options = data;

	अगर (options && options[0] == VBSF_MOUNT_SIGNATURE_BYTE_0 &&
		       options[1] == VBSF_MOUNT_SIGNATURE_BYTE_1 &&
		       options[2] == VBSF_MOUNT_SIGNATURE_BYTE_2 &&
		       options[3] == VBSF_MOUNT_SIGNATURE_BYTE_3) अणु
		vbg_err("vboxsf: Old binary mount data not supported, remove obsolete mount.vboxsf and/or update your VBoxService.\n");
		वापस -EINVAL;
	पूर्ण

	वापस generic_parse_monolithic(fc, data);
पूर्ण

अटल पूर्णांक vboxsf_get_tree(काष्ठा fs_context *fc)
अणु
	पूर्णांक err;

	err = vboxsf_setup();
	अगर (err)
		वापस err;

	वापस get_tree_nodev(fc, vboxsf_fill_super);
पूर्ण

अटल पूर्णांक vboxsf_reconfigure(काष्ठा fs_context *fc)
अणु
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(fc->root->d_sb);
	काष्ठा vboxsf_fs_context *ctx = fc->fs_निजी;
	काष्ठा inode *iroot = fc->root->d_sb->s_root->d_inode;

	/* Apply changed options to the root inode */
	sbi->o = ctx->o;
	vboxsf_init_inode(sbi, iroot, &sbi->root_info, true);

	वापस 0;
पूर्ण

अटल व्योम vboxsf_मुक्त_fc(काष्ठा fs_context *fc)
अणु
	काष्ठा vboxsf_fs_context *ctx = fc->fs_निजी;

	kमुक्त(ctx->nls_name);
	kमुक्त(ctx);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations vboxsf_context_ops = अणु
	.मुक्त			= vboxsf_मुक्त_fc,
	.parse_param		= vboxsf_parse_param,
	.parse_monolithic	= vboxsf_parse_monolithic,
	.get_tree		= vboxsf_get_tree,
	.reconfigure		= vboxsf_reconfigure,
पूर्ण;

अटल पूर्णांक vboxsf_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा vboxsf_fs_context *ctx;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	current_uid_gid(&ctx->o.uid, &ctx->o.gid);

	fc->fs_निजी = ctx;
	fc->ops = &vboxsf_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type vboxsf_fs_type = अणु
	.owner			= THIS_MODULE,
	.name			= "vboxsf",
	.init_fs_context	= vboxsf_init_fs_context,
	.समाप्त_sb		= समाप्त_anon_super
पूर्ण;

/* Module initialization/finalization handlers */
अटल पूर्णांक __init vboxsf_init(व्योम)
अणु
	वापस रेजिस्टर_fileप्रणाली(&vboxsf_fs_type);
पूर्ण

अटल व्योम __निकास vboxsf_fini(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&vboxsf_fs_type);

	mutex_lock(&vboxsf_setup_mutex);
	अगर (vboxsf_setup_करोne) अणु
		vboxsf_disconnect();
		/*
		 * Make sure all delayed rcu मुक्त inodes are flushed
		 * beक्रमe we destroy the cache.
		 */
		rcu_barrier();
		kmem_cache_destroy(vboxsf_inode_cachep);
	पूर्ण
	mutex_unlock(&vboxsf_setup_mutex);
पूर्ण

module_init(vboxsf_init);
module_निकास(vboxsf_fini);

MODULE_DESCRIPTION("Oracle VM VirtualBox Module for Host File System Access");
MODULE_AUTHOR("Oracle Corporation");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS_FS("vboxsf");
