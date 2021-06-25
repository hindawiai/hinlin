<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * IPVS         An implementation of the IP भव server support क्रम the
 *              LINUX operating प्रणाली.  IPVS is now implemented as a module
 *              over the Netfilter framework. IPVS can be used to build a
 *              high-perक्रमmance and highly available server based on a
 *              cluster of servers.
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *              Peter Kese <peter.kese@ijs.si>
 *
 * Changes:
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/माला.स>
#समावेश <linux/kmod.h>
#समावेश <linux/sysctl.h>

#समावेश <net/ip_vs.h>

EXPORT_SYMBOL(ip_vs_scheduler_err);
/*
 *  IPVS scheduler list
 */
अटल LIST_HEAD(ip_vs_schedulers);

/* semaphore क्रम schedulers */
अटल DEFINE_MUTEX(ip_vs_sched_mutex);


/*
 *  Bind a service with a scheduler
 */
पूर्णांक ip_vs_bind_scheduler(काष्ठा ip_vs_service *svc,
			 काष्ठा ip_vs_scheduler *scheduler)
अणु
	पूर्णांक ret;

	अगर (scheduler->init_service) अणु
		ret = scheduler->init_service(svc);
		अगर (ret) अणु
			pr_err("%s(): init error\n", __func__);
			वापस ret;
		पूर्ण
	पूर्ण
	rcu_assign_poपूर्णांकer(svc->scheduler, scheduler);
	वापस 0;
पूर्ण


/*
 *  Unbind a service with its scheduler
 */
व्योम ip_vs_unbind_scheduler(काष्ठा ip_vs_service *svc,
			    काष्ठा ip_vs_scheduler *sched)
अणु
	काष्ठा ip_vs_scheduler *cur_sched;

	cur_sched = rcu_dereference_रक्षित(svc->scheduler, 1);
	/* This check proves that old 'sched' was installed */
	अगर (!cur_sched)
		वापस;

	अगर (sched->करोne_service)
		sched->करोne_service(svc);
	/* svc->scheduler can be set to शून्य only by caller */
पूर्ण


/*
 *  Get scheduler in the scheduler list by name
 */
अटल काष्ठा ip_vs_scheduler *ip_vs_sched_getbyname(स्थिर अक्षर *sched_name)
अणु
	काष्ठा ip_vs_scheduler *sched;

	IP_VS_DBG(2, "%s(): sched_name \"%s\"\n", __func__, sched_name);

	mutex_lock(&ip_vs_sched_mutex);

	list_क्रम_each_entry(sched, &ip_vs_schedulers, n_list) अणु
		/*
		 * Test and get the modules atomically
		 */
		अगर (sched->module && !try_module_get(sched->module)) अणु
			/*
			 * This scheduler is just deleted
			 */
			जारी;
		पूर्ण
		अगर (म_भेद(sched_name, sched->name)==0) अणु
			/* HIT */
			mutex_unlock(&ip_vs_sched_mutex);
			वापस sched;
		पूर्ण
		module_put(sched->module);
	पूर्ण

	mutex_unlock(&ip_vs_sched_mutex);
	वापस शून्य;
पूर्ण


/*
 *  Lookup scheduler and try to load it अगर it करोesn't exist
 */
काष्ठा ip_vs_scheduler *ip_vs_scheduler_get(स्थिर अक्षर *sched_name)
अणु
	काष्ठा ip_vs_scheduler *sched;

	/*
	 *  Search क्रम the scheduler by sched_name
	 */
	sched = ip_vs_sched_getbyname(sched_name);

	/*
	 *  If scheduler not found, load the module and search again
	 */
	अगर (sched == शून्य) अणु
		request_module("ip_vs_%s", sched_name);
		sched = ip_vs_sched_getbyname(sched_name);
	पूर्ण

	वापस sched;
पूर्ण

व्योम ip_vs_scheduler_put(काष्ठा ip_vs_scheduler *scheduler)
अणु
	अगर (scheduler)
		module_put(scheduler->module);
पूर्ण

/*
 * Common error output helper क्रम schedulers
 */

व्योम ip_vs_scheduler_err(काष्ठा ip_vs_service *svc, स्थिर अक्षर *msg)
अणु
	काष्ठा ip_vs_scheduler *sched = rcu_dereference(svc->scheduler);
	अक्षर *sched_name = sched ? sched->name : "none";

	अगर (svc->fwmark) अणु
		IP_VS_ERR_RL("%s: FWM %u 0x%08X - %s\n",
			     sched_name, svc->fwmark, svc->fwmark, msg);
#अगर_घोषित CONFIG_IP_VS_IPV6
	पूर्ण अन्यथा अगर (svc->af == AF_INET6) अणु
		IP_VS_ERR_RL("%s: %s [%pI6c]:%d - %s\n",
			     sched_name, ip_vs_proto_name(svc->protocol),
			     &svc->addr.in6, ntohs(svc->port), msg);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		IP_VS_ERR_RL("%s: %s %pI4:%d - %s\n",
			     sched_name, ip_vs_proto_name(svc->protocol),
			     &svc->addr.ip, ntohs(svc->port), msg);
	पूर्ण
पूर्ण

/*
 *  Register a scheduler in the scheduler list
 */
पूर्णांक रेजिस्टर_ip_vs_scheduler(काष्ठा ip_vs_scheduler *scheduler)
अणु
	काष्ठा ip_vs_scheduler *sched;

	अगर (!scheduler) अणु
		pr_err("%s(): NULL arg\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!scheduler->name) अणु
		pr_err("%s(): NULL scheduler_name\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* increase the module use count */
	अगर (!ip_vs_use_count_inc())
		वापस -ENOENT;

	mutex_lock(&ip_vs_sched_mutex);

	अगर (!list_empty(&scheduler->n_list)) अणु
		mutex_unlock(&ip_vs_sched_mutex);
		ip_vs_use_count_dec();
		pr_err("%s(): [%s] scheduler already linked\n",
		       __func__, scheduler->name);
		वापस -EINVAL;
	पूर्ण

	/*
	 *  Make sure that the scheduler with this name करोesn't exist
	 *  in the scheduler list.
	 */
	list_क्रम_each_entry(sched, &ip_vs_schedulers, n_list) अणु
		अगर (म_भेद(scheduler->name, sched->name) == 0) अणु
			mutex_unlock(&ip_vs_sched_mutex);
			ip_vs_use_count_dec();
			pr_err("%s(): [%s] scheduler already existed "
			       "in the system\n", __func__, scheduler->name);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/*
	 *	Add it पूर्णांकo the d-linked scheduler list
	 */
	list_add(&scheduler->n_list, &ip_vs_schedulers);
	mutex_unlock(&ip_vs_sched_mutex);

	pr_info("[%s] scheduler registered.\n", scheduler->name);

	वापस 0;
पूर्ण


/*
 *  Unरेजिस्टर a scheduler from the scheduler list
 */
पूर्णांक unरेजिस्टर_ip_vs_scheduler(काष्ठा ip_vs_scheduler *scheduler)
अणु
	अगर (!scheduler) अणु
		pr_err("%s(): NULL arg\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&ip_vs_sched_mutex);
	अगर (list_empty(&scheduler->n_list)) अणु
		mutex_unlock(&ip_vs_sched_mutex);
		pr_err("%s(): [%s] scheduler is not in the list. failed\n",
		       __func__, scheduler->name);
		वापस -EINVAL;
	पूर्ण

	/*
	 *	Remove it from the d-linked scheduler list
	 */
	list_del(&scheduler->n_list);
	mutex_unlock(&ip_vs_sched_mutex);

	/* decrease the module use count */
	ip_vs_use_count_dec();

	pr_info("[%s] scheduler unregistered.\n", scheduler->name);

	वापस 0;
पूर्ण
