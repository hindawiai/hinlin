<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* AFS fileserver XDR types
 *
 * Copyright (C) 2018 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित XDR_FS_H
#घोषणा XDR_FS_H

काष्ठा afs_xdr_AFSFetchStatus अणु
	__be32	अगर_version;
#घोषणा AFS_FSTATUS_VERSION	1
	__be32	type;
	__be32	nlink;
	__be32	size_lo;
	__be32	data_version_lo;
	__be32	author;
	__be32	owner;
	__be32	caller_access;
	__be32	anon_access;
	__be32	mode;
	__be32	parent_vnode;
	__be32	parent_unique;
	__be32	seg_size;
	__be32	mसमय_client;
	__be32	mसमय_server;
	__be32	group;
	__be32	sync_counter;
	__be32	data_version_hi;
	__be32	lock_count;
	__be32	size_hi;
	__be32	पात_code;
पूर्ण __packed;

#घोषणा AFS_सूची_HASHTBL_SIZE	128
#घोषणा AFS_सूची_सूचीENT_SIZE	32
#घोषणा AFS_सूची_SLOTS_PER_BLOCK	64
#घोषणा AFS_सूची_BLOCK_SIZE	2048
#घोषणा AFS_सूची_BLOCKS_PER_PAGE	(PAGE_SIZE / AFS_सूची_BLOCK_SIZE)
#घोषणा AFS_सूची_MAX_SLOTS	65536
#घोषणा AFS_सूची_BLOCKS_WITH_CTR	128
#घोषणा AFS_सूची_MAX_BLOCKS	1023
#घोषणा AFS_सूची_RESV_BLOCKS	1
#घोषणा AFS_सूची_RESV_BLOCKS0	13

/*
 * Directory entry काष्ठाure.
 */
जोड़ afs_xdr_dirent अणु
	काष्ठा अणु
		u8		valid;
		u8		unused[1];
		__be16		hash_next;
		__be32		vnode;
		__be32		unique;
		u8		name[];
		/* When determining the number of dirent slots needed to
		 * represent a directory entry, name should be assumed to be 16
		 * bytes, due to a now-standardised (mis)calculation, but it is
		 * in fact 20 bytes in size.  afs_dir_calc_slots() should be
		 * used क्रम this.
		 *
		 * For names दीर्घer than (16 or) 20 bytes, extra slots should
		 * be annexed to this one using the extended_name क्रमmat.
		 */
	पूर्ण u;
	u8			extended_name[32];
पूर्ण __packed;

/*
 * Directory block header (one at the beginning of every 2048-byte block).
 */
काष्ठा afs_xdr_dir_hdr अणु
	__be16		npages;
	__be16		magic;
#घोषणा AFS_सूची_MAGIC htons(1234)
	u8		reserved;
	u8		biपंचांगap[8];
	u8		pad[19];
पूर्ण __packed;

/*
 * Directory block layout
 */
जोड़ afs_xdr_dir_block अणु
	काष्ठा afs_xdr_dir_hdr		hdr;

	काष्ठा अणु
		काष्ठा afs_xdr_dir_hdr	hdr;
		u8			alloc_ctrs[AFS_सूची_MAX_BLOCKS];
		__be16			hashtable[AFS_सूची_HASHTBL_SIZE];
	पूर्ण meta;

	जोड़ afs_xdr_dirent	dirents[AFS_सूची_SLOTS_PER_BLOCK];
पूर्ण __packed;

/*
 * Directory layout on a linux VM page.
 */
काष्ठा afs_xdr_dir_page अणु
	जोड़ afs_xdr_dir_block	blocks[AFS_सूची_BLOCKS_PER_PAGE];
पूर्ण;

/*
 * Calculate the number of dirent slots required क्रम any given name length.
 * The calculation is made assuming the part of the name in the first slot is
 * 16 bytes, rather than 20, but this miscalculation is now standardised.
 */
अटल अंतरभूत अचिन्हित पूर्णांक afs_dir_calc_slots(माप_प्रकार name_len)
अणु
	name_len++; /* NUL-terminated */
	वापस 1 + ((name_len + 15) / AFS_सूची_सूचीENT_SIZE);
पूर्ण

#पूर्ण_अगर /* XDR_FS_H */
