<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#घोषणा _GNU_SOURCE	/* For CPU_ZERO etc. */

#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <समलाँघ.स>
#समावेश <मानककोष.स>
#समावेश <sys/रुको.h>

#समावेश "utils.h"
#समावेश "lib.h"


पूर्णांक bind_to_cpu(पूर्णांक cpu)
अणु
	cpu_set_t mask;

	म_लिखो("Binding to cpu %d\n", cpu);

	CPU_ZERO(&mask);
	CPU_SET(cpu, &mask);

	वापस sched_setaffinity(0, माप(mask), &mask);
पूर्ण

#घोषणा PARENT_TOKEN	0xAA
#घोषणा CHILD_TOKEN	0x55

पूर्णांक sync_with_child(जोड़ pipe पढ़ो_pipe, जोड़ pipe ग_लिखो_pipe)
अणु
	अक्षर c = PARENT_TOKEN;

	FAIL_IF(ग_लिखो(ग_लिखो_pipe.ग_लिखो_fd, &c, 1) != 1);
	FAIL_IF(पढ़ो(पढ़ो_pipe.पढ़ो_fd, &c, 1) != 1);
	अगर (c != CHILD_TOKEN) /* someबार expected */
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक रुको_क्रम_parent(जोड़ pipe पढ़ो_pipe)
अणु
	अक्षर c;

	FAIL_IF(पढ़ो(पढ़ो_pipe.पढ़ो_fd, &c, 1) != 1);
	FAIL_IF(c != PARENT_TOKEN);

	वापस 0;
पूर्ण

पूर्णांक notअगरy_parent(जोड़ pipe ग_लिखो_pipe)
अणु
	अक्षर c = CHILD_TOKEN;

	FAIL_IF(ग_लिखो(ग_लिखो_pipe.ग_लिखो_fd, &c, 1) != 1);

	वापस 0;
पूर्ण

पूर्णांक notअगरy_parent_of_error(जोड़ pipe ग_लिखो_pipe)
अणु
	अक्षर c = ~CHILD_TOKEN;

	FAIL_IF(ग_लिखो(ग_लिखो_pipe.ग_लिखो_fd, &c, 1) != 1);

	वापस 0;
पूर्ण

पूर्णांक रुको_क्रम_child(pid_t child_pid)
अणु
	पूर्णांक rc;

	अगर (रुकोpid(child_pid, &rc, 0) == -1) अणु
		लिखो_त्रुटि("waitpid");
		वापस 1;
	पूर्ण

	अगर (WIFEXITED(rc))
		rc = WEXITSTATUS(rc);
	अन्यथा
		rc = 1; /* Signal or other */

	वापस rc;
पूर्ण

पूर्णांक समाप्त_child_and_रुको(pid_t child_pid)
अणु
	समाप्त(child_pid, संक_इति);

	वापस रुको_क्रम_child(child_pid);
पूर्ण

अटल पूर्णांक eat_cpu_child(जोड़ pipe पढ़ो_pipe, जोड़ pipe ग_लिखो_pipe)
अणु
	अस्थिर पूर्णांक i = 0;

	/*
	 * We are just here to eat cpu and die. So make sure we can be समाप्तed,
	 * and also करोn't करो any custom संक_इति handling.
	 */
	संकेत(संक_इति, संक_पूर्व);

	notअगरy_parent(ग_लिखो_pipe);
	रुको_क्रम_parent(पढ़ो_pipe);

	/* Soak up cpu क्रमever */
	जबतक (1) i++;

	वापस 0;
पूर्ण

pid_t eat_cpu(पूर्णांक (test_function)(व्योम))
अणु
	जोड़ pipe पढ़ो_pipe, ग_लिखो_pipe;
	पूर्णांक cpu, rc;
	pid_t pid;

	cpu = pick_online_cpu();
	FAIL_IF(cpu < 0);
	FAIL_IF(bind_to_cpu(cpu));

	अगर (pipe(पढ़ो_pipe.fds) == -1)
		वापस -1;

	अगर (pipe(ग_लिखो_pipe.fds) == -1)
		वापस -1;

	pid = विभाजन();
	अगर (pid == 0)
		निकास(eat_cpu_child(ग_लिखो_pipe, पढ़ो_pipe));

	अगर (sync_with_child(पढ़ो_pipe, ग_लिखो_pipe)) अणु
		rc = -1;
		जाओ out;
	पूर्ण

	म_लिखो("main test running as pid %d\n", getpid());

	rc = test_function();
out:
	समाप्त(pid, SIGKILL);

	वापस rc;
पूर्ण

काष्ठा addr_range libc, vdso;

पूर्णांक parse_proc_maps(व्योम)
अणु
	अचिन्हित दीर्घ start, end;
	अक्षर execute, name[128];
	खाता *f;
	पूर्णांक rc;

	f = ख_खोलो("/proc/self/maps", "r");
	अगर (!f) अणु
		लिखो_त्रुटि("fopen");
		वापस -1;
	पूर्ण

	करो अणु
		/* This skips line with no executable which is what we want */
		rc = ख_पूछो(f, "%lx-%lx %*c%*c%c%*c %*x %*d:%*d %*d %127s\n",
			    &start, &end, &execute, name);
		अगर (rc <= 0)
			अवरोध;

		अगर (execute != 'x')
			जारी;

		अगर (म_माला(name, "libc")) अणु
			libc.first = start;
			libc.last = end - 1;
		पूर्ण अन्यथा अगर (म_माला(name, "[vdso]")) अणु
			vdso.first = start;
			vdso.last = end - 1;
		पूर्ण
	पूर्ण जबतक(1);

	ख_बंद(f);

	वापस 0;
पूर्ण

#घोषणा PARANOID_PATH	"/proc/sys/kernel/perf_event_paranoid"

bool require_paranoia_below(पूर्णांक level)
अणु
	दीर्घ current;
	अक्षर *end, buf[16];
	खाता *f;
	bool rc;

	rc = false;

	f = ख_खोलो(PARANOID_PATH, "r");
	अगर (!f) अणु
		लिखो_त्रुटि("fopen");
		जाओ out;
	पूर्ण

	अगर (!ख_माला_लो(buf, माप(buf), f)) अणु
		म_लिखो("Couldn't read " PARANOID_PATH "?\n");
		जाओ out_बंद;
	पूर्ण

	current = म_से_दीर्घ(buf, &end, 10);

	अगर (end == buf) अणु
		म_लिखो("Couldn't parse " PARANOID_PATH "?\n");
		जाओ out_बंद;
	पूर्ण

	अगर (current >= level)
		जाओ out_बंद;

	rc = true;
out_बंद:
	ख_बंद(f);
out:
	वापस rc;
पूर्ण

