<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_MEMFD_H
#घोषणा _UAPI_LINUX_MEMFD_H

#समावेश <यंत्र-generic/hugetlb_encode.h>

/* flags क्रम memfd_create(2) (अचिन्हित पूर्णांक) */
#घोषणा MFD_CLOEXEC		0x0001U
#घोषणा MFD_ALLOW_SEALING	0x0002U
#घोषणा MFD_HUGETLB		0x0004U

/*
 * Huge page size encoding when MFD_HUGETLB is specअगरied, and a huge page
 * size other than the शेष is desired.  See hugetlb_encode.h.
 * All known huge page size encodings are provided here.  It is the
 * responsibility of the application to know which sizes are supported on
 * the running प्रणाली.  See mmap(2) man page क्रम details.
 */
#घोषणा MFD_HUGE_SHIFT	HUGETLB_FLAG_ENCODE_SHIFT
#घोषणा MFD_HUGE_MASK	HUGETLB_FLAG_ENCODE_MASK

#घोषणा MFD_HUGE_64KB	HUGETLB_FLAG_ENCODE_64KB
#घोषणा MFD_HUGE_512KB	HUGETLB_FLAG_ENCODE_512KB
#घोषणा MFD_HUGE_1MB	HUGETLB_FLAG_ENCODE_1MB
#घोषणा MFD_HUGE_2MB	HUGETLB_FLAG_ENCODE_2MB
#घोषणा MFD_HUGE_8MB	HUGETLB_FLAG_ENCODE_8MB
#घोषणा MFD_HUGE_16MB	HUGETLB_FLAG_ENCODE_16MB
#घोषणा MFD_HUGE_32MB	HUGETLB_FLAG_ENCODE_32MB
#घोषणा MFD_HUGE_256MB	HUGETLB_FLAG_ENCODE_256MB
#घोषणा MFD_HUGE_512MB	HUGETLB_FLAG_ENCODE_512MB
#घोषणा MFD_HUGE_1GB	HUGETLB_FLAG_ENCODE_1GB
#घोषणा MFD_HUGE_2GB	HUGETLB_FLAG_ENCODE_2GB
#घोषणा MFD_HUGE_16GB	HUGETLB_FLAG_ENCODE_16GB

#पूर्ण_अगर /* _UAPI_LINUX_MEMFD_H */
