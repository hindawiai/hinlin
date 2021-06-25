<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NETLINK      Policy advertisement to userspace
 *
 * 		Authors:	Johannes Berg <johannes@sipsolutions.net>
 *
 * Copyright 2019 Intel Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <net/netlink.h>

#घोषणा INITIAL_POLICIES_ALLOC	10

काष्ठा netlink_policy_dump_state अणु
	अचिन्हित पूर्णांक policy_idx;
	अचिन्हित पूर्णांक attr_idx;
	अचिन्हित पूर्णांक n_alloc;
	काष्ठा अणु
		स्थिर काष्ठा nla_policy *policy;
		अचिन्हित पूर्णांक maxtype;
	पूर्ण policies[];
पूर्ण;

अटल पूर्णांक add_policy(काष्ठा netlink_policy_dump_state **statep,
		      स्थिर काष्ठा nla_policy *policy,
		      अचिन्हित पूर्णांक maxtype)
अणु
	काष्ठा netlink_policy_dump_state *state = *statep;
	अचिन्हित पूर्णांक n_alloc, i;

	अगर (!policy || !maxtype)
		वापस 0;

	क्रम (i = 0; i < state->n_alloc; i++) अणु
		अगर (state->policies[i].policy == policy &&
		    state->policies[i].maxtype == maxtype)
			वापस 0;

		अगर (!state->policies[i].policy) अणु
			state->policies[i].policy = policy;
			state->policies[i].maxtype = maxtype;
			वापस 0;
		पूर्ण
	पूर्ण

	n_alloc = state->n_alloc + INITIAL_POLICIES_ALLOC;
	state = kपुनः_स्मृति(state, काष्ठा_size(state, policies, n_alloc),
			 GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;

	स_रखो(&state->policies[state->n_alloc], 0,
	       flex_array_size(state, policies, n_alloc - state->n_alloc));

	state->policies[state->n_alloc].policy = policy;
	state->policies[state->n_alloc].maxtype = maxtype;
	state->n_alloc = n_alloc;
	*statep = state;

	वापस 0;
पूर्ण

/**
 * netlink_policy_dump_get_policy_idx - retrieve policy index
 * @state: the policy dump state
 * @policy: the policy to find
 * @maxtype: the policy's maxattr
 *
 * Returns: the index of the given policy in the dump state
 *
 * Call this to find a policy index when you've added multiple and e.g.
 * need to tell userspace which command has which policy (by index).
 *
 * Note: this will WARN and वापस 0 अगर the policy isn't found, which
 *	 means it wasn't added in the first place, which would be an
 *	 पूर्णांकernal consistency bug.
 */
पूर्णांक netlink_policy_dump_get_policy_idx(काष्ठा netlink_policy_dump_state *state,
				       स्थिर काष्ठा nla_policy *policy,
				       अचिन्हित पूर्णांक maxtype)
अणु
	अचिन्हित पूर्णांक i;

	अगर (WARN_ON(!policy || !maxtype))
                वापस 0;

	क्रम (i = 0; i < state->n_alloc; i++) अणु
		अगर (state->policies[i].policy == policy &&
		    state->policies[i].maxtype == maxtype)
			वापस i;
	पूर्ण

	WARN_ON(1);
	वापस 0;
पूर्ण

अटल काष्ठा netlink_policy_dump_state *alloc_state(व्योम)
अणु
	काष्ठा netlink_policy_dump_state *state;

	state = kzalloc(काष्ठा_size(state, policies, INITIAL_POLICIES_ALLOC),
			GFP_KERNEL);
	अगर (!state)
		वापस ERR_PTR(-ENOMEM);
	state->n_alloc = INITIAL_POLICIES_ALLOC;

	वापस state;
पूर्ण

/**
 * netlink_policy_dump_add_policy - add a policy to the dump
 * @pstate: state to add to, may be पुनः_स्मृतिated, must be %शून्य the first समय
 * @policy: the new policy to add to the dump
 * @maxtype: the new policy's max attr type
 *
 * Returns: 0 on success, a negative error code otherwise.
 *
 * Call this to allocate a policy dump state, and to add policies to it. This
 * should be called from the dump start() callback.
 *
 * Note: on failures, any previously allocated state is मुक्तd.
 */
पूर्णांक netlink_policy_dump_add_policy(काष्ठा netlink_policy_dump_state **pstate,
				   स्थिर काष्ठा nla_policy *policy,
				   अचिन्हित पूर्णांक maxtype)
अणु
	काष्ठा netlink_policy_dump_state *state = *pstate;
	अचिन्हित पूर्णांक policy_idx;
	पूर्णांक err;

	अगर (!state) अणु
		state = alloc_state();
		अगर (IS_ERR(state))
			वापस PTR_ERR(state);
	पूर्ण

	/*
	 * walk the policies and nested ones first, and build
	 * a linear list of them.
	 */

	err = add_policy(&state, policy, maxtype);
	अगर (err)
		वापस err;

	क्रम (policy_idx = 0;
	     policy_idx < state->n_alloc && state->policies[policy_idx].policy;
	     policy_idx++) अणु
		स्थिर काष्ठा nla_policy *policy;
		अचिन्हित पूर्णांक type;

		policy = state->policies[policy_idx].policy;

		क्रम (type = 0;
		     type <= state->policies[policy_idx].maxtype;
		     type++) अणु
			चयन (policy[type].type) अणु
			हाल NLA_NESTED:
			हाल NLA_NESTED_ARRAY:
				err = add_policy(&state,
						 policy[type].nested_policy,
						 policy[type].len);
				अगर (err)
					वापस err;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	*pstate = state;
	वापस 0;
पूर्ण

अटल bool
netlink_policy_dump_finished(काष्ठा netlink_policy_dump_state *state)
अणु
	वापस state->policy_idx >= state->n_alloc ||
	       !state->policies[state->policy_idx].policy;
पूर्ण

/**
 * netlink_policy_dump_loop - dumping loop indicator
 * @state: the policy dump state
 *
 * Returns: %true अगर the dump जारीs, %false otherwise
 *
 * Note: this मुक्तs the dump state when finishing
 */
bool netlink_policy_dump_loop(काष्ठा netlink_policy_dump_state *state)
अणु
	वापस !netlink_policy_dump_finished(state);
पूर्ण

पूर्णांक netlink_policy_dump_attr_size_estimate(स्थिर काष्ठा nla_policy *pt)
अणु
	/* nested + type */
	पूर्णांक common = 2 * nla_attr_size(माप(u32));

	चयन (pt->type) अणु
	हाल NLA_UNSPEC:
	हाल NLA_REJECT:
		/* these actually करोn't need any space */
		वापस 0;
	हाल NLA_NESTED:
	हाल NLA_NESTED_ARRAY:
		/* common, policy idx, policy maxattr */
		वापस common + 2 * nla_attr_size(माप(u32));
	हाल NLA_U8:
	हाल NLA_U16:
	हाल NLA_U32:
	हाल NLA_U64:
	हाल NLA_MSECS:
	हाल NLA_S8:
	हाल NLA_S16:
	हाल NLA_S32:
	हाल NLA_S64:
		/* maximum is common, u64 min/max with padding */
		वापस common +
		       2 * (nla_attr_size(0) + nla_attr_size(माप(u64)));
	हाल NLA_BITFIELD32:
		वापस common + nla_attr_size(माप(u32));
	हाल NLA_STRING:
	हाल NLA_NUL_STRING:
	हाल NLA_BINARY:
		/* maximum is common, u32 min-length/max-length */
		वापस common + 2 * nla_attr_size(माप(u32));
	हाल NLA_FLAG:
		वापस common;
	पूर्ण

	/* this should then cause a warning later */
	वापस 0;
पूर्ण

अटल पूर्णांक
__netlink_policy_dump_ग_लिखो_attr(काष्ठा netlink_policy_dump_state *state,
				 काष्ठा sk_buff *skb,
				 स्थिर काष्ठा nla_policy *pt,
				 पूर्णांक nestattr)
अणु
	पूर्णांक estimate = netlink_policy_dump_attr_size_estimate(pt);
	क्रमागत netlink_attribute_type type;
	काष्ठा nlattr *attr;

	attr = nla_nest_start(skb, nestattr);
	अगर (!attr)
		वापस -ENOBUFS;

	चयन (pt->type) अणु
	शेष:
	हाल NLA_UNSPEC:
	हाल NLA_REJECT:
		/* skip - use NLA_MIN_LEN to advertise such */
		nla_nest_cancel(skb, attr);
		वापस -ENODATA;
	हाल NLA_NESTED:
		type = NL_ATTR_TYPE_NESTED;
		fallthrough;
	हाल NLA_NESTED_ARRAY:
		अगर (pt->type == NLA_NESTED_ARRAY)
			type = NL_ATTR_TYPE_NESTED_ARRAY;
		अगर (state && pt->nested_policy && pt->len &&
		    (nla_put_u32(skb, NL_POLICY_TYPE_ATTR_POLICY_IDX,
				 netlink_policy_dump_get_policy_idx(state,
								    pt->nested_policy,
								    pt->len)) ||
		     nla_put_u32(skb, NL_POLICY_TYPE_ATTR_POLICY_MAXTYPE,
				 pt->len)))
			जाओ nla_put_failure;
		अवरोध;
	हाल NLA_U8:
	हाल NLA_U16:
	हाल NLA_U32:
	हाल NLA_U64:
	हाल NLA_MSECS: अणु
		काष्ठा netlink_range_validation range;

		अगर (pt->type == NLA_U8)
			type = NL_ATTR_TYPE_U8;
		अन्यथा अगर (pt->type == NLA_U16)
			type = NL_ATTR_TYPE_U16;
		अन्यथा अगर (pt->type == NLA_U32)
			type = NL_ATTR_TYPE_U32;
		अन्यथा
			type = NL_ATTR_TYPE_U64;

		अगर (pt->validation_type == NLA_VALIDATE_MASK) अणु
			अगर (nla_put_u64_64bit(skb, NL_POLICY_TYPE_ATTR_MASK,
					      pt->mask,
					      NL_POLICY_TYPE_ATTR_PAD))
				जाओ nla_put_failure;
			अवरोध;
		पूर्ण

		nla_get_range_अचिन्हित(pt, &range);

		अगर (nla_put_u64_64bit(skb, NL_POLICY_TYPE_ATTR_MIN_VALUE_U,
				      range.min, NL_POLICY_TYPE_ATTR_PAD) ||
		    nla_put_u64_64bit(skb, NL_POLICY_TYPE_ATTR_MAX_VALUE_U,
				      range.max, NL_POLICY_TYPE_ATTR_PAD))
			जाओ nla_put_failure;
		अवरोध;
	पूर्ण
	हाल NLA_S8:
	हाल NLA_S16:
	हाल NLA_S32:
	हाल NLA_S64: अणु
		काष्ठा netlink_range_validation_चिन्हित range;

		अगर (pt->type == NLA_S8)
			type = NL_ATTR_TYPE_S8;
		अन्यथा अगर (pt->type == NLA_S16)
			type = NL_ATTR_TYPE_S16;
		अन्यथा अगर (pt->type == NLA_S32)
			type = NL_ATTR_TYPE_S32;
		अन्यथा
			type = NL_ATTR_TYPE_S64;

		nla_get_range_चिन्हित(pt, &range);

		अगर (nla_put_s64(skb, NL_POLICY_TYPE_ATTR_MIN_VALUE_S,
				range.min, NL_POLICY_TYPE_ATTR_PAD) ||
		    nla_put_s64(skb, NL_POLICY_TYPE_ATTR_MAX_VALUE_S,
				range.max, NL_POLICY_TYPE_ATTR_PAD))
			जाओ nla_put_failure;
		अवरोध;
	पूर्ण
	हाल NLA_BITFIELD32:
		type = NL_ATTR_TYPE_BITFIELD32;
		अगर (nla_put_u32(skb, NL_POLICY_TYPE_ATTR_BITFIELD32_MASK,
				pt->bitfield32_valid))
			जाओ nla_put_failure;
		अवरोध;
	हाल NLA_STRING:
	हाल NLA_NUL_STRING:
	हाल NLA_BINARY:
		अगर (pt->type == NLA_STRING)
			type = NL_ATTR_TYPE_STRING;
		अन्यथा अगर (pt->type == NLA_NUL_STRING)
			type = NL_ATTR_TYPE_NUL_STRING;
		अन्यथा
			type = NL_ATTR_TYPE_BINARY;

		अगर (pt->validation_type == NLA_VALIDATE_RANGE ||
		    pt->validation_type == NLA_VALIDATE_RANGE_WARN_TOO_LONG) अणु
			काष्ठा netlink_range_validation range;

			nla_get_range_अचिन्हित(pt, &range);

			अगर (range.min &&
			    nla_put_u32(skb, NL_POLICY_TYPE_ATTR_MIN_LENGTH,
					range.min))
				जाओ nla_put_failure;

			अगर (range.max < U16_MAX &&
			    nla_put_u32(skb, NL_POLICY_TYPE_ATTR_MAX_LENGTH,
					range.max))
				जाओ nla_put_failure;
		पूर्ण अन्यथा अगर (pt->len &&
			   nla_put_u32(skb, NL_POLICY_TYPE_ATTR_MAX_LENGTH,
				       pt->len)) अणु
			जाओ nla_put_failure;
		पूर्ण
		अवरोध;
	हाल NLA_FLAG:
		type = NL_ATTR_TYPE_FLAG;
		अवरोध;
	पूर्ण

	अगर (nla_put_u32(skb, NL_POLICY_TYPE_ATTR_TYPE, type))
		जाओ nla_put_failure;

	nla_nest_end(skb, attr);
	WARN_ON(attr->nla_len > estimate);

	वापस 0;
nla_put_failure:
	nla_nest_cancel(skb, attr);
	वापस -ENOBUFS;
पूर्ण

/**
 * netlink_policy_dump_ग_लिखो_attr - ग_लिखो a given attribute policy
 * @skb: the message skb to ग_लिखो to
 * @pt: the attribute's policy
 * @nestattr: the nested attribute ID to use
 *
 * Returns: 0 on success, an error code otherwise; -%ENODATA is
 *	    special, indicating that there's no policy data and
 *	    the attribute is generally rejected.
 */
पूर्णांक netlink_policy_dump_ग_लिखो_attr(काष्ठा sk_buff *skb,
				   स्थिर काष्ठा nla_policy *pt,
				   पूर्णांक nestattr)
अणु
	वापस __netlink_policy_dump_ग_लिखो_attr(शून्य, skb, pt, nestattr);
पूर्ण

/**
 * netlink_policy_dump_ग_लिखो - ग_लिखो current policy dump attributes
 * @skb: the message skb to ग_लिखो to
 * @state: the policy dump state
 *
 * Returns: 0 on success, an error code otherwise
 */
पूर्णांक netlink_policy_dump_ग_लिखो(काष्ठा sk_buff *skb,
			      काष्ठा netlink_policy_dump_state *state)
अणु
	स्थिर काष्ठा nla_policy *pt;
	काष्ठा nlattr *policy;
	bool again;
	पूर्णांक err;

send_attribute:
	again = false;

	pt = &state->policies[state->policy_idx].policy[state->attr_idx];

	policy = nla_nest_start(skb, state->policy_idx);
	अगर (!policy)
		वापस -ENOBUFS;

	err = __netlink_policy_dump_ग_लिखो_attr(state, skb, pt, state->attr_idx);
	अगर (err == -ENODATA) अणु
		nla_nest_cancel(skb, policy);
		again = true;
		जाओ next;
	पूर्ण अन्यथा अगर (err) अणु
		जाओ nla_put_failure;
	पूर्ण

	/* finish and move state to next attribute */
	nla_nest_end(skb, policy);

next:
	state->attr_idx += 1;
	अगर (state->attr_idx > state->policies[state->policy_idx].maxtype) अणु
		state->attr_idx = 0;
		state->policy_idx++;
	पूर्ण

	अगर (again) अणु
		अगर (netlink_policy_dump_finished(state))
			वापस -ENODATA;
		जाओ send_attribute;
	पूर्ण

	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, policy);
	वापस -ENOBUFS;
पूर्ण

/**
 * netlink_policy_dump_मुक्त - मुक्त policy dump state
 * @state: the policy dump state to मुक्त
 *
 * Call this from the करोne() method to ensure dump state is मुक्तd.
 */
व्योम netlink_policy_dump_मुक्त(काष्ठा netlink_policy_dump_state *state)
अणु
	kमुक्त(state);
पूर्ण
