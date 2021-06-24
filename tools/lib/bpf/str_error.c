<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)
#अघोषित _GNU_SOURCE
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश "str_error.h"

/* make sure libbpf करोesn't use kernel-only पूर्णांकeger प्रकारs */
#आशय GCC poison u8 u16 u32 u64 s8 s16 s32 s64

/*
 * Wrapper to allow क्रम building in non-GNU प्रणालीs such as Alpine Linux's musl
 * libc, जबतक checking म_त्रुटि_r() वापस to aव्योम having to check this in
 * all places calling it.
 */
अक्षर *libbpf_म_त्रुटि_r(पूर्णांक err, अक्षर *dst, पूर्णांक len)
अणु
	पूर्णांक ret = म_त्रुटि_r(err < 0 ? -err : err, dst, len);
	अगर (ret)
		snम_लिखो(dst, len, "ERROR: strerror_r(%d)=%d", err, ret);
	वापस dst;
पूर्ण
