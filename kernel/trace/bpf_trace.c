<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2011-2015 PLUMgrid, http://plumgrid.com
 * Copyright (c) 2016 Facebook
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_perf_event.h>
#समावेश <linux/btf.h>
#समावेश <linux/filter.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kprobes.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/error-injection.h>
#समावेश <linux/btf_ids.h>
#समावेश <linux/bpf_lsm.h>

#समावेश <net/bpf_sk_storage.h>

#समावेश <uapi/linux/bpf.h>
#समावेश <uapi/linux/btf.h>

#समावेश <यंत्र/tlb.h>

#समावेश "trace_probe.h"
#समावेश "trace.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "bpf_trace.h"

#घोषणा bpf_event_rcu_dereference(p)					\
	rcu_dereference_रक्षित(p, lockdep_is_held(&bpf_event_mutex))

#अगर_घोषित CONFIG_MODULES
काष्ठा bpf_trace_module अणु
	काष्ठा module *module;
	काष्ठा list_head list;
पूर्ण;

अटल LIST_HEAD(bpf_trace_modules);
अटल DEFINE_MUTEX(bpf_module_mutex);

अटल काष्ठा bpf_raw_event_map *bpf_get_raw_tracepoपूर्णांक_module(स्थिर अक्षर *name)
अणु
	काष्ठा bpf_raw_event_map *btp, *ret = शून्य;
	काष्ठा bpf_trace_module *bपंचांग;
	अचिन्हित पूर्णांक i;

	mutex_lock(&bpf_module_mutex);
	list_क्रम_each_entry(bपंचांग, &bpf_trace_modules, list) अणु
		क्रम (i = 0; i < bपंचांग->module->num_bpf_raw_events; ++i) अणु
			btp = &bपंचांग->module->bpf_raw_events[i];
			अगर (!म_भेद(btp->tp->name, name)) अणु
				अगर (try_module_get(bपंचांग->module))
					ret = btp;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&bpf_module_mutex);
	वापस ret;
पूर्ण
#अन्यथा
अटल काष्ठा bpf_raw_event_map *bpf_get_raw_tracepoपूर्णांक_module(स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_MODULES */

u64 bpf_get_stackid(u64 r1, u64 r2, u64 r3, u64 r4, u64 r5);
u64 bpf_get_stack(u64 r1, u64 r2, u64 r3, u64 r4, u64 r5);

अटल पूर्णांक bpf_btf_म_लिखो_prepare(काष्ठा btf_ptr *ptr, u32 btf_ptr_size,
				  u64 flags, स्थिर काष्ठा btf **btf,
				  s32 *btf_id);

/**
 * trace_call_bpf - invoke BPF program
 * @call: tracepoपूर्णांक event
 * @ctx: opaque context poपूर्णांकer
 *
 * kprobe handlers execute BPF programs via this helper.
 * Can be used from अटल tracepoपूर्णांकs in the future.
 *
 * Return: BPF programs always वापस an पूर्णांकeger which is पूर्णांकerpreted by
 * kprobe handler as:
 * 0 - वापस from kprobe (event is filtered out)
 * 1 - store kprobe event पूर्णांकo ring buffer
 * Other values are reserved and currently alias to 1
 */
अचिन्हित पूर्णांक trace_call_bpf(काष्ठा trace_event_call *call, व्योम *ctx)
अणु
	अचिन्हित पूर्णांक ret;

	cant_sleep();

	अगर (unlikely(__this_cpu_inc_वापस(bpf_prog_active) != 1)) अणु
		/*
		 * since some bpf program is alपढ़ोy running on this cpu,
		 * करोn't call पूर्णांकo another bpf program (same or dअगरferent)
		 * and करोn't send kprobe event पूर्णांकo ring-buffer,
		 * so वापस zero here
		 */
		ret = 0;
		जाओ out;
	पूर्ण

	/*
	 * Instead of moving rcu_पढ़ो_lock/rcu_dereference/rcu_पढ़ो_unlock
	 * to all call sites, we did a bpf_prog_array_valid() there to check
	 * whether call->prog_array is empty or not, which is
	 * a heuristic to speed up execution.
	 *
	 * If bpf_prog_array_valid() fetched prog_array was
	 * non-शून्य, we go पूर्णांकo trace_call_bpf() and करो the actual
	 * proper rcu_dereference() under RCU lock.
	 * If it turns out that prog_array is शून्य then, we bail out.
	 * For the opposite, अगर the bpf_prog_array_valid() fetched poपूर्णांकer
	 * was शून्य, you'll skip the prog_array with the risk of missing
	 * out of events when it was updated in between this and the
	 * rcu_dereference() which is accepted risk.
	 */
	ret = BPF_PROG_RUN_ARRAY_CHECK(call->prog_array, ctx, BPF_PROG_RUN);

 out:
	__this_cpu_dec(bpf_prog_active);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_BPF_KPROBE_OVERRIDE
BPF_CALL_2(bpf_override_वापस, काष्ठा pt_regs *, regs, अचिन्हित दीर्घ, rc)
अणु
	regs_set_वापस_value(regs, rc);
	override_function_with_वापस(regs);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_override_वापस_proto = अणु
	.func		= bpf_override_वापस,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;
#पूर्ण_अगर

अटल __always_अंतरभूत पूर्णांक
bpf_probe_पढ़ो_user_common(व्योम *dst, u32 size, स्थिर व्योम __user *unsafe_ptr)
अणु
	पूर्णांक ret;

	ret = copy_from_user_nofault(dst, unsafe_ptr, size);
	अगर (unlikely(ret < 0))
		स_रखो(dst, 0, size);
	वापस ret;
पूर्ण

BPF_CALL_3(bpf_probe_पढ़ो_user, व्योम *, dst, u32, size,
	   स्थिर व्योम __user *, unsafe_ptr)
अणु
	वापस bpf_probe_पढ़ो_user_common(dst, size, unsafe_ptr);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_probe_पढ़ो_user_proto = अणु
	.func		= bpf_probe_पढ़ो_user,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg2_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

अटल __always_अंतरभूत पूर्णांक
bpf_probe_पढ़ो_user_str_common(व्योम *dst, u32 size,
			       स्थिर व्योम __user *unsafe_ptr)
अणु
	पूर्णांक ret;

	/*
	 * NB: We rely on म_नकलन_from_user() not copying junk past the NUL
	 * terminator पूर्णांकo `dst`.
	 *
	 * म_नकलन_from_user() करोes दीर्घ-sized strides in the fast path. If the
	 * म_नकलन करोes not mask out the bytes after the NUL in `unsafe_ptr`,
	 * then there could be junk after the NUL in `dst`. If user takes `dst`
	 * and keys a hash map with it, then semantically identical strings can
	 * occupy multiple entries in the map.
	 */
	ret = म_नकलन_from_user_nofault(dst, unsafe_ptr, size);
	अगर (unlikely(ret < 0))
		स_रखो(dst, 0, size);
	वापस ret;
पूर्ण

BPF_CALL_3(bpf_probe_पढ़ो_user_str, व्योम *, dst, u32, size,
	   स्थिर व्योम __user *, unsafe_ptr)
अणु
	वापस bpf_probe_पढ़ो_user_str_common(dst, size, unsafe_ptr);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_probe_पढ़ो_user_str_proto = अणु
	.func		= bpf_probe_पढ़ो_user_str,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg2_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

अटल __always_अंतरभूत पूर्णांक
bpf_probe_पढ़ो_kernel_common(व्योम *dst, u32 size, स्थिर व्योम *unsafe_ptr)
अणु
	पूर्णांक ret;

	ret = copy_from_kernel_nofault(dst, unsafe_ptr, size);
	अगर (unlikely(ret < 0))
		स_रखो(dst, 0, size);
	वापस ret;
पूर्ण

BPF_CALL_3(bpf_probe_पढ़ो_kernel, व्योम *, dst, u32, size,
	   स्थिर व्योम *, unsafe_ptr)
अणु
	वापस bpf_probe_पढ़ो_kernel_common(dst, size, unsafe_ptr);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_probe_पढ़ो_kernel_proto = अणु
	.func		= bpf_probe_पढ़ो_kernel,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg2_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

अटल __always_अंतरभूत पूर्णांक
bpf_probe_पढ़ो_kernel_str_common(व्योम *dst, u32 size, स्थिर व्योम *unsafe_ptr)
अणु
	पूर्णांक ret;

	/*
	 * The म_नकलन_from_kernel_nofault() call will likely not fill the
	 * entire buffer, but that's okay in this circumstance as we're probing
	 * arbitrary memory anyway similar to bpf_probe_पढ़ो_*() and might
	 * as well probe the stack. Thus, memory is explicitly cleared
	 * only in error हाल, so that improper users ignoring वापस
	 * code altogether करोn't copy garbage; otherwise length of string
	 * is वापसed that can be used क्रम bpf_perf_event_output() et al.
	 */
	ret = म_नकलन_from_kernel_nofault(dst, unsafe_ptr, size);
	अगर (unlikely(ret < 0))
		स_रखो(dst, 0, size);
	वापस ret;
पूर्ण

BPF_CALL_3(bpf_probe_पढ़ो_kernel_str, व्योम *, dst, u32, size,
	   स्थिर व्योम *, unsafe_ptr)
अणु
	वापस bpf_probe_पढ़ो_kernel_str_common(dst, size, unsafe_ptr);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_probe_पढ़ो_kernel_str_proto = अणु
	.func		= bpf_probe_पढ़ो_kernel_str,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg2_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

#अगर_घोषित CONFIG_ARCH_HAS_NON_OVERLAPPING_ADDRESS_SPACE
BPF_CALL_3(bpf_probe_पढ़ो_compat, व्योम *, dst, u32, size,
	   स्थिर व्योम *, unsafe_ptr)
अणु
	अगर ((अचिन्हित दीर्घ)unsafe_ptr < TASK_SIZE) अणु
		वापस bpf_probe_पढ़ो_user_common(dst, size,
				(__क्रमce व्योम __user *)unsafe_ptr);
	पूर्ण
	वापस bpf_probe_पढ़ो_kernel_common(dst, size, unsafe_ptr);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_probe_पढ़ो_compat_proto = अणु
	.func		= bpf_probe_पढ़ो_compat,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg2_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_3(bpf_probe_पढ़ो_compat_str, व्योम *, dst, u32, size,
	   स्थिर व्योम *, unsafe_ptr)
अणु
	अगर ((अचिन्हित दीर्घ)unsafe_ptr < TASK_SIZE) अणु
		वापस bpf_probe_पढ़ो_user_str_common(dst, size,
				(__क्रमce व्योम __user *)unsafe_ptr);
	पूर्ण
	वापस bpf_probe_पढ़ो_kernel_str_common(dst, size, unsafe_ptr);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_probe_पढ़ो_compat_str_proto = अणु
	.func		= bpf_probe_पढ़ो_compat_str,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg2_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;
#पूर्ण_अगर /* CONFIG_ARCH_HAS_NON_OVERLAPPING_ADDRESS_SPACE */

BPF_CALL_3(bpf_probe_ग_लिखो_user, व्योम __user *, unsafe_ptr, स्थिर व्योम *, src,
	   u32, size)
अणु
	/*
	 * Ensure we're in user context which is safe क्रम the helper to
	 * run. This helper has no business in a kthपढ़ो.
	 *
	 * access_ok() should prevent writing to non-user memory, but in
	 * some situations (nommu, temporary चयन, etc) access_ok() करोes
	 * not provide enough validation, hence the check on KERNEL_DS.
	 *
	 * nmi_uaccess_okay() ensures the probe is not run in an पूर्णांकerim
	 * state, when the task or mm are चयनed. This is specअगरically
	 * required to prevent the use of temporary mm.
	 */

	अगर (unlikely(in_पूर्णांकerrupt() ||
		     current->flags & (PF_KTHREAD | PF_EXITING)))
		वापस -EPERM;
	अगर (unlikely(uaccess_kernel()))
		वापस -EPERM;
	अगर (unlikely(!nmi_uaccess_okay()))
		वापस -EPERM;

	वापस copy_to_user_nofault(unsafe_ptr, src, size);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_probe_ग_लिखो_user_proto = अणु
	.func		= bpf_probe_ग_लिखो_user,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_ANYTHING,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto *bpf_get_probe_ग_लिखो_proto(व्योम)
अणु
	अगर (!capable(CAP_SYS_ADMIN))
		वापस शून्य;

	pr_warn_ratelimited("%s[%d] is installing a program with bpf_probe_write_user helper that may corrupt user memory!",
			    current->comm, task_pid_nr(current));

	वापस &bpf_probe_ग_लिखो_user_proto;
पूर्ण

अटल DEFINE_RAW_SPINLOCK(trace_prपूर्णांकk_lock);

#घोषणा MAX_TRACE_PRINTK_VARARGS	3
#घोषणा BPF_TRACE_PRINTK_SIZE		1024

BPF_CALL_5(bpf_trace_prपूर्णांकk, अक्षर *, fmt, u32, fmt_size, u64, arg1,
	   u64, arg2, u64, arg3)
अणु
	u64 args[MAX_TRACE_PRINTK_VARARGS] = अणु arg1, arg2, arg3 पूर्ण;
	u32 *bin_args;
	अटल अक्षर buf[BPF_TRACE_PRINTK_SIZE];
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = bpf_bम_लिखो_prepare(fmt, fmt_size, args, &bin_args,
				  MAX_TRACE_PRINTK_VARARGS);
	अगर (ret < 0)
		वापस ret;

	raw_spin_lock_irqsave(&trace_prपूर्णांकk_lock, flags);
	ret = bstr_म_लिखो(buf, माप(buf), fmt, bin_args);

	trace_bpf_trace_prपूर्णांकk(buf);
	raw_spin_unlock_irqrestore(&trace_prपूर्णांकk_lock, flags);

	bpf_bम_लिखो_cleanup();

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_trace_prपूर्णांकk_proto = अणु
	.func		= bpf_trace_prपूर्णांकk,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_MEM,
	.arg2_type	= ARG_CONST_SIZE,
पूर्ण;

स्थिर काष्ठा bpf_func_proto *bpf_get_trace_prपूर्णांकk_proto(व्योम)
अणु
	/*
	 * This program might be calling bpf_trace_prपूर्णांकk,
	 * so enable the associated bpf_trace/bpf_trace_prपूर्णांकk event.
	 * Repeat this each समय as it is possible a user has
	 * disabled bpf_trace_prपूर्णांकk events.  By loading a program
	 * calling bpf_trace_prपूर्णांकk() however the user has expressed
	 * the पूर्णांकent to see such events.
	 */
	अगर (trace_set_clr_event("bpf_trace", "bpf_trace_printk", 1))
		pr_warn_ratelimited("could not enable bpf_trace_printk events");

	वापस &bpf_trace_prपूर्णांकk_proto;
पूर्ण

#घोषणा MAX_SEQ_PRINTF_VARARGS		12

BPF_CALL_5(bpf_seq_म_लिखो, काष्ठा seq_file *, m, अक्षर *, fmt, u32, fmt_size,
	   स्थिर व्योम *, data, u32, data_len)
अणु
	पूर्णांक err, num_args;
	u32 *bin_args;

	अगर (data_len & 7 || data_len > MAX_SEQ_PRINTF_VARARGS * 8 ||
	    (data_len && !data))
		वापस -EINVAL;
	num_args = data_len / 8;

	err = bpf_bम_लिखो_prepare(fmt, fmt_size, data, &bin_args, num_args);
	अगर (err < 0)
		वापस err;

	seq_bम_लिखो(m, fmt, bin_args);

	bpf_bम_लिखो_cleanup();

	वापस seq_has_overflowed(m) ? -EOVERFLOW : 0;
पूर्ण

BTF_ID_LIST_SINGLE(btf_seq_file_ids, काष्ठा, seq_file)

अटल स्थिर काष्ठा bpf_func_proto bpf_seq_म_लिखो_proto = अणु
	.func		= bpf_seq_म_लिखो,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID,
	.arg1_btf_id	= &btf_seq_file_ids[0],
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE,
	.arg4_type      = ARG_PTR_TO_MEM_OR_शून्य,
	.arg5_type      = ARG_CONST_SIZE_OR_ZERO,
पूर्ण;

BPF_CALL_3(bpf_seq_ग_लिखो, काष्ठा seq_file *, m, स्थिर व्योम *, data, u32, len)
अणु
	वापस seq_ग_लिखो(m, data, len) ? -EOVERFLOW : 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_seq_ग_लिखो_proto = अणु
	.func		= bpf_seq_ग_लिखो,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID,
	.arg1_btf_id	= &btf_seq_file_ids[0],
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE_OR_ZERO,
पूर्ण;

BPF_CALL_4(bpf_seq_म_लिखो_btf, काष्ठा seq_file *, m, काष्ठा btf_ptr *, ptr,
	   u32, btf_ptr_size, u64, flags)
अणु
	स्थिर काष्ठा btf *btf;
	s32 btf_id;
	पूर्णांक ret;

	ret = bpf_btf_म_लिखो_prepare(ptr, btf_ptr_size, flags, &btf, &btf_id);
	अगर (ret)
		वापस ret;

	वापस btf_type_seq_show_flags(btf, btf_id, ptr->ptr, m, flags);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_seq_म_लिखो_btf_proto = अणु
	.func		= bpf_seq_म_लिखो_btf,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID,
	.arg1_btf_id	= &btf_seq_file_ids[0],
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

अटल __always_अंतरभूत पूर्णांक
get_map_perf_counter(काष्ठा bpf_map *map, u64 flags,
		     u64 *value, u64 *enabled, u64 *running)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	u64 index = flags & BPF_F_INDEX_MASK;
	काष्ठा bpf_event_entry *ee;

	अगर (unlikely(flags & ~(BPF_F_INDEX_MASK)))
		वापस -EINVAL;
	अगर (index == BPF_F_CURRENT_CPU)
		index = cpu;
	अगर (unlikely(index >= array->map.max_entries))
		वापस -E2BIG;

	ee = READ_ONCE(array->ptrs[index]);
	अगर (!ee)
		वापस -ENOENT;

	वापस perf_event_पढ़ो_local(ee->event, value, enabled, running);
पूर्ण

BPF_CALL_2(bpf_perf_event_पढ़ो, काष्ठा bpf_map *, map, u64, flags)
अणु
	u64 value = 0;
	पूर्णांक err;

	err = get_map_perf_counter(map, flags, &value, शून्य, शून्य);
	/*
	 * this api is ugly since we miss [-22..-2] range of valid
	 * counter values, but that's uapi
	 */
	अगर (err)
		वापस err;
	वापस value;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_perf_event_पढ़ो_proto = अणु
	.func		= bpf_perf_event_पढ़ो,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_perf_event_पढ़ो_value, काष्ठा bpf_map *, map, u64, flags,
	   काष्ठा bpf_perf_event_value *, buf, u32, size)
अणु
	पूर्णांक err = -EINVAL;

	अगर (unlikely(size != माप(काष्ठा bpf_perf_event_value)))
		जाओ clear;
	err = get_map_perf_counter(map, flags, &buf->counter, &buf->enabled,
				   &buf->running);
	अगर (unlikely(err))
		जाओ clear;
	वापस 0;
clear:
	स_रखो(buf, 0, size);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_perf_event_पढ़ो_value_proto = अणु
	.func		= bpf_perf_event_पढ़ो_value,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg4_type	= ARG_CONST_SIZE,
पूर्ण;

अटल __always_अंतरभूत u64
__bpf_perf_event_output(काष्ठा pt_regs *regs, काष्ठा bpf_map *map,
			u64 flags, काष्ठा perf_sample_data *sd)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	u64 index = flags & BPF_F_INDEX_MASK;
	काष्ठा bpf_event_entry *ee;
	काष्ठा perf_event *event;

	अगर (index == BPF_F_CURRENT_CPU)
		index = cpu;
	अगर (unlikely(index >= array->map.max_entries))
		वापस -E2BIG;

	ee = READ_ONCE(array->ptrs[index]);
	अगर (!ee)
		वापस -ENOENT;

	event = ee->event;
	अगर (unlikely(event->attr.type != PERF_TYPE_SOFTWARE ||
		     event->attr.config != PERF_COUNT_SW_BPF_OUTPUT))
		वापस -EINVAL;

	अगर (unlikely(event->oncpu != cpu))
		वापस -EOPNOTSUPP;

	वापस perf_event_output(event, sd, regs);
पूर्ण

/*
 * Support executing tracepoपूर्णांकs in normal, irq, and nmi context that each call
 * bpf_perf_event_output
 */
काष्ठा bpf_trace_sample_data अणु
	काष्ठा perf_sample_data sds[3];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा bpf_trace_sample_data, bpf_trace_sds);
अटल DEFINE_PER_CPU(पूर्णांक, bpf_trace_nest_level);
BPF_CALL_5(bpf_perf_event_output, काष्ठा pt_regs *, regs, काष्ठा bpf_map *, map,
	   u64, flags, व्योम *, data, u64, size)
अणु
	काष्ठा bpf_trace_sample_data *sds = this_cpu_ptr(&bpf_trace_sds);
	पूर्णांक nest_level = this_cpu_inc_वापस(bpf_trace_nest_level);
	काष्ठा perf_raw_record raw = अणु
		.frag = अणु
			.size = size,
			.data = data,
		पूर्ण,
	पूर्ण;
	काष्ठा perf_sample_data *sd;
	पूर्णांक err;

	अगर (WARN_ON_ONCE(nest_level > ARRAY_SIZE(sds->sds))) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	sd = &sds->sds[nest_level - 1];

	अगर (unlikely(flags & ~(BPF_F_INDEX_MASK))) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	perf_sample_data_init(sd, 0, 0);
	sd->raw = &raw;

	err = __bpf_perf_event_output(regs, map, flags, sd);

out:
	this_cpu_dec(bpf_trace_nest_level);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_perf_event_output_proto = अणु
	.func		= bpf_perf_event_output,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_PTR_TO_MEM,
	.arg5_type	= ARG_CONST_SIZE_OR_ZERO,
पूर्ण;

अटल DEFINE_PER_CPU(पूर्णांक, bpf_event_output_nest_level);
काष्ठा bpf_nested_pt_regs अणु
	काष्ठा pt_regs regs[3];
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा bpf_nested_pt_regs, bpf_pt_regs);
अटल DEFINE_PER_CPU(काष्ठा bpf_trace_sample_data, bpf_misc_sds);

u64 bpf_event_output(काष्ठा bpf_map *map, u64 flags, व्योम *meta, u64 meta_size,
		     व्योम *ctx, u64 ctx_size, bpf_ctx_copy_t ctx_copy)
अणु
	पूर्णांक nest_level = this_cpu_inc_वापस(bpf_event_output_nest_level);
	काष्ठा perf_raw_frag frag = अणु
		.copy		= ctx_copy,
		.size		= ctx_size,
		.data		= ctx,
	पूर्ण;
	काष्ठा perf_raw_record raw = अणु
		.frag = अणु
			अणु
				.next	= ctx_size ? &frag : शून्य,
			पूर्ण,
			.size	= meta_size,
			.data	= meta,
		पूर्ण,
	पूर्ण;
	काष्ठा perf_sample_data *sd;
	काष्ठा pt_regs *regs;
	u64 ret;

	अगर (WARN_ON_ONCE(nest_level > ARRAY_SIZE(bpf_misc_sds.sds))) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण
	sd = this_cpu_ptr(&bpf_misc_sds.sds[nest_level - 1]);
	regs = this_cpu_ptr(&bpf_pt_regs.regs[nest_level - 1]);

	perf_fetch_caller_regs(regs);
	perf_sample_data_init(sd, 0, 0);
	sd->raw = &raw;

	ret = __bpf_perf_event_output(regs, map, flags, sd);
out:
	this_cpu_dec(bpf_event_output_nest_level);
	वापस ret;
पूर्ण

BPF_CALL_0(bpf_get_current_task)
अणु
	वापस (दीर्घ) current;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_current_task_proto = अणु
	.func		= bpf_get_current_task,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
पूर्ण;

BPF_CALL_0(bpf_get_current_task_btf)
अणु
	वापस (अचिन्हित दीर्घ) current;
पूर्ण

BTF_ID_LIST_SINGLE(bpf_get_current_btf_ids, काष्ठा, task_काष्ठा)

अटल स्थिर काष्ठा bpf_func_proto bpf_get_current_task_btf_proto = अणु
	.func		= bpf_get_current_task_btf,
	.gpl_only	= true,
	.ret_type	= RET_PTR_TO_BTF_ID,
	.ret_btf_id	= &bpf_get_current_btf_ids[0],
पूर्ण;

BPF_CALL_2(bpf_current_task_under_cgroup, काष्ठा bpf_map *, map, u32, idx)
अणु
	काष्ठा bpf_array *array = container_of(map, काष्ठा bpf_array, map);
	काष्ठा cgroup *cgrp;

	अगर (unlikely(idx >= array->map.max_entries))
		वापस -E2BIG;

	cgrp = READ_ONCE(array->ptrs[idx]);
	अगर (unlikely(!cgrp))
		वापस -EAGAIN;

	वापस task_under_cgroup_hierarchy(current, cgrp);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_current_task_under_cgroup_proto = अणु
	.func           = bpf_current_task_under_cgroup,
	.gpl_only       = false,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_CONST_MAP_PTR,
	.arg2_type      = ARG_ANYTHING,
पूर्ण;

काष्ठा send_संकेत_irq_work अणु
	काष्ठा irq_work irq_work;
	काष्ठा task_काष्ठा *task;
	u32 sig;
	क्रमागत pid_type type;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा send_संकेत_irq_work, send_संकेत_work);

अटल व्योम करो_bpf_send_संकेत(काष्ठा irq_work *entry)
अणु
	काष्ठा send_संकेत_irq_work *work;

	work = container_of(entry, काष्ठा send_संकेत_irq_work, irq_work);
	group_send_sig_info(work->sig, SEND_SIG_PRIV, work->task, work->type);
पूर्ण

अटल पूर्णांक bpf_send_संकेत_common(u32 sig, क्रमागत pid_type type)
अणु
	काष्ठा send_संकेत_irq_work *work = शून्य;

	/* Similar to bpf_probe_ग_लिखो_user, task needs to be
	 * in a sound condition and kernel memory access be
	 * permitted in order to send संकेत to the current
	 * task.
	 */
	अगर (unlikely(current->flags & (PF_KTHREAD | PF_EXITING)))
		वापस -EPERM;
	अगर (unlikely(uaccess_kernel()))
		वापस -EPERM;
	अगर (unlikely(!nmi_uaccess_okay()))
		वापस -EPERM;

	अगर (irqs_disabled()) अणु
		/* Do an early check on संकेत validity. Otherwise,
		 * the error is lost in deferred irq_work.
		 */
		अगर (unlikely(!valid_संकेत(sig)))
			वापस -EINVAL;

		work = this_cpu_ptr(&send_संकेत_work);
		अगर (irq_work_is_busy(&work->irq_work))
			वापस -EBUSY;

		/* Add the current task, which is the target of sending संकेत,
		 * to the irq_work. The current task may change when queued
		 * irq works get executed.
		 */
		work->task = current;
		work->sig = sig;
		work->type = type;
		irq_work_queue(&work->irq_work);
		वापस 0;
	पूर्ण

	वापस group_send_sig_info(sig, SEND_SIG_PRIV, current, type);
पूर्ण

BPF_CALL_1(bpf_send_संकेत, u32, sig)
अणु
	वापस bpf_send_संकेत_common(sig, PIDTYPE_TGID);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_send_संकेत_proto = अणु
	.func		= bpf_send_संकेत,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_1(bpf_send_संकेत_thपढ़ो, u32, sig)
अणु
	वापस bpf_send_संकेत_common(sig, PIDTYPE_PID);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_send_संकेत_thपढ़ो_proto = अणु
	.func		= bpf_send_संकेत_thपढ़ो,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_3(bpf_d_path, काष्ठा path *, path, अक्षर *, buf, u32, sz)
अणु
	दीर्घ len;
	अक्षर *p;

	अगर (!sz)
		वापस 0;

	p = d_path(path, buf, sz);
	अगर (IS_ERR(p)) अणु
		len = PTR_ERR(p);
	पूर्ण अन्यथा अणु
		len = buf + sz - p;
		स_हटाओ(buf, p, len);
	पूर्ण

	वापस len;
पूर्ण

BTF_SET_START(btf_allowlist_d_path)
#अगर_घोषित CONFIG_SECURITY
BTF_ID(func, security_file_permission)
BTF_ID(func, security_inode_getattr)
BTF_ID(func, security_file_खोलो)
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY_PATH
BTF_ID(func, security_path_truncate)
#पूर्ण_अगर
BTF_ID(func, vfs_truncate)
BTF_ID(func, vfs_fallocate)
BTF_ID(func, dentry_खोलो)
BTF_ID(func, vfs_getattr)
BTF_ID(func, filp_बंद)
BTF_SET_END(btf_allowlist_d_path)

अटल bool bpf_d_path_allowed(स्थिर काष्ठा bpf_prog *prog)
अणु
	अगर (prog->type == BPF_PROG_TYPE_TRACING &&
	    prog->expected_attach_type == BPF_TRACE_ITER)
		वापस true;

	अगर (prog->type == BPF_PROG_TYPE_LSM)
		वापस bpf_lsm_is_sleepable_hook(prog->aux->attach_btf_id);

	वापस btf_id_set_contains(&btf_allowlist_d_path,
				   prog->aux->attach_btf_id);
पूर्ण

BTF_ID_LIST_SINGLE(bpf_d_path_btf_ids, काष्ठा, path)

अटल स्थिर काष्ठा bpf_func_proto bpf_d_path_proto = अणु
	.func		= bpf_d_path,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_BTF_ID,
	.arg1_btf_id	= &bpf_d_path_btf_ids[0],
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE_OR_ZERO,
	.allowed	= bpf_d_path_allowed,
पूर्ण;

#घोषणा BTF_F_ALL	(BTF_F_COMPACT  | BTF_F_NONAME | \
			 BTF_F_PTR_RAW | BTF_F_ZERO)

अटल पूर्णांक bpf_btf_म_लिखो_prepare(काष्ठा btf_ptr *ptr, u32 btf_ptr_size,
				  u64 flags, स्थिर काष्ठा btf **btf,
				  s32 *btf_id)
अणु
	स्थिर काष्ठा btf_type *t;

	अगर (unlikely(flags & ~(BTF_F_ALL)))
		वापस -EINVAL;

	अगर (btf_ptr_size != माप(काष्ठा btf_ptr))
		वापस -EINVAL;

	*btf = bpf_get_btf_vmlinux();

	अगर (IS_ERR_OR_शून्य(*btf))
		वापस IS_ERR(*btf) ? PTR_ERR(*btf) : -EINVAL;

	अगर (ptr->type_id > 0)
		*btf_id = ptr->type_id;
	अन्यथा
		वापस -EINVAL;

	अगर (*btf_id > 0)
		t = btf_type_by_id(*btf, *btf_id);
	अगर (*btf_id <= 0 || !t)
		वापस -ENOENT;

	वापस 0;
पूर्ण

BPF_CALL_5(bpf_snम_लिखो_btf, अक्षर *, str, u32, str_size, काष्ठा btf_ptr *, ptr,
	   u32, btf_ptr_size, u64, flags)
अणु
	स्थिर काष्ठा btf *btf;
	s32 btf_id;
	पूर्णांक ret;

	ret = bpf_btf_म_लिखो_prepare(ptr, btf_ptr_size, flags, &btf, &btf_id);
	अगर (ret)
		वापस ret;

	वापस btf_type_snम_लिखो_show(btf, btf_id, ptr->ptr, str, str_size,
				      flags);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_snम_लिखो_btf_proto = अणु
	.func		= bpf_snम_लिखो_btf,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_MEM,
	.arg2_type	= ARG_CONST_SIZE,
	.arg3_type	= ARG_PTR_TO_MEM,
	.arg4_type	= ARG_CONST_SIZE,
	.arg5_type	= ARG_ANYTHING,
पूर्ण;

स्थिर काष्ठा bpf_func_proto *
bpf_tracing_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_map_lookup_elem:
		वापस &bpf_map_lookup_elem_proto;
	हाल BPF_FUNC_map_update_elem:
		वापस &bpf_map_update_elem_proto;
	हाल BPF_FUNC_map_delete_elem:
		वापस &bpf_map_delete_elem_proto;
	हाल BPF_FUNC_map_push_elem:
		वापस &bpf_map_push_elem_proto;
	हाल BPF_FUNC_map_pop_elem:
		वापस &bpf_map_pop_elem_proto;
	हाल BPF_FUNC_map_peek_elem:
		वापस &bpf_map_peek_elem_proto;
	हाल BPF_FUNC_kसमय_get_ns:
		वापस &bpf_kसमय_get_ns_proto;
	हाल BPF_FUNC_kसमय_get_boot_ns:
		वापस &bpf_kसमय_get_boot_ns_proto;
	हाल BPF_FUNC_kसमय_get_coarse_ns:
		वापस &bpf_kसमय_get_coarse_ns_proto;
	हाल BPF_FUNC_tail_call:
		वापस &bpf_tail_call_proto;
	हाल BPF_FUNC_get_current_pid_tgid:
		वापस &bpf_get_current_pid_tgid_proto;
	हाल BPF_FUNC_get_current_task:
		वापस &bpf_get_current_task_proto;
	हाल BPF_FUNC_get_current_task_btf:
		वापस &bpf_get_current_task_btf_proto;
	हाल BPF_FUNC_get_current_uid_gid:
		वापस &bpf_get_current_uid_gid_proto;
	हाल BPF_FUNC_get_current_comm:
		वापस &bpf_get_current_comm_proto;
	हाल BPF_FUNC_trace_prपूर्णांकk:
		वापस bpf_get_trace_prपूर्णांकk_proto();
	हाल BPF_FUNC_get_smp_processor_id:
		वापस &bpf_get_smp_processor_id_proto;
	हाल BPF_FUNC_get_numa_node_id:
		वापस &bpf_get_numa_node_id_proto;
	हाल BPF_FUNC_perf_event_पढ़ो:
		वापस &bpf_perf_event_पढ़ो_proto;
	हाल BPF_FUNC_probe_ग_लिखो_user:
		वापस bpf_get_probe_ग_लिखो_proto();
	हाल BPF_FUNC_current_task_under_cgroup:
		वापस &bpf_current_task_under_cgroup_proto;
	हाल BPF_FUNC_get_pअक्रमom_u32:
		वापस &bpf_get_pअक्रमom_u32_proto;
	हाल BPF_FUNC_probe_पढ़ो_user:
		वापस &bpf_probe_पढ़ो_user_proto;
	हाल BPF_FUNC_probe_पढ़ो_kernel:
		वापस security_locked_करोwn(LOCKDOWN_BPF_READ) < 0 ?
		       शून्य : &bpf_probe_पढ़ो_kernel_proto;
	हाल BPF_FUNC_probe_पढ़ो_user_str:
		वापस &bpf_probe_पढ़ो_user_str_proto;
	हाल BPF_FUNC_probe_पढ़ो_kernel_str:
		वापस security_locked_करोwn(LOCKDOWN_BPF_READ) < 0 ?
		       शून्य : &bpf_probe_पढ़ो_kernel_str_proto;
#अगर_घोषित CONFIG_ARCH_HAS_NON_OVERLAPPING_ADDRESS_SPACE
	हाल BPF_FUNC_probe_पढ़ो:
		वापस security_locked_करोwn(LOCKDOWN_BPF_READ) < 0 ?
		       शून्य : &bpf_probe_पढ़ो_compat_proto;
	हाल BPF_FUNC_probe_पढ़ो_str:
		वापस security_locked_करोwn(LOCKDOWN_BPF_READ) < 0 ?
		       शून्य : &bpf_probe_पढ़ो_compat_str_proto;
#पूर्ण_अगर
#अगर_घोषित CONFIG_CGROUPS
	हाल BPF_FUNC_get_current_cgroup_id:
		वापस &bpf_get_current_cgroup_id_proto;
#पूर्ण_अगर
	हाल BPF_FUNC_send_संकेत:
		वापस &bpf_send_संकेत_proto;
	हाल BPF_FUNC_send_संकेत_thपढ़ो:
		वापस &bpf_send_संकेत_thपढ़ो_proto;
	हाल BPF_FUNC_perf_event_पढ़ो_value:
		वापस &bpf_perf_event_पढ़ो_value_proto;
	हाल BPF_FUNC_get_ns_current_pid_tgid:
		वापस &bpf_get_ns_current_pid_tgid_proto;
	हाल BPF_FUNC_ringbuf_output:
		वापस &bpf_ringbuf_output_proto;
	हाल BPF_FUNC_ringbuf_reserve:
		वापस &bpf_ringbuf_reserve_proto;
	हाल BPF_FUNC_ringbuf_submit:
		वापस &bpf_ringbuf_submit_proto;
	हाल BPF_FUNC_ringbuf_discard:
		वापस &bpf_ringbuf_discard_proto;
	हाल BPF_FUNC_ringbuf_query:
		वापस &bpf_ringbuf_query_proto;
	हाल BPF_FUNC_jअगरfies64:
		वापस &bpf_jअगरfies64_proto;
	हाल BPF_FUNC_get_task_stack:
		वापस &bpf_get_task_stack_proto;
	हाल BPF_FUNC_copy_from_user:
		वापस prog->aux->sleepable ? &bpf_copy_from_user_proto : शून्य;
	हाल BPF_FUNC_snम_लिखो_btf:
		वापस &bpf_snम_लिखो_btf_proto;
	हाल BPF_FUNC_per_cpu_ptr:
		वापस &bpf_per_cpu_ptr_proto;
	हाल BPF_FUNC_this_cpu_ptr:
		वापस &bpf_this_cpu_ptr_proto;
	हाल BPF_FUNC_task_storage_get:
		वापस &bpf_task_storage_get_proto;
	हाल BPF_FUNC_task_storage_delete:
		वापस &bpf_task_storage_delete_proto;
	हाल BPF_FUNC_क्रम_each_map_elem:
		वापस &bpf_क्रम_each_map_elem_proto;
	हाल BPF_FUNC_snम_लिखो:
		वापस &bpf_snम_लिखो_proto;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto *
kprobe_prog_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_perf_event_output_proto;
	हाल BPF_FUNC_get_stackid:
		वापस &bpf_get_stackid_proto;
	हाल BPF_FUNC_get_stack:
		वापस &bpf_get_stack_proto;
#अगर_घोषित CONFIG_BPF_KPROBE_OVERRIDE
	हाल BPF_FUNC_override_वापस:
		वापस &bpf_override_वापस_proto;
#पूर्ण_अगर
	शेष:
		वापस bpf_tracing_func_proto(func_id, prog);
	पूर्ण
पूर्ण

/* bpf+kprobe programs can access fields of 'struct pt_regs' */
अटल bool kprobe_prog_is_valid_access(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
					स्थिर काष्ठा bpf_prog *prog,
					काष्ठा bpf_insn_access_aux *info)
अणु
	अगर (off < 0 || off >= माप(काष्ठा pt_regs))
		वापस false;
	अगर (type != BPF_READ)
		वापस false;
	अगर (off % size != 0)
		वापस false;
	/*
	 * Assertion क्रम 32 bit to make sure last 8 byte access
	 * (BPF_DW) to the last 4 byte member is disallowed.
	 */
	अगर (off + size > माप(काष्ठा pt_regs))
		वापस false;

	वापस true;
पूर्ण

स्थिर काष्ठा bpf_verअगरier_ops kprobe_verअगरier_ops = अणु
	.get_func_proto  = kprobe_prog_func_proto,
	.is_valid_access = kprobe_prog_is_valid_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops kprobe_prog_ops = अणु
पूर्ण;

BPF_CALL_5(bpf_perf_event_output_tp, व्योम *, tp_buff, काष्ठा bpf_map *, map,
	   u64, flags, व्योम *, data, u64, size)
अणु
	काष्ठा pt_regs *regs = *(काष्ठा pt_regs **)tp_buff;

	/*
	 * r1 poपूर्णांकs to perf tracepoपूर्णांक buffer where first 8 bytes are hidden
	 * from bpf program and contain a poपूर्णांकer to 'struct pt_regs'. Fetch it
	 * from there and call the same bpf_perf_event_output() helper अंतरभूत.
	 */
	वापस ____bpf_perf_event_output(regs, map, flags, data, size);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_perf_event_output_proto_tp = अणु
	.func		= bpf_perf_event_output_tp,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_PTR_TO_MEM,
	.arg5_type	= ARG_CONST_SIZE_OR_ZERO,
पूर्ण;

BPF_CALL_3(bpf_get_stackid_tp, व्योम *, tp_buff, काष्ठा bpf_map *, map,
	   u64, flags)
अणु
	काष्ठा pt_regs *regs = *(काष्ठा pt_regs **)tp_buff;

	/*
	 * Same comment as in bpf_perf_event_output_tp(), only that this समय
	 * the other helper's function body cannot be अंतरभूतd due to being
	 * बाह्यal, thus we need to call raw helper function.
	 */
	वापस bpf_get_stackid((अचिन्हित दीर्घ) regs, (अचिन्हित दीर्घ) map,
			       flags, 0, 0);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_stackid_proto_tp = अणु
	.func		= bpf_get_stackid_tp,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_get_stack_tp, व्योम *, tp_buff, व्योम *, buf, u32, size,
	   u64, flags)
अणु
	काष्ठा pt_regs *regs = *(काष्ठा pt_regs **)tp_buff;

	वापस bpf_get_stack((अचिन्हित दीर्घ) regs, (अचिन्हित दीर्घ) buf,
			     (अचिन्हित दीर्घ) size, flags, 0);
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_stack_proto_tp = अणु
	.func		= bpf_get_stack_tp,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg3_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto *
tp_prog_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_perf_event_output_proto_tp;
	हाल BPF_FUNC_get_stackid:
		वापस &bpf_get_stackid_proto_tp;
	हाल BPF_FUNC_get_stack:
		वापस &bpf_get_stack_proto_tp;
	शेष:
		वापस bpf_tracing_func_proto(func_id, prog);
	पूर्ण
पूर्ण

अटल bool tp_prog_is_valid_access(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
				    स्थिर काष्ठा bpf_prog *prog,
				    काष्ठा bpf_insn_access_aux *info)
अणु
	अगर (off < माप(व्योम *) || off >= PERF_MAX_TRACE_SIZE)
		वापस false;
	अगर (type != BPF_READ)
		वापस false;
	अगर (off % size != 0)
		वापस false;

	BUILD_BUG_ON(PERF_MAX_TRACE_SIZE % माप(__u64));
	वापस true;
पूर्ण

स्थिर काष्ठा bpf_verअगरier_ops tracepoपूर्णांक_verअगरier_ops = अणु
	.get_func_proto  = tp_prog_func_proto,
	.is_valid_access = tp_prog_is_valid_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops tracepoपूर्णांक_prog_ops = अणु
पूर्ण;

BPF_CALL_3(bpf_perf_prog_पढ़ो_value, काष्ठा bpf_perf_event_data_kern *, ctx,
	   काष्ठा bpf_perf_event_value *, buf, u32, size)
अणु
	पूर्णांक err = -EINVAL;

	अगर (unlikely(size != माप(काष्ठा bpf_perf_event_value)))
		जाओ clear;
	err = perf_event_पढ़ो_local(ctx->event, &buf->counter, &buf->enabled,
				    &buf->running);
	अगर (unlikely(err))
		जाओ clear;
	वापस 0;
clear:
	स_रखो(buf, 0, size);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_perf_prog_पढ़ो_value_proto = अणु
         .func           = bpf_perf_prog_पढ़ो_value,
         .gpl_only       = true,
         .ret_type       = RET_INTEGER,
         .arg1_type      = ARG_PTR_TO_CTX,
         .arg2_type      = ARG_PTR_TO_UNINIT_MEM,
         .arg3_type      = ARG_CONST_SIZE,
पूर्ण;

BPF_CALL_4(bpf_पढ़ो_branch_records, काष्ठा bpf_perf_event_data_kern *, ctx,
	   व्योम *, buf, u32, size, u64, flags)
अणु
#अगर_अघोषित CONFIG_X86
	वापस -ENOENT;
#अन्यथा
	अटल स्थिर u32 br_entry_size = माप(काष्ठा perf_branch_entry);
	काष्ठा perf_branch_stack *br_stack = ctx->data->br_stack;
	u32 to_copy;

	अगर (unlikely(flags & ~BPF_F_GET_BRANCH_RECORDS_SIZE))
		वापस -EINVAL;

	अगर (unlikely(!br_stack))
		वापस -EINVAL;

	अगर (flags & BPF_F_GET_BRANCH_RECORDS_SIZE)
		वापस br_stack->nr * br_entry_size;

	अगर (!buf || (size % br_entry_size != 0))
		वापस -EINVAL;

	to_copy = min_t(u32, br_stack->nr * br_entry_size, size);
	स_नकल(buf, br_stack->entries, to_copy);

	वापस to_copy;
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_पढ़ो_branch_records_proto = अणु
	.func           = bpf_पढ़ो_branch_records,
	.gpl_only       = true,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
	.arg2_type      = ARG_PTR_TO_MEM_OR_शून्य,
	.arg3_type      = ARG_CONST_SIZE_OR_ZERO,
	.arg4_type      = ARG_ANYTHING,
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto *
pe_prog_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_perf_event_output_proto_tp;
	हाल BPF_FUNC_get_stackid:
		वापस &bpf_get_stackid_proto_pe;
	हाल BPF_FUNC_get_stack:
		वापस &bpf_get_stack_proto_pe;
	हाल BPF_FUNC_perf_prog_पढ़ो_value:
		वापस &bpf_perf_prog_पढ़ो_value_proto;
	हाल BPF_FUNC_पढ़ो_branch_records:
		वापस &bpf_पढ़ो_branch_records_proto;
	शेष:
		वापस bpf_tracing_func_proto(func_id, prog);
	पूर्ण
पूर्ण

/*
 * bpf_raw_tp_regs are separate from bpf_pt_regs used from skb/xdp
 * to aव्योम potential recursive reuse issue when/अगर tracepoपूर्णांकs are added
 * inside bpf_*_event_output, bpf_get_stackid and/or bpf_get_stack.
 *
 * Since raw tracepoपूर्णांकs run despite bpf_prog_active, support concurrent usage
 * in normal, irq, and nmi context.
 */
काष्ठा bpf_raw_tp_regs अणु
	काष्ठा pt_regs regs[3];
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा bpf_raw_tp_regs, bpf_raw_tp_regs);
अटल DEFINE_PER_CPU(पूर्णांक, bpf_raw_tp_nest_level);
अटल काष्ठा pt_regs *get_bpf_raw_tp_regs(व्योम)
अणु
	काष्ठा bpf_raw_tp_regs *tp_regs = this_cpu_ptr(&bpf_raw_tp_regs);
	पूर्णांक nest_level = this_cpu_inc_वापस(bpf_raw_tp_nest_level);

	अगर (WARN_ON_ONCE(nest_level > ARRAY_SIZE(tp_regs->regs))) अणु
		this_cpu_dec(bpf_raw_tp_nest_level);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	वापस &tp_regs->regs[nest_level - 1];
पूर्ण

अटल व्योम put_bpf_raw_tp_regs(व्योम)
अणु
	this_cpu_dec(bpf_raw_tp_nest_level);
पूर्ण

BPF_CALL_5(bpf_perf_event_output_raw_tp, काष्ठा bpf_raw_tracepoपूर्णांक_args *, args,
	   काष्ठा bpf_map *, map, u64, flags, व्योम *, data, u64, size)
अणु
	काष्ठा pt_regs *regs = get_bpf_raw_tp_regs();
	पूर्णांक ret;

	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	perf_fetch_caller_regs(regs);
	ret = ____bpf_perf_event_output(regs, map, flags, data, size);

	put_bpf_raw_tp_regs();
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_perf_event_output_proto_raw_tp = अणु
	.func		= bpf_perf_event_output_raw_tp,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_PTR_TO_MEM,
	.arg5_type	= ARG_CONST_SIZE_OR_ZERO,
पूर्ण;

बाह्य स्थिर काष्ठा bpf_func_proto bpf_skb_output_proto;
बाह्य स्थिर काष्ठा bpf_func_proto bpf_xdp_output_proto;

BPF_CALL_3(bpf_get_stackid_raw_tp, काष्ठा bpf_raw_tracepoपूर्णांक_args *, args,
	   काष्ठा bpf_map *, map, u64, flags)
अणु
	काष्ठा pt_regs *regs = get_bpf_raw_tp_regs();
	पूर्णांक ret;

	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	perf_fetch_caller_regs(regs);
	/* similar to bpf_perf_event_output_tp, but pt_regs fetched dअगरferently */
	ret = bpf_get_stackid((अचिन्हित दीर्घ) regs, (अचिन्हित दीर्घ) map,
			      flags, 0, 0);
	put_bpf_raw_tp_regs();
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_stackid_proto_raw_tp = अणु
	.func		= bpf_get_stackid_raw_tp,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_CONST_MAP_PTR,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_4(bpf_get_stack_raw_tp, काष्ठा bpf_raw_tracepoपूर्णांक_args *, args,
	   व्योम *, buf, u32, size, u64, flags)
अणु
	काष्ठा pt_regs *regs = get_bpf_raw_tp_regs();
	पूर्णांक ret;

	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	perf_fetch_caller_regs(regs);
	ret = bpf_get_stack((अचिन्हित दीर्घ) regs, (अचिन्हित दीर्घ) buf,
			    (अचिन्हित दीर्घ) size, flags, 0);
	put_bpf_raw_tp_regs();
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto bpf_get_stack_proto_raw_tp = अणु
	.func		= bpf_get_stack_raw_tp,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_CTX,
	.arg2_type	= ARG_PTR_TO_MEM,
	.arg3_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto *
raw_tp_prog_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_perf_event_output:
		वापस &bpf_perf_event_output_proto_raw_tp;
	हाल BPF_FUNC_get_stackid:
		वापस &bpf_get_stackid_proto_raw_tp;
	हाल BPF_FUNC_get_stack:
		वापस &bpf_get_stack_proto_raw_tp;
	शेष:
		वापस bpf_tracing_func_proto(func_id, prog);
	पूर्ण
पूर्ण

स्थिर काष्ठा bpf_func_proto *
tracing_prog_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
#अगर_घोषित CONFIG_NET
	हाल BPF_FUNC_skb_output:
		वापस &bpf_skb_output_proto;
	हाल BPF_FUNC_xdp_output:
		वापस &bpf_xdp_output_proto;
	हाल BPF_FUNC_skc_to_tcp6_sock:
		वापस &bpf_skc_to_tcp6_sock_proto;
	हाल BPF_FUNC_skc_to_tcp_sock:
		वापस &bpf_skc_to_tcp_sock_proto;
	हाल BPF_FUNC_skc_to_tcp_समयरुको_sock:
		वापस &bpf_skc_to_tcp_समयरुको_sock_proto;
	हाल BPF_FUNC_skc_to_tcp_request_sock:
		वापस &bpf_skc_to_tcp_request_sock_proto;
	हाल BPF_FUNC_skc_to_udp6_sock:
		वापस &bpf_skc_to_udp6_sock_proto;
	हाल BPF_FUNC_sk_storage_get:
		वापस &bpf_sk_storage_get_tracing_proto;
	हाल BPF_FUNC_sk_storage_delete:
		वापस &bpf_sk_storage_delete_tracing_proto;
	हाल BPF_FUNC_sock_from_file:
		वापस &bpf_sock_from_file_proto;
	हाल BPF_FUNC_get_socket_cookie:
		वापस &bpf_get_socket_ptr_cookie_proto;
#पूर्ण_अगर
	हाल BPF_FUNC_seq_म_लिखो:
		वापस prog->expected_attach_type == BPF_TRACE_ITER ?
		       &bpf_seq_म_लिखो_proto :
		       शून्य;
	हाल BPF_FUNC_seq_ग_लिखो:
		वापस prog->expected_attach_type == BPF_TRACE_ITER ?
		       &bpf_seq_ग_लिखो_proto :
		       शून्य;
	हाल BPF_FUNC_seq_म_लिखो_btf:
		वापस prog->expected_attach_type == BPF_TRACE_ITER ?
		       &bpf_seq_म_लिखो_btf_proto :
		       शून्य;
	हाल BPF_FUNC_d_path:
		वापस &bpf_d_path_proto;
	शेष:
		वापस raw_tp_prog_func_proto(func_id, prog);
	पूर्ण
पूर्ण

अटल bool raw_tp_prog_is_valid_access(पूर्णांक off, पूर्णांक size,
					क्रमागत bpf_access_type type,
					स्थिर काष्ठा bpf_prog *prog,
					काष्ठा bpf_insn_access_aux *info)
अणु
	अगर (off < 0 || off >= माप(__u64) * MAX_BPF_FUNC_ARGS)
		वापस false;
	अगर (type != BPF_READ)
		वापस false;
	अगर (off % size != 0)
		वापस false;
	वापस true;
पूर्ण

अटल bool tracing_prog_is_valid_access(पूर्णांक off, पूर्णांक size,
					 क्रमागत bpf_access_type type,
					 स्थिर काष्ठा bpf_prog *prog,
					 काष्ठा bpf_insn_access_aux *info)
अणु
	अगर (off < 0 || off >= माप(__u64) * MAX_BPF_FUNC_ARGS)
		वापस false;
	अगर (type != BPF_READ)
		वापस false;
	अगर (off % size != 0)
		वापस false;
	वापस btf_ctx_access(off, size, type, prog, info);
पूर्ण

पूर्णांक __weak bpf_prog_test_run_tracing(काष्ठा bpf_prog *prog,
				     स्थिर जोड़ bpf_attr *kattr,
				     जोड़ bpf_attr __user *uattr)
अणु
	वापस -ENOTSUPP;
पूर्ण

स्थिर काष्ठा bpf_verअगरier_ops raw_tracepoपूर्णांक_verअगरier_ops = अणु
	.get_func_proto  = raw_tp_prog_func_proto,
	.is_valid_access = raw_tp_prog_is_valid_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops raw_tracepoपूर्णांक_prog_ops = अणु
#अगर_घोषित CONFIG_NET
	.test_run = bpf_prog_test_run_raw_tp,
#पूर्ण_अगर
पूर्ण;

स्थिर काष्ठा bpf_verअगरier_ops tracing_verअगरier_ops = अणु
	.get_func_proto  = tracing_prog_func_proto,
	.is_valid_access = tracing_prog_is_valid_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops tracing_prog_ops = अणु
	.test_run = bpf_prog_test_run_tracing,
पूर्ण;

अटल bool raw_tp_writable_prog_is_valid_access(पूर्णांक off, पूर्णांक size,
						 क्रमागत bpf_access_type type,
						 स्थिर काष्ठा bpf_prog *prog,
						 काष्ठा bpf_insn_access_aux *info)
अणु
	अगर (off == 0) अणु
		अगर (size != माप(u64) || type != BPF_READ)
			वापस false;
		info->reg_type = PTR_TO_TP_BUFFER;
	पूर्ण
	वापस raw_tp_prog_is_valid_access(off, size, type, prog, info);
पूर्ण

स्थिर काष्ठा bpf_verअगरier_ops raw_tracepoपूर्णांक_writable_verअगरier_ops = अणु
	.get_func_proto  = raw_tp_prog_func_proto,
	.is_valid_access = raw_tp_writable_prog_is_valid_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops raw_tracepoपूर्णांक_writable_prog_ops = अणु
पूर्ण;

अटल bool pe_prog_is_valid_access(पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type,
				    स्थिर काष्ठा bpf_prog *prog,
				    काष्ठा bpf_insn_access_aux *info)
अणु
	स्थिर पूर्णांक size_u64 = माप(u64);

	अगर (off < 0 || off >= माप(काष्ठा bpf_perf_event_data))
		वापस false;
	अगर (type != BPF_READ)
		वापस false;
	अगर (off % size != 0) अणु
		अगर (माप(अचिन्हित दीर्घ) != 4)
			वापस false;
		अगर (size != 8)
			वापस false;
		अगर (off % size != 4)
			वापस false;
	पूर्ण

	चयन (off) अणु
	हाल bpf_ctx_range(काष्ठा bpf_perf_event_data, sample_period):
		bpf_ctx_record_field_size(info, size_u64);
		अगर (!bpf_ctx_narrow_access_ok(off, size, size_u64))
			वापस false;
		अवरोध;
	हाल bpf_ctx_range(काष्ठा bpf_perf_event_data, addr):
		bpf_ctx_record_field_size(info, size_u64);
		अगर (!bpf_ctx_narrow_access_ok(off, size, size_u64))
			वापस false;
		अवरोध;
	शेष:
		अगर (size != माप(दीर्घ))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल u32 pe_prog_convert_ctx_access(क्रमागत bpf_access_type type,
				      स्थिर काष्ठा bpf_insn *si,
				      काष्ठा bpf_insn *insn_buf,
				      काष्ठा bpf_prog *prog, u32 *target_size)
अणु
	काष्ठा bpf_insn *insn = insn_buf;

	चयन (si->off) अणु
	हाल दुरत्व(काष्ठा bpf_perf_event_data, sample_period):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_perf_event_data_kern,
						       data), si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_perf_event_data_kern, data));
		*insn++ = BPF_LDX_MEM(BPF_DW, si->dst_reg, si->dst_reg,
				      bpf_target_off(काष्ठा perf_sample_data, period, 8,
						     target_size));
		अवरोध;
	हाल दुरत्व(काष्ठा bpf_perf_event_data, addr):
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_perf_event_data_kern,
						       data), si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_perf_event_data_kern, data));
		*insn++ = BPF_LDX_MEM(BPF_DW, si->dst_reg, si->dst_reg,
				      bpf_target_off(काष्ठा perf_sample_data, addr, 8,
						     target_size));
		अवरोध;
	शेष:
		*insn++ = BPF_LDX_MEM(BPF_FIELD_SIZखातापूर्ण(काष्ठा bpf_perf_event_data_kern,
						       regs), si->dst_reg, si->src_reg,
				      दुरत्व(काष्ठा bpf_perf_event_data_kern, regs));
		*insn++ = BPF_LDX_MEM(BPF_SIZखातापूर्ण(दीर्घ), si->dst_reg, si->dst_reg,
				      si->off);
		अवरोध;
	पूर्ण

	वापस insn - insn_buf;
पूर्ण

स्थिर काष्ठा bpf_verअगरier_ops perf_event_verअगरier_ops = अणु
	.get_func_proto		= pe_prog_func_proto,
	.is_valid_access	= pe_prog_is_valid_access,
	.convert_ctx_access	= pe_prog_convert_ctx_access,
पूर्ण;

स्थिर काष्ठा bpf_prog_ops perf_event_prog_ops = अणु
पूर्ण;

अटल DEFINE_MUTEX(bpf_event_mutex);

#घोषणा BPF_TRACE_MAX_PROGS 64

पूर्णांक perf_event_attach_bpf_prog(काष्ठा perf_event *event,
			       काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog_array *old_array;
	काष्ठा bpf_prog_array *new_array;
	पूर्णांक ret = -EEXIST;

	/*
	 * Kprobe override only works अगर they are on the function entry,
	 * and only अगर they are on the opt-in list.
	 */
	अगर (prog->kprobe_override &&
	    (!trace_kprobe_on_func_entry(event->tp_event) ||
	     !trace_kprobe_error_injectable(event->tp_event)))
		वापस -EINVAL;

	mutex_lock(&bpf_event_mutex);

	अगर (event->prog)
		जाओ unlock;

	old_array = bpf_event_rcu_dereference(event->tp_event->prog_array);
	अगर (old_array &&
	    bpf_prog_array_length(old_array) >= BPF_TRACE_MAX_PROGS) अणु
		ret = -E2BIG;
		जाओ unlock;
	पूर्ण

	ret = bpf_prog_array_copy(old_array, शून्य, prog, &new_array);
	अगर (ret < 0)
		जाओ unlock;

	/* set the new array to event->tp_event and set event->prog */
	event->prog = prog;
	rcu_assign_poपूर्णांकer(event->tp_event->prog_array, new_array);
	bpf_prog_array_मुक्त(old_array);

unlock:
	mutex_unlock(&bpf_event_mutex);
	वापस ret;
पूर्ण

व्योम perf_event_detach_bpf_prog(काष्ठा perf_event *event)
अणु
	काष्ठा bpf_prog_array *old_array;
	काष्ठा bpf_prog_array *new_array;
	पूर्णांक ret;

	mutex_lock(&bpf_event_mutex);

	अगर (!event->prog)
		जाओ unlock;

	old_array = bpf_event_rcu_dereference(event->tp_event->prog_array);
	ret = bpf_prog_array_copy(old_array, event->prog, शून्य, &new_array);
	अगर (ret == -ENOENT)
		जाओ unlock;
	अगर (ret < 0) अणु
		bpf_prog_array_delete_safe(old_array, event->prog);
	पूर्ण अन्यथा अणु
		rcu_assign_poपूर्णांकer(event->tp_event->prog_array, new_array);
		bpf_prog_array_मुक्त(old_array);
	पूर्ण

	bpf_prog_put(event->prog);
	event->prog = शून्य;

unlock:
	mutex_unlock(&bpf_event_mutex);
पूर्ण

पूर्णांक perf_event_query_prog_array(काष्ठा perf_event *event, व्योम __user *info)
अणु
	काष्ठा perf_event_query_bpf __user *uquery = info;
	काष्ठा perf_event_query_bpf query = अणुपूर्ण;
	काष्ठा bpf_prog_array *progs;
	u32 *ids, prog_cnt, ids_len;
	पूर्णांक ret;

	अगर (!perfmon_capable())
		वापस -EPERM;
	अगर (event->attr.type != PERF_TYPE_TRACEPOINT)
		वापस -EINVAL;
	अगर (copy_from_user(&query, uquery, माप(query)))
		वापस -EFAULT;

	ids_len = query.ids_len;
	अगर (ids_len > BPF_TRACE_MAX_PROGS)
		वापस -E2BIG;
	ids = kसुस्मृति(ids_len, माप(u32), GFP_USER | __GFP_NOWARN);
	अगर (!ids)
		वापस -ENOMEM;
	/*
	 * The above kसुस्मृति वापसs ZERO_SIZE_PTR when ids_len = 0, which
	 * is required when user only wants to check क्रम uquery->prog_cnt.
	 * There is no need to check क्रम it since the हाल is handled
	 * gracefully in bpf_prog_array_copy_info.
	 */

	mutex_lock(&bpf_event_mutex);
	progs = bpf_event_rcu_dereference(event->tp_event->prog_array);
	ret = bpf_prog_array_copy_info(progs, ids, ids_len, &prog_cnt);
	mutex_unlock(&bpf_event_mutex);

	अगर (copy_to_user(&uquery->prog_cnt, &prog_cnt, माप(prog_cnt)) ||
	    copy_to_user(uquery->ids, ids, ids_len * माप(u32)))
		ret = -EFAULT;

	kमुक्त(ids);
	वापस ret;
पूर्ण

बाह्य काष्ठा bpf_raw_event_map __start__bpf_raw_tp[];
बाह्य काष्ठा bpf_raw_event_map __stop__bpf_raw_tp[];

काष्ठा bpf_raw_event_map *bpf_get_raw_tracepoपूर्णांक(स्थिर अक्षर *name)
अणु
	काष्ठा bpf_raw_event_map *btp = __start__bpf_raw_tp;

	क्रम (; btp < __stop__bpf_raw_tp; btp++) अणु
		अगर (!म_भेद(btp->tp->name, name))
			वापस btp;
	पूर्ण

	वापस bpf_get_raw_tracepoपूर्णांक_module(name);
पूर्ण

व्योम bpf_put_raw_tracepoपूर्णांक(काष्ठा bpf_raw_event_map *btp)
अणु
	काष्ठा module *mod;

	preempt_disable();
	mod = __module_address((अचिन्हित दीर्घ)btp);
	module_put(mod);
	preempt_enable();
पूर्ण

अटल __always_अंतरभूत
व्योम __bpf_trace_run(काष्ठा bpf_prog *prog, u64 *args)
अणु
	cant_sleep();
	rcu_पढ़ो_lock();
	(व्योम) BPF_PROG_RUN(prog, args);
	rcu_पढ़ो_unlock();
पूर्ण

#घोषणा UNPACK(...)			__VA_ARGS__
#घोषणा REPEAT_1(FN, DL, X, ...)	FN(X)
#घोषणा REPEAT_2(FN, DL, X, ...)	FN(X) UNPACK DL REPEAT_1(FN, DL, __VA_ARGS__)
#घोषणा REPEAT_3(FN, DL, X, ...)	FN(X) UNPACK DL REPEAT_2(FN, DL, __VA_ARGS__)
#घोषणा REPEAT_4(FN, DL, X, ...)	FN(X) UNPACK DL REPEAT_3(FN, DL, __VA_ARGS__)
#घोषणा REPEAT_5(FN, DL, X, ...)	FN(X) UNPACK DL REPEAT_4(FN, DL, __VA_ARGS__)
#घोषणा REPEAT_6(FN, DL, X, ...)	FN(X) UNPACK DL REPEAT_5(FN, DL, __VA_ARGS__)
#घोषणा REPEAT_7(FN, DL, X, ...)	FN(X) UNPACK DL REPEAT_6(FN, DL, __VA_ARGS__)
#घोषणा REPEAT_8(FN, DL, X, ...)	FN(X) UNPACK DL REPEAT_7(FN, DL, __VA_ARGS__)
#घोषणा REPEAT_9(FN, DL, X, ...)	FN(X) UNPACK DL REPEAT_8(FN, DL, __VA_ARGS__)
#घोषणा REPEAT_10(FN, DL, X, ...)	FN(X) UNPACK DL REPEAT_9(FN, DL, __VA_ARGS__)
#घोषणा REPEAT_11(FN, DL, X, ...)	FN(X) UNPACK DL REPEAT_10(FN, DL, __VA_ARGS__)
#घोषणा REPEAT_12(FN, DL, X, ...)	FN(X) UNPACK DL REPEAT_11(FN, DL, __VA_ARGS__)
#घोषणा REPEAT(X, FN, DL, ...)		REPEAT_##X(FN, DL, __VA_ARGS__)

#घोषणा SARG(X)		u64 arg##X
#घोषणा COPY(X)		args[X] = arg##X

#घोषणा __DL_COM	(,)
#घोषणा __DL_SEM	(;)

#घोषणा __SEQ_0_11	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11

#घोषणा BPF_TRACE_DEFN_x(x)						\
	व्योम bpf_trace_run##x(काष्ठा bpf_prog *prog,			\
			      REPEAT(x, SARG, __DL_COM, __SEQ_0_11))	\
	अणु								\
		u64 args[x];						\
		REPEAT(x, COPY, __DL_SEM, __SEQ_0_11);			\
		__bpf_trace_run(prog, args);				\
	पूर्ण								\
	EXPORT_SYMBOL_GPL(bpf_trace_run##x)
BPF_TRACE_DEFN_x(1);
BPF_TRACE_DEFN_x(2);
BPF_TRACE_DEFN_x(3);
BPF_TRACE_DEFN_x(4);
BPF_TRACE_DEFN_x(5);
BPF_TRACE_DEFN_x(6);
BPF_TRACE_DEFN_x(7);
BPF_TRACE_DEFN_x(8);
BPF_TRACE_DEFN_x(9);
BPF_TRACE_DEFN_x(10);
BPF_TRACE_DEFN_x(11);
BPF_TRACE_DEFN_x(12);

अटल पूर्णांक __bpf_probe_रेजिस्टर(काष्ठा bpf_raw_event_map *btp, काष्ठा bpf_prog *prog)
अणु
	काष्ठा tracepoपूर्णांक *tp = btp->tp;

	/*
	 * check that program करोesn't access arguments beyond what's
	 * available in this tracepoपूर्णांक
	 */
	अगर (prog->aux->max_ctx_offset > btp->num_args * माप(u64))
		वापस -EINVAL;

	अगर (prog->aux->max_tp_access > btp->writable_size)
		वापस -EINVAL;

	वापस tracepoपूर्णांक_probe_रेजिस्टर(tp, (व्योम *)btp->bpf_func, prog);
पूर्ण

पूर्णांक bpf_probe_रेजिस्टर(काष्ठा bpf_raw_event_map *btp, काष्ठा bpf_prog *prog)
अणु
	वापस __bpf_probe_रेजिस्टर(btp, prog);
पूर्ण

पूर्णांक bpf_probe_unरेजिस्टर(काष्ठा bpf_raw_event_map *btp, काष्ठा bpf_prog *prog)
अणु
	वापस tracepoपूर्णांक_probe_unरेजिस्टर(btp->tp, (व्योम *)btp->bpf_func, prog);
पूर्ण

पूर्णांक bpf_get_perf_event_info(स्थिर काष्ठा perf_event *event, u32 *prog_id,
			    u32 *fd_type, स्थिर अक्षर **buf,
			    u64 *probe_offset, u64 *probe_addr)
अणु
	bool is_tracepoपूर्णांक, is_syscall_tp;
	काष्ठा bpf_prog *prog;
	पूर्णांक flags, err = 0;

	prog = event->prog;
	अगर (!prog)
		वापस -ENOENT;

	/* not supporting BPF_PROG_TYPE_PERF_EVENT yet */
	अगर (prog->type == BPF_PROG_TYPE_PERF_EVENT)
		वापस -EOPNOTSUPP;

	*prog_id = prog->aux->id;
	flags = event->tp_event->flags;
	is_tracepoपूर्णांक = flags & TRACE_EVENT_FL_TRACEPOINT;
	is_syscall_tp = is_syscall_trace_event(event->tp_event);

	अगर (is_tracepoपूर्णांक || is_syscall_tp) अणु
		*buf = is_tracepoपूर्णांक ? event->tp_event->tp->name
				     : event->tp_event->name;
		*fd_type = BPF_FD_TYPE_TRACEPOINT;
		*probe_offset = 0x0;
		*probe_addr = 0x0;
	पूर्ण अन्यथा अणु
		/* kprobe/uprobe */
		err = -EOPNOTSUPP;
#अगर_घोषित CONFIG_KPROBE_EVENTS
		अगर (flags & TRACE_EVENT_FL_KPROBE)
			err = bpf_get_kprobe_info(event, fd_type, buf,
						  probe_offset, probe_addr,
						  event->attr.type == PERF_TYPE_TRACEPOINT);
#पूर्ण_अगर
#अगर_घोषित CONFIG_UPROBE_EVENTS
		अगर (flags & TRACE_EVENT_FL_UPROBE)
			err = bpf_get_uprobe_info(event, fd_type, buf,
						  probe_offset,
						  event->attr.type == PERF_TYPE_TRACEPOINT);
#पूर्ण_अगर
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __init send_संकेत_irq_work_init(व्योम)
अणु
	पूर्णांक cpu;
	काष्ठा send_संकेत_irq_work *work;

	क्रम_each_possible_cpu(cpu) अणु
		work = per_cpu_ptr(&send_संकेत_work, cpu);
		init_irq_work(&work->irq_work, करो_bpf_send_संकेत);
	पूर्ण
	वापस 0;
पूर्ण

subsys_initcall(send_संकेत_irq_work_init);

#अगर_घोषित CONFIG_MODULES
अटल पूर्णांक bpf_event_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ op,
			    व्योम *module)
अणु
	काष्ठा bpf_trace_module *bपंचांग, *पंचांगp;
	काष्ठा module *mod = module;
	पूर्णांक ret = 0;

	अगर (mod->num_bpf_raw_events == 0 ||
	    (op != MODULE_STATE_COMING && op != MODULE_STATE_GOING))
		जाओ out;

	mutex_lock(&bpf_module_mutex);

	चयन (op) अणु
	हाल MODULE_STATE_COMING:
		bपंचांग = kzalloc(माप(*bपंचांग), GFP_KERNEL);
		अगर (bपंचांग) अणु
			bपंचांग->module = module;
			list_add(&bपंचांग->list, &bpf_trace_modules);
		पूर्ण अन्यथा अणु
			ret = -ENOMEM;
		पूर्ण
		अवरोध;
	हाल MODULE_STATE_GOING:
		list_क्रम_each_entry_safe(bपंचांग, पंचांगp, &bpf_trace_modules, list) अणु
			अगर (bपंचांग->module == module) अणु
				list_del(&bपंचांग->list);
				kमुक्त(bपंचांग);
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	mutex_unlock(&bpf_module_mutex);

out:
	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

अटल काष्ठा notअगरier_block bpf_module_nb = अणु
	.notअगरier_call = bpf_event_notअगरy,
पूर्ण;

अटल पूर्णांक __init bpf_event_init(व्योम)
अणु
	रेजिस्टर_module_notअगरier(&bpf_module_nb);
	वापस 0;
पूर्ण

fs_initcall(bpf_event_init);
#पूर्ण_अगर /* CONFIG_MODULES */
