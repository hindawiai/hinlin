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

काष्ठा core_reloc_ptr_as_arr अणु
	पूर्णांक a;
पूर्ण;

#घोषणा CORE_READ(dst, src) bpf_core_पढ़ो(dst, माप(*(dst)), src)

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_ptr_as_arr(व्योम *ctx)
अणु
	काष्ठा core_reloc_ptr_as_arr *in = (व्योम *)&data.in;
	काष्ठा core_reloc_ptr_as_arr *out = (व्योम *)&data.out;

	अगर (CORE_READ(&out->a, &in[2].a))
		वापस 1;

	वापस 0;
पूर्ण

