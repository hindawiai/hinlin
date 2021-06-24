<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/partitions/osf.c
 *
 *  Code extracted from drivers/block/genhd.c
 *
 *  Copyright (C) 1991-1998  Linus Torvalds
 *  Re-organised Feb 1998 Russell King
 */

#समावेश "check.h"

#घोषणा MAX_OSF_PARTITIONS 18
#घोषणा DISKLABELMAGIC (0x82564557UL)

पूर्णांक osf_partition(काष्ठा parsed_partitions *state)
अणु
	पूर्णांक i;
	पूर्णांक slot = 1;
	अचिन्हित पूर्णांक npartitions;
	Sector sect;
	अचिन्हित अक्षर *data;
	काष्ठा disklabel अणु
		__le32 d_magic;
		__le16 d_type,d_subtype;
		u8 d_typename[16];
		u8 d_packname[16];
		__le32 d_secsize;
		__le32 d_nsectors;
		__le32 d_ntracks;
		__le32 d_ncylinders;
		__le32 d_secpercyl;
		__le32 d_secprtunit;
		__le16 d_sparespertrack;
		__le16 d_sparespercyl;
		__le32 d_acylinders;
		__le16 d_rpm, d_पूर्णांकerleave, d_trackskew, d_cylskew;
		__le32 d_headचयन, d_trkseek, d_flags;
		__le32 d_drivedata[5];
		__le32 d_spare[5];
		__le32 d_magic2;
		__le16 d_checksum;
		__le16 d_npartitions;
		__le32 d_bbsize, d_sbsize;
		काष्ठा d_partition अणु
			__le32 p_size;
			__le32 p_offset;
			__le32 p_fsize;
			u8  p_fstype;
			u8  p_frag;
			__le16 p_cpg;
		पूर्ण d_partitions[MAX_OSF_PARTITIONS];
	पूर्ण * label;
	काष्ठा d_partition * partition;

	data = पढ़ो_part_sector(state, 0, &sect);
	अगर (!data)
		वापस -1;

	label = (काष्ठा disklabel *) (data+64);
	partition = label->d_partitions;
	अगर (le32_to_cpu(label->d_magic) != DISKLABELMAGIC) अणु
		put_dev_sector(sect);
		वापस 0;
	पूर्ण
	अगर (le32_to_cpu(label->d_magic2) != DISKLABELMAGIC) अणु
		put_dev_sector(sect);
		वापस 0;
	पूर्ण
	npartitions = le16_to_cpu(label->d_npartitions);
	अगर (npartitions > MAX_OSF_PARTITIONS) अणु
		put_dev_sector(sect);
		वापस 0;
	पूर्ण
	क्रम (i = 0 ; i < npartitions; i++, partition++) अणु
		अगर (slot == state->limit)
		        अवरोध;
		अगर (le32_to_cpu(partition->p_size))
			put_partition(state, slot,
				le32_to_cpu(partition->p_offset),
				le32_to_cpu(partition->p_size));
		slot++;
	पूर्ण
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	put_dev_sector(sect);
	वापस 1;
पूर्ण
