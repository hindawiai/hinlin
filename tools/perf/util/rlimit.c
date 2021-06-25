<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1 */

#समावेश "util/debug.h"
#समावेश "util/rlimit.h"
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>

/*
 * Bump the memlock so that we can get bpf maps of a reasonable size,
 * like the ones used with 'perf trace' and with 'perf test bpf',
 * improve this to some specअगरic request अगर needed.
 */
व्योम rlimit__bump_memlock(व्योम)
अणु
	काष्ठा rlimit rlim;

	अगर (getrlimit(RLIMIT_MEMLOCK, &rlim) == 0) अणु
		rlim.rlim_cur *= 4;
		rlim.rlim_max *= 4;

		अगर (setrlimit(RLIMIT_MEMLOCK, &rlim) < 0) अणु
			rlim.rlim_cur /= 2;
			rlim.rlim_max /= 2;

			अगर (setrlimit(RLIMIT_MEMLOCK, &rlim) < 0)
				pr_debug("Couldn't bump rlimit(MEMLOCK), failures may take place when creating BPF maps, etc\n");
		पूर्ण
	पूर्ण
पूर्ण
