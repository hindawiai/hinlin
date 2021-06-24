<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */

#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/parser.h>
#समावेश <linux/completion.h>
#समावेश <linux/vfs.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/mount.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/crc32.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/blkdev.h>

#समावेश "jfs_incore.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_inode.h"
#समावेश "jfs_metapage.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_imap.h"
#समावेश "jfs_acl.h"
#समावेश "jfs_debug.h"
#समावेश "jfs_xattr.h"
#समावेश "jfs_dinode.h"

MODULE_DESCRIPTION("The Journaled Filesystem (JFS)");
MODULE_AUTHOR("Steve Best/Dave Kleikamp/Barry Arndt, IBM");
MODULE_LICENSE("GPL");

अटल काष्ठा kmem_cache *jfs_inode_cachep;

अटल स्थिर काष्ठा super_operations jfs_super_operations;
अटल स्थिर काष्ठा export_operations jfs_export_operations;
अटल काष्ठा file_प्रणाली_type jfs_fs_type;

#घोषणा MAX_COMMIT_THREADS 64
अटल पूर्णांक commit_thपढ़ोs;
module_param(commit_thपढ़ोs, पूर्णांक, 0);
MODULE_PARM_DESC(commit_thपढ़ोs, "Number of commit threads");

अटल काष्ठा task_काष्ठा *jfsCommitThपढ़ो[MAX_COMMIT_THREADS];
काष्ठा task_काष्ठा *jfsIOthपढ़ो;
काष्ठा task_काष्ठा *jfsSyncThपढ़ो;

#अगर_घोषित CONFIG_JFS_DEBUG
पूर्णांक jfsloglevel = JFS_LOGLEVEL_WARN;
module_param(jfsloglevel, पूर्णांक, 0644);
MODULE_PARM_DESC(jfsloglevel, "Specify JFS loglevel (0, 1 or 2)");
#पूर्ण_अगर

अटल व्योम jfs_handle_error(काष्ठा super_block *sb)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);

	अगर (sb_rकरोnly(sb))
		वापस;

	updateSuper(sb, FM_सूचीTY);

	अगर (sbi->flag & JFS_ERR_PANIC)
		panic("JFS (device %s): panic forced after error\n",
			sb->s_id);
	अन्यथा अगर (sbi->flag & JFS_ERR_REMOUNT_RO) अणु
		jfs_err("ERROR: (device %s): remounting filesystem as read-only",
			sb->s_id);
		sb->s_flags |= SB_RDONLY;
	पूर्ण

	/* nothing is करोne क्रम जारी beyond marking the superblock dirty */
पूर्ण

व्योम jfs_error(काष्ठा super_block *sb, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	pr_err("ERROR: (device %s): %ps: %pV\n",
	       sb->s_id, __builtin_वापस_address(0), &vaf);

	बहु_पूर्ण(args);

	jfs_handle_error(sb);
पूर्ण

अटल काष्ठा inode *jfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा jfs_inode_info *jfs_inode;

	jfs_inode = kmem_cache_alloc(jfs_inode_cachep, GFP_NOFS);
	अगर (!jfs_inode)
		वापस शून्य;
#अगर_घोषित CONFIG_QUOTA
	स_रखो(&jfs_inode->i_dquot, 0, माप(jfs_inode->i_dquot));
#पूर्ण_अगर
	वापस &jfs_inode->vfs_inode;
पूर्ण

अटल व्योम jfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(jfs_inode_cachep, JFS_IP(inode));
पूर्ण

अटल पूर्णांक jfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(dentry->d_sb);
	s64 maxinodes;
	काष्ठा inomap *imap = JFS_IP(sbi->ipimap)->i_imap;

	jfs_info("In jfs_statfs");
	buf->f_type = JFS_SUPER_MAGIC;
	buf->f_bsize = sbi->bsize;
	buf->f_blocks = sbi->bmap->db_mapsize;
	buf->f_bमुक्त = sbi->bmap->db_nमुक्त;
	buf->f_bavail = sbi->bmap->db_nमुक्त;
	/*
	 * If we really वापस the number of allocated & मुक्त inodes, some
	 * applications will fail because they won't see enough मुक्त inodes.
	 * We'll try to calculate some guess as to how many inodes we can
	 * really allocate
	 *
	 * buf->f_files = atomic_पढ़ो(&imap->im_numinos);
	 * buf->f_fमुक्त = atomic_पढ़ो(&imap->im_numमुक्त);
	 */
	maxinodes = min((s64) atomic_पढ़ो(&imap->im_numinos) +
			((sbi->bmap->db_nमुक्त >> imap->im_l2nbperiext)
			 << L2INOSPEREXT), (s64) 0xffffffffLL);
	buf->f_files = maxinodes;
	buf->f_fमुक्त = maxinodes - (atomic_पढ़ो(&imap->im_numinos) -
				    atomic_पढ़ो(&imap->im_numमुक्त));
	buf->f_fsid.val[0] = crc32_le(0, (अक्षर *)&sbi->uuid,
				      माप(sbi->uuid)/2);
	buf->f_fsid.val[1] = crc32_le(0,
				      (अक्षर *)&sbi->uuid + माप(sbi->uuid)/2,
				      माप(sbi->uuid)/2);

	buf->f_namelen = JFS_NAME_MAX;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल पूर्णांक jfs_quota_off(काष्ठा super_block *sb, पूर्णांक type);
अटल पूर्णांक jfs_quota_on(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
			स्थिर काष्ठा path *path);

अटल व्योम jfs_quota_off_umount(काष्ठा super_block *sb)
अणु
	पूर्णांक type;

	क्रम (type = 0; type < MAXQUOTAS; type++)
		jfs_quota_off(sb, type);
पूर्ण

अटल स्थिर काष्ठा quotactl_ops jfs_quotactl_ops = अणु
	.quota_on	= jfs_quota_on,
	.quota_off	= jfs_quota_off,
	.quota_sync	= dquot_quota_sync,
	.get_state	= dquot_get_state,
	.set_info	= dquot_set_dqinfo,
	.get_dqblk	= dquot_get_dqblk,
	.set_dqblk	= dquot_set_dqblk,
	.get_nextdqblk	= dquot_get_next_dqblk,
पूर्ण;
#अन्यथा
अटल अंतरभूत व्योम jfs_quota_off_umount(काष्ठा super_block *sb)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम jfs_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	पूर्णांक rc;

	jfs_info("In jfs_put_super");

	jfs_quota_off_umount(sb);

	rc = jfs_umount(sb);
	अगर (rc)
		jfs_err("jfs_umount failed with return code %d", rc);

	unload_nls(sbi->nls_tab);

	truncate_inode_pages(sbi->direct_inode->i_mapping, 0);
	iput(sbi->direct_inode);

	kमुक्त(sbi);
पूर्ण

क्रमागत अणु
	Opt_पूर्णांकegrity, Opt_noपूर्णांकegrity, Opt_ioअक्षरset, Opt_resize,
	Opt_resize_nosize, Opt_errors, Opt_ignore, Opt_err, Opt_quota,
	Opt_usrquota, Opt_grpquota, Opt_uid, Opt_gid, Opt_umask,
	Opt_discard, Opt_nodiscard, Opt_discard_minblk
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_पूर्णांकegrity, "integrity"पूर्ण,
	अणुOpt_noपूर्णांकegrity, "nointegrity"पूर्ण,
	अणुOpt_ioअक्षरset, "iocharset=%s"पूर्ण,
	अणुOpt_resize, "resize=%u"पूर्ण,
	अणुOpt_resize_nosize, "resize"पूर्ण,
	अणुOpt_errors, "errors=%s"पूर्ण,
	अणुOpt_ignore, "noquota"पूर्ण,
	अणुOpt_quota, "quota"पूर्ण,
	अणुOpt_usrquota, "usrquota"पूर्ण,
	अणुOpt_grpquota, "grpquota"पूर्ण,
	अणुOpt_uid, "uid=%u"पूर्ण,
	अणुOpt_gid, "gid=%u"पूर्ण,
	अणुOpt_umask, "umask=%u"पूर्ण,
	अणुOpt_discard, "discard"पूर्ण,
	अणुOpt_nodiscard, "nodiscard"पूर्ण,
	अणुOpt_discard_minblk, "discard=%u"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक parse_options(अक्षर *options, काष्ठा super_block *sb, s64 *newLVSize,
			 पूर्णांक *flag)
अणु
	व्योम *nls_map = (व्योम *)-1;	/* -1: no change;  शून्य: none */
	अक्षर *p;
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);

	*newLVSize = 0;

	अगर (!options)
		वापस 1;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		substring_t args[MAX_OPT_ARGS];
		पूर्णांक token;
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_पूर्णांकegrity:
			*flag &= ~JFS_NOINTEGRITY;
			अवरोध;
		हाल Opt_noपूर्णांकegrity:
			*flag |= JFS_NOINTEGRITY;
			अवरोध;
		हाल Opt_ignore:
			/* Silently ignore the quota options */
			/* Don't करो anything ;-) */
			अवरोध;
		हाल Opt_ioअक्षरset:
			अगर (nls_map && nls_map != (व्योम *) -1)
				unload_nls(nls_map);
			अगर (!म_भेद(args[0].from, "none"))
				nls_map = शून्य;
			अन्यथा अणु
				nls_map = load_nls(args[0].from);
				अगर (!nls_map) अणु
					pr_err("JFS: charset not found\n");
					जाओ cleanup;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल Opt_resize:
		अणु
			अक्षर *resize = args[0].from;
			पूर्णांक rc = kम_से_दीर्घl(resize, 0, newLVSize);

			अगर (rc)
				जाओ cleanup;
			अवरोध;
		पूर्ण
		हाल Opt_resize_nosize:
		अणु
			*newLVSize = i_size_पढ़ो(sb->s_bdev->bd_inode) >>
				sb->s_blocksize_bits;
			अगर (*newLVSize == 0)
				pr_err("JFS: Cannot determine volume size\n");
			अवरोध;
		पूर्ण
		हाल Opt_errors:
		अणु
			अक्षर *errors = args[0].from;
			अगर (!errors || !*errors)
				जाओ cleanup;
			अगर (!म_भेद(errors, "continue")) अणु
				*flag &= ~JFS_ERR_REMOUNT_RO;
				*flag &= ~JFS_ERR_PANIC;
				*flag |= JFS_ERR_CONTINUE;
			पूर्ण अन्यथा अगर (!म_भेद(errors, "remount-ro")) अणु
				*flag &= ~JFS_ERR_CONTINUE;
				*flag &= ~JFS_ERR_PANIC;
				*flag |= JFS_ERR_REMOUNT_RO;
			पूर्ण अन्यथा अगर (!म_भेद(errors, "panic")) अणु
				*flag &= ~JFS_ERR_CONTINUE;
				*flag &= ~JFS_ERR_REMOUNT_RO;
				*flag |= JFS_ERR_PANIC;
			पूर्ण अन्यथा अणु
				pr_err("JFS: %s is an invalid error handler\n",
				       errors);
				जाओ cleanup;
			पूर्ण
			अवरोध;
		पूर्ण

#अगर_घोषित CONFIG_QUOTA
		हाल Opt_quota:
		हाल Opt_usrquota:
			*flag |= JFS_USRQUOTA;
			अवरोध;
		हाल Opt_grpquota:
			*flag |= JFS_GRPQUOTA;
			अवरोध;
#अन्यथा
		हाल Opt_usrquota:
		हाल Opt_grpquota:
		हाल Opt_quota:
			pr_err("JFS: quota operations not supported\n");
			अवरोध;
#पूर्ण_अगर
		हाल Opt_uid:
		अणु
			अक्षर *uid = args[0].from;
			uid_t val;
			पूर्णांक rc = kstrtouपूर्णांक(uid, 0, &val);

			अगर (rc)
				जाओ cleanup;
			sbi->uid = make_kuid(current_user_ns(), val);
			अगर (!uid_valid(sbi->uid))
				जाओ cleanup;
			अवरोध;
		पूर्ण

		हाल Opt_gid:
		अणु
			अक्षर *gid = args[0].from;
			gid_t val;
			पूर्णांक rc = kstrtouपूर्णांक(gid, 0, &val);

			अगर (rc)
				जाओ cleanup;
			sbi->gid = make_kgid(current_user_ns(), val);
			अगर (!gid_valid(sbi->gid))
				जाओ cleanup;
			अवरोध;
		पूर्ण

		हाल Opt_umask:
		अणु
			अक्षर *umask = args[0].from;
			पूर्णांक rc = kstrtouपूर्णांक(umask, 8, &sbi->umask);

			अगर (rc)
				जाओ cleanup;
			अगर (sbi->umask & ~0777) अणु
				pr_err("JFS: Invalid value of umask\n");
				जाओ cleanup;
			पूर्ण
			अवरोध;
		पूर्ण

		हाल Opt_discard:
		अणु
			काष्ठा request_queue *q = bdev_get_queue(sb->s_bdev);
			/* अगर set to 1, even copying files will cause
			 * trimming :O
			 * -> user has more control over the online trimming
			 */
			sbi->minblks_trim = 64;
			अगर (blk_queue_discard(q))
				*flag |= JFS_DISCARD;
			अन्यथा
				pr_err("JFS: discard option not supported on device\n");
			अवरोध;
		पूर्ण

		हाल Opt_nodiscard:
			*flag &= ~JFS_DISCARD;
			अवरोध;

		हाल Opt_discard_minblk:
		अणु
			काष्ठा request_queue *q = bdev_get_queue(sb->s_bdev);
			अक्षर *minblks_trim = args[0].from;
			पूर्णांक rc;
			अगर (blk_queue_discard(q)) अणु
				*flag |= JFS_DISCARD;
				rc = kstrtouपूर्णांक(minblks_trim, 0,
						&sbi->minblks_trim);
				अगर (rc)
					जाओ cleanup;
			पूर्ण अन्यथा
				pr_err("JFS: discard option not supported on device\n");
			अवरोध;
		पूर्ण

		शेष:
			prपूर्णांकk("jfs: Unrecognized mount option \"%s\" or missing value\n",
			       p);
			जाओ cleanup;
		पूर्ण
	पूर्ण

	अगर (nls_map != (व्योम *) -1) अणु
		/* Discard old (अगर remount) */
		unload_nls(sbi->nls_tab);
		sbi->nls_tab = nls_map;
	पूर्ण
	वापस 1;

cleanup:
	अगर (nls_map && nls_map != (व्योम *) -1)
		unload_nls(nls_map);
	वापस 0;
पूर्ण

अटल पूर्णांक jfs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	s64 newLVSize = 0;
	पूर्णांक rc = 0;
	पूर्णांक flag = JFS_SBI(sb)->flag;
	पूर्णांक ret;

	sync_fileप्रणाली(sb);
	अगर (!parse_options(data, sb, &newLVSize, &flag))
		वापस -EINVAL;

	अगर (newLVSize) अणु
		अगर (sb_rकरोnly(sb)) अणु
			pr_err("JFS: resize requires volume to be mounted read-write\n");
			वापस -EROFS;
		पूर्ण
		rc = jfs_extendfs(sb, newLVSize, 0);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (sb_rकरोnly(sb) && !(*flags & SB_RDONLY)) अणु
		/*
		 * Invalidate any previously पढ़ो metadata.  fsck may have
		 * changed the on-disk data since we mounted r/o
		 */
		truncate_inode_pages(JFS_SBI(sb)->direct_inode->i_mapping, 0);

		JFS_SBI(sb)->flag = flag;
		ret = jfs_mount_rw(sb, 1);

		/* mark the fs r/w क्रम quota activity */
		sb->s_flags &= ~SB_RDONLY;

		dquot_resume(sb, -1);
		वापस ret;
	पूर्ण
	अगर (!sb_rकरोnly(sb) && (*flags & SB_RDONLY)) अणु
		rc = dquot_suspend(sb, -1);
		अगर (rc < 0)
			वापस rc;
		rc = jfs_umount_rw(sb);
		JFS_SBI(sb)->flag = flag;
		वापस rc;
	पूर्ण
	अगर ((JFS_SBI(sb)->flag & JFS_NOINTEGRITY) != (flag & JFS_NOINTEGRITY))
		अगर (!sb_rकरोnly(sb)) अणु
			rc = jfs_umount_rw(sb);
			अगर (rc)
				वापस rc;

			JFS_SBI(sb)->flag = flag;
			ret = jfs_mount_rw(sb, 1);
			वापस ret;
		पूर्ण
	JFS_SBI(sb)->flag = flag;

	वापस 0;
पूर्ण

अटल पूर्णांक jfs_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा jfs_sb_info *sbi;
	काष्ठा inode *inode;
	पूर्णांक rc;
	s64 newLVSize = 0;
	पूर्णांक flag, ret = -EINVAL;

	jfs_info("In jfs_read_super: s_flags=0x%lx", sb->s_flags);

	sbi = kzalloc(माप(काष्ठा jfs_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;

	sb->s_fs_info = sbi;
	sb->s_max_links = JFS_LINK_MAX;
	sb->s_समय_min = 0;
	sb->s_समय_max = U32_MAX;
	sbi->sb = sb;
	sbi->uid = INVALID_UID;
	sbi->gid = INVALID_GID;
	sbi->umask = -1;

	/* initialize the mount flag and determine the शेष error handler */
	flag = JFS_ERR_REMOUNT_RO;

	अगर (!parse_options((अक्षर *) data, sb, &newLVSize, &flag))
		जाओ out_kमुक्त;
	sbi->flag = flag;

#अगर_घोषित CONFIG_JFS_POSIX_ACL
	sb->s_flags |= SB_POSIXACL;
#पूर्ण_अगर

	अगर (newLVSize) अणु
		pr_err("resize option for remount only\n");
		जाओ out_kमुक्त;
	पूर्ण

	/*
	 * Initialize blocksize to 4K.
	 */
	sb_set_blocksize(sb, PSIZE);

	/*
	 * Set method vectors.
	 */
	sb->s_op = &jfs_super_operations;
	sb->s_export_op = &jfs_export_operations;
	sb->s_xattr = jfs_xattr_handlers;
#अगर_घोषित CONFIG_QUOTA
	sb->dq_op = &dquot_operations;
	sb->s_qcop = &jfs_quotactl_ops;
	sb->s_quota_types = QTYPE_MASK_USR | QTYPE_MASK_GRP;
#पूर्ण_अगर

	/*
	 * Initialize direct-mapping inode/address-space
	 */
	inode = new_inode(sb);
	अगर (inode == शून्य) अणु
		ret = -ENOMEM;
		जाओ out_unload;
	पूर्ण
	inode->i_size = i_size_पढ़ो(sb->s_bdev->bd_inode);
	inode->i_mapping->a_ops = &jfs_metapage_aops;
	inode_fake_hash(inode);
	mapping_set_gfp_mask(inode->i_mapping, GFP_NOFS);

	sbi->direct_inode = inode;

	rc = jfs_mount(sb);
	अगर (rc) अणु
		अगर (!silent)
			jfs_err("jfs_mount failed w/return code = %d", rc);
		जाओ out_mount_failed;
	पूर्ण
	अगर (sb_rकरोnly(sb))
		sbi->log = शून्य;
	अन्यथा अणु
		rc = jfs_mount_rw(sb, 0);
		अगर (rc) अणु
			अगर (!silent) अणु
				jfs_err("jfs_mount_rw failed, return code = %d",
					rc);
			पूर्ण
			जाओ out_no_rw;
		पूर्ण
	पूर्ण

	sb->s_magic = JFS_SUPER_MAGIC;

	अगर (sbi->mntflag & JFS_OS2)
		sb->s_d_op = &jfs_ci_dentry_operations;

	inode = jfs_iget(sb, ROOT_I);
	अगर (IS_ERR(inode)) अणु
		ret = PTR_ERR(inode);
		जाओ out_no_rw;
	पूर्ण
	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root)
		जाओ out_no_root;

	/* logical blocks are represented by 40 bits in pxd_t, etc.
	 * and page cache is indexed by दीर्घ
	 */
	sb->s_maxbytes = min(((loff_t)sb->s_blocksize) << 40, MAX_LFS_खाताSIZE);
	sb->s_समय_gran = 1;
	वापस 0;

out_no_root:
	jfs_err("jfs_read_super: get root dentry failed");

out_no_rw:
	rc = jfs_umount(sb);
	अगर (rc)
		jfs_err("jfs_umount failed with return code %d", rc);
out_mount_failed:
	filemap_ग_लिखो_and_रुको(sbi->direct_inode->i_mapping);
	truncate_inode_pages(sbi->direct_inode->i_mapping, 0);
	make_bad_inode(sbi->direct_inode);
	iput(sbi->direct_inode);
	sbi->direct_inode = शून्य;
out_unload:
	unload_nls(sbi->nls_tab);
out_kमुक्त:
	kमुक्त(sbi);
	वापस ret;
पूर्ण

अटल पूर्णांक jfs_मुक्तze(काष्ठा super_block *sb)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	काष्ठा jfs_log *log = sbi->log;
	पूर्णांक rc = 0;

	अगर (!sb_rकरोnly(sb)) अणु
		txQuiesce(sb);
		rc = lmLogShutकरोwn(log);
		अगर (rc) अणु
			jfs_error(sb, "lmLogShutdown failed\n");

			/* let operations fail rather than hang */
			txResume(sb);

			वापस rc;
		पूर्ण
		rc = updateSuper(sb, FM_CLEAN);
		अगर (rc) अणु
			jfs_err("jfs_freeze: updateSuper failed");
			/*
			 * Don't fail here. Everything succeeded except
			 * marking the superblock clean, so there's really
			 * no harm in leaving it frozen क्रम now.
			 */
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक jfs_unमुक्तze(काष्ठा super_block *sb)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	काष्ठा jfs_log *log = sbi->log;
	पूर्णांक rc = 0;

	अगर (!sb_rकरोnly(sb)) अणु
		rc = updateSuper(sb, FM_MOUNT);
		अगर (rc) अणु
			jfs_error(sb, "updateSuper failed\n");
			जाओ out;
		पूर्ण
		rc = lmLogInit(log);
		अगर (rc)
			jfs_error(sb, "lmLogInit failed\n");
out:
		txResume(sb);
	पूर्ण
	वापस rc;
पूर्ण

अटल काष्ठा dentry *jfs_करो_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, jfs_fill_super);
पूर्ण

अटल पूर्णांक jfs_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	काष्ठा jfs_log *log = JFS_SBI(sb)->log;

	/* log == शून्य indicates पढ़ो-only mount */
	अगर (log) अणु
		/*
		 * Write quota काष्ठाures to quota file, sync_blockdev() will
		 * ग_लिखो them to disk later
		 */
		dquot_ग_लिखोback_dquots(sb, -1);
		jfs_flush_journal(log, रुको);
		jfs_syncpt(log, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jfs_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(root->d_sb);

	अगर (uid_valid(sbi->uid))
		seq_म_लिखो(seq, ",uid=%d", from_kuid(&init_user_ns, sbi->uid));
	अगर (gid_valid(sbi->gid))
		seq_म_लिखो(seq, ",gid=%d", from_kgid(&init_user_ns, sbi->gid));
	अगर (sbi->umask != -1)
		seq_म_लिखो(seq, ",umask=%03o", sbi->umask);
	अगर (sbi->flag & JFS_NOINTEGRITY)
		seq_माला_दो(seq, ",nointegrity");
	अगर (sbi->flag & JFS_DISCARD)
		seq_म_लिखो(seq, ",discard=%u", sbi->minblks_trim);
	अगर (sbi->nls_tab)
		seq_म_लिखो(seq, ",iocharset=%s", sbi->nls_tab->अक्षरset);
	अगर (sbi->flag & JFS_ERR_CONTINUE)
		seq_म_लिखो(seq, ",errors=continue");
	अगर (sbi->flag & JFS_ERR_PANIC)
		seq_म_लिखो(seq, ",errors=panic");

#अगर_घोषित CONFIG_QUOTA
	अगर (sbi->flag & JFS_USRQUOTA)
		seq_माला_दो(seq, ",usrquota");

	अगर (sbi->flag & JFS_GRPQUOTA)
		seq_माला_दो(seq, ",grpquota");
#पूर्ण_अगर

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_QUOTA

/* Read data from quotafile - aव्योम pagecache and such because we cannot afक्रमd
 * acquiring the locks... As quota files are never truncated and quota code
 * itself serializes the operations (and no one अन्यथा should touch the files)
 * we करोn't have to be afraid of races */
अटल sमाप_प्रकार jfs_quota_पढ़ो(काष्ठा super_block *sb, पूर्णांक type, अक्षर *data,
			      माप_प्रकार len, loff_t off)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	sector_t blk = off >> sb->s_blocksize_bits;
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
		पंचांगp_bh.b_size = i_blocksize(inode);
		err = jfs_get_block(inode, blk, &पंचांगp_bh, 0);
		अगर (err)
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
अटल sमाप_प्रकार jfs_quota_ग_लिखो(काष्ठा super_block *sb, पूर्णांक type,
			       स्थिर अक्षर *data, माप_प्रकार len, loff_t off)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	sector_t blk = off >> sb->s_blocksize_bits;
	पूर्णांक err = 0;
	पूर्णांक offset = off & (sb->s_blocksize - 1);
	पूर्णांक tocopy;
	माप_प्रकार toग_लिखो = len;
	काष्ठा buffer_head पंचांगp_bh;
	काष्ठा buffer_head *bh;

	inode_lock(inode);
	जबतक (toग_लिखो > 0) अणु
		tocopy = sb->s_blocksize - offset < toग_लिखो ?
				sb->s_blocksize - offset : toग_लिखो;

		पंचांगp_bh.b_state = 0;
		पंचांगp_bh.b_size = i_blocksize(inode);
		err = jfs_get_block(inode, blk, &पंचांगp_bh, 1);
		अगर (err)
			जाओ out;
		अगर (offset || tocopy != sb->s_blocksize)
			bh = sb_bपढ़ो(sb, पंचांगp_bh.b_blocknr);
		अन्यथा
			bh = sb_getblk(sb, पंचांगp_bh.b_blocknr);
		अगर (!bh) अणु
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
	अगर (len == toग_लिखो) अणु
		inode_unlock(inode);
		वापस err;
	पूर्ण
	अगर (inode->i_size < off+len-toग_लिखो)
		i_size_ग_लिखो(inode, off+len-toग_लिखो);
	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);
	inode_unlock(inode);
	वापस len - toग_लिखो;
पूर्ण

अटल काष्ठा dquot **jfs_get_dquots(काष्ठा inode *inode)
अणु
	वापस JFS_IP(inode)->i_dquot;
पूर्ण

अटल पूर्णांक jfs_quota_on(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
			स्थिर काष्ठा path *path)
अणु
	पूर्णांक err;
	काष्ठा inode *inode;

	err = dquot_quota_on(sb, type, क्रमmat_id, path);
	अगर (err)
		वापस err;

	inode = d_inode(path->dentry);
	inode_lock(inode);
	JFS_IP(inode)->mode2 |= JFS_NOATIME_FL | JFS_IMMUTABLE_FL;
	inode_set_flags(inode, S_NOATIME | S_IMMUTABLE,
			S_NOATIME | S_IMMUTABLE);
	inode_unlock(inode);
	mark_inode_dirty(inode);

	वापस 0;
पूर्ण

अटल पूर्णांक jfs_quota_off(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	पूर्णांक err;

	अगर (!inode || !igrab(inode))
		जाओ out;

	err = dquot_quota_off(sb, type);
	अगर (err)
		जाओ out_put;

	inode_lock(inode);
	JFS_IP(inode)->mode2 &= ~(JFS_NOATIME_FL | JFS_IMMUTABLE_FL);
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

अटल स्थिर काष्ठा super_operations jfs_super_operations = अणु
	.alloc_inode	= jfs_alloc_inode,
	.मुक्त_inode	= jfs_मुक्त_inode,
	.dirty_inode	= jfs_dirty_inode,
	.ग_लिखो_inode	= jfs_ग_लिखो_inode,
	.evict_inode	= jfs_evict_inode,
	.put_super	= jfs_put_super,
	.sync_fs	= jfs_sync_fs,
	.मुक्तze_fs	= jfs_मुक्तze,
	.unमुक्तze_fs	= jfs_unमुक्तze,
	.statfs		= jfs_statfs,
	.remount_fs	= jfs_remount,
	.show_options	= jfs_show_options,
#अगर_घोषित CONFIG_QUOTA
	.quota_पढ़ो	= jfs_quota_पढ़ो,
	.quota_ग_लिखो	= jfs_quota_ग_लिखो,
	.get_dquots	= jfs_get_dquots,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा export_operations jfs_export_operations = अणु
	.fh_to_dentry	= jfs_fh_to_dentry,
	.fh_to_parent	= jfs_fh_to_parent,
	.get_parent	= jfs_get_parent,
पूर्ण;

अटल काष्ठा file_प्रणाली_type jfs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "jfs",
	.mount		= jfs_करो_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("jfs");

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा jfs_inode_info *jfs_ip = (काष्ठा jfs_inode_info *) foo;

	स_रखो(jfs_ip, 0, माप(काष्ठा jfs_inode_info));
	INIT_LIST_HEAD(&jfs_ip->anon_inode_list);
	init_rwsem(&jfs_ip->rdwrlock);
	mutex_init(&jfs_ip->commit_mutex);
	init_rwsem(&jfs_ip->xattr_sem);
	spin_lock_init(&jfs_ip->ag_lock);
	jfs_ip->active_ag = -1;
	inode_init_once(&jfs_ip->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_jfs_fs(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक rc;

	jfs_inode_cachep =
	    kmem_cache_create_usercopy("jfs_ip", माप(काष्ठा jfs_inode_info),
			0, SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD|SLAB_ACCOUNT,
			दुरत्व(काष्ठा jfs_inode_info, i_अंतरभूत), IDATASIZE,
			init_once);
	अगर (jfs_inode_cachep == शून्य)
		वापस -ENOMEM;

	/*
	 * Metapage initialization
	 */
	rc = metapage_init();
	अगर (rc) अणु
		jfs_err("metapage_init failed w/rc = %d", rc);
		जाओ मुक्त_slab;
	पूर्ण

	/*
	 * Transaction Manager initialization
	 */
	rc = txInit();
	अगर (rc) अणु
		jfs_err("txInit failed w/rc = %d", rc);
		जाओ मुक्त_metapage;
	पूर्ण

	/*
	 * I/O completion thपढ़ो (endio)
	 */
	jfsIOthपढ़ो = kthपढ़ो_run(jfsIOWait, शून्य, "jfsIO");
	अगर (IS_ERR(jfsIOthपढ़ो)) अणु
		rc = PTR_ERR(jfsIOthपढ़ो);
		jfs_err("init_jfs_fs: fork failed w/rc = %d", rc);
		जाओ end_txmngr;
	पूर्ण

	अगर (commit_thपढ़ोs < 1)
		commit_thपढ़ोs = num_online_cpus();
	अगर (commit_thपढ़ोs > MAX_COMMIT_THREADS)
		commit_thपढ़ोs = MAX_COMMIT_THREADS;

	क्रम (i = 0; i < commit_thपढ़ोs; i++) अणु
		jfsCommitThपढ़ो[i] = kthपढ़ो_run(jfs_lazycommit, शून्य,
						 "jfsCommit");
		अगर (IS_ERR(jfsCommitThपढ़ो[i])) अणु
			rc = PTR_ERR(jfsCommitThपढ़ो[i]);
			jfs_err("init_jfs_fs: fork failed w/rc = %d", rc);
			commit_thपढ़ोs = i;
			जाओ समाप्त_committask;
		पूर्ण
	पूर्ण

	jfsSyncThपढ़ो = kthपढ़ो_run(jfs_sync, शून्य, "jfsSync");
	अगर (IS_ERR(jfsSyncThपढ़ो)) अणु
		rc = PTR_ERR(jfsSyncThपढ़ो);
		jfs_err("init_jfs_fs: fork failed w/rc = %d", rc);
		जाओ समाप्त_committask;
	पूर्ण

#अगर_घोषित PROC_FS_JFS
	jfs_proc_init();
#पूर्ण_अगर

	rc = रेजिस्टर_fileप्रणाली(&jfs_fs_type);
	अगर (!rc)
		वापस 0;

#अगर_घोषित PROC_FS_JFS
	jfs_proc_clean();
#पूर्ण_अगर
	kthपढ़ो_stop(jfsSyncThपढ़ो);
समाप्त_committask:
	क्रम (i = 0; i < commit_thपढ़ोs; i++)
		kthपढ़ो_stop(jfsCommitThपढ़ो[i]);
	kthपढ़ो_stop(jfsIOthपढ़ो);
end_txmngr:
	txExit();
मुक्त_metapage:
	metapage_निकास();
मुक्त_slab:
	kmem_cache_destroy(jfs_inode_cachep);
	वापस rc;
पूर्ण

अटल व्योम __निकास निकास_jfs_fs(व्योम)
अणु
	पूर्णांक i;

	jfs_info("exit_jfs_fs called");

	txExit();
	metapage_निकास();

	kthपढ़ो_stop(jfsIOthपढ़ो);
	क्रम (i = 0; i < commit_thपढ़ोs; i++)
		kthपढ़ो_stop(jfsCommitThपढ़ो[i]);
	kthपढ़ो_stop(jfsSyncThपढ़ो);
#अगर_घोषित PROC_FS_JFS
	jfs_proc_clean();
#पूर्ण_अगर
	unरेजिस्टर_fileप्रणाली(&jfs_fs_type);

	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(jfs_inode_cachep);
पूर्ण

module_init(init_jfs_fs)
module_निकास(निकास_jfs_fs)
