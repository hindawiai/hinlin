<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश <network_helpers.h>

व्योम test_skb_ctx(व्योम)
अणु
	काष्ठा __sk_buff skb = अणु
		.cb[0] = 1,
		.cb[1] = 2,
		.cb[2] = 3,
		.cb[3] = 4,
		.cb[4] = 5,
		.priority = 6,
		.अगरindex = 1,
		.tstamp = 7,
		.wire_len = 100,
		.gso_segs = 8,
		.mark = 9,
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
	पूर्णांक i;

	err = bpf_prog_load("./test_skb_ctx.o", BPF_PROG_TYPE_SCHED_CLS, &obj,
			    &tattr.prog_fd);
	अगर (CHECK_ATTR(err, "load", "err %d errno %d\n", err, त्रुटि_सं))
		वापस;

	/* ctx_in != शून्य, ctx_size_in == 0 */

	tattr.ctx_size_in = 0;
	err = bpf_prog_test_run_xattr(&tattr);
	CHECK_ATTR(err == 0, "ctx_size_in", "err %d errno %d\n", err, त्रुटि_सं);
	tattr.ctx_size_in = माप(skb);

	/* ctx_out != शून्य, ctx_size_out == 0 */

	tattr.ctx_size_out = 0;
	err = bpf_prog_test_run_xattr(&tattr);
	CHECK_ATTR(err == 0, "ctx_size_out", "err %d errno %d\n", err, त्रुटि_सं);
	tattr.ctx_size_out = माप(skb);

	/* non-zero [len, tc_index] fields should be rejected*/

	skb.len = 1;
	err = bpf_prog_test_run_xattr(&tattr);
	CHECK_ATTR(err == 0, "len", "err %d errno %d\n", err, त्रुटि_सं);
	skb.len = 0;

	skb.tc_index = 1;
	err = bpf_prog_test_run_xattr(&tattr);
	CHECK_ATTR(err == 0, "tc_index", "err %d errno %d\n", err, त्रुटि_सं);
	skb.tc_index = 0;

	/* non-zero [hash, sk] fields should be rejected */

	skb.hash = 1;
	err = bpf_prog_test_run_xattr(&tattr);
	CHECK_ATTR(err == 0, "hash", "err %d errno %d\n", err, त्रुटि_सं);
	skb.hash = 0;

	skb.sk = (काष्ठा bpf_sock *)1;
	err = bpf_prog_test_run_xattr(&tattr);
	CHECK_ATTR(err == 0, "sk", "err %d errno %d\n", err, त्रुटि_सं);
	skb.sk = 0;

	err = bpf_prog_test_run_xattr(&tattr);
	CHECK_ATTR(err != 0 || tattr.retval,
		   "run",
		   "err %d errno %d retval %d\n",
		   err, त्रुटि_सं, tattr.retval);

	CHECK_ATTR(tattr.ctx_size_out != माप(skb),
		   "ctx_size_out",
		   "incorrect output size, want %zu have %u\n",
		   माप(skb), tattr.ctx_size_out);

	क्रम (i = 0; i < 5; i++)
		CHECK_ATTR(skb.cb[i] != i + 2,
			   "ctx_out_cb",
			   "skb->cb[i] == %d, expected %d\n",
			   skb.cb[i], i + 2);
	CHECK_ATTR(skb.priority != 7,
		   "ctx_out_priority",
		   "skb->priority == %d, expected %d\n",
		   skb.priority, 7);
	CHECK_ATTR(skb.अगरindex != 1,
		   "ctx_out_ifindex",
		   "skb->ifindex == %d, expected %d\n",
		   skb.अगरindex, 1);
	CHECK_ATTR(skb.tstamp != 8,
		   "ctx_out_tstamp",
		   "skb->tstamp == %lld, expected %d\n",
		   skb.tstamp, 8);
	CHECK_ATTR(skb.mark != 10,
		   "ctx_out_mark",
		   "skb->mark == %u, expected %d\n",
		   skb.mark, 10);
पूर्ण
