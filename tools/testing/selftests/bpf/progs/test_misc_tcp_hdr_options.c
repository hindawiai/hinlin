<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <मानकघोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/socket.h>
#समावेश <linux/bpf.h>
#समावेश <linux/types.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>
#घोषणा BPF_PROG_TEST_TCP_HDR_OPTIONS
#समावेश "test_tcp_hdr_options.h"

__u16 last_addr16_n = __bpf_htons(1);
__u16 active_lport_n = 0;
__u16 active_lport_h = 0;
__u16 passive_lport_n = 0;
__u16 passive_lport_h = 0;

/* options received at passive side */
अचिन्हित पूर्णांक nr_pure_ack = 0;
अचिन्हित पूर्णांक nr_data = 0;
अचिन्हित पूर्णांक nr_syn = 0;
अचिन्हित पूर्णांक nr_fin = 0;

/* Check the header received from the active side */
अटल पूर्णांक __check_active_hdr_in(काष्ठा bpf_sock_ops *skops, bool check_syn)
अणु
	जोड़ अणु
		काष्ठा tcphdr th;
		काष्ठा ipv6hdr ip6;
		काष्ठा tcp_exprm_opt exprm_opt;
		काष्ठा tcp_opt reg_opt;
		__u8 data[100]; /* IPv6 (40) + Max TCP hdr (60) */
	पूर्ण hdr = अणुपूर्ण;
	__u64 load_flags = check_syn ? BPF_LOAD_HDR_OPT_TCP_SYN : 0;
	काष्ठा tcphdr *pth;
	पूर्णांक ret;

	hdr.reg_opt.kind = 0xB9;

	/* The option is 4 bytes दीर्घ instead of 2 bytes */
	ret = bpf_load_hdr_opt(skops, &hdr.reg_opt, 2, load_flags);
	अगर (ret != -ENOSPC)
		RET_CG_ERR(ret);

	/* Test searching magic with regular kind */
	hdr.reg_opt.len = 4;
	ret = bpf_load_hdr_opt(skops, &hdr.reg_opt, माप(hdr.reg_opt),
			       load_flags);
	अगर (ret != -EINVAL)
		RET_CG_ERR(ret);

	hdr.reg_opt.len = 0;
	ret = bpf_load_hdr_opt(skops, &hdr.reg_opt, माप(hdr.reg_opt),
			       load_flags);
	अगर (ret != 4 || hdr.reg_opt.len != 4 || hdr.reg_opt.kind != 0xB9 ||
	    hdr.reg_opt.data[0] != 0xfa || hdr.reg_opt.data[1] != 0xce)
		RET_CG_ERR(ret);

	/* Test searching experimental option with invalid kind length */
	hdr.exprm_opt.kind = TCPOPT_EXP;
	hdr.exprm_opt.len = 5;
	hdr.exprm_opt.magic = 0;
	ret = bpf_load_hdr_opt(skops, &hdr.exprm_opt, माप(hdr.exprm_opt),
			       load_flags);
	अगर (ret != -EINVAL)
		RET_CG_ERR(ret);

	/* Test searching experimental option with 0 magic value */
	hdr.exprm_opt.len = 4;
	ret = bpf_load_hdr_opt(skops, &hdr.exprm_opt, माप(hdr.exprm_opt),
			       load_flags);
	अगर (ret != -ENOMSG)
		RET_CG_ERR(ret);

	hdr.exprm_opt.magic = __bpf_htons(0xeB9F);
	ret = bpf_load_hdr_opt(skops, &hdr.exprm_opt, माप(hdr.exprm_opt),
			       load_flags);
	अगर (ret != 4 || hdr.exprm_opt.len != 4 ||
	    hdr.exprm_opt.kind != TCPOPT_EXP ||
	    hdr.exprm_opt.magic != __bpf_htons(0xeB9F))
		RET_CG_ERR(ret);

	अगर (!check_syn)
		वापस CG_OK;

	/* Test loading from skops->syn_skb अगर sk_state == TCP_NEW_SYN_RECV
	 *
	 * Test loading from tp->saved_syn क्रम other sk_state.
	 */
	ret = bpf_माला_लोockopt(skops, SOL_TCP, TCP_BPF_SYN_IP, &hdr.ip6,
			     माप(hdr.ip6));
	अगर (ret != -ENOSPC)
		RET_CG_ERR(ret);

	अगर (hdr.ip6.saddr.s6_addr16[7] != last_addr16_n ||
	    hdr.ip6.daddr.s6_addr16[7] != last_addr16_n)
		RET_CG_ERR(0);

	ret = bpf_माला_लोockopt(skops, SOL_TCP, TCP_BPF_SYN_IP, &hdr, माप(hdr));
	अगर (ret < 0)
		RET_CG_ERR(ret);

	pth = (काष्ठा tcphdr *)(&hdr.ip6 + 1);
	अगर (pth->dest != passive_lport_n || pth->source != active_lport_n)
		RET_CG_ERR(0);

	ret = bpf_माला_लोockopt(skops, SOL_TCP, TCP_BPF_SYN, &hdr, माप(hdr));
	अगर (ret < 0)
		RET_CG_ERR(ret);

	अगर (hdr.th.dest != passive_lport_n || hdr.th.source != active_lport_n)
		RET_CG_ERR(0);

	वापस CG_OK;
पूर्ण

अटल पूर्णांक check_active_syn_in(काष्ठा bpf_sock_ops *skops)
अणु
	वापस __check_active_hdr_in(skops, true);
पूर्ण

अटल पूर्णांक check_active_hdr_in(काष्ठा bpf_sock_ops *skops)
अणु
	काष्ठा tcphdr *th;

	अगर (__check_active_hdr_in(skops, false) == CG_ERR)
		वापस CG_ERR;

	th = skops->skb_data;
	अगर (th + 1 > skops->skb_data_end)
		RET_CG_ERR(0);

	अगर (tcp_hdrlen(th) < skops->skb_len)
		nr_data++;

	अगर (th->fin)
		nr_fin++;

	अगर (th->ack && !th->fin && tcp_hdrlen(th) == skops->skb_len)
		nr_pure_ack++;

	वापस CG_OK;
पूर्ण

अटल पूर्णांक active_opt_len(काष्ठा bpf_sock_ops *skops)
अणु
	पूर्णांक err;

	/* Reserve more than enough to allow the -EEXIST test in
	 * the ग_लिखो_active_opt().
	 */
	err = bpf_reserve_hdr_opt(skops, 12, 0);
	अगर (err)
		RET_CG_ERR(err);

	वापस CG_OK;
पूर्ण

अटल पूर्णांक ग_लिखो_active_opt(काष्ठा bpf_sock_ops *skops)
अणु
	काष्ठा tcp_exprm_opt exprm_opt = अणुपूर्ण;
	काष्ठा tcp_opt win_scale_opt = अणुपूर्ण;
	काष्ठा tcp_opt reg_opt = अणुपूर्ण;
	काष्ठा tcphdr *th;
	पूर्णांक err, ret;

	exprm_opt.kind = TCPOPT_EXP;
	exprm_opt.len = 4;
	exprm_opt.magic = __bpf_htons(0xeB9F);

	reg_opt.kind = 0xB9;
	reg_opt.len = 4;
	reg_opt.data[0] = 0xfa;
	reg_opt.data[1] = 0xce;

	win_scale_opt.kind = TCPOPT_WINDOW;

	err = bpf_store_hdr_opt(skops, &exprm_opt, माप(exprm_opt), 0);
	अगर (err)
		RET_CG_ERR(err);

	/* Store the same exprm option */
	err = bpf_store_hdr_opt(skops, &exprm_opt, माप(exprm_opt), 0);
	अगर (err != -EEXIST)
		RET_CG_ERR(err);

	err = bpf_store_hdr_opt(skops, &reg_opt, माप(reg_opt), 0);
	अगर (err)
		RET_CG_ERR(err);
	err = bpf_store_hdr_opt(skops, &reg_opt, माप(reg_opt), 0);
	अगर (err != -EEXIST)
		RET_CG_ERR(err);

	/* Check the option has been written and can be searched */
	ret = bpf_load_hdr_opt(skops, &exprm_opt, माप(exprm_opt), 0);
	अगर (ret != 4 || exprm_opt.len != 4 || exprm_opt.kind != TCPOPT_EXP ||
	    exprm_opt.magic != __bpf_htons(0xeB9F))
		RET_CG_ERR(ret);

	reg_opt.len = 0;
	ret = bpf_load_hdr_opt(skops, &reg_opt, माप(reg_opt), 0);
	अगर (ret != 4 || reg_opt.len != 4 || reg_opt.kind != 0xB9 ||
	    reg_opt.data[0] != 0xfa || reg_opt.data[1] != 0xce)
		RET_CG_ERR(ret);

	th = skops->skb_data;
	अगर (th + 1 > skops->skb_data_end)
		RET_CG_ERR(0);

	अगर (th->syn) अणु
		active_lport_h = skops->local_port;
		active_lport_n = th->source;

		/* Search the win scale option written by kernel
		 * in the SYN packet.
		 */
		ret = bpf_load_hdr_opt(skops, &win_scale_opt,
				       माप(win_scale_opt), 0);
		अगर (ret != 3 || win_scale_opt.len != 3 ||
		    win_scale_opt.kind != TCPOPT_WINDOW)
			RET_CG_ERR(ret);

		/* Write the win scale option that kernel
		 * has alपढ़ोy written.
		 */
		err = bpf_store_hdr_opt(skops, &win_scale_opt,
					माप(win_scale_opt), 0);
		अगर (err != -EEXIST)
			RET_CG_ERR(err);
	पूर्ण

	वापस CG_OK;
पूर्ण

अटल पूर्णांक handle_hdr_opt_len(काष्ठा bpf_sock_ops *skops)
अणु
	__u8 tcp_flags = skops_tcp_flags(skops);

	अगर ((tcp_flags & TCPHDR_SYNACK) == TCPHDR_SYNACK)
		/* Check the SYN from bpf_sock_ops_kern->syn_skb */
		वापस check_active_syn_in(skops);

	/* Passive side should have cleared the ग_लिखो hdr cb by now */
	अगर (skops->local_port == passive_lport_h)
		RET_CG_ERR(0);

	वापस active_opt_len(skops);
पूर्ण

अटल पूर्णांक handle_ग_लिखो_hdr_opt(काष्ठा bpf_sock_ops *skops)
अणु
	अगर (skops->local_port == passive_lport_h)
		RET_CG_ERR(0);

	वापस ग_लिखो_active_opt(skops);
पूर्ण

अटल पूर्णांक handle_parse_hdr(काष्ठा bpf_sock_ops *skops)
अणु
	/* Passive side is not writing any non-standard/unknown
	 * option, so the active side should never be called.
	 */
	अगर (skops->local_port == active_lport_h)
		RET_CG_ERR(0);

	वापस check_active_hdr_in(skops);
पूर्ण

अटल पूर्णांक handle_passive_estab(काष्ठा bpf_sock_ops *skops)
अणु
	पूर्णांक err;

	/* No more ग_लिखो hdr cb */
	bpf_sock_ops_cb_flags_set(skops,
				  skops->bpf_sock_ops_cb_flags &
				  ~BPF_SOCK_OPS_WRITE_HDR_OPT_CB_FLAG);

	/* Recheck the SYN but check the tp->saved_syn this समय */
	err = check_active_syn_in(skops);
	अगर (err == CG_ERR)
		वापस err;

	nr_syn++;

	/* The ack has header option written by the active side also */
	वापस check_active_hdr_in(skops);
पूर्ण

SEC("sockops/misc_estab")
पूर्णांक misc_estab(काष्ठा bpf_sock_ops *skops)
अणु
	पूर्णांक true_val = 1;

	चयन (skops->op) अणु
	हाल BPF_SOCK_OPS_TCP_LISTEN_CB:
		passive_lport_h = skops->local_port;
		passive_lport_n = __bpf_htons(passive_lport_h);
		bpf_setsockopt(skops, SOL_TCP, TCP_SAVE_SYN,
			       &true_val, माप(true_val));
		set_hdr_cb_flags(skops, 0);
		अवरोध;
	हाल BPF_SOCK_OPS_TCP_CONNECT_CB:
		set_hdr_cb_flags(skops, 0);
		अवरोध;
	हाल BPF_SOCK_OPS_PARSE_HDR_OPT_CB:
		वापस handle_parse_hdr(skops);
	हाल BPF_SOCK_OPS_HDR_OPT_LEN_CB:
		वापस handle_hdr_opt_len(skops);
	हाल BPF_SOCK_OPS_WRITE_HDR_OPT_CB:
		वापस handle_ग_लिखो_hdr_opt(skops);
	हाल BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB:
		वापस handle_passive_estab(skops);
	पूर्ण

	वापस CG_OK;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
