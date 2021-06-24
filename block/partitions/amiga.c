<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/partitions/amiga.c
 *
 *  Code extracted from drivers/block/genhd.c
 *
 *  Copyright (C) 1991-1998  Linus Torvalds
 *  Re-organised Feb 1998 Russell King
 */

#घोषणा pr_fmt(fmt) fmt

#समावेश <linux/types.h>
#समावेश <linux/affs_hardblocks.h>

#समावेश "check.h"

अटल __अंतरभूत__ u32
checksum_block(__be32 *m, पूर्णांक size)
अणु
	u32 sum = 0;

	जबतक (size--)
		sum += be32_to_cpu(*m++);
	वापस sum;
पूर्ण

पूर्णांक amiga_partition(काष्ठा parsed_partitions *state)
अणु
	Sector sect;
	अचिन्हित अक्षर *data;
	काष्ठा RigidDiskBlock *rdb;
	काष्ठा PartitionBlock *pb;
	पूर्णांक start_sect, nr_sects, blk, part, res = 0;
	पूर्णांक blksize = 1;	/* Multiplier क्रम disk block size */
	पूर्णांक slot = 1;
	अक्षर b[BDEVNAME_SIZE];

	क्रम (blk = 0; ; blk++, put_dev_sector(sect)) अणु
		अगर (blk == RDB_ALLOCATION_LIMIT)
			जाओ rdb_करोne;
		data = पढ़ो_part_sector(state, blk, &sect);
		अगर (!data) अणु
			pr_err("Dev %s: unable to read RDB block %d\n",
			       bdevname(state->bdev, b), blk);
			res = -1;
			जाओ rdb_करोne;
		पूर्ण
		अगर (*(__be32 *)data != cpu_to_be32(IDNAME_RIGIDDISK))
			जारी;

		rdb = (काष्ठा RigidDiskBlock *)data;
		अगर (checksum_block((__be32 *)data, be32_to_cpu(rdb->rdb_SummedLongs) & 0x7F) == 0)
			अवरोध;
		/* Try again with 0xdc..0xdf zeroed, Winकरोws might have
		 * trashed it.
		 */
		*(__be32 *)(data+0xdc) = 0;
		अगर (checksum_block((__be32 *)data,
				be32_to_cpu(rdb->rdb_SummedLongs) & 0x7F)==0) अणु
			pr_err("Trashed word at 0xd0 in block %d ignored in checksum calculation\n",
			       blk);
			अवरोध;
		पूर्ण

		pr_err("Dev %s: RDB in block %d has bad checksum\n",
		       bdevname(state->bdev, b), blk);
	पूर्ण

	/* blksize is blocks per 512 byte standard block */
	blksize = be32_to_cpu( rdb->rdb_BlockBytes ) / 512;

	अणु
		अक्षर पंचांगp[7 + 10 + 1 + 1];

		/* Be more inक्रमmative */
		snम_लिखो(पंचांगp, माप(पंचांगp), " RDSK (%d)", blksize * 512);
		strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
	पूर्ण
	blk = be32_to_cpu(rdb->rdb_PartitionList);
	put_dev_sector(sect);
	क्रम (part = 1; blk>0 && part<=16; part++, put_dev_sector(sect)) अणु
		blk *= blksize;	/* Read in terms partition table understands */
		data = पढ़ो_part_sector(state, blk, &sect);
		अगर (!data) अणु
			pr_err("Dev %s: unable to read partition block %d\n",
			       bdevname(state->bdev, b), blk);
			res = -1;
			जाओ rdb_करोne;
		पूर्ण
		pb  = (काष्ठा PartitionBlock *)data;
		blk = be32_to_cpu(pb->pb_Next);
		अगर (pb->pb_ID != cpu_to_be32(IDNAME_PARTITION))
			जारी;
		अगर (checksum_block((__be32 *)pb, be32_to_cpu(pb->pb_SummedLongs) & 0x7F) != 0 )
			जारी;

		/* Tell Kernel about it */

		nr_sects = (be32_to_cpu(pb->pb_Environment[10]) + 1 -
			    be32_to_cpu(pb->pb_Environment[9])) *
			   be32_to_cpu(pb->pb_Environment[3]) *
			   be32_to_cpu(pb->pb_Environment[5]) *
			   blksize;
		अगर (!nr_sects)
			जारी;
		start_sect = be32_to_cpu(pb->pb_Environment[9]) *
			     be32_to_cpu(pb->pb_Environment[3]) *
			     be32_to_cpu(pb->pb_Environment[5]) *
			     blksize;
		put_partition(state,slot++,start_sect,nr_sects);
		अणु
			/* Be even more inक्रमmative to aid mounting */
			अक्षर करोstype[4];
			अक्षर पंचांगp[42];

			__be32 *dt = (__be32 *)करोstype;
			*dt = pb->pb_Environment[16];
			अगर (करोstype[3] < ' ')
				snम_लिखो(पंचांगp, माप(पंचांगp), " (%c%c%c^%c)",
					करोstype[0], करोstype[1],
					करोstype[2], करोstype[3] + '@' );
			अन्यथा
				snम_लिखो(पंचांगp, माप(पंचांगp), " (%c%c%c%c)",
					करोstype[0], करोstype[1],
					करोstype[2], करोstype[3]);
			strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
			snम_लिखो(पंचांगp, माप(पंचांगp), "(res %d spb %d)",
				be32_to_cpu(pb->pb_Environment[6]),
				be32_to_cpu(pb->pb_Environment[4]));
			strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
		पूर्ण
		res = 1;
	पूर्ण
	strlcat(state->pp_buf, "\n", PAGE_SIZE);

rdb_करोne:
	वापस res;
पूर्ण
