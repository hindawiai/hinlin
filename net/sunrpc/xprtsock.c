<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/net/sunrpc/xprtsock.c
 *
 * Client-side transport implementation क्रम sockets.
 *
 * TCP callback races fixes (C) 1998 Red Hat
 * TCP send fixes (C) 1998 Red Hat
 * TCP NFS related पढ़ो + ग_लिखो fixes
 *  (C) 1999 Dave Airlie, University of Limerick, Ireland <airlied@linux.ie>
 *
 * Reग_लिखो of larges part of the code in order to stabilize TCP stuff.
 * Fix behaviour when socket buffer is full.
 *  (C) 1999 Trond Myklebust <trond.myklebust@fys.uio.no>
 *
 * IP socket transport implementation, (C) 2005 Chuck Lever <cel@netapp.com>
 *
 * IPv6 support contributed by Gilles Quillard, Bull Open Source, 2005.
 *   <gilles.quillard@bull.net>
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/capability.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/net.h>
#समावेश <linux/mm.h>
#समावेश <linux/un.h>
#समावेश <linux/udp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/sunrpc/xprtsock.h>
#समावेश <linux/file.h>
#अगर_घोषित CONFIG_SUNRPC_BACKCHANNEL
#समावेश <linux/sunrpc/bc_xprt.h>
#पूर्ण_अगर

#समावेश <net/sock.h>
#समावेश <net/checksum.h>
#समावेश <net/udp.h>
#समावेश <net/tcp.h>
#समावेश <linux/bvec.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/uपन.स>
#समावेश <linux/sched/mm.h>

#समावेश <trace/events/sunrpc.h>

#समावेश "socklib.h"
#समावेश "sunrpc.h"

अटल व्योम xs_बंद(काष्ठा rpc_xprt *xprt);
अटल व्योम xs_tcp_set_socket_समयouts(काष्ठा rpc_xprt *xprt,
		काष्ठा socket *sock);

/*
 * xprtsock tunables
 */
अटल अचिन्हित पूर्णांक xprt_udp_slot_table_entries = RPC_DEF_SLOT_TABLE;
अटल अचिन्हित पूर्णांक xprt_tcp_slot_table_entries = RPC_MIN_SLOT_TABLE;
अटल अचिन्हित पूर्णांक xprt_max_tcp_slot_table_entries = RPC_MAX_SLOT_TABLE;

अटल अचिन्हित पूर्णांक xprt_min_resvport = RPC_DEF_MIN_RESVPORT;
अटल अचिन्हित पूर्णांक xprt_max_resvport = RPC_DEF_MAX_RESVPORT;

#घोषणा XS_TCP_LINGER_TO	(15U * HZ)
अटल अचिन्हित पूर्णांक xs_tcp_fin_समयout __पढ़ो_mostly = XS_TCP_LINGER_TO;

/*
 * We can रेजिस्टर our own files under /proc/sys/sunrpc by
 * calling रेजिस्टर_sysctl_table() again.  The files in that
 * directory become the जोड़ of all files रेजिस्टरed there.
 *
 * We simply need to make sure that we करोn't collide with
 * someone अन्यथा's file names!
 */

अटल अचिन्हित पूर्णांक min_slot_table_size = RPC_MIN_SLOT_TABLE;
अटल अचिन्हित पूर्णांक max_slot_table_size = RPC_MAX_SLOT_TABLE;
अटल अचिन्हित पूर्णांक max_tcp_slot_table_limit = RPC_MAX_SLOT_TABLE_LIMIT;
अटल अचिन्हित पूर्णांक xprt_min_resvport_limit = RPC_MIN_RESVPORT;
अटल अचिन्हित पूर्णांक xprt_max_resvport_limit = RPC_MAX_RESVPORT;

अटल काष्ठा ctl_table_header *sunrpc_table_header;

/*
 * FIXME: changing the UDP slot table size should also resize the UDP
 *        socket buffers क्रम existing UDP transports
 */
अटल काष्ठा ctl_table xs_tunables_table[] = अणु
	अणु
		.procname	= "udp_slot_table_entries",
		.data		= &xprt_udp_slot_table_entries,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_slot_table_size,
		.extra2		= &max_slot_table_size
	पूर्ण,
	अणु
		.procname	= "tcp_slot_table_entries",
		.data		= &xprt_tcp_slot_table_entries,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_slot_table_size,
		.extra2		= &max_slot_table_size
	पूर्ण,
	अणु
		.procname	= "tcp_max_slot_table_entries",
		.data		= &xprt_max_tcp_slot_table_entries,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_slot_table_size,
		.extra2		= &max_tcp_slot_table_limit
	पूर्ण,
	अणु
		.procname	= "min_resvport",
		.data		= &xprt_min_resvport,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &xprt_min_resvport_limit,
		.extra2		= &xprt_max_resvport_limit
	पूर्ण,
	अणु
		.procname	= "max_resvport",
		.data		= &xprt_max_resvport,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &xprt_min_resvport_limit,
		.extra2		= &xprt_max_resvport_limit
	पूर्ण,
	अणु
		.procname	= "tcp_fin_timeout",
		.data		= &xs_tcp_fin_समयout,
		.maxlen		= माप(xs_tcp_fin_समयout),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा ctl_table sunrpc_table[] = अणु
	अणु
		.procname	= "sunrpc",
		.mode		= 0555,
		.child		= xs_tunables_table
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

/*
 * Wait duration क्रम a reply from the RPC porपंचांगapper.
 */
#घोषणा XS_BIND_TO		(60U * HZ)

/*
 * Delay अगर a UDP socket connect error occurs.  This is most likely some
 * kind of resource problem on the local host.
 */
#घोषणा XS_UDP_REEST_TO		(2U * HZ)

/*
 * The reestablish समयout allows clients to delay क्रम a bit beक्रमe attempting
 * to reconnect to a server that just dropped our connection.
 *
 * We implement an exponential backoff when trying to reestablish a TCP
 * transport connection with the server.  Some servers like to drop a TCP
 * connection when they are overworked, so we start with a लघु समयout and
 * increase over समय अगर the server is करोwn or not responding.
 */
#घोषणा XS_TCP_INIT_REEST_TO	(3U * HZ)

/*
 * TCP idle समयout; client drops the transport socket अगर it is idle
 * क्रम this दीर्घ.  Note that we also समयout UDP sockets to prevent
 * holding port numbers when there is no RPC traffic.
 */
#घोषणा XS_IDLE_DISC_TO		(5U * 60 * HZ)

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# undef  RPC_DEBUG_DATA
# define RPCDBG_FACILITY	RPCDBG_TRANS
#पूर्ण_अगर

#अगर_घोषित RPC_DEBUG_DATA
अटल व्योम xs_pktdump(अक्षर *msg, u32 *packet, अचिन्हित पूर्णांक count)
अणु
	u8 *buf = (u8 *) packet;
	पूर्णांक j;

	dprपूर्णांकk("RPC:       %s\n", msg);
	क्रम (j = 0; j < count && j < 128; j += 4) अणु
		अगर (!(j & 31)) अणु
			अगर (j)
				dprपूर्णांकk("\n");
			dprपूर्णांकk("0x%04x ", j);
		पूर्ण
		dprपूर्णांकk("%02x%02x%02x%02x ",
			buf[j], buf[j+1], buf[j+2], buf[j+3]);
	पूर्ण
	dprपूर्णांकk("\n");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम xs_pktdump(अक्षर *msg, u32 *packet, अचिन्हित पूर्णांक count)
अणु
	/* NOP */
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा rpc_xprt *xprt_from_sock(काष्ठा sock *sk)
अणु
	वापस (काष्ठा rpc_xprt *) sk->sk_user_data;
पूर्ण

अटल अंतरभूत काष्ठा sockaddr *xs_addr(काष्ठा rpc_xprt *xprt)
अणु
	वापस (काष्ठा sockaddr *) &xprt->addr;
पूर्ण

अटल अंतरभूत काष्ठा sockaddr_un *xs_addr_un(काष्ठा rpc_xprt *xprt)
अणु
	वापस (काष्ठा sockaddr_un *) &xprt->addr;
पूर्ण

अटल अंतरभूत काष्ठा sockaddr_in *xs_addr_in(काष्ठा rpc_xprt *xprt)
अणु
	वापस (काष्ठा sockaddr_in *) &xprt->addr;
पूर्ण

अटल अंतरभूत काष्ठा sockaddr_in6 *xs_addr_in6(काष्ठा rpc_xprt *xprt)
अणु
	वापस (काष्ठा sockaddr_in6 *) &xprt->addr;
पूर्ण

अटल व्योम xs_क्रमmat_common_peer_addresses(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा sockaddr *sap = xs_addr(xprt);
	काष्ठा sockaddr_in6 *sin6;
	काष्ठा sockaddr_in *sin;
	काष्ठा sockaddr_un *sun;
	अक्षर buf[128];

	चयन (sap->sa_family) अणु
	हाल AF_LOCAL:
		sun = xs_addr_un(xprt);
		strlcpy(buf, sun->sun_path, माप(buf));
		xprt->address_strings[RPC_DISPLAY_ADDR] =
						kstrdup(buf, GFP_KERNEL);
		अवरोध;
	हाल AF_INET:
		(व्योम)rpc_ntop(sap, buf, माप(buf));
		xprt->address_strings[RPC_DISPLAY_ADDR] =
						kstrdup(buf, GFP_KERNEL);
		sin = xs_addr_in(xprt);
		snम_लिखो(buf, माप(buf), "%08x", ntohl(sin->sin_addr.s_addr));
		अवरोध;
	हाल AF_INET6:
		(व्योम)rpc_ntop(sap, buf, माप(buf));
		xprt->address_strings[RPC_DISPLAY_ADDR] =
						kstrdup(buf, GFP_KERNEL);
		sin6 = xs_addr_in6(xprt);
		snम_लिखो(buf, माप(buf), "%pi6", &sin6->sin6_addr);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	xprt->address_strings[RPC_DISPLAY_HEX_ADDR] = kstrdup(buf, GFP_KERNEL);
पूर्ण

अटल व्योम xs_क्रमmat_common_peer_ports(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा sockaddr *sap = xs_addr(xprt);
	अक्षर buf[128];

	snम_लिखो(buf, माप(buf), "%u", rpc_get_port(sap));
	xprt->address_strings[RPC_DISPLAY_PORT] = kstrdup(buf, GFP_KERNEL);

	snम_लिखो(buf, माप(buf), "%4hx", rpc_get_port(sap));
	xprt->address_strings[RPC_DISPLAY_HEX_PORT] = kstrdup(buf, GFP_KERNEL);
पूर्ण

अटल व्योम xs_क्रमmat_peer_addresses(काष्ठा rpc_xprt *xprt,
				     स्थिर अक्षर *protocol,
				     स्थिर अक्षर *netid)
अणु
	xprt->address_strings[RPC_DISPLAY_PROTO] = protocol;
	xprt->address_strings[RPC_DISPLAY_NETID] = netid;
	xs_क्रमmat_common_peer_addresses(xprt);
	xs_क्रमmat_common_peer_ports(xprt);
पूर्ण

अटल व्योम xs_update_peer_port(काष्ठा rpc_xprt *xprt)
अणु
	kमुक्त(xprt->address_strings[RPC_DISPLAY_HEX_PORT]);
	kमुक्त(xprt->address_strings[RPC_DISPLAY_PORT]);

	xs_क्रमmat_common_peer_ports(xprt);
पूर्ण

अटल व्योम xs_मुक्त_peer_addresses(काष्ठा rpc_xprt *xprt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < RPC_DISPLAY_MAX; i++)
		चयन (i) अणु
		हाल RPC_DISPLAY_PROTO:
		हाल RPC_DISPLAY_NETID:
			जारी;
		शेष:
			kमुक्त(xprt->address_strings[i]);
		पूर्ण
पूर्ण

अटल माप_प्रकार
xs_alloc_sparse_pages(काष्ठा xdr_buf *buf, माप_प्रकार want, gfp_t gfp)
अणु
	माप_प्रकार i,n;

	अगर (!want || !(buf->flags & XDRBUF_SPARSE_PAGES))
		वापस want;
	n = (buf->page_base + want + PAGE_SIZE - 1) >> PAGE_SHIFT;
	क्रम (i = 0; i < n; i++) अणु
		अगर (buf->pages[i])
			जारी;
		buf->bvec[i].bv_page = buf->pages[i] = alloc_page(gfp);
		अगर (!buf->pages[i]) अणु
			i *= PAGE_SIZE;
			वापस i > buf->page_base ? i - buf->page_base : 0;
		पूर्ण
	पूर्ण
	वापस want;
पूर्ण

अटल sमाप_प्रकार
xs_sock_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, पूर्णांक flags, माप_प्रकार seek)
अणु
	sमाप_प्रकार ret;
	अगर (seek != 0)
		iov_iter_advance(&msg->msg_iter, seek);
	ret = sock_recvmsg(sock, msg, flags);
	वापस ret > 0 ? ret + seek : ret;
पूर्ण

अटल sमाप_प्रकार
xs_पढ़ो_kvec(काष्ठा socket *sock, काष्ठा msghdr *msg, पूर्णांक flags,
		काष्ठा kvec *kvec, माप_प्रकार count, माप_प्रकार seek)
अणु
	iov_iter_kvec(&msg->msg_iter, READ, kvec, 1, count);
	वापस xs_sock_recvmsg(sock, msg, flags, seek);
पूर्ण

अटल sमाप_प्रकार
xs_पढ़ो_bvec(काष्ठा socket *sock, काष्ठा msghdr *msg, पूर्णांक flags,
		काष्ठा bio_vec *bvec, अचिन्हित दीर्घ nr, माप_प्रकार count,
		माप_प्रकार seek)
अणु
	iov_iter_bvec(&msg->msg_iter, READ, bvec, nr, count);
	वापस xs_sock_recvmsg(sock, msg, flags, seek);
पूर्ण

अटल sमाप_प्रकार
xs_पढ़ो_discard(काष्ठा socket *sock, काष्ठा msghdr *msg, पूर्णांक flags,
		माप_प्रकार count)
अणु
	iov_iter_discard(&msg->msg_iter, READ, count);
	वापस sock_recvmsg(sock, msg, flags);
पूर्ण

#अगर ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE
अटल व्योम
xs_flush_bvec(स्थिर काष्ठा bio_vec *bvec, माप_प्रकार count, माप_प्रकार seek)
अणु
	काष्ठा bvec_iter bi = अणु
		.bi_size = count,
	पूर्ण;
	काष्ठा bio_vec bv;

	bvec_iter_advance(bvec, &bi, seek & PAGE_MASK);
	क्रम_each_bvec(bv, bvec, bi, bi)
		flush_dcache_page(bv.bv_page);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
xs_flush_bvec(स्थिर काष्ठा bio_vec *bvec, माप_प्रकार count, माप_प्रकार seek)
अणु
पूर्ण
#पूर्ण_अगर

अटल sमाप_प्रकार
xs_पढ़ो_xdr_buf(काष्ठा socket *sock, काष्ठा msghdr *msg, पूर्णांक flags,
		काष्ठा xdr_buf *buf, माप_प्रकार count, माप_प्रकार seek, माप_प्रकार *पढ़ो)
अणु
	माप_प्रकार want, seek_init = seek, offset = 0;
	sमाप_प्रकार ret;

	want = min_t(माप_प्रकार, count, buf->head[0].iov_len);
	अगर (seek < want) अणु
		ret = xs_पढ़ो_kvec(sock, msg, flags, &buf->head[0], want, seek);
		अगर (ret <= 0)
			जाओ sock_err;
		offset += ret;
		अगर (offset == count || msg->msg_flags & (MSG_EOR|MSG_TRUNC))
			जाओ out;
		अगर (ret != want)
			जाओ out;
		seek = 0;
	पूर्ण अन्यथा अणु
		seek -= want;
		offset += want;
	पूर्ण

	want = xs_alloc_sparse_pages(buf,
			min_t(माप_प्रकार, count - offset, buf->page_len),
			GFP_KERNEL);
	अगर (seek < want) अणु
		ret = xs_पढ़ो_bvec(sock, msg, flags, buf->bvec,
				xdr_buf_pagecount(buf),
				want + buf->page_base,
				seek + buf->page_base);
		अगर (ret <= 0)
			जाओ sock_err;
		xs_flush_bvec(buf->bvec, ret, seek + buf->page_base);
		ret -= buf->page_base;
		offset += ret;
		अगर (offset == count || msg->msg_flags & (MSG_EOR|MSG_TRUNC))
			जाओ out;
		अगर (ret != want)
			जाओ out;
		seek = 0;
	पूर्ण अन्यथा अणु
		seek -= want;
		offset += want;
	पूर्ण

	want = min_t(माप_प्रकार, count - offset, buf->tail[0].iov_len);
	अगर (seek < want) अणु
		ret = xs_पढ़ो_kvec(sock, msg, flags, &buf->tail[0], want, seek);
		अगर (ret <= 0)
			जाओ sock_err;
		offset += ret;
		अगर (offset == count || msg->msg_flags & (MSG_EOR|MSG_TRUNC))
			जाओ out;
		अगर (ret != want)
			जाओ out;
	पूर्ण अन्यथा अगर (offset < seek_init)
		offset = seek_init;
	ret = -EMSGSIZE;
out:
	*पढ़ो = offset - seek_init;
	वापस ret;
sock_err:
	offset += seek;
	जाओ out;
पूर्ण

अटल व्योम
xs_पढ़ो_header(काष्ठा sock_xprt *transport, काष्ठा xdr_buf *buf)
अणु
	अगर (!transport->recv.copied) अणु
		अगर (buf->head[0].iov_len >= transport->recv.offset)
			स_नकल(buf->head[0].iov_base,
					&transport->recv.xid,
					transport->recv.offset);
		transport->recv.copied = transport->recv.offset;
	पूर्ण
पूर्ण

अटल bool
xs_पढ़ो_stream_request_करोne(काष्ठा sock_xprt *transport)
अणु
	वापस transport->recv.fraghdr & cpu_to_be32(RPC_LAST_STREAM_FRAGMENT);
पूर्ण

अटल व्योम
xs_पढ़ो_stream_check_eor(काष्ठा sock_xprt *transport,
		काष्ठा msghdr *msg)
अणु
	अगर (xs_पढ़ो_stream_request_करोne(transport))
		msg->msg_flags |= MSG_EOR;
पूर्ण

अटल sमाप_प्रकार
xs_पढ़ो_stream_request(काष्ठा sock_xprt *transport, काष्ठा msghdr *msg,
		पूर्णांक flags, काष्ठा rpc_rqst *req)
अणु
	काष्ठा xdr_buf *buf = &req->rq_निजी_buf;
	माप_प्रकार want, पढ़ो;
	sमाप_प्रकार ret;

	xs_पढ़ो_header(transport, buf);

	want = transport->recv.len - transport->recv.offset;
	अगर (want != 0) अणु
		ret = xs_पढ़ो_xdr_buf(transport->sock, msg, flags, buf,
				transport->recv.copied + want,
				transport->recv.copied,
				&पढ़ो);
		transport->recv.offset += पढ़ो;
		transport->recv.copied += पढ़ो;
	पूर्ण

	अगर (transport->recv.offset == transport->recv.len)
		xs_पढ़ो_stream_check_eor(transport, msg);

	अगर (want == 0)
		वापस 0;

	चयन (ret) अणु
	शेष:
		अवरोध;
	हाल -EFAULT:
	हाल -EMSGSIZE:
		msg->msg_flags |= MSG_TRUNC;
		वापस पढ़ो;
	हाल 0:
		वापस -ESHUTDOWN;
	पूर्ण
	वापस ret < 0 ? ret : पढ़ो;
पूर्ण

अटल माप_प्रकार
xs_पढ़ो_stream_headersize(bool isfrag)
अणु
	अगर (isfrag)
		वापस माप(__be32);
	वापस 3 * माप(__be32);
पूर्ण

अटल sमाप_प्रकार
xs_पढ़ो_stream_header(काष्ठा sock_xprt *transport, काष्ठा msghdr *msg,
		पूर्णांक flags, माप_प्रकार want, माप_प्रकार seek)
अणु
	काष्ठा kvec kvec = अणु
		.iov_base = &transport->recv.fraghdr,
		.iov_len = want,
	पूर्ण;
	वापस xs_पढ़ो_kvec(transport->sock, msg, flags, &kvec, want, seek);
पूर्ण

#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
अटल sमाप_प्रकार
xs_पढ़ो_stream_call(काष्ठा sock_xprt *transport, काष्ठा msghdr *msg, पूर्णांक flags)
अणु
	काष्ठा rpc_xprt *xprt = &transport->xprt;
	काष्ठा rpc_rqst *req;
	sमाप_प्रकार ret;

	/* Is this transport associated with the backchannel? */
	अगर (!xprt->bc_serv)
		वापस -ESHUTDOWN;

	/* Look up and lock the request corresponding to the given XID */
	req = xprt_lookup_bc_request(xprt, transport->recv.xid);
	अगर (!req) अणु
		prपूर्णांकk(KERN_WARNING "Callback slot table overflowed\n");
		वापस -ESHUTDOWN;
	पूर्ण
	अगर (transport->recv.copied && !req->rq_निजी_buf.len)
		वापस -ESHUTDOWN;

	ret = xs_पढ़ो_stream_request(transport, msg, flags, req);
	अगर (msg->msg_flags & (MSG_EOR|MSG_TRUNC))
		xprt_complete_bc_request(req, transport->recv.copied);
	अन्यथा
		req->rq_निजी_buf.len = transport->recv.copied;

	वापस ret;
पूर्ण
#अन्यथा /* CONFIG_SUNRPC_BACKCHANNEL */
अटल sमाप_प्रकार
xs_पढ़ो_stream_call(काष्ठा sock_xprt *transport, काष्ठा msghdr *msg, पूर्णांक flags)
अणु
	वापस -ESHUTDOWN;
पूर्ण
#पूर्ण_अगर /* CONFIG_SUNRPC_BACKCHANNEL */

अटल sमाप_प्रकार
xs_पढ़ो_stream_reply(काष्ठा sock_xprt *transport, काष्ठा msghdr *msg, पूर्णांक flags)
अणु
	काष्ठा rpc_xprt *xprt = &transport->xprt;
	काष्ठा rpc_rqst *req;
	sमाप_प्रकार ret = 0;

	/* Look up and lock the request corresponding to the given XID */
	spin_lock(&xprt->queue_lock);
	req = xprt_lookup_rqst(xprt, transport->recv.xid);
	अगर (!req || (transport->recv.copied && !req->rq_निजी_buf.len)) अणु
		msg->msg_flags |= MSG_TRUNC;
		जाओ out;
	पूर्ण
	xprt_pin_rqst(req);
	spin_unlock(&xprt->queue_lock);

	ret = xs_पढ़ो_stream_request(transport, msg, flags, req);

	spin_lock(&xprt->queue_lock);
	अगर (msg->msg_flags & (MSG_EOR|MSG_TRUNC))
		xprt_complete_rqst(req->rq_task, transport->recv.copied);
	अन्यथा
		req->rq_निजी_buf.len = transport->recv.copied;
	xprt_unpin_rqst(req);
out:
	spin_unlock(&xprt->queue_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार
xs_पढ़ो_stream(काष्ठा sock_xprt *transport, पूर्णांक flags)
अणु
	काष्ठा msghdr msg = अणु 0 पूर्ण;
	माप_प्रकार want, पढ़ो = 0;
	sमाप_प्रकार ret = 0;

	अगर (transport->recv.len == 0) अणु
		want = xs_पढ़ो_stream_headersize(transport->recv.copied != 0);
		ret = xs_पढ़ो_stream_header(transport, &msg, flags, want,
				transport->recv.offset);
		अगर (ret <= 0)
			जाओ out_err;
		transport->recv.offset = ret;
		अगर (transport->recv.offset != want)
			वापस transport->recv.offset;
		transport->recv.len = be32_to_cpu(transport->recv.fraghdr) &
			RPC_FRAGMENT_SIZE_MASK;
		transport->recv.offset -= माप(transport->recv.fraghdr);
		पढ़ो = ret;
	पूर्ण

	चयन (be32_to_cpu(transport->recv.calldir)) अणु
	शेष:
		msg.msg_flags |= MSG_TRUNC;
		अवरोध;
	हाल RPC_CALL:
		ret = xs_पढ़ो_stream_call(transport, &msg, flags);
		अवरोध;
	हाल RPC_REPLY:
		ret = xs_पढ़ो_stream_reply(transport, &msg, flags);
	पूर्ण
	अगर (msg.msg_flags & MSG_TRUNC) अणु
		transport->recv.calldir = cpu_to_be32(-1);
		transport->recv.copied = -1;
	पूर्ण
	अगर (ret < 0)
		जाओ out_err;
	पढ़ो += ret;
	अगर (transport->recv.offset < transport->recv.len) अणु
		अगर (!(msg.msg_flags & MSG_TRUNC))
			वापस पढ़ो;
		msg.msg_flags = 0;
		ret = xs_पढ़ो_discard(transport->sock, &msg, flags,
				transport->recv.len - transport->recv.offset);
		अगर (ret <= 0)
			जाओ out_err;
		transport->recv.offset += ret;
		पढ़ो += ret;
		अगर (transport->recv.offset != transport->recv.len)
			वापस पढ़ो;
	पूर्ण
	अगर (xs_पढ़ो_stream_request_करोne(transport)) अणु
		trace_xs_stream_पढ़ो_request(transport);
		transport->recv.copied = 0;
	पूर्ण
	transport->recv.offset = 0;
	transport->recv.len = 0;
	वापस पढ़ो;
out_err:
	वापस ret != 0 ? ret : -ESHUTDOWN;
पूर्ण

अटल __poll_t xs_poll_socket(काष्ठा sock_xprt *transport)
अणु
	वापस transport->sock->ops->poll(transport->file, transport->sock,
			शून्य);
पूर्ण

अटल bool xs_poll_socket_पढ़ोable(काष्ठा sock_xprt *transport)
अणु
	__poll_t events = xs_poll_socket(transport);

	वापस (events & (EPOLLIN | EPOLLRDNORM)) && !(events & EPOLLRDHUP);
पूर्ण

अटल व्योम xs_poll_check_पढ़ोable(काष्ठा sock_xprt *transport)
अणु

	clear_bit(XPRT_SOCK_DATA_READY, &transport->sock_state);
	अगर (!xs_poll_socket_पढ़ोable(transport))
		वापस;
	अगर (!test_and_set_bit(XPRT_SOCK_DATA_READY, &transport->sock_state))
		queue_work(xprtiod_workqueue, &transport->recv_worker);
पूर्ण

अटल व्योम xs_stream_data_receive(काष्ठा sock_xprt *transport)
अणु
	माप_प्रकार पढ़ो = 0;
	sमाप_प्रकार ret = 0;

	mutex_lock(&transport->recv_mutex);
	अगर (transport->sock == शून्य)
		जाओ out;
	क्रम (;;) अणु
		ret = xs_पढ़ो_stream(transport, MSG_DONTWAIT);
		अगर (ret < 0)
			अवरोध;
		पढ़ो += ret;
		cond_resched();
	पूर्ण
	अगर (ret == -ESHUTDOWN)
		kernel_sock_shutकरोwn(transport->sock, SHUT_RDWR);
	अन्यथा
		xs_poll_check_पढ़ोable(transport);
out:
	mutex_unlock(&transport->recv_mutex);
	trace_xs_stream_पढ़ो_data(&transport->xprt, ret, पढ़ो);
पूर्ण

अटल व्योम xs_stream_data_receive_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sock_xprt *transport =
		container_of(work, काष्ठा sock_xprt, recv_worker);
	अचिन्हित पूर्णांक pflags = meदो_स्मृति_nofs_save();

	xs_stream_data_receive(transport);
	meदो_स्मृति_nofs_restore(pflags);
पूर्ण

अटल व्योम
xs_stream_reset_connect(काष्ठा sock_xprt *transport)
अणु
	transport->recv.offset = 0;
	transport->recv.len = 0;
	transport->recv.copied = 0;
	transport->xmit.offset = 0;
पूर्ण

अटल व्योम
xs_stream_start_connect(काष्ठा sock_xprt *transport)
अणु
	transport->xprt.stat.connect_count++;
	transport->xprt.stat.connect_start = jअगरfies;
पूर्ण

#घोषणा XS_SENDMSG_FLAGS	(MSG_DONTWAIT | MSG_NOSIGNAL)

/**
 * xs_nospace - handle transmit was incomplete
 * @req: poपूर्णांकer to RPC request
 *
 */
अटल पूर्णांक xs_nospace(काष्ठा rpc_rqst *req)
अणु
	काष्ठा rpc_xprt *xprt = req->rq_xprt;
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	काष्ठा sock *sk = transport->inet;
	पूर्णांक ret = -EAGAIN;

	trace_rpc_socket_nospace(req, transport);

	/* Protect against races with ग_लिखो_space */
	spin_lock(&xprt->transport_lock);

	/* Don't race with disconnect */
	अगर (xprt_connected(xprt)) अणु
		/* रुको क्रम more buffer space */
		sk->sk_ग_लिखो_pending++;
		xprt_रुको_क्रम_buffer_space(xprt);
	पूर्ण अन्यथा
		ret = -ENOTCONN;

	spin_unlock(&xprt->transport_lock);

	/* Race अवरोधer in हाल memory is मुक्तd beक्रमe above code is called */
	अगर (ret == -EAGAIN) अणु
		काष्ठा socket_wq *wq;

		rcu_पढ़ो_lock();
		wq = rcu_dereference(sk->sk_wq);
		set_bit(SOCKWQ_ASYNC_NOSPACE, &wq->flags);
		rcu_पढ़ो_unlock();

		sk->sk_ग_लिखो_space(sk);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
xs_stream_prepare_request(काष्ठा rpc_rqst *req)
अणु
	xdr_मुक्त_bvec(&req->rq_rcv_buf);
	req->rq_task->tk_status = xdr_alloc_bvec(&req->rq_rcv_buf, GFP_KERNEL);
पूर्ण

/*
 * Determine अगर the previous message in the stream was पातed beक्रमe it
 * could complete transmission.
 */
अटल bool
xs_send_request_was_पातed(काष्ठा sock_xprt *transport, काष्ठा rpc_rqst *req)
अणु
	वापस transport->xmit.offset != 0 && req->rq_bytes_sent == 0;
पूर्ण

/*
 * Return the stream record marker field क्रम a record of length < 2^31-1
 */
अटल rpc_fraghdr
xs_stream_record_marker(काष्ठा xdr_buf *xdr)
अणु
	अगर (!xdr->len)
		वापस 0;
	वापस cpu_to_be32(RPC_LAST_STREAM_FRAGMENT | (u32)xdr->len);
पूर्ण

/**
 * xs_local_send_request - ग_लिखो an RPC request to an AF_LOCAL socket
 * @req: poपूर्णांकer to RPC request
 *
 * Return values:
 *        0:	The request has been sent
 *   EAGAIN:	The socket was blocked, please call again later to
 *		complete the request
 * ENOTCONN:	Caller needs to invoke connect logic then call again
 *    other:	Some other error occurred, the request was not sent
 */
अटल पूर्णांक xs_local_send_request(काष्ठा rpc_rqst *req)
अणु
	काष्ठा rpc_xprt *xprt = req->rq_xprt;
	काष्ठा sock_xprt *transport =
				container_of(xprt, काष्ठा sock_xprt, xprt);
	काष्ठा xdr_buf *xdr = &req->rq_snd_buf;
	rpc_fraghdr rm = xs_stream_record_marker(xdr);
	अचिन्हित पूर्णांक msglen = rm ? req->rq_slen + माप(rm) : req->rq_slen;
	काष्ठा msghdr msg = अणु
		.msg_flags	= XS_SENDMSG_FLAGS,
	पूर्ण;
	अचिन्हित पूर्णांक sent;
	पूर्णांक status;

	/* Close the stream अगर the previous transmission was incomplete */
	अगर (xs_send_request_was_पातed(transport, req)) अणु
		xs_बंद(xprt);
		वापस -ENOTCONN;
	पूर्ण

	xs_pktdump("packet data:",
			req->rq_svec->iov_base, req->rq_svec->iov_len);

	req->rq_xसमय = kसमय_get();
	status = xprt_sock_sendmsg(transport->sock, &msg, xdr,
				   transport->xmit.offset, rm, &sent);
	dprपूर्णांकk("RPC:       %s(%u) = %d\n",
			__func__, xdr->len - transport->xmit.offset, status);

	अगर (status == -EAGAIN && sock_ग_लिखोable(transport->inet))
		status = -ENOBUFS;

	अगर (likely(sent > 0) || status == 0) अणु
		transport->xmit.offset += sent;
		req->rq_bytes_sent = transport->xmit.offset;
		अगर (likely(req->rq_bytes_sent >= msglen)) अणु
			req->rq_xmit_bytes_sent += transport->xmit.offset;
			transport->xmit.offset = 0;
			वापस 0;
		पूर्ण
		status = -EAGAIN;
	पूर्ण

	चयन (status) अणु
	हाल -ENOBUFS:
		अवरोध;
	हाल -EAGAIN:
		status = xs_nospace(req);
		अवरोध;
	शेष:
		dprपूर्णांकk("RPC:       sendmsg returned unrecognized error %d\n",
			-status);
		fallthrough;
	हाल -EPIPE:
		xs_बंद(xprt);
		status = -ENOTCONN;
	पूर्ण

	वापस status;
पूर्ण

/**
 * xs_udp_send_request - ग_लिखो an RPC request to a UDP socket
 * @req: poपूर्णांकer to RPC request
 *
 * Return values:
 *        0:	The request has been sent
 *   EAGAIN:	The socket was blocked, please call again later to
 *		complete the request
 * ENOTCONN:	Caller needs to invoke connect logic then call again
 *    other:	Some other error occurred, the request was not sent
 */
अटल पूर्णांक xs_udp_send_request(काष्ठा rpc_rqst *req)
अणु
	काष्ठा rpc_xprt *xprt = req->rq_xprt;
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	काष्ठा xdr_buf *xdr = &req->rq_snd_buf;
	काष्ठा msghdr msg = अणु
		.msg_name	= xs_addr(xprt),
		.msg_namelen	= xprt->addrlen,
		.msg_flags	= XS_SENDMSG_FLAGS,
	पूर्ण;
	अचिन्हित पूर्णांक sent;
	पूर्णांक status;

	xs_pktdump("packet data:",
				req->rq_svec->iov_base,
				req->rq_svec->iov_len);

	अगर (!xprt_bound(xprt))
		वापस -ENOTCONN;

	अगर (!xprt_request_get_cong(xprt, req))
		वापस -EBADSLT;

	req->rq_xसमय = kसमय_get();
	status = xprt_sock_sendmsg(transport->sock, &msg, xdr, 0, 0, &sent);

	dprपूर्णांकk("RPC:       xs_udp_send_request(%u) = %d\n",
			xdr->len, status);

	/* firewall is blocking us, करोn't वापस -EAGAIN or we end up looping */
	अगर (status == -EPERM)
		जाओ process_status;

	अगर (status == -EAGAIN && sock_ग_लिखोable(transport->inet))
		status = -ENOBUFS;

	अगर (sent > 0 || status == 0) अणु
		req->rq_xmit_bytes_sent += sent;
		अगर (sent >= req->rq_slen)
			वापस 0;
		/* Still some bytes left; set up क्रम a retry later. */
		status = -EAGAIN;
	पूर्ण

process_status:
	चयन (status) अणु
	हाल -ENOTSOCK:
		status = -ENOTCONN;
		/* Should we call xs_बंद() here? */
		अवरोध;
	हाल -EAGAIN:
		status = xs_nospace(req);
		अवरोध;
	हाल -ENETUNREACH:
	हाल -ENOBUFS:
	हाल -EPIPE:
	हाल -ECONNREFUSED:
	हाल -EPERM:
		/* When the server has died, an ICMP port unreachable message
		 * prompts ECONNREFUSED. */
		अवरोध;
	शेष:
		dprपूर्णांकk("RPC:       sendmsg returned unrecognized error %d\n",
			-status);
	पूर्ण

	वापस status;
पूर्ण

/**
 * xs_tcp_send_request - ग_लिखो an RPC request to a TCP socket
 * @req: poपूर्णांकer to RPC request
 *
 * Return values:
 *        0:	The request has been sent
 *   EAGAIN:	The socket was blocked, please call again later to
 *		complete the request
 * ENOTCONN:	Caller needs to invoke connect logic then call again
 *    other:	Some other error occurred, the request was not sent
 *
 * XXX: In the हाल of soft समयouts, should we eventually give up
 *	अगर sendmsg is not able to make progress?
 */
अटल पूर्णांक xs_tcp_send_request(काष्ठा rpc_rqst *req)
अणु
	काष्ठा rpc_xprt *xprt = req->rq_xprt;
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	काष्ठा xdr_buf *xdr = &req->rq_snd_buf;
	rpc_fraghdr rm = xs_stream_record_marker(xdr);
	अचिन्हित पूर्णांक msglen = rm ? req->rq_slen + माप(rm) : req->rq_slen;
	काष्ठा msghdr msg = अणु
		.msg_flags	= XS_SENDMSG_FLAGS,
	पूर्ण;
	bool vm_रुको = false;
	अचिन्हित पूर्णांक sent;
	पूर्णांक status;

	/* Close the stream अगर the previous transmission was incomplete */
	अगर (xs_send_request_was_पातed(transport, req)) अणु
		अगर (transport->sock != शून्य)
			kernel_sock_shutकरोwn(transport->sock, SHUT_RDWR);
		वापस -ENOTCONN;
	पूर्ण
	अगर (!transport->inet)
		वापस -ENOTCONN;

	xs_pktdump("packet data:",
				req->rq_svec->iov_base,
				req->rq_svec->iov_len);

	अगर (test_bit(XPRT_SOCK_UPD_TIMEOUT, &transport->sock_state))
		xs_tcp_set_socket_समयouts(xprt, transport->sock);

	/* Continue transmitting the packet/record. We must be careful
	 * to cope with ग_लिखोspace callbacks arriving _after_ we have
	 * called sendmsg(). */
	req->rq_xसमय = kसमय_get();
	tcp_sock_set_cork(transport->inet, true);
	जबतक (1) अणु
		status = xprt_sock_sendmsg(transport->sock, &msg, xdr,
					   transport->xmit.offset, rm, &sent);

		dprपूर्णांकk("RPC:       xs_tcp_send_request(%u) = %d\n",
				xdr->len - transport->xmit.offset, status);

		/* If we've sent the entire packet, immediately
		 * reset the count of bytes sent. */
		transport->xmit.offset += sent;
		req->rq_bytes_sent = transport->xmit.offset;
		अगर (likely(req->rq_bytes_sent >= msglen)) अणु
			req->rq_xmit_bytes_sent += transport->xmit.offset;
			transport->xmit.offset = 0;
			अगर (atomic_दीर्घ_पढ़ो(&xprt->xmit_queuelen) == 1)
				tcp_sock_set_cork(transport->inet, false);
			वापस 0;
		पूर्ण

		WARN_ON_ONCE(sent == 0 && status == 0);

		अगर (status == -EAGAIN ) अणु
			/*
			 * Return EAGAIN अगर we're sure we're hitting the
			 * socket send buffer limits.
			 */
			अगर (test_bit(SOCK_NOSPACE, &transport->sock->flags))
				अवरोध;
			/*
			 * Did we hit a memory allocation failure?
			 */
			अगर (sent == 0) अणु
				status = -ENOBUFS;
				अगर (vm_रुको)
					अवरोध;
				/* Retry, knowing now that we're below the
				 * socket send buffer limit
				 */
				vm_रुको = true;
			पूर्ण
			जारी;
		पूर्ण
		अगर (status < 0)
			अवरोध;
		vm_रुको = false;
	पूर्ण

	चयन (status) अणु
	हाल -ENOTSOCK:
		status = -ENOTCONN;
		/* Should we call xs_बंद() here? */
		अवरोध;
	हाल -EAGAIN:
		status = xs_nospace(req);
		अवरोध;
	हाल -ECONNRESET:
	हाल -ECONNREFUSED:
	हाल -ENOTCONN:
	हाल -EADDRINUSE:
	हाल -ENOBUFS:
	हाल -EPIPE:
		अवरोध;
	शेष:
		dprपूर्णांकk("RPC:       sendmsg returned unrecognized error %d\n",
			-status);
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम xs_save_old_callbacks(काष्ठा sock_xprt *transport, काष्ठा sock *sk)
अणु
	transport->old_data_पढ़ोy = sk->sk_data_पढ़ोy;
	transport->old_state_change = sk->sk_state_change;
	transport->old_ग_लिखो_space = sk->sk_ग_लिखो_space;
	transport->old_error_report = sk->sk_error_report;
पूर्ण

अटल व्योम xs_restore_old_callbacks(काष्ठा sock_xprt *transport, काष्ठा sock *sk)
अणु
	sk->sk_data_पढ़ोy = transport->old_data_पढ़ोy;
	sk->sk_state_change = transport->old_state_change;
	sk->sk_ग_लिखो_space = transport->old_ग_लिखो_space;
	sk->sk_error_report = transport->old_error_report;
पूर्ण

अटल व्योम xs_sock_reset_state_flags(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);

	clear_bit(XPRT_SOCK_DATA_READY, &transport->sock_state);
	clear_bit(XPRT_SOCK_WAKE_ERROR, &transport->sock_state);
	clear_bit(XPRT_SOCK_WAKE_WRITE, &transport->sock_state);
	clear_bit(XPRT_SOCK_WAKE_DISCONNECT, &transport->sock_state);
पूर्ण

अटल व्योम xs_run_error_worker(काष्ठा sock_xprt *transport, अचिन्हित पूर्णांक nr)
अणु
	set_bit(nr, &transport->sock_state);
	queue_work(xprtiod_workqueue, &transport->error_worker);
पूर्ण

अटल व्योम xs_sock_reset_connection_flags(काष्ठा rpc_xprt *xprt)
अणु
	smp_mb__beक्रमe_atomic();
	clear_bit(XPRT_CLOSE_WAIT, &xprt->state);
	clear_bit(XPRT_CLOSING, &xprt->state);
	xs_sock_reset_state_flags(xprt);
	smp_mb__after_atomic();
पूर्ण

/**
 * xs_error_report - callback to handle TCP socket state errors
 * @sk: socket
 *
 * Note: we करोn't call sock_error() since there may be a rpc_task
 * using the socket, and so we करोn't want to clear sk->sk_err.
 */
अटल व्योम xs_error_report(काष्ठा sock *sk)
अणु
	काष्ठा sock_xprt *transport;
	काष्ठा rpc_xprt *xprt;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	अगर (!(xprt = xprt_from_sock(sk)))
		जाओ out;

	transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	transport->xprt_err = -sk->sk_err;
	अगर (transport->xprt_err == 0)
		जाओ out;
	dprपूर्णांकk("RPC:       xs_error_report client %p, error=%d...\n",
			xprt, -transport->xprt_err);
	trace_rpc_socket_error(xprt, sk->sk_socket, transport->xprt_err);

	/* barrier ensures xprt_err is set beक्रमe XPRT_SOCK_WAKE_ERROR */
	smp_mb__beक्रमe_atomic();
	xs_run_error_worker(transport, XPRT_SOCK_WAKE_ERROR);
 out:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम xs_reset_transport(काष्ठा sock_xprt *transport)
अणु
	काष्ठा socket *sock = transport->sock;
	काष्ठा sock *sk = transport->inet;
	काष्ठा rpc_xprt *xprt = &transport->xprt;
	काष्ठा file *filp = transport->file;

	अगर (sk == शून्य)
		वापस;

	अगर (atomic_पढ़ो(&transport->xprt.swapper))
		sk_clear_meदो_स्मृति(sk);

	kernel_sock_shutकरोwn(sock, SHUT_RDWR);

	mutex_lock(&transport->recv_mutex);
	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	transport->inet = शून्य;
	transport->sock = शून्य;
	transport->file = शून्य;

	sk->sk_user_data = शून्य;

	xs_restore_old_callbacks(transport, sk);
	xprt_clear_connected(xprt);
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	xs_sock_reset_connection_flags(xprt);
	/* Reset stream record info */
	xs_stream_reset_connect(transport);
	mutex_unlock(&transport->recv_mutex);

	trace_rpc_socket_बंद(xprt, sock);
	fput(filp);

	xprt_disconnect_करोne(xprt);
पूर्ण

/**
 * xs_बंद - बंद a socket
 * @xprt: transport
 *
 * This is used when all requests are complete; ie, no DRC state reमुख्यs
 * on the server we want to save.
 *
 * The caller _must_ be holding XPRT_LOCKED in order to aव्योम issues with
 * xs_reset_transport() zeroing the socket from underneath a ग_लिखोr.
 */
अटल व्योम xs_बंद(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);

	dprपूर्णांकk("RPC:       xs_close xprt %p\n", xprt);

	xs_reset_transport(transport);
	xprt->reestablish_समयout = 0;
पूर्ण

अटल व्योम xs_inject_disconnect(काष्ठा rpc_xprt *xprt)
अणु
	dprपूर्णांकk("RPC:       injecting transport disconnect on xprt=%p\n",
		xprt);
	xprt_disconnect_करोne(xprt);
पूर्ण

अटल व्योम xs_xprt_मुक्त(काष्ठा rpc_xprt *xprt)
अणु
	xs_मुक्त_peer_addresses(xprt);
	xprt_मुक्त(xprt);
पूर्ण

/**
 * xs_destroy - prepare to shutकरोwn a transport
 * @xprt: करोomed transport
 *
 */
अटल व्योम xs_destroy(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt,
			काष्ठा sock_xprt, xprt);
	dprपूर्णांकk("RPC:       xs_destroy xprt %p\n", xprt);

	cancel_delayed_work_sync(&transport->connect_worker);
	xs_बंद(xprt);
	cancel_work_sync(&transport->recv_worker);
	cancel_work_sync(&transport->error_worker);
	xs_xprt_मुक्त(xprt);
	module_put(THIS_MODULE);
पूर्ण

/**
 * xs_udp_data_पढ़ो_skb - receive callback क्रम UDP sockets
 * @xprt: transport
 * @sk: socket
 * @skb: skbuff
 *
 */
अटल व्योम xs_udp_data_पढ़ो_skb(काष्ठा rpc_xprt *xprt,
		काष्ठा sock *sk,
		काष्ठा sk_buff *skb)
अणु
	काष्ठा rpc_task *task;
	काष्ठा rpc_rqst *rovr;
	पूर्णांक repsize, copied;
	u32 _xid;
	__be32 *xp;

	repsize = skb->len;
	अगर (repsize < 4) अणु
		dprपूर्णांकk("RPC:       impossible RPC reply size %d!\n", repsize);
		वापस;
	पूर्ण

	/* Copy the XID from the skb... */
	xp = skb_header_poपूर्णांकer(skb, 0, माप(_xid), &_xid);
	अगर (xp == शून्य)
		वापस;

	/* Look up and lock the request corresponding to the given XID */
	spin_lock(&xprt->queue_lock);
	rovr = xprt_lookup_rqst(xprt, *xp);
	अगर (!rovr)
		जाओ out_unlock;
	xprt_pin_rqst(rovr);
	xprt_update_rtt(rovr->rq_task);
	spin_unlock(&xprt->queue_lock);
	task = rovr->rq_task;

	अगर ((copied = rovr->rq_निजी_buf.buflen) > repsize)
		copied = repsize;

	/* Suck it पूर्णांकo the iovec, verअगरy checksum अगर not करोne by hw. */
	अगर (csum_partial_copy_to_xdr(&rovr->rq_निजी_buf, skb)) अणु
		spin_lock(&xprt->queue_lock);
		__UDPX_INC_STATS(sk, UDP_MIB_INERRORS);
		जाओ out_unpin;
	पूर्ण


	spin_lock(&xprt->transport_lock);
	xprt_adjust_cwnd(xprt, task, copied);
	spin_unlock(&xprt->transport_lock);
	spin_lock(&xprt->queue_lock);
	xprt_complete_rqst(task, copied);
	__UDPX_INC_STATS(sk, UDP_MIB_INDATAGRAMS);
out_unpin:
	xprt_unpin_rqst(rovr);
 out_unlock:
	spin_unlock(&xprt->queue_lock);
पूर्ण

अटल व्योम xs_udp_data_receive(काष्ठा sock_xprt *transport)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sock *sk;
	पूर्णांक err;

	mutex_lock(&transport->recv_mutex);
	sk = transport->inet;
	अगर (sk == शून्य)
		जाओ out;
	क्रम (;;) अणु
		skb = skb_recv_udp(sk, 0, 1, &err);
		अगर (skb == शून्य)
			अवरोध;
		xs_udp_data_पढ़ो_skb(&transport->xprt, sk, skb);
		consume_skb(skb);
		cond_resched();
	पूर्ण
	xs_poll_check_पढ़ोable(transport);
out:
	mutex_unlock(&transport->recv_mutex);
पूर्ण

अटल व्योम xs_udp_data_receive_workfn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sock_xprt *transport =
		container_of(work, काष्ठा sock_xprt, recv_worker);
	अचिन्हित पूर्णांक pflags = meदो_स्मृति_nofs_save();

	xs_udp_data_receive(transport);
	meदो_स्मृति_nofs_restore(pflags);
पूर्ण

/**
 * xs_data_पढ़ोy - "data ready" callback क्रम UDP sockets
 * @sk: socket with data to पढ़ो
 *
 */
अटल व्योम xs_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा rpc_xprt *xprt;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	dprपूर्णांकk("RPC:       xs_data_ready...\n");
	xprt = xprt_from_sock(sk);
	अगर (xprt != शून्य) अणु
		काष्ठा sock_xprt *transport = container_of(xprt,
				काष्ठा sock_xprt, xprt);
		transport->old_data_पढ़ोy(sk);
		/* Any data means we had a useful conversation, so
		 * then we करोn't need to delay the next reconnect
		 */
		अगर (xprt->reestablish_समयout)
			xprt->reestablish_समयout = 0;
		अगर (!test_and_set_bit(XPRT_SOCK_DATA_READY, &transport->sock_state))
			queue_work(xprtiod_workqueue, &transport->recv_worker);
	पूर्ण
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

/*
 * Helper function to क्रमce a TCP बंद अगर the server is sending
 * junk and/or it has put us in CLOSE_WAIT
 */
अटल व्योम xs_tcp_क्रमce_बंद(काष्ठा rpc_xprt *xprt)
अणु
	xprt_क्रमce_disconnect(xprt);
पूर्ण

#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
अटल माप_प्रकार xs_tcp_bc_maxpayload(काष्ठा rpc_xprt *xprt)
अणु
	वापस PAGE_SIZE;
पूर्ण
#पूर्ण_अगर /* CONFIG_SUNRPC_BACKCHANNEL */

/**
 * xs_tcp_state_change - callback to handle TCP socket state changes
 * @sk: socket whose state has changed
 *
 */
अटल व्योम xs_tcp_state_change(काष्ठा sock *sk)
अणु
	काष्ठा rpc_xprt *xprt;
	काष्ठा sock_xprt *transport;

	पढ़ो_lock_bh(&sk->sk_callback_lock);
	अगर (!(xprt = xprt_from_sock(sk)))
		जाओ out;
	dprपूर्णांकk("RPC:       xs_tcp_state_change client %p...\n", xprt);
	dprपूर्णांकk("RPC:       state %x conn %d dead %d zapped %d sk_shutdown %d\n",
			sk->sk_state, xprt_connected(xprt),
			sock_flag(sk, SOCK_DEAD),
			sock_flag(sk, SOCK_ZAPPED),
			sk->sk_shutकरोwn);

	transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	trace_rpc_socket_state_change(xprt, sk->sk_socket);
	चयन (sk->sk_state) अणु
	हाल TCP_ESTABLISHED:
		अगर (!xprt_test_and_set_connected(xprt)) अणु
			xprt->connect_cookie++;
			clear_bit(XPRT_SOCK_CONNECTING, &transport->sock_state);
			xprt_clear_connecting(xprt);

			xprt->stat.connect_count++;
			xprt->stat.connect_समय += (दीर्घ)jअगरfies -
						   xprt->stat.connect_start;
			xs_run_error_worker(transport, XPRT_SOCK_WAKE_PENDING);
		पूर्ण
		अवरोध;
	हाल TCP_FIN_WAIT1:
		/* The client initiated a shutकरोwn of the socket */
		xprt->connect_cookie++;
		xprt->reestablish_समयout = 0;
		set_bit(XPRT_CLOSING, &xprt->state);
		smp_mb__beक्रमe_atomic();
		clear_bit(XPRT_CONNECTED, &xprt->state);
		clear_bit(XPRT_CLOSE_WAIT, &xprt->state);
		smp_mb__after_atomic();
		अवरोध;
	हाल TCP_CLOSE_WAIT:
		/* The server initiated a shutकरोwn of the socket */
		xprt->connect_cookie++;
		clear_bit(XPRT_CONNECTED, &xprt->state);
		xs_run_error_worker(transport, XPRT_SOCK_WAKE_DISCONNECT);
		fallthrough;
	हाल TCP_CLOSING:
		/*
		 * If the server बंदd करोwn the connection, make sure that
		 * we back off beक्रमe reconnecting
		 */
		अगर (xprt->reestablish_समयout < XS_TCP_INIT_REEST_TO)
			xprt->reestablish_समयout = XS_TCP_INIT_REEST_TO;
		अवरोध;
	हाल TCP_LAST_ACK:
		set_bit(XPRT_CLOSING, &xprt->state);
		smp_mb__beक्रमe_atomic();
		clear_bit(XPRT_CONNECTED, &xprt->state);
		smp_mb__after_atomic();
		अवरोध;
	हाल TCP_CLOSE:
		अगर (test_and_clear_bit(XPRT_SOCK_CONNECTING,
					&transport->sock_state))
			xprt_clear_connecting(xprt);
		clear_bit(XPRT_CLOSING, &xprt->state);
		/* Trigger the socket release */
		xs_run_error_worker(transport, XPRT_SOCK_WAKE_DISCONNECT);
	पूर्ण
 out:
	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम xs_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;
	काष्ठा sock_xprt *transport;
	काष्ठा rpc_xprt *xprt;

	अगर (!sk->sk_socket)
		वापस;
	clear_bit(SOCK_NOSPACE, &sk->sk_socket->flags);

	अगर (unlikely(!(xprt = xprt_from_sock(sk))))
		वापस;
	transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (!wq || test_and_clear_bit(SOCKWQ_ASYNC_NOSPACE, &wq->flags) == 0)
		जाओ out;

	xs_run_error_worker(transport, XPRT_SOCK_WAKE_WRITE);
	sk->sk_ग_लिखो_pending--;
out:
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * xs_udp_ग_लिखो_space - callback invoked when socket buffer space
 *                             becomes available
 * @sk: socket whose state has changed
 *
 * Called when more output buffer space is available क्रम this socket.
 * We try not to wake our ग_लिखोrs until they can make "significant"
 * progress, otherwise we'll waste resources thrashing kernel_sendmsg
 * with a bunch of small requests.
 */
अटल व्योम xs_udp_ग_लिखो_space(काष्ठा sock *sk)
अणु
	पढ़ो_lock_bh(&sk->sk_callback_lock);

	/* from net/core/sock.c:sock_def_ग_लिखो_space */
	अगर (sock_ग_लिखोable(sk))
		xs_ग_लिखो_space(sk);

	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

/**
 * xs_tcp_ग_लिखो_space - callback invoked when socket buffer space
 *                             becomes available
 * @sk: socket whose state has changed
 *
 * Called when more output buffer space is available क्रम this socket.
 * We try not to wake our ग_लिखोrs until they can make "significant"
 * progress, otherwise we'll waste resources thrashing kernel_sendmsg
 * with a bunch of small requests.
 */
अटल व्योम xs_tcp_ग_लिखो_space(काष्ठा sock *sk)
अणु
	पढ़ो_lock_bh(&sk->sk_callback_lock);

	/* from net/core/stream.c:sk_stream_ग_लिखो_space */
	अगर (sk_stream_is_ग_लिखोable(sk))
		xs_ग_लिखो_space(sk);

	पढ़ो_unlock_bh(&sk->sk_callback_lock);
पूर्ण

अटल व्योम xs_udp_करो_set_buffer_size(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	काष्ठा sock *sk = transport->inet;

	अगर (transport->rcvsize) अणु
		sk->sk_userlocks |= SOCK_RCVBUF_LOCK;
		sk->sk_rcvbuf = transport->rcvsize * xprt->max_reqs * 2;
	पूर्ण
	अगर (transport->sndsize) अणु
		sk->sk_userlocks |= SOCK_SNDBUF_LOCK;
		sk->sk_sndbuf = transport->sndsize * xprt->max_reqs * 2;
		sk->sk_ग_लिखो_space(sk);
	पूर्ण
पूर्ण

/**
 * xs_udp_set_buffer_size - set send and receive limits
 * @xprt: generic transport
 * @sndsize: requested size of send buffer, in bytes
 * @rcvsize: requested size of receive buffer, in bytes
 *
 * Set socket send and receive buffer size limits.
 */
अटल व्योम xs_udp_set_buffer_size(काष्ठा rpc_xprt *xprt, माप_प्रकार sndsize, माप_प्रकार rcvsize)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);

	transport->sndsize = 0;
	अगर (sndsize)
		transport->sndsize = sndsize + 1024;
	transport->rcvsize = 0;
	अगर (rcvsize)
		transport->rcvsize = rcvsize + 1024;

	xs_udp_करो_set_buffer_size(xprt);
पूर्ण

/**
 * xs_udp_समयr - called when a retransmit समयout occurs on a UDP transport
 * @xprt: controlling transport
 * @task: task that समयd out
 *
 * Adjust the congestion winकरोw after a retransmit समयout has occurred.
 */
अटल व्योम xs_udp_समयr(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	spin_lock(&xprt->transport_lock);
	xprt_adjust_cwnd(xprt, task, -ETIMEDOUT);
	spin_unlock(&xprt->transport_lock);
पूर्ण

अटल पूर्णांक xs_get_अक्रमom_port(व्योम)
अणु
	अचिन्हित लघु min = xprt_min_resvport, max = xprt_max_resvport;
	अचिन्हित लघु range;
	अचिन्हित लघु अक्रम;

	अगर (max < min)
		वापस -EADDRINUSE;
	range = max - min + 1;
	अक्रम = (अचिन्हित लघु) pअक्रमom_u32() % range;
	वापस अक्रम + min;
पूर्ण

अटल अचिन्हित लघु xs_sock_getport(काष्ठा socket *sock)
अणु
	काष्ठा sockaddr_storage buf;
	अचिन्हित लघु port = 0;

	अगर (kernel_माला_लोockname(sock, (काष्ठा sockaddr *)&buf) < 0)
		जाओ out;
	चयन (buf.ss_family) अणु
	हाल AF_INET6:
		port = ntohs(((काष्ठा sockaddr_in6 *)&buf)->sin6_port);
		अवरोध;
	हाल AF_INET:
		port = ntohs(((काष्ठा sockaddr_in *)&buf)->sin_port);
	पूर्ण
out:
	वापस port;
पूर्ण

/**
 * xs_set_port - reset the port number in the remote endpoपूर्णांक address
 * @xprt: generic transport
 * @port: new port number
 *
 */
अटल व्योम xs_set_port(काष्ठा rpc_xprt *xprt, अचिन्हित लघु port)
अणु
	dprपूर्णांकk("RPC:       setting port for xprt %p to %u\n", xprt, port);

	rpc_set_port(xs_addr(xprt), port);
	xs_update_peer_port(xprt);
पूर्ण

अटल व्योम xs_set_srcport(काष्ठा sock_xprt *transport, काष्ठा socket *sock)
अणु
	अगर (transport->srcport == 0 && transport->xprt.reuseport)
		transport->srcport = xs_sock_getport(sock);
पूर्ण

अटल पूर्णांक xs_get_srcport(काष्ठा sock_xprt *transport)
अणु
	पूर्णांक port = transport->srcport;

	अगर (port == 0 && transport->xprt.resvport)
		port = xs_get_अक्रमom_port();
	वापस port;
पूर्ण

अटल अचिन्हित लघु xs_next_srcport(काष्ठा sock_xprt *transport, अचिन्हित लघु port)
अणु
	अगर (transport->srcport != 0)
		transport->srcport = 0;
	अगर (!transport->xprt.resvport)
		वापस 0;
	अगर (port <= xprt_min_resvport || port > xprt_max_resvport)
		वापस xprt_max_resvport;
	वापस --port;
पूर्ण
अटल पूर्णांक xs_bind(काष्ठा sock_xprt *transport, काष्ठा socket *sock)
अणु
	काष्ठा sockaddr_storage myaddr;
	पूर्णांक err, nloop = 0;
	पूर्णांक port = xs_get_srcport(transport);
	अचिन्हित लघु last;

	/*
	 * If we are asking क्रम any ephemeral port (i.e. port == 0 &&
	 * transport->xprt.resvport == 0), करोn't bind.  Let the local
	 * port selection happen implicitly when the socket is used
	 * (क्रम example at connect समय).
	 *
	 * This ensures that we can जारी to establish TCP
	 * connections even when all local ephemeral ports are alपढ़ोy
	 * a part of some TCP connection.  This makes no dअगरference
	 * क्रम UDP sockets, but also करोesn't harm them.
	 *
	 * If we're asking क्रम any reserved port (i.e. port == 0 &&
	 * transport->xprt.resvport == 1) xs_get_srcport above will
	 * ensure that port is non-zero and we will bind as needed.
	 */
	अगर (port <= 0)
		वापस port;

	स_नकल(&myaddr, &transport->srcaddr, transport->xprt.addrlen);
	करो अणु
		rpc_set_port((काष्ठा sockaddr *)&myaddr, port);
		err = kernel_bind(sock, (काष्ठा sockaddr *)&myaddr,
				transport->xprt.addrlen);
		अगर (err == 0) अणु
			transport->srcport = port;
			अवरोध;
		पूर्ण
		last = port;
		port = xs_next_srcport(transport, port);
		अगर (port > last)
			nloop++;
	पूर्ण जबतक (err == -EADDRINUSE && nloop != 2);

	अगर (myaddr.ss_family == AF_INET)
		dprपूर्णांकk("RPC:       %s %pI4:%u: %s (%d)\n", __func__,
				&((काष्ठा sockaddr_in *)&myaddr)->sin_addr,
				port, err ? "failed" : "ok", err);
	अन्यथा
		dprपूर्णांकk("RPC:       %s %pI6:%u: %s (%d)\n", __func__,
				&((काष्ठा sockaddr_in6 *)&myaddr)->sin6_addr,
				port, err ? "failed" : "ok", err);
	वापस err;
पूर्ण

/*
 * We करोn't support स्वतःbind on AF_LOCAL sockets
 */
अटल व्योम xs_local_rpcbind(काष्ठा rpc_task *task)
अणु
	xprt_set_bound(task->tk_xprt);
पूर्ण

अटल व्योम xs_local_set_port(काष्ठा rpc_xprt *xprt, अचिन्हित लघु port)
अणु
पूर्ण

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
अटल काष्ठा lock_class_key xs_key[2];
अटल काष्ठा lock_class_key xs_slock_key[2];

अटल अंतरभूत व्योम xs_reclassअगरy_socketu(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	sock_lock_init_class_and_name(sk, "slock-AF_LOCAL-RPC",
		&xs_slock_key[1], "sk_lock-AF_LOCAL-RPC", &xs_key[1]);
पूर्ण

अटल अंतरभूत व्योम xs_reclassअगरy_socket4(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	sock_lock_init_class_and_name(sk, "slock-AF_INET-RPC",
		&xs_slock_key[0], "sk_lock-AF_INET-RPC", &xs_key[0]);
पूर्ण

अटल अंतरभूत व्योम xs_reclassअगरy_socket6(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	sock_lock_init_class_and_name(sk, "slock-AF_INET6-RPC",
		&xs_slock_key[1], "sk_lock-AF_INET6-RPC", &xs_key[1]);
पूर्ण

अटल अंतरभूत व्योम xs_reclassअगरy_socket(पूर्णांक family, काष्ठा socket *sock)
अणु
	अगर (WARN_ON_ONCE(!sock_allow_reclassअगरication(sock->sk)))
		वापस;

	चयन (family) अणु
	हाल AF_LOCAL:
		xs_reclassअगरy_socketu(sock);
		अवरोध;
	हाल AF_INET:
		xs_reclassअगरy_socket4(sock);
		अवरोध;
	हाल AF_INET6:
		xs_reclassअगरy_socket6(sock);
		अवरोध;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम xs_reclassअगरy_socket(पूर्णांक family, काष्ठा socket *sock)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम xs_dummy_setup_socket(काष्ठा work_काष्ठा *work)
अणु
पूर्ण

अटल काष्ठा socket *xs_create_sock(काष्ठा rpc_xprt *xprt,
		काष्ठा sock_xprt *transport, पूर्णांक family, पूर्णांक type,
		पूर्णांक protocol, bool reuseport)
अणु
	काष्ठा file *filp;
	काष्ठा socket *sock;
	पूर्णांक err;

	err = __sock_create(xprt->xprt_net, family, type, protocol, &sock, 1);
	अगर (err < 0) अणु
		dprपूर्णांकk("RPC:       can't create %d transport socket (%d).\n",
				protocol, -err);
		जाओ out;
	पूर्ण
	xs_reclassअगरy_socket(family, sock);

	अगर (reuseport)
		sock_set_reuseport(sock->sk);

	err = xs_bind(transport, sock);
	अगर (err) अणु
		sock_release(sock);
		जाओ out;
	पूर्ण

	filp = sock_alloc_file(sock, O_NONBLOCK, शून्य);
	अगर (IS_ERR(filp))
		वापस ERR_CAST(filp);
	transport->file = filp;

	वापस sock;
out:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक xs_local_finish_connecting(काष्ठा rpc_xprt *xprt,
				      काष्ठा socket *sock)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt,
									xprt);

	अगर (!transport->inet) अणु
		काष्ठा sock *sk = sock->sk;

		ग_लिखो_lock_bh(&sk->sk_callback_lock);

		xs_save_old_callbacks(transport, sk);

		sk->sk_user_data = xprt;
		sk->sk_data_पढ़ोy = xs_data_पढ़ोy;
		sk->sk_ग_लिखो_space = xs_udp_ग_लिखो_space;
		sock_set_flag(sk, SOCK_FASYNC);
		sk->sk_error_report = xs_error_report;

		xprt_clear_connected(xprt);

		/* Reset to new socket */
		transport->sock = sock;
		transport->inet = sk;

		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	पूर्ण

	xs_stream_start_connect(transport);

	वापस kernel_connect(sock, xs_addr(xprt), xprt->addrlen, 0);
पूर्ण

/**
 * xs_local_setup_socket - create AF_LOCAL socket, connect to a local endpoपूर्णांक
 * @transport: socket transport to connect
 */
अटल पूर्णांक xs_local_setup_socket(काष्ठा sock_xprt *transport)
अणु
	काष्ठा rpc_xprt *xprt = &transport->xprt;
	काष्ठा file *filp;
	काष्ठा socket *sock;
	पूर्णांक status;

	status = __sock_create(xprt->xprt_net, AF_LOCAL,
					SOCK_STREAM, 0, &sock, 1);
	अगर (status < 0) अणु
		dprपूर्णांकk("RPC:       can't create AF_LOCAL "
			"transport socket (%d).\n", -status);
		जाओ out;
	पूर्ण
	xs_reclassअगरy_socket(AF_LOCAL, sock);

	filp = sock_alloc_file(sock, O_NONBLOCK, शून्य);
	अगर (IS_ERR(filp)) अणु
		status = PTR_ERR(filp);
		जाओ out;
	पूर्ण
	transport->file = filp;

	dprपूर्णांकk("RPC:       worker connecting xprt %p via AF_LOCAL to %s\n",
			xprt, xprt->address_strings[RPC_DISPLAY_ADDR]);

	status = xs_local_finish_connecting(xprt, sock);
	trace_rpc_socket_connect(xprt, sock, status);
	चयन (status) अणु
	हाल 0:
		dprपूर्णांकk("RPC:       xprt %p connected to %s\n",
				xprt, xprt->address_strings[RPC_DISPLAY_ADDR]);
		xprt->stat.connect_count++;
		xprt->stat.connect_समय += (दीर्घ)jअगरfies -
					   xprt->stat.connect_start;
		xprt_set_connected(xprt);
		अवरोध;
	हाल -ENOBUFS:
		अवरोध;
	हाल -ENOENT:
		dprपूर्णांकk("RPC:       xprt %p: socket %s does not exist\n",
				xprt, xprt->address_strings[RPC_DISPLAY_ADDR]);
		अवरोध;
	हाल -ECONNREFUSED:
		dprपूर्णांकk("RPC:       xprt %p: connection refused for %s\n",
				xprt, xprt->address_strings[RPC_DISPLAY_ADDR]);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s: unhandled error (%d) connecting to %s\n",
				__func__, -status,
				xprt->address_strings[RPC_DISPLAY_ADDR]);
	पूर्ण

out:
	xprt_clear_connecting(xprt);
	xprt_wake_pending_tasks(xprt, status);
	वापस status;
पूर्ण

अटल व्योम xs_local_connect(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	पूर्णांक ret;

	 अगर (RPC_IS_ASYNC(task)) अणु
		/*
		 * We want the AF_LOCAL connect to be resolved in the
		 * fileप्रणाली namespace of the process making the rpc
		 * call.  Thus we connect synchronously.
		 *
		 * If we want to support asynchronous AF_LOCAL calls,
		 * we'll need to figure out how to pass a namespace to
		 * connect.
		 */
		task->tk_rpc_status = -ENOTCONN;
		rpc_निकास(task, -ENOTCONN);
		वापस;
	पूर्ण
	ret = xs_local_setup_socket(transport);
	अगर (ret && !RPC_IS_SOFTCONN(task))
		msleep_पूर्णांकerruptible(15000);
पूर्ण

#अगर IS_ENABLED(CONFIG_SUNRPC_SWAP)
/*
 * Note that this should be called with XPRT_LOCKED held (or when we otherwise
 * know that we have exclusive access to the socket), to guard against
 * races with xs_reset_transport.
 */
अटल व्योम xs_set_meदो_स्मृति(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt,
			xprt);

	/*
	 * If there's no sock, then we have nothing to set. The
	 * reconnecting process will get it क्रम us.
	 */
	अगर (!transport->inet)
		वापस;
	अगर (atomic_पढ़ो(&xprt->swapper))
		sk_set_meदो_स्मृति(transport->inet);
पूर्ण

/**
 * xs_enable_swap - Tag this transport as being used क्रम swap.
 * @xprt: transport to tag
 *
 * Take a reference to this transport on behalf of the rpc_clnt, and
 * optionally mark it क्रम swapping अगर it wasn't alपढ़ोy.
 */
अटल पूर्णांक
xs_enable_swap(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा sock_xprt *xs = container_of(xprt, काष्ठा sock_xprt, xprt);

	अगर (atomic_inc_वापस(&xprt->swapper) != 1)
		वापस 0;
	अगर (रुको_on_bit_lock(&xprt->state, XPRT_LOCKED, TASK_KILLABLE))
		वापस -ERESTARTSYS;
	अगर (xs->inet)
		sk_set_meदो_स्मृति(xs->inet);
	xprt_release_xprt(xprt, शून्य);
	वापस 0;
पूर्ण

/**
 * xs_disable_swap - Untag this transport as being used क्रम swap.
 * @xprt: transport to tag
 *
 * Drop a "swapper" reference to this xprt on behalf of the rpc_clnt. If the
 * swapper refcount goes to 0, untag the socket as a meदो_स्मृति socket.
 */
अटल व्योम
xs_disable_swap(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा sock_xprt *xs = container_of(xprt, काष्ठा sock_xprt, xprt);

	अगर (!atomic_dec_and_test(&xprt->swapper))
		वापस;
	अगर (रुको_on_bit_lock(&xprt->state, XPRT_LOCKED, TASK_KILLABLE))
		वापस;
	अगर (xs->inet)
		sk_clear_meदो_स्मृति(xs->inet);
	xprt_release_xprt(xprt, शून्य);
पूर्ण
#अन्यथा
अटल व्योम xs_set_meदो_स्मृति(काष्ठा rpc_xprt *xprt)
अणु
पूर्ण

अटल पूर्णांक
xs_enable_swap(काष्ठा rpc_xprt *xprt)
अणु
	वापस -EINVAL;
पूर्ण

अटल व्योम
xs_disable_swap(काष्ठा rpc_xprt *xprt)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम xs_udp_finish_connecting(काष्ठा rpc_xprt *xprt, काष्ठा socket *sock)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);

	अगर (!transport->inet) अणु
		काष्ठा sock *sk = sock->sk;

		ग_लिखो_lock_bh(&sk->sk_callback_lock);

		xs_save_old_callbacks(transport, sk);

		sk->sk_user_data = xprt;
		sk->sk_data_पढ़ोy = xs_data_पढ़ोy;
		sk->sk_ग_लिखो_space = xs_udp_ग_लिखो_space;
		sock_set_flag(sk, SOCK_FASYNC);

		xprt_set_connected(xprt);

		/* Reset to new socket */
		transport->sock = sock;
		transport->inet = sk;

		xs_set_meदो_स्मृति(xprt);

		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	पूर्ण
	xs_udp_करो_set_buffer_size(xprt);

	xprt->stat.connect_start = jअगरfies;
पूर्ण

अटल व्योम xs_udp_setup_socket(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sock_xprt *transport =
		container_of(work, काष्ठा sock_xprt, connect_worker.work);
	काष्ठा rpc_xprt *xprt = &transport->xprt;
	काष्ठा socket *sock;
	पूर्णांक status = -EIO;

	sock = xs_create_sock(xprt, transport,
			xs_addr(xprt)->sa_family, SOCK_DGRAM,
			IPPROTO_UDP, false);
	अगर (IS_ERR(sock))
		जाओ out;

	dprपूर्णांकk("RPC:       worker connecting xprt %p via %s to "
				"%s (port %s)\n", xprt,
			xprt->address_strings[RPC_DISPLAY_PROTO],
			xprt->address_strings[RPC_DISPLAY_ADDR],
			xprt->address_strings[RPC_DISPLAY_PORT]);

	xs_udp_finish_connecting(xprt, sock);
	trace_rpc_socket_connect(xprt, sock, 0);
	status = 0;
out:
	xprt_clear_connecting(xprt);
	xprt_unlock_connect(xprt, transport);
	xprt_wake_pending_tasks(xprt, status);
पूर्ण

/**
 * xs_tcp_shutकरोwn - gracefully shut करोwn a TCP socket
 * @xprt: transport
 *
 * Initiates a graceful shutकरोwn of the TCP socket by calling the
 * equivalent of shutकरोwn(SHUT_RDWR);
 */
अटल व्योम xs_tcp_shutकरोwn(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	काष्ठा socket *sock = transport->sock;
	पूर्णांक skst = transport->inet ? transport->inet->sk_state : TCP_CLOSE;

	अगर (sock == शून्य)
		वापस;
	चयन (skst) अणु
	शेष:
		kernel_sock_shutकरोwn(sock, SHUT_RDWR);
		trace_rpc_socket_shutकरोwn(xprt, sock);
		अवरोध;
	हाल TCP_CLOSE:
	हाल TCP_TIME_WAIT:
		xs_reset_transport(transport);
	पूर्ण
पूर्ण

अटल व्योम xs_tcp_set_socket_समयouts(काष्ठा rpc_xprt *xprt,
		काष्ठा socket *sock)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	अचिन्हित पूर्णांक keepidle;
	अचिन्हित पूर्णांक keepcnt;
	अचिन्हित पूर्णांक समयo;

	spin_lock(&xprt->transport_lock);
	keepidle = DIV_ROUND_UP(xprt->समयout->to_initval, HZ);
	keepcnt = xprt->समयout->to_retries + 1;
	समयo = jअगरfies_to_msecs(xprt->समयout->to_initval) *
		(xprt->समयout->to_retries + 1);
	clear_bit(XPRT_SOCK_UPD_TIMEOUT, &transport->sock_state);
	spin_unlock(&xprt->transport_lock);

	/* TCP Keepalive options */
	sock_set_keepalive(sock->sk);
	tcp_sock_set_keepidle(sock->sk, keepidle);
	tcp_sock_set_keepपूर्णांकvl(sock->sk, keepidle);
	tcp_sock_set_keepcnt(sock->sk, keepcnt);

	/* TCP user समयout (see RFC5482) */
	tcp_sock_set_user_समयout(sock->sk, समयo);
पूर्ण

अटल व्योम xs_tcp_set_connect_समयout(काष्ठा rpc_xprt *xprt,
		अचिन्हित दीर्घ connect_समयout,
		अचिन्हित दीर्घ reconnect_समयout)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	काष्ठा rpc_समयout to;
	अचिन्हित दीर्घ initval;

	spin_lock(&xprt->transport_lock);
	अगर (reconnect_समयout < xprt->max_reconnect_समयout)
		xprt->max_reconnect_समयout = reconnect_समयout;
	अगर (connect_समयout < xprt->connect_समयout) अणु
		स_नकल(&to, xprt->समयout, माप(to));
		initval = DIV_ROUND_UP(connect_समयout, to.to_retries + 1);
		/* Arbitrary lower limit */
		अगर (initval <  XS_TCP_INIT_REEST_TO << 1)
			initval = XS_TCP_INIT_REEST_TO << 1;
		to.to_initval = initval;
		to.to_maxval = initval;
		स_नकल(&transport->tcp_समयout, &to,
				माप(transport->tcp_समयout));
		xprt->समयout = &transport->tcp_समयout;
		xprt->connect_समयout = connect_समयout;
	पूर्ण
	set_bit(XPRT_SOCK_UPD_TIMEOUT, &transport->sock_state);
	spin_unlock(&xprt->transport_lock);
पूर्ण

अटल पूर्णांक xs_tcp_finish_connecting(काष्ठा rpc_xprt *xprt, काष्ठा socket *sock)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	पूर्णांक ret = -ENOTCONN;

	अगर (!transport->inet) अणु
		काष्ठा sock *sk = sock->sk;

		/* Aव्योम temporary address, they are bad क्रम दीर्घ-lived
		 * connections such as NFS mounts.
		 * RFC4941, section 3.6 suggests that:
		 *    Inभागidual applications, which have specअगरic
		 *    knowledge about the normal duration of connections,
		 *    MAY override this as appropriate.
		 */
		अगर (xs_addr(xprt)->sa_family == PF_INET6) अणु
			ip6_sock_set_addr_preferences(sk,
				IPV6_PREFER_SRC_PUBLIC);
		पूर्ण

		xs_tcp_set_socket_समयouts(xprt, sock);
		tcp_sock_set_nodelay(sk);

		ग_लिखो_lock_bh(&sk->sk_callback_lock);

		xs_save_old_callbacks(transport, sk);

		sk->sk_user_data = xprt;
		sk->sk_data_पढ़ोy = xs_data_पढ़ोy;
		sk->sk_state_change = xs_tcp_state_change;
		sk->sk_ग_लिखो_space = xs_tcp_ग_लिखो_space;
		sock_set_flag(sk, SOCK_FASYNC);
		sk->sk_error_report = xs_error_report;

		/* socket options */
		sock_reset_flag(sk, SOCK_LINGER);

		xprt_clear_connected(xprt);

		/* Reset to new socket */
		transport->sock = sock;
		transport->inet = sk;

		ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	पूर्ण

	अगर (!xprt_bound(xprt))
		जाओ out;

	xs_set_meदो_स्मृति(xprt);

	xs_stream_start_connect(transport);

	/* Tell the socket layer to start connecting... */
	set_bit(XPRT_SOCK_CONNECTING, &transport->sock_state);
	ret = kernel_connect(sock, xs_addr(xprt), xprt->addrlen, O_NONBLOCK);
	चयन (ret) अणु
	हाल 0:
		xs_set_srcport(transport, sock);
		fallthrough;
	हाल -EINPROGRESS:
		/* SYN_SENT! */
		अगर (xprt->reestablish_समयout < XS_TCP_INIT_REEST_TO)
			xprt->reestablish_समयout = XS_TCP_INIT_REEST_TO;
		अवरोध;
	हाल -EADDRNOTAVAIL:
		/* Source port number is unavailable. Try a new one! */
		transport->srcport = 0;
	पूर्ण
out:
	वापस ret;
पूर्ण

/**
 * xs_tcp_setup_socket - create a TCP socket and connect to a remote endpoपूर्णांक
 * @work: queued work item
 *
 * Invoked by a work queue tasklet.
 */
अटल व्योम xs_tcp_setup_socket(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sock_xprt *transport =
		container_of(work, काष्ठा sock_xprt, connect_worker.work);
	काष्ठा socket *sock = transport->sock;
	काष्ठा rpc_xprt *xprt = &transport->xprt;
	पूर्णांक status = -EIO;

	अगर (!sock) अणु
		sock = xs_create_sock(xprt, transport,
				xs_addr(xprt)->sa_family, SOCK_STREAM,
				IPPROTO_TCP, true);
		अगर (IS_ERR(sock)) अणु
			status = PTR_ERR(sock);
			जाओ out;
		पूर्ण
	पूर्ण

	dprपूर्णांकk("RPC:       worker connecting xprt %p via %s to "
				"%s (port %s)\n", xprt,
			xprt->address_strings[RPC_DISPLAY_PROTO],
			xprt->address_strings[RPC_DISPLAY_ADDR],
			xprt->address_strings[RPC_DISPLAY_PORT]);

	status = xs_tcp_finish_connecting(xprt, sock);
	trace_rpc_socket_connect(xprt, sock, status);
	dprपूर्णांकk("RPC:       %p connect status %d connected %d sock state %d\n",
			xprt, -status, xprt_connected(xprt),
			sock->sk->sk_state);
	चयन (status) अणु
	शेष:
		prपूर्णांकk("%s: connect returned unhandled error %d\n",
			__func__, status);
		fallthrough;
	हाल -EADDRNOTAVAIL:
		/* We're probably in TIME_WAIT. Get rid of existing socket,
		 * and retry
		 */
		xs_tcp_क्रमce_बंद(xprt);
		अवरोध;
	हाल 0:
	हाल -EINPROGRESS:
	हाल -EALREADY:
		xprt_unlock_connect(xprt, transport);
		वापस;
	हाल -EINVAL:
		/* Happens, क्रम instance, अगर the user specअगरied a link
		 * local IPv6 address without a scope-id.
		 */
	हाल -ECONNREFUSED:
	हाल -ECONNRESET:
	हाल -ENETDOWN:
	हाल -ENETUNREACH:
	हाल -EHOSTUNREACH:
	हाल -EADDRINUSE:
	हाल -ENOBUFS:
		/* xs_tcp_क्रमce_बंद() wakes tasks with a fixed error code.
		 * We need to wake them first to ensure the correct error code.
		 */
		xprt_wake_pending_tasks(xprt, status);
		xs_tcp_क्रमce_बंद(xprt);
		जाओ out;
	पूर्ण
	status = -EAGAIN;
out:
	xprt_clear_connecting(xprt);
	xprt_unlock_connect(xprt, transport);
	xprt_wake_pending_tasks(xprt, status);
पूर्ण

/**
 * xs_connect - connect a socket to a remote endpoपूर्णांक
 * @xprt: poपूर्णांकer to transport काष्ठाure
 * @task: address of RPC task that manages state of connect request
 *
 * TCP: If the remote end dropped the connection, delay reconnecting.
 *
 * UDP socket connects are synchronous, but we use a work queue anyway
 * to guarantee that even unprivileged user processes can set up a
 * socket on a privileged port.
 *
 * If a UDP socket connect fails, the delay behavior here prevents
 * retry floods (hard mounts).
 */
अटल व्योम xs_connect(काष्ठा rpc_xprt *xprt, काष्ठा rpc_task *task)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	अचिन्हित दीर्घ delay = 0;

	WARN_ON_ONCE(!xprt_lock_connect(xprt, task, transport));

	अगर (transport->sock != शून्य) अणु
		dprपूर्णांकk("RPC:       xs_connect delayed xprt %p for %lu "
				"seconds\n",
				xprt, xprt->reestablish_समयout / HZ);

		/* Start by resetting any existing state */
		xs_reset_transport(transport);

		delay = xprt_reconnect_delay(xprt);
		xprt_reconnect_backoff(xprt, XS_TCP_INIT_REEST_TO);

	पूर्ण अन्यथा
		dprपूर्णांकk("RPC:       xs_connect scheduled xprt %p\n", xprt);

	queue_delayed_work(xprtiod_workqueue,
			&transport->connect_worker,
			delay);
पूर्ण

अटल व्योम xs_wake_disconnect(काष्ठा sock_xprt *transport)
अणु
	अगर (test_and_clear_bit(XPRT_SOCK_WAKE_DISCONNECT, &transport->sock_state))
		xs_tcp_क्रमce_बंद(&transport->xprt);
पूर्ण

अटल व्योम xs_wake_ग_लिखो(काष्ठा sock_xprt *transport)
अणु
	अगर (test_and_clear_bit(XPRT_SOCK_WAKE_WRITE, &transport->sock_state))
		xprt_ग_लिखो_space(&transport->xprt);
पूर्ण

अटल व्योम xs_wake_error(काष्ठा sock_xprt *transport)
अणु
	पूर्णांक sockerr;

	अगर (!test_bit(XPRT_SOCK_WAKE_ERROR, &transport->sock_state))
		वापस;
	mutex_lock(&transport->recv_mutex);
	अगर (transport->sock == शून्य)
		जाओ out;
	अगर (!test_and_clear_bit(XPRT_SOCK_WAKE_ERROR, &transport->sock_state))
		जाओ out;
	sockerr = xchg(&transport->xprt_err, 0);
	अगर (sockerr < 0)
		xprt_wake_pending_tasks(&transport->xprt, sockerr);
out:
	mutex_unlock(&transport->recv_mutex);
पूर्ण

अटल व्योम xs_wake_pending(काष्ठा sock_xprt *transport)
अणु
	अगर (test_and_clear_bit(XPRT_SOCK_WAKE_PENDING, &transport->sock_state))
		xprt_wake_pending_tasks(&transport->xprt, -EAGAIN);
पूर्ण

अटल व्योम xs_error_handle(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sock_xprt *transport = container_of(work,
			काष्ठा sock_xprt, error_worker);

	xs_wake_disconnect(transport);
	xs_wake_ग_लिखो(transport);
	xs_wake_error(transport);
	xs_wake_pending(transport);
पूर्ण

/**
 * xs_local_prपूर्णांक_stats - display AF_LOCAL socket-specअगरic stats
 * @xprt: rpc_xprt काष्ठा containing statistics
 * @seq: output file
 *
 */
अटल व्योम xs_local_prपूर्णांक_stats(काष्ठा rpc_xprt *xprt, काष्ठा seq_file *seq)
अणु
	दीर्घ idle_समय = 0;

	अगर (xprt_connected(xprt))
		idle_समय = (दीर्घ)(jअगरfies - xprt->last_used) / HZ;

	seq_म_लिखो(seq, "\txprt:\tlocal %lu %lu %lu %ld %lu %lu %lu "
			"%llu %llu %lu %llu %llu\n",
			xprt->stat.bind_count,
			xprt->stat.connect_count,
			xprt->stat.connect_समय / HZ,
			idle_समय,
			xprt->stat.sends,
			xprt->stat.recvs,
			xprt->stat.bad_xids,
			xprt->stat.req_u,
			xprt->stat.bklog_u,
			xprt->stat.max_slots,
			xprt->stat.sending_u,
			xprt->stat.pending_u);
पूर्ण

/**
 * xs_udp_prपूर्णांक_stats - display UDP socket-specअगरic stats
 * @xprt: rpc_xprt काष्ठा containing statistics
 * @seq: output file
 *
 */
अटल व्योम xs_udp_prपूर्णांक_stats(काष्ठा rpc_xprt *xprt, काष्ठा seq_file *seq)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);

	seq_म_लिखो(seq, "\txprt:\tudp %u %lu %lu %lu %lu %llu %llu "
			"%lu %llu %llu\n",
			transport->srcport,
			xprt->stat.bind_count,
			xprt->stat.sends,
			xprt->stat.recvs,
			xprt->stat.bad_xids,
			xprt->stat.req_u,
			xprt->stat.bklog_u,
			xprt->stat.max_slots,
			xprt->stat.sending_u,
			xprt->stat.pending_u);
पूर्ण

/**
 * xs_tcp_prपूर्णांक_stats - display TCP socket-specअगरic stats
 * @xprt: rpc_xprt काष्ठा containing statistics
 * @seq: output file
 *
 */
अटल व्योम xs_tcp_prपूर्णांक_stats(काष्ठा rpc_xprt *xprt, काष्ठा seq_file *seq)
अणु
	काष्ठा sock_xprt *transport = container_of(xprt, काष्ठा sock_xprt, xprt);
	दीर्घ idle_समय = 0;

	अगर (xprt_connected(xprt))
		idle_समय = (दीर्घ)(jअगरfies - xprt->last_used) / HZ;

	seq_म_लिखो(seq, "\txprt:\ttcp %u %lu %lu %lu %ld %lu %lu %lu "
			"%llu %llu %lu %llu %llu\n",
			transport->srcport,
			xprt->stat.bind_count,
			xprt->stat.connect_count,
			xprt->stat.connect_समय / HZ,
			idle_समय,
			xprt->stat.sends,
			xprt->stat.recvs,
			xprt->stat.bad_xids,
			xprt->stat.req_u,
			xprt->stat.bklog_u,
			xprt->stat.max_slots,
			xprt->stat.sending_u,
			xprt->stat.pending_u);
पूर्ण

/*
 * Allocate a bunch of pages क्रम a scratch buffer क्रम the rpc code. The reason
 * we allocate pages instead करोing a kदो_स्मृति like rpc_दो_स्मृति is because we want
 * to use the server side send routines.
 */
अटल पूर्णांक bc_दो_स्मृति(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *rqst = task->tk_rqstp;
	माप_प्रकार size = rqst->rq_callsize;
	काष्ठा page *page;
	काष्ठा rpc_buffer *buf;

	अगर (size > PAGE_SIZE - माप(काष्ठा rpc_buffer)) अणु
		WARN_ONCE(1, "xprtsock: large bc buffer request (size %zu)\n",
			  size);
		वापस -EINVAL;
	पूर्ण

	page = alloc_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	buf = page_address(page);
	buf->len = PAGE_SIZE;

	rqst->rq_buffer = buf->data;
	rqst->rq_rbuffer = (अक्षर *)rqst->rq_buffer + rqst->rq_callsize;
	वापस 0;
पूर्ण

/*
 * Free the space allocated in the bc_alloc routine
 */
अटल व्योम bc_मुक्त(काष्ठा rpc_task *task)
अणु
	व्योम *buffer = task->tk_rqstp->rq_buffer;
	काष्ठा rpc_buffer *buf;

	buf = container_of(buffer, काष्ठा rpc_buffer, data);
	मुक्त_page((अचिन्हित दीर्घ)buf);
पूर्ण

अटल पूर्णांक bc_sendto(काष्ठा rpc_rqst *req)
अणु
	काष्ठा xdr_buf *xdr = &req->rq_snd_buf;
	काष्ठा sock_xprt *transport =
			container_of(req->rq_xprt, काष्ठा sock_xprt, xprt);
	काष्ठा msghdr msg = अणु
		.msg_flags	= 0,
	पूर्ण;
	rpc_fraghdr marker = cpu_to_be32(RPC_LAST_STREAM_FRAGMENT |
					 (u32)xdr->len);
	अचिन्हित पूर्णांक sent = 0;
	पूर्णांक err;

	req->rq_xसमय = kसमय_get();
	err = xprt_sock_sendmsg(transport->sock, &msg, xdr, 0, marker, &sent);
	xdr_मुक्त_bvec(xdr);
	अगर (err < 0 || sent != (xdr->len + माप(marker)))
		वापस -EAGAIN;
	वापस sent;
पूर्ण

/**
 * bc_send_request - Send a backchannel Call on a TCP socket
 * @req: rpc_rqst containing Call message to be sent
 *
 * xpt_mutex ensures @rqstp's whole message is written to the socket
 * without पूर्णांकerruption.
 *
 * Return values:
 *   %0 अगर the message was sent successfully
 *   %ENOTCONN अगर the message was not sent
 */
अटल पूर्णांक bc_send_request(काष्ठा rpc_rqst *req)
अणु
	काष्ठा svc_xprt	*xprt;
	पूर्णांक len;

	/*
	 * Get the server socket associated with this callback xprt
	 */
	xprt = req->rq_xprt->bc_xprt;

	/*
	 * Grab the mutex to serialize data as the connection is shared
	 * with the क्रमe channel
	 */
	mutex_lock(&xprt->xpt_mutex);
	अगर (test_bit(XPT_DEAD, &xprt->xpt_flags))
		len = -ENOTCONN;
	अन्यथा
		len = bc_sendto(req);
	mutex_unlock(&xprt->xpt_mutex);

	अगर (len > 0)
		len = 0;

	वापस len;
पूर्ण

/*
 * The बंद routine. Since this is client initiated, we करो nothing
 */

अटल व्योम bc_बंद(काष्ठा rpc_xprt *xprt)
अणु
	xprt_disconnect_करोne(xprt);
पूर्ण

/*
 * The xprt destroy routine. Again, because this connection is client
 * initiated, we करो nothing
 */

अटल व्योम bc_destroy(काष्ठा rpc_xprt *xprt)
अणु
	dprपूर्णांकk("RPC:       bc_destroy xprt %p\n", xprt);

	xs_xprt_मुक्त(xprt);
	module_put(THIS_MODULE);
पूर्ण

अटल स्थिर काष्ठा rpc_xprt_ops xs_local_ops = अणु
	.reserve_xprt		= xprt_reserve_xprt,
	.release_xprt		= xprt_release_xprt,
	.alloc_slot		= xprt_alloc_slot,
	.मुक्त_slot		= xprt_मुक्त_slot,
	.rpcbind		= xs_local_rpcbind,
	.set_port		= xs_local_set_port,
	.connect		= xs_local_connect,
	.buf_alloc		= rpc_दो_स्मृति,
	.buf_मुक्त		= rpc_मुक्त,
	.prepare_request	= xs_stream_prepare_request,
	.send_request		= xs_local_send_request,
	.रुको_क्रम_reply_request	= xprt_रुको_क्रम_reply_request_def,
	.बंद			= xs_बंद,
	.destroy		= xs_destroy,
	.prपूर्णांक_stats		= xs_local_prपूर्णांक_stats,
	.enable_swap		= xs_enable_swap,
	.disable_swap		= xs_disable_swap,
पूर्ण;

अटल स्थिर काष्ठा rpc_xprt_ops xs_udp_ops = अणु
	.set_buffer_size	= xs_udp_set_buffer_size,
	.reserve_xprt		= xprt_reserve_xprt_cong,
	.release_xprt		= xprt_release_xprt_cong,
	.alloc_slot		= xprt_alloc_slot,
	.मुक्त_slot		= xprt_मुक्त_slot,
	.rpcbind		= rpcb_getport_async,
	.set_port		= xs_set_port,
	.connect		= xs_connect,
	.buf_alloc		= rpc_दो_स्मृति,
	.buf_मुक्त		= rpc_मुक्त,
	.send_request		= xs_udp_send_request,
	.रुको_क्रम_reply_request	= xprt_रुको_क्रम_reply_request_rtt,
	.समयr			= xs_udp_समयr,
	.release_request	= xprt_release_rqst_cong,
	.बंद			= xs_बंद,
	.destroy		= xs_destroy,
	.prपूर्णांक_stats		= xs_udp_prपूर्णांक_stats,
	.enable_swap		= xs_enable_swap,
	.disable_swap		= xs_disable_swap,
	.inject_disconnect	= xs_inject_disconnect,
पूर्ण;

अटल स्थिर काष्ठा rpc_xprt_ops xs_tcp_ops = अणु
	.reserve_xprt		= xprt_reserve_xprt,
	.release_xprt		= xprt_release_xprt,
	.alloc_slot		= xprt_alloc_slot,
	.मुक्त_slot		= xprt_मुक्त_slot,
	.rpcbind		= rpcb_getport_async,
	.set_port		= xs_set_port,
	.connect		= xs_connect,
	.buf_alloc		= rpc_दो_स्मृति,
	.buf_मुक्त		= rpc_मुक्त,
	.prepare_request	= xs_stream_prepare_request,
	.send_request		= xs_tcp_send_request,
	.रुको_क्रम_reply_request	= xprt_रुको_क्रम_reply_request_def,
	.बंद			= xs_tcp_shutकरोwn,
	.destroy		= xs_destroy,
	.set_connect_समयout	= xs_tcp_set_connect_समयout,
	.prपूर्णांक_stats		= xs_tcp_prपूर्णांक_stats,
	.enable_swap		= xs_enable_swap,
	.disable_swap		= xs_disable_swap,
	.inject_disconnect	= xs_inject_disconnect,
#अगर_घोषित CONFIG_SUNRPC_BACKCHANNEL
	.bc_setup		= xprt_setup_bc,
	.bc_maxpayload		= xs_tcp_bc_maxpayload,
	.bc_num_slots		= xprt_bc_max_slots,
	.bc_मुक्त_rqst		= xprt_मुक्त_bc_rqst,
	.bc_destroy		= xprt_destroy_bc,
#पूर्ण_अगर
पूर्ण;

/*
 * The rpc_xprt_ops क्रम the server backchannel
 */

अटल स्थिर काष्ठा rpc_xprt_ops bc_tcp_ops = अणु
	.reserve_xprt		= xprt_reserve_xprt,
	.release_xprt		= xprt_release_xprt,
	.alloc_slot		= xprt_alloc_slot,
	.मुक्त_slot		= xprt_मुक्त_slot,
	.buf_alloc		= bc_दो_स्मृति,
	.buf_मुक्त		= bc_मुक्त,
	.send_request		= bc_send_request,
	.रुको_क्रम_reply_request	= xprt_रुको_क्रम_reply_request_def,
	.बंद			= bc_बंद,
	.destroy		= bc_destroy,
	.prपूर्णांक_stats		= xs_tcp_prपूर्णांक_stats,
	.enable_swap		= xs_enable_swap,
	.disable_swap		= xs_disable_swap,
	.inject_disconnect	= xs_inject_disconnect,
पूर्ण;

अटल पूर्णांक xs_init_anyaddr(स्थिर पूर्णांक family, काष्ठा sockaddr *sap)
अणु
	अटल स्थिर काष्ठा sockaddr_in sin = अणु
		.sin_family		= AF_INET,
		.sin_addr.s_addr	= htonl(INADDR_ANY),
	पूर्ण;
	अटल स्थिर काष्ठा sockaddr_in6 sin6 = अणु
		.sin6_family		= AF_INET6,
		.sin6_addr		= IN6ADDR_ANY_INIT,
	पूर्ण;

	चयन (family) अणु
	हाल AF_LOCAL:
		अवरोध;
	हाल AF_INET:
		स_नकल(sap, &sin, माप(sin));
		अवरोध;
	हाल AF_INET6:
		स_नकल(sap, &sin6, माप(sin6));
		अवरोध;
	शेष:
		dprपूर्णांकk("RPC:       %s: Bad address family\n", __func__);
		वापस -EAFNOSUPPORT;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा rpc_xprt *xs_setup_xprt(काष्ठा xprt_create *args,
				      अचिन्हित पूर्णांक slot_table_size,
				      अचिन्हित पूर्णांक max_slot_table_size)
अणु
	काष्ठा rpc_xprt *xprt;
	काष्ठा sock_xprt *new;

	अगर (args->addrlen > माप(xprt->addr)) अणु
		dprपूर्णांकk("RPC:       xs_setup_xprt: address too large\n");
		वापस ERR_PTR(-EBADF);
	पूर्ण

	xprt = xprt_alloc(args->net, माप(*new), slot_table_size,
			max_slot_table_size);
	अगर (xprt == शून्य) अणु
		dprपूर्णांकk("RPC:       xs_setup_xprt: couldn't allocate "
				"rpc_xprt\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	new = container_of(xprt, काष्ठा sock_xprt, xprt);
	mutex_init(&new->recv_mutex);
	स_नकल(&xprt->addr, args->dstaddr, args->addrlen);
	xprt->addrlen = args->addrlen;
	अगर (args->srcaddr)
		स_नकल(&new->srcaddr, args->srcaddr, args->addrlen);
	अन्यथा अणु
		पूर्णांक err;
		err = xs_init_anyaddr(args->dstaddr->sa_family,
					(काष्ठा sockaddr *)&new->srcaddr);
		अगर (err != 0) अणु
			xprt_मुक्त(xprt);
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण

	वापस xprt;
पूर्ण

अटल स्थिर काष्ठा rpc_समयout xs_local_शेष_समयout = अणु
	.to_initval = 10 * HZ,
	.to_maxval = 10 * HZ,
	.to_retries = 2,
पूर्ण;

/**
 * xs_setup_local - Set up transport to use an AF_LOCAL socket
 * @args: rpc transport creation arguments
 *
 * AF_LOCAL is a "tpi_cots_ord" transport, just like TCP
 */
अटल काष्ठा rpc_xprt *xs_setup_local(काष्ठा xprt_create *args)
अणु
	काष्ठा sockaddr_un *sun = (काष्ठा sockaddr_un *)args->dstaddr;
	काष्ठा sock_xprt *transport;
	काष्ठा rpc_xprt *xprt;
	काष्ठा rpc_xprt *ret;

	xprt = xs_setup_xprt(args, xprt_tcp_slot_table_entries,
			xprt_max_tcp_slot_table_entries);
	अगर (IS_ERR(xprt))
		वापस xprt;
	transport = container_of(xprt, काष्ठा sock_xprt, xprt);

	xprt->prot = 0;
	xprt->max_payload = RPC_MAX_FRAGMENT_SIZE;

	xprt->bind_समयout = XS_BIND_TO;
	xprt->reestablish_समयout = XS_TCP_INIT_REEST_TO;
	xprt->idle_समयout = XS_IDLE_DISC_TO;

	xprt->ops = &xs_local_ops;
	xprt->समयout = &xs_local_शेष_समयout;

	INIT_WORK(&transport->recv_worker, xs_stream_data_receive_workfn);
	INIT_WORK(&transport->error_worker, xs_error_handle);
	INIT_DELAYED_WORK(&transport->connect_worker, xs_dummy_setup_socket);

	चयन (sun->sun_family) अणु
	हाल AF_LOCAL:
		अगर (sun->sun_path[0] != '/') अणु
			dprपूर्णांकk("RPC:       bad AF_LOCAL address: %s\n",
					sun->sun_path);
			ret = ERR_PTR(-EINVAL);
			जाओ out_err;
		पूर्ण
		xprt_set_bound(xprt);
		xs_क्रमmat_peer_addresses(xprt, "local", RPCBIND_NETID_LOCAL);
		ret = ERR_PTR(xs_local_setup_socket(transport));
		अगर (ret)
			जाओ out_err;
		अवरोध;
	शेष:
		ret = ERR_PTR(-EAFNOSUPPORT);
		जाओ out_err;
	पूर्ण

	dprपूर्णांकk("RPC:       set up xprt to %s via AF_LOCAL\n",
			xprt->address_strings[RPC_DISPLAY_ADDR]);

	अगर (try_module_get(THIS_MODULE))
		वापस xprt;
	ret = ERR_PTR(-EINVAL);
out_err:
	xs_xprt_मुक्त(xprt);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rpc_समयout xs_udp_शेष_समयout = अणु
	.to_initval = 5 * HZ,
	.to_maxval = 30 * HZ,
	.to_increment = 5 * HZ,
	.to_retries = 5,
पूर्ण;

/**
 * xs_setup_udp - Set up transport to use a UDP socket
 * @args: rpc transport creation arguments
 *
 */
अटल काष्ठा rpc_xprt *xs_setup_udp(काष्ठा xprt_create *args)
अणु
	काष्ठा sockaddr *addr = args->dstaddr;
	काष्ठा rpc_xprt *xprt;
	काष्ठा sock_xprt *transport;
	काष्ठा rpc_xprt *ret;

	xprt = xs_setup_xprt(args, xprt_udp_slot_table_entries,
			xprt_udp_slot_table_entries);
	अगर (IS_ERR(xprt))
		वापस xprt;
	transport = container_of(xprt, काष्ठा sock_xprt, xprt);

	xprt->prot = IPPROTO_UDP;
	/* XXX: header size can vary due to auth type, IPv6, etc. */
	xprt->max_payload = (1U << 16) - (MAX_HEADER << 3);

	xprt->bind_समयout = XS_BIND_TO;
	xprt->reestablish_समयout = XS_UDP_REEST_TO;
	xprt->idle_समयout = XS_IDLE_DISC_TO;

	xprt->ops = &xs_udp_ops;

	xprt->समयout = &xs_udp_शेष_समयout;

	INIT_WORK(&transport->recv_worker, xs_udp_data_receive_workfn);
	INIT_WORK(&transport->error_worker, xs_error_handle);
	INIT_DELAYED_WORK(&transport->connect_worker, xs_udp_setup_socket);

	चयन (addr->sa_family) अणु
	हाल AF_INET:
		अगर (((काष्ठा sockaddr_in *)addr)->sin_port != htons(0))
			xprt_set_bound(xprt);

		xs_क्रमmat_peer_addresses(xprt, "udp", RPCBIND_NETID_UDP);
		अवरोध;
	हाल AF_INET6:
		अगर (((काष्ठा sockaddr_in6 *)addr)->sin6_port != htons(0))
			xprt_set_bound(xprt);

		xs_क्रमmat_peer_addresses(xprt, "udp", RPCBIND_NETID_UDP6);
		अवरोध;
	शेष:
		ret = ERR_PTR(-EAFNOSUPPORT);
		जाओ out_err;
	पूर्ण

	अगर (xprt_bound(xprt))
		dprपूर्णांकk("RPC:       set up xprt to %s (port %s) via %s\n",
				xprt->address_strings[RPC_DISPLAY_ADDR],
				xprt->address_strings[RPC_DISPLAY_PORT],
				xprt->address_strings[RPC_DISPLAY_PROTO]);
	अन्यथा
		dprपूर्णांकk("RPC:       set up xprt to %s (autobind) via %s\n",
				xprt->address_strings[RPC_DISPLAY_ADDR],
				xprt->address_strings[RPC_DISPLAY_PROTO]);

	अगर (try_module_get(THIS_MODULE))
		वापस xprt;
	ret = ERR_PTR(-EINVAL);
out_err:
	xs_xprt_मुक्त(xprt);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा rpc_समयout xs_tcp_शेष_समयout = अणु
	.to_initval = 60 * HZ,
	.to_maxval = 60 * HZ,
	.to_retries = 2,
पूर्ण;

/**
 * xs_setup_tcp - Set up transport to use a TCP socket
 * @args: rpc transport creation arguments
 *
 */
अटल काष्ठा rpc_xprt *xs_setup_tcp(काष्ठा xprt_create *args)
अणु
	काष्ठा sockaddr *addr = args->dstaddr;
	काष्ठा rpc_xprt *xprt;
	काष्ठा sock_xprt *transport;
	काष्ठा rpc_xprt *ret;
	अचिन्हित पूर्णांक max_slot_table_size = xprt_max_tcp_slot_table_entries;

	अगर (args->flags & XPRT_CREATE_INFINITE_SLOTS)
		max_slot_table_size = RPC_MAX_SLOT_TABLE_LIMIT;

	xprt = xs_setup_xprt(args, xprt_tcp_slot_table_entries,
			max_slot_table_size);
	अगर (IS_ERR(xprt))
		वापस xprt;
	transport = container_of(xprt, काष्ठा sock_xprt, xprt);

	xprt->prot = IPPROTO_TCP;
	xprt->max_payload = RPC_MAX_FRAGMENT_SIZE;

	xprt->bind_समयout = XS_BIND_TO;
	xprt->reestablish_समयout = XS_TCP_INIT_REEST_TO;
	xprt->idle_समयout = XS_IDLE_DISC_TO;

	xprt->ops = &xs_tcp_ops;
	xprt->समयout = &xs_tcp_शेष_समयout;

	xprt->max_reconnect_समयout = xprt->समयout->to_maxval;
	xprt->connect_समयout = xprt->समयout->to_initval *
		(xprt->समयout->to_retries + 1);

	INIT_WORK(&transport->recv_worker, xs_stream_data_receive_workfn);
	INIT_WORK(&transport->error_worker, xs_error_handle);
	INIT_DELAYED_WORK(&transport->connect_worker, xs_tcp_setup_socket);

	चयन (addr->sa_family) अणु
	हाल AF_INET:
		अगर (((काष्ठा sockaddr_in *)addr)->sin_port != htons(0))
			xprt_set_bound(xprt);

		xs_क्रमmat_peer_addresses(xprt, "tcp", RPCBIND_NETID_TCP);
		अवरोध;
	हाल AF_INET6:
		अगर (((काष्ठा sockaddr_in6 *)addr)->sin6_port != htons(0))
			xprt_set_bound(xprt);

		xs_क्रमmat_peer_addresses(xprt, "tcp", RPCBIND_NETID_TCP6);
		अवरोध;
	शेष:
		ret = ERR_PTR(-EAFNOSUPPORT);
		जाओ out_err;
	पूर्ण

	अगर (xprt_bound(xprt))
		dprपूर्णांकk("RPC:       set up xprt to %s (port %s) via %s\n",
				xprt->address_strings[RPC_DISPLAY_ADDR],
				xprt->address_strings[RPC_DISPLAY_PORT],
				xprt->address_strings[RPC_DISPLAY_PROTO]);
	अन्यथा
		dprपूर्णांकk("RPC:       set up xprt to %s (autobind) via %s\n",
				xprt->address_strings[RPC_DISPLAY_ADDR],
				xprt->address_strings[RPC_DISPLAY_PROTO]);

	अगर (try_module_get(THIS_MODULE))
		वापस xprt;
	ret = ERR_PTR(-EINVAL);
out_err:
	xs_xprt_मुक्त(xprt);
	वापस ret;
पूर्ण

/**
 * xs_setup_bc_tcp - Set up transport to use a TCP backchannel socket
 * @args: rpc transport creation arguments
 *
 */
अटल काष्ठा rpc_xprt *xs_setup_bc_tcp(काष्ठा xprt_create *args)
अणु
	काष्ठा sockaddr *addr = args->dstaddr;
	काष्ठा rpc_xprt *xprt;
	काष्ठा sock_xprt *transport;
	काष्ठा svc_sock *bc_sock;
	काष्ठा rpc_xprt *ret;

	xprt = xs_setup_xprt(args, xprt_tcp_slot_table_entries,
			xprt_tcp_slot_table_entries);
	अगर (IS_ERR(xprt))
		वापस xprt;
	transport = container_of(xprt, काष्ठा sock_xprt, xprt);

	xprt->prot = IPPROTO_TCP;
	xprt->max_payload = RPC_MAX_FRAGMENT_SIZE;
	xprt->समयout = &xs_tcp_शेष_समयout;

	/* backchannel */
	xprt_set_bound(xprt);
	xprt->bind_समयout = 0;
	xprt->reestablish_समयout = 0;
	xprt->idle_समयout = 0;

	xprt->ops = &bc_tcp_ops;

	चयन (addr->sa_family) अणु
	हाल AF_INET:
		xs_क्रमmat_peer_addresses(xprt, "tcp",
					 RPCBIND_NETID_TCP);
		अवरोध;
	हाल AF_INET6:
		xs_क्रमmat_peer_addresses(xprt, "tcp",
				   RPCBIND_NETID_TCP6);
		अवरोध;
	शेष:
		ret = ERR_PTR(-EAFNOSUPPORT);
		जाओ out_err;
	पूर्ण

	dprपूर्णांकk("RPC:       set up xprt to %s (port %s) via %s\n",
			xprt->address_strings[RPC_DISPLAY_ADDR],
			xprt->address_strings[RPC_DISPLAY_PORT],
			xprt->address_strings[RPC_DISPLAY_PROTO]);

	/*
	 * Once we've associated a backchannel xprt with a connection,
	 * we want to keep it around as दीर्घ as the connection lasts,
	 * in हाल we need to start using it क्रम a backchannel again;
	 * this reference won't be dropped until bc_xprt is destroyed.
	 */
	xprt_get(xprt);
	args->bc_xprt->xpt_bc_xprt = xprt;
	xprt->bc_xprt = args->bc_xprt;
	bc_sock = container_of(args->bc_xprt, काष्ठा svc_sock, sk_xprt);
	transport->sock = bc_sock->sk_sock;
	transport->inet = bc_sock->sk_sk;

	/*
	 * Since we करोn't want connections क्रम the backchannel, we set
	 * the xprt status to connected
	 */
	xprt_set_connected(xprt);

	अगर (try_module_get(THIS_MODULE))
		वापस xprt;

	args->bc_xprt->xpt_bc_xprt = शून्य;
	args->bc_xprt->xpt_bc_xps = शून्य;
	xprt_put(xprt);
	ret = ERR_PTR(-EINVAL);
out_err:
	xs_xprt_मुक्त(xprt);
	वापस ret;
पूर्ण

अटल काष्ठा xprt_class	xs_local_transport = अणु
	.list		= LIST_HEAD_INIT(xs_local_transport.list),
	.name		= "named UNIX socket",
	.owner		= THIS_MODULE,
	.ident		= XPRT_TRANSPORT_LOCAL,
	.setup		= xs_setup_local,
	.netid		= अणु "" पूर्ण,
पूर्ण;

अटल काष्ठा xprt_class	xs_udp_transport = अणु
	.list		= LIST_HEAD_INIT(xs_udp_transport.list),
	.name		= "udp",
	.owner		= THIS_MODULE,
	.ident		= XPRT_TRANSPORT_UDP,
	.setup		= xs_setup_udp,
	.netid		= अणु "udp", "udp6", "" पूर्ण,
पूर्ण;

अटल काष्ठा xprt_class	xs_tcp_transport = अणु
	.list		= LIST_HEAD_INIT(xs_tcp_transport.list),
	.name		= "tcp",
	.owner		= THIS_MODULE,
	.ident		= XPRT_TRANSPORT_TCP,
	.setup		= xs_setup_tcp,
	.netid		= अणु "tcp", "tcp6", "" पूर्ण,
पूर्ण;

अटल काष्ठा xprt_class	xs_bc_tcp_transport = अणु
	.list		= LIST_HEAD_INIT(xs_bc_tcp_transport.list),
	.name		= "tcp NFSv4.1 backchannel",
	.owner		= THIS_MODULE,
	.ident		= XPRT_TRANSPORT_BC_TCP,
	.setup		= xs_setup_bc_tcp,
	.netid		= अणु "" पूर्ण,
पूर्ण;

/**
 * init_socket_xprt - set up xprtsock's sysctls, रेजिस्टर with RPC client
 *
 */
पूर्णांक init_socket_xprt(व्योम)
अणु
	अगर (!sunrpc_table_header)
		sunrpc_table_header = रेजिस्टर_sysctl_table(sunrpc_table);

	xprt_रेजिस्टर_transport(&xs_local_transport);
	xprt_रेजिस्टर_transport(&xs_udp_transport);
	xprt_रेजिस्टर_transport(&xs_tcp_transport);
	xprt_रेजिस्टर_transport(&xs_bc_tcp_transport);

	वापस 0;
पूर्ण

/**
 * cleanup_socket_xprt - हटाओ xprtsock's sysctls, unरेजिस्टर
 *
 */
व्योम cleanup_socket_xprt(व्योम)
अणु
	अगर (sunrpc_table_header) अणु
		unरेजिस्टर_sysctl_table(sunrpc_table_header);
		sunrpc_table_header = शून्य;
	पूर्ण

	xprt_unरेजिस्टर_transport(&xs_local_transport);
	xprt_unरेजिस्टर_transport(&xs_udp_transport);
	xprt_unरेजिस्टर_transport(&xs_tcp_transport);
	xprt_unरेजिस्टर_transport(&xs_bc_tcp_transport);
पूर्ण

अटल पूर्णांक param_set_uपूर्णांक_minmax(स्थिर अक्षर *val,
		स्थिर काष्ठा kernel_param *kp,
		अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max)
अणु
	अचिन्हित पूर्णांक num;
	पूर्णांक ret;

	अगर (!val)
		वापस -EINVAL;
	ret = kstrtouपूर्णांक(val, 0, &num);
	अगर (ret)
		वापस ret;
	अगर (num < min || num > max)
		वापस -EINVAL;
	*((अचिन्हित पूर्णांक *)kp->arg) = num;
	वापस 0;
पूर्ण

अटल पूर्णांक param_set_portnr(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस param_set_uपूर्णांक_minmax(val, kp,
			RPC_MIN_RESVPORT,
			RPC_MAX_RESVPORT);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_portnr = अणु
	.set = param_set_portnr,
	.get = param_get_uपूर्णांक,
पूर्ण;

#घोषणा param_check_portnr(name, p) \
	__param_check(name, p, अचिन्हित पूर्णांक);

module_param_named(min_resvport, xprt_min_resvport, portnr, 0644);
module_param_named(max_resvport, xprt_max_resvport, portnr, 0644);

अटल पूर्णांक param_set_slot_table_size(स्थिर अक्षर *val,
				     स्थिर काष्ठा kernel_param *kp)
अणु
	वापस param_set_uपूर्णांक_minmax(val, kp,
			RPC_MIN_SLOT_TABLE,
			RPC_MAX_SLOT_TABLE);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_slot_table_size = अणु
	.set = param_set_slot_table_size,
	.get = param_get_uपूर्णांक,
पूर्ण;

#घोषणा param_check_slot_table_size(name, p) \
	__param_check(name, p, अचिन्हित पूर्णांक);

अटल पूर्णांक param_set_max_slot_table_size(स्थिर अक्षर *val,
				     स्थिर काष्ठा kernel_param *kp)
अणु
	वापस param_set_uपूर्णांक_minmax(val, kp,
			RPC_MIN_SLOT_TABLE,
			RPC_MAX_SLOT_TABLE_LIMIT);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_max_slot_table_size = अणु
	.set = param_set_max_slot_table_size,
	.get = param_get_uपूर्णांक,
पूर्ण;

#घोषणा param_check_max_slot_table_size(name, p) \
	__param_check(name, p, अचिन्हित पूर्णांक);

module_param_named(tcp_slot_table_entries, xprt_tcp_slot_table_entries,
		   slot_table_size, 0644);
module_param_named(tcp_max_slot_table_entries, xprt_max_tcp_slot_table_entries,
		   max_slot_table_size, 0644);
module_param_named(udp_slot_table_entries, xprt_udp_slot_table_entries,
		   slot_table_size, 0644);
