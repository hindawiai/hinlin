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

काष्ठा core_reloc_पूर्णांकs अणु
	uपूर्णांक8_t		u8_field;
	पूर्णांक8_t		s8_field;
	uपूर्णांक16_t	u16_field;
	पूर्णांक16_t		s16_field;
	uपूर्णांक32_t	u32_field;
	पूर्णांक32_t		s32_field;
	uपूर्णांक64_t	u64_field;
	पूर्णांक64_t		s64_field;
पूर्ण;

#घोषणा CORE_READ(dst, src) bpf_core_पढ़ो(dst, माप(*(dst)), src)

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_पूर्णांकs(व्योम *ctx)
अणु
	काष्ठा core_reloc_पूर्णांकs *in = (व्योम *)&data.in;
	काष्ठा core_reloc_पूर्णांकs *out = (व्योम *)&data.out;

	अगर (CORE_READ(&out->u8_field, &in->u8_field) ||
	    CORE_READ(&out->s8_field, &in->s8_field) ||
	    CORE_READ(&out->u16_field, &in->u16_field) ||
	    CORE_READ(&out->s16_field, &in->s16_field) ||
	    CORE_READ(&out->u32_field, &in->u32_field) ||
	    CORE_READ(&out->s32_field, &in->s32_field) ||
	    CORE_READ(&out->u64_field, &in->u64_field) ||
	    CORE_READ(&out->s64_field, &in->s64_field))
		वापस 1;

	वापस 0;
पूर्ण

