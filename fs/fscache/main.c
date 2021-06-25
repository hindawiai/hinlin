<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* General fileप्रणाली local caching manager
 *
 * Copyright (C) 2004-2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा FSCACHE_DEBUG_LEVEL CACHE
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/completion.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश "internal.h"

MODULE_DESCRIPTION("FS Cache Manager");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");

अचिन्हित fscache_defer_lookup = 1;
module_param_named(defer_lookup, fscache_defer_lookup, uपूर्णांक,
		   S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(fscache_defer_lookup,
		 "Defer cookie lookup to background thread");

अचिन्हित fscache_defer_create = 1;
module_param_named(defer_create, fscache_defer_create, uपूर्णांक,
		   S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(fscache_defer_create,
		 "Defer cookie creation to background thread");

अचिन्हित fscache_debug;
module_param_named(debug, fscache_debug, uपूर्णांक,
		   S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(fscache_debug,
		 "FS-Cache debugging mask");

काष्ठा kobject *fscache_root;
काष्ठा workqueue_काष्ठा *fscache_object_wq;
काष्ठा workqueue_काष्ठा *fscache_op_wq;

DEFINE_PER_CPU(रुको_queue_head_t, fscache_object_cong_रुको);

/* these values serve as lower bounds, will be adjusted in fscache_init() */
अटल अचिन्हित fscache_object_max_active = 4;
अटल अचिन्हित fscache_op_max_active = 2;

#अगर_घोषित CONFIG_SYSCTL
अटल काष्ठा ctl_table_header *fscache_sysctl_header;

अटल पूर्णांक fscache_max_active_sysctl(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा workqueue_काष्ठा **wqp = table->extra1;
	अचिन्हित पूर्णांक *datap = table->data;
	पूर्णांक ret;

	ret = proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret == 0)
		workqueue_set_max_active(*wqp, *datap);
	वापस ret;
पूर्ण

अटल काष्ठा ctl_table fscache_sysctls[] = अणु
	अणु
		.procname	= "object_max_active",
		.data		= &fscache_object_max_active,
		.maxlen		= माप(अचिन्हित),
		.mode		= 0644,
		.proc_handler	= fscache_max_active_sysctl,
		.extra1		= &fscache_object_wq,
	पूर्ण,
	अणु
		.procname	= "operation_max_active",
		.data		= &fscache_op_max_active,
		.maxlen		= माप(अचिन्हित),
		.mode		= 0644,
		.proc_handler	= fscache_max_active_sysctl,
		.extra1		= &fscache_op_wq,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table fscache_sysctls_root[] = अणु
	अणु
		.procname	= "fscache",
		.mode		= 0555,
		.child		= fscache_sysctls,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
#पूर्ण_अगर

/*
 * initialise the fs caching module
 */
अटल पूर्णांक __init fscache_init(व्योम)
अणु
	अचिन्हित पूर्णांक nr_cpus = num_possible_cpus();
	अचिन्हित पूर्णांक cpu;
	पूर्णांक ret;

	fscache_object_max_active =
		clamp_val(nr_cpus,
			  fscache_object_max_active, WQ_UNBOUND_MAX_ACTIVE);

	ret = -ENOMEM;
	fscache_object_wq = alloc_workqueue("fscache_object", WQ_UNBOUND,
					    fscache_object_max_active);
	अगर (!fscache_object_wq)
		जाओ error_object_wq;

	fscache_op_max_active =
		clamp_val(fscache_object_max_active / 2,
			  fscache_op_max_active, WQ_UNBOUND_MAX_ACTIVE);

	ret = -ENOMEM;
	fscache_op_wq = alloc_workqueue("fscache_operation", WQ_UNBOUND,
					fscache_op_max_active);
	अगर (!fscache_op_wq)
		जाओ error_op_wq;

	क्रम_each_possible_cpu(cpu)
		init_रुकोqueue_head(&per_cpu(fscache_object_cong_रुको, cpu));

	ret = fscache_proc_init();
	अगर (ret < 0)
		जाओ error_proc;

#अगर_घोषित CONFIG_SYSCTL
	ret = -ENOMEM;
	fscache_sysctl_header = रेजिस्टर_sysctl_table(fscache_sysctls_root);
	अगर (!fscache_sysctl_header)
		जाओ error_sysctl;
#पूर्ण_अगर

	fscache_cookie_jar = kmem_cache_create("fscache_cookie_jar",
					       माप(काष्ठा fscache_cookie),
					       0, 0, शून्य);
	अगर (!fscache_cookie_jar) अणु
		pr_notice("Failed to allocate a cookie jar\n");
		ret = -ENOMEM;
		जाओ error_cookie_jar;
	पूर्ण

	fscache_root = kobject_create_and_add("fscache", kernel_kobj);
	अगर (!fscache_root)
		जाओ error_kobj;

	pr_notice("Loaded\n");
	वापस 0;

error_kobj:
	kmem_cache_destroy(fscache_cookie_jar);
error_cookie_jar:
#अगर_घोषित CONFIG_SYSCTL
	unरेजिस्टर_sysctl_table(fscache_sysctl_header);
error_sysctl:
#पूर्ण_अगर
	fscache_proc_cleanup();
error_proc:
	destroy_workqueue(fscache_op_wq);
error_op_wq:
	destroy_workqueue(fscache_object_wq);
error_object_wq:
	वापस ret;
पूर्ण

fs_initcall(fscache_init);

/*
 * clean up on module removal
 */
अटल व्योम __निकास fscache_निकास(व्योम)
अणु
	_enter("");

	kobject_put(fscache_root);
	kmem_cache_destroy(fscache_cookie_jar);
#अगर_घोषित CONFIG_SYSCTL
	unरेजिस्टर_sysctl_table(fscache_sysctl_header);
#पूर्ण_अगर
	fscache_proc_cleanup();
	destroy_workqueue(fscache_op_wq);
	destroy_workqueue(fscache_object_wq);
	pr_notice("Unloaded\n");
पूर्ण

module_निकास(fscache_निकास);
