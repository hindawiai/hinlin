<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIBLOCKDEP_LINUX_STACKTRACE_H_
#घोषणा _LIBLOCKDEP_LINUX_STACKTRACE_H_

#समावेश <execinfo.h>

काष्ठा stack_trace अणु
	अचिन्हित पूर्णांक nr_entries, max_entries;
	अचिन्हित दीर्घ *entries;
	पूर्णांक skip;
पूर्ण;

अटल अंतरभूत व्योम prपूर्णांक_stack_trace(काष्ठा stack_trace *trace, पूर्णांक spaces)
अणु
	backtrace_symbols_fd((व्योम **)trace->entries, trace->nr_entries, 1);
पूर्ण

#घोषणा save_stack_trace(trace)	\
	((trace)->nr_entries =	\
		backtrace((व्योम **)(trace)->entries, (trace)->max_entries))

अटल अंतरभूत पूर्णांक dump_stack(व्योम)
अणु
	व्योम *array[64];
	माप_प्रकार size;

	size = backtrace(array, 64);
	backtrace_symbols_fd(array, size, 1);

	वापस 0;
पूर्ण

#पूर्ण_अगर
