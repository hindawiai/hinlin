<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Augment the raw_syscalls tracepoपूर्णांकs with the contents of the poपूर्णांकer arguments.
 *
 * Test it with:
 *
 * perf trace -e tools/perf/examples/bpf/augmented_raw_syscalls.c cat /etc/passwd > /dev/null
 *
 * This exactly matches what is marshalled पूर्णांकo the raw_syscall:sys_enter
 * payload expected by the 'perf trace' beautअगरiers.
 *
 * For now it just uses the existing tracepoपूर्णांक augmentation code in 'perf
 * trace', in the next csets we'll hook up these with the sys_enter/sys_निकास
 * code that will combine entry/निकास in a strace like way.
 */

#समावेश <unistd.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/socket.h>
#समावेश <pid_filter.h>

/* bpf-output associated map */
bpf_map(__augmented_syscalls__, PERF_EVENT_ARRAY, पूर्णांक, u32, __NR_CPUS__);

/*
 * string_args_len: one per syscall arg, 0 means not a string or करोn't copy it,
 * 		    PATH_MAX क्रम copying everything, any other value to limit
 * 		    it a la 'strace -s strsize'.
 */
काष्ठा syscall अणु
	bool	enabled;
	u16	string_args_len[6];
पूर्ण;

bpf_map(syscalls, ARRAY, पूर्णांक, काष्ठा syscall, 512);

/*
 * What to augment at entry?
 *
 * Poपूर्णांकer arg payloads (filenames, etc) passed from userspace to the kernel
 */
bpf_map(syscalls_sys_enter, PROG_ARRAY, u32, u32, 512);

/*
 * What to augment at निकास?
 *
 * Poपूर्णांकer arg payloads वापसed from the kernel (काष्ठा stat, etc) to userspace.
 */
bpf_map(syscalls_sys_निकास, PROG_ARRAY, u32, u32, 512);

काष्ठा syscall_enter_args अणु
	अचिन्हित दीर्घ दीर्घ common_tp_fields;
	दीर्घ		   syscall_nr;
	अचिन्हित दीर्घ	   args[6];
पूर्ण;

काष्ठा syscall_निकास_args अणु
	अचिन्हित दीर्घ दीर्घ common_tp_fields;
	दीर्घ		   syscall_nr;
	दीर्घ		   ret;
पूर्ण;

काष्ठा augmented_arg अणु
	अचिन्हित पूर्णांक	size;
	पूर्णांक		err;
	अक्षर		value[PATH_MAX];
पूर्ण;

pid_filter(pids_filtered);

काष्ठा augmented_args_payload अणु
       काष्ठा syscall_enter_args args;
       जोड़ अणु
		काष्ठा अणु
			काष्ठा augmented_arg arg, arg2;
		पूर्ण;
		काष्ठा sockaddr_storage saddr;
	पूर्ण;
पूर्ण;

// We need more पंचांगp space than the BPF stack can give us
bpf_map(augmented_args_पंचांगp, PERCPU_ARRAY, पूर्णांक, काष्ठा augmented_args_payload, 1);

अटल अंतरभूत काष्ठा augmented_args_payload *augmented_args_payload(व्योम)
अणु
	पूर्णांक key = 0;
	वापस bpf_map_lookup_elem(&augmented_args_पंचांगp, &key);
पूर्ण

अटल अंतरभूत पूर्णांक augmented__output(व्योम *ctx, काष्ठा augmented_args_payload *args, पूर्णांक len)
अणु
	/* If perf_event_output fails, वापस non-zero so that it माला_लो recorded unaugmented */
	वापस perf_event_output(ctx, &__augmented_syscalls__, BPF_F_CURRENT_CPU, args, len);
पूर्ण

अटल अंतरभूत
अचिन्हित पूर्णांक augmented_arg__पढ़ो_str(काष्ठा augmented_arg *augmented_arg, स्थिर व्योम *arg, अचिन्हित पूर्णांक arg_len)
अणु
	अचिन्हित पूर्णांक augmented_len = माप(*augmented_arg);
	पूर्णांक string_len = probe_पढ़ो_str(&augmented_arg->value, arg_len, arg);

	augmented_arg->size = augmented_arg->err = 0;
	/*
	 * probe_पढ़ो_str may वापस < 0, e.g. -EFAULT
	 * So we leave that in the augmented_arg->size that userspace will
	 */
	अगर (string_len > 0) अणु
		augmented_len -= माप(augmented_arg->value) - string_len;
		augmented_len &= माप(augmented_arg->value) - 1;
		augmented_arg->size = string_len;
	पूर्ण अन्यथा अणु
		/*
		 * So that username notice the error जबतक still being able
		 * to skip this augmented arg record
		 */
		augmented_arg->err = string_len;
		augmented_len = दुरत्व(काष्ठा augmented_arg, value);
	पूर्ण

	वापस augmented_len;
पूर्ण

SEC("!raw_syscalls:unaugmented")
पूर्णांक syscall_unaugmented(काष्ठा syscall_enter_args *args)
अणु
	वापस 1;
पूर्ण

/*
 * These will be tail_called from SEC("raw_syscalls:sys_enter"), so will find in
 * augmented_args_पंचांगp what was पढ़ो by that raw_syscalls:sys_enter and go
 * on from there, पढ़ोing the first syscall arg as a string, i.e. खोलो's
 * filename.
 */
SEC("!syscalls:sys_enter_connect")
पूर्णांक sys_enter_connect(काष्ठा syscall_enter_args *args)
अणु
	काष्ठा augmented_args_payload *augmented_args = augmented_args_payload();
	स्थिर व्योम *sockaddr_arg = (स्थिर व्योम *)args->args[1];
	अचिन्हित पूर्णांक socklen = args->args[2];
	अचिन्हित पूर्णांक len = माप(augmented_args->args);

        अगर (augmented_args == शून्य)
                वापस 1; /* Failure: करोn't filter */

	अगर (socklen > माप(augmented_args->saddr))
		socklen = माप(augmented_args->saddr);

	probe_पढ़ो(&augmented_args->saddr, socklen, sockaddr_arg);

	वापस augmented__output(args, augmented_args, len + socklen);
पूर्ण

SEC("!syscalls:sys_enter_sendto")
पूर्णांक sys_enter_sendto(काष्ठा syscall_enter_args *args)
अणु
	काष्ठा augmented_args_payload *augmented_args = augmented_args_payload();
	स्थिर व्योम *sockaddr_arg = (स्थिर व्योम *)args->args[4];
	अचिन्हित पूर्णांक socklen = args->args[5];
	अचिन्हित पूर्णांक len = माप(augmented_args->args);

        अगर (augmented_args == शून्य)
                वापस 1; /* Failure: करोn't filter */

	अगर (socklen > माप(augmented_args->saddr))
		socklen = माप(augmented_args->saddr);

	probe_पढ़ो(&augmented_args->saddr, socklen, sockaddr_arg);

	वापस augmented__output(args, augmented_args, len + socklen);
पूर्ण

SEC("!syscalls:sys_enter_open")
पूर्णांक sys_enter_खोलो(काष्ठा syscall_enter_args *args)
अणु
	काष्ठा augmented_args_payload *augmented_args = augmented_args_payload();
	स्थिर व्योम *filename_arg = (स्थिर व्योम *)args->args[0];
	अचिन्हित पूर्णांक len = माप(augmented_args->args);

        अगर (augmented_args == शून्य)
                वापस 1; /* Failure: करोn't filter */

	len += augmented_arg__पढ़ो_str(&augmented_args->arg, filename_arg, माप(augmented_args->arg.value));

	वापस augmented__output(args, augmented_args, len);
पूर्ण

SEC("!syscalls:sys_enter_openat")
पूर्णांक sys_enter_खोलोat(काष्ठा syscall_enter_args *args)
अणु
	काष्ठा augmented_args_payload *augmented_args = augmented_args_payload();
	स्थिर व्योम *filename_arg = (स्थिर व्योम *)args->args[1];
	अचिन्हित पूर्णांक len = माप(augmented_args->args);

        अगर (augmented_args == शून्य)
                वापस 1; /* Failure: करोn't filter */

	len += augmented_arg__पढ़ो_str(&augmented_args->arg, filename_arg, माप(augmented_args->arg.value));

	वापस augmented__output(args, augmented_args, len);
पूर्ण

SEC("!syscalls:sys_enter_rename")
पूर्णांक sys_enter_नाम(काष्ठा syscall_enter_args *args)
अणु
	काष्ठा augmented_args_payload *augmented_args = augmented_args_payload();
	स्थिर व्योम *oldpath_arg = (स्थिर व्योम *)args->args[0],
		   *newpath_arg = (स्थिर व्योम *)args->args[1];
	अचिन्हित पूर्णांक len = माप(augmented_args->args), oldpath_len;

        अगर (augmented_args == शून्य)
                वापस 1; /* Failure: करोn't filter */

	oldpath_len = augmented_arg__पढ़ो_str(&augmented_args->arg, oldpath_arg, माप(augmented_args->arg.value));
	len += oldpath_len + augmented_arg__पढ़ो_str((व्योम *)(&augmented_args->arg) + oldpath_len, newpath_arg, माप(augmented_args->arg.value));

	वापस augmented__output(args, augmented_args, len);
पूर्ण

SEC("!syscalls:sys_enter_renameat")
पूर्णांक sys_enter_नामat(काष्ठा syscall_enter_args *args)
अणु
	काष्ठा augmented_args_payload *augmented_args = augmented_args_payload();
	स्थिर व्योम *oldpath_arg = (स्थिर व्योम *)args->args[1],
		   *newpath_arg = (स्थिर व्योम *)args->args[3];
	अचिन्हित पूर्णांक len = माप(augmented_args->args), oldpath_len;

        अगर (augmented_args == शून्य)
                वापस 1; /* Failure: करोn't filter */

	oldpath_len = augmented_arg__पढ़ो_str(&augmented_args->arg, oldpath_arg, माप(augmented_args->arg.value));
	len += oldpath_len + augmented_arg__पढ़ो_str((व्योम *)(&augmented_args->arg) + oldpath_len, newpath_arg, माप(augmented_args->arg.value));

	वापस augmented__output(args, augmented_args, len);
पूर्ण

SEC("raw_syscalls:sys_enter")
पूर्णांक sys_enter(काष्ठा syscall_enter_args *args)
अणु
	काष्ठा augmented_args_payload *augmented_args;
	/*
	 * We start len, the amount of data that will be in the perf ring
	 * buffer, अगर this is not filtered out by one of pid_filter__has(),
	 * syscall->enabled, etc, with the non-augmented raw syscall payload,
	 * i.e. माप(augmented_args->args).
	 *
	 * We'll add to this as we add augmented syscalls right after that
	 * initial, non-augmented raw_syscalls:sys_enter payload.
	 */
	अचिन्हित पूर्णांक len = माप(augmented_args->args);
	काष्ठा syscall *syscall;

	अगर (pid_filter__has(&pids_filtered, getpid()))
		वापस 0;

	augmented_args = augmented_args_payload();
	अगर (augmented_args == शून्य)
		वापस 1;

	probe_पढ़ो(&augmented_args->args, माप(augmented_args->args), args);

	/*
	 * Jump to syscall specअगरic augmenter, even अगर the शेष one,
	 * "!raw_syscalls:unaugmented" that will just वापस 1 to वापस the
	 * unaugmented tracepoपूर्णांक payload.
	 */
	bpf_tail_call(args, &syscalls_sys_enter, augmented_args->args.syscall_nr);

	// If not found on the PROG_ARRAY syscalls map, then we're filtering it:
	वापस 0;
पूर्ण

SEC("raw_syscalls:sys_exit")
पूर्णांक sys_निकास(काष्ठा syscall_निकास_args *args)
अणु
	काष्ठा syscall_निकास_args निकास_args;

	अगर (pid_filter__has(&pids_filtered, getpid()))
		वापस 0;

	probe_पढ़ो(&निकास_args, माप(निकास_args), args);
	/*
	 * Jump to syscall specअगरic वापस augmenter, even अगर the शेष one,
	 * "!raw_syscalls:unaugmented" that will just वापस 1 to वापस the
	 * unaugmented tracepoपूर्णांक payload.
	 */
	bpf_tail_call(args, &syscalls_sys_निकास, निकास_args.syscall_nr);
	/*
	 * If not found on the PROG_ARRAY syscalls map, then we're filtering it:
	 */
	वापस 0;
पूर्ण

license(GPL);
