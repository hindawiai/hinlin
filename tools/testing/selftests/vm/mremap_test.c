<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2020 Google LLC
 */
#घोषणा _GNU_SOURCE

#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <समय.स>

#समावेश "../kselftest.h"

#घोषणा EXPECT_SUCCESS 0
#घोषणा EXPECT_FAILURE 1
#घोषणा NON_OVERLAPPING 0
#घोषणा OVERLAPPING 1
#घोषणा NS_PER_SEC 1000000000ULL
#घोषणा VALIDATION_DEFAULT_THRESHOLD 4	/* 4MB */
#घोषणा VALIDATION_NO_THRESHOLD 0	/* Verअगरy the entire region */

#घोषणा ARRAY_SIZE(x) (माप(x) / माप((x)[0]))
#घोषणा MIN(X, Y) ((X) < (Y) ? (X) : (Y))

काष्ठा config अणु
	अचिन्हित दीर्घ दीर्घ src_alignment;
	अचिन्हित दीर्घ दीर्घ dest_alignment;
	अचिन्हित दीर्घ दीर्घ region_size;
	पूर्णांक overlapping;
पूर्ण;

काष्ठा test अणु
	स्थिर अक्षर *name;
	काष्ठा config config;
	पूर्णांक expect_failure;
पूर्ण;

क्रमागत अणु
	_1KB = 1ULL << 10,	/* 1KB -> not page aligned */
	_4KB = 4ULL << 10,
	_8KB = 8ULL << 10,
	_1MB = 1ULL << 20,
	_2MB = 2ULL << 20,
	_4MB = 4ULL << 20,
	_1GB = 1ULL << 30,
	_2GB = 2ULL << 30,
	PTE = _4KB,
	PMD = _2MB,
	PUD = _1GB,
पूर्ण;

#घोषणा MAKE_TEST(source_align, destination_align, size,	\
		  overlaps, should_fail, test_name)		\
अणु								\
	.name = test_name,					\
	.config = अणु						\
		.src_alignment = source_align,			\
		.dest_alignment = destination_align,		\
		.region_size = size,				\
		.overlapping = overlaps,			\
	पूर्ण,							\
	.expect_failure = should_fail				\
पूर्ण

/*
 * Returns the start address of the mapping on success, अन्यथा वापसs
 * शून्य on failure.
 */
अटल व्योम *get_source_mapping(काष्ठा config c)
अणु
	अचिन्हित दीर्घ दीर्घ addr = 0ULL;
	व्योम *src_addr = शून्य;
retry:
	addr += c.src_alignment;
	src_addr = mmap((व्योम *) addr, c.region_size, PROT_READ | PROT_WRITE,
			MAP_FIXED | MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	अगर (src_addr == MAP_FAILED) अणु
		अगर (त्रुटि_सं == EPERM)
			जाओ retry;
		जाओ error;
	पूर्ण
	/*
	 * Check that the address is aligned to the specअगरied alignment.
	 * Addresses which have alignments that are multiples of that
	 * specअगरied are not considered valid. For instance, 1GB address is
	 * 2MB-aligned, however it will not be considered valid क्रम a
	 * requested alignment of 2MB. This is करोne to reduce coincidental
	 * alignment in the tests.
	 */
	अगर (((अचिन्हित दीर्घ दीर्घ) src_addr & (c.src_alignment - 1)) ||
			!((अचिन्हित दीर्घ दीर्घ) src_addr & c.src_alignment))
		जाओ retry;

	अगर (!src_addr)
		जाओ error;

	वापस src_addr;
error:
	ksft_prपूर्णांक_msg("Failed to map source region: %s\n",
			म_त्रुटि(त्रुटि_सं));
	वापस शून्य;
पूर्ण

/* Returns the समय taken क्रम the remap on success अन्यथा वापसs -1. */
अटल दीर्घ दीर्घ remap_region(काष्ठा config c, अचिन्हित पूर्णांक threshold_mb,
			      अक्षर pattern_seed)
अणु
	व्योम *addr, *src_addr, *dest_addr;
	अचिन्हित दीर्घ दीर्घ i;
	काष्ठा बारpec t_start = अणु0, 0पूर्ण, t_end = अणु0, 0पूर्ण;
	दीर्घ दीर्घ  start_ns, end_ns, align_mask, ret, offset;
	अचिन्हित दीर्घ दीर्घ threshold;

	अगर (threshold_mb == VALIDATION_NO_THRESHOLD)
		threshold = c.region_size;
	अन्यथा
		threshold = MIN(threshold_mb * _1MB, c.region_size);

	src_addr = get_source_mapping(c);
	अगर (!src_addr) अणु
		ret = -1;
		जाओ out;
	पूर्ण

	/* Set byte pattern */
	बेक्रम(pattern_seed);
	क्रम (i = 0; i < threshold; i++)
		स_रखो((अक्षर *) src_addr + i, (अक्षर) अक्रम(), 1);

	/* Mask to zero out lower bits of address क्रम alignment */
	align_mask = ~(c.dest_alignment - 1);
	/* Offset of destination address from the end of the source region */
	offset = (c.overlapping) ? -c.dest_alignment : c.dest_alignment;
	addr = (व्योम *) (((अचिन्हित दीर्घ दीर्घ) src_addr + c.region_size
			  + offset) & align_mask);

	/* See comment in get_source_mapping() */
	अगर (!((अचिन्हित दीर्घ दीर्घ) addr & c.dest_alignment))
		addr = (व्योम *) ((अचिन्हित दीर्घ दीर्घ) addr | c.dest_alignment);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &t_start);
	dest_addr = mremap(src_addr, c.region_size, c.region_size,
			MREMAP_MAYMOVE|MREMAP_FIXED, (अक्षर *) addr);
	घड़ी_समय_लो(CLOCK_MONOTONIC, &t_end);

	अगर (dest_addr == MAP_FAILED) अणु
		ksft_prपूर्णांक_msg("mremap failed: %s\n", म_त्रुटि(त्रुटि_सं));
		ret = -1;
		जाओ clean_up_src;
	पूर्ण

	/* Verअगरy byte pattern after remapping */
	बेक्रम(pattern_seed);
	क्रम (i = 0; i < threshold; i++) अणु
		अक्षर c = (अक्षर) अक्रम();

		अगर (((अक्षर *) dest_addr)[i] != c) अणु
			ksft_prपूर्णांक_msg("Data after remap doesn't match at offset %d\n",
				       i);
			ksft_prपूर्णांक_msg("Expected: %#x\t Got: %#x\n", c & 0xff,
					((अक्षर *) dest_addr)[i] & 0xff);
			ret = -1;
			जाओ clean_up_dest;
		पूर्ण
	पूर्ण

	start_ns = t_start.tv_sec * NS_PER_SEC + t_start.tv_nsec;
	end_ns = t_end.tv_sec * NS_PER_SEC + t_end.tv_nsec;
	ret = end_ns - start_ns;

/*
 * Since the destination address is specअगरied using MREMAP_FIXED, subsequent
 * mremap will unmap any previous mapping at the address range specअगरied by
 * dest_addr and region_size. This signअगरicantly affects the remap समय of
 * subsequent tests. So we clean up mappings after each test.
 */
clean_up_dest:
	munmap(dest_addr, c.region_size);
clean_up_src:
	munmap(src_addr, c.region_size);
out:
	वापस ret;
पूर्ण

अटल व्योम run_mremap_test_हाल(काष्ठा test test_हाल, पूर्णांक *failures,
				 अचिन्हित पूर्णांक threshold_mb,
				 अचिन्हित पूर्णांक pattern_seed)
अणु
	दीर्घ दीर्घ remap_समय = remap_region(test_हाल.config, threshold_mb,
					    pattern_seed);

	अगर (remap_समय < 0) अणु
		अगर (test_हाल.expect_failure)
			ksft_test_result_pass("%s\n\tExpected mremap failure\n",
					      test_हाल.name);
		अन्यथा अणु
			ksft_test_result_fail("%s\n", test_हाल.name);
			*failures += 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Comparing mremap समय is only applicable अगर entire region
		 * was faulted in.
		 */
		अगर (threshold_mb == VALIDATION_NO_THRESHOLD ||
		    test_हाल.config.region_size <= threshold_mb * _1MB)
			ksft_test_result_pass("%s\n\tmremap time: %12lldns\n",
					      test_हाल.name, remap_समय);
		अन्यथा
			ksft_test_result_pass("%s\n", test_हाल.name);
	पूर्ण
पूर्ण

अटल व्योम usage(स्थिर अक्षर *cmd)
अणु
	ख_लिखो(मानक_त्रुटि,
		"Usage: %s [[-t <threshold_mb>] [-p <pattern_seed>]]\n"
		"-t\t only validate threshold_mb of the remapped region\n"
		"  \t if 0 is supplied no threshold is used; all tests\n"
		"  \t are run and remapped regions validated fully.\n"
		"  \t The default threshold used is 4MB.\n"
		"-p\t provide a seed to generate the random pattern for\n"
		"  \t validating the remapped region.\n", cmd);
पूर्ण

अटल पूर्णांक parse_args(पूर्णांक argc, अक्षर **argv, अचिन्हित पूर्णांक *threshold_mb,
		      अचिन्हित पूर्णांक *pattern_seed)
अणु
	स्थिर अक्षर *optstr = "t:p:";
	पूर्णांक opt;

	जबतक ((opt = getopt(argc, argv, optstr)) != -1) अणु
		चयन (opt) अणु
		हाल 't':
			*threshold_mb = म_से_प(optarg);
			अवरोध;
		हाल 'p':
			*pattern_seed = म_से_प(optarg);
			अवरोध;
		शेष:
			usage(argv[0]);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (optind < argc) अणु
		usage(argv[0]);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक failures = 0;
	पूर्णांक i, run_perf_tests;
	अचिन्हित पूर्णांक threshold_mb = VALIDATION_DEFAULT_THRESHOLD;
	अचिन्हित पूर्णांक pattern_seed;
	समय_प्रकार t;

	pattern_seed = (अचिन्हित पूर्णांक) समय(&t);

	अगर (parse_args(argc, argv, &threshold_mb, &pattern_seed) < 0)
		निकास(निकास_त्रुटि);

	ksft_prपूर्णांक_msg("Test configs:\n\tthreshold_mb=%u\n\tpattern_seed=%u\n\n",
		       threshold_mb, pattern_seed);

	काष्ठा test test_हालs[] = अणु
		/* Expected mremap failures */
		MAKE_TEST(_4KB, _4KB, _4KB, OVERLAPPING, EXPECT_FAILURE,
		  "mremap - Source and Destination Regions Overlapping"),
		MAKE_TEST(_4KB, _1KB, _4KB, NON_OVERLAPPING, EXPECT_FAILURE,
		  "mremap - Destination Address Misaligned (1KB-aligned)"),
		MAKE_TEST(_1KB, _4KB, _4KB, NON_OVERLAPPING, EXPECT_FAILURE,
		  "mremap - Source Address Misaligned (1KB-aligned)"),

		/* Src addr PTE aligned */
		MAKE_TEST(PTE, PTE, _8KB, NON_OVERLAPPING, EXPECT_SUCCESS,
		  "8KB mremap - Source PTE-aligned, Destination PTE-aligned"),

		/* Src addr 1MB aligned */
		MAKE_TEST(_1MB, PTE, _2MB, NON_OVERLAPPING, EXPECT_SUCCESS,
		  "2MB mremap - Source 1MB-aligned, Destination PTE-aligned"),
		MAKE_TEST(_1MB, _1MB, _2MB, NON_OVERLAPPING, EXPECT_SUCCESS,
		  "2MB mremap - Source 1MB-aligned, Destination 1MB-aligned"),

		/* Src addr PMD aligned */
		MAKE_TEST(PMD, PTE, _4MB, NON_OVERLAPPING, EXPECT_SUCCESS,
		  "4MB mremap - Source PMD-aligned, Destination PTE-aligned"),
		MAKE_TEST(PMD, _1MB, _4MB, NON_OVERLAPPING, EXPECT_SUCCESS,
		  "4MB mremap - Source PMD-aligned, Destination 1MB-aligned"),
		MAKE_TEST(PMD, PMD, _4MB, NON_OVERLAPPING, EXPECT_SUCCESS,
		  "4MB mremap - Source PMD-aligned, Destination PMD-aligned"),

		/* Src addr PUD aligned */
		MAKE_TEST(PUD, PTE, _2GB, NON_OVERLAPPING, EXPECT_SUCCESS,
		  "2GB mremap - Source PUD-aligned, Destination PTE-aligned"),
		MAKE_TEST(PUD, _1MB, _2GB, NON_OVERLAPPING, EXPECT_SUCCESS,
		  "2GB mremap - Source PUD-aligned, Destination 1MB-aligned"),
		MAKE_TEST(PUD, PMD, _2GB, NON_OVERLAPPING, EXPECT_SUCCESS,
		  "2GB mremap - Source PUD-aligned, Destination PMD-aligned"),
		MAKE_TEST(PUD, PUD, _2GB, NON_OVERLAPPING, EXPECT_SUCCESS,
		  "2GB mremap - Source PUD-aligned, Destination PUD-aligned"),
	पूर्ण;

	काष्ठा test perf_test_हालs[] = अणु
		/*
		 * mremap 1GB region - Page table level aligned समय
		 * comparison.
		 */
		MAKE_TEST(PTE, PTE, _1GB, NON_OVERLAPPING, EXPECT_SUCCESS,
		  "1GB mremap - Source PTE-aligned, Destination PTE-aligned"),
		MAKE_TEST(PMD, PMD, _1GB, NON_OVERLAPPING, EXPECT_SUCCESS,
		  "1GB mremap - Source PMD-aligned, Destination PMD-aligned"),
		MAKE_TEST(PUD, PUD, _1GB, NON_OVERLAPPING, EXPECT_SUCCESS,
		  "1GB mremap - Source PUD-aligned, Destination PUD-aligned"),
	पूर्ण;

	run_perf_tests =  (threshold_mb == VALIDATION_NO_THRESHOLD) ||
				(threshold_mb * _1MB >= _1GB);

	ksft_set_plan(ARRAY_SIZE(test_हालs) + (run_perf_tests ?
		      ARRAY_SIZE(perf_test_हालs) : 0));

	क्रम (i = 0; i < ARRAY_SIZE(test_हालs); i++)
		run_mremap_test_हाल(test_हालs[i], &failures, threshold_mb,
				     pattern_seed);

	अगर (run_perf_tests) अणु
		ksft_prपूर्णांक_msg("\n%s\n",
		 "mremap HAVE_MOVE_PMD/PUD optimization time comparison for 1GB region:");
		क्रम (i = 0; i < ARRAY_SIZE(perf_test_हालs); i++)
			run_mremap_test_हाल(perf_test_हालs[i], &failures,
					     threshold_mb, pattern_seed);
	पूर्ण

	अगर (failures > 0)
		ksft_निकास_fail();
	अन्यथा
		ksft_निकास_pass();
पूर्ण
