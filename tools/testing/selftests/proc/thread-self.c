<शैली गुरु>
/*
 * Copyright तऊ 2018 Alexey Dobriyan <aकरोbriyan@gmail.com>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
// Test that /proc/thपढ़ो-self gives correct TGID/PID.
#अघोषित न_संशोधन
#समावेश <निश्चित.स>
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/mman.h>
#समावेश <sys/रुको.h>

#समावेश "proc.h"

पूर्णांक f(व्योम *arg)
अणु
	अक्षर buf1[64], buf2[64];
	pid_t pid, tid;
	sमाप_प्रकार rv;

	pid = sys_getpid();
	tid = sys_gettid();
	snम_लिखो(buf1, माप(buf1), "%u/task/%u", pid, tid);

	rv = पढ़ोlink("/proc/thread-self", buf2, माप(buf2));
	निश्चित(rv == म_माप(buf1));
	buf2[rv] = '\0';
	निश्चित(streq(buf1, buf2));

	अगर (arg)
		निकास(0);
	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	स्थिर पूर्णांक PAGE_SIZE = sysconf(_SC_PAGESIZE);
	pid_t pid;
	व्योम *stack;

	/* मुख्य thपढ़ो */
	f((व्योम *)0);

	stack = mmap(शून्य, 2 * PAGE_SIZE, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	निश्चित(stack != MAP_FAILED);
	/* side thपढ़ो */
	pid = clone(f, stack + PAGE_SIZE, CLONE_THREAD|CLONE_SIGHAND|CLONE_VM, (व्योम *)1);
	निश्चित(pid > 0);
	छोड़ो();

	वापस 0;
पूर्ण
