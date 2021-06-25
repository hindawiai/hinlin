<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

SEC("xdp_adjust_tail_grow")
पूर्णांक _xdp_adjust_tail_grow(काष्ठा xdp_md *xdp)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)xdp->data_end;
	व्योम *data = (व्योम *)(दीर्घ)xdp->data;
	अचिन्हित पूर्णांक data_len;
	पूर्णांक offset = 0;

	/* Data length determine test हाल */
	data_len = data_end - data;

	अगर (data_len == 54) अणु /* माप(pkt_v4) */
		offset = 4096; /* test too large offset */
	पूर्ण अन्यथा अगर (data_len == 74) अणु /* माप(pkt_v6) */
		offset = 40;
	पूर्ण अन्यथा अगर (data_len == 64) अणु
		offset = 128;
	पूर्ण अन्यथा अगर (data_len == 128) अणु
		offset = 4096 - 256 - 320 - data_len; /* Max tail grow 3520 */
	पूर्ण अन्यथा अणु
		वापस XDP_ABORTED; /* No matching test */
	पूर्ण

	अगर (bpf_xdp_adjust_tail(xdp, offset))
		वापस XDP_DROP;
	वापस XDP_TX;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
