<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <गणित.स>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <sys/ब_समय.स>
#समावेश <sched.h>
#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <समय.स>
#समावेश "../kselftest.h"

#घोषणा MSEC_PER_SEC	1000L
#घोषणा NSEC_PER_MSEC	1000000L

व्योम usage(अक्षर *name) अणु
	म_लिखो ("Usage: %s cpunum\n", name);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv) अणु
	अचिन्हित पूर्णांक i, cpu, fd;
	अक्षर msr_file_name[64];
	दीर्घ दीर्घ tsc, old_tsc, new_tsc;
	दीर्घ दीर्घ aperf, old_aperf, new_aperf;
	दीर्घ दीर्घ mperf, old_mperf, new_mperf;
	काष्ठा बारpec beक्रमe, after;
	दीर्घ दीर्घ पूर्णांक start, finish, total;
	cpu_set_t cpuset;

	अगर (argc != 2) अणु
		usage(argv[0]);
		वापस 1;
	पूर्ण

	त्रुटि_सं = 0;
	cpu = म_से_दीर्घ(argv[1], (अक्षर **) शून्य, 10);

	अगर (त्रुटि_सं) अणु
		usage(argv[0]);
		वापस 1;
	पूर्ण

	प्र_लिखो(msr_file_name, "/dev/cpu/%d/msr", cpu);
	fd = खोलो(msr_file_name, O_RDONLY);

	अगर (fd == -1) अणु
		म_लिखो("/dev/cpu/%d/msr: %s\n", cpu, म_त्रुटि(त्रुटि_सं));
		वापस KSFT_SKIP;
	पूर्ण

	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);

	अगर (sched_setaffinity(0, माप(cpu_set_t), &cpuset)) अणु
		लिखो_त्रुटि("Failed to set cpu affinity");
		वापस 1;
	पूर्ण

	अगर (घड़ी_समय_लो(CLOCK_MONOTONIC, &beक्रमe) < 0) अणु
		लिखो_त्रुटि("clock_gettime");
		वापस 1;
	पूर्ण
	pपढ़ो(fd, &old_tsc,  माप(old_tsc), 0x10);
	pपढ़ो(fd, &old_aperf,  माप(old_mperf), 0xe7);
	pपढ़ो(fd, &old_mperf,  माप(old_aperf), 0xe8);

	क्रम (i=0; i<0x8fffffff; i++) अणु
		वर्ग_मूल(i);
	पूर्ण

	अगर (घड़ी_समय_लो(CLOCK_MONOTONIC, &after) < 0) अणु
		लिखो_त्रुटि("clock_gettime");
		वापस 1;
	पूर्ण
	pपढ़ो(fd, &new_tsc,  माप(new_tsc), 0x10);
	pपढ़ो(fd, &new_aperf,  माप(new_mperf), 0xe7);
	pपढ़ो(fd, &new_mperf,  माप(new_aperf), 0xe8);

	tsc = new_tsc-old_tsc;
	aperf = new_aperf-old_aperf;
	mperf = new_mperf-old_mperf;

	start = beक्रमe.tv_sec*MSEC_PER_SEC + beक्रमe.tv_nsec/NSEC_PER_MSEC;
	finish = after.tv_sec*MSEC_PER_SEC + after.tv_nsec/NSEC_PER_MSEC;
	total = finish - start;

	म_लिखो("runTime: %4.2f\n", 1.0*total/MSEC_PER_SEC);
	म_लिखो("freq: %7.0f\n", tsc / (1.0*aperf / (1.0 * mperf)) / total);
	वापस 0;
पूर्ण
