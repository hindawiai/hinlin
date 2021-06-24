<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/ext2/super.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/inode.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/parser.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mount.h>
#समावेश <linux/log2.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/dax.h>
#समावेश <linux/iversion.h>
#समावेश "ext2.h"
#समावेश "xattr.h"
#समावेश "acl.h"

अटल व्योम ext2_ग_लिखो_super(काष्ठा super_block *sb);
अटल पूर्णांक ext2_remount (काष्ठा super_block * sb, पूर्णांक * flags, अक्षर * data);
अटल पूर्णांक ext2_statfs (काष्ठा dentry * dentry, काष्ठा kstatfs * buf);
अटल पूर्णांक ext2_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको);
अटल पूर्णांक ext2_मुक्तze(काष्ठा super_block *sb);
अटल पूर्णांक ext2_unमुक्तze(काष्ठा super_block *sb);

व्योम ext2_error(काष्ठा super_block *sb, स्थिर अक्षर *function,
		स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;
	काष्ठा ext2_sb_info *sbi = EXT2_SB(sb);
	काष्ठा ext2_super_block *es = sbi->s_es;

	अगर (!sb_rकरोnly(sb)) अणु
		spin_lock(&sbi->s_lock);
		sbi->s_mount_state |= EXT2_ERROR_FS;
		es->s_state |= cpu_to_le16(EXT2_ERROR_FS);
		spin_unlock(&sbi->s_lock);
		ext2_sync_super(sb, es, 1);
	पूर्ण

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk(KERN_CRIT "EXT2-fs (%s): error: %s: %pV\n",
	       sb->s_id, function, &vaf);

	बहु_पूर्ण(args);

	अगर (test_opt(sb, ERRORS_PANIC))
		panic("EXT2-fs: panic from previous error\n");
	अगर (!sb_rकरोnly(sb) && test_opt(sb, ERRORS_RO)) अणु
		ext2_msg(sb, KERN_CRIT,
			     "error: remounting filesystem read-only");
		sb->s_flags |= SB_RDONLY;
	पूर्ण
पूर्ण

व्योम ext2_msg(काष्ठा super_block *sb, स्थिर अक्षर *prefix,
		स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk("%sEXT2-fs (%s): %pV\n", prefix, sb->s_id, &vaf);

	बहु_पूर्ण(args);
पूर्ण

/*
 * This must be called with sbi->s_lock held.
 */
व्योम ext2_update_dynamic_rev(काष्ठा super_block *sb)
अणु
	काष्ठा ext2_super_block *es = EXT2_SB(sb)->s_es;

	अगर (le32_to_cpu(es->s_rev_level) > EXT2_GOOD_OLD_REV)
		वापस;

	ext2_msg(sb, KERN_WARNING,
		     "warning: updating to rev %d because of "
		     "new feature flag, running e2fsck is recommended",
		     EXT2_DYNAMIC_REV);

	es->s_first_ino = cpu_to_le32(EXT2_GOOD_OLD_FIRST_INO);
	es->s_inode_size = cpu_to_le16(EXT2_GOOD_OLD_INODE_SIZE);
	es->s_rev_level = cpu_to_le32(EXT2_DYNAMIC_REV);
	/* leave es->s_feature_*compat flags alone */
	/* es->s_uuid will be set by e2fsck अगर empty */

	/*
	 * The rest of the superblock fields should be zero, and अगर not it
	 * means they are likely alपढ़ोy in use, so leave them alone.  We
	 * can leave it up to e2fsck to clean up any inconsistencies there.
	 */
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल पूर्णांक ext2_quota_off(काष्ठा super_block *sb, पूर्णांक type);

अटल व्योम ext2_quota_off_umount(काष्ठा super_block *sb)
अणु
	पूर्णांक type;

	क्रम (type = 0; type < MAXQUOTAS; type++)
		ext2_quota_off(sb, type);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम ext2_quota_off_umount(काष्ठा super_block *sb)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम ext2_put_super (काष्ठा super_block * sb)
अणु
	पूर्णांक db_count;
	पूर्णांक i;
	काष्ठा ext2_sb_info *sbi = EXT2_SB(sb);

	ext2_quota_off_umount(sb);

	ext2_xattr_destroy_cache(sbi->s_ea_block_cache);
	sbi->s_ea_block_cache = शून्य;

	अगर (!sb_rकरोnly(sb)) अणु
		काष्ठा ext2_super_block *es = sbi->s_es;

		spin_lock(&sbi->s_lock);
		es->s_state = cpu_to_le16(sbi->s_mount_state);
		spin_unlock(&sbi->s_lock);
		ext2_sync_super(sb, es, 1);
	पूर्ण
	db_count = sbi->s_gdb_count;
	क्रम (i = 0; i < db_count; i++)
		brअन्यथा(sbi->s_group_desc[i]);
	kमुक्त(sbi->s_group_desc);
	kमुक्त(sbi->s_debts);
	percpu_counter_destroy(&sbi->s_मुक्तblocks_counter);
	percpu_counter_destroy(&sbi->s_मुक्तinodes_counter);
	percpu_counter_destroy(&sbi->s_dirs_counter);
	brअन्यथा (sbi->s_sbh);
	sb->s_fs_info = शून्य;
	kमुक्त(sbi->s_blockgroup_lock);
	fs_put_dax(sbi->s_daxdev);
	kमुक्त(sbi);
पूर्ण

अटल काष्ठा kmem_cache * ext2_inode_cachep;

अटल काष्ठा inode *ext2_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा ext2_inode_info *ei;
	ei = kmem_cache_alloc(ext2_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;
	ei->i_block_alloc_info = शून्य;
	inode_set_iversion(&ei->vfs_inode, 1);
#अगर_घोषित CONFIG_QUOTA
	स_रखो(&ei->i_dquot, 0, माप(ei->i_dquot));
#पूर्ण_अगर

	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम ext2_मुक्त_in_core_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(ext2_inode_cachep, EXT2_I(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा ext2_inode_info *ei = (काष्ठा ext2_inode_info *) foo;

	rwlock_init(&ei->i_meta_lock);
#अगर_घोषित CONFIG_EXT2_FS_XATTR
	init_rwsem(&ei->xattr_sem);
#पूर्ण_अगर
	mutex_init(&ei->truncate_mutex);
#अगर_घोषित CONFIG_FS_DAX
	init_rwsem(&ei->dax_sem);
#पूर्ण_अगर
	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_inodecache(व्योम)
अणु
	ext2_inode_cachep = kmem_cache_create_usercopy("ext2_inode_cache",
				माप(काष्ठा ext2_inode_info), 0,
				(SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD|
					SLAB_ACCOUNT),
				दुरत्व(काष्ठा ext2_inode_info, i_data),
				माप_field(काष्ठा ext2_inode_info, i_data),
				init_once);
	अगर (ext2_inode_cachep == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम destroy_inodecache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(ext2_inode_cachep);
पूर्ण

अटल पूर्णांक ext2_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा super_block *sb = root->d_sb;
	काष्ठा ext2_sb_info *sbi = EXT2_SB(sb);
	काष्ठा ext2_super_block *es = sbi->s_es;
	अचिन्हित दीर्घ def_mount_opts;

	spin_lock(&sbi->s_lock);
	def_mount_opts = le32_to_cpu(es->s_शेष_mount_opts);

	अगर (sbi->s_sb_block != 1)
		seq_म_लिखो(seq, ",sb=%lu", sbi->s_sb_block);
	अगर (test_opt(sb, MINIX_DF))
		seq_माला_दो(seq, ",minixdf");
	अगर (test_opt(sb, GRPID))
		seq_माला_दो(seq, ",grpid");
	अगर (!test_opt(sb, GRPID) && (def_mount_opts & EXT2_DEFM_BSDGROUPS))
		seq_माला_दो(seq, ",nogrpid");
	अगर (!uid_eq(sbi->s_resuid, make_kuid(&init_user_ns, EXT2_DEF_RESUID)) ||
	    le16_to_cpu(es->s_def_resuid) != EXT2_DEF_RESUID) अणु
		seq_म_लिखो(seq, ",resuid=%u",
				from_kuid_munged(&init_user_ns, sbi->s_resuid));
	पूर्ण
	अगर (!gid_eq(sbi->s_resgid, make_kgid(&init_user_ns, EXT2_DEF_RESGID)) ||
	    le16_to_cpu(es->s_def_resgid) != EXT2_DEF_RESGID) अणु
		seq_म_लिखो(seq, ",resgid=%u",
				from_kgid_munged(&init_user_ns, sbi->s_resgid));
	पूर्ण
	अगर (test_opt(sb, ERRORS_RO)) अणु
		पूर्णांक def_errors = le16_to_cpu(es->s_errors);

		अगर (def_errors == EXT2_ERRORS_PANIC ||
		    def_errors == EXT2_ERRORS_CONTINUE) अणु
			seq_माला_दो(seq, ",errors=remount-ro");
		पूर्ण
	पूर्ण
	अगर (test_opt(sb, ERRORS_CONT))
		seq_माला_दो(seq, ",errors=continue");
	अगर (test_opt(sb, ERRORS_PANIC))
		seq_माला_दो(seq, ",errors=panic");
	अगर (test_opt(sb, NO_UID32))
		seq_माला_दो(seq, ",nouid32");
	अगर (test_opt(sb, DEBUG))
		seq_माला_दो(seq, ",debug");
	अगर (test_opt(sb, OLDALLOC))
		seq_माला_दो(seq, ",oldalloc");

#अगर_घोषित CONFIG_EXT2_FS_XATTR
	अगर (test_opt(sb, XATTR_USER))
		seq_माला_दो(seq, ",user_xattr");
	अगर (!test_opt(sb, XATTR_USER) &&
	    (def_mount_opts & EXT2_DEFM_XATTR_USER)) अणु
		seq_माला_दो(seq, ",nouser_xattr");
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_EXT2_FS_POSIX_ACL
	अगर (test_opt(sb, POSIX_ACL))
		seq_माला_दो(seq, ",acl");
	अगर (!test_opt(sb, POSIX_ACL) && (def_mount_opts & EXT2_DEFM_ACL))
		seq_माला_दो(seq, ",noacl");
#पूर्ण_अगर

	अगर (test_opt(sb, NOBH))
		seq_माला_दो(seq, ",nobh");

	अगर (test_opt(sb, USRQUOTA))
		seq_माला_दो(seq, ",usrquota");

	अगर (test_opt(sb, GRPQUOTA))
		seq_माला_दो(seq, ",grpquota");

	अगर (test_opt(sb, XIP))
		seq_माला_दो(seq, ",xip");

	अगर (test_opt(sb, DAX))
		seq_माला_दो(seq, ",dax");

	अगर (!test_opt(sb, RESERVATION))
		seq_माला_दो(seq, ",noreservation");

	spin_unlock(&sbi->s_lock);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल sमाप_प्रकार ext2_quota_पढ़ो(काष्ठा super_block *sb, पूर्णांक type, अक्षर *data, माप_प्रकार len, loff_t off);
अटल sमाप_प्रकार ext2_quota_ग_लिखो(काष्ठा super_block *sb, पूर्णांक type, स्थिर अक्षर *data, माप_प्रकार len, loff_t off);
अटल पूर्णांक ext2_quota_on(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
			 स्थिर काष्ठा path *path);
अटल काष्ठा dquot **ext2_get_dquots(काष्ठा inode *inode)
अणु
	वापस EXT2_I(inode)->i_dquot;
पूर्ण

अटल स्थिर काष्ठा quotactl_ops ext2_quotactl_ops = अणु
	.quota_on	= ext2_quota_on,
	.quota_off	= ext2_quota_off,
	.quota_sync	= dquot_quota_sync,
	.get_state	= dquot_get_state,
	.set_info	= dquot_set_dqinfo,
	.get_dqblk	= dquot_get_dqblk,
	.set_dqblk	= dquot_set_dqblk,
	.get_nextdqblk	= dquot_get_next_dqblk,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा super_operations ext2_sops = अणु
	.alloc_inode	= ext2_alloc_inode,
	.मुक्त_inode	= ext2_मुक्त_in_core_inode,
	.ग_लिखो_inode	= ext2_ग_लिखो_inode,
	.evict_inode	= ext2_evict_inode,
	.put_super	= ext2_put_super,
	.sync_fs	= ext2_sync_fs,
	.मुक्तze_fs	= ext2_मुक्तze,
	.unमुक्तze_fs	= ext2_unमुक्तze,
	.statfs		= ext2_statfs,
	.remount_fs	= ext2_remount,
	.show_options	= ext2_show_options,
#अगर_घोषित CONFIG_QUOTA
	.quota_पढ़ो	= ext2_quota_पढ़ो,
	.quota_ग_लिखो	= ext2_quota_ग_लिखो,
	.get_dquots	= ext2_get_dquots,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा inode *ext2_nfs_get_inode(काष्ठा super_block *sb,
		u64 ino, u32 generation)
अणु
	काष्ठा inode *inode;

	अगर (ino < EXT2_FIRST_INO(sb) && ino != EXT2_ROOT_INO)
		वापस ERR_PTR(-ESTALE);
	अगर (ino > le32_to_cpu(EXT2_SB(sb)->s_es->s_inodes_count))
		वापस ERR_PTR(-ESTALE);

	/*
	 * ext2_iget isn't quite right अगर the inode is currently unallocated!
	 * However ext2_iget currently करोes appropriate checks to handle stale
	 * inodes so everything is OK.
	 */
	inode = ext2_iget(sb, ino);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);
	अगर (generation && inode->i_generation != generation) अणु
		/* we didn't find the right inode.. */
		iput(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण
	वापस inode;
पूर्ण

अटल काष्ठा dentry *ext2_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_dentry(sb, fid, fh_len, fh_type,
				    ext2_nfs_get_inode);
पूर्ण

अटल काष्ठा dentry *ext2_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_parent(sb, fid, fh_len, fh_type,
				    ext2_nfs_get_inode);
पूर्ण

अटल स्थिर काष्ठा export_operations ext2_export_ops = अणु
	.fh_to_dentry = ext2_fh_to_dentry,
	.fh_to_parent = ext2_fh_to_parent,
	.get_parent = ext2_get_parent,
पूर्ण;

अटल अचिन्हित दीर्घ get_sb_block(व्योम **data)
अणु
	अचिन्हित दीर्घ 	sb_block;
	अक्षर 		*options = (अक्षर *) *data;

	अगर (!options || म_भेदन(options, "sb=", 3) != 0)
		वापस 1;	/* Default location */
	options += 3;
	sb_block = simple_म_से_अदीर्घ(options, &options, 0);
	अगर (*options && *options != ',') अणु
		prपूर्णांकk("EXT2-fs: Invalid sb specification: %s\n",
		       (अक्षर *) *data);
		वापस 1;
	पूर्ण
	अगर (*options == ',')
		options++;
	*data = (व्योम *) options;
	वापस sb_block;
पूर्ण

क्रमागत अणु
	Opt_bsd_df, Opt_minix_df, Opt_grpid, Opt_nogrpid,
	Opt_resgid, Opt_resuid, Opt_sb, Opt_err_cont, Opt_err_panic,
	Opt_err_ro, Opt_nouid32, Opt_debug,
	Opt_oldalloc, Opt_orlov, Opt_nobh, Opt_user_xattr, Opt_nouser_xattr,
	Opt_acl, Opt_noacl, Opt_xip, Opt_dax, Opt_ignore, Opt_err, Opt_quota,
	Opt_usrquota, Opt_grpquota, Opt_reservation, Opt_noreservation
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_bsd_df, "bsddf"पूर्ण,
	अणुOpt_minix_df, "minixdf"पूर्ण,
	अणुOpt_grpid, "grpid"पूर्ण,
	अणुOpt_grpid, "bsdgroups"पूर्ण,
	अणुOpt_nogrpid, "nogrpid"पूर्ण,
	अणुOpt_nogrpid, "sysvgroups"पूर्ण,
	अणुOpt_resgid, "resgid=%u"पूर्ण,
	अणुOpt_resuid, "resuid=%u"पूर्ण,
	अणुOpt_sb, "sb=%u"पूर्ण,
	अणुOpt_err_cont, "errors=continue"पूर्ण,
	अणुOpt_err_panic, "errors=panic"पूर्ण,
	अणुOpt_err_ro, "errors=remount-ro"पूर्ण,
	अणुOpt_nouid32, "nouid32"पूर्ण,
	अणुOpt_debug, "debug"पूर्ण,
	अणुOpt_oldalloc, "oldalloc"पूर्ण,
	अणुOpt_orlov, "orlov"पूर्ण,
	अणुOpt_nobh, "nobh"पूर्ण,
	अणुOpt_user_xattr, "user_xattr"पूर्ण,
	अणुOpt_nouser_xattr, "nouser_xattr"पूर्ण,
	अणुOpt_acl, "acl"पूर्ण,
	अणुOpt_noacl, "noacl"पूर्ण,
	अणुOpt_xip, "xip"पूर्ण,
	अणुOpt_dax, "dax"पूर्ण,
	अणुOpt_grpquota, "grpquota"पूर्ण,
	अणुOpt_ignore, "noquota"पूर्ण,
	अणुOpt_quota, "quota"पूर्ण,
	अणुOpt_usrquota, "usrquota"पूर्ण,
	अणुOpt_reservation, "reservation"पूर्ण,
	अणुOpt_noreservation, "noreservation"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक parse_options(अक्षर *options, काष्ठा super_block *sb,
			 काष्ठा ext2_mount_options *opts)
अणु
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक option;
	kuid_t uid;
	kgid_t gid;

	अगर (!options)
		वापस 1;

	जबतक ((p = strsep (&options, ",")) != शून्य) अणु
		पूर्णांक token;
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_bsd_df:
			clear_opt (opts->s_mount_opt, MINIX_DF);
			अवरोध;
		हाल Opt_minix_df:
			set_opt (opts->s_mount_opt, MINIX_DF);
			अवरोध;
		हाल Opt_grpid:
			set_opt (opts->s_mount_opt, GRPID);
			अवरोध;
		हाल Opt_nogrpid:
			clear_opt (opts->s_mount_opt, GRPID);
			अवरोध;
		हाल Opt_resuid:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			uid = make_kuid(current_user_ns(), option);
			अगर (!uid_valid(uid)) अणु
				ext2_msg(sb, KERN_ERR, "Invalid uid value %d", option);
				वापस 0;

			पूर्ण
			opts->s_resuid = uid;
			अवरोध;
		हाल Opt_resgid:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			gid = make_kgid(current_user_ns(), option);
			अगर (!gid_valid(gid)) अणु
				ext2_msg(sb, KERN_ERR, "Invalid gid value %d", option);
				वापस 0;
			पूर्ण
			opts->s_resgid = gid;
			अवरोध;
		हाल Opt_sb:
			/* handled by get_sb_block() instead of here */
			/* *sb_block = match_पूर्णांक(&args[0]); */
			अवरोध;
		हाल Opt_err_panic:
			clear_opt (opts->s_mount_opt, ERRORS_CONT);
			clear_opt (opts->s_mount_opt, ERRORS_RO);
			set_opt (opts->s_mount_opt, ERRORS_PANIC);
			अवरोध;
		हाल Opt_err_ro:
			clear_opt (opts->s_mount_opt, ERRORS_CONT);
			clear_opt (opts->s_mount_opt, ERRORS_PANIC);
			set_opt (opts->s_mount_opt, ERRORS_RO);
			अवरोध;
		हाल Opt_err_cont:
			clear_opt (opts->s_mount_opt, ERRORS_RO);
			clear_opt (opts->s_mount_opt, ERRORS_PANIC);
			set_opt (opts->s_mount_opt, ERRORS_CONT);
			अवरोध;
		हाल Opt_nouid32:
			set_opt (opts->s_mount_opt, NO_UID32);
			अवरोध;
		हाल Opt_debug:
			set_opt (opts->s_mount_opt, DEBUG);
			अवरोध;
		हाल Opt_oldalloc:
			set_opt (opts->s_mount_opt, OLDALLOC);
			अवरोध;
		हाल Opt_orlov:
			clear_opt (opts->s_mount_opt, OLDALLOC);
			अवरोध;
		हाल Opt_nobh:
			set_opt (opts->s_mount_opt, NOBH);
			अवरोध;
#अगर_घोषित CONFIG_EXT2_FS_XATTR
		हाल Opt_user_xattr:
			set_opt (opts->s_mount_opt, XATTR_USER);
			अवरोध;
		हाल Opt_nouser_xattr:
			clear_opt (opts->s_mount_opt, XATTR_USER);
			अवरोध;
#अन्यथा
		हाल Opt_user_xattr:
		हाल Opt_nouser_xattr:
			ext2_msg(sb, KERN_INFO, "(no)user_xattr options"
				"not supported");
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_EXT2_FS_POSIX_ACL
		हाल Opt_acl:
			set_opt(opts->s_mount_opt, POSIX_ACL);
			अवरोध;
		हाल Opt_noacl:
			clear_opt(opts->s_mount_opt, POSIX_ACL);
			अवरोध;
#अन्यथा
		हाल Opt_acl:
		हाल Opt_noacl:
			ext2_msg(sb, KERN_INFO,
				"(no)acl options not supported");
			अवरोध;
#पूर्ण_अगर
		हाल Opt_xip:
			ext2_msg(sb, KERN_INFO, "use dax instead of xip");
			set_opt(opts->s_mount_opt, XIP);
			fallthrough;
		हाल Opt_dax:
#अगर_घोषित CONFIG_FS_DAX
			ext2_msg(sb, KERN_WARNING,
		"DAX enabled. Warning: EXPERIMENTAL, use at your own risk");
			set_opt(opts->s_mount_opt, DAX);
#अन्यथा
			ext2_msg(sb, KERN_INFO, "dax option not supported");
#पूर्ण_अगर
			अवरोध;

#अगर defined(CONFIG_QUOTA)
		हाल Opt_quota:
		हाल Opt_usrquota:
			set_opt(opts->s_mount_opt, USRQUOTA);
			अवरोध;

		हाल Opt_grpquota:
			set_opt(opts->s_mount_opt, GRPQUOTA);
			अवरोध;
#अन्यथा
		हाल Opt_quota:
		हाल Opt_usrquota:
		हाल Opt_grpquota:
			ext2_msg(sb, KERN_INFO,
				"quota operations not supported");
			अवरोध;
#पूर्ण_अगर

		हाल Opt_reservation:
			set_opt(opts->s_mount_opt, RESERVATION);
			ext2_msg(sb, KERN_INFO, "reservations ON");
			अवरोध;
		हाल Opt_noreservation:
			clear_opt(opts->s_mount_opt, RESERVATION);
			ext2_msg(sb, KERN_INFO, "reservations OFF");
			अवरोध;
		हाल Opt_ignore:
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक ext2_setup_super (काष्ठा super_block * sb,
			      काष्ठा ext2_super_block * es,
			      पूर्णांक पढ़ो_only)
अणु
	पूर्णांक res = 0;
	काष्ठा ext2_sb_info *sbi = EXT2_SB(sb);

	अगर (le32_to_cpu(es->s_rev_level) > EXT2_MAX_SUPP_REV) अणु
		ext2_msg(sb, KERN_ERR,
			"error: revision level too high, "
			"forcing read-only mode");
		res = SB_RDONLY;
	पूर्ण
	अगर (पढ़ो_only)
		वापस res;
	अगर (!(sbi->s_mount_state & EXT2_VALID_FS))
		ext2_msg(sb, KERN_WARNING,
			"warning: mounting unchecked fs, "
			"running e2fsck is recommended");
	अन्यथा अगर ((sbi->s_mount_state & EXT2_ERROR_FS))
		ext2_msg(sb, KERN_WARNING,
			"warning: mounting fs with errors, "
			"running e2fsck is recommended");
	अन्यथा अगर ((__s16) le16_to_cpu(es->s_max_mnt_count) >= 0 &&
		 le16_to_cpu(es->s_mnt_count) >=
		 (अचिन्हित लघु) (__s16) le16_to_cpu(es->s_max_mnt_count))
		ext2_msg(sb, KERN_WARNING,
			"warning: maximal mount count reached, "
			"running e2fsck is recommended");
	अन्यथा अगर (le32_to_cpu(es->s_checkपूर्णांकerval) &&
		(le32_to_cpu(es->s_lastcheck) +
			le32_to_cpu(es->s_checkपूर्णांकerval) <=
			kसमय_get_real_seconds()))
		ext2_msg(sb, KERN_WARNING,
			"warning: checktime reached, "
			"running e2fsck is recommended");
	अगर (!le16_to_cpu(es->s_max_mnt_count))
		es->s_max_mnt_count = cpu_to_le16(EXT2_DFL_MAX_MNT_COUNT);
	le16_add_cpu(&es->s_mnt_count, 1);
	अगर (test_opt (sb, DEBUG))
		ext2_msg(sb, KERN_INFO, "%s, %s, bs=%lu, fs=%lu, gc=%lu, "
			"bpg=%lu, ipg=%lu, mo=%04lx]",
			EXT2FS_VERSION, EXT2FS_DATE, sb->s_blocksize,
			sbi->s_frag_size,
			sbi->s_groups_count,
			EXT2_BLOCKS_PER_GROUP(sb),
			EXT2_INODES_PER_GROUP(sb),
			sbi->s_mount_opt);
	वापस res;
पूर्ण

अटल पूर्णांक ext2_check_descriptors(काष्ठा super_block *sb)
अणु
	पूर्णांक i;
	काष्ठा ext2_sb_info *sbi = EXT2_SB(sb);

	ext2_debug ("Checking group descriptors");

	क्रम (i = 0; i < sbi->s_groups_count; i++) अणु
		काष्ठा ext2_group_desc *gdp = ext2_get_group_desc(sb, i, शून्य);
		ext2_fsblk_t first_block = ext2_group_first_block_no(sb, i);
		ext2_fsblk_t last_block = ext2_group_last_block_no(sb, i);

		अगर (le32_to_cpu(gdp->bg_block_biपंचांगap) < first_block ||
		    le32_to_cpu(gdp->bg_block_biपंचांगap) > last_block)
		अणु
			ext2_error (sb, "ext2_check_descriptors",
				    "Block bitmap for group %d"
				    " not in group (block %lu)!",
				    i, (अचिन्हित दीर्घ) le32_to_cpu(gdp->bg_block_biपंचांगap));
			वापस 0;
		पूर्ण
		अगर (le32_to_cpu(gdp->bg_inode_biपंचांगap) < first_block ||
		    le32_to_cpu(gdp->bg_inode_biपंचांगap) > last_block)
		अणु
			ext2_error (sb, "ext2_check_descriptors",
				    "Inode bitmap for group %d"
				    " not in group (block %lu)!",
				    i, (अचिन्हित दीर्घ) le32_to_cpu(gdp->bg_inode_biपंचांगap));
			वापस 0;
		पूर्ण
		अगर (le32_to_cpu(gdp->bg_inode_table) < first_block ||
		    le32_to_cpu(gdp->bg_inode_table) + sbi->s_itb_per_group - 1 >
		    last_block)
		अणु
			ext2_error (sb, "ext2_check_descriptors",
				    "Inode table for group %d"
				    " not in group (block %lu)!",
				    i, (अचिन्हित दीर्घ) le32_to_cpu(gdp->bg_inode_table));
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Maximal file size.  There is a direct, and अणु,द्विगुन-,triple-पूर्णindirect
 * block limit, and also a limit of (2^32 - 1) 512-byte sectors in i_blocks.
 * We need to be 1 fileप्रणाली block less than the 2^32 sector limit.
 */
अटल loff_t ext2_max_size(पूर्णांक bits)
अणु
	loff_t res = EXT2_Nसूची_BLOCKS;
	पूर्णांक meta_blocks;
	अचिन्हित पूर्णांक upper_limit;
	अचिन्हित पूर्णांक ppb = 1 << (bits-2);

	/* This is calculated to be the largest file size क्रम a
	 * dense, file such that the total number of
	 * sectors in the file, including data and all indirect blocks,
	 * करोes not exceed 2^32 -1
	 * __u32 i_blocks representing the total number of
	 * 512 bytes blocks of the file
	 */
	upper_limit = (1LL << 32) - 1;

	/* total blocks in file प्रणाली block size */
	upper_limit >>= (bits - 9);

	/* Compute how many blocks we can address by block tree */
	res += 1LL << (bits-2);
	res += 1LL << (2*(bits-2));
	res += 1LL << (3*(bits-2));
	/* Does block tree limit file size? */
	अगर (res < upper_limit)
		जाओ check_lfs;

	res = upper_limit;
	/* How many metadata blocks are needed क्रम addressing upper_limit? */
	upper_limit -= EXT2_Nसूची_BLOCKS;
	/* indirect blocks */
	meta_blocks = 1;
	upper_limit -= ppb;
	/* द्विगुन indirect blocks */
	अगर (upper_limit < ppb * ppb) अणु
		meta_blocks += 1 + DIV_ROUND_UP(upper_limit, ppb);
		res -= meta_blocks;
		जाओ check_lfs;
	पूर्ण
	meta_blocks += 1 + ppb;
	upper_limit -= ppb * ppb;
	/* tripple indirect blocks क्रम the rest */
	meta_blocks += 1 + DIV_ROUND_UP(upper_limit, ppb) +
		DIV_ROUND_UP(upper_limit, ppb*ppb);
	res -= meta_blocks;
check_lfs:
	res <<= bits;
	अगर (res > MAX_LFS_खाताSIZE)
		res = MAX_LFS_खाताSIZE;

	वापस res;
पूर्ण

अटल अचिन्हित दीर्घ descriptor_loc(काष्ठा super_block *sb,
				    अचिन्हित दीर्घ logic_sb_block,
				    पूर्णांक nr)
अणु
	काष्ठा ext2_sb_info *sbi = EXT2_SB(sb);
	अचिन्हित दीर्घ bg, first_meta_bg;
	
	first_meta_bg = le32_to_cpu(sbi->s_es->s_first_meta_bg);

	अगर (!EXT2_HAS_INCOMPAT_FEATURE(sb, EXT2_FEATURE_INCOMPAT_META_BG) ||
	    nr < first_meta_bg)
		वापस (logic_sb_block + nr + 1);
	bg = sbi->s_desc_per_block * nr;

	वापस ext2_group_first_block_no(sb, bg) + ext2_bg_has_super(sb, bg);
पूर्ण

अटल पूर्णांक ext2_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा dax_device *dax_dev = fs_dax_get_by_bdev(sb->s_bdev);
	काष्ठा buffer_head * bh;
	काष्ठा ext2_sb_info * sbi;
	काष्ठा ext2_super_block * es;
	काष्ठा inode *root;
	अचिन्हित दीर्घ block;
	अचिन्हित दीर्घ sb_block = get_sb_block(&data);
	अचिन्हित दीर्घ logic_sb_block;
	अचिन्हित दीर्घ offset = 0;
	अचिन्हित दीर्घ def_mount_opts;
	दीर्घ ret = -ENOMEM;
	पूर्णांक blocksize = BLOCK_SIZE;
	पूर्णांक db_count;
	पूर्णांक i, j;
	__le32 features;
	पूर्णांक err;
	काष्ठा ext2_mount_options opts;

	sbi = kzalloc(माप(*sbi), GFP_KERNEL);
	अगर (!sbi)
		जाओ failed;

	sbi->s_blockgroup_lock =
		kzalloc(माप(काष्ठा blockgroup_lock), GFP_KERNEL);
	अगर (!sbi->s_blockgroup_lock) अणु
		kमुक्त(sbi);
		जाओ failed;
	पूर्ण
	sb->s_fs_info = sbi;
	sbi->s_sb_block = sb_block;
	sbi->s_daxdev = dax_dev;

	spin_lock_init(&sbi->s_lock);
	ret = -EINVAL;

	/*
	 * See what the current blocksize क्रम the device is, and
	 * use that as the blocksize.  Otherwise (or अगर the blocksize
	 * is smaller than the शेष) use the शेष.
	 * This is important क्रम devices that have a hardware
	 * sectorsize that is larger than the शेष.
	 */
	blocksize = sb_min_blocksize(sb, BLOCK_SIZE);
	अगर (!blocksize) अणु
		ext2_msg(sb, KERN_ERR, "error: unable to set blocksize");
		जाओ failed_sbi;
	पूर्ण

	/*
	 * If the superblock करोesn't start on a hardware sector boundary,
	 * calculate the offset.  
	 */
	अगर (blocksize != BLOCK_SIZE) अणु
		logic_sb_block = (sb_block*BLOCK_SIZE) / blocksize;
		offset = (sb_block*BLOCK_SIZE) % blocksize;
	पूर्ण अन्यथा अणु
		logic_sb_block = sb_block;
	पूर्ण

	अगर (!(bh = sb_bपढ़ो(sb, logic_sb_block))) अणु
		ext2_msg(sb, KERN_ERR, "error: unable to read superblock");
		जाओ failed_sbi;
	पूर्ण
	/*
	 * Note: s_es must be initialized as soon as possible because
	 *       some ext2 macro-inकाष्ठाions depend on its value
	 */
	es = (काष्ठा ext2_super_block *) (((अक्षर *)bh->b_data) + offset);
	sbi->s_es = es;
	sb->s_magic = le16_to_cpu(es->s_magic);

	अगर (sb->s_magic != EXT2_SUPER_MAGIC)
		जाओ cantfind_ext2;

	opts.s_mount_opt = 0;
	/* Set शेषs beक्रमe we parse the mount options */
	def_mount_opts = le32_to_cpu(es->s_शेष_mount_opts);
	अगर (def_mount_opts & EXT2_DEFM_DEBUG)
		set_opt(opts.s_mount_opt, DEBUG);
	अगर (def_mount_opts & EXT2_DEFM_BSDGROUPS)
		set_opt(opts.s_mount_opt, GRPID);
	अगर (def_mount_opts & EXT2_DEFM_UID16)
		set_opt(opts.s_mount_opt, NO_UID32);
#अगर_घोषित CONFIG_EXT2_FS_XATTR
	अगर (def_mount_opts & EXT2_DEFM_XATTR_USER)
		set_opt(opts.s_mount_opt, XATTR_USER);
#पूर्ण_अगर
#अगर_घोषित CONFIG_EXT2_FS_POSIX_ACL
	अगर (def_mount_opts & EXT2_DEFM_ACL)
		set_opt(opts.s_mount_opt, POSIX_ACL);
#पूर्ण_अगर
	
	अगर (le16_to_cpu(sbi->s_es->s_errors) == EXT2_ERRORS_PANIC)
		set_opt(opts.s_mount_opt, ERRORS_PANIC);
	अन्यथा अगर (le16_to_cpu(sbi->s_es->s_errors) == EXT2_ERRORS_CONTINUE)
		set_opt(opts.s_mount_opt, ERRORS_CONT);
	अन्यथा
		set_opt(opts.s_mount_opt, ERRORS_RO);

	opts.s_resuid = make_kuid(&init_user_ns, le16_to_cpu(es->s_def_resuid));
	opts.s_resgid = make_kgid(&init_user_ns, le16_to_cpu(es->s_def_resgid));
	
	set_opt(opts.s_mount_opt, RESERVATION);

	अगर (!parse_options((अक्षर *) data, sb, &opts))
		जाओ failed_mount;

	sbi->s_mount_opt = opts.s_mount_opt;
	sbi->s_resuid = opts.s_resuid;
	sbi->s_resgid = opts.s_resgid;

	sb->s_flags = (sb->s_flags & ~SB_POSIXACL) |
		(test_opt(sb, POSIX_ACL) ? SB_POSIXACL : 0);
	sb->s_अगरlags |= SB_I_CGROUPWB;

	अगर (le32_to_cpu(es->s_rev_level) == EXT2_GOOD_OLD_REV &&
	    (EXT2_HAS_COMPAT_FEATURE(sb, ~0U) ||
	     EXT2_HAS_RO_COMPAT_FEATURE(sb, ~0U) ||
	     EXT2_HAS_INCOMPAT_FEATURE(sb, ~0U)))
		ext2_msg(sb, KERN_WARNING,
			"warning: feature flags set on rev 0 fs, "
			"running e2fsck is recommended");
	/*
	 * Check feature flags regardless of the revision level, since we
	 * previously didn't change the revision level when setting the flags,
	 * so there is a chance incompat flags are set on a rev 0 fileप्रणाली.
	 */
	features = EXT2_HAS_INCOMPAT_FEATURE(sb, ~EXT2_FEATURE_INCOMPAT_SUPP);
	अगर (features) अणु
		ext2_msg(sb, KERN_ERR,	"error: couldn't mount because of "
		       "unsupported optional features (%x)",
			le32_to_cpu(features));
		जाओ failed_mount;
	पूर्ण
	अगर (!sb_rकरोnly(sb) && (features = EXT2_HAS_RO_COMPAT_FEATURE(sb, ~EXT2_FEATURE_RO_COMPAT_SUPP)))अणु
		ext2_msg(sb, KERN_ERR, "error: couldn't mount RDWR because of "
		       "unsupported optional features (%x)",
		       le32_to_cpu(features));
		जाओ failed_mount;
	पूर्ण

	blocksize = BLOCK_SIZE << le32_to_cpu(sbi->s_es->s_log_block_size);

	अगर (test_opt(sb, DAX)) अणु
		अगर (!bdev_dax_supported(sb->s_bdev, blocksize)) अणु
			ext2_msg(sb, KERN_ERR,
				"DAX unsupported by block device. Turning off DAX.");
			clear_opt(sbi->s_mount_opt, DAX);
		पूर्ण
	पूर्ण

	/* If the blocksize करोesn't match, re-पढ़ो the thing.. */
	अगर (sb->s_blocksize != blocksize) अणु
		brअन्यथा(bh);

		अगर (!sb_set_blocksize(sb, blocksize)) अणु
			ext2_msg(sb, KERN_ERR,
				"error: bad blocksize %d", blocksize);
			जाओ failed_sbi;
		पूर्ण

		logic_sb_block = (sb_block*BLOCK_SIZE) / blocksize;
		offset = (sb_block*BLOCK_SIZE) % blocksize;
		bh = sb_bपढ़ो(sb, logic_sb_block);
		अगर(!bh) अणु
			ext2_msg(sb, KERN_ERR, "error: couldn't read"
				"superblock on 2nd try");
			जाओ failed_sbi;
		पूर्ण
		es = (काष्ठा ext2_super_block *) (((अक्षर *)bh->b_data) + offset);
		sbi->s_es = es;
		अगर (es->s_magic != cpu_to_le16(EXT2_SUPER_MAGIC)) अणु
			ext2_msg(sb, KERN_ERR, "error: magic mismatch");
			जाओ failed_mount;
		पूर्ण
	पूर्ण

	sb->s_maxbytes = ext2_max_size(sb->s_blocksize_bits);
	sb->s_max_links = EXT2_LINK_MAX;
	sb->s_समय_min = S32_MIN;
	sb->s_समय_max = S32_MAX;

	अगर (le32_to_cpu(es->s_rev_level) == EXT2_GOOD_OLD_REV) अणु
		sbi->s_inode_size = EXT2_GOOD_OLD_INODE_SIZE;
		sbi->s_first_ino = EXT2_GOOD_OLD_FIRST_INO;
	पूर्ण अन्यथा अणु
		sbi->s_inode_size = le16_to_cpu(es->s_inode_size);
		sbi->s_first_ino = le32_to_cpu(es->s_first_ino);
		अगर ((sbi->s_inode_size < EXT2_GOOD_OLD_INODE_SIZE) ||
		    !is_घातer_of_2(sbi->s_inode_size) ||
		    (sbi->s_inode_size > blocksize)) अणु
			ext2_msg(sb, KERN_ERR,
				"error: unsupported inode size: %d",
				sbi->s_inode_size);
			जाओ failed_mount;
		पूर्ण
	पूर्ण

	sbi->s_frag_size = EXT2_MIN_FRAG_SIZE <<
				   le32_to_cpu(es->s_log_frag_size);
	अगर (sbi->s_frag_size == 0)
		जाओ cantfind_ext2;
	sbi->s_frags_per_block = sb->s_blocksize / sbi->s_frag_size;

	sbi->s_blocks_per_group = le32_to_cpu(es->s_blocks_per_group);
	sbi->s_frags_per_group = le32_to_cpu(es->s_frags_per_group);
	sbi->s_inodes_per_group = le32_to_cpu(es->s_inodes_per_group);

	sbi->s_inodes_per_block = sb->s_blocksize / EXT2_INODE_SIZE(sb);
	अगर (sbi->s_inodes_per_block == 0 || sbi->s_inodes_per_group == 0)
		जाओ cantfind_ext2;
	sbi->s_itb_per_group = sbi->s_inodes_per_group /
					sbi->s_inodes_per_block;
	sbi->s_desc_per_block = sb->s_blocksize /
					माप (काष्ठा ext2_group_desc);
	sbi->s_sbh = bh;
	sbi->s_mount_state = le16_to_cpu(es->s_state);
	sbi->s_addr_per_block_bits =
		ilog2 (EXT2_ADDR_PER_BLOCK(sb));
	sbi->s_desc_per_block_bits =
		ilog2 (EXT2_DESC_PER_BLOCK(sb));

	अगर (sb->s_magic != EXT2_SUPER_MAGIC)
		जाओ cantfind_ext2;

	अगर (sb->s_blocksize != bh->b_size) अणु
		अगर (!silent)
			ext2_msg(sb, KERN_ERR, "error: unsupported blocksize");
		जाओ failed_mount;
	पूर्ण

	अगर (sb->s_blocksize != sbi->s_frag_size) अणु
		ext2_msg(sb, KERN_ERR,
			"error: fragsize %lu != blocksize %lu"
			"(not supported yet)",
			sbi->s_frag_size, sb->s_blocksize);
		जाओ failed_mount;
	पूर्ण

	अगर (sbi->s_blocks_per_group > sb->s_blocksize * 8) अणु
		ext2_msg(sb, KERN_ERR,
			"error: #blocks per group too big: %lu",
			sbi->s_blocks_per_group);
		जाओ failed_mount;
	पूर्ण
	अगर (sbi->s_frags_per_group > sb->s_blocksize * 8) अणु
		ext2_msg(sb, KERN_ERR,
			"error: #fragments per group too big: %lu",
			sbi->s_frags_per_group);
		जाओ failed_mount;
	पूर्ण
	अगर (sbi->s_inodes_per_group > sb->s_blocksize * 8) अणु
		ext2_msg(sb, KERN_ERR,
			"error: #inodes per group too big: %lu",
			sbi->s_inodes_per_group);
		जाओ failed_mount;
	पूर्ण

	अगर (EXT2_BLOCKS_PER_GROUP(sb) == 0)
		जाओ cantfind_ext2;
	sbi->s_groups_count = ((le32_to_cpu(es->s_blocks_count) -
				le32_to_cpu(es->s_first_data_block) - 1)
					/ EXT2_BLOCKS_PER_GROUP(sb)) + 1;
	db_count = (sbi->s_groups_count + EXT2_DESC_PER_BLOCK(sb) - 1) /
		   EXT2_DESC_PER_BLOCK(sb);
	sbi->s_group_desc = kदो_स्मृति_array(db_count,
					   माप(काष्ठा buffer_head *),
					   GFP_KERNEL);
	अगर (sbi->s_group_desc == शून्य) अणु
		ret = -ENOMEM;
		ext2_msg(sb, KERN_ERR, "error: not enough memory");
		जाओ failed_mount;
	पूर्ण
	bgl_lock_init(sbi->s_blockgroup_lock);
	sbi->s_debts = kसुस्मृति(sbi->s_groups_count, माप(*sbi->s_debts), GFP_KERNEL);
	अगर (!sbi->s_debts) अणु
		ret = -ENOMEM;
		ext2_msg(sb, KERN_ERR, "error: not enough memory");
		जाओ failed_mount_group_desc;
	पूर्ण
	क्रम (i = 0; i < db_count; i++) अणु
		block = descriptor_loc(sb, logic_sb_block, i);
		sbi->s_group_desc[i] = sb_bपढ़ो(sb, block);
		अगर (!sbi->s_group_desc[i]) अणु
			क्रम (j = 0; j < i; j++)
				brअन्यथा (sbi->s_group_desc[j]);
			ext2_msg(sb, KERN_ERR,
				"error: unable to read group descriptors");
			जाओ failed_mount_group_desc;
		पूर्ण
	पूर्ण
	अगर (!ext2_check_descriptors (sb)) अणु
		ext2_msg(sb, KERN_ERR, "group descriptors corrupted");
		जाओ failed_mount2;
	पूर्ण
	sbi->s_gdb_count = db_count;
	get_अक्रमom_bytes(&sbi->s_next_generation, माप(u32));
	spin_lock_init(&sbi->s_next_gen_lock);

	/* per fileप्रणाली reservation list head & lock */
	spin_lock_init(&sbi->s_rsv_winकरोw_lock);
	sbi->s_rsv_winकरोw_root = RB_ROOT;
	/*
	 * Add a single, अटल dummy reservation to the start of the
	 * reservation winकरोw list --- it gives us a placeholder क्रम
	 * append-at-start-of-list which makes the allocation logic
	 * _much_ simpler.
	 */
	sbi->s_rsv_winकरोw_head.rsv_start = EXT2_RESERVE_WINDOW_NOT_ALLOCATED;
	sbi->s_rsv_winकरोw_head.rsv_end = EXT2_RESERVE_WINDOW_NOT_ALLOCATED;
	sbi->s_rsv_winकरोw_head.rsv_alloc_hit = 0;
	sbi->s_rsv_winकरोw_head.rsv_goal_size = 0;
	ext2_rsv_winकरोw_add(sb, &sbi->s_rsv_winकरोw_head);

	err = percpu_counter_init(&sbi->s_मुक्तblocks_counter,
				ext2_count_मुक्त_blocks(sb), GFP_KERNEL);
	अगर (!err) अणु
		err = percpu_counter_init(&sbi->s_मुक्तinodes_counter,
				ext2_count_मुक्त_inodes(sb), GFP_KERNEL);
	पूर्ण
	अगर (!err) अणु
		err = percpu_counter_init(&sbi->s_dirs_counter,
				ext2_count_dirs(sb), GFP_KERNEL);
	पूर्ण
	अगर (err) अणु
		ret = err;
		ext2_msg(sb, KERN_ERR, "error: insufficient memory");
		जाओ failed_mount3;
	पूर्ण

#अगर_घोषित CONFIG_EXT2_FS_XATTR
	sbi->s_ea_block_cache = ext2_xattr_create_cache();
	अगर (!sbi->s_ea_block_cache) अणु
		ret = -ENOMEM;
		ext2_msg(sb, KERN_ERR, "Failed to create ea_block_cache");
		जाओ failed_mount3;
	पूर्ण
#पूर्ण_अगर
	/*
	 * set up enough so that it can पढ़ो an inode
	 */
	sb->s_op = &ext2_sops;
	sb->s_export_op = &ext2_export_ops;
	sb->s_xattr = ext2_xattr_handlers;

#अगर_घोषित CONFIG_QUOTA
	sb->dq_op = &dquot_operations;
	sb->s_qcop = &ext2_quotactl_ops;
	sb->s_quota_types = QTYPE_MASK_USR | QTYPE_MASK_GRP;
#पूर्ण_अगर

	root = ext2_iget(sb, EXT2_ROOT_INO);
	अगर (IS_ERR(root)) अणु
		ret = PTR_ERR(root);
		जाओ failed_mount3;
	पूर्ण
	अगर (!S_ISसूची(root->i_mode) || !root->i_blocks || !root->i_size) अणु
		iput(root);
		ext2_msg(sb, KERN_ERR, "error: corrupt root inode, run e2fsck");
		जाओ failed_mount3;
	पूर्ण

	sb->s_root = d_make_root(root);
	अगर (!sb->s_root) अणु
		ext2_msg(sb, KERN_ERR, "error: get root inode failed");
		ret = -ENOMEM;
		जाओ failed_mount3;
	पूर्ण
	अगर (EXT2_HAS_COMPAT_FEATURE(sb, EXT3_FEATURE_COMPAT_HAS_JOURNAL))
		ext2_msg(sb, KERN_WARNING,
			"warning: mounting ext3 filesystem as ext2");
	अगर (ext2_setup_super (sb, es, sb_rकरोnly(sb)))
		sb->s_flags |= SB_RDONLY;
	ext2_ग_लिखो_super(sb);
	वापस 0;

cantfind_ext2:
	अगर (!silent)
		ext2_msg(sb, KERN_ERR,
			"error: can't find an ext2 filesystem on dev %s.",
			sb->s_id);
	जाओ failed_mount;
failed_mount3:
	ext2_xattr_destroy_cache(sbi->s_ea_block_cache);
	percpu_counter_destroy(&sbi->s_मुक्तblocks_counter);
	percpu_counter_destroy(&sbi->s_मुक्तinodes_counter);
	percpu_counter_destroy(&sbi->s_dirs_counter);
failed_mount2:
	क्रम (i = 0; i < db_count; i++)
		brअन्यथा(sbi->s_group_desc[i]);
failed_mount_group_desc:
	kमुक्त(sbi->s_group_desc);
	kमुक्त(sbi->s_debts);
failed_mount:
	brअन्यथा(bh);
failed_sbi:
	sb->s_fs_info = शून्य;
	kमुक्त(sbi->s_blockgroup_lock);
	kमुक्त(sbi);
failed:
	fs_put_dax(dax_dev);
	वापस ret;
पूर्ण

अटल व्योम ext2_clear_super_error(काष्ठा super_block *sb)
अणु
	काष्ठा buffer_head *sbh = EXT2_SB(sb)->s_sbh;

	अगर (buffer_ग_लिखो_io_error(sbh)) अणु
		/*
		 * Oh, dear.  A previous attempt to ग_लिखो the
		 * superblock failed.  This could happen because the
		 * USB device was yanked out.  Or it could happen to
		 * be a transient ग_लिखो error and maybe the block will
		 * be remapped.  Nothing we can करो but to retry the
		 * ग_लिखो and hope क्रम the best.
		 */
		ext2_msg(sb, KERN_ERR,
		       "previous I/O error to superblock detected");
		clear_buffer_ग_लिखो_io_error(sbh);
		set_buffer_uptodate(sbh);
	पूर्ण
पूर्ण

व्योम ext2_sync_super(काष्ठा super_block *sb, काष्ठा ext2_super_block *es,
		     पूर्णांक रुको)
अणु
	ext2_clear_super_error(sb);
	spin_lock(&EXT2_SB(sb)->s_lock);
	es->s_मुक्त_blocks_count = cpu_to_le32(ext2_count_मुक्त_blocks(sb));
	es->s_मुक्त_inodes_count = cpu_to_le32(ext2_count_मुक्त_inodes(sb));
	es->s_wसमय = cpu_to_le32(kसमय_get_real_seconds());
	/* unlock beक्रमe we करो IO */
	spin_unlock(&EXT2_SB(sb)->s_lock);
	mark_buffer_dirty(EXT2_SB(sb)->s_sbh);
	अगर (रुको)
		sync_dirty_buffer(EXT2_SB(sb)->s_sbh);
पूर्ण

/*
 * In the second extended file प्रणाली, it is not necessary to
 * ग_लिखो the super block since we use a mapping of the
 * disk super block in a buffer.
 *
 * However, this function is still used to set the fs valid
 * flags to 0.  We need to set this flag to 0 since the fs
 * may have been checked जबतक mounted and e2fsck may have
 * set s_state to EXT2_VALID_FS after some corrections.
 */
अटल पूर्णांक ext2_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा ext2_sb_info *sbi = EXT2_SB(sb);
	काष्ठा ext2_super_block *es = EXT2_SB(sb)->s_es;

	/*
	 * Write quota काष्ठाures to quota file, sync_blockdev() will ग_लिखो
	 * them to disk later
	 */
	dquot_ग_लिखोback_dquots(sb, -1);

	spin_lock(&sbi->s_lock);
	अगर (es->s_state & cpu_to_le16(EXT2_VALID_FS)) अणु
		ext2_debug("setting valid to 0\n");
		es->s_state &= cpu_to_le16(~EXT2_VALID_FS);
	पूर्ण
	spin_unlock(&sbi->s_lock);
	ext2_sync_super(sb, es, रुको);
	वापस 0;
पूर्ण

अटल पूर्णांक ext2_मुक्तze(काष्ठा super_block *sb)
अणु
	काष्ठा ext2_sb_info *sbi = EXT2_SB(sb);

	/*
	 * Open but unlinked files present? Keep EXT2_VALID_FS flag cleared
	 * because we have unattached inodes and thus fileप्रणाली is not fully
	 * consistent.
	 */
	अगर (atomic_दीर्घ_पढ़ो(&sb->s_हटाओ_count)) अणु
		ext2_sync_fs(sb, 1);
		वापस 0;
	पूर्ण
	/* Set EXT2_FS_VALID flag */
	spin_lock(&sbi->s_lock);
	sbi->s_es->s_state = cpu_to_le16(sbi->s_mount_state);
	spin_unlock(&sbi->s_lock);
	ext2_sync_super(sb, sbi->s_es, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक ext2_unमुक्तze(काष्ठा super_block *sb)
अणु
	/* Just ग_लिखो sb to clear EXT2_VALID_FS flag */
	ext2_ग_लिखो_super(sb);

	वापस 0;
पूर्ण

अटल व्योम ext2_ग_लिखो_super(काष्ठा super_block *sb)
अणु
	अगर (!sb_rकरोnly(sb))
		ext2_sync_fs(sb, 1);
पूर्ण

अटल पूर्णांक ext2_remount (काष्ठा super_block * sb, पूर्णांक * flags, अक्षर * data)
अणु
	काष्ठा ext2_sb_info * sbi = EXT2_SB(sb);
	काष्ठा ext2_super_block * es;
	काष्ठा ext2_mount_options new_opts;
	पूर्णांक err;

	sync_fileप्रणाली(sb);

	spin_lock(&sbi->s_lock);
	new_opts.s_mount_opt = sbi->s_mount_opt;
	new_opts.s_resuid = sbi->s_resuid;
	new_opts.s_resgid = sbi->s_resgid;
	spin_unlock(&sbi->s_lock);

	अगर (!parse_options(data, sb, &new_opts))
		वापस -EINVAL;

	spin_lock(&sbi->s_lock);
	es = sbi->s_es;
	अगर ((sbi->s_mount_opt ^ new_opts.s_mount_opt) & EXT2_MOUNT_DAX) अणु
		ext2_msg(sb, KERN_WARNING, "warning: refusing change of "
			 "dax flag with busy inodes while remounting");
		new_opts.s_mount_opt ^= EXT2_MOUNT_DAX;
	पूर्ण
	अगर ((bool)(*flags & SB_RDONLY) == sb_rकरोnly(sb))
		जाओ out_set;
	अगर (*flags & SB_RDONLY) अणु
		अगर (le16_to_cpu(es->s_state) & EXT2_VALID_FS ||
		    !(sbi->s_mount_state & EXT2_VALID_FS))
			जाओ out_set;

		/*
		 * OK, we are remounting a valid rw partition rकरोnly, so set
		 * the rकरोnly flag and then mark the partition as valid again.
		 */
		es->s_state = cpu_to_le16(sbi->s_mount_state);
		es->s_mसमय = cpu_to_le32(kसमय_get_real_seconds());
		spin_unlock(&sbi->s_lock);

		err = dquot_suspend(sb, -1);
		अगर (err < 0)
			वापस err;

		ext2_sync_super(sb, es, 1);
	पूर्ण अन्यथा अणु
		__le32 ret = EXT2_HAS_RO_COMPAT_FEATURE(sb,
					       ~EXT2_FEATURE_RO_COMPAT_SUPP);
		अगर (ret) अणु
			spin_unlock(&sbi->s_lock);
			ext2_msg(sb, KERN_WARNING,
				"warning: couldn't remount RDWR because of "
				"unsupported optional features (%x).",
				le32_to_cpu(ret));
			वापस -EROFS;
		पूर्ण
		/*
		 * Mounting a RDONLY partition पढ़ो-ग_लिखो, so reपढ़ो and
		 * store the current valid flag.  (It may have been changed
		 * by e2fsck since we originally mounted the partition.)
		 */
		sbi->s_mount_state = le16_to_cpu(es->s_state);
		अगर (!ext2_setup_super (sb, es, 0))
			sb->s_flags &= ~SB_RDONLY;
		spin_unlock(&sbi->s_lock);

		ext2_ग_लिखो_super(sb);

		dquot_resume(sb, -1);
	पूर्ण

	spin_lock(&sbi->s_lock);
out_set:
	sbi->s_mount_opt = new_opts.s_mount_opt;
	sbi->s_resuid = new_opts.s_resuid;
	sbi->s_resgid = new_opts.s_resgid;
	sb->s_flags = (sb->s_flags & ~SB_POSIXACL) |
		(test_opt(sb, POSIX_ACL) ? SB_POSIXACL : 0);
	spin_unlock(&sbi->s_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ext2_statfs (काष्ठा dentry * dentry, काष्ठा kstatfs * buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा ext2_sb_info *sbi = EXT2_SB(sb);
	काष्ठा ext2_super_block *es = sbi->s_es;

	spin_lock(&sbi->s_lock);

	अगर (test_opt (sb, MINIX_DF))
		sbi->s_overhead_last = 0;
	अन्यथा अगर (sbi->s_blocks_last != le32_to_cpu(es->s_blocks_count)) अणु
		अचिन्हित दीर्घ i, overhead = 0;
		smp_rmb();

		/*
		 * Compute the overhead (FS काष्ठाures). This is स्थिरant
		 * क्रम a given fileप्रणाली unless the number of block groups
		 * changes so we cache the previous value until it करोes.
		 */

		/*
		 * All of the blocks beक्रमe first_data_block are
		 * overhead
		 */
		overhead = le32_to_cpu(es->s_first_data_block);

		/*
		 * Add the overhead attributed to the superblock and
		 * block group descriptors.  If the sparse superblocks
		 * feature is turned on, then not all groups have this.
		 */
		क्रम (i = 0; i < sbi->s_groups_count; i++)
			overhead += ext2_bg_has_super(sb, i) +
				ext2_bg_num_gdb(sb, i);

		/*
		 * Every block group has an inode biपंचांगap, a block
		 * biपंचांगap, and an inode table.
		 */
		overhead += (sbi->s_groups_count *
			     (2 + sbi->s_itb_per_group));
		sbi->s_overhead_last = overhead;
		smp_wmb();
		sbi->s_blocks_last = le32_to_cpu(es->s_blocks_count);
	पूर्ण

	buf->f_type = EXT2_SUPER_MAGIC;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = le32_to_cpu(es->s_blocks_count) - sbi->s_overhead_last;
	buf->f_bमुक्त = ext2_count_मुक्त_blocks(sb);
	es->s_मुक्त_blocks_count = cpu_to_le32(buf->f_bमुक्त);
	buf->f_bavail = buf->f_bमुक्त - le32_to_cpu(es->s_r_blocks_count);
	अगर (buf->f_bमुक्त < le32_to_cpu(es->s_r_blocks_count))
		buf->f_bavail = 0;
	buf->f_files = le32_to_cpu(es->s_inodes_count);
	buf->f_fमुक्त = ext2_count_मुक्त_inodes(sb);
	es->s_मुक्त_inodes_count = cpu_to_le32(buf->f_fमुक्त);
	buf->f_namelen = EXT2_NAME_LEN;
	buf->f_fsid = uuid_to_fsid(es->s_uuid);
	spin_unlock(&sbi->s_lock);
	वापस 0;
पूर्ण

अटल काष्ठा dentry *ext2_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, ext2_fill_super);
पूर्ण

#अगर_घोषित CONFIG_QUOTA

/* Read data from quotafile - aव्योम pagecache and such because we cannot afक्रमd
 * acquiring the locks... As quota files are never truncated and quota code
 * itself serializes the operations (and no one अन्यथा should touch the files)
 * we करोn't have to be afraid of races */
अटल sमाप_प्रकार ext2_quota_पढ़ो(काष्ठा super_block *sb, पूर्णांक type, अक्षर *data,
			       माप_प्रकार len, loff_t off)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	sector_t blk = off >> EXT2_BLOCK_SIZE_BITS(sb);
	पूर्णांक err = 0;
	पूर्णांक offset = off & (sb->s_blocksize - 1);
	पूर्णांक tocopy;
	माप_प्रकार toपढ़ो;
	काष्ठा buffer_head पंचांगp_bh;
	काष्ठा buffer_head *bh;
	loff_t i_size = i_size_पढ़ो(inode);

	अगर (off > i_size)
		वापस 0;
	अगर (off+len > i_size)
		len = i_size-off;
	toपढ़ो = len;
	जबतक (toपढ़ो > 0) अणु
		tocopy = sb->s_blocksize - offset < toपढ़ो ?
				sb->s_blocksize - offset : toपढ़ो;

		पंचांगp_bh.b_state = 0;
		पंचांगp_bh.b_size = sb->s_blocksize;
		err = ext2_get_block(inode, blk, &पंचांगp_bh, 0);
		अगर (err < 0)
			वापस err;
		अगर (!buffer_mapped(&पंचांगp_bh))	/* A hole? */
			स_रखो(data, 0, tocopy);
		अन्यथा अणु
			bh = sb_bपढ़ो(sb, पंचांगp_bh.b_blocknr);
			अगर (!bh)
				वापस -EIO;
			स_नकल(data, bh->b_data+offset, tocopy);
			brअन्यथा(bh);
		पूर्ण
		offset = 0;
		toपढ़ो -= tocopy;
		data += tocopy;
		blk++;
	पूर्ण
	वापस len;
पूर्ण

/* Write to quotafile */
अटल sमाप_प्रकार ext2_quota_ग_लिखो(काष्ठा super_block *sb, पूर्णांक type,
				स्थिर अक्षर *data, माप_प्रकार len, loff_t off)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	sector_t blk = off >> EXT2_BLOCK_SIZE_BITS(sb);
	पूर्णांक err = 0;
	पूर्णांक offset = off & (sb->s_blocksize - 1);
	पूर्णांक tocopy;
	माप_प्रकार toग_लिखो = len;
	काष्ठा buffer_head पंचांगp_bh;
	काष्ठा buffer_head *bh;

	जबतक (toग_लिखो > 0) अणु
		tocopy = sb->s_blocksize - offset < toग_लिखो ?
				sb->s_blocksize - offset : toग_लिखो;

		पंचांगp_bh.b_state = 0;
		पंचांगp_bh.b_size = sb->s_blocksize;
		err = ext2_get_block(inode, blk, &पंचांगp_bh, 1);
		अगर (err < 0)
			जाओ out;
		अगर (offset || tocopy != EXT2_BLOCK_SIZE(sb))
			bh = sb_bपढ़ो(sb, पंचांगp_bh.b_blocknr);
		अन्यथा
			bh = sb_getblk(sb, पंचांगp_bh.b_blocknr);
		अगर (unlikely(!bh)) अणु
			err = -EIO;
			जाओ out;
		पूर्ण
		lock_buffer(bh);
		स_नकल(bh->b_data+offset, data, tocopy);
		flush_dcache_page(bh->b_page);
		set_buffer_uptodate(bh);
		mark_buffer_dirty(bh);
		unlock_buffer(bh);
		brअन्यथा(bh);
		offset = 0;
		toग_लिखो -= tocopy;
		data += tocopy;
		blk++;
	पूर्ण
out:
	अगर (len == toग_लिखो)
		वापस err;
	अगर (inode->i_size < off+len-toग_लिखो)
		i_size_ग_लिखो(inode, off+len-toग_लिखो);
	inode_inc_iversion(inode);
	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);
	वापस len - toग_लिखो;
पूर्ण

अटल पूर्णांक ext2_quota_on(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
			 स्थिर काष्ठा path *path)
अणु
	पूर्णांक err;
	काष्ठा inode *inode;

	err = dquot_quota_on(sb, type, क्रमmat_id, path);
	अगर (err)
		वापस err;

	inode = d_inode(path->dentry);
	inode_lock(inode);
	EXT2_I(inode)->i_flags |= EXT2_NOATIME_FL | EXT2_IMMUTABLE_FL;
	inode_set_flags(inode, S_NOATIME | S_IMMUTABLE,
			S_NOATIME | S_IMMUTABLE);
	inode_unlock(inode);
	mark_inode_dirty(inode);

	वापस 0;
पूर्ण

अटल पूर्णांक ext2_quota_off(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	पूर्णांक err;

	अगर (!inode || !igrab(inode))
		जाओ out;

	err = dquot_quota_off(sb, type);
	अगर (err)
		जाओ out_put;

	inode_lock(inode);
	EXT2_I(inode)->i_flags &= ~(EXT2_NOATIME_FL | EXT2_IMMUTABLE_FL);
	inode_set_flags(inode, 0, S_NOATIME | S_IMMUTABLE);
	inode_unlock(inode);
	mark_inode_dirty(inode);
out_put:
	iput(inode);
	वापस err;
out:
	वापस dquot_quota_off(sb, type);
पूर्ण

#पूर्ण_अगर

अटल काष्ठा file_प्रणाली_type ext2_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "ext2",
	.mount		= ext2_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("ext2");

अटल पूर्णांक __init init_ext2_fs(व्योम)
अणु
	पूर्णांक err;

	err = init_inodecache();
	अगर (err)
		वापस err;
        err = रेजिस्टर_fileप्रणाली(&ext2_fs_type);
	अगर (err)
		जाओ out;
	वापस 0;
out:
	destroy_inodecache();
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_ext2_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&ext2_fs_type);
	destroy_inodecache();
पूर्ण

MODULE_AUTHOR("Remy Card and others");
MODULE_DESCRIPTION("Second Extended Filesystem");
MODULE_LICENSE("GPL");
module_init(init_ext2_fs)
module_निकास(निकास_ext2_fs)
