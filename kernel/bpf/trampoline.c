<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2019 Facebook */
#समावेश <linux/hash.h>
#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/rbtree_latch.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/btf.h>
#समावेश <linux/rcupdate_trace.h>
#समावेश <linux/rcupdate_रुको.h>
#समावेश <linux/module.h>

/* dummy _ops. The verअगरier will operate on target program's ops. */
स्थिर काष्ठा bpf_verअगरier_ops bpf_extension_verअगरier_ops = अणु
पूर्ण;
स्थिर काष्ठा bpf_prog_ops bpf_extension_prog_ops = अणु
पूर्ण;

/* btf_vmlinux has ~22k attachable functions. 1k htab is enough. */
#घोषणा TRAMPOLINE_HASH_BITS 10
#घोषणा TRAMPOLINE_TABLE_SIZE (1 << TRAMPOLINE_HASH_BITS)

अटल काष्ठा hlist_head trampoline_table[TRAMPOLINE_TABLE_SIZE];

/* serializes access to trampoline_table */
अटल DEFINE_MUTEX(trampoline_mutex);

व्योम *bpf_jit_alloc_exec_page(व्योम)
अणु
	व्योम *image;

	image = bpf_jit_alloc_exec(PAGE_SIZE);
	अगर (!image)
		वापस शून्य;

	set_vm_flush_reset_perms(image);
	/* Keep image as ग_लिखोable. The alternative is to keep flipping ro/rw
	 * everyसमय new program is attached or detached.
	 */
	set_memory_x((दीर्घ)image, 1);
	वापस image;
पूर्ण

व्योम bpf_image_ksym_add(व्योम *data, काष्ठा bpf_ksym *ksym)
अणु
	ksym->start = (अचिन्हित दीर्घ) data;
	ksym->end = ksym->start + PAGE_SIZE;
	bpf_ksym_add(ksym);
	perf_event_ksymbol(PERF_RECORD_KSYMBOL_TYPE_BPF, ksym->start,
			   PAGE_SIZE, false, ksym->name);
पूर्ण

व्योम bpf_image_ksym_del(काष्ठा bpf_ksym *ksym)
अणु
	bpf_ksym_del(ksym);
	perf_event_ksymbol(PERF_RECORD_KSYMBOL_TYPE_BPF, ksym->start,
			   PAGE_SIZE, true, ksym->name);
पूर्ण

अटल काष्ठा bpf_trampoline *bpf_trampoline_lookup(u64 key)
अणु
	काष्ठा bpf_trampoline *tr;
	काष्ठा hlist_head *head;
	पूर्णांक i;

	mutex_lock(&trampoline_mutex);
	head = &trampoline_table[hash_64(key, TRAMPOLINE_HASH_BITS)];
	hlist_क्रम_each_entry(tr, head, hlist) अणु
		अगर (tr->key == key) अणु
			refcount_inc(&tr->refcnt);
			जाओ out;
		पूर्ण
	पूर्ण
	tr = kzalloc(माप(*tr), GFP_KERNEL);
	अगर (!tr)
		जाओ out;

	tr->key = key;
	INIT_HLIST_NODE(&tr->hlist);
	hlist_add_head(&tr->hlist, head);
	refcount_set(&tr->refcnt, 1);
	mutex_init(&tr->mutex);
	क्रम (i = 0; i < BPF_TRAMP_MAX; i++)
		INIT_HLIST_HEAD(&tr->progs_hlist[i]);
out:
	mutex_unlock(&trampoline_mutex);
	वापस tr;
पूर्ण

अटल पूर्णांक bpf_trampoline_module_get(काष्ठा bpf_trampoline *tr)
अणु
	काष्ठा module *mod;
	पूर्णांक err = 0;

	preempt_disable();
	mod = __module_text_address((अचिन्हित दीर्घ) tr->func.addr);
	अगर (mod && !try_module_get(mod))
		err = -ENOENT;
	preempt_enable();
	tr->mod = mod;
	वापस err;
पूर्ण

अटल व्योम bpf_trampoline_module_put(काष्ठा bpf_trampoline *tr)
अणु
	module_put(tr->mod);
	tr->mod = शून्य;
पूर्ण

अटल पूर्णांक is_ftrace_location(व्योम *ip)
अणु
	दीर्घ addr;

	addr = ftrace_location((दीर्घ)ip);
	अगर (!addr)
		वापस 0;
	अगर (WARN_ON_ONCE(addr != (दीर्घ)ip))
		वापस -EFAULT;
	वापस 1;
पूर्ण

अटल पूर्णांक unरेजिस्टर_fentry(काष्ठा bpf_trampoline *tr, व्योम *old_addr)
अणु
	व्योम *ip = tr->func.addr;
	पूर्णांक ret;

	अगर (tr->func.ftrace_managed)
		ret = unरेजिस्टर_ftrace_direct((दीर्घ)ip, (दीर्घ)old_addr);
	अन्यथा
		ret = bpf_arch_text_poke(ip, BPF_MOD_CALL, old_addr, शून्य);

	अगर (!ret)
		bpf_trampoline_module_put(tr);
	वापस ret;
पूर्ण

अटल पूर्णांक modअगरy_fentry(काष्ठा bpf_trampoline *tr, व्योम *old_addr, व्योम *new_addr)
अणु
	व्योम *ip = tr->func.addr;
	पूर्णांक ret;

	अगर (tr->func.ftrace_managed)
		ret = modअगरy_ftrace_direct((दीर्घ)ip, (दीर्घ)old_addr, (दीर्घ)new_addr);
	अन्यथा
		ret = bpf_arch_text_poke(ip, BPF_MOD_CALL, old_addr, new_addr);
	वापस ret;
पूर्ण

/* first समय रेजिस्टरing */
अटल पूर्णांक रेजिस्टर_fentry(काष्ठा bpf_trampoline *tr, व्योम *new_addr)
अणु
	व्योम *ip = tr->func.addr;
	पूर्णांक ret;

	ret = is_ftrace_location(ip);
	अगर (ret < 0)
		वापस ret;
	tr->func.ftrace_managed = ret;

	अगर (bpf_trampoline_module_get(tr))
		वापस -ENOENT;

	अगर (tr->func.ftrace_managed)
		ret = रेजिस्टर_ftrace_direct((दीर्घ)ip, (दीर्घ)new_addr);
	अन्यथा
		ret = bpf_arch_text_poke(ip, BPF_MOD_CALL, शून्य, new_addr);

	अगर (ret)
		bpf_trampoline_module_put(tr);
	वापस ret;
पूर्ण

अटल काष्ठा bpf_tramp_progs *
bpf_trampoline_get_progs(स्थिर काष्ठा bpf_trampoline *tr, पूर्णांक *total)
अणु
	स्थिर काष्ठा bpf_prog_aux *aux;
	काष्ठा bpf_tramp_progs *tprogs;
	काष्ठा bpf_prog **progs;
	पूर्णांक kind;

	*total = 0;
	tprogs = kसुस्मृति(BPF_TRAMP_MAX, माप(*tprogs), GFP_KERNEL);
	अगर (!tprogs)
		वापस ERR_PTR(-ENOMEM);

	क्रम (kind = 0; kind < BPF_TRAMP_MAX; kind++) अणु
		tprogs[kind].nr_progs = tr->progs_cnt[kind];
		*total += tr->progs_cnt[kind];
		progs = tprogs[kind].progs;

		hlist_क्रम_each_entry(aux, &tr->progs_hlist[kind], tramp_hlist)
			*progs++ = aux->prog;
	पूर्ण
	वापस tprogs;
पूर्ण

अटल व्योम __bpf_tramp_image_put_deferred(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bpf_tramp_image *im;

	im = container_of(work, काष्ठा bpf_tramp_image, work);
	bpf_image_ksym_del(&im->ksym);
	bpf_jit_मुक्त_exec(im->image);
	bpf_jit_unअक्षरge_modmem(1);
	percpu_ref_निकास(&im->pcref);
	kमुक्त_rcu(im, rcu);
पूर्ण

/* callback, fनिकास step 3 or fentry step 2 */
अटल व्योम __bpf_tramp_image_put_rcu(काष्ठा rcu_head *rcu)
अणु
	काष्ठा bpf_tramp_image *im;

	im = container_of(rcu, काष्ठा bpf_tramp_image, rcu);
	INIT_WORK(&im->work, __bpf_tramp_image_put_deferred);
	schedule_work(&im->work);
पूर्ण

/* callback, fनिकास step 2. Called after percpu_ref_समाप्त confirms. */
अटल व्योम __bpf_tramp_image_release(काष्ठा percpu_ref *pcref)
अणु
	काष्ठा bpf_tramp_image *im;

	im = container_of(pcref, काष्ठा bpf_tramp_image, pcref);
	call_rcu_tasks(&im->rcu, __bpf_tramp_image_put_rcu);
पूर्ण

/* callback, fनिकास or fentry step 1 */
अटल व्योम __bpf_tramp_image_put_rcu_tasks(काष्ठा rcu_head *rcu)
अणु
	काष्ठा bpf_tramp_image *im;

	im = container_of(rcu, काष्ठा bpf_tramp_image, rcu);
	अगर (im->ip_after_call)
		/* the हाल of भ_शेष_ret/fनिकास trampoline and CONFIG_PREEMPTION=y */
		percpu_ref_समाप्त(&im->pcref);
	अन्यथा
		/* the हाल of fentry trampoline */
		call_rcu_tasks(&im->rcu, __bpf_tramp_image_put_rcu);
पूर्ण

अटल व्योम bpf_tramp_image_put(काष्ठा bpf_tramp_image *im)
अणु
	/* The trampoline image that calls original function is using:
	 * rcu_पढ़ो_lock_trace to protect sleepable bpf progs
	 * rcu_पढ़ो_lock to protect normal bpf progs
	 * percpu_ref to protect trampoline itself
	 * rcu tasks to protect trampoline यंत्र not covered by percpu_ref
	 * (which are few यंत्र insns beक्रमe __bpf_tramp_enter and
	 *  after __bpf_tramp_निकास)
	 *
	 * The trampoline is unreachable beक्रमe bpf_tramp_image_put().
	 *
	 * First, patch the trampoline to aव्योम calling पूर्णांकo fनिकास progs.
	 * The progs will be मुक्तd even अगर the original function is still
	 * executing or sleeping.
	 * In हाल of CONFIG_PREEMPT=y use call_rcu_tasks() to रुको on
	 * first few यंत्र inकाष्ठाions to execute and call पूर्णांकo
	 * __bpf_tramp_enter->percpu_ref_get.
	 * Then use percpu_ref_समाप्त to रुको क्रम the trampoline and the original
	 * function to finish.
	 * Then use call_rcu_tasks() to make sure few यंत्र insns in
	 * the trampoline epilogue are करोne as well.
	 *
	 * In !PREEMPT हाल the task that got पूर्णांकerrupted in the first यंत्र
	 * insns won't go through an RCU quiescent state which the
	 * percpu_ref_समाप्त will be रुकोing क्रम. Hence the first
	 * call_rcu_tasks() is not necessary.
	 */
	अगर (im->ip_after_call) अणु
		पूर्णांक err = bpf_arch_text_poke(im->ip_after_call, BPF_MOD_JUMP,
					     शून्य, im->ip_epilogue);
		WARN_ON(err);
		अगर (IS_ENABLED(CONFIG_PREEMPTION))
			call_rcu_tasks(&im->rcu, __bpf_tramp_image_put_rcu_tasks);
		अन्यथा
			percpu_ref_समाप्त(&im->pcref);
		वापस;
	पूर्ण

	/* The trampoline without fनिकास and भ_शेष_ret progs करोesn't call original
	 * function and करोesn't use percpu_ref.
	 * Use call_rcu_tasks_trace() to रुको क्रम sleepable progs to finish.
	 * Then use call_rcu_tasks() to रुको क्रम the rest of trampoline यंत्र
	 * and normal progs.
	 */
	call_rcu_tasks_trace(&im->rcu, __bpf_tramp_image_put_rcu_tasks);
पूर्ण

अटल काष्ठा bpf_tramp_image *bpf_tramp_image_alloc(u64 key, u32 idx)
अणु
	काष्ठा bpf_tramp_image *im;
	काष्ठा bpf_ksym *ksym;
	व्योम *image;
	पूर्णांक err = -ENOMEM;

	im = kzalloc(माप(*im), GFP_KERNEL);
	अगर (!im)
		जाओ out;

	err = bpf_jit_अक्षरge_modmem(1);
	अगर (err)
		जाओ out_मुक्त_im;

	err = -ENOMEM;
	im->image = image = bpf_jit_alloc_exec_page();
	अगर (!image)
		जाओ out_unअक्षरge;

	err = percpu_ref_init(&im->pcref, __bpf_tramp_image_release, 0, GFP_KERNEL);
	अगर (err)
		जाओ out_मुक्त_image;

	ksym = &im->ksym;
	INIT_LIST_HEAD_RCU(&ksym->lnode);
	snम_लिखो(ksym->name, KSYM_NAME_LEN, "bpf_trampoline_%llu_%u", key, idx);
	bpf_image_ksym_add(image, ksym);
	वापस im;

out_मुक्त_image:
	bpf_jit_मुक्त_exec(im->image);
out_unअक्षरge:
	bpf_jit_unअक्षरge_modmem(1);
out_मुक्त_im:
	kमुक्त(im);
out:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक bpf_trampoline_update(काष्ठा bpf_trampoline *tr)
अणु
	काष्ठा bpf_tramp_image *im;
	काष्ठा bpf_tramp_progs *tprogs;
	u32 flags = BPF_TRAMP_F_RESTORE_REGS;
	पूर्णांक err, total;

	tprogs = bpf_trampoline_get_progs(tr, &total);
	अगर (IS_ERR(tprogs))
		वापस PTR_ERR(tprogs);

	अगर (total == 0) अणु
		err = unरेजिस्टर_fentry(tr, tr->cur_image->image);
		bpf_tramp_image_put(tr->cur_image);
		tr->cur_image = शून्य;
		tr->selector = 0;
		जाओ out;
	पूर्ण

	im = bpf_tramp_image_alloc(tr->key, tr->selector);
	अगर (IS_ERR(im)) अणु
		err = PTR_ERR(im);
		जाओ out;
	पूर्ण

	अगर (tprogs[BPF_TRAMP_FEXIT].nr_progs ||
	    tprogs[BPF_TRAMP_MODIFY_RETURN].nr_progs)
		flags = BPF_TRAMP_F_CALL_ORIG | BPF_TRAMP_F_SKIP_FRAME;

	err = arch_prepare_bpf_trampoline(im, im->image, im->image + PAGE_SIZE,
					  &tr->func.model, flags, tprogs,
					  tr->func.addr);
	अगर (err < 0)
		जाओ out;

	WARN_ON(tr->cur_image && tr->selector == 0);
	WARN_ON(!tr->cur_image && tr->selector);
	अगर (tr->cur_image)
		/* progs alपढ़ोy running at this address */
		err = modअगरy_fentry(tr, tr->cur_image->image, im->image);
	अन्यथा
		/* first समय रेजिस्टरing */
		err = रेजिस्टर_fentry(tr, im->image);
	अगर (err)
		जाओ out;
	अगर (tr->cur_image)
		bpf_tramp_image_put(tr->cur_image);
	tr->cur_image = im;
	tr->selector++;
out:
	kमुक्त(tprogs);
	वापस err;
पूर्ण

अटल क्रमागत bpf_tramp_prog_type bpf_attach_type_to_tramp(काष्ठा bpf_prog *prog)
अणु
	चयन (prog->expected_attach_type) अणु
	हाल BPF_TRACE_FENTRY:
		वापस BPF_TRAMP_FENTRY;
	हाल BPF_MODIFY_RETURN:
		वापस BPF_TRAMP_MODIFY_RETURN;
	हाल BPF_TRACE_FEXIT:
		वापस BPF_TRAMP_FEXIT;
	हाल BPF_LSM_MAC:
		अगर (!prog->aux->attach_func_proto->type)
			/* The function वापसs व्योम, we cannot modअगरy its
			 * वापस value.
			 */
			वापस BPF_TRAMP_FEXIT;
		अन्यथा
			वापस BPF_TRAMP_MODIFY_RETURN;
	शेष:
		वापस BPF_TRAMP_REPLACE;
	पूर्ण
पूर्ण

पूर्णांक bpf_trampoline_link_prog(काष्ठा bpf_prog *prog, काष्ठा bpf_trampoline *tr)
अणु
	क्रमागत bpf_tramp_prog_type kind;
	पूर्णांक err = 0;
	पूर्णांक cnt;

	kind = bpf_attach_type_to_tramp(prog);
	mutex_lock(&tr->mutex);
	अगर (tr->extension_prog) अणु
		/* cannot attach fentry/fनिकास अगर extension prog is attached.
		 * cannot overग_लिखो extension prog either.
		 */
		err = -EBUSY;
		जाओ out;
	पूर्ण
	cnt = tr->progs_cnt[BPF_TRAMP_FENTRY] + tr->progs_cnt[BPF_TRAMP_FEXIT];
	अगर (kind == BPF_TRAMP_REPLACE) अणु
		/* Cannot attach extension अगर fentry/fनिकास are in use. */
		अगर (cnt) अणु
			err = -EBUSY;
			जाओ out;
		पूर्ण
		tr->extension_prog = prog;
		err = bpf_arch_text_poke(tr->func.addr, BPF_MOD_JUMP, शून्य,
					 prog->bpf_func);
		जाओ out;
	पूर्ण
	अगर (cnt >= BPF_MAX_TRAMP_PROGS) अणु
		err = -E2BIG;
		जाओ out;
	पूर्ण
	अगर (!hlist_unhashed(&prog->aux->tramp_hlist)) अणु
		/* prog alपढ़ोy linked */
		err = -EBUSY;
		जाओ out;
	पूर्ण
	hlist_add_head(&prog->aux->tramp_hlist, &tr->progs_hlist[kind]);
	tr->progs_cnt[kind]++;
	err = bpf_trampoline_update(tr);
	अगर (err) अणु
		hlist_del_init(&prog->aux->tramp_hlist);
		tr->progs_cnt[kind]--;
	पूर्ण
out:
	mutex_unlock(&tr->mutex);
	वापस err;
पूर्ण

/* bpf_trampoline_unlink_prog() should never fail. */
पूर्णांक bpf_trampoline_unlink_prog(काष्ठा bpf_prog *prog, काष्ठा bpf_trampoline *tr)
अणु
	क्रमागत bpf_tramp_prog_type kind;
	पूर्णांक err;

	kind = bpf_attach_type_to_tramp(prog);
	mutex_lock(&tr->mutex);
	अगर (kind == BPF_TRAMP_REPLACE) अणु
		WARN_ON_ONCE(!tr->extension_prog);
		err = bpf_arch_text_poke(tr->func.addr, BPF_MOD_JUMP,
					 tr->extension_prog->bpf_func, शून्य);
		tr->extension_prog = शून्य;
		जाओ out;
	पूर्ण
	hlist_del_init(&prog->aux->tramp_hlist);
	tr->progs_cnt[kind]--;
	err = bpf_trampoline_update(tr);
out:
	mutex_unlock(&tr->mutex);
	वापस err;
पूर्ण

काष्ठा bpf_trampoline *bpf_trampoline_get(u64 key,
					  काष्ठा bpf_attach_target_info *tgt_info)
अणु
	काष्ठा bpf_trampoline *tr;

	tr = bpf_trampoline_lookup(key);
	अगर (!tr)
		वापस शून्य;

	mutex_lock(&tr->mutex);
	अगर (tr->func.addr)
		जाओ out;

	स_नकल(&tr->func.model, &tgt_info->भ_शेषel, माप(tgt_info->भ_शेषel));
	tr->func.addr = (व्योम *)tgt_info->tgt_addr;
out:
	mutex_unlock(&tr->mutex);
	वापस tr;
पूर्ण

व्योम bpf_trampoline_put(काष्ठा bpf_trampoline *tr)
अणु
	अगर (!tr)
		वापस;
	mutex_lock(&trampoline_mutex);
	अगर (!refcount_dec_and_test(&tr->refcnt))
		जाओ out;
	WARN_ON_ONCE(mutex_is_locked(&tr->mutex));
	अगर (WARN_ON_ONCE(!hlist_empty(&tr->progs_hlist[BPF_TRAMP_FENTRY])))
		जाओ out;
	अगर (WARN_ON_ONCE(!hlist_empty(&tr->progs_hlist[BPF_TRAMP_FEXIT])))
		जाओ out;
	/* This code will be executed even when the last bpf_tramp_image
	 * is alive. All progs are detached from the trampoline and the
	 * trampoline image is patched with jmp पूर्णांकo epilogue to skip
	 * fनिकास progs. The fentry-only trampoline will be मुक्तd via
	 * multiple rcu callbacks.
	 */
	hlist_del(&tr->hlist);
	kमुक्त(tr);
out:
	mutex_unlock(&trampoline_mutex);
पूर्ण

#घोषणा NO_START_TIME 1
अटल u64 notrace bpf_prog_start_समय(व्योम)
अणु
	u64 start = NO_START_TIME;

	अगर (अटल_branch_unlikely(&bpf_stats_enabled_key)) अणु
		start = sched_घड़ी();
		अगर (unlikely(!start))
			start = NO_START_TIME;
	पूर्ण
	वापस start;
पूर्ण

अटल व्योम notrace inc_misses_counter(काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog_stats *stats;

	stats = this_cpu_ptr(prog->stats);
	u64_stats_update_begin(&stats->syncp);
	stats->misses++;
	u64_stats_update_end(&stats->syncp);
पूर्ण

/* The logic is similar to BPF_PROG_RUN, but with an explicit
 * rcu_पढ़ो_lock() and migrate_disable() which are required
 * क्रम the trampoline. The macro is split पूर्णांकo
 * call __bpf_prog_enter
 * call prog->bpf_func
 * call __bpf_prog_निकास
 *
 * __bpf_prog_enter वापसs:
 * 0 - skip execution of the bpf prog
 * 1 - execute bpf prog
 * [2..MAX_U64] - excute bpf prog and record execution समय.
 *     This is start समय.
 */
u64 notrace __bpf_prog_enter(काष्ठा bpf_prog *prog)
	__acquires(RCU)
अणु
	rcu_पढ़ो_lock();
	migrate_disable();
	अगर (unlikely(__this_cpu_inc_वापस(*(prog->active)) != 1)) अणु
		inc_misses_counter(prog);
		वापस 0;
	पूर्ण
	वापस bpf_prog_start_समय();
पूर्ण

अटल व्योम notrace update_prog_stats(काष्ठा bpf_prog *prog,
				      u64 start)
अणु
	काष्ठा bpf_prog_stats *stats;

	अगर (अटल_branch_unlikely(&bpf_stats_enabled_key) &&
	    /* अटल_key could be enabled in __bpf_prog_enter*
	     * and disabled in __bpf_prog_निकास*.
	     * And vice versa.
	     * Hence check that 'start' is valid.
	     */
	    start > NO_START_TIME) अणु
		stats = this_cpu_ptr(prog->stats);
		u64_stats_update_begin(&stats->syncp);
		stats->cnt++;
		stats->nsecs += sched_घड़ी() - start;
		u64_stats_update_end(&stats->syncp);
	पूर्ण
पूर्ण

व्योम notrace __bpf_prog_निकास(काष्ठा bpf_prog *prog, u64 start)
	__releases(RCU)
अणु
	update_prog_stats(prog, start);
	__this_cpu_dec(*(prog->active));
	migrate_enable();
	rcu_पढ़ो_unlock();
पूर्ण

u64 notrace __bpf_prog_enter_sleepable(काष्ठा bpf_prog *prog)
अणु
	rcu_पढ़ो_lock_trace();
	migrate_disable();
	might_fault();
	अगर (unlikely(__this_cpu_inc_वापस(*(prog->active)) != 1)) अणु
		inc_misses_counter(prog);
		वापस 0;
	पूर्ण
	वापस bpf_prog_start_समय();
पूर्ण

व्योम notrace __bpf_prog_निकास_sleepable(काष्ठा bpf_prog *prog, u64 start)
अणु
	update_prog_stats(prog, start);
	__this_cpu_dec(*(prog->active));
	migrate_enable();
	rcu_पढ़ो_unlock_trace();
पूर्ण

व्योम notrace __bpf_tramp_enter(काष्ठा bpf_tramp_image *tr)
अणु
	percpu_ref_get(&tr->pcref);
पूर्ण

व्योम notrace __bpf_tramp_निकास(काष्ठा bpf_tramp_image *tr)
अणु
	percpu_ref_put(&tr->pcref);
पूर्ण

पूर्णांक __weak
arch_prepare_bpf_trampoline(काष्ठा bpf_tramp_image *tr, व्योम *image, व्योम *image_end,
			    स्थिर काष्ठा btf_func_model *m, u32 flags,
			    काष्ठा bpf_tramp_progs *tprogs,
			    व्योम *orig_call)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक __init init_trampolines(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TRAMPOLINE_TABLE_SIZE; i++)
		INIT_HLIST_HEAD(&trampoline_table[i]);
	वापस 0;
पूर्ण
late_initcall(init_trampolines);
