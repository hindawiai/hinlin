<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2013, Michael Ellerman, IBM Corp.
 */

#घोषणा _GNU_SOURCE
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <sys/ioctl.h>

#समावेश "event.h"


पूर्णांक perf_event_खोलो(काष्ठा perf_event_attr *attr, pid_t pid, पूर्णांक cpu,
		पूर्णांक group_fd, अचिन्हित दीर्घ flags)
अणु
	वापस syscall(__NR_perf_event_खोलो, attr, pid, cpu,
			   group_fd, flags);
पूर्ण

व्योम event_init_opts(काष्ठा event *e, u64 config, पूर्णांक type, अक्षर *name)
अणु
	स_रखो(e, 0, माप(*e));

	e->name = name;

	e->attr.type = type;
	e->attr.config = config;
	e->attr.size = माप(e->attr);
	/* This has to match the काष्ठाure layout in the header */
	e->attr.पढ़ो_क्रमmat = PERF_FORMAT_TOTAL_TIME_ENABLED | \
				  PERF_FORMAT_TOTAL_TIME_RUNNING;
पूर्ण

व्योम event_init_named(काष्ठा event *e, u64 config, अक्षर *name)
अणु
	event_init_opts(e, config, PERF_TYPE_RAW, name);
पूर्ण

व्योम event_init(काष्ठा event *e, u64 config)
अणु
	event_init_opts(e, config, PERF_TYPE_RAW, "event");
पूर्ण

#घोषणा PERF_CURRENT_PID	0
#घोषणा PERF_NO_PID		-1
#घोषणा PERF_NO_CPU		-1
#घोषणा PERF_NO_GROUP		-1

पूर्णांक event_खोलो_with_options(काष्ठा event *e, pid_t pid, पूर्णांक cpu, पूर्णांक group_fd)
अणु
	e->fd = perf_event_खोलो(&e->attr, pid, cpu, group_fd, 0);
	अगर (e->fd == -1) अणु
		लिखो_त्रुटि("perf_event_open");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक event_खोलो_with_group(काष्ठा event *e, पूर्णांक group_fd)
अणु
	वापस event_खोलो_with_options(e, PERF_CURRENT_PID, PERF_NO_CPU, group_fd);
पूर्ण

पूर्णांक event_खोलो_with_pid(काष्ठा event *e, pid_t pid)
अणु
	वापस event_खोलो_with_options(e, pid, PERF_NO_CPU, PERF_NO_GROUP);
पूर्ण

पूर्णांक event_खोलो_with_cpu(काष्ठा event *e, पूर्णांक cpu)
अणु
	वापस event_खोलो_with_options(e, PERF_NO_PID, cpu, PERF_NO_GROUP);
पूर्ण

पूर्णांक event_खोलो(काष्ठा event *e)
अणु
	वापस event_खोलो_with_options(e, PERF_CURRENT_PID, PERF_NO_CPU, PERF_NO_GROUP);
पूर्ण

व्योम event_बंद(काष्ठा event *e)
अणु
	बंद(e->fd);
पूर्ण

पूर्णांक event_enable(काष्ठा event *e)
अणु
	वापस ioctl(e->fd, PERF_EVENT_IOC_ENABLE);
पूर्ण

पूर्णांक event_disable(काष्ठा event *e)
अणु
	वापस ioctl(e->fd, PERF_EVENT_IOC_DISABLE);
पूर्ण

पूर्णांक event_reset(काष्ठा event *e)
अणु
	वापस ioctl(e->fd, PERF_EVENT_IOC_RESET);
पूर्ण

पूर्णांक event_पढ़ो(काष्ठा event *e)
अणु
	पूर्णांक rc;

	rc = पढ़ो(e->fd, &e->result, माप(e->result));
	अगर (rc != माप(e->result)) अणु
		ख_लिखो(मानक_त्रुटि, "read error on event %p!\n", e);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम event_report_justअगरied(काष्ठा event *e, पूर्णांक name_width, पूर्णांक result_width)
अणु
	म_लिखो("%*s: result %*llu ", name_width, e->name, result_width,
	       e->result.value);

	अगर (e->result.running == e->result.enabled)
		म_लिखो("running/enabled %llu\n", e->result.running);
	अन्यथा
		म_लिखो("running %llu enabled %llu\n", e->result.running,
			e->result.enabled);
पूर्ण

व्योम event_report(काष्ठा event *e)
अणु
	event_report_justअगरied(e, 0, 0);
पूर्ण
