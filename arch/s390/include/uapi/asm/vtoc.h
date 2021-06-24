<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file contains volume label definitions क्रम DASD devices.
 *
 * Copyright IBM Corp. 2005
 *
 * Author(s): Volker Sameske <sameske@de.ibm.com>
 *
 */

#अगर_अघोषित _ASM_S390_VTOC_H
#घोषणा _ASM_S390_VTOC_H

#समावेश <linux/types.h>

काष्ठा vtoc_ttr
अणु
	__u16 tt;
	__u8 r;
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_cchhb
अणु
	__u16 cc;
	__u16 hh;
	__u8 b;
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_cchh
अणु
	__u16 cc;
	__u16 hh;
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_labeldate
अणु
	__u8 year;
	__u16 day;
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_volume_label_cdl
अणु
	अक्षर volkey[4];		/* volume key = volume label */
	अक्षर vollbl[4];		/* volume label */
	अक्षर volid[6];		/* volume identअगरier */
	__u8 security;		/* security byte */
	काष्ठा vtoc_cchhb vtoc;	/* VTOC address */
	अक्षर res1[5];		/* reserved */
	अक्षर cisize[4];		/* CI-size क्रम FBA,... */
				/* ...blanks क्रम CKD */
	अक्षर blkperci[4];	/* no of blocks per CI (FBA), blanks क्रम CKD */
	अक्षर labperci[4];	/* no of labels per CI (FBA), blanks क्रम CKD */
	अक्षर res2[4];		/* reserved */
	अक्षर lvtoc[14];		/* owner code क्रम LVTOC */
	अक्षर res3[29];		/* reserved */
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_volume_label_ldl अणु
	अक्षर vollbl[4];		/* volume label */
	अक्षर volid[6];		/* volume identअगरier */
	अक्षर res3[69];		/* reserved */
	अक्षर ldl_version;	/* version number, valid क्रम ldl क्रमmat */
	__u64 क्रमmatted_blocks; /* valid when ldl_version >= f2  */
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_extent
अणु
	__u8 typeind;			/* extent type indicator */
	__u8 seqno;			/* extent sequence number */
	काष्ठा vtoc_cchh llimit;	/* starting poपूर्णांक of this extent */
	काष्ठा vtoc_cchh ulimit;	/* ending poपूर्णांक of this extent */
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_dev_स्थिर
अणु
	__u16 DS4DSCYL;	/* number of logical cyls */
	__u16 DS4DSTRK;	/* number of tracks in a logical cylinder */
	__u16 DS4DEVTK;	/* device track length */
	__u8 DS4DEVI;	/* non-last keyed record overhead */
	__u8 DS4DEVL;	/* last keyed record overhead */
	__u8 DS4DEVK;	/* non-keyed record overhead dअगरferential */
	__u8 DS4DEVFG;	/* flag byte */
	__u16 DS4DEVTL;	/* device tolerance */
	__u8 DS4DEVDT;	/* number of DSCB's per track */
	__u8 DS4DEVDB;	/* number of directory blocks per track */
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_क्रमmat1_label
अणु
	अक्षर DS1DSNAM[44];	/* data set name */
	__u8 DS1FMTID;		/* क्रमmat identअगरier */
	अक्षर DS1DSSN[6];	/* data set serial number */
	__u16 DS1VOLSQ;		/* volume sequence number */
	काष्ठा vtoc_labeldate DS1CREDT; /* creation date: ydd */
	काष्ठा vtoc_labeldate DS1EXPDT; /* expiration date */
	__u8 DS1NOEPV;		/* number of extents on volume */
	__u8 DS1NOBDB;		/* no. of bytes used in last direction blk */
	__u8 DS1FLAG1;		/* flag 1 */
	अक्षर DS1SYSCD[13];	/* प्रणाली code */
	काष्ठा vtoc_labeldate DS1REFD; /* date last referenced	*/
	__u8 DS1SMSFG;		/* प्रणाली managed storage indicators */
	__u8 DS1SCXTF;		/* sec. space extension flag byte */
	__u16 DS1SCXTV;		/* secondary space extension value */
	__u8 DS1DSRG1;		/* data set organisation byte 1 */
	__u8 DS1DSRG2;		/* data set organisation byte 2 */
	__u8 DS1RECFM;		/* record क्रमmat */
	__u8 DS1OPTCD;		/* option code */
	__u16 DS1BLKL;		/* block length */
	__u16 DS1LRECL;		/* record length */
	__u8 DS1KEYL;		/* key length */
	__u16 DS1RKP;		/* relative key position */
	__u8 DS1DSIND;		/* data set indicators */
	__u8 DS1SCAL1;		/* secondary allocation flag byte */
	अक्षर DS1SCAL3[3];	/* secondary allocation quantity */
	काष्ठा vtoc_ttr DS1LSTAR; /* last used track and block on track */
	__u16 DS1TRBAL;		/* space reमुख्यing on last used track */
	__u16 res1;		/* reserved */
	काष्ठा vtoc_extent DS1EXT1; /* first extent description */
	काष्ठा vtoc_extent DS1EXT2; /* second extent description */
	काष्ठा vtoc_extent DS1EXT3; /* third extent description */
	काष्ठा vtoc_cchhb DS1PTRDS; /* possible poपूर्णांकer to f2 or f3 DSCB */
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_क्रमmat4_label
अणु
	अक्षर DS4KEYCD[44];	/* key code क्रम VTOC labels: 44 बार 0x04 */
	__u8 DS4IDFMT;		/* क्रमmat identअगरier */
	काष्ठा vtoc_cchhb DS4HPCHR; /* highest address of a क्रमmat 1 DSCB */
	__u16 DS4DSREC;		/* number of available DSCB's */
	काष्ठा vtoc_cchh DS4HCCHH; /* CCHH of next available alternate track */
	__u16 DS4NOATK;		/* number of reमुख्यing alternate tracks */
	__u8 DS4VTOCI;		/* VTOC indicators */
	__u8 DS4NOEXT;		/* number of extents in VTOC */
	__u8 DS4SMSFG;		/* प्रणाली managed storage indicators */
	__u8 DS4DEVAC;		/* number of alternate cylinders.
				 * Subtract from first two bytes of
				 * DS4DEVSZ to get number of usable
				 * cylinders. can be zero. valid
				 * only अगर DS4DEVAV on. */
	काष्ठा vtoc_dev_स्थिर DS4DEVCT;	/* device स्थिरants */
	अक्षर DS4AMTIM[8];	/* VSAM समय stamp */
	अक्षर DS4AMCAT[3];	/* VSAM catalog indicator */
	अक्षर DS4R2TIM[8];	/* VSAM volume/catalog match समय stamp */
	अक्षर res1[5];		/* reserved */
	अक्षर DS4F6PTR[5];	/* poपूर्णांकer to first क्रमmat 6 DSCB */
	काष्ठा vtoc_extent DS4VTOCE; /* VTOC extent description */
	अक्षर res2[10];		/* reserved */
	__u8 DS4EFLVL;		/* extended मुक्त-space management level */
	काष्ठा vtoc_cchhb DS4EFPTR; /* poपूर्णांकer to extended मुक्त-space info */
	अक्षर res3;		/* reserved */
	__u32 DS4DCYL;		/* number of logical cyls */
	अक्षर res4[2];		/* reserved */
	__u8 DS4DEVF2;		/* device flags */
	अक्षर res5;		/* reserved */
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_ds5ext
अणु
	__u16 t;	/* RTA of the first track of मुक्त extent */
	__u16 fc;	/* number of whole cylinders in मुक्त ext. */
	__u8 ft;	/* number of reमुख्यing मुक्त tracks */
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_क्रमmat5_label
अणु
	अक्षर DS5KEYID[4];	/* key identअगरier */
	काष्ठा vtoc_ds5ext DS5AVEXT; /* first available (मुक्त-space) extent. */
	काष्ठा vtoc_ds5ext DS5EXTAV[7]; /* seven available extents */
	__u8 DS5FMTID;		/* क्रमmat identअगरier */
	काष्ठा vtoc_ds5ext DS5MAVET[18]; /* eighteen available extents */
	काष्ठा vtoc_cchhb DS5PTRDS; /* poपूर्णांकer to next क्रमmat5 DSCB */
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_ds7ext
अणु
	__u32 a; /* starting RTA value */
	__u32 b; /* ending RTA value + 1 */
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_क्रमmat7_label
अणु
	अक्षर DS7KEYID[4];	/* key identअगरier */
	काष्ठा vtoc_ds7ext DS7EXTNT[5]; /* space क्रम 5 extent descriptions */
	__u8 DS7FMTID;		/* क्रमmat identअगरier */
	काष्ठा vtoc_ds7ext DS7ADEXT[11]; /* space क्रम 11 extent descriptions */
	अक्षर res1[2];		/* reserved */
	काष्ठा vtoc_cchhb DS7PTRDS; /* poपूर्णांकer to next FMT7 DSCB */
पूर्ण __attribute__ ((packed));

काष्ठा vtoc_cms_label अणु
	__u8 label_id[4];		/* Label identअगरier */
	__u8 vol_id[6];		/* Volid */
	__u16 version_id;		/* Version identअगरier */
	__u32 block_size;		/* Disk block size */
	__u32 origin_ptr;		/* Disk origin poपूर्णांकer */
	__u32 usable_count;	/* Number of usable cylinders/blocks */
	__u32 क्रमmatted_count;	/* Maximum number of क्रमmatted cylinders/
				 * blocks */
	__u32 block_count;	/* Disk size in CMS blocks */
	__u32 used_count;		/* Number of CMS blocks in use */
	__u32 fst_size;		/* File Status Table (FST) size */
	__u32 fst_count;		/* Number of FSTs per CMS block */
	__u8 क्रमmat_date[6];	/* Disk FORMAT date */
	__u8 reserved1[2];
	__u32 disk_offset;	/* Disk offset when reserved*/
	__u32 map_block;		/* Allocation Map Block with next hole */
	__u32 hblk_disp;		/* Displacement पूर्णांकo HBLK data of next hole */
	__u32 user_disp;		/* Displacement पूर्णांकo user part of Allocation
				 * map */
	__u8 reserved2[4];
	__u8 segment_name[8];	/* Name of shared segment */
पूर्ण __attribute__ ((packed));

#पूर्ण_अगर /* _ASM_S390_VTOC_H */
