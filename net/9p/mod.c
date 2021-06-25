<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  net/9p/9p.c
 *
 *  9P entry poपूर्णांक
 *
 *  Copyright (C) 2007 by Latchesar Ionkov <lucho@ionkov.net>
 *  Copyright (C) 2004 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2002 by Ron Minnich <rminnich@lanl.gov>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/moduleparam.h>
#समावेश <net/9p/9p.h>
#समावेश <linux/fs.h>
#समावेश <linux/parser.h>
#समावेश <net/9p/client.h>
#समावेश <net/9p/transport.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>

#अगर_घोषित CONFIG_NET_9P_DEBUG
अचिन्हित पूर्णांक p9_debug_level = 0;	/* feature-rअगरic global debug level  */
EXPORT_SYMBOL(p9_debug_level);
module_param_named(debug, p9_debug_level, uपूर्णांक, 0);
MODULE_PARM_DESC(debug, "9P debugging level");

व्योम _p9_debug(क्रमागत p9_debug_flags level, स्थिर अक्षर *func,
		स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	अगर ((p9_debug_level & level) != level)
		वापस;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (level == P9_DEBUG_9P)
		pr_notice("(%8.8d) %pV", task_pid_nr(current), &vaf);
	अन्यथा
		pr_notice("-- %s (%d): %pV", func, task_pid_nr(current), &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(_p9_debug);
#पूर्ण_अगर

/*
 * Dynamic Transport Registration Routines
 *
 */

अटल DEFINE_SPINLOCK(v9fs_trans_lock);
अटल LIST_HEAD(v9fs_trans_list);

/**
 * v9fs_रेजिस्टर_trans - रेजिस्टर a new transport with 9p
 * @m: काष्ठाure describing the transport module and entry poपूर्णांकs
 *
 */
व्योम v9fs_रेजिस्टर_trans(काष्ठा p9_trans_module *m)
अणु
	spin_lock(&v9fs_trans_lock);
	list_add_tail(&m->list, &v9fs_trans_list);
	spin_unlock(&v9fs_trans_lock);
पूर्ण
EXPORT_SYMBOL(v9fs_रेजिस्टर_trans);

/**
 * v9fs_unरेजिस्टर_trans - unरेजिस्टर a 9p transport
 * @m: the transport to हटाओ
 *
 */
व्योम v9fs_unरेजिस्टर_trans(काष्ठा p9_trans_module *m)
अणु
	spin_lock(&v9fs_trans_lock);
	list_del_init(&m->list);
	spin_unlock(&v9fs_trans_lock);
पूर्ण
EXPORT_SYMBOL(v9fs_unरेजिस्टर_trans);

/**
 * v9fs_get_trans_by_name - get transport with the matching name
 * @s: string identअगरying transport
 *
 */
काष्ठा p9_trans_module *v9fs_get_trans_by_name(अक्षर *s)
अणु
	काष्ठा p9_trans_module *t, *found = शून्य;

	spin_lock(&v9fs_trans_lock);

	list_क्रम_each_entry(t, &v9fs_trans_list, list)
		अगर (म_भेद(t->name, s) == 0 &&
		    try_module_get(t->owner)) अणु
			found = t;
			अवरोध;
		पूर्ण

	spin_unlock(&v9fs_trans_lock);
	वापस found;
पूर्ण
EXPORT_SYMBOL(v9fs_get_trans_by_name);

/**
 * v9fs_get_शेष_trans - get the शेष transport
 *
 */

काष्ठा p9_trans_module *v9fs_get_शेष_trans(व्योम)
अणु
	काष्ठा p9_trans_module *t, *found = शून्य;

	spin_lock(&v9fs_trans_lock);

	list_क्रम_each_entry(t, &v9fs_trans_list, list)
		अगर (t->def && try_module_get(t->owner)) अणु
			found = t;
			अवरोध;
		पूर्ण

	अगर (!found)
		list_क्रम_each_entry(t, &v9fs_trans_list, list)
			अगर (try_module_get(t->owner)) अणु
				found = t;
				अवरोध;
			पूर्ण

	spin_unlock(&v9fs_trans_lock);
	वापस found;
पूर्ण
EXPORT_SYMBOL(v9fs_get_शेष_trans);

/**
 * v9fs_put_trans - put trans
 * @m: transport to put
 *
 */
व्योम v9fs_put_trans(काष्ठा p9_trans_module *m)
अणु
	अगर (m)
		module_put(m->owner);
पूर्ण

/**
 * init_p9 - Initialize module
 *
 */
अटल पूर्णांक __init init_p9(व्योम)
अणु
	पूर्णांक ret;

	ret = p9_client_init();
	अगर (ret)
		वापस ret;

	p9_error_init();
	pr_info("Installing 9P2000 support\n");
	p9_trans_fd_init();

	वापस ret;
पूर्ण

/**
 * निकास_p9 - shutकरोwn module
 *
 */

अटल व्योम __निकास निकास_p9(व्योम)
अणु
	pr_info("Unloading 9P2000 support\n");

	p9_trans_fd_निकास();
	p9_client_निकास();
पूर्ण

module_init(init_p9)
module_निकास(निकास_p9)

MODULE_AUTHOR("Latchesar Ionkov <lucho@ionkov.net>");
MODULE_AUTHOR("Eric Van Hensbergen <ericvh@gmail.com>");
MODULE_AUTHOR("Ron Minnich <rminnich@lanl.gov>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Plan 9 Resource Sharing Support (9P2000)");
