<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook

#समावेश <fcntl.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#समावेश <linux/filter.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश <bpf/bpf_endian.h>
#समावेश "bpf_rlimit.h"
#समावेश "bpf_util.h"
#समावेश "cgroup_helpers.h"

#घोषणा CG_PATH			"/foo"
#घोषणा MAX_INSNS		512
#घोषणा FIXUP_SYSCTL_VALUE	0

अक्षर bpf_log_buf[BPF_LOG_BUF_SIZE];

काष्ठा sysctl_test अणु
	स्थिर अक्षर *descr;
	माप_प्रकार fixup_value_insn;
	काष्ठा bpf_insn	insns[MAX_INSNS];
	स्थिर अक्षर *prog_file;
	क्रमागत bpf_attach_type attach_type;
	स्थिर अक्षर *sysctl;
	पूर्णांक खोलो_flags;
	पूर्णांक seek;
	स्थिर अक्षर *newval;
	स्थिर अक्षर *oldval;
	क्रमागत अणु
		LOAD_REJECT,
		ATTACH_REJECT,
		OP_EPERM,
		SUCCESS,
	पूर्ण result;
पूर्ण;

अटल काष्ठा sysctl_test tests[] = अणु
	अणु
		.descr = "sysctl wrong attach_type",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = 0,
		.sysctl = "kernel/ostype",
		.खोलो_flags = O_RDONLY,
		.result = ATTACH_REJECT,
	पूर्ण,
	अणु
		.descr = "sysctl:read allow all",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "kernel/ostype",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "sysctl:read deny all",
		.insns = अणु
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "kernel/ostype",
		.खोलो_flags = O_RDONLY,
		.result = OP_EPERM,
	पूर्ण,
	अणु
		.descr = "ctx:write sysctl:read read ok",
		.insns = अणु
			/* If (ग_लिखो) */
			BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sysctl, ग_लिखो)),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_7, 1, 2),

			/* वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_JMP_A(1),

			/* अन्यथा वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "kernel/ostype",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "ctx:write sysctl:write read ok",
		.insns = अणु
			/* If (ग_लिखो) */
			BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sysctl, ग_लिखो)),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_7, 1, 2),

			/* वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_JMP_A(1),

			/* अन्यथा वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "kernel/domainname",
		.खोलो_flags = O_WRONLY,
		.newval = "(none)", /* same as शेष, should fail anyway */
		.result = OP_EPERM,
	पूर्ण,
	अणु
		.descr = "ctx:write sysctl:write read ok narrow",
		.insns = अणु
			/* u64 w = (u16)ग_लिखो & 1; */
#अगर __BYTE_ORDER == __LITTLE_ENDIAN
			BPF_LDX_MEM(BPF_H, BPF_REG_7, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sysctl, ग_लिखो)),
#अन्यथा
			BPF_LDX_MEM(BPF_H, BPF_REG_7, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sysctl, ग_लिखो) + 2),
#पूर्ण_अगर
			BPF_ALU64_IMM(BPF_AND, BPF_REG_7, 1),
			/* वापस 1 - w; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_ALU64_REG(BPF_SUB, BPF_REG_0, BPF_REG_7),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "kernel/domainname",
		.खोलो_flags = O_WRONLY,
		.newval = "(none)", /* same as शेष, should fail anyway */
		.result = OP_EPERM,
	पूर्ण,
	अणु
		.descr = "ctx:write sysctl:read write reject",
		.insns = अणु
			/* ग_लिखो = X */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sysctl, ग_लिखो)),
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "kernel/ostype",
		.खोलो_flags = O_RDONLY,
		.result = LOAD_REJECT,
	पूर्ण,
	अणु
		.descr = "ctx:file_pos sysctl:read read ok",
		.insns = अणु
			/* If (file_pos == X) */
			BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sysctl, file_pos)),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_7, 3, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "kernel/ostype",
		.खोलो_flags = O_RDONLY,
		.seek = 3,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "ctx:file_pos sysctl:read read ok narrow",
		.insns = अणु
			/* If (file_pos == X) */
#अगर __BYTE_ORDER == __LITTLE_ENDIAN
			BPF_LDX_MEM(BPF_B, BPF_REG_7, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sysctl, file_pos)),
#अन्यथा
			BPF_LDX_MEM(BPF_B, BPF_REG_7, BPF_REG_1,
				    दुरत्व(काष्ठा bpf_sysctl, file_pos) + 3),
#पूर्ण_अगर
			BPF_JMP_IMM(BPF_JNE, BPF_REG_7, 4, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "kernel/ostype",
		.खोलो_flags = O_RDONLY,
		.seek = 4,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "ctx:file_pos sysctl:read write ok",
		.insns = अणु
			/* file_pos = X */
			BPF_MOV64_IMM(BPF_REG_0, 2),
			BPF_STX_MEM(BPF_W, BPF_REG_1, BPF_REG_0,
				    दुरत्व(काष्ठा bpf_sysctl, file_pos)),
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "kernel/ostype",
		.खोलो_flags = O_RDONLY,
		.oldval = "nux\n",
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "sysctl_get_name sysctl_value:base ok",
		.insns = अणु
			/* sysctl_get_name arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_name arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 8),

			/* sysctl_get_name arg4 (flags) */
			BPF_MOV64_IMM(BPF_REG_4, BPF_F_SYSCTL_BASE_NAME),

			/* sysctl_get_name(ctx, buf, buf_len, flags) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_name),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, माप("tcp_mem") - 1, 6),
			/*     buf == "tcp_mem\0") */
			BPF_LD_IMM64(BPF_REG_8,
				     bpf_be64_to_cpu(0x7463705f6d656d00ULL)),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/tcp_mem",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "sysctl_get_name sysctl_value:base E2BIG truncated",
		.insns = अणु
			/* sysctl_get_name arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_name arg3 (buf_len) too small */
			BPF_MOV64_IMM(BPF_REG_3, 7),

			/* sysctl_get_name arg4 (flags) */
			BPF_MOV64_IMM(BPF_REG_4, BPF_F_SYSCTL_BASE_NAME),

			/* sysctl_get_name(ctx, buf, buf_len, flags) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_name),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, -E2BIG, 6),

			/*     buf[0:7] == "tcp_me\0") */
			BPF_LD_IMM64(BPF_REG_8,
				     bpf_be64_to_cpu(0x7463705f6d650000ULL)),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/tcp_mem",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "sysctl_get_name sysctl:full ok",
		.insns = अणु
			/* sysctl_get_name arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -24),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 8),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 16),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_name arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 17),

			/* sysctl_get_name arg4 (flags) */
			BPF_MOV64_IMM(BPF_REG_4, 0),

			/* sysctl_get_name(ctx, buf, buf_len, flags) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_name),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 16, 14),

			/*     buf[0:8] == "net/ipv4" && */
			BPF_LD_IMM64(BPF_REG_8,
				     bpf_be64_to_cpu(0x6e65742f69707634ULL)),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 10),

			/*     buf[8:16] == "/tcp_mem" && */
			BPF_LD_IMM64(BPF_REG_8,
				     bpf_be64_to_cpu(0x2f7463705f6d656dULL)),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 8),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 6),

			/*     buf[16:24] == "\0") */
			BPF_LD_IMM64(BPF_REG_8, 0x0ULL),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 16),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/tcp_mem",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "sysctl_get_name sysctl:full E2BIG truncated",
		.insns = अणु
			/* sysctl_get_name arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -16),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 8),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_name arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 16),

			/* sysctl_get_name arg4 (flags) */
			BPF_MOV64_IMM(BPF_REG_4, 0),

			/* sysctl_get_name(ctx, buf, buf_len, flags) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_name),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, -E2BIG, 10),

			/*     buf[0:8] == "net/ipv4" && */
			BPF_LD_IMM64(BPF_REG_8,
				     bpf_be64_to_cpu(0x6e65742f69707634ULL)),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 6),

			/*     buf[8:16] == "/tcp_me\0") */
			BPF_LD_IMM64(BPF_REG_8,
				     bpf_be64_to_cpu(0x2f7463705f6d6500ULL)),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 8),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/tcp_mem",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "sysctl_get_name sysctl:full E2BIG truncated small",
		.insns = अणु
			/* sysctl_get_name arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_name arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 7),

			/* sysctl_get_name arg4 (flags) */
			BPF_MOV64_IMM(BPF_REG_4, 0),

			/* sysctl_get_name(ctx, buf, buf_len, flags) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_name),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, -E2BIG, 6),

			/*     buf[0:8] == "net/ip\0") */
			BPF_LD_IMM64(BPF_REG_8,
				     bpf_be64_to_cpu(0x6e65742f69700000ULL)),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/tcp_mem",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "sysctl_get_current_value sysctl:read ok, gt",
		.insns = अणु
			/* sysctl_get_current_value arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_current_value arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 8),

			/* sysctl_get_current_value(ctx, buf, buf_len) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_current_value),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 6, 6),

			/*     buf[0:6] == "Linux\n\0") */
			BPF_LD_IMM64(BPF_REG_8,
				     bpf_be64_to_cpu(0x4c696e75780a0000ULL)),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "kernel/ostype",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "sysctl_get_current_value sysctl:read ok, eq",
		.insns = अणु
			/* sysctl_get_current_value arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_B, BPF_REG_7, BPF_REG_0, 7),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_current_value arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 7),

			/* sysctl_get_current_value(ctx, buf, buf_len) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_current_value),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 6, 6),

			/*     buf[0:6] == "Linux\n\0") */
			BPF_LD_IMM64(BPF_REG_8,
				     bpf_be64_to_cpu(0x4c696e75780a0000ULL)),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "kernel/ostype",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "sysctl_get_current_value sysctl:read E2BIG truncated",
		.insns = अणु
			/* sysctl_get_current_value arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_H, BPF_REG_7, BPF_REG_0, 6),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_current_value arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 6),

			/* sysctl_get_current_value(ctx, buf, buf_len) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_current_value),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, -E2BIG, 6),

			/*     buf[0:6] == "Linux\0") */
			BPF_LD_IMM64(BPF_REG_8,
				     bpf_be64_to_cpu(0x4c696e7578000000ULL)),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "kernel/ostype",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "sysctl_get_current_value sysctl:read EINVAL",
		.insns = अणु
			/* sysctl_get_current_value arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_current_value arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 8),

			/* sysctl_get_current_value(ctx, buf, buf_len) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_current_value),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, -EINVAL, 4),

			/*     buf[0:8] is NUL-filled) */
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_9, 0, 2),

			/* वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_JMP_A(1),

			/* अन्यथा वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv6/conf/lo/stable_secret", /* -EIO */
		.खोलो_flags = O_RDONLY,
		.result = OP_EPERM,
	पूर्ण,
	अणु
		.descr = "sysctl_get_current_value sysctl:write ok",
		.fixup_value_insn = 6,
		.insns = अणु
			/* sysctl_get_current_value arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_current_value arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 8),

			/* sysctl_get_current_value(ctx, buf, buf_len) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_current_value),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 4, 6),

			/*     buf[0:4] == expected) */
			BPF_LD_IMM64(BPF_REG_8, FIXUP_SYSCTL_VALUE),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 2),

			/* वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_JMP_A(1),

			/* अन्यथा वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_WRONLY,
		.newval = "600", /* same as शेष, should fail anyway */
		.result = OP_EPERM,
	पूर्ण,
	अणु
		.descr = "sysctl_get_new_value sysctl:read EINVAL",
		.insns = अणु
			/* sysctl_get_new_value arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_new_value arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 8),

			/* sysctl_get_new_value(ctx, buf, buf_len) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_new_value),

			/* अगर (ret == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, -EINVAL, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/tcp_mem",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "sysctl_get_new_value sysctl:write ok",
		.insns = अणु
			/* sysctl_get_new_value arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_new_value arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 4),

			/* sysctl_get_new_value(ctx, buf, buf_len) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_new_value),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 3, 4),

			/*     buf[0:4] == "606\0") */
			BPF_LDX_MEM(BPF_W, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_9,
				    bpf_ntohl(0x36303600), 2),

			/* वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_JMP_A(1),

			/* अन्यथा वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_WRONLY,
		.newval = "606",
		.result = OP_EPERM,
	पूर्ण,
	अणु
		.descr = "sysctl_get_new_value sysctl:write ok long",
		.insns = अणु
			/* sysctl_get_new_value arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -24),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_new_value arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 24),

			/* sysctl_get_new_value(ctx, buf, buf_len) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_new_value),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 23, 14),

			/*     buf[0:8] == "3000000 " && */
			BPF_LD_IMM64(BPF_REG_8,
				     bpf_be64_to_cpu(0x3330303030303020ULL)),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 10),

			/*     buf[8:16] == "4000000 " && */
			BPF_LD_IMM64(BPF_REG_8,
				     bpf_be64_to_cpu(0x3430303030303020ULL)),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 8),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 6),

			/*     buf[16:24] == "6000000\0") */
			BPF_LD_IMM64(BPF_REG_8,
				     bpf_be64_to_cpu(0x3630303030303000ULL)),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 16),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 2),

			/* वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_JMP_A(1),

			/* अन्यथा वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/tcp_mem",
		.खोलो_flags = O_WRONLY,
		.newval = "3000000 4000000 6000000",
		.result = OP_EPERM,
	पूर्ण,
	अणु
		.descr = "sysctl_get_new_value sysctl:write E2BIG",
		.insns = अणु
			/* sysctl_get_new_value arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_STX_MEM(BPF_B, BPF_REG_7, BPF_REG_0, 3),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_get_new_value arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 3),

			/* sysctl_get_new_value(ctx, buf, buf_len) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_get_new_value),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, -E2BIG, 4),

			/*     buf[0:3] == "60\0") */
			BPF_LDX_MEM(BPF_W, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_9,
				    bpf_ntohl(0x36300000), 2),

			/* वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_JMP_A(1),

			/* अन्यथा वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_WRONLY,
		.newval = "606",
		.result = OP_EPERM,
	पूर्ण,
	अणु
		.descr = "sysctl_set_new_value sysctl:read EINVAL",
		.insns = अणु
			/* sysctl_set_new_value arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_IMM(BPF_REG_0,
				      bpf_ntohl(0x36303000)),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_set_new_value arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 3),

			/* sysctl_set_new_value(ctx, buf, buf_len) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_set_new_value),

			/* अगर (ret == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, -EINVAL, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		.descr = "sysctl_set_new_value sysctl:write ok",
		.fixup_value_insn = 2,
		.insns = अणु
			/* sysctl_set_new_value arg2 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_LD_IMM64(BPF_REG_0, FIXUP_SYSCTL_VALUE),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_2, BPF_REG_7),

			/* sysctl_set_new_value arg3 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_3, 3),

			/* sysctl_set_new_value(ctx, buf, buf_len) */
			BPF_EMIT_CALL(BPF_FUNC_sysctl_set_new_value),

			/* अगर (ret == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_WRONLY,
		.newval = "606",
		.result = SUCCESS,
	पूर्ण,
	अणु
		"bpf_strtoul one number string",
		.insns = अणु
			/* arg1 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_IMM(BPF_REG_0,
				      bpf_ntohl(0x36303000)),
			BPF_STX_MEM(BPF_W, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

			/* arg2 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_2, 4),

			/* arg3 (flags) */
			BPF_MOV64_IMM(BPF_REG_3, 0),

			/* arg4 (res) */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

			BPF_EMIT_CALL(BPF_FUNC_म_से_अदीर्घ),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 3, 4),
			/*     res == expected) */
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_9, 600, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		"bpf_strtoul multi number string",
		.insns = अणु
			/* arg1 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			/* "600 602\0" */
			BPF_LD_IMM64(BPF_REG_0,
				     bpf_be64_to_cpu(0x3630302036303200ULL)),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

			/* arg2 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_2, 8),

			/* arg3 (flags) */
			BPF_MOV64_IMM(BPF_REG_3, 0),

			/* arg4 (res) */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

			BPF_EMIT_CALL(BPF_FUNC_म_से_अदीर्घ),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 3, 18),
			/*     res == expected) */
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_9, 600, 16),

			/*     arg1 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_ALU64_REG(BPF_ADD, BPF_REG_7, BPF_REG_0),
			BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

			/*     arg2 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_2, 8),
			BPF_ALU64_REG(BPF_SUB, BPF_REG_2, BPF_REG_0),

			/*     arg3 (flags) */
			BPF_MOV64_IMM(BPF_REG_3, 0),

			/*     arg4 (res) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -16),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

			BPF_EMIT_CALL(BPF_FUNC_म_से_अदीर्घ),

			/*     अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 4, 4),
			/*         res == expected) */
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_9, 602, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/tcp_mem",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		"bpf_strtoul buf_len = 0, reject",
		.insns = अणु
			/* arg1 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_IMM(BPF_REG_0,
				      bpf_ntohl(0x36303000)),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

			/* arg2 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_2, 0),

			/* arg3 (flags) */
			BPF_MOV64_IMM(BPF_REG_3, 0),

			/* arg4 (res) */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

			BPF_EMIT_CALL(BPF_FUNC_म_से_अदीर्घ),

			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_RDONLY,
		.result = LOAD_REJECT,
	पूर्ण,
	अणु
		"bpf_strtoul supported base, ok",
		.insns = अणु
			/* arg1 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_IMM(BPF_REG_0,
				      bpf_ntohl(0x30373700)),
			BPF_STX_MEM(BPF_W, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

			/* arg2 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_2, 4),

			/* arg3 (flags) */
			BPF_MOV64_IMM(BPF_REG_3, 8),

			/* arg4 (res) */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

			BPF_EMIT_CALL(BPF_FUNC_म_से_अदीर्घ),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 3, 4),
			/*     res == expected) */
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_9, 63, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		"bpf_strtoul unsupported base, EINVAL",
		.insns = अणु
			/* arg1 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_IMM(BPF_REG_0,
				      bpf_ntohl(0x36303000)),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

			/* arg2 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_2, 4),

			/* arg3 (flags) */
			BPF_MOV64_IMM(BPF_REG_3, 3),

			/* arg4 (res) */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

			BPF_EMIT_CALL(BPF_FUNC_म_से_अदीर्घ),

			/* अगर (ret == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, -EINVAL, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		"bpf_strtoul buf with spaces only, EINVAL",
		.insns = अणु
			/* arg1 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_MOV64_IMM(BPF_REG_0,
				      bpf_ntohl(0x0d0c0a09)),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

			/* arg2 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_2, 4),

			/* arg3 (flags) */
			BPF_MOV64_IMM(BPF_REG_3, 0),

			/* arg4 (res) */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

			BPF_EMIT_CALL(BPF_FUNC_म_से_अदीर्घ),

			/* अगर (ret == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, -EINVAL, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		"bpf_strtoul negative number, EINVAL",
		.insns = अणु
			/* arg1 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			/* " -6\0" */
			BPF_MOV64_IMM(BPF_REG_0,
				      bpf_ntohl(0x0a2d3600)),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

			/* arg2 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_2, 4),

			/* arg3 (flags) */
			BPF_MOV64_IMM(BPF_REG_3, 0),

			/* arg4 (res) */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

			BPF_EMIT_CALL(BPF_FUNC_म_से_अदीर्घ),

			/* अगर (ret == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, -EINVAL, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		"bpf_strtol negative number, ok",
		.insns = अणु
			/* arg1 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			/* " -6\0" */
			BPF_MOV64_IMM(BPF_REG_0,
				      bpf_ntohl(0x0a2d3600)),
			BPF_STX_MEM(BPF_W, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

			/* arg2 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_2, 4),

			/* arg3 (flags) */
			BPF_MOV64_IMM(BPF_REG_3, 10),

			/* arg4 (res) */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

			BPF_EMIT_CALL(BPF_FUNC_म_से_दीर्घ),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 3, 4),
			/*     res == expected) */
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_9, -6, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		"bpf_strtol hex number, ok",
		.insns = अणु
			/* arg1 (buf) */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			/* "0xfe" */
			BPF_MOV64_IMM(BPF_REG_0,
				      bpf_ntohl(0x30786665)),
			BPF_STX_MEM(BPF_W, BPF_REG_7, BPF_REG_0, 0),

			BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

			/* arg2 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_2, 4),

			/* arg3 (flags) */
			BPF_MOV64_IMM(BPF_REG_3, 0),

			/* arg4 (res) */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

			BPF_EMIT_CALL(BPF_FUNC_म_से_दीर्घ),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 4, 4),
			/*     res == expected) */
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_IMM(BPF_JNE, BPF_REG_9, 254, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		"bpf_strtol max long",
		.insns = अणु
			/* arg1 (buf) 9223372036854775807 */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -24),
			BPF_LD_IMM64(BPF_REG_0,
				     bpf_be64_to_cpu(0x3932323333373230ULL)),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_LD_IMM64(BPF_REG_0,
				     bpf_be64_to_cpu(0x3336383534373735ULL)),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 8),
			BPF_LD_IMM64(BPF_REG_0,
				     bpf_be64_to_cpu(0x3830370000000000ULL)),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 16),

			BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

			/* arg2 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_2, 19),

			/* arg3 (flags) */
			BPF_MOV64_IMM(BPF_REG_3, 0),

			/* arg4 (res) */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

			BPF_EMIT_CALL(BPF_FUNC_म_से_दीर्घ),

			/* अगर (ret == expected && */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 19, 6),
			/*     res == expected) */
			BPF_LD_IMM64(BPF_REG_8, 0x7fffffffffffffffULL),
			BPF_LDX_MEM(BPF_DW, BPF_REG_9, BPF_REG_7, 0),
			BPF_JMP_REG(BPF_JNE, BPF_REG_8, BPF_REG_9, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		"bpf_strtol overflow, ERANGE",
		.insns = अणु
			/* arg1 (buf) 9223372036854775808 */
			BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -24),
			BPF_LD_IMM64(BPF_REG_0,
				     bpf_be64_to_cpu(0x3932323333373230ULL)),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_LD_IMM64(BPF_REG_0,
				     bpf_be64_to_cpu(0x3336383534373735ULL)),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 8),
			BPF_LD_IMM64(BPF_REG_0,
				     bpf_be64_to_cpu(0x3830380000000000ULL)),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 16),

			BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

			/* arg2 (buf_len) */
			BPF_MOV64_IMM(BPF_REG_2, 19),

			/* arg3 (flags) */
			BPF_MOV64_IMM(BPF_REG_3, 0),

			/* arg4 (res) */
			BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
			BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
			BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

			BPF_EMIT_CALL(BPF_FUNC_म_से_दीर्घ),

			/* अगर (ret == expected) */
			BPF_JMP_IMM(BPF_JNE, BPF_REG_0, -दुस्फल, 2),

			/* वापस ALLOW; */
			BPF_MOV64_IMM(BPF_REG_0, 1),
			BPF_JMP_A(1),

			/* अन्यथा वापस DENY; */
			BPF_MOV64_IMM(BPF_REG_0, 0),
			BPF_EXIT_INSN(),
		पूर्ण,
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
	अणु
		"C prog: deny all writes",
		.prog_file = "./test_sysctl_prog.o",
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/tcp_mem",
		.खोलो_flags = O_WRONLY,
		.newval = "123 456 789",
		.result = OP_EPERM,
	पूर्ण,
	अणु
		"C prog: deny access by name",
		.prog_file = "./test_sysctl_prog.o",
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/route/mtu_expires",
		.खोलो_flags = O_RDONLY,
		.result = OP_EPERM,
	पूर्ण,
	अणु
		"C prog: read tcp_mem",
		.prog_file = "./test_sysctl_prog.o",
		.attach_type = BPF_CGROUP_SYSCTL,
		.sysctl = "net/ipv4/tcp_mem",
		.खोलो_flags = O_RDONLY,
		.result = SUCCESS,
	पूर्ण,
पूर्ण;

अटल माप_प्रकार probe_prog_length(स्थिर काष्ठा bpf_insn *fp)
अणु
	माप_प्रकार len;

	क्रम (len = MAX_INSNS - 1; len > 0; --len)
		अगर (fp[len].code != 0 || fp[len].imm != 0)
			अवरोध;
	वापस len + 1;
पूर्ण

अटल पूर्णांक fixup_sysctl_value(स्थिर अक्षर *buf, माप_प्रकार buf_len,
			      काष्ठा bpf_insn *prog, माप_प्रकार insn_num)
अणु
	जोड़ अणु
		uपूर्णांक8_t raw[माप(uपूर्णांक64_t)];
		uपूर्णांक64_t num;
	पूर्ण value = अणुपूर्ण;

	अगर (buf_len > माप(value)) अणु
		log_err("Value is too big (%zd) to use in fixup", buf_len);
		वापस -1;
	पूर्ण
	अगर (prog[insn_num].code != (BPF_LD | BPF_DW | BPF_IMM)) अणु
		log_err("Can fixup only BPF_LD_IMM64 insns");
		वापस -1;
	पूर्ण

	स_नकल(value.raw, buf, buf_len);
	prog[insn_num].imm = (uपूर्णांक32_t)value.num;
	prog[insn_num + 1].imm = (uपूर्णांक32_t)(value.num >> 32);

	वापस 0;
पूर्ण

अटल पूर्णांक load_sysctl_prog_insns(काष्ठा sysctl_test *test,
				  स्थिर अक्षर *sysctl_path)
अणु
	काष्ठा bpf_insn *prog = test->insns;
	काष्ठा bpf_load_program_attr attr;
	पूर्णांक ret;

	स_रखो(&attr, 0, माप(काष्ठा bpf_load_program_attr));
	attr.prog_type = BPF_PROG_TYPE_CGROUP_SYSCTL;
	attr.insns = prog;
	attr.insns_cnt = probe_prog_length(attr.insns);
	attr.license = "GPL";

	अगर (test->fixup_value_insn) अणु
		अक्षर buf[128];
		sमाप_प्रकार len;
		पूर्णांक fd;

		fd = खोलो(sysctl_path, O_RDONLY | O_CLOEXEC);
		अगर (fd < 0) अणु
			log_err("open(%s) failed", sysctl_path);
			वापस -1;
		पूर्ण
		len = पढ़ो(fd, buf, माप(buf));
		अगर (len == -1) अणु
			log_err("read(%s) failed", sysctl_path);
			बंद(fd);
			वापस -1;
		पूर्ण
		बंद(fd);
		अगर (fixup_sysctl_value(buf, len, prog, test->fixup_value_insn))
			वापस -1;
	पूर्ण

	ret = bpf_load_program_xattr(&attr, bpf_log_buf, BPF_LOG_BUF_SIZE);
	अगर (ret < 0 && test->result != LOAD_REJECT) अणु
		log_err(">>> Loading program error.\n"
			">>> Verifier output:\n%s\n-------\n", bpf_log_buf);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक load_sysctl_prog_file(काष्ठा sysctl_test *test)
अणु
	काष्ठा bpf_prog_load_attr attr;
	काष्ठा bpf_object *obj;
	पूर्णांक prog_fd;

	स_रखो(&attr, 0, माप(काष्ठा bpf_prog_load_attr));
	attr.file = test->prog_file;
	attr.prog_type = BPF_PROG_TYPE_CGROUP_SYSCTL;

	अगर (bpf_prog_load_xattr(&attr, &obj, &prog_fd)) अणु
		अगर (test->result != LOAD_REJECT)
			log_err(">>> Loading program (%s) error.\n",
				test->prog_file);
		वापस -1;
	पूर्ण

	वापस prog_fd;
पूर्ण

अटल पूर्णांक load_sysctl_prog(काष्ठा sysctl_test *test, स्थिर अक्षर *sysctl_path)
अणु
		वापस test->prog_file
			? load_sysctl_prog_file(test)
			: load_sysctl_prog_insns(test, sysctl_path);
पूर्ण

अटल पूर्णांक access_sysctl(स्थिर अक्षर *sysctl_path,
			 स्थिर काष्ठा sysctl_test *test)
अणु
	पूर्णांक err = 0;
	पूर्णांक fd;

	fd = खोलो(sysctl_path, test->खोलो_flags | O_CLOEXEC);
	अगर (fd < 0)
		वापस fd;

	अगर (test->seek && lseek(fd, test->seek, शुरू_से) == -1) अणु
		log_err("lseek(%d) failed", test->seek);
		जाओ err;
	पूर्ण

	अगर (test->खोलो_flags == O_RDONLY) अणु
		अक्षर buf[128];

		अगर (पढ़ो(fd, buf, माप(buf)) == -1)
			जाओ err;
		अगर (test->oldval &&
		    म_भेदन(buf, test->oldval, म_माप(test->oldval))) अणु
			log_err("Read value %s != %s", buf, test->oldval);
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अगर (test->खोलो_flags == O_WRONLY) अणु
		अगर (!test->newval) अणु
			log_err("New value for sysctl is not set");
			जाओ err;
		पूर्ण
		अगर (ग_लिखो(fd, test->newval, म_माप(test->newval)) == -1)
			जाओ err;
	पूर्ण अन्यथा अणु
		log_err("Unexpected sysctl access: neither read nor write");
		जाओ err;
	पूर्ण

	जाओ out;
err:
	err = -1;
out:
	बंद(fd);
	वापस err;
पूर्ण

अटल पूर्णांक run_test_हाल(पूर्णांक cgfd, काष्ठा sysctl_test *test)
अणु
	क्रमागत bpf_attach_type atype = test->attach_type;
	अक्षर sysctl_path[128];
	पूर्णांक progfd = -1;
	पूर्णांक err = 0;

	म_लिखो("Test case: %s .. ", test->descr);

	snम_लिखो(sysctl_path, माप(sysctl_path), "/proc/sys/%s",
		 test->sysctl);

	progfd = load_sysctl_prog(test, sysctl_path);
	अगर (progfd < 0) अणु
		अगर (test->result == LOAD_REJECT)
			जाओ out;
		अन्यथा
			जाओ err;
	पूर्ण

	अगर (bpf_prog_attach(progfd, cgfd, atype, BPF_F_ALLOW_OVERRIDE) == -1) अणु
		अगर (test->result == ATTACH_REJECT)
			जाओ out;
		अन्यथा
			जाओ err;
	पूर्ण

	त्रुटि_सं = 0;
	अगर (access_sysctl(sysctl_path, test) == -1) अणु
		अगर (test->result == OP_EPERM && त्रुटि_सं == EPERM)
			जाओ out;
		अन्यथा
			जाओ err;
	पूर्ण

	अगर (test->result != SUCCESS) अणु
		log_err("Unexpected success");
		जाओ err;
	पूर्ण

	जाओ out;
err:
	err = -1;
out:
	/* Detaching w/o checking वापस code: best efक्रमt attempt. */
	अगर (progfd != -1)
		bpf_prog_detach(cgfd, atype);
	बंद(progfd);
	म_लिखो("[%s]\n", err ? "FAIL" : "PASS");
	वापस err;
पूर्ण

अटल पूर्णांक run_tests(पूर्णांक cgfd)
अणु
	पूर्णांक passes = 0;
	पूर्णांक fails = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tests); ++i) अणु
		अगर (run_test_हाल(cgfd, &tests[i]))
			++fails;
		अन्यथा
			++passes;
	पूर्ण
	म_लिखो("Summary: %d PASSED, %d FAILED\n", passes, fails);
	वापस fails ? -1 : 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक cgfd = -1;
	पूर्णांक err = 0;

	cgfd = cgroup_setup_and_join(CG_PATH);
	अगर (cgfd < 0)
		जाओ err;

	अगर (run_tests(cgfd))
		जाओ err;

	जाओ out;
err:
	err = -1;
out:
	बंद(cgfd);
	cleanup_cgroup_environment();
	वापस err;
पूर्ण
