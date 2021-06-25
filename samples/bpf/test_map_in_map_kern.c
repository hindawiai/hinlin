<शैली गुरु>
/*
 * Copyright (c) 2017 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#घोषणा KBUILD_MODNAME "foo"
#समावेश <linux/ptrace.h>
#समावेश <linux/version.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/in6.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>
#समावेश <bpf/bpf_core_पढ़ो.h>
#समावेश "trace_common.h"

#घोषणा MAX_NR_PORTS 65536

/* map #0 */
काष्ठा inner_a अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__type(key, u32);
	__type(value, पूर्णांक);
	__uपूर्णांक(max_entries, MAX_NR_PORTS);
पूर्ण port_a SEC(".maps");

/* map #1 */
काष्ठा inner_h अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, u32);
	__type(value, पूर्णांक);
	__uपूर्णांक(max_entries, 1);
पूर्ण port_h SEC(".maps");

/* map #2 */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, u32);
	__type(value, पूर्णांक);
	__uपूर्णांक(max_entries, 1);
पूर्ण reg_result_h SEC(".maps");

/* map #3 */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH);
	__type(key, u32);
	__type(value, पूर्णांक);
	__uपूर्णांक(max_entries, 1);
पूर्ण अंतरभूत_result_h SEC(".maps");

/* map #4 */ /* Test हाल #0 */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY_OF_MAPS);
	__uपूर्णांक(max_entries, MAX_NR_PORTS);
	__uपूर्णांक(key_size, माप(u32));
	__array(values, काष्ठा inner_a); /* use inner_a as inner map */
पूर्ण a_of_port_a SEC(".maps");

/* map #5 */ /* Test हाल #1 */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH_OF_MAPS);
	__uपूर्णांक(max_entries, 1);
	__uपूर्णांक(key_size, माप(u32));
	__array(values, काष्ठा inner_a); /* use inner_a as inner map */
पूर्ण h_of_port_a SEC(".maps");

/* map #6 */ /* Test हाल #2 */
काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_HASH_OF_MAPS);
	__uपूर्णांक(max_entries, 1);
	__uपूर्णांक(key_size, माप(u32));
	__array(values, काष्ठा inner_h); /* use inner_h as inner map */
पूर्ण h_of_port_h SEC(".maps");

अटल __always_अंतरभूत पूर्णांक करो_reg_lookup(व्योम *inner_map, u32 port)
अणु
	पूर्णांक *result;

	result = bpf_map_lookup_elem(inner_map, &port);
	वापस result ? *result : -ENOENT;
पूर्ण

अटल __always_अंतरभूत पूर्णांक करो_अंतरभूत_array_lookup(व्योम *inner_map, u32 port)
अणु
	पूर्णांक *result;

	अगर (inner_map != &port_a)
		वापस -EINVAL;

	result = bpf_map_lookup_elem(&port_a, &port);
	वापस result ? *result : -ENOENT;
पूर्ण

अटल __always_अंतरभूत पूर्णांक करो_अंतरभूत_hash_lookup(व्योम *inner_map, u32 port)
अणु
	पूर्णांक *result;

	अगर (inner_map != &port_h)
		वापस -EINVAL;

	result = bpf_map_lookup_elem(&port_h, &port);
	वापस result ? *result : -ENOENT;
पूर्ण

SEC("kprobe/__sys_connect")
पूर्णांक trace_sys_connect(काष्ठा pt_regs *ctx)
अणु
	काष्ठा sockaddr_in6 *in6;
	u16 test_हाल, port, dst6[8];
	पूर्णांक addrlen, ret, अंतरभूत_ret, ret_key = 0;
	u32 port_key;
	व्योम *outer_map, *inner_map;
	bool अंतरभूत_hash = false;

	in6 = (काष्ठा sockaddr_in6 *)PT_REGS_PARM2_CORE(ctx);
	addrlen = (पूर्णांक)PT_REGS_PARM3_CORE(ctx);

	अगर (addrlen != माप(*in6))
		वापस 0;

	ret = bpf_probe_पढ़ो_user(dst6, माप(dst6), &in6->sin6_addr);
	अगर (ret) अणु
		अंतरभूत_ret = ret;
		जाओ करोne;
	पूर्ण

	अगर (dst6[0] != 0xdead || dst6[1] != 0xbeef)
		वापस 0;

	test_हाल = dst6[7];

	ret = bpf_probe_पढ़ो_user(&port, माप(port), &in6->sin6_port);
	अगर (ret) अणु
		अंतरभूत_ret = ret;
		जाओ करोne;
	पूर्ण

	port_key = port;

	ret = -ENOENT;
	अगर (test_हाल == 0) अणु
		outer_map = &a_of_port_a;
	पूर्ण अन्यथा अगर (test_हाल == 1) अणु
		outer_map = &h_of_port_a;
	पूर्ण अन्यथा अगर (test_हाल == 2) अणु
		outer_map = &h_of_port_h;
	पूर्ण अन्यथा अणु
		ret = __LINE__;
		अंतरभूत_ret = ret;
		जाओ करोne;
	पूर्ण

	inner_map = bpf_map_lookup_elem(outer_map, &port_key);
	अगर (!inner_map) अणु
		ret = __LINE__;
		अंतरभूत_ret = ret;
		जाओ करोne;
	पूर्ण

	ret = करो_reg_lookup(inner_map, port_key);

	अगर (test_हाल == 0 || test_हाल == 1)
		अंतरभूत_ret = करो_अंतरभूत_array_lookup(inner_map, port_key);
	अन्यथा
		अंतरभूत_ret = करो_अंतरभूत_hash_lookup(inner_map, port_key);

करोne:
	bpf_map_update_elem(&reg_result_h, &ret_key, &ret, BPF_ANY);
	bpf_map_update_elem(&अंतरभूत_result_h, &ret_key, &अंतरभूत_ret, BPF_ANY);

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
