<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * समय.स - NTFS समय conversion functions.  Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2005 Anton Altaparmakov
 */

#अगर_अघोषित _LINUX_NTFS_TIME_H
#घोषणा _LINUX_NTFS_TIME_H

#समावेश <linux/समय.स>		/* For current_kernel_समय(). */
#समावेश <यंत्र/भाग64.h>		/* For करो_भाग(). */

#समावेश "endian.h"

#घोषणा NTFS_TIME_OFFSET ((s64)(369 * 365 + 89) * 24 * 3600 * 10000000)

/**
 * utc2ntfs - convert Linux UTC समय to NTFS समय
 * @ts:		Linux UTC समय to convert to NTFS समय
 *
 * Convert the Linux UTC समय @ts to its corresponding NTFS समय and वापस
 * that in little endian क्रमmat.
 *
 * Linux stores समय in a काष्ठा बारpec64 consisting of a समय64_t tv_sec
 * and a दीर्घ tv_nsec where tv_sec is the number of 1-second पूर्णांकervals since
 * 1st January 1970, 00:00:00 UTC and tv_nsec is the number of 1-nano-second
 * पूर्णांकervals since the value of tv_sec.
 *
 * NTFS uses Microsoft's standard समय क्रमmat which is stored in a s64 and is
 * measured as the number of 100-nano-second पूर्णांकervals since 1st January 1601,
 * 00:00:00 UTC.
 */
अटल अंतरभूत sle64 utc2ntfs(स्थिर काष्ठा बारpec64 ts)
अणु
	/*
	 * Convert the seconds to 100ns पूर्णांकervals, add the nano-seconds
	 * converted to 100ns पूर्णांकervals, and then add the NTFS समय offset.
	 */
	वापस cpu_to_sle64((s64)ts.tv_sec * 10000000 + ts.tv_nsec / 100 +
			NTFS_TIME_OFFSET);
पूर्ण

/**
 * get_current_ntfs_समय - get the current समय in little endian NTFS क्रमmat
 *
 * Get the current समय from the Linux kernel, convert it to its corresponding
 * NTFS समय and वापस that in little endian क्रमmat.
 */
अटल अंतरभूत sle64 get_current_ntfs_समय(व्योम)
अणु
	काष्ठा बारpec64 ts;

	kसमय_get_coarse_real_ts64(&ts);
	वापस utc2ntfs(ts);
पूर्ण

/**
 * ntfs2utc - convert NTFS समय to Linux समय
 * @समय:	NTFS समय (little endian) to convert to Linux UTC
 *
 * Convert the little endian NTFS समय @समय to its corresponding Linux UTC
 * समय and वापस that in cpu क्रमmat.
 *
 * Linux stores समय in a काष्ठा बारpec64 consisting of a समय64_t tv_sec
 * and a दीर्घ tv_nsec where tv_sec is the number of 1-second पूर्णांकervals since
 * 1st January 1970, 00:00:00 UTC and tv_nsec is the number of 1-nano-second
 * पूर्णांकervals since the value of tv_sec.
 *
 * NTFS uses Microsoft's standard समय क्रमmat which is stored in a s64 and is
 * measured as the number of 100 nano-second पूर्णांकervals since 1st January 1601,
 * 00:00:00 UTC.
 */
अटल अंतरभूत काष्ठा बारpec64 ntfs2utc(स्थिर sle64 समय)
अणु
	काष्ठा बारpec64 ts;

	/* Subtract the NTFS समय offset. */
	u64 t = (u64)(sle64_to_cpu(समय) - NTFS_TIME_OFFSET);
	/*
	 * Convert the समय to 1-second पूर्णांकervals and the reमुख्यder to
	 * 1-nano-second पूर्णांकervals.
	 */
	ts.tv_nsec = करो_भाग(t, 10000000) * 100;
	ts.tv_sec = t;
	वापस ts;
पूर्ण

#पूर्ण_अगर /* _LINUX_NTFS_TIME_H */
