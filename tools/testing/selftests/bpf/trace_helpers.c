<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <poll.h>
#समावेश <unistd.h>
#समावेश <linux/perf_event.h>
#समावेश <sys/mman.h>
#समावेश "trace_helpers.h"

#घोषणा DEBUGFS "/sys/kernel/debug/tracing/"

#घोषणा MAX_SYMS 300000
अटल काष्ठा ksym syms[MAX_SYMS];
अटल पूर्णांक sym_cnt;

अटल पूर्णांक ksym_cmp(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	वापस ((काष्ठा ksym *)p1)->addr - ((काष्ठा ksym *)p2)->addr;
पूर्ण

पूर्णांक load_kallsyms(व्योम)
अणु
	खाता *f = ख_खोलो("/proc/kallsyms", "r");
	अक्षर func[256], buf[256];
	अक्षर symbol;
	व्योम *addr;
	पूर्णांक i = 0;

	अगर (!f)
		वापस -ENOENT;

	जबतक (ख_माला_लो(buf, माप(buf), f)) अणु
		अगर (माला_पूछो(buf, "%p %c %s", &addr, &symbol, func) != 3)
			अवरोध;
		अगर (!addr)
			जारी;
		syms[i].addr = (दीर्घ) addr;
		syms[i].name = strdup(func);
		i++;
	पूर्ण
	ख_बंद(f);
	sym_cnt = i;
	क्विक(syms, sym_cnt, माप(काष्ठा ksym), ksym_cmp);
	वापस 0;
पूर्ण

काष्ठा ksym *ksym_search(दीर्घ key)
अणु
	पूर्णांक start = 0, end = sym_cnt;
	पूर्णांक result;

	/* kallsyms not loaded. वापस शून्य */
	अगर (sym_cnt <= 0)
		वापस शून्य;

	जबतक (start < end) अणु
		माप_प्रकार mid = start + (end - start) / 2;

		result = key - syms[mid].addr;
		अगर (result < 0)
			end = mid;
		अन्यथा अगर (result > 0)
			start = mid + 1;
		अन्यथा
			वापस &syms[mid];
	पूर्ण

	अगर (start >= 1 && syms[start - 1].addr < key &&
	    key < syms[start].addr)
		/* valid ksym */
		वापस &syms[start - 1];

	/* out of range. वापस _stext */
	वापस &syms[0];
पूर्ण

दीर्घ ksym_get_addr(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sym_cnt; i++) अणु
		अगर (म_भेद(syms[i].name, name) == 0)
			वापस syms[i].addr;
	पूर्ण

	वापस 0;
पूर्ण

/* खोलो kallsyms and पढ़ो symbol addresses on the fly. Without caching all symbols,
 * this is faster than load + find.
 */
पूर्णांक kallsyms_find(स्थिर अक्षर *sym, अचिन्हित दीर्घ दीर्घ *addr)
अणु
	अक्षर type, name[500];
	अचिन्हित दीर्घ दीर्घ value;
	पूर्णांक err = 0;
	खाता *f;

	f = ख_खोलो("/proc/kallsyms", "r");
	अगर (!f)
		वापस -EINVAL;

	जबतक (ख_पूछो(f, "%llx %c %499s%*[^\न]\न", &value, &type, name) > 0) अणु
		अगर (म_भेद(name, sym) == 0) अणु
			*addr = value;
			जाओ out;
		पूर्ण
	पूर्ण
	err = -ENOENT;

out:
	ख_बंद(f);
	वापस err;
पूर्ण

व्योम पढ़ो_trace_pipe(व्योम)
अणु
	पूर्णांक trace_fd;

	trace_fd = खोलो(DEBUGFS "trace_pipe", O_RDONLY, 0);
	अगर (trace_fd < 0)
		वापस;

	जबतक (1) अणु
		अटल अक्षर buf[4096];
		sमाप_प्रकार sz;

		sz = पढ़ो(trace_fd, buf, माप(buf) - 1);
		अगर (sz > 0) अणु
			buf[sz] = 0;
			माला_दो(buf);
		पूर्ण
	पूर्ण
पूर्ण
