<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2017 Arm Ltd.
#घोषणा pr_fmt(fmt) "sdei: " fmt

#समावेश <acpi/ghes.h>
#समावेश <linux/acpi.h>
#समावेश <linux/arm_sdei.h>
#समावेश <linux/arm-smccc.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hardirq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/percpu.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/preempt.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>

/*
 * The call to use to reach the firmware.
 */
अटल यंत्रlinkage व्योम (*sdei_firmware_call)(अचिन्हित दीर्घ function_id,
		      अचिन्हित दीर्घ arg0, अचिन्हित दीर्घ arg1,
		      अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
		      अचिन्हित दीर्घ arg4, काष्ठा arm_smccc_res *res);

/* entry poपूर्णांक from firmware to arch यंत्र code */
अटल अचिन्हित दीर्घ sdei_entry_poपूर्णांक;

काष्ठा sdei_event अणु
	/* These three are रक्षित by the sdei_list_lock */
	काष्ठा list_head	list;
	bool			reरेजिस्टर;
	bool			reenable;

	u32			event_num;
	u8			type;
	u8			priority;

	/* This poपूर्णांकer is handed to firmware as the event argument. */
	जोड़ अणु
		/* Shared events */
		काष्ठा sdei_रेजिस्टरed_event *रेजिस्टरed;

		/* CPU निजी events */
		काष्ठा sdei_रेजिस्टरed_event __percpu *निजी_रेजिस्टरed;
	पूर्ण;
पूर्ण;

/* Take the mutex क्रम any API call or modअगरication. Take the mutex first. */
अटल DEFINE_MUTEX(sdei_events_lock);

/* and then hold this when modअगरying the list */
अटल DEFINE_SPINLOCK(sdei_list_lock);
अटल LIST_HEAD(sdei_list);

/* Private events are रेजिस्टरed/enabled via IPI passing one of these */
काष्ठा sdei_crosscall_args अणु
	काष्ठा sdei_event *event;
	atomic_t errors;
	पूर्णांक first_error;
पूर्ण;

#घोषणा CROSSCALL_INIT(arg, event)		\
	करो अणु					\
		arg.event = event;		\
		arg.first_error = 0;		\
		atomic_set(&arg.errors, 0);	\
	पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक sdei_करो_local_call(smp_call_func_t fn,
				     काष्ठा sdei_event *event)
अणु
	काष्ठा sdei_crosscall_args arg;

	CROSSCALL_INIT(arg, event);
	fn(&arg);

	वापस arg.first_error;
पूर्ण

अटल अंतरभूत पूर्णांक sdei_करो_cross_call(smp_call_func_t fn,
				     काष्ठा sdei_event *event)
अणु
	काष्ठा sdei_crosscall_args arg;

	CROSSCALL_INIT(arg, event);
	on_each_cpu(fn, &arg, true);

	वापस arg.first_error;
पूर्ण

अटल अंतरभूत व्योम
sdei_cross_call_वापस(काष्ठा sdei_crosscall_args *arg, पूर्णांक err)
अणु
	अगर (err && (atomic_inc_वापस(&arg->errors) == 1))
		arg->first_error = err;
पूर्ण

अटल पूर्णांक sdei_to_linux_त्रुटि_सं(अचिन्हित दीर्घ sdei_err)
अणु
	चयन (sdei_err) अणु
	हाल SDEI_NOT_SUPPORTED:
		वापस -EOPNOTSUPP;
	हाल SDEI_INVALID_PARAMETERS:
		वापस -EINVAL;
	हाल SDEI_DENIED:
		वापस -EPERM;
	हाल SDEI_PENDING:
		वापस -EINPROGRESS;
	हाल SDEI_OUT_OF_RESOURCE:
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक invoke_sdei_fn(अचिन्हित दीर्घ function_id, अचिन्हित दीर्घ arg0,
			  अचिन्हित दीर्घ arg1, अचिन्हित दीर्घ arg2,
			  अचिन्हित दीर्घ arg3, अचिन्हित दीर्घ arg4,
			  u64 *result)
अणु
	पूर्णांक err;
	काष्ठा arm_smccc_res res;

	अगर (sdei_firmware_call) अणु
		sdei_firmware_call(function_id, arg0, arg1, arg2, arg3, arg4,
				   &res);
		err = sdei_to_linux_त्रुटि_सं(res.a0);
	पूर्ण अन्यथा अणु
		/*
		 * !sdei_firmware_call means we failed to probe or called
		 * sdei_mark_पूर्णांकerface_broken(). -EIO is not an error वापसed
		 * by sdei_to_linux_त्रुटि_सं() and is used to suppress messages
		 * from this driver.
		 */
		err = -EIO;
		res.a0 = SDEI_NOT_SUPPORTED;
	पूर्ण

	अगर (result)
		*result = res.a0;

	वापस err;
पूर्ण
NOKPROBE_SYMBOL(invoke_sdei_fn);

अटल काष्ठा sdei_event *sdei_event_find(u32 event_num)
अणु
	काष्ठा sdei_event *e, *found = शून्य;

	lockdep_निश्चित_held(&sdei_events_lock);

	spin_lock(&sdei_list_lock);
	list_क्रम_each_entry(e, &sdei_list, list) अणु
		अगर (e->event_num == event_num) अणु
			found = e;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&sdei_list_lock);

	वापस found;
पूर्ण

पूर्णांक sdei_api_event_context(u32 query, u64 *result)
अणु
	वापस invoke_sdei_fn(SDEI_1_0_FN_SDEI_EVENT_CONTEXT, query, 0, 0, 0, 0,
			      result);
पूर्ण
NOKPROBE_SYMBOL(sdei_api_event_context);

अटल पूर्णांक sdei_api_event_get_info(u32 event, u32 info, u64 *result)
अणु
	वापस invoke_sdei_fn(SDEI_1_0_FN_SDEI_EVENT_GET_INFO, event, info, 0,
			      0, 0, result);
पूर्ण

अटल काष्ठा sdei_event *sdei_event_create(u32 event_num,
					    sdei_event_callback *cb,
					    व्योम *cb_arg)
अणु
	पूर्णांक err;
	u64 result;
	काष्ठा sdei_event *event;
	काष्ठा sdei_रेजिस्टरed_event *reg;

	lockdep_निश्चित_held(&sdei_events_lock);

	event = kzalloc(माप(*event), GFP_KERNEL);
	अगर (!event) अणु
		err = -ENOMEM;
		जाओ fail;
	पूर्ण

	INIT_LIST_HEAD(&event->list);
	event->event_num = event_num;

	err = sdei_api_event_get_info(event_num, SDEI_EVENT_INFO_EV_PRIORITY,
				      &result);
	अगर (err)
		जाओ fail;
	event->priority = result;

	err = sdei_api_event_get_info(event_num, SDEI_EVENT_INFO_EV_TYPE,
				      &result);
	अगर (err)
		जाओ fail;
	event->type = result;

	अगर (event->type == SDEI_EVENT_TYPE_SHARED) अणु
		reg = kzalloc(माप(*reg), GFP_KERNEL);
		अगर (!reg) अणु
			err = -ENOMEM;
			जाओ fail;
		पूर्ण

		reg->event_num = event->event_num;
		reg->priority = event->priority;

		reg->callback = cb;
		reg->callback_arg = cb_arg;
		event->रेजिस्टरed = reg;
	पूर्ण अन्यथा अणु
		पूर्णांक cpu;
		काष्ठा sdei_रेजिस्टरed_event __percpu *regs;

		regs = alloc_percpu(काष्ठा sdei_रेजिस्टरed_event);
		अगर (!regs) अणु
			err = -ENOMEM;
			जाओ fail;
		पूर्ण

		क्रम_each_possible_cpu(cpu) अणु
			reg = per_cpu_ptr(regs, cpu);

			reg->event_num = event->event_num;
			reg->priority = event->priority;
			reg->callback = cb;
			reg->callback_arg = cb_arg;
		पूर्ण

		event->निजी_रेजिस्टरed = regs;
	पूर्ण

	spin_lock(&sdei_list_lock);
	list_add(&event->list, &sdei_list);
	spin_unlock(&sdei_list_lock);

	वापस event;

fail:
	kमुक्त(event);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम sdei_event_destroy_llocked(काष्ठा sdei_event *event)
अणु
	lockdep_निश्चित_held(&sdei_events_lock);
	lockdep_निश्चित_held(&sdei_list_lock);

	list_del(&event->list);

	अगर (event->type == SDEI_EVENT_TYPE_SHARED)
		kमुक्त(event->रेजिस्टरed);
	अन्यथा
		मुक्त_percpu(event->निजी_रेजिस्टरed);

	kमुक्त(event);
पूर्ण

अटल व्योम sdei_event_destroy(काष्ठा sdei_event *event)
अणु
	spin_lock(&sdei_list_lock);
	sdei_event_destroy_llocked(event);
	spin_unlock(&sdei_list_lock);
पूर्ण

अटल पूर्णांक sdei_api_get_version(u64 *version)
अणु
	वापस invoke_sdei_fn(SDEI_1_0_FN_SDEI_VERSION, 0, 0, 0, 0, 0, version);
पूर्ण

पूर्णांक sdei_mask_local_cpu(व्योम)
अणु
	पूर्णांक err;

	WARN_ON_ONCE(preemptible());

	err = invoke_sdei_fn(SDEI_1_0_FN_SDEI_PE_MASK, 0, 0, 0, 0, 0, शून्य);
	अगर (err && err != -EIO) अणु
		pr_warn_once("failed to mask CPU[%u]: %d\n",
			      smp_processor_id(), err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम _ipi_mask_cpu(व्योम *ignored)
अणु
	sdei_mask_local_cpu();
पूर्ण

पूर्णांक sdei_unmask_local_cpu(व्योम)
अणु
	पूर्णांक err;

	WARN_ON_ONCE(preemptible());

	err = invoke_sdei_fn(SDEI_1_0_FN_SDEI_PE_UNMASK, 0, 0, 0, 0, 0, शून्य);
	अगर (err && err != -EIO) अणु
		pr_warn_once("failed to unmask CPU[%u]: %d\n",
			     smp_processor_id(), err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम _ipi_unmask_cpu(व्योम *ignored)
अणु
	sdei_unmask_local_cpu();
पूर्ण

अटल व्योम _ipi_निजी_reset(व्योम *ignored)
अणु
	पूर्णांक err;

	err = invoke_sdei_fn(SDEI_1_0_FN_SDEI_PRIVATE_RESET, 0, 0, 0, 0, 0,
			     शून्य);
	अगर (err && err != -EIO)
		pr_warn_once("failed to reset CPU[%u]: %d\n",
			     smp_processor_id(), err);
पूर्ण

अटल पूर्णांक sdei_api_shared_reset(व्योम)
अणु
	वापस invoke_sdei_fn(SDEI_1_0_FN_SDEI_SHARED_RESET, 0, 0, 0, 0, 0,
			      शून्य);
पूर्ण

अटल व्योम sdei_mark_पूर्णांकerface_broken(व्योम)
अणु
	pr_err("disabling SDEI firmware interface\n");
	on_each_cpu(&_ipi_mask_cpu, शून्य, true);
	sdei_firmware_call = शून्य;
पूर्ण

अटल पूर्णांक sdei_platक्रमm_reset(व्योम)
अणु
	पूर्णांक err;

	on_each_cpu(&_ipi_निजी_reset, शून्य, true);
	err = sdei_api_shared_reset();
	अगर (err) अणु
		pr_err("Failed to reset platform: %d\n", err);
		sdei_mark_पूर्णांकerface_broken();
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक sdei_api_event_enable(u32 event_num)
अणु
	वापस invoke_sdei_fn(SDEI_1_0_FN_SDEI_EVENT_ENABLE, event_num, 0, 0, 0,
			      0, शून्य);
पूर्ण

/* Called directly by the hotplug callbacks */
अटल व्योम _local_event_enable(व्योम *data)
अणु
	पूर्णांक err;
	काष्ठा sdei_crosscall_args *arg = data;

	WARN_ON_ONCE(preemptible());

	err = sdei_api_event_enable(arg->event->event_num);

	sdei_cross_call_वापस(arg, err);
पूर्ण

पूर्णांक sdei_event_enable(u32 event_num)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा sdei_event *event;

	mutex_lock(&sdei_events_lock);
	event = sdei_event_find(event_num);
	अगर (!event) अणु
		mutex_unlock(&sdei_events_lock);
		वापस -ENOENT;
	पूर्ण


	cpus_पढ़ो_lock();
	अगर (event->type == SDEI_EVENT_TYPE_SHARED)
		err = sdei_api_event_enable(event->event_num);
	अन्यथा
		err = sdei_करो_cross_call(_local_event_enable, event);

	अगर (!err) अणु
		spin_lock(&sdei_list_lock);
		event->reenable = true;
		spin_unlock(&sdei_list_lock);
	पूर्ण
	cpus_पढ़ो_unlock();
	mutex_unlock(&sdei_events_lock);

	वापस err;
पूर्ण

अटल पूर्णांक sdei_api_event_disable(u32 event_num)
अणु
	वापस invoke_sdei_fn(SDEI_1_0_FN_SDEI_EVENT_DISABLE, event_num, 0, 0,
			      0, 0, शून्य);
पूर्ण

अटल व्योम _ipi_event_disable(व्योम *data)
अणु
	पूर्णांक err;
	काष्ठा sdei_crosscall_args *arg = data;

	err = sdei_api_event_disable(arg->event->event_num);

	sdei_cross_call_वापस(arg, err);
पूर्ण

पूर्णांक sdei_event_disable(u32 event_num)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा sdei_event *event;

	mutex_lock(&sdei_events_lock);
	event = sdei_event_find(event_num);
	अगर (!event) अणु
		mutex_unlock(&sdei_events_lock);
		वापस -ENOENT;
	पूर्ण

	spin_lock(&sdei_list_lock);
	event->reenable = false;
	spin_unlock(&sdei_list_lock);

	अगर (event->type == SDEI_EVENT_TYPE_SHARED)
		err = sdei_api_event_disable(event->event_num);
	अन्यथा
		err = sdei_करो_cross_call(_ipi_event_disable, event);
	mutex_unlock(&sdei_events_lock);

	वापस err;
पूर्ण

अटल पूर्णांक sdei_api_event_unरेजिस्टर(u32 event_num)
अणु
	वापस invoke_sdei_fn(SDEI_1_0_FN_SDEI_EVENT_UNREGISTER, event_num, 0,
			      0, 0, 0, शून्य);
पूर्ण

/* Called directly by the hotplug callbacks */
अटल व्योम _local_event_unरेजिस्टर(व्योम *data)
अणु
	पूर्णांक err;
	काष्ठा sdei_crosscall_args *arg = data;

	WARN_ON_ONCE(preemptible());

	err = sdei_api_event_unरेजिस्टर(arg->event->event_num);

	sdei_cross_call_वापस(arg, err);
पूर्ण

पूर्णांक sdei_event_unरेजिस्टर(u32 event_num)
अणु
	पूर्णांक err;
	काष्ठा sdei_event *event;

	WARN_ON(in_nmi());

	mutex_lock(&sdei_events_lock);
	event = sdei_event_find(event_num);
	अगर (!event) अणु
		pr_warn("Event %u not registered\n", event_num);
		err = -ENOENT;
		जाओ unlock;
	पूर्ण

	spin_lock(&sdei_list_lock);
	event->reरेजिस्टर = false;
	event->reenable = false;
	spin_unlock(&sdei_list_lock);

	अगर (event->type == SDEI_EVENT_TYPE_SHARED)
		err = sdei_api_event_unरेजिस्टर(event->event_num);
	अन्यथा
		err = sdei_करो_cross_call(_local_event_unरेजिस्टर, event);

	अगर (err)
		जाओ unlock;

	sdei_event_destroy(event);
unlock:
	mutex_unlock(&sdei_events_lock);

	वापस err;
पूर्ण

/*
 * unरेजिस्टर events, but करोn't destroy them as they are re-रेजिस्टरed by
 * sdei_reरेजिस्टर_shared().
 */
अटल पूर्णांक sdei_unरेजिस्टर_shared(व्योम)
अणु
	पूर्णांक err = 0;
	काष्ठा sdei_event *event;

	mutex_lock(&sdei_events_lock);
	spin_lock(&sdei_list_lock);
	list_क्रम_each_entry(event, &sdei_list, list) अणु
		अगर (event->type != SDEI_EVENT_TYPE_SHARED)
			जारी;

		err = sdei_api_event_unरेजिस्टर(event->event_num);
		अगर (err)
			अवरोध;
	पूर्ण
	spin_unlock(&sdei_list_lock);
	mutex_unlock(&sdei_events_lock);

	वापस err;
पूर्ण

अटल पूर्णांक sdei_api_event_रेजिस्टर(u32 event_num, अचिन्हित दीर्घ entry_poपूर्णांक,
				   व्योम *arg, u64 flags, u64 affinity)
अणु
	वापस invoke_sdei_fn(SDEI_1_0_FN_SDEI_EVENT_REGISTER, event_num,
			      (अचिन्हित दीर्घ)entry_poपूर्णांक, (अचिन्हित दीर्घ)arg,
			      flags, affinity, शून्य);
पूर्ण

/* Called directly by the hotplug callbacks */
अटल व्योम _local_event_रेजिस्टर(व्योम *data)
अणु
	पूर्णांक err;
	काष्ठा sdei_रेजिस्टरed_event *reg;
	काष्ठा sdei_crosscall_args *arg = data;

	WARN_ON(preemptible());

	reg = per_cpu_ptr(arg->event->निजी_रेजिस्टरed, smp_processor_id());
	err = sdei_api_event_रेजिस्टर(arg->event->event_num, sdei_entry_poपूर्णांक,
				      reg, 0, 0);

	sdei_cross_call_वापस(arg, err);
पूर्ण

पूर्णांक sdei_event_रेजिस्टर(u32 event_num, sdei_event_callback *cb, व्योम *arg)
अणु
	पूर्णांक err;
	काष्ठा sdei_event *event;

	WARN_ON(in_nmi());

	mutex_lock(&sdei_events_lock);
	अगर (sdei_event_find(event_num)) अणु
		pr_warn("Event %u already registered\n", event_num);
		err = -EBUSY;
		जाओ unlock;
	पूर्ण

	event = sdei_event_create(event_num, cb, arg);
	अगर (IS_ERR(event)) अणु
		err = PTR_ERR(event);
		pr_warn("Failed to create event %u: %d\n", event_num, err);
		जाओ unlock;
	पूर्ण

	cpus_पढ़ो_lock();
	अगर (event->type == SDEI_EVENT_TYPE_SHARED) अणु
		err = sdei_api_event_रेजिस्टर(event->event_num,
					      sdei_entry_poपूर्णांक,
					      event->रेजिस्टरed,
					      SDEI_EVENT_REGISTER_RM_ANY, 0);
	पूर्ण अन्यथा अणु
		err = sdei_करो_cross_call(_local_event_रेजिस्टर, event);
		अगर (err)
			sdei_करो_cross_call(_local_event_unरेजिस्टर, event);
	पूर्ण

	अगर (err) अणु
		sdei_event_destroy(event);
		pr_warn("Failed to register event %u: %d\n", event_num, err);
		जाओ cpu_unlock;
	पूर्ण

	spin_lock(&sdei_list_lock);
	event->reरेजिस्टर = true;
	spin_unlock(&sdei_list_lock);
cpu_unlock:
	cpus_पढ़ो_unlock();
unlock:
	mutex_unlock(&sdei_events_lock);
	वापस err;
पूर्ण

अटल पूर्णांक sdei_reरेजिस्टर_shared(व्योम)
अणु
	पूर्णांक err = 0;
	काष्ठा sdei_event *event;

	mutex_lock(&sdei_events_lock);
	spin_lock(&sdei_list_lock);
	list_क्रम_each_entry(event, &sdei_list, list) अणु
		अगर (event->type != SDEI_EVENT_TYPE_SHARED)
			जारी;

		अगर (event->reरेजिस्टर) अणु
			err = sdei_api_event_रेजिस्टर(event->event_num,
					sdei_entry_poपूर्णांक, event->रेजिस्टरed,
					SDEI_EVENT_REGISTER_RM_ANY, 0);
			अगर (err) अणु
				pr_err("Failed to re-register event %u\n",
				       event->event_num);
				sdei_event_destroy_llocked(event);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (event->reenable) अणु
			err = sdei_api_event_enable(event->event_num);
			अगर (err) अणु
				pr_err("Failed to re-enable event %u\n",
				       event->event_num);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&sdei_list_lock);
	mutex_unlock(&sdei_events_lock);

	वापस err;
पूर्ण

अटल पूर्णांक sdei_cpuhp_करोwn(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा sdei_event *event;
	पूर्णांक err;

	/* un-रेजिस्टर निजी events */
	spin_lock(&sdei_list_lock);
	list_क्रम_each_entry(event, &sdei_list, list) अणु
		अगर (event->type == SDEI_EVENT_TYPE_SHARED)
			जारी;

		err = sdei_करो_local_call(_local_event_unरेजिस्टर, event);
		अगर (err) अणु
			pr_err("Failed to unregister event %u: %d\n",
			       event->event_num, err);
		पूर्ण
	पूर्ण
	spin_unlock(&sdei_list_lock);

	वापस sdei_mask_local_cpu();
पूर्ण

अटल पूर्णांक sdei_cpuhp_up(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा sdei_event *event;
	पूर्णांक err;

	/* re-रेजिस्टर/enable निजी events */
	spin_lock(&sdei_list_lock);
	list_क्रम_each_entry(event, &sdei_list, list) अणु
		अगर (event->type == SDEI_EVENT_TYPE_SHARED)
			जारी;

		अगर (event->reरेजिस्टर) अणु
			err = sdei_करो_local_call(_local_event_रेजिस्टर, event);
			अगर (err) अणु
				pr_err("Failed to re-register event %u: %d\n",
				       event->event_num, err);
			पूर्ण
		पूर्ण

		अगर (event->reenable) अणु
			err = sdei_करो_local_call(_local_event_enable, event);
			अगर (err) अणु
				pr_err("Failed to re-enable event %u: %d\n",
				       event->event_num, err);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&sdei_list_lock);

	वापस sdei_unmask_local_cpu();
पूर्ण

/* When entering idle, mask/unmask events क्रम this cpu */
अटल पूर्णांक sdei_pm_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			    व्योम *data)
अणु
	पूर्णांक rv;

	चयन (action) अणु
	हाल CPU_PM_ENTER:
		rv = sdei_mask_local_cpu();
		अवरोध;
	हाल CPU_PM_EXIT:
	हाल CPU_PM_ENTER_FAILED:
		rv = sdei_unmask_local_cpu();
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	अगर (rv)
		वापस notअगरier_from_त्रुटि_सं(rv);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block sdei_pm_nb = अणु
	.notअगरier_call = sdei_pm_notअगरier,
पूर्ण;

अटल पूर्णांक sdei_device_suspend(काष्ठा device *dev)
अणु
	on_each_cpu(_ipi_mask_cpu, शून्य, true);

	वापस 0;
पूर्ण

अटल पूर्णांक sdei_device_resume(काष्ठा device *dev)
अणु
	on_each_cpu(_ipi_unmask_cpu, शून्य, true);

	वापस 0;
पूर्ण

/*
 * We need all events to be reरेजिस्टरed when we resume from hibernate.
 *
 * The sequence is मुक्तze->thaw. Reboot. मुक्तze->restore. We unरेजिस्टर
 * events during मुक्तze, then re-रेजिस्टर and re-enable them during thaw
 * and restore.
 */
अटल पूर्णांक sdei_device_मुक्तze(काष्ठा device *dev)
अणु
	पूर्णांक err;

	/* unरेजिस्टर निजी events */
	cpuhp_हटाओ_state(CPUHP_AP_ARM_SDEI_STARTING);

	err = sdei_unरेजिस्टर_shared();
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक sdei_device_thaw(काष्ठा device *dev)
अणु
	पूर्णांक err;

	/* re-रेजिस्टर shared events */
	err = sdei_reरेजिस्टर_shared();
	अगर (err) अणु
		pr_warn("Failed to re-register shared events...\n");
		sdei_mark_पूर्णांकerface_broken();
		वापस err;
	पूर्ण

	err = cpuhp_setup_state(CPUHP_AP_ARM_SDEI_STARTING, "SDEI",
				&sdei_cpuhp_up, &sdei_cpuhp_करोwn);
	अगर (err)
		pr_warn("Failed to re-register CPU hotplug notifier...\n");

	वापस err;
पूर्ण

अटल पूर्णांक sdei_device_restore(काष्ठा device *dev)
अणु
	पूर्णांक err;

	err = sdei_platक्रमm_reset();
	अगर (err)
		वापस err;

	वापस sdei_device_thaw(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sdei_pm_ops = अणु
	.suspend = sdei_device_suspend,
	.resume = sdei_device_resume,
	.मुक्तze = sdei_device_मुक्तze,
	.thaw = sdei_device_thaw,
	.restore = sdei_device_restore,
पूर्ण;

/*
 * Mask all CPUs and unरेजिस्टर all events on panic, reboot or kexec.
 */
अटल पूर्णांक sdei_reboot_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
				व्योम *data)
अणु
	/*
	 * We are going to reset the पूर्णांकerface, after this there is no poपूर्णांक
	 * करोing work when we take CPUs offline.
	 */
	cpuhp_हटाओ_state(CPUHP_AP_ARM_SDEI_STARTING);

	sdei_platक्रमm_reset();

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block sdei_reboot_nb = अणु
	.notअगरier_call = sdei_reboot_notअगरier,
पूर्ण;

अटल व्योम sdei_smccc_smc(अचिन्हित दीर्घ function_id,
			   अचिन्हित दीर्घ arg0, अचिन्हित दीर्घ arg1,
			   अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
			   अचिन्हित दीर्घ arg4, काष्ठा arm_smccc_res *res)
अणु
	arm_smccc_smc(function_id, arg0, arg1, arg2, arg3, arg4, 0, 0, res);
पूर्ण
NOKPROBE_SYMBOL(sdei_smccc_smc);

अटल व्योम sdei_smccc_hvc(अचिन्हित दीर्घ function_id,
			   अचिन्हित दीर्घ arg0, अचिन्हित दीर्घ arg1,
			   अचिन्हित दीर्घ arg2, अचिन्हित दीर्घ arg3,
			   अचिन्हित दीर्घ arg4, काष्ठा arm_smccc_res *res)
अणु
	arm_smccc_hvc(function_id, arg0, arg1, arg2, arg3, arg4, 0, 0, res);
पूर्ण
NOKPROBE_SYMBOL(sdei_smccc_hvc);

पूर्णांक sdei_रेजिस्टर_ghes(काष्ठा ghes *ghes, sdei_event_callback *normal_cb,
		       sdei_event_callback *critical_cb)
अणु
	पूर्णांक err;
	u64 result;
	u32 event_num;
	sdei_event_callback *cb;

	अगर (!IS_ENABLED(CONFIG_ACPI_APEI_GHES))
		वापस -EOPNOTSUPP;

	event_num = ghes->generic->notअगरy.vector;
	अगर (event_num == 0) अणु
		/*
		 * Event 0 is reserved by the specअगरication क्रम
		 * SDEI_EVENT_SIGNAL.
		 */
		वापस -EINVAL;
	पूर्ण

	err = sdei_api_event_get_info(event_num, SDEI_EVENT_INFO_EV_PRIORITY,
				      &result);
	अगर (err)
		वापस err;

	अगर (result == SDEI_EVENT_PRIORITY_CRITICAL)
		cb = critical_cb;
	अन्यथा
		cb = normal_cb;

	err = sdei_event_रेजिस्टर(event_num, cb, ghes);
	अगर (!err)
		err = sdei_event_enable(event_num);

	वापस err;
पूर्ण

पूर्णांक sdei_unरेजिस्टर_ghes(काष्ठा ghes *ghes)
अणु
	पूर्णांक i;
	पूर्णांक err;
	u32 event_num = ghes->generic->notअगरy.vector;

	might_sleep();

	अगर (!IS_ENABLED(CONFIG_ACPI_APEI_GHES))
		वापस -EOPNOTSUPP;

	/*
	 * The event may be running on another CPU. Disable it
	 * to stop new events, then try to unरेजिस्टर a few बार.
	 */
	err = sdei_event_disable(event_num);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < 3; i++) अणु
		err = sdei_event_unरेजिस्टर(event_num);
		अगर (err != -EINPROGRESS)
			अवरोध;

		schedule();
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक sdei_get_conduit(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर अक्षर *method;
	काष्ठा device_node *np = pdev->dev.of_node;

	sdei_firmware_call = शून्य;
	अगर (np) अणु
		अगर (of_property_पढ़ो_string(np, "method", &method)) अणु
			pr_warn("missing \"method\" property\n");
			वापस SMCCC_CONDUIT_NONE;
		पूर्ण

		अगर (!म_भेद("hvc", method)) अणु
			sdei_firmware_call = &sdei_smccc_hvc;
			वापस SMCCC_CONDUIT_HVC;
		पूर्ण अन्यथा अगर (!म_भेद("smc", method)) अणु
			sdei_firmware_call = &sdei_smccc_smc;
			वापस SMCCC_CONDUIT_SMC;
		पूर्ण

		pr_warn("invalid \"method\" property: %s\n", method);
	पूर्ण अन्यथा अगर (!acpi_disabled) अणु
		अगर (acpi_psci_use_hvc()) अणु
			sdei_firmware_call = &sdei_smccc_hvc;
			वापस SMCCC_CONDUIT_HVC;
		पूर्ण अन्यथा अणु
			sdei_firmware_call = &sdei_smccc_smc;
			वापस SMCCC_CONDUIT_SMC;
		पूर्ण
	पूर्ण

	वापस SMCCC_CONDUIT_NONE;
पूर्ण

अटल पूर्णांक sdei_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	u64 ver = 0;
	पूर्णांक conduit;

	conduit = sdei_get_conduit(pdev);
	अगर (!sdei_firmware_call)
		वापस 0;

	err = sdei_api_get_version(&ver);
	अगर (err) अणु
		pr_err("Failed to get SDEI version: %d\n", err);
		sdei_mark_पूर्णांकerface_broken();
		वापस err;
	पूर्ण

	pr_info("SDEIv%d.%d (0x%x) detected in firmware.\n",
		(पूर्णांक)SDEI_VERSION_MAJOR(ver), (पूर्णांक)SDEI_VERSION_MINOR(ver),
		(पूर्णांक)SDEI_VERSION_VENDOR(ver));

	अगर (SDEI_VERSION_MAJOR(ver) != 1) अणु
		pr_warn("Conflicting SDEI version detected.\n");
		sdei_mark_पूर्णांकerface_broken();
		वापस -EINVAL;
	पूर्ण

	err = sdei_platक्रमm_reset();
	अगर (err)
		वापस err;

	sdei_entry_poपूर्णांक = sdei_arch_get_entry_poपूर्णांक(conduit);
	अगर (!sdei_entry_poपूर्णांक) अणु
		/* Not supported due to hardware or boot configuration */
		sdei_mark_पूर्णांकerface_broken();
		वापस 0;
	पूर्ण

	err = cpu_pm_रेजिस्टर_notअगरier(&sdei_pm_nb);
	अगर (err) अणु
		pr_warn("Failed to register CPU PM notifier...\n");
		जाओ error;
	पूर्ण

	err = रेजिस्टर_reboot_notअगरier(&sdei_reboot_nb);
	अगर (err) अणु
		pr_warn("Failed to register reboot notifier...\n");
		जाओ हटाओ_cpupm;
	पूर्ण

	err = cpuhp_setup_state(CPUHP_AP_ARM_SDEI_STARTING, "SDEI",
				&sdei_cpuhp_up, &sdei_cpuhp_करोwn);
	अगर (err) अणु
		pr_warn("Failed to register CPU hotplug notifier...\n");
		जाओ हटाओ_reboot;
	पूर्ण

	वापस 0;

हटाओ_reboot:
	unरेजिस्टर_reboot_notअगरier(&sdei_reboot_nb);

हटाओ_cpupm:
	cpu_pm_unरेजिस्टर_notअगरier(&sdei_pm_nb);

error:
	sdei_mark_पूर्णांकerface_broken();
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id sdei_of_match[] = अणु
	अणु .compatible = "arm,sdei-1.0" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sdei_driver = अणु
	.driver		= अणु
		.name			= "sdei",
		.pm			= &sdei_pm_ops,
		.of_match_table		= sdei_of_match,
	पूर्ण,
	.probe		= sdei_probe,
पूर्ण;

अटल bool __init sdei_present_acpi(व्योम)
अणु
	acpi_status status;
	काष्ठा acpi_table_header *sdei_table_header;

	अगर (acpi_disabled)
		वापस false;

	status = acpi_get_table(ACPI_SIG_SDEI, 0, &sdei_table_header);
	अगर (ACPI_FAILURE(status) && status != AE_NOT_FOUND) अणु
		स्थिर अक्षर *msg = acpi_क्रमmat_exception(status);

		pr_info("Failed to get ACPI:SDEI table, %s\n", msg);
	पूर्ण
	अगर (ACPI_FAILURE(status))
		वापस false;

	acpi_put_table(sdei_table_header);

	वापस true;
पूर्ण

अटल पूर्णांक __init sdei_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&sdei_driver);
	अगर (ret || !sdei_present_acpi())
		वापस ret;

	pdev = platक्रमm_device_रेजिस्टर_simple(sdei_driver.driver.name,
					       0, शून्य, 0);
	अगर (IS_ERR(pdev)) अणु
		ret = PTR_ERR(pdev);
		platक्रमm_driver_unरेजिस्टर(&sdei_driver);
		pr_info("Failed to register ACPI:SDEI platform device %d\n",
			ret);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * On an ACPI प्रणाली SDEI needs to be पढ़ोy beक्रमe HEST:GHES tries to रेजिस्टर
 * its events. ACPI is initialised from a subsys_initcall(), GHES is initialised
 * by device_initcall(). We want to be called in the middle.
 */
subsys_initcall_sync(sdei_init);

पूर्णांक sdei_event_handler(काष्ठा pt_regs *regs,
		       काष्ठा sdei_रेजिस्टरed_event *arg)
अणु
	पूर्णांक err;
	u32 event_num = arg->event_num;

	err = arg->callback(event_num, regs, arg->callback_arg);
	अगर (err)
		pr_err_ratelimited("event %u on CPU %u failed with error: %d\n",
				   event_num, smp_processor_id(), err);

	वापस err;
पूर्ण
NOKPROBE_SYMBOL(sdei_event_handler);
