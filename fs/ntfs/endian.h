<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * endian.h - Defines क्रम endianness handling in NTFS Linux kernel driver.
 *	      Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2004 Anton Altaparmakov
 */

#अगर_अघोषित _LINUX_NTFS_ENDIAN_H
#घोषणा _LINUX_NTFS_ENDIAN_H

#समावेश <यंत्र/byteorder.h>
#समावेश "types.h"

/*
 * Signed endianness conversion functions.
 */

अटल अंतरभूत s16 sle16_to_cpu(sle16 x)
अणु
	वापस le16_to_cpu((__क्रमce le16)x);
पूर्ण

अटल अंतरभूत s32 sle32_to_cpu(sle32 x)
अणु
	वापस le32_to_cpu((__क्रमce le32)x);
पूर्ण

अटल अंतरभूत s64 sle64_to_cpu(sle64 x)
अणु
	वापस le64_to_cpu((__क्रमce le64)x);
पूर्ण

अटल अंतरभूत s16 sle16_to_cpup(sle16 *x)
अणु
	वापस le16_to_cpu(*(__क्रमce le16*)x);
पूर्ण

अटल अंतरभूत s32 sle32_to_cpup(sle32 *x)
अणु
	वापस le32_to_cpu(*(__क्रमce le32*)x);
पूर्ण

अटल अंतरभूत s64 sle64_to_cpup(sle64 *x)
अणु
	वापस le64_to_cpu(*(__क्रमce le64*)x);
पूर्ण

अटल अंतरभूत sle16 cpu_to_sle16(s16 x)
अणु
	वापस (__क्रमce sle16)cpu_to_le16(x);
पूर्ण

अटल अंतरभूत sle32 cpu_to_sle32(s32 x)
अणु
	वापस (__क्रमce sle32)cpu_to_le32(x);
पूर्ण

अटल अंतरभूत sle64 cpu_to_sle64(s64 x)
अणु
	वापस (__क्रमce sle64)cpu_to_le64(x);
पूर्ण

अटल अंतरभूत sle16 cpu_to_sle16p(s16 *x)
अणु
	वापस (__क्रमce sle16)cpu_to_le16(*x);
पूर्ण

अटल अंतरभूत sle32 cpu_to_sle32p(s32 *x)
अणु
	वापस (__क्रमce sle32)cpu_to_le32(*x);
पूर्ण

अटल अंतरभूत sle64 cpu_to_sle64p(s64 *x)
अणु
	वापस (__क्रमce sle64)cpu_to_le64(*x);
पूर्ण

#पूर्ण_अगर /* _LINUX_NTFS_ENDIAN_H */
