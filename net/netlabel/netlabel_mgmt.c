<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NetLabel Management Support
 *
 * This file defines the management functions क्रम the NetLabel प्रणाली.  The
 * NetLabel प्रणाली manages अटल and dynamic label mappings क्रम network
 * protocols such as CIPSO and RIPSO.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006, 2008
 */

#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/माला.स>
#समावेश <linux/skbuff.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/netlabel.h>
#समावेश <net/cipso_ipv4.h>
#समावेश <net/calipso.h>
#समावेश <linux/atomic.h>

#समावेश "netlabel_calipso.h"
#समावेश "netlabel_domainhash.h"
#समावेश "netlabel_user.h"
#समावेश "netlabel_mgmt.h"

/* NetLabel configured protocol counter */
atomic_t netlabel_mgmt_protocount = ATOMIC_INIT(0);

/* Argument काष्ठा क्रम netlbl_करोmhsh_walk() */
काष्ठा netlbl_करोmhsh_walk_arg अणु
	काष्ठा netlink_callback *nl_cb;
	काष्ठा sk_buff *skb;
	u32 seq;
पूर्ण;

/* NetLabel Generic NETLINK CIPSOv4 family */
अटल काष्ठा genl_family netlbl_mgmt_gnl_family;

/* NetLabel Netlink attribute policy */
अटल स्थिर काष्ठा nla_policy netlbl_mgmt_genl_policy[NLBL_MGMT_A_MAX + 1] = अणु
	[NLBL_MGMT_A_DOMAIN] = अणु .type = NLA_NUL_STRING पूर्ण,
	[NLBL_MGMT_A_PROTOCOL] = अणु .type = NLA_U32 पूर्ण,
	[NLBL_MGMT_A_VERSION] = अणु .type = NLA_U32 पूर्ण,
	[NLBL_MGMT_A_CV4DOI] = अणु .type = NLA_U32 पूर्ण,
	[NLBL_MGMT_A_FAMILY] = अणु .type = NLA_U16 पूर्ण,
	[NLBL_MGMT_A_CLPDOI] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

/*
 * Helper Functions
 */

/**
 * netlbl_mgmt_add_common - Handle an ADD message
 * @info: the Generic NETLINK info block
 * @audit_info: NetLabel audit inक्रमmation
 *
 * Description:
 * Helper function क्रम the ADD and ADDDEF messages to add the करोमुख्य mappings
 * from the message to the hash table.  See netlabel.h क्रम a description of the
 * message क्रमmat.  Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_mgmt_add_common(काष्ठा genl_info *info,
				  काष्ठा netlbl_audit *audit_info)
अणु
	पूर्णांक ret_val = -EINVAL;
	काष्ठा netlbl_करोmaddr_map *addrmap = शून्य;
	काष्ठा cipso_v4_करोi *cipsov4 = शून्य;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा calipso_करोi *calipso = शून्य;
#पूर्ण_अगर
	u32 पंचांगp_val;
	काष्ठा netlbl_करोm_map *entry = kzalloc(माप(*entry), GFP_KERNEL);

	अगर (!entry)
		वापस -ENOMEM;
	entry->def.type = nla_get_u32(info->attrs[NLBL_MGMT_A_PROTOCOL]);
	अगर (info->attrs[NLBL_MGMT_A_DOMAIN]) अणु
		माप_प्रकार पंचांगp_size = nla_len(info->attrs[NLBL_MGMT_A_DOMAIN]);
		entry->करोमुख्य = kदो_स्मृति(पंचांगp_size, GFP_KERNEL);
		अगर (entry->करोमुख्य == शून्य) अणु
			ret_val = -ENOMEM;
			जाओ add_मुक्त_entry;
		पूर्ण
		nla_strscpy(entry->करोमुख्य,
			    info->attrs[NLBL_MGMT_A_DOMAIN], पंचांगp_size);
	पूर्ण

	/* NOTE: पूर्णांकernally we allow/use a entry->def.type value of
	 *       NETLBL_NLTYPE_ADDRSELECT but we करोn't currently allow users
	 *       to pass that as a protocol value because we need to know the
	 *       "real" protocol */

	चयन (entry->def.type) अणु
	हाल NETLBL_NLTYPE_UNLABELED:
		अगर (info->attrs[NLBL_MGMT_A_FAMILY])
			entry->family =
				nla_get_u16(info->attrs[NLBL_MGMT_A_FAMILY]);
		अन्यथा
			entry->family = AF_UNSPEC;
		अवरोध;
	हाल NETLBL_NLTYPE_CIPSOV4:
		अगर (!info->attrs[NLBL_MGMT_A_CV4DOI])
			जाओ add_मुक्त_करोमुख्य;

		पंचांगp_val = nla_get_u32(info->attrs[NLBL_MGMT_A_CV4DOI]);
		cipsov4 = cipso_v4_करोi_getdef(पंचांगp_val);
		अगर (cipsov4 == शून्य)
			जाओ add_मुक्त_करोमुख्य;
		entry->family = AF_INET;
		entry->def.cipso = cipsov4;
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल NETLBL_NLTYPE_CALIPSO:
		अगर (!info->attrs[NLBL_MGMT_A_CLPDOI])
			जाओ add_मुक्त_करोमुख्य;

		पंचांगp_val = nla_get_u32(info->attrs[NLBL_MGMT_A_CLPDOI]);
		calipso = calipso_करोi_getdef(पंचांगp_val);
		अगर (calipso == शून्य)
			जाओ add_मुक्त_करोमुख्य;
		entry->family = AF_INET6;
		entry->def.calipso = calipso;
		अवरोध;
#पूर्ण_अगर /* IPv6 */
	शेष:
		जाओ add_मुक्त_करोमुख्य;
	पूर्ण

	अगर ((entry->family == AF_INET && info->attrs[NLBL_MGMT_A_IPV6ADDR]) ||
	    (entry->family == AF_INET6 && info->attrs[NLBL_MGMT_A_IPV4ADDR]))
		जाओ add_करोi_put_def;

	अगर (info->attrs[NLBL_MGMT_A_IPV4ADDR]) अणु
		काष्ठा in_addr *addr;
		काष्ठा in_addr *mask;
		काष्ठा netlbl_करोmaddr4_map *map;

		addrmap = kzalloc(माप(*addrmap), GFP_KERNEL);
		अगर (addrmap == शून्य) अणु
			ret_val = -ENOMEM;
			जाओ add_करोi_put_def;
		पूर्ण
		INIT_LIST_HEAD(&addrmap->list4);
		INIT_LIST_HEAD(&addrmap->list6);

		अगर (nla_len(info->attrs[NLBL_MGMT_A_IPV4ADDR]) !=
		    माप(काष्ठा in_addr)) अणु
			ret_val = -EINVAL;
			जाओ add_मुक्त_addrmap;
		पूर्ण
		अगर (nla_len(info->attrs[NLBL_MGMT_A_IPV4MASK]) !=
		    माप(काष्ठा in_addr)) अणु
			ret_val = -EINVAL;
			जाओ add_मुक्त_addrmap;
		पूर्ण
		addr = nla_data(info->attrs[NLBL_MGMT_A_IPV4ADDR]);
		mask = nla_data(info->attrs[NLBL_MGMT_A_IPV4MASK]);

		map = kzalloc(माप(*map), GFP_KERNEL);
		अगर (map == शून्य) अणु
			ret_val = -ENOMEM;
			जाओ add_मुक्त_addrmap;
		पूर्ण
		map->list.addr = addr->s_addr & mask->s_addr;
		map->list.mask = mask->s_addr;
		map->list.valid = 1;
		map->def.type = entry->def.type;
		अगर (cipsov4)
			map->def.cipso = cipsov4;

		ret_val = netlbl_af4list_add(&map->list, &addrmap->list4);
		अगर (ret_val != 0) अणु
			kमुक्त(map);
			जाओ add_मुक्त_addrmap;
		पूर्ण

		entry->family = AF_INET;
		entry->def.type = NETLBL_NLTYPE_ADDRSELECT;
		entry->def.addrsel = addrmap;
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्ण अन्यथा अगर (info->attrs[NLBL_MGMT_A_IPV6ADDR]) अणु
		काष्ठा in6_addr *addr;
		काष्ठा in6_addr *mask;
		काष्ठा netlbl_करोmaddr6_map *map;

		addrmap = kzalloc(माप(*addrmap), GFP_KERNEL);
		अगर (addrmap == शून्य) अणु
			ret_val = -ENOMEM;
			जाओ add_करोi_put_def;
		पूर्ण
		INIT_LIST_HEAD(&addrmap->list4);
		INIT_LIST_HEAD(&addrmap->list6);

		अगर (nla_len(info->attrs[NLBL_MGMT_A_IPV6ADDR]) !=
		    माप(काष्ठा in6_addr)) अणु
			ret_val = -EINVAL;
			जाओ add_मुक्त_addrmap;
		पूर्ण
		अगर (nla_len(info->attrs[NLBL_MGMT_A_IPV6MASK]) !=
		    माप(काष्ठा in6_addr)) अणु
			ret_val = -EINVAL;
			जाओ add_मुक्त_addrmap;
		पूर्ण
		addr = nla_data(info->attrs[NLBL_MGMT_A_IPV6ADDR]);
		mask = nla_data(info->attrs[NLBL_MGMT_A_IPV6MASK]);

		map = kzalloc(माप(*map), GFP_KERNEL);
		अगर (map == शून्य) अणु
			ret_val = -ENOMEM;
			जाओ add_मुक्त_addrmap;
		पूर्ण
		map->list.addr = *addr;
		map->list.addr.s6_addr32[0] &= mask->s6_addr32[0];
		map->list.addr.s6_addr32[1] &= mask->s6_addr32[1];
		map->list.addr.s6_addr32[2] &= mask->s6_addr32[2];
		map->list.addr.s6_addr32[3] &= mask->s6_addr32[3];
		map->list.mask = *mask;
		map->list.valid = 1;
		map->def.type = entry->def.type;
		अगर (calipso)
			map->def.calipso = calipso;

		ret_val = netlbl_af6list_add(&map->list, &addrmap->list6);
		अगर (ret_val != 0) अणु
			kमुक्त(map);
			जाओ add_मुक्त_addrmap;
		पूर्ण

		entry->family = AF_INET6;
		entry->def.type = NETLBL_NLTYPE_ADDRSELECT;
		entry->def.addrsel = addrmap;
#पूर्ण_अगर /* IPv6 */
	पूर्ण

	ret_val = netlbl_करोmhsh_add(entry, audit_info);
	अगर (ret_val != 0)
		जाओ add_मुक्त_addrmap;

	वापस 0;

add_मुक्त_addrmap:
	kमुक्त(addrmap);
add_करोi_put_def:
	cipso_v4_करोi_putdef(cipsov4);
#अगर IS_ENABLED(CONFIG_IPV6)
	calipso_करोi_putdef(calipso);
#पूर्ण_अगर
add_मुक्त_करोमुख्य:
	kमुक्त(entry->करोमुख्य);
add_मुक्त_entry:
	kमुक्त(entry);
	वापस ret_val;
पूर्ण

/**
 * netlbl_mgmt_listentry - List a NetLabel/LSM करोमुख्य map entry
 * @skb: the NETLINK buffer
 * @entry: the map entry
 *
 * Description:
 * This function is a helper function used by the LISTALL and LISTDEF command
 * handlers.  The caller is responsible क्रम ensuring that the RCU पढ़ो lock
 * is held.  Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_mgmt_listentry(काष्ठा sk_buff *skb,
				 काष्ठा netlbl_करोm_map *entry)
अणु
	पूर्णांक ret_val = 0;
	काष्ठा nlattr *nla_a;
	काष्ठा nlattr *nla_b;
	काष्ठा netlbl_af4list *iter4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा netlbl_af6list *iter6;
#पूर्ण_अगर

	अगर (entry->करोमुख्य != शून्य) अणु
		ret_val = nla_put_string(skb,
					 NLBL_MGMT_A_DOMAIN, entry->करोमुख्य);
		अगर (ret_val != 0)
			वापस ret_val;
	पूर्ण

	ret_val = nla_put_u16(skb, NLBL_MGMT_A_FAMILY, entry->family);
	अगर (ret_val != 0)
		वापस ret_val;

	चयन (entry->def.type) अणु
	हाल NETLBL_NLTYPE_ADDRSELECT:
		nla_a = nla_nest_start_noflag(skb, NLBL_MGMT_A_SELECTORLIST);
		अगर (nla_a == शून्य)
			वापस -ENOMEM;

		netlbl_af4list_क्रमeach_rcu(iter4, &entry->def.addrsel->list4) अणु
			काष्ठा netlbl_करोmaddr4_map *map4;
			काष्ठा in_addr addr_काष्ठा;

			nla_b = nla_nest_start_noflag(skb,
						      NLBL_MGMT_A_ADDRSELECTOR);
			अगर (nla_b == शून्य)
				वापस -ENOMEM;

			addr_काष्ठा.s_addr = iter4->addr;
			ret_val = nla_put_in_addr(skb, NLBL_MGMT_A_IPV4ADDR,
						  addr_काष्ठा.s_addr);
			अगर (ret_val != 0)
				वापस ret_val;
			addr_काष्ठा.s_addr = iter4->mask;
			ret_val = nla_put_in_addr(skb, NLBL_MGMT_A_IPV4MASK,
						  addr_काष्ठा.s_addr);
			अगर (ret_val != 0)
				वापस ret_val;
			map4 = netlbl_करोmhsh_addr4_entry(iter4);
			ret_val = nla_put_u32(skb, NLBL_MGMT_A_PROTOCOL,
					      map4->def.type);
			अगर (ret_val != 0)
				वापस ret_val;
			चयन (map4->def.type) अणु
			हाल NETLBL_NLTYPE_CIPSOV4:
				ret_val = nla_put_u32(skb, NLBL_MGMT_A_CV4DOI,
						      map4->def.cipso->करोi);
				अगर (ret_val != 0)
					वापस ret_val;
				अवरोध;
			पूर्ण

			nla_nest_end(skb, nla_b);
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
		netlbl_af6list_क्रमeach_rcu(iter6, &entry->def.addrsel->list6) अणु
			काष्ठा netlbl_करोmaddr6_map *map6;

			nla_b = nla_nest_start_noflag(skb,
						      NLBL_MGMT_A_ADDRSELECTOR);
			अगर (nla_b == शून्य)
				वापस -ENOMEM;

			ret_val = nla_put_in6_addr(skb, NLBL_MGMT_A_IPV6ADDR,
						   &iter6->addr);
			अगर (ret_val != 0)
				वापस ret_val;
			ret_val = nla_put_in6_addr(skb, NLBL_MGMT_A_IPV6MASK,
						   &iter6->mask);
			अगर (ret_val != 0)
				वापस ret_val;
			map6 = netlbl_करोmhsh_addr6_entry(iter6);
			ret_val = nla_put_u32(skb, NLBL_MGMT_A_PROTOCOL,
					      map6->def.type);
			अगर (ret_val != 0)
				वापस ret_val;

			चयन (map6->def.type) अणु
			हाल NETLBL_NLTYPE_CALIPSO:
				ret_val = nla_put_u32(skb, NLBL_MGMT_A_CLPDOI,
						      map6->def.calipso->करोi);
				अगर (ret_val != 0)
					वापस ret_val;
				अवरोध;
			पूर्ण

			nla_nest_end(skb, nla_b);
		पूर्ण
#पूर्ण_अगर /* IPv6 */

		nla_nest_end(skb, nla_a);
		अवरोध;
	हाल NETLBL_NLTYPE_UNLABELED:
		ret_val = nla_put_u32(skb, NLBL_MGMT_A_PROTOCOL,
				      entry->def.type);
		अवरोध;
	हाल NETLBL_NLTYPE_CIPSOV4:
		ret_val = nla_put_u32(skb, NLBL_MGMT_A_PROTOCOL,
				      entry->def.type);
		अगर (ret_val != 0)
			वापस ret_val;
		ret_val = nla_put_u32(skb, NLBL_MGMT_A_CV4DOI,
				      entry->def.cipso->करोi);
		अवरोध;
	हाल NETLBL_NLTYPE_CALIPSO:
		ret_val = nla_put_u32(skb, NLBL_MGMT_A_PROTOCOL,
				      entry->def.type);
		अगर (ret_val != 0)
			वापस ret_val;
		ret_val = nla_put_u32(skb, NLBL_MGMT_A_CLPDOI,
				      entry->def.calipso->करोi);
		अवरोध;
	पूर्ण

	वापस ret_val;
पूर्ण

/*
 * NetLabel Command Handlers
 */

/**
 * netlbl_mgmt_add - Handle an ADD message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated ADD message and add the करोमुख्यs from the message
 * to the hash table.  See netlabel.h क्रम a description of the message क्रमmat.
 * Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_mgmt_add(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा netlbl_audit audit_info;

	अगर ((!info->attrs[NLBL_MGMT_A_DOMAIN]) ||
	    (!info->attrs[NLBL_MGMT_A_PROTOCOL]) ||
	    (info->attrs[NLBL_MGMT_A_IPV4ADDR] &&
	     info->attrs[NLBL_MGMT_A_IPV6ADDR]) ||
	    (info->attrs[NLBL_MGMT_A_IPV4MASK] &&
	     info->attrs[NLBL_MGMT_A_IPV6MASK]) ||
	    ((info->attrs[NLBL_MGMT_A_IPV4ADDR] != शून्य) ^
	     (info->attrs[NLBL_MGMT_A_IPV4MASK] != शून्य)) ||
	    ((info->attrs[NLBL_MGMT_A_IPV6ADDR] != शून्य) ^
	     (info->attrs[NLBL_MGMT_A_IPV6MASK] != शून्य)))
		वापस -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);

	वापस netlbl_mgmt_add_common(info, &audit_info);
पूर्ण

/**
 * netlbl_mgmt_हटाओ - Handle a REMOVE message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated REMOVE message and हटाओ the specअगरied करोमुख्य
 * mappings.  Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_mgmt_हटाओ(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	अक्षर *करोमुख्य;
	काष्ठा netlbl_audit audit_info;

	अगर (!info->attrs[NLBL_MGMT_A_DOMAIN])
		वापस -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);

	करोमुख्य = nla_data(info->attrs[NLBL_MGMT_A_DOMAIN]);
	वापस netlbl_करोmhsh_हटाओ(करोमुख्य, AF_UNSPEC, &audit_info);
पूर्ण

/**
 * netlbl_mgmt_listall_cb - netlbl_करोmhsh_walk() callback क्रम LISTALL
 * @entry: the करोमुख्य mapping hash table entry
 * @arg: the netlbl_करोmhsh_walk_arg काष्ठाure
 *
 * Description:
 * This function is deचिन्हित to be used as a callback to the
 * netlbl_करोmhsh_walk() function क्रम use in generating a response क्रम a LISTALL
 * message.  Returns the size of the message on success, negative values on
 * failure.
 *
 */
अटल पूर्णांक netlbl_mgmt_listall_cb(काष्ठा netlbl_करोm_map *entry, व्योम *arg)
अणु
	पूर्णांक ret_val = -ENOMEM;
	काष्ठा netlbl_करोmhsh_walk_arg *cb_arg = arg;
	व्योम *data;

	data = genlmsg_put(cb_arg->skb, NETLINK_CB(cb_arg->nl_cb->skb).portid,
			   cb_arg->seq, &netlbl_mgmt_gnl_family,
			   NLM_F_MULTI, NLBL_MGMT_C_LISTALL);
	अगर (data == शून्य)
		जाओ listall_cb_failure;

	ret_val = netlbl_mgmt_listentry(cb_arg->skb, entry);
	अगर (ret_val != 0)
		जाओ listall_cb_failure;

	cb_arg->seq++;
	genlmsg_end(cb_arg->skb, data);
	वापस 0;

listall_cb_failure:
	genlmsg_cancel(cb_arg->skb, data);
	वापस ret_val;
पूर्ण

/**
 * netlbl_mgmt_listall - Handle a LISTALL message
 * @skb: the NETLINK buffer
 * @cb: the NETLINK callback
 *
 * Description:
 * Process a user generated LISTALL message and dumps the करोमुख्य hash table in
 * a क्रमm suitable क्रम use in a kernel generated LISTALL message.  Returns zero
 * on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_mgmt_listall(काष्ठा sk_buff *skb,
			       काष्ठा netlink_callback *cb)
अणु
	काष्ठा netlbl_करोmhsh_walk_arg cb_arg;
	u32 skip_bkt = cb->args[0];
	u32 skip_chain = cb->args[1];

	cb_arg.nl_cb = cb;
	cb_arg.skb = skb;
	cb_arg.seq = cb->nlh->nlmsg_seq;

	netlbl_करोmhsh_walk(&skip_bkt,
			   &skip_chain,
			   netlbl_mgmt_listall_cb,
			   &cb_arg);

	cb->args[0] = skip_bkt;
	cb->args[1] = skip_chain;
	वापस skb->len;
पूर्ण

/**
 * netlbl_mgmt_adddef - Handle an ADDDEF message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated ADDDEF message and respond accordingly.  Returns
 * zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_mgmt_adddef(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा netlbl_audit audit_info;

	अगर ((!info->attrs[NLBL_MGMT_A_PROTOCOL]) ||
	    (info->attrs[NLBL_MGMT_A_IPV4ADDR] &&
	     info->attrs[NLBL_MGMT_A_IPV6ADDR]) ||
	    (info->attrs[NLBL_MGMT_A_IPV4MASK] &&
	     info->attrs[NLBL_MGMT_A_IPV6MASK]) ||
	    ((info->attrs[NLBL_MGMT_A_IPV4ADDR] != शून्य) ^
	     (info->attrs[NLBL_MGMT_A_IPV4MASK] != शून्य)) ||
	    ((info->attrs[NLBL_MGMT_A_IPV6ADDR] != शून्य) ^
	     (info->attrs[NLBL_MGMT_A_IPV6MASK] != शून्य)))
		वापस -EINVAL;

	netlbl_netlink_auditinfo(skb, &audit_info);

	वापस netlbl_mgmt_add_common(info, &audit_info);
पूर्ण

/**
 * netlbl_mgmt_हटाओdef - Handle a REMOVEDEF message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated REMOVEDEF message and हटाओ the शेष करोमुख्य
 * mapping.  Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_mgmt_हटाओdef(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा netlbl_audit audit_info;

	netlbl_netlink_auditinfo(skb, &audit_info);

	वापस netlbl_करोmhsh_हटाओ_शेष(AF_UNSPEC, &audit_info);
पूर्ण

/**
 * netlbl_mgmt_listdef - Handle a LISTDEF message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated LISTDEF message and dumps the शेष करोमुख्य
 * mapping in a क्रमm suitable क्रम use in a kernel generated LISTDEF message.
 * Returns zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_mgmt_listdef(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक ret_val = -ENOMEM;
	काष्ठा sk_buff *ans_skb = शून्य;
	व्योम *data;
	काष्ठा netlbl_करोm_map *entry;
	u16 family;

	अगर (info->attrs[NLBL_MGMT_A_FAMILY])
		family = nla_get_u16(info->attrs[NLBL_MGMT_A_FAMILY]);
	अन्यथा
		family = AF_INET;

	ans_skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (ans_skb == शून्य)
		वापस -ENOMEM;
	data = genlmsg_put_reply(ans_skb, info, &netlbl_mgmt_gnl_family,
				 0, NLBL_MGMT_C_LISTDEF);
	अगर (data == शून्य)
		जाओ listdef_failure;

	rcu_पढ़ो_lock();
	entry = netlbl_करोmhsh_getentry(शून्य, family);
	अगर (entry == शून्य) अणु
		ret_val = -ENOENT;
		जाओ listdef_failure_lock;
	पूर्ण
	ret_val = netlbl_mgmt_listentry(ans_skb, entry);
	rcu_पढ़ो_unlock();
	अगर (ret_val != 0)
		जाओ listdef_failure;

	genlmsg_end(ans_skb, data);
	वापस genlmsg_reply(ans_skb, info);

listdef_failure_lock:
	rcu_पढ़ो_unlock();
listdef_failure:
	kमुक्त_skb(ans_skb);
	वापस ret_val;
पूर्ण

/**
 * netlbl_mgmt_protocols_cb - Write an inभागidual PROTOCOL message response
 * @skb: the skb to ग_लिखो to
 * @cb: the NETLINK callback
 * @protocol: the NetLabel protocol to use in the message
 *
 * Description:
 * This function is to be used in conjunction with netlbl_mgmt_protocols() to
 * answer a application's PROTOCOLS message.  Returns the size of the message
 * on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_mgmt_protocols_cb(काष्ठा sk_buff *skb,
				    काष्ठा netlink_callback *cb,
				    u32 protocol)
अणु
	पूर्णांक ret_val = -ENOMEM;
	व्योम *data;

	data = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			   &netlbl_mgmt_gnl_family, NLM_F_MULTI,
			   NLBL_MGMT_C_PROTOCOLS);
	अगर (data == शून्य)
		जाओ protocols_cb_failure;

	ret_val = nla_put_u32(skb, NLBL_MGMT_A_PROTOCOL, protocol);
	अगर (ret_val != 0)
		जाओ protocols_cb_failure;

	genlmsg_end(skb, data);
	वापस 0;

protocols_cb_failure:
	genlmsg_cancel(skb, data);
	वापस ret_val;
पूर्ण

/**
 * netlbl_mgmt_protocols - Handle a PROTOCOLS message
 * @skb: the NETLINK buffer
 * @cb: the NETLINK callback
 *
 * Description:
 * Process a user generated PROTOCOLS message and respond accordingly.
 *
 */
अटल पूर्णांक netlbl_mgmt_protocols(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb)
अणु
	u32 protos_sent = cb->args[0];

	अगर (protos_sent == 0) अणु
		अगर (netlbl_mgmt_protocols_cb(skb,
					     cb,
					     NETLBL_NLTYPE_UNLABELED) < 0)
			जाओ protocols_वापस;
		protos_sent++;
	पूर्ण
	अगर (protos_sent == 1) अणु
		अगर (netlbl_mgmt_protocols_cb(skb,
					     cb,
					     NETLBL_NLTYPE_CIPSOV4) < 0)
			जाओ protocols_वापस;
		protos_sent++;
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (protos_sent == 2) अणु
		अगर (netlbl_mgmt_protocols_cb(skb,
					     cb,
					     NETLBL_NLTYPE_CALIPSO) < 0)
			जाओ protocols_वापस;
		protos_sent++;
	पूर्ण
#पूर्ण_अगर

protocols_वापस:
	cb->args[0] = protos_sent;
	वापस skb->len;
पूर्ण

/**
 * netlbl_mgmt_version - Handle a VERSION message
 * @skb: the NETLINK buffer
 * @info: the Generic NETLINK info block
 *
 * Description:
 * Process a user generated VERSION message and respond accordingly.  Returns
 * zero on success, negative values on failure.
 *
 */
अटल पूर्णांक netlbl_mgmt_version(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक ret_val = -ENOMEM;
	काष्ठा sk_buff *ans_skb = शून्य;
	व्योम *data;

	ans_skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (ans_skb == शून्य)
		वापस -ENOMEM;
	data = genlmsg_put_reply(ans_skb, info, &netlbl_mgmt_gnl_family,
				 0, NLBL_MGMT_C_VERSION);
	अगर (data == शून्य)
		जाओ version_failure;

	ret_val = nla_put_u32(ans_skb,
			      NLBL_MGMT_A_VERSION,
			      NETLBL_PROTO_VERSION);
	अगर (ret_val != 0)
		जाओ version_failure;

	genlmsg_end(ans_skb, data);
	वापस genlmsg_reply(ans_skb, info);

version_failure:
	kमुक्त_skb(ans_skb);
	वापस ret_val;
पूर्ण


/*
 * NetLabel Generic NETLINK Command Definitions
 */

अटल स्थिर काष्ठा genl_small_ops netlbl_mgmt_genl_ops[] = अणु
	अणु
	.cmd = NLBL_MGMT_C_ADD,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = GENL_ADMIN_PERM,
	.करोit = netlbl_mgmt_add,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_MGMT_C_REMOVE,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = GENL_ADMIN_PERM,
	.करोit = netlbl_mgmt_हटाओ,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_MGMT_C_LISTALL,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = 0,
	.करोit = शून्य,
	.dumpit = netlbl_mgmt_listall,
	पूर्ण,
	अणु
	.cmd = NLBL_MGMT_C_ADDDEF,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = GENL_ADMIN_PERM,
	.करोit = netlbl_mgmt_adddef,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_MGMT_C_REMOVEDEF,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = GENL_ADMIN_PERM,
	.करोit = netlbl_mgmt_हटाओdef,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_MGMT_C_LISTDEF,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = 0,
	.करोit = netlbl_mgmt_listdef,
	.dumpit = शून्य,
	पूर्ण,
	अणु
	.cmd = NLBL_MGMT_C_PROTOCOLS,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = 0,
	.करोit = शून्य,
	.dumpit = netlbl_mgmt_protocols,
	पूर्ण,
	अणु
	.cmd = NLBL_MGMT_C_VERSION,
	.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
	.flags = 0,
	.करोit = netlbl_mgmt_version,
	.dumpit = शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family netlbl_mgmt_gnl_family __ro_after_init = अणु
	.hdrsize = 0,
	.name = NETLBL_NLTYPE_MGMT_NAME,
	.version = NETLBL_PROTO_VERSION,
	.maxattr = NLBL_MGMT_A_MAX,
	.policy = netlbl_mgmt_genl_policy,
	.module = THIS_MODULE,
	.small_ops = netlbl_mgmt_genl_ops,
	.n_small_ops = ARRAY_SIZE(netlbl_mgmt_genl_ops),
पूर्ण;

/*
 * NetLabel Generic NETLINK Protocol Functions
 */

/**
 * netlbl_mgmt_genl_init - Register the NetLabel management component
 *
 * Description:
 * Register the NetLabel management component with the Generic NETLINK
 * mechanism.  Returns zero on success, negative values on failure.
 *
 */
पूर्णांक __init netlbl_mgmt_genl_init(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&netlbl_mgmt_gnl_family);
पूर्ण
