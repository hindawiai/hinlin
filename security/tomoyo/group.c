<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/group.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश <linux/slab.h>
#समावेश <linux/rculist.h>

#समावेश "common.h"

/**
 * tomoyo_same_path_group - Check क्रम duplicated "struct tomoyo_path_group" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_acl_head".
 * @b: Poपूर्णांकer to "struct tomoyo_acl_head".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल bool tomoyo_same_path_group(स्थिर काष्ठा tomoyo_acl_head *a,
				   स्थिर काष्ठा tomoyo_acl_head *b)
अणु
	वापस container_of(a, काष्ठा tomoyo_path_group, head)->member_name ==
		container_of(b, काष्ठा tomoyo_path_group, head)->member_name;
पूर्ण

/**
 * tomoyo_same_number_group - Check क्रम duplicated "struct tomoyo_number_group" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_acl_head".
 * @b: Poपूर्णांकer to "struct tomoyo_acl_head".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल bool tomoyo_same_number_group(स्थिर काष्ठा tomoyo_acl_head *a,
				     स्थिर काष्ठा tomoyo_acl_head *b)
अणु
	वापस !स_भेद(&container_of(a, काष्ठा tomoyo_number_group, head)
		       ->number,
		       &container_of(b, काष्ठा tomoyo_number_group, head)
		       ->number,
		       माप(container_of(a, काष्ठा tomoyo_number_group, head)
			      ->number));
पूर्ण

/**
 * tomoyo_same_address_group - Check क्रम duplicated "struct tomoyo_address_group" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_acl_head".
 * @b: Poपूर्णांकer to "struct tomoyo_acl_head".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल bool tomoyo_same_address_group(स्थिर काष्ठा tomoyo_acl_head *a,
				      स्थिर काष्ठा tomoyo_acl_head *b)
अणु
	स्थिर काष्ठा tomoyo_address_group *p1 = container_of(a, typeof(*p1),
							     head);
	स्थिर काष्ठा tomoyo_address_group *p2 = container_of(b, typeof(*p2),
							     head);

	वापस tomoyo_same_ipaddr_जोड़(&p1->address, &p2->address);
पूर्ण

/**
 * tomoyo_ग_लिखो_group - Write "struct tomoyo_path_group"/"struct tomoyo_number_group"/"struct tomoyo_address_group" list.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 * @type:  Type of this group.
 *
 * Returns 0 on success, negative value otherwise.
 */
पूर्णांक tomoyo_ग_लिखो_group(काष्ठा tomoyo_acl_param *param, स्थिर u8 type)
अणु
	काष्ठा tomoyo_group *group = tomoyo_get_group(param, type);
	पूर्णांक error = -EINVAL;

	अगर (!group)
		वापस -ENOMEM;
	param->list = &group->member_list;
	अगर (type == TOMOYO_PATH_GROUP) अणु
		काष्ठा tomoyo_path_group e = अणु पूर्ण;

		e.member_name = tomoyo_get_name(tomoyo_पढ़ो_token(param));
		अगर (!e.member_name) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण
		error = tomoyo_update_policy(&e.head, माप(e), param,
					  tomoyo_same_path_group);
		tomoyo_put_name(e.member_name);
	पूर्ण अन्यथा अगर (type == TOMOYO_NUMBER_GROUP) अणु
		काष्ठा tomoyo_number_group e = अणु पूर्ण;

		अगर (param->data[0] == '@' ||
		    !tomoyo_parse_number_जोड़(param, &e.number))
			जाओ out;
		error = tomoyo_update_policy(&e.head, माप(e), param,
					  tomoyo_same_number_group);
		/*
		 * tomoyo_put_number_जोड़() is not needed because
		 * param->data[0] != '@'.
		 */
	पूर्ण अन्यथा अणु
		काष्ठा tomoyo_address_group e = अणु पूर्ण;

		अगर (param->data[0] == '@' ||
		    !tomoyo_parse_ipaddr_जोड़(param, &e.address))
			जाओ out;
		error = tomoyo_update_policy(&e.head, माप(e), param,
					     tomoyo_same_address_group);
	पूर्ण
out:
	tomoyo_put_group(group);
	वापस error;
पूर्ण

/**
 * tomoyo_path_matches_group - Check whether the given pathname matches members of the given pathname group.
 *
 * @pathname: The name of pathname.
 * @group:    Poपूर्णांकer to "struct tomoyo_path_group".
 *
 * Returns matched member's pathname अगर @pathname matches pathnames in @group,
 * शून्य otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
स्थिर काष्ठा tomoyo_path_info *
tomoyo_path_matches_group(स्थिर काष्ठा tomoyo_path_info *pathname,
			  स्थिर काष्ठा tomoyo_group *group)
अणु
	काष्ठा tomoyo_path_group *member;

	list_क्रम_each_entry_rcu(member, &group->member_list, head.list,
				srcu_पढ़ो_lock_held(&tomoyo_ss)) अणु
		अगर (member->head.is_deleted)
			जारी;
		अगर (!tomoyo_path_matches_pattern(pathname, member->member_name))
			जारी;
		वापस member->member_name;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * tomoyo_number_matches_group - Check whether the given number matches members of the given number group.
 *
 * @min:   Min number.
 * @max:   Max number.
 * @group: Poपूर्णांकer to "struct tomoyo_number_group".
 *
 * Returns true अगर @min and @max partially overlaps @group, false otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
bool tomoyo_number_matches_group(स्थिर अचिन्हित दीर्घ min,
				 स्थिर अचिन्हित दीर्घ max,
				 स्थिर काष्ठा tomoyo_group *group)
अणु
	काष्ठा tomoyo_number_group *member;
	bool matched = false;

	list_क्रम_each_entry_rcu(member, &group->member_list, head.list,
				srcu_पढ़ो_lock_held(&tomoyo_ss)) अणु
		अगर (member->head.is_deleted)
			जारी;
		अगर (min > member->number.values[1] ||
		    max < member->number.values[0])
			जारी;
		matched = true;
		अवरोध;
	पूर्ण
	वापस matched;
पूर्ण

/**
 * tomoyo_address_matches_group - Check whether the given address matches members of the given address group.
 *
 * @is_ipv6: True अगर @address is an IPv6 address.
 * @address: An IPv4 or IPv6 address.
 * @group:   Poपूर्णांकer to "struct tomoyo_address_group".
 *
 * Returns true अगर @address matches addresses in @group group, false otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
bool tomoyo_address_matches_group(स्थिर bool is_ipv6, स्थिर __be32 *address,
				  स्थिर काष्ठा tomoyo_group *group)
अणु
	काष्ठा tomoyo_address_group *member;
	bool matched = false;
	स्थिर u8 size = is_ipv6 ? 16 : 4;

	list_क्रम_each_entry_rcu(member, &group->member_list, head.list,
				srcu_पढ़ो_lock_held(&tomoyo_ss)) अणु
		अगर (member->head.is_deleted)
			जारी;
		अगर (member->address.is_ipv6 != is_ipv6)
			जारी;
		अगर (स_भेद(&member->address.ip[0], address, size) > 0 ||
		    स_भेद(address, &member->address.ip[1], size) > 0)
			जारी;
		matched = true;
		अवरोध;
	पूर्ण
	वापस matched;
पूर्ण
