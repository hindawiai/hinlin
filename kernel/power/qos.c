<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Power Management Quality of Service (PM QoS) support base.
 *
 * Copyright (C) 2020 Intel Corporation
 *
 * Authors:
 *	Mark Gross <mgross@linux.पूर्णांकel.com>
 *	Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 *
 * Provided here is an पूर्णांकerface क्रम specअगरying PM QoS dependencies.  It allows
 * entities depending on QoS स्थिरraपूर्णांकs to रेजिस्टर their requests which are
 * aggregated as appropriate to produce effective स्थिरraपूर्णांकs (target values)
 * that can be monitored by entities needing to respect them, either by polling
 * or through a built-in notअगरication mechanism.
 *
 * In addition to the basic functionality, more specअगरic पूर्णांकerfaces क्रम managing
 * global CPU latency QoS requests and frequency QoS requests are provided.
 */

/*#घोषणा DEBUG*/

#समावेश <linux/pm_qos.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/माला.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/export.h>
#समावेश <trace/events/घातer.h>

/*
 * locking rule: all changes to स्थिरraपूर्णांकs or notअगरiers lists
 * or pm_qos_object list and pm_qos_objects need to happen with pm_qos_lock
 * held, taken with _irqsave.  One lock to rule them all
 */
अटल DEFINE_SPINLOCK(pm_qos_lock);

/**
 * pm_qos_पढ़ो_value - Return the current effective स्थिरraपूर्णांक value.
 * @c: List of PM QoS स्थिरraपूर्णांक requests.
 */
s32 pm_qos_पढ़ो_value(काष्ठा pm_qos_स्थिरraपूर्णांकs *c)
अणु
	वापस READ_ONCE(c->target_value);
पूर्ण

अटल पूर्णांक pm_qos_get_value(काष्ठा pm_qos_स्थिरraपूर्णांकs *c)
अणु
	अगर (plist_head_empty(&c->list))
		वापस c->no_स्थिरraपूर्णांक_value;

	चयन (c->type) अणु
	हाल PM_QOS_MIN:
		वापस plist_first(&c->list)->prio;

	हाल PM_QOS_MAX:
		वापस plist_last(&c->list)->prio;

	शेष:
		WARN(1, "Unknown PM QoS type in %s\n", __func__);
		वापस PM_QOS_DEFAULT_VALUE;
	पूर्ण
पूर्ण

अटल व्योम pm_qos_set_value(काष्ठा pm_qos_स्थिरraपूर्णांकs *c, s32 value)
अणु
	WRITE_ONCE(c->target_value, value);
पूर्ण

/**
 * pm_qos_update_target - Update a list of PM QoS स्थिरraपूर्णांक requests.
 * @c: List of PM QoS requests.
 * @node: Target list entry.
 * @action: Action to carry out (add, update or हटाओ).
 * @value: New request value क्रम the target list entry.
 *
 * Update the given list of PM QoS स्थिरraपूर्णांक requests, @c, by carrying an
 * @action involving the @node list entry and @value on it.
 *
 * The recognized values of @action are PM_QOS_ADD_REQ (store @value in @node
 * and add it to the list), PM_QOS_UPDATE_REQ (हटाओ @node from the list, store
 * @value in it and add it to the list again), and PM_QOS_REMOVE_REQ (हटाओ
 * @node from the list, ignore @value).
 *
 * Return: 1 अगर the aggregate स्थिरraपूर्णांक value has changed, 0  otherwise.
 */
पूर्णांक pm_qos_update_target(काष्ठा pm_qos_स्थिरraपूर्णांकs *c, काष्ठा plist_node *node,
			 क्रमागत pm_qos_req_action action, पूर्णांक value)
अणु
	पूर्णांक prev_value, curr_value, new_value;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pm_qos_lock, flags);

	prev_value = pm_qos_get_value(c);
	अगर (value == PM_QOS_DEFAULT_VALUE)
		new_value = c->शेष_value;
	अन्यथा
		new_value = value;

	चयन (action) अणु
	हाल PM_QOS_REMOVE_REQ:
		plist_del(node, &c->list);
		अवरोध;
	हाल PM_QOS_UPDATE_REQ:
		/*
		 * To change the list, atomically हटाओ, reinit with new value
		 * and add, then see अगर the aggregate has changed.
		 */
		plist_del(node, &c->list);
		fallthrough;
	हाल PM_QOS_ADD_REQ:
		plist_node_init(node, new_value);
		plist_add(node, &c->list);
		अवरोध;
	शेष:
		/* no action */
		;
	पूर्ण

	curr_value = pm_qos_get_value(c);
	pm_qos_set_value(c, curr_value);

	spin_unlock_irqrestore(&pm_qos_lock, flags);

	trace_pm_qos_update_target(action, prev_value, curr_value);

	अगर (prev_value == curr_value)
		वापस 0;

	अगर (c->notअगरiers)
		blocking_notअगरier_call_chain(c->notअगरiers, curr_value, शून्य);

	वापस 1;
पूर्ण

/**
 * pm_qos_flags_हटाओ_req - Remove device PM QoS flags request.
 * @pqf: Device PM QoS flags set to हटाओ the request from.
 * @req: Request to हटाओ from the set.
 */
अटल व्योम pm_qos_flags_हटाओ_req(काष्ठा pm_qos_flags *pqf,
				    काष्ठा pm_qos_flags_request *req)
अणु
	s32 val = 0;

	list_del(&req->node);
	list_क्रम_each_entry(req, &pqf->list, node)
		val |= req->flags;

	pqf->effective_flags = val;
पूर्ण

/**
 * pm_qos_update_flags - Update a set of PM QoS flags.
 * @pqf: Set of PM QoS flags to update.
 * @req: Request to add to the set, to modअगरy, or to हटाओ from the set.
 * @action: Action to take on the set.
 * @val: Value of the request to add or modअगरy.
 *
 * Return: 1 अगर the aggregate स्थिरraपूर्णांक value has changed, 0 otherwise.
 */
bool pm_qos_update_flags(काष्ठा pm_qos_flags *pqf,
			 काष्ठा pm_qos_flags_request *req,
			 क्रमागत pm_qos_req_action action, s32 val)
अणु
	अचिन्हित दीर्घ irqflags;
	s32 prev_value, curr_value;

	spin_lock_irqsave(&pm_qos_lock, irqflags);

	prev_value = list_empty(&pqf->list) ? 0 : pqf->effective_flags;

	चयन (action) अणु
	हाल PM_QOS_REMOVE_REQ:
		pm_qos_flags_हटाओ_req(pqf, req);
		अवरोध;
	हाल PM_QOS_UPDATE_REQ:
		pm_qos_flags_हटाओ_req(pqf, req);
		fallthrough;
	हाल PM_QOS_ADD_REQ:
		req->flags = val;
		INIT_LIST_HEAD(&req->node);
		list_add_tail(&req->node, &pqf->list);
		pqf->effective_flags |= val;
		अवरोध;
	शेष:
		/* no action */
		;
	पूर्ण

	curr_value = list_empty(&pqf->list) ? 0 : pqf->effective_flags;

	spin_unlock_irqrestore(&pm_qos_lock, irqflags);

	trace_pm_qos_update_flags(action, prev_value, curr_value);

	वापस prev_value != curr_value;
पूर्ण

#अगर_घोषित CONFIG_CPU_IDLE
/* Definitions related to the CPU latency QoS. */

अटल काष्ठा pm_qos_स्थिरraपूर्णांकs cpu_latency_स्थिरraपूर्णांकs = अणु
	.list = PLIST_HEAD_INIT(cpu_latency_स्थिरraपूर्णांकs.list),
	.target_value = PM_QOS_CPU_LATENCY_DEFAULT_VALUE,
	.शेष_value = PM_QOS_CPU_LATENCY_DEFAULT_VALUE,
	.no_स्थिरraपूर्णांक_value = PM_QOS_CPU_LATENCY_DEFAULT_VALUE,
	.type = PM_QOS_MIN,
पूर्ण;

/**
 * cpu_latency_qos_limit - Return current प्रणाली-wide CPU latency QoS limit.
 */
s32 cpu_latency_qos_limit(व्योम)
अणु
	वापस pm_qos_पढ़ो_value(&cpu_latency_स्थिरraपूर्णांकs);
पूर्ण

/**
 * cpu_latency_qos_request_active - Check the given PM QoS request.
 * @req: PM QoS request to check.
 *
 * Return: 'true' if @req has been added to the CPU latency QoS list, 'false'
 * otherwise.
 */
bool cpu_latency_qos_request_active(काष्ठा pm_qos_request *req)
अणु
	वापस req->qos == &cpu_latency_स्थिरraपूर्णांकs;
पूर्ण
EXPORT_SYMBOL_GPL(cpu_latency_qos_request_active);

अटल व्योम cpu_latency_qos_apply(काष्ठा pm_qos_request *req,
				  क्रमागत pm_qos_req_action action, s32 value)
अणु
	पूर्णांक ret = pm_qos_update_target(req->qos, &req->node, action, value);
	अगर (ret > 0)
		wake_up_all_idle_cpus();
पूर्ण

/**
 * cpu_latency_qos_add_request - Add new CPU latency QoS request.
 * @req: Poपूर्णांकer to a pपुनः_स्मृतिated handle.
 * @value: Requested स्थिरraपूर्णांक value.
 *
 * Use @value to initialize the request handle poपूर्णांकed to by @req, insert it as
 * a new entry to the CPU latency QoS list and recompute the effective QoS
 * स्थिरraपूर्णांक क्रम that list.
 *
 * Callers need to save the handle क्रम later use in updates and removal of the
 * QoS request represented by it.
 */
व्योम cpu_latency_qos_add_request(काष्ठा pm_qos_request *req, s32 value)
अणु
	अगर (!req)
		वापस;

	अगर (cpu_latency_qos_request_active(req)) अणु
		WARN(1, KERN_ERR "%s called for already added request\n", __func__);
		वापस;
	पूर्ण

	trace_pm_qos_add_request(value);

	req->qos = &cpu_latency_स्थिरraपूर्णांकs;
	cpu_latency_qos_apply(req, PM_QOS_ADD_REQ, value);
पूर्ण
EXPORT_SYMBOL_GPL(cpu_latency_qos_add_request);

/**
 * cpu_latency_qos_update_request - Modअगरy existing CPU latency QoS request.
 * @req : QoS request to update.
 * @new_value: New requested स्थिरraपूर्णांक value.
 *
 * Use @new_value to update the QoS request represented by @req in the CPU
 * latency QoS list aदीर्घ with updating the effective स्थिरraपूर्णांक value क्रम that
 * list.
 */
व्योम cpu_latency_qos_update_request(काष्ठा pm_qos_request *req, s32 new_value)
अणु
	अगर (!req)
		वापस;

	अगर (!cpu_latency_qos_request_active(req)) अणु
		WARN(1, KERN_ERR "%s called for unknown object\n", __func__);
		वापस;
	पूर्ण

	trace_pm_qos_update_request(new_value);

	अगर (new_value == req->node.prio)
		वापस;

	cpu_latency_qos_apply(req, PM_QOS_UPDATE_REQ, new_value);
पूर्ण
EXPORT_SYMBOL_GPL(cpu_latency_qos_update_request);

/**
 * cpu_latency_qos_हटाओ_request - Remove existing CPU latency QoS request.
 * @req: QoS request to हटाओ.
 *
 * Remove the CPU latency QoS request represented by @req from the CPU latency
 * QoS list aदीर्घ with updating the effective स्थिरraपूर्णांक value क्रम that list.
 */
व्योम cpu_latency_qos_हटाओ_request(काष्ठा pm_qos_request *req)
अणु
	अगर (!req)
		वापस;

	अगर (!cpu_latency_qos_request_active(req)) अणु
		WARN(1, KERN_ERR "%s called for unknown object\n", __func__);
		वापस;
	पूर्ण

	trace_pm_qos_हटाओ_request(PM_QOS_DEFAULT_VALUE);

	cpu_latency_qos_apply(req, PM_QOS_REMOVE_REQ, PM_QOS_DEFAULT_VALUE);
	स_रखो(req, 0, माप(*req));
पूर्ण
EXPORT_SYMBOL_GPL(cpu_latency_qos_हटाओ_request);

/* User space पूर्णांकerface to the CPU latency QoS via misc device. */

अटल पूर्णांक cpu_latency_qos_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा pm_qos_request *req;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	cpu_latency_qos_add_request(req, PM_QOS_DEFAULT_VALUE);
	filp->निजी_data = req;

	वापस 0;
पूर्ण

अटल पूर्णांक cpu_latency_qos_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा pm_qos_request *req = filp->निजी_data;

	filp->निजी_data = शून्य;

	cpu_latency_qos_हटाओ_request(req);
	kमुक्त(req);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार cpu_latency_qos_पढ़ो(काष्ठा file *filp, अक्षर __user *buf,
				    माप_प्रकार count, loff_t *f_pos)
अणु
	काष्ठा pm_qos_request *req = filp->निजी_data;
	अचिन्हित दीर्घ flags;
	s32 value;

	अगर (!req || !cpu_latency_qos_request_active(req))
		वापस -EINVAL;

	spin_lock_irqsave(&pm_qos_lock, flags);
	value = pm_qos_get_value(&cpu_latency_स्थिरraपूर्णांकs);
	spin_unlock_irqrestore(&pm_qos_lock, flags);

	वापस simple_पढ़ो_from_buffer(buf, count, f_pos, &value, माप(s32));
पूर्ण

अटल sमाप_प्रकार cpu_latency_qos_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
				     माप_प्रकार count, loff_t *f_pos)
अणु
	s32 value;

	अगर (count == माप(s32)) अणु
		अगर (copy_from_user(&value, buf, माप(s32)))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		पूर्णांक ret;

		ret = kstrtos32_from_user(buf, count, 16, &value);
		अगर (ret)
			वापस ret;
	पूर्ण

	cpu_latency_qos_update_request(filp->निजी_data, value);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations cpu_latency_qos_fops = अणु
	.ग_लिखो = cpu_latency_qos_ग_लिखो,
	.पढ़ो = cpu_latency_qos_पढ़ो,
	.खोलो = cpu_latency_qos_खोलो,
	.release = cpu_latency_qos_release,
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice cpu_latency_qos_miscdev = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "cpu_dma_latency",
	.fops = &cpu_latency_qos_fops,
पूर्ण;

अटल पूर्णांक __init cpu_latency_qos_init(व्योम)
अणु
	पूर्णांक ret;

	ret = misc_रेजिस्टर(&cpu_latency_qos_miscdev);
	अगर (ret < 0)
		pr_err("%s: %s setup failed\n", __func__,
		       cpu_latency_qos_miscdev.name);

	वापस ret;
पूर्ण
late_initcall(cpu_latency_qos_init);
#पूर्ण_अगर /* CONFIG_CPU_IDLE */

/* Definitions related to the frequency QoS below. */

/**
 * freq_स्थिरraपूर्णांकs_init - Initialize frequency QoS स्थिरraपूर्णांकs.
 * @qos: Frequency QoS स्थिरraपूर्णांकs to initialize.
 */
व्योम freq_स्थिरraपूर्णांकs_init(काष्ठा freq_स्थिरraपूर्णांकs *qos)
अणु
	काष्ठा pm_qos_स्थिरraपूर्णांकs *c;

	c = &qos->min_freq;
	plist_head_init(&c->list);
	c->target_value = FREQ_QOS_MIN_DEFAULT_VALUE;
	c->शेष_value = FREQ_QOS_MIN_DEFAULT_VALUE;
	c->no_स्थिरraपूर्णांक_value = FREQ_QOS_MIN_DEFAULT_VALUE;
	c->type = PM_QOS_MAX;
	c->notअगरiers = &qos->min_freq_notअगरiers;
	BLOCKING_INIT_NOTIFIER_HEAD(c->notअगरiers);

	c = &qos->max_freq;
	plist_head_init(&c->list);
	c->target_value = FREQ_QOS_MAX_DEFAULT_VALUE;
	c->शेष_value = FREQ_QOS_MAX_DEFAULT_VALUE;
	c->no_स्थिरraपूर्णांक_value = FREQ_QOS_MAX_DEFAULT_VALUE;
	c->type = PM_QOS_MIN;
	c->notअगरiers = &qos->max_freq_notअगरiers;
	BLOCKING_INIT_NOTIFIER_HEAD(c->notअगरiers);
पूर्ण

/**
 * freq_qos_पढ़ो_value - Get frequency QoS स्थिरraपूर्णांक क्रम a given list.
 * @qos: Constraपूर्णांकs to evaluate.
 * @type: QoS request type.
 */
s32 freq_qos_पढ़ो_value(काष्ठा freq_स्थिरraपूर्णांकs *qos,
			क्रमागत freq_qos_req_type type)
अणु
	s32 ret;

	चयन (type) अणु
	हाल FREQ_QOS_MIN:
		ret = IS_ERR_OR_शून्य(qos) ?
			FREQ_QOS_MIN_DEFAULT_VALUE :
			pm_qos_पढ़ो_value(&qos->min_freq);
		अवरोध;
	हाल FREQ_QOS_MAX:
		ret = IS_ERR_OR_शून्य(qos) ?
			FREQ_QOS_MAX_DEFAULT_VALUE :
			pm_qos_पढ़ो_value(&qos->max_freq);
		अवरोध;
	शेष:
		WARN_ON(1);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * freq_qos_apply - Add/modअगरy/हटाओ frequency QoS request.
 * @req: Constraपूर्णांक request to apply.
 * @action: Action to perक्रमm (add/update/हटाओ).
 * @value: Value to assign to the QoS request.
 *
 * This is only meant to be called from inside pm_qos, not drivers.
 */
पूर्णांक freq_qos_apply(काष्ठा freq_qos_request *req,
			  क्रमागत pm_qos_req_action action, s32 value)
अणु
	पूर्णांक ret;

	चयन(req->type) अणु
	हाल FREQ_QOS_MIN:
		ret = pm_qos_update_target(&req->qos->min_freq, &req->pnode,
					   action, value);
		अवरोध;
	हाल FREQ_QOS_MAX:
		ret = pm_qos_update_target(&req->qos->max_freq, &req->pnode,
					   action, value);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * freq_qos_add_request - Insert new frequency QoS request पूर्णांकo a given list.
 * @qos: Constraपूर्णांकs to update.
 * @req: Pपुनः_स्मृतिated request object.
 * @type: Request type.
 * @value: Request value.
 *
 * Insert a new entry पूर्णांकo the @qos list of requests, recompute the effective
 * QoS स्थिरraपूर्णांक value क्रम that list and initialize the @req object.  The
 * caller needs to save that object क्रम later use in updates and removal.
 *
 * Return 1 अगर the effective स्थिरraपूर्णांक value has changed, 0 अगर the effective
 * स्थिरraपूर्णांक value has not changed, or a negative error code on failures.
 */
पूर्णांक freq_qos_add_request(काष्ठा freq_स्थिरraपूर्णांकs *qos,
			 काष्ठा freq_qos_request *req,
			 क्रमागत freq_qos_req_type type, s32 value)
अणु
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(qos) || !req)
		वापस -EINVAL;

	अगर (WARN(freq_qos_request_active(req),
		 "%s() called for active request\n", __func__))
		वापस -EINVAL;

	req->qos = qos;
	req->type = type;
	ret = freq_qos_apply(req, PM_QOS_ADD_REQ, value);
	अगर (ret < 0) अणु
		req->qos = शून्य;
		req->type = 0;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(freq_qos_add_request);

/**
 * freq_qos_update_request - Modअगरy existing frequency QoS request.
 * @req: Request to modअगरy.
 * @new_value: New request value.
 *
 * Update an existing frequency QoS request aदीर्घ with the effective स्थिरraपूर्णांक
 * value क्रम the list of requests it beदीर्घs to.
 *
 * Return 1 अगर the effective स्थिरraपूर्णांक value has changed, 0 अगर the effective
 * स्थिरraपूर्णांक value has not changed, or a negative error code on failures.
 */
पूर्णांक freq_qos_update_request(काष्ठा freq_qos_request *req, s32 new_value)
अणु
	अगर (!req)
		वापस -EINVAL;

	अगर (WARN(!freq_qos_request_active(req),
		 "%s() called for unknown object\n", __func__))
		वापस -EINVAL;

	अगर (req->pnode.prio == new_value)
		वापस 0;

	वापस freq_qos_apply(req, PM_QOS_UPDATE_REQ, new_value);
पूर्ण
EXPORT_SYMBOL_GPL(freq_qos_update_request);

/**
 * freq_qos_हटाओ_request - Remove frequency QoS request from its list.
 * @req: Request to हटाओ.
 *
 * Remove the given frequency QoS request from the list of स्थिरraपूर्णांकs it
 * beदीर्घs to and recompute the effective स्थिरraपूर्णांक value क्रम that list.
 *
 * Return 1 अगर the effective स्थिरraपूर्णांक value has changed, 0 अगर the effective
 * स्थिरraपूर्णांक value has not changed, or a negative error code on failures.
 */
पूर्णांक freq_qos_हटाओ_request(काष्ठा freq_qos_request *req)
अणु
	पूर्णांक ret;

	अगर (!req)
		वापस -EINVAL;

	अगर (WARN(!freq_qos_request_active(req),
		 "%s() called for unknown object\n", __func__))
		वापस -EINVAL;

	ret = freq_qos_apply(req, PM_QOS_REMOVE_REQ, PM_QOS_DEFAULT_VALUE);
	req->qos = शून्य;
	req->type = 0;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(freq_qos_हटाओ_request);

/**
 * freq_qos_add_notअगरier - Add frequency QoS change notअगरier.
 * @qos: List of requests to add the notअगरier to.
 * @type: Request type.
 * @notअगरier: Notअगरier block to add.
 */
पूर्णांक freq_qos_add_notअगरier(काष्ठा freq_स्थिरraपूर्णांकs *qos,
			  क्रमागत freq_qos_req_type type,
			  काष्ठा notअगरier_block *notअगरier)
अणु
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(qos) || !notअगरier)
		वापस -EINVAL;

	चयन (type) अणु
	हाल FREQ_QOS_MIN:
		ret = blocking_notअगरier_chain_रेजिस्टर(qos->min_freq.notअगरiers,
						       notअगरier);
		अवरोध;
	हाल FREQ_QOS_MAX:
		ret = blocking_notअगरier_chain_रेजिस्टर(qos->max_freq.notअगरiers,
						       notअगरier);
		अवरोध;
	शेष:
		WARN_ON(1);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(freq_qos_add_notअगरier);

/**
 * freq_qos_हटाओ_notअगरier - Remove frequency QoS change notअगरier.
 * @qos: List of requests to हटाओ the notअगरier from.
 * @type: Request type.
 * @notअगरier: Notअगरier block to हटाओ.
 */
पूर्णांक freq_qos_हटाओ_notअगरier(काष्ठा freq_स्थिरraपूर्णांकs *qos,
			     क्रमागत freq_qos_req_type type,
			     काष्ठा notअगरier_block *notअगरier)
अणु
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(qos) || !notअगरier)
		वापस -EINVAL;

	चयन (type) अणु
	हाल FREQ_QOS_MIN:
		ret = blocking_notअगरier_chain_unरेजिस्टर(qos->min_freq.notअगरiers,
							 notअगरier);
		अवरोध;
	हाल FREQ_QOS_MAX:
		ret = blocking_notअगरier_chain_unरेजिस्टर(qos->max_freq.notअगरiers,
							 notअगरier);
		अवरोध;
	शेष:
		WARN_ON(1);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(freq_qos_हटाओ_notअगरier);
