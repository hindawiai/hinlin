<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020 Facebook
 * Copyright 2020 Google LLC.
 */

#समावेश <linux/pid.h>
#समावेश <linux/sched.h>
#समावेश <linux/rculist.h>
#समावेश <linux/list.h>
#समावेश <linux/hash.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_local_storage.h>
#समावेश <linux/filter.h>
#समावेश <uapi/linux/btf.h>
#समावेश <linux/btf_ids.h>
#समावेश <linux/fdtable.h>

DEFINE_BPF_STORAGE_CACHE(task_cache);

अटल DEFINE_PER_CPU(पूर्णांक, bpf_task_storage_busy);

अटल व्योम bpf_task_storage_lock(व्योम)
अणु
	migrate_disable();
	__this_cpu_inc(bpf_task_storage_busy);
पूर्ण

अटल व्योम bpf_task_storage_unlock(व्योम)
अणु
	__this_cpu_dec(bpf_task_storage_busy);
	migrate_enable();
पूर्ण

अटल bool bpf_task_storage_trylock(व्योम)
अणु
	migrate_disable();
	अगर (unlikely(__this_cpu_inc_वापस(bpf_task_storage_busy) != 1)) अणु
		__this_cpu_dec(bpf_task_storage_busy);
		migrate_enable();
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल काष्ठा bpf_local_storage __rcu **task_storage_ptr(व्योम *owner)
अणु
	काष्ठा task_काष्ठा *task = owner;

	वापस &task->bpf_storage;
पूर्ण

अटल काष्ठा bpf_local_storage_data *
task_storage_lookup(काष्ठा task_काष्ठा *task, काष्ठा bpf_map *map,
		    bool cacheit_lockit)
अणु
	काष्ठा bpf_local_storage *task_storage;
	काष्ठा bpf_local_storage_map *smap;

	task_storage = rcu_dereference(task->bpf_storage);
	अगर (!task_storage)
		वापस शून्य;

	smap = (काष्ठा bpf_local_storage_map *)map;
	वापस bpf_local_storage_lookup(task_storage, smap, cacheit_lockit);
पूर्ण

व्योम bpf_task_storage_मुक्त(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा bpf_local_storage_elem *selem;
	काष्ठा bpf_local_storage *local_storage;
	bool मुक्त_task_storage = false;
	काष्ठा hlist_node *n;
	अचिन्हित दीर्घ flags;

	rcu_पढ़ो_lock();

	local_storage = rcu_dereference(task->bpf_storage);
	अगर (!local_storage) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	/* Neither the bpf_prog nor the bpf-map's syscall
	 * could be modअगरying the local_storage->list now.
	 * Thus, no elem can be added-to or deleted-from the
	 * local_storage->list by the bpf_prog or by the bpf-map's syscall.
	 *
	 * It is racing with bpf_local_storage_map_मुक्त() alone
	 * when unlinking elem from the local_storage->list and
	 * the map's bucket->list.
	 */
	bpf_task_storage_lock();
	raw_spin_lock_irqsave(&local_storage->lock, flags);
	hlist_क्रम_each_entry_safe(selem, n, &local_storage->list, snode) अणु
		/* Always unlink from map beक्रमe unlinking from
		 * local_storage.
		 */
		bpf_selem_unlink_map(selem);
		मुक्त_task_storage = bpf_selem_unlink_storage_nolock(
			local_storage, selem, false);
	पूर्ण
	raw_spin_unlock_irqrestore(&local_storage->lock, flags);
	bpf_task_storage_unlock();
	rcu_पढ़ो_unlock();

	/* मुक्त_task_storage should always be true as दीर्घ as
	 * local_storage->list was non-empty.
	 */
	अगर (मुक्त_task_storage)
		kमुक्त_rcu(local_storage, rcu);
पूर्ण

अटल व्योम *bpf_pid_task_storage_lookup_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा bpf_local_storage_data *sdata;
	काष्ठा task_काष्ठा *task;
	अचिन्हित पूर्णांक f_flags;
	काष्ठा pid *pid;
	पूर्णांक fd, err;

	fd = *(पूर्णांक *)key;
	pid = pidfd_get_pid(fd, &f_flags);
	अगर (IS_ERR(pid))
		वापस ERR_CAST(pid);

	/* We should be in an RCU पढ़ो side critical section, it should be safe
	 * to call pid_task.
	 */
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	task = pid_task(pid, PIDTYPE_PID);
	अगर (!task) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	bpf_task_storage_lock();
	sdata = task_storage_lookup(task, map, true);
	bpf_task_storage_unlock();
	put_pid(pid);
	वापस sdata ? sdata->data : शून्य;
out:
	put_pid(pid);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक bpf_pid_task_storage_update_elem(काष्ठा bpf_map *map, व्योम *key,
					    व्योम *value, u64 map_flags)
अणु
	काष्ठा bpf_local_storage_data *sdata;
	काष्ठा task_काष्ठा *task;
	अचिन्हित पूर्णांक f_flags;
	काष्ठा pid *pid;
	पूर्णांक fd, err;

	fd = *(पूर्णांक *)key;
	pid = pidfd_get_pid(fd, &f_flags);
	अगर (IS_ERR(pid))
		वापस PTR_ERR(pid);

	/* We should be in an RCU पढ़ो side critical section, it should be safe
	 * to call pid_task.
	 */
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	task = pid_task(pid, PIDTYPE_PID);
	अगर (!task) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	bpf_task_storage_lock();
	sdata = bpf_local_storage_update(
		task, (काष्ठा bpf_local_storage_map *)map, value, map_flags);
	bpf_task_storage_unlock();

	err = PTR_ERR_OR_ZERO(sdata);
out:
	put_pid(pid);
	वापस err;
पूर्ण

अटल पूर्णांक task_storage_delete(काष्ठा task_काष्ठा *task, काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_local_storage_data *sdata;

	sdata = task_storage_lookup(task, map, false);
	अगर (!sdata)
		वापस -ENOENT;

	bpf_selem_unlink(SELEM(sdata));

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_pid_task_storage_delete_elem(काष्ठा bpf_map *map, व्योम *key)
अणु
	काष्ठा task_काष्ठा *task;
	अचिन्हित पूर्णांक f_flags;
	काष्ठा pid *pid;
	पूर्णांक fd, err;

	fd = *(पूर्णांक *)key;
	pid = pidfd_get_pid(fd, &f_flags);
	अगर (IS_ERR(pid))
		वापस PTR_ERR(pid);

	/* We should be in an RCU पढ़ो side critical section, it should be safe
	 * to call pid_task.
	 */
	WARN_ON_ONCE(!rcu_पढ़ो_lock_held());
	task = pid_task(pid, PIDTYPE_PID);
	अगर (!task) अणु
		err = -ENOENT;
		जाओ out;
	पूर्ण

	bpf_task_storage_lock();
	err = task_storage_delete(task, map);
	bpf_task_storage_unlock();
out:
	put_pid(pid);
	वापस err;
पूर्ण

BPF_CALL_4(bpf_task_storage_get, काष्ठा bpf_map *, map, काष्ठा task_काष्ठा *,
	   task, व्योम *, value, u64, flags)
अणु
	काष्ठा bpf_local_storage_data *sdata;

	अगर (flags & ~(BPF_LOCAL_STORAGE_GET_F_CREATE))
		वापस (अचिन्हित दीर्घ)शून्य;

	अगर (!task)
		वापस (अचिन्हित दीर्घ)शून्य;

	अगर (!bpf_task_storage_trylock())
		वापस (अचिन्हित दीर्घ)शून्य;

	sdata = task_storage_lookup(task, map, true);
	अगर (sdata)
		जाओ unlock;

	/* only allocate new storage, when the task is refcounted */
	अगर (refcount_पढ़ो(&task->usage) &&
	    (flags & BPF_LOCAL_STORAGE_GET_F_CREATE))
		sdata = bpf_local_storage_update(
			task, (काष्ठा bpf_local_storage_map *)map, value,
			BPF_NOEXIST);

unlock:
	bpf_task_storage_unlock();
	वापस IS_ERR_OR_शून्य(sdata) ? (अचिन्हित दीर्घ)शून्य :
		(अचिन्हित दीर्घ)sdata->data;
पूर्ण

BPF_CALL_2(bpf_task_storage_delete, काष्ठा bpf_map *, map, काष्ठा task_काष्ठा *,
	   task)
अणु
	पूर्णांक ret;

	अगर (!task)
		वापस -EINVAL;

	अगर (!bpf_task_storage_trylock())
		वापस -EBUSY;

	/* This helper must only be called from places where the lअगरeसमय of the task
	 * is guaranteed. Either by being refcounted or by being रक्षित
	 * by an RCU पढ़ो-side critical section.
	 */
	ret = task_storage_delete(task, map);
	bpf_task_storage_unlock();
	वापस ret;
पूर्ण

अटल पूर्णांक notsupp_get_next_key(काष्ठा bpf_map *map, व्योम *key, व्योम *next_key)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल काष्ठा bpf_map *task_storage_map_alloc(जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_local_storage_map *smap;

	smap = bpf_local_storage_map_alloc(attr);
	अगर (IS_ERR(smap))
		वापस ERR_CAST(smap);

	smap->cache_idx = bpf_local_storage_cache_idx_get(&task_cache);
	वापस &smap->map;
पूर्ण

अटल व्योम task_storage_map_मुक्त(काष्ठा bpf_map *map)
अणु
	काष्ठा bpf_local_storage_map *smap;

	smap = (काष्ठा bpf_local_storage_map *)map;
	bpf_local_storage_cache_idx_मुक्त(&task_cache, smap->cache_idx);
	bpf_local_storage_map_मुक्त(smap, &bpf_task_storage_busy);
पूर्ण

अटल पूर्णांक task_storage_map_btf_id;
स्थिर काष्ठा bpf_map_ops task_storage_map_ops = अणु
	.map_meta_equal = bpf_map_meta_equal,
	.map_alloc_check = bpf_local_storage_map_alloc_check,
	.map_alloc = task_storage_map_alloc,
	.map_मुक्त = task_storage_map_मुक्त,
	.map_get_next_key = notsupp_get_next_key,
	.map_lookup_elem = bpf_pid_task_storage_lookup_elem,
	.map_update_elem = bpf_pid_task_storage_update_elem,
	.map_delete_elem = bpf_pid_task_storage_delete_elem,
	.map_check_btf = bpf_local_storage_map_check_btf,
	.map_btf_name = "bpf_local_storage_map",
	.map_btf_id = &task_storage_map_btf_id,
	.map_owner_storage_ptr = task_storage_ptr,
पूर्ण;

BTF_ID_LIST_SINGLE(bpf_task_storage_btf_ids, काष्ठा, task_काष्ठा)

स्थिर काष्ठा bpf_func_proto bpf_task_storage_get_proto = अणु
	.func = bpf_task_storage_get,
	.gpl_only = false,
	.ret_type = RET_PTR_TO_MAP_VALUE_OR_शून्य,
	.arg1_type = ARG_CONST_MAP_PTR,
	.arg2_type = ARG_PTR_TO_BTF_ID,
	.arg2_btf_id = &bpf_task_storage_btf_ids[0],
	.arg3_type = ARG_PTR_TO_MAP_VALUE_OR_शून्य,
	.arg4_type = ARG_ANYTHING,
पूर्ण;

स्थिर काष्ठा bpf_func_proto bpf_task_storage_delete_proto = अणु
	.func = bpf_task_storage_delete,
	.gpl_only = false,
	.ret_type = RET_INTEGER,
	.arg1_type = ARG_CONST_MAP_PTR,
	.arg2_type = ARG_PTR_TO_BTF_ID,
	.arg2_btf_id = &bpf_task_storage_btf_ids[0],
पूर्ण;
