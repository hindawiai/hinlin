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

काष्ठा core_reloc_arrays_output अणु
	पूर्णांक a2;
	अक्षर b123;
	पूर्णांक c1c;
	पूर्णांक d00d;
	पूर्णांक f01c;
पूर्ण;

काष्ठा core_reloc_arrays_subकाष्ठा अणु
	पूर्णांक c;
	पूर्णांक d;
पूर्ण;

काष्ठा core_reloc_arrays अणु
	पूर्णांक a[5];
	अक्षर b[2][3][4];
	काष्ठा core_reloc_arrays_subकाष्ठा c[3];
	काष्ठा core_reloc_arrays_subकाष्ठा d[1][2];
	काष्ठा core_reloc_arrays_subकाष्ठा f[][2];
पूर्ण;

#घोषणा CORE_READ(dst, src) bpf_core_पढ़ो(dst, माप(*(dst)), src)

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_arrays(व्योम *ctx)
अणु
	काष्ठा core_reloc_arrays *in = (व्योम *)&data.in;
	काष्ठा core_reloc_arrays_output *out = (व्योम *)&data.out;

	अगर (CORE_READ(&out->a2, &in->a[2]))
		वापस 1;
	अगर (CORE_READ(&out->b123, &in->b[1][2][3]))
		वापस 1;
	अगर (CORE_READ(&out->c1c, &in->c[1].c))
		वापस 1;
	अगर (CORE_READ(&out->d00d, &in->d[0][0].d))
		वापस 1;
	अगर (CORE_READ(&out->f01c, &in->f[0][1].c))
		वापस 1;

	वापस 0;
पूर्ण

