<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/gc.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश "common.h"
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>

/**
 * tomoyo_memory_मुक्त - Free memory क्रम elements.
 *
 * @ptr:  Poपूर्णांकer to allocated memory.
 *
 * Returns nothing.
 *
 * Caller holds tomoyo_policy_lock mutex.
 */
अटल अंतरभूत व्योम tomoyo_memory_मुक्त(व्योम *ptr)
अणु
	tomoyo_memory_used[TOMOYO_MEMORY_POLICY] -= ksize(ptr);
	kमुक्त(ptr);
पूर्ण

/* The list क्रम "struct tomoyo_io_buffer". */
अटल LIST_HEAD(tomoyo_io_buffer_list);
/* Lock क्रम protecting tomoyo_io_buffer_list. */
अटल DEFINE_SPINLOCK(tomoyo_io_buffer_list_lock);

/**
 * tomoyo_काष्ठा_used_by_io_buffer - Check whether the list element is used by /sys/kernel/security/tomoyo/ users or not.
 *
 * @element: Poपूर्णांकer to "struct list_head".
 *
 * Returns true अगर @element is used by /sys/kernel/security/tomoyo/ users,
 * false otherwise.
 */
अटल bool tomoyo_काष्ठा_used_by_io_buffer(स्थिर काष्ठा list_head *element)
अणु
	काष्ठा tomoyo_io_buffer *head;
	bool in_use = false;

	spin_lock(&tomoyo_io_buffer_list_lock);
	list_क्रम_each_entry(head, &tomoyo_io_buffer_list, list) अणु
		head->users++;
		spin_unlock(&tomoyo_io_buffer_list_lock);
		mutex_lock(&head->io_sem);
		अगर (head->r.करोमुख्य == element || head->r.group == element ||
		    head->r.acl == element || &head->w.करोमुख्य->list == element)
			in_use = true;
		mutex_unlock(&head->io_sem);
		spin_lock(&tomoyo_io_buffer_list_lock);
		head->users--;
		अगर (in_use)
			अवरोध;
	पूर्ण
	spin_unlock(&tomoyo_io_buffer_list_lock);
	वापस in_use;
पूर्ण

/**
 * tomoyo_name_used_by_io_buffer - Check whether the string is used by /sys/kernel/security/tomoyo/ users or not.
 *
 * @string: String to check.
 *
 * Returns true अगर @string is used by /sys/kernel/security/tomoyo/ users,
 * false otherwise.
 */
अटल bool tomoyo_name_used_by_io_buffer(स्थिर अक्षर *string)
अणु
	काष्ठा tomoyo_io_buffer *head;
	स्थिर माप_प्रकार size = म_माप(string) + 1;
	bool in_use = false;

	spin_lock(&tomoyo_io_buffer_list_lock);
	list_क्रम_each_entry(head, &tomoyo_io_buffer_list, list) अणु
		पूर्णांक i;

		head->users++;
		spin_unlock(&tomoyo_io_buffer_list_lock);
		mutex_lock(&head->io_sem);
		क्रम (i = 0; i < TOMOYO_MAX_IO_READ_QUEUE; i++) अणु
			स्थिर अक्षर *w = head->r.w[i];

			अगर (w < string || w > string + size)
				जारी;
			in_use = true;
			अवरोध;
		पूर्ण
		mutex_unlock(&head->io_sem);
		spin_lock(&tomoyo_io_buffer_list_lock);
		head->users--;
		अगर (in_use)
			अवरोध;
	पूर्ण
	spin_unlock(&tomoyo_io_buffer_list_lock);
	वापस in_use;
पूर्ण

/**
 * tomoyo_del_transition_control - Delete members in "struct tomoyo_transition_control".
 *
 * @element: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम tomoyo_del_transition_control(काष्ठा list_head *element)
अणु
	काष्ठा tomoyo_transition_control *ptr =
		container_of(element, typeof(*ptr), head.list);

	tomoyo_put_name(ptr->करोमुख्यname);
	tomoyo_put_name(ptr->program);
पूर्ण

/**
 * tomoyo_del_aggregator - Delete members in "struct tomoyo_aggregator".
 *
 * @element: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम tomoyo_del_aggregator(काष्ठा list_head *element)
अणु
	काष्ठा tomoyo_aggregator *ptr =
		container_of(element, typeof(*ptr), head.list);

	tomoyo_put_name(ptr->original_name);
	tomoyo_put_name(ptr->aggregated_name);
पूर्ण

/**
 * tomoyo_del_manager - Delete members in "struct tomoyo_manager".
 *
 * @element: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम tomoyo_del_manager(काष्ठा list_head *element)
अणु
	काष्ठा tomoyo_manager *ptr =
		container_of(element, typeof(*ptr), head.list);

	tomoyo_put_name(ptr->manager);
पूर्ण

/**
 * tomoyo_del_acl - Delete members in "struct tomoyo_acl_info".
 *
 * @element: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_del_acl(काष्ठा list_head *element)
अणु
	काष्ठा tomoyo_acl_info *acl =
		container_of(element, typeof(*acl), list);

	tomoyo_put_condition(acl->cond);
	चयन (acl->type) अणु
	हाल TOMOYO_TYPE_PATH_ACL:
		अणु
			काष्ठा tomoyo_path_acl *entry
				= container_of(acl, typeof(*entry), head);
			tomoyo_put_name_जोड़(&entry->name);
		पूर्ण
		अवरोध;
	हाल TOMOYO_TYPE_PATH2_ACL:
		अणु
			काष्ठा tomoyo_path2_acl *entry
				= container_of(acl, typeof(*entry), head);
			tomoyo_put_name_जोड़(&entry->name1);
			tomoyo_put_name_जोड़(&entry->name2);
		पूर्ण
		अवरोध;
	हाल TOMOYO_TYPE_PATH_NUMBER_ACL:
		अणु
			काष्ठा tomoyo_path_number_acl *entry
				= container_of(acl, typeof(*entry), head);
			tomoyo_put_name_जोड़(&entry->name);
			tomoyo_put_number_जोड़(&entry->number);
		पूर्ण
		अवरोध;
	हाल TOMOYO_TYPE_MKDEV_ACL:
		अणु
			काष्ठा tomoyo_mkdev_acl *entry
				= container_of(acl, typeof(*entry), head);
			tomoyo_put_name_जोड़(&entry->name);
			tomoyo_put_number_जोड़(&entry->mode);
			tomoyo_put_number_जोड़(&entry->major);
			tomoyo_put_number_जोड़(&entry->minor);
		पूर्ण
		अवरोध;
	हाल TOMOYO_TYPE_MOUNT_ACL:
		अणु
			काष्ठा tomoyo_mount_acl *entry
				= container_of(acl, typeof(*entry), head);
			tomoyo_put_name_जोड़(&entry->dev_name);
			tomoyo_put_name_जोड़(&entry->dir_name);
			tomoyo_put_name_जोड़(&entry->fs_type);
			tomoyo_put_number_जोड़(&entry->flags);
		पूर्ण
		अवरोध;
	हाल TOMOYO_TYPE_ENV_ACL:
		अणु
			काष्ठा tomoyo_env_acl *entry =
				container_of(acl, typeof(*entry), head);

			tomoyo_put_name(entry->env);
		पूर्ण
		अवरोध;
	हाल TOMOYO_TYPE_INET_ACL:
		अणु
			काष्ठा tomoyo_inet_acl *entry =
				container_of(acl, typeof(*entry), head);

			tomoyo_put_group(entry->address.group);
			tomoyo_put_number_जोड़(&entry->port);
		पूर्ण
		अवरोध;
	हाल TOMOYO_TYPE_UNIX_ACL:
		अणु
			काष्ठा tomoyo_unix_acl *entry =
				container_of(acl, typeof(*entry), head);

			tomoyo_put_name_जोड़(&entry->name);
		पूर्ण
		अवरोध;
	हाल TOMOYO_TYPE_MANUAL_TASK_ACL:
		अणु
			काष्ठा tomoyo_task_acl *entry =
				container_of(acl, typeof(*entry), head);

			tomoyo_put_name(entry->करोमुख्यname);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

/**
 * tomoyo_del_करोमुख्य - Delete members in "struct tomoyo_domain_info".
 *
 * @element: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 *
 * Caller holds tomoyo_policy_lock mutex.
 */
अटल अंतरभूत व्योम tomoyo_del_करोमुख्य(काष्ठा list_head *element)
अणु
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य =
		container_of(element, typeof(*करोमुख्य), list);
	काष्ठा tomoyo_acl_info *acl;
	काष्ठा tomoyo_acl_info *पंचांगp;

	/*
	 * Since this करोमुख्य is referenced from neither
	 * "struct tomoyo_io_buffer" nor "struct cred"->security, we can delete
	 * elements without checking क्रम is_deleted flag.
	 */
	list_क्रम_each_entry_safe(acl, पंचांगp, &करोमुख्य->acl_info_list, list) अणु
		tomoyo_del_acl(&acl->list);
		tomoyo_memory_मुक्त(acl);
	पूर्ण
	tomoyo_put_name(करोमुख्य->करोमुख्यname);
पूर्ण

/**
 * tomoyo_del_condition - Delete members in "struct tomoyo_condition".
 *
 * @element: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 */
व्योम tomoyo_del_condition(काष्ठा list_head *element)
अणु
	काष्ठा tomoyo_condition *cond = container_of(element, typeof(*cond),
						     head.list);
	स्थिर u16 condc = cond->condc;
	स्थिर u16 numbers_count = cond->numbers_count;
	स्थिर u16 names_count = cond->names_count;
	स्थिर u16 argc = cond->argc;
	स्थिर u16 envc = cond->envc;
	अचिन्हित पूर्णांक i;
	स्थिर काष्ठा tomoyo_condition_element *condp
		= (स्थिर काष्ठा tomoyo_condition_element *) (cond + 1);
	काष्ठा tomoyo_number_जोड़ *numbers_p
		= (काष्ठा tomoyo_number_जोड़ *) (condp + condc);
	काष्ठा tomoyo_name_जोड़ *names_p
		= (काष्ठा tomoyo_name_जोड़ *) (numbers_p + numbers_count);
	स्थिर काष्ठा tomoyo_argv *argv
		= (स्थिर काष्ठा tomoyo_argv *) (names_p + names_count);
	स्थिर काष्ठा tomoyo_envp *envp
		= (स्थिर काष्ठा tomoyo_envp *) (argv + argc);

	क्रम (i = 0; i < numbers_count; i++)
		tomoyo_put_number_जोड़(numbers_p++);
	क्रम (i = 0; i < names_count; i++)
		tomoyo_put_name_जोड़(names_p++);
	क्रम (i = 0; i < argc; argv++, i++)
		tomoyo_put_name(argv->value);
	क्रम (i = 0; i < envc; envp++, i++) अणु
		tomoyo_put_name(envp->name);
		tomoyo_put_name(envp->value);
	पूर्ण
पूर्ण

/**
 * tomoyo_del_name - Delete members in "struct tomoyo_name".
 *
 * @element: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम tomoyo_del_name(काष्ठा list_head *element)
अणु
	/* Nothing to करो. */
पूर्ण

/**
 * tomoyo_del_path_group - Delete members in "struct tomoyo_path_group".
 *
 * @element: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम tomoyo_del_path_group(काष्ठा list_head *element)
अणु
	काष्ठा tomoyo_path_group *member =
		container_of(element, typeof(*member), head.list);

	tomoyo_put_name(member->member_name);
पूर्ण

/**
 * tomoyo_del_group - Delete "struct tomoyo_group".
 *
 * @element: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम tomoyo_del_group(काष्ठा list_head *element)
अणु
	काष्ठा tomoyo_group *group =
		container_of(element, typeof(*group), head.list);

	tomoyo_put_name(group->group_name);
पूर्ण

/**
 * tomoyo_del_address_group - Delete members in "struct tomoyo_address_group".
 *
 * @element: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम tomoyo_del_address_group(काष्ठा list_head *element)
अणु
	/* Nothing to करो. */
पूर्ण

/**
 * tomoyo_del_number_group - Delete members in "struct tomoyo_number_group".
 *
 * @element: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 */
अटल अंतरभूत व्योम tomoyo_del_number_group(काष्ठा list_head *element)
अणु
	/* Nothing to करो. */
पूर्ण

/**
 * tomoyo_try_to_gc - Try to kमुक्त() an entry.
 *
 * @type:    One of values in "enum tomoyo_policy_id".
 * @element: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 *
 * Caller holds tomoyo_policy_lock mutex.
 */
अटल व्योम tomoyo_try_to_gc(स्थिर क्रमागत tomoyo_policy_id type,
			     काष्ठा list_head *element)
अणु
	/*
	 * __list_del_entry() guarantees that the list element became no दीर्घer
	 * reachable from the list which the element was originally on (e.g.
	 * tomoyo_करोमुख्य_list). Also, synchronize_srcu() guarantees that the
	 * list element became no दीर्घer referenced by syscall users.
	 */
	__list_del_entry(element);
	mutex_unlock(&tomoyo_policy_lock);
	synchronize_srcu(&tomoyo_ss);
	/*
	 * However, there are two users which may still be using the list
	 * element. We need to defer until both users क्रमget this element.
	 *
	 * Don't kमुक्त() until "struct tomoyo_io_buffer"->r.अणुकरोमुख्य,group,aclपूर्ण
	 * and "struct tomoyo_io_buffer"->w.करोमुख्य क्रमget this element.
	 */
	अगर (tomoyo_काष्ठा_used_by_io_buffer(element))
		जाओ reinject;
	चयन (type) अणु
	हाल TOMOYO_ID_TRANSITION_CONTROL:
		tomoyo_del_transition_control(element);
		अवरोध;
	हाल TOMOYO_ID_MANAGER:
		tomoyo_del_manager(element);
		अवरोध;
	हाल TOMOYO_ID_AGGREGATOR:
		tomoyo_del_aggregator(element);
		अवरोध;
	हाल TOMOYO_ID_GROUP:
		tomoyo_del_group(element);
		अवरोध;
	हाल TOMOYO_ID_PATH_GROUP:
		tomoyo_del_path_group(element);
		अवरोध;
	हाल TOMOYO_ID_ADDRESS_GROUP:
		tomoyo_del_address_group(element);
		अवरोध;
	हाल TOMOYO_ID_NUMBER_GROUP:
		tomoyo_del_number_group(element);
		अवरोध;
	हाल TOMOYO_ID_CONDITION:
		tomoyo_del_condition(element);
		अवरोध;
	हाल TOMOYO_ID_NAME:
		/*
		 * Don't kमुक्त() until all "struct tomoyo_io_buffer"->r.w[]
		 * क्रमget this element.
		 */
		अगर (tomoyo_name_used_by_io_buffer
		    (container_of(element, typeof(काष्ठा tomoyo_name),
				  head.list)->entry.name))
			जाओ reinject;
		tomoyo_del_name(element);
		अवरोध;
	हाल TOMOYO_ID_ACL:
		tomoyo_del_acl(element);
		अवरोध;
	हाल TOMOYO_ID_DOMAIN:
		/*
		 * Don't kमुक्त() until all "struct cred"->security क्रमget this
		 * element.
		 */
		अगर (atomic_पढ़ो(&container_of
				(element, typeof(काष्ठा tomoyo_करोमुख्य_info),
				 list)->users))
			जाओ reinject;
		अवरोध;
	हाल TOMOYO_MAX_POLICY:
		अवरोध;
	पूर्ण
	mutex_lock(&tomoyo_policy_lock);
	अगर (type == TOMOYO_ID_DOMAIN)
		tomoyo_del_करोमुख्य(element);
	tomoyo_memory_मुक्त(element);
	वापस;
reinject:
	/*
	 * We can safely reinject this element here because
	 * (1) Appending list elements and removing list elements are रक्षित
	 *     by tomoyo_policy_lock mutex.
	 * (2) Only this function हटाओs list elements and this function is
	 *     exclusively executed by tomoyo_gc_mutex mutex.
	 * are true.
	 */
	mutex_lock(&tomoyo_policy_lock);
	list_add_rcu(element, element->prev);
पूर्ण

/**
 * tomoyo_collect_member - Delete elements with "struct tomoyo_acl_head".
 *
 * @id:          One of values in "enum tomoyo_policy_id".
 * @member_list: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_collect_member(स्थिर क्रमागत tomoyo_policy_id id,
				  काष्ठा list_head *member_list)
अणु
	काष्ठा tomoyo_acl_head *member;
	काष्ठा tomoyo_acl_head *पंचांगp;

	list_क्रम_each_entry_safe(member, पंचांगp, member_list, list) अणु
		अगर (!member->is_deleted)
			जारी;
		member->is_deleted = TOMOYO_GC_IN_PROGRESS;
		tomoyo_try_to_gc(id, &member->list);
	पूर्ण
पूर्ण

/**
 * tomoyo_collect_acl - Delete elements in "struct tomoyo_domain_info".
 *
 * @list: Poपूर्णांकer to "struct list_head".
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_collect_acl(काष्ठा list_head *list)
अणु
	काष्ठा tomoyo_acl_info *acl;
	काष्ठा tomoyo_acl_info *पंचांगp;

	list_क्रम_each_entry_safe(acl, पंचांगp, list, list) अणु
		अगर (!acl->is_deleted)
			जारी;
		acl->is_deleted = TOMOYO_GC_IN_PROGRESS;
		tomoyo_try_to_gc(TOMOYO_ID_ACL, &acl->list);
	पूर्ण
पूर्ण

/**
 * tomoyo_collect_entry - Try to kमुक्त() deleted elements.
 *
 * Returns nothing.
 */
अटल व्योम tomoyo_collect_entry(व्योम)
अणु
	पूर्णांक i;
	क्रमागत tomoyo_policy_id id;
	काष्ठा tomoyo_policy_namespace *ns;

	mutex_lock(&tomoyo_policy_lock);
	अणु
		काष्ठा tomoyo_करोमुख्य_info *करोमुख्य;
		काष्ठा tomoyo_करोमुख्य_info *पंचांगp;

		list_क्रम_each_entry_safe(करोमुख्य, पंचांगp, &tomoyo_करोमुख्य_list,
					 list) अणु
			tomoyo_collect_acl(&करोमुख्य->acl_info_list);
			अगर (!करोमुख्य->is_deleted || atomic_पढ़ो(&करोमुख्य->users))
				जारी;
			tomoyo_try_to_gc(TOMOYO_ID_DOMAIN, &करोमुख्य->list);
		पूर्ण
	पूर्ण
	list_क्रम_each_entry(ns, &tomoyo_namespace_list, namespace_list) अणु
		क्रम (id = 0; id < TOMOYO_MAX_POLICY; id++)
			tomoyo_collect_member(id, &ns->policy_list[id]);
		क्रम (i = 0; i < TOMOYO_MAX_ACL_GROUPS; i++)
			tomoyo_collect_acl(&ns->acl_group[i]);
	पूर्ण
	अणु
		काष्ठा tomoyo_shared_acl_head *ptr;
		काष्ठा tomoyo_shared_acl_head *पंचांगp;

		list_क्रम_each_entry_safe(ptr, पंचांगp, &tomoyo_condition_list,
					 list) अणु
			अगर (atomic_पढ़ो(&ptr->users) > 0)
				जारी;
			atomic_set(&ptr->users, TOMOYO_GC_IN_PROGRESS);
			tomoyo_try_to_gc(TOMOYO_ID_CONDITION, &ptr->list);
		पूर्ण
	पूर्ण
	list_क्रम_each_entry(ns, &tomoyo_namespace_list, namespace_list) अणु
		क्रम (i = 0; i < TOMOYO_MAX_GROUP; i++) अणु
			काष्ठा list_head *list = &ns->group_list[i];
			काष्ठा tomoyo_group *group;
			काष्ठा tomoyo_group *पंचांगp;

			चयन (i) अणु
			हाल 0:
				id = TOMOYO_ID_PATH_GROUP;
				अवरोध;
			हाल 1:
				id = TOMOYO_ID_NUMBER_GROUP;
				अवरोध;
			शेष:
				id = TOMOYO_ID_ADDRESS_GROUP;
				अवरोध;
			पूर्ण
			list_क्रम_each_entry_safe(group, पंचांगp, list, head.list) अणु
				tomoyo_collect_member(id, &group->member_list);
				अगर (!list_empty(&group->member_list) ||
				    atomic_पढ़ो(&group->head.users) > 0)
					जारी;
				atomic_set(&group->head.users,
					   TOMOYO_GC_IN_PROGRESS);
				tomoyo_try_to_gc(TOMOYO_ID_GROUP,
						 &group->head.list);
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < TOMOYO_MAX_HASH; i++) अणु
		काष्ठा list_head *list = &tomoyo_name_list[i];
		काष्ठा tomoyo_shared_acl_head *ptr;
		काष्ठा tomoyo_shared_acl_head *पंचांगp;

		list_क्रम_each_entry_safe(ptr, पंचांगp, list, list) अणु
			अगर (atomic_पढ़ो(&ptr->users) > 0)
				जारी;
			atomic_set(&ptr->users, TOMOYO_GC_IN_PROGRESS);
			tomoyo_try_to_gc(TOMOYO_ID_NAME, &ptr->list);
		पूर्ण
	पूर्ण
	mutex_unlock(&tomoyo_policy_lock);
पूर्ण

/**
 * tomoyo_gc_thपढ़ो - Garbage collector thपढ़ो function.
 *
 * @unused: Unused.
 *
 * Returns 0.
 */
अटल पूर्णांक tomoyo_gc_thपढ़ो(व्योम *unused)
अणु
	/* Garbage collector thपढ़ो is exclusive. */
	अटल DEFINE_MUTEX(tomoyo_gc_mutex);

	अगर (!mutex_trylock(&tomoyo_gc_mutex))
		जाओ out;
	tomoyo_collect_entry();
	अणु
		काष्ठा tomoyo_io_buffer *head;
		काष्ठा tomoyo_io_buffer *पंचांगp;

		spin_lock(&tomoyo_io_buffer_list_lock);
		list_क्रम_each_entry_safe(head, पंचांगp, &tomoyo_io_buffer_list,
					 list) अणु
			अगर (head->users)
				जारी;
			list_del(&head->list);
			kमुक्त(head->पढ़ो_buf);
			kमुक्त(head->ग_लिखो_buf);
			kमुक्त(head);
		पूर्ण
		spin_unlock(&tomoyo_io_buffer_list_lock);
	पूर्ण
	mutex_unlock(&tomoyo_gc_mutex);
out:
	/* This acts as करो_निकास(0). */
	वापस 0;
पूर्ण

/**
 * tomoyo_notअगरy_gc - Register/unरेजिस्टर /sys/kernel/security/tomoyo/ users.
 *
 * @head:        Poपूर्णांकer to "struct tomoyo_io_buffer".
 * @is_रेजिस्टर: True अगर रेजिस्टर, false अगर unरेजिस्टर.
 *
 * Returns nothing.
 */
व्योम tomoyo_notअगरy_gc(काष्ठा tomoyo_io_buffer *head, स्थिर bool is_रेजिस्टर)
अणु
	bool is_ग_लिखो = false;

	spin_lock(&tomoyo_io_buffer_list_lock);
	अगर (is_रेजिस्टर) अणु
		head->users = 1;
		list_add(&head->list, &tomoyo_io_buffer_list);
	पूर्ण अन्यथा अणु
		is_ग_लिखो = head->ग_लिखो_buf != शून्य;
		अगर (!--head->users) अणु
			list_del(&head->list);
			kमुक्त(head->पढ़ो_buf);
			kमुक्त(head->ग_लिखो_buf);
			kमुक्त(head);
		पूर्ण
	पूर्ण
	spin_unlock(&tomoyo_io_buffer_list_lock);
	अगर (is_ग_लिखो)
		kthपढ़ो_run(tomoyo_gc_thपढ़ो, शून्य, "GC for TOMOYO");
पूर्ण
