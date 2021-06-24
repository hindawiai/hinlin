<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/biपंचांगap.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 */

#समावेश <linux/buffer_head.h>
#समावेश "ext4.h"

अचिन्हित पूर्णांक ext4_count_मुक्त(अक्षर *biपंचांगap, अचिन्हित पूर्णांक numअक्षरs)
अणु
	वापस numअक्षरs * BITS_PER_BYTE - memweight(biपंचांगap, numअक्षरs);
पूर्ण

पूर्णांक ext4_inode_biपंचांगap_csum_verअगरy(काष्ठा super_block *sb, ext4_group_t group,
				  काष्ठा ext4_group_desc *gdp,
				  काष्ठा buffer_head *bh, पूर्णांक sz)
अणु
	__u32 hi;
	__u32 provided, calculated;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	अगर (!ext4_has_metadata_csum(sb))
		वापस 1;

	provided = le16_to_cpu(gdp->bg_inode_biपंचांगap_csum_lo);
	calculated = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)bh->b_data, sz);
	अगर (sbi->s_desc_size >= EXT4_BG_INODE_BITMAP_CSUM_HI_END) अणु
		hi = le16_to_cpu(gdp->bg_inode_biपंचांगap_csum_hi);
		provided |= (hi << 16);
	पूर्ण अन्यथा
		calculated &= 0xFFFF;

	वापस provided == calculated;
पूर्ण

व्योम ext4_inode_biपंचांगap_csum_set(काष्ठा super_block *sb, ext4_group_t group,
				काष्ठा ext4_group_desc *gdp,
				काष्ठा buffer_head *bh, पूर्णांक sz)
अणु
	__u32 csum;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	अगर (!ext4_has_metadata_csum(sb))
		वापस;

	csum = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)bh->b_data, sz);
	gdp->bg_inode_biपंचांगap_csum_lo = cpu_to_le16(csum & 0xFFFF);
	अगर (sbi->s_desc_size >= EXT4_BG_INODE_BITMAP_CSUM_HI_END)
		gdp->bg_inode_biपंचांगap_csum_hi = cpu_to_le16(csum >> 16);
पूर्ण

पूर्णांक ext4_block_biपंचांगap_csum_verअगरy(काष्ठा super_block *sb, ext4_group_t group,
				  काष्ठा ext4_group_desc *gdp,
				  काष्ठा buffer_head *bh)
अणु
	__u32 hi;
	__u32 provided, calculated;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	पूर्णांक sz = EXT4_CLUSTERS_PER_GROUP(sb) / 8;

	अगर (!ext4_has_metadata_csum(sb))
		वापस 1;

	provided = le16_to_cpu(gdp->bg_block_biपंचांगap_csum_lo);
	calculated = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)bh->b_data, sz);
	अगर (sbi->s_desc_size >= EXT4_BG_BLOCK_BITMAP_CSUM_HI_END) अणु
		hi = le16_to_cpu(gdp->bg_block_biपंचांगap_csum_hi);
		provided |= (hi << 16);
	पूर्ण अन्यथा
		calculated &= 0xFFFF;

	अगर (provided == calculated)
		वापस 1;

	वापस 0;
पूर्ण

व्योम ext4_block_biपंचांगap_csum_set(काष्ठा super_block *sb, ext4_group_t group,
				काष्ठा ext4_group_desc *gdp,
				काष्ठा buffer_head *bh)
अणु
	पूर्णांक sz = EXT4_CLUSTERS_PER_GROUP(sb) / 8;
	__u32 csum;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	अगर (!ext4_has_metadata_csum(sb))
		वापस;

	csum = ext4_chksum(sbi, sbi->s_csum_seed, (__u8 *)bh->b_data, sz);
	gdp->bg_block_biपंचांगap_csum_lo = cpu_to_le16(csum & 0xFFFF);
	अगर (sbi->s_desc_size >= EXT4_BG_BLOCK_BITMAP_CSUM_HI_END)
		gdp->bg_block_biपंचांगap_csum_hi = cpu_to_le16(csum >> 16);
पूर्ण
