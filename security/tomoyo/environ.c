<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/environ.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश "common.h"

/**
 * tomoyo_check_env_acl - Check permission क्रम environment variable's name.
 *
 * @r:   Poपूर्णांकer to "struct tomoyo_request_info".
 * @ptr: Poपूर्णांकer to "struct tomoyo_acl_info".
 *
 * Returns true अगर granted, false otherwise.
 */
अटल bool tomoyo_check_env_acl(काष्ठा tomoyo_request_info *r,
				 स्थिर काष्ठा tomoyo_acl_info *ptr)
अणु
	स्थिर काष्ठा tomoyo_env_acl *acl =
		container_of(ptr, typeof(*acl), head);

	वापस tomoyo_path_matches_pattern(r->param.environ.name, acl->env);
पूर्ण

/**
 * tomoyo_audit_env_log - Audit environment variable name log.
 *
 * @r: Poपूर्णांकer to "struct tomoyo_request_info".
 *
 * Returns 0 on success, negative value otherwise.
 */
अटल पूर्णांक tomoyo_audit_env_log(काष्ठा tomoyo_request_info *r)
अणु
	वापस tomoyo_supervisor(r, "misc env %s\n",
				 r->param.environ.name->name);
पूर्ण

/**
 * tomoyo_env_perm - Check permission क्रम environment variable's name.
 *
 * @r:   Poपूर्णांकer to "struct tomoyo_request_info".
 * @env: The name of environment variable.
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
पूर्णांक tomoyo_env_perm(काष्ठा tomoyo_request_info *r, स्थिर अक्षर *env)
अणु
	काष्ठा tomoyo_path_info environ;
	पूर्णांक error;

	अगर (!env || !*env)
		वापस 0;
	environ.name = env;
	tomoyo_fill_path_info(&environ);
	r->param_type = TOMOYO_TYPE_ENV_ACL;
	r->param.environ.name = &environ;
	करो अणु
		tomoyo_check_acl(r, tomoyo_check_env_acl);
		error = tomoyo_audit_env_log(r);
	पूर्ण जबतक (error == TOMOYO_RETRY_REQUEST);
	वापस error;
पूर्ण

/**
 * tomoyo_same_env_acl - Check क्रम duplicated "struct tomoyo_env_acl" entry.
 *
 * @a: Poपूर्णांकer to "struct tomoyo_acl_info".
 * @b: Poपूर्णांकer to "struct tomoyo_acl_info".
 *
 * Returns true अगर @a == @b, false otherwise.
 */
अटल bool tomoyo_same_env_acl(स्थिर काष्ठा tomoyo_acl_info *a,
				स्थिर काष्ठा tomoyo_acl_info *b)
अणु
	स्थिर काष्ठा tomoyo_env_acl *p1 = container_of(a, typeof(*p1), head);
	स्थिर काष्ठा tomoyo_env_acl *p2 = container_of(b, typeof(*p2), head);

	वापस p1->env == p2->env;
पूर्ण

/**
 * tomoyo_ग_लिखो_env - Write "struct tomoyo_env_acl" list.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 *
 * Returns 0 on success, negative value otherwise.
 *
 * Caller holds tomoyo_पढ़ो_lock().
 */
अटल पूर्णांक tomoyo_ग_लिखो_env(काष्ठा tomoyo_acl_param *param)
अणु
	काष्ठा tomoyo_env_acl e = अणु .head.type = TOMOYO_TYPE_ENV_ACL पूर्ण;
	पूर्णांक error = -ENOMEM;
	स्थिर अक्षर *data = tomoyo_पढ़ो_token(param);

	अगर (!tomoyo_correct_word(data) || म_अक्षर(data, '='))
		वापस -EINVAL;
	e.env = tomoyo_get_name(data);
	अगर (!e.env)
		वापस error;
	error = tomoyo_update_करोमुख्य(&e.head, माप(e), param,
				  tomoyo_same_env_acl, शून्य);
	tomoyo_put_name(e.env);
	वापस error;
पूर्ण

/**
 * tomoyo_ग_लिखो_misc - Update environment variable list.
 *
 * @param: Poपूर्णांकer to "struct tomoyo_acl_param".
 *
 * Returns 0 on success, negative value otherwise.
 */
पूर्णांक tomoyo_ग_लिखो_misc(काष्ठा tomoyo_acl_param *param)
अणु
	अगर (tomoyo_str_starts(&param->data, "env "))
		वापस tomoyo_ग_लिखो_env(param);
	वापस -EINVAL;
पूर्ण
