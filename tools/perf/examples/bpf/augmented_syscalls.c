<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Augment syscalls with the contents of the poपूर्णांकer arguments.
 *
 * Test it with:
 *
 * perf trace -e tools/perf/examples/bpf/augmented_syscalls.c cat /etc/passwd > /dev/null
 *
 * It'll catch some खोलोat syscalls related to the dynamic linked and
 * the last one should be the one क्रम '/etc/passwd'.
 *
 * This matches what is marshalled पूर्णांकo the raw_syscall:sys_enter payload
 * expected by the 'perf trace' beautअगरiers, and can be used by them, that will
 * check अगर perf_sample->raw_data is more than what is expected क्रम each
 * syscalls:sys_अणुenter,निकासपूर्ण_SYSCALL tracepoपूर्णांक, uing the extra data as the
 * contents of poपूर्णांकer arguments.
 */

#समावेश <मानकपन.स>
#समावेश <linux/socket.h>

/* bpf-output associated map */
bpf_map(__augmented_syscalls__, PERF_EVENT_ARRAY, पूर्णांक, u32, __NR_CPUS__);

काष्ठा syscall_निकास_args अणु
	अचिन्हित दीर्घ दीर्घ common_tp_fields;
	दीर्घ		   syscall_nr;
	दीर्घ		   ret;
पूर्ण;

काष्ठा augmented_filename अणु
	अचिन्हित पूर्णांक	size;
	पूर्णांक		reserved;
	अक्षर		value[256];
पूर्ण;

#घोषणा augmented_filename_syscall(syscall)							\
काष्ठा augmented_enter_##syscall##_args अणु			 				\
	काष्ठा syscall_enter_##syscall##_args	args;				 		\
	काष्ठा augmented_filename		filename;				 	\
पूर्ण;												\
पूर्णांक syscall_enter(syscall)(काष्ठा syscall_enter_##syscall##_args *args)				\
अणु												\
	काष्ठा augmented_enter_##syscall##_args augmented_args = अणु .filename.reserved = 0, पूर्ण; 	\
	अचिन्हित पूर्णांक len = माप(augmented_args);						\
	probe_पढ़ो(&augmented_args.args, माप(augmented_args.args), args);			\
	augmented_args.filename.size = probe_पढ़ो_str(&augmented_args.filename.value, 		\
						      माप(augmented_args.filename.value), 	\
						      args->filename_ptr); 			\
	अगर (augmented_args.filename.size < माप(augmented_args.filename.value)) अणु		\
		len -= माप(augmented_args.filename.value) - augmented_args.filename.size;	\
		len &= माप(augmented_args.filename.value) - 1;				\
	पूर्ण											\
	/* If perf_event_output fails, वापस non-zero so that it माला_लो recorded unaugmented */	\
	वापस perf_event_output(args, &__augmented_syscalls__, BPF_F_CURRENT_CPU, 		\
				 &augmented_args, len);						\
पूर्ण												\
पूर्णांक syscall_निकास(syscall)(काष्ठा syscall_निकास_args *args)					\
अणु												\
       वापस 1; /* 0 as soon as we start copying data वापसed by the kernel, e.g. 'read' */	\
पूर्ण

काष्ठा syscall_enter_खोलोat_args अणु
	अचिन्हित दीर्घ दीर्घ common_tp_fields;
	दीर्घ		   syscall_nr;
	दीर्घ		   dfd;
	अक्षर		   *filename_ptr;
	दीर्घ		   flags;
	दीर्घ		   mode;
पूर्ण;

augmented_filename_syscall(खोलोat);

काष्ठा syscall_enter_खोलो_args अणु
	अचिन्हित दीर्घ दीर्घ common_tp_fields;
	दीर्घ		   syscall_nr;
	अक्षर		   *filename_ptr;
	दीर्घ		   flags;
	दीर्घ		   mode;
पूर्ण;

augmented_filename_syscall(खोलो);

काष्ठा syscall_enter_inotअगरy_add_watch_args अणु
	अचिन्हित दीर्घ दीर्घ common_tp_fields;
	दीर्घ		   syscall_nr;
	दीर्घ		   fd;
	अक्षर		   *filename_ptr;
	दीर्घ		   mask;
पूर्ण;

augmented_filename_syscall(inotअगरy_add_watch);

काष्ठा statbuf;

काष्ठा syscall_enter_newstat_args अणु
	अचिन्हित दीर्घ दीर्घ common_tp_fields;
	दीर्घ		   syscall_nr;
	अक्षर		   *filename_ptr;
	काष्ठा stat	   *statbuf;
पूर्ण;

augmented_filename_syscall(newstat);

#अगर_अघोषित _K_SS_MAXSIZE
#घोषणा _K_SS_MAXSIZE 128
#पूर्ण_अगर

#घोषणा augmented_sockaddr_syscall(syscall)						\
काष्ठा augmented_enter_##syscall##_args अणु			 				\
	काष्ठा syscall_enter_##syscall##_args	args;				 		\
	काष्ठा sockaddr_storage			addr;						\
पूर्ण;												\
पूर्णांक syscall_enter(syscall)(काष्ठा syscall_enter_##syscall##_args *args)				\
अणु												\
	काष्ठा augmented_enter_##syscall##_args augmented_args;				 	\
	अचिन्हित दीर्घ addrlen = माप(augmented_args.addr);					\
	probe_पढ़ो(&augmented_args.args, माप(augmented_args.args), args);			\
/* FIXME_CLANG_OPTIMIZATION_THAT_ACCESSES_USER_CONTROLLED_ADDRLEN_DESPITE_THIS_CHECK */		\
/*	अगर (addrlen > augmented_args.args.addrlen)				     */		\
/*		addrlen = augmented_args.args.addrlen;				     */		\
/*										     */		\
	probe_पढ़ो(&augmented_args.addr, addrlen, args->addr_ptr); 				\
	/* If perf_event_output fails, वापस non-zero so that it माला_लो recorded unaugmented */	\
	वापस perf_event_output(args, &__augmented_syscalls__, BPF_F_CURRENT_CPU, 		\
				 &augmented_args, 						\
				माप(augmented_args) - माप(augmented_args.addr) + addrlen);\
पूर्ण												\
पूर्णांक syscall_निकास(syscall)(काष्ठा syscall_निकास_args *args)					\
अणु												\
       वापस 1; /* 0 as soon as we start copying data वापसed by the kernel, e.g. 'read' */	\
पूर्ण

काष्ठा sockaddr;

काष्ठा syscall_enter_bind_args अणु
	अचिन्हित दीर्घ दीर्घ common_tp_fields;
	दीर्घ		   syscall_nr;
	दीर्घ		   fd;
	काष्ठा sockaddr	   *addr_ptr;
	अचिन्हित दीर्घ	   addrlen;
पूर्ण;

augmented_sockaddr_syscall(bind);

काष्ठा syscall_enter_connect_args अणु
	अचिन्हित दीर्घ दीर्घ common_tp_fields;
	दीर्घ		   syscall_nr;
	दीर्घ		   fd;
	काष्ठा sockaddr	   *addr_ptr;
	अचिन्हित दीर्घ	   addrlen;
पूर्ण;

augmented_sockaddr_syscall(connect);

काष्ठा syscall_enter_sendto_args अणु
	अचिन्हित दीर्घ दीर्घ common_tp_fields;
	दीर्घ		   syscall_nr;
	दीर्घ		   fd;
	व्योम		   *buff;
	दीर्घ		   len;
	अचिन्हित दीर्घ	   flags;
	काष्ठा sockaddr	   *addr_ptr;
	दीर्घ		   addr_len;
पूर्ण;

augmented_sockaddr_syscall(sendto);

license(GPL);
