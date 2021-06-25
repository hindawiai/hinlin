<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#समावेश "bpf_iter.h"
#समावेश "bpf_tracing_net.h"
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

बाह्य bool CONFIG_IPV6_SUBTREES __kconfig __weak;

SEC("iter/ipv6_route")
पूर्णांक dump_ipv6_route(काष्ठा bpf_iter__ipv6_route *ctx)
अणु
	काष्ठा seq_file *seq = ctx->meta->seq;
	काष्ठा fib6_info *rt = ctx->rt;
	स्थिर काष्ठा net_device *dev;
	काष्ठा fib6_nh *fib6_nh;
	अचिन्हित पूर्णांक flags;
	काष्ठा nexthop *nh;

	अगर (rt == (व्योम *)0)
		वापस 0;

	fib6_nh = &rt->fib6_nh[0];
	flags = rt->fib6_flags;

	/* FIXME: nexthop_is_multipath is not handled here. */
	nh = rt->nh;
	अगर (rt->nh)
		fib6_nh = &nh->nh_info->fib6_nh;

	BPF_SEQ_PRINTF(seq, "%pi6 %02x ", &rt->fib6_dst.addr, rt->fib6_dst.plen);

	अगर (CONFIG_IPV6_SUBTREES)
		BPF_SEQ_PRINTF(seq, "%pi6 %02x ", &rt->fib6_src.addr,
			       rt->fib6_src.plen);
	अन्यथा
		BPF_SEQ_PRINTF(seq, "00000000000000000000000000000000 00 ");

	अगर (fib6_nh->fib_nh_gw_family) अणु
		flags |= RTF_GATEWAY;
		BPF_SEQ_PRINTF(seq, "%pi6 ", &fib6_nh->fib_nh_gw6);
	पूर्ण अन्यथा अणु
		BPF_SEQ_PRINTF(seq, "00000000000000000000000000000000 ");
	पूर्ण

	dev = fib6_nh->fib_nh_dev;
	अगर (dev)
		BPF_SEQ_PRINTF(seq, "%08x %08x %08x %08x %8s\n", rt->fib6_metric,
			       rt->fib6_ref.refs.counter, 0, flags, dev->name);
	अन्यथा
		BPF_SEQ_PRINTF(seq, "%08x %08x %08x %08x\n", rt->fib6_metric,
			       rt->fib6_ref.refs.counter, 0, flags);

	वापस 0;
पूर्ण
