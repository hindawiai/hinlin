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

काष्ठा a_काष्ठा अणु
	पूर्णांक x;
पूर्ण;

जोड़ a_जोड़ अणु
	पूर्णांक y;
	पूर्णांक z;
पूर्ण;

प्रकार काष्ठा a_काष्ठा named_काष्ठा_प्रकार;

प्रकार काष्ठा अणु पूर्णांक x, y, z; पूर्ण anon_काष्ठा_प्रकार;

प्रकार काष्ठा अणु
	पूर्णांक a, b, c;
पूर्ण *काष्ठा_ptr_प्रकार;

क्रमागत an_क्रमागत अणु
	AN_ENUM_VAL1 = 1,
	AN_ENUM_VAL2 = 2,
	AN_ENUM_VAL3 = 3,
पूर्ण;

प्रकार पूर्णांक पूर्णांक_प्रकार;

प्रकार क्रमागत अणु TYPEDEF_ENUM_VAL1, TYPEDEF_ENUM_VAL2 पूर्ण क्रमागत_प्रकार;

प्रकार व्योम *व्योम_ptr_प्रकार;

प्रकार पूर्णांक (*func_proto_प्रकार)(दीर्घ);

प्रकार अक्षर arr_प्रकार[20];

काष्ठा core_reloc_type_based_output अणु
	bool काष्ठा_exists;
	bool जोड़_exists;
	bool क्रमागत_exists;
	bool प्रकार_named_काष्ठा_exists;
	bool प्रकार_anon_काष्ठा_exists;
	bool प्रकार_काष्ठा_ptr_exists;
	bool प्रकार_पूर्णांक_exists;
	bool प्रकार_क्रमागत_exists;
	bool प्रकार_व्योम_ptr_exists;
	bool प्रकार_func_proto_exists;
	bool प्रकार_arr_exists;

	पूर्णांक काष्ठा_sz;
	पूर्णांक जोड़_sz;
	पूर्णांक क्रमागत_sz;
	पूर्णांक प्रकार_named_काष्ठा_sz;
	पूर्णांक प्रकार_anon_काष्ठा_sz;
	पूर्णांक प्रकार_काष्ठा_ptr_sz;
	पूर्णांक प्रकार_पूर्णांक_sz;
	पूर्णांक प्रकार_क्रमागत_sz;
	पूर्णांक प्रकार_व्योम_ptr_sz;
	पूर्णांक प्रकार_func_proto_sz;
	पूर्णांक प्रकार_arr_sz;
पूर्ण;

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_type_based(व्योम *ctx)
अणु
#अगर __has_builtin(__builtin_preserve_type_info)
	काष्ठा core_reloc_type_based_output *out = (व्योम *)&data.out;

	out->काष्ठा_exists = bpf_core_type_exists(काष्ठा a_काष्ठा);
	out->जोड़_exists = bpf_core_type_exists(जोड़ a_जोड़);
	out->क्रमागत_exists = bpf_core_type_exists(क्रमागत an_क्रमागत);
	out->प्रकार_named_काष्ठा_exists = bpf_core_type_exists(named_काष्ठा_प्रकार);
	out->प्रकार_anon_काष्ठा_exists = bpf_core_type_exists(anon_काष्ठा_प्रकार);
	out->प्रकार_काष्ठा_ptr_exists = bpf_core_type_exists(काष्ठा_ptr_प्रकार);
	out->प्रकार_पूर्णांक_exists = bpf_core_type_exists(पूर्णांक_प्रकार);
	out->प्रकार_क्रमागत_exists = bpf_core_type_exists(क्रमागत_प्रकार);
	out->प्रकार_व्योम_ptr_exists = bpf_core_type_exists(व्योम_ptr_प्रकार);
	out->प्रकार_func_proto_exists = bpf_core_type_exists(func_proto_प्रकार);
	out->प्रकार_arr_exists = bpf_core_type_exists(arr_प्रकार);

	out->काष्ठा_sz = bpf_core_type_size(काष्ठा a_काष्ठा);
	out->जोड़_sz = bpf_core_type_size(जोड़ a_जोड़);
	out->क्रमागत_sz = bpf_core_type_size(क्रमागत an_क्रमागत);
	out->प्रकार_named_काष्ठा_sz = bpf_core_type_size(named_काष्ठा_प्रकार);
	out->प्रकार_anon_काष्ठा_sz = bpf_core_type_size(anon_काष्ठा_प्रकार);
	out->प्रकार_काष्ठा_ptr_sz = bpf_core_type_size(काष्ठा_ptr_प्रकार);
	out->प्रकार_पूर्णांक_sz = bpf_core_type_size(पूर्णांक_प्रकार);
	out->प्रकार_क्रमागत_sz = bpf_core_type_size(क्रमागत_प्रकार);
	out->प्रकार_व्योम_ptr_sz = bpf_core_type_size(व्योम_ptr_प्रकार);
	out->प्रकार_func_proto_sz = bpf_core_type_size(func_proto_प्रकार);
	out->प्रकार_arr_sz = bpf_core_type_size(arr_प्रकार);
#अन्यथा
	data.skip = true;
#पूर्ण_अगर
	वापस 0;
पूर्ण
