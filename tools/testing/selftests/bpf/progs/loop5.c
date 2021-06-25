<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#घोषणा barrier() __यंत्र__ __अस्थिर__("": : :"memory")

अक्षर _license[] SEC("license") = "GPL";

SEC("socket")
पूर्णांक जबतक_true(अस्थिर काष्ठा __sk_buff* skb)
अणु
	पूर्णांक i = 0;

	जबतक (1) अणु
		अगर (skb->len)
			i += 3;
		अन्यथा
			i += 7;
		अगर (i == 9)
			अवरोध;
		barrier();
		अगर (i == 10)
			अवरोध;
		barrier();
		अगर (i == 13)
			अवरोध;
		barrier();
		अगर (i == 14)
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण
