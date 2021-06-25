<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Server address list management
 *
 * Copyright (C) 2017 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/dns_resolver.h>
#समावेश <linux/inet.h>
#समावेश <keys/rxrpc-type.h>
#समावेश "internal.h"
#समावेश "afs_fs.h"

/*
 * Release an address list.
 */
व्योम afs_put_addrlist(काष्ठा afs_addr_list *alist)
अणु
	अगर (alist && refcount_dec_and_test(&alist->usage))
		kमुक्त_rcu(alist, rcu);
पूर्ण

/*
 * Allocate an address list.
 */
काष्ठा afs_addr_list *afs_alloc_addrlist(अचिन्हित पूर्णांक nr,
					 अचिन्हित लघु service,
					 अचिन्हित लघु port)
अणु
	काष्ठा afs_addr_list *alist;
	अचिन्हित पूर्णांक i;

	_enter("%u,%u,%u", nr, service, port);

	अगर (nr > AFS_MAX_ADDRESSES)
		nr = AFS_MAX_ADDRESSES;

	alist = kzalloc(काष्ठा_size(alist, addrs, nr), GFP_KERNEL);
	अगर (!alist)
		वापस शून्य;

	refcount_set(&alist->usage, 1);
	alist->max_addrs = nr;

	क्रम (i = 0; i < nr; i++) अणु
		काष्ठा sockaddr_rxrpc *srx = &alist->addrs[i];
		srx->srx_family			= AF_RXRPC;
		srx->srx_service		= service;
		srx->transport_type		= SOCK_DGRAM;
		srx->transport_len		= माप(srx->transport.sin6);
		srx->transport.sin6.sin6_family	= AF_INET6;
		srx->transport.sin6.sin6_port	= htons(port);
	पूर्ण

	वापस alist;
पूर्ण

/*
 * Parse a text string consisting of delimited addresses.
 */
काष्ठा afs_vlserver_list *afs_parse_text_addrs(काष्ठा afs_net *net,
					       स्थिर अक्षर *text, माप_प्रकार len,
					       अक्षर delim,
					       अचिन्हित लघु service,
					       अचिन्हित लघु port)
अणु
	काष्ठा afs_vlserver_list *vllist;
	काष्ठा afs_addr_list *alist;
	स्थिर अक्षर *p, *end = text + len;
	स्थिर अक्षर *problem;
	अचिन्हित पूर्णांक nr = 0;
	पूर्णांक ret = -ENOMEM;

	_enter("%*.*s,%c", (पूर्णांक)len, (पूर्णांक)len, text, delim);

	अगर (!len) अणु
		_leave(" = -EDESTADDRREQ [empty]");
		वापस ERR_PTR(-EDESTADDRREQ);
	पूर्ण

	अगर (delim == ':' && (memchr(text, ',', len) || !memchr(text, '.', len)))
		delim = ',';

	/* Count the addresses */
	p = text;
	करो अणु
		अगर (!*p) अणु
			problem = "nul";
			जाओ inval;
		पूर्ण
		अगर (*p == delim)
			जारी;
		nr++;
		अगर (*p == '[') अणु
			p++;
			अगर (p == end) अणु
				problem = "brace1";
				जाओ inval;
			पूर्ण
			p = स_प्रथम(p, ']', end - p);
			अगर (!p) अणु
				problem = "brace2";
				जाओ inval;
			पूर्ण
			p++;
			अगर (p >= end)
				अवरोध;
		पूर्ण

		p = स_प्रथम(p, delim, end - p);
		अगर (!p)
			अवरोध;
		p++;
	पूर्ण जबतक (p < end);

	_debug("%u/%u addresses", nr, AFS_MAX_ADDRESSES);

	vllist = afs_alloc_vlserver_list(1);
	अगर (!vllist)
		वापस ERR_PTR(-ENOMEM);

	vllist->nr_servers = 1;
	vllist->servers[0].server = afs_alloc_vlserver("<dummy>", 7, AFS_VL_PORT);
	अगर (!vllist->servers[0].server)
		जाओ error_vl;

	alist = afs_alloc_addrlist(nr, service, AFS_VL_PORT);
	अगर (!alist)
		जाओ error;

	/* Extract the addresses */
	p = text;
	करो अणु
		स्थिर अक्षर *q, *stop;
		अचिन्हित पूर्णांक xport = port;
		__be32 x[4];
		पूर्णांक family;

		अगर (*p == delim) अणु
			p++;
			जारी;
		पूर्ण

		अगर (*p == '[') अणु
			p++;
			q = स_प्रथम(p, ']', end - p);
		पूर्ण अन्यथा अणु
			क्रम (q = p; q < end; q++)
				अगर (*q == '+' || *q == delim)
					अवरोध;
		पूर्ण

		अगर (in4_pton(p, q - p, (u8 *)&x[0], -1, &stop)) अणु
			family = AF_INET;
		पूर्ण अन्यथा अगर (in6_pton(p, q - p, (u8 *)x, -1, &stop)) अणु
			family = AF_INET6;
		पूर्ण अन्यथा अणु
			problem = "family";
			जाओ bad_address;
		पूर्ण

		p = q;
		अगर (stop != p) अणु
			problem = "nostop";
			जाओ bad_address;
		पूर्ण

		अगर (q < end && *q == ']')
			p++;

		अगर (p < end) अणु
			अगर (*p == '+') अणु
				/* Port number specअगरication "+1234" */
				xport = 0;
				p++;
				अगर (p >= end || !है_अंक(*p)) अणु
					problem = "port";
					जाओ bad_address;
				पूर्ण
				करो अणु
					xport *= 10;
					xport += *p - '0';
					अगर (xport > 65535) अणु
						problem = "pval";
						जाओ bad_address;
					पूर्ण
					p++;
				पूर्ण जबतक (p < end && है_अंक(*p));
			पूर्ण अन्यथा अगर (*p == delim) अणु
				p++;
			पूर्ण अन्यथा अणु
				problem = "weird";
				जाओ bad_address;
			पूर्ण
		पूर्ण

		अगर (family == AF_INET)
			afs_merge_fs_addr4(alist, x[0], xport);
		अन्यथा
			afs_merge_fs_addr6(alist, x, xport);

	पूर्ण जबतक (p < end);

	rcu_assign_poपूर्णांकer(vllist->servers[0].server->addresses, alist);
	_leave(" = [nr %u]", alist->nr_addrs);
	वापस vllist;

inval:
	_leave(" = -EINVAL [%s %zu %*.*s]",
	       problem, p - text, (पूर्णांक)len, (पूर्णांक)len, text);
	वापस ERR_PTR(-EINVAL);
bad_address:
	_leave(" = -EINVAL [%s %zu %*.*s]",
	       problem, p - text, (पूर्णांक)len, (पूर्णांक)len, text);
	ret = -EINVAL;
error:
	afs_put_addrlist(alist);
error_vl:
	afs_put_vlserverlist(net, vllist);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * Compare old and new address lists to see अगर there's been any change.
 * - How to करो this in better than O(Nlog(N)) समय?
 *   - We करोn't really want to sort the address list, but would rather take the
 *     list as we got it so as not to unकरो record rotation by the DNS server.
 */
#अगर 0
अटल पूर्णांक afs_cmp_addr_list(स्थिर काष्ठा afs_addr_list *a1,
			     स्थिर काष्ठा afs_addr_list *a2)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * Perक्रमm a DNS query क्रम VL servers and build a up an address list.
 */
काष्ठा afs_vlserver_list *afs_dns_query(काष्ठा afs_cell *cell, समय64_t *_expiry)
अणु
	काष्ठा afs_vlserver_list *vllist;
	अक्षर *result = शून्य;
	पूर्णांक ret;

	_enter("%s", cell->name);

	ret = dns_query(cell->net->net, "afsdb", cell->name, cell->name_len,
			"srv=1", &result, _expiry, true);
	अगर (ret < 0) अणु
		_leave(" = %d [dns]", ret);
		वापस ERR_PTR(ret);
	पूर्ण

	अगर (*_expiry == 0)
		*_expiry = kसमय_get_real_seconds() + 60;

	अगर (ret > 1 && result[0] == 0)
		vllist = afs_extract_vlserver_list(cell, result, ret);
	अन्यथा
		vllist = afs_parse_text_addrs(cell->net, result, ret, ',',
					      VL_SERVICE, AFS_VL_PORT);
	kमुक्त(result);
	अगर (IS_ERR(vllist) && vllist != ERR_PTR(-ENOMEM))
		pr_err("Failed to parse DNS data %ld\n", PTR_ERR(vllist));

	वापस vllist;
पूर्ण

/*
 * Merge an IPv4 entry पूर्णांकo a fileserver address list.
 */
व्योम afs_merge_fs_addr4(काष्ठा afs_addr_list *alist, __be32 xdr, u16 port)
अणु
	काष्ठा sockaddr_rxrpc *srx;
	u32 addr = ntohl(xdr);
	पूर्णांक i;

	अगर (alist->nr_addrs >= alist->max_addrs)
		वापस;

	क्रम (i = 0; i < alist->nr_ipv4; i++) अणु
		काष्ठा sockaddr_in *a = &alist->addrs[i].transport.sin;
		u32 a_addr = ntohl(a->sin_addr.s_addr);
		u16 a_port = ntohs(a->sin_port);

		अगर (addr == a_addr && port == a_port)
			वापस;
		अगर (addr == a_addr && port < a_port)
			अवरोध;
		अगर (addr < a_addr)
			अवरोध;
	पूर्ण

	अगर (i < alist->nr_addrs)
		स_हटाओ(alist->addrs + i + 1,
			alist->addrs + i,
			माप(alist->addrs[0]) * (alist->nr_addrs - i));

	srx = &alist->addrs[i];
	srx->srx_family = AF_RXRPC;
	srx->transport_type = SOCK_DGRAM;
	srx->transport_len = माप(srx->transport.sin);
	srx->transport.sin.sin_family = AF_INET;
	srx->transport.sin.sin_port = htons(port);
	srx->transport.sin.sin_addr.s_addr = xdr;
	alist->nr_ipv4++;
	alist->nr_addrs++;
पूर्ण

/*
 * Merge an IPv6 entry पूर्णांकo a fileserver address list.
 */
व्योम afs_merge_fs_addr6(काष्ठा afs_addr_list *alist, __be32 *xdr, u16 port)
अणु
	काष्ठा sockaddr_rxrpc *srx;
	पूर्णांक i, dअगरf;

	अगर (alist->nr_addrs >= alist->max_addrs)
		वापस;

	क्रम (i = alist->nr_ipv4; i < alist->nr_addrs; i++) अणु
		काष्ठा sockaddr_in6 *a = &alist->addrs[i].transport.sin6;
		u16 a_port = ntohs(a->sin6_port);

		dअगरf = स_भेद(xdr, &a->sin6_addr, 16);
		अगर (dअगरf == 0 && port == a_port)
			वापस;
		अगर (dअगरf == 0 && port < a_port)
			अवरोध;
		अगर (dअगरf < 0)
			अवरोध;
	पूर्ण

	अगर (i < alist->nr_addrs)
		स_हटाओ(alist->addrs + i + 1,
			alist->addrs + i,
			माप(alist->addrs[0]) * (alist->nr_addrs - i));

	srx = &alist->addrs[i];
	srx->srx_family = AF_RXRPC;
	srx->transport_type = SOCK_DGRAM;
	srx->transport_len = माप(srx->transport.sin6);
	srx->transport.sin6.sin6_family = AF_INET6;
	srx->transport.sin6.sin6_port = htons(port);
	स_नकल(&srx->transport.sin6.sin6_addr, xdr, 16);
	alist->nr_addrs++;
पूर्ण

/*
 * Get an address to try.
 */
bool afs_iterate_addresses(काष्ठा afs_addr_cursor *ac)
अणु
	अचिन्हित दीर्घ set, failed;
	पूर्णांक index;

	अगर (!ac->alist)
		वापस false;

	set = ac->alist->responded;
	failed = ac->alist->failed;
	_enter("%lx-%lx-%lx,%d", set, failed, ac->tried, ac->index);

	ac->nr_iterations++;

	set &= ~(failed | ac->tried);

	अगर (!set)
		वापस false;

	index = READ_ONCE(ac->alist->preferred);
	अगर (test_bit(index, &set))
		जाओ selected;

	index = __ffs(set);

selected:
	ac->index = index;
	set_bit(index, &ac->tried);
	ac->responded = false;
	वापस true;
पूर्ण

/*
 * Release an address list cursor.
 */
पूर्णांक afs_end_cursor(काष्ठा afs_addr_cursor *ac)
अणु
	काष्ठा afs_addr_list *alist;

	alist = ac->alist;
	अगर (alist) अणु
		अगर (ac->responded &&
		    ac->index != alist->preferred &&
		    test_bit(ac->alist->preferred, &ac->tried))
			WRITE_ONCE(alist->preferred, ac->index);
		afs_put_addrlist(alist);
		ac->alist = शून्य;
	पूर्ण

	वापस ac->error;
पूर्ण
