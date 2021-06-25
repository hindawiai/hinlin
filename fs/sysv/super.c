<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/sysv/inode.c
 *
 *  minix/inode.c
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  xenix/inode.c
 *  Copyright (C) 1992  Doug Evans
 *
 *  coh/inode.c
 *  Copyright (C) 1993  Pascal Haible, Bruno Haible
 *
 *  sysv/inode.c
 *  Copyright (C) 1993  Paul B. Monday
 *
 *  sysv/inode.c
 *  Copyright (C) 1993  Bruno Haible
 *  Copyright (C) 1997, 1998  Krzysztof G. Baranowski
 *
 *  This file contains code क्रम पढ़ो/parsing the superblock.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/buffer_head.h>
#समावेश "sysv.h"

/*
 * The following functions try to recognize specअगरic fileप्रणालीs.
 *
 * We recognize:
 * - Xenix FS by its magic number.
 * - SystemV FS by its magic number.
 * - Coherent FS by its funny fname/fpack field.
 * - SCO AFS by s_nमुक्त == 0xffff
 * - V7 FS has no distinguishing features.
 *
 * We discriminate among SystemV4 and SystemV2 FS by the assumption that
 * the समय stamp is not < 01-01-1980.
 */

क्रमागत अणु
	JAN_1_1980 = (10*365 + 2) * 24 * 60 * 60
पूर्ण;

अटल व्योम detected_xenix(काष्ठा sysv_sb_info *sbi, अचिन्हित *max_links)
अणु
	काष्ठा buffer_head *bh1 = sbi->s_bh1;
	काष्ठा buffer_head *bh2 = sbi->s_bh2;
	काष्ठा xenix_super_block * sbd1;
	काष्ठा xenix_super_block * sbd2;

	अगर (bh1 != bh2)
		sbd1 = sbd2 = (काष्ठा xenix_super_block *) bh1->b_data;
	अन्यथा अणु
		/* block size = 512, so bh1 != bh2 */
		sbd1 = (काष्ठा xenix_super_block *) bh1->b_data;
		sbd2 = (काष्ठा xenix_super_block *) (bh2->b_data - 512);
	पूर्ण

	*max_links = XENIX_LINK_MAX;
	sbi->s_fic_size = XENIX_NICINOD;
	sbi->s_flc_size = XENIX_NICFREE;
	sbi->s_sbd1 = (अक्षर *)sbd1;
	sbi->s_sbd2 = (अक्षर *)sbd2;
	sbi->s_sb_fic_count = &sbd1->s_ninode;
	sbi->s_sb_fic_inodes = &sbd1->s_inode[0];
	sbi->s_sb_total_मुक्त_inodes = &sbd2->s_tinode;
	sbi->s_bcache_count = &sbd1->s_nमुक्त;
	sbi->s_bcache = &sbd1->s_मुक्त[0];
	sbi->s_मुक्त_blocks = &sbd2->s_tमुक्त;
	sbi->s_sb_समय = &sbd2->s_समय;
	sbi->s_firstdatazone = fs16_to_cpu(sbi, sbd1->s_isize);
	sbi->s_nzones = fs32_to_cpu(sbi, sbd1->s_fsize);
पूर्ण

अटल व्योम detected_sysv4(काष्ठा sysv_sb_info *sbi, अचिन्हित *max_links)
अणु
	काष्ठा sysv4_super_block * sbd;
	काष्ठा buffer_head *bh1 = sbi->s_bh1;
	काष्ठा buffer_head *bh2 = sbi->s_bh2;

	अगर (bh1 == bh2)
		sbd = (काष्ठा sysv4_super_block *) (bh1->b_data + BLOCK_SIZE/2);
	अन्यथा
		sbd = (काष्ठा sysv4_super_block *) bh2->b_data;

	*max_links = SYSV_LINK_MAX;
	sbi->s_fic_size = SYSV_NICINOD;
	sbi->s_flc_size = SYSV_NICFREE;
	sbi->s_sbd1 = (अक्षर *)sbd;
	sbi->s_sbd2 = (अक्षर *)sbd;
	sbi->s_sb_fic_count = &sbd->s_ninode;
	sbi->s_sb_fic_inodes = &sbd->s_inode[0];
	sbi->s_sb_total_मुक्त_inodes = &sbd->s_tinode;
	sbi->s_bcache_count = &sbd->s_nमुक्त;
	sbi->s_bcache = &sbd->s_मुक्त[0];
	sbi->s_मुक्त_blocks = &sbd->s_tमुक्त;
	sbi->s_sb_समय = &sbd->s_समय;
	sbi->s_sb_state = &sbd->s_state;
	sbi->s_firstdatazone = fs16_to_cpu(sbi, sbd->s_isize);
	sbi->s_nzones = fs32_to_cpu(sbi, sbd->s_fsize);
पूर्ण

अटल व्योम detected_sysv2(काष्ठा sysv_sb_info *sbi, अचिन्हित *max_links)
अणु
	काष्ठा sysv2_super_block *sbd;
	काष्ठा buffer_head *bh1 = sbi->s_bh1;
	काष्ठा buffer_head *bh2 = sbi->s_bh2;

	अगर (bh1 == bh2)
		sbd = (काष्ठा sysv2_super_block *) (bh1->b_data + BLOCK_SIZE/2);
	अन्यथा
		sbd = (काष्ठा sysv2_super_block *) bh2->b_data;

	*max_links = SYSV_LINK_MAX;
	sbi->s_fic_size = SYSV_NICINOD;
	sbi->s_flc_size = SYSV_NICFREE;
	sbi->s_sbd1 = (अक्षर *)sbd;
	sbi->s_sbd2 = (अक्षर *)sbd;
	sbi->s_sb_fic_count = &sbd->s_ninode;
	sbi->s_sb_fic_inodes = &sbd->s_inode[0];
	sbi->s_sb_total_मुक्त_inodes = &sbd->s_tinode;
	sbi->s_bcache_count = &sbd->s_nमुक्त;
	sbi->s_bcache = &sbd->s_मुक्त[0];
	sbi->s_मुक्त_blocks = &sbd->s_tमुक्त;
	sbi->s_sb_समय = &sbd->s_समय;
	sbi->s_sb_state = &sbd->s_state;
	sbi->s_firstdatazone = fs16_to_cpu(sbi, sbd->s_isize);
	sbi->s_nzones = fs32_to_cpu(sbi, sbd->s_fsize);
पूर्ण

अटल व्योम detected_coherent(काष्ठा sysv_sb_info *sbi, अचिन्हित *max_links)
अणु
	काष्ठा coh_super_block * sbd;
	काष्ठा buffer_head *bh1 = sbi->s_bh1;

	sbd = (काष्ठा coh_super_block *) bh1->b_data;

	*max_links = COH_LINK_MAX;
	sbi->s_fic_size = COH_NICINOD;
	sbi->s_flc_size = COH_NICFREE;
	sbi->s_sbd1 = (अक्षर *)sbd;
	sbi->s_sbd2 = (अक्षर *)sbd;
	sbi->s_sb_fic_count = &sbd->s_ninode;
	sbi->s_sb_fic_inodes = &sbd->s_inode[0];
	sbi->s_sb_total_मुक्त_inodes = &sbd->s_tinode;
	sbi->s_bcache_count = &sbd->s_nमुक्त;
	sbi->s_bcache = &sbd->s_मुक्त[0];
	sbi->s_मुक्त_blocks = &sbd->s_tमुक्त;
	sbi->s_sb_समय = &sbd->s_समय;
	sbi->s_firstdatazone = fs16_to_cpu(sbi, sbd->s_isize);
	sbi->s_nzones = fs32_to_cpu(sbi, sbd->s_fsize);
पूर्ण

अटल व्योम detected_v7(काष्ठा sysv_sb_info *sbi, अचिन्हित *max_links)
अणु
	काष्ठा buffer_head *bh2 = sbi->s_bh2;
	काष्ठा v7_super_block *sbd = (काष्ठा v7_super_block *)bh2->b_data;

	*max_links = V7_LINK_MAX;
	sbi->s_fic_size = V7_NICINOD;
	sbi->s_flc_size = V7_NICFREE;
	sbi->s_sbd1 = (अक्षर *)sbd;
	sbi->s_sbd2 = (अक्षर *)sbd;
	sbi->s_sb_fic_count = &sbd->s_ninode;
	sbi->s_sb_fic_inodes = &sbd->s_inode[0];
	sbi->s_sb_total_मुक्त_inodes = &sbd->s_tinode;
	sbi->s_bcache_count = &sbd->s_nमुक्त;
	sbi->s_bcache = &sbd->s_मुक्त[0];
	sbi->s_मुक्त_blocks = &sbd->s_tमुक्त;
	sbi->s_sb_समय = &sbd->s_समय;
	sbi->s_firstdatazone = fs16_to_cpu(sbi, sbd->s_isize);
	sbi->s_nzones = fs32_to_cpu(sbi, sbd->s_fsize);
पूर्ण

अटल पूर्णांक detect_xenix(काष्ठा sysv_sb_info *sbi, काष्ठा buffer_head *bh)
अणु
	काष्ठा xenix_super_block *sbd = (काष्ठा xenix_super_block *)bh->b_data;
	अगर (*(__le32 *)&sbd->s_magic == cpu_to_le32(0x2b5544))
		sbi->s_bytesex = BYTESEX_LE;
	अन्यथा अगर (*(__be32 *)&sbd->s_magic == cpu_to_be32(0x2b5544))
		sbi->s_bytesex = BYTESEX_BE;
	अन्यथा
		वापस 0;
	चयन (fs32_to_cpu(sbi, sbd->s_type)) अणु
	हाल 1:
		sbi->s_type = FSTYPE_XENIX;
		वापस 1;
	हाल 2:
		sbi->s_type = FSTYPE_XENIX;
		वापस 2;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक detect_sysv(काष्ठा sysv_sb_info *sbi, काष्ठा buffer_head *bh)
अणु
	काष्ठा super_block *sb = sbi->s_sb;
	/* All relevant fields are at the same offsets in R2 and R4 */
	काष्ठा sysv4_super_block * sbd;
	u32 type;

	sbd = (काष्ठा sysv4_super_block *) (bh->b_data + BLOCK_SIZE/2);
	अगर (*(__le32 *)&sbd->s_magic == cpu_to_le32(0xfd187e20))
		sbi->s_bytesex = BYTESEX_LE;
	अन्यथा अगर (*(__be32 *)&sbd->s_magic == cpu_to_be32(0xfd187e20))
		sbi->s_bytesex = BYTESEX_BE;
	अन्यथा
		वापस 0;

	type = fs32_to_cpu(sbi, sbd->s_type);
 
 	अगर (fs16_to_cpu(sbi, sbd->s_nमुक्त) == 0xffff) अणु
 		sbi->s_type = FSTYPE_AFS;
		sbi->s_क्रमced_ro = 1;
 		अगर (!sb_rकरोnly(sb)) अणु
 			prपूर्णांकk("SysV FS: SCO EAFS on %s detected, " 
 				"forcing read-only mode.\n", 
 				sb->s_id);
 		पूर्ण
 		वापस type;
 	पूर्ण
 
	अगर (fs32_to_cpu(sbi, sbd->s_समय) < JAN_1_1980) अणु
		/* this is likely to happen on SystemV2 FS */
		अगर (type > 3 || type < 1)
			वापस 0;
		sbi->s_type = FSTYPE_SYSV2;
		वापस type;
	पूर्ण
	अगर ((type > 3 || type < 1) && (type > 0x30 || type < 0x10))
		वापस 0;

	/* On Interactive Unix (ISC) Version 4.0/3.x s_type field = 0x10,
	   0x20 or 0x30 indicates that symbolic links and the 14-अक्षरacter
	   filename limit is gone. Due to lack of inक्रमmation about this
           feature पढ़ो-only mode seems to be a reasonable approach... -KGB */

	अगर (type >= 0x10) अणु
		prपूर्णांकk("SysV FS: can't handle long file names on %s, "
		       "forcing read-only mode.\n", sb->s_id);
		sbi->s_क्रमced_ro = 1;
	पूर्ण

	sbi->s_type = FSTYPE_SYSV4;
	वापस type >= 0x10 ? type >> 4 : type;
पूर्ण

अटल पूर्णांक detect_coherent(काष्ठा sysv_sb_info *sbi, काष्ठा buffer_head *bh)
अणु
	काष्ठा coh_super_block * sbd;

	sbd = (काष्ठा coh_super_block *) (bh->b_data + BLOCK_SIZE/2);
	अगर ((स_भेद(sbd->s_fname,"noname",6) && स_भेद(sbd->s_fname,"xxxxx ",6))
	    || (स_भेद(sbd->s_fpack,"nopack",6) && स_भेद(sbd->s_fpack,"xxxxx\n",6)))
		वापस 0;
	sbi->s_bytesex = BYTESEX_PDP;
	sbi->s_type = FSTYPE_COH;
	वापस 1;
पूर्ण

अटल पूर्णांक detect_sysv_odd(काष्ठा sysv_sb_info *sbi, काष्ठा buffer_head *bh)
अणु
	पूर्णांक size = detect_sysv(sbi, bh);

	वापस size>2 ? 0 : size;
पूर्ण

अटल काष्ठा अणु
	पूर्णांक block;
	पूर्णांक (*test)(काष्ठा sysv_sb_info *, काष्ठा buffer_head *);
पूर्ण flavours[] = अणु
	अणु1, detect_xenixपूर्ण,
	अणु0, detect_sysvपूर्ण,
	अणु0, detect_coherentपूर्ण,
	अणु9, detect_sysv_oddपूर्ण,
	अणु15,detect_sysv_oddपूर्ण,
	अणु18,detect_sysvपूर्ण,
पूर्ण;

अटल अक्षर *flavour_names[] = अणु
	[FSTYPE_XENIX]	= "Xenix",
	[FSTYPE_SYSV4]	= "SystemV",
	[FSTYPE_SYSV2]	= "SystemV Release 2",
	[FSTYPE_COH]	= "Coherent",
	[FSTYPE_V7]	= "V7",
	[FSTYPE_AFS]	= "AFS",
पूर्ण;

अटल व्योम (*flavour_setup[])(काष्ठा sysv_sb_info *, अचिन्हित *) = अणु
	[FSTYPE_XENIX]	= detected_xenix,
	[FSTYPE_SYSV4]	= detected_sysv4,
	[FSTYPE_SYSV2]	= detected_sysv2,
	[FSTYPE_COH]	= detected_coherent,
	[FSTYPE_V7]	= detected_v7,
	[FSTYPE_AFS]	= detected_sysv4,
पूर्ण;

अटल पूर्णांक complete_पढ़ो_super(काष्ठा super_block *sb, पूर्णांक silent, पूर्णांक size)
अणु
	काष्ठा sysv_sb_info *sbi = SYSV_SB(sb);
	काष्ठा inode *root_inode;
	अक्षर *found = flavour_names[sbi->s_type];
	u_अक्षर n_bits = size+8;
	पूर्णांक bsize = 1 << n_bits;
	पूर्णांक bsize_4 = bsize >> 2;

	sbi->s_firstinodezone = 2;

	flavour_setup[sbi->s_type](sbi, &sb->s_max_links);
	
	sbi->s_ndatazones = sbi->s_nzones - sbi->s_firstdatazone;
	sbi->s_inodes_per_block = bsize >> 6;
	sbi->s_inodes_per_block_1 = (bsize >> 6)-1;
	sbi->s_inodes_per_block_bits = n_bits-6;
	sbi->s_ind_per_block = bsize_4;
	sbi->s_ind_per_block_2 = bsize_4*bsize_4;
	sbi->s_toobig_block = 10 + bsize_4 * (1 + bsize_4 * (1 + bsize_4));
	sbi->s_ind_per_block_bits = n_bits-2;

	sbi->s_ninodes = (sbi->s_firstdatazone - sbi->s_firstinodezone)
		<< sbi->s_inodes_per_block_bits;

	अगर (!silent)
		prपूर्णांकk("VFS: Found a %s FS (block size = %ld) on device %s\n",
		       found, sb->s_blocksize, sb->s_id);

	sb->s_magic = SYSV_MAGIC_BASE + sbi->s_type;
	/* set up enough so that it can पढ़ो an inode */
	sb->s_op = &sysv_sops;
	अगर (sbi->s_क्रमced_ro)
		sb->s_flags |= SB_RDONLY;
	root_inode = sysv_iget(sb, SYSV_ROOT_INO);
	अगर (IS_ERR(root_inode)) अणु
		prपूर्णांकk("SysV FS: get root inode failed\n");
		वापस 0;
	पूर्ण
	sb->s_root = d_make_root(root_inode);
	अगर (!sb->s_root) अणु
		prपूर्णांकk("SysV FS: get root dentry failed\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक sysv_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा buffer_head *bh1, *bh = शून्य;
	काष्ठा sysv_sb_info *sbi;
	अचिन्हित दीर्घ blocknr;
	पूर्णांक size = 0, i;
	
	BUILD_BUG_ON(1024 != माप (काष्ठा xenix_super_block));
	BUILD_BUG_ON(512 != माप (काष्ठा sysv4_super_block));
	BUILD_BUG_ON(512 != माप (काष्ठा sysv2_super_block));
	BUILD_BUG_ON(500 != माप (काष्ठा coh_super_block));
	BUILD_BUG_ON(64 != माप (काष्ठा sysv_inode));

	sbi = kzalloc(माप(काष्ठा sysv_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;

	sbi->s_sb = sb;
	sbi->s_block_base = 0;
	mutex_init(&sbi->s_lock);
	sb->s_fs_info = sbi;
	sb->s_समय_min = 0;
	sb->s_समय_max = U32_MAX;
	sb_set_blocksize(sb, BLOCK_SIZE);

	क्रम (i = 0; i < ARRAY_SIZE(flavours) && !size; i++) अणु
		brअन्यथा(bh);
		bh = sb_bपढ़ो(sb, flavours[i].block);
		अगर (!bh)
			जारी;
		size = flavours[i].test(SYSV_SB(sb), bh);
	पूर्ण

	अगर (!size)
		जाओ Eunknown;

	चयन (size) अणु
		हाल 1:
			blocknr = bh->b_blocknr << 1;
			brअन्यथा(bh);
			sb_set_blocksize(sb, 512);
			bh1 = sb_bपढ़ो(sb, blocknr);
			bh = sb_bपढ़ो(sb, blocknr + 1);
			अवरोध;
		हाल 2:
			bh1 = bh;
			अवरोध;
		हाल 3:
			blocknr = bh->b_blocknr >> 1;
			brअन्यथा(bh);
			sb_set_blocksize(sb, 2048);
			bh1 = bh = sb_bपढ़ो(sb, blocknr);
			अवरोध;
		शेष:
			जाओ Ebadsize;
	पूर्ण

	अगर (bh && bh1) अणु
		sbi->s_bh1 = bh1;
		sbi->s_bh2 = bh;
		अगर (complete_पढ़ो_super(sb, silent, size))
			वापस 0;
	पूर्ण

	brअन्यथा(bh1);
	brअन्यथा(bh);
	sb_set_blocksize(sb, BLOCK_SIZE);
	prपूर्णांकk("oldfs: cannot read superblock\n");
failed:
	kमुक्त(sbi);
	वापस -EINVAL;

Eunknown:
	brअन्यथा(bh);
	अगर (!silent)
		prपूर्णांकk("VFS: unable to find oldfs superblock on device %s\n",
			sb->s_id);
	जाओ failed;
Ebadsize:
	brअन्यथा(bh);
	अगर (!silent)
		prपूर्णांकk("VFS: oldfs: unsupported block size (%dKb)\n",
			1<<(size-2));
	जाओ failed;
पूर्ण

अटल पूर्णांक v7_sanity_check(काष्ठा super_block *sb, काष्ठा buffer_head *bh)
अणु
	काष्ठा v7_super_block *v7sb;
	काष्ठा sysv_inode *v7i;
	काष्ठा buffer_head *bh2;
	काष्ठा sysv_sb_info *sbi;

	sbi = sb->s_fs_info;

	/* plausibility check on superblock */
	v7sb = (काष्ठा v7_super_block *) bh->b_data;
	अगर (fs16_to_cpu(sbi, v7sb->s_nमुक्त) > V7_NICFREE ||
	    fs16_to_cpu(sbi, v7sb->s_ninode) > V7_NICINOD ||
	    fs32_to_cpu(sbi, v7sb->s_fsize) > V7_MAXSIZE)
		वापस 0;

	/* plausibility check on root inode: it is a directory,
	   with a nonzero size that is a multiple of 16 */
	bh2 = sb_bपढ़ो(sb, 2);
	अगर (bh2 == शून्य)
		वापस 0;

	v7i = (काष्ठा sysv_inode *)(bh2->b_data + 64);
	अगर ((fs16_to_cpu(sbi, v7i->i_mode) & ~0777) != S_IFसूची ||
	    (fs32_to_cpu(sbi, v7i->i_size) == 0) ||
	    (fs32_to_cpu(sbi, v7i->i_size) & 017) ||
	    (fs32_to_cpu(sbi, v7i->i_size) > V7_NखाताS *
	     माप(काष्ठा sysv_dir_entry))) अणु
		brअन्यथा(bh2);
		वापस 0;
	पूर्ण

	brअन्यथा(bh2);
	वापस 1;
पूर्ण

अटल पूर्णांक v7_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा sysv_sb_info *sbi;
	काष्ठा buffer_head *bh;

	अगर (440 != माप (काष्ठा v7_super_block))
		panic("V7 FS: bad super-block size");
	अगर (64 != माप (काष्ठा sysv_inode))
		panic("sysv fs: bad i-node size");

	sbi = kzalloc(माप(काष्ठा sysv_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;

	sbi->s_sb = sb;
	sbi->s_block_base = 0;
	sbi->s_type = FSTYPE_V7;
	mutex_init(&sbi->s_lock);
	sb->s_fs_info = sbi;
	sb->s_समय_min = 0;
	sb->s_समय_max = U32_MAX;
	
	sb_set_blocksize(sb, 512);

	अगर ((bh = sb_bपढ़ो(sb, 1)) == शून्य) अणु
		अगर (!silent)
			prपूर्णांकk("VFS: unable to read V7 FS superblock on "
			       "device %s.\n", sb->s_id);
		जाओ failed;
	पूर्ण

	/* Try PDP-11 UNIX */
	sbi->s_bytesex = BYTESEX_PDP;
	अगर (v7_sanity_check(sb, bh))
		जाओ detected;

	/* Try PC/IX, v7/x86 */
	sbi->s_bytesex = BYTESEX_LE;
	अगर (v7_sanity_check(sb, bh))
		जाओ detected;

	जाओ failed;

detected:
	sbi->s_bh1 = bh;
	sbi->s_bh2 = bh;
	अगर (complete_पढ़ो_super(sb, silent, 1))
		वापस 0;

failed:
	prपूर्णांकk(KERN_ERR "VFS: could not find a valid V7 on %s.\n",
		sb->s_id);
	brअन्यथा(bh);
	kमुक्त(sbi);
	वापस -EINVAL;
पूर्ण

/* Every kernel module contains stuff like this. */

अटल काष्ठा dentry *sysv_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, sysv_fill_super);
पूर्ण

अटल काष्ठा dentry *v7_mount(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, v7_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type sysv_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "sysv",
	.mount		= sysv_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("sysv");

अटल काष्ठा file_प्रणाली_type v7_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "v7",
	.mount		= v7_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("v7");
MODULE_ALIAS("v7");

अटल पूर्णांक __init init_sysv_fs(व्योम)
अणु
	पूर्णांक error;

	error = sysv_init_icache();
	अगर (error)
		जाओ out;
	error = रेजिस्टर_fileप्रणाली(&sysv_fs_type);
	अगर (error)
		जाओ destroy_icache;
	error = रेजिस्टर_fileप्रणाली(&v7_fs_type);
	अगर (error)
		जाओ unरेजिस्टर;
	वापस 0;

unरेजिस्टर:
	unरेजिस्टर_fileप्रणाली(&sysv_fs_type);
destroy_icache:
	sysv_destroy_icache();
out:
	वापस error;
पूर्ण

अटल व्योम __निकास निकास_sysv_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&sysv_fs_type);
	unरेजिस्टर_fileप्रणाली(&v7_fs_type);
	sysv_destroy_icache();
पूर्ण

module_init(init_sysv_fs)
module_निकास(निकास_sysv_fs)
MODULE_LICENSE("GPL");
