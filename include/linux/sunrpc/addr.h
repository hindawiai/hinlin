<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/sunrpc/addr.h
 *
 * Various routines क्रम copying and comparing sockaddrs and क्रम
 * converting them to and from presentation क्रमmat.
 */
#अगर_अघोषित _LINUX_SUNRPC_ADDR_H
#घोषणा _LINUX_SUNRPC_ADDR_H

#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <net/ipv6.h>

माप_प्रकार		rpc_ntop(स्थिर काष्ठा sockaddr *, अक्षर *, स्थिर माप_प्रकार);
माप_प्रकार		rpc_pton(काष्ठा net *, स्थिर अक्षर *, स्थिर माप_प्रकार,
			 काष्ठा sockaddr *, स्थिर माप_प्रकार);
अक्षर *		rpc_sockaddr2uaddr(स्थिर काष्ठा sockaddr *, gfp_t);
माप_प्रकार		rpc_uaddr2sockaddr(काष्ठा net *, स्थिर अक्षर *, स्थिर माप_प्रकार,
				   काष्ठा sockaddr *, स्थिर माप_प्रकार);

अटल अंतरभूत अचिन्हित लघु rpc_get_port(स्थिर काष्ठा sockaddr *sap)
अणु
	चयन (sap->sa_family) अणु
	हाल AF_INET:
		वापस ntohs(((काष्ठा sockaddr_in *)sap)->sin_port);
	हाल AF_INET6:
		वापस ntohs(((काष्ठा sockaddr_in6 *)sap)->sin6_port);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम rpc_set_port(काष्ठा sockaddr *sap,
				स्थिर अचिन्हित लघु port)
अणु
	चयन (sap->sa_family) अणु
	हाल AF_INET:
		((काष्ठा sockaddr_in *)sap)->sin_port = htons(port);
		अवरोध;
	हाल AF_INET6:
		((काष्ठा sockaddr_in6 *)sap)->sin6_port = htons(port);
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा IPV6_SCOPE_DELIMITER		'%'
#घोषणा IPV6_SCOPE_ID_LEN		माप("%nnnnnnnnnn")

अटल अंतरभूत bool rpc_cmp_addr4(स्थिर काष्ठा sockaddr *sap1,
				 स्थिर काष्ठा sockaddr *sap2)
अणु
	स्थिर काष्ठा sockaddr_in *sin1 = (स्थिर काष्ठा sockaddr_in *)sap1;
	स्थिर काष्ठा sockaddr_in *sin2 = (स्थिर काष्ठा sockaddr_in *)sap2;

	वापस sin1->sin_addr.s_addr == sin2->sin_addr.s_addr;
पूर्ण

अटल अंतरभूत bool __rpc_copy_addr4(काष्ठा sockaddr *dst,
				    स्थिर काष्ठा sockaddr *src)
अणु
	स्थिर काष्ठा sockaddr_in *ssin = (काष्ठा sockaddr_in *) src;
	काष्ठा sockaddr_in *dsin = (काष्ठा sockaddr_in *) dst;

	dsin->sin_family = ssin->sin_family;
	dsin->sin_addr.s_addr = ssin->sin_addr.s_addr;
	वापस true;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अंतरभूत bool rpc_cmp_addr6(स्थिर काष्ठा sockaddr *sap1,
				 स्थिर काष्ठा sockaddr *sap2)
अणु
	स्थिर काष्ठा sockaddr_in6 *sin1 = (स्थिर काष्ठा sockaddr_in6 *)sap1;
	स्थिर काष्ठा sockaddr_in6 *sin2 = (स्थिर काष्ठा sockaddr_in6 *)sap2;

	अगर (!ipv6_addr_equal(&sin1->sin6_addr, &sin2->sin6_addr))
		वापस false;
	अन्यथा अगर (ipv6_addr_type(&sin1->sin6_addr) & IPV6_ADDR_LINKLOCAL)
		वापस sin1->sin6_scope_id == sin2->sin6_scope_id;

	वापस true;
पूर्ण

अटल अंतरभूत bool __rpc_copy_addr6(काष्ठा sockaddr *dst,
				    स्थिर काष्ठा sockaddr *src)
अणु
	स्थिर काष्ठा sockaddr_in6 *ssin6 = (स्थिर काष्ठा sockaddr_in6 *) src;
	काष्ठा sockaddr_in6 *dsin6 = (काष्ठा sockaddr_in6 *) dst;

	dsin6->sin6_family = ssin6->sin6_family;
	dsin6->sin6_addr = ssin6->sin6_addr;
	dsin6->sin6_scope_id = ssin6->sin6_scope_id;
	वापस true;
पूर्ण
#अन्यथा	/* !(IS_ENABLED(CONFIG_IPV6) */
अटल अंतरभूत bool rpc_cmp_addr6(स्थिर काष्ठा sockaddr *sap1,
				   स्थिर काष्ठा sockaddr *sap2)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool __rpc_copy_addr6(काष्ठा sockaddr *dst,
				    स्थिर काष्ठा sockaddr *src)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर	/* !(IS_ENABLED(CONFIG_IPV6) */

/**
 * rpc_cmp_addr - compare the address portion of two sockaddrs.
 * @sap1: first sockaddr
 * @sap2: second sockaddr
 *
 * Just compares the family and address portion. Ignores port, but
 * compares the scope अगर it's a link-local address.
 *
 * Returns true अगर the addrs are equal, false अगर they aren't.
 */
अटल अंतरभूत bool rpc_cmp_addr(स्थिर काष्ठा sockaddr *sap1,
				स्थिर काष्ठा sockaddr *sap2)
अणु
	अगर (sap1->sa_family == sap2->sa_family) अणु
		चयन (sap1->sa_family) अणु
		हाल AF_INET:
			वापस rpc_cmp_addr4(sap1, sap2);
		हाल AF_INET6:
			वापस rpc_cmp_addr6(sap1, sap2);
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/**
 * rpc_cmp_addr_port - compare the address and port number of two sockaddrs.
 * @sap1: first sockaddr
 * @sap2: second sockaddr
 */
अटल अंतरभूत bool rpc_cmp_addr_port(स्थिर काष्ठा sockaddr *sap1,
				     स्थिर काष्ठा sockaddr *sap2)
अणु
	अगर (!rpc_cmp_addr(sap1, sap2))
		वापस false;
	वापस rpc_get_port(sap1) == rpc_get_port(sap2);
पूर्ण

/**
 * rpc_copy_addr - copy the address portion of one sockaddr to another
 * @dst: destination sockaddr
 * @src: source sockaddr
 *
 * Just copies the address portion and family. Ignores port, scope, etc.
 * Caller is responsible क्रम making certain that dst is large enough to hold
 * the address in src. Returns true अगर address family is supported. Returns
 * false otherwise.
 */
अटल अंतरभूत bool rpc_copy_addr(काष्ठा sockaddr *dst,
				 स्थिर काष्ठा sockaddr *src)
अणु
	चयन (src->sa_family) अणु
	हाल AF_INET:
		वापस __rpc_copy_addr4(dst, src);
	हाल AF_INET6:
		वापस __rpc_copy_addr6(dst, src);
	पूर्ण
	वापस false;
पूर्ण

/**
 * rpc_get_scope_id - वापस scopeid क्रम a given sockaddr
 * @sa: sockaddr to get scopeid from
 *
 * Returns the value of the sin6_scope_id क्रम AF_INET6 addrs, or 0 अगर
 * not an AF_INET6 address.
 */
अटल अंतरभूत u32 rpc_get_scope_id(स्थिर काष्ठा sockaddr *sa)
अणु
	अगर (sa->sa_family != AF_INET6)
		वापस 0;

	वापस ((काष्ठा sockaddr_in6 *) sa)->sin6_scope_id;
पूर्ण

#पूर्ण_अगर /* _LINUX_SUNRPC_ADDR_H */
