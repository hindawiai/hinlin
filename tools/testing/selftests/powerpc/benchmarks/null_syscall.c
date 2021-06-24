<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Test null syscall perक्रमmance
 *
 * Copyright (C) 2009-2015 Anton Blanअक्षरd, IBM
 */

#घोषणा NR_LOOPS 10000000

#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <समय.स>
#समावेश <sys/types.h>
#समावेश <sys/समय.स>
#समावेश <संकेत.स>

अटल अस्थिर पूर्णांक soak_करोne;
अचिन्हित दीर्घ दीर्घ घड़ी_frequency;
अचिन्हित दीर्घ दीर्घ समयbase_frequency;
द्विगुन समयbase_multiplier;

अटल अंतरभूत अचिन्हित दीर्घ mftb(व्योम)
अणु
	अचिन्हित दीर्घ low;

	यंत्र अस्थिर("mftb %0" : "=r" (low));

	वापस low;
पूर्ण

अटल व्योम sigalrm_handler(पूर्णांक unused)
अणु
	soak_करोne = 1;
पूर्ण

/*
 * Use a समयr instead of busy looping on घड़ी_समय_लो() so we करोn't
 * pollute profiles with glibc and VDSO hits.
 */
अटल व्योम cpu_soak_usecs(अचिन्हित दीर्घ usecs)
अणु
	काष्ठा iसमयrval val;

	स_रखो(&val, 0, माप(val));
	val.it_value.tv_usec = usecs;

	संकेत(SIGALRM, sigalrm_handler);
	setiसमयr(ITIMER_REAL, &val, शून्य);

	जबतक (1) अणु
		अगर (soak_करोne)
			अवरोध;
	पूर्ण

	संकेत(SIGALRM, संक_पूर्व);
पूर्ण

/*
 * This only works with recent kernels where cpufreq modअगरies
 * /proc/cpuinfo dynamically.
 */
अटल व्योम get_proc_frequency(व्योम)
अणु
	खाता *f;
	अक्षर line[128];
	अक्षर *p, *end;
	अचिन्हित दीर्घ v;
	द्विगुन d;
	अक्षर *override;

	/* Try to get out of low घातer/low frequency mode */
	cpu_soak_usecs(0.25 * 1000000);

	f = ख_खोलो("/proc/cpuinfo", "r");
	अगर (f == शून्य)
		वापस;

	समयbase_frequency = 0;

	जबतक (ख_माला_लो(line, माप(line), f) != शून्य) अणु
		अगर (म_भेदन(line, "timebase", 8) == 0) अणु
			p = म_अक्षर(line, ':');
			अगर (p != शून्य) अणु
				v = म_से_अदीर्घl(p + 1, &end, 0);
				अगर (end != p + 1)
					समयbase_frequency = v;
			पूर्ण
		पूर्ण

		अगर (((म_भेदन(line, "clock", 5) == 0) ||
		     (म_भेदन(line, "cpu MHz", 7) == 0))) अणु
			p = म_अक्षर(line, ':');
			अगर (p != शून्य) अणु
				d = म_से_भग्न(p + 1, &end);
				अगर (end != p + 1) अणु
					/* Find fastest घड़ी frequency */
					अगर ((d * 1000000ULL) > घड़ी_frequency)
						घड़ी_frequency = d * 1000000ULL;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	ख_बंद(f);

	override = दो_पर्या("FREQUENCY");
	अगर (override)
		घड़ी_frequency = म_से_अदीर्घl(override, शून्य, 10);

	अगर (समयbase_frequency)
		समयbase_multiplier = (द्विगुन)घड़ी_frequency
					/ समयbase_frequency;
	अन्यथा
		समयbase_multiplier = 1;
पूर्ण

अटल व्योम करो_null_syscall(अचिन्हित दीर्घ nr)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < nr; i++)
		getppid();
पूर्ण

#घोषणा TIME(A, STR) \

पूर्णांक मुख्य(व्योम)
अणु
	अचिन्हित दीर्घ tb_start, tb_now;
	काष्ठा बारpec tv_start, tv_now;
	अचिन्हित दीर्घ दीर्घ elapsed_ns, elapsed_tb;

	get_proc_frequency();

	घड़ी_समय_लो(CLOCK_MONOTONIC, &tv_start);
	tb_start = mftb();

	करो_null_syscall(NR_LOOPS);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &tv_now);
	tb_now = mftb();

	elapsed_ns = (tv_now.tv_sec - tv_start.tv_sec) * 1000000000ULL +
			(tv_now.tv_nsec - tv_start.tv_nsec);
	elapsed_tb = tb_now - tb_start;

	म_लिखो("%10.2f ns %10.2f cycles\n", (भग्न)elapsed_ns / NR_LOOPS,
			(भग्न)elapsed_tb * समयbase_multiplier / NR_LOOPS);

	वापस 0;
पूर्ण
