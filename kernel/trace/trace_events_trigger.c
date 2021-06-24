<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace_events_trigger - trace event triggers
 *
 * Copyright (C) 2013 Tom Zanussi <tom.zanussi@linux.पूर्णांकel.com>
 */

#समावेश <linux/security.h>
#समावेश <linux/module.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/rculist.h>

#समावेश "trace.h"

अटल LIST_HEAD(trigger_commands);
अटल DEFINE_MUTEX(trigger_cmd_mutex);

व्योम trigger_data_मुक्त(काष्ठा event_trigger_data *data)
अणु
	अगर (data->cmd_ops->set_filter)
		data->cmd_ops->set_filter(शून्य, data, शून्य);

	/* make sure current triggers निकास beक्रमe मुक्त */
	tracepoपूर्णांक_synchronize_unरेजिस्टर();

	kमुक्त(data);
पूर्ण

/**
 * event_triggers_call - Call triggers associated with a trace event
 * @file: The trace_event_file associated with the event
 * @rec: The trace entry क्रम the event, शून्य क्रम unconditional invocation
 *
 * For each trigger associated with an event, invoke the trigger
 * function रेजिस्टरed with the associated trigger command.  If rec is
 * non-शून्य, it means that the trigger requires further processing and
 * shouldn't be unconditionally invoked.  If rec is non-शून्य and the
 * trigger has a filter associated with it, rec will checked against
 * the filter and अगर the record matches the trigger will be invoked.
 * If the trigger is a 'post_trigger', meaning it shouldn't be invoked
 * in any हाल until the current event is written, the trigger
 * function isn't invoked but the bit associated with the deferred
 * trigger is set in the वापस value.
 *
 * Returns an क्रमागत event_trigger_type value containing a set bit क्रम
 * any trigger that should be deferred, ETT_NONE अगर nothing to defer.
 *
 * Called from tracepoपूर्णांक handlers (with rcu_पढ़ो_lock_sched() held).
 *
 * Return: an क्रमागत event_trigger_type value containing a set bit क्रम
 * any trigger that should be deferred, ETT_NONE अगर nothing to defer.
 */
क्रमागत event_trigger_type
event_triggers_call(काष्ठा trace_event_file *file,
		    काष्ठा trace_buffer *buffer, व्योम *rec,
		    काष्ठा ring_buffer_event *event)
अणु
	काष्ठा event_trigger_data *data;
	क्रमागत event_trigger_type tt = ETT_NONE;
	काष्ठा event_filter *filter;

	अगर (list_empty(&file->triggers))
		वापस tt;

	list_क्रम_each_entry_rcu(data, &file->triggers, list) अणु
		अगर (data->छोड़ोd)
			जारी;
		अगर (!rec) अणु
			data->ops->func(data, buffer, rec, event);
			जारी;
		पूर्ण
		filter = rcu_dereference_sched(data->filter);
		अगर (filter && !filter_match_preds(filter, rec))
			जारी;
		अगर (event_command_post_trigger(data->cmd_ops)) अणु
			tt |= data->cmd_ops->trigger_type;
			जारी;
		पूर्ण
		data->ops->func(data, buffer, rec, event);
	पूर्ण
	वापस tt;
पूर्ण
EXPORT_SYMBOL_GPL(event_triggers_call);

/**
 * event_triggers_post_call - Call 'post_triggers' क्रम a trace event
 * @file: The trace_event_file associated with the event
 * @tt: क्रमागत event_trigger_type containing a set bit क्रम each trigger to invoke
 *
 * For each trigger associated with an event, invoke the trigger
 * function रेजिस्टरed with the associated trigger command, अगर the
 * corresponding bit is set in the tt क्रमागत passed पूर्णांकo this function.
 * See @event_triggers_call क्रम details on how those bits are set.
 *
 * Called from tracepoपूर्णांक handlers (with rcu_पढ़ो_lock_sched() held).
 */
व्योम
event_triggers_post_call(काष्ठा trace_event_file *file,
			 क्रमागत event_trigger_type tt)
अणु
	काष्ठा event_trigger_data *data;

	list_क्रम_each_entry_rcu(data, &file->triggers, list) अणु
		अगर (data->छोड़ोd)
			जारी;
		अगर (data->cmd_ops->trigger_type & tt)
			data->ops->func(data, शून्य, शून्य, शून्य);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(event_triggers_post_call);

#घोषणा SHOW_AVAILABLE_TRIGGERS	(व्योम *)(1UL)

अटल व्योम *trigger_next(काष्ठा seq_file *m, व्योम *t, loff_t *pos)
अणु
	काष्ठा trace_event_file *event_file = event_file_data(m->निजी);

	अगर (t == SHOW_AVAILABLE_TRIGGERS) अणु
		(*pos)++;
		वापस शून्य;
	पूर्ण
	वापस seq_list_next(t, &event_file->triggers, pos);
पूर्ण

अटल व्योम *trigger_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा trace_event_file *event_file;

	/* ->stop() is called even अगर ->start() fails */
	mutex_lock(&event_mutex);
	event_file = event_file_data(m->निजी);
	अगर (unlikely(!event_file))
		वापस ERR_PTR(-ENODEV);

	अगर (list_empty(&event_file->triggers))
		वापस *pos == 0 ? SHOW_AVAILABLE_TRIGGERS : शून्य;

	वापस seq_list_start(&event_file->triggers, *pos);
पूर्ण

अटल व्योम trigger_stop(काष्ठा seq_file *m, व्योम *t)
अणु
	mutex_unlock(&event_mutex);
पूर्ण

अटल पूर्णांक trigger_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा event_trigger_data *data;
	काष्ठा event_command *p;

	अगर (v == SHOW_AVAILABLE_TRIGGERS) अणु
		seq_माला_दो(m, "# Available triggers:\n");
		seq_अ_दो(m, '#');
		mutex_lock(&trigger_cmd_mutex);
		list_क्रम_each_entry_reverse(p, &trigger_commands, list)
			seq_म_लिखो(m, " %s", p->name);
		seq_अ_दो(m, '\n');
		mutex_unlock(&trigger_cmd_mutex);
		वापस 0;
	पूर्ण

	data = list_entry(v, काष्ठा event_trigger_data, list);
	data->ops->prपूर्णांक(m, data->ops, data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations event_triggers_seq_ops = अणु
	.start = trigger_start,
	.next = trigger_next,
	.stop = trigger_stop,
	.show = trigger_show,
पूर्ण;

अटल पूर्णांक event_trigger_regex_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;

	ret = security_locked_करोwn(LOCKDOWN_TRACEFS);
	अगर (ret)
		वापस ret;

	mutex_lock(&event_mutex);

	अगर (unlikely(!event_file_data(file))) अणु
		mutex_unlock(&event_mutex);
		वापस -ENODEV;
	पूर्ण

	अगर ((file->f_mode & FMODE_WRITE) &&
	    (file->f_flags & O_TRUNC)) अणु
		काष्ठा trace_event_file *event_file;
		काष्ठा event_command *p;

		event_file = event_file_data(file);

		list_क्रम_each_entry(p, &trigger_commands, list) अणु
			अगर (p->unreg_all)
				p->unreg_all(event_file);
		पूर्ण
	पूर्ण

	अगर (file->f_mode & FMODE_READ) अणु
		ret = seq_खोलो(file, &event_triggers_seq_ops);
		अगर (!ret) अणु
			काष्ठा seq_file *m = file->निजी_data;
			m->निजी = file;
		पूर्ण
	पूर्ण

	mutex_unlock(&event_mutex);

	वापस ret;
पूर्ण

पूर्णांक trigger_process_regex(काष्ठा trace_event_file *file, अक्षर *buff)
अणु
	अक्षर *command, *next;
	काष्ठा event_command *p;
	पूर्णांक ret = -EINVAL;

	next = buff = skip_spaces(buff);
	command = strsep(&next, ": \t");
	अगर (next) अणु
		next = skip_spaces(next);
		अगर (!*next)
			next = शून्य;
	पूर्ण
	command = (command[0] != '!') ? command : command + 1;

	mutex_lock(&trigger_cmd_mutex);
	list_क्रम_each_entry(p, &trigger_commands, list) अणु
		अगर (म_भेद(p->name, command) == 0) अणु
			ret = p->func(p, file, buff, command, next);
			जाओ out_unlock;
		पूर्ण
	पूर्ण
 out_unlock:
	mutex_unlock(&trigger_cmd_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार event_trigger_regex_ग_लिखो(काष्ठा file *file,
					 स्थिर अक्षर __user *ubuf,
					 माप_प्रकार cnt, loff_t *ppos)
अणु
	काष्ठा trace_event_file *event_file;
	sमाप_प्रकार ret;
	अक्षर *buf;

	अगर (!cnt)
		वापस 0;

	अगर (cnt >= PAGE_SIZE)
		वापस -EINVAL;

	buf = memdup_user_nul(ubuf, cnt);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	strim(buf);

	mutex_lock(&event_mutex);
	event_file = event_file_data(file);
	अगर (unlikely(!event_file)) अणु
		mutex_unlock(&event_mutex);
		kमुक्त(buf);
		वापस -ENODEV;
	पूर्ण
	ret = trigger_process_regex(event_file, buf);
	mutex_unlock(&event_mutex);

	kमुक्त(buf);
	अगर (ret < 0)
		जाओ out;

	*ppos += cnt;
	ret = cnt;
 out:
	वापस ret;
पूर्ण

अटल पूर्णांक event_trigger_regex_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	mutex_lock(&event_mutex);

	अगर (file->f_mode & FMODE_READ)
		seq_release(inode, file);

	mutex_unlock(&event_mutex);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
event_trigger_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
		    माप_प्रकार cnt, loff_t *ppos)
अणु
	वापस event_trigger_regex_ग_लिखो(filp, ubuf, cnt, ppos);
पूर्ण

अटल पूर्णांक
event_trigger_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	/* Checks क्रम tracefs lockकरोwn */
	वापस event_trigger_regex_खोलो(inode, filp);
पूर्ण

अटल पूर्णांक
event_trigger_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस event_trigger_regex_release(inode, file);
पूर्ण

स्थिर काष्ठा file_operations event_trigger_fops = अणु
	.खोलो = event_trigger_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = event_trigger_ग_लिखो,
	.llseek = tracing_lseek,
	.release = event_trigger_release,
पूर्ण;

/*
 * Currently we only रेजिस्टर event commands from __init, so mark this
 * __init too.
 */
__init पूर्णांक रेजिस्टर_event_command(काष्ठा event_command *cmd)
अणु
	काष्ठा event_command *p;
	पूर्णांक ret = 0;

	mutex_lock(&trigger_cmd_mutex);
	list_क्रम_each_entry(p, &trigger_commands, list) अणु
		अगर (म_भेद(cmd->name, p->name) == 0) अणु
			ret = -EBUSY;
			जाओ out_unlock;
		पूर्ण
	पूर्ण
	list_add(&cmd->list, &trigger_commands);
 out_unlock:
	mutex_unlock(&trigger_cmd_mutex);

	वापस ret;
पूर्ण

/*
 * Currently we only unरेजिस्टर event commands from __init, so mark
 * this __init too.
 */
__init पूर्णांक unरेजिस्टर_event_command(काष्ठा event_command *cmd)
अणु
	काष्ठा event_command *p, *n;
	पूर्णांक ret = -ENODEV;

	mutex_lock(&trigger_cmd_mutex);
	list_क्रम_each_entry_safe(p, n, &trigger_commands, list) अणु
		अगर (म_भेद(cmd->name, p->name) == 0) अणु
			ret = 0;
			list_del_init(&p->list);
			जाओ out_unlock;
		पूर्ण
	पूर्ण
 out_unlock:
	mutex_unlock(&trigger_cmd_mutex);

	वापस ret;
पूर्ण

/**
 * event_trigger_prपूर्णांक - Generic event_trigger_ops @prपूर्णांक implementation
 * @name: The name of the event trigger
 * @m: The seq_file being prपूर्णांकed to
 * @data: Trigger-specअगरic data
 * @filter_str: filter_str to prपूर्णांक, अगर present
 *
 * Common implementation क्रम event triggers to prपूर्णांक themselves.
 *
 * Usually wrapped by a function that simply sets the @name of the
 * trigger command and then invokes this.
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
अटल पूर्णांक
event_trigger_prपूर्णांक(स्थिर अक्षर *name, काष्ठा seq_file *m,
		    व्योम *data, अक्षर *filter_str)
अणु
	दीर्घ count = (दीर्घ)data;

	seq_माला_दो(m, name);

	अगर (count == -1)
		seq_माला_दो(m, ":unlimited");
	अन्यथा
		seq_म_लिखो(m, ":count=%ld", count);

	अगर (filter_str)
		seq_म_लिखो(m, " if %s\n", filter_str);
	अन्यथा
		seq_अ_दो(m, '\n');

	वापस 0;
पूर्ण

/**
 * event_trigger_init - Generic event_trigger_ops @init implementation
 * @ops: The trigger ops associated with the trigger
 * @data: Trigger-specअगरic data
 *
 * Common implementation of event trigger initialization.
 *
 * Usually used directly as the @init method in event trigger
 * implementations.
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
पूर्णांक event_trigger_init(काष्ठा event_trigger_ops *ops,
		       काष्ठा event_trigger_data *data)
अणु
	data->ref++;
	वापस 0;
पूर्ण

/**
 * event_trigger_मुक्त - Generic event_trigger_ops @मुक्त implementation
 * @ops: The trigger ops associated with the trigger
 * @data: Trigger-specअगरic data
 *
 * Common implementation of event trigger de-initialization.
 *
 * Usually used directly as the @मुक्त method in event trigger
 * implementations.
 */
अटल व्योम
event_trigger_मुक्त(काष्ठा event_trigger_ops *ops,
		   काष्ठा event_trigger_data *data)
अणु
	अगर (WARN_ON_ONCE(data->ref <= 0))
		वापस;

	data->ref--;
	अगर (!data->ref)
		trigger_data_मुक्त(data);
पूर्ण

पूर्णांक trace_event_trigger_enable_disable(काष्ठा trace_event_file *file,
				       पूर्णांक trigger_enable)
अणु
	पूर्णांक ret = 0;

	अगर (trigger_enable) अणु
		अगर (atomic_inc_वापस(&file->पंचांग_ref) > 1)
			वापस ret;
		set_bit(EVENT_खाता_FL_TRIGGER_MODE_BIT, &file->flags);
		ret = trace_event_enable_disable(file, 1, 1);
	पूर्ण अन्यथा अणु
		अगर (atomic_dec_वापस(&file->पंचांग_ref) > 0)
			वापस ret;
		clear_bit(EVENT_खाता_FL_TRIGGER_MODE_BIT, &file->flags);
		ret = trace_event_enable_disable(file, 0, 1);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * clear_event_triggers - Clear all triggers associated with a trace array
 * @tr: The trace array to clear
 *
 * For each trigger, the triggering event has its पंचांग_ref decremented
 * via trace_event_trigger_enable_disable(), and any associated event
 * (in the हाल of enable/disable_event triggers) will have its sm_ref
 * decremented via मुक्त()->trace_event_enable_disable().  That
 * combination effectively reverses the soft-mode/trigger state added
 * by trigger registration.
 *
 * Must be called with event_mutex held.
 */
व्योम
clear_event_triggers(काष्ठा trace_array *tr)
अणु
	काष्ठा trace_event_file *file;

	list_क्रम_each_entry(file, &tr->events, list) अणु
		काष्ठा event_trigger_data *data, *n;
		list_क्रम_each_entry_safe(data, n, &file->triggers, list) अणु
			trace_event_trigger_enable_disable(file, 0);
			list_del_rcu(&data->list);
			अगर (data->ops->मुक्त)
				data->ops->मुक्त(data->ops, data);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * update_cond_flag - Set or reset the TRIGGER_COND bit
 * @file: The trace_event_file associated with the event
 *
 * If an event has triggers and any of those triggers has a filter or
 * a post_trigger, trigger invocation needs to be deferred until after
 * the current event has logged its data, and the event should have
 * its TRIGGER_COND bit set, otherwise the TRIGGER_COND bit should be
 * cleared.
 */
व्योम update_cond_flag(काष्ठा trace_event_file *file)
अणु
	काष्ठा event_trigger_data *data;
	bool set_cond = false;

	lockdep_निश्चित_held(&event_mutex);

	list_क्रम_each_entry(data, &file->triggers, list) अणु
		अगर (data->filter || event_command_post_trigger(data->cmd_ops) ||
		    event_command_needs_rec(data->cmd_ops)) अणु
			set_cond = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (set_cond)
		set_bit(EVENT_खाता_FL_TRIGGER_COND_BIT, &file->flags);
	अन्यथा
		clear_bit(EVENT_खाता_FL_TRIGGER_COND_BIT, &file->flags);
पूर्ण

/**
 * रेजिस्टर_trigger - Generic event_command @reg implementation
 * @glob: The raw string used to रेजिस्टर the trigger
 * @ops: The trigger ops associated with the trigger
 * @data: Trigger-specअगरic data to associate with the trigger
 * @file: The trace_event_file associated with the event
 *
 * Common implementation क्रम event trigger registration.
 *
 * Usually used directly as the @reg method in event command
 * implementations.
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
अटल पूर्णांक रेजिस्टर_trigger(अक्षर *glob, काष्ठा event_trigger_ops *ops,
			    काष्ठा event_trigger_data *data,
			    काष्ठा trace_event_file *file)
अणु
	काष्ठा event_trigger_data *test;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&event_mutex);

	list_क्रम_each_entry(test, &file->triggers, list) अणु
		अगर (test->cmd_ops->trigger_type == data->cmd_ops->trigger_type) अणु
			ret = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (data->ops->init) अणु
		ret = data->ops->init(data->ops, data);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	list_add_rcu(&data->list, &file->triggers);
	ret++;

	update_cond_flag(file);
	अगर (trace_event_trigger_enable_disable(file, 1) < 0) अणु
		list_del_rcu(&data->list);
		update_cond_flag(file);
		ret--;
	पूर्ण
out:
	वापस ret;
पूर्ण

/**
 * unरेजिस्टर_trigger - Generic event_command @unreg implementation
 * @glob: The raw string used to रेजिस्टर the trigger
 * @ops: The trigger ops associated with the trigger
 * @test: Trigger-specअगरic data used to find the trigger to हटाओ
 * @file: The trace_event_file associated with the event
 *
 * Common implementation क्रम event trigger unregistration.
 *
 * Usually used directly as the @unreg method in event command
 * implementations.
 */
अटल व्योम unरेजिस्टर_trigger(अक्षर *glob, काष्ठा event_trigger_ops *ops,
			       काष्ठा event_trigger_data *test,
			       काष्ठा trace_event_file *file)
अणु
	काष्ठा event_trigger_data *data;
	bool unरेजिस्टरed = false;

	lockdep_निश्चित_held(&event_mutex);

	list_क्रम_each_entry(data, &file->triggers, list) अणु
		अगर (data->cmd_ops->trigger_type == test->cmd_ops->trigger_type) अणु
			unरेजिस्टरed = true;
			list_del_rcu(&data->list);
			trace_event_trigger_enable_disable(file, 0);
			update_cond_flag(file);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (unरेजिस्टरed && data->ops->मुक्त)
		data->ops->मुक्त(data->ops, data);
पूर्ण

/**
 * event_trigger_callback - Generic event_command @func implementation
 * @cmd_ops: The command ops, used क्रम trigger registration
 * @file: The trace_event_file associated with the event
 * @glob: The raw string used to रेजिस्टर the trigger
 * @cmd: The cmd portion of the string used to रेजिस्टर the trigger
 * @param: The params portion of the string used to रेजिस्टर the trigger
 *
 * Common implementation क्रम event command parsing and trigger
 * instantiation.
 *
 * Usually used directly as the @func method in event command
 * implementations.
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
अटल पूर्णांक
event_trigger_callback(काष्ठा event_command *cmd_ops,
		       काष्ठा trace_event_file *file,
		       अक्षर *glob, अक्षर *cmd, अक्षर *param)
अणु
	काष्ठा event_trigger_data *trigger_data;
	काष्ठा event_trigger_ops *trigger_ops;
	अक्षर *trigger = शून्य;
	अक्षर *number;
	पूर्णांक ret;

	/* separate the trigger from the filter (t:n [अगर filter]) */
	अगर (param && है_अंक(param[0])) अणु
		trigger = strsep(&param, " \t");
		अगर (param) अणु
			param = skip_spaces(param);
			अगर (!*param)
				param = शून्य;
		पूर्ण
	पूर्ण

	trigger_ops = cmd_ops->get_trigger_ops(cmd, trigger);

	ret = -ENOMEM;
	trigger_data = kzalloc(माप(*trigger_data), GFP_KERNEL);
	अगर (!trigger_data)
		जाओ out;

	trigger_data->count = -1;
	trigger_data->ops = trigger_ops;
	trigger_data->cmd_ops = cmd_ops;
	trigger_data->निजी_data = file;
	INIT_LIST_HEAD(&trigger_data->list);
	INIT_LIST_HEAD(&trigger_data->named_list);

	अगर (glob[0] == '!') अणु
		cmd_ops->unreg(glob+1, trigger_ops, trigger_data, file);
		kमुक्त(trigger_data);
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (trigger) अणु
		number = strsep(&trigger, ":");

		ret = -EINVAL;
		अगर (!म_माप(number))
			जाओ out_मुक्त;

		/*
		 * We use the callback data field (which is a poपूर्णांकer)
		 * as our counter.
		 */
		ret = kम_से_अदीर्घ(number, 0, &trigger_data->count);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	अगर (!param) /* अगर param is non-empty, it's supposed to be a filter */
		जाओ out_reg;

	अगर (!cmd_ops->set_filter)
		जाओ out_reg;

	ret = cmd_ops->set_filter(param, trigger_data, file);
	अगर (ret < 0)
		जाओ out_मुक्त;

 out_reg:
	/* Up the trigger_data count to make sure reg करोesn't मुक्त it on failure */
	event_trigger_init(trigger_ops, trigger_data);
	ret = cmd_ops->reg(glob, trigger_ops, trigger_data, file);
	/*
	 * The above वापसs on success the # of functions enabled,
	 * but अगर it didn't find any functions it वापसs zero.
	 * Consider no functions a failure too.
	 */
	अगर (!ret) अणु
		cmd_ops->unreg(glob, trigger_ops, trigger_data, file);
		ret = -ENOENT;
	पूर्ण अन्यथा अगर (ret > 0)
		ret = 0;

	/* Down the counter of trigger_data or मुक्त it अगर not used anymore */
	event_trigger_मुक्त(trigger_ops, trigger_data);
 out:
	वापस ret;

 out_मुक्त:
	अगर (cmd_ops->set_filter)
		cmd_ops->set_filter(शून्य, trigger_data, शून्य);
	kमुक्त(trigger_data);
	जाओ out;
पूर्ण

/**
 * set_trigger_filter - Generic event_command @set_filter implementation
 * @filter_str: The filter string क्रम the trigger, शून्य to हटाओ filter
 * @trigger_data: Trigger-specअगरic data
 * @file: The trace_event_file associated with the event
 *
 * Common implementation क्रम event command filter parsing and filter
 * instantiation.
 *
 * Usually used directly as the @set_filter method in event command
 * implementations.
 *
 * Also used to हटाओ a filter (अगर filter_str = शून्य).
 *
 * Return: 0 on success, त्रुटि_सं otherwise
 */
पूर्णांक set_trigger_filter(अक्षर *filter_str,
		       काष्ठा event_trigger_data *trigger_data,
		       काष्ठा trace_event_file *file)
अणु
	काष्ठा event_trigger_data *data = trigger_data;
	काष्ठा event_filter *filter = शून्य, *पंचांगp;
	पूर्णांक ret = -EINVAL;
	अक्षर *s;

	अगर (!filter_str) /* clear the current filter */
		जाओ assign;

	s = strsep(&filter_str, " \t");

	अगर (!म_माप(s) || म_भेद(s, "if") != 0)
		जाओ out;

	अगर (!filter_str)
		जाओ out;

	/* The filter is क्रम the 'trigger' event, not the triggered event */
	ret = create_event_filter(file->tr, file->event_call,
				  filter_str, false, &filter);
	/*
	 * If create_event_filter() fails, filter still needs to be मुक्तd.
	 * Which the calling code will करो with data->filter.
	 */
 assign:
	पंचांगp = rcu_access_poपूर्णांकer(data->filter);

	rcu_assign_poपूर्णांकer(data->filter, filter);

	अगर (पंचांगp) अणु
		/* Make sure the call is करोne with the filter */
		tracepoपूर्णांक_synchronize_unरेजिस्टर();
		मुक्त_event_filter(पंचांगp);
	पूर्ण

	kमुक्त(data->filter_str);
	data->filter_str = शून्य;

	अगर (filter_str) अणु
		data->filter_str = kstrdup(filter_str, GFP_KERNEL);
		अगर (!data->filter_str) अणु
			मुक्त_event_filter(rcu_access_poपूर्णांकer(data->filter));
			data->filter = शून्य;
			ret = -ENOMEM;
		पूर्ण
	पूर्ण
 out:
	वापस ret;
पूर्ण

अटल LIST_HEAD(named_triggers);

/**
 * find_named_trigger - Find the common named trigger associated with @name
 * @name: The name of the set of named triggers to find the common data क्रम
 *
 * Named triggers are sets of triggers that share a common set of
 * trigger data.  The first named trigger रेजिस्टरed with a given name
 * owns the common trigger data that the others subsequently
 * रेजिस्टरed with the same name will reference.  This function
 * वापसs the common trigger data associated with that first
 * रेजिस्टरed instance.
 *
 * Return: the common trigger data क्रम the given named trigger on
 * success, शून्य otherwise.
 */
काष्ठा event_trigger_data *find_named_trigger(स्थिर अक्षर *name)
अणु
	काष्ठा event_trigger_data *data;

	अगर (!name)
		वापस शून्य;

	list_क्रम_each_entry(data, &named_triggers, named_list) अणु
		अगर (data->named_data)
			जारी;
		अगर (म_भेद(data->name, name) == 0)
			वापस data;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * is_named_trigger - determine अगर a given trigger is a named trigger
 * @test: The trigger data to test
 *
 * Return: true अगर 'test' is a named trigger, false otherwise.
 */
bool is_named_trigger(काष्ठा event_trigger_data *test)
अणु
	काष्ठा event_trigger_data *data;

	list_क्रम_each_entry(data, &named_triggers, named_list) अणु
		अगर (test == data)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * save_named_trigger - save the trigger in the named trigger list
 * @name: The name of the named trigger set
 * @data: The trigger data to save
 *
 * Return: 0 अगर successful, negative error otherwise.
 */
पूर्णांक save_named_trigger(स्थिर अक्षर *name, काष्ठा event_trigger_data *data)
अणु
	data->name = kstrdup(name, GFP_KERNEL);
	अगर (!data->name)
		वापस -ENOMEM;

	list_add(&data->named_list, &named_triggers);

	वापस 0;
पूर्ण

/**
 * del_named_trigger - delete a trigger from the named trigger list
 * @data: The trigger data to delete
 */
व्योम del_named_trigger(काष्ठा event_trigger_data *data)
अणु
	kमुक्त(data->name);
	data->name = शून्य;

	list_del(&data->named_list);
पूर्ण

अटल व्योम __छोड़ो_named_trigger(काष्ठा event_trigger_data *data, bool छोड़ो)
अणु
	काष्ठा event_trigger_data *test;

	list_क्रम_each_entry(test, &named_triggers, named_list) अणु
		अगर (म_भेद(test->name, data->name) == 0) अणु
			अगर (छोड़ो) अणु
				test->छोड़ोd_पंचांगp = test->छोड़ोd;
				test->छोड़ोd = true;
			पूर्ण अन्यथा अणु
				test->छोड़ोd = test->छोड़ोd_पंचांगp;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * छोड़ो_named_trigger - Pause all named triggers with the same name
 * @data: The trigger data of a named trigger to छोड़ो
 *
 * Pauses a named trigger aदीर्घ with all other triggers having the
 * same name.  Because named triggers share a common set of data,
 * pausing only one is meaningless, so pausing one named trigger needs
 * to छोड़ो all triggers with the same name.
 */
व्योम छोड़ो_named_trigger(काष्ठा event_trigger_data *data)
अणु
	__छोड़ो_named_trigger(data, true);
पूर्ण

/**
 * unछोड़ो_named_trigger - Un-छोड़ो all named triggers with the same name
 * @data: The trigger data of a named trigger to unछोड़ो
 *
 * Un-छोड़ोs a named trigger aदीर्घ with all other triggers having the
 * same name.  Because named triggers share a common set of data,
 * unpausing only one is meaningless, so unpausing one named trigger
 * needs to unछोड़ो all triggers with the same name.
 */
व्योम unछोड़ो_named_trigger(काष्ठा event_trigger_data *data)
अणु
	__छोड़ो_named_trigger(data, false);
पूर्ण

/**
 * set_named_trigger_data - Associate common named trigger data
 * @data: The trigger data of a named trigger to unछोड़ो
 *
 * Named triggers are sets of triggers that share a common set of
 * trigger data.  The first named trigger रेजिस्टरed with a given name
 * owns the common trigger data that the others subsequently
 * रेजिस्टरed with the same name will reference.  This function
 * associates the common trigger data from the first trigger with the
 * given trigger.
 */
व्योम set_named_trigger_data(काष्ठा event_trigger_data *data,
			    काष्ठा event_trigger_data *named_data)
अणु
	data->named_data = named_data;
पूर्ण

काष्ठा event_trigger_data *
get_named_trigger_data(काष्ठा event_trigger_data *data)
अणु
	वापस data->named_data;
पूर्ण

अटल व्योम
traceon_trigger(काष्ठा event_trigger_data *data,
		काष्ठा trace_buffer *buffer, व्योम *rec,
		काष्ठा ring_buffer_event *event)
अणु
	अगर (tracing_is_on())
		वापस;

	tracing_on();
पूर्ण

अटल व्योम
traceon_count_trigger(काष्ठा event_trigger_data *data,
		      काष्ठा trace_buffer *buffer, व्योम *rec,
		      काष्ठा ring_buffer_event *event)
अणु
	अगर (tracing_is_on())
		वापस;

	अगर (!data->count)
		वापस;

	अगर (data->count != -1)
		(data->count)--;

	tracing_on();
पूर्ण

अटल व्योम
traceoff_trigger(काष्ठा event_trigger_data *data,
		 काष्ठा trace_buffer *buffer, व्योम *rec,
		 काष्ठा ring_buffer_event *event)
अणु
	अगर (!tracing_is_on())
		वापस;

	tracing_off();
पूर्ण

अटल व्योम
traceoff_count_trigger(काष्ठा event_trigger_data *data,
		       काष्ठा trace_buffer *buffer, व्योम *rec,
		       काष्ठा ring_buffer_event *event)
अणु
	अगर (!tracing_is_on())
		वापस;

	अगर (!data->count)
		वापस;

	अगर (data->count != -1)
		(data->count)--;

	tracing_off();
पूर्ण

अटल पूर्णांक
traceon_trigger_prपूर्णांक(काष्ठा seq_file *m, काष्ठा event_trigger_ops *ops,
		      काष्ठा event_trigger_data *data)
अणु
	वापस event_trigger_prपूर्णांक("traceon", m, (व्योम *)data->count,
				   data->filter_str);
पूर्ण

अटल पूर्णांक
traceoff_trigger_prपूर्णांक(काष्ठा seq_file *m, काष्ठा event_trigger_ops *ops,
		       काष्ठा event_trigger_data *data)
अणु
	वापस event_trigger_prपूर्णांक("traceoff", m, (व्योम *)data->count,
				   data->filter_str);
पूर्ण

अटल काष्ठा event_trigger_ops traceon_trigger_ops = अणु
	.func			= traceon_trigger,
	.prपूर्णांक			= traceon_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops traceon_count_trigger_ops = अणु
	.func			= traceon_count_trigger,
	.prपूर्णांक			= traceon_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops traceoff_trigger_ops = अणु
	.func			= traceoff_trigger,
	.prपूर्णांक			= traceoff_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops traceoff_count_trigger_ops = अणु
	.func			= traceoff_count_trigger,
	.prपूर्णांक			= traceoff_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops *
onoff_get_trigger_ops(अक्षर *cmd, अक्षर *param)
अणु
	काष्ठा event_trigger_ops *ops;

	/* we रेजिस्टर both traceon and traceoff to this callback */
	अगर (म_भेद(cmd, "traceon") == 0)
		ops = param ? &traceon_count_trigger_ops :
			&traceon_trigger_ops;
	अन्यथा
		ops = param ? &traceoff_count_trigger_ops :
			&traceoff_trigger_ops;

	वापस ops;
पूर्ण

अटल काष्ठा event_command trigger_traceon_cmd = अणु
	.name			= "traceon",
	.trigger_type		= ETT_TRACE_ONOFF,
	.func			= event_trigger_callback,
	.reg			= रेजिस्टर_trigger,
	.unreg			= unरेजिस्टर_trigger,
	.get_trigger_ops	= onoff_get_trigger_ops,
	.set_filter		= set_trigger_filter,
पूर्ण;

अटल काष्ठा event_command trigger_traceoff_cmd = अणु
	.name			= "traceoff",
	.trigger_type		= ETT_TRACE_ONOFF,
	.flags			= EVENT_CMD_FL_POST_TRIGGER,
	.func			= event_trigger_callback,
	.reg			= रेजिस्टर_trigger,
	.unreg			= unरेजिस्टर_trigger,
	.get_trigger_ops	= onoff_get_trigger_ops,
	.set_filter		= set_trigger_filter,
पूर्ण;

#अगर_घोषित CONFIG_TRACER_SNAPSHOT
अटल व्योम
snapshot_trigger(काष्ठा event_trigger_data *data,
		 काष्ठा trace_buffer *buffer, व्योम *rec,
		 काष्ठा ring_buffer_event *event)
अणु
	काष्ठा trace_event_file *file = data->निजी_data;

	अगर (file)
		tracing_snapshot_instance(file->tr);
	अन्यथा
		tracing_snapshot();
पूर्ण

अटल व्योम
snapshot_count_trigger(काष्ठा event_trigger_data *data,
		       काष्ठा trace_buffer *buffer, व्योम *rec,
		       काष्ठा ring_buffer_event *event)
अणु
	अगर (!data->count)
		वापस;

	अगर (data->count != -1)
		(data->count)--;

	snapshot_trigger(data, buffer, rec, event);
पूर्ण

अटल पूर्णांक
रेजिस्टर_snapshot_trigger(अक्षर *glob, काष्ठा event_trigger_ops *ops,
			  काष्ठा event_trigger_data *data,
			  काष्ठा trace_event_file *file)
अणु
	अगर (tracing_alloc_snapshot_instance(file->tr) != 0)
		वापस 0;

	वापस रेजिस्टर_trigger(glob, ops, data, file);
पूर्ण

अटल पूर्णांक
snapshot_trigger_prपूर्णांक(काष्ठा seq_file *m, काष्ठा event_trigger_ops *ops,
		       काष्ठा event_trigger_data *data)
अणु
	वापस event_trigger_prपूर्णांक("snapshot", m, (व्योम *)data->count,
				   data->filter_str);
पूर्ण

अटल काष्ठा event_trigger_ops snapshot_trigger_ops = अणु
	.func			= snapshot_trigger,
	.prपूर्णांक			= snapshot_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops snapshot_count_trigger_ops = अणु
	.func			= snapshot_count_trigger,
	.prपूर्णांक			= snapshot_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops *
snapshot_get_trigger_ops(अक्षर *cmd, अक्षर *param)
अणु
	वापस param ? &snapshot_count_trigger_ops : &snapshot_trigger_ops;
पूर्ण

अटल काष्ठा event_command trigger_snapshot_cmd = अणु
	.name			= "snapshot",
	.trigger_type		= ETT_SNAPSHOT,
	.func			= event_trigger_callback,
	.reg			= रेजिस्टर_snapshot_trigger,
	.unreg			= unरेजिस्टर_trigger,
	.get_trigger_ops	= snapshot_get_trigger_ops,
	.set_filter		= set_trigger_filter,
पूर्ण;

अटल __init पूर्णांक रेजिस्टर_trigger_snapshot_cmd(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_event_command(&trigger_snapshot_cmd);
	WARN_ON(ret < 0);

	वापस ret;
पूर्ण
#अन्यथा
अटल __init पूर्णांक रेजिस्टर_trigger_snapshot_cmd(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_TRACER_SNAPSHOT */

#अगर_घोषित CONFIG_STACKTRACE
#अगर_घोषित CONFIG_UNWINDER_ORC
/* Skip 2:
 *   event_triggers_post_call()
 *   trace_event_raw_event_xxx()
 */
# define STACK_SKIP 2
#अन्यथा
/*
 * Skip 4:
 *   stacktrace_trigger()
 *   event_triggers_post_call()
 *   trace_event_buffer_commit()
 *   trace_event_raw_event_xxx()
 */
#घोषणा STACK_SKIP 4
#पूर्ण_अगर

अटल व्योम
stacktrace_trigger(काष्ठा event_trigger_data *data,
		   काष्ठा trace_buffer *buffer,  व्योम *rec,
		   काष्ठा ring_buffer_event *event)
अणु
	trace_dump_stack(STACK_SKIP);
पूर्ण

अटल व्योम
stacktrace_count_trigger(काष्ठा event_trigger_data *data,
			 काष्ठा trace_buffer *buffer, व्योम *rec,
			 काष्ठा ring_buffer_event *event)
अणु
	अगर (!data->count)
		वापस;

	अगर (data->count != -1)
		(data->count)--;

	stacktrace_trigger(data, buffer, rec, event);
पूर्ण

अटल पूर्णांक
stacktrace_trigger_prपूर्णांक(काष्ठा seq_file *m, काष्ठा event_trigger_ops *ops,
			 काष्ठा event_trigger_data *data)
अणु
	वापस event_trigger_prपूर्णांक("stacktrace", m, (व्योम *)data->count,
				   data->filter_str);
पूर्ण

अटल काष्ठा event_trigger_ops stacktrace_trigger_ops = अणु
	.func			= stacktrace_trigger,
	.prपूर्णांक			= stacktrace_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops stacktrace_count_trigger_ops = अणु
	.func			= stacktrace_count_trigger,
	.prपूर्णांक			= stacktrace_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops *
stacktrace_get_trigger_ops(अक्षर *cmd, अक्षर *param)
अणु
	वापस param ? &stacktrace_count_trigger_ops : &stacktrace_trigger_ops;
पूर्ण

अटल काष्ठा event_command trigger_stacktrace_cmd = अणु
	.name			= "stacktrace",
	.trigger_type		= ETT_STACKTRACE,
	.flags			= EVENT_CMD_FL_POST_TRIGGER,
	.func			= event_trigger_callback,
	.reg			= रेजिस्टर_trigger,
	.unreg			= unरेजिस्टर_trigger,
	.get_trigger_ops	= stacktrace_get_trigger_ops,
	.set_filter		= set_trigger_filter,
पूर्ण;

अटल __init पूर्णांक रेजिस्टर_trigger_stacktrace_cmd(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_event_command(&trigger_stacktrace_cmd);
	WARN_ON(ret < 0);

	वापस ret;
पूर्ण
#अन्यथा
अटल __init पूर्णांक रेजिस्टर_trigger_stacktrace_cmd(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_STACKTRACE */

अटल __init व्योम unरेजिस्टर_trigger_traceon_traceoff_cmds(व्योम)
अणु
	unरेजिस्टर_event_command(&trigger_traceon_cmd);
	unरेजिस्टर_event_command(&trigger_traceoff_cmd);
पूर्ण

अटल व्योम
event_enable_trigger(काष्ठा event_trigger_data *data,
		     काष्ठा trace_buffer *buffer,  व्योम *rec,
		     काष्ठा ring_buffer_event *event)
अणु
	काष्ठा enable_trigger_data *enable_data = data->निजी_data;

	अगर (enable_data->enable)
		clear_bit(EVENT_खाता_FL_SOFT_DISABLED_BIT, &enable_data->file->flags);
	अन्यथा
		set_bit(EVENT_खाता_FL_SOFT_DISABLED_BIT, &enable_data->file->flags);
पूर्ण

अटल व्योम
event_enable_count_trigger(काष्ठा event_trigger_data *data,
			   काष्ठा trace_buffer *buffer,  व्योम *rec,
			   काष्ठा ring_buffer_event *event)
अणु
	काष्ठा enable_trigger_data *enable_data = data->निजी_data;

	अगर (!data->count)
		वापस;

	/* Skip अगर the event is in a state we want to चयन to */
	अगर (enable_data->enable == !(enable_data->file->flags & EVENT_खाता_FL_SOFT_DISABLED))
		वापस;

	अगर (data->count != -1)
		(data->count)--;

	event_enable_trigger(data, buffer, rec, event);
पूर्ण

पूर्णांक event_enable_trigger_prपूर्णांक(काष्ठा seq_file *m,
			       काष्ठा event_trigger_ops *ops,
			       काष्ठा event_trigger_data *data)
अणु
	काष्ठा enable_trigger_data *enable_data = data->निजी_data;

	seq_म_लिखो(m, "%s:%s:%s",
		   enable_data->hist ?
		   (enable_data->enable ? ENABLE_HIST_STR : DISABLE_HIST_STR) :
		   (enable_data->enable ? ENABLE_EVENT_STR : DISABLE_EVENT_STR),
		   enable_data->file->event_call->class->प्रणाली,
		   trace_event_name(enable_data->file->event_call));

	अगर (data->count == -1)
		seq_माला_दो(m, ":unlimited");
	अन्यथा
		seq_म_लिखो(m, ":count=%ld", data->count);

	अगर (data->filter_str)
		seq_म_लिखो(m, " if %s\n", data->filter_str);
	अन्यथा
		seq_अ_दो(m, '\n');

	वापस 0;
पूर्ण

व्योम event_enable_trigger_मुक्त(काष्ठा event_trigger_ops *ops,
			       काष्ठा event_trigger_data *data)
अणु
	काष्ठा enable_trigger_data *enable_data = data->निजी_data;

	अगर (WARN_ON_ONCE(data->ref <= 0))
		वापस;

	data->ref--;
	अगर (!data->ref) अणु
		/* Remove the SOFT_MODE flag */
		trace_event_enable_disable(enable_data->file, 0, 1);
		module_put(enable_data->file->event_call->mod);
		trigger_data_मुक्त(data);
		kमुक्त(enable_data);
	पूर्ण
पूर्ण

अटल काष्ठा event_trigger_ops event_enable_trigger_ops = अणु
	.func			= event_enable_trigger,
	.prपूर्णांक			= event_enable_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_enable_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops event_enable_count_trigger_ops = अणु
	.func			= event_enable_count_trigger,
	.prपूर्णांक			= event_enable_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_enable_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops event_disable_trigger_ops = अणु
	.func			= event_enable_trigger,
	.prपूर्णांक			= event_enable_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_enable_trigger_मुक्त,
पूर्ण;

अटल काष्ठा event_trigger_ops event_disable_count_trigger_ops = अणु
	.func			= event_enable_count_trigger,
	.prपूर्णांक			= event_enable_trigger_prपूर्णांक,
	.init			= event_trigger_init,
	.मुक्त			= event_enable_trigger_मुक्त,
पूर्ण;

पूर्णांक event_enable_trigger_func(काष्ठा event_command *cmd_ops,
			      काष्ठा trace_event_file *file,
			      अक्षर *glob, अक्षर *cmd, अक्षर *param)
अणु
	काष्ठा trace_event_file *event_enable_file;
	काष्ठा enable_trigger_data *enable_data;
	काष्ठा event_trigger_data *trigger_data;
	काष्ठा event_trigger_ops *trigger_ops;
	काष्ठा trace_array *tr = file->tr;
	स्थिर अक्षर *प्रणाली;
	स्थिर अक्षर *event;
	bool hist = false;
	अक्षर *trigger;
	अक्षर *number;
	bool enable;
	पूर्णांक ret;

	अगर (!param)
		वापस -EINVAL;

	/* separate the trigger from the filter (s:e:n [अगर filter]) */
	trigger = strsep(&param, " \t");
	अगर (!trigger)
		वापस -EINVAL;
	अगर (param) अणु
		param = skip_spaces(param);
		अगर (!*param)
			param = शून्य;
	पूर्ण

	प्रणाली = strsep(&trigger, ":");
	अगर (!trigger)
		वापस -EINVAL;

	event = strsep(&trigger, ":");

	ret = -EINVAL;
	event_enable_file = find_event_file(tr, प्रणाली, event);
	अगर (!event_enable_file)
		जाओ out;

#अगर_घोषित CONFIG_HIST_TRIGGERS
	hist = ((म_भेद(cmd, ENABLE_HIST_STR) == 0) ||
		(म_भेद(cmd, DISABLE_HIST_STR) == 0));

	enable = ((म_भेद(cmd, ENABLE_EVENT_STR) == 0) ||
		  (म_भेद(cmd, ENABLE_HIST_STR) == 0));
#अन्यथा
	enable = म_भेद(cmd, ENABLE_EVENT_STR) == 0;
#पूर्ण_अगर
	trigger_ops = cmd_ops->get_trigger_ops(cmd, trigger);

	ret = -ENOMEM;
	trigger_data = kzalloc(माप(*trigger_data), GFP_KERNEL);
	अगर (!trigger_data)
		जाओ out;

	enable_data = kzalloc(माप(*enable_data), GFP_KERNEL);
	अगर (!enable_data) अणु
		kमुक्त(trigger_data);
		जाओ out;
	पूर्ण

	trigger_data->count = -1;
	trigger_data->ops = trigger_ops;
	trigger_data->cmd_ops = cmd_ops;
	INIT_LIST_HEAD(&trigger_data->list);
	RCU_INIT_POINTER(trigger_data->filter, शून्य);

	enable_data->hist = hist;
	enable_data->enable = enable;
	enable_data->file = event_enable_file;
	trigger_data->निजी_data = enable_data;

	अगर (glob[0] == '!') अणु
		cmd_ops->unreg(glob+1, trigger_ops, trigger_data, file);
		kमुक्त(trigger_data);
		kमुक्त(enable_data);
		ret = 0;
		जाओ out;
	पूर्ण

	/* Up the trigger_data count to make sure nothing मुक्तs it on failure */
	event_trigger_init(trigger_ops, trigger_data);

	अगर (trigger) अणु
		number = strsep(&trigger, ":");

		ret = -EINVAL;
		अगर (!म_माप(number))
			जाओ out_मुक्त;

		/*
		 * We use the callback data field (which is a poपूर्णांकer)
		 * as our counter.
		 */
		ret = kम_से_अदीर्घ(number, 0, &trigger_data->count);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	अगर (!param) /* अगर param is non-empty, it's supposed to be a filter */
		जाओ out_reg;

	अगर (!cmd_ops->set_filter)
		जाओ out_reg;

	ret = cmd_ops->set_filter(param, trigger_data, file);
	अगर (ret < 0)
		जाओ out_मुक्त;

 out_reg:
	/* Don't let event modules unload जबतक probe रेजिस्टरed */
	ret = try_module_get(event_enable_file->event_call->mod);
	अगर (!ret) अणु
		ret = -EBUSY;
		जाओ out_मुक्त;
	पूर्ण

	ret = trace_event_enable_disable(event_enable_file, 1, 1);
	अगर (ret < 0)
		जाओ out_put;
	ret = cmd_ops->reg(glob, trigger_ops, trigger_data, file);
	/*
	 * The above वापसs on success the # of functions enabled,
	 * but अगर it didn't find any functions it वापसs zero.
	 * Consider no functions a failure too.
	 */
	अगर (!ret) अणु
		ret = -ENOENT;
		जाओ out_disable;
	पूर्ण अन्यथा अगर (ret < 0)
		जाओ out_disable;
	/* Just वापस zero, not the number of enabled functions */
	ret = 0;
	event_trigger_मुक्त(trigger_ops, trigger_data);
 out:
	वापस ret;

 out_disable:
	trace_event_enable_disable(event_enable_file, 0, 1);
 out_put:
	module_put(event_enable_file->event_call->mod);
 out_मुक्त:
	अगर (cmd_ops->set_filter)
		cmd_ops->set_filter(शून्य, trigger_data, शून्य);
	event_trigger_मुक्त(trigger_ops, trigger_data);
	kमुक्त(enable_data);
	जाओ out;
पूर्ण

पूर्णांक event_enable_रेजिस्टर_trigger(अक्षर *glob,
				  काष्ठा event_trigger_ops *ops,
				  काष्ठा event_trigger_data *data,
				  काष्ठा trace_event_file *file)
अणु
	काष्ठा enable_trigger_data *enable_data = data->निजी_data;
	काष्ठा enable_trigger_data *test_enable_data;
	काष्ठा event_trigger_data *test;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&event_mutex);

	list_क्रम_each_entry(test, &file->triggers, list) अणु
		test_enable_data = test->निजी_data;
		अगर (test_enable_data &&
		    (test->cmd_ops->trigger_type ==
		     data->cmd_ops->trigger_type) &&
		    (test_enable_data->file == enable_data->file)) अणु
			ret = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (data->ops->init) अणु
		ret = data->ops->init(data->ops, data);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	list_add_rcu(&data->list, &file->triggers);
	ret++;

	update_cond_flag(file);
	अगर (trace_event_trigger_enable_disable(file, 1) < 0) अणु
		list_del_rcu(&data->list);
		update_cond_flag(file);
		ret--;
	पूर्ण
out:
	वापस ret;
पूर्ण

व्योम event_enable_unरेजिस्टर_trigger(अक्षर *glob,
				     काष्ठा event_trigger_ops *ops,
				     काष्ठा event_trigger_data *test,
				     काष्ठा trace_event_file *file)
अणु
	काष्ठा enable_trigger_data *test_enable_data = test->निजी_data;
	काष्ठा enable_trigger_data *enable_data;
	काष्ठा event_trigger_data *data;
	bool unरेजिस्टरed = false;

	lockdep_निश्चित_held(&event_mutex);

	list_क्रम_each_entry(data, &file->triggers, list) अणु
		enable_data = data->निजी_data;
		अगर (enable_data &&
		    (data->cmd_ops->trigger_type ==
		     test->cmd_ops->trigger_type) &&
		    (enable_data->file == test_enable_data->file)) अणु
			unरेजिस्टरed = true;
			list_del_rcu(&data->list);
			trace_event_trigger_enable_disable(file, 0);
			update_cond_flag(file);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (unरेजिस्टरed && data->ops->मुक्त)
		data->ops->मुक्त(data->ops, data);
पूर्ण

अटल काष्ठा event_trigger_ops *
event_enable_get_trigger_ops(अक्षर *cmd, अक्षर *param)
अणु
	काष्ठा event_trigger_ops *ops;
	bool enable;

#अगर_घोषित CONFIG_HIST_TRIGGERS
	enable = ((म_भेद(cmd, ENABLE_EVENT_STR) == 0) ||
		  (म_भेद(cmd, ENABLE_HIST_STR) == 0));
#अन्यथा
	enable = म_भेद(cmd, ENABLE_EVENT_STR) == 0;
#पूर्ण_अगर
	अगर (enable)
		ops = param ? &event_enable_count_trigger_ops :
			&event_enable_trigger_ops;
	अन्यथा
		ops = param ? &event_disable_count_trigger_ops :
			&event_disable_trigger_ops;

	वापस ops;
पूर्ण

अटल काष्ठा event_command trigger_enable_cmd = अणु
	.name			= ENABLE_EVENT_STR,
	.trigger_type		= ETT_EVENT_ENABLE,
	.func			= event_enable_trigger_func,
	.reg			= event_enable_रेजिस्टर_trigger,
	.unreg			= event_enable_unरेजिस्टर_trigger,
	.get_trigger_ops	= event_enable_get_trigger_ops,
	.set_filter		= set_trigger_filter,
पूर्ण;

अटल काष्ठा event_command trigger_disable_cmd = अणु
	.name			= DISABLE_EVENT_STR,
	.trigger_type		= ETT_EVENT_ENABLE,
	.func			= event_enable_trigger_func,
	.reg			= event_enable_रेजिस्टर_trigger,
	.unreg			= event_enable_unरेजिस्टर_trigger,
	.get_trigger_ops	= event_enable_get_trigger_ops,
	.set_filter		= set_trigger_filter,
पूर्ण;

अटल __init व्योम unरेजिस्टर_trigger_enable_disable_cmds(व्योम)
अणु
	unरेजिस्टर_event_command(&trigger_enable_cmd);
	unरेजिस्टर_event_command(&trigger_disable_cmd);
पूर्ण

अटल __init पूर्णांक रेजिस्टर_trigger_enable_disable_cmds(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_event_command(&trigger_enable_cmd);
	अगर (WARN_ON(ret < 0))
		वापस ret;
	ret = रेजिस्टर_event_command(&trigger_disable_cmd);
	अगर (WARN_ON(ret < 0))
		unरेजिस्टर_trigger_enable_disable_cmds();

	वापस ret;
पूर्ण

अटल __init पूर्णांक रेजिस्टर_trigger_traceon_traceoff_cmds(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_event_command(&trigger_traceon_cmd);
	अगर (WARN_ON(ret < 0))
		वापस ret;
	ret = रेजिस्टर_event_command(&trigger_traceoff_cmd);
	अगर (WARN_ON(ret < 0))
		unरेजिस्टर_trigger_traceon_traceoff_cmds();

	वापस ret;
पूर्ण

__init पूर्णांक रेजिस्टर_trigger_cmds(व्योम)
अणु
	रेजिस्टर_trigger_traceon_traceoff_cmds();
	रेजिस्टर_trigger_snapshot_cmd();
	रेजिस्टर_trigger_stacktrace_cmd();
	रेजिस्टर_trigger_enable_disable_cmds();
	रेजिस्टर_trigger_hist_enable_disable_cmds();
	रेजिस्टर_trigger_hist_cmd();

	वापस 0;
पूर्ण
