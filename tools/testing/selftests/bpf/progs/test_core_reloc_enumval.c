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

क्रमागत named_क्रमागत अणु
	NAMED_ENUM_VAL1 = 1,
	NAMED_ENUM_VAL2 = 2,
	NAMED_ENUM_VAL3 = 3,
पूर्ण;

प्रकार क्रमागत अणु
	ANON_ENUM_VAL1 = 0x10,
	ANON_ENUM_VAL2 = 0x20,
	ANON_ENUM_VAL3 = 0x30,
पूर्ण anon_क्रमागत;

काष्ठा core_reloc_क्रमागतval_output अणु
	bool named_val1_exists;
	bool named_val2_exists;
	bool named_val3_exists;
	bool anon_val1_exists;
	bool anon_val2_exists;
	bool anon_val3_exists;

	पूर्णांक named_val1;
	पूर्णांक named_val2;
	पूर्णांक anon_val1;
	पूर्णांक anon_val2;
पूर्ण;

SEC("raw_tracepoint/sys_enter")
पूर्णांक test_core_क्रमागतval(व्योम *ctx)
अणु
#अगर __has_builtin(__builtin_preserve_क्रमागत_value)
	काष्ठा core_reloc_क्रमागतval_output *out = (व्योम *)&data.out;
	क्रमागत named_क्रमागत named = 0;
	anon_क्रमागत anon = 0;

	out->named_val1_exists = bpf_core_क्रमागत_value_exists(named, NAMED_ENUM_VAL1);
	out->named_val2_exists = bpf_core_क्रमागत_value_exists(क्रमागत named_क्रमागत, NAMED_ENUM_VAL2);
	out->named_val3_exists = bpf_core_क्रमागत_value_exists(क्रमागत named_क्रमागत, NAMED_ENUM_VAL3);

	out->anon_val1_exists = bpf_core_क्रमागत_value_exists(anon, ANON_ENUM_VAL1);
	out->anon_val2_exists = bpf_core_क्रमागत_value_exists(anon_क्रमागत, ANON_ENUM_VAL2);
	out->anon_val3_exists = bpf_core_क्रमागत_value_exists(anon_क्रमागत, ANON_ENUM_VAL3);

	out->named_val1 = bpf_core_क्रमागत_value(named, NAMED_ENUM_VAL1);
	out->named_val2 = bpf_core_क्रमागत_value(named, NAMED_ENUM_VAL2);
	/* NAMED_ENUM_VAL3 value is optional */

	out->anon_val1 = bpf_core_क्रमागत_value(anon, ANON_ENUM_VAL1);
	out->anon_val2 = bpf_core_क्रमागत_value(anon, ANON_ENUM_VAL2);
	/* ANON_ENUM_VAL3 value is optional */
#अन्यथा
	data.skip = true;
#पूर्ण_अगर

	वापस 0;
पूर्ण
