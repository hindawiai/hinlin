<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2013, Michael Ellerman, IBM Corp.
 */

#अगर_अघोषित _SELFTESTS_POWERPC_PMU_EVENT_H
#घोषणा _SELFTESTS_POWERPC_PMU_EVENT_H

#समावेश <unistd.h>
#समावेश <linux/perf_event.h>

#समावेश "utils.h"


काष्ठा event अणु
	काष्ठा perf_event_attr attr;
	अक्षर *name;
	पूर्णांक fd;
	/* This must match the पढ़ो_क्रमmat we use */
	काष्ठा अणु
		u64 value;
		u64 running;
		u64 enabled;
	पूर्ण result;
पूर्ण;

व्योम event_init(काष्ठा event *e, u64 config);
व्योम event_init_named(काष्ठा event *e, u64 config, अक्षर *name);
व्योम event_init_opts(काष्ठा event *e, u64 config, पूर्णांक type, अक्षर *name);
पूर्णांक event_खोलो_with_options(काष्ठा event *e, pid_t pid, पूर्णांक cpu, पूर्णांक group_fd);
पूर्णांक event_खोलो_with_group(काष्ठा event *e, पूर्णांक group_fd);
पूर्णांक event_खोलो_with_pid(काष्ठा event *e, pid_t pid);
पूर्णांक event_खोलो_with_cpu(काष्ठा event *e, पूर्णांक cpu);
पूर्णांक event_खोलो(काष्ठा event *e);
व्योम event_बंद(काष्ठा event *e);
पूर्णांक event_enable(काष्ठा event *e);
पूर्णांक event_disable(काष्ठा event *e);
पूर्णांक event_reset(काष्ठा event *e);
पूर्णांक event_पढ़ो(काष्ठा event *e);
व्योम event_report_justअगरied(काष्ठा event *e, पूर्णांक name_width, पूर्णांक result_width);
व्योम event_report(काष्ठा event *e);

#पूर्ण_अगर /* _SELFTESTS_POWERPC_PMU_EVENT_H */
