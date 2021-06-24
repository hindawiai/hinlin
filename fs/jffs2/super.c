<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/fs.h>
#समावेश <linux/err.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/jffs2.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/mtd/super.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/namei.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/exportfs.h>
#समावेश "compr.h"
#समावेश "nodelist.h"

अटल व्योम jffs2_put_super(काष्ठा super_block *);

अटल काष्ठा kmem_cache *jffs2_inode_cachep;

अटल काष्ठा inode *jffs2_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा jffs2_inode_info *f;

	f = kmem_cache_alloc(jffs2_inode_cachep, GFP_KERNEL);
	अगर (!f)
		वापस शून्य;
	वापस &f->vfs_inode;
पूर्ण

अटल व्योम jffs2_मुक्त_inode(काष्ठा inode *inode)
अणु
	काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(inode);

	kमुक्त(f->target);
	kmem_cache_मुक्त(jffs2_inode_cachep, f);
पूर्ण

अटल व्योम jffs2_i_init_once(व्योम *foo)
अणु
	काष्ठा jffs2_inode_info *f = foo;

	mutex_init(&f->sem);
	inode_init_once(&f->vfs_inode);
पूर्ण

अटल स्थिर अक्षर *jffs2_compr_name(अचिन्हित पूर्णांक compr)
अणु
	चयन (compr) अणु
	हाल JFFS2_COMPR_MODE_NONE:
		वापस "none";
#अगर_घोषित CONFIG_JFFS2_LZO
	हाल JFFS2_COMPR_MODE_FORCELZO:
		वापस "lzo";
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_ZLIB
	हाल JFFS2_COMPR_MODE_FORCEZLIB:
		वापस "zlib";
#पूर्ण_अगर
	शेष:
		/* should never happen; programmer error */
		WARN_ON(1);
		वापस "";
	पूर्ण
पूर्ण

अटल पूर्णांक jffs2_show_options(काष्ठा seq_file *s, काष्ठा dentry *root)
अणु
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(root->d_sb);
	काष्ठा jffs2_mount_opts *opts = &c->mount_opts;

	अगर (opts->override_compr)
		seq_म_लिखो(s, ",compr=%s", jffs2_compr_name(opts->compr));
	अगर (opts->set_rp_size)
		seq_म_लिखो(s, ",rp_size=%u", opts->rp_size / 1024);

	वापस 0;
पूर्ण

अटल पूर्णांक jffs2_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(sb);

#अगर_घोषित CONFIG_JFFS2_FS_WRITEBUFFER
	अगर (jffs2_is_ग_लिखोbuffered(c))
		cancel_delayed_work_sync(&c->wbuf_dwork);
#पूर्ण_अगर

	mutex_lock(&c->alloc_sem);
	jffs2_flush_wbuf_pad(c);
	mutex_unlock(&c->alloc_sem);
	वापस 0;
पूर्ण

अटल काष्ठा inode *jffs2_nfs_get_inode(काष्ठा super_block *sb, uपूर्णांक64_t ino,
					 uपूर्णांक32_t generation)
अणु
	/* We करोn't care about i_generation. We'll destroy the flash
	   beक्रमe we start re-using inode numbers anyway. And even
	   अगर that wasn't true, we'd have other problems...*/
	वापस jffs2_iget(sb, ino);
पूर्ण

अटल काष्ठा dentry *jffs2_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
					 पूर्णांक fh_len, पूर्णांक fh_type)
अणु
        वापस generic_fh_to_dentry(sb, fid, fh_len, fh_type,
                                    jffs2_nfs_get_inode);
पूर्ण

अटल काष्ठा dentry *jffs2_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
					 पूर्णांक fh_len, पूर्णांक fh_type)
अणु
        वापस generic_fh_to_parent(sb, fid, fh_len, fh_type,
                                    jffs2_nfs_get_inode);
पूर्ण

अटल काष्ठा dentry *jffs2_get_parent(काष्ठा dentry *child)
अणु
	काष्ठा jffs2_inode_info *f;
	uपूर्णांक32_t pino;

	BUG_ON(!d_is_dir(child));

	f = JFFS2_INODE_INFO(d_inode(child));

	pino = f->inocache->pino_nlink;

	JFFS2_DEBUG("Parent of directory ino #%u is #%u\n",
		    f->inocache->ino, pino);

	वापस d_obtain_alias(jffs2_iget(child->d_sb, pino));
पूर्ण

अटल स्थिर काष्ठा export_operations jffs2_export_ops = अणु
	.get_parent = jffs2_get_parent,
	.fh_to_dentry = jffs2_fh_to_dentry,
	.fh_to_parent = jffs2_fh_to_parent,
पूर्ण;

/*
 * JFFS2 mount options.
 *
 * Opt_source: The source device
 * Opt_override_compr: override शेष compressor
 * Opt_rp_size: size of reserved pool in KiB
 */
क्रमागत अणु
	Opt_override_compr,
	Opt_rp_size,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table jffs2_param_compr[] = अणु
	अणु"none",	JFFS2_COMPR_MODE_NONE पूर्ण,
#अगर_घोषित CONFIG_JFFS2_LZO
	अणु"lzo",		JFFS2_COMPR_MODE_FORCELZO पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_ZLIB
	अणु"zlib",	JFFS2_COMPR_MODE_FORCEZLIB पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec jffs2_fs_parameters[] = अणु
	fsparam_क्रमागत	("compr",	Opt_override_compr, jffs2_param_compr),
	fsparam_u32	("rp_size",	Opt_rp_size),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक jffs2_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा fs_parse_result result;
	काष्ठा jffs2_sb_info *c = fc->s_fs_info;
	पूर्णांक opt;

	opt = fs_parse(fc, jffs2_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_override_compr:
		c->mount_opts.compr = result.uपूर्णांक_32;
		c->mount_opts.override_compr = true;
		अवरोध;
	हाल Opt_rp_size:
		अगर (result.uपूर्णांक_32 > अच_पूर्णांक_उच्च / 1024)
			वापस invalf(fc, "jffs2: rp_size unrepresentable");
		c->mount_opts.rp_size = result.uपूर्णांक_32 * 1024;
		c->mount_opts.set_rp_size = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम jffs2_update_mount_opts(काष्ठा fs_context *fc)
अणु
	काष्ठा jffs2_sb_info *new_c = fc->s_fs_info;
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(fc->root->d_sb);

	mutex_lock(&c->alloc_sem);
	अगर (new_c->mount_opts.override_compr) अणु
		c->mount_opts.override_compr = new_c->mount_opts.override_compr;
		c->mount_opts.compr = new_c->mount_opts.compr;
	पूर्ण
	अगर (new_c->mount_opts.set_rp_size) अणु
		c->mount_opts.set_rp_size = new_c->mount_opts.set_rp_size;
		c->mount_opts.rp_size = new_c->mount_opts.rp_size;
	पूर्ण
	mutex_unlock(&c->alloc_sem);
पूर्ण

अटल पूर्णांक jffs2_reconfigure(काष्ठा fs_context *fc)
अणु
	काष्ठा super_block *sb = fc->root->d_sb;

	sync_fileप्रणाली(sb);
	jffs2_update_mount_opts(fc);

	वापस jffs2_करो_remount_fs(sb, fc);
पूर्ण

अटल स्थिर काष्ठा super_operations jffs2_super_operations =
अणु
	.alloc_inode =	jffs2_alloc_inode,
	.मुक्त_inode =	jffs2_मुक्त_inode,
	.put_super =	jffs2_put_super,
	.statfs =	jffs2_statfs,
	.evict_inode =	jffs2_evict_inode,
	.dirty_inode =	jffs2_dirty_inode,
	.show_options =	jffs2_show_options,
	.sync_fs =	jffs2_sync_fs,
पूर्ण;

/*
 * fill in the superblock
 */
अटल पूर्णांक jffs2_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा jffs2_sb_info *c = sb->s_fs_info;

	jffs2_dbg(1, "jffs2_get_sb_mtd():"
		  " New superblock for device %d (\"%s\")\n",
		  sb->s_mtd->index, sb->s_mtd->name);

	c->mtd = sb->s_mtd;
	c->os_priv = sb;

	अगर (c->mount_opts.rp_size > c->mtd->size)
		वापस invalf(fc, "jffs2: Too large reserve pool specified, max is %llu KB",
			      c->mtd->size / 1024);

	/* Initialize JFFS2 superblock locks, the further initialization will
	 * be करोne later */
	mutex_init(&c->alloc_sem);
	mutex_init(&c->erase_मुक्त_sem);
	init_रुकोqueue_head(&c->erase_रुको);
	init_रुकोqueue_head(&c->inocache_wq);
	spin_lock_init(&c->erase_completion_lock);
	spin_lock_init(&c->inocache_lock);

	sb->s_op = &jffs2_super_operations;
	sb->s_export_op = &jffs2_export_ops;
	sb->s_flags = sb->s_flags | SB_NOATIME;
	sb->s_xattr = jffs2_xattr_handlers;
#अगर_घोषित CONFIG_JFFS2_FS_POSIX_ACL
	sb->s_flags |= SB_POSIXACL;
#पूर्ण_अगर
	वापस jffs2_करो_fill_super(sb, fc);
पूर्ण

अटल पूर्णांक jffs2_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_mtd(fc, jffs2_fill_super);
पूर्ण

अटल व्योम jffs2_मुक्त_fc(काष्ठा fs_context *fc)
अणु
	kमुक्त(fc->s_fs_info);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations jffs2_context_ops = अणु
	.मुक्त		= jffs2_मुक्त_fc,
	.parse_param	= jffs2_parse_param,
	.get_tree	= jffs2_get_tree,
	.reconfigure	= jffs2_reconfigure,
पूर्ण;

अटल पूर्णांक jffs2_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा jffs2_sb_info *ctx;

	ctx = kzalloc(माप(काष्ठा jffs2_sb_info), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	fc->s_fs_info = ctx;
	fc->ops = &jffs2_context_ops;
	वापस 0;
पूर्ण

अटल व्योम jffs2_put_super (काष्ठा super_block *sb)
अणु
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(sb);

	jffs2_dbg(2, "%s()\n", __func__);

	mutex_lock(&c->alloc_sem);
	jffs2_flush_wbuf_pad(c);
	mutex_unlock(&c->alloc_sem);

	jffs2_sum_निकास(c);

	jffs2_मुक्त_ino_caches(c);
	jffs2_मुक्त_raw_node_refs(c);
	kvमुक्त(c->blocks);
	jffs2_flash_cleanup(c);
	kमुक्त(c->inocache_list);
	jffs2_clear_xattr_subप्रणाली(c);
	mtd_sync(c->mtd);
	jffs2_dbg(1, "%s(): returning\n", __func__);
पूर्ण

अटल व्योम jffs2_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(sb);
	अगर (c && !sb_rकरोnly(sb))
		jffs2_stop_garbage_collect_thपढ़ो(c);
	समाप्त_mtd_super(sb);
	kमुक्त(c);
पूर्ण

अटल काष्ठा file_प्रणाली_type jffs2_fs_type = अणु
	.owner =	THIS_MODULE,
	.name =		"jffs2",
	.init_fs_context = jffs2_init_fs_context,
	.parameters =	jffs2_fs_parameters,
	.समाप्त_sb =	jffs2_समाप्त_sb,
पूर्ण;
MODULE_ALIAS_FS("jffs2");

अटल पूर्णांक __init init_jffs2_fs(व्योम)
अणु
	पूर्णांक ret;

	/* Paranoia checks क्रम on-medium काष्ठाures. If we ask GCC
	   to pack them with __attribute__((packed)) then it _also_
	   assumes that they're not aligned -- so it emits crappy
	   code on some architectures. Ideally we want an attribute
	   which means just 'no padding', without the alignment
	   thing. But GCC करोesn't have that -- we have to just
	   hope the काष्ठाs are the right sizes, instead. */
	BUILD_BUG_ON(माप(काष्ठा jffs2_unknown_node) != 12);
	BUILD_BUG_ON(माप(काष्ठा jffs2_raw_dirent) != 40);
	BUILD_BUG_ON(माप(काष्ठा jffs2_raw_inode) != 68);
	BUILD_BUG_ON(माप(काष्ठा jffs2_raw_summary) != 32);

	pr_info("version 2.2."
#अगर_घोषित CONFIG_JFFS2_FS_WRITEBUFFER
	       " (NAND)"
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_SUMMARY
	       " (SUMMARY) "
#पूर्ण_अगर
	       " तऊ 2001-2006 Red Hat, Inc.\n");

	jffs2_inode_cachep = kmem_cache_create("jffs2_i",
					     माप(काष्ठा jffs2_inode_info),
					     0, (SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					     jffs2_i_init_once);
	अगर (!jffs2_inode_cachep) अणु
		pr_err("error: Failed to initialise inode cache\n");
		वापस -ENOMEM;
	पूर्ण
	ret = jffs2_compressors_init();
	अगर (ret) अणु
		pr_err("error: Failed to initialise compressors\n");
		जाओ out;
	पूर्ण
	ret = jffs2_create_slab_caches();
	अगर (ret) अणु
		pr_err("error: Failed to initialise slab caches\n");
		जाओ out_compressors;
	पूर्ण
	ret = रेजिस्टर_fileप्रणाली(&jffs2_fs_type);
	अगर (ret) अणु
		pr_err("error: Failed to register filesystem\n");
		जाओ out_slab;
	पूर्ण
	वापस 0;

 out_slab:
	jffs2_destroy_slab_caches();
 out_compressors:
	jffs2_compressors_निकास();
 out:
	kmem_cache_destroy(jffs2_inode_cachep);
	वापस ret;
पूर्ण

अटल व्योम __निकास निकास_jffs2_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&jffs2_fs_type);
	jffs2_destroy_slab_caches();
	jffs2_compressors_निकास();

	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(jffs2_inode_cachep);
पूर्ण

module_init(init_jffs2_fs);
module_निकास(निकास_jffs2_fs);

MODULE_DESCRIPTION("The Journalling Flash File System, v2");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL"); // Actually dual-licensed, but it करोesn't matter क्रम
		       // the sake of this tag. It's Free Software.
