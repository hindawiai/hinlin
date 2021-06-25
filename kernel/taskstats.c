<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * taskstats.c - Export per-task statistics to userland
 *
 * Copyright (C) Shailabh Nagar, IBM Corp. 2006
 *           (C) Balbir Singh,   IBM Corp. 2006
 */

#समावेश <linux/kernel.h>
#समावेश <linux/taskstats_kern.h>
#समावेश <linux/tsacct_kern.h>
#समावेश <linux/delayacct.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/cgroupstats.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/pid_namespace.h>
#समावेश <net/genetlink.h>
#समावेश <linux/atomic.h>
#समावेश <linux/sched/cpuसमय.स>

/*
 * Maximum length of a cpumask that can be specअगरied in
 * the TASKSTATS_CMD_ATTR_REGISTER/DEREGISTER_CPUMASK attribute
 */
#घोषणा TASKSTATS_CPUMASK_MAXLEN	(100+6*NR_CPUS)

अटल DEFINE_PER_CPU(__u32, taskstats_seqnum);
अटल पूर्णांक family_रेजिस्टरed;
काष्ठा kmem_cache *taskstats_cache;

अटल काष्ठा genl_family family;

अटल स्थिर काष्ठा nla_policy taskstats_cmd_get_policy[] = अणु
	[TASKSTATS_CMD_ATTR_PID]  = अणु .type = NLA_U32 पूर्ण,
	[TASKSTATS_CMD_ATTR_TGID] = अणु .type = NLA_U32 पूर्ण,
	[TASKSTATS_CMD_ATTR_REGISTER_CPUMASK] = अणु .type = NLA_STRING पूर्ण,
	[TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK] = अणु .type = NLA_STRING पूर्ण,पूर्ण;

अटल स्थिर काष्ठा nla_policy cgroupstats_cmd_get_policy[] = अणु
	[CGROUPSTATS_CMD_ATTR_FD] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

काष्ठा listener अणु
	काष्ठा list_head list;
	pid_t pid;
	अक्षर valid;
पूर्ण;

काष्ठा listener_list अणु
	काष्ठा rw_semaphore sem;
	काष्ठा list_head list;
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा listener_list, listener_array);

क्रमागत actions अणु
	REGISTER,
	DEREGISTER,
	CPU_DONT_CARE
पूर्ण;

अटल पूर्णांक prepare_reply(काष्ठा genl_info *info, u8 cmd, काष्ठा sk_buff **skbp,
				माप_प्रकार size)
अणु
	काष्ठा sk_buff *skb;
	व्योम *reply;

	/*
	 * If new attributes are added, please revisit this allocation
	 */
	skb = genlmsg_new(size, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	अगर (!info) अणु
		पूर्णांक seq = this_cpu_inc_वापस(taskstats_seqnum) - 1;

		reply = genlmsg_put(skb, 0, seq, &family, 0, cmd);
	पूर्ण अन्यथा
		reply = genlmsg_put_reply(skb, info, &family, 0, cmd);
	अगर (reply == शून्य) अणु
		nlmsg_मुक्त(skb);
		वापस -EINVAL;
	पूर्ण

	*skbp = skb;
	वापस 0;
पूर्ण

/*
 * Send taskstats data in @skb to listener with nl_pid @pid
 */
अटल पूर्णांक send_reply(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा genlmsghdr *genlhdr = nlmsg_data(nlmsg_hdr(skb));
	व्योम *reply = genlmsg_data(genlhdr);

	genlmsg_end(skb, reply);

	वापस genlmsg_reply(skb, info);
पूर्ण

/*
 * Send taskstats data in @skb to listeners रेजिस्टरed क्रम @cpu's निकास data
 */
अटल व्योम send_cpu_listeners(काष्ठा sk_buff *skb,
					काष्ठा listener_list *listeners)
अणु
	काष्ठा genlmsghdr *genlhdr = nlmsg_data(nlmsg_hdr(skb));
	काष्ठा listener *s, *पंचांगp;
	काष्ठा sk_buff *skb_next, *skb_cur = skb;
	व्योम *reply = genlmsg_data(genlhdr);
	पूर्णांक rc, delcount = 0;

	genlmsg_end(skb, reply);

	rc = 0;
	करोwn_पढ़ो(&listeners->sem);
	list_क्रम_each_entry(s, &listeners->list, list) अणु
		skb_next = शून्य;
		अगर (!list_is_last(&s->list, &listeners->list)) अणु
			skb_next = skb_clone(skb_cur, GFP_KERNEL);
			अगर (!skb_next)
				अवरोध;
		पूर्ण
		rc = genlmsg_unicast(&init_net, skb_cur, s->pid);
		अगर (rc == -ECONNREFUSED) अणु
			s->valid = 0;
			delcount++;
		पूर्ण
		skb_cur = skb_next;
	पूर्ण
	up_पढ़ो(&listeners->sem);

	अगर (skb_cur)
		nlmsg_मुक्त(skb_cur);

	अगर (!delcount)
		वापस;

	/* Delete invalidated entries */
	करोwn_ग_लिखो(&listeners->sem);
	list_क्रम_each_entry_safe(s, पंचांगp, &listeners->list, list) अणु
		अगर (!s->valid) अणु
			list_del(&s->list);
			kमुक्त(s);
		पूर्ण
	पूर्ण
	up_ग_लिखो(&listeners->sem);
पूर्ण

अटल व्योम fill_stats(काष्ठा user_namespace *user_ns,
		       काष्ठा pid_namespace *pid_ns,
		       काष्ठा task_काष्ठा *tsk, काष्ठा taskstats *stats)
अणु
	स_रखो(stats, 0, माप(*stats));
	/*
	 * Each accounting subप्रणाली adds calls to its functions to
	 * fill in relevant parts of काष्ठा taskstsats as follows
	 *
	 *	per-task-foo(stats, tsk);
	 */

	delayacct_add_tsk(stats, tsk);

	/* fill in basic acct fields */
	stats->version = TASKSTATS_VERSION;
	stats->nvcsw = tsk->nvcsw;
	stats->nivcsw = tsk->nivcsw;
	bacct_add_tsk(user_ns, pid_ns, stats, tsk);

	/* fill in extended acct fields */
	xacct_add_tsk(stats, tsk);
पूर्ण

अटल पूर्णांक fill_stats_क्रम_pid(pid_t pid, काष्ठा taskstats *stats)
अणु
	काष्ठा task_काष्ठा *tsk;

	tsk = find_get_task_by_vpid(pid);
	अगर (!tsk)
		वापस -ESRCH;
	fill_stats(current_user_ns(), task_active_pid_ns(current), tsk, stats);
	put_task_काष्ठा(tsk);
	वापस 0;
पूर्ण

अटल पूर्णांक fill_stats_क्रम_tgid(pid_t tgid, काष्ठा taskstats *stats)
अणु
	काष्ठा task_काष्ठा *tsk, *first;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = -ESRCH;
	u64 delta, uसमय, sसमय;
	u64 start_समय;

	/*
	 * Add additional stats from live tasks except zombie thपढ़ो group
	 * leaders who are alपढ़ोy counted with the dead tasks
	 */
	rcu_पढ़ो_lock();
	first = find_task_by_vpid(tgid);

	अगर (!first || !lock_task_sighand(first, &flags))
		जाओ out;

	अगर (first->संकेत->stats)
		स_नकल(stats, first->संकेत->stats, माप(*stats));
	अन्यथा
		स_रखो(stats, 0, माप(*stats));

	tsk = first;
	start_समय = kसमय_get_ns();
	करो अणु
		अगर (tsk->निकास_state)
			जारी;
		/*
		 * Accounting subप्रणाली can call its functions here to
		 * fill in relevant parts of काष्ठा taskstsats as follows
		 *
		 *	per-task-foo(stats, tsk);
		 */
		delayacct_add_tsk(stats, tsk);

		/* calculate task elapsed समय in nsec */
		delta = start_समय - tsk->start_समय;
		/* Convert to micro seconds */
		करो_भाग(delta, NSEC_PER_USEC);
		stats->ac_eसमय += delta;

		task_cpuसमय(tsk, &uसमय, &sसमय);
		stats->ac_uसमय += भाग_u64(uसमय, NSEC_PER_USEC);
		stats->ac_sसमय += भाग_u64(sसमय, NSEC_PER_USEC);

		stats->nvcsw += tsk->nvcsw;
		stats->nivcsw += tsk->nivcsw;
	पूर्ण जबतक_each_thपढ़ो(first, tsk);

	unlock_task_sighand(first, &flags);
	rc = 0;
out:
	rcu_पढ़ो_unlock();

	stats->version = TASKSTATS_VERSION;
	/*
	 * Accounting subप्रणालीs can also add calls here to modअगरy
	 * fields of taskstats.
	 */
	वापस rc;
पूर्ण

अटल व्योम fill_tgid_निकास(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tsk->sighand->siglock, flags);
	अगर (!tsk->संकेत->stats)
		जाओ ret;

	/*
	 * Each accounting subप्रणाली calls its functions here to
	 * accumalate its per-task stats क्रम tsk, पूर्णांकo the per-tgid काष्ठाure
	 *
	 *	per-task-foo(tsk->संकेत->stats, tsk);
	 */
	delayacct_add_tsk(tsk->संकेत->stats, tsk);
ret:
	spin_unlock_irqrestore(&tsk->sighand->siglock, flags);
	वापस;
पूर्ण

अटल पूर्णांक add_del_listener(pid_t pid, स्थिर काष्ठा cpumask *mask, पूर्णांक isadd)
अणु
	काष्ठा listener_list *listeners;
	काष्ठा listener *s, *पंचांगp, *s2;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक ret = 0;

	अगर (!cpumask_subset(mask, cpu_possible_mask))
		वापस -EINVAL;

	अगर (current_user_ns() != &init_user_ns)
		वापस -EINVAL;

	अगर (task_active_pid_ns(current) != &init_pid_ns)
		वापस -EINVAL;

	अगर (isadd == REGISTER) अणु
		क्रम_each_cpu(cpu, mask) अणु
			s = kदो_स्मृति_node(माप(काष्ठा listener),
					GFP_KERNEL, cpu_to_node(cpu));
			अगर (!s) अणु
				ret = -ENOMEM;
				जाओ cleanup;
			पूर्ण
			s->pid = pid;
			s->valid = 1;

			listeners = &per_cpu(listener_array, cpu);
			करोwn_ग_लिखो(&listeners->sem);
			list_क्रम_each_entry(s2, &listeners->list, list) अणु
				अगर (s2->pid == pid && s2->valid)
					जाओ exists;
			पूर्ण
			list_add(&s->list, &listeners->list);
			s = शून्य;
exists:
			up_ग_लिखो(&listeners->sem);
			kमुक्त(s); /* nop अगर शून्य */
		पूर्ण
		वापस 0;
	पूर्ण

	/* Deरेजिस्टर or cleanup */
cleanup:
	क्रम_each_cpu(cpu, mask) अणु
		listeners = &per_cpu(listener_array, cpu);
		करोwn_ग_लिखो(&listeners->sem);
		list_क्रम_each_entry_safe(s, पंचांगp, &listeners->list, list) अणु
			अगर (s->pid == pid) अणु
				list_del(&s->list);
				kमुक्त(s);
				अवरोध;
			पूर्ण
		पूर्ण
		up_ग_लिखो(&listeners->sem);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक parse(काष्ठा nlattr *na, काष्ठा cpumask *mask)
अणु
	अक्षर *data;
	पूर्णांक len;
	पूर्णांक ret;

	अगर (na == शून्य)
		वापस 1;
	len = nla_len(na);
	अगर (len > TASKSTATS_CPUMASK_MAXLEN)
		वापस -E2BIG;
	अगर (len < 1)
		वापस -EINVAL;
	data = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	nla_strscpy(data, na, len);
	ret = cpulist_parse(data, mask);
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल काष्ठा taskstats *mk_reply(काष्ठा sk_buff *skb, पूर्णांक type, u32 pid)
अणु
	काष्ठा nlattr *na, *ret;
	पूर्णांक aggr;

	aggr = (type == TASKSTATS_TYPE_PID)
			? TASKSTATS_TYPE_AGGR_PID
			: TASKSTATS_TYPE_AGGR_TGID;

	na = nla_nest_start_noflag(skb, aggr);
	अगर (!na)
		जाओ err;

	अगर (nla_put(skb, type, माप(pid), &pid) < 0) अणु
		nla_nest_cancel(skb, na);
		जाओ err;
	पूर्ण
	ret = nla_reserve_64bit(skb, TASKSTATS_TYPE_STATS,
				माप(काष्ठा taskstats), TASKSTATS_TYPE_शून्य);
	अगर (!ret) अणु
		nla_nest_cancel(skb, na);
		जाओ err;
	पूर्ण
	nla_nest_end(skb, na);

	वापस nla_data(ret);
err:
	वापस शून्य;
पूर्ण

अटल पूर्णांक cgroupstats_user_cmd(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	पूर्णांक rc = 0;
	काष्ठा sk_buff *rep_skb;
	काष्ठा cgroupstats *stats;
	काष्ठा nlattr *na;
	माप_प्रकार size;
	u32 fd;
	काष्ठा fd f;

	na = info->attrs[CGROUPSTATS_CMD_ATTR_FD];
	अगर (!na)
		वापस -EINVAL;

	fd = nla_get_u32(info->attrs[CGROUPSTATS_CMD_ATTR_FD]);
	f = fdget(fd);
	अगर (!f.file)
		वापस 0;

	size = nla_total_size(माप(काष्ठा cgroupstats));

	rc = prepare_reply(info, CGROUPSTATS_CMD_NEW, &rep_skb,
				size);
	अगर (rc < 0)
		जाओ err;

	na = nla_reserve(rep_skb, CGROUPSTATS_TYPE_CGROUP_STATS,
				माप(काष्ठा cgroupstats));
	अगर (na == शून्य) अणु
		nlmsg_मुक्त(rep_skb);
		rc = -EMSGSIZE;
		जाओ err;
	पूर्ण

	stats = nla_data(na);
	स_रखो(stats, 0, माप(*stats));

	rc = cgroupstats_build(stats, f.file->f_path.dentry);
	अगर (rc < 0) अणु
		nlmsg_मुक्त(rep_skb);
		जाओ err;
	पूर्ण

	rc = send_reply(rep_skb, info);

err:
	fdput(f);
	वापस rc;
पूर्ण

अटल पूर्णांक cmd_attr_रेजिस्टर_cpumask(काष्ठा genl_info *info)
अणु
	cpumask_var_t mask;
	पूर्णांक rc;

	अगर (!alloc_cpumask_var(&mask, GFP_KERNEL))
		वापस -ENOMEM;
	rc = parse(info->attrs[TASKSTATS_CMD_ATTR_REGISTER_CPUMASK], mask);
	अगर (rc < 0)
		जाओ out;
	rc = add_del_listener(info->snd_portid, mask, REGISTER);
out:
	मुक्त_cpumask_var(mask);
	वापस rc;
पूर्ण

अटल पूर्णांक cmd_attr_deरेजिस्टर_cpumask(काष्ठा genl_info *info)
अणु
	cpumask_var_t mask;
	पूर्णांक rc;

	अगर (!alloc_cpumask_var(&mask, GFP_KERNEL))
		वापस -ENOMEM;
	rc = parse(info->attrs[TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK], mask);
	अगर (rc < 0)
		जाओ out;
	rc = add_del_listener(info->snd_portid, mask, DEREGISTER);
out:
	मुक्त_cpumask_var(mask);
	वापस rc;
पूर्ण

अटल माप_प्रकार taskstats_packet_size(व्योम)
अणु
	माप_प्रकार size;

	size = nla_total_size(माप(u32)) +
		nla_total_size_64bit(माप(काष्ठा taskstats)) +
		nla_total_size(0);

	वापस size;
पूर्ण

अटल पूर्णांक cmd_attr_pid(काष्ठा genl_info *info)
अणु
	काष्ठा taskstats *stats;
	काष्ठा sk_buff *rep_skb;
	माप_प्रकार size;
	u32 pid;
	पूर्णांक rc;

	size = taskstats_packet_size();

	rc = prepare_reply(info, TASKSTATS_CMD_NEW, &rep_skb, size);
	अगर (rc < 0)
		वापस rc;

	rc = -EINVAL;
	pid = nla_get_u32(info->attrs[TASKSTATS_CMD_ATTR_PID]);
	stats = mk_reply(rep_skb, TASKSTATS_TYPE_PID, pid);
	अगर (!stats)
		जाओ err;

	rc = fill_stats_क्रम_pid(pid, stats);
	अगर (rc < 0)
		जाओ err;
	वापस send_reply(rep_skb, info);
err:
	nlmsg_मुक्त(rep_skb);
	वापस rc;
पूर्ण

अटल पूर्णांक cmd_attr_tgid(काष्ठा genl_info *info)
अणु
	काष्ठा taskstats *stats;
	काष्ठा sk_buff *rep_skb;
	माप_प्रकार size;
	u32 tgid;
	पूर्णांक rc;

	size = taskstats_packet_size();

	rc = prepare_reply(info, TASKSTATS_CMD_NEW, &rep_skb, size);
	अगर (rc < 0)
		वापस rc;

	rc = -EINVAL;
	tgid = nla_get_u32(info->attrs[TASKSTATS_CMD_ATTR_TGID]);
	stats = mk_reply(rep_skb, TASKSTATS_TYPE_TGID, tgid);
	अगर (!stats)
		जाओ err;

	rc = fill_stats_क्रम_tgid(tgid, stats);
	अगर (rc < 0)
		जाओ err;
	वापस send_reply(rep_skb, info);
err:
	nlmsg_मुक्त(rep_skb);
	वापस rc;
पूर्ण

अटल पूर्णांक taskstats_user_cmd(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	अगर (info->attrs[TASKSTATS_CMD_ATTR_REGISTER_CPUMASK])
		वापस cmd_attr_रेजिस्टर_cpumask(info);
	अन्यथा अगर (info->attrs[TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK])
		वापस cmd_attr_deरेजिस्टर_cpumask(info);
	अन्यथा अगर (info->attrs[TASKSTATS_CMD_ATTR_PID])
		वापस cmd_attr_pid(info);
	अन्यथा अगर (info->attrs[TASKSTATS_CMD_ATTR_TGID])
		वापस cmd_attr_tgid(info);
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल काष्ठा taskstats *taskstats_tgid_alloc(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा संकेत_काष्ठा *sig = tsk->संकेत;
	काष्ठा taskstats *stats_new, *stats;

	/* Pairs with smp_store_release() below. */
	stats = smp_load_acquire(&sig->stats);
	अगर (stats || thपढ़ो_group_empty(tsk))
		वापस stats;

	/* No problem अगर kmem_cache_zalloc() fails */
	stats_new = kmem_cache_zalloc(taskstats_cache, GFP_KERNEL);

	spin_lock_irq(&tsk->sighand->siglock);
	stats = sig->stats;
	अगर (!stats) अणु
		/*
		 * Pairs with smp_store_release() above and order the
		 * kmem_cache_zalloc().
		 */
		smp_store_release(&sig->stats, stats_new);
		stats = stats_new;
		stats_new = शून्य;
	पूर्ण
	spin_unlock_irq(&tsk->sighand->siglock);

	अगर (stats_new)
		kmem_cache_मुक्त(taskstats_cache, stats_new);

	वापस stats;
पूर्ण

/* Send pid data out on निकास */
व्योम taskstats_निकास(काष्ठा task_काष्ठा *tsk, पूर्णांक group_dead)
अणु
	पूर्णांक rc;
	काष्ठा listener_list *listeners;
	काष्ठा taskstats *stats;
	काष्ठा sk_buff *rep_skb;
	माप_प्रकार size;
	पूर्णांक is_thपढ़ो_group;

	अगर (!family_रेजिस्टरed)
		वापस;

	/*
	 * Size includes space क्रम nested attributes
	 */
	size = taskstats_packet_size();

	is_thपढ़ो_group = !!taskstats_tgid_alloc(tsk);
	अगर (is_thपढ़ो_group) अणु
		/* PID + STATS + TGID + STATS */
		size = 2 * size;
		/* fill the tsk->संकेत->stats काष्ठाure */
		fill_tgid_निकास(tsk);
	पूर्ण

	listeners = raw_cpu_ptr(&listener_array);
	अगर (list_empty(&listeners->list))
		वापस;

	rc = prepare_reply(शून्य, TASKSTATS_CMD_NEW, &rep_skb, size);
	अगर (rc < 0)
		वापस;

	stats = mk_reply(rep_skb, TASKSTATS_TYPE_PID,
			 task_pid_nr_ns(tsk, &init_pid_ns));
	अगर (!stats)
		जाओ err;

	fill_stats(&init_user_ns, &init_pid_ns, tsk, stats);

	/*
	 * Doesn't matter अगर tsk is the leader or the last group member leaving
	 */
	अगर (!is_thपढ़ो_group || !group_dead)
		जाओ send;

	stats = mk_reply(rep_skb, TASKSTATS_TYPE_TGID,
			 task_tgid_nr_ns(tsk, &init_pid_ns));
	अगर (!stats)
		जाओ err;

	स_नकल(stats, tsk->संकेत->stats, माप(*stats));

send:
	send_cpu_listeners(rep_skb, listeners);
	वापस;
err:
	nlmsg_मुक्त(rep_skb);
पूर्ण

अटल स्थिर काष्ठा genl_ops taskstats_ops[] = अणु
	अणु
		.cmd		= TASKSTATS_CMD_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit		= taskstats_user_cmd,
		.policy		= taskstats_cmd_get_policy,
		.maxattr	= ARRAY_SIZE(taskstats_cmd_get_policy) - 1,
		.flags		= GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd		= CGROUPSTATS_CMD_GET,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit		= cgroupstats_user_cmd,
		.policy		= cgroupstats_cmd_get_policy,
		.maxattr	= ARRAY_SIZE(cgroupstats_cmd_get_policy) - 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family family __ro_after_init = अणु
	.name		= TASKSTATS_GENL_NAME,
	.version	= TASKSTATS_GENL_VERSION,
	.module		= THIS_MODULE,
	.ops		= taskstats_ops,
	.n_ops		= ARRAY_SIZE(taskstats_ops),
पूर्ण;

/* Needed early in initialization */
व्योम __init taskstats_init_early(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	taskstats_cache = KMEM_CACHE(taskstats, SLAB_PANIC);
	क्रम_each_possible_cpu(i) अणु
		INIT_LIST_HEAD(&(per_cpu(listener_array, i).list));
		init_rwsem(&(per_cpu(listener_array, i).sem));
	पूर्ण
पूर्ण

अटल पूर्णांक __init taskstats_init(व्योम)
अणु
	पूर्णांक rc;

	rc = genl_रेजिस्टर_family(&family);
	अगर (rc)
		वापस rc;

	family_रेजिस्टरed = 1;
	pr_info("registered taskstats version %d\n", TASKSTATS_GENL_VERSION);
	वापस 0;
पूर्ण

/*
 * late initcall ensures initialization of statistics collection
 * mechanisms precedes initialization of the taskstats पूर्णांकerface
 */
late_initcall(taskstats_init);
