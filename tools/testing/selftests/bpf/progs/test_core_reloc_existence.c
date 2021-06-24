<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook

#समावेश <linux/bpf.h>
#समावेश <मानक_निवेशt.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	अक्षर in[256];
	अक्षर out[256];
पूर्ण data = अणुपूर्ण;

काष्ठा core_reloc_existence_output अणु
	पूर्णांक a_exists;
	पूर्णांक a_value;
	पूर्णांक b_exists;
	पूर्णांक b_value;
	पूर्णांक c_exists;
	पूर्णांक c_value;
	पूर्णांक arr_exists;
	पूर्णांक arr_value;
	पूर्णांक s_exists;
	पूर्णांक s_value;
पूर्ण;

काष्ठा core_reloc_existence अणु
	काष्ठा अणु
		पूर्णांक x;
	पूर्ण s;
	पूर्णांक arr[1];
	पूर्णांक a;
	काष्ठा अणु
		पूर्णांक b;
	पूर्ण;
	पूर्णांक c;
पूर्ण;

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_existence(व्योम *ctx)
अणु
	काष्ठा core_reloc_existence *in = (व्योम *)&data.in;
	काष्ठा core_reloc_existence_output *out = (व्योम *)&data.out;

	out->a_exists = bpf_core_field_exists(in->a);
	अगर (bpf_core_field_exists(in->a))
		out->a_value = BPF_CORE_READ(in, a);
	अन्यथा
		out->a_value = 0xff000001u;

	out->b_exists = bpf_core_field_exists(in->b);
	अगर (bpf_core_field_exists(in->b))
		out->b_value = BPF_CORE_READ(in, b);
	अन्यथा
		out->b_value = 0xff000002u;

	out->c_exists = bpf_core_field_exists(in->c);
	अगर (bpf_core_field_exists(in->c))
		out->c_value = BPF_CORE_READ(in, c);
	अन्यथा
		out->c_value = 0xff000003u;

	out->arr_exists = bpf_core_field_exists(in->arr);
	अगर (bpf_core_field_exists(in->arr))
		out->arr_value = BPF_CORE_READ(in, arr[0]);
	अन्यथा
		out->arr_value = 0xff000004u;

	out->s_exists = bpf_core_field_exists(in->s);
	अगर (bpf_core_field_exists(in->s))
		out->s_value = BPF_CORE_READ(in, s.x);
	अन्यथा
		out->s_value = 0xff000005u;

	वापस 0;
पूर्ण

