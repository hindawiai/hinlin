<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_SYS_H
#घोषणा _PERF_SYS_H

#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sys/syscall.h>
#समावेश <linux/compiler.h>

काष्ठा perf_event_attr;

अटल अंतरभूत पूर्णांक
sys_perf_event_खोलो(काष्ठा perf_event_attr *attr,
		      pid_t pid, पूर्णांक cpu, पूर्णांक group_fd,
		      अचिन्हित दीर्घ flags)
अणु
	वापस syscall(__NR_perf_event_खोलो, attr, pid, cpu,
		       group_fd, flags);
पूर्ण

#पूर्ण_अगर /* _PERF_SYS_H */
