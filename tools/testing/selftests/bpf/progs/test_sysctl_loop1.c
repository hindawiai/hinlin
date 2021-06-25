<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook

#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>

#समावेश <linux/मानकघोष.स>
#समावेश <linux/bpf.h>

#समावेश <bpf/bpf_helpers.h>

#अगर_अघोषित ARRAY_SIZE
#घोषणा ARRAY_SIZE(x) (माप(x) / माप((x)[0]))
#पूर्ण_अगर

/* tcp_mem sysctl has only 3 पूर्णांकs, but this test is करोing TCP_MEM_LOOPS */
#घोषणा TCP_MEM_LOOPS 28  /* because 30 करोesn't fit पूर्णांकo 512 bytes of stack */
#घोषणा MAX_ULONG_STR_LEN 7
#घोषणा MAX_VALUE_STR_LEN (TCP_MEM_LOOPS * MAX_ULONG_STR_LEN)

स्थिर अक्षर tcp_mem_name[] = "net/ipv4/tcp_mem/very_very_very_very_long_pointless_string";
अटल __always_अंतरभूत पूर्णांक is_tcp_mem(काष्ठा bpf_sysctl *ctx)
अणु
	अचिन्हित अक्षर i;
	अक्षर name[माप(tcp_mem_name)];
	पूर्णांक ret;

	स_रखो(name, 0, माप(name));
	ret = bpf_sysctl_get_name(ctx, name, माप(name), 0);
	अगर (ret < 0 || ret != माप(tcp_mem_name) - 1)
		वापस 0;

#आशय clang loop unroll(disable)
	क्रम (i = 0; i < माप(tcp_mem_name); ++i)
		अगर (name[i] != tcp_mem_name[i])
			वापस 0;

	वापस 1;
पूर्ण

SEC("cgroup/sysctl")
पूर्णांक sysctl_tcp_mem(काष्ठा bpf_sysctl *ctx)
अणु
	अचिन्हित दीर्घ tcp_mem[TCP_MEM_LOOPS] = अणुपूर्ण;
	अक्षर value[MAX_VALUE_STR_LEN];
	अचिन्हित अक्षर i, off = 0;
	/* a workaround to prevent compiler from generating
	 * codes verअगरier cannot handle yet.
	 */
	अस्थिर पूर्णांक ret;

	अगर (ctx->ग_लिखो)
		वापस 0;

	अगर (!is_tcp_mem(ctx))
		वापस 0;

	ret = bpf_sysctl_get_current_value(ctx, value, MAX_VALUE_STR_LEN);
	अगर (ret < 0 || ret >= MAX_VALUE_STR_LEN)
		वापस 0;

#आशय clang loop unroll(disable)
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
