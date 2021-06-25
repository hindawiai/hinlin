<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
    Description:

    . Disable strace like syscall tracing (--no-syscalls), or try tracing
      just some (-e *sleep).

    . Attach a filter function to a kernel function, वापसing when it should
      be considered, i.e. appear on the output.

    . Run it प्रणाली wide, so that any sleep of >= 5 seconds and < than 6
      seconds माला_लो caught.

    . Ask क्रम callgraphs using DWARF info, so that userspace can be unwound

    . While this is running, run something like "sleep 5s".

    . If we decide to add tv_nsec as well, then it becomes:

      पूर्णांक probe(hrसमयr_nanosleep, rqtp->tv_sec rqtp->tv_nsec)(व्योम *ctx, पूर्णांक err, दीर्घ sec, दीर्घ nsec)

      I.e. add where it comes from (rqtp->tv_nsec) and where it will be
      accessible in the function body (nsec)

    # perf trace --no-syscalls -e tools/perf/examples/bpf/5sec.c/call-graph=dwarf/
         0.000 perf_bpf_probe:func:(ffffffff9811b5f0) tv_sec=5
                                           hrसमयr_nanosleep ([kernel.kallsyms])
                                           __x64_sys_nanosleep ([kernel.kallsyms])
                                           करो_syscall_64 ([kernel.kallsyms])
                                           entry_SYSCALL_64 ([kernel.kallsyms])
                                           __GI___nanosleep (/usr/lib64/libc-2.26.so)
                                           rpl_nanosleep (/usr/bin/sleep)
                                           xnanosleep (/usr/bin/sleep)
                                           मुख्य (/usr/bin/sleep)
                                           __libc_start_मुख्य (/usr/lib64/libc-2.26.so)
                                           _start (/usr/bin/sleep)
    ^C#

   Copyright (C) 2018 Red Hat, Inc., Arnalकरो Carvalho de Melo <acme@redhat.com>
*/

#समावेश <bpf.h>

#घोषणा NSEC_PER_SEC	1000000000L

पूर्णांक probe(hrसमयr_nanosleep, rqtp)(व्योम *ctx, पूर्णांक err, दीर्घ दीर्घ sec)
अणु
	वापस sec / NSEC_PER_SEC == 5ULL;
पूर्ण

license(GPL);
