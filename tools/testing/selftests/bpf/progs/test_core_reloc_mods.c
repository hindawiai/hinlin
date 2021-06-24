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

काष्ठा core_reloc_mods_output अणु
	पूर्णांक a, b, c, d, e, f, g, h;
पूर्ण;

प्रकार स्थिर पूर्णांक पूर्णांक_t;
प्रकार स्थिर अक्षर *अक्षर_ptr_t;
प्रकार स्थिर पूर्णांक arr_t[7];

काष्ठा core_reloc_mods_subकाष्ठा अणु
	पूर्णांक x;
	पूर्णांक y;
पूर्ण;

प्रकार काष्ठा अणु
	पूर्णांक x;
	पूर्णांक y;
पूर्ण core_reloc_mods_subकाष्ठा_t;

काष्ठा core_reloc_mods अणु
	पूर्णांक a;
	पूर्णांक_t b;
	अक्षर *c;
	अक्षर_ptr_t d;
	पूर्णांक e[3];
	arr_t f;
	काष्ठा core_reloc_mods_subकाष्ठा g;
	core_reloc_mods_subकाष्ठा_t h;
पूर्ण;

#घोषणा CORE_READ(dst, src) bpf_core_पढ़ो(dst, माप(*(dst)), src)

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_mods(व्योम *ctx)
अणु
	काष्ठा core_reloc_mods *in = (व्योम *)&data.in;
	काष्ठा core_reloc_mods_output *out = (व्योम *)&data.out;

	अगर (CORE_READ(&out->a, &in->a) ||
	    CORE_READ(&out->b, &in->b) ||
	    CORE_READ(&out->c, &in->c) ||
	    CORE_READ(&out->d, &in->d) ||
	    CORE_READ(&out->e, &in->e[2]) ||
	    CORE_READ(&out->f, &in->f[1]) ||
	    CORE_READ(&out->g, &in->g.x) ||
	    CORE_READ(&out->h, &in->h.y))
		वापस 1;

	वापस 0;
पूर्ण

