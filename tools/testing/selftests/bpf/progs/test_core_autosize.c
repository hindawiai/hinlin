<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <linux/bpf.h>
#समावेश <मानक_निवेशt.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_core_पढ़ो.h>

अक्षर _license[] SEC("license") = "GPL";

/* fields of exactly the same size */
काष्ठा test_काष्ठा___samesize अणु
	व्योम *ptr;
	अचिन्हित दीर्घ दीर्घ val1;
	अचिन्हित पूर्णांक val2;
	अचिन्हित लघु val3;
	अचिन्हित अक्षर val4;
पूर्ण __attribute((preserve_access_index));

/* अचिन्हित fields that have to be करोwnsized by libbpf */
काष्ठा test_काष्ठा___करोwnsize अणु
	व्योम *ptr;
	अचिन्हित दीर्घ val1;
	अचिन्हित दीर्घ val2;
	अचिन्हित दीर्घ val3;
	अचिन्हित दीर्घ val4;
	/* total sz: 40 */
पूर्ण __attribute__((preserve_access_index));

/* fields with चिन्हित पूर्णांकegers of wrong size, should be rejected */
काष्ठा test_काष्ठा___चिन्हित अणु
	व्योम *ptr;
	दीर्घ val1;
	दीर्घ val2;
	दीर्घ val3;
	दीर्घ val4;
पूर्ण __attribute((preserve_access_index));

/* real layout and sizes according to test's (32-bit) BTF */
काष्ठा test_काष्ठा___real अणु
	अचिन्हित पूर्णांक ptr; /* can't use `व्योम *`, it is always 8 byte in BPF target */
	अचिन्हित पूर्णांक val2;
	अचिन्हित दीर्घ दीर्घ val1;
	अचिन्हित लघु val3;
	अचिन्हित अक्षर val4;
	अचिन्हित अक्षर _pad;
	/* total sz: 20 */
पूर्ण;

काष्ठा test_काष्ठा___real input = अणु
	.ptr = 0x01020304,
	.val1 = 0x1020304050607080,
	.val2 = 0x0a0b0c0d,
	.val3 = 0xfeed,
	.val4 = 0xb9,
	._pad = 0xff, /* make sure no accidental zeros are present */
पूर्ण;

अचिन्हित दीर्घ दीर्घ ptr_samesized = 0;
अचिन्हित दीर्घ दीर्घ val1_samesized = 0;
अचिन्हित दीर्घ दीर्घ val2_samesized = 0;
अचिन्हित दीर्घ दीर्घ val3_samesized = 0;
अचिन्हित दीर्घ दीर्घ val4_samesized = 0;
काष्ठा test_काष्ठा___real output_samesized = अणुपूर्ण;

अचिन्हित दीर्घ दीर्घ ptr_करोwnsized = 0;
अचिन्हित दीर्घ दीर्घ val1_करोwnsized = 0;
अचिन्हित दीर्घ दीर्घ val2_करोwnsized = 0;
अचिन्हित दीर्घ दीर्घ val3_करोwnsized = 0;
अचिन्हित दीर्घ दीर्घ val4_करोwnsized = 0;
काष्ठा test_काष्ठा___real output_करोwnsized = अणुपूर्ण;

अचिन्हित दीर्घ दीर्घ ptr_probed = 0;
अचिन्हित दीर्घ दीर्घ val1_probed = 0;
अचिन्हित दीर्घ दीर्घ val2_probed = 0;
अचिन्हित दीर्घ दीर्घ val3_probed = 0;
अचिन्हित दीर्घ दीर्घ val4_probed = 0;

अचिन्हित दीर्घ दीर्घ ptr_चिन्हित = 0;
अचिन्हित दीर्घ दीर्घ val1_चिन्हित = 0;
अचिन्हित दीर्घ दीर्घ val2_चिन्हित = 0;
अचिन्हित दीर्घ दीर्घ val3_चिन्हित = 0;
अचिन्हित दीर्घ दीर्घ val4_चिन्हित = 0;
काष्ठा test_काष्ठा___real output_चिन्हित = अणुपूर्ण;

SEC("raw_tp/sys_exit")
पूर्णांक handle_samesize(व्योम *ctx)
अणु
	काष्ठा test_काष्ठा___samesize *in = (व्योम *)&input;
	काष्ठा test_काष्ठा___samesize *out = (व्योम *)&output_samesized;

	ptr_samesized = (अचिन्हित दीर्घ दीर्घ)in->ptr;
	val1_samesized = in->val1;
	val2_samesized = in->val2;
	val3_samesized = in->val3;
	val4_samesized = in->val4;

	out->ptr = in->ptr;
	out->val1 = in->val1;
	out->val2 = in->val2;
	out->val3 = in->val3;
	out->val4 = in->val4;

	वापस 0;
पूर्ण

SEC("raw_tp/sys_exit")
पूर्णांक handle_करोwnsize(व्योम *ctx)
अणु
	काष्ठा test_काष्ठा___करोwnsize *in = (व्योम *)&input;
	काष्ठा test_काष्ठा___करोwnsize *out = (व्योम *)&output_करोwnsized;

	ptr_करोwnsized = (अचिन्हित दीर्घ दीर्घ)in->ptr;
	val1_करोwnsized = in->val1;
	val2_करोwnsized = in->val2;
	val3_करोwnsized = in->val3;
	val4_करोwnsized = in->val4;

	out->ptr = in->ptr;
	out->val1 = in->val1;
	out->val2 = in->val2;
	out->val3 = in->val3;
	out->val4 = in->val4;

	वापस 0;
पूर्ण

SEC("raw_tp/sys_enter")
पूर्णांक handle_probed(व्योम *ctx)
अणु
	काष्ठा test_काष्ठा___करोwnsize *in = (व्योम *)&input;
	__u64 पंचांगp;

	पंचांगp = 0;
	bpf_core_पढ़ो(&पंचांगp, bpf_core_field_size(in->ptr), &in->ptr);
	ptr_probed = पंचांगp;

	पंचांगp = 0;
	bpf_core_पढ़ो(&पंचांगp, bpf_core_field_size(in->val1), &in->val1);
	val1_probed = पंचांगp;

	पंचांगp = 0;
	bpf_core_पढ़ो(&पंचांगp, bpf_core_field_size(in->val2), &in->val2);
	val2_probed = पंचांगp;

	पंचांगp = 0;
	bpf_core_पढ़ो(&पंचांगp, bpf_core_field_size(in->val3), &in->val3);
	val3_probed = पंचांगp;

	पंचांगp = 0;
	bpf_core_पढ़ो(&पंचांगp, bpf_core_field_size(in->val4), &in->val4);
	val4_probed = पंचांगp;

	वापस 0;
पूर्ण

SEC("raw_tp/sys_enter")
पूर्णांक handle_चिन्हित(व्योम *ctx)
अणु
	काष्ठा test_काष्ठा___चिन्हित *in = (व्योम *)&input;
	काष्ठा test_काष्ठा___चिन्हित *out = (व्योम *)&output_चिन्हित;

	val2_चिन्हित = in->val2;
	val3_चिन्हित = in->val3;
	val4_चिन्हित = in->val4;

	out->val2= in->val2;
	out->val3= in->val3;
	out->val4= in->val4;

	वापस 0;
पूर्ण
