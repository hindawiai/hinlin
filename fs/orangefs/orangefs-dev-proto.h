<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) 2001 Clemson University and The University of Chicago
 *
 * See COPYING in top-level directory.
 */

#अगर_अघोषित _ORANGEFS_DEV_PROTO_H
#घोषणा _ORANGEFS_DEV_PROTO_H

/*
 * types and स्थिरants shared between user space and kernel space क्रम
 * device पूर्णांकeraction using a common protocol
 */

/*
 * valid orangefs kernel operation types
 */
#घोषणा ORANGEFS_VFS_OP_INVALID           0xFF000000
#घोषणा ORANGEFS_VFS_OP_खाता_IO        0xFF000001
#घोषणा ORANGEFS_VFS_OP_LOOKUP         0xFF000002
#घोषणा ORANGEFS_VFS_OP_CREATE         0xFF000003
#घोषणा ORANGEFS_VFS_OP_GETATTR        0xFF000004
#घोषणा ORANGEFS_VFS_OP_REMOVE         0xFF000005
#घोषणा ORANGEFS_VFS_OP_MKसूची          0xFF000006
#घोषणा ORANGEFS_VFS_OP_READसूची        0xFF000007
#घोषणा ORANGEFS_VFS_OP_SETATTR        0xFF000008
#घोषणा ORANGEFS_VFS_OP_SYMLINK        0xFF000009
#घोषणा ORANGEFS_VFS_OP_RENAME         0xFF00000A
#घोषणा ORANGEFS_VFS_OP_STATFS         0xFF00000B
#घोषणा ORANGEFS_VFS_OP_TRUNCATE       0xFF00000C
#घोषणा ORANGEFS_VFS_OP_RA_FLUSH       0xFF00000D
#घोषणा ORANGEFS_VFS_OP_FS_MOUNT       0xFF00000E
#घोषणा ORANGEFS_VFS_OP_FS_UMOUNT      0xFF00000F
#घोषणा ORANGEFS_VFS_OP_GETXATTR       0xFF000010
#घोषणा ORANGEFS_VFS_OP_SETXATTR          0xFF000011
#घोषणा ORANGEFS_VFS_OP_LISTXATTR         0xFF000012
#घोषणा ORANGEFS_VFS_OP_REMOVEXATTR       0xFF000013
#घोषणा ORANGEFS_VFS_OP_PARAM          0xFF000014
#घोषणा ORANGEFS_VFS_OP_PERF_COUNT     0xFF000015
#घोषणा ORANGEFS_VFS_OP_CANCEL            0xFF00EE00
#घोषणा ORANGEFS_VFS_OP_FSYNC          0xFF00EE01
#घोषणा ORANGEFS_VFS_OP_FSKEY             0xFF00EE02
#घोषणा ORANGEFS_VFS_OP_READसूचीPLUS       0xFF00EE03
#घोषणा ORANGEFS_VFS_OP_FEATURES	0xFF00EE05 /* 2.9.6 */

/* features is a 64-bit अचिन्हित biपंचांगask */
#घोषणा ORANGEFS_FEATURE_READAHEAD 1

/*
 * Misc स्थिरants. Please retain them as multiples of 8!
 * Otherwise 32-64 bit पूर्णांकeractions will be messed up :)
 */
#घोषणा ORANGEFS_MAX_DEBUG_STRING_LEN	0x00000800

#घोषणा ORANGEFS_MAX_सूचीENT_COUNT_READसूची 512

#समावेश "upcall.h"
#समावेश "downcall.h"

#पूर्ण_अगर
