<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NETLINK      Netlink attributes
 *
 * 		Authors:	Thomas Graf <tgraf@suug.ch>
 * 				Alexey Kuznetsov <kuznet@ms2.inr.ac.ru>
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <net/netlink.h>

/* For these data types, attribute length should be exactly the given
 * size. However, to मुख्यtain compatibility with broken commands, अगर the
 * attribute length करोes not match the expected size a warning is emitted
 * to the user that the command is sending invalid data and needs to be fixed.
 */
अटल स्थिर u8 nla_attr_len[NLA_TYPE_MAX+1] = अणु
	[NLA_U8]	= माप(u8),
	[NLA_U16]	= माप(u16),
	[NLA_U32]	= माप(u32),
	[NLA_U64]	= माप(u64),
	[NLA_S8]	= माप(s8),
	[NLA_S16]	= माप(s16),
	[NLA_S32]	= माप(s32),
	[NLA_S64]	= माप(s64),
पूर्ण;

अटल स्थिर u8 nla_attr_minlen[NLA_TYPE_MAX+1] = अणु
	[NLA_U8]	= माप(u8),
	[NLA_U16]	= माप(u16),
	[NLA_U32]	= माप(u32),
	[NLA_U64]	= माप(u64),
	[NLA_MSECS]	= माप(u64),
	[NLA_NESTED]	= NLA_HDRLEN,
	[NLA_S8]	= माप(s8),
	[NLA_S16]	= माप(s16),
	[NLA_S32]	= माप(s32),
	[NLA_S64]	= माप(s64),
पूर्ण;

/*
 * Nested policies might refer back to the original
 * policy in some हालs, and userspace could try to
 * abuse that and recurse by nesting in the right
 * ways. Limit recursion to aव्योम this problem.
 */
#घोषणा MAX_POLICY_RECURSION_DEPTH	10

अटल पूर्णांक __nla_validate_parse(स्थिर काष्ठा nlattr *head, पूर्णांक len, पूर्णांक maxtype,
				स्थिर काष्ठा nla_policy *policy,
				अचिन्हित पूर्णांक validate,
				काष्ठा netlink_ext_ack *extack,
				काष्ठा nlattr **tb, अचिन्हित पूर्णांक depth);

अटल पूर्णांक validate_nla_bitfield32(स्थिर काष्ठा nlattr *nla,
				   स्थिर u32 valid_flags_mask)
अणु
	स्थिर काष्ठा nla_bitfield32 *bf = nla_data(nla);

	अगर (!valid_flags_mask)
		वापस -EINVAL;

	/*disallow invalid bit selector */
	अगर (bf->selector & ~valid_flags_mask)
		वापस -EINVAL;

	/*disallow invalid bit values */
	अगर (bf->value & ~valid_flags_mask)
		वापस -EINVAL;

	/*disallow valid bit values that are not selected*/
	अगर (bf->value & ~bf->selector)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nla_validate_array(स्थिर काष्ठा nlattr *head, पूर्णांक len, पूर्णांक maxtype,
			      स्थिर काष्ठा nla_policy *policy,
			      काष्ठा netlink_ext_ack *extack,
			      अचिन्हित पूर्णांक validate, अचिन्हित पूर्णांक depth)
अणु
	स्थिर काष्ठा nlattr *entry;
	पूर्णांक rem;

	nla_क्रम_each_attr(entry, head, len, rem) अणु
		पूर्णांक ret;

		अगर (nla_len(entry) == 0)
			जारी;

		अगर (nla_len(entry) < NLA_HDRLEN) अणु
			NL_SET_ERR_MSG_ATTR_POL(extack, entry, policy,
						"Array element too short");
			वापस -दुस्फल;
		पूर्ण

		ret = __nla_validate_parse(nla_data(entry), nla_len(entry),
					   maxtype, policy, validate, extack,
					   शून्य, depth + 1);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nla_get_range_अचिन्हित(स्थिर काष्ठा nla_policy *pt,
			    काष्ठा netlink_range_validation *range)
अणु
	WARN_ON_ONCE(pt->validation_type != NLA_VALIDATE_RANGE_PTR &&
		     (pt->min < 0 || pt->max < 0));

	range->min = 0;

	चयन (pt->type) अणु
	हाल NLA_U8:
		range->max = U8_MAX;
		अवरोध;
	हाल NLA_U16:
	हाल NLA_BINARY:
		range->max = U16_MAX;
		अवरोध;
	हाल NLA_U32:
		range->max = U32_MAX;
		अवरोध;
	हाल NLA_U64:
	हाल NLA_MSECS:
		range->max = U64_MAX;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	चयन (pt->validation_type) अणु
	हाल NLA_VALIDATE_RANGE:
	हाल NLA_VALIDATE_RANGE_WARN_TOO_LONG:
		range->min = pt->min;
		range->max = pt->max;
		अवरोध;
	हाल NLA_VALIDATE_RANGE_PTR:
		*range = *pt->range;
		अवरोध;
	हाल NLA_VALIDATE_MIN:
		range->min = pt->min;
		अवरोध;
	हाल NLA_VALIDATE_MAX:
		range->max = pt->max;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक nla_validate_range_अचिन्हित(स्थिर काष्ठा nla_policy *pt,
				       स्थिर काष्ठा nlattr *nla,
				       काष्ठा netlink_ext_ack *extack,
				       अचिन्हित पूर्णांक validate)
अणु
	काष्ठा netlink_range_validation range;
	u64 value;

	चयन (pt->type) अणु
	हाल NLA_U8:
		value = nla_get_u8(nla);
		अवरोध;
	हाल NLA_U16:
		value = nla_get_u16(nla);
		अवरोध;
	हाल NLA_U32:
		value = nla_get_u32(nla);
		अवरोध;
	हाल NLA_U64:
	हाल NLA_MSECS:
		value = nla_get_u64(nla);
		अवरोध;
	हाल NLA_BINARY:
		value = nla_len(nla);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	nla_get_range_अचिन्हित(pt, &range);

	अगर (pt->validation_type == NLA_VALIDATE_RANGE_WARN_TOO_LONG &&
	    pt->type == NLA_BINARY && value > range.max) अणु
		pr_warn_ratelimited("netlink: '%s': attribute type %d has an invalid length.\n",
				    current->comm, pt->type);
		अगर (validate & NL_VALIDATE_STRICT_ATTRS) अणु
			NL_SET_ERR_MSG_ATTR_POL(extack, nla, pt,
						"invalid attribute length");
			वापस -EINVAL;
		पूर्ण

		/* this assumes min <= max (करोn't validate against min) */
		वापस 0;
	पूर्ण

	अगर (value < range.min || value > range.max) अणु
		bool binary = pt->type == NLA_BINARY;

		अगर (binary)
			NL_SET_ERR_MSG_ATTR_POL(extack, nla, pt,
						"binary attribute size out of range");
		अन्यथा
			NL_SET_ERR_MSG_ATTR_POL(extack, nla, pt,
						"integer out of range");

		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nla_get_range_चिन्हित(स्थिर काष्ठा nla_policy *pt,
			  काष्ठा netlink_range_validation_चिन्हित *range)
अणु
	चयन (pt->type) अणु
	हाल NLA_S8:
		range->min = S8_MIN;
		range->max = S8_MAX;
		अवरोध;
	हाल NLA_S16:
		range->min = S16_MIN;
		range->max = S16_MAX;
		अवरोध;
	हाल NLA_S32:
		range->min = S32_MIN;
		range->max = S32_MAX;
		अवरोध;
	हाल NLA_S64:
		range->min = S64_MIN;
		range->max = S64_MAX;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	चयन (pt->validation_type) अणु
	हाल NLA_VALIDATE_RANGE:
		range->min = pt->min;
		range->max = pt->max;
		अवरोध;
	हाल NLA_VALIDATE_RANGE_PTR:
		*range = *pt->range_चिन्हित;
		अवरोध;
	हाल NLA_VALIDATE_MIN:
		range->min = pt->min;
		अवरोध;
	हाल NLA_VALIDATE_MAX:
		range->max = pt->max;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक nla_validate_पूर्णांक_range_चिन्हित(स्थिर काष्ठा nla_policy *pt,
					 स्थिर काष्ठा nlattr *nla,
					 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा netlink_range_validation_चिन्हित range;
	s64 value;

	चयन (pt->type) अणु
	हाल NLA_S8:
		value = nla_get_s8(nla);
		अवरोध;
	हाल NLA_S16:
		value = nla_get_s16(nla);
		अवरोध;
	हाल NLA_S32:
		value = nla_get_s32(nla);
		अवरोध;
	हाल NLA_S64:
		value = nla_get_s64(nla);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	nla_get_range_चिन्हित(pt, &range);

	अगर (value < range.min || value > range.max) अणु
		NL_SET_ERR_MSG_ATTR_POL(extack, nla, pt,
					"integer out of range");
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nla_validate_पूर्णांक_range(स्थिर काष्ठा nla_policy *pt,
				  स्थिर काष्ठा nlattr *nla,
				  काष्ठा netlink_ext_ack *extack,
				  अचिन्हित पूर्णांक validate)
अणु
	चयन (pt->type) अणु
	हाल NLA_U8:
	हाल NLA_U16:
	हाल NLA_U32:
	हाल NLA_U64:
	हाल NLA_MSECS:
	हाल NLA_BINARY:
		वापस nla_validate_range_अचिन्हित(pt, nla, extack, validate);
	हाल NLA_S8:
	हाल NLA_S16:
	हाल NLA_S32:
	हाल NLA_S64:
		वापस nla_validate_पूर्णांक_range_चिन्हित(pt, nla, extack);
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक nla_validate_mask(स्थिर काष्ठा nla_policy *pt,
			     स्थिर काष्ठा nlattr *nla,
			     काष्ठा netlink_ext_ack *extack)
अणु
	u64 value;

	चयन (pt->type) अणु
	हाल NLA_U8:
		value = nla_get_u8(nla);
		अवरोध;
	हाल NLA_U16:
		value = nla_get_u16(nla);
		अवरोध;
	हाल NLA_U32:
		value = nla_get_u32(nla);
		अवरोध;
	हाल NLA_U64:
		value = nla_get_u64(nla);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (value & ~(u64)pt->mask) अणु
		NL_SET_ERR_MSG_ATTR(extack, nla, "reserved bit set");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक validate_nla(स्थिर काष्ठा nlattr *nla, पूर्णांक maxtype,
			स्थिर काष्ठा nla_policy *policy, अचिन्हित पूर्णांक validate,
			काष्ठा netlink_ext_ack *extack, अचिन्हित पूर्णांक depth)
अणु
	u16 strict_start_type = policy[0].strict_start_type;
	स्थिर काष्ठा nla_policy *pt;
	पूर्णांक minlen = 0, attrlen = nla_len(nla), type = nla_type(nla);
	पूर्णांक err = -दुस्फल;

	अगर (strict_start_type && type >= strict_start_type)
		validate |= NL_VALIDATE_STRICT;

	अगर (type <= 0 || type > maxtype)
		वापस 0;

	pt = &policy[type];

	BUG_ON(pt->type > NLA_TYPE_MAX);

	अगर (nla_attr_len[pt->type] && attrlen != nla_attr_len[pt->type]) अणु
		pr_warn_ratelimited("netlink: '%s': attribute type %d has an invalid length.\n",
				    current->comm, type);
		अगर (validate & NL_VALIDATE_STRICT_ATTRS) अणु
			NL_SET_ERR_MSG_ATTR_POL(extack, nla, pt,
						"invalid attribute length");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (validate & NL_VALIDATE_NESTED) अणु
		अगर ((pt->type == NLA_NESTED || pt->type == NLA_NESTED_ARRAY) &&
		    !(nla->nla_type & NLA_F_NESTED)) अणु
			NL_SET_ERR_MSG_ATTR_POL(extack, nla, pt,
						"NLA_F_NESTED is missing");
			वापस -EINVAL;
		पूर्ण
		अगर (pt->type != NLA_NESTED && pt->type != NLA_NESTED_ARRAY &&
		    pt->type != NLA_UNSPEC && (nla->nla_type & NLA_F_NESTED)) अणु
			NL_SET_ERR_MSG_ATTR_POL(extack, nla, pt,
						"NLA_F_NESTED not expected");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	चयन (pt->type) अणु
	हाल NLA_REJECT:
		अगर (extack && pt->reject_message) अणु
			NL_SET_BAD_ATTR(extack, nla);
			extack->_msg = pt->reject_message;
			वापस -EINVAL;
		पूर्ण
		err = -EINVAL;
		जाओ out_err;

	हाल NLA_FLAG:
		अगर (attrlen > 0)
			जाओ out_err;
		अवरोध;

	हाल NLA_BITFIELD32:
		अगर (attrlen != माप(काष्ठा nla_bitfield32))
			जाओ out_err;

		err = validate_nla_bitfield32(nla, pt->bitfield32_valid);
		अगर (err)
			जाओ out_err;
		अवरोध;

	हाल NLA_NUL_STRING:
		अगर (pt->len)
			minlen = min_t(पूर्णांक, attrlen, pt->len + 1);
		अन्यथा
			minlen = attrlen;

		अगर (!minlen || स_प्रथम(nla_data(nla), '\0', minlen) == शून्य) अणु
			err = -EINVAL;
			जाओ out_err;
		पूर्ण
		fallthrough;

	हाल NLA_STRING:
		अगर (attrlen < 1)
			जाओ out_err;

		अगर (pt->len) अणु
			अक्षर *buf = nla_data(nla);

			अगर (buf[attrlen - 1] == '\0')
				attrlen--;

			अगर (attrlen > pt->len)
				जाओ out_err;
		पूर्ण
		अवरोध;

	हाल NLA_BINARY:
		अगर (pt->len && attrlen > pt->len)
			जाओ out_err;
		अवरोध;

	हाल NLA_NESTED:
		/* a nested attributes is allowed to be empty; अगर its not,
		 * it must have a size of at least NLA_HDRLEN.
		 */
		अगर (attrlen == 0)
			अवरोध;
		अगर (attrlen < NLA_HDRLEN)
			जाओ out_err;
		अगर (pt->nested_policy) अणु
			err = __nla_validate_parse(nla_data(nla), nla_len(nla),
						   pt->len, pt->nested_policy,
						   validate, extack, शून्य,
						   depth + 1);
			अगर (err < 0) अणु
				/*
				 * वापस directly to preserve the inner
				 * error message/attribute poपूर्णांकer
				 */
				वापस err;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल NLA_NESTED_ARRAY:
		/* a nested array attribute is allowed to be empty; अगर its not,
		 * it must have a size of at least NLA_HDRLEN.
		 */
		अगर (attrlen == 0)
			अवरोध;
		अगर (attrlen < NLA_HDRLEN)
			जाओ out_err;
		अगर (pt->nested_policy) अणु
			पूर्णांक err;

			err = nla_validate_array(nla_data(nla), nla_len(nla),
						 pt->len, pt->nested_policy,
						 extack, validate, depth);
			अगर (err < 0) अणु
				/*
				 * वापस directly to preserve the inner
				 * error message/attribute poपूर्णांकer
				 */
				वापस err;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल NLA_UNSPEC:
		अगर (validate & NL_VALIDATE_UNSPEC) अणु
			NL_SET_ERR_MSG_ATTR(extack, nla,
					    "Unsupported attribute");
			वापस -EINVAL;
		पूर्ण
		अगर (attrlen < pt->len)
			जाओ out_err;
		अवरोध;

	शेष:
		अगर (pt->len)
			minlen = pt->len;
		अन्यथा
			minlen = nla_attr_minlen[pt->type];

		अगर (attrlen < minlen)
			जाओ out_err;
	पूर्ण

	/* further validation */
	चयन (pt->validation_type) अणु
	हाल NLA_VALIDATE_NONE:
		/* nothing to करो */
		अवरोध;
	हाल NLA_VALIDATE_RANGE_PTR:
	हाल NLA_VALIDATE_RANGE:
	हाल NLA_VALIDATE_RANGE_WARN_TOO_LONG:
	हाल NLA_VALIDATE_MIN:
	हाल NLA_VALIDATE_MAX:
		err = nla_validate_पूर्णांक_range(pt, nla, extack, validate);
		अगर (err)
			वापस err;
		अवरोध;
	हाल NLA_VALIDATE_MASK:
		err = nla_validate_mask(pt, nla, extack);
		अगर (err)
			वापस err;
		अवरोध;
	हाल NLA_VALIDATE_FUNCTION:
		अगर (pt->validate) अणु
			err = pt->validate(nla, extack);
			अगर (err)
				वापस err;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
out_err:
	NL_SET_ERR_MSG_ATTR_POL(extack, nla, pt,
				"Attribute failed policy validation");
	वापस err;
पूर्ण

अटल पूर्णांक __nla_validate_parse(स्थिर काष्ठा nlattr *head, पूर्णांक len, पूर्णांक maxtype,
				स्थिर काष्ठा nla_policy *policy,
				अचिन्हित पूर्णांक validate,
				काष्ठा netlink_ext_ack *extack,
				काष्ठा nlattr **tb, अचिन्हित पूर्णांक depth)
अणु
	स्थिर काष्ठा nlattr *nla;
	पूर्णांक rem;

	अगर (depth >= MAX_POLICY_RECURSION_DEPTH) अणु
		NL_SET_ERR_MSG(extack,
			       "allowed policy recursion depth exceeded");
		वापस -EINVAL;
	पूर्ण

	अगर (tb)
		स_रखो(tb, 0, माप(काष्ठा nlattr *) * (maxtype + 1));

	nla_क्रम_each_attr(nla, head, len, rem) अणु
		u16 type = nla_type(nla);

		अगर (type == 0 || type > maxtype) अणु
			अगर (validate & NL_VALIDATE_MAXTYPE) अणु
				NL_SET_ERR_MSG_ATTR(extack, nla,
						    "Unknown attribute type");
				वापस -EINVAL;
			पूर्ण
			जारी;
		पूर्ण
		अगर (policy) अणु
			पूर्णांक err = validate_nla(nla, maxtype, policy,
					       validate, extack, depth);

			अगर (err < 0)
				वापस err;
		पूर्ण

		अगर (tb)
			tb[type] = (काष्ठा nlattr *)nla;
	पूर्ण

	अगर (unlikely(rem > 0)) अणु
		pr_warn_ratelimited("netlink: %d bytes leftover after parsing attributes in process `%s'.\n",
				    rem, current->comm);
		NL_SET_ERR_MSG(extack, "bytes leftover after parsing attributes");
		अगर (validate & NL_VALIDATE_TRAILING)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * __nla_validate - Validate a stream of attributes
 * @head: head of attribute stream
 * @len: length of attribute stream
 * @maxtype: maximum attribute type to be expected
 * @policy: validation policy
 * @validate: validation strictness
 * @extack: extended ACK report काष्ठा
 *
 * Validates all attributes in the specअगरied attribute stream against the
 * specअगरied policy. Validation depends on the validate flags passed, see
 * &क्रमागत netlink_validation क्रम more details on that.
 * See करोcumenation of काष्ठा nla_policy क्रम more details.
 *
 * Returns 0 on success or a negative error code.
 */
पूर्णांक __nla_validate(स्थिर काष्ठा nlattr *head, पूर्णांक len, पूर्णांक maxtype,
		   स्थिर काष्ठा nla_policy *policy, अचिन्हित पूर्णांक validate,
		   काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nla_validate_parse(head, len, maxtype, policy, validate,
				    extack, शून्य, 0);
पूर्ण
EXPORT_SYMBOL(__nla_validate);

/**
 * nla_policy_len - Determin the max. length of a policy
 * @policy: policy to use
 * @n: number of policies
 *
 * Determines the max. length of the policy.  It is currently used
 * to allocated Netlink buffers roughly the size of the actual
 * message.
 *
 * Returns 0 on success or a negative error code.
 */
पूर्णांक
nla_policy_len(स्थिर काष्ठा nla_policy *p, पूर्णांक n)
अणु
	पूर्णांक i, len = 0;

	क्रम (i = 0; i < n; i++, p++) अणु
		अगर (p->len)
			len += nla_total_size(p->len);
		अन्यथा अगर (nla_attr_len[p->type])
			len += nla_total_size(nla_attr_len[p->type]);
		अन्यथा अगर (nla_attr_minlen[p->type])
			len += nla_total_size(nla_attr_minlen[p->type]);
	पूर्ण

	वापस len;
पूर्ण
EXPORT_SYMBOL(nla_policy_len);

/**
 * __nla_parse - Parse a stream of attributes पूर्णांकo a tb buffer
 * @tb: destination array with maxtype+1 elements
 * @maxtype: maximum attribute type to be expected
 * @head: head of attribute stream
 * @len: length of attribute stream
 * @policy: validation policy
 * @validate: validation strictness
 * @extack: extended ACK poपूर्णांकer
 *
 * Parses a stream of attributes and stores a poपूर्णांकer to each attribute in
 * the tb array accessible via the attribute type.
 * Validation is controlled by the @validate parameter.
 *
 * Returns 0 on success or a negative error code.
 */
पूर्णांक __nla_parse(काष्ठा nlattr **tb, पूर्णांक maxtype,
		स्थिर काष्ठा nlattr *head, पूर्णांक len,
		स्थिर काष्ठा nla_policy *policy, अचिन्हित पूर्णांक validate,
		काष्ठा netlink_ext_ack *extack)
अणु
	वापस __nla_validate_parse(head, len, maxtype, policy, validate,
				    extack, tb, 0);
पूर्ण
EXPORT_SYMBOL(__nla_parse);

/**
 * nla_find - Find a specअगरic attribute in a stream of attributes
 * @head: head of attribute stream
 * @len: length of attribute stream
 * @attrtype: type of attribute to look क्रम
 *
 * Returns the first attribute in the stream matching the specअगरied type.
 */
काष्ठा nlattr *nla_find(स्थिर काष्ठा nlattr *head, पूर्णांक len, पूर्णांक attrtype)
अणु
	स्थिर काष्ठा nlattr *nla;
	पूर्णांक rem;

	nla_क्रम_each_attr(nla, head, len, rem)
		अगर (nla_type(nla) == attrtype)
			वापस (काष्ठा nlattr *)nla;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(nla_find);

/**
 * nla_strscpy - Copy string attribute payload पूर्णांकo a sized buffer
 * @dst: Where to copy the string to.
 * @nla: Attribute to copy the string from.
 * @dstsize: Size of destination buffer.
 *
 * Copies at most dstsize - 1 bytes पूर्णांकo the destination buffer.
 * Unlike strlcpy the destination buffer is always padded out.
 *
 * Return:
 * * srclen - Returns @nla length (not including the trailing %NUL).
 * * -E2BIG - If @dstsize is 0 or greater than U16_MAX or @nla length greater
 *            than @dstsize.
 */
sमाप_प्रकार nla_strscpy(अक्षर *dst, स्थिर काष्ठा nlattr *nla, माप_प्रकार dstsize)
अणु
	माप_प्रकार srclen = nla_len(nla);
	अक्षर *src = nla_data(nla);
	sमाप_प्रकार ret;
	माप_प्रकार len;

	अगर (dstsize == 0 || WARN_ON_ONCE(dstsize > U16_MAX))
		वापस -E2BIG;

	अगर (srclen > 0 && src[srclen - 1] == '\0')
		srclen--;

	अगर (srclen >= dstsize) अणु
		len = dstsize - 1;
		ret = -E2BIG;
	पूर्ण अन्यथा अणु
		len = srclen;
		ret = len;
	पूर्ण

	स_नकल(dst, src, len);
	/* Zero pad end of dst. */
	स_रखो(dst + len, 0, dstsize - len);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(nla_strscpy);

/**
 * nla_strdup - Copy string attribute payload पूर्णांकo a newly allocated buffer
 * @nla: attribute to copy the string from
 * @flags: the type of memory to allocate (see kदो_स्मृति).
 *
 * Returns a poपूर्णांकer to the allocated buffer or शून्य on error.
 */
अक्षर *nla_strdup(स्थिर काष्ठा nlattr *nla, gfp_t flags)
अणु
	माप_प्रकार srclen = nla_len(nla);
	अक्षर *src = nla_data(nla), *dst;

	अगर (srclen > 0 && src[srclen - 1] == '\0')
		srclen--;

	dst = kदो_स्मृति(srclen + 1, flags);
	अगर (dst != शून्य) अणु
		स_नकल(dst, src, srclen);
		dst[srclen] = '\0';
	पूर्ण
	वापस dst;
पूर्ण
EXPORT_SYMBOL(nla_strdup);

/**
 * nla_स_नकल - Copy a netlink attribute पूर्णांकo another memory area
 * @dest: where to copy to स_नकल
 * @src: netlink attribute to copy from
 * @count: size of the destination area
 *
 * Note: The number of bytes copied is limited by the length of
 *       attribute's payload. स_नकल
 *
 * Returns the number of bytes copied.
 */
पूर्णांक nla_स_नकल(व्योम *dest, स्थिर काष्ठा nlattr *src, पूर्णांक count)
अणु
	पूर्णांक minlen = min_t(पूर्णांक, count, nla_len(src));

	स_नकल(dest, nla_data(src), minlen);
	अगर (count > minlen)
		स_रखो(dest + minlen, 0, count - minlen);

	वापस minlen;
पूर्ण
EXPORT_SYMBOL(nla_स_नकल);

/**
 * nla_स_भेद - Compare an attribute with sized memory area
 * @nla: netlink attribute
 * @data: memory area
 * @size: size of memory area
 */
पूर्णांक nla_स_भेद(स्थिर काष्ठा nlattr *nla, स्थिर व्योम *data,
			     माप_प्रकार size)
अणु
	पूर्णांक d = nla_len(nla) - size;

	अगर (d == 0)
		d = स_भेद(nla_data(nla), data, size);

	वापस d;
पूर्ण
EXPORT_SYMBOL(nla_स_भेद);

/**
 * nla_म_भेद - Compare a string attribute against a string
 * @nla: netlink string attribute
 * @str: another string
 */
पूर्णांक nla_म_भेद(स्थिर काष्ठा nlattr *nla, स्थिर अक्षर *str)
अणु
	पूर्णांक len = म_माप(str);
	अक्षर *buf = nla_data(nla);
	पूर्णांक attrlen = nla_len(nla);
	पूर्णांक d;

	जबतक (attrlen > 0 && buf[attrlen - 1] == '\0')
		attrlen--;

	d = attrlen - len;
	अगर (d == 0)
		d = स_भेद(nla_data(nla), str, len);

	वापस d;
पूर्ण
EXPORT_SYMBOL(nla_म_भेद);

#अगर_घोषित CONFIG_NET
/**
 * __nla_reserve - reserve room क्रम attribute on the skb
 * @skb: socket buffer to reserve room on
 * @attrtype: attribute type
 * @attrlen: length of attribute payload
 *
 * Adds a netlink attribute header to a socket buffer and reserves
 * room क्रम the payload but करोes not copy it.
 *
 * The caller is responsible to ensure that the skb provides enough
 * tailroom क्रम the attribute header and payload.
 */
काष्ठा nlattr *__nla_reserve(काष्ठा sk_buff *skb, पूर्णांक attrtype, पूर्णांक attrlen)
अणु
	काष्ठा nlattr *nla;

	nla = skb_put(skb, nla_total_size(attrlen));
	nla->nla_type = attrtype;
	nla->nla_len = nla_attr_size(attrlen);

	स_रखो((अचिन्हित अक्षर *) nla + nla->nla_len, 0, nla_padlen(attrlen));

	वापस nla;
पूर्ण
EXPORT_SYMBOL(__nla_reserve);

/**
 * __nla_reserve_64bit - reserve room क्रम attribute on the skb and align it
 * @skb: socket buffer to reserve room on
 * @attrtype: attribute type
 * @attrlen: length of attribute payload
 * @padattr: attribute type क्रम the padding
 *
 * Adds a netlink attribute header to a socket buffer and reserves
 * room क्रम the payload but करोes not copy it. It also ensure that this
 * attribute will have a 64-bit aligned nla_data() area.
 *
 * The caller is responsible to ensure that the skb provides enough
 * tailroom क्रम the attribute header and payload.
 */
काष्ठा nlattr *__nla_reserve_64bit(काष्ठा sk_buff *skb, पूर्णांक attrtype,
				   पूर्णांक attrlen, पूर्णांक padattr)
अणु
	nla_align_64bit(skb, padattr);

	वापस __nla_reserve(skb, attrtype, attrlen);
पूर्ण
EXPORT_SYMBOL(__nla_reserve_64bit);

/**
 * __nla_reserve_nohdr - reserve room क्रम attribute without header
 * @skb: socket buffer to reserve room on
 * @attrlen: length of attribute payload
 *
 * Reserves room क्रम attribute payload without a header.
 *
 * The caller is responsible to ensure that the skb provides enough
 * tailroom क्रम the payload.
 */
व्योम *__nla_reserve_nohdr(काष्ठा sk_buff *skb, पूर्णांक attrlen)
अणु
	वापस skb_put_zero(skb, NLA_ALIGN(attrlen));
पूर्ण
EXPORT_SYMBOL(__nla_reserve_nohdr);

/**
 * nla_reserve - reserve room क्रम attribute on the skb
 * @skb: socket buffer to reserve room on
 * @attrtype: attribute type
 * @attrlen: length of attribute payload
 *
 * Adds a netlink attribute header to a socket buffer and reserves
 * room क्रम the payload but करोes not copy it.
 *
 * Returns शून्य अगर the tailroom of the skb is insufficient to store
 * the attribute header and payload.
 */
काष्ठा nlattr *nla_reserve(काष्ठा sk_buff *skb, पूर्णांक attrtype, पूर्णांक attrlen)
अणु
	अगर (unlikely(skb_tailroom(skb) < nla_total_size(attrlen)))
		वापस शून्य;

	वापस __nla_reserve(skb, attrtype, attrlen);
पूर्ण
EXPORT_SYMBOL(nla_reserve);

/**
 * nla_reserve_64bit - reserve room क्रम attribute on the skb and align it
 * @skb: socket buffer to reserve room on
 * @attrtype: attribute type
 * @attrlen: length of attribute payload
 * @padattr: attribute type क्रम the padding
 *
 * Adds a netlink attribute header to a socket buffer and reserves
 * room क्रम the payload but करोes not copy it. It also ensure that this
 * attribute will have a 64-bit aligned nla_data() area.
 *
 * Returns शून्य अगर the tailroom of the skb is insufficient to store
 * the attribute header and payload.
 */
काष्ठा nlattr *nla_reserve_64bit(काष्ठा sk_buff *skb, पूर्णांक attrtype, पूर्णांक attrlen,
				 पूर्णांक padattr)
अणु
	माप_प्रकार len;

	अगर (nla_need_padding_क्रम_64bit(skb))
		len = nla_total_size_64bit(attrlen);
	अन्यथा
		len = nla_total_size(attrlen);
	अगर (unlikely(skb_tailroom(skb) < len))
		वापस शून्य;

	वापस __nla_reserve_64bit(skb, attrtype, attrlen, padattr);
पूर्ण
EXPORT_SYMBOL(nla_reserve_64bit);

/**
 * nla_reserve_nohdr - reserve room क्रम attribute without header
 * @skb: socket buffer to reserve room on
 * @attrlen: length of attribute payload
 *
 * Reserves room क्रम attribute payload without a header.
 *
 * Returns शून्य अगर the tailroom of the skb is insufficient to store
 * the attribute payload.
 */
व्योम *nla_reserve_nohdr(काष्ठा sk_buff *skb, पूर्णांक attrlen)
अणु
	अगर (unlikely(skb_tailroom(skb) < NLA_ALIGN(attrlen)))
		वापस शून्य;

	वापस __nla_reserve_nohdr(skb, attrlen);
पूर्ण
EXPORT_SYMBOL(nla_reserve_nohdr);

/**
 * __nla_put - Add a netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @attrlen: length of attribute payload
 * @data: head of attribute payload
 *
 * The caller is responsible to ensure that the skb provides enough
 * tailroom क्रम the attribute header and payload.
 */
व्योम __nla_put(काष्ठा sk_buff *skb, पूर्णांक attrtype, पूर्णांक attrlen,
			     स्थिर व्योम *data)
अणु
	काष्ठा nlattr *nla;

	nla = __nla_reserve(skb, attrtype, attrlen);
	स_नकल(nla_data(nla), data, attrlen);
पूर्ण
EXPORT_SYMBOL(__nla_put);

/**
 * __nla_put_64bit - Add a netlink attribute to a socket buffer and align it
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @attrlen: length of attribute payload
 * @data: head of attribute payload
 * @padattr: attribute type क्रम the padding
 *
 * The caller is responsible to ensure that the skb provides enough
 * tailroom क्रम the attribute header and payload.
 */
व्योम __nla_put_64bit(काष्ठा sk_buff *skb, पूर्णांक attrtype, पूर्णांक attrlen,
		     स्थिर व्योम *data, पूर्णांक padattr)
अणु
	काष्ठा nlattr *nla;

	nla = __nla_reserve_64bit(skb, attrtype, attrlen, padattr);
	स_नकल(nla_data(nla), data, attrlen);
पूर्ण
EXPORT_SYMBOL(__nla_put_64bit);

/**
 * __nla_put_nohdr - Add a netlink attribute without header
 * @skb: socket buffer to add attribute to
 * @attrlen: length of attribute payload
 * @data: head of attribute payload
 *
 * The caller is responsible to ensure that the skb provides enough
 * tailroom क्रम the attribute payload.
 */
व्योम __nla_put_nohdr(काष्ठा sk_buff *skb, पूर्णांक attrlen, स्थिर व्योम *data)
अणु
	व्योम *start;

	start = __nla_reserve_nohdr(skb, attrlen);
	स_नकल(start, data, attrlen);
पूर्ण
EXPORT_SYMBOL(__nla_put_nohdr);

/**
 * nla_put - Add a netlink attribute to a socket buffer
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @attrlen: length of attribute payload
 * @data: head of attribute payload
 *
 * Returns -EMSGSIZE अगर the tailroom of the skb is insufficient to store
 * the attribute header and payload.
 */
पूर्णांक nla_put(काष्ठा sk_buff *skb, पूर्णांक attrtype, पूर्णांक attrlen, स्थिर व्योम *data)
अणु
	अगर (unlikely(skb_tailroom(skb) < nla_total_size(attrlen)))
		वापस -EMSGSIZE;

	__nla_put(skb, attrtype, attrlen, data);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(nla_put);

/**
 * nla_put_64bit - Add a netlink attribute to a socket buffer and align it
 * @skb: socket buffer to add attribute to
 * @attrtype: attribute type
 * @attrlen: length of attribute payload
 * @data: head of attribute payload
 * @padattr: attribute type क्रम the padding
 *
 * Returns -EMSGSIZE अगर the tailroom of the skb is insufficient to store
 * the attribute header and payload.
 */
पूर्णांक nla_put_64bit(काष्ठा sk_buff *skb, पूर्णांक attrtype, पूर्णांक attrlen,
		  स्थिर व्योम *data, पूर्णांक padattr)
अणु
	माप_प्रकार len;

	अगर (nla_need_padding_क्रम_64bit(skb))
		len = nla_total_size_64bit(attrlen);
	अन्यथा
		len = nla_total_size(attrlen);
	अगर (unlikely(skb_tailroom(skb) < len))
		वापस -EMSGSIZE;

	__nla_put_64bit(skb, attrtype, attrlen, data, padattr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(nla_put_64bit);

/**
 * nla_put_nohdr - Add a netlink attribute without header
 * @skb: socket buffer to add attribute to
 * @attrlen: length of attribute payload
 * @data: head of attribute payload
 *
 * Returns -EMSGSIZE अगर the tailroom of the skb is insufficient to store
 * the attribute payload.
 */
पूर्णांक nla_put_nohdr(काष्ठा sk_buff *skb, पूर्णांक attrlen, स्थिर व्योम *data)
अणु
	अगर (unlikely(skb_tailroom(skb) < NLA_ALIGN(attrlen)))
		वापस -EMSGSIZE;

	__nla_put_nohdr(skb, attrlen, data);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(nla_put_nohdr);

/**
 * nla_append - Add a netlink attribute without header or padding
 * @skb: socket buffer to add attribute to
 * @attrlen: length of attribute payload
 * @data: head of attribute payload
 *
 * Returns -EMSGSIZE अगर the tailroom of the skb is insufficient to store
 * the attribute payload.
 */
पूर्णांक nla_append(काष्ठा sk_buff *skb, पूर्णांक attrlen, स्थिर व्योम *data)
अणु
	अगर (unlikely(skb_tailroom(skb) < NLA_ALIGN(attrlen)))
		वापस -EMSGSIZE;

	skb_put_data(skb, data, attrlen);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(nla_append);
#पूर्ण_अगर
