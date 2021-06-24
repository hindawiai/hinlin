<शैली गुरु>
/*
 * Copyright (c) 2014, Ericsson AB
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश "core.h"
#समावेश "bearer.h"
#समावेश "link.h"
#समावेश "name_table.h"
#समावेश "socket.h"
#समावेश "node.h"
#समावेश "net.h"
#समावेश <net/genetlink.h>
#समावेश <linux/tipc_config.h>

/* The legacy API had an artअगरicial message length limit called
 * ULTRA_STRING_MAX_LEN.
 */
#घोषणा ULTRA_STRING_MAX_LEN 32768

#घोषणा TIPC_SKB_MAX TLV_SPACE(ULTRA_STRING_MAX_LEN)

#घोषणा REPLY_TRUNCATED "<truncated>\n"

काष्ठा tipc_nl_compat_msg अणु
	u16 cmd;
	पूर्णांक rep_type;
	पूर्णांक rep_size;
	पूर्णांक req_type;
	पूर्णांक req_size;
	काष्ठा net *net;
	काष्ठा sk_buff *rep;
	काष्ठा tlv_desc *req;
	काष्ठा sock *dst_sk;
पूर्ण;

काष्ठा tipc_nl_compat_cmd_dump अणु
	पूर्णांक (*header)(काष्ठा tipc_nl_compat_msg *);
	पूर्णांक (*dumpit)(काष्ठा sk_buff *, काष्ठा netlink_callback *);
	पूर्णांक (*क्रमmat)(काष्ठा tipc_nl_compat_msg *msg, काष्ठा nlattr **attrs);
पूर्ण;

काष्ठा tipc_nl_compat_cmd_करोit अणु
	पूर्णांक (*करोit)(काष्ठा sk_buff *skb, काष्ठा genl_info *info);
	पूर्णांक (*transcode)(काष्ठा tipc_nl_compat_cmd_करोit *cmd,
			 काष्ठा sk_buff *skb, काष्ठा tipc_nl_compat_msg *msg);
पूर्ण;

अटल पूर्णांक tipc_skb_tailroom(काष्ठा sk_buff *skb)
अणु
	पूर्णांक tailroom;
	पूर्णांक limit;

	tailroom = skb_tailroom(skb);
	limit = TIPC_SKB_MAX - skb->len;

	अगर (tailroom < limit)
		वापस tailroom;

	वापस limit;
पूर्ण

अटल अंतरभूत पूर्णांक TLV_GET_DATA_LEN(काष्ठा tlv_desc *tlv)
अणु
	वापस TLV_GET_LEN(tlv) - TLV_SPACE(0);
पूर्ण

अटल पूर्णांक tipc_add_tlv(काष्ठा sk_buff *skb, u16 type, व्योम *data, u16 len)
अणु
	काष्ठा tlv_desc *tlv = (काष्ठा tlv_desc *)skb_tail_poपूर्णांकer(skb);

	अगर (tipc_skb_tailroom(skb) < TLV_SPACE(len))
		वापस -EMSGSIZE;

	skb_put(skb, TLV_SPACE(len));
	tlv->tlv_type = htons(type);
	tlv->tlv_len = htons(TLV_LENGTH(len));
	अगर (len && data)
		स_नकल(TLV_DATA(tlv), data, len);

	वापस 0;
पूर्ण

अटल व्योम tipc_tlv_init(काष्ठा sk_buff *skb, u16 type)
अणु
	काष्ठा tlv_desc *tlv = (काष्ठा tlv_desc *)skb->data;

	TLV_SET_LEN(tlv, 0);
	TLV_SET_TYPE(tlv, type);
	skb_put(skb, माप(काष्ठा tlv_desc));
पूर्ण

अटल __म_लिखो(2, 3) पूर्णांक tipc_tlv_प्र_लिखो(काष्ठा sk_buff *skb,
					   स्थिर अक्षर *fmt, ...)
अणु
	पूर्णांक n;
	u16 len;
	u32 rem;
	अक्षर *buf;
	काष्ठा tlv_desc *tlv;
	बहु_सूची args;

	rem = tipc_skb_tailroom(skb);

	tlv = (काष्ठा tlv_desc *)skb->data;
	len = TLV_GET_LEN(tlv);
	buf = TLV_DATA(tlv) + len;

	बहु_शुरू(args, fmt);
	n = vscnम_लिखो(buf, rem, fmt, args);
	बहु_पूर्ण(args);

	TLV_SET_LEN(tlv, n + len);
	skb_put(skb, n);

	वापस n;
पूर्ण

अटल काष्ठा sk_buff *tipc_tlv_alloc(पूर्णांक size)
अणु
	पूर्णांक hdr_len;
	काष्ठा sk_buff *buf;

	size = TLV_SPACE(size);
	hdr_len = nlmsg_total_size(GENL_HDRLEN + TIPC_GENL_HDRLEN);

	buf = alloc_skb(hdr_len + size, GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;

	skb_reserve(buf, hdr_len);

	वापस buf;
पूर्ण

अटल काष्ठा sk_buff *tipc_get_err_tlv(अक्षर *str)
अणु
	पूर्णांक str_len = म_माप(str) + 1;
	काष्ठा sk_buff *buf;

	buf = tipc_tlv_alloc(TLV_SPACE(str_len));
	अगर (buf)
		tipc_add_tlv(buf, TIPC_TLV_ERROR_STRING, str, str_len);

	वापस buf;
पूर्ण

अटल अंतरभूत bool string_is_valid(अक्षर *s, पूर्णांक len)
अणु
	वापस स_प्रथम(s, '\0', len) ? true : false;
पूर्ण

अटल पूर्णांक __tipc_nl_compat_dumpit(काष्ठा tipc_nl_compat_cmd_dump *cmd,
				   काष्ठा tipc_nl_compat_msg *msg,
				   काष्ठा sk_buff *arg)
अणु
	काष्ठा genl_dumpit_info info;
	पूर्णांक len = 0;
	पूर्णांक err;
	काष्ठा sk_buff *buf;
	काष्ठा nlmsghdr *nlmsg;
	काष्ठा netlink_callback cb;
	काष्ठा nlattr **attrbuf;

	स_रखो(&cb, 0, माप(cb));
	cb.nlh = (काष्ठा nlmsghdr *)arg->data;
	cb.skb = arg;
	cb.data = &info;

	buf = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	buf->sk = msg->dst_sk;
	अगर (__tipc_dump_start(&cb, msg->net)) अणु
		kमुक्त_skb(buf);
		वापस -ENOMEM;
	पूर्ण

	attrbuf = kसुस्मृति(tipc_genl_family.maxattr + 1,
			  माप(काष्ठा nlattr *), GFP_KERNEL);
	अगर (!attrbuf) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	info.attrs = attrbuf;

	अगर (nlmsg_len(cb.nlh) > 0) अणु
		err = nlmsg_parse_deprecated(cb.nlh, GENL_HDRLEN, attrbuf,
					     tipc_genl_family.maxattr,
					     tipc_genl_family.policy, शून्य);
		अगर (err)
			जाओ err_out;
	पूर्ण
	करो अणु
		पूर्णांक rem;

		len = (*cmd->dumpit)(buf, &cb);

		nlmsg_क्रम_each_msg(nlmsg, nlmsg_hdr(buf), len, rem) अणु
			err = nlmsg_parse_deprecated(nlmsg, GENL_HDRLEN,
						     attrbuf,
						     tipc_genl_family.maxattr,
						     tipc_genl_family.policy,
						     शून्य);
			अगर (err)
				जाओ err_out;

			err = (*cmd->क्रमmat)(msg, attrbuf);
			अगर (err)
				जाओ err_out;

			अगर (tipc_skb_tailroom(msg->rep) <= 1) अणु
				err = -EMSGSIZE;
				जाओ err_out;
			पूर्ण
		पूर्ण

		skb_reset_tail_poपूर्णांकer(buf);
		buf->len = 0;

	पूर्ण जबतक (len);

	err = 0;

err_out:
	kमुक्त(attrbuf);
	tipc_dump_करोne(&cb);
	kमुक्त_skb(buf);

	अगर (err == -EMSGSIZE) अणु
		/* The legacy API only considered messages filling
		 * "ULTRA_STRING_MAX_LEN" to be truncated.
		 */
		अगर ((TIPC_SKB_MAX - msg->rep->len) <= 1) अणु
			अक्षर *tail = skb_tail_poपूर्णांकer(msg->rep);

			अगर (*tail != '\0')
				प्र_लिखो(tail - माप(REPLY_TRUNCATED) - 1,
					REPLY_TRUNCATED);
		पूर्ण

		वापस 0;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक tipc_nl_compat_dumpit(काष्ठा tipc_nl_compat_cmd_dump *cmd,
				 काष्ठा tipc_nl_compat_msg *msg)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा sk_buff *arg;
	पूर्णांक err;

	अगर (msg->req_type && (!msg->req_size ||
			      !TLV_CHECK_TYPE(msg->req, msg->req_type)))
		वापस -EINVAL;

	msg->rep = tipc_tlv_alloc(msg->rep_size);
	अगर (!msg->rep)
		वापस -ENOMEM;

	अगर (msg->rep_type)
		tipc_tlv_init(msg->rep, msg->rep_type);

	अगर (cmd->header) अणु
		err = (*cmd->header)(msg);
		अगर (err) अणु
			kमुक्त_skb(msg->rep);
			msg->rep = शून्य;
			वापस err;
		पूर्ण
	पूर्ण

	arg = nlmsg_new(0, GFP_KERNEL);
	अगर (!arg) अणु
		kमुक्त_skb(msg->rep);
		msg->rep = शून्य;
		वापस -ENOMEM;
	पूर्ण

	nlh = nlmsg_put(arg, 0, 0, tipc_genl_family.id, 0, NLM_F_MULTI);
	अगर (!nlh) अणु
		kमुक्त_skb(arg);
		kमुक्त_skb(msg->rep);
		msg->rep = शून्य;
		वापस -EMSGSIZE;
	पूर्ण
	nlmsg_end(arg, nlh);

	err = __tipc_nl_compat_dumpit(cmd, msg, arg);
	अगर (err) अणु
		kमुक्त_skb(msg->rep);
		msg->rep = शून्य;
	पूर्ण
	kमुक्त_skb(arg);

	वापस err;
पूर्ण

अटल पूर्णांक __tipc_nl_compat_करोit(काष्ठा tipc_nl_compat_cmd_करोit *cmd,
				 काष्ठा tipc_nl_compat_msg *msg)
अणु
	पूर्णांक err;
	काष्ठा sk_buff *करोit_buf;
	काष्ठा sk_buff *trans_buf;
	काष्ठा nlattr **attrbuf;
	काष्ठा genl_info info;

	trans_buf = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!trans_buf)
		वापस -ENOMEM;

	attrbuf = kदो_स्मृति_array(tipc_genl_family.maxattr + 1,
				माप(काष्ठा nlattr *),
				GFP_KERNEL);
	अगर (!attrbuf) अणु
		err = -ENOMEM;
		जाओ trans_out;
	पूर्ण

	करोit_buf = alloc_skb(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!करोit_buf) अणु
		err = -ENOMEM;
		जाओ attrbuf_out;
	पूर्ण

	स_रखो(&info, 0, माप(info));
	info.attrs = attrbuf;

	rtnl_lock();
	err = (*cmd->transcode)(cmd, trans_buf, msg);
	अगर (err)
		जाओ करोit_out;

	err = nla_parse_deprecated(attrbuf, tipc_genl_family.maxattr,
				   (स्थिर काष्ठा nlattr *)trans_buf->data,
				   trans_buf->len, शून्य, शून्य);
	अगर (err)
		जाओ करोit_out;

	करोit_buf->sk = msg->dst_sk;

	err = (*cmd->करोit)(करोit_buf, &info);
करोit_out:
	rtnl_unlock();

	kमुक्त_skb(करोit_buf);
attrbuf_out:
	kमुक्त(attrbuf);
trans_out:
	kमुक्त_skb(trans_buf);

	वापस err;
पूर्ण

अटल पूर्णांक tipc_nl_compat_करोit(काष्ठा tipc_nl_compat_cmd_करोit *cmd,
			       काष्ठा tipc_nl_compat_msg *msg)
अणु
	पूर्णांक err;

	अगर (msg->req_type && (!msg->req_size ||
			      !TLV_CHECK_TYPE(msg->req, msg->req_type)))
		वापस -EINVAL;

	err = __tipc_nl_compat_करोit(cmd, msg);
	अगर (err)
		वापस err;

	/* The legacy API considered an empty message a success message */
	msg->rep = tipc_tlv_alloc(0);
	अगर (!msg->rep)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_compat_bearer_dump(काष्ठा tipc_nl_compat_msg *msg,
				      काष्ठा nlattr **attrs)
अणु
	काष्ठा nlattr *bearer[TIPC_NLA_BEARER_MAX + 1];
	पूर्णांक err;

	अगर (!attrs[TIPC_NLA_BEARER])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(bearer, TIPC_NLA_BEARER_MAX,
					  attrs[TIPC_NLA_BEARER], शून्य, शून्य);
	अगर (err)
		वापस err;

	वापस tipc_add_tlv(msg->rep, TIPC_TLV_BEARER_NAME,
			    nla_data(bearer[TIPC_NLA_BEARER_NAME]),
			    nla_len(bearer[TIPC_NLA_BEARER_NAME]));
पूर्ण

अटल पूर्णांक tipc_nl_compat_bearer_enable(काष्ठा tipc_nl_compat_cmd_करोit *cmd,
					काष्ठा sk_buff *skb,
					काष्ठा tipc_nl_compat_msg *msg)
अणु
	काष्ठा nlattr *prop;
	काष्ठा nlattr *bearer;
	काष्ठा tipc_bearer_config *b;
	पूर्णांक len;

	b = (काष्ठा tipc_bearer_config *)TLV_DATA(msg->req);

	bearer = nla_nest_start_noflag(skb, TIPC_NLA_BEARER);
	अगर (!bearer)
		वापस -EMSGSIZE;

	len = TLV_GET_DATA_LEN(msg->req);
	len -= दुरत्व(काष्ठा tipc_bearer_config, name);
	अगर (len <= 0)
		वापस -EINVAL;

	len = min_t(पूर्णांक, len, TIPC_MAX_BEARER_NAME);
	अगर (!string_is_valid(b->name, len))
		वापस -EINVAL;

	अगर (nla_put_string(skb, TIPC_NLA_BEARER_NAME, b->name))
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, TIPC_NLA_BEARER_DOMAIN, ntohl(b->disc_करोमुख्य)))
		वापस -EMSGSIZE;

	अगर (ntohl(b->priority) <= TIPC_MAX_LINK_PRI) अणु
		prop = nla_nest_start_noflag(skb, TIPC_NLA_BEARER_PROP);
		अगर (!prop)
			वापस -EMSGSIZE;
		अगर (nla_put_u32(skb, TIPC_NLA_PROP_PRIO, ntohl(b->priority)))
			वापस -EMSGSIZE;
		nla_nest_end(skb, prop);
	पूर्ण
	nla_nest_end(skb, bearer);

	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_compat_bearer_disable(काष्ठा tipc_nl_compat_cmd_करोit *cmd,
					 काष्ठा sk_buff *skb,
					 काष्ठा tipc_nl_compat_msg *msg)
अणु
	अक्षर *name;
	काष्ठा nlattr *bearer;
	पूर्णांक len;

	name = (अक्षर *)TLV_DATA(msg->req);

	bearer = nla_nest_start_noflag(skb, TIPC_NLA_BEARER);
	अगर (!bearer)
		वापस -EMSGSIZE;

	len = TLV_GET_DATA_LEN(msg->req);
	अगर (len <= 0)
		वापस -EINVAL;

	len = min_t(पूर्णांक, len, TIPC_MAX_BEARER_NAME);
	अगर (!string_is_valid(name, len))
		वापस -EINVAL;

	अगर (nla_put_string(skb, TIPC_NLA_BEARER_NAME, name))
		वापस -EMSGSIZE;

	nla_nest_end(skb, bearer);

	वापस 0;
पूर्ण

अटल अंतरभूत u32 perc(u32 count, u32 total)
अणु
	वापस (count * 100 + (total / 2)) / total;
पूर्ण

अटल व्योम __fill_bc_link_stat(काष्ठा tipc_nl_compat_msg *msg,
				काष्ठा nlattr *prop[], काष्ठा nlattr *stats[])
अणु
	tipc_tlv_प्र_लिखो(msg->rep, "  Window:%u packets\n",
			 nla_get_u32(prop[TIPC_NLA_PROP_WIN]));

	tipc_tlv_प्र_लिखो(msg->rep,
			 "  RX packets:%u fragments:%u/%u bundles:%u/%u\n",
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_INFO]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_FRAGMENTS]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_FRAGMENTED]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_BUNDLES]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_BUNDLED]));

	tipc_tlv_प्र_लिखो(msg->rep,
			 "  TX packets:%u fragments:%u/%u bundles:%u/%u\n",
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_INFO]),
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_FRAGMENTS]),
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_FRAGMENTED]),
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_BUNDLES]),
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_BUNDLED]));

	tipc_tlv_प्र_लिखो(msg->rep, "  RX naks:%u defs:%u dups:%u\n",
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_NACKS]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_DEFERRED]),
			 nla_get_u32(stats[TIPC_NLA_STATS_DUPLICATES]));

	tipc_tlv_प्र_लिखो(msg->rep, "  TX naks:%u acks:%u dups:%u\n",
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_NACKS]),
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_ACKS]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RETRANSMITTED]));

	tipc_tlv_प्र_लिखो(msg->rep,
			 "  Congestion link:%u  Send queue max:%u avg:%u",
			 nla_get_u32(stats[TIPC_NLA_STATS_LINK_CONGS]),
			 nla_get_u32(stats[TIPC_NLA_STATS_MAX_QUEUE]),
			 nla_get_u32(stats[TIPC_NLA_STATS_AVG_QUEUE]));
पूर्ण

अटल पूर्णांक tipc_nl_compat_link_stat_dump(काष्ठा tipc_nl_compat_msg *msg,
					 काष्ठा nlattr **attrs)
अणु
	अक्षर *name;
	काष्ठा nlattr *link[TIPC_NLA_LINK_MAX + 1];
	काष्ठा nlattr *prop[TIPC_NLA_PROP_MAX + 1];
	काष्ठा nlattr *stats[TIPC_NLA_STATS_MAX + 1];
	पूर्णांक err;
	पूर्णांक len;

	अगर (!attrs[TIPC_NLA_LINK])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(link, TIPC_NLA_LINK_MAX,
					  attrs[TIPC_NLA_LINK], शून्य, शून्य);
	अगर (err)
		वापस err;

	अगर (!link[TIPC_NLA_LINK_PROP])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(prop, TIPC_NLA_PROP_MAX,
					  link[TIPC_NLA_LINK_PROP], शून्य,
					  शून्य);
	अगर (err)
		वापस err;

	अगर (!link[TIPC_NLA_LINK_STATS])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(stats, TIPC_NLA_STATS_MAX,
					  link[TIPC_NLA_LINK_STATS], शून्य,
					  शून्य);
	अगर (err)
		वापस err;

	name = (अक्षर *)TLV_DATA(msg->req);

	len = TLV_GET_DATA_LEN(msg->req);
	अगर (len <= 0)
		वापस -EINVAL;

	len = min_t(पूर्णांक, len, TIPC_MAX_LINK_NAME);
	अगर (!string_is_valid(name, len))
		वापस -EINVAL;

	अगर (म_भेद(name, nla_data(link[TIPC_NLA_LINK_NAME])) != 0)
		वापस 0;

	tipc_tlv_प्र_लिखो(msg->rep, "\nLink <%s>\n",
			 (अक्षर *)nla_data(link[TIPC_NLA_LINK_NAME]));

	अगर (link[TIPC_NLA_LINK_BROADCAST]) अणु
		__fill_bc_link_stat(msg, prop, stats);
		वापस 0;
	पूर्ण

	अगर (link[TIPC_NLA_LINK_ACTIVE])
		tipc_tlv_प्र_लिखो(msg->rep, "  ACTIVE");
	अन्यथा अगर (link[TIPC_NLA_LINK_UP])
		tipc_tlv_प्र_लिखो(msg->rep, "  STANDBY");
	अन्यथा
		tipc_tlv_प्र_लिखो(msg->rep, "  DEFUNCT");

	tipc_tlv_प्र_लिखो(msg->rep, "  MTU:%u  Priority:%u",
			 nla_get_u32(link[TIPC_NLA_LINK_MTU]),
			 nla_get_u32(prop[TIPC_NLA_PROP_PRIO]));

	tipc_tlv_प्र_लिखो(msg->rep, "  Tolerance:%u ms  Window:%u packets\n",
			 nla_get_u32(prop[TIPC_NLA_PROP_TOL]),
			 nla_get_u32(prop[TIPC_NLA_PROP_WIN]));

	tipc_tlv_प्र_लिखो(msg->rep,
			 "  RX packets:%u fragments:%u/%u bundles:%u/%u\n",
			 nla_get_u32(link[TIPC_NLA_LINK_RX]) -
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_INFO]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_FRAGMENTS]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_FRAGMENTED]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_BUNDLES]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_BUNDLED]));

	tipc_tlv_प्र_लिखो(msg->rep,
			 "  TX packets:%u fragments:%u/%u bundles:%u/%u\n",
			 nla_get_u32(link[TIPC_NLA_LINK_TX]) -
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_INFO]),
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_FRAGMENTS]),
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_FRAGMENTED]),
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_BUNDLES]),
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_BUNDLED]));

	tipc_tlv_प्र_लिखो(msg->rep,
			 "  TX profile sample:%u packets  average:%u octets\n",
			 nla_get_u32(stats[TIPC_NLA_STATS_MSG_LEN_CNT]),
			 nla_get_u32(stats[TIPC_NLA_STATS_MSG_LEN_TOT]) /
			 nla_get_u32(stats[TIPC_NLA_STATS_MSG_PROF_TOT]));

	tipc_tlv_प्र_लिखो(msg->rep,
			 "  0-64:%u%% -256:%u%% -1024:%u%% -4096:%u%% ",
			 perc(nla_get_u32(stats[TIPC_NLA_STATS_MSG_LEN_P0]),
			      nla_get_u32(stats[TIPC_NLA_STATS_MSG_PROF_TOT])),
			 perc(nla_get_u32(stats[TIPC_NLA_STATS_MSG_LEN_P1]),
			      nla_get_u32(stats[TIPC_NLA_STATS_MSG_PROF_TOT])),
			 perc(nla_get_u32(stats[TIPC_NLA_STATS_MSG_LEN_P2]),
			      nla_get_u32(stats[TIPC_NLA_STATS_MSG_PROF_TOT])),
			 perc(nla_get_u32(stats[TIPC_NLA_STATS_MSG_LEN_P3]),
			      nla_get_u32(stats[TIPC_NLA_STATS_MSG_PROF_TOT])));

	tipc_tlv_प्र_लिखो(msg->rep, "-16384:%u%% -32768:%u%% -66000:%u%%\n",
			 perc(nla_get_u32(stats[TIPC_NLA_STATS_MSG_LEN_P4]),
			      nla_get_u32(stats[TIPC_NLA_STATS_MSG_PROF_TOT])),
			 perc(nla_get_u32(stats[TIPC_NLA_STATS_MSG_LEN_P5]),
			      nla_get_u32(stats[TIPC_NLA_STATS_MSG_PROF_TOT])),
			 perc(nla_get_u32(stats[TIPC_NLA_STATS_MSG_LEN_P6]),
			      nla_get_u32(stats[TIPC_NLA_STATS_MSG_PROF_TOT])));

	tipc_tlv_प्र_लिखो(msg->rep,
			 "  RX states:%u probes:%u naks:%u defs:%u dups:%u\n",
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_STATES]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_PROBES]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_NACKS]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RX_DEFERRED]),
			 nla_get_u32(stats[TIPC_NLA_STATS_DUPLICATES]));

	tipc_tlv_प्र_लिखो(msg->rep,
			 "  TX states:%u probes:%u naks:%u acks:%u dups:%u\n",
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_STATES]),
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_PROBES]),
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_NACKS]),
			 nla_get_u32(stats[TIPC_NLA_STATS_TX_ACKS]),
			 nla_get_u32(stats[TIPC_NLA_STATS_RETRANSMITTED]));

	tipc_tlv_प्र_लिखो(msg->rep,
			 "  Congestion link:%u  Send queue max:%u avg:%u",
			 nla_get_u32(stats[TIPC_NLA_STATS_LINK_CONGS]),
			 nla_get_u32(stats[TIPC_NLA_STATS_MAX_QUEUE]),
			 nla_get_u32(stats[TIPC_NLA_STATS_AVG_QUEUE]));

	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_compat_link_dump(काष्ठा tipc_nl_compat_msg *msg,
				    काष्ठा nlattr **attrs)
अणु
	काष्ठा nlattr *link[TIPC_NLA_LINK_MAX + 1];
	काष्ठा tipc_link_info link_info;
	पूर्णांक err;

	अगर (!attrs[TIPC_NLA_LINK])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(link, TIPC_NLA_LINK_MAX,
					  attrs[TIPC_NLA_LINK], शून्य, शून्य);
	अगर (err)
		वापस err;

	link_info.dest = htonl(nla_get_flag(link[TIPC_NLA_LINK_DEST]));
	link_info.up = htonl(nla_get_flag(link[TIPC_NLA_LINK_UP]));
	nla_strscpy(link_info.str, link[TIPC_NLA_LINK_NAME],
		    TIPC_MAX_LINK_NAME);

	वापस tipc_add_tlv(msg->rep, TIPC_TLV_LINK_INFO,
			    &link_info, माप(link_info));
पूर्ण

अटल पूर्णांक __tipc_add_link_prop(काष्ठा sk_buff *skb,
				काष्ठा tipc_nl_compat_msg *msg,
				काष्ठा tipc_link_config *lc)
अणु
	चयन (msg->cmd) अणु
	हाल TIPC_CMD_SET_LINK_PRI:
		वापस nla_put_u32(skb, TIPC_NLA_PROP_PRIO, ntohl(lc->value));
	हाल TIPC_CMD_SET_LINK_TOL:
		वापस nla_put_u32(skb, TIPC_NLA_PROP_TOL, ntohl(lc->value));
	हाल TIPC_CMD_SET_LINK_WINDOW:
		वापस nla_put_u32(skb, TIPC_NLA_PROP_WIN, ntohl(lc->value));
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tipc_nl_compat_media_set(काष्ठा sk_buff *skb,
				    काष्ठा tipc_nl_compat_msg *msg)
अणु
	काष्ठा nlattr *prop;
	काष्ठा nlattr *media;
	काष्ठा tipc_link_config *lc;

	lc = (काष्ठा tipc_link_config *)TLV_DATA(msg->req);

	media = nla_nest_start_noflag(skb, TIPC_NLA_MEDIA);
	अगर (!media)
		वापस -EMSGSIZE;

	अगर (nla_put_string(skb, TIPC_NLA_MEDIA_NAME, lc->name))
		वापस -EMSGSIZE;

	prop = nla_nest_start_noflag(skb, TIPC_NLA_MEDIA_PROP);
	अगर (!prop)
		वापस -EMSGSIZE;

	__tipc_add_link_prop(skb, msg, lc);
	nla_nest_end(skb, prop);
	nla_nest_end(skb, media);

	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_compat_bearer_set(काष्ठा sk_buff *skb,
				     काष्ठा tipc_nl_compat_msg *msg)
अणु
	काष्ठा nlattr *prop;
	काष्ठा nlattr *bearer;
	काष्ठा tipc_link_config *lc;

	lc = (काष्ठा tipc_link_config *)TLV_DATA(msg->req);

	bearer = nla_nest_start_noflag(skb, TIPC_NLA_BEARER);
	अगर (!bearer)
		वापस -EMSGSIZE;

	अगर (nla_put_string(skb, TIPC_NLA_BEARER_NAME, lc->name))
		वापस -EMSGSIZE;

	prop = nla_nest_start_noflag(skb, TIPC_NLA_BEARER_PROP);
	अगर (!prop)
		वापस -EMSGSIZE;

	__tipc_add_link_prop(skb, msg, lc);
	nla_nest_end(skb, prop);
	nla_nest_end(skb, bearer);

	वापस 0;
पूर्ण

अटल पूर्णांक __tipc_nl_compat_link_set(काष्ठा sk_buff *skb,
				     काष्ठा tipc_nl_compat_msg *msg)
अणु
	काष्ठा nlattr *prop;
	काष्ठा nlattr *link;
	काष्ठा tipc_link_config *lc;

	lc = (काष्ठा tipc_link_config *)TLV_DATA(msg->req);

	link = nla_nest_start_noflag(skb, TIPC_NLA_LINK);
	अगर (!link)
		वापस -EMSGSIZE;

	अगर (nla_put_string(skb, TIPC_NLA_LINK_NAME, lc->name))
		वापस -EMSGSIZE;

	prop = nla_nest_start_noflag(skb, TIPC_NLA_LINK_PROP);
	अगर (!prop)
		वापस -EMSGSIZE;

	__tipc_add_link_prop(skb, msg, lc);
	nla_nest_end(skb, prop);
	nla_nest_end(skb, link);

	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_compat_link_set(काष्ठा tipc_nl_compat_cmd_करोit *cmd,
				   काष्ठा sk_buff *skb,
				   काष्ठा tipc_nl_compat_msg *msg)
अणु
	काष्ठा tipc_link_config *lc;
	काष्ठा tipc_bearer *bearer;
	काष्ठा tipc_media *media;
	पूर्णांक len;

	lc = (काष्ठा tipc_link_config *)TLV_DATA(msg->req);

	len = TLV_GET_DATA_LEN(msg->req);
	len -= दुरत्व(काष्ठा tipc_link_config, name);
	अगर (len <= 0)
		वापस -EINVAL;

	len = min_t(पूर्णांक, len, TIPC_MAX_LINK_NAME);
	अगर (!string_is_valid(lc->name, len))
		वापस -EINVAL;

	media = tipc_media_find(lc->name);
	अगर (media) अणु
		cmd->करोit = &__tipc_nl_media_set;
		वापस tipc_nl_compat_media_set(skb, msg);
	पूर्ण

	bearer = tipc_bearer_find(msg->net, lc->name);
	अगर (bearer) अणु
		cmd->करोit = &__tipc_nl_bearer_set;
		वापस tipc_nl_compat_bearer_set(skb, msg);
	पूर्ण

	वापस __tipc_nl_compat_link_set(skb, msg);
पूर्ण

अटल पूर्णांक tipc_nl_compat_link_reset_stats(काष्ठा tipc_nl_compat_cmd_करोit *cmd,
					   काष्ठा sk_buff *skb,
					   काष्ठा tipc_nl_compat_msg *msg)
अणु
	अक्षर *name;
	काष्ठा nlattr *link;
	पूर्णांक len;

	name = (अक्षर *)TLV_DATA(msg->req);

	link = nla_nest_start_noflag(skb, TIPC_NLA_LINK);
	अगर (!link)
		वापस -EMSGSIZE;

	len = TLV_GET_DATA_LEN(msg->req);
	अगर (len <= 0)
		वापस -EINVAL;

	len = min_t(पूर्णांक, len, TIPC_MAX_LINK_NAME);
	अगर (!string_is_valid(name, len))
		वापस -EINVAL;

	अगर (nla_put_string(skb, TIPC_NLA_LINK_NAME, name))
		वापस -EMSGSIZE;

	nla_nest_end(skb, link);

	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_compat_name_table_dump_header(काष्ठा tipc_nl_compat_msg *msg)
अणु
	पूर्णांक i;
	u32 depth;
	काष्ठा tipc_name_table_query *ntq;
	अटल स्थिर अक्षर * स्थिर header[] = अणु
		"Type       ",
		"Lower      Upper      ",
		"Port Identity              ",
		"Publication Scope"
	पूर्ण;

	ntq = (काष्ठा tipc_name_table_query *)TLV_DATA(msg->req);
	अगर (TLV_GET_DATA_LEN(msg->req) < माप(काष्ठा tipc_name_table_query))
		वापस -EINVAL;

	depth = ntohl(ntq->depth);

	अगर (depth > 4)
		depth = 4;
	क्रम (i = 0; i < depth; i++)
		tipc_tlv_प्र_लिखो(msg->rep, header[i]);
	tipc_tlv_प्र_लिखो(msg->rep, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_compat_name_table_dump(काष्ठा tipc_nl_compat_msg *msg,
					  काष्ठा nlattr **attrs)
अणु
	अक्षर port_str[27];
	काष्ठा tipc_name_table_query *ntq;
	काष्ठा nlattr *nt[TIPC_NLA_NAME_TABLE_MAX + 1];
	काष्ठा nlattr *publ[TIPC_NLA_PUBL_MAX + 1];
	u32 node, depth, type, lowbound, upbound;
	अटल स्थिर अक्षर * स्थिर scope_str[] = अणु"", " zone", " cluster",
						 " node"पूर्ण;
	पूर्णांक err;

	अगर (!attrs[TIPC_NLA_NAME_TABLE])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(nt, TIPC_NLA_NAME_TABLE_MAX,
					  attrs[TIPC_NLA_NAME_TABLE], शून्य,
					  शून्य);
	अगर (err)
		वापस err;

	अगर (!nt[TIPC_NLA_NAME_TABLE_PUBL])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(publ, TIPC_NLA_PUBL_MAX,
					  nt[TIPC_NLA_NAME_TABLE_PUBL], शून्य,
					  शून्य);
	अगर (err)
		वापस err;

	ntq = (काष्ठा tipc_name_table_query *)TLV_DATA(msg->req);

	depth = ntohl(ntq->depth);
	type = ntohl(ntq->type);
	lowbound = ntohl(ntq->lowbound);
	upbound = ntohl(ntq->upbound);

	अगर (!(depth & TIPC_NTQ_ALLTYPES) &&
	    (type != nla_get_u32(publ[TIPC_NLA_PUBL_TYPE])))
		वापस 0;
	अगर (lowbound && (lowbound > nla_get_u32(publ[TIPC_NLA_PUBL_UPPER])))
		वापस 0;
	अगर (upbound && (upbound < nla_get_u32(publ[TIPC_NLA_PUBL_LOWER])))
		वापस 0;

	tipc_tlv_प्र_लिखो(msg->rep, "%-10u ",
			 nla_get_u32(publ[TIPC_NLA_PUBL_TYPE]));

	अगर (depth == 1)
		जाओ out;

	tipc_tlv_प्र_लिखो(msg->rep, "%-10u %-10u ",
			 nla_get_u32(publ[TIPC_NLA_PUBL_LOWER]),
			 nla_get_u32(publ[TIPC_NLA_PUBL_UPPER]));

	अगर (depth == 2)
		जाओ out;

	node = nla_get_u32(publ[TIPC_NLA_PUBL_NODE]);
	प्र_लिखो(port_str, "<%u.%u.%u:%u>", tipc_zone(node), tipc_cluster(node),
		tipc_node(node), nla_get_u32(publ[TIPC_NLA_PUBL_REF]));
	tipc_tlv_प्र_लिखो(msg->rep, "%-26s ", port_str);

	अगर (depth == 3)
		जाओ out;

	tipc_tlv_प्र_लिखो(msg->rep, "%-10u %s",
			 nla_get_u32(publ[TIPC_NLA_PUBL_KEY]),
			 scope_str[nla_get_u32(publ[TIPC_NLA_PUBL_SCOPE])]);
out:
	tipc_tlv_प्र_लिखो(msg->rep, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक __tipc_nl_compat_publ_dump(काष्ठा tipc_nl_compat_msg *msg,
				      काष्ठा nlattr **attrs)
अणु
	u32 type, lower, upper;
	काष्ठा nlattr *publ[TIPC_NLA_PUBL_MAX + 1];
	पूर्णांक err;

	अगर (!attrs[TIPC_NLA_PUBL])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(publ, TIPC_NLA_PUBL_MAX,
					  attrs[TIPC_NLA_PUBL], शून्य, शून्य);
	अगर (err)
		वापस err;

	type = nla_get_u32(publ[TIPC_NLA_PUBL_TYPE]);
	lower = nla_get_u32(publ[TIPC_NLA_PUBL_LOWER]);
	upper = nla_get_u32(publ[TIPC_NLA_PUBL_UPPER]);

	अगर (lower == upper)
		tipc_tlv_प्र_लिखो(msg->rep, " {%u,%u}", type, lower);
	अन्यथा
		tipc_tlv_प्र_लिखो(msg->rep, " {%u,%u,%u}", type, lower, upper);

	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_compat_publ_dump(काष्ठा tipc_nl_compat_msg *msg, u32 sock)
अणु
	पूर्णांक err;
	व्योम *hdr;
	काष्ठा nlattr *nest;
	काष्ठा sk_buff *args;
	काष्ठा tipc_nl_compat_cmd_dump dump;

	args = nlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	अगर (!args)
		वापस -ENOMEM;

	hdr = genlmsg_put(args, 0, 0, &tipc_genl_family, NLM_F_MULTI,
			  TIPC_NL_PUBL_GET);
	अगर (!hdr) अणु
		kमुक्त_skb(args);
		वापस -EMSGSIZE;
	पूर्ण

	nest = nla_nest_start_noflag(args, TIPC_NLA_SOCK);
	अगर (!nest) अणु
		kमुक्त_skb(args);
		वापस -EMSGSIZE;
	पूर्ण

	अगर (nla_put_u32(args, TIPC_NLA_SOCK_REF, sock)) अणु
		kमुक्त_skb(args);
		वापस -EMSGSIZE;
	पूर्ण

	nla_nest_end(args, nest);
	genlmsg_end(args, hdr);

	dump.dumpit = tipc_nl_publ_dump;
	dump.क्रमmat = __tipc_nl_compat_publ_dump;

	err = __tipc_nl_compat_dumpit(&dump, msg, args);

	kमुक्त_skb(args);

	वापस err;
पूर्ण

अटल पूर्णांक tipc_nl_compat_sk_dump(काष्ठा tipc_nl_compat_msg *msg,
				  काष्ठा nlattr **attrs)
अणु
	पूर्णांक err;
	u32 sock_ref;
	काष्ठा nlattr *sock[TIPC_NLA_SOCK_MAX + 1];

	अगर (!attrs[TIPC_NLA_SOCK])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(sock, TIPC_NLA_SOCK_MAX,
					  attrs[TIPC_NLA_SOCK], शून्य, शून्य);
	अगर (err)
		वापस err;

	sock_ref = nla_get_u32(sock[TIPC_NLA_SOCK_REF]);
	tipc_tlv_प्र_लिखो(msg->rep, "%u:", sock_ref);

	अगर (sock[TIPC_NLA_SOCK_CON]) अणु
		u32 node;
		काष्ठा nlattr *con[TIPC_NLA_CON_MAX + 1];

		err = nla_parse_nested_deprecated(con, TIPC_NLA_CON_MAX,
						  sock[TIPC_NLA_SOCK_CON],
						  शून्य, शून्य);

		अगर (err)
			वापस err;

		node = nla_get_u32(con[TIPC_NLA_CON_NODE]);
		tipc_tlv_प्र_लिखो(msg->rep, "  connected to <%u.%u.%u:%u>",
				 tipc_zone(node),
				 tipc_cluster(node),
				 tipc_node(node),
				 nla_get_u32(con[TIPC_NLA_CON_SOCK]));

		अगर (con[TIPC_NLA_CON_FLAG])
			tipc_tlv_प्र_लिखो(msg->rep, " via {%u,%u}\n",
					 nla_get_u32(con[TIPC_NLA_CON_TYPE]),
					 nla_get_u32(con[TIPC_NLA_CON_INST]));
		अन्यथा
			tipc_tlv_प्र_लिखो(msg->rep, "\n");
	पूर्ण अन्यथा अगर (sock[TIPC_NLA_SOCK_HAS_PUBL]) अणु
		tipc_tlv_प्र_लिखो(msg->rep, " bound to");

		err = tipc_nl_compat_publ_dump(msg, sock_ref);
		अगर (err)
			वापस err;
	पूर्ण
	tipc_tlv_प्र_लिखो(msg->rep, "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_compat_media_dump(काष्ठा tipc_nl_compat_msg *msg,
				     काष्ठा nlattr **attrs)
अणु
	काष्ठा nlattr *media[TIPC_NLA_MEDIA_MAX + 1];
	पूर्णांक err;

	अगर (!attrs[TIPC_NLA_MEDIA])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(media, TIPC_NLA_MEDIA_MAX,
					  attrs[TIPC_NLA_MEDIA], शून्य, शून्य);
	अगर (err)
		वापस err;

	वापस tipc_add_tlv(msg->rep, TIPC_TLV_MEDIA_NAME,
			    nla_data(media[TIPC_NLA_MEDIA_NAME]),
			    nla_len(media[TIPC_NLA_MEDIA_NAME]));
पूर्ण

अटल पूर्णांक tipc_nl_compat_node_dump(काष्ठा tipc_nl_compat_msg *msg,
				    काष्ठा nlattr **attrs)
अणु
	काष्ठा tipc_node_info node_info;
	काष्ठा nlattr *node[TIPC_NLA_NODE_MAX + 1];
	पूर्णांक err;

	अगर (!attrs[TIPC_NLA_NODE])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(node, TIPC_NLA_NODE_MAX,
					  attrs[TIPC_NLA_NODE], शून्य, शून्य);
	अगर (err)
		वापस err;

	node_info.addr = htonl(nla_get_u32(node[TIPC_NLA_NODE_ADDR]));
	node_info.up = htonl(nla_get_flag(node[TIPC_NLA_NODE_UP]));

	वापस tipc_add_tlv(msg->rep, TIPC_TLV_NODE_INFO, &node_info,
			    माप(node_info));
पूर्ण

अटल पूर्णांक tipc_nl_compat_net_set(काष्ठा tipc_nl_compat_cmd_करोit *cmd,
				  काष्ठा sk_buff *skb,
				  काष्ठा tipc_nl_compat_msg *msg)
अणु
	u32 val;
	काष्ठा nlattr *net;

	val = ntohl(*(__be32 *)TLV_DATA(msg->req));

	net = nla_nest_start_noflag(skb, TIPC_NLA_NET);
	अगर (!net)
		वापस -EMSGSIZE;

	अगर (msg->cmd == TIPC_CMD_SET_NODE_ADDR) अणु
		अगर (nla_put_u32(skb, TIPC_NLA_NET_ADDR, val))
			वापस -EMSGSIZE;
	पूर्ण अन्यथा अगर (msg->cmd == TIPC_CMD_SET_NETID) अणु
		अगर (nla_put_u32(skb, TIPC_NLA_NET_ID, val))
			वापस -EMSGSIZE;
	पूर्ण
	nla_nest_end(skb, net);

	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_compat_net_dump(काष्ठा tipc_nl_compat_msg *msg,
				   काष्ठा nlattr **attrs)
अणु
	__be32 id;
	काष्ठा nlattr *net[TIPC_NLA_NET_MAX + 1];
	पूर्णांक err;

	अगर (!attrs[TIPC_NLA_NET])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(net, TIPC_NLA_NET_MAX,
					  attrs[TIPC_NLA_NET], शून्य, शून्य);
	अगर (err)
		वापस err;

	id = htonl(nla_get_u32(net[TIPC_NLA_NET_ID]));

	वापस tipc_add_tlv(msg->rep, TIPC_TLV_UNSIGNED, &id, माप(id));
पूर्ण

अटल पूर्णांक tipc_cmd_show_stats_compat(काष्ठा tipc_nl_compat_msg *msg)
अणु
	msg->rep = tipc_tlv_alloc(ULTRA_STRING_MAX_LEN);
	अगर (!msg->rep)
		वापस -ENOMEM;

	tipc_tlv_init(msg->rep, TIPC_TLV_ULTRA_STRING);
	tipc_tlv_प्र_लिखो(msg->rep, "TIPC version " TIPC_MOD_VER "\n");

	वापस 0;
पूर्ण

अटल पूर्णांक tipc_nl_compat_handle(काष्ठा tipc_nl_compat_msg *msg)
अणु
	काष्ठा tipc_nl_compat_cmd_dump dump;
	काष्ठा tipc_nl_compat_cmd_करोit करोit;

	स_रखो(&dump, 0, माप(dump));
	स_रखो(&करोit, 0, माप(करोit));

	चयन (msg->cmd) अणु
	हाल TIPC_CMD_NOOP:
		msg->rep = tipc_tlv_alloc(0);
		अगर (!msg->rep)
			वापस -ENOMEM;
		वापस 0;
	हाल TIPC_CMD_GET_BEARER_NAMES:
		msg->rep_size = MAX_BEARERS * TLV_SPACE(TIPC_MAX_BEARER_NAME);
		dump.dumpit = tipc_nl_bearer_dump;
		dump.क्रमmat = tipc_nl_compat_bearer_dump;
		वापस tipc_nl_compat_dumpit(&dump, msg);
	हाल TIPC_CMD_ENABLE_BEARER:
		msg->req_type = TIPC_TLV_BEARER_CONFIG;
		करोit.करोit = __tipc_nl_bearer_enable;
		करोit.transcode = tipc_nl_compat_bearer_enable;
		वापस tipc_nl_compat_करोit(&करोit, msg);
	हाल TIPC_CMD_DISABLE_BEARER:
		msg->req_type = TIPC_TLV_BEARER_NAME;
		करोit.करोit = __tipc_nl_bearer_disable;
		करोit.transcode = tipc_nl_compat_bearer_disable;
		वापस tipc_nl_compat_करोit(&करोit, msg);
	हाल TIPC_CMD_SHOW_LINK_STATS:
		msg->req_type = TIPC_TLV_LINK_NAME;
		msg->rep_size = ULTRA_STRING_MAX_LEN;
		msg->rep_type = TIPC_TLV_ULTRA_STRING;
		dump.dumpit = tipc_nl_node_dump_link;
		dump.क्रमmat = tipc_nl_compat_link_stat_dump;
		वापस tipc_nl_compat_dumpit(&dump, msg);
	हाल TIPC_CMD_GET_LINKS:
		msg->req_type = TIPC_TLV_NET_ADDR;
		msg->rep_size = ULTRA_STRING_MAX_LEN;
		dump.dumpit = tipc_nl_node_dump_link;
		dump.क्रमmat = tipc_nl_compat_link_dump;
		वापस tipc_nl_compat_dumpit(&dump, msg);
	हाल TIPC_CMD_SET_LINK_TOL:
	हाल TIPC_CMD_SET_LINK_PRI:
	हाल TIPC_CMD_SET_LINK_WINDOW:
		msg->req_type =  TIPC_TLV_LINK_CONFIG;
		करोit.करोit = tipc_nl_node_set_link;
		करोit.transcode = tipc_nl_compat_link_set;
		वापस tipc_nl_compat_करोit(&करोit, msg);
	हाल TIPC_CMD_RESET_LINK_STATS:
		msg->req_type = TIPC_TLV_LINK_NAME;
		करोit.करोit = tipc_nl_node_reset_link_stats;
		करोit.transcode = tipc_nl_compat_link_reset_stats;
		वापस tipc_nl_compat_करोit(&करोit, msg);
	हाल TIPC_CMD_SHOW_NAME_TABLE:
		msg->req_type = TIPC_TLV_NAME_TBL_QUERY;
		msg->rep_size = ULTRA_STRING_MAX_LEN;
		msg->rep_type = TIPC_TLV_ULTRA_STRING;
		dump.header = tipc_nl_compat_name_table_dump_header;
		dump.dumpit = tipc_nl_name_table_dump;
		dump.क्रमmat = tipc_nl_compat_name_table_dump;
		वापस tipc_nl_compat_dumpit(&dump, msg);
	हाल TIPC_CMD_SHOW_PORTS:
		msg->rep_size = ULTRA_STRING_MAX_LEN;
		msg->rep_type = TIPC_TLV_ULTRA_STRING;
		dump.dumpit = tipc_nl_sk_dump;
		dump.क्रमmat = tipc_nl_compat_sk_dump;
		वापस tipc_nl_compat_dumpit(&dump, msg);
	हाल TIPC_CMD_GET_MEDIA_NAMES:
		msg->rep_size = MAX_MEDIA * TLV_SPACE(TIPC_MAX_MEDIA_NAME);
		dump.dumpit = tipc_nl_media_dump;
		dump.क्रमmat = tipc_nl_compat_media_dump;
		वापस tipc_nl_compat_dumpit(&dump, msg);
	हाल TIPC_CMD_GET_NODES:
		msg->rep_size = ULTRA_STRING_MAX_LEN;
		dump.dumpit = tipc_nl_node_dump;
		dump.क्रमmat = tipc_nl_compat_node_dump;
		वापस tipc_nl_compat_dumpit(&dump, msg);
	हाल TIPC_CMD_SET_NODE_ADDR:
		msg->req_type = TIPC_TLV_NET_ADDR;
		करोit.करोit = __tipc_nl_net_set;
		करोit.transcode = tipc_nl_compat_net_set;
		वापस tipc_nl_compat_करोit(&करोit, msg);
	हाल TIPC_CMD_SET_NETID:
		msg->req_type = TIPC_TLV_UNSIGNED;
		करोit.करोit = __tipc_nl_net_set;
		करोit.transcode = tipc_nl_compat_net_set;
		वापस tipc_nl_compat_करोit(&करोit, msg);
	हाल TIPC_CMD_GET_NETID:
		msg->rep_size = माप(u32);
		dump.dumpit = tipc_nl_net_dump;
		dump.क्रमmat = tipc_nl_compat_net_dump;
		वापस tipc_nl_compat_dumpit(&dump, msg);
	हाल TIPC_CMD_SHOW_STATS:
		वापस tipc_cmd_show_stats_compat(msg);
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक tipc_nl_compat_recv(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक err;
	पूर्णांक len;
	काष्ठा tipc_nl_compat_msg msg;
	काष्ठा nlmsghdr *req_nlh;
	काष्ठा nlmsghdr *rep_nlh;
	काष्ठा tipc_genlmsghdr *req_userhdr = info->userhdr;

	स_रखो(&msg, 0, माप(msg));

	req_nlh = (काष्ठा nlmsghdr *)skb->data;
	msg.req = nlmsg_data(req_nlh) + GENL_HDRLEN + TIPC_GENL_HDRLEN;
	msg.cmd = req_userhdr->cmd;
	msg.net = genl_info_net(info);
	msg.dst_sk = skb->sk;

	अगर ((msg.cmd & 0xC000) && (!netlink_net_capable(skb, CAP_NET_ADMIN))) अणु
		msg.rep = tipc_get_err_tlv(TIPC_CFG_NOT_NET_ADMIN);
		err = -EACCES;
		जाओ send;
	पूर्ण

	msg.req_size = nlmsg_attrlen(req_nlh, GENL_HDRLEN + TIPC_GENL_HDRLEN);
	अगर (msg.req_size && !TLV_OK(msg.req, msg.req_size)) अणु
		msg.rep = tipc_get_err_tlv(TIPC_CFG_NOT_SUPPORTED);
		err = -EOPNOTSUPP;
		जाओ send;
	पूर्ण

	err = tipc_nl_compat_handle(&msg);
	अगर ((err == -EOPNOTSUPP) || (err == -EPERM))
		msg.rep = tipc_get_err_tlv(TIPC_CFG_NOT_SUPPORTED);
	अन्यथा अगर (err == -EINVAL)
		msg.rep = tipc_get_err_tlv(TIPC_CFG_TLV_ERROR);
send:
	अगर (!msg.rep)
		वापस err;

	len = nlmsg_total_size(GENL_HDRLEN + TIPC_GENL_HDRLEN);
	skb_push(msg.rep, len);
	rep_nlh = nlmsg_hdr(msg.rep);
	स_नकल(rep_nlh, info->nlhdr, len);
	rep_nlh->nlmsg_len = msg.rep->len;
	genlmsg_unicast(msg.net, msg.rep, NETLINK_CB(skb).portid);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops tipc_genl_compat_ops[] = अणु
	अणु
		.cmd		= TIPC_GENL_CMD,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit		= tipc_nl_compat_recv,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family tipc_genl_compat_family __ro_after_init = अणु
	.name		= TIPC_GENL_NAME,
	.version	= TIPC_GENL_VERSION,
	.hdrsize	= TIPC_GENL_HDRLEN,
	.maxattr	= 0,
	.netnsok	= true,
	.module		= THIS_MODULE,
	.small_ops	= tipc_genl_compat_ops,
	.n_small_ops	= ARRAY_SIZE(tipc_genl_compat_ops),
पूर्ण;

पूर्णांक __init tipc_netlink_compat_start(व्योम)
अणु
	पूर्णांक res;

	res = genl_रेजिस्टर_family(&tipc_genl_compat_family);
	अगर (res) अणु
		pr_err("Failed to register legacy compat interface\n");
		वापस res;
	पूर्ण

	वापस 0;
पूर्ण

व्योम tipc_netlink_compat_stop(व्योम)
अणु
	genl_unरेजिस्टर_family(&tipc_genl_compat_family);
पूर्ण
