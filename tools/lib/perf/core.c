<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#घोषणा __म_लिखो(a, b)  __attribute__((क्रमmat(म_लिखो, a, b)))

#समावेश <मानकपन.स>
#समावेश <मानकतर्क.स>
#समावेश <unistd.h>
#समावेश <linux/compiler.h>
#समावेश <perf/core.h>
#समावेश <पूर्णांकernal/lib.h>
#समावेश "internal.h"

अटल पूर्णांक __base_pr(क्रमागत libperf_prपूर्णांक_level level __maybe_unused, स्थिर अक्षर *क्रमmat,
		     बहु_सूची args)
अणु
	वापस भख_लिखो(मानक_त्रुटि, क्रमmat, args);
पूर्ण

अटल libperf_prपूर्णांक_fn_t __libperf_pr = __base_pr;

__म_लिखो(2, 3)
व्योम libperf_prपूर्णांक(क्रमागत libperf_prपूर्णांक_level level, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;

	अगर (!__libperf_pr)
		वापस;

	बहु_शुरू(args, क्रमmat);
	__libperf_pr(level, क्रमmat, args);
	बहु_पूर्ण(args);
पूर्ण

व्योम libperf_init(libperf_prपूर्णांक_fn_t fn)
अणु
	page_size = sysconf(_SC_PAGE_SIZE);
	__libperf_pr = fn;
पूर्ण
