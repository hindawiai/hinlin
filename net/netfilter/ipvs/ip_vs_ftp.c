<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ip_vs_ftp.c: IPVS ftp application module
 *
 * Authors:	Wensong Zhang <wensong@linuxभवserver.org>
 *
 * Changes:
 *
 * Most code here is taken from ip_masq_ftp.c in kernel 2.2. The dअगरference
 * is that ip_vs_ftp module handles the reverse direction to ip_masq_ftp.
 *
 *		IP_MASQ_FTP ftp masquerading module
 *
 * Version:	@(#)ip_masq_ftp.c 0.04   02/05/96
 *
 * Author:	Wouter Gadeyne
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/inet.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/netfilter.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_nat.h>
#समावेश <net/netfilter/nf_nat_helper.h>
#समावेश <linux/gfp.h>
#समावेश <net/protocol.h>
#समावेश <net/tcp.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <net/ip_vs.h>


#घोषणा SERVER_STRING_PASV "227 "
#घोषणा CLIENT_STRING_PORT "PORT"
#घोषणा SERVER_STRING_EPSV "229 "
#घोषणा CLIENT_STRING_EPRT "EPRT"

क्रमागत अणु
	IP_VS_FTP_ACTIVE = 0,
	IP_VS_FTP_PORT = 0,
	IP_VS_FTP_PASV,
	IP_VS_FTP_EPRT,
	IP_VS_FTP_EPSV,
पूर्ण;

/*
 * List of ports (up to IP_VS_APP_MAX_PORTS) to be handled by helper
 * First port is set to the शेष port.
 */
अटल अचिन्हित पूर्णांक ports_count = 1;
अटल अचिन्हित लघु ports[IP_VS_APP_MAX_PORTS] = अणु21, 0पूर्ण;
module_param_array(ports, uलघु, &ports_count, 0444);
MODULE_PARM_DESC(ports, "Ports to monitor for FTP control commands");


अटल अक्षर *ip_vs_ftp_data_ptr(काष्ठा sk_buff *skb, काष्ठा ip_vs_iphdr *ipvsh)
अणु
	काष्ठा tcphdr *th = (काष्ठा tcphdr *)((अक्षर *)skb->data + ipvsh->len);

	अगर ((th->करोff << 2) < माप(काष्ठा tcphdr))
		वापस शून्य;

	वापस (अक्षर *)th + (th->करोff << 2);
पूर्ण

अटल पूर्णांक
ip_vs_ftp_init_conn(काष्ठा ip_vs_app *app, काष्ठा ip_vs_conn *cp)
अणु
	/* We use connection tracking क्रम the command connection */
	cp->flags |= IP_VS_CONN_F_NFCT;
	वापस 0;
पूर्ण


अटल पूर्णांक
ip_vs_ftp_करोne_conn(काष्ठा ip_vs_app *app, काष्ठा ip_vs_conn *cp)
अणु
	वापस 0;
पूर्ण


/* Get <addr,port> from the string "xxx.xxx.xxx.xxx,ppp,ppp", started
 * with the "pattern". <addr,port> is in network order.
 * Parse extended क्रमmat depending on ext. In this हाल addr can be pre-set.
 */
अटल पूर्णांक ip_vs_ftp_get_addrport(अक्षर *data, अक्षर *data_limit,
				  स्थिर अक्षर *pattern, माप_प्रकार plen,
				  अक्षर skip, bool ext, पूर्णांक mode,
				  जोड़ nf_inet_addr *addr, __be16 *port,
				  __u16 af, अक्षर **start, अक्षर **end)
अणु
	अक्षर *s, c;
	अचिन्हित अक्षर p[6];
	अक्षर edelim;
	__u16 hport;
	पूर्णांक i = 0;

	अगर (data_limit - data < plen) अणु
		/* check अगर there is partial match */
		अगर (strnहालcmp(data, pattern, data_limit - data) == 0)
			वापस -1;
		अन्यथा
			वापस 0;
	पूर्ण

	अगर (strnहालcmp(data, pattern, plen) != 0) अणु
		वापस 0;
	पूर्ण
	s = data + plen;
	अगर (skip) अणु
		bool found = false;

		क्रम (;; s++) अणु
			अगर (s == data_limit)
				वापस -1;
			अगर (!found) अणु
				/* "(" is optional क्रम non-extended क्रमmat,
				 * so catch the start of IPv4 address
				 */
				अगर (!ext && है_अंक(*s))
					अवरोध;
				अगर (*s == skip)
					found = true;
			पूर्ण अन्यथा अगर (*s != skip) अणु
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	/* Old IPv4-only क्रमmat? */
	अगर (!ext) अणु
		p[0] = 0;
		क्रम (data = s; ; data++) अणु
			अगर (data == data_limit)
				वापस -1;
			c = *data;
			अगर (है_अंक(c)) अणु
				p[i] = p[i]*10 + c - '0';
			पूर्ण अन्यथा अगर (c == ',' && i < 5) अणु
				i++;
				p[i] = 0;
			पूर्ण अन्यथा अणु
				/* unexpected अक्षरacter or terminator */
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i != 5)
			वापस -1;

		*start = s;
		*end = data;
		addr->ip = get_unaligned((__be32 *) p);
		*port = get_unaligned((__be16 *) (p + 4));
		वापस 1;
	पूर्ण
	अगर (s == data_limit)
		वापस -1;
	*start = s;
	edelim = *s++;
	अगर (edelim < 33 || edelim > 126)
		वापस -1;
	अगर (s == data_limit)
		वापस -1;
	अगर (*s == edelim) अणु
		/* Address family is usually missing क्रम EPSV response */
		अगर (mode != IP_VS_FTP_EPSV)
			वापस -1;
		s++;
		अगर (s == data_limit)
			वापस -1;
		/* Then address should be missing too */
		अगर (*s != edelim)
			वापस -1;
		/* Caller can pre-set addr, अगर needed */
		s++;
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *ep;

		/* We allow address only from same family */
		अगर (af == AF_INET6 && *s != '2')
			वापस -1;
		अगर (af == AF_INET && *s != '1')
			वापस -1;
		s++;
		अगर (s == data_limit)
			वापस -1;
		अगर (*s != edelim)
			वापस -1;
		s++;
		अगर (s == data_limit)
			वापस -1;
		अगर (af == AF_INET6) अणु
			अगर (in6_pton(s, data_limit - s, (u8 *)addr, edelim,
				     &ep) <= 0)
				वापस -1;
		पूर्ण अन्यथा अणु
			अगर (in4_pton(s, data_limit - s, (u8 *)addr, edelim,
				     &ep) <= 0)
				वापस -1;
		पूर्ण
		s = (अक्षर *) ep;
		अगर (s == data_limit)
			वापस -1;
		अगर (*s != edelim)
			वापस -1;
		s++;
	पूर्ण
	क्रम (hport = 0; ; s++)
	अणु
		अगर (s == data_limit)
			वापस -1;
		अगर (!है_अंक(*s))
			अवरोध;
		hport = hport * 10 + *s - '0';
	पूर्ण
	अगर (s == data_limit || !hport || *s != edelim)
		वापस -1;
	s++;
	*end = s;
	*port = htons(hport);
	वापस 1;
पूर्ण

/* Look at outgoing ftp packets to catch the response to a PASV/EPSV command
 * from the server (inside-to-outside).
 * When we see one, we build a connection entry with the client address,
 * client port 0 (unknown at the moment), the server address and the
 * server port.  Mark the current connection entry as a control channel
 * of the new entry. All this work is just to make the data connection
 * can be scheduled to the right server later.
 *
 * The outgoing packet should be something like
 *   "227 Entering Passive Mode (xxx,xxx,xxx,xxx,ppp,ppp)".
 * xxx,xxx,xxx,xxx is the server address, ppp,ppp is the server port number.
 * The extended क्रमmat क्रम EPSV response provides usually only port:
 *   "229 Entering Extended Passive Mode (|||ppp|)"
 */
अटल पूर्णांक ip_vs_ftp_out(काष्ठा ip_vs_app *app, काष्ठा ip_vs_conn *cp,
			 काष्ठा sk_buff *skb, पूर्णांक *dअगरf,
			 काष्ठा ip_vs_iphdr *ipvsh)
अणु
	अक्षर *data, *data_limit;
	अक्षर *start, *end;
	जोड़ nf_inet_addr from;
	__be16 port;
	काष्ठा ip_vs_conn *n_cp;
	अक्षर buf[24];		/* xxx.xxx.xxx.xxx,ppp,ppp\000 */
	अचिन्हित पूर्णांक buf_len;
	पूर्णांक ret = 0;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	*dअगरf = 0;

	/* Only useful क्रम established sessions */
	अगर (cp->state != IP_VS_TCP_S_ESTABLISHED)
		वापस 1;

	/* Linear packets are much easier to deal with. */
	अगर (skb_ensure_writable(skb, skb->len))
		वापस 0;

	अगर (cp->app_data == (व्योम *) IP_VS_FTP_PASV) अणु
		data = ip_vs_ftp_data_ptr(skb, ipvsh);
		data_limit = skb_tail_poपूर्णांकer(skb);

		अगर (!data || data >= data_limit)
			वापस 1;

		अगर (ip_vs_ftp_get_addrport(data, data_limit,
					   SERVER_STRING_PASV,
					   माप(SERVER_STRING_PASV)-1,
					   '(', false, IP_VS_FTP_PASV,
					   &from, &port, cp->af,
					   &start, &end) != 1)
			वापस 1;

		IP_VS_DBG(7, "PASV response (%pI4:%u) -> %pI4:%u detected\n",
			  &from.ip, ntohs(port), &cp->caddr.ip, 0);
	पूर्ण अन्यथा अगर (cp->app_data == (व्योम *) IP_VS_FTP_EPSV) अणु
		data = ip_vs_ftp_data_ptr(skb, ipvsh);
		data_limit = skb_tail_poपूर्णांकer(skb);

		अगर (!data || data >= data_limit)
			वापस 1;

		/* Usually, data address is not specअगरied but
		 * we support dअगरferent address, so pre-set it.
		 */
		from = cp->daddr;
		अगर (ip_vs_ftp_get_addrport(data, data_limit,
					   SERVER_STRING_EPSV,
					   माप(SERVER_STRING_EPSV)-1,
					   '(', true, IP_VS_FTP_EPSV,
					   &from, &port, cp->af,
					   &start, &end) != 1)
			वापस 1;

		IP_VS_DBG_BUF(7, "EPSV response (%s:%u) -> %s:%u detected\n",
			      IP_VS_DBG_ADDR(cp->af, &from), ntohs(port),
			      IP_VS_DBG_ADDR(cp->af, &cp->caddr), 0);
	पूर्ण अन्यथा अणु
		वापस 1;
	पूर्ण

	/* Now update or create a connection entry क्रम it */
	अणु
		काष्ठा ip_vs_conn_param p;

		ip_vs_conn_fill_param(cp->ipvs, cp->af,
				      ipvsh->protocol, &from, port,
				      &cp->caddr, 0, &p);
		n_cp = ip_vs_conn_out_get(&p);
	पूर्ण
	अगर (!n_cp) अणु
		काष्ठा ip_vs_conn_param p;

		ip_vs_conn_fill_param(cp->ipvs,
				      cp->af, ipvsh->protocol, &cp->caddr,
				      0, &cp->vaddr, port, &p);
		n_cp = ip_vs_conn_new(&p, cp->af, &from, port,
				      IP_VS_CONN_F_NO_CPORT |
				      IP_VS_CONN_F_NFCT,
				      cp->dest, skb->mark);
		अगर (!n_cp)
			वापस 0;

		/* add its controller */
		ip_vs_control_add(n_cp, cp);
	पूर्ण

	/* Replace the old passive address with the new one */
	अगर (cp->app_data == (व्योम *) IP_VS_FTP_PASV) अणु
		from.ip = n_cp->vaddr.ip;
		port = n_cp->vport;
		snम_लिखो(buf, माप(buf), "%u,%u,%u,%u,%u,%u",
			 ((अचिन्हित अक्षर *)&from.ip)[0],
			 ((अचिन्हित अक्षर *)&from.ip)[1],
			 ((अचिन्हित अक्षर *)&from.ip)[2],
			 ((अचिन्हित अक्षर *)&from.ip)[3],
			 ntohs(port) >> 8,
			 ntohs(port) & 0xFF);
	पूर्ण अन्यथा अगर (cp->app_data == (व्योम *) IP_VS_FTP_EPSV) अणु
		from = n_cp->vaddr;
		port = n_cp->vport;
		/* Only port, client will use VIP क्रम the data connection */
		snम_लिखो(buf, माप(buf), "|||%u|",
			 ntohs(port));
	पूर्ण अन्यथा अणु
		*buf = 0;
	पूर्ण
	buf_len = म_माप(buf);

	ct = nf_ct_get(skb, &ctinfo);
	अगर (ct) अणु
		bool mangled;

		/* If mangling fails this function will वापस 0
		 * which will cause the packet to be dropped.
		 * Mangling can only fail under memory pressure,
		 * hopefully it will succeed on the retransmitted
		 * packet.
		 */
		mangled = nf_nat_mangle_tcp_packet(skb, ct, ctinfo,
						   ipvsh->len,
						   start - data,
						   end - start,
						   buf, buf_len);
		अगर (mangled) अणु
			ip_vs_nfct_expect_related(skb, ct, n_cp,
						  ipvsh->protocol, 0, 0);
			अगर (skb->ip_summed == CHECKSUM_COMPLETE)
				skb->ip_summed = CHECKSUM_UNNECESSARY;
			/* csum is updated */
			ret = 1;
		पूर्ण
	पूर्ण

	/* Not setting 'diff' is पूर्णांकentional, otherwise the sequence
	 * would be adjusted twice.
	 */

	cp->app_data = (व्योम *) IP_VS_FTP_ACTIVE;
	ip_vs_tcp_conn_listen(n_cp);
	ip_vs_conn_put(n_cp);
	वापस ret;
पूर्ण


/* Look at incoming ftp packets to catch the PASV/PORT/EPRT/EPSV command
 * (outside-to-inside).
 *
 * The incoming packet having the PORT command should be something like
 *      "PORT xxx,xxx,xxx,xxx,ppp,ppp\n".
 * xxx,xxx,xxx,xxx is the client address, ppp,ppp is the client port number.
 * In this हाल, we create a connection entry using the client address and
 * port, so that the active ftp data connection from the server can reach
 * the client.
 * Extended क्रमmat:
 *	"EPSV\r\n" when client requests server address from same family
 *	"EPSV 1\r\n" when client requests IPv4 server address
 *	"EPSV 2\r\n" when client requests IPv6 server address
 *	"EPSV ALL\r\n" - not supported
 *	EPRT with specअगरied delimiter (ASCII 33..126), "|" by शेष:
 *	"EPRT |1|IPv4ADDR|PORT|\r\n" when client provides IPv4 addrport
 *	"EPRT |2|IPv6ADDR|PORT|\r\n" when client provides IPv6 addrport
 */
अटल पूर्णांक ip_vs_ftp_in(काष्ठा ip_vs_app *app, काष्ठा ip_vs_conn *cp,
			काष्ठा sk_buff *skb, पूर्णांक *dअगरf,
			काष्ठा ip_vs_iphdr *ipvsh)
अणु
	अक्षर *data, *data_start, *data_limit;
	अक्षर *start, *end;
	जोड़ nf_inet_addr to;
	__be16 port;
	काष्ठा ip_vs_conn *n_cp;

	/* no dअगरf required क्रम incoming packets */
	*dअगरf = 0;

	/* Only useful क्रम established sessions */
	अगर (cp->state != IP_VS_TCP_S_ESTABLISHED)
		वापस 1;

	/* Linear packets are much easier to deal with. */
	अगर (skb_ensure_writable(skb, skb->len))
		वापस 0;

	data = data_start = ip_vs_ftp_data_ptr(skb, ipvsh);
	data_limit = skb_tail_poपूर्णांकer(skb);
	अगर (!data || data >= data_limit)
		वापस 1;

	जबतक (data <= data_limit - 6) अणु
		अगर (cp->af == AF_INET &&
		    strnहालcmp(data, "PASV\r\n", 6) == 0) अणु
			/* Passive mode on */
			IP_VS_DBG(7, "got PASV at %td of %td\n",
				  data - data_start,
				  data_limit - data_start);
			cp->app_data = (व्योम *) IP_VS_FTP_PASV;
			वापस 1;
		पूर्ण

		/* EPSV or EPSV<space><net-prt> */
		अगर (strnहालcmp(data, "EPSV", 4) == 0 &&
		    (data[4] == ' ' || data[4] == '\r')) अणु
			अगर (data[4] == ' ') अणु
				अक्षर proto = data[5];

				अगर (data > data_limit - 7 || data[6] != '\r')
					वापस 1;

#अगर_घोषित CONFIG_IP_VS_IPV6
				अगर (cp->af == AF_INET6 && proto == '2') अणु
				पूर्ण अन्यथा
#पूर्ण_अगर
				अगर (cp->af == AF_INET && proto == '1') अणु
				पूर्ण अन्यथा अणु
					वापस 1;
				पूर्ण
			पूर्ण
			/* Extended Passive mode on */
			IP_VS_DBG(7, "got EPSV at %td of %td\n",
				  data - data_start,
				  data_limit - data_start);
			cp->app_data = (व्योम *) IP_VS_FTP_EPSV;
			वापस 1;
		पूर्ण

		data++;
	पूर्ण

	/*
	 * To support भव FTP server, the scenerio is as follows:
	 *       FTP client ----> Load Balancer ----> FTP server
	 * First detect the port number in the application data,
	 * then create a new connection entry क्रम the coming data
	 * connection.
	 */
	अगर (cp->af == AF_INET &&
	    ip_vs_ftp_get_addrport(data_start, data_limit,
				   CLIENT_STRING_PORT,
				   माप(CLIENT_STRING_PORT)-1,
				   ' ', false, IP_VS_FTP_PORT,
				   &to, &port, cp->af,
				   &start, &end) == 1) अणु

		IP_VS_DBG(7, "PORT %pI4:%u detected\n", &to.ip, ntohs(port));

		/* Now update or create a connection entry क्रम it */
		IP_VS_DBG(7, "protocol %s %pI4:%u %pI4:%u\n",
			  ip_vs_proto_name(ipvsh->protocol),
			  &to.ip, ntohs(port), &cp->vaddr.ip,
			  ntohs(cp->vport)-1);
	पूर्ण अन्यथा अगर (ip_vs_ftp_get_addrport(data_start, data_limit,
					  CLIENT_STRING_EPRT,
					  माप(CLIENT_STRING_EPRT)-1,
					  ' ', true, IP_VS_FTP_EPRT,
					  &to, &port, cp->af,
					  &start, &end) == 1) अणु

		IP_VS_DBG_BUF(7, "EPRT %s:%u detected\n",
			      IP_VS_DBG_ADDR(cp->af, &to), ntohs(port));

		/* Now update or create a connection entry क्रम it */
		IP_VS_DBG_BUF(7, "protocol %s %s:%u %s:%u\n",
			      ip_vs_proto_name(ipvsh->protocol),
			      IP_VS_DBG_ADDR(cp->af, &to), ntohs(port),
			      IP_VS_DBG_ADDR(cp->af, &cp->vaddr),
			      ntohs(cp->vport)-1);
	पूर्ण अन्यथा अणु
		वापस 1;
	पूर्ण

	/* Passive mode off */
	cp->app_data = (व्योम *) IP_VS_FTP_ACTIVE;

	अणु
		काष्ठा ip_vs_conn_param p;
		ip_vs_conn_fill_param(cp->ipvs, cp->af,
				      ipvsh->protocol, &to, port, &cp->vaddr,
				      htons(ntohs(cp->vport)-1), &p);
		n_cp = ip_vs_conn_in_get(&p);
		अगर (!n_cp) अणु
			n_cp = ip_vs_conn_new(&p, cp->af, &cp->daddr,
					      htons(ntohs(cp->dport)-1),
					      IP_VS_CONN_F_NFCT, cp->dest,
					      skb->mark);
			अगर (!n_cp)
				वापस 0;

			/* add its controller */
			ip_vs_control_add(n_cp, cp);
		पूर्ण
	पूर्ण

	/*
	 *	Move tunnel to listen state
	 */
	ip_vs_tcp_conn_listen(n_cp);
	ip_vs_conn_put(n_cp);

	वापस 1;
पूर्ण


अटल काष्ठा ip_vs_app ip_vs_ftp = अणु
	.name =		"ftp",
	.type =		IP_VS_APP_TYPE_FTP,
	.protocol =	IPPROTO_TCP,
	.module =	THIS_MODULE,
	.incs_list =	LIST_HEAD_INIT(ip_vs_ftp.incs_list),
	.init_conn =	ip_vs_ftp_init_conn,
	.करोne_conn =	ip_vs_ftp_करोne_conn,
	.bind_conn =	शून्य,
	.unbind_conn =	शून्य,
	.pkt_out =	ip_vs_ftp_out,
	.pkt_in =	ip_vs_ftp_in,
पूर्ण;

/*
 *	per netns ip_vs_ftp initialization
 */
अटल पूर्णांक __net_init __ip_vs_ftp_init(काष्ठा net *net)
अणु
	पूर्णांक i, ret;
	काष्ठा ip_vs_app *app;
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	अगर (!ipvs)
		वापस -ENOENT;

	app = रेजिस्टर_ip_vs_app(ipvs, &ip_vs_ftp);
	अगर (IS_ERR(app))
		वापस PTR_ERR(app);

	क्रम (i = 0; i < ports_count; i++) अणु
		अगर (!ports[i])
			जारी;
		ret = रेजिस्टर_ip_vs_app_inc(ipvs, app, app->protocol, ports[i]);
		अगर (ret)
			जाओ err_unreg;
	पूर्ण
	वापस 0;

err_unreg:
	unरेजिस्टर_ip_vs_app(ipvs, &ip_vs_ftp);
	वापस ret;
पूर्ण
/*
 *	netns निकास
 */
अटल व्योम __ip_vs_ftp_निकास(काष्ठा net *net)
अणु
	काष्ठा netns_ipvs *ipvs = net_ipvs(net);

	अगर (!ipvs)
		वापस;

	unरेजिस्टर_ip_vs_app(ipvs, &ip_vs_ftp);
पूर्ण

अटल काष्ठा pernet_operations ip_vs_ftp_ops = अणु
	.init = __ip_vs_ftp_init,
	.निकास = __ip_vs_ftp_निकास,
पूर्ण;

अटल पूर्णांक __init ip_vs_ftp_init(व्योम)
अणु
	/* rcu_barrier() is called by netns on error */
	वापस रेजिस्टर_pernet_subsys(&ip_vs_ftp_ops);
पूर्ण

/*
 *	ip_vs_ftp finish.
 */
अटल व्योम __निकास ip_vs_ftp_निकास(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&ip_vs_ftp_ops);
	/* rcu_barrier() is called by netns */
पूर्ण


module_init(ip_vs_ftp_init);
module_निकास(ip_vs_ftp_निकास);
MODULE_LICENSE("GPL");
