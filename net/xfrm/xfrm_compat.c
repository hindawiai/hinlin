<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * XFRM compat layer
 * Author: Dmitry Safonov <dima@arista.com>
 * Based on code and translator idea by: Florian Westphal <fw@म_माप.de>
 */
#समावेश <linux/compat.h>
#समावेश <linux/xfrm.h>
#समावेश <net/xfrm.h>

काष्ठा compat_xfrm_lअगरeसमय_cfg अणु
	compat_u64 soft_byte_limit, hard_byte_limit;
	compat_u64 soft_packet_limit, hard_packet_limit;
	compat_u64 soft_add_expires_seconds, hard_add_expires_seconds;
	compat_u64 soft_use_expires_seconds, hard_use_expires_seconds;
पूर्ण; /* same size on 32bit, but only 4 byte alignment required */

काष्ठा compat_xfrm_lअगरeसमय_cur अणु
	compat_u64 bytes, packets, add_समय, use_समय;
पूर्ण; /* same size on 32bit, but only 4 byte alignment required */

काष्ठा compat_xfrm_userpolicy_info अणु
	काष्ठा xfrm_selector sel;
	काष्ठा compat_xfrm_lअगरeसमय_cfg lft;
	काष्ठा compat_xfrm_lअगरeसमय_cur curlft;
	__u32 priority, index;
	u8 dir, action, flags, share;
	/* 4 bytes additional padding on 64bit */
पूर्ण;

काष्ठा compat_xfrm_usersa_info अणु
	काष्ठा xfrm_selector sel;
	काष्ठा xfrm_id id;
	xfrm_address_t saddr;
	काष्ठा compat_xfrm_lअगरeसमय_cfg lft;
	काष्ठा compat_xfrm_lअगरeसमय_cur curlft;
	काष्ठा xfrm_stats stats;
	__u32 seq, reqid;
	u16 family;
	u8 mode, replay_winकरोw, flags;
	/* 4 bytes additional padding on 64bit */
पूर्ण;

काष्ठा compat_xfrm_user_acquire अणु
	काष्ठा xfrm_id id;
	xfrm_address_t saddr;
	काष्ठा xfrm_selector sel;
	काष्ठा compat_xfrm_userpolicy_info policy;
	/* 4 bytes additional padding on 64bit */
	__u32 aalgos, ealgos, calgos, seq;
पूर्ण;

काष्ठा compat_xfrm_userspi_info अणु
	काष्ठा compat_xfrm_usersa_info info;
	/* 4 bytes additional padding on 64bit */
	__u32 min, max;
पूर्ण;

काष्ठा compat_xfrm_user_expire अणु
	काष्ठा compat_xfrm_usersa_info state;
	/* 8 bytes additional padding on 64bit */
	u8 hard;
पूर्ण;

काष्ठा compat_xfrm_user_polexpire अणु
	काष्ठा compat_xfrm_userpolicy_info pol;
	/* 8 bytes additional padding on 64bit */
	u8 hard;
पूर्ण;

#घोषणा XMSGSIZE(type) माप(काष्ठा type)

अटल स्थिर पूर्णांक compat_msg_min[XFRM_NR_MSGTYPES] = अणु
	[XFRM_MSG_NEWSA       - XFRM_MSG_BASE] = XMSGSIZE(compat_xfrm_usersa_info),
	[XFRM_MSG_DELSA       - XFRM_MSG_BASE] = XMSGSIZE(xfrm_usersa_id),
	[XFRM_MSG_GETSA       - XFRM_MSG_BASE] = XMSGSIZE(xfrm_usersa_id),
	[XFRM_MSG_NEWPOLICY   - XFRM_MSG_BASE] = XMSGSIZE(compat_xfrm_userpolicy_info),
	[XFRM_MSG_DELPOLICY   - XFRM_MSG_BASE] = XMSGSIZE(xfrm_userpolicy_id),
	[XFRM_MSG_GETPOLICY   - XFRM_MSG_BASE] = XMSGSIZE(xfrm_userpolicy_id),
	[XFRM_MSG_ALLOCSPI    - XFRM_MSG_BASE] = XMSGSIZE(compat_xfrm_userspi_info),
	[XFRM_MSG_ACQUIRE     - XFRM_MSG_BASE] = XMSGSIZE(compat_xfrm_user_acquire),
	[XFRM_MSG_EXPIRE      - XFRM_MSG_BASE] = XMSGSIZE(compat_xfrm_user_expire),
	[XFRM_MSG_UPDPOLICY   - XFRM_MSG_BASE] = XMSGSIZE(compat_xfrm_userpolicy_info),
	[XFRM_MSG_UPDSA       - XFRM_MSG_BASE] = XMSGSIZE(compat_xfrm_usersa_info),
	[XFRM_MSG_POLEXPIRE   - XFRM_MSG_BASE] = XMSGSIZE(compat_xfrm_user_polexpire),
	[XFRM_MSG_FLUSHSA     - XFRM_MSG_BASE] = XMSGSIZE(xfrm_usersa_flush),
	[XFRM_MSG_FLUSHPOLICY - XFRM_MSG_BASE] = 0,
	[XFRM_MSG_NEWAE       - XFRM_MSG_BASE] = XMSGSIZE(xfrm_aevent_id),
	[XFRM_MSG_GETAE       - XFRM_MSG_BASE] = XMSGSIZE(xfrm_aevent_id),
	[XFRM_MSG_REPORT      - XFRM_MSG_BASE] = XMSGSIZE(xfrm_user_report),
	[XFRM_MSG_MIGRATE     - XFRM_MSG_BASE] = XMSGSIZE(xfrm_userpolicy_id),
	[XFRM_MSG_NEWSADINFO  - XFRM_MSG_BASE] = माप(u32),
	[XFRM_MSG_GETSADINFO  - XFRM_MSG_BASE] = माप(u32),
	[XFRM_MSG_NEWSPDINFO  - XFRM_MSG_BASE] = माप(u32),
	[XFRM_MSG_GETSPDINFO  - XFRM_MSG_BASE] = माप(u32),
	[XFRM_MSG_MAPPING     - XFRM_MSG_BASE] = XMSGSIZE(xfrm_user_mapping)
पूर्ण;

अटल स्थिर काष्ठा nla_policy compat_policy[XFRMA_MAX+1] = अणु
	[XFRMA_SA]		= अणु .len = XMSGSIZE(compat_xfrm_usersa_info)पूर्ण,
	[XFRMA_POLICY]		= अणु .len = XMSGSIZE(compat_xfrm_userpolicy_info)पूर्ण,
	[XFRMA_LASTUSED]	= अणु .type = NLA_U64पूर्ण,
	[XFRMA_ALG_AUTH_TRUNC]	= अणु .len = माप(काष्ठा xfrm_algo_auth)पूर्ण,
	[XFRMA_ALG_AEAD]	= अणु .len = माप(काष्ठा xfrm_algo_aead) पूर्ण,
	[XFRMA_ALG_AUTH]	= अणु .len = माप(काष्ठा xfrm_algo) पूर्ण,
	[XFRMA_ALG_CRYPT]	= अणु .len = माप(काष्ठा xfrm_algo) पूर्ण,
	[XFRMA_ALG_COMP]	= अणु .len = माप(काष्ठा xfrm_algo) पूर्ण,
	[XFRMA_ENCAP]		= अणु .len = माप(काष्ठा xfrm_encap_पंचांगpl) पूर्ण,
	[XFRMA_TMPL]		= अणु .len = माप(काष्ठा xfrm_user_पंचांगpl) पूर्ण,
	[XFRMA_SEC_CTX]		= अणु .len = माप(काष्ठा xfrm_sec_ctx) पूर्ण,
	[XFRMA_LTIME_VAL]	= अणु .len = माप(काष्ठा xfrm_lअगरeसमय_cur) पूर्ण,
	[XFRMA_REPLAY_VAL]	= अणु .len = माप(काष्ठा xfrm_replay_state) पूर्ण,
	[XFRMA_REPLAY_THRESH]	= अणु .type = NLA_U32 पूर्ण,
	[XFRMA_ETIMER_THRESH]	= अणु .type = NLA_U32 पूर्ण,
	[XFRMA_SRCADDR]		= अणु .len = माप(xfrm_address_t) पूर्ण,
	[XFRMA_COADDR]		= अणु .len = माप(xfrm_address_t) पूर्ण,
	[XFRMA_POLICY_TYPE]	= अणु .len = माप(काष्ठा xfrm_userpolicy_type)पूर्ण,
	[XFRMA_MIGRATE]		= अणु .len = माप(काष्ठा xfrm_user_migrate) पूर्ण,
	[XFRMA_KMADDRESS]	= अणु .len = माप(काष्ठा xfrm_user_kmaddress) पूर्ण,
	[XFRMA_MARK]		= अणु .len = माप(काष्ठा xfrm_mark) पूर्ण,
	[XFRMA_TFCPAD]		= अणु .type = NLA_U32 पूर्ण,
	[XFRMA_REPLAY_ESN_VAL]	= अणु .len = माप(काष्ठा xfrm_replay_state_esn) पूर्ण,
	[XFRMA_SA_EXTRA_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
	[XFRMA_PROTO]		= अणु .type = NLA_U8 पूर्ण,
	[XFRMA_ADDRESS_FILTER]	= अणु .len = माप(काष्ठा xfrm_address_filter) पूर्ण,
	[XFRMA_OFFLOAD_DEV]	= अणु .len = माप(काष्ठा xfrm_user_offload) पूर्ण,
	[XFRMA_SET_MARK]	= अणु .type = NLA_U32 पूर्ण,
	[XFRMA_SET_MARK_MASK]	= अणु .type = NLA_U32 पूर्ण,
	[XFRMA_IF_ID]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल काष्ठा nlmsghdr *xfrm_nlmsg_put_compat(काष्ठा sk_buff *skb,
			स्थिर काष्ठा nlmsghdr *nlh_src, u16 type)
अणु
	पूर्णांक payload = compat_msg_min[type];
	पूर्णांक src_len = xfrm_msg_min[type];
	काष्ठा nlmsghdr *nlh_dst;

	/* Compat messages are लघुer or equal to native (+padding) */
	अगर (WARN_ON_ONCE(src_len < payload))
		वापस ERR_PTR(-EMSGSIZE);

	nlh_dst = nlmsg_put(skb, nlh_src->nlmsg_pid, nlh_src->nlmsg_seq,
			    nlh_src->nlmsg_type, payload, nlh_src->nlmsg_flags);
	अगर (!nlh_dst)
		वापस ERR_PTR(-EMSGSIZE);

	स_रखो(nlmsg_data(nlh_dst), 0, payload);

	चयन (nlh_src->nlmsg_type) अणु
	/* Compat message has the same layout as native */
	हाल XFRM_MSG_DELSA:
	हाल XFRM_MSG_DELPOLICY:
	हाल XFRM_MSG_FLUSHSA:
	हाल XFRM_MSG_FLUSHPOLICY:
	हाल XFRM_MSG_NEWAE:
	हाल XFRM_MSG_REPORT:
	हाल XFRM_MSG_MIGRATE:
	हाल XFRM_MSG_NEWSADINFO:
	हाल XFRM_MSG_NEWSPDINFO:
	हाल XFRM_MSG_MAPPING:
		WARN_ON_ONCE(src_len != payload);
		स_नकल(nlmsg_data(nlh_dst), nlmsg_data(nlh_src), src_len);
		अवरोध;
	/* 4 byte alignment क्रम trailing u64 on native, but not on compat */
	हाल XFRM_MSG_NEWSA:
	हाल XFRM_MSG_NEWPOLICY:
	हाल XFRM_MSG_UPDSA:
	हाल XFRM_MSG_UPDPOLICY:
		WARN_ON_ONCE(src_len != payload + 4);
		स_नकल(nlmsg_data(nlh_dst), nlmsg_data(nlh_src), payload);
		अवरोध;
	हाल XFRM_MSG_EXPIRE: अणु
		स्थिर काष्ठा xfrm_user_expire *src_ue  = nlmsg_data(nlh_src);
		काष्ठा compat_xfrm_user_expire *dst_ue = nlmsg_data(nlh_dst);

		/* compat_xfrm_user_expire has 4-byte smaller state */
		स_नकल(dst_ue, src_ue, माप(dst_ue->state));
		dst_ue->hard = src_ue->hard;
		अवरोध;
	पूर्ण
	हाल XFRM_MSG_ACQUIRE: अणु
		स्थिर काष्ठा xfrm_user_acquire *src_ua  = nlmsg_data(nlh_src);
		काष्ठा compat_xfrm_user_acquire *dst_ua = nlmsg_data(nlh_dst);

		स_नकल(dst_ua, src_ua, दुरत्व(काष्ठा compat_xfrm_user_acquire, aalgos));
		dst_ua->aalgos = src_ua->aalgos;
		dst_ua->ealgos = src_ua->ealgos;
		dst_ua->calgos = src_ua->calgos;
		dst_ua->seq    = src_ua->seq;
		अवरोध;
	पूर्ण
	हाल XFRM_MSG_POLEXPIRE: अणु
		स्थिर काष्ठा xfrm_user_polexpire *src_upe  = nlmsg_data(nlh_src);
		काष्ठा compat_xfrm_user_polexpire *dst_upe = nlmsg_data(nlh_dst);

		/* compat_xfrm_user_polexpire has 4-byte smaller state */
		स_नकल(dst_upe, src_upe, माप(dst_upe->pol));
		dst_upe->hard = src_upe->hard;
		अवरोध;
	पूर्ण
	हाल XFRM_MSG_ALLOCSPI: अणु
		स्थिर काष्ठा xfrm_userspi_info *src_usi = nlmsg_data(nlh_src);
		काष्ठा compat_xfrm_userspi_info *dst_usi = nlmsg_data(nlh_dst);

		/* compat_xfrm_user_polexpire has 4-byte smaller state */
		स_नकल(dst_usi, src_usi, माप(src_usi->info));
		dst_usi->min = src_usi->min;
		dst_usi->max = src_usi->max;
		अवरोध;
	पूर्ण
	/* Not being sent by kernel */
	हाल XFRM_MSG_GETSA:
	हाल XFRM_MSG_GETPOLICY:
	हाल XFRM_MSG_GETAE:
	हाल XFRM_MSG_GETSADINFO:
	हाल XFRM_MSG_GETSPDINFO:
	शेष:
		pr_warn_once("unsupported nlmsg_type %d\n", nlh_src->nlmsg_type);
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	वापस nlh_dst;
पूर्ण

अटल पूर्णांक xfrm_nla_cpy(काष्ठा sk_buff *dst, स्थिर काष्ठा nlattr *src, पूर्णांक len)
अणु
	वापस nla_put(dst, src->nla_type, len, nla_data(src));
पूर्ण

अटल पूर्णांक xfrm_xlate64_attr(काष्ठा sk_buff *dst, स्थिर काष्ठा nlattr *src)
अणु
	चयन (src->nla_type) अणु
	हाल XFRMA_PAD:
		/* Ignore */
		वापस 0;
	हाल XFRMA_UNSPEC:
	हाल XFRMA_ALG_AUTH:
	हाल XFRMA_ALG_CRYPT:
	हाल XFRMA_ALG_COMP:
	हाल XFRMA_ENCAP:
	हाल XFRMA_TMPL:
		वापस xfrm_nla_cpy(dst, src, nla_len(src));
	हाल XFRMA_SA:
		वापस xfrm_nla_cpy(dst, src, XMSGSIZE(compat_xfrm_usersa_info));
	हाल XFRMA_POLICY:
		वापस xfrm_nla_cpy(dst, src, XMSGSIZE(compat_xfrm_userpolicy_info));
	हाल XFRMA_SEC_CTX:
		वापस xfrm_nla_cpy(dst, src, nla_len(src));
	हाल XFRMA_LTIME_VAL:
		वापस nla_put_64bit(dst, src->nla_type, nla_len(src),
			nla_data(src), XFRMA_PAD);
	हाल XFRMA_REPLAY_VAL:
	हाल XFRMA_REPLAY_THRESH:
	हाल XFRMA_ETIMER_THRESH:
	हाल XFRMA_SRCADDR:
	हाल XFRMA_COADDR:
		वापस xfrm_nla_cpy(dst, src, nla_len(src));
	हाल XFRMA_LASTUSED:
		वापस nla_put_64bit(dst, src->nla_type, nla_len(src),
			nla_data(src), XFRMA_PAD);
	हाल XFRMA_POLICY_TYPE:
	हाल XFRMA_MIGRATE:
	हाल XFRMA_ALG_AEAD:
	हाल XFRMA_KMADDRESS:
	हाल XFRMA_ALG_AUTH_TRUNC:
	हाल XFRMA_MARK:
	हाल XFRMA_TFCPAD:
	हाल XFRMA_REPLAY_ESN_VAL:
	हाल XFRMA_SA_EXTRA_FLAGS:
	हाल XFRMA_PROTO:
	हाल XFRMA_ADDRESS_FILTER:
	हाल XFRMA_OFFLOAD_DEV:
	हाल XFRMA_SET_MARK:
	हाल XFRMA_SET_MARK_MASK:
	हाल XFRMA_IF_ID:
		वापस xfrm_nla_cpy(dst, src, nla_len(src));
	शेष:
		BUILD_BUG_ON(XFRMA_MAX != XFRMA_IF_ID);
		pr_warn_once("unsupported nla_type %d\n", src->nla_type);
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

/* Take kernel-built (64bit layout) and create 32bit layout क्रम userspace */
अटल पूर्णांक xfrm_xlate64(काष्ठा sk_buff *dst, स्थिर काष्ठा nlmsghdr *nlh_src)
अणु
	u16 type = nlh_src->nlmsg_type - XFRM_MSG_BASE;
	स्थिर काष्ठा nlattr *nla, *attrs;
	काष्ठा nlmsghdr *nlh_dst;
	पूर्णांक len, reमुख्यing;

	nlh_dst = xfrm_nlmsg_put_compat(dst, nlh_src, type);
	अगर (IS_ERR(nlh_dst))
		वापस PTR_ERR(nlh_dst);

	attrs = nlmsg_attrdata(nlh_src, xfrm_msg_min[type]);
	len = nlmsg_attrlen(nlh_src, xfrm_msg_min[type]);

	nla_क्रम_each_attr(nla, attrs, len, reमुख्यing) अणु
		पूर्णांक err = xfrm_xlate64_attr(dst, nla);

		अगर (err)
			वापस err;
	पूर्ण

	nlmsg_end(dst, nlh_dst);

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_alloc_compat(काष्ठा sk_buff *skb, स्थिर काष्ठा nlmsghdr *nlh_src)
अणु
	u16 type = nlh_src->nlmsg_type - XFRM_MSG_BASE;
	काष्ठा sk_buff *new = शून्य;
	पूर्णांक err;

	अगर (type >= ARRAY_SIZE(xfrm_msg_min)) अणु
		pr_warn_once("unsupported nlmsg_type %d\n", nlh_src->nlmsg_type);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (skb_shinfo(skb)->frag_list == शून्य) अणु
		new = alloc_skb(skb->len + skb_tailroom(skb), GFP_ATOMIC);
		अगर (!new)
			वापस -ENOMEM;
		skb_shinfo(skb)->frag_list = new;
	पूर्ण

	err = xfrm_xlate64(skb_shinfo(skb)->frag_list, nlh_src);
	अगर (err) अणु
		अगर (new) अणु
			kमुक्त_skb(new);
			skb_shinfo(skb)->frag_list = शून्य;
		पूर्ण
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Calculates len of translated 64-bit message. */
अटल माप_प्रकार xfrm_user_rcv_calculate_len64(स्थिर काष्ठा nlmsghdr *src,
					    काष्ठा nlattr *attrs[XFRMA_MAX+1])
अणु
	माप_प्रकार len = nlmsg_len(src);

	चयन (src->nlmsg_type) अणु
	हाल XFRM_MSG_NEWSA:
	हाल XFRM_MSG_NEWPOLICY:
	हाल XFRM_MSG_ALLOCSPI:
	हाल XFRM_MSG_ACQUIRE:
	हाल XFRM_MSG_UPDPOLICY:
	हाल XFRM_MSG_UPDSA:
		len += 4;
		अवरोध;
	हाल XFRM_MSG_EXPIRE:
	हाल XFRM_MSG_POLEXPIRE:
		len += 8;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (attrs[XFRMA_SA])
		len += 4;
	अगर (attrs[XFRMA_POLICY])
		len += 4;

	/* XXX: some attrs may need to be realigned
	 * अगर !CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	 */

	वापस len;
पूर्ण

अटल पूर्णांक xfrm_attr_cpy32(व्योम *dst, माप_प्रकार *pos, स्थिर काष्ठा nlattr *src,
			   माप_प्रकार size, पूर्णांक copy_len, पूर्णांक payload)
अणु
	काष्ठा nlmsghdr *nlmsg = dst;
	काष्ठा nlattr *nla;

	/* xfrm_user_rcv_msg_compat() relies on fact that 32-bit messages
	 * have the same len or लघुed than 64-bit ones.
	 * 32-bit translation that is bigger than 64-bit original is unexpected.
	 */
	अगर (WARN_ON_ONCE(copy_len > payload))
		copy_len = payload;

	अगर (size - *pos < nla_attr_size(payload))
		वापस -ENOBUFS;

	nla = dst + *pos;

	स_नकल(nla, src, nla_attr_size(copy_len));
	nla->nla_len = nla_attr_size(payload);
	*pos += nla_attr_size(copy_len);
	nlmsg->nlmsg_len += nla->nla_len;

	स_रखो(dst + *pos, 0, payload - copy_len);
	*pos += payload - copy_len;

	वापस 0;
पूर्ण

अटल पूर्णांक xfrm_xlate32_attr(व्योम *dst, स्थिर काष्ठा nlattr *nla,
			     माप_प्रकार *pos, माप_प्रकार size,
			     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक type = nla_type(nla);
	u16 pol_len32, pol_len64;
	पूर्णांक err;

	अगर (type > XFRMA_MAX) अणु
		BUILD_BUG_ON(XFRMA_MAX != XFRMA_IF_ID);
		NL_SET_ERR_MSG(extack, "Bad attribute");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (nla_len(nla) < compat_policy[type].len) अणु
		NL_SET_ERR_MSG(extack, "Attribute bad length");
		वापस -EOPNOTSUPP;
	पूर्ण

	pol_len32 = compat_policy[type].len;
	pol_len64 = xfrma_policy[type].len;

	/* XFRMA_SA and XFRMA_POLICY - need to know how-to translate */
	अगर (pol_len32 != pol_len64) अणु
		अगर (nla_len(nla) != compat_policy[type].len) अणु
			NL_SET_ERR_MSG(extack, "Attribute bad length");
			वापस -EOPNOTSUPP;
		पूर्ण
		err = xfrm_attr_cpy32(dst, pos, nla, size, pol_len32, pol_len64);
		अगर (err)
			वापस err;
	पूर्ण

	वापस xfrm_attr_cpy32(dst, pos, nla, size, nla_len(nla), nla_len(nla));
पूर्ण

अटल पूर्णांक xfrm_xlate32(काष्ठा nlmsghdr *dst, स्थिर काष्ठा nlmsghdr *src,
			काष्ठा nlattr *attrs[XFRMA_MAX+1],
			माप_प्रकार size, u8 type, काष्ठा netlink_ext_ack *extack)
अणु
	माप_प्रकार pos;
	पूर्णांक i;

	स_नकल(dst, src, NLMSG_HDRLEN);
	dst->nlmsg_len = NLMSG_HDRLEN + xfrm_msg_min[type];
	स_रखो(nlmsg_data(dst), 0, xfrm_msg_min[type]);

	चयन (src->nlmsg_type) अणु
	/* Compat message has the same layout as native */
	हाल XFRM_MSG_DELSA:
	हाल XFRM_MSG_GETSA:
	हाल XFRM_MSG_DELPOLICY:
	हाल XFRM_MSG_GETPOLICY:
	हाल XFRM_MSG_FLUSHSA:
	हाल XFRM_MSG_FLUSHPOLICY:
	हाल XFRM_MSG_NEWAE:
	हाल XFRM_MSG_GETAE:
	हाल XFRM_MSG_REPORT:
	हाल XFRM_MSG_MIGRATE:
	हाल XFRM_MSG_NEWSADINFO:
	हाल XFRM_MSG_GETSADINFO:
	हाल XFRM_MSG_NEWSPDINFO:
	हाल XFRM_MSG_GETSPDINFO:
	हाल XFRM_MSG_MAPPING:
		स_नकल(nlmsg_data(dst), nlmsg_data(src), compat_msg_min[type]);
		अवरोध;
	/* 4 byte alignment क्रम trailing u64 on native, but not on compat */
	हाल XFRM_MSG_NEWSA:
	हाल XFRM_MSG_NEWPOLICY:
	हाल XFRM_MSG_UPDSA:
	हाल XFRM_MSG_UPDPOLICY:
		स_नकल(nlmsg_data(dst), nlmsg_data(src), compat_msg_min[type]);
		अवरोध;
	हाल XFRM_MSG_EXPIRE: अणु
		स्थिर काष्ठा compat_xfrm_user_expire *src_ue = nlmsg_data(src);
		काष्ठा xfrm_user_expire *dst_ue = nlmsg_data(dst);

		/* compat_xfrm_user_expire has 4-byte smaller state */
		स_नकल(dst_ue, src_ue, माप(src_ue->state));
		dst_ue->hard = src_ue->hard;
		अवरोध;
	पूर्ण
	हाल XFRM_MSG_ACQUIRE: अणु
		स्थिर काष्ठा compat_xfrm_user_acquire *src_ua = nlmsg_data(src);
		काष्ठा xfrm_user_acquire *dst_ua = nlmsg_data(dst);

		स_नकल(dst_ua, src_ua, दुरत्व(काष्ठा compat_xfrm_user_acquire, aalgos));
		dst_ua->aalgos = src_ua->aalgos;
		dst_ua->ealgos = src_ua->ealgos;
		dst_ua->calgos = src_ua->calgos;
		dst_ua->seq    = src_ua->seq;
		अवरोध;
	पूर्ण
	हाल XFRM_MSG_POLEXPIRE: अणु
		स्थिर काष्ठा compat_xfrm_user_polexpire *src_upe = nlmsg_data(src);
		काष्ठा xfrm_user_polexpire *dst_upe = nlmsg_data(dst);

		/* compat_xfrm_user_polexpire has 4-byte smaller state */
		स_नकल(dst_upe, src_upe, माप(src_upe->pol));
		dst_upe->hard = src_upe->hard;
		अवरोध;
	पूर्ण
	हाल XFRM_MSG_ALLOCSPI: अणु
		स्थिर काष्ठा compat_xfrm_userspi_info *src_usi = nlmsg_data(src);
		काष्ठा xfrm_userspi_info *dst_usi = nlmsg_data(dst);

		/* compat_xfrm_user_polexpire has 4-byte smaller state */
		स_नकल(dst_usi, src_usi, माप(src_usi->info));
		dst_usi->min = src_usi->min;
		dst_usi->max = src_usi->max;
		अवरोध;
	पूर्ण
	शेष:
		NL_SET_ERR_MSG(extack, "Unsupported message type");
		वापस -EOPNOTSUPP;
	पूर्ण
	pos = dst->nlmsg_len;

	क्रम (i = 1; i < XFRMA_MAX + 1; i++) अणु
		पूर्णांक err;

		अगर (i == XFRMA_PAD)
			जारी;

		अगर (!attrs[i])
			जारी;

		err = xfrm_xlate32_attr(dst, attrs[i], &pos, size, extack);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा nlmsghdr *xfrm_user_rcv_msg_compat(स्थिर काष्ठा nlmsghdr *h32,
			पूर्णांक maxtype, स्थिर काष्ठा nla_policy *policy,
			काष्ठा netlink_ext_ack *extack)
अणु
	/* netlink_rcv_skb() checks अगर a message has full (काष्ठा nlmsghdr) */
	u16 type = h32->nlmsg_type - XFRM_MSG_BASE;
	काष्ठा nlattr *attrs[XFRMA_MAX+1];
	काष्ठा nlmsghdr *h64;
	माप_प्रकार len;
	पूर्णांक err;

	BUILD_BUG_ON(ARRAY_SIZE(xfrm_msg_min) != ARRAY_SIZE(compat_msg_min));

	अगर (type >= ARRAY_SIZE(xfrm_msg_min))
		वापस ERR_PTR(-EINVAL);

	/* Don't call parse: the message might have only nlmsg header */
	अगर ((h32->nlmsg_type == XFRM_MSG_GETSA ||
	     h32->nlmsg_type == XFRM_MSG_GETPOLICY) &&
	    (h32->nlmsg_flags & NLM_F_DUMP))
		वापस शून्य;

	err = nlmsg_parse_deprecated(h32, compat_msg_min[type], attrs,
			maxtype ? : XFRMA_MAX, policy ? : compat_policy, extack);
	अगर (err < 0)
		वापस ERR_PTR(err);

	len = xfrm_user_rcv_calculate_len64(h32, attrs);
	/* The message करोesn't need translation */
	अगर (len == nlmsg_len(h32))
		वापस शून्य;

	len += NLMSG_HDRLEN;
	h64 = kvदो_स्मृति(len, GFP_KERNEL);
	अगर (!h64)
		वापस ERR_PTR(-ENOMEM);

	err = xfrm_xlate32(h64, h32, attrs, len, type, extack);
	अगर (err < 0) अणु
		kvमुक्त(h64);
		वापस ERR_PTR(err);
	पूर्ण

	वापस h64;
पूर्ण

अटल पूर्णांक xfrm_user_policy_compat(u8 **pdata32, पूर्णांक optlen)
अणु
	काष्ठा compat_xfrm_userpolicy_info *p = (व्योम *)*pdata32;
	u8 *src_ढाँचाs, *dst_ढाँचाs;
	u8 *data64;

	अगर (optlen < माप(*p))
		वापस -EINVAL;

	data64 = kदो_स्मृति_track_caller(optlen + 4, GFP_USER | __GFP_NOWARN);
	अगर (!data64)
		वापस -ENOMEM;

	स_नकल(data64, *pdata32, माप(*p));
	स_रखो(data64 + माप(*p), 0, 4);

	src_ढाँचाs = *pdata32 + माप(*p);
	dst_ढाँचाs = data64 + माप(*p) + 4;
	स_नकल(dst_ढाँचाs, src_ढाँचाs, optlen - माप(*p));

	kमुक्त(*pdata32);
	*pdata32 = data64;
	वापस 0;
पूर्ण

अटल काष्ठा xfrm_translator xfrm_translator = अणु
	.owner				= THIS_MODULE,
	.alloc_compat			= xfrm_alloc_compat,
	.rcv_msg_compat			= xfrm_user_rcv_msg_compat,
	.xlate_user_policy_sockptr	= xfrm_user_policy_compat,
पूर्ण;

अटल पूर्णांक __init xfrm_compat_init(व्योम)
अणु
	वापस xfrm_रेजिस्टर_translator(&xfrm_translator);
पूर्ण

अटल व्योम __निकास xfrm_compat_निकास(व्योम)
अणु
	xfrm_unरेजिस्टर_translator(&xfrm_translator);
पूर्ण

module_init(xfrm_compat_init);
module_निकास(xfrm_compat_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dmitry Safonov");
MODULE_DESCRIPTION("XFRM 32-bit compatibility layer");
