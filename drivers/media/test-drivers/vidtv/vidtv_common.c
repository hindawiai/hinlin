<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The Virtual DVB test driver serves as a reference DVB driver and helps
 * validate the existing APIs in the media subप्रणाली. It can also aid
 * developers working on userspace applications.
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s, %d: " fmt, __func__, __LINE__

#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>

#समावेश "vidtv_common.h"

/**
 * vidtv_स_नकल() - wrapper routine to be used by MPEG-TS
 *	generator, in order to aव्योम going past the
 *	output buffer.
 * @to:	Starting element to where a MPEG-TS packet will
 *	be copied.
 * @to_offset:	Starting position of the @to buffer to be filled.
 * @to_size:	Size of the @to buffer.
 * @from:	Starting element of the buffer to be copied.
 * @len:	Number of elements to be copy from @from buffer
 *	पूर्णांकo @to+ @to_offset buffer.
 *
 * Note:
 *	Real digital TV demod drivers should not have स_नकल
 *	wrappers. We use it here because emulating MPEG-TS
 *	generation at kernelspace requires some extra care.
 *
 * Return:
 *	Returns the number of bytes written
 */
u32 vidtv_स_नकल(व्योम *to,
		 माप_प्रकार to_offset,
		 माप_प्रकार to_size,
		 स्थिर व्योम *from,
		 माप_प्रकार len)
अणु
	अगर (unlikely(to_offset + len > to_size)) अणु
		pr_err_ratelimited("overflow detected, skipping. Try increasing the buffer size. Needed %zu, had %zu\n",
				   to_offset + len,
				   to_size);
		वापस 0;
	पूर्ण

	स_नकल(to + to_offset, from, len);
	वापस len;
पूर्ण

/**
 * vidtv_स_रखो() - wrapper routine to be used by MPEG-TS
 *	generator, in order to aव्योम going past the
 *	output buffer.
 * @to:	Starting element to set
 * @to_offset:	Starting position of the @to buffer to be filled.
 * @to_size:	Size of the @to buffer.
 * @c:		The value to set the memory to.
 * @len:	Number of elements to be copy from @from buffer
 *	पूर्णांकo @to+ @to_offset buffer.
 *
 * Note:
 *	Real digital TV demod drivers should not have स_रखो
 *	wrappers. We use it here because emulating MPEG-TS
 *	generation at kernelspace requires some extra care.
 *
 * Return:
 *	Returns the number of bytes written
 */
u32 vidtv_स_रखो(व्योम *to,
		 माप_प्रकार to_offset,
		 माप_प्रकार to_size,
		 स्थिर पूर्णांक c,
		 माप_प्रकार len)
अणु
	अगर (unlikely(to_offset + len > to_size)) अणु
		pr_err_ratelimited("overflow detected, skipping. Try increasing the buffer size. Needed %zu, had %zu\n",
				   to_offset + len,
				   to_size);
		वापस 0;
	पूर्ण

	स_रखो(to + to_offset, c, len);
	वापस len;
पूर्ण
