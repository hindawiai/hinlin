<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Augment the filename syscalls with the contents of the filename poपूर्णांकer argument
 * filtering only those that करो not start with /etc/.
 *
 * Test it with:
 *
 * perf trace -e tools/perf/examples/bpf/augmented_syscalls.c cat /etc/passwd > /dev/null
 *
 * It'll catch some खोलोat syscalls related to the dynamic linked and
 * the last one should be the one क्रम '/etc/passwd'.
 *
 * This matches what is marshalled पूर्णांकo the raw_syscall:sys_enter payload
 * expected by the 'perf trace' beautअगरiers, and can be used by them unmodअगरied,
 * which will be करोne as that feature is implemented in the next csets, क्रम now
 * it will appear in a dump करोne by the शेष tracepoपूर्णांक handler in 'perf trace',
 * that uses bpf_output__ख_लिखो() to just dump those contents, as करोne with
 * the bpf-output event associated with the __bpf_output__ map declared in
 * tools/perf/include/bpf/मानकपन.स.
 */

#समावेश <मानकपन.स>

/* bpf-output associated map */
bpf_map(__augmented_syscalls__, PERF_EVENT_ARRAY, पूर्णांक, u32, __NR_CPUS__);

काष्ठा augmented_filename अणु
	पूर्णांक	size;
	पूर्णांक	reserved;
	अक्षर	value[64];
पूर्ण;

#घोषणा augmented_filename_syscall_enter(syscall) 						\
काष्ठा augmented_enter_##syscall##_args अणु			 				\
	काष्ठा syscall_enter_##syscall##_args	args;				 		\
	काष्ठा augmented_filename		filename;				 	\
पूर्ण;												\
पूर्णांक syscall_enter(syscall)(काष्ठा syscall_enter_##syscall##_args *args)				\
अणु												\
	अक्षर etc[6] = "/etc/";									\
	काष्ठा augmented_enter_##syscall##_args augmented_args = अणु .filename.reserved = 0, पूर्ण; 	\
	probe_पढ़ो(&augmented_args.args, माप(augmented_args.args), args);			\
	augmented_args.filename.size = probe_पढ़ो_str(&augmented_args.filename.value, 		\
						      माप(augmented_args.filename.value), 	\
						      args->filename_ptr); 			\
	अगर (__builtin_स_भेद(augmented_args.filename.value, etc, 4) != 0)			\
		वापस 0;									\
	/* If perf_event_output fails, वापस non-zero so that it माला_लो recorded unaugmented */	\
	वापस perf_event_output(args, &__augmented_syscalls__, BPF_F_CURRENT_CPU, 		\
				 &augmented_args,						\
				 (माप(augmented_args) - माप(augmented_args.filename.value) + \
				 augmented_args.filename.size));				\
पूर्ण

काष्ठा syscall_enter_खोलोat_args अणु
	अचिन्हित दीर्घ दीर्घ common_tp_fields;
	दीर्घ		   syscall_nr;
	दीर्घ		   dfd;
	अक्षर		   *filename_ptr;
	दीर्घ		   flags;
	दीर्घ		   mode;
पूर्ण;

augmented_filename_syscall_enter(खोलोat);

काष्ठा syscall_enter_खोलो_args अणु
	अचिन्हित दीर्घ दीर्घ common_tp_fields;
	दीर्घ		   syscall_nr;
	अक्षर		   *filename_ptr;
	दीर्घ		   flags;
	दीर्घ		   mode;
पूर्ण;

augmented_filename_syscall_enter(खोलो);

license(GPL);
