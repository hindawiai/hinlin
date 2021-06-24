<शैली गुरु>
/*
 * Copyright (C) 2012 Red Hat. All rights reserved.
 *
 * This file is released under the GPL.
 */

#समावेश "dm-cache-policy-internal.h"
#समावेश "dm.h"

#समावेश <linux/module.h>
#समावेश <linux/slab.h>

/*----------------------------------------------------------------*/

#घोषणा DM_MSG_PREFIX "cache-policy"

अटल DEFINE_SPINLOCK(रेजिस्टर_lock);
अटल LIST_HEAD(रेजिस्टर_list);

अटल काष्ठा dm_cache_policy_type *__find_policy(स्थिर अक्षर *name)
अणु
	काष्ठा dm_cache_policy_type *t;

	list_क्रम_each_entry(t, &रेजिस्टर_list, list)
		अगर (!म_भेद(t->name, name))
			वापस t;

	वापस शून्य;
पूर्ण

अटल काष्ठा dm_cache_policy_type *__get_policy_once(स्थिर अक्षर *name)
अणु
	काष्ठा dm_cache_policy_type *t = __find_policy(name);

	अगर (t && !try_module_get(t->owner)) अणु
		DMWARN("couldn't get module %s", name);
		t = ERR_PTR(-EINVAL);
	पूर्ण

	वापस t;
पूर्ण

अटल काष्ठा dm_cache_policy_type *get_policy_once(स्थिर अक्षर *name)
अणु
	काष्ठा dm_cache_policy_type *t;

	spin_lock(&रेजिस्टर_lock);
	t = __get_policy_once(name);
	spin_unlock(&रेजिस्टर_lock);

	वापस t;
पूर्ण

अटल काष्ठा dm_cache_policy_type *get_policy(स्थिर अक्षर *name)
अणु
	काष्ठा dm_cache_policy_type *t;

	t = get_policy_once(name);
	अगर (IS_ERR(t))
		वापस शून्य;

	अगर (t)
		वापस t;

	request_module("dm-cache-%s", name);

	t = get_policy_once(name);
	अगर (IS_ERR(t))
		वापस शून्य;

	वापस t;
पूर्ण

अटल व्योम put_policy(काष्ठा dm_cache_policy_type *t)
अणु
	module_put(t->owner);
पूर्ण

पूर्णांक dm_cache_policy_रेजिस्टर(काष्ठा dm_cache_policy_type *type)
अणु
	पूर्णांक r;

	/* One size fits all क्रम now */
	अगर (type->hपूर्णांक_size != 0 && type->hपूर्णांक_size != 4) अणु
		DMWARN("hint size must be 0 or 4 but %llu supplied.", (अचिन्हित दीर्घ दीर्घ) type->hपूर्णांक_size);
		वापस -EINVAL;
	पूर्ण

	spin_lock(&रेजिस्टर_lock);
	अगर (__find_policy(type->name)) अणु
		DMWARN("attempt to register policy under duplicate name %s", type->name);
		r = -EINVAL;
	पूर्ण अन्यथा अणु
		list_add(&type->list, &रेजिस्टर_list);
		r = 0;
	पूर्ण
	spin_unlock(&रेजिस्टर_lock);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(dm_cache_policy_रेजिस्टर);

व्योम dm_cache_policy_unरेजिस्टर(काष्ठा dm_cache_policy_type *type)
अणु
	spin_lock(&रेजिस्टर_lock);
	list_del_init(&type->list);
	spin_unlock(&रेजिस्टर_lock);
पूर्ण
EXPORT_SYMBOL_GPL(dm_cache_policy_unरेजिस्टर);

काष्ठा dm_cache_policy *dm_cache_policy_create(स्थिर अक्षर *name,
					       dm_cblock_t cache_size,
					       sector_t origin_size,
					       sector_t cache_block_size)
अणु
	काष्ठा dm_cache_policy *p = शून्य;
	काष्ठा dm_cache_policy_type *type;

	type = get_policy(name);
	अगर (!type) अणु
		DMWARN("unknown policy type");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	p = type->create(cache_size, origin_size, cache_block_size);
	अगर (!p) अणु
		put_policy(type);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	p->निजी = type;

	वापस p;
पूर्ण
EXPORT_SYMBOL_GPL(dm_cache_policy_create);

व्योम dm_cache_policy_destroy(काष्ठा dm_cache_policy *p)
अणु
	काष्ठा dm_cache_policy_type *t = p->निजी;

	p->destroy(p);
	put_policy(t);
पूर्ण
EXPORT_SYMBOL_GPL(dm_cache_policy_destroy);

स्थिर अक्षर *dm_cache_policy_get_name(काष्ठा dm_cache_policy *p)
अणु
	काष्ठा dm_cache_policy_type *t = p->निजी;

	/* अगर t->real is set then an alias was used (e.g. "default") */
	अगर (t->real)
		वापस t->real->name;

	वापस t->name;
पूर्ण
EXPORT_SYMBOL_GPL(dm_cache_policy_get_name);

स्थिर अचिन्हित *dm_cache_policy_get_version(काष्ठा dm_cache_policy *p)
अणु
	काष्ठा dm_cache_policy_type *t = p->निजी;

	वापस t->version;
पूर्ण
EXPORT_SYMBOL_GPL(dm_cache_policy_get_version);

माप_प्रकार dm_cache_policy_get_hपूर्णांक_size(काष्ठा dm_cache_policy *p)
अणु
	काष्ठा dm_cache_policy_type *t = p->निजी;

	वापस t->hपूर्णांक_size;
पूर्ण
EXPORT_SYMBOL_GPL(dm_cache_policy_get_hपूर्णांक_size);

/*----------------------------------------------------------------*/
