<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

/*
 * Copyright 2018 IBM Corporation.
 * Copyright 2020 Canonical Ltd.
 */

#घोषणा __SANE_USERSPACE_TYPES__

#समावेश <sys/types.h>
#समावेश <मानक_निवेशt.h>
#समावेश <दो_स्मृति.h>
#समावेश <unistd.h>
#समावेश <संकेत.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश "utils.h"
#समावेश "flush_utils.h"

पूर्णांक uaccess_flush_test(व्योम)
अणु
	अक्षर *p;
	पूर्णांक repetitions = 10;
	पूर्णांक fd, passes = 0, iter, rc = 0;
	काष्ठा perf_event_पढ़ो v;
	__u64 l1d_misses_total = 0;
	अचिन्हित दीर्घ iterations = 100000, zero_size = 24 * 1024;
	अचिन्हित दीर्घ l1d_misses_expected;
	पूर्णांक rfi_flush_orig;
	पूर्णांक entry_flush_orig;
	पूर्णांक uaccess_flush, uaccess_flush_orig;

	SKIP_IF(geteuid() != 0);

	// The PMU event we use only works on Power7 or later
	SKIP_IF(!have_hwcap(PPC_FEATURE_ARCH_2_06));

	अगर (पढ़ो_debugfs_file("powerpc/rfi_flush", &rfi_flush_orig) < 0) अणु
		लिखो_त्रुटि("Unable to read powerpc/rfi_flush debugfs file");
		SKIP_IF(1);
	पूर्ण

	अगर (पढ़ो_debugfs_file("powerpc/entry_flush", &entry_flush_orig) < 0) अणु
		लिखो_त्रुटि("Unable to read powerpc/entry_flush debugfs file");
		SKIP_IF(1);
	पूर्ण

	अगर (पढ़ो_debugfs_file("powerpc/uaccess_flush", &uaccess_flush_orig) < 0) अणु
		लिखो_त्रुटि("Unable to read powerpc/entry_flush debugfs file");
		SKIP_IF(1);
	पूर्ण

	अगर (rfi_flush_orig != 0) अणु
		अगर (ग_लिखो_debugfs_file("powerpc/rfi_flush", 0) < 0) अणु
			लिखो_त्रुटि("error writing to powerpc/rfi_flush debugfs file");
			FAIL_IF(1);
		पूर्ण
	पूर्ण

	अगर (entry_flush_orig != 0) अणु
		अगर (ग_लिखो_debugfs_file("powerpc/entry_flush", 0) < 0) अणु
			लिखो_त्रुटि("error writing to powerpc/entry_flush debugfs file");
			FAIL_IF(1);
		पूर्ण
	पूर्ण

	uaccess_flush = uaccess_flush_orig;

	fd = perf_event_खोलो_counter(PERF_TYPE_HW_CACHE, PERF_L1D_READ_MISS_CONFIG, -1);
	FAIL_IF(fd < 0);

	p = (अक्षर *)memalign(zero_size, CACHELINE_SIZE);

	FAIL_IF(perf_event_enable(fd));

	// disable L1 prefetching
	set_dscr(1);

	iter = repetitions;

	/*
	 * We expect to see l1d miss क्रम each cacheline access when entry_flush
	 * is set. Allow a small variation on this.
	 */
	l1d_misses_expected = iterations * (zero_size / CACHELINE_SIZE - 2);

again:
	FAIL_IF(perf_event_reset(fd));

	syscall_loop_uaccess(p, iterations, zero_size);

	FAIL_IF(पढ़ो(fd, &v, माप(v)) != माप(v));

	अगर (uaccess_flush && v.l1d_misses >= l1d_misses_expected)
		passes++;
	अन्यथा अगर (!uaccess_flush && v.l1d_misses < (l1d_misses_expected / 2))
		passes++;

	l1d_misses_total += v.l1d_misses;

	जबतक (--iter)
		जाओ again;

	अगर (passes < repetitions) अणु
		म_लिखो("FAIL (L1D misses with uaccess_flush=%d: %llu %c %lu) [%d/%d failures]\n",
		       uaccess_flush, l1d_misses_total, uaccess_flush ? '<' : '>',
		       uaccess_flush ? repetitions * l1d_misses_expected :
		       repetitions * l1d_misses_expected / 2,
		       repetitions - passes, repetitions);
		rc = 1;
	पूर्ण अन्यथा अणु
		म_लिखो("PASS (L1D misses with uaccess_flush=%d: %llu %c %lu) [%d/%d pass]\n",
		       uaccess_flush, l1d_misses_total, uaccess_flush ? '>' : '<',
		       uaccess_flush ? repetitions * l1d_misses_expected :
		       repetitions * l1d_misses_expected / 2,
		       passes, repetitions);
	पूर्ण

	अगर (uaccess_flush == uaccess_flush_orig) अणु
		uaccess_flush = !uaccess_flush_orig;
		अगर (ग_लिखो_debugfs_file("powerpc/uaccess_flush", uaccess_flush) < 0) अणु
			लिखो_त्रुटि("error writing to powerpc/uaccess_flush debugfs file");
			वापस 1;
		पूर्ण
		iter = repetitions;
		l1d_misses_total = 0;
		passes = 0;
		जाओ again;
	पूर्ण

	perf_event_disable(fd);
	बंद(fd);

	set_dscr(0);

	अगर (ग_लिखो_debugfs_file("powerpc/rfi_flush", rfi_flush_orig) < 0) अणु
		लिखो_त्रुटि("unable to restore original value of powerpc/rfi_flush debugfs file");
		वापस 1;
	पूर्ण

	अगर (ग_लिखो_debugfs_file("powerpc/entry_flush", entry_flush_orig) < 0) अणु
		लिखो_त्रुटि("unable to restore original value of powerpc/entry_flush debugfs file");
		वापस 1;
	पूर्ण

	अगर (ग_लिखो_debugfs_file("powerpc/uaccess_flush", uaccess_flush_orig) < 0) अणु
		लिखो_त्रुटि("unable to restore original value of powerpc/uaccess_flush debugfs file");
		वापस 1;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(uaccess_flush_test, "uaccess_flush_test");
पूर्ण
