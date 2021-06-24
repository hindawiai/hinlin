<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common code क्रम control of lockd and nfsv4 grace periods.
 *
 * Transplanted from lockd code
 */

#समावेश <linux/module.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <linux/fs.h>

अटल अचिन्हित पूर्णांक grace_net_id;
अटल DEFINE_SPINLOCK(grace_lock);

/**
 * locks_start_grace
 * @net: net namespace that this lock manager beदीर्घs to
 * @lm: who this grace period is क्रम
 *
 * A grace period is a period during which locks should not be given
 * out.  Currently grace periods are only enक्रमced by the two lock
 * managers (lockd and nfsd), using the locks_in_grace() function to
 * check when they are in a grace period.
 *
 * This function is called to start a grace period.
 */
व्योम
locks_start_grace(काष्ठा net *net, काष्ठा lock_manager *lm)
अणु
	काष्ठा list_head *grace_list = net_generic(net, grace_net_id);

	spin_lock(&grace_lock);
	अगर (list_empty(&lm->list))
		list_add(&lm->list, grace_list);
	अन्यथा
		WARN(1, "double list_add attempt detected in net %x %s\n",
		     net->ns.inum, (net == &init_net) ? "(init_net)" : "");
	spin_unlock(&grace_lock);
पूर्ण
EXPORT_SYMBOL_GPL(locks_start_grace);

/**
 * locks_end_grace
 * @net: net namespace that this lock manager beदीर्घs to
 * @lm: who this grace period is क्रम
 *
 * Call this function to state that the given lock manager is पढ़ोy to
 * resume regular locking.  The grace period will not end until all lock
 * managers that called locks_start_grace() also call locks_end_grace().
 * Note that callers count on it being safe to call this more than once,
 * and the second call should be a no-op.
 */
व्योम
locks_end_grace(काष्ठा lock_manager *lm)
अणु
	spin_lock(&grace_lock);
	list_del_init(&lm->list);
	spin_unlock(&grace_lock);
पूर्ण
EXPORT_SYMBOL_GPL(locks_end_grace);

अटल bool
__state_in_grace(काष्ठा net *net, bool खोलो)
अणु
	काष्ठा list_head *grace_list = net_generic(net, grace_net_id);
	काष्ठा lock_manager *lm;

	अगर (!खोलो)
		वापस !list_empty(grace_list);

	spin_lock(&grace_lock);
	list_क्रम_each_entry(lm, grace_list, list) अणु
		अगर (lm->block_खोलोs) अणु
			spin_unlock(&grace_lock);
			वापस true;
		पूर्ण
	पूर्ण
	spin_unlock(&grace_lock);
	वापस false;
पूर्ण

/**
 * locks_in_grace
 *
 * Lock managers call this function to determine when it is OK क्रम them
 * to answer ordinary lock requests, and when they should accept only
 * lock reclaims.
 */
bool locks_in_grace(काष्ठा net *net)
अणु
	वापस __state_in_grace(net, false);
पूर्ण
EXPORT_SYMBOL_GPL(locks_in_grace);

bool खोलोs_in_grace(काष्ठा net *net)
अणु
	वापस __state_in_grace(net, true);
पूर्ण
EXPORT_SYMBOL_GPL(खोलोs_in_grace);

अटल पूर्णांक __net_init
grace_init_net(काष्ठा net *net)
अणु
	काष्ठा list_head *grace_list = net_generic(net, grace_net_id);

	INIT_LIST_HEAD(grace_list);
	वापस 0;
पूर्ण

अटल व्योम __net_निकास
grace_निकास_net(काष्ठा net *net)
अणु
	काष्ठा list_head *grace_list = net_generic(net, grace_net_id);

	WARN_ONCE(!list_empty(grace_list),
		  "net %x %s: grace_list is not empty\n",
		  net->ns.inum, __func__);
पूर्ण

अटल काष्ठा pernet_operations grace_net_ops = अणु
	.init = grace_init_net,
	.निकास = grace_निकास_net,
	.id   = &grace_net_id,
	.size = माप(काष्ठा list_head),
पूर्ण;

अटल पूर्णांक __init
init_grace(व्योम)
अणु
	वापस रेजिस्टर_pernet_subsys(&grace_net_ops);
पूर्ण

अटल व्योम __निकास
निकास_grace(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&grace_net_ops);
पूर्ण

MODULE_AUTHOR("Jeff Layton <jlayton@primarydata.com>");
MODULE_LICENSE("GPL");
module_init(init_grace)
module_निकास(निकास_grace)
