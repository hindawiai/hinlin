<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

व्योम test_skb_helpers(व्योम)
अणु
	काष्ठा __sk_buff skb = अणु
		.wire_len = 100,
		.gso_segs = 8,
		.gso_size = 10,
	पूर्ण;
	काष्ठा bpf_prog_test_run_attr tattr = अणु
		.data_in = &pkt_v4,
		.data_size_in = माप(pkt_v4),
		.ctx_in = &skb,
		.ctx_size_in = माप(skb),
		.ctx_out = &skb,
		.ctx_size_out = माप(skb),
	पूर्ण;
	काष्ठा bpf_object *obj;
	पूर्णांक err;

	err = bpf_prog_load("./test_skb_helpers.o", BPF_PROG_TYPE_SCHED_CLS, &obj,
			    &tattr.prog_fd);
	अगर (CHECK_ATTR(err, "load", "err %d errno %d\n", err, त्रुटि_सं))
		वापस;
	err = bpf_prog_test_run_xattr(&tattr);
	CHECK_ATTR(err, "len", "err %d errno %d\n", err, त्रुटि_सं);
	bpf_object__बंद(obj);
पूर्ण
