<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pmi backend क्रम the cbe_cpufreq driver
 *
 * (C) Copyright IBM Deutschland Entwicklung GmbH 2005-2007
 *
 * Author: Christian Krafft <krafft@de.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_qos.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/pmi.h>
#समावेश <यंत्र/cell-regs.h>

#अगर_घोषित DEBUG
#समावेश <यंत्र/समय.स>
#पूर्ण_अगर

#समावेश "ppc_cbe_cpufreq.h"

bool cbe_cpufreq_has_pmi = false;
EXPORT_SYMBOL_GPL(cbe_cpufreq_has_pmi);

/*
 * hardware specअगरic functions
 */

पूर्णांक cbe_cpufreq_set_pmode_pmi(पूर्णांक cpu, अचिन्हित पूर्णांक pmode)
अणु
	पूर्णांक ret;
	pmi_message_t pmi_msg;
#अगर_घोषित DEBUG
	दीर्घ समय;
#पूर्ण_अगर
	pmi_msg.type = PMI_TYPE_FREQ_CHANGE;
	pmi_msg.data1 =	cbe_cpu_to_node(cpu);
	pmi_msg.data2 = pmode;

#अगर_घोषित DEBUG
	समय = jअगरfies;
#पूर्ण_अगर
	pmi_send_message(pmi_msg);

#अगर_घोषित DEBUG
	समय = jअगरfies  - समय;
	समय = jअगरfies_to_msecs(समय);
	pr_debug("had to wait %lu ms for a transition using " \
		 "PMI\n", समय);
#पूर्ण_अगर
	ret = pmi_msg.data2;
	pr_debug("PMI returned slow mode %d\n", ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_cpufreq_set_pmode_pmi);


अटल व्योम cbe_cpufreq_handle_pmi(pmi_message_t pmi_msg)
अणु
	काष्ठा cpufreq_policy *policy;
	काष्ठा freq_qos_request *req;
	u8 node, slow_mode;
	पूर्णांक cpu, ret;

	BUG_ON(pmi_msg.type != PMI_TYPE_FREQ_CHANGE);

	node = pmi_msg.data1;
	slow_mode = pmi_msg.data2;

	cpu = cbe_node_to_cpu(node);

	pr_debug("cbe_handle_pmi: node: %d max_freq: %d\n", node, slow_mode);

	policy = cpufreq_cpu_get(cpu);
	अगर (!policy) अणु
		pr_warn("cpufreq policy not found cpu%d\n", cpu);
		वापस;
	पूर्ण

	req = policy->driver_data;

	ret = freq_qos_update_request(req,
			policy->freq_table[slow_mode].frequency);
	अगर (ret < 0)
		pr_warn("Failed to update freq constraint: %d\n", ret);
	अन्यथा
		pr_debug("limiting node %d to slow mode %d\n", node, slow_mode);

	cpufreq_cpu_put(policy);
पूर्ण

अटल काष्ठा pmi_handler cbe_pmi_handler = अणु
	.type			= PMI_TYPE_FREQ_CHANGE,
	.handle_pmi_message	= cbe_cpufreq_handle_pmi,
पूर्ण;

व्योम cbe_cpufreq_pmi_policy_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा freq_qos_request *req;
	पूर्णांक ret;

	अगर (!cbe_cpufreq_has_pmi)
		वापस;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस;

	ret = freq_qos_add_request(&policy->स्थिरraपूर्णांकs, req, FREQ_QOS_MAX,
				   policy->freq_table[0].frequency);
	अगर (ret < 0) अणु
		pr_err("Failed to add freq constraint (%d)\n", ret);
		kमुक्त(req);
		वापस;
	पूर्ण

	policy->driver_data = req;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_cpufreq_pmi_policy_init);

व्योम cbe_cpufreq_pmi_policy_निकास(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा freq_qos_request *req = policy->driver_data;

	अगर (cbe_cpufreq_has_pmi) अणु
		freq_qos_हटाओ_request(req);
		kमुक्त(req);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cbe_cpufreq_pmi_policy_निकास);

व्योम cbe_cpufreq_pmi_init(व्योम)
अणु
	अगर (!pmi_रेजिस्टर_handler(&cbe_pmi_handler))
		cbe_cpufreq_has_pmi = true;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_cpufreq_pmi_init);

व्योम cbe_cpufreq_pmi_निकास(व्योम)
अणु
	pmi_unरेजिस्टर_handler(&cbe_pmi_handler);
	cbe_cpufreq_has_pmi = false;
पूर्ण
EXPORT_SYMBOL_GPL(cbe_cpufreq_pmi_निकास);
