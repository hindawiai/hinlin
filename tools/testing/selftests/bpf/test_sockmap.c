<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017-2018 Covalent IO, Inc. http://covalent.io
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/socket.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/select.h>
#समावेश <netinet/in.h>
#समावेश <arpa/inet.h>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <संकेत.स>
#समावेश <fcntl.h>
#समावेश <sys/रुको.h>
#समावेश <समय.स>
#समावेश <sched.h>

#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <sys/types.h>
#समावेश <sys/sendfile.h>

#समावेश <linux/netlink.h>
#समावेश <linux/socket.h>
#समावेश <linux/sock_diag.h>
#समावेश <linux/bpf.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/tls.h>
#समावेश <निश्चित.स>
#समावेश <libgen.h>

#समावेश <getopt.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "bpf_util.h"
#समावेश "bpf_rlimit.h"
#समावेश "cgroup_helpers.h"

पूर्णांक running;
अटल व्योम running_handler(पूर्णांक a);

#अगर_अघोषित TCP_ULP
# define TCP_ULP 31
#पूर्ण_अगर
#अगर_अघोषित SOL_TLS
# define SOL_TLS 282
#पूर्ण_अगर

/* अक्रमomly selected ports क्रम testing on lo */
#घोषणा S1_PORT 10000
#घोषणा S2_PORT 10001

#घोषणा BPF_SOCKMAP_खाताNAME  "test_sockmap_kern.o"
#घोषणा BPF_SOCKHASH_खाताNAME "test_sockhash_kern.o"
#घोषणा CG_PATH "/sockmap"

/* global sockets */
पूर्णांक s1, s2, c1, c2, p1, p2;
पूर्णांक test_cnt;
पूर्णांक passed;
पूर्णांक failed;
पूर्णांक map_fd[9];
काष्ठा bpf_map *maps[9];
पूर्णांक prog_fd[11];

पूर्णांक txmsg_pass;
पूर्णांक txmsg_redir;
पूर्णांक txmsg_drop;
पूर्णांक txmsg_apply;
पूर्णांक txmsg_cork;
पूर्णांक txmsg_start;
पूर्णांक txmsg_end;
पूर्णांक txmsg_start_push;
पूर्णांक txmsg_end_push;
पूर्णांक txmsg_start_pop;
पूर्णांक txmsg_pop;
पूर्णांक txmsg_ingress;
पूर्णांक txmsg_redir_skb;
पूर्णांक txmsg_ktls_skb;
पूर्णांक txmsg_ktls_skb_drop;
पूर्णांक txmsg_ktls_skb_redir;
पूर्णांक ktls;
पूर्णांक peek_flag;
पूर्णांक skb_use_parser;
पूर्णांक txmsg_omit_skb_parser;

अटल स्थिर काष्ठा option दीर्घ_options[] = अणु
	अणु"help",	no_argument,		शून्य, 'h' पूर्ण,
	अणु"cgroup",	required_argument,	शून्य, 'c' पूर्ण,
	अणु"rate",	required_argument,	शून्य, 'r' पूर्ण,
	अणु"verbose",	optional_argument,	शून्य, 'v' पूर्ण,
	अणु"iov_count",	required_argument,	शून्य, 'i' पूर्ण,
	अणु"length",	required_argument,	शून्य, 'l' पूर्ण,
	अणु"test",	required_argument,	शून्य, 't' पूर्ण,
	अणु"data_test",   no_argument,		शून्य, 'd' पूर्ण,
	अणु"txmsg",		no_argument,	&txmsg_pass,  1  पूर्ण,
	अणु"txmsg_redir",		no_argument,	&txmsg_redir, 1  पूर्ण,
	अणु"txmsg_drop",		no_argument,	&txmsg_drop, 1 पूर्ण,
	अणु"txmsg_apply",	required_argument,	शून्य, 'a'पूर्ण,
	अणु"txmsg_cork",	required_argument,	शून्य, 'k'पूर्ण,
	अणु"txmsg_start", required_argument,	शून्य, 's'पूर्ण,
	अणु"txmsg_end",	required_argument,	शून्य, 'e'पूर्ण,
	अणु"txmsg_start_push", required_argument,	शून्य, 'p'पूर्ण,
	अणु"txmsg_end_push",   required_argument,	शून्य, 'q'पूर्ण,
	अणु"txmsg_start_pop",  required_argument,	शून्य, 'w'पूर्ण,
	अणु"txmsg_pop",	     required_argument,	शून्य, 'x'पूर्ण,
	अणु"txmsg_ingress", no_argument,		&txmsg_ingress, 1 पूर्ण,
	अणु"txmsg_redir_skb", no_argument,	&txmsg_redir_skb, 1 पूर्ण,
	अणु"ktls", no_argument,			&ktls, 1 पूर्ण,
	अणु"peek", no_argument,			&peek_flag, 1 पूर्ण,
	अणु"txmsg_omit_skb_parser", no_argument,      &txmsg_omit_skb_parser, 1पूर्ण,
	अणु"whitelist", required_argument,	शून्य, 'n' पूर्ण,
	अणु"blacklist", required_argument,	शून्य, 'b' पूर्ण,
	अणु0, 0, शून्य, 0 पूर्ण
पूर्ण;

काष्ठा test_env अणु
	स्थिर अक्षर *type;
	स्थिर अक्षर *subtest;
	स्थिर अक्षर *prepend;

	पूर्णांक test_num;
	पूर्णांक subtest_num;

	पूर्णांक succ_cnt;
	पूर्णांक fail_cnt;
	पूर्णांक fail_last;
पूर्ण;

काष्ठा test_env env;

काष्ठा sockmap_options अणु
	पूर्णांक verbose;
	bool base;
	bool sendpage;
	bool data_test;
	bool drop_expected;
	पूर्णांक iov_count;
	पूर्णांक iov_length;
	पूर्णांक rate;
	अक्षर *map;
	अक्षर *whitelist;
	अक्षर *blacklist;
	अक्षर *prepend;
पूर्ण;

काष्ठा _test अणु
	अक्षर *title;
	व्योम (*tester)(पूर्णांक cg_fd, काष्ठा sockmap_options *opt);
पूर्ण;

अटल व्योम test_start(व्योम)
अणु
	env.subtest_num++;
पूर्ण

अटल व्योम test_fail(व्योम)
अणु
	env.fail_cnt++;
पूर्ण

अटल व्योम test_pass(व्योम)
अणु
	env.succ_cnt++;
पूर्ण

अटल व्योम test_reset(व्योम)
अणु
	txmsg_start = txmsg_end = 0;
	txmsg_start_pop = txmsg_pop = 0;
	txmsg_start_push = txmsg_end_push = 0;
	txmsg_pass = txmsg_drop = txmsg_redir = 0;
	txmsg_apply = txmsg_cork = 0;
	txmsg_ingress = txmsg_redir_skb = 0;
	txmsg_ktls_skb = txmsg_ktls_skb_drop = txmsg_ktls_skb_redir = 0;
	txmsg_omit_skb_parser = 0;
	skb_use_parser = 0;
पूर्ण

अटल पूर्णांक test_start_subtest(स्थिर काष्ठा _test *t, काष्ठा sockmap_options *o)
अणु
	env.type = o->map;
	env.subtest = t->title;
	env.prepend = o->prepend;
	env.test_num++;
	env.subtest_num = 0;
	env.fail_last = env.fail_cnt;
	test_reset();
	वापस 0;
पूर्ण

अटल व्योम test_end_subtest(व्योम)
अणु
	पूर्णांक error = env.fail_cnt - env.fail_last;
	पूर्णांक type = म_भेद(env.type, BPF_SOCKMAP_खाताNAME);

	अगर (!error)
		test_pass();

	ख_लिखो(मानक_निकास, "#%2d/%2d %8s:%s:%s:%s\n",
		env.test_num, env.subtest_num,
		!type ? "sockmap" : "sockhash",
		env.prepend ? : "",
		env.subtest, error ? "FAIL" : "OK");
पूर्ण

अटल व्योम test_prपूर्णांक_results(व्योम)
अणु
	ख_लिखो(मानक_निकास, "Pass: %d Fail: %d\n",
		env.succ_cnt, env.fail_cnt);
पूर्ण

अटल व्योम usage(अक्षर *argv[])
अणु
	पूर्णांक i;

	म_लिखो(" Usage: %s --cgroup <cgroup_path>\n", argv[0]);
	म_लिखो(" options:\n");
	क्रम (i = 0; दीर्घ_options[i].name != 0; i++) अणु
		म_लिखो(" --%-12s", दीर्घ_options[i].name);
		अगर (दीर्घ_options[i].flag != शून्य)
			म_लिखो(" flag (internal value:%d)\n",
				*दीर्घ_options[i].flag);
		अन्यथा
			म_लिखो(" -%c\n", दीर्घ_options[i].val);
	पूर्ण
	म_लिखो("\n");
पूर्ण

अक्षर *sock_to_string(पूर्णांक s)
अणु
	अगर (s == c1)
		वापस "client1";
	अन्यथा अगर (s == c2)
		वापस "client2";
	अन्यथा अगर (s == s1)
		वापस "server1";
	अन्यथा अगर (s == s2)
		वापस "server2";
	अन्यथा अगर (s == p1)
		वापस "peer1";
	अन्यथा अगर (s == p2)
		वापस "peer2";
	अन्यथा
		वापस "unknown";
पूर्ण

अटल पूर्णांक sockmap_init_ktls(पूर्णांक verbose, पूर्णांक s)
अणु
	काष्ठा tls12_crypto_info_aes_gcm_128 tls_tx = अणु
		.info = अणु
			.version     = TLS_1_2_VERSION,
			.cipher_type = TLS_CIPHER_AES_GCM_128,
		पूर्ण,
	पूर्ण;
	काष्ठा tls12_crypto_info_aes_gcm_128 tls_rx = अणु
		.info = अणु
			.version     = TLS_1_2_VERSION,
			.cipher_type = TLS_CIPHER_AES_GCM_128,
		पूर्ण,
	पूर्ण;
	पूर्णांक so_buf = 6553500;
	पूर्णांक err;

	err = setsockopt(s, 6, TCP_ULP, "tls", माप("tls"));
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "setsockopt: TCP_ULP(%s) failed with error %i\n", sock_to_string(s), err);
		वापस -EINVAL;
	पूर्ण
	err = setsockopt(s, SOL_TLS, TLS_TX, (व्योम *)&tls_tx, माप(tls_tx));
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "setsockopt: TLS_TX(%s) failed with error %i\n", sock_to_string(s), err);
		वापस -EINVAL;
	पूर्ण
	err = setsockopt(s, SOL_TLS, TLS_RX, (व्योम *)&tls_rx, माप(tls_rx));
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "setsockopt: TLS_RX(%s) failed with error %i\n", sock_to_string(s), err);
		वापस -EINVAL;
	पूर्ण
	err = setsockopt(s, SOL_SOCKET, SO_SNDBUF, &so_buf, माप(so_buf));
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "setsockopt: (%s) failed sndbuf with error %i\n", sock_to_string(s), err);
		वापस -EINVAL;
	पूर्ण
	err = setsockopt(s, SOL_SOCKET, SO_RCVBUF, &so_buf, माप(so_buf));
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "setsockopt: (%s) failed rcvbuf with error %i\n", sock_to_string(s), err);
		वापस -EINVAL;
	पूर्ण

	अगर (verbose)
		ख_लिखो(मानक_निकास, "socket(%s) kTLS enabled\n", sock_to_string(s));
	वापस 0;
पूर्ण
अटल पूर्णांक sockmap_init_sockets(पूर्णांक verbose)
अणु
	पूर्णांक i, err, one = 1;
	काष्ठा sockaddr_in addr;
	पूर्णांक *fds[4] = अणु&s1, &s2, &c1, &c2पूर्ण;

	s1 = s2 = p1 = p2 = c1 = c2 = 0;

	/* Init sockets */
	क्रम (i = 0; i < 4; i++) अणु
		*fds[i] = socket(AF_INET, SOCK_STREAM, 0);
		अगर (*fds[i] < 0) अणु
			लिखो_त्रुटि("socket s1 failed()");
			वापस त्रुटि_सं;
		पूर्ण
	पूर्ण

	/* Allow reuse */
	क्रम (i = 0; i < 2; i++) अणु
		err = setsockopt(*fds[i], SOL_SOCKET, SO_REUSEADDR,
				 (अक्षर *)&one, माप(one));
		अगर (err) अणु
			लिखो_त्रुटि("setsockopt failed()");
			वापस त्रुटि_सं;
		पूर्ण
	पूर्ण

	/* Non-blocking sockets */
	क्रम (i = 0; i < 2; i++) अणु
		err = ioctl(*fds[i], FIONBIO, (अक्षर *)&one);
		अगर (err < 0) अणु
			लिखो_त्रुटि("ioctl s1 failed()");
			वापस त्रुटि_सं;
		पूर्ण
	पूर्ण

	/* Bind server sockets */
	स_रखो(&addr, 0, माप(काष्ठा sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	addr.sin_port = htons(S1_PORT);
	err = bind(s1, (काष्ठा sockaddr *)&addr, माप(addr));
	अगर (err < 0) अणु
		लिखो_त्रुटि("bind s1 failed()");
		वापस त्रुटि_सं;
	पूर्ण

	addr.sin_port = htons(S2_PORT);
	err = bind(s2, (काष्ठा sockaddr *)&addr, माप(addr));
	अगर (err < 0) अणु
		लिखो_त्रुटि("bind s2 failed()");
		वापस त्रुटि_सं;
	पूर्ण

	/* Listen server sockets */
	addr.sin_port = htons(S1_PORT);
	err = listen(s1, 32);
	अगर (err < 0) अणु
		लिखो_त्रुटि("listen s1 failed()");
		वापस त्रुटि_सं;
	पूर्ण

	addr.sin_port = htons(S2_PORT);
	err = listen(s2, 32);
	अगर (err < 0) अणु
		लिखो_त्रुटि("listen s1 failed()");
		वापस त्रुटि_सं;
	पूर्ण

	/* Initiate Connect */
	addr.sin_port = htons(S1_PORT);
	err = connect(c1, (काष्ठा sockaddr *)&addr, माप(addr));
	अगर (err < 0 && त्रुटि_सं != EINPROGRESS) अणु
		लिखो_त्रुटि("connect c1 failed()");
		वापस त्रुटि_सं;
	पूर्ण

	addr.sin_port = htons(S2_PORT);
	err = connect(c2, (काष्ठा sockaddr *)&addr, माप(addr));
	अगर (err < 0 && त्रुटि_सं != EINPROGRESS) अणु
		लिखो_त्रुटि("connect c2 failed()");
		वापस त्रुटि_सं;
	पूर्ण अन्यथा अगर (err < 0) अणु
		err = 0;
	पूर्ण

	/* Accept Connecrtions */
	p1 = accept(s1, शून्य, शून्य);
	अगर (p1 < 0) अणु
		लिखो_त्रुटि("accept s1 failed()");
		वापस त्रुटि_सं;
	पूर्ण

	p2 = accept(s2, शून्य, शून्य);
	अगर (p2 < 0) अणु
		लिखो_त्रुटि("accept s1 failed()");
		वापस त्रुटि_सं;
	पूर्ण

	अगर (verbose > 1) अणु
		म_लिखो("connected sockets: c1 <-> p1, c2 <-> p2\n");
		म_लिखो("cgroups binding: c1(%i) <-> s1(%i) - - - c2(%i) <-> s2(%i)\n",
			c1, s1, c2, s2);
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा msg_stats अणु
	माप_प्रकार bytes_sent;
	माप_प्रकार bytes_recvd;
	काष्ठा बारpec start;
	काष्ठा बारpec end;
पूर्ण;

अटल पूर्णांक msg_loop_sendpage(पूर्णांक fd, पूर्णांक iov_length, पूर्णांक cnt,
			     काष्ठा msg_stats *s,
			     काष्ठा sockmap_options *opt)
अणु
	bool drop = opt->drop_expected;
	अचिन्हित अक्षर k = 0;
	खाता *file;
	पूर्णांक i, fp;

	file = क्षणिक_ख();
	अगर (!file) अणु
		लिखो_त्रुटि("create file for sendpage");
		वापस 1;
	पूर्ण
	क्रम (i = 0; i < iov_length * cnt; i++, k++)
		ख_डालो(&k, माप(अक्षर), 1, file);
	ख_साफ(file);
	ख_जाओ(file, 0, शुरू_से);

	fp = fileno(file);

	घड़ी_समय_लो(CLOCK_MONOTONIC, &s->start);
	क्रम (i = 0; i < cnt; i++) अणु
		पूर्णांक sent;

		त्रुटि_सं = 0;
		sent = sendfile(fd, fp, शून्य, iov_length);

		अगर (!drop && sent < 0) अणु
			लिखो_त्रुटि("sendpage loop error");
			ख_बंद(file);
			वापस sent;
		पूर्ण अन्यथा अगर (drop && sent >= 0) अणु
			म_लिखो("sendpage loop error expected: %i errno %i\n",
			       sent, त्रुटि_सं);
			ख_बंद(file);
			वापस -EIO;
		पूर्ण

		अगर (sent > 0)
			s->bytes_sent += sent;
	पूर्ण
	घड़ी_समय_लो(CLOCK_MONOTONIC, &s->end);
	ख_बंद(file);
	वापस 0;
पूर्ण

अटल व्योम msg_मुक्त_iov(काष्ठा msghdr *msg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < msg->msg_iovlen; i++)
		मुक्त(msg->msg_iov[i].iov_base);
	मुक्त(msg->msg_iov);
	msg->msg_iov = शून्य;
	msg->msg_iovlen = 0;
पूर्ण

अटल पूर्णांक msg_alloc_iov(काष्ठा msghdr *msg,
			 पूर्णांक iov_count, पूर्णांक iov_length,
			 bool data, bool xmit)
अणु
	अचिन्हित अक्षर k = 0;
	काष्ठा iovec *iov;
	पूर्णांक i;

	iov = सुस्मृति(iov_count, माप(काष्ठा iovec));
	अगर (!iov)
		वापस त्रुटि_सं;

	क्रम (i = 0; i < iov_count; i++) अणु
		अचिन्हित अक्षर *d = सुस्मृति(iov_length, माप(अक्षर));

		अगर (!d) अणु
			ख_लिखो(मानक_त्रुटि, "iov_count %i/%i OOM\n", i, iov_count);
			जाओ unwind_iov;
		पूर्ण
		iov[i].iov_base = d;
		iov[i].iov_len = iov_length;

		अगर (data && xmit) अणु
			पूर्णांक j;

			क्रम (j = 0; j < iov_length; j++)
				d[j] = k++;
		पूर्ण
	पूर्ण

	msg->msg_iov = iov;
	msg->msg_iovlen = iov_count;

	वापस 0;
unwind_iov:
	क्रम (i--; i >= 0 ; i--)
		मुक्त(msg->msg_iov[i].iov_base);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक msg_verअगरy_data(काष्ठा msghdr *msg, पूर्णांक size, पूर्णांक chunk_sz)
अणु
	पूर्णांक i, j = 0, bytes_cnt = 0;
	अचिन्हित अक्षर k = 0;

	क्रम (i = 0; i < msg->msg_iovlen; i++) अणु
		अचिन्हित अक्षर *d = msg->msg_iov[i].iov_base;

		/* Special हाल test क्रम skb ingress + ktls */
		अगर (i == 0 && txmsg_ktls_skb) अणु
			अगर (msg->msg_iov[i].iov_len < 4)
				वापस -EIO;
			अगर (स_भेद(d, "PASS", 4) != 0) अणु
				ख_लिखो(मानक_त्रुटि,
					"detected skb data error with skb ingress update @iov[%i]:%i \"%02x %02x %02x %02x\" != \"PASS\"\n",
					i, 0, d[0], d[1], d[2], d[3]);
				वापस -EIO;
			पूर्ण
			j = 4; /* advance index past PASS header */
		पूर्ण

		क्रम (; j < msg->msg_iov[i].iov_len && size; j++) अणु
			अगर (d[j] != k++) अणु
				ख_लिखो(मानक_त्रुटि,
					"detected data corruption @iov[%i]:%i %02x != %02x, %02x ?= %02x\n",
					i, j, d[j], k - 1, d[j+1], k);
				वापस -EIO;
			पूर्ण
			bytes_cnt++;
			अगर (bytes_cnt == chunk_sz) अणु
				k = 0;
				bytes_cnt = 0;
			पूर्ण
			size--;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक msg_loop(पूर्णांक fd, पूर्णांक iov_count, पूर्णांक iov_length, पूर्णांक cnt,
		    काष्ठा msg_stats *s, bool tx,
		    काष्ठा sockmap_options *opt)
अणु
	काष्ठा msghdr msg = अणु0पूर्ण, msg_peek = अणु0पूर्ण;
	पूर्णांक err, i, flags = MSG_NOSIGNAL;
	bool drop = opt->drop_expected;
	bool data = opt->data_test;

	err = msg_alloc_iov(&msg, iov_count, iov_length, data, tx);
	अगर (err)
		जाओ out_त्रुटि_सं;
	अगर (peek_flag) अणु
		err = msg_alloc_iov(&msg_peek, iov_count, iov_length, data, tx);
		अगर (err)
			जाओ out_त्रुटि_सं;
	पूर्ण

	अगर (tx) अणु
		घड़ी_समय_लो(CLOCK_MONOTONIC, &s->start);
		क्रम (i = 0; i < cnt; i++) अणु
			पूर्णांक sent;

			त्रुटि_सं = 0;
			sent = sendmsg(fd, &msg, flags);

			अगर (!drop && sent < 0) अणु
				लिखो_त्रुटि("sendmsg loop error");
				जाओ out_त्रुटि_सं;
			पूर्ण अन्यथा अगर (drop && sent >= 0) अणु
				ख_लिखो(मानक_त्रुटि,
					"sendmsg loop error expected: %i errno %i\n",
					sent, त्रुटि_सं);
				त्रुटि_सं = -EIO;
				जाओ out_त्रुटि_सं;
			पूर्ण
			अगर (sent > 0)
				s->bytes_sent += sent;
		पूर्ण
		घड़ी_समय_लो(CLOCK_MONOTONIC, &s->end);
	पूर्ण अन्यथा अणु
		पूर्णांक slct, recvp = 0, recv, max_fd = fd;
		भग्न total_bytes, txmsg_pop_total;
		पूर्णांक fd_flags = O_NONBLOCK;
		काष्ठा समयval समयout;
		fd_set w;

		fcntl(fd, fd_flags);
		/* Account क्रम pop bytes noting each iteration of apply will
		 * call msg_pop_data helper so we need to account क्रम this
		 * by calculating the number of apply iterations. Note user
		 * of the tool can create हालs where no data is sent by
		 * manipulating pop/push/pull/etc. For example txmsg_apply 1
		 * with txmsg_pop 1 will try to apply 1B at a समय but each
		 * iteration will then pop 1B so no data will ever be sent.
		 * This is really only useful क्रम testing edge हालs in code
		 * paths.
		 */
		total_bytes = (भग्न)iov_count * (भग्न)iov_length * (भग्न)cnt;
		अगर (txmsg_apply)
			txmsg_pop_total = txmsg_pop * (total_bytes / txmsg_apply);
		अन्यथा
			txmsg_pop_total = txmsg_pop * cnt;
		total_bytes -= txmsg_pop_total;
		err = घड़ी_समय_लो(CLOCK_MONOTONIC, &s->start);
		अगर (err < 0)
			लिखो_त्रुटि("recv start time");
		जबतक (s->bytes_recvd < total_bytes) अणु
			अगर (txmsg_cork) अणु
				समयout.tv_sec = 0;
				समयout.tv_usec = 300000;
			पूर्ण अन्यथा अणु
				समयout.tv_sec = 3;
				समयout.tv_usec = 0;
			पूर्ण

			/* FD sets */
			FD_ZERO(&w);
			FD_SET(fd, &w);

			slct = select(max_fd + 1, &w, शून्य, शून्य, &समयout);
			अगर (slct == -1) अणु
				लिखो_त्रुटि("select()");
				घड़ी_समय_लो(CLOCK_MONOTONIC, &s->end);
				जाओ out_त्रुटि_सं;
			पूर्ण अन्यथा अगर (!slct) अणु
				अगर (opt->verbose)
					ख_लिखो(मानक_त्रुटि, "unexpected timeout: recved %zu/%f pop_total %f\n", s->bytes_recvd, total_bytes, txmsg_pop_total);
				त्रुटि_सं = -EIO;
				घड़ी_समय_लो(CLOCK_MONOTONIC, &s->end);
				जाओ out_त्रुटि_सं;
			पूर्ण

			त्रुटि_सं = 0;
			अगर (peek_flag) अणु
				flags |= MSG_PEEK;
				recvp = recvmsg(fd, &msg_peek, flags);
				अगर (recvp < 0) अणु
					अगर (त्रुटि_सं != EWOULDBLOCK) अणु
						घड़ी_समय_लो(CLOCK_MONOTONIC, &s->end);
						जाओ out_त्रुटि_सं;
					पूर्ण
				पूर्ण
				flags = 0;
			पूर्ण

			recv = recvmsg(fd, &msg, flags);
			अगर (recv < 0) अणु
				अगर (त्रुटि_सं != EWOULDBLOCK) अणु
					घड़ी_समय_लो(CLOCK_MONOTONIC, &s->end);
					लिखो_त्रुटि("recv failed()");
					जाओ out_त्रुटि_सं;
				पूर्ण
			पूर्ण

			s->bytes_recvd += recv;

			अगर (data) अणु
				पूर्णांक chunk_sz = opt->sendpage ?
						iov_length * cnt :
						iov_length * iov_count;

				त्रुटि_सं = msg_verअगरy_data(&msg, recv, chunk_sz);
				अगर (त्रुटि_सं) अणु
					लिखो_त्रुटि("data verify msg failed");
					जाओ out_त्रुटि_सं;
				पूर्ण
				अगर (recvp) अणु
					त्रुटि_सं = msg_verअगरy_data(&msg_peek,
								recvp,
								chunk_sz);
					अगर (त्रुटि_सं) अणु
						लिखो_त्रुटि("data verify msg_peek failed");
						जाओ out_त्रुटि_सं;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		घड़ी_समय_लो(CLOCK_MONOTONIC, &s->end);
	पूर्ण

	msg_मुक्त_iov(&msg);
	msg_मुक्त_iov(&msg_peek);
	वापस err;
out_त्रुटि_सं:
	msg_मुक्त_iov(&msg);
	msg_मुक्त_iov(&msg_peek);
	वापस त्रुटि_सं;
पूर्ण

अटल भग्न giga = 1000000000;

अटल अंतरभूत भग्न sentBps(काष्ठा msg_stats s)
अणु
	वापस s.bytes_sent / (s.end.tv_sec - s.start.tv_sec);
पूर्ण

अटल अंतरभूत भग्न recvdBps(काष्ठा msg_stats s)
अणु
	वापस s.bytes_recvd / (s.end.tv_sec - s.start.tv_sec);
पूर्ण

अटल पूर्णांक sendmsg_test(काष्ठा sockmap_options *opt)
अणु
	भग्न sent_Bps = 0, recvd_Bps = 0;
	पूर्णांक rx_fd, txpid, rxpid, err = 0;
	काष्ठा msg_stats s = अणु0पूर्ण;
	पूर्णांक iov_count = opt->iov_count;
	पूर्णांक iov_buf = opt->iov_length;
	पूर्णांक rx_status, tx_status;
	पूर्णांक cnt = opt->rate;

	त्रुटि_सं = 0;

	अगर (opt->base)
		rx_fd = p1;
	अन्यथा
		rx_fd = p2;

	अगर (ktls) अणु
		/* Redirecting पूर्णांकo non-TLS socket which sends पूर्णांकo a TLS
		 * socket is not a valid test. So in this हाल lets not
		 * enable kTLS but still run the test.
		 */
		अगर (!txmsg_redir || txmsg_ingress) अणु
			err = sockmap_init_ktls(opt->verbose, rx_fd);
			अगर (err)
				वापस err;
		पूर्ण
		err = sockmap_init_ktls(opt->verbose, c1);
		अगर (err)
			वापस err;
	पूर्ण

	rxpid = विभाजन();
	अगर (rxpid == 0) अणु
		iov_buf -= (txmsg_pop - txmsg_start_pop + 1);
		अगर (opt->drop_expected || txmsg_ktls_skb_drop)
			_निकास(0);

		अगर (!iov_buf) /* zero bytes sent हाल */
			_निकास(0);

		अगर (opt->sendpage)
			iov_count = 1;
		err = msg_loop(rx_fd, iov_count, iov_buf,
			       cnt, &s, false, opt);
		अगर (opt->verbose > 1)
			ख_लिखो(मानक_त्रुटि,
				"msg_loop_rx: iov_count %i iov_buf %i cnt %i err %i\n",
				iov_count, iov_buf, cnt, err);
		अगर (s.end.tv_sec - s.start.tv_sec) अणु
			sent_Bps = sentBps(s);
			recvd_Bps = recvdBps(s);
		पूर्ण
		अगर (opt->verbose > 1)
			ख_लिखो(मानक_निकास,
				"rx_sendmsg: TX: %zuB %fB/s %fGB/s RX: %zuB %fB/s %fGB/s %s\n",
				s.bytes_sent, sent_Bps, sent_Bps/giga,
				s.bytes_recvd, recvd_Bps, recvd_Bps/giga,
				peek_flag ? "(peek_msg)" : "");
		अगर (err && txmsg_cork)
			err = 0;
		निकास(err ? 1 : 0);
	पूर्ण अन्यथा अगर (rxpid == -1) अणु
		लिखो_त्रुटि("msg_loop_rx");
		वापस त्रुटि_सं;
	पूर्ण

	txpid = विभाजन();
	अगर (txpid == 0) अणु
		अगर (opt->sendpage)
			err = msg_loop_sendpage(c1, iov_buf, cnt, &s, opt);
		अन्यथा
			err = msg_loop(c1, iov_count, iov_buf,
				       cnt, &s, true, opt);

		अगर (err)
			ख_लिखो(मानक_त्रुटि,
				"msg_loop_tx: iov_count %i iov_buf %i cnt %i err %i\n",
				iov_count, iov_buf, cnt, err);
		अगर (s.end.tv_sec - s.start.tv_sec) अणु
			sent_Bps = sentBps(s);
			recvd_Bps = recvdBps(s);
		पूर्ण
		अगर (opt->verbose > 1)
			ख_लिखो(मानक_निकास,
				"tx_sendmsg: TX: %zuB %fB/s %f GB/s RX: %zuB %fB/s %fGB/s\n",
				s.bytes_sent, sent_Bps, sent_Bps/giga,
				s.bytes_recvd, recvd_Bps, recvd_Bps/giga);
		निकास(err ? 1 : 0);
	पूर्ण अन्यथा अगर (txpid == -1) अणु
		लिखो_त्रुटि("msg_loop_tx");
		वापस त्रुटि_सं;
	पूर्ण

	निश्चित(रुकोpid(rxpid, &rx_status, 0) == rxpid);
	निश्चित(रुकोpid(txpid, &tx_status, 0) == txpid);
	अगर (WIFEXITED(rx_status)) अणु
		err = WEXITSTATUS(rx_status);
		अगर (err) अणु
			ख_लिखो(मानक_त्रुटि, "rx thread exited with err %d.\n", err);
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (WIFEXITED(tx_status)) अणु
		err = WEXITSTATUS(tx_status);
		अगर (err)
			ख_लिखो(मानक_त्रुटि, "tx thread exited with err %d.\n", err);
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक क्रमever_ping_pong(पूर्णांक rate, काष्ठा sockmap_options *opt)
अणु
	काष्ठा समयval समयout;
	अक्षर buf[1024] = अणु0पूर्ण;
	पूर्णांक sc;

	समयout.tv_sec = 10;
	समयout.tv_usec = 0;

	/* Ping/Pong data from client to server */
	sc = send(c1, buf, माप(buf), 0);
	अगर (sc < 0) अणु
		लिखो_त्रुटि("send failed()");
		वापस sc;
	पूर्ण

	करो अणु
		पूर्णांक s, rc, i, max_fd = p2;
		fd_set w;

		/* FD sets */
		FD_ZERO(&w);
		FD_SET(c1, &w);
		FD_SET(c2, &w);
		FD_SET(p1, &w);
		FD_SET(p2, &w);

		s = select(max_fd + 1, &w, शून्य, शून्य, &समयout);
		अगर (s == -1) अणु
			लिखो_त्रुटि("select()");
			अवरोध;
		पूर्ण अन्यथा अगर (!s) अणु
			ख_लिखो(मानक_त्रुटि, "unexpected timeout\n");
			अवरोध;
		पूर्ण

		क्रम (i = 0; i <= max_fd && s > 0; ++i) अणु
			अगर (!FD_ISSET(i, &w))
				जारी;

			s--;

			rc = recv(i, buf, माप(buf), 0);
			अगर (rc < 0) अणु
				अगर (त्रुटि_सं != EWOULDBLOCK) अणु
					लिखो_त्रुटि("recv failed()");
					वापस rc;
				पूर्ण
			पूर्ण

			अगर (rc == 0) अणु
				बंद(i);
				अवरोध;
			पूर्ण

			sc = send(i, buf, rc, 0);
			अगर (sc < 0) अणु
				लिखो_त्रुटि("send failed()");
				वापस sc;
			पूर्ण
		पूर्ण

		अगर (rate)
			sleep(rate);

		अगर (opt->verbose) अणु
			म_लिखो(".");
			ख_साफ(मानक_निकास);

		पूर्ण
	पूर्ण जबतक (running);

	वापस 0;
पूर्ण

क्रमागत अणु
	SELFTESTS,
	PING_PONG,
	SENDMSG,
	BASE,
	BASE_SENDPAGE,
	SENDPAGE,
पूर्ण;

अटल पूर्णांक run_options(काष्ठा sockmap_options *options, पूर्णांक cg_fd,  पूर्णांक test)
अणु
	पूर्णांक i, key, next_key, err, tx_prog_fd = -1, zero = 0;

	/* If base test skip BPF setup */
	अगर (test == BASE || test == BASE_SENDPAGE)
		जाओ run;

	/* Attach programs to sockmap */
	अगर (!txmsg_omit_skb_parser) अणु
		err = bpf_prog_attach(prog_fd[0], map_fd[0],
				      BPF_SK_SKB_STREAM_PARSER, 0);
		अगर (err) अणु
			ख_लिखो(मानक_त्रुटि,
				"ERROR: bpf_prog_attach (sockmap %i->%i): %d (%s)\n",
				prog_fd[0], map_fd[0], err, म_त्रुटि(त्रुटि_सं));
			वापस err;
		पूर्ण
	पूर्ण

	err = bpf_prog_attach(prog_fd[1], map_fd[0],
				BPF_SK_SKB_STREAM_VERDICT, 0);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: bpf_prog_attach (sockmap): %d (%s)\n",
			err, म_त्रुटि(त्रुटि_सं));
		वापस err;
	पूर्ण

	/* Attach programs to TLS sockmap */
	अगर (txmsg_ktls_skb) अणु
		अगर (!txmsg_omit_skb_parser) अणु
			err = bpf_prog_attach(prog_fd[0], map_fd[8],
					      BPF_SK_SKB_STREAM_PARSER, 0);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_prog_attach (TLS sockmap %i->%i): %d (%s)\n",
					prog_fd[0], map_fd[8], err, म_त्रुटि(त्रुटि_सं));
				वापस err;
			पूर्ण
		पूर्ण

		err = bpf_prog_attach(prog_fd[2], map_fd[8],
				      BPF_SK_SKB_STREAM_VERDICT, 0);
		अगर (err) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: bpf_prog_attach (TLS sockmap): %d (%s)\n",
				err, म_त्रुटि(त्रुटि_सं));
			वापस err;
		पूर्ण
	पूर्ण

	/* Attach to cgroups */
	err = bpf_prog_attach(prog_fd[3], cg_fd, BPF_CGROUP_SOCK_OPS, 0);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: bpf_prog_attach (groups): %d (%s)\n",
			err, म_त्रुटि(त्रुटि_सं));
		वापस err;
	पूर्ण

run:
	err = sockmap_init_sockets(options->verbose);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: test socket failed: %d\n", err);
		जाओ out;
	पूर्ण

	/* Attach txmsg program to sockmap */
	अगर (txmsg_pass)
		tx_prog_fd = prog_fd[4];
	अन्यथा अगर (txmsg_redir)
		tx_prog_fd = prog_fd[5];
	अन्यथा अगर (txmsg_apply)
		tx_prog_fd = prog_fd[6];
	अन्यथा अगर (txmsg_cork)
		tx_prog_fd = prog_fd[7];
	अन्यथा अगर (txmsg_drop)
		tx_prog_fd = prog_fd[8];
	अन्यथा
		tx_prog_fd = 0;

	अगर (tx_prog_fd) अणु
		पूर्णांक redir_fd, i = 0;

		err = bpf_prog_attach(tx_prog_fd,
				      map_fd[1], BPF_SK_MSG_VERDICT, 0);
		अगर (err) अणु
			ख_लिखो(मानक_त्रुटि,
				"ERROR: bpf_prog_attach (txmsg): %d (%s)\n",
				err, म_त्रुटि(त्रुटि_सं));
			जाओ out;
		पूर्ण

		err = bpf_map_update_elem(map_fd[1], &i, &c1, BPF_ANY);
		अगर (err) अणु
			ख_लिखो(मानक_त्रुटि,
				"ERROR: bpf_map_update_elem (txmsg):  %d (%s\n",
				err, म_त्रुटि(त्रुटि_सं));
			जाओ out;
		पूर्ण

		अगर (txmsg_redir)
			redir_fd = c2;
		अन्यथा
			redir_fd = c1;

		err = bpf_map_update_elem(map_fd[2], &i, &redir_fd, BPF_ANY);
		अगर (err) अणु
			ख_लिखो(मानक_त्रुटि,
				"ERROR: bpf_map_update_elem (txmsg):  %d (%s\n",
				err, म_त्रुटि(त्रुटि_सं));
			जाओ out;
		पूर्ण

		अगर (txmsg_apply) अणु
			err = bpf_map_update_elem(map_fd[3],
						  &i, &txmsg_apply, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem (apply_bytes):  %d (%s\n",
					err, म_त्रुटि(त्रुटि_सं));
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (txmsg_cork) अणु
			err = bpf_map_update_elem(map_fd[4],
						  &i, &txmsg_cork, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem (cork_bytes):  %d (%s\n",
					err, म_त्रुटि(त्रुटि_सं));
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (txmsg_start) अणु
			err = bpf_map_update_elem(map_fd[5],
						  &i, &txmsg_start, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem (txmsg_start):  %d (%s)\n",
					err, म_त्रुटि(त्रुटि_सं));
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (txmsg_end) अणु
			i = 1;
			err = bpf_map_update_elem(map_fd[5],
						  &i, &txmsg_end, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem (txmsg_end):  %d (%s)\n",
					err, म_त्रुटि(त्रुटि_सं));
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (txmsg_start_push) अणु
			i = 2;
			err = bpf_map_update_elem(map_fd[5],
						  &i, &txmsg_start_push, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem (txmsg_start_push):  %d (%s)\n",
					err, म_त्रुटि(त्रुटि_सं));
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (txmsg_end_push) अणु
			i = 3;
			err = bpf_map_update_elem(map_fd[5],
						  &i, &txmsg_end_push, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem %i@%i (txmsg_end_push):  %d (%s)\n",
					txmsg_end_push, i, err, म_त्रुटि(त्रुटि_सं));
				जाओ out;
			पूर्ण
		पूर्ण

		अगर (txmsg_start_pop) अणु
			i = 4;
			err = bpf_map_update_elem(map_fd[5],
						  &i, &txmsg_start_pop, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem %i@%i (txmsg_start_pop):  %d (%s)\n",
					txmsg_start_pop, i, err, म_त्रुटि(त्रुटि_सं));
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			i = 4;
			bpf_map_update_elem(map_fd[5],
						  &i, &txmsg_start_pop, BPF_ANY);
		पूर्ण

		अगर (txmsg_pop) अणु
			i = 5;
			err = bpf_map_update_elem(map_fd[5],
						  &i, &txmsg_pop, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem %i@%i (txmsg_pop):  %d (%s)\n",
					txmsg_pop, i, err, म_त्रुटि(त्रुटि_सं));
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अणु
			i = 5;
			bpf_map_update_elem(map_fd[5],
					    &i, &txmsg_pop, BPF_ANY);

		पूर्ण

		अगर (txmsg_ingress) अणु
			पूर्णांक in = BPF_F_INGRESS;

			i = 0;
			err = bpf_map_update_elem(map_fd[6], &i, &in, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem (txmsg_ingress): %d (%s)\n",
					err, म_त्रुटि(त्रुटि_सं));
			पूर्ण
			i = 1;
			err = bpf_map_update_elem(map_fd[1], &i, &p1, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem (p1 txmsg): %d (%s)\n",
					err, म_त्रुटि(त्रुटि_सं));
			पूर्ण
			err = bpf_map_update_elem(map_fd[2], &i, &p1, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem (p1 redir): %d (%s)\n",
					err, म_त्रुटि(त्रुटि_सं));
			पूर्ण

			i = 2;
			err = bpf_map_update_elem(map_fd[2], &i, &p2, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem (p2 txmsg): %d (%s)\n",
					err, म_त्रुटि(त्रुटि_सं));
			पूर्ण
		पूर्ण

		अगर (txmsg_ktls_skb) अणु
			पूर्णांक ingress = BPF_F_INGRESS;

			i = 0;
			err = bpf_map_update_elem(map_fd[8], &i, &p2, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem (c1 sockmap): %d (%s)\n",
					err, म_त्रुटि(त्रुटि_सं));
			पूर्ण

			अगर (txmsg_ktls_skb_redir) अणु
				i = 1;
				err = bpf_map_update_elem(map_fd[7],
							  &i, &ingress, BPF_ANY);
				अगर (err) अणु
					ख_लिखो(मानक_त्रुटि,
						"ERROR: bpf_map_update_elem (txmsg_ingress): %d (%s)\n",
						err, म_त्रुटि(त्रुटि_सं));
				पूर्ण
			पूर्ण

			अगर (txmsg_ktls_skb_drop) अणु
				i = 1;
				err = bpf_map_update_elem(map_fd[7], &i, &i, BPF_ANY);
			पूर्ण
		पूर्ण

		अगर (txmsg_redir_skb) अणु
			पूर्णांक skb_fd = (test == SENDMSG || test == SENDPAGE) ?
					p2 : p1;
			पूर्णांक ingress = BPF_F_INGRESS;

			i = 0;
			err = bpf_map_update_elem(map_fd[7],
						  &i, &ingress, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem (txmsg_ingress): %d (%s)\n",
					err, म_त्रुटि(त्रुटि_सं));
			पूर्ण

			i = 3;
			err = bpf_map_update_elem(map_fd[0], &i, &skb_fd, BPF_ANY);
			अगर (err) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: bpf_map_update_elem (c1 sockmap): %d (%s)\n",
					err, म_त्रुटि(त्रुटि_सं));
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (skb_use_parser) अणु
		i = 2;
		err = bpf_map_update_elem(map_fd[7], &i, &skb_use_parser, BPF_ANY);
	पूर्ण

	अगर (txmsg_drop)
		options->drop_expected = true;

	अगर (test == PING_PONG)
		err = क्रमever_ping_pong(options->rate, options);
	अन्यथा अगर (test == SENDMSG) अणु
		options->base = false;
		options->sendpage = false;
		err = sendmsg_test(options);
	पूर्ण अन्यथा अगर (test == SENDPAGE) अणु
		options->base = false;
		options->sendpage = true;
		err = sendmsg_test(options);
	पूर्ण अन्यथा अगर (test == BASE) अणु
		options->base = true;
		options->sendpage = false;
		err = sendmsg_test(options);
	पूर्ण अन्यथा अगर (test == BASE_SENDPAGE) अणु
		options->base = true;
		options->sendpage = true;
		err = sendmsg_test(options);
	पूर्ण अन्यथा
		ख_लिखो(मानक_त्रुटि, "unknown test\n");
out:
	/* Detatch and zero all the maps */
	bpf_prog_detach2(prog_fd[3], cg_fd, BPF_CGROUP_SOCK_OPS);
	bpf_prog_detach2(prog_fd[0], map_fd[0], BPF_SK_SKB_STREAM_PARSER);
	bpf_prog_detach2(prog_fd[1], map_fd[0], BPF_SK_SKB_STREAM_VERDICT);
	bpf_prog_detach2(prog_fd[0], map_fd[8], BPF_SK_SKB_STREAM_PARSER);
	bpf_prog_detach2(prog_fd[2], map_fd[8], BPF_SK_SKB_STREAM_VERDICT);

	अगर (tx_prog_fd >= 0)
		bpf_prog_detach2(tx_prog_fd, map_fd[1], BPF_SK_MSG_VERDICT);

	क्रम (i = 0; i < 8; i++) अणु
		key = next_key = 0;
		bpf_map_update_elem(map_fd[i], &key, &zero, BPF_ANY);
		जबतक (bpf_map_get_next_key(map_fd[i], &key, &next_key) == 0) अणु
			bpf_map_update_elem(map_fd[i], &key, &zero, BPF_ANY);
			key = next_key;
		पूर्ण
	पूर्ण

	बंद(s1);
	बंद(s2);
	बंद(p1);
	बंद(p2);
	बंद(c1);
	बंद(c2);
	वापस err;
पूर्ण

अटल अक्षर *test_to_str(पूर्णांक test)
अणु
	चयन (test) अणु
	हाल SENDMSG:
		वापस "sendmsg";
	हाल SENDPAGE:
		वापस "sendpage";
	पूर्ण
	वापस "unknown";
पूर्ण

अटल व्योम append_str(अक्षर *dst, स्थिर अक्षर *src, माप_प्रकार dst_cap)
अणु
	माप_प्रकार avail = dst_cap - म_माप(dst);

	अगर (avail <= 1) /* just zero byte could be written */
		वापस;

	म_जोड़न(dst, src, avail - 1); /* म_जोड़न() adds + 1 क्रम zero byte */
पूर्ण

#घोषणा OPTSTRING 60
अटल व्योम test_options(अक्षर *options)
अणु
	अक्षर tstr[OPTSTRING];

	स_रखो(options, 0, OPTSTRING);

	अगर (txmsg_pass)
		append_str(options, "pass,", OPTSTRING);
	अगर (txmsg_redir)
		append_str(options, "redir,", OPTSTRING);
	अगर (txmsg_drop)
		append_str(options, "drop,", OPTSTRING);
	अगर (txmsg_apply) अणु
		snम_लिखो(tstr, OPTSTRING, "apply %d,", txmsg_apply);
		append_str(options, tstr, OPTSTRING);
	पूर्ण
	अगर (txmsg_cork) अणु
		snम_लिखो(tstr, OPTSTRING, "cork %d,", txmsg_cork);
		append_str(options, tstr, OPTSTRING);
	पूर्ण
	अगर (txmsg_start) अणु
		snम_लिखो(tstr, OPTSTRING, "start %d,", txmsg_start);
		append_str(options, tstr, OPTSTRING);
	पूर्ण
	अगर (txmsg_end) अणु
		snम_लिखो(tstr, OPTSTRING, "end %d,", txmsg_end);
		append_str(options, tstr, OPTSTRING);
	पूर्ण
	अगर (txmsg_start_pop) अणु
		snम_लिखो(tstr, OPTSTRING, "pop (%d,%d),",
			 txmsg_start_pop, txmsg_start_pop + txmsg_pop);
		append_str(options, tstr, OPTSTRING);
	पूर्ण
	अगर (txmsg_ingress)
		append_str(options, "ingress,", OPTSTRING);
	अगर (txmsg_redir_skb)
		append_str(options, "redir_skb,", OPTSTRING);
	अगर (txmsg_ktls_skb)
		append_str(options, "ktls_skb,", OPTSTRING);
	अगर (ktls)
		append_str(options, "ktls,", OPTSTRING);
	अगर (peek_flag)
		append_str(options, "peek,", OPTSTRING);
पूर्ण

अटल पूर्णांक __test_exec(पूर्णांक cgrp, पूर्णांक test, काष्ठा sockmap_options *opt)
अणु
	अक्षर *options = सुस्मृति(OPTSTRING, माप(अक्षर));
	पूर्णांक err;

	अगर (test == SENDPAGE)
		opt->sendpage = true;
	अन्यथा
		opt->sendpage = false;

	अगर (txmsg_drop)
		opt->drop_expected = true;
	अन्यथा
		opt->drop_expected = false;

	test_options(options);

	अगर (opt->verbose) अणु
		ख_लिखो(मानक_निकास,
			" [TEST %i]: (%i, %i, %i, %s, %s): ",
			test_cnt, opt->rate, opt->iov_count, opt->iov_length,
			test_to_str(test), options);
		ख_साफ(मानक_निकास);
	पूर्ण
	err = run_options(opt, cgrp, test);
	अगर (opt->verbose)
		ख_लिखो(मानक_निकास, " %s\n", !err ? "PASS" : "FAILED");
	test_cnt++;
	!err ? passed++ : failed++;
	मुक्त(options);
	वापस err;
पूर्ण

अटल व्योम test_exec(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	पूर्णांक type = म_भेद(opt->map, BPF_SOCKMAP_खाताNAME);
	पूर्णांक err;

	अगर (type == 0) अणु
		test_start();
		err = __test_exec(cgrp, SENDMSG, opt);
		अगर (err)
			test_fail();
	पूर्ण अन्यथा अणु
		test_start();
		err = __test_exec(cgrp, SENDPAGE, opt);
		अगर (err)
			test_fail();
	पूर्ण
पूर्ण

अटल व्योम test_send_one(काष्ठा sockmap_options *opt, पूर्णांक cgrp)
अणु
	opt->iov_length = 1;
	opt->iov_count = 1;
	opt->rate = 1;
	test_exec(cgrp, opt);

	opt->iov_length = 1;
	opt->iov_count = 1024;
	opt->rate = 1;
	test_exec(cgrp, opt);

	opt->iov_length = 1024;
	opt->iov_count = 1;
	opt->rate = 1;
	test_exec(cgrp, opt);

पूर्ण

अटल व्योम test_send_many(काष्ठा sockmap_options *opt, पूर्णांक cgrp)
अणु
	opt->iov_length = 3;
	opt->iov_count = 1;
	opt->rate = 512;
	test_exec(cgrp, opt);

	opt->rate = 100;
	opt->iov_count = 1;
	opt->iov_length = 5;
	test_exec(cgrp, opt);
पूर्ण

अटल व्योम test_send_large(काष्ठा sockmap_options *opt, पूर्णांक cgrp)
अणु
	opt->iov_length = 256;
	opt->iov_count = 1024;
	opt->rate = 2;
	test_exec(cgrp, opt);
पूर्ण

अटल व्योम test_send(काष्ठा sockmap_options *opt, पूर्णांक cgrp)
अणु
	test_send_one(opt, cgrp);
	test_send_many(opt, cgrp);
	test_send_large(opt, cgrp);
	sched_yield();
पूर्ण

अटल व्योम test_txmsg_pass(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	/* Test small and large iov_count values with pass/redir/apply/cork */
	txmsg_pass = 1;
	test_send(opt, cgrp);
पूर्ण

अटल व्योम test_txmsg_redir(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	txmsg_redir = 1;
	test_send(opt, cgrp);
पूर्ण

अटल व्योम test_txmsg_drop(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	txmsg_drop = 1;
	test_send(opt, cgrp);
पूर्ण

अटल व्योम test_txmsg_ingress_redir(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	txmsg_pass = txmsg_drop = 0;
	txmsg_ingress = txmsg_redir = 1;
	test_send(opt, cgrp);
पूर्ण

अटल व्योम test_txmsg_skb(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	bool data = opt->data_test;
	पूर्णांक k = ktls;

	opt->data_test = true;
	ktls = 1;

	txmsg_pass = txmsg_drop = 0;
	txmsg_ingress = txmsg_redir = 0;
	txmsg_ktls_skb = 1;
	txmsg_pass = 1;

	/* Using data verअगरication so ensure iov layout is
	 * expected from test receiver side. e.g. has enough
	 * bytes to ग_लिखो test code.
	 */
	opt->iov_length = 100;
	opt->iov_count = 1;
	opt->rate = 1;
	test_exec(cgrp, opt);

	txmsg_ktls_skb_drop = 1;
	test_exec(cgrp, opt);

	txmsg_ktls_skb_drop = 0;
	txmsg_ktls_skb_redir = 1;
	test_exec(cgrp, opt);
	txmsg_ktls_skb_redir = 0;

	/* Tests that omit skb_parser */
	txmsg_omit_skb_parser = 1;
	ktls = 0;
	txmsg_ktls_skb = 0;
	test_exec(cgrp, opt);

	txmsg_ktls_skb_drop = 1;
	test_exec(cgrp, opt);
	txmsg_ktls_skb_drop = 0;

	txmsg_ktls_skb_redir = 1;
	test_exec(cgrp, opt);

	ktls = 1;
	test_exec(cgrp, opt);
	txmsg_omit_skb_parser = 0;

	opt->data_test = data;
	ktls = k;
पूर्ण

/* Test cork with hung data. This tests poor usage patterns where
 * cork can leave data on the ring अगर user program is buggy and
 * करोesn't flush them somehow. They करो take some समय however
 * because they रुको क्रम a समयout. Test pass, redir and cork with
 * apply logic. Use cork size of 4097 with send_large to aव्योम
 * aligning cork size with send size.
 */
अटल व्योम test_txmsg_cork_hangs(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	txmsg_pass = 1;
	txmsg_redir = 0;
	txmsg_cork = 4097;
	txmsg_apply = 4097;
	test_send_large(opt, cgrp);

	txmsg_pass = 0;
	txmsg_redir = 1;
	txmsg_apply = 0;
	txmsg_cork = 4097;
	test_send_large(opt, cgrp);

	txmsg_pass = 0;
	txmsg_redir = 1;
	txmsg_apply = 4097;
	txmsg_cork = 4097;
	test_send_large(opt, cgrp);
पूर्ण

अटल व्योम test_txmsg_pull(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	/* Test basic start/end */
	txmsg_start = 1;
	txmsg_end = 2;
	test_send(opt, cgrp);

	/* Test >4k pull */
	txmsg_start = 4096;
	txmsg_end = 9182;
	test_send_large(opt, cgrp);

	/* Test pull + redirect */
	txmsg_redir = 0;
	txmsg_start = 1;
	txmsg_end = 2;
	test_send(opt, cgrp);

	/* Test pull + cork */
	txmsg_redir = 0;
	txmsg_cork = 512;
	txmsg_start = 1;
	txmsg_end = 2;
	test_send_many(opt, cgrp);

	/* Test pull + cork + redirect */
	txmsg_redir = 1;
	txmsg_cork = 512;
	txmsg_start = 1;
	txmsg_end = 2;
	test_send_many(opt, cgrp);
पूर्ण

अटल व्योम test_txmsg_pop(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	/* Test basic pop */
	txmsg_start_pop = 1;
	txmsg_pop = 2;
	test_send_many(opt, cgrp);

	/* Test pop with >4k */
	txmsg_start_pop = 4096;
	txmsg_pop = 4096;
	test_send_large(opt, cgrp);

	/* Test pop + redirect */
	txmsg_redir = 1;
	txmsg_start_pop = 1;
	txmsg_pop = 2;
	test_send_many(opt, cgrp);

	/* Test pop + cork */
	txmsg_redir = 0;
	txmsg_cork = 512;
	txmsg_start_pop = 1;
	txmsg_pop = 2;
	test_send_many(opt, cgrp);

	/* Test pop + redirect + cork */
	txmsg_redir = 1;
	txmsg_cork = 4;
	txmsg_start_pop = 1;
	txmsg_pop = 2;
	test_send_many(opt, cgrp);
पूर्ण

अटल व्योम test_txmsg_push(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	/* Test basic push */
	txmsg_start_push = 1;
	txmsg_end_push = 1;
	test_send(opt, cgrp);

	/* Test push 4kB >4k */
	txmsg_start_push = 4096;
	txmsg_end_push = 4096;
	test_send_large(opt, cgrp);

	/* Test push + redirect */
	txmsg_redir = 1;
	txmsg_start_push = 1;
	txmsg_end_push = 2;
	test_send_many(opt, cgrp);

	/* Test push + cork */
	txmsg_redir = 0;
	txmsg_cork = 512;
	txmsg_start_push = 1;
	txmsg_end_push = 2;
	test_send_many(opt, cgrp);
पूर्ण

अटल व्योम test_txmsg_push_pop(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	txmsg_start_push = 1;
	txmsg_end_push = 10;
	txmsg_start_pop = 5;
	txmsg_pop = 4;
	test_send_large(opt, cgrp);
पूर्ण

अटल व्योम test_txmsg_apply(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	txmsg_pass = 1;
	txmsg_redir = 0;
	txmsg_apply = 1;
	txmsg_cork = 0;
	test_send_one(opt, cgrp);

	txmsg_pass = 0;
	txmsg_redir = 1;
	txmsg_apply = 1;
	txmsg_cork = 0;
	test_send_one(opt, cgrp);

	txmsg_pass = 1;
	txmsg_redir = 0;
	txmsg_apply = 1024;
	txmsg_cork = 0;
	test_send_large(opt, cgrp);

	txmsg_pass = 0;
	txmsg_redir = 1;
	txmsg_apply = 1024;
	txmsg_cork = 0;
	test_send_large(opt, cgrp);
पूर्ण

अटल व्योम test_txmsg_cork(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	txmsg_pass = 1;
	txmsg_redir = 0;
	txmsg_apply = 0;
	txmsg_cork = 1;
	test_send(opt, cgrp);

	txmsg_pass = 1;
	txmsg_redir = 0;
	txmsg_apply = 1;
	txmsg_cork = 1;
	test_send(opt, cgrp);
पूर्ण

अटल व्योम test_txmsg_ingress_parser(पूर्णांक cgrp, काष्ठा sockmap_options *opt)
अणु
	txmsg_pass = 1;
	skb_use_parser = 512;
	opt->iov_length = 256;
	opt->iov_count = 1;
	opt->rate = 2;
	test_exec(cgrp, opt);
पूर्ण

अक्षर *map_names[] = अणु
	"sock_map",
	"sock_map_txmsg",
	"sock_map_redir",
	"sock_apply_bytes",
	"sock_cork_bytes",
	"sock_bytes",
	"sock_redir_flags",
	"sock_skb_opts",
	"tls_sock_map",
पूर्ण;

पूर्णांक prog_attach_type[] = अणु
	BPF_SK_SKB_STREAM_PARSER,
	BPF_SK_SKB_STREAM_VERDICT,
	BPF_SK_SKB_STREAM_VERDICT,
	BPF_CGROUP_SOCK_OPS,
	BPF_SK_MSG_VERDICT,
	BPF_SK_MSG_VERDICT,
	BPF_SK_MSG_VERDICT,
	BPF_SK_MSG_VERDICT,
	BPF_SK_MSG_VERDICT,
	BPF_SK_MSG_VERDICT,
	BPF_SK_MSG_VERDICT,
पूर्ण;

पूर्णांक prog_type[] = अणु
	BPF_PROG_TYPE_SK_SKB,
	BPF_PROG_TYPE_SK_SKB,
	BPF_PROG_TYPE_SK_SKB,
	BPF_PROG_TYPE_SOCK_OPS,
	BPF_PROG_TYPE_SK_MSG,
	BPF_PROG_TYPE_SK_MSG,
	BPF_PROG_TYPE_SK_MSG,
	BPF_PROG_TYPE_SK_MSG,
	BPF_PROG_TYPE_SK_MSG,
	BPF_PROG_TYPE_SK_MSG,
	BPF_PROG_TYPE_SK_MSG,
पूर्ण;

अटल पूर्णांक populate_progs(अक्षर *bpf_file)
अणु
	काष्ठा bpf_program *prog;
	काष्ठा bpf_object *obj;
	पूर्णांक i = 0;
	दीर्घ err;

	obj = bpf_object__खोलो(bpf_file);
	err = libbpf_get_error(obj);
	अगर (err) अणु
		अक्षर err_buf[256];

		libbpf_म_त्रुटि(err, err_buf, माप(err_buf));
		म_लिखो("Unable to load eBPF objects in file '%s' : %s\n",
		       bpf_file, err_buf);
		वापस -1;
	पूर्ण

	bpf_object__क्रम_each_program(prog, obj) अणु
		bpf_program__set_type(prog, prog_type[i]);
		bpf_program__set_expected_attach_type(prog,
						      prog_attach_type[i]);
		i++;
	पूर्ण

	i = bpf_object__load(obj);
	i = 0;
	bpf_object__क्रम_each_program(prog, obj) अणु
		prog_fd[i] = bpf_program__fd(prog);
		i++;
	पूर्ण

	क्रम (i = 0; i < माप(map_fd)/माप(पूर्णांक); i++) अणु
		maps[i] = bpf_object__find_map_by_name(obj, map_names[i]);
		map_fd[i] = bpf_map__fd(maps[i]);
		अगर (map_fd[i] < 0) अणु
			ख_लिखो(मानक_त्रुटि, "load_bpf_file: (%i) %s\n",
				map_fd[i], म_त्रुटि(त्रुटि_सं));
			वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा _test test[] = अणु
	अणु"txmsg test passthrough", test_txmsg_passपूर्ण,
	अणु"txmsg test redirect", test_txmsg_redirपूर्ण,
	अणु"txmsg test drop", test_txmsg_dropपूर्ण,
	अणु"txmsg test ingress redirect", test_txmsg_ingress_redirपूर्ण,
	अणु"txmsg test skb", test_txmsg_skbपूर्ण,
	अणु"txmsg test apply", test_txmsg_applyपूर्ण,
	अणु"txmsg test cork", test_txmsg_corkपूर्ण,
	अणु"txmsg test hanging corks", test_txmsg_cork_hangsपूर्ण,
	अणु"txmsg test push_data", test_txmsg_pushपूर्ण,
	अणु"txmsg test pull-data", test_txmsg_pullपूर्ण,
	अणु"txmsg test pop-data", test_txmsg_popपूर्ण,
	अणु"txmsg test push/pop data", test_txmsg_push_popपूर्ण,
	अणु"txmsg text ingress parser", test_txmsg_ingress_parserपूर्ण,
पूर्ण;

अटल पूर्णांक check_whitelist(काष्ठा _test *t, काष्ठा sockmap_options *opt)
अणु
	अक्षर *entry, *ptr;

	अगर (!opt->whitelist)
		वापस 0;
	ptr = strdup(opt->whitelist);
	अगर (!ptr)
		वापस -ENOMEM;
	entry = म_मोहर(ptr, ",");
	जबतक (entry) अणु
		अगर ((opt->prepend && म_माला(opt->prepend, entry) != 0) ||
		    म_माला(opt->map, entry) != 0 ||
		    म_माला(t->title, entry) != 0)
			वापस 0;
		entry = म_मोहर(शून्य, ",");
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक check_blacklist(काष्ठा _test *t, काष्ठा sockmap_options *opt)
अणु
	अक्षर *entry, *ptr;

	अगर (!opt->blacklist)
		वापस -EINVAL;
	ptr = strdup(opt->blacklist);
	अगर (!ptr)
		वापस -ENOMEM;
	entry = म_मोहर(ptr, ",");
	जबतक (entry) अणु
		अगर ((opt->prepend && म_माला(opt->prepend, entry) != 0) ||
		    म_माला(opt->map, entry) != 0 ||
		    म_माला(t->title, entry) != 0)
			वापस 0;
		entry = म_मोहर(शून्य, ",");
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __test_selftests(पूर्णांक cg_fd, काष्ठा sockmap_options *opt)
अणु
	पूर्णांक i, err;

	err = populate_progs(opt->map);
	अगर (err < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: (%i) load bpf failed\n", err);
		वापस err;
	पूर्ण

	/* Tests basic commands and APIs */
	क्रम (i = 0; i < माप(test)/माप(काष्ठा _test); i++) अणु
		काष्ठा _test t = test[i];

		अगर (check_whitelist(&t, opt) != 0)
			जारी;
		अगर (check_blacklist(&t, opt) == 0)
			जारी;

		test_start_subtest(&t, opt);
		t.tester(cg_fd, opt);
		test_end_subtest();
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम test_selftests_sockmap(पूर्णांक cg_fd, काष्ठा sockmap_options *opt)
अणु
	opt->map = BPF_SOCKMAP_खाताNAME;
	__test_selftests(cg_fd, opt);
पूर्ण

अटल व्योम test_selftests_sockhash(पूर्णांक cg_fd, काष्ठा sockmap_options *opt)
अणु
	opt->map = BPF_SOCKHASH_खाताNAME;
	__test_selftests(cg_fd, opt);
पूर्ण

अटल व्योम test_selftests_ktls(पूर्णांक cg_fd, काष्ठा sockmap_options *opt)
अणु
	opt->map = BPF_SOCKHASH_खाताNAME;
	opt->prepend = "ktls";
	ktls = 1;
	__test_selftests(cg_fd, opt);
	ktls = 0;
पूर्ण

अटल पूर्णांक test_selftest(पूर्णांक cg_fd, काष्ठा sockmap_options *opt)
अणु

	test_selftests_sockmap(cg_fd, opt);
	test_selftests_sockhash(cg_fd, opt);
	test_selftests_ktls(cg_fd, opt);
	test_prपूर्णांक_results();
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक iov_count = 1, length = 1024, rate = 1;
	काष्ठा sockmap_options options = अणु0पूर्ण;
	पूर्णांक opt, दीर्घindex, err, cg_fd = 0;
	अक्षर *bpf_file = BPF_SOCKMAP_खाताNAME;
	पूर्णांक test = SELFTESTS;
	bool cg_created = 0;

	जबतक ((opt = getopt_दीर्घ(argc, argv, ":dhv:c:r:i:l:t:p:q:n:b:",
				  दीर्घ_options, &दीर्घindex)) != -1) अणु
		चयन (opt) अणु
		हाल 's':
			txmsg_start = म_से_प(optarg);
			अवरोध;
		हाल 'e':
			txmsg_end = म_से_प(optarg);
			अवरोध;
		हाल 'p':
			txmsg_start_push = म_से_प(optarg);
			अवरोध;
		हाल 'q':
			txmsg_end_push = म_से_प(optarg);
			अवरोध;
		हाल 'w':
			txmsg_start_pop = म_से_प(optarg);
			अवरोध;
		हाल 'x':
			txmsg_pop = म_से_प(optarg);
			अवरोध;
		हाल 'a':
			txmsg_apply = म_से_प(optarg);
			अवरोध;
		हाल 'k':
			txmsg_cork = म_से_प(optarg);
			अवरोध;
		हाल 'c':
			cg_fd = खोलो(optarg, O_सूचीECTORY, O_RDONLY);
			अगर (cg_fd < 0) अणु
				ख_लिखो(मानक_त्रुटि,
					"ERROR: (%i) open cg path failed: %s\n",
					cg_fd, optarg);
				वापस cg_fd;
			पूर्ण
			अवरोध;
		हाल 'r':
			rate = म_से_प(optarg);
			अवरोध;
		हाल 'v':
			options.verbose = 1;
			अगर (optarg)
				options.verbose = म_से_प(optarg);
			अवरोध;
		हाल 'i':
			iov_count = म_से_प(optarg);
			अवरोध;
		हाल 'l':
			length = म_से_प(optarg);
			अवरोध;
		हाल 'd':
			options.data_test = true;
			अवरोध;
		हाल 't':
			अगर (म_भेद(optarg, "ping") == 0) अणु
				test = PING_PONG;
			पूर्ण अन्यथा अगर (म_भेद(optarg, "sendmsg") == 0) अणु
				test = SENDMSG;
			पूर्ण अन्यथा अगर (म_भेद(optarg, "base") == 0) अणु
				test = BASE;
			पूर्ण अन्यथा अगर (म_भेद(optarg, "base_sendpage") == 0) अणु
				test = BASE_SENDPAGE;
			पूर्ण अन्यथा अगर (म_भेद(optarg, "sendpage") == 0) अणु
				test = SENDPAGE;
			पूर्ण अन्यथा अणु
				usage(argv);
				वापस -1;
			पूर्ण
			अवरोध;
		हाल 'n':
			options.whitelist = strdup(optarg);
			अगर (!options.whitelist)
				वापस -ENOMEM;
			अवरोध;
		हाल 'b':
			options.blacklist = strdup(optarg);
			अगर (!options.blacklist)
				वापस -ENOMEM;
		हाल 0:
			अवरोध;
		हाल 'h':
		शेष:
			usage(argv);
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (!cg_fd) अणु
		cg_fd = cgroup_setup_and_join(CG_PATH);
		अगर (cg_fd < 0)
			वापस cg_fd;
		cg_created = 1;
	पूर्ण

	अगर (test == SELFTESTS) अणु
		err = test_selftest(cg_fd, &options);
		जाओ out;
	पूर्ण

	err = populate_progs(bpf_file);
	अगर (err) अणु
		ख_लिखो(मानक_त्रुटि, "populate program: (%s) %s\n",
			bpf_file, म_त्रुटि(त्रुटि_सं));
		वापस 1;
	पूर्ण
	running = 1;

	/* catch संक_विघ्न */
	संकेत(संक_विघ्न, running_handler);

	options.iov_count = iov_count;
	options.iov_length = length;
	options.rate = rate;

	err = run_options(&options, cg_fd, test);
out:
	अगर (options.whitelist)
		मुक्त(options.whitelist);
	अगर (options.blacklist)
		मुक्त(options.blacklist);
	अगर (cg_created)
		cleanup_cgroup_environment();
	बंद(cg_fd);
	वापस err;
पूर्ण

व्योम running_handler(पूर्णांक a)
अणु
	running = 0;
पूर्ण
