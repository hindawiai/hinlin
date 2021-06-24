<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2020 Cloudflare
/*
 * Test suite क्रम SOCKMAP/SOCKHASH holding listening sockets.
 * Covers:
 *  1. BPF map operations - bpf_map_अणुupdate,lookup deleteपूर्ण_elem
 *  2. BPF redirect helpers - bpf_अणुsk,msgपूर्ण_redirect_map
 *  3. BPF reuseport helper - bpf_sk_select_reuseport
 */

#समावेश <linux/compiler.h>
#समावेश <त्रुटिसं.स>
#समावेश <error.h>
#समावेश <सीमा.स>
#समावेश <netinet/in.h>
#समावेश <pthपढ़ो.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/select.h>
#समावेश <unistd.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h>

#समावेश "bpf_util.h"
#समावेश "test_progs.h"
#समावेश "test_sockmap_listen.skel.h"

#घोषणा IO_TIMEOUT_SEC 30
#घोषणा MAX_STRERR_LEN 256
#घोषणा MAX_TEST_NAME 80

#घोषणा _FAIL(errnum, fmt...)                                                  \
	(अणु                                                                     \
		error_at_line(0, (errnum), __func__, __LINE__, fmt);           \
		CHECK_FAIL(true);                                              \
	पूर्ण)
#घोषणा FAIL(fmt...) _FAIL(0, fmt)
#घोषणा FAIL_ERRNO(fmt...) _FAIL(त्रुटि_सं, fmt)
#घोषणा FAIL_LIBBPF(err, msg)                                                  \
	(अणु                                                                     \
		अक्षर __buf[MAX_STRERR_LEN];                                    \
		libbpf_म_त्रुटि((err), __buf, माप(__buf));                  \
		FAIL("%s: %s", (msg), __buf);                                  \
	पूर्ण)

/* Wrappers that fail the test on error and report it. */

#घोषणा xaccept_nonblock(fd, addr, len)                                        \
	(अणु                                                                     \
		पूर्णांक __ret =                                                    \
			accept_समयout((fd), (addr), (len), IO_TIMEOUT_SEC);   \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("accept");                                  \
		__ret;                                                         \
	पूर्ण)

#घोषणा xbind(fd, addr, len)                                                   \
	(अणु                                                                     \
		पूर्णांक __ret = bind((fd), (addr), (len));                         \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("bind");                                    \
		__ret;                                                         \
	पूर्ण)

#घोषणा xबंद(fd)                                                             \
	(अणु                                                                     \
		पूर्णांक __ret = बंद((fd));                                       \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("close");                                   \
		__ret;                                                         \
	पूर्ण)

#घोषणा xconnect(fd, addr, len)                                                \
	(अणु                                                                     \
		पूर्णांक __ret = connect((fd), (addr), (len));                      \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("connect");                                 \
		__ret;                                                         \
	पूर्ण)

#घोषणा xमाला_लोockname(fd, addr, len)                                            \
	(अणु                                                                     \
		पूर्णांक __ret = माला_लोockname((fd), (addr), (len));                  \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("getsockname");                             \
		__ret;                                                         \
	पूर्ण)

#घोषणा xमाला_लोockopt(fd, level, name, val, len)                                 \
	(अणु                                                                     \
		पूर्णांक __ret = माला_लोockopt((fd), (level), (name), (val), (len));   \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("getsockopt(" #name ")");                   \
		__ret;                                                         \
	पूर्ण)

#घोषणा xlisten(fd, backlog)                                                   \
	(अणु                                                                     \
		पूर्णांक __ret = listen((fd), (backlog));                           \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("listen");                                  \
		__ret;                                                         \
	पूर्ण)

#घोषणा xsetsockopt(fd, level, name, val, len)                                 \
	(अणु                                                                     \
		पूर्णांक __ret = setsockopt((fd), (level), (name), (val), (len));   \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("setsockopt(" #name ")");                   \
		__ret;                                                         \
	पूर्ण)

#घोषणा xsend(fd, buf, len, flags)                                             \
	(अणु                                                                     \
		sमाप_प्रकार __ret = send((fd), (buf), (len), (flags));             \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("send");                                    \
		__ret;                                                         \
	पूर्ण)

#घोषणा xrecv_nonblock(fd, buf, len, flags)                                    \
	(अणु                                                                     \
		sमाप_प्रकार __ret = recv_समयout((fd), (buf), (len), (flags),      \
					     IO_TIMEOUT_SEC);                  \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("recv");                                    \
		__ret;                                                         \
	पूर्ण)

#घोषणा xsocket(family, sotype, flags)                                         \
	(अणु                                                                     \
		पूर्णांक __ret = socket(family, sotype, flags);                     \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("socket");                                  \
		__ret;                                                         \
	पूर्ण)

#घोषणा xbpf_map_delete_elem(fd, key)                                          \
	(अणु                                                                     \
		पूर्णांक __ret = bpf_map_delete_elem((fd), (key));                  \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("map_delete");                              \
		__ret;                                                         \
	पूर्ण)

#घोषणा xbpf_map_lookup_elem(fd, key, val)                                     \
	(अणु                                                                     \
		पूर्णांक __ret = bpf_map_lookup_elem((fd), (key), (val));           \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("map_lookup");                              \
		__ret;                                                         \
	पूर्ण)

#घोषणा xbpf_map_update_elem(fd, key, val, flags)                              \
	(अणु                                                                     \
		पूर्णांक __ret = bpf_map_update_elem((fd), (key), (val), (flags));  \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("map_update");                              \
		__ret;                                                         \
	पूर्ण)

#घोषणा xbpf_prog_attach(prog, target, type, flags)                            \
	(अणु                                                                     \
		पूर्णांक __ret =                                                    \
			bpf_prog_attach((prog), (target), (type), (flags));    \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("prog_attach(" #type ")");                  \
		__ret;                                                         \
	पूर्ण)

#घोषणा xbpf_prog_detach2(prog, target, type)                                  \
	(अणु                                                                     \
		पूर्णांक __ret = bpf_prog_detach2((prog), (target), (type));        \
		अगर (__ret == -1)                                               \
			FAIL_ERRNO("prog_detach2(" #type ")");                 \
		__ret;                                                         \
	पूर्ण)

#घोषणा xpthपढ़ो_create(thपढ़ो, attr, func, arg)                               \
	(अणु                                                                     \
		पूर्णांक __ret = pthपढ़ो_create((thपढ़ो), (attr), (func), (arg));   \
		त्रुटि_सं = __ret;                                                 \
		अगर (__ret)                                                     \
			FAIL_ERRNO("pthread_create");                          \
		__ret;                                                         \
	पूर्ण)

#घोषणा xpthपढ़ो_join(thपढ़ो, retval)                                          \
	(अणु                                                                     \
		पूर्णांक __ret = pthपढ़ो_join((thपढ़ो), (retval));                  \
		त्रुटि_सं = __ret;                                                 \
		अगर (__ret)                                                     \
			FAIL_ERRNO("pthread_join");                            \
		__ret;                                                         \
	पूर्ण)

अटल पूर्णांक poll_पढ़ो(पूर्णांक fd, अचिन्हित पूर्णांक समयout_sec)
अणु
	काष्ठा समयval समयout = अणु .tv_sec = समयout_sec पूर्ण;
	fd_set rfds;
	पूर्णांक r;

	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);

	r = select(fd + 1, &rfds, शून्य, शून्य, &समयout);
	अगर (r == 0)
		त्रुटि_सं = ETIME;

	वापस r == 1 ? 0 : -1;
पूर्ण

अटल पूर्णांक accept_समयout(पूर्णांक fd, काष्ठा sockaddr *addr, socklen_t *len,
			  अचिन्हित पूर्णांक समयout_sec)
अणु
	अगर (poll_पढ़ो(fd, समयout_sec))
		वापस -1;

	वापस accept(fd, addr, len);
पूर्ण

अटल पूर्णांक recv_समयout(पूर्णांक fd, व्योम *buf, माप_प्रकार len, पूर्णांक flags,
			अचिन्हित पूर्णांक समयout_sec)
अणु
	अगर (poll_पढ़ो(fd, समयout_sec))
		वापस -1;

	वापस recv(fd, buf, len, flags);
पूर्ण

अटल व्योम init_addr_loopback4(काष्ठा sockaddr_storage *ss, socklen_t *len)
अणु
	काष्ठा sockaddr_in *addr4 = स_रखो(ss, 0, माप(*ss));

	addr4->sin_family = AF_INET;
	addr4->sin_port = 0;
	addr4->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	*len = माप(*addr4);
पूर्ण

अटल व्योम init_addr_loopback6(काष्ठा sockaddr_storage *ss, socklen_t *len)
अणु
	काष्ठा sockaddr_in6 *addr6 = स_रखो(ss, 0, माप(*ss));

	addr6->sin6_family = AF_INET6;
	addr6->sin6_port = 0;
	addr6->sin6_addr = in6addr_loopback;
	*len = माप(*addr6);
पूर्ण

अटल व्योम init_addr_loopback(पूर्णांक family, काष्ठा sockaddr_storage *ss,
			       socklen_t *len)
अणु
	चयन (family) अणु
	हाल AF_INET:
		init_addr_loopback4(ss, len);
		वापस;
	हाल AF_INET6:
		init_addr_loopback6(ss, len);
		वापस;
	शेष:
		FAIL("unsupported address family %d", family);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा sockaddr *sockaddr(काष्ठा sockaddr_storage *ss)
अणु
	वापस (काष्ठा sockaddr *)ss;
पूर्ण

अटल पूर्णांक enable_reuseport(पूर्णांक s, पूर्णांक progfd)
अणु
	पूर्णांक err, one = 1;

	err = xsetsockopt(s, SOL_SOCKET, SO_REUSEPORT, &one, माप(one));
	अगर (err)
		वापस -1;
	err = xsetsockopt(s, SOL_SOCKET, SO_ATTACH_REUSEPORT_EBPF, &progfd,
			  माप(progfd));
	अगर (err)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक socket_loopback_reuseport(पूर्णांक family, पूर्णांक sotype, पूर्णांक progfd)
अणु
	काष्ठा sockaddr_storage addr;
	socklen_t len;
	पूर्णांक err, s;

	init_addr_loopback(family, &addr, &len);

	s = xsocket(family, sotype, 0);
	अगर (s == -1)
		वापस -1;

	अगर (progfd >= 0)
		enable_reuseport(s, progfd);

	err = xbind(s, sockaddr(&addr), len);
	अगर (err)
		जाओ बंद;

	अगर (sotype & SOCK_DGRAM)
		वापस s;

	err = xlisten(s, SOMAXCONN);
	अगर (err)
		जाओ बंद;

	वापस s;
बंद:
	xबंद(s);
	वापस -1;
पूर्ण

अटल पूर्णांक socket_loopback(पूर्णांक family, पूर्णांक sotype)
अणु
	वापस socket_loopback_reuseport(family, sotype, -1);
पूर्ण

अटल व्योम test_insert_invalid(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	u32 key = 0;
	u64 value;
	पूर्णांक err;

	value = -1;
	err = bpf_map_update_elem(mapfd, &key, &value, BPF_NOEXIST);
	अगर (!err || त्रुटि_सं != EINVAL)
		FAIL_ERRNO("map_update: expected EINVAL");

	value = पूर्णांक_उच्च;
	err = bpf_map_update_elem(mapfd, &key, &value, BPF_NOEXIST);
	अगर (!err || त्रुटि_सं != EBADF)
		FAIL_ERRNO("map_update: expected EBADF");
पूर्ण

अटल व्योम test_insert_खोलोed(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	u32 key = 0;
	u64 value;
	पूर्णांक err, s;

	s = xsocket(family, sotype, 0);
	अगर (s == -1)
		वापस;

	त्रुटि_सं = 0;
	value = s;
	err = bpf_map_update_elem(mapfd, &key, &value, BPF_NOEXIST);
	अगर (!err || त्रुटि_सं != EOPNOTSUPP)
		FAIL_ERRNO("map_update: expected EOPNOTSUPP");

	xबंद(s);
पूर्ण

अटल व्योम test_insert_bound(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	काष्ठा sockaddr_storage addr;
	socklen_t len;
	u32 key = 0;
	u64 value;
	पूर्णांक err, s;

	init_addr_loopback(family, &addr, &len);

	s = xsocket(family, sotype, 0);
	अगर (s == -1)
		वापस;

	err = xbind(s, sockaddr(&addr), len);
	अगर (err)
		जाओ बंद;

	त्रुटि_सं = 0;
	value = s;
	err = bpf_map_update_elem(mapfd, &key, &value, BPF_NOEXIST);
	अगर (!err || त्रुटि_सं != EOPNOTSUPP)
		FAIL_ERRNO("map_update: expected EOPNOTSUPP");
बंद:
	xबंद(s);
पूर्ण

अटल व्योम test_insert(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	u64 value;
	u32 key;
	पूर्णांक s;

	s = socket_loopback(family, sotype);
	अगर (s < 0)
		वापस;

	key = 0;
	value = s;
	xbpf_map_update_elem(mapfd, &key, &value, BPF_NOEXIST);
	xबंद(s);
पूर्ण

अटल व्योम test_delete_after_insert(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	u64 value;
	u32 key;
	पूर्णांक s;

	s = socket_loopback(family, sotype);
	अगर (s < 0)
		वापस;

	key = 0;
	value = s;
	xbpf_map_update_elem(mapfd, &key, &value, BPF_NOEXIST);
	xbpf_map_delete_elem(mapfd, &key);
	xबंद(s);
पूर्ण

अटल व्योम test_delete_after_बंद(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	पूर्णांक err, s;
	u64 value;
	u32 key;

	s = socket_loopback(family, sotype);
	अगर (s < 0)
		वापस;

	key = 0;
	value = s;
	xbpf_map_update_elem(mapfd, &key, &value, BPF_NOEXIST);

	xबंद(s);

	त्रुटि_सं = 0;
	err = bpf_map_delete_elem(mapfd, &key);
	अगर (!err || (त्रुटि_सं != EINVAL && त्रुटि_सं != ENOENT))
		/* SOCKMAP and SOCKHASH वापस dअगरferent error codes */
		FAIL_ERRNO("map_delete: expected EINVAL/EINVAL");
पूर्ण

अटल व्योम test_lookup_after_insert(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	u64 cookie, value;
	socklen_t len;
	u32 key;
	पूर्णांक s;

	s = socket_loopback(family, sotype);
	अगर (s < 0)
		वापस;

	key = 0;
	value = s;
	xbpf_map_update_elem(mapfd, &key, &value, BPF_NOEXIST);

	len = माप(cookie);
	xमाला_लोockopt(s, SOL_SOCKET, SO_COOKIE, &cookie, &len);

	xbpf_map_lookup_elem(mapfd, &key, &value);

	अगर (value != cookie) अणु
		FAIL("map_lookup: have %#llx, want %#llx",
		     (अचिन्हित दीर्घ दीर्घ)value, (अचिन्हित दीर्घ दीर्घ)cookie);
	पूर्ण

	xबंद(s);
पूर्ण

अटल व्योम test_lookup_after_delete(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	पूर्णांक err, s;
	u64 value;
	u32 key;

	s = socket_loopback(family, sotype);
	अगर (s < 0)
		वापस;

	key = 0;
	value = s;
	xbpf_map_update_elem(mapfd, &key, &value, BPF_NOEXIST);
	xbpf_map_delete_elem(mapfd, &key);

	त्रुटि_सं = 0;
	err = bpf_map_lookup_elem(mapfd, &key, &value);
	अगर (!err || त्रुटि_सं != ENOENT)
		FAIL_ERRNO("map_lookup: expected ENOENT");

	xबंद(s);
पूर्ण

अटल व्योम test_lookup_32_bit_value(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	u32 key, value32;
	पूर्णांक err, s;

	s = socket_loopback(family, sotype);
	अगर (s < 0)
		वापस;

	mapfd = bpf_create_map(BPF_MAP_TYPE_SOCKMAP, माप(key),
			       माप(value32), 1, 0);
	अगर (mapfd < 0) अणु
		FAIL_ERRNO("map_create");
		जाओ बंद;
	पूर्ण

	key = 0;
	value32 = s;
	xbpf_map_update_elem(mapfd, &key, &value32, BPF_NOEXIST);

	त्रुटि_सं = 0;
	err = bpf_map_lookup_elem(mapfd, &key, &value32);
	अगर (!err || त्रुटि_सं != ENOSPC)
		FAIL_ERRNO("map_lookup: expected ENOSPC");

	xबंद(mapfd);
बंद:
	xबंद(s);
पूर्ण

अटल व्योम test_update_existing(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	पूर्णांक s1, s2;
	u64 value;
	u32 key;

	s1 = socket_loopback(family, sotype);
	अगर (s1 < 0)
		वापस;

	s2 = socket_loopback(family, sotype);
	अगर (s2 < 0)
		जाओ बंद_s1;

	key = 0;
	value = s1;
	xbpf_map_update_elem(mapfd, &key, &value, BPF_NOEXIST);

	value = s2;
	xbpf_map_update_elem(mapfd, &key, &value, BPF_EXIST);
	xबंद(s2);
बंद_s1:
	xबंद(s1);
पूर्ण

/* Exercise the code path where we destroy child sockets that never
 * got accept()'ed, aka orphans, when parent socket माला_लो बंदd.
 */
अटल व्योम test_destroy_orphan_child(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	काष्ठा sockaddr_storage addr;
	socklen_t len;
	पूर्णांक err, s, c;
	u64 value;
	u32 key;

	s = socket_loopback(family, sotype);
	अगर (s < 0)
		वापस;

	len = माप(addr);
	err = xमाला_लोockname(s, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_srv;

	key = 0;
	value = s;
	xbpf_map_update_elem(mapfd, &key, &value, BPF_NOEXIST);

	c = xsocket(family, sotype, 0);
	अगर (c == -1)
		जाओ बंद_srv;

	xconnect(c, sockaddr(&addr), len);
	xबंद(c);
बंद_srv:
	xबंद(s);
पूर्ण

/* Perक्रमm a passive खोलो after removing listening socket from SOCKMAP
 * to ensure that callbacks get restored properly.
 */
अटल व्योम test_clone_after_delete(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	काष्ठा sockaddr_storage addr;
	socklen_t len;
	पूर्णांक err, s, c;
	u64 value;
	u32 key;

	s = socket_loopback(family, sotype);
	अगर (s < 0)
		वापस;

	len = माप(addr);
	err = xमाला_लोockname(s, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_srv;

	key = 0;
	value = s;
	xbpf_map_update_elem(mapfd, &key, &value, BPF_NOEXIST);
	xbpf_map_delete_elem(mapfd, &key);

	c = xsocket(family, sotype, 0);
	अगर (c < 0)
		जाओ बंद_srv;

	xconnect(c, sockaddr(&addr), len);
	xबंद(c);
बंद_srv:
	xबंद(s);
पूर्ण

/* Check that child socket that got created जबतक parent was in a
 * SOCKMAP, but got accept()'ed only after the parent has been हटाओd
 * from SOCKMAP, माला_लो cloned without parent psock state or callbacks.
 */
अटल व्योम test_accept_after_delete(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	काष्ठा sockaddr_storage addr;
	स्थिर u32 zero = 0;
	पूर्णांक err, s, c, p;
	socklen_t len;
	u64 value;

	s = socket_loopback(family, sotype | SOCK_NONBLOCK);
	अगर (s == -1)
		वापस;

	len = माप(addr);
	err = xमाला_लोockname(s, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_srv;

	value = s;
	err = xbpf_map_update_elem(mapfd, &zero, &value, BPF_NOEXIST);
	अगर (err)
		जाओ बंद_srv;

	c = xsocket(family, sotype, 0);
	अगर (c == -1)
		जाओ बंद_srv;

	/* Create child जबतक parent is in sockmap */
	err = xconnect(c, sockaddr(&addr), len);
	अगर (err)
		जाओ बंद_cli;

	/* Remove parent from sockmap */
	err = xbpf_map_delete_elem(mapfd, &zero);
	अगर (err)
		जाओ बंद_cli;

	p = xaccept_nonblock(s, शून्य, शून्य);
	अगर (p == -1)
		जाओ बंद_cli;

	/* Check that child sk_user_data is not set */
	value = p;
	xbpf_map_update_elem(mapfd, &zero, &value, BPF_NOEXIST);

	xबंद(p);
बंद_cli:
	xबंद(c);
बंद_srv:
	xबंद(s);
पूर्ण

/* Check that child socket that got created and accepted जबतक parent
 * was in a SOCKMAP is cloned without parent psock state or callbacks.
 */
अटल व्योम test_accept_beक्रमe_delete(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	काष्ठा sockaddr_storage addr;
	स्थिर u32 zero = 0, one = 1;
	पूर्णांक err, s, c, p;
	socklen_t len;
	u64 value;

	s = socket_loopback(family, sotype | SOCK_NONBLOCK);
	अगर (s == -1)
		वापस;

	len = माप(addr);
	err = xमाला_लोockname(s, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_srv;

	value = s;
	err = xbpf_map_update_elem(mapfd, &zero, &value, BPF_NOEXIST);
	अगर (err)
		जाओ बंद_srv;

	c = xsocket(family, sotype, 0);
	अगर (c == -1)
		जाओ बंद_srv;

	/* Create & accept child जबतक parent is in sockmap */
	err = xconnect(c, sockaddr(&addr), len);
	अगर (err)
		जाओ बंद_cli;

	p = xaccept_nonblock(s, शून्य, शून्य);
	अगर (p == -1)
		जाओ बंद_cli;

	/* Check that child sk_user_data is not set */
	value = p;
	xbpf_map_update_elem(mapfd, &one, &value, BPF_NOEXIST);

	xबंद(p);
बंद_cli:
	xबंद(c);
बंद_srv:
	xबंद(s);
पूर्ण

काष्ठा connect_accept_ctx अणु
	पूर्णांक sockfd;
	अचिन्हित पूर्णांक करोne;
	अचिन्हित पूर्णांक nr_iter;
पूर्ण;

अटल bool is_thपढ़ो_करोne(काष्ठा connect_accept_ctx *ctx)
अणु
	वापस READ_ONCE(ctx->करोne);
पूर्ण

अटल व्योम *connect_accept_thपढ़ो(व्योम *arg)
अणु
	काष्ठा connect_accept_ctx *ctx = arg;
	काष्ठा sockaddr_storage addr;
	पूर्णांक family, socktype;
	socklen_t len;
	पूर्णांक err, i, s;

	s = ctx->sockfd;

	len = माप(addr);
	err = xमाला_लोockname(s, sockaddr(&addr), &len);
	अगर (err)
		जाओ करोne;

	len = माप(family);
	err = xमाला_लोockopt(s, SOL_SOCKET, SO_DOMAIN, &family, &len);
	अगर (err)
		जाओ करोne;

	len = माप(socktype);
	err = xमाला_लोockopt(s, SOL_SOCKET, SO_TYPE, &socktype, &len);
	अगर (err)
		जाओ करोne;

	क्रम (i = 0; i < ctx->nr_iter; i++) अणु
		पूर्णांक c, p;

		c = xsocket(family, socktype, 0);
		अगर (c < 0)
			अवरोध;

		err = xconnect(c, (काष्ठा sockaddr *)&addr, माप(addr));
		अगर (err) अणु
			xबंद(c);
			अवरोध;
		पूर्ण

		p = xaccept_nonblock(s, शून्य, शून्य);
		अगर (p < 0) अणु
			xबंद(c);
			अवरोध;
		पूर्ण

		xबंद(p);
		xबंद(c);
	पूर्ण
करोne:
	WRITE_ONCE(ctx->करोne, 1);
	वापस शून्य;
पूर्ण

अटल व्योम test_syn_recv_insert_delete(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd)
अणु
	काष्ठा connect_accept_ctx ctx = अणु 0 पूर्ण;
	काष्ठा sockaddr_storage addr;
	socklen_t len;
	u32 zero = 0;
	pthपढ़ो_t t;
	पूर्णांक err, s;
	u64 value;

	s = socket_loopback(family, sotype | SOCK_NONBLOCK);
	अगर (s < 0)
		वापस;

	len = माप(addr);
	err = xमाला_लोockname(s, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद;

	ctx.sockfd = s;
	ctx.nr_iter = 1000;

	err = xpthपढ़ो_create(&t, शून्य, connect_accept_thपढ़ो, &ctx);
	अगर (err)
		जाओ बंद;

	value = s;
	जबतक (!is_thपढ़ो_करोne(&ctx)) अणु
		err = xbpf_map_update_elem(mapfd, &zero, &value, BPF_NOEXIST);
		अगर (err)
			अवरोध;

		err = xbpf_map_delete_elem(mapfd, &zero);
		अगर (err)
			अवरोध;
	पूर्ण

	xpthपढ़ो_join(t, शून्य);
बंद:
	xबंद(s);
पूर्ण

अटल व्योम *listen_thपढ़ो(व्योम *arg)
अणु
	काष्ठा sockaddr unspec = अणु AF_UNSPEC पूर्ण;
	काष्ठा connect_accept_ctx *ctx = arg;
	पूर्णांक err, i, s;

	s = ctx->sockfd;

	क्रम (i = 0; i < ctx->nr_iter; i++) अणु
		err = xlisten(s, 1);
		अगर (err)
			अवरोध;
		err = xconnect(s, &unspec, माप(unspec));
		अगर (err)
			अवरोध;
	पूर्ण

	WRITE_ONCE(ctx->करोne, 1);
	वापस शून्य;
पूर्ण

अटल व्योम test_race_insert_listen(पूर्णांक family, पूर्णांक socktype, पूर्णांक mapfd)
अणु
	काष्ठा connect_accept_ctx ctx = अणु 0 पूर्ण;
	स्थिर u32 zero = 0;
	स्थिर पूर्णांक one = 1;
	pthपढ़ो_t t;
	पूर्णांक err, s;
	u64 value;

	s = xsocket(family, socktype, 0);
	अगर (s < 0)
		वापस;

	err = xsetsockopt(s, SOL_SOCKET, SO_REUSEADDR, &one, माप(one));
	अगर (err)
		जाओ बंद;

	ctx.sockfd = s;
	ctx.nr_iter = 10000;

	err = pthपढ़ो_create(&t, शून्य, listen_thपढ़ो, &ctx);
	अगर (err)
		जाओ बंद;

	value = s;
	जबतक (!is_thपढ़ो_करोne(&ctx)) अणु
		err = bpf_map_update_elem(mapfd, &zero, &value, BPF_NOEXIST);
		/* Expecting EOPNOTSUPP beक्रमe listen() */
		अगर (err && त्रुटि_सं != EOPNOTSUPP) अणु
			FAIL_ERRNO("map_update");
			अवरोध;
		पूर्ण

		err = bpf_map_delete_elem(mapfd, &zero);
		/* Expecting no entry after unhash on connect(AF_UNSPEC) */
		अगर (err && त्रुटि_सं != EINVAL && त्रुटि_सं != ENOENT) अणु
			FAIL_ERRNO("map_delete");
			अवरोध;
		पूर्ण
	पूर्ण

	xpthपढ़ो_join(t, शून्य);
बंद:
	xबंद(s);
पूर्ण

अटल व्योम zero_verdict_count(पूर्णांक mapfd)
अणु
	अचिन्हित पूर्णांक zero = 0;
	पूर्णांक key;

	key = SK_DROP;
	xbpf_map_update_elem(mapfd, &key, &zero, BPF_ANY);
	key = SK_PASS;
	xbpf_map_update_elem(mapfd, &key, &zero, BPF_ANY);
पूर्ण

क्रमागत redir_mode अणु
	REसूची_INGRESS,
	REसूची_EGRESS,
पूर्ण;

अटल स्थिर अक्षर *redir_mode_str(क्रमागत redir_mode mode)
अणु
	चयन (mode) अणु
	हाल REसूची_INGRESS:
		वापस "ingress";
	हाल REसूची_EGRESS:
		वापस "egress";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल व्योम redir_to_connected(पूर्णांक family, पूर्णांक sotype, पूर्णांक sock_mapfd,
			       पूर्णांक verd_mapfd, क्रमागत redir_mode mode)
अणु
	स्थिर अक्षर *log_prefix = redir_mode_str(mode);
	काष्ठा sockaddr_storage addr;
	पूर्णांक s, c0, c1, p0, p1;
	अचिन्हित पूर्णांक pass;
	socklen_t len;
	पूर्णांक err, n;
	u64 value;
	u32 key;
	अक्षर b;

	zero_verdict_count(verd_mapfd);

	s = socket_loopback(family, sotype | SOCK_NONBLOCK);
	अगर (s < 0)
		वापस;

	len = माप(addr);
	err = xमाला_लोockname(s, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_srv;

	c0 = xsocket(family, sotype, 0);
	अगर (c0 < 0)
		जाओ बंद_srv;
	err = xconnect(c0, sockaddr(&addr), len);
	अगर (err)
		जाओ बंद_cli0;

	p0 = xaccept_nonblock(s, शून्य, शून्य);
	अगर (p0 < 0)
		जाओ बंद_cli0;

	c1 = xsocket(family, sotype, 0);
	अगर (c1 < 0)
		जाओ बंद_peer0;
	err = xconnect(c1, sockaddr(&addr), len);
	अगर (err)
		जाओ बंद_cli1;

	p1 = xaccept_nonblock(s, शून्य, शून्य);
	अगर (p1 < 0)
		जाओ बंद_cli1;

	key = 0;
	value = p0;
	err = xbpf_map_update_elem(sock_mapfd, &key, &value, BPF_NOEXIST);
	अगर (err)
		जाओ बंद_peer1;

	key = 1;
	value = p1;
	err = xbpf_map_update_elem(sock_mapfd, &key, &value, BPF_NOEXIST);
	अगर (err)
		जाओ बंद_peer1;

	n = ग_लिखो(mode == REसूची_INGRESS ? c1 : p1, "a", 1);
	अगर (n < 0)
		FAIL_ERRNO("%s: write", log_prefix);
	अगर (n == 0)
		FAIL("%s: incomplete write", log_prefix);
	अगर (n < 1)
		जाओ बंद_peer1;

	key = SK_PASS;
	err = xbpf_map_lookup_elem(verd_mapfd, &key, &pass);
	अगर (err)
		जाओ बंद_peer1;
	अगर (pass != 1)
		FAIL("%s: want pass count 1, have %d", log_prefix, pass);

	n = पढ़ो(c0, &b, 1);
	अगर (n < 0)
		FAIL_ERRNO("%s: read", log_prefix);
	अगर (n == 0)
		FAIL("%s: incomplete read", log_prefix);

बंद_peer1:
	xबंद(p1);
बंद_cli1:
	xबंद(c1);
बंद_peer0:
	xबंद(p0);
बंद_cli0:
	xबंद(c0);
बंद_srv:
	xबंद(s);
पूर्ण

अटल व्योम test_skb_redir_to_connected(काष्ठा test_sockmap_listen *skel,
					काष्ठा bpf_map *inner_map, पूर्णांक family,
					पूर्णांक sotype)
अणु
	पूर्णांक verdict = bpf_program__fd(skel->progs.prog_stream_verdict);
	पूर्णांक parser = bpf_program__fd(skel->progs.prog_stream_parser);
	पूर्णांक verdict_map = bpf_map__fd(skel->maps.verdict_map);
	पूर्णांक sock_map = bpf_map__fd(inner_map);
	पूर्णांक err;

	err = xbpf_prog_attach(parser, sock_map, BPF_SK_SKB_STREAM_PARSER, 0);
	अगर (err)
		वापस;
	err = xbpf_prog_attach(verdict, sock_map, BPF_SK_SKB_STREAM_VERDICT, 0);
	अगर (err)
		जाओ detach;

	redir_to_connected(family, sotype, sock_map, verdict_map,
			   REसूची_INGRESS);

	xbpf_prog_detach2(verdict, sock_map, BPF_SK_SKB_STREAM_VERDICT);
detach:
	xbpf_prog_detach2(parser, sock_map, BPF_SK_SKB_STREAM_PARSER);
पूर्ण

अटल व्योम test_msg_redir_to_connected(काष्ठा test_sockmap_listen *skel,
					काष्ठा bpf_map *inner_map, पूर्णांक family,
					पूर्णांक sotype)
अणु
	पूर्णांक verdict = bpf_program__fd(skel->progs.prog_msg_verdict);
	पूर्णांक verdict_map = bpf_map__fd(skel->maps.verdict_map);
	पूर्णांक sock_map = bpf_map__fd(inner_map);
	पूर्णांक err;

	err = xbpf_prog_attach(verdict, sock_map, BPF_SK_MSG_VERDICT, 0);
	अगर (err)
		वापस;

	redir_to_connected(family, sotype, sock_map, verdict_map, REसूची_EGRESS);

	xbpf_prog_detach2(verdict, sock_map, BPF_SK_MSG_VERDICT);
पूर्ण

अटल व्योम redir_to_listening(पूर्णांक family, पूर्णांक sotype, पूर्णांक sock_mapfd,
			       पूर्णांक verd_mapfd, क्रमागत redir_mode mode)
अणु
	स्थिर अक्षर *log_prefix = redir_mode_str(mode);
	काष्ठा sockaddr_storage addr;
	पूर्णांक s, c, p, err, n;
	अचिन्हित पूर्णांक drop;
	socklen_t len;
	u64 value;
	u32 key;

	zero_verdict_count(verd_mapfd);

	s = socket_loopback(family, sotype | SOCK_NONBLOCK);
	अगर (s < 0)
		वापस;

	len = माप(addr);
	err = xमाला_लोockname(s, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_srv;

	c = xsocket(family, sotype, 0);
	अगर (c < 0)
		जाओ बंद_srv;
	err = xconnect(c, sockaddr(&addr), len);
	अगर (err)
		जाओ बंद_cli;

	p = xaccept_nonblock(s, शून्य, शून्य);
	अगर (p < 0)
		जाओ बंद_cli;

	key = 0;
	value = s;
	err = xbpf_map_update_elem(sock_mapfd, &key, &value, BPF_NOEXIST);
	अगर (err)
		जाओ बंद_peer;

	key = 1;
	value = p;
	err = xbpf_map_update_elem(sock_mapfd, &key, &value, BPF_NOEXIST);
	अगर (err)
		जाओ बंद_peer;

	n = ग_लिखो(mode == REसूची_INGRESS ? c : p, "a", 1);
	अगर (n < 0 && त्रुटि_सं != EACCES)
		FAIL_ERRNO("%s: write", log_prefix);
	अगर (n == 0)
		FAIL("%s: incomplete write", log_prefix);
	अगर (n < 1)
		जाओ बंद_peer;

	key = SK_DROP;
	err = xbpf_map_lookup_elem(verd_mapfd, &key, &drop);
	अगर (err)
		जाओ बंद_peer;
	अगर (drop != 1)
		FAIL("%s: want drop count 1, have %d", log_prefix, drop);

बंद_peer:
	xबंद(p);
बंद_cli:
	xबंद(c);
बंद_srv:
	xबंद(s);
पूर्ण

अटल व्योम test_skb_redir_to_listening(काष्ठा test_sockmap_listen *skel,
					काष्ठा bpf_map *inner_map, पूर्णांक family,
					पूर्णांक sotype)
अणु
	पूर्णांक verdict = bpf_program__fd(skel->progs.prog_stream_verdict);
	पूर्णांक parser = bpf_program__fd(skel->progs.prog_stream_parser);
	पूर्णांक verdict_map = bpf_map__fd(skel->maps.verdict_map);
	पूर्णांक sock_map = bpf_map__fd(inner_map);
	पूर्णांक err;

	err = xbpf_prog_attach(parser, sock_map, BPF_SK_SKB_STREAM_PARSER, 0);
	अगर (err)
		वापस;
	err = xbpf_prog_attach(verdict, sock_map, BPF_SK_SKB_STREAM_VERDICT, 0);
	अगर (err)
		जाओ detach;

	redir_to_listening(family, sotype, sock_map, verdict_map,
			   REसूची_INGRESS);

	xbpf_prog_detach2(verdict, sock_map, BPF_SK_SKB_STREAM_VERDICT);
detach:
	xbpf_prog_detach2(parser, sock_map, BPF_SK_SKB_STREAM_PARSER);
पूर्ण

अटल व्योम test_msg_redir_to_listening(काष्ठा test_sockmap_listen *skel,
					काष्ठा bpf_map *inner_map, पूर्णांक family,
					पूर्णांक sotype)
अणु
	पूर्णांक verdict = bpf_program__fd(skel->progs.prog_msg_verdict);
	पूर्णांक verdict_map = bpf_map__fd(skel->maps.verdict_map);
	पूर्णांक sock_map = bpf_map__fd(inner_map);
	पूर्णांक err;

	err = xbpf_prog_attach(verdict, sock_map, BPF_SK_MSG_VERDICT, 0);
	अगर (err)
		वापस;

	redir_to_listening(family, sotype, sock_map, verdict_map, REसूची_EGRESS);

	xbpf_prog_detach2(verdict, sock_map, BPF_SK_MSG_VERDICT);
पूर्ण

अटल व्योम test_reuseport_select_listening(पूर्णांक family, पूर्णांक sotype,
					    पूर्णांक sock_map, पूर्णांक verd_map,
					    पूर्णांक reuseport_prog)
अणु
	काष्ठा sockaddr_storage addr;
	अचिन्हित पूर्णांक pass;
	पूर्णांक s, c, err;
	socklen_t len;
	u64 value;
	u32 key;

	zero_verdict_count(verd_map);

	s = socket_loopback_reuseport(family, sotype | SOCK_NONBLOCK,
				      reuseport_prog);
	अगर (s < 0)
		वापस;

	len = माप(addr);
	err = xमाला_लोockname(s, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_srv;

	key = 0;
	value = s;
	err = xbpf_map_update_elem(sock_map, &key, &value, BPF_NOEXIST);
	अगर (err)
		जाओ बंद_srv;

	c = xsocket(family, sotype, 0);
	अगर (c < 0)
		जाओ बंद_srv;
	err = xconnect(c, sockaddr(&addr), len);
	अगर (err)
		जाओ बंद_cli;

	अगर (sotype == SOCK_STREAM) अणु
		पूर्णांक p;

		p = xaccept_nonblock(s, शून्य, शून्य);
		अगर (p < 0)
			जाओ बंद_cli;
		xबंद(p);
	पूर्ण अन्यथा अणु
		अक्षर b = 'a';
		sमाप_प्रकार n;

		n = xsend(c, &b, माप(b), 0);
		अगर (n == -1)
			जाओ बंद_cli;

		n = xrecv_nonblock(s, &b, माप(b), 0);
		अगर (n == -1)
			जाओ बंद_cli;
	पूर्ण

	key = SK_PASS;
	err = xbpf_map_lookup_elem(verd_map, &key, &pass);
	अगर (err)
		जाओ बंद_cli;
	अगर (pass != 1)
		FAIL("want pass count 1, have %d", pass);

बंद_cli:
	xबंद(c);
बंद_srv:
	xबंद(s);
पूर्ण

अटल व्योम test_reuseport_select_connected(पूर्णांक family, पूर्णांक sotype,
					    पूर्णांक sock_map, पूर्णांक verd_map,
					    पूर्णांक reuseport_prog)
अणु
	काष्ठा sockaddr_storage addr;
	पूर्णांक s, c0, c1, p0, err;
	अचिन्हित पूर्णांक drop;
	socklen_t len;
	u64 value;
	u32 key;

	zero_verdict_count(verd_map);

	s = socket_loopback_reuseport(family, sotype, reuseport_prog);
	अगर (s < 0)
		वापस;

	/* Populate sock_map[0] to aव्योम ENOENT on first connection */
	key = 0;
	value = s;
	err = xbpf_map_update_elem(sock_map, &key, &value, BPF_NOEXIST);
	अगर (err)
		जाओ बंद_srv;

	len = माप(addr);
	err = xमाला_लोockname(s, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_srv;

	c0 = xsocket(family, sotype, 0);
	अगर (c0 < 0)
		जाओ बंद_srv;

	err = xconnect(c0, sockaddr(&addr), len);
	अगर (err)
		जाओ बंद_cli0;

	अगर (sotype == SOCK_STREAM) अणु
		p0 = xaccept_nonblock(s, शून्य, शून्य);
		अगर (p0 < 0)
			जाओ बंद_cli0;
	पूर्ण अन्यथा अणु
		p0 = xsocket(family, sotype, 0);
		अगर (p0 < 0)
			जाओ बंद_cli0;

		len = माप(addr);
		err = xमाला_लोockname(c0, sockaddr(&addr), &len);
		अगर (err)
			जाओ बंद_cli0;

		err = xconnect(p0, sockaddr(&addr), len);
		अगर (err)
			जाओ बंद_cli0;
	पूर्ण

	/* Update sock_map[0] to redirect to a connected socket */
	key = 0;
	value = p0;
	err = xbpf_map_update_elem(sock_map, &key, &value, BPF_EXIST);
	अगर (err)
		जाओ बंद_peer0;

	c1 = xsocket(family, sotype, 0);
	अगर (c1 < 0)
		जाओ बंद_peer0;

	len = माप(addr);
	err = xमाला_लोockname(s, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_srv;

	त्रुटि_सं = 0;
	err = connect(c1, sockaddr(&addr), len);
	अगर (sotype == SOCK_DGRAM) अणु
		अक्षर b = 'a';
		sमाप_प्रकार n;

		n = xsend(c1, &b, माप(b), 0);
		अगर (n == -1)
			जाओ बंद_cli1;

		n = recv_समयout(c1, &b, माप(b), 0, IO_TIMEOUT_SEC);
		err = n == -1;
	पूर्ण
	अगर (!err || त्रुटि_सं != ECONNREFUSED)
		FAIL_ERRNO("connect: expected ECONNREFUSED");

	key = SK_DROP;
	err = xbpf_map_lookup_elem(verd_map, &key, &drop);
	अगर (err)
		जाओ बंद_cli1;
	अगर (drop != 1)
		FAIL("want drop count 1, have %d", drop);

बंद_cli1:
	xबंद(c1);
बंद_peer0:
	xबंद(p0);
बंद_cli0:
	xबंद(c0);
बंद_srv:
	xबंद(s);
पूर्ण

/* Check that redirecting across reuseport groups is not allowed. */
अटल व्योम test_reuseport_mixed_groups(पूर्णांक family, पूर्णांक sotype, पूर्णांक sock_map,
					पूर्णांक verd_map, पूर्णांक reuseport_prog)
अणु
	काष्ठा sockaddr_storage addr;
	पूर्णांक s1, s2, c, err;
	अचिन्हित पूर्णांक drop;
	socklen_t len;
	u64 value;
	u32 key;

	zero_verdict_count(verd_map);

	/* Create two listeners, each in its own reuseport group */
	s1 = socket_loopback_reuseport(family, sotype, reuseport_prog);
	अगर (s1 < 0)
		वापस;

	s2 = socket_loopback_reuseport(family, sotype, reuseport_prog);
	अगर (s2 < 0)
		जाओ बंद_srv1;

	key = 0;
	value = s1;
	err = xbpf_map_update_elem(sock_map, &key, &value, BPF_NOEXIST);
	अगर (err)
		जाओ बंद_srv2;

	key = 1;
	value = s2;
	err = xbpf_map_update_elem(sock_map, &key, &value, BPF_NOEXIST);

	/* Connect to s2, reuseport BPF selects s1 via sock_map[0] */
	len = माप(addr);
	err = xमाला_लोockname(s2, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_srv2;

	c = xsocket(family, sotype, 0);
	अगर (c < 0)
		जाओ बंद_srv2;

	err = connect(c, sockaddr(&addr), len);
	अगर (sotype == SOCK_DGRAM) अणु
		अक्षर b = 'a';
		sमाप_प्रकार n;

		n = xsend(c, &b, माप(b), 0);
		अगर (n == -1)
			जाओ बंद_cli;

		n = recv_समयout(c, &b, माप(b), 0, IO_TIMEOUT_SEC);
		err = n == -1;
	पूर्ण
	अगर (!err || त्रुटि_सं != ECONNREFUSED) अणु
		FAIL_ERRNO("connect: expected ECONNREFUSED");
		जाओ बंद_cli;
	पूर्ण

	/* Expect drop, can't redirect outside of reuseport group */
	key = SK_DROP;
	err = xbpf_map_lookup_elem(verd_map, &key, &drop);
	अगर (err)
		जाओ बंद_cli;
	अगर (drop != 1)
		FAIL("want drop count 1, have %d", drop);

बंद_cli:
	xबंद(c);
बंद_srv2:
	xबंद(s2);
बंद_srv1:
	xबंद(s1);
पूर्ण

#घोषणा TEST(fn, ...)                                                          \
	अणु                                                                      \
		fn, #fn, __VA_ARGS__                                           \
	पूर्ण

अटल व्योम test_ops_cleanup(स्थिर काष्ठा bpf_map *map)
अणु
	स्थिर काष्ठा bpf_map_def *def;
	पूर्णांक err, mapfd;
	u32 key;

	def = bpf_map__def(map);
	mapfd = bpf_map__fd(map);

	क्रम (key = 0; key < def->max_entries; key++) अणु
		err = bpf_map_delete_elem(mapfd, &key);
		अगर (err && त्रुटि_सं != EINVAL && त्रुटि_सं != ENOENT)
			FAIL_ERRNO("map_delete: expected EINVAL/ENOENT");
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *family_str(sa_family_t family)
अणु
	चयन (family) अणु
	हाल AF_INET:
		वापस "IPv4";
	हाल AF_INET6:
		वापस "IPv6";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *map_type_str(स्थिर काष्ठा bpf_map *map)
अणु
	स्थिर काष्ठा bpf_map_def *def;

	def = bpf_map__def(map);
	अगर (IS_ERR(def))
		वापस "invalid";

	चयन (def->type) अणु
	हाल BPF_MAP_TYPE_SOCKMAP:
		वापस "sockmap";
	हाल BPF_MAP_TYPE_SOCKHASH:
		वापस "sockhash";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *sotype_str(पूर्णांक sotype)
अणु
	चयन (sotype) अणु
	हाल SOCK_DGRAM:
		वापस "UDP";
	हाल SOCK_STREAM:
		वापस "TCP";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल व्योम test_ops(काष्ठा test_sockmap_listen *skel, काष्ठा bpf_map *map,
		     पूर्णांक family, पूर्णांक sotype)
अणु
	स्थिर काष्ठा op_test अणु
		व्योम (*fn)(पूर्णांक family, पूर्णांक sotype, पूर्णांक mapfd);
		स्थिर अक्षर *name;
		पूर्णांक sotype;
	पूर्ण tests[] = अणु
		/* insert */
		TEST(test_insert_invalid),
		TEST(test_insert_खोलोed),
		TEST(test_insert_bound, SOCK_STREAM),
		TEST(test_insert),
		/* delete */
		TEST(test_delete_after_insert),
		TEST(test_delete_after_बंद),
		/* lookup */
		TEST(test_lookup_after_insert),
		TEST(test_lookup_after_delete),
		TEST(test_lookup_32_bit_value),
		/* update */
		TEST(test_update_existing),
		/* races with insert/delete */
		TEST(test_destroy_orphan_child, SOCK_STREAM),
		TEST(test_syn_recv_insert_delete, SOCK_STREAM),
		TEST(test_race_insert_listen, SOCK_STREAM),
		/* child clone */
		TEST(test_clone_after_delete, SOCK_STREAM),
		TEST(test_accept_after_delete, SOCK_STREAM),
		TEST(test_accept_beक्रमe_delete, SOCK_STREAM),
	पूर्ण;
	स्थिर अक्षर *family_name, *map_name, *sotype_name;
	स्थिर काष्ठा op_test *t;
	अक्षर s[MAX_TEST_NAME];
	पूर्णांक map_fd;

	family_name = family_str(family);
	map_name = map_type_str(map);
	sotype_name = sotype_str(sotype);
	map_fd = bpf_map__fd(map);

	क्रम (t = tests; t < tests + ARRAY_SIZE(tests); t++) अणु
		snम_लिखो(s, माप(s), "%s %s %s %s", map_name, family_name,
			 sotype_name, t->name);

		अगर (t->sotype != 0 && t->sotype != sotype)
			जारी;

		अगर (!test__start_subtest(s))
			जारी;

		t->fn(family, sotype, map_fd);
		test_ops_cleanup(map);
	पूर्ण
पूर्ण

अटल व्योम test_redir(काष्ठा test_sockmap_listen *skel, काष्ठा bpf_map *map,
		       पूर्णांक family, पूर्णांक sotype)
अणु
	स्थिर काष्ठा redir_test अणु
		व्योम (*fn)(काष्ठा test_sockmap_listen *skel,
			   काष्ठा bpf_map *map, पूर्णांक family, पूर्णांक sotype);
		स्थिर अक्षर *name;
	पूर्ण tests[] = अणु
		TEST(test_skb_redir_to_connected),
		TEST(test_skb_redir_to_listening),
		TEST(test_msg_redir_to_connected),
		TEST(test_msg_redir_to_listening),
	पूर्ण;
	स्थिर अक्षर *family_name, *map_name;
	स्थिर काष्ठा redir_test *t;
	अक्षर s[MAX_TEST_NAME];

	family_name = family_str(family);
	map_name = map_type_str(map);

	क्रम (t = tests; t < tests + ARRAY_SIZE(tests); t++) अणु
		snम_लिखो(s, माप(s), "%s %s %s", map_name, family_name,
			 t->name);

		अगर (!test__start_subtest(s))
			जारी;

		t->fn(skel, map, family, sotype);
	पूर्ण
पूर्ण

अटल व्योम test_reuseport(काष्ठा test_sockmap_listen *skel,
			   काष्ठा bpf_map *map, पूर्णांक family, पूर्णांक sotype)
अणु
	स्थिर काष्ठा reuseport_test अणु
		व्योम (*fn)(पूर्णांक family, पूर्णांक sotype, पूर्णांक socket_map,
			   पूर्णांक verdict_map, पूर्णांक reuseport_prog);
		स्थिर अक्षर *name;
		पूर्णांक sotype;
	पूर्ण tests[] = अणु
		TEST(test_reuseport_select_listening),
		TEST(test_reuseport_select_connected),
		TEST(test_reuseport_mixed_groups),
	पूर्ण;
	पूर्णांक socket_map, verdict_map, reuseport_prog;
	स्थिर अक्षर *family_name, *map_name, *sotype_name;
	स्थिर काष्ठा reuseport_test *t;
	अक्षर s[MAX_TEST_NAME];

	family_name = family_str(family);
	map_name = map_type_str(map);
	sotype_name = sotype_str(sotype);

	socket_map = bpf_map__fd(map);
	verdict_map = bpf_map__fd(skel->maps.verdict_map);
	reuseport_prog = bpf_program__fd(skel->progs.prog_reuseport);

	क्रम (t = tests; t < tests + ARRAY_SIZE(tests); t++) अणु
		snम_लिखो(s, माप(s), "%s %s %s %s", map_name, family_name,
			 sotype_name, t->name);

		अगर (t->sotype != 0 && t->sotype != sotype)
			जारी;

		अगर (!test__start_subtest(s))
			जारी;

		t->fn(family, sotype, socket_map, verdict_map, reuseport_prog);
	पूर्ण
पूर्ण

अटल व्योम udp_redir_to_connected(पूर्णांक family, पूर्णांक sotype, पूर्णांक sock_mapfd,
				   पूर्णांक verd_mapfd, क्रमागत redir_mode mode)
अणु
	स्थिर अक्षर *log_prefix = redir_mode_str(mode);
	काष्ठा sockaddr_storage addr;
	पूर्णांक c0, c1, p0, p1;
	अचिन्हित पूर्णांक pass;
	socklen_t len;
	पूर्णांक err, n;
	u64 value;
	u32 key;
	अक्षर b;

	zero_verdict_count(verd_mapfd);

	p0 = socket_loopback(family, sotype | SOCK_NONBLOCK);
	अगर (p0 < 0)
		वापस;
	len = माप(addr);
	err = xमाला_लोockname(p0, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_peer0;

	c0 = xsocket(family, sotype | SOCK_NONBLOCK, 0);
	अगर (c0 < 0)
		जाओ बंद_peer0;
	err = xconnect(c0, sockaddr(&addr), len);
	अगर (err)
		जाओ बंद_cli0;
	err = xमाला_लोockname(c0, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_cli0;
	err = xconnect(p0, sockaddr(&addr), len);
	अगर (err)
		जाओ बंद_cli0;

	p1 = socket_loopback(family, sotype | SOCK_NONBLOCK);
	अगर (p1 < 0)
		जाओ बंद_cli0;
	err = xमाला_लोockname(p1, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_cli0;

	c1 = xsocket(family, sotype | SOCK_NONBLOCK, 0);
	अगर (c1 < 0)
		जाओ बंद_peer1;
	err = xconnect(c1, sockaddr(&addr), len);
	अगर (err)
		जाओ बंद_cli1;
	err = xमाला_लोockname(c1, sockaddr(&addr), &len);
	अगर (err)
		जाओ बंद_cli1;
	err = xconnect(p1, sockaddr(&addr), len);
	अगर (err)
		जाओ बंद_cli1;

	key = 0;
	value = p0;
	err = xbpf_map_update_elem(sock_mapfd, &key, &value, BPF_NOEXIST);
	अगर (err)
		जाओ बंद_cli1;

	key = 1;
	value = p1;
	err = xbpf_map_update_elem(sock_mapfd, &key, &value, BPF_NOEXIST);
	अगर (err)
		जाओ बंद_cli1;

	n = ग_लिखो(c1, "a", 1);
	अगर (n < 0)
		FAIL_ERRNO("%s: write", log_prefix);
	अगर (n == 0)
		FAIL("%s: incomplete write", log_prefix);
	अगर (n < 1)
		जाओ बंद_cli1;

	key = SK_PASS;
	err = xbpf_map_lookup_elem(verd_mapfd, &key, &pass);
	अगर (err)
		जाओ बंद_cli1;
	अगर (pass != 1)
		FAIL("%s: want pass count 1, have %d", log_prefix, pass);

	n = पढ़ो(mode == REसूची_INGRESS ? p0 : c0, &b, 1);
	अगर (n < 0)
		FAIL_ERRNO("%s: read", log_prefix);
	अगर (n == 0)
		FAIL("%s: incomplete read", log_prefix);

बंद_cli1:
	xबंद(c1);
बंद_peer1:
	xबंद(p1);
बंद_cli0:
	xबंद(c0);
बंद_peer0:
	xबंद(p0);
पूर्ण

अटल व्योम udp_skb_redir_to_connected(काष्ठा test_sockmap_listen *skel,
				       काष्ठा bpf_map *inner_map, पूर्णांक family)
अणु
	पूर्णांक verdict = bpf_program__fd(skel->progs.prog_skb_verdict);
	पूर्णांक verdict_map = bpf_map__fd(skel->maps.verdict_map);
	पूर्णांक sock_map = bpf_map__fd(inner_map);
	पूर्णांक err;

	err = xbpf_prog_attach(verdict, sock_map, BPF_SK_SKB_VERDICT, 0);
	अगर (err)
		वापस;

	skel->bss->test_ingress = false;
	udp_redir_to_connected(family, SOCK_DGRAM, sock_map, verdict_map,
			       REसूची_EGRESS);
	skel->bss->test_ingress = true;
	udp_redir_to_connected(family, SOCK_DGRAM, sock_map, verdict_map,
			       REसूची_INGRESS);

	xbpf_prog_detach2(verdict, sock_map, BPF_SK_SKB_VERDICT);
पूर्ण

अटल व्योम test_udp_redir(काष्ठा test_sockmap_listen *skel, काष्ठा bpf_map *map,
			   पूर्णांक family)
अणु
	स्थिर अक्षर *family_name, *map_name;
	अक्षर s[MAX_TEST_NAME];

	family_name = family_str(family);
	map_name = map_type_str(map);
	snम_लिखो(s, माप(s), "%s %s %s", map_name, family_name, __func__);
	अगर (!test__start_subtest(s))
		वापस;
	udp_skb_redir_to_connected(skel, map, family);
पूर्ण

अटल व्योम run_tests(काष्ठा test_sockmap_listen *skel, काष्ठा bpf_map *map,
		      पूर्णांक family)
अणु
	test_ops(skel, map, family, SOCK_STREAM);
	test_ops(skel, map, family, SOCK_DGRAM);
	test_redir(skel, map, family, SOCK_STREAM);
	test_reuseport(skel, map, family, SOCK_STREAM);
	test_reuseport(skel, map, family, SOCK_DGRAM);
	test_udp_redir(skel, map, family);
पूर्ण

व्योम test_sockmap_listen(व्योम)
अणु
	काष्ठा test_sockmap_listen *skel;

	skel = test_sockmap_listen__खोलो_and_load();
	अगर (!skel) अणु
		FAIL("skeleton open/load failed");
		वापस;
	पूर्ण

	skel->bss->test_sockmap = true;
	run_tests(skel, skel->maps.sock_map, AF_INET);
	run_tests(skel, skel->maps.sock_map, AF_INET6);

	skel->bss->test_sockmap = false;
	run_tests(skel, skel->maps.sock_hash, AF_INET);
	run_tests(skel, skel->maps.sock_hash, AF_INET6);

	test_sockmap_listen__destroy(skel);
पूर्ण
