<शैली गुरु>
/*
 * linux/fs/hfsplus/part_tbl.c
 *
 * Copyright (C) 1996-1997  Paul H. Hargrove
 * This file may be distributed under the terms of
 * the GNU General Public License.
 *
 * Original code to handle the new style Mac partition table based on
 * a patch contributed by Holger Schemel (aeglos@valinor.owl.de).
 *
 * In function preconditions the term "valid" applied to a poपूर्णांकer to
 * a काष्ठाure means that the poपूर्णांकer is non-शून्य and the काष्ठाure it
 * poपूर्णांकs to has all fields initialized to consistent values.
 *
 */

#समावेश <linux/slab.h>
#समावेश "hfsplus_fs.h"

/* offsets to various blocks */
#घोषणा HFS_DD_BLK		0 /* Driver Descriptor block */
#घोषणा HFS_PMAP_BLK		1 /* First block of partition map */
#घोषणा HFS_MDB_BLK		2 /* Block (w/i partition) of MDB */

/* magic numbers क्रम various disk blocks */
#घोषणा HFS_DRVR_DESC_MAGIC	0x4552 /* "ER": driver descriptor map */
#घोषणा HFS_OLD_PMAP_MAGIC	0x5453 /* "TS": old-type partition map */
#घोषणा HFS_NEW_PMAP_MAGIC	0x504D /* "PM": new-type partition map */
#घोषणा HFS_SUPER_MAGIC		0x4244 /* "BD": HFS MDB (super block) */
#घोषणा HFS_MFS_SUPER_MAGIC	0xD2D7 /* MFS MDB (super block) */

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
	काष्ठा old_pmap_entry अणु
		__be32	pdStart;
		__be32	pdSize;
		__be32	pdFSID;
	पूर्ण	pdEntry[42];
पूर्ण __packed;

अटल पूर्णांक hfs_parse_old_pmap(काष्ठा super_block *sb, काष्ठा old_pmap *pm,
		sector_t *part_start, sector_t *part_size)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	पूर्णांक i;

	क्रम (i = 0; i < 42; i++) अणु
		काष्ठा old_pmap_entry *p = &pm->pdEntry[i];

		अगर (p->pdStart && p->pdSize &&
		    p->pdFSID == cpu_to_be32(0x54465331)/*"TFS1"*/ &&
		    (sbi->part < 0 || sbi->part == i)) अणु
			*part_start += be32_to_cpu(p->pdStart);
			*part_size = be32_to_cpu(p->pdSize);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक hfs_parse_new_pmap(काष्ठा super_block *sb, व्योम *buf,
		काष्ठा new_pmap *pm, sector_t *part_start, sector_t *part_size)
अणु
	काष्ठा hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	पूर्णांक size = be32_to_cpu(pm->pmMapBlkCnt);
	पूर्णांक buf_size = hfsplus_min_io_size(sb);
	पूर्णांक res;
	पूर्णांक i = 0;

	करो अणु
		अगर (!स_भेद(pm->pmPartType, "Apple_HFS", 9) &&
		    (sbi->part < 0 || sbi->part == i)) अणु
			*part_start += be32_to_cpu(pm->pmPyPartStart);
			*part_size = be32_to_cpu(pm->pmPartBlkCnt);
			वापस 0;
		पूर्ण

		अगर (++i >= size)
			वापस -ENOENT;

		pm = (काष्ठा new_pmap *)((u8 *)pm + HFSPLUS_SECTOR_SIZE);
		अगर ((u8 *)pm - (u8 *)buf >= buf_size) अणु
			res = hfsplus_submit_bio(sb,
						 *part_start + HFS_PMAP_BLK + i,
						 buf, (व्योम **)&pm, REQ_OP_READ,
						 0);
			अगर (res)
				वापस res;
		पूर्ण
	पूर्ण जबतक (pm->pmSig == cpu_to_be16(HFS_NEW_PMAP_MAGIC));

	वापस -ENOENT;
पूर्ण

/*
 * Parse the partition map looking क्रम the start and length of a
 * HFS/HFS+ partition.
 */
पूर्णांक hfs_part_find(काष्ठा super_block *sb,
		sector_t *part_start, sector_t *part_size)
अणु
	व्योम *buf, *data;
	पूर्णांक res;

	buf = kदो_स्मृति(hfsplus_min_io_size(sb), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	res = hfsplus_submit_bio(sb, *part_start + HFS_PMAP_BLK,
				 buf, &data, REQ_OP_READ, 0);
	अगर (res)
		जाओ out;

	चयन (be16_to_cpu(*((__be16 *)data))) अणु
	हाल HFS_OLD_PMAP_MAGIC:
		res = hfs_parse_old_pmap(sb, data, part_start, part_size);
		अवरोध;
	हाल HFS_NEW_PMAP_MAGIC:
		res = hfs_parse_new_pmap(sb, buf, data, part_start, part_size);
		अवरोध;
	शेष:
		res = -ENOENT;
		अवरोध;
	पूर्ण
out:
	kमुक्त(buf);
	वापस res;
पूर्ण
