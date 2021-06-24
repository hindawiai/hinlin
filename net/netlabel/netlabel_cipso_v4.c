<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NetLabel CIPSO/IPv4 Support
 *
 * This file defines the CIPSO/IPv4 functions क्रम the NetLabel प्रणाली.  The
 * NetLabel प्रणाली manages अटल and dynamic label mappings क्रम network
 * protocols such as CIPSO and RIPSO.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 */

#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/audit.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>
#समावेश <net/netlabel.h>
#समावेश <net/cipso_ipv4.h>
#समावेश <linux/atomic.h>

#समावेश "netlabel_user.h"
#समावेश "netlabel_cipso_v4.h"
#समावेश "netlabel_mgmt.h"
#समावेश "netlabel_domainhash.h"

/* Argument काष्ठा क्रम cipso_v4_करोi_walk() */
काष्ठा netlbl_cipsov4_करोiwalk_arg अणु
	काष्ठा netlink_callback *nl_cb;
	काष्ठा sk_buff *skb;
	u32 seq;
पूर्ण;

/* Argument काष्ठा क्रम netlbl_करोmhsh_walk() */
काष्ठा netlbl_करोmhsh_walk_arg अणु
	काष्ठा netlbl_audit *audit_info;
	u32 करोi;
पूर्ण;

/* NetLabel Generic NETLINK CIPSOv4 family */
अटल काष्ठा genl_family netlbl_cipsov4_gnl_family;
/* NetLabel Netlink attribute policy */
अटल स्थिर काष्ठा nla_policy netlbl_cipsov4_genl_policy[NLBL_CIPSOV4_A_MAX + 1] = अणु
	[NLBL_CIPSOV4_A_DOI] = अणु .type = NLA_U32 पूर्ण,
	[NLBL_CIPSOV4_A_MTYPE] = अणु .type = NLA_U32 पूर्ण,
	[NLBL_CIPSOV4_A_TAG] = अणु .type = NLA_U8 पूर्ण,
	[NLBL_CIPSOV4_A_TAGLST] = अणु .type = NLA_NESTED पूर्ण,
	[NLBL_CIPSOV4_A_MLSLVLLOC] = अणु .type = NLA_U32 पूर्ण,
	[NLBL_CIPSOV4_A_MLSLVLREM] = अणु .type = NLA_U32 पूर्ण,
	[NLBL_CIPSOV4_A_MLSLVL] = अणु .type = NLA_NESTED पूर्ण,
	[NLBL_CIPSOV4_A_MLSLVLLST] = अणु .type = NLA_NESTED पूर्ण,
	[NLBL_CIPSOV4_A_MLSCATLOC] = अणु .type = NLA_U32 पूर्ण,
	[NLBL_CIPSOV4_A_MLSCATREM] = अणु .type = NLA_U32 पूर्ण,
	[NLBL_CIPSOV4_A_MLSCAT] = अणु .type = NLA_NESTED पूर्ण,
	[NLBL_CIPSOV4_A_MLSCATLST] = अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

/*
 * Helper Functions
 */

/**
 * netlbl_cipsov4_add_common - Parse the common sections of a ADD message
 * @info: the Generic NETLINK info block
 * @करोi_def: the CIPSO V4 DOI definition
 *
 * Description:
 * Parse the common sections of a ADD message and fill in the related values
 * in @करोi_def.  Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_cipsov4_add_common(काष्ठा genl_info *info,
				     काष्ठा cipso_v4_करोi *करोi_def)
अणु
	काष्ठा nlattr *nla;
	पूर्णांक nla_rem;
	u32 iter = 0;

	करोi_def->करोi = nla_get_u32(info->attrs[NLBL_CIPSOV4_A_DOI]);

	अगर (nla_validate_nested_deprecated(info->attrs[NLBL_CIPSOV4_A_TAGLST],
					   NLBL_CIPSOV4_A_MAX,
					   netlbl_cipsov4_genl_policy,
					   शून्य) != 0)
		वापस -EINVAL;

	nla_क्रम_each_nested(nla, info->attrs[NLBL_CIPSOV4_A_TAGLST], nla_rem)
		अगर (nla_type(nla) == NLBL_CIPSOV4_A_TAG) अणु
			अगर (iter >= CIPSO_V4_TAG_MAXCNT)
				वापस -EINVAL;
			करोi_def->tags[iter++] = nla_get_u8(nla);
		पूर्ण
	जबतक (iter < CIPSO_V4_TAG_MAXCNT)
		करोi_def->tags[iter++] = CIPSO_V4_TAG_INVALID;

	वापस 0;
पूर्ण

/*
 * NetLabel Command Handlers
 */

/**
 * netlbl_cipsov4_add_std - Adds a CIPSO V4 DOI definition
 * @info: the Generic NETLINK info block
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Create a new CIPSO_V4_MAP_TRANS DOI definition based on the given ADD
 * message and add it to the CIPSO V4 engine.  Return zero on success and
 * non-zero on error.
 *
 */
अटल पूर्णांक netlbl_cipsov4_add_std(काष्ठा genl_info *info,
				  काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val = -EINVAL;
	काष्ठा cipso_v4_करोi *करोi_def = शून्य;
	काष्ठा nlattr *nla_a;
	काष्ठा nlattr *nla_b;
	पूर्णांक nla_a_rem;
	पूर्णांक nla_b_rem;
	u32 iter;

	अगर (!info->attrs[NLBL_CIPSOV4_A_TAGLST] ||
	    !info->attrs[NLBL_CIPSOV4_A_MLSLVLLST])
		वापस -EINVAL;

	अगर (nla_validate_nested_deprecated(info->attrs[NLBL_CIPSOV4_A_MLSLVLLST],
					   NLBL_CIPSOV4_A_MAX,
					   netlbl_cipsov4_genl_policy,
					   शून्य) != 0)
		वापस -EINVAL;

	करोi_def = kदो_स्मृति(माप(*करोi_def), GFP_KERNEL);
	अगर (करोi_def == शून्य)
		वापस -ENOMEM;
	करोi_def->map.std = kzalloc(माप(*करोi_def->map.std), GFP_KERNEL);
	अगर (करोi_def->map.std == शून्य) अणु
		ret_val = -ENOMEM;
		जाओ add_std_failure;
	पूर्ण
	करोi_def->type = CIPSO_V4_MAP_TRANS;

	ret_val = netlbl_cipsov4_add_common(info, करोi_def);
	अगर (ret_val != 0)
		जाओ add_std_failure;
	ret_val = -EINVAL;

	nla_क्रम_each_nested(nla_a,
			    info->attrs[NLBL_CIPSOV4_A_MLSLVLLST],
			    nla_a_rem)
		अगर (nla_type(nla_a) == NLBL_CIPSOV4_A_MLSLVL) अणु
			अगर (nla_validate_nested_deprecated(nla_a,
							   NLBL_CIPSOV4_A_MAX,
							   netlbl_cipsov4_genl_policy,
							   शून्य) != 0)
				जाओ add_std_failure;
			nla_क्रम_each_nested(nla_b, nla_a, nla_b_rem)
				चयन (nla_type(nla_b)) अणु
				हाल NLBL_CIPSOV4_A_MLSLVLLOC:
					अगर (nla_get_u32(nla_b) >
					    CIPSO_V4_MAX_LOC_LVLS)
						जाओ add_std_failure;
					अगर (nla_get_u32(nla_b) >=
					    करोi_def->map.std->lvl.local_size)
					     करोi_def->map.std->lvl.local_size =
						     nla_get_u32(nla_b) + 1;
					अवरोध;
				हाल NLBL_CIPSOV4_A_MLSLVLREM:
					अगर (nla_get_u32(nla_b) >
					    CIPSO_V4_MAX_REM_LVLS)
						जाओ add_std_failure;
					अगर (nla_get_u32(nla_b) >=
					    करोi_def->map.std->lvl.cipso_size)
					     करोi_def->map.std->lvl.cipso_size =
						     nla_get_u32(nla_b) + 1;
					अवरोध;
				पूर्ण
		पूर्ण
	करोi_def->map.std->lvl.local = kसुस्मृति(करोi_def->map.std->lvl.local_size,
					      माप(u32),
					      GFP_KERNEL);
	अगर (करोi_def->map.std->lvl.local == शून्य) अणु
		ret_val = -ENOMEM;
		जाओ add_std_failure;
	पूर्ण
	करोi_def->map.std->lvl.cipso = kसुस्मृति(करोi_def->map.std->lvl.cipso_size,
					      माप(u32),
					      GFP_KERNEL);
	अगर (करोi_def->map.std->lvl.cipso == शून्य) अणु
		ret_val = -ENOMEM;
		जाओ add_std_failure;
	पूर्ण
	क्रम (iter = 0; iter < करोi_def->map.std->lvl.local_size; iter++)
		करोi_def->map.std->lvl.local[iter] = CIPSO_V4_INV_LVL;
	क्रम (iter = 0; iter < करोi_def->map.std->lvl.cipso_size; iter++)
		करोi_def->map.std->lvl.cipso[iter] = CIPSO_V4_INV_LVL;
	nla_क्रम_each_nested(nla_a,
			    info->attrs[NLBL_CIPSOV4_A_MLSLVLLST],
			    nla_a_rem)
		अगर (nla_type(nla_a) == NLBL_CIPSOV4_A_MLSLVL) अणु
			काष्ठा nlattr *lvl_loc;
			काष्ठा nlattr *lvl_rem;

			lvl_loc = nla_find_nested(nla_a,
						  NLBL_CIPSOV4_A_MLSLVLLOC);
			lvl_rem = nla_find_nested(nla_a,
						  NLBL_CIPSOV4_A_MLSLVLREM);
			अगर (lvl_loc == शून्य || lvl_rem == शून्य)
				जाओ add_std_failure;
			करोi_def->map.std->lvl.local[nla_get_u32(lvl_loc)] =
				nla_get_u32(lvl_rem);
			करोi_def->map.std->lvl.cipso[nla_get_u32(lvl_rem)] =
				nla_get_u32(lvl_loc);
		पूर्ण

	अगर (info->attrs[NLBL_CIPSOV4_A_MLSCATLST]) अणु
		अगर (nla_validate_nested_deprecated(info->attrs[NLBL_CIPSOV4_A_MLSCATLST],
						   NLBL_CIPSOV4_A_MAX,
						   netlbl_cipsov4_genl_policy,
						   शून्य) != 0)
			जाओ add_std_failure;

		nla_क्रम_each_nested(nla_a,
				    info->attrs[NLBL_CIPSOV4_A_MLSCATLST],
				    nla_a_rem)
			अगर (nla_type(nla_a) == NLBL_CIPSOV4_A_MLSCAT) अणु
				अगर (nla_validate_nested_deprecated(nla_a,
								   NLBL_CIPSOV4_A_MAX,
								   netlbl_cipsov4_genl_policy,
								   शून्य) != 0)
					जाओ add_std_failure;
				nla_क्रम_each_nested(nla_b, nla_a, nla_b_rem)
					चयन (nla_type(nla_b)) अणु
					हाल NLBL_CIPSOV4_A_MLSCATLOC:
						अगर (nla_get_u32(nla_b) >
						    CIPSO_V4_MAX_LOC_CATS)
							जाओ add_std_failure;
						अगर (nla_get_u32(nla_b) >=
					      करोi_def->map.std->cat.local_size)
					     करोi_def->map.std->cat.local_size =
						     nla_get_u32(nla_b) + 1;
						अवरोध;
					हाल NLBL_CIPSOV4_A_MLSCATREM:
						अगर (nla_get_u32(nla_b) >
						    CIPSO_V4_MAX_REM_CATS)
							जाओ add_std_failure;
						अगर (nla_get_u32(nla_b) >=
					      करोi_def->map.std->cat.cipso_size)
					     करोi_def->map.std->cat.cipso_size =
						     nla_get_u32(nla_b) + 1;
						अवरोध;
					पूर्ण
			पूर्ण
		करोi_def->map.std->cat.local = kसुस्मृति(
					      करोi_def->map.std->cat.local_size,
					      माप(u32),
					      GFP_KERNEL);
		अगर (करोi_def->map.std->cat.local == शून्य) अणु
			ret_val = -ENOMEM;
			जाओ add_std_failure;
		पूर्ण
		करोi_def->map.std->cat.cipso = kसुस्मृति(
					      करोi_def->map.std->cat.cipso_size,
					      माप(u32),
					      GFP_KERNEL);
		अगर (करोi_def->map.std->cat.cipso == शून्य) अणु
			ret_val = -ENOMEM;
			जाओ add_std_failure;
		पूर्ण
		क्रम (iter = 0; iter < करोi_def->map.std->cat.local_size; iter++)
			करोi_def->map.std->cat.local[iter] = CIPSO_V4_INV_CAT;
		क्रम (iter = 0; iter < करोi_def->map.std->cat.cipso_size; iter++)
			करोi_def->map.std->cat.cipso[iter] = CIPSO_V4_INV_CAT;
		nla_क्रम_each_nested(nla_a,
				    info->attrs[NLBL_CIPSOV4_A_MLSCATLST],
				    nla_a_rem)
			अगर (nla_type(nla_a) == NLBL_CIPSOV4_A_MLSCAT) अणु
				काष्ठा nlattr *cat_loc;
				काष्ठा nlattr *cat_rem;

				cat_loc = nla_find_nested(nla_a,
						     NLBL_CIPSOV4_A_MLSCATLOC);
				cat_rem = nla_find_nested(nla_a,
						     NLBL_CIPSOV4_A_MLSCATREM);
				अगर (cat_loc == शून्य || cat_rem == शून्य)
					जाओ add_std_failure;
				करोi_def->map.std->cat.local[
							nla_get_u32(cat_loc)] =
					nla_get_u32(cat_rem);
				करोi_def->map.std->cat.cipso[
							nla_get_u32(cat_rem)] =
					nla_get_u32(cat_loc);
			पूर्ण
	पूर्ण

	ret_val = cipso_v4_करोi_add(करोi_def, audit_info);
	अगर (ret_val != 0)
		जाओ add_std_failure;
	वापस 0;

add_std_failure:
	cipso_v4_करोi_मुक्त(करोi_def);
	वापस ret_val;
पूर्ण

/**
 * netlbl_cipsov4_add_pass - Adds a CIPSO V4 DOI definition
 * @info: the Generic NETLINK info block
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Create a new CIPSO_V4_MAP_PASS DOI definition based on the given ADD message
 * and add it to the CIPSO V4 engine.  Return zero on success and non-zero on
 * error.
 *
 */
अटल पूर्णांक netlbl_cipsov4_add_pass(काष्ठा genl_info *info,
				   काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val;
	काष्ठा cipso_v4_करोi *करोi_def = शून्य;

	अगर (!info->attrs[NLBL_CIPSOV4_A_TAGLST])
		वापस -EINVAL;

	करोi_def = kदो_स्मृति(माप(*करोi_def), GFP_KERNEL);
	अगर (करोi_def == शून्य)
		वापस -ENOMEM;
	करोi_def->type = CIPSO_V4_MAP_PASS;

	ret_val = netlbl_cipsov4_add_common(info, करोi_def);
	अगर (ret_val != 0)
		जाओ add_pass_failure;

	ret_val = cipso_v4_करोi_add(करोi_def, audit_info);
	अगर (ret_val != 0)
		जाओ add_pass_failure;
	वापस 0;

add_pass_failure:
	cipso_v4_करोi_मुक्त(करोi_def);
	वापस ret_val;
पूर्ण

/**
 * netlbl_cipsov4_add_local - Adds a CIPSO V4 DOI definition
 * @info: the Generic NETLINK info block
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Create a new CIPSO_V4_MAP_LOCAL DOI definition based on the given ADD
 * message and add it to the CIPSO V4 engine.  Return zero on success and
 * non-zero on error.
 *
 */
अटल पूर्णांक netlbl_cipsov4_add_local(काष्ठा genl_info *info,
				    काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val;
	काष्ठा cipso_v4_करोi *करोi_def = शून्य;

	अगर (!info->attrs[NLBL_CIPSOV4_A_TAGLST])
		वापस -EINVAL;

	करोi_def = kदो_स्मृति(माप(*करोi_def), GFP_KERNEL);
	अगर (करोi_def == शून्य)
		वापस -ENOMEM;
	करोi_def->type = CIPSO_V4_MAP_LOCAL;

	ret_val = netlbl_cipsov4_add_common(info, करोi_def);
	अगर (ret_val != 0)
		जाओ add_local_failure;

	ret_val = cipso_v4_करोi_add(करोi_def, audit_info);
	अगर (ret_val != 0)
		जाओ add_local_failure;
	वापस 0;

add_local_failure:
	cipso_v4_करोi_मुक्त(करोi_def);
	वापस ret_val;
पूर्ण

/**
 * netlbl_cipsov4_add - Handle an ADD message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Create a new DOI definition based on the given ADD message and add it to the
 * CIPSO V4 engine.  Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_cipsov4_add(काष्ठा sk_buff *skb, काष्ठा genl_info *info)

अणु
	पूर्णांक ret_val = -EINVAL;
	काष्ठा netlbl_audit audit_info;

	अगर (!info->attrs[NLBL_CIPSOV4_A_DOI] ||
	    !info->attrs[NLBL_CIPSOV4_A_MTYPE])
		वापस -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);
	चयन (nla_get_u32(info->attrs[NLBL_CIPSOV4_A_MTYPE])) अणु
	हाल CIPSO_V4_MAP_TRANS:
		ret_val = netlbl_cipsov4_add_std(info, &audit_info);
		अवरोध;
	हाल CIPSO_V4_MAP_PASS:
		ret_val = netlbl_cipsov4_add_pass(info, &audit_info);
		अवरोध;
	हाल CIPSO_V4_MAP_LOCAL:
		ret_val = netlbl_cipsov4_add_local(info, &audit_info);
		अवरोध;
	पूर्ण
	अगर (ret_val == 0)
		atomic_inc(&netlabel_mgmt_protocount);

	वापस ret_val;
पूर्ण

/**
 * netlbl_cipsov4_list - Handle a LIST message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated LIST message and respond accordingly.  While the
 * response message generated by the kernel is straightक्रमward, determining
 * beक्रमe hand the size of the buffer to allocate is not (we have to generate
 * the message to know the size).  In order to keep this function sane what we
 * करो is allocate a buffer of NLMSG_GOODSIZE and try to fit the response in
 * that size, अगर we fail then we restart with a larger buffer and try again.
 * We जारी in this manner until we hit a limit of failed attempts then we
 * give up and just send an error message.  Returns zero on success and
 * negative values on error.
 *
 */
अटल पूर्णांक netlbl_cipsov4_list(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक ret_val;
	काष्ठा sk_buff *ans_skb = शून्य;
	u32 nlsze_mult = 1;
	व्योम *data;
	u32 करोi;
	काष्ठा nlattr *nla_a;
	काष्ठा nlattr *nla_b;
	काष्ठा cipso_v4_करोi *करोi_def;
	u32 iter;

	अगर (!info->attrs[NLBL_CIPSOV4_A_DOI]) अणु
		ret_val = -EINVAL;
		जाओ list_failure;
	पूर्ण

list_start:
	ans_skb = nlmsg_new(NLMSG_DEFAULT_SIZE * nlsze_mult, GFP_KERNEL);
	अगर (ans_skb == शून्य) अणु
		ret_val = -ENOMEM;
		जाओ list_failure;
	पूर्ण
	data = genlmsg_put_reply(ans_skb, info, &netlbl_cipsov4_gnl_family,
				 0, NLBL_CIPSOV4_C_LIST);
	अगर (data == शून्य) अणु
		ret_val = -ENOMEM;
		जाओ list_failure;
	पूर्ण

	करोi = nla_get_u32(info->attrs[NLBL_CIPSOV4_A_DOI]);

	rcu_पढ़ो_lock();
	करोi_def = cipso_v4_करोi_getdef(करोi);
	अगर (करोi_def == शून्य) अणु
		ret_val = -EINVAL;
		जाओ list_failure_lock;
	पूर्ण

	ret_val = nla_put_u32(ans_skb, NLBL_CIPSOV4_A_MTYPE, करोi_def->type);
	अगर (ret_val != 0)
		जाओ list_failure_lock;

	nla_a = nla_nest_start_noflag(ans_skb, NLBL_CIPSOV4_A_TAGLST);
	अगर (nla_a == शून्य) अणु
		ret_val = -ENOMEM;
		जाओ list_failure_lock;
	पूर्ण
	क्रम (iter = 0;
	     iter < CIPSO_V4_TAG_MAXCNT &&
	       करोi_def->tags[iter] != CIPSO_V4_TAG_INVALID;
	     iter++) अणु
		ret_val = nla_put_u8(ans_skb,
				     NLBL_CIPSOV4_A_TAG,
				     करोi_def->tags[iter]);
		अगर (ret_val != 0)
			जाओ list_failure_lock;
	पूर्ण
	nla_nest_end(ans_skb, nla_a);

	चयन (करोi_def->type) अणु
	हाल CIPSO_V4_MAP_TRANS:
		nla_a = nla_nest_start_noflag(ans_skb,
					      NLBL_CIPSOV4_A_MLSLVLLST);
		अगर (nla_a == शून्य) अणु
			ret_val = -ENOMEM;
			जाओ list_failure_lock;
		पूर्ण
		क्रम (iter = 0;
		     iter < करोi_def->map.std->lvl.local_size;
		     iter++) अणु
			अगर (करोi_def->map.std->lvl.local[iter] ==
			    CIPSO_V4_INV_LVL)
				जारी;

			nla_b = nla_nest_start_noflag(ans_skb,
						      NLBL_CIPSOV4_A_MLSLVL);
			अगर (nla_b == शून्य) अणु
				ret_val = -ENOMEM;
				जाओ list_retry;
			पूर्ण
			ret_val = nla_put_u32(ans_skb,
					      NLBL_CIPSOV4_A_MLSLVLLOC,
					      iter);
			अगर (ret_val != 0)
				जाओ list_retry;
			ret_val = nla_put_u32(ans_skb,
					    NLBL_CIPSOV4_A_MLSLVLREM,
					    करोi_def->map.std->lvl.local[iter]);
			अगर (ret_val != 0)
				जाओ list_retry;
			nla_nest_end(ans_skb, nla_b);
		पूर्ण
		nla_nest_end(ans_skb, nla_a);

		nla_a = nla_nest_start_noflag(ans_skb,
					      NLBL_CIPSOV4_A_MLSCATLST);
		अगर (nla_a == शून्य) अणु
			ret_val = -ENOMEM;
			जाओ list_retry;
		पूर्ण
		क्रम (iter = 0;
		     iter < करोi_def->map.std->cat.local_size;
		     iter++) अणु
			अगर (करोi_def->map.std->cat.local[iter] ==
			    CIPSO_V4_INV_CAT)
				जारी;

			nla_b = nla_nest_start_noflag(ans_skb,
						      NLBL_CIPSOV4_A_MLSCAT);
			अगर (nla_b == शून्य) अणु
				ret_val = -ENOMEM;
				जाओ list_retry;
			पूर्ण
			ret_val = nla_put_u32(ans_skb,
					      NLBL_CIPSOV4_A_MLSCATLOC,
					      iter);
			अगर (ret_val != 0)
				जाओ list_retry;
			ret_val = nla_put_u32(ans_skb,
					    NLBL_CIPSOV4_A_MLSCATREM,
					    करोi_def->map.std->cat.local[iter]);
			अगर (ret_val != 0)
				जाओ list_retry;
			nla_nest_end(ans_skb, nla_b);
		पूर्ण
		nla_nest_end(ans_skb, nla_a);

		अवरोध;
	पूर्ण
	cipso_v4_करोi_putdef(करोi_def);
	rcu_पढ़ो_unlock();

	genlmsg_end(ans_skb, data);
	वापस genlmsg_reply(ans_skb, info);

list_retry:
	/* XXX - this limit is a guesstimate */
	अगर (nlsze_mult < 4) अणु
		cipso_v4_करोi_putdef(करोi_def);
		rcu_पढ़ो_unlock();
		kमुक्त_skb(ans_skb);
		nlsze_mult *= 2;
		जाओ list_start;
	पूर्ण
list_failure_lock:
	cipso_v4_करोi_putdef(करोi_def);
	rcu_पढ़ो_unlock();
list_failure:
	kमुक्त_skb(ans_skb);
	वापस ret_val;
पूर्ण

/**
 * netlbl_cipsov4_listall_cb - cipso_v4_करोi_walk() callback क्रम LISTALL
 * @करोi_def: the CIPSOv4 DOI definition
 * @arg: the netlbl_cipsov4_करोiwalk_arg काष्ठाure
 *
 * Description:
 * This function is deचिन्हित to be used as a callback to the
 * cipso_v4_करोi_walk() function क्रम use in generating a response क्रम a LISTALL
 * message.  Returns the size of the message on success, negative values on
 * failure.
 *
 */
अटल पूर्णांक netlbl_cipsov4_listall_cb(काष्ठा cipso_v4_करोi *करोi_def, व्योम *arg)
अणु
	पूर्णांक ret_val = -ENOMEM;
	काष्ठा netlbl_cipsov4_करोiwalk_arg *cb_arg = arg;
	व्योम *data;

	data = genlmsg_put(cb_arg->skb, NETLINK_CB(cb_arg->nl_cb->skb).portid,
			   cb_arg->seq, &netlbl_cipsov4_gnl_family,
			   NLM_F_MULTI, NLBL_CIPSOV4_C_LISTALL);
	अगर (data == शून्य)
		जाओ listall_cb_failure;

	ret_val = nla_put_u32(cb_arg->skb, NLBL_CIPSOV4_A_DOI, करोi_def->करोi);
	अगर (ret_val != 0)
		जाओ listall_cb_failure;
	ret_val = nla_put_u32(cb_arg->skb,
			      NLBL_CIPSOV4_A_MTYPE,
			      करोi_def->type);
	अगर (ret_val != 0)
		जाओ listall_cb_failure;

	genlmsg_end(cb_arg->skb, data);
	वापस 0;

listall_cb_failure:
	genlmsg_cancel(cb_arg->skb, data);
	वापस ret_val;
पूर्ण

/**
 * netlbl_cipsov4_listall - Handle a LISTALL message
 * @skb: the NETLINK buffer
 * @cb: the NETLINK callback
 *
 * Description:
 * Process a user generated LISTALL message and respond accordingly.  Returns
 * zero on success and negative values on error.
 *
 */
अटल पूर्णांक netlbl_cipsov4_listall(काष्ठा sk_buff *skb,
				  काष्ठा netlink_callback *cb)
अणु
	काष्ठा netlbl_cipsov4_करोiwalk_arg cb_arg;
	u32 करोi_skip = cb->args[0];

	cb_arg.nl_cb = cb;
	cb_arg.skb = skb;
	cb_arg.seq = cb->nlh->nlmsg_seq;

	cipso_v4_करोi_walk(&करोi_skip, netlbl_cipsov4_listall_cb, &cb_arg);

	cb->args[0] = करोi_skip;
	वापस skb->len;
पूर्ण

/**
 * netlbl_cipsov4_हटाओ_cb - netlbl_cipsov4_हटाओ() callback क्रम REMOVE
 * @entry: LSM करोमुख्य mapping entry
 * @arg: the netlbl_करोmhsh_walk_arg काष्ठाure
 *
 * Description:
 * This function is पूर्णांकended क्रम use by netlbl_cipsov4_हटाओ() as the callback
 * क्रम the netlbl_करोmhsh_walk() function; it हटाओs LSM करोमुख्य map entries
 * which are associated with the CIPSO DOI specअगरied in @arg.  Returns zero on
 * success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_cipsov4_हटाओ_cb(काष्ठा netlbl_करोm_map *entry, व्योम *arg)
अणु
	काष्ठा netlbl_करोmhsh_walk_arg *cb_arg = arg;

	अगर (entry->def.type == NETLBL_NLTYPE_CIPSOV4 &&
	    entry->def.cipso->करोi == cb_arg->करोi)
		वापस netlbl_करोmhsh_हटाओ_entry(entry, cb_arg->audit_info);

	वापस 0;
पूर्ण

/**
 * netlbl_cipsov4_हटाओ - Handle a REMOVE message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated REMOVE message and respond accordingly.  Returns
 * zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_cipsov4_हटाओ(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक ret_val = -EINVAL;
	काष्ठा netlbl_करोmhsh_walk_arg cb_arg;
	काष्ठा netlbl_audit audit_info;
	u32 skip_bkt = 0;
	u32 skip_chain = 0;

	अगर (!info->attrs[NLBL_CIPSOV4_A_DOI])
		वापस -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);
	cb_arg.करोi = nla_get_u32(info->attrs[NLBL_CIPSOV4_A_DOI]);
	cb_arg.audit_info = &audit_info;
	ret_val = netlbl_करोmhsh_walk(&skip_bkt, &skip_chain,
				     netlbl_cipsov4_हटाओ_cb, &cb_arg);
	अगर (ret_val == 0 || ret_val == -ENOENT) अणु
		ret_val = cipso_v4_करोi_हटाओ(cb_arg.करोi, &audit_info);
		अगर (ret_val == 0)
			atomic_dec(&netlabel_mgmt_protocount);
	पूर्ण

	वापस ret_val;
पूर्ण

/*
 * NetLabel Generic NETLINK Command Definitions
 */

अटल स्थिर काष्ठा genl_small_ops netlbl_cipsov4_ops[] = अणु
	अणु
	.cmd = NLBL_CIPSOV4_C_ADD,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = GENL_ADMIN_PERM,
	.करोit = netlbl_cipsov4_add,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_CIPSOV4_C_REMOVE,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = GENL_ADMIN_PERM,
	.करोit = netlbl_cipsov4_हटाओ,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_CIPSOV4_C_LIST,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = 0,
	.करोit = netlbl_cipsov4_list,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_CIPSOV4_C_LISTALL,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = 0,
	.करोit = शून्य,
	.dumpit = netlbl_cipsov4_listall,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family netlbl_cipsov4_gnl_family __ro_after_init = अणु
	.hdrsize = 0,
	.name = NETLBL_NLTYPE_CIPSOV4_NAME,
	.version = NETLBL_PROTO_VERSION,
	.maxattr = NLBL_CIPSOV4_A_MAX,
	.policy = netlbl_cipsov4_genl_policy,
	.module = THIS_MODULE,
	.small_ops = netlbl_cipsov4_ops,
	.n_small_ops = ARRAY_SIZE(netlbl_cipsov4_ops),
पूर्ण;

/*
 * NetLabel Generic NETLINK Protocol Functions
 */

/**
 * netlbl_cipsov4_genl_init - Register the CIPSOv4 NetLabel component
 *
 * Description:
 * Register the CIPSOv4 packet NetLabel component with the Generic NETLINK
 * mechanism.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक __init netlbl_cipsov4_genl_init(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&netlbl_cipsov4_gnl_family);
पूर्ण
