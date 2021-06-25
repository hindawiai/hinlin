<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/**
 * ldm - Part of the Linux-NTFS project.
 *
 * Copyright (C) 2001,2002 Riअक्षरd Russon <ldm@flatcap.org>
 * Copyright (c) 2001-2007 Anton Altaparmakov
 * Copyright (C) 2001,2002 Jakob Kemi <jakob.kemi@telia.com>
 *
 * Documentation is available at http://www.linux-ntfs.org/करोku.php?id=करोwnloads 
 */

#अगर_अघोषित _FS_PT_LDM_H_
#घोषणा _FS_PT_LDM_H_

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/genhd.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/byteorder.h>

काष्ठा parsed_partitions;

/* Magic numbers in CPU क्रमmat. */
#घोषणा MAGIC_VMDB	0x564D4442		/* VMDB */
#घोषणा MAGIC_VBLK	0x56424C4B		/* VBLK */
#घोषणा MAGIC_PRIVHEAD	0x5052495648454144ULL	/* PRIVHEAD */
#घोषणा MAGIC_TOCBLOCK	0x544F43424C4F434BULL	/* TOCBLOCK */

/* The defined vblk types. */
#घोषणा VBLK_VOL5		0x51		/* Volume,     version 5 */
#घोषणा VBLK_CMP3		0x32		/* Component,  version 3 */
#घोषणा VBLK_PRT3		0x33		/* Partition,  version 3 */
#घोषणा VBLK_DSK3		0x34		/* Disk,       version 3 */
#घोषणा VBLK_DSK4		0x44		/* Disk,       version 4 */
#घोषणा VBLK_DGR3		0x35		/* Disk Group, version 3 */
#घोषणा VBLK_DGR4		0x45		/* Disk Group, version 4 */

/* vblk flags indicating extra inक्रमmation will be present */
#घोषणा	VBLK_FLAG_COMP_STRIPE	0x10
#घोषणा	VBLK_FLAG_PART_INDEX	0x08
#घोषणा	VBLK_FLAG_DGR3_IDS	0x08
#घोषणा	VBLK_FLAG_DGR4_IDS	0x08
#घोषणा	VBLK_FLAG_VOLU_ID1	0x08
#घोषणा	VBLK_FLAG_VOLU_ID2	0x20
#घोषणा	VBLK_FLAG_VOLU_SIZE	0x80
#घोषणा	VBLK_FLAG_VOLU_DRIVE	0x02

/* size of a vblk's अटल parts */
#घोषणा VBLK_SIZE_HEAD		16
#घोषणा VBLK_SIZE_CMP3		22		/* Name and version */
#घोषणा VBLK_SIZE_DGR3		12
#घोषणा VBLK_SIZE_DGR4		44
#घोषणा VBLK_SIZE_DSK3		12
#घोषणा VBLK_SIZE_DSK4		45
#घोषणा VBLK_SIZE_PRT3		28
#घोषणा VBLK_SIZE_VOL5		58

/* component types */
#घोषणा COMP_STRIPE		0x01		/* Stripe-set */
#घोषणा COMP_BASIC		0x02		/* Basic disk */
#घोषणा COMP_RAID		0x03		/* Raid-set */

/* Other स्थिरants. */
#घोषणा LDM_DB_SIZE		2048		/* Size in sectors (= 1MiB). */

#घोषणा OFF_PRIV1		6		/* Offset of the first privhead
						   relative to the start of the
						   device in sectors */

/* Offsets to काष्ठाures within the LDM Database in sectors. */
#घोषणा OFF_PRIV2		1856		/* Backup निजी headers. */
#घोषणा OFF_PRIV3		2047

#घोषणा OFF_TOCB1		1		/* Tables of contents. */
#घोषणा OFF_TOCB2		2
#घोषणा OFF_TOCB3		2045
#घोषणा OFF_TOCB4		2046

#घोषणा OFF_VMDB		17		/* List of partitions. */

#घोषणा LDM_PARTITION		0x42		/* Formerly SFS (Landis). */

#घोषणा TOC_BITMAP1		"config"	/* Names of the two defined */
#घोषणा TOC_BITMAP2		"log"		/* biपंचांगaps in the TOCBLOCK. */

/* Borrowed from msकरोs.c */
#घोषणा SYS_IND(p)		(get_unaligned(&(p)->sys_ind))

काष्ठा frag अणु				/* VBLK Fragment handling */
	काष्ठा list_head list;
	u32		group;
	u8		num;		/* Total number of records */
	u8		rec;		/* This is record number n */
	u8		map;		/* Which portions are in use */
	u8		data[];
पूर्ण;

/* In memory LDM database काष्ठाures. */

काष्ठा privhead अणु			/* Offsets and sizes are in sectors. */
	u16	ver_major;
	u16	ver_minor;
	u64	logical_disk_start;
	u64	logical_disk_size;
	u64	config_start;
	u64	config_size;
	uuid_t	disk_id;
पूर्ण;

काष्ठा tocblock अणु			/* We have exactly two biपंचांगaps. */
	u8	biपंचांगap1_name[16];
	u64	biपंचांगap1_start;
	u64	biपंचांगap1_size;
	u8	biपंचांगap2_name[16];
	u64	biपंचांगap2_start;
	u64	biपंचांगap2_size;
पूर्ण;

काष्ठा vmdb अणु				/* VMDB: The database header */
	u16	ver_major;
	u16	ver_minor;
	u32	vblk_size;
	u32	vblk_offset;
	u32	last_vblk_seq;
पूर्ण;

काष्ठा vblk_comp अणु			/* VBLK Component */
	u8	state[16];
	u64	parent_id;
	u8	type;
	u8	children;
	u16	chunksize;
पूर्ण;

काष्ठा vblk_dgrp अणु			/* VBLK Disk Group */
	u8	disk_id[64];
पूर्ण;

काष्ठा vblk_disk अणु			/* VBLK Disk */
	uuid_t	disk_id;
	u8	alt_name[128];
पूर्ण;

काष्ठा vblk_part अणु			/* VBLK Partition */
	u64	start;
	u64	size;			/* start, size and vol_off in sectors */
	u64	volume_offset;
	u64	parent_id;
	u64	disk_id;
	u8	partnum;
पूर्ण;

काष्ठा vblk_volu अणु			/* VBLK Volume */
	u8	volume_type[16];
	u8	volume_state[16];
	u8	guid[16];
	u8	drive_hपूर्णांक[4];
	u64	size;
	u8	partition_type;
पूर्ण;

काष्ठा vblk_head अणु			/* VBLK standard header */
	u32 group;
	u16 rec;
	u16 nrec;
पूर्ण;

काष्ठा vblk अणु				/* Generalised VBLK */
	u8	name[64];
	u64	obj_id;
	u32	sequence;
	u8	flags;
	u8	type;
	जोड़ अणु
		काष्ठा vblk_comp comp;
		काष्ठा vblk_dgrp dgrp;
		काष्ठा vblk_disk disk;
		काष्ठा vblk_part part;
		काष्ठा vblk_volu volu;
	पूर्ण vblk;
	काष्ठा list_head list;
पूर्ण;

काष्ठा ldmdb अणु				/* Cache of the database */
	काष्ठा privhead ph;
	काष्ठा tocblock toc;
	काष्ठा vmdb     vm;
	काष्ठा list_head v_dgrp;
	काष्ठा list_head v_disk;
	काष्ठा list_head v_volu;
	काष्ठा list_head v_comp;
	काष्ठा list_head v_part;
पूर्ण;

#पूर्ण_अगर /* _FS_PT_LDM_H_ */

