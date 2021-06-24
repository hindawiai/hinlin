<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/user-वापस-notअगरier.h>
#समावेश <linux/percpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/export.h>

अटल DEFINE_PER_CPU(काष्ठा hlist_head, वापस_notअगरier_list);

/*
 * Request a notअगरication when the current cpu वापसs to userspace.  Must be
 * called in atomic context.  The notअगरier will also be called in atomic
 * context.
 */
व्योम user_वापस_notअगरier_रेजिस्टर(काष्ठा user_वापस_notअगरier *urn)
अणु
	set_tsk_thपढ़ो_flag(current, TIF_USER_RETURN_NOTIFY);
	hlist_add_head(&urn->link, this_cpu_ptr(&वापस_notअगरier_list));
पूर्ण
EXPORT_SYMBOL_GPL(user_वापस_notअगरier_रेजिस्टर);

/*
 * Removes a रेजिस्टरed user वापस notअगरier.  Must be called from atomic
 * context, and from the same cpu registration occurred in.
 */
व्योम user_वापस_notअगरier_unरेजिस्टर(काष्ठा user_वापस_notअगरier *urn)
अणु
	hlist_del(&urn->link);
	अगर (hlist_empty(this_cpu_ptr(&वापस_notअगरier_list)))
		clear_tsk_thपढ़ो_flag(current, TIF_USER_RETURN_NOTIFY);
पूर्ण
EXPORT_SYMBOL_GPL(user_वापस_notअगरier_unरेजिस्टर);

/* Calls रेजिस्टरed user वापस notअगरiers */
व्योम fire_user_वापस_notअगरiers(व्योम)
अणु
	काष्ठा user_वापस_notअगरier *urn;
	काष्ठा hlist_node *पंचांगp2;
	काष्ठा hlist_head *head;

	head = &get_cpu_var(वापस_notअगरier_list);
	hlist_क्रम_each_entry_safe(urn, पंचांगp2, head, link)
		urn->on_user_वापस(urn);
	put_cpu_var(वापस_notअगरier_list);
पूर्ण
