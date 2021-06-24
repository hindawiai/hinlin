<शैली गुरु>
/*
 * Copyright (c) 2006, 2019 Oracle and/or its affiliates. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
#समावेश <linux/kernel.h>
#समावेश <net/sock.h>
#समावेश <linux/in.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/jhash.h>
#समावेश <linux/ratelimit.h>
#समावेश "rds.h"

अटल काष्ठा rhashtable bind_hash_table;

अटल स्थिर काष्ठा rhashtable_params ht_parms = अणु
	.nelem_hपूर्णांक = 768,
	.key_len = RDS_BOUND_KEY_LEN,
	.key_offset = दुरत्व(काष्ठा rds_sock, rs_bound_key),
	.head_offset = दुरत्व(काष्ठा rds_sock, rs_bound_node),
	.max_size = 16384,
	.min_size = 1024,
पूर्ण;

/* Create a key क्रम the bind hash table manipulation.  Port is in network byte
 * order.
 */
अटल अंतरभूत व्योम __rds_create_bind_key(u8 *key, स्थिर काष्ठा in6_addr *addr,
					 __be16 port, __u32 scope_id)
अणु
	स_नकल(key, addr, माप(*addr));
	key += माप(*addr);
	स_नकल(key, &port, माप(port));
	key += माप(port);
	स_नकल(key, &scope_id, माप(scope_id));
पूर्ण

/*
 * Return the rds_sock bound at the given local address.
 *
 * The rx path can race with rds_release.  We notice अगर rds_release() has
 * marked this socket and करोn't वापस a rs ref to the rx path.
 */
काष्ठा rds_sock *rds_find_bound(स्थिर काष्ठा in6_addr *addr, __be16 port,
				__u32 scope_id)
अणु
	u8 key[RDS_BOUND_KEY_LEN];
	काष्ठा rds_sock *rs;

	__rds_create_bind_key(key, addr, port, scope_id);
	rcu_पढ़ो_lock();
	rs = rhashtable_lookup(&bind_hash_table, key, ht_parms);
	अगर (rs && (sock_flag(rds_rs_to_sk(rs), SOCK_DEAD) ||
		   !refcount_inc_not_zero(&rds_rs_to_sk(rs)->sk_refcnt)))
		rs = शून्य;

	rcu_पढ़ो_unlock();

	rdsdebug("returning rs %p for %pI6c:%u\n", rs, addr,
		 ntohs(port));

	वापस rs;
पूर्ण

/* वापसs -ve त्रुटि_सं or +ve port */
अटल पूर्णांक rds_add_bound(काष्ठा rds_sock *rs, स्थिर काष्ठा in6_addr *addr,
			 __be16 *port, __u32 scope_id)
अणु
	पूर्णांक ret = -EADDRINUSE;
	u16 rover, last;
	u8 key[RDS_BOUND_KEY_LEN];

	अगर (*port != 0) अणु
		rover = be16_to_cpu(*port);
		अगर (rover == RDS_FLAG_PROBE_PORT)
			वापस -EINVAL;
		last = rover;
	पूर्ण अन्यथा अणु
		rover = max_t(u16, pअक्रमom_u32(), 2);
		last = rover - 1;
	पूर्ण

	करो अणु
		अगर (rover == 0)
			rover++;

		अगर (rover == RDS_FLAG_PROBE_PORT)
			जारी;
		__rds_create_bind_key(key, addr, cpu_to_be16(rover),
				      scope_id);
		अगर (rhashtable_lookup_fast(&bind_hash_table, key, ht_parms))
			जारी;

		स_नकल(rs->rs_bound_key, key, माप(rs->rs_bound_key));
		rs->rs_bound_addr = *addr;
		net_get_अक्रमom_once(&rs->rs_hash_initval,
				    माप(rs->rs_hash_initval));
		rs->rs_bound_port = cpu_to_be16(rover);
		rs->rs_bound_node.next = शून्य;
		rds_sock_addref(rs);
		अगर (!rhashtable_insert_fast(&bind_hash_table,
					    &rs->rs_bound_node, ht_parms)) अणु
			*port = rs->rs_bound_port;
			rs->rs_bound_scope_id = scope_id;
			ret = 0;
			rdsdebug("rs %p binding to %pI6c:%d\n",
				 rs, addr, (पूर्णांक)ntohs(*port));
			अवरोध;
		पूर्ण अन्यथा अणु
			rs->rs_bound_addr = in6addr_any;
			rds_sock_put(rs);
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (rover++ != last);

	वापस ret;
पूर्ण

व्योम rds_हटाओ_bound(काष्ठा rds_sock *rs)
अणु

	अगर (ipv6_addr_any(&rs->rs_bound_addr))
		वापस;

	rdsdebug("rs %p unbinding from %pI6c:%d\n",
		 rs, &rs->rs_bound_addr,
		 ntohs(rs->rs_bound_port));

	rhashtable_हटाओ_fast(&bind_hash_table, &rs->rs_bound_node, ht_parms);
	rds_sock_put(rs);
	rs->rs_bound_addr = in6addr_any;
पूर्ण

पूर्णांक rds_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr, पूर्णांक addr_len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा rds_sock *rs = rds_sk_to_rs(sk);
	काष्ठा in6_addr v6addr, *binding_addr;
	काष्ठा rds_transport *trans;
	__u32 scope_id = 0;
	पूर्णांक ret = 0;
	__be16 port;

	/* We allow an RDS socket to be bound to either IPv4 or IPv6
	 * address.
	 */
	अगर (addr_len < दुरत्वend(काष्ठा sockaddr, sa_family))
		वापस -EINVAL;
	अगर (uaddr->sa_family == AF_INET) अणु
		काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)uaddr;

		अगर (addr_len < माप(काष्ठा sockaddr_in) ||
		    sin->sin_addr.s_addr == htonl(INADDR_ANY) ||
		    sin->sin_addr.s_addr == htonl(INADDR_BROADCAST) ||
		    ipv4_is_multicast(sin->sin_addr.s_addr))
			वापस -EINVAL;
		ipv6_addr_set_v4mapped(sin->sin_addr.s_addr, &v6addr);
		binding_addr = &v6addr;
		port = sin->sin_port;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (uaddr->sa_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)uaddr;
		पूर्णांक addr_type;

		अगर (addr_len < माप(काष्ठा sockaddr_in6))
			वापस -EINVAL;
		addr_type = ipv6_addr_type(&sin6->sin6_addr);
		अगर (!(addr_type & IPV6_ADDR_UNICAST)) अणु
			__be32 addr4;

			अगर (!(addr_type & IPV6_ADDR_MAPPED))
				वापस -EINVAL;

			/* It is a mapped address.  Need to करो some sanity
			 * checks.
			 */
			addr4 = sin6->sin6_addr.s6_addr32[3];
			अगर (addr4 == htonl(INADDR_ANY) ||
			    addr4 == htonl(INADDR_BROADCAST) ||
			    ipv4_is_multicast(addr4))
				वापस -EINVAL;
		पूर्ण
		/* The scope ID must be specअगरied क्रम link local address. */
		अगर (addr_type & IPV6_ADDR_LINKLOCAL) अणु
			अगर (sin6->sin6_scope_id == 0)
				वापस -EINVAL;
			scope_id = sin6->sin6_scope_id;
		पूर्ण
		binding_addr = &sin6->sin6_addr;
		port = sin6->sin6_port;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	lock_sock(sk);

	/* RDS socket करोes not allow re-binding. */
	अगर (!ipv6_addr_any(&rs->rs_bound_addr)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	/* Socket is connected.  The binding address should have the same
	 * scope ID as the connected address, except the हाल when one is
	 * non-link local address (scope_id is 0).
	 */
	अगर (!ipv6_addr_any(&rs->rs_conn_addr) && scope_id &&
	    rs->rs_bound_scope_id &&
	    scope_id != rs->rs_bound_scope_id) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* The transport can be set using SO_RDS_TRANSPORT option beक्रमe the
	 * socket is bound.
	 */
	अगर (rs->rs_transport) अणु
		trans = rs->rs_transport;
		अगर (!trans->laddr_check ||
		    trans->laddr_check(sock_net(sock->sk),
				       binding_addr, scope_id) != 0) अणु
			ret = -ENOPROTOOPT;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		trans = rds_trans_get_preferred(sock_net(sock->sk),
						binding_addr, scope_id);
		अगर (!trans) अणु
			ret = -EADDRNOTAVAIL;
			pr_info_ratelimited("RDS: %s could not find a transport for %pI6c, load rds_tcp or rds_rdma?\n",
					    __func__, binding_addr);
			जाओ out;
		पूर्ण
		rs->rs_transport = trans;
	पूर्ण

	sock_set_flag(sk, SOCK_RCU_FREE);
	ret = rds_add_bound(rs, binding_addr, &port, scope_id);
	अगर (ret)
		rs->rs_transport = शून्य;

out:
	release_sock(sk);
	वापस ret;
पूर्ण

व्योम rds_bind_lock_destroy(व्योम)
अणु
	rhashtable_destroy(&bind_hash_table);
पूर्ण

पूर्णांक rds_bind_lock_init(व्योम)
अणु
	वापस rhashtable_init(&bind_hash_table, &ht_parms);
पूर्ण
