<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/network.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश "common.h"
#समावेश <linux/slab.h>

/* Structure क्रम holding inet करोमुख्य socket's address. */
काष्ठा tomoyo_inet_addr_info अणु
	__be16 port;           /* In network byte order. */
	स्थिर __be32 *address; /* In network byte order. */
	bool is_ipv6;
पूर्ण;

/* Structure क्रम holding unix करोमुख्य socket's address. */
काष्ठा tomoyo_unix_addr_info अणु
	u8 *addr; /* This may not be '\0' terminated string. */
	अचिन्हित पूर्णांक addr_len;
पूर्ण;

/* Structure क्रम holding socket address. */
काष्ठा tomoyo_addr_info अणु
	u8 protocol;
	u8 operation;
	काष्ठा tomoyo_inet_addr_info inet;
	काष्ठा tomoyo_unix_addr_info unix0;
पूर्ण;

/* String table क्रम socket's protocols. */
स्थिर अक्षर * स्थिर tomoyo_proto_keyword[TOMOYO_SOCK_MAX] = अणु
	[SOCK_STREAM]    = "stream",
	[SOCK_DGRAM]     = "dgram",
	[SOCK_RAW]       = "raw",
	[SOCK_SEQPACKET] = "seqpacket",
	[0] = " ", /* Dummy क्रम aव्योमing शून्य poपूर्णांकer dereference. */
	[4] = " ", /* Dummy क्रम aव्योमing शून्य poपूर्णांकer dereference. */
पूर्ण;

/**
 * tomoyo_parse_ipaddr_जोड़ - Parse an IP address.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 * @ptr:   Poपूर्णांकer to "struct tomoyo_ipaddr_union".
 *
 * Returns true on success, false otherwise.
 */
bool tomoyo_parse_ipaddr_जोड़(काष्ठा tomoyo_acl_param *param,
			       काष्ठा tomoyo_ipaddr_जोड़ *ptr)
अणु
	u8 * स्थिर min = ptr->ip[0].in6_u.u6_addr8;
	u8 * स्थिर max = ptr->ip[1].in6_u.u6_addr8;
	अक्षर *address = tomoyo_पढ़ो_token(param);
	स्थिर अक्षर *end;

	अगर (!म_अक्षर(address, ':') &&
	    in4_pton(address, -1, min, '-', &end) > 0) अणु
		ptr->is_ipv6 = false;
		अगर (!*end)
			ptr->ip[1].s6_addr32[0] = ptr->ip[0].s6_addr32[0];
		अन्यथा अगर (*end++ != '-' ||
			 in4_pton(end, -1, max, '\0', &end) <= 0 || *end)
			वापस false;
		वापस true;
	पूर्ण
	अगर (in6_pton(address, -1, min, '-', &end) > 0) अणु
		ptr->is_ipv6 = true;
		अगर (!*end)
			स_हटाओ(max, min, माप(u16) * 8);
		अन्यथा अगर (*end++ != '-' ||
			 in6_pton(end, -1, max, '\0', &end) <= 0 || *end)
			वापस false;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * tomoyo_prपूर्णांक_ipv4 - Prपूर्णांक an IPv4 address.
 *
 * @buffer:     Buffer to ग_लिखो to.
 * @buffer_len: Size of @buffer.
 * @min_ip:     Poपूर्णांकer to __be32.
 * @max_ip:     Poपूर्णांकer to __be32.
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_prपूर्णांक_ipv4(अक्षर *buffer, स्थिर अचिन्हित पूर्णांक buffer_len,
			      स्थिर __be32 *min_ip, स्थिर __be32 *max_ip)
अणु
	snम_लिखो(buffer, buffer_len, "%pI4%c%pI4", min_ip,
		 *min_ip == *max_ip ? '\0' : '-', max_ip);
पूर्ण

/**
 * tomoyo_prपूर्णांक_ipv6 - Prपूर्णांक an IPv6 address.
 *
 * @buffer:     Buffer to ग_लिखो to.
 * @buffer_len: Size of @buffer.
 * @min_ip:     Poपूर्णांकer to "struct in6_addr".
 * @max_ip:     Poपूर्णांकer to "struct in6_addr".
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_prपूर्णांक_ipv6(अक्षर *buffer, स्थिर अचिन्हित पूर्णांक buffer_len,
			      स्थिर काष्ठा in6_addr *min_ip,
			      स्थिर काष्ठा in6_addr *max_ip)
अणु
	snम_लिखो(buffer, buffer_len, "%pI6c%c%pI6c", min_ip,
		 !स_भेद(min_ip, max_ip, 16) ? '\0' : '-', max_ip);
पूर्ण

/**
 * tomoyo_prपूर्णांक_ip - Prपूर्णांक an IP address.
 *
 * @buf:  Buffer to ग_लिखो to.
 * @size: Size of @buf.
 * @ptr:  Poपूर्णांकer to "struct ipaddr_union".
 *
 * Returns nothing.
 */
व्योम tomoyo_prपूर्णांक_ip(अक्षर *buf, स्थिर अचिन्हित पूर्णांक size,
		     स्थिर काष्ठा tomoyo_ipaddr_जोड़ *ptr)
अणु
	अगर (ptr->is_ipv6)
		tomoyo_prपूर्णांक_ipv6(buf, size, &ptr->ip[0], &ptr->ip[1]);
	अन्यथा
		tomoyo_prपूर्णांक_ipv4(buf, size, &ptr->ip[0].s6_addr32[0],
				  &ptr->ip[1].s6_addr32[0]);
पूर्ण

/*
 * Mapping table from "enum tomoyo_network_acl_index" to
 * "enum tomoyo_mac_index" क्रम inet करोमुख्य socket.
 */
अटल स्थिर u8 tomoyo_inet2mac
[TOMOYO_SOCK_MAX][TOMOYO_MAX_NETWORK_OPERATION] = अणु
	[SOCK_STREAM] = अणु
		[TOMOYO_NETWORK_BIND]    = TOMOYO_MAC_NETWORK_INET_STREAM_BIND,
		[TOMOYO_NETWORK_LISTEN]  =
		TOMOYO_MAC_NETWORK_INET_STREAM_LISTEN,
		[TOMOYO_NETWORK_CONNECT] =
		TOMOYO_MAC_NETWORK_INET_STREAM_CONNECT,
	पूर्ण,
	[SOCK_DGRAM] = अणु
		[TOMOYO_NETWORK_BIND]    = TOMOYO_MAC_NETWORK_INET_DGRAM_BIND,
		[TOMOYO_NETWORK_SEND]    = TOMOYO_MAC_NETWORK_INET_DGRAM_SEND,
	पूर्ण,
	[SOCK_RAW]    = अणु
		[TOMOYO_NETWORK_BIND]    = TOMOYO_MAC_NETWORK_INET_RAW_BIND,
		[TOMOYO_NETWORK_SEND]    = TOMOYO_MAC_NETWORK_INET_RAW_SEND,
	पूर्ण,
पूर्ण;

/*
 * Mapping table from "enum tomoyo_network_acl_index" to
 * "enum tomoyo_mac_index" क्रम unix करोमुख्य socket.
 */
अटल स्थिर u8 tomoyo_unix2mac
[TOMOYO_SOCK_MAX][TOMOYO_MAX_NETWORK_OPERATION] = अणु
	[SOCK_STREAM] = अणु
		[TOMOYO_NETWORK_BIND]    = TOMOYO_MAC_NETWORK_UNIX_STREAM_BIND,
		[TOMOYO_NETWORK_LISTEN]  =
		TOMOYO_MAC_NETWORK_UNIX_STREAM_LISTEN,
		[TOMOYO_NETWORK_CONNECT] =
		TOMOYO_MAC_NETWORK_UNIX_STREAM_CONNECT,
	पूर्ण,
	[SOCK_DGRAM] = अणु
		[TOMOYO_NETWORK_BIND]    = TOMOYO_MAC_NETWORK_UNIX_DGRAM_BIND,
		[TOMOYO_NETWORK_SEND]    = TOMOYO_MAC_NETWORK_UNIX_DGRAM_SEND,
	पूर्ण,
	[SOCK_SEQPACKET] = अणु
		[TOMOYO_NETWORK_BIND]    =
		TOMOYO_MAC_NETWORK_UNIX_SEQPACKET_BIND,
		[TOMOYO_NETWORK_LISTEN]  =
		TOMOYO_MAC_NETWORK_UNIX_SEQPACKET_LISTEN,
		[TOMOYO_NETWORK_CONNECT] =
		TOMOYO_MAC_NETWORK_UNIX_SEQPACKET_CONNECT,
	पूर्ण,
पूर्ण;

/**
 * tomoyo_same_inet_acl - Check क्रम duplicated "struct tomoyo_inet_acl" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_acl_info".
 * @b: Poपूर्णांकer to "struct tomoyo_acl_info".
 *
 * Returns true अगर @a == @b except permission bits, false otherwise.
 */
अटल bool tomoyo_same_inet_acl(स्थिर काष्ठा tomoyo_acl_info *a,
				 स्थिर काष्ठा tomoyo_acl_info *b)
अणु
	स्थिर काष्ठा tomoyo_inet_acl *p1 = container_of(a, typeof(*p1), head);
	स्थिर काष्ठा tomoyo_inet_acl *p2 = container_of(b, typeof(*p2), head);

	वापस p1->protocol == p2->protocol &&
		tomoyo_same_ipaddr_जोड़(&p1->address, &p2->address) &&
		tomoyo_same_number_जोड़(&p1->port, &p2->port);
पूर्ण

/**
 * tomoyo_same_unix_acl - Check क्रम duplicated "struct tomoyo_unix_acl" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_acl_info".
 * @b: Poपूर्णांकer to "struct tomoyo_acl_info".
 *
 * Returns true अगर @a == @b except permission bits, false otherwise.
 */
अटल bool tomoyo_same_unix_acl(स्थिर काष्ठा tomoyo_acl_info *a,
				 स्थिर काष्ठा tomoyo_acl_info *b)
अणु
	स्थिर काष्ठा tomoyo_unix_acl *p1 = container_of(a, typeof(*p1), head);
	स्थिर काष्ठा tomoyo_unix_acl *p2 = container_of(b, typeof(*p2), head);

	वापस p1->protocol == p2->protocol &&
		tomoyo_same_name_जोड़(&p1->name, &p2->name);
पूर्ण

/**
 * tomoyo_merge_inet_acl - Merge duplicated "struct tomoyo_inet_acl" entry.
 *
 * @a:         Poपूर्णांकer to "struct tomoyo_acl_info".
 * @b:         Poपूर्णांकer to "struct tomoyo_acl_info".
 * @is_delete: True क्रम @a &= ~@b, false क्रम @a |= @b.
 *
 * Returns true अगर @a is empty, false otherwise.
 */
अटल bool tomoyo_merge_inet_acl(काष्ठा tomoyo_acl_info *a,
				  काष्ठा tomoyo_acl_info *b,
				  स्थिर bool is_delete)
अणु
	u8 * स्थिर a_perm =
		&container_of(a, काष्ठा tomoyo_inet_acl, head)->perm;
	u8 perm = READ_ONCE(*a_perm);
	स्थिर u8 b_perm = container_of(b, काष्ठा tomoyo_inet_acl, head)->perm;

	अगर (is_delete)
		perm &= ~b_perm;
	अन्यथा
		perm |= b_perm;
	WRITE_ONCE(*a_perm, perm);
	वापस !perm;
पूर्ण

/**
 * tomoyo_merge_unix_acl - Merge duplicated "struct tomoyo_unix_acl" entry.
 *
 * @a:         Poपूर्णांकer to "struct tomoyo_acl_info".
 * @b:         Poपूर्णांकer to "struct tomoyo_acl_info".
 * @is_delete: True क्रम @a &= ~@b, false क्रम @a |= @b.
 *
 * Returns true अगर @a is empty, false otherwise.
 */
अटल bool tomoyo_merge_unix_acl(काष्ठा tomoyo_acl_info *a,
				  काष्ठा tomoyo_acl_info *b,
				  स्थिर bool is_delete)
अणु
	u8 * स्थिर a_perm =
		&container_of(a, काष्ठा tomoyo_unix_acl, head)->perm;
	u8 perm = READ_ONCE(*a_perm);
	स्थिर u8 b_perm = container_of(b, काष्ठा tomoyo_unix_acl, head)->perm;

	अगर (is_delete)
		perm &= ~b_perm;
	अन्यथा
		perm |= b_perm;
	WRITE_ONCE(*a_perm, perm);
	वापस !perm;
पूर्ण

/**
 * tomoyo_ग_लिखो_inet_network - Write "struct tomoyo_inet_acl" list.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
पूर्णांक tomoyo_ग_लिखो_inet_network(काष्ठा tomoyo_acl_param *param)
अणु
	काष्ठा tomoyo_inet_acl e = अणु .head.type = TOMOYO_TYPE_INET_ACL पूर्ण;
	पूर्णांक error = -EINVAL;
	u8 type;
	स्थिर अक्षर *protocol = tomoyo_पढ़ो_token(param);
	स्थिर अक्षर *operation = tomoyo_पढ़ो_token(param);

	क्रम (e.protocol = 0; e.protocol < TOMOYO_SOCK_MAX; e.protocol++)
		अगर (!म_भेद(protocol, tomoyo_proto_keyword[e.protocol]))
			अवरोध;
	क्रम (type = 0; type < TOMOYO_MAX_NETWORK_OPERATION; type++)
		अगर (tomoyo_permstr(operation, tomoyo_socket_keyword[type]))
			e.perm |= 1 << type;
	अगर (e.protocol == TOMOYO_SOCK_MAX || !e.perm)
		वापस -EINVAL;
	अगर (param->data[0] == '@') अणु
		param->data++;
		e.address.group =
			tomoyo_get_group(param, TOMOYO_ADDRESS_GROUP);
		अगर (!e.address.group)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		अगर (!tomoyo_parse_ipaddr_जोड़(param, &e.address))
			जाओ out;
	पूर्ण
	अगर (!tomoyo_parse_number_जोड़(param, &e.port) ||
	    e.port.values[1] > 65535)
		जाओ out;
	error = tomoyo_update_करोमुख्य(&e.head, माप(e), param,
				     tomoyo_same_inet_acl,
				     tomoyo_merge_inet_acl);
out:
	tomoyo_put_group(e.address.group);
	tomoyo_put_number_जोड़(&e.port);
	वापस error;
पूर्ण

/**
 * tomoyo_ग_लिखो_unix_network - Write "struct tomoyo_unix_acl" list.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 *
 * Returns 0 on success, negative value otherwise.
 */
पूर्णांक tomoyo_ग_लिखो_unix_network(काष्ठा tomoyo_acl_param *param)
अणु
	काष्ठा tomoyo_unix_acl e = अणु .head.type = TOMOYO_TYPE_UNIX_ACL पूर्ण;
	पूर्णांक error;
	u8 type;
	स्थिर अक्षर *protocol = tomoyo_पढ़ो_token(param);
	स्थिर अक्षर *operation = tomoyo_पढ़ो_token(param);

	क्रम (e.protocol = 0; e.protocol < TOMOYO_SOCK_MAX; e.protocol++)
		अगर (!म_भेद(protocol, tomoyo_proto_keyword[e.protocol]))
			अवरोध;
	क्रम (type = 0; type < TOMOYO_MAX_NETWORK_OPERATION; type++)
		अगर (tomoyo_permstr(operation, tomoyo_socket_keyword[type]))
			e.perm |= 1 << type;
	अगर (e.protocol == TOMOYO_SOCK_MAX || !e.perm)
		वापस -EINVAL;
	अगर (!tomoyo_parse_name_जोड़(param, &e.name))
		वापस -EINVAL;
	error = tomoyo_update_करोमुख्य(&e.head, माप(e), param,
				     tomoyo_same_unix_acl,
				     tomoyo_merge_unix_acl);
	tomoyo_put_name_जोड़(&e.name);
	वापस error;
पूर्ण

/**
 * tomoyo_audit_net_log - Audit network log.
 *
 * @r:         Poपूर्णांकer to "struct tomoyo_request_info".
 * @family:    Name of socket family ("inet" or "unix").
 * @protocol:  Name of protocol in @family.
 * @operation: Name of socket operation.
 * @address:   Name of address.
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_audit_net_log(काष्ठा tomoyo_request_info *r,
				स्थिर अक्षर *family, स्थिर u8 protocol,
				स्थिर u8 operation, स्थिर अक्षर *address)
अणु
	वापस tomoyo_supervisor(r, "network %s %s %s %s\n", family,
				 tomoyo_proto_keyword[protocol],
				 tomoyo_socket_keyword[operation], address);
पूर्ण

/**
 * tomoyo_audit_inet_log - Audit INET network log.
 *
 * @r: Poपूर्णांकer to "struct tomoyo_request_info".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_audit_inet_log(काष्ठा tomoyo_request_info *r)
अणु
	अक्षर buf[128];
	पूर्णांक len;
	स्थिर __be32 *address = r->param.inet_network.address;

	अगर (r->param.inet_network.is_ipv6)
		tomoyo_prपूर्णांक_ipv6(buf, माप(buf), (स्थिर काष्ठा in6_addr *)
				  address, (स्थिर काष्ठा in6_addr *) address);
	अन्यथा
		tomoyo_prपूर्णांक_ipv4(buf, माप(buf), address, address);
	len = म_माप(buf);
	snम_लिखो(buf + len, माप(buf) - len, " %u",
		 r->param.inet_network.port);
	वापस tomoyo_audit_net_log(r, "inet", r->param.inet_network.protocol,
				    r->param.inet_network.operation, buf);
पूर्ण

/**
 * tomoyo_audit_unix_log - Audit UNIX network log.
 *
 * @r: Poपूर्णांकer to "struct tomoyo_request_info".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_audit_unix_log(काष्ठा tomoyo_request_info *r)
अणु
	वापस tomoyo_audit_net_log(r, "unix", r->param.unix_network.protocol,
				    r->param.unix_network.operation,
				    r->param.unix_network.address->name);
पूर्ण

/**
 * tomoyo_check_inet_acl - Check permission क्रम inet करोमुख्य socket operation.
 *
 * @r:   Poपूर्णांकer to "struct tomoyo_request_info".
 * @ptr: Poपूर्णांकer to "struct tomoyo_acl_info".
 *
 * Returns true अगर granted, false otherwise.
 */
अटल bool tomoyo_check_inet_acl(काष्ठा tomoyo_request_info *r,
				  स्थिर काष्ठा tomoyo_acl_info *ptr)
अणु
	स्थिर काष्ठा tomoyo_inet_acl *acl =
		container_of(ptr, typeof(*acl), head);
	स्थिर u8 size = r->param.inet_network.is_ipv6 ? 16 : 4;

	अगर (!(acl->perm & (1 << r->param.inet_network.operation)) ||
	    !tomoyo_compare_number_जोड़(r->param.inet_network.port,
					 &acl->port))
		वापस false;
	अगर (acl->address.group)
		वापस tomoyo_address_matches_group
			(r->param.inet_network.is_ipv6,
			 r->param.inet_network.address, acl->address.group);
	वापस acl->address.is_ipv6 == r->param.inet_network.is_ipv6 &&
		स_भेद(&acl->address.ip[0],
		       r->param.inet_network.address, size) <= 0 &&
		स_भेद(r->param.inet_network.address,
		       &acl->address.ip[1], size) <= 0;
पूर्ण

/**
 * tomoyo_check_unix_acl - Check permission क्रम unix करोमुख्य socket operation.
 *
 * @r:   Poपूर्णांकer to "struct tomoyo_request_info".
 * @ptr: Poपूर्णांकer to "struct tomoyo_acl_info".
 *
 * Returns true अगर granted, false otherwise.
 */
अटल bool tomoyo_check_unix_acl(काष्ठा tomoyo_request_info *r,
				  स्थिर काष्ठा tomoyo_acl_info *ptr)
अणु
	स्थिर काष्ठा tomoyo_unix_acl *acl =
		container_of(ptr, typeof(*acl), head);

	वापस (acl->perm & (1 << r->param.unix_network.operation)) &&
		tomoyo_compare_name_जोड़(r->param.unix_network.address,
					  &acl->name);
पूर्ण

/**
 * tomoyo_inet_entry - Check permission क्रम INET network operation.
 *
 * @address: Poपूर्णांकer to "struct tomoyo_addr_info".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_inet_entry(स्थिर काष्ठा tomoyo_addr_info *address)
अणु
	स्थिर पूर्णांक idx = tomoyo_पढ़ो_lock();
	काष्ठा tomoyo_request_info r;
	पूर्णांक error = 0;
	स्थिर u8 type = tomoyo_inet2mac[address->protocol][address->operation];

	अगर (type && tomoyo_init_request_info(&r, शून्य, type)
	    != TOMOYO_CONFIG_DISABLED) अणु
		r.param_type = TOMOYO_TYPE_INET_ACL;
		r.param.inet_network.protocol = address->protocol;
		r.param.inet_network.operation = address->operation;
		r.param.inet_network.is_ipv6 = address->inet.is_ipv6;
		r.param.inet_network.address = address->inet.address;
		r.param.inet_network.port = ntohs(address->inet.port);
		करो अणु
			tomoyo_check_acl(&r, tomoyo_check_inet_acl);
			error = tomoyo_audit_inet_log(&r);
		पूर्ण जबतक (error == TOMOYO_RETRY_REQUEST);
	पूर्ण
	tomoyo_पढ़ो_unlock(idx);
	वापस error;
पूर्ण

/**
 * tomoyo_check_inet_address - Check permission क्रम inet करोमुख्य socket's operation.
 *
 * @addr:     Poपूर्णांकer to "struct sockaddr".
 * @addr_len: Size of @addr.
 * @port:     Port number.
 * @address:  Poपूर्णांकer to "struct tomoyo_addr_info".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_check_inet_address(स्थिर काष्ठा sockaddr *addr,
				     स्थिर अचिन्हित पूर्णांक addr_len,
				     स्थिर u16 port,
				     काष्ठा tomoyo_addr_info *address)
अणु
	काष्ठा tomoyo_inet_addr_info *i = &address->inet;

	अगर (addr_len < दुरत्वend(काष्ठा sockaddr, sa_family))
		वापस 0;
	चयन (addr->sa_family) अणु
	हाल AF_INET6:
		अगर (addr_len < SIN6_LEN_RFC2133)
			जाओ skip;
		i->is_ipv6 = true;
		i->address = (__be32 *)
			((काष्ठा sockaddr_in6 *) addr)->sin6_addr.s6_addr;
		i->port = ((काष्ठा sockaddr_in6 *) addr)->sin6_port;
		अवरोध;
	हाल AF_INET:
		अगर (addr_len < माप(काष्ठा sockaddr_in))
			जाओ skip;
		i->is_ipv6 = false;
		i->address = (__be32 *)
			&((काष्ठा sockaddr_in *) addr)->sin_addr;
		i->port = ((काष्ठा sockaddr_in *) addr)->sin_port;
		अवरोध;
	शेष:
		जाओ skip;
	पूर्ण
	अगर (address->protocol == SOCK_RAW)
		i->port = htons(port);
	वापस tomoyo_inet_entry(address);
skip:
	वापस 0;
पूर्ण

/**
 * tomoyo_unix_entry - Check permission क्रम UNIX network operation.
 *
 * @address: Poपूर्णांकer to "struct tomoyo_addr_info".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_unix_entry(स्थिर काष्ठा tomoyo_addr_info *address)
अणु
	स्थिर पूर्णांक idx = tomoyo_पढ़ो_lock();
	काष्ठा tomoyo_request_info r;
	पूर्णांक error = 0;
	स्थिर u8 type = tomoyo_unix2mac[address->protocol][address->operation];

	अगर (type && tomoyo_init_request_info(&r, शून्य, type)
	    != TOMOYO_CONFIG_DISABLED) अणु
		अक्षर *buf = address->unix0.addr;
		पूर्णांक len = address->unix0.addr_len - माप(sa_family_t);

		अगर (len <= 0) अणु
			buf = "anonymous";
			len = 9;
		पूर्ण अन्यथा अगर (buf[0]) अणु
			len = strnlen(buf, len);
		पूर्ण
		buf = tomoyo_encode2(buf, len);
		अगर (buf) अणु
			काष्ठा tomoyo_path_info addr;

			addr.name = buf;
			tomoyo_fill_path_info(&addr);
			r.param_type = TOMOYO_TYPE_UNIX_ACL;
			r.param.unix_network.protocol = address->protocol;
			r.param.unix_network.operation = address->operation;
			r.param.unix_network.address = &addr;
			करो अणु
				tomoyo_check_acl(&r, tomoyo_check_unix_acl);
				error = tomoyo_audit_unix_log(&r);
			पूर्ण जबतक (error == TOMOYO_RETRY_REQUEST);
			kमुक्त(buf);
		पूर्ण अन्यथा
			error = -ENOMEM;
	पूर्ण
	tomoyo_पढ़ो_unlock(idx);
	वापस error;
पूर्ण

/**
 * tomoyo_check_unix_address - Check permission क्रम unix करोमुख्य socket's operation.
 *
 * @addr:     Poपूर्णांकer to "struct sockaddr".
 * @addr_len: Size of @addr.
 * @address:  Poपूर्णांकer to "struct tomoyo_addr_info".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_check_unix_address(काष्ठा sockaddr *addr,
				     स्थिर अचिन्हित पूर्णांक addr_len,
				     काष्ठा tomoyo_addr_info *address)
अणु
	काष्ठा tomoyo_unix_addr_info *u = &address->unix0;

	अगर (addr_len < दुरत्वend(काष्ठा sockaddr, sa_family))
		वापस 0;
	अगर (addr->sa_family != AF_UNIX)
		वापस 0;
	u->addr = ((काष्ठा sockaddr_un *) addr)->sun_path;
	u->addr_len = addr_len;
	वापस tomoyo_unix_entry(address);
पूर्ण

/**
 * tomoyo_kernel_service - Check whether I'm kernel service or not.
 *
 * Returns true अगर I'm kernel service, false otherwise.
 */
अटल bool tomoyo_kernel_service(व्योम)
अणु
	/* Nothing to करो अगर I am a kernel service. */
	वापस current->flags & PF_KTHREAD;
पूर्ण

/**
 * tomoyo_sock_family - Get socket's family.
 *
 * @sk: Poपूर्णांकer to "struct sock".
 *
 * Returns one of PF_INET, PF_INET6, PF_UNIX or 0.
 */
अटल u8 tomoyo_sock_family(काष्ठा sock *sk)
अणु
	u8 family;

	अगर (tomoyo_kernel_service())
		वापस 0;
	family = sk->sk_family;
	चयन (family) अणु
	हाल PF_INET:
	हाल PF_INET6:
	हाल PF_UNIX:
		वापस family;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/**
 * tomoyo_socket_listen_permission - Check permission क्रम listening a socket.
 *
 * @sock: Poपूर्णांकer to "struct socket".
 *
 * Returns 0 on success, negative value otherwise.
 */
पूर्णांक tomoyo_socket_listen_permission(काष्ठा socket *sock)
अणु
	काष्ठा tomoyo_addr_info address;
	स्थिर u8 family = tomoyo_sock_family(sock->sk);
	स्थिर अचिन्हित पूर्णांक type = sock->type;
	काष्ठा sockaddr_storage addr;
	पूर्णांक addr_len;

	अगर (!family || (type != SOCK_STREAM && type != SOCK_SEQPACKET))
		वापस 0;
	अणु
		स्थिर पूर्णांक error = sock->ops->getname(sock, (काष्ठा sockaddr *)
						     &addr, 0);

		अगर (error < 0)
			वापस error;
		addr_len = error;
	पूर्ण
	address.protocol = type;
	address.operation = TOMOYO_NETWORK_LISTEN;
	अगर (family == PF_UNIX)
		वापस tomoyo_check_unix_address((काष्ठा sockaddr *) &addr,
						 addr_len, &address);
	वापस tomoyo_check_inet_address((काष्ठा sockaddr *) &addr, addr_len,
					 0, &address);
पूर्ण

/**
 * tomoyo_socket_connect_permission - Check permission क्रम setting the remote address of a socket.
 *
 * @sock:     Poपूर्णांकer to "struct socket".
 * @addr:     Poपूर्णांकer to "struct sockaddr".
 * @addr_len: Size of @addr.
 *
 * Returns 0 on success, negative value otherwise.
 */
पूर्णांक tomoyo_socket_connect_permission(काष्ठा socket *sock,
				     काष्ठा sockaddr *addr, पूर्णांक addr_len)
अणु
	काष्ठा tomoyo_addr_info address;
	स्थिर u8 family = tomoyo_sock_family(sock->sk);
	स्थिर अचिन्हित पूर्णांक type = sock->type;

	अगर (!family)
		वापस 0;
	address.protocol = type;
	चयन (type) अणु
	हाल SOCK_DGRAM:
	हाल SOCK_RAW:
		address.operation = TOMOYO_NETWORK_SEND;
		अवरोध;
	हाल SOCK_STREAM:
	हाल SOCK_SEQPACKET:
		address.operation = TOMOYO_NETWORK_CONNECT;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	अगर (family == PF_UNIX)
		वापस tomoyo_check_unix_address(addr, addr_len, &address);
	वापस tomoyo_check_inet_address(addr, addr_len, sock->sk->sk_protocol,
					 &address);
पूर्ण

/**
 * tomoyo_socket_bind_permission - Check permission क्रम setting the local address of a socket.
 *
 * @sock:     Poपूर्णांकer to "struct socket".
 * @addr:     Poपूर्णांकer to "struct sockaddr".
 * @addr_len: Size of @addr.
 *
 * Returns 0 on success, negative value otherwise.
 */
पूर्णांक tomoyo_socket_bind_permission(काष्ठा socket *sock, काष्ठा sockaddr *addr,
				  पूर्णांक addr_len)
अणु
	काष्ठा tomoyo_addr_info address;
	स्थिर u8 family = tomoyo_sock_family(sock->sk);
	स्थिर अचिन्हित पूर्णांक type = sock->type;

	अगर (!family)
		वापस 0;
	चयन (type) अणु
	हाल SOCK_STREAM:
	हाल SOCK_DGRAM:
	हाल SOCK_RAW:
	हाल SOCK_SEQPACKET:
		address.protocol = type;
		address.operation = TOMOYO_NETWORK_BIND;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	अगर (family == PF_UNIX)
		वापस tomoyo_check_unix_address(addr, addr_len, &address);
	वापस tomoyo_check_inet_address(addr, addr_len, sock->sk->sk_protocol,
					 &address);
पूर्ण

/**
 * tomoyo_socket_sendmsg_permission - Check permission क्रम sending a datagram.
 *
 * @sock: Poपूर्णांकer to "struct socket".
 * @msg:  Poपूर्णांकer to "struct msghdr".
 * @size: Unused.
 *
 * Returns 0 on success, negative value otherwise.
 */
पूर्णांक tomoyo_socket_sendmsg_permission(काष्ठा socket *sock, काष्ठा msghdr *msg,
				     पूर्णांक size)
अणु
	काष्ठा tomoyo_addr_info address;
	स्थिर u8 family = tomoyo_sock_family(sock->sk);
	स्थिर अचिन्हित पूर्णांक type = sock->type;

	अगर (!msg->msg_name || !family ||
	    (type != SOCK_DGRAM && type != SOCK_RAW))
		वापस 0;
	address.protocol = type;
	address.operation = TOMOYO_NETWORK_SEND;
	अगर (family == PF_UNIX)
		वापस tomoyo_check_unix_address((काष्ठा sockaddr *)
						 msg->msg_name,
						 msg->msg_namelen, &address);
	वापस tomoyo_check_inet_address((काष्ठा sockaddr *) msg->msg_name,
					 msg->msg_namelen,
					 sock->sk->sk_protocol, &address);
पूर्ण
