<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/partitions/sysv68.c
 *
 *  Copyright (C) 2007 Philippe De Muyter <phdm@macqel.be>
 */

#समावेश "check.h"

/*
 *	Volume ID काष्ठाure: on first 256-bytes sector of disk
 */

काष्ठा volumeid अणु
	u8	vid_unused[248];
	u8	vid_mac[8];	/* ASCII string "MOTOROLA" */
पूर्ण;

/*
 *	config block: second 256-bytes sector on disk
 */

काष्ठा dkconfig अणु
	u8	ios_unused0[128];
	__be32	ios_slcblk;	/* Slice table block number */
	__be16	ios_slccnt;	/* Number of entries in slice table */
	u8	ios_unused1[122];
पूर्ण;

/*
 *	combined volumeid and dkconfig block
 */

काष्ठा dkblk0 अणु
	काष्ठा volumeid dk_vid;
	काष्ठा dkconfig dk_ios;
पूर्ण;

/*
 *	Slice Table Structure
 */

काष्ठा slice अणु
	__be32	nblocks;		/* slice size (in blocks) */
	__be32	blkoff;			/* block offset of slice */
पूर्ण;


पूर्णांक sysv68_partition(काष्ठा parsed_partitions *state)
अणु
	पूर्णांक i, slices;
	पूर्णांक slot = 1;
	Sector sect;
	अचिन्हित अक्षर *data;
	काष्ठा dkblk0 *b;
	काष्ठा slice *slice;
	अक्षर पंचांगp[64];

	data = पढ़ो_part_sector(state, 0, &sect);
	अगर (!data)
		वापस -1;

	b = (काष्ठा dkblk0 *)data;
	अगर (स_भेद(b->dk_vid.vid_mac, "MOTOROLA", माप(b->dk_vid.vid_mac))) अणु
		put_dev_sector(sect);
		वापस 0;
	पूर्ण
	slices = be16_to_cpu(b->dk_ios.ios_slccnt);
	i = be32_to_cpu(b->dk_ios.ios_slcblk);
	put_dev_sector(sect);

	data = पढ़ो_part_sector(state, i, &sect);
	अगर (!data)
		वापस -1;

	slices -= 1; /* last slice is the whole disk */
	snम_लिखो(पंचांगp, माप(पंचांगp), "sysV68: %s(s%u)", state->name, slices);
	strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
	slice = (काष्ठा slice *)data;
	क्रम (i = 0; i < slices; i++, slice++) अणु
		अगर (slot == state->limit)
			अवरोध;
		अगर (be32_to_cpu(slice->nblocks)) अणु
			put_partition(state, slot,
				be32_to_cpu(slice->blkoff),
				be32_to_cpu(slice->nblocks));
			snम_लिखो(पंचांगp, माप(पंचांगp), "(s%u)", i);
			strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
		पूर्ण
		slot++;
	पूर्ण
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	put_dev_sector(sect);
	वापस 1;
पूर्ण
