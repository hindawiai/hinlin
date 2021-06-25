<शैली गुरु>
/*
 * Copyright (C) 2004-2005 IBM Corp.  All Rights Reserved.
 * Copyright (C) 2006-2009 NEC Corporation.
 *
 * dm-queue-length.c
 *
 * Module Author: Stefan Bader, IBM
 * Modअगरied by: Kiyoshi Ueda, NEC
 *
 * This file is released under the GPL.
 *
 * queue-length path selector - choose a path with the least number of
 * in-flight I/Os.
 */

#समावेश "dm.h"
#समावेश "dm-path-selector.h"

#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/atomic.h>

#घोषणा DM_MSG_PREFIX	"multipath queue-length"
#घोषणा QL_MIN_IO	1
#घोषणा QL_VERSION	"0.2.0"

काष्ठा selector अणु
	काष्ठा list_head	valid_paths;
	काष्ठा list_head	failed_paths;
	spinlock_t lock;
पूर्ण;

काष्ठा path_info अणु
	काष्ठा list_head	list;
	काष्ठा dm_path		*path;
	अचिन्हित		repeat_count;
	atomic_t		qlen;	/* the number of in-flight I/Os */
पूर्ण;

अटल काष्ठा selector *alloc_selector(व्योम)
अणु
	काष्ठा selector *s = kदो_स्मृति(माप(*s), GFP_KERNEL);

	अगर (s) अणु
		INIT_LIST_HEAD(&s->valid_paths);
		INIT_LIST_HEAD(&s->failed_paths);
		spin_lock_init(&s->lock);
	पूर्ण

	वापस s;
पूर्ण

अटल पूर्णांक ql_create(काष्ठा path_selector *ps, अचिन्हित argc, अक्षर **argv)
अणु
	काष्ठा selector *s = alloc_selector();

	अगर (!s)
		वापस -ENOMEM;

	ps->context = s;
	वापस 0;
पूर्ण

अटल व्योम ql_मुक्त_paths(काष्ठा list_head *paths)
अणु
	काष्ठा path_info *pi, *next;

	list_क्रम_each_entry_safe(pi, next, paths, list) अणु
		list_del(&pi->list);
		kमुक्त(pi);
	पूर्ण
पूर्ण

अटल व्योम ql_destroy(काष्ठा path_selector *ps)
अणु
	काष्ठा selector *s = ps->context;

	ql_मुक्त_paths(&s->valid_paths);
	ql_मुक्त_paths(&s->failed_paths);
	kमुक्त(s);
	ps->context = शून्य;
पूर्ण

अटल पूर्णांक ql_status(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		     status_type_t type, अक्षर *result, अचिन्हित maxlen)
अणु
	अचिन्हित sz = 0;
	काष्ठा path_info *pi;

	/* When called with शून्य path, वापस selector status/args. */
	अगर (!path)
		DMEMIT("0 ");
	अन्यथा अणु
		pi = path->pscontext;

		चयन (type) अणु
		हाल STATUSTYPE_INFO:
			DMEMIT("%d ", atomic_पढ़ो(&pi->qlen));
			अवरोध;
		हाल STATUSTYPE_TABLE:
			DMEMIT("%u ", pi->repeat_count);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस sz;
पूर्ण

अटल पूर्णांक ql_add_path(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		       पूर्णांक argc, अक्षर **argv, अक्षर **error)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi;
	अचिन्हित repeat_count = QL_MIN_IO;
	अक्षर dummy;
	अचिन्हित दीर्घ flags;

	/*
	 * Arguments: [<repeat_count>]
	 * 	<repeat_count>: The number of I/Os beक्रमe चयनing path.
	 * 			If not given, शेष (QL_MIN_IO) is used.
	 */
	अगर (argc > 1) अणु
		*error = "queue-length ps: incorrect number of arguments";
		वापस -EINVAL;
	पूर्ण

	अगर ((argc == 1) && (माला_पूछो(argv[0], "%u%c", &repeat_count, &dummy) != 1)) अणु
		*error = "queue-length ps: invalid repeat count";
		वापस -EINVAL;
	पूर्ण

	अगर (repeat_count > 1) अणु
		DMWARN_LIMIT("repeat_count > 1 is deprecated, using 1 instead");
		repeat_count = 1;
	पूर्ण

	/* Allocate the path inक्रमmation काष्ठाure */
	pi = kदो_स्मृति(माप(*pi), GFP_KERNEL);
	अगर (!pi) अणु
		*error = "queue-length ps: Error allocating path information";
		वापस -ENOMEM;
	पूर्ण

	pi->path = path;
	pi->repeat_count = repeat_count;
	atomic_set(&pi->qlen, 0);

	path->pscontext = pi;

	spin_lock_irqsave(&s->lock, flags);
	list_add_tail(&pi->list, &s->valid_paths);
	spin_unlock_irqrestore(&s->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम ql_fail_path(काष्ठा path_selector *ps, काष्ठा dm_path *path)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi = path->pscontext;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	list_move(&pi->list, &s->failed_paths);
	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

अटल पूर्णांक ql_reinstate_path(काष्ठा path_selector *ps, काष्ठा dm_path *path)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi = path->pscontext;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	list_move_tail(&pi->list, &s->valid_paths);
	spin_unlock_irqrestore(&s->lock, flags);

	वापस 0;
पूर्ण

/*
 * Select a path having the minimum number of in-flight I/Os
 */
अटल काष्ठा dm_path *ql_select_path(काष्ठा path_selector *ps, माप_प्रकार nr_bytes)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi = शून्य, *best = शून्य;
	काष्ठा dm_path *ret = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&s->lock, flags);
	अगर (list_empty(&s->valid_paths))
		जाओ out;

	list_क्रम_each_entry(pi, &s->valid_paths, list) अणु
		अगर (!best ||
		    (atomic_पढ़ो(&pi->qlen) < atomic_पढ़ो(&best->qlen)))
			best = pi;

		अगर (!atomic_पढ़ो(&best->qlen))
			अवरोध;
	पूर्ण

	अगर (!best)
		जाओ out;

	/* Move most recently used to least preferred to evenly balance. */
	list_move_tail(&best->list, &s->valid_paths);

	ret = best->path;
out:
	spin_unlock_irqrestore(&s->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक ql_start_io(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		       माप_प्रकार nr_bytes)
अणु
	काष्ठा path_info *pi = path->pscontext;

	atomic_inc(&pi->qlen);

	वापस 0;
पूर्ण

अटल पूर्णांक ql_end_io(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		     माप_प्रकार nr_bytes, u64 start_समय)
अणु
	काष्ठा path_info *pi = path->pscontext;

	atomic_dec(&pi->qlen);

	वापस 0;
पूर्ण

अटल काष्ठा path_selector_type ql_ps = अणु
	.name		= "queue-length",
	.module		= THIS_MODULE,
	.table_args	= 1,
	.info_args	= 1,
	.create		= ql_create,
	.destroy	= ql_destroy,
	.status		= ql_status,
	.add_path	= ql_add_path,
	.fail_path	= ql_fail_path,
	.reinstate_path	= ql_reinstate_path,
	.select_path	= ql_select_path,
	.start_io	= ql_start_io,
	.end_io		= ql_end_io,
पूर्ण;

अटल पूर्णांक __init dm_ql_init(व्योम)
अणु
	पूर्णांक r = dm_रेजिस्टर_path_selector(&ql_ps);

	अगर (r < 0)
		DMERR("register failed %d", r);

	DMINFO("version " QL_VERSION " loaded");

	वापस r;
पूर्ण

अटल व्योम __निकास dm_ql_निकास(व्योम)
अणु
	पूर्णांक r = dm_unरेजिस्टर_path_selector(&ql_ps);

	अगर (r < 0)
		DMERR("unregister failed %d", r);
पूर्ण

module_init(dm_ql_init);
module_निकास(dm_ql_निकास);

MODULE_AUTHOR("Stefan Bader <Stefan.Bader at de.ibm.com>");
MODULE_DESCRIPTION(
	"(C) Copyright IBM Corp. 2004,2005   All Rights Reserved.\n"
	DM_NAME " path selector to balance the number of in-flight I/Os"
);
MODULE_LICENSE("GPL");
