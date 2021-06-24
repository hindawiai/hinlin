<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/ethtool_netlink.h>
#समावेश <linux/biपंचांगap.h>
#समावेश "netlink.h"
#समावेश "bitset.h"

/* Some biपंचांगaps are पूर्णांकernally represented as an array of अचिन्हित दीर्घ, some
 * as an array of u32 (some even as single u32 क्रम now). To aव्योम the need of
 * wrappers on caller side, we provide two set of functions: those with "32"
 * suffix in their names expect u32 based biपंचांगaps, those without it expect
 * अचिन्हित दीर्घ biपंचांगaps.
 */

अटल u32 ethnl_lower_bits(अचिन्हित पूर्णांक n)
अणु
	वापस ~(u32)0 >> (32 - n % 32);
पूर्ण

अटल u32 ethnl_upper_bits(अचिन्हित पूर्णांक n)
अणु
	वापस ~(u32)0 << (n % 32);
पूर्ण

/**
 * ethnl_biपंचांगap32_clear() - Clear u32 based biपंचांगap
 * @dst:   biपंचांगap to clear
 * @start: beginning of the पूर्णांकerval
 * @end:   end of the पूर्णांकerval
 * @mod:   set अगर biपंचांगap was modअगरied
 *
 * Clear @nbits bits of a biपंचांगap with indices @start <= i < @end
 */
अटल व्योम ethnl_biपंचांगap32_clear(u32 *dst, अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end,
				 bool *mod)
अणु
	अचिन्हित पूर्णांक start_word = start / 32;
	अचिन्हित पूर्णांक end_word = end / 32;
	अचिन्हित पूर्णांक i;
	u32 mask;

	अगर (end <= start)
		वापस;

	अगर (start % 32) अणु
		mask = ethnl_upper_bits(start);
		अगर (end_word == start_word) अणु
			mask &= ethnl_lower_bits(end);
			अगर (dst[start_word] & mask) अणु
				dst[start_word] &= ~mask;
				*mod = true;
			पूर्ण
			वापस;
		पूर्ण
		अगर (dst[start_word] & mask) अणु
			dst[start_word] &= ~mask;
			*mod = true;
		पूर्ण
		start_word++;
	पूर्ण

	क्रम (i = start_word; i < end_word; i++) अणु
		अगर (dst[i]) अणु
			dst[i] = 0;
			*mod = true;
		पूर्ण
	पूर्ण
	अगर (end % 32) अणु
		mask = ethnl_lower_bits(end);
		अगर (dst[end_word] & mask) अणु
			dst[end_word] &= ~mask;
			*mod = true;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ethnl_biपंचांगap32_not_zero() - Check अगर any bit is set in an पूर्णांकerval
 * @map:   biपंचांगap to test
 * @start: beginning of the पूर्णांकerval
 * @end:   end of the पूर्णांकerval
 *
 * Return: true अगर there is non-zero bit with  index @start <= i < @end,
 *         false अगर the whole पूर्णांकerval is zero
 */
अटल bool ethnl_biपंचांगap32_not_zero(स्थिर u32 *map, अचिन्हित पूर्णांक start,
				    अचिन्हित पूर्णांक end)
अणु
	अचिन्हित पूर्णांक start_word = start / 32;
	अचिन्हित पूर्णांक end_word = end / 32;
	u32 mask;

	अगर (end <= start)
		वापस true;

	अगर (start % 32) अणु
		mask = ethnl_upper_bits(start);
		अगर (end_word == start_word) अणु
			mask &= ethnl_lower_bits(end);
			वापस map[start_word] & mask;
		पूर्ण
		अगर (map[start_word] & mask)
			वापस true;
		start_word++;
	पूर्ण

	अगर (!स_प्रथम_inv(map + start_word, '\0',
			(end_word - start_word) * माप(u32)))
		वापस true;
	अगर (end % 32 == 0)
		वापस true;
	वापस map[end_word] & ethnl_lower_bits(end);
पूर्ण

/**
 * ethnl_biपंचांगap32_update() - Modअगरy u32 based biपंचांगap according to value/mask
 *			     pair
 * @dst:   biपंचांगap to update
 * @nbits: bit size of the biपंचांगap
 * @value: values to set
 * @mask:  mask of bits to set
 * @mod:   set to true अगर biपंचांगap is modअगरied, preserve अगर not
 *
 * Set bits in @dst biपंचांगap which are set in @mask to values from @value, leave
 * the rest untouched. If destination biपंचांगap was modअगरied, set @mod to true,
 * leave as it is अगर not.
 */
अटल व्योम ethnl_biपंचांगap32_update(u32 *dst, अचिन्हित पूर्णांक nbits,
				  स्थिर u32 *value, स्थिर u32 *mask, bool *mod)
अणु
	जबतक (nbits > 0) अणु
		u32 real_mask = mask ? *mask : ~(u32)0;
		u32 new_value;

		अगर (nbits < 32)
			real_mask &= ethnl_lower_bits(nbits);
		new_value = (*dst & ~real_mask) | (*value & real_mask);
		अगर (new_value != *dst) अणु
			*dst = new_value;
			*mod = true;
		पूर्ण

		अगर (nbits <= 32)
			अवरोध;
		dst++;
		nbits -= 32;
		value++;
		अगर (mask)
			mask++;
	पूर्ण
पूर्ण

अटल bool ethnl_biपंचांगap32_test_bit(स्थिर u32 *map, अचिन्हित पूर्णांक index)
अणु
	वापस map[index / 32] & (1U << (index % 32));
पूर्ण

/**
 * ethnl_bitset32_size() - Calculate size of bitset nested attribute
 * @val:     value biपंचांगap (u32 based)
 * @mask:    mask biपंचांगap (u32 based, optional)
 * @nbits:   bit length of the bitset
 * @names:   array of bit names (optional)
 * @compact: assume compact क्रमmat क्रम output
 *
 * Estimate length of netlink attribute composed by a later call to
 * ethnl_put_bitset32() call with the same arguments.
 *
 * Return: negative error code or attribute length estimate
 */
पूर्णांक ethnl_bitset32_size(स्थिर u32 *val, स्थिर u32 *mask, अचिन्हित पूर्णांक nbits,
			ethnl_string_array_t names, bool compact)
अणु
	अचिन्हित पूर्णांक len = 0;

	/* list flag */
	अगर (!mask)
		len += nla_total_size(माप(u32));
	/* size */
	len += nla_total_size(माप(u32));

	अगर (compact) अणु
		अचिन्हित पूर्णांक nwords = DIV_ROUND_UP(nbits, 32);

		/* value, mask */
		len += (mask ? 2 : 1) * nla_total_size(nwords * माप(u32));
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक bits_len = 0;
		अचिन्हित पूर्णांक bit_len, i;

		क्रम (i = 0; i < nbits; i++) अणु
			स्थिर अक्षर *name = names ? names[i] : शून्य;

			अगर (!ethnl_biपंचांगap32_test_bit(mask ?: val, i))
				जारी;
			/* index */
			bit_len = nla_total_size(माप(u32));
			/* name */
			अगर (name)
				bit_len += ethnl_strz_size(name);
			/* value */
			अगर (mask && ethnl_biपंचांगap32_test_bit(val, i))
				bit_len += nla_total_size(0);

			/* bit nest */
			bits_len += nla_total_size(bit_len);
		पूर्ण
		/* bits nest */
		len += nla_total_size(bits_len);
	पूर्ण

	/* outermost nest */
	वापस nla_total_size(len);
पूर्ण

/**
 * ethnl_put_bitset32() - Put a bitset nest पूर्णांकo a message
 * @skb:      skb with the message
 * @attrtype: attribute type क्रम the bitset nest
 * @val:      value biपंचांगap (u32 based)
 * @mask:     mask biपंचांगap (u32 based, optional)
 * @nbits:    bit length of the bitset
 * @names:    array of bit names (optional)
 * @compact:  use compact क्रमmat क्रम the output
 *
 * Compose a nested attribute representing a bitset. If @mask is null, simple
 * biपंचांगap (bit list) is created, अगर @mask is provided, represent a value/mask
 * pair. Bit names are only used in verbose mode and when provided by calller.
 *
 * Return: 0 on success, negative error value on error
 */
पूर्णांक ethnl_put_bitset32(काष्ठा sk_buff *skb, पूर्णांक attrtype, स्थिर u32 *val,
		       स्थिर u32 *mask, अचिन्हित पूर्णांक nbits,
		       ethnl_string_array_t names, bool compact)
अणु
	काष्ठा nlattr *nest;
	काष्ठा nlattr *attr;

	nest = nla_nest_start(skb, attrtype);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (!mask && nla_put_flag(skb, ETHTOOL_A_BITSET_NOMASK))
		जाओ nla_put_failure;
	अगर (nla_put_u32(skb, ETHTOOL_A_BITSET_SIZE, nbits))
		जाओ nla_put_failure;
	अगर (compact) अणु
		अचिन्हित पूर्णांक nwords = DIV_ROUND_UP(nbits, 32);
		अचिन्हित पूर्णांक nbytes = nwords * माप(u32);
		u32 *dst;

		attr = nla_reserve(skb, ETHTOOL_A_BITSET_VALUE, nbytes);
		अगर (!attr)
			जाओ nla_put_failure;
		dst = nla_data(attr);
		स_नकल(dst, val, nbytes);
		अगर (nbits % 32)
			dst[nwords - 1] &= ethnl_lower_bits(nbits);

		अगर (mask) अणु
			attr = nla_reserve(skb, ETHTOOL_A_BITSET_MASK, nbytes);
			अगर (!attr)
				जाओ nla_put_failure;
			dst = nla_data(attr);
			स_नकल(dst, mask, nbytes);
			अगर (nbits % 32)
				dst[nwords - 1] &= ethnl_lower_bits(nbits);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा nlattr *bits;
		अचिन्हित पूर्णांक i;

		bits = nla_nest_start(skb, ETHTOOL_A_BITSET_BITS);
		अगर (!bits)
			जाओ nla_put_failure;
		क्रम (i = 0; i < nbits; i++) अणु
			स्थिर अक्षर *name = names ? names[i] : शून्य;

			अगर (!ethnl_biपंचांगap32_test_bit(mask ?: val, i))
				जारी;
			attr = nla_nest_start(skb, ETHTOOL_A_BITSET_BITS_BIT);
			अगर (!attr)
				जाओ nla_put_failure;
			अगर (nla_put_u32(skb, ETHTOOL_A_BITSET_BIT_INDEX, i))
				जाओ nla_put_failure;
			अगर (name &&
			    ethnl_put_strz(skb, ETHTOOL_A_BITSET_BIT_NAME, name))
				जाओ nla_put_failure;
			अगर (mask && ethnl_biपंचांगap32_test_bit(val, i) &&
			    nla_put_flag(skb, ETHTOOL_A_BITSET_BIT_VALUE))
				जाओ nla_put_failure;
			nla_nest_end(skb, attr);
		पूर्ण
		nla_nest_end(skb, bits);
	पूर्ण

	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा nla_policy bitset_policy[] = अणु
	[ETHTOOL_A_BITSET_NOMASK]	= अणु .type = NLA_FLAG पूर्ण,
	[ETHTOOL_A_BITSET_SIZE]		= NLA_POLICY_MAX(NLA_U32,
							 ETHNL_MAX_BITSET_SIZE),
	[ETHTOOL_A_BITSET_BITS]		= अणु .type = NLA_NESTED पूर्ण,
	[ETHTOOL_A_BITSET_VALUE]	= अणु .type = NLA_BINARY पूर्ण,
	[ETHTOOL_A_BITSET_MASK]		= अणु .type = NLA_BINARY पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy bit_policy[] = अणु
	[ETHTOOL_A_BITSET_BIT_INDEX]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_BITSET_BIT_NAME]	= अणु .type = NLA_NUL_STRING पूर्ण,
	[ETHTOOL_A_BITSET_BIT_VALUE]	= अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

/**
 * ethnl_bitset_is_compact() - check अगर bitset attribute represents a compact
 *			       bitset
 * @bitset:  nested attribute representing a bitset
 * @compact: poपूर्णांकer क्रम वापस value
 *
 * Return: 0 on success, negative error code on failure
 */
पूर्णांक ethnl_bitset_is_compact(स्थिर काष्ठा nlattr *bitset, bool *compact)
अणु
	काष्ठा nlattr *tb[ARRAY_SIZE(bitset_policy)];
	पूर्णांक ret;

	ret = nla_parse_nested(tb, ARRAY_SIZE(bitset_policy) - 1, bitset,
			       bitset_policy, शून्य);
	अगर (ret < 0)
		वापस ret;

	अगर (tb[ETHTOOL_A_BITSET_BITS]) अणु
		अगर (tb[ETHTOOL_A_BITSET_VALUE] || tb[ETHTOOL_A_BITSET_MASK])
			वापस -EINVAL;
		*compact = false;
		वापस 0;
	पूर्ण
	अगर (!tb[ETHTOOL_A_BITSET_SIZE] || !tb[ETHTOOL_A_BITSET_VALUE])
		वापस -EINVAL;

	*compact = true;
	वापस 0;
पूर्ण

/**
 * ethnl_name_to_idx() - look up string index क्रम a name
 * @names:   array of ETH_GSTRING_LEN sized strings
 * @n_names: number of strings in the array
 * @name:    name to look up
 *
 * Return: index of the string अगर found, -ENOENT अगर not found
 */
अटल पूर्णांक ethnl_name_to_idx(ethnl_string_array_t names, अचिन्हित पूर्णांक n_names,
			     स्थिर अक्षर *name)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!names)
		वापस -ENOENT;

	क्रम (i = 0; i < n_names; i++) अणु
		/* names[i] may not be null terminated */
		अगर (!म_भेदन(names[i], name, ETH_GSTRING_LEN) &&
		    म_माप(name) <= ETH_GSTRING_LEN)
			वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक ethnl_parse_bit(अचिन्हित पूर्णांक *index, bool *val, अचिन्हित पूर्णांक nbits,
			   स्थिर काष्ठा nlattr *bit_attr, bool no_mask,
			   ethnl_string_array_t names,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[ARRAY_SIZE(bit_policy)];
	पूर्णांक ret, idx;

	ret = nla_parse_nested(tb, ARRAY_SIZE(bit_policy) - 1, bit_attr,
			       bit_policy, extack);
	अगर (ret < 0)
		वापस ret;

	अगर (tb[ETHTOOL_A_BITSET_BIT_INDEX]) अणु
		स्थिर अक्षर *name;

		idx = nla_get_u32(tb[ETHTOOL_A_BITSET_BIT_INDEX]);
		अगर (idx >= nbits) अणु
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[ETHTOOL_A_BITSET_BIT_INDEX],
					    "bit index too high");
			वापस -EOPNOTSUPP;
		पूर्ण
		name = names ? names[idx] : शून्य;
		अगर (tb[ETHTOOL_A_BITSET_BIT_NAME] && name &&
		    म_भेदन(nla_data(tb[ETHTOOL_A_BITSET_BIT_NAME]), name,
			    nla_len(tb[ETHTOOL_A_BITSET_BIT_NAME]))) अणु
			NL_SET_ERR_MSG_ATTR(extack, bit_attr,
					    "bit index and name mismatch");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (tb[ETHTOOL_A_BITSET_BIT_NAME]) अणु
		idx = ethnl_name_to_idx(names, nbits,
					nla_data(tb[ETHTOOL_A_BITSET_BIT_NAME]));
		अगर (idx < 0) अणु
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[ETHTOOL_A_BITSET_BIT_NAME],
					    "bit name not found");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG_ATTR(extack, bit_attr,
				    "neither bit index nor name specified");
		वापस -EINVAL;
	पूर्ण

	*index = idx;
	*val = no_mask || tb[ETHTOOL_A_BITSET_BIT_VALUE];
	वापस 0;
पूर्ण

अटल पूर्णांक
ethnl_update_bitset32_verbose(u32 *biपंचांगap, अचिन्हित पूर्णांक nbits,
			      स्थिर काष्ठा nlattr *attr, काष्ठा nlattr **tb,
			      ethnl_string_array_t names,
			      काष्ठा netlink_ext_ack *extack, bool *mod)
अणु
	काष्ठा nlattr *bit_attr;
	bool no_mask;
	पूर्णांक rem;
	पूर्णांक ret;

	अगर (tb[ETHTOOL_A_BITSET_VALUE]) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb[ETHTOOL_A_BITSET_VALUE],
				    "value only allowed in compact bitset");
		वापस -EINVAL;
	पूर्ण
	अगर (tb[ETHTOOL_A_BITSET_MASK]) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb[ETHTOOL_A_BITSET_MASK],
				    "mask only allowed in compact bitset");
		वापस -EINVAL;
	पूर्ण

	no_mask = tb[ETHTOOL_A_BITSET_NOMASK];
	अगर (no_mask)
		ethnl_biपंचांगap32_clear(biपंचांगap, 0, nbits, mod);

	nla_क्रम_each_nested(bit_attr, tb[ETHTOOL_A_BITSET_BITS], rem) अणु
		bool old_val, new_val;
		अचिन्हित पूर्णांक idx;

		अगर (nla_type(bit_attr) != ETHTOOL_A_BITSET_BITS_BIT) अणु
			NL_SET_ERR_MSG_ATTR(extack, bit_attr,
					    "only ETHTOOL_A_BITSET_BITS_BIT allowed in ETHTOOL_A_BITSET_BITS");
			वापस -EINVAL;
		पूर्ण
		ret = ethnl_parse_bit(&idx, &new_val, nbits, bit_attr, no_mask,
				      names, extack);
		अगर (ret < 0)
			वापस ret;
		old_val = biपंचांगap[idx / 32] & ((u32)1 << (idx % 32));
		अगर (new_val != old_val) अणु
			अगर (new_val)
				biपंचांगap[idx / 32] |= ((u32)1 << (idx % 32));
			अन्यथा
				biपंचांगap[idx / 32] &= ~((u32)1 << (idx % 32));
			*mod = true;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ethnl_compact_sanity_checks(अचिन्हित पूर्णांक nbits,
				       स्थिर काष्ठा nlattr *nest,
				       काष्ठा nlattr **tb,
				       काष्ठा netlink_ext_ack *extack)
अणु
	bool no_mask = tb[ETHTOOL_A_BITSET_NOMASK];
	अचिन्हित पूर्णांक attr_nbits, attr_nwords;
	स्थिर काष्ठा nlattr *test_attr;

	अगर (no_mask && tb[ETHTOOL_A_BITSET_MASK]) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb[ETHTOOL_A_BITSET_MASK],
				    "mask not allowed in list bitset");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[ETHTOOL_A_BITSET_SIZE]) अणु
		NL_SET_ERR_MSG_ATTR(extack, nest,
				    "missing size in compact bitset");
		वापस -EINVAL;
	पूर्ण
	अगर (!tb[ETHTOOL_A_BITSET_VALUE]) अणु
		NL_SET_ERR_MSG_ATTR(extack, nest,
				    "missing value in compact bitset");
		वापस -EINVAL;
	पूर्ण
	अगर (!no_mask && !tb[ETHTOOL_A_BITSET_MASK]) अणु
		NL_SET_ERR_MSG_ATTR(extack, nest,
				    "missing mask in compact nonlist bitset");
		वापस -EINVAL;
	पूर्ण

	attr_nbits = nla_get_u32(tb[ETHTOOL_A_BITSET_SIZE]);
	attr_nwords = DIV_ROUND_UP(attr_nbits, 32);
	अगर (nla_len(tb[ETHTOOL_A_BITSET_VALUE]) != attr_nwords * माप(u32)) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb[ETHTOOL_A_BITSET_VALUE],
				    "bitset value length does not match size");
		वापस -EINVAL;
	पूर्ण
	अगर (tb[ETHTOOL_A_BITSET_MASK] &&
	    nla_len(tb[ETHTOOL_A_BITSET_MASK]) != attr_nwords * माप(u32)) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb[ETHTOOL_A_BITSET_MASK],
				    "bitset mask length does not match size");
		वापस -EINVAL;
	पूर्ण
	अगर (attr_nbits <= nbits)
		वापस 0;

	test_attr = no_mask ? tb[ETHTOOL_A_BITSET_VALUE] :
			      tb[ETHTOOL_A_BITSET_MASK];
	अगर (ethnl_biपंचांगap32_not_zero(nla_data(test_attr), nbits, attr_nbits)) अणु
		NL_SET_ERR_MSG_ATTR(extack, test_attr,
				    "cannot modify bits past kernel bitset size");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ethnl_update_bitset32() - Apply a bitset nest to a u32 based biपंचांगap
 * @biपंचांगap:  biपंचांगap to update
 * @nbits:   size of the updated biपंचांगap in bits
 * @attr:    nest attribute to parse and apply
 * @names:   array of bit names; may be null क्रम compact क्रमmat
 * @extack:  extack क्रम error reporting
 * @mod:     set this to true अगर biपंचांगap is modअगरied, leave as it is अगर not
 *
 * Apply bitset netsted attribute to a biपंचांगap. If the attribute represents
 * a bit list, @biपंचांगap is set to its contents; otherwise, bits in mask are
 * set to values from value. Biपंचांगaps in the attribute may be दीर्घer than
 * @nbits but the message must not request modअगरying any bits past @nbits.
 *
 * Return: negative error code on failure, 0 on success
 */
पूर्णांक ethnl_update_bitset32(u32 *biपंचांगap, अचिन्हित पूर्णांक nbits,
			  स्थिर काष्ठा nlattr *attr, ethnl_string_array_t names,
			  काष्ठा netlink_ext_ack *extack, bool *mod)
अणु
	काष्ठा nlattr *tb[ARRAY_SIZE(bitset_policy)];
	अचिन्हित पूर्णांक change_bits;
	bool no_mask;
	पूर्णांक ret;

	अगर (!attr)
		वापस 0;
	ret = nla_parse_nested(tb, ARRAY_SIZE(bitset_policy) - 1, attr,
			       bitset_policy, extack);
	अगर (ret < 0)
		वापस ret;

	अगर (tb[ETHTOOL_A_BITSET_BITS])
		वापस ethnl_update_bitset32_verbose(biपंचांगap, nbits, attr, tb,
						     names, extack, mod);
	ret = ethnl_compact_sanity_checks(nbits, attr, tb, extack);
	अगर (ret < 0)
		वापस ret;

	no_mask = tb[ETHTOOL_A_BITSET_NOMASK];
	change_bits = min_t(अचिन्हित पूर्णांक,
			    nla_get_u32(tb[ETHTOOL_A_BITSET_SIZE]), nbits);
	ethnl_biपंचांगap32_update(biपंचांगap, change_bits,
			      nla_data(tb[ETHTOOL_A_BITSET_VALUE]),
			      no_mask ? शून्य :
					nla_data(tb[ETHTOOL_A_BITSET_MASK]),
			      mod);
	अगर (no_mask && change_bits < nbits)
		ethnl_biपंचांगap32_clear(biपंचांगap, change_bits, nbits, mod);

	वापस 0;
पूर्ण

/**
 * ethnl_parse_bitset() - Compute effective value and mask from bitset nest
 * @val:     अचिन्हित दीर्घ based biपंचांगap to put value पूर्णांकo
 * @mask:    अचिन्हित दीर्घ based biपंचांगap to put mask पूर्णांकo
 * @nbits:   size of @val and @mask biपंचांगaps
 * @attr:    nest attribute to parse and apply
 * @names:   array of bit names; may be null क्रम compact क्रमmat
 * @extack:  extack क्रम error reporting
 *
 * Provide @nbits size दीर्घ biपंचांगaps क्रम value and mask so that
 * x = (val & mask) | (x & ~mask) would modअगरy any @nbits sized biपंचांगap x
 * the same way ethnl_update_bitset() with the same bitset attribute would.
 *
 * Return:   negative error code on failure, 0 on success
 */
पूर्णांक ethnl_parse_bitset(अचिन्हित दीर्घ *val, अचिन्हित दीर्घ *mask,
		       अचिन्हित पूर्णांक nbits, स्थिर काष्ठा nlattr *attr,
		       ethnl_string_array_t names,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[ARRAY_SIZE(bitset_policy)];
	स्थिर काष्ठा nlattr *bit_attr;
	bool no_mask;
	पूर्णांक rem;
	पूर्णांक ret;

	अगर (!attr)
		वापस 0;
	ret = nla_parse_nested(tb, ARRAY_SIZE(bitset_policy) - 1, attr,
			       bitset_policy, extack);
	अगर (ret < 0)
		वापस ret;
	no_mask = tb[ETHTOOL_A_BITSET_NOMASK];

	अगर (!tb[ETHTOOL_A_BITSET_BITS]) अणु
		अचिन्हित पूर्णांक change_bits;

		ret = ethnl_compact_sanity_checks(nbits, attr, tb, extack);
		अगर (ret < 0)
			वापस ret;

		change_bits = nla_get_u32(tb[ETHTOOL_A_BITSET_SIZE]);
		अगर (change_bits > nbits)
			change_bits = nbits;
		biपंचांगap_from_arr32(val, nla_data(tb[ETHTOOL_A_BITSET_VALUE]),
				  change_bits);
		अगर (change_bits < nbits)
			biपंचांगap_clear(val, change_bits, nbits - change_bits);
		अगर (no_mask) अणु
			biपंचांगap_fill(mask, nbits);
		पूर्ण अन्यथा अणु
			biपंचांगap_from_arr32(mask,
					  nla_data(tb[ETHTOOL_A_BITSET_MASK]),
					  change_bits);
			अगर (change_bits < nbits)
				biपंचांगap_clear(mask, change_bits,
					     nbits - change_bits);
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (tb[ETHTOOL_A_BITSET_VALUE]) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb[ETHTOOL_A_BITSET_VALUE],
				    "value only allowed in compact bitset");
		वापस -EINVAL;
	पूर्ण
	अगर (tb[ETHTOOL_A_BITSET_MASK]) अणु
		NL_SET_ERR_MSG_ATTR(extack, tb[ETHTOOL_A_BITSET_MASK],
				    "mask only allowed in compact bitset");
		वापस -EINVAL;
	पूर्ण

	biपंचांगap_zero(val, nbits);
	अगर (no_mask)
		biपंचांगap_fill(mask, nbits);
	अन्यथा
		biपंचांगap_zero(mask, nbits);

	nla_क्रम_each_nested(bit_attr, tb[ETHTOOL_A_BITSET_BITS], rem) अणु
		अचिन्हित पूर्णांक idx;
		bool bit_val;

		ret = ethnl_parse_bit(&idx, &bit_val, nbits, bit_attr, no_mask,
				      names, extack);
		अगर (ret < 0)
			वापस ret;
		अगर (bit_val)
			__set_bit(idx, val);
		अगर (!no_mask)
			__set_bit(idx, mask);
	पूर्ण

	वापस 0;
पूर्ण

#अगर BITS_PER_LONG == 64 && defined(__BIG_ENDIAN)

/* 64-bit big endian architectures are the only हाल when u32 based biपंचांगaps
 * and अचिन्हित दीर्घ based biपंचांगaps have dअगरferent memory layout so that we
 * cannot simply cast the latter to the क्रमmer and need actual wrappers
 * converting the latter to the क्रमmer.
 *
 * To reduce the number of slab allocations, the wrappers use fixed size local
 * variables क्रम biपंचांगaps up to ETHNL_SMALL_BITMAP_BITS bits which is the
 * majority of biपंचांगaps used by ethtool.
 */
#घोषणा ETHNL_SMALL_BITMAP_BITS 128
#घोषणा ETHNL_SMALL_BITMAP_WORDS DIV_ROUND_UP(ETHNL_SMALL_BITMAP_BITS, 32)

पूर्णांक ethnl_bitset_size(स्थिर अचिन्हित दीर्घ *val, स्थिर अचिन्हित दीर्घ *mask,
		      अचिन्हित पूर्णांक nbits, ethnl_string_array_t names,
		      bool compact)
अणु
	u32 small_mask32[ETHNL_SMALL_BITMAP_WORDS];
	u32 small_val32[ETHNL_SMALL_BITMAP_WORDS];
	u32 *mask32;
	u32 *val32;
	पूर्णांक ret;

	अगर (nbits > ETHNL_SMALL_BITMAP_BITS) अणु
		अचिन्हित पूर्णांक nwords = DIV_ROUND_UP(nbits, 32);

		val32 = kदो_स्मृति_array(2 * nwords, माप(u32), GFP_KERNEL);
		अगर (!val32)
			वापस -ENOMEM;
		mask32 = val32 + nwords;
	पूर्ण अन्यथा अणु
		val32 = small_val32;
		mask32 = small_mask32;
	पूर्ण

	biपंचांगap_to_arr32(val32, val, nbits);
	अगर (mask)
		biपंचांगap_to_arr32(mask32, mask, nbits);
	अन्यथा
		mask32 = शून्य;
	ret = ethnl_bitset32_size(val32, mask32, nbits, names, compact);

	अगर (nbits > ETHNL_SMALL_BITMAP_BITS)
		kमुक्त(val32);

	वापस ret;
पूर्ण

पूर्णांक ethnl_put_bitset(काष्ठा sk_buff *skb, पूर्णांक attrtype,
		     स्थिर अचिन्हित दीर्घ *val, स्थिर अचिन्हित दीर्घ *mask,
		     अचिन्हित पूर्णांक nbits, ethnl_string_array_t names,
		     bool compact)
अणु
	u32 small_mask32[ETHNL_SMALL_BITMAP_WORDS];
	u32 small_val32[ETHNL_SMALL_BITMAP_WORDS];
	u32 *mask32;
	u32 *val32;
	पूर्णांक ret;

	अगर (nbits > ETHNL_SMALL_BITMAP_BITS) अणु
		अचिन्हित पूर्णांक nwords = DIV_ROUND_UP(nbits, 32);

		val32 = kदो_स्मृति_array(2 * nwords, माप(u32), GFP_KERNEL);
		अगर (!val32)
			वापस -ENOMEM;
		mask32 = val32 + nwords;
	पूर्ण अन्यथा अणु
		val32 = small_val32;
		mask32 = small_mask32;
	पूर्ण

	biपंचांगap_to_arr32(val32, val, nbits);
	अगर (mask)
		biपंचांगap_to_arr32(mask32, mask, nbits);
	अन्यथा
		mask32 = शून्य;
	ret = ethnl_put_bitset32(skb, attrtype, val32, mask32, nbits, names,
				 compact);

	अगर (nbits > ETHNL_SMALL_BITMAP_BITS)
		kमुक्त(val32);

	वापस ret;
पूर्ण

पूर्णांक ethnl_update_bitset(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक nbits,
			स्थिर काष्ठा nlattr *attr, ethnl_string_array_t names,
			काष्ठा netlink_ext_ack *extack, bool *mod)
अणु
	u32 small_biपंचांगap32[ETHNL_SMALL_BITMAP_WORDS];
	u32 *biपंचांगap32 = small_biपंचांगap32;
	bool u32_mod = false;
	पूर्णांक ret;

	अगर (nbits > ETHNL_SMALL_BITMAP_BITS) अणु
		अचिन्हित पूर्णांक dst_words = DIV_ROUND_UP(nbits, 32);

		biपंचांगap32 = kदो_स्मृति_array(dst_words, माप(u32), GFP_KERNEL);
		अगर (!biपंचांगap32)
			वापस -ENOMEM;
	पूर्ण

	biपंचांगap_to_arr32(biपंचांगap32, biपंचांगap, nbits);
	ret = ethnl_update_bitset32(biपंचांगap32, nbits, attr, names, extack,
				    &u32_mod);
	अगर (u32_mod) अणु
		biपंचांगap_from_arr32(biपंचांगap, biपंचांगap32, nbits);
		*mod = true;
	पूर्ण

	अगर (nbits > ETHNL_SMALL_BITMAP_BITS)
		kमुक्त(biपंचांगap32);

	वापस ret;
पूर्ण

#अन्यथा

/* On little endian 64-bit and all 32-bit architectures, an अचिन्हित दीर्घ
 * based biपंचांगap can be पूर्णांकerpreted as u32 based one using a simple cast.
 */

पूर्णांक ethnl_bitset_size(स्थिर अचिन्हित दीर्घ *val, स्थिर अचिन्हित दीर्घ *mask,
		      अचिन्हित पूर्णांक nbits, ethnl_string_array_t names,
		      bool compact)
अणु
	वापस ethnl_bitset32_size((स्थिर u32 *)val, (स्थिर u32 *)mask, nbits,
				   names, compact);
पूर्ण

पूर्णांक ethnl_put_bitset(काष्ठा sk_buff *skb, पूर्णांक attrtype,
		     स्थिर अचिन्हित दीर्घ *val, स्थिर अचिन्हित दीर्घ *mask,
		     अचिन्हित पूर्णांक nbits, ethnl_string_array_t names,
		     bool compact)
अणु
	वापस ethnl_put_bitset32(skb, attrtype, (स्थिर u32 *)val,
				  (स्थिर u32 *)mask, nbits, names, compact);
पूर्ण

पूर्णांक ethnl_update_bitset(अचिन्हित दीर्घ *biपंचांगap, अचिन्हित पूर्णांक nbits,
			स्थिर काष्ठा nlattr *attr, ethnl_string_array_t names,
			काष्ठा netlink_ext_ack *extack, bool *mod)
अणु
	वापस ethnl_update_bitset32((u32 *)biपंचांगap, nbits, attr, names, extack,
				     mod);
पूर्ण

#पूर्ण_अगर /* BITS_PER_LONG == 64 && defined(__BIG_ENDIAN) */
