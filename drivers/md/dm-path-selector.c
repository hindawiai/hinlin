<शैली गुरु>
/*
 * Copyright (C) 2003 Sistina Software.
 * Copyright (C) 2004 Red Hat, Inc. All rights reserved.
 *
 * Module Author: Heinz Mauelshagen
 *
 * This file is released under the GPL.
 *
 * Path selector registration.
 */

#समावेश <linux/device-mapper.h>
#समावेश <linux/module.h>

#समावेश "dm-path-selector.h"

#समावेश <linux/slab.h>

काष्ठा ps_पूर्णांकernal अणु
	काष्ठा path_selector_type pst;
	काष्ठा list_head list;
पूर्ण;

#घोषणा pst_to_psi(__pst) container_of((__pst), काष्ठा ps_पूर्णांकernal, pst)

अटल LIST_HEAD(_path_selectors);
अटल DECLARE_RWSEM(_ps_lock);

अटल काष्ठा ps_पूर्णांकernal *__find_path_selector_type(स्थिर अक्षर *name)
अणु
	काष्ठा ps_पूर्णांकernal *psi;

	list_क्रम_each_entry(psi, &_path_selectors, list) अणु
		अगर (!म_भेद(name, psi->pst.name))
			वापस psi;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा ps_पूर्णांकernal *get_path_selector(स्थिर अक्षर *name)
अणु
	काष्ठा ps_पूर्णांकernal *psi;

	करोwn_पढ़ो(&_ps_lock);
	psi = __find_path_selector_type(name);
	अगर (psi && !try_module_get(psi->pst.module))
		psi = शून्य;
	up_पढ़ो(&_ps_lock);

	वापस psi;
पूर्ण

काष्ठा path_selector_type *dm_get_path_selector(स्थिर अक्षर *name)
अणु
	काष्ठा ps_पूर्णांकernal *psi;

	अगर (!name)
		वापस शून्य;

	psi = get_path_selector(name);
	अगर (!psi) अणु
		request_module("dm-%s", name);
		psi = get_path_selector(name);
	पूर्ण

	वापस psi ? &psi->pst : शून्य;
पूर्ण

व्योम dm_put_path_selector(काष्ठा path_selector_type *pst)
अणु
	काष्ठा ps_पूर्णांकernal *psi;

	अगर (!pst)
		वापस;

	करोwn_पढ़ो(&_ps_lock);
	psi = __find_path_selector_type(pst->name);
	अगर (!psi)
		जाओ out;

	module_put(psi->pst.module);
out:
	up_पढ़ो(&_ps_lock);
पूर्ण

अटल काष्ठा ps_पूर्णांकernal *_alloc_path_selector(काष्ठा path_selector_type *pst)
अणु
	काष्ठा ps_पूर्णांकernal *psi = kzalloc(माप(*psi), GFP_KERNEL);

	अगर (psi)
		psi->pst = *pst;

	वापस psi;
पूर्ण

पूर्णांक dm_रेजिस्टर_path_selector(काष्ठा path_selector_type *pst)
अणु
	पूर्णांक r = 0;
	काष्ठा ps_पूर्णांकernal *psi = _alloc_path_selector(pst);

	अगर (!psi)
		वापस -ENOMEM;

	करोwn_ग_लिखो(&_ps_lock);

	अगर (__find_path_selector_type(pst->name)) अणु
		kमुक्त(psi);
		r = -EEXIST;
	पूर्ण अन्यथा
		list_add(&psi->list, &_path_selectors);

	up_ग_लिखो(&_ps_lock);

	वापस r;
पूर्ण

पूर्णांक dm_unरेजिस्टर_path_selector(काष्ठा path_selector_type *pst)
अणु
	काष्ठा ps_पूर्णांकernal *psi;

	करोwn_ग_लिखो(&_ps_lock);

	psi = __find_path_selector_type(pst->name);
	अगर (!psi) अणु
		up_ग_लिखो(&_ps_lock);
		वापस -EINVAL;
	पूर्ण

	list_del(&psi->list);

	up_ग_लिखो(&_ps_lock);

	kमुक्त(psi);

	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(dm_रेजिस्टर_path_selector);
EXPORT_SYMBOL_GPL(dm_unरेजिस्टर_path_selector);
