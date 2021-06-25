<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/partitions/karma.c
 *  Rio Karma partition info.
 *
 *  Copyright (C) 2006 Bob Copeland (me@bobcopeland.com)
 *  based on osf.c
 */

#समावेश "check.h"
#समावेश <linux/compiler.h>

#घोषणा KARMA_LABEL_MAGIC		0xAB56

पूर्णांक karma_partition(काष्ठा parsed_partitions *state)
अणु
	पूर्णांक i;
	पूर्णांक slot = 1;
	Sector sect;
	अचिन्हित अक्षर *data;
	काष्ठा disklabel अणु
		u8 d_reserved[270];
		काष्ठा d_partition अणु
			__le32 p_res;
			u8 p_fstype;
			u8 p_res2[3];
			__le32 p_offset;
			__le32 p_size;
		पूर्ण d_partitions[2];
		u8 d_blank[208];
		__le16 d_magic;
	पूर्ण __packed *label;
	काष्ठा d_partition *p;

	data = पढ़ो_part_sector(state, 0, &sect);
	अगर (!data)
		वापस -1;

	label = (काष्ठा disklabel *)data;
	अगर (le16_to_cpu(label->d_magic) != KARMA_LABEL_MAGIC) अणु
		put_dev_sector(sect);
		वापस 0;
	पूर्ण

	p = label->d_partitions;
	क्रम (i = 0 ; i < 2; i++, p++) अणु
		अगर (slot == state->limit)
			अवरोध;

		अगर (p->p_fstype == 0x4d && le32_to_cpu(p->p_size)) अणु
			put_partition(state, slot, le32_to_cpu(p->p_offset),
				le32_to_cpu(p->p_size));
		पूर्ण
		slot++;
	पूर्ण
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	put_dev_sector(sect);
	वापस 1;
पूर्ण

