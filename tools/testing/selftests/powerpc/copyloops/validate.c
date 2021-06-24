<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <दो_स्मृति.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>

#समावेश "utils.h"

#घोषणा MAX_LEN 8192
#घोषणा MAX_OFFSET 16
#घोषणा MIN_REDZONE 128
#घोषणा BUFLEN (MAX_LEN+MAX_OFFSET+2*MIN_REDZONE)
#घोषणा POISON 0xa5

अचिन्हित दीर्घ COPY_LOOP(व्योम *to, स्थिर व्योम *from, अचिन्हित दीर्घ size);

अटल व्योम करो_one(अक्षर *src, अक्षर *dst, अचिन्हित दीर्घ src_off,
		   अचिन्हित दीर्घ dst_off, अचिन्हित दीर्घ len, व्योम *redzone,
		   व्योम *fill)
अणु
	अक्षर *srcp, *dstp;
	अचिन्हित दीर्घ ret;
	अचिन्हित दीर्घ i;

	srcp = src + MIN_REDZONE + src_off;
	dstp = dst + MIN_REDZONE + dst_off;

	स_रखो(src, POISON, BUFLEN);
	स_रखो(dst, POISON, BUFLEN);
	स_नकल(srcp, fill, len);

	ret = COPY_LOOP(dstp, srcp, len);
	अगर (ret && ret != (अचिन्हित दीर्घ)dstp) अणु
		म_लिखो("(%p,%p,%ld) returned %ld\n", dstp, srcp, len, ret);
		पात();
	पूर्ण

	अगर (स_भेद(dstp, srcp, len)) अणु
		म_लिखो("(%p,%p,%ld) miscompare\n", dstp, srcp, len);
		म_लिखो("src: ");
		क्रम (i = 0; i < len; i++)
			म_लिखो("%02x ", srcp[i]);
		म_लिखो("\ndst: ");
		क्रम (i = 0; i < len; i++)
			म_लिखो("%02x ", dstp[i]);
		म_लिखो("\n");
		पात();
	पूर्ण

	अगर (स_भेद(dst, redzone, dstp - dst)) अणु
		म_लिखो("(%p,%p,%ld) redzone before corrupted\n",
		       dstp, srcp, len);
		पात();
	पूर्ण

	अगर (स_भेद(dstp+len, redzone, dst+BUFLEN-(dstp+len))) अणु
		म_लिखो("(%p,%p,%ld) redzone after corrupted\n",
		       dstp, srcp, len);
		पात();
	पूर्ण
पूर्ण

पूर्णांक test_copy_loop(व्योम)
अणु
	अक्षर *src, *dst, *redzone, *fill;
	अचिन्हित दीर्घ len, src_off, dst_off;
	अचिन्हित दीर्घ i;

	src = memalign(BUFLEN, BUFLEN);
	dst = memalign(BUFLEN, BUFLEN);
	redzone = दो_स्मृति(BUFLEN);
	fill = दो_स्मृति(BUFLEN);

	अगर (!src || !dst || !redzone || !fill) अणु
		ख_लिखो(मानक_त्रुटि, "malloc failed\n");
		निकास(1);
	पूर्ण

	स_रखो(redzone, POISON, BUFLEN);

	/* Fill with sequential bytes */
	क्रम (i = 0; i < BUFLEN; i++)
		fill[i] = i & 0xff;

	क्रम (len = 1; len < MAX_LEN; len++) अणु
		क्रम (src_off = 0; src_off < MAX_OFFSET; src_off++) अणु
			क्रम (dst_off = 0; dst_off < MAX_OFFSET; dst_off++) अणु
				करो_one(src, dst, src_off, dst_off, len,
				       redzone, fill);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test_copy_loop, str(COPY_LOOP));
पूर्ण
