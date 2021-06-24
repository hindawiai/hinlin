<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * FS_IOC_GETFSMAP ioctl infraकाष्ठाure.
 *
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 *
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#अगर_अघोषित _LINUX_FSMAP_H
#घोषणा _LINUX_FSMAP_H

#समावेश <linux/types.h>

/*
 *	Structure क्रम FS_IOC_GETFSMAP.
 *
 *	The memory layout क्रम this call are the scalar values defined in
 *	काष्ठा fsmap_head, followed by two काष्ठा fsmap that describe
 *	the lower and upper bound of mappings to वापस, followed by an
 *	array of काष्ठा fsmap mappings.
 *
 *	fmh_अगरlags control the output of the call, whereas fmh_oflags report
 *	on the overall record output.  fmh_count should be set to the
 *	length of the fmh_recs array, and fmh_entries will be set to the
 *	number of entries filled out during each call.  If fmh_count is
 *	zero, the number of reverse mappings will be वापसed in
 *	fmh_entries, though no mappings will be वापसed.  fmh_reserved
 *	must be set to zero.
 *
 *	The two elements in the fmh_keys array are used to स्थिरrain the
 *	output.  The first element in the array should represent the
 *	lowest disk mapping ("low key") that the user wants to learn
 *	about.  If this value is all zeroes, the fileप्रणाली will वापस
 *	the first entry it knows about.  For a subsequent call, the
 *	contents of fsmap_head.fmh_recs[fsmap_head.fmh_count - 1] should be
 *	copied पूर्णांकo fmh_keys[0] to have the kernel start where it left off.
 *
 *	The second element in the fmh_keys array should represent the
 *	highest disk mapping ("high key") that the user wants to learn
 *	about.  If this value is all ones, the fileप्रणाली will not stop
 *	until it runs out of mapping to वापस or runs out of space in
 *	fmh_recs.
 *
 *	fmr_device can be either a 32-bit cookie representing a device, or
 *	a 32-bit dev_t अगर the FMH_OF_DEV_T flag is set.  fmr_physical,
 *	fmr_offset, and fmr_length are expressed in units of bytes.
 *	fmr_owner is either an inode number, or a special value अगर
 *	FMR_OF_SPECIAL_OWNER is set in fmr_flags.
 */
काष्ठा fsmap अणु
	__u32		fmr_device;	/* device id */
	__u32		fmr_flags;	/* mapping flags */
	__u64		fmr_physical;	/* device offset of segment */
	__u64		fmr_owner;	/* owner id */
	__u64		fmr_offset;	/* file offset of segment */
	__u64		fmr_length;	/* length of segment */
	__u64		fmr_reserved[3];	/* must be zero */
पूर्ण;

काष्ठा fsmap_head अणु
	__u32		fmh_अगरlags;	/* control flags */
	__u32		fmh_oflags;	/* output flags */
	__u32		fmh_count;	/* # of entries in array incl. input */
	__u32		fmh_entries;	/* # of entries filled in (output). */
	__u64		fmh_reserved[6];	/* must be zero */

	काष्ठा fsmap	fmh_keys[2];	/* low and high keys क्रम the mapping search */
	काष्ठा fsmap	fmh_recs[];	/* वापसed records */
पूर्ण;

/* Size of an fsmap_head with room क्रम nr records. */
अटल अंतरभूत माप_प्रकार
fsmap_माप(
	अचिन्हित पूर्णांक	nr)
अणु
	वापस माप(काष्ठा fsmap_head) + nr * माप(काष्ठा fsmap);
पूर्ण

/* Start the next fsmap query at the end of the current query results. */
अटल अंतरभूत व्योम
fsmap_advance(
	काष्ठा fsmap_head	*head)
अणु
	head->fmh_keys[0] = head->fmh_recs[head->fmh_entries - 1];
पूर्ण

/*	fmh_अगरlags values - set by FS_IOC_GETFSMAP caller in the header. */
/* no flags defined yet */
#घोषणा FMH_IF_VALID		0

/*	fmh_oflags values - वापसed in the header segment only. */
#घोषणा FMH_OF_DEV_T		0x1	/* fmr_device values will be dev_t */

/*	fmr_flags values - वापसed क्रम each non-header segment */
#घोषणा FMR_OF_PREALLOC		0x1	/* segment = unwritten pre-allocation */
#घोषणा FMR_OF_ATTR_FORK	0x2	/* segment = attribute विभाजन */
#घोषणा FMR_OF_EXTENT_MAP	0x4	/* segment = extent map */
#घोषणा FMR_OF_SHARED		0x8	/* segment = shared with another file */
#घोषणा FMR_OF_SPECIAL_OWNER	0x10	/* owner is a special value */
#घोषणा FMR_OF_LAST		0x20	/* segment is the last in the dataset */

/* Each FS माला_लो to define its own special owner codes. */
#घोषणा FMR_OWNER(type, code)	(((__u64)type << 32) | \
				 ((__u64)code & 0xFFFFFFFFULL))
#घोषणा FMR_OWNER_TYPE(owner)	((__u32)((__u64)owner >> 32))
#घोषणा FMR_OWNER_CODE(owner)	((__u32)(((__u64)owner & 0xFFFFFFFFULL)))
#घोषणा FMR_OWN_FREE		FMR_OWNER(0, 1) /* मुक्त space */
#घोषणा FMR_OWN_UNKNOWN		FMR_OWNER(0, 2) /* unknown owner */
#घोषणा FMR_OWN_METADATA	FMR_OWNER(0, 3) /* metadata */

#घोषणा FS_IOC_GETFSMAP		_IOWR('X', 59, काष्ठा fsmap_head)

#पूर्ण_अगर /* _LINUX_FSMAP_H */
