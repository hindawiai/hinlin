<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux Socket Filter - Kernel level socket filtering
 *
 * Based on the design of the Berkeley Packet Filter. The new
 * पूर्णांकernal क्रमmat has been deचिन्हित by PLUMgrid:
 *
 *	Copyright (c) 2011 - 2014 PLUMgrid, http://plumgrid.com
 *
 * Authors:
 *
 *	Jay Schulist <jschlst@samba.org>
 *	Alexei Starovoitov <ast@plumgrid.com>
 *	Daniel Borkmann <dborkman@redhat.com>
 *
 * Andi Kleen - Fix a few bad bugs and races.
 * Kris Katterjohn - Added many additional checks in bpf_check_classic()
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/socket.h>
#समावेश <linux/sock_diag.h>
#समावेश <linux/in.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/gfp.h>
#समावेश <net/inet_common.h>
#समावेश <net/ip.h>
#समावेश <net/protocol.h>
#समावेश <net/netlink.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/skmsg.h>
#समावेश <net/sock.h>
#समावेश <net/flow_dissector.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/समयr.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <linux/filter.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/bpf.h>
#समावेश <linux/btf.h>
#समावेश <net/sch_generic.h>
#समावेश <net/cls_cgroup.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/dst.h>
#समावेश <net/sock_reuseport.h>
#समावेश <net/busy_poll.h>
#समावेश <net/tcp.h>
#समावेश <net/xfrm.h>
#समावेश <net/udp.h>
#समावेश <linux/bpf_trace.h>
#समावेश <net/xdp_sock.h>
#समावेश <linux/inetdevice.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/inet6_hashtables.h>
#समावेश <net/ip_fib.h>
#समावेश <net/nexthop.h>
#समावेश <net/flow.h>
#समावेश <net/arp.h>
#समावेश <net/ipv6.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/seg6_local.h>
#समावेश <net/seg6.h>
#समावेश <net/seg6_local.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/ipv6_stubs.h>
#समावेश <net/bpf_sk_storage.h>
#समावेश <net/transp_v6.h>
#समावेश <linux/btf_ids.h>
#समावेश <net/tls.h>

अटल स्थिर काष्ठा bpf_func_proto *
bpf_sk_base_func_proto(क्रमागत bpf_func_id func_id);

पूर्णांक copy_bpf_fprog_from_user(काष्ठा sock_fprog *dst, sockptr_t src, पूर्णांक len)
अणु
	अगर (in_compat_syscall()) अणु
		काष्ठा compat_sock_fprog f32;

		अगर (len != माप(f32))
			वापस -EINVAL;
		अगर (copy_from_sockptr(&f32, src, माप(f32)))
			वापस -EFAULT;
		स_रखो(dst, 0, माप(*dst));
		dst->len = f32.len;
		dst->filter = compat_ptr(f32.filter);
	पूर्ण अन्यथा अणु
		अगर (len != माप(*dst))
			वापस -EINVAL;
		अगर (copy_from_sockptr(dst, src, माप(*dst)))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(copy_bpf_fprog_from_user);

/**
 *	sk_filter_trim_cap - run a packet through a socket filter
 *	@sk: sock associated with &sk_buff
 *	@skb: buffer to filter
 *	@cap: limit on how लघु the eBPF program may trim the packet
 *
 * Run the eBPF program and then cut skb->data to correct size वापसed by
 * the program. If pkt_len is 0 we toss packet. If skb->len is smaller
 * than pkt_len we keep whole skb->data. This is the socket level
 * wrapper to BPF_PROG_RUN. It वापसs 0 अगर the packet should
 * be accepted or -EPERM अगर the packet should be tossed.
 *
 */
पूर्णांक sk_filter_trim_cap(काष्ठा sock *sk, काष्ठा sk_buff *skb, अचिन्हित पूर्णांक cap)
अणु
	पूर्णांक err;
	काष्ठा sk_filter *filter;

	/*
	 * If the skb was allocated from pfmeदो_स्मृति reserves, only
	 * allow SOCK_MEMALLOC sockets to use it as this socket is
	 * helping मुक्त memory
	 */
	अगर (skb_pfmeदो_स्मृति(skb) && !sock_flag(sk, SOCK_MEMALLOC)) अणु
		NET_INC_STATS(sock_net(sk), LINUX_MIB_PFMEMALLOCDROP);
		वापस -ENOMEM;
	पूर्ण
	err = BPF_CGROUP_RUN_PROG_INET_INGRESS(sk, skb);
	अगर (err)
		वापस err;

	err = security_sock_rcv_skb(sk, skb);
	अगर (err)
		वापस err;

	rcu_पढ़ो_lock();
	filter = rcu_dereference(sk->sk_filter);
	अगर (filter) अणु
		काष्ठा sock *save_sk = skb->sk;
		अचिन्हित पूर्णांक pkt_len;

		skb->sk = sk;
		pkt_len = bpf_prog_run_save_cb(filter->prog, skb);
		skb->sk = save_sk;
		err = pkt_len ? pskb_trim(skb, max(cap, pkt_len)) : -EPERM;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण
EXPORT_SYMBOL(sk_filter_trim_cap);

BPF_CALL_1(bpf_skb_get_pay_offset, काष्ठा sk_buff *, skb)
अणु
	वापस skb_get_poff(skb);
पूर्ण

BPF_CALL_3(bpf_skb_get_nlattr, काष्ठा sk_buff *, skb, u32, a, u32, x)
अणु
	काष्ठा nlattr *nla;

	अगर (skb_is_nonlinear(skb))
		वापस 0;

	अगर (skb->len < माप(काष्ठा nlattr))
		वापस 0;

	अगर (a > skb->len - माप(काष्ठा nlattr))
		वापस 0;

	nla = nla_find((काष्ठा nlattr *) &skb->data[a], skb->len - a, x);
	अगर (nla)
		वापस (व्योम *) nla - (व्योम *) skb->data;

	वापस 0;
पूर्ण

BPF_CALL_3(bpf_skb_get_nlattr_nest, काष्ठा sk_buff *, skb, u32, a, u32, x)
अणु
	काष्ठा nlattr *nla;

	अगर (skb_is_nonlinear(skb))
		वापस 0;

	अगर (skb->len < माप(काष्ठा nlattr))
		वापस 0;

	अगर (a > skb->len - माप(काष्ठा nlattr))
		वापस 0;

	nla = (काष्ठा nlattr *) &skb->data[a];
	अगर (nla->nla_len > skb->len - a)
		वापस 0;

	nla = nla_find_nested(nla, x);
	अगर (nla)
		वापस (व्योम *) nla - (व्योम *) skb->data;

	वापस 0;
पूर्ण

BPF_CALL_4(bpf_skb_load_helper_8, स्थिर काष्ठा sk_buff *, skb, स्थिर व्योम *,
	   data, पूर्णांक, headlen, पूर्णांक, offset)
अणु
	u8 पंचांगp, *ptr;
	स्थिर पूर्णांक len = माप(पंचांगp);

	अगर (offset >= 0) अणु
		अगर (headlen - offset >= len)
			वापस *(u8 *)(data + offset);
		अगर (!skb_copy_bits(skb, offset, &पंचांगp, माप(पंचांगp)))
			वापस पंचांगp;
	पूर्ण अन्यथा अणु
		ptr = bpf_पूर्णांकernal_load_poपूर्णांकer_neg_helper(skb, offset, len);
		अगर (likely(ptr))
			वापस *(u8 *)ptr;
	पूर्ण

	वापस -EFAULT;
पूर्ण

BPF_CALL_2(bpf_skb_load_helper_8_no_cache, स्थिर काष्ठा sk_buff *, skb,
	   पूर्णांक, offset)
अणु
	वापस ____bpf_skb_load_helper_8(skb, skb->data, skb->len - skb->data_len,
					 offset);
पूर्ण

BPF_CALL_4(bpf_skb_load_helper_16, स्थिर काष्ठा sk_buff *, skb, स्थिर व्योम *,
	   data, पूर्णांक, headlen, पूर्णांक, offset)
अणु
	u16 पंचांगp, *ptr;
	स्थिर पूर्णांक len = माप(पंचांगp);

	अगर (offset >= 0) अणु
		अगर (headlen - offset >= len)
			वापस get_unaligned_be16(data + offset);
		अगर (!skb_copy_bits(skb, offset, &पंचांगp, माप(पंचांगp)))
			वापस be16_to_cpu(पंचांगp);
	पूर्ण अन्यथा अणु
		ptr = bpf_पूर्णांकernal_load_poपूर्णांकer_neg_helper(skb, offset, len);
		अगर (likely(ptr))
			वापस get_unaligned_be16(ptr);
	पूर्ण

	वापस -EFAULT;
पूर्ण

BPF_CALL_2(bpf_skb_load_helper_16_no_cache, स्थिर काष्ठा sk_buff *, skb,
	   पूर्णांक, offset)
अणु
	वापस ____bpf_skb_load_helper_16(skb, skb->data, skb->len - skb->data_len,
					  offset);
पूर्ण

BPF_CALL_4(bpf_skb_load_helper_32, स्थिर काष्ठा sk_buff *, skb, स्थिर व्योम *,
	   data, पूर्णांक, headlen, पूर्णांक, offset)
अणु
	u32 पंचांगp, *ptr;
	स्थिर पूर्णांक len = माप(पंचांगp);

	अगर (likely(offset >= 0)) अणु
		अगर (headlen - offset >= len)
			वापस get_unaligned_be32(data + offset);
		अगर (!skb_copy_bits(skb, offset, &पंचांगp, माप(पंचांगp)))
			वापस be32_to_cpu(पंचांगp);
	पूर्ण अन्यथा अणु
		ptr = bpf_पूर्णांकernal_load_poपूर्णांकer_neg_helper(skb, offset, len);
		अगर (likely(ptr))
			वापस get_unaligned_be32(ptr);
	पूर्ण

	वापस -EFAULT;
पूर्ण

BPF_CALL_2(bpf_skb_load_helper_32_no_cache, स्थिर काष्ठा sk_buff *, skb,
	   पूर्णांक, offset)
अणु
	वापस ____bpf_skb_load_helper_32(skb, skb->data, skb->len - skb->data_len,
					  offset);
पूर्ण

अटल u32 convert_skb_access(पूर्णांक skb_field, पूर्णांक dst_reg, पूर्णांक src_reg,
			      काष्ठा bpf_insn *insn_buf)
अणु
	काष्ठा bpf_insn *insn = insn_buf;

	चयन (skb_field) अणु
	हाल SKF_AD_MARK:
		BUILD_BUG_ON(माप_field(काष्ठा sk_buff, mark) != 4);

		*insn++ = BPF_LDX_MEM(BPF_W, dst_reg, src_reg,
				      दुरत्व(काष्ठा sk_buff, mark));
		अवरोध;

	हाल SKF_AD_PKTTYPE:
		*insn++ = BPF_LDX_MEM(BPF_B, dst_reg, src_reg, PKT_TYPE_OFFSET());
		*insn++ = BPF_ALU32_IMM(BPF_AND, dst_reg, PKT_TYPE_MAX);
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		*insn++ = BPF_ALU32_IMM(BPF_RSH, dst_reg, 5);
#पूर्ण_अगर
		अवरोध;

	हाल SKF_AD_QUEUE:
		BUILD_BUG_ON(माप_field(काष्ठा sk_buff, queue_mapping) != 2);

		*insn++ = BPF_LDX_MEM(BPF_H, dst_reg, src_reg,
				      दुरत्व(काष्ठा sk_buff, queue_mapping));
		अवरोध;

	हाल SKF_AD_VLAN_TAG:
		BUILD_BUG_ON(माप_field(काष्ठा sk_buff, vlan_tci) != 2);

		/* dst_reg = *(u16 *) (src_reg + दुरत्व(vlan_tci)) */
		*insn++ = BPF_LDX_MEM(BPF_H, dst_reg, src_reg,
				      दुरत्व(काष्ठा sk_buff, vlan_tci));
		अवरोध;
	हाल SKF_AD_VLAN_TAG_PRESENT:
		*insn++ = BPF_LDX_MEM(BPF_B, dst_reg, src_reg, PKT_VLAN_PRESENT_OFFSET());
		अगर (PKT_VLAN_PRESENT_BIT)
			*insn++ = BPF_ALU32_IMM(BPF_RSH, dst_reg, PKT_VLAN_PRESENT_BIT);
		अगर (PKT_VLAN_PRESENT_BIT < 7)
			*insn++ = BPF_ALU32_IMM(BPF_AND, dst_reg, 1);
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

अटल bool convert_bpf_extensions(काष्ठा sock_filter *fp,
				   काष्ठा bpf_insn **insnp)
अणु
	काष्ठा bpf_insn *insn = *insnp;
	u32 cnt;

	चयन (fp->k) अणु
	हाल SKF_AD_OFF + SKF_AD_PROTOCOL:
		BUILD_BUG_ON(माप_field(काष्ठा sk_buff, protocol) != 2);

		/* A = *(u16 *) (CTX + दुरत्व(protocol)) */
		*insn++ = BPF_LDX_MEM(BPF_H, BPF_REG_A, BPF_REG_CTX,
				      दुरत्व(काष्ठा sk_buff, protocol));
		/* A = ntohs(A) [emitting a nop or swap16] */
		*insn = BPF_ENDIAN(BPF_FROM_BE, BPF_REG_A, 16);
		अवरोध;

	हाल SKF_AD_OFF + SKF_AD_PKTTYPE:
		cnt = convert_skb_access(SKF_AD_PKTTYPE, BPF_REG_A, BPF_REG_CTX, insn);
		insn += cnt - 1;
		अवरोध;

	हाल SKF_AD_OFF + SKF_AD_IFINDEX:
	हाल SKF_AD_OFF + SKF_AD_HATYPE:
		BUILD_BUG_ON(माप_field(काष्ठा net_device, अगरindex) != 4);
		BUILD_BUG_ON(माप_field(काष्ठा net_device, type) != 2);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, dev),
				      BPF_REG_TMP, BPF_REG_CTX,
				      दुरत्व(काष्ठा sk_buff, dev));
		/* अगर (पंचांगp != 0) जाओ pc + 1 */
		*insn++ = BPF_JMP_IMM(BPF_JNE, BPF_REG_TMP, 0, 1);
		*insn++ = BPF_EXIT_INSN();
		अगर (fp->k == SKF_AD_OFF + SKF_AD_IFINDEX)
			*insn = BPF_LDX_MEM(BPF_W, BPF_REG_A, BPF_REG_TMP,
					    दुरत्व(काष्ठा net_device, अगरindex));
		अन्यथा
			*insn = BPF_LDX_MEM(BPF_H, BPF_REG_A, BPF_REG_TMP,
					    दुरत्व(काष्ठा net_device, type));
		अवरोध;

	हाल SKF_AD_OFF + SKF_AD_MARK:
		cnt = convert_skb_access(SKF_AD_MARK, BPF_REG_A, BPF_REG_CTX, insn);
		insn += cnt - 1;
		अवरोध;

	हाल SKF_AD_OFF + SKF_AD_RXHASH:
		BUILD_BUG_ON(माप_field(काष्ठा sk_buff, hash) != 4);

		*insn = BPF_LDX_MEM(BPF_W, BPF_REG_A, BPF_REG_CTX,
				    दुरत्व(काष्ठा sk_buff, hash));
		अवरोध;

	हाल SKF_AD_OFF + SKF_AD_QUEUE:
		cnt = convert_skb_access(SKF_AD_QUEUE, BPF_REG_A, BPF_REG_CTX, insn);
		insn += cnt - 1;
		अवरोध;

	हाल SKF_AD_OFF + SKF_AD_VLAN_TAG:
		cnt = convert_skb_access(SKF_AD_VLAN_TAG,
					 BPF_REG_A, BPF_REG_CTX, insn);
		insn += cnt - 1;
		अवरोध;

	हाल SKF_AD_OFF + SKF_AD_VLAN_TAG_PRESENT:
		cnt = convert_skb_access(SKF_AD_VLAN_TAG_PRESENT,
					 BPF_REG_A, BPF_REG_CTX, insn);
		insn += cnt - 1;
		अवरोध;

	हाल SKF_AD_OFF + SKF_AD_VLAN_TPID:
		BUILD_BUG_ON(माप_field(काष्ठा sk_buff, vlan_proto) != 2);

		/* A = *(u16 *) (CTX + दुरत्व(vlan_proto)) */
		*insn++ = BPF_LDX_MEM(BPF_H, BPF_REG_A, BPF_REG_CTX,
				      दुरत्व(काष्ठा sk_buff, vlan_proto));
		/* A = ntohs(A) [emitting a nop or swap16] */
		*insn = BPF_ENDIAN(BPF_FROM_BE, BPF_REG_A, 16);
		अवरोध;

	हाल SKF_AD_OFF + SKF_AD_PAY_OFFSET:
	हाल SKF_AD_OFF + SKF_AD_NLATTR:
	हाल SKF_AD_OFF + SKF_AD_NLATTR_NEST:
	हाल SKF_AD_OFF + SKF_AD_CPU:
	हाल SKF_AD_OFF + SKF_AD_RANDOM:
		/* arg1 = CTX */
		*insn++ = BPF_MOV64_REG(BPF_REG_ARG1, BPF_REG_CTX);
		/* arg2 = A */
		*insn++ = BPF_MOV64_REG(BPF_REG_ARG2, BPF_REG_A);
		/* arg3 = X */
		*insn++ = BPF_MOV64_REG(BPF_REG_ARG3, BPF_REG_X);
		/* Emit call(arg1=CTX, arg2=A, arg3=X) */
		चयन (fp->k) अणु
		हाल SKF_AD_OFF + SKF_AD_PAY_OFFSET:
			*insn = BPF_EMIT_CALL(bpf_skb_get_pay_offset);
			अवरोध;
		हाल SKF_AD_OFF + SKF_AD_NLATTR:
			*insn = BPF_EMIT_CALL(bpf_skb_get_nlattr);
			अवरोध;
		हाल SKF_AD_OFF + SKF_AD_NLATTR_NEST:
			*insn = BPF_EMIT_CALL(bpf_skb_get_nlattr_nest);
			अवरोध;
		हाल SKF_AD_OFF + SKF_AD_CPU:
			*insn = BPF_EMIT_CALL(bpf_get_raw_cpu_id);
			अवरोध;
		हाल SKF_AD_OFF + SKF_AD_RANDOM:
			*insn = BPF_EMIT_CALL(bpf_user_rnd_u32);
			bpf_user_rnd_init_once();
			अवरोध;
		पूर्ण
		अवरोध;

	हाल SKF_AD_OFF + SKF_AD_ALU_XOR_X:
		/* A ^= X */
		*insn = BPF_ALU32_REG(BPF_XOR, BPF_REG_A, BPF_REG_X);
		अवरोध;

	शेष:
		/* This is just a dummy call to aव्योम letting the compiler
		 * evict __bpf_call_base() as an optimization. Placed here
		 * where no-one bothers.
		 */
		BUG_ON(__bpf_call_base(0, 0, 0, 0, 0) != 0);
		वापस false;
	पूर्ण

	*insnp = insn;
	वापस true;
पूर्ण

अटल bool convert_bpf_ld_असल(काष्ठा sock_filter *fp, काष्ठा bpf_insn **insnp)
अणु
	स्थिर bool unaligned_ok = IS_BUILTIN(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS);
	पूर्णांक size = bpf_माप_प्रकारo_bytes(BPF_SIZE(fp->code));
	bool endian = BPF_SIZE(fp->code) == BPF_H ||
		      BPF_SIZE(fp->code) == BPF_W;
	bool indirect = BPF_MODE(fp->code) == BPF_IND;
	स्थिर पूर्णांक ip_align = NET_IP_ALIGN;
	काष्ठा bpf_insn *insn = *insnp;
	पूर्णांक offset = fp->k;

	अगर (!indirect &&
	    ((unaligned_ok && offset >= 0) ||
	     (!unaligned_ok && offset >= 0 &&
	      offset + ip_align >= 0 &&
	      offset + ip_align % size == 0))) अणु
		bool ldx_off_ok = offset <= S16_MAX;

		*insn++ = BPF_MOV64_REG(BPF_REG_TMP, BPF_REG_H);
		अगर (offset)
			*insn++ = BPF_ALU64_IMM(BPF_SUB, BPF_REG_TMP, offset);
		*insn++ = BPF_JMP_IMM(BPF_JSLT, BPF_REG_TMP,
				      size, 2 + endian + (!ldx_off_ok * 2));
		अगर (ldx_off_ok) अणु
			*insn++ = BPF_LDX_MEM(BPF_SIZE(fp->code), BPF_REG_A,
					      BPF_REG_D, offset);
		पूर्ण अन्यथा अणु
			*insn++ = BPF_MOV64_REG(BPF_REG_TMP, BPF_REG_D);
			*insn++ = BPF_ALU64_IMM(BPF_ADD, BPF_REG_TMP, offset);
			*insn++ = BPF_LDX_MEM(BPF_SIZE(fp->code), BPF_REG_A,
					      BPF_REG_TMP, 0);
		पूर्ण
		अगर (endian)
			*insn++ = BPF_ENDIAN(BPF_FROM_BE, BPF_REG_A, size * 8);
		*insn++ = BPF_JMP_A(8);
	पूर्ण

	*insn++ = BPF_MOV64_REG(BPF_REG_ARG1, BPF_REG_CTX);
	*insn++ = BPF_MOV64_REG(BPF_REG_ARG2, BPF_REG_D);
	*insn++ = BPF_MOV64_REG(BPF_REG_ARG3, BPF_REG_H);
	अगर (!indirect) अणु
		*insn++ = BPF_MOV64_IMM(BPF_REG_ARG4, offset);
	पूर्ण अन्यथा अणु
		*insn++ = BPF_MOV64_REG(BPF_REG_ARG4, BPF_REG_X);
		अगर (fp->k)
			*insn++ = BPF_ALU64_IMM(BPF_ADD, BPF_REG_ARG4, offset);
	पूर्ण

	चयन (BPF_SIZE(fp->code)) अणु
	हाल BPF_B:
		*insn++ = BPF_EMIT_CALL(bpf_skb_load_helper_8);
		अवरोध;
	हाल BPF_H:
		*insn++ = BPF_EMIT_CALL(bpf_skb_load_helper_16);
		अवरोध;
	हाल BPF_W:
		*insn++ = BPF_EMIT_CALL(bpf_skb_load_helper_32);
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	*insn++ = BPF_JMP_IMM(BPF_JSGE, BPF_REG_A, 0, 2);
	*insn++ = BPF_ALU32_REG(BPF_XOR, BPF_REG_A, BPF_REG_A);
	*insn   = BPF_EXIT_INSN();

	*insnp = insn;
	वापस true;
पूर्ण

/**
 *	bpf_convert_filter - convert filter program
 *	@prog: the user passed filter program
 *	@len: the length of the user passed filter program
 *	@new_prog: allocated 'struct bpf_prog' or शून्य
 *	@new_len: poपूर्णांकer to store length of converted program
 *	@seen_ld_असल: bool whether we've seen ld_असल/ind
 *
 * Remap 'sock_filter' style classic BPF (cBPF) instruction set to 'bpf_insn'
 * style extended BPF (eBPF).
 * Conversion workflow:
 *
 * 1) First pass क्रम calculating the new program length:
 *   bpf_convert_filter(old_prog, old_len, शून्य, &new_len, &seen_ld_असल)
 *
 * 2) 2nd pass to remap in two passes: 1st pass finds new
 *    jump offsets, 2nd pass remapping:
 *   bpf_convert_filter(old_prog, old_len, new_prog, &new_len, &seen_ld_असल)
 */
अटल पूर्णांक bpf_convert_filter(काष्ठा sock_filter *prog, पूर्णांक len,
			      काष्ठा bpf_prog *new_prog, पूर्णांक *new_len,
			      bool *seen_ld_असल)
अणु
	पूर्णांक new_flen = 0, pass = 0, target, i, stack_off;
	काष्ठा bpf_insn *new_insn, *first_insn = शून्य;
	काष्ठा sock_filter *fp;
	पूर्णांक *addrs = शून्य;
	u8 bpf_src;

	BUILD_BUG_ON(BPF_MEMWORDS * माप(u32) > MAX_BPF_STACK);
	BUILD_BUG_ON(BPF_REG_FP + 1 != MAX_BPF_REG);

	अगर (len <= 0 || len > BPF_MAXINSNS)
		वापस -EINVAL;

	अगर (new_prog) अणु
		first_insn = new_prog->insnsi;
		addrs = kसुस्मृति(len, माप(*addrs),
				GFP_KERNEL | __GFP_NOWARN);
		अगर (!addrs)
			वापस -ENOMEM;
	पूर्ण

करो_pass:
	new_insn = first_insn;
	fp = prog;

	/* Classic BPF related prologue emission. */
	अगर (new_prog) अणु
		/* Classic BPF expects A and X to be reset first. These need
		 * to be guaranteed to be the first two inकाष्ठाions.
		 */
		*new_insn++ = BPF_ALU32_REG(BPF_XOR, BPF_REG_A, BPF_REG_A);
		*new_insn++ = BPF_ALU32_REG(BPF_XOR, BPF_REG_X, BPF_REG_X);

		/* All programs must keep CTX in callee saved BPF_REG_CTX.
		 * In eBPF हाल it's करोne by the compiler, here we need to
		 * करो this ourself. Initial CTX is present in BPF_REG_ARG1.
		 */
		*new_insn++ = BPF_MOV64_REG(BPF_REG_CTX, BPF_REG_ARG1);
		अगर (*seen_ld_असल) अणु
			/* For packet access in classic BPF, cache skb->data
			 * in callee-saved BPF R8 and skb->len - skb->data_len
			 * (headlen) in BPF R9. Since classic BPF is पढ़ो-only
			 * on CTX, we only need to cache it once.
			 */
			*new_insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, data),
						  BPF_REG_D, BPF_REG_CTX,
						  दुरत्व(काष्ठा sk_buff, data));
			*new_insn++ = BPF_LDX_MEM(BPF_W, BPF_REG_H, BPF_REG_CTX,
						  दुरत्व(काष्ठा sk_buff, len));
			*new_insn++ = BPF_LDX_MEM(BPF_W, BPF_REG_TMP, BPF_REG_CTX,
						  दुरत्व(काष्ठा sk_buff, data_len));
			*new_insn++ = BPF_ALU32_REG(BPF_SUB, BPF_REG_H, BPF_REG_TMP);
		पूर्ण
	पूर्ण अन्यथा अणु
		new_insn += 3;
	पूर्ण

	क्रम (i = 0; i < len; fp++, i++) अणु
		काष्ठा bpf_insn पंचांगp_insns[32] = अणु पूर्ण;
		काष्ठा bpf_insn *insn = पंचांगp_insns;

		अगर (addrs)
			addrs[i] = new_insn - first_insn;

		चयन (fp->code) अणु
		/* All arithmetic insns and skb loads map as-is. */
		हाल BPF_ALU | BPF_ADD | BPF_X:
		हाल BPF_ALU | BPF_ADD | BPF_K:
		हाल BPF_ALU | BPF_SUB | BPF_X:
		हाल BPF_ALU | BPF_SUB | BPF_K:
		हाल BPF_ALU | BPF_AND | BPF_X:
		हाल BPF_ALU | BPF_AND | BPF_K:
		हाल BPF_ALU | BPF_OR | BPF_X:
		हाल BPF_ALU | BPF_OR | BPF_K:
		हाल BPF_ALU | BPF_LSH | BPF_X:
		हाल BPF_ALU | BPF_LSH | BPF_K:
		हाल BPF_ALU | BPF_RSH | BPF_X:
		हाल BPF_ALU | BPF_RSH | BPF_K:
		हाल BPF_ALU | BPF_XOR | BPF_X:
		हाल BPF_ALU | BPF_XOR | BPF_K:
		हाल BPF_ALU | BPF_MUL | BPF_X:
		हाल BPF_ALU | BPF_MUL | BPF_K:
		हाल BPF_ALU | BPF_DIV | BPF_X:
		हाल BPF_ALU | BPF_DIV | BPF_K:
		हाल BPF_ALU | BPF_MOD | BPF_X:
		हाल BPF_ALU | BPF_MOD | BPF_K:
		हाल BPF_ALU | BPF_NEG:
		हाल BPF_LD | BPF_ABS | BPF_W:
		हाल BPF_LD | BPF_ABS | BPF_H:
		हाल BPF_LD | BPF_ABS | BPF_B:
		हाल BPF_LD | BPF_IND | BPF_W:
		हाल BPF_LD | BPF_IND | BPF_H:
		हाल BPF_LD | BPF_IND | BPF_B:
			/* Check क्रम overloaded BPF extension and
			 * directly convert it अगर found, otherwise
			 * just move on with mapping.
			 */
			अगर (BPF_CLASS(fp->code) == BPF_LD &&
			    BPF_MODE(fp->code) == BPF_ABS &&
			    convert_bpf_extensions(fp, &insn))
				अवरोध;
			अगर (BPF_CLASS(fp->code) == BPF_LD &&
			    convert_bpf_ld_असल(fp, &insn)) अणु
				*seen_ld_असल = true;
				अवरोध;
			पूर्ण

			अगर (fp->code == (BPF_ALU | BPF_DIV | BPF_X) ||
			    fp->code == (BPF_ALU | BPF_MOD | BPF_X)) अणु
				*insn++ = BPF_MOV32_REG(BPF_REG_X, BPF_REG_X);
				/* Error with exception code on भाग/mod by 0.
				 * For cBPF programs, this was always वापस 0.
				 */
				*insn++ = BPF_JMP_IMM(BPF_JNE, BPF_REG_X, 0, 2);
				*insn++ = BPF_ALU32_REG(BPF_XOR, BPF_REG_A, BPF_REG_A);
				*insn++ = BPF_EXIT_INSN();
			पूर्ण

			*insn = BPF_RAW_INSN(fp->code, BPF_REG_A, BPF_REG_X, 0, fp->k);
			अवरोध;

		/* Jump transक्रमmation cannot use BPF block macros
		 * everywhere as offset calculation and target updates
		 * require a bit more work than the rest, i.e. jump
		 * opcodes map as-is, but offsets need adjusपंचांगent.
		 */

#घोषणा BPF_EMIT_JMP							\
	करो अणु								\
		स्थिर s32 off_min = S16_MIN, off_max = S16_MAX;		\
		s32 off;						\
									\
		अगर (target >= len || target < 0)			\
			जाओ err;					\
		off = addrs ? addrs[target] - addrs[i] - 1 : 0;		\
		/* Adjust pc relative offset क्रम 2nd or 3rd insn. */	\
		off -= insn - पंचांगp_insns;				\
		/* Reject anything not fitting पूर्णांकo insn->off. */	\
		अगर (off < off_min || off > off_max)			\
			जाओ err;					\
		insn->off = off;					\
	पूर्ण जबतक (0)

		हाल BPF_JMP | BPF_JA:
			target = i + fp->k + 1;
			insn->code = fp->code;
			BPF_EMIT_JMP;
			अवरोध;

		हाल BPF_JMP | BPF_JEQ | BPF_K:
		हाल BPF_JMP | BPF_JEQ | BPF_X:
		हाल BPF_JMP | BPF_JSET | BPF_K:
		हाल BPF_JMP | BPF_JSET | BPF_X:
		हाल BPF_JMP | BPF_JGT | BPF_K:
		हाल BPF_JMP | BPF_JGT | BPF_X:
		हाल BPF_JMP | BPF_JGE | BPF_K:
		हाल BPF_JMP | BPF_JGE | BPF_X:
			अगर (BPF_SRC(fp->code) == BPF_K && (पूर्णांक) fp->k < 0) अणु
				/* BPF immediates are चिन्हित, zero extend
				 * immediate पूर्णांकo पंचांगp रेजिस्टर and use it
				 * in compare insn.
				 */
				*insn++ = BPF_MOV32_IMM(BPF_REG_TMP, fp->k);

				insn->dst_reg = BPF_REG_A;
				insn->src_reg = BPF_REG_TMP;
				bpf_src = BPF_X;
			पूर्ण अन्यथा अणु
				insn->dst_reg = BPF_REG_A;
				insn->imm = fp->k;
				bpf_src = BPF_SRC(fp->code);
				insn->src_reg = bpf_src == BPF_X ? BPF_REG_X : 0;
			पूर्ण

			/* Common हाल where 'jump_false' is next insn. */
			अगर (fp->jf == 0) अणु
				insn->code = BPF_JMP | BPF_OP(fp->code) | bpf_src;
				target = i + fp->jt + 1;
				BPF_EMIT_JMP;
				अवरोध;
			पूर्ण

			/* Convert some jumps when 'jump_true' is next insn. */
			अगर (fp->jt == 0) अणु
				चयन (BPF_OP(fp->code)) अणु
				हाल BPF_JEQ:
					insn->code = BPF_JMP | BPF_JNE | bpf_src;
					अवरोध;
				हाल BPF_JGT:
					insn->code = BPF_JMP | BPF_JLE | bpf_src;
					अवरोध;
				हाल BPF_JGE:
					insn->code = BPF_JMP | BPF_JLT | bpf_src;
					अवरोध;
				शेष:
					जाओ jmp_rest;
				पूर्ण

				target = i + fp->jf + 1;
				BPF_EMIT_JMP;
				अवरोध;
			पूर्ण
jmp_rest:
			/* Other jumps are mapped पूर्णांकo two insns: Jxx and JA. */
			target = i + fp->jt + 1;
			insn->code = BPF_JMP | BPF_OP(fp->code) | bpf_src;
			BPF_EMIT_JMP;
			insn++;

			insn->code = BPF_JMP | BPF_JA;
			target = i + fp->jf + 1;
			BPF_EMIT_JMP;
			अवरोध;

		/* ldxb 4 * ([14] & 0xf) is remaped पूर्णांकo 6 insns. */
		हाल BPF_LDX | BPF_MSH | BPF_B: अणु
			काष्ठा sock_filter पंचांगp = अणु
				.code	= BPF_LD | BPF_ABS | BPF_B,
				.k	= fp->k,
			पूर्ण;

			*seen_ld_असल = true;

			/* X = A */
			*insn++ = BPF_MOV64_REG(BPF_REG_X, BPF_REG_A);
			/* A = BPF_R0 = *(u8 *) (skb->data + K) */
			convert_bpf_ld_असल(&पंचांगp, &insn);
			insn++;
			/* A &= 0xf */
			*insn++ = BPF_ALU32_IMM(BPF_AND, BPF_REG_A, 0xf);
			/* A <<= 2 */
			*insn++ = BPF_ALU32_IMM(BPF_LSH, BPF_REG_A, 2);
			/* पंचांगp = X */
			*insn++ = BPF_MOV64_REG(BPF_REG_TMP, BPF_REG_X);
			/* X = A */
			*insn++ = BPF_MOV64_REG(BPF_REG_X, BPF_REG_A);
			/* A = पंचांगp */
			*insn = BPF_MOV64_REG(BPF_REG_A, BPF_REG_TMP);
			अवरोध;
		पूर्ण
		/* RET_K is remaped पूर्णांकo 2 insns. RET_A हाल करोesn't need an
		 * extra mov as BPF_REG_0 is alपढ़ोy mapped पूर्णांकo BPF_REG_A.
		 */
		हाल BPF_RET | BPF_A:
		हाल BPF_RET | BPF_K:
			अगर (BPF_RVAL(fp->code) == BPF_K)
				*insn++ = BPF_MOV32_RAW(BPF_K, BPF_REG_0,
							0, fp->k);
			*insn = BPF_EXIT_INSN();
			अवरोध;

		/* Store to stack. */
		हाल BPF_ST:
		हाल BPF_STX:
			stack_off = fp->k * 4  + 4;
			*insn = BPF_STX_MEM(BPF_W, BPF_REG_FP, BPF_CLASS(fp->code) ==
					    BPF_ST ? BPF_REG_A : BPF_REG_X,
					    -stack_off);
			/* check_load_and_stores() verअगरies that classic BPF can
			 * load from stack only after ग_लिखो, so tracking
			 * stack_depth क्रम ST|STX insns is enough
			 */
			अगर (new_prog && new_prog->aux->stack_depth < stack_off)
				new_prog->aux->stack_depth = stack_off;
			अवरोध;

		/* Load from stack. */
		हाल BPF_LD | BPF_MEM:
		हाल BPF_LDX | BPF_MEM:
			stack_off = fp->k * 4  + 4;
			*insn = BPF_LDX_MEM(BPF_W, BPF_CLASS(fp->code) == BPF_LD  ?
					    BPF_REG_A : BPF_REG_X, BPF_REG_FP,
					    -stack_off);
			अवरोध;

		/* A = K or X = K */
		हाल BPF_LD | BPF_IMM:
		हाल BPF_LDX | BPF_IMM:
			*insn = BPF_MOV32_IMM(BPF_CLASS(fp->code) == BPF_LD ?
					      BPF_REG_A : BPF_REG_X, fp->k);
			अवरोध;

		/* X = A */
		हाल BPF_MISC | BPF_TAX:
			*insn = BPF_MOV64_REG(BPF_REG_X, BPF_REG_A);
			अवरोध;

		/* A = X */
		हाल BPF_MISC | BPF_TXA:
			*insn = BPF_MOV64_REG(BPF_REG_A, BPF_REG_X);
			अवरोध;

		/* A = skb->len or X = skb->len */
		हाल BPF_LD | BPF_W | BPF_LEN:
		हाल BPF_LDX | BPF_W | BPF_LEN:
			*insn = BPF_LDX_MEM(BPF_W, BPF_CLASS(fp->code) == BPF_LD ?
					    BPF_REG_A : BPF_REG_X, BPF_REG_CTX,
					    दुरत्व(काष्ठा sk_buff, len));
			अवरोध;

		/* Access seccomp_data fields. */
		हाल BPF_LDX | BPF_ABS | BPF_W:
			/* A = *(u32 *) (ctx + K) */
			*insn = BPF_LDX_MEM(BPF_W, BPF_REG_A, BPF_REG_CTX, fp->k);
			अवरोध;

		/* Unknown inकाष्ठाion. */
		शेष:
			जाओ err;
		पूर्ण

		insn++;
		अगर (new_prog)
			स_नकल(new_insn, पंचांगp_insns,
			       माप(*insn) * (insn - पंचांगp_insns));
		new_insn += insn - पंचांगp_insns;
	पूर्ण

	अगर (!new_prog) अणु
		/* Only calculating new length. */
		*new_len = new_insn - first_insn;
		अगर (*seen_ld_असल)
			*new_len += 4; /* Prologue bits. */
		वापस 0;
	पूर्ण

	pass++;
	अगर (new_flen != new_insn - first_insn) अणु
		new_flen = new_insn - first_insn;
		अगर (pass > 2)
			जाओ err;
		जाओ करो_pass;
	पूर्ण

	kमुक्त(addrs);
	BUG_ON(*new_len != new_flen);
	वापस 0;
err:
	kमुक्त(addrs);
	वापस -EINVAL;
पूर्ण

/* Security:
 *
 * As we करोnt want to clear mem[] array क्रम each packet going through
 * __bpf_prog_run(), we check that filter loaded by user never try to पढ़ो
 * a cell अगर not previously written, and we check all branches to be sure
 * a malicious user करोesn't try to abuse us.
 */
अटल पूर्णांक check_load_and_stores(स्थिर काष्ठा sock_filter *filter, पूर्णांक flen)
अणु
	u16 *masks, memvalid = 0; /* One bit per cell, 16 cells */
	पूर्णांक pc, ret = 0;

	BUILD_BUG_ON(BPF_MEMWORDS > 16);

	masks = kदो_स्मृति_array(flen, माप(*masks), GFP_KERNEL);
	अगर (!masks)
		वापस -ENOMEM;

	स_रखो(masks, 0xff, flen * माप(*masks));

	क्रम (pc = 0; pc < flen; pc++) अणु
		memvalid &= masks[pc];

		चयन (filter[pc].code) अणु
		हाल BPF_ST:
		हाल BPF_STX:
			memvalid |= (1 << filter[pc].k);
			अवरोध;
		हाल BPF_LD | BPF_MEM:
		हाल BPF_LDX | BPF_MEM:
			अगर (!(memvalid & (1 << filter[pc].k))) अणु
				ret = -EINVAL;
				जाओ error;
			पूर्ण
			अवरोध;
		हाल BPF_JMP | BPF_JA:
			/* A jump must set masks on target */
			masks[pc + 1 + filter[pc].k] &= memvalid;
			memvalid = ~0;
			अवरोध;
		हाल BPF_JMP | BPF_JEQ | BPF_K:
		हाल BPF_JMP | BPF_JEQ | BPF_X:
		हाल BPF_JMP | BPF_JGE | BPF_K:
		हाल BPF_JMP | BPF_JGE | BPF_X:
		हाल BPF_JMP | BPF_JGT | BPF_K:
		हाल BPF_JMP | BPF_JGT | BPF_X:
		हाल BPF_JMP | BPF_JSET | BPF_K:
		हाल BPF_JMP | BPF_JSET | BPF_X:
			/* A jump must set masks on tarमाला_लो */
			masks[pc + 1 + filter[pc].jt] &= memvalid;
			masks[pc + 1 + filter[pc].jf] &= memvalid;
			memvalid = ~0;
			अवरोध;
		पूर्ण
	पूर्ण
error:
	kमुक्त(masks);
	वापस ret;
पूर्ण

अटल bool chk_code_allowed(u16 code_to_probe)
अणु
	अटल स्थिर bool codes[] = अणु
		/* 32 bit ALU operations */
		[BPF_ALU | BPF_ADD | BPF_K] = true,
		[BPF_ALU | BPF_ADD | BPF_X] = true,
		[BPF_ALU | BPF_SUB | BPF_K] = true,
		[BPF_ALU | BPF_SUB | BPF_X] = true,
		[BPF_ALU | BPF_MUL | BPF_K] = true,
		[BPF_ALU | BPF_MUL | BPF_X] = true,
		[BPF_ALU | BPF_DIV | BPF_K] = true,
		[BPF_ALU | BPF_DIV | BPF_X] = true,
		[BPF_ALU | BPF_MOD | BPF_K] = true,
		[BPF_ALU | BPF_MOD | BPF_X] = true,
		[BPF_ALU | BPF_AND | BPF_K] = true,
		[BPF_ALU | BPF_AND | BPF_X] = true,
		[BPF_ALU | BPF_OR | BPF_K] = true,
		[BPF_ALU | BPF_OR | BPF_X] = true,
		[BPF_ALU | BPF_XOR | BPF_K] = true,
		[BPF_ALU | BPF_XOR | BPF_X] = true,
		[BPF_ALU | BPF_LSH | BPF_K] = true,
		[BPF_ALU | BPF_LSH | BPF_X] = true,
		[BPF_ALU | BPF_RSH | BPF_K] = true,
		[BPF_ALU | BPF_RSH | BPF_X] = true,
		[BPF_ALU | BPF_NEG] = true,
		/* Load inकाष्ठाions */
		[BPF_LD | BPF_W | BPF_ABS] = true,
		[BPF_LD | BPF_H | BPF_ABS] = true,
		[BPF_LD | BPF_B | BPF_ABS] = true,
		[BPF_LD | BPF_W | BPF_LEN] = true,
		[BPF_LD | BPF_W | BPF_IND] = true,
		[BPF_LD | BPF_H | BPF_IND] = true,
		[BPF_LD | BPF_B | BPF_IND] = true,
		[BPF_LD | BPF_IMM] = true,
		[BPF_LD | BPF_MEM] = true,
		[BPF_LDX | BPF_W | BPF_LEN] = true,
		[BPF_LDX | BPF_B | BPF_MSH] = true,
		[BPF_LDX | BPF_IMM] = true,
		[BPF_LDX | BPF_MEM] = true,
		/* Store inकाष्ठाions */
		[BPF_ST] = true,
		[BPF_STX] = true,
		/* Misc inकाष्ठाions */
		[BPF_MISC | BPF_TAX] = true,
		[BPF_MISC | BPF_TXA] = true,
		/* Return inकाष्ठाions */
		[BPF_RET | BPF_K] = true,
		[BPF_RET | BPF_A] = true,
		/* Jump inकाष्ठाions */
		[BPF_JMP | BPF_JA] = true,
		[BPF_JMP | BPF_JEQ | BPF_K] = true,
		[BPF_JMP | BPF_JEQ | BPF_X] = true,
		[BPF_JMP | BPF_JGE | BPF_K] = true,
		[BPF_JMP | BPF_JGE | BPF_X] = true,
		[BPF_JMP | BPF_JGT | BPF_K] = true,
		[BPF_JMP | BPF_JGT | BPF_X] = true,
		[BPF_JMP | BPF_JSET | BPF_K] = true,
		[BPF_JMP | BPF_JSET | BPF_X] = true,
	पूर्ण;

	अगर (code_to_probe >= ARRAY_SIZE(codes))
		वापस false;

	वापस codes[code_to_probe];
पूर्ण

अटल bool bpf_check_basics_ok(स्थिर काष्ठा sock_filter *filter,
				अचिन्हित पूर्णांक flen)
अणु
	अगर (filter == शून्य)
		वापस false;
	अगर (flen == 0 || flen > BPF_MAXINSNS)
		वापस false;

	वापस true;
पूर्ण

/**
 *	bpf_check_classic - verअगरy socket filter code
 *	@filter: filter to verअगरy
 *	@flen: length of filter
 *
 * Check the user's filter code. If we let some ugly
 * filter code slip through kaboom! The filter must contain
 * no references or jumps that are out of range, no illegal
 * inकाष्ठाions, and must end with a RET inकाष्ठाion.
 *
 * All jumps are क्रमward as they are not चिन्हित.
 *
 * Returns 0 अगर the rule set is legal or -EINVAL अगर not.
 */
अटल पूर्णांक bpf_check_classic(स्थिर काष्ठा sock_filter *filter,
			     अचिन्हित पूर्णांक flen)
अणु
	bool anc_found;
	पूर्णांक pc;

	/* Check the filter code now */
	क्रम (pc = 0; pc < flen; pc++) अणु
		स्थिर काष्ठा sock_filter *ftest = &filter[pc];

		/* May we actually operate on this code? */
		अगर (!chk_code_allowed(ftest->code))
			वापस -EINVAL;

		/* Some inकाष्ठाions need special checks */
		चयन (ftest->code) अणु
		हाल BPF_ALU | BPF_DIV | BPF_K:
		हाल BPF_ALU | BPF_MOD | BPF_K:
			/* Check क्रम भागision by zero */
			अगर (ftest->k == 0)
				वापस -EINVAL;
			अवरोध;
		हाल BPF_ALU | BPF_LSH | BPF_K:
		हाल BPF_ALU | BPF_RSH | BPF_K:
			अगर (ftest->k >= 32)
				वापस -EINVAL;
			अवरोध;
		हाल BPF_LD | BPF_MEM:
		हाल BPF_LDX | BPF_MEM:
		हाल BPF_ST:
		हाल BPF_STX:
			/* Check क्रम invalid memory addresses */
			अगर (ftest->k >= BPF_MEMWORDS)
				वापस -EINVAL;
			अवरोध;
		हाल BPF_JMP | BPF_JA:
			/* Note, the large ftest->k might cause loops.
			 * Compare this with conditional jumps below,
			 * where offsets are limited. --ANK (981016)
			 */
			अगर (ftest->k >= (अचिन्हित पूर्णांक)(flen - pc - 1))
				वापस -EINVAL;
			अवरोध;
		हाल BPF_JMP | BPF_JEQ | BPF_K:
		हाल BPF_JMP | BPF_JEQ | BPF_X:
		हाल BPF_JMP | BPF_JGE | BPF_K:
		हाल BPF_JMP | BPF_JGE | BPF_X:
		हाल BPF_JMP | BPF_JGT | BPF_K:
		हाल BPF_JMP | BPF_JGT | BPF_X:
		हाल BPF_JMP | BPF_JSET | BPF_K:
		हाल BPF_JMP | BPF_JSET | BPF_X:
			/* Both conditionals must be safe */
			अगर (pc + ftest->jt + 1 >= flen ||
			    pc + ftest->jf + 1 >= flen)
				वापस -EINVAL;
			अवरोध;
		हाल BPF_LD | BPF_W | BPF_ABS:
		हाल BPF_LD | BPF_H | BPF_ABS:
		हाल BPF_LD | BPF_B | BPF_ABS:
			anc_found = false;
			अगर (bpf_anc_helper(ftest) & BPF_ANC)
				anc_found = true;
			/* Ancillary operation unknown or unsupported */
			अगर (anc_found == false && ftest->k >= SKF_AD_OFF)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Last inकाष्ठाion must be a RET code */
	चयन (filter[flen - 1].code) अणु
	हाल BPF_RET | BPF_K:
	हाल BPF_RET | BPF_A:
		वापस check_load_and_stores(filter, flen);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bpf_prog_store_orig_filter(काष्ठा bpf_prog *fp,
				      स्थिर काष्ठा sock_fprog *fprog)
अणु
	अचिन्हित पूर्णांक fsize = bpf_classic_proglen(fprog);
	काष्ठा sock_fprog_kern *fkprog;

	fp->orig_prog = kदो_स्मृति(माप(*fkprog), GFP_KERNEL);
	अगर (!fp->orig_prog)
		वापस -ENOMEM;

	fkprog = fp->orig_prog;
	fkprog->len = fprog->len;

	fkprog->filter = kmemdup(fp->insns, fsize,
				 GFP_KERNEL | __GFP_NOWARN);
	अगर (!fkprog->filter) अणु
		kमुक्त(fp->orig_prog);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bpf_release_orig_filter(काष्ठा bpf_prog *fp)
अणु
	काष्ठा sock_fprog_kern *fprog = fp->orig_prog;

	अगर (fprog) अणु
		kमुक्त(fprog->filter);
		kमुक्त(fprog);
	पूर्ण
पूर्ण

अटल व्योम __bpf_prog_release(काष्ठा bpf_prog *prog)
अणु
	अगर (prog->type == BPF_PROG_TYPE_SOCKET_FILTER) अणु
		bpf_prog_put(prog);
	पूर्ण अन्यथा अणु
		bpf_release_orig_filter(prog);
		bpf_prog_मुक्त(prog);
	पूर्ण
पूर्ण

अटल व्योम __sk_filter_release(काष्ठा sk_filter *fp)
अणु
	__bpf_prog_release(fp->prog);
	kमुक्त(fp);
पूर्ण

/**
 * 	sk_filter_release_rcu - Release a socket filter by rcu_head
 *	@rcu: rcu_head that contains the sk_filter to मुक्त
 */
अटल व्योम sk_filter_release_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा sk_filter *fp = container_of(rcu, काष्ठा sk_filter, rcu);

	__sk_filter_release(fp);
पूर्ण

/**
 *	sk_filter_release - release a socket filter
 *	@fp: filter to हटाओ
 *
 *	Remove a filter from a socket and release its resources.
 */
अटल व्योम sk_filter_release(काष्ठा sk_filter *fp)
अणु
	अगर (refcount_dec_and_test(&fp->refcnt))
		call_rcu(&fp->rcu, sk_filter_release_rcu);
पूर्ण

व्योम sk_filter_unअक्षरge(काष्ठा sock *sk, काष्ठा sk_filter *fp)
अणु
	u32 filter_size = bpf_prog_size(fp->prog->len);

	atomic_sub(filter_size, &sk->sk_omem_alloc);
	sk_filter_release(fp);
पूर्ण

/* try to अक्षरge the socket memory अगर there is space available
 * वापस true on success
 */
अटल bool __sk_filter_अक्षरge(काष्ठा sock *sk, काष्ठा sk_filter *fp)
अणु
	u32 filter_size = bpf_prog_size(fp->prog->len);

	/* same check as in sock_kदो_स्मृति() */
	अगर (filter_size <= sysctl_opपंचांगem_max &&
	    atomic_पढ़ो(&sk->sk_omem_alloc) + filter_size < sysctl_opपंचांगem_max) अणु
		atomic_add(filter_size, &sk->sk_omem_alloc);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool sk_filter_अक्षरge(काष्ठा sock *sk, काष्ठा sk_filter *fp)
अणु
	अगर (!refcount_inc_not_zero(&fp->refcnt))
		वापस false;

	अगर (!__sk_filter_अक्षरge(sk, fp)) अणु
		sk_filter_release(fp);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल काष्ठा bpf_prog *bpf_migrate_filter(काष्ठा bpf_prog *fp)
अणु
	काष्ठा sock_filter *old_prog;
	काष्ठा bpf_prog *old_fp;
	पूर्णांक err, new_len, old_len = fp->len;
	bool seen_ld_असल = false;

	/* We are मुक्त to overग_लिखो insns et al right here as it
	 * won't be used at this poपूर्णांक in समय anymore पूर्णांकernally
	 * after the migration to the पूर्णांकernal BPF inकाष्ठाion
	 * representation.
	 */
	BUILD_BUG_ON(माप(काष्ठा sock_filter) !=
		     माप(काष्ठा bpf_insn));

	/* Conversion cannot happen on overlapping memory areas,
	 * so we need to keep the user BPF around until the 2nd
	 * pass. At this समय, the user BPF is stored in fp->insns.
	 */
	old_prog = kmemdup(fp->insns, old_len * माप(काष्ठा sock_filter),
			   GFP_KERNEL | __GFP_NOWARN);
	अगर (!old_prog) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	/* 1st pass: calculate the new program length. */
	err = bpf_convert_filter(old_prog, old_len, शून्य, &new_len,
				 &seen_ld_असल);
	अगर (err)
		जाओ out_err_मुक्त;

	/* Expand fp क्रम appending the new filter representation. */
	old_fp = fp;
	fp = bpf_prog_पुनः_स्मृति(old_fp, bpf_prog_size(new_len), 0);
	अगर (!fp) अणु
		/* The old_fp is still around in हाल we couldn't
		 * allocate new memory, so unअक्षरge on that one.
		 */
		fp = old_fp;
		err = -ENOMEM;
		जाओ out_err_मुक्त;
	पूर्ण

	fp->len = new_len;

	/* 2nd pass: remap sock_filter insns पूर्णांकo bpf_insn insns. */
	err = bpf_convert_filter(old_prog, old_len, fp, &new_len,
				 &seen_ld_असल);
	अगर (err)
		/* 2nd bpf_convert_filter() can fail only अगर it fails
		 * to allocate memory, remapping must succeed. Note,
		 * that at this समय old_fp has alपढ़ोy been released
		 * by kपुनः_स्मृति().
		 */
		जाओ out_err_मुक्त;

	fp = bpf_prog_select_runसमय(fp, &err);
	अगर (err)
		जाओ out_err_मुक्त;

	kमुक्त(old_prog);
	वापस fp;

out_err_मुक्त:
	kमुक्त(old_prog);
out_err:
	__bpf_prog_release(fp);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा bpf_prog *bpf_prepare_filter(काष्ठा bpf_prog *fp,
					   bpf_aux_classic_check_t trans)
अणु
	पूर्णांक err;

	fp->bpf_func = शून्य;
	fp->jited = 0;

	err = bpf_check_classic(fp->insns, fp->len);
	अगर (err) अणु
		__bpf_prog_release(fp);
		वापस ERR_PTR(err);
	पूर्ण

	/* There might be additional checks and transक्रमmations
	 * needed on classic filters, f.e. in हाल of seccomp.
	 */
	अगर (trans) अणु
		err = trans(fp->insns, fp->len);
		अगर (err) अणु
			__bpf_prog_release(fp);
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण

	/* Probe अगर we can JIT compile the filter and अगर so, करो
	 * the compilation of the filter.
	 */
	bpf_jit_compile(fp);

	/* JIT compiler couldn't process this filter, so करो the
	 * पूर्णांकernal BPF translation क्रम the optimized पूर्णांकerpreter.
	 */
	अगर (!fp->jited)
		fp = bpf_migrate_filter(fp);

	वापस fp;
पूर्ण

/**
 *	bpf_prog_create - create an unattached filter
 *	@pfp: the unattached filter that is created
 *	@fprog: the filter program
 *
 * Create a filter independent of any socket. We first run some
 * sanity checks on it to make sure it करोes not explode on us later.
 * If an error occurs or there is insufficient memory क्रम the filter
 * a negative त्रुटि_सं code is वापसed. On success the वापस is zero.
 */
पूर्णांक bpf_prog_create(काष्ठा bpf_prog **pfp, काष्ठा sock_fprog_kern *fprog)
अणु
	अचिन्हित पूर्णांक fsize = bpf_classic_proglen(fprog);
	काष्ठा bpf_prog *fp;

	/* Make sure new filter is there and in the right amounts. */
	अगर (!bpf_check_basics_ok(fprog->filter, fprog->len))
		वापस -EINVAL;

	fp = bpf_prog_alloc(bpf_prog_size(fprog->len), 0);
	अगर (!fp)
		वापस -ENOMEM;

	स_नकल(fp->insns, fprog->filter, fsize);

	fp->len = fprog->len;
	/* Since unattached filters are not copied back to user
	 * space through sk_get_filter(), we करो not need to hold
	 * a copy here, and can spare us the work.
	 */
	fp->orig_prog = शून्य;

	/* bpf_prepare_filter() alपढ़ोy takes care of मुक्तing
	 * memory in हाल something goes wrong.
	 */
	fp = bpf_prepare_filter(fp, शून्य);
	अगर (IS_ERR(fp))
		वापस PTR_ERR(fp);

	*pfp = fp;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bpf_prog_create);

/**
 *	bpf_prog_create_from_user - create an unattached filter from user buffer
 *	@pfp: the unattached filter that is created
 *	@fprog: the filter program
 *	@trans: post-classic verअगरier transक्रमmation handler
 *	@save_orig: save classic BPF program
 *
 * This function effectively करोes the same as bpf_prog_create(), only
 * that it builds up its insns buffer from user space provided buffer.
 * It also allows क्रम passing a bpf_aux_classic_check_t handler.
 */
पूर्णांक bpf_prog_create_from_user(काष्ठा bpf_prog **pfp, काष्ठा sock_fprog *fprog,
			      bpf_aux_classic_check_t trans, bool save_orig)
अणु
	अचिन्हित पूर्णांक fsize = bpf_classic_proglen(fprog);
	काष्ठा bpf_prog *fp;
	पूर्णांक err;

	/* Make sure new filter is there and in the right amounts. */
	अगर (!bpf_check_basics_ok(fprog->filter, fprog->len))
		वापस -EINVAL;

	fp = bpf_prog_alloc(bpf_prog_size(fprog->len), 0);
	अगर (!fp)
		वापस -ENOMEM;

	अगर (copy_from_user(fp->insns, fprog->filter, fsize)) अणु
		__bpf_prog_मुक्त(fp);
		वापस -EFAULT;
	पूर्ण

	fp->len = fprog->len;
	fp->orig_prog = शून्य;

	अगर (save_orig) अणु
		err = bpf_prog_store_orig_filter(fp, fprog);
		अगर (err) अणु
			__bpf_prog_मुक्त(fp);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* bpf_prepare_filter() alपढ़ोy takes care of मुक्तing
	 * memory in हाल something goes wrong.
	 */
	fp = bpf_prepare_filter(fp, trans);
	अगर (IS_ERR(fp))
		वापस PTR_ERR(fp);

	*pfp = fp;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bpf_prog_create_from_user);

व्योम bpf_prog_destroy(काष्ठा bpf_prog *fp)
अणु
	__bpf_prog_release(fp);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_prog_destroy);

अटल पूर्णांक __sk_attach_prog(काष्ठा bpf_prog *prog, काष्ठा sock *sk)
अणु
	काष्ठा sk_filter *fp, *old_fp;

	fp = kदो_स्मृति(माप(*fp), GFP_KERNEL);
	अगर (!fp)
		वापस -ENOMEM;

	fp->prog = prog;

	अगर (!__sk_filter_अक्षरge(sk, fp)) अणु
		kमुक्त(fp);
		वापस -ENOMEM;
	पूर्ण
	refcount_set(&fp->refcnt, 1);

	old_fp = rcu_dereference_रक्षित(sk->sk_filter,
					   lockdep_sock_is_held(sk));
	rcu_assign_poपूर्णांकer(sk->sk_filter, fp);

	अगर (old_fp)
		sk_filter_unअक्षरge(sk, old_fp);

	वापस 0;
पूर्ण

अटल
काष्ठा bpf_prog *__get_filter(काष्ठा sock_fprog *fprog, काष्ठा sock *sk)
अणु
	अचिन्हित पूर्णांक fsize = bpf_classic_proglen(fprog);
	काष्ठा bpf_prog *prog;
	पूर्णांक err;

	अगर (sock_flag(sk, SOCK_FILTER_LOCKED))
		वापस ERR_PTR(-EPERM);

	/* Make sure new filter is there and in the right amounts. */
	अगर (!bpf_check_basics_ok(fprog->filter, fprog->len))
		वापस ERR_PTR(-EINVAL);

	prog = bpf_prog_alloc(bpf_prog_size(fprog->len), 0);
	अगर (!prog)
		वापस ERR_PTR(-ENOMEM);

	अगर (copy_from_user(prog->insns, fprog->filter, fsize)) अणु
		__bpf_prog_मुक्त(prog);
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	prog->len = fprog->len;

	err = bpf_prog_store_orig_filter(prog, fprog);
	अगर (err) अणु
		__bpf_prog_मुक्त(prog);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* bpf_prepare_filter() alपढ़ोy takes care of मुक्तing
	 * memory in हाल something goes wrong.
	 */
	वापस bpf_prepare_filter(prog, शून्य);
पूर्ण

/**
 *	sk_attach_filter - attach a socket filter
 *	@fprog: the filter program
 *	@sk: the socket to use
 *
 * Attach the user's filter code. We first run some sanity checks on
 * it to make sure it करोes not explode on us later. If an error
 * occurs or there is insufficient memory क्रम the filter a negative
 * त्रुटि_सं code is वापसed. On success the वापस is zero.
 */
पूर्णांक sk_attach_filter(काष्ठा sock_fprog *fprog, काष्ठा sock *sk)
अणु
	काष्ठा bpf_prog *prog = __get_filter(fprog, sk);
	पूर्णांक err;

	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	err = __sk_attach_prog(prog, sk);
	अगर (err < 0) अणु
		__bpf_prog_release(prog);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sk_attach_filter);

पूर्णांक sk_reuseport_attach_filter(काष्ठा sock_fprog *fprog, काष्ठा sock *sk)
अणु
	काष्ठा bpf_prog *prog = __get_filter(fprog, sk);
	पूर्णांक err;

	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	अगर (bpf_prog_size(prog->len) > sysctl_opपंचांगem_max)
		err = -ENOMEM;
	अन्यथा
		err = reuseport_attach_prog(sk, prog);

	अगर (err)
		__bpf_prog_release(prog);

	वापस err;
पूर्ण

अटल काष्ठा bpf_prog *__get_bpf(u32 ufd, काष्ठा sock *sk)
अणु
	अगर (sock_flag(sk, SOCK_FILTER_LOCKED))
		वापस ERR_PTR(-EPERM);

	वापस bpf_prog_get_type(ufd, BPF_PROG_TYPE_SOCKET_FILTER);
पूर्ण

पूर्णांक sk_attach_bpf(u32 ufd, काष्ठा sock *sk)
अणु
	काष्ठा bpf_prog *prog = __get_bpf(ufd, sk);
	पूर्णांक err;

	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	err = __sk_attach_prog(prog, sk);
	अगर (err < 0) अणु
		bpf_prog_put(prog);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक sk_reuseport_attach_bpf(u32 ufd, काष्ठा sock *sk)
अणु
	काष्ठा bpf_prog *prog;
	पूर्णांक err;

	अगर (sock_flag(sk, SOCK_FILTER_LOCKED))
		वापस -EPERM;

	prog = bpf_prog_get_type(ufd, BPF_PROG_TYPE_SOCKET_FILTER);
	अगर (PTR_ERR(prog) == -EINVAL)
		prog = bpf_prog_get_type(ufd, BPF_PROG_TYPE_SK_REUSEPORT);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	अगर (prog->type == BPF_PROG_TYPE_SK_REUSEPORT) अणु
		/* Like other non BPF_PROG_TYPE_SOCKET_FILTER
		 * bpf prog (e.g. sockmap).  It depends on the
		 * limitation imposed by bpf_prog_load().
		 * Hence, sysctl_opपंचांगem_max is not checked.
		 */
		अगर ((sk->sk_type != SOCK_STREAM &&
		     sk->sk_type != SOCK_DGRAM) ||
		    (sk->sk_protocol != IPPROTO_UDP &&
		     sk->sk_protocol != IPPROTO_TCP) ||
		    (sk->sk_family != AF_INET &&
		     sk->sk_family != AF_INET6)) अणु
			err = -ENOTSUPP;
			जाओ err_prog_put;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* BPF_PROG_TYPE_SOCKET_FILTER */
		अगर (bpf_prog_size(prog->len) > sysctl_opपंचांगem_max) अणु
			err = -ENOMEM;
			जाओ err_prog_put;
		पूर्ण
	पूर्ण

	err = reuseport_attach_prog(sk, prog);
err_prog_put:
	अगर (err)
		bpf_prog_put(prog);

	वापस err;
पूर्ण

व्योम sk_reuseport_prog_मुक्त(काष्ठा bpf_prog *prog)
अणु
	अगर (!prog)
		वापस;

	अगर (prog->type == BPF_PROG_TYPE_SK_REUSEPORT)
		bpf_prog_put(prog);
	अन्यथा
		bpf_prog_destroy(prog);
पूर्ण

काष्ठा bpf_scratchpad अणु
	जोड़ अणु
		__be32 dअगरf[MAX_BPF_STACK / माप(__be32)];
		u8     buff[MAX_BPF_STACK];
	पूर्ण;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा bpf_scratchpad, bpf_sp);

अटल अंतरभूत पूर्णांक __bpf_try_make_writable(काष्ठा sk_buff *skb,
					  अचिन्हित पूर्णांक ग_लिखो_len)
अणु
	वापस skb_ensure_writable(skb, ग_लिखो_len);
पूर्ण

अटल अंतरभूत पूर्णांक bpf_try_make_writable(काष्ठा sk_buff *skb,
					अचिन्हित पूर्णांक ग_लिखो_len)
अणु
	पूर्णांक err = __bpf_try_make_writable(skb, ग_लिखो_len);

	bpf_compute_data_poपूर्णांकers(skb);
	वापस err;
पूर्ण

अटल पूर्णांक bpf_try_make_head_writable(काष्ठा sk_buff *skb)
अणु
	वापस bpf_try_make_writable(skb, skb_headlen(skb));
पूर्ण

अटल अंतरभूत व्योम bpf_push_mac_rcsum(काष्ठा sk_buff *skb)
अणु
	अगर (skb_at_tc_ingress(skb))
		skb_postpush_rcsum(skb, skb_mac_header(skb), skb->mac_len);
पूर्ण

अटल अंतरभूत व्योम bpf_pull_mac_rcsum(काष्ठा sk_buff *skb)
अणु
	अगर (skb_at_tc_ingress(skb))
		skb_postpull_rcsum(skb, skb_mac_header(skb), skb->mac_len);
पूर्ण

BPF_CALL_5(bpf_skb_store_bytes, काष्ठा sk_buff *, skb, u32, offset,
	   स्थिर व्योम *, from, u32, len, u64, flags)
अणु
	व्योम *ptr;

	अगर (unlikely(flags & ~(BPF_F_RECOMPUTE_CSUM | BPF_F_INVALIDATE_HASH)))
		वापस -EINVAL;
	अगर (unlikely(offset > 0xffff))
		वापस -EFAULT;
	अगर (unlikely(bpf_try_make_writable(skb, offset + len)))
		वापस -EFAULT;

	ptr = skb->data + offset;
	अगर (flags & BPF_F_RECOMPUTE_CSUM)
		__skb_postpull_rcsum(skb, ptr, len, offset);

	स_नकल(ptr, from, len);

	अगर (flags & BPF_F_RECOMPUTE_CSUM)
		__skb_postpush_rcsum(skb, ptr, len, offset);
	अगर (flags & BPF_F_INVALIDATE_HASH)
		skb_clear_hash(skb);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_store_bytes_proto = अणु
	.func		= bpf_skb_store_bytes,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_PTR_TO_MEM,
	.arg4_type	= ARG_CONST_SIZE,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_skb_load_bytes, स्थिर काष्ठा sk_buff *, skb, u32, offset,
	   व्योम *, to, u32, len)
अणु
	व्योम *ptr;

	अगर (unlikely(offset > 0xffff))
		जाओ err_clear;

	ptr = skb_header_poपूर्णांकer(skb, offset, len, to);
	अगर (unlikely(!ptr))
		जाओ err_clear;
	अगर (ptr != to)
		स_नकल(to, ptr, len);

	वापस 0;
err_clear:
	स_रखो(to, 0, len);
	वापस -EFAULT;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_load_bytes_proto = अणु
	.func		= bpf_skb_load_bytes,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg4_type	= ARG_CONST_SIZE,
पूर्ण;

BPF_CALL_4(bpf_flow_dissector_load_bytes,
	   स्थिर काष्ठा bpf_flow_dissector *, ctx, u32, offset,
	   व्योम *, to, u32, len)
अणु
	व्योम *ptr;

	अगर (unlikely(offset > 0xffff))
		जाओ err_clear;

	अगर (unlikely(!ctx->skb))
		जाओ err_clear;

	ptr = skb_header_poपूर्णांकer(ctx->skb, offset, len, to);
	अगर (unlikely(!ptr))
		जाओ err_clear;
	अगर (ptr != to)
		स_नकल(to, ptr, len);

	वापस 0;
err_clear:
	स_रखो(to, 0, len);
	वापस -EFAULT;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_flow_dissector_load_bytes_proto = अणु
	.func		= bpf_flow_dissector_load_bytes,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg4_type	= ARG_CONST_SIZE,
पूर्ण;

BPF_CALL_5(bpf_skb_load_bytes_relative, स्थिर काष्ठा sk_buff *, skb,
	   u32, offset, व्योम *, to, u32, len, u32, start_header)
अणु
	u8 *end = skb_tail_poपूर्णांकer(skb);
	u8 *start, *ptr;

	अगर (unlikely(offset > 0xffff))
		जाओ err_clear;

	चयन (start_header) अणु
	हाल BPF_HDR_START_MAC:
		अगर (unlikely(!skb_mac_header_was_set(skb)))
			जाओ err_clear;
		start = skb_mac_header(skb);
		अवरोध;
	हाल BPF_HDR_START_NET:
		start = skb_network_header(skb);
		अवरोध;
	शेष:
		जाओ err_clear;
	पूर्ण

	ptr = start + offset;

	अगर (likely(ptr + len <= end)) अणु
		स_नकल(to, ptr, len);
		वापस 0;
	पूर्ण

err_clear:
	स_रखो(to, 0, len);
	वापस -EFAULT;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_load_bytes_relative_proto = अणु
	.func		= bpf_skb_load_bytes_relative,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg4_type	= ARG_CONST_SIZE,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_skb_pull_data, काष्ठा sk_buff *, skb, u32, len)
अणु
	/* Idea is the following: should the needed direct पढ़ो/ग_लिखो
	 * test fail during runसमय, we can pull in more data and reकरो
	 * again, since implicitly, we invalidate previous checks here.
	 *
	 * Or, since we know how much we need to make पढ़ो/ग_लिखोable,
	 * this can be करोne once at the program beginning क्रम direct
	 * access हाल. By this we overcome limitations of only current
	 * headroom being accessible.
	 */
	वापस bpf_try_make_writable(skb, len ? : skb_headlen(skb));
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_pull_data_proto = अणु
	.func		= bpf_skb_pull_data,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_1(bpf_sk_fullsock, काष्ठा sock *, sk)
अणु
	वापस sk_fullsock(sk) ? (अचिन्हित दीर्घ)sk : (अचिन्हित दीर्घ)शून्य;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sk_fullsock_proto = अणु
	.func		= bpf_sk_fullsock,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_SOCKET_OR_शून्य,
	.arg1_type	= ARG_PTR_TO_SOCK_COMMON,
पूर्ण;

अटल अंतरभूत पूर्णांक sk_skb_try_make_writable(काष्ठा sk_buff *skb,
					   अचिन्हित पूर्णांक ग_लिखो_len)
अणु
	वापस __bpf_try_make_writable(skb, ग_लिखो_len);
पूर्ण

BPF_CALL_2(sk_skb_pull_data, काष्ठा sk_buff *, skb, u32, len)
अणु
	/* Idea is the following: should the needed direct पढ़ो/ग_लिखो
	 * test fail during runसमय, we can pull in more data and reकरो
	 * again, since implicitly, we invalidate previous checks here.
	 *
	 * Or, since we know how much we need to make पढ़ो/ग_लिखोable,
	 * this can be करोne once at the program beginning क्रम direct
	 * access हाल. By this we overcome limitations of only current
	 * headroom being accessible.
	 */
	वापस sk_skb_try_make_writable(skb, len ? : skb_headlen(skb));
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto sk_skb_pull_data_proto = अणु
	.func		= sk_skb_pull_data,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_5(bpf_l3_csum_replace, काष्ठा sk_buff *, skb, u32, offset,
	   u64, from, u64, to, u64, flags)
अणु
	__sum16 *ptr;

	अगर (unlikely(flags & ~(BPF_F_HDR_FIELD_MASK)))
		वापस -EINVAL;
	अगर (unlikely(offset > 0xffff || offset & 1))
		वापस -EFAULT;
	अगर (unlikely(bpf_try_make_writable(skb, offset + माप(*ptr))))
		वापस -EFAULT;

	ptr = (__sum16 *)(skb->data + offset);
	चयन (flags & BPF_F_HDR_FIELD_MASK) अणु
	हाल 0:
		अगर (unlikely(from != 0))
			वापस -EINVAL;

		csum_replace_by_dअगरf(ptr, to);
		अवरोध;
	हाल 2:
		csum_replace2(ptr, from, to);
		अवरोध;
	हाल 4:
		csum_replace4(ptr, from, to);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_l3_csum_replace_proto = अणु
	.func		= bpf_l3_csum_replace,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_ANYTHING,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_5(bpf_l4_csum_replace, काष्ठा sk_buff *, skb, u32, offset,
	   u64, from, u64, to, u64, flags)
अणु
	bool is_pseuकरो = flags & BPF_F_PSEUDO_HDR;
	bool is_mmzero = flags & BPF_F_MARK_MANGLED_0;
	bool करो_mक्रमce = flags & BPF_F_MARK_ENFORCE;
	__sum16 *ptr;

	अगर (unlikely(flags & ~(BPF_F_MARK_MANGLED_0 | BPF_F_MARK_ENFORCE |
			       BPF_F_PSEUDO_HDR | BPF_F_HDR_FIELD_MASK)))
		वापस -EINVAL;
	अगर (unlikely(offset > 0xffff || offset & 1))
		वापस -EFAULT;
	अगर (unlikely(bpf_try_make_writable(skb, offset + माप(*ptr))))
		वापस -EFAULT;

	ptr = (__sum16 *)(skb->data + offset);
	अगर (is_mmzero && !करो_mक्रमce && !*ptr)
		वापस 0;

	चयन (flags & BPF_F_HDR_FIELD_MASK) अणु
	हाल 0:
		अगर (unlikely(from != 0))
			वापस -EINVAL;

		inet_proto_csum_replace_by_dअगरf(ptr, skb, to, is_pseuकरो);
		अवरोध;
	हाल 2:
		inet_proto_csum_replace2(ptr, skb, from, to, is_pseuकरो);
		अवरोध;
	हाल 4:
		inet_proto_csum_replace4(ptr, skb, from, to, is_pseuकरो);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (is_mmzero && !*ptr)
		*ptr = CSUM_MANGLED_0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_l4_csum_replace_proto = अणु
	.func		= bpf_l4_csum_replace,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_ANYTHING,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_5(bpf_csum_dअगरf, __be32 *, from, u32, from_size,
	   __be32 *, to, u32, to_size, __wsum, seed)
अणु
	काष्ठा bpf_scratchpad *sp = this_cpu_ptr(&bpf_sp);
	u32 dअगरf_size = from_size + to_size;
	पूर्णांक i, j = 0;

	/* This is quite flexible, some examples:
	 *
	 * from_size == 0, to_size > 0,  seed := csum --> pushing data
	 * from_size > 0,  to_size == 0, seed := csum --> pulling data
	 * from_size > 0,  to_size > 0,  seed := 0    --> dअगरfing data
	 *
	 * Even क्रम dअगरfing, from_size and to_size करोn't need to be equal.
	 */
	अगर (unlikely(((from_size | to_size) & (माप(__be32) - 1)) ||
		     dअगरf_size > माप(sp->dअगरf)))
		वापस -EINVAL;

	क्रम (i = 0; i < from_size / माप(__be32); i++, j++)
		sp->dअगरf[j] = ~from[i];
	क्रम (i = 0; i <   to_size / माप(__be32); i++, j++)
		sp->dअगरf[j] = to[i];

	वापस csum_partial(sp->dअगरf, dअगरf_size, seed);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_csum_dअगरf_proto = अणु
	.func		= bpf_csum_dअगरf,
	.gpl_only	= false,
	.pkt_access	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_MEM_OR_शून्य,
	.arg2_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg3_type	= ARG_PTR_TO_MEM_OR_शून्य,
	.arg4_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_csum_update, काष्ठा sk_buff *, skb, __wsum, csum)
अणु
	/* The पूर्णांकerface is to be used in combination with bpf_csum_dअगरf()
	 * क्रम direct packet ग_लिखोs. csum rotation क्रम alignment as well
	 * as emulating csum_sub() can be करोne from the eBPF program.
	 */
	अगर (skb->ip_summed == CHECKSUM_COMPLETE)
		वापस (skb->csum = csum_add(skb->csum, csum));

	वापस -ENOTSUPP;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_csum_update_proto = अणु
	.func		= bpf_csum_update,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_csum_level, काष्ठा sk_buff *, skb, u64, level)
अणु
	/* The पूर्णांकerface is to be used in combination with bpf_skb_adjust_room()
	 * क्रम encap/decap of packet headers when BPF_F_ADJ_ROOM_NO_CSUM_RESET
	 * is passed as flags, क्रम example.
	 */
	चयन (level) अणु
	हाल BPF_CSUM_LEVEL_INC:
		__skb_incr_checksum_unnecessary(skb);
		अवरोध;
	हाल BPF_CSUM_LEVEL_DEC:
		__skb_decr_checksum_unnecessary(skb);
		अवरोध;
	हाल BPF_CSUM_LEVEL_RESET:
		__skb_reset_checksum_unnecessary(skb);
		अवरोध;
	हाल BPF_CSUM_LEVEL_QUERY:
		वापस skb->ip_summed == CHECKSUM_UNNECESSARY ?
		       skb->csum_level : -EACCES;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_csum_level_proto = अणु
	.func		= bpf_csum_level,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

अटल अंतरभूत पूर्णांक __bpf_rx_skb(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	वापस dev_क्रमward_skb_nomtu(dev, skb);
पूर्ण

अटल अंतरभूत पूर्णांक __bpf_rx_skb_no_mac(काष्ठा net_device *dev,
				      काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret = ____dev_क्रमward_skb(dev, skb, false);

	अगर (likely(!ret)) अणु
		skb->dev = dev;
		ret = netअगर_rx(skb);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक __bpf_tx_skb(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ret;

	अगर (dev_xmit_recursion()) अणु
		net_crit_ratelimited("bpf: recursion limit reached on datapath, buggy bpf program?\n");
		kमुक्त_skb(skb);
		वापस -ENETDOWN;
	पूर्ण

	skb->dev = dev;
	skb->tstamp = 0;

	dev_xmit_recursion_inc();
	ret = dev_queue_xmit(skb);
	dev_xmit_recursion_dec();

	वापस ret;
पूर्ण

अटल पूर्णांक __bpf_redirect_no_mac(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				 u32 flags)
अणु
	अचिन्हित पूर्णांक mlen = skb_network_offset(skb);

	अगर (mlen) अणु
		__skb_pull(skb, mlen);

		/* At ingress, the mac header has alपढ़ोy been pulled once.
		 * At egress, skb_pospull_rcsum has to be करोne in हाल that
		 * the skb is originated from ingress (i.e. a क्रमwarded skb)
		 * to ensure that rcsum starts at net header.
		 */
		अगर (!skb_at_tc_ingress(skb))
			skb_postpull_rcsum(skb, skb_mac_header(skb), mlen);
	पूर्ण
	skb_pop_mac_header(skb);
	skb_reset_mac_len(skb);
	वापस flags & BPF_F_INGRESS ?
	       __bpf_rx_skb_no_mac(dev, skb) : __bpf_tx_skb(dev, skb);
पूर्ण

अटल पूर्णांक __bpf_redirect_common(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				 u32 flags)
अणु
	/* Verअगरy that a link layer header is carried */
	अगर (unlikely(skb->mac_header >= skb->network_header)) अणु
		kमुक्त_skb(skb);
		वापस -दुस्फल;
	पूर्ण

	bpf_push_mac_rcsum(skb);
	वापस flags & BPF_F_INGRESS ?
	       __bpf_rx_skb(dev, skb) : __bpf_tx_skb(dev, skb);
पूर्ण

अटल पूर्णांक __bpf_redirect(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			  u32 flags)
अणु
	अगर (dev_is_mac_header_xmit(dev))
		वापस __bpf_redirect_common(skb, dev, flags);
	अन्यथा
		वापस __bpf_redirect_no_mac(skb, dev, flags);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक bpf_out_neigh_v6(काष्ठा net *net, काष्ठा sk_buff *skb,
			    काष्ठा net_device *dev, काष्ठा bpf_nh_params *nh)
अणु
	u32 hh_len = LL_RESERVED_SPACE(dev);
	स्थिर काष्ठा in6_addr *nexthop;
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा neighbour *neigh;

	अगर (dev_xmit_recursion()) अणु
		net_crit_ratelimited("bpf: recursion limit reached on datapath, buggy bpf program?\n");
		जाओ out_drop;
	पूर्ण

	skb->dev = dev;
	skb->tstamp = 0;

	अगर (unlikely(skb_headroom(skb) < hh_len && dev->header_ops)) अणु
		काष्ठा sk_buff *skb2;

		skb2 = skb_पुनः_स्मृति_headroom(skb, hh_len);
		अगर (unlikely(!skb2)) अणु
			kमुक्त_skb(skb);
			वापस -ENOMEM;
		पूर्ण
		अगर (skb->sk)
			skb_set_owner_w(skb2, skb->sk);
		consume_skb(skb);
		skb = skb2;
	पूर्ण

	rcu_पढ़ो_lock_bh();
	अगर (!nh) अणु
		dst = skb_dst(skb);
		nexthop = rt6_nexthop(container_of(dst, काष्ठा rt6_info, dst),
				      &ipv6_hdr(skb)->daddr);
	पूर्ण अन्यथा अणु
		nexthop = &nh->ipv6_nh;
	पूर्ण
	neigh = ip_neigh_gw6(dev, nexthop);
	अगर (likely(!IS_ERR(neigh))) अणु
		पूर्णांक ret;

		sock_confirm_neigh(skb, neigh);
		dev_xmit_recursion_inc();
		ret = neigh_output(neigh, skb, false);
		dev_xmit_recursion_dec();
		rcu_पढ़ो_unlock_bh();
		वापस ret;
	पूर्ण
	rcu_पढ़ो_unlock_bh();
	अगर (dst)
		IP6_INC_STATS(dev_net(dst->dev),
			      ip6_dst_idev(dst), IPSTATS_MIB_OUTNOROUTES);
out_drop:
	kमुक्त_skb(skb);
	वापस -ENETDOWN;
पूर्ण

अटल पूर्णांक __bpf_redirect_neigh_v6(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   काष्ठा bpf_nh_params *nh)
अणु
	स्थिर काष्ठा ipv6hdr *ip6h = ipv6_hdr(skb);
	काष्ठा net *net = dev_net(dev);
	पूर्णांक err, ret = NET_XMIT_DROP;

	अगर (!nh) अणु
		काष्ठा dst_entry *dst;
		काष्ठा flowi6 fl6 = अणु
			.flowi6_flags = FLOWI_FLAG_ANYSRC,
			.flowi6_mark  = skb->mark,
			.flowlabel    = ip6_flowinfo(ip6h),
			.flowi6_oअगर   = dev->अगरindex,
			.flowi6_proto = ip6h->nexthdr,
			.daddr	      = ip6h->daddr,
			.saddr	      = ip6h->saddr,
		पूर्ण;

		dst = ipv6_stub->ipv6_dst_lookup_flow(net, शून्य, &fl6, शून्य);
		अगर (IS_ERR(dst))
			जाओ out_drop;

		skb_dst_set(skb, dst);
	पूर्ण अन्यथा अगर (nh->nh_family != AF_INET6) अणु
		जाओ out_drop;
	पूर्ण

	err = bpf_out_neigh_v6(net, skb, dev, nh);
	अगर (unlikely(net_xmit_eval(err)))
		dev->stats.tx_errors++;
	अन्यथा
		ret = NET_XMIT_SUCCESS;
	जाओ out_xmit;
out_drop:
	dev->stats.tx_errors++;
	kमुक्त_skb(skb);
out_xmit:
	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक __bpf_redirect_neigh_v6(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   काष्ठा bpf_nh_params *nh)
अणु
	kमुक्त_skb(skb);
	वापस NET_XMIT_DROP;
पूर्ण
#पूर्ण_अगर /* CONFIG_IPV6 */

#अगर IS_ENABLED(CONFIG_INET)
अटल पूर्णांक bpf_out_neigh_v4(काष्ठा net *net, काष्ठा sk_buff *skb,
			    काष्ठा net_device *dev, काष्ठा bpf_nh_params *nh)
अणु
	u32 hh_len = LL_RESERVED_SPACE(dev);
	काष्ठा neighbour *neigh;
	bool is_v6gw = false;

	अगर (dev_xmit_recursion()) अणु
		net_crit_ratelimited("bpf: recursion limit reached on datapath, buggy bpf program?\n");
		जाओ out_drop;
	पूर्ण

	skb->dev = dev;
	skb->tstamp = 0;

	अगर (unlikely(skb_headroom(skb) < hh_len && dev->header_ops)) अणु
		काष्ठा sk_buff *skb2;

		skb2 = skb_पुनः_स्मृति_headroom(skb, hh_len);
		अगर (unlikely(!skb2)) अणु
			kमुक्त_skb(skb);
			वापस -ENOMEM;
		पूर्ण
		अगर (skb->sk)
			skb_set_owner_w(skb2, skb->sk);
		consume_skb(skb);
		skb = skb2;
	पूर्ण

	rcu_पढ़ो_lock_bh();
	अगर (!nh) अणु
		काष्ठा dst_entry *dst = skb_dst(skb);
		काष्ठा rtable *rt = container_of(dst, काष्ठा rtable, dst);

		neigh = ip_neigh_क्रम_gw(rt, skb, &is_v6gw);
	पूर्ण अन्यथा अगर (nh->nh_family == AF_INET6) अणु
		neigh = ip_neigh_gw6(dev, &nh->ipv6_nh);
		is_v6gw = true;
	पूर्ण अन्यथा अगर (nh->nh_family == AF_INET) अणु
		neigh = ip_neigh_gw4(dev, nh->ipv4_nh);
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_unlock_bh();
		जाओ out_drop;
	पूर्ण

	अगर (likely(!IS_ERR(neigh))) अणु
		पूर्णांक ret;

		sock_confirm_neigh(skb, neigh);
		dev_xmit_recursion_inc();
		ret = neigh_output(neigh, skb, is_v6gw);
		dev_xmit_recursion_dec();
		rcu_पढ़ो_unlock_bh();
		वापस ret;
	पूर्ण
	rcu_पढ़ो_unlock_bh();
out_drop:
	kमुक्त_skb(skb);
	वापस -ENETDOWN;
पूर्ण

अटल पूर्णांक __bpf_redirect_neigh_v4(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   काष्ठा bpf_nh_params *nh)
अणु
	स्थिर काष्ठा iphdr *ip4h = ip_hdr(skb);
	काष्ठा net *net = dev_net(dev);
	पूर्णांक err, ret = NET_XMIT_DROP;

	अगर (!nh) अणु
		काष्ठा flowi4 fl4 = अणु
			.flowi4_flags = FLOWI_FLAG_ANYSRC,
			.flowi4_mark  = skb->mark,
			.flowi4_tos   = RT_TOS(ip4h->tos),
			.flowi4_oअगर   = dev->अगरindex,
			.flowi4_proto = ip4h->protocol,
			.daddr	      = ip4h->daddr,
			.saddr	      = ip4h->saddr,
		पूर्ण;
		काष्ठा rtable *rt;

		rt = ip_route_output_flow(net, &fl4, शून्य);
		अगर (IS_ERR(rt))
			जाओ out_drop;
		अगर (rt->rt_type != RTN_UNICAST && rt->rt_type != RTN_LOCAL) अणु
			ip_rt_put(rt);
			जाओ out_drop;
		पूर्ण

		skb_dst_set(skb, &rt->dst);
	पूर्ण

	err = bpf_out_neigh_v4(net, skb, dev, nh);
	अगर (unlikely(net_xmit_eval(err)))
		dev->stats.tx_errors++;
	अन्यथा
		ret = NET_XMIT_SUCCESS;
	जाओ out_xmit;
out_drop:
	dev->stats.tx_errors++;
	kमुक्त_skb(skb);
out_xmit:
	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक __bpf_redirect_neigh_v4(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				   काष्ठा bpf_nh_params *nh)
अणु
	kमुक्त_skb(skb);
	वापस NET_XMIT_DROP;
पूर्ण
#पूर्ण_अगर /* CONFIG_INET */

अटल पूर्णांक __bpf_redirect_neigh(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				काष्ठा bpf_nh_params *nh)
अणु
	काष्ठा ethhdr *ethh = eth_hdr(skb);

	अगर (unlikely(skb->mac_header >= skb->network_header))
		जाओ out;
	bpf_push_mac_rcsum(skb);
	अगर (is_multicast_ether_addr(ethh->h_dest))
		जाओ out;

	skb_pull(skb, माप(*ethh));
	skb_unset_mac_header(skb);
	skb_reset_network_header(skb);

	अगर (skb->protocol == htons(ETH_P_IP))
		वापस __bpf_redirect_neigh_v4(skb, dev, nh);
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		वापस __bpf_redirect_neigh_v6(skb, dev, nh);
out:
	kमुक्त_skb(skb);
	वापस -ENOTSUPP;
पूर्ण

/* Internal, non-exposed redirect flags. */
क्रमागत अणु
	BPF_F_NEIGH	= (1ULL << 1),
	BPF_F_PEER	= (1ULL << 2),
	BPF_F_NEXTHOP	= (1ULL << 3),
#घोषणा BPF_F_REसूचीECT_INTERNAL	(BPF_F_NEIGH | BPF_F_PEER | BPF_F_NEXTHOP)
पूर्ण;

BPF_CALL_3(bpf_clone_redirect, काष्ठा sk_buff *, skb, u32, अगरindex, u64, flags)
अणु
	काष्ठा net_device *dev;
	काष्ठा sk_buff *clone;
	पूर्णांक ret;

	अगर (unlikely(flags & (~(BPF_F_INGRESS) | BPF_F_REसूचीECT_INTERNAL)))
		वापस -EINVAL;

	dev = dev_get_by_index_rcu(dev_net(skb->dev), अगरindex);
	अगर (unlikely(!dev))
		वापस -EINVAL;

	clone = skb_clone(skb, GFP_ATOMIC);
	अगर (unlikely(!clone))
		वापस -ENOMEM;

	/* For direct ग_लिखो, we need to keep the invariant that the skbs
	 * we're dealing with need to be uncloned. Should uncloning fail
	 * here, we need to मुक्त the just generated clone to unclone once
	 * again.
	 */
	ret = bpf_try_make_head_writable(skb);
	अगर (unlikely(ret)) अणु
		kमुक्त_skb(clone);
		वापस -ENOMEM;
	पूर्ण

	वापस __bpf_redirect(clone, dev, flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_clone_redirect_proto = अणु
	.func           = bpf_clone_redirect,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
	.arg2_type      = ARG_ANYTHING,
	.arg3_type      = ARG_ANYTHING,
पूर्ण;

DEFINE_PER_CPU(काष्ठा bpf_redirect_info, bpf_redirect_info);
EXPORT_PER_CPU_SYMBOL_GPL(bpf_redirect_info);

पूर्णांक skb_करो_redirect(काष्ठा sk_buff *skb)
अणु
	काष्ठा bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);
	काष्ठा net *net = dev_net(skb->dev);
	काष्ठा net_device *dev;
	u32 flags = ri->flags;

	dev = dev_get_by_index_rcu(net, ri->tgt_index);
	ri->tgt_index = 0;
	ri->flags = 0;
	अगर (unlikely(!dev))
		जाओ out_drop;
	अगर (flags & BPF_F_PEER) अणु
		स्थिर काष्ठा net_device_ops *ops = dev->netdev_ops;

		अगर (unlikely(!ops->nकरो_get_peer_dev ||
			     !skb_at_tc_ingress(skb)))
			जाओ out_drop;
		dev = ops->nकरो_get_peer_dev(dev);
		अगर (unlikely(!dev ||
			     !(dev->flags & IFF_UP) ||
			     net_eq(net, dev_net(dev))))
			जाओ out_drop;
		skb->dev = dev;
		वापस -EAGAIN;
	पूर्ण
	वापस flags & BPF_F_NEIGH ?
	       __bpf_redirect_neigh(skb, dev, flags & BPF_F_NEXTHOP ?
				    &ri->nh : शून्य) :
	       __bpf_redirect(skb, dev, flags);
out_drop:
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण

BPF_CALL_2(bpf_redirect, u32, अगरindex, u64, flags)
अणु
	काष्ठा bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);

	अगर (unlikely(flags & (~(BPF_F_INGRESS) | BPF_F_REसूचीECT_INTERNAL)))
		वापस TC_ACT_SHOT;

	ri->flags = flags;
	ri->tgt_index = अगरindex;

	वापस TC_ACT_REसूचीECT;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_redirect_proto = अणु
	.func           = bpf_redirect,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_ANYTHING,
	.arg2_type      = ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_redirect_peer, u32, अगरindex, u64, flags)
अणु
	काष्ठा bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);

	अगर (unlikely(flags))
		वापस TC_ACT_SHOT;

	ri->flags = BPF_F_PEER;
	ri->tgt_index = अगरindex;

	वापस TC_ACT_REसूचीECT;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_redirect_peer_proto = अणु
	.func           = bpf_redirect_peer,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_ANYTHING,
	.arg2_type      = ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_redirect_neigh, u32, अगरindex, काष्ठा bpf_redir_neigh *, params,
	   पूर्णांक, plen, u64, flags)
अणु
	काष्ठा bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);

	अगर (unlikely((plen && plen < माप(*params)) || flags))
		वापस TC_ACT_SHOT;

	ri->flags = BPF_F_NEIGH | (plen ? BPF_F_NEXTHOP : 0);
	ri->tgt_index = अगरindex;

	BUILD_BUG_ON(माप(काष्ठा bpf_redir_neigh) != माप(काष्ठा bpf_nh_params));
	अगर (plen)
		स_नकल(&ri->nh, params, माप(ri->nh));

	वापस TC_ACT_REसूचीECT;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_redirect_neigh_proto = अणु
	.func		= bpf_redirect_neigh,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_ANYTHING,
	.arg2_type      = ARG_PTR_TO_MEM_OR_शून्य,
	.arg3_type      = ARG_CONST_SIZE_OR_ZERO,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_msg_apply_bytes, काष्ठा sk_msg *, msg, u32, bytes)
अणु
	msg->apply_bytes = bytes;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_msg_apply_bytes_proto = अणु
	.func           = bpf_msg_apply_bytes,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type      = ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_msg_cork_bytes, काष्ठा sk_msg *, msg, u32, bytes)
अणु
	msg->cork_bytes = bytes;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_msg_cork_bytes_proto = अणु
	.func           = bpf_msg_cork_bytes,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type      = ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_msg_pull_data, काष्ठा sk_msg *, msg, u32, start,
	   u32, end, u64, flags)
अणु
	u32 len = 0, offset = 0, copy = 0, poffset = 0, bytes = end - start;
	u32 first_sge, last_sge, i, shअगरt, bytes_sg_total;
	काष्ठा scatterlist *sge;
	u8 *raw, *to, *from;
	काष्ठा page *page;

	अगर (unlikely(flags || end <= start))
		वापस -EINVAL;

	/* First find the starting scatterlist element */
	i = msg->sg.start;
	करो अणु
		offset += len;
		len = sk_msg_elem(msg, i)->length;
		अगर (start < offset + len)
			अवरोध;
		sk_msg_iter_var_next(i);
	पूर्ण जबतक (i != msg->sg.end);

	अगर (unlikely(start >= offset + len))
		वापस -EINVAL;

	first_sge = i;
	/* The start may poपूर्णांक पूर्णांकo the sg element so we need to also
	 * account क्रम the headroom.
	 */
	bytes_sg_total = start - offset + bytes;
	अगर (!test_bit(i, &msg->sg.copy) && bytes_sg_total <= len)
		जाओ out;

	/* At this poपूर्णांक we need to linearize multiple scatterlist
	 * elements or a single shared page. Either way we need to
	 * copy पूर्णांकo a linear buffer exclusively owned by BPF. Then
	 * place the buffer in the scatterlist and fixup the original
	 * entries by removing the entries now in the linear buffer
	 * and shअगरting the reमुख्यing entries. For now we करो not try
	 * to copy partial entries to aव्योम complनिकासy of running out
	 * of sg_entry slots. The करोwnside is पढ़ोing a single byte
	 * will copy the entire sg entry.
	 */
	करो अणु
		copy += sk_msg_elem(msg, i)->length;
		sk_msg_iter_var_next(i);
		अगर (bytes_sg_total <= copy)
			अवरोध;
	पूर्ण जबतक (i != msg->sg.end);
	last_sge = i;

	अगर (unlikely(bytes_sg_total > copy))
		वापस -EINVAL;

	page = alloc_pages(__GFP_NOWARN | GFP_ATOMIC | __GFP_COMP,
			   get_order(copy));
	अगर (unlikely(!page))
		वापस -ENOMEM;

	raw = page_address(page);
	i = first_sge;
	करो अणु
		sge = sk_msg_elem(msg, i);
		from = sg_virt(sge);
		len = sge->length;
		to = raw + poffset;

		स_नकल(to, from, len);
		poffset += len;
		sge->length = 0;
		put_page(sg_page(sge));

		sk_msg_iter_var_next(i);
	पूर्ण जबतक (i != last_sge);

	sg_set_page(&msg->sg.data[first_sge], page, copy, 0);

	/* To repair sg ring we need to shअगरt entries. If we only
	 * had a single entry though we can just replace it and
	 * be करोne. Otherwise walk the ring and shअगरt the entries.
	 */
	WARN_ON_ONCE(last_sge == first_sge);
	shअगरt = last_sge > first_sge ?
		last_sge - first_sge - 1 :
		NR_MSG_FRAG_IDS - first_sge + last_sge - 1;
	अगर (!shअगरt)
		जाओ out;

	i = first_sge;
	sk_msg_iter_var_next(i);
	करो अणु
		u32 move_from;

		अगर (i + shअगरt >= NR_MSG_FRAG_IDS)
			move_from = i + shअगरt - NR_MSG_FRAG_IDS;
		अन्यथा
			move_from = i + shअगरt;
		अगर (move_from == msg->sg.end)
			अवरोध;

		msg->sg.data[i] = msg->sg.data[move_from];
		msg->sg.data[move_from].length = 0;
		msg->sg.data[move_from].page_link = 0;
		msg->sg.data[move_from].offset = 0;
		sk_msg_iter_var_next(i);
	पूर्ण जबतक (1);

	msg->sg.end = msg->sg.end - shअगरt > msg->sg.end ?
		      msg->sg.end - shअगरt + NR_MSG_FRAG_IDS :
		      msg->sg.end - shअगरt;
out:
	msg->data = sg_virt(&msg->sg.data[first_sge]) + start - offset;
	msg->data_end = msg->data + bytes;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_msg_pull_data_proto = अणु
	.func		= bpf_msg_pull_data,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_msg_push_data, काष्ठा sk_msg *, msg, u32, start,
	   u32, len, u64, flags)
अणु
	काष्ठा scatterlist sge, nsge, nnsge, rsge = अणु0पूर्ण, *psge;
	u32 new, i = 0, l = 0, space, copy = 0, offset = 0;
	u8 *raw, *to, *from;
	काष्ठा page *page;

	अगर (unlikely(flags))
		वापस -EINVAL;

	/* First find the starting scatterlist element */
	i = msg->sg.start;
	करो अणु
		offset += l;
		l = sk_msg_elem(msg, i)->length;

		अगर (start < offset + l)
			अवरोध;
		sk_msg_iter_var_next(i);
	पूर्ण जबतक (i != msg->sg.end);

	अगर (start >= offset + l)
		वापस -EINVAL;

	space = MAX_MSG_FRAGS - sk_msg_elem_used(msg);

	/* If no space available will fallback to copy, we need at
	 * least one scatterlist elem available to push data पूर्णांकo
	 * when start aligns to the beginning of an element or two
	 * when it falls inside an element. We handle the start equals
	 * offset हाल because its the common हाल क्रम inserting a
	 * header.
	 */
	अगर (!space || (space == 1 && start != offset))
		copy = msg->sg.data[i].length;

	page = alloc_pages(__GFP_NOWARN | GFP_ATOMIC | __GFP_COMP,
			   get_order(copy + len));
	अगर (unlikely(!page))
		वापस -ENOMEM;

	अगर (copy) अणु
		पूर्णांक front, back;

		raw = page_address(page);

		psge = sk_msg_elem(msg, i);
		front = start - offset;
		back = psge->length - front;
		from = sg_virt(psge);

		अगर (front)
			स_नकल(raw, from, front);

		अगर (back) अणु
			from += front;
			to = raw + front + len;

			स_नकल(to, from, back);
		पूर्ण

		put_page(sg_page(psge));
	पूर्ण अन्यथा अगर (start - offset) अणु
		psge = sk_msg_elem(msg, i);
		rsge = sk_msg_elem_cpy(msg, i);

		psge->length = start - offset;
		rsge.length -= psge->length;
		rsge.offset += start;

		sk_msg_iter_var_next(i);
		sg_unmark_end(psge);
		sg_unmark_end(&rsge);
		sk_msg_iter_next(msg, end);
	पूर्ण

	/* Slot(s) to place newly allocated data */
	new = i;

	/* Shअगरt one or two slots as needed */
	अगर (!copy) अणु
		sge = sk_msg_elem_cpy(msg, i);

		sk_msg_iter_var_next(i);
		sg_unmark_end(&sge);
		sk_msg_iter_next(msg, end);

		nsge = sk_msg_elem_cpy(msg, i);
		अगर (rsge.length) अणु
			sk_msg_iter_var_next(i);
			nnsge = sk_msg_elem_cpy(msg, i);
		पूर्ण

		जबतक (i != msg->sg.end) अणु
			msg->sg.data[i] = sge;
			sge = nsge;
			sk_msg_iter_var_next(i);
			अगर (rsge.length) अणु
				nsge = nnsge;
				nnsge = sk_msg_elem_cpy(msg, i);
			पूर्ण अन्यथा अणु
				nsge = sk_msg_elem_cpy(msg, i);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Place newly allocated data buffer */
	sk_mem_अक्षरge(msg->sk, len);
	msg->sg.size += len;
	__clear_bit(new, &msg->sg.copy);
	sg_set_page(&msg->sg.data[new], page, len + copy, 0);
	अगर (rsge.length) अणु
		get_page(sg_page(&rsge));
		sk_msg_iter_var_next(new);
		msg->sg.data[new] = rsge;
	पूर्ण

	sk_msg_compute_data_poपूर्णांकers(msg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_msg_push_data_proto = अणु
	.func		= bpf_msg_push_data,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

अटल व्योम sk_msg_shअगरt_left(काष्ठा sk_msg *msg, पूर्णांक i)
अणु
	पूर्णांक prev;

	करो अणु
		prev = i;
		sk_msg_iter_var_next(i);
		msg->sg.data[prev] = msg->sg.data[i];
	पूर्ण जबतक (i != msg->sg.end);

	sk_msg_iter_prev(msg, end);
पूर्ण

अटल व्योम sk_msg_shअगरt_right(काष्ठा sk_msg *msg, पूर्णांक i)
अणु
	काष्ठा scatterlist पंचांगp, sge;

	sk_msg_iter_next(msg, end);
	sge = sk_msg_elem_cpy(msg, i);
	sk_msg_iter_var_next(i);
	पंचांगp = sk_msg_elem_cpy(msg, i);

	जबतक (i != msg->sg.end) अणु
		msg->sg.data[i] = sge;
		sk_msg_iter_var_next(i);
		sge = पंचांगp;
		पंचांगp = sk_msg_elem_cpy(msg, i);
	पूर्ण
पूर्ण

BPF_CALL_4(bpf_msg_pop_data, काष्ठा sk_msg *, msg, u32, start,
	   u32, len, u64, flags)
अणु
	u32 i = 0, l = 0, space, offset = 0;
	u64 last = start + len;
	पूर्णांक pop;

	अगर (unlikely(flags))
		वापस -EINVAL;

	/* First find the starting scatterlist element */
	i = msg->sg.start;
	करो अणु
		offset += l;
		l = sk_msg_elem(msg, i)->length;

		अगर (start < offset + l)
			अवरोध;
		sk_msg_iter_var_next(i);
	पूर्ण जबतक (i != msg->sg.end);

	/* Bounds checks: start and pop must be inside message */
	अगर (start >= offset + l || last >= msg->sg.size)
		वापस -EINVAL;

	space = MAX_MSG_FRAGS - sk_msg_elem_used(msg);

	pop = len;
	/* --------------| offset
	 * -| start      |-------- len -------|
	 *
	 *  |----- a ----|-------- pop -------|----- b ----|
	 *  |______________________________________________| length
	 *
	 *
	 * a:   region at front of scatter element to save
	 * b:   region at back of scatter element to save when length > A + pop
	 * pop: region to pop from element, same as input 'pop' here will be
	 *      decremented below per iteration.
	 *
	 * Two top-level हालs to handle when start != offset, first B is non
	 * zero and second B is zero corresponding to when a pop includes more
	 * than one element.
	 *
	 * Then अगर B is non-zero AND there is no space allocate space and
	 * compact A, B regions पूर्णांकo page. If there is space shअगरt ring to
	 * the rigth मुक्त'ing the next element in ring to place B, leaving
	 * A untouched except to reduce length.
	 */
	अगर (start != offset) अणु
		काष्ठा scatterlist *nsge, *sge = sk_msg_elem(msg, i);
		पूर्णांक a = start;
		पूर्णांक b = sge->length - pop - a;

		sk_msg_iter_var_next(i);

		अगर (pop < sge->length - a) अणु
			अगर (space) अणु
				sge->length = a;
				sk_msg_shअगरt_right(msg, i);
				nsge = sk_msg_elem(msg, i);
				get_page(sg_page(sge));
				sg_set_page(nsge,
					    sg_page(sge),
					    b, sge->offset + pop + a);
			पूर्ण अन्यथा अणु
				काष्ठा page *page, *orig;
				u8 *to, *from;

				page = alloc_pages(__GFP_NOWARN |
						   __GFP_COMP   | GFP_ATOMIC,
						   get_order(a + b));
				अगर (unlikely(!page))
					वापस -ENOMEM;

				sge->length = a;
				orig = sg_page(sge);
				from = sg_virt(sge);
				to = page_address(page);
				स_नकल(to, from, a);
				स_नकल(to + a, from + a + pop, b);
				sg_set_page(sge, page, a + b, 0);
				put_page(orig);
			पूर्ण
			pop = 0;
		पूर्ण अन्यथा अगर (pop >= sge->length - a) अणु
			pop -= (sge->length - a);
			sge->length = a;
		पूर्ण
	पूर्ण

	/* From above the current layout _must_ be as follows,
	 *
	 * -| offset
	 * -| start
	 *
	 *  |---- pop ---|---------------- b ------------|
	 *  |____________________________________________| length
	 *
	 * Offset and start of the current msg elem are equal because in the
	 * previous हाल we handled offset != start and either consumed the
	 * entire element and advanced to the next element OR pop == 0.
	 *
	 * Two हालs to handle here are first pop is less than the length
	 * leaving some reमुख्यder b above. Simply adjust the element's layout
	 * in this हाल. Or pop >= length of the element so that b = 0. In this
	 * हाल advance to next element decrementing pop.
	 */
	जबतक (pop) अणु
		काष्ठा scatterlist *sge = sk_msg_elem(msg, i);

		अगर (pop < sge->length) अणु
			sge->length -= pop;
			sge->offset += pop;
			pop = 0;
		पूर्ण अन्यथा अणु
			pop -= sge->length;
			sk_msg_shअगरt_left(msg, i);
		पूर्ण
		sk_msg_iter_var_next(i);
	पूर्ण

	sk_mem_unअक्षरge(msg->sk, len - pop);
	msg->sg.size -= (len - pop);
	sk_msg_compute_data_poपूर्णांकers(msg);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_msg_pop_data_proto = अणु
	.func		= bpf_msg_pop_data,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

#अगर_घोषित CONFIG_CGROUP_NET_CLASSID
BPF_CALL_0(bpf_get_cgroup_classid_curr)
अणु
	वापस __task_get_classid(current);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_cgroup_classid_curr_proto = अणु
	.func		= bpf_get_cgroup_classid_curr,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
पूर्ण;

BPF_CALL_1(bpf_skb_cgroup_classid, स्थिर काष्ठा sk_buff *, skb)
अणु
	काष्ठा sock *sk = skb_to_full_sk(skb);

	अगर (!sk || !sk_fullsock(sk))
		वापस 0;

	वापस sock_cgroup_classid(&sk->sk_cgrp_data);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_cgroup_classid_proto = अणु
	.func		= bpf_skb_cgroup_classid,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
पूर्ण;
#पूर्ण_अगर

BPF_CALL_1(bpf_get_cgroup_classid, स्थिर काष्ठा sk_buff *, skb)
अणु
	वापस task_get_classid(skb);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_cgroup_classid_proto = अणु
	.func           = bpf_get_cgroup_classid,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
पूर्ण;

BPF_CALL_1(bpf_get_route_realm, स्थिर काष्ठा sk_buff *, skb)
अणु
	वापस dst_tclassid(skb);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_route_realm_proto = अणु
	.func           = bpf_get_route_realm,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
पूर्ण;

BPF_CALL_1(bpf_get_hash_recalc, काष्ठा sk_buff *, skb)
अणु
	/* If skb_clear_hash() was called due to mangling, we can
	 * trigger SW recalculation here. Later access to hash
	 * can then use the अंतरभूत skb->hash via context directly
	 * instead of calling this helper again.
	 */
	वापस skb_get_hash(skb);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_hash_recalc_proto = अणु
	.func		= bpf_get_hash_recalc,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
पूर्ण;

BPF_CALL_1(bpf_set_hash_invalid, काष्ठा sk_buff *, skb)
अणु
	/* After all direct packet ग_लिखो, this can be used once क्रम
	 * triggering a lazy recalc on next skb_get_hash() invocation.
	 */
	skb_clear_hash(skb);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_set_hash_invalid_proto = अणु
	.func		= bpf_set_hash_invalid,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
पूर्ण;

BPF_CALL_2(bpf_set_hash, काष्ठा sk_buff *, skb, u32, hash)
अणु
	/* Set user specअगरied hash as L4(+), so that it माला_लो वापसed
	 * on skb_get_hash() call unless BPF prog later on triggers a
	 * skb_clear_hash().
	 */
	__skb_set_sw_hash(skb, hash, true);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_set_hash_proto = अणु
	.func		= bpf_set_hash,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_3(bpf_skb_vlan_push, काष्ठा sk_buff *, skb, __be16, vlan_proto,
	   u16, vlan_tci)
अणु
	पूर्णांक ret;

	अगर (unlikely(vlan_proto != htons(ETH_P_8021Q) &&
		     vlan_proto != htons(ETH_P_8021AD)))
		vlan_proto = htons(ETH_P_8021Q);

	bpf_push_mac_rcsum(skb);
	ret = skb_vlan_push(skb, vlan_proto, vlan_tci);
	bpf_pull_mac_rcsum(skb);

	bpf_compute_data_poपूर्णांकers(skb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_vlan_push_proto = अणु
	.func           = bpf_skb_vlan_push,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
	.arg2_type      = ARG_ANYTHING,
	.arg3_type      = ARG_ANYTHING,
पूर्ण;

BPF_CALL_1(bpf_skb_vlan_pop, काष्ठा sk_buff *, skb)
अणु
	पूर्णांक ret;

	bpf_push_mac_rcsum(skb);
	ret = skb_vlan_pop(skb);
	bpf_pull_mac_rcsum(skb);

	bpf_compute_data_poपूर्णांकers(skb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_vlan_pop_proto = अणु
	.func           = bpf_skb_vlan_pop,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
पूर्ण;

अटल पूर्णांक bpf_skb_generic_push(काष्ठा sk_buff *skb, u32 off, u32 len)
अणु
	/* Caller alपढ़ोy did skb_cow() with len as headroom,
	 * so no need to करो it here.
	 */
	skb_push(skb, len);
	स_हटाओ(skb->data, skb->data + len, off);
	स_रखो(skb->data + off, 0, len);

	/* No skb_postpush_rcsum(skb, skb->data + off, len)
	 * needed here as it करोes not change the skb->csum
	 * result क्रम checksum complete when summing over
	 * zeroed blocks.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_skb_generic_pop(काष्ठा sk_buff *skb, u32 off, u32 len)
अणु
	/* skb_ensure_writable() is not needed here, as we're
	 * alपढ़ोy working on an uncloned skb.
	 */
	अगर (unlikely(!pskb_may_pull(skb, off + len)))
		वापस -ENOMEM;

	skb_postpull_rcsum(skb, skb->data + off, len);
	स_हटाओ(skb->data + len, skb->data, off);
	__skb_pull(skb, len);

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_skb_net_hdr_push(काष्ठा sk_buff *skb, u32 off, u32 len)
अणु
	bool trans_same = skb->transport_header == skb->network_header;
	पूर्णांक ret;

	/* There's no need क्रम __skb_push()/__skb_pull() pair to
	 * get to the start of the mac header as we're guaranteed
	 * to always start from here under eBPF.
	 */
	ret = bpf_skb_generic_push(skb, off, len);
	अगर (likely(!ret)) अणु
		skb->mac_header -= len;
		skb->network_header -= len;
		अगर (trans_same)
			skb->transport_header = skb->network_header;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bpf_skb_net_hdr_pop(काष्ठा sk_buff *skb, u32 off, u32 len)
अणु
	bool trans_same = skb->transport_header == skb->network_header;
	पूर्णांक ret;

	/* Same here, __skb_push()/__skb_pull() pair not needed. */
	ret = bpf_skb_generic_pop(skb, off, len);
	अगर (likely(!ret)) अणु
		skb->mac_header += len;
		skb->network_header += len;
		अगर (trans_same)
			skb->transport_header = skb->network_header;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bpf_skb_proto_4_to_6(काष्ठा sk_buff *skb)
अणु
	स्थिर u32 len_dअगरf = माप(काष्ठा ipv6hdr) - माप(काष्ठा iphdr);
	u32 off = skb_mac_header_len(skb);
	पूर्णांक ret;

	अगर (skb_is_gso(skb) && !skb_is_gso_tcp(skb))
		वापस -ENOTSUPP;

	ret = skb_cow(skb, len_dअगरf);
	अगर (unlikely(ret < 0))
		वापस ret;

	ret = bpf_skb_net_hdr_push(skb, off, len_dअगरf);
	अगर (unlikely(ret < 0))
		वापस ret;

	अगर (skb_is_gso(skb)) अणु
		काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);

		/* SKB_GSO_TCPV4 needs to be changed पूर्णांकo
		 * SKB_GSO_TCPV6.
		 */
		अगर (shinfo->gso_type & SKB_GSO_TCPV4) अणु
			shinfo->gso_type &= ~SKB_GSO_TCPV4;
			shinfo->gso_type |=  SKB_GSO_TCPV6;
		पूर्ण

		/* Due to IPv6 header, MSS needs to be करोwngraded. */
		skb_decrease_gso_size(shinfo, len_dअगरf);
		/* Header must be checked, and gso_segs recomputed. */
		shinfo->gso_type |= SKB_GSO_DODGY;
		shinfo->gso_segs = 0;
	पूर्ण

	skb->protocol = htons(ETH_P_IPV6);
	skb_clear_hash(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_skb_proto_6_to_4(काष्ठा sk_buff *skb)
अणु
	स्थिर u32 len_dअगरf = माप(काष्ठा ipv6hdr) - माप(काष्ठा iphdr);
	u32 off = skb_mac_header_len(skb);
	पूर्णांक ret;

	अगर (skb_is_gso(skb) && !skb_is_gso_tcp(skb))
		वापस -ENOTSUPP;

	ret = skb_unclone(skb, GFP_ATOMIC);
	अगर (unlikely(ret < 0))
		वापस ret;

	ret = bpf_skb_net_hdr_pop(skb, off, len_dअगरf);
	अगर (unlikely(ret < 0))
		वापस ret;

	अगर (skb_is_gso(skb)) अणु
		काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);

		/* SKB_GSO_TCPV6 needs to be changed पूर्णांकo
		 * SKB_GSO_TCPV4.
		 */
		अगर (shinfo->gso_type & SKB_GSO_TCPV6) अणु
			shinfo->gso_type &= ~SKB_GSO_TCPV6;
			shinfo->gso_type |=  SKB_GSO_TCPV4;
		पूर्ण

		/* Due to IPv4 header, MSS can be upgraded. */
		skb_increase_gso_size(shinfo, len_dअगरf);
		/* Header must be checked, and gso_segs recomputed. */
		shinfo->gso_type |= SKB_GSO_DODGY;
		shinfo->gso_segs = 0;
	पूर्ण

	skb->protocol = htons(ETH_P_IP);
	skb_clear_hash(skb);

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_skb_proto_xlat(काष्ठा sk_buff *skb, __be16 to_proto)
अणु
	__be16 from_proto = skb->protocol;

	अगर (from_proto == htons(ETH_P_IP) &&
	      to_proto == htons(ETH_P_IPV6))
		वापस bpf_skb_proto_4_to_6(skb);

	अगर (from_proto == htons(ETH_P_IPV6) &&
	      to_proto == htons(ETH_P_IP))
		वापस bpf_skb_proto_6_to_4(skb);

	वापस -ENOTSUPP;
पूर्ण

BPF_CALL_3(bpf_skb_change_proto, काष्ठा sk_buff *, skb, __be16, proto,
	   u64, flags)
अणु
	पूर्णांक ret;

	अगर (unlikely(flags))
		वापस -EINVAL;

	/* General idea is that this helper करोes the basic groundwork
	 * needed क्रम changing the protocol, and eBPF program fills the
	 * rest through bpf_skb_store_bytes(), bpf_lX_csum_replace()
	 * and other helpers, rather than passing a raw buffer here.
	 *
	 * The rationale is to keep this minimal and without a need to
	 * deal with raw packet data. F.e. even अगर we would pass buffers
	 * here, the program still needs to call the bpf_lX_csum_replace()
	 * helpers anyway. Plus, this way we keep also separation of
	 * concerns, since f.e. bpf_skb_store_bytes() should only take
	 * care of stores.
	 *
	 * Currently, additional options and extension header space are
	 * not supported, but flags रेजिस्टर is reserved so we can adapt
	 * that. For offloads, we mark packet as करोdgy, so that headers
	 * need to be verअगरied first.
	 */
	ret = bpf_skb_proto_xlat(skb, proto);
	bpf_compute_data_poपूर्णांकers(skb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_change_proto_proto = अणु
	.func		= bpf_skb_change_proto,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_skb_change_type, काष्ठा sk_buff *, skb, u32, pkt_type)
अणु
	/* We only allow a restricted subset to be changed क्रम now. */
	अगर (unlikely(!skb_pkt_type_ok(skb->pkt_type) ||
		     !skb_pkt_type_ok(pkt_type)))
		वापस -EINVAL;

	skb->pkt_type = pkt_type;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_change_type_proto = अणु
	.func		= bpf_skb_change_type,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

अटल u32 bpf_skb_net_base_len(स्थिर काष्ठा sk_buff *skb)
अणु
	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		वापस माप(काष्ठा iphdr);
	हाल htons(ETH_P_IPV6):
		वापस माप(काष्ठा ipv6hdr);
	शेष:
		वापस ~0U;
	पूर्ण
पूर्ण

#घोषणा BPF_F_ADJ_ROOM_ENCAP_L3_MASK	(BPF_F_ADJ_ROOM_ENCAP_L3_IPV4 | \
					 BPF_F_ADJ_ROOM_ENCAP_L3_IPV6)

#घोषणा BPF_F_ADJ_ROOM_MASK		(BPF_F_ADJ_ROOM_FIXED_GSO | \
					 BPF_F_ADJ_ROOM_ENCAP_L3_MASK | \
					 BPF_F_ADJ_ROOM_ENCAP_L4_GRE | \
					 BPF_F_ADJ_ROOM_ENCAP_L4_UDP | \
					 BPF_F_ADJ_ROOM_ENCAP_L2_ETH | \
					 BPF_F_ADJ_ROOM_ENCAP_L2( \
					  BPF_ADJ_ROOM_ENCAP_L2_MASK))

अटल पूर्णांक bpf_skb_net_grow(काष्ठा sk_buff *skb, u32 off, u32 len_dअगरf,
			    u64 flags)
अणु
	u8 inner_mac_len = flags >> BPF_ADJ_ROOM_ENCAP_L2_SHIFT;
	bool encap = flags & BPF_F_ADJ_ROOM_ENCAP_L3_MASK;
	u16 mac_len = 0, inner_net = 0, inner_trans = 0;
	अचिन्हित पूर्णांक gso_type = SKB_GSO_DODGY;
	पूर्णांक ret;

	अगर (skb_is_gso(skb) && !skb_is_gso_tcp(skb)) अणु
		/* udp gso_size delineates datagrams, only allow अगर fixed */
		अगर (!(skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) ||
		    !(flags & BPF_F_ADJ_ROOM_FIXED_GSO))
			वापस -ENOTSUPP;
	पूर्ण

	ret = skb_cow_head(skb, len_dअगरf);
	अगर (unlikely(ret < 0))
		वापस ret;

	अगर (encap) अणु
		अगर (skb->protocol != htons(ETH_P_IP) &&
		    skb->protocol != htons(ETH_P_IPV6))
			वापस -ENOTSUPP;

		अगर (flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV4 &&
		    flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV6)
			वापस -EINVAL;

		अगर (flags & BPF_F_ADJ_ROOM_ENCAP_L4_GRE &&
		    flags & BPF_F_ADJ_ROOM_ENCAP_L4_UDP)
			वापस -EINVAL;

		अगर (flags & BPF_F_ADJ_ROOM_ENCAP_L2_ETH &&
		    inner_mac_len < ETH_HLEN)
			वापस -EINVAL;

		अगर (skb->encapsulation)
			वापस -EALREADY;

		mac_len = skb->network_header - skb->mac_header;
		inner_net = skb->network_header;
		अगर (inner_mac_len > len_dअगरf)
			वापस -EINVAL;
		inner_trans = skb->transport_header;
	पूर्ण

	ret = bpf_skb_net_hdr_push(skb, off, len_dअगरf);
	अगर (unlikely(ret < 0))
		वापस ret;

	अगर (encap) अणु
		skb->inner_mac_header = inner_net - inner_mac_len;
		skb->inner_network_header = inner_net;
		skb->inner_transport_header = inner_trans;

		अगर (flags & BPF_F_ADJ_ROOM_ENCAP_L2_ETH)
			skb_set_inner_protocol(skb, htons(ETH_P_TEB));
		अन्यथा
			skb_set_inner_protocol(skb, skb->protocol);

		skb->encapsulation = 1;
		skb_set_network_header(skb, mac_len);

		अगर (flags & BPF_F_ADJ_ROOM_ENCAP_L4_UDP)
			gso_type |= SKB_GSO_UDP_TUNNEL;
		अन्यथा अगर (flags & BPF_F_ADJ_ROOM_ENCAP_L4_GRE)
			gso_type |= SKB_GSO_GRE;
		अन्यथा अगर (flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV6)
			gso_type |= SKB_GSO_IPXIP6;
		अन्यथा अगर (flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV4)
			gso_type |= SKB_GSO_IPXIP4;

		अगर (flags & BPF_F_ADJ_ROOM_ENCAP_L4_GRE ||
		    flags & BPF_F_ADJ_ROOM_ENCAP_L4_UDP) अणु
			पूर्णांक nh_len = flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV6 ?
					माप(काष्ठा ipv6hdr) :
					माप(काष्ठा iphdr);

			skb_set_transport_header(skb, mac_len + nh_len);
		पूर्ण

		/* Match skb->protocol to new outer l3 protocol */
		अगर (skb->protocol == htons(ETH_P_IP) &&
		    flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV6)
			skb->protocol = htons(ETH_P_IPV6);
		अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6) &&
			 flags & BPF_F_ADJ_ROOM_ENCAP_L3_IPV4)
			skb->protocol = htons(ETH_P_IP);
	पूर्ण

	अगर (skb_is_gso(skb)) अणु
		काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);

		/* Due to header grow, MSS needs to be करोwngraded. */
		अगर (!(flags & BPF_F_ADJ_ROOM_FIXED_GSO))
			skb_decrease_gso_size(shinfo, len_dअगरf);

		/* Header must be checked, and gso_segs recomputed. */
		shinfo->gso_type |= gso_type;
		shinfo->gso_segs = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_skb_net_shrink(काष्ठा sk_buff *skb, u32 off, u32 len_dअगरf,
			      u64 flags)
अणु
	पूर्णांक ret;

	अगर (unlikely(flags & ~(BPF_F_ADJ_ROOM_FIXED_GSO |
			       BPF_F_ADJ_ROOM_NO_CSUM_RESET)))
		वापस -EINVAL;

	अगर (skb_is_gso(skb) && !skb_is_gso_tcp(skb)) अणु
		/* udp gso_size delineates datagrams, only allow अगर fixed */
		अगर (!(skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) ||
		    !(flags & BPF_F_ADJ_ROOM_FIXED_GSO))
			वापस -ENOTSUPP;
	पूर्ण

	ret = skb_unclone(skb, GFP_ATOMIC);
	अगर (unlikely(ret < 0))
		वापस ret;

	ret = bpf_skb_net_hdr_pop(skb, off, len_dअगरf);
	अगर (unlikely(ret < 0))
		वापस ret;

	अगर (skb_is_gso(skb)) अणु
		काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);

		/* Due to header shrink, MSS can be upgraded. */
		अगर (!(flags & BPF_F_ADJ_ROOM_FIXED_GSO))
			skb_increase_gso_size(shinfo, len_dअगरf);

		/* Header must be checked, and gso_segs recomputed. */
		shinfo->gso_type |= SKB_GSO_DODGY;
		shinfo->gso_segs = 0;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा BPF_SKB_MAX_LEN SKB_MAX_ALLOC

BPF_CALL_4(sk_skb_adjust_room, काष्ठा sk_buff *, skb, s32, len_dअगरf,
	   u32, mode, u64, flags)
अणु
	u32 len_dअगरf_असल = असल(len_dअगरf);
	bool shrink = len_dअगरf < 0;
	पूर्णांक ret = 0;

	अगर (unlikely(flags || mode))
		वापस -EINVAL;
	अगर (unlikely(len_dअगरf_असल > 0xfffU))
		वापस -EFAULT;

	अगर (!shrink) अणु
		ret = skb_cow(skb, len_dअगरf);
		अगर (unlikely(ret < 0))
			वापस ret;
		__skb_push(skb, len_dअगरf_असल);
		स_रखो(skb->data, 0, len_dअगरf_असल);
	पूर्ण अन्यथा अणु
		अगर (unlikely(!pskb_may_pull(skb, len_dअगरf_असल)))
			वापस -ENOMEM;
		__skb_pull(skb, len_dअगरf_असल);
	पूर्ण
	अगर (tls_sw_has_ctx_rx(skb->sk)) अणु
		काष्ठा strp_msg *rxm = strp_msg(skb);

		rxm->full_len += len_dअगरf;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto sk_skb_adjust_room_proto = अणु
	.func		= sk_skb_adjust_room,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_skb_adjust_room, काष्ठा sk_buff *, skb, s32, len_dअगरf,
	   u32, mode, u64, flags)
अणु
	u32 len_cur, len_dअगरf_असल = असल(len_dअगरf);
	u32 len_min = bpf_skb_net_base_len(skb);
	u32 len_max = BPF_SKB_MAX_LEN;
	__be16 proto = skb->protocol;
	bool shrink = len_dअगरf < 0;
	u32 off;
	पूर्णांक ret;

	अगर (unlikely(flags & ~(BPF_F_ADJ_ROOM_MASK |
			       BPF_F_ADJ_ROOM_NO_CSUM_RESET)))
		वापस -EINVAL;
	अगर (unlikely(len_dअगरf_असल > 0xfffU))
		वापस -EFAULT;
	अगर (unlikely(proto != htons(ETH_P_IP) &&
		     proto != htons(ETH_P_IPV6)))
		वापस -ENOTSUPP;

	off = skb_mac_header_len(skb);
	चयन (mode) अणु
	हाल BPF_ADJ_ROOM_NET:
		off += bpf_skb_net_base_len(skb);
		अवरोध;
	हाल BPF_ADJ_ROOM_MAC:
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	len_cur = skb->len - skb_network_offset(skb);
	अगर ((shrink && (len_dअगरf_असल >= len_cur ||
			len_cur - len_dअगरf_असल < len_min)) ||
	    (!shrink && (skb->len + len_dअगरf_असल > len_max &&
			 !skb_is_gso(skb))))
		वापस -ENOTSUPP;

	ret = shrink ? bpf_skb_net_shrink(skb, off, len_dअगरf_असल, flags) :
		       bpf_skb_net_grow(skb, off, len_dअगरf_असल, flags);
	अगर (!ret && !(flags & BPF_F_ADJ_ROOM_NO_CSUM_RESET))
		__skb_reset_checksum_unnecessary(skb);

	bpf_compute_data_poपूर्णांकers(skb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_adjust_room_proto = अणु
	.func		= bpf_skb_adjust_room,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

अटल u32 __bpf_skb_min_len(स्थिर काष्ठा sk_buff *skb)
अणु
	u32 min_len = skb_network_offset(skb);

	अगर (skb_transport_header_was_set(skb))
		min_len = skb_transport_offset(skb);
	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		min_len = skb_checksum_start_offset(skb) +
			  skb->csum_offset + माप(__sum16);
	वापस min_len;
पूर्ण

अटल पूर्णांक bpf_skb_grow_rcsum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक new_len)
अणु
	अचिन्हित पूर्णांक old_len = skb->len;
	पूर्णांक ret;

	ret = __skb_grow_rcsum(skb, new_len);
	अगर (!ret)
		स_रखो(skb->data + old_len, 0, new_len - old_len);
	वापस ret;
पूर्ण

अटल पूर्णांक bpf_skb_trim_rcsum(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक new_len)
अणु
	वापस __skb_trim_rcsum(skb, new_len);
पूर्ण

अटल अंतरभूत पूर्णांक __bpf_skb_change_tail(काष्ठा sk_buff *skb, u32 new_len,
					u64 flags)
अणु
	u32 max_len = BPF_SKB_MAX_LEN;
	u32 min_len = __bpf_skb_min_len(skb);
	पूर्णांक ret;

	अगर (unlikely(flags || new_len > max_len || new_len < min_len))
		वापस -EINVAL;
	अगर (skb->encapsulation)
		वापस -ENOTSUPP;

	/* The basic idea of this helper is that it's perक्रमming the
	 * needed work to either grow or trim an skb, and eBPF program
	 * reग_लिखोs the rest via helpers like bpf_skb_store_bytes(),
	 * bpf_lX_csum_replace() and others rather than passing a raw
	 * buffer here. This one is a slow path helper and पूर्णांकended
	 * क्रम replies with control messages.
	 *
	 * Like in bpf_skb_change_proto(), we want to keep this rather
	 * minimal and without protocol specअगरics so that we are able
	 * to separate concerns as in bpf_skb_store_bytes() should only
	 * be the one responsible क्रम writing buffers.
	 *
	 * It's really expected to be a slow path operation here क्रम
	 * control message replies, so we're implicitly linearizing,
	 * uncloning and drop offloads from the skb by this.
	 */
	ret = __bpf_try_make_writable(skb, skb->len);
	अगर (!ret) अणु
		अगर (new_len > skb->len)
			ret = bpf_skb_grow_rcsum(skb, new_len);
		अन्यथा अगर (new_len < skb->len)
			ret = bpf_skb_trim_rcsum(skb, new_len);
		अगर (!ret && skb_is_gso(skb))
			skb_gso_reset(skb);
	पूर्ण
	वापस ret;
पूर्ण

BPF_CALL_3(bpf_skb_change_tail, काष्ठा sk_buff *, skb, u32, new_len,
	   u64, flags)
अणु
	पूर्णांक ret = __bpf_skb_change_tail(skb, new_len, flags);

	bpf_compute_data_poपूर्णांकers(skb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_change_tail_proto = अणु
	.func		= bpf_skb_change_tail,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_3(sk_skb_change_tail, काष्ठा sk_buff *, skb, u32, new_len,
	   u64, flags)
अणु
	वापस __bpf_skb_change_tail(skb, new_len, flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto sk_skb_change_tail_proto = अणु
	.func		= sk_skb_change_tail,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

अटल अंतरभूत पूर्णांक __bpf_skb_change_head(काष्ठा sk_buff *skb, u32 head_room,
					u64 flags)
अणु
	u32 max_len = BPF_SKB_MAX_LEN;
	u32 new_len = skb->len + head_room;
	पूर्णांक ret;

	अगर (unlikely(flags || (!skb_is_gso(skb) && new_len > max_len) ||
		     new_len < skb->len))
		वापस -EINVAL;

	ret = skb_cow(skb, head_room);
	अगर (likely(!ret)) अणु
		/* Idea क्रम this helper is that we currently only
		 * allow to expand on mac header. This means that
		 * skb->protocol network header, etc, stay as is.
		 * Compared to bpf_skb_change_tail(), we're more
		 * flexible due to not needing to linearize or
		 * reset GSO. Intention क्रम this helper is to be
		 * used by an L3 skb that needs to push mac header
		 * क्रम redirection पूर्णांकo L2 device.
		 */
		__skb_push(skb, head_room);
		स_रखो(skb->data, 0, head_room);
		skb_reset_mac_header(skb);
		skb_reset_mac_len(skb);
	पूर्ण

	वापस ret;
पूर्ण

BPF_CALL_3(bpf_skb_change_head, काष्ठा sk_buff *, skb, u32, head_room,
	   u64, flags)
अणु
	पूर्णांक ret = __bpf_skb_change_head(skb, head_room, flags);

	bpf_compute_data_poपूर्णांकers(skb);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_change_head_proto = अणु
	.func		= bpf_skb_change_head,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_3(sk_skb_change_head, काष्ठा sk_buff *, skb, u32, head_room,
	   u64, flags)
अणु
	वापस __bpf_skb_change_head(skb, head_room, flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto sk_skb_change_head_proto = अणु
	.func		= sk_skb_change_head,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;
अटल अचिन्हित दीर्घ xdp_get_metalen(स्थिर काष्ठा xdp_buff *xdp)
अणु
	वापस xdp_data_meta_unsupported(xdp) ? 0 :
	       xdp->data - xdp->data_meta;
पूर्ण

BPF_CALL_2(bpf_xdp_adjust_head, काष्ठा xdp_buff *, xdp, पूर्णांक, offset)
अणु
	व्योम *xdp_frame_end = xdp->data_hard_start + माप(काष्ठा xdp_frame);
	अचिन्हित दीर्घ metalen = xdp_get_metalen(xdp);
	व्योम *data_start = xdp_frame_end + metalen;
	व्योम *data = xdp->data + offset;

	अगर (unlikely(data < data_start ||
		     data > xdp->data_end - ETH_HLEN))
		वापस -EINVAL;

	अगर (metalen)
		स_हटाओ(xdp->data_meta + offset,
			xdp->data_meta, metalen);
	xdp->data_meta += offset;
	xdp->data = data;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_xdp_adjust_head_proto = अणु
	.func		= bpf_xdp_adjust_head,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_xdp_adjust_tail, काष्ठा xdp_buff *, xdp, पूर्णांक, offset)
अणु
	व्योम *data_hard_end = xdp_data_hard_end(xdp); /* use xdp->frame_sz */
	व्योम *data_end = xdp->data_end + offset;

	/* Notice that xdp_data_hard_end have reserved some tailroom */
	अगर (unlikely(data_end > data_hard_end))
		वापस -EINVAL;

	/* ALL drivers MUST init xdp->frame_sz, chicken check below */
	अगर (unlikely(xdp->frame_sz > PAGE_SIZE)) अणु
		WARN_ONCE(1, "Too BIG xdp->frame_sz = %d\n", xdp->frame_sz);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(data_end < xdp->data + ETH_HLEN))
		वापस -EINVAL;

	/* Clear memory area on grow, can contain uninit kernel memory */
	अगर (offset > 0)
		स_रखो(xdp->data_end, 0, offset);

	xdp->data_end = data_end;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_xdp_adjust_tail_proto = अणु
	.func		= bpf_xdp_adjust_tail,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_xdp_adjust_meta, काष्ठा xdp_buff *, xdp, पूर्णांक, offset)
अणु
	व्योम *xdp_frame_end = xdp->data_hard_start + माप(काष्ठा xdp_frame);
	व्योम *meta = xdp->data_meta + offset;
	अचिन्हित दीर्घ metalen = xdp->data - meta;

	अगर (xdp_data_meta_unsupported(xdp))
		वापस -ENOTSUPP;
	अगर (unlikely(meta < xdp_frame_end ||
		     meta > xdp->data))
		वापस -EINVAL;
	अगर (unlikely((metalen & (माप(__u32) - 1)) ||
		     (metalen > 32)))
		वापस -EACCES;

	xdp->data_meta = meta;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_xdp_adjust_meta_proto = अणु
	.func		= bpf_xdp_adjust_meta,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

व्योम xdp_करो_flush(व्योम)
अणु
	__dev_flush();
	__cpu_map_flush();
	__xsk_map_flush();
पूर्ण
EXPORT_SYMBOL_GPL(xdp_करो_flush);

पूर्णांक xdp_करो_redirect(काष्ठा net_device *dev, काष्ठा xdp_buff *xdp,
		    काष्ठा bpf_prog *xdp_prog)
अणु
	काष्ठा bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);
	क्रमागत bpf_map_type map_type = ri->map_type;
	व्योम *fwd = ri->tgt_value;
	u32 map_id = ri->map_id;
	पूर्णांक err;

	ri->map_id = 0; /* Valid map id idr range: [1,पूर्णांक_उच्च[ */
	ri->map_type = BPF_MAP_TYPE_UNSPEC;

	चयन (map_type) अणु
	हाल BPF_MAP_TYPE_DEVMAP:
		fallthrough;
	हाल BPF_MAP_TYPE_DEVMAP_HASH:
		err = dev_map_enqueue(fwd, xdp, dev);
		अवरोध;
	हाल BPF_MAP_TYPE_CPUMAP:
		err = cpu_map_enqueue(fwd, xdp, dev);
		अवरोध;
	हाल BPF_MAP_TYPE_XSKMAP:
		err = __xsk_map_redirect(fwd, xdp);
		अवरोध;
	हाल BPF_MAP_TYPE_UNSPEC:
		अगर (map_id == पूर्णांक_उच्च) अणु
			fwd = dev_get_by_index_rcu(dev_net(dev), ri->tgt_index);
			अगर (unlikely(!fwd)) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			err = dev_xdp_enqueue(fwd, xdp, dev);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		err = -EBADRQC;
	पूर्ण

	अगर (unlikely(err))
		जाओ err;

	_trace_xdp_redirect_map(dev, xdp_prog, fwd, map_type, map_id, ri->tgt_index);
	वापस 0;
err:
	_trace_xdp_redirect_map_err(dev, xdp_prog, fwd, map_type, map_id, ri->tgt_index, err);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(xdp_करो_redirect);

अटल पूर्णांक xdp_करो_generic_redirect_map(काष्ठा net_device *dev,
				       काष्ठा sk_buff *skb,
				       काष्ठा xdp_buff *xdp,
				       काष्ठा bpf_prog *xdp_prog,
				       व्योम *fwd,
				       क्रमागत bpf_map_type map_type, u32 map_id)
अणु
	काष्ठा bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);
	पूर्णांक err;

	चयन (map_type) अणु
	हाल BPF_MAP_TYPE_DEVMAP:
		fallthrough;
	हाल BPF_MAP_TYPE_DEVMAP_HASH:
		err = dev_map_generic_redirect(fwd, skb, xdp_prog);
		अगर (unlikely(err))
			जाओ err;
		अवरोध;
	हाल BPF_MAP_TYPE_XSKMAP:
		err = xsk_generic_rcv(fwd, xdp);
		अगर (err)
			जाओ err;
		consume_skb(skb);
		अवरोध;
	शेष:
		/* TODO: Handle BPF_MAP_TYPE_CPUMAP */
		err = -EBADRQC;
		जाओ err;
	पूर्ण

	_trace_xdp_redirect_map(dev, xdp_prog, fwd, map_type, map_id, ri->tgt_index);
	वापस 0;
err:
	_trace_xdp_redirect_map_err(dev, xdp_prog, fwd, map_type, map_id, ri->tgt_index, err);
	वापस err;
पूर्ण

पूर्णांक xdp_करो_generic_redirect(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			    काष्ठा xdp_buff *xdp, काष्ठा bpf_prog *xdp_prog)
अणु
	काष्ठा bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);
	क्रमागत bpf_map_type map_type = ri->map_type;
	व्योम *fwd = ri->tgt_value;
	u32 map_id = ri->map_id;
	पूर्णांक err;

	ri->map_id = 0; /* Valid map id idr range: [1,पूर्णांक_उच्च[ */
	ri->map_type = BPF_MAP_TYPE_UNSPEC;

	अगर (map_type == BPF_MAP_TYPE_UNSPEC && map_id == पूर्णांक_उच्च) अणु
		fwd = dev_get_by_index_rcu(dev_net(dev), ri->tgt_index);
		अगर (unlikely(!fwd)) अणु
			err = -EINVAL;
			जाओ err;
		पूर्ण

		err = xdp_ok_fwd_dev(fwd, skb->len);
		अगर (unlikely(err))
			जाओ err;

		skb->dev = fwd;
		_trace_xdp_redirect(dev, xdp_prog, ri->tgt_index);
		generic_xdp_tx(skb, xdp_prog);
		वापस 0;
	पूर्ण

	वापस xdp_करो_generic_redirect_map(dev, skb, xdp, xdp_prog, fwd, map_type, map_id);
err:
	_trace_xdp_redirect_err(dev, xdp_prog, ri->tgt_index, err);
	वापस err;
पूर्ण

BPF_CALL_2(bpf_xdp_redirect, u32, अगरindex, u64, flags)
अणु
	काष्ठा bpf_redirect_info *ri = this_cpu_ptr(&bpf_redirect_info);

	अगर (unlikely(flags))
		वापस XDP_ABORTED;

	/* NB! Map type UNSPEC and map_id == पूर्णांक_उच्च (never generated
	 * by map_idr) is used क्रम अगरindex based XDP redirect.
	 */
	ri->tgt_index = अगरindex;
	ri->map_id = पूर्णांक_उच्च;
	ri->map_type = BPF_MAP_TYPE_UNSPEC;

	वापस XDP_REसूचीECT;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_xdp_redirect_proto = अणु
	.func           = bpf_xdp_redirect,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_ANYTHING,
	.arg2_type      = ARG_ANYTHING,
पूर्ण;

BPF_CALL_3(bpf_xdp_redirect_map, काष्ठा bpf_map *, map, u32, अगरindex,
	   u64, flags)
अणु
	वापस map->ops->map_redirect(map, अगरindex, flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_xdp_redirect_map_proto = अणु
	.func           = bpf_xdp_redirect_map,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_CONST_MAP_PTR,
	.arg2_type      = ARG_ANYTHING,
	.arg3_type      = ARG_ANYTHING,
पूर्ण;

अटल अचिन्हित दीर्घ bpf_skb_copy(व्योम *dst_buff, स्थिर व्योम *skb,
				  अचिन्हित दीर्घ off, अचिन्हित दीर्घ len)
अणु
	व्योम *ptr = skb_header_poपूर्णांकer(skb, off, len, dst_buff);

	अगर (unlikely(!ptr))
		वापस len;
	अगर (ptr != dst_buff)
		स_नकल(dst_buff, ptr, len);

	वापस 0;
पूर्ण

BPF_CALL_5(bpf_skb_event_output, काष्ठा sk_buff *, skb, काष्ठा bpf_map *, map,
	   u64, flags, व्योम *, meta, u64, meta_size)
अणु
	u64 skb_size = (flags & BPF_F_CTXLEN_MASK) >> 32;

	अगर (unlikely(flags & ~(BPF_F_CTXLEN_MASK | BPF_F_INDEX_MASK)))
		वापस -EINVAL;
	अगर (unlikely(!skb || skb_size > skb->len))
		वापस -EFAULT;

	वापस bpf_event_output(map, flags, meta, meta_size, skb, skb_size,
				bpf_skb_copy);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_event_output_proto = अणु
	.func		= bpf_skb_event_output,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_PTR_TO_MEM,
	.arg5_type	= ARG_CONST_SIZE_OR_ZERO,
पूर्ण;

BTF_ID_LIST_SINGLE(bpf_skb_output_btf_ids, काष्ठा, sk_buff)

स्थिर काष्ठा bpf_func_proto bpf_skb_output_proto = अणु
	.func		= bpf_skb_event_output,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID,
	.arg1_btf_id	= &bpf_skb_output_btf_ids[0],
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_PTR_TO_MEM,
	.arg5_type	= ARG_CONST_SIZE_OR_ZERO,
पूर्ण;

अटल अचिन्हित लघु bpf_tunnel_key_af(u64 flags)
अणु
	वापस flags & BPF_F_TUNINFO_IPV6 ? AF_INET6 : AF_INET;
पूर्ण

BPF_CALL_4(bpf_skb_get_tunnel_key, काष्ठा sk_buff *, skb, काष्ठा bpf_tunnel_key *, to,
	   u32, size, u64, flags)
अणु
	स्थिर काष्ठा ip_tunnel_info *info = skb_tunnel_info(skb);
	u8 compat[माप(काष्ठा bpf_tunnel_key)];
	व्योम *to_orig = to;
	पूर्णांक err;

	अगर (unlikely(!info || (flags & ~(BPF_F_TUNINFO_IPV6)))) अणु
		err = -EINVAL;
		जाओ err_clear;
	पूर्ण
	अगर (ip_tunnel_info_af(info) != bpf_tunnel_key_af(flags)) अणु
		err = -EPROTO;
		जाओ err_clear;
	पूर्ण
	अगर (unlikely(size != माप(काष्ठा bpf_tunnel_key))) अणु
		err = -EINVAL;
		चयन (size) अणु
		हाल दुरत्व(काष्ठा bpf_tunnel_key, tunnel_label):
		हाल दुरत्व(काष्ठा bpf_tunnel_key, tunnel_ext):
			जाओ set_compat;
		हाल दुरत्व(काष्ठा bpf_tunnel_key, remote_ipv6[1]):
			/* Fixup deprecated काष्ठाure layouts here, so we have
			 * a common path later on.
			 */
			अगर (ip_tunnel_info_af(info) != AF_INET)
				जाओ err_clear;
set_compat:
			to = (काष्ठा bpf_tunnel_key *)compat;
			अवरोध;
		शेष:
			जाओ err_clear;
		पूर्ण
	पूर्ण

	to->tunnel_id = be64_to_cpu(info->key.tun_id);
	to->tunnel_tos = info->key.tos;
	to->tunnel_ttl = info->key.ttl;
	to->tunnel_ext = 0;

	अगर (flags & BPF_F_TUNINFO_IPV6) अणु
		स_नकल(to->remote_ipv6, &info->key.u.ipv6.src,
		       माप(to->remote_ipv6));
		to->tunnel_label = be32_to_cpu(info->key.label);
	पूर्ण अन्यथा अणु
		to->remote_ipv4 = be32_to_cpu(info->key.u.ipv4.src);
		स_रखो(&to->remote_ipv6[1], 0, माप(__u32) * 3);
		to->tunnel_label = 0;
	पूर्ण

	अगर (unlikely(size != माप(काष्ठा bpf_tunnel_key)))
		स_नकल(to_orig, to, size);

	वापस 0;
err_clear:
	स_रखो(to_orig, 0, size);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_get_tunnel_key_proto = अणु
	.func		= bpf_skb_get_tunnel_key,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_3(bpf_skb_get_tunnel_opt, काष्ठा sk_buff *, skb, u8 *, to, u32, size)
अणु
	स्थिर काष्ठा ip_tunnel_info *info = skb_tunnel_info(skb);
	पूर्णांक err;

	अगर (unlikely(!info ||
		     !(info->key.tun_flags & TUNNEL_OPTIONS_PRESENT))) अणु
		err = -ENOENT;
		जाओ err_clear;
	पूर्ण
	अगर (unlikely(size < info->options_len)) अणु
		err = -ENOMEM;
		जाओ err_clear;
	पूर्ण

	ip_tunnel_info_opts_get(to, info);
	अगर (size > info->options_len)
		स_रखो(to + info->options_len, 0, size - info->options_len);

	वापस info->options_len;
err_clear:
	स_रखो(to, 0, size);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_get_tunnel_opt_proto = अणु
	.func		= bpf_skb_get_tunnel_opt,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg3_type	= ARG_CONST_SIZE,
पूर्ण;

अटल काष्ठा metadata_dst __percpu *md_dst;

BPF_CALL_4(bpf_skb_set_tunnel_key, काष्ठा sk_buff *, skb,
	   स्थिर काष्ठा bpf_tunnel_key *, from, u32, size, u64, flags)
अणु
	काष्ठा metadata_dst *md = this_cpu_ptr(md_dst);
	u8 compat[माप(काष्ठा bpf_tunnel_key)];
	काष्ठा ip_tunnel_info *info;

	अगर (unlikely(flags & ~(BPF_F_TUNINFO_IPV6 | BPF_F_ZERO_CSUM_TX |
			       BPF_F_DONT_FRAGMENT | BPF_F_SEQ_NUMBER)))
		वापस -EINVAL;
	अगर (unlikely(size != माप(काष्ठा bpf_tunnel_key))) अणु
		चयन (size) अणु
		हाल दुरत्व(काष्ठा bpf_tunnel_key, tunnel_label):
		हाल दुरत्व(काष्ठा bpf_tunnel_key, tunnel_ext):
		हाल दुरत्व(काष्ठा bpf_tunnel_key, remote_ipv6[1]):
			/* Fixup deprecated काष्ठाure layouts here, so we have
			 * a common path later on.
			 */
			स_नकल(compat, from, size);
			स_रखो(compat + size, 0, माप(compat) - size);
			from = (स्थिर काष्ठा bpf_tunnel_key *) compat;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (unlikely((!(flags & BPF_F_TUNINFO_IPV6) && from->tunnel_label) ||
		     from->tunnel_ext))
		वापस -EINVAL;

	skb_dst_drop(skb);
	dst_hold((काष्ठा dst_entry *) md);
	skb_dst_set(skb, (काष्ठा dst_entry *) md);

	info = &md->u.tun_info;
	स_रखो(info, 0, माप(*info));
	info->mode = IP_TUNNEL_INFO_TX;

	info->key.tun_flags = TUNNEL_KEY | TUNNEL_CSUM | TUNNEL_NOCACHE;
	अगर (flags & BPF_F_DONT_FRAGMENT)
		info->key.tun_flags |= TUNNEL_DONT_FRAGMENT;
	अगर (flags & BPF_F_ZERO_CSUM_TX)
		info->key.tun_flags &= ~TUNNEL_CSUM;
	अगर (flags & BPF_F_SEQ_NUMBER)
		info->key.tun_flags |= TUNNEL_SEQ;

	info->key.tun_id = cpu_to_be64(from->tunnel_id);
	info->key.tos = from->tunnel_tos;
	info->key.ttl = from->tunnel_ttl;

	अगर (flags & BPF_F_TUNINFO_IPV6) अणु
		info->mode |= IP_TUNNEL_INFO_IPV6;
		स_नकल(&info->key.u.ipv6.dst, from->remote_ipv6,
		       माप(from->remote_ipv6));
		info->key.label = cpu_to_be32(from->tunnel_label) &
				  IPV6_FLOWLABEL_MASK;
	पूर्ण अन्यथा अणु
		info->key.u.ipv4.dst = cpu_to_be32(from->remote_ipv4);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_set_tunnel_key_proto = अणु
	.func		= bpf_skb_set_tunnel_key,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_3(bpf_skb_set_tunnel_opt, काष्ठा sk_buff *, skb,
	   स्थिर u8 *, from, u32, size)
अणु
	काष्ठा ip_tunnel_info *info = skb_tunnel_info(skb);
	स्थिर काष्ठा metadata_dst *md = this_cpu_ptr(md_dst);

	अगर (unlikely(info != &md->u.tun_info || (size & (माप(u32) - 1))))
		वापस -EINVAL;
	अगर (unlikely(size > IP_TUNNEL_OPTS_MAX))
		वापस -ENOMEM;

	ip_tunnel_info_opts_set(info, from, size, TUNNEL_OPTIONS_PRESENT);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_set_tunnel_opt_proto = अणु
	.func		= bpf_skb_set_tunnel_opt,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto *
bpf_get_skb_set_tunnel_proto(क्रमागत bpf_func_id which)
अणु
	अगर (!md_dst) अणु
		काष्ठा metadata_dst __percpu *पंचांगp;

		पंचांगp = metadata_dst_alloc_percpu(IP_TUNNEL_OPTS_MAX,
						METADATA_IP_TUNNEL,
						GFP_KERNEL);
		अगर (!पंचांगp)
			वापस शून्य;
		अगर (cmpxchg(&md_dst, शून्य, पंचांगp))
			metadata_dst_मुक्त_percpu(पंचांगp);
	पूर्ण

	चयन (which) अणु
	हाल BPF_FUNC_skb_set_tunnel_key:
		वापस &bpf_skb_set_tunnel_key_proto;
	हाल BPF_FUNC_skb_set_tunnel_opt:
		वापस &bpf_skb_set_tunnel_opt_proto;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

BPF_CALL_3(bpf_skb_under_cgroup, काष्ठा sk_buff *, skb, काष्ठा bpf_map *, map,
	   u32, idx)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	काष्ठा cgroup *cgrp;
	काष्ठा sock *sk;

	sk = skb_to_full_sk(skb);
	अगर (!sk || !sk_fullsock(sk))
		वापस -ENOENT;
	अगर (unlikely(idx >= array->map.max_entries))
		वापस -E2BIG;

	cgrp = READ_ONCE(array->ptrs[idx]);
	अगर (unlikely(!cgrp))
		वापस -EAGAIN;

	वापस sk_under_cgroup_hierarchy(sk, cgrp);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_under_cgroup_proto = अणु
	.func		= bpf_skb_under_cgroup,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
अटल अंतरभूत u64 __bpf_sk_cgroup_id(काष्ठा sock *sk)
अणु
	काष्ठा cgroup *cgrp;

	sk = sk_to_full_sk(sk);
	अगर (!sk || !sk_fullsock(sk))
		वापस 0;

	cgrp = sock_cgroup_ptr(&sk->sk_cgrp_data);
	वापस cgroup_id(cgrp);
पूर्ण

BPF_CALL_1(bpf_skb_cgroup_id, स्थिर काष्ठा sk_buff *, skb)
अणु
	वापस __bpf_sk_cgroup_id(skb->sk);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_cgroup_id_proto = अणु
	.func           = bpf_skb_cgroup_id,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
पूर्ण;

अटल अंतरभूत u64 __bpf_sk_ancestor_cgroup_id(काष्ठा sock *sk,
					      पूर्णांक ancestor_level)
अणु
	काष्ठा cgroup *ancestor;
	काष्ठा cgroup *cgrp;

	sk = sk_to_full_sk(sk);
	अगर (!sk || !sk_fullsock(sk))
		वापस 0;

	cgrp = sock_cgroup_ptr(&sk->sk_cgrp_data);
	ancestor = cgroup_ancestor(cgrp, ancestor_level);
	अगर (!ancestor)
		वापस 0;

	वापस cgroup_id(ancestor);
पूर्ण

BPF_CALL_2(bpf_skb_ancestor_cgroup_id, स्थिर काष्ठा sk_buff *, skb, पूर्णांक,
	   ancestor_level)
अणु
	वापस __bpf_sk_ancestor_cgroup_id(skb->sk, ancestor_level);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_ancestor_cgroup_id_proto = अणु
	.func           = bpf_skb_ancestor_cgroup_id,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
	.arg2_type      = ARG_ANYTHING,
पूर्ण;

BPF_CALL_1(bpf_sk_cgroup_id, काष्ठा sock *, sk)
अणु
	वापस __bpf_sk_cgroup_id(sk);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sk_cgroup_id_proto = अणु
	.func           = bpf_sk_cgroup_id,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_BTF_ID_SOCK_COMMON,
पूर्ण;

BPF_CALL_2(bpf_sk_ancestor_cgroup_id, काष्ठा sock *, sk, पूर्णांक, ancestor_level)
अणु
	वापस __bpf_sk_ancestor_cgroup_id(sk, ancestor_level);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sk_ancestor_cgroup_id_proto = अणु
	.func           = bpf_sk_ancestor_cgroup_id,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_BTF_ID_SOCK_COMMON,
	.arg2_type      = ARG_ANYTHING,
पूर्ण;
#पूर्ण_अगर

अटल अचिन्हित दीर्घ bpf_xdp_copy(व्योम *dst_buff, स्थिर व्योम *src_buff,
				  अचिन्हित दीर्घ off, अचिन्हित दीर्घ len)
अणु
	स_नकल(dst_buff, src_buff + off, len);
	वापस 0;
पूर्ण

BPF_CALL_5(bpf_xdp_event_output, काष्ठा xdp_buff *, xdp, काष्ठा bpf_map *, map,
	   u64, flags, व्योम *, meta, u64, meta_size)
अणु
	u64 xdp_size = (flags & BPF_F_CTXLEN_MASK) >> 32;

	अगर (unlikely(flags & ~(BPF_F_CTXLEN_MASK | BPF_F_INDEX_MASK)))
		वापस -EINVAL;
	अगर (unlikely(!xdp ||
		     xdp_size > (अचिन्हित दीर्घ)(xdp->data_end - xdp->data)))
		वापस -EFAULT;

	वापस bpf_event_output(map, flags, meta, meta_size, xdp->data,
				xdp_size, bpf_xdp_copy);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_xdp_event_output_proto = अणु
	.func		= bpf_xdp_event_output,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_PTR_TO_MEM,
	.arg5_type	= ARG_CONST_SIZE_OR_ZERO,
पूर्ण;

BTF_ID_LIST_SINGLE(bpf_xdp_output_btf_ids, काष्ठा, xdp_buff)

स्थिर काष्ठा bpf_func_proto bpf_xdp_output_proto = अणु
	.func		= bpf_xdp_event_output,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID,
	.arg1_btf_id	= &bpf_xdp_output_btf_ids[0],
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_PTR_TO_MEM,
	.arg5_type	= ARG_CONST_SIZE_OR_ZERO,
पूर्ण;

BPF_CALL_1(bpf_get_socket_cookie, काष्ठा sk_buff *, skb)
अणु
	वापस skb->sk ? __sock_gen_cookie(skb->sk) : 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_socket_cookie_proto = अणु
	.func           = bpf_get_socket_cookie,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
पूर्ण;

BPF_CALL_1(bpf_get_socket_cookie_sock_addr, काष्ठा bpf_sock_addr_kern *, ctx)
अणु
	वापस __sock_gen_cookie(ctx->sk);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_socket_cookie_sock_addr_proto = अणु
	.func		= bpf_get_socket_cookie_sock_addr,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
पूर्ण;

BPF_CALL_1(bpf_get_socket_cookie_sock, काष्ठा sock *, ctx)
अणु
	वापस __sock_gen_cookie(ctx);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_socket_cookie_sock_proto = अणु
	.func		= bpf_get_socket_cookie_sock,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
पूर्ण;

BPF_CALL_1(bpf_get_socket_ptr_cookie, काष्ठा sock *, sk)
अणु
	वापस sk ? sock_gen_cookie(sk) : 0;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_socket_ptr_cookie_proto = अणु
	.func		= bpf_get_socket_ptr_cookie,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID_SOCK_COMMON,
पूर्ण;

BPF_CALL_1(bpf_get_socket_cookie_sock_ops, काष्ठा bpf_sock_ops_kern *, ctx)
अणु
	वापस __sock_gen_cookie(ctx->sk);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_socket_cookie_sock_ops_proto = अणु
	.func		= bpf_get_socket_cookie_sock_ops,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
पूर्ण;

अटल u64 __bpf_get_netns_cookie(काष्ठा sock *sk)
अणु
	स्थिर काष्ठा net *net = sk ? sock_net(sk) : &init_net;

	वापस net->net_cookie;
पूर्ण

BPF_CALL_1(bpf_get_netns_cookie_sock, काष्ठा sock *, ctx)
अणु
	वापस __bpf_get_netns_cookie(ctx);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_netns_cookie_sock_proto = अणु
	.func		= bpf_get_netns_cookie_sock,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX_OR_शून्य,
पूर्ण;

BPF_CALL_1(bpf_get_netns_cookie_sock_addr, काष्ठा bpf_sock_addr_kern *, ctx)
अणु
	वापस __bpf_get_netns_cookie(ctx ? ctx->sk : शून्य);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_netns_cookie_sock_addr_proto = अणु
	.func		= bpf_get_netns_cookie_sock_addr,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX_OR_शून्य,
पूर्ण;

BPF_CALL_1(bpf_get_socket_uid, काष्ठा sk_buff *, skb)
अणु
	काष्ठा sock *sk = sk_to_full_sk(skb->sk);
	kuid_t kuid;

	अगर (!sk || !sk_fullsock(sk))
		वापस overflowuid;
	kuid = sock_net_uid(sock_net(sk), sk);
	वापस from_kuid_munged(sock_net(sk)->user_ns, kuid);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_socket_uid_proto = अणु
	.func           = bpf_get_socket_uid,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
पूर्ण;

अटल पूर्णांक _bpf_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			   अक्षर *optval, पूर्णांक optlen)
अणु
	अक्षर devname[IFNAMSIZ];
	पूर्णांक val, valbool;
	काष्ठा net *net;
	पूर्णांक अगरindex;
	पूर्णांक ret = 0;

	अगर (!sk_fullsock(sk))
		वापस -EINVAL;

	sock_owned_by_me(sk);

	अगर (level == SOL_SOCKET) अणु
		अगर (optlen != माप(पूर्णांक) && optname != SO_BINDTODEVICE)
			वापस -EINVAL;
		val = *((पूर्णांक *)optval);
		valbool = val ? 1 : 0;

		/* Only some socketops are supported */
		चयन (optname) अणु
		हाल SO_RCVBUF:
			val = min_t(u32, val, sysctl_rmem_max);
			sk->sk_userlocks |= SOCK_RCVBUF_LOCK;
			WRITE_ONCE(sk->sk_rcvbuf,
				   max_t(पूर्णांक, val * 2, SOCK_MIN_RCVBUF));
			अवरोध;
		हाल SO_SNDBUF:
			val = min_t(u32, val, sysctl_wmem_max);
			sk->sk_userlocks |= SOCK_SNDBUF_LOCK;
			WRITE_ONCE(sk->sk_sndbuf,
				   max_t(पूर्णांक, val * 2, SOCK_MIN_SNDBUF));
			अवरोध;
		हाल SO_MAX_PACING_RATE: /* 32bit version */
			अगर (val != ~0U)
				cmpxchg(&sk->sk_pacing_status,
					SK_PACING_NONE,
					SK_PACING_NEEDED);
			sk->sk_max_pacing_rate = (val == ~0U) ?
						 ~0UL : (अचिन्हित पूर्णांक)val;
			sk->sk_pacing_rate = min(sk->sk_pacing_rate,
						 sk->sk_max_pacing_rate);
			अवरोध;
		हाल SO_PRIORITY:
			sk->sk_priority = val;
			अवरोध;
		हाल SO_RCVLOWAT:
			अगर (val < 0)
				val = पूर्णांक_उच्च;
			WRITE_ONCE(sk->sk_rcvlowat, val ? : 1);
			अवरोध;
		हाल SO_MARK:
			अगर (sk->sk_mark != val) अणु
				sk->sk_mark = val;
				sk_dst_reset(sk);
			पूर्ण
			अवरोध;
		हाल SO_BINDTODEVICE:
			optlen = min_t(दीर्घ, optlen, IFNAMSIZ - 1);
			म_नकलन(devname, optval, optlen);
			devname[optlen] = 0;

			अगरindex = 0;
			अगर (devname[0] != '\0') अणु
				काष्ठा net_device *dev;

				ret = -ENODEV;

				net = sock_net(sk);
				dev = dev_get_by_name(net, devname);
				अगर (!dev)
					अवरोध;
				अगरindex = dev->अगरindex;
				dev_put(dev);
			पूर्ण
			fallthrough;
		हाल SO_BINDTOIFINDEX:
			अगर (optname == SO_BINDTOIFINDEX)
				अगरindex = val;
			ret = sock_bindtoindex(sk, अगरindex, false);
			अवरोध;
		हाल SO_KEEPALIVE:
			अगर (sk->sk_prot->keepalive)
				sk->sk_prot->keepalive(sk, valbool);
			sock_valbool_flag(sk, SOCK_KEEPOPEN, valbool);
			अवरोध;
		हाल SO_REUSEPORT:
			sk->sk_reuseport = valbool;
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
#अगर_घोषित CONFIG_INET
	पूर्ण अन्यथा अगर (level == SOL_IP) अणु
		अगर (optlen != माप(पूर्णांक) || sk->sk_family != AF_INET)
			वापस -EINVAL;

		val = *((पूर्णांक *)optval);
		/* Only some options are supported */
		चयन (optname) अणु
		हाल IP_TOS:
			अगर (val < -1 || val > 0xff) अणु
				ret = -EINVAL;
			पूर्ण अन्यथा अणु
				काष्ठा inet_sock *inet = inet_sk(sk);

				अगर (val == -1)
					val = 0;
				inet->tos = val;
			पूर्ण
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (level == SOL_IPV6) अणु
		अगर (optlen != माप(पूर्णांक) || sk->sk_family != AF_INET6)
			वापस -EINVAL;

		val = *((पूर्णांक *)optval);
		/* Only some options are supported */
		चयन (optname) अणु
		हाल IPV6_TCLASS:
			अगर (val < -1 || val > 0xff) अणु
				ret = -EINVAL;
			पूर्ण अन्यथा अणु
				काष्ठा ipv6_pinfo *np = inet6_sk(sk);

				अगर (val == -1)
					val = 0;
				np->tclass = val;
			पूर्ण
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (level == SOL_TCP &&
		   sk->sk_prot->setsockopt == tcp_setsockopt) अणु
		अगर (optname == TCP_CONGESTION) अणु
			अक्षर name[TCP_CA_NAME_MAX];

			म_नकलन(name, optval, min_t(दीर्घ, optlen,
						    TCP_CA_NAME_MAX-1));
			name[TCP_CA_NAME_MAX-1] = 0;
			ret = tcp_set_congestion_control(sk, name, false, true);
		पूर्ण अन्यथा अणु
			काष्ठा inet_connection_sock *icsk = inet_csk(sk);
			काष्ठा tcp_sock *tp = tcp_sk(sk);
			अचिन्हित दीर्घ समयout;

			अगर (optlen != माप(पूर्णांक))
				वापस -EINVAL;

			val = *((पूर्णांक *)optval);
			/* Only some options are supported */
			चयन (optname) अणु
			हाल TCP_BPF_IW:
				अगर (val <= 0 || tp->data_segs_out > tp->syn_data)
					ret = -EINVAL;
				अन्यथा
					tp->snd_cwnd = val;
				अवरोध;
			हाल TCP_BPF_SNDCWND_CLAMP:
				अगर (val <= 0) अणु
					ret = -EINVAL;
				पूर्ण अन्यथा अणु
					tp->snd_cwnd_clamp = val;
					tp->snd_ssthresh = val;
				पूर्ण
				अवरोध;
			हाल TCP_BPF_DELACK_MAX:
				समयout = usecs_to_jअगरfies(val);
				अगर (समयout > TCP_DELACK_MAX ||
				    समयout < TCP_TIMEOUT_MIN)
					वापस -EINVAL;
				inet_csk(sk)->icsk_delack_max = समयout;
				अवरोध;
			हाल TCP_BPF_RTO_MIN:
				समयout = usecs_to_jअगरfies(val);
				अगर (समयout > TCP_RTO_MIN ||
				    समयout < TCP_TIMEOUT_MIN)
					वापस -EINVAL;
				inet_csk(sk)->icsk_rto_min = समयout;
				अवरोध;
			हाल TCP_SAVE_SYN:
				अगर (val < 0 || val > 1)
					ret = -EINVAL;
				अन्यथा
					tp->save_syn = val;
				अवरोध;
			हाल TCP_KEEPIDLE:
				ret = tcp_sock_set_keepidle_locked(sk, val);
				अवरोध;
			हाल TCP_KEEPINTVL:
				अगर (val < 1 || val > MAX_TCP_KEEPINTVL)
					ret = -EINVAL;
				अन्यथा
					tp->keepalive_पूर्णांकvl = val * HZ;
				अवरोध;
			हाल TCP_KEEPCNT:
				अगर (val < 1 || val > MAX_TCP_KEEPCNT)
					ret = -EINVAL;
				अन्यथा
					tp->keepalive_probes = val;
				अवरोध;
			हाल TCP_SYNCNT:
				अगर (val < 1 || val > MAX_TCP_SYNCNT)
					ret = -EINVAL;
				अन्यथा
					icsk->icsk_syn_retries = val;
				अवरोध;
			हाल TCP_USER_TIMEOUT:
				अगर (val < 0)
					ret = -EINVAL;
				अन्यथा
					icsk->icsk_user_समयout = val;
				अवरोध;
			हाल TCP_NOTSENT_LOWAT:
				tp->notsent_lowat = val;
				sk->sk_ग_लिखो_space(sk);
				अवरोध;
			हाल TCP_WINDOW_CLAMP:
				ret = tcp_set_winकरोw_clamp(sk, val);
				अवरोध;
			शेष:
				ret = -EINVAL;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक _bpf_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			   अक्षर *optval, पूर्णांक optlen)
अणु
	अगर (!sk_fullsock(sk))
		जाओ err_clear;

	sock_owned_by_me(sk);

	अगर (level == SOL_SOCKET) अणु
		अगर (optlen != माप(पूर्णांक))
			जाओ err_clear;

		चयन (optname) अणु
		हाल SO_MARK:
			*((पूर्णांक *)optval) = sk->sk_mark;
			अवरोध;
		हाल SO_PRIORITY:
			*((पूर्णांक *)optval) = sk->sk_priority;
			अवरोध;
		हाल SO_BINDTOIFINDEX:
			*((पूर्णांक *)optval) = sk->sk_bound_dev_अगर;
			अवरोध;
		हाल SO_REUSEPORT:
			*((पूर्णांक *)optval) = sk->sk_reuseport;
			अवरोध;
		शेष:
			जाओ err_clear;
		पूर्ण
#अगर_घोषित CONFIG_INET
	पूर्ण अन्यथा अगर (level == SOL_TCP && sk->sk_prot->माला_लोockopt == tcp_माला_लोockopt) अणु
		काष्ठा inet_connection_sock *icsk;
		काष्ठा tcp_sock *tp;

		चयन (optname) अणु
		हाल TCP_CONGESTION:
			icsk = inet_csk(sk);

			अगर (!icsk->icsk_ca_ops || optlen <= 1)
				जाओ err_clear;
			म_नकलन(optval, icsk->icsk_ca_ops->name, optlen);
			optval[optlen - 1] = 0;
			अवरोध;
		हाल TCP_SAVED_SYN:
			tp = tcp_sk(sk);

			अगर (optlen <= 0 || !tp->saved_syn ||
			    optlen > tcp_saved_syn_len(tp->saved_syn))
				जाओ err_clear;
			स_नकल(optval, tp->saved_syn->data, optlen);
			अवरोध;
		शेष:
			जाओ err_clear;
		पूर्ण
	पूर्ण अन्यथा अगर (level == SOL_IP) अणु
		काष्ठा inet_sock *inet = inet_sk(sk);

		अगर (optlen != माप(पूर्णांक) || sk->sk_family != AF_INET)
			जाओ err_clear;

		/* Only some options are supported */
		चयन (optname) अणु
		हाल IP_TOS:
			*((पूर्णांक *)optval) = (पूर्णांक)inet->tos;
			अवरोध;
		शेष:
			जाओ err_clear;
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (level == SOL_IPV6) अणु
		काष्ठा ipv6_pinfo *np = inet6_sk(sk);

		अगर (optlen != माप(पूर्णांक) || sk->sk_family != AF_INET6)
			जाओ err_clear;

		/* Only some options are supported */
		चयन (optname) अणु
		हाल IPV6_TCLASS:
			*((पूर्णांक *)optval) = (पूर्णांक)np->tclass;
			अवरोध;
		शेष:
			जाओ err_clear;
		पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		जाओ err_clear;
	पूर्ण
	वापस 0;
err_clear:
	स_रखो(optval, 0, optlen);
	वापस -EINVAL;
पूर्ण

BPF_CALL_5(bpf_sock_addr_setsockopt, काष्ठा bpf_sock_addr_kern *, ctx,
	   पूर्णांक, level, पूर्णांक, optname, अक्षर *, optval, पूर्णांक, optlen)
अणु
	वापस _bpf_setsockopt(ctx->sk, level, optname, optval, optlen);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sock_addr_setsockopt_proto = अणु
	.func		= bpf_sock_addr_setsockopt,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_PTR_TO_MEM,
	.arg5_type	= ARG_CONST_SIZE,
पूर्ण;

BPF_CALL_5(bpf_sock_addr_माला_लोockopt, काष्ठा bpf_sock_addr_kern *, ctx,
	   पूर्णांक, level, पूर्णांक, optname, अक्षर *, optval, पूर्णांक, optlen)
अणु
	वापस _bpf_माला_लोockopt(ctx->sk, level, optname, optval, optlen);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sock_addr_माला_लोockopt_proto = अणु
	.func		= bpf_sock_addr_माला_लोockopt,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg5_type	= ARG_CONST_SIZE,
पूर्ण;

BPF_CALL_5(bpf_sock_ops_setsockopt, काष्ठा bpf_sock_ops_kern *, bpf_sock,
	   पूर्णांक, level, पूर्णांक, optname, अक्षर *, optval, पूर्णांक, optlen)
अणु
	वापस _bpf_setsockopt(bpf_sock->sk, level, optname, optval, optlen);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sock_ops_setsockopt_proto = अणु
	.func		= bpf_sock_ops_setsockopt,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_PTR_TO_MEM,
	.arg5_type	= ARG_CONST_SIZE,
पूर्ण;

अटल पूर्णांक bpf_sock_ops_get_syn(काष्ठा bpf_sock_ops_kern *bpf_sock,
				पूर्णांक optname, स्थिर u8 **start)
अणु
	काष्ठा sk_buff *syn_skb = bpf_sock->syn_skb;
	स्थिर u8 *hdr_start;
	पूर्णांक ret;

	अगर (syn_skb) अणु
		/* sk is a request_sock here */

		अगर (optname == TCP_BPF_SYN) अणु
			hdr_start = syn_skb->data;
			ret = tcp_hdrlen(syn_skb);
		पूर्ण अन्यथा अगर (optname == TCP_BPF_SYN_IP) अणु
			hdr_start = skb_network_header(syn_skb);
			ret = skb_network_header_len(syn_skb) +
				tcp_hdrlen(syn_skb);
		पूर्ण अन्यथा अणु
			/* optname == TCP_BPF_SYN_MAC */
			hdr_start = skb_mac_header(syn_skb);
			ret = skb_mac_header_len(syn_skb) +
				skb_network_header_len(syn_skb) +
				tcp_hdrlen(syn_skb);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा sock *sk = bpf_sock->sk;
		काष्ठा saved_syn *saved_syn;

		अगर (sk->sk_state == TCP_NEW_SYN_RECV)
			/* synack retransmit. bpf_sock->syn_skb will
			 * not be available.  It has to resort to
			 * saved_syn (अगर it is saved).
			 */
			saved_syn = inet_reqsk(sk)->saved_syn;
		अन्यथा
			saved_syn = tcp_sk(sk)->saved_syn;

		अगर (!saved_syn)
			वापस -ENOENT;

		अगर (optname == TCP_BPF_SYN) अणु
			hdr_start = saved_syn->data +
				saved_syn->mac_hdrlen +
				saved_syn->network_hdrlen;
			ret = saved_syn->tcp_hdrlen;
		पूर्ण अन्यथा अगर (optname == TCP_BPF_SYN_IP) अणु
			hdr_start = saved_syn->data +
				saved_syn->mac_hdrlen;
			ret = saved_syn->network_hdrlen +
				saved_syn->tcp_hdrlen;
		पूर्ण अन्यथा अणु
			/* optname == TCP_BPF_SYN_MAC */

			/* TCP_SAVE_SYN may not have saved the mac hdr */
			अगर (!saved_syn->mac_hdrlen)
				वापस -ENOENT;

			hdr_start = saved_syn->data;
			ret = saved_syn->mac_hdrlen +
				saved_syn->network_hdrlen +
				saved_syn->tcp_hdrlen;
		पूर्ण
	पूर्ण

	*start = hdr_start;
	वापस ret;
पूर्ण

BPF_CALL_5(bpf_sock_ops_माला_लोockopt, काष्ठा bpf_sock_ops_kern *, bpf_sock,
	   पूर्णांक, level, पूर्णांक, optname, अक्षर *, optval, पूर्णांक, optlen)
अणु
	अगर (IS_ENABLED(CONFIG_INET) && level == SOL_TCP &&
	    optname >= TCP_BPF_SYN && optname <= TCP_BPF_SYN_MAC) अणु
		पूर्णांक ret, copy_len = 0;
		स्थिर u8 *start;

		ret = bpf_sock_ops_get_syn(bpf_sock, optname, &start);
		अगर (ret > 0) अणु
			copy_len = ret;
			अगर (optlen < copy_len) अणु
				copy_len = optlen;
				ret = -ENOSPC;
			पूर्ण

			स_नकल(optval, start, copy_len);
		पूर्ण

		/* Zero out unused buffer at the end */
		स_रखो(optval + copy_len, 0, optlen - copy_len);

		वापस ret;
	पूर्ण

	वापस _bpf_माला_लोockopt(bpf_sock->sk, level, optname, optval, optlen);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sock_ops_माला_लोockopt_proto = अणु
	.func		= bpf_sock_ops_माला_लोockopt,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg5_type	= ARG_CONST_SIZE,
पूर्ण;

BPF_CALL_2(bpf_sock_ops_cb_flags_set, काष्ठा bpf_sock_ops_kern *, bpf_sock,
	   पूर्णांक, argval)
अणु
	काष्ठा sock *sk = bpf_sock->sk;
	पूर्णांक val = argval & BPF_SOCK_OPS_ALL_CB_FLAGS;

	अगर (!IS_ENABLED(CONFIG_INET) || !sk_fullsock(sk))
		वापस -EINVAL;

	tcp_sk(sk)->bpf_sock_ops_cb_flags = val;

	वापस argval & (~BPF_SOCK_OPS_ALL_CB_FLAGS);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sock_ops_cb_flags_set_proto = अणु
	.func		= bpf_sock_ops_cb_flags_set,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

स्थिर काष्ठा ipv6_bpf_stub *ipv6_bpf_stub __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(ipv6_bpf_stub);

BPF_CALL_3(bpf_bind, काष्ठा bpf_sock_addr_kern *, ctx, काष्ठा sockaddr *, addr,
	   पूर्णांक, addr_len)
अणु
#अगर_घोषित CONFIG_INET
	काष्ठा sock *sk = ctx->sk;
	u32 flags = BIND_FROM_BPF;
	पूर्णांक err;

	err = -EINVAL;
	अगर (addr_len < दुरत्वend(काष्ठा sockaddr, sa_family))
		वापस err;
	अगर (addr->sa_family == AF_INET) अणु
		अगर (addr_len < माप(काष्ठा sockaddr_in))
			वापस err;
		अगर (((काष्ठा sockaddr_in *)addr)->sin_port == htons(0))
			flags |= BIND_FORCE_ADDRESS_NO_PORT;
		वापस __inet_bind(sk, addr, addr_len, flags);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (addr->sa_family == AF_INET6) अणु
		अगर (addr_len < SIN6_LEN_RFC2133)
			वापस err;
		अगर (((काष्ठा sockaddr_in6 *)addr)->sin6_port == htons(0))
			flags |= BIND_FORCE_ADDRESS_NO_PORT;
		/* ipv6_bpf_stub cannot be शून्य, since it's called from
		 * bpf_cgroup_inet6_connect hook and ipv6 is alपढ़ोy loaded
		 */
		वापस ipv6_bpf_stub->inet6_bind(sk, addr, addr_len, flags);
#पूर्ण_अगर /* CONFIG_IPV6 */
	पूर्ण
#पूर्ण_अगर /* CONFIG_INET */

	वापस -EAFNOSUPPORT;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_bind_proto = अणु
	.func		= bpf_bind,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
पूर्ण;

#अगर_घोषित CONFIG_XFRM
BPF_CALL_5(bpf_skb_get_xfrm_state, काष्ठा sk_buff *, skb, u32, index,
	   काष्ठा bpf_xfrm_state *, to, u32, size, u64, flags)
अणु
	स्थिर काष्ठा sec_path *sp = skb_sec_path(skb);
	स्थिर काष्ठा xfrm_state *x;

	अगर (!sp || unlikely(index >= sp->len || flags))
		जाओ err_clear;

	x = sp->xvec[index];

	अगर (unlikely(size != माप(काष्ठा bpf_xfrm_state)))
		जाओ err_clear;

	to->reqid = x->props.reqid;
	to->spi = x->id.spi;
	to->family = x->props.family;
	to->ext = 0;

	अगर (to->family == AF_INET6) अणु
		स_नकल(to->remote_ipv6, x->props.saddr.a6,
		       माप(to->remote_ipv6));
	पूर्ण अन्यथा अणु
		to->remote_ipv4 = x->props.saddr.a4;
		स_रखो(&to->remote_ipv6[1], 0, माप(__u32) * 3);
	पूर्ण

	वापस 0;
err_clear:
	स_रखो(to, 0, size);
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_get_xfrm_state_proto = अणु
	.func		= bpf_skb_get_xfrm_state,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg4_type	= ARG_CONST_SIZE,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_INET) || IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक bpf_fib_set_fwd_params(काष्ठा bpf_fib_lookup *params,
				  स्थिर काष्ठा neighbour *neigh,
				  स्थिर काष्ठा net_device *dev, u32 mtu)
अणु
	स_नकल(params->dmac, neigh->ha, ETH_ALEN);
	स_नकल(params->smac, dev->dev_addr, ETH_ALEN);
	params->h_vlan_TCI = 0;
	params->h_vlan_proto = 0;
	अगर (mtu)
		params->mtu_result = mtu; /* जोड़ with tot_len */

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_INET)
अटल पूर्णांक bpf_ipv4_fib_lookup(काष्ठा net *net, काष्ठा bpf_fib_lookup *params,
			       u32 flags, bool check_mtu)
अणु
	काष्ठा fib_nh_common *nhc;
	काष्ठा in_device *in_dev;
	काष्ठा neighbour *neigh;
	काष्ठा net_device *dev;
	काष्ठा fib_result res;
	काष्ठा flowi4 fl4;
	u32 mtu = 0;
	पूर्णांक err;

	dev = dev_get_by_index_rcu(net, params->अगरindex);
	अगर (unlikely(!dev))
		वापस -ENODEV;

	/* verअगरy क्रमwarding is enabled on this पूर्णांकerface */
	in_dev = __in_dev_get_rcu(dev);
	अगर (unlikely(!in_dev || !IN_DEV_FORWARD(in_dev)))
		वापस BPF_FIB_LKUP_RET_FWD_DISABLED;

	अगर (flags & BPF_FIB_LOOKUP_OUTPUT) अणु
		fl4.flowi4_iअगर = 1;
		fl4.flowi4_oअगर = params->अगरindex;
	पूर्ण अन्यथा अणु
		fl4.flowi4_iअगर = params->अगरindex;
		fl4.flowi4_oअगर = 0;
	पूर्ण
	fl4.flowi4_tos = params->tos & IPTOS_RT_MASK;
	fl4.flowi4_scope = RT_SCOPE_UNIVERSE;
	fl4.flowi4_flags = 0;

	fl4.flowi4_proto = params->l4_protocol;
	fl4.daddr = params->ipv4_dst;
	fl4.saddr = params->ipv4_src;
	fl4.fl4_sport = params->sport;
	fl4.fl4_dport = params->dport;
	fl4.flowi4_multipath_hash = 0;

	अगर (flags & BPF_FIB_LOOKUP_सूचीECT) अणु
		u32 tbid = l3mdev_fib_table_rcu(dev) ? : RT_TABLE_MAIN;
		काष्ठा fib_table *tb;

		tb = fib_get_table(net, tbid);
		अगर (unlikely(!tb))
			वापस BPF_FIB_LKUP_RET_NOT_FWDED;

		err = fib_table_lookup(tb, &fl4, &res, FIB_LOOKUP_NOREF);
	पूर्ण अन्यथा अणु
		fl4.flowi4_mark = 0;
		fl4.flowi4_secid = 0;
		fl4.flowi4_tun_key.tun_id = 0;
		fl4.flowi4_uid = sock_net_uid(net, शून्य);

		err = fib_lookup(net, &fl4, &res, FIB_LOOKUP_NOREF);
	पूर्ण

	अगर (err) अणु
		/* map fib lookup errors to RTN_ type */
		अगर (err == -EINVAL)
			वापस BPF_FIB_LKUP_RET_BLACKHOLE;
		अगर (err == -EHOSTUNREACH)
			वापस BPF_FIB_LKUP_RET_UNREACHABLE;
		अगर (err == -EACCES)
			वापस BPF_FIB_LKUP_RET_PROHIBIT;

		वापस BPF_FIB_LKUP_RET_NOT_FWDED;
	पूर्ण

	अगर (res.type != RTN_UNICAST)
		वापस BPF_FIB_LKUP_RET_NOT_FWDED;

	अगर (fib_info_num_path(res.fi) > 1)
		fib_select_path(net, &res, &fl4, शून्य);

	अगर (check_mtu) अणु
		mtu = ip_mtu_from_fib_result(&res, params->ipv4_dst);
		अगर (params->tot_len > mtu) अणु
			params->mtu_result = mtu; /* जोड़ with tot_len */
			वापस BPF_FIB_LKUP_RET_FRAG_NEEDED;
		पूर्ण
	पूर्ण

	nhc = res.nhc;

	/* करो not handle lwt encaps right now */
	अगर (nhc->nhc_lwtstate)
		वापस BPF_FIB_LKUP_RET_UNSUPP_LWT;

	dev = nhc->nhc_dev;

	params->rt_metric = res.fi->fib_priority;
	params->अगरindex = dev->अगरindex;

	/* xdp and cls_bpf programs are run in RCU-bh so
	 * rcu_पढ़ो_lock_bh is not needed here
	 */
	अगर (likely(nhc->nhc_gw_family != AF_INET6)) अणु
		अगर (nhc->nhc_gw_family)
			params->ipv4_dst = nhc->nhc_gw.ipv4;

		neigh = __ipv4_neigh_lookup_noref(dev,
						 (__क्रमce u32)params->ipv4_dst);
	पूर्ण अन्यथा अणु
		काष्ठा in6_addr *dst = (काष्ठा in6_addr *)params->ipv6_dst;

		params->family = AF_INET6;
		*dst = nhc->nhc_gw.ipv6;
		neigh = __ipv6_neigh_lookup_noref_stub(dev, dst);
	पूर्ण

	अगर (!neigh)
		वापस BPF_FIB_LKUP_RET_NO_NEIGH;

	वापस bpf_fib_set_fwd_params(params, neigh, dev, mtu);
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक bpf_ipv6_fib_lookup(काष्ठा net *net, काष्ठा bpf_fib_lookup *params,
			       u32 flags, bool check_mtu)
अणु
	काष्ठा in6_addr *src = (काष्ठा in6_addr *) params->ipv6_src;
	काष्ठा in6_addr *dst = (काष्ठा in6_addr *) params->ipv6_dst;
	काष्ठा fib6_result res = अणुपूर्ण;
	काष्ठा neighbour *neigh;
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *idev;
	काष्ठा flowi6 fl6;
	पूर्णांक strict = 0;
	पूर्णांक oअगर, err;
	u32 mtu = 0;

	/* link local addresses are never क्रमwarded */
	अगर (rt6_need_strict(dst) || rt6_need_strict(src))
		वापस BPF_FIB_LKUP_RET_NOT_FWDED;

	dev = dev_get_by_index_rcu(net, params->अगरindex);
	अगर (unlikely(!dev))
		वापस -ENODEV;

	idev = __in6_dev_get_safely(dev);
	अगर (unlikely(!idev || !idev->cnf.क्रमwarding))
		वापस BPF_FIB_LKUP_RET_FWD_DISABLED;

	अगर (flags & BPF_FIB_LOOKUP_OUTPUT) अणु
		fl6.flowi6_iअगर = 1;
		oअगर = fl6.flowi6_oअगर = params->अगरindex;
	पूर्ण अन्यथा अणु
		oअगर = fl6.flowi6_iअगर = params->अगरindex;
		fl6.flowi6_oअगर = 0;
		strict = RT6_LOOKUP_F_HAS_SADDR;
	पूर्ण
	fl6.flowlabel = params->flowinfo;
	fl6.flowi6_scope = 0;
	fl6.flowi6_flags = 0;
	fl6.mp_hash = 0;

	fl6.flowi6_proto = params->l4_protocol;
	fl6.daddr = *dst;
	fl6.saddr = *src;
	fl6.fl6_sport = params->sport;
	fl6.fl6_dport = params->dport;

	अगर (flags & BPF_FIB_LOOKUP_सूचीECT) अणु
		u32 tbid = l3mdev_fib_table_rcu(dev) ? : RT_TABLE_MAIN;
		काष्ठा fib6_table *tb;

		tb = ipv6_stub->fib6_get_table(net, tbid);
		अगर (unlikely(!tb))
			वापस BPF_FIB_LKUP_RET_NOT_FWDED;

		err = ipv6_stub->fib6_table_lookup(net, tb, oअगर, &fl6, &res,
						   strict);
	पूर्ण अन्यथा अणु
		fl6.flowi6_mark = 0;
		fl6.flowi6_secid = 0;
		fl6.flowi6_tun_key.tun_id = 0;
		fl6.flowi6_uid = sock_net_uid(net, शून्य);

		err = ipv6_stub->fib6_lookup(net, oअगर, &fl6, &res, strict);
	पूर्ण

	अगर (unlikely(err || IS_ERR_OR_शून्य(res.f6i) ||
		     res.f6i == net->ipv6.fib6_null_entry))
		वापस BPF_FIB_LKUP_RET_NOT_FWDED;

	चयन (res.fib6_type) अणु
	/* only unicast is क्रमwarded */
	हाल RTN_UNICAST:
		अवरोध;
	हाल RTN_BLACKHOLE:
		वापस BPF_FIB_LKUP_RET_BLACKHOLE;
	हाल RTN_UNREACHABLE:
		वापस BPF_FIB_LKUP_RET_UNREACHABLE;
	हाल RTN_PROHIBIT:
		वापस BPF_FIB_LKUP_RET_PROHIBIT;
	शेष:
		वापस BPF_FIB_LKUP_RET_NOT_FWDED;
	पूर्ण

	ipv6_stub->fib6_select_path(net, &res, &fl6, fl6.flowi6_oअगर,
				    fl6.flowi6_oअगर != 0, शून्य, strict);

	अगर (check_mtu) अणु
		mtu = ipv6_stub->ip6_mtu_from_fib6(&res, dst, src);
		अगर (params->tot_len > mtu) अणु
			params->mtu_result = mtu; /* जोड़ with tot_len */
			वापस BPF_FIB_LKUP_RET_FRAG_NEEDED;
		पूर्ण
	पूर्ण

	अगर (res.nh->fib_nh_lws)
		वापस BPF_FIB_LKUP_RET_UNSUPP_LWT;

	अगर (res.nh->fib_nh_gw_family)
		*dst = res.nh->fib_nh_gw6;

	dev = res.nh->fib_nh_dev;
	params->rt_metric = res.f6i->fib6_metric;
	params->अगरindex = dev->अगरindex;

	/* xdp and cls_bpf programs are run in RCU-bh so rcu_पढ़ो_lock_bh is
	 * not needed here.
	 */
	neigh = __ipv6_neigh_lookup_noref_stub(dev, dst);
	अगर (!neigh)
		वापस BPF_FIB_LKUP_RET_NO_NEIGH;

	वापस bpf_fib_set_fwd_params(params, neigh, dev, mtu);
पूर्ण
#पूर्ण_अगर

BPF_CALL_4(bpf_xdp_fib_lookup, काष्ठा xdp_buff *, ctx,
	   काष्ठा bpf_fib_lookup *, params, पूर्णांक, plen, u32, flags)
अणु
	अगर (plen < माप(*params))
		वापस -EINVAL;

	अगर (flags & ~(BPF_FIB_LOOKUP_सूचीECT | BPF_FIB_LOOKUP_OUTPUT))
		वापस -EINVAL;

	चयन (params->family) अणु
#अगर IS_ENABLED(CONFIG_INET)
	हाल AF_INET:
		वापस bpf_ipv4_fib_lookup(dev_net(ctx->rxq->dev), params,
					   flags, true);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		वापस bpf_ipv6_fib_lookup(dev_net(ctx->rxq->dev), params,
					   flags, true);
#पूर्ण_अगर
	पूर्ण
	वापस -EAFNOSUPPORT;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_xdp_fib_lookup_proto = अणु
	.func		= bpf_xdp_fib_lookup,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
	.arg2_type      = ARG_PTR_TO_MEM,
	.arg3_type      = ARG_CONST_SIZE,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_skb_fib_lookup, काष्ठा sk_buff *, skb,
	   काष्ठा bpf_fib_lookup *, params, पूर्णांक, plen, u32, flags)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	पूर्णांक rc = -EAFNOSUPPORT;
	bool check_mtu = false;

	अगर (plen < माप(*params))
		वापस -EINVAL;

	अगर (flags & ~(BPF_FIB_LOOKUP_सूचीECT | BPF_FIB_LOOKUP_OUTPUT))
		वापस -EINVAL;

	अगर (params->tot_len)
		check_mtu = true;

	चयन (params->family) अणु
#अगर IS_ENABLED(CONFIG_INET)
	हाल AF_INET:
		rc = bpf_ipv4_fib_lookup(net, params, flags, check_mtu);
		अवरोध;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल AF_INET6:
		rc = bpf_ipv6_fib_lookup(net, params, flags, check_mtu);
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	अगर (rc == BPF_FIB_LKUP_RET_SUCCESS && !check_mtu) अणु
		काष्ठा net_device *dev;

		/* When tot_len isn't provided by user, check skb
		 * against MTU of FIB lookup resulting net_device
		 */
		dev = dev_get_by_index_rcu(net, params->अगरindex);
		अगर (!is_skb_क्रमwardable(dev, skb))
			rc = BPF_FIB_LKUP_RET_FRAG_NEEDED;

		params->mtu_result = dev->mtu; /* जोड़ with tot_len */
	पूर्ण

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_fib_lookup_proto = अणु
	.func		= bpf_skb_fib_lookup,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
	.arg2_type      = ARG_PTR_TO_MEM,
	.arg3_type      = ARG_CONST_SIZE,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

अटल काष्ठा net_device *__dev_via_अगरindex(काष्ठा net_device *dev_curr,
					    u32 अगरindex)
अणु
	काष्ठा net *netns = dev_net(dev_curr);

	/* Non-redirect use-हालs can use अगरindex=0 and save अगरindex lookup */
	अगर (अगरindex == 0)
		वापस dev_curr;

	वापस dev_get_by_index_rcu(netns, अगरindex);
पूर्ण

BPF_CALL_5(bpf_skb_check_mtu, काष्ठा sk_buff *, skb,
	   u32, अगरindex, u32 *, mtu_len, s32, len_dअगरf, u64, flags)
अणु
	पूर्णांक ret = BPF_MTU_CHK_RET_FRAG_NEEDED;
	काष्ठा net_device *dev = skb->dev;
	पूर्णांक skb_len, dev_len;
	पूर्णांक mtu;

	अगर (unlikely(flags & ~(BPF_MTU_CHK_SEGS)))
		वापस -EINVAL;

	अगर (unlikely(flags & BPF_MTU_CHK_SEGS && (len_dअगरf || *mtu_len)))
		वापस -EINVAL;

	dev = __dev_via_अगरindex(dev, अगरindex);
	अगर (unlikely(!dev))
		वापस -ENODEV;

	mtu = READ_ONCE(dev->mtu);

	dev_len = mtu + dev->hard_header_len;

	/* If set use *mtu_len as input, L3 as iph->tot_len (like fib_lookup) */
	skb_len = *mtu_len ? *mtu_len + dev->hard_header_len : skb->len;

	skb_len += len_dअगरf; /* minus result pass check */
	अगर (skb_len <= dev_len) अणु
		ret = BPF_MTU_CHK_RET_SUCCESS;
		जाओ out;
	पूर्ण
	/* At this poपूर्णांक, skb->len exceed MTU, but as it include length of all
	 * segments, it can still be below MTU.  The SKB can possibly get
	 * re-segmented in transmit path (see validate_xmit_skb).  Thus, user
	 * must choose अगर segs are to be MTU checked.
	 */
	अगर (skb_is_gso(skb)) अणु
		ret = BPF_MTU_CHK_RET_SUCCESS;

		अगर (flags & BPF_MTU_CHK_SEGS &&
		    !skb_gso_validate_network_len(skb, mtu))
			ret = BPF_MTU_CHK_RET_SEGS_TOOBIG;
	पूर्ण
out:
	/* BPF verअगरier guarantees valid poपूर्णांकer */
	*mtu_len = mtu;

	वापस ret;
पूर्ण

BPF_CALL_5(bpf_xdp_check_mtu, काष्ठा xdp_buff *, xdp,
	   u32, अगरindex, u32 *, mtu_len, s32, len_dअगरf, u64, flags)
अणु
	काष्ठा net_device *dev = xdp->rxq->dev;
	पूर्णांक xdp_len = xdp->data_end - xdp->data;
	पूर्णांक ret = BPF_MTU_CHK_RET_SUCCESS;
	पूर्णांक mtu, dev_len;

	/* XDP variant करोesn't support multi-buffer segment check (yet) */
	अगर (unlikely(flags))
		वापस -EINVAL;

	dev = __dev_via_अगरindex(dev, अगरindex);
	अगर (unlikely(!dev))
		वापस -ENODEV;

	mtu = READ_ONCE(dev->mtu);

	/* Add L2-header as dev MTU is L3 size */
	dev_len = mtu + dev->hard_header_len;

	/* Use *mtu_len as input, L3 as iph->tot_len (like fib_lookup) */
	अगर (*mtu_len)
		xdp_len = *mtu_len + dev->hard_header_len;

	xdp_len += len_dअगरf; /* minus result pass check */
	अगर (xdp_len > dev_len)
		ret = BPF_MTU_CHK_RET_FRAG_NEEDED;

	/* BPF verअगरier guarantees valid poपूर्णांकer */
	*mtu_len = mtu;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_check_mtu_proto = अणु
	.func		= bpf_skb_check_mtu,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
	.arg2_type      = ARG_ANYTHING,
	.arg3_type      = ARG_PTR_TO_INT,
	.arg4_type      = ARG_ANYTHING,
	.arg5_type      = ARG_ANYTHING,
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto bpf_xdp_check_mtu_proto = अणु
	.func		= bpf_xdp_check_mtu,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
	.arg2_type      = ARG_ANYTHING,
	.arg3_type      = ARG_PTR_TO_INT,
	.arg4_type      = ARG_ANYTHING,
	.arg5_type      = ARG_ANYTHING,
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6_SEG6_BPF)
अटल पूर्णांक bpf_push_seg6_encap(काष्ठा sk_buff *skb, u32 type, व्योम *hdr, u32 len)
अणु
	पूर्णांक err;
	काष्ठा ipv6_sr_hdr *srh = (काष्ठा ipv6_sr_hdr *)hdr;

	अगर (!seg6_validate_srh(srh, len, false))
		वापस -EINVAL;

	चयन (type) अणु
	हाल BPF_LWT_ENCAP_SEG6_INLINE:
		अगर (skb->protocol != htons(ETH_P_IPV6))
			वापस -EBADMSG;

		err = seg6_करो_srh_अंतरभूत(skb, srh);
		अवरोध;
	हाल BPF_LWT_ENCAP_SEG6:
		skb_reset_inner_headers(skb);
		skb->encapsulation = 1;
		err = seg6_करो_srh_encap(skb, srh, IPPROTO_IPV6);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	bpf_compute_data_poपूर्णांकers(skb);
	अगर (err)
		वापस err;

	ipv6_hdr(skb)->payload_len = htons(skb->len - माप(काष्ठा ipv6hdr));
	skb_set_transport_header(skb, माप(काष्ठा ipv6hdr));

	वापस seg6_lookup_nexthop(skb, शून्य, 0);
पूर्ण
#पूर्ण_अगर /* CONFIG_IPV6_SEG6_BPF */

#अगर IS_ENABLED(CONFIG_LWTUNNEL_BPF)
अटल पूर्णांक bpf_push_ip_encap(काष्ठा sk_buff *skb, व्योम *hdr, u32 len,
			     bool ingress)
अणु
	वापस bpf_lwt_push_ip_encap(skb, hdr, len, ingress);
पूर्ण
#पूर्ण_अगर

BPF_CALL_4(bpf_lwt_in_push_encap, काष्ठा sk_buff *, skb, u32, type, व्योम *, hdr,
	   u32, len)
अणु
	चयन (type) अणु
#अगर IS_ENABLED(CONFIG_IPV6_SEG6_BPF)
	हाल BPF_LWT_ENCAP_SEG6:
	हाल BPF_LWT_ENCAP_SEG6_INLINE:
		वापस bpf_push_seg6_encap(skb, type, hdr, len);
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_LWTUNNEL_BPF)
	हाल BPF_LWT_ENCAP_IP:
		वापस bpf_push_ip_encap(skb, hdr, len, true /* ingress */);
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

BPF_CALL_4(bpf_lwt_xmit_push_encap, काष्ठा sk_buff *, skb, u32, type,
	   व्योम *, hdr, u32, len)
अणु
	चयन (type) अणु
#अगर IS_ENABLED(CONFIG_LWTUNNEL_BPF)
	हाल BPF_LWT_ENCAP_IP:
		वापस bpf_push_ip_encap(skb, hdr, len, false /* egress */);
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_lwt_in_push_encap_proto = अणु
	.func		= bpf_lwt_in_push_encap,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_PTR_TO_MEM,
	.arg4_type	= ARG_CONST_SIZE
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto bpf_lwt_xmit_push_encap_proto = अणु
	.func		= bpf_lwt_xmit_push_encap,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_PTR_TO_MEM,
	.arg4_type	= ARG_CONST_SIZE
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6_SEG6_BPF)
BPF_CALL_4(bpf_lwt_seg6_store_bytes, काष्ठा sk_buff *, skb, u32, offset,
	   स्थिर व्योम *, from, u32, len)
अणु
	काष्ठा seg6_bpf_srh_state *srh_state =
		this_cpu_ptr(&seg6_bpf_srh_states);
	काष्ठा ipv6_sr_hdr *srh = srh_state->srh;
	व्योम *srh_tlvs, *srh_end, *ptr;
	पूर्णांक srhoff = 0;

	अगर (srh == शून्य)
		वापस -EINVAL;

	srh_tlvs = (व्योम *)((अक्षर *)srh + ((srh->first_segment + 1) << 4));
	srh_end = (व्योम *)((अक्षर *)srh + माप(*srh) + srh_state->hdrlen);

	ptr = skb->data + offset;
	अगर (ptr >= srh_tlvs && ptr + len <= srh_end)
		srh_state->valid = false;
	अन्यथा अगर (ptr < (व्योम *)&srh->flags ||
		 ptr + len > (व्योम *)&srh->segments)
		वापस -EFAULT;

	अगर (unlikely(bpf_try_make_writable(skb, offset + len)))
		वापस -EFAULT;
	अगर (ipv6_find_hdr(skb, &srhoff, IPPROTO_ROUTING, शून्य, शून्य) < 0)
		वापस -EINVAL;
	srh_state->srh = (काष्ठा ipv6_sr_hdr *)(skb->data + srhoff);

	स_नकल(skb->data + offset, from, len);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_lwt_seg6_store_bytes_proto = अणु
	.func		= bpf_lwt_seg6_store_bytes,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_PTR_TO_MEM,
	.arg4_type	= ARG_CONST_SIZE
पूर्ण;

अटल व्योम bpf_update_srh_state(काष्ठा sk_buff *skb)
अणु
	काष्ठा seg6_bpf_srh_state *srh_state =
		this_cpu_ptr(&seg6_bpf_srh_states);
	पूर्णांक srhoff = 0;

	अगर (ipv6_find_hdr(skb, &srhoff, IPPROTO_ROUTING, शून्य, शून्य) < 0) अणु
		srh_state->srh = शून्य;
	पूर्ण अन्यथा अणु
		srh_state->srh = (काष्ठा ipv6_sr_hdr *)(skb->data + srhoff);
		srh_state->hdrlen = srh_state->srh->hdrlen << 3;
		srh_state->valid = true;
	पूर्ण
पूर्ण

BPF_CALL_4(bpf_lwt_seg6_action, काष्ठा sk_buff *, skb,
	   u32, action, व्योम *, param, u32, param_len)
अणु
	काष्ठा seg6_bpf_srh_state *srh_state =
		this_cpu_ptr(&seg6_bpf_srh_states);
	पूर्णांक hdroff = 0;
	पूर्णांक err;

	चयन (action) अणु
	हाल SEG6_LOCAL_ACTION_END_X:
		अगर (!seg6_bpf_has_valid_srh(skb))
			वापस -EBADMSG;
		अगर (param_len != माप(काष्ठा in6_addr))
			वापस -EINVAL;
		वापस seg6_lookup_nexthop(skb, (काष्ठा in6_addr *)param, 0);
	हाल SEG6_LOCAL_ACTION_END_T:
		अगर (!seg6_bpf_has_valid_srh(skb))
			वापस -EBADMSG;
		अगर (param_len != माप(पूर्णांक))
			वापस -EINVAL;
		वापस seg6_lookup_nexthop(skb, शून्य, *(पूर्णांक *)param);
	हाल SEG6_LOCAL_ACTION_END_DT6:
		अगर (!seg6_bpf_has_valid_srh(skb))
			वापस -EBADMSG;
		अगर (param_len != माप(पूर्णांक))
			वापस -EINVAL;

		अगर (ipv6_find_hdr(skb, &hdroff, IPPROTO_IPV6, शून्य, शून्य) < 0)
			वापस -EBADMSG;
		अगर (!pskb_pull(skb, hdroff))
			वापस -EBADMSG;

		skb_postpull_rcsum(skb, skb_network_header(skb), hdroff);
		skb_reset_network_header(skb);
		skb_reset_transport_header(skb);
		skb->encapsulation = 0;

		bpf_compute_data_poपूर्णांकers(skb);
		bpf_update_srh_state(skb);
		वापस seg6_lookup_nexthop(skb, शून्य, *(पूर्णांक *)param);
	हाल SEG6_LOCAL_ACTION_END_B6:
		अगर (srh_state->srh && !seg6_bpf_has_valid_srh(skb))
			वापस -EBADMSG;
		err = bpf_push_seg6_encap(skb, BPF_LWT_ENCAP_SEG6_INLINE,
					  param, param_len);
		अगर (!err)
			bpf_update_srh_state(skb);

		वापस err;
	हाल SEG6_LOCAL_ACTION_END_B6_ENCAP:
		अगर (srh_state->srh && !seg6_bpf_has_valid_srh(skb))
			वापस -EBADMSG;
		err = bpf_push_seg6_encap(skb, BPF_LWT_ENCAP_SEG6,
					  param, param_len);
		अगर (!err)
			bpf_update_srh_state(skb);

		वापस err;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_lwt_seg6_action_proto = अणु
	.func		= bpf_lwt_seg6_action,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_PTR_TO_MEM,
	.arg4_type	= ARG_CONST_SIZE
पूर्ण;

BPF_CALL_3(bpf_lwt_seg6_adjust_srh, काष्ठा sk_buff *, skb, u32, offset,
	   s32, len)
अणु
	काष्ठा seg6_bpf_srh_state *srh_state =
		this_cpu_ptr(&seg6_bpf_srh_states);
	काष्ठा ipv6_sr_hdr *srh = srh_state->srh;
	व्योम *srh_end, *srh_tlvs, *ptr;
	काष्ठा ipv6hdr *hdr;
	पूर्णांक srhoff = 0;
	पूर्णांक ret;

	अगर (unlikely(srh == शून्य))
		वापस -EINVAL;

	srh_tlvs = (व्योम *)((अचिन्हित अक्षर *)srh + माप(*srh) +
			((srh->first_segment + 1) << 4));
	srh_end = (व्योम *)((अचिन्हित अक्षर *)srh + माप(*srh) +
			srh_state->hdrlen);
	ptr = skb->data + offset;

	अगर (unlikely(ptr < srh_tlvs || ptr > srh_end))
		वापस -EFAULT;
	अगर (unlikely(len < 0 && (व्योम *)((अक्षर *)ptr - len) > srh_end))
		वापस -EFAULT;

	अगर (len > 0) अणु
		ret = skb_cow_head(skb, len);
		अगर (unlikely(ret < 0))
			वापस ret;

		ret = bpf_skb_net_hdr_push(skb, offset, len);
	पूर्ण अन्यथा अणु
		ret = bpf_skb_net_hdr_pop(skb, offset, -1 * len);
	पूर्ण

	bpf_compute_data_poपूर्णांकers(skb);
	अगर (unlikely(ret < 0))
		वापस ret;

	hdr = (काष्ठा ipv6hdr *)skb->data;
	hdr->payload_len = htons(skb->len - माप(काष्ठा ipv6hdr));

	अगर (ipv6_find_hdr(skb, &srhoff, IPPROTO_ROUTING, शून्य, शून्य) < 0)
		वापस -EINVAL;
	srh_state->srh = (काष्ठा ipv6_sr_hdr *)(skb->data + srhoff);
	srh_state->hdrlen += len;
	srh_state->valid = false;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_lwt_seg6_adjust_srh_proto = अणु
	.func		= bpf_lwt_seg6_adjust_srh,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;
#पूर्ण_अगर /* CONFIG_IPV6_SEG6_BPF */

#अगर_घोषित CONFIG_INET
अटल काष्ठा sock *sk_lookup(काष्ठा net *net, काष्ठा bpf_sock_tuple *tuple,
			      पूर्णांक dअगर, पूर्णांक sdअगर, u8 family, u8 proto)
अणु
	bool refcounted = false;
	काष्ठा sock *sk = शून्य;

	अगर (family == AF_INET) अणु
		__be32 src4 = tuple->ipv4.saddr;
		__be32 dst4 = tuple->ipv4.daddr;

		अगर (proto == IPPROTO_TCP)
			sk = __inet_lookup(net, &tcp_hashinfo, शून्य, 0,
					   src4, tuple->ipv4.sport,
					   dst4, tuple->ipv4.dport,
					   dअगर, sdअगर, &refcounted);
		अन्यथा
			sk = __udp4_lib_lookup(net, src4, tuple->ipv4.sport,
					       dst4, tuple->ipv4.dport,
					       dअगर, sdअगर, &udp_table, शून्य);
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अणु
		काष्ठा in6_addr *src6 = (काष्ठा in6_addr *)&tuple->ipv6.saddr;
		काष्ठा in6_addr *dst6 = (काष्ठा in6_addr *)&tuple->ipv6.daddr;

		अगर (proto == IPPROTO_TCP)
			sk = __inet6_lookup(net, &tcp_hashinfo, शून्य, 0,
					    src6, tuple->ipv6.sport,
					    dst6, ntohs(tuple->ipv6.dport),
					    dअगर, sdअगर, &refcounted);
		अन्यथा अगर (likely(ipv6_bpf_stub))
			sk = ipv6_bpf_stub->udp6_lib_lookup(net,
							    src6, tuple->ipv6.sport,
							    dst6, tuple->ipv6.dport,
							    dअगर, sdअगर,
							    &udp_table, शून्य);
#पूर्ण_अगर
	पूर्ण

	अगर (unlikely(sk && !refcounted && !sock_flag(sk, SOCK_RCU_FREE))) अणु
		WARN_ONCE(1, "Found non-RCU, unreferenced socket!");
		sk = शून्य;
	पूर्ण
	वापस sk;
पूर्ण

/* bpf_skc_lookup perक्रमms the core lookup क्रम dअगरferent types of sockets,
 * taking a reference on the socket अगर it करोesn't have the flag SOCK_RCU_FREE.
 * Returns the socket as an 'unsigned long' to simplअगरy the casting in the
 * callers to satisfy BPF_CALL declarations.
 */
अटल काष्ठा sock *
__bpf_skc_lookup(काष्ठा sk_buff *skb, काष्ठा bpf_sock_tuple *tuple, u32 len,
		 काष्ठा net *caller_net, u32 अगरindex, u8 proto, u64 netns_id,
		 u64 flags)
अणु
	काष्ठा sock *sk = शून्य;
	u8 family = AF_UNSPEC;
	काष्ठा net *net;
	पूर्णांक sdअगर;

	अगर (len == माप(tuple->ipv4))
		family = AF_INET;
	अन्यथा अगर (len == माप(tuple->ipv6))
		family = AF_INET6;
	अन्यथा
		वापस शून्य;

	अगर (unlikely(family == AF_UNSPEC || flags ||
		     !((s32)netns_id < 0 || netns_id <= S32_MAX)))
		जाओ out;

	अगर (family == AF_INET)
		sdअगर = inet_sdअगर(skb);
	अन्यथा
		sdअगर = inet6_sdअगर(skb);

	अगर ((s32)netns_id < 0) अणु
		net = caller_net;
		sk = sk_lookup(net, tuple, अगरindex, sdअगर, family, proto);
	पूर्ण अन्यथा अणु
		net = get_net_ns_by_id(caller_net, netns_id);
		अगर (unlikely(!net))
			जाओ out;
		sk = sk_lookup(net, tuple, अगरindex, sdअगर, family, proto);
		put_net(net);
	पूर्ण

out:
	वापस sk;
पूर्ण

अटल काष्ठा sock *
__bpf_sk_lookup(काष्ठा sk_buff *skb, काष्ठा bpf_sock_tuple *tuple, u32 len,
		काष्ठा net *caller_net, u32 अगरindex, u8 proto, u64 netns_id,
		u64 flags)
अणु
	काष्ठा sock *sk = __bpf_skc_lookup(skb, tuple, len, caller_net,
					   अगरindex, proto, netns_id, flags);

	अगर (sk) अणु
		sk = sk_to_full_sk(sk);
		अगर (!sk_fullsock(sk)) अणु
			sock_gen_put(sk);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस sk;
पूर्ण

अटल काष्ठा sock *
bpf_skc_lookup(काष्ठा sk_buff *skb, काष्ठा bpf_sock_tuple *tuple, u32 len,
	       u8 proto, u64 netns_id, u64 flags)
अणु
	काष्ठा net *caller_net;
	पूर्णांक अगरindex;

	अगर (skb->dev) अणु
		caller_net = dev_net(skb->dev);
		अगरindex = skb->dev->अगरindex;
	पूर्ण अन्यथा अणु
		caller_net = sock_net(skb->sk);
		अगरindex = 0;
	पूर्ण

	वापस __bpf_skc_lookup(skb, tuple, len, caller_net, अगरindex, proto,
				netns_id, flags);
पूर्ण

अटल काष्ठा sock *
bpf_sk_lookup(काष्ठा sk_buff *skb, काष्ठा bpf_sock_tuple *tuple, u32 len,
	      u8 proto, u64 netns_id, u64 flags)
अणु
	काष्ठा sock *sk = bpf_skc_lookup(skb, tuple, len, proto, netns_id,
					 flags);

	अगर (sk) अणु
		sk = sk_to_full_sk(sk);
		अगर (!sk_fullsock(sk)) अणु
			sock_gen_put(sk);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस sk;
पूर्ण

BPF_CALL_5(bpf_skc_lookup_tcp, काष्ठा sk_buff *, skb,
	   काष्ठा bpf_sock_tuple *, tuple, u32, len, u64, netns_id, u64, flags)
अणु
	वापस (अचिन्हित दीर्घ)bpf_skc_lookup(skb, tuple, len, IPPROTO_TCP,
					     netns_id, flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skc_lookup_tcp_proto = अणु
	.func		= bpf_skc_lookup_tcp,
	.gpl_only	= false,
	.pkt_access	= true,
	.ret_type	= RET_PTR_TO_SOCK_COMMON_OR_शून्य,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type	= ARG_ANYTHING,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_5(bpf_sk_lookup_tcp, काष्ठा sk_buff *, skb,
	   काष्ठा bpf_sock_tuple *, tuple, u32, len, u64, netns_id, u64, flags)
अणु
	वापस (अचिन्हित दीर्घ)bpf_sk_lookup(skb, tuple, len, IPPROTO_TCP,
					    netns_id, flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sk_lookup_tcp_proto = अणु
	.func		= bpf_sk_lookup_tcp,
	.gpl_only	= false,
	.pkt_access	= true,
	.ret_type	= RET_PTR_TO_SOCKET_OR_शून्य,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type	= ARG_ANYTHING,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_5(bpf_sk_lookup_udp, काष्ठा sk_buff *, skb,
	   काष्ठा bpf_sock_tuple *, tuple, u32, len, u64, netns_id, u64, flags)
अणु
	वापस (अचिन्हित दीर्घ)bpf_sk_lookup(skb, tuple, len, IPPROTO_UDP,
					    netns_id, flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sk_lookup_udp_proto = अणु
	.func		= bpf_sk_lookup_udp,
	.gpl_only	= false,
	.pkt_access	= true,
	.ret_type	= RET_PTR_TO_SOCKET_OR_शून्य,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type	= ARG_ANYTHING,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_1(bpf_sk_release, काष्ठा sock *, sk)
अणु
	अगर (sk && sk_is_refcounted(sk))
		sock_gen_put(sk);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sk_release_proto = अणु
	.func		= bpf_sk_release,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID_SOCK_COMMON,
पूर्ण;

BPF_CALL_5(bpf_xdp_sk_lookup_udp, काष्ठा xdp_buff *, ctx,
	   काष्ठा bpf_sock_tuple *, tuple, u32, len, u32, netns_id, u64, flags)
अणु
	काष्ठा net *caller_net = dev_net(ctx->rxq->dev);
	पूर्णांक अगरindex = ctx->rxq->dev->अगरindex;

	वापस (अचिन्हित दीर्घ)__bpf_sk_lookup(शून्य, tuple, len, caller_net,
					      अगरindex, IPPROTO_UDP, netns_id,
					      flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_xdp_sk_lookup_udp_proto = अणु
	.func           = bpf_xdp_sk_lookup_udp,
	.gpl_only       = false,
	.pkt_access     = true,
	.ret_type       = RET_PTR_TO_SOCKET_OR_शून्य,
	.arg1_type      = ARG_PTR_TO_CTX,
	.arg2_type      = ARG_PTR_TO_MEM,
	.arg3_type      = ARG_CONST_SIZE,
	.arg4_type      = ARG_ANYTHING,
	.arg5_type      = ARG_ANYTHING,
पूर्ण;

BPF_CALL_5(bpf_xdp_skc_lookup_tcp, काष्ठा xdp_buff *, ctx,
	   काष्ठा bpf_sock_tuple *, tuple, u32, len, u32, netns_id, u64, flags)
अणु
	काष्ठा net *caller_net = dev_net(ctx->rxq->dev);
	पूर्णांक अगरindex = ctx->rxq->dev->अगरindex;

	वापस (अचिन्हित दीर्घ)__bpf_skc_lookup(शून्य, tuple, len, caller_net,
					       अगरindex, IPPROTO_TCP, netns_id,
					       flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_xdp_skc_lookup_tcp_proto = अणु
	.func           = bpf_xdp_skc_lookup_tcp,
	.gpl_only       = false,
	.pkt_access     = true,
	.ret_type       = RET_PTR_TO_SOCK_COMMON_OR_शून्य,
	.arg1_type      = ARG_PTR_TO_CTX,
	.arg2_type      = ARG_PTR_TO_MEM,
	.arg3_type      = ARG_CONST_SIZE,
	.arg4_type      = ARG_ANYTHING,
	.arg5_type      = ARG_ANYTHING,
पूर्ण;

BPF_CALL_5(bpf_xdp_sk_lookup_tcp, काष्ठा xdp_buff *, ctx,
	   काष्ठा bpf_sock_tuple *, tuple, u32, len, u32, netns_id, u64, flags)
अणु
	काष्ठा net *caller_net = dev_net(ctx->rxq->dev);
	पूर्णांक अगरindex = ctx->rxq->dev->अगरindex;

	वापस (अचिन्हित दीर्घ)__bpf_sk_lookup(शून्य, tuple, len, caller_net,
					      अगरindex, IPPROTO_TCP, netns_id,
					      flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_xdp_sk_lookup_tcp_proto = अणु
	.func           = bpf_xdp_sk_lookup_tcp,
	.gpl_only       = false,
	.pkt_access     = true,
	.ret_type       = RET_PTR_TO_SOCKET_OR_शून्य,
	.arg1_type      = ARG_PTR_TO_CTX,
	.arg2_type      = ARG_PTR_TO_MEM,
	.arg3_type      = ARG_CONST_SIZE,
	.arg4_type      = ARG_ANYTHING,
	.arg5_type      = ARG_ANYTHING,
पूर्ण;

BPF_CALL_5(bpf_sock_addr_skc_lookup_tcp, काष्ठा bpf_sock_addr_kern *, ctx,
	   काष्ठा bpf_sock_tuple *, tuple, u32, len, u64, netns_id, u64, flags)
अणु
	वापस (अचिन्हित दीर्घ)__bpf_skc_lookup(शून्य, tuple, len,
					       sock_net(ctx->sk), 0,
					       IPPROTO_TCP, netns_id, flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sock_addr_skc_lookup_tcp_proto = अणु
	.func		= bpf_sock_addr_skc_lookup_tcp,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_SOCK_COMMON_OR_शून्य,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type	= ARG_ANYTHING,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_5(bpf_sock_addr_sk_lookup_tcp, काष्ठा bpf_sock_addr_kern *, ctx,
	   काष्ठा bpf_sock_tuple *, tuple, u32, len, u64, netns_id, u64, flags)
अणु
	वापस (अचिन्हित दीर्घ)__bpf_sk_lookup(शून्य, tuple, len,
					      sock_net(ctx->sk), 0, IPPROTO_TCP,
					      netns_id, flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sock_addr_sk_lookup_tcp_proto = अणु
	.func		= bpf_sock_addr_sk_lookup_tcp,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_SOCKET_OR_शून्य,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type	= ARG_ANYTHING,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_5(bpf_sock_addr_sk_lookup_udp, काष्ठा bpf_sock_addr_kern *, ctx,
	   काष्ठा bpf_sock_tuple *, tuple, u32, len, u64, netns_id, u64, flags)
अणु
	वापस (अचिन्हित दीर्घ)__bpf_sk_lookup(शून्य, tuple, len,
					      sock_net(ctx->sk), 0, IPPROTO_UDP,
					      netns_id, flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sock_addr_sk_lookup_udp_proto = अणु
	.func		= bpf_sock_addr_sk_lookup_udp,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_SOCKET_OR_शून्य,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type	= ARG_ANYTHING,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;

bool bpf_tcp_sock_is_valid_access(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
				  काष्ठा bpf_insn_access_aux *info)
अणु
	अगर (off < 0 || off >= दुरत्वend(काष्ठा bpf_tcp_sock,
					  icsk_retransmits))
		वापस false;

	अगर (off % size != 0)
		वापस false;

	चयन (off) अणु
	हाल दुरत्व(काष्ठा bpf_tcp_sock, bytes_received):
	हाल दुरत्व(काष्ठा bpf_tcp_sock, bytes_acked):
		वापस size == माप(__u64);
	शेष:
		वापस size == माप(__u32);
	पूर्ण
पूर्ण

u32 bpf_tcp_sock_convert_ctx_access(क्रमागत bpf_access_type type,
				    स्थिर काष्ठा bpf_insn *si,
				    काष्ठा bpf_insn *insn_buf,
				    काष्ठा bpf_prog *prog, u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;

#घोषणा BPF_TCP_SOCK_GET_COMMON(FIELD)					\
	करो अणु								\
		BUILD_BUG_ON(माप_field(काष्ठा tcp_sock, FIELD) >	\
			     माप_field(काष्ठा bpf_tcp_sock, FIELD));	\
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा tcp_sock, FIELD),\
				      si->dst_reg, si->src_reg,		\
				      दुरत्व(काष्ठा tcp_sock, FIELD)); \
	पूर्ण जबतक (0)

#घोषणा BPF_INET_SOCK_GET_COMMON(FIELD)					\
	करो अणु								\
		BUILD_BUG_ON(माप_field(काष्ठा inet_connection_sock,	\
					  FIELD) >			\
			     माप_field(काष्ठा bpf_tcp_sock, FIELD));	\
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(			\
					काष्ठा inet_connection_sock,	\
					FIELD),				\
				      si->dst_reg, si->src_reg,		\
				      दुरत्व(				\
					काष्ठा inet_connection_sock,	\
					FIELD));			\
	पूर्ण जबतक (0)

	अगर (insn > insn_buf)
		वापस insn - insn_buf;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा bpf_tcp_sock, rtt_min):
		BUILD_BUG_ON(माप_field(काष्ठा tcp_sock, rtt_min) !=
			     माप(काष्ठा minmax));
		BUILD_BUG_ON(माप(काष्ठा minmax) <
			     माप(काष्ठा minmax_sample));

		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा tcp_sock, rtt_min) +
				      दुरत्व(काष्ठा minmax_sample, v));
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, snd_cwnd):
		BPF_TCP_SOCK_GET_COMMON(snd_cwnd);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, srtt_us):
		BPF_TCP_SOCK_GET_COMMON(srtt_us);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, snd_ssthresh):
		BPF_TCP_SOCK_GET_COMMON(snd_ssthresh);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, rcv_nxt):
		BPF_TCP_SOCK_GET_COMMON(rcv_nxt);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, snd_nxt):
		BPF_TCP_SOCK_GET_COMMON(snd_nxt);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, snd_una):
		BPF_TCP_SOCK_GET_COMMON(snd_una);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, mss_cache):
		BPF_TCP_SOCK_GET_COMMON(mss_cache);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, ecn_flags):
		BPF_TCP_SOCK_GET_COMMON(ecn_flags);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, rate_delivered):
		BPF_TCP_SOCK_GET_COMMON(rate_delivered);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, rate_पूर्णांकerval_us):
		BPF_TCP_SOCK_GET_COMMON(rate_पूर्णांकerval_us);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, packets_out):
		BPF_TCP_SOCK_GET_COMMON(packets_out);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, retrans_out):
		BPF_TCP_SOCK_GET_COMMON(retrans_out);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, total_retrans):
		BPF_TCP_SOCK_GET_COMMON(total_retrans);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, segs_in):
		BPF_TCP_SOCK_GET_COMMON(segs_in);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, data_segs_in):
		BPF_TCP_SOCK_GET_COMMON(data_segs_in);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, segs_out):
		BPF_TCP_SOCK_GET_COMMON(segs_out);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, data_segs_out):
		BPF_TCP_SOCK_GET_COMMON(data_segs_out);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, lost_out):
		BPF_TCP_SOCK_GET_COMMON(lost_out);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, sacked_out):
		BPF_TCP_SOCK_GET_COMMON(sacked_out);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, bytes_received):
		BPF_TCP_SOCK_GET_COMMON(bytes_received);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, bytes_acked):
		BPF_TCP_SOCK_GET_COMMON(bytes_acked);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, dsack_dups):
		BPF_TCP_SOCK_GET_COMMON(dsack_dups);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, delivered):
		BPF_TCP_SOCK_GET_COMMON(delivered);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, delivered_ce):
		BPF_TCP_SOCK_GET_COMMON(delivered_ce);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_tcp_sock, icsk_retransmits):
		BPF_INET_SOCK_GET_COMMON(icsk_retransmits);
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

BPF_CALL_1(bpf_tcp_sock, काष्ठा sock *, sk)
अणु
	अगर (sk_fullsock(sk) && sk->sk_protocol == IPPROTO_TCP)
		वापस (अचिन्हित दीर्घ)sk;

	वापस (अचिन्हित दीर्घ)शून्य;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_tcp_sock_proto = अणु
	.func		= bpf_tcp_sock,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_TCP_SOCK_OR_शून्य,
	.arg1_type	= ARG_PTR_TO_SOCK_COMMON,
पूर्ण;

BPF_CALL_1(bpf_get_listener_sock, काष्ठा sock *, sk)
अणु
	sk = sk_to_full_sk(sk);

	अगर (sk->sk_state == TCP_LISTEN && sock_flag(sk, SOCK_RCU_FREE))
		वापस (अचिन्हित दीर्घ)sk;

	वापस (अचिन्हित दीर्घ)शून्य;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_listener_sock_proto = अणु
	.func		= bpf_get_listener_sock,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_SOCKET_OR_शून्य,
	.arg1_type	= ARG_PTR_TO_SOCK_COMMON,
पूर्ण;

BPF_CALL_1(bpf_skb_ecn_set_ce, काष्ठा sk_buff *, skb)
अणु
	अचिन्हित पूर्णांक iphdr_len;

	चयन (skb_protocol(skb, true)) अणु
	हाल cpu_to_be16(ETH_P_IP):
		iphdr_len = माप(काष्ठा iphdr);
		अवरोध;
	हाल cpu_to_be16(ETH_P_IPV6):
		iphdr_len = माप(काष्ठा ipv6hdr);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (skb_headlen(skb) < iphdr_len)
		वापस 0;

	अगर (skb_cloned(skb) && !skb_clone_writable(skb, iphdr_len))
		वापस 0;

	वापस INET_ECN_set_ce(skb);
पूर्ण

bool bpf_xdp_sock_is_valid_access(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
				  काष्ठा bpf_insn_access_aux *info)
अणु
	अगर (off < 0 || off >= दुरत्वend(काष्ठा bpf_xdp_sock, queue_id))
		वापस false;

	अगर (off % size != 0)
		वापस false;

	चयन (off) अणु
	शेष:
		वापस size == माप(__u32);
	पूर्ण
पूर्ण

u32 bpf_xdp_sock_convert_ctx_access(क्रमागत bpf_access_type type,
				    स्थिर काष्ठा bpf_insn *si,
				    काष्ठा bpf_insn *insn_buf,
				    काष्ठा bpf_prog *prog, u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;

#घोषणा BPF_XDP_SOCK_GET(FIELD)						\
	करो अणु								\
		BUILD_BUG_ON(माप_field(काष्ठा xdp_sock, FIELD) >	\
			     माप_field(काष्ठा bpf_xdp_sock, FIELD));	\
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा xdp_sock, FIELD),\
				      si->dst_reg, si->src_reg,		\
				      दुरत्व(काष्ठा xdp_sock, FIELD)); \
	पूर्ण जबतक (0)

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा bpf_xdp_sock, queue_id):
		BPF_XDP_SOCK_GET(queue_id);
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_skb_ecn_set_ce_proto = अणु
	.func           = bpf_skb_ecn_set_ce,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
पूर्ण;

BPF_CALL_5(bpf_tcp_check_syncookie, काष्ठा sock *, sk, व्योम *, iph, u32, iph_len,
	   काष्ठा tcphdr *, th, u32, th_len)
अणु
#अगर_घोषित CONFIG_SYN_COOKIES
	u32 cookie;
	पूर्णांक ret;

	अगर (unlikely(!sk || th_len < माप(*th)))
		वापस -EINVAL;

	/* sk_listener() allows TCP_NEW_SYN_RECV, which makes no sense here. */
	अगर (sk->sk_protocol != IPPROTO_TCP || sk->sk_state != TCP_LISTEN)
		वापस -EINVAL;

	अगर (!sock_net(sk)->ipv4.sysctl_tcp_syncookies)
		वापस -EINVAL;

	अगर (!th->ack || th->rst || th->syn)
		वापस -ENOENT;

	अगर (tcp_synq_no_recent_overflow(sk))
		वापस -ENOENT;

	cookie = ntohl(th->ack_seq) - 1;

	चयन (sk->sk_family) अणु
	हाल AF_INET:
		अगर (unlikely(iph_len < माप(काष्ठा iphdr)))
			वापस -EINVAL;

		ret = __cookie_v4_check((काष्ठा iphdr *)iph, th, cookie);
		अवरोध;

#अगर IS_BUILTIN(CONFIG_IPV6)
	हाल AF_INET6:
		अगर (unlikely(iph_len < माप(काष्ठा ipv6hdr)))
			वापस -EINVAL;

		ret = __cookie_v6_check((काष्ठा ipv6hdr *)iph, th, cookie);
		अवरोध;
#पूर्ण_अगर /* CONFIG_IPV6 */

	शेष:
		वापस -EPROTONOSUPPORT;
	पूर्ण

	अगर (ret > 0)
		वापस 0;

	वापस -ENOENT;
#अन्यथा
	वापस -ENOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_tcp_check_syncookie_proto = अणु
	.func		= bpf_tcp_check_syncookie,
	.gpl_only	= true,
	.pkt_access	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID_SOCK_COMMON,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type	= ARG_PTR_TO_MEM,
	.arg5_type	= ARG_CONST_SIZE,
पूर्ण;

BPF_CALL_5(bpf_tcp_gen_syncookie, काष्ठा sock *, sk, व्योम *, iph, u32, iph_len,
	   काष्ठा tcphdr *, th, u32, th_len)
अणु
#अगर_घोषित CONFIG_SYN_COOKIES
	u32 cookie;
	u16 mss;

	अगर (unlikely(!sk || th_len < माप(*th) || th_len != th->करोff * 4))
		वापस -EINVAL;

	अगर (sk->sk_protocol != IPPROTO_TCP || sk->sk_state != TCP_LISTEN)
		वापस -EINVAL;

	अगर (!sock_net(sk)->ipv4.sysctl_tcp_syncookies)
		वापस -ENOENT;

	अगर (!th->syn || th->ack || th->fin || th->rst)
		वापस -EINVAL;

	अगर (unlikely(iph_len < माप(काष्ठा iphdr)))
		वापस -EINVAL;

	/* Both काष्ठा iphdr and काष्ठा ipv6hdr have the version field at the
	 * same offset so we can cast to the लघुer header (काष्ठा iphdr).
	 */
	चयन (((काष्ठा iphdr *)iph)->version) अणु
	हाल 4:
		अगर (sk->sk_family == AF_INET6 && sk->sk_ipv6only)
			वापस -EINVAL;

		mss = tcp_v4_get_syncookie(sk, iph, th, &cookie);
		अवरोध;

#अगर IS_BUILTIN(CONFIG_IPV6)
	हाल 6:
		अगर (unlikely(iph_len < माप(काष्ठा ipv6hdr)))
			वापस -EINVAL;

		अगर (sk->sk_family != AF_INET6)
			वापस -EINVAL;

		mss = tcp_v6_get_syncookie(sk, iph, th, &cookie);
		अवरोध;
#पूर्ण_अगर /* CONFIG_IPV6 */

	शेष:
		वापस -EPROTONOSUPPORT;
	पूर्ण
	अगर (mss == 0)
		वापस -ENOENT;

	वापस cookie | ((u64)mss << 32);
#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर /* CONFIG_SYN_COOKIES */
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_tcp_gen_syncookie_proto = अणु
	.func		= bpf_tcp_gen_syncookie,
	.gpl_only	= true, /* __cookie_v*_init_sequence() is GPL */
	.pkt_access	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID_SOCK_COMMON,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type	= ARG_PTR_TO_MEM,
	.arg5_type	= ARG_CONST_SIZE,
पूर्ण;

BPF_CALL_3(bpf_sk_assign, काष्ठा sk_buff *, skb, काष्ठा sock *, sk, u64, flags)
अणु
	अगर (!sk || flags != 0)
		वापस -EINVAL;
	अगर (!skb_at_tc_ingress(skb))
		वापस -EOPNOTSUPP;
	अगर (unlikely(dev_net(skb->dev) != sock_net(sk)))
		वापस -ENETUNREACH;
	अगर (unlikely(sk_fullsock(sk) && sk->sk_reuseport))
		वापस -ESOCKTNOSUPPORT;
	अगर (sk_is_refcounted(sk) &&
	    unlikely(!refcount_inc_not_zero(&sk->sk_refcnt)))
		वापस -ENOENT;

	skb_orphan(skb);
	skb->sk = sk;
	skb->deकाष्ठाor = sock_pमुक्त;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sk_assign_proto = अणु
	.func		= bpf_sk_assign,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
	.arg2_type      = ARG_PTR_TO_BTF_ID_SOCK_COMMON,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

अटल स्थिर u8 *bpf_search_tcp_opt(स्थिर u8 *op, स्थिर u8 *खोलोd,
				    u8 search_kind, स्थिर u8 *magic,
				    u8 magic_len, bool *eol)
अणु
	u8 kind, kind_len;

	*eol = false;

	जबतक (op < खोलोd) अणु
		kind = op[0];

		अगर (kind == TCPOPT_EOL) अणु
			*eol = true;
			वापस ERR_PTR(-ENOMSG);
		पूर्ण अन्यथा अगर (kind == TCPOPT_NOP) अणु
			op++;
			जारी;
		पूर्ण

		अगर (खोलोd - op < 2 || खोलोd - op < op[1] || op[1] < 2)
			/* Something is wrong in the received header.
			 * Follow the TCP stack's tcp_parse_options()
			 * and just bail here.
			 */
			वापस ERR_PTR(-EFAULT);

		kind_len = op[1];
		अगर (search_kind == kind) अणु
			अगर (!magic_len)
				वापस op;

			अगर (magic_len > kind_len - 2)
				वापस ERR_PTR(-ENOMSG);

			अगर (!स_भेद(&op[2], magic, magic_len))
				वापस op;
		पूर्ण

		op += kind_len;
	पूर्ण

	वापस ERR_PTR(-ENOMSG);
पूर्ण

BPF_CALL_4(bpf_sock_ops_load_hdr_opt, काष्ठा bpf_sock_ops_kern *, bpf_sock,
	   व्योम *, search_res, u32, len, u64, flags)
अणु
	bool eol, load_syn = flags & BPF_LOAD_HDR_OPT_TCP_SYN;
	स्थिर u8 *op, *खोलोd, *magic, *search = search_res;
	u8 search_kind, search_len, copy_len, magic_len;
	पूर्णांक ret;

	/* 2 byte is the minimal option len except TCPOPT_NOP and
	 * TCPOPT_EOL which are useless क्रम the bpf prog to learn
	 * and this helper disallow loading them also.
	 */
	अगर (len < 2 || flags & ~BPF_LOAD_HDR_OPT_TCP_SYN)
		वापस -EINVAL;

	search_kind = search[0];
	search_len = search[1];

	अगर (search_len > len || search_kind == TCPOPT_NOP ||
	    search_kind == TCPOPT_EOL)
		वापस -EINVAL;

	अगर (search_kind == TCPOPT_EXP || search_kind == 253) अणु
		/* 16 or 32 bit magic.  +2 क्रम kind and kind length */
		अगर (search_len != 4 && search_len != 6)
			वापस -EINVAL;
		magic = &search[2];
		magic_len = search_len - 2;
	पूर्ण अन्यथा अणु
		अगर (search_len)
			वापस -EINVAL;
		magic = शून्य;
		magic_len = 0;
	पूर्ण

	अगर (load_syn) अणु
		ret = bpf_sock_ops_get_syn(bpf_sock, TCP_BPF_SYN, &op);
		अगर (ret < 0)
			वापस ret;

		खोलोd = op + ret;
		op += माप(काष्ठा tcphdr);
	पूर्ण अन्यथा अणु
		अगर (!bpf_sock->skb ||
		    bpf_sock->op == BPF_SOCK_OPS_HDR_OPT_LEN_CB)
			/* This bpf_sock->op cannot call this helper */
			वापस -EPERM;

		खोलोd = bpf_sock->skb_data_end;
		op = bpf_sock->skb->data + माप(काष्ठा tcphdr);
	पूर्ण

	op = bpf_search_tcp_opt(op, खोलोd, search_kind, magic, magic_len,
				&eol);
	अगर (IS_ERR(op))
		वापस PTR_ERR(op);

	copy_len = op[1];
	ret = copy_len;
	अगर (copy_len > len) अणु
		ret = -ENOSPC;
		copy_len = len;
	पूर्ण

	स_नकल(search_res, op, copy_len);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sock_ops_load_hdr_opt_proto = अणु
	.func		= bpf_sock_ops_load_hdr_opt,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_sock_ops_store_hdr_opt, काष्ठा bpf_sock_ops_kern *, bpf_sock,
	   स्थिर व्योम *, from, u32, len, u64, flags)
अणु
	u8 new_kind, new_kind_len, magic_len = 0, *खोलोd;
	स्थिर u8 *op, *new_op, *magic = शून्य;
	काष्ठा sk_buff *skb;
	bool eol;

	अगर (bpf_sock->op != BPF_SOCK_OPS_WRITE_HDR_OPT_CB)
		वापस -EPERM;

	अगर (len < 2 || flags)
		वापस -EINVAL;

	new_op = from;
	new_kind = new_op[0];
	new_kind_len = new_op[1];

	अगर (new_kind_len > len || new_kind == TCPOPT_NOP ||
	    new_kind == TCPOPT_EOL)
		वापस -EINVAL;

	अगर (new_kind_len > bpf_sock->reमुख्यing_opt_len)
		वापस -ENOSPC;

	/* 253 is another experimental kind */
	अगर (new_kind == TCPOPT_EXP || new_kind == 253)  अणु
		अगर (new_kind_len < 4)
			वापस -EINVAL;
		/* Match क्रम the 2 byte magic also.
		 * RFC 6994: the magic could be 2 or 4 bytes.
		 * Hence, matching by 2 byte only is on the
		 * conservative side but it is the right
		 * thing to करो क्रम the 'search-for-duplication'
		 * purpose.
		 */
		magic = &new_op[2];
		magic_len = 2;
	पूर्ण

	/* Check क्रम duplication */
	skb = bpf_sock->skb;
	op = skb->data + माप(काष्ठा tcphdr);
	खोलोd = bpf_sock->skb_data_end;

	op = bpf_search_tcp_opt(op, खोलोd, new_kind, magic, magic_len,
				&eol);
	अगर (!IS_ERR(op))
		वापस -EEXIST;

	अगर (PTR_ERR(op) != -ENOMSG)
		वापस PTR_ERR(op);

	अगर (eol)
		/* The option has been ended.  Treat it as no more
		 * header option can be written.
		 */
		वापस -ENOSPC;

	/* No duplication found.  Store the header option. */
	स_नकल(खोलोd, from, new_kind_len);

	bpf_sock->reमुख्यing_opt_len -= new_kind_len;
	bpf_sock->skb_data_end += new_kind_len;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sock_ops_store_hdr_opt_proto = अणु
	.func		= bpf_sock_ops_store_hdr_opt,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_3(bpf_sock_ops_reserve_hdr_opt, काष्ठा bpf_sock_ops_kern *, bpf_sock,
	   u32, len, u64, flags)
अणु
	अगर (bpf_sock->op != BPF_SOCK_OPS_HDR_OPT_LEN_CB)
		वापस -EPERM;

	अगर (flags || len < 2)
		वापस -EINVAL;

	अगर (len > bpf_sock->reमुख्यing_opt_len)
		वापस -ENOSPC;

	bpf_sock->reमुख्यing_opt_len -= len;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sock_ops_reserve_hdr_opt_proto = अणु
	.func		= bpf_sock_ops_reserve_hdr_opt,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

#पूर्ण_अगर /* CONFIG_INET */

bool bpf_helper_changes_pkt_data(व्योम *func)
अणु
	अगर (func == bpf_skb_vlan_push ||
	    func == bpf_skb_vlan_pop ||
	    func == bpf_skb_store_bytes ||
	    func == bpf_skb_change_proto ||
	    func == bpf_skb_change_head ||
	    func == sk_skb_change_head ||
	    func == bpf_skb_change_tail ||
	    func == sk_skb_change_tail ||
	    func == bpf_skb_adjust_room ||
	    func == sk_skb_adjust_room ||
	    func == bpf_skb_pull_data ||
	    func == sk_skb_pull_data ||
	    func == bpf_clone_redirect ||
	    func == bpf_l3_csum_replace ||
	    func == bpf_l4_csum_replace ||
	    func == bpf_xdp_adjust_head ||
	    func == bpf_xdp_adjust_meta ||
	    func == bpf_msg_pull_data ||
	    func == bpf_msg_push_data ||
	    func == bpf_msg_pop_data ||
	    func == bpf_xdp_adjust_tail ||
#अगर IS_ENABLED(CONFIG_IPV6_SEG6_BPF)
	    func == bpf_lwt_seg6_store_bytes ||
	    func == bpf_lwt_seg6_adjust_srh ||
	    func == bpf_lwt_seg6_action ||
#पूर्ण_अगर
#अगर_घोषित CONFIG_INET
	    func == bpf_sock_ops_store_hdr_opt ||
#पूर्ण_अगर
	    func == bpf_lwt_in_push_encap ||
	    func == bpf_lwt_xmit_push_encap)
		वापस true;

	वापस false;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_event_output_data_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_sk_storage_get_cg_sock_proto __weak;

अटल स्थिर काष्ठा bpf_func_proto *
sock_filter_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	/* inet and inet6 sockets are created in a process
	 * context so there is always a valid uid/gid
	 */
	हाल BPF_FUNC_get_current_uid_gid:
		वापस &bpf_get_current_uid_gid_proto;
	हाल BPF_FUNC_get_local_storage:
		वापस &bpf_get_local_storage_proto;
	हाल BPF_FUNC_get_socket_cookie:
		वापस &bpf_get_socket_cookie_sock_proto;
	हाल BPF_FUNC_get_netns_cookie:
		वापस &bpf_get_netns_cookie_sock_proto;
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_event_output_data_proto;
	हाल BPF_FUNC_get_current_pid_tgid:
		वापस &bpf_get_current_pid_tgid_proto;
	हाल BPF_FUNC_get_current_comm:
		वापस &bpf_get_current_comm_proto;
#अगर_घोषित CONFIG_CGROUPS
	हाल BPF_FUNC_get_current_cgroup_id:
		वापस &bpf_get_current_cgroup_id_proto;
	हाल BPF_FUNC_get_current_ancestor_cgroup_id:
		वापस &bpf_get_current_ancestor_cgroup_id_proto;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUP_NET_CLASSID
	हाल BPF_FUNC_get_cgroup_classid:
		वापस &bpf_get_cgroup_classid_curr_proto;
#पूर्ण_अगर
	हाल BPF_FUNC_sk_storage_get:
		वापस &bpf_sk_storage_get_cg_sock_proto;
	शेष:
		वापस bpf_base_func_proto(func_id);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto *
sock_addr_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	/* inet and inet6 sockets are created in a process
	 * context so there is always a valid uid/gid
	 */
	हाल BPF_FUNC_get_current_uid_gid:
		वापस &bpf_get_current_uid_gid_proto;
	हाल BPF_FUNC_bind:
		चयन (prog->expected_attach_type) अणु
		हाल BPF_CGROUP_INET4_CONNECT:
		हाल BPF_CGROUP_INET6_CONNECT:
			वापस &bpf_bind_proto;
		शेष:
			वापस शून्य;
		पूर्ण
	हाल BPF_FUNC_get_socket_cookie:
		वापस &bpf_get_socket_cookie_sock_addr_proto;
	हाल BPF_FUNC_get_netns_cookie:
		वापस &bpf_get_netns_cookie_sock_addr_proto;
	हाल BPF_FUNC_get_local_storage:
		वापस &bpf_get_local_storage_proto;
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_event_output_data_proto;
	हाल BPF_FUNC_get_current_pid_tgid:
		वापस &bpf_get_current_pid_tgid_proto;
	हाल BPF_FUNC_get_current_comm:
		वापस &bpf_get_current_comm_proto;
#अगर_घोषित CONFIG_CGROUPS
	हाल BPF_FUNC_get_current_cgroup_id:
		वापस &bpf_get_current_cgroup_id_proto;
	हाल BPF_FUNC_get_current_ancestor_cgroup_id:
		वापस &bpf_get_current_ancestor_cgroup_id_proto;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUP_NET_CLASSID
	हाल BPF_FUNC_get_cgroup_classid:
		वापस &bpf_get_cgroup_classid_curr_proto;
#पूर्ण_अगर
#अगर_घोषित CONFIG_INET
	हाल BPF_FUNC_sk_lookup_tcp:
		वापस &bpf_sock_addr_sk_lookup_tcp_proto;
	हाल BPF_FUNC_sk_lookup_udp:
		वापस &bpf_sock_addr_sk_lookup_udp_proto;
	हाल BPF_FUNC_sk_release:
		वापस &bpf_sk_release_proto;
	हाल BPF_FUNC_skc_lookup_tcp:
		वापस &bpf_sock_addr_skc_lookup_tcp_proto;
#पूर्ण_अगर /* CONFIG_INET */
	हाल BPF_FUNC_sk_storage_get:
		वापस &bpf_sk_storage_get_proto;
	हाल BPF_FUNC_sk_storage_delete:
		वापस &bpf_sk_storage_delete_proto;
	हाल BPF_FUNC_setsockopt:
		चयन (prog->expected_attach_type) अणु
		हाल BPF_CGROUP_INET4_BIND:
		हाल BPF_CGROUP_INET6_BIND:
		हाल BPF_CGROUP_INET4_CONNECT:
		हाल BPF_CGROUP_INET6_CONNECT:
		हाल BPF_CGROUP_UDP4_RECVMSG:
		हाल BPF_CGROUP_UDP6_RECVMSG:
		हाल BPF_CGROUP_UDP4_SENDMSG:
		हाल BPF_CGROUP_UDP6_SENDMSG:
		हाल BPF_CGROUP_INET4_GETPEERNAME:
		हाल BPF_CGROUP_INET6_GETPEERNAME:
		हाल BPF_CGROUP_INET4_GETSOCKNAME:
		हाल BPF_CGROUP_INET6_GETSOCKNAME:
			वापस &bpf_sock_addr_setsockopt_proto;
		शेष:
			वापस शून्य;
		पूर्ण
	हाल BPF_FUNC_माला_लोockopt:
		चयन (prog->expected_attach_type) अणु
		हाल BPF_CGROUP_INET4_BIND:
		हाल BPF_CGROUP_INET6_BIND:
		हाल BPF_CGROUP_INET4_CONNECT:
		हाल BPF_CGROUP_INET6_CONNECT:
		हाल BPF_CGROUP_UDP4_RECVMSG:
		हाल BPF_CGROUP_UDP6_RECVMSG:
		हाल BPF_CGROUP_UDP4_SENDMSG:
		हाल BPF_CGROUP_UDP6_SENDMSG:
		हाल BPF_CGROUP_INET4_GETPEERNAME:
		हाल BPF_CGROUP_INET6_GETPEERNAME:
		हाल BPF_CGROUP_INET4_GETSOCKNAME:
		हाल BPF_CGROUP_INET6_GETSOCKNAME:
			वापस &bpf_sock_addr_माला_लोockopt_proto;
		शेष:
			वापस शून्य;
		पूर्ण
	शेष:
		वापस bpf_sk_base_func_proto(func_id);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto *
sk_filter_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_skb_load_bytes:
		वापस &bpf_skb_load_bytes_proto;
	हाल BPF_FUNC_skb_load_bytes_relative:
		वापस &bpf_skb_load_bytes_relative_proto;
	हाल BPF_FUNC_get_socket_cookie:
		वापस &bpf_get_socket_cookie_proto;
	हाल BPF_FUNC_get_socket_uid:
		वापस &bpf_get_socket_uid_proto;
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_skb_event_output_proto;
	शेष:
		वापस bpf_sk_base_func_proto(func_id);
	पूर्ण
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_sk_storage_get_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_sk_storage_delete_proto __weak;

अटल स्थिर काष्ठा bpf_func_proto *
cg_skb_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_get_local_storage:
		वापस &bpf_get_local_storage_proto;
	हाल BPF_FUNC_sk_fullsock:
		वापस &bpf_sk_fullsock_proto;
	हाल BPF_FUNC_sk_storage_get:
		वापस &bpf_sk_storage_get_proto;
	हाल BPF_FUNC_sk_storage_delete:
		वापस &bpf_sk_storage_delete_proto;
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_skb_event_output_proto;
#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
	हाल BPF_FUNC_skb_cgroup_id:
		वापस &bpf_skb_cgroup_id_proto;
	हाल BPF_FUNC_skb_ancestor_cgroup_id:
		वापस &bpf_skb_ancestor_cgroup_id_proto;
	हाल BPF_FUNC_sk_cgroup_id:
		वापस &bpf_sk_cgroup_id_proto;
	हाल BPF_FUNC_sk_ancestor_cgroup_id:
		वापस &bpf_sk_ancestor_cgroup_id_proto;
#पूर्ण_अगर
#अगर_घोषित CONFIG_INET
	हाल BPF_FUNC_sk_lookup_tcp:
		वापस &bpf_sk_lookup_tcp_proto;
	हाल BPF_FUNC_sk_lookup_udp:
		वापस &bpf_sk_lookup_udp_proto;
	हाल BPF_FUNC_sk_release:
		वापस &bpf_sk_release_proto;
	हाल BPF_FUNC_skc_lookup_tcp:
		वापस &bpf_skc_lookup_tcp_proto;
	हाल BPF_FUNC_tcp_sock:
		वापस &bpf_tcp_sock_proto;
	हाल BPF_FUNC_get_listener_sock:
		वापस &bpf_get_listener_sock_proto;
	हाल BPF_FUNC_skb_ecn_set_ce:
		वापस &bpf_skb_ecn_set_ce_proto;
#पूर्ण_अगर
	शेष:
		वापस sk_filter_func_proto(func_id, prog);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto *
tc_cls_act_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_skb_store_bytes:
		वापस &bpf_skb_store_bytes_proto;
	हाल BPF_FUNC_skb_load_bytes:
		वापस &bpf_skb_load_bytes_proto;
	हाल BPF_FUNC_skb_load_bytes_relative:
		वापस &bpf_skb_load_bytes_relative_proto;
	हाल BPF_FUNC_skb_pull_data:
		वापस &bpf_skb_pull_data_proto;
	हाल BPF_FUNC_csum_dअगरf:
		वापस &bpf_csum_dअगरf_proto;
	हाल BPF_FUNC_csum_update:
		वापस &bpf_csum_update_proto;
	हाल BPF_FUNC_csum_level:
		वापस &bpf_csum_level_proto;
	हाल BPF_FUNC_l3_csum_replace:
		वापस &bpf_l3_csum_replace_proto;
	हाल BPF_FUNC_l4_csum_replace:
		वापस &bpf_l4_csum_replace_proto;
	हाल BPF_FUNC_clone_redirect:
		वापस &bpf_clone_redirect_proto;
	हाल BPF_FUNC_get_cgroup_classid:
		वापस &bpf_get_cgroup_classid_proto;
	हाल BPF_FUNC_skb_vlan_push:
		वापस &bpf_skb_vlan_push_proto;
	हाल BPF_FUNC_skb_vlan_pop:
		वापस &bpf_skb_vlan_pop_proto;
	हाल BPF_FUNC_skb_change_proto:
		वापस &bpf_skb_change_proto_proto;
	हाल BPF_FUNC_skb_change_type:
		वापस &bpf_skb_change_type_proto;
	हाल BPF_FUNC_skb_adjust_room:
		वापस &bpf_skb_adjust_room_proto;
	हाल BPF_FUNC_skb_change_tail:
		वापस &bpf_skb_change_tail_proto;
	हाल BPF_FUNC_skb_change_head:
		वापस &bpf_skb_change_head_proto;
	हाल BPF_FUNC_skb_get_tunnel_key:
		वापस &bpf_skb_get_tunnel_key_proto;
	हाल BPF_FUNC_skb_set_tunnel_key:
		वापस bpf_get_skb_set_tunnel_proto(func_id);
	हाल BPF_FUNC_skb_get_tunnel_opt:
		वापस &bpf_skb_get_tunnel_opt_proto;
	हाल BPF_FUNC_skb_set_tunnel_opt:
		वापस bpf_get_skb_set_tunnel_proto(func_id);
	हाल BPF_FUNC_redirect:
		वापस &bpf_redirect_proto;
	हाल BPF_FUNC_redirect_neigh:
		वापस &bpf_redirect_neigh_proto;
	हाल BPF_FUNC_redirect_peer:
		वापस &bpf_redirect_peer_proto;
	हाल BPF_FUNC_get_route_realm:
		वापस &bpf_get_route_realm_proto;
	हाल BPF_FUNC_get_hash_recalc:
		वापस &bpf_get_hash_recalc_proto;
	हाल BPF_FUNC_set_hash_invalid:
		वापस &bpf_set_hash_invalid_proto;
	हाल BPF_FUNC_set_hash:
		वापस &bpf_set_hash_proto;
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_skb_event_output_proto;
	हाल BPF_FUNC_get_smp_processor_id:
		वापस &bpf_get_smp_processor_id_proto;
	हाल BPF_FUNC_skb_under_cgroup:
		वापस &bpf_skb_under_cgroup_proto;
	हाल BPF_FUNC_get_socket_cookie:
		वापस &bpf_get_socket_cookie_proto;
	हाल BPF_FUNC_get_socket_uid:
		वापस &bpf_get_socket_uid_proto;
	हाल BPF_FUNC_fib_lookup:
		वापस &bpf_skb_fib_lookup_proto;
	हाल BPF_FUNC_check_mtu:
		वापस &bpf_skb_check_mtu_proto;
	हाल BPF_FUNC_sk_fullsock:
		वापस &bpf_sk_fullsock_proto;
	हाल BPF_FUNC_sk_storage_get:
		वापस &bpf_sk_storage_get_proto;
	हाल BPF_FUNC_sk_storage_delete:
		वापस &bpf_sk_storage_delete_proto;
#अगर_घोषित CONFIG_XFRM
	हाल BPF_FUNC_skb_get_xfrm_state:
		वापस &bpf_skb_get_xfrm_state_proto;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUP_NET_CLASSID
	हाल BPF_FUNC_skb_cgroup_classid:
		वापस &bpf_skb_cgroup_classid_proto;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
	हाल BPF_FUNC_skb_cgroup_id:
		वापस &bpf_skb_cgroup_id_proto;
	हाल BPF_FUNC_skb_ancestor_cgroup_id:
		वापस &bpf_skb_ancestor_cgroup_id_proto;
#पूर्ण_अगर
#अगर_घोषित CONFIG_INET
	हाल BPF_FUNC_sk_lookup_tcp:
		वापस &bpf_sk_lookup_tcp_proto;
	हाल BPF_FUNC_sk_lookup_udp:
		वापस &bpf_sk_lookup_udp_proto;
	हाल BPF_FUNC_sk_release:
		वापस &bpf_sk_release_proto;
	हाल BPF_FUNC_tcp_sock:
		वापस &bpf_tcp_sock_proto;
	हाल BPF_FUNC_get_listener_sock:
		वापस &bpf_get_listener_sock_proto;
	हाल BPF_FUNC_skc_lookup_tcp:
		वापस &bpf_skc_lookup_tcp_proto;
	हाल BPF_FUNC_tcp_check_syncookie:
		वापस &bpf_tcp_check_syncookie_proto;
	हाल BPF_FUNC_skb_ecn_set_ce:
		वापस &bpf_skb_ecn_set_ce_proto;
	हाल BPF_FUNC_tcp_gen_syncookie:
		वापस &bpf_tcp_gen_syncookie_proto;
	हाल BPF_FUNC_sk_assign:
		वापस &bpf_sk_assign_proto;
#पूर्ण_अगर
	शेष:
		वापस bpf_sk_base_func_proto(func_id);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto *
xdp_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_xdp_event_output_proto;
	हाल BPF_FUNC_get_smp_processor_id:
		वापस &bpf_get_smp_processor_id_proto;
	हाल BPF_FUNC_csum_dअगरf:
		वापस &bpf_csum_dअगरf_proto;
	हाल BPF_FUNC_xdp_adjust_head:
		वापस &bpf_xdp_adjust_head_proto;
	हाल BPF_FUNC_xdp_adjust_meta:
		वापस &bpf_xdp_adjust_meta_proto;
	हाल BPF_FUNC_redirect:
		वापस &bpf_xdp_redirect_proto;
	हाल BPF_FUNC_redirect_map:
		वापस &bpf_xdp_redirect_map_proto;
	हाल BPF_FUNC_xdp_adjust_tail:
		वापस &bpf_xdp_adjust_tail_proto;
	हाल BPF_FUNC_fib_lookup:
		वापस &bpf_xdp_fib_lookup_proto;
	हाल BPF_FUNC_check_mtu:
		वापस &bpf_xdp_check_mtu_proto;
#अगर_घोषित CONFIG_INET
	हाल BPF_FUNC_sk_lookup_udp:
		वापस &bpf_xdp_sk_lookup_udp_proto;
	हाल BPF_FUNC_sk_lookup_tcp:
		वापस &bpf_xdp_sk_lookup_tcp_proto;
	हाल BPF_FUNC_sk_release:
		वापस &bpf_sk_release_proto;
	हाल BPF_FUNC_skc_lookup_tcp:
		वापस &bpf_xdp_skc_lookup_tcp_proto;
	हाल BPF_FUNC_tcp_check_syncookie:
		वापस &bpf_tcp_check_syncookie_proto;
	हाल BPF_FUNC_tcp_gen_syncookie:
		वापस &bpf_tcp_gen_syncookie_proto;
#पूर्ण_अगर
	शेष:
		वापस bpf_sk_base_func_proto(func_id);
	पूर्ण
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_sock_map_update_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_sock_hash_update_proto __weak;

अटल स्थिर काष्ठा bpf_func_proto *
sock_ops_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_setsockopt:
		वापस &bpf_sock_ops_setsockopt_proto;
	हाल BPF_FUNC_माला_लोockopt:
		वापस &bpf_sock_ops_माला_लोockopt_proto;
	हाल BPF_FUNC_sock_ops_cb_flags_set:
		वापस &bpf_sock_ops_cb_flags_set_proto;
	हाल BPF_FUNC_sock_map_update:
		वापस &bpf_sock_map_update_proto;
	हाल BPF_FUNC_sock_hash_update:
		वापस &bpf_sock_hash_update_proto;
	हाल BPF_FUNC_get_socket_cookie:
		वापस &bpf_get_socket_cookie_sock_ops_proto;
	हाल BPF_FUNC_get_local_storage:
		वापस &bpf_get_local_storage_proto;
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_event_output_data_proto;
	हाल BPF_FUNC_sk_storage_get:
		वापस &bpf_sk_storage_get_proto;
	हाल BPF_FUNC_sk_storage_delete:
		वापस &bpf_sk_storage_delete_proto;
#अगर_घोषित CONFIG_INET
	हाल BPF_FUNC_load_hdr_opt:
		वापस &bpf_sock_ops_load_hdr_opt_proto;
	हाल BPF_FUNC_store_hdr_opt:
		वापस &bpf_sock_ops_store_hdr_opt_proto;
	हाल BPF_FUNC_reserve_hdr_opt:
		वापस &bpf_sock_ops_reserve_hdr_opt_proto;
	हाल BPF_FUNC_tcp_sock:
		वापस &bpf_tcp_sock_proto;
#पूर्ण_अगर /* CONFIG_INET */
	शेष:
		वापस bpf_sk_base_func_proto(func_id);
	पूर्ण
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_msg_redirect_map_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_msg_redirect_hash_proto __weak;

अटल स्थिर काष्ठा bpf_func_proto *
sk_msg_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_msg_redirect_map:
		वापस &bpf_msg_redirect_map_proto;
	हाल BPF_FUNC_msg_redirect_hash:
		वापस &bpf_msg_redirect_hash_proto;
	हाल BPF_FUNC_msg_apply_bytes:
		वापस &bpf_msg_apply_bytes_proto;
	हाल BPF_FUNC_msg_cork_bytes:
		वापस &bpf_msg_cork_bytes_proto;
	हाल BPF_FUNC_msg_pull_data:
		वापस &bpf_msg_pull_data_proto;
	हाल BPF_FUNC_msg_push_data:
		वापस &bpf_msg_push_data_proto;
	हाल BPF_FUNC_msg_pop_data:
		वापस &bpf_msg_pop_data_proto;
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_event_output_data_proto;
	हाल BPF_FUNC_get_current_uid_gid:
		वापस &bpf_get_current_uid_gid_proto;
	हाल BPF_FUNC_get_current_pid_tgid:
		वापस &bpf_get_current_pid_tgid_proto;
	हाल BPF_FUNC_sk_storage_get:
		वापस &bpf_sk_storage_get_proto;
	हाल BPF_FUNC_sk_storage_delete:
		वापस &bpf_sk_storage_delete_proto;
#अगर_घोषित CONFIG_CGROUPS
	हाल BPF_FUNC_get_current_cgroup_id:
		वापस &bpf_get_current_cgroup_id_proto;
	हाल BPF_FUNC_get_current_ancestor_cgroup_id:
		वापस &bpf_get_current_ancestor_cgroup_id_proto;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUP_NET_CLASSID
	हाल BPF_FUNC_get_cgroup_classid:
		वापस &bpf_get_cgroup_classid_curr_proto;
#पूर्ण_अगर
	शेष:
		वापस bpf_sk_base_func_proto(func_id);
	पूर्ण
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_sk_redirect_map_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_sk_redirect_hash_proto __weak;

अटल स्थिर काष्ठा bpf_func_proto *
sk_skb_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_skb_store_bytes:
		वापस &bpf_skb_store_bytes_proto;
	हाल BPF_FUNC_skb_load_bytes:
		वापस &bpf_skb_load_bytes_proto;
	हाल BPF_FUNC_skb_pull_data:
		वापस &sk_skb_pull_data_proto;
	हाल BPF_FUNC_skb_change_tail:
		वापस &sk_skb_change_tail_proto;
	हाल BPF_FUNC_skb_change_head:
		वापस &sk_skb_change_head_proto;
	हाल BPF_FUNC_skb_adjust_room:
		वापस &sk_skb_adjust_room_proto;
	हाल BPF_FUNC_get_socket_cookie:
		वापस &bpf_get_socket_cookie_proto;
	हाल BPF_FUNC_get_socket_uid:
		वापस &bpf_get_socket_uid_proto;
	हाल BPF_FUNC_sk_redirect_map:
		वापस &bpf_sk_redirect_map_proto;
	हाल BPF_FUNC_sk_redirect_hash:
		वापस &bpf_sk_redirect_hash_proto;
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_skb_event_output_proto;
#अगर_घोषित CONFIG_INET
	हाल BPF_FUNC_sk_lookup_tcp:
		वापस &bpf_sk_lookup_tcp_proto;
	हाल BPF_FUNC_sk_lookup_udp:
		वापस &bpf_sk_lookup_udp_proto;
	हाल BPF_FUNC_sk_release:
		वापस &bpf_sk_release_proto;
	हाल BPF_FUNC_skc_lookup_tcp:
		वापस &bpf_skc_lookup_tcp_proto;
#पूर्ण_अगर
	शेष:
		वापस bpf_sk_base_func_proto(func_id);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto *
flow_dissector_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_skb_load_bytes:
		वापस &bpf_flow_dissector_load_bytes_proto;
	शेष:
		वापस bpf_sk_base_func_proto(func_id);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto *
lwt_out_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_skb_load_bytes:
		वापस &bpf_skb_load_bytes_proto;
	हाल BPF_FUNC_skb_pull_data:
		वापस &bpf_skb_pull_data_proto;
	हाल BPF_FUNC_csum_dअगरf:
		वापस &bpf_csum_dअगरf_proto;
	हाल BPF_FUNC_get_cgroup_classid:
		वापस &bpf_get_cgroup_classid_proto;
	हाल BPF_FUNC_get_route_realm:
		वापस &bpf_get_route_realm_proto;
	हाल BPF_FUNC_get_hash_recalc:
		वापस &bpf_get_hash_recalc_proto;
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_skb_event_output_proto;
	हाल BPF_FUNC_get_smp_processor_id:
		वापस &bpf_get_smp_processor_id_proto;
	हाल BPF_FUNC_skb_under_cgroup:
		वापस &bpf_skb_under_cgroup_proto;
	शेष:
		वापस bpf_sk_base_func_proto(func_id);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto *
lwt_in_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_lwt_push_encap:
		वापस &bpf_lwt_in_push_encap_proto;
	शेष:
		वापस lwt_out_func_proto(func_id, prog);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto *
lwt_xmit_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_skb_get_tunnel_key:
		वापस &bpf_skb_get_tunnel_key_proto;
	हाल BPF_FUNC_skb_set_tunnel_key:
		वापस bpf_get_skb_set_tunnel_proto(func_id);
	हाल BPF_FUNC_skb_get_tunnel_opt:
		वापस &bpf_skb_get_tunnel_opt_proto;
	हाल BPF_FUNC_skb_set_tunnel_opt:
		वापस bpf_get_skb_set_tunnel_proto(func_id);
	हाल BPF_FUNC_redirect:
		वापस &bpf_redirect_proto;
	हाल BPF_FUNC_clone_redirect:
		वापस &bpf_clone_redirect_proto;
	हाल BPF_FUNC_skb_change_tail:
		वापस &bpf_skb_change_tail_proto;
	हाल BPF_FUNC_skb_change_head:
		वापस &bpf_skb_change_head_proto;
	हाल BPF_FUNC_skb_store_bytes:
		वापस &bpf_skb_store_bytes_proto;
	हाल BPF_FUNC_csum_update:
		वापस &bpf_csum_update_proto;
	हाल BPF_FUNC_csum_level:
		वापस &bpf_csum_level_proto;
	हाल BPF_FUNC_l3_csum_replace:
		वापस &bpf_l3_csum_replace_proto;
	हाल BPF_FUNC_l4_csum_replace:
		वापस &bpf_l4_csum_replace_proto;
	हाल BPF_FUNC_set_hash_invalid:
		वापस &bpf_set_hash_invalid_proto;
	हाल BPF_FUNC_lwt_push_encap:
		वापस &bpf_lwt_xmit_push_encap_proto;
	शेष:
		वापस lwt_out_func_proto(func_id, prog);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto *
lwt_seg6local_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
#अगर IS_ENABLED(CONFIG_IPV6_SEG6_BPF)
	हाल BPF_FUNC_lwt_seg6_store_bytes:
		वापस &bpf_lwt_seg6_store_bytes_proto;
	हाल BPF_FUNC_lwt_seg6_action:
		वापस &bpf_lwt_seg6_action_proto;
	हाल BPF_FUNC_lwt_seg6_adjust_srh:
		वापस &bpf_lwt_seg6_adjust_srh_proto;
#पूर्ण_अगर
	शेष:
		वापस lwt_out_func_proto(func_id, prog);
	पूर्ण
पूर्ण

अटल bool bpf_skb_is_valid_access(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
				    स्थिर काष्ठा bpf_prog *prog,
				    काष्ठा bpf_insn_access_aux *info)
अणु
	स्थिर पूर्णांक size_शेष = माप(__u32);

	अगर (off < 0 || off >= माप(काष्ठा __sk_buff))
		वापस false;

	/* The verअगरier guarantees that size > 0. */
	अगर (off % size != 0)
		वापस false;

	चयन (off) अणु
	हाल bpf_ctx_range_till(काष्ठा __sk_buff, cb[0], cb[4]):
		अगर (off + size > दुरत्वend(काष्ठा __sk_buff, cb[4]))
			वापस false;
		अवरोध;
	हाल bpf_ctx_range_till(काष्ठा __sk_buff, remote_ip6[0], remote_ip6[3]):
	हाल bpf_ctx_range_till(काष्ठा __sk_buff, local_ip6[0], local_ip6[3]):
	हाल bpf_ctx_range_till(काष्ठा __sk_buff, remote_ip4, remote_ip4):
	हाल bpf_ctx_range_till(काष्ठा __sk_buff, local_ip4, local_ip4):
	हाल bpf_ctx_range(काष्ठा __sk_buff, data):
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_meta):
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_end):
		अगर (size != size_शेष)
			वापस false;
		अवरोध;
	हाल bpf_ctx_range_ptr(काष्ठा __sk_buff, flow_keys):
		वापस false;
	हाल bpf_ctx_range(काष्ठा __sk_buff, tstamp):
		अगर (size != माप(__u64))
			वापस false;
		अवरोध;
	हाल दुरत्व(काष्ठा __sk_buff, sk):
		अगर (type == BPF_WRITE || size != माप(__u64))
			वापस false;
		info->reg_type = PTR_TO_SOCK_COMMON_OR_शून्य;
		अवरोध;
	शेष:
		/* Only narrow पढ़ो access allowed क्रम now. */
		अगर (type == BPF_WRITE) अणु
			अगर (size != size_शेष)
				वापस false;
		पूर्ण अन्यथा अणु
			bpf_ctx_record_field_size(info, size_शेष);
			अगर (!bpf_ctx_narrow_access_ok(off, size, size_शेष))
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool sk_filter_is_valid_access(पूर्णांक off, पूर्णांक size,
				      क्रमागत bpf_access_type type,
				      स्थिर काष्ठा bpf_prog *prog,
				      काष्ठा bpf_insn_access_aux *info)
अणु
	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा __sk_buff, tc_classid):
	हाल bpf_ctx_range(काष्ठा __sk_buff, data):
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_meta):
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_end):
	हाल bpf_ctx_range_till(काष्ठा __sk_buff, family, local_port):
	हाल bpf_ctx_range(काष्ठा __sk_buff, tstamp):
	हाल bpf_ctx_range(काष्ठा __sk_buff, wire_len):
		वापस false;
	पूर्ण

	अगर (type == BPF_WRITE) अणु
		चयन (off) अणु
		हाल bpf_ctx_range_till(काष्ठा __sk_buff, cb[0], cb[4]):
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	वापस bpf_skb_is_valid_access(off, size, type, prog, info);
पूर्ण

अटल bool cg_skb_is_valid_access(पूर्णांक off, पूर्णांक size,
				   क्रमागत bpf_access_type type,
				   स्थिर काष्ठा bpf_prog *prog,
				   काष्ठा bpf_insn_access_aux *info)
अणु
	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा __sk_buff, tc_classid):
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_meta):
	हाल bpf_ctx_range(काष्ठा __sk_buff, wire_len):
		वापस false;
	हाल bpf_ctx_range(काष्ठा __sk_buff, data):
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_end):
		अगर (!bpf_capable())
			वापस false;
		अवरोध;
	पूर्ण

	अगर (type == BPF_WRITE) अणु
		चयन (off) अणु
		हाल bpf_ctx_range(काष्ठा __sk_buff, mark):
		हाल bpf_ctx_range(काष्ठा __sk_buff, priority):
		हाल bpf_ctx_range_till(काष्ठा __sk_buff, cb[0], cb[4]):
			अवरोध;
		हाल bpf_ctx_range(काष्ठा __sk_buff, tstamp):
			अगर (!bpf_capable())
				वापस false;
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा __sk_buff, data):
		info->reg_type = PTR_TO_PACKET;
		अवरोध;
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_end):
		info->reg_type = PTR_TO_PACKET_END;
		अवरोध;
	पूर्ण

	वापस bpf_skb_is_valid_access(off, size, type, prog, info);
पूर्ण

अटल bool lwt_is_valid_access(पूर्णांक off, पूर्णांक size,
				क्रमागत bpf_access_type type,
				स्थिर काष्ठा bpf_prog *prog,
				काष्ठा bpf_insn_access_aux *info)
अणु
	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा __sk_buff, tc_classid):
	हाल bpf_ctx_range_till(काष्ठा __sk_buff, family, local_port):
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_meta):
	हाल bpf_ctx_range(काष्ठा __sk_buff, tstamp):
	हाल bpf_ctx_range(काष्ठा __sk_buff, wire_len):
		वापस false;
	पूर्ण

	अगर (type == BPF_WRITE) अणु
		चयन (off) अणु
		हाल bpf_ctx_range(काष्ठा __sk_buff, mark):
		हाल bpf_ctx_range(काष्ठा __sk_buff, priority):
		हाल bpf_ctx_range_till(काष्ठा __sk_buff, cb[0], cb[4]):
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा __sk_buff, data):
		info->reg_type = PTR_TO_PACKET;
		अवरोध;
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_end):
		info->reg_type = PTR_TO_PACKET_END;
		अवरोध;
	पूर्ण

	वापस bpf_skb_is_valid_access(off, size, type, prog, info);
पूर्ण

/* Attach type specअगरic accesses */
अटल bool __sock_filter_check_attach_type(पूर्णांक off,
					    क्रमागत bpf_access_type access_type,
					    क्रमागत bpf_attach_type attach_type)
अणु
	चयन (off) अणु
	हाल दुरत्व(काष्ठा bpf_sock, bound_dev_अगर):
	हाल दुरत्व(काष्ठा bpf_sock, mark):
	हाल दुरत्व(काष्ठा bpf_sock, priority):
		चयन (attach_type) अणु
		हाल BPF_CGROUP_INET_SOCK_CREATE:
		हाल BPF_CGROUP_INET_SOCK_RELEASE:
			जाओ full_access;
		शेष:
			वापस false;
		पूर्ण
	हाल bpf_ctx_range(काष्ठा bpf_sock, src_ip4):
		चयन (attach_type) अणु
		हाल BPF_CGROUP_INET4_POST_BIND:
			जाओ पढ़ो_only;
		शेष:
			वापस false;
		पूर्ण
	हाल bpf_ctx_range_till(काष्ठा bpf_sock, src_ip6[0], src_ip6[3]):
		चयन (attach_type) अणु
		हाल BPF_CGROUP_INET6_POST_BIND:
			जाओ पढ़ो_only;
		शेष:
			वापस false;
		पूर्ण
	हाल bpf_ctx_range(काष्ठा bpf_sock, src_port):
		चयन (attach_type) अणु
		हाल BPF_CGROUP_INET4_POST_BIND:
		हाल BPF_CGROUP_INET6_POST_BIND:
			जाओ पढ़ो_only;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण
पढ़ो_only:
	वापस access_type == BPF_READ;
full_access:
	वापस true;
पूर्ण

bool bpf_sock_common_is_valid_access(पूर्णांक off, पूर्णांक size,
				     क्रमागत bpf_access_type type,
				     काष्ठा bpf_insn_access_aux *info)
अणु
	चयन (off) अणु
	हाल bpf_ctx_range_till(काष्ठा bpf_sock, type, priority):
		वापस false;
	शेष:
		वापस bpf_sock_is_valid_access(off, size, type, info);
	पूर्ण
पूर्ण

bool bpf_sock_is_valid_access(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
			      काष्ठा bpf_insn_access_aux *info)
अणु
	स्थिर पूर्णांक size_शेष = माप(__u32);

	अगर (off < 0 || off >= माप(काष्ठा bpf_sock))
		वापस false;
	अगर (off % size != 0)
		वापस false;

	चयन (off) अणु
	हाल दुरत्व(काष्ठा bpf_sock, state):
	हाल दुरत्व(काष्ठा bpf_sock, family):
	हाल दुरत्व(काष्ठा bpf_sock, type):
	हाल दुरत्व(काष्ठा bpf_sock, protocol):
	हाल दुरत्व(काष्ठा bpf_sock, dst_port):
	हाल दुरत्व(काष्ठा bpf_sock, src_port):
	हाल दुरत्व(काष्ठा bpf_sock, rx_queue_mapping):
	हाल bpf_ctx_range(काष्ठा bpf_sock, src_ip4):
	हाल bpf_ctx_range_till(काष्ठा bpf_sock, src_ip6[0], src_ip6[3]):
	हाल bpf_ctx_range(काष्ठा bpf_sock, dst_ip4):
	हाल bpf_ctx_range_till(काष्ठा bpf_sock, dst_ip6[0], dst_ip6[3]):
		bpf_ctx_record_field_size(info, size_शेष);
		वापस bpf_ctx_narrow_access_ok(off, size, size_शेष);
	पूर्ण

	वापस size == size_शेष;
पूर्ण

अटल bool sock_filter_is_valid_access(पूर्णांक off, पूर्णांक size,
					क्रमागत bpf_access_type type,
					स्थिर काष्ठा bpf_prog *prog,
					काष्ठा bpf_insn_access_aux *info)
अणु
	अगर (!bpf_sock_is_valid_access(off, size, type, info))
		वापस false;
	वापस __sock_filter_check_attach_type(off, type,
					       prog->expected_attach_type);
पूर्ण

अटल पूर्णांक bpf_noop_prologue(काष्ठा bpf_insn *insn_buf, bool direct_ग_लिखो,
			     स्थिर काष्ठा bpf_prog *prog)
अणु
	/* Neither direct पढ़ो nor direct ग_लिखो requires any preliminary
	 * action.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक bpf_unclone_prologue(काष्ठा bpf_insn *insn_buf, bool direct_ग_लिखो,
				स्थिर काष्ठा bpf_prog *prog, पूर्णांक drop_verdict)
अणु
	काष्ठा bpf_insn *insn = insn_buf;

	अगर (!direct_ग_लिखो)
		वापस 0;

	/* अगर (!skb->cloned)
	 *       जाओ start;
	 *
	 * (Fast-path, otherwise approximation that we might be
	 *  a clone, करो the rest in helper.)
	 */
	*insn++ = BPF_LDX_MEM(BPF_B, BPF_REG_6, BPF_REG_1, CLONED_OFFSET());
	*insn++ = BPF_ALU32_IMM(BPF_AND, BPF_REG_6, CLONED_MASK);
	*insn++ = BPF_JMP_IMM(BPF_JEQ, BPF_REG_6, 0, 7);

	/* ret = bpf_skb_pull_data(skb, 0); */
	*insn++ = BPF_MOV64_REG(BPF_REG_6, BPF_REG_1);
	*insn++ = BPF_ALU64_REG(BPF_XOR, BPF_REG_2, BPF_REG_2);
	*insn++ = BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0,
			       BPF_FUNC_skb_pull_data);
	/* अगर (!ret)
	 *      जाओ restore;
	 * वापस TC_ACT_SHOT;
	 */
	*insn++ = BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 2);
	*insn++ = BPF_ALU32_IMM(BPF_MOV, BPF_REG_0, drop_verdict);
	*insn++ = BPF_EXIT_INSN();

	/* restore: */
	*insn++ = BPF_MOV64_REG(BPF_REG_1, BPF_REG_6);
	/* start: */
	*insn++ = prog->insnsi[0];

	वापस insn - insn_buf;
पूर्ण

अटल पूर्णांक bpf_gen_ld_असल(स्थिर काष्ठा bpf_insn *orig,
			  काष्ठा bpf_insn *insn_buf)
अणु
	bool indirect = BPF_MODE(orig->code) == BPF_IND;
	काष्ठा bpf_insn *insn = insn_buf;

	अगर (!indirect) अणु
		*insn++ = BPF_MOV64_IMM(BPF_REG_2, orig->imm);
	पूर्ण अन्यथा अणु
		*insn++ = BPF_MOV64_REG(BPF_REG_2, orig->src_reg);
		अगर (orig->imm)
			*insn++ = BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, orig->imm);
	पूर्ण
	/* We're guaranteed here that CTX is in R6. */
	*insn++ = BPF_MOV64_REG(BPF_REG_1, BPF_REG_CTX);

	चयन (BPF_SIZE(orig->code)) अणु
	हाल BPF_B:
		*insn++ = BPF_EMIT_CALL(bpf_skb_load_helper_8_no_cache);
		अवरोध;
	हाल BPF_H:
		*insn++ = BPF_EMIT_CALL(bpf_skb_load_helper_16_no_cache);
		अवरोध;
	हाल BPF_W:
		*insn++ = BPF_EMIT_CALL(bpf_skb_load_helper_32_no_cache);
		अवरोध;
	पूर्ण

	*insn++ = BPF_JMP_IMM(BPF_JSGE, BPF_REG_0, 0, 2);
	*insn++ = BPF_ALU32_REG(BPF_XOR, BPF_REG_0, BPF_REG_0);
	*insn++ = BPF_EXIT_INSN();

	वापस insn - insn_buf;
पूर्ण

अटल पूर्णांक tc_cls_act_prologue(काष्ठा bpf_insn *insn_buf, bool direct_ग_लिखो,
			       स्थिर काष्ठा bpf_prog *prog)
अणु
	वापस bpf_unclone_prologue(insn_buf, direct_ग_लिखो, prog, TC_ACT_SHOT);
पूर्ण

अटल bool tc_cls_act_is_valid_access(पूर्णांक off, पूर्णांक size,
				       क्रमागत bpf_access_type type,
				       स्थिर काष्ठा bpf_prog *prog,
				       काष्ठा bpf_insn_access_aux *info)
अणु
	अगर (type == BPF_WRITE) अणु
		चयन (off) अणु
		हाल bpf_ctx_range(काष्ठा __sk_buff, mark):
		हाल bpf_ctx_range(काष्ठा __sk_buff, tc_index):
		हाल bpf_ctx_range(काष्ठा __sk_buff, priority):
		हाल bpf_ctx_range(काष्ठा __sk_buff, tc_classid):
		हाल bpf_ctx_range_till(काष्ठा __sk_buff, cb[0], cb[4]):
		हाल bpf_ctx_range(काष्ठा __sk_buff, tstamp):
		हाल bpf_ctx_range(काष्ठा __sk_buff, queue_mapping):
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा __sk_buff, data):
		info->reg_type = PTR_TO_PACKET;
		अवरोध;
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_meta):
		info->reg_type = PTR_TO_PACKET_META;
		अवरोध;
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_end):
		info->reg_type = PTR_TO_PACKET_END;
		अवरोध;
	हाल bpf_ctx_range_till(काष्ठा __sk_buff, family, local_port):
		वापस false;
	पूर्ण

	वापस bpf_skb_is_valid_access(off, size, type, prog, info);
पूर्ण

अटल bool __is_valid_xdp_access(पूर्णांक off, पूर्णांक size)
अणु
	अगर (off < 0 || off >= माप(काष्ठा xdp_md))
		वापस false;
	अगर (off % size != 0)
		वापस false;
	अगर (size != माप(__u32))
		वापस false;

	वापस true;
पूर्ण

अटल bool xdp_is_valid_access(पूर्णांक off, पूर्णांक size,
				क्रमागत bpf_access_type type,
				स्थिर काष्ठा bpf_prog *prog,
				काष्ठा bpf_insn_access_aux *info)
अणु
	अगर (prog->expected_attach_type != BPF_XDP_DEVMAP) अणु
		चयन (off) अणु
		हाल दुरत्व(काष्ठा xdp_md, egress_अगरindex):
			वापस false;
		पूर्ण
	पूर्ण

	अगर (type == BPF_WRITE) अणु
		अगर (bpf_prog_is_dev_bound(prog->aux)) अणु
			चयन (off) अणु
			हाल दुरत्व(काष्ठा xdp_md, rx_queue_index):
				वापस __is_valid_xdp_access(off, size);
			पूर्ण
		पूर्ण
		वापस false;
	पूर्ण

	चयन (off) अणु
	हाल दुरत्व(काष्ठा xdp_md, data):
		info->reg_type = PTR_TO_PACKET;
		अवरोध;
	हाल दुरत्व(काष्ठा xdp_md, data_meta):
		info->reg_type = PTR_TO_PACKET_META;
		अवरोध;
	हाल दुरत्व(काष्ठा xdp_md, data_end):
		info->reg_type = PTR_TO_PACKET_END;
		अवरोध;
	पूर्ण

	वापस __is_valid_xdp_access(off, size);
पूर्ण

व्योम bpf_warn_invalid_xdp_action(u32 act)
अणु
	स्थिर u32 act_max = XDP_REसूचीECT;

	WARN_ONCE(1, "%s XDP return value %u, expect packet loss!\n",
		  act > act_max ? "Illegal" : "Driver unsupported",
		  act);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_warn_invalid_xdp_action);

अटल bool sock_addr_is_valid_access(पूर्णांक off, पूर्णांक size,
				      क्रमागत bpf_access_type type,
				      स्थिर काष्ठा bpf_prog *prog,
				      काष्ठा bpf_insn_access_aux *info)
अणु
	स्थिर पूर्णांक size_शेष = माप(__u32);

	अगर (off < 0 || off >= माप(काष्ठा bpf_sock_addr))
		वापस false;
	अगर (off % size != 0)
		वापस false;

	/* Disallow access to IPv6 fields from IPv4 contex and vise
	 * versa.
	 */
	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा bpf_sock_addr, user_ip4):
		चयन (prog->expected_attach_type) अणु
		हाल BPF_CGROUP_INET4_BIND:
		हाल BPF_CGROUP_INET4_CONNECT:
		हाल BPF_CGROUP_INET4_GETPEERNAME:
		हाल BPF_CGROUP_INET4_GETSOCKNAME:
		हाल BPF_CGROUP_UDP4_SENDMSG:
		हाल BPF_CGROUP_UDP4_RECVMSG:
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
		अवरोध;
	हाल bpf_ctx_range_till(काष्ठा bpf_sock_addr, user_ip6[0], user_ip6[3]):
		चयन (prog->expected_attach_type) अणु
		हाल BPF_CGROUP_INET6_BIND:
		हाल BPF_CGROUP_INET6_CONNECT:
		हाल BPF_CGROUP_INET6_GETPEERNAME:
		हाल BPF_CGROUP_INET6_GETSOCKNAME:
		हाल BPF_CGROUP_UDP6_SENDMSG:
		हाल BPF_CGROUP_UDP6_RECVMSG:
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
		अवरोध;
	हाल bpf_ctx_range(काष्ठा bpf_sock_addr, msg_src_ip4):
		चयन (prog->expected_attach_type) अणु
		हाल BPF_CGROUP_UDP4_SENDMSG:
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
		अवरोध;
	हाल bpf_ctx_range_till(काष्ठा bpf_sock_addr, msg_src_ip6[0],
				msg_src_ip6[3]):
		चयन (prog->expected_attach_type) अणु
		हाल BPF_CGROUP_UDP6_SENDMSG:
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
		अवरोध;
	पूर्ण

	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा bpf_sock_addr, user_ip4):
	हाल bpf_ctx_range_till(काष्ठा bpf_sock_addr, user_ip6[0], user_ip6[3]):
	हाल bpf_ctx_range(काष्ठा bpf_sock_addr, msg_src_ip4):
	हाल bpf_ctx_range_till(काष्ठा bpf_sock_addr, msg_src_ip6[0],
				msg_src_ip6[3]):
	हाल bpf_ctx_range(काष्ठा bpf_sock_addr, user_port):
		अगर (type == BPF_READ) अणु
			bpf_ctx_record_field_size(info, size_शेष);

			अगर (bpf_ctx_wide_access_ok(off, size,
						   काष्ठा bpf_sock_addr,
						   user_ip6))
				वापस true;

			अगर (bpf_ctx_wide_access_ok(off, size,
						   काष्ठा bpf_sock_addr,
						   msg_src_ip6))
				वापस true;

			अगर (!bpf_ctx_narrow_access_ok(off, size, size_शेष))
				वापस false;
		पूर्ण अन्यथा अणु
			अगर (bpf_ctx_wide_access_ok(off, size,
						   काष्ठा bpf_sock_addr,
						   user_ip6))
				वापस true;

			अगर (bpf_ctx_wide_access_ok(off, size,
						   काष्ठा bpf_sock_addr,
						   msg_src_ip6))
				वापस true;

			अगर (size != size_शेष)
				वापस false;
		पूर्ण
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_addr, sk):
		अगर (type != BPF_READ)
			वापस false;
		अगर (size != माप(__u64))
			वापस false;
		info->reg_type = PTR_TO_SOCKET;
		अवरोध;
	शेष:
		अगर (type == BPF_READ) अणु
			अगर (size != size_शेष)
				वापस false;
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool sock_ops_is_valid_access(पूर्णांक off, पूर्णांक size,
				     क्रमागत bpf_access_type type,
				     स्थिर काष्ठा bpf_prog *prog,
				     काष्ठा bpf_insn_access_aux *info)
अणु
	स्थिर पूर्णांक size_शेष = माप(__u32);

	अगर (off < 0 || off >= माप(काष्ठा bpf_sock_ops))
		वापस false;

	/* The verअगरier guarantees that size > 0. */
	अगर (off % size != 0)
		वापस false;

	अगर (type == BPF_WRITE) अणु
		चयन (off) अणु
		हाल दुरत्व(काष्ठा bpf_sock_ops, reply):
		हाल दुरत्व(काष्ठा bpf_sock_ops, sk_txhash):
			अगर (size != size_शेष)
				वापस false;
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (off) अणु
		हाल bpf_ctx_range_till(काष्ठा bpf_sock_ops, bytes_received,
					bytes_acked):
			अगर (size != माप(__u64))
				वापस false;
			अवरोध;
		हाल दुरत्व(काष्ठा bpf_sock_ops, sk):
			अगर (size != माप(__u64))
				वापस false;
			info->reg_type = PTR_TO_SOCKET_OR_शून्य;
			अवरोध;
		हाल दुरत्व(काष्ठा bpf_sock_ops, skb_data):
			अगर (size != माप(__u64))
				वापस false;
			info->reg_type = PTR_TO_PACKET;
			अवरोध;
		हाल दुरत्व(काष्ठा bpf_sock_ops, skb_data_end):
			अगर (size != माप(__u64))
				वापस false;
			info->reg_type = PTR_TO_PACKET_END;
			अवरोध;
		हाल दुरत्व(काष्ठा bpf_sock_ops, skb_tcp_flags):
			bpf_ctx_record_field_size(info, size_शेष);
			वापस bpf_ctx_narrow_access_ok(off, size,
							size_शेष);
		शेष:
			अगर (size != size_शेष)
				वापस false;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक sk_skb_prologue(काष्ठा bpf_insn *insn_buf, bool direct_ग_लिखो,
			   स्थिर काष्ठा bpf_prog *prog)
अणु
	वापस bpf_unclone_prologue(insn_buf, direct_ग_लिखो, prog, SK_DROP);
पूर्ण

अटल bool sk_skb_is_valid_access(पूर्णांक off, पूर्णांक size,
				   क्रमागत bpf_access_type type,
				   स्थिर काष्ठा bpf_prog *prog,
				   काष्ठा bpf_insn_access_aux *info)
अणु
	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा __sk_buff, tc_classid):
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_meta):
	हाल bpf_ctx_range(काष्ठा __sk_buff, tstamp):
	हाल bpf_ctx_range(काष्ठा __sk_buff, wire_len):
		वापस false;
	पूर्ण

	अगर (type == BPF_WRITE) अणु
		चयन (off) अणु
		हाल bpf_ctx_range(काष्ठा __sk_buff, tc_index):
		हाल bpf_ctx_range(काष्ठा __sk_buff, priority):
			अवरोध;
		शेष:
			वापस false;
		पूर्ण
	पूर्ण

	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा __sk_buff, mark):
		वापस false;
	हाल bpf_ctx_range(काष्ठा __sk_buff, data):
		info->reg_type = PTR_TO_PACKET;
		अवरोध;
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_end):
		info->reg_type = PTR_TO_PACKET_END;
		अवरोध;
	पूर्ण

	वापस bpf_skb_is_valid_access(off, size, type, prog, info);
पूर्ण

अटल bool sk_msg_is_valid_access(पूर्णांक off, पूर्णांक size,
				   क्रमागत bpf_access_type type,
				   स्थिर काष्ठा bpf_prog *prog,
				   काष्ठा bpf_insn_access_aux *info)
अणु
	अगर (type == BPF_WRITE)
		वापस false;

	अगर (off % size != 0)
		वापस false;

	चयन (off) अणु
	हाल दुरत्व(काष्ठा sk_msg_md, data):
		info->reg_type = PTR_TO_PACKET;
		अगर (size != माप(__u64))
			वापस false;
		अवरोध;
	हाल दुरत्व(काष्ठा sk_msg_md, data_end):
		info->reg_type = PTR_TO_PACKET_END;
		अगर (size != माप(__u64))
			वापस false;
		अवरोध;
	हाल दुरत्व(काष्ठा sk_msg_md, sk):
		अगर (size != माप(__u64))
			वापस false;
		info->reg_type = PTR_TO_SOCKET;
		अवरोध;
	हाल bpf_ctx_range(काष्ठा sk_msg_md, family):
	हाल bpf_ctx_range(काष्ठा sk_msg_md, remote_ip4):
	हाल bpf_ctx_range(काष्ठा sk_msg_md, local_ip4):
	हाल bpf_ctx_range_till(काष्ठा sk_msg_md, remote_ip6[0], remote_ip6[3]):
	हाल bpf_ctx_range_till(काष्ठा sk_msg_md, local_ip6[0], local_ip6[3]):
	हाल bpf_ctx_range(काष्ठा sk_msg_md, remote_port):
	हाल bpf_ctx_range(काष्ठा sk_msg_md, local_port):
	हाल bpf_ctx_range(काष्ठा sk_msg_md, size):
		अगर (size != माप(__u32))
			वापस false;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool flow_dissector_is_valid_access(पूर्णांक off, पूर्णांक size,
					   क्रमागत bpf_access_type type,
					   स्थिर काष्ठा bpf_prog *prog,
					   काष्ठा bpf_insn_access_aux *info)
अणु
	स्थिर पूर्णांक size_शेष = माप(__u32);

	अगर (off < 0 || off >= माप(काष्ठा __sk_buff))
		वापस false;

	अगर (type == BPF_WRITE)
		वापस false;

	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा __sk_buff, data):
		अगर (size != size_शेष)
			वापस false;
		info->reg_type = PTR_TO_PACKET;
		वापस true;
	हाल bpf_ctx_range(काष्ठा __sk_buff, data_end):
		अगर (size != size_शेष)
			वापस false;
		info->reg_type = PTR_TO_PACKET_END;
		वापस true;
	हाल bpf_ctx_range_ptr(काष्ठा __sk_buff, flow_keys):
		अगर (size != माप(__u64))
			वापस false;
		info->reg_type = PTR_TO_FLOW_KEYS;
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल u32 flow_dissector_convert_ctx_access(क्रमागत bpf_access_type type,
					     स्थिर काष्ठा bpf_insn *si,
					     काष्ठा bpf_insn *insn_buf,
					     काष्ठा bpf_prog *prog,
					     u32 *target_size)

अणु
	काष्ठा bpf_insn *insn = insn_buf;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा __sk_buff, data):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_flow_dissector, data),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_flow_dissector, data));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, data_end):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_flow_dissector, data_end),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_flow_dissector, data_end));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, flow_keys):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_flow_dissector, flow_keys),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_flow_dissector, flow_keys));
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

अटल काष्ठा bpf_insn *bpf_convert_shinfo_access(स्थिर काष्ठा bpf_insn *si,
						  काष्ठा bpf_insn *insn)
अणु
	/* si->dst_reg = skb_shinfo(SKB); */
#अगर_घोषित NET_SKBUFF_DATA_USES_OFFSET
	*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, end),
			      BPF_REG_AX, si->src_reg,
			      दुरत्व(काष्ठा sk_buff, end));
	*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, head),
			      si->dst_reg, si->src_reg,
			      दुरत्व(काष्ठा sk_buff, head));
	*insn++ = BPF_ALU64_REG(BPF_ADD, si->dst_reg, BPF_REG_AX);
#अन्यथा
	*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, end),
			      si->dst_reg, si->src_reg,
			      दुरत्व(काष्ठा sk_buff, end));
#पूर्ण_अगर

	वापस insn;
पूर्ण

अटल u32 bpf_convert_ctx_access(क्रमागत bpf_access_type type,
				  स्थिर काष्ठा bpf_insn *si,
				  काष्ठा bpf_insn *insn_buf,
				  काष्ठा bpf_prog *prog, u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;
	पूर्णांक off;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा __sk_buff, len):
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg,
				      bpf_target_off(काष्ठा sk_buff, len, 4,
						     target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, protocol):
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->src_reg,
				      bpf_target_off(काष्ठा sk_buff, protocol, 2,
						     target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, vlan_proto):
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->src_reg,
				      bpf_target_off(काष्ठा sk_buff, vlan_proto, 2,
						     target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, priority):
		अगर (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_W, si->dst_reg, si->src_reg,
					      bpf_target_off(काष्ठा sk_buff, priority, 4,
							     target_size));
		अन्यथा
			*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg,
					      bpf_target_off(काष्ठा sk_buff, priority, 4,
							     target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, ingress_अगरindex):
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg,
				      bpf_target_off(काष्ठा sk_buff, skb_iअगर, 4,
						     target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, अगरindex):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, dev),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_buff, dev));
		*insn++ = BPF_JMP_IMM(BPF_JEQ, si->dst_reg, 0, 1);
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      bpf_target_off(काष्ठा net_device, अगरindex, 4,
						     target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, hash):
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg,
				      bpf_target_off(काष्ठा sk_buff, hash, 4,
						     target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, mark):
		अगर (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_W, si->dst_reg, si->src_reg,
					      bpf_target_off(काष्ठा sk_buff, mark, 4,
							     target_size));
		अन्यथा
			*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg,
					      bpf_target_off(काष्ठा sk_buff, mark, 4,
							     target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, pkt_type):
		*target_size = 1;
		*insn++ = BPF_LDX_MEM(BPF_B, si->dst_reg, si->src_reg,
				      PKT_TYPE_OFFSET());
		*insn++ = BPF_ALU32_IMM(BPF_AND, si->dst_reg, PKT_TYPE_MAX);
#अगर_घोषित __BIG_ENDIAN_BITFIELD
		*insn++ = BPF_ALU32_IMM(BPF_RSH, si->dst_reg, 5);
#पूर्ण_अगर
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, queue_mapping):
		अगर (type == BPF_WRITE) अणु
			*insn++ = BPF_JMP_IMM(BPF_JGE, si->src_reg, NO_QUEUE_MAPPING, 1);
			*insn++ = BPF_STX_MEM(BPF_H, si->dst_reg, si->src_reg,
					      bpf_target_off(काष्ठा sk_buff,
							     queue_mapping,
							     2, target_size));
		पूर्ण अन्यथा अणु
			*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->src_reg,
					      bpf_target_off(काष्ठा sk_buff,
							     queue_mapping,
							     2, target_size));
		पूर्ण
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, vlan_present):
		*target_size = 1;
		*insn++ = BPF_LDX_MEM(BPF_B, si->dst_reg, si->src_reg,
				      PKT_VLAN_PRESENT_OFFSET());
		अगर (PKT_VLAN_PRESENT_BIT)
			*insn++ = BPF_ALU32_IMM(BPF_RSH, si->dst_reg, PKT_VLAN_PRESENT_BIT);
		अगर (PKT_VLAN_PRESENT_BIT < 7)
			*insn++ = BPF_ALU32_IMM(BPF_AND, si->dst_reg, 1);
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, vlan_tci):
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->src_reg,
				      bpf_target_off(काष्ठा sk_buff, vlan_tci, 2,
						     target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, cb[0]) ...
	     दुरत्वend(काष्ठा __sk_buff, cb[4]) - 1:
		BUILD_BUG_ON(माप_field(काष्ठा qdisc_skb_cb, data) < 20);
		BUILD_BUG_ON((दुरत्व(काष्ठा sk_buff, cb) +
			      दुरत्व(काष्ठा qdisc_skb_cb, data)) %
			     माप(__u64));

		prog->cb_access = 1;
		off  = si->off;
		off -= दुरत्व(काष्ठा __sk_buff, cb[0]);
		off += दुरत्व(काष्ठा sk_buff, cb);
		off += दुरत्व(काष्ठा qdisc_skb_cb, data);
		अगर (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_SIZE(si->code), si->dst_reg,
					      si->src_reg, off);
		अन्यथा
			*insn++ = BPF_LDX_MEM(BPF_SIZE(si->code), si->dst_reg,
					      si->src_reg, off);
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, tc_classid):
		BUILD_BUG_ON(माप_field(काष्ठा qdisc_skb_cb, tc_classid) != 2);

		off  = si->off;
		off -= दुरत्व(काष्ठा __sk_buff, tc_classid);
		off += दुरत्व(काष्ठा sk_buff, cb);
		off += दुरत्व(काष्ठा qdisc_skb_cb, tc_classid);
		*target_size = 2;
		अगर (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_H, si->dst_reg,
					      si->src_reg, off);
		अन्यथा
			*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg,
					      si->src_reg, off);
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, data):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, data),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_buff, data));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, data_meta):
		off  = si->off;
		off -= दुरत्व(काष्ठा __sk_buff, data_meta);
		off += दुरत्व(काष्ठा sk_buff, cb);
		off += दुरत्व(काष्ठा bpf_skb_data_end, data_meta);
		*insn++ = BPF_LDX_MEM(BPF_SIZखातापूर्ण(व्योम *), si->dst_reg,
				      si->src_reg, off);
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, data_end):
		off  = si->off;
		off -= दुरत्व(काष्ठा __sk_buff, data_end);
		off += दुरत्व(काष्ठा sk_buff, cb);
		off += दुरत्व(काष्ठा bpf_skb_data_end, data_end);
		*insn++ = BPF_LDX_MEM(BPF_SIZखातापूर्ण(व्योम *), si->dst_reg,
				      si->src_reg, off);
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, tc_index):
#अगर_घोषित CONFIG_NET_SCHED
		अगर (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_H, si->dst_reg, si->src_reg,
					      bpf_target_off(काष्ठा sk_buff, tc_index, 2,
							     target_size));
		अन्यथा
			*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->src_reg,
					      bpf_target_off(काष्ठा sk_buff, tc_index, 2,
							     target_size));
#अन्यथा
		*target_size = 2;
		अगर (type == BPF_WRITE)
			*insn++ = BPF_MOV64_REG(si->dst_reg, si->dst_reg);
		अन्यथा
			*insn++ = BPF_MOV64_IMM(si->dst_reg, 0);
#पूर्ण_अगर
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, napi_id):
#अगर defined(CONFIG_NET_RX_BUSY_POLL)
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg,
				      bpf_target_off(काष्ठा sk_buff, napi_id, 4,
						     target_size));
		*insn++ = BPF_JMP_IMM(BPF_JGE, si->dst_reg, MIN_NAPI_ID, 1);
		*insn++ = BPF_MOV64_IMM(si->dst_reg, 0);
#अन्यथा
		*target_size = 4;
		*insn++ = BPF_MOV64_IMM(si->dst_reg, 0);
#पूर्ण_अगर
		अवरोध;
	हाल दुरत्व(काष्ठा __sk_buff, family):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common, skc_family) != 2);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_buff, sk));
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->dst_reg,
				      bpf_target_off(काष्ठा sock_common,
						     skc_family,
						     2, target_size));
		अवरोध;
	हाल दुरत्व(काष्ठा __sk_buff, remote_ip4):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common, skc_daddr) != 4);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_buff, sk));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      bpf_target_off(काष्ठा sock_common,
						     skc_daddr,
						     4, target_size));
		अवरोध;
	हाल दुरत्व(काष्ठा __sk_buff, local_ip4):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common,
					  skc_rcv_saddr) != 4);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_buff, sk));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      bpf_target_off(काष्ठा sock_common,
						     skc_rcv_saddr,
						     4, target_size));
		अवरोध;
	हाल दुरत्व(काष्ठा __sk_buff, remote_ip6[0]) ...
	     दुरत्व(काष्ठा __sk_buff, remote_ip6[3]):
#अगर IS_ENABLED(CONFIG_IPV6)
		BUILD_BUG_ON(माप_field(काष्ठा sock_common,
					  skc_v6_daddr.s6_addr32[0]) != 4);

		off = si->off;
		off -= दुरत्व(काष्ठा __sk_buff, remote_ip6[0]);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_buff, sk));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common,
					       skc_v6_daddr.s6_addr32[0]) +
				      off);
#अन्यथा
		*insn++ = BPF_MOV32_IMM(si->dst_reg, 0);
#पूर्ण_अगर
		अवरोध;
	हाल दुरत्व(काष्ठा __sk_buff, local_ip6[0]) ...
	     दुरत्व(काष्ठा __sk_buff, local_ip6[3]):
#अगर IS_ENABLED(CONFIG_IPV6)
		BUILD_BUG_ON(माप_field(काष्ठा sock_common,
					  skc_v6_rcv_saddr.s6_addr32[0]) != 4);

		off = si->off;
		off -= दुरत्व(काष्ठा __sk_buff, local_ip6[0]);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_buff, sk));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common,
					       skc_v6_rcv_saddr.s6_addr32[0]) +
				      off);
#अन्यथा
		*insn++ = BPF_MOV32_IMM(si->dst_reg, 0);
#पूर्ण_अगर
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, remote_port):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common, skc_dport) != 2);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_buff, sk));
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->dst_reg,
				      bpf_target_off(काष्ठा sock_common,
						     skc_dport,
						     2, target_size));
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
		*insn++ = BPF_ALU32_IMM(BPF_LSH, si->dst_reg, 16);
#पूर्ण_अगर
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, local_port):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common, skc_num) != 2);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_buff, sk));
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->dst_reg,
				      bpf_target_off(काष्ठा sock_common,
						     skc_num, 2, target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, tstamp):
		BUILD_BUG_ON(माप_field(काष्ठा sk_buff, tstamp) != 8);

		अगर (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_DW,
					      si->dst_reg, si->src_reg,
					      bpf_target_off(काष्ठा sk_buff,
							     tstamp, 8,
							     target_size));
		अन्यथा
			*insn++ = BPF_LDX_MEM(BPF_DW,
					      si->dst_reg, si->src_reg,
					      bpf_target_off(काष्ठा sk_buff,
							     tstamp, 8,
							     target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, gso_segs):
		insn = bpf_convert_shinfo_access(si, insn);
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा skb_shared_info, gso_segs),
				      si->dst_reg, si->dst_reg,
				      bpf_target_off(काष्ठा skb_shared_info,
						     gso_segs, 2,
						     target_size));
		अवरोध;
	हाल दुरत्व(काष्ठा __sk_buff, gso_size):
		insn = bpf_convert_shinfo_access(si, insn);
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा skb_shared_info, gso_size),
				      si->dst_reg, si->dst_reg,
				      bpf_target_off(काष्ठा skb_shared_info,
						     gso_size, 2,
						     target_size));
		अवरोध;
	हाल दुरत्व(काष्ठा __sk_buff, wire_len):
		BUILD_BUG_ON(माप_field(काष्ठा qdisc_skb_cb, pkt_len) != 4);

		off = si->off;
		off -= दुरत्व(काष्ठा __sk_buff, wire_len);
		off += दुरत्व(काष्ठा sk_buff, cb);
		off += दुरत्व(काष्ठा qdisc_skb_cb, pkt_len);
		*target_size = 4;
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg, off);
		अवरोध;

	हाल दुरत्व(काष्ठा __sk_buff, sk):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_buff, sk));
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

u32 bpf_sock_convert_ctx_access(क्रमागत bpf_access_type type,
				स्थिर काष्ठा bpf_insn *si,
				काष्ठा bpf_insn *insn_buf,
				काष्ठा bpf_prog *prog, u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;
	पूर्णांक off;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा bpf_sock, bound_dev_अगर):
		BUILD_BUG_ON(माप_field(काष्ठा sock, sk_bound_dev_अगर) != 4);

		अगर (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_W, si->dst_reg, si->src_reg,
					दुरत्व(काष्ठा sock, sk_bound_dev_अगर));
		अन्यथा
			*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sock, sk_bound_dev_अगर));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock, mark):
		BUILD_BUG_ON(माप_field(काष्ठा sock, sk_mark) != 4);

		अगर (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_W, si->dst_reg, si->src_reg,
					दुरत्व(काष्ठा sock, sk_mark));
		अन्यथा
			*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sock, sk_mark));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock, priority):
		BUILD_BUG_ON(माप_field(काष्ठा sock, sk_priority) != 4);

		अगर (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_W, si->dst_reg, si->src_reg,
					दुरत्व(काष्ठा sock, sk_priority));
		अन्यथा
			*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sock, sk_priority));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock, family):
		*insn++ = BPF_LDX_MEM(
			BPF_FIELD_SIZखातापूर्ण(काष्ठा sock_common, skc_family),
			si->dst_reg, si->src_reg,
			bpf_target_off(काष्ठा sock_common,
				       skc_family,
				       माप_field(काष्ठा sock_common,
						    skc_family),
				       target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock, type):
		*insn++ = BPF_LDX_MEM(
			BPF_FIELD_SIZखातापूर्ण(काष्ठा sock, sk_type),
			si->dst_reg, si->src_reg,
			bpf_target_off(काष्ठा sock, sk_type,
				       माप_field(काष्ठा sock, sk_type),
				       target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock, protocol):
		*insn++ = BPF_LDX_MEM(
			BPF_FIELD_SIZखातापूर्ण(काष्ठा sock, sk_protocol),
			si->dst_reg, si->src_reg,
			bpf_target_off(काष्ठा sock, sk_protocol,
				       माप_field(काष्ठा sock, sk_protocol),
				       target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock, src_ip4):
		*insn++ = BPF_LDX_MEM(
			BPF_SIZE(si->code), si->dst_reg, si->src_reg,
			bpf_target_off(काष्ठा sock_common, skc_rcv_saddr,
				       माप_field(काष्ठा sock_common,
						    skc_rcv_saddr),
				       target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock, dst_ip4):
		*insn++ = BPF_LDX_MEM(
			BPF_SIZE(si->code), si->dst_reg, si->src_reg,
			bpf_target_off(काष्ठा sock_common, skc_daddr,
				       माप_field(काष्ठा sock_common,
						    skc_daddr),
				       target_size));
		अवरोध;

	हाल bpf_ctx_range_till(काष्ठा bpf_sock, src_ip6[0], src_ip6[3]):
#अगर IS_ENABLED(CONFIG_IPV6)
		off = si->off;
		off -= दुरत्व(काष्ठा bpf_sock, src_ip6[0]);
		*insn++ = BPF_LDX_MEM(
			BPF_SIZE(si->code), si->dst_reg, si->src_reg,
			bpf_target_off(
				काष्ठा sock_common,
				skc_v6_rcv_saddr.s6_addr32[0],
				माप_field(काष्ठा sock_common,
					     skc_v6_rcv_saddr.s6_addr32[0]),
				target_size) + off);
#अन्यथा
		(व्योम)off;
		*insn++ = BPF_MOV32_IMM(si->dst_reg, 0);
#पूर्ण_अगर
		अवरोध;

	हाल bpf_ctx_range_till(काष्ठा bpf_sock, dst_ip6[0], dst_ip6[3]):
#अगर IS_ENABLED(CONFIG_IPV6)
		off = si->off;
		off -= दुरत्व(काष्ठा bpf_sock, dst_ip6[0]);
		*insn++ = BPF_LDX_MEM(
			BPF_SIZE(si->code), si->dst_reg, si->src_reg,
			bpf_target_off(काष्ठा sock_common,
				       skc_v6_daddr.s6_addr32[0],
				       माप_field(काष्ठा sock_common,
						    skc_v6_daddr.s6_addr32[0]),
				       target_size) + off);
#अन्यथा
		*insn++ = BPF_MOV32_IMM(si->dst_reg, 0);
		*target_size = 4;
#पूर्ण_अगर
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock, src_port):
		*insn++ = BPF_LDX_MEM(
			BPF_FIELD_SIZखातापूर्ण(काष्ठा sock_common, skc_num),
			si->dst_reg, si->src_reg,
			bpf_target_off(काष्ठा sock_common, skc_num,
				       माप_field(काष्ठा sock_common,
						    skc_num),
				       target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock, dst_port):
		*insn++ = BPF_LDX_MEM(
			BPF_FIELD_SIZखातापूर्ण(काष्ठा sock_common, skc_dport),
			si->dst_reg, si->src_reg,
			bpf_target_off(काष्ठा sock_common, skc_dport,
				       माप_field(काष्ठा sock_common,
						    skc_dport),
				       target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock, state):
		*insn++ = BPF_LDX_MEM(
			BPF_FIELD_SIZखातापूर्ण(काष्ठा sock_common, skc_state),
			si->dst_reg, si->src_reg,
			bpf_target_off(काष्ठा sock_common, skc_state,
				       माप_field(काष्ठा sock_common,
						    skc_state),
				       target_size));
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock, rx_queue_mapping):
#अगर_घोषित CONFIG_SOCK_RX_QUEUE_MAPPING
		*insn++ = BPF_LDX_MEM(
			BPF_FIELD_SIZखातापूर्ण(काष्ठा sock, sk_rx_queue_mapping),
			si->dst_reg, si->src_reg,
			bpf_target_off(काष्ठा sock, sk_rx_queue_mapping,
				       माप_field(काष्ठा sock,
						    sk_rx_queue_mapping),
				       target_size));
		*insn++ = BPF_JMP_IMM(BPF_JNE, si->dst_reg, NO_QUEUE_MAPPING,
				      1);
		*insn++ = BPF_MOV64_IMM(si->dst_reg, -1);
#अन्यथा
		*insn++ = BPF_MOV64_IMM(si->dst_reg, -1);
		*target_size = 2;
#पूर्ण_अगर
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

अटल u32 tc_cls_act_convert_ctx_access(क्रमागत bpf_access_type type,
					 स्थिर काष्ठा bpf_insn *si,
					 काष्ठा bpf_insn *insn_buf,
					 काष्ठा bpf_prog *prog, u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा __sk_buff, अगरindex):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, dev),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_buff, dev));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      bpf_target_off(काष्ठा net_device, अगरindex, 4,
						     target_size));
		अवरोध;
	शेष:
		वापस bpf_convert_ctx_access(type, si, insn_buf, prog,
					      target_size);
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

अटल u32 xdp_convert_ctx_access(क्रमागत bpf_access_type type,
				  स्थिर काष्ठा bpf_insn *si,
				  काष्ठा bpf_insn *insn_buf,
				  काष्ठा bpf_prog *prog, u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा xdp_md, data):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा xdp_buff, data),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा xdp_buff, data));
		अवरोध;
	हाल दुरत्व(काष्ठा xdp_md, data_meta):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा xdp_buff, data_meta),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा xdp_buff, data_meta));
		अवरोध;
	हाल दुरत्व(काष्ठा xdp_md, data_end):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा xdp_buff, data_end),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा xdp_buff, data_end));
		अवरोध;
	हाल दुरत्व(काष्ठा xdp_md, ingress_अगरindex):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा xdp_buff, rxq),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा xdp_buff, rxq));
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा xdp_rxq_info, dev),
				      si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा xdp_rxq_info, dev));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा net_device, अगरindex));
		अवरोध;
	हाल दुरत्व(काष्ठा xdp_md, rx_queue_index):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा xdp_buff, rxq),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा xdp_buff, rxq));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा xdp_rxq_info,
					       queue_index));
		अवरोध;
	हाल दुरत्व(काष्ठा xdp_md, egress_अगरindex):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा xdp_buff, txq),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा xdp_buff, txq));
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा xdp_txq_info, dev),
				      si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा xdp_txq_info, dev));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा net_device, अगरindex));
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

/* SOCK_ADDR_LOAD_NESTED_FIELD() loads Nested Field S.F.NF where S is type of
 * context Structure, F is Field in context काष्ठाure that contains a poपूर्णांकer
 * to Nested Structure of type NS that has the field NF.
 *
 * SIZE encodes the load size (BPF_B, BPF_H, etc). It's up to caller to make
 * sure that SIZE is not greater than actual size of S.F.NF.
 *
 * If offset OFF is provided, the load happens from that offset relative to
 * offset of NF.
 */
#घोषणा SOCK_ADDR_LOAD_NESTED_FIELD_SIZE_OFF(S, NS, F, NF, SIZE, OFF)	       \
	करो अणु								       \
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(S, F), si->dst_reg,     \
				      si->src_reg, दुरत्व(S, F));	       \
		*insn++ = BPF_LDX_MEM(					       \
			SIZE, si->dst_reg, si->dst_reg,			       \
			bpf_target_off(NS, NF, माप_field(NS, NF),	       \
				       target_size)			       \
				+ OFF);					       \
	पूर्ण जबतक (0)

#घोषणा SOCK_ADDR_LOAD_NESTED_FIELD(S, NS, F, NF)			       \
	SOCK_ADDR_LOAD_NESTED_FIELD_SIZE_OFF(S, NS, F, NF,		       \
					     BPF_FIELD_SIZखातापूर्ण(NS, NF), 0)

/* SOCK_ADDR_STORE_NESTED_FIELD_OFF() has semantic similar to
 * SOCK_ADDR_LOAD_NESTED_FIELD_SIZE_OFF() but क्रम store operation.
 *
 * In addition it uses Temporary Field TF (member of काष्ठा S) as the 3rd
 * "register" since two रेजिस्टरs available in convert_ctx_access are not
 * enough: we can't override neither SRC, since it contains value to store, nor
 * DST since it contains poपूर्णांकer to context that may be used by later
 * inकाष्ठाions. But we need a temporary place to save poपूर्णांकer to nested
 * काष्ठाure whose field we want to store to.
 */
#घोषणा SOCK_ADDR_STORE_NESTED_FIELD_OFF(S, NS, F, NF, SIZE, OFF, TF)	       \
	करो अणु								       \
		पूर्णांक पंचांगp_reg = BPF_REG_9;				       \
		अगर (si->src_reg == पंचांगp_reg || si->dst_reg == पंचांगp_reg)	       \
			--पंचांगp_reg;					       \
		अगर (si->src_reg == पंचांगp_reg || si->dst_reg == पंचांगp_reg)	       \
			--पंचांगp_reg;					       \
		*insn++ = BPF_STX_MEM(BPF_DW, si->dst_reg, पंचांगp_reg,	       \
				      दुरत्व(S, TF));			       \
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(S, F), पंचांगp_reg,	       \
				      si->dst_reg, दुरत्व(S, F));	       \
		*insn++ = BPF_STX_MEM(SIZE, पंचांगp_reg, si->src_reg,	       \
			bpf_target_off(NS, NF, माप_field(NS, NF),	       \
				       target_size)			       \
				+ OFF);					       \
		*insn++ = BPF_LDX_MEM(BPF_DW, पंचांगp_reg, si->dst_reg,	       \
				      दुरत्व(S, TF));			       \
	पूर्ण जबतक (0)

#घोषणा SOCK_ADDR_LOAD_OR_STORE_NESTED_FIELD_SIZE_OFF(S, NS, F, NF, SIZE, OFF, \
						      TF)		       \
	करो अणु								       \
		अगर (type == BPF_WRITE) अणु				       \
			SOCK_ADDR_STORE_NESTED_FIELD_OFF(S, NS, F, NF, SIZE,   \
							 OFF, TF);	       \
		पूर्ण अन्यथा अणु						       \
			SOCK_ADDR_LOAD_NESTED_FIELD_SIZE_OFF(		       \
				S, NS, F, NF, SIZE, OFF);  \
		पूर्ण							       \
	पूर्ण जबतक (0)

#घोषणा SOCK_ADDR_LOAD_OR_STORE_NESTED_FIELD(S, NS, F, NF, TF)		       \
	SOCK_ADDR_LOAD_OR_STORE_NESTED_FIELD_SIZE_OFF(			       \
		S, NS, F, NF, BPF_FIELD_SIZखातापूर्ण(NS, NF), 0, TF)

अटल u32 sock_addr_convert_ctx_access(क्रमागत bpf_access_type type,
					स्थिर काष्ठा bpf_insn *si,
					काष्ठा bpf_insn *insn_buf,
					काष्ठा bpf_prog *prog, u32 *target_size)
अणु
	पूर्णांक off, port_size = माप_field(काष्ठा sockaddr_in6, sin6_port);
	काष्ठा bpf_insn *insn = insn_buf;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा bpf_sock_addr, user_family):
		SOCK_ADDR_LOAD_NESTED_FIELD(काष्ठा bpf_sock_addr_kern,
					    काष्ठा sockaddr, uaddr, sa_family);
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_addr, user_ip4):
		SOCK_ADDR_LOAD_OR_STORE_NESTED_FIELD_SIZE_OFF(
			काष्ठा bpf_sock_addr_kern, काष्ठा sockaddr_in, uaddr,
			sin_addr, BPF_SIZE(si->code), 0, पंचांगp_reg);
		अवरोध;

	हाल bpf_ctx_range_till(काष्ठा bpf_sock_addr, user_ip6[0], user_ip6[3]):
		off = si->off;
		off -= दुरत्व(काष्ठा bpf_sock_addr, user_ip6[0]);
		SOCK_ADDR_LOAD_OR_STORE_NESTED_FIELD_SIZE_OFF(
			काष्ठा bpf_sock_addr_kern, काष्ठा sockaddr_in6, uaddr,
			sin6_addr.s6_addr32[0], BPF_SIZE(si->code), off,
			पंचांगp_reg);
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_addr, user_port):
		/* To get port we need to know sa_family first and then treat
		 * sockaddr as either sockaddr_in or sockaddr_in6.
		 * Though we can simplअगरy since port field has same offset and
		 * size in both काष्ठाures.
		 * Here we check this invariant and use just one of the
		 * काष्ठाures अगर it's true.
		 */
		BUILD_BUG_ON(दुरत्व(काष्ठा sockaddr_in, sin_port) !=
			     दुरत्व(काष्ठा sockaddr_in6, sin6_port));
		BUILD_BUG_ON(माप_field(काष्ठा sockaddr_in, sin_port) !=
			     माप_field(काष्ठा sockaddr_in6, sin6_port));
		/* Account क्रम sin6_port being smaller than user_port. */
		port_size = min(port_size, BPF_LDST_BYTES(si));
		SOCK_ADDR_LOAD_OR_STORE_NESTED_FIELD_SIZE_OFF(
			काष्ठा bpf_sock_addr_kern, काष्ठा sockaddr_in6, uaddr,
			sin6_port, bytes_to_bpf_size(port_size), 0, पंचांगp_reg);
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_addr, family):
		SOCK_ADDR_LOAD_NESTED_FIELD(काष्ठा bpf_sock_addr_kern,
					    काष्ठा sock, sk, sk_family);
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_addr, type):
		SOCK_ADDR_LOAD_NESTED_FIELD(काष्ठा bpf_sock_addr_kern,
					    काष्ठा sock, sk, sk_type);
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_addr, protocol):
		SOCK_ADDR_LOAD_NESTED_FIELD(काष्ठा bpf_sock_addr_kern,
					    काष्ठा sock, sk, sk_protocol);
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_addr, msg_src_ip4):
		/* Treat t_ctx as काष्ठा in_addr क्रम msg_src_ip4. */
		SOCK_ADDR_LOAD_OR_STORE_NESTED_FIELD_SIZE_OFF(
			काष्ठा bpf_sock_addr_kern, काष्ठा in_addr, t_ctx,
			s_addr, BPF_SIZE(si->code), 0, पंचांगp_reg);
		अवरोध;

	हाल bpf_ctx_range_till(काष्ठा bpf_sock_addr, msg_src_ip6[0],
				msg_src_ip6[3]):
		off = si->off;
		off -= दुरत्व(काष्ठा bpf_sock_addr, msg_src_ip6[0]);
		/* Treat t_ctx as काष्ठा in6_addr क्रम msg_src_ip6. */
		SOCK_ADDR_LOAD_OR_STORE_NESTED_FIELD_SIZE_OFF(
			काष्ठा bpf_sock_addr_kern, काष्ठा in6_addr, t_ctx,
			s6_addr32[0], BPF_SIZE(si->code), off, पंचांगp_reg);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_addr, sk):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_sock_addr_kern, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_addr_kern, sk));
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

अटल u32 sock_ops_convert_ctx_access(क्रमागत bpf_access_type type,
				       स्थिर काष्ठा bpf_insn *si,
				       काष्ठा bpf_insn *insn_buf,
				       काष्ठा bpf_prog *prog,
				       u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;
	पूर्णांक off;

/* Helper macro क्रम adding पढ़ो access to tcp_sock or sock fields. */
#घोषणा SOCK_OPS_GET_FIELD(BPF_FIELD, OBJ_FIELD, OBJ)			      \
	करो अणु								      \
		पूर्णांक fullsock_reg = si->dst_reg, reg = BPF_REG_9, jmp = 2;     \
		BUILD_BUG_ON(माप_field(OBJ, OBJ_FIELD) >		      \
			     माप_field(काष्ठा bpf_sock_ops, BPF_FIELD));   \
		अगर (si->dst_reg == reg || si->src_reg == reg)		      \
			reg--;						      \
		अगर (si->dst_reg == reg || si->src_reg == reg)		      \
			reg--;						      \
		अगर (si->dst_reg == si->src_reg) अणु			      \
			*insn++ = BPF_STX_MEM(BPF_DW, si->src_reg, reg,	      \
					  दुरत्व(काष्ठा bpf_sock_ops_kern,  \
					  temp));			      \
			fullsock_reg = reg;				      \
			jmp += 2;					      \
		पूर्ण							      \
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(			      \
						काष्ठा bpf_sock_ops_kern,     \
						is_fullsock),		      \
				      fullsock_reg, si->src_reg,	      \
				      दुरत्व(काष्ठा bpf_sock_ops_kern,      \
					       is_fullsock));		      \
		*insn++ = BPF_JMP_IMM(BPF_JEQ, fullsock_reg, 0, jmp);	      \
		अगर (si->dst_reg == si->src_reg)				      \
			*insn++ = BPF_LDX_MEM(BPF_DW, reg, si->src_reg,	      \
				      दुरत्व(काष्ठा bpf_sock_ops_kern,      \
				      temp));				      \
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(			      \
						काष्ठा bpf_sock_ops_kern, sk),\
				      si->dst_reg, si->src_reg,		      \
				      दुरत्व(काष्ठा bpf_sock_ops_kern, sk));\
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(OBJ,		      \
						       OBJ_FIELD),	      \
				      si->dst_reg, si->dst_reg,		      \
				      दुरत्व(OBJ, OBJ_FIELD));	      \
		अगर (si->dst_reg == si->src_reg)	अणु			      \
			*insn++ = BPF_JMP_A(1);				      \
			*insn++ = BPF_LDX_MEM(BPF_DW, reg, si->src_reg,	      \
				      दुरत्व(काष्ठा bpf_sock_ops_kern,      \
				      temp));				      \
		पूर्ण							      \
	पूर्ण जबतक (0)

#घोषणा SOCK_OPS_GET_SK()							      \
	करो अणु								      \
		पूर्णांक fullsock_reg = si->dst_reg, reg = BPF_REG_9, jmp = 1;     \
		अगर (si->dst_reg == reg || si->src_reg == reg)		      \
			reg--;						      \
		अगर (si->dst_reg == reg || si->src_reg == reg)		      \
			reg--;						      \
		अगर (si->dst_reg == si->src_reg) अणु			      \
			*insn++ = BPF_STX_MEM(BPF_DW, si->src_reg, reg,	      \
					  दुरत्व(काष्ठा bpf_sock_ops_kern,  \
					  temp));			      \
			fullsock_reg = reg;				      \
			jmp += 2;					      \
		पूर्ण							      \
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(			      \
						काष्ठा bpf_sock_ops_kern,     \
						is_fullsock),		      \
				      fullsock_reg, si->src_reg,	      \
				      दुरत्व(काष्ठा bpf_sock_ops_kern,      \
					       is_fullsock));		      \
		*insn++ = BPF_JMP_IMM(BPF_JEQ, fullsock_reg, 0, jmp);	      \
		अगर (si->dst_reg == si->src_reg)				      \
			*insn++ = BPF_LDX_MEM(BPF_DW, reg, si->src_reg,	      \
				      दुरत्व(काष्ठा bpf_sock_ops_kern,      \
				      temp));				      \
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(			      \
						काष्ठा bpf_sock_ops_kern, sk),\
				      si->dst_reg, si->src_reg,		      \
				      दुरत्व(काष्ठा bpf_sock_ops_kern, sk));\
		अगर (si->dst_reg == si->src_reg)	अणु			      \
			*insn++ = BPF_JMP_A(1);				      \
			*insn++ = BPF_LDX_MEM(BPF_DW, reg, si->src_reg,	      \
				      दुरत्व(काष्ठा bpf_sock_ops_kern,      \
				      temp));				      \
		पूर्ण							      \
	पूर्ण जबतक (0)

#घोषणा SOCK_OPS_GET_TCP_SOCK_FIELD(FIELD) \
		SOCK_OPS_GET_FIELD(FIELD, FIELD, काष्ठा tcp_sock)

/* Helper macro क्रम adding ग_लिखो access to tcp_sock or sock fields.
 * The macro is called with two रेजिस्टरs, dst_reg which contains a poपूर्णांकer
 * to ctx (context) and src_reg which contains the value that should be
 * stored. However, we need an additional रेजिस्टर since we cannot overग_लिखो
 * dst_reg because it may be used later in the program.
 * Instead we "borrow" one of the other रेजिस्टर. We first save its value
 * पूर्णांकo a new (temp) field in bpf_sock_ops_kern, use it, and then restore
 * it at the end of the macro.
 */
#घोषणा SOCK_OPS_SET_FIELD(BPF_FIELD, OBJ_FIELD, OBJ)			      \
	करो अणु								      \
		पूर्णांक reg = BPF_REG_9;					      \
		BUILD_BUG_ON(माप_field(OBJ, OBJ_FIELD) >		      \
			     माप_field(काष्ठा bpf_sock_ops, BPF_FIELD));   \
		अगर (si->dst_reg == reg || si->src_reg == reg)		      \
			reg--;						      \
		अगर (si->dst_reg == reg || si->src_reg == reg)		      \
			reg--;						      \
		*insn++ = BPF_STX_MEM(BPF_DW, si->dst_reg, reg,		      \
				      दुरत्व(काष्ठा bpf_sock_ops_kern,      \
					       temp));			      \
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(			      \
						काष्ठा bpf_sock_ops_kern,     \
						is_fullsock),		      \
				      reg, si->dst_reg,			      \
				      दुरत्व(काष्ठा bpf_sock_ops_kern,      \
					       is_fullsock));		      \
		*insn++ = BPF_JMP_IMM(BPF_JEQ, reg, 0, 2);		      \
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(			      \
						काष्ठा bpf_sock_ops_kern, sk),\
				      reg, si->dst_reg,			      \
				      दुरत्व(काष्ठा bpf_sock_ops_kern, sk));\
		*insn++ = BPF_STX_MEM(BPF_FIELD_SIZखातापूर्ण(OBJ, OBJ_FIELD),	      \
				      reg, si->src_reg,			      \
				      दुरत्व(OBJ, OBJ_FIELD));	      \
		*insn++ = BPF_LDX_MEM(BPF_DW, reg, si->dst_reg,		      \
				      दुरत्व(काष्ठा bpf_sock_ops_kern,      \
					       temp));			      \
	पूर्ण जबतक (0)

#घोषणा SOCK_OPS_GET_OR_SET_FIELD(BPF_FIELD, OBJ_FIELD, OBJ, TYPE)	      \
	करो अणु								      \
		अगर (TYPE == BPF_WRITE)					      \
			SOCK_OPS_SET_FIELD(BPF_FIELD, OBJ_FIELD, OBJ);	      \
		अन्यथा							      \
			SOCK_OPS_GET_FIELD(BPF_FIELD, OBJ_FIELD, OBJ);	      \
	पूर्ण जबतक (0)

	अगर (insn > insn_buf)
		वापस insn - insn_buf;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा bpf_sock_ops, op):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_sock_ops_kern,
						       op),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern, op));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_ops, replyदीर्घ[0]) ...
	     दुरत्व(काष्ठा bpf_sock_ops, replyदीर्घ[3]):
		BUILD_BUG_ON(माप_field(काष्ठा bpf_sock_ops, reply) !=
			     माप_field(काष्ठा bpf_sock_ops_kern, reply));
		BUILD_BUG_ON(माप_field(काष्ठा bpf_sock_ops, replyदीर्घ) !=
			     माप_field(काष्ठा bpf_sock_ops_kern, replyदीर्घ));
		off = si->off;
		off -= दुरत्व(काष्ठा bpf_sock_ops, replyदीर्घ[0]);
		off += दुरत्व(काष्ठा bpf_sock_ops_kern, replyदीर्घ[0]);
		अगर (type == BPF_WRITE)
			*insn++ = BPF_STX_MEM(BPF_W, si->dst_reg, si->src_reg,
					      off);
		अन्यथा
			*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg,
					      off);
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_ops, family):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common, skc_family) != 2);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
					      काष्ठा bpf_sock_ops_kern, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern, sk));
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common, skc_family));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_ops, remote_ip4):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common, skc_daddr) != 4);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
						काष्ठा bpf_sock_ops_kern, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern, sk));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common, skc_daddr));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_ops, local_ip4):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common,
					  skc_rcv_saddr) != 4);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
					      काष्ठा bpf_sock_ops_kern, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern, sk));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common,
					       skc_rcv_saddr));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_ops, remote_ip6[0]) ...
	     दुरत्व(काष्ठा bpf_sock_ops, remote_ip6[3]):
#अगर IS_ENABLED(CONFIG_IPV6)
		BUILD_BUG_ON(माप_field(काष्ठा sock_common,
					  skc_v6_daddr.s6_addr32[0]) != 4);

		off = si->off;
		off -= दुरत्व(काष्ठा bpf_sock_ops, remote_ip6[0]);
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
						काष्ठा bpf_sock_ops_kern, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern, sk));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common,
					       skc_v6_daddr.s6_addr32[0]) +
				      off);
#अन्यथा
		*insn++ = BPF_MOV32_IMM(si->dst_reg, 0);
#पूर्ण_अगर
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_ops, local_ip6[0]) ...
	     दुरत्व(काष्ठा bpf_sock_ops, local_ip6[3]):
#अगर IS_ENABLED(CONFIG_IPV6)
		BUILD_BUG_ON(माप_field(काष्ठा sock_common,
					  skc_v6_rcv_saddr.s6_addr32[0]) != 4);

		off = si->off;
		off -= दुरत्व(काष्ठा bpf_sock_ops, local_ip6[0]);
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
						काष्ठा bpf_sock_ops_kern, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern, sk));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common,
					       skc_v6_rcv_saddr.s6_addr32[0]) +
				      off);
#अन्यथा
		*insn++ = BPF_MOV32_IMM(si->dst_reg, 0);
#पूर्ण_अगर
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_ops, remote_port):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common, skc_dport) != 2);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
						काष्ठा bpf_sock_ops_kern, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern, sk));
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common, skc_dport));
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
		*insn++ = BPF_ALU32_IMM(BPF_LSH, si->dst_reg, 16);
#पूर्ण_अगर
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_ops, local_port):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common, skc_num) != 2);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
						काष्ठा bpf_sock_ops_kern, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern, sk));
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common, skc_num));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_ops, is_fullsock):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
						काष्ठा bpf_sock_ops_kern,
						is_fullsock),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern,
					       is_fullsock));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_ops, state):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common, skc_state) != 1);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
						काष्ठा bpf_sock_ops_kern, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern, sk));
		*insn++ = BPF_LDX_MEM(BPF_B, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common, skc_state));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_ops, rtt_min):
		BUILD_BUG_ON(माप_field(काष्ठा tcp_sock, rtt_min) !=
			     माप(काष्ठा minmax));
		BUILD_BUG_ON(माप(काष्ठा minmax) <
			     माप(काष्ठा minmax_sample));

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
						काष्ठा bpf_sock_ops_kern, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern, sk));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा tcp_sock, rtt_min) +
				      माप_field(काष्ठा minmax_sample, t));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_ops, bpf_sock_ops_cb_flags):
		SOCK_OPS_GET_FIELD(bpf_sock_ops_cb_flags, bpf_sock_ops_cb_flags,
				   काष्ठा tcp_sock);
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sock_ops, sk_txhash):
		SOCK_OPS_GET_OR_SET_FIELD(sk_txhash, sk_txhash,
					  काष्ठा sock, type);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, snd_cwnd):
		SOCK_OPS_GET_TCP_SOCK_FIELD(snd_cwnd);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, srtt_us):
		SOCK_OPS_GET_TCP_SOCK_FIELD(srtt_us);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, snd_ssthresh):
		SOCK_OPS_GET_TCP_SOCK_FIELD(snd_ssthresh);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, rcv_nxt):
		SOCK_OPS_GET_TCP_SOCK_FIELD(rcv_nxt);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, snd_nxt):
		SOCK_OPS_GET_TCP_SOCK_FIELD(snd_nxt);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, snd_una):
		SOCK_OPS_GET_TCP_SOCK_FIELD(snd_una);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, mss_cache):
		SOCK_OPS_GET_TCP_SOCK_FIELD(mss_cache);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, ecn_flags):
		SOCK_OPS_GET_TCP_SOCK_FIELD(ecn_flags);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, rate_delivered):
		SOCK_OPS_GET_TCP_SOCK_FIELD(rate_delivered);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, rate_पूर्णांकerval_us):
		SOCK_OPS_GET_TCP_SOCK_FIELD(rate_पूर्णांकerval_us);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, packets_out):
		SOCK_OPS_GET_TCP_SOCK_FIELD(packets_out);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, retrans_out):
		SOCK_OPS_GET_TCP_SOCK_FIELD(retrans_out);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, total_retrans):
		SOCK_OPS_GET_TCP_SOCK_FIELD(total_retrans);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, segs_in):
		SOCK_OPS_GET_TCP_SOCK_FIELD(segs_in);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, data_segs_in):
		SOCK_OPS_GET_TCP_SOCK_FIELD(data_segs_in);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, segs_out):
		SOCK_OPS_GET_TCP_SOCK_FIELD(segs_out);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, data_segs_out):
		SOCK_OPS_GET_TCP_SOCK_FIELD(data_segs_out);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, lost_out):
		SOCK_OPS_GET_TCP_SOCK_FIELD(lost_out);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, sacked_out):
		SOCK_OPS_GET_TCP_SOCK_FIELD(sacked_out);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, bytes_received):
		SOCK_OPS_GET_TCP_SOCK_FIELD(bytes_received);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, bytes_acked):
		SOCK_OPS_GET_TCP_SOCK_FIELD(bytes_acked);
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, sk):
		SOCK_OPS_GET_SK();
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, skb_data_end):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_sock_ops_kern,
						       skb_data_end),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern,
					       skb_data_end));
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, skb_data):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_sock_ops_kern,
						       skb),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern,
					       skb));
		*insn++ = BPF_JMP_IMM(BPF_JEQ, si->dst_reg, 0, 1);
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, data),
				      si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sk_buff, data));
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, skb_len):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_sock_ops_kern,
						       skb),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern,
					       skb));
		*insn++ = BPF_JMP_IMM(BPF_JEQ, si->dst_reg, 0, 1);
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, len),
				      si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sk_buff, len));
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_sock_ops, skb_tcp_flags):
		off = दुरत्व(काष्ठा sk_buff, cb);
		off += दुरत्व(काष्ठा tcp_skb_cb, tcp_flags);
		*target_size = माप_field(काष्ठा tcp_skb_cb, tcp_flags);
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_sock_ops_kern,
						       skb),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sock_ops_kern,
					       skb));
		*insn++ = BPF_JMP_IMM(BPF_JEQ, si->dst_reg, 0, 1);
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा tcp_skb_cb,
						       tcp_flags),
				      si->dst_reg, si->dst_reg, off);
		अवरोध;
	पूर्ण
	वापस insn - insn_buf;
पूर्ण

/* data_end = skb->data + skb_headlen() */
अटल काष्ठा bpf_insn *bpf_convert_data_end_access(स्थिर काष्ठा bpf_insn *si,
						    काष्ठा bpf_insn *insn)
अणु
	/* si->dst_reg = skb->data */
	*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, data),
			      si->dst_reg, si->src_reg,
			      दुरत्व(काष्ठा sk_buff, data));
	/* AX = skb->len */
	*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, len),
			      BPF_REG_AX, si->src_reg,
			      दुरत्व(काष्ठा sk_buff, len));
	/* si->dst_reg = skb->data + skb->len */
	*insn++ = BPF_ALU64_REG(BPF_ADD, si->dst_reg, BPF_REG_AX);
	/* AX = skb->data_len */
	*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_buff, data_len),
			      BPF_REG_AX, si->src_reg,
			      दुरत्व(काष्ठा sk_buff, data_len));
	/* si->dst_reg = skb->data + skb->len - skb->data_len */
	*insn++ = BPF_ALU64_REG(BPF_SUB, si->dst_reg, BPF_REG_AX);

	वापस insn;
पूर्ण

अटल u32 sk_skb_convert_ctx_access(क्रमागत bpf_access_type type,
				     स्थिर काष्ठा bpf_insn *si,
				     काष्ठा bpf_insn *insn_buf,
				     काष्ठा bpf_prog *prog, u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा __sk_buff, data_end):
		insn = bpf_convert_data_end_access(si, insn);
		अवरोध;
	शेष:
		वापस bpf_convert_ctx_access(type, si, insn_buf, prog,
					      target_size);
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

अटल u32 sk_msg_convert_ctx_access(क्रमागत bpf_access_type type,
				     स्थिर काष्ठा bpf_insn *si,
				     काष्ठा bpf_insn *insn_buf,
				     काष्ठा bpf_prog *prog, u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्णांक off;
#पूर्ण_अगर

	/* convert ctx uses the fact sg element is first in काष्ठा */
	BUILD_BUG_ON(दुरत्व(काष्ठा sk_msg, sg) != 0);

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा sk_msg_md, data):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_msg, data),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_msg, data));
		अवरोध;
	हाल दुरत्व(काष्ठा sk_msg_md, data_end):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_msg, data_end),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_msg, data_end));
		अवरोध;
	हाल दुरत्व(काष्ठा sk_msg_md, family):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common, skc_family) != 2);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
					      काष्ठा sk_msg, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_msg, sk));
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common, skc_family));
		अवरोध;

	हाल दुरत्व(काष्ठा sk_msg_md, remote_ip4):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common, skc_daddr) != 4);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
						काष्ठा sk_msg, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_msg, sk));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common, skc_daddr));
		अवरोध;

	हाल दुरत्व(काष्ठा sk_msg_md, local_ip4):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common,
					  skc_rcv_saddr) != 4);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
					      काष्ठा sk_msg, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_msg, sk));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common,
					       skc_rcv_saddr));
		अवरोध;

	हाल दुरत्व(काष्ठा sk_msg_md, remote_ip6[0]) ...
	     दुरत्व(काष्ठा sk_msg_md, remote_ip6[3]):
#अगर IS_ENABLED(CONFIG_IPV6)
		BUILD_BUG_ON(माप_field(काष्ठा sock_common,
					  skc_v6_daddr.s6_addr32[0]) != 4);

		off = si->off;
		off -= दुरत्व(काष्ठा sk_msg_md, remote_ip6[0]);
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
						काष्ठा sk_msg, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_msg, sk));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common,
					       skc_v6_daddr.s6_addr32[0]) +
				      off);
#अन्यथा
		*insn++ = BPF_MOV32_IMM(si->dst_reg, 0);
#पूर्ण_अगर
		अवरोध;

	हाल दुरत्व(काष्ठा sk_msg_md, local_ip6[0]) ...
	     दुरत्व(काष्ठा sk_msg_md, local_ip6[3]):
#अगर IS_ENABLED(CONFIG_IPV6)
		BUILD_BUG_ON(माप_field(काष्ठा sock_common,
					  skc_v6_rcv_saddr.s6_addr32[0]) != 4);

		off = si->off;
		off -= दुरत्व(काष्ठा sk_msg_md, local_ip6[0]);
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
						काष्ठा sk_msg, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_msg, sk));
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common,
					       skc_v6_rcv_saddr.s6_addr32[0]) +
				      off);
#अन्यथा
		*insn++ = BPF_MOV32_IMM(si->dst_reg, 0);
#पूर्ण_अगर
		अवरोध;

	हाल दुरत्व(काष्ठा sk_msg_md, remote_port):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common, skc_dport) != 2);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
						काष्ठा sk_msg, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_msg, sk));
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common, skc_dport));
#अगर_अघोषित __BIG_ENDIAN_BITFIELD
		*insn++ = BPF_ALU32_IMM(BPF_LSH, si->dst_reg, 16);
#पूर्ण_अगर
		अवरोध;

	हाल दुरत्व(काष्ठा sk_msg_md, local_port):
		BUILD_BUG_ON(माप_field(काष्ठा sock_common, skc_num) != 2);

		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(
						काष्ठा sk_msg, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_msg, sk));
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->dst_reg,
				      दुरत्व(काष्ठा sock_common, skc_num));
		अवरोध;

	हाल दुरत्व(काष्ठा sk_msg_md, size):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_msg_sg, size),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_msg_sg, size));
		अवरोध;

	हाल दुरत्व(काष्ठा sk_msg_md, sk):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_msg, sk),
				      si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा sk_msg, sk));
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

स्थिर काष्ठा bpf_verअगरier_ops sk_filter_verअगरier_ops = अणु
	.get_func_proto		= sk_filter_func_proto,
	.is_valid_access	= sk_filter_is_valid_access,
	.convert_ctx_access	= bpf_convert_ctx_access,
	.gen_ld_असल		= bpf_gen_ld_असल,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops sk_filter_prog_ops = अणु
	.test_run		= bpf_prog_test_run_skb,
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops tc_cls_act_verअगरier_ops = अणु
	.get_func_proto		= tc_cls_act_func_proto,
	.is_valid_access	= tc_cls_act_is_valid_access,
	.convert_ctx_access	= tc_cls_act_convert_ctx_access,
	.gen_prologue		= tc_cls_act_prologue,
	.gen_ld_असल		= bpf_gen_ld_असल,
	.check_kfunc_call	= bpf_prog_test_check_kfunc_call,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops tc_cls_act_prog_ops = अणु
	.test_run		= bpf_prog_test_run_skb,
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops xdp_verअगरier_ops = अणु
	.get_func_proto		= xdp_func_proto,
	.is_valid_access	= xdp_is_valid_access,
	.convert_ctx_access	= xdp_convert_ctx_access,
	.gen_prologue		= bpf_noop_prologue,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops xdp_prog_ops = अणु
	.test_run		= bpf_prog_test_run_xdp,
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops cg_skb_verअगरier_ops = अणु
	.get_func_proto		= cg_skb_func_proto,
	.is_valid_access	= cg_skb_is_valid_access,
	.convert_ctx_access	= bpf_convert_ctx_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops cg_skb_prog_ops = अणु
	.test_run		= bpf_prog_test_run_skb,
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops lwt_in_verअगरier_ops = अणु
	.get_func_proto		= lwt_in_func_proto,
	.is_valid_access	= lwt_is_valid_access,
	.convert_ctx_access	= bpf_convert_ctx_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops lwt_in_prog_ops = अणु
	.test_run		= bpf_prog_test_run_skb,
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops lwt_out_verअगरier_ops = अणु
	.get_func_proto		= lwt_out_func_proto,
	.is_valid_access	= lwt_is_valid_access,
	.convert_ctx_access	= bpf_convert_ctx_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops lwt_out_prog_ops = अणु
	.test_run		= bpf_prog_test_run_skb,
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops lwt_xmit_verअगरier_ops = अणु
	.get_func_proto		= lwt_xmit_func_proto,
	.is_valid_access	= lwt_is_valid_access,
	.convert_ctx_access	= bpf_convert_ctx_access,
	.gen_prologue		= tc_cls_act_prologue,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops lwt_xmit_prog_ops = अणु
	.test_run		= bpf_prog_test_run_skb,
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops lwt_seg6local_verअगरier_ops = अणु
	.get_func_proto		= lwt_seg6local_func_proto,
	.is_valid_access	= lwt_is_valid_access,
	.convert_ctx_access	= bpf_convert_ctx_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops lwt_seg6local_prog_ops = अणु
	.test_run		= bpf_prog_test_run_skb,
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops cg_sock_verअगरier_ops = अणु
	.get_func_proto		= sock_filter_func_proto,
	.is_valid_access	= sock_filter_is_valid_access,
	.convert_ctx_access	= bpf_sock_convert_ctx_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops cg_sock_prog_ops = अणु
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops cg_sock_addr_verअगरier_ops = अणु
	.get_func_proto		= sock_addr_func_proto,
	.is_valid_access	= sock_addr_is_valid_access,
	.convert_ctx_access	= sock_addr_convert_ctx_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops cg_sock_addr_prog_ops = अणु
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops sock_ops_verअगरier_ops = अणु
	.get_func_proto		= sock_ops_func_proto,
	.is_valid_access	= sock_ops_is_valid_access,
	.convert_ctx_access	= sock_ops_convert_ctx_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops sock_ops_prog_ops = अणु
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops sk_skb_verअगरier_ops = अणु
	.get_func_proto		= sk_skb_func_proto,
	.is_valid_access	= sk_skb_is_valid_access,
	.convert_ctx_access	= sk_skb_convert_ctx_access,
	.gen_prologue		= sk_skb_prologue,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops sk_skb_prog_ops = अणु
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops sk_msg_verअगरier_ops = अणु
	.get_func_proto		= sk_msg_func_proto,
	.is_valid_access	= sk_msg_is_valid_access,
	.convert_ctx_access	= sk_msg_convert_ctx_access,
	.gen_prologue		= bpf_noop_prologue,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops sk_msg_prog_ops = अणु
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops flow_dissector_verअगरier_ops = अणु
	.get_func_proto		= flow_dissector_func_proto,
	.is_valid_access	= flow_dissector_is_valid_access,
	.convert_ctx_access	= flow_dissector_convert_ctx_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops flow_dissector_prog_ops = अणु
	.test_run		= bpf_prog_test_run_flow_dissector,
पूर्ण;

पूर्णांक sk_detach_filter(काष्ठा sock *sk)
अणु
	पूर्णांक ret = -ENOENT;
	काष्ठा sk_filter *filter;

	अगर (sock_flag(sk, SOCK_FILTER_LOCKED))
		वापस -EPERM;

	filter = rcu_dereference_रक्षित(sk->sk_filter,
					   lockdep_sock_is_held(sk));
	अगर (filter) अणु
		RCU_INIT_POINTER(sk->sk_filter, शून्य);
		sk_filter_unअक्षरge(sk, filter);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sk_detach_filter);

पूर्णांक sk_get_filter(काष्ठा sock *sk, काष्ठा sock_filter __user *ubuf,
		  अचिन्हित पूर्णांक len)
अणु
	काष्ठा sock_fprog_kern *fprog;
	काष्ठा sk_filter *filter;
	पूर्णांक ret = 0;

	lock_sock(sk);
	filter = rcu_dereference_रक्षित(sk->sk_filter,
					   lockdep_sock_is_held(sk));
	अगर (!filter)
		जाओ out;

	/* We're copying the filter that has been originally attached,
	 * so no conversion/decode needed anymore. eBPF programs that
	 * have no original program cannot be dumped through this.
	 */
	ret = -EACCES;
	fprog = filter->prog->orig_prog;
	अगर (!fprog)
		जाओ out;

	ret = fprog->len;
	अगर (!len)
		/* User space only enquires number of filter blocks. */
		जाओ out;

	ret = -EINVAL;
	अगर (len < fprog->len)
		जाओ out;

	ret = -EFAULT;
	अगर (copy_to_user(ubuf, fprog->filter, bpf_classic_proglen(fprog)))
		जाओ out;

	/* Instead of bytes, the API requests to वापस the number
	 * of filter blocks.
	 */
	ret = fprog->len;
out:
	release_sock(sk);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_INET
अटल व्योम bpf_init_reuseport_kern(काष्ठा sk_reuseport_kern *reuse_kern,
				    काष्ठा sock_reuseport *reuse,
				    काष्ठा sock *sk, काष्ठा sk_buff *skb,
				    u32 hash)
अणु
	reuse_kern->skb = skb;
	reuse_kern->sk = sk;
	reuse_kern->selected_sk = शून्य;
	reuse_kern->data_end = skb->data + skb_headlen(skb);
	reuse_kern->hash = hash;
	reuse_kern->reuseport_id = reuse->reuseport_id;
	reuse_kern->bind_inany = reuse->bind_inany;
पूर्ण

काष्ठा sock *bpf_run_sk_reuseport(काष्ठा sock_reuseport *reuse, काष्ठा sock *sk,
				  काष्ठा bpf_prog *prog, काष्ठा sk_buff *skb,
				  u32 hash)
अणु
	काष्ठा sk_reuseport_kern reuse_kern;
	क्रमागत sk_action action;

	bpf_init_reuseport_kern(&reuse_kern, reuse, sk, skb, hash);
	action = BPF_PROG_RUN(prog, &reuse_kern);

	अगर (action == SK_PASS)
		वापस reuse_kern.selected_sk;
	अन्यथा
		वापस ERR_PTR(-ECONNREFUSED);
पूर्ण

BPF_CALL_4(sk_select_reuseport, काष्ठा sk_reuseport_kern *, reuse_kern,
	   काष्ठा bpf_map *, map, व्योम *, key, u32, flags)
अणु
	bool is_sockarray = map->map_type == BPF_MAP_TYPE_REUSEPORT_SOCKARRAY;
	काष्ठा sock_reuseport *reuse;
	काष्ठा sock *selected_sk;

	selected_sk = map->ops->map_lookup_elem(map, key);
	अगर (!selected_sk)
		वापस -ENOENT;

	reuse = rcu_dereference(selected_sk->sk_reuseport_cb);
	अगर (!reuse) अणु
		/* Lookup in sock_map can वापस TCP ESTABLISHED sockets. */
		अगर (sk_is_refcounted(selected_sk))
			sock_put(selected_sk);

		/* reuseport_array has only sk with non शून्य sk_reuseport_cb.
		 * The only (!reuse) हाल here is - the sk has alपढ़ोy been
		 * unhashed (e.g. by बंद()), so treat it as -ENOENT.
		 *
		 * Other maps (e.g. sock_map) करो not provide this guarantee and
		 * the sk may never be in the reuseport group to begin with.
		 */
		वापस is_sockarray ? -ENOENT : -EINVAL;
	पूर्ण

	अगर (unlikely(reuse->reuseport_id != reuse_kern->reuseport_id)) अणु
		काष्ठा sock *sk = reuse_kern->sk;

		अगर (sk->sk_protocol != selected_sk->sk_protocol)
			वापस -EPROTOTYPE;
		अन्यथा अगर (sk->sk_family != selected_sk->sk_family)
			वापस -EAFNOSUPPORT;

		/* Catch all. Likely bound to a dअगरferent sockaddr. */
		वापस -EBADFD;
	पूर्ण

	reuse_kern->selected_sk = selected_sk;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto sk_select_reuseport_proto = अणु
	.func           = sk_select_reuseport,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type      = ARG_CONST_MAP_PTR,
	.arg3_type      = ARG_PTR_TO_MAP_KEY,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(sk_reuseport_load_bytes,
	   स्थिर काष्ठा sk_reuseport_kern *, reuse_kern, u32, offset,
	   व्योम *, to, u32, len)
अणु
	वापस ____bpf_skb_load_bytes(reuse_kern->skb, offset, to, len);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto sk_reuseport_load_bytes_proto = अणु
	.func		= sk_reuseport_load_bytes,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg4_type	= ARG_CONST_SIZE,
पूर्ण;

BPF_CALL_5(sk_reuseport_load_bytes_relative,
	   स्थिर काष्ठा sk_reuseport_kern *, reuse_kern, u32, offset,
	   व्योम *, to, u32, len, u32, start_header)
अणु
	वापस ____bpf_skb_load_bytes_relative(reuse_kern->skb, offset, to,
					       len, start_header);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto sk_reuseport_load_bytes_relative_proto = अणु
	.func		= sk_reuseport_load_bytes_relative,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg4_type	= ARG_CONST_SIZE,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto *
sk_reuseport_func_proto(क्रमागत bpf_func_id func_id,
			स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_sk_select_reuseport:
		वापस &sk_select_reuseport_proto;
	हाल BPF_FUNC_skb_load_bytes:
		वापस &sk_reuseport_load_bytes_proto;
	हाल BPF_FUNC_skb_load_bytes_relative:
		वापस &sk_reuseport_load_bytes_relative_proto;
	शेष:
		वापस bpf_base_func_proto(func_id);
	पूर्ण
पूर्ण

अटल bool
sk_reuseport_is_valid_access(पूर्णांक off, पूर्णांक size,
			     क्रमागत bpf_access_type type,
			     स्थिर काष्ठा bpf_prog *prog,
			     काष्ठा bpf_insn_access_aux *info)
अणु
	स्थिर u32 size_शेष = माप(__u32);

	अगर (off < 0 || off >= माप(काष्ठा sk_reuseport_md) ||
	    off % size || type != BPF_READ)
		वापस false;

	चयन (off) अणु
	हाल दुरत्व(काष्ठा sk_reuseport_md, data):
		info->reg_type = PTR_TO_PACKET;
		वापस size == माप(__u64);

	हाल दुरत्व(काष्ठा sk_reuseport_md, data_end):
		info->reg_type = PTR_TO_PACKET_END;
		वापस size == माप(__u64);

	हाल दुरत्व(काष्ठा sk_reuseport_md, hash):
		वापस size == size_शेष;

	/* Fields that allow narrowing */
	हाल bpf_ctx_range(काष्ठा sk_reuseport_md, eth_protocol):
		अगर (size < माप_field(काष्ठा sk_buff, protocol))
			वापस false;
		fallthrough;
	हाल bpf_ctx_range(काष्ठा sk_reuseport_md, ip_protocol):
	हाल bpf_ctx_range(काष्ठा sk_reuseport_md, bind_inany):
	हाल bpf_ctx_range(काष्ठा sk_reuseport_md, len):
		bpf_ctx_record_field_size(info, size_शेष);
		वापस bpf_ctx_narrow_access_ok(off, size, size_शेष);

	शेष:
		वापस false;
	पूर्ण
पूर्ण

#घोषणा SK_REUSEPORT_LOAD_FIELD(F) (अणु					\
	*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा sk_reuseport_kern, F), \
			      si->dst_reg, si->src_reg,			\
			      bpf_target_off(काष्ठा sk_reuseport_kern, F, \
					     माप_field(काष्ठा sk_reuseport_kern, F), \
					     target_size));		\
	पूर्ण)

#घोषणा SK_REUSEPORT_LOAD_SKB_FIELD(SKB_FIELD)				\
	SOCK_ADDR_LOAD_NESTED_FIELD(काष्ठा sk_reuseport_kern,		\
				    काष्ठा sk_buff,			\
				    skb,				\
				    SKB_FIELD)

#घोषणा SK_REUSEPORT_LOAD_SK_FIELD(SK_FIELD)				\
	SOCK_ADDR_LOAD_NESTED_FIELD(काष्ठा sk_reuseport_kern,		\
				    काष्ठा sock,			\
				    sk,					\
				    SK_FIELD)

अटल u32 sk_reuseport_convert_ctx_access(क्रमागत bpf_access_type type,
					   स्थिर काष्ठा bpf_insn *si,
					   काष्ठा bpf_insn *insn_buf,
					   काष्ठा bpf_prog *prog,
					   u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा sk_reuseport_md, data):
		SK_REUSEPORT_LOAD_SKB_FIELD(data);
		अवरोध;

	हाल दुरत्व(काष्ठा sk_reuseport_md, len):
		SK_REUSEPORT_LOAD_SKB_FIELD(len);
		अवरोध;

	हाल दुरत्व(काष्ठा sk_reuseport_md, eth_protocol):
		SK_REUSEPORT_LOAD_SKB_FIELD(protocol);
		अवरोध;

	हाल दुरत्व(काष्ठा sk_reuseport_md, ip_protocol):
		SK_REUSEPORT_LOAD_SK_FIELD(sk_protocol);
		अवरोध;

	हाल दुरत्व(काष्ठा sk_reuseport_md, data_end):
		SK_REUSEPORT_LOAD_FIELD(data_end);
		अवरोध;

	हाल दुरत्व(काष्ठा sk_reuseport_md, hash):
		SK_REUSEPORT_LOAD_FIELD(hash);
		अवरोध;

	हाल दुरत्व(काष्ठा sk_reuseport_md, bind_inany):
		SK_REUSEPORT_LOAD_FIELD(bind_inany);
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

स्थिर काष्ठा bpf_verअगरier_ops sk_reuseport_verअगरier_ops = अणु
	.get_func_proto		= sk_reuseport_func_proto,
	.is_valid_access	= sk_reuseport_is_valid_access,
	.convert_ctx_access	= sk_reuseport_convert_ctx_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops sk_reuseport_prog_ops = अणु
पूर्ण;

DEFINE_STATIC_KEY_FALSE(bpf_sk_lookup_enabled);
EXPORT_SYMBOL(bpf_sk_lookup_enabled);

BPF_CALL_3(bpf_sk_lookup_assign, काष्ठा bpf_sk_lookup_kern *, ctx,
	   काष्ठा sock *, sk, u64, flags)
अणु
	अगर (unlikely(flags & ~(BPF_SK_LOOKUP_F_REPLACE |
			       BPF_SK_LOOKUP_F_NO_REUSEPORT)))
		वापस -EINVAL;
	अगर (unlikely(sk && sk_is_refcounted(sk)))
		वापस -ESOCKTNOSUPPORT; /* reject non-RCU मुक्तd sockets */
	अगर (unlikely(sk && sk->sk_state == TCP_ESTABLISHED))
		वापस -ESOCKTNOSUPPORT; /* reject connected sockets */

	/* Check अगर socket is suitable क्रम packet L3/L4 protocol */
	अगर (sk && sk->sk_protocol != ctx->protocol)
		वापस -EPROTOTYPE;
	अगर (sk && sk->sk_family != ctx->family &&
	    (sk->sk_family == AF_INET || ipv6_only_sock(sk)))
		वापस -EAFNOSUPPORT;

	अगर (ctx->selected_sk && !(flags & BPF_SK_LOOKUP_F_REPLACE))
		वापस -EEXIST;

	/* Select socket as lookup result */
	ctx->selected_sk = sk;
	ctx->no_reuseport = flags & BPF_SK_LOOKUP_F_NO_REUSEPORT;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_sk_lookup_assign_proto = अणु
	.func		= bpf_sk_lookup_assign,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_SOCKET_OR_शून्य,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto *
sk_lookup_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_event_output_data_proto;
	हाल BPF_FUNC_sk_assign:
		वापस &bpf_sk_lookup_assign_proto;
	हाल BPF_FUNC_sk_release:
		वापस &bpf_sk_release_proto;
	शेष:
		वापस bpf_sk_base_func_proto(func_id);
	पूर्ण
पूर्ण

अटल bool sk_lookup_is_valid_access(पूर्णांक off, पूर्णांक size,
				      क्रमागत bpf_access_type type,
				      स्थिर काष्ठा bpf_prog *prog,
				      काष्ठा bpf_insn_access_aux *info)
अणु
	अगर (off < 0 || off >= माप(काष्ठा bpf_sk_lookup))
		वापस false;
	अगर (off % size != 0)
		वापस false;
	अगर (type != BPF_READ)
		वापस false;

	चयन (off) अणु
	हाल दुरत्व(काष्ठा bpf_sk_lookup, sk):
		info->reg_type = PTR_TO_SOCKET_OR_शून्य;
		वापस size == माप(__u64);

	हाल bpf_ctx_range(काष्ठा bpf_sk_lookup, family):
	हाल bpf_ctx_range(काष्ठा bpf_sk_lookup, protocol):
	हाल bpf_ctx_range(काष्ठा bpf_sk_lookup, remote_ip4):
	हाल bpf_ctx_range(काष्ठा bpf_sk_lookup, local_ip4):
	हाल bpf_ctx_range_till(काष्ठा bpf_sk_lookup, remote_ip6[0], remote_ip6[3]):
	हाल bpf_ctx_range_till(काष्ठा bpf_sk_lookup, local_ip6[0], local_ip6[3]):
	हाल bpf_ctx_range(काष्ठा bpf_sk_lookup, remote_port):
	हाल bpf_ctx_range(काष्ठा bpf_sk_lookup, local_port):
		bpf_ctx_record_field_size(info, माप(__u32));
		वापस bpf_ctx_narrow_access_ok(off, size, माप(__u32));

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल u32 sk_lookup_convert_ctx_access(क्रमागत bpf_access_type type,
					स्थिर काष्ठा bpf_insn *si,
					काष्ठा bpf_insn *insn_buf,
					काष्ठा bpf_prog *prog,
					u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा bpf_sk_lookup, sk):
		*insn++ = BPF_LDX_MEM(BPF_SIZखातापूर्ण(व्योम *), si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sk_lookup_kern, selected_sk));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sk_lookup, family):
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->src_reg,
				      bpf_target_off(काष्ठा bpf_sk_lookup_kern,
						     family, 2, target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sk_lookup, protocol):
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->src_reg,
				      bpf_target_off(काष्ठा bpf_sk_lookup_kern,
						     protocol, 2, target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sk_lookup, remote_ip4):
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg,
				      bpf_target_off(काष्ठा bpf_sk_lookup_kern,
						     v4.saddr, 4, target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sk_lookup, local_ip4):
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->src_reg,
				      bpf_target_off(काष्ठा bpf_sk_lookup_kern,
						     v4.daddr, 4, target_size));
		अवरोध;

	हाल bpf_ctx_range_till(काष्ठा bpf_sk_lookup,
				remote_ip6[0], remote_ip6[3]): अणु
#अगर IS_ENABLED(CONFIG_IPV6)
		पूर्णांक off = si->off;

		off -= दुरत्व(काष्ठा bpf_sk_lookup, remote_ip6[0]);
		off += bpf_target_off(काष्ठा in6_addr, s6_addr32[0], 4, target_size);
		*insn++ = BPF_LDX_MEM(BPF_SIZखातापूर्ण(व्योम *), si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sk_lookup_kern, v6.saddr));
		*insn++ = BPF_JMP_IMM(BPF_JEQ, si->dst_reg, 0, 1);
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg, off);
#अन्यथा
		*insn++ = BPF_MOV32_IMM(si->dst_reg, 0);
#पूर्ण_अगर
		अवरोध;
	पूर्ण
	हाल bpf_ctx_range_till(काष्ठा bpf_sk_lookup,
				local_ip6[0], local_ip6[3]): अणु
#अगर IS_ENABLED(CONFIG_IPV6)
		पूर्णांक off = si->off;

		off -= दुरत्व(काष्ठा bpf_sk_lookup, local_ip6[0]);
		off += bpf_target_off(काष्ठा in6_addr, s6_addr32[0], 4, target_size);
		*insn++ = BPF_LDX_MEM(BPF_SIZखातापूर्ण(व्योम *), si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_sk_lookup_kern, v6.daddr));
		*insn++ = BPF_JMP_IMM(BPF_JEQ, si->dst_reg, 0, 1);
		*insn++ = BPF_LDX_MEM(BPF_W, si->dst_reg, si->dst_reg, off);
#अन्यथा
		*insn++ = BPF_MOV32_IMM(si->dst_reg, 0);
#पूर्ण_अगर
		अवरोध;
	पूर्ण
	हाल दुरत्व(काष्ठा bpf_sk_lookup, remote_port):
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->src_reg,
				      bpf_target_off(काष्ठा bpf_sk_lookup_kern,
						     sport, 2, target_size));
		अवरोध;

	हाल दुरत्व(काष्ठा bpf_sk_lookup, local_port):
		*insn++ = BPF_LDX_MEM(BPF_H, si->dst_reg, si->src_reg,
				      bpf_target_off(काष्ठा bpf_sk_lookup_kern,
						     dport, 2, target_size));
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

स्थिर काष्ठा bpf_prog_ops sk_lookup_prog_ops = अणु
	.test_run = bpf_prog_test_run_sk_lookup,
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops sk_lookup_verअगरier_ops = अणु
	.get_func_proto		= sk_lookup_func_proto,
	.is_valid_access	= sk_lookup_is_valid_access,
	.convert_ctx_access	= sk_lookup_convert_ctx_access,
पूर्ण;

#पूर्ण_अगर /* CONFIG_INET */

DEFINE_BPF_DISPATCHER(xdp)

व्योम bpf_prog_change_xdp(काष्ठा bpf_prog *prev_prog, काष्ठा bpf_prog *prog)
अणु
	bpf_dispatcher_change_prog(BPF_DISPATCHER_PTR(xdp), prev_prog, prog);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_INFO_BTF
BTF_ID_LIST_GLOBAL(btf_sock_ids)
#घोषणा BTF_SOCK_TYPE(name, type) BTF_ID(काष्ठा, type)
BTF_SOCK_TYPE_xxx
#अघोषित BTF_SOCK_TYPE
#अन्यथा
u32 btf_sock_ids[MAX_BTF_SOCK_TYPE];
#पूर्ण_अगर

BPF_CALL_1(bpf_skc_to_tcp6_sock, काष्ठा sock *, sk)
अणु
	/* tcp6_sock type is not generated in dwarf and hence btf,
	 * trigger an explicit type generation here.
	 */
	BTF_TYPE_EMIT(काष्ठा tcp6_sock);
	अगर (sk && sk_fullsock(sk) && sk->sk_protocol == IPPROTO_TCP &&
	    sk->sk_family == AF_INET6)
		वापस (अचिन्हित दीर्घ)sk;

	वापस (अचिन्हित दीर्घ)शून्य;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_skc_to_tcp6_sock_proto = अणु
	.func			= bpf_skc_to_tcp6_sock,
	.gpl_only		= false,
	.ret_type		= RET_PTR_TO_BTF_ID_OR_शून्य,
	.arg1_type		= ARG_PTR_TO_BTF_ID_SOCK_COMMON,
	.ret_btf_id		= &btf_sock_ids[BTF_SOCK_TYPE_TCP6],
पूर्ण;

BPF_CALL_1(bpf_skc_to_tcp_sock, काष्ठा sock *, sk)
अणु
	अगर (sk && sk_fullsock(sk) && sk->sk_protocol == IPPROTO_TCP)
		वापस (अचिन्हित दीर्घ)sk;

	वापस (अचिन्हित दीर्घ)शून्य;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_skc_to_tcp_sock_proto = अणु
	.func			= bpf_skc_to_tcp_sock,
	.gpl_only		= false,
	.ret_type		= RET_PTR_TO_BTF_ID_OR_शून्य,
	.arg1_type		= ARG_PTR_TO_BTF_ID_SOCK_COMMON,
	.ret_btf_id		= &btf_sock_ids[BTF_SOCK_TYPE_TCP],
पूर्ण;

BPF_CALL_1(bpf_skc_to_tcp_समयरुको_sock, काष्ठा sock *, sk)
अणु
	/* BTF types क्रम tcp_समयरुको_sock and inet_समयरुको_sock are not
	 * generated अगर CONFIG_INET=n. Trigger an explicit generation here.
	 */
	BTF_TYPE_EMIT(काष्ठा inet_समयरुको_sock);
	BTF_TYPE_EMIT(काष्ठा tcp_समयरुको_sock);

#अगर_घोषित CONFIG_INET
	अगर (sk && sk->sk_prot == &tcp_prot && sk->sk_state == TCP_TIME_WAIT)
		वापस (अचिन्हित दीर्घ)sk;
#पूर्ण_अगर

#अगर IS_BUILTIN(CONFIG_IPV6)
	अगर (sk && sk->sk_prot == &tcpv6_prot && sk->sk_state == TCP_TIME_WAIT)
		वापस (अचिन्हित दीर्घ)sk;
#पूर्ण_अगर

	वापस (अचिन्हित दीर्घ)शून्य;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_skc_to_tcp_समयरुको_sock_proto = अणु
	.func			= bpf_skc_to_tcp_समयरुको_sock,
	.gpl_only		= false,
	.ret_type		= RET_PTR_TO_BTF_ID_OR_शून्य,
	.arg1_type		= ARG_PTR_TO_BTF_ID_SOCK_COMMON,
	.ret_btf_id		= &btf_sock_ids[BTF_SOCK_TYPE_TCP_TW],
पूर्ण;

BPF_CALL_1(bpf_skc_to_tcp_request_sock, काष्ठा sock *, sk)
अणु
#अगर_घोषित CONFIG_INET
	अगर (sk && sk->sk_prot == &tcp_prot && sk->sk_state == TCP_NEW_SYN_RECV)
		वापस (अचिन्हित दीर्घ)sk;
#पूर्ण_अगर

#अगर IS_BUILTIN(CONFIG_IPV6)
	अगर (sk && sk->sk_prot == &tcpv6_prot && sk->sk_state == TCP_NEW_SYN_RECV)
		वापस (अचिन्हित दीर्घ)sk;
#पूर्ण_अगर

	वापस (अचिन्हित दीर्घ)शून्य;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_skc_to_tcp_request_sock_proto = अणु
	.func			= bpf_skc_to_tcp_request_sock,
	.gpl_only		= false,
	.ret_type		= RET_PTR_TO_BTF_ID_OR_शून्य,
	.arg1_type		= ARG_PTR_TO_BTF_ID_SOCK_COMMON,
	.ret_btf_id		= &btf_sock_ids[BTF_SOCK_TYPE_TCP_REQ],
पूर्ण;

BPF_CALL_1(bpf_skc_to_udp6_sock, काष्ठा sock *, sk)
अणु
	/* udp6_sock type is not generated in dwarf and hence btf,
	 * trigger an explicit type generation here.
	 */
	BTF_TYPE_EMIT(काष्ठा udp6_sock);
	अगर (sk && sk_fullsock(sk) && sk->sk_protocol == IPPROTO_UDP &&
	    sk->sk_type == SOCK_DGRAM && sk->sk_family == AF_INET6)
		वापस (अचिन्हित दीर्घ)sk;

	वापस (अचिन्हित दीर्घ)शून्य;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_skc_to_udp6_sock_proto = अणु
	.func			= bpf_skc_to_udp6_sock,
	.gpl_only		= false,
	.ret_type		= RET_PTR_TO_BTF_ID_OR_शून्य,
	.arg1_type		= ARG_PTR_TO_BTF_ID_SOCK_COMMON,
	.ret_btf_id		= &btf_sock_ids[BTF_SOCK_TYPE_UDP6],
पूर्ण;

BPF_CALL_1(bpf_sock_from_file, काष्ठा file *, file)
अणु
	वापस (अचिन्हित दीर्घ)sock_from_file(file);
पूर्ण

BTF_ID_LIST(bpf_sock_from_file_btf_ids)
BTF_ID(काष्ठा, socket)
BTF_ID(काष्ठा, file)

स्थिर काष्ठा bpf_func_proto bpf_sock_from_file_proto = अणु
	.func		= bpf_sock_from_file,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_BTF_ID_OR_शून्य,
	.ret_btf_id	= &bpf_sock_from_file_btf_ids[0],
	.arg1_type	= ARG_PTR_TO_BTF_ID,
	.arg1_btf_id	= &bpf_sock_from_file_btf_ids[1],
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto *
bpf_sk_base_func_proto(क्रमागत bpf_func_id func_id)
अणु
	स्थिर काष्ठा bpf_func_proto *func;

	चयन (func_id) अणु
	हाल BPF_FUNC_skc_to_tcp6_sock:
		func = &bpf_skc_to_tcp6_sock_proto;
		अवरोध;
	हाल BPF_FUNC_skc_to_tcp_sock:
		func = &bpf_skc_to_tcp_sock_proto;
		अवरोध;
	हाल BPF_FUNC_skc_to_tcp_समयरुको_sock:
		func = &bpf_skc_to_tcp_समयरुको_sock_proto;
		अवरोध;
	हाल BPF_FUNC_skc_to_tcp_request_sock:
		func = &bpf_skc_to_tcp_request_sock_proto;
		अवरोध;
	हाल BPF_FUNC_skc_to_udp6_sock:
		func = &bpf_skc_to_udp6_sock_proto;
		अवरोध;
	शेष:
		वापस bpf_base_func_proto(func_id);
	पूर्ण

	अगर (!perfmon_capable())
		वापस शून्य;

	वापस func;
पूर्ण
