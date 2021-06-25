<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Generic address resultion entity
 *
 *	Authors:
 *	net_अक्रमom Alan Cox
 *	net_ratelimit Andi Kleen
 *	inअणु4,6पूर्ण_pton YOSHIFUJI Hideaki, Copyright (C)2006 USAGI/WIDE Project
 *
 *	Created by Alexey Kuznetsov <kuznet@ms2.inr.ac.ru>
 */

#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/inet.h>
#समावेश <linux/mm.h>
#समावेश <linux/net.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/percpu.h>
#समावेश <linux/init.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/socket.h>

#समावेश <net/sock.h>
#समावेश <net/net_ratelimit.h>
#समावेश <net/ipv6.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/uaccess.h>

DEFINE_RATELIMIT_STATE(net_ratelimit_state, 5 * HZ, 10);
/*
 * All net warning prपूर्णांकk()s should be guarded by this function.
 */
पूर्णांक net_ratelimit(व्योम)
अणु
	वापस __ratelimit(&net_ratelimit_state);
पूर्ण
EXPORT_SYMBOL(net_ratelimit);

/*
 * Convert an ASCII string to binary IP.
 * This is outside of net/ipv4/ because various code that uses IP addresses
 * is otherwise not dependent on the TCP/IP stack.
 */

__be32 in_aton(स्थिर अक्षर *str)
अणु
	अचिन्हित पूर्णांक l;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	l = 0;
	क्रम (i = 0; i < 4; i++)	अणु
		l <<= 8;
		अगर (*str != '\0') अणु
			val = 0;
			जबतक (*str != '\0' && *str != '.' && *str != '\n') अणु
				val *= 10;
				val += *str - '0';
				str++;
			पूर्ण
			l |= val;
			अगर (*str != '\0')
				str++;
		पूर्ण
	पूर्ण
	वापस htonl(l);
पूर्ण
EXPORT_SYMBOL(in_aton);

#घोषणा IN6PTON_XDIGIT		0x00010000
#घोषणा IN6PTON_DIGIT		0x00020000
#घोषणा IN6PTON_COLON_MASK	0x00700000
#घोषणा IN6PTON_COLON_1		0x00100000	/* single : requested */
#घोषणा IN6PTON_COLON_2		0x00200000	/* second : requested */
#घोषणा IN6PTON_COLON_1_2	0x00400000	/* :: requested */
#घोषणा IN6PTON_DOT		0x00800000	/* . */
#घोषणा IN6PTON_DELIM		0x10000000
#घोषणा IN6PTON_शून्य		0x20000000	/* first/tail */
#घोषणा IN6PTON_UNKNOWN		0x40000000

अटल अंतरभूत पूर्णांक xdigit2bin(अक्षर c, पूर्णांक delim)
अणु
	पूर्णांक val;

	अगर (c == delim || c == '\0')
		वापस IN6PTON_DELIM;
	अगर (c == ':')
		वापस IN6PTON_COLON_MASK;
	अगर (c == '.')
		वापस IN6PTON_DOT;

	val = hex_to_bin(c);
	अगर (val >= 0)
		वापस val | IN6PTON_XDIGIT | (val < 10 ? IN6PTON_DIGIT : 0);

	अगर (delim == -1)
		वापस IN6PTON_DELIM;
	वापस IN6PTON_UNKNOWN;
पूर्ण

/**
 * in4_pton - convert an IPv4 address from literal to binary representation
 * @src: the start of the IPv4 address string
 * @srclen: the length of the string, -1 means म_माप(src)
 * @dst: the binary (u8[4] array) representation of the IPv4 address
 * @delim: the delimiter of the IPv4 address in @src, -1 means no delimiter
 * @end: A poपूर्णांकer to the end of the parsed string will be placed here
 *
 * Return one on success, वापस zero when any error occurs
 * and @end will poपूर्णांक to the end of the parsed string.
 *
 */
पूर्णांक in4_pton(स्थिर अक्षर *src, पूर्णांक srclen,
	     u8 *dst,
	     पूर्णांक delim, स्थिर अक्षर **end)
अणु
	स्थिर अक्षर *s;
	u8 *d;
	u8 dbuf[4];
	पूर्णांक ret = 0;
	पूर्णांक i;
	पूर्णांक w = 0;

	अगर (srclen < 0)
		srclen = म_माप(src);
	s = src;
	d = dbuf;
	i = 0;
	जबतक (1) अणु
		पूर्णांक c;
		c = xdigit2bin(srclen > 0 ? *s : '\0', delim);
		अगर (!(c & (IN6PTON_DIGIT | IN6PTON_DOT | IN6PTON_DELIM | IN6PTON_COLON_MASK))) अणु
			जाओ out;
		पूर्ण
		अगर (c & (IN6PTON_DOT | IN6PTON_DELIM | IN6PTON_COLON_MASK)) अणु
			अगर (w == 0)
				जाओ out;
			*d++ = w & 0xff;
			w = 0;
			i++;
			अगर (c & (IN6PTON_DELIM | IN6PTON_COLON_MASK)) अणु
				अगर (i != 4)
					जाओ out;
				अवरोध;
			पूर्ण
			जाओ cont;
		पूर्ण
		w = (w * 10) + c;
		अगर ((w & 0xffff) > 255) अणु
			जाओ out;
		पूर्ण
cont:
		अगर (i >= 4)
			जाओ out;
		s++;
		srclen--;
	पूर्ण
	ret = 1;
	स_नकल(dst, dbuf, माप(dbuf));
out:
	अगर (end)
		*end = s;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(in4_pton);

/**
 * in6_pton - convert an IPv6 address from literal to binary representation
 * @src: the start of the IPv6 address string
 * @srclen: the length of the string, -1 means म_माप(src)
 * @dst: the binary (u8[16] array) representation of the IPv6 address
 * @delim: the delimiter of the IPv6 address in @src, -1 means no delimiter
 * @end: A poपूर्णांकer to the end of the parsed string will be placed here
 *
 * Return one on success, वापस zero when any error occurs
 * and @end will poपूर्णांक to the end of the parsed string.
 *
 */
पूर्णांक in6_pton(स्थिर अक्षर *src, पूर्णांक srclen,
	     u8 *dst,
	     पूर्णांक delim, स्थिर अक्षर **end)
अणु
	स्थिर अक्षर *s, *tok = शून्य;
	u8 *d, *dc = शून्य;
	u8 dbuf[16];
	पूर्णांक ret = 0;
	पूर्णांक i;
	पूर्णांक state = IN6PTON_COLON_1_2 | IN6PTON_XDIGIT | IN6PTON_शून्य;
	पूर्णांक w = 0;

	स_रखो(dbuf, 0, माप(dbuf));

	s = src;
	d = dbuf;
	अगर (srclen < 0)
		srclen = म_माप(src);

	जबतक (1) अणु
		पूर्णांक c;

		c = xdigit2bin(srclen > 0 ? *s : '\0', delim);
		अगर (!(c & state))
			जाओ out;
		अगर (c & (IN6PTON_DELIM | IN6PTON_COLON_MASK)) अणु
			/* process one 16-bit word */
			अगर (!(state & IN6PTON_शून्य)) अणु
				*d++ = (w >> 8) & 0xff;
				*d++ = w & 0xff;
			पूर्ण
			w = 0;
			अगर (c & IN6PTON_DELIM) अणु
				/* We've processed last word */
				अवरोध;
			पूर्ण
			/*
			 * COLON_1 => XDIGIT
			 * COLON_2 => XDIGIT|DELIM
			 * COLON_1_2 => COLON_2
			 */
			चयन (state & IN6PTON_COLON_MASK) अणु
			हाल IN6PTON_COLON_2:
				dc = d;
				state = IN6PTON_XDIGIT | IN6PTON_DELIM;
				अगर (dc - dbuf >= माप(dbuf))
					state |= IN6PTON_शून्य;
				अवरोध;
			हाल IN6PTON_COLON_1|IN6PTON_COLON_1_2:
				state = IN6PTON_XDIGIT | IN6PTON_COLON_2;
				अवरोध;
			हाल IN6PTON_COLON_1:
				state = IN6PTON_XDIGIT;
				अवरोध;
			हाल IN6PTON_COLON_1_2:
				state = IN6PTON_COLON_2;
				अवरोध;
			शेष:
				state = 0;
			पूर्ण
			tok = s + 1;
			जाओ cont;
		पूर्ण

		अगर (c & IN6PTON_DOT) अणु
			ret = in4_pton(tok ? tok : s, srclen + (पूर्णांक)(s - tok), d, delim, &s);
			अगर (ret > 0) अणु
				d += 4;
				अवरोध;
			पूर्ण
			जाओ out;
		पूर्ण

		w = (w << 4) | (0xff & c);
		state = IN6PTON_COLON_1 | IN6PTON_DELIM;
		अगर (!(w & 0xf000)) अणु
			state |= IN6PTON_XDIGIT;
		पूर्ण
		अगर (!dc && d + 2 < dbuf + माप(dbuf)) अणु
			state |= IN6PTON_COLON_1_2;
			state &= ~IN6PTON_DELIM;
		पूर्ण
		अगर (d + 2 >= dbuf + माप(dbuf)) अणु
			state &= ~(IN6PTON_COLON_1|IN6PTON_COLON_1_2);
		पूर्ण
cont:
		अगर ((dc && d + 4 < dbuf + माप(dbuf)) ||
		    d + 4 == dbuf + माप(dbuf)) अणु
			state |= IN6PTON_DOT;
		पूर्ण
		अगर (d >= dbuf + माप(dbuf)) अणु
			state &= ~(IN6PTON_XDIGIT|IN6PTON_COLON_MASK);
		पूर्ण
		s++;
		srclen--;
	पूर्ण

	i = 15; d--;

	अगर (dc) अणु
		जबतक (d >= dc)
			dst[i--] = *d--;
		जबतक (i >= dc - dbuf)
			dst[i--] = 0;
		जबतक (i >= 0)
			dst[i--] = *d--;
	पूर्ण अन्यथा
		स_नकल(dst, dbuf, माप(dbuf));

	ret = 1;
out:
	अगर (end)
		*end = s;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(in6_pton);

अटल पूर्णांक inet4_pton(स्थिर अक्षर *src, u16 port_num,
		काष्ठा sockaddr_storage *addr)
अणु
	काष्ठा sockaddr_in *addr4 = (काष्ठा sockaddr_in *)addr;
	पूर्णांक srclen = म_माप(src);

	अगर (srclen > INET_ADDRSTRLEN)
		वापस -EINVAL;

	अगर (in4_pton(src, srclen, (u8 *)&addr4->sin_addr.s_addr,
		     '\n', शून्य) == 0)
		वापस -EINVAL;

	addr4->sin_family = AF_INET;
	addr4->sin_port = htons(port_num);

	वापस 0;
पूर्ण

अटल पूर्णांक inet6_pton(काष्ठा net *net, स्थिर अक्षर *src, u16 port_num,
		काष्ठा sockaddr_storage *addr)
अणु
	काष्ठा sockaddr_in6 *addr6 = (काष्ठा sockaddr_in6 *)addr;
	स्थिर अक्षर *scope_delim;
	पूर्णांक srclen = म_माप(src);

	अगर (srclen > INET6_ADDRSTRLEN)
		वापस -EINVAL;

	अगर (in6_pton(src, srclen, (u8 *)&addr6->sin6_addr.s6_addr,
		     '%', &scope_delim) == 0)
		वापस -EINVAL;

	अगर (ipv6_addr_type(&addr6->sin6_addr) & IPV6_ADDR_LINKLOCAL &&
	    src + srclen != scope_delim && *scope_delim == '%') अणु
		काष्ठा net_device *dev;
		अक्षर scope_id[16];
		माप_प्रकार scope_len = min_t(माप_प्रकार, माप(scope_id) - 1,
					 src + srclen - scope_delim - 1);

		स_नकल(scope_id, scope_delim + 1, scope_len);
		scope_id[scope_len] = '\0';

		dev = dev_get_by_name(net, scope_id);
		अगर (dev) अणु
			addr6->sin6_scope_id = dev->अगरindex;
			dev_put(dev);
		पूर्ण अन्यथा अगर (kstrtouपूर्णांक(scope_id, 0, &addr6->sin6_scope_id)) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	addr6->sin6_family = AF_INET6;
	addr6->sin6_port = htons(port_num);

	वापस 0;
पूर्ण

/**
 * inet_pton_with_scope - convert an IPv4/IPv6 and port to socket address
 * @net: net namespace (used क्रम scope handling)
 * @af: address family, AF_INET, AF_INET6 or AF_UNSPEC क्रम either
 * @src: the start of the address string
 * @port: the start of the port string (or शून्य क्रम none)
 * @addr: output socket address
 *
 * Return zero on success, वापस त्रुटि_सं when any error occurs.
 */
पूर्णांक inet_pton_with_scope(काष्ठा net *net, __kernel_sa_family_t af,
		स्थिर अक्षर *src, स्थिर अक्षर *port, काष्ठा sockaddr_storage *addr)
अणु
	u16 port_num;
	पूर्णांक ret = -EINVAL;

	अगर (port) अणु
		अगर (kstrtou16(port, 0, &port_num))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		port_num = 0;
	पूर्ण

	चयन (af) अणु
	हाल AF_INET:
		ret = inet4_pton(src, port_num, addr);
		अवरोध;
	हाल AF_INET6:
		ret = inet6_pton(net, src, port_num, addr);
		अवरोध;
	हाल AF_UNSPEC:
		ret = inet4_pton(src, port_num, addr);
		अगर (ret)
			ret = inet6_pton(net, src, port_num, addr);
		अवरोध;
	शेष:
		pr_err("unexpected address family %d\n", af);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(inet_pton_with_scope);

bool inet_addr_is_any(काष्ठा sockaddr *addr)
अणु
	अगर (addr->sa_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *in6 = (काष्ठा sockaddr_in6 *)addr;
		स्थिर काष्ठा sockaddr_in6 in6_any =
			अणु .sin6_addr = IN6ADDR_ANY_INIT पूर्ण;

		अगर (!स_भेद(in6->sin6_addr.s6_addr,
			    in6_any.sin6_addr.s6_addr, 16))
			वापस true;
	पूर्ण अन्यथा अगर (addr->sa_family == AF_INET) अणु
		काष्ठा sockaddr_in *in = (काष्ठा sockaddr_in *)addr;

		अगर (in->sin_addr.s_addr == htonl(INADDR_ANY))
			वापस true;
	पूर्ण अन्यथा अणु
		pr_warn("unexpected address family %u\n", addr->sa_family);
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(inet_addr_is_any);

व्योम inet_proto_csum_replace4(__sum16 *sum, काष्ठा sk_buff *skb,
			      __be32 from, __be32 to, bool pseuकरोhdr)
अणु
	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
		csum_replace4(sum, from, to);
		अगर (skb->ip_summed == CHECKSUM_COMPLETE && pseuकरोhdr)
			skb->csum = ~csum_add(csum_sub(~(skb->csum),
						       (__क्रमce __wsum)from),
					      (__क्रमce __wsum)to);
	पूर्ण अन्यथा अगर (pseuकरोhdr)
		*sum = ~csum_fold(csum_add(csum_sub(csum_unfold(*sum),
						    (__क्रमce __wsum)from),
					   (__क्रमce __wsum)to));
पूर्ण
EXPORT_SYMBOL(inet_proto_csum_replace4);

/**
 * inet_proto_csum_replace16 - update layer 4 header checksum field
 * @sum: Layer 4 header checksum field
 * @skb: sk_buff क्रम the packet
 * @from: old IPv6 address
 * @to: new IPv6 address
 * @pseuकरोhdr: True अगर layer 4 header checksum includes pseuकरोheader
 *
 * Update layer 4 header as per the update in IPv6 src/dst address.
 *
 * There is no need to update skb->csum in this function, because update in two
 * fields a.) IPv6 src/dst address and b.) L4 header checksum cancels each other
 * क्रम skb->csum calculation. Whereas inet_proto_csum_replace4 function needs to
 * update skb->csum, because update in 3 fields a.) IPv4 src/dst address,
 * b.) IPv4 Header checksum and c.) L4 header checksum results in same dअगरf as
 * L4 Header checksum क्रम skb->csum calculation.
 */
व्योम inet_proto_csum_replace16(__sum16 *sum, काष्ठा sk_buff *skb,
			       स्थिर __be32 *from, स्थिर __be32 *to,
			       bool pseuकरोhdr)
अणु
	__be32 dअगरf[] = अणु
		~from[0], ~from[1], ~from[2], ~from[3],
		to[0], to[1], to[2], to[3],
	पूर्ण;
	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
		*sum = csum_fold(csum_partial(dअगरf, माप(dअगरf),
				 ~csum_unfold(*sum)));
	पूर्ण अन्यथा अगर (pseuकरोhdr)
		*sum = ~csum_fold(csum_partial(dअगरf, माप(dअगरf),
				  csum_unfold(*sum)));
पूर्ण
EXPORT_SYMBOL(inet_proto_csum_replace16);

व्योम inet_proto_csum_replace_by_dअगरf(__sum16 *sum, काष्ठा sk_buff *skb,
				     __wsum dअगरf, bool pseuकरोhdr)
अणु
	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
		*sum = csum_fold(csum_add(dअगरf, ~csum_unfold(*sum)));
		अगर (skb->ip_summed == CHECKSUM_COMPLETE && pseuकरोhdr)
			skb->csum = ~csum_add(dअगरf, ~skb->csum);
	पूर्ण अन्यथा अगर (pseuकरोhdr) अणु
		*sum = ~csum_fold(csum_add(dअगरf, csum_unfold(*sum)));
	पूर्ण
पूर्ण
EXPORT_SYMBOL(inet_proto_csum_replace_by_dअगरf);
