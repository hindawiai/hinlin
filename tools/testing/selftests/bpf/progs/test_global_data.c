<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Isovalent, Inc.

#समावेश <linux/bpf.h>
#समावेश <linux/pkt_cls.h>
#समावेश <माला.स>

#समावेश <bpf/bpf_helpers.h>

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 11);
	__type(key, __u32);
	__type(value, __u64);
पूर्ण result_number SEC(".maps");

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 5);
	__type(key, __u32);
	स्थिर अक्षर (*value)[32];
पूर्ण result_string SEC(".maps");

काष्ठा foo अणु
	__u8  a;
	__u32 b;
	__u64 c;
पूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_ARRAY);
	__uपूर्णांक(max_entries, 5);
	__type(key, __u32);
	__type(value, काष्ठा foo);
पूर्ण result_काष्ठा SEC(".maps");

/* Relocation tests क्रम __u64s. */
अटल       __u64 num0;
अटल       __u64 num1 = 42;
अटल स्थिर __u64 num2 = 24;
अटल       __u64 num3 = 0;
अटल       __u64 num4 = 0xffeeff;
अटल स्थिर __u64 num5 = 0xabab;
अटल स्थिर __u64 num6 = 0xab;

/* Relocation tests क्रम strings. */
अटल स्थिर अक्षर str0[32] = "abcdefghijklmnopqrstuvwxyz";
अटल       अक्षर str1[32] = "abcdefghijklmnopqrstuvwxyz";
अटल       अक्षर str2[32];

/* Relocation tests क्रम काष्ठाs. */
अटल स्थिर काष्ठा foo काष्ठा0 = अणु
	.a = 42,
	.b = 0xfefeefef,
	.c = 0x1111111111111111ULL,
पूर्ण;
अटल काष्ठा foo काष्ठा1;
अटल स्थिर काष्ठा foo काष्ठा2;
अटल काष्ठा foo काष्ठा3 = अणु
	.a = 41,
	.b = 0xeeeeefef,
	.c = 0x2111111111111111ULL,
पूर्ण;

#घोषणा test_reloc(map, num, var)					\
	करो अणु								\
		__u32 key = num;					\
		bpf_map_update_elem(&result_##map, &key, var, 0);	\
	पूर्ण जबतक (0)

SEC("classifier/static_data_load")
पूर्णांक load_अटल_data(काष्ठा __sk_buff *skb)
अणु
	अटल स्थिर __u64 bar = ~0;

	test_reloc(number, 0, &num0);
	test_reloc(number, 1, &num1);
	test_reloc(number, 2, &num2);
	test_reloc(number, 3, &num3);
	test_reloc(number, 4, &num4);
	test_reloc(number, 5, &num5);
	num4 = 1234;
	test_reloc(number, 6, &num4);
	test_reloc(number, 7, &num0);
	test_reloc(number, 8, &num6);

	test_reloc(string, 0, str0);
	test_reloc(string, 1, str1);
	test_reloc(string, 2, str2);
	str1[5] = 'x';
	test_reloc(string, 3, str1);
	__builtin_स_नकल(&str2[2], "hello", माप("hello"));
	test_reloc(string, 4, str2);

	test_reloc(काष्ठा, 0, &काष्ठा0);
	test_reloc(काष्ठा, 1, &काष्ठा1);
	test_reloc(काष्ठा, 2, &काष्ठा2);
	test_reloc(काष्ठा, 3, &काष्ठा3);

	test_reloc(number,  9, &काष्ठा0.c);
	test_reloc(number, 10, &bar);

	वापस TC_ACT_OK;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
