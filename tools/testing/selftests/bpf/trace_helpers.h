<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __TRACE_HELPER_H
#घोषणा __TRACE_HELPER_H

#समावेश <bpf/libbpf.h>

काष्ठा ksym अणु
	दीर्घ addr;
	अक्षर *name;
पूर्ण;

पूर्णांक load_kallsyms(व्योम);
काष्ठा ksym *ksym_search(दीर्घ key);
दीर्घ ksym_get_addr(स्थिर अक्षर *name);

/* खोलो kallsyms and find addresses on the fly, faster than load + search. */
पूर्णांक kallsyms_find(स्थिर अक्षर *sym, अचिन्हित दीर्घ दीर्घ *addr);

व्योम पढ़ो_trace_pipe(व्योम);

#पूर्ण_अगर
