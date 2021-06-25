<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/minix/biपंचांगap.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

/*
 * Modअगरied क्रम 680x0 by Hamish Macकरोnald
 * Fixed क्रम 680x0 by Andreas Schwab
 */

/* biपंचांगap.c contains the code that handles the inode and block biपंचांगaps */

#समावेश "minix.h"
#समावेश <linux/buffer_head.h>
#समावेश <linux/bitops.h>
#समावेश <linux/sched.h>

अटल DEFINE_SPINLOCK(biपंचांगap_lock);

/*
 * biपंचांगap consists of blocks filled with 16bit words
 * bit set == busy, bit clear == मुक्त
 * endianness is a mess, but क्रम counting zero bits it really करोesn't matter...
 */
अटल __u32 count_मुक्त(काष्ठा buffer_head *map[], अचिन्हित blocksize, __u32 numbits)
अणु
	__u32 sum = 0;
	अचिन्हित blocks = DIV_ROUND_UP(numbits, blocksize * 8);

	जबतक (blocks--) अणु
		अचिन्हित words = blocksize / 2;
		__u16 *p = (__u16 *)(*map++)->b_data;
		जबतक (words--)
			sum += 16 - hweight16(*p++);
	पूर्ण

	वापस sum;
पूर्ण

व्योम minix_मुक्त_block(काष्ठा inode *inode, अचिन्हित दीर्घ block)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा minix_sb_info *sbi = minix_sb(sb);
	काष्ठा buffer_head *bh;
	पूर्णांक k = sb->s_blocksize_bits + 3;
	अचिन्हित दीर्घ bit, zone;

	अगर (block < sbi->s_firstdatazone || block >= sbi->s_nzones) अणु
		prपूर्णांकk("Trying to free block not in datazone\n");
		वापस;
	पूर्ण
	zone = block - sbi->s_firstdatazone + 1;
	bit = zone & ((1<<k) - 1);
	zone >>= k;
	अगर (zone >= sbi->s_zmap_blocks) अणु
		prपूर्णांकk("minix_free_block: nonexistent bitmap buffer\n");
		वापस;
	पूर्ण
	bh = sbi->s_zmap[zone];
	spin_lock(&biपंचांगap_lock);
	अगर (!minix_test_and_clear_bit(bit, bh->b_data))
		prपूर्णांकk("minix_free_block (%s:%lu): bit already cleared\n",
		       sb->s_id, block);
	spin_unlock(&biपंचांगap_lock);
	mark_buffer_dirty(bh);
	वापस;
पूर्ण

पूर्णांक minix_new_block(काष्ठा inode * inode)
अणु
	काष्ठा minix_sb_info *sbi = minix_sb(inode->i_sb);
	पूर्णांक bits_per_zone = 8 * inode->i_sb->s_blocksize;
	पूर्णांक i;

	क्रम (i = 0; i < sbi->s_zmap_blocks; i++) अणु
		काष्ठा buffer_head *bh = sbi->s_zmap[i];
		पूर्णांक j;

		spin_lock(&biपंचांगap_lock);
		j = minix_find_first_zero_bit(bh->b_data, bits_per_zone);
		अगर (j < bits_per_zone) अणु
			minix_set_bit(j, bh->b_data);
			spin_unlock(&biपंचांगap_lock);
			mark_buffer_dirty(bh);
			j += i * bits_per_zone + sbi->s_firstdatazone-1;
			अगर (j < sbi->s_firstdatazone || j >= sbi->s_nzones)
				अवरोध;
			वापस j;
		पूर्ण
		spin_unlock(&biपंचांगap_lock);
	पूर्ण
	वापस 0;
पूर्ण

अचिन्हित दीर्घ minix_count_मुक्त_blocks(काष्ठा super_block *sb)
अणु
	काष्ठा minix_sb_info *sbi = minix_sb(sb);
	u32 bits = sbi->s_nzones - sbi->s_firstdatazone + 1;

	वापस (count_मुक्त(sbi->s_zmap, sb->s_blocksize, bits)
		<< sbi->s_log_zone_size);
पूर्ण

काष्ठा minix_inode *
minix_V1_raw_inode(काष्ठा super_block *sb, ino_t ino, काष्ठा buffer_head **bh)
अणु
	पूर्णांक block;
	काष्ठा minix_sb_info *sbi = minix_sb(sb);
	काष्ठा minix_inode *p;

	अगर (!ino || ino > sbi->s_ninodes) अणु
		prपूर्णांकk("Bad inode number on dev %s: %ld is out of range\n",
		       sb->s_id, (दीर्घ)ino);
		वापस शून्य;
	पूर्ण
	ino--;
	block = 2 + sbi->s_imap_blocks + sbi->s_zmap_blocks +
		 ino / MINIX_INODES_PER_BLOCK;
	*bh = sb_bपढ़ो(sb, block);
	अगर (!*bh) अणु
		prपूर्णांकk("Unable to read inode block\n");
		वापस शून्य;
	पूर्ण
	p = (व्योम *)(*bh)->b_data;
	वापस p + ino % MINIX_INODES_PER_BLOCK;
पूर्ण

काष्ठा minix2_inode *
minix_V2_raw_inode(काष्ठा super_block *sb, ino_t ino, काष्ठा buffer_head **bh)
अणु
	पूर्णांक block;
	काष्ठा minix_sb_info *sbi = minix_sb(sb);
	काष्ठा minix2_inode *p;
	पूर्णांक minix2_inodes_per_block = sb->s_blocksize / माप(काष्ठा minix2_inode);

	*bh = शून्य;
	अगर (!ino || ino > sbi->s_ninodes) अणु
		prपूर्णांकk("Bad inode number on dev %s: %ld is out of range\n",
		       sb->s_id, (दीर्घ)ino);
		वापस शून्य;
	पूर्ण
	ino--;
	block = 2 + sbi->s_imap_blocks + sbi->s_zmap_blocks +
		 ino / minix2_inodes_per_block;
	*bh = sb_bपढ़ो(sb, block);
	अगर (!*bh) अणु
		prपूर्णांकk("Unable to read inode block\n");
		वापस शून्य;
	पूर्ण
	p = (व्योम *)(*bh)->b_data;
	वापस p + ino % minix2_inodes_per_block;
पूर्ण

/* Clear the link count and mode of a deleted inode on disk. */

अटल व्योम minix_clear_inode(काष्ठा inode *inode)
अणु
	काष्ठा buffer_head *bh = शून्य;

	अगर (INODE_VERSION(inode) == MINIX_V1) अणु
		काष्ठा minix_inode *raw_inode;
		raw_inode = minix_V1_raw_inode(inode->i_sb, inode->i_ino, &bh);
		अगर (raw_inode) अणु
			raw_inode->i_nlinks = 0;
			raw_inode->i_mode = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा minix2_inode *raw_inode;
		raw_inode = minix_V2_raw_inode(inode->i_sb, inode->i_ino, &bh);
		अगर (raw_inode) अणु
			raw_inode->i_nlinks = 0;
			raw_inode->i_mode = 0;
		पूर्ण
	पूर्ण
	अगर (bh) अणु
		mark_buffer_dirty(bh);
		brअन्यथा (bh);
	पूर्ण
पूर्ण

व्योम minix_मुक्त_inode(काष्ठा inode * inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा minix_sb_info *sbi = minix_sb(inode->i_sb);
	काष्ठा buffer_head *bh;
	पूर्णांक k = sb->s_blocksize_bits + 3;
	अचिन्हित दीर्घ ino, bit;

	ino = inode->i_ino;
	अगर (ino < 1 || ino > sbi->s_ninodes) अणु
		prपूर्णांकk("minix_free_inode: inode 0 or nonexistent inode\n");
		वापस;
	पूर्ण
	bit = ino & ((1<<k) - 1);
	ino >>= k;
	अगर (ino >= sbi->s_imap_blocks) अणु
		prपूर्णांकk("minix_free_inode: nonexistent imap in superblock\n");
		वापस;
	पूर्ण

	minix_clear_inode(inode);	/* clear on-disk copy */

	bh = sbi->s_imap[ino];
	spin_lock(&biपंचांगap_lock);
	अगर (!minix_test_and_clear_bit(bit, bh->b_data))
		prपूर्णांकk("minix_free_inode: bit %lu already cleared\n", bit);
	spin_unlock(&biपंचांगap_lock);
	mark_buffer_dirty(bh);
पूर्ण

काष्ठा inode *minix_new_inode(स्थिर काष्ठा inode *dir, umode_t mode, पूर्णांक *error)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा minix_sb_info *sbi = minix_sb(sb);
	काष्ठा inode *inode = new_inode(sb);
	काष्ठा buffer_head * bh;
	पूर्णांक bits_per_zone = 8 * sb->s_blocksize;
	अचिन्हित दीर्घ j;
	पूर्णांक i;

	अगर (!inode) अणु
		*error = -ENOMEM;
		वापस शून्य;
	पूर्ण
	j = bits_per_zone;
	bh = शून्य;
	*error = -ENOSPC;
	spin_lock(&biपंचांगap_lock);
	क्रम (i = 0; i < sbi->s_imap_blocks; i++) अणु
		bh = sbi->s_imap[i];
		j = minix_find_first_zero_bit(bh->b_data, bits_per_zone);
		अगर (j < bits_per_zone)
			अवरोध;
	पूर्ण
	अगर (!bh || j >= bits_per_zone) अणु
		spin_unlock(&biपंचांगap_lock);
		iput(inode);
		वापस शून्य;
	पूर्ण
	अगर (minix_test_and_set_bit(j, bh->b_data)) अणु	/* shouldn't happen */
		spin_unlock(&biपंचांगap_lock);
		prपूर्णांकk("minix_new_inode: bit already set\n");
		iput(inode);
		वापस शून्य;
	पूर्ण
	spin_unlock(&biपंचांगap_lock);
	mark_buffer_dirty(bh);
	j += i * bits_per_zone;
	अगर (!j || j > sbi->s_ninodes) अणु
		iput(inode);
		वापस शून्य;
	पूर्ण
	inode_init_owner(&init_user_ns, inode, dir, mode);
	inode->i_ino = j;
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	inode->i_blocks = 0;
	स_रखो(&minix_i(inode)->u, 0, माप(minix_i(inode)->u));
	insert_inode_hash(inode);
	mark_inode_dirty(inode);

	*error = 0;
	वापस inode;
पूर्ण

अचिन्हित दीर्घ minix_count_मुक्त_inodes(काष्ठा super_block *sb)
अणु
	काष्ठा minix_sb_info *sbi = minix_sb(sb);
	u32 bits = sbi->s_ninodes + 1;

	वापस count_मुक्त(sbi->s_imap, sb->s_blocksize, bits);
पूर्ण
