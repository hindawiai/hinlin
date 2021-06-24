<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015, Anton Blanअक्षरd, IBM Corp.
 */

#समावेश <sys/समय.स>
#समावेश <मानकपन.स>

#समावेश "utils.h"

अटल पूर्णांक test_समय_लोofday(व्योम)
अणु
	पूर्णांक i;

	काष्ठा समयval tv_start, tv_end;

	समय_लोofday(&tv_start, शून्य);

	क्रम(i = 0; i < 100000000; i++) अणु
		समय_लोofday(&tv_end, शून्य);
	पूर्ण

	म_लिखो("time = %.6f\n", tv_end.tv_sec - tv_start.tv_sec + (tv_end.tv_usec - tv_start.tv_usec) * 1e-6);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(test_समय_लोofday, "gettimeofday");
पूर्ण
