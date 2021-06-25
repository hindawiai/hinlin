<शैली गुरु>
/*
 *  linux/fs/hfs/part_tbl.c
 *
 * Copyright (C) 1996-1997  Paul H. Hargrove
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 * This file may be distributed under the terms of the GNU General Public License.
 *
 * Original code to handle the new style Mac partition table based on
 * a patch contributed by Holger Schemel (aeglos@valinor.owl.de).
 */

#समावेश "hfs_fs.h"

/*
 * The new style Mac partition map
 *
 * For each partition on the media there is a physical block (512-byte
 * block) containing one of these काष्ठाures.  These blocks are
 * contiguous starting at block 1.
 */
काष्ठा new_pmap अणु
	__be16	pmSig;		/* signature */
	__be16	reSigPad;	/* padding */
	__be32	pmMapBlkCnt;	/* partition blocks count */
	__be32	pmPyPartStart;	/* physical block start of partition */
	__be32	pmPartBlkCnt;	/* physical block count of partition */
	u8	pmPartName[32];	/* (null terminated?) string
				   giving the name of this
				   partition */
	u8	pmPartType[32];	/* (null terminated?) string
				   giving the type of this
				   partition */
	/* a bunch more stuff we करोn't need */
पूर्ण __packed;

/*
 * The old style Mac partition map
 *
 * The partition map consists क्रम a 2-byte signature followed by an
 * array of these काष्ठाures.  The map is terminated with an all-zero
 * one of these.
 */
काष्ठा old_pmap अणु
	__be16		pdSig;	/* Signature bytes */
	काष्ठा 	old_pmap_entry अणु
		__be32	pdStart;
		__be32	pdSize;
		__be32	pdFSID;
	पूर्ण	pdEntry[42];
पूर्ण __packed;

/*
 * hfs_part_find()
 *
 * Parse the partition map looking क्रम the
 * start and length of the 'part'th HFS partition.
 */
पूर्णांक hfs_part_find(काष्ठा super_block *sb,
		  sector_t *part_start, sector_t *part_size)
अणु
	काष्ठा buffer_head *bh;
	__be16 *data;
	पूर्णांक i, size, res;

	res = -ENOENT;
	bh = sb_bपढ़ो512(sb, *part_start + HFS_PMAP_BLK, data);
	अगर (!bh)
		वापस -EIO;

	चयन (be16_to_cpu(*data)) अणु
	हाल HFS_OLD_PMAP_MAGIC:
	  अणु
		काष्ठा old_pmap *pm;
		काष्ठा old_pmap_entry *p;

		pm = (काष्ठा old_pmap *)bh->b_data;
		p = pm->pdEntry;
		size = 42;
		क्रम (i = 0; i < size; p++, i++) अणु
			अगर (p->pdStart && p->pdSize &&
			    p->pdFSID == cpu_to_be32(0x54465331)/*"TFS1"*/ &&
			    (HFS_SB(sb)->part < 0 || HFS_SB(sb)->part == i)) अणु
				*part_start += be32_to_cpu(p->pdStart);
				*part_size = be32_to_cpu(p->pdSize);
				res = 0;
			पूर्ण
		पूर्ण
		अवरोध;
	  पूर्ण
	हाल HFS_NEW_PMAP_MAGIC:
	  अणु
		काष्ठा new_pmap *pm;

		pm = (काष्ठा new_pmap *)bh->b_data;
		size = be32_to_cpu(pm->pmMapBlkCnt);
		क्रम (i = 0; i < size;) अणु
			अगर (!स_भेद(pm->pmPartType,"Apple_HFS", 9) &&
			    (HFS_SB(sb)->part < 0 || HFS_SB(sb)->part == i)) अणु
				*part_start += be32_to_cpu(pm->pmPyPartStart);
				*part_size = be32_to_cpu(pm->pmPartBlkCnt);
				res = 0;
				अवरोध;
			पूर्ण
			brअन्यथा(bh);
			bh = sb_bपढ़ो512(sb, *part_start + HFS_PMAP_BLK + ++i, pm);
			अगर (!bh)
				वापस -EIO;
			अगर (pm->pmSig != cpu_to_be16(HFS_NEW_PMAP_MAGIC))
				अवरोध;
		पूर्ण
		अवरोध;
	  पूर्ण
	पूर्ण
	brअन्यथा(bh);

	वापस res;
पूर्ण
