<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2011-2014 PLUMgrid, http://plumgrid.com
 */
#समावेश <linux/bpf.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/smp.h>
#समावेश <linux/topology.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/sched.h>
#समावेश <linux/uidgid.h>
#समावेश <linux/filter.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/security.h>

#समावेश "../../lib/kstrtox.h"

/* If kernel subप्रणाली is allowing eBPF programs to call this function,
 * inside its own verअगरier_ops->get_func_proto() callback it should वापस
 * bpf_map_lookup_elem_proto, so that verअगरier can properly check the arguments
 *
 * Dअगरferent map implementations will rely on rcu in map methods
 * lookup/update/delete, thereक्रमe eBPF programs must run under rcu lock
 * अगर program is allowed to access maps, so check rcu_पढ़ो_lock_held in
 * all three functions.
 */
BPF_CALL_2(bpf_map_lookup_elem, काष्ठा bpf_map *, map, व्योम *, key)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	वापस (अचिन्हित दीर्घ) map->ops->map_lookup_elem(map, key);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_map_lookup_elem_proto = अणु
	.func		= bpf_map_lookup_elem,
	.gpl_only	= false,
	.pkt_access	= true,
	.ret_type	= RET_PTR_TO_MAP_VALUE_OR_शून्य,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_MAP_KEY,
पूर्ण;

BPF_CALL_4(bpf_map_update_elem, काष्ठा bpf_map *, map, व्योम *, key,
	   व्योम *, value, u64, flags)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	वापस map->ops->map_update_elem(map, key, value, flags);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_map_update_elem_proto = अणु
	.func		= bpf_map_update_elem,
	.gpl_only	= false,
	.pkt_access	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_MAP_KEY,
	.arg3_type	= ARG_PTR_TO_MAP_VALUE,
	.arg4_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_map_delete_elem, काष्ठा bpf_map *, map, व्योम *, key)
अणु
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	वापस map->ops->map_delete_elem(map, key);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_map_delete_elem_proto = अणु
	.func		= bpf_map_delete_elem,
	.gpl_only	= false,
	.pkt_access	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_MAP_KEY,
पूर्ण;

BPF_CALL_3(bpf_map_push_elem, काष्ठा bpf_map *, map, व्योम *, value, u64, flags)
अणु
	वापस map->ops->map_push_elem(map, value, flags);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_map_push_elem_proto = अणु
	.func		= bpf_map_push_elem,
	.gpl_only	= false,
	.pkt_access	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_MAP_VALUE,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_map_pop_elem, काष्ठा bpf_map *, map, व्योम *, value)
अणु
	वापस map->ops->map_pop_elem(map, value);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_map_pop_elem_proto = अणु
	.func		= bpf_map_pop_elem,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_UNINIT_MAP_VALUE,
पूर्ण;

BPF_CALL_2(bpf_map_peek_elem, काष्ठा bpf_map *, map, व्योम *, value)
अणु
	वापस map->ops->map_peek_elem(map, value);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_map_peek_elem_proto = अणु
	.func		= bpf_map_peek_elem,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_PTR_TO_UNINIT_MAP_VALUE,
पूर्ण;

स्थिर काष्ठा bpf_func_proto bpf_get_pअक्रमom_u32_proto = अणु
	.func		= bpf_user_rnd_u32,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
पूर्ण;

BPF_CALL_0(bpf_get_smp_processor_id)
अणु
	वापस smp_processor_id();
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_smp_processor_id_proto = अणु
	.func		= bpf_get_smp_processor_id,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
पूर्ण;

BPF_CALL_0(bpf_get_numa_node_id)
अणु
	वापस numa_node_id();
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_numa_node_id_proto = अणु
	.func		= bpf_get_numa_node_id,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
पूर्ण;

BPF_CALL_0(bpf_kसमय_get_ns)
अणु
	/* NMI safe access to घड़ी monotonic */
	वापस kसमय_get_mono_fast_ns();
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_kसमय_get_ns_proto = अणु
	.func		= bpf_kसमय_get_ns,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
पूर्ण;

BPF_CALL_0(bpf_kसमय_get_boot_ns)
अणु
	/* NMI safe access to घड़ी bootसमय */
	वापस kसमय_get_boot_fast_ns();
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_kसमय_get_boot_ns_proto = अणु
	.func		= bpf_kसमय_get_boot_ns,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
पूर्ण;

BPF_CALL_0(bpf_kसमय_get_coarse_ns)
अणु
	वापस kसमय_get_coarse_ns();
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_kसमय_get_coarse_ns_proto = अणु
	.func		= bpf_kसमय_get_coarse_ns,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
पूर्ण;

BPF_CALL_0(bpf_get_current_pid_tgid)
अणु
	काष्ठा task_काष्ठा *task = current;

	अगर (unlikely(!task))
		वापस -EINVAL;

	वापस (u64) task->tgid << 32 | task->pid;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_current_pid_tgid_proto = अणु
	.func		= bpf_get_current_pid_tgid,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
पूर्ण;

BPF_CALL_0(bpf_get_current_uid_gid)
अणु
	काष्ठा task_काष्ठा *task = current;
	kuid_t uid;
	kgid_t gid;

	अगर (unlikely(!task))
		वापस -EINVAL;

	current_uid_gid(&uid, &gid);
	वापस (u64) from_kgid(&init_user_ns, gid) << 32 |
		     from_kuid(&init_user_ns, uid);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_current_uid_gid_proto = अणु
	.func		= bpf_get_current_uid_gid,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
पूर्ण;

BPF_CALL_2(bpf_get_current_comm, अक्षर *, buf, u32, size)
अणु
	काष्ठा task_काष्ठा *task = current;

	अगर (unlikely(!task))
		जाओ err_clear;

	म_नकलन(buf, task->comm, size);

	/* Verअगरier guarantees that size > 0. For task->comm exceeding
	 * size, guarantee that buf is %NUL-terminated. Unconditionally
	 * करोne here to save the size test.
	 */
	buf[size - 1] = 0;
	वापस 0;
err_clear:
	स_रखो(buf, 0, size);
	वापस -EINVAL;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_current_comm_proto = अणु
	.func		= bpf_get_current_comm,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg2_type	= ARG_CONST_SIZE,
पूर्ण;

#अगर defined(CONFIG_QUEUED_SPINLOCKS) || defined(CONFIG_BPF_ARCH_SPINLOCK)

अटल अंतरभूत व्योम __bpf_spin_lock(काष्ठा bpf_spin_lock *lock)
अणु
	arch_spinlock_t *l = (व्योम *)lock;
	जोड़ अणु
		__u32 val;
		arch_spinlock_t lock;
	पूर्ण u = अणु .lock = __ARCH_SPIN_LOCK_UNLOCKED पूर्ण;

	compileसमय_निश्चित(u.val == 0, "__ARCH_SPIN_LOCK_UNLOCKED not 0");
	BUILD_BUG_ON(माप(*l) != माप(__u32));
	BUILD_BUG_ON(माप(*lock) != माप(__u32));
	arch_spin_lock(l);
पूर्ण

अटल अंतरभूत व्योम __bpf_spin_unlock(काष्ठा bpf_spin_lock *lock)
अणु
	arch_spinlock_t *l = (व्योम *)lock;

	arch_spin_unlock(l);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम __bpf_spin_lock(काष्ठा bpf_spin_lock *lock)
अणु
	atomic_t *l = (व्योम *)lock;

	BUILD_BUG_ON(माप(*l) != माप(*lock));
	करो अणु
		atomic_cond_पढ़ो_relaxed(l, !VAL);
	पूर्ण जबतक (atomic_xchg(l, 1));
पूर्ण

अटल अंतरभूत व्योम __bpf_spin_unlock(काष्ठा bpf_spin_lock *lock)
अणु
	atomic_t *l = (व्योम *)lock;

	atomic_set_release(l, 0);
पूर्ण

#पूर्ण_अगर

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, irqsave_flags);

notrace BPF_CALL_1(bpf_spin_lock, काष्ठा bpf_spin_lock *, lock)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	__bpf_spin_lock(lock);
	__this_cpu_ग_लिखो(irqsave_flags, flags);
	वापस 0;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_spin_lock_proto = अणु
	.func		= bpf_spin_lock,
	.gpl_only	= false,
	.ret_type	= RET_VOID,
	.arg1_type	= ARG_PTR_TO_SPIN_LOCK,
पूर्ण;

notrace BPF_CALL_1(bpf_spin_unlock, काष्ठा bpf_spin_lock *, lock)
अणु
	अचिन्हित दीर्घ flags;

	flags = __this_cpu_पढ़ो(irqsave_flags);
	__bpf_spin_unlock(lock);
	local_irq_restore(flags);
	वापस 0;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_spin_unlock_proto = अणु
	.func		= bpf_spin_unlock,
	.gpl_only	= false,
	.ret_type	= RET_VOID,
	.arg1_type	= ARG_PTR_TO_SPIN_LOCK,
पूर्ण;

व्योम copy_map_value_locked(काष्ठा bpf_map *map, व्योम *dst, व्योम *src,
			   bool lock_src)
अणु
	काष्ठा bpf_spin_lock *lock;

	अगर (lock_src)
		lock = src + map->spin_lock_off;
	अन्यथा
		lock = dst + map->spin_lock_off;
	preempt_disable();
	____bpf_spin_lock(lock);
	copy_map_value(map, dst, src);
	____bpf_spin_unlock(lock);
	preempt_enable();
पूर्ण

BPF_CALL_0(bpf_jअगरfies64)
अणु
	वापस get_jअगरfies_64();
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_jअगरfies64_proto = अणु
	.func		= bpf_jअगरfies64,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
पूर्ण;

#अगर_घोषित CONFIG_CGROUPS
BPF_CALL_0(bpf_get_current_cgroup_id)
अणु
	काष्ठा cgroup *cgrp = task_dfl_cgroup(current);

	वापस cgroup_id(cgrp);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_current_cgroup_id_proto = अणु
	.func		= bpf_get_current_cgroup_id,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
पूर्ण;

BPF_CALL_1(bpf_get_current_ancestor_cgroup_id, पूर्णांक, ancestor_level)
अणु
	काष्ठा cgroup *cgrp = task_dfl_cgroup(current);
	काष्ठा cgroup *ancestor;

	ancestor = cgroup_ancestor(cgrp, ancestor_level);
	अगर (!ancestor)
		वापस 0;
	वापस cgroup_id(ancestor);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_current_ancestor_cgroup_id_proto = अणु
	.func		= bpf_get_current_ancestor_cgroup_id,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_ANYTHING,
पूर्ण;

#अगर_घोषित CONFIG_CGROUP_BPF
DECLARE_PER_CPU(काष्ठा bpf_cgroup_storage_info,
		bpf_cgroup_storage_info[BPF_CGROUP_STORAGE_NEST_MAX]);

BPF_CALL_2(bpf_get_local_storage, काष्ठा bpf_map *, map, u64, flags)
अणु
	/* flags argument is not used now,
	 * but provides an ability to extend the API.
	 * verअगरier checks that its value is correct.
	 */
	क्रमागत bpf_cgroup_storage_type stype = cgroup_storage_type(map);
	काष्ठा bpf_cgroup_storage *storage = शून्य;
	व्योम *ptr;
	पूर्णांक i;

	क्रम (i = 0; i < BPF_CGROUP_STORAGE_NEST_MAX; i++) अणु
		अगर (unlikely(this_cpu_पढ़ो(bpf_cgroup_storage_info[i].task) != current))
			जारी;

		storage = this_cpu_पढ़ो(bpf_cgroup_storage_info[i].storage[stype]);
		अवरोध;
	पूर्ण

	अगर (stype == BPF_CGROUP_STORAGE_SHARED)
		ptr = &READ_ONCE(storage->buf)->data[0];
	अन्यथा
		ptr = this_cpu_ptr(storage->percpu_buf);

	वापस (अचिन्हित दीर्घ)ptr;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_local_storage_proto = अणु
	.func		= bpf_get_local_storage,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_MAP_VALUE,
	.arg1_type	= ARG_CONST_MAP_PTR,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;
#पूर्ण_अगर

#घोषणा BPF_STRTOX_BASE_MASK 0x1F

अटल पूर्णांक __bpf_म_से_अदीर्घl(स्थिर अक्षर *buf, माप_प्रकार buf_len, u64 flags,
			  अचिन्हित दीर्घ दीर्घ *res, bool *is_negative)
अणु
	अचिन्हित पूर्णांक base = flags & BPF_STRTOX_BASE_MASK;
	स्थिर अक्षर *cur_buf = buf;
	माप_प्रकार cur_len = buf_len;
	अचिन्हित पूर्णांक consumed;
	माप_प्रकार val_len;
	अक्षर str[64];

	अगर (!buf || !buf_len || !res || !is_negative)
		वापस -EINVAL;

	अगर (base != 0 && base != 8 && base != 10 && base != 16)
		वापस -EINVAL;

	अगर (flags & ~BPF_STRTOX_BASE_MASK)
		वापस -EINVAL;

	जबतक (cur_buf < buf + buf_len && है_खाली(*cur_buf))
		++cur_buf;

	*is_negative = (cur_buf < buf + buf_len && *cur_buf == '-');
	अगर (*is_negative)
		++cur_buf;

	consumed = cur_buf - buf;
	cur_len -= consumed;
	अगर (!cur_len)
		वापस -EINVAL;

	cur_len = min(cur_len, माप(str) - 1);
	स_नकल(str, cur_buf, cur_len);
	str[cur_len] = '\0';
	cur_buf = str;

	cur_buf = _parse_पूर्णांकeger_fixup_radix(cur_buf, &base);
	val_len = _parse_पूर्णांकeger(cur_buf, base, res);

	अगर (val_len & KSTRTOX_OVERFLOW)
		वापस -दुस्फल;

	अगर (val_len == 0)
		वापस -EINVAL;

	cur_buf += val_len;
	consumed += cur_buf - str;

	वापस consumed;
पूर्ण

अटल पूर्णांक __bpf_म_से_दीर्घl(स्थिर अक्षर *buf, माप_प्रकार buf_len, u64 flags,
			 दीर्घ दीर्घ *res)
अणु
	अचिन्हित दीर्घ दीर्घ _res;
	bool is_negative;
	पूर्णांक err;

	err = __bpf_म_से_अदीर्घl(buf, buf_len, flags, &_res, &is_negative);
	अगर (err < 0)
		वापस err;
	अगर (is_negative) अणु
		अगर ((दीर्घ दीर्घ)-_res > 0)
			वापस -दुस्फल;
		*res = -_res;
	पूर्ण अन्यथा अणु
		अगर ((दीर्घ दीर्घ)_res < 0)
			वापस -दुस्फल;
		*res = _res;
	पूर्ण
	वापस err;
पूर्ण

BPF_CALL_4(bpf_म_से_दीर्घ, स्थिर अक्षर *, buf, माप_प्रकार, buf_len, u64, flags,
	   दीर्घ *, res)
अणु
	दीर्घ दीर्घ _res;
	पूर्णांक err;

	err = __bpf_म_से_दीर्घl(buf, buf_len, flags, &_res);
	अगर (err < 0)
		वापस err;
	अगर (_res != (दीर्घ)_res)
		वापस -दुस्फल;
	*res = _res;
	वापस err;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_म_से_दीर्घ_proto = अणु
	.func		= bpf_म_से_दीर्घ,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_MEM,
	.arg2_type	= ARG_CONST_SIZE,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_PTR_TO_LONG,
पूर्ण;

BPF_CALL_4(bpf_म_से_अदीर्घ, स्थिर अक्षर *, buf, माप_प्रकार, buf_len, u64, flags,
	   अचिन्हित दीर्घ *, res)
अणु
	अचिन्हित दीर्घ दीर्घ _res;
	bool is_negative;
	पूर्णांक err;

	err = __bpf_म_से_अदीर्घl(buf, buf_len, flags, &_res, &is_negative);
	अगर (err < 0)
		वापस err;
	अगर (is_negative)
		वापस -EINVAL;
	अगर (_res != (अचिन्हित दीर्घ)_res)
		वापस -दुस्फल;
	*res = _res;
	वापस err;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_म_से_अदीर्घ_proto = अणु
	.func		= bpf_म_से_अदीर्घ,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_MEM,
	.arg2_type	= ARG_CONST_SIZE,
	.arg3_type	= ARG_ANYTHING,
	.arg4_type	= ARG_PTR_TO_LONG,
पूर्ण;
#पूर्ण_अगर

BPF_CALL_4(bpf_get_ns_current_pid_tgid, u64, dev, u64, ino,
	   काष्ठा bpf_pidns_info *, nsdata, u32, size)
अणु
	काष्ठा task_काष्ठा *task = current;
	काष्ठा pid_namespace *pidns;
	पूर्णांक err = -EINVAL;

	अगर (unlikely(size != माप(काष्ठा bpf_pidns_info)))
		जाओ clear;

	अगर (unlikely((u64)(dev_t)dev != dev))
		जाओ clear;

	अगर (unlikely(!task))
		जाओ clear;

	pidns = task_active_pid_ns(task);
	अगर (unlikely(!pidns)) अणु
		err = -ENOENT;
		जाओ clear;
	पूर्ण

	अगर (!ns_match(&pidns->ns, (dev_t)dev, ino))
		जाओ clear;

	nsdata->pid = task_pid_nr_ns(task, pidns);
	nsdata->tgid = task_tgid_nr_ns(task, pidns);
	वापस 0;
clear:
	स_रखो((व्योम *)nsdata, 0, (माप_प्रकार) size);
	वापस err;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_get_ns_current_pid_tgid_proto = अणु
	.func		= bpf_get_ns_current_pid_tgid,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_ANYTHING,
	.arg2_type	= ARG_ANYTHING,
	.arg3_type      = ARG_PTR_TO_UNINIT_MEM,
	.arg4_type      = ARG_CONST_SIZE,
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto bpf_get_raw_smp_processor_id_proto = अणु
	.func		= bpf_get_raw_cpu_id,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
पूर्ण;

BPF_CALL_5(bpf_event_output_data, व्योम *, ctx, काष्ठा bpf_map *, map,
	   u64, flags, व्योम *, data, u64, size)
अणु
	अगर (unlikely(flags & ~(BPF_F_INDEX_MASK)))
		वापस -EINVAL;

	वापस bpf_event_output(map, flags, data, size, शून्य, 0, शून्य);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_event_output_data_proto =  अणु
	.func		= bpf_event_output_data,
	.gpl_only       = true,
	.ret_type       = RET_INTEGER,
	.arg1_type      = ARG_PTR_TO_CTX,
	.arg2_type      = ARG_CONST_MAP_PTR,
	.arg3_type      = ARG_ANYTHING,
	.arg4_type      = ARG_PTR_TO_MEM,
	.arg5_type      = ARG_CONST_SIZE_OR_ZERO,
पूर्ण;

BPF_CALL_3(bpf_copy_from_user, व्योम *, dst, u32, size,
	   स्थिर व्योम __user *, user_ptr)
अणु
	पूर्णांक ret = copy_from_user(dst, user_ptr, size);

	अगर (unlikely(ret)) अणु
		स_रखो(dst, 0, size);
		ret = -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_copy_from_user_proto = अणु
	.func		= bpf_copy_from_user,
	.gpl_only	= false,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_UNINIT_MEM,
	.arg2_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg3_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_2(bpf_per_cpu_ptr, स्थिर व्योम *, ptr, u32, cpu)
अणु
	अगर (cpu >= nr_cpu_ids)
		वापस (अचिन्हित दीर्घ)शून्य;

	वापस (अचिन्हित दीर्घ)per_cpu_ptr((स्थिर व्योम __percpu *)ptr, cpu);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_per_cpu_ptr_proto = अणु
	.func		= bpf_per_cpu_ptr,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_MEM_OR_BTF_ID_OR_शून्य,
	.arg1_type	= ARG_PTR_TO_PERCPU_BTF_ID,
	.arg2_type	= ARG_ANYTHING,
पूर्ण;

BPF_CALL_1(bpf_this_cpu_ptr, स्थिर व्योम *, percpu_ptr)
अणु
	वापस (अचिन्हित दीर्घ)this_cpu_ptr((स्थिर व्योम __percpu *)percpu_ptr);
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_this_cpu_ptr_proto = अणु
	.func		= bpf_this_cpu_ptr,
	.gpl_only	= false,
	.ret_type	= RET_PTR_TO_MEM_OR_BTF_ID,
	.arg1_type	= ARG_PTR_TO_PERCPU_BTF_ID,
पूर्ण;

अटल पूर्णांक bpf_trace_copy_string(अक्षर *buf, व्योम *unsafe_ptr, अक्षर fmt_ptype,
		माप_प्रकार bufsz)
अणु
	व्योम __user *user_ptr = (__क्रमce व्योम __user *)unsafe_ptr;

	buf[0] = 0;

	चयन (fmt_ptype) अणु
	हाल 's':
#अगर_घोषित CONFIG_ARCH_HAS_NON_OVERLAPPING_ADDRESS_SPACE
		अगर ((अचिन्हित दीर्घ)unsafe_ptr < TASK_SIZE)
			वापस म_नकलन_from_user_nofault(buf, user_ptr, bufsz);
		fallthrough;
#पूर्ण_अगर
	हाल 'k':
		वापस म_नकलन_from_kernel_nofault(buf, unsafe_ptr, bufsz);
	हाल 'u':
		वापस म_नकलन_from_user_nofault(buf, user_ptr, bufsz);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* Per-cpu temp buffers used by म_लिखो-like helpers to store the bम_लिखो binary
 * arguments representation.
 */
#घोषणा MAX_BPRINTF_BUF_LEN	512

/* Support executing three nested bम_लिखो helper calls on a given CPU */
#घोषणा MAX_BPRINTF_NEST_LEVEL	3
काष्ठा bpf_bम_लिखो_buffers अणु
	अक्षर पंचांगp_bufs[MAX_BPRINTF_NEST_LEVEL][MAX_BPRINTF_BUF_LEN];
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा bpf_bम_लिखो_buffers, bpf_bम_लिखो_bufs);
अटल DEFINE_PER_CPU(पूर्णांक, bpf_bम_लिखो_nest_level);

अटल पूर्णांक try_get_fmt_पंचांगp_buf(अक्षर **पंचांगp_buf)
अणु
	काष्ठा bpf_bम_लिखो_buffers *bufs;
	पूर्णांक nest_level;

	preempt_disable();
	nest_level = this_cpu_inc_वापस(bpf_bम_लिखो_nest_level);
	अगर (WARN_ON_ONCE(nest_level > MAX_BPRINTF_NEST_LEVEL)) अणु
		this_cpu_dec(bpf_bम_लिखो_nest_level);
		preempt_enable();
		वापस -EBUSY;
	पूर्ण
	bufs = this_cpu_ptr(&bpf_bम_लिखो_bufs);
	*पंचांगp_buf = bufs->पंचांगp_bufs[nest_level - 1];

	वापस 0;
पूर्ण

व्योम bpf_bम_लिखो_cleanup(व्योम)
अणु
	अगर (this_cpu_पढ़ो(bpf_bम_लिखो_nest_level)) अणु
		this_cpu_dec(bpf_bम_लिखो_nest_level);
		preempt_enable();
	पूर्ण
पूर्ण

/*
 * bpf_bम_लिखो_prepare - Generic pass on क्रमmat strings क्रम bम_लिखो-like helpers
 *
 * Returns a negative value अगर fmt is an invalid क्रमmat string or 0 otherwise.
 *
 * This can be used in two ways:
 * - Format string verअगरication only: when bin_args is शून्य
 * - Arguments preparation: in addition to the above verअगरication, it ग_लिखोs in
 *   bin_args a binary representation of arguments usable by bstr_म_लिखो where
 *   poपूर्णांकers from BPF have been sanitized.
 *
 * In argument preparation mode, अगर 0 is वापसed, safe temporary buffers are
 * allocated and bpf_bम_लिखो_cleanup should be called to मुक्त them after use.
 */
पूर्णांक bpf_bम_लिखो_prepare(अक्षर *fmt, u32 fmt_size, स्थिर u64 *raw_args,
			u32 **bin_args, u32 num_args)
अणु
	अक्षर *unsafe_ptr = शून्य, *पंचांगp_buf = शून्य, *पंचांगp_buf_end, *fmt_end;
	माप_प्रकार माप_cur_arg, माप_cur_ip;
	पूर्णांक err, i, num_spec = 0;
	u64 cur_arg;
	अक्षर fmt_ptype, cur_ip[16], ip_spec[] = "%pXX";

	fmt_end = strnchr(fmt, fmt_size, 0);
	अगर (!fmt_end)
		वापस -EINVAL;
	fmt_size = fmt_end - fmt;

	अगर (bin_args) अणु
		अगर (num_args && try_get_fmt_पंचांगp_buf(&पंचांगp_buf))
			वापस -EBUSY;

		पंचांगp_buf_end = पंचांगp_buf + MAX_BPRINTF_BUF_LEN;
		*bin_args = (u32 *)पंचांगp_buf;
	पूर्ण

	क्रम (i = 0; i < fmt_size; i++) अणु
		अगर ((!है_छाप(fmt[i]) && !है_खाली(fmt[i])) || !isascii(fmt[i])) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (fmt[i] != '%')
			जारी;

		अगर (fmt[i + 1] == '%') अणु
			i++;
			जारी;
		पूर्ण

		अगर (num_spec >= num_args) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		/* The string is zero-terminated so अगर fmt[i] != 0, we can
		 * always access fmt[i + 1], in the worst हाल it will be a 0
		 */
		i++;

		/* skip optional "[0 +-][num]" width क्रमmatting field */
		जबतक (fmt[i] == '0' || fmt[i] == '+'  || fmt[i] == '-' ||
		       fmt[i] == ' ')
			i++;
		अगर (fmt[i] >= '1' && fmt[i] <= '9') अणु
			i++;
			जबतक (fmt[i] >= '0' && fmt[i] <= '9')
				i++;
		पूर्ण

		अगर (fmt[i] == 'p') अणु
			माप_cur_arg = माप(दीर्घ);

			अगर ((fmt[i + 1] == 'k' || fmt[i + 1] == 'u') &&
			    fmt[i + 2] == 's') अणु
				fmt_ptype = fmt[i + 1];
				i += 2;
				जाओ fmt_str;
			पूर्ण

			अगर (fmt[i + 1] == 0 || है_खाली(fmt[i + 1]) ||
			    है_विराम(fmt[i + 1]) || fmt[i + 1] == 'K' ||
			    fmt[i + 1] == 'x' || fmt[i + 1] == 's' ||
			    fmt[i + 1] == 'S') अणु
				/* just kernel poपूर्णांकers */
				अगर (पंचांगp_buf)
					cur_arg = raw_args[num_spec];
				i++;
				जाओ nocopy_fmt;
			पूर्ण

			अगर (fmt[i + 1] == 'B') अणु
				अगर (पंचांगp_buf)  अणु
					err = snम_लिखो(पंचांगp_buf,
						       (पंचांगp_buf_end - पंचांगp_buf),
						       "%pB",
						       (व्योम *)(दीर्घ)raw_args[num_spec]);
					पंचांगp_buf += (err + 1);
				पूर्ण

				i++;
				num_spec++;
				जारी;
			पूर्ण

			/* only support "%pI4", "%pi4", "%pI6" and "%pi6". */
			अगर ((fmt[i + 1] != 'i' && fmt[i + 1] != 'I') ||
			    (fmt[i + 2] != '4' && fmt[i + 2] != '6')) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण

			i += 2;
			अगर (!पंचांगp_buf)
				जाओ nocopy_fmt;

			माप_cur_ip = (fmt[i] == '4') ? 4 : 16;
			अगर (पंचांगp_buf_end - पंचांगp_buf < माप_cur_ip) अणु
				err = -ENOSPC;
				जाओ out;
			पूर्ण

			unsafe_ptr = (अक्षर *)(दीर्घ)raw_args[num_spec];
			err = copy_from_kernel_nofault(cur_ip, unsafe_ptr,
						       माप_cur_ip);
			अगर (err < 0)
				स_रखो(cur_ip, 0, माप_cur_ip);

			/* hack: bstr_म_लिखो expects IP addresses to be
			 * pre-क्रमmatted as strings, ironically, the easiest way
			 * to करो that is to call snम_लिखो.
			 */
			ip_spec[2] = fmt[i - 1];
			ip_spec[3] = fmt[i];
			err = snम_लिखो(पंचांगp_buf, पंचांगp_buf_end - पंचांगp_buf,
				       ip_spec, &cur_ip);

			पंचांगp_buf += err + 1;
			num_spec++;

			जारी;
		पूर्ण अन्यथा अगर (fmt[i] == 's') अणु
			fmt_ptype = fmt[i];
fmt_str:
			अगर (fmt[i + 1] != 0 &&
			    !है_खाली(fmt[i + 1]) &&
			    !है_विराम(fmt[i + 1])) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण

			अगर (!पंचांगp_buf)
				जाओ nocopy_fmt;

			अगर (पंचांगp_buf_end == पंचांगp_buf) अणु
				err = -ENOSPC;
				जाओ out;
			पूर्ण

			unsafe_ptr = (अक्षर *)(दीर्घ)raw_args[num_spec];
			err = bpf_trace_copy_string(पंचांगp_buf, unsafe_ptr,
						    fmt_ptype,
						    पंचांगp_buf_end - पंचांगp_buf);
			अगर (err < 0) अणु
				पंचांगp_buf[0] = '\0';
				err = 1;
			पूर्ण

			पंचांगp_buf += err;
			num_spec++;

			जारी;
		पूर्ण

		माप_cur_arg = माप(पूर्णांक);

		अगर (fmt[i] == 'l') अणु
			माप_cur_arg = माप(दीर्घ);
			i++;
		पूर्ण
		अगर (fmt[i] == 'l') अणु
			माप_cur_arg = माप(दीर्घ दीर्घ);
			i++;
		पूर्ण

		अगर (fmt[i] != 'i' && fmt[i] != 'd' && fmt[i] != 'u' &&
		    fmt[i] != 'x' && fmt[i] != 'X') अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (पंचांगp_buf)
			cur_arg = raw_args[num_spec];
nocopy_fmt:
		अगर (पंचांगp_buf) अणु
			पंचांगp_buf = PTR_ALIGN(पंचांगp_buf, माप(u32));
			अगर (पंचांगp_buf_end - पंचांगp_buf < माप_cur_arg) अणु
				err = -ENOSPC;
				जाओ out;
			पूर्ण

			अगर (माप_cur_arg == 8) अणु
				*(u32 *)पंचांगp_buf = *(u32 *)&cur_arg;
				*(u32 *)(पंचांगp_buf + 4) = *((u32 *)&cur_arg + 1);
			पूर्ण अन्यथा अणु
				*(u32 *)पंचांगp_buf = (u32)(दीर्घ)cur_arg;
			पूर्ण
			पंचांगp_buf += माप_cur_arg;
		पूर्ण
		num_spec++;
	पूर्ण

	err = 0;
out:
	अगर (err)
		bpf_bम_लिखो_cleanup();
	वापस err;
पूर्ण

#घोषणा MAX_SNPRINTF_VARARGS		12

BPF_CALL_5(bpf_snम_लिखो, अक्षर *, str, u32, str_size, अक्षर *, fmt,
	   स्थिर व्योम *, data, u32, data_len)
अणु
	पूर्णांक err, num_args;
	u32 *bin_args;

	अगर (data_len % 8 || data_len > MAX_SNPRINTF_VARARGS * 8 ||
	    (data_len && !data))
		वापस -EINVAL;
	num_args = data_len / 8;

	/* ARG_PTR_TO_CONST_STR guarantees that fmt is zero-terminated so we
	 * can safely give an unbounded size.
	 */
	err = bpf_bम_लिखो_prepare(fmt, अच_पूर्णांक_उच्च, data, &bin_args, num_args);
	अगर (err < 0)
		वापस err;

	err = bstr_म_लिखो(str, str_size, fmt, bin_args);

	bpf_bम_लिखो_cleanup();

	वापस err + 1;
पूर्ण

स्थिर काष्ठा bpf_func_proto bpf_snम_लिखो_proto = अणु
	.func		= bpf_snम_लिखो,
	.gpl_only	= true,
	.ret_type	= RET_INTEGER,
	.arg1_type	= ARG_PTR_TO_MEM_OR_शून्य,
	.arg2_type	= ARG_CONST_SIZE_OR_ZERO,
	.arg3_type	= ARG_PTR_TO_CONST_STR,
	.arg4_type	= ARG_PTR_TO_MEM_OR_शून्य,
	.arg5_type	= ARG_CONST_SIZE_OR_ZERO,
पूर्ण;

स्थिर काष्ठा bpf_func_proto bpf_get_current_task_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_probe_पढ़ो_user_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_probe_पढ़ो_user_str_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_probe_पढ़ो_kernel_proto __weak;
स्थिर काष्ठा bpf_func_proto bpf_probe_पढ़ो_kernel_str_proto __weak;

स्थिर काष्ठा bpf_func_proto *
bpf_base_func_proto(क्रमागत bpf_func_id func_id)
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
	हाल BPF_FUNC_get_pअक्रमom_u32:
		वापस &bpf_get_pअक्रमom_u32_proto;
	हाल BPF_FUNC_get_smp_processor_id:
		वापस &bpf_get_raw_smp_processor_id_proto;
	हाल BPF_FUNC_get_numa_node_id:
		वापस &bpf_get_numa_node_id_proto;
	हाल BPF_FUNC_tail_call:
		वापस &bpf_tail_call_proto;
	हाल BPF_FUNC_kसमय_get_ns:
		वापस &bpf_kसमय_get_ns_proto;
	हाल BPF_FUNC_kसमय_get_boot_ns:
		वापस &bpf_kसमय_get_boot_ns_proto;
	हाल BPF_FUNC_kसमय_get_coarse_ns:
		वापस &bpf_kसमय_get_coarse_ns_proto;
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
	हाल BPF_FUNC_क्रम_each_map_elem:
		वापस &bpf_क्रम_each_map_elem_proto;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!bpf_capable())
		वापस शून्य;

	चयन (func_id) अणु
	हाल BPF_FUNC_spin_lock:
		वापस &bpf_spin_lock_proto;
	हाल BPF_FUNC_spin_unlock:
		वापस &bpf_spin_unlock_proto;
	हाल BPF_FUNC_jअगरfies64:
		वापस &bpf_jअगरfies64_proto;
	हाल BPF_FUNC_per_cpu_ptr:
		वापस &bpf_per_cpu_ptr_proto;
	हाल BPF_FUNC_this_cpu_ptr:
		वापस &bpf_this_cpu_ptr_proto;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!perfmon_capable())
		वापस शून्य;

	चयन (func_id) अणु
	हाल BPF_FUNC_trace_prपूर्णांकk:
		वापस bpf_get_trace_prपूर्णांकk_proto();
	हाल BPF_FUNC_get_current_task:
		वापस &bpf_get_current_task_proto;
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
	हाल BPF_FUNC_snम_लिखो_btf:
		वापस &bpf_snम_लिखो_btf_proto;
	हाल BPF_FUNC_snम_लिखो:
		वापस &bpf_snम_लिखो_proto;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण
