<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/memory.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश <linux/hash.h>
#समावेश <linux/slab.h>
#समावेश "common.h"

/**
 * tomoyo_warn_oom - Prपूर्णांक out of memory warning message.
 *
 * @function: Function's name.
 */
व्योम tomoyo_warn_oom(स्थिर अक्षर *function)
अणु
	/* Reduce error messages. */
	अटल pid_t tomoyo_last_pid;
	स्थिर pid_t pid = current->pid;

	अगर (tomoyo_last_pid != pid) अणु
		pr_warn("ERROR: Out of memory at %s.\n", function);
		tomoyo_last_pid = pid;
	पूर्ण
	अगर (!tomoyo_policy_loaded)
		panic("MAC Initialization failed.\n");
पूर्ण

/* Memoy currently used by policy/audit log/query. */
अचिन्हित पूर्णांक tomoyo_memory_used[TOMOYO_MAX_MEMORY_STAT];
/* Memory quota क्रम "policy"/"audit log"/"query". */
अचिन्हित पूर्णांक tomoyo_memory_quota[TOMOYO_MAX_MEMORY_STAT];

/**
 * tomoyo_memory_ok - Check memory quota.
 *
 * @ptr: Poपूर्णांकer to allocated memory.
 *
 * Returns true on success, false otherwise.
 *
 * Returns true अगर @ptr is not शून्य and quota not exceeded, false otherwise.
 *
 * Caller holds tomoyo_policy_lock mutex.
 */
bool tomoyo_memory_ok(व्योम *ptr)
अणु
	अगर (ptr) अणु
		स्थिर माप_प्रकार s = ksize(ptr);

		tomoyo_memory_used[TOMOYO_MEMORY_POLICY] += s;
		अगर (!tomoyo_memory_quota[TOMOYO_MEMORY_POLICY] ||
		    tomoyo_memory_used[TOMOYO_MEMORY_POLICY] <=
		    tomoyo_memory_quota[TOMOYO_MEMORY_POLICY])
			वापस true;
		tomoyo_memory_used[TOMOYO_MEMORY_POLICY] -= s;
	पूर्ण
	tomoyo_warn_oom(__func__);
	वापस false;
पूर्ण

/**
 * tomoyo_commit_ok - Check memory quota.
 *
 * @data:   Data to copy from.
 * @size:   Size in byte.
 *
 * Returns poपूर्णांकer to allocated memory on success, शून्य otherwise.
 * @data is zero-cleared on success.
 *
 * Caller holds tomoyo_policy_lock mutex.
 */
व्योम *tomoyo_commit_ok(व्योम *data, स्थिर अचिन्हित पूर्णांक size)
अणु
	व्योम *ptr = kzalloc(size, GFP_NOFS | __GFP_NOWARN);

	अगर (tomoyo_memory_ok(ptr)) अणु
		स_हटाओ(ptr, data, size);
		स_रखो(data, 0, size);
		वापस ptr;
	पूर्ण
	kमुक्त(ptr);
	वापस शून्य;
पूर्ण

/**
 * tomoyo_get_group - Allocate memory क्रम "struct tomoyo_path_group"/"struct tomoyo_number_group".
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 * @idx:   Index number.
 *
 * Returns poपूर्णांकer to "struct tomoyo_group" on success, शून्य otherwise.
 */
काष्ठा tomoyo_group *tomoyo_get_group(काष्ठा tomoyo_acl_param *param,
				      स्थिर u8 idx)
अणु
	काष्ठा tomoyo_group e = अणु पूर्ण;
	काष्ठा tomoyo_group *group = शून्य;
	काष्ठा list_head *list;
	स्थिर अक्षर *group_name = tomoyo_पढ़ो_token(param);
	bool found = false;

	अगर (!tomoyo_correct_word(group_name) || idx >= TOMOYO_MAX_GROUP)
		वापस शून्य;
	e.group_name = tomoyo_get_name(group_name);
	अगर (!e.group_name)
		वापस शून्य;
	अगर (mutex_lock_पूर्णांकerruptible(&tomoyo_policy_lock))
		जाओ out;
	list = &param->ns->group_list[idx];
	list_क्रम_each_entry(group, list, head.list) अणु
		अगर (e.group_name != group->group_name ||
		    atomic_पढ़ो(&group->head.users) == TOMOYO_GC_IN_PROGRESS)
			जारी;
		atomic_inc(&group->head.users);
		found = true;
		अवरोध;
	पूर्ण
	अगर (!found) अणु
		काष्ठा tomoyo_group *entry = tomoyo_commit_ok(&e, माप(e));

		अगर (entry) अणु
			INIT_LIST_HEAD(&entry->member_list);
			atomic_set(&entry->head.users, 1);
			list_add_tail_rcu(&entry->head.list, list);
			group = entry;
			found = true;
		पूर्ण
	पूर्ण
	mutex_unlock(&tomoyo_policy_lock);
out:
	tomoyo_put_name(e.group_name);
	वापस found ? group : शून्य;
पूर्ण

/*
 * tomoyo_name_list is used क्रम holding string data used by TOMOYO.
 * Since same string data is likely used क्रम multiple बार (e.g.
 * "/lib/libc-2.5.so"), TOMOYO shares string data in the क्रमm of
 * "const struct tomoyo_path_info *".
 */
काष्ठा list_head tomoyo_name_list[TOMOYO_MAX_HASH];

/**
 * tomoyo_get_name - Allocate permanent memory क्रम string data.
 *
 * @name: The string to store पूर्णांकo the permernent memory.
 *
 * Returns poपूर्णांकer to "struct tomoyo_path_info" on success, शून्य otherwise.
 */
स्थिर काष्ठा tomoyo_path_info *tomoyo_get_name(स्थिर अक्षर *name)
अणु
	काष्ठा tomoyo_name *ptr;
	अचिन्हित पूर्णांक hash;
	पूर्णांक len;
	काष्ठा list_head *head;

	अगर (!name)
		वापस शून्य;
	len = म_माप(name) + 1;
	hash = full_name_hash(शून्य, (स्थिर अचिन्हित अक्षर *) name, len - 1);
	head = &tomoyo_name_list[hash_दीर्घ(hash, TOMOYO_HASH_BITS)];
	अगर (mutex_lock_पूर्णांकerruptible(&tomoyo_policy_lock))
		वापस शून्य;
	list_क्रम_each_entry(ptr, head, head.list) अणु
		अगर (hash != ptr->entry.hash || म_भेद(name, ptr->entry.name) ||
		    atomic_पढ़ो(&ptr->head.users) == TOMOYO_GC_IN_PROGRESS)
			जारी;
		atomic_inc(&ptr->head.users);
		जाओ out;
	पूर्ण
	ptr = kzalloc(माप(*ptr) + len, GFP_NOFS | __GFP_NOWARN);
	अगर (tomoyo_memory_ok(ptr)) अणु
		ptr->entry.name = ((अक्षर *) ptr) + माप(*ptr);
		स_हटाओ((अक्षर *) ptr->entry.name, name, len);
		atomic_set(&ptr->head.users, 1);
		tomoyo_fill_path_info(&ptr->entry);
		list_add_tail(&ptr->head.list, head);
	पूर्ण अन्यथा अणु
		kमुक्त(ptr);
		ptr = शून्य;
	पूर्ण
out:
	mutex_unlock(&tomoyo_policy_lock);
	वापस ptr ? &ptr->entry : शून्य;
पूर्ण

/* Initial namespace.*/
काष्ठा tomoyo_policy_namespace tomoyo_kernel_namespace;

/**
 * tomoyo_mm_init - Initialize mm related code.
 */
व्योम __init tomoyo_mm_init(व्योम)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < TOMOYO_MAX_HASH; idx++)
		INIT_LIST_HEAD(&tomoyo_name_list[idx]);
	tomoyo_kernel_namespace.name = "<kernel>";
	tomoyo_init_policy_namespace(&tomoyo_kernel_namespace);
	tomoyo_kernel_करोमुख्य.ns = &tomoyo_kernel_namespace;
	INIT_LIST_HEAD(&tomoyo_kernel_करोमुख्य.acl_info_list);
	tomoyo_kernel_करोमुख्य.करोमुख्यname = tomoyo_get_name("<kernel>");
	list_add_tail_rcu(&tomoyo_kernel_करोमुख्य.list, &tomoyo_करोमुख्य_list);
पूर्ण
