<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Facebook

#समावेश <linux/bpf.h>
#समावेश <मानक_निवेशt.h>
#समावेश <stdbool.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

अक्षर _license[] SEC("license") = "GPL";

काष्ठा अणु
	अक्षर in[256];
	अक्षर out[256];
	bool skip;
पूर्ण data = अणुपूर्ण;

/* some types are shared with test_core_reloc_type_based.c */
काष्ठा a_काष्ठा अणु
	पूर्णांक x;
पूर्ण;

जोड़ a_जोड़ अणु
	पूर्णांक y;
	पूर्णांक z;
पूर्ण;

क्रमागत an_क्रमागत अणु
	AN_ENUM_VAL1 = 1,
	AN_ENUM_VAL2 = 2,
	AN_ENUM_VAL3 = 3,
पूर्ण;

प्रकार काष्ठा a_काष्ठा named_काष्ठा_प्रकार;

प्रकार पूर्णांक (*func_proto_प्रकार)(दीर्घ);

प्रकार अक्षर arr_प्रकार[20];

काष्ठा core_reloc_type_id_output अणु
	पूर्णांक local_anon_काष्ठा;
	पूर्णांक local_anon_जोड़;
	पूर्णांक local_anon_क्रमागत;
	पूर्णांक local_anon_func_proto_ptr;
	पूर्णांक local_anon_व्योम_ptr;
	पूर्णांक local_anon_arr;

	पूर्णांक local_काष्ठा;
	पूर्णांक local_जोड़;
	पूर्णांक local_क्रमागत;
	पूर्णांक local_पूर्णांक;
	पूर्णांक local_काष्ठा_प्रकार;
	पूर्णांक local_func_proto_प्रकार;
	पूर्णांक local_arr_प्रकार;

	पूर्णांक targ_काष्ठा;
	पूर्णांक targ_जोड़;
	पूर्णांक targ_क्रमागत;
	पूर्णांक targ_पूर्णांक;
	पूर्णांक targ_काष्ठा_प्रकार;
	पूर्णांक targ_func_proto_प्रकार;
	पूर्णांक targ_arr_प्रकार;
पूर्ण;

/* preserve types even अगर Clang करोesn't support built-in */
काष्ठा a_काष्ठा t1 = अणुपूर्ण;
जोड़ a_जोड़ t2 = अणुपूर्ण;
क्रमागत an_क्रमागत t3 = 0;
named_काष्ठा_प्रकार t4 = अणुपूर्ण;
func_proto_प्रकार t5 = 0;
arr_प्रकार t6 = अणुपूर्ण;

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_type_id(व्योम *ctx)
अणु
	/* We use __builtin_btf_type_id() in this tests, but up until the समय
	 * __builtin_preserve_type_info() was added it contained a bug that
	 * would make this test fail. The bug was fixed ([0]) with addition of
	 * __builtin_preserve_type_info(), though, so that's what we are using
	 * to detect whether this test has to be executed, however strange
	 * that might look like.
	 *
	 *   [0] https://reviews.llvm.org/D85174
	 */
#अगर __has_builtin(__builtin_preserve_type_info)
	काष्ठा core_reloc_type_id_output *out = (व्योम *)&data.out;

	out->local_anon_काष्ठा = bpf_core_type_id_local(काष्ठा अणु पूर्णांक marker_field; पूर्ण);
	out->local_anon_जोड़ = bpf_core_type_id_local(जोड़ अणु पूर्णांक marker_field; पूर्ण);
	out->local_anon_क्रमागत = bpf_core_type_id_local(क्रमागत अणु MARKER_ENUM_VAL = 123 पूर्ण);
	out->local_anon_func_proto_ptr = bpf_core_type_id_local(_Bool(*)(पूर्णांक));
	out->local_anon_व्योम_ptr = bpf_core_type_id_local(व्योम *);
	out->local_anon_arr = bpf_core_type_id_local(_Bool[47]);

	out->local_काष्ठा = bpf_core_type_id_local(काष्ठा a_काष्ठा);
	out->local_जोड़ = bpf_core_type_id_local(जोड़ a_जोड़);
	out->local_क्रमागत = bpf_core_type_id_local(क्रमागत an_क्रमागत);
	out->local_पूर्णांक = bpf_core_type_id_local(पूर्णांक);
	out->local_काष्ठा_प्रकार = bpf_core_type_id_local(named_काष्ठा_प्रकार);
	out->local_func_proto_प्रकार = bpf_core_type_id_local(func_proto_प्रकार);
	out->local_arr_प्रकार = bpf_core_type_id_local(arr_प्रकार);

	out->targ_काष्ठा = bpf_core_type_id_kernel(काष्ठा a_काष्ठा);
	out->targ_जोड़ = bpf_core_type_id_kernel(जोड़ a_जोड़);
	out->targ_क्रमागत = bpf_core_type_id_kernel(क्रमागत an_क्रमागत);
	out->targ_पूर्णांक = bpf_core_type_id_kernel(पूर्णांक);
	out->targ_काष्ठा_प्रकार = bpf_core_type_id_kernel(named_काष्ठा_प्रकार);
	out->targ_func_proto_प्रकार = bpf_core_type_id_kernel(func_proto_प्रकार);
	out->targ_arr_प्रकार = bpf_core_type_id_kernel(arr_प्रकार);
#अन्यथा
	data.skip = true;
#पूर्ण_अगर

	वापस 0;
पूर्ण
