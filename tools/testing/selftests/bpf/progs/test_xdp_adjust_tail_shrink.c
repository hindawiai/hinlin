<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018 Facebook
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_ether.h>
#समावेश <bpf/bpf_helpers.h>

पूर्णांक _version SEC("version") = 1;

SEC("xdp_adjust_tail_shrink")
पूर्णांक _xdp_adjust_tail_shrink(काष्ठा xdp_md *xdp)
अणु
	व्योम *data_end = (व्योम *)(दीर्घ)xdp->data_end;
	व्योम *data = (व्योम *)(दीर्घ)xdp->data;
	पूर्णांक offset = 0;

	अगर (data_end - data == 54) /* माप(pkt_v4) */
		offset = 256; /* shrink too much */
	अन्यथा
		offset = 20;
	अगर (bpf_xdp_adjust_tail(xdp, 0 - offset))
		वापस XDP_DROP;
	वापस XDP_TX;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
