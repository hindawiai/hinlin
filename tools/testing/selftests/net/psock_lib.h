<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2013 Google Inc.
 * Author: Willem de Bruijn <willemb@google.com>
 *         Daniel Borkmann <dborkman@redhat.com>
 */

#अगर_अघोषित PSOCK_LIB_H
#घोषणा PSOCK_LIB_H

#समावेश <sys/types.h>
#समावेश <sys/socket.h>
#समावेश <माला.स>
#समावेश <arpa/inet.h>
#समावेश <unistd.h>

#घोषणा DATA_LEN			100
#घोषणा DATA_CHAR			'a'
#घोषणा DATA_CHAR_1			'b'

#घोषणा PORT_BASE			8000

#अगर_अघोषित __maybe_unused
# define __maybe_unused		__attribute__ ((__unused__))
#पूर्ण_अगर

अटल __maybe_unused व्योम pair_udp_setfilter(पूर्णांक fd)
अणु
	/* the filter below checks क्रम all of the following conditions that
	 * are based on the contents of create_payload()
	 *  ether type 0x800 and
	 *  ip proto udp     and
	 *  skb->len == DATA_LEN and
	 *  udp[38] == 'a' or udp[38] == 'b'
	 * It can be generated from the following bpf_यंत्र input:
	 *	ldh [12]
	 *	jne #0x800, drop	; ETH_P_IP
	 *	ldb [23]
	 *	jneq #17, drop		; IPPROTO_UDP
	 *	ld len			; ld skb->len
	 *	jlt #100, drop		; DATA_LEN
	 *	ldb [80]
	 *	jeq #97, pass		; DATA_CHAR
	 *	jne #98, drop		; DATA_CHAR_1
	 *	pass:
	 *	  ret #-1
	 *	drop:
	 *	  ret #0
	 */
	काष्ठा sock_filter bpf_filter[] = अणु
		अणु 0x28,  0,  0, 0x0000000c पूर्ण,
		अणु 0x15,  0,  8, 0x00000800 पूर्ण,
		अणु 0x30,  0,  0, 0x00000017 पूर्ण,
		अणु 0x15,  0,  6, 0x00000011 पूर्ण,
		अणु 0x80,  0,  0, 0000000000 पूर्ण,
		अणु 0x35,  0,  4, 0x00000064 पूर्ण,
		अणु 0x30,  0,  0, 0x00000050 पूर्ण,
		अणु 0x15,  1,  0, 0x00000061 पूर्ण,
		अणु 0x15,  0,  1, 0x00000062 पूर्ण,
		अणु 0x06,  0,  0, 0xffffffff पूर्ण,
		अणु 0x06,  0,  0, 0000000000 पूर्ण,
	पूर्ण;
	काष्ठा sock_fprog bpf_prog;

	bpf_prog.filter = bpf_filter;
	bpf_prog.len = माप(bpf_filter) / माप(काष्ठा sock_filter);

	अगर (setsockopt(fd, SOL_SOCKET, SO_ATTACH_FILTER, &bpf_prog,
		       माप(bpf_prog))) अणु
		लिखो_त्रुटि("setsockopt SO_ATTACH_FILTER");
		निकास(1);
	पूर्ण
पूर्ण

अटल __maybe_unused व्योम pair_udp_खोलो(पूर्णांक fds[], uपूर्णांक16_t port)
अणु
	काष्ठा sockaddr_in saddr, daddr;

	fds[0] = socket(PF_INET, SOCK_DGRAM, 0);
	fds[1] = socket(PF_INET, SOCK_DGRAM, 0);
	अगर (fds[0] == -1 || fds[1] == -1) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: socket dgram\n");
		निकास(1);
	पूर्ण

	स_रखो(&saddr, 0, माप(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	स_रखो(&daddr, 0, माप(daddr));
	daddr.sin_family = AF_INET;
	daddr.sin_port = htons(port + 1);
	daddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	/* must bind both to get consistent hash result */
	अगर (bind(fds[1], (व्योम *) &daddr, माप(daddr))) अणु
		लिखो_त्रुटि("bind");
		निकास(1);
	पूर्ण
	अगर (bind(fds[0], (व्योम *) &saddr, माप(saddr))) अणु
		लिखो_त्रुटि("bind");
		निकास(1);
	पूर्ण
	अगर (connect(fds[0], (व्योम *) &daddr, माप(daddr))) अणु
		लिखो_त्रुटि("connect");
		निकास(1);
	पूर्ण
पूर्ण

अटल __maybe_unused व्योम pair_udp_send_अक्षर(पूर्णांक fds[], पूर्णांक num, अक्षर payload)
अणु
	अक्षर buf[DATA_LEN], rbuf[DATA_LEN];

	स_रखो(buf, payload, माप(buf));
	जबतक (num--) अणु
		/* Should really handle EINTR and EAGAIN */
		अगर (ग_लिखो(fds[0], buf, माप(buf)) != माप(buf)) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: send failed left=%d\n", num);
			निकास(1);
		पूर्ण
		अगर (पढ़ो(fds[1], rbuf, माप(rbuf)) != माप(rbuf)) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: recv failed left=%d\n", num);
			निकास(1);
		पूर्ण
		अगर (स_भेद(buf, rbuf, माप(buf))) अणु
			ख_लिखो(मानक_त्रुटि, "ERROR: data failed left=%d\n", num);
			निकास(1);
		पूर्ण
	पूर्ण
पूर्ण

अटल __maybe_unused व्योम pair_udp_send(पूर्णांक fds[], पूर्णांक num)
अणु
	वापस pair_udp_send_अक्षर(fds, num, DATA_CHAR);
पूर्ण

अटल __maybe_unused व्योम pair_udp_बंद(पूर्णांक fds[])
अणु
	बंद(fds[0]);
	बंद(fds[1]);
पूर्ण

#पूर्ण_अगर /* PSOCK_LIB_H */
