<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS vlserver list management.
 *
 * Copyright (C) 2018 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"

काष्ठा afs_vlserver *afs_alloc_vlserver(स्थिर अक्षर *name, माप_प्रकार name_len,
					अचिन्हित लघु port)
अणु
	काष्ठा afs_vlserver *vlserver;

	vlserver = kzalloc(काष्ठा_size(vlserver, name, name_len + 1),
			   GFP_KERNEL);
	अगर (vlserver) अणु
		atomic_set(&vlserver->usage, 1);
		rwlock_init(&vlserver->lock);
		init_रुकोqueue_head(&vlserver->probe_wq);
		spin_lock_init(&vlserver->probe_lock);
		vlserver->rtt = अच_पूर्णांक_उच्च;
		vlserver->name_len = name_len;
		vlserver->port = port;
		स_नकल(vlserver->name, name, name_len);
	पूर्ण
	वापस vlserver;
पूर्ण

अटल व्योम afs_vlserver_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा afs_vlserver *vlserver = container_of(rcu, काष्ठा afs_vlserver, rcu);

	afs_put_addrlist(rcu_access_poपूर्णांकer(vlserver->addresses));
	kमुक्त_rcu(vlserver, rcu);
पूर्ण

व्योम afs_put_vlserver(काष्ठा afs_net *net, काष्ठा afs_vlserver *vlserver)
अणु
	अगर (vlserver) अणु
		अचिन्हित पूर्णांक u = atomic_dec_वापस(&vlserver->usage);
		//_debug("VL PUT %p{%u}", vlserver, u);

		अगर (u == 0)
			call_rcu(&vlserver->rcu, afs_vlserver_rcu);
	पूर्ण
पूर्ण

काष्ठा afs_vlserver_list *afs_alloc_vlserver_list(अचिन्हित पूर्णांक nr_servers)
अणु
	काष्ठा afs_vlserver_list *vllist;

	vllist = kzalloc(काष्ठा_size(vllist, servers, nr_servers), GFP_KERNEL);
	अगर (vllist) अणु
		atomic_set(&vllist->usage, 1);
		rwlock_init(&vllist->lock);
	पूर्ण

	वापस vllist;
पूर्ण

व्योम afs_put_vlserverlist(काष्ठा afs_net *net, काष्ठा afs_vlserver_list *vllist)
अणु
	अगर (vllist) अणु
		अचिन्हित पूर्णांक u = atomic_dec_वापस(&vllist->usage);

		//_debug("VLLS PUT %p{%u}", vllist, u);
		अगर (u == 0) अणु
			पूर्णांक i;

			क्रम (i = 0; i < vllist->nr_servers; i++) अणु
				afs_put_vlserver(net, vllist->servers[i].server);
			पूर्ण
			kमुक्त_rcu(vllist, rcu);
		पूर्ण
	पूर्ण
पूर्ण

अटल u16 afs_extract_le16(स्थिर u8 **_b)
अणु
	u16 val;

	val  = (u16)*(*_b)++ << 0;
	val |= (u16)*(*_b)++ << 8;
	वापस val;
पूर्ण

/*
 * Build a VL server address list from a DNS queried server list.
 */
अटल काष्ठा afs_addr_list *afs_extract_vl_addrs(स्थिर u8 **_b, स्थिर u8 *end,
						  u8 nr_addrs, u16 port)
अणु
	काष्ठा afs_addr_list *alist;
	स्थिर u8 *b = *_b;
	पूर्णांक ret = -EINVAL;

	alist = afs_alloc_addrlist(nr_addrs, VL_SERVICE, port);
	अगर (!alist)
		वापस ERR_PTR(-ENOMEM);
	अगर (nr_addrs == 0)
		वापस alist;

	क्रम (; nr_addrs > 0 && end - b >= nr_addrs; nr_addrs--) अणु
		काष्ठा dns_server_list_v1_address hdr;
		__be32 x[4];

		hdr.address_type = *b++;

		चयन (hdr.address_type) अणु
		हाल DNS_ADDRESS_IS_IPV4:
			अगर (end - b < 4) अणु
				_leave(" = -EINVAL [short inet]");
				जाओ error;
			पूर्ण
			स_नकल(x, b, 4);
			afs_merge_fs_addr4(alist, x[0], port);
			b += 4;
			अवरोध;

		हाल DNS_ADDRESS_IS_IPV6:
			अगर (end - b < 16) अणु
				_leave(" = -EINVAL [short inet6]");
				जाओ error;
			पूर्ण
			स_नकल(x, b, 16);
			afs_merge_fs_addr6(alist, x, port);
			b += 16;
			अवरोध;

		शेष:
			_leave(" = -EADDRNOTAVAIL [unknown af %u]",
			       hdr.address_type);
			ret = -EADDRNOTAVAIL;
			जाओ error;
		पूर्ण
	पूर्ण

	/* Start with IPv6 अगर available. */
	अगर (alist->nr_ipv4 < alist->nr_addrs)
		alist->preferred = alist->nr_ipv4;

	*_b = b;
	वापस alist;

error:
	*_b = b;
	afs_put_addrlist(alist);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * Build a VL server list from a DNS queried server list.
 */
काष्ठा afs_vlserver_list *afs_extract_vlserver_list(काष्ठा afs_cell *cell,
						    स्थिर व्योम *buffer,
						    माप_प्रकार buffer_size)
अणु
	स्थिर काष्ठा dns_server_list_v1_header *hdr = buffer;
	काष्ठा dns_server_list_v1_server bs;
	काष्ठा afs_vlserver_list *vllist, *previous;
	काष्ठा afs_addr_list *addrs;
	काष्ठा afs_vlserver *server;
	स्थिर u8 *b = buffer, *end = buffer + buffer_size;
	पूर्णांक ret = -ENOMEM, nr_servers, i, j;

	_enter("");

	/* Check that it's a server list, v1 */
	अगर (end - b < माप(*hdr) ||
	    hdr->hdr.content != DNS_PAYLOAD_IS_SERVER_LIST ||
	    hdr->hdr.version != 1) अणु
		pr_notice("kAFS: Got DNS record [%u,%u] len %zu\n",
			  hdr->hdr.content, hdr->hdr.version, end - b);
		ret = -EDESTADDRREQ;
		जाओ dump;
	पूर्ण

	nr_servers = hdr->nr_servers;

	vllist = afs_alloc_vlserver_list(nr_servers);
	अगर (!vllist)
		वापस ERR_PTR(-ENOMEM);

	vllist->source = (hdr->source < NR__dns_record_source) ?
		hdr->source : NR__dns_record_source;
	vllist->status = (hdr->status < NR__dns_lookup_status) ?
		hdr->status : NR__dns_lookup_status;

	पढ़ो_lock(&cell->vl_servers_lock);
	previous = afs_get_vlserverlist(
		rcu_dereference_रक्षित(cell->vl_servers,
					  lockdep_is_held(&cell->vl_servers_lock)));
	पढ़ो_unlock(&cell->vl_servers_lock);

	b += माप(*hdr);
	जबतक (end - b >= माप(bs)) अणु
		bs.name_len	= afs_extract_le16(&b);
		bs.priority	= afs_extract_le16(&b);
		bs.weight	= afs_extract_le16(&b);
		bs.port		= afs_extract_le16(&b);
		bs.source	= *b++;
		bs.status	= *b++;
		bs.protocol	= *b++;
		bs.nr_addrs	= *b++;

		_debug("extract %u %u %u %u %u %u %*.*s",
		       bs.name_len, bs.priority, bs.weight,
		       bs.port, bs.protocol, bs.nr_addrs,
		       bs.name_len, bs.name_len, b);

		अगर (end - b < bs.name_len)
			अवरोध;

		ret = -EPROTONOSUPPORT;
		अगर (bs.protocol == DNS_SERVER_PROTOCOL_UNSPECIFIED) अणु
			bs.protocol = DNS_SERVER_PROTOCOL_UDP;
		पूर्ण अन्यथा अगर (bs.protocol != DNS_SERVER_PROTOCOL_UDP) अणु
			_leave(" = [proto %u]", bs.protocol);
			जाओ error;
		पूर्ण

		अगर (bs.port == 0)
			bs.port = AFS_VL_PORT;
		अगर (bs.source > NR__dns_record_source)
			bs.source = NR__dns_record_source;
		अगर (bs.status > NR__dns_lookup_status)
			bs.status = NR__dns_lookup_status;

		/* See अगर we can update an old server record */
		server = शून्य;
		क्रम (i = 0; i < previous->nr_servers; i++) अणु
			काष्ठा afs_vlserver *p = previous->servers[i].server;

			अगर (p->name_len == bs.name_len &&
			    p->port == bs.port &&
			    strnहालcmp(b, p->name, bs.name_len) == 0) अणु
				server = afs_get_vlserver(p);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!server) अणु
			ret = -ENOMEM;
			server = afs_alloc_vlserver(b, bs.name_len, bs.port);
			अगर (!server)
				जाओ error;
		पूर्ण

		b += bs.name_len;

		/* Extract the addresses - note that we can't skip this as we
		 * have to advance the payload poपूर्णांकer.
		 */
		addrs = afs_extract_vl_addrs(&b, end, bs.nr_addrs, bs.port);
		अगर (IS_ERR(addrs)) अणु
			ret = PTR_ERR(addrs);
			जाओ error_2;
		पूर्ण

		अगर (vllist->nr_servers >= nr_servers) अणु
			_debug("skip %u >= %u", vllist->nr_servers, nr_servers);
			afs_put_addrlist(addrs);
			afs_put_vlserver(cell->net, server);
			जारी;
		पूर्ण

		addrs->source = bs.source;
		addrs->status = bs.status;

		अगर (addrs->nr_addrs == 0) अणु
			afs_put_addrlist(addrs);
			अगर (!rcu_access_poपूर्णांकer(server->addresses)) अणु
				afs_put_vlserver(cell->net, server);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा afs_addr_list *old = addrs;

			ग_लिखो_lock(&server->lock);
			old = rcu_replace_poपूर्णांकer(server->addresses, old,
						  lockdep_is_held(&server->lock));
			ग_लिखो_unlock(&server->lock);
			afs_put_addrlist(old);
		पूर्ण


		/* TODO: Might want to check क्रम duplicates */

		/* Insertion-sort by priority and weight */
		क्रम (j = 0; j < vllist->nr_servers; j++) अणु
			अगर (bs.priority < vllist->servers[j].priority)
				अवरोध; /* Lower preferable */
			अगर (bs.priority == vllist->servers[j].priority &&
			    bs.weight > vllist->servers[j].weight)
				अवरोध; /* Higher preferable */
		पूर्ण

		अगर (j < vllist->nr_servers) अणु
			स_हटाओ(vllist->servers + j + 1,
				vllist->servers + j,
				(vllist->nr_servers - j) * माप(काष्ठा afs_vlserver_entry));
		पूर्ण

		clear_bit(AFS_VLSERVER_FL_PROBED, &server->flags);

		vllist->servers[j].priority = bs.priority;
		vllist->servers[j].weight = bs.weight;
		vllist->servers[j].server = server;
		vllist->nr_servers++;
	पूर्ण

	अगर (b != end) अणु
		_debug("parse error %zd", b - end);
		जाओ error;
	पूर्ण

	afs_put_vlserverlist(cell->net, previous);
	_leave(" = ok [%u]", vllist->nr_servers);
	वापस vllist;

error_2:
	afs_put_vlserver(cell->net, server);
error:
	afs_put_vlserverlist(cell->net, vllist);
	afs_put_vlserverlist(cell->net, previous);
dump:
	अगर (ret != -ENOMEM) अणु
		prपूर्णांकk(KERN_DEBUG "DNS: at %zu\n", (स्थिर व्योम *)b - buffer);
		prपूर्णांक_hex_dump_bytes("DNS: ", DUMP_PREFIX_NONE, buffer, buffer_size);
	पूर्ण
	वापस ERR_PTR(ret);
पूर्ण
