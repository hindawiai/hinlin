<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * FS_IOC_FIEMAP ioctl infraकाष्ठाure.
 *
 * Some portions copyright (C) 2007 Cluster File Systems, Inc
 *
 * Authors: Mark Fasheh <mfasheh@suse.com>
 *          Kalpak Shah <kalpak.shah@sun.com>
 *          Andreas Dilger <adilger@sun.com>
 */

#अगर_अघोषित _UAPI_LINUX_FIEMAP_H
#घोषणा _UAPI_LINUX_FIEMAP_H

#समावेश <linux/types.h>

काष्ठा fiemap_extent अणु
	__u64 fe_logical;  /* logical offset in bytes क्रम the start of
			    * the extent from the beginning of the file */
	__u64 fe_physical; /* physical offset in bytes क्रम the start
			    * of the extent from the beginning of the disk */
	__u64 fe_length;   /* length in bytes क्रम this extent */
	__u64 fe_reserved64[2];
	__u32 fe_flags;    /* FIEMAP_EXTENT_* flags क्रम this extent */
	__u32 fe_reserved[3];
पूर्ण;

काष्ठा fiemap अणु
	__u64 fm_start;		/* logical offset (inclusive) at
				 * which to start mapping (in) */
	__u64 fm_length;	/* logical length of mapping which
				 * userspace wants (in) */
	__u32 fm_flags;		/* FIEMAP_FLAG_* flags क्रम request (in/out) */
	__u32 fm_mapped_extents;/* number of extents that were mapped (out) */
	__u32 fm_extent_count;  /* size of fm_extents array (in) */
	__u32 fm_reserved;
	काष्ठा fiemap_extent fm_extents[0]; /* array of mapped extents (out) */
पूर्ण;

#घोषणा FIEMAP_MAX_OFFSET	(~0ULL)

#घोषणा FIEMAP_FLAG_SYNC	0x00000001 /* sync file data beक्रमe map */
#घोषणा FIEMAP_FLAG_XATTR	0x00000002 /* map extended attribute tree */
#घोषणा FIEMAP_FLAG_CACHE	0x00000004 /* request caching of the extents */

#घोषणा FIEMAP_FLAGS_COMPAT	(FIEMAP_FLAG_SYNC | FIEMAP_FLAG_XATTR)

#घोषणा FIEMAP_EXTENT_LAST		0x00000001 /* Last extent in file. */
#घोषणा FIEMAP_EXTENT_UNKNOWN		0x00000002 /* Data location unknown. */
#घोषणा FIEMAP_EXTENT_DELALLOC		0x00000004 /* Location still pending.
						    * Sets EXTENT_UNKNOWN. */
#घोषणा FIEMAP_EXTENT_ENCODED		0x00000008 /* Data can not be पढ़ो
						    * जबतक fs is unmounted */
#घोषणा FIEMAP_EXTENT_DATA_ENCRYPTED	0x00000080 /* Data is encrypted by fs.
						    * Sets EXTENT_NO_BYPASS. */
#घोषणा FIEMAP_EXTENT_NOT_ALIGNED	0x00000100 /* Extent offsets may not be
						    * block aligned. */
#घोषणा FIEMAP_EXTENT_DATA_INLINE	0x00000200 /* Data mixed with metadata.
						    * Sets EXTENT_NOT_ALIGNED.*/
#घोषणा FIEMAP_EXTENT_DATA_TAIL		0x00000400 /* Multiple files in block.
						    * Sets EXTENT_NOT_ALIGNED.*/
#घोषणा FIEMAP_EXTENT_UNWRITTEN		0x00000800 /* Space allocated, but
						    * no data (i.e. zero). */
#घोषणा FIEMAP_EXTENT_MERGED		0x00001000 /* File करोes not natively
						    * support extents. Result
						    * merged क्रम efficiency. */
#घोषणा FIEMAP_EXTENT_SHARED		0x00002000 /* Space shared with other
						    * files. */

#पूर्ण_अगर /* _UAPI_LINUX_FIEMAP_H */
