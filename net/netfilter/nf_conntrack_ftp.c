<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* FTP extension क्रम connection tracking. */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2004 Netfilter Core Team <coreteam@netfilter.org>
 * (C) 2003,2004 USAGI/WIDE Project <http://www.linux-ipv6.org>
 * (C) 2006-2012 Patrick McHardy <kaber@trash.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/ip.h>
#समावेश <linux/slab.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/inet.h>
#समावेश <net/checksum.h>
#समावेश <net/tcp.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_ecache.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <linux/netfilter/nf_conntrack_ftp.h>

#घोषणा HELPER_NAME "ftp"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rusty Russell <rusty@rustcorp.com.au>");
MODULE_DESCRIPTION("ftp connection tracking helper");
MODULE_ALIAS("ip_conntrack_ftp");
MODULE_ALIAS_NFCT_HELPER(HELPER_NAME);

/* This is slow, but it's simple. --RR */
अटल अक्षर *ftp_buffer;

अटल DEFINE_SPINLOCK(nf_ftp_lock);

#घोषणा MAX_PORTS 8
अटल u_पूर्णांक16_t ports[MAX_PORTS];
अटल अचिन्हित पूर्णांक ports_c;
module_param_array(ports, uलघु, &ports_c, 0400);

अटल bool loose;
module_param(loose, bool, 0600);

अचिन्हित पूर्णांक (*nf_nat_ftp_hook)(काष्ठा sk_buff *skb,
				क्रमागत ip_conntrack_info ctinfo,
				क्रमागत nf_ct_ftp_type type,
				अचिन्हित पूर्णांक protoff,
				अचिन्हित पूर्णांक matchoff,
				अचिन्हित पूर्णांक matchlen,
				काष्ठा nf_conntrack_expect *exp);
EXPORT_SYMBOL_GPL(nf_nat_ftp_hook);

अटल पूर्णांक try_rfc959(स्थिर अक्षर *, माप_प्रकार, काष्ठा nf_conntrack_man *,
		      अक्षर, अचिन्हित पूर्णांक *);
अटल पूर्णांक try_rfc1123(स्थिर अक्षर *, माप_प्रकार, काष्ठा nf_conntrack_man *,
		       अक्षर, अचिन्हित पूर्णांक *);
अटल पूर्णांक try_eprt(स्थिर अक्षर *, माप_प्रकार, काष्ठा nf_conntrack_man *,
		    अक्षर, अचिन्हित पूर्णांक *);
अटल पूर्णांक try_epsv_response(स्थिर अक्षर *, माप_प्रकार, काष्ठा nf_conntrack_man *,
			     अक्षर, अचिन्हित पूर्णांक *);

अटल काष्ठा ftp_search अणु
	स्थिर अक्षर *pattern;
	माप_प्रकार plen;
	अक्षर skip;
	अक्षर term;
	क्रमागत nf_ct_ftp_type ftptype;
	पूर्णांक (*getnum)(स्थिर अक्षर *, माप_प्रकार, काष्ठा nf_conntrack_man *, अक्षर, अचिन्हित पूर्णांक *);
पूर्ण search[IP_CT_सूची_MAX][2] = अणु
	[IP_CT_सूची_ORIGINAL] = अणु
		अणु
			.pattern	= "PORT",
			.plen		= माप("PORT") - 1,
			.skip		= ' ',
			.term		= '\r',
			.ftptype	= NF_CT_FTP_PORT,
			.getnum		= try_rfc959,
		पूर्ण,
		अणु
			.pattern	= "EPRT",
			.plen		= माप("EPRT") - 1,
			.skip		= ' ',
			.term		= '\r',
			.ftptype	= NF_CT_FTP_EPRT,
			.getnum		= try_eprt,
		पूर्ण,
	पूर्ण,
	[IP_CT_सूची_REPLY] = अणु
		अणु
			.pattern	= "227 ",
			.plen		= माप("227 ") - 1,
			.ftptype	= NF_CT_FTP_PASV,
			.getnum		= try_rfc1123,
		पूर्ण,
		अणु
			.pattern	= "229 ",
			.plen		= माप("229 ") - 1,
			.skip		= '(',
			.term		= ')',
			.ftptype	= NF_CT_FTP_EPSV,
			.getnum		= try_epsv_response,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक
get_ipv6_addr(स्थिर अक्षर *src, माप_प्रकार dlen, काष्ठा in6_addr *dst, u_पूर्णांक8_t term)
अणु
	स्थिर अक्षर *end;
	पूर्णांक ret = in6_pton(src, min_t(माप_प्रकार, dlen, 0xffff), (u8 *)dst, term, &end);
	अगर (ret > 0)
		वापस (पूर्णांक)(end - src);
	वापस 0;
पूर्ण

अटल पूर्णांक try_number(स्थिर अक्षर *data, माप_प्रकार dlen, u_पूर्णांक32_t array[],
		      पूर्णांक array_size, अक्षर sep, अक्षर term)
अणु
	u_पूर्णांक32_t i, len;

	स_रखो(array, 0, माप(array[0])*array_size);

	/* Keep data poपूर्णांकing at next अक्षर. */
	क्रम (i = 0, len = 0; len < dlen && i < array_size; len++, data++) अणु
		अगर (*data >= '0' && *data <= '9') अणु
			array[i] = array[i]*10 + *data - '0';
		पूर्ण
		अन्यथा अगर (*data == sep)
			i++;
		अन्यथा अणु
			/* Unexpected अक्षरacter; true अगर it's the
			   terminator (or we करोn't care about one)
			   and we're finished. */
			अगर ((*data == term || !term) && i == array_size - 1)
				वापस len;

			pr_debug("Char %u (got %u nums) `%u' unexpected\n",
				 len, i, *data);
			वापस 0;
		पूर्ण
	पूर्ण
	pr_debug("Failed to fill %u numbers separated by %c\n",
		 array_size, sep);
	वापस 0;
पूर्ण

/* Returns 0, or length of numbers: 192,168,1,1,5,6 */
अटल पूर्णांक try_rfc959(स्थिर अक्षर *data, माप_प्रकार dlen,
		      काष्ठा nf_conntrack_man *cmd, अक्षर term,
		      अचिन्हित पूर्णांक *offset)
अणु
	पूर्णांक length;
	u_पूर्णांक32_t array[6];

	length = try_number(data, dlen, array, 6, ',', term);
	अगर (length == 0)
		वापस 0;

	cmd->u3.ip = htonl((array[0] << 24) | (array[1] << 16) |
				    (array[2] << 8) | array[3]);
	cmd->u.tcp.port = htons((array[4] << 8) | array[5]);
	वापस length;
पूर्ण

/*
 * From RFC 1123:
 * The क्रमmat of the 227 reply to a PASV command is not
 * well standardized.  In particular, an FTP client cannot
 * assume that the parentheses shown on page 40 of RFC-959
 * will be present (and in fact, Figure 3 on page 43 omits
 * them).  Thereक्रमe, a User-FTP program that पूर्णांकerprets
 * the PASV reply must scan the reply क्रम the first digit
 * of the host and port numbers.
 */
अटल पूर्णांक try_rfc1123(स्थिर अक्षर *data, माप_प्रकार dlen,
		       काष्ठा nf_conntrack_man *cmd, अक्षर term,
		       अचिन्हित पूर्णांक *offset)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < dlen; i++)
		अगर (है_अंक(data[i]))
			अवरोध;

	अगर (i == dlen)
		वापस 0;

	*offset += i;

	वापस try_rfc959(data + i, dlen - i, cmd, 0, offset);
पूर्ण

/* Grab port: number up to delimiter */
अटल पूर्णांक get_port(स्थिर अक्षर *data, पूर्णांक start, माप_प्रकार dlen, अक्षर delim,
		    __be16 *port)
अणु
	u_पूर्णांक16_t पंचांगp_port = 0;
	पूर्णांक i;

	क्रम (i = start; i < dlen; i++) अणु
		/* Finished? */
		अगर (data[i] == delim) अणु
			अगर (पंचांगp_port == 0)
				अवरोध;
			*port = htons(पंचांगp_port);
			pr_debug("get_port: return %d\n", पंचांगp_port);
			वापस i + 1;
		पूर्ण
		अन्यथा अगर (data[i] >= '0' && data[i] <= '9')
			पंचांगp_port = पंचांगp_port*10 + data[i] - '0';
		अन्यथा अणु /* Some other crap */
			pr_debug("get_port: invalid char.\n");
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Returns 0, or length of numbers: |1|132.235.1.2|6275| or |2|3ffe::1|6275| */
अटल पूर्णांक try_eprt(स्थिर अक्षर *data, माप_प्रकार dlen, काष्ठा nf_conntrack_man *cmd,
		    अक्षर term, अचिन्हित पूर्णांक *offset)
अणु
	अक्षर delim;
	पूर्णांक length;

	/* First अक्षरacter is delimiter, then "1" क्रम IPv4 or "2" क्रम IPv6,
	   then delimiter again. */
	अगर (dlen <= 3) अणु
		pr_debug("EPRT: too short\n");
		वापस 0;
	पूर्ण
	delim = data[0];
	अगर (है_अंक(delim) || delim < 33 || delim > 126 || data[2] != delim) अणु
		pr_debug("try_eprt: invalid delimiter.\n");
		वापस 0;
	पूर्ण

	अगर ((cmd->l3num == PF_INET && data[1] != '1') ||
	    (cmd->l3num == PF_INET6 && data[1] != '2')) अणु
		pr_debug("EPRT: invalid protocol number.\n");
		वापस 0;
	पूर्ण

	pr_debug("EPRT: Got %c%c%c\n", delim, data[1], delim);

	अगर (data[1] == '1') अणु
		u_पूर्णांक32_t array[4];

		/* Now we have IP address. */
		length = try_number(data + 3, dlen - 3, array, 4, '.', delim);
		अगर (length != 0)
			cmd->u3.ip = htonl((array[0] << 24) | (array[1] << 16)
					   | (array[2] << 8) | array[3]);
	पूर्ण अन्यथा अणु
		/* Now we have IPv6 address. */
		length = get_ipv6_addr(data + 3, dlen - 3,
				       (काष्ठा in6_addr *)cmd->u3.ip6, delim);
	पूर्ण

	अगर (length == 0)
		वापस 0;
	pr_debug("EPRT: Got IP address!\n");
	/* Start offset includes initial "|1|", and trailing delimiter */
	वापस get_port(data, 3 + length + 1, dlen, delim, &cmd->u.tcp.port);
पूर्ण

/* Returns 0, or length of numbers: |||6446| */
अटल पूर्णांक try_epsv_response(स्थिर अक्षर *data, माप_प्रकार dlen,
			     काष्ठा nf_conntrack_man *cmd, अक्षर term,
			     अचिन्हित पूर्णांक *offset)
अणु
	अक्षर delim;

	/* Three delimiters. */
	अगर (dlen <= 3) वापस 0;
	delim = data[0];
	अगर (है_अंक(delim) || delim < 33 || delim > 126 ||
	    data[1] != delim || data[2] != delim)
		वापस 0;

	वापस get_port(data, 3, dlen, delim, &cmd->u.tcp.port);
पूर्ण

/* Return 1 क्रम match, 0 क्रम accept, -1 क्रम partial. */
अटल पूर्णांक find_pattern(स्थिर अक्षर *data, माप_प्रकार dlen,
			स्थिर अक्षर *pattern, माप_प्रकार plen,
			अक्षर skip, अक्षर term,
			अचिन्हित पूर्णांक *numoff,
			अचिन्हित पूर्णांक *numlen,
			काष्ठा nf_conntrack_man *cmd,
			पूर्णांक (*getnum)(स्थिर अक्षर *, माप_प्रकार,
				      काष्ठा nf_conntrack_man *, अक्षर,
				      अचिन्हित पूर्णांक *))
अणु
	माप_प्रकार i = plen;

	pr_debug("find_pattern `%s': dlen = %zu\n", pattern, dlen);

	अगर (dlen <= plen) अणु
		/* Short packet: try क्रम partial? */
		अगर (strnहालcmp(data, pattern, dlen) == 0)
			वापस -1;
		अन्यथा वापस 0;
	पूर्ण

	अगर (strnहालcmp(data, pattern, plen) != 0)
		वापस 0;

	pr_debug("Pattern matches!\n");
	/* Now we've found the स्थिरant string, try to skip
	   to the 'skip' अक्षरacter */
	अगर (skip) अणु
		क्रम (i = plen; data[i] != skip; i++)
			अगर (i == dlen - 1) वापस -1;

		/* Skip over the last अक्षरacter */
		i++;
	पूर्ण

	pr_debug("Skipped up to 0x%hhx delimiter!\n", skip);

	*numoff = i;
	*numlen = getnum(data + i, dlen - i, cmd, term, numoff);
	अगर (!*numlen)
		वापस -1;

	pr_debug("Match succeeded!\n");
	वापस 1;
पूर्ण

/* Look up to see अगर we're just after a \न. */
अटल पूर्णांक find_nl_seq(u32 seq, स्थिर काष्ठा nf_ct_ftp_master *info, पूर्णांक dir)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < info->seq_aft_nl_num[dir]; i++)
		अगर (info->seq_aft_nl[dir][i] == seq)
			वापस 1;
	वापस 0;
पूर्ण

/* We करोn't update if it's older than what we have. */
अटल व्योम update_nl_seq(काष्ठा nf_conn *ct, u32 nl_seq,
			  काष्ठा nf_ct_ftp_master *info, पूर्णांक dir,
			  काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक i, oldest;

	/* Look क्रम oldest: अगर we find exact match, we're करोne. */
	क्रम (i = 0; i < info->seq_aft_nl_num[dir]; i++) अणु
		अगर (info->seq_aft_nl[dir][i] == nl_seq)
			वापस;
	पूर्ण

	अगर (info->seq_aft_nl_num[dir] < NUM_SEQ_TO_REMEMBER) अणु
		info->seq_aft_nl[dir][info->seq_aft_nl_num[dir]++] = nl_seq;
	पूर्ण अन्यथा अणु
		अगर (beक्रमe(info->seq_aft_nl[dir][0], info->seq_aft_nl[dir][1]))
			oldest = 0;
		अन्यथा
			oldest = 1;

		अगर (after(nl_seq, info->seq_aft_nl[dir][oldest]))
			info->seq_aft_nl[dir][oldest] = nl_seq;
	पूर्ण
पूर्ण

अटल पूर्णांक help(काष्ठा sk_buff *skb,
		अचिन्हित पूर्णांक protoff,
		काष्ठा nf_conn *ct,
		क्रमागत ip_conntrack_info ctinfo)
अणु
	अचिन्हित पूर्णांक dataoff, datalen;
	स्थिर काष्ठा tcphdr *th;
	काष्ठा tcphdr _tcph;
	स्थिर अक्षर *fb_ptr;
	पूर्णांक ret;
	u32 seq;
	पूर्णांक dir = CTINFO2सूची(ctinfo);
	अचिन्हित पूर्णांक matchlen, matchoff;
	काष्ठा nf_ct_ftp_master *ct_ftp_info = nfct_help_data(ct);
	काष्ठा nf_conntrack_expect *exp;
	जोड़ nf_inet_addr *daddr;
	काष्ठा nf_conntrack_man cmd = अणुपूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक found = 0, ends_in_nl;
	typeof(nf_nat_ftp_hook) nf_nat_ftp;

	/* Until there's been traffic both ways, don't look in packets. */
	अगर (ctinfo != IP_CT_ESTABLISHED &&
	    ctinfo != IP_CT_ESTABLISHED_REPLY) अणु
		pr_debug("ftp: Conntrackinfo = %u\n", ctinfo);
		वापस NF_ACCEPT;
	पूर्ण

	th = skb_header_poपूर्णांकer(skb, protoff, माप(_tcph), &_tcph);
	अगर (th == शून्य)
		वापस NF_ACCEPT;

	dataoff = protoff + th->करोff * 4;
	/* No data? */
	अगर (dataoff >= skb->len) अणु
		pr_debug("ftp: dataoff(%u) >= skblen(%u)\n", dataoff,
			 skb->len);
		वापस NF_ACCEPT;
	पूर्ण
	datalen = skb->len - dataoff;

	spin_lock_bh(&nf_ftp_lock);
	fb_ptr = skb_header_poपूर्णांकer(skb, dataoff, datalen, ftp_buffer);
	अगर (!fb_ptr) अणु
		spin_unlock_bh(&nf_ftp_lock);
		वापस NF_ACCEPT;
	पूर्ण

	ends_in_nl = (fb_ptr[datalen - 1] == '\n');
	seq = ntohl(th->seq) + datalen;

	/* Look up to see अगर we're just after a \न. */
	अगर (!find_nl_seq(ntohl(th->seq), ct_ftp_info, dir)) अणु
		/* We're picking up this, clear flags and let it जारी */
		अगर (unlikely(ct_ftp_info->flags[dir] & NF_CT_FTP_SEQ_PICKUP)) अणु
			ct_ftp_info->flags[dir] ^= NF_CT_FTP_SEQ_PICKUP;
			जाओ skip_nl_seq;
		पूर्ण

		/* Now अगर this ends in \न, update ftp info. */
		pr_debug("nf_conntrack_ftp: wrong seq pos %s(%u) or %s(%u)\n",
			 ct_ftp_info->seq_aft_nl_num[dir] > 0 ? "" : "(UNSET)",
			 ct_ftp_info->seq_aft_nl[dir][0],
			 ct_ftp_info->seq_aft_nl_num[dir] > 1 ? "" : "(UNSET)",
			 ct_ftp_info->seq_aft_nl[dir][1]);
		ret = NF_ACCEPT;
		जाओ out_update_nl;
	पूर्ण

skip_nl_seq:
	/* Initialize IP/IPv6 addr to expected address (it's not mentioned
	   in EPSV responses) */
	cmd.l3num = nf_ct_l3num(ct);
	स_नकल(cmd.u3.all, &ct->tuplehash[dir].tuple.src.u3.all,
	       माप(cmd.u3.all));

	क्रम (i = 0; i < ARRAY_SIZE(search[dir]); i++) अणु
		found = find_pattern(fb_ptr, datalen,
				     search[dir][i].pattern,
				     search[dir][i].plen,
				     search[dir][i].skip,
				     search[dir][i].term,
				     &matchoff, &matchlen,
				     &cmd,
				     search[dir][i].getnum);
		अगर (found) अवरोध;
	पूर्ण
	अगर (found == -1) अणु
		/* We करोn't usually drop packets.  After all, this is
		   connection tracking, not packet filtering.
		   However, it is necessary क्रम accurate tracking in
		   this हाल. */
		nf_ct_helper_log(skb, ct, "partial matching of `%s'",
			         search[dir][i].pattern);
		ret = NF_DROP;
		जाओ out;
	पूर्ण अन्यथा अगर (found == 0) अणु /* No match */
		ret = NF_ACCEPT;
		जाओ out_update_nl;
	पूर्ण

	pr_debug("conntrack_ftp: match `%.*s' (%u bytes at %u)\n",
		 matchlen, fb_ptr + matchoff,
		 matchlen, ntohl(th->seq) + matchoff);

	exp = nf_ct_expect_alloc(ct);
	अगर (exp == शून्य) अणु
		nf_ct_helper_log(skb, ct, "cannot alloc expectation");
		ret = NF_DROP;
		जाओ out;
	पूर्ण

	/* We refer to the reverse direction ("!dir") tuples here,
	 * because we're expecting something in the other direction.
	 * Doesn't matter unless NAT is happening.  */
	daddr = &ct->tuplehash[!dir].tuple.dst.u3;

	/* Update the ftp info */
	अगर ((cmd.l3num == nf_ct_l3num(ct)) &&
	    स_भेद(&cmd.u3.all, &ct->tuplehash[dir].tuple.src.u3.all,
		     माप(cmd.u3.all))) अणु
		/* Enrico Scholz's passive FTP to partially RNAT'd ftp
		   server: it really wants us to connect to a
		   dअगरferent IP address.  Simply करोn't record it क्रम
		   NAT. */
		अगर (cmd.l3num == PF_INET) अणु
			pr_debug("NOT RECORDING: %pI4 != %pI4\n",
				 &cmd.u3.ip,
				 &ct->tuplehash[dir].tuple.src.u3.ip);
		पूर्ण अन्यथा अणु
			pr_debug("NOT RECORDING: %pI6 != %pI6\n",
				 cmd.u3.ip6,
				 ct->tuplehash[dir].tuple.src.u3.ip6);
		पूर्ण

		/* Thanks to Cristiano Lincoln Mattos
		   <lincoln@cesar.org.br> क्रम reporting this potential
		   problem (DMZ machines खोलोing holes to पूर्णांकernal
		   networks, or the packet filter itself). */
		अगर (!loose) अणु
			ret = NF_ACCEPT;
			जाओ out_put_expect;
		पूर्ण
		daddr = &cmd.u3;
	पूर्ण

	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, cmd.l3num,
			  &ct->tuplehash[!dir].tuple.src.u3, daddr,
			  IPPROTO_TCP, शून्य, &cmd.u.tcp.port);

	/* Now, NAT might want to mangle the packet, and रेजिस्टर the
	 * (possibly changed) expectation itself. */
	nf_nat_ftp = rcu_dereference(nf_nat_ftp_hook);
	अगर (nf_nat_ftp && ct->status & IPS_NAT_MASK)
		ret = nf_nat_ftp(skb, ctinfo, search[dir][i].ftptype,
				 protoff, matchoff, matchlen, exp);
	अन्यथा अणु
		/* Can't expect this?  Best to drop packet now. */
		अगर (nf_ct_expect_related(exp, 0) != 0) अणु
			nf_ct_helper_log(skb, ct, "cannot add expectation");
			ret = NF_DROP;
		पूर्ण अन्यथा
			ret = NF_ACCEPT;
	पूर्ण

out_put_expect:
	nf_ct_expect_put(exp);

out_update_nl:
	/* Now अगर this ends in \न, update ftp info.  Seq may have been
	 * adjusted by NAT code. */
	अगर (ends_in_nl)
		update_nl_seq(ct, seq, ct_ftp_info, dir, skb);
 out:
	spin_unlock_bh(&nf_ftp_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक nf_ct_ftp_from_nlattr(काष्ठा nlattr *attr, काष्ठा nf_conn *ct)
अणु
	काष्ठा nf_ct_ftp_master *ftp = nfct_help_data(ct);

	/* This conntrack has been injected from user-space, always pick up
	 * sequence tracking. Otherwise, the first FTP command after the
	 * failover अवरोधs.
	 */
	ftp->flags[IP_CT_सूची_ORIGINAL] |= NF_CT_FTP_SEQ_PICKUP;
	ftp->flags[IP_CT_सूची_REPLY] |= NF_CT_FTP_SEQ_PICKUP;
	वापस 0;
पूर्ण

अटल काष्ठा nf_conntrack_helper ftp[MAX_PORTS * 2] __पढ़ो_mostly;

अटल स्थिर काष्ठा nf_conntrack_expect_policy ftp_exp_policy = अणु
	.max_expected	= 1,
	.समयout	= 5 * 60,
पूर्ण;

अटल व्योम __निकास nf_conntrack_ftp_fini(व्योम)
अणु
	nf_conntrack_helpers_unरेजिस्टर(ftp, ports_c * 2);
	kमुक्त(ftp_buffer);
पूर्ण

अटल पूर्णांक __init nf_conntrack_ftp_init(व्योम)
अणु
	पूर्णांक i, ret = 0;

	NF_CT_HELPER_BUILD_BUG_ON(माप(काष्ठा nf_ct_ftp_master));

	ftp_buffer = kदो_स्मृति(65536, GFP_KERNEL);
	अगर (!ftp_buffer)
		वापस -ENOMEM;

	अगर (ports_c == 0)
		ports[ports_c++] = FTP_PORT;

	/* FIXME should be configurable whether IPv4 and IPv6 FTP connections
		 are tracked or not - YK */
	क्रम (i = 0; i < ports_c; i++) अणु
		nf_ct_helper_init(&ftp[2 * i], AF_INET, IPPROTO_TCP,
				  HELPER_NAME, FTP_PORT, ports[i], ports[i],
				  &ftp_exp_policy, 0, help,
				  nf_ct_ftp_from_nlattr, THIS_MODULE);
		nf_ct_helper_init(&ftp[2 * i + 1], AF_INET6, IPPROTO_TCP,
				  HELPER_NAME, FTP_PORT, ports[i], ports[i],
				  &ftp_exp_policy, 0, help,
				  nf_ct_ftp_from_nlattr, THIS_MODULE);
	पूर्ण

	ret = nf_conntrack_helpers_रेजिस्टर(ftp, ports_c * 2);
	अगर (ret < 0) अणु
		pr_err("failed to register helpers\n");
		kमुक्त(ftp_buffer);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

module_init(nf_conntrack_ftp_init);
module_निकास(nf_conntrack_ftp_fini);
