<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * efs_vh.h
 *
 * Copyright (c) 1999 Al Smith
 *
 * Portions derived from IRIX header files (c) 1985 MIPS Computer Systems, Inc.
 */

#अगर_अघोषित __EFS_VH_H__
#घोषणा __EFS_VH_H__

#घोषणा VHMAGIC		0xbe5a941	/* volume header magic number */
#घोषणा NPARTAB		16		/* 16 unix partitions */
#घोषणा NVसूची		15		/* max of 15 directory entries */
#घोषणा BFNAMESIZE	16		/* max 16 अक्षरs in boot file name */
#घोषणा VDNAMESIZE	8

काष्ठा volume_directory अणु
	अक्षर	vd_name[VDNAMESIZE];	/* name */
	__be32	vd_lbn;			/* logical block number */
	__be32	vd_nbytes;		/* file length in bytes */
पूर्ण;

काष्ठा partition_table अणु	/* one per logical partition */
	__be32	pt_nblks;	/* # of logical blks in partition */
	__be32	pt_firstlbn;	/* first lbn of partition */
	__be32	pt_type;	/* use of partition */
पूर्ण;

काष्ठा volume_header अणु
	__be32	vh_magic;			/* identअगरies volume header */
	__be16	vh_rootpt;			/* root partition number */
	__be16	vh_swappt;			/* swap partition number */
	अक्षर	vh_bootfile[BFNAMESIZE];	/* name of file to boot */
	अक्षर	pad[48];			/* device param space */
	काष्ठा volume_directory vh_vd[NVसूची];	/* other vol hdr contents */
	काष्ठा partition_table  vh_pt[NPARTAB];	/* device partition layout */
	__be32	vh_csum;			/* volume header checksum */
	__be32	vh_fill;			/* fill out to 512 bytes */
पूर्ण;

/* partition type sysv is used क्रम EFS क्रमmat CD-ROM partitions */
#घोषणा SGI_SYSV	0x05
#घोषणा SGI_EFS		0x07
#घोषणा IS_EFS(x)	(((x) == SGI_EFS) || ((x) == SGI_SYSV))

काष्ठा pt_types अणु
	पूर्णांक	pt_type;
	अक्षर	*pt_name;
पूर्ण;

#पूर्ण_अगर /* __EFS_VH_H__ */

