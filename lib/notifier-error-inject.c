<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/module.h>

#समावेश "notifier-error-inject.h"

अटल पूर्णांक debugfs_त्रुटि_सं_set(व्योम *data, u64 val)
अणु
	*(पूर्णांक *)data = clamp_t(पूर्णांक, val, -MAX_ERRNO, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_त्रुटि_सं_get(व्योम *data, u64 *val)
अणु
	*val = *(पूर्णांक *)data;
	वापस 0;
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(fops_त्रुटि_सं, debugfs_त्रुटि_सं_get, debugfs_त्रुटि_सं_set,
			"%lld\n");

अटल काष्ठा dentry *debugfs_create_त्रुटि_सं(स्थिर अक्षर *name, umode_t mode,
				काष्ठा dentry *parent, पूर्णांक *value)
अणु
	वापस debugfs_create_file(name, mode, parent, value, &fops_त्रुटि_सं);
पूर्ण

अटल पूर्णांक notअगरier_err_inject_callback(काष्ठा notअगरier_block *nb,
				अचिन्हित दीर्घ val, व्योम *p)
अणु
	पूर्णांक err = 0;
	काष्ठा notअगरier_err_inject *err_inject =
		container_of(nb, काष्ठा notअगरier_err_inject, nb);
	काष्ठा notअगरier_err_inject_action *action;

	क्रम (action = err_inject->actions; action->name; action++) अणु
		अगर (action->val == val) अणु
			err = action->error;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (err)
		pr_info("Injecting error (%d) to %s\n", err, action->name);

	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

काष्ठा dentry *notअगरier_err_inject_dir;
EXPORT_SYMBOL_GPL(notअगरier_err_inject_dir);

काष्ठा dentry *notअगरier_err_inject_init(स्थिर अक्षर *name, काष्ठा dentry *parent,
			काष्ठा notअगरier_err_inject *err_inject, पूर्णांक priority)
अणु
	काष्ठा notअगरier_err_inject_action *action;
	umode_t mode = S_IFREG | S_IRUSR | S_IWUSR;
	काष्ठा dentry *dir;
	काष्ठा dentry *actions_dir;

	err_inject->nb.notअगरier_call = notअगरier_err_inject_callback;
	err_inject->nb.priority = priority;

	dir = debugfs_create_dir(name, parent);

	actions_dir = debugfs_create_dir("actions", dir);

	क्रम (action = err_inject->actions; action->name; action++) अणु
		काष्ठा dentry *action_dir;

		action_dir = debugfs_create_dir(action->name, actions_dir);

		/*
		 * Create debugfs r/w file containing action->error. If
		 * notअगरier call chain is called with action->val, it will
		 * fail with the error code
		 */
		debugfs_create_त्रुटि_सं("error", mode, action_dir, &action->error);
	पूर्ण
	वापस dir;
पूर्ण
EXPORT_SYMBOL_GPL(notअगरier_err_inject_init);

अटल पूर्णांक __init err_inject_init(व्योम)
अणु
	notअगरier_err_inject_dir =
		debugfs_create_dir("notifier-error-inject", शून्य);

	अगर (!notअगरier_err_inject_dir)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम __निकास err_inject_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(notअगरier_err_inject_dir);
पूर्ण

module_init(err_inject_init);
module_निकास(err_inject_निकास);

MODULE_DESCRIPTION("Notifier error injection module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Akinobu Mita <akinobu.mita@gmail.com>");
