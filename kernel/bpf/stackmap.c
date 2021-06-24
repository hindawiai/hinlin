<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2016 Facebook
 */
#समावेश <linux/bpf.h>
#समावेश <linux/jhash.h>
#समावेश <linux/filter.h>
#समावेश <linux/kernel.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/btf_ids.h>
#समावेश <linux/buildid.h>
#समावेश "percpu_freelist.h"

#घोषणा STACK_CREATE_FLAG_MASK					\
	(BPF_F_NUMA_NODE | BPF_F_RDONLY | BPF_F_WRONLY |	\
	 BPF_F_STACK_BUILD_ID)

काष्ठा stack_map_bucket अणु
	काष्ठा pcpu_मुक्तlist_node fnode;
	u32 hash;
	u32 nr;
	u64 data[];
पूर्ण;

काष्ठा bpf_stack_map अणु
	काष्ठा bpf_map map;
	व्योम *elems;
	काष्ठा pcpu_मुक्तlist मुक्तlist;
	u32 n_buckets;
	काष्ठा stack_map_bucket *buckets[];
पूर्ण;

/* irq_work to run up_पढ़ो() क्रम build_id lookup in nmi context */
काष्ठा stack_map_irq_work अणु
	काष्ठा irq_work irq_work;
	काष्ठा mm_काष्ठा *mm;
पूर्ण;

अटल व्योम करो_up_पढ़ो(काष्ठा irq_work *entry)
अणु
	काष्ठा stack_map_irq_work *work;

	अगर (WARN_ON_ONCE(IS_ENABLED(CONFIG_PREEMPT_RT)))
		वापस;

	work = container_of(entry, काष्ठा stack_map_irq_work, irq_work);
	mmap_पढ़ो_unlock_non_owner(work->mm);
पूर्ण

अटल DEFINE_PER_CPU(काष्ठा stack_map_irq_work, up_पढ़ो_work);

अटल अंतरभूत bool stack_map_use_build_id(काष्ठा bpf_map *map)
अणु
	वापस (map->map_flags & BPF_F_STACK_BUILD_ID);
पूर्ण

अटल अंतरभूत पूर्णांक stack_map_data_size(काष्ठा bpf_map *map)
अणु
	वापस stack_map_use_build_id(map) ?
		माप(काष्ठा bpf_stack_build_id) : माप(u64);
पूर्ण

अटल पूर्णांक pपुनः_स्मृति_elems_and_मुक्तlist(काष्ठा bpf_stack_map *smap)
अणु
	u32 elem_size = माप(काष्ठा stack_map_bucket) + smap->map.value_size;
	पूर्णांक err;

	smap->elems = bpf_map_area_alloc(elem_size * smap->map.max_entries,
					 smap->map.numa_node);
	अगर (!smap->elems)
		वापस -ENOMEM;

	err = pcpu_मुक्तlist_init(&smap->मुक्तlist);
	अगर (err)
		जाओ मुक्त_elems;

	pcpu_मुक्तlist_populate(&smap->मुक्तlist, smap->elems, elem_size,
			       smap->map.max_entries);
	वापस 0;

मुक्त_elems:
	bpf_map_area_मुक्त(smap->elems);
	वापस err;
पूर्ण

/* Called from syscall */
अटल काष्ठा bpf_map *stack_map_alloc(जोड़ bpf_attr *attr)
अणु
	u32 value_size = attr->value_size;
	काष्ठा bpf_stack_map *smap;
	u64 cost, n_buckets;
	पूर्णांक err;

	अगर (!bpf_capable())
		वापस ERR_PTR(-EPERM);

	अगर (attr->map_flags & ~STACK_CREATE_FLAG_MASK)
		वापस ERR_PTR(-EINVAL);

	/* check sanity of attributes */
	अगर (attr->max_entries == 0 || attr->key_size != 4 ||
	    value_size < 8 || value_size % 8)
		वापस ERR_PTR(-EINVAL);

	BUILD_BUG_ON(माप(काष्ठा bpf_stack_build_id) % माप(u64));
	अगर (attr->map_flags & BPF_F_STACK_BUILD_ID) अणु
		अगर (value_size % माप(काष्ठा bpf_stack_build_id) ||
		    value_size / माप(काष्ठा bpf_stack_build_id)
		    > sysctl_perf_event_max_stack)
			वापस ERR_PTR(-EINVAL);
	पूर्ण अन्यथा अगर (value_size / 8 > sysctl_perf_event_max_stack)
		वापस ERR_PTR(-EINVAL);

	/* hash table size must be घातer of 2 */
	n_buckets = roundup_घात_of_two(attr->max_entries);
	अगर (!n_buckets)
		वापस ERR_PTR(-E2BIG);

	cost = n_buckets * माप(काष्ठा stack_map_bucket *) + माप(*smap);
	cost += n_buckets * (value_size + माप(काष्ठा stack_map_bucket));
	smap = bpf_map_area_alloc(cost, bpf_map_attr_numa_node(attr));
	अगर (!smap)
		वापस ERR_PTR(-ENOMEM);

	bpf_map_init_from_attr(&smap->map, attr);
	smap->map.value_size = value_size;
	smap->n_buckets = n_buckets;

	err = get_callchain_buffers(sysctl_perf_event_max_stack);
	अगर (err)
		जाओ मुक्त_smap;

	err = pपुनः_स्मृति_elems_and_मुक्तlist(smap);
	अगर (err)
		जाओ put_buffers;

	वापस &smap->map;

put_buffers:
	put_callchain_buffers();
मुक्त_smap:
	bpf_map_area_मुक्त(smap);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम stack_map_get_build_id_offset(काष्ठा bpf_stack_build_id *id_offs,
					  u64 *ips, u32 trace_nr, bool user)
अणु
	पूर्णांक i;
	काष्ठा vm_area_काष्ठा *vma;
	bool irq_work_busy = false;
	काष्ठा stack_map_irq_work *work = शून्य;

	अगर (irqs_disabled()) अणु
		अगर (!IS_ENABLED(CONFIG_PREEMPT_RT)) अणु
			work = this_cpu_ptr(&up_पढ़ो_work);
			अगर (irq_work_is_busy(&work->irq_work)) अणु
				/* cannot queue more up_पढ़ो, fallback */
				irq_work_busy = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * PREEMPT_RT करोes not allow to trylock mmap sem in
			 * पूर्णांकerrupt disabled context. Force the fallback code.
			 */
			irq_work_busy = true;
		पूर्ण
	पूर्ण

	/*
	 * We cannot करो up_पढ़ो() when the irq is disabled, because of
	 * risk to deadlock with rq_lock. To करो build_id lookup when the
	 * irqs are disabled, we need to run up_पढ़ो() in irq_work. We use
	 * a percpu variable to करो the irq_work. If the irq_work is
	 * alपढ़ोy used by another lookup, we fall back to report ips.
	 *
	 * Same fallback is used क्रम kernel stack (!user) on a stackmap
	 * with build_id.
	 */
	अगर (!user || !current || !current->mm || irq_work_busy ||
	    !mmap_पढ़ो_trylock_non_owner(current->mm)) अणु
		/* cannot access current->mm, fall back to ips */
		क्रम (i = 0; i < trace_nr; i++) अणु
			id_offs[i].status = BPF_STACK_BUILD_ID_IP;
			id_offs[i].ip = ips[i];
			स_रखो(id_offs[i].build_id, 0, BUILD_ID_SIZE_MAX);
		पूर्ण
		वापस;
	पूर्ण

	क्रम (i = 0; i < trace_nr; i++) अणु
		vma = find_vma(current->mm, ips[i]);
		अगर (!vma || build_id_parse(vma, id_offs[i].build_id, शून्य)) अणु
			/* per entry fall back to ips */
			id_offs[i].status = BPF_STACK_BUILD_ID_IP;
			id_offs[i].ip = ips[i];
			स_रखो(id_offs[i].build_id, 0, BUILD_ID_SIZE_MAX);
			जारी;
		पूर्ण
		id_offs[i].offset = (vma->vm_pgoff << PAGE_SHIFT) + ips[i]
			- vma->vm_start;
		id_offs[i].status = BPF_STACK_BUILD_ID_VALID;
	पूर्ण

	अगर (!work) अणु
		mmap_पढ़ो_unlock_non_owner(current->mm);
	पूर्ण अन्यथा अणु
		work->mm = current->mm;
		irq_work_queue(&work->irq_work);
	पूर्ण
पूर्ण

अटल काष्ठा perf_callchain_entry *
get_callchain_entry_क्रम_task(काष्ठा task_काष्ठा *task, u32 init_nr)
अणु
#अगर_घोषित CONFIG_STACKTRACE
	काष्ठा perf_callchain_entry *entry;
	पूर्णांक rctx;

	entry = get_callchain_entry(&rctx);

	अगर (!entry)
		वापस शून्य;

	entry->nr = init_nr +
		stack_trace_save_tsk(task, (अचिन्हित दीर्घ *)(entry->ip + init_nr),
				     sysctl_perf_event_max_stack - init_nr, 0);

	/* stack_trace_save_tsk() works on अचिन्हित दीर्घ array, जबतक
	 * perf_callchain_entry uses u64 array. For 32-bit प्रणालीs, it is
	 * necessary to fix this mismatch.
	 */
	अगर (__BITS_PER_LONG != 64) अणु
		अचिन्हित दीर्घ *from = (अचिन्हित दीर्घ *) entry->ip;
		u64 *to = entry->ip;
		पूर्णांक i;

		/* copy data from the end to aव्योम using extra buffer */
		क्रम (i = entry->nr - 1; i >= (पूर्णांक)init_nr; i--)
			to[i] = (u64)(from[i]);
	पूर्ण

	put_callchain_entry(rctx);

	वापस entry;
#अन्यथा /* CONFIG_STACKTRACE */
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

अटल दीर्घ __bpf_get_stackid(काष्ठा bpf_map *map,
			      काष्ठा perf_callchain_entry *trace, u64 flags)
अणु
	काष्ठा bpf_stack_map *smap = container_of(map, काष्ठा bpf_stack_map, map);
	काष्ठा stack_map_bucket *bucket, *new_bucket, *old_bucket;
	u32 max_depth = map->value_size / stack_map_data_size(map);
	/* stack_map_alloc() checks that max_depth <= sysctl_perf_event_max_stack */
	u32 init_nr = sysctl_perf_event_max_stack - max_depth;
	u32 skip = flags & BPF_F_SKIP_FIELD_MASK;
	u32 hash, id, trace_nr, trace_len;
	bool user = flags & BPF_F_USER_STACK;
	u64 *ips;
	bool hash_matches;

	/* get_perf_callchain() guarantees that trace->nr >= init_nr
	 * and trace-nr <= sysctl_perf_event_max_stack, so trace_nr <= max_depth
	 */
	trace_nr = trace->nr - init_nr;

	अगर (trace_nr <= skip)
		/* skipping more than usable stack trace */
		वापस -EFAULT;

	trace_nr -= skip;
	trace_len = trace_nr * माप(u64);
	ips = trace->ip + skip + init_nr;
	hash = jhash2((u32 *)ips, trace_len / माप(u32), 0);
	id = hash & (smap->n_buckets - 1);
	bucket = READ_ONCE(smap->buckets[id]);

	hash_matches = bucket && bucket->hash == hash;
	/* fast cmp */
	अगर (hash_matches && flags & BPF_F_FAST_STACK_CMP)
		वापस id;

	अगर (stack_map_use_build_id(map)) अणु
		/* क्रम build_id+offset, pop a bucket beक्रमe slow cmp */
		new_bucket = (काष्ठा stack_map_bucket *)
			pcpu_मुक्तlist_pop(&smap->मुक्तlist);
		अगर (unlikely(!new_bucket))
			वापस -ENOMEM;
		new_bucket->nr = trace_nr;
		stack_map_get_build_id_offset(
			(काष्ठा bpf_stack_build_id *)new_bucket->data,
			ips, trace_nr, user);
		trace_len = trace_nr * माप(काष्ठा bpf_stack_build_id);
		अगर (hash_matches && bucket->nr == trace_nr &&
		    स_भेद(bucket->data, new_bucket->data, trace_len) == 0) अणु
			pcpu_मुक्तlist_push(&smap->मुक्तlist, &new_bucket->fnode);
			वापस id;
		पूर्ण
		अगर (bucket && !(flags & BPF_F_REUSE_STACKID)) अणु
			pcpu_मुक्तlist_push(&smap->मुक्तlist, &new_bucket->fnode);
			वापस -EEXIST;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (hash_matches && bucket->nr == trace_nr &&
		    स_भेद(bucket->data, ips, trace_len) == 0)
			वापस id;
		अगर (bucket && !(flags & BPF_F_REUSE_STACKID))
			वापस -EEXIST;

		new_bucket = (काष्ठा stack_map_bucket *)
			pcpu_मुक्तlist_pop(&smap->मुक्तlist);
		अगर (unlikely(!new_bucket))
			वापस -ENOMEM;
		स_नकल(new_bucket->data, ips, trace_len);
	पूर्ण

	new_bucket->hash = hash;
	new_bucket->nr = trace_nr;

	old_bucket = xchg(&smap->buckets[id], new_bucket);
	अगर (old_bucket)
		pcpu_मुक्तlist_push(&smap->मुक्तlist, &old_bucket->fnode);
	वापस id;
पूर्ण

BPF_CALL_3(bpf_get_stackid, काष्ठा pt_regs *, regs, काष्ठा bpf_map *, map,
	   u64, flags)
अणु
	u32 max_depth = map->value_size / stack_map_data_size(map);
	/* stack_map_alloc() checks that max_depth <= sysctl_perf_event_max_stack */
	u32 init_nr = sysctl_perf_event_max_stack - max_depth;
	bool user = flags & BPF_F_USER_STACK;
	काष्ठा perf_callchain_entry *trace;
	bool kernel = !user;

	अगर (unlikely(flags & ~(BPF_F_SKIP_FIELD_MASK | BPF_F_USER_STACK |
			       BPF_F_FAST_STACK_CMP | BPF_F_REUSE_STACKID)))
		वापस -EINVAL;

	trace = get_perf_callchain(regs, init_nr, kernel, user,
				   sysctl_perf_event_max_stack, false, false);

	अगर (unlikely(!trace))
		/* couldn't fetch the stack trace */
		वापस -EFAULT;

	वापस __bpf_get_stackid(map, trace, flags);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_stackid_proto = अणु
	.func		= bpf_get_stackid,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

अटल __u64 count_kernel_ip(काष्ठा perf_callchain_entry *trace)
अणु
	__u64 nr_kernel = 0;

	जबतक (nr_kernel < trace->nr) अणु
		अगर (trace->ip[nr_kernel] == PERF_CONTEXT_USER)
			अवरोध;
		nr_kernel++;
	पूर्ण
	वापस nr_kernel;
पूर्ण

BPF_CALL_3(bpf_get_stackid_pe, काष्ठा bpf_perf_event_data_kern *, ctx,
	   काष्ठा bpf_map *, map, u64, flags)
अणु
	काष्ठा perf_event *event = ctx->event;
	काष्ठा perf_callchain_entry *trace;
	bool kernel, user;
	__u64 nr_kernel;
	पूर्णांक ret;

	/* perf_sample_data करोesn't have callchain, use bpf_get_stackid */
	अगर (!(event->attr.sample_type & __PERF_SAMPLE_CALLCHAIN_EARLY))
		वापस bpf_get_stackid((अचिन्हित दीर्घ)(ctx->regs),
				       (अचिन्हित दीर्घ) map, flags, 0, 0);

	अगर (unlikely(flags & ~(BPF_F_SKIP_FIELD_MASK | BPF_F_USER_STACK |
			       BPF_F_FAST_STACK_CMP | BPF_F_REUSE_STACKID)))
		वापस -EINVAL;

	user = flags & BPF_F_USER_STACK;
	kernel = !user;

	trace = ctx->data->callchain;
	अगर (unlikely(!trace))
		वापस -EFAULT;

	nr_kernel = count_kernel_ip(trace);

	अगर (kernel) अणु
		__u64 nr = trace->nr;

		trace->nr = nr_kernel;
		ret = __bpf_get_stackid(map, trace, flags);

		/* restore nr */
		trace->nr = nr;
	पूर्ण अन्यथा अणु /* user */
		u64 skip = flags & BPF_F_SKIP_FIELD_MASK;

		skip += nr_kernel;
		अगर (skip > BPF_F_SKIP_FIELD_MASK)
			वापस -EFAULT;

		flags = (flags & ~BPF_F_SKIP_FIELD_MASK) | skip;
		ret = __bpf_get_stackid(map, trace, flags);
	पूर्ण
	वापस ret;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_stackid_proto_pe = अणु
	.func		= bpf_get_stackid_pe,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

अटल दीर्घ __bpf_get_stack(काष्ठा pt_regs *regs, काष्ठा task_काष्ठा *task,
			    काष्ठा perf_callchain_entry *trace_in,
			    व्योम *buf, u32 size, u64 flags)
अणु
	u32 init_nr, trace_nr, copy_len, elem_size, num_elem;
	bool user_build_id = flags & BPF_F_USER_BUILD_ID;
	u32 skip = flags & BPF_F_SKIP_FIELD_MASK;
	bool user = flags & BPF_F_USER_STACK;
	काष्ठा perf_callchain_entry *trace;
	bool kernel = !user;
	पूर्णांक err = -EINVAL;
	u64 *ips;

	अगर (unlikely(flags & ~(BPF_F_SKIP_FIELD_MASK | BPF_F_USER_STACK |
			       BPF_F_USER_BUILD_ID)))
		जाओ clear;
	अगर (kernel && user_build_id)
		जाओ clear;

	elem_size = (user && user_build_id) ? माप(काष्ठा bpf_stack_build_id)
					    : माप(u64);
	अगर (unlikely(size % elem_size))
		जाओ clear;

	/* cannot get valid user stack क्रम task without user_mode regs */
	अगर (task && user && !user_mode(regs))
		जाओ err_fault;

	num_elem = size / elem_size;
	अगर (sysctl_perf_event_max_stack < num_elem)
		init_nr = 0;
	अन्यथा
		init_nr = sysctl_perf_event_max_stack - num_elem;

	अगर (trace_in)
		trace = trace_in;
	अन्यथा अगर (kernel && task)
		trace = get_callchain_entry_क्रम_task(task, init_nr);
	अन्यथा
		trace = get_perf_callchain(regs, init_nr, kernel, user,
					   sysctl_perf_event_max_stack,
					   false, false);
	अगर (unlikely(!trace))
		जाओ err_fault;

	trace_nr = trace->nr - init_nr;
	अगर (trace_nr < skip)
		जाओ err_fault;

	trace_nr -= skip;
	trace_nr = (trace_nr <= num_elem) ? trace_nr : num_elem;
	copy_len = trace_nr * elem_size;
	ips = trace->ip + skip + init_nr;
	अगर (user && user_build_id)
		stack_map_get_build_id_offset(buf, ips, trace_nr, user);
	अन्यथा
		स_नकल(buf, ips, copy_len);

	अगर (size > copy_len)
		स_रखो(buf + copy_len, 0, size - copy_len);
	वापस copy_len;

err_fault:
	err = -EFAULT;
clear:
	स_रखो(buf, 0, size);
	वापस err;
पूर्ण

BPF_CALL_4(bpf_get_stack, काष्ठा pt_regs *, regs, व्योम *, buf, u32, size,
	   u64, flags)
अणु
	वापस __bpf_get_stack(regs, शून्य, शून्य, buf, size, flags);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_stack_proto = अणु
	.func		= bpf_get_stack,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg3_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_get_task_stack, काष्ठा task_काष्ठा *, task, व्योम *, buf,
	   u32, size, u64, flags)
अणु
	काष्ठा pt_regs *regs;
	दीर्घ res;

	अगर (!try_get_task_stack(task))
		वापस -EFAULT;

	regs = task_pt_regs(task);
	res = __bpf_get_stack(regs, task, शून्य, buf, size, flags);
	put_task_stack(task);

	वापस res;
पूर्ण

BTF_ID_LIST_SINGLE(bpf_get_task_stack_btf_ids, काष्ठा, task_काष्ठा)

स्थिर काष्ठा bpf_func_proto bpf_get_task_stack_proto = अणु
	.func		= bpf_get_task_stack,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID,
	.arg1_btf_id	= &bpf_get_task_stack_btf_ids[0],
	.arg2_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg3_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_get_stack_pe, काष्ठा bpf_perf_event_data_kern *, ctx,
	   व्योम *, buf, u32, size, u64, flags)
अणु
	काष्ठा pt_regs *regs = (काष्ठा pt_regs *)(ctx->regs);
	काष्ठा perf_event *event = ctx->event;
	काष्ठा perf_callchain_entry *trace;
	bool kernel, user;
	पूर्णांक err = -EINVAL;
	__u64 nr_kernel;

	अगर (!(event->attr.sample_type & __PERF_SAMPLE_CALLCHAIN_EARLY))
		वापस __bpf_get_stack(regs, शून्य, शून्य, buf, size, flags);

	अगर (unlikely(flags & ~(BPF_F_SKIP_FIELD_MASK | BPF_F_USER_STACK |
			       BPF_F_USER_BUILD_ID)))
		जाओ clear;

	user = flags & BPF_F_USER_STACK;
	kernel = !user;

	err = -EFAULT;
	trace = ctx->data->callchain;
	अगर (unlikely(!trace))
		जाओ clear;

	nr_kernel = count_kernel_ip(trace);

	अगर (kernel) अणु
		__u64 nr = trace->nr;

		trace->nr = nr_kernel;
		err = __bpf_get_stack(regs, शून्य, trace, buf, size, flags);

		/* restore nr */
		trace->nr = nr;
	पूर्ण अन्यथा अणु /* user */
		u64 skip = flags & BPF_F_SKIP_FIELD_MASK;

		skip += nr_kernel;
		अगर (skip > BPF_F_SKIP_FIELD_MASK)
			जाओ clear;

		flags = (flags & ~BPF_F_SKIP_FIELD_MASK) | skip;
		err = __bpf_get_stack(regs, शून्य, trace, buf, size, flags);
	पूर्ण
	वापस err;

clear:
	स_रखो(buf, 0, size);
	वापस err;

पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_stack_proto_pe = अणु
	.func		= bpf_get_stack_pe,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg3_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

/* Called from eBPF program */
अटल व्योम *stack_map_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

/* Called from syscall */
पूर्णांक bpf_stackmap_copy(काष्ठा bpf_map *map, व्योम *key, व्योम *value)
अणु
	काष्ठा bpf_stack_map *smap = container_of(map, काष्ठा bpf_stack_map, map);
	काष्ठा stack_map_bucket *bucket, *old_bucket;
	u32 id = *(u32 *)key, trace_len;

	अगर (unlikely(id >= smap->n_buckets))
		वापस -ENOENT;

	bucket = xchg(&smap->buckets[id], शून्य);
	अगर (!bucket)
		वापस -ENOENT;

	trace_len = bucket->nr * stack_map_data_size(map);
	स_नकल(value, bucket->data, trace_len);
	स_रखो(value + trace_len, 0, map->value_size - trace_len);

	old_bucket = xchg(&smap->buckets[id], bucket);
	अगर (old_bucket)
		pcpu_मुक्तlist_push(&smap->मुक्तlist, &old_bucket->fnode);
	वापस 0;
पूर्ण

अटल पूर्णांक stack_map_get_next_key(काष्ठा bpf_map *map, व्योम *key,
				  व्योम *next_key)
अणु
	काष्ठा bpf_stack_map *smap = container_of(map,
						  काष्ठा bpf_stack_map, map);
	u32 id;

	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());

	अगर (!key) अणु
		id = 0;
	पूर्ण अन्यथा अणु
		id = *(u32 *)key;
		अगर (id >= smap->n_buckets || !smap->buckets[id])
			id = 0;
		अन्यथा
			id++;
	पूर्ण

	जबतक (id < smap->n_buckets && !smap->buckets[id])
		id++;

	अगर (id >= smap->n_buckets)
		वापस -ENOENT;

	*(u32 *)next_key = id;
	वापस 0;
पूर्ण

अटल पूर्णांक stack_map_update_elem(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
				 u64 map_flags)
अणु
	वापस -EINVAL;
पूर्ण

/* Called from syscall or from eBPF program */
अटल पूर्णांक stack_map_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_stack_map *smap = container_of(map, काष्ठा bpf_stack_map, map);
	काष्ठा stack_map_bucket *old_bucket;
	u32 id = *(u32 *)key;

	अगर (unlikely(id >= smap->n_buckets))
		वापस -E2BIG;

	old_bucket = xchg(&smap->buckets[id], शून्य);
	अगर (old_bucket) अणु
		pcpu_मुक्तlist_push(&smap->मुक्तlist, &old_bucket->fnode);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -ENOENT;
	पूर्ण
पूर्ण

/* Called when map->refcnt goes to zero, either from workqueue or from syscall */
अटल व्योम stack_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_stack_map *smap = container_of(map, काष्ठा bpf_stack_map, map);

	bpf_map_area_मुक्त(smap->elems);
	pcpu_मुक्तlist_destroy(&smap->मुक्तlist);
	bpf_map_area_मुक्त(smap);
	put_callchain_buffers();
पूर्ण

अटल पूर्णांक stack_trace_map_btf_id;
स्थिर काष्ठा bpf_map_ops stack_trace_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc = stack_map_alloc,
	.map_मुक्त = stack_map_मुक्त,
	.map_get_next_key = stack_map_get_next_key,
	.map_lookup_elem = stack_map_lookup_elem,
	.map_update_elem = stack_map_update_elem,
	.map_delete_elem = stack_map_delete_elem,
	.map_check_btf = map_check_no_btf,
	.map_btf_name = "bpf_stack_map",
	.map_btf_id = &stack_trace_map_btf_id,
पूर्ण;

अटल पूर्णांक __init stack_map_init(व्योम)
अणु
	पूर्णांक cpu;
	काष्ठा stack_map_irq_work *work;

	क्रम_each_possible_cpu(cpu) अणु
		work = per_cpu_ptr(&up_पढ़ो_work, cpu);
		init_irq_work(&work->irq_work, करो_up_पढ़ो);
	पूर्ण
	वापस 0;
पूर्ण
subsys_initcall(stack_map_init);
