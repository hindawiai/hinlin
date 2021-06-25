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
// Test that values in /proc/upसमय increment monotonically
// जबतक shअगरting across CPUs.
#अघोषित न_संशोधन
#समावेश <निश्चित.स>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>

#समावेश <मानक_निवेशt.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>

#समावेश "proc-uptime.h"

अटल अंतरभूत पूर्णांक sys_sched_getaffinity(pid_t pid, अचिन्हित पूर्णांक len, अचिन्हित दीर्घ *m)
अणु
	वापस syscall(SYS_sched_getaffinity, pid, len, m);
पूर्ण

अटल अंतरभूत पूर्णांक sys_sched_setaffinity(pid_t pid, अचिन्हित पूर्णांक len, अचिन्हित दीर्घ *m)
अणु
	वापस syscall(SYS_sched_setaffinity, pid, len, m);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित दीर्घ *m;
	अचिन्हित पूर्णांक cpu;
	uपूर्णांक64_t u0, u1, i0, i1;
	पूर्णांक fd;

	/* find out "nr_cpu_ids" */
	m = शून्य;
	len = 0;
	करो अणु
		len += माप(अचिन्हित दीर्घ);
		मुक्त(m);
		m = दो_स्मृति(len);
	पूर्ण जबतक (sys_sched_getaffinity(0, len, m) == -EINVAL);

	fd = खोलो("/proc/uptime", O_RDONLY);
	निश्चित(fd >= 0);

	proc_upसमय(fd, &u0, &i0);
	क्रम (cpu = 0; cpu < len * 8; cpu++) अणु
		स_रखो(m, 0, len);
		m[cpu / (8 * माप(अचिन्हित दीर्घ))] |= 1UL << (cpu % (8 * माप(अचिन्हित दीर्घ)));

		/* CPU might not exist, ignore error */
		sys_sched_setaffinity(0, len, m);

		proc_upसमय(fd, &u1, &i1);
		निश्चित(u1 >= u0);
		निश्चित(i1 >= i0);
		u0 = u1;
		i0 = i1;
	पूर्ण

	वापस 0;
पूर्ण
