<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/fs/ufs/swab.h
 *
 * Copyright (C) 1997, 1998 Francois-Rene Rideau <fare@tunes.org>
 * Copyright (C) 1998 Jakub Jelinek <jj@ultra.linux.cz>
 * Copyright (C) 2001 Christoph Hellwig <hch@infradead.org>
 */

#अगर_अघोषित _UFS_SWAB_H
#घोषणा _UFS_SWAB_H

/*
 * Notes:
 *    HERE WE ASSUME EITHER BIG OR LITTLE ENDIAN UFSes
 *    in हाल there are ufs implementations that have strange bytesexes,
 *    you'll need to modअगरy code here as well as in ufs_super.c and ufs_fs.h
 *    to support them.
 */

क्रमागत अणु
	BYTESEX_LE,
	BYTESEX_BE
पूर्ण;

अटल अंतरभूत u64
fs64_to_cpu(काष्ठा super_block *sbp, __fs64 n)
अणु
	अगर (UFS_SB(sbp)->s_bytesex == BYTESEX_LE)
		वापस le64_to_cpu((__क्रमce __le64)n);
	अन्यथा
		वापस be64_to_cpu((__क्रमce __be64)n);
पूर्ण

अटल अंतरभूत __fs64
cpu_to_fs64(काष्ठा super_block *sbp, u64 n)
अणु
	अगर (UFS_SB(sbp)->s_bytesex == BYTESEX_LE)
		वापस (__क्रमce __fs64)cpu_to_le64(n);
	अन्यथा
		वापस (__क्रमce __fs64)cpu_to_be64(n);
पूर्ण

अटल अंतरभूत u32
fs32_to_cpu(काष्ठा super_block *sbp, __fs32 n)
अणु
	अगर (UFS_SB(sbp)->s_bytesex == BYTESEX_LE)
		वापस le32_to_cpu((__क्रमce __le32)n);
	अन्यथा
		वापस be32_to_cpu((__क्रमce __be32)n);
पूर्ण

अटल अंतरभूत __fs32
cpu_to_fs32(काष्ठा super_block *sbp, u32 n)
अणु
	अगर (UFS_SB(sbp)->s_bytesex == BYTESEX_LE)
		वापस (__क्रमce __fs32)cpu_to_le32(n);
	अन्यथा
		वापस (__क्रमce __fs32)cpu_to_be32(n);
पूर्ण

अटल अंतरभूत व्योम
fs32_add(काष्ठा super_block *sbp, __fs32 *n, पूर्णांक d)
अणु
	अगर (UFS_SB(sbp)->s_bytesex == BYTESEX_LE)
		le32_add_cpu((__le32 *)n, d);
	अन्यथा
		be32_add_cpu((__be32 *)n, d);
पूर्ण

अटल अंतरभूत व्योम
fs32_sub(काष्ठा super_block *sbp, __fs32 *n, पूर्णांक d)
अणु
	अगर (UFS_SB(sbp)->s_bytesex == BYTESEX_LE)
		le32_add_cpu((__le32 *)n, -d);
	अन्यथा
		be32_add_cpu((__be32 *)n, -d);
पूर्ण

अटल अंतरभूत u16
fs16_to_cpu(काष्ठा super_block *sbp, __fs16 n)
अणु
	अगर (UFS_SB(sbp)->s_bytesex == BYTESEX_LE)
		वापस le16_to_cpu((__क्रमce __le16)n);
	अन्यथा
		वापस be16_to_cpu((__क्रमce __be16)n);
पूर्ण

अटल अंतरभूत __fs16
cpu_to_fs16(काष्ठा super_block *sbp, u16 n)
अणु
	अगर (UFS_SB(sbp)->s_bytesex == BYTESEX_LE)
		वापस (__क्रमce __fs16)cpu_to_le16(n);
	अन्यथा
		वापस (__क्रमce __fs16)cpu_to_be16(n);
पूर्ण

अटल अंतरभूत व्योम
fs16_add(काष्ठा super_block *sbp, __fs16 *n, पूर्णांक d)
अणु
	अगर (UFS_SB(sbp)->s_bytesex == BYTESEX_LE)
		le16_add_cpu((__le16 *)n, d);
	अन्यथा
		be16_add_cpu((__be16 *)n, d);
पूर्ण

अटल अंतरभूत व्योम
fs16_sub(काष्ठा super_block *sbp, __fs16 *n, पूर्णांक d)
अणु
	अगर (UFS_SB(sbp)->s_bytesex == BYTESEX_LE)
		le16_add_cpu((__le16 *)n, -d);
	अन्यथा
		be16_add_cpu((__be16 *)n, -d);
पूर्ण

#पूर्ण_अगर /* _UFS_SWAB_H */
