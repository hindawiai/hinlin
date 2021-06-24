<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * types.h - Defines क्रम NTFS Linux kernel driver specअगरic types.
 *	     Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2005 Anton Altaparmakov
 */

#अगर_अघोषित _LINUX_NTFS_TYPES_H
#घोषणा _LINUX_NTFS_TYPES_H

#समावेश <linux/types.h>

प्रकार __le16 le16;
प्रकार __le32 le32;
प्रकार __le64 le64;
प्रकार __u16 __bitwise sle16;
प्रकार __u32 __bitwise sle32;
प्रकार __u64 __bitwise sle64;

/* 2-byte Unicode अक्षरacter type. */
प्रकार le16 ntfsअक्षर;
#घोषणा UCHAR_T_SIZE_BITS 1

/*
 * Clusters are चिन्हित 64-bit values on NTFS volumes. We define two types, LCN
 * and VCN, to allow क्रम type checking and better code पढ़ोability.
 */
प्रकार s64 VCN;
प्रकार sle64 leVCN;
प्रकार s64 LCN;
प्रकार sle64 leLCN;

/*
 * The NTFS journal $LogFile uses log sequence numbers which are चिन्हित 64-bit
 * values.  We define our own type LSN, to allow क्रम type checking and better
 * code पढ़ोability.
 */
प्रकार s64 LSN;
प्रकार sle64 leLSN;

/*
 * The NTFS transaction log $UsnJrnl uses usn which are चिन्हित 64-bit values.
 * We define our own type USN, to allow क्रम type checking and better code
 * पढ़ोability.
 */
प्रकार s64 USN;
प्रकार sle64 leUSN;

प्रकार क्रमागत अणु
	CASE_SENSITIVE = 0,
	IGNORE_CASE = 1,
पूर्ण IGNORE_CASE_BOOL;

#पूर्ण_अगर /* _LINUX_NTFS_TYPES_H */
