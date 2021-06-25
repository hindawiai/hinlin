<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Benchmark find_next_bit and related bit operations.
 *
 * Copyright 2020 Google LLC.
 */
#समावेश <मानककोष.स>
#समावेश "bench.h"
#समावेश "../util/stat.h"
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/समय64.h>
#समावेश <subcmd/parse-options.h>

अटल अचिन्हित पूर्णांक outer_iterations = 5;
अटल अचिन्हित पूर्णांक inner_iterations = 100000;

अटल स्थिर काष्ठा option options[] = अणु
	OPT_UINTEGER('i', "outer-iterations", &outer_iterations,
		"Number of outer iterations used"),
	OPT_UINTEGER('j', "inner-iterations", &inner_iterations,
		"Number of inner iterations used"),
	OPT_END()
पूर्ण;

अटल स्थिर अक्षर *स्थिर bench_usage[] = अणु
	"perf bench mem find_bit <options>",
	शून्य
पूर्ण;

अटल अचिन्हित पूर्णांक accumulator;
अटल अचिन्हित पूर्णांक use_of_val;

अटल noअंतरभूत व्योम workload(पूर्णांक val)
अणु
	use_of_val += val;
	accumulator++;
पूर्ण

#अगर (defined(__i386__) || defined(__x86_64__)) && defined(__GCC_ASM_FLAG_OUTPUTS__)
अटल bool यंत्र_test_bit(दीर्घ nr, स्थिर अचिन्हित दीर्घ *addr)
अणु
	bool oldbit;

	यंत्र अस्थिर("bt %2,%1"
		     : "=@ccc" (oldbit)
		     : "m" (*(अचिन्हित दीर्घ *)addr), "Ir" (nr) : "memory");

	वापस oldbit;
पूर्ण
#अन्यथा
#घोषणा यंत्र_test_bit test_bit
#पूर्ण_अगर

अटल पूर्णांक करो_क्रम_each_set_bit(अचिन्हित पूर्णांक num_bits)
अणु
	अचिन्हित दीर्घ *to_test = biपंचांगap_alloc(num_bits);
	काष्ठा समयval start, end, dअगरf;
	u64 runसमय_us;
	काष्ठा stats fb_समय_stats, tb_समय_stats;
	द्विगुन समय_average, समय_stddev;
	अचिन्हित पूर्णांक bit, i, j;
	अचिन्हित पूर्णांक set_bits, skip;
	अचिन्हित पूर्णांक old;

	init_stats(&fb_समय_stats);
	init_stats(&tb_समय_stats);

	क्रम (set_bits = 1; set_bits <= num_bits; set_bits <<= 1) अणु
		biपंचांगap_zero(to_test, num_bits);
		skip = num_bits / set_bits;
		क्रम (i = 0; i < num_bits; i += skip)
			set_bit(i, to_test);

		क्रम (i = 0; i < outer_iterations; i++) अणु
			old = accumulator;
			समय_लोofday(&start, शून्य);
			क्रम (j = 0; j < inner_iterations; j++) अणु
				क्रम_each_set_bit(bit, to_test, num_bits)
					workload(bit);
			पूर्ण
			समय_लोofday(&end, शून्य);
			निश्चित(old + (inner_iterations * set_bits) == accumulator);
			समयrsub(&end, &start, &dअगरf);
			runसमय_us = dअगरf.tv_sec * USEC_PER_SEC + dअगरf.tv_usec;
			update_stats(&fb_समय_stats, runसमय_us);

			old = accumulator;
			समय_लोofday(&start, शून्य);
			क्रम (j = 0; j < inner_iterations; j++) अणु
				क्रम (bit = 0; bit < num_bits; bit++) अणु
					अगर (यंत्र_test_bit(bit, to_test))
						workload(bit);
				पूर्ण
			पूर्ण
			समय_लोofday(&end, शून्य);
			निश्चित(old + (inner_iterations * set_bits) == accumulator);
			समयrsub(&end, &start, &dअगरf);
			runसमय_us = dअगरf.tv_sec * USEC_PER_SEC + dअगरf.tv_usec;
			update_stats(&tb_समय_stats, runसमय_us);
		पूर्ण

		म_लिखो("%d operations %d bits set of %d bits\n",
			inner_iterations, set_bits, num_bits);
		समय_average = avg_stats(&fb_समय_stats);
		समय_stddev = stddev_stats(&fb_समय_stats);
		म_लिखो("  Average for_each_set_bit took: %.3f usec (+- %.3f usec)\n",
			समय_average, समय_stddev);
		समय_average = avg_stats(&tb_समय_stats);
		समय_stddev = stddev_stats(&tb_समय_stats);
		म_लिखो("  Average test_bit loop took:    %.3f usec (+- %.3f usec)\n",
			समय_average, समय_stddev);

		अगर (use_of_val == accumulator)  /* Try to aव्योम compiler tricks. */
			म_लिखो("\n");
	पूर्ण
	biपंचांगap_मुक्त(to_test);
	वापस 0;
पूर्ण

पूर्णांक bench_mem_find_bit(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक err = 0, i;

	argc = parse_options(argc, argv, options, bench_usage, 0);
	अगर (argc) अणु
		usage_with_options(bench_usage, options);
		निकास(निकास_त्रुटि);
	पूर्ण

	क्रम (i = 1; i <= 2048; i <<= 1)
		करो_क्रम_each_set_bit(i);

	वापस err;
पूर्ण
