<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016, Anton Blanअक्षरd, Michael Ellerman, IBM Corp.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/mman.h>
#समावेश <समय.स>
#समावेश <getopt.h>

#समावेश "utils.h"

#घोषणा ITERATIONS 5000000

#घोषणा MEMSIZE (1UL << 27)
#घोषणा PAGE_SIZE (1UL << 16)
#घोषणा CHUNK_COUNT (MEMSIZE/PAGE_SIZE)

अटल पूर्णांक pg_fault;
अटल पूर्णांक iterations = ITERATIONS;

अटल काष्ठा option options[] = अणु
	अणु "pgfault", no_argument, &pg_fault, 1 पूर्ण,
	अणु "iterations", required_argument, 0, 'i' पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;

अटल व्योम usage(व्योम)
अणु
	म_लिखो("mmap_bench <--pgfault> <--iterations count>\n");
पूर्ण

पूर्णांक test_mmap(व्योम)
अणु
	काष्ठा बारpec ts_start, ts_end;
	अचिन्हित दीर्घ i = iterations;

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts_start);

	जबतक (i--) अणु
		अक्षर *c = mmap(शून्य, MEMSIZE, PROT_READ|PROT_WRITE,
			       MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
		FAIL_IF(c == MAP_FAILED);
		अगर (pg_fault) अणु
			पूर्णांक count;
			क्रम (count = 0; count < CHUNK_COUNT; count++)
				c[count << 16] = 'c';
		पूर्ण
		munmap(c, MEMSIZE);
	पूर्ण

	घड़ी_समय_लो(CLOCK_MONOTONIC, &ts_end);

	म_लिखो("time = %.6f\n", ts_end.tv_sec - ts_start.tv_sec + (ts_end.tv_nsec - ts_start.tv_nsec) / 1e9);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	चिन्हित अक्षर c;
	जबतक (1) अणु
		पूर्णांक option_index = 0;

		c = getopt_दीर्घ(argc, argv, "", options, &option_index);

		अगर (c == -1)
			अवरोध;

		चयन (c) अणु
		हाल 0:
			अगर (options[option_index].flag != 0)
				अवरोध;

			usage();
			निकास(1);
			अवरोध;
		हाल 'i':
			iterations = म_से_प(optarg);
			अवरोध;
		शेष:
			usage();
			निकास(1);
		पूर्ण
	पूर्ण

	test_harness_set_समयout(300);
	वापस test_harness(test_mmap, "mmap_bench");
पूर्ण
