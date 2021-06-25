<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook

#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>

#समावेश <linux/मानकघोष.स>
#समावेश <linux/bpf.h>

#समावेश <bpf/bpf_helpers.h>

/* Max supported length of a string with अचिन्हित दीर्घ in base 10 (घात2 - 1). */
#घोषणा MAX_ULONG_STR_LEN 0xF

/* Max supported length of sysctl value string (घात2). */
#घोषणा MAX_VALUE_STR_LEN 0x40

#अगर_अघोषित ARRAY_SIZE
#घोषणा ARRAY_SIZE(x) (माप(x) / माप((x)[0]))
#पूर्ण_अगर

स्थिर अक्षर tcp_mem_name[] = "net/ipv4/tcp_mem";
अटल __always_अंतरभूत पूर्णांक is_tcp_mem(काष्ठा bpf_sysctl *ctx)
अणु
	अचिन्हित अक्षर i;
	अक्षर name[माप(tcp_mem_name)];
	पूर्णांक ret;

	स_रखो(name, 0, माप(name));
	ret = bpf_sysctl_get_name(ctx, name, माप(name), 0);
	अगर (ret < 0 || ret != माप(tcp_mem_name) - 1)
		वापस 0;

#आशय clang loop unroll(full)
	क्रम (i = 0; i < माप(tcp_mem_name); ++i)
		अगर (name[i] != tcp_mem_name[i])
			वापस 0;

	वापस 1;
पूर्ण

SEC("cgroup/sysctl")
पूर्णांक sysctl_tcp_mem(काष्ठा bpf_sysctl *ctx)
अणु
	अचिन्हित दीर्घ tcp_mem[3] = अणु0, 0, 0पूर्ण;
	अक्षर value[MAX_VALUE_STR_LEN];
	अचिन्हित अक्षर i, off = 0;
	अस्थिर पूर्णांक ret;

	अगर (ctx->ग_लिखो)
		वापस 0;

	अगर (!is_tcp_mem(ctx))
		वापस 0;

	ret = bpf_sysctl_get_current_value(ctx, value, MAX_VALUE_STR_LEN);
	अगर (ret < 0 || ret >= MAX_VALUE_STR_LEN)
		वापस 0;

#आशय clang loop unroll(full)
	क्रम (i = 0; i < ARRAY_SIZE(tcp_mem); ++i) अणु
		ret = bpf_म_से_अदीर्घ(value + off, MAX_ULONG_STR_LEN, 0,
				  tcp_mem + i);
		अगर (ret <= 0 || ret > MAX_ULONG_STR_LEN)
			वापस 0;
		off += ret & MAX_ULONG_STR_LEN;
	पूर्ण


	वापस tcp_mem[0] < tcp_mem[1] && tcp_mem[1] < tcp_mem[2];
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
