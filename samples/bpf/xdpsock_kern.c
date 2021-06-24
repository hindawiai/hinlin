<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश "xdpsock.h"

/* This XDP program is only needed क्रम the XDP_SHARED_UMEM mode.
 * If you करो not use this mode, libbpf can supply an XDP program क्रम you.
 */

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_XSKMAP);
	__uपूर्णांक(max_entries, MAX_SOCKS);
	__uपूर्णांक(key_size, माप(पूर्णांक));
	__uपूर्णांक(value_size, माप(पूर्णांक));
पूर्ण xsks_map SEC(".maps");

अटल अचिन्हित पूर्णांक rr;

SEC("xdp_sock") पूर्णांक xdp_sock_prog(काष्ठा xdp_md *ctx)
अणु
	rr = (rr + 1) & (MAX_SOCKS - 1);

	वापस bpf_redirect_map(&xsks_map, rr, XDP_DROP);
पूर्ण
