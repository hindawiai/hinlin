<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/partitions/msकरोs.c
 *
 *  Code extracted from drivers/block/genhd.c
 *  Copyright (C) 1991-1998  Linus Torvalds
 *
 *  Thanks to Branko Lankester, lankeste@fwi.uva.nl, who found a bug
 *  in the early extended-partition checks and added DM partitions
 *
 *  Support क्रम DiskManager v6.0x added by Mark Lord,
 *  with inक्रमmation provided by OnTrack.  This now works क्रम linux fdisk
 *  and LILO, as well as loadlin and bootln.  Note that disks other than
 *  /dev/hda *must* have a "DOS" type 0x51 partition in the first slot (hda1).
 *
 *  More flexible handling of extended partitions - aeb, 950831
 *
 *  Check partition table on IDE disks क्रम common CHS translations
 *
 *  Re-organised Feb 1998 Russell King
 *
 *  BSD disklabel support by Yossi Gottlieb <yogo@math.tau.ac.il>
 *  updated by Marc Espie <Marc.Espie@खोलोbsd.org>
 *
 *  Unixware slices support by Andrzej Krzysztofowicz <ankry@mअगर.pg.gda.pl>
 *  and Krzysztof G. Baranowski <kgb@knm.org.pl>
 */
#समावेश <linux/msकरोs_fs.h>
#समावेश <linux/msकरोs_partition.h>

#समावेश "check.h"
#समावेश "efi.h"

/*
 * Many architectures करोn't like unaligned accesses, जबतक
 * the nr_sects and start_sect partition table entries are
 * at a 2 (mod 4) address.
 */
#समावेश <यंत्र/unaligned.h>

#घोषणा SYS_IND(p)	get_unaligned(&p->sys_ind)

अटल अंतरभूत sector_t nr_sects(काष्ठा msकरोs_partition *p)
अणु
	वापस (sector_t)get_unaligned_le32(&p->nr_sects);
पूर्ण

अटल अंतरभूत sector_t start_sect(काष्ठा msकरोs_partition *p)
अणु
	वापस (sector_t)get_unaligned_le32(&p->start_sect);
पूर्ण

अटल अंतरभूत पूर्णांक is_extended_partition(काष्ठा msकरोs_partition *p)
अणु
	वापस (SYS_IND(p) == DOS_EXTENDED_PARTITION ||
		SYS_IND(p) == WIN98_EXTENDED_PARTITION ||
		SYS_IND(p) == LINUX_EXTENDED_PARTITION);
पूर्ण

#घोषणा MSDOS_LABEL_MAGIC1	0x55
#घोषणा MSDOS_LABEL_MAGIC2	0xAA

अटल अंतरभूत पूर्णांक
msकरोs_magic_present(अचिन्हित अक्षर *p)
अणु
	वापस (p[0] == MSDOS_LABEL_MAGIC1 && p[1] == MSDOS_LABEL_MAGIC2);
पूर्ण

/* Value is EBCDIC 'IBMA' */
#घोषणा AIX_LABEL_MAGIC1	0xC9
#घोषणा AIX_LABEL_MAGIC2	0xC2
#घोषणा AIX_LABEL_MAGIC3	0xD4
#घोषणा AIX_LABEL_MAGIC4	0xC1
अटल पूर्णांक aix_magic_present(काष्ठा parsed_partitions *state, अचिन्हित अक्षर *p)
अणु
	काष्ठा msकरोs_partition *pt = (काष्ठा msकरोs_partition *) (p + 0x1be);
	Sector sect;
	अचिन्हित अक्षर *d;
	पूर्णांक slot, ret = 0;

	अगर (!(p[0] == AIX_LABEL_MAGIC1 &&
		p[1] == AIX_LABEL_MAGIC2 &&
		p[2] == AIX_LABEL_MAGIC3 &&
		p[3] == AIX_LABEL_MAGIC4))
		वापस 0;

	/*
	 * Assume the partition table is valid अगर Linux partitions exists.
	 * Note that old Solaris/x86 partitions use the same indicator as
	 * Linux swap partitions, so we consider that a Linux partition as
	 * well.
	 */
	क्रम (slot = 1; slot <= 4; slot++, pt++) अणु
		अगर (pt->sys_ind == SOLARIS_X86_PARTITION ||
		    pt->sys_ind == LINUX_RAID_PARTITION ||
		    pt->sys_ind == LINUX_DATA_PARTITION ||
		    pt->sys_ind == LINUX_LVM_PARTITION ||
		    is_extended_partition(pt))
			वापस 0;
	पूर्ण
	d = पढ़ो_part_sector(state, 7, &sect);
	अगर (d) अणु
		अगर (d[0] == '_' && d[1] == 'L' && d[2] == 'V' && d[3] == 'M')
			ret = 1;
		put_dev_sector(sect);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम set_info(काष्ठा parsed_partitions *state, पूर्णांक slot,
		     u32 disksig)
अणु
	काष्ठा partition_meta_info *info = &state->parts[slot].info;

	snम_लिखो(info->uuid, माप(info->uuid), "%08x-%02x", disksig,
		 slot);
	info->volname[0] = 0;
	state->parts[slot].has_info = true;
पूर्ण

/*
 * Create devices क्रम each logical partition in an extended partition.
 * The logical partitions क्रमm a linked list, with each entry being
 * a partition table with two entries.  The first entry
 * is the real data partition (with a start relative to the partition
 * table start).  The second is a poपूर्णांकer to the next logical partition
 * (with a start relative to the entire extended partition).
 * We करो not create a Linux partition क्रम the partition tables, but
 * only क्रम the actual data partitions.
 */

अटल व्योम parse_extended(काष्ठा parsed_partitions *state,
			   sector_t first_sector, sector_t first_size,
			   u32 disksig)
अणु
	काष्ठा msकरोs_partition *p;
	Sector sect;
	अचिन्हित अक्षर *data;
	sector_t this_sector, this_size;
	sector_t sector_size = bdev_logical_block_size(state->bdev) / 512;
	पूर्णांक loopct = 0;		/* number of links followed
				   without finding a data partition */
	पूर्णांक i;

	this_sector = first_sector;
	this_size = first_size;

	जबतक (1) अणु
		अगर (++loopct > 100)
			वापस;
		अगर (state->next == state->limit)
			वापस;
		data = पढ़ो_part_sector(state, this_sector, &sect);
		अगर (!data)
			वापस;

		अगर (!msकरोs_magic_present(data + 510))
			जाओ करोne;

		p = (काष्ठा msकरोs_partition *) (data + 0x1be);

		/*
		 * Usually, the first entry is the real data partition,
		 * the 2nd entry is the next extended partition, or empty,
		 * and the 3rd and 4th entries are unused.
		 * However, DRDOS someबार has the extended partition as
		 * the first entry (when the data partition is empty),
		 * and OS/2 seems to use all four entries.
		 */

		/*
		 * First process the data partition(s)
		 */
		क्रम (i = 0; i < 4; i++, p++) अणु
			sector_t offs, size, next;

			अगर (!nr_sects(p) || is_extended_partition(p))
				जारी;

			/* Check the 3rd and 4th entries -
			   these someबार contain अक्रमom garbage */
			offs = start_sect(p)*sector_size;
			size = nr_sects(p)*sector_size;
			next = this_sector + offs;
			अगर (i >= 2) अणु
				अगर (offs + size > this_size)
					जारी;
				अगर (next < first_sector)
					जारी;
				अगर (next + size > first_sector + first_size)
					जारी;
			पूर्ण

			put_partition(state, state->next, next, size);
			set_info(state, state->next, disksig);
			अगर (SYS_IND(p) == LINUX_RAID_PARTITION)
				state->parts[state->next].flags = ADDPART_FLAG_RAID;
			loopct = 0;
			अगर (++state->next == state->limit)
				जाओ करोne;
		पूर्ण
		/*
		 * Next, process the (first) extended partition, अगर present.
		 * (So far, there seems to be no reason to make
		 *  parse_extended()  recursive and allow a tree
		 *  of extended partitions.)
		 * It should be a link to the next logical partition.
		 */
		p -= 4;
		क्रम (i = 0; i < 4; i++, p++)
			अगर (nr_sects(p) && is_extended_partition(p))
				अवरोध;
		अगर (i == 4)
			जाओ करोne;	 /* nothing left to करो */

		this_sector = first_sector + start_sect(p) * sector_size;
		this_size = nr_sects(p) * sector_size;
		put_dev_sector(sect);
	पूर्ण
करोne:
	put_dev_sector(sect);
पूर्ण

#घोषणा SOLARIS_X86_NUMSLICE	16
#घोषणा SOLARIS_X86_VTOC_SANE	(0x600DDEEEUL)

काष्ठा solaris_x86_slice अणु
	__le16 s_tag;		/* ID tag of partition */
	__le16 s_flag;		/* permission flags */
	__le32 s_start;		/* start sector no of partition */
	__le32 s_size;		/* # of blocks in partition */
पूर्ण;

काष्ठा solaris_x86_vtoc अणु
	अचिन्हित पूर्णांक v_bootinfo[3];	/* info needed by mboot */
	__le32 v_sanity;		/* to verअगरy vtoc sanity */
	__le32 v_version;		/* layout version */
	अक्षर	v_volume[8];		/* volume name */
	__le16	v_sectorsz;		/* sector size in bytes */
	__le16	v_nparts;		/* number of partitions */
	अचिन्हित पूर्णांक v_reserved[10];	/* मुक्त space */
	काष्ठा solaris_x86_slice
		v_slice[SOLARIS_X86_NUMSLICE]; /* slice headers */
	अचिन्हित पूर्णांक बारtamp[SOLARIS_X86_NUMSLICE]; /* बारtamp */
	अक्षर	v_asciilabel[128];	/* क्रम compatibility */
पूर्ण;

/* james@bpgc.com: Solaris has a nasty indicator: 0x82 which also
   indicates linux swap.  Be careful beक्रमe believing this is Solaris. */

अटल व्योम parse_solaris_x86(काष्ठा parsed_partitions *state,
			      sector_t offset, sector_t size, पूर्णांक origin)
अणु
#अगर_घोषित CONFIG_SOLARIS_X86_PARTITION
	Sector sect;
	काष्ठा solaris_x86_vtoc *v;
	पूर्णांक i;
	लघु max_nparts;

	v = पढ़ो_part_sector(state, offset + 1, &sect);
	अगर (!v)
		वापस;
	अगर (le32_to_cpu(v->v_sanity) != SOLARIS_X86_VTOC_SANE) अणु
		put_dev_sector(sect);
		वापस;
	पूर्ण
	अणु
		अक्षर पंचांगp[1 + BDEVNAME_SIZE + 10 + 11 + 1];

		snम_लिखो(पंचांगp, माप(पंचांगp), " %s%d: <solaris:", state->name, origin);
		strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
	पूर्ण
	अगर (le32_to_cpu(v->v_version) != 1) अणु
		अक्षर पंचांगp[64];

		snम_लिखो(पंचांगp, माप(पंचांगp), "  cannot handle version %d vtoc>\n",
			 le32_to_cpu(v->v_version));
		strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
		put_dev_sector(sect);
		वापस;
	पूर्ण
	/* Ensure we can handle previous हाल of VTOC with 8 entries gracefully */
	max_nparts = le16_to_cpu(v->v_nparts) > 8 ? SOLARIS_X86_NUMSLICE : 8;
	क्रम (i = 0; i < max_nparts && state->next < state->limit; i++) अणु
		काष्ठा solaris_x86_slice *s = &v->v_slice[i];
		अक्षर पंचांगp[3 + 10 + 1 + 1];

		अगर (s->s_size == 0)
			जारी;
		snम_लिखो(पंचांगp, माप(पंचांगp), " [s%d]", i);
		strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
		/* solaris partitions are relative to current MS-DOS
		 * one; must add the offset of the current partition */
		put_partition(state, state->next++,
				 le32_to_cpu(s->s_start)+offset,
				 le32_to_cpu(s->s_size));
	पूर्ण
	put_dev_sector(sect);
	strlcat(state->pp_buf, " >\n", PAGE_SIZE);
#पूर्ण_अगर
पूर्ण

/* check against BSD src/sys/sys/disklabel.h क्रम consistency */
#घोषणा BSD_DISKMAGIC	(0x82564557UL)	/* The disk magic number */
#घोषणा BSD_MAXPARTITIONS	16
#घोषणा OPENBSD_MAXPARTITIONS	16
#घोषणा BSD_FS_UNUSED		0 /* disklabel unused partition entry ID */
काष्ठा bsd_disklabel अणु
	__le32	d_magic;		/* the magic number */
	__s16	d_type;			/* drive type */
	__s16	d_subtype;		/* controller/d_type specअगरic */
	अक्षर	d_typename[16];		/* type name, e.g. "eagle" */
	अक्षर	d_packname[16];		/* pack identअगरier */
	__u32	d_secsize;		/* # of bytes per sector */
	__u32	d_nsectors;		/* # of data sectors per track */
	__u32	d_ntracks;		/* # of tracks per cylinder */
	__u32	d_ncylinders;		/* # of data cylinders per unit */
	__u32	d_secpercyl;		/* # of data sectors per cylinder */
	__u32	d_secperunit;		/* # of data sectors per unit */
	__u16	d_sparespertrack;	/* # of spare sectors per track */
	__u16	d_sparespercyl;		/* # of spare sectors per cylinder */
	__u32	d_acylinders;		/* # of alt. cylinders per unit */
	__u16	d_rpm;			/* rotational speed */
	__u16	d_पूर्णांकerleave;		/* hardware sector पूर्णांकerleave */
	__u16	d_trackskew;		/* sector 0 skew, per track */
	__u16	d_cylskew;		/* sector 0 skew, per cylinder */
	__u32	d_headचयन;		/* head चयन समय, usec */
	__u32	d_trkseek;		/* track-to-track seek, usec */
	__u32	d_flags;		/* generic flags */
#घोषणा NDDATA 5
	__u32	d_drivedata[NDDATA];	/* drive-type specअगरic inक्रमmation */
#घोषणा NSPARE 5
	__u32	d_spare[NSPARE];	/* reserved क्रम future use */
	__le32	d_magic2;		/* the magic number (again) */
	__le16	d_checksum;		/* xor of data incl. partitions */

			/* fileप्रणाली and partition inक्रमmation: */
	__le16	d_npartitions;		/* number of partitions in following */
	__le32	d_bbsize;		/* size of boot area at sn0, bytes */
	__le32	d_sbsize;		/* max size of fs superblock, bytes */
	काष्ठा	bsd_partition अणु		/* the partition table */
		__le32	p_size;		/* number of sectors in partition */
		__le32	p_offset;	/* starting sector */
		__le32	p_fsize;	/* fileप्रणाली basic fragment size */
		__u8	p_fstype;	/* fileप्रणाली type, see below */
		__u8	p_frag;		/* fileप्रणाली fragments per block */
		__le16	p_cpg;		/* fileप्रणाली cylinders per group */
	पूर्ण d_partitions[BSD_MAXPARTITIONS];	/* actually may be more */
पूर्ण;

#अगर defined(CONFIG_BSD_DISKLABEL)
/*
 * Create devices क्रम BSD partitions listed in a disklabel, under a
 * करोs-like partition. See parse_extended() क्रम more inक्रमmation.
 */
अटल व्योम parse_bsd(काष्ठा parsed_partitions *state,
		      sector_t offset, sector_t size, पूर्णांक origin, अक्षर *flavour,
		      पूर्णांक max_partitions)
अणु
	Sector sect;
	काष्ठा bsd_disklabel *l;
	काष्ठा bsd_partition *p;
	अक्षर पंचांगp[64];

	l = पढ़ो_part_sector(state, offset + 1, &sect);
	अगर (!l)
		वापस;
	अगर (le32_to_cpu(l->d_magic) != BSD_DISKMAGIC) अणु
		put_dev_sector(sect);
		वापस;
	पूर्ण

	snम_लिखो(पंचांगp, माप(पंचांगp), " %s%d: <%s:", state->name, origin, flavour);
	strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);

	अगर (le16_to_cpu(l->d_npartitions) < max_partitions)
		max_partitions = le16_to_cpu(l->d_npartitions);
	क्रम (p = l->d_partitions; p - l->d_partitions < max_partitions; p++) अणु
		sector_t bsd_start, bsd_size;

		अगर (state->next == state->limit)
			अवरोध;
		अगर (p->p_fstype == BSD_FS_UNUSED)
			जारी;
		bsd_start = le32_to_cpu(p->p_offset);
		bsd_size = le32_to_cpu(p->p_size);
		/* FreeBSD has relative offset अगर C partition offset is zero */
		अगर (स_भेद(flavour, "bsd\0", 4) == 0 &&
		    le32_to_cpu(l->d_partitions[2].p_offset) == 0)
			bsd_start += offset;
		अगर (offset == bsd_start && size == bsd_size)
			/* full parent partition, we have it alपढ़ोy */
			जारी;
		अगर (offset > bsd_start || offset+size < bsd_start+bsd_size) अणु
			strlcat(state->pp_buf, "bad subpartition - ignored\n", PAGE_SIZE);
			जारी;
		पूर्ण
		put_partition(state, state->next++, bsd_start, bsd_size);
	पूर्ण
	put_dev_sector(sect);
	अगर (le16_to_cpu(l->d_npartitions) > max_partitions) अणु
		snम_लिखो(पंचांगp, माप(पंचांगp), " (ignored %d more)",
			 le16_to_cpu(l->d_npartitions) - max_partitions);
		strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
	पूर्ण
	strlcat(state->pp_buf, " >\n", PAGE_SIZE);
पूर्ण
#पूर्ण_अगर

अटल व्योम parse_मुक्तbsd(काष्ठा parsed_partitions *state,
			  sector_t offset, sector_t size, पूर्णांक origin)
अणु
#अगर_घोषित CONFIG_BSD_DISKLABEL
	parse_bsd(state, offset, size, origin, "bsd", BSD_MAXPARTITIONS);
#पूर्ण_अगर
पूर्ण

अटल व्योम parse_netbsd(काष्ठा parsed_partitions *state,
			 sector_t offset, sector_t size, पूर्णांक origin)
अणु
#अगर_घोषित CONFIG_BSD_DISKLABEL
	parse_bsd(state, offset, size, origin, "netbsd", BSD_MAXPARTITIONS);
#पूर्ण_अगर
पूर्ण

अटल व्योम parse_खोलोbsd(काष्ठा parsed_partitions *state,
			  sector_t offset, sector_t size, पूर्णांक origin)
अणु
#अगर_घोषित CONFIG_BSD_DISKLABEL
	parse_bsd(state, offset, size, origin, "openbsd",
		  OPENBSD_MAXPARTITIONS);
#पूर्ण_अगर
पूर्ण

#घोषणा UNIXWARE_DISKMAGIC     (0xCA5E600DUL)	/* The disk magic number */
#घोषणा UNIXWARE_DISKMAGIC2    (0x600DDEEEUL)	/* The slice table magic nr */
#घोषणा UNIXWARE_NUMSLICE      16
#घोषणा UNIXWARE_FS_UNUSED     0		/* Unused slice entry ID */

काष्ठा unixware_slice अणु
	__le16   s_label;	/* label */
	__le16   s_flags;	/* permission flags */
	__le32   start_sect;	/* starting sector */
	__le32   nr_sects;	/* number of sectors in slice */
पूर्ण;

काष्ठा unixware_disklabel अणु
	__le32	d_type;			/* drive type */
	__le32	d_magic;		/* the magic number */
	__le32	d_version;		/* version number */
	अक्षर	d_serial[12];		/* serial number of the device */
	__le32	d_ncylinders;		/* # of data cylinders per device */
	__le32	d_ntracks;		/* # of tracks per cylinder */
	__le32	d_nsectors;		/* # of data sectors per track */
	__le32	d_secsize;		/* # of bytes per sector */
	__le32	d_part_start;		/* # of first sector of this partition*/
	__le32	d_unknown1[12];		/* ? */
	__le32	d_alt_tbl;		/* byte offset of alternate table */
	__le32	d_alt_len;		/* byte length of alternate table */
	__le32	d_phys_cyl;		/* # of physical cylinders per device */
	__le32	d_phys_trk;		/* # of physical tracks per cylinder */
	__le32	d_phys_sec;		/* # of physical sectors per track */
	__le32	d_phys_bytes;		/* # of physical bytes per sector */
	__le32	d_unknown2;		/* ? */
	__le32	d_unknown3;		/* ? */
	__le32	d_pad[8];		/* pad */

	काष्ठा unixware_vtoc अणु
		__le32	v_magic;		/* the magic number */
		__le32	v_version;		/* version number */
		अक्षर	v_name[8];		/* volume name */
		__le16	v_nslices;		/* # of slices */
		__le16	v_unknown1;		/* ? */
		__le32	v_reserved[10];		/* reserved */
		काष्ठा unixware_slice
			v_slice[UNIXWARE_NUMSLICE];	/* slice headers */
	पूर्ण vtoc;
पूर्ण;  /* 408 */

/*
 * Create devices क्रम Unixware partitions listed in a disklabel, under a
 * करोs-like partition. See parse_extended() क्रम more inक्रमmation.
 */
अटल व्योम parse_unixware(काष्ठा parsed_partitions *state,
			   sector_t offset, sector_t size, पूर्णांक origin)
अणु
#अगर_घोषित CONFIG_UNIXWARE_DISKLABEL
	Sector sect;
	काष्ठा unixware_disklabel *l;
	काष्ठा unixware_slice *p;

	l = पढ़ो_part_sector(state, offset + 29, &sect);
	अगर (!l)
		वापस;
	अगर (le32_to_cpu(l->d_magic) != UNIXWARE_DISKMAGIC ||
	    le32_to_cpu(l->vtoc.v_magic) != UNIXWARE_DISKMAGIC2) अणु
		put_dev_sector(sect);
		वापस;
	पूर्ण
	अणु
		अक्षर पंचांगp[1 + BDEVNAME_SIZE + 10 + 12 + 1];

		snम_लिखो(पंचांगp, माप(पंचांगp), " %s%d: <unixware:", state->name, origin);
		strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
	पूर्ण
	p = &l->vtoc.v_slice[1];
	/* I omit the 0th slice as it is the same as whole disk. */
	जबतक (p - &l->vtoc.v_slice[0] < UNIXWARE_NUMSLICE) अणु
		अगर (state->next == state->limit)
			अवरोध;

		अगर (p->s_label != UNIXWARE_FS_UNUSED)
			put_partition(state, state->next++,
				      le32_to_cpu(p->start_sect),
				      le32_to_cpu(p->nr_sects));
		p++;
	पूर्ण
	put_dev_sector(sect);
	strlcat(state->pp_buf, " >\n", PAGE_SIZE);
#पूर्ण_अगर
पूर्ण

#घोषणा MINIX_NR_SUBPARTITIONS  4

/*
 * Minix 2.0.0/2.0.2 subpartition support.
 * Anand Krishnamurthy <anandk@wiproge.med.ge.com>
 * Rajeev V. Pillai    <rajeevvp@yahoo.com>
 */
अटल व्योम parse_minix(काष्ठा parsed_partitions *state,
			sector_t offset, sector_t size, पूर्णांक origin)
अणु
#अगर_घोषित CONFIG_MINIX_SUBPARTITION
	Sector sect;
	अचिन्हित अक्षर *data;
	काष्ठा msकरोs_partition *p;
	पूर्णांक i;

	data = पढ़ो_part_sector(state, offset, &sect);
	अगर (!data)
		वापस;

	p = (काष्ठा msकरोs_partition *)(data + 0x1be);

	/* The first sector of a Minix partition can have either
	 * a secondary MBR describing its subpartitions, or
	 * the normal boot sector. */
	अगर (msकरोs_magic_present(data + 510) &&
	    SYS_IND(p) == MINIX_PARTITION) अणु /* subpartition table present */
		अक्षर पंचांगp[1 + BDEVNAME_SIZE + 10 + 9 + 1];

		snम_लिखो(पंचांगp, माप(पंचांगp), " %s%d: <minix:", state->name, origin);
		strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
		क्रम (i = 0; i < MINIX_NR_SUBPARTITIONS; i++, p++) अणु
			अगर (state->next == state->limit)
				अवरोध;
			/* add each partition in use */
			अगर (SYS_IND(p) == MINIX_PARTITION)
				put_partition(state, state->next++,
					      start_sect(p), nr_sects(p));
		पूर्ण
		strlcat(state->pp_buf, " >\n", PAGE_SIZE);
	पूर्ण
	put_dev_sector(sect);
#पूर्ण_अगर /* CONFIG_MINIX_SUBPARTITION */
पूर्ण

अटल काष्ठा अणु
	अचिन्हित अक्षर id;
	व्योम (*parse)(काष्ठा parsed_partitions *, sector_t, sector_t, पूर्णांक);
पूर्ण subtypes[] = अणु
	अणुFREEBSD_PARTITION, parse_मुक्तbsdपूर्ण,
	अणुNETBSD_PARTITION, parse_netbsdपूर्ण,
	अणुOPENBSD_PARTITION, parse_खोलोbsdपूर्ण,
	अणुMINIX_PARTITION, parse_minixपूर्ण,
	अणुUNIXWARE_PARTITION, parse_unixwareपूर्ण,
	अणुSOLARIS_X86_PARTITION, parse_solaris_x86पूर्ण,
	अणुNEW_SOLARIS_X86_PARTITION, parse_solaris_x86पूर्ण,
	अणु0, शून्यपूर्ण,
पूर्ण;

पूर्णांक msकरोs_partition(काष्ठा parsed_partitions *state)
अणु
	sector_t sector_size = bdev_logical_block_size(state->bdev) / 512;
	Sector sect;
	अचिन्हित अक्षर *data;
	काष्ठा msकरोs_partition *p;
	काष्ठा fat_boot_sector *fb;
	पूर्णांक slot;
	u32 disksig;

	data = पढ़ो_part_sector(state, 0, &sect);
	अगर (!data)
		वापस -1;

	/*
	 * Note order! (some AIX disks, e.g. unbootable kind,
	 * have no MSDOS 55aa)
	 */
	अगर (aix_magic_present(state, data)) अणु
		put_dev_sector(sect);
#अगर_घोषित CONFIG_AIX_PARTITION
		वापस aix_partition(state);
#अन्यथा
		strlcat(state->pp_buf, " [AIX]", PAGE_SIZE);
		वापस 0;
#पूर्ण_अगर
	पूर्ण

	अगर (!msकरोs_magic_present(data + 510)) अणु
		put_dev_sector(sect);
		वापस 0;
	पूर्ण

	/*
	 * Now that the 55aa signature is present, this is probably
	 * either the boot sector of a FAT fileप्रणाली or a DOS-type
	 * partition table. Reject this in हाल the boot indicator
	 * is not 0 or 0x80.
	 */
	p = (काष्ठा msकरोs_partition *) (data + 0x1be);
	क्रम (slot = 1; slot <= 4; slot++, p++) अणु
		अगर (p->boot_ind != 0 && p->boot_ind != 0x80) अणु
			/*
			 * Even without a valid boot inidicator value
			 * its still possible this is valid FAT fileप्रणाली
			 * without a partition table.
			 */
			fb = (काष्ठा fat_boot_sector *) data;
			अगर (slot == 1 && fb->reserved && fb->fats
				&& fat_valid_media(fb->media)) अणु
				strlcat(state->pp_buf, "\n", PAGE_SIZE);
				put_dev_sector(sect);
				वापस 1;
			पूर्ण अन्यथा अणु
				put_dev_sector(sect);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_EFI_PARTITION
	p = (काष्ठा msकरोs_partition *) (data + 0x1be);
	क्रम (slot = 1 ; slot <= 4 ; slot++, p++) अणु
		/* If this is an EFI GPT disk, msकरोs should ignore it. */
		अगर (SYS_IND(p) == EFI_PMBR_OSTYPE_EFI_GPT) अणु
			put_dev_sector(sect);
			वापस 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	p = (काष्ठा msकरोs_partition *) (data + 0x1be);

	disksig = le32_to_cpup((__le32 *)(data + 0x1b8));

	/*
	 * Look क्रम partitions in two passes:
	 * First find the primary and DOS-type extended partitions.
	 * On the second pass look inside *BSD, Unixware and Solaris partitions.
	 */

	state->next = 5;
	क्रम (slot = 1 ; slot <= 4 ; slot++, p++) अणु
		sector_t start = start_sect(p)*sector_size;
		sector_t size = nr_sects(p)*sector_size;

		अगर (!size)
			जारी;
		अगर (is_extended_partition(p)) अणु
			/*
			 * prevent someone करोing mkfs or mkswap on an
			 * extended partition, but leave room क्रम LILO
			 * FIXME: this uses one logical sector क्रम > 512b
			 * sector, although it may not be enough/proper.
			 */
			sector_t n = 2;

			n = min(size, max(sector_size, n));
			put_partition(state, slot, start, n);

			strlcat(state->pp_buf, " <", PAGE_SIZE);
			parse_extended(state, start, size, disksig);
			strlcat(state->pp_buf, " >", PAGE_SIZE);
			जारी;
		पूर्ण
		put_partition(state, slot, start, size);
		set_info(state, slot, disksig);
		अगर (SYS_IND(p) == LINUX_RAID_PARTITION)
			state->parts[slot].flags = ADDPART_FLAG_RAID;
		अगर (SYS_IND(p) == DM6_PARTITION)
			strlcat(state->pp_buf, "[DM]", PAGE_SIZE);
		अगर (SYS_IND(p) == EZD_PARTITION)
			strlcat(state->pp_buf, "[EZD]", PAGE_SIZE);
	पूर्ण

	strlcat(state->pp_buf, "\n", PAGE_SIZE);

	/* second pass - output क्रम each on a separate line */
	p = (काष्ठा msकरोs_partition *) (0x1be + data);
	क्रम (slot = 1 ; slot <= 4 ; slot++, p++) अणु
		अचिन्हित अक्षर id = SYS_IND(p);
		पूर्णांक n;

		अगर (!nr_sects(p))
			जारी;

		क्रम (n = 0; subtypes[n].parse && id != subtypes[n].id; n++)
			;

		अगर (!subtypes[n].parse)
			जारी;
		subtypes[n].parse(state, start_sect(p) * sector_size,
				  nr_sects(p) * sector_size, slot);
	पूर्ण
	put_dev_sector(sect);
	वापस 1;
पूर्ण
