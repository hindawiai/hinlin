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

काष्ठा core_reloc_nesting_subकाष्ठा अणु
	पूर्णांक a;
पूर्ण;

जोड़ core_reloc_nesting_subजोड़ अणु
	पूर्णांक b;
पूर्ण;

/* पूर्णांक a.a.a and b.b.b accesses */
काष्ठा core_reloc_nesting अणु
	जोड़ अणु
		काष्ठा core_reloc_nesting_subकाष्ठा a;
	पूर्ण a;
	काष्ठा अणु
		जोड़ core_reloc_nesting_subजोड़ b;
	पूर्ण b;
पूर्ण;

#घोषणा CORE_READ(dst, src) bpf_core_पढ़ो(dst, माप(*(dst)), src)

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_nesting(व्योम *ctx)
अणु
	काष्ठा core_reloc_nesting *in = (व्योम *)&data.in;
	काष्ठा core_reloc_nesting *out = (व्योम *)&data.out;

	अगर (CORE_READ(&out->a.a.a, &in->a.a.a))
		वापस 1;
	अगर (CORE_READ(&out->b.b.b, &in->b.b.b))
		वापस 1;

	वापस 0;
पूर्ण

