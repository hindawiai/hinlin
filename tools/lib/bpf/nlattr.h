<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */

/*
 * NETLINK      Netlink attributes
 *
 * Copyright (c) 2003-2013 Thomas Graf <tgraf@suug.ch>
 */

#अगर_अघोषित __LIBBPF_NLATTR_H
#घोषणा __LIBBPF_NLATTR_H

#समावेश <मानक_निवेशt.h>
#समावेश <linux/netlink.h>
/* aव्योम multiple definition of netlink features */
#घोषणा __LINUX_NETLINK_H

/**
 * Standard attribute types to specअगरy validation policy
 */
क्रमागत अणु
	LIBBPF_NLA_UNSPEC,	/**< Unspecअगरied type, binary data chunk */
	LIBBPF_NLA_U8,		/**< 8 bit पूर्णांकeger */
	LIBBPF_NLA_U16,		/**< 16 bit पूर्णांकeger */
	LIBBPF_NLA_U32,		/**< 32 bit पूर्णांकeger */
	LIBBPF_NLA_U64,		/**< 64 bit पूर्णांकeger */
	LIBBPF_NLA_STRING,	/**< NUL terminated अक्षरacter string */
	LIBBPF_NLA_FLAG,	/**< Flag */
	LIBBPF_NLA_MSECS,	/**< Micro seconds (64bit) */
	LIBBPF_NLA_NESTED,	/**< Nested attributes */
	__LIBBPF_NLA_TYPE_MAX,
पूर्ण;

#घोषणा LIBBPF_NLA_TYPE_MAX (__LIBBPF_NLA_TYPE_MAX - 1)

/**
 * @ingroup attr
 * Attribute validation policy.
 *
 * See section @core_करोcअणुcore_attr_parse,Attribute Parsingपूर्ण क्रम more details.
 */
काष्ठा libbpf_nla_policy अणु
	/** Type of attribute or LIBBPF_NLA_UNSPEC */
	uपूर्णांक16_t	type;

	/** Minimal length of payload required */
	uपूर्णांक16_t	minlen;

	/** Maximal length of payload allowed */
	uपूर्णांक16_t	maxlen;
पूर्ण;

/**
 * @ingroup attr
 * Iterate over a stream of attributes
 * @arg pos	loop counter, set to current attribute
 * @arg head	head of attribute stream
 * @arg len	length of attribute stream
 * @arg rem	initialized to len, holds bytes currently reमुख्यing in stream
 */
#घोषणा libbpf_nla_क्रम_each_attr(pos, head, len, rem) \
	क्रम (pos = head, rem = len; \
	     nla_ok(pos, rem); \
	     pos = nla_next(pos, &(rem)))

/**
 * libbpf_nla_data - head of payload
 * @nla: netlink attribute
 */
अटल अंतरभूत व्योम *libbpf_nla_data(स्थिर काष्ठा nlattr *nla)
अणु
	वापस (अक्षर *) nla + NLA_HDRLEN;
पूर्ण

अटल अंतरभूत uपूर्णांक8_t libbpf_nla_getattr_u8(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(uपूर्णांक8_t *)libbpf_nla_data(nla);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t libbpf_nla_getattr_u32(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(uपूर्णांक32_t *)libbpf_nla_data(nla);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *libbpf_nla_getattr_str(स्थिर काष्ठा nlattr *nla)
अणु
	वापस (स्थिर अक्षर *)libbpf_nla_data(nla);
पूर्ण

/**
 * libbpf_nla_len - length of payload
 * @nla: netlink attribute
 */
अटल अंतरभूत पूर्णांक libbpf_nla_len(स्थिर काष्ठा nlattr *nla)
अणु
	वापस nla->nla_len - NLA_HDRLEN;
पूर्ण

पूर्णांक libbpf_nla_parse(काष्ठा nlattr *tb[], पूर्णांक maxtype, काष्ठा nlattr *head,
		     पूर्णांक len, काष्ठा libbpf_nla_policy *policy);
पूर्णांक libbpf_nla_parse_nested(काष्ठा nlattr *tb[], पूर्णांक maxtype,
			    काष्ठा nlattr *nla,
			    काष्ठा libbpf_nla_policy *policy);

पूर्णांक libbpf_nla_dump_errormsg(काष्ठा nlmsghdr *nlh);

#पूर्ण_अगर /* __LIBBPF_NLATTR_H */
