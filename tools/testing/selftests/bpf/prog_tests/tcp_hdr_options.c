<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */

#घोषणा _GNU_SOURCE
#समावेश <sched.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/socket.h>
#समावेश <linux/compiler.h>

#समावेश "test_progs.h"
#समावेश "cgroup_helpers.h"
#समावेश "network_helpers.h"
#समावेश "test_tcp_hdr_options.h"
#समावेश "test_tcp_hdr_options.skel.h"
#समावेश "test_misc_tcp_hdr_options.skel.h"

#घोषणा LO_ADDR6 "::1"
#घोषणा CG_NAME "/tcpbpf-hdr-opt-test"

अटल काष्ठा bpf_test_option exp_passive_estab_in;
अटल काष्ठा bpf_test_option exp_active_estab_in;
अटल काष्ठा bpf_test_option exp_passive_fin_in;
अटल काष्ठा bpf_test_option exp_active_fin_in;
अटल काष्ठा hdr_stg exp_passive_hdr_stg;
अटल काष्ठा hdr_stg exp_active_hdr_stg = अणु .active = true, पूर्ण;

अटल काष्ठा test_misc_tcp_hdr_options *misc_skel;
अटल काष्ठा test_tcp_hdr_options *skel;
अटल पूर्णांक lport_linum_map_fd;
अटल पूर्णांक hdr_stg_map_fd;
अटल __u32 duration;
अटल पूर्णांक cg_fd;

काष्ठा sk_fds अणु
	पूर्णांक srv_fd;
	पूर्णांक passive_fd;
	पूर्णांक active_fd;
	पूर्णांक passive_lport;
	पूर्णांक active_lport;
पूर्ण;

अटल पूर्णांक create_netns(व्योम)
अणु
	अगर (CHECK(unshare(CLONE_NEWNET), "create netns",
		  "unshare(CLONE_NEWNET): %s (%d)",
		  म_त्रुटि(त्रुटि_सं), त्रुटि_सं))
		वापस -1;

	अगर (CHECK(प्रणाली("ip link set dev lo up"), "run ip cmd",
		  "failed to bring lo link up\n"))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_sysctl(स्थिर अक्षर *sysctl, स्थिर अक्षर *value)
अणु
	पूर्णांक fd, err, len;

	fd = खोलो(sysctl, O_WRONLY);
	अगर (CHECK(fd == -1, "open sysctl", "open(%s): %s (%d)\n",
		  sysctl, म_त्रुटि(त्रुटि_सं), त्रुटि_सं))
		वापस -1;

	len = म_माप(value);
	err = ग_लिखो(fd, value, len);
	बंद(fd);
	अगर (CHECK(err != len, "write sysctl",
		  "write(%s, %s): err:%d %s (%d)\n",
		  sysctl, value, err, म_त्रुटि(त्रुटि_सं), त्रुटि_सं))
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_hdr_stg(स्थिर काष्ठा hdr_stg *hdr_stg, स्थिर अक्षर *prefix)
अणु
	ख_लिखो(मानक_त्रुटि, "%s{active:%u, resend_syn:%u, syncookie:%u, fastopen:%u}\n",
		prefix ? : "", hdr_stg->active, hdr_stg->resend_syn,
		hdr_stg->syncookie, hdr_stg->fastखोलो);
पूर्ण

अटल व्योम prपूर्णांक_option(स्थिर काष्ठा bpf_test_option *opt, स्थिर अक्षर *prefix)
अणु
	ख_लिखो(मानक_त्रुटि, "%s{flags:0x%x, max_delack_ms:%u, rand:0x%x}\n",
		prefix ? : "", opt->flags, opt->max_delack_ms, opt->अक्रम);
पूर्ण

अटल व्योम sk_fds_बंद(काष्ठा sk_fds *sk_fds)
अणु
	बंद(sk_fds->srv_fd);
	बंद(sk_fds->passive_fd);
	बंद(sk_fds->active_fd);
पूर्ण

अटल पूर्णांक sk_fds_shutकरोwn(काष्ठा sk_fds *sk_fds)
अणु
	पूर्णांक ret, abyte;

	shutकरोwn(sk_fds->active_fd, SHUT_WR);
	ret = पढ़ो(sk_fds->passive_fd, &abyte, माप(abyte));
	अगर (CHECK(ret != 0, "read-after-shutdown(passive_fd):",
		  "ret:%d %s (%d)\n",
		  ret, म_त्रुटि(त्रुटि_सं), त्रुटि_सं))
		वापस -1;

	shutकरोwn(sk_fds->passive_fd, SHUT_WR);
	ret = पढ़ो(sk_fds->active_fd, &abyte, माप(abyte));
	अगर (CHECK(ret != 0, "read-after-shutdown(active_fd):",
		  "ret:%d %s (%d)\n",
		  ret, म_त्रुटि(त्रुटि_सं), त्रुटि_सं))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक sk_fds_connect(काष्ठा sk_fds *sk_fds, bool fast_खोलो)
अणु
	स्थिर अक्षर fast[] = "FAST!!!";
	काष्ठा sockaddr_in6 addr6;
	socklen_t len;

	sk_fds->srv_fd = start_server(AF_INET6, SOCK_STREAM, LO_ADDR6, 0, 0);
	अगर (CHECK(sk_fds->srv_fd == -1, "start_server", "%s (%d)\n",
		  म_त्रुटि(त्रुटि_सं), त्रुटि_सं))
		जाओ error;

	अगर (fast_खोलो)
		sk_fds->active_fd = fastखोलो_connect(sk_fds->srv_fd, fast,
						     माप(fast), 0);
	अन्यथा
		sk_fds->active_fd = connect_to_fd(sk_fds->srv_fd, 0);

	अगर (CHECK_FAIL(sk_fds->active_fd == -1)) अणु
		बंद(sk_fds->srv_fd);
		जाओ error;
	पूर्ण

	len = माप(addr6);
	अगर (CHECK(माला_लोockname(sk_fds->srv_fd, (काष्ठा sockaddr *)&addr6,
			      &len), "getsockname(srv_fd)", "%s (%d)\n",
		  म_त्रुटि(त्रुटि_सं), त्रुटि_सं))
		जाओ error_बंद;
	sk_fds->passive_lport = ntohs(addr6.sin6_port);

	len = माप(addr6);
	अगर (CHECK(माला_लोockname(sk_fds->active_fd, (काष्ठा sockaddr *)&addr6,
			      &len), "getsockname(active_fd)", "%s (%d)\n",
		  म_त्रुटि(त्रुटि_सं), त्रुटि_सं))
		जाओ error_बंद;
	sk_fds->active_lport = ntohs(addr6.sin6_port);

	sk_fds->passive_fd = accept(sk_fds->srv_fd, शून्य, 0);
	अगर (CHECK(sk_fds->passive_fd == -1, "accept(srv_fd)", "%s (%d)\n",
		  म_त्रुटि(त्रुटि_सं), त्रुटि_सं))
		जाओ error_बंद;

	अगर (fast_खोलो) अणु
		अक्षर bytes_in[माप(fast)];
		पूर्णांक ret;

		ret = पढ़ो(sk_fds->passive_fd, bytes_in, माप(bytes_in));
		अगर (CHECK(ret != माप(fast), "read fastopen syn data",
			  "expected=%lu actual=%d\n", माप(fast), ret)) अणु
			बंद(sk_fds->passive_fd);
			जाओ error_बंद;
		पूर्ण
	पूर्ण

	वापस 0;

error_बंद:
	बंद(sk_fds->active_fd);
	बंद(sk_fds->srv_fd);

error:
	स_रखो(sk_fds, -1, माप(*sk_fds));
	वापस -1;
पूर्ण

अटल पूर्णांक check_hdr_opt(स्थिर काष्ठा bpf_test_option *exp,
			 स्थिर काष्ठा bpf_test_option *act,
			 स्थिर अक्षर *hdr_desc)
अणु
	अगर (CHECK(स_भेद(exp, act, माप(*exp)),
		  "expected-vs-actual", "unexpected %s\n", hdr_desc)) अणु
		prपूर्णांक_option(exp, "expected: ");
		prपूर्णांक_option(act, "  actual: ");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_hdr_stg(स्थिर काष्ठा hdr_stg *exp, पूर्णांक fd,
			 स्थिर अक्षर *stg_desc)
अणु
	काष्ठा hdr_stg act;

	अगर (CHECK(bpf_map_lookup_elem(hdr_stg_map_fd, &fd, &act),
		  "map_lookup(hdr_stg_map_fd)", "%s %s (%d)\n",
		  stg_desc, म_त्रुटि(त्रुटि_सं), त्रुटि_सं))
		वापस -1;

	अगर (CHECK(स_भेद(exp, &act, माप(*exp)),
		  "expected-vs-actual", "unexpected %s\n", stg_desc)) अणु
		prपूर्णांक_hdr_stg(exp, "expected: ");
		prपूर्णांक_hdr_stg(&act, "  actual: ");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_error_linum(स्थिर काष्ठा sk_fds *sk_fds)
अणु
	अचिन्हित पूर्णांक nr_errors = 0;
	काष्ठा linum_err linum_err;
	पूर्णांक lport;

	lport = sk_fds->passive_lport;
	अगर (!bpf_map_lookup_elem(lport_linum_map_fd, &lport, &linum_err)) अणु
		ख_लिखो(मानक_त्रुटि,
			"bpf prog error out at lport:passive(%d), linum:%u err:%d\n",
			lport, linum_err.linum, linum_err.err);
		nr_errors++;
	पूर्ण

	lport = sk_fds->active_lport;
	अगर (!bpf_map_lookup_elem(lport_linum_map_fd, &lport, &linum_err)) अणु
		ख_लिखो(मानक_त्रुटि,
			"bpf prog error out at lport:active(%d), linum:%u err:%d\n",
			lport, linum_err.linum, linum_err.err);
		nr_errors++;
	पूर्ण

	वापस nr_errors;
पूर्ण

अटल व्योम check_hdr_and_बंद_fds(काष्ठा sk_fds *sk_fds)
अणु
	स्थिर __u32 expected_inherit_cb_flags =
		BPF_SOCK_OPS_PARSE_UNKNOWN_HDR_OPT_CB_FLAG |
		BPF_SOCK_OPS_WRITE_HDR_OPT_CB_FLAG |
		BPF_SOCK_OPS_STATE_CB_FLAG;

	अगर (sk_fds_shutकरोwn(sk_fds))
		जाओ check_linum;

	अगर (CHECK(expected_inherit_cb_flags != skel->bss->inherit_cb_flags,
		  "Unexpected inherit_cb_flags", "0x%x != 0x%x\n",
		  skel->bss->inherit_cb_flags, expected_inherit_cb_flags))
		जाओ check_linum;

	अगर (check_hdr_stg(&exp_passive_hdr_stg, sk_fds->passive_fd,
			  "passive_hdr_stg"))
		जाओ check_linum;

	अगर (check_hdr_stg(&exp_active_hdr_stg, sk_fds->active_fd,
			  "active_hdr_stg"))
		जाओ check_linum;

	अगर (check_hdr_opt(&exp_passive_estab_in, &skel->bss->passive_estab_in,
			  "passive_estab_in"))
		जाओ check_linum;

	अगर (check_hdr_opt(&exp_active_estab_in, &skel->bss->active_estab_in,
			  "active_estab_in"))
		जाओ check_linum;

	अगर (check_hdr_opt(&exp_passive_fin_in, &skel->bss->passive_fin_in,
			  "passive_fin_in"))
		जाओ check_linum;

	check_hdr_opt(&exp_active_fin_in, &skel->bss->active_fin_in,
		      "active_fin_in");

check_linum:
	CHECK_FAIL(check_error_linum(sk_fds));
	sk_fds_बंद(sk_fds);
पूर्ण

अटल व्योम prepare_out(व्योम)
अणु
	skel->bss->active_syn_out = exp_passive_estab_in;
	skel->bss->passive_synack_out = exp_active_estab_in;

	skel->bss->active_fin_out = exp_passive_fin_in;
	skel->bss->passive_fin_out = exp_active_fin_in;
पूर्ण

अटल व्योम reset_test(व्योम)
अणु
	माप_प्रकार optsize = माप(काष्ठा bpf_test_option);
	पूर्णांक lport, err;

	स_रखो(&skel->bss->passive_synack_out, 0, optsize);
	स_रखो(&skel->bss->passive_fin_out, 0, optsize);

	स_रखो(&skel->bss->passive_estab_in, 0, optsize);
	स_रखो(&skel->bss->passive_fin_in, 0, optsize);

	स_रखो(&skel->bss->active_syn_out, 0, optsize);
	स_रखो(&skel->bss->active_fin_out, 0, optsize);

	स_रखो(&skel->bss->active_estab_in, 0, optsize);
	स_रखो(&skel->bss->active_fin_in, 0, optsize);

	skel->bss->inherit_cb_flags = 0;

	skel->data->test_kind = TCPOPT_EXP;
	skel->data->test_magic = 0xeB9F;

	स_रखो(&exp_passive_estab_in, 0, optsize);
	स_रखो(&exp_active_estab_in, 0, optsize);
	स_रखो(&exp_passive_fin_in, 0, optsize);
	स_रखो(&exp_active_fin_in, 0, optsize);

	स_रखो(&exp_passive_hdr_stg, 0, माप(exp_passive_hdr_stg));
	स_रखो(&exp_active_hdr_stg, 0, माप(exp_active_hdr_stg));
	exp_active_hdr_stg.active = true;

	err = bpf_map_get_next_key(lport_linum_map_fd, शून्य, &lport);
	जबतक (!err) अणु
		bpf_map_delete_elem(lport_linum_map_fd, &lport);
		err = bpf_map_get_next_key(lport_linum_map_fd, &lport, &lport);
	पूर्ण
पूर्ण

अटल व्योम fastखोलो_estab(व्योम)
अणु
	काष्ठा bpf_link *link;
	काष्ठा sk_fds sk_fds;

	hdr_stg_map_fd = bpf_map__fd(skel->maps.hdr_stg_map);
	lport_linum_map_fd = bpf_map__fd(skel->maps.lport_linum_map);

	exp_passive_estab_in.flags = OPTION_F_RAND | OPTION_F_MAX_DELACK_MS;
	exp_passive_estab_in.अक्रम = 0xfa;
	exp_passive_estab_in.max_delack_ms = 11;

	exp_active_estab_in.flags = OPTION_F_RAND | OPTION_F_MAX_DELACK_MS;
	exp_active_estab_in.अक्रम = 0xce;
	exp_active_estab_in.max_delack_ms = 22;

	exp_passive_hdr_stg.fastखोलो = true;

	prepare_out();

	/* Allow fastखोलो without fastखोलो cookie */
	अगर (ग_लिखो_sysctl("/proc/sys/net/ipv4/tcp_fastopen", "1543"))
		वापस;

	link = bpf_program__attach_cgroup(skel->progs.estab, cg_fd);
	अगर (CHECK(IS_ERR(link), "attach_cgroup(estab)", "err: %ld\n",
		  PTR_ERR(link)))
		वापस;

	अगर (sk_fds_connect(&sk_fds, true)) अणु
		bpf_link__destroy(link);
		वापस;
	पूर्ण

	check_hdr_and_बंद_fds(&sk_fds);
	bpf_link__destroy(link);
पूर्ण

अटल व्योम syncookie_estab(व्योम)
अणु
	काष्ठा bpf_link *link;
	काष्ठा sk_fds sk_fds;

	hdr_stg_map_fd = bpf_map__fd(skel->maps.hdr_stg_map);
	lport_linum_map_fd = bpf_map__fd(skel->maps.lport_linum_map);

	exp_passive_estab_in.flags = OPTION_F_RAND | OPTION_F_MAX_DELACK_MS;
	exp_passive_estab_in.अक्रम = 0xfa;
	exp_passive_estab_in.max_delack_ms = 11;

	exp_active_estab_in.flags = OPTION_F_RAND | OPTION_F_MAX_DELACK_MS |
					OPTION_F_RESEND;
	exp_active_estab_in.अक्रम = 0xce;
	exp_active_estab_in.max_delack_ms = 22;

	exp_passive_hdr_stg.syncookie = true;
	exp_active_hdr_stg.resend_syn = true,

	prepare_out();

	/* Clear the RESEND to ensure the bpf prog can learn
	 * want_cookie and set the RESEND by itself.
	 */
	skel->bss->passive_synack_out.flags &= ~OPTION_F_RESEND;

	/* Enक्रमce syncookie mode */
	अगर (ग_लिखो_sysctl("/proc/sys/net/ipv4/tcp_syncookies", "2"))
		वापस;

	link = bpf_program__attach_cgroup(skel->progs.estab, cg_fd);
	अगर (CHECK(IS_ERR(link), "attach_cgroup(estab)", "err: %ld\n",
		  PTR_ERR(link)))
		वापस;

	अगर (sk_fds_connect(&sk_fds, false)) अणु
		bpf_link__destroy(link);
		वापस;
	पूर्ण

	check_hdr_and_बंद_fds(&sk_fds);
	bpf_link__destroy(link);
पूर्ण

अटल व्योम fin(व्योम)
अणु
	काष्ठा bpf_link *link;
	काष्ठा sk_fds sk_fds;

	hdr_stg_map_fd = bpf_map__fd(skel->maps.hdr_stg_map);
	lport_linum_map_fd = bpf_map__fd(skel->maps.lport_linum_map);

	exp_passive_fin_in.flags = OPTION_F_RAND;
	exp_passive_fin_in.अक्रम = 0xfa;

	exp_active_fin_in.flags = OPTION_F_RAND;
	exp_active_fin_in.अक्रम = 0xce;

	prepare_out();

	अगर (ग_लिखो_sysctl("/proc/sys/net/ipv4/tcp_syncookies", "1"))
		वापस;

	link = bpf_program__attach_cgroup(skel->progs.estab, cg_fd);
	अगर (CHECK(IS_ERR(link), "attach_cgroup(estab)", "err: %ld\n",
		  PTR_ERR(link)))
		वापस;

	अगर (sk_fds_connect(&sk_fds, false)) अणु
		bpf_link__destroy(link);
		वापस;
	पूर्ण

	check_hdr_and_बंद_fds(&sk_fds);
	bpf_link__destroy(link);
पूर्ण

अटल व्योम __simple_estab(bool exprm)
अणु
	काष्ठा bpf_link *link;
	काष्ठा sk_fds sk_fds;

	hdr_stg_map_fd = bpf_map__fd(skel->maps.hdr_stg_map);
	lport_linum_map_fd = bpf_map__fd(skel->maps.lport_linum_map);

	exp_passive_estab_in.flags = OPTION_F_RAND | OPTION_F_MAX_DELACK_MS;
	exp_passive_estab_in.अक्रम = 0xfa;
	exp_passive_estab_in.max_delack_ms = 11;

	exp_active_estab_in.flags = OPTION_F_RAND | OPTION_F_MAX_DELACK_MS;
	exp_active_estab_in.अक्रम = 0xce;
	exp_active_estab_in.max_delack_ms = 22;

	prepare_out();

	अगर (!exprm) अणु
		skel->data->test_kind = 0xB9;
		skel->data->test_magic = 0;
	पूर्ण

	अगर (ग_लिखो_sysctl("/proc/sys/net/ipv4/tcp_syncookies", "1"))
		वापस;

	link = bpf_program__attach_cgroup(skel->progs.estab, cg_fd);
	अगर (CHECK(IS_ERR(link), "attach_cgroup(estab)", "err: %ld\n",
		  PTR_ERR(link)))
		वापस;

	अगर (sk_fds_connect(&sk_fds, false)) अणु
		bpf_link__destroy(link);
		वापस;
	पूर्ण

	check_hdr_and_बंद_fds(&sk_fds);
	bpf_link__destroy(link);
पूर्ण

अटल व्योम no_exprm_estab(व्योम)
अणु
	__simple_estab(false);
पूर्ण

अटल व्योम simple_estab(व्योम)
अणु
	__simple_estab(true);
पूर्ण

अटल व्योम misc(व्योम)
अणु
	स्थिर अक्षर send_msg[] = "MISC!!!";
	अक्षर recv_msg[माप(send_msg)];
	स्थिर अचिन्हित पूर्णांक nr_data = 2;
	काष्ठा bpf_link *link;
	काष्ठा sk_fds sk_fds;
	पूर्णांक i, ret;

	lport_linum_map_fd = bpf_map__fd(misc_skel->maps.lport_linum_map);

	अगर (ग_लिखो_sysctl("/proc/sys/net/ipv4/tcp_syncookies", "1"))
		वापस;

	link = bpf_program__attach_cgroup(misc_skel->progs.misc_estab, cg_fd);
	अगर (CHECK(IS_ERR(link), "attach_cgroup(misc_estab)", "err: %ld\n",
		  PTR_ERR(link)))
		वापस;

	अगर (sk_fds_connect(&sk_fds, false)) अणु
		bpf_link__destroy(link);
		वापस;
	पूर्ण

	क्रम (i = 0; i < nr_data; i++) अणु
		/* MSG_EOR to ensure skb will not be combined */
		ret = send(sk_fds.active_fd, send_msg, माप(send_msg),
			   MSG_EOR);
		अगर (CHECK(ret != माप(send_msg), "send(msg)", "ret:%d\n",
			  ret))
			जाओ check_linum;

		ret = पढ़ो(sk_fds.passive_fd, recv_msg, माप(recv_msg));
		अगर (CHECK(ret != माप(send_msg), "read(msg)", "ret:%d\n",
			  ret))
			जाओ check_linum;
	पूर्ण

	अगर (sk_fds_shutकरोwn(&sk_fds))
		जाओ check_linum;

	CHECK(misc_skel->bss->nr_syn != 1, "unexpected nr_syn",
	      "expected (1) != actual (%u)\n",
		misc_skel->bss->nr_syn);

	CHECK(misc_skel->bss->nr_data != nr_data, "unexpected nr_data",
	      "expected (%u) != actual (%u)\n",
	      nr_data, misc_skel->bss->nr_data);

	/* The last ACK may have been delayed, so it is either 1 or 2. */
	CHECK(misc_skel->bss->nr_pure_ack != 1 &&
	      misc_skel->bss->nr_pure_ack != 2,
	      "unexpected nr_pure_ack",
	      "expected (1 or 2) != actual (%u)\n",
		misc_skel->bss->nr_pure_ack);

	CHECK(misc_skel->bss->nr_fin != 1, "unexpected nr_fin",
	      "expected (1) != actual (%u)\n",
	      misc_skel->bss->nr_fin);

check_linum:
	CHECK_FAIL(check_error_linum(&sk_fds));
	sk_fds_बंद(&sk_fds);
	bpf_link__destroy(link);
पूर्ण

काष्ठा test अणु
	स्थिर अक्षर *desc;
	व्योम (*run)(व्योम);
पूर्ण;

#घोषणा DEF_TEST(name) अणु #name, name पूर्ण
अटल काष्ठा test tests[] = अणु
	DEF_TEST(simple_estab),
	DEF_TEST(no_exprm_estab),
	DEF_TEST(syncookie_estab),
	DEF_TEST(fastखोलो_estab),
	DEF_TEST(fin),
	DEF_TEST(misc),
पूर्ण;

व्योम test_tcp_hdr_options(व्योम)
अणु
	पूर्णांक i;

	skel = test_tcp_hdr_options__खोलो_and_load();
	अगर (CHECK(!skel, "open and load skel", "failed"))
		वापस;

	misc_skel = test_misc_tcp_hdr_options__खोलो_and_load();
	अगर (CHECK(!misc_skel, "open and load misc test skel", "failed"))
		जाओ skel_destroy;

	cg_fd = test__join_cgroup(CG_NAME);
	अगर (CHECK_FAIL(cg_fd < 0))
		जाओ skel_destroy;

	क्रम (i = 0; i < ARRAY_SIZE(tests); i++) अणु
		अगर (!test__start_subtest(tests[i].desc))
			जारी;

		अगर (create_netns())
			अवरोध;

		tests[i].run();

		reset_test();
	पूर्ण

	बंद(cg_fd);
skel_destroy:
	test_misc_tcp_hdr_options__destroy(misc_skel);
	test_tcp_hdr_options__destroy(skel);
पूर्ण
