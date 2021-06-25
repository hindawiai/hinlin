<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>

#समावेश "notifier-error-inject.h"

अटल पूर्णांक priority;
module_param(priority, पूर्णांक, 0);
MODULE_PARM_DESC(priority, "specify netdevice notifier priority");

अटल काष्ठा notअगरier_err_inject netdev_notअगरier_err_inject = अणु
	.actions = अणु
		अणु NOTIFIER_ERR_INJECT_ACTION(NETDEV_REGISTER) पूर्ण,
		अणु NOTIFIER_ERR_INJECT_ACTION(NETDEV_CHANGEMTU) पूर्ण,
		अणु NOTIFIER_ERR_INJECT_ACTION(NETDEV_CHANGENAME) पूर्ण,
		अणु NOTIFIER_ERR_INJECT_ACTION(NETDEV_PRE_UP) पूर्ण,
		अणु NOTIFIER_ERR_INJECT_ACTION(NETDEV_PRE_TYPE_CHANGE) पूर्ण,
		अणु NOTIFIER_ERR_INJECT_ACTION(NETDEV_POST_INIT) पूर्ण,
		अणु NOTIFIER_ERR_INJECT_ACTION(NETDEV_PRECHANGEMTU) पूर्ण,
		अणु NOTIFIER_ERR_INJECT_ACTION(NETDEV_PRECHANGEUPPER) पूर्ण,
		अणु NOTIFIER_ERR_INJECT_ACTION(NETDEV_CHANGEUPPER) पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा dentry *dir;

अटल पूर्णांक netdev_err_inject_init(व्योम)
अणु
	पूर्णांक err;

	dir = notअगरier_err_inject_init("netdev", notअगरier_err_inject_dir,
				       &netdev_notअगरier_err_inject, priority);
	अगर (IS_ERR(dir))
		वापस PTR_ERR(dir);

	err = रेजिस्टर_netdevice_notअगरier(&netdev_notअगरier_err_inject.nb);
	अगर (err)
		debugfs_हटाओ_recursive(dir);

	वापस err;
पूर्ण

अटल व्योम netdev_err_inject_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&netdev_notअगरier_err_inject.nb);
	debugfs_हटाओ_recursive(dir);
पूर्ण

module_init(netdev_err_inject_init);
module_निकास(netdev_err_inject_निकास);

MODULE_DESCRIPTION("Netdevice notifier error injection module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nikolay Aleksandrov <razor@blackwall.org>");
