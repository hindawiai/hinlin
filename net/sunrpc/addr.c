<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2009, Oracle.  All rights reserved.
 *
 * Convert socket addresses to presentation addresses and universal
 * addresses, and vice versa.
 *
 * Universal addresses are पूर्णांकroduced by RFC 1833 and further refined by
 * recent RFCs describing NFSv4.  The universal address क्रमmat is part
 * of the बाह्यal (network) पूर्णांकerface provided by rpcbind version 3
 * and 4, and by NFSv4.  Such an address is a string containing a
 * presentation क्रमmat IP address followed by a port number in
 * "hibyte.lobyte" क्रमmat.
 *
 * IPv6 addresses can also include a scope ID, typically denoted by
 * a '%' followed by a device name or a non-negative पूर्णांकeger.  Refer to
 * RFC 4291, Section 2.2 क्रम details on IPv6 presentation क्रमmats.
 */

#समावेश <net/ipv6.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/msg_prot.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#अगर IS_ENABLED(CONFIG_IPV6)

अटल माप_प्रकार rpc_ntop6_noscopeid(स्थिर काष्ठा sockaddr *sap,
				  अक्षर *buf, स्थिर पूर्णांक buflen)
अणु
	स्थिर काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)sap;
	स्थिर काष्ठा in6_addr *addr = &sin6->sin6_addr;

	/*
	 * RFC 4291, Section 2.2.2
	 *
	 * Shorthanded ANY address
	 */
	अगर (ipv6_addr_any(addr))
		वापस snम_लिखो(buf, buflen, "::");

	/*
	 * RFC 4291, Section 2.2.2
	 *
	 * Shorthanded loopback address
	 */
	अगर (ipv6_addr_loopback(addr))
		वापस snम_लिखो(buf, buflen, "::1");

	/*
	 * RFC 4291, Section 2.2.3
	 *
	 * Special presentation address क्रमmat क्रम mapped v4
	 * addresses.
	 */
	अगर (ipv6_addr_v4mapped(addr))
		वापस snम_लिखो(buf, buflen, "::ffff:%pI4",
					&addr->s6_addr32[3]);

	/*
	 * RFC 4291, Section 2.2.1
	 */
	वापस snम_लिखो(buf, buflen, "%pI6c", addr);
पूर्ण

अटल माप_प्रकार rpc_ntop6(स्थिर काष्ठा sockaddr *sap,
			अक्षर *buf, स्थिर माप_प्रकार buflen)
अणु
	स्थिर काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)sap;
	अक्षर scopebuf[IPV6_SCOPE_ID_LEN];
	माप_प्रकार len;
	पूर्णांक rc;

	len = rpc_ntop6_noscopeid(sap, buf, buflen);
	अगर (unlikely(len == 0))
		वापस len;

	अगर (!(ipv6_addr_type(&sin6->sin6_addr) & IPV6_ADDR_LINKLOCAL))
		वापस len;
	अगर (sin6->sin6_scope_id == 0)
		वापस len;

	rc = snम_लिखो(scopebuf, माप(scopebuf), "%c%u",
			IPV6_SCOPE_DELIMITER, sin6->sin6_scope_id);
	अगर (unlikely((माप_प्रकार)rc >= माप(scopebuf)))
		वापस 0;

	len += rc;
	अगर (unlikely(len >= buflen))
		वापस 0;

	म_जोड़ो(buf, scopebuf);
	वापस len;
पूर्ण

#अन्यथा	/* !IS_ENABLED(CONFIG_IPV6) */

अटल माप_प्रकार rpc_ntop6_noscopeid(स्थिर काष्ठा sockaddr *sap,
				  अक्षर *buf, स्थिर पूर्णांक buflen)
अणु
	वापस 0;
पूर्ण

अटल माप_प्रकार rpc_ntop6(स्थिर काष्ठा sockaddr *sap,
			अक्षर *buf, स्थिर माप_प्रकार buflen)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर	/* !IS_ENABLED(CONFIG_IPV6) */

अटल पूर्णांक rpc_ntop4(स्थिर काष्ठा sockaddr *sap,
		     अक्षर *buf, स्थिर माप_प्रकार buflen)
अणु
	स्थिर काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)sap;

	वापस snम_लिखो(buf, buflen, "%pI4", &sin->sin_addr);
पूर्ण

/**
 * rpc_ntop - स्थिरruct a presentation address in @buf
 * @sap: socket address
 * @buf: स्थिरruction area
 * @buflen: size of @buf, in bytes
 *
 * Plants a %NUL-terminated string in @buf and वापसs the length
 * of the string, excluding the %NUL.  Otherwise zero is वापसed.
 */
माप_प्रकार rpc_ntop(स्थिर काष्ठा sockaddr *sap, अक्षर *buf, स्थिर माप_प्रकार buflen)
अणु
	चयन (sap->sa_family) अणु
	हाल AF_INET:
		वापस rpc_ntop4(sap, buf, buflen);
	हाल AF_INET6:
		वापस rpc_ntop6(sap, buf, buflen);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_ntop);

अटल माप_प्रकार rpc_pton4(स्थिर अक्षर *buf, स्थिर माप_प्रकार buflen,
			काष्ठा sockaddr *sap, स्थिर माप_प्रकार salen)
अणु
	काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)sap;
	u8 *addr = (u8 *)&sin->sin_addr.s_addr;

	अगर (buflen > INET_ADDRSTRLEN || salen < माप(काष्ठा sockaddr_in))
		वापस 0;

	स_रखो(sap, 0, माप(काष्ठा sockaddr_in));

	अगर (in4_pton(buf, buflen, addr, '\0', शून्य) == 0)
		वापस 0;

	sin->sin_family = AF_INET;
	वापस माप(काष्ठा sockaddr_in);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक rpc_parse_scope_id(काष्ठा net *net, स्थिर अक्षर *buf,
			      स्थिर माप_प्रकार buflen, स्थिर अक्षर *delim,
			      काष्ठा sockaddr_in6 *sin6)
अणु
	अक्षर *p;
	माप_प्रकार len;

	अगर ((buf + buflen) == delim)
		वापस 1;

	अगर (*delim != IPV6_SCOPE_DELIMITER)
		वापस 0;

	अगर (!(ipv6_addr_type(&sin6->sin6_addr) & IPV6_ADDR_LINKLOCAL))
		वापस 0;

	len = (buf + buflen) - delim - 1;
	p = kmemdup_nul(delim + 1, len, GFP_KERNEL);
	अगर (p) अणु
		u32 scope_id = 0;
		काष्ठा net_device *dev;

		dev = dev_get_by_name(net, p);
		अगर (dev != शून्य) अणु
			scope_id = dev->अगरindex;
			dev_put(dev);
		पूर्ण अन्यथा अणु
			अगर (kstrtou32(p, 10, &scope_id) != 0) अणु
				kमुक्त(p);
				वापस 0;
			पूर्ण
		पूर्ण

		kमुक्त(p);

		sin6->sin6_scope_id = scope_id;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल माप_प्रकार rpc_pton6(काष्ठा net *net, स्थिर अक्षर *buf, स्थिर माप_प्रकार buflen,
			काष्ठा sockaddr *sap, स्थिर माप_प्रकार salen)
अणु
	काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)sap;
	u8 *addr = (u8 *)&sin6->sin6_addr.in6_u;
	स्थिर अक्षर *delim;

	अगर (buflen > (INET6_ADDRSTRLEN + IPV6_SCOPE_ID_LEN) ||
	    salen < माप(काष्ठा sockaddr_in6))
		वापस 0;

	स_रखो(sap, 0, माप(काष्ठा sockaddr_in6));

	अगर (in6_pton(buf, buflen, addr, IPV6_SCOPE_DELIMITER, &delim) == 0)
		वापस 0;

	अगर (!rpc_parse_scope_id(net, buf, buflen, delim, sin6))
		वापस 0;

	sin6->sin6_family = AF_INET6;
	वापस माप(काष्ठा sockaddr_in6);
पूर्ण
#अन्यथा
अटल माप_प्रकार rpc_pton6(काष्ठा net *net, स्थिर अक्षर *buf, स्थिर माप_प्रकार buflen,
			काष्ठा sockaddr *sap, स्थिर माप_प्रकार salen)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/**
 * rpc_pton - Conकाष्ठा a sockaddr in @sap
 * @net: applicable network namespace
 * @buf: C string containing presentation क्रमmat IP address
 * @buflen: length of presentation address in bytes
 * @sap: buffer पूर्णांकo which to plant socket address
 * @salen: size of buffer in bytes
 *
 * Returns the size of the socket address अगर successful; otherwise
 * zero is वापसed.
 *
 * Plants a socket address in @sap and वापसs the size of the
 * socket address, अगर successful.  Returns zero अगर an error
 * occurred.
 */
माप_प्रकार rpc_pton(काष्ठा net *net, स्थिर अक्षर *buf, स्थिर माप_प्रकार buflen,
		काष्ठा sockaddr *sap, स्थिर माप_प्रकार salen)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < buflen; i++)
		अगर (buf[i] == ':')
			वापस rpc_pton6(net, buf, buflen, sap, salen);
	वापस rpc_pton4(buf, buflen, sap, salen);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_pton);

/**
 * rpc_sockaddr2uaddr - Conकाष्ठा a universal address string from @sap.
 * @sap: socket address
 * @gfp_flags: allocation mode
 *
 * Returns a %NUL-terminated string in dynamically allocated memory;
 * otherwise शून्य is वापसed अगर an error occurred.  Caller must
 * मुक्त the वापसed string.
 */
अक्षर *rpc_sockaddr2uaddr(स्थिर काष्ठा sockaddr *sap, gfp_t gfp_flags)
अणु
	अक्षर portbuf[RPCBIND_MAXUADDRPLEN];
	अक्षर addrbuf[RPCBIND_MAXUADDRLEN];
	अचिन्हित लघु port;

	चयन (sap->sa_family) अणु
	हाल AF_INET:
		अगर (rpc_ntop4(sap, addrbuf, माप(addrbuf)) == 0)
			वापस शून्य;
		port = ntohs(((काष्ठा sockaddr_in *)sap)->sin_port);
		अवरोध;
	हाल AF_INET6:
		अगर (rpc_ntop6_noscopeid(sap, addrbuf, माप(addrbuf)) == 0)
			वापस शून्य;
		port = ntohs(((काष्ठा sockaddr_in6 *)sap)->sin6_port);
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	अगर (snम_लिखो(portbuf, माप(portbuf),
		     ".%u.%u", port >> 8, port & 0xff) > (पूर्णांक)माप(portbuf))
		वापस शून्य;

	अगर (strlcat(addrbuf, portbuf, माप(addrbuf)) > माप(addrbuf))
		वापस शून्य;

	वापस kstrdup(addrbuf, gfp_flags);
पूर्ण

/**
 * rpc_uaddr2sockaddr - convert a universal address to a socket address.
 * @net: applicable network namespace
 * @uaddr: C string containing universal address to convert
 * @uaddr_len: length of universal address string
 * @sap: buffer पूर्णांकo which to plant socket address
 * @salen: size of buffer
 *
 * @uaddr करोes not have to be '\0'-terminated, but kstrtou8() and
 * rpc_pton() require proper string termination to be successful.
 *
 * Returns the size of the socket address अगर successful; otherwise
 * zero is वापसed.
 */
माप_प्रकार rpc_uaddr2sockaddr(काष्ठा net *net, स्थिर अक्षर *uaddr,
			  स्थिर माप_प्रकार uaddr_len, काष्ठा sockaddr *sap,
			  स्थिर माप_प्रकार salen)
अणु
	अक्षर *c, buf[RPCBIND_MAXUADDRLEN + माप('\0')];
	u8 portlo, porthi;
	अचिन्हित लघु port;

	अगर (uaddr_len > RPCBIND_MAXUADDRLEN)
		वापस 0;

	स_नकल(buf, uaddr, uaddr_len);

	buf[uaddr_len] = '\0';
	c = म_खोजप(buf, '.');
	अगर (unlikely(c == शून्य))
		वापस 0;
	अगर (unlikely(kstrtou8(c + 1, 10, &portlo) != 0))
		वापस 0;

	*c = '\0';
	c = म_खोजप(buf, '.');
	अगर (unlikely(c == शून्य))
		वापस 0;
	अगर (unlikely(kstrtou8(c + 1, 10, &porthi) != 0))
		वापस 0;

	port = (अचिन्हित लघु)((porthi << 8) | portlo);

	*c = '\0';
	अगर (rpc_pton(net, buf, म_माप(buf), sap, salen) == 0)
		वापस 0;

	चयन (sap->sa_family) अणु
	हाल AF_INET:
		((काष्ठा sockaddr_in *)sap)->sin_port = htons(port);
		वापस माप(काष्ठा sockaddr_in);
	हाल AF_INET6:
		((काष्ठा sockaddr_in6 *)sap)->sin6_port = htons(port);
		वापस माप(काष्ठा sockaddr_in6);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_uaddr2sockaddr);
