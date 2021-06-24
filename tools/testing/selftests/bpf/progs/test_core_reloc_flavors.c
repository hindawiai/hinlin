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

काष्ठा core_reloc_flavors अणु
	पूर्णांक a;
	पूर्णांक b;
	पूर्णांक c;
पूर्ण;

/* local flavor with reversed layout */
काष्ठा core_reloc_flavors___reversed अणु
	पूर्णांक c;
	पूर्णांक b;
	पूर्णांक a;
पूर्ण;

/* local flavor with nested/overlapping layout */
काष्ठा core_reloc_flavors___weird अणु
	काष्ठा अणु
		पूर्णांक b;
	पूर्ण;
	/* a and c overlap in local flavor, but this should still work
	 * correctly with target original flavor
	 */
	जोड़ अणु
		पूर्णांक a;
		पूर्णांक c;
	पूर्ण;
पूर्ण;

#घोषणा CORE_READ(dst, src) bpf_core_पढ़ो(dst, माप(*(dst)), src)

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_flavors(व्योम *ctx)
अणु
	काष्ठा core_reloc_flavors *in_orig = (व्योम *)&data.in;
	काष्ठा core_reloc_flavors___reversed *in_rev = (व्योम *)&data.in;
	काष्ठा core_reloc_flavors___weird *in_weird = (व्योम *)&data.in;
	काष्ठा core_reloc_flavors *out = (व्योम *)&data.out;

	/* पढ़ो a using weird layout */
	अगर (CORE_READ(&out->a, &in_weird->a))
		वापस 1;
	/* पढ़ो b using reversed layout */
	अगर (CORE_READ(&out->b, &in_rev->b))
		वापस 1;
	/* पढ़ो c using original layout */
	अगर (CORE_READ(&out->c, &in_orig->c))
		वापस 1;

	वापस 0;
पूर्ण

