<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Network fileप्रणाली caching backend to use cache files on a premounted
 * fileप्रणाली
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/completion.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/statfs.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/miscdevice.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश "internal.h"

अचिन्हित cachefiles_debug;
module_param_named(debug, cachefiles_debug, uपूर्णांक, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(cachefiles_debug, "CacheFiles debugging mask");

MODULE_DESCRIPTION("Mounted-filesystem based cache");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");

काष्ठा kmem_cache *cachefiles_object_jar;

अटल काष्ठा miscdevice cachefiles_dev = अणु
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "cachefiles",
	.fops	= &cachefiles_daemon_fops,
पूर्ण;

अटल व्योम cachefiles_object_init_once(व्योम *_object)
अणु
	काष्ठा cachefiles_object *object = _object;

	स_रखो(object, 0, माप(*object));
	spin_lock_init(&object->work_lock);
पूर्ण

/*
 * initialise the fs caching module
 */
अटल पूर्णांक __init cachefiles_init(व्योम)
अणु
	पूर्णांक ret;

	ret = misc_रेजिस्टर(&cachefiles_dev);
	अगर (ret < 0)
		जाओ error_dev;

	/* create an object jar */
	ret = -ENOMEM;
	cachefiles_object_jar =
		kmem_cache_create("cachefiles_object_jar",
				  माप(काष्ठा cachefiles_object),
				  0,
				  SLAB_HWCACHE_ALIGN,
				  cachefiles_object_init_once);
	अगर (!cachefiles_object_jar) अणु
		pr_notice("Failed to allocate an object jar\n");
		जाओ error_object_jar;
	पूर्ण

	ret = cachefiles_proc_init();
	अगर (ret < 0)
		जाओ error_proc;

	pr_info("Loaded\n");
	वापस 0;

error_proc:
	kmem_cache_destroy(cachefiles_object_jar);
error_object_jar:
	misc_deरेजिस्टर(&cachefiles_dev);
error_dev:
	pr_err("failed to register: %d\n", ret);
	वापस ret;
पूर्ण

fs_initcall(cachefiles_init);

/*
 * clean up on module removal
 */
अटल व्योम __निकास cachefiles_निकास(व्योम)
अणु
	pr_info("Unloading\n");

	cachefiles_proc_cleanup();
	kmem_cache_destroy(cachefiles_object_jar);
	misc_deरेजिस्टर(&cachefiles_dev);
पूर्ण

module_निकास(cachefiles_निकास);
