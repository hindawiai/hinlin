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

काष्ठा core_reloc_misc_output अणु
	पूर्णांक a, b, c;
पूर्ण;

काष्ठा core_reloc_misc___a अणु
	पूर्णांक a1;
	पूर्णांक a2;
पूर्ण;

काष्ठा core_reloc_misc___b अणु
	पूर्णांक b1;
	पूर्णांक b2;
पूर्ण;

/* fixed two first members, can be extended with new fields */
काष्ठा core_reloc_misc_extensible अणु
	पूर्णांक a;
	पूर्णांक b;
पूर्ण;

#घोषणा CORE_READ(dst, src) bpf_core_पढ़ो(dst, माप(*(dst)), src)

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_misc(व्योम *ctx)
अणु
	काष्ठा core_reloc_misc___a *in_a = (व्योम *)&data.in;
	काष्ठा core_reloc_misc___b *in_b = (व्योम *)&data.in;
	काष्ठा core_reloc_misc_extensible *in_ext = (व्योम *)&data.in;
	काष्ठा core_reloc_misc_output *out = (व्योम *)&data.out;

	/* record two dअगरferent relocations with the same accessor string */
	अगर (CORE_READ(&out->a, &in_a->a1) ||		/* accessor: 0:0 */
	    CORE_READ(&out->b, &in_b->b1))		/* accessor: 0:0 */
		वापस 1;

	/* Validate relocations capture array-only accesses क्रम काष्ठाs with
	 * fixed header, but with potentially extendable tail. This will पढ़ो
	 * first 4 bytes of 2nd element of in_ext array of potentially
	 * variably sized काष्ठा core_reloc_misc_extensible. */ 
	अगर (CORE_READ(&out->c, &in_ext[2]))		/* accessor: 2 */
		वापस 1;

	वापस 0;
पूर्ण

