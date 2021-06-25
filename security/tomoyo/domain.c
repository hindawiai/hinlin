<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/करोमुख्य.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश "common.h"

#समावेश <linux/binfmts.h>
#समावेश <linux/slab.h>
#समावेश <linux/rculist.h>

/* Variables definitions.*/

/* The initial करोमुख्य. */
काष्ठा tomoyo_करोमुख्य_info tomoyo_kernel_करोमुख्य;

/**
 * tomoyo_update_policy - Update an entry क्रम exception policy.
 *
 * @new_entry:       Poपूर्णांकer to "struct tomoyo_acl_info".
 * @size:            Size of @new_entry in bytes.
 * @param:           Poपूर्णांकer to "struct tomoyo_acl_param".
 * @check_duplicate: Callback function to find duplicated entry.
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
पूर्णांक tomoyo_update_policy(काष्ठा tomoyo_acl_head *new_entry, स्थिर पूर्णांक size,
			 काष्ठा tomoyo_acl_param *param,
			 bool (*check_duplicate)(स्थिर काष्ठा tomoyo_acl_head
						 *,
						 स्थिर काष्ठा tomoyo_acl_head
						 *))
अणु
	पूर्णांक error = param->is_delete ? -ENOENT : -ENOMEM;
	काष्ठा tomoyo_acl_head *entry;
	काष्ठा list_head *list = param->list;

	अगर (mutex_lock_पूर्णांकerruptible(&tomoyo_policy_lock))
		वापस -ENOMEM;
	list_क्रम_each_entry_rcu(entry, list, list,
				srcu_पढ़ो_lock_held(&tomoyo_ss)) अणु
		अगर (entry->is_deleted == TOMOYO_GC_IN_PROGRESS)
			जारी;
		अगर (!check_duplicate(entry, new_entry))
			जारी;
		entry->is_deleted = param->is_delete;
		error = 0;
		अवरोध;
	पूर्ण
	अगर (error && !param->is_delete) अणु
		entry = tomoyo_commit_ok(new_entry, size);
		अगर (entry) अणु
			list_add_tail_rcu(&entry->list, list);
			error = 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&tomoyo_policy_lock);
	वापस error;
पूर्ण

/**
 * tomoyo_same_acl_head - Check क्रम duplicated "struct tomoyo_acl_info" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_acl_info".
 * @b: Poपूर्णांकer to "struct tomoyo_acl_info".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल अंतरभूत bool tomoyo_same_acl_head(स्थिर काष्ठा tomoyo_acl_info *a,
					स्थिर काष्ठा tomoyo_acl_info *b)
अणु
	वापस a->type == b->type && a->cond == b->cond;
पूर्ण

/**
 * tomoyo_update_करोमुख्य - Update an entry क्रम करोमुख्य policy.
 *
 * @new_entry:       Poपूर्णांकer to "struct tomoyo_acl_info".
 * @size:            Size of @new_entry in bytes.
 * @param:           Poपूर्णांकer to "struct tomoyo_acl_param".
 * @check_duplicate: Callback function to find duplicated entry.
 * @merge_duplicate: Callback function to merge duplicated entry.
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
पूर्णांक tomoyo_update_करोमुख्य(काष्ठा tomoyo_acl_info *new_entry, स्थिर पूर्णांक size,
			 काष्ठा tomoyo_acl_param *param,
			 bool (*check_duplicate)(स्थिर काष्ठा tomoyo_acl_info
						 *,
						 स्थिर काष्ठा tomoyo_acl_info
						 *),
			 bool (*merge_duplicate)(काष्ठा tomoyo_acl_info *,
						 काष्ठा tomoyo_acl_info *,
						 स्थिर bool))
अणु
	स्थिर bool is_delete = param->is_delete;
	पूर्णांक error = is_delete ? -ENOENT : -ENOMEM;
	काष्ठा tomoyo_acl_info *entry;
	काष्ठा list_head * स्थिर list = param->list;

	अगर (param->data[0]) अणु
		new_entry->cond = tomoyo_get_condition(param);
		अगर (!new_entry->cond)
			वापस -EINVAL;
		/*
		 * Doमुख्य transition preference is allowed क्रम only
		 * "file execute" entries.
		 */
		अगर (new_entry->cond->transit &&
		    !(new_entry->type == TOMOYO_TYPE_PATH_ACL &&
		      container_of(new_entry, काष्ठा tomoyo_path_acl, head)
		      ->perm == 1 << TOMOYO_TYPE_EXECUTE))
			जाओ out;
	पूर्ण
	अगर (mutex_lock_पूर्णांकerruptible(&tomoyo_policy_lock))
		जाओ out;
	list_क्रम_each_entry_rcu(entry, list, list,
				srcu_पढ़ो_lock_held(&tomoyo_ss)) अणु
		अगर (entry->is_deleted == TOMOYO_GC_IN_PROGRESS)
			जारी;
		अगर (!tomoyo_same_acl_head(entry, new_entry) ||
		    !check_duplicate(entry, new_entry))
			जारी;
		अगर (merge_duplicate)
			entry->is_deleted = merge_duplicate(entry, new_entry,
							    is_delete);
		अन्यथा
			entry->is_deleted = is_delete;
		error = 0;
		अवरोध;
	पूर्ण
	अगर (error && !is_delete) अणु
		entry = tomoyo_commit_ok(new_entry, size);
		अगर (entry) अणु
			list_add_tail_rcu(&entry->list, list);
			error = 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&tomoyo_policy_lock);
out:
	tomoyo_put_condition(new_entry->cond);
	वापस error;
पूर्ण

/**
 * tomoyo_check_acl - Do permission check.
 *
 * @r:           Poपूर्णांकer to "struct tomoyo_request_info".
 * @check_entry: Callback function to check type specअगरic parameters.
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
व्योम tomoyo_check_acl(काष्ठा tomoyo_request_info *r,
		      bool (*check_entry)(काष्ठा tomoyo_request_info *,
					  स्थिर काष्ठा tomoyo_acl_info *))
अणु
	स्थिर काष्ठा tomoyo_करोमुख्य_info *करोमुख्य = r->करोमुख्य;
	काष्ठा tomoyo_acl_info *ptr;
	स्थिर काष्ठा list_head *list = &करोमुख्य->acl_info_list;
	u16 i = 0;

retry:
	list_क्रम_each_entry_rcu(ptr, list, list,
				srcu_पढ़ो_lock_held(&tomoyo_ss)) अणु
		अगर (ptr->is_deleted || ptr->type != r->param_type)
			जारी;
		अगर (!check_entry(r, ptr))
			जारी;
		अगर (!tomoyo_condition(r, ptr->cond))
			जारी;
		r->matched_acl = ptr;
		r->granted = true;
		वापस;
	पूर्ण
	क्रम (; i < TOMOYO_MAX_ACL_GROUPS; i++) अणु
		अगर (!test_bit(i, करोमुख्य->group))
			जारी;
		list = &करोमुख्य->ns->acl_group[i++];
		जाओ retry;
	पूर्ण
	r->granted = false;
पूर्ण

/* The list क्रम "struct tomoyo_domain_info". */
LIST_HEAD(tomoyo_करोमुख्य_list);

/**
 * tomoyo_last_word - Get last component of a करोमुख्यname.
 *
 * @name: Doमुख्यname to check.
 *
 * Returns the last word of @करोमुख्यname.
 */
अटल स्थिर अक्षर *tomoyo_last_word(स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *cp = म_खोजप(name, ' ');

	अगर (cp)
		वापस cp + 1;
	वापस name;
पूर्ण

/**
 * tomoyo_same_transition_control - Check क्रम duplicated "struct tomoyo_transition_control" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_acl_head".
 * @b: Poपूर्णांकer to "struct tomoyo_acl_head".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल bool tomoyo_same_transition_control(स्थिर काष्ठा tomoyo_acl_head *a,
					   स्थिर काष्ठा tomoyo_acl_head *b)
अणु
	स्थिर काष्ठा tomoyo_transition_control *p1 = container_of(a,
								  typeof(*p1),
								  head);
	स्थिर काष्ठा tomoyo_transition_control *p2 = container_of(b,
								  typeof(*p2),
								  head);

	वापस p1->type == p2->type && p1->is_last_name == p2->is_last_name
		&& p1->करोमुख्यname == p2->करोमुख्यname
		&& p1->program == p2->program;
पूर्ण

/**
 * tomoyo_ग_लिखो_transition_control - Write "struct tomoyo_transition_control" list.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 * @type:  Type of this entry.
 *
 * Returns 0 on success, negative value otherwise.
 */
पूर्णांक tomoyo_ग_लिखो_transition_control(काष्ठा tomoyo_acl_param *param,
				    स्थिर u8 type)
अणु
	काष्ठा tomoyo_transition_control e = अणु .type = type पूर्ण;
	पूर्णांक error = param->is_delete ? -ENOENT : -ENOMEM;
	अक्षर *program = param->data;
	अक्षर *करोमुख्यname = म_माला(program, " from ");

	अगर (करोमुख्यname) अणु
		*करोमुख्यname = '\0';
		करोमुख्यname += 6;
	पूर्ण अन्यथा अगर (type == TOMOYO_TRANSITION_CONTROL_NO_KEEP ||
		   type == TOMOYO_TRANSITION_CONTROL_KEEP) अणु
		करोमुख्यname = program;
		program = शून्य;
	पूर्ण
	अगर (program && म_भेद(program, "any")) अणु
		अगर (!tomoyo_correct_path(program))
			वापस -EINVAL;
		e.program = tomoyo_get_name(program);
		अगर (!e.program)
			जाओ out;
	पूर्ण
	अगर (करोमुख्यname && म_भेद(करोमुख्यname, "any")) अणु
		अगर (!tomoyo_correct_करोमुख्य(करोमुख्यname)) अणु
			अगर (!tomoyo_correct_path(करोमुख्यname))
				जाओ out;
			e.is_last_name = true;
		पूर्ण
		e.करोमुख्यname = tomoyo_get_name(करोमुख्यname);
		अगर (!e.करोमुख्यname)
			जाओ out;
	पूर्ण
	param->list = &param->ns->policy_list[TOMOYO_ID_TRANSITION_CONTROL];
	error = tomoyo_update_policy(&e.head, माप(e), param,
				     tomoyo_same_transition_control);
out:
	tomoyo_put_name(e.करोमुख्यname);
	tomoyo_put_name(e.program);
	वापस error;
पूर्ण

/**
 * tomoyo_scan_transition - Try to find specअगरic करोमुख्य transition type.
 *
 * @list:       Poपूर्णांकer to "struct list_head".
 * @करोमुख्यname: The name of current करोमुख्य.
 * @program:    The name of requested program.
 * @last_name:  The last component of @करोमुख्यname.
 * @type:       One of values in "enum tomoyo_transition_type".
 *
 * Returns true अगर found one, false otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल अंतरभूत bool tomoyo_scan_transition
(स्थिर काष्ठा list_head *list, स्थिर काष्ठा tomoyo_path_info *करोमुख्यname,
 स्थिर काष्ठा tomoyo_path_info *program, स्थिर अक्षर *last_name,
 स्थिर क्रमागत tomoyo_transition_type type)
अणु
	स्थिर काष्ठा tomoyo_transition_control *ptr;

	list_क्रम_each_entry_rcu(ptr, list, head.list,
				srcu_पढ़ो_lock_held(&tomoyo_ss)) अणु
		अगर (ptr->head.is_deleted || ptr->type != type)
			जारी;
		अगर (ptr->करोमुख्यname) अणु
			अगर (!ptr->is_last_name) अणु
				अगर (ptr->करोमुख्यname != करोमुख्यname)
					जारी;
			पूर्ण अन्यथा अणु
				/*
				 * Use direct म_भेद() since this is
				 * unlikely used.
				 */
				अगर (म_भेद(ptr->करोमुख्यname->name, last_name))
					जारी;
			पूर्ण
		पूर्ण
		अगर (ptr->program && tomoyo_pathcmp(ptr->program, program))
			जारी;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * tomoyo_transition_type - Get करोमुख्य transition type.
 *
 * @ns:         Poपूर्णांकer to "struct tomoyo_policy_namespace".
 * @करोमुख्यname: The name of current करोमुख्य.
 * @program:    The name of requested program.
 *
 * Returns TOMOYO_TRANSITION_CONTROL_TRANSIT अगर executing @program causes
 * करोमुख्य transition across namespaces, TOMOYO_TRANSITION_CONTROL_INITIALIZE अगर
 * executing @program reinitializes करोमुख्य transition within that namespace,
 * TOMOYO_TRANSITION_CONTROL_KEEP अगर executing @program stays at @करोमुख्यname ,
 * others otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल क्रमागत tomoyo_transition_type tomoyo_transition_type
(स्थिर काष्ठा tomoyo_policy_namespace *ns,
 स्थिर काष्ठा tomoyo_path_info *करोमुख्यname,
 स्थिर काष्ठा tomoyo_path_info *program)
अणु
	स्थिर अक्षर *last_name = tomoyo_last_word(करोमुख्यname->name);
	क्रमागत tomoyo_transition_type type = TOMOYO_TRANSITION_CONTROL_NO_RESET;

	जबतक (type < TOMOYO_MAX_TRANSITION_TYPE) अणु
		स्थिर काष्ठा list_head * स्थिर list =
			&ns->policy_list[TOMOYO_ID_TRANSITION_CONTROL];

		अगर (!tomoyo_scan_transition(list, करोमुख्यname, program,
					    last_name, type)) अणु
			type++;
			जारी;
		पूर्ण
		अगर (type != TOMOYO_TRANSITION_CONTROL_NO_RESET &&
		    type != TOMOYO_TRANSITION_CONTROL_NO_INITIALIZE)
			अवरोध;
		/*
		 * Do not check क्रम reset_करोमुख्य अगर no_reset_करोमुख्य matched.
		 * Do not check क्रम initialize_करोमुख्य अगर no_initialize_करोमुख्य
		 * matched.
		 */
		type++;
		type++;
	पूर्ण
	वापस type;
पूर्ण

/**
 * tomoyo_same_aggregator - Check क्रम duplicated "struct tomoyo_aggregator" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_acl_head".
 * @b: Poपूर्णांकer to "struct tomoyo_acl_head".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल bool tomoyo_same_aggregator(स्थिर काष्ठा tomoyo_acl_head *a,
				   स्थिर काष्ठा tomoyo_acl_head *b)
अणु
	स्थिर काष्ठा tomoyo_aggregator *p1 = container_of(a, typeof(*p1),
							  head);
	स्थिर काष्ठा tomoyo_aggregator *p2 = container_of(b, typeof(*p2),
							  head);

	वापस p1->original_name == p2->original_name &&
		p1->aggregated_name == p2->aggregated_name;
पूर्ण

/**
 * tomoyo_ग_लिखो_aggregator - Write "struct tomoyo_aggregator" list.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
पूर्णांक tomoyo_ग_लिखो_aggregator(काष्ठा tomoyo_acl_param *param)
अणु
	काष्ठा tomoyo_aggregator e = अणु पूर्ण;
	पूर्णांक error = param->is_delete ? -ENOENT : -ENOMEM;
	स्थिर अक्षर *original_name = tomoyo_पढ़ो_token(param);
	स्थिर अक्षर *aggregated_name = tomoyo_पढ़ो_token(param);

	अगर (!tomoyo_correct_word(original_name) ||
	    !tomoyo_correct_path(aggregated_name))
		वापस -EINVAL;
	e.original_name = tomoyo_get_name(original_name);
	e.aggregated_name = tomoyo_get_name(aggregated_name);
	अगर (!e.original_name || !e.aggregated_name ||
	    e.aggregated_name->is_patterned) /* No patterns allowed. */
		जाओ out;
	param->list = &param->ns->policy_list[TOMOYO_ID_AGGREGATOR];
	error = tomoyo_update_policy(&e.head, माप(e), param,
				     tomoyo_same_aggregator);
out:
	tomoyo_put_name(e.original_name);
	tomoyo_put_name(e.aggregated_name);
	वापस error;
पूर्ण

/**
 * tomoyo_find_namespace - Find specअगरied namespace.
 *
 * @name: Name of namespace to find.
 * @len:  Length of @name.
 *
 * Returns poपूर्णांकer to "struct tomoyo_policy_namespace" अगर found,
 * शून्य otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल काष्ठा tomoyo_policy_namespace *tomoyo_find_namespace
(स्थिर अक्षर *name, स्थिर अचिन्हित पूर्णांक len)
अणु
	काष्ठा tomoyo_policy_namespace *ns;

	list_क्रम_each_entry(ns, &tomoyo_namespace_list, namespace_list) अणु
		अगर (म_भेदन(name, ns->name, len) ||
		    (name[len] && name[len] != ' '))
			जारी;
		वापस ns;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * tomoyo_assign_namespace - Create a new namespace.
 *
 * @करोमुख्यname: Name of namespace to create.
 *
 * Returns poपूर्णांकer to "struct tomoyo_policy_namespace" on success,
 * शून्य otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
काष्ठा tomoyo_policy_namespace *tomoyo_assign_namespace(स्थिर अक्षर *करोमुख्यname)
अणु
	काष्ठा tomoyo_policy_namespace *ptr;
	काष्ठा tomoyo_policy_namespace *entry;
	स्थिर अक्षर *cp = करोमुख्यname;
	अचिन्हित पूर्णांक len = 0;

	जबतक (*cp && *cp++ != ' ')
		len++;
	ptr = tomoyo_find_namespace(करोमुख्यname, len);
	अगर (ptr)
		वापस ptr;
	अगर (len >= TOMOYO_EXEC_TMPSIZE - 10 || !tomoyo_करोमुख्य_def(करोमुख्यname))
		वापस शून्य;
	entry = kzalloc(माप(*entry) + len + 1, GFP_NOFS | __GFP_NOWARN);
	अगर (mutex_lock_पूर्णांकerruptible(&tomoyo_policy_lock))
		जाओ out;
	ptr = tomoyo_find_namespace(करोमुख्यname, len);
	अगर (!ptr && tomoyo_memory_ok(entry)) अणु
		अक्षर *name = (अक्षर *) (entry + 1);

		ptr = entry;
		स_हटाओ(name, करोमुख्यname, len);
		name[len] = '\0';
		entry->name = name;
		tomoyo_init_policy_namespace(entry);
		entry = शून्य;
	पूर्ण
	mutex_unlock(&tomoyo_policy_lock);
out:
	kमुक्त(entry);
	वापस ptr;
पूर्ण

/**
 * tomoyo_namespace_jump - Check क्रम namespace jump.
 *
 * @करोमुख्यname: Name of करोमुख्य.
 *
 * Returns true अगर namespace dअगरfers, false otherwise.
 */
अटल bool tomoyo_namespace_jump(स्थिर अक्षर *करोमुख्यname)
अणु
	स्थिर अक्षर *namespace = tomoyo_current_namespace()->name;
	स्थिर पूर्णांक len = म_माप(namespace);

	वापस म_भेदन(करोमुख्यname, namespace, len) ||
		(करोमुख्यname[len] && करोमुख्यname[len] != ' ');
पूर्ण

/**
 * tomoyo_assign_करोमुख्य - Create a करोमुख्य or a namespace.
 *
 * @करोमुख्यname: The name of करोमुख्य.
 * @transit:    True अगर transit to करोमुख्य found or created.
 *
 * Returns poपूर्णांकer to "struct tomoyo_domain_info" on success, शून्य otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
काष्ठा tomoyo_करोमुख्य_info *tomoyo_assign_करोमुख्य(स्थिर अक्षर *करोमुख्यname,
						स्थिर bool transit)
अणु
	काष्ठा tomoyo_करोमुख्य_info e = अणु पूर्ण;
	काष्ठा tomoyo_करोमुख्य_info *entry = tomoyo_find_करोमुख्य(करोमुख्यname);
	bool created = false;

	अगर (entry) अणु
		अगर (transit) अणु
			/*
			 * Since namespace is created at runसमय, profiles may
			 * not be created by the moment the process transits to
			 * that करोमुख्य. Do not perक्रमm करोमुख्य transition अगर
			 * profile क्रम that करोमुख्य is not yet created.
			 */
			अगर (tomoyo_policy_loaded &&
			    !entry->ns->profile_ptr[entry->profile])
				वापस शून्य;
		पूर्ण
		वापस entry;
	पूर्ण
	/* Requested करोमुख्य करोes not exist. */
	/* Don't create requested करोमुख्य अगर करोमुख्यname is invalid. */
	अगर (म_माप(करोमुख्यname) >= TOMOYO_EXEC_TMPSIZE - 10 ||
	    !tomoyo_correct_करोमुख्य(करोमुख्यname))
		वापस शून्य;
	/*
	 * Since definition of profiles and acl_groups may dअगरfer across
	 * namespaces, करो not inherit "use_profile" and "use_group" settings
	 * by स्वतःmatically creating requested करोमुख्य upon करोमुख्य transition.
	 */
	अगर (transit && tomoyo_namespace_jump(करोमुख्यname))
		वापस शून्य;
	e.ns = tomoyo_assign_namespace(करोमुख्यname);
	अगर (!e.ns)
		वापस शून्य;
	/*
	 * "use_profile" and "use_group" settings क्रम स्वतःmatically created
	 * करोमुख्यs are inherited from current करोमुख्य. These are 0 क्रम manually
	 * created करोमुख्यs.
	 */
	अगर (transit) अणु
		स्थिर काष्ठा tomoyo_करोमुख्य_info *करोमुख्य = tomoyo_करोमुख्य();

		e.profile = करोमुख्य->profile;
		स_नकल(e.group, करोमुख्य->group, माप(e.group));
	पूर्ण
	e.करोमुख्यname = tomoyo_get_name(करोमुख्यname);
	अगर (!e.करोमुख्यname)
		वापस शून्य;
	अगर (mutex_lock_पूर्णांकerruptible(&tomoyo_policy_lock))
		जाओ out;
	entry = tomoyo_find_करोमुख्य(करोमुख्यname);
	अगर (!entry) अणु
		entry = tomoyo_commit_ok(&e, माप(e));
		अगर (entry) अणु
			INIT_LIST_HEAD(&entry->acl_info_list);
			list_add_tail_rcu(&entry->list, &tomoyo_करोमुख्य_list);
			created = true;
		पूर्ण
	पूर्ण
	mutex_unlock(&tomoyo_policy_lock);
out:
	tomoyo_put_name(e.करोमुख्यname);
	अगर (entry && transit) अणु
		अगर (created) अणु
			काष्ठा tomoyo_request_info r;
			पूर्णांक i;

			tomoyo_init_request_info(&r, entry,
						 TOMOYO_MAC_खाता_EXECUTE);
			r.granted = false;
			tomoyo_ग_लिखो_log(&r, "use_profile %u\n",
					 entry->profile);
			क्रम (i = 0; i < TOMOYO_MAX_ACL_GROUPS; i++)
				अगर (test_bit(i, entry->group))
					tomoyo_ग_लिखो_log(&r, "use_group %u\n",
							 i);
			tomoyo_update_stat(TOMOYO_STAT_POLICY_UPDATES);
		पूर्ण
	पूर्ण
	वापस entry;
पूर्ण

/**
 * tomoyo_environ - Check permission क्रम environment variable names.
 *
 * @ee: Poपूर्णांकer to "struct tomoyo_execve".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_environ(काष्ठा tomoyo_execve *ee)
अणु
	काष्ठा tomoyo_request_info *r = &ee->r;
	काष्ठा linux_binprm *bprm = ee->bprm;
	/* env_page.data is allocated by tomoyo_dump_page(). */
	काष्ठा tomoyo_page_dump env_page = अणु पूर्ण;
	अक्षर *arg_ptr; /* Size is TOMOYO_EXEC_TMPSIZE bytes */
	पूर्णांक arg_len = 0;
	अचिन्हित दीर्घ pos = bprm->p;
	पूर्णांक offset = pos % PAGE_SIZE;
	पूर्णांक argv_count = bprm->argc;
	पूर्णांक envp_count = bprm->envc;
	पूर्णांक error = -ENOMEM;

	ee->r.type = TOMOYO_MAC_ENVIRON;
	ee->r.profile = r->करोमुख्य->profile;
	ee->r.mode = tomoyo_get_mode(r->करोमुख्य->ns, ee->r.profile,
				     TOMOYO_MAC_ENVIRON);
	अगर (!r->mode || !envp_count)
		वापस 0;
	arg_ptr = kzalloc(TOMOYO_EXEC_TMPSIZE, GFP_NOFS);
	अगर (!arg_ptr)
		जाओ out;
	जबतक (error == -ENOMEM) अणु
		अगर (!tomoyo_dump_page(bprm, pos, &env_page))
			जाओ out;
		pos += PAGE_SIZE - offset;
		/* Read. */
		जबतक (argv_count && offset < PAGE_SIZE) अणु
			अगर (!env_page.data[offset++])
				argv_count--;
		पूर्ण
		अगर (argv_count) अणु
			offset = 0;
			जारी;
		पूर्ण
		जबतक (offset < PAGE_SIZE) अणु
			स्थिर अचिन्हित अक्षर c = env_page.data[offset++];

			अगर (c && arg_len < TOMOYO_EXEC_TMPSIZE - 10) अणु
				अगर (c == '=') अणु
					arg_ptr[arg_len++] = '\0';
				पूर्ण अन्यथा अगर (c == '\\') अणु
					arg_ptr[arg_len++] = '\\';
					arg_ptr[arg_len++] = '\\';
				पूर्ण अन्यथा अगर (c > ' ' && c < 127) अणु
					arg_ptr[arg_len++] = c;
				पूर्ण अन्यथा अणु
					arg_ptr[arg_len++] = '\\';
					arg_ptr[arg_len++] = (c >> 6) + '0';
					arg_ptr[arg_len++]
						= ((c >> 3) & 7) + '0';
					arg_ptr[arg_len++] = (c & 7) + '0';
				पूर्ण
			पूर्ण अन्यथा अणु
				arg_ptr[arg_len] = '\0';
			पूर्ण
			अगर (c)
				जारी;
			अगर (tomoyo_env_perm(r, arg_ptr)) अणु
				error = -EPERM;
				अवरोध;
			पूर्ण
			अगर (!--envp_count) अणु
				error = 0;
				अवरोध;
			पूर्ण
			arg_len = 0;
		पूर्ण
		offset = 0;
	पूर्ण
out:
	अगर (r->mode != TOMOYO_CONFIG_ENFORCING)
		error = 0;
	kमुक्त(env_page.data);
	kमुक्त(arg_ptr);
	वापस error;
पूर्ण

/**
 * tomoyo_find_next_करोमुख्य - Find a करोमुख्य.
 *
 * @bprm: Poपूर्णांकer to "struct linux_binprm".
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
पूर्णांक tomoyo_find_next_करोमुख्य(काष्ठा linux_binprm *bprm)
अणु
	काष्ठा tomoyo_करोमुख्य_info *old_करोमुख्य = tomoyo_करोमुख्य();
	काष्ठा tomoyo_करोमुख्य_info *करोमुख्य = शून्य;
	स्थिर अक्षर *original_name = bprm->filename;
	पूर्णांक retval = -ENOMEM;
	bool reject_on_transition_failure = false;
	स्थिर काष्ठा tomoyo_path_info *candidate;
	काष्ठा tomoyo_path_info exename;
	काष्ठा tomoyo_execve *ee = kzalloc(माप(*ee), GFP_NOFS);

	अगर (!ee)
		वापस -ENOMEM;
	ee->पंचांगp = kzalloc(TOMOYO_EXEC_TMPSIZE, GFP_NOFS);
	अगर (!ee->पंचांगp) अणु
		kमुक्त(ee);
		वापस -ENOMEM;
	पूर्ण
	/* ee->dump->data is allocated by tomoyo_dump_page(). */
	tomoyo_init_request_info(&ee->r, शून्य, TOMOYO_MAC_खाता_EXECUTE);
	ee->r.ee = ee;
	ee->bprm = bprm;
	ee->r.obj = &ee->obj;
	ee->obj.path1 = bprm->file->f_path;
	/* Get symlink's pathname of program. */
	retval = -ENOENT;
	exename.name = tomoyo_realpath_nofollow(original_name);
	अगर (!exename.name)
		जाओ out;
	tomoyo_fill_path_info(&exename);
retry:
	/* Check 'aggregator' directive. */
	अणु
		काष्ठा tomoyo_aggregator *ptr;
		काष्ठा list_head *list =
			&old_करोमुख्य->ns->policy_list[TOMOYO_ID_AGGREGATOR];

		/* Check 'aggregator' directive. */
		candidate = &exename;
		list_क्रम_each_entry_rcu(ptr, list, head.list,
					srcu_पढ़ो_lock_held(&tomoyo_ss)) अणु
			अगर (ptr->head.is_deleted ||
			    !tomoyo_path_matches_pattern(&exename,
							 ptr->original_name))
				जारी;
			candidate = ptr->aggregated_name;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Check execute permission. */
	retval = tomoyo_execute_permission(&ee->r, candidate);
	अगर (retval == TOMOYO_RETRY_REQUEST)
		जाओ retry;
	अगर (retval < 0)
		जाओ out;
	/*
	 * To be able to specअगरy करोमुख्यnames with wildcards, use the
	 * pathname specअगरied in the policy (which may contain
	 * wildcard) rather than the pathname passed to execve()
	 * (which never contains wildcard).
	 */
	अगर (ee->r.param.path.matched_path)
		candidate = ee->r.param.path.matched_path;

	/*
	 * Check क्रम करोमुख्य transition preference अगर "file execute" matched.
	 * If preference is given, make execve() fail अगर करोमुख्य transition
	 * has failed, क्रम करोमुख्य transition preference should be used with
	 * destination करोमुख्य defined.
	 */
	अगर (ee->transition) अणु
		स्थिर अक्षर *करोमुख्यname = ee->transition->name;

		reject_on_transition_failure = true;
		अगर (!म_भेद(करोमुख्यname, "keep"))
			जाओ क्रमce_keep_करोमुख्य;
		अगर (!म_भेद(करोमुख्यname, "child"))
			जाओ क्रमce_child_करोमुख्य;
		अगर (!म_भेद(करोमुख्यname, "reset"))
			जाओ क्रमce_reset_करोमुख्य;
		अगर (!म_भेद(करोमुख्यname, "initialize"))
			जाओ क्रमce_initialize_करोमुख्य;
		अगर (!म_भेद(करोमुख्यname, "parent")) अणु
			अक्षर *cp;

			म_नकलन(ee->पंचांगp, old_करोमुख्य->करोमुख्यname->name,
				TOMOYO_EXEC_TMPSIZE - 1);
			cp = म_खोजप(ee->पंचांगp, ' ');
			अगर (cp)
				*cp = '\0';
		पूर्ण अन्यथा अगर (*करोमुख्यname == '<')
			म_नकलन(ee->पंचांगp, करोमुख्यname, TOMOYO_EXEC_TMPSIZE - 1);
		अन्यथा
			snम_लिखो(ee->पंचांगp, TOMOYO_EXEC_TMPSIZE - 1, "%s %s",
				 old_करोमुख्य->करोमुख्यname->name, करोमुख्यname);
		जाओ क्रमce_jump_करोमुख्य;
	पूर्ण
	/*
	 * No करोमुख्य transition preference specअगरied.
	 * Calculate करोमुख्य to transit to.
	 */
	चयन (tomoyo_transition_type(old_करोमुख्य->ns, old_करोमुख्य->करोमुख्यname,
				       candidate)) अणु
	हाल TOMOYO_TRANSITION_CONTROL_RESET:
क्रमce_reset_करोमुख्य:
		/* Transit to the root of specअगरied namespace. */
		snम_लिखो(ee->पंचांगp, TOMOYO_EXEC_TMPSIZE - 1, "<%s>",
			 candidate->name);
		/*
		 * Make execve() fail अगर करोमुख्य transition across namespaces
		 * has failed.
		 */
		reject_on_transition_failure = true;
		अवरोध;
	हाल TOMOYO_TRANSITION_CONTROL_INITIALIZE:
क्रमce_initialize_करोमुख्य:
		/* Transit to the child of current namespace's root. */
		snम_लिखो(ee->पंचांगp, TOMOYO_EXEC_TMPSIZE - 1, "%s %s",
			 old_करोमुख्य->ns->name, candidate->name);
		अवरोध;
	हाल TOMOYO_TRANSITION_CONTROL_KEEP:
क्रमce_keep_करोमुख्य:
		/* Keep current करोमुख्य. */
		करोमुख्य = old_करोमुख्य;
		अवरोध;
	शेष:
		अगर (old_करोमुख्य == &tomoyo_kernel_करोमुख्य &&
		    !tomoyo_policy_loaded) अणु
			/*
			 * Needn't to transit from kernel करोमुख्य beक्रमe
			 * starting /sbin/init. But transit from kernel करोमुख्य
			 * अगर executing initializers because they might start
			 * beक्रमe /sbin/init.
			 */
			करोमुख्य = old_करोमुख्य;
			अवरोध;
		पूर्ण
क्रमce_child_करोमुख्य:
		/* Normal करोमुख्य transition. */
		snम_लिखो(ee->पंचांगp, TOMOYO_EXEC_TMPSIZE - 1, "%s %s",
			 old_करोमुख्य->करोमुख्यname->name, candidate->name);
		अवरोध;
	पूर्ण
क्रमce_jump_करोमुख्य:
	अगर (!करोमुख्य)
		करोमुख्य = tomoyo_assign_करोमुख्य(ee->पंचांगp, true);
	अगर (करोमुख्य)
		retval = 0;
	अन्यथा अगर (reject_on_transition_failure) अणु
		pr_warn("ERROR: Domain '%s' not ready.\n", ee->पंचांगp);
		retval = -ENOMEM;
	पूर्ण अन्यथा अगर (ee->r.mode == TOMOYO_CONFIG_ENFORCING)
		retval = -ENOMEM;
	अन्यथा अणु
		retval = 0;
		अगर (!old_करोमुख्य->flags[TOMOYO_DIF_TRANSITION_FAILED]) अणु
			old_करोमुख्य->flags[TOMOYO_DIF_TRANSITION_FAILED] = true;
			ee->r.granted = false;
			tomoyo_ग_लिखो_log(&ee->r, "%s", tomoyo_dअगर
					 [TOMOYO_DIF_TRANSITION_FAILED]);
			pr_warn("ERROR: Domain '%s' not defined.\n", ee->पंचांगp);
		पूर्ण
	पूर्ण
 out:
	अगर (!करोमुख्य)
		करोमुख्य = old_करोमुख्य;
	/* Update reference count on "struct tomoyo_domain_info". */
	अणु
		काष्ठा tomoyo_task *s = tomoyo_task(current);

		s->old_करोमुख्य_info = s->करोमुख्य_info;
		s->करोमुख्य_info = करोमुख्य;
		atomic_inc(&करोमुख्य->users);
	पूर्ण
	kमुक्त(exename.name);
	अगर (!retval) अणु
		ee->r.करोमुख्य = करोमुख्य;
		retval = tomoyo_environ(ee);
	पूर्ण
	kमुक्त(ee->पंचांगp);
	kमुक्त(ee->dump.data);
	kमुक्त(ee);
	वापस retval;
पूर्ण

/**
 * tomoyo_dump_page - Dump a page to buffer.
 *
 * @bprm: Poपूर्णांकer to "struct linux_binprm".
 * @pos:  Location to dump.
 * @dump: Poपूर्णांकer to "struct tomoyo_page_dump".
 *
 * Returns true on success, false otherwise.
 */
bool tomoyo_dump_page(काष्ठा linux_binprm *bprm, अचिन्हित दीर्घ pos,
		      काष्ठा tomoyo_page_dump *dump)
अणु
	काष्ठा page *page;

	/* dump->data is released by tomoyo_find_next_करोमुख्य(). */
	अगर (!dump->data) अणु
		dump->data = kzalloc(PAGE_SIZE, GFP_NOFS);
		अगर (!dump->data)
			वापस false;
	पूर्ण
	/* Same with get_arg_page(bprm, pos, 0) in fs/exec.c */
#अगर_घोषित CONFIG_MMU
	/*
	 * This is called at execve() समय in order to dig around
	 * in the argv/environment of the new proceess
	 * (represented by bprm).  'current' is the process करोing
	 * the execve().
	 */
	अगर (get_user_pages_remote(bprm->mm, pos, 1,
				FOLL_FORCE, &page, शून्य, शून्य) <= 0)
		वापस false;
#अन्यथा
	page = bprm->page[pos / PAGE_SIZE];
#पूर्ण_अगर
	अगर (page != dump->page) अणु
		स्थिर अचिन्हित पूर्णांक offset = pos % PAGE_SIZE;
		/*
		 * Maybe kmap()/kunmap() should be used here.
		 * But हटाओ_arg_zero() uses kmap_atomic()/kunmap_atomic().
		 * So करो I.
		 */
		अक्षर *kaddr = kmap_atomic(page);

		dump->page = page;
		स_नकल(dump->data + offset, kaddr + offset,
		       PAGE_SIZE - offset);
		kunmap_atomic(kaddr);
	पूर्ण
	/* Same with put_arg_page(page) in fs/exec.c */
#अगर_घोषित CONFIG_MMU
	put_page(page);
#पूर्ण_अगर
	वापस true;
पूर्ण
