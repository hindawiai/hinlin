<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hook पूर्णांकo 'openat' syscall entry tracepoपूर्णांक
 *
 * Test it with:
 *
 * perf trace -e tools/perf/examples/bpf/sys_enter_खोलोat.c cat /etc/passwd > /dev/null
 *
 * It'll catch some खोलोat syscalls related to the dynamic linked and
 * the last one should be the one क्रम '/etc/passwd'.
 *
 * The syscall_enter_खोलोat_args can be used to get the syscall fields
 * and use them क्रम filtering calls, i.e. use in expressions क्रम
 * the वापस value.
 */

#समावेश <bpf/bpf.h>

काष्ठा syscall_enter_खोलोat_args अणु
	अचिन्हित दीर्घ दीर्घ unused;
	दीर्घ		   syscall_nr;
	दीर्घ		   dfd;
	अक्षर		   *filename_ptr;
	दीर्घ		   flags;
	दीर्घ		   mode;
पूर्ण;

पूर्णांक syscall_enter(खोलोat)(काष्ठा syscall_enter_खोलोat_args *args)
अणु
	वापस 1;
पूर्ण

license(GPL);
