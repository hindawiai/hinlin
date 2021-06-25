<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) Tino Reiअक्षरdt, 2012
 */

#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>

#समावेश "jfs_incore.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_discard.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_debug.h"


/*
 * NAME:	jfs_issue_discard()
 *
 * FUNCTION:	TRIM the specअगरied block range on device, अगर supported
 *
 * PARAMETERS:
 *	ip	- poपूर्णांकer to in-core inode
 *	blkno	- starting block number to be trimmed (0..N)
 *	nblocks	- number of blocks to be trimmed
 *
 * RETURN VALUES:
 *	none
 *
 * serialization: IREAD_LOCK(ipbmap) held on entry/निकास;
 */
व्योम jfs_issue_discard(काष्ठा inode *ip, u64 blkno, u64 nblocks)
अणु
	काष्ठा super_block *sb = ip->i_sb;
	पूर्णांक r = 0;

	r = sb_issue_discard(sb, blkno, nblocks, GFP_NOFS, 0);
	अगर (unlikely(r != 0)) अणु
		jfs_err("JFS: sb_issue_discard(%p, %llu, %llu, GFP_NOFS, 0) = %d => failed!",
			sb, (अचिन्हित दीर्घ दीर्घ)blkno,
			(अचिन्हित दीर्घ दीर्घ)nblocks, r);
	पूर्ण

	jfs_info("JFS: sb_issue_discard(%p, %llu, %llu, GFP_NOFS, 0) = %d",
		sb, (अचिन्हित दीर्घ दीर्घ)blkno,
		(अचिन्हित दीर्घ दीर्घ)nblocks, r);

	वापस;
पूर्ण

/*
 * NAME:	jfs_ioc_trim()
 *
 * FUNCTION:	attempt to discard (TRIM) all मुक्त blocks from the
 *              fileप्रणाली.
 *
 * PARAMETERS:
 *	ip	- poपूर्णांकer to in-core inode;
 *	range	- the range, given by user space
 *
 * RETURN VALUES:
 *	0	- success
 *	-EIO	- i/o error
 */
पूर्णांक jfs_ioc_trim(काष्ठा inode *ip, काष्ठा fstrim_range *range)
अणु
	काष्ठा inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	काष्ठा bmap *bmp = JFS_SBI(ip->i_sb)->bmap;
	काष्ठा super_block *sb = ipbmap->i_sb;
	पूर्णांक agno, agno_end;
	u64 start, end, minlen;
	u64 trimmed = 0;

	/**
	 * convert byte values to block size of fileप्रणाली:
	 * start:	First Byte to trim
	 * len:		number of Bytes to trim from start
	 * minlen:	minimum extent length in Bytes
	 */
	start = range->start >> sb->s_blocksize_bits;
	end = start + (range->len >> sb->s_blocksize_bits) - 1;
	minlen = range->minlen >> sb->s_blocksize_bits;
	अगर (minlen == 0)
		minlen = 1;

	अगर (minlen > bmp->db_agsize ||
	    start >= bmp->db_mapsize ||
	    range->len < sb->s_blocksize)
		वापस -EINVAL;

	अगर (end >= bmp->db_mapsize)
		end = bmp->db_mapsize - 1;

	/**
	 * we trim all ag's within the range
	 */
	agno = BLKTOAG(start, JFS_SBI(ip->i_sb));
	agno_end = BLKTOAG(end, JFS_SBI(ip->i_sb));
	जबतक (agno <= agno_end) अणु
		trimmed += dbDiscardAG(ip, agno, minlen);
		agno++;
	पूर्ण
	range->len = trimmed << sb->s_blocksize_bits;

	वापस 0;
पूर्ण
