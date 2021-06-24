<शैली गुरु>
/* Copyright (c) 2013-2015 PLUMgrid, http://plumgrid.com
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <uapi/linux/bpf.h>
#समावेश <linux/version.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

#घोषणा _(P)                                                                   \
	(अणु                                                                     \
		typeof(P) val = 0;                                             \
		bpf_probe_पढ़ो_kernel(&val, माप(val), &(P));                \
		val;                                                           \
	पूर्ण)

/* kprobe is NOT a stable ABI
 * kernel functions can be हटाओd, नामd or completely change semantics.
 * Number of arguments and their positions can change, etc.
 * In such हाल this bpf+kprobe example will no दीर्घer be meaningful
 */
SEC("kprobe/__netif_receive_skb_core")
पूर्णांक bpf_prog1(काष्ठा pt_regs *ctx)
अणु
	/* attaches to kprobe __netअगर_receive_skb_core,
	 * looks क्रम packets on loobpack device and prपूर्णांकs them
	 */
	अक्षर devname[IFNAMSIZ];
	काष्ठा net_device *dev;
	काष्ठा sk_buff *skb;
	पूर्णांक len;

	/* non-portable! works क्रम the given kernel only */
	bpf_probe_पढ़ो_kernel(&skb, माप(skb), (व्योम *)PT_REGS_PARM1(ctx));
	dev = _(skb->dev);
	len = _(skb->len);

	bpf_probe_पढ़ो_kernel(devname, माप(devname), dev->name);

	अगर (devname[0] == 'l' && devname[1] == 'o') अणु
		अक्षर fmt[] = "skb %p len %d\n";
		/* using bpf_trace_prपूर्णांकk() क्रम DEBUG ONLY */
		bpf_trace_prपूर्णांकk(fmt, माप(fmt), skb, len);
	पूर्ण

	वापस 0;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
u32 _version SEC("version") = LINUX_VERSION_CODE;
