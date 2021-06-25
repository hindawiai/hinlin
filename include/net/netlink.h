<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NET_NETLINK_H
#घोषणा __NET_NETLINK_H

#समावेश <linux/types.h>
#समावेश <linux/netlink.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/in6.h>

/* ========================================================================
 *         Netlink Messages and Attributes Interface (As Seen On TV)
 * ------------------------------------------------------------------------
 *                          Messages Interface
 * ------------------------------------------------------------------------
 *
 * Message Format:
 *    <--- nlmsg_total_size(payload)  --->
 *    <-- nlmsg_msg_size(payload) ->
 *   +----------+- - -+-------------+- - -+-------- - -
 *   | nlmsghdr | Pad |   Payload   | Pad | nlmsghdr
 *   +----------+- - -+-------------+- - -+-------- - -
 *   nlmsg_data(nlh)---^                   ^
 *   nlmsg_next(nlh)-----------------------+
 *
 * Payload Format:
 *    <---------------------- nlmsg_len(nlh) --------------------->
 *    <------ hdrlen ------>       <- nlmsg_attrlen(nlh, hdrlen) ->
 *   +----------------------+- - -+--------------------------------+
 *   |     Family Header    | Pad |           Attributes           |
 *   +----------------------+- - -+--------------------------------+
 *   nlmsg_attrdata(nlh, hdrlen)---^
 *
 * Data Structures:
 *   काष्ठा nlmsghdr			netlink message header
 *
 * Message Conकाष्ठाion:
 *   nlmsg_new()			create a new netlink message
 *   nlmsg_put()			add a netlink message to an skb
 *   nlmsg_put_answer()			callback based nlmsg_put()
 *   nlmsg_end()			finalize netlink message
 *   nlmsg_get_pos()			वापस current position in message
 *   nlmsg_trim()			trim part of message
 *   nlmsg_cancel()			cancel message स्थिरruction
 *   nlmsg_मुक्त()			मुक्त a netlink message
 *
 * Message Sending:
 *   nlmsg_multicast()			multicast message to several groups
 *   nlmsg_unicast()			unicast a message to a single socket
 *   nlmsg_notअगरy()			send notअगरication message
 *
 * Message Length Calculations:
 *   nlmsg_msg_size(payload)		length of message w/o padding
 *   nlmsg_total_size(payload)		length of message w/ padding
 *   nlmsg_padlen(payload)		length of padding at tail
 *
 * Message Payload Access:
 *   nlmsg_data(nlh)			head of message payload
 *   nlmsg_len(nlh)			length of message payload
 *   nlmsg_attrdata(nlh, hdrlen)	head of attributes data
 *   nlmsg_attrlen(nlh, hdrlen)		length of attributes data
 *
 * Message Parsing:
 *   nlmsg_ok(nlh, reमुख्यing)		करोes nlh fit पूर्णांकo reमुख्यing bytes?
 *   nlmsg_next(nlh, reमुख्यing)		get next netlink message
 *   nlmsg_parse()			parse attributes of a message
 *   nlmsg_find_attr()			find an attribute in a message
 *   nlmsg_क्रम_each_msg()		loop over all messages
 *   nlmsg_validate()			validate netlink message incl. attrs
 *   nlmsg_क्रम_each_attr()		loop over all attributes
 *
 * Misc:
 *   nlmsg_report()			report back to application?
 *
 * ------------------------------------------------------------------------
 *                          Attributes Interface
 * ------------------------------------------------------------------------
 *
 * Attribute Format:
 *    <------- nla_total_size(payload) ------->
 *    <---- nla_attr_size(payload) ----->
 *   +----------+- - -+- - - - - - - - - +- - -+-------- - -
 *   |  Header  | Pad |     Payload      | Pad |  Header
 *   +----------+- - -+- - - - - - - - - +- - -+-------- - -
 *                     <- nla_len(nla) ->      ^
 *   nla_data(nla)----^                        |
 *   nla_next(nla)-----------------------------'
 *
 * Data Structures:
 *   काष्ठा nlattr			netlink attribute header
 *
 * Attribute Conकाष्ठाion:
 *   nla_reserve(skb, type, len)	reserve room क्रम an attribute
 *   nla_reserve_nohdr(skb, len)	reserve room क्रम an attribute w/o hdr
 *   nla_put(skb, type, len, data)	add attribute to skb
 *   nla_put_nohdr(skb, len, data)	add attribute w/o hdr
 *   nla_append(skb, len, data)		append data to skb
 *
 * Attribute Conकाष्ठाion क्रम Basic Types:
 *   nla_put_u8(skb, type, value)	add u8 attribute to skb
 *   nla_put_u16(skb, type, value)	add u16 attribute to skb
 *   nla_put_u32(skb, type, value)	add u32 attribute to skb
 *   nla_put_u64_64bit(skb, type,
 *                     value, padattr)	add u64 attribute to skb
 *   nla_put_s8(skb, type, value)	add s8 attribute to skb
 *   nla_put_s16(skb, type, value)	add s16 attribute to skb
 *   nla_put_s32(skb, type, value)	add s32 attribute to skb
 *   nla_put_s64(skb, type, value,
 *               padattr)		add s64 attribute to skb
 *   nla_put_string(skb, type, str)	add string attribute to skb
 *   nla_put_flag(skb, type)		add flag attribute to skb
 *   nla_put_msecs(skb, type, jअगरfies,
 *                 padattr)		add msecs attribute to skb
 *   nla_put_in_addr(skb, type, addr)	add IPv4 address attribute to skb
 *   nla_put_in6_addr(skb, type, addr)	add IPv6 address attribute to skb
 *
 * Nested Attributes Conकाष्ठाion:
 *   nla_nest_start(skb, type)		start a nested attribute
 *   nla_nest_end(skb, nla)		finalize a nested attribute
 *   nla_nest_cancel(skb, nla)		cancel nested attribute स्थिरruction
 *
 * Attribute Length Calculations:
 *   nla_attr_size(payload)		length of attribute w/o padding
 *   nla_total_size(payload)		length of attribute w/ padding
 *   nla_padlen(payload)		length of padding
 *
 * Attribute Payload Access:
 *   nla_data(nla)			head of attribute payload
 *   nla_len(nla)			length of attribute payload
 *
 * Attribute Payload Access क्रम Basic Types:
 *   nla_get_u8(nla)			get payload क्रम a u8 attribute
 *   nla_get_u16(nla)			get payload क्रम a u16 attribute
 *   nla_get_u32(nla)			get payload क्रम a u32 attribute
 *   nla_get_u64(nla)			get payload क्रम a u64 attribute
 *   nla_get_s8(nla)			get payload क्रम a s8 attribute
 *   nla_get_s16(nla)			get payload क्रम a s16 attribute
 *   nla_get_s32(nla)			get payload क्रम a s32 attribute
 *   nla_get_s64(nla)			get payload क्रम a s64 attribute
 *   nla_get_flag(nla)			वापस 1 अगर flag is true
 *   nla_get_msecs(nla)			get payload क्रम a msecs attribute
 *
 * Attribute Misc:
 *   nla_स_नकल(dest, nla, count)	copy attribute पूर्णांकo memory
 *   nla_स_भेद(nla, data, size)	compare attribute with memory area
 *   nla_strscpy(dst, nla, size)	copy attribute to a sized string
 *   nla_म_भेद(nla, str)		compare attribute with string
 *
 * Attribute Parsing:
 *   nla_ok(nla, reमुख्यing)		करोes nla fit पूर्णांकo reमुख्यing bytes?
 *   nla_next(nla, reमुख्यing)		get next netlink attribute
 *   nla_validate()			validate a stream of attributes
 *   nla_validate_nested()		validate a stream of nested attributes
 *   nla_find()				find attribute in stream of attributes
 *   nla_find_nested()			find attribute in nested attributes
 *   nla_parse()			parse and validate stream of attrs
 *   nla_parse_nested()			parse nested attributes
 *   nla_क्रम_each_attr()		loop over all attributes
 *   nla_क्रम_each_nested()		loop over the nested attributes
 *=========================================================================
 */

 /**
  * Standard attribute types to specअगरy validation policy
  */
क्रमागत अणु
	NLA_UNSPEC,
	NLA_U8,
	NLA_U16,
	NLA_U32,
	NLA_U64,
	NLA_STRING,
	NLA_FLAG,
	NLA_MSECS,
	NLA_NESTED,
	NLA_NESTED_ARRAY,
	NLA_NUL_STRING,
	NLA_BINARY,
	NLA_S8,
	NLA_S16,
	NLA_S32,
	NLA_S64,
	NLA_BITFIELD32,
	NLA_REJECT,
	__NLA_TYPE_MAX,
पूर्ण;

#घोषणा NLA_TYPE_MAX (__NLA_TYPE_MAX - 1)

काष्ठा netlink_range_validation अणु
	u64 min, max;
पूर्ण;

काष्ठा netlink_range_validation_चिन्हित अणु
	s64 min, max;
पूर्ण;

क्रमागत nla_policy_validation अणु
	NLA_VALIDATE_NONE,
	NLA_VALIDATE_RANGE,
	NLA_VALIDATE_RANGE_WARN_TOO_LONG,
	NLA_VALIDATE_MIN,
	NLA_VALIDATE_MAX,
	NLA_VALIDATE_MASK,
	NLA_VALIDATE_RANGE_PTR,
	NLA_VALIDATE_FUNCTION,
पूर्ण;

/**
 * काष्ठा nla_policy - attribute validation policy
 * @type: Type of attribute or NLA_UNSPEC
 * @validation_type: type of attribute validation करोne in addition to
 *	type-specअगरic validation (e.g. range, function call), see
 *	&क्रमागत nla_policy_validation
 * @len: Type specअगरic length of payload
 *
 * Policies are defined as arrays of this काष्ठा, the array must be
 * accessible by attribute type up to the highest identअगरier to be expected.
 *
 * Meaning of `len' field:
 *    NLA_STRING           Maximum length of string
 *    NLA_NUL_STRING       Maximum length of string (excluding NUL)
 *    NLA_FLAG             Unused
 *    NLA_BINARY           Maximum length of attribute payload
 *                         (but see also below with the validation type)
 *    NLA_NESTED,
 *    NLA_NESTED_ARRAY     Length verअगरication is करोne by checking len of
 *                         nested header (or empty); len field is used अगर
 *                         nested_policy is also used, क्रम the max attr
 *                         number in the nested policy.
 *    NLA_U8, NLA_U16,
 *    NLA_U32, NLA_U64,
 *    NLA_S8, NLA_S16,
 *    NLA_S32, NLA_S64,
 *    NLA_MSECS            Leaving the length field zero will verअगरy the
 *                         given type fits, using it verअगरies minimum length
 *                         just like "All other"
 *    NLA_BITFIELD32       Unused
 *    NLA_REJECT           Unused
 *    All other            Minimum length of attribute payload
 *
 * Meaning of validation जोड़:
 *    NLA_BITFIELD32       This is a 32-bit biपंचांगap/bitselector attribute and
 *                         `bitfield32_valid' is the u32 value of valid flags
 *    NLA_REJECT           This attribute is always rejected and `reject_message'
 *                         may poपूर्णांक to a string to report as the error instead
 *                         of the generic one in extended ACK.
 *    NLA_NESTED           `nested_policy' to a nested policy to validate, must
 *                         also set `len' to the max attribute number. Use the
 *                         provided NLA_POLICY_NESTED() macro.
 *                         Note that nla_parse() will validate, but of course not
 *                         parse, the nested sub-policies.
 *    NLA_NESTED_ARRAY     `nested_policy' poपूर्णांकs to a nested policy to validate,
 *                         must also set `len' to the max attribute number. Use
 *                         the provided NLA_POLICY_NESTED_ARRAY() macro.
 *                         The dअगरference to NLA_NESTED is the काष्ठाure:
 *                         NLA_NESTED has the nested attributes directly inside
 *                         जबतक an array has the nested attributes at another
 *                         level करोwn and the attribute types directly in the
 *                         nesting करोn't matter.
 *    NLA_U8,
 *    NLA_U16,
 *    NLA_U32,
 *    NLA_U64,
 *    NLA_S8,
 *    NLA_S16,
 *    NLA_S32,
 *    NLA_S64              The `min' and `max' fields are used depending on the
 *                         validation_type field, अगर that is min/max/range then
 *                         the min, max or both are used (respectively) to check
 *                         the value of the पूर्णांकeger attribute.
 *                         Note that in the पूर्णांकerest of code simplicity and
 *                         काष्ठा size both limits are s16, so you cannot
 *                         enक्रमce a range that करोesn't fall within the range
 *                         of s16 - करो that as usual in the code instead.
 *                         Use the NLA_POLICY_MIN(), NLA_POLICY_MAX() and
 *                         NLA_POLICY_RANGE() macros.
 *    NLA_U8,
 *    NLA_U16,
 *    NLA_U32,
 *    NLA_U64              If the validation_type field instead is set to
 *                         NLA_VALIDATE_RANGE_PTR, `range' must be a poपूर्णांकer
 *                         to a काष्ठा netlink_range_validation that indicates
 *                         the min/max values.
 *                         Use NLA_POLICY_FULL_RANGE().
 *    NLA_S8,
 *    NLA_S16,
 *    NLA_S32,
 *    NLA_S64              If the validation_type field instead is set to
 *                         NLA_VALIDATE_RANGE_PTR, `range_चिन्हित' must be a
 *                         poपूर्णांकer to a काष्ठा netlink_range_validation_चिन्हित
 *                         that indicates the min/max values.
 *                         Use NLA_POLICY_FULL_RANGE_SIGNED().
 *
 *    NLA_BINARY           If the validation type is like the ones क्रम पूर्णांकegers
 *                         above, then the min/max length (not value like क्रम
 *                         पूर्णांकegers) of the attribute is enक्रमced.
 *
 *    All other            Unused - but note that it's a जोड़
 *
 * Meaning of `validate' field, use via NLA_POLICY_VALIDATE_FN:
 *    NLA_BINARY           Validation function called क्रम the attribute.
 *    All other            Unused - but note that it's a जोड़
 *
 * Example:
 *
 * अटल स्थिर u32 myvalidflags = 0xff231023;
 *
 * अटल स्थिर काष्ठा nla_policy my_policy[ATTR_MAX+1] = अणु
 * 	[ATTR_FOO] = अणु .type = NLA_U16 पूर्ण,
 *	[ATTR_BAR] = अणु .type = NLA_STRING, .len = BARSIZ पूर्ण,
 *	[ATTR_BAZ] = NLA_POLICY_EXACT_LEN(माप(काष्ठा myकाष्ठा)),
 *	[ATTR_GOO] = NLA_POLICY_BITFIELD32(myvalidflags),
 * पूर्ण;
 */
काष्ठा nla_policy अणु
	u8		type;
	u8		validation_type;
	u16		len;
	जोड़ अणु
		स्थिर u32 bitfield32_valid;
		स्थिर u32 mask;
		स्थिर अक्षर *reject_message;
		स्थिर काष्ठा nla_policy *nested_policy;
		काष्ठा netlink_range_validation *range;
		काष्ठा netlink_range_validation_चिन्हित *range_चिन्हित;
		काष्ठा अणु
			s16 min, max;
		पूर्ण;
		पूर्णांक (*validate)(स्थिर काष्ठा nlattr *attr,
				काष्ठा netlink_ext_ack *extack);
		/* This entry is special, and used क्रम the attribute at index 0
		 * only, and specअगरies special data about the policy, namely it
		 * specअगरies the "boundary type" where strict length validation
		 * starts क्रम any attribute types >= this value, also, strict
		 * nesting validation starts here.
		 *
		 * Additionally, it means that NLA_UNSPEC is actually NLA_REJECT
		 * क्रम any types >= this, so need to use NLA_POLICY_MIN_LEN() to
		 * get the previous pure अणु .len = xyz पूर्ण behaviour. The advantage
		 * of this is that types not specअगरied in the policy will be
		 * rejected.
		 *
		 * For completely new families it should be set to 1 so that the
		 * validation is enक्रमced क्रम all attributes. For existing ones
		 * it should be set at least when new attributes are added to
		 * the क्रमागत used by the policy, and be set to the new value that
		 * was added to enक्रमce strict validation from thereon.
		 */
		u16 strict_start_type;
	पूर्ण;
पूर्ण;

#घोषणा NLA_POLICY_ETH_ADDR		NLA_POLICY_EXACT_LEN(ETH_ALEN)
#घोषणा NLA_POLICY_ETH_ADDR_COMPAT	NLA_POLICY_EXACT_LEN_WARN(ETH_ALEN)

#घोषणा _NLA_POLICY_NESTED(maxattr, policy) \
	अणु .type = NLA_NESTED, .nested_policy = policy, .len = maxattr पूर्ण
#घोषणा _NLA_POLICY_NESTED_ARRAY(maxattr, policy) \
	अणु .type = NLA_NESTED_ARRAY, .nested_policy = policy, .len = maxattr पूर्ण
#घोषणा NLA_POLICY_NESTED(policy) \
	_NLA_POLICY_NESTED(ARRAY_SIZE(policy) - 1, policy)
#घोषणा NLA_POLICY_NESTED_ARRAY(policy) \
	_NLA_POLICY_NESTED_ARRAY(ARRAY_SIZE(policy) - 1, policy)
#घोषणा NLA_POLICY_BITFIELD32(valid) \
	अणु .type = NLA_BITFIELD32, .bitfield32_valid = valid पूर्ण

#घोषणा __NLA_IS_UINT_TYPE(tp)						\
	(tp == NLA_U8 || tp == NLA_U16 || tp == NLA_U32 || tp == NLA_U64)
#घोषणा __NLA_IS_SINT_TYPE(tp)						\
	(tp == NLA_S8 || tp == NLA_S16 || tp == NLA_S32 || tp == NLA_S64)

#घोषणा __NLA_ENSURE(condition) BUILD_BUG_ON_ZERO(!(condition))
#घोषणा NLA_ENSURE_UINT_TYPE(tp)			\
	(__NLA_ENSURE(__NLA_IS_UINT_TYPE(tp)) + tp)
#घोषणा NLA_ENSURE_UINT_OR_BINARY_TYPE(tp)		\
	(__NLA_ENSURE(__NLA_IS_UINT_TYPE(tp) ||	\
		      tp == NLA_MSECS ||		\
		      tp == NLA_BINARY) + tp)
#घोषणा NLA_ENSURE_SINT_TYPE(tp)			\
	(__NLA_ENSURE(__NLA_IS_SINT_TYPE(tp)) + tp)
#घोषणा NLA_ENSURE_INT_OR_BINARY_TYPE(tp)		\
	(__NLA_ENSURE(__NLA_IS_UINT_TYPE(tp) ||		\
		      __NLA_IS_SINT_TYPE(tp) ||		\
		      tp == NLA_MSECS ||		\
		      tp == NLA_BINARY) + tp)
#घोषणा NLA_ENSURE_NO_VALIDATION_PTR(tp)		\
	(__NLA_ENSURE(tp != NLA_BITFIELD32 &&		\
		      tp != NLA_REJECT &&		\
		      tp != NLA_NESTED &&		\
		      tp != NLA_NESTED_ARRAY) + tp)

#घोषणा NLA_POLICY_RANGE(tp, _min, _max) अणु		\
	.type = NLA_ENSURE_INT_OR_BINARY_TYPE(tp),	\
	.validation_type = NLA_VALIDATE_RANGE,		\
	.min = _min,					\
	.max = _max					\
पूर्ण

#घोषणा NLA_POLICY_FULL_RANGE(tp, _range) अणु		\
	.type = NLA_ENSURE_UINT_OR_BINARY_TYPE(tp),	\
	.validation_type = NLA_VALIDATE_RANGE_PTR,	\
	.range = _range,				\
पूर्ण

#घोषणा NLA_POLICY_FULL_RANGE_SIGNED(tp, _range) अणु	\
	.type = NLA_ENSURE_SINT_TYPE(tp),		\
	.validation_type = NLA_VALIDATE_RANGE_PTR,	\
	.range_चिन्हित = _range,				\
पूर्ण

#घोषणा NLA_POLICY_MIN(tp, _min) अणु			\
	.type = NLA_ENSURE_INT_OR_BINARY_TYPE(tp),	\
	.validation_type = NLA_VALIDATE_MIN,		\
	.min = _min,					\
पूर्ण

#घोषणा NLA_POLICY_MAX(tp, _max) अणु			\
	.type = NLA_ENSURE_INT_OR_BINARY_TYPE(tp),	\
	.validation_type = NLA_VALIDATE_MAX,		\
	.max = _max,					\
पूर्ण

#घोषणा NLA_POLICY_MASK(tp, _mask) अणु			\
	.type = NLA_ENSURE_UINT_TYPE(tp),		\
	.validation_type = NLA_VALIDATE_MASK,		\
	.mask = _mask,					\
पूर्ण

#घोषणा NLA_POLICY_VALIDATE_FN(tp, fn, ...) अणु		\
	.type = NLA_ENSURE_NO_VALIDATION_PTR(tp),	\
	.validation_type = NLA_VALIDATE_FUNCTION,	\
	.validate = fn,					\
	.len = __VA_ARGS__ + 0,				\
पूर्ण

#घोषणा NLA_POLICY_EXACT_LEN(_len)	NLA_POLICY_RANGE(NLA_BINARY, _len, _len)
#घोषणा NLA_POLICY_EXACT_LEN_WARN(_len) अणु			\
	.type = NLA_BINARY,					\
	.validation_type = NLA_VALIDATE_RANGE_WARN_TOO_LONG,	\
	.min = _len,						\
	.max = _len						\
पूर्ण
#घोषणा NLA_POLICY_MIN_LEN(_len)	NLA_POLICY_MIN(NLA_BINARY, _len)

/**
 * काष्ठा nl_info - netlink source inक्रमmation
 * @nlh: Netlink message header of original request
 * @nl_net: Network namespace
 * @portid: Netlink PORTID of requesting application
 * @skip_notअगरy: Skip netlink notअगरications to user space
 * @skip_notअगरy_kernel: Skip selected in-kernel notअगरications
 */
काष्ठा nl_info अणु
	काष्ठा nlmsghdr		*nlh;
	काष्ठा net		*nl_net;
	u32			portid;
	u8			skip_notअगरy:1,
				skip_notअगरy_kernel:1;
पूर्ण;

/**
 * क्रमागत netlink_validation - netlink message/attribute validation levels
 * @NL_VALIDATE_LIBERAL: Old-style "be liberal" validation, not caring about
 *	extra data at the end of the message, attributes being दीर्घer than
 *	they should be, or unknown attributes being present.
 * @NL_VALIDATE_TRAILING: Reject junk data encountered after attribute parsing.
 * @NL_VALIDATE_MAXTYPE: Reject attributes > max type; Together with _TRAILING
 *	this is equivalent to the old nla_parse_strict()/nlmsg_parse_strict().
 * @NL_VALIDATE_UNSPEC: Reject attributes with NLA_UNSPEC in the policy.
 *	This can safely be set by the kernel when the given policy has no
 *	NLA_UNSPEC anymore, and can thus be used to ensure policy entries
 *	are enक्रमced going क्रमward.
 * @NL_VALIDATE_STRICT_ATTRS: strict attribute policy parsing (e.g.
 *	U8, U16, U32 must have exact size, etc.)
 * @NL_VALIDATE_NESTED: Check that NLA_F_NESTED is set क्रम NLA_NESTED(_ARRAY)
 *	and unset क्रम other policies.
 */
क्रमागत netlink_validation अणु
	NL_VALIDATE_LIBERAL = 0,
	NL_VALIDATE_TRAILING = BIT(0),
	NL_VALIDATE_MAXTYPE = BIT(1),
	NL_VALIDATE_UNSPEC = BIT(2),
	NL_VALIDATE_STRICT_ATTRS = BIT(3),
	NL_VALIDATE_NESTED = BIT(4),
पूर्ण;

#घोषणा NL_VALIDATE_DEPRECATED_STRICT (NL_VALIDATE_TRAILING |\
				       NL_VALIDATE_MAXTYPE)
#घोषणा NL_VALIDATE_STRICT (NL_VALIDATE_TRAILING |\
			    NL_VALIDATE_MAXTYPE |\
			    NL_VALIDATE_UNSPEC |\
			    NL_VALIDATE_STRICT_ATTRS |\
			    NL_VALIDATE_NESTED)

पूर्णांक netlink_rcv_skb(काष्ठा sk_buff *skb,
		    पूर्णांक (*cb)(काष्ठा sk_buff *, काष्ठा nlmsghdr *,
			      काष्ठा netlink_ext_ack *));
पूर्णांक nlmsg_notअगरy(काष्ठा sock *sk, काष्ठा sk_buff *skb, u32 portid,
		 अचिन्हित पूर्णांक group, पूर्णांक report, gfp_t flags);

पूर्णांक __nla_validate(स्थिर काष्ठा nlattr *head, पूर्णांक len, पूर्णांक maxtype,
		   स्थिर काष्ठा nla_policy *policy, अचिन्हित पूर्णांक validate,
		   काष्ठा netlink_ext_ack *extack);
पूर्णांक __nla_parse(काष्ठा nlattr **tb, पूर्णांक maxtype, स्थिर काष्ठा nlattr *head,
		पूर्णांक len, स्थिर काष्ठा nla_policy *policy, अचिन्हित पूर्णांक validate,
		काष्ठा netlink_ext_ack *extack);
पूर्णांक nla_policy_len(स्थिर काष्ठा nla_policy *, पूर्णांक);
काष्ठा nlattr *nla_find(स्थिर काष्ठा nlattr *head, पूर्णांक len, पूर्णांक attrtype);
sमाप_प्रकार nla_strscpy(अक्षर *dst, स्थिर काष्ठा nlattr *nla, माप_प्रकार dstsize);
अक्षर *nla_strdup(स्थिर काष्ठा nlattr *nla, gfp_t flags);
पूर्णांक nla_स_नकल(व्योम *dest, स्थिर काष्ठा nlattr *src, पूर्णांक count);
पूर्णांक nla_स_भेद(स्थिर काष्ठा nlattr *nla, स्थिर व्योम *data, माप_प्रकार size);
पूर्णांक nla_म_भेद(स्थिर काष्ठा nlattr *nla, स्थिर अक्षर *str);
काष्ठा nlattr *__nla_reserve(काष्ठा sk_buff *skb, पूर्णांक attrtype, पूर्णांक attrlen);
काष्ठा nlattr *__nla_reserve_64bit(काष्ठा sk_buff *skb, पूर्णांक attrtype,
				   पूर्णांक attrlen, पूर्णांक padattr);
व्योम *__nla_reserve_nohdr(काष्ठा sk_buff *skb, पूर्णांक attrlen);
काष्ठा nlattr *nla_reserve(काष्ठा sk_buff *skb, पूर्णांक attrtype, पूर्णांक attrlen);
काष्ठा nlattr *nla_reserve_64bit(काष्ठा sk_buff *skb, पूर्णांक attrtype,
				 पूर्णांक attrlen, पूर्णांक padattr);
व्योम *nla_reserve_nohdr(काष्ठा sk_buff *skb, पूर्णांक attrlen);
व्योम __nla_put(काष्ठा sk_buff *skb, पूर्णांक attrtype, पूर्णांक attrlen,
	       स्थिर व्योम *data);
व्योम __nla_put_64bit(काष्ठा sk_buff *skb, पूर्णांक attrtype, पूर्णांक attrlen,
		     स्थिर व्योम *data, पूर्णांक padattr);
व्योम __nla_put_nohdr(काष्ठा sk_buff *skb, पूर्णांक attrlen, स्थिर व्योम *data);
पूर्णांक nla_put(काष्ठा sk_buff *skb, पूर्णांक attrtype, पूर्णांक attrlen, स्थिर व्योम *data);
पूर्णांक nla_put_64bit(काष्ठा sk_buff *skb, पूर्णांक attrtype, पूर्णांक attrlen,
		  स्थिर व्योम *data, पूर्णांक padattr);
पूर्णांक nla_put_nohdr(काष्ठा sk_buff *skb, पूर्णांक attrlen, स्थिर व्योम *data);
पूर्णांक nla_append(काष्ठा sk_buff *skb, पूर्णांक attrlen, स्थिर व्योम *data);

/**************************************************************************
 * Netlink Messages
 **************************************************************************/

/**
 * nlmsg_msg_size - length of netlink message not including padding
 * @payload: length of message payload
 */
अटल अंतरभूत पूर्णांक nlmsg_msg_size(पूर्णांक payload)
अणु
	वापस NLMSG_HDRLEN + payload;
पूर्ण

/**
 * nlmsg_total_size - length of netlink message including padding
 * @payload: length of message payload
 */
अटल अंतरभूत पूर्णांक nlmsg_total_size(पूर्णांक payload)
अणु
	वापस NLMSG_ALIGN(nlmsg_msg_size(payload));
पूर्ण

/**
 * nlmsg_padlen - length of padding at the message's tail
 * @payload: length of message payload
 */
अटल अंतरभूत पूर्णांक nlmsg_padlen(पूर्णांक payload)
अणु
	वापस nlmsg_total_size(payload) - nlmsg_msg_size(payload);
पूर्ण

/**
 * nlmsg_data - head of message payload
 * @nlh: netlink message header
 */
अटल अंतरभूत व्योम *nlmsg_data(स्थिर काष्ठा nlmsghdr *nlh)
अणु
	वापस (अचिन्हित अक्षर *) nlh + NLMSG_HDRLEN;
पूर्ण

/**
 * nlmsg_len - length of message payload
 * @nlh: netlink message header
 */
अटल अंतरभूत पूर्णांक nlmsg_len(स्थिर काष्ठा nlmsghdr *nlh)
अणु
	वापस nlh->nlmsg_len - NLMSG_HDRLEN;
पूर्ण

/**
 * nlmsg_attrdata - head of attributes data
 * @nlh: netlink message header
 * @hdrlen: length of family specअगरic header
 */
अटल अंतरभूत काष्ठा nlattr *nlmsg_attrdata(स्थिर काष्ठा nlmsghdr *nlh,
					    पूर्णांक hdrlen)
अणु
	अचिन्हित अक्षर *data = nlmsg_data(nlh);
	वापस (काष्ठा nlattr *) (data + NLMSG_ALIGN(hdrlen));
पूर्ण

/**
 * nlmsg_attrlen - length of attributes data
 * @nlh: netlink message header
 * @hdrlen: length of family specअगरic header
 */
अटल अंतरभूत पूर्णांक nlmsg_attrlen(स्थिर काष्ठा nlmsghdr *nlh, पूर्णांक hdrlen)
अणु
	वापस nlmsg_len(nlh) - NLMSG_ALIGN(hdrlen);
पूर्ण

/**
 * nlmsg_ok - check अगर the netlink message fits पूर्णांकo the reमुख्यing bytes
 * @nlh: netlink message header
 * @reमुख्यing: number of bytes reमुख्यing in message stream
 */
अटल अंतरभूत पूर्णांक nlmsg_ok(स्थिर काष्ठा nlmsghdr *nlh, पूर्णांक reमुख्यing)
अणु
	वापस (reमुख्यing >= (पूर्णांक) माप(काष्ठा nlmsghdr) &&
		nlh->nlmsg_len >= माप(काष्ठा nlmsghdr) &&
		nlh->nlmsg_len <= reमुख्यing);
पूर्ण

/**
 * nlmsg_next - next netlink message in message stream
 * @nlh: netlink message header
 * @reमुख्यing: number of bytes reमुख्यing in message stream
 *
 * Returns the next netlink message in the message stream and
 * decrements reमुख्यing by the size of the current message.
 */
अटल अंतरभूत काष्ठा nlmsghdr *
nlmsg_next(स्थिर काष्ठा nlmsghdr *nlh, पूर्णांक *reमुख्यing)
अणु
	पूर्णांक totlen = NLMSG_ALIGN(nlh->nlmsg_len);

	*reमुख्यing -= totlen;

	वापस (काष्ठा nlmsghdr *) ((अचिन्हित अक्षर *) nlh + totlen);
पूर्ण

/**
 * nla_parse - Parse a stream of attributes पूर्णांकo a tb buffer
 * @tb: destination array with maxtype+1 elements
 * @maxtype: maximum attribute type to be expected
 * @head: head of attribute stream
 * @len: length of attribute stream
 * @policy: validation policy
 * @extack: extended ACK poपूर्णांकer
 *
 * Parses a stream of attributes and stores a poपूर्णांकer to each attribute in
 * the tb array accessible via the attribute type. Attributes with a type
 * exceeding maxtype will be rejected, policy must be specअगरied, attributes
 * will be validated in the strictest way possible.
 *
 * Returns 0 on success or a negative error code.
 */
अटल अंतरभूत पूर्णांक nla_parse(काष्ठा nlattr **tb, पूर्णांक maxtype,
			    स्थिर काष्ठा nlattr *head, पूर्णांक len,
			    स्थिर काष्ठा nla_policy *policy,
			    काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nla_parse(tb, maxtype, head, len, policy,
			   NL_VALIDATE_STRICT, extack);
पूर्ण

/**
 * nla_parse_deprecated - Parse a stream of attributes पूर्णांकo a tb buffer
 * @tb: destination array with maxtype+1 elements
 * @maxtype: maximum attribute type to be expected
 * @head: head of attribute stream
 * @len: length of attribute stream
 * @policy: validation policy
 * @extack: extended ACK poपूर्णांकer
 *
 * Parses a stream of attributes and stores a poपूर्णांकer to each attribute in
 * the tb array accessible via the attribute type. Attributes with a type
 * exceeding maxtype will be ignored and attributes from the policy are not
 * always strictly validated (only क्रम new attributes).
 *
 * Returns 0 on success or a negative error code.
 */
अटल अंतरभूत पूर्णांक nla_parse_deprecated(काष्ठा nlattr **tb, पूर्णांक maxtype,
				       स्थिर काष्ठा nlattr *head, पूर्णांक len,
				       स्थिर काष्ठा nla_policy *policy,
				       काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nla_parse(tb, maxtype, head, len, policy,
			   NL_VALIDATE_LIBERAL, extack);
पूर्ण

/**
 * nla_parse_deprecated_strict - Parse a stream of attributes पूर्णांकo a tb buffer
 * @tb: destination array with maxtype+1 elements
 * @maxtype: maximum attribute type to be expected
 * @head: head of attribute stream
 * @len: length of attribute stream
 * @policy: validation policy
 * @extack: extended ACK poपूर्णांकer
 *
 * Parses a stream of attributes and stores a poपूर्णांकer to each attribute in
 * the tb array accessible via the attribute type. Attributes with a type
 * exceeding maxtype will be rejected as well as trailing data, but the
 * policy is not completely strictly validated (only क्रम new attributes).
 *
 * Returns 0 on success or a negative error code.
 */
अटल अंतरभूत पूर्णांक nla_parse_deprecated_strict(काष्ठा nlattr **tb, पूर्णांक maxtype,
					      स्थिर काष्ठा nlattr *head,
					      पूर्णांक len,
					      स्थिर काष्ठा nla_policy *policy,
					      काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nla_parse(tb, maxtype, head, len, policy,
			   NL_VALIDATE_DEPRECATED_STRICT, extack);
पूर्ण

/**
 * __nlmsg_parse - parse attributes of a netlink message
 * @nlh: netlink message header
 * @hdrlen: length of family specअगरic header
 * @tb: destination array with maxtype+1 elements
 * @maxtype: maximum attribute type to be expected
 * @policy: validation policy
 * @validate: validation strictness
 * @extack: extended ACK report काष्ठा
 *
 * See nla_parse()
 */
अटल अंतरभूत पूर्णांक __nlmsg_parse(स्थिर काष्ठा nlmsghdr *nlh, पूर्णांक hdrlen,
				काष्ठा nlattr *tb[], पूर्णांक maxtype,
				स्थिर काष्ठा nla_policy *policy,
				अचिन्हित पूर्णांक validate,
				काष्ठा netlink_ext_ack *extack)
अणु
	अगर (nlh->nlmsg_len < nlmsg_msg_size(hdrlen)) अणु
		NL_SET_ERR_MSG(extack, "Invalid header length");
		वापस -EINVAL;
	पूर्ण

	वापस __nla_parse(tb, maxtype, nlmsg_attrdata(nlh, hdrlen),
			   nlmsg_attrlen(nlh, hdrlen), policy, validate,
			   extack);
पूर्ण

/**
 * nlmsg_parse - parse attributes of a netlink message
 * @nlh: netlink message header
 * @hdrlen: length of family specअगरic header
 * @tb: destination array with maxtype+1 elements
 * @maxtype: maximum attribute type to be expected
 * @extack: extended ACK report काष्ठा
 *
 * See nla_parse()
 */
अटल अंतरभूत पूर्णांक nlmsg_parse(स्थिर काष्ठा nlmsghdr *nlh, पूर्णांक hdrlen,
			      काष्ठा nlattr *tb[], पूर्णांक maxtype,
			      स्थिर काष्ठा nla_policy *policy,
			      काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nlmsg_parse(nlh, hdrlen, tb, maxtype, policy,
			     NL_VALIDATE_STRICT, extack);
पूर्ण

/**
 * nlmsg_parse_deprecated - parse attributes of a netlink message
 * @nlh: netlink message header
 * @hdrlen: length of family specअगरic header
 * @tb: destination array with maxtype+1 elements
 * @maxtype: maximum attribute type to be expected
 * @extack: extended ACK report काष्ठा
 *
 * See nla_parse_deprecated()
 */
अटल अंतरभूत पूर्णांक nlmsg_parse_deprecated(स्थिर काष्ठा nlmsghdr *nlh, पूर्णांक hdrlen,
					 काष्ठा nlattr *tb[], पूर्णांक maxtype,
					 स्थिर काष्ठा nla_policy *policy,
					 काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nlmsg_parse(nlh, hdrlen, tb, maxtype, policy,
			     NL_VALIDATE_LIBERAL, extack);
पूर्ण

/**
 * nlmsg_parse_deprecated_strict - parse attributes of a netlink message
 * @nlh: netlink message header
 * @hdrlen: length of family specअगरic header
 * @tb: destination array with maxtype+1 elements
 * @maxtype: maximum attribute type to be expected
 * @extack: extended ACK report काष्ठा
 *
 * See nla_parse_deprecated_strict()
 */
अटल अंतरभूत पूर्णांक
nlmsg_parse_deprecated_strict(स्थिर काष्ठा nlmsghdr *nlh, पूर्णांक hdrlen,
			      काष्ठा nlattr *tb[], पूर्णांक maxtype,
			      स्थिर काष्ठा nla_policy *policy,
			      काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nlmsg_parse(nlh, hdrlen, tb, maxtype, policy,
			     NL_VALIDATE_DEPRECATED_STRICT, extack);
पूर्ण

/**
 * nlmsg_find_attr - find a specअगरic attribute in a netlink message
 * @nlh: netlink message header
 * @hdrlen: length of familiy specअगरic header
 * @attrtype: type of attribute to look क्रम
 *
 * Returns the first attribute which matches the specअगरied type.
 */
अटल अंतरभूत काष्ठा nlattr *nlmsg_find_attr(स्थिर काष्ठा nlmsghdr *nlh,
					     पूर्णांक hdrlen, पूर्णांक attrtype)
अणु
	वापस nla_find(nlmsg_attrdata(nlh, hdrlen),
			nlmsg_attrlen(nlh, hdrlen), attrtype);
पूर्ण

/**
 * nla_validate_deprecated - Validate a stream of attributes
 * @head: head of attribute stream
 * @len: length of attribute stream
 * @maxtype: maximum attribute type to be expected
 * @policy: validation policy
 * @validate: validation strictness
 * @extack: extended ACK report काष्ठा
 *
 * Validates all attributes in the specअगरied attribute stream against the
 * specअगरied policy. Validation is करोne in liberal mode.
 * See करोcumenation of काष्ठा nla_policy क्रम more details.
 *
 * Returns 0 on success or a negative error code.
 */
अटल अंतरभूत पूर्णांक nla_validate_deprecated(स्थिर काष्ठा nlattr *head, पूर्णांक len,
					  पूर्णांक maxtype,
					  स्थिर काष्ठा nla_policy *policy,
					  काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nla_validate(head, len, maxtype, policy, NL_VALIDATE_LIBERAL,
			      extack);
पूर्ण

/**
 * nla_validate - Validate a stream of attributes
 * @head: head of attribute stream
 * @len: length of attribute stream
 * @maxtype: maximum attribute type to be expected
 * @policy: validation policy
 * @extack: extended ACK report काष्ठा
 *
 * Validates all attributes in the specअगरied attribute stream against the
 * specअगरied policy. Validation is करोne in strict mode.
 * See करोcumenation of काष्ठा nla_policy क्रम more details.
 *
 * Returns 0 on success or a negative error code.
 */
अटल अंतरभूत पूर्णांक nla_validate(स्थिर काष्ठा nlattr *head, पूर्णांक len, पूर्णांक maxtype,
			       स्थिर काष्ठा nla_policy *policy,
			       काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nla_validate(head, len, maxtype, policy, NL_VALIDATE_STRICT,
			      extack);
पूर्ण

/**
 * nlmsg_validate_deprecated - validate a netlink message including attributes
 * @nlh: netlinket message header
 * @hdrlen: length of familiy specअगरic header
 * @maxtype: maximum attribute type to be expected
 * @policy: validation policy
 * @extack: extended ACK report काष्ठा
 */
अटल अंतरभूत पूर्णांक nlmsg_validate_deprecated(स्थिर काष्ठा nlmsghdr *nlh,
					    पूर्णांक hdrlen, पूर्णांक maxtype,
					    स्थिर काष्ठा nla_policy *policy,
					    काष्ठा netlink_ext_ack *extack)
अणु
	अगर (nlh->nlmsg_len < nlmsg_msg_size(hdrlen))
		वापस -EINVAL;

	वापस __nla_validate(nlmsg_attrdata(nlh, hdrlen),
			      nlmsg_attrlen(nlh, hdrlen), maxtype,
			      policy, NL_VALIDATE_LIBERAL, extack);
पूर्ण



/**
 * nlmsg_report - need to report back to application?
 * @nlh: netlink message header
 *
 * Returns 1 अगर a report back to the application is requested.
 */
अटल अंतरभूत पूर्णांक nlmsg_report(स्थिर काष्ठा nlmsghdr *nlh)
अणु
	वापस !!(nlh->nlmsg_flags & NLM_F_ECHO);
पूर्ण

/**
 * nlmsg_क्रम_each_attr - iterate over a stream of attributes
 * @pos: loop counter, set to current attribute
 * @nlh: netlink message header
 * @hdrlen: length of familiy specअगरic header
 * @rem: initialized to len, holds bytes currently reमुख्यing in stream
 */
#घोषणा nlmsg_क्रम_each_attr(pos, nlh, hdrlen, rem) \
	nla_क्रम_each_attr(pos, nlmsg_attrdata(nlh, hdrlen), \
			  nlmsg_attrlen(nlh, hdrlen), rem)

/**
 * nlmsg_put - Add a new netlink message to an skb
 * @skb: socket buffer to store message in
 * @portid: netlink PORTID of requesting application
 * @seq: sequence number of message
 * @type: message type
 * @payload: length of message payload
 * @flags: message flags
 *
 * Returns शून्य अगर the tailroom of the skb is insufficient to store
 * the message header and payload.
 */
अटल अंतरभूत काष्ठा nlmsghdr *nlmsg_put(काष्ठा sk_buff *skb, u32 portid, u32 seq,
					 पूर्णांक type, पूर्णांक payload, पूर्णांक flags)
अणु
	अगर (unlikely(skb_tailroom(skb) < nlmsg_total_size(payload)))
		वापस शून्य;

	वापस __nlmsg_put(skb, portid, seq, type, payload, flags);
पूर्ण

/**
 * nlmsg_put_answer - Add a new callback based netlink message to an skb
 * @skb: socket buffer to store message in
 * @cb: netlink callback
 * @type: message type
 * @payload: length of message payload
 * @flags: message flags
 *
 * Returns शून्य अगर the tailroom of the skb is insufficient to store
 * the message header and payload.
 */
अटल अंतरभूत काष्ठा nlmsghdr *nlmsg_put_answer(काष्ठा sk_buff *skb,
						काष्ठा netlink_callback *cb,
						पूर्णांक type, पूर्णांक payload,
						पूर्णांक flags)
अणु
	वापस nlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			 type, payload, flags);
पूर्ण

/**
 * nlmsg_new - Allocate a new netlink message
 * @payload: size of the message payload
 * @flags: the type of memory to allocate.
 *
 * Use NLMSG_DEFAULT_SIZE अगर the size of the payload isn't known
 * and a good शेष is needed.
 */
अटल अंतरभूत काष्ठा sk_buff *nlmsg_new(माप_प्रकार payload, gfp_t flags)
अणु
	वापस alloc_skb(nlmsg_total_size(payload), flags);
पूर्ण

/**
 * nlmsg_end - Finalize a netlink message
 * @skb: socket buffer the message is stored in
 * @nlh: netlink message header
 *
 * Corrects the netlink message header to include the appeneded
 * attributes. Only necessary अगर attributes have been added to
 * the message.
 */
अटल अंतरभूत व्योम nlmsg_end(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh)
अणु
	nlh->nlmsg_len = skb_tail_poपूर्णांकer(skb) - (अचिन्हित अक्षर *)nlh;
पूर्ण

/**
 * nlmsg_get_pos - वापस current position in netlink message
 * @skb: socket buffer the message is stored in
 *
 * Returns a poपूर्णांकer to the current tail of the message.
 */
अटल अंतरभूत व्योम *nlmsg_get_pos(काष्ठा sk_buff *skb)
अणु
	वापस skb_tail_poपूर्णांकer(skb);
पूर्ण

/**
 * nlmsg_trim - Trim message to a mark
 * @skb: socket buffer the message is stored in
 * @mark: mark to trim to
 *
 * Trims the message to the provided mark.
 */
अटल अंतरभूत व्योम nlmsg_trim(काष्ठा sk_buff *skb, स्थिर व्योम *mark)
अणु
	अगर (mark) अणु
		WARN_ON((अचिन्हित अक्षर *) mark < skb->data);
		skb_trim(skb, (अचिन्हित अक्षर *) mark - skb->data);
	पूर्ण
पूर्ण

/**
 * nlmsg_cancel - Cancel स्थिरruction of a netlink message
 * @skb: socket buffer the message is stored in
 * @nlh: netlink message header
 *
 * Removes the complete netlink message including all
 * attributes from the socket buffer again.
 */
अटल अंतरभूत व्योम nlmsg_cancel(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh)
अणु
	nlmsg_trim(skb, nlh);
पूर्ण

/**
 * nlmsg_मुक्त - मुक्त a netlink message
 * @skb: socket buffer of netlink message
 */
अटल अंतरभूत व्योम nlmsg_मुक्त(काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
पूर्ण

/**
 * nlmsg_multicast - multicast a netlink message
 * @sk: netlink socket to spपढ़ो messages to
 * @skb: netlink message as socket buffer
 * @portid: own netlink portid to aव्योम sending to yourself
 * @group: multicast group id
 * @flags: allocation flags
 */
अटल अंतरभूत पूर्णांक nlmsg_multicast(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				  u32 portid, अचिन्हित पूर्णांक group, gfp_t flags)
अणु
	पूर्णांक err;

	NETLINK_CB(skb).dst_group = group;

	err = netlink_broadcast(sk, skb, portid, group, flags);
	अगर (err > 0)
		err = 0;

	वापस err;
पूर्ण

/**
 * nlmsg_unicast - unicast a netlink message
 * @sk: netlink socket to spपढ़ो message to
 * @skb: netlink message as socket buffer
 * @portid: netlink portid of the destination socket
 */
अटल अंतरभूत पूर्णांक nlmsg_unicast(काष्ठा sock *sk, काष्ठा sk_buff *skb, u32 portid)
अणु
	पूर्णांक err;

	err = netlink_unicast(sk, skb, portid, MSG_DONTWAIT);
	अगर (err > 0)
		err = 0;

	वापस err;
पूर्ण

/**
 * nlmsg_क्रम_each_msg - iterate over a stream of messages
 * @pos: loop counter, set to current message
 * @head: head of message stream
 * @len: length of message stream
 * @rem: initialized to len, holds bytes currently reमुख्यing in stream
 */
#घोषणा nlmsg_क्रम_each_msg(pos, head, len, rem) \
	क्रम (pos = head, rem = len; \
	     nlmsg_ok(pos, rem); \
	     pos = nlmsg_next(pos, &(rem)))

/**
 * nl_dump_check_consistent - check अगर sequence is consistent and advertise अगर not
 * @cb: netlink callback काष्ठाure that stores the sequence number
 * @nlh: netlink message header to ग_लिखो the flag to
 *
 * This function checks अगर the sequence (generation) number changed during dump
 * and अगर it did, advertises it in the netlink message header.
 *
 * The correct way to use it is to set cb->seq to the generation counter when
 * all locks क्रम dumping have been acquired, and then call this function क्रम
 * each message that is generated.
 *
 * Note that due to initialisation concerns, 0 is an invalid sequence number
 * and must not be used by code that uses this functionality.
 */
अटल अंतरभूत व्योम
nl_dump_check_consistent(काष्ठा netlink_callback *cb,
			 काष्ठा nlmsghdr *nlh)
अणु
	अगर (cb->prev_seq && cb->seq != cb->prev_seq)
		nlh->nlmsg_flags |= NLM_F_DUMP_INTR;
	cb->prev_seq = cb->seq;
पूर्ण

/**************************************************************************
 * Netlink Attributes
 **************************************************************************/

/**
 * nla_attr_size - length of attribute not including padding
 * @payload: length of payload
 */
अटल अंतरभूत पूर्णांक nla_attr_size(पूर्णांक payload)
अणु
	वापस NLA_HDRLEN + payload;
पूर्ण

/**
 * nla_total_size - total length of attribute including padding
 * @payload: length of payload
 */
अटल अंतरभूत पूर्णांक nla_total_size(पूर्णांक payload)
अणु
	वापस NLA_ALIGN(nla_attr_size(payload));
पूर्ण

/**
 * nla_padlen - length of padding at the tail of attribute
 * @payload: length of payload
 */
अटल अंतरभूत पूर्णांक nla_padlen(पूर्णांक payload)
अणु
	वापस nla_total_size(payload) - nla_attr_size(payload);
पूर्ण

/**
 * nla_type - attribute type
 * @nla: netlink attribute
 */
अटल अंतरभूत पूर्णांक nla_type(स्थिर काष्ठा nlattr *nla)
अणु
	वापस nla->nla_type & NLA_TYPE_MASK;
पूर्ण

/**
 * nla_data - head of payload
 * @nla: netlink attribute
 */
अटल अंतरभूत व्योम *nla_data(स्थिर काष्ठा nlattr *nla)
अणु
	वापस (अक्षर *) nla + NLA_HDRLEN;
पूर्ण

/**
 * nla_len - length of payload
 * @nla: netlink attribute
 */
अटल अंतरभूत पूर्णांक nla_len(स्थिर काष्ठा nlattr *nla)
अणु
	वापस nla->nla_len - NLA_HDRLEN;
पूर्ण

/**
 * nla_ok - check अगर the netlink attribute fits पूर्णांकo the reमुख्यing bytes
 * @nla: netlink attribute
 * @reमुख्यing: number of bytes reमुख्यing in attribute stream
 */
अटल अंतरभूत पूर्णांक nla_ok(स्थिर काष्ठा nlattr *nla, पूर्णांक reमुख्यing)
अणु
	वापस reमुख्यing >= (पूर्णांक) माप(*nla) &&
	       nla->nla_len >= माप(*nla) &&
	       nla->nla_len <= reमुख्यing;
पूर्ण

/**
 * nla_next - next netlink attribute in attribute stream
 * @nla: netlink attribute
 * @reमुख्यing: number of bytes reमुख्यing in attribute stream
 *
 * Returns the next netlink attribute in the attribute stream and
 * decrements reमुख्यing by the size of the current attribute.
 */
अटल अंतरभूत काष्ठा nlattr *nla_next(स्थिर काष्ठा nlattr *nla, पूर्णांक *reमुख्यing)
अणु
	अचिन्हित पूर्णांक totlen = NLA_ALIGN(nla->nla_len);

	*reमुख्यing -= totlen;
	वापस (काष्ठा nlattr *) ((अक्षर *) nla + totlen);
पूर्ण

/**
 * nla_find_nested - find attribute in a set of nested attributes
 * @nla: attribute containing the nested attributes
 * @attrtype: type of attribute to look क्रम
 *
 * Returns the first attribute which matches the specअगरied type.
 */
अटल अंतरभूत काष्ठा nlattr *
nla_find_nested(स्थिर काष्ठा nlattr *nla, पूर्णांक attrtype)
अणु
	वापस nla_find(nla_data(nla), nla_len(nla), attrtype);
पूर्ण

/**
 * nla_parse_nested - parse nested attributes
 * @tb: destination array with maxtype+1 elements
 * @maxtype: maximum attribute type to be expected
 * @nla: attribute containing the nested attributes
 * @policy: validation policy
 * @extack: extended ACK report काष्ठा
 *
 * See nla_parse()
 */
अटल अंतरभूत पूर्णांक nla_parse_nested(काष्ठा nlattr *tb[], पूर्णांक maxtype,
				   स्थिर काष्ठा nlattr *nla,
				   स्थिर काष्ठा nla_policy *policy,
				   काष्ठा netlink_ext_ack *extack)
अणु
	अगर (!(nla->nla_type & NLA_F_NESTED)) अणु
		NL_SET_ERR_MSG_ATTR(extack, nla, "NLA_F_NESTED is missing");
		वापस -EINVAL;
	पूर्ण

	वापस __nla_parse(tb, maxtype, nla_data(nla), nla_len(nla), policy,
			   NL_VALIDATE_STRICT, extack);
पूर्ण

/**
 * nla_parse_nested_deprecated - parse nested attributes
 * @tb: destination array with maxtype+1 elements
 * @maxtype: maximum attribute type to be expected
 * @nla: attribute containing the nested attributes
 * @policy: validation policy
 * @extack: extended ACK report काष्ठा
 *
 * See nla_parse_deprecated()
 */
अटल अंतरभूत पूर्णांक nla_parse_nested_deprecated(काष्ठा nlattr *tb[], पूर्णांक maxtype,
					      स्थिर काष्ठा nlattr *nla,
					      स्थिर काष्ठा nla_policy *policy,
					      काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nla_parse(tb, maxtype, nla_data(nla), nla_len(nla), policy,
			   NL_VALIDATE_LIBERAL, extack);
पूर्ण

/**
 * nla_put_u8 - Add a u8 netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 */
अटल अंतरभूत पूर्णांक nla_put_u8(काष्ठा sk_buff *skb, पूर्णांक attrtype, u8 value)
अणु
	/* temporary variables to work around GCC PR81715 with asan-stack=1 */
	u8 पंचांगp = value;

	वापस nla_put(skb, attrtype, माप(u8), &पंचांगp);
पूर्ण

/**
 * nla_put_u16 - Add a u16 netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 */
अटल अंतरभूत पूर्णांक nla_put_u16(काष्ठा sk_buff *skb, पूर्णांक attrtype, u16 value)
अणु
	u16 पंचांगp = value;

	वापस nla_put(skb, attrtype, माप(u16), &पंचांगp);
पूर्ण

/**
 * nla_put_be16 - Add a __be16 netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 */
अटल अंतरभूत पूर्णांक nla_put_be16(काष्ठा sk_buff *skb, पूर्णांक attrtype, __be16 value)
अणु
	__be16 पंचांगp = value;

	वापस nla_put(skb, attrtype, माप(__be16), &पंचांगp);
पूर्ण

/**
 * nla_put_net16 - Add 16-bit network byte order netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 */
अटल अंतरभूत पूर्णांक nla_put_net16(काष्ठा sk_buff *skb, पूर्णांक attrtype, __be16 value)
अणु
	__be16 पंचांगp = value;

	वापस nla_put_be16(skb, attrtype | NLA_F_NET_BYTEORDER, पंचांगp);
पूर्ण

/**
 * nla_put_le16 - Add a __le16 netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 */
अटल अंतरभूत पूर्णांक nla_put_le16(काष्ठा sk_buff *skb, पूर्णांक attrtype, __le16 value)
अणु
	__le16 पंचांगp = value;

	वापस nla_put(skb, attrtype, माप(__le16), &पंचांगp);
पूर्ण

/**
 * nla_put_u32 - Add a u32 netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 */
अटल अंतरभूत पूर्णांक nla_put_u32(काष्ठा sk_buff *skb, पूर्णांक attrtype, u32 value)
अणु
	u32 पंचांगp = value;

	वापस nla_put(skb, attrtype, माप(u32), &पंचांगp);
पूर्ण

/**
 * nla_put_be32 - Add a __be32 netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 */
अटल अंतरभूत पूर्णांक nla_put_be32(काष्ठा sk_buff *skb, पूर्णांक attrtype, __be32 value)
अणु
	__be32 पंचांगp = value;

	वापस nla_put(skb, attrtype, माप(__be32), &पंचांगp);
पूर्ण

/**
 * nla_put_net32 - Add 32-bit network byte order netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 */
अटल अंतरभूत पूर्णांक nla_put_net32(काष्ठा sk_buff *skb, पूर्णांक attrtype, __be32 value)
अणु
	__be32 पंचांगp = value;

	वापस nla_put_be32(skb, attrtype | NLA_F_NET_BYTEORDER, पंचांगp);
पूर्ण

/**
 * nla_put_le32 - Add a __le32 netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 */
अटल अंतरभूत पूर्णांक nla_put_le32(काष्ठा sk_buff *skb, पूर्णांक attrtype, __le32 value)
अणु
	__le32 पंचांगp = value;

	वापस nla_put(skb, attrtype, माप(__le32), &पंचांगp);
पूर्ण

/**
 * nla_put_u64_64bit - Add a u64 netlink attribute to a skb and align it
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 * @padattr: attribute type क्रम the padding
 */
अटल अंतरभूत पूर्णांक nla_put_u64_64bit(काष्ठा sk_buff *skb, पूर्णांक attrtype,
				    u64 value, पूर्णांक padattr)
अणु
	u64 पंचांगp = value;

	वापस nla_put_64bit(skb, attrtype, माप(u64), &पंचांगp, padattr);
पूर्ण

/**
 * nla_put_be64 - Add a __be64 netlink attribute to a socket buffer and align it
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 * @padattr: attribute type क्रम the padding
 */
अटल अंतरभूत पूर्णांक nla_put_be64(काष्ठा sk_buff *skb, पूर्णांक attrtype, __be64 value,
			       पूर्णांक padattr)
अणु
	__be64 पंचांगp = value;

	वापस nla_put_64bit(skb, attrtype, माप(__be64), &पंचांगp, padattr);
पूर्ण

/**
 * nla_put_net64 - Add 64-bit network byte order nlattr to a skb and align it
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 * @padattr: attribute type क्रम the padding
 */
अटल अंतरभूत पूर्णांक nla_put_net64(काष्ठा sk_buff *skb, पूर्णांक attrtype, __be64 value,
				पूर्णांक padattr)
अणु
	__be64 पंचांगp = value;

	वापस nla_put_be64(skb, attrtype | NLA_F_NET_BYTEORDER, पंचांगp,
			    padattr);
पूर्ण

/**
 * nla_put_le64 - Add a __le64 netlink attribute to a socket buffer and align it
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 * @padattr: attribute type क्रम the padding
 */
अटल अंतरभूत पूर्णांक nla_put_le64(काष्ठा sk_buff *skb, पूर्णांक attrtype, __le64 value,
			       पूर्णांक padattr)
अणु
	__le64 पंचांगp = value;

	वापस nla_put_64bit(skb, attrtype, माप(__le64), &पंचांगp, padattr);
पूर्ण

/**
 * nla_put_s8 - Add a s8 netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 */
अटल अंतरभूत पूर्णांक nla_put_s8(काष्ठा sk_buff *skb, पूर्णांक attrtype, s8 value)
अणु
	s8 पंचांगp = value;

	वापस nla_put(skb, attrtype, माप(s8), &पंचांगp);
पूर्ण

/**
 * nla_put_s16 - Add a s16 netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 */
अटल अंतरभूत पूर्णांक nla_put_s16(काष्ठा sk_buff *skb, पूर्णांक attrtype, s16 value)
अणु
	s16 पंचांगp = value;

	वापस nla_put(skb, attrtype, माप(s16), &पंचांगp);
पूर्ण

/**
 * nla_put_s32 - Add a s32 netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 */
अटल अंतरभूत पूर्णांक nla_put_s32(काष्ठा sk_buff *skb, पूर्णांक attrtype, s32 value)
अणु
	s32 पंचांगp = value;

	वापस nla_put(skb, attrtype, माप(s32), &पंचांगp);
पूर्ण

/**
 * nla_put_s64 - Add a s64 netlink attribute to a socket buffer and align it
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: numeric value
 * @padattr: attribute type क्रम the padding
 */
अटल अंतरभूत पूर्णांक nla_put_s64(काष्ठा sk_buff *skb, पूर्णांक attrtype, s64 value,
			      पूर्णांक padattr)
अणु
	s64 पंचांगp = value;

	वापस nla_put_64bit(skb, attrtype, माप(s64), &पंचांगp, padattr);
पूर्ण

/**
 * nla_put_string - Add a string netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @str: NUL terminated string
 */
अटल अंतरभूत पूर्णांक nla_put_string(काष्ठा sk_buff *skb, पूर्णांक attrtype,
				 स्थिर अक्षर *str)
अणु
	वापस nla_put(skb, attrtype, म_माप(str) + 1, str);
पूर्ण

/**
 * nla_put_flag - Add a flag netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 */
अटल अंतरभूत पूर्णांक nla_put_flag(काष्ठा sk_buff *skb, पूर्णांक attrtype)
अणु
	वापस nla_put(skb, attrtype, 0, शून्य);
पूर्ण

/**
 * nla_put_msecs - Add a msecs netlink attribute to a skb and align it
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @njअगरfies: number of jअगरfies to convert to msecs
 * @padattr: attribute type क्रम the padding
 */
अटल अंतरभूत पूर्णांक nla_put_msecs(काष्ठा sk_buff *skb, पूर्णांक attrtype,
				अचिन्हित दीर्घ njअगरfies, पूर्णांक padattr)
अणु
	u64 पंचांगp = jअगरfies_to_msecs(njअगरfies);

	वापस nla_put_64bit(skb, attrtype, माप(u64), &पंचांगp, padattr);
पूर्ण

/**
 * nla_put_in_addr - Add an IPv4 address netlink attribute to a socket
 * buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @addr: IPv4 address
 */
अटल अंतरभूत पूर्णांक nla_put_in_addr(काष्ठा sk_buff *skb, पूर्णांक attrtype,
				  __be32 addr)
अणु
	__be32 पंचांगp = addr;

	वापस nla_put_be32(skb, attrtype, पंचांगp);
पूर्ण

/**
 * nla_put_in6_addr - Add an IPv6 address netlink attribute to a socket
 * buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @addr: IPv6 address
 */
अटल अंतरभूत पूर्णांक nla_put_in6_addr(काष्ठा sk_buff *skb, पूर्णांक attrtype,
				   स्थिर काष्ठा in6_addr *addr)
अणु
	वापस nla_put(skb, attrtype, माप(*addr), addr);
पूर्ण

/**
 * nla_put_bitfield32 - Add a bitfield32 netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @value: value carrying bits
 * @selector: selector of valid bits
 */
अटल अंतरभूत पूर्णांक nla_put_bitfield32(काष्ठा sk_buff *skb, पूर्णांक attrtype,
				     __u32 value, __u32 selector)
अणु
	काष्ठा nla_bitfield32 पंचांगp = अणु value, selector, पूर्ण;

	वापस nla_put(skb, attrtype, माप(पंचांगp), &पंचांगp);
पूर्ण

/**
 * nla_get_u32 - वापस payload of u32 attribute
 * @nla: u32 netlink attribute
 */
अटल अंतरभूत u32 nla_get_u32(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(u32 *) nla_data(nla);
पूर्ण

/**
 * nla_get_be32 - वापस payload of __be32 attribute
 * @nla: __be32 netlink attribute
 */
अटल अंतरभूत __be32 nla_get_be32(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(__be32 *) nla_data(nla);
पूर्ण

/**
 * nla_get_le32 - वापस payload of __le32 attribute
 * @nla: __le32 netlink attribute
 */
अटल अंतरभूत __le32 nla_get_le32(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(__le32 *) nla_data(nla);
पूर्ण

/**
 * nla_get_u16 - वापस payload of u16 attribute
 * @nla: u16 netlink attribute
 */
अटल अंतरभूत u16 nla_get_u16(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(u16 *) nla_data(nla);
पूर्ण

/**
 * nla_get_be16 - वापस payload of __be16 attribute
 * @nla: __be16 netlink attribute
 */
अटल अंतरभूत __be16 nla_get_be16(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(__be16 *) nla_data(nla);
पूर्ण

/**
 * nla_get_le16 - वापस payload of __le16 attribute
 * @nla: __le16 netlink attribute
 */
अटल अंतरभूत __le16 nla_get_le16(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(__le16 *) nla_data(nla);
पूर्ण

/**
 * nla_get_u8 - वापस payload of u8 attribute
 * @nla: u8 netlink attribute
 */
अटल अंतरभूत u8 nla_get_u8(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(u8 *) nla_data(nla);
पूर्ण

/**
 * nla_get_u64 - वापस payload of u64 attribute
 * @nla: u64 netlink attribute
 */
अटल अंतरभूत u64 nla_get_u64(स्थिर काष्ठा nlattr *nla)
अणु
	u64 पंचांगp;

	nla_स_नकल(&पंचांगp, nla, माप(पंचांगp));

	वापस पंचांगp;
पूर्ण

/**
 * nla_get_be64 - वापस payload of __be64 attribute
 * @nla: __be64 netlink attribute
 */
अटल अंतरभूत __be64 nla_get_be64(स्थिर काष्ठा nlattr *nla)
अणु
	__be64 पंचांगp;

	nla_स_नकल(&पंचांगp, nla, माप(पंचांगp));

	वापस पंचांगp;
पूर्ण

/**
 * nla_get_le64 - वापस payload of __le64 attribute
 * @nla: __le64 netlink attribute
 */
अटल अंतरभूत __le64 nla_get_le64(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(__le64 *) nla_data(nla);
पूर्ण

/**
 * nla_get_s32 - वापस payload of s32 attribute
 * @nla: s32 netlink attribute
 */
अटल अंतरभूत s32 nla_get_s32(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(s32 *) nla_data(nla);
पूर्ण

/**
 * nla_get_s16 - वापस payload of s16 attribute
 * @nla: s16 netlink attribute
 */
अटल अंतरभूत s16 nla_get_s16(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(s16 *) nla_data(nla);
पूर्ण

/**
 * nla_get_s8 - वापस payload of s8 attribute
 * @nla: s8 netlink attribute
 */
अटल अंतरभूत s8 nla_get_s8(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(s8 *) nla_data(nla);
पूर्ण

/**
 * nla_get_s64 - वापस payload of s64 attribute
 * @nla: s64 netlink attribute
 */
अटल अंतरभूत s64 nla_get_s64(स्थिर काष्ठा nlattr *nla)
अणु
	s64 पंचांगp;

	nla_स_नकल(&पंचांगp, nla, माप(पंचांगp));

	वापस पंचांगp;
पूर्ण

/**
 * nla_get_flag - वापस payload of flag attribute
 * @nla: flag netlink attribute
 */
अटल अंतरभूत पूर्णांक nla_get_flag(स्थिर काष्ठा nlattr *nla)
अणु
	वापस !!nla;
पूर्ण

/**
 * nla_get_msecs - वापस payload of msecs attribute
 * @nla: msecs netlink attribute
 *
 * Returns the number of milliseconds in jअगरfies.
 */
अटल अंतरभूत अचिन्हित दीर्घ nla_get_msecs(स्थिर काष्ठा nlattr *nla)
अणु
	u64 msecs = nla_get_u64(nla);

	वापस msecs_to_jअगरfies((अचिन्हित दीर्घ) msecs);
पूर्ण

/**
 * nla_get_in_addr - वापस payload of IPv4 address attribute
 * @nla: IPv4 address netlink attribute
 */
अटल अंतरभूत __be32 nla_get_in_addr(स्थिर काष्ठा nlattr *nla)
अणु
	वापस *(__be32 *) nla_data(nla);
पूर्ण

/**
 * nla_get_in6_addr - वापस payload of IPv6 address attribute
 * @nla: IPv6 address netlink attribute
 */
अटल अंतरभूत काष्ठा in6_addr nla_get_in6_addr(स्थिर काष्ठा nlattr *nla)
अणु
	काष्ठा in6_addr पंचांगp;

	nla_स_नकल(&पंचांगp, nla, माप(पंचांगp));
	वापस पंचांगp;
पूर्ण

/**
 * nla_get_bitfield32 - वापस payload of 32 bitfield attribute
 * @nla: nla_bitfield32 attribute
 */
अटल अंतरभूत काष्ठा nla_bitfield32 nla_get_bitfield32(स्थिर काष्ठा nlattr *nla)
अणु
	काष्ठा nla_bitfield32 पंचांगp;

	nla_स_नकल(&पंचांगp, nla, माप(पंचांगp));
	वापस पंचांगp;
पूर्ण

/**
 * nla_memdup - duplicate attribute memory (kmemdup)
 * @src: netlink attribute to duplicate from
 * @gfp: GFP mask
 */
अटल अंतरभूत व्योम *nla_memdup(स्थिर काष्ठा nlattr *src, gfp_t gfp)
अणु
	वापस kmemdup(nla_data(src), nla_len(src), gfp);
पूर्ण

/**
 * nla_nest_start_noflag - Start a new level of nested attributes
 * @skb: socket buffer to add attributes to
 * @attrtype: attribute type of container
 *
 * This function exists क्रम backward compatibility to use in APIs which never
 * marked their nest attributes with NLA_F_NESTED flag. New APIs should use
 * nla_nest_start() which sets the flag.
 *
 * Returns the container attribute or शून्य on error
 */
अटल अंतरभूत काष्ठा nlattr *nla_nest_start_noflag(काष्ठा sk_buff *skb,
						   पूर्णांक attrtype)
अणु
	काष्ठा nlattr *start = (काष्ठा nlattr *)skb_tail_poपूर्णांकer(skb);

	अगर (nla_put(skb, attrtype, 0, शून्य) < 0)
		वापस शून्य;

	वापस start;
पूर्ण

/**
 * nla_nest_start - Start a new level of nested attributes, with NLA_F_NESTED
 * @skb: socket buffer to add attributes to
 * @attrtype: attribute type of container
 *
 * Unlike nla_nest_start_noflag(), mark the nest attribute with NLA_F_NESTED
 * flag. This is the preferred function to use in new code.
 *
 * Returns the container attribute or शून्य on error
 */
अटल अंतरभूत काष्ठा nlattr *nla_nest_start(काष्ठा sk_buff *skb, पूर्णांक attrtype)
अणु
	वापस nla_nest_start_noflag(skb, attrtype | NLA_F_NESTED);
पूर्ण

/**
 * nla_nest_end - Finalize nesting of attributes
 * @skb: socket buffer the attributes are stored in
 * @start: container attribute
 *
 * Corrects the container attribute header to include the all
 * appeneded attributes.
 *
 * Returns the total data length of the skb.
 */
अटल अंतरभूत पूर्णांक nla_nest_end(काष्ठा sk_buff *skb, काष्ठा nlattr *start)
अणु
	start->nla_len = skb_tail_poपूर्णांकer(skb) - (अचिन्हित अक्षर *)start;
	वापस skb->len;
पूर्ण

/**
 * nla_nest_cancel - Cancel nesting of attributes
 * @skb: socket buffer the message is stored in
 * @start: container attribute
 *
 * Removes the container attribute and including all nested
 * attributes. Returns -EMSGSIZE
 */
अटल अंतरभूत व्योम nla_nest_cancel(काष्ठा sk_buff *skb, काष्ठा nlattr *start)
अणु
	nlmsg_trim(skb, start);
पूर्ण

/**
 * __nla_validate_nested - Validate a stream of nested attributes
 * @start: container attribute
 * @maxtype: maximum attribute type to be expected
 * @policy: validation policy
 * @validate: validation strictness
 * @extack: extended ACK report काष्ठा
 *
 * Validates all attributes in the nested attribute stream against the
 * specअगरied policy. Attributes with a type exceeding maxtype will be
 * ignored. See करोcumenation of काष्ठा nla_policy क्रम more details.
 *
 * Returns 0 on success or a negative error code.
 */
अटल अंतरभूत पूर्णांक __nla_validate_nested(स्थिर काष्ठा nlattr *start, पूर्णांक maxtype,
					स्थिर काष्ठा nla_policy *policy,
					अचिन्हित पूर्णांक validate,
					काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nla_validate(nla_data(start), nla_len(start), maxtype, policy,
			      validate, extack);
पूर्ण

अटल अंतरभूत पूर्णांक
nla_validate_nested(स्थिर काष्ठा nlattr *start, पूर्णांक maxtype,
		    स्थिर काष्ठा nla_policy *policy,
		    काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nla_validate_nested(start, maxtype, policy,
				     NL_VALIDATE_STRICT, extack);
पूर्ण

अटल अंतरभूत पूर्णांक
nla_validate_nested_deprecated(स्थिर काष्ठा nlattr *start, पूर्णांक maxtype,
			       स्थिर काष्ठा nla_policy *policy,
			       काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nla_validate_nested(start, maxtype, policy,
				     NL_VALIDATE_LIBERAL, extack);
पूर्ण

/**
 * nla_need_padding_क्रम_64bit - test 64-bit alignment of the next attribute
 * @skb: socket buffer the message is stored in
 *
 * Return true अगर padding is needed to align the next attribute (nla_data()) to
 * a 64-bit aligned area.
 */
अटल अंतरभूत bool nla_need_padding_क्रम_64bit(काष्ठा sk_buff *skb)
अणु
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	/* The nlattr header is 4 bytes in size, that's why we test
	 * अगर the skb->data _is_ aligned.  A NOP attribute, plus
	 * nlattr header क्रम next attribute, will make nla_data()
	 * 8-byte aligned.
	 */
	अगर (IS_ALIGNED((अचिन्हित दीर्घ)skb_tail_poपूर्णांकer(skb), 8))
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

/**
 * nla_align_64bit - 64-bit align the nla_data() of next attribute
 * @skb: socket buffer the message is stored in
 * @padattr: attribute type क्रम the padding
 *
 * Conditionally emit a padding netlink attribute in order to make
 * the next attribute we emit have a 64-bit aligned nla_data() area.
 * This will only be करोne in architectures which करो not have
 * CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS defined.
 *
 * Returns zero on success or a negative error code.
 */
अटल अंतरभूत पूर्णांक nla_align_64bit(काष्ठा sk_buff *skb, पूर्णांक padattr)
अणु
	अगर (nla_need_padding_क्रम_64bit(skb) &&
	    !nla_reserve(skb, padattr, 0))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

/**
 * nla_total_size_64bit - total length of attribute including padding
 * @payload: length of payload
 */
अटल अंतरभूत पूर्णांक nla_total_size_64bit(पूर्णांक payload)
अणु
	वापस NLA_ALIGN(nla_attr_size(payload))
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
		+ NLA_ALIGN(nla_attr_size(0))
#पूर्ण_अगर
		;
पूर्ण

/**
 * nla_क्रम_each_attr - iterate over a stream of attributes
 * @pos: loop counter, set to current attribute
 * @head: head of attribute stream
 * @len: length of attribute stream
 * @rem: initialized to len, holds bytes currently reमुख्यing in stream
 */
#घोषणा nla_क्रम_each_attr(pos, head, len, rem) \
	क्रम (pos = head, rem = len; \
	     nla_ok(pos, rem); \
	     pos = nla_next(pos, &(rem)))

/**
 * nla_क्रम_each_nested - iterate over nested attributes
 * @pos: loop counter, set to current attribute
 * @nla: attribute containing the nested attributes
 * @rem: initialized to len, holds bytes currently reमुख्यing in stream
 */
#घोषणा nla_क्रम_each_nested(pos, nla, rem) \
	nla_क्रम_each_attr(pos, nla_data(nla), nla_len(nla), rem)

/**
 * nla_is_last - Test अगर attribute is last in stream
 * @nla: attribute to test
 * @rem: bytes reमुख्यing in stream
 */
अटल अंतरभूत bool nla_is_last(स्थिर काष्ठा nlattr *nla, पूर्णांक rem)
अणु
	वापस nla->nla_len == rem;
पूर्ण

व्योम nla_get_range_अचिन्हित(स्थिर काष्ठा nla_policy *pt,
			    काष्ठा netlink_range_validation *range);
व्योम nla_get_range_चिन्हित(स्थिर काष्ठा nla_policy *pt,
			  काष्ठा netlink_range_validation_चिन्हित *range);

काष्ठा netlink_policy_dump_state;

पूर्णांक netlink_policy_dump_add_policy(काष्ठा netlink_policy_dump_state **pstate,
				   स्थिर काष्ठा nla_policy *policy,
				   अचिन्हित पूर्णांक maxtype);
पूर्णांक netlink_policy_dump_get_policy_idx(काष्ठा netlink_policy_dump_state *state,
				       स्थिर काष्ठा nla_policy *policy,
				       अचिन्हित पूर्णांक maxtype);
bool netlink_policy_dump_loop(काष्ठा netlink_policy_dump_state *state);
पूर्णांक netlink_policy_dump_ग_लिखो(काष्ठा sk_buff *skb,
			      काष्ठा netlink_policy_dump_state *state);
पूर्णांक netlink_policy_dump_attr_size_estimate(स्थिर काष्ठा nla_policy *pt);
पूर्णांक netlink_policy_dump_ग_लिखो_attr(काष्ठा sk_buff *skb,
				   स्थिर काष्ठा nla_policy *pt,
				   पूर्णांक nestattr);
व्योम netlink_policy_dump_मुक्त(काष्ठा netlink_policy_dump_state *state);

#पूर्ण_अगर
