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

काष्ठा core_reloc_bitfields अणु
	/* अचिन्हित bitfields */
	uपूर्णांक8_t		ub1: 1;
	uपूर्णांक8_t		ub2: 2;
	uपूर्णांक32_t	ub7: 7;
	/* चिन्हित bitfields */
	पूर्णांक8_t		sb4: 4;
	पूर्णांक32_t		sb20: 20;
	/* non-bitfields */
	uपूर्णांक32_t	u32;
	पूर्णांक32_t		s32;
पूर्ण;

/* bitfield पढ़ो results, all as plain पूर्णांकegers */
काष्ठा core_reloc_bitfields_output अणु
	पूर्णांक64_t		ub1;
	पूर्णांक64_t		ub2;
	पूर्णांक64_t		ub7;
	पूर्णांक64_t		sb4;
	पूर्णांक64_t		sb20;
	पूर्णांक64_t		u32;
	पूर्णांक64_t		s32;
पूर्ण;

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_bitfields(व्योम *ctx)
अणु
	काष्ठा core_reloc_bitfields *in = (व्योम *)&data.in;
	काष्ठा core_reloc_bitfields_output *out = (व्योम *)&data.out;
	uपूर्णांक64_t res;

	out->ub1 = BPF_CORE_READ_BITFIELD_PROBED(in, ub1);
	out->ub2 = BPF_CORE_READ_BITFIELD_PROBED(in, ub2);
	out->ub7 = BPF_CORE_READ_BITFIELD_PROBED(in, ub7);
	out->sb4 = BPF_CORE_READ_BITFIELD_PROBED(in, sb4);
	out->sb20 = BPF_CORE_READ_BITFIELD_PROBED(in, sb20);
	out->u32 = BPF_CORE_READ_BITFIELD_PROBED(in, u32);
	out->s32 = BPF_CORE_READ_BITFIELD_PROBED(in, s32);

	वापस 0;
पूर्ण

