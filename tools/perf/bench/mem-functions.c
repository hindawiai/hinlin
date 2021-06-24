<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mem-स_नकल.c
 *
 * Simple स_नकल() and स_रखो() benchmarks
 *
 * Written by Hitoshi Mitake <mitake@dcl.info.waseda.ac.jp>
 */

#समावेश "debug.h"
#समावेश "../perf-sys.h"
#समावेश <subcmd/parse-options.h>
#समावेश "../util/header.h"
#समावेश "../util/cloexec.h"
#समावेश "../util/string2.h"
#समावेश "bench.h"
#समावेश "mem-memcpy-arch.h"
#समावेश "mem-memset-arch.h"

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/समय.स>
#समावेश <त्रुटिसं.स>
#समावेश <linux/समय64.h>
#समावेश <linux/zभाग.स>

#घोषणा K 1024

अटल स्थिर अक्षर	*size_str	= "1MB";
अटल स्थिर अक्षर	*function_str	= "all";
अटल पूर्णांक		nr_loops	= 1;
अटल bool		use_cycles;
अटल पूर्णांक		cycles_fd;

अटल स्थिर काष्ठा option options[] = अणु
	OPT_STRING('s', "size", &size_str, "1MB",
		    "Specify the size of the memory buffers. "
		    "Available units: B, KB, MB, GB and TB (case insensitive)"),

	OPT_STRING('f', "function", &function_str, "all",
		    "Specify the function to run, \"all\" runs all available functions, \"help\" lists them"),

	OPT_INTEGER('l', "nr_loops", &nr_loops,
		    "Specify the number of loops to run. (default: 1)"),

	OPT_BOOLEAN('c', "cycles", &use_cycles,
		    "Use a cycles event instead of gettimeofday() to measure performance"),

	OPT_END()
पूर्ण;

प्रकार व्योम *(*स_नकल_t)(व्योम *, स्थिर व्योम *, माप_प्रकार);
प्रकार व्योम *(*स_रखो_t)(व्योम *, पूर्णांक, माप_प्रकार);

काष्ठा function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *desc;
	जोड़ अणु
		स_नकल_t स_नकल;
		स_रखो_t स_रखो;
	पूर्ण fn;
पूर्ण;

अटल काष्ठा perf_event_attr cycle_attr = अणु
	.type		= PERF_TYPE_HARDWARE,
	.config		= PERF_COUNT_HW_CPU_CYCLES
पूर्ण;

अटल पूर्णांक init_cycles(व्योम)
अणु
	cycles_fd = sys_perf_event_खोलो(&cycle_attr, getpid(), -1, -1, perf_event_खोलो_cloexec_flag());

	अगर (cycles_fd < 0 && त्रुटि_सं == ENOSYS) अणु
		pr_debug("No CONFIG_PERF_EVENTS=y kernel support configured?\n");
		वापस -1;
	पूर्ण

	वापस cycles_fd;
पूर्ण

अटल u64 get_cycles(व्योम)
अणु
	पूर्णांक ret;
	u64 clk;

	ret = पढ़ो(cycles_fd, &clk, माप(u64));
	BUG_ON(ret != माप(u64));

	वापस clk;
पूर्ण

अटल द्विगुन समयval2द्विगुन(काष्ठा समयval *ts)
अणु
	वापस (द्विगुन)ts->tv_sec + (द्विगुन)ts->tv_usec / (द्विगुन)USEC_PER_SEC;
पूर्ण

#घोषणा prपूर्णांक_bps(x) करो अणु						\
		अगर (x < K)						\
			म_लिखो(" %14lf bytes/sec\n", x);		\
		अन्यथा अगर (x < K * K)					\
			म_लिखो(" %14lfd KB/sec\n", x / K);		\
		अन्यथा अगर (x < K * K * K)					\
			म_लिखो(" %14lf MB/sec\n", x / K / K);		\
		अन्यथा							\
			म_लिखो(" %14lf GB/sec\n", x / K / K / K);	\
	पूर्ण जबतक (0)

काष्ठा bench_mem_info अणु
	स्थिर काष्ठा function *functions;
	u64 (*करो_cycles)(स्थिर काष्ठा function *r, माप_प्रकार size, व्योम *src, व्योम *dst);
	द्विगुन (*करो_समय_लोofday)(स्थिर काष्ठा function *r, माप_प्रकार size, व्योम *src, व्योम *dst);
	स्थिर अक्षर *स्थिर *usage;
	bool alloc_src;
पूर्ण;

अटल व्योम __bench_mem_function(काष्ठा bench_mem_info *info, पूर्णांक r_idx, माप_प्रकार size, द्विगुन माप_प्रकारotal)
अणु
	स्थिर काष्ठा function *r = &info->functions[r_idx];
	द्विगुन result_bps = 0.0;
	u64 result_cycles = 0;
	व्योम *src = शून्य, *dst = zalloc(size);

	म_लिखो("# function '%s' (%s)\n", r->name, r->desc);

	अगर (dst == शून्य)
		जाओ out_alloc_failed;

	अगर (info->alloc_src) अणु
		src = zalloc(size);
		अगर (src == शून्य)
			जाओ out_alloc_failed;
	पूर्ण

	अगर (bench_क्रमmat == BENCH_FORMAT_DEFAULT)
		म_लिखो("# Copying %s bytes ...\n\n", size_str);

	अगर (use_cycles) अणु
		result_cycles = info->करो_cycles(r, size, src, dst);
	पूर्ण अन्यथा अणु
		result_bps = info->करो_समय_लोofday(r, size, src, dst);
	पूर्ण

	चयन (bench_क्रमmat) अणु
	हाल BENCH_FORMAT_DEFAULT:
		अगर (use_cycles) अणु
			म_लिखो(" %14lf cycles/byte\n", (द्विगुन)result_cycles/माप_प्रकारotal);
		पूर्ण अन्यथा अणु
			prपूर्णांक_bps(result_bps);
		पूर्ण
		अवरोध;

	हाल BENCH_FORMAT_SIMPLE:
		अगर (use_cycles) अणु
			म_लिखो("%lf\n", (द्विगुन)result_cycles/माप_प्रकारotal);
		पूर्ण अन्यथा अणु
			म_लिखो("%lf\n", result_bps);
		पूर्ण
		अवरोध;

	शेष:
		BUG_ON(1);
		अवरोध;
	पूर्ण

out_मुक्त:
	मुक्त(src);
	मुक्त(dst);
	वापस;
out_alloc_failed:
	म_लिखो("# Memory allocation failed - maybe size (%s) is too large?\n", size_str);
	जाओ out_मुक्त;
पूर्ण

अटल पूर्णांक bench_mem_common(पूर्णांक argc, स्थिर अक्षर **argv, काष्ठा bench_mem_info *info)
अणु
	पूर्णांक i;
	माप_प्रकार size;
	द्विगुन माप_प्रकारotal;

	argc = parse_options(argc, argv, options, info->usage, 0);

	अगर (use_cycles) अणु
		i = init_cycles();
		अगर (i < 0) अणु
			ख_लिखो(मानक_त्रुटि, "Failed to open cycles counter\n");
			वापस i;
		पूर्ण
	पूर्ण

	size = (माप_प्रकार)perf_म_से_दl((अक्षर *)size_str);
	माप_प्रकारotal = (द्विगुन)size * nr_loops;

	अगर ((s64)size <= 0) अणु
		ख_लिखो(मानक_त्रुटि, "Invalid size:%s\n", size_str);
		वापस 1;
	पूर्ण

	अगर (!म_भेदन(function_str, "all", 3)) अणु
		क्रम (i = 0; info->functions[i].name; i++)
			__bench_mem_function(info, i, size, माप_प्रकारotal);
		वापस 0;
	पूर्ण

	क्रम (i = 0; info->functions[i].name; i++) अणु
		अगर (!म_भेद(info->functions[i].name, function_str))
			अवरोध;
	पूर्ण
	अगर (!info->functions[i].name) अणु
		अगर (म_भेद(function_str, "help") && म_भेद(function_str, "h"))
			म_लिखो("Unknown function: %s\n", function_str);
		म_लिखो("Available functions:\n");
		क्रम (i = 0; info->functions[i].name; i++) अणु
			म_लिखो("\t%s ... %s\n",
			       info->functions[i].name, info->functions[i].desc);
		पूर्ण
		वापस 1;
	पूर्ण

	__bench_mem_function(info, i, size, माप_प्रकारotal);

	वापस 0;
पूर्ण

अटल व्योम स_नकल_prefault(स_नकल_t fn, माप_प्रकार size, व्योम *src, व्योम *dst)
अणु
	/* Make sure to always prefault zero pages even अगर MMAP_THRESH is crossed: */
	स_रखो(src, 0, size);

	/*
	 * We prefault the freshly allocated memory range here,
	 * to not measure page fault overhead:
	 */
	fn(dst, src, size);
पूर्ण

अटल u64 करो_स_नकल_cycles(स्थिर काष्ठा function *r, माप_प्रकार size, व्योम *src, व्योम *dst)
अणु
	u64 cycle_start = 0ULL, cycle_end = 0ULL;
	स_नकल_t fn = r->fn.स_नकल;
	पूर्णांक i;

	स_नकल_prefault(fn, size, src, dst);

	cycle_start = get_cycles();
	क्रम (i = 0; i < nr_loops; ++i)
		fn(dst, src, size);
	cycle_end = get_cycles();

	वापस cycle_end - cycle_start;
पूर्ण

अटल द्विगुन करो_स_नकल_समय_लोofday(स्थिर काष्ठा function *r, माप_प्रकार size, व्योम *src, व्योम *dst)
अणु
	काष्ठा समयval tv_start, tv_end, tv_dअगरf;
	स_नकल_t fn = r->fn.स_नकल;
	पूर्णांक i;

	स_नकल_prefault(fn, size, src, dst);

	BUG_ON(समय_लोofday(&tv_start, शून्य));
	क्रम (i = 0; i < nr_loops; ++i)
		fn(dst, src, size);
	BUG_ON(समय_लोofday(&tv_end, शून्य));

	समयrsub(&tv_end, &tv_start, &tv_dअगरf);

	वापस (द्विगुन)(((द्विगुन)size * nr_loops) / समयval2द्विगुन(&tv_dअगरf));
पूर्ण

काष्ठा function स_नकल_functions[] = अणु
	अणु .name		= "default",
	  .desc		= "Default memcpy() provided by glibc",
	  .fn.स_नकल	= स_नकल पूर्ण,

#अगर_घोषित HAVE_ARCH_X86_64_SUPPORT
# define MEMCPY_FN(_fn, _name, _desc) अणु.name = _name, .desc = _desc, .fn.स_नकल = _fnपूर्ण,
# include "mem-memcpy-x86-64-asm-def.h"
# undef MEMCPY_FN
#पूर्ण_अगर

	अणु .name = शून्य, पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर bench_mem_स_नकल_usage[] = अणु
	"perf bench mem memcpy <options>",
	शून्य
पूर्ण;

पूर्णांक bench_mem_स_नकल(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा bench_mem_info info = अणु
		.functions		= स_नकल_functions,
		.करो_cycles		= करो_स_नकल_cycles,
		.करो_समय_लोofday	= करो_स_नकल_समय_लोofday,
		.usage			= bench_mem_स_नकल_usage,
		.alloc_src              = true,
	पूर्ण;

	वापस bench_mem_common(argc, argv, &info);
पूर्ण

अटल u64 करो_स_रखो_cycles(स्थिर काष्ठा function *r, माप_प्रकार size, व्योम *src __maybe_unused, व्योम *dst)
अणु
	u64 cycle_start = 0ULL, cycle_end = 0ULL;
	स_रखो_t fn = r->fn.स_रखो;
	पूर्णांक i;

	/*
	 * We prefault the freshly allocated memory range here,
	 * to not measure page fault overhead:
	 */
	fn(dst, -1, size);

	cycle_start = get_cycles();
	क्रम (i = 0; i < nr_loops; ++i)
		fn(dst, i, size);
	cycle_end = get_cycles();

	वापस cycle_end - cycle_start;
पूर्ण

अटल द्विगुन करो_स_रखो_समय_लोofday(स्थिर काष्ठा function *r, माप_प्रकार size, व्योम *src __maybe_unused, व्योम *dst)
अणु
	काष्ठा समयval tv_start, tv_end, tv_dअगरf;
	स_रखो_t fn = r->fn.स_रखो;
	पूर्णांक i;

	/*
	 * We prefault the freshly allocated memory range here,
	 * to not measure page fault overhead:
	 */
	fn(dst, -1, size);

	BUG_ON(समय_लोofday(&tv_start, शून्य));
	क्रम (i = 0; i < nr_loops; ++i)
		fn(dst, i, size);
	BUG_ON(समय_लोofday(&tv_end, शून्य));

	समयrsub(&tv_end, &tv_start, &tv_dअगरf);

	वापस (द्विगुन)(((द्विगुन)size * nr_loops) / समयval2द्विगुन(&tv_dअगरf));
पूर्ण

अटल स्थिर अक्षर * स्थिर bench_mem_स_रखो_usage[] = अणु
	"perf bench mem memset <options>",
	शून्य
पूर्ण;

अटल स्थिर काष्ठा function स_रखो_functions[] = अणु
	अणु .name		= "default",
	  .desc		= "Default memset() provided by glibc",
	  .fn.स_रखो	= स_रखो पूर्ण,

#अगर_घोषित HAVE_ARCH_X86_64_SUPPORT
# define MEMSET_FN(_fn, _name, _desc) अणु .name = _name, .desc = _desc, .fn.स_रखो = _fn पूर्ण,
# include "mem-memset-x86-64-asm-def.h"
# undef MEMSET_FN
#पूर्ण_अगर

	अणु .name = शून्य, पूर्ण
पूर्ण;

पूर्णांक bench_mem_स_रखो(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा bench_mem_info info = अणु
		.functions		= स_रखो_functions,
		.करो_cycles		= करो_स_रखो_cycles,
		.करो_समय_लोofday	= करो_स_रखो_समय_लोofday,
		.usage			= bench_mem_स_रखो_usage,
	पूर्ण;

	वापस bench_mem_common(argc, argv, &info);
पूर्ण
