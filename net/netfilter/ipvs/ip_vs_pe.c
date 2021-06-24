<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/माला.स>
#समावेश <linux/kmod.h>
#समावेश <linux/sysctl.h>

#समावेश <net/ip_vs.h>

/* IPVS pe list */
अटल LIST_HEAD(ip_vs_pe);

/* semaphore क्रम IPVS PEs. */
अटल DEFINE_MUTEX(ip_vs_pe_mutex);

/* Get pe in the pe list by name */
काष्ठा ip_vs_pe *__ip_vs_pe_getbyname(स्थिर अक्षर *pe_name)
अणु
	काष्ठा ip_vs_pe *pe;

	IP_VS_DBG(10, "%s(): pe_name \"%s\"\n", __func__,
		  pe_name);

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(pe, &ip_vs_pe, n_list) अणु
		/* Test and get the modules atomically */
		अगर (pe->module &&
		    !try_module_get(pe->module)) अणु
			/* This pe is just deleted */
			जारी;
		पूर्ण
		अगर (म_भेद(pe_name, pe->name)==0) अणु
			/* HIT */
			rcu_पढ़ो_unlock();
			वापस pe;
		पूर्ण
		module_put(pe->module);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

/* Lookup pe and try to load it अगर it करोesn't exist */
काष्ठा ip_vs_pe *ip_vs_pe_getbyname(स्थिर अक्षर *name)
अणु
	काष्ठा ip_vs_pe *pe;

	/* Search क्रम the pe by name */
	pe = __ip_vs_pe_getbyname(name);

	/* If pe not found, load the module and search again */
	अगर (!pe) अणु
		request_module("ip_vs_pe_%s", name);
		pe = __ip_vs_pe_getbyname(name);
	पूर्ण

	वापस pe;
पूर्ण

/* Register a pe in the pe list */
पूर्णांक रेजिस्टर_ip_vs_pe(काष्ठा ip_vs_pe *pe)
अणु
	काष्ठा ip_vs_pe *पंचांगp;

	/* increase the module use count */
	अगर (!ip_vs_use_count_inc())
		वापस -ENOENT;

	mutex_lock(&ip_vs_pe_mutex);
	/* Make sure that the pe with this name करोesn't exist
	 * in the pe list.
	 */
	list_क्रम_each_entry(पंचांगp, &ip_vs_pe, n_list) अणु
		अगर (म_भेद(पंचांगp->name, pe->name) == 0) अणु
			mutex_unlock(&ip_vs_pe_mutex);
			ip_vs_use_count_dec();
			pr_err("%s(): [%s] pe already existed "
			       "in the system\n", __func__, pe->name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* Add it पूर्णांकo the d-linked pe list */
	list_add_rcu(&pe->n_list, &ip_vs_pe);
	mutex_unlock(&ip_vs_pe_mutex);

	pr_info("[%s] pe registered.\n", pe->name);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_ip_vs_pe);

/* Unरेजिस्टर a pe from the pe list */
पूर्णांक unरेजिस्टर_ip_vs_pe(काष्ठा ip_vs_pe *pe)
अणु
	mutex_lock(&ip_vs_pe_mutex);
	/* Remove it from the d-linked pe list */
	list_del_rcu(&pe->n_list);
	mutex_unlock(&ip_vs_pe_mutex);

	/* decrease the module use count */
	ip_vs_use_count_dec();

	pr_info("[%s] pe unregistered.\n", pe->name);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_ip_vs_pe);
