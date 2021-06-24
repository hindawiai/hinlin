<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * सूची.स - Defines क्रम directory handling in NTFS Linux kernel driver. Part of
 *	   the Linux-NTFS project.
 *
 * Copyright (c) 2002-2004 Anton Altaparmakov
 */

#अगर_अघोषित _LINUX_NTFS_सूची_H
#घोषणा _LINUX_NTFS_सूची_H

#समावेश "layout.h"
#समावेश "inode.h"
#समावेश "types.h"

/*
 * ntfs_name is used to वापस the file name to the caller of
 * ntfs_lookup_inode_by_name() in order क्रम the caller (namei.c::ntfs_lookup())
 * to be able to deal with dcache aliasing issues.
 */
प्रकार काष्ठा अणु
	MFT_REF mref;
	खाता_NAME_TYPE_FLAGS type;
	u8 len;
	ntfsअक्षर name[0];
पूर्ण __attribute__ ((__packed__)) ntfs_name;

/* The little endian Unicode string $I30 as a global स्थिरant. */
बाह्य ntfsअक्षर I30[5];

बाह्य MFT_REF ntfs_lookup_inode_by_name(ntfs_inode *dir_ni,
		स्थिर ntfsअक्षर *uname, स्थिर पूर्णांक uname_len, ntfs_name **res);

#पूर्ण_अगर /* _LINUX_NTFS_FS_सूची_H */
