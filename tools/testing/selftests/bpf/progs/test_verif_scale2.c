<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Facebook
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#घोषणा ATTR __always_अंतरभूत
#समावेश "test_jhash.h"

SEC("scale90_inline")
पूर्णांक balancer_ingress(काष्ठा __sk_buff *ctx)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)ctx->data_end;
	व्योम *data = (व्योम *)(दीर्घ)ctx->data;
	व्योम *ptr;
	पूर्णांक ret = 0, nh_off, i = 0;

	nh_off = 14;

	/* pragma unroll करोesn't work on large loops */

#घोषणा C करो अणु \
	ptr = data + i; \
	अगर (ptr + nh_off > data_end) \
		अवरोध; \
	ctx->tc_index = jhash(ptr, nh_off, ctx->cb[0] + i++); \
	पूर्ण जबतक (0);
#घोषणा C30 C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;C;
	C30;C30;C30; /* 90 calls */
	वापस 0;
पूर्ण
अक्षर _license[] SEC("license") = "GPL";
