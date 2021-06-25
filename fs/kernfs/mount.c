<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fs/kernfs/mount.c - kernfs mount implementation
 *
 * Copyright (c) 2001-3 Patrick Mochel
 * Copyright (c) 2007 SUSE Linux Products GmbH
 * Copyright (c) 2007, 2013 Tejun Heo <tj@kernel.org>
 */

#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/init.h>
#समावेश <linux/magic.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/namei.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/exportfs.h>

#समावेश "kernfs-internal.h"

काष्ठा kmem_cache *kernfs_node_cache, *kernfs_iattrs_cache;

अटल पूर्णांक kernfs_sop_show_options(काष्ठा seq_file *sf, काष्ठा dentry *dentry)
अणु
	काष्ठा kernfs_root *root = kernfs_root(kernfs_dentry_node(dentry));
	काष्ठा kernfs_syscall_ops *scops = root->syscall_ops;

	अगर (scops && scops->show_options)
		वापस scops->show_options(sf, root);
	वापस 0;
पूर्ण

अटल पूर्णांक kernfs_sop_show_path(काष्ठा seq_file *sf, काष्ठा dentry *dentry)
अणु
	काष्ठा kernfs_node *node = kernfs_dentry_node(dentry);
	काष्ठा kernfs_root *root = kernfs_root(node);
	काष्ठा kernfs_syscall_ops *scops = root->syscall_ops;

	अगर (scops && scops->show_path)
		वापस scops->show_path(sf, node, root);

	seq_dentry(sf, dentry, " \t\n\\");
	वापस 0;
पूर्ण

स्थिर काष्ठा super_operations kernfs_sops = अणु
	.statfs		= simple_statfs,
	.drop_inode	= generic_delete_inode,
	.evict_inode	= kernfs_evict_inode,

	.show_options	= kernfs_sop_show_options,
	.show_path	= kernfs_sop_show_path,
पूर्ण;

अटल पूर्णांक kernfs_encode_fh(काष्ठा inode *inode, __u32 *fh, पूर्णांक *max_len,
			    काष्ठा inode *parent)
अणु
	काष्ठा kernfs_node *kn = inode->i_निजी;

	अगर (*max_len < 2) अणु
		*max_len = 2;
		वापस खाताID_INVALID;
	पूर्ण

	*max_len = 2;
	*(u64 *)fh = kn->id;
	वापस खाताID_KERNFS;
पूर्ण

अटल काष्ठा dentry *__kernfs_fh_to_dentry(काष्ठा super_block *sb,
					    काष्ठा fid *fid, पूर्णांक fh_len,
					    पूर्णांक fh_type, bool get_parent)
अणु
	काष्ठा kernfs_super_info *info = kernfs_info(sb);
	काष्ठा kernfs_node *kn;
	काष्ठा inode *inode;
	u64 id;

	अगर (fh_len < 2)
		वापस शून्य;

	चयन (fh_type) अणु
	हाल खाताID_KERNFS:
		id = *(u64 *)fid;
		अवरोध;
	हाल खाताID_INO32_GEN:
	हाल खाताID_INO32_GEN_PARENT:
		/*
		 * blk_log_action() exposes "LOW32,HIGH32" pair without
		 * type and userland can call us with generic fid
		 * स्थिरructed from them.  Combine it back to ID.  See
		 * blk_log_action().
		 */
		id = ((u64)fid->i32.gen << 32) | fid->i32.ino;
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	kn = kernfs_find_and_get_node_by_id(info->root, id);
	अगर (!kn)
		वापस ERR_PTR(-ESTALE);

	अगर (get_parent) अणु
		काष्ठा kernfs_node *parent;

		parent = kernfs_get_parent(kn);
		kernfs_put(kn);
		kn = parent;
		अगर (!kn)
			वापस ERR_PTR(-ESTALE);
	पूर्ण

	inode = kernfs_get_inode(sb, kn);
	kernfs_put(kn);
	अगर (!inode)
		वापस ERR_PTR(-ESTALE);

	वापस d_obtain_alias(inode);
पूर्ण

अटल काष्ठा dentry *kernfs_fh_to_dentry(काष्ठा super_block *sb,
					  काष्ठा fid *fid, पूर्णांक fh_len,
					  पूर्णांक fh_type)
अणु
	वापस __kernfs_fh_to_dentry(sb, fid, fh_len, fh_type, false);
पूर्ण

अटल काष्ठा dentry *kernfs_fh_to_parent(काष्ठा super_block *sb,
					  काष्ठा fid *fid, पूर्णांक fh_len,
					  पूर्णांक fh_type)
अणु
	वापस __kernfs_fh_to_dentry(sb, fid, fh_len, fh_type, true);
पूर्ण

अटल काष्ठा dentry *kernfs_get_parent_dentry(काष्ठा dentry *child)
अणु
	काष्ठा kernfs_node *kn = kernfs_dentry_node(child);

	वापस d_obtain_alias(kernfs_get_inode(child->d_sb, kn->parent));
पूर्ण

अटल स्थिर काष्ठा export_operations kernfs_export_ops = अणु
	.encode_fh	= kernfs_encode_fh,
	.fh_to_dentry	= kernfs_fh_to_dentry,
	.fh_to_parent	= kernfs_fh_to_parent,
	.get_parent	= kernfs_get_parent_dentry,
पूर्ण;

/**
 * kernfs_root_from_sb - determine kernfs_root associated with a super_block
 * @sb: the super_block in question
 *
 * Return the kernfs_root associated with @sb.  If @sb is not a kernfs one,
 * %शून्य is वापसed.
 */
काष्ठा kernfs_root *kernfs_root_from_sb(काष्ठा super_block *sb)
अणु
	अगर (sb->s_op == &kernfs_sops)
		वापस kernfs_info(sb)->root;
	वापस शून्य;
पूर्ण

/*
 * find the next ancestor in the path करोwn to @child, where @parent was the
 * ancestor whose descendant we want to find.
 *
 * Say the path is /a/b/c/d.  @child is d, @parent is शून्य.  We वापस the root
 * node.  If @parent is b, then we वापस the node क्रम c.
 * Passing in d as @parent is not ok.
 */
अटल काष्ठा kernfs_node *find_next_ancestor(काष्ठा kernfs_node *child,
					      काष्ठा kernfs_node *parent)
अणु
	अगर (child == parent) अणु
		pr_crit_once("BUG in find_next_ancestor: called with parent == child");
		वापस शून्य;
	पूर्ण

	जबतक (child->parent != parent) अणु
		अगर (!child->parent)
			वापस शून्य;
		child = child->parent;
	पूर्ण

	वापस child;
पूर्ण

/**
 * kernfs_node_dentry - get a dentry क्रम the given kernfs_node
 * @kn: kernfs_node क्रम which a dentry is needed
 * @sb: the kernfs super_block
 */
काष्ठा dentry *kernfs_node_dentry(काष्ठा kernfs_node *kn,
				  काष्ठा super_block *sb)
अणु
	काष्ठा dentry *dentry;
	काष्ठा kernfs_node *knparent = शून्य;

	BUG_ON(sb->s_op != &kernfs_sops);

	dentry = dget(sb->s_root);

	/* Check अगर this is the root kernfs_node */
	अगर (!kn->parent)
		वापस dentry;

	knparent = find_next_ancestor(kn, शून्य);
	अगर (WARN_ON(!knparent)) अणु
		dput(dentry);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	करो अणु
		काष्ठा dentry *dपंचांगp;
		काष्ठा kernfs_node *knपंचांगp;

		अगर (kn == knparent)
			वापस dentry;
		knपंचांगp = find_next_ancestor(kn, knparent);
		अगर (WARN_ON(!knपंचांगp)) अणु
			dput(dentry);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		dपंचांगp = lookup_positive_unlocked(knपंचांगp->name, dentry,
					       म_माप(knपंचांगp->name));
		dput(dentry);
		अगर (IS_ERR(dपंचांगp))
			वापस dपंचांगp;
		knparent = knपंचांगp;
		dentry = dपंचांगp;
	पूर्ण जबतक (true);
पूर्ण

अटल पूर्णांक kernfs_fill_super(काष्ठा super_block *sb, काष्ठा kernfs_fs_context *kfc)
अणु
	काष्ठा kernfs_super_info *info = kernfs_info(sb);
	काष्ठा inode *inode;
	काष्ठा dentry *root;

	info->sb = sb;
	/* Userspace would अवरोध अगर executables or devices appear on sysfs */
	sb->s_अगरlags |= SB_I_NOEXEC | SB_I_NODEV;
	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = kfc->magic;
	sb->s_op = &kernfs_sops;
	sb->s_xattr = kernfs_xattr_handlers;
	अगर (info->root->flags & KERNFS_ROOT_SUPPORT_EXPORTOP)
		sb->s_export_op = &kernfs_export_ops;
	sb->s_समय_gran = 1;

	/* sysfs dentries and inodes करोn't require IO to create */
	sb->s_shrink.seeks = 0;

	/* get root inode, initialize and unlock it */
	mutex_lock(&kernfs_mutex);
	inode = kernfs_get_inode(sb, info->root->kn);
	mutex_unlock(&kernfs_mutex);
	अगर (!inode) अणु
		pr_debug("kernfs: could not get root inode\n");
		वापस -ENOMEM;
	पूर्ण

	/* instantiate and link root dentry */
	root = d_make_root(inode);
	अगर (!root) अणु
		pr_debug("%s: could not get root dentry!\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	sb->s_root = root;
	sb->s_d_op = &kernfs_करोps;
	वापस 0;
पूर्ण

अटल पूर्णांक kernfs_test_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा kernfs_super_info *sb_info = kernfs_info(sb);
	काष्ठा kernfs_super_info *info = fc->s_fs_info;

	वापस sb_info->root == info->root && sb_info->ns == info->ns;
पूर्ण

अटल पूर्णांक kernfs_set_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा kernfs_fs_context *kfc = fc->fs_निजी;

	kfc->ns_tag = शून्य;
	वापस set_anon_super_fc(sb, fc);
पूर्ण

/**
 * kernfs_super_ns - determine the namespace tag of a kernfs super_block
 * @sb: super_block of पूर्णांकerest
 *
 * Return the namespace tag associated with kernfs super_block @sb.
 */
स्थिर व्योम *kernfs_super_ns(काष्ठा super_block *sb)
अणु
	काष्ठा kernfs_super_info *info = kernfs_info(sb);

	वापस info->ns;
पूर्ण

/**
 * kernfs_get_tree - kernfs fileप्रणाली access/retrieval helper
 * @fc: The fileप्रणाली context.
 *
 * This is to be called from each kernfs user's fs_context->ops->get_tree()
 * implementation, which should set the specअगरied ->@fs_type and ->@flags, and
 * specअगरy the hierarchy and namespace tag to mount via ->@root and ->@ns,
 * respectively.
 */
पूर्णांक kernfs_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा kernfs_fs_context *kfc = fc->fs_निजी;
	काष्ठा super_block *sb;
	काष्ठा kernfs_super_info *info;
	पूर्णांक error;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->root = kfc->root;
	info->ns = kfc->ns_tag;
	INIT_LIST_HEAD(&info->node);

	fc->s_fs_info = info;
	sb = sget_fc(fc, kernfs_test_super, kernfs_set_super);
	अगर (IS_ERR(sb))
		वापस PTR_ERR(sb);

	अगर (!sb->s_root) अणु
		काष्ठा kernfs_super_info *info = kernfs_info(sb);

		kfc->new_sb_created = true;

		error = kernfs_fill_super(sb, kfc);
		अगर (error) अणु
			deactivate_locked_super(sb);
			वापस error;
		पूर्ण
		sb->s_flags |= SB_ACTIVE;

		mutex_lock(&kernfs_mutex);
		list_add(&info->node, &info->root->supers);
		mutex_unlock(&kernfs_mutex);
	पूर्ण

	fc->root = dget(sb->s_root);
	वापस 0;
पूर्ण

व्योम kernfs_मुक्त_fs_context(काष्ठा fs_context *fc)
अणु
	/* Note that we करोn't deal with kfc->ns_tag here. */
	kमुक्त(fc->s_fs_info);
	fc->s_fs_info = शून्य;
पूर्ण

/**
 * kernfs_समाप्त_sb - समाप्त_sb क्रम kernfs
 * @sb: super_block being समाप्तed
 *
 * This can be used directly क्रम file_प्रणाली_type->समाप्त_sb().  If a kernfs
 * user needs extra cleanup, it can implement its own समाप्त_sb() and call
 * this function at the end.
 */
व्योम kernfs_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा kernfs_super_info *info = kernfs_info(sb);

	mutex_lock(&kernfs_mutex);
	list_del(&info->node);
	mutex_unlock(&kernfs_mutex);

	/*
	 * Remove the superblock from fs_supers/s_instances
	 * so we can't find it, beक्रमe मुक्तing kernfs_super_info.
	 */
	समाप्त_anon_super(sb);
	kमुक्त(info);
पूर्ण

व्योम __init kernfs_init(व्योम)
अणु
	kernfs_node_cache = kmem_cache_create("kernfs_node_cache",
					      माप(काष्ठा kernfs_node),
					      0, SLAB_PANIC, शून्य);

	/* Creates slab cache क्रम kernfs inode attributes */
	kernfs_iattrs_cache  = kmem_cache_create("kernfs_iattrs_cache",
					      माप(काष्ठा kernfs_iattrs),
					      0, SLAB_PANIC, शून्य);
पूर्ण
