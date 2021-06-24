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

काष्ठा core_reloc_size_output अणु
	पूर्णांक पूर्णांक_sz;
	पूर्णांक काष्ठा_sz;
	पूर्णांक जोड़_sz;
	पूर्णांक arr_sz;
	पूर्णांक arr_elem_sz;
	पूर्णांक ptr_sz;
	पूर्णांक क्रमागत_sz;
	पूर्णांक भग्न_sz;
पूर्ण;

काष्ठा core_reloc_size अणु
	पूर्णांक पूर्णांक_field;
	काष्ठा अणु पूर्णांक x; पूर्ण काष्ठा_field;
	जोड़ अणु पूर्णांक x; पूर्ण जोड़_field;
	पूर्णांक arr_field[4];
	व्योम *ptr_field;
	क्रमागत अणु VALUE = 123 पूर्ण क्रमागत_field;
	भग्न भग्न_field;
पूर्ण;

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_size(व्योम *ctx)
अणु
	काष्ठा core_reloc_size *in = (व्योम *)&data.in;
	काष्ठा core_reloc_size_output *out = (व्योम *)&data.out;

	out->पूर्णांक_sz = bpf_core_field_size(in->पूर्णांक_field);
	out->काष्ठा_sz = bpf_core_field_size(in->काष्ठा_field);
	out->जोड़_sz = bpf_core_field_size(in->जोड़_field);
	out->arr_sz = bpf_core_field_size(in->arr_field);
	out->arr_elem_sz = bpf_core_field_size(in->arr_field[0]);
	out->ptr_sz = bpf_core_field_size(in->ptr_field);
	out->क्रमागत_sz = bpf_core_field_size(in->क्रमागत_field);
	out->भग्न_sz = bpf_core_field_size(in->भग्न_field);

	वापस 0;
पूर्ण

