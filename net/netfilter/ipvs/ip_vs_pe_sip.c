<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>

#समावेश <net/ip_vs.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <linux/netfilter/nf_conntrack_sip.h>

#अगर_घोषित CONFIG_IP_VS_DEBUG
अटल स्थिर अक्षर *ip_vs_dbg_callid(अक्षर *buf, माप_प्रकार buf_len,
				    स्थिर अक्षर *callid, माप_प्रकार callid_len,
				    पूर्णांक *idx)
अणु
	माप_प्रकार max_len = 64;
	माप_प्रकार len = min3(max_len, callid_len, buf_len - *idx - 1);
	स_नकल(buf + *idx, callid, len);
	buf[*idx+len] = '\0';
	*idx += len + 1;
	वापस buf + *idx - len;
पूर्ण

#घोषणा IP_VS_DEBUG_CALLID(callid, len)					\
	ip_vs_dbg_callid(ip_vs_dbg_buf, माप(ip_vs_dbg_buf),		\
			 callid, len, &ip_vs_dbg_idx)
#पूर्ण_अगर

अटल पूर्णांक get_callid(स्थिर अक्षर *dptr, अचिन्हित पूर्णांक dataoff,
		      अचिन्हित पूर्णांक datalen,
		      अचिन्हित पूर्णांक *matchoff, अचिन्हित पूर्णांक *matchlen)
अणु
	/* Find callid */
	जबतक (1) अणु
		पूर्णांक ret = ct_sip_get_header(शून्य, dptr, dataoff, datalen,
					    SIP_HDR_CALL_ID, matchoff,
					    matchlen);
		अगर (ret > 0)
			अवरोध;
		अगर (!ret)
			वापस -EINVAL;
		dataoff += *matchoff;
	पूर्ण

	/* Too large is useless */
	अगर (*matchlen > IP_VS_PEDATA_MAXLEN)
		वापस -EINVAL;

	/* SIP headers are always followed by a line terminator */
	अगर (*matchoff + *matchlen == datalen)
		वापस -EINVAL;

	/* RFC 2543 allows lines to be terminated with CR, LF or CRLF,
	 * RFC 3261 allows only CRLF, we support both. */
	अगर (*(dptr + *matchoff + *matchlen) != '\r' &&
	    *(dptr + *matchoff + *matchlen) != '\n')
		वापस -EINVAL;

	IP_VS_DBG_BUF(9, "SIP callid %s (%d bytes)\n",
		      IP_VS_DEBUG_CALLID(dptr + *matchoff, *matchlen),
		      *matchlen);
	वापस 0;
पूर्ण

अटल पूर्णांक
ip_vs_sip_fill_param(काष्ठा ip_vs_conn_param *p, काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_vs_iphdr iph;
	अचिन्हित पूर्णांक dataoff, datalen, matchoff, matchlen;
	स्थिर अक्षर *dptr;
	पूर्णांक retc;

	retc = ip_vs_fill_iph_skb(p->af, skb, false, &iph);

	/* Only useful with UDP */
	अगर (!retc || iph.protocol != IPPROTO_UDP)
		वापस -EINVAL;
	/* toकरो: IPv6 fragments:
	 *       I think this only should be करोne क्रम the first fragment. /HS
	 */
	dataoff = iph.len + माप(काष्ठा udphdr);

	अगर (dataoff >= skb->len)
		वापस -EINVAL;
	retc = skb_linearize(skb);
	अगर (retc < 0)
		वापस retc;
	dptr = skb->data + dataoff;
	datalen = skb->len - dataoff;

	अगर (get_callid(dptr, 0, datalen, &matchoff, &matchlen))
		वापस -EINVAL;

	/* N.B: pe_data is only set on success,
	 * this allows fallback to the शेष persistence logic on failure
	 */
	p->pe_data = kmemdup(dptr + matchoff, matchlen, GFP_ATOMIC);
	अगर (!p->pe_data)
		वापस -ENOMEM;

	p->pe_data_len = matchlen;

	वापस 0;
पूर्ण

अटल bool ip_vs_sip_ct_match(स्थिर काष्ठा ip_vs_conn_param *p,
				  काष्ठा ip_vs_conn *ct)

अणु
	bool ret = false;

	अगर (ct->af == p->af &&
	    ip_vs_addr_equal(p->af, p->caddr, &ct->caddr) &&
	    /* protocol should only be IPPROTO_IP अगर
	     * d_addr is a fwmark */
	    ip_vs_addr_equal(p->protocol == IPPROTO_IP ? AF_UNSPEC : p->af,
			     p->vaddr, &ct->vaddr) &&
	    ct->vport == p->vport &&
	    ct->flags & IP_VS_CONN_F_TEMPLATE &&
	    ct->protocol == p->protocol &&
	    ct->pe_data && ct->pe_data_len == p->pe_data_len &&
	    !स_भेद(ct->pe_data, p->pe_data, p->pe_data_len))
		ret = true;

	IP_VS_DBG_BUF(9, "SIP template match %s %s->%s:%d %s\n",
		      ip_vs_proto_name(p->protocol),
		      IP_VS_DEBUG_CALLID(p->pe_data, p->pe_data_len),
		      IP_VS_DBG_ADDR(p->af, p->vaddr), ntohs(p->vport),
		      ret ? "hit" : "not hit");

	वापस ret;
पूर्ण

अटल u32 ip_vs_sip_hashkey_raw(स्थिर काष्ठा ip_vs_conn_param *p,
				 u32 initval, bool inverse)
अणु
	वापस jhash(p->pe_data, p->pe_data_len, initval);
पूर्ण

अटल पूर्णांक ip_vs_sip_show_pe_data(स्थिर काष्ठा ip_vs_conn *cp, अक्षर *buf)
अणु
	स_नकल(buf, cp->pe_data, cp->pe_data_len);
	वापस cp->pe_data_len;
पूर्ण

अटल काष्ठा ip_vs_conn *
ip_vs_sip_conn_out(काष्ठा ip_vs_service *svc,
		   काष्ठा ip_vs_dest *dest,
		   काष्ठा sk_buff *skb,
		   स्थिर काष्ठा ip_vs_iphdr *iph,
		   __be16 dport,
		   __be16 cport)
अणु
	अगर (likely(iph->protocol == IPPROTO_UDP))
		वापस ip_vs_new_conn_out(svc, dest, skb, iph, dport, cport);
	/* currently no need to handle other than UDP */
	वापस शून्य;
पूर्ण

अटल काष्ठा ip_vs_pe ip_vs_sip_pe =
अणु
	.name =			"sip",
	.refcnt =		ATOMIC_INIT(0),
	.module =		THIS_MODULE,
	.n_list =		LIST_HEAD_INIT(ip_vs_sip_pe.n_list),
	.fill_param =		ip_vs_sip_fill_param,
	.ct_match =		ip_vs_sip_ct_match,
	.hashkey_raw =		ip_vs_sip_hashkey_raw,
	.show_pe_data =		ip_vs_sip_show_pe_data,
	.conn_out =		ip_vs_sip_conn_out,
पूर्ण;

अटल पूर्णांक __init ip_vs_sip_init(व्योम)
अणु
	वापस रेजिस्टर_ip_vs_pe(&ip_vs_sip_pe);
पूर्ण

अटल व्योम __निकास ip_vs_sip_cleanup(व्योम)
अणु
	unरेजिस्टर_ip_vs_pe(&ip_vs_sip_pe);
	synchronize_rcu();
पूर्ण

module_init(ip_vs_sip_init);
module_निकास(ip_vs_sip_cleanup);
MODULE_LICENSE("GPL");
