<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/partitions/sun.c
 *
 *  Code extracted from drivers/block/genhd.c
 *
 *  Copyright (C) 1991-1998  Linus Torvalds
 *  Re-organised Feb 1998 Russell King
 */

#समावेश "check.h"

#घोषणा SUN_LABEL_MAGIC          0xDABE
#घोषणा SUN_VTOC_SANITY          0x600DDEEE

क्रमागत अणु
	SUN_WHOLE_DISK = 5,
	LINUX_RAID_PARTITION = 0xfd,	/* स्वतःdetect RAID partition */
पूर्ण;

पूर्णांक sun_partition(काष्ठा parsed_partitions *state)
अणु
	पूर्णांक i;
	__be16 csum;
	पूर्णांक slot = 1;
	__be16 *ush;
	Sector sect;
	काष्ठा sun_disklabel अणु
		अचिन्हित अक्षर info[128];   /* Inक्रमmative text string */
		काष्ठा sun_vtoc अणु
		    __be32 version;     /* Layout version */
		    अक्षर   volume[8];   /* Volume name */
		    __be16 nparts;      /* Number of partitions */
		    काष्ठा sun_info अणु           /* Partition hdrs, sec 2 */
			__be16 id;
			__be16 flags;
		    पूर्ण infos[8];
		    __be16 padding;     /* Alignment padding */
		    __be32 bootinfo[3];  /* Info needed by mboot */
		    __be32 sanity;       /* To verअगरy vtoc sanity */
		    __be32 reserved[10]; /* Free space */
		    __be32 बारtamp[8]; /* Partition बारtamp */
		पूर्ण vtoc;
		__be32 ग_लिखो_reinकाष्ठा; /* sectors to skip, ग_लिखोs */
		__be32 पढ़ो_reinकाष्ठा;  /* sectors to skip, पढ़ोs */
		अचिन्हित अक्षर spare[148]; /* Padding */
		__be16 rspeed;     /* Disk rotational speed */
		__be16 pcylcount;  /* Physical cylinder count */
		__be16 sparecyl;   /* extra sects per cylinder */
		__be16 obs1;       /* gap1 */
		__be16 obs2;       /* gap2 */
		__be16 ilfact;     /* Interleave factor */
		__be16 ncyl;       /* Data cylinder count */
		__be16 nacyl;      /* Alt. cylinder count */
		__be16 ntrks;      /* Tracks per cylinder */
		__be16 nsect;      /* Sectors per track */
		__be16 obs3;       /* bhead - Label head offset */
		__be16 obs4;       /* ppart - Physical Partition */
		काष्ठा sun_partition अणु
			__be32 start_cylinder;
			__be32 num_sectors;
		पूर्ण partitions[8];
		__be16 magic;      /* Magic number */
		__be16 csum;       /* Label xor'd checksum */
	पूर्ण * label;
	काष्ठा sun_partition *p;
	अचिन्हित दीर्घ spc;
	अक्षर b[BDEVNAME_SIZE];
	पूर्णांक use_vtoc;
	पूर्णांक nparts;

	label = पढ़ो_part_sector(state, 0, &sect);
	अगर (!label)
		वापस -1;

	p = label->partitions;
	अगर (be16_to_cpu(label->magic) != SUN_LABEL_MAGIC) अणु
/*		prपूर्णांकk(KERN_INFO "Dev %s Sun disklabel: bad magic %04x\n",
		       bdevname(bdev, b), be16_to_cpu(label->magic)); */
		put_dev_sector(sect);
		वापस 0;
	पूर्ण
	/* Look at the checksum */
	ush = ((__be16 *) (label+1)) - 1;
	क्रम (csum = 0; ush >= ((__be16 *) label);)
		csum ^= *ush--;
	अगर (csum) अणु
		prपूर्णांकk("Dev %s Sun disklabel: Csum bad, label corrupted\n",
		       bdevname(state->bdev, b));
		put_dev_sector(sect);
		वापस 0;
	पूर्ण

	/* Check to see अगर we can use the VTOC table */
	use_vtoc = ((be32_to_cpu(label->vtoc.sanity) == SUN_VTOC_SANITY) &&
		    (be32_to_cpu(label->vtoc.version) == 1) &&
		    (be16_to_cpu(label->vtoc.nparts) <= 8));

	/* Use 8 partition entries अगर not specअगरied in validated VTOC */
	nparts = (use_vtoc) ? be16_to_cpu(label->vtoc.nparts) : 8;

	/*
	 * So that old Linux-Sun partitions जारी to work,
	 * alow the VTOC to be used under the additional condition ...
	 */
	use_vtoc = use_vtoc || !(label->vtoc.sanity ||
				 label->vtoc.version || label->vtoc.nparts);
	spc = be16_to_cpu(label->ntrks) * be16_to_cpu(label->nsect);
	क्रम (i = 0; i < nparts; i++, p++) अणु
		अचिन्हित दीर्घ st_sector;
		अचिन्हित पूर्णांक num_sectors;

		st_sector = be32_to_cpu(p->start_cylinder) * spc;
		num_sectors = be32_to_cpu(p->num_sectors);
		अगर (num_sectors) अणु
			put_partition(state, slot, st_sector, num_sectors);
			state->parts[slot].flags = 0;
			अगर (use_vtoc) अणु
				अगर (be16_to_cpu(label->vtoc.infos[i].id) == LINUX_RAID_PARTITION)
					state->parts[slot].flags |= ADDPART_FLAG_RAID;
				अन्यथा अगर (be16_to_cpu(label->vtoc.infos[i].id) == SUN_WHOLE_DISK)
					state->parts[slot].flags |= ADDPART_FLAG_WHOLEDISK;
			पूर्ण
		पूर्ण
		slot++;
	पूर्ण
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	put_dev_sector(sect);
	वापस 1;
पूर्ण
