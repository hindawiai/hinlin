<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/include/linux/ext2_fs.h
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laborम_से_पre MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/include/linux/minix_fs.h
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#अगर_अघोषित _LINUX_EXT2_FS_H
#घोषणा _LINUX_EXT2_FS_H

#समावेश <linux/types.h>
#समावेश <linux/magic.h>

#घोषणा EXT2_NAME_LEN 255

/*
 * Maximal count of links to a file
 */
#घोषणा EXT2_LINK_MAX		32000

#घोषणा EXT2_SB_MAGIC_OFFSET	0x38
#घोषणा EXT2_SB_BLOCKS_OFFSET	0x04
#घोषणा EXT2_SB_BSIZE_OFFSET	0x18

अटल अंतरभूत u64 ext2_image_size(व्योम *ext2_sb)
अणु
	__u8 *p = ext2_sb;
	अगर (*(__le16 *)(p + EXT2_SB_MAGIC_OFFSET) != cpu_to_le16(EXT2_SUPER_MAGIC))
		वापस 0;
	वापस (u64)le32_to_cpup((__le32 *)(p + EXT2_SB_BLOCKS_OFFSET)) <<
		le32_to_cpup((__le32 *)(p + EXT2_SB_BSIZE_OFFSET));
पूर्ण

#पूर्ण_अगर	/* _LINUX_EXT2_FS_H */
