<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 *
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित __EXT4_FSMAP_H__
#घोषणा	__EXT4_FSMAP_H__

काष्ठा fsmap;

/* पूर्णांकernal fsmap representation */
काष्ठा ext4_fsmap अणु
	काष्ठा list_head	fmr_list;
	dev_t		fmr_device;	/* device id */
	uपूर्णांक32_t	fmr_flags;	/* mapping flags */
	uपूर्णांक64_t	fmr_physical;	/* device offset of segment */
	uपूर्णांक64_t	fmr_owner;	/* owner id */
	uपूर्णांक64_t	fmr_length;	/* length of segment, blocks */
पूर्ण;

काष्ठा ext4_fsmap_head अणु
	uपूर्णांक32_t	fmh_अगरlags;	/* control flags */
	uपूर्णांक32_t	fmh_oflags;	/* output flags */
	अचिन्हित पूर्णांक	fmh_count;	/* # of entries in array incl. input */
	अचिन्हित पूर्णांक	fmh_entries;	/* # of entries filled in (output). */

	काष्ठा ext4_fsmap fmh_keys[2];	/* low and high keys */
पूर्ण;

व्योम ext4_fsmap_from_पूर्णांकernal(काष्ठा super_block *sb, काष्ठा fsmap *dest,
		काष्ठा ext4_fsmap *src);
व्योम ext4_fsmap_to_पूर्णांकernal(काष्ठा super_block *sb, काष्ठा ext4_fsmap *dest,
		काष्ठा fsmap *src);

/* fsmap to userspace क्रमmatter - copy to user & advance poपूर्णांकer */
प्रकार पूर्णांक (*ext4_fsmap_क्रमmat_t)(काष्ठा ext4_fsmap *, व्योम *);

पूर्णांक ext4_getfsmap(काष्ठा super_block *sb, काष्ठा ext4_fsmap_head *head,
		ext4_fsmap_क्रमmat_t क्रमmatter, व्योम *arg);

#घोषणा EXT4_QUERY_RANGE_ABORT		1
#घोषणा EXT4_QUERY_RANGE_CONTINUE	0

/*	fmr_owner special values क्रम FS_IOC_GETFSMAP; some share w/ XFS */
#घोषणा EXT4_FMR_OWN_FREE	FMR_OWN_FREE      /* मुक्त space */
#घोषणा EXT4_FMR_OWN_UNKNOWN	FMR_OWN_UNKNOWN   /* unknown owner */
#घोषणा EXT4_FMR_OWN_FS		FMR_OWNER('X', 1) /* अटल fs metadata */
#घोषणा EXT4_FMR_OWN_LOG	FMR_OWNER('X', 2) /* journalling log */
#घोषणा EXT4_FMR_OWN_INODES	FMR_OWNER('X', 5) /* inodes */
#घोषणा EXT4_FMR_OWN_GDT	FMR_OWNER('f', 1) /* group descriptors */
#घोषणा EXT4_FMR_OWN_RESV_GDT	FMR_OWNER('f', 2) /* reserved gdt blocks */
#घोषणा EXT4_FMR_OWN_BLKBM	FMR_OWNER('f', 3) /* inode biपंचांगap */
#घोषणा EXT4_FMR_OWN_INOBM	FMR_OWNER('f', 4) /* block biपंचांगap */

#पूर्ण_अगर /* __EXT4_FSMAP_H__ */
