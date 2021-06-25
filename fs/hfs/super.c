<शैली गुरु>
/*
 *  linux/fs/hfs/super.c
 *
 * Copyright (C) 1995-1997  Paul H. Hargrove
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 * This file may be distributed under the terms of the GNU General Public License.
 *
 * This file contains hfs_पढ़ो_super(), some of the super_ops and
 * init_hfs_fs() and निकास_hfs_fs().  The reमुख्यing super_ops are in
 * inode.c since they deal with inodes.
 *
 * Based on the minix file प्रणाली code, (C) 1991, 1992 by Linus Torvalds
 */

#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/mount.h>
#समावेश <linux/init.h>
#समावेश <linux/nls.h>
#समावेश <linux/parser.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/vfs.h>

#समावेश "hfs_fs.h"
#समावेश "btree.h"

अटल काष्ठा kmem_cache *hfs_inode_cachep;

MODULE_LICENSE("GPL");

अटल पूर्णांक hfs_sync_fs(काष्ठा super_block *sb, पूर्णांक रुको)
अणु
	hfs_mdb_commit(sb);
	वापस 0;
पूर्ण

/*
 * hfs_put_super()
 *
 * This is the put_super() entry in the super_operations काष्ठाure क्रम
 * HFS fileप्रणालीs.  The purpose is to release the resources
 * associated with the superblock sb.
 */
अटल व्योम hfs_put_super(काष्ठा super_block *sb)
अणु
	cancel_delayed_work_sync(&HFS_SB(sb)->mdb_work);
	hfs_mdb_बंद(sb);
	/* release the MDB's resources */
	hfs_mdb_put(sb);
पूर्ण

अटल व्योम flush_mdb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hfs_sb_info *sbi;
	काष्ठा super_block *sb;

	sbi = container_of(work, काष्ठा hfs_sb_info, mdb_work.work);
	sb = sbi->sb;

	spin_lock(&sbi->work_lock);
	sbi->work_queued = 0;
	spin_unlock(&sbi->work_lock);

	hfs_mdb_commit(sb);
पूर्ण

व्योम hfs_mark_mdb_dirty(काष्ठा super_block *sb)
अणु
	काष्ठा hfs_sb_info *sbi = HFS_SB(sb);
	अचिन्हित दीर्घ delay;

	अगर (sb_rकरोnly(sb))
		वापस;

	spin_lock(&sbi->work_lock);
	अगर (!sbi->work_queued) अणु
		delay = msecs_to_jअगरfies(dirty_ग_लिखोback_पूर्णांकerval * 10);
		queue_delayed_work(प्रणाली_दीर्घ_wq, &sbi->mdb_work, delay);
		sbi->work_queued = 1;
	पूर्ण
	spin_unlock(&sbi->work_lock);
पूर्ण

/*
 * hfs_statfs()
 *
 * This is the statfs() entry in the super_operations काष्ठाure क्रम
 * HFS fileप्रणालीs.  The purpose is to वापस various data about the
 * fileप्रणाली.
 *
 * changed f_files/f_fमुक्त to reflect the fs_ablock/मुक्त_ablocks.
 */
अटल पूर्णांक hfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type = HFS_SUPER_MAGIC;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = (u32)HFS_SB(sb)->fs_ablocks * HFS_SB(sb)->fs_भाग;
	buf->f_bमुक्त = (u32)HFS_SB(sb)->मुक्त_ablocks * HFS_SB(sb)->fs_भाग;
	buf->f_bavail = buf->f_bमुक्त;
	buf->f_files = HFS_SB(sb)->fs_ablocks;
	buf->f_fमुक्त = HFS_SB(sb)->मुक्त_ablocks;
	buf->f_fsid = u64_to_fsid(id);
	buf->f_namelen = HFS_NAMELEN;

	वापस 0;
पूर्ण

अटल पूर्णांक hfs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	sync_fileप्रणाली(sb);
	*flags |= SB_NOसूचीATIME;
	अगर ((bool)(*flags & SB_RDONLY) == sb_rकरोnly(sb))
		वापस 0;
	अगर (!(*flags & SB_RDONLY)) अणु
		अगर (!(HFS_SB(sb)->mdb->drAtrb & cpu_to_be16(HFS_SB_ATTRIB_UNMNT))) अणु
			pr_warn("filesystem was not cleanly unmounted, running fsck.hfs is recommended.  leaving read-only.\n");
			sb->s_flags |= SB_RDONLY;
			*flags |= SB_RDONLY;
		पूर्ण अन्यथा अगर (HFS_SB(sb)->mdb->drAtrb & cpu_to_be16(HFS_SB_ATTRIB_SLOCK)) अणु
			pr_warn("filesystem is marked locked, leaving read-only.\n");
			sb->s_flags |= SB_RDONLY;
			*flags |= SB_RDONLY;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hfs_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा hfs_sb_info *sbi = HFS_SB(root->d_sb);

	अगर (sbi->s_creator != cpu_to_be32(0x3f3f3f3f))
		seq_show_option_n(seq, "creator", (अक्षर *)&sbi->s_creator, 4);
	अगर (sbi->s_type != cpu_to_be32(0x3f3f3f3f))
		seq_show_option_n(seq, "type", (अक्षर *)&sbi->s_type, 4);
	seq_म_लिखो(seq, ",uid=%u,gid=%u",
			from_kuid_munged(&init_user_ns, sbi->s_uid),
			from_kgid_munged(&init_user_ns, sbi->s_gid));
	अगर (sbi->s_file_umask != 0133)
		seq_म_लिखो(seq, ",file_umask=%o", sbi->s_file_umask);
	अगर (sbi->s_dir_umask != 0022)
		seq_म_लिखो(seq, ",dir_umask=%o", sbi->s_dir_umask);
	अगर (sbi->part >= 0)
		seq_म_लिखो(seq, ",part=%u", sbi->part);
	अगर (sbi->session >= 0)
		seq_म_लिखो(seq, ",session=%u", sbi->session);
	अगर (sbi->nls_disk)
		seq_म_लिखो(seq, ",codepage=%s", sbi->nls_disk->अक्षरset);
	अगर (sbi->nls_io)
		seq_म_लिखो(seq, ",iocharset=%s", sbi->nls_io->अक्षरset);
	अगर (sbi->s_quiet)
		seq_म_लिखो(seq, ",quiet");
	वापस 0;
पूर्ण

अटल काष्ठा inode *hfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा hfs_inode_info *i;

	i = kmem_cache_alloc(hfs_inode_cachep, GFP_KERNEL);
	वापस i ? &i->vfs_inode : शून्य;
पूर्ण

अटल व्योम hfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(hfs_inode_cachep, HFS_I(inode));
पूर्ण

अटल स्थिर काष्ठा super_operations hfs_super_operations = अणु
	.alloc_inode	= hfs_alloc_inode,
	.मुक्त_inode	= hfs_मुक्त_inode,
	.ग_लिखो_inode	= hfs_ग_लिखो_inode,
	.evict_inode	= hfs_evict_inode,
	.put_super	= hfs_put_super,
	.sync_fs	= hfs_sync_fs,
	.statfs		= hfs_statfs,
	.remount_fs     = hfs_remount,
	.show_options	= hfs_show_options,
पूर्ण;

क्रमागत अणु
	opt_uid, opt_gid, opt_umask, opt_file_umask, opt_dir_umask,
	opt_part, opt_session, opt_type, opt_creator, opt_quiet,
	opt_codepage, opt_ioअक्षरset,
	opt_err
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणु opt_uid, "uid=%u" पूर्ण,
	अणु opt_gid, "gid=%u" पूर्ण,
	अणु opt_umask, "umask=%o" पूर्ण,
	अणु opt_file_umask, "file_umask=%o" पूर्ण,
	अणु opt_dir_umask, "dir_umask=%o" पूर्ण,
	अणु opt_part, "part=%u" पूर्ण,
	अणु opt_session, "session=%u" पूर्ण,
	अणु opt_type, "type=%s" पूर्ण,
	अणु opt_creator, "creator=%s" पूर्ण,
	अणु opt_quiet, "quiet" पूर्ण,
	अणु opt_codepage, "codepage=%s" पूर्ण,
	अणु opt_ioअक्षरset, "iocharset=%s" पूर्ण,
	अणु opt_err, शून्य पूर्ण
पूर्ण;

अटल अंतरभूत पूर्णांक match_fourअक्षर(substring_t *arg, u32 *result)
अणु
	अगर (arg->to - arg->from != 4)
		वापस -EINVAL;
	स_नकल(result, arg->from, 4);
	वापस 0;
पूर्ण

/*
 * parse_options()
 *
 * adapted from linux/fs/msकरोs/inode.c written 1992,93 by Werner Almesberger
 * This function is called by hfs_पढ़ो_super() to parse the mount options.
 */
अटल पूर्णांक parse_options(अक्षर *options, काष्ठा hfs_sb_info *hsb)
अणु
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक पंचांगp, token;

	/* initialize the sb with शेषs */
	hsb->s_uid = current_uid();
	hsb->s_gid = current_gid();
	hsb->s_file_umask = 0133;
	hsb->s_dir_umask = 0022;
	hsb->s_type = hsb->s_creator = cpu_to_be32(0x3f3f3f3f);	/* == '????' */
	hsb->s_quiet = 0;
	hsb->part = -1;
	hsb->session = -1;

	अगर (!options)
		वापस 1;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल opt_uid:
			अगर (match_पूर्णांक(&args[0], &पंचांगp)) अणु
				pr_err("uid requires an argument\n");
				वापस 0;
			पूर्ण
			hsb->s_uid = make_kuid(current_user_ns(), (uid_t)पंचांगp);
			अगर (!uid_valid(hsb->s_uid)) अणु
				pr_err("invalid uid %d\n", पंचांगp);
				वापस 0;
			पूर्ण
			अवरोध;
		हाल opt_gid:
			अगर (match_पूर्णांक(&args[0], &पंचांगp)) अणु
				pr_err("gid requires an argument\n");
				वापस 0;
			पूर्ण
			hsb->s_gid = make_kgid(current_user_ns(), (gid_t)पंचांगp);
			अगर (!gid_valid(hsb->s_gid)) अणु
				pr_err("invalid gid %d\n", पंचांगp);
				वापस 0;
			पूर्ण
			अवरोध;
		हाल opt_umask:
			अगर (match_octal(&args[0], &पंचांगp)) अणु
				pr_err("umask requires a value\n");
				वापस 0;
			पूर्ण
			hsb->s_file_umask = (umode_t)पंचांगp;
			hsb->s_dir_umask = (umode_t)पंचांगp;
			अवरोध;
		हाल opt_file_umask:
			अगर (match_octal(&args[0], &पंचांगp)) अणु
				pr_err("file_umask requires a value\n");
				वापस 0;
			पूर्ण
			hsb->s_file_umask = (umode_t)पंचांगp;
			अवरोध;
		हाल opt_dir_umask:
			अगर (match_octal(&args[0], &पंचांगp)) अणु
				pr_err("dir_umask requires a value\n");
				वापस 0;
			पूर्ण
			hsb->s_dir_umask = (umode_t)पंचांगp;
			अवरोध;
		हाल opt_part:
			अगर (match_पूर्णांक(&args[0], &hsb->part)) अणु
				pr_err("part requires an argument\n");
				वापस 0;
			पूर्ण
			अवरोध;
		हाल opt_session:
			अगर (match_पूर्णांक(&args[0], &hsb->session)) अणु
				pr_err("session requires an argument\n");
				वापस 0;
			पूर्ण
			अवरोध;
		हाल opt_type:
			अगर (match_fourअक्षर(&args[0], &hsb->s_type)) अणु
				pr_err("type requires a 4 character value\n");
				वापस 0;
			पूर्ण
			अवरोध;
		हाल opt_creator:
			अगर (match_fourअक्षर(&args[0], &hsb->s_creator)) अणु
				pr_err("creator requires a 4 character value\n");
				वापस 0;
			पूर्ण
			अवरोध;
		हाल opt_quiet:
			hsb->s_quiet = 1;
			अवरोध;
		हाल opt_codepage:
			अगर (hsb->nls_disk) अणु
				pr_err("unable to change codepage\n");
				वापस 0;
			पूर्ण
			p = match_strdup(&args[0]);
			अगर (p)
				hsb->nls_disk = load_nls(p);
			अगर (!hsb->nls_disk) अणु
				pr_err("unable to load codepage \"%s\"\n", p);
				kमुक्त(p);
				वापस 0;
			पूर्ण
			kमुक्त(p);
			अवरोध;
		हाल opt_ioअक्षरset:
			अगर (hsb->nls_io) अणु
				pr_err("unable to change iocharset\n");
				वापस 0;
			पूर्ण
			p = match_strdup(&args[0]);
			अगर (p)
				hsb->nls_io = load_nls(p);
			अगर (!hsb->nls_io) अणु
				pr_err("unable to load iocharset \"%s\"\n", p);
				kमुक्त(p);
				वापस 0;
			पूर्ण
			kमुक्त(p);
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (hsb->nls_disk && !hsb->nls_io) अणु
		hsb->nls_io = load_nls_शेष();
		अगर (!hsb->nls_io) अणु
			pr_err("unable to load default iocharset\n");
			वापस 0;
		पूर्ण
	पूर्ण
	hsb->s_dir_umask &= 0777;
	hsb->s_file_umask &= 0577;

	वापस 1;
पूर्ण

/*
 * hfs_पढ़ो_super()
 *
 * This is the function that is responsible क्रम mounting an HFS
 * fileप्रणाली.	It perक्रमms all the tasks necessary to get enough data
 * from the disk to पढ़ो the root inode.  This includes parsing the
 * mount options, dealing with Macपूर्णांकosh partitions, पढ़ोing the
 * superblock and the allocation biपंचांगap blocks, calling
 * hfs_btree_init() to get the necessary data about the extents and
 * catalog B-trees and, finally, पढ़ोing the root inode पूर्णांकo memory.
 */
अटल पूर्णांक hfs_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा hfs_sb_info *sbi;
	काष्ठा hfs_find_data fd;
	hfs_cat_rec rec;
	काष्ठा inode *root_inode;
	पूर्णांक res;

	sbi = kzalloc(माप(काष्ठा hfs_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;

	sbi->sb = sb;
	sb->s_fs_info = sbi;
	spin_lock_init(&sbi->work_lock);
	INIT_DELAYED_WORK(&sbi->mdb_work, flush_mdb);

	res = -EINVAL;
	अगर (!parse_options((अक्षर *)data, sbi)) अणु
		pr_err("unable to parse mount options\n");
		जाओ bail;
	पूर्ण

	sb->s_op = &hfs_super_operations;
	sb->s_xattr = hfs_xattr_handlers;
	sb->s_flags |= SB_NOसूचीATIME;
	mutex_init(&sbi->biपंचांगap_lock);

	res = hfs_mdb_get(sb);
	अगर (res) अणु
		अगर (!silent)
			pr_warn("can't find a HFS filesystem on dev %s\n",
				hfs_mdb_name(sb));
		res = -EINVAL;
		जाओ bail;
	पूर्ण

	/* try to get the root inode */
	res = hfs_find_init(HFS_SB(sb)->cat_tree, &fd);
	अगर (res)
		जाओ bail_no_root;
	res = hfs_cat_find_brec(sb, HFS_ROOT_CNID, &fd);
	अगर (!res) अणु
		अगर (fd.entrylength > माप(rec) || fd.entrylength < 0) अणु
			res =  -EIO;
			जाओ bail;
		पूर्ण
		hfs_bnode_पढ़ो(fd.bnode, &rec, fd.entryoffset, fd.entrylength);
	पूर्ण
	अगर (res) अणु
		hfs_find_निकास(&fd);
		जाओ bail_no_root;
	पूर्ण
	res = -EINVAL;
	root_inode = hfs_iget(sb, &fd.search_key->cat, &rec);
	hfs_find_निकास(&fd);
	अगर (!root_inode)
		जाओ bail_no_root;

	sb->s_d_op = &hfs_dentry_operations;
	res = -ENOMEM;
	sb->s_root = d_make_root(root_inode);
	अगर (!sb->s_root)
		जाओ bail_no_root;

	/* everything's okay */
	वापस 0;

bail_no_root:
	pr_err("get root inode failed\n");
bail:
	hfs_mdb_put(sb);
	वापस res;
पूर्ण

अटल काष्ठा dentry *hfs_mount(काष्ठा file_प्रणाली_type *fs_type,
		      पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, hfs_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type hfs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "hfs",
	.mount		= hfs_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("hfs");

अटल व्योम hfs_init_once(व्योम *p)
अणु
	काष्ठा hfs_inode_info *i = p;

	inode_init_once(&i->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_hfs_fs(व्योम)
अणु
	पूर्णांक err;

	hfs_inode_cachep = kmem_cache_create("hfs_inode_cache",
		माप(काष्ठा hfs_inode_info), 0,
		SLAB_HWCACHE_ALIGN|SLAB_ACCOUNT, hfs_init_once);
	अगर (!hfs_inode_cachep)
		वापस -ENOMEM;
	err = रेजिस्टर_fileप्रणाली(&hfs_fs_type);
	अगर (err)
		kmem_cache_destroy(hfs_inode_cachep);
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_hfs_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&hfs_fs_type);

	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(hfs_inode_cachep);
पूर्ण

module_init(init_hfs_fs)
module_निकास(निकास_hfs_fs)
