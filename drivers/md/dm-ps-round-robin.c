<शैली गुरु>
/*
 * Copyright (C) 2003 Sistina Software.
 * Copyright (C) 2004-2005 Red Hat, Inc. All rights reserved.
 *
 * Module Author: Heinz Mauelshagen
 *
 * This file is released under the GPL.
 *
 * Round-robin path selector.
 */

#समावेश <linux/device-mapper.h>

#समावेश "dm-path-selector.h"

#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#घोषणा DM_MSG_PREFIX "multipath round-robin"
#घोषणा RR_MIN_IO     1
#घोषणा RR_VERSION    "1.2.0"

/*-----------------------------------------------------------------
 * Path-handling code, paths are held in lists
 *---------------------------------------------------------------*/
काष्ठा path_info अणु
	काष्ठा list_head list;
	काष्ठा dm_path *path;
	अचिन्हित repeat_count;
पूर्ण;

अटल व्योम मुक्त_paths(काष्ठा list_head *paths)
अणु
	काष्ठा path_info *pi, *next;

	list_क्रम_each_entry_safe(pi, next, paths, list) अणु
		list_del(&pi->list);
		kमुक्त(pi);
	पूर्ण
पूर्ण

/*-----------------------------------------------------------------
 * Round-robin selector
 *---------------------------------------------------------------*/

काष्ठा selector अणु
	काष्ठा list_head valid_paths;
	काष्ठा list_head invalid_paths;
	spinlock_t lock;
पूर्ण;

अटल काष्ठा selector *alloc_selector(व्योम)
अणु
	काष्ठा selector *s = kदो_स्मृति(माप(*s), GFP_KERNEL);

	अगर (s) अणु
		INIT_LIST_HEAD(&s->valid_paths);
		INIT_LIST_HEAD(&s->invalid_paths);
		spin_lock_init(&s->lock);
	पूर्ण

	वापस s;
पूर्ण

अटल पूर्णांक rr_create(काष्ठा path_selector *ps, अचिन्हित argc, अक्षर **argv)
अणु
	काष्ठा selector *s;

	s = alloc_selector();
	अगर (!s)
		वापस -ENOMEM;

	ps->context = s;
	वापस 0;
पूर्ण

अटल व्योम rr_destroy(काष्ठा path_selector *ps)
अणु
	काष्ठा selector *s = ps->context;

	मुक्त_paths(&s->valid_paths);
	मुक्त_paths(&s->invalid_paths);
	kमुक्त(s);
	ps->context = शून्य;
पूर्ण

अटल पूर्णांक rr_status(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		     status_type_t type, अक्षर *result, अचिन्हित पूर्णांक maxlen)
अणु
	काष्ठा path_info *pi;
	पूर्णांक sz = 0;

	अगर (!path)
		DMEMIT("0 ");
	अन्यथा अणु
		चयन(type) अणु
		हाल STATUSTYPE_INFO:
			अवरोध;
		हाल STATUSTYPE_TABLE:
			pi = path->pscontext;
			DMEMIT("%u ", pi->repeat_count);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस sz;
पूर्ण

/*
 * Called during initialisation to रेजिस्टर each path with an
 * optional repeat_count.
 */
अटल पूर्णांक rr_add_path(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		       पूर्णांक argc, अक्षर **argv, अक्षर **error)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi;
	अचिन्हित repeat_count = RR_MIN_IO;
	अक्षर dummy;
	अचिन्हित दीर्घ flags;

	अगर (argc > 1) अणु
		*error = "round-robin ps: incorrect number of arguments";
		वापस -EINVAL;
	पूर्ण

	/* First path argument is number of I/Os beक्रमe चयनing path */
	अगर ((argc == 1) && (माला_पूछो(argv[0], "%u%c", &repeat_count, &dummy) != 1)) अणु
		*error = "round-robin ps: invalid repeat count";
		वापस -EINVAL;
	पूर्ण

	अगर (repeat_count > 1) अणु
		DMWARN_LIMIT("repeat_count > 1 is deprecated, using 1 instead");
		repeat_count = 1;
	पूर्ण

	/* allocate the path */
	pi = kदो_स्मृति(माप(*pi), GFP_KERNEL);
	अगर (!pi) अणु
		*error = "round-robin ps: Error allocating path context";
		वापस -ENOMEM;
	पूर्ण

	pi->path = path;
	pi->repeat_count = repeat_count;

	path->pscontext = pi;

	spin_lock_irqsave(&s->lock, flags);
	list_add_tail(&pi->list, &s->valid_paths);
	spin_unlock_irqrestore(&s->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम rr_fail_path(काष्ठा path_selector *ps, काष्ठा dm_path *p)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi = p->pscontext;

	spin_lock_irqsave(&s->lock, flags);
	list_move(&pi->list, &s->invalid_paths);
	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

अटल पूर्णांक rr_reinstate_path(काष्ठा path_selector *ps, काष्ठा dm_path *p)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi = p->pscontext;

	spin_lock_irqsave(&s->lock, flags);
	list_move(&pi->list, &s->valid_paths);
	spin_unlock_irqrestore(&s->lock, flags);

	वापस 0;
पूर्ण

अटल काष्ठा dm_path *rr_select_path(काष्ठा path_selector *ps, माप_प्रकार nr_bytes)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi = शून्य;

	spin_lock_irqsave(&s->lock, flags);
	अगर (!list_empty(&s->valid_paths)) अणु
		pi = list_entry(s->valid_paths.next, काष्ठा path_info, list);
		list_move_tail(&pi->list, &s->valid_paths);
	पूर्ण
	spin_unlock_irqrestore(&s->lock, flags);

	वापस pi ? pi->path : शून्य;
पूर्ण

अटल काष्ठा path_selector_type rr_ps = अणु
	.name = "round-robin",
	.module = THIS_MODULE,
	.table_args = 1,
	.info_args = 0,
	.create = rr_create,
	.destroy = rr_destroy,
	.status = rr_status,
	.add_path = rr_add_path,
	.fail_path = rr_fail_path,
	.reinstate_path = rr_reinstate_path,
	.select_path = rr_select_path,
पूर्ण;

अटल पूर्णांक __init dm_rr_init(व्योम)
अणु
	पूर्णांक r = dm_रेजिस्टर_path_selector(&rr_ps);

	अगर (r < 0)
		DMERR("register failed %d", r);

	DMINFO("version " RR_VERSION " loaded");

	वापस r;
पूर्ण

अटल व्योम __निकास dm_rr_निकास(व्योम)
अणु
	पूर्णांक r = dm_unरेजिस्टर_path_selector(&rr_ps);

	अगर (r < 0)
		DMERR("unregister failed %d", r);
पूर्ण

module_init(dm_rr_init);
module_निकास(dm_rr_निकास);

MODULE_DESCRIPTION(DM_NAME " round-robin multipath path selector");
MODULE_AUTHOR("Sistina Software <dm-devel@redhat.com>");
MODULE_LICENSE("GPL");
