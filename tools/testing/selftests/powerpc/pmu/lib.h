<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#अगर_अघोषित __SELFTESTS_POWERPC_PMU_LIB_H
#घोषणा __SELFTESTS_POWERPC_PMU_LIB_H

#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>
#समावेश <unistd.h>

जोड़ pipe अणु
	काष्ठा अणु
		पूर्णांक पढ़ो_fd;
		पूर्णांक ग_लिखो_fd;
	पूर्ण;
	पूर्णांक fds[2];
पूर्ण;

बाह्य पूर्णांक bind_to_cpu(पूर्णांक cpu);
बाह्य पूर्णांक समाप्त_child_and_रुको(pid_t child_pid);
बाह्य पूर्णांक रुको_क्रम_child(pid_t child_pid);
बाह्य पूर्णांक sync_with_child(जोड़ pipe पढ़ो_pipe, जोड़ pipe ग_लिखो_pipe);
बाह्य पूर्णांक रुको_क्रम_parent(जोड़ pipe पढ़ो_pipe);
बाह्य पूर्णांक notअगरy_parent(जोड़ pipe ग_लिखो_pipe);
बाह्य पूर्णांक notअगरy_parent_of_error(जोड़ pipe ग_लिखो_pipe);
बाह्य pid_t eat_cpu(पूर्णांक (test_function)(व्योम));
बाह्य bool require_paranoia_below(पूर्णांक level);

काष्ठा addr_range अणु
	uपूर्णांक64_t first, last;
पूर्ण;

बाह्य काष्ठा addr_range libc, vdso;

पूर्णांक parse_proc_maps(व्योम);

#पूर्ण_अगर /* __SELFTESTS_POWERPC_PMU_LIB_H */
