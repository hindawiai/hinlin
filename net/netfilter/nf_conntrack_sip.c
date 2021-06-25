<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* SIP extension क्रम IP connection tracking.
 *
 * (C) 2005 by Christian Hentschel <chentschel@arnet.com.ar>
 * based on RR's ip_conntrack_ftp.c and other modules.
 * (C) 2007 United Security Providers
 * (C) 2007, 2008 Patrick McHardy <kaber@trash.net>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/inet.h>
#समावेश <linux/in.h>
#समावेश <linux/udp.h>
#समावेश <linux/tcp.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/netfilter_ipv6.h>

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_expect.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <linux/netfilter/nf_conntrack_sip.h>

#घोषणा HELPER_NAME "sip"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Hentschel <chentschel@arnet.com.ar>");
MODULE_DESCRIPTION("SIP connection tracking helper");
MODULE_ALIAS("ip_conntrack_sip");
MODULE_ALIAS_NFCT_HELPER(HELPER_NAME);

#घोषणा MAX_PORTS	8
अटल अचिन्हित लघु ports[MAX_PORTS];
अटल अचिन्हित पूर्णांक ports_c;
module_param_array(ports, uलघु, &ports_c, 0400);
MODULE_PARM_DESC(ports, "port numbers of SIP servers");

अटल अचिन्हित पूर्णांक sip_समयout __पढ़ो_mostly = SIP_TIMEOUT;
module_param(sip_समयout, uपूर्णांक, 0600);
MODULE_PARM_DESC(sip_समयout, "timeout for the master SIP session");

अटल पूर्णांक sip_direct_संकेतling __पढ़ो_mostly = 1;
module_param(sip_direct_संकेतling, पूर्णांक, 0600);
MODULE_PARM_DESC(sip_direct_संकेतling, "expect incoming calls from registrar "
					"only (default 1)");

अटल पूर्णांक sip_direct_media __पढ़ो_mostly = 1;
module_param(sip_direct_media, पूर्णांक, 0600);
MODULE_PARM_DESC(sip_direct_media, "Expect Media streams between signalling "
				   "endpoints only (default 1)");

अटल पूर्णांक sip_बाह्यal_media __पढ़ो_mostly = 0;
module_param(sip_बाह्यal_media, पूर्णांक, 0600);
MODULE_PARM_DESC(sip_बाह्यal_media, "Expect Media streams between external "
				     "endpoints (default 0)");

स्थिर काष्ठा nf_nat_sip_hooks *nf_nat_sip_hooks;
EXPORT_SYMBOL_GPL(nf_nat_sip_hooks);

अटल पूर्णांक string_len(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
		      स्थिर अक्षर *limit, पूर्णांक *shअगरt)
अणु
	पूर्णांक len = 0;

	जबतक (dptr < limit && है_अक्षर(*dptr)) अणु
		dptr++;
		len++;
	पूर्ण
	वापस len;
पूर्ण

अटल पूर्णांक digits_len(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
		      स्थिर अक्षर *limit, पूर्णांक *shअगरt)
अणु
	पूर्णांक len = 0;
	जबतक (dptr < limit && है_अंक(*dptr)) अणु
		dptr++;
		len++;
	पूर्ण
	वापस len;
पूर्ण

अटल पूर्णांक iswordc(स्थिर अक्षर c)
अणु
	अगर (है_अक्षर_अंक(c) || c == '!' || c == '"' || c == '%' ||
	    (c >= '(' && c <= '+') || c == ':' || c == '<' || c == '>' ||
	    c == '?' || (c >= '[' && c <= ']') || c == '_' || c == '`' ||
	    c == '{' || c == '}' || c == '~' || (c >= '-' && c <= '/') ||
	    c == '\'')
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक word_len(स्थिर अक्षर *dptr, स्थिर अक्षर *limit)
अणु
	पूर्णांक len = 0;
	जबतक (dptr < limit && iswordc(*dptr)) अणु
		dptr++;
		len++;
	पूर्ण
	वापस len;
पूर्ण

अटल पूर्णांक callid_len(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
		      स्थिर अक्षर *limit, पूर्णांक *shअगरt)
अणु
	पूर्णांक len, करोमुख्य_len;

	len = word_len(dptr, limit);
	dptr += len;
	अगर (!len || dptr == limit || *dptr != '@')
		वापस len;
	dptr++;
	len++;

	करोमुख्य_len = word_len(dptr, limit);
	अगर (!करोमुख्य_len)
		वापस 0;
	वापस len + करोमुख्य_len;
पूर्ण

/* get media type + port length */
अटल पूर्णांक media_len(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
		     स्थिर अक्षर *limit, पूर्णांक *shअगरt)
अणु
	पूर्णांक len = string_len(ct, dptr, limit, shअगरt);

	dptr += len;
	अगर (dptr >= limit || *dptr != ' ')
		वापस 0;
	len++;
	dptr++;

	वापस len + digits_len(ct, dptr, limit, shअगरt);
पूर्ण

अटल पूर्णांक sip_parse_addr(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *cp,
			  स्थिर अक्षर **endp, जोड़ nf_inet_addr *addr,
			  स्थिर अक्षर *limit, bool delim)
अणु
	स्थिर अक्षर *end;
	पूर्णांक ret;

	अगर (!ct)
		वापस 0;

	स_रखो(addr, 0, माप(*addr));
	चयन (nf_ct_l3num(ct)) अणु
	हाल AF_INET:
		ret = in4_pton(cp, limit - cp, (u8 *)&addr->ip, -1, &end);
		अगर (ret == 0)
			वापस 0;
		अवरोध;
	हाल AF_INET6:
		अगर (cp < limit && *cp == '[')
			cp++;
		अन्यथा अगर (delim)
			वापस 0;

		ret = in6_pton(cp, limit - cp, (u8 *)&addr->ip6, -1, &end);
		अगर (ret == 0)
			वापस 0;

		अगर (end < limit && *end == ']')
			end++;
		अन्यथा अगर (delim)
			वापस 0;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (endp)
		*endp = end;
	वापस 1;
पूर्ण

/* skip ip address. वापसs its length. */
अटल पूर्णांक epaddr_len(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
		      स्थिर अक्षर *limit, पूर्णांक *shअगरt)
अणु
	जोड़ nf_inet_addr addr;
	स्थिर अक्षर *aux = dptr;

	अगर (!sip_parse_addr(ct, dptr, &dptr, &addr, limit, true)) अणु
		pr_debug("ip: %s parse failed.!\n", dptr);
		वापस 0;
	पूर्ण

	/* Port number */
	अगर (*dptr == ':') अणु
		dptr++;
		dptr += digits_len(ct, dptr, limit, shअगरt);
	पूर्ण
	वापस dptr - aux;
पूर्ण

/* get address length, skiping user info. */
अटल पूर्णांक skp_epaddr_len(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
			  स्थिर अक्षर *limit, पूर्णांक *shअगरt)
अणु
	स्थिर अक्षर *start = dptr;
	पूर्णांक s = *shअगरt;

	/* Search क्रम @, but stop at the end of the line.
	 * We are inside a sip: URI, so we करोn't need to worry about
	 * continuation lines. */
	जबतक (dptr < limit &&
	       *dptr != '@' && *dptr != '\r' && *dptr != '\n') अणु
		(*shअगरt)++;
		dptr++;
	पूर्ण

	अगर (dptr < limit && *dptr == '@') अणु
		dptr++;
		(*shअगरt)++;
	पूर्ण अन्यथा अणु
		dptr = start;
		*shअगरt = s;
	पूर्ण

	वापस epaddr_len(ct, dptr, limit, shअगरt);
पूर्ण

/* Parse a SIP request line of the क्रमm:
 *
 * Request-Line = Method SP Request-URI SP SIP-Version CRLF
 *
 * and वापस the offset and length of the address contained in the Request-URI.
 */
पूर्णांक ct_sip_parse_request(स्थिर काष्ठा nf_conn *ct,
			 स्थिर अक्षर *dptr, अचिन्हित पूर्णांक datalen,
			 अचिन्हित पूर्णांक *matchoff, अचिन्हित पूर्णांक *matchlen,
			 जोड़ nf_inet_addr *addr, __be16 *port)
अणु
	स्थिर अक्षर *start = dptr, *limit = dptr + datalen, *end;
	अचिन्हित पूर्णांक mlen;
	अचिन्हित पूर्णांक p;
	पूर्णांक shअगरt = 0;

	/* Skip method and following whitespace */
	mlen = string_len(ct, dptr, limit, शून्य);
	अगर (!mlen)
		वापस 0;
	dptr += mlen;
	अगर (++dptr >= limit)
		वापस 0;

	/* Find SIP URI */
	क्रम (; dptr < limit - म_माप("sip:"); dptr++) अणु
		अगर (*dptr == '\r' || *dptr == '\n')
			वापस -1;
		अगर (strnहालcmp(dptr, "sip:", म_माप("sip:")) == 0) अणु
			dptr += म_माप("sip:");
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!skp_epaddr_len(ct, dptr, limit, &shअगरt))
		वापस 0;
	dptr += shअगरt;

	अगर (!sip_parse_addr(ct, dptr, &end, addr, limit, true))
		वापस -1;
	अगर (end < limit && *end == ':') अणु
		end++;
		p = simple_म_से_अदीर्घ(end, (अक्षर **)&end, 10);
		अगर (p < 1024 || p > 65535)
			वापस -1;
		*port = htons(p);
	पूर्ण अन्यथा
		*port = htons(SIP_PORT);

	अगर (end == dptr)
		वापस 0;
	*matchoff = dptr - start;
	*matchlen = end - dptr;
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(ct_sip_parse_request);

/* SIP header parsing: SIP headers are located at the beginning of a line, but
 * may span several lines, in which हाल the continuation lines begin with a
 * whitespace अक्षरacter. RFC 2543 allows lines to be terminated with CR, LF or
 * CRLF, RFC 3261 allows only CRLF, we support both.
 *
 * Headers are followed by (optionally) whitespace, a colon, again (optionally)
 * whitespace and the values. Whitespace in this context means any amount of
 * tअसल, spaces and continuation lines, which are treated as a single whitespace
 * अक्षरacter.
 *
 * Some headers may appear multiple बार. A comma separated list of values is
 * equivalent to multiple headers.
 */
अटल स्थिर काष्ठा sip_header ct_sip_hdrs[] = अणु
	[SIP_HDR_CSEQ]			= SIP_HDR("CSeq", शून्य, शून्य, digits_len),
	[SIP_HDR_FROM]			= SIP_HDR("From", "f", "sip:", skp_epaddr_len),
	[SIP_HDR_TO]			= SIP_HDR("To", "t", "sip:", skp_epaddr_len),
	[SIP_HDR_CONTACT]		= SIP_HDR("Contact", "m", "sip:", skp_epaddr_len),
	[SIP_HDR_VIA_UDP]		= SIP_HDR("Via", "v", "UDP ", epaddr_len),
	[SIP_HDR_VIA_TCP]		= SIP_HDR("Via", "v", "TCP ", epaddr_len),
	[SIP_HDR_EXPIRES]		= SIP_HDR("Expires", शून्य, शून्य, digits_len),
	[SIP_HDR_CONTENT_LENGTH]	= SIP_HDR("Content-Length", "l", शून्य, digits_len),
	[SIP_HDR_CALL_ID]		= SIP_HDR("Call-Id", "i", शून्य, callid_len),
पूर्ण;

अटल स्थिर अक्षर *sip_follow_continuation(स्थिर अक्षर *dptr, स्थिर अक्षर *limit)
अणु
	/* Walk past newline */
	अगर (++dptr >= limit)
		वापस शून्य;

	/* Skip '\n' in CR LF */
	अगर (*(dptr - 1) == '\r' && *dptr == '\n') अणु
		अगर (++dptr >= limit)
			वापस शून्य;
	पूर्ण

	/* Continuation line? */
	अगर (*dptr != ' ' && *dptr != '\t')
		वापस शून्य;

	/* skip leading whitespace */
	क्रम (; dptr < limit; dptr++) अणु
		अगर (*dptr != ' ' && *dptr != '\t')
			अवरोध;
	पूर्ण
	वापस dptr;
पूर्ण

अटल स्थिर अक्षर *sip_skip_whitespace(स्थिर अक्षर *dptr, स्थिर अक्षर *limit)
अणु
	क्रम (; dptr < limit; dptr++) अणु
		अगर (*dptr == ' ' || *dptr == '\t')
			जारी;
		अगर (*dptr != '\r' && *dptr != '\n')
			अवरोध;
		dptr = sip_follow_continuation(dptr, limit);
		अवरोध;
	पूर्ण
	वापस dptr;
पूर्ण

/* Search within a SIP header value, dealing with continuation lines */
अटल स्थिर अक्षर *ct_sip_header_search(स्थिर अक्षर *dptr, स्थिर अक्षर *limit,
					स्थिर अक्षर *needle, अचिन्हित पूर्णांक len)
अणु
	क्रम (limit -= len; dptr < limit; dptr++) अणु
		अगर (*dptr == '\r' || *dptr == '\n') अणु
			dptr = sip_follow_continuation(dptr, limit);
			अगर (dptr == शून्य)
				अवरोध;
			जारी;
		पूर्ण

		अगर (strnहालcmp(dptr, needle, len) == 0)
			वापस dptr;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक ct_sip_get_header(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
		      अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक datalen,
		      क्रमागत sip_header_types type,
		      अचिन्हित पूर्णांक *matchoff, अचिन्हित पूर्णांक *matchlen)
अणु
	स्थिर काष्ठा sip_header *hdr = &ct_sip_hdrs[type];
	स्थिर अक्षर *start = dptr, *limit = dptr + datalen;
	पूर्णांक shअगरt = 0;

	क्रम (dptr += dataoff; dptr < limit; dptr++) अणु
		/* Find beginning of line */
		अगर (*dptr != '\r' && *dptr != '\n')
			जारी;
		अगर (++dptr >= limit)
			अवरोध;
		अगर (*(dptr - 1) == '\r' && *dptr == '\n') अणु
			अगर (++dptr >= limit)
				अवरोध;
		पूर्ण

		/* Skip continuation lines */
		अगर (*dptr == ' ' || *dptr == '\t')
			जारी;

		/* Find header. Compact headers must be followed by a
		 * non-alphabetic अक्षरacter to aव्योम mismatches. */
		अगर (limit - dptr >= hdr->len &&
		    strnहालcmp(dptr, hdr->name, hdr->len) == 0)
			dptr += hdr->len;
		अन्यथा अगर (hdr->cname && limit - dptr >= hdr->clen + 1 &&
			 strnहालcmp(dptr, hdr->cname, hdr->clen) == 0 &&
			 !है_अक्षर(*(dptr + hdr->clen)))
			dptr += hdr->clen;
		अन्यथा
			जारी;

		/* Find and skip colon */
		dptr = sip_skip_whitespace(dptr, limit);
		अगर (dptr == शून्य)
			अवरोध;
		अगर (*dptr != ':' || ++dptr >= limit)
			अवरोध;

		/* Skip whitespace after colon */
		dptr = sip_skip_whitespace(dptr, limit);
		अगर (dptr == शून्य)
			अवरोध;

		*matchoff = dptr - start;
		अगर (hdr->search) अणु
			dptr = ct_sip_header_search(dptr, limit, hdr->search,
						    hdr->slen);
			अगर (!dptr)
				वापस -1;
			dptr += hdr->slen;
		पूर्ण

		*matchlen = hdr->match_len(ct, dptr, limit, &shअगरt);
		अगर (!*matchlen)
			वापस -1;
		*matchoff = dptr - start + shअगरt;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ct_sip_get_header);

/* Get next header field in a list of comma separated values */
अटल पूर्णांक ct_sip_next_header(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
			      अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक datalen,
			      क्रमागत sip_header_types type,
			      अचिन्हित पूर्णांक *matchoff, अचिन्हित पूर्णांक *matchlen)
अणु
	स्थिर काष्ठा sip_header *hdr = &ct_sip_hdrs[type];
	स्थिर अक्षर *start = dptr, *limit = dptr + datalen;
	पूर्णांक shअगरt = 0;

	dptr += dataoff;

	dptr = ct_sip_header_search(dptr, limit, ",", म_माप(","));
	अगर (!dptr)
		वापस 0;

	dptr = ct_sip_header_search(dptr, limit, hdr->search, hdr->slen);
	अगर (!dptr)
		वापस 0;
	dptr += hdr->slen;

	*matchoff = dptr - start;
	*matchlen = hdr->match_len(ct, dptr, limit, &shअगरt);
	अगर (!*matchlen)
		वापस -1;
	*matchoff += shअगरt;
	वापस 1;
पूर्ण

/* Walk through headers until a parsable one is found or no header of the
 * given type is left. */
अटल पूर्णांक ct_sip_walk_headers(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
			       अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक datalen,
			       क्रमागत sip_header_types type, पूर्णांक *in_header,
			       अचिन्हित पूर्णांक *matchoff, अचिन्हित पूर्णांक *matchlen)
अणु
	पूर्णांक ret;

	अगर (in_header && *in_header) अणु
		जबतक (1) अणु
			ret = ct_sip_next_header(ct, dptr, dataoff, datalen,
						 type, matchoff, matchlen);
			अगर (ret > 0)
				वापस ret;
			अगर (ret == 0)
				अवरोध;
			dataoff += *matchoff;
		पूर्ण
		*in_header = 0;
	पूर्ण

	जबतक (1) अणु
		ret = ct_sip_get_header(ct, dptr, dataoff, datalen,
					type, matchoff, matchlen);
		अगर (ret > 0)
			अवरोध;
		अगर (ret == 0)
			वापस ret;
		dataoff += *matchoff;
	पूर्ण

	अगर (in_header)
		*in_header = 1;
	वापस 1;
पूर्ण

/* Locate a SIP header, parse the URI and वापस the offset and length of
 * the address as well as the address and port themselves. A stream of
 * headers can be parsed by handing in a non-शून्य datalen and in_header
 * poपूर्णांकer.
 */
पूर्णांक ct_sip_parse_header_uri(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
			    अचिन्हित पूर्णांक *dataoff, अचिन्हित पूर्णांक datalen,
			    क्रमागत sip_header_types type, पूर्णांक *in_header,
			    अचिन्हित पूर्णांक *matchoff, अचिन्हित पूर्णांक *matchlen,
			    जोड़ nf_inet_addr *addr, __be16 *port)
अणु
	स्थिर अक्षर *c, *limit = dptr + datalen;
	अचिन्हित पूर्णांक p;
	पूर्णांक ret;

	ret = ct_sip_walk_headers(ct, dptr, dataoff ? *dataoff : 0, datalen,
				  type, in_header, matchoff, matchlen);
	WARN_ON(ret < 0);
	अगर (ret == 0)
		वापस ret;

	अगर (!sip_parse_addr(ct, dptr + *matchoff, &c, addr, limit, true))
		वापस -1;
	अगर (*c == ':') अणु
		c++;
		p = simple_म_से_अदीर्घ(c, (अक्षर **)&c, 10);
		अगर (p < 1024 || p > 65535)
			वापस -1;
		*port = htons(p);
	पूर्ण अन्यथा
		*port = htons(SIP_PORT);

	अगर (dataoff)
		*dataoff = c - dptr;
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(ct_sip_parse_header_uri);

अटल पूर्णांक ct_sip_parse_param(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
			      अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक datalen,
			      स्थिर अक्षर *name,
			      अचिन्हित पूर्णांक *matchoff, अचिन्हित पूर्णांक *matchlen)
अणु
	स्थिर अक्षर *limit = dptr + datalen;
	स्थिर अक्षर *start;
	स्थिर अक्षर *end;

	limit = ct_sip_header_search(dptr + dataoff, limit, ",", म_माप(","));
	अगर (!limit)
		limit = dptr + datalen;

	start = ct_sip_header_search(dptr + dataoff, limit, name, म_माप(name));
	अगर (!start)
		वापस 0;
	start += म_माप(name);

	end = ct_sip_header_search(start, limit, ";", म_माप(";"));
	अगर (!end)
		end = limit;

	*matchoff = start - dptr;
	*matchlen = end - start;
	वापस 1;
पूर्ण

/* Parse address from header parameter and वापस address, offset and length */
पूर्णांक ct_sip_parse_address_param(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
			       अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक datalen,
			       स्थिर अक्षर *name,
			       अचिन्हित पूर्णांक *matchoff, अचिन्हित पूर्णांक *matchlen,
			       जोड़ nf_inet_addr *addr, bool delim)
अणु
	स्थिर अक्षर *limit = dptr + datalen;
	स्थिर अक्षर *start, *end;

	limit = ct_sip_header_search(dptr + dataoff, limit, ",", म_माप(","));
	अगर (!limit)
		limit = dptr + datalen;

	start = ct_sip_header_search(dptr + dataoff, limit, name, म_माप(name));
	अगर (!start)
		वापस 0;

	start += म_माप(name);
	अगर (!sip_parse_addr(ct, start, &end, addr, limit, delim))
		वापस 0;
	*matchoff = start - dptr;
	*matchlen = end - start;
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(ct_sip_parse_address_param);

/* Parse numerical header parameter and वापस value, offset and length */
पूर्णांक ct_sip_parse_numerical_param(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
				 अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक datalen,
				 स्थिर अक्षर *name,
				 अचिन्हित पूर्णांक *matchoff, अचिन्हित पूर्णांक *matchlen,
				 अचिन्हित पूर्णांक *val)
अणु
	स्थिर अक्षर *limit = dptr + datalen;
	स्थिर अक्षर *start;
	अक्षर *end;

	limit = ct_sip_header_search(dptr + dataoff, limit, ",", म_माप(","));
	अगर (!limit)
		limit = dptr + datalen;

	start = ct_sip_header_search(dptr + dataoff, limit, name, म_माप(name));
	अगर (!start)
		वापस 0;

	start += म_माप(name);
	*val = simple_म_से_अदीर्घ(start, &end, 0);
	अगर (start == end)
		वापस 0;
	अगर (matchoff && matchlen) अणु
		*matchoff = start - dptr;
		*matchlen = end - start;
	पूर्ण
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(ct_sip_parse_numerical_param);

अटल पूर्णांक ct_sip_parse_transport(काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
				  अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक datalen,
				  u8 *proto)
अणु
	अचिन्हित पूर्णांक matchoff, matchlen;

	अगर (ct_sip_parse_param(ct, dptr, dataoff, datalen, "transport=",
			       &matchoff, &matchlen)) अणु
		अगर (!strnहालcmp(dptr + matchoff, "TCP", म_माप("TCP")))
			*proto = IPPROTO_TCP;
		अन्यथा अगर (!strnहालcmp(dptr + matchoff, "UDP", म_माप("UDP")))
			*proto = IPPROTO_UDP;
		अन्यथा
			वापस 0;

		अगर (*proto != nf_ct_protonum(ct))
			वापस 0;
	पूर्ण अन्यथा
		*proto = nf_ct_protonum(ct);

	वापस 1;
पूर्ण

अटल पूर्णांक sdp_parse_addr(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *cp,
			  स्थिर अक्षर **endp, जोड़ nf_inet_addr *addr,
			  स्थिर अक्षर *limit)
अणु
	स्थिर अक्षर *end;
	पूर्णांक ret;

	स_रखो(addr, 0, माप(*addr));
	चयन (nf_ct_l3num(ct)) अणु
	हाल AF_INET:
		ret = in4_pton(cp, limit - cp, (u8 *)&addr->ip, -1, &end);
		अवरोध;
	हाल AF_INET6:
		ret = in6_pton(cp, limit - cp, (u8 *)&addr->ip6, -1, &end);
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (ret == 0)
		वापस 0;
	अगर (endp)
		*endp = end;
	वापस 1;
पूर्ण

/* skip ip address. वापसs its length. */
अटल पूर्णांक sdp_addr_len(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
			स्थिर अक्षर *limit, पूर्णांक *shअगरt)
अणु
	जोड़ nf_inet_addr addr;
	स्थिर अक्षर *aux = dptr;

	अगर (!sdp_parse_addr(ct, dptr, &dptr, &addr, limit)) अणु
		pr_debug("ip: %s parse failed.!\n", dptr);
		वापस 0;
	पूर्ण

	वापस dptr - aux;
पूर्ण

/* SDP header parsing: a SDP session description contains an ordered set of
 * headers, starting with a section containing general session parameters,
 * optionally followed by multiple media descriptions.
 *
 * SDP headers always start at the beginning of a line. According to RFC 2327:
 * "The sequence CRLF (0x0d0a) is used to end a record, although parsers should
 * be tolerant and also accept records terminated with a single newline
 * अक्षरacter". We handle both हालs.
 */
अटल स्थिर काष्ठा sip_header ct_sdp_hdrs_v4[] = अणु
	[SDP_HDR_VERSION]	= SDP_HDR("v=", शून्य, digits_len),
	[SDP_HDR_OWNER]		= SDP_HDR("o=", "IN IP4 ", sdp_addr_len),
	[SDP_HDR_CONNECTION]	= SDP_HDR("c=", "IN IP4 ", sdp_addr_len),
	[SDP_HDR_MEDIA]		= SDP_HDR("m=", शून्य, media_len),
पूर्ण;

अटल स्थिर काष्ठा sip_header ct_sdp_hdrs_v6[] = अणु
	[SDP_HDR_VERSION]	= SDP_HDR("v=", शून्य, digits_len),
	[SDP_HDR_OWNER]		= SDP_HDR("o=", "IN IP6 ", sdp_addr_len),
	[SDP_HDR_CONNECTION]	= SDP_HDR("c=", "IN IP6 ", sdp_addr_len),
	[SDP_HDR_MEDIA]		= SDP_HDR("m=", शून्य, media_len),
पूर्ण;

/* Linear string search within SDP header values */
अटल स्थिर अक्षर *ct_sdp_header_search(स्थिर अक्षर *dptr, स्थिर अक्षर *limit,
					स्थिर अक्षर *needle, अचिन्हित पूर्णांक len)
अणु
	क्रम (limit -= len; dptr < limit; dptr++) अणु
		अगर (*dptr == '\r' || *dptr == '\n')
			अवरोध;
		अगर (म_भेदन(dptr, needle, len) == 0)
			वापस dptr;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Locate a SDP header (optionally a substring within the header value),
 * optionally stopping at the first occurrence of the term header, parse
 * it and वापस the offset and length of the data we're पूर्णांकerested in.
 */
पूर्णांक ct_sip_get_sdp_header(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
			  अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक datalen,
			  क्रमागत sdp_header_types type,
			  क्रमागत sdp_header_types term,
			  अचिन्हित पूर्णांक *matchoff, अचिन्हित पूर्णांक *matchlen)
अणु
	स्थिर काष्ठा sip_header *hdrs, *hdr, *thdr;
	स्थिर अक्षर *start = dptr, *limit = dptr + datalen;
	पूर्णांक shअगरt = 0;

	hdrs = nf_ct_l3num(ct) == NFPROTO_IPV4 ? ct_sdp_hdrs_v4 : ct_sdp_hdrs_v6;
	hdr = &hdrs[type];
	thdr = &hdrs[term];

	क्रम (dptr += dataoff; dptr < limit; dptr++) अणु
		/* Find beginning of line */
		अगर (*dptr != '\r' && *dptr != '\n')
			जारी;
		अगर (++dptr >= limit)
			अवरोध;
		अगर (*(dptr - 1) == '\r' && *dptr == '\n') अणु
			अगर (++dptr >= limit)
				अवरोध;
		पूर्ण

		अगर (term != SDP_HDR_UNSPEC &&
		    limit - dptr >= thdr->len &&
		    strnहालcmp(dptr, thdr->name, thdr->len) == 0)
			अवरोध;
		अन्यथा अगर (limit - dptr >= hdr->len &&
			 strnहालcmp(dptr, hdr->name, hdr->len) == 0)
			dptr += hdr->len;
		अन्यथा
			जारी;

		*matchoff = dptr - start;
		अगर (hdr->search) अणु
			dptr = ct_sdp_header_search(dptr, limit, hdr->search,
						    hdr->slen);
			अगर (!dptr)
				वापस -1;
			dptr += hdr->slen;
		पूर्ण

		*matchlen = hdr->match_len(ct, dptr, limit, &shअगरt);
		अगर (!*matchlen)
			वापस -1;
		*matchoff = dptr - start + shअगरt;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ct_sip_get_sdp_header);

अटल पूर्णांक ct_sip_parse_sdp_addr(स्थिर काष्ठा nf_conn *ct, स्थिर अक्षर *dptr,
				 अचिन्हित पूर्णांक dataoff, अचिन्हित पूर्णांक datalen,
				 क्रमागत sdp_header_types type,
				 क्रमागत sdp_header_types term,
				 अचिन्हित पूर्णांक *matchoff, अचिन्हित पूर्णांक *matchlen,
				 जोड़ nf_inet_addr *addr)
अणु
	पूर्णांक ret;

	ret = ct_sip_get_sdp_header(ct, dptr, dataoff, datalen, type, term,
				    matchoff, matchlen);
	अगर (ret <= 0)
		वापस ret;

	अगर (!sdp_parse_addr(ct, dptr + *matchoff, शून्य, addr,
			    dptr + *matchoff + *matchlen))
		वापस -1;
	वापस 1;
पूर्ण

अटल पूर्णांक refresh_संकेतling_expectation(काष्ठा nf_conn *ct,
					  जोड़ nf_inet_addr *addr,
					  u8 proto, __be16 port,
					  अचिन्हित पूर्णांक expires)
अणु
	काष्ठा nf_conn_help *help = nfct_help(ct);
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा hlist_node *next;
	पूर्णांक found = 0;

	spin_lock_bh(&nf_conntrack_expect_lock);
	hlist_क्रम_each_entry_safe(exp, next, &help->expectations, lnode) अणु
		अगर (exp->class != SIP_EXPECT_SIGNALLING ||
		    !nf_inet_addr_cmp(&exp->tuple.dst.u3, addr) ||
		    exp->tuple.dst.protonum != proto ||
		    exp->tuple.dst.u.udp.port != port)
			जारी;
		अगर (mod_समयr_pending(&exp->समयout, jअगरfies + expires * HZ)) अणु
			exp->flags &= ~NF_CT_EXPECT_INACTIVE;
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&nf_conntrack_expect_lock);
	वापस found;
पूर्ण

अटल व्योम flush_expectations(काष्ठा nf_conn *ct, bool media)
अणु
	काष्ठा nf_conn_help *help = nfct_help(ct);
	काष्ठा nf_conntrack_expect *exp;
	काष्ठा hlist_node *next;

	spin_lock_bh(&nf_conntrack_expect_lock);
	hlist_क्रम_each_entry_safe(exp, next, &help->expectations, lnode) अणु
		अगर ((exp->class != SIP_EXPECT_SIGNALLING) ^ media)
			जारी;
		अगर (!nf_ct_हटाओ_expect(exp))
			जारी;
		अगर (!media)
			अवरोध;
	पूर्ण
	spin_unlock_bh(&nf_conntrack_expect_lock);
पूर्ण

अटल पूर्णांक set_expected_rtp_rtcp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				 अचिन्हित पूर्णांक dataoff,
				 स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				 जोड़ nf_inet_addr *daddr, __be16 port,
				 क्रमागत sip_expectation_classes class,
				 अचिन्हित पूर्णांक mediaoff, अचिन्हित पूर्णांक medialen)
अणु
	काष्ठा nf_conntrack_expect *exp, *rtp_exp, *rtcp_exp;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	काष्ठा net *net = nf_ct_net(ct);
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	जोड़ nf_inet_addr *saddr;
	काष्ठा nf_conntrack_tuple tuple;
	पूर्णांक direct_rtp = 0, skip_expect = 0, ret = NF_DROP;
	u_पूर्णांक16_t base_port;
	__be16 rtp_port, rtcp_port;
	स्थिर काष्ठा nf_nat_sip_hooks *hooks;

	saddr = शून्य;
	अगर (sip_direct_media) अणु
		अगर (!nf_inet_addr_cmp(daddr, &ct->tuplehash[dir].tuple.src.u3))
			वापस NF_ACCEPT;
		saddr = &ct->tuplehash[!dir].tuple.src.u3;
	पूर्ण अन्यथा अगर (sip_बाह्यal_media) अणु
		काष्ठा net_device *dev = skb_dst(skb)->dev;
		काष्ठा net *net = dev_net(dev);
		काष्ठा flowi fl;
		काष्ठा dst_entry *dst = शून्य;

		स_रखो(&fl, 0, माप(fl));

		चयन (nf_ct_l3num(ct)) अणु
			हाल NFPROTO_IPV4:
				fl.u.ip4.daddr = daddr->ip;
				nf_ip_route(net, &dst, &fl, false);
				अवरोध;

			हाल NFPROTO_IPV6:
				fl.u.ip6.daddr = daddr->in6;
				nf_ip6_route(net, &dst, &fl, false);
				अवरोध;
		पूर्ण

		/* Don't predict any conntracks when media endpoपूर्णांक is reachable
		 * through the same पूर्णांकerface as the संकेतling peer.
		 */
		अगर (dst) अणु
			bool बाह्यal_media = (dst->dev == dev);

			dst_release(dst);
			अगर (बाह्यal_media)
				वापस NF_ACCEPT;
		पूर्ण
	पूर्ण

	/* We need to check whether the registration exists beक्रमe attempting
	 * to रेजिस्टर it since we can see the same media description multiple
	 * बार on dअगरferent connections in हाल multiple endpoपूर्णांकs receive
	 * the same call.
	 *
	 * RTP optimization: अगर we find a matching media channel expectation
	 * and both the expectation and this connection are SNATed, we assume
	 * both sides can reach each other directly and use the final
	 * destination address from the expectation. We still need to keep
	 * the NATed expectations क्रम media that might arrive from the
	 * outside, and additionally need to expect the direct RTP stream
	 * in हाल it passes through us even without NAT.
	 */
	स_रखो(&tuple, 0, माप(tuple));
	अगर (saddr)
		tuple.src.u3 = *saddr;
	tuple.src.l3num		= nf_ct_l3num(ct);
	tuple.dst.protonum	= IPPROTO_UDP;
	tuple.dst.u3		= *daddr;
	tuple.dst.u.udp.port	= port;

	करो अणु
		exp = __nf_ct_expect_find(net, nf_ct_zone(ct), &tuple);

		अगर (!exp || exp->master == ct ||
		    nfct_help(exp->master)->helper != nfct_help(ct)->helper ||
		    exp->class != class)
			अवरोध;
#अगर IS_ENABLED(CONFIG_NF_NAT)
		अगर (!direct_rtp &&
		    (!nf_inet_addr_cmp(&exp->saved_addr, &exp->tuple.dst.u3) ||
		     exp->saved_proto.udp.port != exp->tuple.dst.u.udp.port) &&
		    ct->status & IPS_NAT_MASK) अणु
			*daddr			= exp->saved_addr;
			tuple.dst.u3		= exp->saved_addr;
			tuple.dst.u.udp.port	= exp->saved_proto.udp.port;
			direct_rtp = 1;
		पूर्ण अन्यथा
#पूर्ण_अगर
			skip_expect = 1;
	पूर्ण जबतक (!skip_expect);

	base_port = ntohs(tuple.dst.u.udp.port) & ~1;
	rtp_port = htons(base_port);
	rtcp_port = htons(base_port + 1);

	अगर (direct_rtp) अणु
		hooks = rcu_dereference(nf_nat_sip_hooks);
		अगर (hooks &&
		    !hooks->sdp_port(skb, protoff, dataoff, dptr, datalen,
				     mediaoff, medialen, ntohs(rtp_port)))
			जाओ err1;
	पूर्ण

	अगर (skip_expect)
		वापस NF_ACCEPT;

	rtp_exp = nf_ct_expect_alloc(ct);
	अगर (rtp_exp == शून्य)
		जाओ err1;
	nf_ct_expect_init(rtp_exp, class, nf_ct_l3num(ct), saddr, daddr,
			  IPPROTO_UDP, शून्य, &rtp_port);

	rtcp_exp = nf_ct_expect_alloc(ct);
	अगर (rtcp_exp == शून्य)
		जाओ err2;
	nf_ct_expect_init(rtcp_exp, class, nf_ct_l3num(ct), saddr, daddr,
			  IPPROTO_UDP, शून्य, &rtcp_port);

	hooks = rcu_dereference(nf_nat_sip_hooks);
	अगर (hooks && ct->status & IPS_NAT_MASK && !direct_rtp)
		ret = hooks->sdp_media(skb, protoff, dataoff, dptr,
				       datalen, rtp_exp, rtcp_exp,
				       mediaoff, medialen, daddr);
	अन्यथा अणु
		/* -EALREADY handling works around end-poपूर्णांकs that send
		 * SDP messages with identical port but dअगरferent media type,
		 * we pretend expectation was set up.
		 * It also works in the हाल that SDP messages are sent with
		 * identical expect tuples but क्रम dअगरferent master conntracks.
		 */
		पूर्णांक errp = nf_ct_expect_related(rtp_exp,
						NF_CT_EXP_F_SKIP_MASTER);

		अगर (errp == 0 || errp == -EALREADY) अणु
			पूर्णांक errcp = nf_ct_expect_related(rtcp_exp,
						NF_CT_EXP_F_SKIP_MASTER);

			अगर (errcp == 0 || errcp == -EALREADY)
				ret = NF_ACCEPT;
			अन्यथा अगर (errp == 0)
				nf_ct_unexpect_related(rtp_exp);
		पूर्ण
	पूर्ण
	nf_ct_expect_put(rtcp_exp);
err2:
	nf_ct_expect_put(rtp_exp);
err1:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sdp_media_type sdp_media_types[] = अणु
	SDP_MEDIA_TYPE("audio ", SIP_EXPECT_AUDIO),
	SDP_MEDIA_TYPE("video ", SIP_EXPECT_VIDEO),
	SDP_MEDIA_TYPE("image ", SIP_EXPECT_IMAGE),
पूर्ण;

अटल स्थिर काष्ठा sdp_media_type *sdp_media_type(स्थिर अक्षर *dptr,
						   अचिन्हित पूर्णांक matchoff,
						   अचिन्हित पूर्णांक matchlen)
अणु
	स्थिर काष्ठा sdp_media_type *t;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sdp_media_types); i++) अणु
		t = &sdp_media_types[i];
		अगर (matchlen < t->len ||
		    म_भेदन(dptr + matchoff, t->name, t->len))
			जारी;
		वापस t;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक process_sdp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
		       अचिन्हित पूर्णांक dataoff,
		       स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
		       अचिन्हित पूर्णांक cseq)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	अचिन्हित पूर्णांक matchoff, matchlen;
	अचिन्हित पूर्णांक mediaoff, medialen;
	अचिन्हित पूर्णांक sdpoff;
	अचिन्हित पूर्णांक caddr_len, maddr_len;
	अचिन्हित पूर्णांक i;
	जोड़ nf_inet_addr caddr, maddr, rtp_addr;
	स्थिर काष्ठा nf_nat_sip_hooks *hooks;
	अचिन्हित पूर्णांक port;
	स्थिर काष्ठा sdp_media_type *t;
	पूर्णांक ret = NF_ACCEPT;

	hooks = rcu_dereference(nf_nat_sip_hooks);

	/* Find beginning of session description */
	अगर (ct_sip_get_sdp_header(ct, *dptr, 0, *datalen,
				  SDP_HDR_VERSION, SDP_HDR_UNSPEC,
				  &matchoff, &matchlen) <= 0)
		वापस NF_ACCEPT;
	sdpoff = matchoff;

	/* The connection inक्रमmation is contained in the session description
	 * and/or once per media description. The first media description marks
	 * the end of the session description. */
	caddr_len = 0;
	अगर (ct_sip_parse_sdp_addr(ct, *dptr, sdpoff, *datalen,
				  SDP_HDR_CONNECTION, SDP_HDR_MEDIA,
				  &matchoff, &matchlen, &caddr) > 0)
		caddr_len = matchlen;

	mediaoff = sdpoff;
	क्रम (i = 0; i < ARRAY_SIZE(sdp_media_types); ) अणु
		अगर (ct_sip_get_sdp_header(ct, *dptr, mediaoff, *datalen,
					  SDP_HDR_MEDIA, SDP_HDR_UNSPEC,
					  &mediaoff, &medialen) <= 0)
			अवरोध;

		/* Get media type and port number. A media port value of zero
		 * indicates an inactive stream. */
		t = sdp_media_type(*dptr, mediaoff, medialen);
		अगर (!t) अणु
			mediaoff += medialen;
			जारी;
		पूर्ण
		mediaoff += t->len;
		medialen -= t->len;

		port = simple_म_से_अदीर्घ(*dptr + mediaoff, शून्य, 10);
		अगर (port == 0)
			जारी;
		अगर (port < 1024 || port > 65535) अणु
			nf_ct_helper_log(skb, ct, "wrong port %u", port);
			वापस NF_DROP;
		पूर्ण

		/* The media description overrides the session description. */
		maddr_len = 0;
		अगर (ct_sip_parse_sdp_addr(ct, *dptr, mediaoff, *datalen,
					  SDP_HDR_CONNECTION, SDP_HDR_MEDIA,
					  &matchoff, &matchlen, &maddr) > 0) अणु
			maddr_len = matchlen;
			स_नकल(&rtp_addr, &maddr, माप(rtp_addr));
		पूर्ण अन्यथा अगर (caddr_len)
			स_नकल(&rtp_addr, &caddr, माप(rtp_addr));
		अन्यथा अणु
			nf_ct_helper_log(skb, ct, "cannot parse SDP message");
			वापस NF_DROP;
		पूर्ण

		ret = set_expected_rtp_rtcp(skb, protoff, dataoff,
					    dptr, datalen,
					    &rtp_addr, htons(port), t->class,
					    mediaoff, medialen);
		अगर (ret != NF_ACCEPT) अणु
			nf_ct_helper_log(skb, ct,
					 "cannot add expectation for voice");
			वापस ret;
		पूर्ण

		/* Update media connection address अगर present */
		अगर (maddr_len && hooks && ct->status & IPS_NAT_MASK) अणु
			ret = hooks->sdp_addr(skb, protoff, dataoff,
					      dptr, datalen, mediaoff,
					      SDP_HDR_CONNECTION,
					      SDP_HDR_MEDIA,
					      &rtp_addr);
			अगर (ret != NF_ACCEPT) अणु
				nf_ct_helper_log(skb, ct, "cannot mangle SDP");
				वापस ret;
			पूर्ण
		पूर्ण
		i++;
	पूर्ण

	/* Update session connection and owner addresses */
	hooks = rcu_dereference(nf_nat_sip_hooks);
	अगर (hooks && ct->status & IPS_NAT_MASK)
		ret = hooks->sdp_session(skb, protoff, dataoff,
					 dptr, datalen, sdpoff,
					 &rtp_addr);

	वापस ret;
पूर्ण
अटल पूर्णांक process_invite_response(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				   अचिन्हित पूर्णांक dataoff,
				   स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				   अचिन्हित पूर्णांक cseq, अचिन्हित पूर्णांक code)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	काष्ठा nf_ct_sip_master *ct_sip_info = nfct_help_data(ct);

	अगर ((code >= 100 && code <= 199) ||
	    (code >= 200 && code <= 299))
		वापस process_sdp(skb, protoff, dataoff, dptr, datalen, cseq);
	अन्यथा अगर (ct_sip_info->invite_cseq == cseq)
		flush_expectations(ct, true);
	वापस NF_ACCEPT;
पूर्ण

अटल पूर्णांक process_update_response(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				   अचिन्हित पूर्णांक dataoff,
				   स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				   अचिन्हित पूर्णांक cseq, अचिन्हित पूर्णांक code)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	काष्ठा nf_ct_sip_master *ct_sip_info = nfct_help_data(ct);

	अगर ((code >= 100 && code <= 199) ||
	    (code >= 200 && code <= 299))
		वापस process_sdp(skb, protoff, dataoff, dptr, datalen, cseq);
	अन्यथा अगर (ct_sip_info->invite_cseq == cseq)
		flush_expectations(ct, true);
	वापस NF_ACCEPT;
पूर्ण

अटल पूर्णांक process_prack_response(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				  अचिन्हित पूर्णांक dataoff,
				  स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				  अचिन्हित पूर्णांक cseq, अचिन्हित पूर्णांक code)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	काष्ठा nf_ct_sip_master *ct_sip_info = nfct_help_data(ct);

	अगर ((code >= 100 && code <= 199) ||
	    (code >= 200 && code <= 299))
		वापस process_sdp(skb, protoff, dataoff, dptr, datalen, cseq);
	अन्यथा अगर (ct_sip_info->invite_cseq == cseq)
		flush_expectations(ct, true);
	वापस NF_ACCEPT;
पूर्ण

अटल पूर्णांक process_invite_request(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				  अचिन्हित पूर्णांक dataoff,
				  स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				  अचिन्हित पूर्णांक cseq)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	काष्ठा nf_ct_sip_master *ct_sip_info = nfct_help_data(ct);
	अचिन्हित पूर्णांक ret;

	flush_expectations(ct, true);
	ret = process_sdp(skb, protoff, dataoff, dptr, datalen, cseq);
	अगर (ret == NF_ACCEPT)
		ct_sip_info->invite_cseq = cseq;
	वापस ret;
पूर्ण

अटल पूर्णांक process_bye_request(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			       अचिन्हित पूर्णांक dataoff,
			       स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
			       अचिन्हित पूर्णांक cseq)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);

	flush_expectations(ct, true);
	वापस NF_ACCEPT;
पूर्ण

/* Parse a REGISTER request and create a permanent expectation क्रम incoming
 * संकेतling connections. The expectation is marked inactive and is activated
 * when receiving a response indicating success from the registrar.
 */
अटल पूर्णांक process_रेजिस्टर_request(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				    अचिन्हित पूर्णांक dataoff,
				    स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				    अचिन्हित पूर्णांक cseq)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	काष्ठा nf_ct_sip_master *ct_sip_info = nfct_help_data(ct);
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	अचिन्हित पूर्णांक matchoff, matchlen;
	काष्ठा nf_conntrack_expect *exp;
	जोड़ nf_inet_addr *saddr, daddr;
	स्थिर काष्ठा nf_nat_sip_hooks *hooks;
	__be16 port;
	u8 proto;
	अचिन्हित पूर्णांक expires = 0;
	पूर्णांक ret;

	/* Expected connections can not रेजिस्टर again. */
	अगर (ct->status & IPS_EXPECTED)
		वापस NF_ACCEPT;

	/* We must check the expiration समय: a value of zero संकेतs the
	 * registrar to release the binding. We'll हटाओ our expectation
	 * when receiving the new bindings in the response, but we करोn't
	 * want to create new ones.
	 *
	 * The expiration समय may be contained in Expires: header, the
	 * Contact: header parameters or the URI parameters.
	 */
	अगर (ct_sip_get_header(ct, *dptr, 0, *datalen, SIP_HDR_EXPIRES,
			      &matchoff, &matchlen) > 0)
		expires = simple_म_से_अदीर्घ(*dptr + matchoff, शून्य, 10);

	ret = ct_sip_parse_header_uri(ct, *dptr, शून्य, *datalen,
				      SIP_HDR_CONTACT, शून्य,
				      &matchoff, &matchlen, &daddr, &port);
	अगर (ret < 0) अणु
		nf_ct_helper_log(skb, ct, "cannot parse contact");
		वापस NF_DROP;
	पूर्ण अन्यथा अगर (ret == 0)
		वापस NF_ACCEPT;

	/* We करोn't support third-party registrations */
	अगर (!nf_inet_addr_cmp(&ct->tuplehash[dir].tuple.src.u3, &daddr))
		वापस NF_ACCEPT;

	अगर (ct_sip_parse_transport(ct, *dptr, matchoff + matchlen, *datalen,
				   &proto) == 0)
		वापस NF_ACCEPT;

	अगर (ct_sip_parse_numerical_param(ct, *dptr,
					 matchoff + matchlen, *datalen,
					 "expires=", शून्य, शून्य, &expires) < 0) अणु
		nf_ct_helper_log(skb, ct, "cannot parse expires");
		वापस NF_DROP;
	पूर्ण

	अगर (expires == 0) अणु
		ret = NF_ACCEPT;
		जाओ store_cseq;
	पूर्ण

	exp = nf_ct_expect_alloc(ct);
	अगर (!exp) अणु
		nf_ct_helper_log(skb, ct, "cannot alloc expectation");
		वापस NF_DROP;
	पूर्ण

	saddr = शून्य;
	अगर (sip_direct_संकेतling)
		saddr = &ct->tuplehash[!dir].tuple.src.u3;

	nf_ct_expect_init(exp, SIP_EXPECT_SIGNALLING, nf_ct_l3num(ct),
			  saddr, &daddr, proto, शून्य, &port);
	exp->समयout.expires = sip_समयout * HZ;
	exp->helper = nfct_help(ct)->helper;
	exp->flags = NF_CT_EXPECT_PERMANENT | NF_CT_EXPECT_INACTIVE;

	hooks = rcu_dereference(nf_nat_sip_hooks);
	अगर (hooks && ct->status & IPS_NAT_MASK)
		ret = hooks->expect(skb, protoff, dataoff, dptr, datalen,
				    exp, matchoff, matchlen);
	अन्यथा अणु
		अगर (nf_ct_expect_related(exp, 0) != 0) अणु
			nf_ct_helper_log(skb, ct, "cannot add expectation");
			ret = NF_DROP;
		पूर्ण अन्यथा
			ret = NF_ACCEPT;
	पूर्ण
	nf_ct_expect_put(exp);

store_cseq:
	अगर (ret == NF_ACCEPT)
		ct_sip_info->रेजिस्टर_cseq = cseq;
	वापस ret;
पूर्ण

अटल पूर्णांक process_रेजिस्टर_response(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				     अचिन्हित पूर्णांक dataoff,
				     स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen,
				     अचिन्हित पूर्णांक cseq, अचिन्हित पूर्णांक code)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	काष्ठा nf_ct_sip_master *ct_sip_info = nfct_help_data(ct);
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	जोड़ nf_inet_addr addr;
	__be16 port;
	u8 proto;
	अचिन्हित पूर्णांक matchoff, matchlen, coff = 0;
	अचिन्हित पूर्णांक expires = 0;
	पूर्णांक in_contact = 0, ret;

	/* According to RFC 3261, "UAs MUST NOT send a new registration until
	 * they have received a final response from the registrar क्रम the
	 * previous one or the previous REGISTER request has समयd out".
	 *
	 * However, some servers fail to detect retransmissions and send late
	 * responses, so we store the sequence number of the last valid
	 * request and compare it here.
	 */
	अगर (ct_sip_info->रेजिस्टर_cseq != cseq)
		वापस NF_ACCEPT;

	अगर (code >= 100 && code <= 199)
		वापस NF_ACCEPT;
	अगर (code < 200 || code > 299)
		जाओ flush;

	अगर (ct_sip_get_header(ct, *dptr, 0, *datalen, SIP_HDR_EXPIRES,
			      &matchoff, &matchlen) > 0)
		expires = simple_म_से_अदीर्घ(*dptr + matchoff, शून्य, 10);

	जबतक (1) अणु
		अचिन्हित पूर्णांक c_expires = expires;

		ret = ct_sip_parse_header_uri(ct, *dptr, &coff, *datalen,
					      SIP_HDR_CONTACT, &in_contact,
					      &matchoff, &matchlen,
					      &addr, &port);
		अगर (ret < 0) अणु
			nf_ct_helper_log(skb, ct, "cannot parse contact");
			वापस NF_DROP;
		पूर्ण अन्यथा अगर (ret == 0)
			अवरोध;

		/* We करोn't support third-party registrations */
		अगर (!nf_inet_addr_cmp(&ct->tuplehash[dir].tuple.dst.u3, &addr))
			जारी;

		अगर (ct_sip_parse_transport(ct, *dptr, matchoff + matchlen,
					   *datalen, &proto) == 0)
			जारी;

		ret = ct_sip_parse_numerical_param(ct, *dptr,
						   matchoff + matchlen,
						   *datalen, "expires=",
						   शून्य, शून्य, &c_expires);
		अगर (ret < 0) अणु
			nf_ct_helper_log(skb, ct, "cannot parse expires");
			वापस NF_DROP;
		पूर्ण
		अगर (c_expires == 0)
			अवरोध;
		अगर (refresh_संकेतling_expectation(ct, &addr, proto, port,
						   c_expires))
			वापस NF_ACCEPT;
	पूर्ण

flush:
	flush_expectations(ct, false);
	वापस NF_ACCEPT;
पूर्ण

अटल स्थिर काष्ठा sip_handler sip_handlers[] = अणु
	SIP_HANDLER("INVITE", process_invite_request, process_invite_response),
	SIP_HANDLER("UPDATE", process_sdp, process_update_response),
	SIP_HANDLER("ACK", process_sdp, शून्य),
	SIP_HANDLER("PRACK", process_sdp, process_prack_response),
	SIP_HANDLER("BYE", process_bye_request, शून्य),
	SIP_HANDLER("REGISTER", process_रेजिस्टर_request, process_रेजिस्टर_response),
पूर्ण;

अटल पूर्णांक process_sip_response(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
				अचिन्हित पूर्णांक dataoff,
				स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	अचिन्हित पूर्णांक matchoff, matchlen, matchend;
	अचिन्हित पूर्णांक code, cseq, i;

	अगर (*datalen < म_माप("SIP/2.0 200"))
		वापस NF_ACCEPT;
	code = simple_म_से_अदीर्घ(*dptr + म_माप("SIP/2.0 "), शून्य, 10);
	अगर (!code) अणु
		nf_ct_helper_log(skb, ct, "cannot get code");
		वापस NF_DROP;
	पूर्ण

	अगर (ct_sip_get_header(ct, *dptr, 0, *datalen, SIP_HDR_CSEQ,
			      &matchoff, &matchlen) <= 0) अणु
		nf_ct_helper_log(skb, ct, "cannot parse cseq");
		वापस NF_DROP;
	पूर्ण
	cseq = simple_म_से_अदीर्घ(*dptr + matchoff, शून्य, 10);
	अगर (!cseq && *(*dptr + matchoff) != '0') अणु
		nf_ct_helper_log(skb, ct, "cannot get cseq");
		वापस NF_DROP;
	पूर्ण
	matchend = matchoff + matchlen + 1;

	क्रम (i = 0; i < ARRAY_SIZE(sip_handlers); i++) अणु
		स्थिर काष्ठा sip_handler *handler;

		handler = &sip_handlers[i];
		अगर (handler->response == शून्य)
			जारी;
		अगर (*datalen < matchend + handler->len ||
		    strnहालcmp(*dptr + matchend, handler->method, handler->len))
			जारी;
		वापस handler->response(skb, protoff, dataoff, dptr, datalen,
					 cseq, code);
	पूर्ण
	वापस NF_ACCEPT;
पूर्ण

अटल पूर्णांक process_sip_request(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			       अचिन्हित पूर्णांक dataoff,
			       स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);
	काष्ठा nf_ct_sip_master *ct_sip_info = nfct_help_data(ct);
	क्रमागत ip_conntrack_dir dir = CTINFO2सूची(ctinfo);
	अचिन्हित पूर्णांक matchoff, matchlen;
	अचिन्हित पूर्णांक cseq, i;
	जोड़ nf_inet_addr addr;
	__be16 port;

	/* Many Cisco IP phones use a high source port क्रम SIP requests, but
	 * listen क्रम the response on port 5060.  If we are the local
	 * router क्रम one of these phones, save the port number from the
	 * Via: header so that nf_nat_sip can redirect the responses to
	 * the correct port.
	 */
	अगर (ct_sip_parse_header_uri(ct, *dptr, शून्य, *datalen,
				    SIP_HDR_VIA_UDP, शून्य, &matchoff,
				    &matchlen, &addr, &port) > 0 &&
	    port != ct->tuplehash[dir].tuple.src.u.udp.port &&
	    nf_inet_addr_cmp(&addr, &ct->tuplehash[dir].tuple.src.u3))
		ct_sip_info->क्रमced_dport = port;

	क्रम (i = 0; i < ARRAY_SIZE(sip_handlers); i++) अणु
		स्थिर काष्ठा sip_handler *handler;

		handler = &sip_handlers[i];
		अगर (handler->request == शून्य)
			जारी;
		अगर (*datalen < handler->len + 2 ||
		    strnहालcmp(*dptr, handler->method, handler->len))
			जारी;
		अगर ((*dptr)[handler->len] != ' ' ||
		    !है_अक्षर((*dptr)[handler->len+1]))
			जारी;

		अगर (ct_sip_get_header(ct, *dptr, 0, *datalen, SIP_HDR_CSEQ,
				      &matchoff, &matchlen) <= 0) अणु
			nf_ct_helper_log(skb, ct, "cannot parse cseq");
			वापस NF_DROP;
		पूर्ण
		cseq = simple_म_से_अदीर्घ(*dptr + matchoff, शून्य, 10);
		अगर (!cseq && *(*dptr + matchoff) != '0') अणु
			nf_ct_helper_log(skb, ct, "cannot get cseq");
			वापस NF_DROP;
		पूर्ण

		वापस handler->request(skb, protoff, dataoff, dptr, datalen,
					cseq);
	पूर्ण
	वापस NF_ACCEPT;
पूर्ण

अटल पूर्णांक process_sip_msg(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			   अचिन्हित पूर्णांक protoff, अचिन्हित पूर्णांक dataoff,
			   स्थिर अक्षर **dptr, अचिन्हित पूर्णांक *datalen)
अणु
	स्थिर काष्ठा nf_nat_sip_hooks *hooks;
	पूर्णांक ret;

	अगर (strnहालcmp(*dptr, "SIP/2.0 ", म_माप("SIP/2.0 ")) != 0)
		ret = process_sip_request(skb, protoff, dataoff, dptr, datalen);
	अन्यथा
		ret = process_sip_response(skb, protoff, dataoff, dptr, datalen);

	अगर (ret == NF_ACCEPT && ct->status & IPS_NAT_MASK) अणु
		hooks = rcu_dereference(nf_nat_sip_hooks);
		अगर (hooks && !hooks->msg(skb, protoff, dataoff,
					 dptr, datalen)) अणु
			nf_ct_helper_log(skb, ct, "cannot NAT SIP message");
			ret = NF_DROP;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sip_help_tcp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo)
अणु
	काष्ठा tcphdr *th, _tcph;
	अचिन्हित पूर्णांक dataoff, datalen;
	अचिन्हित पूर्णांक matchoff, matchlen, clen;
	अचिन्हित पूर्णांक msglen, origlen;
	स्थिर अक्षर *dptr, *end;
	s16 dअगरf, tdअगरf = 0;
	पूर्णांक ret = NF_ACCEPT;
	bool term;

	अगर (ctinfo != IP_CT_ESTABLISHED &&
	    ctinfo != IP_CT_ESTABLISHED_REPLY)
		वापस NF_ACCEPT;

	/* No Data ? */
	th = skb_header_poपूर्णांकer(skb, protoff, माप(_tcph), &_tcph);
	अगर (th == शून्य)
		वापस NF_ACCEPT;
	dataoff = protoff + th->करोff * 4;
	अगर (dataoff >= skb->len)
		वापस NF_ACCEPT;

	nf_ct_refresh(ct, skb, sip_समयout * HZ);

	अगर (unlikely(skb_linearize(skb)))
		वापस NF_DROP;

	dptr = skb->data + dataoff;
	datalen = skb->len - dataoff;
	अगर (datalen < म_माप("SIP/2.0 200"))
		वापस NF_ACCEPT;

	जबतक (1) अणु
		अगर (ct_sip_get_header(ct, dptr, 0, datalen,
				      SIP_HDR_CONTENT_LENGTH,
				      &matchoff, &matchlen) <= 0)
			अवरोध;

		clen = simple_म_से_अदीर्घ(dptr + matchoff, (अक्षर **)&end, 10);
		अगर (dptr + matchoff == end)
			अवरोध;

		term = false;
		क्रम (; end + म_माप("\r\n\r\n") <= dptr + datalen; end++) अणु
			अगर (end[0] == '\r' && end[1] == '\n' &&
			    end[2] == '\r' && end[3] == '\n') अणु
				term = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!term)
			अवरोध;
		end += म_माप("\r\n\r\n") + clen;

		msglen = origlen = end - dptr;
		अगर (msglen > datalen)
			वापस NF_ACCEPT;

		ret = process_sip_msg(skb, ct, protoff, dataoff,
				      &dptr, &msglen);
		/* process_sip_* functions report why this packet is dropped */
		अगर (ret != NF_ACCEPT)
			अवरोध;
		dअगरf     = msglen - origlen;
		tdअगरf   += dअगरf;

		dataoff += msglen;
		dptr    += msglen;
		datalen  = datalen + dअगरf - msglen;
	पूर्ण

	अगर (ret == NF_ACCEPT && ct->status & IPS_NAT_MASK) अणु
		स्थिर काष्ठा nf_nat_sip_hooks *hooks;

		hooks = rcu_dereference(nf_nat_sip_hooks);
		अगर (hooks)
			hooks->seq_adjust(skb, protoff, tdअगरf);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sip_help_udp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक protoff,
			काष्ठा nf_conn *ct, क्रमागत ip_conntrack_info ctinfo)
अणु
	अचिन्हित पूर्णांक dataoff, datalen;
	स्थिर अक्षर *dptr;

	/* No Data ? */
	dataoff = protoff + माप(काष्ठा udphdr);
	अगर (dataoff >= skb->len)
		वापस NF_ACCEPT;

	nf_ct_refresh(ct, skb, sip_समयout * HZ);

	अगर (unlikely(skb_linearize(skb)))
		वापस NF_DROP;

	dptr = skb->data + dataoff;
	datalen = skb->len - dataoff;
	अगर (datalen < म_माप("SIP/2.0 200"))
		वापस NF_ACCEPT;

	वापस process_sip_msg(skb, ct, protoff, dataoff, &dptr, &datalen);
पूर्ण

अटल काष्ठा nf_conntrack_helper sip[MAX_PORTS * 4] __पढ़ो_mostly;

अटल स्थिर काष्ठा nf_conntrack_expect_policy sip_exp_policy[SIP_EXPECT_MAX + 1] = अणु
	[SIP_EXPECT_SIGNALLING] = अणु
		.name		= "signalling",
		.max_expected	= 1,
		.समयout	= 3 * 60,
	पूर्ण,
	[SIP_EXPECT_AUDIO] = अणु
		.name		= "audio",
		.max_expected	= 2 * IP_CT_सूची_MAX,
		.समयout	= 3 * 60,
	पूर्ण,
	[SIP_EXPECT_VIDEO] = अणु
		.name		= "video",
		.max_expected	= 2 * IP_CT_सूची_MAX,
		.समयout	= 3 * 60,
	पूर्ण,
	[SIP_EXPECT_IMAGE] = अणु
		.name		= "image",
		.max_expected	= IP_CT_सूची_MAX,
		.समयout	= 3 * 60,
	पूर्ण,
पूर्ण;

अटल व्योम __निकास nf_conntrack_sip_fini(व्योम)
अणु
	nf_conntrack_helpers_unरेजिस्टर(sip, ports_c * 4);
पूर्ण

अटल पूर्णांक __init nf_conntrack_sip_init(व्योम)
अणु
	पूर्णांक i, ret;

	NF_CT_HELPER_BUILD_BUG_ON(माप(काष्ठा nf_ct_sip_master));

	अगर (ports_c == 0)
		ports[ports_c++] = SIP_PORT;

	क्रम (i = 0; i < ports_c; i++) अणु
		nf_ct_helper_init(&sip[4 * i], AF_INET, IPPROTO_UDP,
				  HELPER_NAME, SIP_PORT, ports[i], i,
				  sip_exp_policy, SIP_EXPECT_MAX, sip_help_udp,
				  शून्य, THIS_MODULE);
		nf_ct_helper_init(&sip[4 * i + 1], AF_INET, IPPROTO_TCP,
				  HELPER_NAME, SIP_PORT, ports[i], i,
				  sip_exp_policy, SIP_EXPECT_MAX, sip_help_tcp,
				  शून्य, THIS_MODULE);
		nf_ct_helper_init(&sip[4 * i + 2], AF_INET6, IPPROTO_UDP,
				  HELPER_NAME, SIP_PORT, ports[i], i,
				  sip_exp_policy, SIP_EXPECT_MAX, sip_help_udp,
				  शून्य, THIS_MODULE);
		nf_ct_helper_init(&sip[4 * i + 3], AF_INET6, IPPROTO_TCP,
				  HELPER_NAME, SIP_PORT, ports[i], i,
				  sip_exp_policy, SIP_EXPECT_MAX, sip_help_tcp,
				  शून्य, THIS_MODULE);
	पूर्ण

	ret = nf_conntrack_helpers_रेजिस्टर(sip, ports_c * 4);
	अगर (ret < 0) अणु
		pr_err("failed to register helpers\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

module_init(nf_conntrack_sip_init);
module_निकास(nf_conntrack_sip_fini);
