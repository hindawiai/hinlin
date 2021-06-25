<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * NETLINK      Netlink attributes
 *
 * Copyright (c) 2003-2013 Thomas Graf <tgraf@suug.ch>
 */

#समावेश <त्रुटिसं.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <linux/rtnetlink.h>
#समावेश "nlattr.h"
#समावेश "libbpf_internal.h"

अटल uपूर्णांक16_t nla_attr_minlen[LIBBPF_NLA_TYPE_MAX+1] = अणु
	[LIBBPF_NLA_U8]		= माप(uपूर्णांक8_t),
	[LIBBPF_NLA_U16]	= माप(uपूर्णांक16_t),
	[LIBBPF_NLA_U32]	= माप(uपूर्णांक32_t),
	[LIBBPF_NLA_U64]	= माप(uपूर्णांक64_t),
	[LIBBPF_NLA_STRING]	= 1,
	[LIBBPF_NLA_FLAG]	= 0,
पूर्ण;

अटल काष्ठा nlattr *nla_next(स्थिर काष्ठा nlattr *nla, पूर्णांक *reमुख्यing)
अणु
	पूर्णांक totlen = NLA_ALIGN(nla->nla_len);

	*reमुख्यing -= totlen;
	वापस (काष्ठा nlattr *) ((अक्षर *) nla + totlen);
पूर्ण

अटल पूर्णांक nla_ok(स्थिर काष्ठा nlattr *nla, पूर्णांक reमुख्यing)
अणु
	वापस reमुख्यing >= माप(*nla) &&
	       nla->nla_len >= माप(*nla) &&
	       nla->nla_len <= reमुख्यing;
पूर्ण

अटल पूर्णांक nla_type(स्थिर काष्ठा nlattr *nla)
अणु
	वापस nla->nla_type & NLA_TYPE_MASK;
पूर्ण

अटल पूर्णांक validate_nla(काष्ठा nlattr *nla, पूर्णांक maxtype,
			काष्ठा libbpf_nla_policy *policy)
अणु
	काष्ठा libbpf_nla_policy *pt;
	अचिन्हित पूर्णांक minlen = 0;
	पूर्णांक type = nla_type(nla);

	अगर (type < 0 || type > maxtype)
		वापस 0;

	pt = &policy[type];

	अगर (pt->type > LIBBPF_NLA_TYPE_MAX)
		वापस 0;

	अगर (pt->minlen)
		minlen = pt->minlen;
	अन्यथा अगर (pt->type != LIBBPF_NLA_UNSPEC)
		minlen = nla_attr_minlen[pt->type];

	अगर (libbpf_nla_len(nla) < minlen)
		वापस -1;

	अगर (pt->maxlen && libbpf_nla_len(nla) > pt->maxlen)
		वापस -1;

	अगर (pt->type == LIBBPF_NLA_STRING) अणु
		अक्षर *data = libbpf_nla_data(nla);

		अगर (data[libbpf_nla_len(nla) - 1] != '\0')
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक nlmsg_len(स्थिर काष्ठा nlmsghdr *nlh)
अणु
	वापस nlh->nlmsg_len - NLMSG_HDRLEN;
पूर्ण

/**
 * Create attribute index based on a stream of attributes.
 * @arg tb		Index array to be filled (maxtype+1 elements).
 * @arg maxtype		Maximum attribute type expected and accepted.
 * @arg head		Head of attribute stream.
 * @arg len		Length of attribute stream.
 * @arg policy		Attribute validation policy.
 *
 * Iterates over the stream of attributes and stores a poपूर्णांकer to each
 * attribute in the index array using the attribute type as index to
 * the array. Attribute with a type greater than the maximum type
 * specअगरied will be silently ignored in order to मुख्यtain backwards
 * compatibility. If \च policy is not शून्य, the attribute will be
 * validated using the specअगरied policy.
 *
 * @see nla_validate
 * @वापस 0 on success or a negative error code.
 */
पूर्णांक libbpf_nla_parse(काष्ठा nlattr *tb[], पूर्णांक maxtype, काष्ठा nlattr *head,
		     पूर्णांक len, काष्ठा libbpf_nla_policy *policy)
अणु
	काष्ठा nlattr *nla;
	पूर्णांक rem, err;

	स_रखो(tb, 0, माप(काष्ठा nlattr *) * (maxtype + 1));

	libbpf_nla_क्रम_each_attr(nla, head, len, rem) अणु
		पूर्णांक type = nla_type(nla);

		अगर (type > maxtype)
			जारी;

		अगर (policy) अणु
			err = validate_nla(nla, maxtype, policy);
			अगर (err < 0)
				जाओ errout;
		पूर्ण

		अगर (tb[type])
			pr_warn("Attribute of type %#x found multiple times in message, "
				"previous attribute is being ignored.\n", type);

		tb[type] = nla;
	पूर्ण

	err = 0;
errout:
	वापस err;
पूर्ण

/**
 * Create attribute index based on nested attribute
 * @arg tb              Index array to be filled (maxtype+1 elements).
 * @arg maxtype         Maximum attribute type expected and accepted.
 * @arg nla             Nested Attribute.
 * @arg policy          Attribute validation policy.
 *
 * Feeds the stream of attributes nested पूर्णांकo the specअगरied attribute
 * to libbpf_nla_parse().
 *
 * @see libbpf_nla_parse
 * @वापस 0 on success or a negative error code.
 */
पूर्णांक libbpf_nla_parse_nested(काष्ठा nlattr *tb[], पूर्णांक maxtype,
			    काष्ठा nlattr *nla,
			    काष्ठा libbpf_nla_policy *policy)
अणु
	वापस libbpf_nla_parse(tb, maxtype, libbpf_nla_data(nla),
				libbpf_nla_len(nla), policy);
पूर्ण

/* dump netlink extended ack error message */
पूर्णांक libbpf_nla_dump_errormsg(काष्ठा nlmsghdr *nlh)
अणु
	काष्ठा libbpf_nla_policy extack_policy[NLMSGERR_ATTR_MAX + 1] = अणु
		[NLMSGERR_ATTR_MSG]	= अणु .type = LIBBPF_NLA_STRING पूर्ण,
		[NLMSGERR_ATTR_OFFS]	= अणु .type = LIBBPF_NLA_U32 पूर्ण,
	पूर्ण;
	काष्ठा nlattr *tb[NLMSGERR_ATTR_MAX + 1], *attr;
	काष्ठा nlmsgerr *err;
	अक्षर *errmsg = शून्य;
	पूर्णांक hlen, alen;

	/* no TLVs, nothing to करो here */
	अगर (!(nlh->nlmsg_flags & NLM_F_ACK_TLVS))
		वापस 0;

	err = (काष्ठा nlmsgerr *)NLMSG_DATA(nlh);
	hlen = माप(*err);

	/* अगर NLM_F_CAPPED is set then the inner err msg was capped */
	अगर (!(nlh->nlmsg_flags & NLM_F_CAPPED))
		hlen += nlmsg_len(&err->msg);

	attr = (काष्ठा nlattr *) ((व्योम *) err + hlen);
	alen = nlh->nlmsg_len - hlen;

	अगर (libbpf_nla_parse(tb, NLMSGERR_ATTR_MAX, attr, alen,
			     extack_policy) != 0) अणु
		pr_warn("Failed to parse extended error attributes\n");
		वापस 0;
	पूर्ण

	अगर (tb[NLMSGERR_ATTR_MSG])
		errmsg = (अक्षर *) libbpf_nla_data(tb[NLMSGERR_ATTR_MSG]);

	pr_warn("Kernel error message: %s\n", errmsg);

	वापस 0;
पूर्ण
