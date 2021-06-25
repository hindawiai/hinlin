<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QNX6 file प्रणाली, Linux implementation.
 *
 * Version : 1.0.0
 *
 * History :
 *
 * 01-02-2012 by Kai Bankett (chaosman@ontika.net) : first release.
 * 16-02-2012 pagemap extension by Al Viro
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/highuid.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/statfs.h>
#समावेश <linux/parser.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mount.h>
#समावेश <linux/crc32.h>
#समावेश <linux/mpage.h>
#समावेश "qnx6.h"

अटल स्थिर काष्ठा super_operations qnx6_sops;

अटल व्योम qnx6_put_super(काष्ठा super_block *sb);
अटल काष्ठा inode *qnx6_alloc_inode(काष्ठा super_block *sb);
अटल व्योम qnx6_मुक्त_inode(काष्ठा inode *inode);
अटल पूर्णांक qnx6_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data);
अटल पूर्णांक qnx6_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf);
अटल पूर्णांक qnx6_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root);

अटल स्थिर काष्ठा super_operations qnx6_sops = अणु
	.alloc_inode	= qnx6_alloc_inode,
	.मुक्त_inode	= qnx6_मुक्त_inode,
	.put_super	= qnx6_put_super,
	.statfs		= qnx6_statfs,
	.remount_fs	= qnx6_remount,
	.show_options	= qnx6_show_options,
पूर्ण;

अटल पूर्णांक qnx6_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा super_block *sb = root->d_sb;
	काष्ठा qnx6_sb_info *sbi = QNX6_SB(sb);

	अगर (sbi->s_mount_opt & QNX6_MOUNT_MMI_FS)
		seq_माला_दो(seq, ",mmi_fs");
	वापस 0;
पूर्ण

अटल पूर्णांक qnx6_remount(काष्ठा super_block *sb, पूर्णांक *flags, अक्षर *data)
अणु
	sync_fileप्रणाली(sb);
	*flags |= SB_RDONLY;
	वापस 0;
पूर्ण

अटल अचिन्हित qnx6_get_devblock(काष्ठा super_block *sb, __fs32 block)
अणु
	काष्ठा qnx6_sb_info *sbi = QNX6_SB(sb);
	वापस fs32_to_cpu(sbi, block) + sbi->s_blks_off;
पूर्ण

अटल अचिन्हित qnx6_block_map(काष्ठा inode *inode, अचिन्हित iblock);

अटल पूर्णांक qnx6_get_block(काष्ठा inode *inode, sector_t iblock,
			काष्ठा buffer_head *bh, पूर्णांक create)
अणु
	अचिन्हित phys;

	pr_debug("qnx6_get_block inode=[%ld] iblock=[%ld]\n",
		 inode->i_ino, (अचिन्हित दीर्घ)iblock);

	phys = qnx6_block_map(inode, iblock);
	अगर (phys) अणु
		/* logical block is beक्रमe खातापूर्ण */
		map_bh(bh, inode->i_sb, phys);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qnx6_check_blockptr(__fs32 ptr)
अणु
	अगर (ptr == ~(__fs32)0) अणु
		pr_err("hit unused blockpointer.\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक qnx6_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस mpage_पढ़ोpage(page, qnx6_get_block);
पूर्ण

अटल व्योम qnx6_पढ़ोahead(काष्ठा पढ़ोahead_control *rac)
अणु
	mpage_पढ़ोahead(rac, qnx6_get_block);
पूर्ण

/*
 * वापसs the block number क्रम the no-th element in the tree
 * inodebits requred as there are multiple inodes in one inode block
 */
अटल अचिन्हित qnx6_block_map(काष्ठा inode *inode, अचिन्हित no)
अणु
	काष्ठा super_block *s = inode->i_sb;
	काष्ठा qnx6_sb_info *sbi = QNX6_SB(s);
	काष्ठा qnx6_inode_info *ei = QNX6_I(inode);
	अचिन्हित block = 0;
	काष्ठा buffer_head *bh;
	__fs32 ptr;
	पूर्णांक levelptr;
	पूर्णांक ptrbits = sbi->s_ptrbits;
	पूर्णांक bitdelta;
	u32 mask = (1 << ptrbits) - 1;
	पूर्णांक depth = ei->di_filelevels;
	पूर्णांक i;

	bitdelta = ptrbits * depth;
	levelptr = no >> bitdelta;

	अगर (levelptr > QNX6_NO_सूचीECT_POINTERS - 1) अणु
		pr_err("Requested file block number (%u) too big.", no);
		वापस 0;
	पूर्ण

	block = qnx6_get_devblock(s, ei->di_block_ptr[levelptr]);

	क्रम (i = 0; i < depth; i++) अणु
		bh = sb_bपढ़ो(s, block);
		अगर (!bh) अणु
			pr_err("Error reading block (%u)\n", block);
			वापस 0;
		पूर्ण
		bitdelta -= ptrbits;
		levelptr = (no >> bitdelta) & mask;
		ptr = ((__fs32 *)bh->b_data)[levelptr];

		अगर (!qnx6_check_blockptr(ptr))
			वापस 0;

		block = qnx6_get_devblock(s, ptr);
		brअन्यथा(bh);
	पूर्ण
	वापस block;
पूर्ण

अटल पूर्णांक qnx6_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	काष्ठा qnx6_sb_info *sbi = QNX6_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type    = sb->s_magic;
	buf->f_bsize   = sb->s_blocksize;
	buf->f_blocks  = fs32_to_cpu(sbi, sbi->sb->sb_num_blocks);
	buf->f_bमुक्त   = fs32_to_cpu(sbi, sbi->sb->sb_मुक्त_blocks);
	buf->f_files   = fs32_to_cpu(sbi, sbi->sb->sb_num_inodes);
	buf->f_fमुक्त   = fs32_to_cpu(sbi, sbi->sb->sb_मुक्त_inodes);
	buf->f_bavail  = buf->f_bमुक्त;
	buf->f_namelen = QNX6_LONG_NAME_MAX;
	buf->f_fsid    = u64_to_fsid(id);

	वापस 0;
पूर्ण

/*
 * Check the root directory of the fileप्रणाली to make sure
 * it really _is_ a qnx6 fileप्रणाली, and to check the size
 * of the directory entry.
 */
अटल स्थिर अक्षर *qnx6_checkroot(काष्ठा super_block *s)
अणु
	अटल अक्षर match_root[2][3] = अणु".\0\0", "..\0"पूर्ण;
	पूर्णांक i, error = 0;
	काष्ठा qnx6_dir_entry *dir_entry;
	काष्ठा inode *root = d_inode(s->s_root);
	काष्ठा address_space *mapping = root->i_mapping;
	काष्ठा page *page = पढ़ो_mapping_page(mapping, 0, शून्य);
	अगर (IS_ERR(page))
		वापस "error reading root directory";
	kmap(page);
	dir_entry = page_address(page);
	क्रम (i = 0; i < 2; i++) अणु
		/* maximum 3 bytes - due to match_root limitation */
		अगर (म_भेदन(dir_entry[i].de_fname, match_root[i], 3))
			error = 1;
	पूर्ण
	qnx6_put_page(page);
	अगर (error)
		वापस "error reading root directory.";
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_QNX6FS_DEBUG
व्योम qnx6_superblock_debug(काष्ठा qnx6_super_block *sb, काष्ठा super_block *s)
अणु
	काष्ठा qnx6_sb_info *sbi = QNX6_SB(s);

	pr_debug("magic: %08x\n", fs32_to_cpu(sbi, sb->sb_magic));
	pr_debug("checksum: %08x\n", fs32_to_cpu(sbi, sb->sb_checksum));
	pr_debug("serial: %llx\n", fs64_to_cpu(sbi, sb->sb_serial));
	pr_debug("flags: %08x\n", fs32_to_cpu(sbi, sb->sb_flags));
	pr_debug("blocksize: %08x\n", fs32_to_cpu(sbi, sb->sb_blocksize));
	pr_debug("num_inodes: %08x\n", fs32_to_cpu(sbi, sb->sb_num_inodes));
	pr_debug("free_inodes: %08x\n", fs32_to_cpu(sbi, sb->sb_मुक्त_inodes));
	pr_debug("num_blocks: %08x\n", fs32_to_cpu(sbi, sb->sb_num_blocks));
	pr_debug("free_blocks: %08x\n", fs32_to_cpu(sbi, sb->sb_मुक्त_blocks));
	pr_debug("inode_levels: %02x\n", sb->Inode.levels);
पूर्ण
#पूर्ण_अगर

क्रमागत अणु
	Opt_mmअगरs,
	Opt_err
पूर्ण;

अटल स्थिर match_table_t tokens = अणु
	अणुOpt_mmअगरs, "mmi_fs"पूर्ण,
	अणुOpt_err, शून्यपूर्ण
पूर्ण;

अटल पूर्णांक qnx6_parse_options(अक्षर *options, काष्ठा super_block *sb)
अणु
	अक्षर *p;
	काष्ठा qnx6_sb_info *sbi = QNX6_SB(sb);
	substring_t args[MAX_OPT_ARGS];

	अगर (!options)
		वापस 1;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;
		अगर (!*p)
			जारी;

		token = match_token(p, tokens, args);
		चयन (token) अणु
		हाल Opt_mmअगरs:
			set_opt(sbi->s_mount_opt, MMI_FS);
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल काष्ठा buffer_head *qnx6_check_first_superblock(काष्ठा super_block *s,
				पूर्णांक offset, पूर्णांक silent)
अणु
	काष्ठा qnx6_sb_info *sbi = QNX6_SB(s);
	काष्ठा buffer_head *bh;
	काष्ठा qnx6_super_block *sb;

	/* Check the superblock signatures
	   start with the first superblock */
	bh = sb_bपढ़ो(s, offset);
	अगर (!bh) अणु
		pr_err("unable to read the first superblock\n");
		वापस शून्य;
	पूर्ण
	sb = (काष्ठा qnx6_super_block *)bh->b_data;
	अगर (fs32_to_cpu(sbi, sb->sb_magic) != QNX6_SUPER_MAGIC) अणु
		sbi->s_bytesex = BYTESEX_BE;
		अगर (fs32_to_cpu(sbi, sb->sb_magic) == QNX6_SUPER_MAGIC) अणु
			/* we got a big endian fs */
			pr_debug("fs got different endianness.\n");
			वापस bh;
		पूर्ण अन्यथा
			sbi->s_bytesex = BYTESEX_LE;
		अगर (!silent) अणु
			अगर (offset == 0) अणु
				pr_err("wrong signature (magic) in superblock #1.\n");
			पूर्ण अन्यथा अणु
				pr_info("wrong signature (magic) at position (0x%lx) - will try alternative position (0x0000).\n",
					offset * s->s_blocksize);
			पूर्ण
		पूर्ण
		brअन्यथा(bh);
		वापस शून्य;
	पूर्ण
	वापस bh;
पूर्ण

अटल काष्ठा inode *qnx6_निजी_inode(काष्ठा super_block *s,
					काष्ठा qnx6_root_node *p);

अटल पूर्णांक qnx6_fill_super(काष्ठा super_block *s, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा buffer_head *bh1 = शून्य, *bh2 = शून्य;
	काष्ठा qnx6_super_block *sb1 = शून्य, *sb2 = शून्य;
	काष्ठा qnx6_sb_info *sbi;
	काष्ठा inode *root;
	स्थिर अक्षर *errmsg;
	काष्ठा qnx6_sb_info *qs;
	पूर्णांक ret = -EINVAL;
	u64 offset;
	पूर्णांक bootblock_offset = QNX6_BOOTBLOCK_SIZE;

	qs = kzalloc(माप(काष्ठा qnx6_sb_info), GFP_KERNEL);
	अगर (!qs)
		वापस -ENOMEM;
	s->s_fs_info = qs;

	/* Superblock always is 512 Byte दीर्घ */
	अगर (!sb_set_blocksize(s, QNX6_SUPERBLOCK_SIZE)) अणु
		pr_err("unable to set blocksize\n");
		जाओ outnobh;
	पूर्ण

	/* parse the mount-options */
	अगर (!qnx6_parse_options((अक्षर *) data, s)) अणु
		pr_err("invalid mount options.\n");
		जाओ outnobh;
	पूर्ण
	अगर (test_opt(s, MMI_FS)) अणु
		sb1 = qnx6_mmi_fill_super(s, silent);
		अगर (sb1)
			जाओ mmi_success;
		अन्यथा
			जाओ outnobh;
	पूर्ण
	sbi = QNX6_SB(s);
	sbi->s_bytesex = BYTESEX_LE;
	/* Check the superblock signatures
	   start with the first superblock */
	bh1 = qnx6_check_first_superblock(s,
		bootblock_offset / QNX6_SUPERBLOCK_SIZE, silent);
	अगर (!bh1) अणु
		/* try again without bootblock offset */
		bh1 = qnx6_check_first_superblock(s, 0, silent);
		अगर (!bh1) अणु
			pr_err("unable to read the first superblock\n");
			जाओ outnobh;
		पूर्ण
		/* seems that no bootblock at partition start */
		bootblock_offset = 0;
	पूर्ण
	sb1 = (काष्ठा qnx6_super_block *)bh1->b_data;

#अगर_घोषित CONFIG_QNX6FS_DEBUG
	qnx6_superblock_debug(sb1, s);
#पूर्ण_अगर

	/* checksum check - start at byte 8 and end at byte 512 */
	अगर (fs32_to_cpu(sbi, sb1->sb_checksum) !=
			crc32_be(0, (अक्षर *)(bh1->b_data + 8), 504)) अणु
		pr_err("superblock #1 checksum error\n");
		जाओ out;
	पूर्ण

	/* set new blocksize */
	अगर (!sb_set_blocksize(s, fs32_to_cpu(sbi, sb1->sb_blocksize))) अणु
		pr_err("unable to set blocksize\n");
		जाओ out;
	पूर्ण
	/* blocksize invalidates bh - pull it back in */
	brअन्यथा(bh1);
	bh1 = sb_bपढ़ो(s, bootblock_offset >> s->s_blocksize_bits);
	अगर (!bh1)
		जाओ outnobh;
	sb1 = (काष्ठा qnx6_super_block *)bh1->b_data;

	/* calculate second superblock blocknumber */
	offset = fs32_to_cpu(sbi, sb1->sb_num_blocks) +
		(bootblock_offset >> s->s_blocksize_bits) +
		(QNX6_SUPERBLOCK_AREA >> s->s_blocksize_bits);

	/* set bootblock offset */
	sbi->s_blks_off = (bootblock_offset >> s->s_blocksize_bits) +
			  (QNX6_SUPERBLOCK_AREA >> s->s_blocksize_bits);

	/* next the second superblock */
	bh2 = sb_bपढ़ो(s, offset);
	अगर (!bh2) अणु
		pr_err("unable to read the second superblock\n");
		जाओ out;
	पूर्ण
	sb2 = (काष्ठा qnx6_super_block *)bh2->b_data;
	अगर (fs32_to_cpu(sbi, sb2->sb_magic) != QNX6_SUPER_MAGIC) अणु
		अगर (!silent)
			pr_err("wrong signature (magic) in superblock #2.\n");
		जाओ out;
	पूर्ण

	/* checksum check - start at byte 8 and end at byte 512 */
	अगर (fs32_to_cpu(sbi, sb2->sb_checksum) !=
				crc32_be(0, (अक्षर *)(bh2->b_data + 8), 504)) अणु
		pr_err("superblock #2 checksum error\n");
		जाओ out;
	पूर्ण

	अगर (fs64_to_cpu(sbi, sb1->sb_serial) >=
					fs64_to_cpu(sbi, sb2->sb_serial)) अणु
		/* superblock #1 active */
		sbi->sb_buf = bh1;
		sbi->sb = (काष्ठा qnx6_super_block *)bh1->b_data;
		brअन्यथा(bh2);
		pr_info("superblock #1 active\n");
	पूर्ण अन्यथा अणु
		/* superblock #2 active */
		sbi->sb_buf = bh2;
		sbi->sb = (काष्ठा qnx6_super_block *)bh2->b_data;
		brअन्यथा(bh1);
		pr_info("superblock #2 active\n");
	पूर्ण
mmi_success:
	/* sanity check - limit maximum indirect poपूर्णांकer levels */
	अगर (sb1->Inode.levels > QNX6_PTR_MAX_LEVELS) अणु
		pr_err("too many inode levels (max %i, sb %i)\n",
		       QNX6_PTR_MAX_LEVELS, sb1->Inode.levels);
		जाओ out;
	पूर्ण
	अगर (sb1->Longfile.levels > QNX6_PTR_MAX_LEVELS) अणु
		pr_err("too many longfilename levels (max %i, sb %i)\n",
		       QNX6_PTR_MAX_LEVELS, sb1->Longfile.levels);
		जाओ out;
	पूर्ण
	s->s_op = &qnx6_sops;
	s->s_magic = QNX6_SUPER_MAGIC;
	s->s_flags |= SB_RDONLY;        /* Yup, पढ़ो-only yet */
	s->s_समय_min = 0;
	s->s_समय_max = U32_MAX;

	/* ease the later tree level calculations */
	sbi = QNX6_SB(s);
	sbi->s_ptrbits = ilog2(s->s_blocksize / 4);
	sbi->inodes = qnx6_निजी_inode(s, &sb1->Inode);
	अगर (!sbi->inodes)
		जाओ out;
	sbi->दीर्घfile = qnx6_निजी_inode(s, &sb1->Longfile);
	अगर (!sbi->दीर्घfile)
		जाओ out1;

	/* prefetch root inode */
	root = qnx6_iget(s, QNX6_ROOT_INO);
	अगर (IS_ERR(root)) अणु
		pr_err("get inode failed\n");
		ret = PTR_ERR(root);
		जाओ out2;
	पूर्ण

	ret = -ENOMEM;
	s->s_root = d_make_root(root);
	अगर (!s->s_root)
		जाओ out2;

	ret = -EINVAL;
	errmsg = qnx6_checkroot(s);
	अगर (errmsg != शून्य) अणु
		अगर (!silent)
			pr_err("%s\n", errmsg);
		जाओ out3;
	पूर्ण
	वापस 0;

out3:
	dput(s->s_root);
	s->s_root = शून्य;
out2:
	iput(sbi->दीर्घfile);
out1:
	iput(sbi->inodes);
out:
	अगर (bh1)
		brअन्यथा(bh1);
	अगर (bh2)
		brअन्यथा(bh2);
outnobh:
	kमुक्त(qs);
	s->s_fs_info = शून्य;
	वापस ret;
पूर्ण

अटल व्योम qnx6_put_super(काष्ठा super_block *sb)
अणु
	काष्ठा qnx6_sb_info *qs = QNX6_SB(sb);
	brअन्यथा(qs->sb_buf);
	iput(qs->दीर्घfile);
	iput(qs->inodes);
	kमुक्त(qs);
	sb->s_fs_info = शून्य;
	वापस;
पूर्ण

अटल sector_t qnx6_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping, block, qnx6_get_block);
पूर्ण
अटल स्थिर काष्ठा address_space_operations qnx6_aops = अणु
	.पढ़ोpage	= qnx6_पढ़ोpage,
	.पढ़ोahead	= qnx6_पढ़ोahead,
	.bmap		= qnx6_bmap
पूर्ण;

अटल काष्ठा inode *qnx6_निजी_inode(काष्ठा super_block *s,
					काष्ठा qnx6_root_node *p)
अणु
	काष्ठा inode *inode = new_inode(s);
	अगर (inode) अणु
		काष्ठा qnx6_inode_info *ei = QNX6_I(inode);
		काष्ठा qnx6_sb_info *sbi = QNX6_SB(s);
		inode->i_size = fs64_to_cpu(sbi, p->size);
		स_नकल(ei->di_block_ptr, p->ptr, माप(p->ptr));
		ei->di_filelevels = p->levels;
		inode->i_mode = S_IFREG | S_IRUSR; /* probably wrong */
		inode->i_mapping->a_ops = &qnx6_aops;
	पूर्ण
	वापस inode;
पूर्ण

काष्ठा inode *qnx6_iget(काष्ठा super_block *sb, अचिन्हित ino)
अणु
	काष्ठा qnx6_sb_info *sbi = QNX6_SB(sb);
	काष्ठा qnx6_inode_entry *raw_inode;
	काष्ठा inode *inode;
	काष्ठा qnx6_inode_info	*ei;
	काष्ठा address_space *mapping;
	काष्ठा page *page;
	u32 n, offs;

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	ei = QNX6_I(inode);

	inode->i_mode = 0;

	अगर (ino == 0) अणु
		pr_err("bad inode number on dev %s: %u is out of range\n",
		       sb->s_id, ino);
		iget_failed(inode);
		वापस ERR_PTR(-EIO);
	पूर्ण
	n = (ino - 1) >> (PAGE_SHIFT - QNX6_INODE_SIZE_BITS);
	offs = (ino - 1) & (~PAGE_MASK >> QNX6_INODE_SIZE_BITS);
	mapping = sbi->inodes->i_mapping;
	page = पढ़ो_mapping_page(mapping, n, शून्य);
	अगर (IS_ERR(page)) अणु
		pr_err("major problem: unable to read inode from dev %s\n",
		       sb->s_id);
		iget_failed(inode);
		वापस ERR_CAST(page);
	पूर्ण
	kmap(page);
	raw_inode = ((काष्ठा qnx6_inode_entry *)page_address(page)) + offs;

	inode->i_mode    = fs16_to_cpu(sbi, raw_inode->di_mode);
	i_uid_ग_लिखो(inode, (uid_t)fs32_to_cpu(sbi, raw_inode->di_uid));
	i_gid_ग_लिखो(inode, (gid_t)fs32_to_cpu(sbi, raw_inode->di_gid));
	inode->i_size    = fs64_to_cpu(sbi, raw_inode->di_size);
	inode->i_mसमय.tv_sec   = fs32_to_cpu(sbi, raw_inode->di_mसमय);
	inode->i_mसमय.tv_nsec = 0;
	inode->i_aसमय.tv_sec   = fs32_to_cpu(sbi, raw_inode->di_aसमय);
	inode->i_aसमय.tv_nsec = 0;
	inode->i_स_समय.tv_sec   = fs32_to_cpu(sbi, raw_inode->di_स_समय);
	inode->i_स_समय.tv_nsec = 0;

	/* calc blocks based on 512 byte blocksize */
	inode->i_blocks = (inode->i_size + 511) >> 9;

	स_नकल(&ei->di_block_ptr, &raw_inode->di_block_ptr,
				माप(raw_inode->di_block_ptr));
	ei->di_filelevels = raw_inode->di_filelevels;

	अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_fop = &generic_ro_fops;
		inode->i_mapping->a_ops = &qnx6_aops;
	पूर्ण अन्यथा अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op = &qnx6_dir_inode_operations;
		inode->i_fop = &qnx6_dir_operations;
		inode->i_mapping->a_ops = &qnx6_aops;
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		inode->i_op = &page_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &qnx6_aops;
	पूर्ण अन्यथा
		init_special_inode(inode, inode->i_mode, 0);
	qnx6_put_page(page);
	unlock_new_inode(inode);
	वापस inode;
पूर्ण

अटल काष्ठा kmem_cache *qnx6_inode_cachep;

अटल काष्ठा inode *qnx6_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा qnx6_inode_info *ei;
	ei = kmem_cache_alloc(qnx6_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;
	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम qnx6_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(qnx6_inode_cachep, QNX6_I(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा qnx6_inode_info *ei = (काष्ठा qnx6_inode_info *) foo;

	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक init_inodecache(व्योम)
अणु
	qnx6_inode_cachep = kmem_cache_create("qnx6_inode_cache",
					     माप(काष्ठा qnx6_inode_info),
					     0, (SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					     init_once);
	अगर (!qnx6_inode_cachep)
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
	kmem_cache_destroy(qnx6_inode_cachep);
पूर्ण

अटल काष्ठा dentry *qnx6_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, qnx6_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type qnx6_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "qnx6",
	.mount		= qnx6_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("qnx6");

अटल पूर्णांक __init init_qnx6_fs(व्योम)
अणु
	पूर्णांक err;

	err = init_inodecache();
	अगर (err)
		वापस err;

	err = रेजिस्टर_fileप्रणाली(&qnx6_fs_type);
	अगर (err) अणु
		destroy_inodecache();
		वापस err;
	पूर्ण

	pr_info("QNX6 filesystem 1.0.0 registered.\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_qnx6_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&qnx6_fs_type);
	destroy_inodecache();
पूर्ण

module_init(init_qnx6_fs)
module_निकास(निकास_qnx6_fs)
MODULE_LICENSE("GPL");
