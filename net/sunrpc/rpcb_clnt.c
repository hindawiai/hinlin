<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * In-kernel rpcbind client supporting versions 2, 3, and 4 of the rpcbind
 * protocol
 *
 * Based on RFC 1833: "Binding Protocols for ONC RPC Version 2" and
 * RFC 3530: "Network File System (NFS) version 4 Protocol"
 *
 * Original: Gilles Quillard, Bull Open Source, 2005 <gilles.quillard@bull.net>
 * Updated: Chuck Lever, Oracle Corporation, 2007 <chuck.lever@oracle.com>
 *
 * Descended from net/sunrpc/pmap_clnt.c,
 *  Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/module.h>

#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/un.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <net/ipv6.h>

#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/xprtsock.h>

#समावेश <trace/events/sunrpc.h>

#समावेश "netns.h"

#घोषणा RPCBIND_SOCK_PATHNAME	"/var/run/rpcbind.sock"

#घोषणा RPCBIND_PROGRAM		(100000u)
#घोषणा RPCBIND_PORT		(111u)

#घोषणा RPCBVERS_2		(2u)
#घोषणा RPCBVERS_3		(3u)
#घोषणा RPCBVERS_4		(4u)

क्रमागत अणु
	RPCBPROC_शून्य,
	RPCBPROC_SET,
	RPCBPROC_UNSET,
	RPCBPROC_GETPORT,
	RPCBPROC_GETADDR = 3,		/* alias क्रम GETPORT */
	RPCBPROC_DUMP,
	RPCBPROC_CALLIT,
	RPCBPROC_BCAST = 5,		/* alias क्रम CALLIT */
	RPCBPROC_GETTIME,
	RPCBPROC_UADDR2TADDR,
	RPCBPROC_TADDR2UADDR,
	RPCBPROC_GETVERSADDR,
	RPCBPROC_INसूचीECT,
	RPCBPROC_GETADDRLIST,
	RPCBPROC_GETSTAT,
पूर्ण;

/*
 * r_owner
 *
 * The "owner" is allowed to unset a service in the rpcbind database.
 *
 * For AF_LOCAL SET/UNSET requests, rpcbind treats this string as a
 * UID which it maps to a local user name via a password lookup.
 * In all other हालs it is ignored.
 *
 * For SET/UNSET requests, user space provides a value, even क्रम
 * network requests, and GETADDR uses an empty string.  We follow
 * those precedents here.
 */
#घोषणा RPCB_OWNER_STRING	"0"
#घोषणा RPCB_MAXOWNERLEN	माप(RPCB_OWNER_STRING)

/*
 * XDR data type sizes
 */
#घोषणा RPCB_program_sz		(1)
#घोषणा RPCB_version_sz		(1)
#घोषणा RPCB_protocol_sz	(1)
#घोषणा RPCB_port_sz		(1)
#घोषणा RPCB_boolean_sz		(1)

#घोषणा RPCB_netid_sz		(1 + XDR_QUADLEN(RPCBIND_MAXNETIDLEN))
#घोषणा RPCB_addr_sz		(1 + XDR_QUADLEN(RPCBIND_MAXUADDRLEN))
#घोषणा RPCB_ownerstring_sz	(1 + XDR_QUADLEN(RPCB_MAXOWNERLEN))

/*
 * XDR argument and result sizes
 */
#घोषणा RPCB_mappingargs_sz	(RPCB_program_sz + RPCB_version_sz + \
				RPCB_protocol_sz + RPCB_port_sz)
#घोषणा RPCB_getaddrargs_sz	(RPCB_program_sz + RPCB_version_sz + \
				RPCB_netid_sz + RPCB_addr_sz + \
				RPCB_ownerstring_sz)

#घोषणा RPCB_getportres_sz	RPCB_port_sz
#घोषणा RPCB_setres_sz		RPCB_boolean_sz

/*
 * Note that RFC 1833 करोes not put any size restrictions on the
 * address string वापसed by the remote rpcbind database.
 */
#घोषणा RPCB_getaddrres_sz	RPCB_addr_sz

अटल व्योम			rpcb_getport_करोne(काष्ठा rpc_task *, व्योम *);
अटल व्योम			rpcb_map_release(व्योम *data);
अटल स्थिर काष्ठा rpc_program	rpcb_program;

काष्ठा rpcbind_args अणु
	काष्ठा rpc_xprt *	r_xprt;

	u32			r_prog;
	u32			r_vers;
	u32			r_prot;
	अचिन्हित लघु		r_port;
	स्थिर अक्षर *		r_netid;
	स्थिर अक्षर *		r_addr;
	स्थिर अक्षर *		r_owner;

	पूर्णांक			r_status;
पूर्ण;

अटल स्थिर काष्ठा rpc_procinfo rpcb_procedures2[];
अटल स्थिर काष्ठा rpc_procinfo rpcb_procedures3[];
अटल स्थिर काष्ठा rpc_procinfo rpcb_procedures4[];

काष्ठा rpcb_info अणु
	u32			rpc_vers;
	स्थिर काष्ठा rpc_procinfo *rpc_proc;
पूर्ण;

अटल स्थिर काष्ठा rpcb_info rpcb_next_version[];
अटल स्थिर काष्ठा rpcb_info rpcb_next_version6[];

अटल स्थिर काष्ठा rpc_call_ops rpcb_getport_ops = अणु
	.rpc_call_करोne		= rpcb_getport_करोne,
	.rpc_release		= rpcb_map_release,
पूर्ण;

अटल व्योम rpcb_wake_rpcbind_रुकोers(काष्ठा rpc_xprt *xprt, पूर्णांक status)
अणु
	xprt_clear_binding(xprt);
	rpc_wake_up_status(&xprt->binding, status);
पूर्ण

अटल व्योम rpcb_map_release(व्योम *data)
अणु
	काष्ठा rpcbind_args *map = data;

	rpcb_wake_rpcbind_रुकोers(map->r_xprt, map->r_status);
	xprt_put(map->r_xprt);
	kमुक्त(map->r_addr);
	kमुक्त(map);
पूर्ण

अटल पूर्णांक rpcb_get_local(काष्ठा net *net)
अणु
	पूर्णांक cnt;
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	spin_lock(&sn->rpcb_clnt_lock);
	अगर (sn->rpcb_users)
		sn->rpcb_users++;
	cnt = sn->rpcb_users;
	spin_unlock(&sn->rpcb_clnt_lock);

	वापस cnt;
पूर्ण

व्योम rpcb_put_local(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा rpc_clnt *clnt = sn->rpcb_local_clnt;
	काष्ठा rpc_clnt *clnt4 = sn->rpcb_local_clnt4;
	पूर्णांक shutकरोwn = 0;

	spin_lock(&sn->rpcb_clnt_lock);
	अगर (sn->rpcb_users) अणु
		अगर (--sn->rpcb_users == 0) अणु
			sn->rpcb_local_clnt = शून्य;
			sn->rpcb_local_clnt4 = शून्य;
		पूर्ण
		shutकरोwn = !sn->rpcb_users;
	पूर्ण
	spin_unlock(&sn->rpcb_clnt_lock);

	अगर (shutकरोwn) अणु
		/*
		 * cleanup_rpcb_clnt - हटाओ xprtsock's sysctls, unरेजिस्टर
		 */
		अगर (clnt4)
			rpc_shutकरोwn_client(clnt4);
		अगर (clnt)
			rpc_shutकरोwn_client(clnt);
	पूर्ण
पूर्ण

अटल व्योम rpcb_set_local(काष्ठा net *net, काष्ठा rpc_clnt *clnt,
			काष्ठा rpc_clnt *clnt4,
			bool is_af_local)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	/* Protected by rpcb_create_local_mutex */
	sn->rpcb_local_clnt = clnt;
	sn->rpcb_local_clnt4 = clnt4;
	sn->rpcb_is_af_local = is_af_local ? 1 : 0;
	smp_wmb();
	sn->rpcb_users = 1;
पूर्ण

/*
 * Returns zero on success, otherwise a negative त्रुटि_सं value
 * is वापसed.
 */
अटल पूर्णांक rpcb_create_local_unix(काष्ठा net *net)
अणु
	अटल स्थिर काष्ठा sockaddr_un rpcb_localaddr_rpcbind = अणु
		.sun_family		= AF_LOCAL,
		.sun_path		= RPCBIND_SOCK_PATHNAME,
	पूर्ण;
	काष्ठा rpc_create_args args = अणु
		.net		= net,
		.protocol	= XPRT_TRANSPORT_LOCAL,
		.address	= (काष्ठा sockaddr *)&rpcb_localaddr_rpcbind,
		.addrsize	= माप(rpcb_localaddr_rpcbind),
		.servername	= "localhost",
		.program	= &rpcb_program,
		.version	= RPCBVERS_2,
		.authflavor	= RPC_AUTH_शून्य,
		.cred		= current_cred(),
		/*
		 * We turn off the idle समयout to prevent the kernel
		 * from स्वतःmatically disconnecting the socket.
		 * Otherwise, we'd have to cache the mount namespace
		 * of the caller and somehow pass that to the socket
		 * reconnect code.
		 */
		.flags		= RPC_CLNT_CREATE_NO_IDLE_TIMEOUT,
	पूर्ण;
	काष्ठा rpc_clnt *clnt, *clnt4;
	पूर्णांक result = 0;

	/*
	 * Because we requested an RPC PING at transport creation समय,
	 * this works only अगर the user space porपंचांगapper is rpcbind, and
	 * it's listening on AF_LOCAL on the named socket.
	 */
	clnt = rpc_create(&args);
	अगर (IS_ERR(clnt)) अणु
		result = PTR_ERR(clnt);
		जाओ out;
	पूर्ण

	clnt4 = rpc_bind_new_program(clnt, &rpcb_program, RPCBVERS_4);
	अगर (IS_ERR(clnt4))
		clnt4 = शून्य;

	rpcb_set_local(net, clnt, clnt4, true);

out:
	वापस result;
पूर्ण

/*
 * Returns zero on success, otherwise a negative त्रुटि_सं value
 * is वापसed.
 */
अटल पूर्णांक rpcb_create_local_net(काष्ठा net *net)
अणु
	अटल स्थिर काष्ठा sockaddr_in rpcb_inaddr_loopback = अणु
		.sin_family		= AF_INET,
		.sin_addr.s_addr	= htonl(INADDR_LOOPBACK),
		.sin_port		= htons(RPCBIND_PORT),
	पूर्ण;
	काष्ठा rpc_create_args args = अणु
		.net		= net,
		.protocol	= XPRT_TRANSPORT_TCP,
		.address	= (काष्ठा sockaddr *)&rpcb_inaddr_loopback,
		.addrsize	= माप(rpcb_inaddr_loopback),
		.servername	= "localhost",
		.program	= &rpcb_program,
		.version	= RPCBVERS_2,
		.authflavor	= RPC_AUTH_UNIX,
		.cred		= current_cred(),
		.flags		= RPC_CLNT_CREATE_NOPING,
	पूर्ण;
	काष्ठा rpc_clnt *clnt, *clnt4;
	पूर्णांक result = 0;

	clnt = rpc_create(&args);
	अगर (IS_ERR(clnt)) अणु
		result = PTR_ERR(clnt);
		जाओ out;
	पूर्ण

	/*
	 * This results in an RPC ping.  On प्रणालीs running porपंचांगapper,
	 * the v4 ping will fail.  Proceed anyway, but disallow rpcb
	 * v4 upcalls.
	 */
	clnt4 = rpc_bind_new_program(clnt, &rpcb_program, RPCBVERS_4);
	अगर (IS_ERR(clnt4))
		clnt4 = शून्य;

	rpcb_set_local(net, clnt, clnt4, false);

out:
	वापस result;
पूर्ण

/*
 * Returns zero on success, otherwise a negative त्रुटि_सं value
 * is वापसed.
 */
पूर्णांक rpcb_create_local(काष्ठा net *net)
अणु
	अटल DEFINE_MUTEX(rpcb_create_local_mutex);
	पूर्णांक result = 0;

	अगर (rpcb_get_local(net))
		वापस result;

	mutex_lock(&rpcb_create_local_mutex);
	अगर (rpcb_get_local(net))
		जाओ out;

	अगर (rpcb_create_local_unix(net) != 0)
		result = rpcb_create_local_net(net);

out:
	mutex_unlock(&rpcb_create_local_mutex);
	वापस result;
पूर्ण

अटल काष्ठा rpc_clnt *rpcb_create(काष्ठा net *net, स्थिर अक्षर *nodename,
				    स्थिर अक्षर *hostname,
				    काष्ठा sockaddr *srvaddr, माप_प्रकार salen,
				    पूर्णांक proto, u32 version,
				    स्थिर काष्ठा cred *cred,
				    स्थिर काष्ठा rpc_समयout *समयo)
अणु
	काष्ठा rpc_create_args args = अणु
		.net		= net,
		.protocol	= proto,
		.address	= srvaddr,
		.addrsize	= salen,
		.समयout	= समयo,
		.servername	= hostname,
		.nodename	= nodename,
		.program	= &rpcb_program,
		.version	= version,
		.authflavor	= RPC_AUTH_UNIX,
		.cred		= cred,
		.flags		= (RPC_CLNT_CREATE_NOPING |
					RPC_CLNT_CREATE_NONPRIVPORT),
	पूर्ण;

	चयन (srvaddr->sa_family) अणु
	हाल AF_INET:
		((काष्ठा sockaddr_in *)srvaddr)->sin_port = htons(RPCBIND_PORT);
		अवरोध;
	हाल AF_INET6:
		((काष्ठा sockaddr_in6 *)srvaddr)->sin6_port = htons(RPCBIND_PORT);
		अवरोध;
	शेष:
		वापस ERR_PTR(-EAFNOSUPPORT);
	पूर्ण

	वापस rpc_create(&args);
पूर्ण

अटल पूर्णांक rpcb_रेजिस्टर_call(काष्ठा sunrpc_net *sn, काष्ठा rpc_clnt *clnt, काष्ठा rpc_message *msg, bool is_set)
अणु
	पूर्णांक flags = RPC_TASK_NOCONNECT;
	पूर्णांक error, result = 0;

	अगर (is_set || !sn->rpcb_is_af_local)
		flags = RPC_TASK_SOFTCONN;
	msg->rpc_resp = &result;

	error = rpc_call_sync(clnt, msg, flags);
	अगर (error < 0)
		वापस error;

	अगर (!result)
		वापस -EACCES;
	वापस 0;
पूर्ण

/**
 * rpcb_रेजिस्टर - set or unset a port registration with the local rpcbind svc
 * @net: target network namespace
 * @prog: RPC program number to bind
 * @vers: RPC version number to bind
 * @prot: transport protocol to रेजिस्टर
 * @port: port value to रेजिस्टर
 *
 * Returns zero अगर the registration request was dispatched successfully
 * and the rpcbind daemon वापसed success.  Otherwise, वापसs an त्रुटि_सं
 * value that reflects the nature of the error (request could not be
 * dispatched, समयd out, or rpcbind वापसed an error).
 *
 * RPC services invoke this function to advertise their contact
 * inक्रमmation via the प्रणाली's rpcbind daemon.  RPC services
 * invoke this function once क्रम each [program, version, transport]
 * tuple they wish to advertise.
 *
 * Callers may also unरेजिस्टर RPC services that are no दीर्घer
 * available by setting the passed-in port to zero.  This हटाओs
 * all रेजिस्टरed transports क्रम [program, version] from the local
 * rpcbind database.
 *
 * This function uses rpcbind protocol version 2 to contact the
 * local rpcbind daemon.
 *
 * Registration works over both AF_INET and AF_INET6, and services
 * रेजिस्टरed via this function are advertised as available क्रम any
 * address.  If the local rpcbind daemon is listening on AF_INET6,
 * services रेजिस्टरed via this function will be advertised on
 * IN6ADDR_ANY (ie available क्रम all AF_INET and AF_INET6
 * addresses).
 */
पूर्णांक rpcb_रेजिस्टर(काष्ठा net *net, u32 prog, u32 vers, पूर्णांक prot, अचिन्हित लघु port)
अणु
	काष्ठा rpcbind_args map = अणु
		.r_prog		= prog,
		.r_vers		= vers,
		.r_prot		= prot,
		.r_port		= port,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_argp	= &map,
	पूर्ण;
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	bool is_set = false;

	trace_pmap_रेजिस्टर(prog, vers, prot, port);

	msg.rpc_proc = &rpcb_procedures2[RPCBPROC_UNSET];
	अगर (port != 0) अणु
		msg.rpc_proc = &rpcb_procedures2[RPCBPROC_SET];
		is_set = true;
	पूर्ण

	वापस rpcb_रेजिस्टर_call(sn, sn->rpcb_local_clnt, &msg, is_set);
पूर्ण

/*
 * Fill in AF_INET family-specअगरic arguments to रेजिस्टर
 */
अटल पूर्णांक rpcb_रेजिस्टर_inet4(काष्ठा sunrpc_net *sn,
			       स्थिर काष्ठा sockaddr *sap,
			       काष्ठा rpc_message *msg)
अणु
	स्थिर काष्ठा sockaddr_in *sin = (स्थिर काष्ठा sockaddr_in *)sap;
	काष्ठा rpcbind_args *map = msg->rpc_argp;
	अचिन्हित लघु port = ntohs(sin->sin_port);
	bool is_set = false;
	पूर्णांक result;

	map->r_addr = rpc_sockaddr2uaddr(sap, GFP_KERNEL);

	msg->rpc_proc = &rpcb_procedures4[RPCBPROC_UNSET];
	अगर (port != 0) अणु
		msg->rpc_proc = &rpcb_procedures4[RPCBPROC_SET];
		is_set = true;
	पूर्ण

	result = rpcb_रेजिस्टर_call(sn, sn->rpcb_local_clnt4, msg, is_set);
	kमुक्त(map->r_addr);
	वापस result;
पूर्ण

/*
 * Fill in AF_INET6 family-specअगरic arguments to रेजिस्टर
 */
अटल पूर्णांक rpcb_रेजिस्टर_inet6(काष्ठा sunrpc_net *sn,
			       स्थिर काष्ठा sockaddr *sap,
			       काष्ठा rpc_message *msg)
अणु
	स्थिर काष्ठा sockaddr_in6 *sin6 = (स्थिर काष्ठा sockaddr_in6 *)sap;
	काष्ठा rpcbind_args *map = msg->rpc_argp;
	अचिन्हित लघु port = ntohs(sin6->sin6_port);
	bool is_set = false;
	पूर्णांक result;

	map->r_addr = rpc_sockaddr2uaddr(sap, GFP_KERNEL);

	msg->rpc_proc = &rpcb_procedures4[RPCBPROC_UNSET];
	अगर (port != 0) अणु
		msg->rpc_proc = &rpcb_procedures4[RPCBPROC_SET];
		is_set = true;
	पूर्ण

	result = rpcb_रेजिस्टर_call(sn, sn->rpcb_local_clnt4, msg, is_set);
	kमुक्त(map->r_addr);
	वापस result;
पूर्ण

अटल पूर्णांक rpcb_unरेजिस्टर_all_protofamilies(काष्ठा sunrpc_net *sn,
					     काष्ठा rpc_message *msg)
अणु
	काष्ठा rpcbind_args *map = msg->rpc_argp;

	trace_rpcb_unरेजिस्टर(map->r_prog, map->r_vers, map->r_netid);

	map->r_addr = "";
	msg->rpc_proc = &rpcb_procedures4[RPCBPROC_UNSET];

	वापस rpcb_रेजिस्टर_call(sn, sn->rpcb_local_clnt4, msg, false);
पूर्ण

/**
 * rpcb_v4_रेजिस्टर - set or unset a port registration with the local rpcbind
 * @net: target network namespace
 * @program: RPC program number of service to (un)रेजिस्टर
 * @version: RPC version number of service to (un)रेजिस्टर
 * @address: address family, IP address, and port to (un)रेजिस्टर
 * @netid: netid of transport protocol to (un)रेजिस्टर
 *
 * Returns zero अगर the registration request was dispatched successfully
 * and the rpcbind daemon वापसed success.  Otherwise, वापसs an त्रुटि_सं
 * value that reflects the nature of the error (request could not be
 * dispatched, समयd out, or rpcbind वापसed an error).
 *
 * RPC services invoke this function to advertise their contact
 * inक्रमmation via the प्रणाली's rpcbind daemon.  RPC services
 * invoke this function once क्रम each [program, version, address,
 * netid] tuple they wish to advertise.
 *
 * Callers may also unरेजिस्टर RPC services that are रेजिस्टरed at a
 * specअगरic address by setting the port number in @address to zero.
 * They may unरेजिस्टर all रेजिस्टरed protocol families at once क्रम
 * a service by passing a शून्य @address argument.  If @netid is ""
 * then all netids क्रम [program, version, address] are unरेजिस्टरed.
 *
 * This function uses rpcbind protocol version 4 to contact the
 * local rpcbind daemon.  The local rpcbind daemon must support
 * version 4 of the rpcbind protocol in order क्रम these functions
 * to रेजिस्टर a service successfully.
 *
 * Supported netids include "udp" and "tcp" क्रम UDP and TCP over
 * IPv4, and "udp6" and "tcp6" क्रम UDP and TCP over IPv6,
 * respectively.
 *
 * The contents of @address determine the address family and the
 * port to be रेजिस्टरed.  The usual practice is to pass INADDR_ANY
 * as the raw address, but specअगरying a non-zero address is also
 * supported by this API अगर the caller wishes to advertise an RPC
 * service on a specअगरic network पूर्णांकerface.
 *
 * Note that passing in INADDR_ANY करोes not create the same service
 * registration as IN6ADDR_ANY.  The क्रमmer advertises an RPC
 * service on any IPv4 address, but not on IPv6.  The latter
 * advertises the service on all IPv4 and IPv6 addresses.
 */
पूर्णांक rpcb_v4_रेजिस्टर(काष्ठा net *net, स्थिर u32 program, स्थिर u32 version,
		     स्थिर काष्ठा sockaddr *address, स्थिर अक्षर *netid)
अणु
	काष्ठा rpcbind_args map = अणु
		.r_prog		= program,
		.r_vers		= version,
		.r_netid	= netid,
		.r_owner	= RPCB_OWNER_STRING,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_argp	= &map,
	पूर्ण;
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	अगर (sn->rpcb_local_clnt4 == शून्य)
		वापस -EPROTONOSUPPORT;

	अगर (address == शून्य)
		वापस rpcb_unरेजिस्टर_all_protofamilies(sn, &msg);

	trace_rpcb_रेजिस्टर(map.r_prog, map.r_vers, map.r_addr, map.r_netid);

	चयन (address->sa_family) अणु
	हाल AF_INET:
		वापस rpcb_रेजिस्टर_inet4(sn, address, &msg);
	हाल AF_INET6:
		वापस rpcb_रेजिस्टर_inet6(sn, address, &msg);
	पूर्ण

	वापस -EAFNOSUPPORT;
पूर्ण

अटल काष्ठा rpc_task *rpcb_call_async(काष्ठा rpc_clnt *rpcb_clnt,
		काष्ठा rpcbind_args *map, स्थिर काष्ठा rpc_procinfo *proc)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = proc,
		.rpc_argp = map,
		.rpc_resp = map,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = rpcb_clnt,
		.rpc_message = &msg,
		.callback_ops = &rpcb_getport_ops,
		.callback_data = map,
		.flags = RPC_TASK_ASYNC | RPC_TASK_SOFTCONN,
	पूर्ण;

	वापस rpc_run_task(&task_setup_data);
पूर्ण

/*
 * In the हाल where rpc clients have been cloned, we want to make
 * sure that we use the program number/version etc of the actual
 * owner of the xprt. To करो so, we walk back up the tree of parents
 * to find whoever created the transport and/or whoever has the
 * स्वतःbind flag set.
 */
अटल काष्ठा rpc_clnt *rpcb_find_transport_owner(काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा rpc_clnt *parent = clnt->cl_parent;
	काष्ठा rpc_xprt_चयन *xps = rcu_access_poपूर्णांकer(clnt->cl_xpi.xpi_xpचयन);

	जबतक (parent != clnt) अणु
		अगर (rcu_access_poपूर्णांकer(parent->cl_xpi.xpi_xpचयन) != xps)
			अवरोध;
		अगर (clnt->cl_स्वतःbind)
			अवरोध;
		clnt = parent;
		parent = parent->cl_parent;
	पूर्ण
	वापस clnt;
पूर्ण

/**
 * rpcb_getport_async - obtain the port क्रम a given RPC service on a given host
 * @task: task that is रुकोing क्रम porपंचांगapper request
 *
 * This one can be called क्रम an ongoing RPC request, and can be used in
 * an async (rpciod) context.
 */
व्योम rpcb_getport_async(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_clnt *clnt;
	स्थिर काष्ठा rpc_procinfo *proc;
	u32 bind_version;
	काष्ठा rpc_xprt *xprt;
	काष्ठा rpc_clnt	*rpcb_clnt;
	काष्ठा rpcbind_args *map;
	काष्ठा rpc_task	*child;
	काष्ठा sockaddr_storage addr;
	काष्ठा sockaddr *sap = (काष्ठा sockaddr *)&addr;
	माप_प्रकार salen;
	पूर्णांक status;

	rcu_पढ़ो_lock();
	clnt = rpcb_find_transport_owner(task->tk_client);
	rcu_पढ़ो_unlock();
	xprt = xprt_get(task->tk_xprt);

	/* Put self on the रुको queue to ensure we get notअगरied अगर
	 * some other task is alपढ़ोy attempting to bind the port */
	rpc_sleep_on_समयout(&xprt->binding, task,
			शून्य, jअगरfies + xprt->bind_समयout);

	अगर (xprt_test_and_set_binding(xprt)) अणु
		xprt_put(xprt);
		वापस;
	पूर्ण

	/* Someone अन्यथा may have bound अगर we slept */
	अगर (xprt_bound(xprt)) अणु
		status = 0;
		जाओ bailout_noमुक्त;
	पूर्ण

	/* Parent transport's destination address */
	salen = rpc_peeraddr(clnt, sap, माप(addr));

	/* Don't ever use rpcbind v2 क्रम AF_INET6 requests */
	चयन (sap->sa_family) अणु
	हाल AF_INET:
		proc = rpcb_next_version[xprt->bind_index].rpc_proc;
		bind_version = rpcb_next_version[xprt->bind_index].rpc_vers;
		अवरोध;
	हाल AF_INET6:
		proc = rpcb_next_version6[xprt->bind_index].rpc_proc;
		bind_version = rpcb_next_version6[xprt->bind_index].rpc_vers;
		अवरोध;
	शेष:
		status = -EAFNOSUPPORT;
		जाओ bailout_noमुक्त;
	पूर्ण
	अगर (proc == शून्य) अणु
		xprt->bind_index = 0;
		status = -EPFNOSUPPORT;
		जाओ bailout_noमुक्त;
	पूर्ण

	trace_rpcb_getport(clnt, task, bind_version);

	rpcb_clnt = rpcb_create(xprt->xprt_net,
				clnt->cl_nodename,
				xprt->servername, sap, salen,
				xprt->prot, bind_version,
				clnt->cl_cred,
				task->tk_client->cl_समयout);
	अगर (IS_ERR(rpcb_clnt)) अणु
		status = PTR_ERR(rpcb_clnt);
		जाओ bailout_noमुक्त;
	पूर्ण

	map = kzalloc(माप(काष्ठा rpcbind_args), GFP_NOFS);
	अगर (!map) अणु
		status = -ENOMEM;
		जाओ bailout_release_client;
	पूर्ण
	map->r_prog = clnt->cl_prog;
	map->r_vers = clnt->cl_vers;
	map->r_prot = xprt->prot;
	map->r_port = 0;
	map->r_xprt = xprt;
	map->r_status = -EIO;

	चयन (bind_version) अणु
	हाल RPCBVERS_4:
	हाल RPCBVERS_3:
		map->r_netid = xprt->address_strings[RPC_DISPLAY_NETID];
		map->r_addr = rpc_sockaddr2uaddr(sap, GFP_NOFS);
		अगर (!map->r_addr) अणु
			status = -ENOMEM;
			जाओ bailout_मुक्त_args;
		पूर्ण
		map->r_owner = "";
		अवरोध;
	हाल RPCBVERS_2:
		map->r_addr = शून्य;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	child = rpcb_call_async(rpcb_clnt, map, proc);
	rpc_release_client(rpcb_clnt);

	xprt->stat.bind_count++;
	rpc_put_task(child);
	वापस;

bailout_मुक्त_args:
	kमुक्त(map);
bailout_release_client:
	rpc_release_client(rpcb_clnt);
bailout_noमुक्त:
	rpcb_wake_rpcbind_रुकोers(xprt, status);
	task->tk_status = status;
	xprt_put(xprt);
पूर्ण
EXPORT_SYMBOL_GPL(rpcb_getport_async);

/*
 * Rpcbind child task calls this callback via tk_निकास.
 */
अटल व्योम rpcb_getport_करोne(काष्ठा rpc_task *child, व्योम *data)
अणु
	काष्ठा rpcbind_args *map = data;
	काष्ठा rpc_xprt *xprt = map->r_xprt;

	map->r_status = child->tk_status;

	/* Garbage reply: retry with a lesser rpcbind version */
	अगर (map->r_status == -EIO)
		map->r_status = -EPROTONOSUPPORT;

	/* rpcbind server करोesn't support this rpcbind protocol version */
	अगर (map->r_status == -EPROTONOSUPPORT)
		xprt->bind_index++;

	अगर (map->r_status < 0) अणु
		/* rpcbind server not available on remote host? */
		map->r_port = 0;

	पूर्ण अन्यथा अगर (map->r_port == 0) अणु
		/* Requested RPC service wasn't रेजिस्टरed on remote host */
		map->r_status = -EACCES;
	पूर्ण अन्यथा अणु
		/* Succeeded */
		map->r_status = 0;
	पूर्ण

	trace_rpcb_setport(child, map->r_status, map->r_port);
	xprt->ops->set_port(xprt, map->r_port);
	अगर (map->r_port)
		xprt_set_bound(xprt);
पूर्ण

/*
 * XDR functions क्रम rpcbind
 */

अटल व्योम rpcb_enc_mapping(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा rpcbind_args *rpcb = data;
	__be32 *p;

	p = xdr_reserve_space(xdr, RPCB_mappingargs_sz << 2);
	*p++ = cpu_to_be32(rpcb->r_prog);
	*p++ = cpu_to_be32(rpcb->r_vers);
	*p++ = cpu_to_be32(rpcb->r_prot);
	*p   = cpu_to_be32(rpcb->r_port);
पूर्ण

अटल पूर्णांक rpcb_dec_getport(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			    व्योम *data)
अणु
	काष्ठा rpcbind_args *rpcb = data;
	अचिन्हित दीर्घ port;
	__be32 *p;

	rpcb->r_port = 0;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -EIO;

	port = be32_to_cpup(p);
	अगर (unlikely(port > अच_लघु_उच्च))
		वापस -EIO;

	rpcb->r_port = port;
	वापस 0;
पूर्ण

अटल पूर्णांक rpcb_dec_set(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			व्योम *data)
अणु
	अचिन्हित पूर्णांक *boolp = data;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -EIO;

	*boolp = 0;
	अगर (*p != xdr_zero)
		*boolp = 1;
	वापस 0;
पूर्ण

अटल व्योम encode_rpcb_string(काष्ठा xdr_stream *xdr, स्थिर अक्षर *string,
			       स्थिर u32 maxम_माप)
अणु
	__be32 *p;
	u32 len;

	len = म_माप(string);
	WARN_ON_ONCE(len > maxम_माप);
	अगर (len > maxम_माप)
		/* truncate and hope क्रम the best */
		len = maxम_माप;
	p = xdr_reserve_space(xdr, 4 + len);
	xdr_encode_opaque(p, string, len);
पूर्ण

अटल व्योम rpcb_enc_getaddr(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा rpcbind_args *rpcb = data;
	__be32 *p;

	p = xdr_reserve_space(xdr, (RPCB_program_sz + RPCB_version_sz) << 2);
	*p++ = cpu_to_be32(rpcb->r_prog);
	*p = cpu_to_be32(rpcb->r_vers);

	encode_rpcb_string(xdr, rpcb->r_netid, RPCBIND_MAXNETIDLEN);
	encode_rpcb_string(xdr, rpcb->r_addr, RPCBIND_MAXUADDRLEN);
	encode_rpcb_string(xdr, rpcb->r_owner, RPCB_MAXOWNERLEN);
पूर्ण

अटल पूर्णांक rpcb_dec_getaddr(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			    व्योम *data)
अणु
	काष्ठा rpcbind_args *rpcb = data;
	काष्ठा sockaddr_storage address;
	काष्ठा sockaddr *sap = (काष्ठा sockaddr *)&address;
	__be32 *p;
	u32 len;

	rpcb->r_port = 0;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		जाओ out_fail;
	len = be32_to_cpup(p);

	/*
	 * If the वापसed universal address is a null string,
	 * the requested RPC service was not रेजिस्टरed.
	 */
	अगर (len == 0)
		वापस 0;

	अगर (unlikely(len > RPCBIND_MAXUADDRLEN))
		जाओ out_fail;

	p = xdr_अंतरभूत_decode(xdr, len);
	अगर (unlikely(p == शून्य))
		जाओ out_fail;

	अगर (rpc_uaddr2sockaddr(req->rq_xprt->xprt_net, (अक्षर *)p, len,
				sap, माप(address)) == 0)
		जाओ out_fail;
	rpcb->r_port = rpc_get_port(sap);

	वापस 0;

out_fail:
	वापस -EIO;
पूर्ण

/*
 * Not all rpcbind procedures described in RFC 1833 are implemented
 * since the Linux kernel RPC code requires only these.
 */

अटल स्थिर काष्ठा rpc_procinfo rpcb_procedures2[] = अणु
	[RPCBPROC_SET] = अणु
		.p_proc		= RPCBPROC_SET,
		.p_encode	= rpcb_enc_mapping,
		.p_decode	= rpcb_dec_set,
		.p_arglen	= RPCB_mappingargs_sz,
		.p_replen	= RPCB_setres_sz,
		.p_statidx	= RPCBPROC_SET,
		.p_समयr	= 0,
		.p_name		= "SET",
	पूर्ण,
	[RPCBPROC_UNSET] = अणु
		.p_proc		= RPCBPROC_UNSET,
		.p_encode	= rpcb_enc_mapping,
		.p_decode	= rpcb_dec_set,
		.p_arglen	= RPCB_mappingargs_sz,
		.p_replen	= RPCB_setres_sz,
		.p_statidx	= RPCBPROC_UNSET,
		.p_समयr	= 0,
		.p_name		= "UNSET",
	पूर्ण,
	[RPCBPROC_GETPORT] = अणु
		.p_proc		= RPCBPROC_GETPORT,
		.p_encode	= rpcb_enc_mapping,
		.p_decode	= rpcb_dec_getport,
		.p_arglen	= RPCB_mappingargs_sz,
		.p_replen	= RPCB_getportres_sz,
		.p_statidx	= RPCBPROC_GETPORT,
		.p_समयr	= 0,
		.p_name		= "GETPORT",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpc_procinfo rpcb_procedures3[] = अणु
	[RPCBPROC_SET] = अणु
		.p_proc		= RPCBPROC_SET,
		.p_encode	= rpcb_enc_getaddr,
		.p_decode	= rpcb_dec_set,
		.p_arglen	= RPCB_getaddrargs_sz,
		.p_replen	= RPCB_setres_sz,
		.p_statidx	= RPCBPROC_SET,
		.p_समयr	= 0,
		.p_name		= "SET",
	पूर्ण,
	[RPCBPROC_UNSET] = अणु
		.p_proc		= RPCBPROC_UNSET,
		.p_encode	= rpcb_enc_getaddr,
		.p_decode	= rpcb_dec_set,
		.p_arglen	= RPCB_getaddrargs_sz,
		.p_replen	= RPCB_setres_sz,
		.p_statidx	= RPCBPROC_UNSET,
		.p_समयr	= 0,
		.p_name		= "UNSET",
	पूर्ण,
	[RPCBPROC_GETADDR] = अणु
		.p_proc		= RPCBPROC_GETADDR,
		.p_encode	= rpcb_enc_getaddr,
		.p_decode	= rpcb_dec_getaddr,
		.p_arglen	= RPCB_getaddrargs_sz,
		.p_replen	= RPCB_getaddrres_sz,
		.p_statidx	= RPCBPROC_GETADDR,
		.p_समयr	= 0,
		.p_name		= "GETADDR",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpc_procinfo rpcb_procedures4[] = अणु
	[RPCBPROC_SET] = अणु
		.p_proc		= RPCBPROC_SET,
		.p_encode	= rpcb_enc_getaddr,
		.p_decode	= rpcb_dec_set,
		.p_arglen	= RPCB_getaddrargs_sz,
		.p_replen	= RPCB_setres_sz,
		.p_statidx	= RPCBPROC_SET,
		.p_समयr	= 0,
		.p_name		= "SET",
	पूर्ण,
	[RPCBPROC_UNSET] = अणु
		.p_proc		= RPCBPROC_UNSET,
		.p_encode	= rpcb_enc_getaddr,
		.p_decode	= rpcb_dec_set,
		.p_arglen	= RPCB_getaddrargs_sz,
		.p_replen	= RPCB_setres_sz,
		.p_statidx	= RPCBPROC_UNSET,
		.p_समयr	= 0,
		.p_name		= "UNSET",
	पूर्ण,
	[RPCBPROC_GETADDR] = अणु
		.p_proc		= RPCBPROC_GETADDR,
		.p_encode	= rpcb_enc_getaddr,
		.p_decode	= rpcb_dec_getaddr,
		.p_arglen	= RPCB_getaddrargs_sz,
		.p_replen	= RPCB_getaddrres_sz,
		.p_statidx	= RPCBPROC_GETADDR,
		.p_समयr	= 0,
		.p_name		= "GETADDR",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpcb_info rpcb_next_version[] = अणु
	अणु
		.rpc_vers	= RPCBVERS_2,
		.rpc_proc	= &rpcb_procedures2[RPCBPROC_GETPORT],
	पूर्ण,
	अणु
		.rpc_proc	= शून्य,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rpcb_info rpcb_next_version6[] = अणु
	अणु
		.rpc_vers	= RPCBVERS_4,
		.rpc_proc	= &rpcb_procedures4[RPCBPROC_GETADDR],
	पूर्ण,
	अणु
		.rpc_vers	= RPCBVERS_3,
		.rpc_proc	= &rpcb_procedures3[RPCBPROC_GETADDR],
	पूर्ण,
	अणु
		.rpc_proc	= शून्य,
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक rpcb_version2_counts[ARRAY_SIZE(rpcb_procedures2)];
अटल स्थिर काष्ठा rpc_version rpcb_version2 = अणु
	.number		= RPCBVERS_2,
	.nrprocs	= ARRAY_SIZE(rpcb_procedures2),
	.procs		= rpcb_procedures2,
	.counts		= rpcb_version2_counts,
पूर्ण;

अटल अचिन्हित पूर्णांक rpcb_version3_counts[ARRAY_SIZE(rpcb_procedures3)];
अटल स्थिर काष्ठा rpc_version rpcb_version3 = अणु
	.number		= RPCBVERS_3,
	.nrprocs	= ARRAY_SIZE(rpcb_procedures3),
	.procs		= rpcb_procedures3,
	.counts		= rpcb_version3_counts,
पूर्ण;

अटल अचिन्हित पूर्णांक rpcb_version4_counts[ARRAY_SIZE(rpcb_procedures4)];
अटल स्थिर काष्ठा rpc_version rpcb_version4 = अणु
	.number		= RPCBVERS_4,
	.nrprocs	= ARRAY_SIZE(rpcb_procedures4),
	.procs		= rpcb_procedures4,
	.counts		= rpcb_version4_counts,
पूर्ण;

अटल स्थिर काष्ठा rpc_version *rpcb_version[] = अणु
	शून्य,
	शून्य,
	&rpcb_version2,
	&rpcb_version3,
	&rpcb_version4
पूर्ण;

अटल काष्ठा rpc_stat rpcb_stats;

अटल स्थिर काष्ठा rpc_program rpcb_program = अणु
	.name		= "rpcbind",
	.number		= RPCBIND_PROGRAM,
	.nrvers		= ARRAY_SIZE(rpcb_version),
	.version	= rpcb_version,
	.stats		= &rpcb_stats,
पूर्ण;
