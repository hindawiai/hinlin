<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/hpfs/super.c
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  mounting, unmounting, error handling
 */

#समावेश "hpfs_fn.h"
#समावेश <linux/module.h>
#समावेश <linux/parser.h>
#समावेश <linux/init.h>
#समावेश <linux/statfs.h>
#समावेश <linux/magic.h>
#समावेश <linux/sched.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>

/* Mark the fileप्रणाली dirty, so that chkdsk checks it when os/2 booted */

अटल व्योम mark_dirty(काष्ठा super_block *s, पूर्णांक remount)
अणु
	अगर (hpfs_sb(s)->sb_chkdsk && (remount || !sb_rकरोnly(s))) अणु
		काष्ठा buffer_head *bh;
		काष्ठा hpfs_spare_block *sb;
		अगर ((sb = hpfs_map_sector(s, 17, &bh, 0))) अणु
			sb->dirty = 1;
			sb->old_wrote = 0;
			mark_buffer_dirty(bh);
			sync_dirty_buffer(bh);
			brअन्यथा(bh);
		पूर्ण
	पूर्ण
पूर्ण

/* Mark the fileप्रणाली clean (mark it dirty क्रम chkdsk अगर chkdsk==2 or अगर there
   were errors) */

अटल व्योम unmark_dirty(काष्ठा super_block *s)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा hpfs_spare_block *sb;
	अगर (sb_rकरोnly(s)) वापस;
	sync_blockdev(s->s_bdev);
	अगर ((sb = hpfs_map_sector(s, 17, &bh, 0))) अणु
		sb->dirty = hpfs_sb(s)->sb_chkdsk > 1 - hpfs_sb(s)->sb_was_error;
		sb->old_wrote = hpfs_sb(s)->sb_chkdsk >= 2 && !hpfs_sb(s)->sb_was_error;
		mark_buffer_dirty(bh);
		sync_dirty_buffer(bh);
		brअन्यथा(bh);
	पूर्ण
पूर्ण

/* Fileप्रणाली error... */
व्योम hpfs_error(काष्ठा super_block *s, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	pr_err("filesystem error: %pV", &vaf);

	बहु_पूर्ण(args);

	अगर (!hpfs_sb(s)->sb_was_error) अणु
		अगर (hpfs_sb(s)->sb_err == 2) अणु
			pr_cont("; crashing the system because you wanted it\n");
			mark_dirty(s, 0);
			panic("HPFS panic");
		पूर्ण अन्यथा अगर (hpfs_sb(s)->sb_err == 1) अणु
			अगर (sb_rकरोnly(s))
				pr_cont("; already mounted read-only\n");
			अन्यथा अणु
				pr_cont("; remounting read-only\n");
				mark_dirty(s, 0);
				s->s_flags |= SB_RDONLY;
			पूर्ण
		पूर्ण अन्यथा अगर (sb_rकरोnly(s))
				pr_cont("; going on - but anything won't be destroyed because it's read-only\n");
		अन्यथा
			pr_cont("; corrupted filesystem mounted read/write - your computer will explode within 20 seconds ... but you wanted it so!\n");
	पूर्ण अन्यथा
		pr_cont("\n");
	hpfs_sb(s)->sb_was_error = 1;
पूर्ण

/* 
 * A little trick to detect cycles in many hpfs काष्ठाures and करोn't let the
 * kernel crash on corrupted fileप्रणाली. When first called, set c2 to 0.
 *
 * BTW. chkdsk करोesn't detect cycles correctly. When I had 2 lost directories
 * nested each in other, chkdsk locked up happilly.
 */

पूर्णांक hpfs_stop_cycles(काष्ठा super_block *s, पूर्णांक key, पूर्णांक *c1, पूर्णांक *c2,
		अक्षर *msg)
अणु
	अगर (*c2 && *c1 == key) अणु
		hpfs_error(s, "cycle detected on key %08x in %s", key, msg);
		वापस 1;
	पूर्ण
	(*c2)++;
	अगर (!((*c2 - 1) & *c2)) *c1 = key;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_sbi(काष्ठा hpfs_sb_info *sbi)
अणु
	kमुक्त(sbi->sb_cp_table);
	kमुक्त(sbi->sb_bmp_dir);
	kमुक्त(sbi);
पूर्ण

अटल व्योम lazy_मुक्त_sbi(काष्ठा rcu_head *rcu)
अणु
	मुक्त_sbi(container_of(rcu, काष्ठा hpfs_sb_info, rcu));
पूर्ण

अटल व्योम hpfs_put_super(काष्ठा super_block *s)
अणु
	hpfs_lock(s);
	unmark_dirty(s);
	hpfs_unlock(s);
	call_rcu(&hpfs_sb(s)->rcu, lazy_मुक्त_sbi);
पूर्ण

अटल अचिन्हित hpfs_count_one_biपंचांगap(काष्ठा super_block *s, secno secno)
अणु
	काष्ठा quad_buffer_head qbh;
	अचिन्हित दीर्घ *bits;
	अचिन्हित count;

	bits = hpfs_map_4sectors(s, secno, &qbh, 0);
	अगर (!bits)
		वापस (अचिन्हित)-1;
	count = biपंचांगap_weight(bits, 2048 * BITS_PER_BYTE);
	hpfs_brअन्यथा4(&qbh);
	वापस count;
पूर्ण

अटल अचिन्हित count_biपंचांगaps(काष्ठा super_block *s)
अणु
	अचिन्हित n, count, n_bands;
	n_bands = (hpfs_sb(s)->sb_fs_size + 0x3fff) >> 14;
	count = 0;
	क्रम (n = 0; n < COUNT_RD_AHEAD; n++) अणु
		hpfs_prefetch_biपंचांगap(s, n);
	पूर्ण
	क्रम (n = 0; n < n_bands; n++) अणु
		अचिन्हित c;
		hpfs_prefetch_biपंचांगap(s, n + COUNT_RD_AHEAD);
		c = hpfs_count_one_biपंचांगap(s, le32_to_cpu(hpfs_sb(s)->sb_bmp_dir[n]));
		अगर (c != (अचिन्हित)-1)
			count += c;
	पूर्ण
	वापस count;
पूर्ण

अचिन्हित hpfs_get_मुक्त_dnodes(काष्ठा super_block *s)
अणु
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	अगर (sbi->sb_n_मुक्त_dnodes == (अचिन्हित)-1) अणु
		अचिन्हित c = hpfs_count_one_biपंचांगap(s, sbi->sb_dmap);
		अगर (c == (अचिन्हित)-1)
			वापस 0;
		sbi->sb_n_मुक्त_dnodes = c;
	पूर्ण
	वापस sbi->sb_n_मुक्त_dnodes;
पूर्ण

अटल पूर्णांक hpfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *s = dentry->d_sb;
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);
	u64 id = huge_encode_dev(s->s_bdev->bd_dev);

	hpfs_lock(s);

	अगर (sbi->sb_n_मुक्त == (अचिन्हित)-1)
		sbi->sb_n_मुक्त = count_biपंचांगaps(s);

	buf->f_type = s->s_magic;
	buf->f_bsize = 512;
	buf->f_blocks = sbi->sb_fs_size;
	buf->f_bमुक्त = sbi->sb_n_मुक्त;
	buf->f_bavail = sbi->sb_n_मुक्त;
	buf->f_files = sbi->sb_dirband_size / 4;
	buf->f_fमुक्त = hpfs_get_मुक्त_dnodes(s);
	buf->f_fsid = u64_to_fsid(id);
	buf->f_namelen = 254;

	hpfs_unlock(s);

	वापस 0;
पूर्ण


दीर्घ hpfs_ioctl(काष्ठा file *file, अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
		हाल FITRIM: अणु
			काष्ठा fstrim_range range;
			secno n_trimmed;
			पूर्णांक r;
			अगर (!capable(CAP_SYS_ADMIN))
				वापस -EPERM;
			अगर (copy_from_user(&range, (काष्ठा fstrim_range __user *)arg, माप(range)))
				वापस -EFAULT;
			r = hpfs_trim_fs(file_inode(file)->i_sb, range.start >> 9, (range.start + range.len) >> 9, (range.minlen + 511) >> 9, &n_trimmed);
			अगर (r)
				वापस r;
			range.len = (u64)n_trimmed << 9;
			अगर (copy_to_user((काष्ठा fstrim_range __user *)arg, &range, माप(range)))
				वापस -EFAULT;
			वापस 0;
		पूर्ण
		शेष: अणु
			वापस -ENOIOCTLCMD;
		पूर्ण
	पूर्ण
पूर्ण


अटल काष्ठा kmem_cache * hpfs_inode_cachep;

अटल काष्ठा inode *hpfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा hpfs_inode_info *ei;
	ei = kmem_cache_alloc(hpfs_inode_cachep, GFP_NOFS);
	अगर (!ei)
		वापस शून्य;
	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम hpfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(hpfs_inode_cachep, hpfs_i(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा hpfs_inode_info *ei = (काष्ठा hpfs_inode_info *) foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक init_inodecache(व्योम)
अणु
	hpfs_inode_cachep = kmem_cache_create("hpfs_inode_cache",
					     माप(काष्ठा hpfs_inode_info),
					     0, (SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					     init_once);
	अगर (hpfs_inode_cachep == शून्य)
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
	kmem_cache_destroy(hpfs_inode_cachep);
पूर्ण

/*
 * A tiny parser क्रम option strings, stolen from करोsfs.
 * Stolen again from पढ़ो-only hpfs.
 * And updated क्रम table-driven option parsing.
 */

क्रमागत अणु
	Opt_help, Opt_uid, Opt_gid, Opt_umask, Opt_हाल_lower, Opt_हाल_asis,
	Opt_check_none, Opt_check_normal, Opt_check_strict,
	Opt_err_cont, Opt_err_ro, Opt_err_panic,
	Opt_eas_no, Opt_eas_ro, Opt_eas_rw,
	Opt_chkdsk_no, Opt_chkdsk_errors, Opt_chkdsk_always,
	Opt_बारhअगरt, Opt_err,
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_help, "help"पूर्ण,
	अणुOpt_uid, "uid=%u"पूर्ण,
	अणुOpt_gid, "gid=%u"पूर्ण,
	अणुOpt_umask, "umask=%o"पूर्ण,
	अणुOpt_हाल_lower, "case=lower"पूर्ण,
	अणुOpt_हाल_asis, "case=asis"पूर्ण,
	अणुOpt_check_none, "check=none"पूर्ण,
	अणुOpt_check_normal, "check=normal"पूर्ण,
	अणुOpt_check_strict, "check=strict"पूर्ण,
	अणुOpt_err_cont, "errors=continue"पूर्ण,
	अणुOpt_err_ro, "errors=remount-ro"पूर्ण,
	अणुOpt_err_panic, "errors=panic"पूर्ण,
	अणुOpt_eas_no, "eas=no"पूर्ण,
	अणुOpt_eas_ro, "eas=ro"पूर्ण,
	अणुOpt_eas_rw, "eas=rw"पूर्ण,
	अणुOpt_chkdsk_no, "chkdsk=no"पूर्ण,
	अणुOpt_chkdsk_errors, "chkdsk=errors"पूर्ण,
	अणुOpt_chkdsk_always, "chkdsk=always"पूर्ण,
	अणुOpt_बारhअगरt, "timeshift=%d"पूर्ण,
	अणुOpt_err, शून्यपूर्ण,
पूर्ण;

अटल पूर्णांक parse_opts(अक्षर *opts, kuid_t *uid, kgid_t *gid, umode_t *umask,
		      पूर्णांक *lowerहाल, पूर्णांक *eas, पूर्णांक *chk, पूर्णांक *errs,
		      पूर्णांक *chkdsk, पूर्णांक *बारhअगरt)
अणु
	अक्षर *p;
	पूर्णांक option;

	अगर (!opts)
		वापस 1;

	/*pr_info("Parsing opts: '%s'\n",opts);*/

	जबतक ((p = strsep(&opts, ",")) != शून्य) अणु
		substring_t args[MAX_OPT_ARGS];
		पूर्णांक token;
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_help:
			वापस 2;
		हाल Opt_uid:
			अगर (match_पूर्णांक(args, &option))
				वापस 0;
			*uid = make_kuid(current_user_ns(), option);
			अगर (!uid_valid(*uid))
				वापस 0;
			अवरोध;
		हाल Opt_gid:
			अगर (match_पूर्णांक(args, &option))
				वापस 0;
			*gid = make_kgid(current_user_ns(), option);
			अगर (!gid_valid(*gid))
				वापस 0;
			अवरोध;
		हाल Opt_umask:
			अगर (match_octal(args, &option))
				वापस 0;
			*umask = option;
			अवरोध;
		हाल Opt_हाल_lower:
			*lowerहाल = 1;
			अवरोध;
		हाल Opt_हाल_asis:
			*lowerहाल = 0;
			अवरोध;
		हाल Opt_check_none:
			*chk = 0;
			अवरोध;
		हाल Opt_check_normal:
			*chk = 1;
			अवरोध;
		हाल Opt_check_strict:
			*chk = 2;
			अवरोध;
		हाल Opt_err_cont:
			*errs = 0;
			अवरोध;
		हाल Opt_err_ro:
			*errs = 1;
			अवरोध;
		हाल Opt_err_panic:
			*errs = 2;
			अवरोध;
		हाल Opt_eas_no:
			*eas = 0;
			अवरोध;
		हाल Opt_eas_ro:
			*eas = 1;
			अवरोध;
		हाल Opt_eas_rw:
			*eas = 2;
			अवरोध;
		हाल Opt_chkdsk_no:
			*chkdsk = 0;
			अवरोध;
		हाल Opt_chkdsk_errors:
			*chkdsk = 1;
			अवरोध;
		हाल Opt_chkdsk_always:
			*chkdsk = 2;
			अवरोध;
		हाल Opt_बारhअगरt:
		अणु
			पूर्णांक m = 1;
			अक्षर *rhs = args[0].from;
			अगर (!rhs || !*rhs)
				वापस 0;
			अगर (*rhs == '-') m = -1;
			अगर (*rhs == '+' || *rhs == '-') rhs++;
			*बारhअगरt = simple_म_से_अदीर्घ(rhs, &rhs, 0) * m;
			अगर (*rhs)
				वापस 0;
			अवरोध;
		पूर्ण
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम hpfs_help(व्योम)
अणु
	pr_info("\न\
HPFS fileप्रणाली options:\न\
      help              करो not mount and display this text\न\
      uid=xxx           set uid of files that करोn't have uid specअगरied in eas\न\
      gid=xxx           set gid of files that करोn't have gid specअगरied in eas\न\
      umask=xxx         set mode of files that करोn't have mode specअगरied in eas\न\
      हाल=lower        lowerहाल all files\न\
      हाल=asis         करो not lowerहाल files (शेष)\न\
      check=none        no fs checks - kernel may crash on corrupted fileप्रणाली\न\
      check=normal      करो some checks - it should not crash (शेष)\न\
      check=strict      करो extra समय-consuming checks, used क्रम debugging\न\
      errors=जारी   जारी on errors\न\
      errors=remount-ro remount पढ़ो-only अगर errors found (शेष)\न\
      errors=panic      panic on errors\न\
      chkdsk=no         करो not mark fs क्रम chkdsking even अगर there were errors\न\
      chkdsk=errors     mark fs dirty अगर errors found (शेष)\न\
      chkdsk=always     always mark fs dirty - used क्रम debugging\न\
      eas=no            ignore extended attributes\न\
      eas=ro            पढ़ो but करो not ग_लिखो extended attributes\न\
      eas=rw            r/w eas => enables chmod, chown, mknod, ln -s (शेष)\न\
      बारhअगरt=nnn	add nnn seconds to file बार\न\
\न");
पूर्ण

अटल पूर्णांक hpfs_remount_fs(काष्ठा super_block *s, पूर्णांक *flags, अक्षर *data)
अणु
	kuid_t uid;
	kgid_t gid;
	umode_t umask;
	पूर्णांक lowerहाल, eas, chk, errs, chkdsk, बारhअगरt;
	पूर्णांक o;
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(s);

	sync_fileप्रणाली(s);

	*flags |= SB_NOATIME;

	hpfs_lock(s);
	uid = sbi->sb_uid; gid = sbi->sb_gid;
	umask = 0777 & ~sbi->sb_mode;
	lowerहाल = sbi->sb_lowerहाल;
	eas = sbi->sb_eas; chk = sbi->sb_chk; chkdsk = sbi->sb_chkdsk;
	errs = sbi->sb_err; बारhअगरt = sbi->sb_बारhअगरt;

	अगर (!(o = parse_opts(data, &uid, &gid, &umask, &lowerहाल,
	    &eas, &chk, &errs, &chkdsk, &बारhअगरt))) अणु
		pr_err("bad mount options.\n");
		जाओ out_err;
	पूर्ण
	अगर (o == 2) अणु
		hpfs_help();
		जाओ out_err;
	पूर्ण
	अगर (बारhअगरt != sbi->sb_बारhअगरt) अणु
		pr_err("timeshift can't be changed using remount.\n");
		जाओ out_err;
	पूर्ण

	unmark_dirty(s);

	sbi->sb_uid = uid; sbi->sb_gid = gid;
	sbi->sb_mode = 0777 & ~umask;
	sbi->sb_lowerहाल = lowerहाल;
	sbi->sb_eas = eas; sbi->sb_chk = chk; sbi->sb_chkdsk = chkdsk;
	sbi->sb_err = errs; sbi->sb_बारhअगरt = बारhअगरt;

	अगर (!(*flags & SB_RDONLY)) mark_dirty(s, 1);

	hpfs_unlock(s);
	वापस 0;

out_err:
	hpfs_unlock(s);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hpfs_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा hpfs_sb_info *sbi = hpfs_sb(root->d_sb);

	seq_म_लिखो(seq, ",uid=%u", from_kuid_munged(&init_user_ns, sbi->sb_uid));
	seq_म_लिखो(seq, ",gid=%u", from_kgid_munged(&init_user_ns, sbi->sb_gid));
	seq_म_लिखो(seq, ",umask=%03o", (~sbi->sb_mode & 0777));
	अगर (sbi->sb_lowerहाल)
		seq_म_लिखो(seq, ",case=lower");
	अगर (!sbi->sb_chk)
		seq_म_लिखो(seq, ",check=none");
	अगर (sbi->sb_chk == 2)
		seq_म_लिखो(seq, ",check=strict");
	अगर (!sbi->sb_err)
		seq_म_लिखो(seq, ",errors=continue");
	अगर (sbi->sb_err == 2)
		seq_म_लिखो(seq, ",errors=panic");
	अगर (!sbi->sb_chkdsk)
		seq_म_लिखो(seq, ",chkdsk=no");
	अगर (sbi->sb_chkdsk == 2)
		seq_म_लिखो(seq, ",chkdsk=always");
	अगर (!sbi->sb_eas)
		seq_म_लिखो(seq, ",eas=no");
	अगर (sbi->sb_eas == 1)
		seq_म_लिखो(seq, ",eas=ro");
	अगर (sbi->sb_बारhअगरt)
		seq_म_लिखो(seq, ",timeshift=%d", sbi->sb_बारhअगरt);
	वापस 0;
पूर्ण

/* Super operations */

अटल स्थिर काष्ठा super_operations hpfs_sops =
अणु
	.alloc_inode	= hpfs_alloc_inode,
	.मुक्त_inode	= hpfs_मुक्त_inode,
	.evict_inode	= hpfs_evict_inode,
	.put_super	= hpfs_put_super,
	.statfs		= hpfs_statfs,
	.remount_fs	= hpfs_remount_fs,
	.show_options	= hpfs_show_options,
पूर्ण;

अटल पूर्णांक hpfs_fill_super(काष्ठा super_block *s, व्योम *options, पूर्णांक silent)
अणु
	काष्ठा buffer_head *bh0, *bh1, *bh2;
	काष्ठा hpfs_boot_block *bootblock;
	काष्ठा hpfs_super_block *superblock;
	काष्ठा hpfs_spare_block *spareblock;
	काष्ठा hpfs_sb_info *sbi;
	काष्ठा inode *root;

	kuid_t uid;
	kgid_t gid;
	umode_t umask;
	पूर्णांक lowerहाल, eas, chk, errs, chkdsk, बारhअगरt;

	dnode_secno root_dno;
	काष्ठा hpfs_dirent *de = शून्य;
	काष्ठा quad_buffer_head qbh;

	पूर्णांक o;

	sbi = kzalloc(माप(*sbi), GFP_KERNEL);
	अगर (!sbi) अणु
		वापस -ENOMEM;
	पूर्ण
	s->s_fs_info = sbi;

	mutex_init(&sbi->hpfs_mutex);
	hpfs_lock(s);

	uid = current_uid();
	gid = current_gid();
	umask = current_umask();
	lowerहाल = 0;
	eas = 2;
	chk = 1;
	errs = 1;
	chkdsk = 1;
	बारhअगरt = 0;

	अगर (!(o = parse_opts(options, &uid, &gid, &umask, &lowerहाल,
	    &eas, &chk, &errs, &chkdsk, &बारhअगरt))) अणु
		pr_err("bad mount options.\n");
		जाओ bail0;
	पूर्ण
	अगर (o==2) अणु
		hpfs_help();
		जाओ bail0;
	पूर्ण

	/*sbi->sb_mounting = 1;*/
	sb_set_blocksize(s, 512);
	sbi->sb_fs_size = -1;
	अगर (!(bootblock = hpfs_map_sector(s, 0, &bh0, 0))) जाओ bail1;
	अगर (!(superblock = hpfs_map_sector(s, 16, &bh1, 1))) जाओ bail2;
	अगर (!(spareblock = hpfs_map_sector(s, 17, &bh2, 0))) जाओ bail3;

	/* Check magics */
	अगर (/*le16_to_cpu(bootblock->magic) != BB_MAGIC
	    ||*/ le32_to_cpu(superblock->magic) != SB_MAGIC
	    || le32_to_cpu(spareblock->magic) != SP_MAGIC) अणु
		अगर (!silent)
			pr_err("Bad magic ... probably not HPFS\n");
		जाओ bail4;
	पूर्ण

	/* Check version */
	अगर (!sb_rकरोnly(s) && superblock->funcversion != 2 && superblock->funcversion != 3) अणु
		pr_err("Bad version %d,%d. Mount readonly to go around\n",
			(पूर्णांक)superblock->version, (पूर्णांक)superblock->funcversion);
		pr_err("please try recent version of HPFS driver at http://artax.karlin.mff.cuni.cz/~mikulas/vyplody/hpfs/index-e.cgi and if it still can't understand this format, contact author - mikulas@artax.karlin.mff.cuni.cz\n");
		जाओ bail4;
	पूर्ण

	s->s_flags |= SB_NOATIME;

	/* Fill superblock stuff */
	s->s_magic = HPFS_SUPER_MAGIC;
	s->s_op = &hpfs_sops;
	s->s_d_op = &hpfs_dentry_operations;
	s->s_समय_min =  local_to_gmt(s, 0);
	s->s_समय_max =  local_to_gmt(s, U32_MAX);

	sbi->sb_root = le32_to_cpu(superblock->root);
	sbi->sb_fs_size = le32_to_cpu(superblock->n_sectors);
	sbi->sb_biपंचांगaps = le32_to_cpu(superblock->biपंचांगaps);
	sbi->sb_dirband_start = le32_to_cpu(superblock->dir_band_start);
	sbi->sb_dirband_size = le32_to_cpu(superblock->n_dir_band);
	sbi->sb_dmap = le32_to_cpu(superblock->dir_band_biपंचांगap);
	sbi->sb_uid = uid;
	sbi->sb_gid = gid;
	sbi->sb_mode = 0777 & ~umask;
	sbi->sb_n_मुक्त = -1;
	sbi->sb_n_मुक्त_dnodes = -1;
	sbi->sb_lowerहाल = lowerहाल;
	sbi->sb_eas = eas;
	sbi->sb_chk = chk;
	sbi->sb_chkdsk = chkdsk;
	sbi->sb_err = errs;
	sbi->sb_बारhअगरt = बारhअगरt;
	sbi->sb_was_error = 0;
	sbi->sb_cp_table = शून्य;
	sbi->sb_c_biपंचांगap = -1;
	sbi->sb_max_fwd_alloc = 0xffffff;

	अगर (sbi->sb_fs_size >= 0x80000000) अणु
		hpfs_error(s, "invalid size in superblock: %08x",
			(अचिन्हित)sbi->sb_fs_size);
		जाओ bail4;
	पूर्ण

	अगर (spareblock->n_spares_used)
		hpfs_load_hotfix_map(s, spareblock);

	/* Load biपंचांगap directory */
	अगर (!(sbi->sb_bmp_dir = hpfs_load_biपंचांगap_directory(s, le32_to_cpu(superblock->biपंचांगaps))))
		जाओ bail4;
	
	/* Check क्रम general fs errors*/
	अगर (spareblock->dirty && !spareblock->old_wrote) अणु
		अगर (errs == 2) अणु
			pr_err("Improperly stopped, not mounted\n");
			जाओ bail4;
		पूर्ण
		hpfs_error(s, "improperly stopped");
	पूर्ण

	अगर (!sb_rकरोnly(s)) अणु
		spareblock->dirty = 1;
		spareblock->old_wrote = 0;
		mark_buffer_dirty(bh2);
	पूर्ण

	अगर (le32_to_cpu(spareblock->n_dnode_spares) != le32_to_cpu(spareblock->n_dnode_spares_मुक्त)) अणु
		अगर (errs >= 2) अणु
			pr_err("Spare dnodes used, try chkdsk\n");
			mark_dirty(s, 0);
			जाओ bail4;
		पूर्ण
		hpfs_error(s, "warning: spare dnodes used, try chkdsk");
		अगर (errs == 0)
			pr_err("Proceeding, but your filesystem could be corrupted if you delete files or directories\n");
	पूर्ण
	अगर (chk) अणु
		अचिन्हित a;
		अगर (le32_to_cpu(superblock->dir_band_end) - le32_to_cpu(superblock->dir_band_start) + 1 != le32_to_cpu(superblock->n_dir_band) ||
		    le32_to_cpu(superblock->dir_band_end) < le32_to_cpu(superblock->dir_band_start) || le32_to_cpu(superblock->n_dir_band) > 0x4000) अणु
			hpfs_error(s, "dir band size mismatch: dir_band_start==%08x, dir_band_end==%08x, n_dir_band==%08x",
				le32_to_cpu(superblock->dir_band_start), le32_to_cpu(superblock->dir_band_end), le32_to_cpu(superblock->n_dir_band));
			जाओ bail4;
		पूर्ण
		a = sbi->sb_dirband_size;
		sbi->sb_dirband_size = 0;
		अगर (hpfs_chk_sectors(s, le32_to_cpu(superblock->dir_band_start), le32_to_cpu(superblock->n_dir_band), "dir_band") ||
		    hpfs_chk_sectors(s, le32_to_cpu(superblock->dir_band_biपंचांगap), 4, "dir_band_bitmap") ||
		    hpfs_chk_sectors(s, le32_to_cpu(superblock->biपंचांगaps), 4, "bitmaps")) अणु
			mark_dirty(s, 0);
			जाओ bail4;
		पूर्ण
		sbi->sb_dirband_size = a;
	पूर्ण अन्यथा
		pr_err("You really don't want any checks? You are crazy...\n");

	/* Load code page table */
	अगर (le32_to_cpu(spareblock->n_code_pages))
		अगर (!(sbi->sb_cp_table = hpfs_load_code_page(s, le32_to_cpu(spareblock->code_page_dir))))
			pr_err("code page support is disabled\n");

	brअन्यथा(bh2);
	brअन्यथा(bh1);
	brअन्यथा(bh0);

	root = iget_locked(s, sbi->sb_root);
	अगर (!root)
		जाओ bail0;
	hpfs_init_inode(root);
	hpfs_पढ़ो_inode(root);
	unlock_new_inode(root);
	s->s_root = d_make_root(root);
	अगर (!s->s_root)
		जाओ bail0;

	/*
	 * find the root directory's . poपूर्णांकer & finish filling in the inode
	 */

	root_dno = hpfs_fnode_dno(s, sbi->sb_root);
	अगर (root_dno)
		de = map_dirent(root, root_dno, "\001\001", 2, शून्य, &qbh);
	अगर (!de)
		hpfs_error(s, "unable to find root dir");
	अन्यथा अणु
		root->i_aसमय.tv_sec = local_to_gmt(s, le32_to_cpu(de->पढ़ो_date));
		root->i_aसमय.tv_nsec = 0;
		root->i_mसमय.tv_sec = local_to_gmt(s, le32_to_cpu(de->ग_लिखो_date));
		root->i_mसमय.tv_nsec = 0;
		root->i_स_समय.tv_sec = local_to_gmt(s, le32_to_cpu(de->creation_date));
		root->i_स_समय.tv_nsec = 0;
		hpfs_i(root)->i_ea_size = le32_to_cpu(de->ea_size);
		hpfs_i(root)->i_parent_dir = root->i_ino;
		अगर (root->i_size == -1)
			root->i_size = 2048;
		अगर (root->i_blocks == -1)
			root->i_blocks = 5;
		hpfs_brअन्यथा4(&qbh);
	पूर्ण
	hpfs_unlock(s);
	वापस 0;

bail4:	brअन्यथा(bh2);
bail3:	brअन्यथा(bh1);
bail2:	brअन्यथा(bh0);
bail1:
bail0:
	hpfs_unlock(s);
	मुक्त_sbi(sbi);
	वापस -EINVAL;
पूर्ण

अटल काष्ठा dentry *hpfs_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, hpfs_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type hpfs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "hpfs",
	.mount		= hpfs_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("hpfs");

अटल पूर्णांक __init init_hpfs_fs(व्योम)
अणु
	पूर्णांक err = init_inodecache();
	अगर (err)
		जाओ out1;
	err = रेजिस्टर_fileप्रणाली(&hpfs_fs_type);
	अगर (err)
		जाओ out;
	वापस 0;
out:
	destroy_inodecache();
out1:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_hpfs_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&hpfs_fs_type);
	destroy_inodecache();
पूर्ण

module_init(init_hpfs_fs)
module_निकास(निकास_hpfs_fs)
MODULE_LICENSE("GPL");
