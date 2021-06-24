<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <test_progs.h>
#समावेश "cgroup_helpers.h"

#समावेश <linux/tcp.h>
#समावेश "sockopt_sk.skel.h"

#अगर_अघोषित SOL_TCP
#घोषणा SOL_TCP IPPROTO_TCP
#पूर्ण_अगर

#घोषणा SOL_CUSTOM			0xdeadbeef

अटल पूर्णांक माला_लोetsockopt(व्योम)
अणु
	पूर्णांक fd, err;
	जोड़ अणु
		अक्षर u8[4];
		__u32 u32;
		अक्षर cc[16]; /* TCP_CA_NAME_MAX */
		काष्ठा tcp_zerocopy_receive zc;
	पूर्ण buf = अणुपूर्ण;
	socklen_t optlen;
	अक्षर *big_buf = शून्य;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	अगर (fd < 0) अणु
		log_err("Failed to create socket");
		वापस -1;
	पूर्ण

	/* IP_TOS - BPF bypass */

	optlen = getpagesize() * 2;
	big_buf = सुस्मृति(1, optlen);
	अगर (!big_buf) अणु
		log_err("Couldn't allocate two pages");
		जाओ err;
	पूर्ण

	*(पूर्णांक *)big_buf = 0x08;
	err = setsockopt(fd, SOL_IP, IP_TOS, big_buf, optlen);
	अगर (err) अणु
		log_err("Failed to call setsockopt(IP_TOS)");
		जाओ err;
	पूर्ण

	स_रखो(big_buf, 0, optlen);
	optlen = 1;
	err = माला_लोockopt(fd, SOL_IP, IP_TOS, big_buf, &optlen);
	अगर (err) अणु
		log_err("Failed to call getsockopt(IP_TOS)");
		जाओ err;
	पूर्ण

	अगर (*big_buf != 0x08) अणु
		log_err("Unexpected getsockopt(IP_TOS) optval 0x%x != 0x08",
			(पूर्णांक)*big_buf);
		जाओ err;
	पूर्ण

	/* IP_TTL - EPERM */

	buf.u8[0] = 1;
	err = setsockopt(fd, SOL_IP, IP_TTL, &buf, 1);
	अगर (!err || त्रुटि_सं != EPERM) अणु
		log_err("Unexpected success from setsockopt(IP_TTL)");
		जाओ err;
	पूर्ण

	/* SOL_CUSTOM - handled by BPF */

	buf.u8[0] = 0x01;
	err = setsockopt(fd, SOL_CUSTOM, 0, &buf, 1);
	अगर (err) अणु
		log_err("Failed to call setsockopt");
		जाओ err;
	पूर्ण

	buf.u32 = 0x00;
	optlen = 4;
	err = माला_लोockopt(fd, SOL_CUSTOM, 0, &buf, &optlen);
	अगर (err) अणु
		log_err("Failed to call getsockopt");
		जाओ err;
	पूर्ण

	अगर (optlen != 1) अणु
		log_err("Unexpected optlen %d != 1", optlen);
		जाओ err;
	पूर्ण
	अगर (buf.u8[0] != 0x01) अणु
		log_err("Unexpected buf[0] 0x%02x != 0x01", buf.u8[0]);
		जाओ err;
	पूर्ण

	/* IP_FREEBIND - BPF can't access optval past PAGE_SIZE */

	optlen = getpagesize() * 2;
	स_रखो(big_buf, 0, optlen);

	err = setsockopt(fd, SOL_IP, IP_FREEBIND, big_buf, optlen);
	अगर (err != 0) अणु
		log_err("Failed to call setsockopt, ret=%d", err);
		जाओ err;
	पूर्ण

	err = माला_लोockopt(fd, SOL_IP, IP_FREEBIND, big_buf, &optlen);
	अगर (err != 0) अणु
		log_err("Failed to call getsockopt, ret=%d", err);
		जाओ err;
	पूर्ण

	अगर (optlen != 1 || *(__u8 *)big_buf != 0x55) अणु
		log_err("Unexpected IP_FREEBIND getsockopt, optlen=%d, optval=0x%x",
			optlen, *(__u8 *)big_buf);
	पूर्ण

	/* SO_SNDBUF is overwritten */

	buf.u32 = 0x01010101;
	err = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &buf, 4);
	अगर (err) अणु
		log_err("Failed to call setsockopt(SO_SNDBUF)");
		जाओ err;
	पूर्ण

	buf.u32 = 0x00;
	optlen = 4;
	err = माला_लोockopt(fd, SOL_SOCKET, SO_SNDBUF, &buf, &optlen);
	अगर (err) अणु
		log_err("Failed to call getsockopt(SO_SNDBUF)");
		जाओ err;
	पूर्ण

	अगर (buf.u32 != 0x55AA*2) अणु
		log_err("Unexpected getsockopt(SO_SNDBUF) 0x%x != 0x55AA*2",
			buf.u32);
		जाओ err;
	पूर्ण

	/* TCP_CONGESTION can extend the string */

	म_नकल(buf.cc, "nv");
	err = setsockopt(fd, SOL_TCP, TCP_CONGESTION, &buf, म_माप("nv"));
	अगर (err) अणु
		log_err("Failed to call setsockopt(TCP_CONGESTION)");
		जाओ err;
	पूर्ण


	optlen = माप(buf.cc);
	err = माला_लोockopt(fd, SOL_TCP, TCP_CONGESTION, &buf, &optlen);
	अगर (err) अणु
		log_err("Failed to call getsockopt(TCP_CONGESTION)");
		जाओ err;
	पूर्ण

	अगर (म_भेद(buf.cc, "cubic") != 0) अणु
		log_err("Unexpected getsockopt(TCP_CONGESTION) %s != %s",
			buf.cc, "cubic");
		जाओ err;
	पूर्ण

	/* TCP_ZEROCOPY_RECEIVE triggers */
	स_रखो(&buf, 0, माप(buf));
	optlen = माप(buf.zc);
	err = माला_लोockopt(fd, SOL_TCP, TCP_ZEROCOPY_RECEIVE, &buf, &optlen);
	अगर (err) अणु
		log_err("Unexpected getsockopt(TCP_ZEROCOPY_RECEIVE) err=%d errno=%d",
			err, त्रुटि_सं);
		जाओ err;
	पूर्ण

	स_रखो(&buf, 0, माप(buf));
	buf.zc.address = 12345; /* rejected by BPF */
	optlen = माप(buf.zc);
	त्रुटि_सं = 0;
	err = माला_लोockopt(fd, SOL_TCP, TCP_ZEROCOPY_RECEIVE, &buf, &optlen);
	अगर (त्रुटि_सं != EPERM) अणु
		log_err("Unexpected getsockopt(TCP_ZEROCOPY_RECEIVE) err=%d errno=%d",
			err, त्रुटि_सं);
		जाओ err;
	पूर्ण

	मुक्त(big_buf);
	बंद(fd);
	वापस 0;
err:
	मुक्त(big_buf);
	बंद(fd);
	वापस -1;
पूर्ण

अटल व्योम run_test(पूर्णांक cgroup_fd)
अणु
	काष्ठा sockopt_sk *skel;

	skel = sockopt_sk__खोलो_and_load();
	अगर (!ASSERT_OK_PTR(skel, "skel_load"))
		जाओ cleanup;

	skel->bss->page_size = getpagesize();

	skel->links._setsockopt =
		bpf_program__attach_cgroup(skel->progs._setsockopt, cgroup_fd);
	अगर (!ASSERT_OK_PTR(skel->links._setsockopt, "setsockopt_link"))
		जाओ cleanup;

	skel->links._माला_लोockopt =
		bpf_program__attach_cgroup(skel->progs._माला_लोockopt, cgroup_fd);
	अगर (!ASSERT_OK_PTR(skel->links._माला_लोockopt, "getsockopt_link"))
		जाओ cleanup;

	ASSERT_OK(माला_लोetsockopt(), "getsetsockopt");

cleanup:
	sockopt_sk__destroy(skel);
पूर्ण

व्योम test_sockopt_sk(व्योम)
अणु
	पूर्णांक cgroup_fd;

	cgroup_fd = test__join_cgroup("/sockopt_sk");
	अगर (CHECK_FAIL(cgroup_fd < 0))
		वापस;

	run_test(cgroup_fd);
	बंद(cgroup_fd);
पूर्ण
