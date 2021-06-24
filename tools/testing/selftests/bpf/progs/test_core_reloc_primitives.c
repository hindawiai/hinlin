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

क्रमागत core_reloc_primitives_क्रमागत अणु
	A = 0,
	B = 1,
पूर्ण;

काष्ठा core_reloc_primitives अणु
	अक्षर a;
	पूर्णांक b;
	क्रमागत core_reloc_primitives_क्रमागत c;
	व्योम *d;
	पूर्णांक (*f)(स्थिर अक्षर *);
पूर्ण;

#घोषणा CORE_READ(dst, src) bpf_core_पढ़ो(dst, माप(*(dst)), src)

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_primitives(व्योम *ctx)
अणु
	काष्ठा core_reloc_primitives *in = (व्योम *)&data.in;
	काष्ठा core_reloc_primitives *out = (व्योम *)&data.out;

	अगर (CORE_READ(&out->a, &in->a) ||
	    CORE_READ(&out->b, &in->b) ||
	    CORE_READ(&out->c, &in->c) ||
	    CORE_READ(&out->d, &in->d) ||
	    CORE_READ(&out->f, &in->f))
		वापस 1;

	वापस 0;
पूर्ण

