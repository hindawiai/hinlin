<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 * SPU file प्रणाली
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005
 *
 * Author: Arnd Bergmann <arndb@de.ibm.com>
 */

#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/init.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/spu.h>
#समावेश <यंत्र/spu_priv1.h>
#समावेश <linux/uaccess.h>

#समावेश "spufs.h"

काष्ठा spufs_sb_info अणु
	bool debug;
पूर्ण;

अटल काष्ठा kmem_cache *spufs_inode_cache;
अक्षर *isolated_loader;
अटल पूर्णांक isolated_loader_size;

अटल काष्ठा spufs_sb_info *spufs_get_sb_info(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल काष्ठा inode *
spufs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा spufs_inode_info *ei;

	ei = kmem_cache_alloc(spufs_inode_cache, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;

	ei->i_gang = शून्य;
	ei->i_ctx = शून्य;
	ei->i_खोलोers = 0;

	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम spufs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(spufs_inode_cache, SPUFS_I(inode));
पूर्ण

अटल व्योम
spufs_init_once(व्योम *p)
अणु
	काष्ठा spufs_inode_info *ei = p;

	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल काष्ठा inode *
spufs_new_inode(काष्ठा super_block *sb, umode_t mode)
अणु
	काष्ठा inode *inode;

	inode = new_inode(sb);
	अगर (!inode)
		जाओ out;

	inode->i_ino = get_next_ino();
	inode->i_mode = mode;
	inode->i_uid = current_fsuid();
	inode->i_gid = current_fsgid();
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
out:
	वापस inode;
पूर्ण

अटल पूर्णांक
spufs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
	      काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);

	अगर ((attr->ia_valid & ATTR_SIZE) &&
	    (attr->ia_size != inode->i_size))
		वापस -EINVAL;
	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण


अटल पूर्णांक
spufs_new_file(काष्ठा super_block *sb, काष्ठा dentry *dentry,
		स्थिर काष्ठा file_operations *fops, umode_t mode,
		माप_प्रकार size, काष्ठा spu_context *ctx)
अणु
	अटल स्थिर काष्ठा inode_operations spufs_file_iops = अणु
		.setattr = spufs_setattr,
	पूर्ण;
	काष्ठा inode *inode;
	पूर्णांक ret;

	ret = -ENOSPC;
	inode = spufs_new_inode(sb, S_IFREG | mode);
	अगर (!inode)
		जाओ out;

	ret = 0;
	inode->i_op = &spufs_file_iops;
	inode->i_fop = fops;
	inode->i_size = size;
	inode->i_निजी = SPUFS_I(inode)->i_ctx = get_spu_context(ctx);
	d_add(dentry, inode);
out:
	वापस ret;
पूर्ण

अटल व्योम
spufs_evict_inode(काष्ठा inode *inode)
अणु
	काष्ठा spufs_inode_info *ei = SPUFS_I(inode);
	clear_inode(inode);
	अगर (ei->i_ctx)
		put_spu_context(ei->i_ctx);
	अगर (ei->i_gang)
		put_spu_gang(ei->i_gang);
पूर्ण

अटल व्योम spufs_prune_dir(काष्ठा dentry *dir)
अणु
	काष्ठा dentry *dentry, *पंचांगp;

	inode_lock(d_inode(dir));
	list_क्रम_each_entry_safe(dentry, पंचांगp, &dir->d_subdirs, d_child) अणु
		spin_lock(&dentry->d_lock);
		अगर (simple_positive(dentry)) अणु
			dget_dlock(dentry);
			__d_drop(dentry);
			spin_unlock(&dentry->d_lock);
			simple_unlink(d_inode(dir), dentry);
			/* XXX: what was dcache_lock protecting here? Other
			 * fileप्रणालीs (IB, configfs) release dcache_lock
			 * beक्रमe unlink */
			dput(dentry);
		पूर्ण अन्यथा अणु
			spin_unlock(&dentry->d_lock);
		पूर्ण
	पूर्ण
	shrink_dcache_parent(dir);
	inode_unlock(d_inode(dir));
पूर्ण

/* Caller must hold parent->i_mutex */
अटल पूर्णांक spufs_सूची_हटाओ(काष्ठा inode *parent, काष्ठा dentry *dir)
अणु
	/* हटाओ all entries */
	पूर्णांक res;
	spufs_prune_dir(dir);
	d_drop(dir);
	res = simple_सूची_हटाओ(parent, dir);
	/* We have to give up the mm_काष्ठा */
	spu_क्रमget(SPUFS_I(d_inode(dir))->i_ctx);
	वापस res;
पूर्ण

अटल पूर्णांक spufs_fill_dir(काष्ठा dentry *dir,
		स्थिर काष्ठा spufs_tree_descr *files, umode_t mode,
		काष्ठा spu_context *ctx)
अणु
	जबतक (files->name && files->name[0]) अणु
		पूर्णांक ret;
		काष्ठा dentry *dentry = d_alloc_name(dir, files->name);
		अगर (!dentry)
			वापस -ENOMEM;
		ret = spufs_new_file(dir->d_sb, dentry, files->ops,
					files->mode & mode, files->size, ctx);
		अगर (ret)
			वापस ret;
		files++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक spufs_dir_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा inode *parent;
	काष्ठा dentry *dir;
	पूर्णांक ret;

	dir = file->f_path.dentry;
	parent = d_inode(dir->d_parent);

	inode_lock_nested(parent, I_MUTEX_PARENT);
	ret = spufs_सूची_हटाओ(parent, dir);
	inode_unlock(parent);
	WARN_ON(ret);

	वापस dcache_dir_बंद(inode, file);
पूर्ण

स्थिर काष्ठा file_operations spufs_context_fops = अणु
	.खोलो		= dcache_dir_खोलो,
	.release	= spufs_dir_बंद,
	.llseek		= dcache_dir_lseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= dcache_सूची_पढ़ो,
	.fsync		= noop_fsync,
पूर्ण;
EXPORT_SYMBOL_GPL(spufs_context_fops);

अटल पूर्णांक
spufs_सूची_गढ़ो(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags,
		umode_t mode)
अणु
	पूर्णांक ret;
	काष्ठा inode *inode;
	काष्ठा spu_context *ctx;

	inode = spufs_new_inode(dir->i_sb, mode | S_IFसूची);
	अगर (!inode)
		वापस -ENOSPC;

	inode_init_owner(&init_user_ns, inode, dir, mode | S_IFसूची);
	ctx = alloc_spu_context(SPUFS_I(dir)->i_gang); /* XXX gang */
	SPUFS_I(inode)->i_ctx = ctx;
	अगर (!ctx) अणु
		iput(inode);
		वापस -ENOSPC;
	पूर्ण

	ctx->flags = flags;
	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;

	inode_lock(inode);

	dget(dentry);
	inc_nlink(dir);
	inc_nlink(inode);

	d_instantiate(dentry, inode);

	अगर (flags & SPU_CREATE_NOSCHED)
		ret = spufs_fill_dir(dentry, spufs_dir_nosched_contents,
					 mode, ctx);
	अन्यथा
		ret = spufs_fill_dir(dentry, spufs_dir_contents, mode, ctx);

	अगर (!ret && spufs_get_sb_info(dir->i_sb)->debug)
		ret = spufs_fill_dir(dentry, spufs_dir_debug_contents,
				mode, ctx);

	अगर (ret)
		spufs_सूची_हटाओ(dir, dentry);

	inode_unlock(inode);

	वापस ret;
पूर्ण

अटल पूर्णांक spufs_context_खोलो(काष्ठा path *path)
अणु
	पूर्णांक ret;
	काष्ठा file *filp;

	ret = get_unused_fd_flags(0);
	अगर (ret < 0)
		वापस ret;

	filp = dentry_खोलो(path, O_RDONLY, current_cred());
	अगर (IS_ERR(filp)) अणु
		put_unused_fd(ret);
		वापस PTR_ERR(filp);
	पूर्ण

	filp->f_op = &spufs_context_fops;
	fd_install(ret, filp);
	वापस ret;
पूर्ण

अटल काष्ठा spu_context *
spufs_निश्चित_affinity(अचिन्हित पूर्णांक flags, काष्ठा spu_gang *gang,
						काष्ठा file *filp)
अणु
	काष्ठा spu_context *पंचांगp, *neighbor, *err;
	पूर्णांक count, node;
	पूर्णांक aff_supp;

	aff_supp = !list_empty(&(list_entry(cbe_spu_info[0].spus.next,
					काष्ठा spu, cbe_list))->aff_list);

	अगर (!aff_supp)
		वापस ERR_PTR(-EINVAL);

	अगर (flags & SPU_CREATE_GANG)
		वापस ERR_PTR(-EINVAL);

	अगर (flags & SPU_CREATE_AFFINITY_MEM &&
	    gang->aff_ref_ctx &&
	    gang->aff_ref_ctx->flags & SPU_CREATE_AFFINITY_MEM)
		वापस ERR_PTR(-EEXIST);

	अगर (gang->aff_flags & AFF_MERGED)
		वापस ERR_PTR(-EBUSY);

	neighbor = शून्य;
	अगर (flags & SPU_CREATE_AFFINITY_SPU) अणु
		अगर (!filp || filp->f_op != &spufs_context_fops)
			वापस ERR_PTR(-EINVAL);

		neighbor = get_spu_context(
				SPUFS_I(file_inode(filp))->i_ctx);

		अगर (!list_empty(&neighbor->aff_list) && !(neighbor->aff_head) &&
		    !list_is_last(&neighbor->aff_list, &gang->aff_list_head) &&
		    !list_entry(neighbor->aff_list.next, काष्ठा spu_context,
		    aff_list)->aff_head) अणु
			err = ERR_PTR(-EEXIST);
			जाओ out_put_neighbor;
		पूर्ण

		अगर (gang != neighbor->gang) अणु
			err = ERR_PTR(-EINVAL);
			जाओ out_put_neighbor;
		पूर्ण

		count = 1;
		list_क्रम_each_entry(पंचांगp, &gang->aff_list_head, aff_list)
			count++;
		अगर (list_empty(&neighbor->aff_list))
			count++;

		क्रम (node = 0; node < MAX_NUMNODES; node++) अणु
			अगर ((cbe_spu_info[node].n_spus - atomic_पढ़ो(
				&cbe_spu_info[node].reserved_spus)) >= count)
				अवरोध;
		पूर्ण

		अगर (node == MAX_NUMNODES) अणु
			err = ERR_PTR(-EEXIST);
			जाओ out_put_neighbor;
		पूर्ण
	पूर्ण

	वापस neighbor;

out_put_neighbor:
	put_spu_context(neighbor);
	वापस err;
पूर्ण

अटल व्योम
spufs_set_affinity(अचिन्हित पूर्णांक flags, काष्ठा spu_context *ctx,
					काष्ठा spu_context *neighbor)
अणु
	अगर (flags & SPU_CREATE_AFFINITY_MEM)
		ctx->gang->aff_ref_ctx = ctx;

	अगर (flags & SPU_CREATE_AFFINITY_SPU) अणु
		अगर (list_empty(&neighbor->aff_list)) अणु
			list_add_tail(&neighbor->aff_list,
				&ctx->gang->aff_list_head);
			neighbor->aff_head = 1;
		पूर्ण

		अगर (list_is_last(&neighbor->aff_list, &ctx->gang->aff_list_head)
		    || list_entry(neighbor->aff_list.next, काष्ठा spu_context,
							aff_list)->aff_head) अणु
			list_add(&ctx->aff_list, &neighbor->aff_list);
		पूर्ण अन्यथा  अणु
			list_add_tail(&ctx->aff_list, &neighbor->aff_list);
			अगर (neighbor->aff_head) अणु
				neighbor->aff_head = 0;
				ctx->aff_head = 1;
			पूर्ण
		पूर्ण

		अगर (!ctx->gang->aff_ref_ctx)
			ctx->gang->aff_ref_ctx = ctx;
	पूर्ण
पूर्ण

अटल पूर्णांक
spufs_create_context(काष्ठा inode *inode, काष्ठा dentry *dentry,
			काष्ठा vfsmount *mnt, पूर्णांक flags, umode_t mode,
			काष्ठा file *aff_filp)
अणु
	पूर्णांक ret;
	पूर्णांक affinity;
	काष्ठा spu_gang *gang;
	काष्ठा spu_context *neighbor;
	काष्ठा path path = अणु.mnt = mnt, .dentry = dentryपूर्ण;

	अगर ((flags & SPU_CREATE_NOSCHED) &&
	    !capable(CAP_SYS_NICE))
		वापस -EPERM;

	अगर ((flags & (SPU_CREATE_NOSCHED | SPU_CREATE_ISOLATE))
	    == SPU_CREATE_ISOLATE)
		वापस -EINVAL;

	अगर ((flags & SPU_CREATE_ISOLATE) && !isolated_loader)
		वापस -ENODEV;

	gang = शून्य;
	neighbor = शून्य;
	affinity = flags & (SPU_CREATE_AFFINITY_MEM | SPU_CREATE_AFFINITY_SPU);
	अगर (affinity) अणु
		gang = SPUFS_I(inode)->i_gang;
		अगर (!gang)
			वापस -EINVAL;
		mutex_lock(&gang->aff_mutex);
		neighbor = spufs_निश्चित_affinity(flags, gang, aff_filp);
		अगर (IS_ERR(neighbor)) अणु
			ret = PTR_ERR(neighbor);
			जाओ out_aff_unlock;
		पूर्ण
	पूर्ण

	ret = spufs_सूची_गढ़ो(inode, dentry, flags, mode & 0777);
	अगर (ret)
		जाओ out_aff_unlock;

	अगर (affinity) अणु
		spufs_set_affinity(flags, SPUFS_I(d_inode(dentry))->i_ctx,
								neighbor);
		अगर (neighbor)
			put_spu_context(neighbor);
	पूर्ण

	ret = spufs_context_खोलो(&path);
	अगर (ret < 0)
		WARN_ON(spufs_सूची_हटाओ(inode, dentry));

out_aff_unlock:
	अगर (affinity)
		mutex_unlock(&gang->aff_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक
spufs_mkgang(काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mode)
अणु
	पूर्णांक ret;
	काष्ठा inode *inode;
	काष्ठा spu_gang *gang;

	ret = -ENOSPC;
	inode = spufs_new_inode(dir->i_sb, mode | S_IFसूची);
	अगर (!inode)
		जाओ out;

	ret = 0;
	inode_init_owner(&init_user_ns, inode, dir, mode | S_IFसूची);
	gang = alloc_spu_gang();
	SPUFS_I(inode)->i_ctx = शून्य;
	SPUFS_I(inode)->i_gang = gang;
	अगर (!gang) अणु
		ret = -ENOMEM;
		जाओ out_iput;
	पूर्ण

	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;

	d_instantiate(dentry, inode);
	inc_nlink(dir);
	inc_nlink(d_inode(dentry));
	वापस ret;

out_iput:
	iput(inode);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक spufs_gang_खोलो(काष्ठा path *path)
अणु
	पूर्णांक ret;
	काष्ठा file *filp;

	ret = get_unused_fd_flags(0);
	अगर (ret < 0)
		वापस ret;

	/*
	 * get references क्रम dget and mntget, will be released
	 * in error path of *_खोलो().
	 */
	filp = dentry_खोलो(path, O_RDONLY, current_cred());
	अगर (IS_ERR(filp)) अणु
		put_unused_fd(ret);
		वापस PTR_ERR(filp);
	पूर्ण

	filp->f_op = &simple_dir_operations;
	fd_install(ret, filp);
	वापस ret;
पूर्ण

अटल पूर्णांक spufs_create_gang(काष्ठा inode *inode,
			काष्ठा dentry *dentry,
			काष्ठा vfsmount *mnt, umode_t mode)
अणु
	काष्ठा path path = अणु.mnt = mnt, .dentry = dentryपूर्ण;
	पूर्णांक ret;

	ret = spufs_mkgang(inode, dentry, mode & 0777);
	अगर (!ret) अणु
		ret = spufs_gang_खोलो(&path);
		अगर (ret < 0) अणु
			पूर्णांक err = simple_सूची_हटाओ(inode, dentry);
			WARN_ON(err);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण


अटल काष्ठा file_प्रणाली_type spufs_type;

दीर्घ spufs_create(काष्ठा path *path, काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक flags, umode_t mode, काष्ठा file *filp)
अणु
	काष्ठा inode *dir = d_inode(path->dentry);
	पूर्णांक ret;

	/* check अगर we are on spufs */
	अगर (path->dentry->d_sb->s_type != &spufs_type)
		वापस -EINVAL;

	/* करोn't accept undefined flags */
	अगर (flags & (~SPU_CREATE_FLAG_ALL))
		वापस -EINVAL;

	/* only thपढ़ोs can be underneath a gang */
	अगर (path->dentry != path->dentry->d_sb->s_root)
		अगर ((flags & SPU_CREATE_GANG) || !SPUFS_I(dir)->i_gang)
			वापस -EINVAL;

	mode &= ~current_umask();

	अगर (flags & SPU_CREATE_GANG)
		ret = spufs_create_gang(dir, dentry, path->mnt, mode);
	अन्यथा
		ret = spufs_create_context(dir, dentry, path->mnt, flags, mode,
					    filp);
	अगर (ret >= 0)
		fsnotअगरy_सूची_गढ़ो(dir, dentry);

	वापस ret;
पूर्ण

/* File प्रणाली initialization */
काष्ठा spufs_fs_context अणु
	kuid_t	uid;
	kgid_t	gid;
	umode_t	mode;
पूर्ण;

क्रमागत अणु
	Opt_uid, Opt_gid, Opt_mode, Opt_debug,
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec spufs_fs_parameters[] = अणु
	fsparam_u32	("gid",				Opt_gid),
	fsparam_u32oct	("mode",			Opt_mode),
	fsparam_u32	("uid",				Opt_uid),
	fsparam_flag	("debug",			Opt_debug),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक spufs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा spufs_sb_info *sbi = spufs_get_sb_info(root->d_sb);
	काष्ठा inode *inode = root->d_inode;

	अगर (!uid_eq(inode->i_uid, GLOBAL_ROOT_UID))
		seq_म_लिखो(m, ",uid=%u",
			   from_kuid_munged(&init_user_ns, inode->i_uid));
	अगर (!gid_eq(inode->i_gid, GLOBAL_ROOT_GID))
		seq_म_लिखो(m, ",gid=%u",
			   from_kgid_munged(&init_user_ns, inode->i_gid));
	अगर ((inode->i_mode & S_IALLUGO) != 0775)
		seq_म_लिखो(m, ",mode=%o", inode->i_mode);
	अगर (sbi->debug)
		seq_माला_दो(m, ",debug");
	वापस 0;
पूर्ण

अटल पूर्णांक spufs_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा spufs_fs_context *ctx = fc->fs_निजी;
	काष्ठा spufs_sb_info *sbi = fc->s_fs_info;
	काष्ठा fs_parse_result result;
	kuid_t uid;
	kgid_t gid;
	पूर्णांक opt;

	opt = fs_parse(fc, spufs_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_uid:
		uid = make_kuid(current_user_ns(), result.uपूर्णांक_32);
		अगर (!uid_valid(uid))
			वापस invalf(fc, "Unknown uid");
		ctx->uid = uid;
		अवरोध;
	हाल Opt_gid:
		gid = make_kgid(current_user_ns(), result.uपूर्णांक_32);
		अगर (!gid_valid(gid))
			वापस invalf(fc, "Unknown gid");
		ctx->gid = gid;
		अवरोध;
	हाल Opt_mode:
		ctx->mode = result.uपूर्णांक_32 & S_IALLUGO;
		अवरोध;
	हाल Opt_debug:
		sbi->debug = true;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम spufs_निकास_isolated_loader(व्योम)
अणु
	मुक्त_pages((अचिन्हित दीर्घ) isolated_loader,
			get_order(isolated_loader_size));
पूर्ण

अटल व्योम
spufs_init_isolated_loader(व्योम)
अणु
	काष्ठा device_node *dn;
	स्थिर अक्षर *loader;
	पूर्णांक size;

	dn = of_find_node_by_path("/spu-isolation");
	अगर (!dn)
		वापस;

	loader = of_get_property(dn, "loader", &size);
	अगर (!loader)
		वापस;

	/* the loader must be align on a 16 byte boundary */
	isolated_loader = (अक्षर *)__get_मुक्त_pages(GFP_KERNEL, get_order(size));
	अगर (!isolated_loader)
		वापस;

	isolated_loader_size = size;
	स_नकल(isolated_loader, loader, size);
	prपूर्णांकk(KERN_INFO "spufs: SPU isolation mode enabled\n");
पूर्ण

अटल पूर्णांक spufs_create_root(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा spufs_fs_context *ctx = fc->fs_निजी;
	काष्ठा inode *inode;

	अगर (!spu_management_ops)
		वापस -ENODEV;

	inode = spufs_new_inode(sb, S_IFसूची | ctx->mode);
	अगर (!inode)
		वापस -ENOMEM;

	inode->i_uid = ctx->uid;
	inode->i_gid = ctx->gid;
	inode->i_op = &simple_dir_inode_operations;
	inode->i_fop = &simple_dir_operations;
	SPUFS_I(inode)->i_ctx = शून्य;
	inc_nlink(inode);

	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations spufs_ops = अणु
	.alloc_inode	= spufs_alloc_inode,
	.मुक्त_inode	= spufs_मुक्त_inode,
	.statfs		= simple_statfs,
	.evict_inode	= spufs_evict_inode,
	.show_options	= spufs_show_options,
पूर्ण;

अटल पूर्णांक spufs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = SPUFS_MAGIC;
	sb->s_op = &spufs_ops;

	वापस spufs_create_root(sb, fc);
पूर्ण

अटल पूर्णांक spufs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, spufs_fill_super);
पूर्ण

अटल व्योम spufs_मुक्त_fc(काष्ठा fs_context *fc)
अणु
	kमुक्त(fc->s_fs_info);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations spufs_context_ops = अणु
	.मुक्त		= spufs_मुक्त_fc,
	.parse_param	= spufs_parse_param,
	.get_tree	= spufs_get_tree,
पूर्ण;

अटल पूर्णांक spufs_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा spufs_fs_context *ctx;
	काष्ठा spufs_sb_info *sbi;

	ctx = kzalloc(माप(काष्ठा spufs_fs_context), GFP_KERNEL);
	अगर (!ctx)
		जाओ nomem;

	sbi = kzalloc(माप(काष्ठा spufs_sb_info), GFP_KERNEL);
	अगर (!sbi)
		जाओ nomem_ctx;

	ctx->uid = current_uid();
	ctx->gid = current_gid();
	ctx->mode = 0755;

	fc->fs_निजी = ctx;
	fc->s_fs_info = sbi;
	fc->ops = &spufs_context_ops;
	वापस 0;

nomem_ctx:
	kमुक्त(ctx);
nomem:
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा file_प्रणाली_type spufs_type = अणु
	.owner = THIS_MODULE,
	.name = "spufs",
	.init_fs_context = spufs_init_fs_context,
	.parameters	= spufs_fs_parameters,
	.समाप्त_sb = समाप्त_litter_super,
पूर्ण;
MODULE_ALIAS_FS("spufs");

अटल पूर्णांक __init spufs_init(व्योम)
अणु
	पूर्णांक ret;

	ret = -ENODEV;
	अगर (!spu_management_ops)
		जाओ out;

	ret = -ENOMEM;
	spufs_inode_cache = kmem_cache_create("spufs_inode_cache",
			माप(काष्ठा spufs_inode_info), 0,
			SLAB_HWCACHE_ALIGN|SLAB_ACCOUNT, spufs_init_once);

	अगर (!spufs_inode_cache)
		जाओ out;
	ret = spu_sched_init();
	अगर (ret)
		जाओ out_cache;
	ret = रेजिस्टर_spu_syscalls(&spufs_calls);
	अगर (ret)
		जाओ out_sched;
	ret = रेजिस्टर_fileप्रणाली(&spufs_type);
	अगर (ret)
		जाओ out_syscalls;

	spufs_init_isolated_loader();

	वापस 0;

out_syscalls:
	unरेजिस्टर_spu_syscalls(&spufs_calls);
out_sched:
	spu_sched_निकास();
out_cache:
	kmem_cache_destroy(spufs_inode_cache);
out:
	वापस ret;
पूर्ण
module_init(spufs_init);

अटल व्योम __निकास spufs_निकास(व्योम)
अणु
	spu_sched_निकास();
	spufs_निकास_isolated_loader();
	unरेजिस्टर_spu_syscalls(&spufs_calls);
	unरेजिस्टर_fileप्रणाली(&spufs_type);
	kmem_cache_destroy(spufs_inode_cache);
पूर्ण
module_निकास(spufs_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arnd Bergmann <arndb@de.ibm.com>");

