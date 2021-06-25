<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#समावेश <मानकघोष.स>
#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <linux/tcp.h>
#समावेश <linux/socket.h>
#समावेश <linux/bpf.h>
#समावेश <linux/types.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_endian.h>
#घोषणा BPF_PROG_TEST_TCP_HDR_OPTIONS
#समावेश "test_tcp_hdr_options.h"

#अगर_अघोषित माप_field
#घोषणा माप_field(TYPE, MEMBER) माप((((TYPE *)0)->MEMBER))
#पूर्ण_अगर

__u8 test_kind = TCPOPT_EXP;
__u16 test_magic = 0xeB9F;
__u32 inherit_cb_flags = 0;

काष्ठा bpf_test_option passive_synack_out = अणुपूर्ण;
काष्ठा bpf_test_option passive_fin_out	= अणुपूर्ण;

काष्ठा bpf_test_option passive_estab_in = अणुपूर्ण;
काष्ठा bpf_test_option passive_fin_in	= अणुपूर्ण;

काष्ठा bpf_test_option active_syn_out	= अणुपूर्ण;
काष्ठा bpf_test_option active_fin_out	= अणुपूर्ण;

काष्ठा bpf_test_option active_estab_in	= अणुपूर्ण;
काष्ठा bpf_test_option active_fin_in	= अणुपूर्ण;

काष्ठा अणु
	__uपूर्णांक(type, BPF_MAP_TYPE_SK_STORAGE);
	__uपूर्णांक(map_flags, BPF_F_NO_PREALLOC);
	__type(key, पूर्णांक);
	__type(value, काष्ठा hdr_stg);
पूर्ण hdr_stg_map SEC(".maps");

अटल bool skops_want_cookie(स्थिर काष्ठा bpf_sock_ops *skops)
अणु
	वापस skops->args[0] == BPF_WRITE_HDR_TCP_SYNACK_COOKIE;
पूर्ण

अटल bool skops_current_mss(स्थिर काष्ठा bpf_sock_ops *skops)
अणु
	वापस skops->args[0] == BPF_WRITE_HDR_TCP_CURRENT_MSS;
पूर्ण

अटल __u8 option_total_len(__u8 flags)
अणु
	__u8 i, len = 1; /* +1 क्रम flags */

	अगर (!flags)
		वापस 0;

	/* RESEND bit करोes not use a byte */
	क्रम (i = OPTION_RESEND + 1; i < __NR_OPTION_FLAGS; i++)
		len += !!TEST_OPTION_FLAGS(flags, i);

	अगर (test_kind == TCPOPT_EXP)
		वापस len + TCP_BPF_EXPOPT_BASE_LEN;
	अन्यथा
		वापस len + 2; /* +1 kind, +1 kind-len */
पूर्ण

अटल व्योम ग_लिखो_test_option(स्थिर काष्ठा bpf_test_option *test_opt,
			      __u8 *data)
अणु
	__u8 offset = 0;

	data[offset++] = test_opt->flags;
	अगर (TEST_OPTION_FLAGS(test_opt->flags, OPTION_MAX_DELACK_MS))
		data[offset++] = test_opt->max_delack_ms;

	अगर (TEST_OPTION_FLAGS(test_opt->flags, OPTION_RAND))
		data[offset++] = test_opt->अक्रम;
पूर्ण

अटल पूर्णांक store_option(काष्ठा bpf_sock_ops *skops,
			स्थिर काष्ठा bpf_test_option *test_opt)
अणु
	जोड़ अणु
		काष्ठा tcp_exprm_opt exprm;
		काष्ठा tcp_opt regular;
	पूर्ण ग_लिखो_opt;
	पूर्णांक err;

	अगर (test_kind == TCPOPT_EXP) अणु
		ग_लिखो_opt.exprm.kind = TCPOPT_EXP;
		ग_लिखो_opt.exprm.len = option_total_len(test_opt->flags);
		ग_लिखो_opt.exprm.magic = __bpf_htons(test_magic);
		ग_लिखो_opt.exprm.data32 = 0;
		ग_लिखो_test_option(test_opt, ग_लिखो_opt.exprm.data);
		err = bpf_store_hdr_opt(skops, &ग_लिखो_opt.exprm,
					माप(ग_लिखो_opt.exprm), 0);
	पूर्ण अन्यथा अणु
		ग_लिखो_opt.regular.kind = test_kind;
		ग_लिखो_opt.regular.len = option_total_len(test_opt->flags);
		ग_लिखो_opt.regular.data32 = 0;
		ग_लिखो_test_option(test_opt, ग_लिखो_opt.regular.data);
		err = bpf_store_hdr_opt(skops, &ग_लिखो_opt.regular,
					माप(ग_लिखो_opt.regular), 0);
	पूर्ण

	अगर (err)
		RET_CG_ERR(err);

	वापस CG_OK;
पूर्ण

अटल पूर्णांक parse_test_option(काष्ठा bpf_test_option *opt, स्थिर __u8 *start)
अणु
	opt->flags = *start++;

	अगर (TEST_OPTION_FLAGS(opt->flags, OPTION_MAX_DELACK_MS))
		opt->max_delack_ms = *start++;

	अगर (TEST_OPTION_FLAGS(opt->flags, OPTION_RAND))
		opt->अक्रम = *start++;

	वापस 0;
पूर्ण

अटल पूर्णांक load_option(काष्ठा bpf_sock_ops *skops,
		       काष्ठा bpf_test_option *test_opt, bool from_syn)
अणु
	जोड़ अणु
		काष्ठा tcp_exprm_opt exprm;
		काष्ठा tcp_opt regular;
	पूर्ण search_opt;
	पूर्णांक ret, load_flags = from_syn ? BPF_LOAD_HDR_OPT_TCP_SYN : 0;

	अगर (test_kind == TCPOPT_EXP) अणु
		search_opt.exprm.kind = TCPOPT_EXP;
		search_opt.exprm.len = 4;
		search_opt.exprm.magic = __bpf_htons(test_magic);
		search_opt.exprm.data32 = 0;
		ret = bpf_load_hdr_opt(skops, &search_opt.exprm,
				       माप(search_opt.exprm), load_flags);
		अगर (ret < 0)
			वापस ret;
		वापस parse_test_option(test_opt, search_opt.exprm.data);
	पूर्ण अन्यथा अणु
		search_opt.regular.kind = test_kind;
		search_opt.regular.len = 0;
		search_opt.regular.data32 = 0;
		ret = bpf_load_hdr_opt(skops, &search_opt.regular,
				       माप(search_opt.regular), load_flags);
		अगर (ret < 0)
			वापस ret;
		वापस parse_test_option(test_opt, search_opt.regular.data);
	पूर्ण
पूर्ण

अटल पूर्णांक synack_opt_len(काष्ठा bpf_sock_ops *skops)
अणु
	काष्ठा bpf_test_option test_opt = अणुपूर्ण;
	__u8 optlen;
	पूर्णांक err;

	अगर (!passive_synack_out.flags)
		वापस CG_OK;

	err = load_option(skops, &test_opt, true);

	/* bpf_test_option is not found */
	अगर (err == -ENOMSG)
		वापस CG_OK;

	अगर (err)
		RET_CG_ERR(err);

	optlen = option_total_len(passive_synack_out.flags);
	अगर (optlen) अणु
		err = bpf_reserve_hdr_opt(skops, optlen, 0);
		अगर (err)
			RET_CG_ERR(err);
	पूर्ण

	वापस CG_OK;
पूर्ण

अटल पूर्णांक ग_लिखो_synack_opt(काष्ठा bpf_sock_ops *skops)
अणु
	काष्ठा bpf_test_option opt;

	अगर (!passive_synack_out.flags)
		/* We should not even be called since no header
		 * space has been reserved.
		 */
		RET_CG_ERR(0);

	opt = passive_synack_out;
	अगर (skops_want_cookie(skops))
		SET_OPTION_FLAGS(opt.flags, OPTION_RESEND);

	वापस store_option(skops, &opt);
पूर्ण

अटल पूर्णांक syn_opt_len(काष्ठा bpf_sock_ops *skops)
अणु
	__u8 optlen;
	पूर्णांक err;

	अगर (!active_syn_out.flags)
		वापस CG_OK;

	optlen = option_total_len(active_syn_out.flags);
	अगर (optlen) अणु
		err = bpf_reserve_hdr_opt(skops, optlen, 0);
		अगर (err)
			RET_CG_ERR(err);
	पूर्ण

	वापस CG_OK;
पूर्ण

अटल पूर्णांक ग_लिखो_syn_opt(काष्ठा bpf_sock_ops *skops)
अणु
	अगर (!active_syn_out.flags)
		RET_CG_ERR(0);

	वापस store_option(skops, &active_syn_out);
पूर्ण

अटल पूर्णांक fin_opt_len(काष्ठा bpf_sock_ops *skops)
अणु
	काष्ठा bpf_test_option *opt;
	काष्ठा hdr_stg *hdr_stg;
	__u8 optlen;
	पूर्णांक err;

	अगर (!skops->sk)
		RET_CG_ERR(0);

	hdr_stg = bpf_sk_storage_get(&hdr_stg_map, skops->sk, शून्य, 0);
	अगर (!hdr_stg)
		RET_CG_ERR(0);

	अगर (hdr_stg->active)
		opt = &active_fin_out;
	अन्यथा
		opt = &passive_fin_out;

	optlen = option_total_len(opt->flags);
	अगर (optlen) अणु
		err = bpf_reserve_hdr_opt(skops, optlen, 0);
		अगर (err)
			RET_CG_ERR(err);
	पूर्ण

	वापस CG_OK;
पूर्ण

अटल पूर्णांक ग_लिखो_fin_opt(काष्ठा bpf_sock_ops *skops)
अणु
	काष्ठा bpf_test_option *opt;
	काष्ठा hdr_stg *hdr_stg;

	अगर (!skops->sk)
		RET_CG_ERR(0);

	hdr_stg = bpf_sk_storage_get(&hdr_stg_map, skops->sk, शून्य, 0);
	अगर (!hdr_stg)
		RET_CG_ERR(0);

	अगर (hdr_stg->active)
		opt = &active_fin_out;
	अन्यथा
		opt = &passive_fin_out;

	अगर (!opt->flags)
		RET_CG_ERR(0);

	वापस store_option(skops, opt);
पूर्ण

अटल पूर्णांक resend_in_ack(काष्ठा bpf_sock_ops *skops)
अणु
	काष्ठा hdr_stg *hdr_stg;

	अगर (!skops->sk)
		वापस -1;

	hdr_stg = bpf_sk_storage_get(&hdr_stg_map, skops->sk, शून्य, 0);
	अगर (!hdr_stg)
		वापस -1;

	वापस !!hdr_stg->resend_syn;
पूर्ण

अटल पूर्णांक nodata_opt_len(काष्ठा bpf_sock_ops *skops)
अणु
	पूर्णांक resend;

	resend = resend_in_ack(skops);
	अगर (resend < 0)
		RET_CG_ERR(0);

	अगर (resend)
		वापस syn_opt_len(skops);

	वापस CG_OK;
पूर्ण

अटल पूर्णांक ग_लिखो_nodata_opt(काष्ठा bpf_sock_ops *skops)
अणु
	पूर्णांक resend;

	resend = resend_in_ack(skops);
	अगर (resend < 0)
		RET_CG_ERR(0);

	अगर (resend)
		वापस ग_लिखो_syn_opt(skops);

	वापस CG_OK;
पूर्ण

अटल पूर्णांक data_opt_len(काष्ठा bpf_sock_ops *skops)
अणु
	/* Same as the nodata version.  Mostly to show
	 * an example usage on skops->skb_len.
	 */
	वापस nodata_opt_len(skops);
पूर्ण

अटल पूर्णांक ग_लिखो_data_opt(काष्ठा bpf_sock_ops *skops)
अणु
	वापस ग_लिखो_nodata_opt(skops);
पूर्ण

अटल पूर्णांक current_mss_opt_len(काष्ठा bpf_sock_ops *skops)
अणु
	/* Reserve maximum that may be needed */
	पूर्णांक err;

	err = bpf_reserve_hdr_opt(skops, option_total_len(OPTION_MASK), 0);
	अगर (err)
		RET_CG_ERR(err);

	वापस CG_OK;
पूर्ण

अटल पूर्णांक handle_hdr_opt_len(काष्ठा bpf_sock_ops *skops)
अणु
	__u8 tcp_flags = skops_tcp_flags(skops);

	अगर ((tcp_flags & TCPHDR_SYNACK) == TCPHDR_SYNACK)
		वापस synack_opt_len(skops);

	अगर (tcp_flags & TCPHDR_SYN)
		वापस syn_opt_len(skops);

	अगर (tcp_flags & TCPHDR_FIN)
		वापस fin_opt_len(skops);

	अगर (skops_current_mss(skops))
		/* The kernel is calculating the MSS */
		वापस current_mss_opt_len(skops);

	अगर (skops->skb_len)
		वापस data_opt_len(skops);

	वापस nodata_opt_len(skops);
पूर्ण

अटल पूर्णांक handle_ग_लिखो_hdr_opt(काष्ठा bpf_sock_ops *skops)
अणु
	__u8 tcp_flags = skops_tcp_flags(skops);
	काष्ठा tcphdr *th;

	अगर ((tcp_flags & TCPHDR_SYNACK) == TCPHDR_SYNACK)
		वापस ग_लिखो_synack_opt(skops);

	अगर (tcp_flags & TCPHDR_SYN)
		वापस ग_लिखो_syn_opt(skops);

	अगर (tcp_flags & TCPHDR_FIN)
		वापस ग_लिखो_fin_opt(skops);

	th = skops->skb_data;
	अगर (th + 1 > skops->skb_data_end)
		RET_CG_ERR(0);

	अगर (skops->skb_len > tcp_hdrlen(th))
		वापस ग_लिखो_data_opt(skops);

	वापस ग_लिखो_nodata_opt(skops);
पूर्ण

अटल पूर्णांक set_delack_max(काष्ठा bpf_sock_ops *skops, __u8 max_delack_ms)
अणु
	__u32 max_delack_us = max_delack_ms * 1000;

	वापस bpf_setsockopt(skops, SOL_TCP, TCP_BPF_DELACK_MAX,
			      &max_delack_us, माप(max_delack_us));
पूर्ण

अटल पूर्णांक set_rto_min(काष्ठा bpf_sock_ops *skops, __u8 peer_max_delack_ms)
अणु
	__u32 min_rto_us = peer_max_delack_ms * 1000;

	वापस bpf_setsockopt(skops, SOL_TCP, TCP_BPF_RTO_MIN, &min_rto_us,
			      माप(min_rto_us));
पूर्ण

अटल पूर्णांक handle_active_estab(काष्ठा bpf_sock_ops *skops)
अणु
	काष्ठा hdr_stg init_stg = अणु
		.active = true,
	पूर्ण;
	पूर्णांक err;

	err = load_option(skops, &active_estab_in, false);
	अगर (err && err != -ENOMSG)
		RET_CG_ERR(err);

	init_stg.resend_syn = TEST_OPTION_FLAGS(active_estab_in.flags,
						OPTION_RESEND);
	अगर (!skops->sk || !bpf_sk_storage_get(&hdr_stg_map, skops->sk,
					      &init_stg,
					      BPF_SK_STORAGE_GET_F_CREATE))
		RET_CG_ERR(0);

	अगर (init_stg.resend_syn)
		/* Don't clear the ग_लिखो_hdr cb now because
		 * the ACK may get lost and retransmit may
		 * be needed.
		 *
		 * PARSE_ALL_HDR cb flag is set to learn अगर this
		 * resend_syn option has received by the peer.
		 *
		 * The header option will be resent until a valid
		 * packet is received at handle_parse_hdr()
		 * and all hdr cb flags will be cleared in
		 * handle_parse_hdr().
		 */
		set_parse_all_hdr_cb_flags(skops);
	अन्यथा अगर (!active_fin_out.flags)
		/* No options will be written from now */
		clear_hdr_cb_flags(skops);

	अगर (active_syn_out.max_delack_ms) अणु
		err = set_delack_max(skops, active_syn_out.max_delack_ms);
		अगर (err)
			RET_CG_ERR(err);
	पूर्ण

	अगर (active_estab_in.max_delack_ms) अणु
		err = set_rto_min(skops, active_estab_in.max_delack_ms);
		अगर (err)
			RET_CG_ERR(err);
	पूर्ण

	वापस CG_OK;
पूर्ण

अटल पूर्णांक handle_passive_estab(काष्ठा bpf_sock_ops *skops)
अणु
	काष्ठा hdr_stg init_stg = अणुपूर्ण;
	काष्ठा tcphdr *th;
	पूर्णांक err;

	inherit_cb_flags = skops->bpf_sock_ops_cb_flags;

	err = load_option(skops, &passive_estab_in, true);
	अगर (err == -ENOENT) अणु
		/* saved_syn is not found. It was in syncookie mode.
		 * We have asked the active side to resend the options
		 * in ACK, so try to find the bpf_test_option from ACK now.
		 */
		err = load_option(skops, &passive_estab_in, false);
		init_stg.syncookie = true;
	पूर्ण

	/* ENOMSG: The bpf_test_option is not found which is fine.
	 * Bail out now क्रम all other errors.
	 */
	अगर (err && err != -ENOMSG)
		RET_CG_ERR(err);

	th = skops->skb_data;
	अगर (th + 1 > skops->skb_data_end)
		RET_CG_ERR(0);

	अगर (th->syn) अणु
		/* Fastखोलो */

		/* Cannot clear cb_flags to stop ग_लिखो_hdr cb.
		 * synack is not sent yet क्रम fast खोलो.
		 * Even it was, the synack may need to be retransmitted.
		 *
		 * PARSE_ALL_HDR cb flag is set to learn
		 * अगर synack has reached the peer.
		 * All cb_flags will be cleared in handle_parse_hdr().
		 */
		set_parse_all_hdr_cb_flags(skops);
		init_stg.fastखोलो = true;
	पूर्ण अन्यथा अगर (!passive_fin_out.flags) अणु
		/* No options will be written from now */
		clear_hdr_cb_flags(skops);
	पूर्ण

	अगर (!skops->sk ||
	    !bpf_sk_storage_get(&hdr_stg_map, skops->sk, &init_stg,
				BPF_SK_STORAGE_GET_F_CREATE))
		RET_CG_ERR(0);

	अगर (passive_synack_out.max_delack_ms) अणु
		err = set_delack_max(skops, passive_synack_out.max_delack_ms);
		अगर (err)
			RET_CG_ERR(err);
	पूर्ण

	अगर (passive_estab_in.max_delack_ms) अणु
		err = set_rto_min(skops, passive_estab_in.max_delack_ms);
		अगर (err)
			RET_CG_ERR(err);
	पूर्ण

	वापस CG_OK;
पूर्ण

अटल पूर्णांक handle_parse_hdr(काष्ठा bpf_sock_ops *skops)
अणु
	काष्ठा hdr_stg *hdr_stg;
	काष्ठा tcphdr *th;

	अगर (!skops->sk)
		RET_CG_ERR(0);

	th = skops->skb_data;
	अगर (th + 1 > skops->skb_data_end)
		RET_CG_ERR(0);

	hdr_stg = bpf_sk_storage_get(&hdr_stg_map, skops->sk, शून्य, 0);
	अगर (!hdr_stg)
		RET_CG_ERR(0);

	अगर (hdr_stg->resend_syn || hdr_stg->fastखोलो)
		/* The PARSE_ALL_HDR cb flag was turned on
		 * to ensure that the previously written
		 * options have reached the peer.
		 * Those previously written option includes:
		 *     - Active side: resend_syn in ACK during syncookie
		 *      or
		 *     - Passive side: SYNACK during fastखोलो
		 *
		 * A valid packet has been received here after
		 * the 3WHS, so the PARSE_ALL_HDR cb flag
		 * can be cleared now.
		 */
		clear_parse_all_hdr_cb_flags(skops);

	अगर (hdr_stg->resend_syn && !active_fin_out.flags)
		/* Active side resent the syn option in ACK
		 * because the server was in syncookie mode.
		 * A valid packet has been received, so
		 * clear header cb flags अगर there is no
		 * more option to send.
		 */
		clear_hdr_cb_flags(skops);

	अगर (hdr_stg->fastखोलो && !passive_fin_out.flags)
		/* Passive side was in fastखोलो.
		 * A valid packet has been received, so
		 * the SYNACK has reached the peer.
		 * Clear header cb flags अगर there is no more
		 * option to send.
		 */
		clear_hdr_cb_flags(skops);

	अगर (th->fin) अणु
		काष्ठा bpf_test_option *fin_opt;
		पूर्णांक err;

		अगर (hdr_stg->active)
			fin_opt = &active_fin_in;
		अन्यथा
			fin_opt = &passive_fin_in;

		err = load_option(skops, fin_opt, false);
		अगर (err && err != -ENOMSG)
			RET_CG_ERR(err);
	पूर्ण

	वापस CG_OK;
पूर्ण

SEC("sockops/estab")
पूर्णांक estab(काष्ठा bpf_sock_ops *skops)
अणु
	पूर्णांक true_val = 1;

	चयन (skops->op) अणु
	हाल BPF_SOCK_OPS_TCP_LISTEN_CB:
		bpf_setsockopt(skops, SOL_TCP, TCP_SAVE_SYN,
			       &true_val, माप(true_val));
		set_hdr_cb_flags(skops, BPF_SOCK_OPS_STATE_CB_FLAG);
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
	हाल BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB:
		वापस handle_active_estab(skops);
	पूर्ण

	वापस CG_OK;
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
