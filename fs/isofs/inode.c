<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/isofs/inode.c
 *
 *  (C) 1991  Linus Torvalds - minix fileप्रणाली
 *      1992, 1993, 1994  Eric Youngdale Modअगरied क्रम ISO 9660 fileप्रणाली.
 *      1994  Eberhard Mथघnkeberg - multi session handling.
 *      1995  Mark Dobie - allow mounting of some weird VideoCDs and PhotoCDs.
 *	1997  Gorकरोn Chaffee - Joliet CDs
 *	1998  Eric Lammerts - ISO 9660 Level 3
 *	2004  Paul Serice - Inode Support pushed out from 4GB to 128GB
 *	2004  Paul Serice - NFS Export Operations
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>

#समावेश <linux/slab.h>
#समावेश <linux/cred.h>
#समावेश <linux/nls.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/statfs.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/parser.h>
#समावेश <linux/mpage.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/blkdev.h>

#समावेश "isofs.h"
#समावेश "zisofs.h"

/* max tz offset is 13 hours */
#घोषणा MAX_TZ_OFFSET (52*15*60)

#घोषणा BEQUIET

अटल पूर्णांक isofs_hashi(स्थिर काष्ठा dentry *parent, काष्ठा qstr *qstr);
अटल पूर्णांक isofs_dentry_cmpi(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name);

#अगर_घोषित CONFIG_JOLIET
अटल पूर्णांक isofs_hashi_ms(स्थिर काष्ठा dentry *parent, काष्ठा qstr *qstr);
अटल पूर्णांक isofs_hash_ms(स्थिर काष्ठा dentry *parent, काष्ठा qstr *qstr);
अटल पूर्णांक isofs_dentry_cmpi_ms(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name);
अटल पूर्णांक isofs_dentry_cmp_ms(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name);
#पूर्ण_अगर

अटल व्योम isofs_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा isofs_sb_info *sbi = ISOFS_SB(sb);

#अगर_घोषित CONFIG_JOLIET
	unload_nls(sbi->s_nls_ioअक्षरset);
#पूर्ण_अगर

	kमुक्त(sbi);
	sb->s_fs_info = शून्य;
	वापस;
पूर्ण

अटल पूर्णांक isofs_पढ़ो_inode(काष्ठा inode *, पूर्णांक relocated);
अटल पूर्णांक isofs_statfs (काष्ठा dentry *, काष्ठा kstatfs *);
अटल पूर्णांक isofs_show_options(काष्ठा seq_file *, काष्ठा dentry *);

अटल काष्ठा kmem_cache *isofs_inode_cachep;

अटल काष्ठा inode *isofs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा iso_inode_info *ei;
	ei = kmem_cache_alloc(isofs_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;
	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम isofs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(isofs_inode_cachep, ISOFS_I(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा iso_inode_info *ei = foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_inodecache(व्योम)
अणु
	isofs_inode_cachep = kmem_cache_create("isofs_inode_cache",
					माप(काष्ठा iso_inode_info),
					0, (SLAB_RECLAIM_ACCOUNT|
					SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					init_once);
	अगर (!isofs_inode_cachep)
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
	kmem_cache_destroy(isofs_inode_cachep);
पूर्ण

अटल पूर्णांक isofs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	sync_fileप्रणाली(sb);
	अगर (!(*flags & SB_RDONLY))
		वापस -EROFS;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations isofs_sops = अणु
	.alloc_inode	= isofs_alloc_inode,
	.मुक्त_inode	= isofs_मुक्त_inode,
	.put_super	= isofs_put_super,
	.statfs		= isofs_statfs,
	.remount_fs	= isofs_remount,
	.show_options	= isofs_show_options,
पूर्ण;


अटल स्थिर काष्ठा dentry_operations isofs_dentry_ops[] = अणु
	अणु
		.d_hash		= isofs_hashi,
		.d_compare	= isofs_dentry_cmpi,
	पूर्ण,
#अगर_घोषित CONFIG_JOLIET
	अणु
		.d_hash		= isofs_hash_ms,
		.d_compare	= isofs_dentry_cmp_ms,
	पूर्ण,
	अणु
		.d_hash		= isofs_hashi_ms,
		.d_compare	= isofs_dentry_cmpi_ms,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

काष्ठा iso9660_optionsअणु
	अचिन्हित पूर्णांक rock:1;
	अचिन्हित पूर्णांक joliet:1;
	अचिन्हित पूर्णांक cruft:1;
	अचिन्हित पूर्णांक hide:1;
	अचिन्हित पूर्णांक showassoc:1;
	अचिन्हित पूर्णांक nocompress:1;
	अचिन्हित पूर्णांक overriderockperm:1;
	अचिन्हित पूर्णांक uid_set:1;
	अचिन्हित पूर्णांक gid_set:1;
	अचिन्हित पूर्णांक utf8:1;
	अचिन्हित अक्षर map;
	अचिन्हित अक्षर check;
	अचिन्हित पूर्णांक blocksize;
	umode_t भ_शेषe;
	umode_t dmode;
	kgid_t gid;
	kuid_t uid;
	अक्षर *ioअक्षरset;
	/* LVE */
	s32 session;
	s32 sbsector;
पूर्ण;

/*
 * Compute the hash क्रम the isofs name corresponding to the dentry.
 */
अटल पूर्णांक
isofs_hashi_common(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr, पूर्णांक ms)
अणु
	स्थिर अक्षर *name;
	पूर्णांक len;
	अक्षर c;
	अचिन्हित दीर्घ hash;

	len = qstr->len;
	name = qstr->name;
	अगर (ms) अणु
		जबतक (len && name[len-1] == '.')
			len--;
	पूर्ण

	hash = init_name_hash(dentry);
	जबतक (len--) अणु
		c = छोटे(*name++);
		hash = partial_name_hash(c, hash);
	पूर्ण
	qstr->hash = end_name_hash(hash);

	वापस 0;
पूर्ण

/*
 * Compare of two isofs names.
 */
अटल पूर्णांक isofs_dentry_cmp_common(
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str,
		स्थिर काष्ठा qstr *name, पूर्णांक ms, पूर्णांक ci)
अणु
	पूर्णांक alen, blen;

	/* A filename cannot end in '.' or we treat it like it has none */
	alen = name->len;
	blen = len;
	अगर (ms) अणु
		जबतक (alen && name->name[alen-1] == '.')
			alen--;
		जबतक (blen && str[blen-1] == '.')
			blen--;
	पूर्ण
	अगर (alen == blen) अणु
		अगर (ci) अणु
			अगर (strnहालcmp(name->name, str, alen) == 0)
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर (म_भेदन(name->name, str, alen) == 0)
				वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक
isofs_hashi(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr)
अणु
	वापस isofs_hashi_common(dentry, qstr, 0);
पूर्ण

अटल पूर्णांक
isofs_dentry_cmpi(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	वापस isofs_dentry_cmp_common(len, str, name, 0, 1);
पूर्ण

#अगर_घोषित CONFIG_JOLIET
/*
 * Compute the hash क्रम the isofs name corresponding to the dentry.
 */
अटल पूर्णांक
isofs_hash_common(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr, पूर्णांक ms)
अणु
	स्थिर अक्षर *name;
	पूर्णांक len;

	len = qstr->len;
	name = qstr->name;
	अगर (ms) अणु
		जबतक (len && name[len-1] == '.')
			len--;
	पूर्ण

	qstr->hash = full_name_hash(dentry, name, len);

	वापस 0;
पूर्ण

अटल पूर्णांक
isofs_hash_ms(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr)
अणु
	वापस isofs_hash_common(dentry, qstr, 1);
पूर्ण

अटल पूर्णांक
isofs_hashi_ms(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr)
अणु
	वापस isofs_hashi_common(dentry, qstr, 1);
पूर्ण

अटल पूर्णांक
isofs_dentry_cmp_ms(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	वापस isofs_dentry_cmp_common(len, str, name, 1, 0);
पूर्ण

अटल पूर्णांक
isofs_dentry_cmpi_ms(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	वापस isofs_dentry_cmp_common(len, str, name, 1, 1);
पूर्ण
#पूर्ण_अगर

क्रमागत अणु
	Opt_block, Opt_check_r, Opt_check_s, Opt_cruft, Opt_gid, Opt_ignore,
	Opt_ioअक्षरset, Opt_map_a, Opt_map_n, Opt_map_o, Opt_mode, Opt_nojoliet,
	Opt_norock, Opt_sb, Opt_session, Opt_uid, Opt_unhide, Opt_utf8, Opt_err,
	Opt_nocompress, Opt_hide, Opt_showassoc, Opt_dmode, Opt_overriderockperm,
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_norock, "norock"पूर्ण,
	अणुOpt_nojoliet, "nojoliet"पूर्ण,
	अणुOpt_unhide, "unhide"पूर्ण,
	अणुOpt_hide, "hide"पूर्ण,
	अणुOpt_showassoc, "showassoc"पूर्ण,
	अणुOpt_cruft, "cruft"पूर्ण,
	अणुOpt_utf8, "utf8"पूर्ण,
	अणुOpt_ioअक्षरset, "iocharset=%s"पूर्ण,
	अणुOpt_map_a, "map=acorn"पूर्ण,
	अणुOpt_map_a, "map=a"पूर्ण,
	अणुOpt_map_n, "map=normal"पूर्ण,
	अणुOpt_map_n, "map=n"पूर्ण,
	अणुOpt_map_o, "map=off"पूर्ण,
	अणुOpt_map_o, "map=o"पूर्ण,
	अणुOpt_session, "session=%u"पूर्ण,
	अणुOpt_sb, "sbsector=%u"पूर्ण,
	अणुOpt_check_r, "check=relaxed"पूर्ण,
	अणुOpt_check_r, "check=r"पूर्ण,
	अणुOpt_check_s, "check=strict"पूर्ण,
	अणुOpt_check_s, "check=s"पूर्ण,
	अणुOpt_uid, "uid=%u"पूर्ण,
	अणुOpt_gid, "gid=%u"पूर्ण,
	अणुOpt_mode, "mode=%u"पूर्ण,
	अणुOpt_dmode, "dmode=%u"पूर्ण,
	अणुOpt_overriderockperm, "overriderockperm"पूर्ण,
	अणुOpt_block, "block=%u"पूर्ण,
	अणुOpt_ignore, "conv=binary"पूर्ण,
	अणुOpt_ignore, "conv=b"पूर्ण,
	अणुOpt_ignore, "conv=text"पूर्ण,
	अणुOpt_ignore, "conv=t"पूर्ण,
	अणुOpt_ignore, "conv=mtext"पूर्ण,
	अणुOpt_ignore, "conv=m"पूर्ण,
	अणुOpt_ignore, "conv=auto"पूर्ण,
	अणुOpt_ignore, "conv=a"पूर्ण,
	अणुOpt_nocompress, "nocompress"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक parse_options(अक्षर *options, काष्ठा iso9660_options *popt)
अणु
	अक्षर *p;
	पूर्णांक option;
	अचिन्हित पूर्णांक uv;

	popt->map = 'n';
	popt->rock = 1;
	popt->joliet = 1;
	popt->cruft = 0;
	popt->hide = 0;
	popt->showassoc = 0;
	popt->check = 'u';		/* unset */
	popt->nocompress = 0;
	popt->blocksize = 1024;
	popt->भ_शेषe = popt->dmode = ISOFS_INVALID_MODE;
	popt->uid_set = 0;
	popt->gid_set = 0;
	popt->gid = GLOBAL_ROOT_GID;
	popt->uid = GLOBAL_ROOT_UID;
	popt->ioअक्षरset = शून्य;
	popt->utf8 = 0;
	popt->overriderockperm = 0;
	popt->session=-1;
	popt->sbsector=-1;
	अगर (!options)
		वापस 1;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;
		substring_t args[MAX_OPT_ARGS];
		अचिन्हित n;

		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_norock:
			popt->rock = 0;
			अवरोध;
		हाल Opt_nojoliet:
			popt->joliet = 0;
			अवरोध;
		हाल Opt_hide:
			popt->hide = 1;
			अवरोध;
		हाल Opt_unhide:
		हाल Opt_showassoc:
			popt->showassoc = 1;
			अवरोध;
		हाल Opt_cruft:
			popt->cruft = 1;
			अवरोध;
		हाल Opt_utf8:
			popt->utf8 = 1;
			अवरोध;
#अगर_घोषित CONFIG_JOLIET
		हाल Opt_ioअक्षरset:
			kमुक्त(popt->ioअक्षरset);
			popt->ioअक्षरset = match_strdup(&args[0]);
			अगर (!popt->ioअक्षरset)
				वापस 0;
			अवरोध;
#पूर्ण_अगर
		हाल Opt_map_a:
			popt->map = 'a';
			अवरोध;
		हाल Opt_map_o:
			popt->map = 'o';
			अवरोध;
		हाल Opt_map_n:
			popt->map = 'n';
			अवरोध;
		हाल Opt_session:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			n = option;
			/*
			 * Track numbers are supposed to be in range 1-99, the
			 * mount option starts indexing at 0.
			 */
			अगर (n >= 99)
				वापस 0;
			popt->session = n + 1;
			अवरोध;
		हाल Opt_sb:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			popt->sbsector = option;
			अवरोध;
		हाल Opt_check_r:
			popt->check = 'r';
			अवरोध;
		हाल Opt_check_s:
			popt->check = 's';
			अवरोध;
		हाल Opt_ignore:
			अवरोध;
		हाल Opt_uid:
			अगर (match_uपूर्णांक(&args[0], &uv))
				वापस 0;
			popt->uid = make_kuid(current_user_ns(), uv);
			अगर (!uid_valid(popt->uid))
				वापस 0;
			popt->uid_set = 1;
			अवरोध;
		हाल Opt_gid:
			अगर (match_uपूर्णांक(&args[0], &uv))
				वापस 0;
			popt->gid = make_kgid(current_user_ns(), uv);
			अगर (!gid_valid(popt->gid))
				वापस 0;
			popt->gid_set = 1;
			अवरोध;
		हाल Opt_mode:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			popt->भ_शेषe = option;
			अवरोध;
		हाल Opt_dmode:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			popt->dmode = option;
			अवरोध;
		हाल Opt_overriderockperm:
			popt->overriderockperm = 1;
			अवरोध;
		हाल Opt_block:
			अगर (match_पूर्णांक(&args[0], &option))
				वापस 0;
			n = option;
			अगर (n != 512 && n != 1024 && n != 2048)
				वापस 0;
			popt->blocksize = n;
			अवरोध;
		हाल Opt_nocompress:
			popt->nocompress = 1;
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

/*
 * Display the mount options in /proc/mounts.
 */
अटल पूर्णांक isofs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा isofs_sb_info *sbi = ISOFS_SB(root->d_sb);

	अगर (!sbi->s_rock)		seq_माला_दो(m, ",norock");
	अन्यथा अगर (!sbi->s_joliet_level)	seq_माला_दो(m, ",nojoliet");
	अगर (sbi->s_cruft)		seq_माला_दो(m, ",cruft");
	अगर (sbi->s_hide)		seq_माला_दो(m, ",hide");
	अगर (sbi->s_nocompress)		seq_माला_दो(m, ",nocompress");
	अगर (sbi->s_overriderockperm)	seq_माला_दो(m, ",overriderockperm");
	अगर (sbi->s_showassoc)		seq_माला_दो(m, ",showassoc");
	अगर (sbi->s_utf8)		seq_माला_दो(m, ",utf8");

	अगर (sbi->s_check)		seq_म_लिखो(m, ",check=%c", sbi->s_check);
	अगर (sbi->s_mapping)		seq_म_लिखो(m, ",map=%c", sbi->s_mapping);
	अगर (sbi->s_session != 255)	seq_म_लिखो(m, ",session=%u", sbi->s_session - 1);
	अगर (sbi->s_sbsector != -1)	seq_म_लिखो(m, ",sbsector=%u", sbi->s_sbsector);

	अगर (root->d_sb->s_blocksize != 1024)
		seq_म_लिखो(m, ",blocksize=%lu", root->d_sb->s_blocksize);

	अगर (sbi->s_uid_set)
		seq_म_लिखो(m, ",uid=%u",
			   from_kuid_munged(&init_user_ns, sbi->s_uid));
	अगर (sbi->s_gid_set)
		seq_म_लिखो(m, ",gid=%u",
			   from_kgid_munged(&init_user_ns, sbi->s_gid));

	अगर (sbi->s_dmode != ISOFS_INVALID_MODE)
		seq_म_लिखो(m, ",dmode=%o", sbi->s_dmode);
	अगर (sbi->s_भ_शेषe != ISOFS_INVALID_MODE)
		seq_म_लिखो(m, ",fmode=%o", sbi->s_भ_शेषe);

#अगर_घोषित CONFIG_JOLIET
	अगर (sbi->s_nls_ioअक्षरset &&
	    म_भेद(sbi->s_nls_ioअक्षरset->अक्षरset, CONFIG_NLS_DEFAULT) != 0)
		seq_म_लिखो(m, ",iocharset=%s", sbi->s_nls_ioअक्षरset->अक्षरset);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * look अगर the driver can tell the multi session redirection value
 *
 * करोn't change this if you don't know what you करो, please!
 * Multisession is legal only with XA disks.
 * A non-XA disk with more than one volume descriptor may करो it right, but
 * usually is written in a nowhere standardized "multi-partition" manner.
 * Multisession uses असलolute addressing (solely the first frame of the whole
 * track is #0), multi-partition uses relative addressing (each first frame of
 * each track is #0), and a track is not a session.
 *
 * A broken CDग_लिखोr software or drive firmware करोes not set new standards,
 * at least not अगर conflicting with the existing ones.
 *
 * emoenke@gwdg.de
 */
#घोषणा WE_OBEY_THE_WRITTEN_STANDARDS 1

अटल अचिन्हित पूर्णांक isofs_get_last_session(काष्ठा super_block *sb, s32 session)
अणु
	काष्ठा cdrom_device_info *cdi = disk_to_cdi(sb->s_bdev->bd_disk);
	अचिन्हित पूर्णांक vol_desc_start = 0;

	अगर (session > 0) अणु
		काष्ठा cdrom_tocentry te;

		अगर (!cdi)
			वापस 0;

		te.cdte_track = session;
		te.cdte_क्रमmat = CDROM_LBA;
		अगर (cdrom_पढ़ो_tocentry(cdi, &te) == 0) अणु
			prपूर्णांकk(KERN_DEBUG "ISOFS: Session %d start %d type %d\n",
				session, te.cdte_addr.lba,
				te.cdte_ctrl & CDROM_DATA_TRACK);
			अगर ((te.cdte_ctrl & CDROM_DATA_TRACK) == 4)
				वापस te.cdte_addr.lba;
		पूर्ण

		prपूर्णांकk(KERN_ERR "ISOFS: Invalid session number or type of track\n");
	पूर्ण

	अगर (cdi) अणु
		काष्ठा cdrom_multisession ms_info;

		ms_info.addr_क्रमmat = CDROM_LBA;
		अगर (cdrom_multisession(cdi, &ms_info) == 0) अणु
#अगर WE_OBEY_THE_WRITTEN_STANDARDS
			/* necessary क्रम a valid ms_info.addr */
			अगर (ms_info.xa_flag)
#पूर्ण_अगर
				vol_desc_start = ms_info.addr.lba;
		पूर्ण
	पूर्ण

	वापस vol_desc_start;
पूर्ण

/*
 * Check अगर root directory is empty (has less than 3 files).
 *
 * Used to detect broken CDs where ISO root directory is empty but Joliet root
 * directory is OK. If such CD has Rock Ridge extensions, they will be disabled
 * (and Joliet used instead) or अन्यथा no files would be visible.
 */
अटल bool rootdir_empty(काष्ठा super_block *sb, अचिन्हित दीर्घ block)
अणु
	पूर्णांक offset = 0, files = 0, de_len;
	काष्ठा iso_directory_record *de;
	काष्ठा buffer_head *bh;

	bh = sb_bपढ़ो(sb, block);
	अगर (!bh)
		वापस true;
	जबतक (files < 3) अणु
		de = (काष्ठा iso_directory_record *) (bh->b_data + offset);
		de_len = *(अचिन्हित अक्षर *) de;
		अगर (de_len == 0)
			अवरोध;
		files++;
		offset += de_len;
	पूर्ण
	brअन्यथा(bh);
	वापस files < 3;
पूर्ण

/*
 * Initialize the superblock and पढ़ो the root inode.
 */
अटल पूर्णांक isofs_fill_super(काष्ठा super_block *s, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा buffer_head *bh = शून्य, *pri_bh = शून्य;
	काष्ठा hs_primary_descriptor *h_pri = शून्य;
	काष्ठा iso_primary_descriptor *pri = शून्य;
	काष्ठा iso_supplementary_descriptor *sec = शून्य;
	काष्ठा iso_directory_record *rootp;
	काष्ठा inode *inode;
	काष्ठा iso9660_options opt;
	काष्ठा isofs_sb_info *sbi;
	अचिन्हित दीर्घ first_data_zone;
	पूर्णांक joliet_level = 0;
	पूर्णांक iso_blknum, block;
	पूर्णांक orig_zonesize;
	पूर्णांक table, error = -EINVAL;
	अचिन्हित पूर्णांक vol_desc_start;

	sbi = kzalloc(माप(*sbi), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;
	s->s_fs_info = sbi;

	अगर (!parse_options((अक्षर *)data, &opt))
		जाओ out_मुक्तsbi;

	/*
	 * First of all, get the hardware blocksize क्रम this device.
	 * If we करोn't know what it is, or the hardware blocksize is
	 * larger than the blocksize the user specअगरied, then use
	 * that value.
	 */
	/*
	 * What अगर bugger tells us to go beyond page size?
	 */
	अगर (bdev_logical_block_size(s->s_bdev) > 2048) अणु
		prपूर्णांकk(KERN_WARNING
		       "ISOFS: unsupported/invalid hardware sector size %d\n",
			bdev_logical_block_size(s->s_bdev));
		जाओ out_मुक्तsbi;
	पूर्ण
	opt.blocksize = sb_min_blocksize(s, opt.blocksize);

	sbi->s_high_sierra = 0; /* शेष is iso9660 */
	sbi->s_session = opt.session;
	sbi->s_sbsector = opt.sbsector;

	vol_desc_start = (opt.sbsector != -1) ?
		opt.sbsector : isofs_get_last_session(s,opt.session);

	क्रम (iso_blknum = vol_desc_start+16;
		iso_blknum < vol_desc_start+100; iso_blknum++) अणु
		काष्ठा hs_volume_descriptor *hdp;
		काष्ठा iso_volume_descriptor  *vdp;

		block = iso_blknum << (ISOFS_BLOCK_BITS - s->s_blocksize_bits);
		अगर (!(bh = sb_bपढ़ो(s, block)))
			जाओ out_no_पढ़ो;

		vdp = (काष्ठा iso_volume_descriptor *)bh->b_data;
		hdp = (काष्ठा hs_volume_descriptor *)bh->b_data;

		/*
		 * Due to the overlapping physical location of the descriptors,
		 * ISO CDs can match hdp->id==HS_STANDARD_ID as well. To ensure
		 * proper identअगरication in this हाल, we first check क्रम ISO.
		 */
		अगर (म_भेदन (vdp->id, ISO_STANDARD_ID, माप vdp->id) == 0) अणु
			अगर (isonum_711(vdp->type) == ISO_VD_END)
				अवरोध;
			अगर (isonum_711(vdp->type) == ISO_VD_PRIMARY) अणु
				अगर (!pri) अणु
					pri = (काष्ठा iso_primary_descriptor *)vdp;
					/* Save the buffer in हाल we need it ... */
					pri_bh = bh;
					bh = शून्य;
				पूर्ण
			पूर्ण
#अगर_घोषित CONFIG_JOLIET
			अन्यथा अगर (isonum_711(vdp->type) == ISO_VD_SUPPLEMENTARY) अणु
				sec = (काष्ठा iso_supplementary_descriptor *)vdp;
				अगर (sec->escape[0] == 0x25 && sec->escape[1] == 0x2f) अणु
					अगर (opt.joliet) अणु
						अगर (sec->escape[2] == 0x40)
							joliet_level = 1;
						अन्यथा अगर (sec->escape[2] == 0x43)
							joliet_level = 2;
						अन्यथा अगर (sec->escape[2] == 0x45)
							joliet_level = 3;

						prपूर्णांकk(KERN_DEBUG "ISO 9660 Extensions: "
							"Microsoft Joliet Level %d\n",
							joliet_level);
					पूर्ण
					जाओ root_found;
				पूर्ण अन्यथा अणु
				/* Unknown supplementary volume descriptor */
				sec = शून्य;
				पूर्ण
			पूर्ण
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			अगर (म_भेदन (hdp->id, HS_STANDARD_ID, माप hdp->id) == 0) अणु
				अगर (isonum_711(hdp->type) != ISO_VD_PRIMARY)
					जाओ out_मुक्तbh;

				sbi->s_high_sierra = 1;
				opt.rock = 0;
				h_pri = (काष्ठा hs_primary_descriptor *)vdp;
				जाओ root_found;
			पूर्ण
		पूर्ण

		/* Just skip any volume descriptors we करोn't recognize */

		brअन्यथा(bh);
		bh = शून्य;
	पूर्ण
	/*
	 * If we fall through, either no volume descriptor was found,
	 * or अन्यथा we passed a primary descriptor looking क्रम others.
	 */
	अगर (!pri)
		जाओ out_unknown_क्रमmat;
	brअन्यथा(bh);
	bh = pri_bh;
	pri_bh = शून्य;

root_found:
	/* We करोn't support पढ़ो-ग_लिखो mounts */
	अगर (!sb_rकरोnly(s)) अणु
		error = -EACCES;
		जाओ out_मुक्तbh;
	पूर्ण

	अगर (joliet_level && (!pri || !opt.rock)) अणु
		/* This is the हाल of Joliet with the norock mount flag.
		 * A disc with both Joliet and Rock Ridge is handled later
		 */
		pri = (काष्ठा iso_primary_descriptor *) sec;
	पूर्ण

	अगर(sbi->s_high_sierra)अणु
		rootp = (काष्ठा iso_directory_record *) h_pri->root_directory_record;
		sbi->s_nzones = isonum_733(h_pri->volume_space_size);
		sbi->s_log_zone_size = isonum_723(h_pri->logical_block_size);
		sbi->s_max_size = isonum_733(h_pri->volume_space_size);
	पूर्ण अन्यथा अणु
		अगर (!pri)
			जाओ out_मुक्तbh;
		rootp = (काष्ठा iso_directory_record *) pri->root_directory_record;
		sbi->s_nzones = isonum_733(pri->volume_space_size);
		sbi->s_log_zone_size = isonum_723(pri->logical_block_size);
		sbi->s_max_size = isonum_733(pri->volume_space_size);
	पूर्ण

	sbi->s_ninodes = 0; /* No way to figure this out easily */

	orig_zonesize = sbi->s_log_zone_size;
	/*
	 * If the zone size is smaller than the hardware sector size,
	 * this is a fatal error.  This would occur अगर the disc drive
	 * had sectors that were 2048 bytes, but the fileप्रणाली had
	 * blocks that were 512 bytes (which should only very rarely
	 * happen.)
	 */
	अगर (orig_zonesize < opt.blocksize)
		जाओ out_bad_size;

	/* RDE: convert log zone size to bit shअगरt */
	चयन (sbi->s_log_zone_size) अणु
	हाल  512: sbi->s_log_zone_size =  9; अवरोध;
	हाल 1024: sbi->s_log_zone_size = 10; अवरोध;
	हाल 2048: sbi->s_log_zone_size = 11; अवरोध;

	शेष:
		जाओ out_bad_zone_size;
	पूर्ण

	s->s_magic = ISOFS_SUPER_MAGIC;

	/*
	 * With multi-extent files, file size is only limited by the maximum
	 * size of a file प्रणाली, which is 8 TB.
	 */
	s->s_maxbytes = 0x80000000000LL;

	/* ECMA-119 बारtamp from 1900/1/1 with tz offset */
	s->s_समय_min = स_गढ़ो64(1900, 1, 1, 0, 0, 0) - MAX_TZ_OFFSET;
	s->s_समय_max = स_गढ़ो64(U8_MAX+1900, 12, 31, 23, 59, 59) + MAX_TZ_OFFSET;

	/* Set this क्रम reference. Its not currently used except on ग_लिखो
	   which we करोn't have .. */

	first_data_zone = isonum_733(rootp->extent) +
			  isonum_711(rootp->ext_attr_length);
	sbi->s_firstdatazone = first_data_zone;
#अगर_अघोषित BEQUIET
	prपूर्णांकk(KERN_DEBUG "ISOFS: Max size:%ld   Log zone size:%ld\n",
		sbi->s_max_size, 1UL << sbi->s_log_zone_size);
	prपूर्णांकk(KERN_DEBUG "ISOFS: First datazone:%ld\n", sbi->s_firstdatazone);
	अगर(sbi->s_high_sierra)
		prपूर्णांकk(KERN_DEBUG "ISOFS: Disc in High Sierra format.\n");
#पूर्ण_अगर

	/*
	 * If the Joliet level is set, we _may_ decide to use the
	 * secondary descriptor, but can't be sure until after we
	 * पढ़ो the root inode. But beक्रमe पढ़ोing the root inode
	 * we may need to change the device blocksize, and would
	 * rather release the old buffer first. So, we cache the
	 * first_data_zone value from the secondary descriptor.
	 */
	अगर (joliet_level) अणु
		pri = (काष्ठा iso_primary_descriptor *) sec;
		rootp = (काष्ठा iso_directory_record *)
			pri->root_directory_record;
		first_data_zone = isonum_733(rootp->extent) +
				isonum_711(rootp->ext_attr_length);
	पूर्ण

	/*
	 * We're all करोne using the volume descriptor, and may need
	 * to change the device blocksize, so release the buffer now.
	 */
	brअन्यथा(pri_bh);
	brअन्यथा(bh);

	/*
	 * Force the blocksize to 512 क्रम 512 byte sectors.  The file
	 * पढ़ो primitives really get it wrong in a bad way अगर we करोn't
	 * करो this.
	 *
	 * Note - we should never be setting the blocksize to something
	 * less than the hardware sector size क्रम the device.  If we
	 * करो, we would end up having to पढ़ो larger buffers and split
	 * out portions to satisfy requests.
	 *
	 * Note2- the idea here is that we want to deal with the optimal
	 * zonesize in the fileप्रणाली.  If we have it set to something less,
	 * then we have horrible problems with trying to piece together
	 * bits of adjacent blocks in order to properly पढ़ो directory
	 * entries.  By क्रमcing the blocksize in this way, we ensure
	 * that we will never be required to करो this.
	 */
	sb_set_blocksize(s, orig_zonesize);

	sbi->s_nls_ioअक्षरset = शून्य;

#अगर_घोषित CONFIG_JOLIET
	अगर (joliet_level && opt.utf8 == 0) अणु
		अक्षर *p = opt.ioअक्षरset ? opt.ioअक्षरset : CONFIG_NLS_DEFAULT;
		sbi->s_nls_ioअक्षरset = load_nls(p);
		अगर (! sbi->s_nls_ioअक्षरset) अणु
			/* Fail only अगर explicit अक्षरset specअगरied */
			अगर (opt.ioअक्षरset)
				जाओ out_मुक्तsbi;
			sbi->s_nls_ioअक्षरset = load_nls_शेष();
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	s->s_op = &isofs_sops;
	s->s_export_op = &isofs_export_ops;
	sbi->s_mapping = opt.map;
	sbi->s_rock = (opt.rock ? 2 : 0);
	sbi->s_rock_offset = -1; /* initial offset, will guess until SP is found*/
	sbi->s_cruft = opt.cruft;
	sbi->s_hide = opt.hide;
	sbi->s_showassoc = opt.showassoc;
	sbi->s_uid = opt.uid;
	sbi->s_gid = opt.gid;
	sbi->s_uid_set = opt.uid_set;
	sbi->s_gid_set = opt.gid_set;
	sbi->s_utf8 = opt.utf8;
	sbi->s_nocompress = opt.nocompress;
	sbi->s_overriderockperm = opt.overriderockperm;
	/*
	 * It would be incredibly stupid to allow people to mark every file
	 * on the disk as suid, so we merely allow them to set the शेष
	 * permissions.
	 */
	अगर (opt.भ_शेषe != ISOFS_INVALID_MODE)
		sbi->s_भ_शेषe = opt.भ_शेषe & 0777;
	अन्यथा
		sbi->s_भ_शेषe = ISOFS_INVALID_MODE;
	अगर (opt.dmode != ISOFS_INVALID_MODE)
		sbi->s_dmode = opt.dmode & 0777;
	अन्यथा
		sbi->s_dmode = ISOFS_INVALID_MODE;

	/*
	 * Read the root inode, which _may_ result in changing
	 * the s_rock flag. Once we have the final s_rock value,
	 * we then decide whether to use the Joliet descriptor.
	 */
	inode = isofs_iget(s, sbi->s_firstdatazone, 0);
	अगर (IS_ERR(inode))
		जाओ out_no_root;

	/*
	 * Fix क्रम broken CDs with Rock Ridge and empty ISO root directory but
	 * correct Joliet root directory.
	 */
	अगर (sbi->s_rock == 1 && joliet_level &&
				rootdir_empty(s, sbi->s_firstdatazone)) अणु
		prपूर्णांकk(KERN_NOTICE
			"ISOFS: primary root directory is empty. "
			"Disabling Rock Ridge and switching to Joliet.");
		sbi->s_rock = 0;
	पूर्ण

	/*
	 * If this disk has both Rock Ridge and Joliet on it, then we
	 * want to use Rock Ridge by शेष.  This can be overridden
	 * by using the norock mount option.  There is still one other
	 * possibility that is not taken पूर्णांकo account: a Rock Ridge
	 * CD with Unicode names.  Until someone sees such a beast, it
	 * will not be supported.
	 */
	अगर (sbi->s_rock == 1) अणु
		joliet_level = 0;
	पूर्ण अन्यथा अगर (joliet_level) अणु
		sbi->s_rock = 0;
		अगर (sbi->s_firstdatazone != first_data_zone) अणु
			sbi->s_firstdatazone = first_data_zone;
			prपूर्णांकk(KERN_DEBUG
				"ISOFS: changing to secondary root\n");
			iput(inode);
			inode = isofs_iget(s, sbi->s_firstdatazone, 0);
			अगर (IS_ERR(inode))
				जाओ out_no_root;
		पूर्ण
	पूर्ण

	अगर (opt.check == 'u') अणु
		/* Only Joliet is हाल insensitive by शेष */
		अगर (joliet_level)
			opt.check = 'r';
		अन्यथा
			opt.check = 's';
	पूर्ण
	sbi->s_joliet_level = joliet_level;

	/* Make sure the root inode is a directory */
	अगर (!S_ISसूची(inode->i_mode)) अणु
		prपूर्णांकk(KERN_WARNING
			"isofs_fill_super: root inode is not a directory. "
			"Corrupted media?\n");
		जाओ out_iput;
	पूर्ण

	table = 0;
	अगर (joliet_level)
		table += 2;
	अगर (opt.check == 'r')
		table++;
	sbi->s_check = opt.check;

	अगर (table)
		s->s_d_op = &isofs_dentry_ops[table - 1];

	/* get the root dentry */
	s->s_root = d_make_root(inode);
	अगर (!(s->s_root)) अणु
		error = -ENOMEM;
		जाओ out_no_inode;
	पूर्ण

	kमुक्त(opt.ioअक्षरset);

	वापस 0;

	/*
	 * Display error messages and मुक्त resources.
	 */
out_iput:
	iput(inode);
	जाओ out_no_inode;
out_no_root:
	error = PTR_ERR(inode);
	अगर (error != -ENOMEM)
		prपूर्णांकk(KERN_WARNING "%s: get root inode failed\n", __func__);
out_no_inode:
#अगर_घोषित CONFIG_JOLIET
	unload_nls(sbi->s_nls_ioअक्षरset);
#पूर्ण_अगर
	जाओ out_मुक्तsbi;
out_no_पढ़ो:
	prपूर्णांकk(KERN_WARNING "%s: bread failed, dev=%s, iso_blknum=%d, block=%d\n",
		__func__, s->s_id, iso_blknum, block);
	जाओ out_मुक्तbh;
out_bad_zone_size:
	prपूर्णांकk(KERN_WARNING "ISOFS: Bad logical zone size %ld\n",
		sbi->s_log_zone_size);
	जाओ out_मुक्तbh;
out_bad_size:
	prपूर्णांकk(KERN_WARNING "ISOFS: Logical zone size(%d) < hardware blocksize(%u)\n",
		orig_zonesize, opt.blocksize);
	जाओ out_मुक्तbh;
out_unknown_क्रमmat:
	अगर (!silent)
		prपूर्णांकk(KERN_WARNING "ISOFS: Unable to identify CD-ROM format.\n");

out_मुक्तbh:
	brअन्यथा(bh);
	brअन्यथा(pri_bh);
out_मुक्तsbi:
	kमुक्त(opt.ioअक्षरset);
	kमुक्त(sbi);
	s->s_fs_info = शून्य;
	वापस error;
पूर्ण

अटल पूर्णांक isofs_statfs (काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type = ISOFS_SUPER_MAGIC;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = (ISOFS_SB(sb)->s_nzones
		<< (ISOFS_SB(sb)->s_log_zone_size - sb->s_blocksize_bits));
	buf->f_bमुक्त = 0;
	buf->f_bavail = 0;
	buf->f_files = ISOFS_SB(sb)->s_ninodes;
	buf->f_fमुक्त = 0;
	buf->f_fsid = u64_to_fsid(id);
	buf->f_namelen = NAME_MAX;
	वापस 0;
पूर्ण

/*
 * Get a set of blocks; filling in buffer_heads अगर alपढ़ोy allocated
 * or getblk() अगर they are not.  Returns the number of blocks inserted
 * (-ve == error.)
 */
पूर्णांक isofs_get_blocks(काष्ठा inode *inode, sector_t iblock,
		     काष्ठा buffer_head **bh, अचिन्हित दीर्घ nblocks)
अणु
	अचिन्हित दीर्घ b_off = iblock;
	अचिन्हित offset, sect_size;
	अचिन्हित पूर्णांक firstext;
	अचिन्हित दीर्घ nextblk, nextoff;
	पूर्णांक section, rv, error;
	काष्ठा iso_inode_info *ei = ISOFS_I(inode);

	error = -EIO;
	rv = 0;
	अगर (iblock != b_off) अणु
		prपूर्णांकk(KERN_DEBUG "%s: block number too large\n", __func__);
		जाओ पात;
	पूर्ण


	offset = 0;
	firstext = ei->i_first_extent;
	sect_size = ei->i_section_size >> ISOFS_BUFFER_BITS(inode);
	nextblk = ei->i_next_section_block;
	nextoff = ei->i_next_section_offset;
	section = 0;

	जबतक (nblocks) अणु
		/* If we are *way* beyond the end of the file, prपूर्णांक a message.
		 * Access beyond the end of the file up to the next page boundary
		 * is normal, however because of the way the page cache works.
		 * In this हाल, we just वापस 0 so that we can properly fill
		 * the page with useless inक्रमmation without generating any
		 * I/O errors.
		 */
		अगर (b_off > ((inode->i_size + PAGE_SIZE - 1) >> ISOFS_BUFFER_BITS(inode))) अणु
			prपूर्णांकk(KERN_DEBUG "%s: block >= EOF (%lu, %llu)\n",
				__func__, b_off,
				(अचिन्हित दीर्घ दीर्घ)inode->i_size);
			जाओ पात;
		पूर्ण

		/* On the last section, nextblk == 0, section size is likely to
		 * exceed sect_size by a partial block, and access beyond the
		 * end of the file will reach beyond the section size, too.
		 */
		जबतक (nextblk && (b_off >= (offset + sect_size))) अणु
			काष्ठा inode *ninode;

			offset += sect_size;
			ninode = isofs_iget(inode->i_sb, nextblk, nextoff);
			अगर (IS_ERR(ninode)) अणु
				error = PTR_ERR(ninode);
				जाओ पात;
			पूर्ण
			firstext  = ISOFS_I(ninode)->i_first_extent;
			sect_size = ISOFS_I(ninode)->i_section_size >> ISOFS_BUFFER_BITS(ninode);
			nextblk   = ISOFS_I(ninode)->i_next_section_block;
			nextoff   = ISOFS_I(ninode)->i_next_section_offset;
			iput(ninode);

			अगर (++section > 100) अणु
				prपूर्णांकk(KERN_DEBUG "%s: More than 100 file sections ?!?"
					" aborting...\n", __func__);
				prपूर्णांकk(KERN_DEBUG "%s: block=%lu firstext=%u sect_size=%u "
					"nextblk=%lu nextoff=%lu\n", __func__,
					b_off, firstext, (अचिन्हित) sect_size,
					nextblk, nextoff);
				जाओ पात;
			पूर्ण
		पूर्ण

		अगर (*bh) अणु
			map_bh(*bh, inode->i_sb, firstext + b_off - offset);
		पूर्ण अन्यथा अणु
			*bh = sb_getblk(inode->i_sb, firstext+b_off-offset);
			अगर (!*bh)
				जाओ पात;
		पूर्ण
		bh++;	/* Next buffer head */
		b_off++;	/* Next buffer offset */
		nblocks--;
		rv++;
	पूर्ण

	error = 0;
पात:
	वापस rv != 0 ? rv : error;
पूर्ण

/*
 * Used by the standard पूर्णांकerfaces.
 */
अटल पूर्णांक isofs_get_block(काष्ठा inode *inode, sector_t iblock,
		    काष्ठा buffer_head *bh_result, पूर्णांक create)
अणु
	पूर्णांक ret;

	अगर (create) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Kernel tries to allocate a block\n", __func__);
		वापस -EROFS;
	पूर्ण

	ret = isofs_get_blocks(inode, iblock, &bh_result, 1);
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल पूर्णांक isofs_bmap(काष्ठा inode *inode, sector_t block)
अणु
	काष्ठा buffer_head dummy;
	पूर्णांक error;

	dummy.b_state = 0;
	dummy.b_blocknr = -1000;
	error = isofs_get_block(inode, block, &dummy, 0);
	अगर (!error)
		वापस dummy.b_blocknr;
	वापस 0;
पूर्ण

काष्ठा buffer_head *isofs_bपढ़ो(काष्ठा inode *inode, sector_t block)
अणु
	sector_t blknr = isofs_bmap(inode, block);
	अगर (!blknr)
		वापस शून्य;
	वापस sb_bपढ़ो(inode->i_sb, blknr);
पूर्ण

अटल पूर्णांक isofs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस mpage_पढ़ोpage(page, isofs_get_block);
पूर्ण

अटल व्योम isofs_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	mpage_पढ़ोahead(rac, isofs_get_block);
पूर्ण

अटल sector_t _isofs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping,block,isofs_get_block);
पूर्ण

अटल स्थिर काष्ठा address_space_operations isofs_aops = अणु
	.पढ़ोpage = isofs_पढ़ोpage,
	.पढ़ोahead = isofs_पढ़ोahead,
	.bmap = _isofs_bmap
पूर्ण;

अटल पूर्णांक isofs_पढ़ो_level3_size(काष्ठा inode *inode)
अणु
	अचिन्हित दीर्घ bufsize = ISOFS_BUFFER_SIZE(inode);
	पूर्णांक high_sierra = ISOFS_SB(inode->i_sb)->s_high_sierra;
	काष्ठा buffer_head *bh = शून्य;
	अचिन्हित दीर्घ block, offset, block_saved, offset_saved;
	पूर्णांक i = 0;
	पूर्णांक more_entries = 0;
	काष्ठा iso_directory_record *पंचांगpde = शून्य;
	काष्ठा iso_inode_info *ei = ISOFS_I(inode);

	inode->i_size = 0;

	/* The first 16 blocks are reserved as the System Area.  Thus,
	 * no inodes can appear in block 0.  We use this to flag that
	 * this is the last section. */
	ei->i_next_section_block = 0;
	ei->i_next_section_offset = 0;

	block = ei->i_iget5_block;
	offset = ei->i_iget5_offset;

	करो अणु
		काष्ठा iso_directory_record *de;
		अचिन्हित पूर्णांक de_len;

		अगर (!bh) अणु
			bh = sb_bपढ़ो(inode->i_sb, block);
			अगर (!bh)
				जाओ out_noपढ़ो;
		पूर्ण
		de = (काष्ठा iso_directory_record *) (bh->b_data + offset);
		de_len = *(अचिन्हित अक्षर *) de;

		अगर (de_len == 0) अणु
			brअन्यथा(bh);
			bh = शून्य;
			++block;
			offset = 0;
			जारी;
		पूर्ण

		block_saved = block;
		offset_saved = offset;
		offset += de_len;

		/* Make sure we have a full directory entry */
		अगर (offset >= bufsize) अणु
			पूर्णांक slop = bufsize - offset + de_len;
			अगर (!पंचांगpde) अणु
				पंचांगpde = kदो_स्मृति(256, GFP_KERNEL);
				अगर (!पंचांगpde)
					जाओ out_nomem;
			पूर्ण
			स_नकल(पंचांगpde, de, slop);
			offset &= bufsize - 1;
			block++;
			brअन्यथा(bh);
			bh = शून्य;
			अगर (offset) अणु
				bh = sb_bपढ़ो(inode->i_sb, block);
				अगर (!bh)
					जाओ out_noपढ़ो;
				स_नकल((व्योम *)पंचांगpde+slop, bh->b_data, offset);
			पूर्ण
			de = पंचांगpde;
		पूर्ण

		inode->i_size += isonum_733(de->size);
		अगर (i == 1) अणु
			ei->i_next_section_block = block_saved;
			ei->i_next_section_offset = offset_saved;
		पूर्ण

		more_entries = de->flags[-high_sierra] & 0x80;

		i++;
		अगर (i > 100)
			जाओ out_toomany;
	पूर्ण जबतक (more_entries);
out:
	kमुक्त(पंचांगpde);
	अगर (bh)
		brअन्यथा(bh);
	वापस 0;

out_nomem:
	अगर (bh)
		brअन्यथा(bh);
	वापस -ENOMEM;

out_noपढ़ो:
	prपूर्णांकk(KERN_INFO "ISOFS: unable to read i-node block %lu\n", block);
	kमुक्त(पंचांगpde);
	वापस -EIO;

out_toomany:
	prपूर्णांकk(KERN_INFO "%s: More than 100 file sections ?!?, aborting...\n"
		"isofs_read_level3_size: inode=%lu\n",
		__func__, inode->i_ino);
	जाओ out;
पूर्ण

अटल पूर्णांक isofs_पढ़ो_inode(काष्ठा inode *inode, पूर्णांक relocated)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा isofs_sb_info *sbi = ISOFS_SB(sb);
	अचिन्हित दीर्घ bufsize = ISOFS_BUFFER_SIZE(inode);
	अचिन्हित दीर्घ block;
	पूर्णांक high_sierra = sbi->s_high_sierra;
	काष्ठा buffer_head *bh;
	काष्ठा iso_directory_record *de;
	काष्ठा iso_directory_record *पंचांगpde = शून्य;
	अचिन्हित पूर्णांक de_len;
	अचिन्हित दीर्घ offset;
	काष्ठा iso_inode_info *ei = ISOFS_I(inode);
	पूर्णांक ret = -EIO;

	block = ei->i_iget5_block;
	bh = sb_bपढ़ो(inode->i_sb, block);
	अगर (!bh)
		जाओ out_badपढ़ो;

	offset = ei->i_iget5_offset;

	de = (काष्ठा iso_directory_record *) (bh->b_data + offset);
	de_len = *(अचिन्हित अक्षर *) de;

	अगर (offset + de_len > bufsize) अणु
		पूर्णांक frag1 = bufsize - offset;

		पंचांगpde = kदो_स्मृति(de_len, GFP_KERNEL);
		अगर (!पंचांगpde) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण
		स_नकल(पंचांगpde, bh->b_data + offset, frag1);
		brअन्यथा(bh);
		bh = sb_bपढ़ो(inode->i_sb, ++block);
		अगर (!bh)
			जाओ out_badपढ़ो;
		स_नकल((अक्षर *)पंचांगpde+frag1, bh->b_data, de_len - frag1);
		de = पंचांगpde;
	पूर्ण

	inode->i_ino = isofs_get_ino(ei->i_iget5_block,
					ei->i_iget5_offset,
					ISOFS_BUFFER_BITS(inode));

	/* Assume it is a normal-क्रमmat file unless told otherwise */
	ei->i_file_क्रमmat = isofs_file_normal;

	अगर (de->flags[-high_sierra] & 2) अणु
		अगर (sbi->s_dmode != ISOFS_INVALID_MODE)
			inode->i_mode = S_IFसूची | sbi->s_dmode;
		अन्यथा
			inode->i_mode = S_IFसूची | S_IRUGO | S_IXUGO;
		set_nlink(inode, 1);	/*
					 * Set to 1.  We know there are 2, but
					 * the find utility tries to optimize
					 * अगर it is 2, and it screws up.  It is
					 * easier to give 1 which tells find to
					 * करो it the hard way.
					 */
	पूर्ण अन्यथा अणु
		अगर (sbi->s_भ_शेषe != ISOFS_INVALID_MODE) अणु
			inode->i_mode = S_IFREG | sbi->s_भ_शेषe;
		पूर्ण अन्यथा अणु
			/*
			 * Set शेष permissions: r-x क्रम all.  The disc
			 * could be shared with DOS machines so भवly
			 * anything could be a valid executable.
			 */
			inode->i_mode = S_IFREG | S_IRUGO | S_IXUGO;
		पूर्ण
		set_nlink(inode, 1);
	पूर्ण
	inode->i_uid = sbi->s_uid;
	inode->i_gid = sbi->s_gid;
	inode->i_blocks = 0;

	ei->i_क्रमmat_parm[0] = 0;
	ei->i_क्रमmat_parm[1] = 0;
	ei->i_क्रमmat_parm[2] = 0;

	ei->i_section_size = isonum_733(de->size);
	अगर (de->flags[-high_sierra] & 0x80) अणु
		ret = isofs_पढ़ो_level3_size(inode);
		अगर (ret < 0)
			जाओ fail;
		ret = -EIO;
	पूर्ण अन्यथा अणु
		ei->i_next_section_block = 0;
		ei->i_next_section_offset = 0;
		inode->i_size = isonum_733(de->size);
	पूर्ण

	/*
	 * Some dipshit decided to store some other bit of inक्रमmation
	 * in the high byte of the file length.  Truncate size in हाल
	 * this CDROM was mounted with the cruft option.
	 */

	अगर (sbi->s_cruft)
		inode->i_size &= 0x00ffffff;

	अगर (de->पूर्णांकerleave[0]) अणु
		prपूर्णांकk(KERN_DEBUG "ISOFS: Interleaved files not (yet) supported.\n");
		inode->i_size = 0;
	पूर्ण

	/* I have no idea what file_unit_size is used क्रम, so
	   we will flag it क्रम now */
	अगर (de->file_unit_size[0] != 0) अणु
		prपूर्णांकk(KERN_DEBUG "ISOFS: File unit size != 0 for ISO file (%ld).\n",
			inode->i_ino);
	पूर्ण

	/* I have no idea what other flag bits are used क्रम, so
	   we will flag it क्रम now */
#अगर_घोषित DEBUG
	अगर((de->flags[-high_sierra] & ~2)!= 0)अणु
		prपूर्णांकk(KERN_DEBUG "ISOFS: Unusual flag settings for ISO file "
				"(%ld %x).\n",
			inode->i_ino, de->flags[-high_sierra]);
	पूर्ण
#पूर्ण_अगर

	inode->i_mसमय.tv_sec =
	inode->i_aसमय.tv_sec =
	inode->i_स_समय.tv_sec = iso_date(de->date, high_sierra);
	inode->i_mसमय.tv_nsec =
	inode->i_aसमय.tv_nsec =
	inode->i_स_समय.tv_nsec = 0;

	ei->i_first_extent = (isonum_733(de->extent) +
			isonum_711(de->ext_attr_length));

	/* Set the number of blocks क्रम stat() - should be करोne beक्रमe RR */
	inode->i_blocks = (inode->i_size + 511) >> 9;

	/*
	 * Now test क्रम possible Rock Ridge extensions which will override
	 * some of these numbers in the inode काष्ठाure.
	 */

	अगर (!high_sierra) अणु
		parse_rock_ridge_inode(de, inode, relocated);
		/* अगर we want uid/gid set, override the rock ridge setting */
		अगर (sbi->s_uid_set)
			inode->i_uid = sbi->s_uid;
		अगर (sbi->s_gid_set)
			inode->i_gid = sbi->s_gid;
	पूर्ण
	/* Now set final access rights अगर overriding rock ridge setting */
	अगर (S_ISसूची(inode->i_mode) && sbi->s_overriderockperm &&
	    sbi->s_dmode != ISOFS_INVALID_MODE)
		inode->i_mode = S_IFसूची | sbi->s_dmode;
	अगर (S_ISREG(inode->i_mode) && sbi->s_overriderockperm &&
	    sbi->s_भ_शेषe != ISOFS_INVALID_MODE)
		inode->i_mode = S_IFREG | sbi->s_भ_शेषe;

	/* Install the inode operations vector */
	अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_fop = &generic_ro_fops;
		चयन (ei->i_file_क्रमmat) अणु
#अगर_घोषित CONFIG_ZISOFS
		हाल isofs_file_compressed:
			inode->i_data.a_ops = &zisofs_aops;
			अवरोध;
#पूर्ण_अगर
		शेष:
			inode->i_data.a_ops = &isofs_aops;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = &isofs_dir_inode_operations;
		inode->i_fop = &isofs_dir_operations;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		inode->i_op = &page_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_data.a_ops = &isofs_symlink_aops;
	पूर्ण अन्यथा
		/* XXX - parse_rock_ridge_inode() had alपढ़ोy set i_rdev. */
		init_special_inode(inode, inode->i_mode, inode->i_rdev);

	ret = 0;
out:
	kमुक्त(पंचांगpde);
	अगर (bh)
		brअन्यथा(bh);
	वापस ret;

out_badपढ़ो:
	prपूर्णांकk(KERN_WARNING "ISOFS: unable to read i-node block\n");
fail:
	जाओ out;
पूर्ण

काष्ठा isofs_iget5_callback_data अणु
	अचिन्हित दीर्घ block;
	अचिन्हित दीर्घ offset;
पूर्ण;

अटल पूर्णांक isofs_iget5_test(काष्ठा inode *ino, व्योम *data)
अणु
	काष्ठा iso_inode_info *i = ISOFS_I(ino);
	काष्ठा isofs_iget5_callback_data *d =
		(काष्ठा isofs_iget5_callback_data*)data;
	वापस (i->i_iget5_block == d->block)
		&& (i->i_iget5_offset == d->offset);
पूर्ण

अटल पूर्णांक isofs_iget5_set(काष्ठा inode *ino, व्योम *data)
अणु
	काष्ठा iso_inode_info *i = ISOFS_I(ino);
	काष्ठा isofs_iget5_callback_data *d =
		(काष्ठा isofs_iget5_callback_data*)data;
	i->i_iget5_block = d->block;
	i->i_iget5_offset = d->offset;
	वापस 0;
पूर्ण

/* Store, in the inode's containing काष्ठाure, the block and block
 * offset that poपूर्णांक to the underlying meta-data क्रम the inode.  The
 * code below is otherwise similar to the iget() code in
 * include/linux/fs.h */
काष्ठा inode *__isofs_iget(काष्ठा super_block *sb,
			   अचिन्हित दीर्घ block,
			   अचिन्हित दीर्घ offset,
			   पूर्णांक relocated)
अणु
	अचिन्हित दीर्घ hashval;
	काष्ठा inode *inode;
	काष्ठा isofs_iget5_callback_data data;
	दीर्घ ret;

	अगर (offset >= 1ul << sb->s_blocksize_bits)
		वापस ERR_PTR(-EINVAL);

	data.block = block;
	data.offset = offset;

	hashval = (block << sb->s_blocksize_bits) | offset;

	inode = iget5_locked(sb, hashval, &isofs_iget5_test,
				&isofs_iget5_set, &data);

	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	अगर (inode->i_state & I_NEW) अणु
		ret = isofs_पढ़ो_inode(inode, relocated);
		अगर (ret < 0) अणु
			iget_failed(inode);
			inode = ERR_PTR(ret);
		पूर्ण अन्यथा अणु
			unlock_new_inode(inode);
		पूर्ण
	पूर्ण

	वापस inode;
पूर्ण

अटल काष्ठा dentry *isofs_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, isofs_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type iso9660_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "iso9660",
	.mount		= isofs_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("iso9660");
MODULE_ALIAS("iso9660");

अटल पूर्णांक __init init_iso9660_fs(व्योम)
अणु
	पूर्णांक err = init_inodecache();
	अगर (err)
		जाओ out;
#अगर_घोषित CONFIG_ZISOFS
	err = zisofs_init();
	अगर (err)
		जाओ out1;
#पूर्ण_अगर
	err = रेजिस्टर_fileप्रणाली(&iso9660_fs_type);
	अगर (err)
		जाओ out2;
	वापस 0;
out2:
#अगर_घोषित CONFIG_ZISOFS
	zisofs_cleanup();
out1:
#पूर्ण_अगर
	destroy_inodecache();
out:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_iso9660_fs(व्योम)
अणु
        unरेजिस्टर_fileप्रणाली(&iso9660_fs_type);
#अगर_घोषित CONFIG_ZISOFS
	zisofs_cleanup();
#पूर्ण_अगर
	destroy_inodecache();
पूर्ण

module_init(init_iso9660_fs)
module_निकास(निकास_iso9660_fs)
MODULE_LICENSE("GPL");
