<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/memory.h>

#समावेश "notifier-error-inject.h"

अटल पूर्णांक priority;
module_param(priority, पूर्णांक, 0);
MODULE_PARM_DESC(priority, "specify memory notifier priority");

अटल काष्ठा notअगरier_err_inject memory_notअगरier_err_inject = अणु
	.actions = अणु
		अणु NOTIFIER_ERR_INJECT_ACTION(MEM_GOING_ONLINE) पूर्ण,
		अणु NOTIFIER_ERR_INJECT_ACTION(MEM_GOING_OFFLINE) पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा dentry *dir;

अटल पूर्णांक err_inject_init(व्योम)
अणु
	पूर्णांक err;

	dir = notअगरier_err_inject_init("memory", notअगरier_err_inject_dir,
					&memory_notअगरier_err_inject, priority);
	अगर (IS_ERR(dir))
		वापस PTR_ERR(dir);

	err = रेजिस्टर_memory_notअगरier(&memory_notअगरier_err_inject.nb);
	अगर (err)
		debugfs_हटाओ_recursive(dir);

	वापस err;
पूर्ण

अटल व्योम err_inject_निकास(व्योम)
अणु
	unरेजिस्टर_memory_notअगरier(&memory_notअगरier_err_inject.nb);
	debugfs_हटाओ_recursive(dir);
पूर्ण

module_init(err_inject_init);
module_निकास(err_inject_निकास);

MODULE_DESCRIPTION("memory notifier error injection module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Akinobu Mita <akinobu.mita@gmail.com>");
