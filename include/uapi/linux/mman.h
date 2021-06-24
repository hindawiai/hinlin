<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_MMAN_H
#घोषणा _UAPI_LINUX_MMAN_H

#समावेश <यंत्र/mman.h>
#समावेश <यंत्र-generic/hugetlb_encode.h>

#घोषणा MREMAP_MAYMOVE		1
#घोषणा MREMAP_FIXED		2
#घोषणा MREMAP_DONTUNMAP	4

#घोषणा OVERCOMMIT_GUESS		0
#घोषणा OVERCOMMIT_ALWAYS		1
#घोषणा OVERCOMMIT_NEVER		2

#घोषणा MAP_SHARED	0x01		/* Share changes */
#घोषणा MAP_PRIVATE	0x02		/* Changes are निजी */
#घोषणा MAP_SHARED_VALIDATE 0x03	/* share + validate extension flags */

/*
 * Huge page size encoding when MAP_HUGETLB is specअगरied, and a huge page
 * size other than the शेष is desired.  See hugetlb_encode.h.
 * All known huge page size encodings are provided here.  It is the
 * responsibility of the application to know which sizes are supported on
 * the running प्रणाली.  See mmap(2) man page क्रम details.
 */
#घोषणा MAP_HUGE_SHIFT	HUGETLB_FLAG_ENCODE_SHIFT
#घोषणा MAP_HUGE_MASK	HUGETLB_FLAG_ENCODE_MASK

#घोषणा MAP_HUGE_16KB	HUGETLB_FLAG_ENCODE_16KB
#घोषणा MAP_HUGE_64KB	HUGETLB_FLAG_ENCODE_64KB
#घोषणा MAP_HUGE_512KB	HUGETLB_FLAG_ENCODE_512KB
#घोषणा MAP_HUGE_1MB	HUGETLB_FLAG_ENCODE_1MB
#घोषणा MAP_HUGE_2MB	HUGETLB_FLAG_ENCODE_2MB
#घोषणा MAP_HUGE_8MB	HUGETLB_FLAG_ENCODE_8MB
#घोषणा MAP_HUGE_16MB	HUGETLB_FLAG_ENCODE_16MB
#घोषणा MAP_HUGE_32MB	HUGETLB_FLAG_ENCODE_32MB
#घोषणा MAP_HUGE_256MB	HUGETLB_FLAG_ENCODE_256MB
#घोषणा MAP_HUGE_512MB	HUGETLB_FLAG_ENCODE_512MB
#घोषणा MAP_HUGE_1GB	HUGETLB_FLAG_ENCODE_1GB
#घोषणा MAP_HUGE_2GB	HUGETLB_FLAG_ENCODE_2GB
#घोषणा MAP_HUGE_16GB	HUGETLB_FLAG_ENCODE_16GB

#पूर्ण_अगर /* _UAPI_LINUX_MMAN_H */
