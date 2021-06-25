<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/partitions/ultrix.c
 *
 *  Code extracted from drivers/block/genhd.c
 *
 *  Re-organised Jul 1999 Russell King
 */

#समावेश "check.h"

पूर्णांक ultrix_partition(काष्ठा parsed_partitions *state)
अणु
	पूर्णांक i;
	Sector sect;
	अचिन्हित अक्षर *data;
	काष्ठा ultrix_disklabel अणु
		s32	pt_magic;	/* magic no. indicating part. info निकासs */
		s32	pt_valid;	/* set by driver अगर pt is current */
		काष्ठा  pt_info अणु
			s32		pi_nblocks; /* no. of sectors */
			u32		pi_blkoff;  /* block offset क्रम start */
		पूर्ण pt_part[8];
	पूर्ण *label;

#घोषणा PT_MAGIC	0x032957	/* Partition magic number */
#घोषणा PT_VALID	1		/* Indicates अगर काष्ठा is valid */

	data = पढ़ो_part_sector(state, (16384 - माप(*label))/512, &sect);
	अगर (!data)
		वापस -1;
	
	label = (काष्ठा ultrix_disklabel *)(data + 512 - माप(*label));

	अगर (label->pt_magic == PT_MAGIC && label->pt_valid == PT_VALID) अणु
		क्रम (i=0; i<8; i++)
			अगर (label->pt_part[i].pi_nblocks)
				put_partition(state, i+1, 
					      label->pt_part[i].pi_blkoff,
					      label->pt_part[i].pi_nblocks);
		put_dev_sector(sect);
		strlcat(state->pp_buf, "\n", PAGE_SIZE);
		वापस 1;
	पूर्ण अन्यथा अणु
		put_dev_sector(sect);
		वापस 0;
	पूर्ण
पूर्ण
