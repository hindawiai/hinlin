<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/adfs/super.c
 *
 *  Copyright (C) 1997-1999 Russell King
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/parser.h>
#समावेश <linux/mount.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/statfs.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/blkdev.h>
#समावेश "adfs.h"
#समावेश "dir_f.h"
#समावेश "dir_fplus.h"

#घोषणा ADFS_SB_FLAGS SB_NOATIME

#घोषणा ADFS_DEFAULT_OWNER_MASK S_IRWXU
#घोषणा ADFS_DEFAULT_OTHER_MASK (S_IRWXG | S_IRWXO)

व्योम __adfs_error(काष्ठा super_block *sb, स्थिर अक्षर *function, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk(KERN_CRIT "ADFS-fs error (device %s)%s%s: %pV\n",
		sb->s_id, function ? ": " : "",
		function ? function : "", &vaf);

	बहु_पूर्ण(args);
पूर्ण

व्योम adfs_msg(काष्ठा super_block *sb, स्थिर अक्षर *pfx, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);
	vaf.fmt = fmt;
	vaf.va = &args;
	prपूर्णांकk("%sADFS-fs (%s): %pV\n", pfx, sb->s_id, &vaf);
	बहु_पूर्ण(args);
पूर्ण

अटल पूर्णांक adfs_checkdiscrecord(काष्ठा adfs_discrecord *dr)
अणु
	अचिन्हित पूर्णांक max_idlen;
	पूर्णांक i;

	/* sector size must be 256, 512 or 1024 bytes */
	अगर (dr->log2secsize != 8 &&
	    dr->log2secsize != 9 &&
	    dr->log2secsize != 10)
		वापस 1;

	/* idlen must be at least log2secsize + 3 */
	अगर (dr->idlen < dr->log2secsize + 3)
		वापस 1;

	/* we cannot have such a large disc that we
	 * are unable to represent sector offsets in
	 * 32 bits.  This works out at 2.0 TB.
	 */
	अगर (le32_to_cpu(dr->disc_size_high) >> dr->log2secsize)
		वापस 1;

	/*
	 * Maximum idlen is limited to 16 bits क्रम new directories by
	 * the three-byte storage of an indirect disc address.  For
	 * big directories, idlen must be no greater than 19 v2 [1.0]
	 */
	max_idlen = dr->क्रमmat_version ? 19 : 16;
	अगर (dr->idlen > max_idlen)
		वापस 1;

	/* reserved bytes should be zero */
	क्रम (i = 0; i < माप(dr->unused52); i++)
		अगर (dr->unused52[i] != 0)
			वापस 1;

	वापस 0;
पूर्ण

अटल व्योम adfs_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा adfs_sb_info *asb = ADFS_SB(sb);

	adfs_मुक्त_map(sb);
	kमुक्त_rcu(asb, rcu);
पूर्ण

अटल पूर्णांक adfs_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा adfs_sb_info *asb = ADFS_SB(root->d_sb);

	अगर (!uid_eq(asb->s_uid, GLOBAL_ROOT_UID))
		seq_म_लिखो(seq, ",uid=%u", from_kuid_munged(&init_user_ns, asb->s_uid));
	अगर (!gid_eq(asb->s_gid, GLOBAL_ROOT_GID))
		seq_म_लिखो(seq, ",gid=%u", from_kgid_munged(&init_user_ns, asb->s_gid));
	अगर (asb->s_owner_mask != ADFS_DEFAULT_OWNER_MASK)
		seq_म_लिखो(seq, ",ownmask=%o", asb->s_owner_mask);
	अगर (asb->s_other_mask != ADFS_DEFAULT_OTHER_MASK)
		seq_म_लिखो(seq, ",othmask=%o", asb->s_other_mask);
	अगर (asb->s_ftsuffix != 0)
		seq_म_लिखो(seq, ",ftsuffix=%u", asb->s_ftsuffix);

	वापस 0;
पूर्ण

क्रमागत अणुOpt_uid, Opt_gid, Opt_ownmask, Opt_othmask, Opt_ftsuffix, Opt_errपूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_uid, "uid=%u"पूर्ण,
	अणुOpt_gid, "gid=%u"पूर्ण,
	अणुOpt_ownmask, "ownmask=%o"पूर्ण,
	अणुOpt_othmask, "othmask=%o"पूर्ण,
	अणुOpt_ftsuffix, "ftsuffix=%u"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक parse_options(काष्ठा super_block *sb, काष्ठा adfs_sb_info *asb,
			 अक्षर *options)
अणु
	अक्षर *p;
	पूर्णांक option;

	अगर (!options)
		वापस 0;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		substring_t args[MAX_OPT_ARGS];
		पूर्णांक token;
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_uid:
			अगर (match_पूर्णांक(args, &option))
				वापस -EINVAL;
			asb->s_uid = make_kuid(current_user_ns(), option);
			अगर (!uid_valid(asb->s_uid))
				वापस -EINVAL;
			अवरोध;
		हाल Opt_gid:
			अगर (match_पूर्णांक(args, &option))
				वापस -EINVAL;
			asb->s_gid = make_kgid(current_user_ns(), option);
			अगर (!gid_valid(asb->s_gid))
				वापस -EINVAL;
			अवरोध;
		हाल Opt_ownmask:
			अगर (match_octal(args, &option))
				वापस -EINVAL;
			asb->s_owner_mask = option;
			अवरोध;
		हाल Opt_othmask:
			अगर (match_octal(args, &option))
				वापस -EINVAL;
			asb->s_other_mask = option;
			अवरोध;
		हाल Opt_ftsuffix:
			अगर (match_पूर्णांक(args, &option))
				वापस -EINVAL;
			asb->s_ftsuffix = option;
			अवरोध;
		शेष:
			adfs_msg(sb, KERN_ERR,
				 "unrecognised mount option \"%s\" or missing value",
				 p);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक adfs_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	काष्ठा adfs_sb_info temp_asb;
	पूर्णांक ret;

	sync_fileप्रणाली(sb);
	*flags |= ADFS_SB_FLAGS;

	temp_asb = *ADFS_SB(sb);
	ret = parse_options(sb, &temp_asb, data);
	अगर (ret == 0)
		*ADFS_SB(sb) = temp_asb;

	वापस ret;
पूर्ण

अटल पूर्णांक adfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा adfs_sb_info *sbi = ADFS_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	adfs_map_statfs(sb, buf);

	buf->f_type    = ADFS_SUPER_MAGIC;
	buf->f_namelen = sbi->s_namelen;
	buf->f_bsize   = sb->s_blocksize;
	buf->f_fमुक्त   = (दीर्घ)(buf->f_bमुक्त * buf->f_files) / (दीर्घ)buf->f_blocks;
	buf->f_fsid    = u64_to_fsid(id);

	वापस 0;
पूर्ण

अटल काष्ठा kmem_cache *adfs_inode_cachep;

अटल काष्ठा inode *adfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा adfs_inode_info *ei;
	ei = kmem_cache_alloc(adfs_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;
	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम adfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(adfs_inode_cachep, ADFS_I(inode));
पूर्ण

अटल पूर्णांक adfs_drop_inode(काष्ठा inode *inode)
अणु
	/* always drop inodes अगर we are पढ़ो-only */
	वापस !IS_ENABLED(CONFIG_ADFS_FS_RW) || IS_RDONLY(inode);
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा adfs_inode_info *ei = (काष्ठा adfs_inode_info *) foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_inodecache(व्योम)
अणु
	adfs_inode_cachep = kmem_cache_create("adfs_inode_cache",
					     माप(काष्ठा adfs_inode_info),
					     0, (SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					     init_once);
	अगर (adfs_inode_cachep == शून्य)
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
	kmem_cache_destroy(adfs_inode_cachep);
पूर्ण

अटल स्थिर काष्ठा super_operations adfs_sops = अणु
	.alloc_inode	= adfs_alloc_inode,
	.मुक्त_inode	= adfs_मुक्त_inode,
	.drop_inode	= adfs_drop_inode,
	.ग_लिखो_inode	= adfs_ग_लिखो_inode,
	.put_super	= adfs_put_super,
	.statfs		= adfs_statfs,
	.remount_fs	= adfs_remount,
	.show_options	= adfs_show_options,
पूर्ण;

अटल पूर्णांक adfs_probe(काष्ठा super_block *sb, अचिन्हित पूर्णांक offset, पूर्णांक silent,
		      पूर्णांक (*validate)(काष्ठा super_block *sb,
				      काष्ठा buffer_head *bh,
				      काष्ठा adfs_discrecord **bhp))
अणु
	काष्ठा adfs_sb_info *asb = ADFS_SB(sb);
	काष्ठा adfs_discrecord *dr;
	काष्ठा buffer_head *bh;
	अचिन्हित पूर्णांक blocksize = BLOCK_SIZE;
	पूर्णांक ret, try;

	क्रम (try = 0; try < 2; try++) अणु
		/* try to set the requested block size */
		अगर (sb->s_blocksize != blocksize &&
		    !sb_set_blocksize(sb, blocksize)) अणु
			अगर (!silent)
				adfs_msg(sb, KERN_ERR,
					 "error: unsupported blocksize");
			वापस -EINVAL;
		पूर्ण

		/* पढ़ो the buffer */
		bh = sb_bपढ़ो(sb, offset >> sb->s_blocksize_bits);
		अगर (!bh) अणु
			adfs_msg(sb, KERN_ERR,
				 "error: unable to read block %u, try %d",
				 offset >> sb->s_blocksize_bits, try);
			वापस -EIO;
		पूर्ण

		/* validate it */
		ret = validate(sb, bh, &dr);
		अगर (ret) अणु
			brअन्यथा(bh);
			वापस ret;
		पूर्ण

		/* करोes the block size match the fileप्रणाली block size? */
		blocksize = 1 << dr->log2secsize;
		अगर (sb->s_blocksize == blocksize) अणु
			asb->s_map = adfs_पढ़ो_map(sb, dr);
			brअन्यथा(bh);
			वापस PTR_ERR_OR_ZERO(asb->s_map);
		पूर्ण

		brअन्यथा(bh);
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक adfs_validate_bblk(काष्ठा super_block *sb, काष्ठा buffer_head *bh,
			      काष्ठा adfs_discrecord **drp)
अणु
	काष्ठा adfs_discrecord *dr;
	अचिन्हित अक्षर *b_data;

	b_data = bh->b_data + (ADFS_DISCRECORD % sb->s_blocksize);
	अगर (adfs_checkbblk(b_data))
		वापस -EILSEQ;

	/* Do some sanity checks on the ADFS disc record */
	dr = (काष्ठा adfs_discrecord *)(b_data + ADFS_DR_OFFSET);
	अगर (adfs_checkdiscrecord(dr))
		वापस -EILSEQ;

	*drp = dr;
	वापस 0;
पूर्ण

अटल पूर्णांक adfs_validate_dr0(काष्ठा super_block *sb, काष्ठा buffer_head *bh,
			      काष्ठा adfs_discrecord **drp)
अणु
	काष्ठा adfs_discrecord *dr;

	/* Do some sanity checks on the ADFS disc record */
	dr = (काष्ठा adfs_discrecord *)(bh->b_data + 4);
	अगर (adfs_checkdiscrecord(dr) || dr->nzones_high || dr->nzones != 1)
		वापस -EILSEQ;

	*drp = dr;
	वापस 0;
पूर्ण

अटल पूर्णांक adfs_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा adfs_discrecord *dr;
	काष्ठा object_info root_obj;
	काष्ठा adfs_sb_info *asb;
	काष्ठा inode *root;
	पूर्णांक ret = -EINVAL;

	sb->s_flags |= ADFS_SB_FLAGS;

	asb = kzalloc(माप(*asb), GFP_KERNEL);
	अगर (!asb)
		वापस -ENOMEM;

	sb->s_fs_info = asb;
	sb->s_magic = ADFS_SUPER_MAGIC;
	sb->s_समय_gran = 10000000;

	/* set शेष options */
	asb->s_uid = GLOBAL_ROOT_UID;
	asb->s_gid = GLOBAL_ROOT_GID;
	asb->s_owner_mask = ADFS_DEFAULT_OWNER_MASK;
	asb->s_other_mask = ADFS_DEFAULT_OTHER_MASK;
	asb->s_ftsuffix = 0;

	अगर (parse_options(sb, asb, data))
		जाओ error;

	/* Try to probe the fileप्रणाली boot block */
	ret = adfs_probe(sb, ADFS_DISCRECORD, 1, adfs_validate_bblk);
	अगर (ret == -EILSEQ)
		ret = adfs_probe(sb, 0, silent, adfs_validate_dr0);
	अगर (ret == -EILSEQ) अणु
		अगर (!silent)
			adfs_msg(sb, KERN_ERR,
				 "error: can't find an ADFS filesystem on dev %s.",
				 sb->s_id);
		ret = -EINVAL;
	पूर्ण
	अगर (ret)
		जाओ error;

	/* set up enough so that we can पढ़ो an inode */
	sb->s_op = &adfs_sops;

	dr = adfs_map_discrecord(asb->s_map);

	root_obj.parent_id = root_obj.indaddr = le32_to_cpu(dr->root);
	root_obj.name_len  = 0;
	/* Set root object date as 01 Jan 1987 00:00:00 */
	root_obj.loadaddr  = 0xfff0003f;
	root_obj.execaddr  = 0xec22c000;
	root_obj.size	   = ADFS_NEWसूची_SIZE;
	root_obj.attr	   = ADFS_NDA_सूचीECTORY   | ADFS_NDA_OWNER_READ |
			     ADFS_NDA_OWNER_WRITE | ADFS_NDA_PUBLIC_READ;

	/*
	 * If this is a F+ disk with variable length directories,
	 * get the root_size from the disc record.
	 */
	अगर (dr->क्रमmat_version) अणु
		root_obj.size = le32_to_cpu(dr->root_size);
		asb->s_dir     = &adfs_fplus_dir_ops;
		asb->s_namelen = ADFS_FPLUS_NAME_LEN;
	पूर्ण अन्यथा अणु
		asb->s_dir     = &adfs_f_dir_ops;
		asb->s_namelen = ADFS_F_NAME_LEN;
	पूर्ण
	/*
	 * ,xyz hex filetype suffix may be added by driver
	 * to files that have valid RISC OS filetype
	 */
	अगर (asb->s_ftsuffix)
		asb->s_namelen += 4;

	sb->s_d_op = &adfs_dentry_operations;
	root = adfs_iget(sb, &root_obj);
	sb->s_root = d_make_root(root);
	अगर (!sb->s_root) अणु
		adfs_मुक्त_map(sb);
		adfs_error(sb, "get root inode failed\n");
		ret = -EIO;
		जाओ error;
	पूर्ण
	वापस 0;

error:
	sb->s_fs_info = शून्य;
	kमुक्त(asb);
	वापस ret;
पूर्ण

अटल काष्ठा dentry *adfs_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, adfs_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type adfs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "adfs",
	.mount		= adfs_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("adfs");

अटल पूर्णांक __init init_adfs_fs(व्योम)
अणु
	पूर्णांक err = init_inodecache();
	अगर (err)
		जाओ out1;
	err = रेजिस्टर_fileप्रणाली(&adfs_fs_type);
	अगर (err)
		जाओ out;
	वापस 0;
out:
	destroy_inodecache();
out1:
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_adfs_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&adfs_fs_type);
	destroy_inodecache();
पूर्ण

module_init(init_adfs_fs)
module_निकास(निकास_adfs_fs)
MODULE_LICENSE("GPL");
