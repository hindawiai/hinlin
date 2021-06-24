<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016, Anton Blanअक्षरd, Michael Ellerman, IBM Corp.
 */

#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>
#समावेश <sys/syscall.h>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <linux/futex.h>

#समावेश "utils.h"

#घोषणा ITERATIONS 100000000

#घोषणा futex(A, B, C, D, E, F)	 syscall(__NR_futex, A, B, C, D, E, F)

पूर्णांक test_futex(व्योम)
अणु
	काष्ठा बारpec ts_start, ts_end;
	अचिन्हित दीर्घ i = ITERATIONS;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts_start);

	जबतक (i--) अणु
		अचिन्हित पूर्णांक addr = 0;
		futex(&addr, FUTEX_WAKE, 1, शून्य, शून्य, 0);
	पूर्ण

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts_end);

	म_लिखो("time = %.6f\n", ts_end.tv_sec - ts_start.tv_sec + (ts_end.tv_nsec - ts_start.tv_nsec) / 1e9);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	test_harness_set_समयout(300);
	वापस test_harness(test_futex, "futex_bench");
पूर्ण
