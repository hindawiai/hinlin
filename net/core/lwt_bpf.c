<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 Thomas Graf <tgraf@tgraf.ch>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <linux/bpf.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/gre.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ipv6_stubs.h>

काष्ठा bpf_lwt_prog अणु
	काष्ठा bpf_prog *prog;
	अक्षर *name;
पूर्ण;

काष्ठा bpf_lwt अणु
	काष्ठा bpf_lwt_prog in;
	काष्ठा bpf_lwt_prog out;
	काष्ठा bpf_lwt_prog xmit;
	पूर्णांक family;
पूर्ण;

#घोषणा MAX_PROG_NAME 256

अटल अंतरभूत काष्ठा bpf_lwt *bpf_lwt_lwtunnel(काष्ठा lwtunnel_state *lwt)
अणु
	वापस (काष्ठा bpf_lwt *)lwt->data;
पूर्ण

#घोषणा NO_REसूचीECT false
#घोषणा CAN_REसूचीECT true

अटल पूर्णांक run_lwt_bpf(काष्ठा sk_buff *skb, काष्ठा bpf_lwt_prog *lwt,
		       काष्ठा dst_entry *dst, bool can_redirect)
अणु
	पूर्णांक ret;

	/* Migration disable and BH disable are needed to protect per-cpu
	 * redirect_info between BPF prog and skb_करो_redirect().
	 */
	migrate_disable();
	local_bh_disable();
	bpf_compute_data_poपूर्णांकers(skb);
	ret = bpf_prog_run_save_cb(lwt->prog, skb);

	चयन (ret) अणु
	हाल BPF_OK:
	हाल BPF_LWT_REROUTE:
		अवरोध;

	हाल BPF_REसूचीECT:
		अगर (unlikely(!can_redirect)) अणु
			pr_warn_once("Illegal redirect return code in prog %s\n",
				     lwt->name ? : "<unknown>");
			ret = BPF_OK;
		पूर्ण अन्यथा अणु
			skb_reset_mac_header(skb);
			ret = skb_करो_redirect(skb);
			अगर (ret == 0)
				ret = BPF_REसूचीECT;
		पूर्ण
		अवरोध;

	हाल BPF_DROP:
		kमुक्त_skb(skb);
		ret = -EPERM;
		अवरोध;

	शेष:
		pr_warn_once("bpf-lwt: Illegal return value %u, expect packet loss\n", ret);
		kमुक्त_skb(skb);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	local_bh_enable();
	migrate_enable();

	वापस ret;
पूर्ण

अटल पूर्णांक bpf_lwt_input_reroute(काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = -EINVAL;

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		काष्ठा net_device *dev = skb_dst(skb)->dev;
		काष्ठा iphdr *iph = ip_hdr(skb);

		dev_hold(dev);
		skb_dst_drop(skb);
		err = ip_route_input_noref(skb, iph->daddr, iph->saddr,
					   iph->tos, dev);
		dev_put(dev);
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		skb_dst_drop(skb);
		err = ipv6_stub->ipv6_route_input(skb);
	पूर्ण अन्यथा अणु
		err = -EAFNOSUPPORT;
	पूर्ण

	अगर (err)
		जाओ err;
	वापस dst_input(skb);

err:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक bpf_input(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा bpf_lwt *bpf;
	पूर्णांक ret;

	bpf = bpf_lwt_lwtunnel(dst->lwtstate);
	अगर (bpf->in.prog) अणु
		ret = run_lwt_bpf(skb, &bpf->in, dst, NO_REसूचीECT);
		अगर (ret < 0)
			वापस ret;
		अगर (ret == BPF_LWT_REROUTE)
			वापस bpf_lwt_input_reroute(skb);
	पूर्ण

	अगर (unlikely(!dst->lwtstate->orig_input)) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	वापस dst->lwtstate->orig_input(skb);
पूर्ण

अटल पूर्णांक bpf_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा bpf_lwt *bpf;
	पूर्णांक ret;

	bpf = bpf_lwt_lwtunnel(dst->lwtstate);
	अगर (bpf->out.prog) अणु
		ret = run_lwt_bpf(skb, &bpf->out, dst, NO_REसूचीECT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (unlikely(!dst->lwtstate->orig_output)) अणु
		pr_warn_once("orig_output not set on dst for prog %s\n",
			     bpf->out.name);
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	वापस dst->lwtstate->orig_output(net, sk, skb);
पूर्ण

अटल पूर्णांक xmit_check_hhlen(काष्ठा sk_buff *skb)
अणु
	पूर्णांक hh_len = skb_dst(skb)->dev->hard_header_len;

	अगर (skb_headroom(skb) < hh_len) अणु
		पूर्णांक nhead = HH_DATA_ALIGN(hh_len - skb_headroom(skb));

		अगर (pskb_expand_head(skb, nhead, 0, GFP_ATOMIC))
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_lwt_xmit_reroute(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *l3mdev = l3mdev_master_dev_rcu(skb_dst(skb)->dev);
	पूर्णांक oअगर = l3mdev ? l3mdev->अगरindex : 0;
	काष्ठा dst_entry *dst = शून्य;
	पूर्णांक err = -EAFNOSUPPORT;
	काष्ठा sock *sk;
	काष्ठा net *net;
	bool ipv4;

	अगर (skb->protocol == htons(ETH_P_IP))
		ipv4 = true;
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		ipv4 = false;
	अन्यथा
		जाओ err;

	sk = sk_to_full_sk(skb->sk);
	अगर (sk) अणु
		अगर (sk->sk_bound_dev_अगर)
			oअगर = sk->sk_bound_dev_अगर;
		net = sock_net(sk);
	पूर्ण अन्यथा अणु
		net = dev_net(skb_dst(skb)->dev);
	पूर्ण

	अगर (ipv4) अणु
		काष्ठा iphdr *iph = ip_hdr(skb);
		काष्ठा flowi4 fl4 = अणुपूर्ण;
		काष्ठा rtable *rt;

		fl4.flowi4_oअगर = oअगर;
		fl4.flowi4_mark = skb->mark;
		fl4.flowi4_uid = sock_net_uid(net, sk);
		fl4.flowi4_tos = RT_TOS(iph->tos);
		fl4.flowi4_flags = FLOWI_FLAG_ANYSRC;
		fl4.flowi4_proto = iph->protocol;
		fl4.daddr = iph->daddr;
		fl4.saddr = iph->saddr;

		rt = ip_route_output_key(net, &fl4);
		अगर (IS_ERR(rt)) अणु
			err = PTR_ERR(rt);
			जाओ err;
		पूर्ण
		dst = &rt->dst;
	पूर्ण अन्यथा अणु
		काष्ठा ipv6hdr *iph6 = ipv6_hdr(skb);
		काष्ठा flowi6 fl6 = अणुपूर्ण;

		fl6.flowi6_oअगर = oअगर;
		fl6.flowi6_mark = skb->mark;
		fl6.flowi6_uid = sock_net_uid(net, sk);
		fl6.flowlabel = ip6_flowinfo(iph6);
		fl6.flowi6_proto = iph6->nexthdr;
		fl6.daddr = iph6->daddr;
		fl6.saddr = iph6->saddr;

		dst = ipv6_stub->ipv6_dst_lookup_flow(net, skb->sk, &fl6, शून्य);
		अगर (IS_ERR(dst)) अणु
			err = PTR_ERR(dst);
			जाओ err;
		पूर्ण
	पूर्ण
	अगर (unlikely(dst->error)) अणु
		err = dst->error;
		dst_release(dst);
		जाओ err;
	पूर्ण

	/* Although skb header was reserved in bpf_lwt_push_ip_encap(), it
	 * was करोne क्रम the previous dst, so we are करोing it here again, in
	 * हाल the new dst needs much more space. The call below is a noop
	 * अगर there is enough header space in skb.
	 */
	err = skb_cow_head(skb, LL_RESERVED_SPACE(dst->dev));
	अगर (unlikely(err))
		जाओ err;

	skb_dst_drop(skb);
	skb_dst_set(skb, dst);

	err = dst_output(dev_net(skb_dst(skb)->dev), skb->sk, skb);
	अगर (unlikely(err))
		वापस err;

	/* ip[6]_finish_output2 understand LWTUNNEL_XMIT_DONE */
	वापस LWTUNNEL_XMIT_DONE;

err:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक bpf_xmit(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा bpf_lwt *bpf;

	bpf = bpf_lwt_lwtunnel(dst->lwtstate);
	अगर (bpf->xmit.prog) अणु
		__be16 proto = skb->protocol;
		पूर्णांक ret;

		ret = run_lwt_bpf(skb, &bpf->xmit, dst, CAN_REसूचीECT);
		चयन (ret) अणु
		हाल BPF_OK:
			/* If the header changed, e.g. via bpf_lwt_push_encap,
			 * BPF_LWT_REROUTE below should have been used अगर the
			 * protocol was also changed.
			 */
			अगर (skb->protocol != proto) अणु
				kमुक्त_skb(skb);
				वापस -EINVAL;
			पूर्ण
			/* If the header was expanded, headroom might be too
			 * small क्रम L2 header to come, expand as needed.
			 */
			ret = xmit_check_hhlen(skb);
			अगर (unlikely(ret))
				वापस ret;

			वापस LWTUNNEL_XMIT_CONTINUE;
		हाल BPF_REसूचीECT:
			वापस LWTUNNEL_XMIT_DONE;
		हाल BPF_LWT_REROUTE:
			वापस bpf_lwt_xmit_reroute(skb);
		शेष:
			वापस ret;
		पूर्ण
	पूर्ण

	वापस LWTUNNEL_XMIT_CONTINUE;
पूर्ण

अटल व्योम bpf_lwt_prog_destroy(काष्ठा bpf_lwt_prog *prog)
अणु
	अगर (prog->prog)
		bpf_prog_put(prog->prog);

	kमुक्त(prog->name);
पूर्ण

अटल व्योम bpf_destroy_state(काष्ठा lwtunnel_state *lwt)
अणु
	काष्ठा bpf_lwt *bpf = bpf_lwt_lwtunnel(lwt);

	bpf_lwt_prog_destroy(&bpf->in);
	bpf_lwt_prog_destroy(&bpf->out);
	bpf_lwt_prog_destroy(&bpf->xmit);
पूर्ण

अटल स्थिर काष्ठा nla_policy bpf_prog_policy[LWT_BPF_PROG_MAX + 1] = अणु
	[LWT_BPF_PROG_FD]   = अणु .type = NLA_U32, पूर्ण,
	[LWT_BPF_PROG_NAME] = अणु .type = NLA_NUL_STRING,
				.len = MAX_PROG_NAME पूर्ण,
पूर्ण;

अटल पूर्णांक bpf_parse_prog(काष्ठा nlattr *attr, काष्ठा bpf_lwt_prog *prog,
			  क्रमागत bpf_prog_type type)
अणु
	काष्ठा nlattr *tb[LWT_BPF_PROG_MAX + 1];
	काष्ठा bpf_prog *p;
	पूर्णांक ret;
	u32 fd;

	ret = nla_parse_nested_deprecated(tb, LWT_BPF_PROG_MAX, attr,
					  bpf_prog_policy, शून्य);
	अगर (ret < 0)
		वापस ret;

	अगर (!tb[LWT_BPF_PROG_FD] || !tb[LWT_BPF_PROG_NAME])
		वापस -EINVAL;

	prog->name = nla_memdup(tb[LWT_BPF_PROG_NAME], GFP_ATOMIC);
	अगर (!prog->name)
		वापस -ENOMEM;

	fd = nla_get_u32(tb[LWT_BPF_PROG_FD]);
	p = bpf_prog_get_type(fd, type);
	अगर (IS_ERR(p))
		वापस PTR_ERR(p);

	prog->prog = p;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy bpf_nl_policy[LWT_BPF_MAX + 1] = अणु
	[LWT_BPF_IN]		= अणु .type = NLA_NESTED, पूर्ण,
	[LWT_BPF_OUT]		= अणु .type = NLA_NESTED, पूर्ण,
	[LWT_BPF_XMIT]		= अणु .type = NLA_NESTED, पूर्ण,
	[LWT_BPF_XMIT_HEADROOM]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक bpf_build_state(काष्ठा net *net, काष्ठा nlattr *nla,
			   अचिन्हित पूर्णांक family, स्थिर व्योम *cfg,
			   काष्ठा lwtunnel_state **ts,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[LWT_BPF_MAX + 1];
	काष्ठा lwtunnel_state *newts;
	काष्ठा bpf_lwt *bpf;
	पूर्णांक ret;

	अगर (family != AF_INET && family != AF_INET6)
		वापस -EAFNOSUPPORT;

	ret = nla_parse_nested_deprecated(tb, LWT_BPF_MAX, nla, bpf_nl_policy,
					  extack);
	अगर (ret < 0)
		वापस ret;

	अगर (!tb[LWT_BPF_IN] && !tb[LWT_BPF_OUT] && !tb[LWT_BPF_XMIT])
		वापस -EINVAL;

	newts = lwtunnel_state_alloc(माप(*bpf));
	अगर (!newts)
		वापस -ENOMEM;

	newts->type = LWTUNNEL_ENCAP_BPF;
	bpf = bpf_lwt_lwtunnel(newts);

	अगर (tb[LWT_BPF_IN]) अणु
		newts->flags |= LWTUNNEL_STATE_INPUT_REसूचीECT;
		ret = bpf_parse_prog(tb[LWT_BPF_IN], &bpf->in,
				     BPF_PROG_TYPE_LWT_IN);
		अगर (ret  < 0)
			जाओ errout;
	पूर्ण

	अगर (tb[LWT_BPF_OUT]) अणु
		newts->flags |= LWTUNNEL_STATE_OUTPUT_REसूचीECT;
		ret = bpf_parse_prog(tb[LWT_BPF_OUT], &bpf->out,
				     BPF_PROG_TYPE_LWT_OUT);
		अगर (ret < 0)
			जाओ errout;
	पूर्ण

	अगर (tb[LWT_BPF_XMIT]) अणु
		newts->flags |= LWTUNNEL_STATE_XMIT_REसूचीECT;
		ret = bpf_parse_prog(tb[LWT_BPF_XMIT], &bpf->xmit,
				     BPF_PROG_TYPE_LWT_XMIT);
		अगर (ret < 0)
			जाओ errout;
	पूर्ण

	अगर (tb[LWT_BPF_XMIT_HEADROOM]) अणु
		u32 headroom = nla_get_u32(tb[LWT_BPF_XMIT_HEADROOM]);

		अगर (headroom > LWT_BPF_MAX_HEADROOM) अणु
			ret = -दुस्फल;
			जाओ errout;
		पूर्ण

		newts->headroom = headroom;
	पूर्ण

	bpf->family = family;
	*ts = newts;

	वापस 0;

errout:
	bpf_destroy_state(newts);
	kमुक्त(newts);
	वापस ret;
पूर्ण

अटल पूर्णांक bpf_fill_lwt_prog(काष्ठा sk_buff *skb, पूर्णांक attr,
			     काष्ठा bpf_lwt_prog *prog)
अणु
	काष्ठा nlattr *nest;

	अगर (!prog->prog)
		वापस 0;

	nest = nla_nest_start_noflag(skb, attr);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (prog->name &&
	    nla_put_string(skb, LWT_BPF_PROG_NAME, prog->name))
		वापस -EMSGSIZE;

	वापस nla_nest_end(skb, nest);
पूर्ण

अटल पूर्णांक bpf_fill_encap_info(काष्ठा sk_buff *skb, काष्ठा lwtunnel_state *lwt)
अणु
	काष्ठा bpf_lwt *bpf = bpf_lwt_lwtunnel(lwt);

	अगर (bpf_fill_lwt_prog(skb, LWT_BPF_IN, &bpf->in) < 0 ||
	    bpf_fill_lwt_prog(skb, LWT_BPF_OUT, &bpf->out) < 0 ||
	    bpf_fill_lwt_prog(skb, LWT_BPF_XMIT, &bpf->xmit) < 0)
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_encap_nlsize(काष्ठा lwtunnel_state *lwtstate)
अणु
	पूर्णांक nest_len = nla_total_size(माप(काष्ठा nlattr)) +
		       nla_total_size(MAX_PROG_NAME) + /* LWT_BPF_PROG_NAME */
		       0;

	वापस nest_len + /* LWT_BPF_IN */
	       nest_len + /* LWT_BPF_OUT */
	       nest_len + /* LWT_BPF_XMIT */
	       0;
पूर्ण

अटल पूर्णांक bpf_lwt_prog_cmp(काष्ठा bpf_lwt_prog *a, काष्ठा bpf_lwt_prog *b)
अणु
	/* FIXME:
	 * The LWT state is currently rebuilt क्रम delete requests which
	 * results in a new bpf_prog instance. Comparing names क्रम now.
	 */
	अगर (!a->name && !b->name)
		वापस 0;

	अगर (!a->name || !b->name)
		वापस 1;

	वापस म_भेद(a->name, b->name);
पूर्ण

अटल पूर्णांक bpf_encap_cmp(काष्ठा lwtunnel_state *a, काष्ठा lwtunnel_state *b)
अणु
	काष्ठा bpf_lwt *a_bpf = bpf_lwt_lwtunnel(a);
	काष्ठा bpf_lwt *b_bpf = bpf_lwt_lwtunnel(b);

	वापस bpf_lwt_prog_cmp(&a_bpf->in, &b_bpf->in) ||
	       bpf_lwt_prog_cmp(&a_bpf->out, &b_bpf->out) ||
	       bpf_lwt_prog_cmp(&a_bpf->xmit, &b_bpf->xmit);
पूर्ण

अटल स्थिर काष्ठा lwtunnel_encap_ops bpf_encap_ops = अणु
	.build_state	= bpf_build_state,
	.destroy_state	= bpf_destroy_state,
	.input		= bpf_input,
	.output		= bpf_output,
	.xmit		= bpf_xmit,
	.fill_encap	= bpf_fill_encap_info,
	.get_encap_size = bpf_encap_nlsize,
	.cmp_encap	= bpf_encap_cmp,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक handle_gso_type(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक gso_type,
			   पूर्णांक encap_len)
अणु
	काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);

	gso_type |= SKB_GSO_DODGY;
	shinfo->gso_type |= gso_type;
	skb_decrease_gso_size(shinfo, encap_len);
	shinfo->gso_segs = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक handle_gso_encap(काष्ठा sk_buff *skb, bool ipv4, पूर्णांक encap_len)
अणु
	पूर्णांक next_hdr_offset;
	व्योम *next_hdr;
	__u8 protocol;

	/* SCTP and UDP_L4 gso need more nuanced handling than what
	 * handle_gso_type() करोes above: skb_decrease_gso_size() is not enough.
	 * So at the moment only TCP GSO packets are let through.
	 */
	अगर (!(skb_shinfo(skb)->gso_type & (SKB_GSO_TCPV4 | SKB_GSO_TCPV6)))
		वापस -ENOTSUPP;

	अगर (ipv4) अणु
		protocol = ip_hdr(skb)->protocol;
		next_hdr_offset = माप(काष्ठा iphdr);
		next_hdr = skb_network_header(skb) + next_hdr_offset;
	पूर्ण अन्यथा अणु
		protocol = ipv6_hdr(skb)->nexthdr;
		next_hdr_offset = माप(काष्ठा ipv6hdr);
		next_hdr = skb_network_header(skb) + next_hdr_offset;
	पूर्ण

	चयन (protocol) अणु
	हाल IPPROTO_GRE:
		next_hdr_offset += माप(काष्ठा gre_base_hdr);
		अगर (next_hdr_offset > encap_len)
			वापस -EINVAL;

		अगर (((काष्ठा gre_base_hdr *)next_hdr)->flags & GRE_CSUM)
			वापस handle_gso_type(skb, SKB_GSO_GRE_CSUM,
					       encap_len);
		वापस handle_gso_type(skb, SKB_GSO_GRE, encap_len);

	हाल IPPROTO_UDP:
		next_hdr_offset += माप(काष्ठा udphdr);
		अगर (next_hdr_offset > encap_len)
			वापस -EINVAL;

		अगर (((काष्ठा udphdr *)next_hdr)->check)
			वापस handle_gso_type(skb, SKB_GSO_UDP_TUNNEL_CSUM,
					       encap_len);
		वापस handle_gso_type(skb, SKB_GSO_UDP_TUNNEL, encap_len);

	हाल IPPROTO_IP:
	हाल IPPROTO_IPV6:
		अगर (ipv4)
			वापस handle_gso_type(skb, SKB_GSO_IPXIP4, encap_len);
		अन्यथा
			वापस handle_gso_type(skb, SKB_GSO_IPXIP6, encap_len);

	शेष:
		वापस -EPROTONOSUPPORT;
	पूर्ण
पूर्ण

पूर्णांक bpf_lwt_push_ip_encap(काष्ठा sk_buff *skb, व्योम *hdr, u32 len, bool ingress)
अणु
	काष्ठा iphdr *iph;
	bool ipv4;
	पूर्णांक err;

	अगर (unlikely(len < माप(काष्ठा iphdr) || len > LWT_BPF_MAX_HEADROOM))
		वापस -EINVAL;

	/* validate protocol and length */
	iph = (काष्ठा iphdr *)hdr;
	अगर (iph->version == 4) अणु
		ipv4 = true;
		अगर (unlikely(len < iph->ihl * 4))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (iph->version == 6) अणु
		ipv4 = false;
		अगर (unlikely(len < माप(काष्ठा ipv6hdr)))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (ingress)
		err = skb_cow_head(skb, len + skb->mac_len);
	अन्यथा
		err = skb_cow_head(skb,
				   len + LL_RESERVED_SPACE(skb_dst(skb)->dev));
	अगर (unlikely(err))
		वापस err;

	/* push the encap headers and fix poपूर्णांकers */
	skb_reset_inner_headers(skb);
	skb_reset_inner_mac_header(skb);  /* mac header is not yet set */
	skb_set_inner_protocol(skb, skb->protocol);
	skb->encapsulation = 1;
	skb_push(skb, len);
	अगर (ingress)
		skb_postpush_rcsum(skb, iph, len);
	skb_reset_network_header(skb);
	स_नकल(skb_network_header(skb), hdr, len);
	bpf_compute_data_poपूर्णांकers(skb);
	skb_clear_hash(skb);

	अगर (ipv4) अणु
		skb->protocol = htons(ETH_P_IP);
		iph = ip_hdr(skb);

		अगर (!iph->check)
			iph->check = ip_fast_csum((अचिन्हित अक्षर *)iph,
						  iph->ihl);
	पूर्ण अन्यथा अणु
		skb->protocol = htons(ETH_P_IPV6);
	पूर्ण

	अगर (skb_is_gso(skb))
		वापस handle_gso_encap(skb, ipv4, len);

	वापस 0;
पूर्ण

अटल पूर्णांक __init bpf_lwt_init(व्योम)
अणु
	वापस lwtunnel_encap_add_ops(&bpf_encap_ops, LWTUNNEL_ENCAP_BPF);
पूर्ण

subsys_initcall(bpf_lwt_init)
