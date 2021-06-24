<शैली गुरु>
/*
 *
 * syscall.c
 *
 * syscall: Benchmark क्रम प्रणाली call perक्रमmance
 */
#समावेश "../perf.h"
#समावेश "../util/util.h"
#समावेश <subcmd/parse-options.h>
#समावेश "../builtin.h"
#समावेश "bench.h"

#समावेश <मानकपन.स>
#समावेश <sys/समय.स>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <unistd.h>
#समावेश <मानककोष.स>

#घोषणा LOOPS_DEFAULT 10000000
अटल	पूर्णांक loops = LOOPS_DEFAULT;

अटल स्थिर काष्ठा option options[] = अणु
	OPT_INTEGER('l', "loop",	&loops,		"Specify number of loops"),
	OPT_END()
पूर्ण;

अटल स्थिर अक्षर * स्थिर bench_syscall_usage[] = अणु
	"perf bench syscall <options>",
	शून्य
पूर्ण;

पूर्णांक bench_syscall_basic(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा समयval start, stop, dअगरf;
	अचिन्हित दीर्घ दीर्घ result_usec = 0;
	पूर्णांक i;

	argc = parse_options(argc, argv, options, bench_syscall_usage, 0);

	समय_लोofday(&start, शून्य);

	क्रम (i = 0; i < loops; i++)
		getppid();

	समय_लोofday(&stop, शून्य);
	समयrsub(&stop, &start, &dअगरf);

	चयन (bench_क्रमmat) अणु
	हाल BENCH_FORMAT_DEFAULT:
		म_लिखो("# Executed %'d getppid() calls\n", loops);

		result_usec = dअगरf.tv_sec * 1000000;
		result_usec += dअगरf.tv_usec;

		म_लिखो(" %14s: %lu.%03lu [sec]\n\n", "Total time",
		       (अचिन्हित दीर्घ) dअगरf.tv_sec,
		       (अचिन्हित दीर्घ) (dअगरf.tv_usec/1000));

		म_लिखो(" %14lf usecs/op\n",
		       (द्विगुन)result_usec / (द्विगुन)loops);
		म_लिखो(" %'14d ops/sec\n",
		       (पूर्णांक)((द्विगुन)loops /
			     ((द्विगुन)result_usec / (द्विगुन)1000000)));
		अवरोध;

	हाल BENCH_FORMAT_SIMPLE:
		म_लिखो("%lu.%03lu\n",
		       (अचिन्हित दीर्घ) dअगरf.tv_sec,
		       (अचिन्हित दीर्घ) (dअगरf.tv_usec / 1000));
		अवरोध;

	शेष:
		/* reaching here is something disaster */
		ख_लिखो(मानक_त्रुटि, "Unknown format:%d\n", bench_क्रमmat);
		निकास(1);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
