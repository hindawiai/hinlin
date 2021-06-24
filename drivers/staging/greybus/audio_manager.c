<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus operations
 *
 * Copyright 2015-2016 Google Inc.
 */

#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/idr.h>

#समावेश "audio_manager.h"
#समावेश "audio_manager_private.h"

अटल काष्ठा kset *manager_kset;

अटल LIST_HEAD(modules_list);
अटल DECLARE_RWSEM(modules_rwsem);
अटल DEFINE_IDA(module_id);

/* helpers */
अटल काष्ठा gb_audio_manager_module *gb_audio_manager_get_locked(पूर्णांक id)
अणु
	काष्ठा gb_audio_manager_module *module;

	अगर (id < 0)
		वापस शून्य;

	list_क्रम_each_entry(module, &modules_list, list) अणु
		अगर (module->id == id)
			वापस module;
	पूर्ण

	वापस शून्य;
पूर्ण

/* खुला API */
पूर्णांक gb_audio_manager_add(काष्ठा gb_audio_manager_module_descriptor *desc)
अणु
	काष्ठा gb_audio_manager_module *module;
	पूर्णांक id;
	पूर्णांक err;

	id = ida_simple_get(&module_id, 0, 0, GFP_KERNEL);
	अगर (id < 0)
		वापस id;

	err = gb_audio_manager_module_create(&module, manager_kset,
					     id, desc);
	अगर (err) अणु
		ida_simple_हटाओ(&module_id, id);
		वापस err;
	पूर्ण

	/* Add it to the list */
	करोwn_ग_लिखो(&modules_rwsem);
	list_add_tail(&module->list, &modules_list);
	up_ग_लिखो(&modules_rwsem);

	वापस module->id;
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_manager_add);

पूर्णांक gb_audio_manager_हटाओ(पूर्णांक id)
अणु
	काष्ठा gb_audio_manager_module *module;

	करोwn_ग_लिखो(&modules_rwsem);

	module = gb_audio_manager_get_locked(id);
	अगर (!module) अणु
		up_ग_लिखो(&modules_rwsem);
		वापस -EINVAL;
	पूर्ण
	list_del(&module->list);
	kobject_put(&module->kobj);
	up_ग_लिखो(&modules_rwsem);
	ida_simple_हटाओ(&module_id, id);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_manager_हटाओ);

व्योम gb_audio_manager_हटाओ_all(व्योम)
अणु
	काष्ठा gb_audio_manager_module *module, *next;
	पूर्णांक is_empty;

	करोwn_ग_लिखो(&modules_rwsem);

	list_क्रम_each_entry_safe(module, next, &modules_list, list) अणु
		list_del(&module->list);
		ida_simple_हटाओ(&module_id, module->id);
		kobject_put(&module->kobj);
	पूर्ण

	is_empty = list_empty(&modules_list);

	up_ग_लिखो(&modules_rwsem);

	अगर (!is_empty)
		pr_warn("Not all nodes were deleted\n");
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_manager_हटाओ_all);

काष्ठा gb_audio_manager_module *gb_audio_manager_get_module(पूर्णांक id)
अणु
	काष्ठा gb_audio_manager_module *module;

	करोwn_पढ़ो(&modules_rwsem);
	module = gb_audio_manager_get_locked(id);
	kobject_get(&module->kobj);
	up_पढ़ो(&modules_rwsem);
	वापस module;
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_manager_get_module);

व्योम gb_audio_manager_put_module(काष्ठा gb_audio_manager_module *module)
अणु
	kobject_put(&module->kobj);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_manager_put_module);

पूर्णांक gb_audio_manager_dump_module(पूर्णांक id)
अणु
	काष्ठा gb_audio_manager_module *module;

	करोwn_पढ़ो(&modules_rwsem);
	module = gb_audio_manager_get_locked(id);
	up_पढ़ो(&modules_rwsem);

	अगर (!module)
		वापस -EINVAL;

	gb_audio_manager_module_dump(module);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_manager_dump_module);

व्योम gb_audio_manager_dump_all(व्योम)
अणु
	काष्ठा gb_audio_manager_module *module;
	पूर्णांक count = 0;

	करोwn_पढ़ो(&modules_rwsem);
	list_क्रम_each_entry(module, &modules_list, list) अणु
		gb_audio_manager_module_dump(module);
		count++;
	पूर्ण
	up_पढ़ो(&modules_rwsem);

	pr_info("Number of connected modules: %d\n", count);
पूर्ण
EXPORT_SYMBOL_GPL(gb_audio_manager_dump_all);

/*
 * module init/deinit
 */
अटल पूर्णांक __init manager_init(व्योम)
अणु
	manager_kset = kset_create_and_add(GB_AUDIO_MANAGER_NAME, शून्य,
					   kernel_kobj);
	अगर (!manager_kset)
		वापस -ENOMEM;

#अगर_घोषित GB_AUDIO_MANAGER_SYSFS
	gb_audio_manager_sysfs_init(&manager_kset->kobj);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम __निकास manager_निकास(व्योम)
अणु
	gb_audio_manager_हटाओ_all();
	kset_unरेजिस्टर(manager_kset);
	ida_destroy(&module_id);
पूर्ण

module_init(manager_init);
module_निकास(manager_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Svetlin Ankov <ankov_svetlin@projectara.com>");
