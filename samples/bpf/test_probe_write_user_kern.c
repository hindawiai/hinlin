<शैली गुरु>
/* Copyright (c) 2016 Sargun Dhillon <sargun@sargun.me>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <linux/version.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_core_पढ़ो.h>
#समावेश "trace_common.h"

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, काष्ठा sockaddr_in);
	__type(value, काष्ठा sockaddr_in);
	__uपूर्णांक(max_entries, 256);
पूर्ण dnat_map SEC(".maps");

/* kprobe is NOT a stable ABI
 * kernel functions can be हटाओd, नामd or completely change semantics.
 * Number of arguments and their positions can change, etc.
 * In such हाल this bpf+kprobe example will no दीर्घer be meaningful
 *
 * This example sits on a syscall, and the syscall ABI is relatively stable
 * of course, across platक्रमms, and over समय, the ABI may change.
 */
SEC("kprobe/" SYSCALL(sys_connect))
पूर्णांक bpf_prog1(काष्ठा pt_regs *ctx)
अणु
	काष्ठा pt_regs *real_regs = (काष्ठा pt_regs *)PT_REGS_PARM1_CORE(ctx);
	व्योम *sockaddr_arg = (व्योम *)PT_REGS_PARM2_CORE(real_regs);
	पूर्णांक sockaddr_len = (पूर्णांक)PT_REGS_PARM3_CORE(real_regs);
	काष्ठा sockaddr_in new_addr, orig_addr = अणुपूर्ण;
	काष्ठा sockaddr_in *mapped_addr;

	अगर (sockaddr_len > माप(orig_addr))
		वापस 0;

	अगर (bpf_probe_पढ़ो_user(&orig_addr, माप(orig_addr), sockaddr_arg) != 0)
		वापस 0;

	mapped_addr = bpf_map_lookup_elem(&dnat_map, &orig_addr);
	अगर (mapped_addr != शून्य) अणु
		स_नकल(&new_addr, mapped_addr, माप(new_addr));
		bpf_probe_ग_लिखो_user(sockaddr_arg, &new_addr,
				     माप(new_addr));
	पूर्ण
	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
