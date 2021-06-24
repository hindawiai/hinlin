<शैली गुरु>
/*
 * Copyright (C) 2001 Sistina Software (UK) Limited
 *
 * This file is released under the GPL.
 */

#समावेश "dm-core.h"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kmod.h>
#समावेश <linux/bपन.स>

#घोषणा DM_MSG_PREFIX "target"

अटल LIST_HEAD(_tarमाला_लो);
अटल DECLARE_RWSEM(_lock);

अटल अंतरभूत काष्ठा target_type *__find_target_type(स्थिर अक्षर *name)
अणु
	काष्ठा target_type *tt;

	list_क्रम_each_entry(tt, &_tarमाला_लो, list)
		अगर (!म_भेद(name, tt->name))
			वापस tt;

	वापस शून्य;
पूर्ण

अटल काष्ठा target_type *get_target_type(स्थिर अक्षर *name)
अणु
	काष्ठा target_type *tt;

	करोwn_पढ़ो(&_lock);

	tt = __find_target_type(name);
	अगर (tt && !try_module_get(tt->module))
		tt = शून्य;

	up_पढ़ो(&_lock);
	वापस tt;
पूर्ण

अटल व्योम load_module(स्थिर अक्षर *name)
अणु
	request_module("dm-%s", name);
पूर्ण

काष्ठा target_type *dm_get_target_type(स्थिर अक्षर *name)
अणु
	काष्ठा target_type *tt = get_target_type(name);

	अगर (!tt) अणु
		load_module(name);
		tt = get_target_type(name);
	पूर्ण

	वापस tt;
पूर्ण

व्योम dm_put_target_type(काष्ठा target_type *tt)
अणु
	करोwn_पढ़ो(&_lock);
	module_put(tt->module);
	up_पढ़ो(&_lock);
पूर्ण

पूर्णांक dm_target_iterate(व्योम (*iter_func)(काष्ठा target_type *tt,
					व्योम *param), व्योम *param)
अणु
	काष्ठा target_type *tt;

	करोwn_पढ़ो(&_lock);
	list_क्रम_each_entry(tt, &_tarमाला_लो, list)
		iter_func(tt, param);
	up_पढ़ो(&_lock);

	वापस 0;
पूर्ण

पूर्णांक dm_रेजिस्टर_target(काष्ठा target_type *tt)
अणु
	पूर्णांक rv = 0;

	करोwn_ग_लिखो(&_lock);
	अगर (__find_target_type(tt->name))
		rv = -EEXIST;
	अन्यथा
		list_add(&tt->list, &_tarमाला_लो);

	up_ग_लिखो(&_lock);
	वापस rv;
पूर्ण

व्योम dm_unरेजिस्टर_target(काष्ठा target_type *tt)
अणु
	करोwn_ग_लिखो(&_lock);
	अगर (!__find_target_type(tt->name)) अणु
		DMCRIT("Unregistering unrecognised target: %s", tt->name);
		BUG();
	पूर्ण

	list_del(&tt->list);

	up_ग_लिखो(&_lock);
पूर्ण

/*
 * io-err: always fails an io, useful क्रम bringing
 * up LVs that have holes in them.
 */
अटल पूर्णांक io_err_ctr(काष्ठा dm_target *tt, अचिन्हित पूर्णांक argc, अक्षर **args)
अणु
	/*
	 * Return error क्रम discards instead of -EOPNOTSUPP
	 */
	tt->num_discard_bios = 1;

	वापस 0;
पूर्ण

अटल व्योम io_err_dtr(काष्ठा dm_target *tt)
अणु
	/* empty */
पूर्ण

अटल पूर्णांक io_err_map(काष्ठा dm_target *tt, काष्ठा bio *bio)
अणु
	वापस DM_MAPIO_KILL;
पूर्ण

अटल पूर्णांक io_err_clone_and_map_rq(काष्ठा dm_target *ti, काष्ठा request *rq,
				   जोड़ map_info *map_context,
				   काष्ठा request **clone)
अणु
	वापस DM_MAPIO_KILL;
पूर्ण

अटल व्योम io_err_release_clone_rq(काष्ठा request *clone,
				    जोड़ map_info *map_context)
अणु
पूर्ण

अटल दीर्घ io_err_dax_direct_access(काष्ठा dm_target *ti, pgoff_t pgoff,
		दीर्घ nr_pages, व्योम **kaddr, pfn_t *pfn)
अणु
	वापस -EIO;
पूर्ण

अटल काष्ठा target_type error_target = अणु
	.name = "error",
	.version = अणु1, 5, 0पूर्ण,
	.features = DM_TARGET_WILDCARD,
	.ctr  = io_err_ctr,
	.dtr  = io_err_dtr,
	.map  = io_err_map,
	.clone_and_map_rq = io_err_clone_and_map_rq,
	.release_clone_rq = io_err_release_clone_rq,
	.direct_access = io_err_dax_direct_access,
पूर्ण;

पूर्णांक __init dm_target_init(व्योम)
अणु
	वापस dm_रेजिस्टर_target(&error_target);
पूर्ण

व्योम dm_target_निकास(व्योम)
अणु
	dm_unरेजिस्टर_target(&error_target);
पूर्ण

EXPORT_SYMBOL(dm_रेजिस्टर_target);
EXPORT_SYMBOL(dm_unरेजिस्टर_target);
