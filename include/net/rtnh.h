<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_RTNH_H
#घोषणा __NET_RTNH_H

#समावेश <linux/rtnetlink.h>
#समावेश <net/netlink.h>

अटल अंतरभूत पूर्णांक rtnh_ok(स्थिर काष्ठा rtnexthop *rtnh, पूर्णांक reमुख्यing)
अणु
	वापस reमुख्यing >= (पूर्णांक)माप(*rtnh) &&
	       rtnh->rtnh_len >= माप(*rtnh) &&
	       rtnh->rtnh_len <= reमुख्यing;
पूर्ण

अटल अंतरभूत काष्ठा rtnexthop *rtnh_next(स्थिर काष्ठा rtnexthop *rtnh,
                                         पूर्णांक *reमुख्यing)
अणु
	पूर्णांक totlen = NLA_ALIGN(rtnh->rtnh_len);

	*reमुख्यing -= totlen;
	वापस (काष्ठा rtnexthop *) ((अक्षर *) rtnh + totlen);
पूर्ण

अटल अंतरभूत काष्ठा nlattr *rtnh_attrs(स्थिर काष्ठा rtnexthop *rtnh)
अणु
	वापस (काष्ठा nlattr *) ((अक्षर *) rtnh + NLA_ALIGN(माप(*rtnh)));
पूर्ण

अटल अंतरभूत पूर्णांक rtnh_attrlen(स्थिर काष्ठा rtnexthop *rtnh)
अणु
	वापस rtnh->rtnh_len - NLA_ALIGN(माप(*rtnh));
पूर्ण

#पूर्ण_अगर
