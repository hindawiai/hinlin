<शैली गुरु>
/* Copyright (c) 2015 PLUMgrid, http://plumgrid.com
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <linux/ptrace.h>
#समावेश <linux/version.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/seccomp.h>
#समावेश <uapi/linux/unistd.h>
#समावेश "syscall_nrs.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

#घोषणा PROG(F) SEC("kprobe/"__stringअगरy(F)) पूर्णांक bpf_func_##F

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_PROG_ARRAY);
	__uपूर्णांक(key_size, माप(u32));
	__uपूर्णांक(value_size, माप(u32));
#अगर_घोषित __mips__
	__uपूर्णांक(max_entries, 6000); /* MIPS n64 syscalls start at 5000 */
#अन्यथा
	__uपूर्णांक(max_entries, 1024);
#पूर्ण_अगर
पूर्ण progs SEC(".maps");

SEC("kprobe/__seccomp_filter")
पूर्णांक bpf_prog1(काष्ठा pt_regs *ctx)
अणु
	पूर्णांक sc_nr = (पूर्णांक)PT_REGS_PARM1(ctx);

	/* dispatch पूर्णांकo next BPF program depending on syscall number */
	bpf_tail_call(ctx, &progs, sc_nr);

	/* fall through -> unknown syscall */
	अगर (sc_nr >= __NR_getuid && sc_nr <= __NR_माला_लोid) अणु
		अक्षर fmt[] = "syscall=%d (one of get/set uid/pid/gid)\n";
		bpf_trace_prपूर्णांकk(fmt, माप(fmt), sc_nr);
	पूर्ण
	वापस 0;
पूर्ण

/* we jump here when syscall number == __NR_ग_लिखो */
PROG(SYS__NR_ग_लिखो)(काष्ठा pt_regs *ctx)
अणु
	काष्ठा seccomp_data sd;

	bpf_probe_पढ़ो_kernel(&sd, माप(sd), (व्योम *)PT_REGS_PARM2(ctx));
	अगर (sd.args[2] == 512) अणु
		अक्षर fmt[] = "write(fd=%d, buf=%p, size=%d)\n";
		bpf_trace_prपूर्णांकk(fmt, माप(fmt),
				 sd.args[0], sd.args[1], sd.args[2]);
	पूर्ण
	वापस 0;
पूर्ण

PROG(SYS__NR_पढ़ो)(काष्ठा pt_regs *ctx)
अणु
	काष्ठा seccomp_data sd;

	bpf_probe_पढ़ो_kernel(&sd, माप(sd), (व्योम *)PT_REGS_PARM2(ctx));
	अगर (sd.args[2] > 128 && sd.args[2] <= 1024) अणु
		अक्षर fmt[] = "read(fd=%d, buf=%p, size=%d)\n";
		bpf_trace_prपूर्णांकk(fmt, माप(fmt),
				 sd.args[0], sd.args[1], sd.args[2]);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित __NR_mmap2
PROG(SYS__NR_mmap2)(काष्ठा pt_regs *ctx)
अणु
	अक्षर fmt[] = "mmap2\n";

	bpf_trace_prपूर्णांकk(fmt, माप(fmt));
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित __NR_mmap
PROG(SYS__NR_mmap)(काष्ठा pt_regs *ctx)
अणु
	अक्षर fmt[] = "mmap\n";

	bpf_trace_prपूर्णांकk(fmt, माप(fmt));
	वापस 0;
पूर्ण
#पूर्ण_अगर

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
