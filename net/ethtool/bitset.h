<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित _NET_ETHTOOL_BITSET_H
#घोषणा _NET_ETHTOOL_BITSET_H

#घोषणा ETHNL_MAX_BITSET_SIZE S16_MAX

प्रकार स्थिर अक्षर (*स्थिर ethnl_string_array_t)[ETH_GSTRING_LEN];

पूर्णांक ethnl_bitset_is_compact(स्थिर काष्ठा nlattr *bitset, bool *compact);
पूर्णांक ethnl_bitset_size(स्थिर अचिन्हित दीर्घ *val, स्थिर अचिन्हित दीर्घ *mask,
		      अचिन्हित पूर्णांक nbits, ethnl_string_array_t names,
		      bool compact);
पूर्णांक ethnl_bitset32_size(स्थिर u32 *val, स्थिर u32 *mask, अचिन्हित पूर्णांक nbits,
			ethnl_string_array_t names, bool compact);
पूर्णांक ethnl_put_bitset(काष्ठा sk_buff *skb, पूर्णांक attrtype,
		     स्थिर अचिन्हित दीर्घ *val, स्थिर अचिन्हित दीर्घ *mask,
		     अचिन्हित पूर्णांक nbits, ethnl_string_array_t names,
		     bool compact);
पूर्णांक ethnl_put_bitset32(काष्ठा sk_buff *skb, पूर्णांक attrtype, स्थिर u32 *val,
		       स्थिर u32 *mask, अचिन्हित पूर्णांक nbits,
		       ethnl_string_array_t names, bool compact);
पूर्णांक ethnl_update_bitset(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक nbits,
			स्थिर काष्ठा nlattr *attr, ethnl_string_array_t names,
			काष्ठा netlink_ext_ack *extack, bool *mod);
पूर्णांक ethnl_update_bitset32(u32 *biपंचांगap, अचिन्हित पूर्णांक nbits,
			  स्थिर काष्ठा nlattr *attr, ethnl_string_array_t names,
			  काष्ठा netlink_ext_ack *extack, bool *mod);
पूर्णांक ethnl_parse_bitset(अचिन्हित दीर्घ *val, अचिन्हित दीर्घ *mask,
		       अचिन्हित पूर्णांक nbits, स्थिर काष्ठा nlattr *attr,
		       ethnl_string_array_t names,
		       काष्ठा netlink_ext_ack *extack);

#पूर्ण_अगर /* _NET_ETHTOOL_BITSET_H */
