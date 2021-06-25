<शैली गुरु>
/* AFS superblock handling
 *
 * Copyright (c) 2002, 2007, 2018 Red Hat, Inc. All rights reserved.
 *
 * This software may be मुक्तly redistributed under the terms of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Authors: David Howells <dhowells@redhat.com>
 *          David Woodhouse <dwmw2@infradead.org>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mount.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/statfs.h>
#समावेश <linux/sched.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/magic.h>
#समावेश <net/net_namespace.h>
#समावेश "internal.h"

अटल व्योम afs_i_init_once(व्योम *foo);
अटल व्योम afs_समाप्त_super(काष्ठा super_block *sb);
अटल काष्ठा inode *afs_alloc_inode(काष्ठा super_block *sb);
अटल व्योम afs_destroy_inode(काष्ठा inode *inode);
अटल व्योम afs_मुक्त_inode(काष्ठा inode *inode);
अटल पूर्णांक afs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf);
अटल पूर्णांक afs_show_devname(काष्ठा seq_file *m, काष्ठा dentry *root);
अटल पूर्णांक afs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root);
अटल पूर्णांक afs_init_fs_context(काष्ठा fs_context *fc);
अटल स्थिर काष्ठा fs_parameter_spec afs_fs_parameters[];

काष्ठा file_प्रणाली_type afs_fs_type = अणु
	.owner			= THIS_MODULE,
	.name			= "afs",
	.init_fs_context	= afs_init_fs_context,
	.parameters		= afs_fs_parameters,
	.समाप्त_sb		= afs_समाप्त_super,
	.fs_flags		= FS_RENAME_DOES_D_MOVE,
पूर्ण;
MODULE_ALIAS_FS("afs");

पूर्णांक afs_net_id;

अटल स्थिर काष्ठा super_operations afs_super_ops = अणु
	.statfs		= afs_statfs,
	.alloc_inode	= afs_alloc_inode,
	.drop_inode	= afs_drop_inode,
	.destroy_inode	= afs_destroy_inode,
	.मुक्त_inode	= afs_मुक्त_inode,
	.evict_inode	= afs_evict_inode,
	.show_devname	= afs_show_devname,
	.show_options	= afs_show_options,
पूर्ण;

अटल काष्ठा kmem_cache *afs_inode_cachep;
अटल atomic_t afs_count_active_inodes;

क्रमागत afs_param अणु
	Opt_स्वतःcell,
	Opt_dyn,
	Opt_flock,
	Opt_source,
पूर्ण;

अटल स्थिर काष्ठा स्थिरant_table afs_param_flock[] = अणु
	अणु"local",	afs_flock_mode_local पूर्ण,
	अणु"openafs",	afs_flock_mode_खोलोafs पूर्ण,
	अणु"strict",	afs_flock_mode_strict पूर्ण,
	अणु"write",	afs_flock_mode_ग_लिखो पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec afs_fs_parameters[] = अणु
	fsparam_flag  ("autocell",	Opt_स्वतःcell),
	fsparam_flag  ("dyn",		Opt_dyn),
	fsparam_क्रमागत  ("flock",		Opt_flock, afs_param_flock),
	fsparam_string("source",	Opt_source),
	अणुपूर्ण
पूर्ण;

/*
 * initialise the fileप्रणाली
 */
पूर्णांक __init afs_fs_init(व्योम)
अणु
	पूर्णांक ret;

	_enter("");

	/* create ourselves an inode cache */
	atomic_set(&afs_count_active_inodes, 0);

	ret = -ENOMEM;
	afs_inode_cachep = kmem_cache_create("afs_inode_cache",
					     माप(काष्ठा afs_vnode),
					     0,
					     SLAB_HWCACHE_ALIGN|SLAB_ACCOUNT,
					     afs_i_init_once);
	अगर (!afs_inode_cachep) अणु
		prपूर्णांकk(KERN_NOTICE "kAFS: Failed to allocate inode cache\n");
		वापस ret;
	पूर्ण

	/* now export our fileप्रणाली to lesser mortals */
	ret = रेजिस्टर_fileप्रणाली(&afs_fs_type);
	अगर (ret < 0) अणु
		kmem_cache_destroy(afs_inode_cachep);
		_leave(" = %d", ret);
		वापस ret;
	पूर्ण

	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * clean up the fileप्रणाली
 */
व्योम afs_fs_निकास(व्योम)
अणु
	_enter("");

	afs_mntpt_समाप्त_समयr();
	unरेजिस्टर_fileप्रणाली(&afs_fs_type);

	अगर (atomic_पढ़ो(&afs_count_active_inodes) != 0) अणु
		prपूर्णांकk("kAFS: %d active inode objects still present\n",
		       atomic_पढ़ो(&afs_count_active_inodes));
		BUG();
	पूर्ण

	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(afs_inode_cachep);
	_leave("");
पूर्ण

/*
 * Display the mount device name in /proc/mounts.
 */
अटल पूर्णांक afs_show_devname(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा afs_super_info *as = AFS_FS_S(root->d_sb);
	काष्ठा afs_volume *volume = as->volume;
	काष्ठा afs_cell *cell = as->cell;
	स्थिर अक्षर *suf = "";
	अक्षर pref = '%';

	अगर (as->dyn_root) अणु
		seq_माला_दो(m, "none");
		वापस 0;
	पूर्ण

	चयन (volume->type) अणु
	हाल AFSVL_RWVOL:
		अवरोध;
	हाल AFSVL_ROVOL:
		pref = '#';
		अगर (volume->type_क्रमce)
			suf = ".readonly";
		अवरोध;
	हाल AFSVL_BACKVOL:
		pref = '#';
		suf = ".backup";
		अवरोध;
	पूर्ण

	seq_म_लिखो(m, "%c%s:%s%s", pref, cell->name, volume->name, suf);
	वापस 0;
पूर्ण

/*
 * Display the mount options in /proc/mounts.
 */
अटल पूर्णांक afs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा afs_super_info *as = AFS_FS_S(root->d_sb);
	स्थिर अक्षर *p = शून्य;

	अगर (as->dyn_root)
		seq_माला_दो(m, ",dyn");
	अगर (test_bit(AFS_VNODE_AUTOCELL, &AFS_FS_I(d_inode(root))->flags))
		seq_माला_दो(m, ",autocell");
	चयन (as->flock_mode) अणु
	हाल afs_flock_mode_unset:	अवरोध;
	हाल afs_flock_mode_local:	p = "local";	अवरोध;
	हाल afs_flock_mode_खोलोafs:	p = "openafs";	अवरोध;
	हाल afs_flock_mode_strict:	p = "strict";	अवरोध;
	हाल afs_flock_mode_ग_लिखो:	p = "write";	अवरोध;
	पूर्ण
	अगर (p)
		seq_म_लिखो(m, ",flock=%s", p);

	वापस 0;
पूर्ण

/*
 * Parse the source name to get cell name, volume name, volume type and R/W
 * selector.
 *
 * This can be one of the following:
 *	"%[cell:]volume[.]"		R/W volume
 *	"#[cell:]volume[.]"		R/O or R/W volume (R/O parent),
 *					 or R/W (R/W parent) volume
 *	"%[cell:]volume.readonly"	R/O volume
 *	"#[cell:]volume.readonly"	R/O volume
 *	"%[cell:]volume.backup"		Backup volume
 *	"#[cell:]volume.backup"		Backup volume
 */
अटल पूर्णांक afs_parse_source(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा afs_fs_context *ctx = fc->fs_निजी;
	काष्ठा afs_cell *cell;
	स्थिर अक्षर *cellname, *suffix, *name = param->string;
	पूर्णांक cellnamesz;

	_enter(",%s", name);

	अगर (fc->source)
		वापस invalf(fc, "kAFS: Multiple sources not supported");

	अगर (!name) अणु
		prपूर्णांकk(KERN_ERR "kAFS: no volume name specified\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((name[0] != '%' && name[0] != '#') || !name[1]) अणु
		/* To use dynroot, we करोn't want to have to provide a source */
		अगर (म_भेद(name, "none") == 0) अणु
			ctx->no_cell = true;
			वापस 0;
		पूर्ण
		prपूर्णांकk(KERN_ERR "kAFS: unparsable volume name\n");
		वापस -EINVAL;
	पूर्ण

	/* determine the type of volume we're looking क्रम */
	अगर (name[0] == '%') अणु
		ctx->type = AFSVL_RWVOL;
		ctx->क्रमce = true;
	पूर्ण
	name++;

	/* split the cell name out अगर there is one */
	ctx->volname = म_अक्षर(name, ':');
	अगर (ctx->volname) अणु
		cellname = name;
		cellnamesz = ctx->volname - name;
		ctx->volname++;
	पूर्ण अन्यथा अणु
		ctx->volname = name;
		cellname = शून्य;
		cellnamesz = 0;
	पूर्ण

	/* the volume type is further affected by a possible suffix */
	suffix = म_खोजप(ctx->volname, '.');
	अगर (suffix) अणु
		अगर (म_भेद(suffix, ".readonly") == 0) अणु
			ctx->type = AFSVL_ROVOL;
			ctx->क्रमce = true;
		पूर्ण अन्यथा अगर (म_भेद(suffix, ".backup") == 0) अणु
			ctx->type = AFSVL_BACKVOL;
			ctx->क्रमce = true;
		पूर्ण अन्यथा अगर (suffix[1] == 0) अणु
		पूर्ण अन्यथा अणु
			suffix = शून्य;
		पूर्ण
	पूर्ण

	ctx->volnamesz = suffix ?
		suffix - ctx->volname : म_माप(ctx->volname);

	_debug("cell %*.*s [%p]",
	       cellnamesz, cellnamesz, cellname ?: "", ctx->cell);

	/* lookup the cell record */
	अगर (cellname) अणु
		cell = afs_lookup_cell(ctx->net, cellname, cellnamesz,
				       शून्य, false);
		अगर (IS_ERR(cell)) अणु
			pr_err("kAFS: unable to lookup cell '%*.*s'\n",
			       cellnamesz, cellnamesz, cellname ?: "");
			वापस PTR_ERR(cell);
		पूर्ण
		afs_unuse_cell(ctx->net, ctx->cell, afs_cell_trace_unuse_parse);
		afs_see_cell(cell, afs_cell_trace_see_source);
		ctx->cell = cell;
	पूर्ण

	_debug("CELL:%s [%p] VOLUME:%*.*s SUFFIX:%s TYPE:%d%s",
	       ctx->cell->name, ctx->cell,
	       ctx->volnamesz, ctx->volnamesz, ctx->volname,
	       suffix ?: "-", ctx->type, ctx->क्रमce ? " FORCE" : "");

	fc->source = param->string;
	param->string = शून्य;
	वापस 0;
पूर्ण

/*
 * Parse a single mount parameter.
 */
अटल पूर्णांक afs_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा fs_parse_result result;
	काष्ठा afs_fs_context *ctx = fc->fs_निजी;
	पूर्णांक opt;

	opt = fs_parse(fc, afs_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_source:
		वापस afs_parse_source(fc, param);

	हाल Opt_स्वतःcell:
		ctx->स्वतःcell = true;
		अवरोध;

	हाल Opt_dyn:
		ctx->dyn_root = true;
		अवरोध;

	हाल Opt_flock:
		ctx->flock_mode = result.uपूर्णांक_32;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * Validate the options, get the cell key and look up the volume.
 */
अटल पूर्णांक afs_validate_fc(काष्ठा fs_context *fc)
अणु
	काष्ठा afs_fs_context *ctx = fc->fs_निजी;
	काष्ठा afs_volume *volume;
	काष्ठा afs_cell *cell;
	काष्ठा key *key;
	पूर्णांक ret;

	अगर (!ctx->dyn_root) अणु
		अगर (ctx->no_cell) अणु
			pr_warn("kAFS: Can only specify source 'none' with -o dyn\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!ctx->cell) अणु
			pr_warn("kAFS: No cell specified\n");
			वापस -EDESTADDRREQ;
		पूर्ण

	reget_key:
		/* We try to करो the mount securely. */
		key = afs_request_key(ctx->cell);
		अगर (IS_ERR(key))
			वापस PTR_ERR(key);

		ctx->key = key;

		अगर (ctx->volume) अणु
			afs_put_volume(ctx->net, ctx->volume,
				       afs_volume_trace_put_validate_fc);
			ctx->volume = शून्य;
		पूर्ण

		अगर (test_bit(AFS_CELL_FL_CHECK_ALIAS, &ctx->cell->flags)) अणु
			ret = afs_cell_detect_alias(ctx->cell, key);
			अगर (ret < 0)
				वापस ret;
			अगर (ret == 1) अणु
				_debug("switch to alias");
				key_put(ctx->key);
				ctx->key = शून्य;
				cell = afs_use_cell(ctx->cell->alias_of,
						    afs_cell_trace_use_fc_alias);
				afs_unuse_cell(ctx->net, ctx->cell, afs_cell_trace_unuse_fc);
				ctx->cell = cell;
				जाओ reget_key;
			पूर्ण
		पूर्ण

		volume = afs_create_volume(ctx);
		अगर (IS_ERR(volume))
			वापस PTR_ERR(volume);

		ctx->volume = volume;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * check a superblock to see अगर it's the one we're looking क्रम
 */
अटल पूर्णांक afs_test_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा afs_fs_context *ctx = fc->fs_निजी;
	काष्ठा afs_super_info *as = AFS_FS_S(sb);

	वापस (as->net_ns == fc->net_ns &&
		as->volume &&
		as->volume->vid == ctx->volume->vid &&
		as->cell == ctx->cell &&
		!as->dyn_root);
पूर्ण

अटल पूर्णांक afs_dynroot_test_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा afs_super_info *as = AFS_FS_S(sb);

	वापस (as->net_ns == fc->net_ns &&
		as->dyn_root);
पूर्ण

अटल पूर्णांक afs_set_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	वापस set_anon_super(sb, शून्य);
पूर्ण

/*
 * fill in the superblock
 */
अटल पूर्णांक afs_fill_super(काष्ठा super_block *sb, काष्ठा afs_fs_context *ctx)
अणु
	काष्ठा afs_super_info *as = AFS_FS_S(sb);
	काष्ठा inode *inode = शून्य;
	पूर्णांक ret;

	_enter("");

	/* fill in the superblock */
	sb->s_blocksize		= PAGE_SIZE;
	sb->s_blocksize_bits	= PAGE_SHIFT;
	sb->s_maxbytes		= MAX_LFS_खाताSIZE;
	sb->s_magic		= AFS_FS_MAGIC;
	sb->s_op		= &afs_super_ops;
	अगर (!as->dyn_root)
		sb->s_xattr	= afs_xattr_handlers;
	ret = super_setup_bdi(sb);
	अगर (ret)
		वापस ret;

	/* allocate the root inode and dentry */
	अगर (as->dyn_root) अणु
		inode = afs_iget_pseuकरो_dir(sb, true);
	पूर्ण अन्यथा अणु
		प्र_लिखो(sb->s_id, "%llu", as->volume->vid);
		afs_activate_volume(as->volume);
		inode = afs_root_iget(sb, ctx->key);
	पूर्ण

	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	अगर (ctx->स्वतःcell || as->dyn_root)
		set_bit(AFS_VNODE_AUTOCELL, &AFS_FS_I(inode)->flags);

	ret = -ENOMEM;
	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root)
		जाओ error;

	अगर (as->dyn_root) अणु
		sb->s_d_op = &afs_dynroot_dentry_operations;
		ret = afs_dynroot_populate(sb);
		अगर (ret < 0)
			जाओ error;
	पूर्ण अन्यथा अणु
		sb->s_d_op = &afs_fs_dentry_operations;
		rcu_assign_poपूर्णांकer(as->volume->sb, sb);
	पूर्ण

	_leave(" = 0");
	वापस 0;

error:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

अटल काष्ठा afs_super_info *afs_alloc_sbi(काष्ठा fs_context *fc)
अणु
	काष्ठा afs_fs_context *ctx = fc->fs_निजी;
	काष्ठा afs_super_info *as;

	as = kzalloc(माप(काष्ठा afs_super_info), GFP_KERNEL);
	अगर (as) अणु
		as->net_ns = get_net(fc->net_ns);
		as->flock_mode = ctx->flock_mode;
		अगर (ctx->dyn_root) अणु
			as->dyn_root = true;
		पूर्ण अन्यथा अणु
			as->cell = afs_use_cell(ctx->cell, afs_cell_trace_use_sbi);
			as->volume = afs_get_volume(ctx->volume,
						    afs_volume_trace_get_alloc_sbi);
		पूर्ण
	पूर्ण
	वापस as;
पूर्ण

अटल व्योम afs_destroy_sbi(काष्ठा afs_super_info *as)
अणु
	अगर (as) अणु
		काष्ठा afs_net *net = afs_net(as->net_ns);
		afs_put_volume(net, as->volume, afs_volume_trace_put_destroy_sbi);
		afs_unuse_cell(net, as->cell, afs_cell_trace_unuse_sbi);
		put_net(as->net_ns);
		kमुक्त(as);
	पूर्ण
पूर्ण

अटल व्योम afs_समाप्त_super(काष्ठा super_block *sb)
अणु
	काष्ठा afs_super_info *as = AFS_FS_S(sb);

	अगर (as->dyn_root)
		afs_dynroot_depopulate(sb);

	/* Clear the callback पूर्णांकerests (which will करो ilookup5) beक्रमe
	 * deactivating the superblock.
	 */
	अगर (as->volume)
		rcu_assign_poपूर्णांकer(as->volume->sb, शून्य);
	समाप्त_anon_super(sb);
	अगर (as->volume)
		afs_deactivate_volume(as->volume);
	afs_destroy_sbi(as);
पूर्ण

/*
 * Get an AFS superblock and root directory.
 */
अटल पूर्णांक afs_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा afs_fs_context *ctx = fc->fs_निजी;
	काष्ठा super_block *sb;
	काष्ठा afs_super_info *as;
	पूर्णांक ret;

	ret = afs_validate_fc(fc);
	अगर (ret)
		जाओ error;

	_enter("");

	/* allocate a superblock info record */
	ret = -ENOMEM;
	as = afs_alloc_sbi(fc);
	अगर (!as)
		जाओ error;
	fc->s_fs_info = as;

	/* allocate a deviceless superblock */
	sb = sget_fc(fc,
		     as->dyn_root ? afs_dynroot_test_super : afs_test_super,
		     afs_set_super);
	अगर (IS_ERR(sb)) अणु
		ret = PTR_ERR(sb);
		जाओ error;
	पूर्ण

	अगर (!sb->s_root) अणु
		/* initial superblock/root creation */
		_debug("create");
		ret = afs_fill_super(sb, ctx);
		अगर (ret < 0)
			जाओ error_sb;
		sb->s_flags |= SB_ACTIVE;
	पूर्ण अन्यथा अणु
		_debug("reuse");
		ASSERTCMP(sb->s_flags, &, SB_ACTIVE);
	पूर्ण

	fc->root = dget(sb->s_root);
	trace_afs_get_tree(as->cell, as->volume);
	_leave(" = 0 [%p]", sb);
	वापस 0;

error_sb:
	deactivate_locked_super(sb);
error:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

अटल व्योम afs_मुक्त_fc(काष्ठा fs_context *fc)
अणु
	काष्ठा afs_fs_context *ctx = fc->fs_निजी;

	afs_destroy_sbi(fc->s_fs_info);
	afs_put_volume(ctx->net, ctx->volume, afs_volume_trace_put_मुक्त_fc);
	afs_unuse_cell(ctx->net, ctx->cell, afs_cell_trace_unuse_fc);
	key_put(ctx->key);
	kमुक्त(ctx);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations afs_context_ops = अणु
	.मुक्त		= afs_मुक्त_fc,
	.parse_param	= afs_parse_param,
	.get_tree	= afs_get_tree,
पूर्ण;

/*
 * Set up the fileप्रणाली mount context.
 */
अटल पूर्णांक afs_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा afs_fs_context *ctx;
	काष्ठा afs_cell *cell;

	ctx = kzalloc(माप(काष्ठा afs_fs_context), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->type = AFSVL_ROVOL;
	ctx->net = afs_net(fc->net_ns);

	/* Default to the workstation cell. */
	cell = afs_find_cell(ctx->net, शून्य, 0, afs_cell_trace_use_fc);
	अगर (IS_ERR(cell))
		cell = शून्य;
	ctx->cell = cell;

	fc->fs_निजी = ctx;
	fc->ops = &afs_context_ops;
	वापस 0;
पूर्ण

/*
 * Initialise an inode cache slab element prior to any use.  Note that
 * afs_alloc_inode() *must* reset anything that could incorrectly leak from one
 * inode to another.
 */
अटल व्योम afs_i_init_once(व्योम *_vnode)
अणु
	काष्ठा afs_vnode *vnode = _vnode;

	स_रखो(vnode, 0, माप(*vnode));
	inode_init_once(&vnode->vfs_inode);
	mutex_init(&vnode->io_lock);
	init_rwsem(&vnode->validate_lock);
	spin_lock_init(&vnode->wb_lock);
	spin_lock_init(&vnode->lock);
	INIT_LIST_HEAD(&vnode->wb_keys);
	INIT_LIST_HEAD(&vnode->pending_locks);
	INIT_LIST_HEAD(&vnode->granted_locks);
	INIT_DELAYED_WORK(&vnode->lock_work, afs_lock_work);
	seqlock_init(&vnode->cb_lock);
पूर्ण

/*
 * allocate an AFS inode काष्ठा from our slab cache
 */
अटल काष्ठा inode *afs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा afs_vnode *vnode;

	vnode = kmem_cache_alloc(afs_inode_cachep, GFP_KERNEL);
	अगर (!vnode)
		वापस शून्य;

	atomic_inc(&afs_count_active_inodes);

	/* Reset anything that shouldn't leak from one inode to the next. */
	स_रखो(&vnode->fid, 0, माप(vnode->fid));
	स_रखो(&vnode->status, 0, माप(vnode->status));

	vnode->volume		= शून्य;
	vnode->lock_key		= शून्य;
	vnode->permit_cache	= शून्य;
#अगर_घोषित CONFIG_AFS_FSCACHE
	vnode->cache		= शून्य;
#पूर्ण_अगर

	vnode->flags		= 1 << AFS_VNODE_UNSET;
	vnode->lock_state	= AFS_VNODE_LOCK_NONE;

	init_rwsem(&vnode->सूची_हटाओ_lock);

	_leave(" = %p", &vnode->vfs_inode);
	वापस &vnode->vfs_inode;
पूर्ण

अटल व्योम afs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(afs_inode_cachep, AFS_FS_I(inode));
पूर्ण

/*
 * destroy an AFS inode काष्ठा
 */
अटल व्योम afs_destroy_inode(काष्ठा inode *inode)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);

	_enter("%p{%llx:%llu}", inode, vnode->fid.vid, vnode->fid.vnode);

	_debug("DESTROY INODE %p", inode);

	atomic_dec(&afs_count_active_inodes);
पूर्ण

अटल व्योम afs_get_volume_status_success(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_volume_status *vs = &op->volstatus.vs;
	काष्ठा kstatfs *buf = op->volstatus.buf;

	अगर (vs->max_quota == 0)
		buf->f_blocks = vs->part_max_blocks;
	अन्यथा
		buf->f_blocks = vs->max_quota;

	अगर (buf->f_blocks > vs->blocks_in_use)
		buf->f_bavail = buf->f_bमुक्त =
			buf->f_blocks - vs->blocks_in_use;
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_get_volume_status_operation = अणु
	.issue_afs_rpc	= afs_fs_get_volume_status,
	.issue_yfs_rpc	= yfs_fs_get_volume_status,
	.success	= afs_get_volume_status_success,
पूर्ण;

/*
 * वापस inक्रमmation about an AFS volume
 */
अटल पूर्णांक afs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा afs_super_info *as = AFS_FS_S(dentry->d_sb);
	काष्ठा afs_operation *op;
	काष्ठा afs_vnode *vnode = AFS_FS_I(d_inode(dentry));

	buf->f_type	= dentry->d_sb->s_magic;
	buf->f_bsize	= AFS_BLOCK_SIZE;
	buf->f_namelen	= AFSNAMEMAX - 1;

	अगर (as->dyn_root) अणु
		buf->f_blocks	= 1;
		buf->f_bavail	= 0;
		buf->f_bमुक्त	= 0;
		वापस 0;
	पूर्ण

	op = afs_alloc_operation(शून्य, as->volume);
	अगर (IS_ERR(op))
		वापस PTR_ERR(op);

	afs_op_set_vnode(op, 0, vnode);
	op->nr_files		= 1;
	op->volstatus.buf	= buf;
	op->ops			= &afs_get_volume_status_operation;
	वापस afs_करो_sync_operation(op);
पूर्ण
