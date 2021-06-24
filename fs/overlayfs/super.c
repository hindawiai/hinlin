<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2011 Novell Inc.
 */

#समावेश <uapi/linux/magic.h>
#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/xattr.h>
#समावेश <linux/mount.h>
#समावेश <linux/parser.h>
#समावेश <linux/module.h>
#समावेश <linux/statfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/exportfs.h>
#समावेश "overlayfs.h"

MODULE_AUTHOR("Miklos Szeredi <miklos@szeredi.hu>");
MODULE_DESCRIPTION("Overlay filesystem");
MODULE_LICENSE("GPL");


काष्ठा ovl_dir_cache;

#घोषणा OVL_MAX_STACK 500

अटल bool ovl_redirect_dir_def = IS_ENABLED(CONFIG_OVERLAY_FS_REसूचीECT_सूची);
module_param_named(redirect_dir, ovl_redirect_dir_def, bool, 0644);
MODULE_PARM_DESC(redirect_dir,
		 "Default to on or off for the redirect_dir feature");

अटल bool ovl_redirect_always_follow =
	IS_ENABLED(CONFIG_OVERLAY_FS_REसूचीECT_ALWAYS_FOLLOW);
module_param_named(redirect_always_follow, ovl_redirect_always_follow,
		   bool, 0644);
MODULE_PARM_DESC(redirect_always_follow,
		 "Follow redirects even if redirect_dir feature is turned off");

अटल bool ovl_index_def = IS_ENABLED(CONFIG_OVERLAY_FS_INDEX);
module_param_named(index, ovl_index_def, bool, 0644);
MODULE_PARM_DESC(index,
		 "Default to on or off for the inodes index feature");

अटल bool ovl_nfs_export_def = IS_ENABLED(CONFIG_OVERLAY_FS_NFS_EXPORT);
module_param_named(nfs_export, ovl_nfs_export_def, bool, 0644);
MODULE_PARM_DESC(nfs_export,
		 "Default to on or off for the NFS export feature");

अटल bool ovl_xino_स्वतः_def = IS_ENABLED(CONFIG_OVERLAY_FS_XINO_AUTO);
module_param_named(xino_स्वतः, ovl_xino_स्वतः_def, bool, 0644);
MODULE_PARM_DESC(xino_स्वतः,
		 "Auto enable xino feature");

अटल व्योम ovl_entry_stack_मुक्त(काष्ठा ovl_entry *oe)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < oe->numlower; i++)
		dput(oe->lowerstack[i].dentry);
पूर्ण

अटल bool ovl_metacopy_def = IS_ENABLED(CONFIG_OVERLAY_FS_METACOPY);
module_param_named(metacopy, ovl_metacopy_def, bool, 0644);
MODULE_PARM_DESC(metacopy,
		 "Default to on or off for the metadata only copy up feature");

अटल व्योम ovl_dentry_release(काष्ठा dentry *dentry)
अणु
	काष्ठा ovl_entry *oe = dentry->d_fsdata;

	अगर (oe) अणु
		ovl_entry_stack_मुक्त(oe);
		kमुक्त_rcu(oe, rcu);
	पूर्ण
पूर्ण

अटल काष्ठा dentry *ovl_d_real(काष्ठा dentry *dentry,
				 स्थिर काष्ठा inode *inode)
अणु
	काष्ठा dentry *real = शून्य, *lower;

	/* It's an overlay file */
	अगर (inode && d_inode(dentry) == inode)
		वापस dentry;

	अगर (!d_is_reg(dentry)) अणु
		अगर (!inode || inode == d_inode(dentry))
			वापस dentry;
		जाओ bug;
	पूर्ण

	real = ovl_dentry_upper(dentry);
	अगर (real && (inode == d_inode(real)))
		वापस real;

	अगर (real && !inode && ovl_has_upperdata(d_inode(dentry)))
		वापस real;

	lower = ovl_dentry_lowerdata(dentry);
	अगर (!lower)
		जाओ bug;
	real = lower;

	/* Handle recursion */
	real = d_real(real, inode);

	अगर (!inode || inode == d_inode(real))
		वापस real;
bug:
	WARN(1, "%s(%pd4, %s:%lu): real dentry (%p/%lu) not found\n",
	     __func__, dentry, inode ? inode->i_sb->s_id : "NULL",
	     inode ? inode->i_ino : 0, real,
	     real && d_inode(real) ? d_inode(real)->i_ino : 0);
	वापस dentry;
पूर्ण

अटल पूर्णांक ovl_revalidate_real(काष्ठा dentry *d, अचिन्हित पूर्णांक flags, bool weak)
अणु
	पूर्णांक ret = 1;

	अगर (weak) अणु
		अगर (d->d_flags & DCACHE_OP_WEAK_REVALIDATE)
			ret =  d->d_op->d_weak_revalidate(d, flags);
	पूर्ण अन्यथा अगर (d->d_flags & DCACHE_OP_REVALIDATE) अणु
		ret = d->d_op->d_revalidate(d, flags);
		अगर (!ret) अणु
			अगर (!(flags & LOOKUP_RCU))
				d_invalidate(d);
			ret = -ESTALE;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ovl_dentry_revalidate_common(काष्ठा dentry *dentry,
					अचिन्हित पूर्णांक flags, bool weak)
अणु
	काष्ठा ovl_entry *oe = dentry->d_fsdata;
	काष्ठा dentry *upper;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 1;

	upper = ovl_dentry_upper(dentry);
	अगर (upper)
		ret = ovl_revalidate_real(upper, flags, weak);

	क्रम (i = 0; ret > 0 && i < oe->numlower; i++) अणु
		ret = ovl_revalidate_real(oe->lowerstack[i].dentry, flags,
					  weak);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ovl_dentry_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	वापस ovl_dentry_revalidate_common(dentry, flags, false);
पूर्ण

अटल पूर्णांक ovl_dentry_weak_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	वापस ovl_dentry_revalidate_common(dentry, flags, true);
पूर्ण

अटल स्थिर काष्ठा dentry_operations ovl_dentry_operations = अणु
	.d_release = ovl_dentry_release,
	.d_real = ovl_d_real,
	.d_revalidate = ovl_dentry_revalidate,
	.d_weak_revalidate = ovl_dentry_weak_revalidate,
पूर्ण;

अटल काष्ठा kmem_cache *ovl_inode_cachep;

अटल काष्ठा inode *ovl_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा ovl_inode *oi = kmem_cache_alloc(ovl_inode_cachep, GFP_KERNEL);

	अगर (!oi)
		वापस शून्य;

	oi->cache = शून्य;
	oi->redirect = शून्य;
	oi->version = 0;
	oi->flags = 0;
	oi->__upperdentry = शून्य;
	oi->lower = शून्य;
	oi->lowerdata = शून्य;
	mutex_init(&oi->lock);

	वापस &oi->vfs_inode;
पूर्ण

अटल व्योम ovl_मुक्त_inode(काष्ठा inode *inode)
अणु
	काष्ठा ovl_inode *oi = OVL_I(inode);

	kमुक्त(oi->redirect);
	mutex_destroy(&oi->lock);
	kmem_cache_मुक्त(ovl_inode_cachep, oi);
पूर्ण

अटल व्योम ovl_destroy_inode(काष्ठा inode *inode)
अणु
	काष्ठा ovl_inode *oi = OVL_I(inode);

	dput(oi->__upperdentry);
	iput(oi->lower);
	अगर (S_ISसूची(inode->i_mode))
		ovl_dir_cache_मुक्त(inode);
	अन्यथा
		iput(oi->lowerdata);
पूर्ण

अटल व्योम ovl_मुक्त_fs(काष्ठा ovl_fs *ofs)
अणु
	काष्ठा vfsmount **mounts;
	अचिन्हित i;

	iput(ofs->workbasedir_trap);
	iput(ofs->indexdir_trap);
	iput(ofs->workdir_trap);
	dput(ofs->whiteout);
	dput(ofs->indexdir);
	dput(ofs->workdir);
	अगर (ofs->workdir_locked)
		ovl_inuse_unlock(ofs->workbasedir);
	dput(ofs->workbasedir);
	अगर (ofs->upperdir_locked)
		ovl_inuse_unlock(ovl_upper_mnt(ofs)->mnt_root);

	/* Hack!  Reuse ofs->layers as a vfsmount array beक्रमe मुक्तing it */
	mounts = (काष्ठा vfsmount **) ofs->layers;
	क्रम (i = 0; i < ofs->numlayer; i++) अणु
		iput(ofs->layers[i].trap);
		mounts[i] = ofs->layers[i].mnt;
	पूर्ण
	kern_unmount_array(mounts, ofs->numlayer);
	kमुक्त(ofs->layers);
	क्रम (i = 0; i < ofs->numfs; i++)
		मुक्त_anon_bdev(ofs->fs[i].pseuकरो_dev);
	kमुक्त(ofs->fs);

	kमुक्त(ofs->config.lowerdir);
	kमुक्त(ofs->config.upperdir);
	kमुक्त(ofs->config.workdir);
	kमुक्त(ofs->config.redirect_mode);
	अगर (ofs->creator_cred)
		put_cred(ofs->creator_cred);
	kमुक्त(ofs);
पूर्ण

अटल व्योम ovl_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;

	ovl_मुक्त_fs(ofs);
पूर्ण

/* Sync real dirty inodes in upper fileप्रणाली (अगर it exists) */
अटल पूर्णांक ovl_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;
	काष्ठा super_block *upper_sb;
	पूर्णांक ret;

	ret = ovl_sync_status(ofs);
	/*
	 * We have to always set the err, because the वापस value isn't
	 * checked in syncfs, and instead indirectly वापस an error via
	 * the sb's ग_लिखोback errseq, which VFS inspects after this call.
	 */
	अगर (ret < 0) अणु
		errseq_set(&sb->s_wb_err, -EIO);
		वापस -EIO;
	पूर्ण

	अगर (!ret)
		वापस ret;

	/*
	 * Not called क्रम sync(2) call or an emergency sync (SB_I_SKIP_SYNC).
	 * All the super blocks will be iterated, including upper_sb.
	 *
	 * If this is a syncfs(2) call, then we करो need to call
	 * sync_fileप्रणाली() on upper_sb, but enough अगर we करो it when being
	 * called with रुको == 1.
	 */
	अगर (!रुको)
		वापस 0;

	upper_sb = ovl_upper_mnt(ofs)->mnt_sb;

	करोwn_पढ़ो(&upper_sb->s_umount);
	ret = sync_fileप्रणाली(upper_sb);
	up_पढ़ो(&upper_sb->s_umount);

	वापस ret;
पूर्ण

/**
 * ovl_statfs
 * @sb: The overlayfs super block
 * @buf: The काष्ठा kstatfs to fill in with stats
 *
 * Get the fileप्रणाली statistics.  As ग_लिखोs always target the upper layer
 * fileप्रणाली pass the statfs to the upper fileप्रणाली (अगर it exists)
 */
अटल पूर्णांक ovl_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा ovl_fs *ofs = dentry->d_sb->s_fs_info;
	काष्ठा dentry *root_dentry = dentry->d_sb->s_root;
	काष्ठा path path;
	पूर्णांक err;

	ovl_path_real(root_dentry, &path);

	err = vfs_statfs(&path, buf);
	अगर (!err) अणु
		buf->f_namelen = ofs->namelen;
		buf->f_type = OVERLAYFS_SUPER_MAGIC;
	पूर्ण

	वापस err;
पूर्ण

/* Will this overlay be क्रमced to mount/remount ro? */
अटल bool ovl_क्रमce_पढ़ोonly(काष्ठा ovl_fs *ofs)
अणु
	वापस (!ovl_upper_mnt(ofs) || !ofs->workdir);
पूर्ण

अटल स्थिर अक्षर *ovl_redirect_mode_def(व्योम)
अणु
	वापस ovl_redirect_dir_def ? "on" : "off";
पूर्ण

अटल स्थिर अक्षर * स्थिर ovl_xino_str[] = अणु
	"off",
	"auto",
	"on",
पूर्ण;

अटल अंतरभूत पूर्णांक ovl_xino_def(व्योम)
अणु
	वापस ovl_xino_स्वतः_def ? OVL_XINO_AUTO : OVL_XINO_OFF;
पूर्ण

/**
 * ovl_show_options
 *
 * Prपूर्णांकs the mount options क्रम a given superblock.
 * Returns zero; करोes not fail.
 */
अटल पूर्णांक ovl_show_options(काष्ठा seq_file *m, काष्ठा dentry *dentry)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा ovl_fs *ofs = sb->s_fs_info;

	seq_show_option(m, "lowerdir", ofs->config.lowerdir);
	अगर (ofs->config.upperdir) अणु
		seq_show_option(m, "upperdir", ofs->config.upperdir);
		seq_show_option(m, "workdir", ofs->config.workdir);
	पूर्ण
	अगर (ofs->config.शेष_permissions)
		seq_माला_दो(m, ",default_permissions");
	अगर (म_भेद(ofs->config.redirect_mode, ovl_redirect_mode_def()) != 0)
		seq_म_लिखो(m, ",redirect_dir=%s", ofs->config.redirect_mode);
	अगर (ofs->config.index != ovl_index_def)
		seq_म_लिखो(m, ",index=%s", ofs->config.index ? "on" : "off");
	अगर (!ofs->config.uuid)
		seq_माला_दो(m, ",uuid=off");
	अगर (ofs->config.nfs_export != ovl_nfs_export_def)
		seq_म_लिखो(m, ",nfs_export=%s", ofs->config.nfs_export ?
						"on" : "off");
	अगर (ofs->config.xino != ovl_xino_def() && !ovl_same_fs(sb))
		seq_म_लिखो(m, ",xino=%s", ovl_xino_str[ofs->config.xino]);
	अगर (ofs->config.metacopy != ovl_metacopy_def)
		seq_म_लिखो(m, ",metacopy=%s",
			   ofs->config.metacopy ? "on" : "off");
	अगर (ofs->config.ovl_अस्थिर)
		seq_माला_दो(m, ",volatile");
	अगर (ofs->config.userxattr)
		seq_माला_दो(m, ",userxattr");
	वापस 0;
पूर्ण

अटल पूर्णांक ovl_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	काष्ठा ovl_fs *ofs = sb->s_fs_info;
	काष्ठा super_block *upper_sb;
	पूर्णांक ret = 0;

	अगर (!(*flags & SB_RDONLY) && ovl_क्रमce_पढ़ोonly(ofs))
		वापस -EROFS;

	अगर (*flags & SB_RDONLY && !sb_rकरोnly(sb)) अणु
		upper_sb = ovl_upper_mnt(ofs)->mnt_sb;
		अगर (ovl_should_sync(ofs)) अणु
			करोwn_पढ़ो(&upper_sb->s_umount);
			ret = sync_fileप्रणाली(upper_sb);
			up_पढ़ो(&upper_sb->s_umount);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा super_operations ovl_super_operations = अणु
	.alloc_inode	= ovl_alloc_inode,
	.मुक्त_inode	= ovl_मुक्त_inode,
	.destroy_inode	= ovl_destroy_inode,
	.drop_inode	= generic_delete_inode,
	.put_super	= ovl_put_super,
	.sync_fs	= ovl_sync_fs,
	.statfs		= ovl_statfs,
	.show_options	= ovl_show_options,
	.remount_fs	= ovl_remount,
पूर्ण;

क्रमागत अणु
	OPT_LOWERसूची,
	OPT_UPPERसूची,
	OPT_WORKसूची,
	OPT_DEFAULT_PERMISSIONS,
	OPT_REसूचीECT_सूची,
	OPT_INDEX_ON,
	OPT_INDEX_OFF,
	OPT_UUID_ON,
	OPT_UUID_OFF,
	OPT_NFS_EXPORT_ON,
	OPT_USERXATTR,
	OPT_NFS_EXPORT_OFF,
	OPT_XINO_ON,
	OPT_XINO_OFF,
	OPT_XINO_AUTO,
	OPT_METACOPY_ON,
	OPT_METACOPY_OFF,
	OPT_VOLATILE,
	OPT_ERR,
पूर्ण;

अटल स्थिर match_table_t ovl_tokens = अणु
	अणुOPT_LOWERसूची,			"lowerdir=%s"पूर्ण,
	अणुOPT_UPPERसूची,			"upperdir=%s"पूर्ण,
	अणुOPT_WORKसूची,			"workdir=%s"पूर्ण,
	अणुOPT_DEFAULT_PERMISSIONS,	"default_permissions"पूर्ण,
	अणुOPT_REसूचीECT_सूची,		"redirect_dir=%s"पूर्ण,
	अणुOPT_INDEX_ON,			"index=on"पूर्ण,
	अणुOPT_INDEX_OFF,			"index=off"पूर्ण,
	अणुOPT_USERXATTR,			"userxattr"पूर्ण,
	अणुOPT_UUID_ON,			"uuid=on"पूर्ण,
	अणुOPT_UUID_OFF,			"uuid=off"पूर्ण,
	अणुOPT_NFS_EXPORT_ON,		"nfs_export=on"पूर्ण,
	अणुOPT_NFS_EXPORT_OFF,		"nfs_export=off"पूर्ण,
	अणुOPT_XINO_ON,			"xino=on"पूर्ण,
	अणुOPT_XINO_OFF,			"xino=off"पूर्ण,
	अणुOPT_XINO_AUTO,			"xino=auto"पूर्ण,
	अणुOPT_METACOPY_ON,		"metacopy=on"पूर्ण,
	अणुOPT_METACOPY_OFF,		"metacopy=off"पूर्ण,
	अणुOPT_VOLATILE,			"volatile"पूर्ण,
	अणुOPT_ERR,			शून्यपूर्ण
पूर्ण;

अटल अक्षर *ovl_next_opt(अक्षर **s)
अणु
	अक्षर *sbegin = *s;
	अक्षर *p;

	अगर (sbegin == शून्य)
		वापस शून्य;

	क्रम (p = sbegin; *p; p++) अणु
		अगर (*p == '\\') अणु
			p++;
			अगर (!*p)
				अवरोध;
		पूर्ण अन्यथा अगर (*p == ',') अणु
			*p = '\0';
			*s = p + 1;
			वापस sbegin;
		पूर्ण
	पूर्ण
	*s = शून्य;
	वापस sbegin;
पूर्ण

अटल पूर्णांक ovl_parse_redirect_mode(काष्ठा ovl_config *config, स्थिर अक्षर *mode)
अणु
	अगर (म_भेद(mode, "on") == 0) अणु
		config->redirect_dir = true;
		/*
		 * Does not make sense to have redirect creation without
		 * redirect following.
		 */
		config->redirect_follow = true;
	पूर्ण अन्यथा अगर (म_भेद(mode, "follow") == 0) अणु
		config->redirect_follow = true;
	पूर्ण अन्यथा अगर (म_भेद(mode, "off") == 0) अणु
		अगर (ovl_redirect_always_follow)
			config->redirect_follow = true;
	पूर्ण अन्यथा अगर (म_भेद(mode, "nofollow") != 0) अणु
		pr_err("bad mount option \"redirect_dir=%s\"\n",
		       mode);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ovl_parse_opt(अक्षर *opt, काष्ठा ovl_config *config)
अणु
	अक्षर *p;
	पूर्णांक err;
	bool metacopy_opt = false, redirect_opt = false;
	bool nfs_export_opt = false, index_opt = false;

	config->redirect_mode = kstrdup(ovl_redirect_mode_def(), GFP_KERNEL);
	अगर (!config->redirect_mode)
		वापस -ENOMEM;

	जबतक ((p = ovl_next_opt(&opt)) != शून्य) अणु
		पूर्णांक token;
		substring_t args[MAX_OPT_ARGS];

		अगर (!*p)
			जारी;

		token = match_token(p, ovl_tokens, args);
		चयन (token) अणु
		हाल OPT_UPPERसूची:
			kमुक्त(config->upperdir);
			config->upperdir = match_strdup(&args[0]);
			अगर (!config->upperdir)
				वापस -ENOMEM;
			अवरोध;

		हाल OPT_LOWERसूची:
			kमुक्त(config->lowerdir);
			config->lowerdir = match_strdup(&args[0]);
			अगर (!config->lowerdir)
				वापस -ENOMEM;
			अवरोध;

		हाल OPT_WORKसूची:
			kमुक्त(config->workdir);
			config->workdir = match_strdup(&args[0]);
			अगर (!config->workdir)
				वापस -ENOMEM;
			अवरोध;

		हाल OPT_DEFAULT_PERMISSIONS:
			config->शेष_permissions = true;
			अवरोध;

		हाल OPT_REसूचीECT_सूची:
			kमुक्त(config->redirect_mode);
			config->redirect_mode = match_strdup(&args[0]);
			अगर (!config->redirect_mode)
				वापस -ENOMEM;
			redirect_opt = true;
			अवरोध;

		हाल OPT_INDEX_ON:
			config->index = true;
			index_opt = true;
			अवरोध;

		हाल OPT_INDEX_OFF:
			config->index = false;
			index_opt = true;
			अवरोध;

		हाल OPT_UUID_ON:
			config->uuid = true;
			अवरोध;

		हाल OPT_UUID_OFF:
			config->uuid = false;
			अवरोध;

		हाल OPT_NFS_EXPORT_ON:
			config->nfs_export = true;
			nfs_export_opt = true;
			अवरोध;

		हाल OPT_NFS_EXPORT_OFF:
			config->nfs_export = false;
			nfs_export_opt = true;
			अवरोध;

		हाल OPT_XINO_ON:
			config->xino = OVL_XINO_ON;
			अवरोध;

		हाल OPT_XINO_OFF:
			config->xino = OVL_XINO_OFF;
			अवरोध;

		हाल OPT_XINO_AUTO:
			config->xino = OVL_XINO_AUTO;
			अवरोध;

		हाल OPT_METACOPY_ON:
			config->metacopy = true;
			metacopy_opt = true;
			अवरोध;

		हाल OPT_METACOPY_OFF:
			config->metacopy = false;
			metacopy_opt = true;
			अवरोध;

		हाल OPT_VOLATILE:
			config->ovl_अस्थिर = true;
			अवरोध;

		हाल OPT_USERXATTR:
			config->userxattr = true;
			अवरोध;

		शेष:
			pr_err("unrecognized mount option \"%s\" or missing value\n",
					p);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Workdir/index are useless in non-upper mount */
	अगर (!config->upperdir) अणु
		अगर (config->workdir) अणु
			pr_info("option \"workdir=%s\" is useless in a non-upper mount, ignore\n",
				config->workdir);
			kमुक्त(config->workdir);
			config->workdir = शून्य;
		पूर्ण
		अगर (config->index && index_opt) अणु
			pr_info("option \"index=on\" is useless in a non-upper mount, ignore\n");
			index_opt = false;
		पूर्ण
		config->index = false;
	पूर्ण

	अगर (!config->upperdir && config->ovl_अस्थिर) अणु
		pr_info("option \"volatile\" is meaningless in a non-upper mount, ignoring it.\n");
		config->ovl_अस्थिर = false;
	पूर्ण

	err = ovl_parse_redirect_mode(config, config->redirect_mode);
	अगर (err)
		वापस err;

	/*
	 * This is to make the logic below simpler.  It करोesn't make any other
	 * dअगरference, since config->redirect_dir is only used क्रम upper.
	 */
	अगर (!config->upperdir && config->redirect_follow)
		config->redirect_dir = true;

	/* Resolve metacopy -> redirect_dir dependency */
	अगर (config->metacopy && !config->redirect_dir) अणु
		अगर (metacopy_opt && redirect_opt) अणु
			pr_err("conflicting options: metacopy=on,redirect_dir=%s\n",
			       config->redirect_mode);
			वापस -EINVAL;
		पूर्ण
		अगर (redirect_opt) अणु
			/*
			 * There was an explicit redirect_dir=... that resulted
			 * in this conflict.
			 */
			pr_info("disabling metacopy due to redirect_dir=%s\n",
				config->redirect_mode);
			config->metacopy = false;
		पूर्ण अन्यथा अणु
			/* Automatically enable redirect otherwise. */
			config->redirect_follow = config->redirect_dir = true;
		पूर्ण
	पूर्ण

	/* Resolve nfs_export -> index dependency */
	अगर (config->nfs_export && !config->index) अणु
		अगर (!config->upperdir && config->redirect_follow) अणु
			pr_info("NFS export requires \"redirect_dir=nofollow\" on non-upper mount, falling back to nfs_export=off.\n");
			config->nfs_export = false;
		पूर्ण अन्यथा अगर (nfs_export_opt && index_opt) अणु
			pr_err("conflicting options: nfs_export=on,index=off\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (index_opt) अणु
			/*
			 * There was an explicit index=off that resulted
			 * in this conflict.
			 */
			pr_info("disabling nfs_export due to index=off\n");
			config->nfs_export = false;
		पूर्ण अन्यथा अणु
			/* Automatically enable index otherwise. */
			config->index = true;
		पूर्ण
	पूर्ण

	/* Resolve nfs_export -> !metacopy dependency */
	अगर (config->nfs_export && config->metacopy) अणु
		अगर (nfs_export_opt && metacopy_opt) अणु
			pr_err("conflicting options: nfs_export=on,metacopy=on\n");
			वापस -EINVAL;
		पूर्ण
		अगर (metacopy_opt) अणु
			/*
			 * There was an explicit metacopy=on that resulted
			 * in this conflict.
			 */
			pr_info("disabling nfs_export due to metacopy=on\n");
			config->nfs_export = false;
		पूर्ण अन्यथा अणु
			/*
			 * There was an explicit nfs_export=on that resulted
			 * in this conflict.
			 */
			pr_info("disabling metacopy due to nfs_export=on\n");
			config->metacopy = false;
		पूर्ण
	पूर्ण


	/* Resolve userxattr -> !redirect && !metacopy dependency */
	अगर (config->userxattr) अणु
		अगर (config->redirect_follow && redirect_opt) अणु
			pr_err("conflicting options: userxattr,redirect_dir=%s\n",
			       config->redirect_mode);
			वापस -EINVAL;
		पूर्ण
		अगर (config->metacopy && metacopy_opt) अणु
			pr_err("conflicting options: userxattr,metacopy=on\n");
			वापस -EINVAL;
		पूर्ण
		/*
		 * Silently disable शेष setting of redirect and metacopy.
		 * This shall be the शेष in the future as well: these
		 * options must be explicitly enabled अगर used together with
		 * userxattr.
		 */
		config->redirect_dir = config->redirect_follow = false;
		config->metacopy = false;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा OVL_WORKसूची_NAME "work"
#घोषणा OVL_INDEXसूची_NAME "index"

अटल काष्ठा dentry *ovl_workdir_create(काष्ठा ovl_fs *ofs,
					 स्थिर अक्षर *name, bool persist)
अणु
	काष्ठा inode *dir =  ofs->workbasedir->d_inode;
	काष्ठा vfsmount *mnt = ovl_upper_mnt(ofs);
	काष्ठा dentry *work;
	पूर्णांक err;
	bool retried = false;

	inode_lock_nested(dir, I_MUTEX_PARENT);
retry:
	work = lookup_one_len(name, ofs->workbasedir, म_माप(name));

	अगर (!IS_ERR(work)) अणु
		काष्ठा iattr attr = अणु
			.ia_valid = ATTR_MODE,
			.ia_mode = S_IFसूची | 0,
		पूर्ण;

		अगर (work->d_inode) अणु
			err = -EEXIST;
			अगर (retried)
				जाओ out_dput;

			अगर (persist)
				जाओ out_unlock;

			retried = true;
			err = ovl_workdir_cleanup(dir, mnt, work, 0);
			dput(work);
			अगर (err == -EINVAL) अणु
				work = ERR_PTR(err);
				जाओ out_unlock;
			पूर्ण
			जाओ retry;
		पूर्ण

		work = ovl_create_real(dir, work, OVL_CATTR(attr.ia_mode));
		err = PTR_ERR(work);
		अगर (IS_ERR(work))
			जाओ out_err;

		/*
		 * Try to हटाओ POSIX ACL xattrs from workdir.  We are good अगर:
		 *
		 * a) success (there was a POSIX ACL xattr and was हटाओd)
		 * b) -ENODATA (there was no POSIX ACL xattr)
		 * c) -EOPNOTSUPP (POSIX ACL xattrs are not supported)
		 *
		 * There are various other error values that could effectively
		 * mean that the xattr करोesn't exist (e.g. -दुस्फल is वापसed
		 * अगर the xattr name is too दीर्घ), but the set of fileप्रणालीs
		 * allowed as upper are limited to "normal" ones, where checking
		 * क्रम the above two errors is sufficient.
		 */
		err = vfs_हटाओxattr(&init_user_ns, work,
				      XATTR_NAME_POSIX_ACL_DEFAULT);
		अगर (err && err != -ENODATA && err != -EOPNOTSUPP)
			जाओ out_dput;

		err = vfs_हटाओxattr(&init_user_ns, work,
				      XATTR_NAME_POSIX_ACL_ACCESS);
		अगर (err && err != -ENODATA && err != -EOPNOTSUPP)
			जाओ out_dput;

		/* Clear any inherited mode bits */
		inode_lock(work->d_inode);
		err = notअगरy_change(&init_user_ns, work, &attr, शून्य);
		inode_unlock(work->d_inode);
		अगर (err)
			जाओ out_dput;
	पूर्ण अन्यथा अणु
		err = PTR_ERR(work);
		जाओ out_err;
	पूर्ण
out_unlock:
	inode_unlock(dir);
	वापस work;

out_dput:
	dput(work);
out_err:
	pr_warn("failed to create directory %s/%s (errno: %i); mounting read-only\n",
		ofs->config.workdir, name, -err);
	work = शून्य;
	जाओ out_unlock;
पूर्ण

अटल व्योम ovl_unescape(अक्षर *s)
अणु
	अक्षर *d = s;

	क्रम (;; s++, d++) अणु
		अगर (*s == '\\')
			s++;
		*d = *s;
		अगर (!*s)
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ovl_mount_dir_noesc(स्थिर अक्षर *name, काष्ठा path *path)
अणु
	पूर्णांक err = -EINVAL;

	अगर (!*name) अणु
		pr_err("empty lowerdir\n");
		जाओ out;
	पूर्ण
	err = kern_path(name, LOOKUP_FOLLOW, path);
	अगर (err) अणु
		pr_err("failed to resolve '%s': %i\n", name, err);
		जाओ out;
	पूर्ण
	err = -EINVAL;
	अगर (ovl_dentry_weird(path->dentry)) अणु
		pr_err("filesystem on '%s' not supported\n", name);
		जाओ out_put;
	पूर्ण
	अगर (mnt_user_ns(path->mnt) != &init_user_ns) अणु
		pr_err("idmapped layers are currently not supported\n");
		जाओ out_put;
	पूर्ण
	अगर (!d_is_dir(path->dentry)) अणु
		pr_err("'%s' not a directory\n", name);
		जाओ out_put;
	पूर्ण
	वापस 0;

out_put:
	path_put_init(path);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ovl_mount_dir(स्थिर अक्षर *name, काष्ठा path *path)
अणु
	पूर्णांक err = -ENOMEM;
	अक्षर *पंचांगp = kstrdup(name, GFP_KERNEL);

	अगर (पंचांगp) अणु
		ovl_unescape(पंचांगp);
		err = ovl_mount_dir_noesc(पंचांगp, path);

		अगर (!err && path->dentry->d_flags & DCACHE_OP_REAL) अणु
			pr_err("filesystem on '%s' not supported as upperdir\n",
			       पंचांगp);
			path_put_init(path);
			err = -EINVAL;
		पूर्ण
		kमुक्त(पंचांगp);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक ovl_check_namelen(काष्ठा path *path, काष्ठा ovl_fs *ofs,
			     स्थिर अक्षर *name)
अणु
	काष्ठा kstatfs statfs;
	पूर्णांक err = vfs_statfs(path, &statfs);

	अगर (err)
		pr_err("statfs failed on '%s'\n", name);
	अन्यथा
		ofs->namelen = max(ofs->namelen, statfs.f_namelen);

	वापस err;
पूर्ण

अटल पूर्णांक ovl_lower_dir(स्थिर अक्षर *name, काष्ठा path *path,
			 काष्ठा ovl_fs *ofs, पूर्णांक *stack_depth)
अणु
	पूर्णांक fh_type;
	पूर्णांक err;

	err = ovl_mount_dir_noesc(name, path);
	अगर (err)
		वापस err;

	err = ovl_check_namelen(path, ofs, name);
	अगर (err)
		वापस err;

	*stack_depth = max(*stack_depth, path->mnt->mnt_sb->s_stack_depth);

	/*
	 * The inodes index feature and NFS export need to encode and decode
	 * file handles, so they require that all layers support them.
	 */
	fh_type = ovl_can_decode_fh(path->dentry->d_sb);
	अगर ((ofs->config.nfs_export ||
	     (ofs->config.index && ofs->config.upperdir)) && !fh_type) अणु
		ofs->config.index = false;
		ofs->config.nfs_export = false;
		pr_warn("fs on '%s' does not support file handles, falling back to index=off,nfs_export=off.\n",
			name);
	पूर्ण
	/*
	 * Decoding origin file handle is required क्रम persistent st_ino.
	 * Without persistent st_ino, xino=स्वतः falls back to xino=off.
	 */
	अगर (ofs->config.xino == OVL_XINO_AUTO &&
	    ofs->config.upperdir && !fh_type) अणु
		ofs->config.xino = OVL_XINO_OFF;
		pr_warn("fs on '%s' does not support file handles, falling back to xino=off.\n",
			name);
	पूर्ण

	/* Check अगर lower fs has 32bit inode numbers */
	अगर (fh_type != खाताID_INO32_GEN)
		ofs->xino_mode = -1;

	वापस 0;
पूर्ण

/* Workdir should not be subdir of upperdir and vice versa */
अटल bool ovl_workdir_ok(काष्ठा dentry *workdir, काष्ठा dentry *upperdir)
अणु
	bool ok = false;

	अगर (workdir != upperdir) अणु
		ok = (lock_नाम(workdir, upperdir) == शून्य);
		unlock_नाम(workdir, upperdir);
	पूर्ण
	वापस ok;
पूर्ण

अटल अचिन्हित पूर्णांक ovl_split_lowerdirs(अक्षर *str)
अणु
	अचिन्हित पूर्णांक ctr = 1;
	अक्षर *s, *d;

	क्रम (s = d = str;; s++, d++) अणु
		अगर (*s == '\\') अणु
			s++;
		पूर्ण अन्यथा अगर (*s == ':') अणु
			*d = '\0';
			ctr++;
			जारी;
		पूर्ण
		*d = *s;
		अगर (!*s)
			अवरोध;
	पूर्ण
	वापस ctr;
पूर्ण

अटल पूर्णांक __maybe_unused
ovl_posix_acl_xattr_get(स्थिर काष्ठा xattr_handler *handler,
			काष्ठा dentry *dentry, काष्ठा inode *inode,
			स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	वापस ovl_xattr_get(dentry, inode, handler->name, buffer, size);
पूर्ण

अटल पूर्णांक __maybe_unused
ovl_posix_acl_xattr_set(स्थिर काष्ठा xattr_handler *handler,
			काष्ठा user_namespace *mnt_userns,
			काष्ठा dentry *dentry, काष्ठा inode *inode,
			स्थिर अक्षर *name, स्थिर व्योम *value,
			माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा dentry *workdir = ovl_workdir(dentry);
	काष्ठा inode *realinode = ovl_inode_real(inode);
	काष्ठा posix_acl *acl = शून्य;
	पूर्णांक err;

	/* Check that everything is OK beक्रमe copy-up */
	अगर (value) अणु
		acl = posix_acl_from_xattr(&init_user_ns, value, size);
		अगर (IS_ERR(acl))
			वापस PTR_ERR(acl);
	पूर्ण
	err = -EOPNOTSUPP;
	अगर (!IS_POSIXACL(d_inode(workdir)))
		जाओ out_acl_release;
	अगर (!realinode->i_op->set_acl)
		जाओ out_acl_release;
	अगर (handler->flags == ACL_TYPE_DEFAULT && !S_ISसूची(inode->i_mode)) अणु
		err = acl ? -EACCES : 0;
		जाओ out_acl_release;
	पूर्ण
	err = -EPERM;
	अगर (!inode_owner_or_capable(&init_user_ns, inode))
		जाओ out_acl_release;

	posix_acl_release(acl);

	/*
	 * Check अगर sgid bit needs to be cleared (actual setacl operation will
	 * be करोne with mounter's capabilities and so that won't करो it क्रम us).
	 */
	अगर (unlikely(inode->i_mode & S_ISGID) &&
	    handler->flags == ACL_TYPE_ACCESS &&
	    !in_group_p(inode->i_gid) &&
	    !capable_wrt_inode_uidgid(&init_user_ns, inode, CAP_FSETID)) अणु
		काष्ठा iattr iattr = अणु .ia_valid = ATTR_KILL_SGID पूर्ण;

		err = ovl_setattr(&init_user_ns, dentry, &iattr);
		अगर (err)
			वापस err;
	पूर्ण

	err = ovl_xattr_set(dentry, inode, handler->name, value, size, flags);
	वापस err;

out_acl_release:
	posix_acl_release(acl);
	वापस err;
पूर्ण

अटल पूर्णांक ovl_own_xattr_get(स्थिर काष्ठा xattr_handler *handler,
			     काष्ठा dentry *dentry, काष्ठा inode *inode,
			     स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ovl_own_xattr_set(स्थिर काष्ठा xattr_handler *handler,
			     काष्ठा user_namespace *mnt_userns,
			     काष्ठा dentry *dentry, काष्ठा inode *inode,
			     स्थिर अक्षर *name, स्थिर व्योम *value,
			     माप_प्रकार size, पूर्णांक flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ovl_other_xattr_get(स्थिर काष्ठा xattr_handler *handler,
			       काष्ठा dentry *dentry, काष्ठा inode *inode,
			       स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	वापस ovl_xattr_get(dentry, inode, name, buffer, size);
पूर्ण

अटल पूर्णांक ovl_other_xattr_set(स्थिर काष्ठा xattr_handler *handler,
			       काष्ठा user_namespace *mnt_userns,
			       काष्ठा dentry *dentry, काष्ठा inode *inode,
			       स्थिर अक्षर *name, स्थिर व्योम *value,
			       माप_प्रकार size, पूर्णांक flags)
अणु
	वापस ovl_xattr_set(dentry, inode, name, value, size, flags);
पूर्ण

अटल स्थिर काष्ठा xattr_handler __maybe_unused
ovl_posix_acl_access_xattr_handler = अणु
	.name = XATTR_NAME_POSIX_ACL_ACCESS,
	.flags = ACL_TYPE_ACCESS,
	.get = ovl_posix_acl_xattr_get,
	.set = ovl_posix_acl_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler __maybe_unused
ovl_posix_acl_शेष_xattr_handler = अणु
	.name = XATTR_NAME_POSIX_ACL_DEFAULT,
	.flags = ACL_TYPE_DEFAULT,
	.get = ovl_posix_acl_xattr_get,
	.set = ovl_posix_acl_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler ovl_own_trusted_xattr_handler = अणु
	.prefix	= OVL_XATTR_TRUSTED_PREFIX,
	.get = ovl_own_xattr_get,
	.set = ovl_own_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler ovl_own_user_xattr_handler = अणु
	.prefix	= OVL_XATTR_USER_PREFIX,
	.get = ovl_own_xattr_get,
	.set = ovl_own_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler ovl_other_xattr_handler = अणु
	.prefix	= "", /* catch all */
	.get = ovl_other_xattr_get,
	.set = ovl_other_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler *ovl_trusted_xattr_handlers[] = अणु
#अगर_घोषित CONFIG_FS_POSIX_ACL
	&ovl_posix_acl_access_xattr_handler,
	&ovl_posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	&ovl_own_trusted_xattr_handler,
	&ovl_other_xattr_handler,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा xattr_handler *ovl_user_xattr_handlers[] = अणु
#अगर_घोषित CONFIG_FS_POSIX_ACL
	&ovl_posix_acl_access_xattr_handler,
	&ovl_posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	&ovl_own_user_xattr_handler,
	&ovl_other_xattr_handler,
	शून्य
पूर्ण;

अटल पूर्णांक ovl_setup_trap(काष्ठा super_block *sb, काष्ठा dentry *dir,
			  काष्ठा inode **ptrap, स्थिर अक्षर *name)
अणु
	काष्ठा inode *trap;
	पूर्णांक err;

	trap = ovl_get_trap_inode(sb, dir);
	err = PTR_ERR_OR_ZERO(trap);
	अगर (err) अणु
		अगर (err == -ELOOP)
			pr_err("conflicting %s path\n", name);
		वापस err;
	पूर्ण

	*ptrap = trap;
	वापस 0;
पूर्ण

/*
 * Determine how we treat concurrent use of upperdir/workdir based on the
 * index feature. This is papering over mount leaks of container runबार,
 * क्रम example, an old overlay mount is leaked and now its upperdir is
 * attempted to be used as a lower layer in a new overlay mount.
 */
अटल पूर्णांक ovl_report_in_use(काष्ठा ovl_fs *ofs, स्थिर अक्षर *name)
अणु
	अगर (ofs->config.index) अणु
		pr_err("%s is in-use as upperdir/workdir of another mount, mount with '-o index=off' to override exclusive upperdir protection.\n",
		       name);
		वापस -EBUSY;
	पूर्ण अन्यथा अणु
		pr_warn("%s is in-use as upperdir/workdir of another mount, accessing files from both mounts will result in undefined behavior.\n",
			name);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ovl_get_upper(काष्ठा super_block *sb, काष्ठा ovl_fs *ofs,
			 काष्ठा ovl_layer *upper_layer, काष्ठा path *upperpath)
अणु
	काष्ठा vfsmount *upper_mnt;
	पूर्णांक err;

	err = ovl_mount_dir(ofs->config.upperdir, upperpath);
	अगर (err)
		जाओ out;

	/* Upperdir path should not be r/o */
	अगर (__mnt_is_पढ़ोonly(upperpath->mnt)) अणु
		pr_err("upper fs is r/o, try multi-lower layers mount\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = ovl_check_namelen(upperpath, ofs, ofs->config.upperdir);
	अगर (err)
		जाओ out;

	err = ovl_setup_trap(sb, upperpath->dentry, &upper_layer->trap,
			     "upperdir");
	अगर (err)
		जाओ out;

	upper_mnt = clone_निजी_mount(upperpath);
	err = PTR_ERR(upper_mnt);
	अगर (IS_ERR(upper_mnt)) अणु
		pr_err("failed to clone upperpath\n");
		जाओ out;
	पूर्ण

	/* Don't inherit aसमय flags */
	upper_mnt->mnt_flags &= ~(MNT_NOATIME | MNT_NOसूचीATIME | MNT_RELATIME);
	upper_layer->mnt = upper_mnt;
	upper_layer->idx = 0;
	upper_layer->fsid = 0;

	/*
	 * Inherit SB_NOSEC flag from upperdir.
	 *
	 * This optimization changes behavior when a security related attribute
	 * (suid/sgid/security.*) is changed on an underlying layer.  This is
	 * okay because we करोn't yet have guarantees in that हाल, but it will
	 * need careful treaपंचांगent once we want to honour changes to underlying
	 * fileप्रणालीs.
	 */
	अगर (upper_mnt->mnt_sb->s_flags & SB_NOSEC)
		sb->s_flags |= SB_NOSEC;

	अगर (ovl_inuse_trylock(ovl_upper_mnt(ofs)->mnt_root)) अणु
		ofs->upperdir_locked = true;
	पूर्ण अन्यथा अणु
		err = ovl_report_in_use(ofs, "upperdir");
		अगर (err)
			जाओ out;
	पूर्ण

	err = 0;
out:
	वापस err;
पूर्ण

/*
 * Returns 1 अगर RENAME_WHITEOUT is supported, 0 अगर not supported and
 * negative values अगर error is encountered.
 */
अटल पूर्णांक ovl_check_नाम_whiteout(काष्ठा dentry *workdir)
अणु
	काष्ठा inode *dir = d_inode(workdir);
	काष्ठा dentry *temp;
	काष्ठा dentry *dest;
	काष्ठा dentry *whiteout;
	काष्ठा name_snapshot name;
	पूर्णांक err;

	inode_lock_nested(dir, I_MUTEX_PARENT);

	temp = ovl_create_temp(workdir, OVL_CATTR(S_IFREG | 0));
	err = PTR_ERR(temp);
	अगर (IS_ERR(temp))
		जाओ out_unlock;

	dest = ovl_lookup_temp(workdir);
	err = PTR_ERR(dest);
	अगर (IS_ERR(dest)) अणु
		dput(temp);
		जाओ out_unlock;
	पूर्ण

	/* Name is अंतरभूत and stable - using snapshot as a copy helper */
	take_dentry_name_snapshot(&name, temp);
	err = ovl_करो_नाम(dir, temp, dir, dest, RENAME_WHITEOUT);
	अगर (err) अणु
		अगर (err == -EINVAL)
			err = 0;
		जाओ cleanup_temp;
	पूर्ण

	whiteout = lookup_one_len(name.name.name, workdir, name.name.len);
	err = PTR_ERR(whiteout);
	अगर (IS_ERR(whiteout))
		जाओ cleanup_temp;

	err = ovl_is_whiteout(whiteout);

	/* Best efक्रमt cleanup of whiteout and temp file */
	अगर (err)
		ovl_cleanup(dir, whiteout);
	dput(whiteout);

cleanup_temp:
	ovl_cleanup(dir, temp);
	release_dentry_name_snapshot(&name);
	dput(temp);
	dput(dest);

out_unlock:
	inode_unlock(dir);

	वापस err;
पूर्ण

अटल काष्ठा dentry *ovl_lookup_or_create(काष्ठा dentry *parent,
					   स्थिर अक्षर *name, umode_t mode)
अणु
	माप_प्रकार len = म_माप(name);
	काष्ठा dentry *child;

	inode_lock_nested(parent->d_inode, I_MUTEX_PARENT);
	child = lookup_one_len(name, parent, len);
	अगर (!IS_ERR(child) && !child->d_inode)
		child = ovl_create_real(parent->d_inode, child,
					OVL_CATTR(mode));
	inode_unlock(parent->d_inode);
	dput(parent);

	वापस child;
पूर्ण

/*
 * Creates $workdir/work/incompat/अस्थिर/dirty file अगर it is not alपढ़ोy
 * present.
 */
अटल पूर्णांक ovl_create_अस्थिर_dirty(काष्ठा ovl_fs *ofs)
अणु
	अचिन्हित पूर्णांक ctr;
	काष्ठा dentry *d = dget(ofs->workbasedir);
	अटल स्थिर अक्षर *स्थिर अस्थिर_path[] = अणु
		OVL_WORKसूची_NAME, "incompat", "volatile", "dirty"
	पूर्ण;
	स्थिर अक्षर *स्थिर *name = अस्थिर_path;

	क्रम (ctr = ARRAY_SIZE(अस्थिर_path); ctr; ctr--, name++) अणु
		d = ovl_lookup_or_create(d, *name, ctr > 1 ? S_IFसूची : S_IFREG);
		अगर (IS_ERR(d))
			वापस PTR_ERR(d);
	पूर्ण
	dput(d);
	वापस 0;
पूर्ण

अटल पूर्णांक ovl_make_workdir(काष्ठा super_block *sb, काष्ठा ovl_fs *ofs,
			    काष्ठा path *workpath)
अणु
	काष्ठा vfsmount *mnt = ovl_upper_mnt(ofs);
	काष्ठा dentry *temp, *workdir;
	bool नाम_whiteout;
	bool d_type;
	पूर्णांक fh_type;
	पूर्णांक err;

	err = mnt_want_ग_लिखो(mnt);
	अगर (err)
		वापस err;

	workdir = ovl_workdir_create(ofs, OVL_WORKसूची_NAME, false);
	err = PTR_ERR(workdir);
	अगर (IS_ERR_OR_शून्य(workdir))
		जाओ out;

	ofs->workdir = workdir;

	err = ovl_setup_trap(sb, ofs->workdir, &ofs->workdir_trap, "workdir");
	अगर (err)
		जाओ out;

	/*
	 * Upper should support d_type, अन्यथा whiteouts are visible.  Given
	 * workdir and upper are on same fs, we can करो iterate_dir() on
	 * workdir. This check requires successful creation of workdir in
	 * previous step.
	 */
	err = ovl_check_d_type_supported(workpath);
	अगर (err < 0)
		जाओ out;

	d_type = err;
	अगर (!d_type)
		pr_warn("upper fs needs to support d_type.\n");

	/* Check अगर upper/work fs supports O_TMPखाता */
	temp = ovl_करो_क्षणिक_ख(ofs->workdir, S_IFREG | 0);
	ofs->क्षणिक_ख = !IS_ERR(temp);
	अगर (ofs->क्षणिक_ख)
		dput(temp);
	अन्यथा
		pr_warn("upper fs does not support tmpfile.\n");


	/* Check अगर upper/work fs supports RENAME_WHITEOUT */
	err = ovl_check_नाम_whiteout(ofs->workdir);
	अगर (err < 0)
		जाओ out;

	नाम_whiteout = err;
	अगर (!नाम_whiteout)
		pr_warn("upper fs does not support RENAME_WHITEOUT.\n");

	/*
	 * Check अगर upper/work fs supports (trusted|user).overlay.* xattr
	 */
	err = ovl_करो_setxattr(ofs, ofs->workdir, OVL_XATTR_OPAQUE, "0", 1);
	अगर (err) अणु
		ofs->noxattr = true;
		अगर (ofs->config.index || ofs->config.metacopy) अणु
			ofs->config.index = false;
			ofs->config.metacopy = false;
			pr_warn("upper fs does not support xattr, falling back to index=off,metacopy=off.\n");
		पूर्ण
		/*
		 * xattr support is required क्रम persistent st_ino.
		 * Without persistent st_ino, xino=स्वतः falls back to xino=off.
		 */
		अगर (ofs->config.xino == OVL_XINO_AUTO) अणु
			ofs->config.xino = OVL_XINO_OFF;
			pr_warn("upper fs does not support xattr, falling back to xino=off.\n");
		पूर्ण
		err = 0;
	पूर्ण अन्यथा अणु
		ovl_करो_हटाओxattr(ofs, ofs->workdir, OVL_XATTR_OPAQUE);
	पूर्ण

	/*
	 * We allowed sub-optimal upper fs configuration and करोn't want to अवरोध
	 * users over kernel upgrade, but we never allowed remote upper fs, so
	 * we can enक्रमce strict requirements क्रम remote upper fs.
	 */
	अगर (ovl_dentry_remote(ofs->workdir) &&
	    (!d_type || !नाम_whiteout || ofs->noxattr)) अणु
		pr_err("upper fs missing required features.\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * For अस्थिर mount, create a incompat/अस्थिर/dirty file to keep
	 * track of it.
	 */
	अगर (ofs->config.ovl_अस्थिर) अणु
		err = ovl_create_अस्थिर_dirty(ofs);
		अगर (err < 0) अणु
			pr_err("Failed to create volatile/dirty file.\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* Check अगर upper/work fs supports file handles */
	fh_type = ovl_can_decode_fh(ofs->workdir->d_sb);
	अगर (ofs->config.index && !fh_type) अणु
		ofs->config.index = false;
		pr_warn("upper fs does not support file handles, falling back to index=off.\n");
	पूर्ण

	/* Check अगर upper fs has 32bit inode numbers */
	अगर (fh_type != खाताID_INO32_GEN)
		ofs->xino_mode = -1;

	/* NFS export of r/w mount depends on index */
	अगर (ofs->config.nfs_export && !ofs->config.index) अणु
		pr_warn("NFS export requires \"index=on\", falling back to nfs_export=off.\n");
		ofs->config.nfs_export = false;
	पूर्ण
out:
	mnt_drop_ग_लिखो(mnt);
	वापस err;
पूर्ण

अटल पूर्णांक ovl_get_workdir(काष्ठा super_block *sb, काष्ठा ovl_fs *ofs,
			   काष्ठा path *upperpath)
अणु
	पूर्णांक err;
	काष्ठा path workpath = अणु पूर्ण;

	err = ovl_mount_dir(ofs->config.workdir, &workpath);
	अगर (err)
		जाओ out;

	err = -EINVAL;
	अगर (upperpath->mnt != workpath.mnt) अणु
		pr_err("workdir and upperdir must reside under the same mount\n");
		जाओ out;
	पूर्ण
	अगर (!ovl_workdir_ok(workpath.dentry, upperpath->dentry)) अणु
		pr_err("workdir and upperdir must be separate subtrees\n");
		जाओ out;
	पूर्ण

	ofs->workbasedir = dget(workpath.dentry);

	अगर (ovl_inuse_trylock(ofs->workbasedir)) अणु
		ofs->workdir_locked = true;
	पूर्ण अन्यथा अणु
		err = ovl_report_in_use(ofs, "workdir");
		अगर (err)
			जाओ out;
	पूर्ण

	err = ovl_setup_trap(sb, ofs->workbasedir, &ofs->workbasedir_trap,
			     "workdir");
	अगर (err)
		जाओ out;

	err = ovl_make_workdir(sb, ofs, &workpath);

out:
	path_put(&workpath);

	वापस err;
पूर्ण

अटल पूर्णांक ovl_get_indexdir(काष्ठा super_block *sb, काष्ठा ovl_fs *ofs,
			    काष्ठा ovl_entry *oe, काष्ठा path *upperpath)
अणु
	काष्ठा vfsmount *mnt = ovl_upper_mnt(ofs);
	काष्ठा dentry *indexdir;
	पूर्णांक err;

	err = mnt_want_ग_लिखो(mnt);
	अगर (err)
		वापस err;

	/* Verअगरy lower root is upper root origin */
	err = ovl_verअगरy_origin(ofs, upperpath->dentry,
				oe->lowerstack[0].dentry, true);
	अगर (err) अणु
		pr_err("failed to verify upper root origin\n");
		जाओ out;
	पूर्ण

	/* index dir will act also as workdir */
	iput(ofs->workdir_trap);
	ofs->workdir_trap = शून्य;
	dput(ofs->workdir);
	ofs->workdir = शून्य;
	indexdir = ovl_workdir_create(ofs, OVL_INDEXसूची_NAME, true);
	अगर (IS_ERR(indexdir)) अणु
		err = PTR_ERR(indexdir);
	पूर्ण अन्यथा अगर (indexdir) अणु
		ofs->indexdir = indexdir;
		ofs->workdir = dget(indexdir);

		err = ovl_setup_trap(sb, ofs->indexdir, &ofs->indexdir_trap,
				     "indexdir");
		अगर (err)
			जाओ out;

		/*
		 * Verअगरy upper root is exclusively associated with index dir.
		 * Older kernels stored upper fh in ".overlay.origin"
		 * xattr. If that xattr exists, verअगरy that it is a match to
		 * upper dir file handle. In any हाल, verअगरy or set xattr
		 * ".overlay.upper" to indicate that index may have
		 * directory entries.
		 */
		अगर (ovl_check_origin_xattr(ofs, ofs->indexdir)) अणु
			err = ovl_verअगरy_set_fh(ofs, ofs->indexdir,
						OVL_XATTR_ORIGIN,
						upperpath->dentry, true, false);
			अगर (err)
				pr_err("failed to verify index dir 'origin' xattr\n");
		पूर्ण
		err = ovl_verअगरy_upper(ofs, ofs->indexdir, upperpath->dentry,
				       true);
		अगर (err)
			pr_err("failed to verify index dir 'upper' xattr\n");

		/* Cleanup bad/stale/orphan index entries */
		अगर (!err)
			err = ovl_indexdir_cleanup(ofs);
	पूर्ण
	अगर (err || !ofs->indexdir)
		pr_warn("try deleting index dir or mounting with '-o index=off' to disable inodes index.\n");

out:
	mnt_drop_ग_लिखो(mnt);
	वापस err;
पूर्ण

अटल bool ovl_lower_uuid_ok(काष्ठा ovl_fs *ofs, स्थिर uuid_t *uuid)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!ofs->config.nfs_export && !ovl_upper_mnt(ofs))
		वापस true;

	/*
	 * We allow using single lower with null uuid क्रम index and nfs_export
	 * क्रम example to support those features with single lower squashfs.
	 * To aव्योम regressions in setups of overlay with re-क्रमmatted lower
	 * squashfs, करो not allow decoding origin with lower null uuid unless
	 * user opted-in to one of the new features that require following the
	 * lower inode of non-dir upper.
	 */
	अगर (!ofs->config.index && !ofs->config.metacopy &&
	    ofs->config.xino != OVL_XINO_ON &&
	    uuid_is_null(uuid))
		वापस false;

	क्रम (i = 0; i < ofs->numfs; i++) अणु
		/*
		 * We use uuid to associate an overlay lower file handle with a
		 * lower layer, so we can accept lower fs with null uuid as दीर्घ
		 * as all lower layers with null uuid are on the same fs.
		 * अगर we detect multiple lower fs with the same uuid, we
		 * disable lower file handle decoding on all of them.
		 */
		अगर (ofs->fs[i].is_lower &&
		    uuid_equal(&ofs->fs[i].sb->s_uuid, uuid)) अणु
			ofs->fs[i].bad_uuid = true;
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

/* Get a unique fsid क्रम the layer */
अटल पूर्णांक ovl_get_fsid(काष्ठा ovl_fs *ofs, स्थिर काष्ठा path *path)
अणु
	काष्ठा super_block *sb = path->mnt->mnt_sb;
	अचिन्हित पूर्णांक i;
	dev_t dev;
	पूर्णांक err;
	bool bad_uuid = false;
	bool warn = false;

	क्रम (i = 0; i < ofs->numfs; i++) अणु
		अगर (ofs->fs[i].sb == sb)
			वापस i;
	पूर्ण

	अगर (!ovl_lower_uuid_ok(ofs, &sb->s_uuid)) अणु
		bad_uuid = true;
		अगर (ofs->config.xino == OVL_XINO_AUTO) अणु
			ofs->config.xino = OVL_XINO_OFF;
			warn = true;
		पूर्ण
		अगर (ofs->config.index || ofs->config.nfs_export) अणु
			ofs->config.index = false;
			ofs->config.nfs_export = false;
			warn = true;
		पूर्ण
		अगर (warn) अणु
			pr_warn("%s uuid detected in lower fs '%pd2', falling back to xino=%s,index=off,nfs_export=off.\n",
				uuid_is_null(&sb->s_uuid) ? "null" :
							    "conflicting",
				path->dentry, ovl_xino_str[ofs->config.xino]);
		पूर्ण
	पूर्ण

	err = get_anon_bdev(&dev);
	अगर (err) अणु
		pr_err("failed to get anonymous bdev for lowerpath\n");
		वापस err;
	पूर्ण

	ofs->fs[ofs->numfs].sb = sb;
	ofs->fs[ofs->numfs].pseuकरो_dev = dev;
	ofs->fs[ofs->numfs].bad_uuid = bad_uuid;

	वापस ofs->numfs++;
पूर्ण

अटल पूर्णांक ovl_get_layers(काष्ठा super_block *sb, काष्ठा ovl_fs *ofs,
			  काष्ठा path *stack, अचिन्हित पूर्णांक numlower,
			  काष्ठा ovl_layer *layers)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i;

	err = -ENOMEM;
	ofs->fs = kसुस्मृति(numlower + 1, माप(काष्ठा ovl_sb), GFP_KERNEL);
	अगर (ofs->fs == शून्य)
		जाओ out;

	/* idx/fsid 0 are reserved क्रम upper fs even with lower only overlay */
	ofs->numfs++;

	/*
	 * All lower layers that share the same fs as upper layer, use the same
	 * pseuकरो_dev as upper layer.  Allocate fs[0].pseuकरो_dev even क्रम lower
	 * only overlay to simplअगरy ovl_fs_मुक्त().
	 * is_lower will be set अगर upper fs is shared with a lower layer.
	 */
	err = get_anon_bdev(&ofs->fs[0].pseuकरो_dev);
	अगर (err) अणु
		pr_err("failed to get anonymous bdev for upper fs\n");
		जाओ out;
	पूर्ण

	अगर (ovl_upper_mnt(ofs)) अणु
		ofs->fs[0].sb = ovl_upper_mnt(ofs)->mnt_sb;
		ofs->fs[0].is_lower = false;
	पूर्ण

	क्रम (i = 0; i < numlower; i++) अणु
		काष्ठा vfsmount *mnt;
		काष्ठा inode *trap;
		पूर्णांक fsid;

		err = fsid = ovl_get_fsid(ofs, &stack[i]);
		अगर (err < 0)
			जाओ out;

		/*
		 * Check अगर lower root conflicts with this overlay layers beक्रमe
		 * checking अगर it is in-use as upperdir/workdir of "another"
		 * mount, because we करो not bother to check in ovl_is_inuse() अगर
		 * the upperdir/workdir is in fact in-use by our
		 * upperdir/workdir.
		 */
		err = ovl_setup_trap(sb, stack[i].dentry, &trap, "lowerdir");
		अगर (err)
			जाओ out;

		अगर (ovl_is_inuse(stack[i].dentry)) अणु
			err = ovl_report_in_use(ofs, "lowerdir");
			अगर (err) अणु
				iput(trap);
				जाओ out;
			पूर्ण
		पूर्ण

		mnt = clone_निजी_mount(&stack[i]);
		err = PTR_ERR(mnt);
		अगर (IS_ERR(mnt)) अणु
			pr_err("failed to clone lowerpath\n");
			iput(trap);
			जाओ out;
		पूर्ण

		/*
		 * Make lower layers R/O.  That way fchmod/fchown on lower file
		 * will fail instead of modअगरying lower fs.
		 */
		mnt->mnt_flags |= MNT_READONLY | MNT_NOATIME;

		layers[ofs->numlayer].trap = trap;
		layers[ofs->numlayer].mnt = mnt;
		layers[ofs->numlayer].idx = ofs->numlayer;
		layers[ofs->numlayer].fsid = fsid;
		layers[ofs->numlayer].fs = &ofs->fs[fsid];
		ofs->numlayer++;
		ofs->fs[fsid].is_lower = true;
	पूर्ण

	/*
	 * When all layers on same fs, overlay can use real inode numbers.
	 * With mount option "xino=<on|auto>", mounter declares that there are
	 * enough मुक्त high bits in underlying fs to hold the unique fsid.
	 * If overlayfs करोes encounter underlying inodes using the high xino
	 * bits reserved क्रम fsid, it emits a warning and uses the original
	 * inode number or a non persistent inode number allocated from a
	 * dedicated range.
	 */
	अगर (ofs->numfs - !ovl_upper_mnt(ofs) == 1) अणु
		अगर (ofs->config.xino == OVL_XINO_ON)
			pr_info("\"xino=on\" is useless with all layers on same fs, ignore.\n");
		ofs->xino_mode = 0;
	पूर्ण अन्यथा अगर (ofs->config.xino == OVL_XINO_OFF) अणु
		ofs->xino_mode = -1;
	पूर्ण अन्यथा अगर (ofs->xino_mode < 0) अणु
		/*
		 * This is a roundup of number of bits needed क्रम encoding
		 * fsid, where fsid 0 is reserved क्रम upper fs (even with
		 * lower only overlay) +1 extra bit is reserved क्रम the non
		 * persistent inode number range that is used क्रम resolving
		 * xino lower bits overflow.
		 */
		BUILD_BUG_ON(ilog2(OVL_MAX_STACK) > 30);
		ofs->xino_mode = ilog2(ofs->numfs - 1) + 2;
	पूर्ण

	अगर (ofs->xino_mode > 0) अणु
		pr_info("\"xino\" feature enabled using %d upper inode bits.\n",
			ofs->xino_mode);
	पूर्ण

	err = 0;
out:
	वापस err;
पूर्ण

अटल काष्ठा ovl_entry *ovl_get_lowerstack(काष्ठा super_block *sb,
				स्थिर अक्षर *lower, अचिन्हित पूर्णांक numlower,
				काष्ठा ovl_fs *ofs, काष्ठा ovl_layer *layers)
अणु
	पूर्णांक err;
	काष्ठा path *stack = शून्य;
	अचिन्हित पूर्णांक i;
	काष्ठा ovl_entry *oe;

	अगर (!ofs->config.upperdir && numlower == 1) अणु
		pr_err("at least 2 lowerdir are needed while upperdir nonexistent\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	stack = kसुस्मृति(numlower, माप(काष्ठा path), GFP_KERNEL);
	अगर (!stack)
		वापस ERR_PTR(-ENOMEM);

	err = -EINVAL;
	क्रम (i = 0; i < numlower; i++) अणु
		err = ovl_lower_dir(lower, &stack[i], ofs, &sb->s_stack_depth);
		अगर (err)
			जाओ out_err;

		lower = म_अक्षर(lower, '\0') + 1;
	पूर्ण

	err = -EINVAL;
	sb->s_stack_depth++;
	अगर (sb->s_stack_depth > खाताSYSTEM_MAX_STACK_DEPTH) अणु
		pr_err("maximum fs stacking depth exceeded\n");
		जाओ out_err;
	पूर्ण

	err = ovl_get_layers(sb, ofs, stack, numlower, layers);
	अगर (err)
		जाओ out_err;

	err = -ENOMEM;
	oe = ovl_alloc_entry(numlower);
	अगर (!oe)
		जाओ out_err;

	क्रम (i = 0; i < numlower; i++) अणु
		oe->lowerstack[i].dentry = dget(stack[i].dentry);
		oe->lowerstack[i].layer = &ofs->layers[i+1];
	पूर्ण

out:
	क्रम (i = 0; i < numlower; i++)
		path_put(&stack[i]);
	kमुक्त(stack);

	वापस oe;

out_err:
	oe = ERR_PTR(err);
	जाओ out;
पूर्ण

/*
 * Check अगर this layer root is a descendant of:
 * - another layer of this overlayfs instance
 * - upper/work dir of any overlayfs instance
 */
अटल पूर्णांक ovl_check_layer(काष्ठा super_block *sb, काष्ठा ovl_fs *ofs,
			   काष्ठा dentry *dentry, स्थिर अक्षर *name,
			   bool is_lower)
अणु
	काष्ठा dentry *next = dentry, *parent;
	पूर्णांक err = 0;

	अगर (!dentry)
		वापस 0;

	parent = dget_parent(next);

	/* Walk back ancestors to root (inclusive) looking क्रम traps */
	जबतक (!err && parent != next) अणु
		अगर (is_lower && ovl_lookup_trap_inode(sb, parent)) अणु
			err = -ELOOP;
			pr_err("overlapping %s path\n", name);
		पूर्ण अन्यथा अगर (ovl_is_inuse(parent)) अणु
			err = ovl_report_in_use(ofs, name);
		पूर्ण
		next = parent;
		parent = dget_parent(next);
		dput(next);
	पूर्ण

	dput(parent);

	वापस err;
पूर्ण

/*
 * Check अगर any of the layers or work dirs overlap.
 */
अटल पूर्णांक ovl_check_overlapping_layers(काष्ठा super_block *sb,
					काष्ठा ovl_fs *ofs)
अणु
	पूर्णांक i, err;

	अगर (ovl_upper_mnt(ofs)) अणु
		err = ovl_check_layer(sb, ofs, ovl_upper_mnt(ofs)->mnt_root,
				      "upperdir", false);
		अगर (err)
			वापस err;

		/*
		 * Checking workbasedir aव्योमs hitting ovl_is_inuse(parent) of
		 * this instance and covers overlapping work and index dirs,
		 * unless work or index dir have been moved since created inside
		 * workbasedir.  In that हाल, we alपढ़ोy have their traps in
		 * inode cache and we will catch that हाल on lookup.
		 */
		err = ovl_check_layer(sb, ofs, ofs->workbasedir, "workdir",
				      false);
		अगर (err)
			वापस err;
	पूर्ण

	क्रम (i = 1; i < ofs->numlayer; i++) अणु
		err = ovl_check_layer(sb, ofs,
				      ofs->layers[i].mnt->mnt_root,
				      "lowerdir", true);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dentry *ovl_get_root(काष्ठा super_block *sb,
				   काष्ठा dentry *upperdentry,
				   काष्ठा ovl_entry *oe)
अणु
	काष्ठा dentry *root;
	काष्ठा ovl_path *lowerpath = &oe->lowerstack[0];
	अचिन्हित दीर्घ ino = d_inode(lowerpath->dentry)->i_ino;
	पूर्णांक fsid = lowerpath->layer->fsid;
	काष्ठा ovl_inode_params oip = अणु
		.upperdentry = upperdentry,
		.lowerpath = lowerpath,
	पूर्ण;

	root = d_make_root(ovl_new_inode(sb, S_IFसूची, 0));
	अगर (!root)
		वापस शून्य;

	root->d_fsdata = oe;

	अगर (upperdentry) अणु
		/* Root inode uses upper st_ino/i_ino */
		ino = d_inode(upperdentry)->i_ino;
		fsid = 0;
		ovl_dentry_set_upper_alias(root);
		अगर (ovl_is_impuredir(sb, upperdentry))
			ovl_set_flag(OVL_IMPURE, d_inode(root));
	पूर्ण

	/* Root is always merge -> can have whiteouts */
	ovl_set_flag(OVL_WHITEOUTS, d_inode(root));
	ovl_dentry_set_flag(OVL_E_CONNECTED, root);
	ovl_set_upperdata(d_inode(root));
	ovl_inode_init(d_inode(root), &oip, ino, fsid);
	ovl_dentry_update_reval(root, upperdentry, DCACHE_OP_WEAK_REVALIDATE);

	वापस root;
पूर्ण

अटल पूर्णांक ovl_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा path upperpath = अणु पूर्ण;
	काष्ठा dentry *root_dentry;
	काष्ठा ovl_entry *oe;
	काष्ठा ovl_fs *ofs;
	काष्ठा ovl_layer *layers;
	काष्ठा cred *cred;
	अक्षर *splitlower = शून्य;
	अचिन्हित पूर्णांक numlower;
	पूर्णांक err;

	err = -EIO;
	अगर (WARN_ON(sb->s_user_ns != current_user_ns()))
		जाओ out;

	sb->s_d_op = &ovl_dentry_operations;

	err = -ENOMEM;
	ofs = kzalloc(माप(काष्ठा ovl_fs), GFP_KERNEL);
	अगर (!ofs)
		जाओ out;

	err = -ENOMEM;
	ofs->creator_cred = cred = prepare_creds();
	अगर (!cred)
		जाओ out_err;

	/* Is there a reason anyone would want not to share whiteouts? */
	ofs->share_whiteout = true;

	ofs->config.index = ovl_index_def;
	ofs->config.uuid = true;
	ofs->config.nfs_export = ovl_nfs_export_def;
	ofs->config.xino = ovl_xino_def();
	ofs->config.metacopy = ovl_metacopy_def;
	err = ovl_parse_opt((अक्षर *) data, &ofs->config);
	अगर (err)
		जाओ out_err;

	err = -EINVAL;
	अगर (!ofs->config.lowerdir) अणु
		अगर (!silent)
			pr_err("missing 'lowerdir'\n");
		जाओ out_err;
	पूर्ण

	err = -ENOMEM;
	splitlower = kstrdup(ofs->config.lowerdir, GFP_KERNEL);
	अगर (!splitlower)
		जाओ out_err;

	err = -EINVAL;
	numlower = ovl_split_lowerdirs(splitlower);
	अगर (numlower > OVL_MAX_STACK) अणु
		pr_err("too many lower directories, limit is %d\n",
		       OVL_MAX_STACK);
		जाओ out_err;
	पूर्ण

	err = -ENOMEM;
	layers = kसुस्मृति(numlower + 1, माप(काष्ठा ovl_layer), GFP_KERNEL);
	अगर (!layers)
		जाओ out_err;

	ofs->layers = layers;
	/* Layer 0 is reserved क्रम upper even अगर there's no upper */
	ofs->numlayer = 1;

	sb->s_stack_depth = 0;
	sb->s_maxbytes = MAX_LFS_खाताSIZE;
	atomic_दीर्घ_set(&ofs->last_ino, 1);
	/* Assume underlaying fs uses 32bit inodes unless proven otherwise */
	अगर (ofs->config.xino != OVL_XINO_OFF) अणु
		ofs->xino_mode = BITS_PER_LONG - 32;
		अगर (!ofs->xino_mode) अणु
			pr_warn("xino not supported on 32bit kernel, falling back to xino=off.\n");
			ofs->config.xino = OVL_XINO_OFF;
		पूर्ण
	पूर्ण

	/* alloc/destroy_inode needed क्रम setting up traps in inode cache */
	sb->s_op = &ovl_super_operations;

	अगर (ofs->config.upperdir) अणु
		काष्ठा super_block *upper_sb;

		err = -EINVAL;
		अगर (!ofs->config.workdir) अणु
			pr_err("missing 'workdir'\n");
			जाओ out_err;
		पूर्ण

		err = ovl_get_upper(sb, ofs, &layers[0], &upperpath);
		अगर (err)
			जाओ out_err;

		upper_sb = ovl_upper_mnt(ofs)->mnt_sb;
		अगर (!ovl_should_sync(ofs)) अणु
			ofs->errseq = errseq_sample(&upper_sb->s_wb_err);
			अगर (errseq_check(&upper_sb->s_wb_err, ofs->errseq)) अणु
				err = -EIO;
				pr_err("Cannot mount volatile when upperdir has an unseen error. Sync upperdir fs to clear state.\n");
				जाओ out_err;
			पूर्ण
		पूर्ण

		err = ovl_get_workdir(sb, ofs, &upperpath);
		अगर (err)
			जाओ out_err;

		अगर (!ofs->workdir)
			sb->s_flags |= SB_RDONLY;

		sb->s_stack_depth = upper_sb->s_stack_depth;
		sb->s_समय_gran = upper_sb->s_समय_gran;
	पूर्ण
	oe = ovl_get_lowerstack(sb, splitlower, numlower, ofs, layers);
	err = PTR_ERR(oe);
	अगर (IS_ERR(oe))
		जाओ out_err;

	/* If the upper fs is nonexistent, we mark overlayfs r/o too */
	अगर (!ovl_upper_mnt(ofs))
		sb->s_flags |= SB_RDONLY;

	अगर (!ofs->config.uuid && ofs->numfs > 1) अणु
		pr_warn("The uuid=off requires a single fs for lower and upper, falling back to uuid=on.\n");
		ofs->config.uuid = true;
	पूर्ण

	अगर (!ovl_क्रमce_पढ़ोonly(ofs) && ofs->config.index) अणु
		err = ovl_get_indexdir(sb, ofs, oe, &upperpath);
		अगर (err)
			जाओ out_मुक्त_oe;

		/* Force r/o mount with no index dir */
		अगर (!ofs->indexdir)
			sb->s_flags |= SB_RDONLY;
	पूर्ण

	err = ovl_check_overlapping_layers(sb, ofs);
	अगर (err)
		जाओ out_मुक्त_oe;

	/* Show index=off in /proc/mounts क्रम क्रमced r/o mount */
	अगर (!ofs->indexdir) अणु
		ofs->config.index = false;
		अगर (ovl_upper_mnt(ofs) && ofs->config.nfs_export) अणु
			pr_warn("NFS export requires an index dir, falling back to nfs_export=off.\n");
			ofs->config.nfs_export = false;
		पूर्ण
	पूर्ण

	अगर (ofs->config.metacopy && ofs->config.nfs_export) अणु
		pr_warn("NFS export is not supported with metadata only copy up, falling back to nfs_export=off.\n");
		ofs->config.nfs_export = false;
	पूर्ण

	अगर (ofs->config.nfs_export)
		sb->s_export_op = &ovl_export_operations;

	/* Never override disk quota limits or use reserved space */
	cap_lower(cred->cap_effective, CAP_SYS_RESOURCE);

	sb->s_magic = OVERLAYFS_SUPER_MAGIC;
	sb->s_xattr = ofs->config.userxattr ? ovl_user_xattr_handlers :
		ovl_trusted_xattr_handlers;
	sb->s_fs_info = ofs;
	sb->s_flags |= SB_POSIXACL;
	sb->s_अगरlags |= SB_I_SKIP_SYNC;

	err = -ENOMEM;
	root_dentry = ovl_get_root(sb, upperpath.dentry, oe);
	अगर (!root_dentry)
		जाओ out_मुक्त_oe;

	mntput(upperpath.mnt);
	kमुक्त(splitlower);

	sb->s_root = root_dentry;

	वापस 0;

out_मुक्त_oe:
	ovl_entry_stack_मुक्त(oe);
	kमुक्त(oe);
out_err:
	kमुक्त(splitlower);
	path_put(&upperpath);
	ovl_मुक्त_fs(ofs);
out:
	वापस err;
पूर्ण

अटल काष्ठा dentry *ovl_mount(काष्ठा file_प्रणाली_type *fs_type, पूर्णांक flags,
				स्थिर अक्षर *dev_name, व्योम *raw_data)
अणु
	वापस mount_nodev(fs_type, flags, raw_data, ovl_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type ovl_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "overlay",
	.fs_flags	= FS_USERNS_MOUNT,
	.mount		= ovl_mount,
	.समाप्त_sb	= समाप्त_anon_super,
पूर्ण;
MODULE_ALIAS_FS("overlay");

अटल व्योम ovl_inode_init_once(व्योम *foo)
अणु
	काष्ठा ovl_inode *oi = foo;

	inode_init_once(&oi->vfs_inode);
पूर्ण

अटल पूर्णांक __init ovl_init(व्योम)
अणु
	पूर्णांक err;

	ovl_inode_cachep = kmem_cache_create("ovl_inode",
					     माप(काष्ठा ovl_inode), 0,
					     (SLAB_RECLAIM_ACCOUNT|
					      SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					     ovl_inode_init_once);
	अगर (ovl_inode_cachep == शून्य)
		वापस -ENOMEM;

	err = ovl_aio_request_cache_init();
	अगर (!err) अणु
		err = रेजिस्टर_fileप्रणाली(&ovl_fs_type);
		अगर (!err)
			वापस 0;

		ovl_aio_request_cache_destroy();
	पूर्ण
	kmem_cache_destroy(ovl_inode_cachep);

	वापस err;
पूर्ण

अटल व्योम __निकास ovl_निकास(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&ovl_fs_type);

	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(ovl_inode_cachep);
	ovl_aio_request_cache_destroy();
पूर्ण

module_init(ovl_init);
module_निकास(ovl_निकास);
